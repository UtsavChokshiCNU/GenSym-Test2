/* smlt1.c
 * Input file:  simulate1.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "smlt1.h"


DEFINE_VARIABLE_WITH_SYMBOL(Available_simulate_conses, Qavailable_simulate_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_simulate_conses_tail, Qavailable_simulate_conses_tail);

Object Available_simulate_conses_vector = UNBOUND;

Object Available_simulate_conses_tail_vector = UNBOUND;

Object Simulate_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Simulate_cons_counter, Qsimulate_cons_counter);

/* OUTSTANDING-SIMULATE-CONSES */
Object outstanding_simulate_conses()
{
    Object temp;

    x_note_fn_call(184,0);
    temp = FIXNUM_MINUS(Simulate_cons_counter,
	    length(Available_simulate_conses));
    return VALUES_1(temp);
}

/* SIMULATE-CONS-MEMORY-USAGE */
Object simulate_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(184,1);
    temp = FIXNUM_TIMES(Simulate_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-SIMULATE-CONS-POOL */
Object replenish_simulate_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(184,2);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qsimulate_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_simulate_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_simulate_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_simulate_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_simulate_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_simulate_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Simulate_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qsimulate;           /* simulate */

/* SIMULATE-CONS-1 */
Object simulate_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(184,3);
    new_cons = ISVREF(Available_simulate_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_simulate_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_simulate_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_simulate_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_simulate_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qsimulate);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-SIMULATE-LIST-POOL */
Object replenish_simulate_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(184,4);
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
    if (ISVREF(Available_simulate_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_simulate_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_simulate_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_simulate_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_simulate_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qsimulate_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-SIMULATE-LIST-1 */
Object make_simulate_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(184,5);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_simulate_conses_vector,
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
	replenish_simulate_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_simulate_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qsimulate);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_simulate_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_simulate_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_simulate_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_simulate_conses_tail_vector;
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

/* SIMULATE-LIST-2 */
Object simulate_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(184,6);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_simulate_conses_vector,IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_simulate_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_simulate_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qsimulate);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_simulate_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_simulate_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_simulate_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_simulate_conses_tail_vector;
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

/* SIMULATE-LIST-3 */
Object simulate_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(184,7);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_simulate_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_simulate_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_simulate_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qsimulate);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_simulate_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_simulate_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_simulate_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_simulate_conses_tail_vector;
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

/* SIMULATE-LIST-4 */
Object simulate_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(184,8);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_simulate_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_simulate_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_simulate_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qsimulate);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_simulate_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_simulate_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_simulate_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_simulate_conses_tail_vector;
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

/* SIMULATE-LIST-TRACE-HOOK */
Object simulate_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(184,9);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-SIMULATE-CONSES-1 */
Object copy_tree_using_simulate_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(184,10);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_simulate_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_simulate_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_simulate_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_simulate_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_simulate_cons_pool();
	temp_1 = copy_tree_using_simulate_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qsimulate);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_simulate_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_simulate_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_simulate_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_simulate_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_simulate_cons_pool();
	temp_1 = copy_tree_using_simulate_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qsimulate);
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

/* COPY-LIST-USING-SIMULATE-CONSES-1 */
Object copy_list_using_simulate_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(184,11);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_simulate_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_simulate_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_simulate_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_simulate_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_simulate_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qsimulate);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_simulate_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_simulate_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_simulate_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_simulate_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_simulate_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qsimulate);
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

/* RECLAIM-SIMULATE-CONS-1 */
Object reclaim_simulate_cons_1(simulate_cons)
    Object simulate_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(184,12);
    inline_note_reclaim_cons(simulate_cons,Qsimulate);
    if (ISVREF(Available_simulate_conses_tail_vector,
	    IFIX(Current_thread_index))) {
	temp = ISVREF(Available_simulate_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = simulate_cons;
	temp = Available_simulate_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = simulate_cons;
    }
    else {
	temp = Available_simulate_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = simulate_cons;
	temp = Available_simulate_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = simulate_cons;
    }
    M_CDR(simulate_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-SIMULATE-LIST-1 */
Object reclaim_simulate_list_1(simulate_list)
    Object simulate_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(184,13);
    if (simulate_list) {
	last_1 = simulate_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qsimulate);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qsimulate);
	if (ISVREF(Available_simulate_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_simulate_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = simulate_list;
	    temp = Available_simulate_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_simulate_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = simulate_list;
	    temp = Available_simulate_conses_tail_vector;
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

/* RECLAIM-SIMULATE-LIST*-1 */
Object reclaim_simulate_list_star_1(simulate_list)
    Object simulate_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(184,14);
    if (CONSP(simulate_list)) {
	temp = last(simulate_list,_);
	M_CDR(temp) = Nil;
	if (simulate_list) {
	    last_1 = simulate_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qsimulate);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qsimulate);
	    if (ISVREF(Available_simulate_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_simulate_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = simulate_list;
		temp = Available_simulate_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_simulate_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = simulate_list;
		temp = Available_simulate_conses_tail_vector;
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

/* RECLAIM-SIMULATE-TREE-1 */
Object reclaim_simulate_tree_1(tree)
    Object tree;
{
    Object e, e2, simulate_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(184,15);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_simulate_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		simulate_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(simulate_cons,Qsimulate);
		if (EQ(simulate_cons,e))
		    goto end_1;
		else if ( !TRUEP(simulate_cons))
		    goto end_1;
		else
		    simulate_cons = CDR(simulate_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_simulate_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_simulate_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_simulate_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_simulate_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_simulate_conses_tail_vector;
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

/* DELETE-SIMULATE-ELEMENT-1 */
Object delete_simulate_element_1(element,simulate_list)
    Object element, simulate_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(184,16);
    if (simulate_list) {
	if (EQ(element,M_CAR(simulate_list))) {
	    temp = CDR(simulate_list);
	    inline_note_reclaim_cons(simulate_list,Qsimulate);
	    if (ISVREF(Available_simulate_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_simulate_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = simulate_list;
		temp_1 = Available_simulate_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = simulate_list;
	    }
	    else {
		temp_1 = Available_simulate_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = simulate_list;
		temp_1 = Available_simulate_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = simulate_list;
	    }
	    M_CDR(simulate_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = simulate_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qsimulate);
		if (ISVREF(Available_simulate_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_simulate_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_simulate_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_simulate_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_simulate_conses_tail_vector;
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
	    temp = simulate_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-SIMULATE-CONS-1 */
Object delete_simulate_cons_1(simulate_cons,simulate_list)
    Object simulate_cons, simulate_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(184,17);
    if (EQ(simulate_cons,simulate_list))
	temp = CDR(simulate_list);
    else {
	l_trailer_qm = Nil;
	l = simulate_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,simulate_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = simulate_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_simulate_cons_1(simulate_cons);
    return VALUES_1(temp);
}

static Object Qsimulation_info_qm;  /* simulation-info? */

/* ADD-TO-INSTALLATION-SET */
Object add_to_installation_set(installation_set,element)
    Object installation_set, element;
{
    Object element_set_structure_qm, first_element_qm;

    x_note_fn_call(184,18);
    element_set_structure_qm = get_lookup_slot_value_given_default(element,
	    Qsimulation_info_qm,Nil);
    if (element_set_structure_qm) {
	delete_from_installation_set(element);
	first_element_qm = ISVREF(installation_set,(SI_Long)9L);
	SVREF(installation_set,FIX((SI_Long)9L)) = element_set_structure_qm;
	SVREF(element_set_structure_qm,FIX((SI_Long)10L)) = installation_set;
	if (first_element_qm) {
	    SVREF(first_element_qm,FIX((SI_Long)10L)) = 
		    element_set_structure_qm;
	    return VALUES_1(SVREF(element_set_structure_qm,
		    FIX((SI_Long)9L)) = first_element_qm);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* DELETE-FROM-INSTALLATION-SET */
Object delete_from_installation_set(element)
    Object element;
{
    Object element_set_structure_qm, previous_structure_or_header_qm;
    Object next_structure_qm;

    x_note_fn_call(184,19);
    element_set_structure_qm = get_lookup_slot_value_given_default(element,
	    Qsimulation_info_qm,Nil);
    previous_structure_or_header_qm = element_set_structure_qm ? 
	    ISVREF(element_set_structure_qm,(SI_Long)10L) : Nil;
    next_structure_qm = ISVREF(element_set_structure_qm,(SI_Long)9L);
    if (previous_structure_or_header_qm)
	SVREF(previous_structure_or_header_qm,FIX((SI_Long)9L)) = 
		next_structure_qm;
    if (next_structure_qm)
	SVREF(next_structure_qm,FIX((SI_Long)10L)) = 
		previous_structure_or_header_qm;
    SVREF(element_set_structure_qm,FIX((SI_Long)10L)) = Nil;
    return VALUES_1(SVREF(element_set_structure_qm,FIX((SI_Long)9L)) = Nil);
}

/* MAKE-INSTALLATION-SET */
Object make_installation_set()
{
    x_note_fn_call(184,20);
    return make_simulation_info_1();
}

/* RECLAIM-INSTALLATION-SET */
Object reclaim_installation_set(installation_set)
    Object installation_set;
{
    Object first_element_qm;

    x_note_fn_call(184,21);
    first_element_qm = ISVREF(installation_set,(SI_Long)9L);
    if (first_element_qm)
	SVREF(first_element_qm,FIX((SI_Long)10L)) = Nil;
    return reclaim_simulation_info_1(installation_set);
}

/* CLEAR-INSTALLATION-SET */
Object clear_installation_set(installation_set)
    Object installation_set;
{
    Object first_element_qm;

    x_note_fn_call(184,22);
    first_element_qm = ISVREF(installation_set,(SI_Long)9L);
    if (first_element_qm) {
	SVREF(first_element_qm,FIX((SI_Long)10L)) = Nil;
	return VALUES_1(SVREF(installation_set,FIX((SI_Long)9L)) = Nil);
    }
    else
	return VALUES_1(Nil);
}

/* INSTALLATION-SET-EMPTY? */
Object installation_set_empty_qm(installation_set)
    Object installation_set;
{
    x_note_fn_call(184,23);
    return VALUES_1( !TRUEP(ISVREF(installation_set,(SI_Long)9L)) ? T : Nil);
}

/* INSERT-IN-INSTALLATION-SET */
Object insert_in_installation_set(insert_pointer,element)
    Object insert_pointer, element;
{
    Object element_set_structure_qm, insert_before_pointer_qm;

    x_note_fn_call(184,24);
    element_set_structure_qm = get_lookup_slot_value_given_default(element,
	    Qsimulation_info_qm,Nil);
    insert_before_pointer_qm = Nil;
    if (element_set_structure_qm) {
	delete_from_installation_set(element);
	insert_before_pointer_qm = ISVREF(insert_pointer,(SI_Long)9L);
	SVREF(insert_pointer,FIX((SI_Long)9L)) = element_set_structure_qm;
	SVREF(element_set_structure_qm,FIX((SI_Long)10L)) = insert_pointer;
	if (insert_before_pointer_qm) {
	    SVREF(element_set_structure_qm,FIX((SI_Long)9L)) = 
		    insert_before_pointer_qm;
	    return VALUES_1(SVREF(insert_before_pointer_qm,
		    FIX((SI_Long)10L)) = element_set_structure_qm);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* FOR-EACH-ELEMENT-IN-INSTALLATION-SET */
Object for_each_element_in_installation_set(installation_set,
	    function_for_element)
    Object installation_set, function_for_element;
{
    Object first_element_qm, element_set_structure_qm, element, temp;

    x_note_fn_call(184,25);
    first_element_qm = ISVREF(installation_set,(SI_Long)9L);
    if (first_element_qm) {
	element_set_structure_qm = first_element_qm;
	element = Nil;
      next_loop:
	if ( !TRUEP(element_set_structure_qm))
	    goto end_loop;
	element = ISVREF(element_set_structure_qm,(SI_Long)11L);
	temp = SYMBOL_FUNCTION(function_for_element);
	FUNCALL_1(temp,element);
	element_set_structure_qm = ISVREF(element_set_structure_qm,
		(SI_Long)9L);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* ADD-TO-REDERIVE-SET */
Object add_to_rederive_set(rederive_set,element)
    Object rederive_set, element;
{
    Object element_set_structure_qm, first_element_qm;

    x_note_fn_call(184,26);
    element_set_structure_qm = get_lookup_slot_value_given_default(element,
	    Qsimulation_info_qm,Nil);
    if (element_set_structure_qm) {
	delete_from_rederive_set(element);
	first_element_qm = ISVREF(rederive_set,(SI_Long)12L);
	SVREF(rederive_set,FIX((SI_Long)12L)) = element_set_structure_qm;
	SVREF(element_set_structure_qm,FIX((SI_Long)13L)) = rederive_set;
	if (first_element_qm) {
	    SVREF(first_element_qm,FIX((SI_Long)13L)) = 
		    element_set_structure_qm;
	    return VALUES_1(SVREF(element_set_structure_qm,
		    FIX((SI_Long)12L)) = first_element_qm);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* DELETE-FROM-REDERIVE-SET */
Object delete_from_rederive_set(element)
    Object element;
{
    Object element_set_structure_qm, previous_structure_or_header_qm;
    Object next_structure_qm;

    x_note_fn_call(184,27);
    element_set_structure_qm = get_lookup_slot_value_given_default(element,
	    Qsimulation_info_qm,Nil);
    previous_structure_or_header_qm = element_set_structure_qm ? 
	    ISVREF(element_set_structure_qm,(SI_Long)13L) : Nil;
    next_structure_qm = ISVREF(element_set_structure_qm,(SI_Long)12L);
    if (previous_structure_or_header_qm)
	SVREF(previous_structure_or_header_qm,FIX((SI_Long)12L)) = 
		next_structure_qm;
    if (next_structure_qm)
	SVREF(next_structure_qm,FIX((SI_Long)13L)) = 
		previous_structure_or_header_qm;
    SVREF(element_set_structure_qm,FIX((SI_Long)13L)) = Nil;
    return VALUES_1(SVREF(element_set_structure_qm,FIX((SI_Long)12L)) = Nil);
}

/* MAKE-REDERIVE-SET */
Object make_rederive_set()
{
    x_note_fn_call(184,28);
    return make_simulation_info_1();
}

/* RECLAIM-REDERIVE-SET */
Object reclaim_rederive_set(rederive_set)
    Object rederive_set;
{
    Object first_element_qm;

    x_note_fn_call(184,29);
    first_element_qm = ISVREF(rederive_set,(SI_Long)12L);
    if (first_element_qm)
	SVREF(first_element_qm,FIX((SI_Long)13L)) = Nil;
    return reclaim_simulation_info_1(rederive_set);
}

/* CLEAR-REDERIVE-SET */
Object clear_rederive_set(rederive_set)
    Object rederive_set;
{
    Object first_element_qm;

    x_note_fn_call(184,30);
    first_element_qm = ISVREF(rederive_set,(SI_Long)12L);
    if (first_element_qm) {
	SVREF(first_element_qm,FIX((SI_Long)13L)) = Nil;
	return VALUES_1(SVREF(rederive_set,FIX((SI_Long)12L)) = Nil);
    }
    else
	return VALUES_1(Nil);
}

/* REDERIVE-SET-EMPTY? */
Object rederive_set_empty_qm(rederive_set)
    Object rederive_set;
{
    x_note_fn_call(184,31);
    return VALUES_1( !TRUEP(ISVREF(rederive_set,(SI_Long)12L)) ? T : Nil);
}

/* INSERT-IN-REDERIVE-SET */
Object insert_in_rederive_set(insert_pointer,element)
    Object insert_pointer, element;
{
    Object element_set_structure_qm, insert_before_pointer_qm;

    x_note_fn_call(184,32);
    element_set_structure_qm = get_lookup_slot_value_given_default(element,
	    Qsimulation_info_qm,Nil);
    insert_before_pointer_qm = Nil;
    if (element_set_structure_qm) {
	delete_from_rederive_set(element);
	insert_before_pointer_qm = ISVREF(insert_pointer,(SI_Long)12L);
	SVREF(insert_pointer,FIX((SI_Long)12L)) = element_set_structure_qm;
	SVREF(element_set_structure_qm,FIX((SI_Long)13L)) = insert_pointer;
	if (insert_before_pointer_qm) {
	    SVREF(element_set_structure_qm,FIX((SI_Long)12L)) = 
		    insert_before_pointer_qm;
	    return VALUES_1(SVREF(insert_before_pointer_qm,
		    FIX((SI_Long)13L)) = element_set_structure_qm);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* FOR-EACH-ELEMENT-IN-REDERIVE-SET */
Object for_each_element_in_rederive_set(rederive_set,function_for_element)
    Object rederive_set, function_for_element;
{
    Object first_element_qm, element_set_structure_qm, element, temp;

    x_note_fn_call(184,33);
    first_element_qm = ISVREF(rederive_set,(SI_Long)12L);
    if (first_element_qm) {
	element_set_structure_qm = first_element_qm;
	element = Nil;
      next_loop:
	if ( !TRUEP(element_set_structure_qm))
	    goto end_loop;
	element = ISVREF(element_set_structure_qm,(SI_Long)11L);
	temp = SYMBOL_FUNCTION(function_for_element);
	FUNCALL_1(temp,element);
	element_set_structure_qm = ISVREF(element_set_structure_qm,
		(SI_Long)12L);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

Object The_type_description_of_external_set_pointers = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_external_set_pointerss, Qchain_of_available_external_set_pointerss);

DEFINE_VARIABLE_WITH_SYMBOL(External_set_pointers_count, Qexternal_set_pointers_count);

Object Chain_of_available_external_set_pointerss_vector = UNBOUND;

/* EXTERNAL-SET-POINTERS-STRUCTURE-MEMORY-USAGE */
Object external_set_pointers_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(184,34);
    temp = External_set_pointers_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)4L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-EXTERNAL-SET-POINTERS-COUNT */
Object outstanding_external_set_pointers_count()
{
    Object def_structure_external_set_pointers_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(184,35);
    gensymed_symbol = IFIX(External_set_pointers_count);
    def_structure_external_set_pointers_variable = 
	    Chain_of_available_external_set_pointerss;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_external_set_pointers_variable))
	goto end_loop;
    def_structure_external_set_pointers_variable = 
	    ISVREF(def_structure_external_set_pointers_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-EXTERNAL-SET-POINTERS-1 */
Object reclaim_external_set_pointers_1(external_set_pointers)
    Object external_set_pointers;
{
    Object temp, svref_arg_2;

    x_note_fn_call(184,36);
    inline_note_reclaim_cons(external_set_pointers,Nil);
    temp = ISVREF(Chain_of_available_external_set_pointerss_vector,
	    IFIX(Current_thread_index));
    SVREF(external_set_pointers,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_external_set_pointerss_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = external_set_pointers;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-EXTERNAL-SET-POINTERS */
Object reclaim_structure_for_external_set_pointers(external_set_pointers)
    Object external_set_pointers;
{
    x_note_fn_call(184,37);
    return reclaim_external_set_pointers_1(external_set_pointers);
}

static Object Qg2_defstruct_structure_name_external_set_pointers_g2_struct;  /* g2-defstruct-structure-name::external-set-pointers-g2-struct */

/* MAKE-PERMANENT-EXTERNAL-SET-POINTERS-STRUCTURE-INTERNAL */
Object make_permanent_external_set_pointers_structure_internal()
{
    Object def_structure_external_set_pointers_variable;
    Object defstruct_g2_external_set_pointers_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(184,38);
    def_structure_external_set_pointers_variable = Nil;
    atomic_incff_symval(Qexternal_set_pointers_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_external_set_pointers_variable = Nil;
	gensymed_symbol = (SI_Long)4L;
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
	defstruct_g2_external_set_pointers_variable = the_array;
	SVREF(defstruct_g2_external_set_pointers_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_external_set_pointers_g2_struct;
	def_structure_external_set_pointers_variable = 
		defstruct_g2_external_set_pointers_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_external_set_pointers_variable);
}

/* MAKE-EXTERNAL-SET-POINTERS-1 */
Object make_external_set_pointers_1()
{
    Object def_structure_external_set_pointers_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(184,39);
    def_structure_external_set_pointers_variable = 
	    ISVREF(Chain_of_available_external_set_pointerss_vector,
	    IFIX(Current_thread_index));
    if (def_structure_external_set_pointers_variable) {
	svref_arg_1 = Chain_of_available_external_set_pointerss_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_external_set_pointers_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_external_set_pointers_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_external_set_pointers_g2_struct;
    }
    else
	def_structure_external_set_pointers_variable = 
		make_permanent_external_set_pointers_structure_internal();
    inline_note_allocate_cons(def_structure_external_set_pointers_variable,
	    Nil);
    SVREF(def_structure_external_set_pointers_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_external_set_pointers_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_external_set_pointers_variable,FIX((SI_Long)3L)) = Nil;
    return VALUES_1(def_structure_external_set_pointers_variable);
}

/* ADD-TO-EXTERNAL-SET */
Object add_to_external_set(external_set,element)
    Object external_set, element;
{
    Object element_set_structure_qm, first_element_qm;

    x_note_fn_call(184,40);
    element_set_structure_qm = get_external_set_pointers_qm(element);
    if (element_set_structure_qm) {
	delete_from_external_set(element);
	first_element_qm = ISVREF(external_set,(SI_Long)1L);
	SVREF(external_set,FIX((SI_Long)1L)) = element_set_structure_qm;
	SVREF(element_set_structure_qm,FIX((SI_Long)2L)) = external_set;
	if (first_element_qm) {
	    SVREF(first_element_qm,FIX((SI_Long)2L)) = 
		    element_set_structure_qm;
	    return VALUES_1(SVREF(element_set_structure_qm,
		    FIX((SI_Long)1L)) = first_element_qm);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* DELETE-FROM-EXTERNAL-SET */
Object delete_from_external_set(element)
    Object element;
{
    Object element_set_structure_qm, previous_structure_or_header_qm;
    Object next_structure_qm;

    x_note_fn_call(184,41);
    element_set_structure_qm = get_external_set_pointers_qm(element);
    previous_structure_or_header_qm = element_set_structure_qm ? 
	    ISVREF(element_set_structure_qm,(SI_Long)2L) : Nil;
    next_structure_qm = ISVREF(element_set_structure_qm,(SI_Long)1L);
    if (previous_structure_or_header_qm)
	SVREF(previous_structure_or_header_qm,FIX((SI_Long)1L)) = 
		next_structure_qm;
    if (next_structure_qm)
	SVREF(next_structure_qm,FIX((SI_Long)2L)) = 
		previous_structure_or_header_qm;
    SVREF(element_set_structure_qm,FIX((SI_Long)2L)) = Nil;
    return VALUES_1(SVREF(element_set_structure_qm,FIX((SI_Long)1L)) = Nil);
}

/* MAKE-EXTERNAL-SET */
Object make_external_set()
{
    x_note_fn_call(184,42);
    return make_external_set_pointers_1();
}

/* RECLAIM-EXTERNAL-SET */
Object reclaim_external_set(external_set)
    Object external_set;
{
    Object first_element_qm;

    x_note_fn_call(184,43);
    first_element_qm = ISVREF(external_set,(SI_Long)1L);
    if (first_element_qm)
	SVREF(first_element_qm,FIX((SI_Long)2L)) = Nil;
    return reclaim_external_set_pointers_1(external_set);
}

/* CLEAR-EXTERNAL-SET */
Object clear_external_set(external_set)
    Object external_set;
{
    Object first_element_qm;

    x_note_fn_call(184,44);
    first_element_qm = ISVREF(external_set,(SI_Long)1L);
    if (first_element_qm) {
	SVREF(first_element_qm,FIX((SI_Long)2L)) = Nil;
	return VALUES_1(SVREF(external_set,FIX((SI_Long)1L)) = Nil);
    }
    else
	return VALUES_1(Nil);
}

/* EXTERNAL-SET-EMPTY? */
Object external_set_empty_qm(external_set)
    Object external_set;
{
    x_note_fn_call(184,45);
    return VALUES_1( !TRUEP(ISVREF(external_set,(SI_Long)1L)) ? T : Nil);
}

/* INSERT-IN-EXTERNAL-SET */
Object insert_in_external_set(insert_pointer,element)
    Object insert_pointer, element;
{
    Object element_set_structure_qm, insert_before_pointer_qm;

    x_note_fn_call(184,46);
    element_set_structure_qm = get_external_set_pointers_qm(element);
    insert_before_pointer_qm = Nil;
    if (element_set_structure_qm) {
	delete_from_external_set(element);
	insert_before_pointer_qm = ISVREF(insert_pointer,(SI_Long)1L);
	SVREF(insert_pointer,FIX((SI_Long)1L)) = element_set_structure_qm;
	SVREF(element_set_structure_qm,FIX((SI_Long)2L)) = insert_pointer;
	if (insert_before_pointer_qm) {
	    SVREF(element_set_structure_qm,FIX((SI_Long)1L)) = 
		    insert_before_pointer_qm;
	    return VALUES_1(SVREF(insert_before_pointer_qm,
		    FIX((SI_Long)2L)) = element_set_structure_qm);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* FOR-EACH-ELEMENT-IN-EXTERNAL-SET */
Object for_each_element_in_external_set(external_set,function_for_element)
    Object external_set, function_for_element;
{
    Object first_element_qm, element_set_structure_qm, element, temp;

    x_note_fn_call(184,47);
    first_element_qm = ISVREF(external_set,(SI_Long)1L);
    if (first_element_qm) {
	element_set_structure_qm = first_element_qm;
	element = Nil;
      next_loop:
	if ( !TRUEP(element_set_structure_qm))
	    goto end_loop;
	element = ISVREF(element_set_structure_qm,(SI_Long)3L);
	temp = SYMBOL_FUNCTION(function_for_element);
	FUNCALL_1(temp,element);
	element_set_structure_qm = ISVREF(element_set_structure_qm,
		(SI_Long)1L);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qexternal_set_pointers_qm;  /* external-set-pointers? */

/* GET-EXTERNAL-SET-POINTERS? */
Object get_external_set_pointers_qm(entity)
    Object entity;
{
    x_note_fn_call(184,48);
    return get_slot_value_function(entity,Qexternal_set_pointers_qm,Nil);
}

/* MAKE-EXTERNAL-SET-POINTERS-IF-NECESSARY */
Object make_external_set_pointers_if_necessary(entity)
    Object entity;
{
    Object new_external_set_pointers;

    x_note_fn_call(184,49);
    if ( !TRUEP(get_external_set_pointers_qm(entity))) {
	new_external_set_pointers = make_external_set_pointers_1();
	set_slot_value_function(entity,Qexternal_set_pointers_qm,
		new_external_set_pointers,Nil);
	SVREF(new_external_set_pointers,FIX((SI_Long)3L)) = entity;
	return VALUES_1(new_external_set_pointers);
    }
    else
	return VALUES_1(Nil);
}

/* RECLAIM-EXTERNAL-SET-POINTERS?-VALUE */
Object reclaim_external_set_pointers_qm_value(external_set_pointers_qm,entity)
    Object external_set_pointers_qm, entity;
{
    x_note_fn_call(184,50);
    delete_from_external_set(entity);
    reclaim_external_set_pointers_1(external_set_pointers_qm);
    return VALUES_1(Nil);
}

Object The_type_description_of_compound_fixnum_simulation_time = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_compound_fixnum_simulation_times, Qchain_of_available_compound_fixnum_simulation_times);

DEFINE_VARIABLE_WITH_SYMBOL(Compound_fixnum_simulation_time_count, Qcompound_fixnum_simulation_time_count);

Object Chain_of_available_compound_fixnum_simulation_times_vector = UNBOUND;

/* COMPOUND-FIXNUM-SIMULATION-TIME-STRUCTURE-MEMORY-USAGE */
Object compound_fixnum_simulation_time_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(184,51);
    temp = Compound_fixnum_simulation_time_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)3L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-COMPOUND-FIXNUM-SIMULATION-TIME-COUNT */
Object outstanding_compound_fixnum_simulation_time_count()
{
    Object def_structure_compound_fixnum_simulation_time_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(184,52);
    gensymed_symbol = IFIX(Compound_fixnum_simulation_time_count);
    def_structure_compound_fixnum_simulation_time_variable = 
	    Chain_of_available_compound_fixnum_simulation_times;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_compound_fixnum_simulation_time_variable))
	goto end_loop;
    def_structure_compound_fixnum_simulation_time_variable = 
	    ISVREF(def_structure_compound_fixnum_simulation_time_variable,
	    (SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* REAL-RECLAIM-COMPOUND-FIXNUM-SIMULATION-TIME-1 */
Object real_reclaim_compound_fixnum_simulation_time_1(compound_fixnum_simulation_time)
    Object compound_fixnum_simulation_time;
{
    Object temp, svref_arg_2;

    x_note_fn_call(184,53);
    inline_note_reclaim_cons(compound_fixnum_simulation_time,Nil);
    temp = 
	    ISVREF(Chain_of_available_compound_fixnum_simulation_times_vector,
	    IFIX(Current_thread_index));
    SVREF(compound_fixnum_simulation_time,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_compound_fixnum_simulation_times_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = compound_fixnum_simulation_time;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-COMPOUND-FIXNUM-SIMULATION-TIME */
Object reclaim_structure_for_compound_fixnum_simulation_time(compound_fixnum_simulation_time)
    Object compound_fixnum_simulation_time;
{
    x_note_fn_call(184,54);
    return real_reclaim_compound_fixnum_simulation_time_1(compound_fixnum_simulation_time);
}

static Object Qg2_defstruct_structure_name_compound_fixnum_simulation_time_g2_struct;  /* g2-defstruct-structure-name::compound-fixnum-simulation-time-g2-struct */

/* MAKE-PERMANENT-COMPOUND-FIXNUM-SIMULATION-TIME-STRUCTURE-INTERNAL */
Object make_permanent_compound_fixnum_simulation_time_structure_internal()
{
    Object def_structure_compound_fixnum_simulation_time_variable;
    Object defstruct_g2_compound_fixnum_simulation_time_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(184,55);
    def_structure_compound_fixnum_simulation_time_variable = Nil;
    atomic_incff_symval(Qcompound_fixnum_simulation_time_count,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_compound_fixnum_simulation_time_variable = Nil;
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
	defstruct_g2_compound_fixnum_simulation_time_variable = the_array;
	SVREF(defstruct_g2_compound_fixnum_simulation_time_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_compound_fixnum_simulation_time_g2_struct;
	def_structure_compound_fixnum_simulation_time_variable = 
		defstruct_g2_compound_fixnum_simulation_time_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_compound_fixnum_simulation_time_variable);
}

/* MAKE-COMPOUND-FIXNUM-SIMULATION-TIME-1 */
Object make_compound_fixnum_simulation_time_1()
{
    Object def_structure_compound_fixnum_simulation_time_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(184,56);
    def_structure_compound_fixnum_simulation_time_variable = 
	    ISVREF(Chain_of_available_compound_fixnum_simulation_times_vector,
	    IFIX(Current_thread_index));
    if (def_structure_compound_fixnum_simulation_time_variable) {
	svref_arg_1 = 
		Chain_of_available_compound_fixnum_simulation_times_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_compound_fixnum_simulation_time_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_compound_fixnum_simulation_time_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_compound_fixnum_simulation_time_g2_struct;
    }
    else
	def_structure_compound_fixnum_simulation_time_variable = 
		make_permanent_compound_fixnum_simulation_time_structure_internal();
    inline_note_allocate_cons(def_structure_compound_fixnum_simulation_time_variable,
	    Nil);
    ISVREF(def_structure_compound_fixnum_simulation_time_variable,
	    (SI_Long)1L) = FIX((SI_Long)0L);
    ISVREF(def_structure_compound_fixnum_simulation_time_variable,
	    (SI_Long)2L) = FIX((SI_Long)0L);
    return VALUES_1(def_structure_compound_fixnum_simulation_time_variable);
}

/* RECLAIM-COMPOUND-FIXNUM-SIMULATION-TIME */
Object reclaim_compound_fixnum_simulation_time(compound_time_qm)
    Object compound_time_qm;
{
    x_note_fn_call(184,57);
    if (compound_time_qm && SIMPLE_VECTOR_P(compound_time_qm) && 
	    EQ(ISVREF(compound_time_qm,(SI_Long)0L),
	    Qg2_defstruct_structure_name_compound_fixnum_simulation_time_g2_struct))
	return real_reclaim_compound_fixnum_simulation_time_1(compound_time_qm);
    else
	return VALUES_1(Nil);
}

Object The_type_description_of_model_runtime_info = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_model_runtime_infos, Qchain_of_available_model_runtime_infos);

DEFINE_VARIABLE_WITH_SYMBOL(Model_runtime_info_count, Qmodel_runtime_info_count);

Object Chain_of_available_model_runtime_infos_vector = UNBOUND;

/* MODEL-RUNTIME-INFO-STRUCTURE-MEMORY-USAGE */
Object model_runtime_info_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(184,58);
    temp = Model_runtime_info_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)39L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-MODEL-RUNTIME-INFO-COUNT */
Object outstanding_model_runtime_info_count()
{
    Object def_structure_model_runtime_info_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(184,59);
    gensymed_symbol = IFIX(Model_runtime_info_count);
    def_structure_model_runtime_info_variable = 
	    Chain_of_available_model_runtime_infos;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_model_runtime_info_variable))
	goto end_loop;
    def_structure_model_runtime_info_variable = 
	    ISVREF(def_structure_model_runtime_info_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-MODEL-RUNTIME-INFO-1 */
Object reclaim_model_runtime_info_1(model_runtime_info)
    Object model_runtime_info;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(184,60);
    inline_note_reclaim_cons(model_runtime_info,Nil);
    structure_being_reclaimed = model_runtime_info;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_compound_fixnum_simulation_time(ISVREF(model_runtime_info,
	      (SI_Long)4L));
      SVREF(model_runtime_info,FIX((SI_Long)4L)) = Nil;
      reclaim_compound_fixnum_simulation_time(ISVREF(model_runtime_info,
	      (SI_Long)5L));
      SVREF(model_runtime_info,FIX((SI_Long)5L)) = Nil;
      reclaim_compound_fixnum_simulation_time(ISVREF(model_runtime_info,
	      (SI_Long)6L));
      SVREF(model_runtime_info,FIX((SI_Long)6L)) = Nil;
      reclaim_compound_fixnum_simulation_time(ISVREF(model_runtime_info,
	      (SI_Long)7L));
      SVREF(model_runtime_info,FIX((SI_Long)7L)) = Nil;
      reclaim_compound_fixnum_simulation_time(ISVREF(model_runtime_info,
	      (SI_Long)8L));
      SVREF(model_runtime_info,FIX((SI_Long)8L)) = Nil;
      reclaim_compound_fixnum_simulation_time(ISVREF(model_runtime_info,
	      (SI_Long)9L));
      SVREF(model_runtime_info,FIX((SI_Long)9L)) = Nil;
      reclaim_installation_set(ISVREF(model_runtime_info,(SI_Long)19L));
      SVREF(model_runtime_info,FIX((SI_Long)19L)) = Nil;
      reclaim_installation_set(ISVREF(model_runtime_info,(SI_Long)20L));
      SVREF(model_runtime_info,FIX((SI_Long)20L)) = Nil;
      reclaim_installation_set(ISVREF(model_runtime_info,(SI_Long)21L));
      SVREF(model_runtime_info,FIX((SI_Long)21L)) = Nil;
      reclaim_rederive_set(ISVREF(model_runtime_info,(SI_Long)24L));
      SVREF(model_runtime_info,FIX((SI_Long)24L)) = Nil;
      reclaim_external_set(ISVREF(model_runtime_info,(SI_Long)26L));
      SVREF(model_runtime_info,FIX((SI_Long)26L)) = Nil;
      clear_variables_that_need_simulated_values_1(ISVREF(model_runtime_info,
	      (SI_Long)30L));
      SVREF(model_runtime_info,FIX((SI_Long)30L)) = Nil;
      clear_tainted_variables_1(1,ISVREF(model_runtime_info,(SI_Long)32L));
      SVREF(model_runtime_info,FIX((SI_Long)32L)) = Nil;
      reclaim_compound_fixnum_simulation_time(ISVREF(model_runtime_info,
	      (SI_Long)33L));
      SVREF(model_runtime_info,FIX((SI_Long)33L)) = Nil;
      reclaim_simulate_list_1(ISVREF(model_runtime_info,(SI_Long)37L));
      SVREF(model_runtime_info,FIX((SI_Long)37L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_model_runtime_infos_vector,
	    IFIX(Current_thread_index));
    SVREF(model_runtime_info,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_model_runtime_infos_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = model_runtime_info;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-MODEL-RUNTIME-INFO */
Object reclaim_structure_for_model_runtime_info(model_runtime_info)
    Object model_runtime_info;
{
    x_note_fn_call(184,61);
    return reclaim_model_runtime_info_1(model_runtime_info);
}

static Object Qg2_defstruct_structure_name_model_runtime_info_g2_struct;  /* g2-defstruct-structure-name::model-runtime-info-g2-struct */

/* MAKE-PERMANENT-MODEL-RUNTIME-INFO-STRUCTURE-INTERNAL */
Object make_permanent_model_runtime_info_structure_internal()
{
    Object def_structure_model_runtime_info_variable;
    Object defstruct_g2_model_runtime_info_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(184,62);
    def_structure_model_runtime_info_variable = Nil;
    atomic_incff_symval(Qmodel_runtime_info_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_model_runtime_info_variable = Nil;
	gensymed_symbol = (SI_Long)39L;
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
	defstruct_g2_model_runtime_info_variable = the_array;
	SVREF(defstruct_g2_model_runtime_info_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_model_runtime_info_g2_struct;
	def_structure_model_runtime_info_variable = 
		defstruct_g2_model_runtime_info_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_model_runtime_info_variable);
}

/* MAKE-MODEL-RUNTIME-INFO-1 */
Object make_model_runtime_info_1()
{
    Object def_structure_model_runtime_info_variable, temp, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(184,63);
    def_structure_model_runtime_info_variable = 
	    ISVREF(Chain_of_available_model_runtime_infos_vector,
	    IFIX(Current_thread_index));
    if (def_structure_model_runtime_info_variable) {
	temp = Chain_of_available_model_runtime_infos_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_model_runtime_info_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_model_runtime_info_g2_struct;
    }
    else
	def_structure_model_runtime_info_variable = 
		make_permanent_model_runtime_info_structure_internal();
    inline_note_allocate_cons(def_structure_model_runtime_info_variable,Nil);
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)3L)) = Nil;
    temp = make_compound_fixnum_simulation_time_1();
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)4L)) = temp;
    temp = make_compound_fixnum_simulation_time_1();
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)5L)) = temp;
    temp = make_compound_fixnum_simulation_time_1();
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)6L)) = temp;
    temp = make_compound_fixnum_simulation_time_1();
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)7L)) = temp;
    temp = make_compound_fixnum_simulation_time_1();
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)8L)) = temp;
    temp = make_compound_fixnum_simulation_time_1();
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)9L)) = temp;
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)13L)) = Nil;
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)14L)) = Nil;
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)15L)) = Nil;
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)16L)) = Nil;
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)17L)) = Nil;
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)18L)) = Nil;
    temp = make_installation_set();
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)19L)) = temp;
    temp = make_installation_set();
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)20L)) = temp;
    temp = make_installation_set();
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)21L)) = temp;
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)22L)) = Nil;
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)23L)) = Nil;
    temp = make_rederive_set();
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)24L)) = temp;
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)25L)) = Nil;
    temp = make_external_set();
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)26L)) = temp;
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)27L)) = Nil;
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)28L)) = Nil;
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)29L)) = Nil;
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)30L)) = Nil;
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)31L)) = Nil;
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)32L)) = Nil;
    temp = make_compound_fixnum_simulation_time_1();
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)33L)) = temp;
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)34L)) = Nil;
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)35L)) = Nil;
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)36L)) = Nil;
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)37L)) = Nil;
    SVREF(def_structure_model_runtime_info_variable,FIX((SI_Long)38L)) = Nil;
    return VALUES_1(def_structure_model_runtime_info_variable);
}

