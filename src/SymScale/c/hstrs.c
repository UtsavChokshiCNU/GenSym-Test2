/* hstrs.c
 * Input file:  histories.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "hstrs.h"


DEFINE_VARIABLE_WITH_SYMBOL(Available_history_conses, Qavailable_history_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_history_conses_tail, Qavailable_history_conses_tail);

Object Available_history_conses_vector = UNBOUND;

Object Available_history_conses_tail_vector = UNBOUND;

Object History_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(History_cons_counter, Qhistory_cons_counter);

/* OUTSTANDING-HISTORY-CONSES */
Object outstanding_history_conses()
{
    Object temp;

    x_note_fn_call(148,0);
    temp = FIXNUM_MINUS(History_cons_counter,length(Available_history_conses));
    return VALUES_1(temp);
}

/* HISTORY-CONS-MEMORY-USAGE */
Object history_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(148,1);
    temp = FIXNUM_TIMES(History_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-HISTORY-CONS-POOL */
Object replenish_history_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(148,2);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qhistory_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_history_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_history_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_history_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_history_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_history_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = History_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qhistory;            /* history */

/* HISTORY-CONS-1 */
Object history_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(148,3);
    new_cons = ISVREF(Available_history_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_history_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_history_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_history_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_history_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qhistory);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-HISTORY-LIST-POOL */
Object replenish_history_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(148,4);
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
    if (ISVREF(Available_history_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_history_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_history_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_history_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_history_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qhistory_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-HISTORY-LIST-1 */
Object make_history_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(148,5);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_history_conses_vector,
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
	replenish_history_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_history_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qhistory);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_history_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_history_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_history_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_history_conses_tail_vector;
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

/* HISTORY-LIST-2 */
Object history_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(148,6);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_history_conses_vector,IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_history_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_history_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qhistory);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_history_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_history_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_history_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_history_conses_tail_vector;
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

/* HISTORY-LIST-3 */
Object history_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(148,7);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_history_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_history_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_history_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qhistory);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_history_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_history_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_history_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_history_conses_tail_vector;
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

/* HISTORY-LIST-4 */
Object history_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(148,8);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_history_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_history_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_history_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qhistory);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_history_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_history_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_history_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_history_conses_tail_vector;
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

/* HISTORY-LIST-TRACE-HOOK */
Object history_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(148,9);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-HISTORY-CONSES-1 */
Object copy_tree_using_history_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(148,10);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_history_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_history_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_history_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_history_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_history_cons_pool();
	temp_1 = copy_tree_using_history_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qhistory);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_history_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_history_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_history_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_history_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_history_cons_pool();
	temp_1 = copy_tree_using_history_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qhistory);
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

/* COPY-LIST-USING-HISTORY-CONSES-1 */
Object copy_list_using_history_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(148,11);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_history_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_history_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_history_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_history_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_history_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qhistory);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_history_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_history_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_history_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_history_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_history_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qhistory);
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

/* RECLAIM-HISTORY-CONS-1 */
Object reclaim_history_cons_1(history_cons)
    Object history_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(148,12);
    inline_note_reclaim_cons(history_cons,Qhistory);
    if (ISVREF(Available_history_conses_tail_vector,
	    IFIX(Current_thread_index))) {
	temp = ISVREF(Available_history_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = history_cons;
	temp = Available_history_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = history_cons;
    }
    else {
	temp = Available_history_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = history_cons;
	temp = Available_history_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = history_cons;
    }
    M_CDR(history_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-HISTORY-LIST-1 */
Object reclaim_history_list_1(history_list)
    Object history_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(148,13);
    if (history_list) {
	last_1 = history_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qhistory);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qhistory);
	if (ISVREF(Available_history_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_history_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = history_list;
	    temp = Available_history_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_history_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = history_list;
	    temp = Available_history_conses_tail_vector;
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

/* RECLAIM-HISTORY-LIST*-1 */
Object reclaim_history_list_star_1(history_list)
    Object history_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(148,14);
    if (CONSP(history_list)) {
	temp = last(history_list,_);
	M_CDR(temp) = Nil;
	if (history_list) {
	    last_1 = history_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qhistory);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qhistory);
	    if (ISVREF(Available_history_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_history_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = history_list;
		temp = Available_history_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_history_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = history_list;
		temp = Available_history_conses_tail_vector;
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

/* RECLAIM-HISTORY-TREE-1 */
Object reclaim_history_tree_1(tree)
    Object tree;
{
    Object e, e2, history_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(148,15);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_history_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		history_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(history_cons,Qhistory);
		if (EQ(history_cons,e))
		    goto end_1;
		else if ( !TRUEP(history_cons))
		    goto end_1;
		else
		    history_cons = CDR(history_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_history_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_history_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_history_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_history_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_history_conses_tail_vector;
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

/* DELETE-HISTORY-ELEMENT-1 */
Object delete_history_element_1(element,history_list)
    Object element, history_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(148,16);
    if (history_list) {
	if (EQ(element,M_CAR(history_list))) {
	    temp = CDR(history_list);
	    inline_note_reclaim_cons(history_list,Qhistory);
	    if (ISVREF(Available_history_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_history_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = history_list;
		temp_1 = Available_history_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = history_list;
	    }
	    else {
		temp_1 = Available_history_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = history_list;
		temp_1 = Available_history_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = history_list;
	    }
	    M_CDR(history_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = history_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qhistory);
		if (ISVREF(Available_history_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_history_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_history_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_history_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_history_conses_tail_vector;
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
	    temp = history_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-HISTORY-CONS-1 */
Object delete_history_cons_1(history_cons,history_list)
    Object history_cons, history_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(148,17);
    if (EQ(history_cons,history_list))
	temp = CDR(history_list);
    else {
	l_trailer_qm = Nil;
	l = history_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,history_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = history_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_history_cons_1(history_cons);
    return VALUES_1(temp);
}

Object The_type_description_of_history_ring_buffer = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_history_ring_buffers, Qchain_of_available_history_ring_buffers);

DEFINE_VARIABLE_WITH_SYMBOL(History_ring_buffer_count, Qhistory_ring_buffer_count);

Object Chain_of_available_history_ring_buffers_vector = UNBOUND;

/* HISTORY-RING-BUFFER-STRUCTURE-MEMORY-USAGE */
Object history_ring_buffer_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(148,18);
    temp = History_ring_buffer_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)8L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-HISTORY-RING-BUFFER-COUNT */
Object outstanding_history_ring_buffer_count()
{
    Object def_structure_history_ring_buffer_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(148,19);
    gensymed_symbol = IFIX(History_ring_buffer_count);
    def_structure_history_ring_buffer_variable = 
	    Chain_of_available_history_ring_buffers;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_history_ring_buffer_variable))
	goto end_loop;
    def_structure_history_ring_buffer_variable = 
	    ISVREF(def_structure_history_ring_buffer_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-HISTORY-RING-BUFFER-1 */
Object reclaim_history_ring_buffer_1(history_ring_buffer)
    Object history_ring_buffer;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(148,20);
    inline_note_reclaim_cons(history_ring_buffer,Nil);
    structure_being_reclaimed = history_ring_buffer;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_ring_buffer_vector(ISVREF(history_ring_buffer,(SI_Long)6L));
      SVREF(history_ring_buffer,FIX((SI_Long)6L)) = Nil;
      reclaim_ring_buffer_vector(ISVREF(history_ring_buffer,(SI_Long)7L));
      SVREF(history_ring_buffer,FIX((SI_Long)7L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_history_ring_buffers_vector,
	    IFIX(Current_thread_index));
    SVREF(history_ring_buffer,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_history_ring_buffers_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = history_ring_buffer;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-HISTORY-RING-BUFFER */
Object reclaim_structure_for_history_ring_buffer(history_ring_buffer)
    Object history_ring_buffer;
{
    x_note_fn_call(148,21);
    return reclaim_history_ring_buffer_1(history_ring_buffer);
}

static Object Qg2_defstruct_structure_name_history_ring_buffer_g2_struct;  /* g2-defstruct-structure-name::history-ring-buffer-g2-struct */

/* MAKE-PERMANENT-HISTORY-RING-BUFFER-STRUCTURE-INTERNAL */
Object make_permanent_history_ring_buffer_structure_internal()
{
    Object def_structure_history_ring_buffer_variable;
    Object defstruct_g2_history_ring_buffer_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(148,22);
    def_structure_history_ring_buffer_variable = Nil;
    atomic_incff_symval(Qhistory_ring_buffer_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_history_ring_buffer_variable = Nil;
	gensymed_symbol = (SI_Long)8L;
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
	defstruct_g2_history_ring_buffer_variable = the_array;
	SVREF(defstruct_g2_history_ring_buffer_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_history_ring_buffer_g2_struct;
	SVREF(defstruct_g2_history_ring_buffer_variable,FIX((SI_Long)1L)) 
		= Nil;
	SVREF(defstruct_g2_history_ring_buffer_variable,FIX((SI_Long)2L)) 
		= Nil;
	SVREF(defstruct_g2_history_ring_buffer_variable,FIX((SI_Long)3L)) 
		= Nil;
	SVREF(defstruct_g2_history_ring_buffer_variable,FIX((SI_Long)4L)) 
		= Nil;
	SVREF(defstruct_g2_history_ring_buffer_variable,FIX((SI_Long)5L)) 
		= Nil;
	def_structure_history_ring_buffer_variable = 
		defstruct_g2_history_ring_buffer_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_history_ring_buffer_variable);
}

/* MAKE-HISTORY-RING-BUFFER-1 */
Object make_history_ring_buffer_1()
{
    Object def_structure_history_ring_buffer_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(148,23);
    def_structure_history_ring_buffer_variable = 
	    ISVREF(Chain_of_available_history_ring_buffers_vector,
	    IFIX(Current_thread_index));
    if (def_structure_history_ring_buffer_variable) {
	svref_arg_1 = Chain_of_available_history_ring_buffers_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_history_ring_buffer_variable,(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_history_ring_buffer_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_history_ring_buffer_g2_struct;
    }
    else
	def_structure_history_ring_buffer_variable = 
		make_permanent_history_ring_buffer_structure_internal();
    inline_note_allocate_cons(def_structure_history_ring_buffer_variable,Nil);
    ISVREF(def_structure_history_ring_buffer_variable,(SI_Long)1L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_history_ring_buffer_variable,(SI_Long)2L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_history_ring_buffer_variable,FIX((SI_Long)3L)) = T;
    ISVREF(def_structure_history_ring_buffer_variable,(SI_Long)4L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_history_ring_buffer_variable,(SI_Long)5L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_history_ring_buffer_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_history_ring_buffer_variable,FIX((SI_Long)7L)) = Nil;
    return VALUES_1(def_structure_history_ring_buffer_variable);
}

/* COPY-HISTORY-RING-BUFFER */
Object copy_history_ring_buffer varargs_1(int, n)
{
    Object ring_buffer;
    Object new_shell, svref_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(148,24);
    INIT_ARGS_nonrelocating();
    ring_buffer = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    new_shell = make_history_ring_buffer_1();
    copy_ring_buffer_shell_slots(ring_buffer,new_shell);
    svref_new_value = copy_ring_buffer_vector(ISVREF(ring_buffer,(SI_Long)6L));
    SVREF(new_shell,FIX((SI_Long)6L)) = svref_new_value;
    svref_new_value = copy_ring_buffer_vector(ISVREF(ring_buffer,(SI_Long)7L));
    SVREF(new_shell,FIX((SI_Long)7L)) = svref_new_value;
    return VALUES_1(new_shell);
}

Object The_type_description_of_cascaded_ring_buffer = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_cascaded_ring_buffers, Qchain_of_available_cascaded_ring_buffers);

DEFINE_VARIABLE_WITH_SYMBOL(Cascaded_ring_buffer_count, Qcascaded_ring_buffer_count);

Object Chain_of_available_cascaded_ring_buffers_vector = UNBOUND;

/* CASCADED-RING-BUFFER-STRUCTURE-MEMORY-USAGE */
Object cascaded_ring_buffer_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(148,25);
    temp = Cascaded_ring_buffer_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)12L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-CASCADED-RING-BUFFER-COUNT */
Object outstanding_cascaded_ring_buffer_count()
{
    Object def_structure_cascaded_ring_buffer_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(148,26);
    gensymed_symbol = IFIX(Cascaded_ring_buffer_count);
    def_structure_cascaded_ring_buffer_variable = 
	    Chain_of_available_cascaded_ring_buffers;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_cascaded_ring_buffer_variable))
	goto end_loop;
    def_structure_cascaded_ring_buffer_variable = 
	    ISVREF(def_structure_cascaded_ring_buffer_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-CASCADED-RING-BUFFER-1 */
Object reclaim_cascaded_ring_buffer_1(cascaded_ring_buffer)
    Object cascaded_ring_buffer;
{
    Object temp, svref_arg_2;

    x_note_fn_call(148,27);
    inline_note_reclaim_cons(cascaded_ring_buffer,Nil);
    temp = ISVREF(Chain_of_available_cascaded_ring_buffers_vector,
	    IFIX(Current_thread_index));
    SVREF(cascaded_ring_buffer,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_cascaded_ring_buffers_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = cascaded_ring_buffer;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-CASCADED-RING-BUFFER */
Object reclaim_structure_for_cascaded_ring_buffer(cascaded_ring_buffer)
    Object cascaded_ring_buffer;
{
    x_note_fn_call(148,28);
    return reclaim_cascaded_ring_buffer_1(cascaded_ring_buffer);
}

static Object Qg2_defstruct_structure_name_cascaded_ring_buffer_g2_struct;  /* g2-defstruct-structure-name::cascaded-ring-buffer-g2-struct */

/* MAKE-PERMANENT-CASCADED-RING-BUFFER-STRUCTURE-INTERNAL */
Object make_permanent_cascaded_ring_buffer_structure_internal()
{
    Object def_structure_cascaded_ring_buffer_variable;
    Object defstruct_g2_cascaded_ring_buffer_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(148,29);
    def_structure_cascaded_ring_buffer_variable = Nil;
    atomic_incff_symval(Qcascaded_ring_buffer_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_cascaded_ring_buffer_variable = Nil;
	gensymed_symbol = (SI_Long)12L;
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
	defstruct_g2_cascaded_ring_buffer_variable = the_array;
	SVREF(defstruct_g2_cascaded_ring_buffer_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_cascaded_ring_buffer_g2_struct;
	def_structure_cascaded_ring_buffer_variable = 
		defstruct_g2_cascaded_ring_buffer_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_cascaded_ring_buffer_variable);
}

/* MAKE-CASCADED-RING-BUFFER-1 */
Object make_cascaded_ring_buffer_1()
{
    Object def_structure_cascaded_ring_buffer_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(148,30);
    def_structure_cascaded_ring_buffer_variable = 
	    ISVREF(Chain_of_available_cascaded_ring_buffers_vector,
	    IFIX(Current_thread_index));
    if (def_structure_cascaded_ring_buffer_variable) {
	svref_arg_1 = Chain_of_available_cascaded_ring_buffers_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_cascaded_ring_buffer_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_cascaded_ring_buffer_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_cascaded_ring_buffer_g2_struct;
    }
    else
	def_structure_cascaded_ring_buffer_variable = 
		make_permanent_cascaded_ring_buffer_structure_internal();
    inline_note_allocate_cons(def_structure_cascaded_ring_buffer_variable,Nil);
    SVREF(def_structure_cascaded_ring_buffer_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_cascaded_ring_buffer_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_cascaded_ring_buffer_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_cascaded_ring_buffer_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_cascaded_ring_buffer_variable,FIX((SI_Long)5L)) = Nil;
    ISVREF(def_structure_cascaded_ring_buffer_variable,(SI_Long)6L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_cascaded_ring_buffer_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_cascaded_ring_buffer_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_cascaded_ring_buffer_variable,FIX((SI_Long)9L)) = T;
    SVREF(def_structure_cascaded_ring_buffer_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_cascaded_ring_buffer_variable,FIX((SI_Long)11L)) = Nil;
    return VALUES_1(def_structure_cascaded_ring_buffer_variable);
}

/* COPY-CASCADED-RING-BUFFER */
Object copy_cascaded_ring_buffer(cascaded_ring_buffer)
    Object cascaded_ring_buffer;
{
    Object new_cascaded_ring_buffer, svref_new_value;

    x_note_fn_call(148,31);
    new_cascaded_ring_buffer = make_cascaded_ring_buffer_1();
    svref_new_value = 
	    copy_tree_using_history_conses_1(ISVREF(cascaded_ring_buffer,
	    (SI_Long)1L));
    SVREF(new_cascaded_ring_buffer,FIX((SI_Long)1L)) = svref_new_value;
    svref_new_value = 
	    copy_tree_using_history_conses_1(ISVREF(cascaded_ring_buffer,
	    (SI_Long)2L));
    SVREF(new_cascaded_ring_buffer,FIX((SI_Long)2L)) = svref_new_value;
    svref_new_value = 
	    copy_tree_using_history_conses_1(ISVREF(cascaded_ring_buffer,
	    (SI_Long)3L));
    SVREF(new_cascaded_ring_buffer,FIX((SI_Long)3L)) = svref_new_value;
    return VALUES_1(new_cascaded_ring_buffer);
}

/* GET-NEWEST-ACTIVE-ELEMENT-INDEX-FOR-CASCADED-RING-BUFFER */
Object get_newest_active_element_index_for_cascaded_ring_buffer(cascaded_ring_buffer)
    Object cascaded_ring_buffer;
{
    Object temp, newest_ring_buffer;

    x_note_fn_call(148,32);
    temp = ISVREF(cascaded_ring_buffer,(SI_Long)4L);
    newest_ring_buffer = CAR(temp);
    return history_cons_1(newest_ring_buffer,ISVREF(newest_ring_buffer,
	    (SI_Long)1L));
}

/* GET-OLDEST-ACTIVE-ELEMENT-INDEX-FOR-CASCADED-RING-BUFFER */
Object get_oldest_active_element_index_for_cascaded_ring_buffer(cascaded_ring_buffer)
    Object cascaded_ring_buffer;
{
    Object temp, oldest_ring_buffer;

    x_note_fn_call(148,33);
    temp = last(ISVREF(cascaded_ring_buffer,(SI_Long)4L),_);
    oldest_ring_buffer = CAR(temp);
    return history_cons_1(oldest_ring_buffer,ISVREF(oldest_ring_buffer,
	    (SI_Long)2L));
}

/* INCREMENT-ACTIVE-ELEMENT-INDEX-FOR-CASCADED-RING-BUFFER */
Object increment_active_element_index_for_cascaded_ring_buffer(element_index,
	    cascaded_ring_buffer)
    Object element_index, cascaded_ring_buffer;
{
    Object ring_buffer, element_index_for_ring_buffer, temp;
    Object cascaded_ring_buffers, previous_ring_buffer, rest_of_ring_buffers;
    Object ab_loop_it_, cdr_new_value_1;
    SI_Long cdr_new_value;

    x_note_fn_call(148,34);
    ring_buffer = CAR(element_index);
    element_index_for_ring_buffer = CDR(element_index);
    temp = ISVREF(ring_buffer,(SI_Long)1L);
    if ( !NUM_EQ(element_index_for_ring_buffer,temp)) {
	cdr_new_value = FIXNUM_EQ(element_index_for_ring_buffer,
		FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ? 
		(SI_Long)0L : IFIX(FIXNUM_ADD1(element_index_for_ring_buffer));
	M_CDR(element_index) = FIX(cdr_new_value);
    }
    else {
	cascaded_ring_buffers = ISVREF(cascaded_ring_buffer,(SI_Long)4L);
	if (EQ(ring_buffer,CAR(cascaded_ring_buffers))) {
	    temp = last(cascaded_ring_buffers,_);
	    previous_ring_buffer = CAR(temp);
	}
	else {
	    rest_of_ring_buffers = cascaded_ring_buffers;
	    ab_loop_it_ = Nil;
	  next_loop:
	    if ( !TRUEP(rest_of_ring_buffers))
		goto end_loop;
	    ab_loop_it_ = EQ(CADR(rest_of_ring_buffers),ring_buffer) ? 
		    CAR(rest_of_ring_buffers) : Nil;
	    if (ab_loop_it_) {
		previous_ring_buffer = ab_loop_it_;
		goto end_1;
	    }
	    rest_of_ring_buffers = M_CDR(rest_of_ring_buffers);
	    goto next_loop;
	  end_loop:
	    previous_ring_buffer = Qnil;
	  end_1:;
	}
	M_CAR(element_index) = previous_ring_buffer;
	cdr_new_value_1 = ISVREF(previous_ring_buffer,(SI_Long)2L);
	M_CDR(element_index) = cdr_new_value_1;
    }
    return VALUES_1(element_index);
}

/* DECREMENT-ACTIVE-ELEMENT-INDEX-FOR-CASCADED-RING-BUFFER */
Object decrement_active_element_index_for_cascaded_ring_buffer(element_index,
	    cascaded_ring_buffer)
    Object element_index, cascaded_ring_buffer;
{
    Object ring_buffer, element_index_for_ring_buffer, temp;
    Object cascaded_ring_buffers, next_ring_buffer, rest_of_ring_buffers;
    Object ab_loop_it_, cdr_new_value_1;
    SI_Long cdr_new_value;

    x_note_fn_call(148,35);
    ring_buffer = CAR(element_index);
    element_index_for_ring_buffer = CDR(element_index);
    temp = ISVREF(ring_buffer,(SI_Long)2L);
    if ( !NUM_EQ(element_index_for_ring_buffer,temp)) {
	cdr_new_value = IFIX(element_index_for_ring_buffer) == (SI_Long)0L 
		? IFIX(FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) : 
		IFIX(FIXNUM_SUB1(element_index_for_ring_buffer));
	M_CDR(element_index) = FIX(cdr_new_value);
    }
    else {
	cascaded_ring_buffers = ISVREF(cascaded_ring_buffer,(SI_Long)4L);
	temp = last(cascaded_ring_buffers,_);
	if (EQ(ring_buffer,CAR(temp)))
	    next_ring_buffer = CAR(cascaded_ring_buffers);
	else {
	    rest_of_ring_buffers = cascaded_ring_buffers;
	    ab_loop_it_ = Nil;
	  next_loop:
	    if ( !TRUEP(rest_of_ring_buffers))
		goto end_loop;
	    ab_loop_it_ = EQ(CAR(rest_of_ring_buffers),ring_buffer) ? 
		    CADR(rest_of_ring_buffers) : Nil;
	    if (ab_loop_it_) {
		next_ring_buffer = ab_loop_it_;
		goto end_1;
	    }
	    rest_of_ring_buffers = M_CDR(rest_of_ring_buffers);
	    goto next_loop;
	  end_loop:
	    next_ring_buffer = Qnil;
	  end_1:;
	}
	M_CAR(element_index) = next_ring_buffer;
	cdr_new_value_1 = ISVREF(next_ring_buffer,(SI_Long)1L);
	M_CDR(element_index) = cdr_new_value_1;
    }
    return VALUES_1(element_index);
}

static Object Qtruth_value;        /* truth-value */

static Object Qfloat_array;        /* float-array */

/* GET-HISTORY-G2-TIME */
Object get_history_g2_time varargs_1(int, n)
{
    Object cascaded_ring_buffer, element_index;
    Object simulated_value_qm, temp, ring_buffer, base_time_qm, vector_1;
    Object value, history_time, amf_available_array_cons_qm, amf_array, temp_1;
    Object temp_2, amf_result, new_float;
    double aref_new_value, history_time_float, gensymed_symbol;
    double gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(148,36);
    INIT_ARGS_nonrelocating();
    cascaded_ring_buffer = REQUIRED_ARG_nonrelocating();
    element_index = REQUIRED_ARG_nonrelocating();
    simulated_value_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = ISVREF(cascaded_ring_buffer,(SI_Long)4L);
    ring_buffer = CAR(temp);
    base_time_qm = ISVREF(cascaded_ring_buffer,(SI_Long)10L);
    vector_1 = ISVREF(ring_buffer,(SI_Long)7L);
    if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
	    Managed_array_unique_marker)) {
	value = FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(vector_1,
		IFIX(FIXNUM_ADD(element_index,
		Managed_array_index_offset))) : ISVREF(ISVREF(vector_1,
		(IFIX(element_index) >>  -  - (SI_Long)10L) + (SI_Long)2L),
		IFIX(element_index) & (SI_Long)1023L);
	if (Nil) {
	    if (FIXNUM_EQ(value,Truth))
		history_time = Evaluation_true_value;
	    else if (FIXNUM_EQ(value,Falsity))
		history_time = Evaluation_false_value;
	    else
		history_time = eval_cons_1(value,Qtruth_value);
	}
	else
	    history_time = FIXNUMP(value) || value && SYMBOLP(value) ? 
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
	aref_new_value = DFLOAT_ISAREF_1(ISVREF(vector_1,
		(IFIX(element_index) >>  -  - (SI_Long)10L) + (SI_Long)2L),
		IFIX(element_index) & (SI_Long)1023L);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	history_time = new_float;
    }
    history_time_float = INLINE_DOUBLE_FLOAT_VECTOR_P(history_time) != 
	    (SI_Long)0L && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(history_time)) 
	    == (SI_Long)1L ? DFLOAT_ISAREF_1(history_time,(SI_Long)0L) : 0.0;
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(history_time) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(history_time)) == (SI_Long)1L)
	reclaim_managed_simple_float_array_of_length_1(history_time);
    if (FIXNUMP(history_time)) {
	gensymed_symbol = (double)IFIX(history_time);
	gensymed_symbol_1 = base_time_qm ? DFLOAT_ISAREF_1(base_time_qm,
		(SI_Long)0L) : 0.0;
	return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(gensymed_symbol + 
		gensymed_symbol_1));
    }
    else if (simulated_value_qm ||  !TRUEP(base_time_qm))
	return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(history_time_float));
    else
	return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(history_time_float + 
		DFLOAT_ISAREF_1(base_time_qm,(SI_Long)0L)));
}

/* GET-HISTORY-G2-TIME-AS-EVALUATION-VALUE */
Object get_history_g2_time_as_evaluation_value(cascaded_ring_buffer,
	    element_index,simulated_value_qm)
    Object cascaded_ring_buffer, element_index, simulated_value_qm;
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float, temp_2, ring_buffer, base_time_qm, vector_1, value;
    Object history_time, new_float_1;
    double aref_new_value, history_time_float, gensymed_symbol;
    double gensymed_symbol_1;

    x_note_fn_call(148,37);
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
    temp_2 = ISVREF(cascaded_ring_buffer,(SI_Long)4L);
    ring_buffer = CAR(temp_2);
    base_time_qm = ISVREF(cascaded_ring_buffer,(SI_Long)10L);
    vector_1 = ISVREF(ring_buffer,(SI_Long)7L);
    if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
	    Managed_array_unique_marker)) {
	value = FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(vector_1,
		IFIX(FIXNUM_ADD(element_index,
		Managed_array_index_offset))) : ISVREF(ISVREF(vector_1,
		(IFIX(element_index) >>  -  - (SI_Long)10L) + (SI_Long)2L),
		IFIX(element_index) & (SI_Long)1023L);
	if (Nil) {
	    if (FIXNUM_EQ(value,Truth))
		history_time = Evaluation_true_value;
	    else if (FIXNUM_EQ(value,Falsity))
		history_time = Evaluation_false_value;
	    else
		history_time = eval_cons_1(value,Qtruth_value);
	}
	else
	    history_time = FIXNUMP(value) || value && SYMBOLP(value) ? 
		    value : copy_evaluation_value_1(value);
    }
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
	new_float_1 = amf_result;
	aref_new_value = DFLOAT_ISAREF_1(ISVREF(vector_1,
		(IFIX(element_index) >>  -  - (SI_Long)10L) + (SI_Long)2L),
		IFIX(element_index) & (SI_Long)1023L);
	DFLOAT_ISASET_1(new_float_1,(SI_Long)0L,aref_new_value);
	history_time = new_float_1;
    }
    history_time_float = INLINE_DOUBLE_FLOAT_VECTOR_P(history_time) != 
	    (SI_Long)0L && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(history_time)) 
	    == (SI_Long)1L ? DFLOAT_ISAREF_1(history_time,(SI_Long)0L) : 0.0;
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(history_time) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(history_time)) == (SI_Long)1L)
	reclaim_managed_simple_float_array_of_length_1(history_time);
    if (FIXNUMP(history_time)) {
	gensymed_symbol = (double)IFIX(history_time);
	gensymed_symbol_1 = base_time_qm ? DFLOAT_ISAREF_1(base_time_qm,
		(SI_Long)0L) : 0.0;
	aref_new_value = gensymed_symbol + gensymed_symbol_1;
    }
    else if (simulated_value_qm ||  !TRUEP(base_time_qm))
	aref_new_value = history_time_float;
    else
	aref_new_value = history_time_float + DFLOAT_ISAREF_1(base_time_qm,
		(SI_Long)0L);
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
    return VALUES_1(new_float);
}

/* GET-HISTORY-CURRENT-TIME */
Object get_history_current_time(cascaded_ring_buffer,element_index,
	    simulated_history_qm)
    Object cascaded_ring_buffer, element_index, simulated_history_qm;
{
    Object temp;
    double temp_1;

    x_note_fn_call(148,38);
    if ( !TRUEP(simulated_history_qm)) {
	temp = get_history_g2_time(2,cascaded_ring_buffer,element_index);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(temp_1 - 
		DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L)));
    }
    else
	return get_history_g2_time(3,cascaded_ring_buffer,element_index,
		simulated_history_qm);
}

/* GET-HISTORY-CURRENT-TIME-AS-EVALUATION-VALUE */
Object get_history_current_time_as_evaluation_value(cascaded_ring_buffer,
	    element_index,simulated_history_qm)
    Object cascaded_ring_buffer, element_index, simulated_history_qm;
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float, temp_2;
    double temp_3, aref_new_value;

    x_note_fn_call(148,39);
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
    if ( !TRUEP(simulated_history_qm)) {
	temp_2 = get_history_g2_time(2,cascaded_ring_buffer,element_index);
	temp_3 = DOUBLE_FLOAT_TO_DOUBLE(temp_2);
	aref_new_value = temp_3 - DFLOAT_ISAREF_1(G2_time_at_start,
		(SI_Long)0L);
    }
    else {
	temp_2 = get_history_g2_time(3,cascaded_ring_buffer,element_index,
		simulated_history_qm);
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_2);
    }
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
    return VALUES_1(new_float);
}

/* GET-HISTORY-VALUE-FOR-RING-BUFFER-OR-CASCADE-FUNCTION */
Object get_history_value_for_ring_buffer_or_cascade_function(ring_buffer_or_cascaded_ring_buffer,
	    element_index)
    Object ring_buffer_or_cascaded_ring_buffer, element_index;
{
    Object vector_1, managed_number_or_value;

    x_note_fn_call(148,40);
    vector_1 = ISVREF(ring_buffer_or_cascaded_ring_buffer,(SI_Long)6L);
    if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
	    Managed_array_unique_marker)) {
	managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(vector_1,
		IFIX(FIXNUM_ADD(element_index,
		Managed_array_index_offset))) : ISVREF(ISVREF(vector_1,
		(IFIX(element_index) >>  -  - (SI_Long)10L) + (SI_Long)2L),
		IFIX(element_index) & (SI_Long)1023L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L)));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    return aref1(managed_number_or_value,FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    return copy_text_string(managed_number_or_value);
	else
	    return VALUES_1(managed_number_or_value);
    }
    else
	return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
		(IFIX(element_index) >>  -  - (SI_Long)10L) + (SI_Long)2L),
		IFIX(element_index) & (SI_Long)1023L)));
}

/* GET-HISTORY-VALUE-FOR-CASCADED-RING-BUFFER */
Object get_history_value_for_cascaded_ring_buffer(cascaded_ring_buffer,
	    element_index)
    Object cascaded_ring_buffer, element_index;
{
    Object vector_1, gensymed_symbol, managed_number_or_value;
    SI_Long gensymed_symbol_1;

    x_note_fn_call(148,41);
    vector_1 = ISVREF(CAR(element_index),(SI_Long)6L);
    if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
	    Managed_array_unique_marker)) {
	gensymed_symbol = CDR(element_index);
	managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(vector_1,
		IFIX(FIXNUM_ADD(gensymed_symbol,
		Managed_array_index_offset))) : ISVREF(ISVREF(vector_1,
		(IFIX(gensymed_symbol) >>  -  - (SI_Long)10L) + 
		(SI_Long)2L),IFIX(gensymed_symbol) & (SI_Long)1023L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L)));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    return aref1(managed_number_or_value,FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    return copy_text_string(managed_number_or_value);
	else
	    return VALUES_1(managed_number_or_value);
    }
    else {
	gensymed_symbol_1 = IFIX(CDR(element_index));
	gensymed_symbol = ISVREF(vector_1,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(gensymed_symbol,
		gensymed_symbol_1 & (SI_Long)1023L)));
    }
}

/* CASCADED-RING-BUFFER-INDICES-SAME-P */
Object cascaded_ring_buffer_indices_same_p(index_1,index_2)
    Object index_1, index_2;
{
    x_note_fn_call(148,42);
    if (EQ(CAR(index_1),CAR(index_2)))
	return VALUES_1(FIXNUM_EQ(CDR(index_1),CDR(index_2)) ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* ADD-CASCADED-RING-BUFFER-CLIENT */
Object add_cascaded_ring_buffer_client(thing,cascaded_ring_buffer)
    Object thing, cascaded_ring_buffer;
{
    Object history_modify_macro_using_test_arg_1, car_1, cdr_1, key_result;
    Object x_element, ab_loop_list_, ab_loop_it_, svref_new_value;
    char temp;

    x_note_fn_call(148,43);
    history_modify_macro_using_test_arg_1 = thing;
    car_1 = history_modify_macro_using_test_arg_1;
    cdr_1 = ISVREF(cascaded_ring_buffer,(SI_Long)11L);
    key_result = car_1;
    x_element = Nil;
    ab_loop_list_ = cdr_1;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    x_element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ = EQL(key_result,x_element) ? T : Nil;
    if (ab_loop_it_) {
	temp = TRUEP(ab_loop_it_);
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = TRUEP(Qnil);
  end_1:;
    svref_new_value = temp ? cdr_1 : history_cons_1(car_1,cdr_1);
    return VALUES_1(SVREF(cascaded_ring_buffer,FIX((SI_Long)11L)) = 
	    svref_new_value);
}

/* REMOVE-CASCADED-RING-BUFFER-CLIENT */
Object remove_cascaded_ring_buffer_client(thing,cascaded_ring_buffer)
    Object thing, cascaded_ring_buffer;
{
    Object svref_new_value;

    x_note_fn_call(148,44);
    svref_new_value = delete_history_element_1(thing,
	    ISVREF(cascaded_ring_buffer,(SI_Long)11L));
    return VALUES_1(SVREF(cascaded_ring_buffer,FIX((SI_Long)11L)) = 
	    svref_new_value);
}

/* CLEAR-CASCADED-RING-BUFFER-CLIENTS */
Object clear_cascaded_ring_buffer_clients(cascaded_ring_buffer)
    Object cascaded_ring_buffer;
{
    Object clients_qm;

    x_note_fn_call(148,45);
    clients_qm = ISVREF(cascaded_ring_buffer,(SI_Long)11L);
    if (clients_qm) {
	reclaim_history_list_1(clients_qm);
	return VALUES_1(SVREF(cascaded_ring_buffer,FIX((SI_Long)11L)) = Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qgeneric_history;    /* generic-history */

/* NOTIFY-CLIENT-OF-CHANGE-TO-CASCADED-RING-BUFFER */
Object notify_client_of_change_to_cascaded_ring_buffer(frame)
    Object frame;
{
    Object gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(148,46);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(Qgeneric_history,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
	update_generic_history_for_change_to_cascaded_ring_buffer(frame);
	return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* MAINTAIN-HIGH-WATER-MARKS */
Object maintain_high_water_marks(cascaded_ring_buffer,unnormalized_value)
    Object cascaded_ring_buffer, unnormalized_value;
{
    Object value, high_water_mark, low_water_mark, amf_available_array_cons_qm;
    Object amf_array, temp, temp_1, amf_result, new_float;
    double arg, arg_1, aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(148,47);
    if (NUMBERP(unnormalized_value)) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    if (FIXNUMP(unnormalized_value))
		value = 
			DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(unnormalized_value));
	    else if (INLINE_LONG_P(unnormalized_value) != (SI_Long)0L)
		value = convert_g2longint_to_double(unnormalized_value);
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(unnormalized_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(unnormalized_value)) == 
		    (SI_Long)1L)
		value = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(unnormalized_value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(unnormalized_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(unnormalized_value)) == 
		    (SI_Long)1L)
		value = aref1(unnormalized_value,FIX((SI_Long)0L));
	    else
		value = unnormalized_value;
	    if (ISVREF(cascaded_ring_buffer,(SI_Long)7L)) {
		high_water_mark = ISVREF(cascaded_ring_buffer,(SI_Long)7L);
		low_water_mark = ISVREF(cascaded_ring_buffer,(SI_Long)8L);
		arg = DOUBLE_FLOAT_TO_DOUBLE(value);
		arg_1 = DFLOAT_ISAREF_1(high_water_mark,(SI_Long)0L);
		if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
			!inline_nanp_for_comparison(arg_1)) {
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		    DFLOAT_ISASET_1(high_water_mark,(SI_Long)0L,
			    aref_new_value);
		    result = VALUES_1(Nil);
		}
		else {
		    arg = DOUBLE_FLOAT_TO_DOUBLE(value);
		    arg_1 = DFLOAT_ISAREF_1(low_water_mark,(SI_Long)0L);
		    if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) 
			    &&  !inline_nanp_for_comparison(arg_1)) {
			aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
			DFLOAT_ISASET_1(low_water_mark,(SI_Long)0L,
				aref_new_value);
			result = VALUES_1(Nil);
		    }
		    else
			result = VALUES_1(Qnil);
		}
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
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		SVREF(cascaded_ring_buffer,FIX((SI_Long)7L)) = new_float;
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
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		result = VALUES_1(SVREF(cascaded_ring_buffer,
			FIX((SI_Long)8L)) = new_float);
	    }
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* CLEAR-HIGH-WATER-MARKS */
Object clear_high_water_marks(cascaded_ring_buffer)
    Object cascaded_ring_buffer;
{
    Object managed_float;

    x_note_fn_call(148,48);
    if (ISVREF(cascaded_ring_buffer,(SI_Long)7L)) {
	managed_float = ISVREF(cascaded_ring_buffer,(SI_Long)7L);
	reclaim_managed_simple_float_array_of_length_1(managed_float);
	SVREF(cascaded_ring_buffer,FIX((SI_Long)7L)) = Nil;
	managed_float = ISVREF(cascaded_ring_buffer,(SI_Long)8L);
	reclaim_managed_simple_float_array_of_length_1(managed_float);
	return VALUES_1(SVREF(cascaded_ring_buffer,FIX((SI_Long)8L)) = Nil);
    }
    else
	return VALUES_1(Nil);
}

/* CLEAR-CASCADED-RING-BUFFER-BASE-TIME */
Object clear_cascaded_ring_buffer_base_time(cascaded_ring_buffer)
    Object cascaded_ring_buffer;
{
    Object managed_float;

    x_note_fn_call(148,49);
    if (ISVREF(cascaded_ring_buffer,(SI_Long)10L)) {
	managed_float = ISVREF(cascaded_ring_buffer,(SI_Long)10L);
	reclaim_managed_simple_float_array_of_length_1(managed_float);
	return VALUES_1(SVREF(cascaded_ring_buffer,FIX((SI_Long)10L)) = Nil);
    }
    else
	return VALUES_1(Nil);
}

/* CLEAR-HISTORIES */
Object clear_histories(variable)
    Object variable;
{
    Object buffer_of_stored_values_qm;

    x_note_fn_call(148,50);
    if (ISVREF(variable,(SI_Long)25L)) {
	buffer_of_stored_values_qm = ISVREF(variable,(SI_Long)24L);
	if (buffer_of_stored_values_qm)
	    clear_history_buffer(buffer_of_stored_values_qm);
    }
    return clear_simulation_history(variable);
}

static Object Qsimulation_details;  /* simulation-details */

/* CLEAR-SIMULATION-HISTORY */
Object clear_simulation_history(variable)
    Object variable;
{
    Object sub_class_bit_vector, buffer_of_stored_values_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(148,51);
    sub_class_bit_vector = ISVREF(ISVREF(variable,(SI_Long)1L),(SI_Long)19L);
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
    if (temp ? TRUEP(get_lookup_slot_value(variable,Qsimulation_details)) :
	     TRUEP(Nil)) {
	if (ISVREF(get_lookup_slot_value(variable,Qsimulation_details),
		(SI_Long)21L)) {
	    buffer_of_stored_values_qm = 
		    ISVREF(get_lookup_slot_value(variable,
		    Qsimulation_details),(SI_Long)20L);
	    if (buffer_of_stored_values_qm)
		clear_history_buffer(buffer_of_stored_values_qm);
	}
    }
    return VALUES_1(Nil);
}

/* CLEAR-SIMULATION-HISTORY-AT-RUNTIME */
Object clear_simulation_history_at_runtime(variable)
    Object variable;
{
    Object sub_class_bit_vector, simulation_details_qm;
    Object buffer_of_stored_values_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(148,52);
    sub_class_bit_vector = ISVREF(ISVREF(variable,(SI_Long)1L),(SI_Long)19L);
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
    simulation_details_qm = temp ? get_lookup_slot_value(variable,
	    Qsimulation_details) : Nil;
    buffer_of_stored_values_qm = simulation_details_qm && 
	    ISVREF(simulation_details_qm,(SI_Long)21L) ? 
	    ISVREF(simulation_details_qm,(SI_Long)20L) : Qnil;
    if (buffer_of_stored_values_qm)
	clear_history_buffer_at_runtime(variable,buffer_of_stored_values_qm);
    return VALUES_1(Nil);
}

/* CLEAR-HISTORY-BUFFER-AT-RUNTIME */
Object clear_history_buffer_at_runtime(variable_or_parameter,
	    buffer_of_stored_values)
    Object variable_or_parameter, buffer_of_stored_values;
{
    Object gensymed_symbol, ab_loop_list_;

    x_note_fn_call(148,53);
    if (Noting_changes_to_kb_p)
	note_change_to_runtime_data_for_block_1(variable_or_parameter);
    clear_history_buffer(buffer_of_stored_values);
    gensymed_symbol = Nil;
    ab_loop_list_ = ISVREF(buffer_of_stored_values,(SI_Long)11L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    gensymed_symbol = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    notify_client_of_change_to_cascaded_ring_buffer(gensymed_symbol);
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* CLEAR-HISTORY-BUFFER */
Object clear_history_buffer(buffer_of_stored_values)
    Object buffer_of_stored_values;
{
    x_note_fn_call(148,54);
    clear_cascaded_ring_buffer_base_time(buffer_of_stored_values);
    return clear_history_buffer_and_not_base_time(buffer_of_stored_values);
}

/* CLEAR-HISTORY-BUFFER-AND-NOT-BASE-TIME */
Object clear_history_buffer_and_not_base_time(buffer_of_stored_values)
    Object buffer_of_stored_values;
{
    Object ring_buffer, ab_loop_list_;

    x_note_fn_call(148,55);
    clear_high_water_marks(buffer_of_stored_values);
    ISVREF(buffer_of_stored_values,(SI_Long)6L) = FIX((SI_Long)0L);
    ring_buffer = Nil;
    ab_loop_list_ = ISVREF(buffer_of_stored_values,(SI_Long)4L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ring_buffer = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ISVREF(ring_buffer,(SI_Long)1L) = FIX((SI_Long)0L);
    ISVREF(ring_buffer,(SI_Long)2L) = FIX((SI_Long)0L);
    SVREF(ring_buffer,FIX((SI_Long)3L)) = T;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* CASCADED-RING-BUFFER-EMPTY? */
Object cascaded_ring_buffer_empty_qm(cascaded_buffer)
    Object cascaded_buffer;
{
    Object ring_buffer, ab_loop_list_;

    x_note_fn_call(148,56);
    ring_buffer = Nil;
    ab_loop_list_ = ISVREF(cascaded_buffer,(SI_Long)4L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ring_buffer = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ISVREF(ring_buffer,(SI_Long)3L)))
	return VALUES_1(Nil);
    goto next_loop;
  end_loop:
    return VALUES_1(T);
    return VALUES_1(Qnil);
}

/* RECLAIM-VARIABLE-OR-PARAMETER-STORED-HISTORIES?-VALUE */
Object reclaim_variable_or_parameter_stored_histories_qm_value(history_buffer_qm,
	    variable)
    Object history_buffer_qm, variable;
{
    x_note_fn_call(148,57);
    if (history_buffer_qm)
	reclaim_history_buffer(history_buffer_qm);
    return VALUES_1(Nil);
}

/* RECLAIM-SIMULATION-STORED-HISTORIES?-VALUE */
Object reclaim_simulation_stored_histories_qm_value(history_buffer_qm,
	    simulation_subtable)
    Object history_buffer_qm, simulation_subtable;
{
    x_note_fn_call(148,58);
    if (history_buffer_qm)
	reclaim_history_buffer(history_buffer_qm);
    return VALUES_1(Nil);
}

/* RECLAIM-HISTORY-BUFFER */
Object reclaim_history_buffer(cascaded_history_ring_buffer)
    Object cascaded_history_ring_buffer;
{
    Object history_ring_buffer, ab_loop_list_;

    x_note_fn_call(148,59);
    reclaim_history_tree_1(ISVREF(cascaded_history_ring_buffer,(SI_Long)3L));
    SVREF(cascaded_history_ring_buffer,FIX((SI_Long)3L)) = Nil;
    history_ring_buffer = Nil;
    ab_loop_list_ = ISVREF(cascaded_history_ring_buffer,(SI_Long)4L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    history_ring_buffer = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_history_ring_buffer_1(history_ring_buffer);
    goto next_loop;
  end_loop:;
    reclaim_history_list_1(ISVREF(cascaded_history_ring_buffer,(SI_Long)4L));
    clear_high_water_marks(cascaded_history_ring_buffer);
    clear_cascaded_ring_buffer_base_time(cascaded_history_ring_buffer);
    clear_cascaded_ring_buffer_clients(cascaded_history_ring_buffer);
    return reclaim_cascaded_ring_buffer_1(cascaded_history_ring_buffer);
}

/* G2-INITIALIZE-PARAMETER-AUX */
Object g2_initialize_parameter_aux(param)
    Object param;
{
    Object old_collection_time, svref_new_value;

    x_note_fn_call(148,60);
    old_collection_time = ISVREF(param,(SI_Long)21L);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(old_collection_time) != (SI_Long)0L 
	    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_collection_time)) == 
	    (SI_Long)1L)
	reclaim_managed_simple_float_array_of_length_1(old_collection_time);
    svref_new_value = Some_time_ago;
    ISVREF(param,(SI_Long)21L) = svref_new_value;
    return VALUES_1(Nil);
}

/* STORE-HISTORY-VALUE */
Object store_history_value(value_history_cascaded_ring_buffer,
	    history_specification,value,time_1,storing_simulated_value_qm)
    Object value_history_cascaded_ring_buffer, history_specification, value;
    Object time_1, storing_simulated_value_qm;
{
    Object gensymed_symbol, maximum_number_of_data_points_qm;
    Object history_granularity_qm, temp_1, base_time;
    Object amf_available_array_cons_qm, amf_array, temp_2, temp_3, amf_result;
    Object new_float, time_adjusted_for_history, ab_loop_list_;
    SI_Long temp_4, integer_granularity;
    char temp, overwrite_value_if_duplicate_time_qm;
    double base_time_value, time_value, time_offset, arg, arg_1, temp_5;
    double temp_6, floored_time_float, subsecond_time, float_granularity;

    x_note_fn_call(148,61);
    gensymed_symbol = history_specification;
    gensymed_symbol = CDR(gensymed_symbol);
    maximum_number_of_data_points_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    history_granularity_qm = CAR(gensymed_symbol);
    temp =  !TRUEP(maximum_number_of_data_points_qm);
    if (temp);
    else {
	temp_1 = FIX((SI_Long)0L);
	temp =  !NUM_EQ(temp_1,maximum_number_of_data_points_qm);
    }
    if (temp) {
	base_time = value_history_cascaded_ring_buffer ? 
		ISVREF(value_history_cascaded_ring_buffer,(SI_Long)10L) : Qnil;
	if (base_time);
	else if (storing_simulated_value_qm) {
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
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
	    base_time = new_float;
	}
	else
	    base_time = Nil;
	if (base_time);
	else
	    base_time = 
		    allocate_base_time_adjusted_for_granularity(history_granularity_qm);
	base_time_value = DFLOAT_ISAREF_1(base_time,(SI_Long)0L);
	temp_1 = normalize_to_gensym_float(time_1);
	time_value = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
	time_offset = storing_simulated_value_qm ? 0.0 : time_value - 
		base_time_value;
	if ( !TRUEP(history_granularity_qm) || 
		IFIX(history_granularity_qm) == (SI_Long)1000L) {
	    arg = time_offset;
	    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum_as_float);
	    time_adjusted_for_history = arg > arg_1 &&  
		    !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1) ? 
		    DOUBLE_TO_DOUBLE_FLOAT(inline_ffloor_1(time_offset)) : 
		    LONG_TO_FIXNUM(inline_floor_1(time_offset));
	}
	else if (IFIX(history_granularity_qm) == (SI_Long)0L)
	    time_adjusted_for_history = DOUBLE_TO_DOUBLE_FLOAT(time_offset);
	else if (IFIX(history_granularity_qm) > (SI_Long)1000L) {
	    temp_4 = IFIX(history_granularity_qm) / (SI_Long)1000L;
	    integer_granularity = temp_4;
	    temp_5 = (double)integer_granularity;
	    temp_6 = DOUBLE_FLOAT_TO_DOUBLE(History_timestamp_epsilon);
	    time_adjusted_for_history = DOUBLE_TO_DOUBLE_FLOAT(temp_5 * 
		    inline_ffloor_1((time_offset + temp_6) / 
		    (double)integer_granularity));
	}
	else {
	    floored_time_float = inline_ffloor_1(time_offset);
	    subsecond_time = time_offset - floored_time_float;
	    float_granularity = (double)IFIX(history_granularity_qm) / 1000.0;
	    temp_6 = DOUBLE_FLOAT_TO_DOUBLE(History_timestamp_epsilon);
	    time_adjusted_for_history = 
		    DOUBLE_TO_DOUBLE_FLOAT(floored_time_float + 
		    float_granularity * inline_ffloor_1((subsecond_time + 
		    temp_6) / float_granularity));
	}
	overwrite_value_if_duplicate_time_qm =  !(history_granularity_qm 
		&& IFIX(history_granularity_qm) == (SI_Long)0L);
	if ( !(ISVREF(value_history_cascaded_ring_buffer,(SI_Long)10L) || 
		storing_simulated_value_qm))
	    SVREF(value_history_cascaded_ring_buffer,FIX((SI_Long)10L)) = 
		    base_time;
	store_history_element_in_cascaded_ring_buffer(5,
		value_history_cascaded_ring_buffer,value,
		time_adjusted_for_history,
		overwrite_value_if_duplicate_time_qm ? T : Nil,
		storing_simulated_value_qm);
	gensymed_symbol = Nil;
	ab_loop_list_ = ISVREF(value_history_cascaded_ring_buffer,
		(SI_Long)11L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	gensymed_symbol = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	notify_client_of_change_to_cascaded_ring_buffer(gensymed_symbol);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* ALLOCATE-BASE-TIME-ADJUSTED-FOR-GRANULARITY */
Object allocate_base_time_adjusted_for_granularity(history_granularity_qm)
    Object history_granularity_qm;
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float;
    SI_Long temp_2, integer_granularity;
    double aref_new_value, temp_3, temp_4, floored_current_time;
    double subsecond_of_current_time, float_granularity, arg, arg_1;

    x_note_fn_call(148,62);
    if ( !TRUEP(history_granularity_qm) || IFIX(history_granularity_qm) == 
	    (SI_Long)1000L) {
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
	aref_new_value = inline_ffloor_1(DFLOAT_ISAREF_1(Current_g2_time,
		(SI_Long)0L));
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	return VALUES_1(new_float);
    }
    else if (IFIX(history_granularity_qm) == (SI_Long)0L)
	return copy_managed_float(Current_g2_time);
    else if (IFIX(history_granularity_qm) > (SI_Long)1000L) {
	temp_2 = IFIX(history_granularity_qm) / (SI_Long)1000L;
	integer_granularity = temp_2;
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
	temp_3 = (double)integer_granularity;
	temp_4 = DOUBLE_FLOAT_TO_DOUBLE(History_timestamp_epsilon);
	aref_new_value = temp_3 * 
		inline_ffloor_1((DFLOAT_ISAREF_1(Current_g2_time,
		(SI_Long)0L) + temp_4) / (double)integer_granularity);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	return VALUES_1(new_float);
    }
    else {
	floored_current_time = 
		inline_ffloor_1(DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L));
	subsecond_of_current_time = DFLOAT_ISAREF_1(Current_g2_time,
		(SI_Long)0L) - floored_current_time;
	float_granularity = (double)IFIX(history_granularity_qm) / 1000.0;
	arg = subsecond_of_current_time;
	arg_1 = float_granularity;
	if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) {
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
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,floored_current_time);
	    return VALUES_1(new_float);
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
	    temp_4 = DOUBLE_FLOAT_TO_DOUBLE(History_timestamp_epsilon);
	    aref_new_value = floored_current_time + float_granularity * 
		    inline_ffloor_1((subsecond_of_current_time + temp_4) / 
		    float_granularity);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    return VALUES_1(new_float);
	}
    }
}

/* GET-OR-MAKE-HISTORY-BUFFER */
Object get_or_make_history_buffer(frame,history_spec_qm)
    Object frame, history_spec_qm;
{
    Object value_history_cascaded_ring_buffer_qm, gensymed_symbol;
    Object sub_class_bit_vector, variable_or_parameter_p;
    Object maximum_number_of_data_points_qm, maximum_age_of_data_points_qm;
    Object millisecond_interval_between_data_points_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(148,63);
    if (history_spec_qm) {
	value_history_cascaded_ring_buffer_qm = Nil;
	gensymed_symbol = ISVREF(frame,(SI_Long)1L);
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
	if (temp)
	    variable_or_parameter_p = T;
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
		variable_or_parameter_p = Nil;
	    else
		variable_or_parameter_p = Qnil;
	}
	value_history_cascaded_ring_buffer_qm = variable_or_parameter_p ? 
		ISVREF(frame,(SI_Long)24L) : ISVREF(frame,(SI_Long)20L);
	if ( !TRUEP(value_history_cascaded_ring_buffer_qm)) {
	    gensymed_symbol = history_spec_qm;
	    gensymed_symbol = CDR(gensymed_symbol);
	    maximum_number_of_data_points_qm = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    maximum_age_of_data_points_qm = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    millisecond_interval_between_data_points_qm = CAR(gensymed_symbol);
	    value_history_cascaded_ring_buffer_qm = 
		    make_or_reformat_cascaded_ring_buffer(Nil,
		    maximum_number_of_data_points_qm,
		    maximum_age_of_data_points_qm,
		    millisecond_interval_between_data_points_qm);
	    if (variable_or_parameter_p)
		ISVREF(frame,(SI_Long)24L) = 
			value_history_cascaded_ring_buffer_qm;
	    else
		ISVREF(frame,(SI_Long)20L) = 
			value_history_cascaded_ring_buffer_qm;
	}
	return VALUES_1(value_history_cascaded_ring_buffer_qm);
    }
    else
	return VALUES_1(Nil);
}

/* MAKE-OR-REFORMAT-CASCADED-RING-BUFFER */
Object make_or_reformat_cascaded_ring_buffer(cascaded_ring_buffer_qm,
	    maximum_number_of_data_points_qm,maximum_age_of_data_points_qm,
	    millisecond_interval_between_data_points_qm)
    Object cascaded_ring_buffer_qm, maximum_number_of_data_points_qm;
    Object maximum_age_of_data_points_qm;
    Object millisecond_interval_between_data_points_qm;
{
    Object new_cascaded_ring_buffer, svref_new_value, temp;
    Object existing_ring_buffer_qm, ring_buffer_size, new_size_qm;
    Object oldest_active_element_index, ring_buffer, index_1;
    Object oldest_active_element_index_for_ring_buffer, next_larger_size;
    Object thing, ring_buffer_shell, size_to_allocate;
    SI_Long ring_buffer_length, svref_new_value_1;

    x_note_fn_call(148,64);
    new_cascaded_ring_buffer = cascaded_ring_buffer_qm;
    if (new_cascaded_ring_buffer);
    else
	new_cascaded_ring_buffer = make_cascaded_ring_buffer_1();
    if (cascaded_ring_buffer_qm) {
	reclaim_history_tree_1(ISVREF(new_cascaded_ring_buffer,(SI_Long)3L));
	SVREF(new_cascaded_ring_buffer,FIX((SI_Long)3L)) = Nil;
    }
    svref_new_value = 
	    history_cons_1(history_list_3(maximum_number_of_data_points_qm,
	    maximum_age_of_data_points_qm,
	    millisecond_interval_between_data_points_qm),Nil);
    SVREF(new_cascaded_ring_buffer,FIX((SI_Long)3L)) = svref_new_value;
    if (maximum_number_of_data_points_qm) {
	temp = ISVREF(new_cascaded_ring_buffer,(SI_Long)4L);
	existing_ring_buffer_qm = CAR(temp);
	if (existing_ring_buffer_qm) {
	    if (ISVREF(existing_ring_buffer_qm,(SI_Long)3L)) {
		reclaim_history_ring_buffer_1(existing_ring_buffer_qm);
		reclaim_history_list_1(ISVREF(new_cascaded_ring_buffer,
			(SI_Long)4L));
		SVREF(new_cascaded_ring_buffer,FIX((SI_Long)4L)) = Nil;
	    }
	    else {
		ring_buffer_size = ISVREF(existing_ring_buffer_qm,(SI_Long)4L);
		if (FIXNUM_GT(maximum_number_of_data_points_qm,
			ring_buffer_size)) {
		    new_size_qm = 
			    FIXNUM_MIN(Largest_ring_buffer_vector_size,
			    maximum_number_of_data_points_qm);
		    oldest_active_element_index = 
			    ISVREF(existing_ring_buffer_qm,(SI_Long)2L);
		    ring_buffer = existing_ring_buffer_qm;
		    index_1 = ISVREF(existing_ring_buffer_qm,(SI_Long)1L);
		    oldest_active_element_index_for_ring_buffer = 
			    ISVREF(ring_buffer,(SI_Long)2L);
		    ring_buffer_length = FIXNUM_GE(index_1,
			    oldest_active_element_index_for_ring_buffer) ? 
			    IFIX(FIXNUM_ADD1(FIXNUM_MINUS(index_1,
			    oldest_active_element_index_for_ring_buffer))) 
			    : 
			    IFIX(FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(index_1,
			    ISVREF(ring_buffer,(SI_Long)4L)),
			    oldest_active_element_index_for_ring_buffer)));
		    next_larger_size = new_size_qm;
		    if (next_larger_size);
		    else
			next_larger_size = 
				compute_next_larger_size_for_ring_buffer_vectors(ring_buffer_size);
		    thing = ISVREF(existing_ring_buffer_qm,(SI_Long)6L);
		    if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,
			    (SI_Long)0L),Managed_array_unique_marker)) {
			rotate_managed_array(ISVREF(existing_ring_buffer_qm,
				(SI_Long)6L),oldest_active_element_index);
			svref_new_value = adjust_managed_array(2,
				ISVREF(existing_ring_buffer_qm,
				(SI_Long)6L),next_larger_size);
			SVREF(existing_ring_buffer_qm,FIX((SI_Long)6L)) = 
				svref_new_value;
		    }
		    else {
			rotate_managed_float_array(ISVREF(existing_ring_buffer_qm,
				(SI_Long)6L),oldest_active_element_index);
			svref_new_value = adjust_managed_float_array(2,
				ISVREF(existing_ring_buffer_qm,
				(SI_Long)6L),next_larger_size);
			SVREF(existing_ring_buffer_qm,FIX((SI_Long)6L)) = 
				svref_new_value;
		    }
		    thing = ISVREF(existing_ring_buffer_qm,(SI_Long)7L);
		    if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,
			    (SI_Long)0L),Managed_array_unique_marker)) {
			rotate_managed_array(ISVREF(existing_ring_buffer_qm,
				(SI_Long)7L),oldest_active_element_index);
			svref_new_value = adjust_managed_array(2,
				ISVREF(existing_ring_buffer_qm,
				(SI_Long)7L),next_larger_size);
			SVREF(existing_ring_buffer_qm,FIX((SI_Long)7L)) = 
				svref_new_value;
		    }
		    else {
			rotate_managed_float_array(ISVREF(existing_ring_buffer_qm,
				(SI_Long)7L),oldest_active_element_index);
			svref_new_value = adjust_managed_float_array(2,
				ISVREF(existing_ring_buffer_qm,
				(SI_Long)7L),next_larger_size);
			SVREF(existing_ring_buffer_qm,FIX((SI_Long)7L)) = 
				svref_new_value;
		    }
		    ISVREF(existing_ring_buffer_qm,(SI_Long)2L) = 
			    FIX((SI_Long)0L);
		    svref_new_value_1 = ring_buffer_length - (SI_Long)1L;
		    ISVREF(existing_ring_buffer_qm,(SI_Long)1L) = 
			    FIX(svref_new_value_1);
		    SVREF(existing_ring_buffer_qm,FIX((SI_Long)4L)) = 
			    next_larger_size;
		}
		else if (FIXNUM_LT(maximum_number_of_data_points_qm,
			ring_buffer_size)) {
		    oldest_active_element_index = 
			    ISVREF(existing_ring_buffer_qm,(SI_Long)2L);
		    ring_buffer = existing_ring_buffer_qm;
		    index_1 = ISVREF(existing_ring_buffer_qm,(SI_Long)1L);
		    oldest_active_element_index_for_ring_buffer = 
			    ISVREF(ring_buffer,(SI_Long)2L);
		    ring_buffer_length = FIXNUM_GE(index_1,
			    oldest_active_element_index_for_ring_buffer) ? 
			    IFIX(FIXNUM_ADD1(FIXNUM_MINUS(index_1,
			    oldest_active_element_index_for_ring_buffer))) 
			    : 
			    IFIX(FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(index_1,
			    ISVREF(ring_buffer,(SI_Long)4L)),
			    oldest_active_element_index_for_ring_buffer)));
		    thing = ISVREF(existing_ring_buffer_qm,(SI_Long)6L);
		    if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,
			    (SI_Long)0L),Managed_array_unique_marker)) {
			rotate_managed_array(ISVREF(existing_ring_buffer_qm,
				(SI_Long)6L),oldest_active_element_index);
			if (IFIX(maximum_number_of_data_points_qm) < 
				ring_buffer_length)
			    rotate_managed_array(ISVREF(existing_ring_buffer_qm,
				    (SI_Long)6L),FIX(ring_buffer_length - 
				    IFIX(maximum_number_of_data_points_qm)));
			svref_new_value = adjust_managed_array(2,
				ISVREF(existing_ring_buffer_qm,
				(SI_Long)6L),maximum_number_of_data_points_qm);
			SVREF(existing_ring_buffer_qm,FIX((SI_Long)6L)) = 
				svref_new_value;
		    }
		    else {
			rotate_managed_float_array(ISVREF(existing_ring_buffer_qm,
				(SI_Long)6L),oldest_active_element_index);
			if (IFIX(maximum_number_of_data_points_qm) < 
				ring_buffer_length)
			    rotate_managed_float_array(ISVREF(existing_ring_buffer_qm,
				    (SI_Long)6L),FIX(ring_buffer_length - 
				    IFIX(maximum_number_of_data_points_qm)));
			svref_new_value = adjust_managed_float_array(2,
				ISVREF(existing_ring_buffer_qm,
				(SI_Long)6L),maximum_number_of_data_points_qm);
			SVREF(existing_ring_buffer_qm,FIX((SI_Long)6L)) = 
				svref_new_value;
		    }
		    thing = ISVREF(existing_ring_buffer_qm,(SI_Long)7L);
		    if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,
			    (SI_Long)0L),Managed_array_unique_marker)) {
			rotate_managed_array(ISVREF(existing_ring_buffer_qm,
				(SI_Long)7L),oldest_active_element_index);
			if (IFIX(maximum_number_of_data_points_qm) < 
				ring_buffer_length)
			    rotate_managed_array(ISVREF(existing_ring_buffer_qm,
				    (SI_Long)7L),FIX(ring_buffer_length - 
				    IFIX(maximum_number_of_data_points_qm)));
			svref_new_value = adjust_managed_array(2,
				ISVREF(existing_ring_buffer_qm,
				(SI_Long)7L),maximum_number_of_data_points_qm);
			SVREF(existing_ring_buffer_qm,FIX((SI_Long)7L)) = 
				svref_new_value;
		    }
		    else {
			rotate_managed_float_array(ISVREF(existing_ring_buffer_qm,
				(SI_Long)7L),oldest_active_element_index);
			if (IFIX(maximum_number_of_data_points_qm) < 
				ring_buffer_length)
			    rotate_managed_float_array(ISVREF(existing_ring_buffer_qm,
				    (SI_Long)7L),FIX(ring_buffer_length - 
				    IFIX(maximum_number_of_data_points_qm)));
			svref_new_value = adjust_managed_float_array(2,
				ISVREF(existing_ring_buffer_qm,
				(SI_Long)7L),maximum_number_of_data_points_qm);
			SVREF(existing_ring_buffer_qm,FIX((SI_Long)7L)) = 
				svref_new_value;
		    }
		    ISVREF(existing_ring_buffer_qm,(SI_Long)2L) = 
			    FIX((SI_Long)0L);
		    svref_new_value_1 = MIN(ring_buffer_length,
			    IFIX(maximum_number_of_data_points_qm)) - 
			    (SI_Long)1L;
		    ISVREF(existing_ring_buffer_qm,(SI_Long)1L) = 
			    FIX(svref_new_value_1);
		    SVREF(existing_ring_buffer_qm,FIX((SI_Long)4L)) = 
			    maximum_number_of_data_points_qm;
		}
	    }
	}
	if ( !TRUEP(ISVREF(new_cascaded_ring_buffer,(SI_Long)4L))) {
	    ring_buffer_shell = make_history_ring_buffer_1();
	    size_to_allocate = FIXNUM_MIN(maximum_number_of_data_points_qm,
		    Largest_ring_buffer_vector_size);
	    svref_new_value = allocate_managed_float_array(1,size_to_allocate);
	    SVREF(ring_buffer_shell,FIX((SI_Long)6L)) = svref_new_value;
	    svref_new_value = allocate_managed_float_array(1,size_to_allocate);
	    SVREF(ring_buffer_shell,FIX((SI_Long)7L)) = svref_new_value;
	    SVREF(ring_buffer_shell,FIX((SI_Long)4L)) = size_to_allocate;
	    svref_new_value = history_cons_1(ring_buffer_shell,Nil);
	    SVREF(new_cascaded_ring_buffer,FIX((SI_Long)4L)) = svref_new_value;
	}
    }
    return VALUES_1(new_cascaded_ring_buffer);
}

/* STORE-HISTORY-ELEMENT-IN-CASCADED-RING-BUFFER */
Object store_history_element_in_cascaded_ring_buffer varargs_1(int, n)
{
    Object cascaded_ring_buffer, new_element_value, new_element_time;
    Object overwrite_value_if_duplicate_time_qm, storing_simulated_value_qm;
    Object temp, runtime_specification, ring_buffer;
    Object maximum_number_of_data_points_qm, maximum_age_of_data_points_qm;
    Object newest_active_element_index, time_of_previous_data_point_qm;
    Object ring_buffer_was_emptied_p, ring_buffer_shell, size_to_allocate;
    Object temp_1, new_ring_buffer, vector_1, managed_number_or_value, index_1;
    Object oldest_active_element_index_for_ring_buffer;
    Object store_managed_number_or_value_arg, temp_4, new_managed_array;
    Object element_index, amf_available_array_cons_qm, amf_array, temp_5;
    Object amf_result, new_float, gensymed_symbol, ab_loop_list_, index_2;
    SI_Long temp_3;
    char temp_2;
    double aref_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(148,65);
    INIT_ARGS_nonrelocating();
    cascaded_ring_buffer = REQUIRED_ARG_nonrelocating();
    new_element_value = REQUIRED_ARG_nonrelocating();
    new_element_time = REQUIRED_ARG_nonrelocating();
    overwrite_value_if_duplicate_time_qm = OPTIONAL_ARG_P_nonrelocating() ?
	     OPTIONAL_ARG_nonrelocating() : T;
    storing_simulated_value_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = ISVREF(cascaded_ring_buffer,(SI_Long)3L);
    runtime_specification = CAR(temp);
    temp = ISVREF(cascaded_ring_buffer,(SI_Long)4L);
    ring_buffer = CAR(temp);
    maximum_number_of_data_points_qm = FIRST(runtime_specification);
    maximum_age_of_data_points_qm = SECOND(runtime_specification);
    newest_active_element_index = Nil;
    time_of_previous_data_point_qm = Nil;
    ring_buffer_was_emptied_p = Nil;
    if (ISVREF(cascaded_ring_buffer,(SI_Long)9L))
	maintain_high_water_marks(cascaded_ring_buffer,new_element_value);
    if ( !TRUEP(ring_buffer)) {
	if (maximum_number_of_data_points_qm) {
	    ring_buffer_shell = make_history_ring_buffer_1();
	    size_to_allocate = FIXNUM_MIN(maximum_number_of_data_points_qm,
		    Largest_ring_buffer_vector_size);
	    temp_1 = allocate_managed_float_array(1,size_to_allocate);
	    SVREF(ring_buffer_shell,FIX((SI_Long)6L)) = temp_1;
	    temp_1 = allocate_managed_float_array(1,size_to_allocate);
	    SVREF(ring_buffer_shell,FIX((SI_Long)7L)) = temp_1;
	    SVREF(ring_buffer_shell,FIX((SI_Long)4L)) = size_to_allocate;
	    new_ring_buffer = ring_buffer_shell;
	}
	else {
	    ring_buffer_shell = make_history_ring_buffer_1();
	    temp_1 = allocate_managed_float_array(1,
		    Smallest_ring_buffer_vector_size);
	    SVREF(ring_buffer_shell,FIX((SI_Long)6L)) = temp_1;
	    temp_1 = allocate_managed_float_array(1,
		    Smallest_ring_buffer_vector_size);
	    SVREF(ring_buffer_shell,FIX((SI_Long)7L)) = temp_1;
	    temp_1 = Smallest_ring_buffer_vector_size;
	    SVREF(ring_buffer_shell,FIX((SI_Long)4L)) = temp_1;
	    new_ring_buffer = ring_buffer_shell;
	}
	temp_1 = nconc2(ISVREF(cascaded_ring_buffer,(SI_Long)4L),
		history_cons_1(new_ring_buffer,Nil));
	SVREF(cascaded_ring_buffer,FIX((SI_Long)4L)) = temp_1;
	ring_buffer = new_ring_buffer;
    }
    if ( !TRUEP(ISVREF(ring_buffer,(SI_Long)3L))) {
	if (maximum_age_of_data_points_qm) {
	    temp = ring_buffer;
	    remove_history_values_past_maximum_age(cascaded_ring_buffer,
		    temp,maximum_age_of_data_points_qm,
		    storing_simulated_value_qm ? 
		    current_simulation_time_as_managed_float() : 
		    Current_g2_time);
	}
	if (ISVREF(ring_buffer,(SI_Long)3L))
	    ring_buffer_was_emptied_p = T;
	newest_active_element_index = ISVREF(ring_buffer,(SI_Long)1L);
	vector_1 = ISVREF(ring_buffer,(SI_Long)7L);
	if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
		Managed_array_unique_marker)) {
	    managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(vector_1,
		    IFIX(FIXNUM_ADD(newest_active_element_index,
		    Managed_array_index_offset))) : ISVREF(ISVREF(vector_1,
		    (IFIX(newest_active_element_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),
		    IFIX(newest_active_element_index) & (SI_Long)1023L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		time_of_previous_data_point_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		time_of_previous_data_point_qm = 
			aref1(managed_number_or_value,FIX((SI_Long)0L));
	    else if (text_string_p(managed_number_or_value))
		time_of_previous_data_point_qm = 
			copy_text_string(managed_number_or_value);
	    else
		time_of_previous_data_point_qm = managed_number_or_value;
	}
	else
	    time_of_previous_data_point_qm = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
		    (IFIX(newest_active_element_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),
		    IFIX(newest_active_element_index) & (SI_Long)1023L));
	if ( !(overwrite_value_if_duplicate_time_qm && 
		time_of_previous_data_point_qm && NUM_EQ(new_element_time,
		time_of_previous_data_point_qm))) {
	    if (maximum_number_of_data_points_qm) {
		index_1 = ISVREF(ring_buffer,(SI_Long)1L);
		oldest_active_element_index_for_ring_buffer = 
			ISVREF(ring_buffer,(SI_Long)2L);
		temp = FIXNUM_GE(index_1,
			oldest_active_element_index_for_ring_buffer) ? 
			FIXNUM_ADD1(FIXNUM_MINUS(index_1,
			oldest_active_element_index_for_ring_buffer)) : 
			FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(index_1,
			ISVREF(ring_buffer,(SI_Long)4L)),
			oldest_active_element_index_for_ring_buffer));
		temp_2 = NUM_EQ(temp,maximum_number_of_data_points_qm);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		temp_1 = FIXNUM_ADD1(ISVREF(cascaded_ring_buffer,(SI_Long)6L));
		SVREF(cascaded_ring_buffer,FIX((SI_Long)6L)) = temp_1;
		if (FIXNUM_EQ(ISVREF(ring_buffer,(SI_Long)2L),
			newest_active_element_index)) {
		    SVREF(ring_buffer,FIX((SI_Long)3L)) = T;
		    ring_buffer_was_emptied_p = T;
		    index_1 = ISVREF(ring_buffer,(SI_Long)2L);
		    temp_3 = FIXNUM_EQ(index_1,
			    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ?
			     (SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
		    ISVREF(ring_buffer,(SI_Long)2L) = FIX(temp_3);
		    index_1 = ISVREF(ring_buffer,(SI_Long)1L);
		    temp_3 = FIXNUM_EQ(index_1,
			    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ?
			     (SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
		    ISVREF(ring_buffer,(SI_Long)1L) = FIX(temp_3);
		}
		else {
		    index_1 = ISVREF(ring_buffer,(SI_Long)2L);
		    temp_3 = FIXNUM_EQ(index_1,
			    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ?
			     (SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
		    ISVREF(ring_buffer,(SI_Long)2L) = FIX(temp_3);
		}
	    }
	}
    }
    if (ISVREF(ring_buffer,(SI_Long)3L))
	temp = T;
    else if ( !TRUEP(time_of_previous_data_point_qm))
	temp = T;
    else if (NUM_GT(new_element_time,time_of_previous_data_point_qm))
	temp = T;
    else if (NUM_EQ(new_element_time,time_of_previous_data_point_qm)) {
	if (overwrite_value_if_duplicate_time_qm) {
	    temp_1 = FIXNUM_ADD1(ISVREF(ring_buffer,(SI_Long)5L));
	    SVREF(ring_buffer,FIX((SI_Long)5L)) = temp_1;
	    vector_1 = ISVREF(ring_buffer,(SI_Long)6L);
	    if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
		    (SI_Long)0L),Managed_array_unique_marker)) {
		store_managed_number_or_value_arg = new_element_value;
		temp_4 = 
			store_managed_number_or_value_function(FIXNUM_LE(ISVREF(vector_1,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(vector_1,
			IFIX(FIXNUM_ADD(newest_active_element_index,
			Managed_array_index_offset))) : 
			ISVREF(ISVREF(vector_1,
			(IFIX(newest_active_element_index) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),
			IFIX(newest_active_element_index) & 
			(SI_Long)1023L),store_managed_number_or_value_arg);
		if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    temp_1 = FIXNUM_ADD(newest_active_element_index,
			    Managed_array_index_offset);
		    SVREF(vector_1,temp_1) = temp_4;
		}
		else {
		    temp_1 = ISVREF(vector_1,
			    (IFIX(newest_active_element_index) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(newest_active_element_index) & 
			    (SI_Long)1023L;
		    ISVREF(temp_1,temp_3) = temp_4;
		}
	    }
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(new_element_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_element_value)) == 
		    (SI_Long)1L) {
		temp_1 = ISVREF(vector_1,
			(IFIX(newest_active_element_index) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(newest_active_element_index) & (SI_Long)1023L;
		aref_new_value = DFLOAT_ISAREF_1(new_element_value,
			(SI_Long)0L);
		DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
	    }
	    else if (FLOATP(new_element_value)) {
		temp_1 = ISVREF(vector_1,
			(IFIX(newest_active_element_index) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(newest_active_element_index) & (SI_Long)1023L;
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(new_element_value);
		DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
	    }
	    else {
		new_managed_array = allocate_managed_array(1,
			ISVREF(vector_1,(SI_Long)1L));
		if ( !TRUEP(ISVREF(ring_buffer,(SI_Long)3L))) {
		    element_index = ISVREF(ring_buffer,(SI_Long)2L);
		  next_loop:
		    if (FIXNUM_LE(ISVREF(new_managed_array,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			temp_1 = FIXNUM_ADD(element_index,
				Managed_array_index_offset);
			amf_available_array_cons_qm = 
				ISVREF(Vector_of_simple_float_array_pools,
				(SI_Long)1L);
			if (amf_available_array_cons_qm) {
			    amf_array = M_CAR(amf_available_array_cons_qm);
			    temp_4 = Vector_of_simple_float_array_pools;
			    temp_5 = M_CDR(amf_available_array_cons_qm);
			    SVREF(temp_4,FIX((SI_Long)1L)) = temp_5;
			    inline_note_reclaim_cons(amf_available_array_cons_qm,
				    Qfloat_array);
			    if (ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp_4 = 
					ISVREF(Available_float_array_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp_4) = amf_available_array_cons_qm;
				temp_4 = 
					Available_float_array_conses_tail_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
					amf_available_array_cons_qm;
			    }
			    else {
				temp_4 = Available_float_array_conses_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
					amf_available_array_cons_qm;
				temp_4 = 
					Available_float_array_conses_tail_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
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
			aref_new_value = DFLOAT_ISAREF_1(ISVREF(vector_1,
				(IFIX(element_index) >>  -  - 
				(SI_Long)10L) + (SI_Long)2L),
				IFIX(element_index) & (SI_Long)1023L);
			DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
			SVREF(new_managed_array,temp_1) = new_float;
		    }
		    else {
			temp_1 = ISVREF(new_managed_array,
				(IFIX(element_index) >>  -  - 
				(SI_Long)10L) + (SI_Long)2L);
			temp_3 = IFIX(element_index) & (SI_Long)1023L;
			amf_available_array_cons_qm = 
				ISVREF(Vector_of_simple_float_array_pools,
				(SI_Long)1L);
			if (amf_available_array_cons_qm) {
			    amf_array = M_CAR(amf_available_array_cons_qm);
			    temp_4 = Vector_of_simple_float_array_pools;
			    temp_5 = M_CDR(amf_available_array_cons_qm);
			    SVREF(temp_4,FIX((SI_Long)1L)) = temp_5;
			    inline_note_reclaim_cons(amf_available_array_cons_qm,
				    Qfloat_array);
			    if (ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp_4 = 
					ISVREF(Available_float_array_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp_4) = amf_available_array_cons_qm;
				temp_4 = 
					Available_float_array_conses_tail_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
					amf_available_array_cons_qm;
			    }
			    else {
				temp_4 = Available_float_array_conses_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
					amf_available_array_cons_qm;
				temp_4 = 
					Available_float_array_conses_tail_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
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
			aref_new_value = DFLOAT_ISAREF_1(ISVREF(vector_1,
				(IFIX(element_index) >>  -  - 
				(SI_Long)10L) + (SI_Long)2L),
				IFIX(element_index) & (SI_Long)1023L);
			DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
			ISVREF(temp_1,temp_3) = new_float;
		    }
		    if (FIXNUM_EQ(element_index,ISVREF(ring_buffer,
			    (SI_Long)1L)))
			goto end_loop;
		    element_index = FIXNUM_EQ(element_index,
			    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ?
			     FIX((SI_Long)0L) : FIXNUM_ADD1(element_index);
		    goto next_loop;
		  end_loop:;
		}
		reclaim_managed_float_array(vector_1);
		SVREF(ring_buffer,FIX((SI_Long)6L)) = new_managed_array;
		temp_1 = ISVREF(ring_buffer,(SI_Long)6L);
		store_managed_number_or_value_arg = new_element_value;
		temp_5 = 
			store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp_1,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(temp_1,
			IFIX(FIXNUM_ADD(newest_active_element_index,
			Managed_array_index_offset))) : 
			ISVREF(ISVREF(temp_1,
			(IFIX(newest_active_element_index) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),
			IFIX(newest_active_element_index) & 
			(SI_Long)1023L),store_managed_number_or_value_arg);
		if (FIXNUM_LE(ISVREF(temp_1,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    temp_4 = FIXNUM_ADD(newest_active_element_index,
			    Managed_array_index_offset);
		    SVREF(temp_1,temp_4) = temp_5;
		}
		else {
		    temp_1 = ISVREF(temp_1,
			    (IFIX(newest_active_element_index) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(newest_active_element_index) & 
			    (SI_Long)1023L;
		    ISVREF(temp_1,temp_3) = temp_5;
		}
	    }
	    vector_1 = ISVREF(ring_buffer,(SI_Long)7L);
	    if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
		    (SI_Long)0L),Managed_array_unique_marker)) {
		store_managed_number_or_value_arg = new_element_time;
		temp_4 = 
			store_managed_number_or_value_function(FIXNUM_LE(ISVREF(vector_1,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(vector_1,
			IFIX(FIXNUM_ADD(newest_active_element_index,
			Managed_array_index_offset))) : 
			ISVREF(ISVREF(vector_1,
			(IFIX(newest_active_element_index) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),
			IFIX(newest_active_element_index) & 
			(SI_Long)1023L),store_managed_number_or_value_arg);
		if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    temp_1 = FIXNUM_ADD(newest_active_element_index,
			    Managed_array_index_offset);
		    SVREF(vector_1,temp_1) = temp_4;
		}
		else {
		    temp_1 = ISVREF(vector_1,
			    (IFIX(newest_active_element_index) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(newest_active_element_index) & 
			    (SI_Long)1023L;
		    ISVREF(temp_1,temp_3) = temp_4;
		}
	    }
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(new_element_time) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_element_time)) == 
		    (SI_Long)1L) {
		temp_1 = ISVREF(vector_1,
			(IFIX(newest_active_element_index) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(newest_active_element_index) & (SI_Long)1023L;
		aref_new_value = DFLOAT_ISAREF_1(new_element_time,(SI_Long)0L);
		DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
	    }
	    else if (FLOATP(new_element_time)) {
		temp_1 = ISVREF(vector_1,
			(IFIX(newest_active_element_index) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(newest_active_element_index) & (SI_Long)1023L;
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(new_element_time);
		DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
	    }
	    else {
		new_managed_array = allocate_managed_array(1,
			ISVREF(vector_1,(SI_Long)1L));
		if ( !TRUEP(ISVREF(ring_buffer,(SI_Long)3L))) {
		    element_index = ISVREF(ring_buffer,(SI_Long)2L);
		  next_loop_1:
		    if (FIXNUM_LE(ISVREF(new_managed_array,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			temp_1 = FIXNUM_ADD(element_index,
				Managed_array_index_offset);
			amf_available_array_cons_qm = 
				ISVREF(Vector_of_simple_float_array_pools,
				(SI_Long)1L);
			if (amf_available_array_cons_qm) {
			    amf_array = M_CAR(amf_available_array_cons_qm);
			    temp_4 = Vector_of_simple_float_array_pools;
			    temp_5 = M_CDR(amf_available_array_cons_qm);
			    SVREF(temp_4,FIX((SI_Long)1L)) = temp_5;
			    inline_note_reclaim_cons(amf_available_array_cons_qm,
				    Qfloat_array);
			    if (ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp_4 = 
					ISVREF(Available_float_array_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp_4) = amf_available_array_cons_qm;
				temp_4 = 
					Available_float_array_conses_tail_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
					amf_available_array_cons_qm;
			    }
			    else {
				temp_4 = Available_float_array_conses_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
					amf_available_array_cons_qm;
				temp_4 = 
					Available_float_array_conses_tail_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
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
			aref_new_value = DFLOAT_ISAREF_1(ISVREF(vector_1,
				(IFIX(element_index) >>  -  - 
				(SI_Long)10L) + (SI_Long)2L),
				IFIX(element_index) & (SI_Long)1023L);
			DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
			SVREF(new_managed_array,temp_1) = new_float;
		    }
		    else {
			temp_1 = ISVREF(new_managed_array,
				(IFIX(element_index) >>  -  - 
				(SI_Long)10L) + (SI_Long)2L);
			temp_3 = IFIX(element_index) & (SI_Long)1023L;
			amf_available_array_cons_qm = 
				ISVREF(Vector_of_simple_float_array_pools,
				(SI_Long)1L);
			if (amf_available_array_cons_qm) {
			    amf_array = M_CAR(amf_available_array_cons_qm);
			    temp_4 = Vector_of_simple_float_array_pools;
			    temp_5 = M_CDR(amf_available_array_cons_qm);
			    SVREF(temp_4,FIX((SI_Long)1L)) = temp_5;
			    inline_note_reclaim_cons(amf_available_array_cons_qm,
				    Qfloat_array);
			    if (ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp_4 = 
					ISVREF(Available_float_array_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp_4) = amf_available_array_cons_qm;
				temp_4 = 
					Available_float_array_conses_tail_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
					amf_available_array_cons_qm;
			    }
			    else {
				temp_4 = Available_float_array_conses_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
					amf_available_array_cons_qm;
				temp_4 = 
					Available_float_array_conses_tail_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
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
			aref_new_value = DFLOAT_ISAREF_1(ISVREF(vector_1,
				(IFIX(element_index) >>  -  - 
				(SI_Long)10L) + (SI_Long)2L),
				IFIX(element_index) & (SI_Long)1023L);
			DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
			ISVREF(temp_1,temp_3) = new_float;
		    }
		    if (FIXNUM_EQ(element_index,ISVREF(ring_buffer,
			    (SI_Long)1L)))
			goto end_loop_1;
		    element_index = FIXNUM_EQ(element_index,
			    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ?
			     FIX((SI_Long)0L) : FIXNUM_ADD1(element_index);
		    goto next_loop_1;
		  end_loop_1:;
		}
		reclaim_managed_float_array(vector_1);
		SVREF(ring_buffer,FIX((SI_Long)7L)) = new_managed_array;
		temp_1 = ISVREF(ring_buffer,(SI_Long)7L);
		store_managed_number_or_value_arg = new_element_time;
		temp_5 = 
			store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp_1,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(temp_1,
			IFIX(FIXNUM_ADD(newest_active_element_index,
			Managed_array_index_offset))) : 
			ISVREF(ISVREF(temp_1,
			(IFIX(newest_active_element_index) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),
			IFIX(newest_active_element_index) & 
			(SI_Long)1023L),store_managed_number_or_value_arg);
		if (FIXNUM_LE(ISVREF(temp_1,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    temp_4 = FIXNUM_ADD(newest_active_element_index,
			    Managed_array_index_offset);
		    SVREF(temp_1,temp_4) = temp_5;
		}
		else {
		    temp_1 = ISVREF(temp_1,
			    (IFIX(newest_active_element_index) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(newest_active_element_index) & 
			    (SI_Long)1023L;
		    ISVREF(temp_1,temp_3) = temp_5;
		}
	    }
	    gensymed_symbol = Nil;
	    ab_loop_list_ = ISVREF(cascaded_ring_buffer,(SI_Long)11L);
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    gensymed_symbol = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    notify_client_of_change_to_cascaded_ring_buffer(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	    temp = Nil;
	}
	else
	    temp = T;
    }
    else {
	store_old_data_in_history_ring_buffer(4,ring_buffer,
		new_element_value,new_element_time,
		overwrite_value_if_duplicate_time_qm);
	SVREF(cascaded_ring_buffer,FIX((SI_Long)5L)) = T;
	gensymed_symbol = Nil;
	ab_loop_list_ = ISVREF(cascaded_ring_buffer,(SI_Long)11L);
      next_loop_3:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_3;
	gensymed_symbol = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	notify_client_of_change_to_cascaded_ring_buffer(gensymed_symbol);
	goto next_loop_3;
      end_loop_3:;
	temp = Nil;
    }
    if (temp) {
	if (ISVREF(ring_buffer,(SI_Long)3L)) {
	    index_2 = ISVREF(ring_buffer,(SI_Long)1L);
	    temp_1 = FIXNUM_ADD1(ISVREF(ring_buffer,(SI_Long)5L));
	    SVREF(ring_buffer,FIX((SI_Long)5L)) = temp_1;
	    vector_1 = ISVREF(ring_buffer,(SI_Long)6L);
	    if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
		    (SI_Long)0L),Managed_array_unique_marker)) {
		store_managed_number_or_value_arg = new_element_value;
		temp_4 = 
			store_managed_number_or_value_function(FIXNUM_LE(ISVREF(vector_1,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(vector_1,IFIX(FIXNUM_ADD(index_2,
			Managed_array_index_offset))) : 
			ISVREF(ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),IFIX(index_2) & 
			(SI_Long)1023L),store_managed_number_or_value_arg);
		if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    temp_1 = FIXNUM_ADD(index_2,Managed_array_index_offset);
		    SVREF(vector_1,temp_1) = temp_4;
		}
		else {
		    temp_1 = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(index_2) & (SI_Long)1023L;
		    ISVREF(temp_1,temp_3) = temp_4;
		}
	    }
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(new_element_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_element_value)) == 
		    (SI_Long)1L) {
		temp_1 = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(index_2) & (SI_Long)1023L;
		aref_new_value = DFLOAT_ISAREF_1(new_element_value,
			(SI_Long)0L);
		DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
	    }
	    else if (FLOATP(new_element_value)) {
		temp_1 = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(index_2) & (SI_Long)1023L;
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(new_element_value);
		DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
	    }
	    else {
		new_managed_array = allocate_managed_array(1,
			ISVREF(vector_1,(SI_Long)1L));
		if ( !TRUEP(ISVREF(ring_buffer,(SI_Long)3L))) {
		    element_index = ISVREF(ring_buffer,(SI_Long)2L);
		  next_loop_4:
		    if (FIXNUM_LE(ISVREF(new_managed_array,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			temp_1 = FIXNUM_ADD(element_index,
				Managed_array_index_offset);
			amf_available_array_cons_qm = 
				ISVREF(Vector_of_simple_float_array_pools,
				(SI_Long)1L);
			if (amf_available_array_cons_qm) {
			    amf_array = M_CAR(amf_available_array_cons_qm);
			    temp_4 = Vector_of_simple_float_array_pools;
			    temp_5 = M_CDR(amf_available_array_cons_qm);
			    SVREF(temp_4,FIX((SI_Long)1L)) = temp_5;
			    inline_note_reclaim_cons(amf_available_array_cons_qm,
				    Qfloat_array);
			    if (ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp_4 = 
					ISVREF(Available_float_array_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp_4) = amf_available_array_cons_qm;
				temp_4 = 
					Available_float_array_conses_tail_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
					amf_available_array_cons_qm;
			    }
			    else {
				temp_4 = Available_float_array_conses_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
					amf_available_array_cons_qm;
				temp_4 = 
					Available_float_array_conses_tail_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
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
			aref_new_value = DFLOAT_ISAREF_1(ISVREF(vector_1,
				(IFIX(element_index) >>  -  - 
				(SI_Long)10L) + (SI_Long)2L),
				IFIX(element_index) & (SI_Long)1023L);
			DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
			SVREF(new_managed_array,temp_1) = new_float;
		    }
		    else {
			temp_1 = ISVREF(new_managed_array,
				(IFIX(element_index) >>  -  - 
				(SI_Long)10L) + (SI_Long)2L);
			temp_3 = IFIX(element_index) & (SI_Long)1023L;
			amf_available_array_cons_qm = 
				ISVREF(Vector_of_simple_float_array_pools,
				(SI_Long)1L);
			if (amf_available_array_cons_qm) {
			    amf_array = M_CAR(amf_available_array_cons_qm);
			    temp_4 = Vector_of_simple_float_array_pools;
			    temp_5 = M_CDR(amf_available_array_cons_qm);
			    SVREF(temp_4,FIX((SI_Long)1L)) = temp_5;
			    inline_note_reclaim_cons(amf_available_array_cons_qm,
				    Qfloat_array);
			    if (ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp_4 = 
					ISVREF(Available_float_array_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp_4) = amf_available_array_cons_qm;
				temp_4 = 
					Available_float_array_conses_tail_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
					amf_available_array_cons_qm;
			    }
			    else {
				temp_4 = Available_float_array_conses_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
					amf_available_array_cons_qm;
				temp_4 = 
					Available_float_array_conses_tail_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
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
			aref_new_value = DFLOAT_ISAREF_1(ISVREF(vector_1,
				(IFIX(element_index) >>  -  - 
				(SI_Long)10L) + (SI_Long)2L),
				IFIX(element_index) & (SI_Long)1023L);
			DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
			ISVREF(temp_1,temp_3) = new_float;
		    }
		    if (FIXNUM_EQ(element_index,ISVREF(ring_buffer,
			    (SI_Long)1L)))
			goto end_loop_4;
		    element_index = FIXNUM_EQ(element_index,
			    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ?
			     FIX((SI_Long)0L) : FIXNUM_ADD1(element_index);
		    goto next_loop_4;
		  end_loop_4:;
		}
		reclaim_managed_float_array(vector_1);
		SVREF(ring_buffer,FIX((SI_Long)6L)) = new_managed_array;
		temp_1 = ISVREF(ring_buffer,(SI_Long)6L);
		store_managed_number_or_value_arg = new_element_value;
		temp_5 = 
			store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp_1,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(temp_1,IFIX(FIXNUM_ADD(index_2,
			Managed_array_index_offset))) : 
			ISVREF(ISVREF(temp_1,(IFIX(index_2) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),IFIX(index_2) & 
			(SI_Long)1023L),store_managed_number_or_value_arg);
		if (FIXNUM_LE(ISVREF(temp_1,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    temp_4 = FIXNUM_ADD(index_2,Managed_array_index_offset);
		    SVREF(temp_1,temp_4) = temp_5;
		}
		else {
		    temp_1 = ISVREF(temp_1,(IFIX(index_2) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(index_2) & (SI_Long)1023L;
		    ISVREF(temp_1,temp_3) = temp_5;
		}
	    }
	    vector_1 = ISVREF(ring_buffer,(SI_Long)7L);
	    if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
		    (SI_Long)0L),Managed_array_unique_marker)) {
		store_managed_number_or_value_arg = new_element_time;
		temp_4 = 
			store_managed_number_or_value_function(FIXNUM_LE(ISVREF(vector_1,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(vector_1,IFIX(FIXNUM_ADD(index_2,
			Managed_array_index_offset))) : 
			ISVREF(ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),IFIX(index_2) & 
			(SI_Long)1023L),store_managed_number_or_value_arg);
		if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    temp_1 = FIXNUM_ADD(index_2,Managed_array_index_offset);
		    SVREF(vector_1,temp_1) = temp_4;
		}
		else {
		    temp_1 = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(index_2) & (SI_Long)1023L;
		    ISVREF(temp_1,temp_3) = temp_4;
		}
	    }
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(new_element_time) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_element_time)) == 
		    (SI_Long)1L) {
		temp_1 = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(index_2) & (SI_Long)1023L;
		aref_new_value = DFLOAT_ISAREF_1(new_element_time,(SI_Long)0L);
		DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
	    }
	    else if (FLOATP(new_element_time)) {
		temp_1 = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(index_2) & (SI_Long)1023L;
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(new_element_time);
		DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
	    }
	    else {
		new_managed_array = allocate_managed_array(1,
			ISVREF(vector_1,(SI_Long)1L));
		if ( !TRUEP(ISVREF(ring_buffer,(SI_Long)3L))) {
		    element_index = ISVREF(ring_buffer,(SI_Long)2L);
		  next_loop_5:
		    if (FIXNUM_LE(ISVREF(new_managed_array,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			temp_1 = FIXNUM_ADD(element_index,
				Managed_array_index_offset);
			amf_available_array_cons_qm = 
				ISVREF(Vector_of_simple_float_array_pools,
				(SI_Long)1L);
			if (amf_available_array_cons_qm) {
			    amf_array = M_CAR(amf_available_array_cons_qm);
			    temp_4 = Vector_of_simple_float_array_pools;
			    temp_5 = M_CDR(amf_available_array_cons_qm);
			    SVREF(temp_4,FIX((SI_Long)1L)) = temp_5;
			    inline_note_reclaim_cons(amf_available_array_cons_qm,
				    Qfloat_array);
			    if (ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp_4 = 
					ISVREF(Available_float_array_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp_4) = amf_available_array_cons_qm;
				temp_4 = 
					Available_float_array_conses_tail_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
					amf_available_array_cons_qm;
			    }
			    else {
				temp_4 = Available_float_array_conses_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
					amf_available_array_cons_qm;
				temp_4 = 
					Available_float_array_conses_tail_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
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
			aref_new_value = DFLOAT_ISAREF_1(ISVREF(vector_1,
				(IFIX(element_index) >>  -  - 
				(SI_Long)10L) + (SI_Long)2L),
				IFIX(element_index) & (SI_Long)1023L);
			DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
			SVREF(new_managed_array,temp_1) = new_float;
		    }
		    else {
			temp_1 = ISVREF(new_managed_array,
				(IFIX(element_index) >>  -  - 
				(SI_Long)10L) + (SI_Long)2L);
			temp_3 = IFIX(element_index) & (SI_Long)1023L;
			amf_available_array_cons_qm = 
				ISVREF(Vector_of_simple_float_array_pools,
				(SI_Long)1L);
			if (amf_available_array_cons_qm) {
			    amf_array = M_CAR(amf_available_array_cons_qm);
			    temp_4 = Vector_of_simple_float_array_pools;
			    temp_5 = M_CDR(amf_available_array_cons_qm);
			    SVREF(temp_4,FIX((SI_Long)1L)) = temp_5;
			    inline_note_reclaim_cons(amf_available_array_cons_qm,
				    Qfloat_array);
			    if (ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp_4 = 
					ISVREF(Available_float_array_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp_4) = amf_available_array_cons_qm;
				temp_4 = 
					Available_float_array_conses_tail_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
					amf_available_array_cons_qm;
			    }
			    else {
				temp_4 = Available_float_array_conses_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
					amf_available_array_cons_qm;
				temp_4 = 
					Available_float_array_conses_tail_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
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
			aref_new_value = DFLOAT_ISAREF_1(ISVREF(vector_1,
				(IFIX(element_index) >>  -  - 
				(SI_Long)10L) + (SI_Long)2L),
				IFIX(element_index) & (SI_Long)1023L);
			DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
			ISVREF(temp_1,temp_3) = new_float;
		    }
		    if (FIXNUM_EQ(element_index,ISVREF(ring_buffer,
			    (SI_Long)1L)))
			goto end_loop_5;
		    element_index = FIXNUM_EQ(element_index,
			    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ?
			     FIX((SI_Long)0L) : FIXNUM_ADD1(element_index);
		    goto next_loop_5;
		  end_loop_5:;
		}
		reclaim_managed_float_array(vector_1);
		SVREF(ring_buffer,FIX((SI_Long)7L)) = new_managed_array;
		temp_1 = ISVREF(ring_buffer,(SI_Long)7L);
		store_managed_number_or_value_arg = new_element_time;
		temp_5 = 
			store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp_1,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(temp_1,IFIX(FIXNUM_ADD(index_2,
			Managed_array_index_offset))) : 
			ISVREF(ISVREF(temp_1,(IFIX(index_2) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),IFIX(index_2) & 
			(SI_Long)1023L),store_managed_number_or_value_arg);
		if (FIXNUM_LE(ISVREF(temp_1,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    temp_4 = FIXNUM_ADD(index_2,Managed_array_index_offset);
		    SVREF(temp_1,temp_4) = temp_5;
		}
		else {
		    temp_1 = ISVREF(temp_1,(IFIX(index_2) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(index_2) & (SI_Long)1023L;
		    ISVREF(temp_1,temp_3) = temp_5;
		}
	    }
	    SVREF(ring_buffer,FIX((SI_Long)3L)) = Nil;
	}
	else {
	    index_1 = ISVREF(ring_buffer,(SI_Long)1L);
	    oldest_active_element_index_for_ring_buffer = 
		    ISVREF(ring_buffer,(SI_Long)2L);
	    if (FIXNUM_EQ(FIXNUM_GE(index_1,
		    oldest_active_element_index_for_ring_buffer) ? 
		    FIXNUM_ADD1(FIXNUM_MINUS(index_1,
		    oldest_active_element_index_for_ring_buffer)) : 
		    FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(index_1,
		    ISVREF(ring_buffer,(SI_Long)4L)),
		    oldest_active_element_index_for_ring_buffer)),
		    ISVREF(ring_buffer,(SI_Long)4L)))
		expand_history_ring_buffer(ring_buffer);
	    index_1 = ISVREF(ring_buffer,(SI_Long)1L);
	    temp_3 = FIXNUM_EQ(index_1,FIXNUM_SUB1(ISVREF(ring_buffer,
		    (SI_Long)4L))) ? (SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
	    ISVREF(ring_buffer,(SI_Long)1L) = FIX(temp_3);
	    index_2 = ISVREF(ring_buffer,(SI_Long)1L);
	    temp_1 = FIXNUM_ADD1(ISVREF(ring_buffer,(SI_Long)5L));
	    SVREF(ring_buffer,FIX((SI_Long)5L)) = temp_1;
	    vector_1 = ISVREF(ring_buffer,(SI_Long)6L);
	    if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
		    (SI_Long)0L),Managed_array_unique_marker)) {
		store_managed_number_or_value_arg = new_element_value;
		temp_4 = 
			store_managed_number_or_value_function(FIXNUM_LE(ISVREF(vector_1,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(vector_1,IFIX(FIXNUM_ADD(index_2,
			Managed_array_index_offset))) : 
			ISVREF(ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),IFIX(index_2) & 
			(SI_Long)1023L),store_managed_number_or_value_arg);
		if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    temp_1 = FIXNUM_ADD(index_2,Managed_array_index_offset);
		    SVREF(vector_1,temp_1) = temp_4;
		}
		else {
		    temp_1 = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(index_2) & (SI_Long)1023L;
		    ISVREF(temp_1,temp_3) = temp_4;
		}
	    }
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(new_element_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_element_value)) == 
		    (SI_Long)1L) {
		temp_1 = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(index_2) & (SI_Long)1023L;
		aref_new_value = DFLOAT_ISAREF_1(new_element_value,
			(SI_Long)0L);
		DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
	    }
	    else if (FLOATP(new_element_value)) {
		temp_1 = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(index_2) & (SI_Long)1023L;
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(new_element_value);
		DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
	    }
	    else {
		new_managed_array = allocate_managed_array(1,
			ISVREF(vector_1,(SI_Long)1L));
		if ( !TRUEP(ISVREF(ring_buffer,(SI_Long)3L))) {
		    element_index = ISVREF(ring_buffer,(SI_Long)2L);
		  next_loop_6:
		    if (FIXNUM_LE(ISVREF(new_managed_array,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			temp_1 = FIXNUM_ADD(element_index,
				Managed_array_index_offset);
			amf_available_array_cons_qm = 
				ISVREF(Vector_of_simple_float_array_pools,
				(SI_Long)1L);
			if (amf_available_array_cons_qm) {
			    amf_array = M_CAR(amf_available_array_cons_qm);
			    temp_4 = Vector_of_simple_float_array_pools;
			    temp_5 = M_CDR(amf_available_array_cons_qm);
			    SVREF(temp_4,FIX((SI_Long)1L)) = temp_5;
			    inline_note_reclaim_cons(amf_available_array_cons_qm,
				    Qfloat_array);
			    if (ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp_4 = 
					ISVREF(Available_float_array_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp_4) = amf_available_array_cons_qm;
				temp_4 = 
					Available_float_array_conses_tail_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
					amf_available_array_cons_qm;
			    }
			    else {
				temp_4 = Available_float_array_conses_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
					amf_available_array_cons_qm;
				temp_4 = 
					Available_float_array_conses_tail_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
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
			aref_new_value = DFLOAT_ISAREF_1(ISVREF(vector_1,
				(IFIX(element_index) >>  -  - 
				(SI_Long)10L) + (SI_Long)2L),
				IFIX(element_index) & (SI_Long)1023L);
			DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
			SVREF(new_managed_array,temp_1) = new_float;
		    }
		    else {
			temp_1 = ISVREF(new_managed_array,
				(IFIX(element_index) >>  -  - 
				(SI_Long)10L) + (SI_Long)2L);
			temp_3 = IFIX(element_index) & (SI_Long)1023L;
			amf_available_array_cons_qm = 
				ISVREF(Vector_of_simple_float_array_pools,
				(SI_Long)1L);
			if (amf_available_array_cons_qm) {
			    amf_array = M_CAR(amf_available_array_cons_qm);
			    temp_4 = Vector_of_simple_float_array_pools;
			    temp_5 = M_CDR(amf_available_array_cons_qm);
			    SVREF(temp_4,FIX((SI_Long)1L)) = temp_5;
			    inline_note_reclaim_cons(amf_available_array_cons_qm,
				    Qfloat_array);
			    if (ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp_4 = 
					ISVREF(Available_float_array_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp_4) = amf_available_array_cons_qm;
				temp_4 = 
					Available_float_array_conses_tail_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
					amf_available_array_cons_qm;
			    }
			    else {
				temp_4 = Available_float_array_conses_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
					amf_available_array_cons_qm;
				temp_4 = 
					Available_float_array_conses_tail_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
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
			aref_new_value = DFLOAT_ISAREF_1(ISVREF(vector_1,
				(IFIX(element_index) >>  -  - 
				(SI_Long)10L) + (SI_Long)2L),
				IFIX(element_index) & (SI_Long)1023L);
			DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
			ISVREF(temp_1,temp_3) = new_float;
		    }
		    if (FIXNUM_EQ(element_index,ISVREF(ring_buffer,
			    (SI_Long)1L)))
			goto end_loop_6;
		    element_index = FIXNUM_EQ(element_index,
			    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ?
			     FIX((SI_Long)0L) : FIXNUM_ADD1(element_index);
		    goto next_loop_6;
		  end_loop_6:;
		}
		reclaim_managed_float_array(vector_1);
		SVREF(ring_buffer,FIX((SI_Long)6L)) = new_managed_array;
		temp_1 = ISVREF(ring_buffer,(SI_Long)6L);
		store_managed_number_or_value_arg = new_element_value;
		temp_5 = 
			store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp_1,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(temp_1,IFIX(FIXNUM_ADD(index_2,
			Managed_array_index_offset))) : 
			ISVREF(ISVREF(temp_1,(IFIX(index_2) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),IFIX(index_2) & 
			(SI_Long)1023L),store_managed_number_or_value_arg);
		if (FIXNUM_LE(ISVREF(temp_1,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    temp_4 = FIXNUM_ADD(index_2,Managed_array_index_offset);
		    SVREF(temp_1,temp_4) = temp_5;
		}
		else {
		    temp_1 = ISVREF(temp_1,(IFIX(index_2) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(index_2) & (SI_Long)1023L;
		    ISVREF(temp_1,temp_3) = temp_5;
		}
	    }
	    vector_1 = ISVREF(ring_buffer,(SI_Long)7L);
	    if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
		    (SI_Long)0L),Managed_array_unique_marker)) {
		store_managed_number_or_value_arg = new_element_time;
		temp_4 = 
			store_managed_number_or_value_function(FIXNUM_LE(ISVREF(vector_1,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(vector_1,IFIX(FIXNUM_ADD(index_2,
			Managed_array_index_offset))) : 
			ISVREF(ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),IFIX(index_2) & 
			(SI_Long)1023L),store_managed_number_or_value_arg);
		if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    temp_1 = FIXNUM_ADD(index_2,Managed_array_index_offset);
		    SVREF(vector_1,temp_1) = temp_4;
		}
		else {
		    temp_1 = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(index_2) & (SI_Long)1023L;
		    ISVREF(temp_1,temp_3) = temp_4;
		}
	    }
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(new_element_time) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_element_time)) == 
		    (SI_Long)1L) {
		temp_1 = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(index_2) & (SI_Long)1023L;
		aref_new_value = DFLOAT_ISAREF_1(new_element_time,(SI_Long)0L);
		DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
	    }
	    else if (FLOATP(new_element_time)) {
		temp_1 = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(index_2) & (SI_Long)1023L;
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(new_element_time);
		DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
	    }
	    else {
		new_managed_array = allocate_managed_array(1,
			ISVREF(vector_1,(SI_Long)1L));
		if ( !TRUEP(ISVREF(ring_buffer,(SI_Long)3L))) {
		    element_index = ISVREF(ring_buffer,(SI_Long)2L);
		  next_loop_7:
		    if (FIXNUM_LE(ISVREF(new_managed_array,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			temp_1 = FIXNUM_ADD(element_index,
				Managed_array_index_offset);
			amf_available_array_cons_qm = 
				ISVREF(Vector_of_simple_float_array_pools,
				(SI_Long)1L);
			if (amf_available_array_cons_qm) {
			    amf_array = M_CAR(amf_available_array_cons_qm);
			    temp_4 = Vector_of_simple_float_array_pools;
			    temp_5 = M_CDR(amf_available_array_cons_qm);
			    SVREF(temp_4,FIX((SI_Long)1L)) = temp_5;
			    inline_note_reclaim_cons(amf_available_array_cons_qm,
				    Qfloat_array);
			    if (ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp_4 = 
					ISVREF(Available_float_array_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp_4) = amf_available_array_cons_qm;
				temp_4 = 
					Available_float_array_conses_tail_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
					amf_available_array_cons_qm;
			    }
			    else {
				temp_4 = Available_float_array_conses_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
					amf_available_array_cons_qm;
				temp_4 = 
					Available_float_array_conses_tail_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
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
			aref_new_value = DFLOAT_ISAREF_1(ISVREF(vector_1,
				(IFIX(element_index) >>  -  - 
				(SI_Long)10L) + (SI_Long)2L),
				IFIX(element_index) & (SI_Long)1023L);
			DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
			SVREF(new_managed_array,temp_1) = new_float;
		    }
		    else {
			temp_1 = ISVREF(new_managed_array,
				(IFIX(element_index) >>  -  - 
				(SI_Long)10L) + (SI_Long)2L);
			temp_3 = IFIX(element_index) & (SI_Long)1023L;
			amf_available_array_cons_qm = 
				ISVREF(Vector_of_simple_float_array_pools,
				(SI_Long)1L);
			if (amf_available_array_cons_qm) {
			    amf_array = M_CAR(amf_available_array_cons_qm);
			    temp_4 = Vector_of_simple_float_array_pools;
			    temp_5 = M_CDR(amf_available_array_cons_qm);
			    SVREF(temp_4,FIX((SI_Long)1L)) = temp_5;
			    inline_note_reclaim_cons(amf_available_array_cons_qm,
				    Qfloat_array);
			    if (ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp_4 = 
					ISVREF(Available_float_array_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp_4) = amf_available_array_cons_qm;
				temp_4 = 
					Available_float_array_conses_tail_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
					amf_available_array_cons_qm;
			    }
			    else {
				temp_4 = Available_float_array_conses_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
					amf_available_array_cons_qm;
				temp_4 = 
					Available_float_array_conses_tail_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_4,temp_5) = 
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
			aref_new_value = DFLOAT_ISAREF_1(ISVREF(vector_1,
				(IFIX(element_index) >>  -  - 
				(SI_Long)10L) + (SI_Long)2L),
				IFIX(element_index) & (SI_Long)1023L);
			DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
			ISVREF(temp_1,temp_3) = new_float;
		    }
		    if (FIXNUM_EQ(element_index,ISVREF(ring_buffer,
			    (SI_Long)1L)))
			goto end_loop_7;
		    element_index = FIXNUM_EQ(element_index,
			    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ?
			     FIX((SI_Long)0L) : FIXNUM_ADD1(element_index);
		    goto next_loop_7;
		  end_loop_7:;
		}
		reclaim_managed_float_array(vector_1);
		SVREF(ring_buffer,FIX((SI_Long)7L)) = new_managed_array;
		temp_1 = ISVREF(ring_buffer,(SI_Long)7L);
		store_managed_number_or_value_arg = new_element_time;
		temp_5 = 
			store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp_1,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(temp_1,IFIX(FIXNUM_ADD(index_2,
			Managed_array_index_offset))) : 
			ISVREF(ISVREF(temp_1,(IFIX(index_2) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),IFIX(index_2) & 
			(SI_Long)1023L),store_managed_number_or_value_arg);
		if (FIXNUM_LE(ISVREF(temp_1,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    temp_4 = FIXNUM_ADD(index_2,Managed_array_index_offset);
		    SVREF(temp_1,temp_4) = temp_5;
		}
		else {
		    temp_1 = ISVREF(temp_1,(IFIX(index_2) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(index_2) & (SI_Long)1023L;
		    ISVREF(temp_1,temp_3) = temp_5;
		}
	    }
	}
	if (ring_buffer_was_emptied_p) {
	    gensymed_symbol = Nil;
	    ab_loop_list_ = ISVREF(cascaded_ring_buffer,(SI_Long)11L);
	  next_loop_8:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_8;
	    gensymed_symbol = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    notify_client_of_change_to_cascaded_ring_buffer(gensymed_symbol);
	    goto next_loop_8;
	  end_loop_8:
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* STORE-NEW-ELEMENT-IN-HISTORY-CASCADED-RING-BUFFER */
Object store_new_element_in_history_cascaded_ring_buffer(cascaded_ring_buffer,
	    value,time_1)
    Object cascaded_ring_buffer, value, time_1;
{
    Object temp, ring_buffer_shell, index_1, temp_1, vector_1;
    Object store_managed_number_or_value_arg, temp_2, new_managed_array;
    Object element_index, amf_available_array_cons_qm, amf_array, temp_4;
    Object amf_result, new_float, ring_buffer, index_2;
    Object oldest_active_element_index_for_ring_buffer;
    SI_Long temp_3;
    double aref_new_value;

    x_note_fn_call(148,66);
    temp = ISVREF(cascaded_ring_buffer,(SI_Long)4L);
    ring_buffer_shell = CAR(temp);
    if (ISVREF(ring_buffer_shell,(SI_Long)3L)) {
	index_1 = ISVREF(ring_buffer_shell,(SI_Long)1L);
	temp_1 = FIXNUM_ADD1(ISVREF(ring_buffer_shell,(SI_Long)5L));
	SVREF(ring_buffer_shell,FIX((SI_Long)5L)) = temp_1;
	vector_1 = ISVREF(ring_buffer_shell,(SI_Long)6L);
	if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
		Managed_array_unique_marker)) {
	    store_managed_number_or_value_arg = value;
	    temp_2 = 
		    store_managed_number_or_value_function(FIXNUM_LE(ISVREF(vector_1,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(vector_1,IFIX(FIXNUM_ADD(index_1,
		    Managed_array_index_offset))) : ISVREF(ISVREF(vector_1,
		    (IFIX(index_1) >>  -  - (SI_Long)10L) + (SI_Long)2L),
		    IFIX(index_1) & (SI_Long)1023L),
		    store_managed_number_or_value_arg);
	    if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp_1 = FIXNUM_ADD(index_1,Managed_array_index_offset);
		SVREF(vector_1,temp_1) = temp_2;
	    }
	    else {
		temp_1 = ISVREF(vector_1,(IFIX(index_1) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(index_1) & (SI_Long)1023L;
		ISVREF(temp_1,temp_3) = temp_2;
	    }
	}
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L) {
	    temp_1 = ISVREF(vector_1,(IFIX(index_1) >>  -  - (SI_Long)10L) 
		    + (SI_Long)2L);
	    temp_3 = IFIX(index_1) & (SI_Long)1023L;
	    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
	    DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
	}
	else if (FLOATP(value)) {
	    temp_1 = ISVREF(vector_1,(IFIX(index_1) >>  -  - (SI_Long)10L) 
		    + (SI_Long)2L);
	    temp_3 = IFIX(index_1) & (SI_Long)1023L;
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
	    DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
	}
	else {
	    new_managed_array = allocate_managed_array(1,ISVREF(vector_1,
		    (SI_Long)1L));
	    if ( !TRUEP(ISVREF(ring_buffer_shell,(SI_Long)3L))) {
		element_index = ISVREF(ring_buffer_shell,(SI_Long)2L);
	      next_loop:
		if (FIXNUM_LE(ISVREF(new_managed_array,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    temp_1 = FIXNUM_ADD(element_index,
			    Managed_array_index_offset);
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_4 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_4;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
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
		    SVREF(new_managed_array,temp_1) = new_float;
		}
		else {
		    temp_1 = ISVREF(new_managed_array,(IFIX(element_index) 
			    >>  -  - (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(element_index) & (SI_Long)1023L;
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_4 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_4;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
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
		    ISVREF(temp_1,temp_3) = new_float;
		}
		if (FIXNUM_EQ(element_index,ISVREF(ring_buffer_shell,
			(SI_Long)1L)))
		    goto end_loop;
		element_index = FIXNUM_EQ(element_index,
			FIXNUM_SUB1(ISVREF(ring_buffer_shell,
			(SI_Long)4L))) ? FIX((SI_Long)0L) : 
			FIXNUM_ADD1(element_index);
		goto next_loop;
	      end_loop:;
	    }
	    reclaim_managed_float_array(vector_1);
	    SVREF(ring_buffer_shell,FIX((SI_Long)6L)) = new_managed_array;
	    temp_1 = ISVREF(ring_buffer_shell,(SI_Long)6L);
	    store_managed_number_or_value_arg = value;
	    temp_4 = 
		    store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp_1,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(temp_1,IFIX(FIXNUM_ADD(index_1,
		    Managed_array_index_offset))) : ISVREF(ISVREF(temp_1,
		    (IFIX(index_1) >>  -  - (SI_Long)10L) + (SI_Long)2L),
		    IFIX(index_1) & (SI_Long)1023L),
		    store_managed_number_or_value_arg);
	    if (FIXNUM_LE(ISVREF(temp_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp_2 = FIXNUM_ADD(index_1,Managed_array_index_offset);
		SVREF(temp_1,temp_2) = temp_4;
	    }
	    else {
		temp_1 = ISVREF(temp_1,(IFIX(index_1) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(index_1) & (SI_Long)1023L;
		ISVREF(temp_1,temp_3) = temp_4;
	    }
	}
	vector_1 = ISVREF(ring_buffer_shell,(SI_Long)7L);
	if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
		Managed_array_unique_marker)) {
	    store_managed_number_or_value_arg = time_1;
	    temp_2 = 
		    store_managed_number_or_value_function(FIXNUM_LE(ISVREF(vector_1,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(vector_1,IFIX(FIXNUM_ADD(index_1,
		    Managed_array_index_offset))) : ISVREF(ISVREF(vector_1,
		    (IFIX(index_1) >>  -  - (SI_Long)10L) + (SI_Long)2L),
		    IFIX(index_1) & (SI_Long)1023L),
		    store_managed_number_or_value_arg);
	    if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp_1 = FIXNUM_ADD(index_1,Managed_array_index_offset);
		SVREF(vector_1,temp_1) = temp_2;
	    }
	    else {
		temp_1 = ISVREF(vector_1,(IFIX(index_1) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(index_1) & (SI_Long)1023L;
		ISVREF(temp_1,temp_3) = temp_2;
	    }
	}
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(time_1) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(time_1)) == (SI_Long)1L) {
	    temp_1 = ISVREF(vector_1,(IFIX(index_1) >>  -  - (SI_Long)10L) 
		    + (SI_Long)2L);
	    temp_3 = IFIX(index_1) & (SI_Long)1023L;
	    aref_new_value = DFLOAT_ISAREF_1(time_1,(SI_Long)0L);
	    DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
	}
	else if (FLOATP(time_1)) {
	    temp_1 = ISVREF(vector_1,(IFIX(index_1) >>  -  - (SI_Long)10L) 
		    + (SI_Long)2L);
	    temp_3 = IFIX(index_1) & (SI_Long)1023L;
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(time_1);
	    DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
	}
	else {
	    new_managed_array = allocate_managed_array(1,ISVREF(vector_1,
		    (SI_Long)1L));
	    if ( !TRUEP(ISVREF(ring_buffer_shell,(SI_Long)3L))) {
		element_index = ISVREF(ring_buffer_shell,(SI_Long)2L);
	      next_loop_1:
		if (FIXNUM_LE(ISVREF(new_managed_array,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    temp_1 = FIXNUM_ADD(element_index,
			    Managed_array_index_offset);
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_4 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_4;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
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
		    SVREF(new_managed_array,temp_1) = new_float;
		}
		else {
		    temp_1 = ISVREF(new_managed_array,(IFIX(element_index) 
			    >>  -  - (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(element_index) & (SI_Long)1023L;
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_4 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_4;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
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
		    ISVREF(temp_1,temp_3) = new_float;
		}
		if (FIXNUM_EQ(element_index,ISVREF(ring_buffer_shell,
			(SI_Long)1L)))
		    goto end_loop_1;
		element_index = FIXNUM_EQ(element_index,
			FIXNUM_SUB1(ISVREF(ring_buffer_shell,
			(SI_Long)4L))) ? FIX((SI_Long)0L) : 
			FIXNUM_ADD1(element_index);
		goto next_loop_1;
	      end_loop_1:;
	    }
	    reclaim_managed_float_array(vector_1);
	    SVREF(ring_buffer_shell,FIX((SI_Long)7L)) = new_managed_array;
	    temp_1 = ISVREF(ring_buffer_shell,(SI_Long)7L);
	    store_managed_number_or_value_arg = time_1;
	    temp_4 = 
		    store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp_1,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(temp_1,IFIX(FIXNUM_ADD(index_1,
		    Managed_array_index_offset))) : ISVREF(ISVREF(temp_1,
		    (IFIX(index_1) >>  -  - (SI_Long)10L) + (SI_Long)2L),
		    IFIX(index_1) & (SI_Long)1023L),
		    store_managed_number_or_value_arg);
	    if (FIXNUM_LE(ISVREF(temp_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp_2 = FIXNUM_ADD(index_1,Managed_array_index_offset);
		SVREF(temp_1,temp_2) = temp_4;
	    }
	    else {
		temp_1 = ISVREF(temp_1,(IFIX(index_1) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(index_1) & (SI_Long)1023L;
		ISVREF(temp_1,temp_3) = temp_4;
	    }
	}
	return VALUES_1(SVREF(ring_buffer_shell,FIX((SI_Long)3L)) = Nil);
    }
    else {
	ring_buffer = ring_buffer_shell;
	index_2 = ISVREF(ring_buffer_shell,(SI_Long)1L);
	oldest_active_element_index_for_ring_buffer = ISVREF(ring_buffer,
		(SI_Long)2L);
	if (FIXNUM_EQ(FIXNUM_GE(index_2,
		oldest_active_element_index_for_ring_buffer) ? 
		FIXNUM_ADD1(FIXNUM_MINUS(index_2,
		oldest_active_element_index_for_ring_buffer)) : 
		FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(index_2,
		ISVREF(ring_buffer,(SI_Long)4L)),
		oldest_active_element_index_for_ring_buffer)),
		ISVREF(ring_buffer_shell,(SI_Long)4L)))
	    expand_history_ring_buffer(ring_buffer_shell);
	index_2 = ISVREF(ring_buffer_shell,(SI_Long)1L);
	ring_buffer = ring_buffer_shell;
	temp_3 = FIXNUM_EQ(index_2,FIXNUM_SUB1(ISVREF(ring_buffer,
		(SI_Long)4L))) ? (SI_Long)0L : IFIX(FIXNUM_ADD1(index_2));
	ISVREF(ring_buffer_shell,(SI_Long)1L) = FIX(temp_3);
	index_1 = ISVREF(ring_buffer_shell,(SI_Long)1L);
	temp_1 = FIXNUM_ADD1(ISVREF(ring_buffer_shell,(SI_Long)5L));
	SVREF(ring_buffer_shell,FIX((SI_Long)5L)) = temp_1;
	vector_1 = ISVREF(ring_buffer_shell,(SI_Long)6L);
	if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
		Managed_array_unique_marker)) {
	    store_managed_number_or_value_arg = value;
	    temp_2 = 
		    store_managed_number_or_value_function(FIXNUM_LE(ISVREF(vector_1,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(vector_1,IFIX(FIXNUM_ADD(index_1,
		    Managed_array_index_offset))) : ISVREF(ISVREF(vector_1,
		    (IFIX(index_1) >>  -  - (SI_Long)10L) + (SI_Long)2L),
		    IFIX(index_1) & (SI_Long)1023L),
		    store_managed_number_or_value_arg);
	    if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp_1 = FIXNUM_ADD(index_1,Managed_array_index_offset);
		SVREF(vector_1,temp_1) = temp_2;
	    }
	    else {
		temp_1 = ISVREF(vector_1,(IFIX(index_1) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(index_1) & (SI_Long)1023L;
		ISVREF(temp_1,temp_3) = temp_2;
	    }
	}
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L) {
	    temp_1 = ISVREF(vector_1,(IFIX(index_1) >>  -  - (SI_Long)10L) 
		    + (SI_Long)2L);
	    temp_3 = IFIX(index_1) & (SI_Long)1023L;
	    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
	    DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
	}
	else if (FLOATP(value)) {
	    temp_1 = ISVREF(vector_1,(IFIX(index_1) >>  -  - (SI_Long)10L) 
		    + (SI_Long)2L);
	    temp_3 = IFIX(index_1) & (SI_Long)1023L;
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
	    DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
	}
	else {
	    new_managed_array = allocate_managed_array(1,ISVREF(vector_1,
		    (SI_Long)1L));
	    if ( !TRUEP(ISVREF(ring_buffer_shell,(SI_Long)3L))) {
		element_index = ISVREF(ring_buffer_shell,(SI_Long)2L);
	      next_loop_2:
		if (FIXNUM_LE(ISVREF(new_managed_array,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    temp_1 = FIXNUM_ADD(element_index,
			    Managed_array_index_offset);
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_4 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_4;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
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
		    SVREF(new_managed_array,temp_1) = new_float;
		}
		else {
		    temp_1 = ISVREF(new_managed_array,(IFIX(element_index) 
			    >>  -  - (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(element_index) & (SI_Long)1023L;
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_4 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_4;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
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
		    ISVREF(temp_1,temp_3) = new_float;
		}
		if (FIXNUM_EQ(element_index,ISVREF(ring_buffer_shell,
			(SI_Long)1L)))
		    goto end_loop_2;
		element_index = FIXNUM_EQ(element_index,
			FIXNUM_SUB1(ISVREF(ring_buffer_shell,
			(SI_Long)4L))) ? FIX((SI_Long)0L) : 
			FIXNUM_ADD1(element_index);
		goto next_loop_2;
	      end_loop_2:;
	    }
	    reclaim_managed_float_array(vector_1);
	    SVREF(ring_buffer_shell,FIX((SI_Long)6L)) = new_managed_array;
	    temp_1 = ISVREF(ring_buffer_shell,(SI_Long)6L);
	    store_managed_number_or_value_arg = value;
	    temp_4 = 
		    store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp_1,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(temp_1,IFIX(FIXNUM_ADD(index_1,
		    Managed_array_index_offset))) : ISVREF(ISVREF(temp_1,
		    (IFIX(index_1) >>  -  - (SI_Long)10L) + (SI_Long)2L),
		    IFIX(index_1) & (SI_Long)1023L),
		    store_managed_number_or_value_arg);
	    if (FIXNUM_LE(ISVREF(temp_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp_2 = FIXNUM_ADD(index_1,Managed_array_index_offset);
		SVREF(temp_1,temp_2) = temp_4;
	    }
	    else {
		temp_1 = ISVREF(temp_1,(IFIX(index_1) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(index_1) & (SI_Long)1023L;
		ISVREF(temp_1,temp_3) = temp_4;
	    }
	}
	vector_1 = ISVREF(ring_buffer_shell,(SI_Long)7L);
	if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
		Managed_array_unique_marker)) {
	    store_managed_number_or_value_arg = time_1;
	    temp_2 = 
		    store_managed_number_or_value_function(FIXNUM_LE(ISVREF(vector_1,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(vector_1,IFIX(FIXNUM_ADD(index_1,
		    Managed_array_index_offset))) : ISVREF(ISVREF(vector_1,
		    (IFIX(index_1) >>  -  - (SI_Long)10L) + (SI_Long)2L),
		    IFIX(index_1) & (SI_Long)1023L),
		    store_managed_number_or_value_arg);
	    if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp_1 = FIXNUM_ADD(index_1,Managed_array_index_offset);
		return VALUES_1(SVREF(vector_1,temp_1) = temp_2);
	    }
	    else {
		temp_1 = ISVREF(vector_1,(IFIX(index_1) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(index_1) & (SI_Long)1023L;
		return VALUES_1(ISVREF(temp_1,temp_3) = temp_2);
	    }
	}
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(time_1) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(time_1)) == (SI_Long)1L) {
	    temp_1 = ISVREF(vector_1,(IFIX(index_1) >>  -  - (SI_Long)10L) 
		    + (SI_Long)2L);
	    temp_3 = IFIX(index_1) & (SI_Long)1023L;
	    aref_new_value = DFLOAT_ISAREF_1(time_1,(SI_Long)0L);
	    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISASET_1(temp_1,
		    temp_3,aref_new_value)));
	}
	else if (FLOATP(time_1)) {
	    temp_1 = ISVREF(vector_1,(IFIX(index_1) >>  -  - (SI_Long)10L) 
		    + (SI_Long)2L);
	    temp_3 = IFIX(index_1) & (SI_Long)1023L;
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(time_1);
	    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISASET_1(temp_1,
		    temp_3,aref_new_value)));
	}
	else {
	    new_managed_array = allocate_managed_array(1,ISVREF(vector_1,
		    (SI_Long)1L));
	    if ( !TRUEP(ISVREF(ring_buffer_shell,(SI_Long)3L))) {
		element_index = ISVREF(ring_buffer_shell,(SI_Long)2L);
	      next_loop_3:
		if (FIXNUM_LE(ISVREF(new_managed_array,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    temp_1 = FIXNUM_ADD(element_index,
			    Managed_array_index_offset);
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_4 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_4;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
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
		    SVREF(new_managed_array,temp_1) = new_float;
		}
		else {
		    temp_1 = ISVREF(new_managed_array,(IFIX(element_index) 
			    >>  -  - (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(element_index) & (SI_Long)1023L;
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_4 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_4;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
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
		    ISVREF(temp_1,temp_3) = new_float;
		}
		if (FIXNUM_EQ(element_index,ISVREF(ring_buffer_shell,
			(SI_Long)1L)))
		    goto end_loop_3;
		element_index = FIXNUM_EQ(element_index,
			FIXNUM_SUB1(ISVREF(ring_buffer_shell,
			(SI_Long)4L))) ? FIX((SI_Long)0L) : 
			FIXNUM_ADD1(element_index);
		goto next_loop_3;
	      end_loop_3:;
	    }
	    reclaim_managed_float_array(vector_1);
	    SVREF(ring_buffer_shell,FIX((SI_Long)7L)) = new_managed_array;
	    temp_1 = ISVREF(ring_buffer_shell,(SI_Long)7L);
	    store_managed_number_or_value_arg = time_1;
	    temp_4 = 
		    store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp_1,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(temp_1,IFIX(FIXNUM_ADD(index_1,
		    Managed_array_index_offset))) : ISVREF(ISVREF(temp_1,
		    (IFIX(index_1) >>  -  - (SI_Long)10L) + (SI_Long)2L),
		    IFIX(index_1) & (SI_Long)1023L),
		    store_managed_number_or_value_arg);
	    if (FIXNUM_LE(ISVREF(temp_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp_2 = FIXNUM_ADD(index_1,Managed_array_index_offset);
		return VALUES_1(SVREF(temp_1,temp_2) = temp_4);
	    }
	    else {
		temp_1 = ISVREF(temp_1,(IFIX(index_1) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(index_1) & (SI_Long)1023L;
		return VALUES_1(ISVREF(temp_1,temp_3) = temp_4);
	    }
	}
    }
}

/* STORE-NEW-ELEMENT-EVALUATION-VALUE-IN-HISTORY-CASCADED-RING-BUFFER */
Object store_new_element_evaluation_value_in_history_cascaded_ring_buffer(cascaded_ring_buffer,
	    value,time_1)
    Object cascaded_ring_buffer, value, time_1;
{
    Object temp, ring_buffer_shell, index_1, temp_1, vector_1;
    Object store_managed_number_or_value_arg, temp_2, new_managed_array;
    Object element_index, amf_available_array_cons_qm, amf_array, temp_4;
    Object amf_result, new_float, ring_buffer, index_2;
    Object oldest_active_element_index_for_ring_buffer;
    SI_Long temp_3;
    double aref_new_value;

    x_note_fn_call(148,67);
    temp = ISVREF(cascaded_ring_buffer,(SI_Long)4L);
    ring_buffer_shell = CAR(temp);
    if (ISVREF(ring_buffer_shell,(SI_Long)3L)) {
	index_1 = ISVREF(ring_buffer_shell,(SI_Long)1L);
	temp_1 = FIXNUM_ADD1(ISVREF(ring_buffer_shell,(SI_Long)5L));
	SVREF(ring_buffer_shell,FIX((SI_Long)5L)) = temp_1;
	vector_1 = ISVREF(ring_buffer_shell,(SI_Long)6L);
	if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
		Managed_array_unique_marker)) {
	    store_managed_number_or_value_arg = value;
	    temp_2 = 
		    store_managed_number_or_value_function(FIXNUM_LE(ISVREF(vector_1,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(vector_1,IFIX(FIXNUM_ADD(index_1,
		    Managed_array_index_offset))) : ISVREF(ISVREF(vector_1,
		    (IFIX(index_1) >>  -  - (SI_Long)10L) + (SI_Long)2L),
		    IFIX(index_1) & (SI_Long)1023L),
		    store_managed_number_or_value_arg);
	    if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp_1 = FIXNUM_ADD(index_1,Managed_array_index_offset);
		SVREF(vector_1,temp_1) = temp_2;
	    }
	    else {
		temp_1 = ISVREF(vector_1,(IFIX(index_1) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(index_1) & (SI_Long)1023L;
		ISVREF(temp_1,temp_3) = temp_2;
	    }
	}
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L) {
	    temp_1 = ISVREF(vector_1,(IFIX(index_1) >>  -  - (SI_Long)10L) 
		    + (SI_Long)2L);
	    temp_3 = IFIX(index_1) & (SI_Long)1023L;
	    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
	    DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
	}
	else if (FLOATP(value)) {
	    temp_1 = ISVREF(vector_1,(IFIX(index_1) >>  -  - (SI_Long)10L) 
		    + (SI_Long)2L);
	    temp_3 = IFIX(index_1) & (SI_Long)1023L;
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
	    DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
	}
	else {
	    new_managed_array = allocate_managed_array(1,ISVREF(vector_1,
		    (SI_Long)1L));
	    if ( !TRUEP(ISVREF(ring_buffer_shell,(SI_Long)3L))) {
		element_index = ISVREF(ring_buffer_shell,(SI_Long)2L);
	      next_loop:
		if (FIXNUM_LE(ISVREF(new_managed_array,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    temp_1 = FIXNUM_ADD(element_index,
			    Managed_array_index_offset);
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_4 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_4;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
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
		    SVREF(new_managed_array,temp_1) = new_float;
		}
		else {
		    temp_1 = ISVREF(new_managed_array,(IFIX(element_index) 
			    >>  -  - (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(element_index) & (SI_Long)1023L;
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_4 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_4;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
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
		    ISVREF(temp_1,temp_3) = new_float;
		}
		if (FIXNUM_EQ(element_index,ISVREF(ring_buffer_shell,
			(SI_Long)1L)))
		    goto end_loop;
		element_index = FIXNUM_EQ(element_index,
			FIXNUM_SUB1(ISVREF(ring_buffer_shell,
			(SI_Long)4L))) ? FIX((SI_Long)0L) : 
			FIXNUM_ADD1(element_index);
		goto next_loop;
	      end_loop:;
	    }
	    reclaim_managed_float_array(vector_1);
	    SVREF(ring_buffer_shell,FIX((SI_Long)6L)) = new_managed_array;
	    temp_1 = ISVREF(ring_buffer_shell,(SI_Long)6L);
	    store_managed_number_or_value_arg = value;
	    temp_4 = 
		    store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp_1,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(temp_1,IFIX(FIXNUM_ADD(index_1,
		    Managed_array_index_offset))) : ISVREF(ISVREF(temp_1,
		    (IFIX(index_1) >>  -  - (SI_Long)10L) + (SI_Long)2L),
		    IFIX(index_1) & (SI_Long)1023L),
		    store_managed_number_or_value_arg);
	    if (FIXNUM_LE(ISVREF(temp_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp_2 = FIXNUM_ADD(index_1,Managed_array_index_offset);
		SVREF(temp_1,temp_2) = temp_4;
	    }
	    else {
		temp_1 = ISVREF(temp_1,(IFIX(index_1) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(index_1) & (SI_Long)1023L;
		ISVREF(temp_1,temp_3) = temp_4;
	    }
	}
	vector_1 = ISVREF(ring_buffer_shell,(SI_Long)7L);
	if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
		Managed_array_unique_marker)) {
	    store_managed_number_or_value_arg = time_1;
	    temp_2 = 
		    store_managed_number_or_value_function(FIXNUM_LE(ISVREF(vector_1,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(vector_1,IFIX(FIXNUM_ADD(index_1,
		    Managed_array_index_offset))) : ISVREF(ISVREF(vector_1,
		    (IFIX(index_1) >>  -  - (SI_Long)10L) + (SI_Long)2L),
		    IFIX(index_1) & (SI_Long)1023L),
		    store_managed_number_or_value_arg);
	    if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp_1 = FIXNUM_ADD(index_1,Managed_array_index_offset);
		SVREF(vector_1,temp_1) = temp_2;
	    }
	    else {
		temp_1 = ISVREF(vector_1,(IFIX(index_1) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(index_1) & (SI_Long)1023L;
		ISVREF(temp_1,temp_3) = temp_2;
	    }
	}
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(time_1) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(time_1)) == (SI_Long)1L) {
	    temp_1 = ISVREF(vector_1,(IFIX(index_1) >>  -  - (SI_Long)10L) 
		    + (SI_Long)2L);
	    temp_3 = IFIX(index_1) & (SI_Long)1023L;
	    aref_new_value = DFLOAT_ISAREF_1(time_1,(SI_Long)0L);
	    DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
	}
	else if (FLOATP(time_1)) {
	    temp_1 = ISVREF(vector_1,(IFIX(index_1) >>  -  - (SI_Long)10L) 
		    + (SI_Long)2L);
	    temp_3 = IFIX(index_1) & (SI_Long)1023L;
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(time_1);
	    DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
	}
	else {
	    new_managed_array = allocate_managed_array(1,ISVREF(vector_1,
		    (SI_Long)1L));
	    if ( !TRUEP(ISVREF(ring_buffer_shell,(SI_Long)3L))) {
		element_index = ISVREF(ring_buffer_shell,(SI_Long)2L);
	      next_loop_1:
		if (FIXNUM_LE(ISVREF(new_managed_array,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    temp_1 = FIXNUM_ADD(element_index,
			    Managed_array_index_offset);
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_4 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_4;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
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
		    SVREF(new_managed_array,temp_1) = new_float;
		}
		else {
		    temp_1 = ISVREF(new_managed_array,(IFIX(element_index) 
			    >>  -  - (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(element_index) & (SI_Long)1023L;
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_4 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_4;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
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
		    ISVREF(temp_1,temp_3) = new_float;
		}
		if (FIXNUM_EQ(element_index,ISVREF(ring_buffer_shell,
			(SI_Long)1L)))
		    goto end_loop_1;
		element_index = FIXNUM_EQ(element_index,
			FIXNUM_SUB1(ISVREF(ring_buffer_shell,
			(SI_Long)4L))) ? FIX((SI_Long)0L) : 
			FIXNUM_ADD1(element_index);
		goto next_loop_1;
	      end_loop_1:;
	    }
	    reclaim_managed_float_array(vector_1);
	    SVREF(ring_buffer_shell,FIX((SI_Long)7L)) = new_managed_array;
	    temp_1 = ISVREF(ring_buffer_shell,(SI_Long)7L);
	    store_managed_number_or_value_arg = time_1;
	    temp_4 = 
		    store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp_1,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(temp_1,IFIX(FIXNUM_ADD(index_1,
		    Managed_array_index_offset))) : ISVREF(ISVREF(temp_1,
		    (IFIX(index_1) >>  -  - (SI_Long)10L) + (SI_Long)2L),
		    IFIX(index_1) & (SI_Long)1023L),
		    store_managed_number_or_value_arg);
	    if (FIXNUM_LE(ISVREF(temp_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp_2 = FIXNUM_ADD(index_1,Managed_array_index_offset);
		SVREF(temp_1,temp_2) = temp_4;
	    }
	    else {
		temp_1 = ISVREF(temp_1,(IFIX(index_1) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(index_1) & (SI_Long)1023L;
		ISVREF(temp_1,temp_3) = temp_4;
	    }
	}
	return VALUES_1(SVREF(ring_buffer_shell,FIX((SI_Long)3L)) = Nil);
    }
    else {
	ring_buffer = ring_buffer_shell;
	index_2 = ISVREF(ring_buffer_shell,(SI_Long)1L);
	oldest_active_element_index_for_ring_buffer = ISVREF(ring_buffer,
		(SI_Long)2L);
	if (FIXNUM_EQ(FIXNUM_GE(index_2,
		oldest_active_element_index_for_ring_buffer) ? 
		FIXNUM_ADD1(FIXNUM_MINUS(index_2,
		oldest_active_element_index_for_ring_buffer)) : 
		FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(index_2,
		ISVREF(ring_buffer,(SI_Long)4L)),
		oldest_active_element_index_for_ring_buffer)),
		ISVREF(ring_buffer_shell,(SI_Long)4L)))
	    expand_history_ring_buffer(ring_buffer_shell);
	index_2 = ISVREF(ring_buffer_shell,(SI_Long)1L);
	ring_buffer = ring_buffer_shell;
	temp_3 = FIXNUM_EQ(index_2,FIXNUM_SUB1(ISVREF(ring_buffer,
		(SI_Long)4L))) ? (SI_Long)0L : IFIX(FIXNUM_ADD1(index_2));
	ISVREF(ring_buffer_shell,(SI_Long)1L) = FIX(temp_3);
	index_1 = ISVREF(ring_buffer_shell,(SI_Long)1L);
	temp_1 = FIXNUM_ADD1(ISVREF(ring_buffer_shell,(SI_Long)5L));
	SVREF(ring_buffer_shell,FIX((SI_Long)5L)) = temp_1;
	vector_1 = ISVREF(ring_buffer_shell,(SI_Long)6L);
	if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
		Managed_array_unique_marker)) {
	    store_managed_number_or_value_arg = value;
	    temp_2 = 
		    store_managed_number_or_value_function(FIXNUM_LE(ISVREF(vector_1,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(vector_1,IFIX(FIXNUM_ADD(index_1,
		    Managed_array_index_offset))) : ISVREF(ISVREF(vector_1,
		    (IFIX(index_1) >>  -  - (SI_Long)10L) + (SI_Long)2L),
		    IFIX(index_1) & (SI_Long)1023L),
		    store_managed_number_or_value_arg);
	    if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp_1 = FIXNUM_ADD(index_1,Managed_array_index_offset);
		SVREF(vector_1,temp_1) = temp_2;
	    }
	    else {
		temp_1 = ISVREF(vector_1,(IFIX(index_1) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(index_1) & (SI_Long)1023L;
		ISVREF(temp_1,temp_3) = temp_2;
	    }
	}
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L) {
	    temp_1 = ISVREF(vector_1,(IFIX(index_1) >>  -  - (SI_Long)10L) 
		    + (SI_Long)2L);
	    temp_3 = IFIX(index_1) & (SI_Long)1023L;
	    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
	    DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
	}
	else if (FLOATP(value)) {
	    temp_1 = ISVREF(vector_1,(IFIX(index_1) >>  -  - (SI_Long)10L) 
		    + (SI_Long)2L);
	    temp_3 = IFIX(index_1) & (SI_Long)1023L;
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
	    DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
	}
	else {
	    new_managed_array = allocate_managed_array(1,ISVREF(vector_1,
		    (SI_Long)1L));
	    if ( !TRUEP(ISVREF(ring_buffer_shell,(SI_Long)3L))) {
		element_index = ISVREF(ring_buffer_shell,(SI_Long)2L);
	      next_loop_2:
		if (FIXNUM_LE(ISVREF(new_managed_array,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    temp_1 = FIXNUM_ADD(element_index,
			    Managed_array_index_offset);
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_4 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_4;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
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
		    SVREF(new_managed_array,temp_1) = new_float;
		}
		else {
		    temp_1 = ISVREF(new_managed_array,(IFIX(element_index) 
			    >>  -  - (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(element_index) & (SI_Long)1023L;
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_4 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_4;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
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
		    ISVREF(temp_1,temp_3) = new_float;
		}
		if (FIXNUM_EQ(element_index,ISVREF(ring_buffer_shell,
			(SI_Long)1L)))
		    goto end_loop_2;
		element_index = FIXNUM_EQ(element_index,
			FIXNUM_SUB1(ISVREF(ring_buffer_shell,
			(SI_Long)4L))) ? FIX((SI_Long)0L) : 
			FIXNUM_ADD1(element_index);
		goto next_loop_2;
	      end_loop_2:;
	    }
	    reclaim_managed_float_array(vector_1);
	    SVREF(ring_buffer_shell,FIX((SI_Long)6L)) = new_managed_array;
	    temp_1 = ISVREF(ring_buffer_shell,(SI_Long)6L);
	    store_managed_number_or_value_arg = value;
	    temp_4 = 
		    store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp_1,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(temp_1,IFIX(FIXNUM_ADD(index_1,
		    Managed_array_index_offset))) : ISVREF(ISVREF(temp_1,
		    (IFIX(index_1) >>  -  - (SI_Long)10L) + (SI_Long)2L),
		    IFIX(index_1) & (SI_Long)1023L),
		    store_managed_number_or_value_arg);
	    if (FIXNUM_LE(ISVREF(temp_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp_2 = FIXNUM_ADD(index_1,Managed_array_index_offset);
		SVREF(temp_1,temp_2) = temp_4;
	    }
	    else {
		temp_1 = ISVREF(temp_1,(IFIX(index_1) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(index_1) & (SI_Long)1023L;
		ISVREF(temp_1,temp_3) = temp_4;
	    }
	}
	vector_1 = ISVREF(ring_buffer_shell,(SI_Long)7L);
	if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
		Managed_array_unique_marker)) {
	    store_managed_number_or_value_arg = time_1;
	    temp_2 = 
		    store_managed_number_or_value_function(FIXNUM_LE(ISVREF(vector_1,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(vector_1,IFIX(FIXNUM_ADD(index_1,
		    Managed_array_index_offset))) : ISVREF(ISVREF(vector_1,
		    (IFIX(index_1) >>  -  - (SI_Long)10L) + (SI_Long)2L),
		    IFIX(index_1) & (SI_Long)1023L),
		    store_managed_number_or_value_arg);
	    if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp_1 = FIXNUM_ADD(index_1,Managed_array_index_offset);
		return VALUES_1(SVREF(vector_1,temp_1) = temp_2);
	    }
	    else {
		temp_1 = ISVREF(vector_1,(IFIX(index_1) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(index_1) & (SI_Long)1023L;
		return VALUES_1(ISVREF(temp_1,temp_3) = temp_2);
	    }
	}
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(time_1) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(time_1)) == (SI_Long)1L) {
	    temp_1 = ISVREF(vector_1,(IFIX(index_1) >>  -  - (SI_Long)10L) 
		    + (SI_Long)2L);
	    temp_3 = IFIX(index_1) & (SI_Long)1023L;
	    aref_new_value = DFLOAT_ISAREF_1(time_1,(SI_Long)0L);
	    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISASET_1(temp_1,
		    temp_3,aref_new_value)));
	}
	else if (FLOATP(time_1)) {
	    temp_1 = ISVREF(vector_1,(IFIX(index_1) >>  -  - (SI_Long)10L) 
		    + (SI_Long)2L);
	    temp_3 = IFIX(index_1) & (SI_Long)1023L;
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(time_1);
	    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISASET_1(temp_1,
		    temp_3,aref_new_value)));
	}
	else {
	    new_managed_array = allocate_managed_array(1,ISVREF(vector_1,
		    (SI_Long)1L));
	    if ( !TRUEP(ISVREF(ring_buffer_shell,(SI_Long)3L))) {
		element_index = ISVREF(ring_buffer_shell,(SI_Long)2L);
	      next_loop_3:
		if (FIXNUM_LE(ISVREF(new_managed_array,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    temp_1 = FIXNUM_ADD(element_index,
			    Managed_array_index_offset);
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_4 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_4;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
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
		    SVREF(new_managed_array,temp_1) = new_float;
		}
		else {
		    temp_1 = ISVREF(new_managed_array,(IFIX(element_index) 
			    >>  -  - (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(element_index) & (SI_Long)1023L;
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_4 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_4;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_2,temp_4) = amf_available_array_cons_qm;
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
		    ISVREF(temp_1,temp_3) = new_float;
		}
		if (FIXNUM_EQ(element_index,ISVREF(ring_buffer_shell,
			(SI_Long)1L)))
		    goto end_loop_3;
		element_index = FIXNUM_EQ(element_index,
			FIXNUM_SUB1(ISVREF(ring_buffer_shell,
			(SI_Long)4L))) ? FIX((SI_Long)0L) : 
			FIXNUM_ADD1(element_index);
		goto next_loop_3;
	      end_loop_3:;
	    }
	    reclaim_managed_float_array(vector_1);
	    SVREF(ring_buffer_shell,FIX((SI_Long)7L)) = new_managed_array;
	    temp_1 = ISVREF(ring_buffer_shell,(SI_Long)7L);
	    store_managed_number_or_value_arg = time_1;
	    temp_4 = 
		    store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp_1,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(temp_1,IFIX(FIXNUM_ADD(index_1,
		    Managed_array_index_offset))) : ISVREF(ISVREF(temp_1,
		    (IFIX(index_1) >>  -  - (SI_Long)10L) + (SI_Long)2L),
		    IFIX(index_1) & (SI_Long)1023L),
		    store_managed_number_or_value_arg);
	    if (FIXNUM_LE(ISVREF(temp_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp_2 = FIXNUM_ADD(index_1,Managed_array_index_offset);
		return VALUES_1(SVREF(temp_1,temp_2) = temp_4);
	    }
	    else {
		temp_1 = ISVREF(temp_1,(IFIX(index_1) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(index_1) & (SI_Long)1023L;
		return VALUES_1(ISVREF(temp_1,temp_3) = temp_4);
	    }
	}
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Data_point_value, Qdata_point_value);

/* STORE-OLD-DATA-IN-HISTORY-RING-BUFFER */
Object store_old_data_in_history_ring_buffer varargs_1(int, n)
{
    Object ring_buffer, data_point_value, data_point_time;
    Object overwrite_value_if_duplicate_time_qm, index_1;
    Object oldest_active_element_index_for_ring_buffer, temp;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(148,68);
    INIT_ARGS_nonrelocating();
    ring_buffer = REQUIRED_ARG_nonrelocating();
    data_point_value = REQUIRED_ARG_nonrelocating();
    data_point_time = REQUIRED_ARG_nonrelocating();
    PUSH_SPECIAL_WITH_SYMBOL(Data_point_value,Qdata_point_value,data_point_value,
	    0);
      overwrite_value_if_duplicate_time_qm = 
	      OPTIONAL_ARG_P_nonrelocating() ? 
	      OPTIONAL_ARG_nonrelocating() : T;
      END_ARGS_nonrelocating();
      index_1 = ISVREF(ring_buffer,(SI_Long)1L);
      oldest_active_element_index_for_ring_buffer = ISVREF(ring_buffer,
	      (SI_Long)2L);
      if (FIXNUM_EQ(FIXNUM_GE(index_1,
	      oldest_active_element_index_for_ring_buffer) ? 
	      FIXNUM_ADD1(FIXNUM_MINUS(index_1,
	      oldest_active_element_index_for_ring_buffer)) : 
	      FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(index_1,
	      ISVREF(ring_buffer,(SI_Long)4L)),
	      oldest_active_element_index_for_ring_buffer)),
	      ISVREF(ring_buffer,(SI_Long)4L)))
	  expand_history_ring_buffer(ring_buffer);
      temp = overwrite_value_if_duplicate_time_qm ? 
	      overwrite_old_data_point_qm(ring_buffer,Data_point_value,
	      data_point_time) : Qnil;
      if (temp)
	  result = VALUES_1(temp);
      else
	  result = make_space_for_and_insert_old_data_point(ring_buffer,
		  Data_point_value,data_point_time);
    POP_SPECIAL();
    return result;
}

/* OVERWRITE-OLD-DATA-POINT? */
Object overwrite_old_data_point_qm(ring_buffer,data_point_value,
	    data_point_time)
    Object ring_buffer, data_point_value, data_point_time;
{
    Object history_value, closest_history_time, next_history_time;
    Object ring_buffer_index, temp, vector_1;
    Object store_managed_number_or_value_arg, temp_1, new_managed_array;
    Object element_index, amf_available_array_cons_qm, amf_array, temp_3;
    Object amf_result, new_float;
    SI_Long temp_2;
    double aref_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(148,69);
    PUSH_SPECIAL_WITH_SYMBOL(Data_point_value,Qdata_point_value,data_point_value,
	    0);
      result = get_ring_buffer_element_at_history_time(ring_buffer,
	      data_point_time);
      MVS_4(result,history_value,closest_history_time,next_history_time,
	      ring_buffer_index);
      if (NUM_EQ(data_point_time,closest_history_time)) {
	  temp = FIXNUM_ADD1(ISVREF(ring_buffer,(SI_Long)5L));
	  SVREF(ring_buffer,FIX((SI_Long)5L)) = temp;
	  vector_1 = ISVREF(ring_buffer,(SI_Long)6L);
	  if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
		  Managed_array_unique_marker)) {
	      store_managed_number_or_value_arg = Data_point_value;
	      temp_1 = 
		      store_managed_number_or_value_function(FIXNUM_LE(ISVREF(vector_1,
		      (SI_Long)1L),Maximum_in_place_array_size) ? 
		      ISVREF(vector_1,IFIX(FIXNUM_ADD(ring_buffer_index,
		      Managed_array_index_offset))) : 
		      ISVREF(ISVREF(vector_1,(IFIX(ring_buffer_index) >>  
		      -  - (SI_Long)10L) + (SI_Long)2L),
		      IFIX(ring_buffer_index) & (SI_Long)1023L),
		      store_managed_number_or_value_arg);
	      if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		      Maximum_in_place_array_size)) {
		  temp = FIXNUM_ADD(ring_buffer_index,
			  Managed_array_index_offset);
		  SVREF(vector_1,temp) = temp_1;
	      }
	      else {
		  temp = ISVREF(vector_1,(IFIX(ring_buffer_index) >>  -  - 
			  (SI_Long)10L) + (SI_Long)2L);
		  temp_2 = IFIX(ring_buffer_index) & (SI_Long)1023L;
		  ISVREF(temp,temp_2) = temp_1;
	      }
	  }
	  else if (INLINE_DOUBLE_FLOAT_VECTOR_P(Data_point_value) != 
		  (SI_Long)0L && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Data_point_value)) == 
		  (SI_Long)1L) {
	      temp = ISVREF(vector_1,(IFIX(ring_buffer_index) >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L);
	      temp_2 = IFIX(ring_buffer_index) & (SI_Long)1023L;
	      aref_new_value = DFLOAT_ISAREF_1(Data_point_value,(SI_Long)0L);
	      DFLOAT_ISASET_1(temp,temp_2,aref_new_value);
	  }
	  else if (FLOATP(Data_point_value)) {
	      temp = ISVREF(vector_1,(IFIX(ring_buffer_index) >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L);
	      temp_2 = IFIX(ring_buffer_index) & (SI_Long)1023L;
	      aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(Data_point_value);
	      DFLOAT_ISASET_1(temp,temp_2,aref_new_value);
	  }
	  else {
	      new_managed_array = allocate_managed_array(1,ISVREF(vector_1,
		      (SI_Long)1L));
	      if ( !TRUEP(ISVREF(ring_buffer,(SI_Long)3L))) {
		  element_index = ISVREF(ring_buffer,(SI_Long)2L);
		next_loop:
		  if (FIXNUM_LE(ISVREF(new_managed_array,(SI_Long)1L),
			  Maximum_in_place_array_size)) {
		      temp = FIXNUM_ADD(element_index,
			      Managed_array_index_offset);
		      amf_available_array_cons_qm = 
			      ISVREF(Vector_of_simple_float_array_pools,
			      (SI_Long)1L);
		      if (amf_available_array_cons_qm) {
			  amf_array = M_CAR(amf_available_array_cons_qm);
			  temp_1 = Vector_of_simple_float_array_pools;
			  temp_3 = M_CDR(amf_available_array_cons_qm);
			  SVREF(temp_1,FIX((SI_Long)1L)) = temp_3;
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
			      temp_3 = Current_thread_index;
			      SVREF(temp_1,temp_3) = 
				      amf_available_array_cons_qm;
			  }
			  else {
			      temp_1 = Available_float_array_conses_vector;
			      temp_3 = Current_thread_index;
			      SVREF(temp_1,temp_3) = 
				      amf_available_array_cons_qm;
			      temp_1 = 
				      Available_float_array_conses_tail_vector;
			      temp_3 = Current_thread_index;
			      SVREF(temp_1,temp_3) = 
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
			  amf_result = generate_float_vector(FIX((SI_Long)1L));
		      }
		      new_float = amf_result;
		      aref_new_value = DFLOAT_ISAREF_1(ISVREF(vector_1,
			      (IFIX(element_index) >>  -  - (SI_Long)10L) 
			      + (SI_Long)2L),IFIX(element_index) & 
			      (SI_Long)1023L);
		      DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		      SVREF(new_managed_array,temp) = new_float;
		  }
		  else {
		      temp = ISVREF(new_managed_array,(IFIX(element_index) 
			      >>  -  - (SI_Long)10L) + (SI_Long)2L);
		      temp_2 = IFIX(element_index) & (SI_Long)1023L;
		      amf_available_array_cons_qm = 
			      ISVREF(Vector_of_simple_float_array_pools,
			      (SI_Long)1L);
		      if (amf_available_array_cons_qm) {
			  amf_array = M_CAR(amf_available_array_cons_qm);
			  temp_1 = Vector_of_simple_float_array_pools;
			  temp_3 = M_CDR(amf_available_array_cons_qm);
			  SVREF(temp_1,FIX((SI_Long)1L)) = temp_3;
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
			      temp_3 = Current_thread_index;
			      SVREF(temp_1,temp_3) = 
				      amf_available_array_cons_qm;
			  }
			  else {
			      temp_1 = Available_float_array_conses_vector;
			      temp_3 = Current_thread_index;
			      SVREF(temp_1,temp_3) = 
				      amf_available_array_cons_qm;
			      temp_1 = 
				      Available_float_array_conses_tail_vector;
			      temp_3 = Current_thread_index;
			      SVREF(temp_1,temp_3) = 
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
			  amf_result = generate_float_vector(FIX((SI_Long)1L));
		      }
		      new_float = amf_result;
		      aref_new_value = DFLOAT_ISAREF_1(ISVREF(vector_1,
			      (IFIX(element_index) >>  -  - (SI_Long)10L) 
			      + (SI_Long)2L),IFIX(element_index) & 
			      (SI_Long)1023L);
		      DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		      ISVREF(temp,temp_2) = new_float;
		  }
		  if (FIXNUM_EQ(element_index,ISVREF(ring_buffer,(SI_Long)1L)))
		      goto end_loop;
		  element_index = FIXNUM_EQ(element_index,
			  FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ? 
			  FIX((SI_Long)0L) : FIXNUM_ADD1(element_index);
		  goto next_loop;
		end_loop:;
	      }
	      reclaim_managed_float_array(vector_1);
	      SVREF(ring_buffer,FIX((SI_Long)6L)) = new_managed_array;
	      temp = ISVREF(ring_buffer,(SI_Long)6L);
	      store_managed_number_or_value_arg = Data_point_value;
	      temp_3 = 
		      store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp,
		      (SI_Long)1L),Maximum_in_place_array_size) ? 
		      ISVREF(temp,IFIX(FIXNUM_ADD(ring_buffer_index,
		      Managed_array_index_offset))) : ISVREF(ISVREF(temp,
		      (IFIX(ring_buffer_index) >>  -  - (SI_Long)10L) + 
		      (SI_Long)2L),IFIX(ring_buffer_index) & 
		      (SI_Long)1023L),store_managed_number_or_value_arg);
	      if (FIXNUM_LE(ISVREF(temp,(SI_Long)1L),
		      Maximum_in_place_array_size)) {
		  temp_1 = FIXNUM_ADD(ring_buffer_index,
			  Managed_array_index_offset);
		  SVREF(temp,temp_1) = temp_3;
	      }
	      else {
		  temp = ISVREF(temp,(IFIX(ring_buffer_index) >>  -  - 
			  (SI_Long)10L) + (SI_Long)2L);
		  temp_2 = IFIX(ring_buffer_index) & (SI_Long)1023L;
		  ISVREF(temp,temp_2) = temp_3;
	      }
	  }
	  vector_1 = ISVREF(ring_buffer,(SI_Long)7L);
	  if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
		  Managed_array_unique_marker)) {
	      store_managed_number_or_value_arg = data_point_time;
	      temp_1 = 
		      store_managed_number_or_value_function(FIXNUM_LE(ISVREF(vector_1,
		      (SI_Long)1L),Maximum_in_place_array_size) ? 
		      ISVREF(vector_1,IFIX(FIXNUM_ADD(ring_buffer_index,
		      Managed_array_index_offset))) : 
		      ISVREF(ISVREF(vector_1,(IFIX(ring_buffer_index) >>  
		      -  - (SI_Long)10L) + (SI_Long)2L),
		      IFIX(ring_buffer_index) & (SI_Long)1023L),
		      store_managed_number_or_value_arg);
	      if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		      Maximum_in_place_array_size)) {
		  temp = FIXNUM_ADD(ring_buffer_index,
			  Managed_array_index_offset);
		  SVREF(vector_1,temp) = temp_1;
	      }
	      else {
		  temp = ISVREF(vector_1,(IFIX(ring_buffer_index) >>  -  - 
			  (SI_Long)10L) + (SI_Long)2L);
		  temp_2 = IFIX(ring_buffer_index) & (SI_Long)1023L;
		  ISVREF(temp,temp_2) = temp_1;
	      }
	  }
	  else if (INLINE_DOUBLE_FLOAT_VECTOR_P(data_point_time) != 
		  (SI_Long)0L && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(data_point_time)) == 
		  (SI_Long)1L) {
	      temp = ISVREF(vector_1,(IFIX(ring_buffer_index) >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L);
	      temp_2 = IFIX(ring_buffer_index) & (SI_Long)1023L;
	      aref_new_value = DFLOAT_ISAREF_1(data_point_time,(SI_Long)0L);
	      DFLOAT_ISASET_1(temp,temp_2,aref_new_value);
	  }
	  else if (FLOATP(data_point_time)) {
	      temp = ISVREF(vector_1,(IFIX(ring_buffer_index) >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L);
	      temp_2 = IFIX(ring_buffer_index) & (SI_Long)1023L;
	      aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(data_point_time);
	      DFLOAT_ISASET_1(temp,temp_2,aref_new_value);
	  }
	  else {
	      new_managed_array = allocate_managed_array(1,ISVREF(vector_1,
		      (SI_Long)1L));
	      if ( !TRUEP(ISVREF(ring_buffer,(SI_Long)3L))) {
		  element_index = ISVREF(ring_buffer,(SI_Long)2L);
		next_loop_1:
		  if (FIXNUM_LE(ISVREF(new_managed_array,(SI_Long)1L),
			  Maximum_in_place_array_size)) {
		      temp = FIXNUM_ADD(element_index,
			      Managed_array_index_offset);
		      amf_available_array_cons_qm = 
			      ISVREF(Vector_of_simple_float_array_pools,
			      (SI_Long)1L);
		      if (amf_available_array_cons_qm) {
			  amf_array = M_CAR(amf_available_array_cons_qm);
			  temp_1 = Vector_of_simple_float_array_pools;
			  temp_3 = M_CDR(amf_available_array_cons_qm);
			  SVREF(temp_1,FIX((SI_Long)1L)) = temp_3;
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
			      temp_3 = Current_thread_index;
			      SVREF(temp_1,temp_3) = 
				      amf_available_array_cons_qm;
			  }
			  else {
			      temp_1 = Available_float_array_conses_vector;
			      temp_3 = Current_thread_index;
			      SVREF(temp_1,temp_3) = 
				      amf_available_array_cons_qm;
			      temp_1 = 
				      Available_float_array_conses_tail_vector;
			      temp_3 = Current_thread_index;
			      SVREF(temp_1,temp_3) = 
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
			  amf_result = generate_float_vector(FIX((SI_Long)1L));
		      }
		      new_float = amf_result;
		      aref_new_value = DFLOAT_ISAREF_1(ISVREF(vector_1,
			      (IFIX(element_index) >>  -  - (SI_Long)10L) 
			      + (SI_Long)2L),IFIX(element_index) & 
			      (SI_Long)1023L);
		      DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		      SVREF(new_managed_array,temp) = new_float;
		  }
		  else {
		      temp = ISVREF(new_managed_array,(IFIX(element_index) 
			      >>  -  - (SI_Long)10L) + (SI_Long)2L);
		      temp_2 = IFIX(element_index) & (SI_Long)1023L;
		      amf_available_array_cons_qm = 
			      ISVREF(Vector_of_simple_float_array_pools,
			      (SI_Long)1L);
		      if (amf_available_array_cons_qm) {
			  amf_array = M_CAR(amf_available_array_cons_qm);
			  temp_1 = Vector_of_simple_float_array_pools;
			  temp_3 = M_CDR(amf_available_array_cons_qm);
			  SVREF(temp_1,FIX((SI_Long)1L)) = temp_3;
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
			      temp_3 = Current_thread_index;
			      SVREF(temp_1,temp_3) = 
				      amf_available_array_cons_qm;
			  }
			  else {
			      temp_1 = Available_float_array_conses_vector;
			      temp_3 = Current_thread_index;
			      SVREF(temp_1,temp_3) = 
				      amf_available_array_cons_qm;
			      temp_1 = 
				      Available_float_array_conses_tail_vector;
			      temp_3 = Current_thread_index;
			      SVREF(temp_1,temp_3) = 
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
			  amf_result = generate_float_vector(FIX((SI_Long)1L));
		      }
		      new_float = amf_result;
		      aref_new_value = DFLOAT_ISAREF_1(ISVREF(vector_1,
			      (IFIX(element_index) >>  -  - (SI_Long)10L) 
			      + (SI_Long)2L),IFIX(element_index) & 
			      (SI_Long)1023L);
		      DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		      ISVREF(temp,temp_2) = new_float;
		  }
		  if (FIXNUM_EQ(element_index,ISVREF(ring_buffer,(SI_Long)1L)))
		      goto end_loop_1;
		  element_index = FIXNUM_EQ(element_index,
			  FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ? 
			  FIX((SI_Long)0L) : FIXNUM_ADD1(element_index);
		  goto next_loop_1;
		end_loop_1:;
	      }
	      reclaim_managed_float_array(vector_1);
	      SVREF(ring_buffer,FIX((SI_Long)7L)) = new_managed_array;
	      temp = ISVREF(ring_buffer,(SI_Long)7L);
	      store_managed_number_or_value_arg = data_point_time;
	      temp_3 = 
		      store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp,
		      (SI_Long)1L),Maximum_in_place_array_size) ? 
		      ISVREF(temp,IFIX(FIXNUM_ADD(ring_buffer_index,
		      Managed_array_index_offset))) : ISVREF(ISVREF(temp,
		      (IFIX(ring_buffer_index) >>  -  - (SI_Long)10L) + 
		      (SI_Long)2L),IFIX(ring_buffer_index) & 
		      (SI_Long)1023L),store_managed_number_or_value_arg);
	      if (FIXNUM_LE(ISVREF(temp,(SI_Long)1L),
		      Maximum_in_place_array_size)) {
		  temp_1 = FIXNUM_ADD(ring_buffer_index,
			  Managed_array_index_offset);
		  SVREF(temp,temp_1) = temp_3;
	      }
	      else {
		  temp = ISVREF(temp,(IFIX(ring_buffer_index) >>  -  - 
			  (SI_Long)10L) + (SI_Long)2L);
		  temp_2 = IFIX(ring_buffer_index) & (SI_Long)1023L;
		  ISVREF(temp,temp_2) = temp_3;
	      }
	  }
	  if (text_string_p(history_value))
	      reclaim_text_string(history_value);
	  result = VALUES_1(T);
      }
      else {
	  if (text_string_p(history_value))
	      reclaim_text_string(history_value);
	  result = VALUES_1(Nil);
      }
    POP_SPECIAL();
    return result;
}

/* MAKE-SPACE-FOR-AND-INSERT-OLD-DATA-POINT */
Object make_space_for_and_insert_old_data_point(ring_buffer,
	    data_point_value,data_point_time)
    Object ring_buffer, data_point_value, data_point_time;
{
    Object index_1, index_to_copy_to, index_to_copy_from, temp_1, vector_1;
    Object store_managed_number_or_value_arg, temp_2, new_managed_array;
    Object element_index, amf_available_array_cons_qm, amf_array, temp_3;
    Object amf_result, new_float;
    SI_Long temp;
    double aref_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(148,70);
    PUSH_SPECIAL_WITH_SYMBOL(Data_point_value,Qdata_point_value,data_point_value,
	    0);
      index_1 = ISVREF(ring_buffer,(SI_Long)1L);
      temp = FIXNUM_EQ(index_1,FIXNUM_SUB1(ISVREF(ring_buffer,
	      (SI_Long)4L))) ? (SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
      index_to_copy_to = ISVREF(ring_buffer,(SI_Long)1L) = FIX(temp);
      index_to_copy_from = IFIX(index_to_copy_to) == (SI_Long)0L ? 
	      FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L)) : 
	      FIXNUM_SUB1(index_to_copy_to);
    next_loop:
      if (insert_old_data_point_if_appropriate(ring_buffer,
	      index_to_copy_to,index_to_copy_from,Data_point_value,
	      data_point_time)) {
	  result = VALUES_0();
	  goto end_1;
      }
      if (FIXNUM_EQ(index_to_copy_from,ISVREF(ring_buffer,(SI_Long)2L)))
	  goto end_loop;
      index_to_copy_to = IFIX(index_to_copy_to) == (SI_Long)0L ? 
	      FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L)) : 
	      FIXNUM_SUB1(index_to_copy_to);
      index_to_copy_from = IFIX(index_to_copy_from) == (SI_Long)0L ? 
	      FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L)) : 
	      FIXNUM_SUB1(index_to_copy_from);
      goto next_loop;
    end_loop:
      temp_1 = FIXNUM_ADD1(ISVREF(ring_buffer,(SI_Long)5L));
      SVREF(ring_buffer,FIX((SI_Long)5L)) = temp_1;
      vector_1 = ISVREF(ring_buffer,(SI_Long)6L);
      if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
	      Managed_array_unique_marker)) {
	  store_managed_number_or_value_arg = Data_point_value;
	  temp_2 = 
		  store_managed_number_or_value_function(FIXNUM_LE(ISVREF(vector_1,
		  (SI_Long)1L),Maximum_in_place_array_size) ? 
		  ISVREF(vector_1,IFIX(FIXNUM_ADD(index_to_copy_from,
		  Managed_array_index_offset))) : ISVREF(ISVREF(vector_1,
		  (IFIX(index_to_copy_from) >>  -  - (SI_Long)10L) + 
		  (SI_Long)2L),IFIX(index_to_copy_from) & (SI_Long)1023L),
		  store_managed_number_or_value_arg);
	  if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      temp_1 = FIXNUM_ADD(index_to_copy_from,
		      Managed_array_index_offset);
	      SVREF(vector_1,temp_1) = temp_2;
	  }
	  else {
	      temp_1 = ISVREF(vector_1,(IFIX(index_to_copy_from) >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L);
	      temp = IFIX(index_to_copy_from) & (SI_Long)1023L;
	      ISVREF(temp_1,temp) = temp_2;
	  }
      }
      else if (INLINE_DOUBLE_FLOAT_VECTOR_P(Data_point_value) != 
	      (SI_Long)0L && 
	      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Data_point_value)) == 
		  (SI_Long)1L) {
	  temp_1 = ISVREF(vector_1,(IFIX(index_to_copy_from) >>  -  - 
		  (SI_Long)10L) + (SI_Long)2L);
	  temp = IFIX(index_to_copy_from) & (SI_Long)1023L;
	  aref_new_value = DFLOAT_ISAREF_1(Data_point_value,(SI_Long)0L);
	  DFLOAT_ISASET_1(temp_1,temp,aref_new_value);
      }
      else if (FLOATP(Data_point_value)) {
	  temp_1 = ISVREF(vector_1,(IFIX(index_to_copy_from) >>  -  - 
		  (SI_Long)10L) + (SI_Long)2L);
	  temp = IFIX(index_to_copy_from) & (SI_Long)1023L;
	  aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(Data_point_value);
	  DFLOAT_ISASET_1(temp_1,temp,aref_new_value);
      }
      else {
	  new_managed_array = allocate_managed_array(1,ISVREF(vector_1,
		  (SI_Long)1L));
	  if ( !TRUEP(ISVREF(ring_buffer,(SI_Long)3L))) {
	      element_index = ISVREF(ring_buffer,(SI_Long)2L);
	    next_loop_1:
	      if (FIXNUM_LE(ISVREF(new_managed_array,(SI_Long)1L),
		      Maximum_in_place_array_size)) {
		  temp_1 = FIXNUM_ADD(element_index,
			  Managed_array_index_offset);
		  amf_available_array_cons_qm = 
			  ISVREF(Vector_of_simple_float_array_pools,
			  (SI_Long)1L);
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
		  aref_new_value = DFLOAT_ISAREF_1(ISVREF(vector_1,
			  (IFIX(element_index) >>  -  - (SI_Long)10L) + 
			  (SI_Long)2L),IFIX(element_index) & (SI_Long)1023L);
		  DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		  SVREF(new_managed_array,temp_1) = new_float;
	      }
	      else {
		  temp_1 = ISVREF(new_managed_array,(IFIX(element_index) 
			  >>  -  - (SI_Long)10L) + (SI_Long)2L);
		  temp = IFIX(element_index) & (SI_Long)1023L;
		  amf_available_array_cons_qm = 
			  ISVREF(Vector_of_simple_float_array_pools,
			  (SI_Long)1L);
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
		  aref_new_value = DFLOAT_ISAREF_1(ISVREF(vector_1,
			  (IFIX(element_index) >>  -  - (SI_Long)10L) + 
			  (SI_Long)2L),IFIX(element_index) & (SI_Long)1023L);
		  DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		  ISVREF(temp_1,temp) = new_float;
	      }
	      if (FIXNUM_EQ(element_index,ISVREF(ring_buffer,(SI_Long)1L)))
		  goto end_loop_1;
	      element_index = FIXNUM_EQ(element_index,
		      FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ? 
		      FIX((SI_Long)0L) : FIXNUM_ADD1(element_index);
	      goto next_loop_1;
	    end_loop_1:;
	  }
	  reclaim_managed_float_array(vector_1);
	  SVREF(ring_buffer,FIX((SI_Long)6L)) = new_managed_array;
	  temp_1 = ISVREF(ring_buffer,(SI_Long)6L);
	  store_managed_number_or_value_arg = Data_point_value;
	  temp_3 = 
		  store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp_1,
		  (SI_Long)1L),Maximum_in_place_array_size) ? 
		  ISVREF(temp_1,IFIX(FIXNUM_ADD(index_to_copy_from,
		  Managed_array_index_offset))) : ISVREF(ISVREF(temp_1,
		  (IFIX(index_to_copy_from) >>  -  - (SI_Long)10L) + 
		  (SI_Long)2L),IFIX(index_to_copy_from) & (SI_Long)1023L),
		  store_managed_number_or_value_arg);
	  if (FIXNUM_LE(ISVREF(temp_1,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      temp_2 = FIXNUM_ADD(index_to_copy_from,
		      Managed_array_index_offset);
	      SVREF(temp_1,temp_2) = temp_3;
	  }
	  else {
	      temp_1 = ISVREF(temp_1,(IFIX(index_to_copy_from) >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L);
	      temp = IFIX(index_to_copy_from) & (SI_Long)1023L;
	      ISVREF(temp_1,temp) = temp_3;
	  }
      }
      vector_1 = ISVREF(ring_buffer,(SI_Long)7L);
      if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
	      Managed_array_unique_marker)) {
	  store_managed_number_or_value_arg = data_point_time;
	  temp_2 = 
		  store_managed_number_or_value_function(FIXNUM_LE(ISVREF(vector_1,
		  (SI_Long)1L),Maximum_in_place_array_size) ? 
		  ISVREF(vector_1,IFIX(FIXNUM_ADD(index_to_copy_from,
		  Managed_array_index_offset))) : ISVREF(ISVREF(vector_1,
		  (IFIX(index_to_copy_from) >>  -  - (SI_Long)10L) + 
		  (SI_Long)2L),IFIX(index_to_copy_from) & (SI_Long)1023L),
		  store_managed_number_or_value_arg);
	  if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      temp_1 = FIXNUM_ADD(index_to_copy_from,
		      Managed_array_index_offset);
	      SVREF(vector_1,temp_1) = temp_2;
	  }
	  else {
	      temp_1 = ISVREF(vector_1,(IFIX(index_to_copy_from) >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L);
	      temp = IFIX(index_to_copy_from) & (SI_Long)1023L;
	      ISVREF(temp_1,temp) = temp_2;
	  }
      }
      else if (INLINE_DOUBLE_FLOAT_VECTOR_P(data_point_time) != 
	      (SI_Long)0L && 
	      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(data_point_time)) == 
		  (SI_Long)1L) {
	  temp_1 = ISVREF(vector_1,(IFIX(index_to_copy_from) >>  -  - 
		  (SI_Long)10L) + (SI_Long)2L);
	  temp = IFIX(index_to_copy_from) & (SI_Long)1023L;
	  aref_new_value = DFLOAT_ISAREF_1(data_point_time,(SI_Long)0L);
	  DFLOAT_ISASET_1(temp_1,temp,aref_new_value);
      }
      else if (FLOATP(data_point_time)) {
	  temp_1 = ISVREF(vector_1,(IFIX(index_to_copy_from) >>  -  - 
		  (SI_Long)10L) + (SI_Long)2L);
	  temp = IFIX(index_to_copy_from) & (SI_Long)1023L;
	  aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(data_point_time);
	  DFLOAT_ISASET_1(temp_1,temp,aref_new_value);
      }
      else {
	  new_managed_array = allocate_managed_array(1,ISVREF(vector_1,
		  (SI_Long)1L));
	  if ( !TRUEP(ISVREF(ring_buffer,(SI_Long)3L))) {
	      element_index = ISVREF(ring_buffer,(SI_Long)2L);
	    next_loop_2:
	      if (FIXNUM_LE(ISVREF(new_managed_array,(SI_Long)1L),
		      Maximum_in_place_array_size)) {
		  temp_1 = FIXNUM_ADD(element_index,
			  Managed_array_index_offset);
		  amf_available_array_cons_qm = 
			  ISVREF(Vector_of_simple_float_array_pools,
			  (SI_Long)1L);
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
		  aref_new_value = DFLOAT_ISAREF_1(ISVREF(vector_1,
			  (IFIX(element_index) >>  -  - (SI_Long)10L) + 
			  (SI_Long)2L),IFIX(element_index) & (SI_Long)1023L);
		  DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		  SVREF(new_managed_array,temp_1) = new_float;
	      }
	      else {
		  temp_1 = ISVREF(new_managed_array,(IFIX(element_index) 
			  >>  -  - (SI_Long)10L) + (SI_Long)2L);
		  temp = IFIX(element_index) & (SI_Long)1023L;
		  amf_available_array_cons_qm = 
			  ISVREF(Vector_of_simple_float_array_pools,
			  (SI_Long)1L);
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
		  aref_new_value = DFLOAT_ISAREF_1(ISVREF(vector_1,
			  (IFIX(element_index) >>  -  - (SI_Long)10L) + 
			  (SI_Long)2L),IFIX(element_index) & (SI_Long)1023L);
		  DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		  ISVREF(temp_1,temp) = new_float;
	      }
	      if (FIXNUM_EQ(element_index,ISVREF(ring_buffer,(SI_Long)1L)))
		  goto end_loop_2;
	      element_index = FIXNUM_EQ(element_index,
		      FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ? 
		      FIX((SI_Long)0L) : FIXNUM_ADD1(element_index);
	      goto next_loop_2;
	    end_loop_2:;
	  }
	  reclaim_managed_float_array(vector_1);
	  SVREF(ring_buffer,FIX((SI_Long)7L)) = new_managed_array;
	  temp_1 = ISVREF(ring_buffer,(SI_Long)7L);
	  store_managed_number_or_value_arg = data_point_time;
	  temp_3 = 
		  store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp_1,
		  (SI_Long)1L),Maximum_in_place_array_size) ? 
		  ISVREF(temp_1,IFIX(FIXNUM_ADD(index_to_copy_from,
		  Managed_array_index_offset))) : ISVREF(ISVREF(temp_1,
		  (IFIX(index_to_copy_from) >>  -  - (SI_Long)10L) + 
		  (SI_Long)2L),IFIX(index_to_copy_from) & (SI_Long)1023L),
		  store_managed_number_or_value_arg);
	  if (FIXNUM_LE(ISVREF(temp_1,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      temp_2 = FIXNUM_ADD(index_to_copy_from,
		      Managed_array_index_offset);
	      SVREF(temp_1,temp_2) = temp_3;
	  }
	  else {
	      temp_1 = ISVREF(temp_1,(IFIX(index_to_copy_from) >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L);
	      temp = IFIX(index_to_copy_from) & (SI_Long)1023L;
	      ISVREF(temp_1,temp) = temp_3;
	  }
      }
      result = VALUES_1(Qnil);
    end_1:;
    POP_SPECIAL();
    return result;
}

/* INSERT-OLD-DATA-POINT-IF-APPROPRIATE */
Object insert_old_data_point_if_appropriate(ring_buffer,index_to_copy_to,
	    index_to_copy_from,data_point_value,data_point_time)
    Object ring_buffer, index_to_copy_to, index_to_copy_from, data_point_value;
    Object data_point_time;
{
    Object vector_1, managed_number_or_value, temp, temp_1;
    Object previous_data_point_value, previous_data_point_time, temp_2;
    Object store_managed_number_or_value_arg, temp_3, new_managed_array;
    Object element_index, amf_available_array_cons_qm, amf_array, temp_5;
    Object amf_result, new_float;
    SI_Long temp_4;
    double aref_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(148,71);
    PUSH_SPECIAL_WITH_SYMBOL(Data_point_value,Qdata_point_value,data_point_value,
	    0);
      vector_1 = ISVREF(ring_buffer,(SI_Long)6L);
      if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
	      Managed_array_unique_marker)) {
	  managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		  Maximum_in_place_array_size) ? ISVREF(vector_1,
		  IFIX(FIXNUM_ADD(index_to_copy_from,
		  Managed_array_index_offset))) : ISVREF(ISVREF(vector_1,
		  (IFIX(index_to_copy_from) >>  -  - (SI_Long)10L) + 
		  (SI_Long)2L),IFIX(index_to_copy_from) & (SI_Long)1023L);
	  if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		  (SI_Long)0L && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		  == (SI_Long)1L)
	      temp = 
		      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		      (SI_Long)0L));
	  else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		  (SI_Long)0L && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		  == (SI_Long)1L)
	      temp = aref1(managed_number_or_value,FIX((SI_Long)0L));
	  else if (text_string_p(managed_number_or_value))
	      temp = copy_text_string(managed_number_or_value);
	  else
	      temp = managed_number_or_value;
      }
      else
	  temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
		  (IFIX(index_to_copy_from) >>  -  - (SI_Long)10L) + 
		  (SI_Long)2L),IFIX(index_to_copy_from) & (SI_Long)1023L));
      vector_1 = ISVREF(ring_buffer,(SI_Long)7L);
      if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
	      Managed_array_unique_marker)) {
	  managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		  Maximum_in_place_array_size) ? ISVREF(vector_1,
		  IFIX(FIXNUM_ADD(index_to_copy_from,
		  Managed_array_index_offset))) : ISVREF(ISVREF(vector_1,
		  (IFIX(index_to_copy_from) >>  -  - (SI_Long)10L) + 
		  (SI_Long)2L),IFIX(index_to_copy_from) & (SI_Long)1023L);
	  if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		  (SI_Long)0L && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		  == (SI_Long)1L)
	      temp_1 = 
		      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		      (SI_Long)0L));
	  else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		  (SI_Long)0L && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		  == (SI_Long)1L)
	      temp_1 = aref1(managed_number_or_value,FIX((SI_Long)0L));
	  else if (text_string_p(managed_number_or_value))
	      temp_1 = copy_text_string(managed_number_or_value);
	  else
	      temp_1 = managed_number_or_value;
      }
      else
	  temp_1 = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
		  (IFIX(index_to_copy_from) >>  -  - (SI_Long)10L) + 
		  (SI_Long)2L),IFIX(index_to_copy_from) & (SI_Long)1023L));
      result = VALUES_2(temp,temp_1);
      MVS_2(result,previous_data_point_value,previous_data_point_time);
      if (NUM_GT(data_point_time,previous_data_point_time)) {
	  temp_2 = FIXNUM_ADD1(ISVREF(ring_buffer,(SI_Long)5L));
	  SVREF(ring_buffer,FIX((SI_Long)5L)) = temp_2;
	  vector_1 = ISVREF(ring_buffer,(SI_Long)6L);
	  if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
		  Managed_array_unique_marker)) {
	      store_managed_number_or_value_arg = Data_point_value;
	      temp_3 = 
		      store_managed_number_or_value_function(FIXNUM_LE(ISVREF(vector_1,
		      (SI_Long)1L),Maximum_in_place_array_size) ? 
		      ISVREF(vector_1,IFIX(FIXNUM_ADD(index_to_copy_to,
		      Managed_array_index_offset))) : 
		      ISVREF(ISVREF(vector_1,(IFIX(index_to_copy_to) >>  - 
		       - (SI_Long)10L) + (SI_Long)2L),
		      IFIX(index_to_copy_to) & (SI_Long)1023L),
		      store_managed_number_or_value_arg);
	      if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		      Maximum_in_place_array_size)) {
		  temp_2 = FIXNUM_ADD(index_to_copy_to,
			  Managed_array_index_offset);
		  SVREF(vector_1,temp_2) = temp_3;
	      }
	      else {
		  temp_2 = ISVREF(vector_1,(IFIX(index_to_copy_to) >>  -  
			  - (SI_Long)10L) + (SI_Long)2L);
		  temp_4 = IFIX(index_to_copy_to) & (SI_Long)1023L;
		  ISVREF(temp_2,temp_4) = temp_3;
	      }
	  }
	  else if (INLINE_DOUBLE_FLOAT_VECTOR_P(Data_point_value) != 
		  (SI_Long)0L && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Data_point_value)) == 
		  (SI_Long)1L) {
	      temp_2 = ISVREF(vector_1,(IFIX(index_to_copy_to) >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L);
	      temp_4 = IFIX(index_to_copy_to) & (SI_Long)1023L;
	      aref_new_value = DFLOAT_ISAREF_1(Data_point_value,(SI_Long)0L);
	      DFLOAT_ISASET_1(temp_2,temp_4,aref_new_value);
	  }
	  else if (FLOATP(Data_point_value)) {
	      temp_2 = ISVREF(vector_1,(IFIX(index_to_copy_to) >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L);
	      temp_4 = IFIX(index_to_copy_to) & (SI_Long)1023L;
	      aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(Data_point_value);
	      DFLOAT_ISASET_1(temp_2,temp_4,aref_new_value);
	  }
	  else {
	      new_managed_array = allocate_managed_array(1,ISVREF(vector_1,
		      (SI_Long)1L));
	      if ( !TRUEP(ISVREF(ring_buffer,(SI_Long)3L))) {
		  element_index = ISVREF(ring_buffer,(SI_Long)2L);
		next_loop:
		  if (FIXNUM_LE(ISVREF(new_managed_array,(SI_Long)1L),
			  Maximum_in_place_array_size)) {
		      temp_2 = FIXNUM_ADD(element_index,
			      Managed_array_index_offset);
		      amf_available_array_cons_qm = 
			      ISVREF(Vector_of_simple_float_array_pools,
			      (SI_Long)1L);
		      if (amf_available_array_cons_qm) {
			  amf_array = M_CAR(amf_available_array_cons_qm);
			  temp_3 = Vector_of_simple_float_array_pools;
			  temp_5 = M_CDR(amf_available_array_cons_qm);
			  SVREF(temp_3,FIX((SI_Long)1L)) = temp_5;
			  inline_note_reclaim_cons(amf_available_array_cons_qm,
				  Qfloat_array);
			  if (ISVREF(Available_float_array_conses_tail_vector,
				  IFIX(Current_thread_index))) {
			      temp_3 = 
				      ISVREF(Available_float_array_conses_tail_vector,
				      IFIX(Current_thread_index));
			      M_CDR(temp_3) = amf_available_array_cons_qm;
			      temp_3 = 
				      Available_float_array_conses_tail_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_3,temp_5) = 
				      amf_available_array_cons_qm;
			  }
			  else {
			      temp_3 = Available_float_array_conses_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_3,temp_5) = 
				      amf_available_array_cons_qm;
			      temp_3 = 
				      Available_float_array_conses_tail_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_3,temp_5) = 
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
			  amf_result = generate_float_vector(FIX((SI_Long)1L));
		      }
		      new_float = amf_result;
		      aref_new_value = DFLOAT_ISAREF_1(ISVREF(vector_1,
			      (IFIX(element_index) >>  -  - (SI_Long)10L) 
			      + (SI_Long)2L),IFIX(element_index) & 
			      (SI_Long)1023L);
		      DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		      SVREF(new_managed_array,temp_2) = new_float;
		  }
		  else {
		      temp_2 = ISVREF(new_managed_array,
			      (IFIX(element_index) >>  -  - (SI_Long)10L) 
			      + (SI_Long)2L);
		      temp_4 = IFIX(element_index) & (SI_Long)1023L;
		      amf_available_array_cons_qm = 
			      ISVREF(Vector_of_simple_float_array_pools,
			      (SI_Long)1L);
		      if (amf_available_array_cons_qm) {
			  amf_array = M_CAR(amf_available_array_cons_qm);
			  temp_3 = Vector_of_simple_float_array_pools;
			  temp_5 = M_CDR(amf_available_array_cons_qm);
			  SVREF(temp_3,FIX((SI_Long)1L)) = temp_5;
			  inline_note_reclaim_cons(amf_available_array_cons_qm,
				  Qfloat_array);
			  if (ISVREF(Available_float_array_conses_tail_vector,
				  IFIX(Current_thread_index))) {
			      temp_3 = 
				      ISVREF(Available_float_array_conses_tail_vector,
				      IFIX(Current_thread_index));
			      M_CDR(temp_3) = amf_available_array_cons_qm;
			      temp_3 = 
				      Available_float_array_conses_tail_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_3,temp_5) = 
				      amf_available_array_cons_qm;
			  }
			  else {
			      temp_3 = Available_float_array_conses_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_3,temp_5) = 
				      amf_available_array_cons_qm;
			      temp_3 = 
				      Available_float_array_conses_tail_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_3,temp_5) = 
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
			  amf_result = generate_float_vector(FIX((SI_Long)1L));
		      }
		      new_float = amf_result;
		      aref_new_value = DFLOAT_ISAREF_1(ISVREF(vector_1,
			      (IFIX(element_index) >>  -  - (SI_Long)10L) 
			      + (SI_Long)2L),IFIX(element_index) & 
			      (SI_Long)1023L);
		      DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		      ISVREF(temp_2,temp_4) = new_float;
		  }
		  if (FIXNUM_EQ(element_index,ISVREF(ring_buffer,(SI_Long)1L)))
		      goto end_loop;
		  element_index = FIXNUM_EQ(element_index,
			  FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ? 
			  FIX((SI_Long)0L) : FIXNUM_ADD1(element_index);
		  goto next_loop;
		end_loop:;
	      }
	      reclaim_managed_float_array(vector_1);
	      SVREF(ring_buffer,FIX((SI_Long)6L)) = new_managed_array;
	      temp_2 = ISVREF(ring_buffer,(SI_Long)6L);
	      store_managed_number_or_value_arg = Data_point_value;
	      temp_5 = 
		      store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp_2,
		      (SI_Long)1L),Maximum_in_place_array_size) ? 
		      ISVREF(temp_2,IFIX(FIXNUM_ADD(index_to_copy_to,
		      Managed_array_index_offset))) : ISVREF(ISVREF(temp_2,
		      (IFIX(index_to_copy_to) >>  -  - (SI_Long)10L) + 
		      (SI_Long)2L),IFIX(index_to_copy_to) & 
		      (SI_Long)1023L),store_managed_number_or_value_arg);
	      if (FIXNUM_LE(ISVREF(temp_2,(SI_Long)1L),
		      Maximum_in_place_array_size)) {
		  temp_3 = FIXNUM_ADD(index_to_copy_to,
			  Managed_array_index_offset);
		  SVREF(temp_2,temp_3) = temp_5;
	      }
	      else {
		  temp_2 = ISVREF(temp_2,(IFIX(index_to_copy_to) >>  -  - 
			  (SI_Long)10L) + (SI_Long)2L);
		  temp_4 = IFIX(index_to_copy_to) & (SI_Long)1023L;
		  ISVREF(temp_2,temp_4) = temp_5;
	      }
	  }
	  vector_1 = ISVREF(ring_buffer,(SI_Long)7L);
	  if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
		  Managed_array_unique_marker)) {
	      store_managed_number_or_value_arg = data_point_time;
	      temp_3 = 
		      store_managed_number_or_value_function(FIXNUM_LE(ISVREF(vector_1,
		      (SI_Long)1L),Maximum_in_place_array_size) ? 
		      ISVREF(vector_1,IFIX(FIXNUM_ADD(index_to_copy_to,
		      Managed_array_index_offset))) : 
		      ISVREF(ISVREF(vector_1,(IFIX(index_to_copy_to) >>  - 
		       - (SI_Long)10L) + (SI_Long)2L),
		      IFIX(index_to_copy_to) & (SI_Long)1023L),
		      store_managed_number_or_value_arg);
	      if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		      Maximum_in_place_array_size)) {
		  temp_2 = FIXNUM_ADD(index_to_copy_to,
			  Managed_array_index_offset);
		  SVREF(vector_1,temp_2) = temp_3;
	      }
	      else {
		  temp_2 = ISVREF(vector_1,(IFIX(index_to_copy_to) >>  -  
			  - (SI_Long)10L) + (SI_Long)2L);
		  temp_4 = IFIX(index_to_copy_to) & (SI_Long)1023L;
		  ISVREF(temp_2,temp_4) = temp_3;
	      }
	  }
	  else if (INLINE_DOUBLE_FLOAT_VECTOR_P(data_point_time) != 
		  (SI_Long)0L && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(data_point_time)) == 
		  (SI_Long)1L) {
	      temp_2 = ISVREF(vector_1,(IFIX(index_to_copy_to) >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L);
	      temp_4 = IFIX(index_to_copy_to) & (SI_Long)1023L;
	      aref_new_value = DFLOAT_ISAREF_1(data_point_time,(SI_Long)0L);
	      DFLOAT_ISASET_1(temp_2,temp_4,aref_new_value);
	  }
	  else if (FLOATP(data_point_time)) {
	      temp_2 = ISVREF(vector_1,(IFIX(index_to_copy_to) >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L);
	      temp_4 = IFIX(index_to_copy_to) & (SI_Long)1023L;
	      aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(data_point_time);
	      DFLOAT_ISASET_1(temp_2,temp_4,aref_new_value);
	  }
	  else {
	      new_managed_array = allocate_managed_array(1,ISVREF(vector_1,
		      (SI_Long)1L));
	      if ( !TRUEP(ISVREF(ring_buffer,(SI_Long)3L))) {
		  element_index = ISVREF(ring_buffer,(SI_Long)2L);
		next_loop_1:
		  if (FIXNUM_LE(ISVREF(new_managed_array,(SI_Long)1L),
			  Maximum_in_place_array_size)) {
		      temp_2 = FIXNUM_ADD(element_index,
			      Managed_array_index_offset);
		      amf_available_array_cons_qm = 
			      ISVREF(Vector_of_simple_float_array_pools,
			      (SI_Long)1L);
		      if (amf_available_array_cons_qm) {
			  amf_array = M_CAR(amf_available_array_cons_qm);
			  temp_3 = Vector_of_simple_float_array_pools;
			  temp_5 = M_CDR(amf_available_array_cons_qm);
			  SVREF(temp_3,FIX((SI_Long)1L)) = temp_5;
			  inline_note_reclaim_cons(amf_available_array_cons_qm,
				  Qfloat_array);
			  if (ISVREF(Available_float_array_conses_tail_vector,
				  IFIX(Current_thread_index))) {
			      temp_3 = 
				      ISVREF(Available_float_array_conses_tail_vector,
				      IFIX(Current_thread_index));
			      M_CDR(temp_3) = amf_available_array_cons_qm;
			      temp_3 = 
				      Available_float_array_conses_tail_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_3,temp_5) = 
				      amf_available_array_cons_qm;
			  }
			  else {
			      temp_3 = Available_float_array_conses_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_3,temp_5) = 
				      amf_available_array_cons_qm;
			      temp_3 = 
				      Available_float_array_conses_tail_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_3,temp_5) = 
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
			  amf_result = generate_float_vector(FIX((SI_Long)1L));
		      }
		      new_float = amf_result;
		      aref_new_value = DFLOAT_ISAREF_1(ISVREF(vector_1,
			      (IFIX(element_index) >>  -  - (SI_Long)10L) 
			      + (SI_Long)2L),IFIX(element_index) & 
			      (SI_Long)1023L);
		      DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		      SVREF(new_managed_array,temp_2) = new_float;
		  }
		  else {
		      temp_2 = ISVREF(new_managed_array,
			      (IFIX(element_index) >>  -  - (SI_Long)10L) 
			      + (SI_Long)2L);
		      temp_4 = IFIX(element_index) & (SI_Long)1023L;
		      amf_available_array_cons_qm = 
			      ISVREF(Vector_of_simple_float_array_pools,
			      (SI_Long)1L);
		      if (amf_available_array_cons_qm) {
			  amf_array = M_CAR(amf_available_array_cons_qm);
			  temp_3 = Vector_of_simple_float_array_pools;
			  temp_5 = M_CDR(amf_available_array_cons_qm);
			  SVREF(temp_3,FIX((SI_Long)1L)) = temp_5;
			  inline_note_reclaim_cons(amf_available_array_cons_qm,
				  Qfloat_array);
			  if (ISVREF(Available_float_array_conses_tail_vector,
				  IFIX(Current_thread_index))) {
			      temp_3 = 
				      ISVREF(Available_float_array_conses_tail_vector,
				      IFIX(Current_thread_index));
			      M_CDR(temp_3) = amf_available_array_cons_qm;
			      temp_3 = 
				      Available_float_array_conses_tail_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_3,temp_5) = 
				      amf_available_array_cons_qm;
			  }
			  else {
			      temp_3 = Available_float_array_conses_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_3,temp_5) = 
				      amf_available_array_cons_qm;
			      temp_3 = 
				      Available_float_array_conses_tail_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_3,temp_5) = 
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
			  amf_result = generate_float_vector(FIX((SI_Long)1L));
		      }
		      new_float = amf_result;
		      aref_new_value = DFLOAT_ISAREF_1(ISVREF(vector_1,
			      (IFIX(element_index) >>  -  - (SI_Long)10L) 
			      + (SI_Long)2L),IFIX(element_index) & 
			      (SI_Long)1023L);
		      DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		      ISVREF(temp_2,temp_4) = new_float;
		  }
		  if (FIXNUM_EQ(element_index,ISVREF(ring_buffer,(SI_Long)1L)))
		      goto end_loop_1;
		  element_index = FIXNUM_EQ(element_index,
			  FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ? 
			  FIX((SI_Long)0L) : FIXNUM_ADD1(element_index);
		  goto next_loop_1;
		end_loop_1:;
	      }
	      reclaim_managed_float_array(vector_1);
	      SVREF(ring_buffer,FIX((SI_Long)7L)) = new_managed_array;
	      temp_2 = ISVREF(ring_buffer,(SI_Long)7L);
	      store_managed_number_or_value_arg = data_point_time;
	      temp_5 = 
		      store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp_2,
		      (SI_Long)1L),Maximum_in_place_array_size) ? 
		      ISVREF(temp_2,IFIX(FIXNUM_ADD(index_to_copy_to,
		      Managed_array_index_offset))) : ISVREF(ISVREF(temp_2,
		      (IFIX(index_to_copy_to) >>  -  - (SI_Long)10L) + 
		      (SI_Long)2L),IFIX(index_to_copy_to) & 
		      (SI_Long)1023L),store_managed_number_or_value_arg);
	      if (FIXNUM_LE(ISVREF(temp_2,(SI_Long)1L),
		      Maximum_in_place_array_size)) {
		  temp_3 = FIXNUM_ADD(index_to_copy_to,
			  Managed_array_index_offset);
		  SVREF(temp_2,temp_3) = temp_5;
	      }
	      else {
		  temp_2 = ISVREF(temp_2,(IFIX(index_to_copy_to) >>  -  - 
			  (SI_Long)10L) + (SI_Long)2L);
		  temp_4 = IFIX(index_to_copy_to) & (SI_Long)1023L;
		  ISVREF(temp_2,temp_4) = temp_5;
	      }
	  }
	  if (text_string_p(previous_data_point_value))
	      reclaim_text_string(previous_data_point_value);
	  result = VALUES_1(T);
      }
      else {
	  temp_2 = FIXNUM_ADD1(ISVREF(ring_buffer,(SI_Long)5L));
	  SVREF(ring_buffer,FIX((SI_Long)5L)) = temp_2;
	  vector_1 = ISVREF(ring_buffer,(SI_Long)6L);
	  if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
		  Managed_array_unique_marker)) {
	      store_managed_number_or_value_arg = previous_data_point_value;
	      temp_3 = 
		      store_managed_number_or_value_function(FIXNUM_LE(ISVREF(vector_1,
		      (SI_Long)1L),Maximum_in_place_array_size) ? 
		      ISVREF(vector_1,IFIX(FIXNUM_ADD(index_to_copy_to,
		      Managed_array_index_offset))) : 
		      ISVREF(ISVREF(vector_1,(IFIX(index_to_copy_to) >>  - 
		       - (SI_Long)10L) + (SI_Long)2L),
		      IFIX(index_to_copy_to) & (SI_Long)1023L),
		      store_managed_number_or_value_arg);
	      if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		      Maximum_in_place_array_size)) {
		  temp_2 = FIXNUM_ADD(index_to_copy_to,
			  Managed_array_index_offset);
		  SVREF(vector_1,temp_2) = temp_3;
	      }
	      else {
		  temp_2 = ISVREF(vector_1,(IFIX(index_to_copy_to) >>  -  
			  - (SI_Long)10L) + (SI_Long)2L);
		  temp_4 = IFIX(index_to_copy_to) & (SI_Long)1023L;
		  ISVREF(temp_2,temp_4) = temp_3;
	      }
	  }
	  else if (INLINE_DOUBLE_FLOAT_VECTOR_P(previous_data_point_value) 
		  != (SI_Long)0L && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(previous_data_point_value)) 
		  == (SI_Long)1L) {
	      temp_2 = ISVREF(vector_1,(IFIX(index_to_copy_to) >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L);
	      temp_4 = IFIX(index_to_copy_to) & (SI_Long)1023L;
	      aref_new_value = DFLOAT_ISAREF_1(previous_data_point_value,
		      (SI_Long)0L);
	      DFLOAT_ISASET_1(temp_2,temp_4,aref_new_value);
	  }
	  else if (FLOATP(previous_data_point_value)) {
	      temp_2 = ISVREF(vector_1,(IFIX(index_to_copy_to) >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L);
	      temp_4 = IFIX(index_to_copy_to) & (SI_Long)1023L;
	      aref_new_value = 
		      DOUBLE_FLOAT_TO_DOUBLE(previous_data_point_value);
	      DFLOAT_ISASET_1(temp_2,temp_4,aref_new_value);
	  }
	  else {
	      new_managed_array = allocate_managed_array(1,ISVREF(vector_1,
		      (SI_Long)1L));
	      if ( !TRUEP(ISVREF(ring_buffer,(SI_Long)3L))) {
		  element_index = ISVREF(ring_buffer,(SI_Long)2L);
		next_loop_2:
		  if (FIXNUM_LE(ISVREF(new_managed_array,(SI_Long)1L),
			  Maximum_in_place_array_size)) {
		      temp_2 = FIXNUM_ADD(element_index,
			      Managed_array_index_offset);
		      amf_available_array_cons_qm = 
			      ISVREF(Vector_of_simple_float_array_pools,
			      (SI_Long)1L);
		      if (amf_available_array_cons_qm) {
			  amf_array = M_CAR(amf_available_array_cons_qm);
			  temp_3 = Vector_of_simple_float_array_pools;
			  temp_5 = M_CDR(amf_available_array_cons_qm);
			  SVREF(temp_3,FIX((SI_Long)1L)) = temp_5;
			  inline_note_reclaim_cons(amf_available_array_cons_qm,
				  Qfloat_array);
			  if (ISVREF(Available_float_array_conses_tail_vector,
				  IFIX(Current_thread_index))) {
			      temp_3 = 
				      ISVREF(Available_float_array_conses_tail_vector,
				      IFIX(Current_thread_index));
			      M_CDR(temp_3) = amf_available_array_cons_qm;
			      temp_3 = 
				      Available_float_array_conses_tail_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_3,temp_5) = 
				      amf_available_array_cons_qm;
			  }
			  else {
			      temp_3 = Available_float_array_conses_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_3,temp_5) = 
				      amf_available_array_cons_qm;
			      temp_3 = 
				      Available_float_array_conses_tail_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_3,temp_5) = 
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
			  amf_result = generate_float_vector(FIX((SI_Long)1L));
		      }
		      new_float = amf_result;
		      aref_new_value = DFLOAT_ISAREF_1(ISVREF(vector_1,
			      (IFIX(element_index) >>  -  - (SI_Long)10L) 
			      + (SI_Long)2L),IFIX(element_index) & 
			      (SI_Long)1023L);
		      DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		      SVREF(new_managed_array,temp_2) = new_float;
		  }
		  else {
		      temp_2 = ISVREF(new_managed_array,
			      (IFIX(element_index) >>  -  - (SI_Long)10L) 
			      + (SI_Long)2L);
		      temp_4 = IFIX(element_index) & (SI_Long)1023L;
		      amf_available_array_cons_qm = 
			      ISVREF(Vector_of_simple_float_array_pools,
			      (SI_Long)1L);
		      if (amf_available_array_cons_qm) {
			  amf_array = M_CAR(amf_available_array_cons_qm);
			  temp_3 = Vector_of_simple_float_array_pools;
			  temp_5 = M_CDR(amf_available_array_cons_qm);
			  SVREF(temp_3,FIX((SI_Long)1L)) = temp_5;
			  inline_note_reclaim_cons(amf_available_array_cons_qm,
				  Qfloat_array);
			  if (ISVREF(Available_float_array_conses_tail_vector,
				  IFIX(Current_thread_index))) {
			      temp_3 = 
				      ISVREF(Available_float_array_conses_tail_vector,
				      IFIX(Current_thread_index));
			      M_CDR(temp_3) = amf_available_array_cons_qm;
			      temp_3 = 
				      Available_float_array_conses_tail_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_3,temp_5) = 
				      amf_available_array_cons_qm;
			  }
			  else {
			      temp_3 = Available_float_array_conses_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_3,temp_5) = 
				      amf_available_array_cons_qm;
			      temp_3 = 
				      Available_float_array_conses_tail_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_3,temp_5) = 
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
			  amf_result = generate_float_vector(FIX((SI_Long)1L));
		      }
		      new_float = amf_result;
		      aref_new_value = DFLOAT_ISAREF_1(ISVREF(vector_1,
			      (IFIX(element_index) >>  -  - (SI_Long)10L) 
			      + (SI_Long)2L),IFIX(element_index) & 
			      (SI_Long)1023L);
		      DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		      ISVREF(temp_2,temp_4) = new_float;
		  }
		  if (FIXNUM_EQ(element_index,ISVREF(ring_buffer,(SI_Long)1L)))
		      goto end_loop_2;
		  element_index = FIXNUM_EQ(element_index,
			  FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ? 
			  FIX((SI_Long)0L) : FIXNUM_ADD1(element_index);
		  goto next_loop_2;
		end_loop_2:;
	      }
	      reclaim_managed_float_array(vector_1);
	      SVREF(ring_buffer,FIX((SI_Long)6L)) = new_managed_array;
	      temp_2 = ISVREF(ring_buffer,(SI_Long)6L);
	      store_managed_number_or_value_arg = previous_data_point_value;
	      temp_5 = 
		      store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp_2,
		      (SI_Long)1L),Maximum_in_place_array_size) ? 
		      ISVREF(temp_2,IFIX(FIXNUM_ADD(index_to_copy_to,
		      Managed_array_index_offset))) : ISVREF(ISVREF(temp_2,
		      (IFIX(index_to_copy_to) >>  -  - (SI_Long)10L) + 
		      (SI_Long)2L),IFIX(index_to_copy_to) & 
		      (SI_Long)1023L),store_managed_number_or_value_arg);
	      if (FIXNUM_LE(ISVREF(temp_2,(SI_Long)1L),
		      Maximum_in_place_array_size)) {
		  temp_3 = FIXNUM_ADD(index_to_copy_to,
			  Managed_array_index_offset);
		  SVREF(temp_2,temp_3) = temp_5;
	      }
	      else {
		  temp_2 = ISVREF(temp_2,(IFIX(index_to_copy_to) >>  -  - 
			  (SI_Long)10L) + (SI_Long)2L);
		  temp_4 = IFIX(index_to_copy_to) & (SI_Long)1023L;
		  ISVREF(temp_2,temp_4) = temp_5;
	      }
	  }
	  vector_1 = ISVREF(ring_buffer,(SI_Long)7L);
	  if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
		  Managed_array_unique_marker)) {
	      store_managed_number_or_value_arg = previous_data_point_time;
	      temp_3 = 
		      store_managed_number_or_value_function(FIXNUM_LE(ISVREF(vector_1,
		      (SI_Long)1L),Maximum_in_place_array_size) ? 
		      ISVREF(vector_1,IFIX(FIXNUM_ADD(index_to_copy_to,
		      Managed_array_index_offset))) : 
		      ISVREF(ISVREF(vector_1,(IFIX(index_to_copy_to) >>  - 
		       - (SI_Long)10L) + (SI_Long)2L),
		      IFIX(index_to_copy_to) & (SI_Long)1023L),
		      store_managed_number_or_value_arg);
	      if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		      Maximum_in_place_array_size)) {
		  temp_2 = FIXNUM_ADD(index_to_copy_to,
			  Managed_array_index_offset);
		  SVREF(vector_1,temp_2) = temp_3;
	      }
	      else {
		  temp_2 = ISVREF(vector_1,(IFIX(index_to_copy_to) >>  -  
			  - (SI_Long)10L) + (SI_Long)2L);
		  temp_4 = IFIX(index_to_copy_to) & (SI_Long)1023L;
		  ISVREF(temp_2,temp_4) = temp_3;
	      }
	  }
	  else if (INLINE_DOUBLE_FLOAT_VECTOR_P(previous_data_point_time) 
		  != (SI_Long)0L && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(previous_data_point_time)) 
		  == (SI_Long)1L) {
	      temp_2 = ISVREF(vector_1,(IFIX(index_to_copy_to) >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L);
	      temp_4 = IFIX(index_to_copy_to) & (SI_Long)1023L;
	      aref_new_value = DFLOAT_ISAREF_1(previous_data_point_time,
		      (SI_Long)0L);
	      DFLOAT_ISASET_1(temp_2,temp_4,aref_new_value);
	  }
	  else if (FLOATP(previous_data_point_time)) {
	      temp_2 = ISVREF(vector_1,(IFIX(index_to_copy_to) >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L);
	      temp_4 = IFIX(index_to_copy_to) & (SI_Long)1023L;
	      aref_new_value = 
		      DOUBLE_FLOAT_TO_DOUBLE(previous_data_point_time);
	      DFLOAT_ISASET_1(temp_2,temp_4,aref_new_value);
	  }
	  else {
	      new_managed_array = allocate_managed_array(1,ISVREF(vector_1,
		      (SI_Long)1L));
	      if ( !TRUEP(ISVREF(ring_buffer,(SI_Long)3L))) {
		  element_index = ISVREF(ring_buffer,(SI_Long)2L);
		next_loop_3:
		  if (FIXNUM_LE(ISVREF(new_managed_array,(SI_Long)1L),
			  Maximum_in_place_array_size)) {
		      temp_2 = FIXNUM_ADD(element_index,
			      Managed_array_index_offset);
		      amf_available_array_cons_qm = 
			      ISVREF(Vector_of_simple_float_array_pools,
			      (SI_Long)1L);
		      if (amf_available_array_cons_qm) {
			  amf_array = M_CAR(amf_available_array_cons_qm);
			  temp_3 = Vector_of_simple_float_array_pools;
			  temp_5 = M_CDR(amf_available_array_cons_qm);
			  SVREF(temp_3,FIX((SI_Long)1L)) = temp_5;
			  inline_note_reclaim_cons(amf_available_array_cons_qm,
				  Qfloat_array);
			  if (ISVREF(Available_float_array_conses_tail_vector,
				  IFIX(Current_thread_index))) {
			      temp_3 = 
				      ISVREF(Available_float_array_conses_tail_vector,
				      IFIX(Current_thread_index));
			      M_CDR(temp_3) = amf_available_array_cons_qm;
			      temp_3 = 
				      Available_float_array_conses_tail_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_3,temp_5) = 
				      amf_available_array_cons_qm;
			  }
			  else {
			      temp_3 = Available_float_array_conses_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_3,temp_5) = 
				      amf_available_array_cons_qm;
			      temp_3 = 
				      Available_float_array_conses_tail_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_3,temp_5) = 
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
			  amf_result = generate_float_vector(FIX((SI_Long)1L));
		      }
		      new_float = amf_result;
		      aref_new_value = DFLOAT_ISAREF_1(ISVREF(vector_1,
			      (IFIX(element_index) >>  -  - (SI_Long)10L) 
			      + (SI_Long)2L),IFIX(element_index) & 
			      (SI_Long)1023L);
		      DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		      SVREF(new_managed_array,temp_2) = new_float;
		  }
		  else {
		      temp_2 = ISVREF(new_managed_array,
			      (IFIX(element_index) >>  -  - (SI_Long)10L) 
			      + (SI_Long)2L);
		      temp_4 = IFIX(element_index) & (SI_Long)1023L;
		      amf_available_array_cons_qm = 
			      ISVREF(Vector_of_simple_float_array_pools,
			      (SI_Long)1L);
		      if (amf_available_array_cons_qm) {
			  amf_array = M_CAR(amf_available_array_cons_qm);
			  temp_3 = Vector_of_simple_float_array_pools;
			  temp_5 = M_CDR(amf_available_array_cons_qm);
			  SVREF(temp_3,FIX((SI_Long)1L)) = temp_5;
			  inline_note_reclaim_cons(amf_available_array_cons_qm,
				  Qfloat_array);
			  if (ISVREF(Available_float_array_conses_tail_vector,
				  IFIX(Current_thread_index))) {
			      temp_3 = 
				      ISVREF(Available_float_array_conses_tail_vector,
				      IFIX(Current_thread_index));
			      M_CDR(temp_3) = amf_available_array_cons_qm;
			      temp_3 = 
				      Available_float_array_conses_tail_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_3,temp_5) = 
				      amf_available_array_cons_qm;
			  }
			  else {
			      temp_3 = Available_float_array_conses_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_3,temp_5) = 
				      amf_available_array_cons_qm;
			      temp_3 = 
				      Available_float_array_conses_tail_vector;
			      temp_5 = Current_thread_index;
			      SVREF(temp_3,temp_5) = 
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
			  amf_result = generate_float_vector(FIX((SI_Long)1L));
		      }
		      new_float = amf_result;
		      aref_new_value = DFLOAT_ISAREF_1(ISVREF(vector_1,
			      (IFIX(element_index) >>  -  - (SI_Long)10L) 
			      + (SI_Long)2L),IFIX(element_index) & 
			      (SI_Long)1023L);
		      DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		      ISVREF(temp_2,temp_4) = new_float;
		  }
		  if (FIXNUM_EQ(element_index,ISVREF(ring_buffer,(SI_Long)1L)))
		      goto end_loop_3;
		  element_index = FIXNUM_EQ(element_index,
			  FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ? 
			  FIX((SI_Long)0L) : FIXNUM_ADD1(element_index);
		  goto next_loop_3;
		end_loop_3:;
	      }
	      reclaim_managed_float_array(vector_1);
	      SVREF(ring_buffer,FIX((SI_Long)7L)) = new_managed_array;
	      temp_2 = ISVREF(ring_buffer,(SI_Long)7L);
	      store_managed_number_or_value_arg = previous_data_point_time;
	      temp_5 = 
		      store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp_2,
		      (SI_Long)1L),Maximum_in_place_array_size) ? 
		      ISVREF(temp_2,IFIX(FIXNUM_ADD(index_to_copy_to,
		      Managed_array_index_offset))) : ISVREF(ISVREF(temp_2,
		      (IFIX(index_to_copy_to) >>  -  - (SI_Long)10L) + 
		      (SI_Long)2L),IFIX(index_to_copy_to) & 
		      (SI_Long)1023L),store_managed_number_or_value_arg);
	      if (FIXNUM_LE(ISVREF(temp_2,(SI_Long)1L),
		      Maximum_in_place_array_size)) {
		  temp_3 = FIXNUM_ADD(index_to_copy_to,
			  Managed_array_index_offset);
		  SVREF(temp_2,temp_3) = temp_5;
	      }
	      else {
		  temp_2 = ISVREF(temp_2,(IFIX(index_to_copy_to) >>  -  - 
			  (SI_Long)10L) + (SI_Long)2L);
		  temp_4 = IFIX(index_to_copy_to) & (SI_Long)1023L;
		  ISVREF(temp_2,temp_4) = temp_5;
	      }
	  }
	  if (text_string_p(previous_data_point_value))
	      reclaim_text_string(previous_data_point_value);
	  result = VALUES_1(Nil);
      }
    POP_SPECIAL();
    return result;
}

/* GET-TOTAL-CASCADED-RING-BUFFER-LENGTH */
Object get_total_cascaded_ring_buffer_length(cascaded_ring_buffer)
    Object cascaded_ring_buffer;
{
    Object ring_buffer, ab_loop_list_, ab_loopvar_, index_1;
    Object oldest_active_element_index_for_ring_buffer, temp;

    x_note_fn_call(148,72);
    ring_buffer = Nil;
    ab_loop_list_ = ISVREF(cascaded_ring_buffer,(SI_Long)4L);
    ab_loopvar_ = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ring_buffer = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    index_1 = ISVREF(ring_buffer,(SI_Long)1L);
    oldest_active_element_index_for_ring_buffer = ISVREF(ring_buffer,
	    (SI_Long)2L);
    ab_loopvar_ = add(FIXNUM_GE(index_1,
	    oldest_active_element_index_for_ring_buffer) ? 
	    FIXNUM_ADD1(FIXNUM_MINUS(index_1,
	    oldest_active_element_index_for_ring_buffer)) : 
	    FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(index_1,ISVREF(ring_buffer,
	    (SI_Long)4L)),oldest_active_element_index_for_ring_buffer)),
	    ab_loopvar_);
    goto next_loop;
  end_loop:
    temp = ab_loopvar_;
    goto end_1;
    temp = Qnil;
  end_1:;
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(FIX((SI_Long)0L));
}

/* EXPAND-HISTORY-RING-BUFFER */
Object expand_history_ring_buffer(value_history_ring_buffer)
    Object value_history_ring_buffer;
{
    Object current_size, oldest_active_element_index, ring_buffer, index_1;
    Object oldest_active_element_index_for_ring_buffer, next_larger_size;
    Object thing, svref_new_value;
    SI_Long ring_buffer_length, svref_new_value_1;

    x_note_fn_call(148,73);
    current_size = ISVREF(value_history_ring_buffer,(SI_Long)4L);
    if (FIXNUM_LT(current_size,Largest_ring_buffer_vector_size)) {
	oldest_active_element_index = ISVREF(value_history_ring_buffer,
		(SI_Long)2L);
	ring_buffer = value_history_ring_buffer;
	index_1 = ISVREF(value_history_ring_buffer,(SI_Long)1L);
	oldest_active_element_index_for_ring_buffer = ISVREF(ring_buffer,
		(SI_Long)2L);
	ring_buffer_length = FIXNUM_GE(index_1,
		oldest_active_element_index_for_ring_buffer) ? 
		IFIX(FIXNUM_ADD1(FIXNUM_MINUS(index_1,
		oldest_active_element_index_for_ring_buffer))) : 
		IFIX(FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(index_1,
		ISVREF(ring_buffer,(SI_Long)4L)),
		oldest_active_element_index_for_ring_buffer)));
	next_larger_size = Nil;
	if (next_larger_size);
	else
	    next_larger_size = 
		    compute_next_larger_size_for_ring_buffer_vectors(current_size);
	thing = ISVREF(value_history_ring_buffer,(SI_Long)6L);
	if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
		Managed_array_unique_marker)) {
	    rotate_managed_array(ISVREF(value_history_ring_buffer,
		    (SI_Long)6L),oldest_active_element_index);
	    svref_new_value = adjust_managed_array(2,
		    ISVREF(value_history_ring_buffer,(SI_Long)6L),
		    next_larger_size);
	    SVREF(value_history_ring_buffer,FIX((SI_Long)6L)) = 
		    svref_new_value;
	}
	else {
	    rotate_managed_float_array(ISVREF(value_history_ring_buffer,
		    (SI_Long)6L),oldest_active_element_index);
	    svref_new_value = adjust_managed_float_array(2,
		    ISVREF(value_history_ring_buffer,(SI_Long)6L),
		    next_larger_size);
	    SVREF(value_history_ring_buffer,FIX((SI_Long)6L)) = 
		    svref_new_value;
	}
	thing = ISVREF(value_history_ring_buffer,(SI_Long)7L);
	if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
		Managed_array_unique_marker)) {
	    rotate_managed_array(ISVREF(value_history_ring_buffer,
		    (SI_Long)7L),oldest_active_element_index);
	    svref_new_value = adjust_managed_array(2,
		    ISVREF(value_history_ring_buffer,(SI_Long)7L),
		    next_larger_size);
	    SVREF(value_history_ring_buffer,FIX((SI_Long)7L)) = 
		    svref_new_value;
	}
	else {
	    rotate_managed_float_array(ISVREF(value_history_ring_buffer,
		    (SI_Long)7L),oldest_active_element_index);
	    svref_new_value = adjust_managed_float_array(2,
		    ISVREF(value_history_ring_buffer,(SI_Long)7L),
		    next_larger_size);
	    SVREF(value_history_ring_buffer,FIX((SI_Long)7L)) = 
		    svref_new_value;
	}
	ISVREF(value_history_ring_buffer,(SI_Long)2L) = FIX((SI_Long)0L);
	svref_new_value_1 = ring_buffer_length - (SI_Long)1L;
	ISVREF(value_history_ring_buffer,(SI_Long)1L) = FIX(svref_new_value_1);
	return VALUES_1(SVREF(value_history_ring_buffer,FIX((SI_Long)4L)) 
		= next_larger_size);
    }
    else
	return VALUES_1(Nil);
}

/* VERIFY-OLDEST-AND-NEWEST-HISTORY-VALUES-WITH-GIVEN-TIME */
Object verify_oldest_and_newest_history_values_with_given_time(buffer_of_stored_values,
	    ring_buffer,maximum_age_of_data_points_qm,time_as_managed_float)
    Object buffer_of_stored_values, ring_buffer, maximum_age_of_data_points_qm;
    Object time_as_managed_float;
{
    Object oldest_active_element_index, vector_1, managed_number_or_value;
    Object temp, oldest_absolute_unix_time_of_datum, oldest_age_of_datum;
    Object newest_active_element_index, newest_absolute_unix_time_of_datum;
    Object newest_age_of_datum, obsolete_old_value_qm;
    char invalid_future_value_qm;
    double time_float_value, base_time_qm;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(148,74);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	time_float_value = DFLOAT_ISAREF_1(time_as_managed_float,(SI_Long)0L);
	base_time_qm = ISVREF(buffer_of_stored_values,(SI_Long)10L) ? 
		DFLOAT_ISAREF_1(ISVREF(buffer_of_stored_values,
		(SI_Long)10L),(SI_Long)0L) : 
		DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L);
	oldest_active_element_index = ISVREF(ring_buffer,(SI_Long)2L);
	vector_1 = ISVREF(ring_buffer,(SI_Long)7L);
	if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
		Managed_array_unique_marker)) {
	    managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(vector_1,
		    IFIX(FIXNUM_ADD(oldest_active_element_index,
		    Managed_array_index_offset))) : ISVREF(ISVREF(vector_1,
		    (IFIX(oldest_active_element_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),
		    IFIX(oldest_active_element_index) & (SI_Long)1023L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		temp = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		temp = aref1(managed_number_or_value,FIX((SI_Long)0L));
	    else if (text_string_p(managed_number_or_value))
		temp = copy_text_string(managed_number_or_value);
	    else
		temp = managed_number_or_value;
	}
	else
	    temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
		    (IFIX(oldest_active_element_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),
		    IFIX(oldest_active_element_index) & (SI_Long)1023L));
	oldest_absolute_unix_time_of_datum = add(temp,
		DOUBLE_TO_DOUBLE_FLOAT(base_time_qm));
	oldest_age_of_datum = 
		minus(DOUBLE_TO_DOUBLE_FLOAT(time_float_value),
		oldest_absolute_unix_time_of_datum);
	newest_active_element_index = ISVREF(ring_buffer,(SI_Long)1L);
	vector_1 = ISVREF(ring_buffer,(SI_Long)7L);
	if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
		Managed_array_unique_marker)) {
	    managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(vector_1,
		    IFIX(FIXNUM_ADD(newest_active_element_index,
		    Managed_array_index_offset))) : ISVREF(ISVREF(vector_1,
		    (IFIX(newest_active_element_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),
		    IFIX(newest_active_element_index) & (SI_Long)1023L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		temp = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		temp = aref1(managed_number_or_value,FIX((SI_Long)0L));
	    else if (text_string_p(managed_number_or_value))
		temp = copy_text_string(managed_number_or_value);
	    else
		temp = managed_number_or_value;
	}
	else
	    temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
		    (IFIX(newest_active_element_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),
		    IFIX(newest_active_element_index) & (SI_Long)1023L));
	newest_absolute_unix_time_of_datum = add(temp,
		DOUBLE_TO_DOUBLE_FLOAT(base_time_qm));
	newest_age_of_datum = 
		minus(DOUBLE_TO_DOUBLE_FLOAT(time_float_value),
		newest_absolute_unix_time_of_datum);
	obsolete_old_value_qm = maximum_age_of_data_points_qm ? 
		(NUM_GT(oldest_age_of_datum,maximum_age_of_data_points_qm) 
		? T : Nil) : Qnil;
	temp = FIX((SI_Long)0L);
	invalid_future_value_qm = NUM_LT(newest_age_of_datum,temp);
	result = VALUES_1( !(obsolete_old_value_qm || 
		invalid_future_value_qm) ? T : Nil);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* REMOVE-HISTORY-VALUES-PAST-MAXIMUM-AGE */
Object remove_history_values_past_maximum_age(cascaded_ring_buffer,
	    ring_buffer,maximum_age_of_data_points,time_as_managed_float)
    Object cascaded_ring_buffer, ring_buffer, maximum_age_of_data_points;
    Object time_as_managed_float;
{
    Object newest_active_element_index, vector_1, managed_number_or_value;
    Object temp, newest_absolute_unix_time_of_datum, newest_age_of_datum;
    Object oldest_active_element_index, absolute_unix_time_of_datum;
    Object age_of_datum, index_1, svref_new_value_1;
    SI_Long inner_loop_count, svref_new_value;
    double current_time_float, base_time_qm;
    XDeclare_area(2);
    XDeclare_frontier(2);
    Object result;

    x_note_fn_call(148,75);
    if ( !TRUEP(maximum_age_of_data_points))
	return VALUES_1(Nil);
    if (PUSH_LOCAL_ALLOCATION(Local_area,1,1)) {
	current_time_float = DFLOAT_ISAREF_1(time_as_managed_float,
		(SI_Long)0L);
	base_time_qm = ISVREF(cascaded_ring_buffer,(SI_Long)10L) ? 
		DFLOAT_ISAREF_1(ISVREF(cascaded_ring_buffer,(SI_Long)10L),
		(SI_Long)0L) : DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L);
	newest_active_element_index = ISVREF(ring_buffer,(SI_Long)1L);
	vector_1 = ISVREF(ring_buffer,(SI_Long)7L);
	if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
		Managed_array_unique_marker)) {
	    managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(vector_1,
		    IFIX(FIXNUM_ADD(newest_active_element_index,
		    Managed_array_index_offset))) : ISVREF(ISVREF(vector_1,
		    (IFIX(newest_active_element_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),
		    IFIX(newest_active_element_index) & (SI_Long)1023L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		temp = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		temp = aref1(managed_number_or_value,FIX((SI_Long)0L));
	    else if (text_string_p(managed_number_or_value))
		temp = copy_text_string(managed_number_or_value);
	    else
		temp = managed_number_or_value;
	}
	else
	    temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
		    (IFIX(newest_active_element_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),
		    IFIX(newest_active_element_index) & (SI_Long)1023L));
	newest_absolute_unix_time_of_datum = add(temp,
		DOUBLE_TO_DOUBLE_FLOAT(base_time_qm));
	newest_age_of_datum = 
		minus(DOUBLE_TO_DOUBLE_FLOAT(current_time_float),
		newest_absolute_unix_time_of_datum);
	oldest_active_element_index = Nil;
	absolute_unix_time_of_datum = Nil;
	age_of_datum = Nil;
	if (NUM_GT(newest_age_of_datum,maximum_age_of_data_points))
	    result = clear_history_buffer_and_not_base_time(cascaded_ring_buffer);
	else {
	  next_loop:
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		inner_loop_count = (SI_Long)0L;
	      next_loop_1:
		if (inner_loop_count >= (SI_Long)100L)
		    goto end_loop;
		oldest_active_element_index = ISVREF(ring_buffer,(SI_Long)2L);
		vector_1 = ISVREF(ring_buffer,(SI_Long)7L);
		if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
			(SI_Long)0L),Managed_array_unique_marker)) {
		    managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    ISVREF(vector_1,
			    IFIX(FIXNUM_ADD(oldest_active_element_index,
			    Managed_array_index_offset))) : 
			    ISVREF(ISVREF(vector_1,
			    (IFIX(oldest_active_element_index) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L),
			    IFIX(oldest_active_element_index) & 
			    (SI_Long)1023L);
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			temp = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			temp = aref1(managed_number_or_value,FIX((SI_Long)0L));
		    else if (text_string_p(managed_number_or_value))
			temp = copy_text_string(managed_number_or_value);
		    else
			temp = managed_number_or_value;
		}
		else
		    temp = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
			    (IFIX(oldest_active_element_index) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L),
			    IFIX(oldest_active_element_index) & 
			    (SI_Long)1023L));
		absolute_unix_time_of_datum = add(temp,
			DOUBLE_TO_DOUBLE_FLOAT(base_time_qm));
		age_of_datum = 
			minus(DOUBLE_TO_DOUBLE_FLOAT(current_time_float),
			absolute_unix_time_of_datum);
		if ( !(NUM_GT(age_of_datum,maximum_age_of_data_points) &&  
			!NUM_EQ(oldest_active_element_index,
			newest_active_element_index)))
		    goto end_loop;
		index_1 = ISVREF(ring_buffer,(SI_Long)2L);
		svref_new_value = FIXNUM_EQ(index_1,
			FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ? 
			(SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
		ISVREF(ring_buffer,(SI_Long)2L) = FIX(svref_new_value);
		svref_new_value_1 = 
			FIXNUM_ADD1(ISVREF(cascaded_ring_buffer,(SI_Long)6L));
		SVREF(cascaded_ring_buffer,FIX((SI_Long)6L)) = 
			svref_new_value_1;
		inner_loop_count = inner_loop_count + (SI_Long)1L;
		goto next_loop_1;
	      end_loop:;
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	    if ( !(NUM_GT(age_of_datum,maximum_age_of_data_points) &&  
		    !NUM_EQ(oldest_active_element_index,
		    newest_active_element_index)))
		goto end_loop_1;
	    goto next_loop;
	  end_loop_1:
	    if (NUM_GT(age_of_datum,maximum_age_of_data_points)) {
		SVREF(ring_buffer,FIX((SI_Long)3L)) = T;
		index_1 = ISVREF(ring_buffer,(SI_Long)2L);
		svref_new_value = FIXNUM_EQ(index_1,
			FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ? 
			(SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
		ISVREF(ring_buffer,(SI_Long)2L) = FIX(svref_new_value);
		index_1 = ISVREF(ring_buffer,(SI_Long)1L);
		svref_new_value = FIXNUM_EQ(index_1,
			FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ? 
			(SI_Long)0L : IFIX(FIXNUM_ADD1(index_1));
		ISVREF(ring_buffer,(SI_Long)1L) = FIX(svref_new_value);
	    }
	    result = VALUES_1(Qnil);
	}
    }
    POP_LOCAL_ALLOCATION(1,1);
    return result;
}

/* REMOVE-FUTURE-HISTORY-VALUES */
Object remove_future_history_values(cascaded_ring_buffer,ring_buffer,
	    time_as_managed_float)
    Object cascaded_ring_buffer, ring_buffer, time_as_managed_float;
{
    Object oldest_active_element_index, vector_1, managed_number_or_value;
    Object temp, oldest_absolute_unix_time_of_datum, oldest_age_of_datum;
    Object newest_active_element_index, absolute_unix_time_of_datum;
    Object age_of_datum, index_1, svref_new_value_1;
    SI_Long inner_loop_count, svref_new_value;
    double current_time_float, base_time_qm;
    XDeclare_area(2);
    XDeclare_frontier(2);
    Object result;

    x_note_fn_call(148,76);
    if (PUSH_LOCAL_ALLOCATION(Local_area,1,1)) {
	current_time_float = DFLOAT_ISAREF_1(time_as_managed_float,
		(SI_Long)0L);
	base_time_qm = ISVREF(cascaded_ring_buffer,(SI_Long)10L) ? 
		DFLOAT_ISAREF_1(ISVREF(cascaded_ring_buffer,(SI_Long)10L),
		(SI_Long)0L) : DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L);
	oldest_active_element_index = ISVREF(ring_buffer,(SI_Long)2L);
	vector_1 = ISVREF(ring_buffer,(SI_Long)7L);
	if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
		Managed_array_unique_marker)) {
	    managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(vector_1,
		    IFIX(FIXNUM_ADD(oldest_active_element_index,
		    Managed_array_index_offset))) : ISVREF(ISVREF(vector_1,
		    (IFIX(oldest_active_element_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),
		    IFIX(oldest_active_element_index) & (SI_Long)1023L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		temp = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		temp = aref1(managed_number_or_value,FIX((SI_Long)0L));
	    else if (text_string_p(managed_number_or_value))
		temp = copy_text_string(managed_number_or_value);
	    else
		temp = managed_number_or_value;
	}
	else
	    temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
		    (IFIX(oldest_active_element_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),
		    IFIX(oldest_active_element_index) & (SI_Long)1023L));
	oldest_absolute_unix_time_of_datum = add(temp,
		DOUBLE_TO_DOUBLE_FLOAT(base_time_qm));
	oldest_age_of_datum = 
		minus(DOUBLE_TO_DOUBLE_FLOAT(current_time_float),
		oldest_absolute_unix_time_of_datum);
	newest_active_element_index = Nil;
	absolute_unix_time_of_datum = Nil;
	age_of_datum = Nil;
	temp = FIX((SI_Long)0L);
	if (NUM_LT(oldest_age_of_datum,temp))
	    result = clear_history_buffer_and_not_base_time(cascaded_ring_buffer);
	else {
	  next_loop:
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		inner_loop_count = (SI_Long)0L;
	      next_loop_1:
		if (inner_loop_count >= (SI_Long)100L)
		    goto end_loop;
		newest_active_element_index = ISVREF(ring_buffer,(SI_Long)1L);
		vector_1 = ISVREF(ring_buffer,(SI_Long)7L);
		if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
			(SI_Long)0L),Managed_array_unique_marker)) {
		    managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    ISVREF(vector_1,
			    IFIX(FIXNUM_ADD(newest_active_element_index,
			    Managed_array_index_offset))) : 
			    ISVREF(ISVREF(vector_1,
			    (IFIX(newest_active_element_index) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L),
			    IFIX(newest_active_element_index) & 
			    (SI_Long)1023L);
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			temp = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			temp = aref1(managed_number_or_value,FIX((SI_Long)0L));
		    else if (text_string_p(managed_number_or_value))
			temp = copy_text_string(managed_number_or_value);
		    else
			temp = managed_number_or_value;
		}
		else
		    temp = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
			    (IFIX(newest_active_element_index) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L),
			    IFIX(newest_active_element_index) & 
			    (SI_Long)1023L));
		absolute_unix_time_of_datum = add(temp,
			DOUBLE_TO_DOUBLE_FLOAT(base_time_qm));
		age_of_datum = 
			minus(DOUBLE_TO_DOUBLE_FLOAT(current_time_float),
			absolute_unix_time_of_datum);
		temp = FIX((SI_Long)0L);
		if ( !(NUM_LT(age_of_datum,temp) &&  
			!NUM_EQ(oldest_active_element_index,
			newest_active_element_index)))
		    goto end_loop;
		index_1 = ISVREF(ring_buffer,(SI_Long)1L);
		svref_new_value = IFIX(index_1) == (SI_Long)0L ? 
			IFIX(FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) 
			: IFIX(FIXNUM_SUB1(index_1));
		ISVREF(ring_buffer,(SI_Long)1L) = FIX(svref_new_value);
		svref_new_value_1 = 
			FIXNUM_ADD1(ISVREF(cascaded_ring_buffer,(SI_Long)6L));
		SVREF(cascaded_ring_buffer,FIX((SI_Long)6L)) = 
			svref_new_value_1;
		inner_loop_count = inner_loop_count + (SI_Long)1L;
		goto next_loop_1;
	      end_loop:;
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	    temp = FIX((SI_Long)0L);
	    if ( !(NUM_LT(age_of_datum,temp) &&  
		    !NUM_EQ(oldest_active_element_index,
		    newest_active_element_index)))
		goto end_loop_1;
	    goto next_loop;
	  end_loop_1:
	    temp = FIX((SI_Long)0L);
	    if (NUM_LT(age_of_datum,temp)) {
		SVREF(ring_buffer,FIX((SI_Long)3L)) = T;
		index_1 = ISVREF(ring_buffer,(SI_Long)2L);
		svref_new_value = IFIX(index_1) == (SI_Long)0L ? 
			IFIX(FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) 
			: IFIX(FIXNUM_SUB1(index_1));
		ISVREF(ring_buffer,(SI_Long)2L) = FIX(svref_new_value);
		index_1 = ISVREF(ring_buffer,(SI_Long)1L);
		svref_new_value = IFIX(index_1) == (SI_Long)0L ? 
			IFIX(FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) 
			: IFIX(FIXNUM_SUB1(index_1));
		ISVREF(ring_buffer,(SI_Long)1L) = FIX(svref_new_value);
	    }
	    result = VALUES_1(Qnil);
	}
    }
    POP_LOCAL_ALLOCATION(1,1);
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Previous_cascaded_ring_buffer_accessed, Qprevious_cascaded_ring_buffer_accessed);

DEFINE_VARIABLE_WITH_SYMBOL(Previous_index_for_ring_buffer, Qprevious_index_for_ring_buffer);

/* RESULTS-OF-ELEMENT-SEARCH */
Object results_of_element_search(cascaded_ring_buffer_qm,ring_buffer,
	    index_1,next_history_time)
    Object cascaded_ring_buffer_qm, ring_buffer, index_1, next_history_time;
{
    Object vector_1, managed_number_or_value, temp, temp_1, history_value;
    Object history_time, base_time;
    double temp_2;
    Object result;

    x_note_fn_call(148,77);
    Previous_cascaded_ring_buffer_accessed = cascaded_ring_buffer_qm;
    Previous_index_for_ring_buffer = index_1;
    vector_1 = ISVREF(ring_buffer,(SI_Long)6L);
    if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
	    Managed_array_unique_marker)) {
	managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(vector_1,
		IFIX(FIXNUM_ADD(index_1,Managed_array_index_offset))) : 
		ISVREF(ISVREF(vector_1,(IFIX(index_1) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),IFIX(index_1) & (SI_Long)1023L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    temp = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    temp = aref1(managed_number_or_value,FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    temp = copy_text_string(managed_number_or_value);
	else
	    temp = managed_number_or_value;
    }
    else
	temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
		(IFIX(index_1) >>  -  - (SI_Long)10L) + (SI_Long)2L),
		IFIX(index_1) & (SI_Long)1023L));
    vector_1 = ISVREF(ring_buffer,(SI_Long)7L);
    if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
	    Managed_array_unique_marker)) {
	managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(vector_1,
		IFIX(FIXNUM_ADD(index_1,Managed_array_index_offset))) : 
		ISVREF(ISVREF(vector_1,(IFIX(index_1) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),IFIX(index_1) & (SI_Long)1023L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    temp_1 = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    temp_1 = aref1(managed_number_or_value,FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    temp_1 = copy_text_string(managed_number_or_value);
	else
	    temp_1 = managed_number_or_value;
    }
    else
	temp_1 = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
		(IFIX(index_1) >>  -  - (SI_Long)10L) + (SI_Long)2L),
		IFIX(index_1) & (SI_Long)1023L));
    result = VALUES_2(temp,temp_1);
    MVS_2(result,history_value,history_time);
    if (cascaded_ring_buffer_qm) {
	base_time = ISVREF(cascaded_ring_buffer_qm,(SI_Long)10L);
	if (FIXNUMP(history_time))
	    temp = DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(history_time) + 
		    DFLOAT_ISAREF_1(base_time,(SI_Long)0L));
	else {
	    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(history_time);
	    temp = DOUBLE_TO_DOUBLE_FLOAT(temp_2 + 
		    DFLOAT_ISAREF_1(base_time,(SI_Long)0L));
	}
    }
    else
	temp = history_time;
    if (cascaded_ring_buffer_qm && next_history_time) {
	base_time = ISVREF(cascaded_ring_buffer_qm,(SI_Long)10L);
	if (FIXNUMP(next_history_time))
	    temp_1 = 
		    DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(next_history_time) 
		    + DFLOAT_ISAREF_1(base_time,(SI_Long)0L));
	else {
	    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(next_history_time);
	    temp_1 = DOUBLE_TO_DOUBLE_FLOAT(temp_2 + 
		    DFLOAT_ISAREF_1(base_time,(SI_Long)0L));
	}
    }
    else
	temp_1 = next_history_time;
    return VALUES_4(history_value,temp,temp_1,index_1);
}

/* GET-HISTORY-ELEMENT-BY-LINEAR-SEARCH */
Object get_history_element_by_linear_search varargs_1(int, n)
{
    Object cascaded_ring_buffer, absolute_history_time;
    Object relative_p, temp, ring_buffer, next_index, next_history_time;
    Object index_1, vector_1, managed_number_or_value;
    double gensymed_symbol, gensymed_symbol_1, history_time;
    Declare_varargs_nonrelocating;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(148,78);
    INIT_ARGS_nonrelocating();
    cascaded_ring_buffer = REQUIRED_ARG_nonrelocating();
    absolute_history_time = REQUIRED_ARG_nonrelocating();
    relative_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	temp = ISVREF(cascaded_ring_buffer,(SI_Long)4L);
	ring_buffer = CAR(temp);
	if (FIXNUMP(absolute_history_time))
	    gensymed_symbol = (double)IFIX(absolute_history_time);
	else
	    gensymed_symbol = DOUBLE_FLOAT_TO_DOUBLE(absolute_history_time);
	gensymed_symbol_1 = relative_p ? DFLOAT_ISAREF_1(G2_time_at_start,
		(SI_Long)0L) : 0.0;
	gensymed_symbol = gensymed_symbol + gensymed_symbol_1;
	gensymed_symbol_1 = DFLOAT_ISAREF_1(ISVREF(cascaded_ring_buffer,
		(SI_Long)10L),(SI_Long)0L);
	history_time = gensymed_symbol - gensymed_symbol_1;
	next_index = Nil;
	next_history_time = Nil;
	index_1 = Previous_index_for_ring_buffer;
      next_loop:
	if (FIXNUM_EQ(index_1,ISVREF(ring_buffer,(SI_Long)1L))) {
	    result = results_of_element_search(cascaded_ring_buffer,
		    ring_buffer,index_1,Nil);
	    goto end_1;
	}
	next_index = FIXNUM_EQ(index_1,FIXNUM_SUB1(ISVREF(ring_buffer,
		(SI_Long)4L))) ? FIX((SI_Long)0L) : FIXNUM_ADD1(index_1);
	vector_1 = ISVREF(ring_buffer,(SI_Long)7L);
	if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
		Managed_array_unique_marker)) {
	    managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(vector_1,IFIX(FIXNUM_ADD(next_index,
		    Managed_array_index_offset))) : ISVREF(ISVREF(vector_1,
		    (IFIX(next_index) >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L),IFIX(next_index) & (SI_Long)1023L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		next_history_time = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		next_history_time = aref1(managed_number_or_value,
			FIX((SI_Long)0L));
	    else if (text_string_p(managed_number_or_value))
		next_history_time = copy_text_string(managed_number_or_value);
	    else
		next_history_time = managed_number_or_value;
	}
	else
	    next_history_time = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
		    (IFIX(next_index) >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L),IFIX(next_index) & (SI_Long)1023L));
	if (NUM_GT(next_history_time,DOUBLE_TO_DOUBLE_FLOAT(history_time)))
	    goto end_loop;
	index_1 = next_index;
	goto next_loop;
      end_loop:
	result = results_of_element_search(cascaded_ring_buffer,
		ring_buffer,index_1,next_history_time);
	goto end_1;
	result = VALUES_1(Qnil);
      end_1:;
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* GET-HISTORY-ELEMENT-BY-BINARY-SEARCH */
Object get_history_element_by_binary_search varargs_1(int, n)
{
    Object cascaded_ring_buffer, history_time;
    Object relative_p, temp;
    double gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(148,79);
    INIT_ARGS_nonrelocating();
    cascaded_ring_buffer = REQUIRED_ARG_nonrelocating();
    history_time = REQUIRED_ARG_nonrelocating();
    relative_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	temp = ISVREF(cascaded_ring_buffer,(SI_Long)4L);
	temp = CAR(temp);
	if (FIXNUMP(history_time))
	    gensymed_symbol = (double)IFIX(history_time);
	else
	    gensymed_symbol = DOUBLE_FLOAT_TO_DOUBLE(history_time);
	gensymed_symbol_1 = relative_p ? DFLOAT_ISAREF_1(G2_time_at_start,
		(SI_Long)0L) : 0.0;
	gensymed_symbol = gensymed_symbol + gensymed_symbol_1;
	gensymed_symbol_1 = DFLOAT_ISAREF_1(ISVREF(cascaded_ring_buffer,
		(SI_Long)10L),(SI_Long)0L);
	result = get_ring_buffer_element_by_binary_search(cascaded_ring_buffer,
		temp,DOUBLE_TO_DOUBLE_FLOAT(gensymed_symbol - 
		gensymed_symbol_1));
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* GET-RING-BUFFER-ELEMENT-BY-BINARY-SEARCH */
Object get_ring_buffer_element_by_binary_search(cascaded_ring_buffer_qm,
	    ring_buffer,history_time)
    Object cascaded_ring_buffer_qm, ring_buffer, history_time;
{
    Object index_for_newest_element_in_interval;
    Object index_for_oldest_element_in_interval;
    Object index_for_median_element_in_interval, vector_1;
    Object managed_number_or_value, temp, temp_1, gensymed_symbol_1;
    Object time_for_median_element;
    SI_Long gensymed_symbol;

    x_note_fn_call(148,80);
    index_for_newest_element_in_interval = ISVREF(ring_buffer,(SI_Long)1L);
    index_for_oldest_element_in_interval = ISVREF(ring_buffer,(SI_Long)2L);
    index_for_median_element_in_interval = 
	    get_median_element_index(ring_buffer,
	    index_for_newest_element_in_interval,
	    index_for_oldest_element_in_interval);
  next_loop:
    if (FIXNUM_EQ(index_for_median_element_in_interval,
	    index_for_oldest_element_in_interval) || 
	    FIXNUM_EQ(index_for_median_element_in_interval,
	    index_for_newest_element_in_interval)) {
	if (FIXNUM_NE(index_for_oldest_element_in_interval,
		index_for_newest_element_in_interval)) {
	    vector_1 = ISVREF(ring_buffer,(SI_Long)7L);
	    if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
		    (SI_Long)0L),Managed_array_unique_marker)) {
		managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(vector_1,
			IFIX(FIXNUM_ADD(index_for_oldest_element_in_interval,
			Managed_array_index_offset))) : 
			ISVREF(ISVREF(vector_1,
			(IFIX(index_for_oldest_element_in_interval) >>  -  
			- (SI_Long)10L) + (SI_Long)2L),
			IFIX(index_for_oldest_element_in_interval) & 
			(SI_Long)1023L);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    temp = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    temp = aref1(managed_number_or_value,FIX((SI_Long)0L));
		else if (text_string_p(managed_number_or_value))
		    temp = copy_text_string(managed_number_or_value);
		else
		    temp = managed_number_or_value;
	    }
	    else
		temp = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
			(IFIX(index_for_oldest_element_in_interval) >>  -  
			- (SI_Long)10L) + (SI_Long)2L),
			IFIX(index_for_oldest_element_in_interval) & 
			(SI_Long)1023L));
	    temp_1 = l_abs(minus(history_time,temp));
	    vector_1 = ISVREF(ring_buffer,(SI_Long)7L);
	    if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
		    (SI_Long)0L),Managed_array_unique_marker)) {
		managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(vector_1,
			IFIX(FIXNUM_ADD(index_for_newest_element_in_interval,
			Managed_array_index_offset))) : 
			ISVREF(ISVREF(vector_1,
			(IFIX(index_for_newest_element_in_interval) >>  -  
			- (SI_Long)10L) + (SI_Long)2L),
			IFIX(index_for_newest_element_in_interval) & 
			(SI_Long)1023L);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    temp = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    temp = aref1(managed_number_or_value,FIX((SI_Long)0L));
		else if (text_string_p(managed_number_or_value))
		    temp = copy_text_string(managed_number_or_value);
		else
		    temp = managed_number_or_value;
	    }
	    else
		temp = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
			(IFIX(index_for_newest_element_in_interval) >>  -  
			- (SI_Long)10L) + (SI_Long)2L),
			IFIX(index_for_newest_element_in_interval) & 
			(SI_Long)1023L));
	    temp = l_abs(minus(history_time,temp));
	    index_for_median_element_in_interval = NUM_LT(temp_1,temp) ? 
		    index_for_oldest_element_in_interval : 
		    index_for_newest_element_in_interval;
	}
	temp_1 = index_for_median_element_in_interval;
	if ( !FIXNUM_EQ(index_for_median_element_in_interval,
		ISVREF(ring_buffer,(SI_Long)1L))) {
	    vector_1 = ISVREF(ring_buffer,(SI_Long)7L);
	    if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
		    (SI_Long)0L),Managed_array_unique_marker)) {
		gensymed_symbol = 
			FIXNUM_EQ(index_for_median_element_in_interval,
			FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ? 
			(SI_Long)0L : 
			IFIX(FIXNUM_ADD1(index_for_median_element_in_interval));
		managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(vector_1,gensymed_symbol + 
			IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(vector_1,(gensymed_symbol >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
			(SI_Long)1023L);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    temp = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    temp = aref1(managed_number_or_value,FIX((SI_Long)0L));
		else if (text_string_p(managed_number_or_value))
		    temp = copy_text_string(managed_number_or_value);
		else
		    temp = managed_number_or_value;
	    }
	    else {
		gensymed_symbol = 
			FIXNUM_EQ(index_for_median_element_in_interval,
			FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L))) ? 
			(SI_Long)0L : 
			IFIX(FIXNUM_ADD1(index_for_median_element_in_interval));
		gensymed_symbol_1 = ISVREF(vector_1,(gensymed_symbol >>  - 
			 - (SI_Long)10L) + (SI_Long)2L);
		temp = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(gensymed_symbol_1,
			gensymed_symbol & (SI_Long)1023L));
	    }
	}
	else
	    temp = Nil;
	return results_of_element_search(cascaded_ring_buffer_qm,
		ring_buffer,temp_1,temp);
    }
    else {
	vector_1 = ISVREF(ring_buffer,(SI_Long)7L);
	if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
		Managed_array_unique_marker)) {
	    managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(vector_1,
		    IFIX(FIXNUM_ADD(index_for_median_element_in_interval,
		    Managed_array_index_offset))) : ISVREF(ISVREF(vector_1,
		    (IFIX(index_for_median_element_in_interval) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),
		    IFIX(index_for_median_element_in_interval) & 
		    (SI_Long)1023L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		time_for_median_element = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		time_for_median_element = aref1(managed_number_or_value,
			FIX((SI_Long)0L));
	    else if (text_string_p(managed_number_or_value))
		time_for_median_element = 
			copy_text_string(managed_number_or_value);
	    else
		time_for_median_element = managed_number_or_value;
	}
	else
	    time_for_median_element = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
		    (IFIX(index_for_median_element_in_interval) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),
		    IFIX(index_for_median_element_in_interval) & 
		    (SI_Long)1023L));
	if (NUM_LT(history_time,time_for_median_element))
	    index_for_newest_element_in_interval = 
		    index_for_median_element_in_interval;
	else
	    index_for_oldest_element_in_interval = 
		    index_for_median_element_in_interval;
	index_for_median_element_in_interval = 
		get_median_element_index(ring_buffer,
		index_for_newest_element_in_interval,
		index_for_oldest_element_in_interval);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* GET-HISTORY-INDEX-BY-BINARY-SEARCH */
Object get_history_index_by_binary_search(cascaded_ring_buffer,
	    history_time,relative_p)
    Object cascaded_ring_buffer, history_time, relative_p;
{
    Object gensymed_symbol;
    Object result;

    x_note_fn_call(148,81);
    result = get_history_element_by_binary_search(3,cascaded_ring_buffer,
	    history_time,relative_p);
    gensymed_symbol = NTH_VALUE((SI_Long)3L, result);
    return VALUES_1(gensymed_symbol);
}

/* GET-PREVIOUS-HISTORY-TIME */
Object get_previous_history_time()
{
    Object temp, ring_buffer, previous_index;

    x_note_fn_call(148,82);
    temp = ISVREF(Previous_cascaded_ring_buffer_accessed,(SI_Long)4L);
    ring_buffer = CAR(temp);
    previous_index = FIXNUM_EQ(Previous_index_for_ring_buffer,
	    ISVREF(ring_buffer,(SI_Long)2L)) ? 
	    Previous_index_for_ring_buffer : 
	    IFIX(Previous_index_for_ring_buffer) == (SI_Long)0L ? 
	    FIXNUM_SUB1(ISVREF(ring_buffer,(SI_Long)4L)) : 
	    FIXNUM_SUB1(Previous_index_for_ring_buffer);
    return get_history_current_time(Previous_cascaded_ring_buffer_accessed,
	    previous_index,Nil);
}

/* GET-HISTORY-ELEMENT-USING-BEST-SEARCH */
Object get_history_element_using_best_search(cascaded_ring_buffer,
	    history_time,relative_p)
    Object cascaded_ring_buffer, history_time, relative_p;
{
    x_note_fn_call(148,83);
    if (EQ(cascaded_ring_buffer,Previous_cascaded_ring_buffer_accessed))
	return get_history_element_by_linear_search(3,cascaded_ring_buffer,
		history_time,relative_p);
    else
	return get_history_element_by_binary_search(3,cascaded_ring_buffer,
		history_time,relative_p);
}

/* GET-RING-BUFFER-ELEMENT-AT-HISTORY-TIME */
Object get_ring_buffer_element_at_history_time(ring_buffer,history_time)
    Object ring_buffer, history_time;
{
    Object previous_cascaded_ring_buffer_accessed;
    Object previous_index_for_ring_buffer;
    Declare_special(2);
    Object result;

    x_note_fn_call(148,84);
    previous_cascaded_ring_buffer_accessed = Nil;
    previous_index_for_ring_buffer = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Previous_index_for_ring_buffer,Qprevious_index_for_ring_buffer,previous_index_for_ring_buffer,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Previous_cascaded_ring_buffer_accessed,Qprevious_cascaded_ring_buffer_accessed,previous_cascaded_ring_buffer_accessed,
	      0);
	result = get_ring_buffer_element_by_binary_search(Nil,ring_buffer,
		history_time);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* GET-MEDIAN-ELEMENT-INDEX */
Object get_median_element_index(ring_buffer,newest_element_index,
	    oldest_element_index)
    Object ring_buffer, newest_element_index, oldest_element_index;
{
    Object ring_buffer_size;
    SI_Long ring_buffer_length, ring_buffer_half_length;

    x_note_fn_call(148,85);
    ring_buffer_size = ISVREF(ring_buffer,(SI_Long)4L);
    ring_buffer_length = FIXNUM_GE(newest_element_index,
	    oldest_element_index) ? IFIX(FIXNUM_MINUS(newest_element_index,
	    oldest_element_index)) : 
	    IFIX(FIXNUM_MINUS(FIXNUM_ADD(newest_element_index,
	    ring_buffer_size),oldest_element_index));
    ring_buffer_half_length = ring_buffer_length >>  -  - (SI_Long)1L;
    return chestnut_modf_function(FIX(IFIX(oldest_element_index) + 
	    ring_buffer_half_length),ring_buffer_size);
}

static Object Qnever;              /* never */

static Object string_constant;     /* "Non-numeric value encountered in history for ~NF while computing ~
				    *                       ~a value request.  The value was ~a."
				    */

static Object string_constant_1;   /* "The begin time of the interval specified is greater than the end time ~
				    *                  while computing ~a value for ~NF."
				    */

/* RETURN-HISTORY-VALUE */
Object return_history_value(variable,history_value,history_operator_string,
	    value_must_be_a_number_qm,value_requested_by_simulator_qm,
	    computation_involves_interval_qm,interval_ok_qm,value_type)
    Object variable, history_value, history_operator_string;
    Object value_must_be_a_number_qm, value_requested_by_simulator_qm;
    Object computation_involves_interval_qm, interval_ok_qm, value_type;
{
    Object top_of_stack, message_1, value, expiration_qm, data_type;
    Object result;

    x_note_fn_call(148,86);
    if (history_value) {
	if ( !TRUEP(value_must_be_a_number_qm) || NUMBERP(history_value))
	    result = VALUES_3(history_value,Qnever,value_type);
	else {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(4,string_constant,
		    variable,history_operator_string,history_value);
	    raw_stack_error_named_error(top_of_stack,message_1);
	    if (value_requested_by_simulator_qm)
		result = VALUES_1(Simulation_no_value);
	    else
		result = VALUES_3(Nil,Nil,Nil);
	}
    }
    else {
	if (computation_involves_interval_qm &&  !TRUEP(interval_ok_qm)) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(3,
		    string_constant_1,history_operator_string,variable);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	result = VALUES_1(Nil);
    }
    MVS_3(result,value,expiration_qm,data_type);
    if (value_requested_by_simulator_qm)
	return VALUES_1(value);
    else
	return VALUES_3(value,expiration_qm,data_type);
}

Object Max_number_of_history_evaluations = UNBOUND;

/* GET-NUMBER-OF-DATAPOINTS-IN-INTERVAL */
Object get_number_of_datapoints_in_interval(interval_begin_time,
	    interval_end_time,value_history_ring_buffer_or_cascade,
	    value_history_cascaded_ring_buffer,
	    referencing_simulation_history_qm)
    Object interval_begin_time, interval_end_time;
    Object value_history_ring_buffer_or_cascade;
    Object value_history_cascaded_ring_buffer;
    Object referencing_simulation_history_qm;
{
    Object storage_time, oldest_active_element_index, element_index;
    Object in_interval_qm, total_number;

    x_note_fn_call(148,87);
    storage_time = Nil;
    oldest_active_element_index = 
	    ISVREF(value_history_ring_buffer_or_cascade,(SI_Long)2L);
    element_index = ISVREF(value_history_ring_buffer_or_cascade,(SI_Long)1L);
    in_interval_qm = Nil;
    total_number = FIX((SI_Long)0L);
  next_loop:
    storage_time = 
	    get_history_current_time(value_history_cascaded_ring_buffer,
	    element_index,referencing_simulation_history_qm);
    if (NUM_LT(storage_time,interval_begin_time))
	return VALUES_1(total_number);
    if ( !TRUEP(in_interval_qm)) {
	if (NUM_LE(storage_time,interval_end_time)) {
	    in_interval_qm = T;
	    total_number = FIXNUM_ADD1(total_number);
	}
    }
    else
	total_number = FIXNUM_ADD1(total_number);
    if (FIXNUM_EQ(element_index,oldest_active_element_index))
	return VALUES_1(total_number);
    element_index = IFIX(element_index) == (SI_Long)0L ? 
	    FIXNUM_SUB1(ISVREF(value_history_ring_buffer_or_cascade,
	    (SI_Long)4L)) : FIXNUM_SUB1(element_index);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qlong;               /* long */

static Object string_constant_2;   /* "The history function ~a, which requires numeric data, ~
				    *                tried to use the history of the variable ~NF, which has a ~
				    *               non-numeric data type."
				    */

static Object Qget_interpolated_delayed_value;  /* get-interpolated-delayed-value */

static Object float_constant;      /* 0.0 */

static Object string_constant_3;   /* "an interpolated delayed" */

/* GET-INTERPOLATED-DELAYED-VALUE */
Object get_interpolated_delayed_value(variable,
	    value_requested_by_simulator_qm,delay_time)
    Object variable, value_requested_by_simulator_qm, delay_time;
{
    Object symbol, top_of_stack, message_1, history_being_kept_qm;
    Object referencing_simulation_history_qm, sub_class_bit_vector;
    Object simulation_subtable_qm, simulation_stored_histories_qm;
    Object value_history_cascaded_ring_buffer;
    Object variable_or_parameter_stored_histories_qm;
    Object value_history_ring_buffer_or_cascade, temp_1, historical_time;
    Object oldest_active_element_index, newest_active_element_index;
    Object element_index, storage_time, vector_1, managed_number_or_value;
    Object interpolated_delayed_value, delayed_value_1, storage_time_1;
    Object delayed_value_2, storage_time_2;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(148,88);
    if (T) {
	symbol = ISVREF(variable,(SI_Long)20L);
	temp =  !(EQ(symbol,Qnumber) || EQ(symbol,Qinteger) || EQ(symbol,
		Qfloat) || EQ(symbol,Qlong) || 
		lookup_global_or_kb_specific_property_value(symbol,
		Numeric_data_type_gkbprop));
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_2,
		Qget_interpolated_delayed_value,variable);
	raw_stack_error_named_error(top_of_stack,message_1);
	return VALUES_1(Nil);
    }
    else {
	history_being_kept_qm = Nil;
	referencing_simulation_history_qm = value_requested_by_simulator_qm;
	if (value_requested_by_simulator_qm) {
	    sub_class_bit_vector = ISVREF(ISVREF(variable,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Variable_class_description,(SI_Long)18L));
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
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    simulation_subtable_qm = get_lookup_slot_value(variable,
		    Qsimulation_details);
	    simulation_stored_histories_qm = simulation_subtable_qm ? 
		    ISVREF(simulation_subtable_qm,(SI_Long)20L) : Nil;
	    history_being_kept_qm =  ! !(simulation_subtable_qm && 
		    ISVREF(simulation_subtable_qm,(SI_Long)21L)) ? T : Nil;
	    value_history_cascaded_ring_buffer =  
		    !TRUEP(history_being_kept_qm) ||  
		    !TRUEP(simulation_stored_histories_qm) || 
		    cascaded_ring_buffer_empty_qm(simulation_stored_histories_qm) 
		    ? Nil : simulation_stored_histories_qm;
	}
	else {
	    variable_or_parameter_stored_histories_qm = ISVREF(variable,
		    (SI_Long)24L);
	    referencing_simulation_history_qm = Nil;
	    history_being_kept_qm =  ! !TRUEP(ISVREF(variable,
		    (SI_Long)25L)) ? T : Nil;
	    value_history_cascaded_ring_buffer =  
		    !TRUEP(history_being_kept_qm) ||  
		    !TRUEP(ISVREF(variable,(SI_Long)24L)) || 
		    cascaded_ring_buffer_empty_qm(variable_or_parameter_stored_histories_qm) 
		    ? Nil : variable_or_parameter_stored_histories_qm;
	}
	value_history_ring_buffer_or_cascade = Nil;
	if ( !TRUEP(value_history_cascaded_ring_buffer) && ( 
		!TRUEP(history_being_kept_qm) || T))
	    return VALUES_1(Nil);
	else {
	    if (value_history_cascaded_ring_buffer) {
		temp_1 = ISVREF(value_history_cascaded_ring_buffer,
			(SI_Long)4L);
		value_history_ring_buffer_or_cascade = CAR(temp_1);
	    }
	    else
		value_history_ring_buffer_or_cascade = Nil;
	    historical_time = delay_time;
	    oldest_active_element_index = 
		    ISVREF(value_history_ring_buffer_or_cascade,(SI_Long)2L);
	    newest_active_element_index = 
		    ISVREF(value_history_ring_buffer_or_cascade,(SI_Long)1L);
	    element_index = newest_active_element_index;
	    storage_time = Nil;
	  next_loop:
	    storage_time = 
		    get_history_current_time(value_history_cascaded_ring_buffer,
		    element_index,referencing_simulation_history_qm);
	    if (NUM_EQ(storage_time,historical_time)) {
		vector_1 = ISVREF(value_history_ring_buffer_or_cascade,
			(SI_Long)6L);
		if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
			(SI_Long)0L),Managed_array_unique_marker)) {
		    managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    ISVREF(vector_1,IFIX(FIXNUM_ADD(element_index,
			    Managed_array_index_offset))) : 
			    ISVREF(ISVREF(vector_1,(IFIX(element_index) >> 
			     -  - (SI_Long)10L) + (SI_Long)2L),
			    IFIX(element_index) & (SI_Long)1023L);
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			interpolated_delayed_value = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			interpolated_delayed_value = 
				aref1(managed_number_or_value,
				FIX((SI_Long)0L));
		    else if (text_string_p(managed_number_or_value))
			interpolated_delayed_value = 
				copy_text_string(managed_number_or_value);
		    else
			interpolated_delayed_value = managed_number_or_value;
		}
		else
		    interpolated_delayed_value = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
			    (IFIX(element_index) >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),IFIX(element_index) & 
			    (SI_Long)1023L));
		goto end_1;
	    }
	    else if (NUM_LT(storage_time,historical_time)) {
		vector_1 = ISVREF(value_history_ring_buffer_or_cascade,
			(SI_Long)6L);
		if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
			(SI_Long)0L),Managed_array_unique_marker)) {
		    managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    ISVREF(vector_1,IFIX(FIXNUM_ADD(element_index,
			    Managed_array_index_offset))) : 
			    ISVREF(ISVREF(vector_1,(IFIX(element_index) >> 
			     -  - (SI_Long)10L) + (SI_Long)2L),
			    IFIX(element_index) & (SI_Long)1023L);
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			delayed_value_1 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			delayed_value_1 = aref1(managed_number_or_value,
				FIX((SI_Long)0L));
		    else if (text_string_p(managed_number_or_value))
			delayed_value_1 = 
				copy_text_string(managed_number_or_value);
		    else
			delayed_value_1 = managed_number_or_value;
		}
		else
		    delayed_value_1 = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
			    (IFIX(element_index) >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),IFIX(element_index) & 
			    (SI_Long)1023L));
		storage_time_1 = lfloat(storage_time,float_constant);
		delayed_value_2 = Nil;
		storage_time_2 = Nil;
		if (NUMBERP(delayed_value_1))
		    delayed_value_1 = lfloat(delayed_value_1,float_constant);
		else {
		    interpolated_delayed_value = delayed_value_1;
		    goto end_1;
		}
		if ( !FIXNUM_EQ(element_index,newest_active_element_index))
		    element_index = FIXNUM_EQ(element_index,
			    FIXNUM_SUB1(ISVREF(value_history_ring_buffer_or_cascade,
			    (SI_Long)4L))) ? FIX((SI_Long)0L) : 
			    FIXNUM_ADD1(element_index);
		else {
		    interpolated_delayed_value = delayed_value_1;
		    goto end_1;
		}
		storage_time_2 = 
			lfloat(get_history_current_time(value_history_cascaded_ring_buffer,
			element_index,referencing_simulation_history_qm),
			float_constant);
		vector_1 = ISVREF(value_history_ring_buffer_or_cascade,
			(SI_Long)6L);
		if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
			(SI_Long)0L),Managed_array_unique_marker)) {
		    managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    ISVREF(vector_1,IFIX(FIXNUM_ADD(element_index,
			    Managed_array_index_offset))) : 
			    ISVREF(ISVREF(vector_1,(IFIX(element_index) >> 
			     -  - (SI_Long)10L) + (SI_Long)2L),
			    IFIX(element_index) & (SI_Long)1023L);
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			delayed_value_2 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			delayed_value_2 = aref1(managed_number_or_value,
				FIX((SI_Long)0L));
		    else if (text_string_p(managed_number_or_value))
			delayed_value_2 = 
				copy_text_string(managed_number_or_value);
		    else
			delayed_value_2 = managed_number_or_value;
		}
		else
		    delayed_value_2 = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
			    (IFIX(element_index) >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),IFIX(element_index) & 
			    (SI_Long)1023L));
		if (NUMBERP(delayed_value_2))
		    delayed_value_2 = lfloat(delayed_value_2,float_constant);
		else {
		    interpolated_delayed_value = delayed_value_2;
		    goto end_1;
		}
		if (NUM_EQ(storage_time_1,storage_time_2)) {
		    interpolated_delayed_value = delayed_value_2;
		    goto end_1;
		}
		interpolated_delayed_value = add(delayed_value_1,
			ltimes(minus(historical_time,storage_time_1),
			divide(minus(delayed_value_2,delayed_value_1),
			minus(storage_time_2,storage_time_1))));
		goto end_1;
	    }
	    if ( ! !FIXNUM_EQ(element_index,oldest_active_element_index))
		goto end_loop;
	    element_index = IFIX(element_index) == (SI_Long)0L ? 
		    FIXNUM_SUB1(ISVREF(value_history_ring_buffer_or_cascade,
		    (SI_Long)4L)) : FIXNUM_SUB1(element_index);
	    goto next_loop;
	  end_loop:
	    interpolated_delayed_value = Qnil;
	  end_1:;
	    return return_history_value(variable,
		    interpolated_delayed_value,string_constant_3,T,
		    value_requested_by_simulator_qm,Nil,Nil,
		    type_specification_of_variable_or_parameter_value(variable));
	}
    }
}

static Object Qget_historical_delayed_value;  /* get-historical-delayed-value */

static Object string_constant_4;   /* "WARNING: suspected historical-delayed-value internal error.  Please report to Gensym." */

static Object string_constant_5;   /* "a delayed" */

/* GET-HISTORICAL-DELAYED-VALUE */
Object get_historical_delayed_value(variable,
	    value_requested_by_simulator_qm,delay_time)
    Object variable, value_requested_by_simulator_qm, delay_time;
{
    Object symbol, top_of_stack, message_1, history_being_kept_qm;
    Object referencing_simulation_history_qm, sub_class_bit_vector;
    Object simulation_subtable_qm, simulation_stored_histories_qm;
    Object value_history_cascaded_ring_buffer;
    Object variable_or_parameter_stored_histories_qm;
    Object value_history_ring_buffer_or_cascade, temp_1, bottom, top;
    Object oldest_active_element_index, newest_active_element_index;
    Object zero_index_time, oldest_time, newest_time, top_time, bottom_time;
    Object delayed_value, value_time, max_index, probe_index, probe_time;
    Object value_index, temp_2, vector_1, managed_number_or_value;
    Object element_index, storage_time;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, max_index_time;
    char temp;

    x_note_fn_call(148,89);
    if (Nil) {
	symbol = ISVREF(variable,(SI_Long)20L);
	temp =  !(EQ(symbol,Qnumber) || EQ(symbol,Qinteger) || EQ(symbol,
		Qfloat) || EQ(symbol,Qlong) || 
		lookup_global_or_kb_specific_property_value(symbol,
		Numeric_data_type_gkbprop));
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_2,
		Qget_historical_delayed_value,variable);
	raw_stack_error_named_error(top_of_stack,message_1);
	return VALUES_1(Nil);
    }
    else {
	history_being_kept_qm = Nil;
	referencing_simulation_history_qm = value_requested_by_simulator_qm;
	if (value_requested_by_simulator_qm) {
	    sub_class_bit_vector = ISVREF(ISVREF(variable,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Variable_class_description,(SI_Long)18L));
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
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    simulation_subtable_qm = get_lookup_slot_value(variable,
		    Qsimulation_details);
	    simulation_stored_histories_qm = simulation_subtable_qm ? 
		    ISVREF(simulation_subtable_qm,(SI_Long)20L) : Nil;
	    history_being_kept_qm =  ! !(simulation_subtable_qm && 
		    ISVREF(simulation_subtable_qm,(SI_Long)21L)) ? T : Nil;
	    value_history_cascaded_ring_buffer =  
		    !TRUEP(history_being_kept_qm) ||  
		    !TRUEP(simulation_stored_histories_qm) || 
		    cascaded_ring_buffer_empty_qm(simulation_stored_histories_qm) 
		    ? Nil : simulation_stored_histories_qm;
	}
	else {
	    variable_or_parameter_stored_histories_qm = ISVREF(variable,
		    (SI_Long)24L);
	    referencing_simulation_history_qm = Nil;
	    history_being_kept_qm =  ! !TRUEP(ISVREF(variable,
		    (SI_Long)25L)) ? T : Nil;
	    value_history_cascaded_ring_buffer =  
		    !TRUEP(history_being_kept_qm) ||  
		    !TRUEP(ISVREF(variable,(SI_Long)24L)) || 
		    cascaded_ring_buffer_empty_qm(variable_or_parameter_stored_histories_qm) 
		    ? Nil : variable_or_parameter_stored_histories_qm;
	}
	value_history_ring_buffer_or_cascade = Nil;
	if ( !TRUEP(value_history_cascaded_ring_buffer) && ( 
		!TRUEP(history_being_kept_qm) || T))
	    return VALUES_1(Nil);
	else {
	    if (value_history_cascaded_ring_buffer) {
		temp_1 = ISVREF(value_history_cascaded_ring_buffer,
			(SI_Long)4L);
		value_history_ring_buffer_or_cascade = CAR(temp_1);
	    }
	    else
		value_history_ring_buffer_or_cascade = Nil;
	    bottom = Nil;
	    top = Nil;
	    oldest_active_element_index = 
		    ISVREF(value_history_ring_buffer_or_cascade,(SI_Long)2L);
	    newest_active_element_index = 
		    ISVREF(value_history_ring_buffer_or_cascade,(SI_Long)1L);
	    zero_index_time = 
		    get_history_current_time(value_history_cascaded_ring_buffer,
		    FIX((SI_Long)0L),referencing_simulation_history_qm);
	    oldest_time = Nil;
	    newest_time = Nil;
	    top_time = Nil;
	    bottom_time = Nil;
	    delayed_value = Nil;
	    max_index_time = (SI_Long)0L;
	    value_time = Nil;
	    max_index = 
		    FIXNUM_SUB1(ISVREF(value_history_ring_buffer_or_cascade,
		    (SI_Long)4L));
	    newest_time = 
		    get_history_current_time(value_history_cascaded_ring_buffer,
		    newest_active_element_index,
		    referencing_simulation_history_qm);
	    oldest_time = 
		    get_history_current_time(value_history_cascaded_ring_buffer,
		    oldest_active_element_index,
		    referencing_simulation_history_qm);
	    if (NUM_LE(delay_time,newest_time) && NUM_GE(delay_time,
		    oldest_time)) {
		if (FIXNUM_GT(max_index,Most_positive_fixnum)) {
		    zero_index_time = 
			    get_history_current_time(value_history_cascaded_ring_buffer,
			    FIX((SI_Long)0L),
			    referencing_simulation_history_qm);
		    if (IFIX(oldest_active_element_index) == (SI_Long)0L 
			    || NUM_LT(delay_time,newest_time) && 
			    NUM_GT(delay_time,zero_index_time)) {
			bottom = FIX((SI_Long)0L);
			bottom_time = zero_index_time;
			top = newest_active_element_index;
			top_time = newest_time;
		    }
		    else {
			bottom = oldest_active_element_index;
			bottom_time = oldest_time;
			top_time = 
				get_history_current_time(value_history_cascaded_ring_buffer,
				max_index,referencing_simulation_history_qm);
			top = max_index;
		    }
		    probe_index = Nil;
		    probe_time = Nil;
		    value_index = Nil;
		  next_loop:
		    if (FIXNUM_EQ(top,bottom) || delayed_value || value_index)
			goto end_loop;
		    probe_index = add(bottom,ltruncate(minus(top,bottom),
			    FIX((SI_Long)2L)));
		    if (FIXNUM_EQ(probe_index,bottom))
			probe_index = FIXNUM_ADD1(probe_index);
		    probe_time = 
			    get_history_current_time(value_history_cascaded_ring_buffer,
			    probe_index,referencing_simulation_history_qm);
		    if (FIXNUM_EQ(top,add1(bottom))) {
			temp_1 = minus(top,delay_time);
			temp_2 = minus(delay_time,bottom_time);
			if (NUM_GT(temp_1,temp_2)) {
			    value_index = bottom;
			    value_time = bottom_time;
			}
			else {
			    value_index = top;
			    value_time = top_time;
			}
			temp_1 = FIX((SI_Long)0L);
			if (NUM_EQ(value_index,temp_1)) {
			    notify_user_at_console(1,string_constant_4);
			    temp_1 = minus(delay_time,FIX(max_index_time));
			    temp_2 = minus(value_time,delay_time);
			    if (NUM_LT(temp_1,temp_2))
				value_index = max_index;
			}
			else if (NUM_EQ(value_index,max_index)) {
			    temp_1 = minus(zero_index_time,delay_time);
			    temp_2 = minus(delay_time,value_time);
			    if (NUM_LT(temp_1,temp_2))
				value_index = FIX((SI_Long)0L);
			}
		    }
		    else if (NUM_GT(probe_time,delay_time)) {
			top_time = probe_time;
			top = probe_index;
		    }
		    else if (NUM_LT(probe_time,delay_time)) {
			bottom_time = probe_time;
			bottom = probe_index;
		    }
		    else if (NUM_EQ(probe_time,delay_time)) {
			vector_1 = 
				ISVREF(value_history_ring_buffer_or_cascade,
				(SI_Long)6L);
			if (SIMPLE_VECTOR_P(vector_1) && 
				EQ(ISVREF(vector_1,(SI_Long)0L),
				Managed_array_unique_marker)) {
			    managed_number_or_value = 
				    FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
				    Maximum_in_place_array_size) ? 
				    ISVREF(vector_1,
				    IFIX(FIXNUM_ADD(probe_index,
				    Managed_array_index_offset))) : 
				    ISVREF(ISVREF(vector_1,
				    (IFIX(probe_index) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    IFIX(probe_index) & (SI_Long)1023L);
			    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
				    != (SI_Long)0L && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				    == (SI_Long)1L)
				delayed_value = 
					DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
					(SI_Long)0L));
			    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
				    != (SI_Long)0L && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				    == (SI_Long)1L)
				delayed_value = 
					aref1(managed_number_or_value,
					FIX((SI_Long)0L));
			    else if (text_string_p(managed_number_or_value))
				delayed_value = 
					copy_text_string(managed_number_or_value);
			    else
				delayed_value = managed_number_or_value;
			}
			else
			    delayed_value = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
				    (IFIX(probe_index) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    IFIX(probe_index) & (SI_Long)1023L));
		    }
		    goto next_loop;
		  end_loop:
		    if ( !TRUEP(delayed_value)) {
			vector_1 = 
				ISVREF(value_history_ring_buffer_or_cascade,
				(SI_Long)6L);
			if (SIMPLE_VECTOR_P(vector_1) && 
				EQ(ISVREF(vector_1,(SI_Long)0L),
				Managed_array_unique_marker)) {
			    managed_number_or_value = 
				    FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
				    Maximum_in_place_array_size) ? 
				    ISVREF(vector_1,
				    IFIX(FIXNUM_ADD(value_index,
				    Managed_array_index_offset))) : 
				    ISVREF(ISVREF(vector_1,
				    (IFIX(value_index) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    IFIX(value_index) & (SI_Long)1023L);
			    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
				    != (SI_Long)0L && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				    == (SI_Long)1L)
				delayed_value = 
					DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
					(SI_Long)0L));
			    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
				    != (SI_Long)0L && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				    == (SI_Long)1L)
				delayed_value = 
					aref1(managed_number_or_value,
					FIX((SI_Long)0L));
			    else if (text_string_p(managed_number_or_value))
				delayed_value = 
					copy_text_string(managed_number_or_value);
			    else
				delayed_value = managed_number_or_value;
			}
			else
			    delayed_value = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
				    (IFIX(value_index) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    IFIX(value_index) & (SI_Long)1023L));
		    }
		}
		else {
		    element_index = newest_active_element_index;
		    storage_time = Nil;
		  next_loop_1:
		    storage_time = 
			    get_history_current_time(value_history_cascaded_ring_buffer,
			    element_index,referencing_simulation_history_qm);
		    if (NUM_LE(storage_time,delay_time)) {
			vector_1 = 
				ISVREF(value_history_ring_buffer_or_cascade,
				(SI_Long)6L);
			if (SIMPLE_VECTOR_P(vector_1) && 
				EQ(ISVREF(vector_1,(SI_Long)0L),
				Managed_array_unique_marker)) {
			    managed_number_or_value = 
				    FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
				    Maximum_in_place_array_size) ? 
				    ISVREF(vector_1,
				    IFIX(FIXNUM_ADD(element_index,
				    Managed_array_index_offset))) : 
				    ISVREF(ISVREF(vector_1,
				    (IFIX(element_index) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    IFIX(element_index) & (SI_Long)1023L);
			    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
				    != (SI_Long)0L && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				    == (SI_Long)1L)
				delayed_value = 
					DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
					(SI_Long)0L));
			    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
				    != (SI_Long)0L && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				    == (SI_Long)1L)
				delayed_value = 
					aref1(managed_number_or_value,
					FIX((SI_Long)0L));
			    else if (text_string_p(managed_number_or_value))
				delayed_value = 
					copy_text_string(managed_number_or_value);
			    else
				delayed_value = managed_number_or_value;
			}
			else
			    delayed_value = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
				    (IFIX(element_index) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    IFIX(element_index) & (SI_Long)1023L));
			goto end_1;
		    }
		    if ( ! !FIXNUM_EQ(element_index,
			    oldest_active_element_index))
			goto end_loop_1;
		    element_index = IFIX(element_index) == (SI_Long)0L ? 
			    FIXNUM_SUB1(ISVREF(value_history_ring_buffer_or_cascade,
			    (SI_Long)4L)) : FIXNUM_SUB1(element_index);
		    goto next_loop_1;
		  end_loop_1:
		    delayed_value = Qnil;
		  end_1:;
		}
	    }
	    else if (NUM_LT(newest_time,delay_time)) {
		vector_1 = ISVREF(value_history_ring_buffer_or_cascade,
			(SI_Long)6L);
		if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
			(SI_Long)0L),Managed_array_unique_marker)) {
		    managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    ISVREF(vector_1,
			    IFIX(FIXNUM_ADD(newest_active_element_index,
			    Managed_array_index_offset))) : 
			    ISVREF(ISVREF(vector_1,
			    (IFIX(newest_active_element_index) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L),
			    IFIX(newest_active_element_index) & 
			    (SI_Long)1023L);
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			delayed_value = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			delayed_value = aref1(managed_number_or_value,
				FIX((SI_Long)0L));
		    else if (text_string_p(managed_number_or_value))
			delayed_value = 
				copy_text_string(managed_number_or_value);
		    else
			delayed_value = managed_number_or_value;
		}
		else
		    delayed_value = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
			    (IFIX(newest_active_element_index) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L),
			    IFIX(newest_active_element_index) & 
			    (SI_Long)1023L));
	    }
	    return return_history_value(variable,delayed_value,
		    string_constant_5,Nil,value_requested_by_simulator_qm,
		    Nil,Nil,
		    type_specification_of_variable_or_parameter_value(variable));
	}
    }
}

static Object Qget_value_of_previous_datapoint;  /* get-value-of-previous-datapoint */

static Object Qget_history_value_for_ring_buffer_or_cascade_function;  /* get-history-value-for-ring-buffer-or-cascade-function */

/* GET-VALUE-OF-PREVIOUS-DATAPOINT */
Object get_value_of_previous_datapoint(variable,
	    value_requested_by_simulator_qm,n_1)
    Object variable, value_requested_by_simulator_qm, n_1;
{
    Object symbol, top_of_stack, message_1, history_being_kept_qm;
    Object referencing_simulation_history_qm, sub_class_bit_vector;
    Object simulation_subtable_qm, simulation_stored_histories_qm;
    Object value_history_cascaded_ring_buffer;
    Object variable_or_parameter_stored_histories_qm;
    Object value_history_ring_buffer_or_cascade, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(148,90);
    if (Nil) {
	symbol = ISVREF(variable,(SI_Long)20L);
	temp =  !(EQ(symbol,Qnumber) || EQ(symbol,Qinteger) || EQ(symbol,
		Qfloat) || EQ(symbol,Qlong) || 
		lookup_global_or_kb_specific_property_value(symbol,
		Numeric_data_type_gkbprop));
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_2,
		Qget_value_of_previous_datapoint,variable);
	raw_stack_error_named_error(top_of_stack,message_1);
	return VALUES_1(Nil);
    }
    else {
	history_being_kept_qm = Nil;
	referencing_simulation_history_qm = value_requested_by_simulator_qm;
	if (value_requested_by_simulator_qm) {
	    sub_class_bit_vector = ISVREF(ISVREF(variable,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Variable_class_description,(SI_Long)18L));
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
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    simulation_subtable_qm = get_lookup_slot_value(variable,
		    Qsimulation_details);
	    simulation_stored_histories_qm = simulation_subtable_qm ? 
		    ISVREF(simulation_subtable_qm,(SI_Long)20L) : Nil;
	    history_being_kept_qm =  ! !(simulation_subtable_qm && 
		    ISVREF(simulation_subtable_qm,(SI_Long)21L)) ? T : Nil;
	    value_history_cascaded_ring_buffer =  
		    !TRUEP(history_being_kept_qm) ||  
		    !TRUEP(simulation_stored_histories_qm) || 
		    cascaded_ring_buffer_empty_qm(simulation_stored_histories_qm) 
		    ? Nil : simulation_stored_histories_qm;
	}
	else {
	    variable_or_parameter_stored_histories_qm = ISVREF(variable,
		    (SI_Long)24L);
	    referencing_simulation_history_qm = Nil;
	    history_being_kept_qm =  ! !TRUEP(ISVREF(variable,
		    (SI_Long)25L)) ? T : Nil;
	    value_history_cascaded_ring_buffer =  
		    !TRUEP(history_being_kept_qm) ||  
		    !TRUEP(ISVREF(variable,(SI_Long)24L)) || 
		    cascaded_ring_buffer_empty_qm(variable_or_parameter_stored_histories_qm) 
		    ? Nil : variable_or_parameter_stored_histories_qm;
	}
	value_history_ring_buffer_or_cascade = Nil;
	if ( !TRUEP(value_history_cascaded_ring_buffer) && ( 
		!TRUEP(history_being_kept_qm) || T))
	    return VALUES_1(Nil);
	else {
	    if (value_history_cascaded_ring_buffer) {
		temp_1 = ISVREF(value_history_cascaded_ring_buffer,
			(SI_Long)4L);
		value_history_ring_buffer_or_cascade = CAR(temp_1);
	    }
	    else
		value_history_ring_buffer_or_cascade = Nil;
	    return get_value_or_time_of_previous_data_point(variable,
		    value_history_cascaded_ring_buffer,
		    value_history_ring_buffer_or_cascade,
		    value_requested_by_simulator_qm,
		    referencing_simulation_history_qm,n_1,
		    Qget_history_value_for_ring_buffer_or_cascade_function,
		    Nil);
	}
    }
}

static Object Qget_collection_time_of_previous_datapoint;  /* get-collection-time-of-previous-datapoint */

static Object Qget_history_current_time;  /* get-history-current-time */

/* GET-COLLECTION-TIME-OF-PREVIOUS-DATAPOINT */
Object get_collection_time_of_previous_datapoint(variable,
	    value_requested_by_simulator_qm,n_1)
    Object variable, value_requested_by_simulator_qm, n_1;
{
    Object symbol, top_of_stack, message_1, history_being_kept_qm;
    Object referencing_simulation_history_qm, sub_class_bit_vector;
    Object simulation_subtable_qm, simulation_stored_histories_qm;
    Object value_history_cascaded_ring_buffer;
    Object variable_or_parameter_stored_histories_qm;
    Object value_history_ring_buffer_or_cascade, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(148,91);
    if (Nil) {
	symbol = ISVREF(variable,(SI_Long)20L);
	temp =  !(EQ(symbol,Qnumber) || EQ(symbol,Qinteger) || EQ(symbol,
		Qfloat) || EQ(symbol,Qlong) || 
		lookup_global_or_kb_specific_property_value(symbol,
		Numeric_data_type_gkbprop));
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_2,
		Qget_collection_time_of_previous_datapoint,variable);
	raw_stack_error_named_error(top_of_stack,message_1);
	return VALUES_1(Nil);
    }
    else {
	history_being_kept_qm = Nil;
	referencing_simulation_history_qm = value_requested_by_simulator_qm;
	if (value_requested_by_simulator_qm) {
	    sub_class_bit_vector = ISVREF(ISVREF(variable,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Variable_class_description,(SI_Long)18L));
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
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    simulation_subtable_qm = get_lookup_slot_value(variable,
		    Qsimulation_details);
	    simulation_stored_histories_qm = simulation_subtable_qm ? 
		    ISVREF(simulation_subtable_qm,(SI_Long)20L) : Nil;
	    history_being_kept_qm =  ! !(simulation_subtable_qm && 
		    ISVREF(simulation_subtable_qm,(SI_Long)21L)) ? T : Nil;
	    value_history_cascaded_ring_buffer =  
		    !TRUEP(history_being_kept_qm) ||  
		    !TRUEP(simulation_stored_histories_qm) || 
		    cascaded_ring_buffer_empty_qm(simulation_stored_histories_qm) 
		    ? Nil : simulation_stored_histories_qm;
	}
	else {
	    variable_or_parameter_stored_histories_qm = ISVREF(variable,
		    (SI_Long)24L);
	    referencing_simulation_history_qm = Nil;
	    history_being_kept_qm =  ! !TRUEP(ISVREF(variable,
		    (SI_Long)25L)) ? T : Nil;
	    value_history_cascaded_ring_buffer =  
		    !TRUEP(history_being_kept_qm) ||  
		    !TRUEP(ISVREF(variable,(SI_Long)24L)) || 
		    cascaded_ring_buffer_empty_qm(variable_or_parameter_stored_histories_qm) 
		    ? Nil : variable_or_parameter_stored_histories_qm;
	}
	value_history_ring_buffer_or_cascade = Nil;
	if ( !TRUEP(value_history_cascaded_ring_buffer) && ( 
		!TRUEP(history_being_kept_qm) || T))
	    return VALUES_1(Nil);
	else {
	    if (value_history_cascaded_ring_buffer) {
		temp_1 = ISVREF(value_history_cascaded_ring_buffer,
			(SI_Long)4L);
		value_history_ring_buffer_or_cascade = CAR(temp_1);
	    }
	    else
		value_history_ring_buffer_or_cascade = Nil;
	    return get_value_or_time_of_previous_data_point(variable,
		    value_history_cascaded_ring_buffer,
		    value_history_ring_buffer_or_cascade,
		    value_requested_by_simulator_qm,
		    referencing_simulation_history_qm,n_1,
		    Qget_history_current_time,T);
	}
    }
}

static Object string_constant_6;   /* "a previous datapoint" */

/* GET-VALUE-OR-TIME-OF-PREVIOUS-DATA-POINT */
Object get_value_or_time_of_previous_data_point(variable,
	    value_history_cascaded_ring_buffer,
	    value_history_ring_buffer_or_cascade,
	    value_requested_by_simulator_qm,
	    referencing_simulation_history_qm,n_1,accessor_function,
	    type_is_time_stamp_qm)
    Object variable, value_history_cascaded_ring_buffer;
    Object value_history_ring_buffer_or_cascade;
    Object value_requested_by_simulator_qm, referencing_simulation_history_qm;
    Object n_1, accessor_function, type_is_time_stamp_qm;
{
    Object element_index_qm, temp, value_or_time_of_previous_datapoint;

    x_note_fn_call(148,92);
    element_index_qm = 
	    compute_index_for_previous_data_point(value_history_ring_buffer_or_cascade,
	    n_1);
    if (element_index_qm) {
	if (type_is_time_stamp_qm) {
	    temp = SYMBOL_FUNCTION(accessor_function);
	    value_or_time_of_previous_datapoint = FUNCALL_3(temp,
		    value_history_cascaded_ring_buffer,element_index_qm,
		    referencing_simulation_history_qm);
	}
	else {
	    temp = SYMBOL_FUNCTION(accessor_function);
	    value_or_time_of_previous_datapoint = FUNCALL_2(temp,
		    value_history_ring_buffer_or_cascade,element_index_qm);
	}
    }
    else
	value_or_time_of_previous_datapoint = Nil;
    return return_history_value(variable,
	    value_or_time_of_previous_datapoint,string_constant_6,Nil,
	    value_requested_by_simulator_qm,Nil,Nil,type_is_time_stamp_qm ?
	     Qnumber : 
	    type_specification_of_variable_or_parameter_value(variable));
}

/* COMPUTE-INDEX-FOR-PREVIOUS-DATA-POINT */
Object compute_index_for_previous_data_point(ring_buffer_or_cascade,n_1)
    Object ring_buffer_or_cascade, n_1;
{
    Object newest_active_element_index, unwrapped_index, temp, ring_buffer;
    Object index_1, oldest_active_element_index_for_ring_buffer;

    x_note_fn_call(148,93);
    newest_active_element_index = ISVREF(ring_buffer_or_cascade,(SI_Long)1L);
    unwrapped_index = Nil;
    if (ISVREF(ring_buffer_or_cascade,(SI_Long)3L))
	temp = FIX((SI_Long)0L);
    else {
	ring_buffer = ring_buffer_or_cascade;
	index_1 = ISVREF(ring_buffer_or_cascade,(SI_Long)1L);
	oldest_active_element_index_for_ring_buffer = ISVREF(ring_buffer,
		(SI_Long)2L);
	temp = FIXNUM_GE(index_1,
		oldest_active_element_index_for_ring_buffer) ? 
		FIXNUM_ADD1(FIXNUM_MINUS(index_1,
		oldest_active_element_index_for_ring_buffer)) : 
		FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(index_1,
		ISVREF(ring_buffer,(SI_Long)4L)),
		oldest_active_element_index_for_ring_buffer));
    }
    if ( !FIXNUM_GE(n_1,temp)) {
	unwrapped_index = FIXNUM_MINUS(newest_active_element_index,n_1);
	if (IFIX(unwrapped_index) >= (SI_Long)0L)
	    return VALUES_1(unwrapped_index);
	else
	    return VALUES_1(FIXNUM_ADD(ISVREF(ring_buffer_or_cascade,
		    (SI_Long)4L),unwrapped_index));
    }
    else
	return VALUES_1(Nil);
}

static Object Qnumber_of_datapoints;  /* number-of-datapoints */

static Object string_constant_7;   /* "number of history datapoints" */

/* NUMBER-OF-DATAPOINTS */
Object number_of_datapoints(variable,value_requested_by_simulator_qm,
	    interval_begin_time_qm,interval_end_time_qm)
    Object variable, value_requested_by_simulator_qm, interval_begin_time_qm;
    Object interval_end_time_qm;
{
    Object symbol, top_of_stack, message_1, history_being_kept_qm;
    Object referencing_simulation_history_qm, sub_class_bit_vector;
    Object simulation_subtable_qm, simulation_stored_histories_qm;
    Object value_history_cascaded_ring_buffer;
    Object variable_or_parameter_stored_histories_qm;
    Object value_history_ring_buffer_or_cascade, temp_1, interval_ok_qm;
    Object number_of_datapoints_1, ring_buffer, index_1;
    Object oldest_active_element_index_for_ring_buffer;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(148,94);
    if (Nil) {
	symbol = ISVREF(variable,(SI_Long)20L);
	temp =  !(EQ(symbol,Qnumber) || EQ(symbol,Qinteger) || EQ(symbol,
		Qfloat) || EQ(symbol,Qlong) || 
		lookup_global_or_kb_specific_property_value(symbol,
		Numeric_data_type_gkbprop));
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_2,
		Qnumber_of_datapoints,variable);
	raw_stack_error_named_error(top_of_stack,message_1);
	return VALUES_1(Nil);
    }
    else {
	history_being_kept_qm = Nil;
	referencing_simulation_history_qm = value_requested_by_simulator_qm;
	if (value_requested_by_simulator_qm) {
	    sub_class_bit_vector = ISVREF(ISVREF(variable,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Variable_class_description,(SI_Long)18L));
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
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    simulation_subtable_qm = get_lookup_slot_value(variable,
		    Qsimulation_details);
	    simulation_stored_histories_qm = simulation_subtable_qm ? 
		    ISVREF(simulation_subtable_qm,(SI_Long)20L) : Nil;
	    history_being_kept_qm =  ! !(simulation_subtable_qm && 
		    ISVREF(simulation_subtable_qm,(SI_Long)21L)) ? T : Nil;
	    value_history_cascaded_ring_buffer =  
		    !TRUEP(history_being_kept_qm) ||  
		    !TRUEP(simulation_stored_histories_qm) || 
		    cascaded_ring_buffer_empty_qm(simulation_stored_histories_qm) 
		    ? Nil : simulation_stored_histories_qm;
	}
	else {
	    variable_or_parameter_stored_histories_qm = ISVREF(variable,
		    (SI_Long)24L);
	    referencing_simulation_history_qm = Nil;
	    history_being_kept_qm =  ! !TRUEP(ISVREF(variable,
		    (SI_Long)25L)) ? T : Nil;
	    value_history_cascaded_ring_buffer =  
		    !TRUEP(history_being_kept_qm) ||  
		    !TRUEP(ISVREF(variable,(SI_Long)24L)) || 
		    cascaded_ring_buffer_empty_qm(variable_or_parameter_stored_histories_qm) 
		    ? Nil : variable_or_parameter_stored_histories_qm;
	}
	value_history_ring_buffer_or_cascade = Nil;
	if ( !TRUEP(value_history_cascaded_ring_buffer) && ( 
		!TRUEP(history_being_kept_qm) || Nil))
	    return VALUES_1(Nil);
	else {
	    if (value_history_cascaded_ring_buffer) {
		temp_1 = ISVREF(value_history_cascaded_ring_buffer,
			(SI_Long)4L);
		value_history_ring_buffer_or_cascade = CAR(temp_1);
	    }
	    else
		value_history_ring_buffer_or_cascade = Nil;
	    interval_ok_qm =  !TRUEP(interval_begin_time_qm) ? T : Nil;
	    if (interval_ok_qm);
	    else
		interval_ok_qm =  !TRUEP(nanp(interval_begin_time_qm)) &&  
			!TRUEP(nanp(interval_end_time_qm)) ? 
			(NUM_LE(interval_begin_time_qm,
			interval_end_time_qm) ? T : Nil) : Qnil;
	    if ( !TRUEP(value_history_ring_buffer_or_cascade))
		number_of_datapoints_1 = FIX((SI_Long)0L);
	    else if ( !TRUEP(interval_begin_time_qm)) {
		if (ISVREF(value_history_ring_buffer_or_cascade,(SI_Long)3L))
		    number_of_datapoints_1 = FIX((SI_Long)0L);
		else {
		    ring_buffer = value_history_ring_buffer_or_cascade;
		    index_1 = ISVREF(value_history_ring_buffer_or_cascade,
			    (SI_Long)1L);
		    oldest_active_element_index_for_ring_buffer = 
			    ISVREF(ring_buffer,(SI_Long)2L);
		    number_of_datapoints_1 = FIXNUM_GE(index_1,
			    oldest_active_element_index_for_ring_buffer) ? 
			    FIXNUM_ADD1(FIXNUM_MINUS(index_1,
			    oldest_active_element_index_for_ring_buffer)) :
			     FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(index_1,
			    ISVREF(ring_buffer,(SI_Long)4L)),
			    oldest_active_element_index_for_ring_buffer));
		}
	    }
	    else
		number_of_datapoints_1 = interval_ok_qm ? 
			get_number_of_datapoints_in_interval(interval_begin_time_qm,
			interval_end_time_qm,
			value_history_ring_buffer_or_cascade,
			value_history_cascaded_ring_buffer,
			referencing_simulation_history_qm) : Nil;
	    return return_history_value(variable,number_of_datapoints_1,
		    string_constant_7,Nil,value_requested_by_simulator_qm,
		    interval_begin_time_qm,interval_ok_qm,Qinteger);
	}
    }
}

static Object Qget_maximum_value;  /* get-maximum-value */

static Object string_constant_8;   /* "a maximum" */

/* GET-MAXIMUM-VALUE */
Object get_maximum_value(variable,value_requested_by_simulator_qm,
	    interval_begin_time,interval_end_time)
    Object variable, value_requested_by_simulator_qm, interval_begin_time;
    Object interval_end_time;
{
    Object symbol, top_of_stack, message_1, history_being_kept_qm;
    Object referencing_simulation_history_qm, sub_class_bit_vector;
    Object simulation_subtable_qm, simulation_stored_histories_qm;
    Object value_history_cascaded_ring_buffer;
    Object variable_or_parameter_stored_histories_qm;
    Object value_history_ring_buffer_or_cascade, temp_1;
    Object oldest_active_element_index, newest_active_element_index;
    Object interval_ok_qm, in_interval_qm, max_val_qm, element_index, done_qm;
    Object gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    Object temp_accumulated_value_1, storage_time, vector_1;
    Object managed_number_or_value, next_history_value;
    Object store_managed_number_arg, maximum_value;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, i, ab_loop_bind_;
    char temp;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(148,95);
    if (T) {
	symbol = ISVREF(variable,(SI_Long)20L);
	temp =  !(EQ(symbol,Qnumber) || EQ(symbol,Qinteger) || EQ(symbol,
		Qfloat) || EQ(symbol,Qlong) || 
		lookup_global_or_kb_specific_property_value(symbol,
		Numeric_data_type_gkbprop));
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_2,
		Qget_maximum_value,variable);
	raw_stack_error_named_error(top_of_stack,message_1);
	return VALUES_1(Nil);
    }
    else {
	history_being_kept_qm = Nil;
	referencing_simulation_history_qm = value_requested_by_simulator_qm;
	if (value_requested_by_simulator_qm) {
	    sub_class_bit_vector = ISVREF(ISVREF(variable,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Variable_class_description,(SI_Long)18L));
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
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    simulation_subtable_qm = get_lookup_slot_value(variable,
		    Qsimulation_details);
	    simulation_stored_histories_qm = simulation_subtable_qm ? 
		    ISVREF(simulation_subtable_qm,(SI_Long)20L) : Nil;
	    history_being_kept_qm =  ! !(simulation_subtable_qm && 
		    ISVREF(simulation_subtable_qm,(SI_Long)21L)) ? T : Nil;
	    value_history_cascaded_ring_buffer =  
		    !TRUEP(history_being_kept_qm) ||  
		    !TRUEP(simulation_stored_histories_qm) || 
		    cascaded_ring_buffer_empty_qm(simulation_stored_histories_qm) 
		    ? Nil : simulation_stored_histories_qm;
	}
	else {
	    variable_or_parameter_stored_histories_qm = ISVREF(variable,
		    (SI_Long)24L);
	    referencing_simulation_history_qm = Nil;
	    history_being_kept_qm =  ! !TRUEP(ISVREF(variable,
		    (SI_Long)25L)) ? T : Nil;
	    value_history_cascaded_ring_buffer =  
		    !TRUEP(history_being_kept_qm) ||  
		    !TRUEP(ISVREF(variable,(SI_Long)24L)) || 
		    cascaded_ring_buffer_empty_qm(variable_or_parameter_stored_histories_qm) 
		    ? Nil : variable_or_parameter_stored_histories_qm;
	}
	value_history_ring_buffer_or_cascade = Nil;
	if ( !TRUEP(value_history_cascaded_ring_buffer) && ( 
		!TRUEP(history_being_kept_qm) || T))
	    return VALUES_1(Nil);
	else {
	    if (value_history_cascaded_ring_buffer) {
		temp_1 = ISVREF(value_history_cascaded_ring_buffer,
			(SI_Long)4L);
		value_history_ring_buffer_or_cascade = CAR(temp_1);
	    }
	    else
		value_history_ring_buffer_or_cascade = Nil;
	    oldest_active_element_index = 
		    ISVREF(value_history_ring_buffer_or_cascade,(SI_Long)2L);
	    newest_active_element_index = 
		    ISVREF(value_history_ring_buffer_or_cascade,(SI_Long)1L);
	    interval_ok_qm =  !TRUEP(nanp(interval_begin_time)) &&  
		    !TRUEP(nanp(interval_end_time)) ? 
		    (NUM_LE(interval_begin_time,interval_end_time) ? T : 
		    Nil) : Qnil;
	    if (interval_ok_qm) {
		in_interval_qm = Nil;
		max_val_qm = Nil;
		element_index = oldest_active_element_index;
		done_qm = Nil;
	      next_loop:
		gensymed_symbol_3 = interval_end_time;
		gensymed_symbol_4 = value_history_ring_buffer_or_cascade;
		gensymed_symbol_5 = value_history_cascaded_ring_buffer;
		temp_accumulated_value_1 = Nil;
		if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(max_val_qm) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(max_val_qm)) == 
			    (SI_Long)1L)
			temp_accumulated_value_1 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(max_val_qm,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(max_val_qm) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(max_val_qm)) == 
			    (SI_Long)1L)
			temp_accumulated_value_1 = aref1(max_val_qm,
				FIX((SI_Long)0L));
		    else
			temp_accumulated_value_1 = max_val_qm;
		    storage_time = Nil;
		    i = (SI_Long)1L;
		    ab_loop_bind_ = IFIX(Max_number_of_history_evaluations);
		  next_loop_1:
		    if (i > ab_loop_bind_)
			goto end_loop;
		    storage_time = 
			    get_history_current_time(gensymed_symbol_5,
			    element_index,referencing_simulation_history_qm);
		    if ( !TRUEP(in_interval_qm)) {
			if (NUM_GE(storage_time,interval_begin_time) &&  
				!NUM_GT(storage_time,gensymed_symbol_3)) {
			    in_interval_qm = T;
			    vector_1 = ISVREF(gensymed_symbol_4,(SI_Long)6L);
			    if (SIMPLE_VECTOR_P(vector_1) && 
				    EQ(ISVREF(vector_1,(SI_Long)0L),
				    Managed_array_unique_marker)) {
				managed_number_or_value = 
					FIXNUM_LE(ISVREF(vector_1,
					(SI_Long)1L),
					Maximum_in_place_array_size) ? 
					ISVREF(vector_1,
					IFIX(FIXNUM_ADD(element_index,
					Managed_array_index_offset))) : 
					ISVREF(ISVREF(vector_1,
					(IFIX(element_index) >>  -  - 
					(SI_Long)10L) + (SI_Long)2L),
					IFIX(element_index) & (SI_Long)1023L);
				if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					== (SI_Long)1L)
				    next_history_value = 
					    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
					    (SI_Long)0L));
				else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					== (SI_Long)1L)
				    next_history_value = 
					    aref1(managed_number_or_value,
					    FIX((SI_Long)0L));
				else if (text_string_p(managed_number_or_value))
				    next_history_value = 
					    copy_text_string(managed_number_or_value);
				else
				    next_history_value = 
					    managed_number_or_value;
			    }
			    else
				next_history_value = 
					DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
					(IFIX(element_index) >>  -  - 
					(SI_Long)10L) + (SI_Long)2L),
					IFIX(element_index) & (SI_Long)1023L));
			    temp_accumulated_value_1 = next_history_value;
			}
		    }
		    else {
			vector_1 = ISVREF(gensymed_symbol_4,(SI_Long)6L);
			if (SIMPLE_VECTOR_P(vector_1) && 
				EQ(ISVREF(vector_1,(SI_Long)0L),
				Managed_array_unique_marker)) {
			    managed_number_or_value = 
				    FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
				    Maximum_in_place_array_size) ? 
				    ISVREF(vector_1,
				    IFIX(FIXNUM_ADD(element_index,
				    Managed_array_index_offset))) : 
				    ISVREF(ISVREF(vector_1,
				    (IFIX(element_index) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    IFIX(element_index) & (SI_Long)1023L);
			    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
				    != (SI_Long)0L && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				    == (SI_Long)1L)
				next_history_value = 
					DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
					(SI_Long)0L));
			    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
				    != (SI_Long)0L && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				    == (SI_Long)1L)
				next_history_value = 
					aref1(managed_number_or_value,
					FIX((SI_Long)0L));
			    else if (text_string_p(managed_number_or_value))
				next_history_value = 
					copy_text_string(managed_number_or_value);
			    else
				next_history_value = managed_number_or_value;
			}
			else
			    next_history_value = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
				    (IFIX(element_index) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    IFIX(element_index) & (SI_Long)1023L));
			if (NUM_GT(storage_time,gensymed_symbol_3)) {
			    if (temp_accumulated_value_1) {
				store_managed_number_arg = 
					temp_accumulated_value_1;
				max_val_qm = 
					store_managed_number_function(max_val_qm,
					store_managed_number_arg);
			    }
			    done_qm = T;
			    goto end_1;
			}
			else
			    temp_accumulated_value_1 = 
				    lmax(temp_accumulated_value_1,
				    next_history_value);
		    }
		    if (NUM_EQ(storage_time,gensymed_symbol_3) || 
			    FIXNUM_EQ(element_index,
			    newest_active_element_index)) {
			if (temp_accumulated_value_1) {
			    store_managed_number_arg = 
				    temp_accumulated_value_1;
			    max_val_qm = 
				    store_managed_number_function(max_val_qm,
				    store_managed_number_arg);
			}
			done_qm = T;
			goto end_1;
		    }
		    element_index = FIXNUM_EQ(element_index,
			    FIXNUM_SUB1(ISVREF(gensymed_symbol_4,
			    (SI_Long)4L))) ? FIX((SI_Long)0L) : 
			    FIXNUM_ADD1(element_index);
		    i = i + (SI_Long)1L;
		    goto next_loop_1;
		  end_loop:
		    if (temp_accumulated_value_1) {
			store_managed_number_arg = temp_accumulated_value_1;
			max_val_qm = 
				store_managed_number_function(max_val_qm,
				store_managed_number_arg);
		    }
		    done_qm = Nil;
		    goto end_1;
		    done_qm = Qnil;
		  end_1:;
		}
		POP_LOCAL_ALLOCATION(0,0);
		if (done_qm) {
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(max_val_qm) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(max_val_qm)) == 
			    (SI_Long)1L)
			temp_1 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(max_val_qm,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(max_val_qm) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(max_val_qm)) == 
			    (SI_Long)1L)
			temp_1 = aref1(max_val_qm,FIX((SI_Long)0L));
		    else
			temp_1 = max_val_qm;
		    max_val_qm = 
			    reclaim_managed_number_or_value_function(max_val_qm);
		    maximum_value = temp_1;
		    goto end_2;
		}
		goto next_loop;
	      end_loop_1:
		maximum_value = Qnil;
	      end_2:;
	    }
	    else
		maximum_value = Nil;
	    return return_history_value(variable,maximum_value,
		    string_constant_8,T,value_requested_by_simulator_qm,T,
		    interval_ok_qm,
		    type_specification_of_variable_or_parameter_value(variable));
	}
    }
}

static Object Qget_minimum_value;  /* get-minimum-value */

static Object string_constant_9;   /* "minimum" */

/* GET-MINIMUM-VALUE */
Object get_minimum_value(variable,value_requested_by_simulator_qm,
	    interval_begin_time,interval_end_time)
    Object variable, value_requested_by_simulator_qm, interval_begin_time;
    Object interval_end_time;
{
    Object symbol, top_of_stack, message_1, history_being_kept_qm;
    Object referencing_simulation_history_qm, sub_class_bit_vector;
    Object simulation_subtable_qm, simulation_stored_histories_qm;
    Object value_history_cascaded_ring_buffer;
    Object variable_or_parameter_stored_histories_qm;
    Object value_history_ring_buffer_or_cascade, temp_1;
    Object oldest_active_element_index, newest_active_element_index;
    Object interval_ok_qm, in_interval_qm, min_val_qm, element_index, done_qm;
    Object gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    Object temp_accumulated_value_1, storage_time, vector_1;
    Object managed_number_or_value, next_history_value;
    Object store_managed_number_arg, minimum_value;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, i, ab_loop_bind_;
    char temp;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(148,96);
    if (T) {
	symbol = ISVREF(variable,(SI_Long)20L);
	temp =  !(EQ(symbol,Qnumber) || EQ(symbol,Qinteger) || EQ(symbol,
		Qfloat) || EQ(symbol,Qlong) || 
		lookup_global_or_kb_specific_property_value(symbol,
		Numeric_data_type_gkbprop));
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_2,
		Qget_minimum_value,variable);
	raw_stack_error_named_error(top_of_stack,message_1);
	return VALUES_1(Nil);
    }
    else {
	history_being_kept_qm = Nil;
	referencing_simulation_history_qm = value_requested_by_simulator_qm;
	if (value_requested_by_simulator_qm) {
	    sub_class_bit_vector = ISVREF(ISVREF(variable,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Variable_class_description,(SI_Long)18L));
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
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    simulation_subtable_qm = get_lookup_slot_value(variable,
		    Qsimulation_details);
	    simulation_stored_histories_qm = simulation_subtable_qm ? 
		    ISVREF(simulation_subtable_qm,(SI_Long)20L) : Nil;
	    history_being_kept_qm =  ! !(simulation_subtable_qm && 
		    ISVREF(simulation_subtable_qm,(SI_Long)21L)) ? T : Nil;
	    value_history_cascaded_ring_buffer =  
		    !TRUEP(history_being_kept_qm) ||  
		    !TRUEP(simulation_stored_histories_qm) || 
		    cascaded_ring_buffer_empty_qm(simulation_stored_histories_qm) 
		    ? Nil : simulation_stored_histories_qm;
	}
	else {
	    variable_or_parameter_stored_histories_qm = ISVREF(variable,
		    (SI_Long)24L);
	    referencing_simulation_history_qm = Nil;
	    history_being_kept_qm =  ! !TRUEP(ISVREF(variable,
		    (SI_Long)25L)) ? T : Nil;
	    value_history_cascaded_ring_buffer =  
		    !TRUEP(history_being_kept_qm) ||  
		    !TRUEP(ISVREF(variable,(SI_Long)24L)) || 
		    cascaded_ring_buffer_empty_qm(variable_or_parameter_stored_histories_qm) 
		    ? Nil : variable_or_parameter_stored_histories_qm;
	}
	value_history_ring_buffer_or_cascade = Nil;
	if ( !TRUEP(value_history_cascaded_ring_buffer) && ( 
		!TRUEP(history_being_kept_qm) || T))
	    return VALUES_1(Nil);
	else {
	    if (value_history_cascaded_ring_buffer) {
		temp_1 = ISVREF(value_history_cascaded_ring_buffer,
			(SI_Long)4L);
		value_history_ring_buffer_or_cascade = CAR(temp_1);
	    }
	    else
		value_history_ring_buffer_or_cascade = Nil;
	    oldest_active_element_index = 
		    ISVREF(value_history_ring_buffer_or_cascade,(SI_Long)2L);
	    newest_active_element_index = 
		    ISVREF(value_history_ring_buffer_or_cascade,(SI_Long)1L);
	    interval_ok_qm =  !TRUEP(nanp(interval_begin_time)) &&  
		    !TRUEP(nanp(interval_end_time)) ? 
		    (NUM_LE(interval_begin_time,interval_end_time) ? T : 
		    Nil) : Qnil;
	    if (interval_ok_qm) {
		in_interval_qm = Nil;
		min_val_qm = Nil;
		element_index = oldest_active_element_index;
		done_qm = Nil;
	      next_loop:
		gensymed_symbol_3 = interval_end_time;
		gensymed_symbol_4 = value_history_ring_buffer_or_cascade;
		gensymed_symbol_5 = value_history_cascaded_ring_buffer;
		temp_accumulated_value_1 = Nil;
		if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(min_val_qm) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(min_val_qm)) == 
			    (SI_Long)1L)
			temp_accumulated_value_1 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(min_val_qm,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(min_val_qm) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(min_val_qm)) == 
			    (SI_Long)1L)
			temp_accumulated_value_1 = aref1(min_val_qm,
				FIX((SI_Long)0L));
		    else
			temp_accumulated_value_1 = min_val_qm;
		    storage_time = Nil;
		    i = (SI_Long)1L;
		    ab_loop_bind_ = IFIX(Max_number_of_history_evaluations);
		  next_loop_1:
		    if (i > ab_loop_bind_)
			goto end_loop;
		    storage_time = 
			    get_history_current_time(gensymed_symbol_5,
			    element_index,referencing_simulation_history_qm);
		    if ( !TRUEP(in_interval_qm)) {
			if (NUM_GE(storage_time,interval_begin_time) &&  
				!NUM_GT(storage_time,gensymed_symbol_3)) {
			    in_interval_qm = T;
			    vector_1 = ISVREF(gensymed_symbol_4,(SI_Long)6L);
			    if (SIMPLE_VECTOR_P(vector_1) && 
				    EQ(ISVREF(vector_1,(SI_Long)0L),
				    Managed_array_unique_marker)) {
				managed_number_or_value = 
					FIXNUM_LE(ISVREF(vector_1,
					(SI_Long)1L),
					Maximum_in_place_array_size) ? 
					ISVREF(vector_1,
					IFIX(FIXNUM_ADD(element_index,
					Managed_array_index_offset))) : 
					ISVREF(ISVREF(vector_1,
					(IFIX(element_index) >>  -  - 
					(SI_Long)10L) + (SI_Long)2L),
					IFIX(element_index) & (SI_Long)1023L);
				if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					== (SI_Long)1L)
				    next_history_value = 
					    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
					    (SI_Long)0L));
				else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					== (SI_Long)1L)
				    next_history_value = 
					    aref1(managed_number_or_value,
					    FIX((SI_Long)0L));
				else if (text_string_p(managed_number_or_value))
				    next_history_value = 
					    copy_text_string(managed_number_or_value);
				else
				    next_history_value = 
					    managed_number_or_value;
			    }
			    else
				next_history_value = 
					DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
					(IFIX(element_index) >>  -  - 
					(SI_Long)10L) + (SI_Long)2L),
					IFIX(element_index) & (SI_Long)1023L));
			    temp_accumulated_value_1 = next_history_value;
			}
		    }
		    else {
			vector_1 = ISVREF(gensymed_symbol_4,(SI_Long)6L);
			if (SIMPLE_VECTOR_P(vector_1) && 
				EQ(ISVREF(vector_1,(SI_Long)0L),
				Managed_array_unique_marker)) {
			    managed_number_or_value = 
				    FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
				    Maximum_in_place_array_size) ? 
				    ISVREF(vector_1,
				    IFIX(FIXNUM_ADD(element_index,
				    Managed_array_index_offset))) : 
				    ISVREF(ISVREF(vector_1,
				    (IFIX(element_index) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    IFIX(element_index) & (SI_Long)1023L);
			    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
				    != (SI_Long)0L && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				    == (SI_Long)1L)
				next_history_value = 
					DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
					(SI_Long)0L));
			    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
				    != (SI_Long)0L && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				    == (SI_Long)1L)
				next_history_value = 
					aref1(managed_number_or_value,
					FIX((SI_Long)0L));
			    else if (text_string_p(managed_number_or_value))
				next_history_value = 
					copy_text_string(managed_number_or_value);
			    else
				next_history_value = managed_number_or_value;
			}
			else
			    next_history_value = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
				    (IFIX(element_index) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    IFIX(element_index) & (SI_Long)1023L));
			if (NUM_GT(storage_time,gensymed_symbol_3)) {
			    if (temp_accumulated_value_1) {
				store_managed_number_arg = 
					temp_accumulated_value_1;
				min_val_qm = 
					store_managed_number_function(min_val_qm,
					store_managed_number_arg);
			    }
			    done_qm = T;
			    goto end_1;
			}
			else
			    temp_accumulated_value_1 = 
				    lmin(temp_accumulated_value_1,
				    next_history_value);
		    }
		    if (NUM_EQ(storage_time,gensymed_symbol_3) || 
			    FIXNUM_EQ(element_index,
			    newest_active_element_index)) {
			if (temp_accumulated_value_1) {
			    store_managed_number_arg = 
				    temp_accumulated_value_1;
			    min_val_qm = 
				    store_managed_number_function(min_val_qm,
				    store_managed_number_arg);
			}
			done_qm = T;
			goto end_1;
		    }
		    element_index = FIXNUM_EQ(element_index,
			    FIXNUM_SUB1(ISVREF(gensymed_symbol_4,
			    (SI_Long)4L))) ? FIX((SI_Long)0L) : 
			    FIXNUM_ADD1(element_index);
		    i = i + (SI_Long)1L;
		    goto next_loop_1;
		  end_loop:
		    if (temp_accumulated_value_1) {
			store_managed_number_arg = temp_accumulated_value_1;
			min_val_qm = 
				store_managed_number_function(min_val_qm,
				store_managed_number_arg);
		    }
		    done_qm = Nil;
		    goto end_1;
		    done_qm = Qnil;
		  end_1:;
		}
		POP_LOCAL_ALLOCATION(0,0);
		if (done_qm) {
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(min_val_qm) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(min_val_qm)) == 
			    (SI_Long)1L)
			temp_1 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(min_val_qm,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(min_val_qm) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(min_val_qm)) == 
			    (SI_Long)1L)
			temp_1 = aref1(min_val_qm,FIX((SI_Long)0L));
		    else
			temp_1 = min_val_qm;
		    min_val_qm = 
			    reclaim_managed_number_or_value_function(min_val_qm);
		    minimum_value = temp_1;
		    goto end_2;
		}
		goto next_loop;
	      end_loop_1:
		minimum_value = Qnil;
	      end_2:;
	    }
	    else
		minimum_value = Nil;
	    return return_history_value(variable,minimum_value,
		    string_constant_9,T,value_requested_by_simulator_qm,T,
		    interval_ok_qm,
		    type_specification_of_variable_or_parameter_value(variable));
	}
    }
}

static Object Qget_averaged_value;  /* get-averaged-value */

static Object string_constant_10;  /* "average" */

/* GET-AVERAGED-VALUE */
Object get_averaged_value(variable,value_requested_by_simulator_qm,
	    interval_begin_time,interval_end_time)
    Object variable, value_requested_by_simulator_qm, interval_begin_time;
    Object interval_end_time;
{
    Object symbol, top_of_stack, message_1, history_being_kept_qm;
    Object referencing_simulation_history_qm, sub_class_bit_vector;
    Object simulation_subtable_qm, simulation_stored_histories_qm;
    Object value_history_cascaded_ring_buffer;
    Object variable_or_parameter_stored_histories_qm;
    Object value_history_ring_buffer_or_cascade, temp_1;
    Object oldest_active_element_index, newest_active_element_index;
    Object interval_ok_qm, in_interval_qm, sum, number_of_values;
    Object element_index, result_sum, done_qm, gensymed_symbol_3;
    Object gensymed_symbol_4, gensymed_symbol_5, temp_accumulated_value_1;
    Object temp_accumulated_value_2, storage_time, vector_1;
    Object managed_number_or_value, next_history_value;
    Object store_managed_number_arg, averaged_value;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, i, ab_loop_bind_;
    char temp;
    double temp_2, temp_3;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(148,97);
    if (T) {
	symbol = ISVREF(variable,(SI_Long)20L);
	temp =  !(EQ(symbol,Qnumber) || EQ(symbol,Qinteger) || EQ(symbol,
		Qfloat) || EQ(symbol,Qlong) || 
		lookup_global_or_kb_specific_property_value(symbol,
		Numeric_data_type_gkbprop));
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_2,
		Qget_averaged_value,variable);
	raw_stack_error_named_error(top_of_stack,message_1);
	return VALUES_1(Nil);
    }
    else {
	history_being_kept_qm = Nil;
	referencing_simulation_history_qm = value_requested_by_simulator_qm;
	if (value_requested_by_simulator_qm) {
	    sub_class_bit_vector = ISVREF(ISVREF(variable,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Variable_class_description,(SI_Long)18L));
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
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    simulation_subtable_qm = get_lookup_slot_value(variable,
		    Qsimulation_details);
	    simulation_stored_histories_qm = simulation_subtable_qm ? 
		    ISVREF(simulation_subtable_qm,(SI_Long)20L) : Nil;
	    history_being_kept_qm =  ! !(simulation_subtable_qm && 
		    ISVREF(simulation_subtable_qm,(SI_Long)21L)) ? T : Nil;
	    value_history_cascaded_ring_buffer =  
		    !TRUEP(history_being_kept_qm) ||  
		    !TRUEP(simulation_stored_histories_qm) || 
		    cascaded_ring_buffer_empty_qm(simulation_stored_histories_qm) 
		    ? Nil : simulation_stored_histories_qm;
	}
	else {
	    variable_or_parameter_stored_histories_qm = ISVREF(variable,
		    (SI_Long)24L);
	    referencing_simulation_history_qm = Nil;
	    history_being_kept_qm =  ! !TRUEP(ISVREF(variable,
		    (SI_Long)25L)) ? T : Nil;
	    value_history_cascaded_ring_buffer =  
		    !TRUEP(history_being_kept_qm) ||  
		    !TRUEP(ISVREF(variable,(SI_Long)24L)) || 
		    cascaded_ring_buffer_empty_qm(variable_or_parameter_stored_histories_qm) 
		    ? Nil : variable_or_parameter_stored_histories_qm;
	}
	value_history_ring_buffer_or_cascade = Nil;
	if ( !TRUEP(value_history_cascaded_ring_buffer) && ( 
		!TRUEP(history_being_kept_qm) || T))
	    return VALUES_1(Nil);
	else {
	    if (value_history_cascaded_ring_buffer) {
		temp_1 = ISVREF(value_history_cascaded_ring_buffer,
			(SI_Long)4L);
		value_history_ring_buffer_or_cascade = CAR(temp_1);
	    }
	    else
		value_history_ring_buffer_or_cascade = Nil;
	    oldest_active_element_index = 
		    ISVREF(value_history_ring_buffer_or_cascade,(SI_Long)2L);
	    newest_active_element_index = 
		    ISVREF(value_history_ring_buffer_or_cascade,(SI_Long)1L);
	    interval_ok_qm =  !TRUEP(nanp(interval_begin_time)) &&  
		    !TRUEP(nanp(interval_end_time)) ? 
		    (NUM_LE(interval_begin_time,interval_end_time) ? T : 
		    Nil) : Qnil;
	    if (interval_ok_qm) {
		in_interval_qm = Nil;
		sum = Nil;
		number_of_values = FIX((SI_Long)0L);
		element_index = oldest_active_element_index;
		result_sum = Nil;
		done_qm = Nil;
	      next_loop:
		gensymed_symbol_3 = interval_end_time;
		gensymed_symbol_4 = value_history_ring_buffer_or_cascade;
		gensymed_symbol_5 = value_history_cascaded_ring_buffer;
		temp_accumulated_value_1 = Nil;
		temp_accumulated_value_2 = Nil;
		if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(sum) != (SI_Long)0L 
			    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sum)) == 
			    (SI_Long)1L)
			temp_accumulated_value_1 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(sum,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(sum) != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sum)) == 
			    (SI_Long)1L)
			temp_accumulated_value_1 = aref1(sum,FIX((SI_Long)0L));
		    else
			temp_accumulated_value_1 = sum;
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(number_of_values) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(number_of_values)) 
			    == (SI_Long)1L)
			temp_accumulated_value_2 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(number_of_values,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(number_of_values) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(number_of_values)) 
			    == (SI_Long)1L)
			temp_accumulated_value_2 = aref1(number_of_values,
				FIX((SI_Long)0L));
		    else
			temp_accumulated_value_2 = number_of_values;
		    storage_time = Nil;
		    i = (SI_Long)1L;
		    ab_loop_bind_ = IFIX(Max_number_of_history_evaluations);
		  next_loop_1:
		    if (i > ab_loop_bind_)
			goto end_loop;
		    storage_time = 
			    get_history_current_time(gensymed_symbol_5,
			    element_index,referencing_simulation_history_qm);
		    if ( !TRUEP(in_interval_qm)) {
			if (NUM_GE(storage_time,interval_begin_time) &&  
				!NUM_GT(storage_time,gensymed_symbol_3)) {
			    in_interval_qm = T;
			    vector_1 = ISVREF(gensymed_symbol_4,(SI_Long)6L);
			    if (SIMPLE_VECTOR_P(vector_1) && 
				    EQ(ISVREF(vector_1,(SI_Long)0L),
				    Managed_array_unique_marker)) {
				managed_number_or_value = 
					FIXNUM_LE(ISVREF(vector_1,
					(SI_Long)1L),
					Maximum_in_place_array_size) ? 
					ISVREF(vector_1,
					IFIX(FIXNUM_ADD(element_index,
					Managed_array_index_offset))) : 
					ISVREF(ISVREF(vector_1,
					(IFIX(element_index) >>  -  - 
					(SI_Long)10L) + (SI_Long)2L),
					IFIX(element_index) & (SI_Long)1023L);
				if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					== (SI_Long)1L)
				    next_history_value = 
					    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
					    (SI_Long)0L));
				else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					== (SI_Long)1L)
				    next_history_value = 
					    aref1(managed_number_or_value,
					    FIX((SI_Long)0L));
				else if (text_string_p(managed_number_or_value))
				    next_history_value = 
					    copy_text_string(managed_number_or_value);
				else
				    next_history_value = 
					    managed_number_or_value;
			    }
			    else
				next_history_value = 
					DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
					(IFIX(element_index) >>  -  - 
					(SI_Long)10L) + (SI_Long)2L),
					IFIX(element_index) & (SI_Long)1023L));
			    temp_accumulated_value_1 = next_history_value;
			    temp_accumulated_value_2 = 
				    add1(temp_accumulated_value_2);
			}
		    }
		    else {
			vector_1 = ISVREF(gensymed_symbol_4,(SI_Long)6L);
			if (SIMPLE_VECTOR_P(vector_1) && 
				EQ(ISVREF(vector_1,(SI_Long)0L),
				Managed_array_unique_marker)) {
			    managed_number_or_value = 
				    FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
				    Maximum_in_place_array_size) ? 
				    ISVREF(vector_1,
				    IFIX(FIXNUM_ADD(element_index,
				    Managed_array_index_offset))) : 
				    ISVREF(ISVREF(vector_1,
				    (IFIX(element_index) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    IFIX(element_index) & (SI_Long)1023L);
			    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
				    != (SI_Long)0L && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				    == (SI_Long)1L)
				next_history_value = 
					DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
					(SI_Long)0L));
			    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
				    != (SI_Long)0L && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				    == (SI_Long)1L)
				next_history_value = 
					aref1(managed_number_or_value,
					FIX((SI_Long)0L));
			    else if (text_string_p(managed_number_or_value))
				next_history_value = 
					copy_text_string(managed_number_or_value);
			    else
				next_history_value = managed_number_or_value;
			}
			else
			    next_history_value = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
				    (IFIX(element_index) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    IFIX(element_index) & (SI_Long)1023L));
			if (NUM_GT(storage_time,gensymed_symbol_3)) {
			    if (temp_accumulated_value_1) {
				store_managed_number_arg = 
					temp_accumulated_value_1;
				sum = store_managed_number_function(sum,
					store_managed_number_arg);
			    }
			    if (temp_accumulated_value_2) {
				store_managed_number_arg = 
					temp_accumulated_value_2;
				number_of_values = 
					store_managed_number_function(number_of_values,
					store_managed_number_arg);
			    }
			    done_qm = T;
			    goto end_1;
			}
			else {
			    temp_accumulated_value_1 = 
				    add(temp_accumulated_value_1,
				    next_history_value);
			    temp_accumulated_value_2 = 
				    FIXNUM_ADD1(temp_accumulated_value_2);
			}
		    }
		    if (NUM_EQ(storage_time,gensymed_symbol_3) || 
			    FIXNUM_EQ(element_index,
			    newest_active_element_index)) {
			if (temp_accumulated_value_1) {
			    store_managed_number_arg = 
				    temp_accumulated_value_1;
			    sum = store_managed_number_function(sum,
				    store_managed_number_arg);
			}
			if (temp_accumulated_value_2) {
			    store_managed_number_arg = 
				    temp_accumulated_value_2;
			    number_of_values = 
				    store_managed_number_function(number_of_values,
				    store_managed_number_arg);
			}
			done_qm = T;
			goto end_1;
		    }
		    element_index = FIXNUM_EQ(element_index,
			    FIXNUM_SUB1(ISVREF(gensymed_symbol_4,
			    (SI_Long)4L))) ? FIX((SI_Long)0L) : 
			    FIXNUM_ADD1(element_index);
		    i = i + (SI_Long)1L;
		    goto next_loop_1;
		  end_loop:
		    if (temp_accumulated_value_1) {
			store_managed_number_arg = temp_accumulated_value_1;
			sum = store_managed_number_function(sum,
				store_managed_number_arg);
		    }
		    if (temp_accumulated_value_2) {
			store_managed_number_arg = temp_accumulated_value_2;
			number_of_values = 
				store_managed_number_function(number_of_values,
				store_managed_number_arg);
		    }
		    done_qm = Nil;
		    goto end_1;
		    done_qm = Qnil;
		  end_1:;
		}
		POP_LOCAL_ALLOCATION(0,0);
		if (done_qm) {
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(sum) != (SI_Long)0L 
			    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sum)) == 
			    (SI_Long)1L)
			result_sum = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(sum,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(sum) != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sum)) == 
			    (SI_Long)1L)
			result_sum = aref1(sum,FIX((SI_Long)0L));
		    else
			result_sum = sum;
		    sum = reclaim_managed_number_or_value_function(sum);
		    if (result_sum) {
			if (NUMBERP(result_sum)) {
			    temp_1 = lfloat(result_sum,float_constant);
			    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
			    if (INLINE_DOUBLE_FLOAT_VECTOR_P(number_of_values) 
				    != (SI_Long)0L && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(number_of_values)) 
				    == (SI_Long)1L)
				temp_1 = 
					DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(number_of_values,
					(SI_Long)0L));
			    else if (INLINE_LONG_VECTOR_P(number_of_values) 
				    != (SI_Long)0L && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(number_of_values)) 
				    == (SI_Long)1L)
				temp_1 = aref1(number_of_values,
					FIX((SI_Long)0L));
			    else
				temp_1 = number_of_values;
			    temp_1 = lfloat(temp_1,float_constant);
			    temp_3 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
			    averaged_value = DOUBLE_TO_DOUBLE_FLOAT(temp_2 
				    / temp_3);
			    goto end_2;
			}
			else {
			    averaged_value = result_sum;
			    goto end_2;
			}
		    }
		    else {
			averaged_value = Nil;
			goto end_2;
		    }
		}
		goto next_loop;
	      end_loop_1:
		averaged_value = Qnil;
	      end_2:;
	    }
	    else
		averaged_value = Nil;
	    return return_history_value(variable,averaged_value,
		    string_constant_10,T,value_requested_by_simulator_qm,T,
		    interval_ok_qm,
		    type_specification_of_variable_or_parameter_value(variable));
	}
    }
}

static Object Qget_sum_of_values;  /* get-sum-of-values */

static Object string_constant_11;  /* "sum" */

/* GET-SUM-OF-VALUES */
Object get_sum_of_values(variable,value_requested_by_simulator_qm,
	    interval_begin_time,interval_end_time)
    Object variable, value_requested_by_simulator_qm, interval_begin_time;
    Object interval_end_time;
{
    Object symbol, top_of_stack, message_1, history_being_kept_qm;
    Object referencing_simulation_history_qm, sub_class_bit_vector;
    Object simulation_subtable_qm, simulation_stored_histories_qm;
    Object value_history_cascaded_ring_buffer;
    Object variable_or_parameter_stored_histories_qm;
    Object value_history_ring_buffer_or_cascade, temp_1;
    Object oldest_active_element_index, newest_active_element_index;
    Object interval_ok_qm, in_interval_qm, sum, element_index, result_sum;
    Object done_qm, gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    Object temp_accumulated_value_1, storage_time, vector_1;
    Object managed_number_or_value, next_history_value;
    Object store_managed_number_arg, sum_of_values;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, i, ab_loop_bind_;
    char temp;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(148,98);
    if (T) {
	symbol = ISVREF(variable,(SI_Long)20L);
	temp =  !(EQ(symbol,Qnumber) || EQ(symbol,Qinteger) || EQ(symbol,
		Qfloat) || EQ(symbol,Qlong) || 
		lookup_global_or_kb_specific_property_value(symbol,
		Numeric_data_type_gkbprop));
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_2,
		Qget_sum_of_values,variable);
	raw_stack_error_named_error(top_of_stack,message_1);
	return VALUES_1(Nil);
    }
    else {
	history_being_kept_qm = Nil;
	referencing_simulation_history_qm = value_requested_by_simulator_qm;
	if (value_requested_by_simulator_qm) {
	    sub_class_bit_vector = ISVREF(ISVREF(variable,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Variable_class_description,(SI_Long)18L));
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
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    simulation_subtable_qm = get_lookup_slot_value(variable,
		    Qsimulation_details);
	    simulation_stored_histories_qm = simulation_subtable_qm ? 
		    ISVREF(simulation_subtable_qm,(SI_Long)20L) : Nil;
	    history_being_kept_qm =  ! !(simulation_subtable_qm && 
		    ISVREF(simulation_subtable_qm,(SI_Long)21L)) ? T : Nil;
	    value_history_cascaded_ring_buffer =  
		    !TRUEP(history_being_kept_qm) ||  
		    !TRUEP(simulation_stored_histories_qm) || 
		    cascaded_ring_buffer_empty_qm(simulation_stored_histories_qm) 
		    ? Nil : simulation_stored_histories_qm;
	}
	else {
	    variable_or_parameter_stored_histories_qm = ISVREF(variable,
		    (SI_Long)24L);
	    referencing_simulation_history_qm = Nil;
	    history_being_kept_qm =  ! !TRUEP(ISVREF(variable,
		    (SI_Long)25L)) ? T : Nil;
	    value_history_cascaded_ring_buffer =  
		    !TRUEP(history_being_kept_qm) ||  
		    !TRUEP(ISVREF(variable,(SI_Long)24L)) || 
		    cascaded_ring_buffer_empty_qm(variable_or_parameter_stored_histories_qm) 
		    ? Nil : variable_or_parameter_stored_histories_qm;
	}
	value_history_ring_buffer_or_cascade = Nil;
	if ( !TRUEP(value_history_cascaded_ring_buffer) && ( 
		!TRUEP(history_being_kept_qm) || Nil))
	    return VALUES_1(Nil);
	else {
	    if (value_history_cascaded_ring_buffer) {
		temp_1 = ISVREF(value_history_cascaded_ring_buffer,
			(SI_Long)4L);
		value_history_ring_buffer_or_cascade = CAR(temp_1);
	    }
	    else
		value_history_ring_buffer_or_cascade = Nil;
	    oldest_active_element_index = 
		    ISVREF(value_history_ring_buffer_or_cascade,(SI_Long)2L);
	    newest_active_element_index = 
		    ISVREF(value_history_ring_buffer_or_cascade,(SI_Long)1L);
	    interval_ok_qm =  !TRUEP(nanp(interval_begin_time)) &&  
		    !TRUEP(nanp(interval_end_time)) ? 
		    (NUM_LE(interval_begin_time,interval_end_time) ? T : 
		    Nil) : Qnil;
	    if (interval_ok_qm) {
		in_interval_qm = Nil;
		sum = Nil;
		element_index = oldest_active_element_index;
		result_sum = Nil;
		done_qm = Nil;
	      next_loop:
		gensymed_symbol_3 = interval_end_time;
		gensymed_symbol_4 = value_history_ring_buffer_or_cascade;
		gensymed_symbol_5 = value_history_cascaded_ring_buffer;
		temp_accumulated_value_1 = Nil;
		if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(sum) != (SI_Long)0L 
			    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sum)) == 
			    (SI_Long)1L)
			temp_accumulated_value_1 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(sum,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(sum) != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sum)) == 
			    (SI_Long)1L)
			temp_accumulated_value_1 = aref1(sum,FIX((SI_Long)0L));
		    else
			temp_accumulated_value_1 = sum;
		    storage_time = Nil;
		    i = (SI_Long)1L;
		    ab_loop_bind_ = IFIX(Max_number_of_history_evaluations);
		  next_loop_1:
		    if (i > ab_loop_bind_)
			goto end_loop;
		    storage_time = 
			    get_history_current_time(gensymed_symbol_5,
			    element_index,referencing_simulation_history_qm);
		    if ( !TRUEP(in_interval_qm)) {
			if (NUM_GE(storage_time,interval_begin_time) &&  
				!NUM_GT(storage_time,gensymed_symbol_3)) {
			    in_interval_qm = T;
			    vector_1 = ISVREF(gensymed_symbol_4,(SI_Long)6L);
			    if (SIMPLE_VECTOR_P(vector_1) && 
				    EQ(ISVREF(vector_1,(SI_Long)0L),
				    Managed_array_unique_marker)) {
				managed_number_or_value = 
					FIXNUM_LE(ISVREF(vector_1,
					(SI_Long)1L),
					Maximum_in_place_array_size) ? 
					ISVREF(vector_1,
					IFIX(FIXNUM_ADD(element_index,
					Managed_array_index_offset))) : 
					ISVREF(ISVREF(vector_1,
					(IFIX(element_index) >>  -  - 
					(SI_Long)10L) + (SI_Long)2L),
					IFIX(element_index) & (SI_Long)1023L);
				if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					== (SI_Long)1L)
				    next_history_value = 
					    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
					    (SI_Long)0L));
				else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					== (SI_Long)1L)
				    next_history_value = 
					    aref1(managed_number_or_value,
					    FIX((SI_Long)0L));
				else if (text_string_p(managed_number_or_value))
				    next_history_value = 
					    copy_text_string(managed_number_or_value);
				else
				    next_history_value = 
					    managed_number_or_value;
			    }
			    else
				next_history_value = 
					DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
					(IFIX(element_index) >>  -  - 
					(SI_Long)10L) + (SI_Long)2L),
					IFIX(element_index) & (SI_Long)1023L));
			    temp_accumulated_value_1 = next_history_value;
			}
		    }
		    else {
			vector_1 = ISVREF(gensymed_symbol_4,(SI_Long)6L);
			if (SIMPLE_VECTOR_P(vector_1) && 
				EQ(ISVREF(vector_1,(SI_Long)0L),
				Managed_array_unique_marker)) {
			    managed_number_or_value = 
				    FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
				    Maximum_in_place_array_size) ? 
				    ISVREF(vector_1,
				    IFIX(FIXNUM_ADD(element_index,
				    Managed_array_index_offset))) : 
				    ISVREF(ISVREF(vector_1,
				    (IFIX(element_index) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    IFIX(element_index) & (SI_Long)1023L);
			    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
				    != (SI_Long)0L && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				    == (SI_Long)1L)
				next_history_value = 
					DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
					(SI_Long)0L));
			    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
				    != (SI_Long)0L && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				    == (SI_Long)1L)
				next_history_value = 
					aref1(managed_number_or_value,
					FIX((SI_Long)0L));
			    else if (text_string_p(managed_number_or_value))
				next_history_value = 
					copy_text_string(managed_number_or_value);
			    else
				next_history_value = managed_number_or_value;
			}
			else
			    next_history_value = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
				    (IFIX(element_index) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    IFIX(element_index) & (SI_Long)1023L));
			if (NUM_GT(storage_time,gensymed_symbol_3)) {
			    if (temp_accumulated_value_1) {
				store_managed_number_arg = 
					temp_accumulated_value_1;
				sum = store_managed_number_function(sum,
					store_managed_number_arg);
			    }
			    done_qm = T;
			    goto end_1;
			}
			else
			    temp_accumulated_value_1 = 
				    add(temp_accumulated_value_1,
				    next_history_value);
		    }
		    if (NUM_EQ(storage_time,gensymed_symbol_3) || 
			    FIXNUM_EQ(element_index,
			    newest_active_element_index)) {
			if (temp_accumulated_value_1) {
			    store_managed_number_arg = 
				    temp_accumulated_value_1;
			    sum = store_managed_number_function(sum,
				    store_managed_number_arg);
			}
			done_qm = T;
			goto end_1;
		    }
		    element_index = FIXNUM_EQ(element_index,
			    FIXNUM_SUB1(ISVREF(gensymed_symbol_4,
			    (SI_Long)4L))) ? FIX((SI_Long)0L) : 
			    FIXNUM_ADD1(element_index);
		    i = i + (SI_Long)1L;
		    goto next_loop_1;
		  end_loop:
		    if (temp_accumulated_value_1) {
			store_managed_number_arg = temp_accumulated_value_1;
			sum = store_managed_number_function(sum,
				store_managed_number_arg);
		    }
		    done_qm = Nil;
		    goto end_1;
		    done_qm = Qnil;
		  end_1:;
		}
		POP_LOCAL_ALLOCATION(0,0);
		if (done_qm) {
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(sum) != (SI_Long)0L 
			    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sum)) == 
			    (SI_Long)1L)
			result_sum = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(sum,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(sum) != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sum)) == 
			    (SI_Long)1L)
			result_sum = aref1(sum,FIX((SI_Long)0L));
		    else
			result_sum = sum;
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(sum) != (SI_Long)0L 
			    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sum)) == 
			    (SI_Long)1L)
			reclaim_managed_simple_float_array_of_length_1(sum);
		    if (NUMBERP(result_sum)) {
			sum_of_values = lfloat(result_sum,float_constant);
			goto end_2;
		    }
		    else {
			sum_of_values = float_constant;
			goto end_2;
		    }
		}
		goto next_loop;
	      end_loop_1:
		sum_of_values = Qnil;
	      end_2:;
	    }
	    else
		sum_of_values = Nil;
	    return return_history_value(variable,sum_of_values,
		    string_constant_11,T,value_requested_by_simulator_qm,T,
		    interval_ok_qm,
		    type_specification_of_variable_or_parameter_value(variable));
	}
    }
}

static Object Qget_standard_deviation_of_value;  /* get-standard-deviation-of-value */

static Object string_constant_12;  /* "standard deviation" */

/* GET-STANDARD-DEVIATION-OF-VALUE */
Object get_standard_deviation_of_value(variable,
	    value_requested_by_simulator_qm,interval_begin_time,
	    interval_end_time)
    Object variable, value_requested_by_simulator_qm, interval_begin_time;
    Object interval_end_time;
{
    Object symbol, top_of_stack, message_1, history_being_kept_qm;
    Object referencing_simulation_history_qm, sub_class_bit_vector;
    Object simulation_subtable_qm, simulation_stored_histories_qm;
    Object value_history_cascaded_ring_buffer;
    Object variable_or_parameter_stored_histories_qm;
    Object value_history_ring_buffer_or_cascade, temp_1;
    Object oldest_active_element_index, newest_active_element_index;
    Object interval_ok_qm, in_interval_qm, sum, square_sum, number_of_values;
    Object element_index, result_sum, result_square_sum, done_qm;
    Object gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    Object temp_accumulated_value_1, temp_accumulated_value_2;
    Object temp_accumulated_value_3, storage_time, vector_1;
    Object managed_number_or_value, next_history_value;
    Object store_managed_number_arg, float_number_of_values;
    Object standard_deviation;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, i, ab_loop_bind_;
    char temp;
    double temp_2, temp_3, average;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(148,99);
    if (T) {
	symbol = ISVREF(variable,(SI_Long)20L);
	temp =  !(EQ(symbol,Qnumber) || EQ(symbol,Qinteger) || EQ(symbol,
		Qfloat) || EQ(symbol,Qlong) || 
		lookup_global_or_kb_specific_property_value(symbol,
		Numeric_data_type_gkbprop));
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_2,
		Qget_standard_deviation_of_value,variable);
	raw_stack_error_named_error(top_of_stack,message_1);
	return VALUES_1(Nil);
    }
    else {
	history_being_kept_qm = Nil;
	referencing_simulation_history_qm = value_requested_by_simulator_qm;
	if (value_requested_by_simulator_qm) {
	    sub_class_bit_vector = ISVREF(ISVREF(variable,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Variable_class_description,(SI_Long)18L));
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
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    simulation_subtable_qm = get_lookup_slot_value(variable,
		    Qsimulation_details);
	    simulation_stored_histories_qm = simulation_subtable_qm ? 
		    ISVREF(simulation_subtable_qm,(SI_Long)20L) : Nil;
	    history_being_kept_qm =  ! !(simulation_subtable_qm && 
		    ISVREF(simulation_subtable_qm,(SI_Long)21L)) ? T : Nil;
	    value_history_cascaded_ring_buffer =  
		    !TRUEP(history_being_kept_qm) ||  
		    !TRUEP(simulation_stored_histories_qm) || 
		    cascaded_ring_buffer_empty_qm(simulation_stored_histories_qm) 
		    ? Nil : simulation_stored_histories_qm;
	}
	else {
	    variable_or_parameter_stored_histories_qm = ISVREF(variable,
		    (SI_Long)24L);
	    referencing_simulation_history_qm = Nil;
	    history_being_kept_qm =  ! !TRUEP(ISVREF(variable,
		    (SI_Long)25L)) ? T : Nil;
	    value_history_cascaded_ring_buffer =  
		    !TRUEP(history_being_kept_qm) ||  
		    !TRUEP(ISVREF(variable,(SI_Long)24L)) || 
		    cascaded_ring_buffer_empty_qm(variable_or_parameter_stored_histories_qm) 
		    ? Nil : variable_or_parameter_stored_histories_qm;
	}
	value_history_ring_buffer_or_cascade = Nil;
	if ( !TRUEP(value_history_cascaded_ring_buffer) && ( 
		!TRUEP(history_being_kept_qm) || T))
	    return VALUES_1(Nil);
	else {
	    if (value_history_cascaded_ring_buffer) {
		temp_1 = ISVREF(value_history_cascaded_ring_buffer,
			(SI_Long)4L);
		value_history_ring_buffer_or_cascade = CAR(temp_1);
	    }
	    else
		value_history_ring_buffer_or_cascade = Nil;
	    oldest_active_element_index = 
		    ISVREF(value_history_ring_buffer_or_cascade,(SI_Long)2L);
	    newest_active_element_index = 
		    ISVREF(value_history_ring_buffer_or_cascade,(SI_Long)1L);
	    interval_ok_qm =  !TRUEP(nanp(interval_begin_time)) &&  
		    !TRUEP(nanp(interval_end_time)) ? 
		    (NUM_LE(interval_begin_time,interval_end_time) ? T : 
		    Nil) : Qnil;
	    if (interval_ok_qm) {
		in_interval_qm = Nil;
		sum = Nil;
		square_sum = Nil;
		number_of_values = FIX((SI_Long)0L);
		element_index = oldest_active_element_index;
		result_sum = Nil;
		result_square_sum = Nil;
		done_qm = Nil;
	      next_loop:
		gensymed_symbol_3 = interval_end_time;
		gensymed_symbol_4 = value_history_ring_buffer_or_cascade;
		gensymed_symbol_5 = value_history_cascaded_ring_buffer;
		temp_accumulated_value_1 = Nil;
		temp_accumulated_value_2 = Nil;
		temp_accumulated_value_3 = Nil;
		if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(sum) != (SI_Long)0L 
			    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sum)) == 
			    (SI_Long)1L)
			temp_accumulated_value_1 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(sum,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(sum) != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sum)) == 
			    (SI_Long)1L)
			temp_accumulated_value_1 = aref1(sum,FIX((SI_Long)0L));
		    else
			temp_accumulated_value_1 = sum;
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(square_sum) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(square_sum)) == 
			    (SI_Long)1L)
			temp_accumulated_value_2 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(square_sum,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(square_sum) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(square_sum)) == 
			    (SI_Long)1L)
			temp_accumulated_value_2 = aref1(square_sum,
				FIX((SI_Long)0L));
		    else
			temp_accumulated_value_2 = square_sum;
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(number_of_values) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(number_of_values)) 
			    == (SI_Long)1L)
			temp_accumulated_value_3 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(number_of_values,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(number_of_values) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(number_of_values)) 
			    == (SI_Long)1L)
			temp_accumulated_value_3 = aref1(number_of_values,
				FIX((SI_Long)0L));
		    else
			temp_accumulated_value_3 = number_of_values;
		    storage_time = Nil;
		    i = (SI_Long)1L;
		    ab_loop_bind_ = IFIX(Max_number_of_history_evaluations);
		  next_loop_1:
		    if (i > ab_loop_bind_)
			goto end_loop;
		    storage_time = 
			    get_history_current_time(gensymed_symbol_5,
			    element_index,referencing_simulation_history_qm);
		    if ( !TRUEP(in_interval_qm)) {
			if (NUM_GE(storage_time,interval_begin_time) &&  
				!NUM_GT(storage_time,gensymed_symbol_3)) {
			    in_interval_qm = T;
			    vector_1 = ISVREF(gensymed_symbol_4,(SI_Long)6L);
			    if (SIMPLE_VECTOR_P(vector_1) && 
				    EQ(ISVREF(vector_1,(SI_Long)0L),
				    Managed_array_unique_marker)) {
				managed_number_or_value = 
					FIXNUM_LE(ISVREF(vector_1,
					(SI_Long)1L),
					Maximum_in_place_array_size) ? 
					ISVREF(vector_1,
					IFIX(FIXNUM_ADD(element_index,
					Managed_array_index_offset))) : 
					ISVREF(ISVREF(vector_1,
					(IFIX(element_index) >>  -  - 
					(SI_Long)10L) + (SI_Long)2L),
					IFIX(element_index) & (SI_Long)1023L);
				if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					== (SI_Long)1L)
				    next_history_value = 
					    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
					    (SI_Long)0L));
				else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					== (SI_Long)1L)
				    next_history_value = 
					    aref1(managed_number_or_value,
					    FIX((SI_Long)0L));
				else if (text_string_p(managed_number_or_value))
				    next_history_value = 
					    copy_text_string(managed_number_or_value);
				else
				    next_history_value = 
					    managed_number_or_value;
			    }
			    else
				next_history_value = 
					DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
					(IFIX(element_index) >>  -  - 
					(SI_Long)10L) + (SI_Long)2L),
					IFIX(element_index) & (SI_Long)1023L));
			    temp_accumulated_value_1 = next_history_value;
			    temp_accumulated_value_2 = 
				    ltimes(next_history_value,
				    next_history_value);
			    temp_accumulated_value_3 = 
				    FIXNUM_ADD1(temp_accumulated_value_3);
			}
		    }
		    else {
			vector_1 = ISVREF(gensymed_symbol_4,(SI_Long)6L);
			if (SIMPLE_VECTOR_P(vector_1) && 
				EQ(ISVREF(vector_1,(SI_Long)0L),
				Managed_array_unique_marker)) {
			    managed_number_or_value = 
				    FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
				    Maximum_in_place_array_size) ? 
				    ISVREF(vector_1,
				    IFIX(FIXNUM_ADD(element_index,
				    Managed_array_index_offset))) : 
				    ISVREF(ISVREF(vector_1,
				    (IFIX(element_index) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    IFIX(element_index) & (SI_Long)1023L);
			    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
				    != (SI_Long)0L && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				    == (SI_Long)1L)
				next_history_value = 
					DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
					(SI_Long)0L));
			    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
				    != (SI_Long)0L && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				    == (SI_Long)1L)
				next_history_value = 
					aref1(managed_number_or_value,
					FIX((SI_Long)0L));
			    else if (text_string_p(managed_number_or_value))
				next_history_value = 
					copy_text_string(managed_number_or_value);
			    else
				next_history_value = managed_number_or_value;
			}
			else
			    next_history_value = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
				    (IFIX(element_index) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    IFIX(element_index) & (SI_Long)1023L));
			if (NUM_GT(storage_time,gensymed_symbol_3)) {
			    if (temp_accumulated_value_1) {
				store_managed_number_arg = 
					temp_accumulated_value_1;
				sum = store_managed_number_function(sum,
					store_managed_number_arg);
			    }
			    if (temp_accumulated_value_2) {
				store_managed_number_arg = 
					temp_accumulated_value_2;
				square_sum = 
					store_managed_number_function(square_sum,
					store_managed_number_arg);
			    }
			    if (temp_accumulated_value_3) {
				store_managed_number_arg = 
					temp_accumulated_value_3;
				number_of_values = 
					store_managed_number_function(number_of_values,
					store_managed_number_arg);
			    }
			    done_qm = T;
			    goto end_1;
			}
			else {
			    temp_accumulated_value_1 = 
				    add(temp_accumulated_value_1,
				    next_history_value);
			    temp_accumulated_value_2 = 
				    add(temp_accumulated_value_2,
				    ltimes(next_history_value,
				    next_history_value));
			    temp_accumulated_value_3 = 
				    FIXNUM_ADD1(temp_accumulated_value_3);
			}
		    }
		    if (NUM_EQ(storage_time,gensymed_symbol_3) || 
			    FIXNUM_EQ(element_index,
			    newest_active_element_index)) {
			if (temp_accumulated_value_1) {
			    store_managed_number_arg = 
				    temp_accumulated_value_1;
			    sum = store_managed_number_function(sum,
				    store_managed_number_arg);
			}
			if (temp_accumulated_value_2) {
			    store_managed_number_arg = 
				    temp_accumulated_value_2;
			    square_sum = 
				    store_managed_number_function(square_sum,
				    store_managed_number_arg);
			}
			if (temp_accumulated_value_3) {
			    store_managed_number_arg = 
				    temp_accumulated_value_3;
			    number_of_values = 
				    store_managed_number_function(number_of_values,
				    store_managed_number_arg);
			}
			done_qm = T;
			goto end_1;
		    }
		    element_index = FIXNUM_EQ(element_index,
			    FIXNUM_SUB1(ISVREF(gensymed_symbol_4,
			    (SI_Long)4L))) ? FIX((SI_Long)0L) : 
			    FIXNUM_ADD1(element_index);
		    i = i + (SI_Long)1L;
		    goto next_loop_1;
		  end_loop:
		    if (temp_accumulated_value_1) {
			store_managed_number_arg = temp_accumulated_value_1;
			sum = store_managed_number_function(sum,
				store_managed_number_arg);
		    }
		    if (temp_accumulated_value_2) {
			store_managed_number_arg = temp_accumulated_value_2;
			square_sum = 
				store_managed_number_function(square_sum,
				store_managed_number_arg);
		    }
		    if (temp_accumulated_value_3) {
			store_managed_number_arg = temp_accumulated_value_3;
			number_of_values = 
				store_managed_number_function(number_of_values,
				store_managed_number_arg);
		    }
		    done_qm = Nil;
		    goto end_1;
		    done_qm = Qnil;
		  end_1:;
		}
		POP_LOCAL_ALLOCATION(0,0);
		if (done_qm) {
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(sum) != (SI_Long)0L 
			    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sum)) == 
			    (SI_Long)1L)
			result_sum = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(sum,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(sum) != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sum)) == 
			    (SI_Long)1L)
			result_sum = aref1(sum,FIX((SI_Long)0L));
		    else
			result_sum = sum;
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(square_sum) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(square_sum)) == 
			    (SI_Long)1L)
			result_square_sum = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(square_sum,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(square_sum) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(square_sum)) == 
			    (SI_Long)1L)
			result_square_sum = aref1(square_sum,FIX((SI_Long)0L));
		    else
			result_square_sum = square_sum;
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(sum) != (SI_Long)0L 
			    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sum)) == 
			    (SI_Long)1L)
			reclaim_managed_simple_float_array_of_length_1(sum);
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(square_sum) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(square_sum)) == 
			    (SI_Long)1L)
			reclaim_managed_simple_float_array_of_length_1(square_sum);
		    if (NUMBERP(result_sum)) {
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(number_of_values) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(number_of_values)) 
				== (SI_Long)1L)
			    temp_1 = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(number_of_values,
				    (SI_Long)0L));
			else if (INLINE_LONG_VECTOR_P(number_of_values) != 
				(SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(number_of_values)) 
				== (SI_Long)1L)
			    temp_1 = aref1(number_of_values,FIX((SI_Long)0L));
			else
			    temp_1 = number_of_values;
			float_number_of_values = lfloat(temp_1,float_constant);
			temp_1 = lfloat(result_sum,float_constant);
			temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
			temp_3 = 
				DOUBLE_FLOAT_TO_DOUBLE(float_number_of_values);
			average = temp_2 / temp_3;
			temp_1 = lfloat(result_square_sum,float_constant);
			temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
			temp_3 = 
				DOUBLE_FLOAT_TO_DOUBLE(float_number_of_values);
			temp_3 = temp_2 / temp_3 - average * average;
			standard_deviation = 
				DOUBLE_TO_DOUBLE_FLOAT(sqrt(ABS(temp_3)));
			goto end_2;
			goto end_2;
		    }
		    else {
			standard_deviation = Nil;
			goto end_2;
		    }
		}
		goto next_loop;
	      end_loop_1:
		standard_deviation = Qnil;
	      end_2:;
	    }
	    else
		standard_deviation = Nil;
	    return return_history_value(variable,standard_deviation,
		    string_constant_12,T,value_requested_by_simulator_qm,T,
		    interval_ok_qm,
		    type_specification_of_variable_or_parameter_value(variable));
	}
    }
}

static Object Qget_rate_of_change_of_value;  /* get-rate-of-change-of-value */

static Object string_constant_13;  /* "rate of change" */

/* GET-RATE-OF-CHANGE-OF-VALUE */
Object get_rate_of_change_of_value(variable,
	    value_requested_by_simulator_qm,units,interval_begin_time,
	    interval_end_time)
    Object variable, value_requested_by_simulator_qm, units;
    Object interval_begin_time, interval_end_time;
{
    Object symbol, top_of_stack, message_1, history_being_kept_qm;
    Object referencing_simulation_history_qm, sub_class_bit_vector;
    Object simulation_subtable_qm, simulation_stored_histories_qm;
    Object value_history_cascaded_ring_buffer;
    Object variable_or_parameter_stored_histories_qm;
    Object value_history_ring_buffer_or_cascade, temp_1;
    Object oldest_active_element_index, newest_active_element_index;
    Object interval_ok_qm, in_interval_qm, first_value_in_interval;
    Object second_value_in_interval, last_value_in_interval;
    Object next_to_last_value_in_interval, time_of_first_value_in_interval;
    Object time_of_second_value_in_interval, time_of_last_value_in_interval;
    Object time_of_next_to_last_value_in_interval, element_index;
    Object first_result_value, second_result_value, next_to_last_result_value;
    Object last_result_value, unmanaged_time_of_first_value;
    Object unmanaged_time_of_second_value;
    Object unmanaged_time_of_next_to_last_value, unmanaged_time_of_last_value;
    Object done_qm, gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    Object temp_accumulated_value_1, temp_accumulated_value_2;
    Object temp_accumulated_value_3, temp_accumulated_value_4, storage_time;
    Object vector_1, managed_number_or_value, next_history_value;
    Object store_managed_number_arg, rate_of_change, begin_point_value;
    Object begin_point_time, end_point_value, end_point_time;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, i, ab_loop_bind_;
    char temp;
    double temp_2, temp_3;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(148,100);
    if (T) {
	symbol = ISVREF(variable,(SI_Long)20L);
	temp =  !(EQ(symbol,Qnumber) || EQ(symbol,Qinteger) || EQ(symbol,
		Qfloat) || EQ(symbol,Qlong) || 
		lookup_global_or_kb_specific_property_value(symbol,
		Numeric_data_type_gkbprop));
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_2,
		Qget_rate_of_change_of_value,variable);
	raw_stack_error_named_error(top_of_stack,message_1);
	return VALUES_1(Nil);
    }
    else {
	history_being_kept_qm = Nil;
	referencing_simulation_history_qm = value_requested_by_simulator_qm;
	if (value_requested_by_simulator_qm) {
	    sub_class_bit_vector = ISVREF(ISVREF(variable,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Variable_class_description,(SI_Long)18L));
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
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    simulation_subtable_qm = get_lookup_slot_value(variable,
		    Qsimulation_details);
	    simulation_stored_histories_qm = simulation_subtable_qm ? 
		    ISVREF(simulation_subtable_qm,(SI_Long)20L) : Nil;
	    history_being_kept_qm =  ! !(simulation_subtable_qm && 
		    ISVREF(simulation_subtable_qm,(SI_Long)21L)) ? T : Nil;
	    value_history_cascaded_ring_buffer =  
		    !TRUEP(history_being_kept_qm) ||  
		    !TRUEP(simulation_stored_histories_qm) || 
		    cascaded_ring_buffer_empty_qm(simulation_stored_histories_qm) 
		    ? Nil : simulation_stored_histories_qm;
	}
	else {
	    variable_or_parameter_stored_histories_qm = ISVREF(variable,
		    (SI_Long)24L);
	    referencing_simulation_history_qm = Nil;
	    history_being_kept_qm =  ! !TRUEP(ISVREF(variable,
		    (SI_Long)25L)) ? T : Nil;
	    value_history_cascaded_ring_buffer =  
		    !TRUEP(history_being_kept_qm) ||  
		    !TRUEP(ISVREF(variable,(SI_Long)24L)) || 
		    cascaded_ring_buffer_empty_qm(variable_or_parameter_stored_histories_qm) 
		    ? Nil : variable_or_parameter_stored_histories_qm;
	}
	value_history_ring_buffer_or_cascade = Nil;
	if ( !TRUEP(value_history_cascaded_ring_buffer) && ( 
		!TRUEP(history_being_kept_qm) || T))
	    return VALUES_1(Nil);
	else {
	    if (value_history_cascaded_ring_buffer) {
		temp_1 = ISVREF(value_history_cascaded_ring_buffer,
			(SI_Long)4L);
		value_history_ring_buffer_or_cascade = CAR(temp_1);
	    }
	    else
		value_history_ring_buffer_or_cascade = Nil;
	    oldest_active_element_index = 
		    ISVREF(value_history_ring_buffer_or_cascade,(SI_Long)2L);
	    newest_active_element_index = 
		    ISVREF(value_history_ring_buffer_or_cascade,(SI_Long)1L);
	    interval_ok_qm =  !TRUEP(nanp(interval_begin_time)) &&  
		    !TRUEP(nanp(interval_end_time)) ? 
		    (NUM_LE(interval_begin_time,interval_end_time) ? T : 
		    Nil) : Qnil;
	    if (interval_ok_qm) {
		in_interval_qm = Nil;
		first_value_in_interval = Nil;
		second_value_in_interval = Nil;
		last_value_in_interval = Nil;
		next_to_last_value_in_interval = Nil;
		time_of_first_value_in_interval = Nil;
		time_of_second_value_in_interval = Nil;
		time_of_last_value_in_interval = Nil;
		time_of_next_to_last_value_in_interval = Nil;
		element_index = oldest_active_element_index;
		first_result_value = Nil;
		second_result_value = Nil;
		next_to_last_result_value = Nil;
		last_result_value = Nil;
		unmanaged_time_of_first_value = Nil;
		unmanaged_time_of_second_value = Nil;
		unmanaged_time_of_next_to_last_value = Nil;
		unmanaged_time_of_last_value = Nil;
		done_qm = Nil;
	      next_loop:
		gensymed_symbol_3 = interval_end_time;
		gensymed_symbol_4 = value_history_ring_buffer_or_cascade;
		gensymed_symbol_5 = value_history_cascaded_ring_buffer;
		temp_accumulated_value_1 = Nil;
		temp_accumulated_value_2 = Nil;
		temp_accumulated_value_3 = Nil;
		temp_accumulated_value_4 = Nil;
		if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(first_value_in_interval) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(first_value_in_interval)) 
			    == (SI_Long)1L)
			temp_accumulated_value_1 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(first_value_in_interval,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(first_value_in_interval) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(first_value_in_interval)) 
			    == (SI_Long)1L)
			temp_accumulated_value_1 = 
				aref1(first_value_in_interval,
				FIX((SI_Long)0L));
		    else
			temp_accumulated_value_1 = first_value_in_interval;
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(second_value_in_interval) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(second_value_in_interval)) 
			    == (SI_Long)1L)
			temp_accumulated_value_2 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(second_value_in_interval,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(second_value_in_interval) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(second_value_in_interval)) 
			    == (SI_Long)1L)
			temp_accumulated_value_2 = 
				aref1(second_value_in_interval,
				FIX((SI_Long)0L));
		    else
			temp_accumulated_value_2 = second_value_in_interval;
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(next_to_last_value_in_interval) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(next_to_last_value_in_interval)) 
			    == (SI_Long)1L)
			temp_accumulated_value_3 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(next_to_last_value_in_interval,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(next_to_last_value_in_interval) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(next_to_last_value_in_interval)) 
			    == (SI_Long)1L)
			temp_accumulated_value_3 = 
				aref1(next_to_last_value_in_interval,
				FIX((SI_Long)0L));
		    else
			temp_accumulated_value_3 = 
				next_to_last_value_in_interval;
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(last_value_in_interval) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(last_value_in_interval)) 
			    == (SI_Long)1L)
			temp_accumulated_value_4 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(last_value_in_interval,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(last_value_in_interval) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(last_value_in_interval)) 
			    == (SI_Long)1L)
			temp_accumulated_value_4 = 
				aref1(last_value_in_interval,FIX((SI_Long)0L));
		    else
			temp_accumulated_value_4 = last_value_in_interval;
		    storage_time = Nil;
		    i = (SI_Long)1L;
		    ab_loop_bind_ = IFIX(Max_number_of_history_evaluations);
		  next_loop_1:
		    if (i > ab_loop_bind_)
			goto end_loop;
		    storage_time = 
			    get_history_current_time(gensymed_symbol_5,
			    element_index,referencing_simulation_history_qm);
		    if ( !TRUEP(in_interval_qm)) {
			if (NUM_GE(storage_time,interval_begin_time) &&  
				!NUM_GT(storage_time,gensymed_symbol_3)) {
			    in_interval_qm = T;
			    vector_1 = ISVREF(gensymed_symbol_4,(SI_Long)6L);
			    if (SIMPLE_VECTOR_P(vector_1) && 
				    EQ(ISVREF(vector_1,(SI_Long)0L),
				    Managed_array_unique_marker)) {
				managed_number_or_value = 
					FIXNUM_LE(ISVREF(vector_1,
					(SI_Long)1L),
					Maximum_in_place_array_size) ? 
					ISVREF(vector_1,
					IFIX(FIXNUM_ADD(element_index,
					Managed_array_index_offset))) : 
					ISVREF(ISVREF(vector_1,
					(IFIX(element_index) >>  -  - 
					(SI_Long)10L) + (SI_Long)2L),
					IFIX(element_index) & (SI_Long)1023L);
				if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					== (SI_Long)1L)
				    next_history_value = 
					    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
					    (SI_Long)0L));
				else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					== (SI_Long)1L)
				    next_history_value = 
					    aref1(managed_number_or_value,
					    FIX((SI_Long)0L));
				else if (text_string_p(managed_number_or_value))
				    next_history_value = 
					    copy_text_string(managed_number_or_value);
				else
				    next_history_value = 
					    managed_number_or_value;
			    }
			    else
				next_history_value = 
					DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
					(IFIX(element_index) >>  -  - 
					(SI_Long)10L) + (SI_Long)2L),
					IFIX(element_index) & (SI_Long)1023L));
			    temp_accumulated_value_1 = next_history_value;
			    store_managed_number_arg = storage_time;
			    time_of_first_value_in_interval = 
				    store_managed_number_function(time_of_first_value_in_interval,
				    store_managed_number_arg);
			}
		    }
		    else {
			vector_1 = ISVREF(gensymed_symbol_4,(SI_Long)6L);
			if (SIMPLE_VECTOR_P(vector_1) && 
				EQ(ISVREF(vector_1,(SI_Long)0L),
				Managed_array_unique_marker)) {
			    managed_number_or_value = 
				    FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
				    Maximum_in_place_array_size) ? 
				    ISVREF(vector_1,
				    IFIX(FIXNUM_ADD(element_index,
				    Managed_array_index_offset))) : 
				    ISVREF(ISVREF(vector_1,
				    (IFIX(element_index) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    IFIX(element_index) & (SI_Long)1023L);
			    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
				    != (SI_Long)0L && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				    == (SI_Long)1L)
				next_history_value = 
					DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
					(SI_Long)0L));
			    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
				    != (SI_Long)0L && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				    == (SI_Long)1L)
				next_history_value = 
					aref1(managed_number_or_value,
					FIX((SI_Long)0L));
			    else if (text_string_p(managed_number_or_value))
				next_history_value = 
					copy_text_string(managed_number_or_value);
			    else
				next_history_value = managed_number_or_value;
			}
			else
			    next_history_value = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
				    (IFIX(element_index) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    IFIX(element_index) & (SI_Long)1023L));
			if (NUM_GT(storage_time,gensymed_symbol_3)) {
			    if (temp_accumulated_value_1) {
				store_managed_number_arg = 
					temp_accumulated_value_1;
				first_value_in_interval = 
					store_managed_number_function(first_value_in_interval,
					store_managed_number_arg);
			    }
			    if (temp_accumulated_value_2) {
				store_managed_number_arg = 
					temp_accumulated_value_2;
				second_value_in_interval = 
					store_managed_number_function(second_value_in_interval,
					store_managed_number_arg);
			    }
			    if (temp_accumulated_value_3) {
				store_managed_number_arg = 
					temp_accumulated_value_3;
				next_to_last_value_in_interval = 
					store_managed_number_function(next_to_last_value_in_interval,
					store_managed_number_arg);
			    }
			    if (temp_accumulated_value_4) {
				store_managed_number_arg = 
					temp_accumulated_value_4;
				last_value_in_interval = 
					store_managed_number_function(last_value_in_interval,
					store_managed_number_arg);
			    }
			    done_qm = T;
			    goto end_1;
			}
			else if ( !TRUEP(temp_accumulated_value_2)) {
			    temp_accumulated_value_2 = next_history_value;
			    store_managed_number_arg = storage_time;
			    time_of_second_value_in_interval = 
				    store_managed_number_function(time_of_second_value_in_interval,
				    store_managed_number_arg);
			}
			else if ( !TRUEP(temp_accumulated_value_4)) {
			    temp_accumulated_value_4 = next_history_value;
			    store_managed_number_arg = storage_time;
			    time_of_last_value_in_interval = 
				    store_managed_number_function(time_of_last_value_in_interval,
				    store_managed_number_arg);
			}
			else if ( !TRUEP(temp_accumulated_value_3)) {
			    temp_accumulated_value_3 = next_history_value;
			    store_managed_number_arg = storage_time;
			    time_of_next_to_last_value_in_interval = 
				    store_managed_number_function(time_of_next_to_last_value_in_interval,
				    store_managed_number_arg);
			}
			else {
			    temp_accumulated_value_3 = 
				    temp_accumulated_value_4;
			    temp_accumulated_value_4 = next_history_value;
			    if (INLINE_DOUBLE_FLOAT_VECTOR_P(time_of_last_value_in_interval) 
				    != (SI_Long)0L && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(time_of_last_value_in_interval)) 
				    == (SI_Long)1L)
				store_managed_number_arg = 
					DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(time_of_last_value_in_interval,
					(SI_Long)0L));
			    else if (INLINE_LONG_VECTOR_P(time_of_last_value_in_interval) 
				    != (SI_Long)0L && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(time_of_last_value_in_interval)) 
				    == (SI_Long)1L)
				store_managed_number_arg = 
					aref1(time_of_last_value_in_interval,
					FIX((SI_Long)0L));
			    else
				store_managed_number_arg = 
					time_of_last_value_in_interval;
			    time_of_next_to_last_value_in_interval = 
				    store_managed_number_function(time_of_next_to_last_value_in_interval,
				    store_managed_number_arg);
			    store_managed_number_arg = storage_time;
			    time_of_last_value_in_interval = 
				    store_managed_number_function(time_of_last_value_in_interval,
				    store_managed_number_arg);
			}
		    }
		    if (NUM_EQ(storage_time,gensymed_symbol_3) || 
			    FIXNUM_EQ(element_index,
			    newest_active_element_index)) {
			if (temp_accumulated_value_1) {
			    store_managed_number_arg = 
				    temp_accumulated_value_1;
			    first_value_in_interval = 
				    store_managed_number_function(first_value_in_interval,
				    store_managed_number_arg);
			}
			if (temp_accumulated_value_2) {
			    store_managed_number_arg = 
				    temp_accumulated_value_2;
			    second_value_in_interval = 
				    store_managed_number_function(second_value_in_interval,
				    store_managed_number_arg);
			}
			if (temp_accumulated_value_3) {
			    store_managed_number_arg = 
				    temp_accumulated_value_3;
			    next_to_last_value_in_interval = 
				    store_managed_number_function(next_to_last_value_in_interval,
				    store_managed_number_arg);
			}
			if (temp_accumulated_value_4) {
			    store_managed_number_arg = 
				    temp_accumulated_value_4;
			    last_value_in_interval = 
				    store_managed_number_function(last_value_in_interval,
				    store_managed_number_arg);
			}
			done_qm = T;
			goto end_1;
		    }
		    element_index = FIXNUM_EQ(element_index,
			    FIXNUM_SUB1(ISVREF(gensymed_symbol_4,
			    (SI_Long)4L))) ? FIX((SI_Long)0L) : 
			    FIXNUM_ADD1(element_index);
		    i = i + (SI_Long)1L;
		    goto next_loop_1;
		  end_loop:
		    if (temp_accumulated_value_1) {
			store_managed_number_arg = temp_accumulated_value_1;
			first_value_in_interval = 
				store_managed_number_function(first_value_in_interval,
				store_managed_number_arg);
		    }
		    if (temp_accumulated_value_2) {
			store_managed_number_arg = temp_accumulated_value_2;
			second_value_in_interval = 
				store_managed_number_function(second_value_in_interval,
				store_managed_number_arg);
		    }
		    if (temp_accumulated_value_3) {
			store_managed_number_arg = temp_accumulated_value_3;
			next_to_last_value_in_interval = 
				store_managed_number_function(next_to_last_value_in_interval,
				store_managed_number_arg);
		    }
		    if (temp_accumulated_value_4) {
			store_managed_number_arg = temp_accumulated_value_4;
			last_value_in_interval = 
				store_managed_number_function(last_value_in_interval,
				store_managed_number_arg);
		    }
		    done_qm = Nil;
		    goto end_1;
		    done_qm = Qnil;
		  end_1:;
		}
		POP_LOCAL_ALLOCATION(0,0);
		if (done_qm) {
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(first_value_in_interval) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(first_value_in_interval)) 
			    == (SI_Long)1L)
			first_result_value = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(first_value_in_interval,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(first_value_in_interval) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(first_value_in_interval)) 
			    == (SI_Long)1L)
			first_result_value = aref1(first_value_in_interval,
				FIX((SI_Long)0L));
		    else
			first_result_value = first_value_in_interval;
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(second_value_in_interval) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(second_value_in_interval)) 
			    == (SI_Long)1L)
			second_result_value = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(second_value_in_interval,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(second_value_in_interval) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(second_value_in_interval)) 
			    == (SI_Long)1L)
			second_result_value = 
				aref1(second_value_in_interval,
				FIX((SI_Long)0L));
		    else
			second_result_value = second_value_in_interval;
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(next_to_last_value_in_interval) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(next_to_last_value_in_interval)) 
			    == (SI_Long)1L)
			next_to_last_result_value = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(next_to_last_value_in_interval,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(next_to_last_value_in_interval) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(next_to_last_value_in_interval)) 
			    == (SI_Long)1L)
			next_to_last_result_value = 
				aref1(next_to_last_value_in_interval,
				FIX((SI_Long)0L));
		    else
			next_to_last_result_value = 
				next_to_last_value_in_interval;
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(last_value_in_interval) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(last_value_in_interval)) 
			    == (SI_Long)1L)
			last_result_value = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(last_value_in_interval,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(last_value_in_interval) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(last_value_in_interval)) 
			    == (SI_Long)1L)
			last_result_value = aref1(last_value_in_interval,
				FIX((SI_Long)0L));
		    else
			last_result_value = last_value_in_interval;
		    if (time_of_first_value_in_interval) {
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(time_of_first_value_in_interval) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(time_of_first_value_in_interval)) 
				== (SI_Long)1L)
			    unmanaged_time_of_first_value = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(time_of_first_value_in_interval,
				    (SI_Long)0L));
			else if (INLINE_LONG_VECTOR_P(time_of_first_value_in_interval) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(time_of_first_value_in_interval)) 
				== (SI_Long)1L)
			    unmanaged_time_of_first_value = 
				    aref1(time_of_first_value_in_interval,
				    FIX((SI_Long)0L));
			else
			    unmanaged_time_of_first_value = 
				    time_of_first_value_in_interval;
		    }
		    else
			unmanaged_time_of_first_value = Nil;
		    if (time_of_second_value_in_interval) {
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(time_of_second_value_in_interval) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(time_of_second_value_in_interval)) 
				== (SI_Long)1L)
			    unmanaged_time_of_second_value = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(time_of_second_value_in_interval,
				    (SI_Long)0L));
			else if (INLINE_LONG_VECTOR_P(time_of_second_value_in_interval) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(time_of_second_value_in_interval)) 
				== (SI_Long)1L)
			    unmanaged_time_of_second_value = 
				    aref1(time_of_second_value_in_interval,
				    FIX((SI_Long)0L));
			else
			    unmanaged_time_of_second_value = 
				    time_of_second_value_in_interval;
		    }
		    else
			unmanaged_time_of_second_value = Nil;
		    if (time_of_next_to_last_value_in_interval) {
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(time_of_next_to_last_value_in_interval) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(time_of_next_to_last_value_in_interval)) 
				== (SI_Long)1L)
			    unmanaged_time_of_next_to_last_value = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(time_of_next_to_last_value_in_interval,
				    (SI_Long)0L));
			else if (INLINE_LONG_VECTOR_P(time_of_next_to_last_value_in_interval) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(time_of_next_to_last_value_in_interval)) 
				== (SI_Long)1L)
			    unmanaged_time_of_next_to_last_value = 
				    aref1(time_of_next_to_last_value_in_interval,
				    FIX((SI_Long)0L));
			else
			    unmanaged_time_of_next_to_last_value = 
				    time_of_next_to_last_value_in_interval;
		    }
		    else
			unmanaged_time_of_next_to_last_value = Nil;
		    if (time_of_last_value_in_interval) {
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(time_of_last_value_in_interval) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(time_of_last_value_in_interval)) 
				== (SI_Long)1L)
			    unmanaged_time_of_last_value = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(time_of_last_value_in_interval,
				    (SI_Long)0L));
			else if (INLINE_LONG_VECTOR_P(time_of_last_value_in_interval) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(time_of_last_value_in_interval)) 
				== (SI_Long)1L)
			    unmanaged_time_of_last_value = 
				    aref1(time_of_last_value_in_interval,
				    FIX((SI_Long)0L));
			else
			    unmanaged_time_of_last_value = 
				    time_of_last_value_in_interval;
		    }
		    else
			unmanaged_time_of_last_value = Nil;
		    first_value_in_interval = 
			    reclaim_managed_number_or_value_function(first_value_in_interval);
		    second_value_in_interval = 
			    reclaim_managed_number_or_value_function(second_value_in_interval);
		    next_to_last_value_in_interval = 
			    reclaim_managed_number_or_value_function(next_to_last_value_in_interval);
		    last_value_in_interval = 
			    reclaim_managed_number_or_value_function(last_value_in_interval);
		    time_of_first_value_in_interval = 
			    reclaim_managed_number_or_value_function(time_of_first_value_in_interval);
		    time_of_second_value_in_interval = 
			    reclaim_managed_number_or_value_function(time_of_second_value_in_interval);
		    time_of_next_to_last_value_in_interval = 
			    reclaim_managed_number_or_value_function(time_of_next_to_last_value_in_interval);
		    time_of_last_value_in_interval = 
			    reclaim_managed_number_or_value_function(time_of_last_value_in_interval);
		    if (first_result_value) {
			if (NUMBERP(first_result_value)) {
			    rate_of_change =  !TRUEP(first_result_value) ? 
				    T : Nil;
			    if (rate_of_change);
			    else if ( !TRUEP(second_result_value))
				rate_of_change = FIX((SI_Long)0L);
			    else if ( !TRUEP(last_result_value)) {
				temp_1 = lfloat(minus(second_result_value,
					first_result_value),float_constant);
				temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
				temp_1 = 
					lfloat(minus(unmanaged_time_of_second_value,
					unmanaged_time_of_first_value),
					float_constant);
				temp_3 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
				rate_of_change = 
					DOUBLE_TO_DOUBLE_FLOAT(temp_2 / 
					temp_3);
			    }
			    else if ( !TRUEP(next_to_last_result_value)) {
				temp_1 = lfloat(minus(last_result_value,
					first_result_value),float_constant);
				temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
				temp_1 = 
					lfloat(minus(unmanaged_time_of_last_value,
					unmanaged_time_of_first_value),
					float_constant);
				temp_3 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
				rate_of_change = 
					DOUBLE_TO_DOUBLE_FLOAT(temp_2 / 
					temp_3);
			    }
			    else {
				temp_1 = lfloat(minus(second_result_value,
					first_result_value),float_constant);
				temp_3 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
				begin_point_value = add(first_result_value,
					DOUBLE_TO_DOUBLE_FLOAT(temp_3 / 2.0));
				temp_1 = 
					lfloat(minus(unmanaged_time_of_second_value,
					unmanaged_time_of_first_value),
					float_constant);
				temp_3 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
				begin_point_time = 
					add(unmanaged_time_of_first_value,
					DOUBLE_TO_DOUBLE_FLOAT(temp_3 / 2.0));
				temp_1 = lfloat(minus(last_result_value,
					next_to_last_result_value),
					float_constant);
				temp_3 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
				end_point_value = 
					add(next_to_last_result_value,
					DOUBLE_TO_DOUBLE_FLOAT(temp_3 / 2.0));
				temp_1 = 
					lfloat(minus(unmanaged_time_of_last_value,
					unmanaged_time_of_next_to_last_value),
					float_constant);
				temp_3 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
				end_point_time = 
					add(unmanaged_time_of_next_to_last_value,
					DOUBLE_TO_DOUBLE_FLOAT(temp_3 / 2.0));
				temp_1 = lfloat(minus(end_point_value,
					begin_point_value),float_constant);
				temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
				temp_1 = lfloat(minus(end_point_time,
					begin_point_time),float_constant);
				temp_3 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
				rate_of_change = 
					DOUBLE_TO_DOUBLE_FLOAT(temp_2 / 
					temp_3);
			    }
			    goto end_2;
			}
			else {
			    rate_of_change = first_result_value;
			    goto end_2;
			}
		    }
		    else {
			rate_of_change = Nil;
			goto end_2;
		    }
		}
		goto next_loop;
	      end_loop_1:
		rate_of_change = Qnil;
	      end_2:;
	    }
	    else
		rate_of_change = Nil;
	    if (NUMBERP(rate_of_change))
		rate_of_change = ltimes(rate_of_change,units);
	    return return_history_value(variable,rate_of_change,
		    string_constant_13,T,value_requested_by_simulator_qm,T,
		    interval_ok_qm,
		    type_specification_of_variable_or_parameter_value(variable));
	}
    }
}

static Object Qget_integral_of_value_over_interval;  /* get-integral-of-value-over-interval */

static Object string_constant_14;  /* "integral" */

/* GET-INTEGRAL-OF-VALUE-OVER-INTERVAL */
Object get_integral_of_value_over_interval(variable,
	    value_requested_by_simulator_qm,units,interval_begin_time,
	    interval_end_time)
    Object variable, value_requested_by_simulator_qm, units;
    Object interval_begin_time, interval_end_time;
{
    Object symbol, top_of_stack, message_1, history_being_kept_qm;
    Object referencing_simulation_history_qm, sub_class_bit_vector;
    Object simulation_subtable_qm, simulation_stored_histories_qm;
    Object value_history_cascaded_ring_buffer;
    Object variable_or_parameter_stored_histories_qm;
    Object value_history_ring_buffer_or_cascade, temp_1;
    Object oldest_active_element_index, newest_active_element_index;
    Object interval_ok_qm, in_interval_qm, running_sum, previous_value;
    Object previous_time, element_index, done_qm, gensymed_symbol_3;
    Object gensymed_symbol_4, gensymed_symbol_5, temp_accumulated_value_1;
    Object temp_accumulated_value_2, temp_accumulated_value_3, storage_time;
    Object vector_1, managed_number_or_value, next_history_value;
    Object store_managed_number_arg, integral_value;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, i, ab_loop_bind_;
    char temp;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(148,101);
    if (T) {
	symbol = ISVREF(variable,(SI_Long)20L);
	temp =  !(EQ(symbol,Qnumber) || EQ(symbol,Qinteger) || EQ(symbol,
		Qfloat) || EQ(symbol,Qlong) || 
		lookup_global_or_kb_specific_property_value(symbol,
		Numeric_data_type_gkbprop));
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_2,
		Qget_integral_of_value_over_interval,variable);
	raw_stack_error_named_error(top_of_stack,message_1);
	return VALUES_1(Nil);
    }
    else {
	history_being_kept_qm = Nil;
	referencing_simulation_history_qm = value_requested_by_simulator_qm;
	if (value_requested_by_simulator_qm) {
	    sub_class_bit_vector = ISVREF(ISVREF(variable,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Variable_class_description,(SI_Long)18L));
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
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    simulation_subtable_qm = get_lookup_slot_value(variable,
		    Qsimulation_details);
	    simulation_stored_histories_qm = simulation_subtable_qm ? 
		    ISVREF(simulation_subtable_qm,(SI_Long)20L) : Nil;
	    history_being_kept_qm =  ! !(simulation_subtable_qm && 
		    ISVREF(simulation_subtable_qm,(SI_Long)21L)) ? T : Nil;
	    value_history_cascaded_ring_buffer =  
		    !TRUEP(history_being_kept_qm) ||  
		    !TRUEP(simulation_stored_histories_qm) || 
		    cascaded_ring_buffer_empty_qm(simulation_stored_histories_qm) 
		    ? Nil : simulation_stored_histories_qm;
	}
	else {
	    variable_or_parameter_stored_histories_qm = ISVREF(variable,
		    (SI_Long)24L);
	    referencing_simulation_history_qm = Nil;
	    history_being_kept_qm =  ! !TRUEP(ISVREF(variable,
		    (SI_Long)25L)) ? T : Nil;
	    value_history_cascaded_ring_buffer =  
		    !TRUEP(history_being_kept_qm) ||  
		    !TRUEP(ISVREF(variable,(SI_Long)24L)) || 
		    cascaded_ring_buffer_empty_qm(variable_or_parameter_stored_histories_qm) 
		    ? Nil : variable_or_parameter_stored_histories_qm;
	}
	value_history_ring_buffer_or_cascade = Nil;
	if ( !TRUEP(value_history_cascaded_ring_buffer) && ( 
		!TRUEP(history_being_kept_qm) || T))
	    return VALUES_1(Nil);
	else {
	    if (value_history_cascaded_ring_buffer) {
		temp_1 = ISVREF(value_history_cascaded_ring_buffer,
			(SI_Long)4L);
		value_history_ring_buffer_or_cascade = CAR(temp_1);
	    }
	    else
		value_history_ring_buffer_or_cascade = Nil;
	    oldest_active_element_index = 
		    ISVREF(value_history_ring_buffer_or_cascade,(SI_Long)2L);
	    newest_active_element_index = 
		    ISVREF(value_history_ring_buffer_or_cascade,(SI_Long)1L);
	    interval_ok_qm =  !TRUEP(nanp(interval_begin_time)) &&  
		    !TRUEP(nanp(interval_end_time)) ? 
		    (NUM_LE(interval_begin_time,interval_end_time) ? T : 
		    Nil) : Qnil;
	    if (interval_ok_qm) {
		in_interval_qm = Nil;
		running_sum = float_constant;
		previous_value = float_constant;
		previous_time = Nil;
		element_index = oldest_active_element_index;
		done_qm = Nil;
	      next_loop:
		gensymed_symbol_3 = interval_end_time;
		gensymed_symbol_4 = value_history_ring_buffer_or_cascade;
		gensymed_symbol_5 = value_history_cascaded_ring_buffer;
		temp_accumulated_value_1 = Nil;
		temp_accumulated_value_2 = Nil;
		temp_accumulated_value_3 = Nil;
		if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(running_sum) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(running_sum)) 
			    == (SI_Long)1L)
			temp_accumulated_value_1 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(running_sum,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(running_sum) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(running_sum)) 
			    == (SI_Long)1L)
			temp_accumulated_value_1 = aref1(running_sum,
				FIX((SI_Long)0L));
		    else
			temp_accumulated_value_1 = running_sum;
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(previous_value) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(previous_value)) 
			    == (SI_Long)1L)
			temp_accumulated_value_2 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(previous_value,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(previous_value) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(previous_value)) 
			    == (SI_Long)1L)
			temp_accumulated_value_2 = aref1(previous_value,
				FIX((SI_Long)0L));
		    else
			temp_accumulated_value_2 = previous_value;
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(previous_time) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(previous_time)) 
			    == (SI_Long)1L)
			temp_accumulated_value_3 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(previous_time,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(previous_time) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(previous_time)) 
			    == (SI_Long)1L)
			temp_accumulated_value_3 = aref1(previous_time,
				FIX((SI_Long)0L));
		    else
			temp_accumulated_value_3 = previous_time;
		    storage_time = Nil;
		    i = (SI_Long)1L;
		    ab_loop_bind_ = IFIX(Max_number_of_history_evaluations);
		  next_loop_1:
		    if (i > ab_loop_bind_)
			goto end_loop;
		    storage_time = 
			    get_history_current_time(gensymed_symbol_5,
			    element_index,referencing_simulation_history_qm);
		    if ( !TRUEP(in_interval_qm)) {
			if (NUM_GE(storage_time,interval_begin_time) &&  
				!NUM_GT(storage_time,gensymed_symbol_3)) {
			    in_interval_qm = T;
			    vector_1 = ISVREF(gensymed_symbol_4,(SI_Long)6L);
			    if (SIMPLE_VECTOR_P(vector_1) && 
				    EQ(ISVREF(vector_1,(SI_Long)0L),
				    Managed_array_unique_marker)) {
				managed_number_or_value = 
					FIXNUM_LE(ISVREF(vector_1,
					(SI_Long)1L),
					Maximum_in_place_array_size) ? 
					ISVREF(vector_1,
					IFIX(FIXNUM_ADD(element_index,
					Managed_array_index_offset))) : 
					ISVREF(ISVREF(vector_1,
					(IFIX(element_index) >>  -  - 
					(SI_Long)10L) + (SI_Long)2L),
					IFIX(element_index) & (SI_Long)1023L);
				if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					== (SI_Long)1L)
				    next_history_value = 
					    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
					    (SI_Long)0L));
				else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					== (SI_Long)1L)
				    next_history_value = 
					    aref1(managed_number_or_value,
					    FIX((SI_Long)0L));
				else if (text_string_p(managed_number_or_value))
				    next_history_value = 
					    copy_text_string(managed_number_or_value);
				else
				    next_history_value = 
					    managed_number_or_value;
			    }
			    else
				next_history_value = 
					DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
					(IFIX(element_index) >>  -  - 
					(SI_Long)10L) + (SI_Long)2L),
					IFIX(element_index) & (SI_Long)1023L));
			    temp_accumulated_value_1 = 
				    add(temp_accumulated_value_1,
				    ltimes(temp_accumulated_value_2,
				    minus(storage_time,interval_begin_time)));
			    temp_accumulated_value_2 = next_history_value;
			    temp_accumulated_value_3 = storage_time;
			}
		    }
		    else {
			vector_1 = ISVREF(gensymed_symbol_4,(SI_Long)6L);
			if (SIMPLE_VECTOR_P(vector_1) && 
				EQ(ISVREF(vector_1,(SI_Long)0L),
				Managed_array_unique_marker)) {
			    managed_number_or_value = 
				    FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
				    Maximum_in_place_array_size) ? 
				    ISVREF(vector_1,
				    IFIX(FIXNUM_ADD(element_index,
				    Managed_array_index_offset))) : 
				    ISVREF(ISVREF(vector_1,
				    (IFIX(element_index) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    IFIX(element_index) & (SI_Long)1023L);
			    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
				    != (SI_Long)0L && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				    == (SI_Long)1L)
				next_history_value = 
					DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
					(SI_Long)0L));
			    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
				    != (SI_Long)0L && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				    == (SI_Long)1L)
				next_history_value = 
					aref1(managed_number_or_value,
					FIX((SI_Long)0L));
			    else if (text_string_p(managed_number_or_value))
				next_history_value = 
					copy_text_string(managed_number_or_value);
			    else
				next_history_value = managed_number_or_value;
			}
			else
			    next_history_value = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
				    (IFIX(element_index) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    IFIX(element_index) & (SI_Long)1023L));
			if (NUM_GT(storage_time,gensymed_symbol_3)) {
			    temp_accumulated_value_1 = 
				    add(temp_accumulated_value_1,
				    ltimes(temp_accumulated_value_2,
				    minus(interval_end_time,
				    temp_accumulated_value_3)));
			    if (temp_accumulated_value_1) {
				store_managed_number_arg = 
					temp_accumulated_value_1;
				running_sum = 
					store_managed_number_function(running_sum,
					store_managed_number_arg);
			    }
			    if (temp_accumulated_value_2) {
				store_managed_number_arg = 
					temp_accumulated_value_2;
				previous_value = 
					store_managed_number_function(previous_value,
					store_managed_number_arg);
			    }
			    if (temp_accumulated_value_3) {
				store_managed_number_arg = 
					temp_accumulated_value_3;
				previous_time = 
					store_managed_number_function(previous_time,
					store_managed_number_arg);
			    }
			    done_qm = T;
			    goto end_1;
			}
			else {
			    temp_accumulated_value_1 = 
				    add(temp_accumulated_value_1,
				    ltimes(temp_accumulated_value_2,
				    minus(storage_time,
				    temp_accumulated_value_3)));
			    temp_accumulated_value_2 = next_history_value;
			    temp_accumulated_value_3 = storage_time;
			}
		    }
		    if (NUM_EQ(storage_time,gensymed_symbol_3) || 
			    FIXNUM_EQ(element_index,
			    newest_active_element_index)) {
			if (temp_accumulated_value_1) {
			    store_managed_number_arg = 
				    temp_accumulated_value_1;
			    running_sum = 
				    store_managed_number_function(running_sum,
				    store_managed_number_arg);
			}
			if (temp_accumulated_value_2) {
			    store_managed_number_arg = 
				    temp_accumulated_value_2;
			    previous_value = 
				    store_managed_number_function(previous_value,
				    store_managed_number_arg);
			}
			if (temp_accumulated_value_3) {
			    store_managed_number_arg = 
				    temp_accumulated_value_3;
			    previous_time = 
				    store_managed_number_function(previous_time,
				    store_managed_number_arg);
			}
			done_qm = T;
			goto end_1;
		    }
		    element_index = FIXNUM_EQ(element_index,
			    FIXNUM_SUB1(ISVREF(gensymed_symbol_4,
			    (SI_Long)4L))) ? FIX((SI_Long)0L) : 
			    FIXNUM_ADD1(element_index);
		    i = i + (SI_Long)1L;
		    goto next_loop_1;
		  end_loop:
		    if (temp_accumulated_value_1) {
			store_managed_number_arg = temp_accumulated_value_1;
			running_sum = 
				store_managed_number_function(running_sum,
				store_managed_number_arg);
		    }
		    if (temp_accumulated_value_2) {
			store_managed_number_arg = temp_accumulated_value_2;
			previous_value = 
				store_managed_number_function(previous_value,
				store_managed_number_arg);
		    }
		    if (temp_accumulated_value_3) {
			store_managed_number_arg = temp_accumulated_value_3;
			previous_time = 
				store_managed_number_function(previous_time,
				store_managed_number_arg);
		    }
		    done_qm = Nil;
		    goto end_1;
		    done_qm = Qnil;
		  end_1:;
		}
		POP_LOCAL_ALLOCATION(0,0);
		if (done_qm) {
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(running_sum) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(running_sum)) 
			    == (SI_Long)1L)
			temp_1 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(running_sum,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(running_sum) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(running_sum)) 
			    == (SI_Long)1L)
			temp_1 = aref1(running_sum,FIX((SI_Long)0L));
		    else
			temp_1 = running_sum;
		    running_sum = 
			    reclaim_managed_number_or_value_function(running_sum);
		    previous_value = 
			    reclaim_managed_number_or_value_function(previous_value);
		    previous_time = 
			    reclaim_managed_number_or_value_function(previous_time);
		    integral_value = temp_1;
		    goto end_2;
		}
		goto next_loop;
	      end_loop_1:
		integral_value = Qnil;
	      end_2:;
	    }
	    else
		integral_value = Nil;
	    if (NUMBERP(integral_value))
		integral_value = divide(integral_value,units);
	    return return_history_value(variable,integral_value,
		    string_constant_14,T,value_requested_by_simulator_qm,T,
		    interval_ok_qm,
		    type_specification_of_variable_or_parameter_value(variable));
	}
    }
}

static Object Qget_history_ring_buffer_if_any;  /* get-history-ring-buffer-if-any */

/* GET-HISTORY-RING-BUFFER-IF-ANY */
Object get_history_ring_buffer_if_any(variable,value_requested_by_simulator_qm)
    Object variable, value_requested_by_simulator_qm;
{
    Object symbol, top_of_stack, message_1, history_being_kept_qm;
    Object referencing_simulation_history_qm, sub_class_bit_vector;
    Object simulation_subtable_qm, simulation_stored_histories_qm;
    Object value_history_cascaded_ring_buffer;
    Object variable_or_parameter_stored_histories_qm;
    Object value_history_ring_buffer_or_cascade, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(148,102);
    if (Nil) {
	symbol = ISVREF(variable,(SI_Long)20L);
	temp =  !(EQ(symbol,Qnumber) || EQ(symbol,Qinteger) || EQ(symbol,
		Qfloat) || EQ(symbol,Qlong) || 
		lookup_global_or_kb_specific_property_value(symbol,
		Numeric_data_type_gkbprop));
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_2,
		Qget_history_ring_buffer_if_any,variable);
	raw_stack_error_named_error(top_of_stack,message_1);
	return VALUES_1(Nil);
    }
    else {
	history_being_kept_qm = Nil;
	referencing_simulation_history_qm = value_requested_by_simulator_qm;
	if (value_requested_by_simulator_qm) {
	    sub_class_bit_vector = ISVREF(ISVREF(variable,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Variable_class_description,(SI_Long)18L));
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
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    simulation_subtable_qm = get_lookup_slot_value(variable,
		    Qsimulation_details);
	    simulation_stored_histories_qm = simulation_subtable_qm ? 
		    ISVREF(simulation_subtable_qm,(SI_Long)20L) : Nil;
	    history_being_kept_qm =  ! !(simulation_subtable_qm && 
		    ISVREF(simulation_subtable_qm,(SI_Long)21L)) ? T : Nil;
	    value_history_cascaded_ring_buffer =  
		    !TRUEP(history_being_kept_qm) ||  
		    !TRUEP(simulation_stored_histories_qm) || 
		    cascaded_ring_buffer_empty_qm(simulation_stored_histories_qm) 
		    ? Nil : simulation_stored_histories_qm;
	}
	else {
	    variable_or_parameter_stored_histories_qm = ISVREF(variable,
		    (SI_Long)24L);
	    referencing_simulation_history_qm = Nil;
	    history_being_kept_qm =  ! !TRUEP(ISVREF(variable,
		    (SI_Long)25L)) ? T : Nil;
	    value_history_cascaded_ring_buffer =  
		    !TRUEP(history_being_kept_qm) ||  
		    !TRUEP(ISVREF(variable,(SI_Long)24L)) || 
		    cascaded_ring_buffer_empty_qm(variable_or_parameter_stored_histories_qm) 
		    ? Nil : variable_or_parameter_stored_histories_qm;
	}
	value_history_ring_buffer_or_cascade = Nil;
	if ( !TRUEP(value_history_cascaded_ring_buffer) && ( 
		!TRUEP(history_being_kept_qm) || Nil))
	    return VALUES_1(Nil);
	else {
	    if (value_history_cascaded_ring_buffer) {
		temp_1 = ISVREF(value_history_cascaded_ring_buffer,
			(SI_Long)4L);
		value_history_ring_buffer_or_cascade = CAR(temp_1);
	    }
	    else
		value_history_ring_buffer_or_cascade = Nil;
	    return VALUES_1(value_history_ring_buffer_or_cascade);
	}
    }
}

/* ADD-DELTA-TO-ALL-HISTORY-BUFFER-TIMES */
Object add_delta_to_all_history_buffer_times(buffer,delta)
    Object buffer, delta;
{
    Object gensymed_symbol, temp, value_history_ring_buffer_or_cascade;
    Object oldest_active_element_index, newest_active_element_index;
    Object history_value, history_collection_time, points_read, element_index;
    Object initial_element_index_qm, vector_1, managed_number_or_value, temp_1;
    Object temp_2, value, store_managed_number_or_value_arg, temp_3;
    Object new_managed_array, element_index_1, amf_available_array_cons_qm;
    Object amf_array, temp_5, amf_result, new_float;
    SI_Long temp_4, temp_7;
    char temp_6;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(148,103);
    gensymed_symbol = buffer;
    if ( !TRUEP(cascaded_ring_buffer_empty_qm(gensymed_symbol))) {
	temp = ISVREF(gensymed_symbol,(SI_Long)4L);
	value_history_ring_buffer_or_cascade = CAR(temp);
	oldest_active_element_index = 
		ISVREF(value_history_ring_buffer_or_cascade,(SI_Long)2L);
	newest_active_element_index = 
		ISVREF(value_history_ring_buffer_or_cascade,(SI_Long)1L);
	history_value = Nil;
	history_collection_time = Nil;
	points_read = FIX((SI_Long)0L);
	element_index = oldest_active_element_index;
	initial_element_index_qm = T;
      next_loop:
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	  next_loop_1:
	    if (initial_element_index_qm)
		initial_element_index_qm = Nil;
	    else
		element_index = FIXNUM_EQ(element_index,
			FIXNUM_SUB1(ISVREF(value_history_ring_buffer_or_cascade,
			(SI_Long)4L))) ? FIX((SI_Long)0L) : 
			FIXNUM_ADD1(element_index);
	    vector_1 = ISVREF(value_history_ring_buffer_or_cascade,
		    (SI_Long)6L);
	    if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
		    (SI_Long)0L),Managed_array_unique_marker)) {
		managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(vector_1,IFIX(FIXNUM_ADD(element_index,
			Managed_array_index_offset))) : 
			ISVREF(ISVREF(vector_1,(IFIX(element_index) >>  -  
			- (SI_Long)10L) + (SI_Long)2L),IFIX(element_index) 
			& (SI_Long)1023L);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    temp = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    temp = aref1(managed_number_or_value,FIX((SI_Long)0L));
		else if (text_string_p(managed_number_or_value))
		    temp = copy_text_string(managed_number_or_value);
		else
		    temp = managed_number_or_value;
	    }
	    else
		temp = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
			(IFIX(element_index) >>  -  - (SI_Long)10L) + 
			(SI_Long)2L),IFIX(element_index) & (SI_Long)1023L));
	    vector_1 = ISVREF(value_history_ring_buffer_or_cascade,
		    (SI_Long)7L);
	    if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
		    (SI_Long)0L),Managed_array_unique_marker)) {
		managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(vector_1,IFIX(FIXNUM_ADD(element_index,
			Managed_array_index_offset))) : 
			ISVREF(ISVREF(vector_1,(IFIX(element_index) >>  -  
			- (SI_Long)10L) + (SI_Long)2L),IFIX(element_index) 
			& (SI_Long)1023L);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    temp_1 = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    temp_1 = aref1(managed_number_or_value,FIX((SI_Long)0L));
		else if (text_string_p(managed_number_or_value))
		    temp_1 = copy_text_string(managed_number_or_value);
		else
		    temp_1 = managed_number_or_value;
	    }
	    else
		temp_1 = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(vector_1,
			(IFIX(element_index) >>  -  - (SI_Long)10L) + 
			(SI_Long)2L),IFIX(element_index) & (SI_Long)1023L));
	    history_value = temp;
	    history_collection_time = temp_1;
	    points_read = FIXNUM_ADD1(points_read);
	    temp_2 = 
		    FIXNUM_ADD1(ISVREF(value_history_ring_buffer_or_cascade,
		    (SI_Long)5L));
	    SVREF(value_history_ring_buffer_or_cascade,FIX((SI_Long)5L)) = 
		    temp_2;
	    vector_1 = ISVREF(value_history_ring_buffer_or_cascade,
		    (SI_Long)7L);
	    value = add(history_collection_time,delta);
	    if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
		    (SI_Long)0L),Managed_array_unique_marker)) {
		store_managed_number_or_value_arg = value;
		temp_3 = 
			store_managed_number_or_value_function(FIXNUM_LE(ISVREF(vector_1,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(vector_1,IFIX(FIXNUM_ADD(element_index,
			Managed_array_index_offset))) : 
			ISVREF(ISVREF(vector_1,(IFIX(element_index) >>  -  
			- (SI_Long)10L) + (SI_Long)2L),IFIX(element_index) 
			& (SI_Long)1023L),store_managed_number_or_value_arg);
		if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    temp_2 = FIXNUM_ADD(element_index,
			    Managed_array_index_offset);
		    SVREF(vector_1,temp_2) = temp_3;
		}
		else {
		    temp_2 = ISVREF(vector_1,(IFIX(element_index) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_4 = IFIX(element_index) & (SI_Long)1023L;
		    ISVREF(temp_2,temp_4) = temp_3;
		}
	    }
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L) {
		temp_2 = ISVREF(vector_1,(IFIX(element_index) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_4 = IFIX(element_index) & (SI_Long)1023L;
		aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		DFLOAT_ISASET_1(temp_2,temp_4,aref_new_value);
	    }
	    else if (FLOATP(value)) {
		temp_2 = ISVREF(vector_1,(IFIX(element_index) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_4 = IFIX(element_index) & (SI_Long)1023L;
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		DFLOAT_ISASET_1(temp_2,temp_4,aref_new_value);
	    }
	    else {
		new_managed_array = allocate_managed_array(1,
			ISVREF(vector_1,(SI_Long)1L));
		if ( !TRUEP(ISVREF(value_history_ring_buffer_or_cascade,
			(SI_Long)3L))) {
		    element_index_1 = 
			    ISVREF(value_history_ring_buffer_or_cascade,
			    (SI_Long)2L);
		  next_loop_2:
		    if (FIXNUM_LE(ISVREF(new_managed_array,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			temp_2 = FIXNUM_ADD(element_index_1,
				Managed_array_index_offset);
			amf_available_array_cons_qm = 
				ISVREF(Vector_of_simple_float_array_pools,
				(SI_Long)1L);
			if (amf_available_array_cons_qm) {
			    amf_array = M_CAR(amf_available_array_cons_qm);
			    temp_3 = Vector_of_simple_float_array_pools;
			    temp_5 = M_CDR(amf_available_array_cons_qm);
			    SVREF(temp_3,FIX((SI_Long)1L)) = temp_5;
			    inline_note_reclaim_cons(amf_available_array_cons_qm,
				    Qfloat_array);
			    if (ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp_3 = 
					ISVREF(Available_float_array_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp_3) = amf_available_array_cons_qm;
				temp_3 = 
					Available_float_array_conses_tail_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_3,temp_5) = 
					amf_available_array_cons_qm;
			    }
			    else {
				temp_3 = Available_float_array_conses_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_3,temp_5) = 
					amf_available_array_cons_qm;
				temp_3 = 
					Available_float_array_conses_tail_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_3,temp_5) = 
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
			aref_new_value = DFLOAT_ISAREF_1(ISVREF(vector_1,
				(IFIX(element_index_1) >>  -  - 
				(SI_Long)10L) + (SI_Long)2L),
				IFIX(element_index_1) & (SI_Long)1023L);
			DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
			SVREF(new_managed_array,temp_2) = new_float;
		    }
		    else {
			temp_2 = ISVREF(new_managed_array,
				(IFIX(element_index_1) >>  -  - 
				(SI_Long)10L) + (SI_Long)2L);
			temp_4 = IFIX(element_index_1) & (SI_Long)1023L;
			amf_available_array_cons_qm = 
				ISVREF(Vector_of_simple_float_array_pools,
				(SI_Long)1L);
			if (amf_available_array_cons_qm) {
			    amf_array = M_CAR(amf_available_array_cons_qm);
			    temp_3 = Vector_of_simple_float_array_pools;
			    temp_5 = M_CDR(amf_available_array_cons_qm);
			    SVREF(temp_3,FIX((SI_Long)1L)) = temp_5;
			    inline_note_reclaim_cons(amf_available_array_cons_qm,
				    Qfloat_array);
			    if (ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp_3 = 
					ISVREF(Available_float_array_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp_3) = amf_available_array_cons_qm;
				temp_3 = 
					Available_float_array_conses_tail_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_3,temp_5) = 
					amf_available_array_cons_qm;
			    }
			    else {
				temp_3 = Available_float_array_conses_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_3,temp_5) = 
					amf_available_array_cons_qm;
				temp_3 = 
					Available_float_array_conses_tail_vector;
				temp_5 = Current_thread_index;
				SVREF(temp_3,temp_5) = 
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
			aref_new_value = DFLOAT_ISAREF_1(ISVREF(vector_1,
				(IFIX(element_index_1) >>  -  - 
				(SI_Long)10L) + (SI_Long)2L),
				IFIX(element_index_1) & (SI_Long)1023L);
			DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
			ISVREF(temp_2,temp_4) = new_float;
		    }
		    if (FIXNUM_EQ(element_index_1,
			    ISVREF(value_history_ring_buffer_or_cascade,
			    (SI_Long)1L)))
			goto end_loop;
		    element_index_1 = FIXNUM_EQ(element_index_1,
			    FIXNUM_SUB1(ISVREF(value_history_ring_buffer_or_cascade,
			    (SI_Long)4L))) ? FIX((SI_Long)0L) : 
			    FIXNUM_ADD1(element_index_1);
		    goto next_loop_2;
		  end_loop:;
		}
		reclaim_managed_float_array(vector_1);
		SVREF(value_history_ring_buffer_or_cascade,
			FIX((SI_Long)7L)) = new_managed_array;
		temp_2 = ISVREF(value_history_ring_buffer_or_cascade,
			(SI_Long)7L);
		store_managed_number_or_value_arg = value;
		temp_5 = 
			store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp_2,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(temp_2,IFIX(FIXNUM_ADD(element_index,
			Managed_array_index_offset))) : 
			ISVREF(ISVREF(temp_2,(IFIX(element_index) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),IFIX(element_index) & 
			(SI_Long)1023L),store_managed_number_or_value_arg);
		if (FIXNUM_LE(ISVREF(temp_2,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    temp_3 = FIXNUM_ADD(element_index,
			    Managed_array_index_offset);
		    SVREF(temp_2,temp_3) = temp_5;
		}
		else {
		    temp_2 = ISVREF(temp_2,(IFIX(element_index) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_4 = IFIX(element_index) & (SI_Long)1023L;
		    ISVREF(temp_2,temp_4) = temp_5;
		}
	    }
	    temp_6 = FIXNUM_EQ(element_index,newest_active_element_index);
	    if (temp_6);
	    else {
		temp_7 = IFIX(points_read) % (SI_Long)500L;
		temp_6 = temp_7 == (SI_Long)0L;
	    }
	    if (temp_6)
		goto end_loop_1;
	    goto next_loop_1;
	  end_loop_1:;
	}
	POP_LOCAL_ALLOCATION(0,0);
	if (FIXNUM_EQ(element_index,newest_active_element_index))
	    goto end_loop_2;
	goto next_loop;
      end_loop_2:;
    }
    return VALUES_1(buffer);
}

/* ADD-DELTA-TO-HISTORY-BUFFER-BASE-TIME */
Object add_delta_to_history_buffer_base_time(history_buffer,
	    managed_float_delta)
    Object history_buffer, managed_float_delta;
{
    Object base_time_qm;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(148,104);
    base_time_qm = ISVREF(history_buffer,(SI_Long)10L);
    if (base_time_qm) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    aref_new_value = DFLOAT_ISAREF_1(base_time_qm,(SI_Long)0L) + 
		    DFLOAT_ISAREF_1(managed_float_delta,(SI_Long)0L);
	    DFLOAT_ISASET_1(base_time_qm,(SI_Long)0L,aref_new_value);
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    return VALUES_1(Nil);
}

static Object Qparameter;          /* parameter */

/* ADD-DELTA-TIME-TO-VARIABLES-AND-PARAMETERS */
Object add_delta_time_to_variables_and_parameters(managed_float_delta)
    Object managed_float_delta;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, parameter;
    Object history_buffer_qm, variable, current_value_time_qm;
    Object simulation_subtable_qm, simulation_history_buffer_qm;
    char temp;
    double aref_new_value;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(148,105);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    parameter = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      history_buffer_qm = Nil;
      ab_loopvar_ = collect_subclasses(Qparameter);
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
      parameter = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      history_buffer_qm = ISVREF(parameter,(SI_Long)24L);
      if (history_buffer_qm) {
	  if (Noting_changes_to_kb_p)
	      note_change_to_runtime_data_for_block_1(parameter);
	  add_delta_to_history_buffer_base_time(history_buffer_qm,
		  managed_float_delta);
      }
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    variable = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      current_value_time_qm = Nil;
      history_buffer_qm = Nil;
      simulation_subtable_qm = Nil;
      simulation_history_buffer_qm = Nil;
      ab_loopvar_ = collect_subclasses(Qvariable);
    next_loop_2:
      if ( !TRUEP(ab_loopvar__1)) {
	next_loop_3:
	  if ( !TRUEP(ab_loopvar_))
	      goto end_loop_2;
	  ab_loopvar__1 = 
		  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		  Instances_specific_to_this_class_kbprop);
	  ab_loopvar_ = M_CDR(ab_loopvar_);
	  if (ab_loopvar__1)
	      goto end_loop_2;
	  goto next_loop_3;
	end_loop_2:
	  temp =  !TRUEP(ab_loopvar__1);
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  goto end_loop_3;
      variable = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      current_value_time_qm = ISVREF(variable,(SI_Long)21L);
      history_buffer_qm = ISVREF(variable,(SI_Long)24L);
      simulation_subtable_qm = get_lookup_slot_value(variable,
	      Qsimulation_details);
      simulation_history_buffer_qm = simulation_subtable_qm ? 
	      ISVREF(simulation_subtable_qm,(SI_Long)20L) : Nil;
      if (current_value_time_qm || history_buffer_qm || 
	      simulation_history_buffer_qm) {
	  if (Noting_changes_to_kb_p)
	      note_change_to_runtime_data_for_block_1(variable);
      }
      if (current_value_time_qm && 
	      INLINE_DOUBLE_FLOAT_VECTOR_P(current_value_time_qm) != 
	      (SI_Long)0L && 
	      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_value_time_qm)) == 
	      (SI_Long)1L) {
	  if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	      aref_new_value = DFLOAT_ISAREF_1(current_value_time_qm,
		      (SI_Long)0L) + DFLOAT_ISAREF_1(managed_float_delta,
		      (SI_Long)0L);
	      DFLOAT_ISASET_1(current_value_time_qm,(SI_Long)0L,
		      aref_new_value);
	  }
	  POP_LOCAL_ALLOCATION(0,0);
      }
      if (history_buffer_qm)
	  add_delta_to_history_buffer_base_time(history_buffer_qm,
		  managed_float_delta);
      if (simulation_history_buffer_qm)
	  add_delta_to_history_buffer_base_time(simulation_history_buffer_qm,
		  managed_float_delta);
      goto next_loop_2;
    end_loop_3:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Time_used_to_adjust_histories_qm, Qtime_used_to_adjust_histories_qm);

/* ADJUST-SIMULATION-HISTORY-AT-RUNTIME-IF-NECESSARY */
Object adjust_simulation_history_at_runtime_if_necessary(variable)
    Object variable;
{
    Object sub_class_bit_vector, simulation_details_qm;
    Object buffer_of_stored_values_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(148,106);
    sub_class_bit_vector = ISVREF(ISVREF(variable,(SI_Long)1L),(SI_Long)19L);
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
    simulation_details_qm = temp ? get_lookup_slot_value(variable,
	    Qsimulation_details) : Nil;
    buffer_of_stored_values_qm = simulation_details_qm && 
	    ISVREF(simulation_details_qm,(SI_Long)21L) ? 
	    ISVREF(simulation_details_qm,(SI_Long)20L) : Qnil;
    if (buffer_of_stored_values_qm && Time_used_to_adjust_histories_qm)
	adjust_history_at_runtime_if_necessary(variable,
		buffer_of_stored_values_qm,Time_used_to_adjust_histories_qm);
    return VALUES_1(Nil);
}

/* ADJUST-HISTORY-AT-RUNTIME-IF-NECESSARY */
Object adjust_history_at_runtime_if_necessary(variable_or_parameter,
	    buffer_of_stored_values,managed_float_time)
    Object variable_or_parameter, buffer_of_stored_values, managed_float_time;
{
    Object temp, runtime_specification, ring_buffer;
    Object maximum_age_of_data_points_qm, gensymed_symbol, ab_loop_list_;

    x_note_fn_call(148,107);
    temp = ISVREF(buffer_of_stored_values,(SI_Long)3L);
    runtime_specification = CAR(temp);
    temp = ISVREF(buffer_of_stored_values,(SI_Long)4L);
    ring_buffer = CAR(temp);
    maximum_age_of_data_points_qm = SECOND(runtime_specification);
    if (buffer_of_stored_values && 
	    INLINE_DOUBLE_FLOAT_VECTOR_P(managed_float_time) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_float_time)) == 
		(SI_Long)1L) {
	if ( 
		!TRUEP(verify_oldest_and_newest_history_values_with_given_time(buffer_of_stored_values,
		ring_buffer,maximum_age_of_data_points_qm,
		    managed_float_time))) {
	    if (Noting_changes_to_kb_p)
		note_change_to_runtime_data_for_block_1(variable_or_parameter);
	    if (maximum_age_of_data_points_qm)
		remove_history_values_past_maximum_age(buffer_of_stored_values,
			ring_buffer,maximum_age_of_data_points_qm,
			managed_float_time);
	    remove_future_history_values(buffer_of_stored_values,
		    ring_buffer,managed_float_time);
	    gensymed_symbol = Nil;
	    ab_loop_list_ = ISVREF(buffer_of_stored_values,(SI_Long)11L);
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    gensymed_symbol = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    notify_client_of_change_to_cascaded_ring_buffer(gensymed_symbol);
	    goto next_loop;
	  end_loop:;
	}
    }
    return VALUES_1(Nil);
}

/* MAKE-HISTORY-BUFFER-INFORMATION */
Object make_history_buffer_information(history_buffer)
    Object history_buffer;
{
    Object history_spec_list_qm, history_spec_qm;
    Object maximum_number_of_data_points_qm, maximum_age_of_data_points_qm;
    Object minimum_interval_between_data_points_qm, gensymed_symbol;
    Object gensymed_symbol_1, car_new_value;

    x_note_fn_call(148,108);
    history_spec_list_qm = ISVREF(history_buffer,(SI_Long)3L);
    history_spec_qm = history_spec_list_qm ? FIRST(history_spec_list_qm) : Nil;
    maximum_number_of_data_points_qm = FIRST(history_spec_qm);
    maximum_age_of_data_points_qm = SECOND(history_spec_qm);
    minimum_interval_between_data_points_qm = THIRD(history_spec_qm);
    gensymed_symbol = make_slot_value_list_1(FIX((SI_Long)6L));
    gensymed_symbol_1 = gensymed_symbol;
    car_new_value = ISVREF(history_buffer,(SI_Long)10L);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = maximum_number_of_data_points_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = maximum_age_of_data_points_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = minimum_interval_between_data_points_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = ISVREF(history_buffer,(SI_Long)8L);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = ISVREF(history_buffer,(SI_Long)7L);
    M_CAR(gensymed_symbol_1) = car_new_value;
    return VALUES_1(gensymed_symbol);
}

/* READ-HISTORY-BUFFER-FROM-KB */
Object read_history_buffer_from_kb()
{
    Object history_buffer_information, number_of_elements_to_read;
    Object gensymed_symbol, base_time, maximum_number_of_data_points_qm;
    Object maximum_age_of_data_points_qm;
    Object minimum_interval_between_data_points_qm, lowest_value_qm;
    Object highest_value_qm, history_buffer, svref_new_value, shell, size;
    char svref_new_value_1;

    x_note_fn_call(148,109);
    history_buffer_information = read_element_for_kb(Nil);
    number_of_elements_to_read = read_element_for_kb(Nil);
    gensymed_symbol = history_buffer_information;
    base_time = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    maximum_number_of_data_points_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    maximum_age_of_data_points_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    minimum_interval_between_data_points_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    lowest_value_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    highest_value_qm = CAR(gensymed_symbol);
    reclaim_slot_value_list_1(history_buffer_information);
    history_buffer = make_cascaded_ring_buffer_1();
    svref_new_value = 
	    history_cons_1(history_list_3(maximum_number_of_data_points_qm,
	    maximum_age_of_data_points_qm,
	    minimum_interval_between_data_points_qm),Nil);
    SVREF(history_buffer,FIX((SI_Long)3L)) = svref_new_value;
    shell = make_history_ring_buffer_1();
    size = maximum_number_of_data_points_qm ? 
	    FIXNUM_MAX(maximum_number_of_data_points_qm,
	    number_of_elements_to_read) : number_of_elements_to_read;
    svref_new_value = read_history_buffer_vector_from_kb(size,
	    number_of_elements_to_read);
    SVREF(shell,FIX((SI_Long)6L)) = svref_new_value;
    svref_new_value = read_history_buffer_vector_from_kb(size,
	    number_of_elements_to_read);
    SVREF(shell,FIX((SI_Long)7L)) = svref_new_value;
    svref_new_value_1 = IFIX(number_of_elements_to_read) == (SI_Long)0L;
    if ( !TRUEP(SVREF(shell,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil)) {
	svref_new_value = FIXNUM_SUB1(number_of_elements_to_read);
	SVREF(shell,FIX((SI_Long)1L)) = svref_new_value;
    }
    SVREF(shell,FIX((SI_Long)4L)) = size;
    svref_new_value = history_cons_1(shell,Nil);
    SVREF(history_buffer,FIX((SI_Long)4L)) = svref_new_value;
    SVREF(history_buffer,FIX((SI_Long)10L)) = base_time;
    SVREF(history_buffer,FIX((SI_Long)8L)) = lowest_value_qm;
    SVREF(history_buffer,FIX((SI_Long)7L)) = highest_value_qm;
    return VALUES_1(history_buffer);
}

static Object Qmanaged_float_array;  /* managed-float-array */

/* READ-HISTORY-BUFFER-VECTOR-FROM-KB */
Object read_history_buffer_vector_from_kb(size,number_of_elements_to_read)
    Object size, number_of_elements_to_read;
{
    Object vector_type;

    x_note_fn_call(148,110);
    vector_type = read_element_for_kb(Nil);
    if (EQ(vector_type,Qmanaged_float_array))
	return finish_reading_into_managed_float_array_for_kb(allocate_managed_float_array(1,
		size),number_of_elements_to_read);
    else
	return finish_reading_into_managed_array_for_kb(allocate_managed_array(1,
		size),number_of_elements_to_read);
}

/* READ-PAST-HISTORY-BUFFER-FROM-KB */
Object read_past_history_buffer_from_kb(print_qm)
    Object print_qm;
{
    Object ring_buffer_length;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(148,111);
    read_past_element_for_kb(print_qm);
    ring_buffer_length = read_element_for_kb(Nil);
    if (print_qm)
	format((SI_Long)3L,T,"~%Value Vector (~d elements): ~%",
		ring_buffer_length);
    read_past_element_for_kb(print_qm);
    ab_loop_repeat_ = IFIX(ring_buffer_length);
  next_loop:
    if ( !((SI_Long)0L < ab_loop_repeat_))
	goto end_loop;
    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
    read_past_element_for_kb(print_qm);
    goto next_loop;
  end_loop:;
    if (print_qm)
	format((SI_Long)3L,T,"~%Time Vector (~d elements): ~%",
		ring_buffer_length);
    read_past_element_for_kb(print_qm);
    ab_loop_repeat_ = IFIX(ring_buffer_length);
  next_loop_1:
    if ( !((SI_Long)0L < ab_loop_repeat_))
	goto end_loop_1;
    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
    read_past_element_for_kb(print_qm);
    goto next_loop_1;
  end_loop_1:
    return VALUES_1(Qnil);
}

static Object Qslot_component;     /* slot-component */

static Object Qslot;               /* slot */

/* MAKE-HISTORY-LOCATION-INFORMATION */
Object make_history_location_information(slot_name,defining_class_qm,
	    slot_component_name_qm,slot_component_indicator_qm)
    Object slot_name, defining_class_qm, slot_component_name_qm;
    Object slot_component_indicator_qm;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(148,112);
    if (slot_component_name_qm) {
	gensymed_symbol = make_slot_value_list_1(FIX((SI_Long)5L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = Qslot_component;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = slot_name;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = defining_class_qm;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = slot_component_name_qm;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = slot_component_indicator_qm;
	return VALUES_1(gensymed_symbol);
    }
    else
	return slot_value_list_3(Qslot,slot_name,defining_class_qm);
}

/* GET-TYPE-OF-HISTORY-LOCATION-INFORMATION */
Object get_type_of_history_location_information(history_location_information)
    Object history_location_information;
{
    x_note_fn_call(148,113);
    return VALUES_1(FIRST(history_location_information));
}

/* SAVE-HISTORY-BUFFER-FOR-KB */
Object save_history_buffer_for_kb varargs_1(int, n)
{
    Object history_buffer, slot_name;
    Object defining_class_qm, slot_component_name_qm;
    Object slot_component_indicator_qm, location_information;
    Object history_buffer_information, temp, history_ring_buffer, ring_buffer;
    Object index_1, oldest_active_element_index_for_ring_buffer, newest_index;
    Object oldest_index;
    SI_Long length_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(148,114);
    INIT_ARGS_nonrelocating();
    history_buffer = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    defining_class_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    slot_component_name_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    slot_component_indicator_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    write_char_for_kb(CHR('B'));
    location_information = make_history_location_information(slot_name,
	    defining_class_qm,slot_component_name_qm,
	    slot_component_indicator_qm);
    write_element_for_kb(location_information);
    reclaim_slot_value_list_1(location_information);
    history_buffer_information = 
	    make_history_buffer_information(history_buffer);
    write_element_for_kb(history_buffer_information);
    reclaim_slot_value_list_1(history_buffer_information);
    temp = ISVREF(history_buffer,(SI_Long)4L);
    history_ring_buffer = FIRST(temp);
    ring_buffer = history_ring_buffer;
    index_1 = ISVREF(history_ring_buffer,(SI_Long)1L);
    oldest_active_element_index_for_ring_buffer = ISVREF(ring_buffer,
	    (SI_Long)2L);
    length_1 = FIXNUM_GE(index_1,
	    oldest_active_element_index_for_ring_buffer) ? 
	    IFIX(FIXNUM_ADD1(FIXNUM_MINUS(index_1,
	    oldest_active_element_index_for_ring_buffer))) : 
	    IFIX(FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(index_1,
	    ISVREF(ring_buffer,(SI_Long)4L)),
	    oldest_active_element_index_for_ring_buffer)));
    newest_index = ISVREF(history_ring_buffer,(SI_Long)1L);
    oldest_index = ISVREF(history_ring_buffer,(SI_Long)2L);
    write_element_for_kb(FIX(length_1));
    write_vector_from_history_buffer_for_kb(ISVREF(history_ring_buffer,
	    (SI_Long)6L),oldest_index,newest_index,
	    ISVREF(history_ring_buffer,(SI_Long)4L));
    return write_vector_from_history_buffer_for_kb(ISVREF(history_ring_buffer,
	    (SI_Long)7L),oldest_index,newest_index,
	    ISVREF(history_ring_buffer,(SI_Long)4L));
}

static Object Qmanaged_array;      /* managed-array */

/* WRITE-VECTOR-FROM-HISTORY-BUFFER-FOR-KB */
Object write_vector_from_history_buffer_for_kb(vector_1,oldest_index,
	    newest_index,vector_length)
    Object vector_1, oldest_index, newest_index, vector_length;
{
    Object start_1, end_1, start_2_qm, end_2_qm;

    x_note_fn_call(148,115);
    start_1 = Nil;
    end_1 = Nil;
    start_2_qm = Nil;
    end_2_qm = Nil;
    start_1 = oldest_index;
    if (FIXNUM_LE(oldest_index,newest_index))
	end_1 = FIXNUM_ADD1(newest_index);
    else {
	end_1 = vector_length;
	start_2_qm = FIX((SI_Long)0L);
	end_2_qm = FIXNUM_ADD1(newest_index);
    }
    if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
	    Managed_float_array_unique_marker)) {
	write_element_for_kb(Qmanaged_float_array);
	finish_writing_out_managed_float_array_for_kb(vector_1,start_1,end_1);
	if (start_2_qm)
	    return finish_writing_out_managed_float_array_for_kb(vector_1,
		    start_2_qm,end_2_qm);
	else
	    return VALUES_1(Nil);
    }
    else {
	write_element_for_kb(Qmanaged_array);
	finish_writing_out_managed_array_for_kb(vector_1,start_1,end_1);
	if (start_2_qm)
	    return finish_writing_out_managed_array_for_kb(vector_1,
		    start_2_qm,end_2_qm);
	else
	    return VALUES_1(Nil);
    }
}

/* RESTORE-HISTORY-BUFFER-FOR-VARIABLE-OR-PARAMETER */
Object restore_history_buffer_for_variable_or_parameter(variable_or_parameter,
	    history_buffer,history_location_information)
    Object variable_or_parameter, history_buffer, history_location_information;
{
    x_note_fn_call(148,116);
    return restore_history_buffer_to_slot(variable_or_parameter,
	    history_buffer,history_location_information);
}

/* RESTORE-HISTORY-BUFFER-FOR-SIMULATION-SUBTABLE */
Object restore_history_buffer_for_simulation_subtable(simulation_subtable,
	    history_buffer,history_location_information)
    Object simulation_subtable, history_buffer, history_location_information;
{
    x_note_fn_call(148,117);
    return restore_history_buffer_to_slot(simulation_subtable,
	    history_buffer,history_location_information);
}

/* RESTORE-HISTORY-BUFFER-TO-SLOT */
Object restore_history_buffer_to_slot(block,history_buffer,
	    history_location_information)
    Object block, history_buffer, history_location_information;
{
    Object slot_name, defining_class_qm, old_history_buffer_qm;

    x_note_fn_call(148,118);
    slot_name = SECOND(history_location_information);
    defining_class_qm = THIRD(history_location_information);
    old_history_buffer_qm = get_slot_value_function(block,slot_name,
	    defining_class_qm);
    if (old_history_buffer_qm)
	reclaim_history_buffer(old_history_buffer_qm);
    return set_slot_value_function(block,slot_name,history_buffer,
	    defining_class_qm);
}

/* READ-HISTORY-BUFFER-AND-LOCATION-FOR-BLOCK */
Object read_history_buffer_and_location_for_block()
{
    Object location, buffer;

    x_note_fn_call(148,119);
    location = read_element_for_kb(Nil);
    buffer = read_history_buffer_from_kb();
    return VALUES_2(buffer,location);
}

/* READ-PAST-HISTORY-BUFFER-AND-LOCATION-FOR-BLOCK */
Object read_past_history_buffer_and_location_for_block(print_qm)
    Object print_qm;
{
    x_note_fn_call(148,120);
    if (print_qm)
	format((SI_Long)2L,T,
		"~%; start history reading history buffer and location:~%");
    read_past_element_for_kb(print_qm);
    read_past_history_buffer_from_kb(print_qm);
    if (print_qm)
	return format((SI_Long)2L,T,
		"~%; end reading history buffer and location:~%");
    else
	return VALUES_1(Nil);
}

static Object Qsimulation_info_qm;  /* simulation-info? */

static Object Qvariable_or_parameter_stored_histories_qm;  /* variable-or-parameter-stored-histories? */

/* WRITE-PARAMETER-DATA-FOR-KB */
Object write_parameter_data_for_kb(parameter)
    Object parameter;
{
    Object collection_time, simulation_info_qm;
    Object simulation_runtime_information_qm, simulation_value_qm;
    Object history_buffer_qm;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(148,121);
    if ( !TRUEP(Left_braket_written_qm)) {
	write_char_for_kb(CHR('['));
	Left_braket_written_qm = T;
    }
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	collection_time = ISVREF(parameter,(SI_Long)21L);
	simulation_info_qm = get_lookup_slot_value_given_default(parameter,
		Qsimulation_info_qm,Nil);
	simulation_runtime_information_qm = simulation_info_qm ? 
		ISVREF(simulation_info_qm,(SI_Long)1L) : Nil;
	simulation_value_qm = simulation_runtime_information_qm ? 
		ISVREF(simulation_runtime_information_qm,(SI_Long)1L) : Nil;
	history_buffer_qm = ISVREF(parameter,(SI_Long)24L);
	write_char_for_kb(CHR('P'));
	write_element_for_kb(ISVREF(parameter,(SI_Long)23L));
	if ( !FIXNUMP(collection_time) || FIXNUM_NE(collection_time,
		Some_time_ago))
	    write_element_for_kb(collection_time);
	else
	    write_char_for_kb(CHR('G'));
	if (history_buffer_qm &&  
		!TRUEP(cascaded_ring_buffer_empty_qm(history_buffer_qm)))
	    save_history_buffer_for_kb(2,history_buffer_qm,
		    Qvariable_or_parameter_stored_histories_qm);
	if (simulation_value_qm) {
	    write_char_for_kb(CHR('S'));
	    result = write_element_for_kb(simulation_value_qm);
	}
	else
	    result = VALUES_1(Nil);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* WRITE-VARIABLE-DATA-FOR-KB */
Object write_variable_data_for_kb(variable)
    Object variable;
{
    Object collection_time, expiration_time, simulation_info_qm;
    Object simulation_runtime_information_qm, simulation_value_qm;
    Object history_buffer_qm;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(148,122);
    if ( !TRUEP(Left_braket_written_qm)) {
	write_char_for_kb(CHR('['));
	Left_braket_written_qm = T;
    }
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	collection_time = ISVREF(variable,(SI_Long)21L);
	expiration_time = ISVREF(variable,(SI_Long)26L);
	simulation_info_qm = get_lookup_slot_value_given_default(variable,
		Qsimulation_info_qm,Nil);
	simulation_runtime_information_qm = simulation_info_qm ? 
		ISVREF(simulation_info_qm,(SI_Long)1L) : Nil;
	simulation_value_qm = simulation_runtime_information_qm ? 
		ISVREF(simulation_runtime_information_qm,(SI_Long)1L) : Nil;
	history_buffer_qm = ISVREF(variable,(SI_Long)24L);
	if ( !FIXNUMP(collection_time) || FIXNUM_NE(collection_time,
		Some_time_ago)) {
	    write_char_for_kb(CHR('V'));
	    write_element_for_kb(ISVREF(variable,(SI_Long)23L));
	    write_element_for_kb(collection_time);
	    if (EQ(expiration_time,Qnever))
		write_char_for_kb(CHR('X'));
	    else if (FIXNUM_EQ(expiration_time,Some_time_ago))
		write_char_for_kb(CHR('G'));
	    else
		write_timestamp_for_kb(expiration_time);
	}
	if (history_buffer_qm &&  
		!TRUEP(cascaded_ring_buffer_empty_qm(history_buffer_qm)))
	    save_history_buffer_for_kb(2,history_buffer_qm,
		    Qvariable_or_parameter_stored_histories_qm);
	if (simulation_value_qm) {
	    write_char_for_kb(CHR('S'));
	    result = write_element_for_kb(simulation_value_qm);
	}
	else
	    result = VALUES_1(Nil);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

static Object Qsimulation_stored_histories_qm;  /* simulation-stored-histories? */

/* WRITE-SIMULATION-SUBTABLE-DATA-FOR-KB */
Object write_simulation_subtable_data_for_kb(simulation_subtable)
    Object simulation_subtable;
{
    Object history_buffer_qm;

    x_note_fn_call(148,123);
    history_buffer_qm = ISVREF(simulation_subtable,(SI_Long)20L);
    if (history_buffer_qm &&  
	    !TRUEP(cascaded_ring_buffer_empty_qm(history_buffer_qm))) {
	if ( !TRUEP(Left_braket_written_qm)) {
	    write_char_for_kb(CHR('['));
	    Left_braket_written_qm = T;
	}
	return save_history_buffer_for_kb(2,history_buffer_qm,
		Qsimulation_stored_histories_qm);
    }
    else
	return VALUES_1(Nil);
}

/* READ-HISTORY-BUFFER-FOR-BLOCK */
Object read_history_buffer_for_block varargs_1(int, n)
{
    Object block, dispatch_char;
    Object history_keeping_spec_qm, number_of_points, history_keeping_spec;
    Object ring_buffer, points_read, history_value, temp, temp_2;
    char temp_1;
    Declare_varargs_nonrelocating;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(148,124);
    INIT_ARGS_nonrelocating();
    block = REQUIRED_ARG_nonrelocating();
    dispatch_char = REQUIRED_ARG_nonrelocating();
    history_keeping_spec_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    number_of_points = read_element_for_kb(Nil);
    history_keeping_spec = history_keeping_spec_qm;
    if (history_keeping_spec);
    else if ( !CHARACTERP(dispatch_char))
	history_keeping_spec = Nil;
    else
	switch (ICHAR_CODE(dispatch_char)) {
	  case 'H':
	    history_keeping_spec = ISVREF(block,(SI_Long)25L);
	    break;
	  case 'J':
	    history_keeping_spec = ISVREF(block,(SI_Long)21L);
	    break;
	  default:
	    history_keeping_spec = Nil;
	    break;
	}
    ring_buffer = make_or_reformat_cascaded_ring_buffer(Nil,
	    SECOND(history_keeping_spec),THIRD(history_keeping_spec),
	    FOURTH(history_keeping_spec));
    points_read = FIX((SI_Long)0L);
  next_loop:
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
      next_loop_1:
	history_value = read_element_for_kb(Nil);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(history_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(history_value)) == (SI_Long)1L)
	    temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(history_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(history_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(history_value)) == (SI_Long)1L)
	    temp = aref1(history_value,FIX((SI_Long)0L));
	else if (text_string_p(history_value))
	    temp = copy_text_string(history_value);
	else
	    temp = history_value;
	store_history_element_in_cascaded_ring_buffer(3,ring_buffer,temp,
		read_element_for_kb(Nil));
	if ( !(FIXNUMP(history_value) || SYMBOLP(history_value) || 
		SIMPLE_VECTOR_P(history_value)))
	    reclaim_if_evaluation_value_1(history_value);
	points_read = FIXNUM_ADD1(points_read);
	temp_1 = FIXNUM_GE(points_read,number_of_points);
	if (temp_1);
	else {
	    temp_2 = chestnut_modf_function(points_read,FIX((SI_Long)500L));
	    temp = FIX((SI_Long)0L);
	    temp_1 = NUM_EQ(temp_2,temp);
	}
	if (temp_1)
	    goto end_loop;
	goto next_loop_1;
      end_loop:;
    }
    POP_LOCAL_ALLOCATION(0,0);
    if ( !FIXNUM_LT(points_read,number_of_points))
	goto end_loop_1;
    goto next_loop;
  end_loop_1:
    return VALUES_1(ring_buffer);
    return VALUES_1(Qnil);
}

/* READ-PAST-HISTORY-BUFFER-FOR-BLOCK */
Object read_past_history_buffer_for_block(print_qm)
    Object print_qm;
{
    Object number_of_points;
    SI_Long ab_loop_repeat_;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(148,125);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	number_of_points = read_element_for_kb(Nil);
	ab_loop_repeat_ = IFIX(number_of_points);
	if (print_qm)
	    format((SI_Long)3L,T,
		    "~%; START HISTORY BUFFER -- ~D POINTS:~%",
		    number_of_points);
      next_loop:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	read_past_element_for_kb(print_qm);
	read_past_element_for_kb(print_qm);
	goto next_loop;
      end_loop:
	if (print_qm)
	    format((SI_Long)3L,T,"~%; END HISTORY BUFFER -- ~d POINTS:~%",
		    number_of_points);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(Nil);
}

static Object Qsquirreled_data;    /* squirreled-data */

static Object Qrelation_instances;  /* relation-instances */

/* UNSQUIRREL-DATA-FOR-BLOCK */
Object unsquirrel_data_for_block(block)
    Object block;
{
    Object squirreled_data, element, ab_loop_list_, char_1, first_1, second_1;
    Object third_1, temp, temp_1, managed_float_or_number, simulation_info_qm;
    Object simulation_runtime_information_qm;
    Object store_managed_number_or_value_arg, buffer_qm;
    Object amf_available_array_cons_qm, amf_array, temp_2, amf_result;
    Object new_float, history_buffer, history_location_information, frame;
    Object sub_vector_qm, function_qm, gensymed_symbol, gensymed_symbol_1;
    SI_Long method_index;
    double aref_new_value;

    x_note_fn_call(148,126);
    squirreled_data = get_lookup_slot_value_given_default(block,
	    Qsquirreled_data,Nil);
    if (squirreled_data) {
	element = Nil;
	ab_loop_list_ = squirreled_data;
	char_1 = Nil;
	first_1 = Nil;
	second_1 = Nil;
	third_1 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	char_1 = CAR(element);
	temp = CDR(element);
	first_1 = CAR(temp);
	temp = CDR(element);
	temp = CDR(temp);
	second_1 = CAR(temp);
	temp = CDR(element);
	temp = CDR(temp);
	temp = CDR(temp);
	third_1 = CAR(temp);
	temp = CHAR_CODE(char_1);
	if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		FIX((SI_Long)127L))))
	    switch (INTEGER_TO_CHAR(temp)) {
	      case 86:
		temp_1 = 
			reclaim_managed_number_or_value_function(ISVREF(block,
			(SI_Long)23L));
		ISVREF(block,(SI_Long)23L) = temp_1;
		ISVREF(block,(SI_Long)23L) = first_1;
		managed_float_or_number = ISVREF(block,(SI_Long)21L);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_float_or_number) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_float_or_number)) 
			== (SI_Long)1L)
		    reclaim_managed_simple_float_array_of_length_1(managed_float_or_number);
		else if (INLINE_LONG_VECTOR_P(managed_float_or_number) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_float_or_number)) 
			== (SI_Long)1L)
		    reclaim_managed_simple_long_array_of_length_1(managed_float_or_number);
		temp_1 = Nil;
		ISVREF(block,(SI_Long)21L) = temp_1;
		ISVREF(block,(SI_Long)21L) = second_1;
		ISVREF(block,(SI_Long)26L) = third_1;
		update_representations_of_variable_or_parameter_value(block);
		break;
	      case 80:
		temp_1 = 
			reclaim_managed_number_or_value_function(ISVREF(block,
			(SI_Long)23L));
		ISVREF(block,(SI_Long)23L) = temp_1;
		ISVREF(block,(SI_Long)23L) = first_1;
		managed_float_or_number = ISVREF(block,(SI_Long)21L);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_float_or_number) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_float_or_number)) 
			== (SI_Long)1L)
		    reclaim_managed_simple_float_array_of_length_1(managed_float_or_number);
		else if (INLINE_LONG_VECTOR_P(managed_float_or_number) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_float_or_number)) 
			== (SI_Long)1L)
		    reclaim_managed_simple_long_array_of_length_1(managed_float_or_number);
		temp_1 = Nil;
		ISVREF(block,(SI_Long)21L) = temp_1;
		ISVREF(block,(SI_Long)21L) = second_1;
		update_representations_of_variable_or_parameter_value(block);
		break;
	      case 83:
		simulation_info_qm = 
			get_lookup_slot_value_given_default(block,
			Qsimulation_info_qm,Nil);
		simulation_runtime_information_qm = simulation_info_qm ? 
			ISVREF(simulation_info_qm,(SI_Long)1L) : Nil;
		if ( !TRUEP(simulation_runtime_information_qm)) {
		    make_variable_simulation_runtime_structure_with_model(block);
		    simulation_info_qm = 
			    get_lookup_slot_value_given_default(block,
			    Qsimulation_info_qm,Nil);
		    simulation_runtime_information_qm = simulation_info_qm 
			    ? ISVREF(simulation_info_qm,(SI_Long)1L) : Nil;
		}
		store_managed_number_or_value_arg = first_1;
		temp_1 = 
			store_managed_number_or_value_function(ISVREF(simulation_runtime_information_qm,
			(SI_Long)1L),store_managed_number_or_value_arg);
		SVREF(simulation_runtime_information_qm,FIX((SI_Long)1L)) 
			= temp_1;
		store_managed_number_or_value_arg = first_1;
		temp_1 = 
			store_managed_number_or_value_function(ISVREF(simulation_runtime_information_qm,
			(SI_Long)2L),store_managed_number_or_value_arg);
		SVREF(simulation_runtime_information_qm,FIX((SI_Long)2L)) 
			= temp_1;
		break;
	      case 72:
		buffer_qm = ISVREF(block,(SI_Long)24L);
		if (buffer_qm)
		    reclaim_history_buffer(buffer_qm);
		temp_1 = add_delta_to_all_history_buffer_times(first_1,
			FIXNUM_NEGATE(Gensym_time_at_start));
		ISVREF(block,(SI_Long)24L) = temp_1;
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
		aref_new_value = 
			(double)IFIX(FIXNUM_MINUS(Gensym_time_at_start,
			Gensym_time_at_start)) + 
			DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		SVREF(first_1,FIX((SI_Long)10L)) = new_float;
		break;
	      case 74:
		buffer_qm = ISVREF(block,(SI_Long)20L);
		if (buffer_qm)
		    reclaim_history_buffer(buffer_qm);
		temp_1 = add_delta_to_all_history_buffer_times(first_1,
			FIXNUM_NEGATE(Gensym_time_at_start));
		ISVREF(block,(SI_Long)20L) = temp_1;
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
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
		SVREF(first_1,FIX((SI_Long)10L)) = new_float;
		break;
	      case 66:
		history_buffer = first_1;
		history_location_information = second_1;
		method_index = (SI_Long)51L;
		frame = block;
		sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
			(SI_Long)11L),method_index);
		function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,
			(SI_Long)1L) : Nil;
		if (function_qm)
		    inline_funcall_3(function_qm,frame,history_buffer,
			    history_location_information);
		reclaim_slot_value_list_1(history_location_information);
		break;
	      case 82:
		reclaim_relation_instances(ISVREF(block,(SI_Long)12L));
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(block,Qrelation_instances);
		temp_1 = SECOND(element);
		SVREF(block,FIX((SI_Long)12L)) = temp_1;
		upgrade_relation_instance(block);
		break;
	      case 65:
	      next_loop_1:
		gensymed_symbol = ISVREF(block,(SI_Long)23L);
		gensymed_symbol_1 = first_1;
		if (CAS_SVREF(block,(SI_Long)23L,gensymed_symbol,
			gensymed_symbol_1))
		    goto end_1;
		goto next_loop_1;
	      end_loop_1:
	      end_1:
		break;
	      case 76:
		unsquirrel_list_data(block,first_1);
		break;
	      case 79:
		unsquirrel_hash_table_data(block,first_1);
		break;
	      default:
		break;
	    }
	reclaim_slot_value_list_1(element);
	goto next_loop;
      end_loop:;
	reclaim_slot_value_list_1(squirreled_data);
	return set_non_savable_lookup_slot_value(block,Qsquirreled_data,Nil);
    }
    else
	return VALUES_1(Nil);
}

void histories_INIT()
{
    Object temp, reclaim_structure_for_history_ring_buffer_1;
    Object reclaim_structure_for_cascaded_ring_buffer_1, gensymed_symbol;
    Object temp_1;
    Object AB_package, Qclasses_which_define, Qrestore_history_buffer;
    Object Qsimulation_subtable;
    Object Qrestore_history_buffer_for_simulation_subtable;
    Object Qvariable_or_parameter;
    Object Qrestore_history_buffer_for_variable_or_parameter;
    Object Qgeneric_method_lambda_list, list_constant_2;
    Object Qhistory_location_information, Qhistory_buffer, Qhistories;
    Object Qg2_initialize_parameter_aux;
    Object Qfunction_keeps_procedure_environment_valid_qm;
    Object Qslot_value_reclaimer;
    Object Qreclaim_simulation_stored_histories_qm_value;
    Object Qreclaim_variable_or_parameter_stored_histories_qm_value;
    Object Qcascaded_ring_buffer, Qreclaim_structure;
    Object Qoutstanding_cascaded_ring_buffer_count;
    Object Qcascaded_ring_buffer_structure_memory_usage, Qutilities2;
    Object string_constant_19, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_18, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qhistory_ring_buffer;
    Object Qoutstanding_history_ring_buffer_count;
    Object Qhistory_ring_buffer_structure_memory_usage, string_constant_17;
    Object string_constant_16, string_constant_15, Qhistory_cons_memory_usage;
    Object Qoutstanding_history_conses, Qutilities1, list_constant_1;
    Object Qhistory_cons_counter_vector, Qmake_thread_array, Kfuncall;
    Object list_constant, Qavailable_history_conses_tail_vector;
    Object Qavailable_history_conses_vector;

    x_note_fn_call(148,127);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qavailable_history_conses = STATIC_SYMBOL("AVAILABLE-HISTORY-CONSES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_history_conses,
	    Available_history_conses);
    Qutilities1 = STATIC_SYMBOL("UTILITIES1",AB_package);
    record_system_variable(Qavailable_history_conses,Qutilities1,Nil,Qnil,
	    Qt,Qnil,Qnil);
    Qavailable_history_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-HISTORY-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_history_conses_tail,
	    Available_history_conses_tail);
    record_system_variable(Qavailable_history_conses_tail,Qutilities1,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_history_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-HISTORY-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_history_conses_vector,
	    Available_history_conses_vector);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_thread_array = STATIC_SYMBOL("MAKE-THREAD-ARRAY",AB_package);
    list_constant = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,Qnil);
    record_system_variable(Qavailable_history_conses_vector,Qutilities1,
	    list_constant,Qnil,Qt,Qnil,Qnil);
    Qavailable_history_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-HISTORY-CONSES-TAIL-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_history_conses_tail_vector,
	    Available_history_conses_tail_vector);
    record_system_variable(Qavailable_history_conses_tail_vector,
	    Qutilities1,list_constant,Qnil,Qt,Qnil,Qnil);
    Qhistory_cons_counter_vector = 
	    STATIC_SYMBOL("HISTORY-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qhistory_cons_counter_vector,
	    History_cons_counter_vector);
    list_constant_1 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    FIX((SI_Long)0L));
    record_system_variable(Qhistory_cons_counter_vector,Qutilities1,
	    list_constant_1,Qnil,Qt,Qnil,Qnil);
    Qhistory_cons_counter = STATIC_SYMBOL("HISTORY-CONS-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qhistory_cons_counter,History_cons_counter);
    record_system_variable(Qhistory_cons_counter,Qutilities1,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_history_conses = 
	    STATIC_SYMBOL("OUTSTANDING-HISTORY-CONSES",AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_history_conses,
	    STATIC_FUNCTION(outstanding_history_conses,NIL,FALSE,0,0));
    Qhistory_cons_memory_usage = STATIC_SYMBOL("HISTORY-CONS-MEMORY-USAGE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhistory_cons_memory_usage,
	    STATIC_FUNCTION(history_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_15 = STATIC_STRING("1q83-Y6y9k83-Y5y09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_history_conses);
    push_optimized_constant(Qhistory_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_15));
    Qhistory = STATIC_SYMBOL("HISTORY",AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_history_ring_buffer_g2_struct = 
	    STATIC_SYMBOL("HISTORY-RING-BUFFER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qhistory_ring_buffer = STATIC_SYMBOL("HISTORY-RING-BUFFER",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_history_ring_buffer_g2_struct,
	    Qhistory_ring_buffer,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qhistory_ring_buffer,
	    Qg2_defstruct_structure_name_history_ring_buffer_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_history_ring_buffer == UNBOUND)
	The_type_description_of_history_ring_buffer = Nil;
    string_constant_16 = 
	    STATIC_STRING("43Dy8m83iUy1o83iUy834Yy8n8k1l834Yy0000001m1m8x834Yy1m8y83-4Cyksk0k0");
    temp = The_type_description_of_history_ring_buffer;
    The_type_description_of_history_ring_buffer = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_16));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_history_ring_buffer_g2_struct,
	    The_type_description_of_history_ring_buffer,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qhistory_ring_buffer,
	    The_type_description_of_history_ring_buffer,
	    Qtype_description_of_type);
    Qoutstanding_history_ring_buffer_count = 
	    STATIC_SYMBOL("OUTSTANDING-HISTORY-RING-BUFFER-COUNT",AB_package);
    Qhistory_ring_buffer_structure_memory_usage = 
	    STATIC_SYMBOL("HISTORY-RING-BUFFER-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_17 = STATIC_STRING("1q83iUy8s83-Y8y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_history_ring_buffer_count);
    push_optimized_constant(Qhistory_ring_buffer_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_17));
    Qchain_of_available_history_ring_buffers = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-HISTORY-RING-BUFFERS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_history_ring_buffers,
	    Chain_of_available_history_ring_buffers);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_history_ring_buffers,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qhistory_ring_buffer_count = STATIC_SYMBOL("HISTORY-RING-BUFFER-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qhistory_ring_buffer_count,
	    History_ring_buffer_count);
    record_system_variable(Qhistory_ring_buffer_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_history_ring_buffers_vector == UNBOUND)
	Chain_of_available_history_ring_buffers_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qhistory_ring_buffer_structure_memory_usage,
	    STATIC_FUNCTION(history_ring_buffer_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_history_ring_buffer_count,
	    STATIC_FUNCTION(outstanding_history_ring_buffer_count,NIL,
	    FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_history_ring_buffer_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_history_ring_buffer,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qhistory_ring_buffer,
	    reclaim_structure_for_history_ring_buffer_1);
    Qg2_defstruct_structure_name_cascaded_ring_buffer_g2_struct = 
	    STATIC_SYMBOL("CASCADED-RING-BUFFER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qcascaded_ring_buffer = STATIC_SYMBOL("CASCADED-RING-BUFFER",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_cascaded_ring_buffer_g2_struct,
	    Qcascaded_ring_buffer,Qab_name_of_unique_structure_type);
    mutate_global_property(Qcascaded_ring_buffer,
	    Qg2_defstruct_structure_name_cascaded_ring_buffer_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_cascaded_ring_buffer == UNBOUND)
	The_type_description_of_cascaded_ring_buffer = Nil;
    string_constant_18 = 
	    STATIC_STRING("43Dy8m83fcy1n83fcy8n8k1l8n0000001m1m8y83-31y1m83=0y83-9Aykwk0k0");
    temp = The_type_description_of_cascaded_ring_buffer;
    The_type_description_of_cascaded_ring_buffer = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_18));
    mutate_global_property(Qg2_defstruct_structure_name_cascaded_ring_buffer_g2_struct,
	    The_type_description_of_cascaded_ring_buffer,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qcascaded_ring_buffer,
	    The_type_description_of_cascaded_ring_buffer,
	    Qtype_description_of_type);
    Qoutstanding_cascaded_ring_buffer_count = 
	    STATIC_SYMBOL("OUTSTANDING-CASCADED-RING-BUFFER-COUNT",AB_package);
    Qcascaded_ring_buffer_structure_memory_usage = 
	    STATIC_SYMBOL("CASCADED-RING-BUFFER-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_19 = STATIC_STRING("1q83fcy8s83-LVy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_cascaded_ring_buffer_count);
    push_optimized_constant(Qcascaded_ring_buffer_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_19));
    Qchain_of_available_cascaded_ring_buffers = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-CASCADED-RING-BUFFERS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_cascaded_ring_buffers,
	    Chain_of_available_cascaded_ring_buffers);
    record_system_variable(Qchain_of_available_cascaded_ring_buffers,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcascaded_ring_buffer_count = 
	    STATIC_SYMBOL("CASCADED-RING-BUFFER-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcascaded_ring_buffer_count,
	    Cascaded_ring_buffer_count);
    record_system_variable(Qcascaded_ring_buffer_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_cascaded_ring_buffers_vector == UNBOUND)
	Chain_of_available_cascaded_ring_buffers_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qcascaded_ring_buffer_structure_memory_usage,
	    STATIC_FUNCTION(cascaded_ring_buffer_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_cascaded_ring_buffer_count,
	    STATIC_FUNCTION(outstanding_cascaded_ring_buffer_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_cascaded_ring_buffer_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_cascaded_ring_buffer,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qcascaded_ring_buffer,
	    reclaim_structure_for_cascaded_ring_buffer_1);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Qgeneric_history = STATIC_SYMBOL("GENERIC-HISTORY",AB_package);
    Qsimulation_details = STATIC_SYMBOL("SIMULATION-DETAILS",AB_package);
    Qvariable_or_parameter_stored_histories_qm = 
	    STATIC_SYMBOL("VARIABLE-OR-PARAMETER-STORED-HISTORIES\?",
	    AB_package);
    Qreclaim_variable_or_parameter_stored_histories_qm_value = 
	    STATIC_SYMBOL("RECLAIM-VARIABLE-OR-PARAMETER-STORED-HISTORIES\?-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_variable_or_parameter_stored_histories_qm_value,
	    STATIC_FUNCTION(reclaim_variable_or_parameter_stored_histories_qm_value,
	    NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qvariable_or_parameter_stored_histories_qm,
	    SYMBOL_FUNCTION(Qreclaim_variable_or_parameter_stored_histories_qm_value),
	    Qslot_value_reclaimer);
    Qsimulation_stored_histories_qm = 
	    STATIC_SYMBOL("SIMULATION-STORED-HISTORIES\?",AB_package);
    Qreclaim_simulation_stored_histories_qm_value = 
	    STATIC_SYMBOL("RECLAIM-SIMULATION-STORED-HISTORIES\?-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_simulation_stored_histories_qm_value,
	    STATIC_FUNCTION(reclaim_simulation_stored_histories_qm_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qsimulation_stored_histories_qm,
	    SYMBOL_FUNCTION(Qreclaim_simulation_stored_histories_qm_value),
	    Qslot_value_reclaimer);
    Qg2_initialize_parameter_aux = 
	    STATIC_SYMBOL("G2-INITIALIZE-PARAMETER-AUX",AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_initialize_parameter_aux,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_initialize_parameter_aux,
	    STATIC_FUNCTION(g2_initialize_parameter_aux,NIL,FALSE,1,1));
    Qnever = STATIC_SYMBOL("NEVER",AB_package);
    string_constant = 
	    STATIC_STRING("Non-numeric value encountered in history for ~NF while computing ~\n                      ~a value request.  The value was ~a.");
    string_constant_1 = 
	    STATIC_STRING("The begin time of the interval specified is greater than the end time ~\n                 while computing ~a value for ~NF.");
    Max_number_of_history_evaluations = FIX((SI_Long)100L);
    Qlong = STATIC_SYMBOL("LONG",AB_package);
    string_constant_2 = 
	    STATIC_STRING("The history function ~a, which requires numeric data, ~\n               tried to use the history of the variable ~NF, which has a ~\n              non-numeric data type.");
    Qget_interpolated_delayed_value = 
	    STATIC_SYMBOL("GET-INTERPOLATED-DELAYED-VALUE",AB_package);
    float_constant = STATIC_FLOAT(0.0);
    string_constant_3 = STATIC_STRING("an interpolated delayed");
    SET_SYMBOL_FUNCTION(Qget_interpolated_delayed_value,
	    STATIC_FUNCTION(get_interpolated_delayed_value,NIL,FALSE,3,3));
    Qget_historical_delayed_value = 
	    STATIC_SYMBOL("GET-HISTORICAL-DELAYED-VALUE",AB_package);
    string_constant_4 = 
	    STATIC_STRING("WARNING: suspected historical-delayed-value internal error.  Please report to Gensym.");
    string_constant_5 = STATIC_STRING("a delayed");
    SET_SYMBOL_FUNCTION(Qget_historical_delayed_value,
	    STATIC_FUNCTION(get_historical_delayed_value,NIL,FALSE,3,3));
    Qget_value_of_previous_datapoint = 
	    STATIC_SYMBOL("GET-VALUE-OF-PREVIOUS-DATAPOINT",AB_package);
    Qget_history_value_for_ring_buffer_or_cascade_function = 
	    STATIC_SYMBOL("GET-HISTORY-VALUE-FOR-RING-BUFFER-OR-CASCADE-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_history_value_for_ring_buffer_or_cascade_function,
	    STATIC_FUNCTION(get_history_value_for_ring_buffer_or_cascade_function,
	    NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qget_value_of_previous_datapoint,
	    STATIC_FUNCTION(get_value_of_previous_datapoint,NIL,FALSE,3,3));
    Qget_collection_time_of_previous_datapoint = 
	    STATIC_SYMBOL("GET-COLLECTION-TIME-OF-PREVIOUS-DATAPOINT",
	    AB_package);
    Qget_history_current_time = STATIC_SYMBOL("GET-HISTORY-CURRENT-TIME",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_history_current_time,
	    STATIC_FUNCTION(get_history_current_time,NIL,FALSE,3,3));
    SET_SYMBOL_FUNCTION(Qget_collection_time_of_previous_datapoint,
	    STATIC_FUNCTION(get_collection_time_of_previous_datapoint,NIL,
	    FALSE,3,3));
    string_constant_6 = STATIC_STRING("a previous datapoint");
    Qnumber_of_datapoints = STATIC_SYMBOL("NUMBER-OF-DATAPOINTS",AB_package);
    string_constant_7 = STATIC_STRING("number of history datapoints");
    SET_SYMBOL_FUNCTION(Qnumber_of_datapoints,
	    STATIC_FUNCTION(number_of_datapoints,NIL,FALSE,4,4));
    Qget_maximum_value = STATIC_SYMBOL("GET-MAXIMUM-VALUE",AB_package);
    string_constant_8 = STATIC_STRING("a maximum");
    SET_SYMBOL_FUNCTION(Qget_maximum_value,
	    STATIC_FUNCTION(get_maximum_value,NIL,FALSE,4,4));
    Qget_minimum_value = STATIC_SYMBOL("GET-MINIMUM-VALUE",AB_package);
    string_constant_9 = STATIC_STRING("minimum");
    SET_SYMBOL_FUNCTION(Qget_minimum_value,
	    STATIC_FUNCTION(get_minimum_value,NIL,FALSE,4,4));
    Qget_averaged_value = STATIC_SYMBOL("GET-AVERAGED-VALUE",AB_package);
    string_constant_10 = STATIC_STRING("average");
    SET_SYMBOL_FUNCTION(Qget_averaged_value,
	    STATIC_FUNCTION(get_averaged_value,NIL,FALSE,4,4));
    Qget_sum_of_values = STATIC_SYMBOL("GET-SUM-OF-VALUES",AB_package);
    string_constant_11 = STATIC_STRING("sum");
    SET_SYMBOL_FUNCTION(Qget_sum_of_values,
	    STATIC_FUNCTION(get_sum_of_values,NIL,FALSE,4,4));
    Qget_standard_deviation_of_value = 
	    STATIC_SYMBOL("GET-STANDARD-DEVIATION-OF-VALUE",AB_package);
    string_constant_12 = STATIC_STRING("standard deviation");
    SET_SYMBOL_FUNCTION(Qget_standard_deviation_of_value,
	    STATIC_FUNCTION(get_standard_deviation_of_value,NIL,FALSE,4,4));
    Qget_rate_of_change_of_value = 
	    STATIC_SYMBOL("GET-RATE-OF-CHANGE-OF-VALUE",AB_package);
    string_constant_13 = STATIC_STRING("rate of change");
    SET_SYMBOL_FUNCTION(Qget_rate_of_change_of_value,
	    STATIC_FUNCTION(get_rate_of_change_of_value,NIL,FALSE,5,5));
    Qget_integral_of_value_over_interval = 
	    STATIC_SYMBOL("GET-INTEGRAL-OF-VALUE-OVER-INTERVAL",AB_package);
    string_constant_14 = STATIC_STRING("integral");
    SET_SYMBOL_FUNCTION(Qget_integral_of_value_over_interval,
	    STATIC_FUNCTION(get_integral_of_value_over_interval,NIL,FALSE,
	    5,5));
    Qget_history_ring_buffer_if_any = 
	    STATIC_SYMBOL("GET-HISTORY-RING-BUFFER-IF-ANY",AB_package);
    SET_SYMBOL_FUNCTION(Qget_history_ring_buffer_if_any,
	    STATIC_FUNCTION(get_history_ring_buffer_if_any,NIL,FALSE,2,2));
    Qparameter = STATIC_SYMBOL("PARAMETER",AB_package);
    Qtime_used_to_adjust_histories_qm = 
	    STATIC_SYMBOL("TIME-USED-TO-ADJUST-HISTORIES\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtime_used_to_adjust_histories_qm,
	    Time_used_to_adjust_histories_qm);
    Qhistories = STATIC_SYMBOL("HISTORIES",AB_package);
    record_system_variable(Qtime_used_to_adjust_histories_qm,Qhistories,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qmanaged_float_array = STATIC_SYMBOL("MANAGED-FLOAT-ARRAY",AB_package);
    Qslot_component = STATIC_SYMBOL("SLOT-COMPONENT",AB_package);
    Qslot = STATIC_SYMBOL("SLOT",AB_package);
    Qmanaged_array = STATIC_SYMBOL("MANAGED-ARRAY",AB_package);
    Qrestore_history_buffer = STATIC_SYMBOL("RESTORE-HISTORY-BUFFER",
	    AB_package);
    Qhistory_buffer = STATIC_SYMBOL("HISTORY-BUFFER",AB_package);
    Qhistory_location_information = 
	    STATIC_SYMBOL("HISTORY-LOCATION-INFORMATION",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)3L,Qblock,Qhistory_buffer,
	    Qhistory_location_information);
    Qgeneric_method_lambda_list = 
	    STATIC_SYMBOL("GENERIC-METHOD-LAMBDA-LIST",AB_package);
    mutate_global_property(Qrestore_history_buffer,list_constant_2,
	    Qgeneric_method_lambda_list);
    Qrestore_history_buffer_for_variable_or_parameter = 
	    STATIC_SYMBOL("RESTORE-HISTORY-BUFFER-FOR-VARIABLE-OR-PARAMETER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qrestore_history_buffer_for_variable_or_parameter,
	    STATIC_FUNCTION(restore_history_buffer_for_variable_or_parameter,
	    NIL,FALSE,3,3));
    Qvariable_or_parameter = STATIC_SYMBOL("VARIABLE-OR-PARAMETER",AB_package);
    temp_1 = 
	    SYMBOL_FUNCTION(Qrestore_history_buffer_for_variable_or_parameter);
    set_get(Qvariable_or_parameter,Qrestore_history_buffer,temp_1);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qrestore_history_buffer),
	    Qclasses_which_define);
    temp_1 = CONS(Qvariable_or_parameter,temp);
    mutate_global_property(Qrestore_history_buffer,temp_1,
	    Qclasses_which_define);
    Qrestore_history_buffer_for_simulation_subtable = 
	    STATIC_SYMBOL("RESTORE-HISTORY-BUFFER-FOR-SIMULATION-SUBTABLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qrestore_history_buffer_for_simulation_subtable,
	    STATIC_FUNCTION(restore_history_buffer_for_simulation_subtable,
	    NIL,FALSE,3,3));
    Qsimulation_subtable = STATIC_SYMBOL("SIMULATION-SUBTABLE",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qrestore_history_buffer_for_simulation_subtable);
    set_get(Qsimulation_subtable,Qrestore_history_buffer,temp_1);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qrestore_history_buffer),
	    Qclasses_which_define);
    temp_1 = CONS(Qsimulation_subtable,temp);
    mutate_global_property(Qrestore_history_buffer,temp_1,
	    Qclasses_which_define);
    Qsimulation_info_qm = STATIC_SYMBOL("SIMULATION-INFO\?",AB_package);
    Qsquirreled_data = STATIC_SYMBOL("SQUIRRELED-DATA",AB_package);
    Qrelation_instances = STATIC_SYMBOL("RELATION-INSTANCES",AB_package);
}