/* INITIALIZE-MAIN-MODEL-RUNTIME-INFO */
Object initialize_main_model_runtime_info()
{
    x_note_fn_call(184,64);
    return make_model_runtime_info_1();
}

/* INITIALIZE-MODEL-RUNTIME-INFO */
Object initialize_model_runtime_info varargs_1(int, n)
{
    Object model_definition_qm, model_runtime_info, svref_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(184,65);
    INIT_ARGS_nonrelocating();
    model_definition_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    model_runtime_info = make_model_runtime_info_1();
    svref_new_value = model_definition_qm;
    if (svref_new_value);
    else
	svref_new_value = Frame_being_made;
    SVREF(model_runtime_info,FIX((SI_Long)28L)) = svref_new_value;
    return VALUES_1(model_runtime_info);
}

DEFINE_VARIABLE_WITH_SYMBOL(Main_model_runtime_info, Qmain_model_runtime_info);

DEFINE_VARIABLE_WITH_SYMBOL(Current_model_runtime_info_qm, Qcurrent_model_runtime_info_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Current_model_definition_qm, Qcurrent_model_definition_qm);

static Object Qrk4;                /* rk4 */

static Object Qintegration_algorithm;  /* integration-algorithm */

/* PUT-INTEGRATION-ALGORITHM */
Object put_integration_algorithm(frame,new_value,gensymed_symbol)
    Object frame, new_value, gensymed_symbol;
{
    Object svref_arg_1;

    x_note_fn_call(184,66);
    if (EQ(ISVREF(frame,(SI_Long)23L),Qrk4) &&  !EQ(new_value,Qrk4) && 
	    EQ(frame,Simulation_parameters)) {
	svref_arg_1 = Main_model_runtime_info;
	SVREF(svref_arg_1,FIX((SI_Long)3L)) = Nil;
    }
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,Qintegration_algorithm);
    return VALUES_1(SVREF(frame,FIX((SI_Long)23L)) = new_value);
}

/* ADD-VARIABLE-TO-SIMULATION-MODEL */
Object add_variable_to_simulation_model(variable_or_parameter)
    Object variable_or_parameter;
{
    x_note_fn_call(184,67);
    if (continuous_state_variable_p(variable_or_parameter))
	add_to_installation_set(ISVREF(Current_model_runtime_info_qm,
		(SI_Long)19L),variable_or_parameter);
    else if (discrete_state_variable_p(variable_or_parameter))
	add_to_installation_set(ISVREF(Current_model_runtime_info_qm,
		(SI_Long)20L),variable_or_parameter);
    else if (dependent_variable_p(variable_or_parameter))
	add_to_installation_set(ISVREF(Current_model_runtime_info_qm,
		(SI_Long)21L),variable_or_parameter);
    return add_model_which_has_something_to_simulate(Current_model_runtime_info_qm);
}

/* ADD-EXTERNALLY-SIMULATED-ENTITY-TO-SIMULATION-MODEL */
Object add_externally_simulated_entity_to_simulation_model(entity)
    Object entity;
{
    x_note_fn_call(184,68);
    add_to_external_set(ISVREF(Current_model_runtime_info_qm,(SI_Long)26L),
	    entity);
    return add_model_which_has_something_to_simulate(Current_model_runtime_info_qm);
}

/* REMOVE-VARIABLE-FROM-SIMULATION-MODEL */
Object remove_variable_from_simulation_model(variable_or_parameter)
    Object variable_or_parameter;
{
    x_note_fn_call(184,69);
    delete_from_installation_set(variable_or_parameter);
    return update_anything_to_simulate_in_model_qm(Current_model_runtime_info_qm);
}

/* REMOVE-EXTERNALLY-SIMULATED-ENTITY-FROM-SIMULATION-MODEL */
Object remove_externally_simulated_entity_from_simulation_model(entity)
    Object entity;
{
    x_note_fn_call(184,70);
    delete_from_external_set(entity);
    return update_anything_to_simulate_in_model_qm(Current_model_runtime_info_qm);
}

/* FOR-EACH-VARIABLE-IN-MODEL */
Object for_each_variable_in_model(function_for_variable)
    Object function_for_variable;
{
    x_note_fn_call(184,71);
    for_each_element_in_installation_set(ISVREF(Current_model_runtime_info_qm,
	    (SI_Long)19L),function_for_variable);
    for_each_element_in_installation_set(ISVREF(Current_model_runtime_info_qm,
	    (SI_Long)20L),function_for_variable);
    return for_each_element_in_installation_set(ISVREF(Current_model_runtime_info_qm,
	    (SI_Long)21L),function_for_variable);
}

DEFINE_VARIABLE_WITH_SYMBOL(Within_simulate_until_consistent_with_gensym_time, Qwithin_simulate_until_consistent_with_gensym_time);

DEFINE_VARIABLE_WITH_SYMBOL(Initializing_simulator_qm, Qinitializing_simulator_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Initializing_state_variables_qm, Qinitializing_state_variables_qm);

static Object Qsimulation_error_catch;  /* simulation-error-catch */

/* SIGNAL-SIMULATION-ERROR-AFTER-STACK-EVAL */
Object signal_simulation_error_after_stack_eval()
{
    Object svref_arg_1;
    Object result;

    x_note_fn_call(184,72);
    if (ISVREF(Current_model_runtime_info_qm,(SI_Long)12L)) {
	abort_procedure_invocation(1,ISVREF(Current_model_runtime_info_qm,
		(SI_Long)12L));
	svref_arg_1 = Current_model_runtime_info_qm;
	SVREF(svref_arg_1,FIX((SI_Long)12L)) = Nil;
    }
    if (Within_simulate_until_consistent_with_gensym_time || 
	    Initializing_simulator_qm) {
	result = VALUES_1(T);
	THROW(Qsimulation_error_catch,result);
    }
    else
	return VALUES_1(Nil);
}

static Object Qpost_simulation_warning_for_no_value;  /* post-simulation-warning-for-no-value */

static Object string_constant;     /* "Simulation problem.  Can't get value for ~NF." */

/* POST-SIMULATION-WARNING-FOR-NO-VALUE */
Object post_simulation_warning_for_no_value(variable)
    Object variable;
{
    Object svref_arg_1;
    Object result;

    x_note_fn_call(184,73);
    svref_arg_1 = Current_model_runtime_info_qm;
    SVREF(svref_arg_1,FIX((SI_Long)11L)) = 
	    Qpost_simulation_warning_for_no_value;
    if (ISVREF(Current_model_runtime_info_qm,(SI_Long)12L)) {
	abort_procedure_invocation(1,ISVREF(Current_model_runtime_info_qm,
		(SI_Long)12L));
	svref_arg_1 = Current_model_runtime_info_qm;
	SVREF(svref_arg_1,FIX((SI_Long)12L)) = Nil;
    }
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	give_warning_1(3,FIX((SI_Long)1L),string_constant,variable);
    if (Within_simulate_until_consistent_with_gensym_time || 
	    Initializing_simulator_qm) {
	result = VALUES_1(T);
	THROW(Qsimulation_error_catch,result);
    }
    else
	return VALUES_1(Nil);
}

static Object Qsimulation_type_error;  /* simulation-type-error */

static Object string_constant_1;   /* "An attempt to put the value ~s into ~NF ~
				    *      which has type ~NT failed because of type mismatch."
				    */

/* SIMULATION-TYPE-ERROR */
Object simulation_type_error(variable,value)
    Object variable, value;
{
    Object svref_arg_1;
    Object result;

    x_note_fn_call(184,74);
    svref_arg_1 = Current_model_runtime_info_qm;
    SVREF(svref_arg_1,FIX((SI_Long)11L)) = Qsimulation_type_error;
    if (ISVREF(Current_model_runtime_info_qm,(SI_Long)12L)) {
	abort_procedure_invocation(1,ISVREF(Current_model_runtime_info_qm,
		(SI_Long)12L));
	svref_arg_1 = Current_model_runtime_info_qm;
	SVREF(svref_arg_1,FIX((SI_Long)12L)) = Nil;
    }
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	give_warning_1(5,FIX((SI_Long)1L),string_constant_1,EQ(value,
		Simulation_no_value) ? Qno_value : value,variable,
		type_specification_of_variable_or_parameter_value(variable));
    if (Within_simulate_until_consistent_with_gensym_time || 
	    Initializing_simulator_qm) {
	result = VALUES_1(T);
	THROW(Qsimulation_error_catch,result);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_2;   /* "Simulation problem.  The initialization expression \"the current parameter value\" ~
				    *      is not valid because ~NF is not a parameter."
				    */

/* POST-SIMULATION-WARNING-FOR-NOT-PARAMETER */
Object post_simulation_warning_for_not_parameter(variable)
    Object variable;
{
    x_note_fn_call(184,75);
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	return give_warning_1(3,FIX((SI_Long)1L),string_constant_2,variable);
    else
	return VALUES_1(Nil);
}

static Object Qrecord_block_for_tformat;  /* record-block-for-tformat */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_3;   /* "An attempt to put the value ~s into ~NF ~
				    *           which has type ~NT failed because of type mismatch."
				    */

/* SIMULATION-TYPE-ERROR-FROM-WITHIN-OR-WITHOUT-STACK-EVAL */
Object simulation_type_error_from_within_or_without_stack_eval(variable,value)
    Object variable, value;
{
    Object svref_arg_1, top_of_stack, text_string, snapshots;
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object message_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(7);

    x_note_fn_call(184,76);
    if (within_stack_eval_p()) {
	if (SIMPLE_VECTOR_P(Current_model_runtime_info_qm) && 
		EQ(ISVREF(Current_model_runtime_info_qm,(SI_Long)0L),
		Qg2_defstruct_structure_name_model_runtime_info_g2_struct)) {
	    svref_arg_1 = Current_model_runtime_info_qm;
	    SVREF(svref_arg_1,FIX((SI_Long)11L)) = Qsimulation_type_error;
	}
	top_of_stack = Cached_top_of_stack;
	text_string = Nil;
	snapshots = Nil;
	snapshots_of_related_blocks = Nil;
	note_blocks_in_tformat = SYMBOL_FUNCTION(Qrecord_block_for_tformat);
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
		      tformat(4,string_constant_3,EQ(value,
			      Simulation_no_value) ? Qno_value : value,
			      variable,
			      type_specification_of_variable_or_parameter_value(variable));
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
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
    else
	return simulation_type_error(variable,value);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_simulation_runtime_structure, Qcurrent_simulation_runtime_structure);

DEFINE_VARIABLE_WITH_SYMBOL(Dont_backward_chain_in_sim_eval_qm, Qdont_backward_chain_in_sim_eval_qm);

static Object Qunknown_encountered;  /* unknown-encountered */

static Object string_constant_4;   /* "~nw~%~%Exiting execution of this formula.  No value was computed for ~
				    *           ~NF, and simulation has been halted for its model."
				    */

static Object Qsimulation_stack_error;  /* simulation-stack-error */

/* HANDLE-SIMULATOR-STACK-ERROR */
Object handle_simulator_stack_error(variable_or_parameter,
	    computation_frame,computation_component_particulars,error_1,
	    error_level,error_text_string,current_program_counter,
	    local_stack,top_of_stack,byte_code_body,local_var_vector)
    Object variable_or_parameter, computation_frame;
    Object computation_component_particulars, error_1, error_level;
    Object error_text_string, current_program_counter, local_stack;
    Object top_of_stack, byte_code_body, local_var_vector;
{
    Object svref_arg_1, standard_message, local_var_vector_qm;
    Object dont_backward_chain_in_sim_eval_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(184,77);
    if (EQ(ISVREF(Current_model_runtime_info_qm,(SI_Long)11L),
	    Qunknown_encountered)) {
	reclaim_error_text(error_text_string);
	svref_arg_1 = Current_model_runtime_info_qm;
	SVREF(svref_arg_1,FIX((SI_Long)11L)) = Nil;
    }
    else {
	standard_message = generate_standard_error_message(error_1,
		error_text_string,computation_frame,
		computation_component_particulars,variable_or_parameter,
		byte_code_body,ISVREF(byte_code_body,(SI_Long)3L),
		current_program_counter,local_stack,top_of_stack,
		local_var_vector);
	if (registered_and_active_default_error_handler_p() && 
		invoke_user_defined_default_error_handler(error_1,
		standard_message));
	else {
	    Suppress_warning_message_header_qm = T;
	    if (FIXNUM_LE(error_level,Warning_message_level))
		give_warning_1(4,error_level,string_constant_4,
			standard_message,variable_or_parameter);
	    Suppress_warning_message_header_qm = Nil;
	    reclaim_error_text(standard_message);
	}
	reclaim_error_text(error_text_string);
	if ( !TRUEP(ISVREF(Current_model_runtime_info_qm,(SI_Long)11L))) {
	    svref_arg_1 = Current_model_runtime_info_qm;
	    SVREF(svref_arg_1,FIX((SI_Long)11L)) = Qsimulation_stack_error;
	}
    }
    if (Current_computation_instance && Current_simulation_runtime_structure) {
	local_var_vector_qm = ISVREF(Current_simulation_runtime_structure,
		(SI_Long)20L);
	if (local_var_vector_qm) {
	    dont_backward_chain_in_sim_eval_qm = T;
	    PUSH_SPECIAL_WITH_SYMBOL(Dont_backward_chain_in_sim_eval_qm,Qdont_backward_chain_in_sim_eval_qm,dont_backward_chain_in_sim_eval_qm,
		    0);
	      Current_computation_instance = Nil;
	      result = exit_last_simulation_variable_context(Nil,
		      local_var_vector_qm);
	    POP_SPECIAL();
	    return result;
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Minimum_simulation_time_increment, Qminimum_simulation_time_increment);

/* INITIALIZE-MINIMUM-SIMULATION-TIME-INCREMENT */
Object initialize_minimum_simulation_time_increment()
{
    x_note_fn_call(184,78);
    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(1.0 / 100000.0));
}

DEFINE_VARIABLE_WITH_SYMBOL(Simulation_time_managed_float, Qsimulation_time_managed_float);

/* INITIALIZE-SIMULATION-TIME-MANAGED-FLOAT */
Object initialize_simulation_time_managed_float()
{
    x_note_fn_call(184,79);
    return allocate_managed_float_box();
}

DEFINE_VARIABLE_WITH_SYMBOL(Number_of_variables_to_process_at_a_time, Qnumber_of_variables_to_process_at_a_time);

DEFINE_VARIABLE_WITH_SYMBOL(Task_for_display_of_simulation_time, Qtask_for_display_of_simulation_time);

DEFINE_VARIABLE_WITH_SYMBOL(Ran_out_of_time_qm, Qran_out_of_time_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Number_of_simulated_variables_processed, Qnumber_of_simulated_variables_processed);

/* INITIALIZE-COMPOUND-SIMULATION-TIME */
Object initialize_compound_simulation_time()
{
    x_note_fn_call(184,80);
    return make_compound_fixnum_simulation_time_1();
}

DEFINE_VARIABLE_WITH_SYMBOL(Simulation_time_accumulator, Qsimulation_time_accumulator);

DEFINE_VARIABLE_WITH_SYMBOL(Synchronous_model_queue, Qsynchronous_model_queue);

DEFINE_VARIABLE_WITH_SYMBOL(As_fast_as_possible_model_queue, Qas_fast_as_possible_model_queue);

DEFINE_VARIABLE_WITH_SYMBOL(Current_model_queue_qm, Qcurrent_model_queue_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Processing_as_fast_as_possible_models_qm, Qprocessing_as_fast_as_possible_models_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Simulator_initialized_as_data_server_qm, Qsimulator_initialized_as_data_server_qm);

Object The_type_description_of_model_queue = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_model_queues, Qchain_of_available_model_queues);

DEFINE_VARIABLE_WITH_SYMBOL(Model_queue_count, Qmodel_queue_count);

Object Chain_of_available_model_queues_vector = UNBOUND;

/* MODEL-QUEUE-STRUCTURE-MEMORY-USAGE */
Object model_queue_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(184,81);
    temp = Model_queue_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)7L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-MODEL-QUEUE-COUNT */
Object outstanding_model_queue_count()
{
    Object def_structure_model_queue_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(184,82);
    gensymed_symbol = IFIX(Model_queue_count);
    def_structure_model_queue_variable = Chain_of_available_model_queues;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_model_queue_variable))
	goto end_loop;
    def_structure_model_queue_variable = 
	    ISVREF(def_structure_model_queue_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-MODEL-QUEUE-1 */
Object reclaim_model_queue_1(model_queue)
    Object model_queue;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(184,83);
    inline_note_reclaim_cons(model_queue,Nil);
    structure_being_reclaimed = model_queue;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_compound_fixnum_simulation_time(ISVREF(model_queue,(SI_Long)3L));
      SVREF(model_queue,FIX((SI_Long)3L)) = Nil;
      reclaim_compound_fixnum_simulation_time(ISVREF(model_queue,(SI_Long)4L));
      SVREF(model_queue,FIX((SI_Long)4L)) = Nil;
      reclaim_compound_fixnum_simulation_time(ISVREF(model_queue,(SI_Long)6L));
      SVREF(model_queue,FIX((SI_Long)6L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_model_queues_vector,
	    IFIX(Current_thread_index));
    SVREF(model_queue,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_model_queues_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = model_queue;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-MODEL-QUEUE */
Object reclaim_structure_for_model_queue(model_queue)
    Object model_queue;
{
    x_note_fn_call(184,84);
    return reclaim_model_queue_1(model_queue);
}

static Object Qg2_defstruct_structure_name_model_queue_g2_struct;  /* g2-defstruct-structure-name::model-queue-g2-struct */

/* MAKE-PERMANENT-MODEL-QUEUE-STRUCTURE-INTERNAL */
Object make_permanent_model_queue_structure_internal()
{
    Object def_structure_model_queue_variable;
    Object defstruct_g2_model_queue_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(184,85);
    def_structure_model_queue_variable = Nil;
    atomic_incff_symval(Qmodel_queue_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_model_queue_variable = Nil;
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
	defstruct_g2_model_queue_variable = the_array;
	SVREF(defstruct_g2_model_queue_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_model_queue_g2_struct;
	def_structure_model_queue_variable = defstruct_g2_model_queue_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_model_queue_variable);
}

/* MAKE-MODEL-QUEUE-1 */
Object make_model_queue_1()
{
    Object def_structure_model_queue_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(184,86);
    def_structure_model_queue_variable = 
	    ISVREF(Chain_of_available_model_queues_vector,
	    IFIX(Current_thread_index));
    if (def_structure_model_queue_variable) {
	svref_arg_1 = Chain_of_available_model_queues_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_model_queue_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_model_queue_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_model_queue_g2_struct;
    }
    else
	def_structure_model_queue_variable = 
		make_permanent_model_queue_structure_internal();
    inline_note_allocate_cons(def_structure_model_queue_variable,Nil);
    SVREF(def_structure_model_queue_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_model_queue_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_model_queue_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_model_queue_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_model_queue_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_model_queue_variable,FIX((SI_Long)6L)) = Nil;
    return VALUES_1(def_structure_model_queue_variable);
}

/* INITIALIZE-MODEL-QUEUE */
Object initialize_model_queue()
{
    x_note_fn_call(184,87);
    return make_model_queue_1();
}

/* RECLAIM-MODEL-QUEUE-FUNCTION */
Object reclaim_model_queue_function(a_model_queue)
    Object a_model_queue;
{
    x_note_fn_call(184,88);
    return reclaim_model_queue_1(a_model_queue);
}

/* ADD-MODEL-TO-SIMULATION */
Object add_model_to_simulation(model_runtime_info)
    Object model_runtime_info;
{
    Object tail, head, model_runtime_info_in_queue, temp, svref_new_value;

    x_note_fn_call(184,89);
    tail = Nil;
    head = ISVREF(Current_model_queue_qm,(SI_Long)1L);
    model_runtime_info_in_queue = Nil;
  next_loop:
    model_runtime_info_in_queue = CAR(head);
    if ( !TRUEP(head))
	goto end_loop;
    if (EQ(model_runtime_info_in_queue,model_runtime_info))
	return VALUES_0();
    tail = head;
    head = CDR(head);
    goto next_loop;
  end_loop:
    if ( !TRUEP(tail)) {
	temp = Current_model_queue_qm;
	svref_new_value = simulate_cons_1(model_runtime_info,Nil);
	SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
    }
    else {
	temp = simulate_cons_1(model_runtime_info,Nil);
	M_CDR(tail) = temp;
    }
    return VALUES_1(Qnil);
}

/* REMOVE-MODEL-FROM-SIMULATION */
Object remove_model_from_simulation(model_runtime_info)
    Object model_runtime_info;
{
    Object temp, models_to_shutdown, model_to_shutdown, ab_loop_list_;
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, temp_1;
    Object temp_2;

    x_note_fn_call(184,90);
    SVREF(model_runtime_info,FIX((SI_Long)29L)) = Nil;
    if (EQ(model_runtime_info,Main_model_runtime_info)) {
	temp = Current_model_queue_qm;
	SVREF(temp,FIX((SI_Long)2L)) = Nil;
	temp = Current_model_queue_qm;
	SVREF(temp,FIX((SI_Long)5L)) = Nil;
	models_to_shutdown = 
		copy_list_using_simulate_conses_1(ISVREF(Current_model_queue_qm,
		(SI_Long)1L));
	model_to_shutdown = Nil;
	ab_loop_list_ = models_to_shutdown;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	model_to_shutdown = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !EQ(model_to_shutdown,model_runtime_info))
	    shutdown_simulator(2,model_to_shutdown,
		    ISVREF(model_runtime_info,(SI_Long)28L));
	goto next_loop;
      end_loop:;
	reclaim_simulate_list_1(models_to_shutdown);
	gensymed_symbol = model_runtime_info;
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = ISVREF(Current_model_queue_qm,(SI_Long)1L);
      next_loop_1:
	if ( !TRUEP(gensymed_symbol_2))
	    goto end_loop_1;
	if (EQ(CAR(gensymed_symbol_2),gensymed_symbol)) {
	    if (gensymed_symbol_1) {
		temp = CDR(gensymed_symbol_2);
		M_CDR(gensymed_symbol_1) = temp;
	    }
	    else {
		temp = Current_model_queue_qm;
		temp_1 = CDR(gensymed_symbol_2);
		SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	    }
	    temp_2 = CAR(gensymed_symbol_2);
	    inline_note_reclaim_cons(gensymed_symbol_2,Qsimulate);
	    if (ISVREF(Available_simulate_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_simulate_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = gensymed_symbol_2;
		temp = Available_simulate_conses_tail_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = gensymed_symbol_2;
	    }
	    else {
		temp = Available_simulate_conses_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = gensymed_symbol_2;
		temp = Available_simulate_conses_tail_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = gensymed_symbol_2;
	    }
	    M_CDR(gensymed_symbol_2) = Nil;
	    return VALUES_1(temp_2);
	}
	gensymed_symbol_1 = gensymed_symbol_2;
	gensymed_symbol_2 = CDR(gensymed_symbol_2);
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
    else {
	temp_2 = ISVREF(Current_model_queue_qm,(SI_Long)2L);
	if (EQ(model_runtime_info,CAR(temp_2))) {
	    temp_2 = ISVREF(Current_model_queue_qm,(SI_Long)2L);
	    if ( !TRUEP(CDR(temp_2))) {
		initialize_current_model_queue();
		temp_2 = ISVREF(Current_model_queue_qm,(SI_Long)2L);
		if (EQ(model_runtime_info,CAR(temp_2))) {
		    temp = Current_model_queue_qm;
		    temp_2 = ISVREF(Current_model_queue_qm,(SI_Long)2L);
		    temp_1 = CDR(temp_2);
		    SVREF(temp,FIX((SI_Long)2L)) = temp_1;
		}
	    }
	    else {
		temp = Current_model_queue_qm;
		temp_2 = ISVREF(Current_model_queue_qm,(SI_Long)2L);
		temp_1 = CDR(temp_2);
		SVREF(temp,FIX((SI_Long)2L)) = temp_1;
	    }
	}
	gensymed_symbol = model_runtime_info;
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = ISVREF(Current_model_queue_qm,(SI_Long)1L);
      next_loop_2:
	if ( !TRUEP(gensymed_symbol_2))
	    goto end_loop_2;
	if (EQ(CAR(gensymed_symbol_2),gensymed_symbol)) {
	    if (gensymed_symbol_1) {
		temp = CDR(gensymed_symbol_2);
		M_CDR(gensymed_symbol_1) = temp;
	    }
	    else {
		temp = Current_model_queue_qm;
		temp_1 = CDR(gensymed_symbol_2);
		SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	    }
	    temp_2 = CAR(gensymed_symbol_2);
	    inline_note_reclaim_cons(gensymed_symbol_2,Qsimulate);
	    if (ISVREF(Available_simulate_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_simulate_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = gensymed_symbol_2;
		temp = Available_simulate_conses_tail_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = gensymed_symbol_2;
	    }
	    else {
		temp = Available_simulate_conses_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = gensymed_symbol_2;
		temp = Available_simulate_conses_tail_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = gensymed_symbol_2;
	    }
	    M_CDR(gensymed_symbol_2) = Nil;
	    return VALUES_1(temp_2);
	}
	gensymed_symbol_1 = gensymed_symbol_2;
	gensymed_symbol_2 = CDR(gensymed_symbol_2);
	goto next_loop_2;
      end_loop_2:
	return VALUES_1(Qnil);
    }
}

/* INITIALIZE-CURRENT-MODEL-QUEUE */
Object initialize_current_model_queue()
{
    Object svref_arg_1, svref_new_value;

    x_note_fn_call(184,91);
    svref_arg_1 = Current_model_queue_qm;
    SVREF(svref_arg_1,FIX((SI_Long)5L)) = T;
    svref_arg_1 = Current_model_queue_qm;
    svref_new_value = ISVREF(Current_model_queue_qm,(SI_Long)1L);
    return VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)2L)) = svref_new_value);
}

/* ANY-MODELS-RUNNING-FUNCTION? */
Object any_models_running_function_qm()
{
    x_note_fn_call(184,92);
    return VALUES_1(ISVREF(Synchronous_model_queue,(SI_Long)1L));
}

/* ALL-MODELS-PAUSED? */
Object all_models_paused_qm(list_of_model_runtime_infos)
    Object list_of_model_runtime_infos;
{
    Object result_qm, runtime_info, ab_loop_list_;

    x_note_fn_call(184,93);
    result_qm = T;
    runtime_info = Nil;
    ab_loop_list_ = list_of_model_runtime_infos;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    runtime_info = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(result_qm))
	goto end_loop;
    if ( !TRUEP(model_paused_qm(runtime_info)))
	result_qm = Nil;
    goto next_loop;
  end_loop:;
    return VALUES_1(result_qm);
}

/* NEED-CALLS-TO-SIMULATE-UNTIL-CONSISTENT-WITH-GENSYM-TIME */
Object need_calls_to_simulate_until_consistent_with_gensym_time()
{
    Object temp;

    x_note_fn_call(184,94);
    temp = ISVREF(Simulation_parameters,(SI_Long)24L);
    return VALUES_1(temp);
}

/* SIMULATE-UNTIL-CONSISTENT-WITH-GENSYM-TIME */
Object simulate_until_consistent_with_gensym_time()
{
    Object code, number_of_simulated_variables_processed;
    Object current_computation_flags, processing_as_fast_as_possible_models_qm;
    char temp;
    Declare_special(3);
    Object result;

    x_note_fn_call(184,95);
    if (ISVREF(Simulation_parameters,(SI_Long)24L)) {
	code = M_CAR(M_CDR(Edit_type_alias_mapping));
	temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)4096L) != 
		(SI_Long)0L : TRUEP(Qnil);
	if (temp);
	else
	    temp = TRUEP(M_CAR(M_CDR(Cache_g1_semantics_graph)));
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	Inhibit_non_real_time_clock_ticks_qm = Nil;
	if ( !TRUEP(Simulator_initialized_as_data_server_qm)) {
	    initialize_simulator(0);
	    Simulator_initialized_as_data_server_qm = T;
	}
	number_of_simulated_variables_processed = FIX((SI_Long)0L);
	current_computation_flags = Current_computation_flags;
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		2);
	  PUSH_SPECIAL_WITH_SYMBOL(Number_of_simulated_variables_processed,Qnumber_of_simulated_variables_processed,number_of_simulated_variables_processed,
		  1);
	    Current_computation_flags = 
		    FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    processing_as_fast_as_possible_models_qm = T;
	    PUSH_SPECIAL_WITH_SYMBOL(Processing_as_fast_as_possible_models_qm,Qprocessing_as_fast_as_possible_models_qm,processing_as_fast_as_possible_models_qm,
		    0);
	      if (simulate_until_consistent_with_gensym_time_1(As_fast_as_possible_model_queue) 
		      && Inhibit_non_real_time_clock_ticks_qm) {
		  result = VALUES_1(T);
		  POP_SPECIAL();
		  POP_SPECIAL();
		  POP_SPECIAL();
		  goto end_simulate_until_consistent_with_gensym_time;
	      }
	    POP_SPECIAL();
	    if ( !TRUEP(ISVREF(As_fast_as_possible_model_queue,
		    (SI_Long)1L)) || 
		    all_models_paused_qm(ISVREF(As_fast_as_possible_model_queue,
		    (SI_Long)1L)))
		result = simulate_until_consistent_with_gensym_time_1(Synchronous_model_queue);
	    else
		result = VALUES_1(Nil);
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    else
	result = VALUES_1(T);
  end_simulate_until_consistent_with_gensym_time:
    return result;
}

static Object Qneeds_to_be_initialized;  /* needs-to-be-initialized */

static Object Qneeds_to_be_shutdown;  /* needs-to-be-shutdown */

static Object Qwaiting;            /* waiting */

/* SIMULATE-UNTIL-CONSISTENT-WITH-GENSYM-TIME-1 */
Object simulate_until_consistent_with_gensym_time_1(model_queue)
    Object model_queue;
{
    Object current_model_queue_qm, gensymed_symbol, integer_portion;
    Object micro_time, gensymed_symbol_1, gensymed_symbol_2, macro_time_1;
    Object micro_time_1, macro_time_2, micro_time_2, temp_2;
    Object ran_out_of_time_qm, model_consistent_or_waiting_qm;
    Object current_model_to_process, temp_3, svref_new_value;
    char temp;
    double arg, temp_1, arg_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(184,96);
    if (ISVREF(model_queue,(SI_Long)1L)) {
	current_model_queue_qm = model_queue;
	PUSH_SPECIAL_WITH_SYMBOL(Current_model_queue_qm,Qcurrent_model_queue_qm,current_model_queue_qm,
		1);
	  if ( !TRUEP(ISVREF(Current_model_queue_qm,(SI_Long)2L))) {
	      initialize_current_model_queue();
	      if (ISVREF(Current_model_queue_qm,(SI_Long)3L)) {
		  temp = TRUEP(Processing_as_fast_as_possible_models_qm);
		  if (temp);
		  else {
		      gensymed_symbol = ISVREF(Current_model_queue_qm,
			      (SI_Long)3L);
		      integer_portion = ISVREF(gensymed_symbol,(SI_Long)1L);
		      micro_time = ISVREF(gensymed_symbol,(SI_Long)2L);
		      arg = IFIX(micro_time) == (SI_Long)0L ? 
			      (double)IFIX(integer_portion) : 
			      (double)IFIX(integer_portion) + 
			      (double)IFIX(micro_time) / 100000.0;
		      temp_1 = 
			      DOUBLE_FLOAT_TO_DOUBLE(Seconds_from_1900_to_1970);
		      arg_1 = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L) 
			      - 
			      (DFLOAT_ISAREF_1(Gensym_base_time_as_managed_float,
			      (SI_Long)0L) - temp_1);
		      temp = arg < arg_1 &&  
			      !inline_nanp_for_comparison(arg) ?  
			      !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		  }
		  if (temp) {
		      gensymed_symbol = ISVREF(Current_model_queue_qm,
			      (SI_Long)3L);
		      gensymed_symbol_1 = ISVREF(Current_model_queue_qm,
			      (SI_Long)3L);
		      gensymed_symbol_2 = ISVREF(Current_model_queue_qm,
			      (SI_Long)4L);
		      macro_time_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
		      micro_time_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		      macro_time_2 = ISVREF(gensymed_symbol_2,(SI_Long)1L);
		      micro_time_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
		      if (IFIX(micro_time_2) != (SI_Long)0L) {
			  micro_time_1 = FIXNUM_ADD(micro_time_1,micro_time_2);
			  if (FIXNUM_GE(micro_time_1,
				  Fraction_modulus_of_compound_fixnum_simulation_time)) 
				      {
			      temp_2 = FIXNUM_MINUS(micro_time_1,
				      Fraction_modulus_of_compound_fixnum_simulation_time);
			      SVREF(gensymed_symbol,FIX((SI_Long)2L)) = temp_2;
			      macro_time_1 = FIXNUM_ADD1(macro_time_1);
			  }
			  else
			      SVREF(gensymed_symbol,FIX((SI_Long)2L)) = 
				      micro_time_1;
		      }
		      else {
			  if (SVREF(gensymed_symbol,FIX((SI_Long)2L)) = 
				  micro_time_1);
		      }
		      temp_2 = FIXNUM_ADD(macro_time_1,macro_time_2);
		      SVREF(gensymed_symbol,FIX((SI_Long)1L)) = temp_2;
		  }
	      }
	  }
	  ran_out_of_time_qm = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Ran_out_of_time_qm,Qran_out_of_time_qm,ran_out_of_time_qm,
		  0);
	    model_consistent_or_waiting_qm = Nil;
	    current_model_to_process = Nil;
	  next_loop:
	    temp_3 = ISVREF(Current_model_queue_qm,(SI_Long)2L);
	    current_model_to_process = CAR(temp_3);
	    if (EQ(ISVREF(current_model_to_process,(SI_Long)29L),
		    Qneeds_to_be_initialized)) {
		if (EQ(current_model_to_process,Main_model_runtime_info))
		    initialize_simulator(0);
		else
		    initialize_simulator(2,current_model_to_process,
			    ISVREF(current_model_to_process,(SI_Long)28L));
	    }
	    if (EQ(ISVREF(current_model_to_process,(SI_Long)29L),
		    Qneeds_to_be_initialized)) {
		result = VALUES_1(T);
		goto end_1;
	    }
	    else if (EQ(ISVREF(current_model_to_process,(SI_Long)29L),
		    Qneeds_to_be_shutdown)) {
		if (EQ(current_model_to_process,Main_model_runtime_info))
		    shutdown_simulator(0);
		else
		    shutdown_simulator(2,current_model_to_process,
			    ISVREF(current_model_to_process,(SI_Long)28L));
		if ( !TRUEP(ISVREF(Current_model_queue_qm,(SI_Long)2L))) {
		    result = VALUES_1(T);
		    goto end_1;
		}
	    }
	    else {
		if (model_paused_qm(current_model_to_process)) {
		    result = VALUES_1(T);
		    goto end_1;
		}
		if (time_slice_expired_p()) {
		    result = VALUES_1(Nil);
		    goto end_1;
		}
		model_consistent_or_waiting_qm = 
			simulate_model_until_consistent(current_model_to_process);
		if ( !TRUEP(model_consistent_or_waiting_qm)) {
		    result = VALUES_1(Nil);
		    goto end_1;
		}
		else if (EQ(model_consistent_or_waiting_qm,Qwaiting) &&  
			!TRUEP(dont_wait_for_model_to_finish_function_qm(current_model_to_process))) 
			    {
		    Inhibit_non_real_time_clock_ticks_qm = T;
		    result = VALUES_1(T);
		    goto end_1;
		}
		else {
		    temp_2 = Current_model_queue_qm;
		    temp_3 = ISVREF(Current_model_queue_qm,(SI_Long)2L);
		    svref_new_value = CDR(temp_3);
		    SVREF(temp_2,FIX((SI_Long)2L)) = svref_new_value;
		    if ( !EQ(model_consistent_or_waiting_qm,Qwaiting)) {
			temp_2 = Current_model_queue_qm;
			SVREF(temp_2,FIX((SI_Long)5L)) = Nil;
		    }
		    if ( !TRUEP(ISVREF(Current_model_queue_qm,(SI_Long)2L))) {
			if (ISVREF(Current_model_queue_qm,(SI_Long)5L)) {
			    Inhibit_non_real_time_clock_ticks_qm = T;
			    result = VALUES_1(T);
			    goto end_1;
			}
			temp = TRUEP(Processing_as_fast_as_possible_models_qm);
			if (temp);
			else {
			    gensymed_symbol = 
				    ISVREF(Current_model_queue_qm,(SI_Long)3L);
			    integer_portion = ISVREF(gensymed_symbol,
				    (SI_Long)1L);
			    micro_time = ISVREF(gensymed_symbol,(SI_Long)2L);
			    arg = IFIX(micro_time) == (SI_Long)0L ? 
				    (double)IFIX(integer_portion) : 
				    (double)IFIX(integer_portion) + 
				    (double)IFIX(micro_time) / 100000.0;
			    temp_1 = 
				    DOUBLE_FLOAT_TO_DOUBLE(Seconds_from_1900_to_1970);
			    arg_1 = DFLOAT_ISAREF_1(Current_g2_time,
				    (SI_Long)0L) - 
				    (DFLOAT_ISAREF_1(Gensym_base_time_as_managed_float,
				    (SI_Long)0L) - temp_1);
			    temp = arg < arg_1 &&  
				    !inline_nanp_for_comparison(arg) ?  
				    !inline_nanp_for_comparison(arg_1) : 
				    TRUEP(Qnil);
			}
			if (temp) {
			    gensymed_symbol = 
				    ISVREF(Current_model_queue_qm,(SI_Long)3L);
			    gensymed_symbol_1 = 
				    ISVREF(Current_model_queue_qm,(SI_Long)3L);
			    gensymed_symbol_2 = 
				    ISVREF(Current_model_queue_qm,(SI_Long)4L);
			    macro_time_1 = ISVREF(gensymed_symbol_1,
				    (SI_Long)1L);
			    micro_time_1 = ISVREF(gensymed_symbol_1,
				    (SI_Long)2L);
			    macro_time_2 = ISVREF(gensymed_symbol_2,
				    (SI_Long)1L);
			    micro_time_2 = ISVREF(gensymed_symbol_2,
				    (SI_Long)2L);
			    if (IFIX(micro_time_2) != (SI_Long)0L) {
				micro_time_1 = FIXNUM_ADD(micro_time_1,
					micro_time_2);
				if (FIXNUM_GE(micro_time_1,
					Fraction_modulus_of_compound_fixnum_simulation_time)) 
					    {
				    temp_2 = FIXNUM_MINUS(micro_time_1,
					    Fraction_modulus_of_compound_fixnum_simulation_time);
				    SVREF(gensymed_symbol,
					    FIX((SI_Long)2L)) = temp_2;
				    macro_time_1 = FIXNUM_ADD1(macro_time_1);
				}
				else
				    SVREF(gensymed_symbol,
					    FIX((SI_Long)2L)) = micro_time_1;
			    }
			    else {
				if (SVREF(gensymed_symbol,
					FIX((SI_Long)2L)) = micro_time_1);
			    }
			    temp_2 = FIXNUM_ADD(macro_time_1,macro_time_2);
			    SVREF(gensymed_symbol,FIX((SI_Long)1L)) = temp_2;
			    temp = TRUEP(T);
			}
			else
			    temp = TRUEP(Nil);
			if (temp)
			    initialize_current_model_queue();
			else {
			    result = VALUES_1(T);
			    goto end_1;
			}
		    }
		}
	    }
	    goto next_loop;
	  end_loop:
	    result = VALUES_1(Qnil);
	  end_1:;
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(T);
}

/* SIMULATE-MODEL-UNTIL-CONSISTENT */
Object simulate_model_until_consistent(model_runtime_info)
    Object model_runtime_info;
{
    Object current_model_runtime_info_qm, current_model_definition_qm, code;
    Object within_simulate_until_consistent_with_gensym_time;
    char temp;
    Declare_catch(1);
    Declare_special(3);
    Object result;

    x_note_fn_call(184,97);
    current_model_runtime_info_qm = Nil;
    current_model_definition_qm = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_model_definition_qm,Qcurrent_model_definition_qm,current_model_definition_qm,
	    2);
      PUSH_SPECIAL_WITH_SYMBOL(Current_model_runtime_info_qm,Qcurrent_model_runtime_info_qm,current_model_runtime_info_qm,
	      1);
	if (model_runtime_info) {
	    Current_model_runtime_info_qm = model_runtime_info;
	    Current_model_definition_qm = ISVREF(model_runtime_info,
		    (SI_Long)28L);
	}
	else {
	    if (ISVREF(Simulation_parameters,(SI_Long)24L)) {
		code = M_CAR(M_CDR(Edit_type_alias_mapping));
		temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)4096L) != 
			(SI_Long)0L : TRUEP(Qnil);
		if (temp);
		else
		    temp = TRUEP(M_CAR(M_CDR(Cache_g1_semantics_graph)));
		temp =  !temp;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		Current_model_runtime_info_qm = Main_model_runtime_info;
		Current_model_definition_qm = Nil;
	    }
	}
	if (Current_model_runtime_info_qm) {
	    if ( !TRUEP(ISVREF(Current_model_runtime_info_qm,
		    (SI_Long)11L)) &&  
		    !TRUEP(current_model_is_paused_qm()) && 
		    ISVREF(Current_model_runtime_info_qm,(SI_Long)15L)) {
		within_simulate_until_consistent_with_gensym_time = T;
		PUSH_SPECIAL_WITH_SYMBOL(Within_simulate_until_consistent_with_gensym_time,Qwithin_simulate_until_consistent_with_gensym_time,within_simulate_until_consistent_with_gensym_time,
			0);
		  if (PUSH_CATCH(Qsimulation_error_catch,0))
		      result = simulate_model_until_consistent_internal();
		  else
		      result = CATCH_VALUES();
		  POP_CATCH(0);
		POP_SPECIAL();
	    }
	    else
		result = VALUES_1(T);
	}
	else
	    result = VALUES_1(Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qsimulate_model_until_consistent_internal;  /* simulate-model-until-consistent-internal */

static Object Qsimulate_one_cycle;  /* simulate-one-cycle */

static Object string_constant_5;   /* "The simulator is not initialized and will not do anything. ~
				    *                        Restarting is recommended."
				    */

/* SIMULATE-MODEL-UNTIL-CONSISTENT-INTERNAL */
Object simulate_model_until_consistent_internal()
{
    Object tag_temp, gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object macro_time_1, micro_time_1, macro_time_2, micro_time_2, temp;
    Object temp_1, svref_new_value;
    Declare_catch(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(184,98);
    tag_temp = UNIQUE_TAG(Qsimulate_model_until_consistent_internal);
    if (PUSH_CATCH(tag_temp,0)) {
	if (Current_model_runtime_info_qm || 
		current_external_simulator_configuration()) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		check_for_simulation_changes();
		if (ISVREF(Current_model_runtime_info_qm,(SI_Long)17L)) {
		    result = VALUES_1(Qwaiting);
		    THROW(tag_temp,result);
		}
		else {
		  next_loop:
		    gensymed_symbol = Simulation_time_accumulator;
		    gensymed_symbol_1 = 
			    ISVREF(Current_model_runtime_info_qm,(SI_Long)5L);
		    gensymed_symbol_2 = 
			    ISVREF(Current_model_runtime_info_qm,(SI_Long)7L);
		    macro_time_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
		    micro_time_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		    macro_time_2 = ISVREF(gensymed_symbol_2,(SI_Long)1L);
		    micro_time_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
		    if (IFIX(micro_time_2) != (SI_Long)0L) {
			micro_time_1 = FIXNUM_ADD(micro_time_1,micro_time_2);
			if (FIXNUM_GE(micro_time_1,
				Fraction_modulus_of_compound_fixnum_simulation_time)) 
				    {
			    temp = FIXNUM_MINUS(micro_time_1,
				    Fraction_modulus_of_compound_fixnum_simulation_time);
			    SVREF(gensymed_symbol,FIX((SI_Long)2L)) = temp;
			    macro_time_1 = FIXNUM_ADD1(macro_time_1);
			}
			else
			    SVREF(gensymed_symbol,FIX((SI_Long)2L)) = 
				    micro_time_1;
		    }
		    else {
			if (SVREF(gensymed_symbol,FIX((SI_Long)2L)) = 
				micro_time_1);
		    }
		    temp = FIXNUM_ADD(macro_time_1,macro_time_2);
		    SVREF(gensymed_symbol,FIX((SI_Long)1L)) = temp;
		    gensymed_symbol = Simulation_time_accumulator;
		    gensymed_symbol_1 = ISVREF(Current_model_queue_qm,
			    (SI_Long)3L);
		    macro_time_1 = ISVREF(gensymed_symbol,(SI_Long)1L);
		    micro_time_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		    macro_time_2 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
		    micro_time_2 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		    if (FIXNUM_LT(macro_time_1,macro_time_2))
			temp_1 = T;
		    else if (FIXNUM_EQ(macro_time_1,macro_time_2))
			temp_1 = FIXNUM_LT(micro_time_1,micro_time_2) ? T :
				 Nil;
		    else
			temp_1 = Qnil;
		    if (temp_1) {
			if ( 
				!TRUEP(simulation_procedure_and_external_simulation_finished_qm())) 
				    {
			    result = VALUES_1(Qwaiting);
			    THROW(tag_temp,result);
			}
		    }
		    else {
			temp = Current_model_runtime_info_qm;
			SVREF(temp,FIX((SI_Long)1L)) = T;
			result = VALUES_1(T);
			THROW(tag_temp,result);
		    }
		  next_loop_1:
		    temp = Current_model_runtime_info_qm;
		    svref_new_value = ISVREF(Current_model_runtime_info_qm,
			    (SI_Long)10L) ? 
			    resume_task(ISVREF(Current_model_runtime_info_qm,
			    (SI_Long)10L)) : 
			    work_on_suspendable_task(Qsimulate_one_cycle,
			    Nil,Nil,Nil,Nil);
		    SVREF(temp,FIX((SI_Long)10L)) = svref_new_value;
		    if ( !TRUEP(ISVREF(Current_model_runtime_info_qm,
			    (SI_Long)10L)))
			goto end_1;
		    if (Ran_out_of_time_qm) {
			result = VALUES_1(Nil);
			THROW(tag_temp,result);
		    }
		    goto next_loop_1;
		  end_loop:
		  end_1:
		    goto next_loop;
		  end_loop_1:
		    result = VALUES_1(Qnil);
		}
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	}
	else {
	    Suppress_warning_message_header_qm = T;
	    if ((SI_Long)1L <= IFIX(Warning_message_level))
		give_warning_1(2,FIX((SI_Long)1L),string_constant_5);
	    Suppress_warning_message_header_qm = Nil;
	    result = VALUES_1(Suppress_warning_message_header_qm);
	}
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    return result;
}

static Object Qsimulation_formulas_qm;  /* simulation-formulas? */

/* PUT-SIMULATION-COMPUTATION-METHODS-WHERE-SLOT-IS-ABSENT */
Object put_simulation_computation_methods_where_slot_is_absent(frame,formulas)
    Object frame, formulas;
{
    x_note_fn_call(184,99);
    set_slot_value_function(frame,Qsimulation_formulas_qm,formulas,Nil);
    return VALUES_1(Nil);
}

static Object Qsimulator_data_server;  /* simulator-data-server */

/* INITIALIZE-SIMULATOR-AS-DATA-SERVER */
Object initialize_simulator_as_data_server()
{
    Object anything_to_simulate_qm_1, current_model_runtime_info_qm;
    Object current_model_definition_qm, code, current_model_queue_qm;
    Object data_server;
    char temp;
    Declare_special(3);

    x_note_fn_call(184,100);
    anything_to_simulate_qm_1 = Nil;
    current_model_runtime_info_qm = Nil;
    current_model_definition_qm = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_model_definition_qm,Qcurrent_model_definition_qm,current_model_definition_qm,
	    2);
      PUSH_SPECIAL_WITH_SYMBOL(Current_model_runtime_info_qm,Qcurrent_model_runtime_info_qm,current_model_runtime_info_qm,
	      1);
	if (Nil) {
	    Current_model_runtime_info_qm = Nil;
	    Current_model_definition_qm = Nil;
	}
	else {
	    if (ISVREF(Simulation_parameters,(SI_Long)24L)) {
		code = M_CAR(M_CDR(Edit_type_alias_mapping));
		temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)4096L) != 
			(SI_Long)0L : TRUEP(Qnil);
		if (temp);
		else
		    temp = TRUEP(M_CAR(M_CDR(Cache_g1_semantics_graph)));
		temp =  !temp;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		Current_model_runtime_info_qm = Main_model_runtime_info;
		Current_model_definition_qm = Nil;
	    }
	}
	if (Current_model_runtime_info_qm) {
	    current_model_queue_qm = 
		    get_model_queue_for_model(Current_model_runtime_info_qm);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_model_queue_qm,Qcurrent_model_queue_qm,current_model_queue_qm,
		    0);
	      anything_to_simulate_qm_1 = 
		      anything_to_simulate_qm(Current_model_runtime_info_qm);
	    POP_SPECIAL();
	}
      POP_SPECIAL();
    POP_SPECIAL();
    if (anything_to_simulate_qm_1) {
	data_server = 
		lookup_kb_specific_property_value(Qsimulator_data_server,
		Data_server_kbprop);
	SVREF(data_server,FIX((SI_Long)6L)) = T;
	Simulator_initialized_as_data_server_qm = Nil;
	return schedule_task_to_accept_data(data_server);
    }
    else {
	Simulator_initialized_as_data_server_qm = T;
	return VALUES_1(Simulator_initialized_as_data_server_qm);
    }
}

/* INITIALIZE-SIMULATOR */
Object initialize_simulator varargs_1(int, n)
{
    Object model_runtime_info_qm, model_definition_qm;
    Object current_model_runtime_info_qm, current_model_definition_qm, code;
    Object current_model_queue_qm;
    char temp;
    Declare_varargs_nonrelocating;
    Declare_special(3);
    Object result;

    x_note_fn_call(184,101);
    INIT_ARGS_nonrelocating();
    model_runtime_info_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    model_definition_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    current_model_runtime_info_qm = Nil;
    current_model_definition_qm = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_model_definition_qm,Qcurrent_model_definition_qm,current_model_definition_qm,
	    2);
      PUSH_SPECIAL_WITH_SYMBOL(Current_model_runtime_info_qm,Qcurrent_model_runtime_info_qm,current_model_runtime_info_qm,
	      1);
	if (model_runtime_info_qm) {
	    Current_model_runtime_info_qm = model_runtime_info_qm;
	    Current_model_definition_qm = model_definition_qm;
	}
	else {
	    if (ISVREF(Simulation_parameters,(SI_Long)24L)) {
		code = M_CAR(M_CDR(Edit_type_alias_mapping));
		temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)4096L) != 
			(SI_Long)0L : TRUEP(Qnil);
		if (temp);
		else
		    temp = TRUEP(M_CAR(M_CDR(Cache_g1_semantics_graph)));
		temp =  !temp;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		Current_model_runtime_info_qm = Main_model_runtime_info;
		Current_model_definition_qm = Nil;
	    }
	}
	if (Current_model_runtime_info_qm) {
	    current_model_queue_qm = 
		    get_model_queue_for_model(Current_model_runtime_info_qm);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_model_queue_qm,Qcurrent_model_queue_qm,current_model_queue_qm,
		    0);
	      result = initialize_simulator_1();
	    POP_SPECIAL();
	}
	else
	    result = VALUES_1(Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qrunning;            /* running */

static Object float_constant;      /* 0.0 */

static Object Qcalculating_dependent_variables;  /* calculating-dependent-variables */

/* INITIALIZE-SIMULATOR-1 */
Object initialize_simulator_1()
{
    Object number_of_simulated_variables_processed, current_computation_flags;
    Object temp, gensymed_symbol, gensymed_symbol_1, integer_portion;
    Object fraction_portion, initializing_simulator_qm;
    SI_Long gensymed_symbol_2;
    double temp_1;
    Declare_catch(1);
    Declare_special(3);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(184,102);
    if (anything_to_simulate_qm(Current_model_runtime_info_qm)) {
	number_of_simulated_variables_processed = FIX((SI_Long)0L);
	current_computation_flags = Current_computation_flags;
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		2);
	  PUSH_SPECIAL_WITH_SYMBOL(Number_of_simulated_variables_processed,Qnumber_of_simulated_variables_processed,number_of_simulated_variables_processed,
		  1);
	    Current_computation_flags = 
		    FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    add_model_to_simulation(Current_model_runtime_info_qm);
	    temp = Current_model_runtime_info_qm;
	    SVREF(temp,FIX((SI_Long)29L)) = Qrunning;
	    temp = Current_model_runtime_info_qm;
	    SVREF(temp,FIX((SI_Long)25L)) = Nil;
	    if ( !TRUEP(Warmbooting_qm))
		clear_variables_that_need_simulated_values();
	    temp = Current_model_runtime_info_qm;
	    SVREF(temp,FIX((SI_Long)13L)) = T;
	    temp = Current_model_runtime_info_qm;
	    SVREF(temp,FIX((SI_Long)17L)) = Nil;
	    temp = Current_model_runtime_info_qm;
	    SVREF(temp,FIX((SI_Long)11L)) = Nil;
	    temp = Current_model_runtime_info_qm;
	    SVREF(temp,FIX((SI_Long)10L)) = Nil;
	    temp = Current_model_runtime_info_qm;
	    SVREF(temp,FIX((SI_Long)3L)) = Nil;
	    temp = 
		    lookup_kb_specific_property_value(Qsimulator_data_server,
		    Data_server_kbprop);
	    SVREF(temp,FIX((SI_Long)6L)) = T;
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		gensymed_symbol = ISVREF(Current_model_runtime_info_qm,
			(SI_Long)9L);
		gensymed_symbol_1 = 
			current_default_simulation_time_increment();
		if (INTEGERP(gensymed_symbol_1)) {
		    SVREF(gensymed_symbol,FIX((SI_Long)1L)) = 
			    gensymed_symbol_1;
		    ISVREF(gensymed_symbol,(SI_Long)2L) = FIX((SI_Long)0L);
		}
		else {
		    result = ltruncate(lfloat(gensymed_symbol_1,
			    float_constant),_);
		    MVS_2(result,integer_portion,fraction_portion);
		    SVREF(gensymed_symbol,FIX((SI_Long)1L)) = integer_portion;
		    temp = l_round(ltimes(fraction_portion,
			    Fraction_modulus_of_compound_fixnum_simulation_time),
			    _);
		    SVREF(gensymed_symbol,FIX((SI_Long)2L)) = temp;
		}
		gensymed_symbol = ISVREF(Current_model_runtime_info_qm,
			(SI_Long)33L);
		gensymed_symbol_2 = (SI_Long)-1L;
		if (INTEGERP(FIX(gensymed_symbol_2))) {
		    ISVREF(gensymed_symbol,(SI_Long)1L) = 
			    FIX(gensymed_symbol_2);
		    ISVREF(gensymed_symbol,(SI_Long)2L) = FIX((SI_Long)0L);
		}
		else {
		    result = ltruncate(DOUBLE_TO_DOUBLE_FLOAT((double)gensymed_symbol_2),
			    _);
		    MVS_2(result,integer_portion,fraction_portion);
		    SVREF(gensymed_symbol,FIX((SI_Long)1L)) = integer_portion;
		    temp = l_round(ltimes(fraction_portion,
			    Fraction_modulus_of_compound_fixnum_simulation_time),
			    _);
		    SVREF(gensymed_symbol,FIX((SI_Long)2L)) = temp;
		}
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	    gensymed_symbol = ISVREF(Current_model_runtime_info_qm,
		    (SI_Long)8L);
	    gensymed_symbol_1 = ISVREF(Current_model_runtime_info_qm,
		    (SI_Long)9L);
	    temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	    SVREF(gensymed_symbol,FIX((SI_Long)2L)) = temp;
	    temp = ISVREF(gensymed_symbol_1,(SI_Long)1L);
	    SVREF(gensymed_symbol,FIX((SI_Long)1L)) = temp;
	    initialize_variables_for_model();
	    gensymed_symbol = ISVREF(Current_model_runtime_info_qm,
		    (SI_Long)5L);
	    gensymed_symbol_1 = ISVREF(Current_model_runtime_info_qm,
		    (SI_Long)4L);
	    temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	    SVREF(gensymed_symbol,FIX((SI_Long)2L)) = temp;
	    temp = ISVREF(gensymed_symbol_1,(SI_Long)1L);
	    SVREF(gensymed_symbol,FIX((SI_Long)1L)) = temp;
	    gensymed_symbol = ISVREF(Current_model_runtime_info_qm,
		    (SI_Long)6L);
	    gensymed_symbol_1 = ISVREF(Current_model_runtime_info_qm,
		    (SI_Long)4L);
	    temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	    SVREF(gensymed_symbol,FIX((SI_Long)2L)) = temp;
	    temp = ISVREF(gensymed_symbol_1,(SI_Long)1L);
	    SVREF(gensymed_symbol,FIX((SI_Long)1L)) = temp;
	    gensymed_symbol = ISVREF(Current_model_runtime_info_qm,
		    (SI_Long)7L);
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(Seconds_from_1900_to_1970);
	    gensymed_symbol_1 = 
		    lffloor(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
		    (SI_Long)0L) - 
		    (DFLOAT_ISAREF_1(Gensym_base_time_as_managed_float,
		    (SI_Long)0L) - temp_1)),_);
	    if (INTEGERP(gensymed_symbol_1)) {
		SVREF(gensymed_symbol,FIX((SI_Long)1L)) = gensymed_symbol_1;
		ISVREF(gensymed_symbol,(SI_Long)2L) = FIX((SI_Long)0L);
	    }
	    else {
		result = ltruncate(lfloat(gensymed_symbol_1,float_constant),_);
		MVS_2(result,integer_portion,fraction_portion);
		SVREF(gensymed_symbol,FIX((SI_Long)1L)) = integer_portion;
		temp = l_round(ltimes(fraction_portion,
			Fraction_modulus_of_compound_fixnum_simulation_time),
			_);
		SVREF(gensymed_symbol,FIX((SI_Long)2L)) = temp;
	    }
	    if (PUSH_CATCH(Qsimulation_error_catch,0)) {
		initializing_simulator_qm = T;
		PUSH_SPECIAL_WITH_SYMBOL(Initializing_simulator_qm,Qinitializing_simulator_qm,initializing_simulator_qm,
			0);
		  temp = Current_model_runtime_info_qm;
		  SVREF(temp,FIX((SI_Long)2L)) = 
			  Qcalculating_dependent_variables;
		  if ( !TRUEP(Warmbooting_qm))
		      compute_initial_values_for_all_state_variables();
		  calculate_new_values_for_dependent_variables(ISVREF(ISVREF(Current_model_runtime_info_qm,
			  (SI_Long)21L),(SI_Long)9L),Nil,Nil);
		  update_variables();
		POP_SPECIAL();
	    }
	    POP_CATCH(0);
	    initialize_externally_simulated_portion_of_model();
	    result = add_shortest_simulation_time_increment_for_all_models(ISVREF(Current_model_runtime_info_qm,
		    (SI_Long)8L));
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

static Object Qmake_and_initialize_variable_simulation_runtime_structure;  /* make-and-initialize-variable-simulation-runtime-structure */

static Object Qinitialize_runtime_simulation_information_for_variable;  /* initialize-runtime-simulation-information-for-variable */

/* INITIALIZE-VARIABLES-FOR-MODEL */
Object initialize_variables_for_model()
{
    x_note_fn_call(184,103);
    for_each_variable_in_model(Qmake_and_initialize_variable_simulation_runtime_structure);
    for_each_variable_in_model(Qinitialize_runtime_simulation_information_for_variable);
    if ( 
	    !TRUEP(installation_set_empty_qm(ISVREF(Current_model_runtime_info_qm,
	    (SI_Long)21L))))
	return sort_dependent_variable_info();
    else
	return VALUES_1(Nil);
}

static Object Qsimulation_details;  /* simulation-details */

/* MAKE-AND-INITIALIZE-VARIABLE-SIMULATION-RUNTIME-STRUCTURE */
Object make_and_initialize_variable_simulation_runtime_structure(variable_or_parameter)
    Object variable_or_parameter;
{
    Object sub_class_bit_vector, simulation_subtable_qm, slot_value_number;
    Object simulation_subtable_time_increment_for_update_qm;
    Object override_time_increment_for_update_qm, simulation_info_qm;
    Object old_runtime_structure_qm, new_runtime_structure, svref_new_value;
    Object variable_simulation_runtime_structure;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(184,104);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
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
	simulation_subtable_qm = temp ? 
		get_lookup_slot_value(variable_or_parameter,
		Qsimulation_details) : Nil;
	if (simulation_subtable_qm) {
	    slot_value_number = ISVREF(simulation_subtable_qm,(SI_Long)16L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		    (SI_Long)1L)
		simulation_subtable_time_increment_for_update_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(slot_value_number) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		    (SI_Long)1L)
		simulation_subtable_time_increment_for_update_qm = 
			aref1(slot_value_number,FIX((SI_Long)0L));
	    else
		simulation_subtable_time_increment_for_update_qm = 
			slot_value_number;
	}
	else
	    simulation_subtable_time_increment_for_update_qm = Nil;
	override_time_increment_for_update_qm = 
		simulation_subtable_time_increment_for_update_qm;
	if (override_time_increment_for_update_qm);
	else {
	    simulation_info_qm = 
		    get_lookup_slot_value_given_default(variable_or_parameter,
		    Qsimulation_info_qm,Nil);
	    slot_value_number = simulation_info_qm ? 
		    ISVREF(simulation_info_qm,(SI_Long)4L) : Nil;
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		    (SI_Long)1L)
		override_time_increment_for_update_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(slot_value_number) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		    (SI_Long)1L)
		override_time_increment_for_update_qm = 
			aref1(slot_value_number,FIX((SI_Long)0L));
	    else
		override_time_increment_for_update_qm = slot_value_number;
	}
	simulation_info_qm = 
		get_lookup_slot_value_given_default(variable_or_parameter,
		Qsimulation_info_qm,Nil);
	old_runtime_structure_qm = simulation_info_qm ? 
		ISVREF(simulation_info_qm,(SI_Long)1L) : Nil;
	new_runtime_structure = make_variable_simulation_runtime_structure_1();
	if (old_runtime_structure_qm) {
	    if (Warmbooting_qm) {
		svref_new_value = 
			copy_for_slot_value(ISVREF(old_runtime_structure_qm,
			(SI_Long)2L));
		SVREF(new_runtime_structure,FIX((SI_Long)2L)) = 
			svref_new_value;
		svref_new_value = 
			copy_for_slot_value(ISVREF(old_runtime_structure_qm,
			(SI_Long)1L));
		SVREF(new_runtime_structure,FIX((SI_Long)1L)) = 
			svref_new_value;
	    }
	    reclaim_variable_simulation_runtime_structure(old_runtime_structure_qm);
	}
	SVREF(new_runtime_structure,FIX((SI_Long)16L)) = variable_or_parameter;
	simulation_info_qm = 
		get_lookup_slot_value_given_default(variable_or_parameter,
		Qsimulation_info_qm,Nil);
	if (simulation_info_qm)
	    SVREF(simulation_info_qm,FIX((SI_Long)1L)) = new_runtime_structure;
	variable_simulation_runtime_structure = new_runtime_structure;
	SVREF(variable_simulation_runtime_structure,FIX((SI_Long)14L)) = Nil;
	set_up_update_timing_for_variable(variable_simulation_runtime_structure,
		override_time_increment_for_update_qm);
	if ( !TRUEP(Warmbooting_qm)) {
	    svref_new_value = Simulation_no_value;
	    SVREF(variable_simulation_runtime_structure,FIX((SI_Long)1L)) 
		    = svref_new_value;
	    svref_new_value = Simulation_no_value;
	    SVREF(variable_simulation_runtime_structure,FIX((SI_Long)2L)) 
		    = svref_new_value;
	}
	SVREF(variable_simulation_runtime_structure,FIX((SI_Long)23L)) = Nil;
	result = VALUES_1(variable_simulation_runtime_structure);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* INITIALIZE-RUNTIME-SIMULATION-INFORMATION-FOR-VARIABLE */
Object initialize_runtime_simulation_information_for_variable(variable)
    Object variable;
{
    Object simulation_info_qm, variable_simulation_runtime_structure;

    x_note_fn_call(184,105);
    simulation_info_qm = get_lookup_slot_value_given_default(variable,
	    Qsimulation_info_qm,Nil);
    variable_simulation_runtime_structure = simulation_info_qm ? 
	    ISVREF(simulation_info_qm,(SI_Long)1L) : Nil;
    generate_and_set_runtime_formula(variable,
	    variable_simulation_runtime_structure);
    return begin_collecting_data_for_simulated_variable_if_appropriate(variable);
}

/* GENERATE-AND-SET-RUNTIME-FORMULA */
Object generate_and_set_runtime_formula(variable,
	    variable_simulation_runtime_structure)
    Object variable, variable_simulation_runtime_structure;
{
    Object things_that_affect_runtime_formula;

    x_note_fn_call(184,106);
    things_that_affect_runtime_formula = 
	    generate_and_set_runtime_formula_1(variable,
	    variable_simulation_runtime_structure);
    note_runtime_structure_in_things_that_affect_it(variable,
	    things_that_affect_runtime_formula,Nil);
    return reclaim_eval_list_1(things_that_affect_runtime_formula);
}

/* GENERATE-AND-SET-RUNTIME-FORMULA-1 */
Object generate_and_set_runtime_formula_1(variable,
	    variable_simulation_runtime_structure)
    Object variable, variable_simulation_runtime_structure;
{
    Object current_computation_flags;
    Object note_things_encountered_during_role_service_qm;
    Object things_that_affect_this_formula, simulation_specifier_to_use;
    Object sub_class_bit_vector, gensymed_symbol_3, gensymed_symbol_4;
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_5;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(3);
    Object result;

    x_note_fn_call(184,107);
    current_computation_flags = Current_computation_flags;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
	    2);
      Current_computation_flags = FIX(IFIX(Current_computation_flags) | 
	      (SI_Long)16L);
      note_things_encountered_during_role_service_qm = T;
      PUSH_SPECIAL_WITH_SYMBOL(Note_things_encountered_during_role_service_qm,Qnote_things_encountered_during_role_service_qm,note_things_encountered_during_role_service_qm,
	      1);
	things_that_affect_this_formula = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Things_that_affect_this_formula,Qthings_that_affect_this_formula,things_that_affect_this_formula,
		0);
	  simulation_specifier_to_use = 
		  get_simulation_specifier_to_use(variable);
	  sub_class_bit_vector = ISVREF(ISVREF(simulation_specifier_to_use,
		  (SI_Long)1L),(SI_Long)19L);
	  superior_class_bit_number = 
		  IFIX(ISVREF(Simulation_subtable_class_description,
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
	  if (temp) {
	      gensymed_symbol_3 = Things_that_affect_this_formula;
	      gensymed_symbol_4 = variable;
	      if ( !TRUEP(memq_function(gensymed_symbol_4,
			  gensymed_symbol_3))) {
		  new_cons = ISVREF(Available_eval_conses_vector,
			  IFIX(Current_thread_index));
		  if (new_cons) {
		      svref_arg_1 = Available_eval_conses_vector;
		      svref_arg_2 = Current_thread_index;
		      svref_new_value = M_CDR(new_cons);
		      SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		      if ( !TRUEP(ISVREF(Available_eval_conses_vector,
			      IFIX(Current_thread_index)))) {
			  svref_arg_1 = Available_eval_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(svref_arg_1,svref_arg_2) = Nil;
		      }
		      gensymed_symbol_5 = new_cons;
		  }
		  else
		      gensymed_symbol_5 = Nil;
		  if ( !TRUEP(gensymed_symbol_5))
		      gensymed_symbol_5 = replenish_eval_cons_pool();
		  M_CAR(gensymed_symbol_5) = gensymed_symbol_4;
		  M_CDR(gensymed_symbol_5) = gensymed_symbol_3;
		  inline_note_allocate_cons(gensymed_symbol_5,Qeval);
		  Things_that_affect_this_formula = gensymed_symbol_5;
	      }
	  }
	  else {
	      sub_class_bit_vector = 
		      ISVREF(ISVREF(simulation_specifier_to_use,
		      (SI_Long)1L),(SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Generic_simulation_formula_class_description,
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
	      if (temp) {
		  gensymed_symbol_3 = Things_that_affect_this_formula;
		  gensymed_symbol_4 = simulation_specifier_to_use;
		  if ( !TRUEP(memq_function(gensymed_symbol_4,
			  gensymed_symbol_3))) {
		      new_cons = ISVREF(Available_eval_conses_vector,
			      IFIX(Current_thread_index));
		      if (new_cons) {
			  svref_arg_1 = Available_eval_conses_vector;
			  svref_arg_2 = Current_thread_index;
			  svref_new_value = M_CDR(new_cons);
			  SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
			  if ( !TRUEP(ISVREF(Available_eval_conses_vector,
				  IFIX(Current_thread_index)))) {
			      svref_arg_1 = Available_eval_conses_tail_vector;
			      svref_arg_2 = Current_thread_index;
			      SVREF(svref_arg_1,svref_arg_2) = Nil;
			  }
			  gensymed_symbol_5 = new_cons;
		      }
		      else
			  gensymed_symbol_5 = Nil;
		      if ( !TRUEP(gensymed_symbol_5))
			  gensymed_symbol_5 = replenish_eval_cons_pool();
		      M_CAR(gensymed_symbol_5) = gensymed_symbol_4;
		      M_CDR(gensymed_symbol_5) = gensymed_symbol_3;
		      inline_note_allocate_cons(gensymed_symbol_5,Qeval);
		      Things_that_affect_this_formula = gensymed_symbol_5;
		  }
	      }
	  }
	  SVREF(variable_simulation_runtime_structure,FIX((SI_Long)21L)) = 
		  simulation_specifier_to_use;
	  initialize_simulation_environment_vector(variable,
		  simulation_specifier_to_use);
	  result = VALUES_1(Things_that_affect_this_formula);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* INITIALIZE-SIMULATION-ENVIRONMENT-VECTOR */
Object initialize_simulation_environment_vector(variable,simulation_formula)
    Object variable, simulation_formula;
{
    Object simulation_info_qm, runtime_structure, sub_class_bit_vector;
    Object byte_code_body, simulation_environment_vector;
    Object initial_value_byte_code_body_qm;
    Object initial_value_simulation_environment_vector_qm, focal_entity_qm;
    Object dependent_variable_qm, evaluated_designation;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, binding_cache_start_index;
    SI_Long index_1, ab_loop_bind_;
    char temp;

    x_note_fn_call(184,108);
    simulation_info_qm = get_lookup_slot_value_given_default(variable,
	    Qsimulation_info_qm,Nil);
    runtime_structure = simulation_info_qm ? ISVREF(simulation_info_qm,
	    (SI_Long)1L) : Nil;
    sub_class_bit_vector = ISVREF(ISVREF(simulation_formula,(SI_Long)1L),
	    (SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Generic_simulation_formula_class_description,
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
    if (temp)
	byte_code_body = ISVREF(simulation_formula,(SI_Long)20L);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(simulation_formula,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Simulation_subtable_class_description,
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
	    byte_code_body = ISVREF(simulation_formula,(SI_Long)23L);
	else
	    byte_code_body = Qnil;
    }
    simulation_environment_vector = 
	    get_or_make_simulation_runtime_cache(var_count(ISVREF(byte_code_body,
	    (SI_Long)4L)),runtime_structure,Nil);
    sub_class_bit_vector = ISVREF(ISVREF(simulation_formula,(SI_Long)1L),
	    (SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Generic_simulation_formula_class_description,
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
    if (temp)
	initial_value_byte_code_body_qm = ISVREF(simulation_formula,
		(SI_Long)21L);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(simulation_formula,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Simulation_subtable_class_description,
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
	    initial_value_byte_code_body_qm = ISVREF(simulation_formula,
		    (SI_Long)24L);
	else
	    initial_value_byte_code_body_qm = Qnil;
    }
    initial_value_simulation_environment_vector_qm = 
	    initial_value_byte_code_body_qm ? 
	    get_or_make_simulation_runtime_cache(var_count(ISVREF(initial_value_byte_code_body_qm,
	    (SI_Long)4L)),runtime_structure,T) : Nil;
    focal_entity_qm = get_formula_focal_entity_for_variable(variable);
    dependent_variable_qm = dependent_variable_p(variable);
    if (initial_value_simulation_environment_vector_qm) {
	if (focal_entity_qm)
	    SVREF(initial_value_simulation_environment_vector_qm,
		    FIX((SI_Long)3L)) = focal_entity_qm;
	set_recaching_needed_flag(initial_value_simulation_environment_vector_qm,
		Nil);
    }
    if (dependent_variable_qm) {
	reclaim_eval_list_1(ISVREF(runtime_structure,(SI_Long)18L));
	SVREF(runtime_structure,FIX((SI_Long)18L)) = Nil;
    }
    if (focal_entity_qm)
	SVREF(simulation_environment_vector,FIX((SI_Long)3L)) = 
		focal_entity_qm;
    set_recaching_needed_flag(simulation_environment_vector,T);
    SVREF(runtime_structure,FIX((SI_Long)17L)) = byte_code_body;
    sim_eval_for_stack_without_chaining(variable);
    set_recaching_needed_flag(simulation_environment_vector,Nil);
    if (dependent_variable_qm) {
	binding_cache_start_index = focal_entity_qm ? (SI_Long)4L : 
		(SI_Long)3L;
	evaluated_designation = Nil;
	index_1 = binding_cache_start_index;
	ab_loop_bind_ = binding_cache_start_index + 
		IFIX(ISVREF(simulation_environment_vector,(SI_Long)2L));
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	evaluated_designation = ISVREF(simulation_environment_vector,index_1);
	note_supporting_variables(evaluated_designation,runtime_structure);
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qtruth_value;        /* truth-value */

/* SET-RECACHING-NEEDED-FLAG */
Object set_recaching_needed_flag(simulation_environment_vector,
	    recaching_needed_qm)
    Object simulation_environment_vector, recaching_needed_qm;
{
    Object existing_flag_qm, svref_new_value;
    SI_Long gensymed_symbol;

    x_note_fn_call(184,109);
    existing_flag_qm = ISVREF(simulation_environment_vector,(SI_Long)0L);
    if (existing_flag_qm) {
	if ( !(EQ(existing_flag_qm,Evaluation_true_value) || 
		EQ(existing_flag_qm,Evaluation_false_value)))
	    reclaim_eval_cons_1(existing_flag_qm);
    }
    gensymed_symbol = recaching_needed_qm ? IFIX(Truth) : IFIX(Falsity);
    if (gensymed_symbol == IFIX(Truth))
	svref_new_value = Evaluation_true_value;
    else if (gensymed_symbol == IFIX(Falsity))
	svref_new_value = Evaluation_false_value;
    else
	svref_new_value = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    return VALUES_1(SVREF(simulation_environment_vector,FIX((SI_Long)0L)) 
	    = svref_new_value);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* NOTE-SUPPORTING-VARIABLES */
Object note_supporting_variables(cached_designation,runtime_structure)
    Object cached_designation, runtime_structure;
{
    Object x2, gensymed_symbol, sub_class_bit_vector, simulation_info_qm;
    Object gensymed_symbol_4, temp_1, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol_5;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(184,110);
    if (SIMPLE_VECTOR_P(cached_designation) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(cached_designation)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(cached_designation,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(cached_designation,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
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
    if (temp) {
	simulation_info_qm = 
		get_lookup_slot_value_given_default(cached_designation,
		Qsimulation_info_qm,Nil);
	temp = simulation_info_qm ? EQ(ISVREF(simulation_info_qm,
		(SI_Long)8L),Current_model_definition_qm) : TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol = ISVREF(runtime_structure,(SI_Long)18L);
	gensymed_symbol_4 = cached_designation;
	if ( !TRUEP(memq_function(gensymed_symbol_4,gensymed_symbol))) {
	    temp_1 = gensymed_symbol_4;
	    new_cons = ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		svref_arg_1 = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_eval_conses_vector,
			IFIX(Current_thread_index)))) {
		    svref_arg_1 = Available_eval_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(svref_arg_1,svref_arg_2) = Nil;
		}
		gensymed_symbol_5 = new_cons;
	    }
	    else
		gensymed_symbol_5 = Nil;
	    if ( !TRUEP(gensymed_symbol_5))
		gensymed_symbol_5 = replenish_eval_cons_pool();
	    M_CAR(gensymed_symbol_5) = gensymed_symbol_4;
	    M_CDR(gensymed_symbol_5) = gensymed_symbol;
	    inline_note_allocate_cons(gensymed_symbol_5,Qeval);
	    SVREF(runtime_structure,FIX((SI_Long)18L)) = gensymed_symbol_5;
	    return VALUES_1(temp_1);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qrole_server;        /* role-server */

/* ROLES-IN-DESIGNATION-CAN-BE-CACHED? */
Object roles_in_designation_can_be_cached_qm(designation,runtime_cache)
    Object designation, runtime_cache;
{
    Object temp, role, domain_qm;

    x_note_fn_call(184,111);
    if ( !TRUEP(designation))
	return VALUES_1(Nil);
    else if (CONSP(designation)) {
	temp = CAR(designation);
	if (EQ(temp,Qthe)) {
	    role = SECOND(designation);
	    domain_qm = THIRD(designation);
	    if (CONSP(role)) {
		if (role_can_be_cached_qm(CAR(role)))
		    return roles_in_designation_can_be_cached_qm(domain_qm,
			    runtime_cache);
		else
		    return VALUES_1(Nil);
	    }
	    else if ( 
		    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(role),
		    Qrole_server)) || role_can_be_cached_qm(role))
		return roles_in_designation_can_be_cached_qm(domain_qm,
			runtime_cache);
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(T);
}

Object List_of_roles_that_can_be_cached = UNBOUND;

/* ROLE-CAN-BE-CACHED? */
Object role_can_be_cached_qm(role_name)
    Object role_name;
{
    x_note_fn_call(184,112);
    return memq_function(role_name,List_of_roles_that_can_be_cached);
}

/* NOTE-RUNTIME-STRUCTURE-IN-THINGS-THAT-AFFECT-IT */
Object note_runtime_structure_in_things_that_affect_it(variable,
	    things_that_affect_runtime_formula,affects_installation_qm)
    Object variable, things_that_affect_runtime_formula;
    Object affects_installation_qm;
{
    Object thing, ab_loop_list_, edit_cache_qm;

    x_note_fn_call(184,113);
    thing = Nil;
    ab_loop_list_ = things_that_affect_runtime_formula;
    edit_cache_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    thing = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    edit_cache_qm = get_or_make_edit_cache(thing);
    if (edit_cache_qm)
	add_to_structures_affected_by_edit_cache(edit_cache_qm,variable,
		affects_installation_qm);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qg2_defstruct_structure_name_connection_g2_struct;  /* g2-defstruct-structure-name::connection-g2-struct */

/* GET-OR-MAKE-EDIT-CACHE */
Object get_or_make_edit_cache(thing)
    Object thing;
{
    Object x2, sub_class_bit_vector, svref_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(184,114);
    if (SIMPLE_VECTOR_P(thing) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(thing,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(thing,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(thing,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Entity_class_description,
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
	if (temp) {
	    svref_new_value = get_or_make_edit_cache_1(ISVREF(thing,
		    (SI_Long)19L));
	    return VALUES_1(ISVREF(thing,(SI_Long)19L) = svref_new_value);
	}
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(thing,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Statement_class_description,(SI_Long)18L));
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
		svref_new_value = get_or_make_edit_cache_1(ISVREF(thing,
			(SI_Long)19L));
		return VALUES_1(ISVREF(thing,(SI_Long)19L) = svref_new_value);
	    }
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(thing,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Connection_class_description,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_1 = (SI_Long)1L;
		    gensymed_symbol_2 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		    gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		    temp = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp = TRUEP(Nil);
		if (temp)
		    return get_or_make_edit_cache(ISVREF(thing,(SI_Long)21L));
		else
		    return VALUES_1(Qnil);
	    }
	}
    }
    else if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
	    Qg2_defstruct_structure_name_connection_g2_struct)) {
	svref_new_value = get_or_make_edit_cache_1(ISVREF(thing,(SI_Long)8L));
	return VALUES_1(SVREF(thing,FIX((SI_Long)8L)) = svref_new_value);
    }
    else
	return VALUES_1(Qnil);
}

/* GET-OR-MAKE-EDIT-CACHE-1 */
Object get_or_make_edit_cache_1(edit_cache_qm)
    Object edit_cache_qm;
{
    Object temp;

    x_note_fn_call(184,115);
    temp = edit_cache_qm;
    if (temp)
	return VALUES_1(temp);
    else
	return make_edit_cache_1();
}

/* ADD-TO-STRUCTURES-AFFECTED-BY-EDIT-CACHE */
Object add_to_structures_affected_by_edit_cache(edit_cache,
	    runtime_structure_to_add,affects_installation_qm)
    Object edit_cache, runtime_structure_to_add, affects_installation_qm;
{
    Object frame_serial_number_setf_arg, old, new_1, svref_new_value;

    x_note_fn_call(184,116);
    purge_deleted_frames_and_add_new_one(edit_cache,
	    affects_installation_qm,runtime_structure_to_add);
    frame_serial_number_setf_arg = Current_frame_serial_number;
    old = ISVREF(edit_cache,(SI_Long)1L);
    new_1 = frame_serial_number_setf_arg;
    svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && (FIXNUMP(new_1) || 
	     !TRUEP(new_1)) ? new_1 : 
	    frame_serial_number_setf_helper_1(old,new_1);
    return VALUES_1(SVREF(edit_cache,FIX((SI_Long)1L)) = svref_new_value);
}

/* PURGE-DELETED-FRAMES-AND-ADD-NEW-ONE */
Object purge_deleted_frames_and_add_new_one(edit_cache,
	    affects_installation_qm,runtime_structure_to_add)
    Object edit_cache, affects_installation_qm, runtime_structure_to_add;
{
    Object frame_serial_number_for_cache, trailing_pointer_qm, leading_pointer;
    Object cons_to_reclaim, exists_in_cache_qm, runtime_structure_to_check_qm;
    Object gensymed_symbol, xa, ya, temp_1;
    char temp;

    x_note_fn_call(184,117);
    frame_serial_number_for_cache = ISVREF(edit_cache,(SI_Long)1L);
    trailing_pointer_qm = Nil;
    leading_pointer = affects_installation_qm ? ISVREF(edit_cache,
	    (SI_Long)3L) : ISVREF(edit_cache,(SI_Long)2L);
    cons_to_reclaim = Nil;
    exists_in_cache_qm = Nil;
    runtime_structure_to_check_qm = Nil;
  next_loop:
    runtime_structure_to_check_qm = CAR(leading_pointer);
    if ( !TRUEP(runtime_structure_to_check_qm))
	goto end_loop;
    if (EQ(runtime_structure_to_check_qm,runtime_structure_to_add))
	exists_in_cache_qm = T;
    gensymed_symbol = ISVREF(runtime_structure_to_check_qm,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(runtime_structure_to_check_qm) ? 
	    EQ(ISVREF(runtime_structure_to_check_qm,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(frame_serial_number_for_cache))
	temp = FIXNUMP(gensymed_symbol) ? 
		FIXNUM_LT(frame_serial_number_for_cache,gensymed_symbol) : 
		TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(frame_serial_number_for_cache);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? 
		    FIXNUM_LT(M_CDR(frame_serial_number_for_cache),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    if (temp) {
	if (trailing_pointer_qm) {
	    temp_1 = CDR(leading_pointer);
	    M_CDR(trailing_pointer_qm) = temp_1;
	}
	else if (affects_installation_qm) {
	    temp_1 = CDR(leading_pointer);
	    SVREF(edit_cache,FIX((SI_Long)3L)) = temp_1;
	}
	else {
	    temp_1 = CDR(leading_pointer);
	    SVREF(edit_cache,FIX((SI_Long)2L)) = temp_1;
	}
	cons_to_reclaim = leading_pointer;
	leading_pointer = CDR(leading_pointer);
	reclaim_eval_cons_1(cons_to_reclaim);
    }
    else {
	trailing_pointer_qm = leading_pointer;
	leading_pointer = CDR(leading_pointer);
    }
    goto next_loop;
  end_loop:
    if ( !TRUEP(exists_in_cache_qm)) {
	if (affects_installation_qm) {
	    temp_1 = eval_cons_1(runtime_structure_to_add,
		    ISVREF(edit_cache,(SI_Long)3L));
	    SVREF(edit_cache,FIX((SI_Long)3L)) = temp_1;
	}
	else {
	    temp_1 = eval_cons_1(runtime_structure_to_add,
		    ISVREF(edit_cache,(SI_Long)2L));
	    SVREF(edit_cache,FIX((SI_Long)2L)) = temp_1;
	}
    }
    return VALUES_1(Qnil);
}

static Object Qreset_sort_flag;    /* reset-sort-flag */

/* SORT-DEPENDENT-VARIABLE-INFO */
Object sort_dependent_variable_info()
{
    Object svref_arg_1;

    x_note_fn_call(184,118);
    for_each_element_in_installation_set(ISVREF(Current_model_runtime_info_qm,
	    (SI_Long)21L),Qreset_sort_flag);
    svref_arg_1 = Current_model_runtime_info_qm;
    SVREF(svref_arg_1,FIX((SI_Long)22L)) = Nil;
    return sort_dependent_variable_info_1();
}

/* RESET-SORT-FLAG */
Object reset_sort_flag(variable)
    Object variable;
{
    Object simulation_info_qm, runtime_structure;

    x_note_fn_call(184,119);
    simulation_info_qm = get_lookup_slot_value_given_default(variable,
	    Qsimulation_info_qm,Nil);
    runtime_structure = simulation_info_qm ? ISVREF(simulation_info_qm,
	    (SI_Long)1L) : Nil;
    if (runtime_structure)
	return VALUES_1(SVREF(runtime_structure,FIX((SI_Long)19L)) = Nil);
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Next_element_to_be_sorted_qm, Qnext_element_to_be_sorted_qm);

/* SORT-DEPENDENT-VARIABLE-INFO-1 */
Object sort_dependent_variable_info_1()
{
    Object next_element_to_be_sorted_qm, runtime_info_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(184,120);
    next_element_to_be_sorted_qm = 
	    ISVREF(ISVREF(Current_model_runtime_info_qm,(SI_Long)21L),
	    (SI_Long)9L);
    PUSH_SPECIAL_WITH_SYMBOL(Next_element_to_be_sorted_qm,Qnext_element_to_be_sorted_qm,next_element_to_be_sorted_qm,
	    0);
      runtime_info_qm = Nil;
    next_loop:
      if ( !TRUEP(Next_element_to_be_sorted_qm))
	  goto end_loop;
      runtime_info_qm = ISVREF(Next_element_to_be_sorted_qm,(SI_Long)1L);
      sort_dependent_variable(runtime_info_qm);
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object Qbeing_sorted;       /* being-sorted */

static Object Qunsorted;           /* unsorted */

static Object Qsorted;             /* sorted */

/* SORT-DEPENDENT-VARIABLE */
Object sort_dependent_variable(runtime_structure)
    Object runtime_structure;
{
    Object add_to_sorted_list_qm, supporting_variable, ab_loop_list_;
    Object supporting_structure, simulation_info_qm;

    x_note_fn_call(184,121);
    add_to_sorted_list_qm = Nil;
    supporting_variable = Nil;
    ab_loop_list_ = ISVREF(runtime_structure,(SI_Long)18L);
    supporting_structure = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    supporting_variable = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    simulation_info_qm = 
	    get_lookup_slot_value_given_default(supporting_variable,
	    Qsimulation_info_qm,Nil);
    supporting_structure = simulation_info_qm ? ISVREF(simulation_info_qm,
	    (SI_Long)1L) : Nil;
    if (dependent_variable_p(supporting_variable)) {
	if ( !TRUEP(ISVREF(supporting_structure,(SI_Long)19L))) {
	    SVREF(runtime_structure,FIX((SI_Long)19L)) = Qbeing_sorted;
	    sort_dependent_variable(supporting_structure);
	}
	if (EQ(ISVREF(supporting_structure,(SI_Long)19L),Qunsorted) || 
		EQ(ISVREF(supporting_structure,(SI_Long)19L),Qbeing_sorted)) {
	    add_to_sorted_list_qm = Nil;
	    goto end_1;
	}
    }
    goto next_loop;
  end_loop:
    add_to_sorted_list_qm = T;
    goto end_1;
    add_to_sorted_list_qm = Qnil;
  end_1:;
    if (add_to_sorted_list_qm) {
	SVREF(runtime_structure,FIX((SI_Long)19L)) = Qsorted;
	return add_variable_to_sorted_or_unsorted_portion_of_set(runtime_structure,
		T);
    }
    else if ( !EQ(ISVREF(runtime_structure,(SI_Long)19L),Qunsorted)) {
	SVREF(runtime_structure,FIX((SI_Long)19L)) = Qunsorted;
	return add_variable_to_sorted_or_unsorted_portion_of_set(runtime_structure,
		Nil);
    }
    else
	return VALUES_1(Nil);
}

/* ADD-VARIABLE-TO-SORTED-OR-UNSORTED-PORTION-OF-SET */
Object add_variable_to_sorted_or_unsorted_portion_of_set(runtime_structure,
	    sorted_qm)
    Object runtime_structure, sorted_qm;
{
    Object variable, simulation_info, sort_boundary_qm, svref_arg_1;

    x_note_fn_call(184,122);
    variable = ISVREF(runtime_structure,(SI_Long)16L);
    simulation_info = get_lookup_slot_value_given_default(variable,
	    Qsimulation_info_qm,Nil);
    sort_boundary_qm = ISVREF(Current_model_runtime_info_qm,(SI_Long)22L);
    if (EQ(simulation_info,Next_element_to_be_sorted_qm))
	Next_element_to_be_sorted_qm = ISVREF(Next_element_to_be_sorted_qm,
		(SI_Long)9L);
    if (sort_boundary_qm)
	insert_in_installation_set(sort_boundary_qm,variable);
    else
	add_to_installation_set(ISVREF(Current_model_runtime_info_qm,
		(SI_Long)21L),variable);
    if (sorted_qm) {
	svref_arg_1 = Current_model_runtime_info_qm;
	return VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)22L)) = 
		simulation_info);
    }
    else
	return VALUES_1(Nil);
}

static Object Qcompute_and_initialize_state_variable;  /* compute-and-initialize-state-variable */

/* COMPUTE-INITIAL-VALUES-FOR-ALL-STATE-VARIABLES */
Object compute_initial_values_for_all_state_variables()
{
    Object initializing_state_variables_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(184,123);
    initializing_state_variables_qm = T;
    PUSH_SPECIAL_WITH_SYMBOL(Initializing_state_variables_qm,Qinitializing_state_variables_qm,initializing_state_variables_qm,
	    0);
      for_each_element_in_installation_set(ISVREF(Current_model_runtime_info_qm,
	      (SI_Long)19L),Qcompute_and_initialize_state_variable);
      result = for_each_element_in_installation_set(ISVREF(Current_model_runtime_info_qm,
	      (SI_Long)20L),Qcompute_and_initialize_state_variable);
    POP_SPECIAL();
    return result;
}

/* COMPUTE-AND-INITIALIZE-STATE-VARIABLE */
Object compute_and_initialize_state_variable(state_variable)
    Object state_variable;
{
    Object simulation_info_qm, runtime_structure_qm;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(184,124);
    simulation_info_qm = 
	    get_lookup_slot_value_given_default(state_variable,
	    Qsimulation_info_qm,Nil);
    runtime_structure_qm = simulation_info_qm ? ISVREF(simulation_info_qm,
	    (SI_Long)1L) : Nil;
    if (runtime_structure_qm) {
	SVREF(runtime_structure_qm,FIX((SI_Long)13L)) = T;
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
	    result = compute_initial_value_for_state_variable(state_variable,
		    runtime_structure_qm);
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* COMPUTE-INITIAL-VALUE-FOR-STATE-VARIABLE */
Object compute_initial_value_for_state_variable(variable_or_parameter,
	    runtime_structure)
    Object variable_or_parameter, runtime_structure;
{
    x_note_fn_call(184,125);
    if (need_to_stack_eval_to_get_initial_value_for_state_variable_qm(variable_or_parameter,
	    runtime_structure))
	return sim_eval_for_stack_until_value_found(variable_or_parameter);
    else
	return VALUES_1(Nil);
}

static Object Qnon_default_initial_simulated_value_qm;  /* non-default-initial-simulated-value? */

static Object Qlong;               /* long */

static Object Qtext;               /* text */

static Object Qboolean;            /* boolean */

static Object Quse_initial_value_expression_in_generic_simulation_formula;  /* use-initial-value-expression-in-generic-simulation-formula */

static Object Qab_let;             /* let */

static Object Qcurrent_parameter_value;  /* current-parameter-value */

/* NEED-TO-STACK-EVAL-TO-GET-INITIAL-VALUE-FOR-STATE-VARIABLE? */
Object need_to_stack_eval_to_get_initial_value_for_state_variable_qm(variable_or_parameter,
	    runtime_structure)
    Object variable_or_parameter, runtime_structure;
{
    Object sub_class_bit_vector, slot_value_number;
    Object non_default_initial_value_qm, simulation_info_qm;
    Object initial_value_expression_from_formulas, gensymed_symbol_3;
    Object gensymed_symbol_4, gensymed_symbol_5, type_specification;
    Object svref_new_value, temp_1, store_managed_number_or_value_arg_1;
    Object generic_simulation_formula, initial_value_expression;
    Object managed_number_or_value;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    double store_managed_number_or_value_arg;

    x_note_fn_call(184,126);
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
	slot_value_number = 
		get_lookup_slot_value_given_default(variable_or_parameter,
		Qnon_default_initial_simulated_value_qm,Nil);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != (SI_Long)0L 
		&& IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		(SI_Long)1L)
	    non_default_initial_value_qm = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(slot_value_number) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		(SI_Long)1L)
	    non_default_initial_value_qm = aref1(slot_value_number,
		    FIX((SI_Long)0L));
	else
	    non_default_initial_value_qm = slot_value_number;
    }
    else
	non_default_initial_value_qm = Nil;
    simulation_info_qm = 
	    get_lookup_slot_value_given_default(variable_or_parameter,
	    Qsimulation_info_qm,Nil);
    initial_value_expression_from_formulas = simulation_info_qm ? 
	    ISVREF(simulation_info_qm,(SI_Long)3L) : Nil;
    if (non_default_initial_value_qm) {
	gensymed_symbol_3 = runtime_structure;
	gensymed_symbol_4 = ISVREF(gensymed_symbol_3,(SI_Long)16L);
	gensymed_symbol_5 = non_default_initial_value_qm;
	type_specification = 
		type_specification_of_variable_or_parameter_value(gensymed_symbol_4);
	if (EQ(type_specification,Qfloat) && FIXNUMP(gensymed_symbol_5)) {
	    store_managed_number_or_value_arg = 
		    (double)IFIX(gensymed_symbol_5);
	    svref_new_value = 
		    store_managed_number_or_value_function(ISVREF(gensymed_symbol_3,
		    (SI_Long)2L),
		    DOUBLE_TO_DOUBLE_FLOAT(store_managed_number_or_value_arg));
	    SVREF(gensymed_symbol_3,FIX((SI_Long)2L)) = svref_new_value;
	}
	else {
	    if (EQ(type_specification,Qinteger))
		temp_1 = FIXNUMP(gensymed_symbol_5) ? T : Nil;
	    else if (EQ(type_specification,Qlong))
		temp_1 = INLINE_LONG_P(gensymed_symbol_5) != (SI_Long)0L ? 
			T : Nil;
	    else if (EQ(type_specification,Qfloat))
		temp_1 = FLOATP(gensymed_symbol_5) ? T : Nil;
	    else if (EQ(type_specification,Qsymbol))
		temp_1 = gensymed_symbol_5 ? (SYMBOLP(gensymed_symbol_5) ? 
			T : Nil) : Qnil;
	    else if (EQ(type_specification,Qtext))
		temp_1 = text_string_p(gensymed_symbol_5);
	    else if (EQ(type_specification,Qtruth_value))
		temp_1 = FIXNUMP(gensymed_symbol_5) && FIXNUM_LE(Falsity,
			gensymed_symbol_5) ? (FIXNUM_LE(gensymed_symbol_5,
			Truth) ? T : Nil) : Qnil;
	    else if (EQ(type_specification,Qboolean)) {
		if (FIXNUMP(gensymed_symbol_5)) {
		    temp_1 = FIXNUM_EQ(gensymed_symbol_5,Falsity) ? T : Nil;
		    if (temp_1);
		    else
			temp_1 = FIXNUM_EQ(gensymed_symbol_5,Truth) ? T : Nil;
		}
		else
		    temp_1 = Nil;
	    }
	    else if (EQ(type_specification,Qnumber) || 
		    EQ(type_specification,Qinteger) || 
		    EQ(type_specification,Qfloat) || EQ(type_specification,
		    Qlong) || 
		    lookup_global_or_kb_specific_property_value(type_specification,
		    Numeric_data_type_gkbprop)) {
		temp_1 = FLOATP(gensymed_symbol_5) ? T : Nil;
		if (temp_1);
		else
		    temp_1 = FIXNUMP(gensymed_symbol_5) ? T : Nil;
	    }
	    else
		temp_1 = Nil;
	    if (temp_1) {
		store_managed_number_or_value_arg_1 = gensymed_symbol_5;
		svref_new_value = 
			store_managed_number_or_value_function(ISVREF(gensymed_symbol_3,
			(SI_Long)2L),store_managed_number_or_value_arg_1);
		SVREF(gensymed_symbol_3,FIX((SI_Long)2L)) = svref_new_value;
	    }
	    else
		simulation_type_error_from_within_or_without_stack_eval(gensymed_symbol_4,
			gensymed_symbol_5);
	}
	SVREF(gensymed_symbol_3,FIX((SI_Long)12L)) = T;
	return VALUES_1(Nil);
    }
    else if (EQ(initial_value_expression_from_formulas,
	    Quse_initial_value_expression_in_generic_simulation_formula)) {
	generic_simulation_formula = 
		get_simulation_specifier_to_use(variable_or_parameter);
	temp_1 = ISVREF(generic_simulation_formula,(SI_Long)16L);
	initial_value_expression = FIFTH(CAR(temp_1));
	sub_class_bit_vector = ISVREF(ISVREF(generic_simulation_formula,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Generic_simulation_formula_class_description,
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
	if (temp) {
	    if (CONSP(initial_value_expression)) {
		if (EQ(CAR(initial_value_expression),Qab_let)) {
		    temp_1 = THIRD(initial_value_expression);
		    if (CONSP(temp_1)) {
			temp_1 = THIRD(initial_value_expression);
			temp = EQ(CAR(temp_1),Qcurrent_parameter_value);
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = EQ(CAR(initial_value_expression),
			    Qcurrent_parameter_value);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		gensymed_symbol_3 = runtime_structure;
		gensymed_symbol_4 = ISVREF(gensymed_symbol_3,(SI_Long)16L);
		sub_class_bit_vector = ISVREF(ISVREF(variable_or_parameter,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Parameter_class_description,(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_1 = (SI_Long)1L;
		    gensymed_symbol_2 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		    gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		    temp = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    managed_number_or_value = ISVREF(variable_or_parameter,
			    (SI_Long)23L);
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			gensymed_symbol_5 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			gensymed_symbol_5 = aref1(managed_number_or_value,
				FIX((SI_Long)0L));
		    else if (text_string_p(managed_number_or_value))
			gensymed_symbol_5 = 
				copy_text_string(managed_number_or_value);
		    else
			gensymed_symbol_5 = managed_number_or_value;
		}
		else {
		    post_simulation_warning_for_not_parameter(variable_or_parameter);
		    gensymed_symbol_5 = Simulation_no_value;
		}
		type_specification = 
			type_specification_of_variable_or_parameter_value(gensymed_symbol_4);
		if (EQ(type_specification,Qfloat) && 
			FIXNUMP(gensymed_symbol_5)) {
		    store_managed_number_or_value_arg = 
			    (double)IFIX(gensymed_symbol_5);
		    svref_new_value = 
			    store_managed_number_or_value_function(ISVREF(gensymed_symbol_3,
			    (SI_Long)2L),
			    DOUBLE_TO_DOUBLE_FLOAT(store_managed_number_or_value_arg));
		    SVREF(gensymed_symbol_3,FIX((SI_Long)2L)) = 
			    svref_new_value;
		}
		else {
		    if (EQ(type_specification,Qinteger))
			temp_1 = FIXNUMP(gensymed_symbol_5) ? T : Nil;
		    else if (EQ(type_specification,Qlong))
			temp_1 = INLINE_LONG_P(gensymed_symbol_5) != 
				(SI_Long)0L ? T : Nil;
		    else if (EQ(type_specification,Qfloat))
			temp_1 = FLOATP(gensymed_symbol_5) ? T : Nil;
		    else if (EQ(type_specification,Qsymbol))
			temp_1 = gensymed_symbol_5 ? 
				(SYMBOLP(gensymed_symbol_5) ? T : Nil) : Qnil;
		    else if (EQ(type_specification,Qtext))
			temp_1 = text_string_p(gensymed_symbol_5);
		    else if (EQ(type_specification,Qtruth_value))
			temp_1 = FIXNUMP(gensymed_symbol_5) && 
				FIXNUM_LE(Falsity,gensymed_symbol_5) ? 
				(FIXNUM_LE(gensymed_symbol_5,Truth) ? T : 
				Nil) : Qnil;
		    else if (EQ(type_specification,Qboolean)) {
			if (FIXNUMP(gensymed_symbol_5)) {
			    temp_1 = FIXNUM_EQ(gensymed_symbol_5,Falsity) ?
				     T : Nil;
			    if (temp_1);
			    else
				temp_1 = FIXNUM_EQ(gensymed_symbol_5,
					Truth) ? T : Nil;
			}
			else
			    temp_1 = Nil;
		    }
		    else if (EQ(type_specification,Qnumber) || 
			    EQ(type_specification,Qinteger) || 
			    EQ(type_specification,Qfloat) || 
			    EQ(type_specification,Qlong) || 
			    lookup_global_or_kb_specific_property_value(type_specification,
			    Numeric_data_type_gkbprop)) {
			temp_1 = FLOATP(gensymed_symbol_5) ? T : Nil;
			if (temp_1);
			else
			    temp_1 = FIXNUMP(gensymed_symbol_5) ? T : Nil;
		    }
		    else
			temp_1 = Nil;
		    if (temp_1) {
			store_managed_number_or_value_arg_1 = 
				gensymed_symbol_5;
			svref_new_value = 
				store_managed_number_or_value_function(ISVREF(gensymed_symbol_3,
				(SI_Long)2L),
				store_managed_number_or_value_arg_1);
			SVREF(gensymed_symbol_3,FIX((SI_Long)2L)) = 
				svref_new_value;
		    }
		    else
			simulation_type_error_from_within_or_without_stack_eval(gensymed_symbol_4,
				gensymed_symbol_5);
		}
		SVREF(gensymed_symbol_3,FIX((SI_Long)12L)) = T;
		return VALUES_1(Nil);
	    }
	    else
		return get_formula_focal_entity_for_variable(variable_or_parameter);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(T);
}

static Object Qwork_completed_for_this_cycle;  /* work-completed-for-this-cycle */

static Object Qno_work_done_yet_for_this_cycle;  /* no-work-done-yet-for-this-cycle */

/* CHECK-FOR-SIMULATION-CHANGES */
Object check_for_simulation_changes()
{
    Object svref_arg_1;

    x_note_fn_call(184,127);
    if (simulation_changes_p()) {
	clear_simulation_resumption_stack();
	if (ISVREF(Current_model_runtime_info_qm,(SI_Long)12L)) {
	    abort_procedure_invocation(1,
		    ISVREF(Current_model_runtime_info_qm,(SI_Long)12L));
	    svref_arg_1 = Current_model_runtime_info_qm;
	    SVREF(svref_arg_1,FIX((SI_Long)12L)) = Nil;
	}
	if (simulating_externally_p() &&  
		!(EQ(ISVREF(Current_model_runtime_info_qm,(SI_Long)16L),
		Qwork_completed_for_this_cycle) || 
		EQ(ISVREF(Current_model_runtime_info_qm,(SI_Long)16L),
		Qno_work_done_yet_for_this_cycle))) {
	    svref_arg_1 = Current_model_runtime_info_qm;
	    SVREF(svref_arg_1,FIX((SI_Long)17L)) = T;
	}
	handle_editing_changes_effecting_simulation();
	svref_arg_1 = Current_model_runtime_info_qm;
	SVREF(svref_arg_1,FIX((SI_Long)25L)) = Nil;
	return re_initialize_variables_for_one_simulation_cycle();
    }
    else
	return VALUES_1(Nil);
}

/* SIMULATING-EXTERNALLY-P */
Object simulating_externally_p()
{
    x_note_fn_call(184,128);
    return VALUES_1(ISVREF(Current_model_runtime_info_qm,(SI_Long)14L));
}

/* SIMULATION-CHANGES-P */
Object simulation_changes_p()
{
    Object temp;

    x_note_fn_call(184,129);
    temp = ISVREF(Current_model_runtime_info_qm,(SI_Long)25L);
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1( 
		!TRUEP(rederive_set_empty_qm(ISVREF(Current_model_runtime_info_qm,
		(SI_Long)24L))) ? T : Nil);
}

static Object Qreset_new_value_computed_slot;  /* reset-new-value-computed-slot */

/* RE-INITIALIZE-VARIABLES-FOR-ONE-SIMULATION-CYCLE */
Object re_initialize_variables_for_one_simulation_cycle()
{
    x_note_fn_call(184,130);
    return for_each_variable_in_model(Qreset_new_value_computed_slot);
}

/* RESET-NEW-VALUE-COMPUTED-SLOT */
Object reset_new_value_computed_slot(variable_or_parameter)
    Object variable_or_parameter;
{
    Object simulation_info_qm, runtime_structure_qm;

    x_note_fn_call(184,131);
    simulation_info_qm = 
	    get_lookup_slot_value_given_default(variable_or_parameter,
	    Qsimulation_info_qm,Nil);
    runtime_structure_qm = simulation_info_qm ? ISVREF(simulation_info_qm,
	    (SI_Long)1L) : Nil;
    if (runtime_structure_qm)
	return VALUES_1(SVREF(runtime_structure_qm,FIX((SI_Long)12L)) = Nil);
    else
	return VALUES_1(Nil);
}

/* CLEAR-SIMULATION-RESUMPTION-STACK */
Object clear_simulation_resumption_stack()
{
    Object temp, cdddr_of_resumption_stack, temp_1, cdddr_new_value;

    x_note_fn_call(184,132);
    if (ISVREF(Current_model_runtime_info_qm,(SI_Long)10L)) {
	temp = ISVREF(Current_model_runtime_info_qm,(SI_Long)10L);
	cdddr_of_resumption_stack = CDDDR(temp);
      next_loop:
	temp_1 = ISVREF(Current_model_runtime_info_qm,(SI_Long)10L);
	M_FIRST(temp_1) = Nil;
	temp_1 = ISVREF(Current_model_runtime_info_qm,(SI_Long)10L);
	M_SECOND(temp_1) = Nil;
	temp_1 = ISVREF(Current_model_runtime_info_qm,(SI_Long)10L);
	M_THIRD(temp_1) = Nil;
	temp_1 = ISVREF(Current_model_runtime_info_qm,(SI_Long)10L);
	cdddr_new_value = Recycled_resumption_conses;
	M_CDDDR(temp_1) = cdddr_new_value;
	Recycled_resumption_conses = ISVREF(Current_model_runtime_info_qm,
		(SI_Long)10L);
	temp_1 = Current_model_runtime_info_qm;
	SVREF(temp_1,FIX((SI_Long)10L)) = cdddr_of_resumption_stack;
	if ( !TRUEP(ISVREF(Current_model_runtime_info_qm,(SI_Long)10L)))
	    goto end_loop;
	temp = ISVREF(Current_model_runtime_info_qm,(SI_Long)10L);
	cdddr_of_resumption_stack = CDDDR(temp);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qhandle_newly_simulated_variable_if_necessary;  /* handle-newly-simulated-variable-if-necessary */

static Object Qgenerate_new_runtime_simulation_formula;  /* generate-new-runtime-simulation-formula */

/* HANDLE-EDITING-CHANGES-EFFECTING-SIMULATION */
Object handle_editing_changes_effecting_simulation()
{
    x_note_fn_call(184,133);
    for_each_element_in_rederive_set(ISVREF(Current_model_runtime_info_qm,
	    (SI_Long)24L),Qhandle_newly_simulated_variable_if_necessary);
    for_each_element_in_rederive_set(ISVREF(Current_model_runtime_info_qm,
	    (SI_Long)24L),Qgenerate_new_runtime_simulation_formula);
    if ( 
	    !TRUEP(installation_set_empty_qm(ISVREF(Current_model_runtime_info_qm,
	    (SI_Long)21L))) &&  
	    !TRUEP(installation_set_empty_qm(ISVREF(Current_model_runtime_info_qm,
	    (SI_Long)24L))))
	sort_dependent_variable_info();
    return clear_edit_handling_lists();
}

/* HANDLE-NEWLY-SIMULATED-VARIABLE-IF-NECESSARY */
Object handle_newly_simulated_variable_if_necessary(variable)
    Object variable;
{
    Object simulation_info_qm;

    x_note_fn_call(184,134);
    simulation_info_qm = get_lookup_slot_value_given_default(variable,
	    Qsimulation_info_qm,Nil);
    if ( !(simulation_info_qm ? TRUEP(ISVREF(simulation_info_qm,
	    (SI_Long)1L)) : TRUEP(Nil))) {
	make_and_initialize_variable_simulation_runtime_structure(variable);
	add_variable_simulation_runtime_structure_to_runtime_info(variable);
	return begin_collecting_data_for_simulated_variable_if_appropriate(variable);
    }
    else
	return VALUES_1(Nil);
}

/* RECLAIM-VARIABLE-SIMULATION-RUNTIME-STRUCTURE */
Object reclaim_variable_simulation_runtime_structure(variable_simulation_runtime_structure)
    Object variable_simulation_runtime_structure;
{
    Object variable, simulation_info_qm;

    x_note_fn_call(184,135);
    variable = ISVREF(variable_simulation_runtime_structure,(SI_Long)16L);
    if (variable) {
	simulation_info_qm = get_lookup_slot_value_given_default(variable,
		Qsimulation_info_qm,Nil);
	if (simulation_info_qm)
	    SVREF(simulation_info_qm,FIX((SI_Long)1L)) = Nil;
    }
    reclaim_interval_at_which_to_send_value_to_inference_engine(ISVREF(variable_simulation_runtime_structure,
	    (SI_Long)14L));
    SVREF(variable_simulation_runtime_structure,FIX((SI_Long)14L)) = Nil;
    return reclaim_variable_simulation_runtime_structure_internal_1(variable_simulation_runtime_structure);
}

static Object Qsuppress_first_update;  /* suppress-first-update */

/* ADD-VARIABLE-SIMULATION-RUNTIME-STRUCTURE-TO-RUNTIME-INFO */
Object add_variable_simulation_runtime_structure_to_runtime_info(variable)
    Object variable;
{
    Object initializing_state_variables_qm, simulation_info_qm;
    Object variable_simulation_runtime_structure, gensymed_symbol;
    Object managed_number_or_value, gensymed_symbol_1, type_specification;
    Object svref_new_value, temp, store_managed_number_or_value_arg_1;
    double store_managed_number_or_value_arg;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(184,136);
    initialize_runtime_simulation_information_for_variable(variable);
    if (state_variable_p(variable)) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    initializing_state_variables_qm = T;
	    simulation_info_qm = 
		    get_lookup_slot_value_given_default(variable,
		    Qsimulation_info_qm,Nil);
	    variable_simulation_runtime_structure = simulation_info_qm ? 
		    ISVREF(simulation_info_qm,(SI_Long)1L) : Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Initializing_state_variables_qm,Qinitializing_state_variables_qm,initializing_state_variables_qm,
		    0);
	      SVREF(variable_simulation_runtime_structure,
		      FIX((SI_Long)25L)) = T;
	      compute_initial_value_for_state_variable(variable,
		      variable_simulation_runtime_structure);
	      SVREF(variable_simulation_runtime_structure,
		      FIX((SI_Long)25L)) = Nil;
	      gensymed_symbol = variable;
	      managed_number_or_value = 
		      ISVREF(variable_simulation_runtime_structure,
		      (SI_Long)2L);
	      if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		      (SI_Long)0L && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		      == (SI_Long)1L)
		  gensymed_symbol_1 = 
			  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			  (SI_Long)0L));
	      else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		      (SI_Long)0L && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		      == (SI_Long)1L)
		  gensymed_symbol_1 = aref1(managed_number_or_value,
			  FIX((SI_Long)0L));
	      else if (text_string_p(managed_number_or_value))
		  gensymed_symbol_1 = 
			  copy_text_string(managed_number_or_value);
	      else
		  gensymed_symbol_1 = managed_number_or_value;
	      type_specification = 
		      type_specification_of_variable_or_parameter_value(gensymed_symbol);
	      if (EQ(type_specification,Qfloat) && 
			  FIXNUMP(gensymed_symbol_1)) {
		  store_managed_number_or_value_arg = 
			  (double)IFIX(gensymed_symbol_1);
		  svref_new_value = 
			  store_managed_number_or_value_function(ISVREF(variable_simulation_runtime_structure,
			  (SI_Long)1L),
			  DOUBLE_TO_DOUBLE_FLOAT(store_managed_number_or_value_arg));
		  SVREF(variable_simulation_runtime_structure,
			  FIX((SI_Long)1L)) = svref_new_value;
	      }
	      else {
		  if (EQ(type_specification,Qinteger))
		      temp = FIXNUMP(gensymed_symbol_1) ? T : Nil;
		  else if (EQ(type_specification,Qlong))
		      temp = INLINE_LONG_P(gensymed_symbol_1) != 
			      (SI_Long)0L ? T : Nil;
		  else if (EQ(type_specification,Qfloat))
		      temp = FLOATP(gensymed_symbol_1) ? T : Nil;
		  else if (EQ(type_specification,Qsymbol))
		      temp = gensymed_symbol_1 ? 
			      (SYMBOLP(gensymed_symbol_1) ? T : Nil) : Qnil;
		  else if (EQ(type_specification,Qtext))
		      temp = text_string_p(gensymed_symbol_1);
		  else if (EQ(type_specification,Qtruth_value))
		      temp = FIXNUMP(gensymed_symbol_1) && 
			      FIXNUM_LE(Falsity,gensymed_symbol_1) ? 
			      (FIXNUM_LE(gensymed_symbol_1,Truth) ? T : 
			      Nil) : Qnil;
		  else if (EQ(type_specification,Qboolean)) {
		      if (FIXNUMP(gensymed_symbol_1)) {
			  temp = FIXNUM_EQ(gensymed_symbol_1,Falsity) ? T :
				   Nil;
			  if (temp);
			  else
			      temp = FIXNUM_EQ(gensymed_symbol_1,Truth) ? 
				      T : Nil;
		      }
		      else
			  temp = Nil;
		  }
		  else if (EQ(type_specification,Qnumber) || 
			  EQ(type_specification,Qinteger) || 
			  EQ(type_specification,Qfloat) || 
			  EQ(type_specification,Qlong) || 
			  lookup_global_or_kb_specific_property_value(type_specification,
			  Numeric_data_type_gkbprop)) {
		      temp = FLOATP(gensymed_symbol_1) ? T : Nil;
		      if (temp);
		      else
			  temp = FIXNUMP(gensymed_symbol_1) ? T : Nil;
		  }
		  else
		      temp = Nil;
		  if (temp) {
		      store_managed_number_or_value_arg_1 = gensymed_symbol_1;
		      svref_new_value = 
			      store_managed_number_or_value_function(ISVREF(variable_simulation_runtime_structure,
			      (SI_Long)1L),
			      store_managed_number_or_value_arg_1);
		      SVREF(variable_simulation_runtime_structure,
			      FIX((SI_Long)1L)) = svref_new_value;
		  }
		  else
		      simulation_type_error_from_within_or_without_stack_eval(gensymed_symbol,
			      gensymed_symbol_1);
	      }
	      result = VALUES_1(SVREF(variable_simulation_runtime_structure,
		      FIX((SI_Long)13L)) = Qsuppress_first_update);
	    POP_SPECIAL();
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* GENERATE-NEW-RUNTIME-SIMULATION-FORMULA */
Object generate_new_runtime_simulation_formula(variable)
    Object variable;
{
    Object simulation_info_qm;

    x_note_fn_call(184,137);
    simulation_info_qm = get_lookup_slot_value_given_default(variable,
	    Qsimulation_info_qm,Nil);
    return generate_and_set_runtime_formula(variable,simulation_info_qm ? 
	    ISVREF(simulation_info_qm,(SI_Long)1L) : Nil);
}

/* SHUTDOWN-SIMULATOR */
Object shutdown_simulator varargs_1(int, n)
{
    Object model_runtime_info_qm, model_definition_qm, synchronous_models;
    Object as_fast_as_possible_models, current_model_runtime_info_qm;
    Object current_model_definition_qm, code, current_model_queue_qm;
    char temp;
    Declare_varargs_nonrelocating;
    Declare_special(3);
    Object result;

    x_note_fn_call(184,138);
    INIT_ARGS_nonrelocating();
    model_runtime_info_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    model_definition_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(model_runtime_info_qm)) {
	synchronous_models = 
		copy_list_using_gensym_conses_1(ISVREF(Synchronous_model_queue,
		(SI_Long)1L));
	as_fast_as_possible_models = 
		copy_list_using_gensym_conses_1(ISVREF(As_fast_as_possible_model_queue,
		(SI_Long)1L));
	shutdown_models_in_list(synchronous_models);
	shutdown_models_in_list(as_fast_as_possible_models);
	reclaim_gensym_list_1(synchronous_models);
	return reclaim_gensym_list_1(as_fast_as_possible_models);
    }
    else {
	current_model_runtime_info_qm = Nil;
	current_model_definition_qm = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_model_definition_qm,Qcurrent_model_definition_qm,current_model_definition_qm,
		2);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_model_runtime_info_qm,Qcurrent_model_runtime_info_qm,current_model_runtime_info_qm,
		  1);
	    if (model_runtime_info_qm) {
		Current_model_runtime_info_qm = model_runtime_info_qm;
		Current_model_definition_qm = model_definition_qm;
	    }
	    else {
		if (ISVREF(Simulation_parameters,(SI_Long)24L)) {
		    code = M_CAR(M_CDR(Edit_type_alias_mapping));
		    temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)4096L) 
			    != (SI_Long)0L : TRUEP(Qnil);
		    if (temp);
		    else
			temp = TRUEP(M_CAR(M_CDR(Cache_g1_semantics_graph)));
		    temp =  !temp;
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    Current_model_runtime_info_qm = Main_model_runtime_info;
		    Current_model_definition_qm = Nil;
		}
	    }
	    if (Current_model_runtime_info_qm) {
		current_model_queue_qm = 
			get_model_queue_for_model(Current_model_runtime_info_qm);
		PUSH_SPECIAL_WITH_SYMBOL(Current_model_queue_qm,Qcurrent_model_queue_qm,current_model_queue_qm,
			0);
		  result = shutdown_simulator_1();
		POP_SPECIAL();
	    }
	    else
		result = VALUES_1(Nil);
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
}

static Object Qmodel_simulation_status;  /* model-simulation-status */

static Object Qnot_running;        /* not-running */

/* SHUTDOWN-MODELS-IN-LIST */
Object shutdown_models_in_list(model_list)
    Object model_list;
{
    Object model_runtime_info, ab_loop_list_, current_model_runtime_info_qm;
    Object current_model_definition_qm, code, current_model_queue_qm;
    char temp;
    Declare_special(3);

    x_note_fn_call(184,139);
    model_runtime_info = Nil;
    ab_loop_list_ = model_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    model_runtime_info = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    current_model_runtime_info_qm = Nil;
    current_model_definition_qm = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_model_definition_qm,Qcurrent_model_definition_qm,current_model_definition_qm,
	    2);
      PUSH_SPECIAL_WITH_SYMBOL(Current_model_runtime_info_qm,Qcurrent_model_runtime_info_qm,current_model_runtime_info_qm,
	      1);
	if (model_runtime_info) {
	    Current_model_runtime_info_qm = model_runtime_info;
	    Current_model_definition_qm = ISVREF(model_runtime_info,
		    (SI_Long)28L);
	}
	else {
	    if (ISVREF(Simulation_parameters,(SI_Long)24L)) {
		code = M_CAR(M_CDR(Edit_type_alias_mapping));
		temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)4096L) != 
			(SI_Long)0L : TRUEP(Qnil);
		if (temp);
		else
		    temp = TRUEP(M_CAR(M_CDR(Cache_g1_semantics_graph)));
		temp =  !temp;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		Current_model_runtime_info_qm = Main_model_runtime_info;
		Current_model_definition_qm = Nil;
	    }
	}
	if (Current_model_runtime_info_qm) {
	    current_model_queue_qm = 
		    get_model_queue_for_model(Current_model_runtime_info_qm);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_model_queue_qm,Qcurrent_model_queue_qm,current_model_queue_qm,
		    0);
	      if (Current_model_definition_qm)
		  change_slot_value(3,Current_model_definition_qm,
			  Qmodel_simulation_status,Qnot_running);
	      shutdown_simulator_1();
	    POP_SPECIAL();
	}
      POP_SPECIAL();
    POP_SPECIAL();
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qcontinue_data_server_data_acceptance;  /* continue-data-server-data-acceptance */

/* SHUTDOWN-SIMULATOR-1 */
Object shutdown_simulator_1()
{
    Object temp, simulation_procedure_invocation_for_model_qm;
    Object structure_being_reclaimed, svref_arg_2;
    Object def_structure_schedule_task_variable, svref_new_value, task, ctask;
    Object p, v, q;
    char g2_p;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(184,140);
    remove_model_from_simulation(Current_model_runtime_info_qm);
    if ( !EQ(ISVREF(Current_model_runtime_info_qm,(SI_Long)29L),
	    Qneeds_to_be_initialized)) {
	clear_variables_that_need_simulated_values();
	update_shortest_simulation_time_increment_for_all_models();
	clear_edit_handling_lists();
	clear_runtime_structures_caches();
	reclaim_simulation_update_table();
	temp = Current_model_runtime_info_qm;
	SVREF(temp,FIX((SI_Long)13L)) = T;
	simulation_procedure_invocation_for_model_qm = 
		ISVREF(Current_model_runtime_info_qm,(SI_Long)12L);
	if (simulation_procedure_invocation_for_model_qm) {
	    if (Evaluating_simulator_procedure_qm && 
		    EQ(Evaluating_simulator_procedure_qm,
		    Current_model_definition_qm)) {
		restart_simulator_after_procedure_1(Current_model_definition_qm);
		SVREF(simulation_procedure_invocation_for_model_qm,
			FIX((SI_Long)25L)) = Nil;
		SVREF(simulation_procedure_invocation_for_model_qm,
			FIX((SI_Long)26L)) = Nil;
	    }
	    else
		abort_procedure_invocation(1,
			simulation_procedure_invocation_for_model_qm);
	    temp = Current_model_runtime_info_qm;
	    SVREF(temp,FIX((SI_Long)12L)) = Nil;
	}
	temp = Current_model_runtime_info_qm;
	SVREF(temp,FIX((SI_Long)17L)) = Nil;
	shutdown_externally_simulated_portion_of_model();
    }
    if (System_is_running || System_has_paused) {
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
	    temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    SVREF(Nil,FIX((SI_Long)0L)) = temp;
	    temp = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = Nil;
	}
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
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = T;
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
	task = def_structure_schedule_task_variable;
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = -1.0;
	DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	temp = ISVREF(Data_server_parameters,(SI_Long)22L);
	SVREF(task,FIX((SI_Long)4L)) = temp;
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)10L)) = Nil;
	g2_p =  !TRUEP(Nil);
	SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
		Current_real_time,(SI_Long)0L);
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	SVREF(task,FIX((SI_Long)7L)) = Qcontinue_data_server_data_acceptance;
	temp = SYMBOL_FUNCTION(Qcontinue_data_server_data_acceptance);
	SVREF(task,FIX((SI_Long)8L)) = temp;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)2L);
	temp = lookup_kb_specific_property_value(Qsimulator_data_server,
		Data_server_kbprop);
	SVREF(task,FIX((SI_Long)13L)) = temp;
	temp = Current_g2_time;
	SVREF(task,FIX((SI_Long)14L)) = temp;
	ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
	if (ctask);
	else
	    ctask = System_is_running;
	p = ISVREF(task,(SI_Long)4L);
	v = ctask ? Current_task_queue_vector : Deferred_task_queue_vector;
	q = ISVREF(v,IFIX(p));
	SVREF(task,FIX((SI_Long)11L)) = q;
	temp = constant_queue_push_right(q,task);
	SVREF(task,FIX((SI_Long)6L)) = temp;
	if (ctask && FIXNUM_LT(p,Priority_of_next_task))
	    Priority_of_next_task = p;
	return VALUES_1(task);
    }
    else
	return VALUES_1(Nil);
}

/* RECLAIM-SIMULATION-UPDATE-TABLE */
Object reclaim_simulation_update_table()
{
    Object variable_group_update_structure, ab_loop_list_, svref_arg_1;

    x_note_fn_call(184,141);
    variable_group_update_structure = Nil;
    ab_loop_list_ = ISVREF(Current_model_runtime_info_qm,(SI_Long)23L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    variable_group_update_structure = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_variable_group_update_structure_completely(variable_group_update_structure);
    goto next_loop;
  end_loop:;
    reclaim_eval_list_1(ISVREF(Current_model_runtime_info_qm,(SI_Long)23L));
    svref_arg_1 = Current_model_runtime_info_qm;
    return VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)23L)) = Nil);
}

/* CLEAR-EDIT-HANDLING-LISTS */
Object clear_edit_handling_lists()
{
    x_note_fn_call(184,142);
    return clear_rederive_set(ISVREF(Current_model_runtime_info_qm,
	    (SI_Long)24L));
}

static Object Qentity;             /* entity */

static Object Qstatement;          /* statement */

/* CLEAR-RUNTIME-STRUCTURES-CACHES */
Object clear_runtime_structures_caches()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1;
    Object entity_involved_in_simulation_qm, edit_cache_qm, ab_node_stack_;
    Object ab_current_node_, gensymed_symbol, ab_skip_list_form_;
    Object ab_skip_list_p_, ab_next_node_, ab_tail_node_, ab_current_alist_;
    Object ab_entry_cons_, ab_connection_, ab_connection_item_;
    Object connection_involved_in_simulation_qm, temp_1;
    Object ab_less_than_branch_qm_, statement_involved_in_simulation_qm;
    char temp;
    Declare_special(2);
    Object result;

    x_note_fn_call(184,143);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    entity_involved_in_simulation_qm = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,1);
      ab_loopvar_ = collect_subclasses(Qentity);
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
      entity_involved_in_simulation_qm = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      edit_cache_qm = ISVREF(entity_involved_in_simulation_qm,(SI_Long)19L);
      if (edit_cache_qm) {
	  if ( !TRUEP(ISVREF(edit_cache_qm,(SI_Long)3L))) {
	      ISVREF(entity_involved_in_simulation_qm,(SI_Long)19L) = Nil;
	      reclaim_edit_cache(edit_cache_qm);
	  }
	  else {
	      reclaim_eval_list_1(ISVREF(edit_cache_qm,(SI_Long)2L));
	      SVREF(edit_cache_qm,FIX((SI_Long)2L)) = Nil;
	  }
      }
      scope_conses = Scope_conses;
      ab_node_stack_ = Nil;
      ab_current_node_ = Nil;
      gensymed_symbol = 
	      ACCESS_ONCE(ISVREF(entity_involved_in_simulation_qm,
	      (SI_Long)14L));
      gensymed_symbol = gensymed_symbol ? 
	      ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
      ab_skip_list_form_ = gensymed_symbol;
      ab_skip_list_p_ = Nil;
      ab_next_node_ = Nil;
      ab_tail_node_ = Nil;
      ab_current_alist_ = Nil;
      ab_entry_cons_ = Nil;
      ab_connection_ = Nil;
      ab_connection_item_ = Nil;
      connection_involved_in_simulation_qm = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	gensymed_symbol = CDR(ab_skip_list_form_);
	if (CONSP(gensymed_symbol)) {
	    temp_1 = M_CAR(gensymed_symbol);
	    temp = SIMPLE_VECTOR_P(temp_1);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    temp_1 = M_CDR(gensymed_symbol);
	    ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
	}
	else
	    ab_skip_list_p_ = Nil;
	if (ab_skip_list_p_) {
	    ab_next_node_ = 
		    ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
		    (SI_Long)0L),(SI_Long)0L));
	    ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
	    if (EQ(ab_next_node_,ab_tail_node_))
		ab_next_node_ = Nil;
	}
	else
	    ab_next_node_ = CDR(ab_skip_list_form_);
      next_loop_2:
      next_loop_3:
	if (ab_current_alist_) {
	    ab_entry_cons_ = M_CAR(ab_current_alist_);
	    ab_connection_ = M_CAR(ab_entry_cons_);
	    ab_connection_item_ = M_CDR(ab_entry_cons_);
	    ab_current_alist_ = M_CDR(ab_current_alist_);
	}
	else if (ab_skip_list_p_) {
	    if (ab_next_node_) {
		ab_current_node_ = ab_next_node_;
		ab_next_node_ = 
			ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node_,
			(SI_Long)0L),(SI_Long)0L));
		if (EQ(ab_next_node_,ab_tail_node_))
		    ab_next_node_ = Nil;
		ab_connection_ = ISVREF(ab_current_node_,(SI_Long)2L);
		ab_connection_item_ = ISVREF(ab_current_node_,(SI_Long)3L);
	    }
	    else
		ab_current_node_ = Nil;
	}
	else {
	    if (ab_next_node_) {
		ab_current_node_ = ab_next_node_;
		ab_less_than_branch_qm_ = Nil;
	      next_loop_4:
		ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
		if ( !TRUEP(ab_less_than_branch_qm_))
		    goto end_loop_2;
		ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
		ab_current_node_ = ab_less_than_branch_qm_;
		goto next_loop_4;
	      end_loop_2:;
	    }
	    else if (ab_node_stack_) {
		ab_next_node_ = ab_node_stack_;
		ab_current_node_ = M_CAR(ab_node_stack_);
		ab_node_stack_ = M_CDR(ab_node_stack_);
	    }
	    else
		ab_current_node_ = Nil;
	    if (ab_current_node_) {
		ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
		ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
		ab_entry_cons_ = M_CAR(ab_current_alist_);
		ab_connection_ = M_CAR(ab_entry_cons_);
		ab_connection_item_ = M_CDR(ab_entry_cons_);
		ab_current_alist_ = M_CDR(ab_current_alist_);
	    }
	}
	if ( !TRUEP(ab_current_node_) || ab_current_node_ && 
		ab_connection_ && EQ(ISVREF(ab_connection_,(SI_Long)3L),
		entity_involved_in_simulation_qm))
	    goto end_1;
	goto next_loop_3;
      end_loop_3:
      end_1:
	if ( !TRUEP(ab_current_node_))
	    goto end_loop_4;
	connection_involved_in_simulation_qm = ab_connection_;
	edit_cache_qm = ISVREF(connection_involved_in_simulation_qm,
		(SI_Long)8L);
	if (edit_cache_qm) {
	    if ( !TRUEP(ISVREF(edit_cache_qm,(SI_Long)3L))) {
		SVREF(connection_involved_in_simulation_qm,
			FIX((SI_Long)8L)) = Nil;
		reclaim_edit_cache(edit_cache_qm);
	    }
	    else {
		reclaim_eval_list_1(ISVREF(edit_cache_qm,(SI_Long)2L));
		SVREF(edit_cache_qm,FIX((SI_Long)2L)) = Nil;
	    }
	}
	goto next_loop_2;
      end_loop_4:;
      POP_SPECIAL();
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    statement_involved_in_simulation_qm = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qstatement);
    next_loop_5:
      if ( !TRUEP(ab_loopvar__1)) {
	next_loop_6:
	  if ( !TRUEP(ab_loopvar_))
	      goto end_loop_5;
	  ab_loopvar__1 = 
		  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		  Instances_specific_to_this_class_kbprop);
	  ab_loopvar_ = M_CDR(ab_loopvar_);
	  if (ab_loopvar__1)
	      goto end_loop_5;
	  goto next_loop_6;
	end_loop_5:
	  temp =  !TRUEP(ab_loopvar__1);
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  goto end_loop_6;
      statement_involved_in_simulation_qm = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      edit_cache_qm = ISVREF(statement_involved_in_simulation_qm,(SI_Long)19L);
      if (edit_cache_qm) {
	  if ( !TRUEP(ISVREF(edit_cache_qm,(SI_Long)3L))) {
	      ISVREF(statement_involved_in_simulation_qm,(SI_Long)19L) = Nil;
	      reclaim_edit_cache(edit_cache_qm);
	  }
	  else {
	      reclaim_eval_list_1(ISVREF(edit_cache_qm,(SI_Long)2L));
	      SVREF(edit_cache_qm,FIX((SI_Long)2L)) = Nil;
	  }
      }
      goto next_loop_5;
    end_loop_6:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* CLEAR-TAINTED-VARIABLES */
Object clear_tainted_variables varargs_1(int, n)
{
    Object invalidate_values_qm, svref_arg_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(184,144);
    INIT_ARGS_nonrelocating();
    invalidate_values_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    svref_arg_1 = Current_model_runtime_info_qm;
    SVREF(svref_arg_1,FIX((SI_Long)31L)) = Nil;
    return clear_tainted_variables_1(2,
	    ISVREF(Current_model_runtime_info_qm,(SI_Long)32L),
	    invalidate_values_qm);
}

/* CLEAR-TAINTED-VARIABLES-1 */
Object clear_tainted_variables_1 varargs_1(int, n)
{
    Object tainted_variables;
    Object invalidate_values_qm, variable, ab_loop_list_, simulation_info_qm;
    Object temp, runtime_structure, value_computed_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(184,145);
    INIT_ARGS_nonrelocating();
    tainted_variables = REQUIRED_ARG_nonrelocating();
    invalidate_values_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    variable = Nil;
    ab_loop_list_ = tainted_variables;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    variable = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    simulation_info_qm = get_lookup_slot_value_given_default(variable,
	    Qsimulation_info_qm,Nil);
    temp = simulation_info_qm ? ISVREF(simulation_info_qm,(SI_Long)1L) : Nil;
    SVREF(temp,FIX((SI_Long)24L)) = Nil;
    if (invalidate_values_qm) {
	simulation_info_qm = get_lookup_slot_value_given_default(variable,
		Qsimulation_info_qm,Nil);
	runtime_structure = simulation_info_qm ? ISVREF(simulation_info_qm,
		(SI_Long)1L) : Nil;
	value_computed_qm = ISVREF(runtime_structure,(SI_Long)12L);
	temp = NUMBERP(value_computed_qm) ? FIXNUM_SUB1(value_computed_qm) 
		: Nil;
	SVREF(runtime_structure,FIX((SI_Long)12L)) = temp;
    }
    goto next_loop;
  end_loop:;
    temp = Current_model_runtime_info_qm;
    SVREF(temp,FIX((SI_Long)32L)) = Nil;
    return reclaim_simulate_list_1(tainted_variables);
}

/* CLEAR-VARIABLES-THAT-NEED-SIMULATED-VALUES */
Object clear_variables_that_need_simulated_values()
{
    x_note_fn_call(184,146);
    clear_tainted_variables(0);
    return clear_variables_that_need_simulated_values_1(ISVREF(Current_model_runtime_info_qm,
	    (SI_Long)30L));
}

/* CLEAR-VARIABLES-THAT-NEED-SIMULATED-VALUES-1 */
Object clear_variables_that_need_simulated_values_1(variables_that_need_simulated_values)
    Object variables_that_need_simulated_values;
{
    Object variable, ab_loop_list_, variable_simulation_runtime_structure_qm;
    Object simulation_info_qm, svref_arg_1;

    x_note_fn_call(184,147);
    variable = Nil;
    ab_loop_list_ = variables_that_need_simulated_values;
    variable_simulation_runtime_structure_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    variable = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    simulation_info_qm = get_lookup_slot_value_given_default(variable,
	    Qsimulation_info_qm,Nil);
    variable_simulation_runtime_structure_qm = simulation_info_qm ? 
	    ISVREF(simulation_info_qm,(SI_Long)1L) : Nil;
    if (variable_simulation_runtime_structure_qm)
	SVREF(variable_simulation_runtime_structure_qm,FIX((SI_Long)23L)) 
		= Nil;
    goto next_loop;
  end_loop:;
    svref_arg_1 = Current_model_runtime_info_qm;
    SVREF(svref_arg_1,FIX((SI_Long)30L)) = Nil;
    return reclaim_simulate_list_1(variables_that_need_simulated_values);
}

Object The_type_description_of_variable_group_update_structure = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_variable_group_update_structures, Qchain_of_available_variable_group_update_structures);

DEFINE_VARIABLE_WITH_SYMBOL(Variable_group_update_structure_count, Qvariable_group_update_structure_count);

Object Chain_of_available_variable_group_update_structures_vector = UNBOUND;

/* VARIABLE-GROUP-UPDATE-STRUCTURE-STRUCTURE-MEMORY-USAGE */
Object variable_group_update_structure_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(184,148);
    temp = Variable_group_update_structure_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)7L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-VARIABLE-GROUP-UPDATE-STRUCTURE-COUNT */
Object outstanding_variable_group_update_structure_count()
{
    Object def_structure_variable_group_update_structure_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(184,149);
    gensymed_symbol = IFIX(Variable_group_update_structure_count);
    def_structure_variable_group_update_structure_variable = 
	    Chain_of_available_variable_group_update_structures;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_variable_group_update_structure_variable))
	goto end_loop;
    def_structure_variable_group_update_structure_variable = 
	    ISVREF(def_structure_variable_group_update_structure_variable,
	    (SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-VARIABLE-GROUP-UPDATE-STRUCTURE-1 */
Object reclaim_variable_group_update_structure_1(variable_group_update_structure)
    Object variable_group_update_structure;
{
    Object temp, svref_arg_2;

    x_note_fn_call(184,150);
    inline_note_reclaim_cons(variable_group_update_structure,Nil);
    temp = 
	    ISVREF(Chain_of_available_variable_group_update_structures_vector,
	    IFIX(Current_thread_index));
    SVREF(variable_group_update_structure,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_variable_group_update_structures_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = variable_group_update_structure;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-VARIABLE-GROUP-UPDATE-STRUCTURE */
Object reclaim_structure_for_variable_group_update_structure(variable_group_update_structure)
    Object variable_group_update_structure;
{
    x_note_fn_call(184,151);
    return reclaim_variable_group_update_structure_1(variable_group_update_structure);
}

static Object Qg2_defstruct_structure_name_variable_group_update_structure_g2_struct;  /* g2-defstruct-structure-name::variable-group-update-structure-g2-struct */

/* MAKE-PERMANENT-VARIABLE-GROUP-UPDATE-STRUCTURE-STRUCTURE-INTERNAL */
Object make_permanent_variable_group_update_structure_structure_internal()
{
    Object def_structure_variable_group_update_structure_variable;
    Object defstruct_g2_variable_group_update_structure_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(184,152);
    def_structure_variable_group_update_structure_variable = Nil;
    atomic_incff_symval(Qvariable_group_update_structure_count,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_variable_group_update_structure_variable = Nil;
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
	defstruct_g2_variable_group_update_structure_variable = the_array;
	SVREF(defstruct_g2_variable_group_update_structure_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_variable_group_update_structure_g2_struct;
	def_structure_variable_group_update_structure_variable = 
		defstruct_g2_variable_group_update_structure_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_variable_group_update_structure_variable);
}

/* MAKE-VARIABLE-GROUP-UPDATE-STRUCTURE-1 */
Object make_variable_group_update_structure_1()
{
    Object def_structure_variable_group_update_structure_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(184,153);
    def_structure_variable_group_update_structure_variable = 
	    ISVREF(Chain_of_available_variable_group_update_structures_vector,
	    IFIX(Current_thread_index));
    if (def_structure_variable_group_update_structure_variable) {
	svref_arg_1 = 
		Chain_of_available_variable_group_update_structures_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_variable_group_update_structure_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_variable_group_update_structure_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_variable_group_update_structure_g2_struct;
    }
    else
	def_structure_variable_group_update_structure_variable = 
		make_permanent_variable_group_update_structure_structure_internal();
    inline_note_allocate_cons(def_structure_variable_group_update_structure_variable,
	    Nil);
    SVREF(def_structure_variable_group_update_structure_variable,
	    FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_variable_group_update_structure_variable,
	    FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_variable_group_update_structure_variable,
	    FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_variable_group_update_structure_variable,
	    FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_variable_group_update_structure_variable,
	    FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_variable_group_update_structure_variable,
	    FIX((SI_Long)6L)) = Nil;
    return VALUES_1(def_structure_variable_group_update_structure_variable);
}

/* RECLAIM-POSSIBLE-VARIABLE-GROUP-UPDATE-STRUCTURE */
Object reclaim_possible_variable_group_update_structure(variable_group_update_structure_qm)
    Object variable_group_update_structure_qm;
{
    x_note_fn_call(184,154);
    if (SIMPLE_VECTOR_P(variable_group_update_structure_qm) && 
	    EQ(ISVREF(variable_group_update_structure_qm,(SI_Long)0L),
	    Qg2_defstruct_structure_name_variable_group_update_structure_g2_struct))
	reclaim_variable_group_update_structure_1(variable_group_update_structure_qm);
    return VALUES_1(Nil);
}

Object The_type_description_of_group_index_structure = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_group_index_structures, Qchain_of_available_group_index_structures);

DEFINE_VARIABLE_WITH_SYMBOL(Group_index_structure_count, Qgroup_index_structure_count);

Object Chain_of_available_group_index_structures_vector = UNBOUND;

/* GROUP-INDEX-STRUCTURE-STRUCTURE-MEMORY-USAGE */
Object group_index_structure_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(184,155);
    temp = Group_index_structure_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)2L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-GROUP-INDEX-STRUCTURE-COUNT */
Object outstanding_group_index_structure_count()
{
    Object def_structure_group_index_structure_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(184,156);
    gensymed_symbol = IFIX(Group_index_structure_count);
    def_structure_group_index_structure_variable = 
	    Chain_of_available_group_index_structures;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_group_index_structure_variable))
	goto end_loop;
    def_structure_group_index_structure_variable = 
	    ISVREF(def_structure_group_index_structure_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-GROUP-INDEX-STRUCTURE-1 */
Object reclaim_group_index_structure_1(group_index_structure)
    Object group_index_structure;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(184,157);
    inline_note_reclaim_cons(group_index_structure,Nil);
    structure_being_reclaimed = group_index_structure;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_possible_variable_group_update_structure(ISVREF(group_index_structure,
	      (SI_Long)1L));
      SVREF(group_index_structure,FIX((SI_Long)1L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_group_index_structures_vector,
	    IFIX(Current_thread_index));
    SVREF(group_index_structure,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_group_index_structures_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = group_index_structure;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GROUP-INDEX-STRUCTURE */
Object reclaim_structure_for_group_index_structure(group_index_structure)
    Object group_index_structure;
{
    x_note_fn_call(184,158);
    return reclaim_group_index_structure_1(group_index_structure);
}

static Object Qg2_defstruct_structure_name_group_index_structure_g2_struct;  /* g2-defstruct-structure-name::group-index-structure-g2-struct */

/* MAKE-PERMANENT-GROUP-INDEX-STRUCTURE-STRUCTURE-INTERNAL */
Object make_permanent_group_index_structure_structure_internal()
{
    Object def_structure_group_index_structure_variable;
    Object defstruct_g2_group_index_structure_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(184,159);
    def_structure_group_index_structure_variable = Nil;
    atomic_incff_symval(Qgroup_index_structure_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_group_index_structure_variable = Nil;
	gensymed_symbol = (SI_Long)2L;
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
	defstruct_g2_group_index_structure_variable = the_array;
	SVREF(defstruct_g2_group_index_structure_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_group_index_structure_g2_struct;
	def_structure_group_index_structure_variable = 
		defstruct_g2_group_index_structure_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_group_index_structure_variable);
}

/* MAKE-GROUP-INDEX-STRUCTURE-1 */
Object make_group_index_structure_1()
{
    Object def_structure_group_index_structure_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(184,160);
    def_structure_group_index_structure_variable = 
	    ISVREF(Chain_of_available_group_index_structures_vector,
	    IFIX(Current_thread_index));
    if (def_structure_group_index_structure_variable) {
	svref_arg_1 = Chain_of_available_group_index_structures_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_group_index_structure_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_group_index_structure_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_group_index_structure_g2_struct;
    }
    else
	def_structure_group_index_structure_variable = 
		make_permanent_group_index_structure_structure_internal();
    inline_note_allocate_cons(def_structure_group_index_structure_variable,
	    Nil);
    SVREF(def_structure_group_index_structure_variable,FIX((SI_Long)1L)) = Nil;
    return VALUES_1(def_structure_group_index_structure_variable);
}

/* SET-UP-UPDATE-TIMING-FOR-VARIABLE */
Object set_up_update_timing_for_variable(variable_simulation_runtime_structure,
	    override_time_increment_for_update_qm)
    Object variable_simulation_runtime_structure;
    Object override_time_increment_for_update_qm;
{
    Object time_increment_for_variable, gensymed_symbol, gensymed_symbol_1;
    Object integer_portion, fraction_portion, temp;
    Object variable_group_update_structure, ab_loop_list_, macro_time_1;
    Object micro_time_1, macro_time_2, micro_time_2;
    Object new_variable_group_update_structure, index_structure_for_new_group;
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_2, temp_2;
    char temp_1;
    Object result;

    x_note_fn_call(184,161);
    time_increment_for_variable = override_time_increment_for_update_qm;
    if (time_increment_for_variable);
    else
	time_increment_for_variable = 
		current_default_simulation_time_increment();
    gensymed_symbol = Simulation_time_accumulator;
    gensymed_symbol_1 = time_increment_for_variable;
    if (INTEGERP(gensymed_symbol_1)) {
	SVREF(gensymed_symbol,FIX((SI_Long)1L)) = gensymed_symbol_1;
	ISVREF(gensymed_symbol,(SI_Long)2L) = FIX((SI_Long)0L);
    }
    else {
	result = ltruncate(lfloat(gensymed_symbol_1,float_constant),_);
	MVS_2(result,integer_portion,fraction_portion);
	SVREF(gensymed_symbol,FIX((SI_Long)1L)) = integer_portion;
	temp = l_round(ltimes(fraction_portion,
		Fraction_modulus_of_compound_fixnum_simulation_time),_);
	SVREF(gensymed_symbol,FIX((SI_Long)2L)) = temp;
    }
    variable_group_update_structure = Nil;
    ab_loop_list_ = ISVREF(Current_model_runtime_info_qm,(SI_Long)23L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    variable_group_update_structure = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = Simulation_time_accumulator;
    gensymed_symbol_1 = ISVREF(variable_group_update_structure,(SI_Long)2L);
    macro_time_1 = ISVREF(gensymed_symbol,(SI_Long)1L);
    micro_time_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
    macro_time_2 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
    micro_time_2 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
    if (FIXNUM_EQ(macro_time_1,macro_time_2) && FIXNUM_EQ(micro_time_1,
	    micro_time_2) ? (ISVREF(variable_group_update_structure,
	    (SI_Long)6L) ? TRUEP(override_time_increment_for_update_qm) :  
	    !TRUEP(override_time_increment_for_update_qm)) : TRUEP(Nil)) {
	temp = ISVREF(variable_group_update_structure,(SI_Long)1L);
	SVREF(variable_simulation_runtime_structure,FIX((SI_Long)11L)) = temp;
	temp_1 = TRUEP(T);
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp_1 = TRUEP(Qnil);
  end_1:;
    if ( !temp_1) {
	new_variable_group_update_structure = 
		make_variable_group_update_structure_1();
	index_structure_for_new_group = make_group_index_structure_1();
	temp = override_time_increment_for_update_qm ? T : Nil;
	SVREF(new_variable_group_update_structure,FIX((SI_Long)6L)) = temp;
	SVREF(variable_simulation_runtime_structure,FIX((SI_Long)11L)) = 
		index_structure_for_new_group;
	SVREF(index_structure_for_new_group,FIX((SI_Long)1L)) = 
		new_variable_group_update_structure;
	gensymed_symbol = ISVREF(Current_model_runtime_info_qm,(SI_Long)23L);
	gensymed_symbol_1 = new_variable_group_update_structure;
	if ( !TRUEP(memq_function(gensymed_symbol_1,gensymed_symbol))) {
	    temp = Current_model_runtime_info_qm;
	    new_cons = ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		svref_arg_1 = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_eval_conses_vector,
			IFIX(Current_thread_index)))) {
		    svref_arg_1 = Available_eval_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(svref_arg_1,svref_arg_2) = Nil;
		}
		gensymed_symbol_2 = new_cons;
	    }
	    else
		gensymed_symbol_2 = Nil;
	    if ( !TRUEP(gensymed_symbol_2))
		gensymed_symbol_2 = replenish_eval_cons_pool();
	    M_CAR(gensymed_symbol_2) = gensymed_symbol_1;
	    M_CDR(gensymed_symbol_2) = gensymed_symbol;
	    inline_note_allocate_cons(gensymed_symbol_2,Qeval);
	    SVREF(temp,FIX((SI_Long)23L)) = gensymed_symbol_2;
	}
	SVREF(new_variable_group_update_structure,FIX((SI_Long)1L)) = 
		index_structure_for_new_group;
	temp = make_compound_fixnum_simulation_time_1();
	SVREF(new_variable_group_update_structure,FIX((SI_Long)2L)) = temp;
	temp = make_compound_fixnum_simulation_time_1();
	SVREF(new_variable_group_update_structure,FIX((SI_Long)3L)) = temp;
	temp = make_compound_fixnum_simulation_time_1();
	SVREF(new_variable_group_update_structure,FIX((SI_Long)5L)) = temp;
	gensymed_symbol = ISVREF(new_variable_group_update_structure,
		(SI_Long)2L);
	gensymed_symbol_1 = Simulation_time_accumulator;
	temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	SVREF(gensymed_symbol,FIX((SI_Long)2L)) = temp;
	temp = ISVREF(gensymed_symbol_1,(SI_Long)1L);
	SVREF(gensymed_symbol,FIX((SI_Long)1L)) = temp;
	gensymed_symbol = ISVREF(Current_model_runtime_info_qm,(SI_Long)8L);
	gensymed_symbol_1 = ISVREF(Current_model_runtime_info_qm,(SI_Long)8L);
	gensymed_symbol_2 = ISVREF(new_variable_group_update_structure,
		(SI_Long)2L);
	macro_time_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
	micro_time_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	macro_time_2 = ISVREF(gensymed_symbol_2,(SI_Long)1L);
	micro_time_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	if (FIXNUM_LT(macro_time_1,macro_time_2))
	    temp_2 = T;
	else if (FIXNUM_EQ(macro_time_1,macro_time_2))
	    temp_2 = FIXNUM_LT(micro_time_1,micro_time_2) ? T : Nil;
	else
	    temp_2 = Qnil;
	gensymed_symbol_1 = temp_2 ? gensymed_symbol_1 : gensymed_symbol_2;
	temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	SVREF(gensymed_symbol,FIX((SI_Long)2L)) = temp;
	temp = ISVREF(gensymed_symbol_1,(SI_Long)1L);
	SVREF(gensymed_symbol,FIX((SI_Long)1L)) = temp;
	if (override_time_increment_for_update_qm) {
	    if (IFIX(ISVREF(ISVREF(Current_model_runtime_info_qm,
		    (SI_Long)33L),(SI_Long)1L)) < (SI_Long)0L) {
		gensymed_symbol = ISVREF(Current_model_runtime_info_qm,
			(SI_Long)33L);
		gensymed_symbol_1 = override_time_increment_for_update_qm;
		if (INTEGERP(gensymed_symbol_1)) {
		    SVREF(gensymed_symbol,FIX((SI_Long)1L)) = 
			    gensymed_symbol_1;
		    ISVREF(gensymed_symbol,(SI_Long)2L) = FIX((SI_Long)0L);
		}
		else {
		    result = ltruncate(lfloat(gensymed_symbol_1,
			    float_constant),_);
		    MVS_2(result,integer_portion,fraction_portion);
		    SVREF(gensymed_symbol,FIX((SI_Long)1L)) = integer_portion;
		    temp = l_round(ltimes(fraction_portion,
			    Fraction_modulus_of_compound_fixnum_simulation_time),
			    _);
		    SVREF(gensymed_symbol,FIX((SI_Long)2L)) = temp;
		}
	    }
	    else {
		gensymed_symbol = Simulation_time_accumulator;
		gensymed_symbol_1 = override_time_increment_for_update_qm;
		if (INTEGERP(gensymed_symbol_1)) {
		    SVREF(gensymed_symbol,FIX((SI_Long)1L)) = 
			    gensymed_symbol_1;
		    ISVREF(gensymed_symbol,(SI_Long)2L) = FIX((SI_Long)0L);
		}
		else {
		    result = ltruncate(lfloat(gensymed_symbol_1,
			    float_constant),_);
		    MVS_2(result,integer_portion,fraction_portion);
		    SVREF(gensymed_symbol,FIX((SI_Long)1L)) = integer_portion;
		    temp = l_round(ltimes(fraction_portion,
			    Fraction_modulus_of_compound_fixnum_simulation_time),
			    _);
		    SVREF(gensymed_symbol,FIX((SI_Long)2L)) = temp;
		}
		gensymed_symbol = Simulation_time_accumulator;
		gensymed_symbol_1 = ISVREF(Current_model_runtime_info_qm,
			(SI_Long)33L);
		macro_time_1 = ISVREF(gensymed_symbol,(SI_Long)1L);
		micro_time_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		macro_time_2 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
		micro_time_2 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		if (FIXNUM_LT(macro_time_1,macro_time_2))
		    temp_2 = T;
		else if (FIXNUM_EQ(macro_time_1,macro_time_2))
		    temp_2 = FIXNUM_LT(micro_time_1,micro_time_2) ? T : Nil;
		else
		    temp_2 = Qnil;
		if (temp_2) {
		    gensymed_symbol = ISVREF(Current_model_runtime_info_qm,
			    (SI_Long)33L);
		    gensymed_symbol_1 = Simulation_time_accumulator;
		    temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		    SVREF(gensymed_symbol,FIX((SI_Long)2L)) = temp;
		    temp = ISVREF(gensymed_symbol_1,(SI_Long)1L);
		    SVREF(gensymed_symbol,FIX((SI_Long)1L)) = temp;
		}
	    }
	}
	SVREF(new_variable_group_update_structure,FIX((SI_Long)4L)) = T;
	gensymed_symbol = ISVREF(new_variable_group_update_structure,
		(SI_Long)3L);
	gensymed_symbol_1 = ISVREF(Current_model_runtime_info_qm,(SI_Long)4L);
	temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	SVREF(gensymed_symbol,FIX((SI_Long)2L)) = temp;
	temp = ISVREF(gensymed_symbol_1,(SI_Long)1L);
	SVREF(gensymed_symbol,FIX((SI_Long)1L)) = temp;
	gensymed_symbol = ISVREF(new_variable_group_update_structure,
		(SI_Long)3L);
	gensymed_symbol_1 = ISVREF(new_variable_group_update_structure,
		(SI_Long)3L);
	gensymed_symbol_2 = ISVREF(new_variable_group_update_structure,
		(SI_Long)2L);
	macro_time_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
	micro_time_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	macro_time_2 = ISVREF(gensymed_symbol_2,(SI_Long)1L);
	micro_time_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	if (IFIX(micro_time_2) != (SI_Long)0L) {
	    micro_time_1 = FIXNUM_ADD(micro_time_1,micro_time_2);
	    if (FIXNUM_GE(micro_time_1,
		    Fraction_modulus_of_compound_fixnum_simulation_time)) {
		temp = FIXNUM_MINUS(micro_time_1,
			Fraction_modulus_of_compound_fixnum_simulation_time);
		SVREF(gensymed_symbol,FIX((SI_Long)2L)) = temp;
		macro_time_1 = FIXNUM_ADD1(macro_time_1);
	    }
	    else
		SVREF(gensymed_symbol,FIX((SI_Long)2L)) = micro_time_1;
	}
	else {
	    if (SVREF(gensymed_symbol,FIX((SI_Long)2L)) = micro_time_1);
	}
	temp = FIXNUM_ADD(macro_time_1,macro_time_2);
	SVREF(gensymed_symbol,FIX((SI_Long)1L)) = temp;
	gensymed_symbol = ISVREF(new_variable_group_update_structure,
		(SI_Long)5L);
	gensymed_symbol_1 = ISVREF(new_variable_group_update_structure,
		(SI_Long)3L);
	temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	SVREF(gensymed_symbol,FIX((SI_Long)2L)) = temp;
	temp = ISVREF(gensymed_symbol_1,(SI_Long)1L);
	return VALUES_1(SVREF(gensymed_symbol,FIX((SI_Long)1L)) = temp);
    }
    else
	return VALUES_1(Nil);
}

/* GET-NON-OVERRIDE-VARIABLE-GROUP-UPDATE-STRUCTURE */
Object get_non_override_variable_group_update_structure(model_runtime_info)
    Object model_runtime_info;
{
    Object variable_group_update_structure, ab_loop_list_;

    x_note_fn_call(184,162);
    variable_group_update_structure = Nil;
    ab_loop_list_ = ISVREF(model_runtime_info,(SI_Long)23L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    variable_group_update_structure = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ISVREF(variable_group_update_structure,(SI_Long)6L)))
	return VALUES_1(variable_group_update_structure);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* RECLAIM-VARIABLE-GROUP-UPDATE-STRUCTURE-COMPLETELY */
Object reclaim_variable_group_update_structure_completely(variable_group_update_structure)
    Object variable_group_update_structure;
{
    x_note_fn_call(184,163);
    reclaim_group_index_structure_1(ISVREF(variable_group_update_structure,
	    (SI_Long)1L));
    reclaim_compound_fixnum_simulation_time(ISVREF(variable_group_update_structure,
	    (SI_Long)2L));
    return reclaim_compound_fixnum_simulation_time(ISVREF(variable_group_update_structure,
	    (SI_Long)3L));
}

/* ADD-SHORTEST-SIMULATION-TIME-INCREMENT-FOR-ALL-MODELS */
Object add_shortest_simulation_time_increment_for_all_models(shortest_time_increment_for_model)
    Object shortest_time_increment_for_model;
{
    Object temp, svref_new_value, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, macro_time_1, micro_time_1, macro_time_2;
    Object micro_time_2, temp_1;

    x_note_fn_call(184,164);
    if ( !TRUEP(ISVREF(Current_model_queue_qm,(SI_Long)3L))) {
	temp = Current_model_queue_qm;
	svref_new_value = initialize_compound_simulation_time();
	SVREF(temp,FIX((SI_Long)3L)) = svref_new_value;
	temp = Current_model_queue_qm;
	svref_new_value = initialize_compound_simulation_time();
	SVREF(temp,FIX((SI_Long)6L)) = svref_new_value;
	gensymed_symbol = ISVREF(Current_model_queue_qm,(SI_Long)3L);
	gensymed_symbol_1 = ISVREF(Current_model_runtime_info_qm,(SI_Long)7L);
	temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	SVREF(gensymed_symbol,FIX((SI_Long)2L)) = temp;
	temp = ISVREF(gensymed_symbol_1,(SI_Long)1L);
	SVREF(gensymed_symbol,FIX((SI_Long)1L)) = temp;
	gensymed_symbol = ISVREF(Current_model_queue_qm,(SI_Long)6L);
	gensymed_symbol_1 = ISVREF(Current_model_runtime_info_qm,(SI_Long)7L);
	temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	SVREF(gensymed_symbol,FIX((SI_Long)2L)) = temp;
	temp = ISVREF(gensymed_symbol_1,(SI_Long)1L);
	SVREF(gensymed_symbol,FIX((SI_Long)1L)) = temp;
    }
    if ( !TRUEP(ISVREF(Current_model_queue_qm,(SI_Long)4L))) {
	temp = Current_model_queue_qm;
	svref_new_value = initialize_compound_simulation_time();
	SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
	gensymed_symbol = ISVREF(Current_model_queue_qm,(SI_Long)4L);
	gensymed_symbol_1 = shortest_time_increment_for_model;
	temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	SVREF(gensymed_symbol,FIX((SI_Long)2L)) = temp;
	temp = ISVREF(gensymed_symbol_1,(SI_Long)1L);
	return VALUES_1(SVREF(gensymed_symbol,FIX((SI_Long)1L)) = temp);
    }
    else {
	gensymed_symbol = ISVREF(Current_model_queue_qm,(SI_Long)4L);
	gensymed_symbol_1 = ISVREF(Current_model_queue_qm,(SI_Long)4L);
	gensymed_symbol_2 = shortest_time_increment_for_model;
	macro_time_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
	micro_time_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	macro_time_2 = ISVREF(gensymed_symbol_2,(SI_Long)1L);
	micro_time_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	if (FIXNUM_LT(macro_time_1,macro_time_2))
	    temp_1 = T;
	else if (FIXNUM_EQ(macro_time_1,macro_time_2))
	    temp_1 = FIXNUM_LT(micro_time_1,micro_time_2) ? T : Nil;
	else
	    temp_1 = Qnil;
	gensymed_symbol_1 = temp_1 ? gensymed_symbol_1 : gensymed_symbol_2;
	temp = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	SVREF(gensymed_symbol,FIX((SI_Long)2L)) = temp;
	temp = ISVREF(gensymed_symbol_1,(SI_Long)1L);
	return VALUES_1(SVREF(gensymed_symbol,FIX((SI_Long)1L)) = temp);
    }
}

/* UPDATE-SHORTEST-SIMULATION-TIME-INCREMENT-FOR-ALL-MODELS */
Object update_shortest_simulation_time_increment_for_all_models()
{
    Object svref_arg_1, model_runtime_info, ab_loop_list_;

    x_note_fn_call(184,165);
    if ( !TRUEP(ISVREF(Current_model_queue_qm,(SI_Long)1L))) {
	reclaim_compound_fixnum_simulation_time(ISVREF(Current_model_queue_qm,
		(SI_Long)3L));
	reclaim_compound_fixnum_simulation_time(ISVREF(Current_model_queue_qm,
		(SI_Long)6L));
	svref_arg_1 = Current_model_queue_qm;
	SVREF(svref_arg_1,FIX((SI_Long)3L)) = Nil;
	svref_arg_1 = Current_model_queue_qm;
	SVREF(svref_arg_1,FIX((SI_Long)6L)) = Nil;
    }
    reclaim_compound_fixnum_simulation_time(ISVREF(Current_model_queue_qm,
	    (SI_Long)4L));
    svref_arg_1 = Current_model_queue_qm;
    SVREF(svref_arg_1,FIX((SI_Long)4L)) = Nil;
    model_runtime_info = Nil;
    ab_loop_list_ = ISVREF(Current_model_queue_qm,(SI_Long)1L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    model_runtime_info = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    add_shortest_simulation_time_increment_for_all_models(ISVREF(model_runtime_info,
	    (SI_Long)8L));
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* GET-CURRENT-TIME-IN-SIMULATION-ENVIRONMENT */
Object get_current_time_in_simulation_environment()
{
    Object x2, time_for_models_in_queue, base_time_for_models_in_queue;
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, macro_time_1;
    Object micro_time_1, macro_time_2, micro_time_2, result_negative_p;
    Object micro_time_1_temp, macro_time_1_temp, integer_portion;
    Object fraction_portion, svref_new_value_1;
    SI_Long svref_new_value;
    char temp;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(184,166);
    if (Current_model_runtime_info_qm)
	return VALUES_1(ISVREF(Current_model_runtime_info_qm,(SI_Long)5L));
    else {
	if (SIMPLE_VECTOR_P(Evaluating_simulator_procedure_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Evaluating_simulator_procedure_qm)) 
		> (SI_Long)2L &&  
		!EQ(ISVREF(Evaluating_simulator_procedure_qm,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(Evaluating_simulator_procedure_qm,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    return VALUES_1(ISVREF(model_runtime_info_function_qm(Evaluating_simulator_procedure_qm),
		    (SI_Long)5L));
	else {
	    time_for_models_in_queue = ISVREF(Synchronous_model_queue,
		    (SI_Long)3L);
	    base_time_for_models_in_queue = ISVREF(Synchronous_model_queue,
		    (SI_Long)6L);
	    if (time_for_models_in_queue && base_time_for_models_in_queue) {
		gensymed_symbol = Simulation_time_accumulator;
		gensymed_symbol_1 = time_for_models_in_queue;
		gensymed_symbol_2 = base_time_for_models_in_queue;
		macro_time_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
		micro_time_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		macro_time_2 = ISVREF(gensymed_symbol_2,(SI_Long)1L);
		micro_time_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
		result_negative_p = Nil;
		if (FIXNUM_GT(macro_time_2,macro_time_1) || 
			FIXNUM_EQ(macro_time_1,macro_time_2) && 
			FIXNUM_GT(micro_time_2,micro_time_1)) {
		    micro_time_1_temp = micro_time_2;
		    macro_time_1_temp = macro_time_2;
		    micro_time_2 = micro_time_1;
		    micro_time_1 = micro_time_1_temp;
		    macro_time_2 = macro_time_1;
		    macro_time_1 = macro_time_1_temp;
		    result_negative_p = T;
		}
		if (IFIX(micro_time_2) != (SI_Long)0L) {
		    if (FIXNUM_GT(micro_time_2,micro_time_1)) {
			macro_time_1 = FIXNUM_SUB1(macro_time_1);
			micro_time_1 = 
				FIXNUM_MINUS(FIXNUM_ADD(micro_time_1,
				Fraction_modulus_of_compound_fixnum_simulation_time),
				micro_time_2);
		    }
		    else
			micro_time_1 = FIXNUM_MINUS(micro_time_1,micro_time_2);
		}
		macro_time_1 = FIXNUM_MINUS(macro_time_1,macro_time_2);
		if (result_negative_p) {
		    svref_new_value = IFIX(micro_time_1) * (SI_Long)-1L;
		    ISVREF(gensymed_symbol,(SI_Long)2L) = FIX(svref_new_value);
		    svref_new_value = IFIX(macro_time_1) * (SI_Long)-1L;
		    ISVREF(gensymed_symbol,(SI_Long)1L) = FIX(svref_new_value);
		}
		else {
		    SVREF(gensymed_symbol,FIX((SI_Long)2L)) = micro_time_1;
		    SVREF(gensymed_symbol,FIX((SI_Long)1L)) = macro_time_1;
		}
	    }
	    else {
		if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		    gensymed_symbol = Simulation_time_accumulator;
		    gensymed_symbol_1 = float_constant;
		    if (INTEGERP(gensymed_symbol_1)) {
			SVREF(gensymed_symbol,FIX((SI_Long)1L)) = 
				gensymed_symbol_1;
			ISVREF(gensymed_symbol,(SI_Long)2L) = FIX((SI_Long)0L);
		    }
		    else {
			result = ltruncate(lfloat(gensymed_symbol_1,
				float_constant),_);
			MVS_2(result,integer_portion,fraction_portion);
			SVREF(gensymed_symbol,FIX((SI_Long)1L)) = 
				integer_portion;
			svref_new_value_1 = 
				l_round(ltimes(fraction_portion,
				Fraction_modulus_of_compound_fixnum_simulation_time),
				_);
			SVREF(gensymed_symbol,FIX((SI_Long)2L)) = 
				svref_new_value_1;
		    }
		}
		POP_LOCAL_ALLOCATION(0,0);
	    }
	    return VALUES_1(Simulation_time_accumulator);
	}
    }
}

/* GET-CURRENT-TIME-IN-SIMULATION-ENVIRONMENT-AND-CONVERT-TO-G2-TIME */
Object get_current_time_in_simulation_environment_and_convert_to_g2_time()
{
    Object gensym_time_value, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, macro_time_1, micro_time_1, macro_time_2;
    Object micro_time_2, svref_new_value, x2, model_runtime_info;
    char temp;
    double gensymed_symbol_3, gensymed_symbol_4;

    x_note_fn_call(184,167);
    gensym_time_value = Nil;
    if (Current_model_runtime_info_qm) {
	gensymed_symbol = Simulation_time_accumulator;
	gensymed_symbol_1 = ISVREF(Current_model_runtime_info_qm,(SI_Long)5L);
	gensymed_symbol_2 = ISVREF(Current_model_runtime_info_qm,(SI_Long)7L);
	macro_time_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
	micro_time_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	macro_time_2 = ISVREF(gensymed_symbol_2,(SI_Long)1L);
	micro_time_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	if (IFIX(micro_time_2) != (SI_Long)0L) {
	    micro_time_1 = FIXNUM_ADD(micro_time_1,micro_time_2);
	    if (FIXNUM_GE(micro_time_1,
		    Fraction_modulus_of_compound_fixnum_simulation_time)) {
		svref_new_value = FIXNUM_MINUS(micro_time_1,
			Fraction_modulus_of_compound_fixnum_simulation_time);
		SVREF(gensymed_symbol,FIX((SI_Long)2L)) = svref_new_value;
		macro_time_1 = FIXNUM_ADD1(macro_time_1);
	    }
	    else
		SVREF(gensymed_symbol,FIX((SI_Long)2L)) = micro_time_1;
	}
	else {
	    if (SVREF(gensymed_symbol,FIX((SI_Long)2L)) = micro_time_1);
	}
	svref_new_value = FIXNUM_ADD(macro_time_1,macro_time_2);
	SVREF(gensymed_symbol,FIX((SI_Long)1L)) = svref_new_value;
	gensym_time_value = ISVREF(Simulation_time_accumulator,(SI_Long)1L);
    }
    else {
	if (SIMPLE_VECTOR_P(Evaluating_simulator_procedure_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Evaluating_simulator_procedure_qm)) 
		> (SI_Long)2L &&  
		!EQ(ISVREF(Evaluating_simulator_procedure_qm,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(Evaluating_simulator_procedure_qm,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    model_runtime_info = 
		    model_runtime_info_function_qm(Evaluating_simulator_procedure_qm);
	    gensymed_symbol = Simulation_time_accumulator;
	    gensymed_symbol_1 = ISVREF(model_runtime_info,(SI_Long)5L);
	    gensymed_symbol_2 = ISVREF(model_runtime_info,(SI_Long)7L);
	    macro_time_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
	    micro_time_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	    macro_time_2 = ISVREF(gensymed_symbol_2,(SI_Long)1L);
	    micro_time_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    if (IFIX(micro_time_2) != (SI_Long)0L) {
		micro_time_1 = FIXNUM_ADD(micro_time_1,micro_time_2);
		if (FIXNUM_GE(micro_time_1,
			Fraction_modulus_of_compound_fixnum_simulation_time)) {
		    svref_new_value = FIXNUM_MINUS(micro_time_1,
			    Fraction_modulus_of_compound_fixnum_simulation_time);
		    SVREF(gensymed_symbol,FIX((SI_Long)2L)) = svref_new_value;
		    macro_time_1 = FIXNUM_ADD1(macro_time_1);
		}
		else
		    SVREF(gensymed_symbol,FIX((SI_Long)2L)) = micro_time_1;
	    }
	    else {
		if (SVREF(gensymed_symbol,FIX((SI_Long)2L)) = micro_time_1);
	    }
	    svref_new_value = FIXNUM_ADD(macro_time_1,macro_time_2);
	    SVREF(gensymed_symbol,FIX((SI_Long)1L)) = svref_new_value;
	    gensym_time_value = ISVREF(Simulation_time_accumulator,
		    (SI_Long)1L);
	}
	else {
	    gensymed_symbol = Simulation_time_accumulator;
	    gensymed_symbol_1 = ISVREF(Synchronous_model_queue,(SI_Long)3L);
	    svref_new_value = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	    SVREF(gensymed_symbol,FIX((SI_Long)2L)) = svref_new_value;
	    svref_new_value = ISVREF(gensymed_symbol_1,(SI_Long)1L);
	    SVREF(gensymed_symbol,FIX((SI_Long)1L)) = svref_new_value;
	    gensym_time_value = ISVREF(Simulation_time_accumulator,
		    (SI_Long)1L);
	}
    }
    gensymed_symbol_3 = (double)IFIX(FIXNUM_MINUS(gensym_time_value,
	    Gensym_time_at_start)) + DFLOAT_ISAREF_1(G2_time_at_start,
	    (SI_Long)0L);
    gensymed_symbol = ISVREF(Simulation_time_accumulator,(SI_Long)2L);
    gensymed_symbol_4 = IFIX(gensymed_symbol) == (SI_Long)0L ? 0.0 : 
	    (double)IFIX(gensymed_symbol) / 100000.0;
    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(gensymed_symbol_3 + 
	    gensymed_symbol_4));
}

/* GET-SIMULATION-ENVIRONMENT-GENSYM-TIME-FOR-VARIABLE-AS-FLOAT */
Object get_simulation_environment_gensym_time_for_variable_as_float(variable_or_parameter)
    Object variable_or_parameter;
{
    Object model_runtime_info_qm, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, macro_time_1, micro_time_1, macro_time_2;
    Object micro_time_2, temp, integer_portion, micro_time;
    double aref_new_value;

    x_note_fn_call(184,168);
    model_runtime_info_qm = 
	    get_lookup_slot_value_given_default(variable_or_parameter,
	    Qsimulation_info_qm,Nil) ? 
	    get_model_runtime_info_for_variable(variable_or_parameter) : Nil;
    if (model_runtime_info_qm) {
	gensymed_symbol = Simulation_time_accumulator;
	gensymed_symbol_1 = ISVREF(model_runtime_info_qm,(SI_Long)5L);
	gensymed_symbol_2 = ISVREF(model_runtime_info_qm,(SI_Long)7L);
	macro_time_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
	micro_time_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	macro_time_2 = ISVREF(gensymed_symbol_2,(SI_Long)1L);
	micro_time_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	if (IFIX(micro_time_2) != (SI_Long)0L) {
	    micro_time_1 = FIXNUM_ADD(micro_time_1,micro_time_2);
	    if (FIXNUM_GE(micro_time_1,
		    Fraction_modulus_of_compound_fixnum_simulation_time)) {
		temp = FIXNUM_MINUS(micro_time_1,
			Fraction_modulus_of_compound_fixnum_simulation_time);
		SVREF(gensymed_symbol,FIX((SI_Long)2L)) = temp;
		macro_time_1 = FIXNUM_ADD1(macro_time_1);
	    }
	    else
		SVREF(gensymed_symbol,FIX((SI_Long)2L)) = micro_time_1;
	}
	else {
	    if (SVREF(gensymed_symbol,FIX((SI_Long)2L)) = micro_time_1);
	}
	temp = FIXNUM_ADD(macro_time_1,macro_time_2);
	SVREF(gensymed_symbol,FIX((SI_Long)1L)) = temp;
	gensymed_symbol = Simulation_time_accumulator;
	integer_portion = ISVREF(gensymed_symbol,(SI_Long)1L);
	micro_time = ISVREF(gensymed_symbol,(SI_Long)2L);
	if (IFIX(micro_time) == (SI_Long)0L) {
	    temp = Simulation_time_managed_float;
	    aref_new_value = (double)IFIX(integer_portion);
	    DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	}
	else {
	    temp = Simulation_time_managed_float;
	    aref_new_value = (double)IFIX(integer_portion) + 
		    (double)IFIX(micro_time) / 100000.0;
	    DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	}
	return VALUES_1(Simulation_time_managed_float);
    }
    else
	return VALUES_1(Nil);
}

/* COLLECT-ONE-SHOT-DATA-FOR-SIMULATOR */
Object collect_one_shot_data_for_simulator varargs_1(int, n)
{
    Object variable;
    Object model_runtime_info_qm, model_definition_qm;
    Object current_model_runtime_info_qm, current_model_definition_qm, code;
    char temp;
    Declare_varargs_nonrelocating;
    Declare_special(2);
    Object result;

    x_note_fn_call(184,169);
    INIT_ARGS_nonrelocating();
    variable = REQUIRED_ARG_nonrelocating();
    model_runtime_info_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    model_definition_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    current_model_runtime_info_qm = Nil;
    current_model_definition_qm = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_model_definition_qm,Qcurrent_model_definition_qm,current_model_definition_qm,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Current_model_runtime_info_qm,Qcurrent_model_runtime_info_qm,current_model_runtime_info_qm,
	      0);
	if (model_runtime_info_qm) {
	    Current_model_runtime_info_qm = model_runtime_info_qm;
	    Current_model_definition_qm = model_definition_qm;
	}
	else {
	    if (ISVREF(Simulation_parameters,(SI_Long)24L)) {
		code = M_CAR(M_CDR(Edit_type_alias_mapping));
		temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)4096L) != 
			(SI_Long)0L : TRUEP(Qnil);
		if (temp);
		else
		    temp = TRUEP(M_CAR(M_CDR(Cache_g1_semantics_graph)));
		temp =  !temp;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		Current_model_runtime_info_qm = Main_model_runtime_info;
		Current_model_definition_qm = Nil;
	    }
	}
	if (Current_model_runtime_info_qm)
	    result = collect_one_shot_data_for_simulator_1(variable);
	else
	    result = VALUES_1(Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qsend_one_value;     /* send-one-value */

static Object Qfloat_array;        /* float-array */

/* COLLECT-ONE-SHOT-DATA-FOR-SIMULATOR-1 */
Object collect_one_shot_data_for_simulator_1(variable)
    Object variable;
{
    Object code, simulation_info_qm, variable_simulation_runtime_structure_qm;
    Object interval_at_which_to_send_value_to_inference_engine;
    Object current_computation_frame, current_computation_instance;
    Object gensymed_symbol, gensymed_symbol_1, managed_number_or_value;
    Object simulation_value, amf_available_array_cons_qm, amf_array, temp_1;
    Object temp_2, amf_result, new_float;
    char temp;
    double temp_3, aref_new_value;
    Declare_special(2);
    Object result;

    x_note_fn_call(184,170);
    if (ISVREF(Simulation_parameters,(SI_Long)24L)) {
	code = M_CAR(M_CDR(Edit_type_alias_mapping));
	temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)4096L) != 
		(SI_Long)0L : TRUEP(Qnil);
	if (temp);
	else
	    temp = TRUEP(M_CAR(M_CDR(Cache_g1_semantics_graph)));
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	simulation_info_qm = get_lookup_slot_value_given_default(variable,
		Qsimulation_info_qm,Nil);
	variable_simulation_runtime_structure_qm = simulation_info_qm ? 
		ISVREF(simulation_info_qm,(SI_Long)1L) : Nil;
	interval_at_which_to_send_value_to_inference_engine = 
		variable_simulation_runtime_structure_qm ? 
		ISVREF(variable_simulation_runtime_structure_qm,
		(SI_Long)14L) : Nil;
	current_computation_frame = variable;
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		1);
	  current_computation_instance = 
		  lookup_kb_specific_property_value(Qsimulator_data_server,
		  Data_server_kbprop);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_instance,Qcurrent_computation_instance,current_computation_instance,
		  0);
	    if (variable_simulation_runtime_structure_qm &&  
		    !EQ(CAR(interval_at_which_to_send_value_to_inference_engine),
		    Qsend_one_value)) {
		temp = TRUEP(ISVREF(Current_model_runtime_info_qm,
			(SI_Long)1L));
		if (temp);
		else {
		    gensymed_symbol = variable_simulation_runtime_structure_qm;
		    gensymed_symbol_1 = ISVREF(ISVREF(gensymed_symbol,
			    (SI_Long)11L),(SI_Long)1L);
		    temp =  !(gensymed_symbol_1 && 
			    ISVREF(gensymed_symbol_1,(SI_Long)4L) ? 
			    (EQ(ISVREF(gensymed_symbol,(SI_Long)13L),
			    Qsuppress_first_update) ? TRUEP(Nil) : 
			    TRUEP(T)) : TRUEP(Nil));
		}
		if (temp) {
		    managed_number_or_value = 
			    ISVREF(variable_simulation_runtime_structure_qm,
			    (SI_Long)1L);
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			simulation_value = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			simulation_value = aref1(managed_number_or_value,
				FIX((SI_Long)0L));
		    else if (text_string_p(managed_number_or_value))
			simulation_value = 
				copy_text_string(managed_number_or_value);
		    else
			simulation_value = managed_number_or_value;
		    if ( !EQ(simulation_value,Simulation_no_value))
			result = put_simulated_value_to_inference_engine(3,
				variable,simulation_value,Nil);
		    else
			result = VALUES_1(Nil);
		}
		else {
		    gensymed_symbol = 
			    interval_at_which_to_send_value_to_inference_engine;
		    if (gensymed_symbol &&  !EQ(CAR(gensymed_symbol),
			    Qsend_one_value)) {
			amf_available_array_cons_qm = 
				ISVREF(Vector_of_simple_float_array_pools,
				(SI_Long)1L);
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
				temp_1 = 
					Available_float_array_conses_tail_vector;
				temp_2 = Current_thread_index;
				SVREF(temp_1,temp_2) = 
					amf_available_array_cons_qm;
			    }
			    else {
				temp_1 = Available_float_array_conses_vector;
				temp_2 = Current_thread_index;
				SVREF(temp_1,temp_2) = 
					amf_available_array_cons_qm;
				temp_1 = 
					Available_float_array_conses_tail_vector;
				temp_2 = Current_thread_index;
				SVREF(temp_1,temp_2) = 
					amf_available_array_cons_qm;
			    }
			    M_CDR(amf_available_array_cons_qm) = Nil;
			    amf_result = amf_array;
			}
			else {
			    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
				    FIX((SI_Long)1L));
			    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
				    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
			    amf_result = 
				    generate_float_vector(FIX((SI_Long)1L));
			}
			new_float = amf_result;
			temp_3 = 
				DOUBLE_FLOAT_TO_DOUBLE(Seconds_from_1900_to_1970);
			aref_new_value = DFLOAT_ISAREF_1(Current_g2_time,
				(SI_Long)0L) - 
				(DFLOAT_ISAREF_1(Gensym_base_time_as_managed_float,
				(SI_Long)0L) - temp_3);
			DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
			temp_1 = simulate_cons_1(Qsend_one_value,
				simulate_cons_1(new_float,
				interval_at_which_to_send_value_to_inference_engine));
		    }
		    else {
			amf_available_array_cons_qm = 
				ISVREF(Vector_of_simple_float_array_pools,
				(SI_Long)1L);
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
				temp_1 = 
					Available_float_array_conses_tail_vector;
				temp_2 = Current_thread_index;
				SVREF(temp_1,temp_2) = 
					amf_available_array_cons_qm;
			    }
			    else {
				temp_1 = Available_float_array_conses_vector;
				temp_2 = Current_thread_index;
				SVREF(temp_1,temp_2) = 
					amf_available_array_cons_qm;
				temp_1 = 
					Available_float_array_conses_tail_vector;
				temp_2 = Current_thread_index;
				SVREF(temp_1,temp_2) = 
					amf_available_array_cons_qm;
			    }
			    M_CDR(amf_available_array_cons_qm) = Nil;
			    amf_result = amf_array;
			}
			else {
			    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
				    FIX((SI_Long)1L));
			    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
				    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
			    amf_result = 
				    generate_float_vector(FIX((SI_Long)1L));
			}
			new_float = amf_result;
			temp_3 = 
				DOUBLE_FLOAT_TO_DOUBLE(Seconds_from_1900_to_1970);
			aref_new_value = DFLOAT_ISAREF_1(Current_g2_time,
				(SI_Long)0L) - 
				(DFLOAT_ISAREF_1(Gensym_base_time_as_managed_float,
				(SI_Long)0L) - temp_3);
			DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
			temp_1 = simulate_cons_1(Qsend_one_value,new_float);
		    }
		    result = VALUES_1(SVREF(variable_simulation_runtime_structure_qm,
			    FIX((SI_Long)14L)) = temp_1);
		}
	    }
	    else
		result = VALUES_1(Nil);
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* BEGIN-COLLECTING-DATA-FOR-SIMULATOR */
Object begin_collecting_data_for_simulator varargs_1(int, n)
{
    Object variable, interval;
    Object model_runtime_info_qm, model_definition_qm, interval_to_use;
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float, current_model_runtime_info_qm;
    Object current_model_definition_qm, code;
    char temp_2;
    double aref_new_value;
    Declare_varargs_nonrelocating;
    Declare_special(2);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(184,171);
    INIT_ARGS_nonrelocating();
    variable = REQUIRED_ARG_nonrelocating();
    interval = REQUIRED_ARG_nonrelocating();
    model_runtime_info_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    model_definition_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    interval_to_use = Nil;
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
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
	aref_new_value = INLINE_DOUBLE_FLOAT_VECTOR_P(interval) != 
		(SI_Long)0L && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(interval)) 
		== (SI_Long)1L ? DFLOAT_ISAREF_1(interval,(SI_Long)0L) : 
		(double)IFIX(interval);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	interval_to_use = new_float;
    }
    POP_LOCAL_ALLOCATION(0,0);
    current_model_runtime_info_qm = Nil;
    current_model_definition_qm = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_model_definition_qm,Qcurrent_model_definition_qm,current_model_definition_qm,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Current_model_runtime_info_qm,Qcurrent_model_runtime_info_qm,current_model_runtime_info_qm,
	      0);
	if (model_runtime_info_qm) {
	    Current_model_runtime_info_qm = model_runtime_info_qm;
	    Current_model_definition_qm = model_definition_qm;
	}
	else {
	    if (ISVREF(Simulation_parameters,(SI_Long)24L)) {
		code = M_CAR(M_CDR(Edit_type_alias_mapping));
		temp_2 = FIXNUMP(code) ? (IFIX(code) & (SI_Long)4096L) != 
			(SI_Long)0L : TRUEP(Qnil);
		if (temp_2);
		else
		    temp_2 = TRUEP(M_CAR(M_CDR(Cache_g1_semantics_graph)));
		temp_2 =  !temp_2;
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		Current_model_runtime_info_qm = Main_model_runtime_info;
		Current_model_definition_qm = Nil;
	    }
	}
	if (Current_model_runtime_info_qm)
	    result = begin_collecting_data_for_simulator_1(variable,
		    interval_to_use);
	else
	    result = VALUES_1(Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* RECLAIM-INTERVAL-AT-WHICH-TO-SEND-VALUE-TO-INFERENCE-ENGINE */
Object reclaim_interval_at_which_to_send_value_to_inference_engine(interval)
    Object interval;
{
    Object car_item, cdr_item;

    x_note_fn_call(184,172);
    if (CONSP(interval)) {
	car_item = CAR(interval);
	cdr_item = CDR(interval);
      next_loop:
	if ( !TRUEP(car_item))
	    goto end_loop;
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(car_item) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(car_item)) == (SI_Long)1L)
	    reclaim_managed_simple_float_array_of_length_1(car_item);
	if (CONSP(cdr_item))
	    car_item = CAR(cdr_item);
	else
	    car_item = cdr_item;
	cdr_item = CONSP(cdr_item) ? CDR(cdr_item) : Nil;
	goto next_loop;
      end_loop:;
	return reclaim_simulate_list_star_1(interval);
    }
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(interval) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(interval)) == (SI_Long)1L) {
	reclaim_managed_simple_float_array_of_length_1(interval);
	return VALUES_1(Nil);
    }
    else
	return VALUES_1(Qnil);
}

static Object Qlong_time_ago;      /* long-time-ago */

/* BEGIN-COLLECTING-DATA-FOR-SIMULATOR-1 */
Object begin_collecting_data_for_simulator_1(variable,collection_interval)
    Object variable, collection_interval;
{
    Object collection_interval_used_qm, code, simulation_info_qm;
    Object variable_simulation_runtime_structure_qm, current_computation_frame;
    Object current_computation_instance;
    Object interval_at_which_to_send_value_to_inference_engine;
    Object gensymed_symbol, gensymed_symbol_1, managed_number_or_value;
    Object simulation_value, amf_available_array_cons_qm, amf_array, temp_2;
    Object temp_3, amf_result, new_float;
    char temp;
    double temp_1, aref_new_value;
    Declare_special(2);

    x_note_fn_call(184,173);
    collection_interval_used_qm = Nil;
    if (ISVREF(Simulation_parameters,(SI_Long)24L)) {
	code = M_CAR(M_CDR(Edit_type_alias_mapping));
	temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)4096L) != 
		(SI_Long)0L : TRUEP(Qnil);
	if (temp);
	else
	    temp = TRUEP(M_CAR(M_CDR(Cache_g1_semantics_graph)));
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	simulation_info_qm = get_lookup_slot_value_given_default(variable,
		Qsimulation_info_qm,Nil);
	variable_simulation_runtime_structure_qm = simulation_info_qm ? 
		ISVREF(simulation_info_qm,(SI_Long)1L) : Nil;
	current_computation_frame = variable;
	current_computation_instance = 
		lookup_kb_specific_property_value(Qsimulator_data_server,
		Data_server_kbprop);
	interval_at_which_to_send_value_to_inference_engine = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_instance,Qcurrent_computation_instance,current_computation_instance,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		  0);
	    if (variable_simulation_runtime_structure_qm) {
		interval_at_which_to_send_value_to_inference_engine = 
			ISVREF(variable_simulation_runtime_structure_qm,
			(SI_Long)14L);
		temp = TRUEP(ISVREF(Current_model_runtime_info_qm,
			(SI_Long)1L));
		if (temp);
		else {
		    gensymed_symbol = variable_simulation_runtime_structure_qm;
		    gensymed_symbol_1 = ISVREF(ISVREF(gensymed_symbol,
			    (SI_Long)11L),(SI_Long)1L);
		    temp =  !(gensymed_symbol_1 && 
			    ISVREF(gensymed_symbol_1,(SI_Long)4L) ? 
			    (EQ(ISVREF(gensymed_symbol,(SI_Long)13L),
			    Qsuppress_first_update) ? TRUEP(Nil) : 
			    TRUEP(T)) : TRUEP(Nil));
		}
		if (temp) {
		    managed_number_or_value = 
			    ISVREF(variable_simulation_runtime_structure_qm,
			    (SI_Long)1L);
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			simulation_value = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			simulation_value = aref1(managed_number_or_value,
				FIX((SI_Long)0L));
		    else if (text_string_p(managed_number_or_value))
			simulation_value = 
				copy_text_string(managed_number_or_value);
		    else
			simulation_value = managed_number_or_value;
		    if ( !EQ(simulation_value,Simulation_no_value))
			put_simulated_value_to_inference_engine(3,variable,
				simulation_value,Nil);
		    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(Seconds_from_1900_to_1970);
		    set_last_time_value_sent_to_inference_engine(variable_simulation_runtime_structure_qm,
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			    (SI_Long)0L) - 
			    (DFLOAT_ISAREF_1(Gensym_base_time_as_managed_float,
			    (SI_Long)0L) - temp_1)));
		}
		else
		    set_last_time_value_sent_to_inference_engine(variable_simulation_runtime_structure_qm,
			    Qlong_time_ago);
		reclaim_interval_at_which_to_send_value_to_inference_engine(interval_at_which_to_send_value_to_inference_engine);
		collection_interval_used_qm = T;
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
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(Seconds_from_1900_to_1970);
		aref_new_value = DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L) - 
			(DFLOAT_ISAREF_1(Gensym_base_time_as_managed_float,
			(SI_Long)0L) - temp_1);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		temp_2 = simulate_cons_1(collection_interval,new_float);
		SVREF(variable_simulation_runtime_structure_qm,
			FIX((SI_Long)14L)) = temp_2;
	    }
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if ( !TRUEP(collection_interval_used_qm)) {
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(collection_interval) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(collection_interval)) == 
		(SI_Long)1L) {
	    reclaim_managed_simple_float_array_of_length_1(collection_interval);
	    return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qg2_defstruct_structure_name_data_server_g2_struct;  /* g2-defstruct-structure-name::data-server-g2-struct */

/* BEGIN-COLLECTING-DATA-FOR-SIMULATED-VARIABLE-IF-APPROPRIATE */
Object begin_collecting_data_for_simulated_variable_if_appropriate(variable_or_parameter)
    Object variable_or_parameter;
{
    Object sub_class_bit_vector, collection_interval_qm, source_or_map;
    Object server_qm, data_server_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(184,174);
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
    if (temp ? (SI_Long)0L != (IFIX(ISVREF(variable_or_parameter,
	    (SI_Long)5L)) & (SI_Long)1L) : TRUEP(Nil)) {
	collection_interval_qm = ISVREF(variable_or_parameter,(SI_Long)32L);
	source_or_map = ISVREF(variable_or_parameter,(SI_Long)31L);
	server_qm = ATOM(source_or_map) ? 
		lookup_kb_specific_property_value(source_or_map,
		Data_server_or_alias_qm_kbprop) : Nil;
	data_server_qm = server_qm ? server_qm : 
		warn_of_undefined_data_server(variable_or_parameter,
		source_or_map);
	if (collection_interval_qm && SIMPLE_VECTOR_P(data_server_qm) && 
		EQ(ISVREF(data_server_qm,(SI_Long)0L),
		Qg2_defstruct_structure_name_data_server_g2_struct) && 
		EQ(ISVREF(data_server_qm,(SI_Long)1L),Qsimulator_data_server))
	    return begin_collecting_data_for_simulator(2,
		    variable_or_parameter,collection_interval_qm);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* STOP-COLLECTING-DATA-FOR-SIMULATOR */
Object stop_collecting_data_for_simulator(variable)
    Object variable;
{
    Object simulation_info_qm, variable_simulation_runtime_structure_qm;
    Object interval_at_which_to_send_value_to_inference_engine_qm, temp_1;
    Object svref_new_value;
    char temp;

    x_note_fn_call(184,175);
    simulation_info_qm = get_lookup_slot_value_given_default(variable,
	    Qsimulation_info_qm,Nil);
    variable_simulation_runtime_structure_qm = simulation_info_qm ? 
	    ISVREF(simulation_info_qm,(SI_Long)1L) : Nil;
    interval_at_which_to_send_value_to_inference_engine_qm = Nil;
    if (variable_simulation_runtime_structure_qm) {
	interval_at_which_to_send_value_to_inference_engine_qm = 
		ISVREF(variable_simulation_runtime_structure_qm,(SI_Long)14L);
	temp = TRUEP(interval_at_which_to_send_value_to_inference_engine_qm);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	temp_1 = CDR(interval_at_which_to_send_value_to_inference_engine_qm);
	svref_new_value = CONSP(temp_1) ? 
		simulate_cons_1(FIRST(interval_at_which_to_send_value_to_inference_engine_qm),
		SECOND(interval_at_which_to_send_value_to_inference_engine_qm)) 
		: Nil;
	SVREF(variable_simulation_runtime_structure_qm,FIX((SI_Long)14L)) 
		= svref_new_value;
	if (ISVREF(variable_simulation_runtime_structure_qm,(SI_Long)14L))
	    return reclaim_simulate_list_star_1(interval_at_which_to_send_value_to_inference_engine_qm);
	else
	    return reclaim_interval_at_which_to_send_value_to_inference_engine(interval_at_which_to_send_value_to_inference_engine_qm);
    }
    else
	return VALUES_1(Nil);
}

/* COMPUTE-G2-TIME-FOR-SIMULATION-TIME */
Object compute_g2_time_for_simulation_time(simulation_time)
    Object simulation_time;
{
    Object accumulator_compound_fixnum_simulation_time, gensym_time_value;
    Object g2_time_value, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, macro_time_1, micro_time_1, macro_time_2;
    Object micro_time_2, svref_new_value;
    double gensymed_symbol_3, gensymed_symbol_4;

    x_note_fn_call(184,176);
    accumulator_compound_fixnum_simulation_time = 
	    make_compound_fixnum_simulation_time_1();
    gensym_time_value = Nil;
    g2_time_value = Nil;
    gensymed_symbol = accumulator_compound_fixnum_simulation_time;
    gensymed_symbol_1 = simulation_time;
    gensymed_symbol_2 = ISVREF(Current_model_runtime_info_qm,(SI_Long)7L);
    macro_time_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
    micro_time_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
    macro_time_2 = ISVREF(gensymed_symbol_2,(SI_Long)1L);
    micro_time_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
    if (IFIX(micro_time_2) != (SI_Long)0L) {
	micro_time_1 = FIXNUM_ADD(micro_time_1,micro_time_2);
	if (FIXNUM_GE(micro_time_1,
		Fraction_modulus_of_compound_fixnum_simulation_time)) {
	    svref_new_value = FIXNUM_MINUS(micro_time_1,
		    Fraction_modulus_of_compound_fixnum_simulation_time);
	    SVREF(gensymed_symbol,FIX((SI_Long)2L)) = svref_new_value;
	    macro_time_1 = FIXNUM_ADD1(macro_time_1);
	}
	else
	    SVREF(gensymed_symbol,FIX((SI_Long)2L)) = micro_time_1;
    }
    else {
	if (SVREF(gensymed_symbol,FIX((SI_Long)2L)) = micro_time_1);
    }
    svref_new_value = FIXNUM_ADD(macro_time_1,macro_time_2);
    SVREF(gensymed_symbol,FIX((SI_Long)1L)) = svref_new_value;
    gensym_time_value = ISVREF(accumulator_compound_fixnum_simulation_time,
	    (SI_Long)1L);
    gensymed_symbol_3 = (double)IFIX(FIXNUM_MINUS(gensym_time_value,
	    Gensym_time_at_start)) + DFLOAT_ISAREF_1(G2_time_at_start,
	    (SI_Long)0L);
    gensymed_symbol = ISVREF(accumulator_compound_fixnum_simulation_time,
	    (SI_Long)2L);
    gensymed_symbol_4 = IFIX(gensymed_symbol) == (SI_Long)0L ? 0.0 : 
	    (double)IFIX(gensymed_symbol) / 100000.0;
    g2_time_value = DOUBLE_TO_DOUBLE_FLOAT(gensymed_symbol_3 + 
	    gensymed_symbol_4);
    reclaim_compound_fixnum_simulation_time(accumulator_compound_fixnum_simulation_time);
    return VALUES_1(g2_time_value);
}

/* CURRENT-SIMULATION-TIME-AS-FLOAT */
Object current_simulation_time_as_float()
{
    x_note_fn_call(184,177);
    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(current_simulation_time_as_managed_float(),
	    (SI_Long)0L)));
}

/* CURRENT-SIMULATION-TIME-AS-MANAGED-FLOAT */
Object current_simulation_time_as_managed_float()
{
    Object gensymed_symbol, integer_portion, micro_time, aref_arg_1;
    double aref_new_value;

    x_note_fn_call(184,178);
    gensymed_symbol = ISVREF(Current_model_runtime_info_qm,(SI_Long)6L);
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
    return VALUES_1(Simulation_time_managed_float);
}

/* SET-EXTERNAL-VARIABLE-FOR-SIMULATOR */
Object set_external_variable_for_simulator varargs_1(int, n)
{
    Object variable, value;
    Object data_type, simulation_info_qm, gensymed_symbol, gensymed_symbol_1;
    Object type_specification, svref_arg_1, svref_new_value, temp;
    Object store_managed_number_or_value_arg_1, sub_class_bit_vector;
    Object put_current_value_called_from_simulator_p;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp_1;
    double store_managed_number_or_value_arg;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(184,179);
    INIT_ARGS_nonrelocating();
    variable = REQUIRED_ARG_nonrelocating();
    value = REQUIRED_ARG_nonrelocating();
    data_type = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    value = evaluation_value_value(value);
    simulation_info_qm = get_lookup_slot_value_given_default(variable,
	    Qsimulation_info_qm,Nil);
    if (simulation_info_qm ? TRUEP(ISVREF(simulation_info_qm,(SI_Long)1L)) 
	    : TRUEP(Nil)) {
	gensymed_symbol = variable;
	gensymed_symbol_1 = value;
	type_specification = 
		type_specification_of_variable_or_parameter_value(gensymed_symbol);
	if (EQ(type_specification,Qfloat) && FIXNUMP(gensymed_symbol_1)) {
	    simulation_info_qm = 
		    get_lookup_slot_value_given_default(variable,
		    Qsimulation_info_qm,Nil);
	    svref_arg_1 = simulation_info_qm ? ISVREF(simulation_info_qm,
		    (SI_Long)1L) : Nil;
	    store_managed_number_or_value_arg = 
		    (double)IFIX(gensymed_symbol_1);
	    svref_new_value = 
		    store_managed_number_or_value_function(ISVREF(svref_arg_1,
		    (SI_Long)1L),
		    DOUBLE_TO_DOUBLE_FLOAT(store_managed_number_or_value_arg));
	    SVREF(svref_arg_1,FIX((SI_Long)1L)) = svref_new_value;
	}
	else {
	    if (EQ(type_specification,Qinteger))
		temp = FIXNUMP(gensymed_symbol_1) ? T : Nil;
	    else if (EQ(type_specification,Qlong))
		temp = INLINE_LONG_P(gensymed_symbol_1) != (SI_Long)0L ? T 
			: Nil;
	    else if (EQ(type_specification,Qfloat))
		temp = FLOATP(gensymed_symbol_1) ? T : Nil;
	    else if (EQ(type_specification,Qsymbol))
		temp = gensymed_symbol_1 ? (SYMBOLP(gensymed_symbol_1) ? T 
			: Nil) : Qnil;
	    else if (EQ(type_specification,Qtext))
		temp = text_string_p(gensymed_symbol_1);
	    else if (EQ(type_specification,Qtruth_value))
		temp = FIXNUMP(gensymed_symbol_1) && FIXNUM_LE(Falsity,
			gensymed_symbol_1) ? (FIXNUM_LE(gensymed_symbol_1,
			Truth) ? T : Nil) : Qnil;
	    else if (EQ(type_specification,Qboolean)) {
		if (FIXNUMP(gensymed_symbol_1)) {
		    temp = FIXNUM_EQ(gensymed_symbol_1,Falsity) ? T : Nil;
		    if (temp);
		    else
			temp = FIXNUM_EQ(gensymed_symbol_1,Truth) ? T : Nil;
		}
		else
		    temp = Nil;
	    }
	    else if (EQ(type_specification,Qnumber) || 
		    EQ(type_specification,Qinteger) || 
		    EQ(type_specification,Qfloat) || EQ(type_specification,
		    Qlong) || 
		    lookup_global_or_kb_specific_property_value(type_specification,
		    Numeric_data_type_gkbprop)) {
		temp = FLOATP(gensymed_symbol_1) ? T : Nil;
		if (temp);
		else
		    temp = FIXNUMP(gensymed_symbol_1) ? T : Nil;
	    }
	    else
		temp = Nil;
	    if (temp) {
		simulation_info_qm = 
			get_lookup_slot_value_given_default(variable,
			Qsimulation_info_qm,Nil);
		svref_arg_1 = simulation_info_qm ? 
			ISVREF(simulation_info_qm,(SI_Long)1L) : Nil;
		store_managed_number_or_value_arg_1 = gensymed_symbol_1;
		svref_new_value = 
			store_managed_number_or_value_function(ISVREF(svref_arg_1,
			(SI_Long)1L),store_managed_number_or_value_arg_1);
		SVREF(svref_arg_1,FIX((SI_Long)1L)) = svref_new_value;
	    }
	    else
		simulation_type_error_from_within_or_without_stack_eval(gensymed_symbol,
			gensymed_symbol_1);
	}
	gensymed_symbol = variable;
	gensymed_symbol_1 = value;
	type_specification = 
		type_specification_of_variable_or_parameter_value(gensymed_symbol);
	if (EQ(type_specification,Qfloat) && FIXNUMP(gensymed_symbol_1)) {
	    simulation_info_qm = 
		    get_lookup_slot_value_given_default(variable,
		    Qsimulation_info_qm,Nil);
	    svref_arg_1 = simulation_info_qm ? ISVREF(simulation_info_qm,
		    (SI_Long)1L) : Nil;
	    store_managed_number_or_value_arg = 
		    (double)IFIX(gensymed_symbol_1);
	    svref_new_value = 
		    store_managed_number_or_value_function(ISVREF(svref_arg_1,
		    (SI_Long)2L),
		    DOUBLE_TO_DOUBLE_FLOAT(store_managed_number_or_value_arg));
	    SVREF(svref_arg_1,FIX((SI_Long)2L)) = svref_new_value;
	}
	else {
	    if (EQ(type_specification,Qinteger))
		temp = FIXNUMP(gensymed_symbol_1) ? T : Nil;
	    else if (EQ(type_specification,Qlong))
		temp = INLINE_LONG_P(gensymed_symbol_1) != (SI_Long)0L ? T 
			: Nil;
	    else if (EQ(type_specification,Qfloat))
		temp = FLOATP(gensymed_symbol_1) ? T : Nil;
	    else if (EQ(type_specification,Qsymbol))
		temp = gensymed_symbol_1 ? (SYMBOLP(gensymed_symbol_1) ? T 
			: Nil) : Qnil;
	    else if (EQ(type_specification,Qtext))
		temp = text_string_p(gensymed_symbol_1);
	    else if (EQ(type_specification,Qtruth_value))
		temp = FIXNUMP(gensymed_symbol_1) && FIXNUM_LE(Falsity,
			gensymed_symbol_1) ? (FIXNUM_LE(gensymed_symbol_1,
			Truth) ? T : Nil) : Qnil;
	    else if (EQ(type_specification,Qboolean)) {
		if (FIXNUMP(gensymed_symbol_1)) {
		    temp = FIXNUM_EQ(gensymed_symbol_1,Falsity) ? T : Nil;
		    if (temp);
		    else
			temp = FIXNUM_EQ(gensymed_symbol_1,Truth) ? T : Nil;
		}
		else
		    temp = Nil;
	    }
	    else if (EQ(type_specification,Qnumber) || 
		    EQ(type_specification,Qinteger) || 
		    EQ(type_specification,Qfloat) || EQ(type_specification,
		    Qlong) || 
		    lookup_global_or_kb_specific_property_value(type_specification,
		    Numeric_data_type_gkbprop)) {
		temp = FLOATP(gensymed_symbol_1) ? T : Nil;
		if (temp);
		else
		    temp = FIXNUMP(gensymed_symbol_1) ? T : Nil;
	    }
	    else
		temp = Nil;
	    if (temp) {
		simulation_info_qm = 
			get_lookup_slot_value_given_default(variable,
			Qsimulation_info_qm,Nil);
		svref_arg_1 = simulation_info_qm ? 
			ISVREF(simulation_info_qm,(SI_Long)1L) : Nil;
		store_managed_number_or_value_arg_1 = gensymed_symbol_1;
		svref_new_value = 
			store_managed_number_or_value_function(ISVREF(svref_arg_1,
			(SI_Long)2L),store_managed_number_or_value_arg_1);
		SVREF(svref_arg_1,FIX((SI_Long)2L)) = svref_new_value;
	    }
	    else
		simulation_type_error_from_within_or_without_stack_eval(gensymed_symbol,
			gensymed_symbol_1);
	}
    }
    sub_class_bit_vector = ISVREF(ISVREF(variable,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Parameter_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol_2 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_3 = (SI_Long)1L;
	gensymed_symbol_4 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
	gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
	temp_1 = (SI_Long)0L < gensymed_symbol_2;
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1 ? TRUEP(Evaluating_simulator_procedure_qm) : TRUEP(Nil)) {
	put_current_value_called_from_simulator_p = T;
	PUSH_SPECIAL_WITH_SYMBOL(Put_current_value_called_from_simulator_p,Qput_current_value_called_from_simulator_p,put_current_value_called_from_simulator_p,
		0);
	  temp = value;
	  result = put_simulated_value_to_inference_engine(4,variable,temp,
		  get_current_time_in_simulation_environment_and_convert_to_g2_time(),
		  data_type);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* CONVERT-SIMULATION-VALUE-TO-VALUE-AND-TYPE */
Object convert_simulation_value_to_value_and_type(value)
    Object value;
{
    Object type;

    x_note_fn_call(184,180);
    if (NUMBERP(value))
	type = Qnumber;
    else if (EQ(value,Nil)) {
	value = FIX((SI_Long)-1000L);
	type = Qtruth_value;
    }
    else if (EQ(value,T)) {
	value = FIX((SI_Long)1000L);
	type = Qtruth_value;
    }
    else if (SYMBOLP(value))
	type = Qsymbol;
    else if (text_string_p(value))
	type = Qtext;
    else
	type = Qnil;
    return VALUES_2(value,type);
}

/* PUT-SIMULATED-VALUE-TO-INFERENCE-ENGINE */
Object put_simulated_value_to_inference_engine varargs_1(int, n)
{
    Object variable, simulation_value, collection_time_qm;
    Object type_qm, value, type;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(184,181);
    INIT_ARGS_nonrelocating();
    variable = REQUIRED_ARG_nonrelocating();
    simulation_value = REQUIRED_ARG_nonrelocating();
    collection_time_qm = REQUIRED_ARG_nonrelocating();
    type_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    value = Nil;
    type = Nil;
    if (type_qm) {
	value = simulation_value;
	type = type_qm;
    }
    else {
	result = convert_simulation_value_to_value_and_type(simulation_value);
	MVS_2(result,value,type);
    }
    return put_current_value(5,variable,value,type,Nil,collection_time_qm);
}

void simulate1_INIT()
{
    Object temp, reclaim_structure_for_external_set_pointers_1;
    Object reclaim_structure_for_compound_fixnum_simulation_time_1;
    Object reclaim_structure_for_model_runtime_info_1;
    Object reclaim_structure_for_model_queue_1;
    Object reclaim_structure_for_variable_group_update_structure_1;
    Object reclaim_structure_for_group_index_structure_1;
    Object Qset_external_variable_for_simulator;
    Object Qstop_collecting_data_for_simulator;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, AB_package;
    Object Qbegin_collecting_data_for_simulator;
    Object Qcollect_one_shot_data_for_simulator, Qgroup_index_structure;
    Object Qreclaim_structure, Qoutstanding_group_index_structure_count;
    Object Qgroup_index_structure_structure_memory_usage, Qutilities2;
    Object string_constant_18, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_17, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type, Qvariable_group_update_structure;
    Object Qoutstanding_variable_group_update_structure_count;
    Object Qvariable_group_update_structure_structure_memory_usage;
    Object string_constant_16, string_constant_15, Qshutdown_simulator;
    Object list_constant_7, Qat_either_end, Qat_output_end, Qat_input_end;
    Object Qat_an_output, Qat_an_input, Qat_port, Qconnected_to;
    Object Qinitialize_simulator_as_data_server, Qabsent_slot_putter;
    Object Qput_simulation_computation_methods_where_slot_is_absent;
    Object Qsimulation_computation_methods;
    Object Qsimulate_until_consistent_with_gensym_time;
    Object Qneed_calls_to_simulate_until_consistent_with_gensym_time;
    Object Qreclaim_model_queue_function, Qinitialize_model_queue;
    Object Qmodel_queue, Qoutstanding_model_queue_count;
    Object Qmodel_queue_structure_memory_usage, string_constant_14;
    Object string_constant_13, Qsimulate1, list_constant_6, Kfuncall;
    Object list_constant_5, Qinitialize_compound_simulation_time;
    Object Qinitialize_simulation_time_managed_float, list_constant_4;
    Object Qinitialize_minimum_simulation_time_increment, list_constant_3;
    Object Qpost_on_message_board, Qslot_putter, Qput_integration_algorithm;
    Object list_constant_2, Qinitialize_main_model_runtime_info;
    Object Qmodel_runtime_info, Qoutstanding_model_runtime_info_count;
    Object Qmodel_runtime_info_structure_memory_usage, string_constant_12;
    Object string_constant_11, Qcompound_fixnum_simulation_time;
    Object Qoutstanding_compound_fixnum_simulation_time_count;
    Object Qcompound_fixnum_simulation_time_structure_memory_usage;
    Object string_constant_10, string_constant_9, Qslot_value_reclaimer;
    Object Qreclaim_external_set_pointers_qm_value, Qexternal_set_pointers;
    Object Qoutstanding_external_set_pointers_count;
    Object Qexternal_set_pointers_structure_memory_usage, string_constant_8;
    Object string_constant_7, string_constant_6, Qsimulate_cons_memory_usage;
    Object Qoutstanding_simulate_conses, Qutilities1, list_constant_1;
    Object Qsimulate_cons_counter_vector, Qmake_thread_array, list_constant;
    Object Qavailable_simulate_conses_tail_vector;
    Object Qavailable_simulate_conses_vector;

    x_note_fn_call(184,182);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qavailable_simulate_conses = STATIC_SYMBOL("AVAILABLE-SIMULATE-CONSES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_simulate_conses,
	    Available_simulate_conses);
    Qutilities1 = STATIC_SYMBOL("UTILITIES1",AB_package);
    record_system_variable(Qavailable_simulate_conses,Qutilities1,Nil,Qnil,
	    Qt,Qnil,Qnil);
    Qavailable_simulate_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-SIMULATE-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_simulate_conses_tail,
	    Available_simulate_conses_tail);
    record_system_variable(Qavailable_simulate_conses_tail,Qutilities1,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_simulate_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-SIMULATE-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_simulate_conses_vector,
	    Available_simulate_conses_vector);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_thread_array = STATIC_SYMBOL("MAKE-THREAD-ARRAY",AB_package);
    list_constant = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,Qnil);
    record_system_variable(Qavailable_simulate_conses_vector,Qutilities1,
	    list_constant,Qnil,Qt,Qnil,Qnil);
    Qavailable_simulate_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-SIMULATE-CONSES-TAIL-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_simulate_conses_tail_vector,
	    Available_simulate_conses_tail_vector);
    record_system_variable(Qavailable_simulate_conses_tail_vector,
	    Qutilities1,list_constant,Qnil,Qt,Qnil,Qnil);
    Qsimulate_cons_counter_vector = 
	    STATIC_SYMBOL("SIMULATE-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsimulate_cons_counter_vector,
	    Simulate_cons_counter_vector);
    list_constant_1 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    FIX((SI_Long)0L));
    record_system_variable(Qsimulate_cons_counter_vector,Qutilities1,
	    list_constant_1,Qnil,Qt,Qnil,Qnil);
    Qsimulate_cons_counter = STATIC_SYMBOL("SIMULATE-CONS-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsimulate_cons_counter,Simulate_cons_counter);
    record_system_variable(Qsimulate_cons_counter,Qutilities1,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_simulate_conses = 
	    STATIC_SYMBOL("OUTSTANDING-SIMULATE-CONSES",AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_simulate_conses,
	    STATIC_FUNCTION(outstanding_simulate_conses,NIL,FALSE,0,0));
    Qsimulate_cons_memory_usage = 
	    STATIC_SYMBOL("SIMULATE-CONS-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qsimulate_cons_memory_usage,
	    STATIC_FUNCTION(simulate_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_6 = STATIC_STRING("1q83-pXy9k83-pWy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_simulate_conses);
    push_optimized_constant(Qsimulate_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_6));
    Qsimulate = STATIC_SYMBOL("SIMULATE",AB_package);
    Qsimulation_info_qm = STATIC_SYMBOL("SIMULATION-INFO\?",AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_external_set_pointers_g2_struct = 
	    STATIC_SYMBOL("EXTERNAL-SET-POINTERS-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qexternal_set_pointers = STATIC_SYMBOL("EXTERNAL-SET-POINTERS",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_external_set_pointers_g2_struct,
	    Qexternal_set_pointers,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qexternal_set_pointers,
	    Qg2_defstruct_structure_name_external_set_pointers_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_external_set_pointers == UNBOUND)
	The_type_description_of_external_set_pointers = Nil;
    string_constant_7 = 
	    STATIC_STRING("43Dy8m83hDy1n83hDy8n8k1l8n0000000kok0k0");
    temp = The_type_description_of_external_set_pointers;
    The_type_description_of_external_set_pointers = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_7));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_external_set_pointers_g2_struct,
	    The_type_description_of_external_set_pointers,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qexternal_set_pointers,
	    The_type_description_of_external_set_pointers,
	    Qtype_description_of_type);
    Qoutstanding_external_set_pointers_count = 
	    STATIC_SYMBOL("OUTSTANDING-EXTERNAL-SET-POINTERS-COUNT",
	    AB_package);
    Qexternal_set_pointers_structure_memory_usage = 
	    STATIC_SYMBOL("EXTERNAL-SET-POINTERS-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_8 = STATIC_STRING("1q83hDy8s83-TYy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_external_set_pointers_count);
    push_optimized_constant(Qexternal_set_pointers_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_8));
    Qchain_of_available_external_set_pointerss = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-EXTERNAL-SET-POINTERSS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_external_set_pointerss,
	    Chain_of_available_external_set_pointerss);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_external_set_pointerss,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qexternal_set_pointers_count = 
	    STATIC_SYMBOL("EXTERNAL-SET-POINTERS-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qexternal_set_pointers_count,
	    External_set_pointers_count);
    record_system_variable(Qexternal_set_pointers_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_external_set_pointerss_vector == UNBOUND)
	Chain_of_available_external_set_pointerss_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qexternal_set_pointers_structure_memory_usage,
	    STATIC_FUNCTION(external_set_pointers_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_external_set_pointers_count,
	    STATIC_FUNCTION(outstanding_external_set_pointers_count,NIL,
	    FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_external_set_pointers_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_external_set_pointers,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qexternal_set_pointers,
	    reclaim_structure_for_external_set_pointers_1);
    Qexternal_set_pointers_qm = STATIC_SYMBOL("EXTERNAL-SET-POINTERS\?",
	    AB_package);
    Qreclaim_external_set_pointers_qm_value = 
	    STATIC_SYMBOL("RECLAIM-EXTERNAL-SET-POINTERS\?-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_external_set_pointers_qm_value,
	    STATIC_FUNCTION(reclaim_external_set_pointers_qm_value,NIL,
	    FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qexternal_set_pointers_qm,
	    SYMBOL_FUNCTION(Qreclaim_external_set_pointers_qm_value),
	    Qslot_value_reclaimer);
    Qg2_defstruct_structure_name_compound_fixnum_simulation_time_g2_struct 
	    = STATIC_SYMBOL("COMPOUND-FIXNUM-SIMULATION-TIME-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qcompound_fixnum_simulation_time = 
	    STATIC_SYMBOL("COMPOUND-FIXNUM-SIMULATION-TIME",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_compound_fixnum_simulation_time_g2_struct,
	    Qcompound_fixnum_simulation_time,
	    Qab_name_of_unique_structure_type);
    mutate_global_property(Qcompound_fixnum_simulation_time,
	    Qg2_defstruct_structure_name_compound_fixnum_simulation_time_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_compound_fixnum_simulation_time == UNBOUND)
	The_type_description_of_compound_fixnum_simulation_time = Nil;
    string_constant_9 = 
	    STATIC_STRING("43Dy8m83g6y1n83g6y8n8k1l8n0000001l1m83My83-A*yknk0k0");
    temp = The_type_description_of_compound_fixnum_simulation_time;
    The_type_description_of_compound_fixnum_simulation_time = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_9));
    mutate_global_property(Qg2_defstruct_structure_name_compound_fixnum_simulation_time_g2_struct,
	    The_type_description_of_compound_fixnum_simulation_time,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qcompound_fixnum_simulation_time,
	    The_type_description_of_compound_fixnum_simulation_time,
	    Qtype_description_of_type);
    Qoutstanding_compound_fixnum_simulation_time_count = 
	    STATIC_SYMBOL("OUTSTANDING-COMPOUND-FIXNUM-SIMULATION-TIME-COUNT",
	    AB_package);
    Qcompound_fixnum_simulation_time_structure_memory_usage = 
	    STATIC_SYMBOL("COMPOUND-FIXNUM-SIMULATION-TIME-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_10 = STATIC_STRING("1q83g6y8s83-NXy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_compound_fixnum_simulation_time_count);
    push_optimized_constant(Qcompound_fixnum_simulation_time_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_10));
    Qchain_of_available_compound_fixnum_simulation_times = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-COMPOUND-FIXNUM-SIMULATION-TIMES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_compound_fixnum_simulation_times,
	    Chain_of_available_compound_fixnum_simulation_times);
    record_system_variable(Qchain_of_available_compound_fixnum_simulation_times,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcompound_fixnum_simulation_time_count = 
	    STATIC_SYMBOL("COMPOUND-FIXNUM-SIMULATION-TIME-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcompound_fixnum_simulation_time_count,
	    Compound_fixnum_simulation_time_count);
    record_system_variable(Qcompound_fixnum_simulation_time_count,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_compound_fixnum_simulation_times_vector == UNBOUND)
	Chain_of_available_compound_fixnum_simulation_times_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qcompound_fixnum_simulation_time_structure_memory_usage,
	    STATIC_FUNCTION(compound_fixnum_simulation_time_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_compound_fixnum_simulation_time_count,
	    STATIC_FUNCTION(outstanding_compound_fixnum_simulation_time_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_compound_fixnum_simulation_time_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_compound_fixnum_simulation_time,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qcompound_fixnum_simulation_time,
	    reclaim_structure_for_compound_fixnum_simulation_time_1);
    Qg2_defstruct_structure_name_model_runtime_info_g2_struct = 
	    STATIC_SYMBOL("MODEL-RUNTIME-INFO-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qmodel_runtime_info = STATIC_SYMBOL("MODEL-RUNTIME-INFO",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_model_runtime_info_g2_struct,
	    Qmodel_runtime_info,Qab_name_of_unique_structure_type);
    mutate_global_property(Qmodel_runtime_info,
	    Qg2_defstruct_structure_name_model_runtime_info_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_model_runtime_info == UNBOUND)
	The_type_description_of_model_runtime_info = Nil;
    string_constant_11 = 
	    STATIC_STRING("43Dy8m83kny1n83kny8n8k1l8n0000000k3Zyk0k0");
    temp = The_type_description_of_model_runtime_info;
    The_type_description_of_model_runtime_info = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_11));
    mutate_global_property(Qg2_defstruct_structure_name_model_runtime_info_g2_struct,
	    The_type_description_of_model_runtime_info,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qmodel_runtime_info,
	    The_type_description_of_model_runtime_info,
	    Qtype_description_of_type);
    Qoutstanding_model_runtime_info_count = 
	    STATIC_SYMBOL("OUTSTANDING-MODEL-RUNTIME-INFO-COUNT",AB_package);
    Qmodel_runtime_info_structure_memory_usage = 
	    STATIC_SYMBOL("MODEL-RUNTIME-INFO-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_12 = STATIC_STRING("1q83kny8s83-fNy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_model_runtime_info_count);
    push_optimized_constant(Qmodel_runtime_info_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_12));
    Qchain_of_available_model_runtime_infos = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-MODEL-RUNTIME-INFOS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_model_runtime_infos,
	    Chain_of_available_model_runtime_infos);
    record_system_variable(Qchain_of_available_model_runtime_infos,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qmodel_runtime_info_count = STATIC_SYMBOL("MODEL-RUNTIME-INFO-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmodel_runtime_info_count,
	    Model_runtime_info_count);
    record_system_variable(Qmodel_runtime_info_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_model_runtime_infos_vector == UNBOUND)
	Chain_of_available_model_runtime_infos_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qmodel_runtime_info_structure_memory_usage,
	    STATIC_FUNCTION(model_runtime_info_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_model_runtime_info_count,
	    STATIC_FUNCTION(outstanding_model_runtime_info_count,NIL,FALSE,
	    0,0));
    reclaim_structure_for_model_runtime_info_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_model_runtime_info,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qmodel_runtime_info,
	    reclaim_structure_for_model_runtime_info_1);
    Qmain_model_runtime_info = STATIC_SYMBOL("MAIN-MODEL-RUNTIME-INFO",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmain_model_runtime_info,
	    Main_model_runtime_info);
    Qsimulate1 = STATIC_SYMBOL("SIMULATE1",AB_package);
    Qinitialize_main_model_runtime_info = 
	    STATIC_SYMBOL("INITIALIZE-MAIN-MODEL-RUNTIME-INFO",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_main_model_runtime_info,
	    STATIC_FUNCTION(initialize_main_model_runtime_info,NIL,FALSE,0,0));
    list_constant_2 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_main_model_runtime_info);
    record_system_variable(Qmain_model_runtime_info,Qsimulate1,
	    list_constant_2,Qnil,Qnil,Qnil,Qnil);
    Qcurrent_model_runtime_info_qm = 
	    STATIC_SYMBOL("CURRENT-MODEL-RUNTIME-INFO\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_model_runtime_info_qm,
	    Current_model_runtime_info_qm);
    record_system_variable(Qcurrent_model_runtime_info_qm,Qsimulate1,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qcurrent_model_definition_qm = 
	    STATIC_SYMBOL("CURRENT-MODEL-DEFINITION\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_model_definition_qm,
	    Current_model_definition_qm);
    record_system_variable(Qcurrent_model_definition_qm,Qsimulate1,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qrk4 = STATIC_SYMBOL("RK4",AB_package);
    Qintegration_algorithm = STATIC_SYMBOL("INTEGRATION-ALGORITHM",AB_package);
    Qput_integration_algorithm = STATIC_SYMBOL("PUT-INTEGRATION-ALGORITHM",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_integration_algorithm,
	    STATIC_FUNCTION(put_integration_algorithm,NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qintegration_algorithm,
	    SYMBOL_FUNCTION(Qput_integration_algorithm),Qslot_putter);
    Qwithin_simulate_until_consistent_with_gensym_time = 
	    STATIC_SYMBOL("WITHIN-SIMULATE-UNTIL-CONSISTENT-WITH-GENSYM-TIME",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qwithin_simulate_until_consistent_with_gensym_time,
	    Within_simulate_until_consistent_with_gensym_time);
    record_system_variable(Qwithin_simulate_until_consistent_with_gensym_time,
	    Qsimulate1,Nil,Qnil,Qnil,Qnil,Qnil);
    Qinitializing_simulator_qm = STATIC_SYMBOL("INITIALIZING-SIMULATOR\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qinitializing_simulator_qm,
	    Initializing_simulator_qm);
    record_system_variable(Qinitializing_simulator_qm,Qsimulate1,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qinitializing_state_variables_qm = 
	    STATIC_SYMBOL("INITIALIZING-STATE-VARIABLES\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qinitializing_state_variables_qm,
	    Initializing_state_variables_qm);
    record_system_variable(Qinitializing_state_variables_qm,Qsimulate1,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qsimulation_error_catch = STATIC_SYMBOL("SIMULATION-ERROR-CATCH",
	    AB_package);
    Qpost_simulation_warning_for_no_value = 
	    STATIC_SYMBOL("POST-SIMULATION-WARNING-FOR-NO-VALUE",AB_package);
    string_constant = 
	    STATIC_STRING("Simulation problem.  Can\'t get value for ~NF.");
    SET_SYMBOL_FUNCTION(Qpost_simulation_warning_for_no_value,
	    STATIC_FUNCTION(post_simulation_warning_for_no_value,NIL,FALSE,
	    1,1));
    Qsimulation_type_error = STATIC_SYMBOL("SIMULATION-TYPE-ERROR",AB_package);
    string_constant_1 = 
	    STATIC_STRING("An attempt to put the value ~s into ~NF ~\n     which has type ~NT failed because of type mismatch.");
    Qno_value = STATIC_SYMBOL("NO-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qsimulation_type_error,
	    STATIC_FUNCTION(simulation_type_error,NIL,FALSE,2,2));
    string_constant_2 = 
	    STATIC_STRING("Simulation problem.  The initialization expression \"the current parameter value\" ~\n     is not valid because ~NF is not a parameter.");
    Qrecord_block_for_tformat = STATIC_SYMBOL("RECORD-BLOCK-FOR-TFORMAT",
	    AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_3 = 
	    STATIC_STRING("An attempt to put the value ~s into ~NF ~\n          which has type ~NT failed because of type mismatch.");
    Qunknown_encountered = STATIC_SYMBOL("UNKNOWN-ENCOUNTERED",AB_package);
    string_constant_4 = 
	    STATIC_STRING("~nw~%~%Exiting execution of this formula.  No value was computed for ~\n          ~NF, and simulation has been halted for its model.");
    Qsimulation_stack_error = STATIC_SYMBOL("SIMULATION-STACK-ERROR",
	    AB_package);
    Qsimulator_data_server = STATIC_SYMBOL("SIMULATOR-DATA-SERVER",AB_package);
    Qcollect_one_shot_data_for_simulator = 
	    STATIC_SYMBOL("COLLECT-ONE-SHOT-DATA-FOR-SIMULATOR",AB_package);
    Qbegin_collecting_data_for_simulator = 
	    STATIC_SYMBOL("BEGIN-COLLECTING-DATA-FOR-SIMULATOR",AB_package);
    Qstop_collecting_data_for_simulator = 
	    STATIC_SYMBOL("STOP-COLLECTING-DATA-FOR-SIMULATOR",AB_package);
    Qsimulate_until_consistent_with_gensym_time = 
	    STATIC_SYMBOL("SIMULATE-UNTIL-CONSISTENT-WITH-GENSYM-TIME",
	    AB_package);
    Qinitialize_simulator_as_data_server = 
	    STATIC_SYMBOL("INITIALIZE-SIMULATOR-AS-DATA-SERVER",AB_package);
    Qset_external_variable_for_simulator = 
	    STATIC_SYMBOL("SET-EXTERNAL-VARIABLE-FOR-SIMULATOR",AB_package);
    Qshutdown_simulator = STATIC_SYMBOL("SHUTDOWN-SIMULATOR",AB_package);
    Qpost_on_message_board = STATIC_SYMBOL("POST-ON-MESSAGE-BOARD",AB_package);
    SET_SYMBOL_FUNCTION(Qpost_on_message_board,
	    STATIC_FUNCTION(post_on_message_board,NIL,TRUE,5,9));
    Qneed_calls_to_simulate_until_consistent_with_gensym_time = 
	    STATIC_SYMBOL("NEED-CALLS-TO-SIMULATE-UNTIL-CONSISTENT-WITH-GENSYM-TIME",
	    AB_package);
    def_data_server(13,Qsimulator_data_server,
	    Qcollect_one_shot_data_for_simulator,
	    Qbegin_collecting_data_for_simulator,
	    Qstop_collecting_data_for_simulator,
	    Qsimulate_until_consistent_with_gensym_time,Nil,
	    Qinitialize_simulator_as_data_server,
	    Qset_external_variable_for_simulator,Qshutdown_simulator,
	    Qpost_on_message_board,Nil,Nil,
	    Qneed_calls_to_simulate_until_consistent_with_gensym_time);
    Qminimum_simulation_time_increment = 
	    STATIC_SYMBOL("MINIMUM-SIMULATION-TIME-INCREMENT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qminimum_simulation_time_increment,
	    Minimum_simulation_time_increment);
    Qinitialize_minimum_simulation_time_increment = 
	    STATIC_SYMBOL("INITIALIZE-MINIMUM-SIMULATION-TIME-INCREMENT",
	    AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_minimum_simulation_time_increment);
    record_system_variable(Qminimum_simulation_time_increment,Qsimulate1,
	    list_constant_3,Qnil,Qnil,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qinitialize_minimum_simulation_time_increment,
	    STATIC_FUNCTION(initialize_minimum_simulation_time_increment,
	    NIL,FALSE,0,0));
    Qsimulation_time_managed_float = 
	    STATIC_SYMBOL("SIMULATION-TIME-MANAGED-FLOAT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsimulation_time_managed_float,
	    Simulation_time_managed_float);
    Qinitialize_simulation_time_managed_float = 
	    STATIC_SYMBOL("INITIALIZE-SIMULATION-TIME-MANAGED-FLOAT",
	    AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_simulation_time_managed_float);
    record_system_variable(Qsimulation_time_managed_float,Qsimulate1,
	    list_constant_4,Qnil,Qnil,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qinitialize_simulation_time_managed_float,
	    STATIC_FUNCTION(initialize_simulation_time_managed_float,NIL,
	    FALSE,0,0));
    Qnumber_of_variables_to_process_at_a_time = 
	    STATIC_SYMBOL("NUMBER-OF-VARIABLES-TO-PROCESS-AT-A-TIME",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qnumber_of_variables_to_process_at_a_time,
	    Number_of_variables_to_process_at_a_time);
    record_system_variable(Qnumber_of_variables_to_process_at_a_time,
	    Qsimulate1,FIX((SI_Long)100L),Qnil,Qnil,Qnil,Qnil);
    Qtask_for_display_of_simulation_time = 
	    STATIC_SYMBOL("*TASK-FOR-DISPLAY-OF-SIMULATION-TIME*",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtask_for_display_of_simulation_time,
	    Task_for_display_of_simulation_time);
    record_system_variable(Qtask_for_display_of_simulation_time,Qsimulate1,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qsimulation_time_accumulator = 
	    STATIC_SYMBOL("SIMULATION-TIME-ACCUMULATOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsimulation_time_accumulator,
	    Simulation_time_accumulator);
    Qinitialize_compound_simulation_time = 
	    STATIC_SYMBOL("INITIALIZE-COMPOUND-SIMULATION-TIME",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_compound_simulation_time,
	    STATIC_FUNCTION(initialize_compound_simulation_time,NIL,FALSE,
	    0,0));
    list_constant_5 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_compound_simulation_time);
    record_system_variable(Qsimulation_time_accumulator,Qsimulate1,
	    list_constant_5,Qnil,Qnil,Qnil,Qnil);
    Qsynchronous_model_queue = STATIC_SYMBOL("SYNCHRONOUS-MODEL-QUEUE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsynchronous_model_queue,
	    Synchronous_model_queue);
    Qinitialize_model_queue = STATIC_SYMBOL("INITIALIZE-MODEL-QUEUE",
	    AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_model_queue);
    Qreclaim_model_queue_function = 
	    STATIC_SYMBOL("RECLAIM-MODEL-QUEUE-FUNCTION",AB_package);
    record_system_variable(Qsynchronous_model_queue,Qsimulate1,
	    list_constant_6,Qnil,Qnil,Qreclaim_model_queue_function,Qt);
    Qas_fast_as_possible_model_queue = 
	    STATIC_SYMBOL("AS-FAST-AS-POSSIBLE-MODEL-QUEUE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qas_fast_as_possible_model_queue,
	    As_fast_as_possible_model_queue);
    record_system_variable(Qas_fast_as_possible_model_queue,Qsimulate1,
	    list_constant_6,Qnil,Qnil,Qreclaim_model_queue_function,Qt);
    Qcurrent_model_queue_qm = STATIC_SYMBOL("CURRENT-MODEL-QUEUE\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_model_queue_qm,Current_model_queue_qm);
    record_system_variable(Qcurrent_model_queue_qm,Qsimulate1,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qprocessing_as_fast_as_possible_models_qm = 
	    STATIC_SYMBOL("PROCESSING-AS-FAST-AS-POSSIBLE-MODELS\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qprocessing_as_fast_as_possible_models_qm,
	    Processing_as_fast_as_possible_models_qm);
    record_system_variable(Qprocessing_as_fast_as_possible_models_qm,
	    Qsimulate1,Nil,Qnil,Qnil,Qnil,Qnil);
    Qsimulator_initialized_as_data_server_qm = 
	    STATIC_SYMBOL("SIMULATOR-INITIALIZED-AS-DATA-SERVER\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsimulator_initialized_as_data_server_qm,
	    Simulator_initialized_as_data_server_qm);
    record_system_variable(Qsimulator_initialized_as_data_server_qm,
	    Qsimulate1,Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2_defstruct_structure_name_model_queue_g2_struct = 
	    STATIC_SYMBOL("MODEL-QUEUE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qmodel_queue = STATIC_SYMBOL("MODEL-QUEUE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_model_queue_g2_struct,
	    Qmodel_queue,Qab_name_of_unique_structure_type);
    mutate_global_property(Qmodel_queue,
	    Qg2_defstruct_structure_name_model_queue_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_model_queue == UNBOUND)
	The_type_description_of_model_queue = Nil;
    string_constant_13 = 
	    STATIC_STRING("43Dy8m83kmy1n83kmy8n8k1l8n0000000krk0k0");
    temp = The_type_description_of_model_queue;
    The_type_description_of_model_queue = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_13));
    mutate_global_property(Qg2_defstruct_structure_name_model_queue_g2_struct,
	    The_type_description_of_model_queue,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qmodel_queue,
	    The_type_description_of_model_queue,Qtype_description_of_type);
    Qoutstanding_model_queue_count = 
	    STATIC_SYMBOL("OUTSTANDING-MODEL-QUEUE-COUNT",AB_package);
    Qmodel_queue_structure_memory_usage = 
	    STATIC_SYMBOL("MODEL-QUEUE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_14 = STATIC_STRING("1q83kmy8s83-fMy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_model_queue_count);
    push_optimized_constant(Qmodel_queue_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_14));
    Qchain_of_available_model_queues = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-MODEL-QUEUES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_model_queues,
	    Chain_of_available_model_queues);
    record_system_variable(Qchain_of_available_model_queues,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qmodel_queue_count = STATIC_SYMBOL("MODEL-QUEUE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmodel_queue_count,Model_queue_count);
    record_system_variable(Qmodel_queue_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_model_queues_vector == UNBOUND)
	Chain_of_available_model_queues_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qmodel_queue_structure_memory_usage,
	    STATIC_FUNCTION(model_queue_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_model_queue_count,
	    STATIC_FUNCTION(outstanding_model_queue_count,NIL,FALSE,0,0));
    reclaim_structure_for_model_queue_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_model_queue,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qmodel_queue,
	    reclaim_structure_for_model_queue_1);
    SET_SYMBOL_FUNCTION(Qinitialize_model_queue,
	    STATIC_FUNCTION(initialize_model_queue,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qreclaim_model_queue_function,
	    STATIC_FUNCTION(reclaim_model_queue_function,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qneed_calls_to_simulate_until_consistent_with_gensym_time,
	    STATIC_FUNCTION(need_calls_to_simulate_until_consistent_with_gensym_time,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qsimulate_until_consistent_with_gensym_time,
	    STATIC_FUNCTION(simulate_until_consistent_with_gensym_time,NIL,
	    FALSE,0,0));
    Qneeds_to_be_initialized = STATIC_SYMBOL("NEEDS-TO-BE-INITIALIZED",
	    AB_package);
    Qneeds_to_be_shutdown = STATIC_SYMBOL("NEEDS-TO-BE-SHUTDOWN",AB_package);
    Qwaiting = STATIC_SYMBOL("WAITING",AB_package);
    Qsimulate_model_until_consistent_internal = 
	    STATIC_SYMBOL("SIMULATE-MODEL-UNTIL-CONSISTENT-INTERNAL",
	    AB_package);
    Qsimulate_one_cycle = STATIC_SYMBOL("SIMULATE-ONE-CYCLE",AB_package);
    string_constant_5 = 
	    STATIC_STRING("The simulator is not initialized and will not do anything. ~\n                       Restarting is recommended.");
    SET_SYMBOL_FUNCTION(Qsimulate_model_until_consistent_internal,
	    STATIC_FUNCTION(simulate_model_until_consistent_internal,NIL,
	    FALSE,0,0));
    Qsimulation_formulas_qm = STATIC_SYMBOL("SIMULATION-FORMULAS\?",
	    AB_package);
    Qsimulation_computation_methods = 
	    STATIC_SYMBOL("SIMULATION-COMPUTATION-METHODS",AB_package);
    Qput_simulation_computation_methods_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-SIMULATION-COMPUTATION-METHODS-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_simulation_computation_methods_where_slot_is_absent,
	    STATIC_FUNCTION(put_simulation_computation_methods_where_slot_is_absent,
	    NIL,FALSE,2,2));
    Qabsent_slot_putter = STATIC_SYMBOL("ABSENT-SLOT-PUTTER",AB_package);
    mutate_global_property(Qsimulation_computation_methods,
	    SYMBOL_FUNCTION(Qput_simulation_computation_methods_where_slot_is_absent),
	    Qabsent_slot_putter);
    SET_SYMBOL_FUNCTION(Qinitialize_simulator_as_data_server,
	    STATIC_FUNCTION(initialize_simulator_as_data_server,NIL,FALSE,
	    0,0));
    Qrunning = STATIC_SYMBOL("RUNNING",AB_package);
    float_constant = STATIC_FLOAT(0.0);
    Qcalculating_dependent_variables = 
	    STATIC_SYMBOL("CALCULATING-DEPENDENT-VARIABLES",AB_package);
    Qmake_and_initialize_variable_simulation_runtime_structure = 
	    STATIC_SYMBOL("MAKE-AND-INITIALIZE-VARIABLE-SIMULATION-RUNTIME-STRUCTURE",
	    AB_package);
    Qinitialize_runtime_simulation_information_for_variable = 
	    STATIC_SYMBOL("INITIALIZE-RUNTIME-SIMULATION-INFORMATION-FOR-VARIABLE",
	    AB_package);
    Qsimulation_details = STATIC_SYMBOL("SIMULATION-DETAILS",AB_package);
    SET_SYMBOL_FUNCTION(Qmake_and_initialize_variable_simulation_runtime_structure,
	    STATIC_FUNCTION(make_and_initialize_variable_simulation_runtime_structure,
	    NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qinitialize_runtime_simulation_information_for_variable,
	    STATIC_FUNCTION(initialize_runtime_simulation_information_for_variable,
	    NIL,FALSE,1,1));
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qrole_server = STATIC_SYMBOL("ROLE-SERVER",AB_package);
    Qconnected_to = STATIC_SYMBOL("CONNECTED-TO",AB_package);
    Qat_port = STATIC_SYMBOL("AT-PORT",AB_package);
    Qat_an_input = STATIC_SYMBOL("AT-AN-INPUT",AB_package);
    Qat_an_output = STATIC_SYMBOL("AT-AN-OUTPUT",AB_package);
    Qat_input_end = STATIC_SYMBOL("AT-INPUT-END",AB_package);
    Qat_output_end = STATIC_SYMBOL("AT-OUTPUT-END",AB_package);
    Qat_either_end = STATIC_SYMBOL("AT-EITHER-END",AB_package);
    list_constant_7 = STATIC_LIST((SI_Long)7L,Qconnected_to,Qat_port,
	    Qat_an_input,Qat_an_output,Qat_input_end,Qat_output_end,
	    Qat_either_end);
    List_of_roles_that_can_be_cached = list_constant_7;
    Qg2_defstruct_structure_name_connection_g2_struct = 
	    STATIC_SYMBOL("CONNECTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qreset_sort_flag = STATIC_SYMBOL("RESET-SORT-FLAG",AB_package);
    SET_SYMBOL_FUNCTION(Qreset_sort_flag,STATIC_FUNCTION(reset_sort_flag,
	    NIL,FALSE,1,1));
    Qbeing_sorted = STATIC_SYMBOL("BEING-SORTED",AB_package);
    Qunsorted = STATIC_SYMBOL("UNSORTED",AB_package);
    Qsorted = STATIC_SYMBOL("SORTED",AB_package);
    Qcompute_and_initialize_state_variable = 
	    STATIC_SYMBOL("COMPUTE-AND-INITIALIZE-STATE-VARIABLE",AB_package);
    SET_SYMBOL_FUNCTION(Qcompute_and_initialize_state_variable,
	    STATIC_FUNCTION(compute_and_initialize_state_variable,NIL,
	    FALSE,1,1));
    Qnon_default_initial_simulated_value_qm = 
	    STATIC_SYMBOL("NON-DEFAULT-INITIAL-SIMULATED-VALUE\?",AB_package);
    Qlong = STATIC_SYMBOL("LONG",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qboolean = STATIC_SYMBOL("BOOLEAN",AB_package);
    Quse_initial_value_expression_in_generic_simulation_formula = 
	    STATIC_SYMBOL("USE-INITIAL-VALUE-EXPRESSION-IN-GENERIC-SIMULATION-FORMULA",
	    AB_package);
    Qab_let = STATIC_SYMBOL("LET",AB_package);
    Qcurrent_parameter_value = STATIC_SYMBOL("CURRENT-PARAMETER-VALUE",
	    AB_package);
    Qwork_completed_for_this_cycle = 
	    STATIC_SYMBOL("WORK-COMPLETED-FOR-THIS-CYCLE",AB_package);
    Qno_work_done_yet_for_this_cycle = 
	    STATIC_SYMBOL("NO-WORK-DONE-YET-FOR-THIS-CYCLE",AB_package);
    Qreset_new_value_computed_slot = 
	    STATIC_SYMBOL("RESET-NEW-VALUE-COMPUTED-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qreset_new_value_computed_slot,
	    STATIC_FUNCTION(reset_new_value_computed_slot,NIL,FALSE,1,1));
    Qhandle_newly_simulated_variable_if_necessary = 
	    STATIC_SYMBOL("HANDLE-NEWLY-SIMULATED-VARIABLE-IF-NECESSARY",
	    AB_package);
    Qgenerate_new_runtime_simulation_formula = 
	    STATIC_SYMBOL("GENERATE-NEW-RUNTIME-SIMULATION-FORMULA",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_newly_simulated_variable_if_necessary,
	    STATIC_FUNCTION(handle_newly_simulated_variable_if_necessary,
	    NIL,FALSE,1,1));
    Qsuppress_first_update = STATIC_SYMBOL("SUPPRESS-FIRST-UPDATE",AB_package);
    SET_SYMBOL_FUNCTION(Qgenerate_new_runtime_simulation_formula,
	    STATIC_FUNCTION(generate_new_runtime_simulation_formula,NIL,
	    FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qshutdown_simulator,
	    STATIC_FUNCTION(shutdown_simulator,NIL,TRUE,0,2));
    Qmodel_simulation_status = STATIC_SYMBOL("MODEL-SIMULATION-STATUS",
	    AB_package);
    Qnot_running = STATIC_SYMBOL("NOT-RUNNING",AB_package);
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qcontinue_data_server_data_acceptance = 
	    STATIC_SYMBOL("CONTINUE-DATA-SERVER-DATA-ACCEPTANCE",AB_package);
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    Qstatement = STATIC_SYMBOL("STATEMENT",AB_package);
    Qg2_defstruct_structure_name_variable_group_update_structure_g2_struct 
	    = STATIC_SYMBOL("VARIABLE-GROUP-UPDATE-STRUCTURE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qvariable_group_update_structure = 
	    STATIC_SYMBOL("VARIABLE-GROUP-UPDATE-STRUCTURE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_variable_group_update_structure_g2_struct,
	    Qvariable_group_update_structure,
	    Qab_name_of_unique_structure_type);
    mutate_global_property(Qvariable_group_update_structure,
	    Qg2_defstruct_structure_name_variable_group_update_structure_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_variable_group_update_structure == UNBOUND)
	The_type_description_of_variable_group_update_structure = Nil;
    string_constant_15 = 
	    STATIC_STRING("43Dy8m83oRy1n83oRy8n8k1l8n0000000krk0k0");
    temp = The_type_description_of_variable_group_update_structure;
    The_type_description_of_variable_group_update_structure = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_15));
    mutate_global_property(Qg2_defstruct_structure_name_variable_group_update_structure_g2_struct,
	    The_type_description_of_variable_group_update_structure,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qvariable_group_update_structure,
	    The_type_description_of_variable_group_update_structure,
	    Qtype_description_of_type);
    Qoutstanding_variable_group_update_structure_count = 
	    STATIC_SYMBOL("OUTSTANDING-VARIABLE-GROUP-UPDATE-STRUCTURE-COUNT",
	    AB_package);
    Qvariable_group_update_structure_structure_memory_usage = 
	    STATIC_SYMBOL("VARIABLE-GROUP-UPDATE-STRUCTURE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_16 = STATIC_STRING("1q83oRy8s83-wFy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_variable_group_update_structure_count);
    push_optimized_constant(Qvariable_group_update_structure_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_16));
    Qchain_of_available_variable_group_update_structures = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-VARIABLE-GROUP-UPDATE-STRUCTURES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_variable_group_update_structures,
	    Chain_of_available_variable_group_update_structures);
    record_system_variable(Qchain_of_available_variable_group_update_structures,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qvariable_group_update_structure_count = 
	    STATIC_SYMBOL("VARIABLE-GROUP-UPDATE-STRUCTURE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qvariable_group_update_structure_count,
	    Variable_group_update_structure_count);
    record_system_variable(Qvariable_group_update_structure_count,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_variable_group_update_structures_vector == UNBOUND)
	Chain_of_available_variable_group_update_structures_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qvariable_group_update_structure_structure_memory_usage,
	    STATIC_FUNCTION(variable_group_update_structure_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_variable_group_update_structure_count,
	    STATIC_FUNCTION(outstanding_variable_group_update_structure_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_variable_group_update_structure_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_variable_group_update_structure,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qvariable_group_update_structure,
	    reclaim_structure_for_variable_group_update_structure_1);
    Qg2_defstruct_structure_name_group_index_structure_g2_struct = 
	    STATIC_SYMBOL("GROUP-INDEX-STRUCTURE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qgroup_index_structure = STATIC_SYMBOL("GROUP-INDEX-STRUCTURE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_group_index_structure_g2_struct,
	    Qgroup_index_structure,Qab_name_of_unique_structure_type);
    mutate_global_property(Qgroup_index_structure,
	    Qg2_defstruct_structure_name_group_index_structure_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_group_index_structure == UNBOUND)
	The_type_description_of_group_index_structure = Nil;
    string_constant_17 = 
	    STATIC_STRING("43Dy8m83iCy1n83iCy8n8k1l8n0000000kmk0k0");
    temp = The_type_description_of_group_index_structure;
    The_type_description_of_group_index_structure = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_17));
    mutate_global_property(Qg2_defstruct_structure_name_group_index_structure_g2_struct,
	    The_type_description_of_group_index_structure,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qgroup_index_structure,
	    The_type_description_of_group_index_structure,
	    Qtype_description_of_type);
    Qoutstanding_group_index_structure_count = 
	    STATIC_SYMBOL("OUTSTANDING-GROUP-INDEX-STRUCTURE-COUNT",
	    AB_package);
    Qgroup_index_structure_structure_memory_usage = 
	    STATIC_SYMBOL("GROUP-INDEX-STRUCTURE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_18 = STATIC_STRING("1q83iCy8s83-XIy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_group_index_structure_count);
    push_optimized_constant(Qgroup_index_structure_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_18));
    Qchain_of_available_group_index_structures = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-GROUP-INDEX-STRUCTURES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_group_index_structures,
	    Chain_of_available_group_index_structures);
    record_system_variable(Qchain_of_available_group_index_structures,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qgroup_index_structure_count = 
	    STATIC_SYMBOL("GROUP-INDEX-STRUCTURE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgroup_index_structure_count,
	    Group_index_structure_count);
    record_system_variable(Qgroup_index_structure_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_group_index_structures_vector == UNBOUND)
	Chain_of_available_group_index_structures_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qgroup_index_structure_structure_memory_usage,
	    STATIC_FUNCTION(group_index_structure_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_group_index_structure_count,
	    STATIC_FUNCTION(outstanding_group_index_structure_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_group_index_structure_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_group_index_structure,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qgroup_index_structure,
	    reclaim_structure_for_group_index_structure_1);
    SET_SYMBOL_FUNCTION(Qcollect_one_shot_data_for_simulator,
	    STATIC_FUNCTION(collect_one_shot_data_for_simulator,NIL,TRUE,1,3));
    Qsend_one_value = STATIC_SYMBOL("SEND-ONE-VALUE",AB_package);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qbegin_collecting_data_for_simulator,
	    STATIC_FUNCTION(begin_collecting_data_for_simulator,NIL,TRUE,2,4));
    Qlong_time_ago = STATIC_SYMBOL("LONG-TIME-AGO",AB_package);
    Qg2_defstruct_structure_name_data_server_g2_struct = 
	    STATIC_SYMBOL("DATA-SERVER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    SET_SYMBOL_FUNCTION(Qstop_collecting_data_for_simulator,
	    STATIC_FUNCTION(stop_collecting_data_for_simulator,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qset_external_variable_for_simulator,
	    STATIC_FUNCTION(set_external_variable_for_simulator,NIL,TRUE,2,3));
}
