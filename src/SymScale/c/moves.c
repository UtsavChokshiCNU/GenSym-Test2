/* moves.c
 * Input file:  moves.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "moves.h"


DEFINE_VARIABLE_WITH_SYMBOL(Current_dragging_states, Qcurrent_dragging_states);

DEFINE_VARIABLE_WITH_SYMBOL(Available_dragging_conses, Qavailable_dragging_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_dragging_conses_tail, Qavailable_dragging_conses_tail);

Object Available_dragging_conses_vector = UNBOUND;

Object Available_dragging_conses_tail_vector = UNBOUND;

Object Dragging_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Dragging_cons_counter, Qdragging_cons_counter);

/* OUTSTANDING-DRAGGING-CONSES */
Object outstanding_dragging_conses()
{
    Object temp;

    x_note_fn_call(128,0);
    temp = FIXNUM_MINUS(Dragging_cons_counter,
	    length(Available_dragging_conses));
    return VALUES_1(temp);
}

/* DRAGGING-CONS-MEMORY-USAGE */
Object dragging_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(128,1);
    temp = FIXNUM_TIMES(Dragging_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-DRAGGING-CONS-POOL */
Object replenish_dragging_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(128,2);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qdragging_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_dragging_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_dragging_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_dragging_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_dragging_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_dragging_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Dragging_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qdragging;           /* dragging */

/* DRAGGING-CONS-1 */
Object dragging_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(128,3);
    new_cons = ISVREF(Available_dragging_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_dragging_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_dragging_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_dragging_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_dragging_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qdragging);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-DRAGGING-LIST-POOL */
Object replenish_dragging_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(128,4);
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
    if (ISVREF(Available_dragging_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_dragging_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_dragging_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_dragging_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_dragging_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qdragging_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-DRAGGING-LIST-1 */
Object make_dragging_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(128,5);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_dragging_conses_vector,
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
	replenish_dragging_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_dragging_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qdragging);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_dragging_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_dragging_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_dragging_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_dragging_conses_tail_vector;
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

/* DRAGGING-LIST-2 */
Object dragging_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(128,6);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_dragging_conses_vector,IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_dragging_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_dragging_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qdragging);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_dragging_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_dragging_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_dragging_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_dragging_conses_tail_vector;
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

/* DRAGGING-LIST-3 */
Object dragging_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(128,7);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_dragging_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_dragging_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_dragging_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qdragging);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_dragging_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_dragging_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_dragging_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_dragging_conses_tail_vector;
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

/* DRAGGING-LIST-4 */
Object dragging_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(128,8);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_dragging_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_dragging_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_dragging_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qdragging);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_dragging_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_dragging_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_dragging_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_dragging_conses_tail_vector;
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

/* DRAGGING-LIST-TRACE-HOOK */
Object dragging_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(128,9);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-DRAGGING-CONSES-1 */
Object copy_tree_using_dragging_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(128,10);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_dragging_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_dragging_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_dragging_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_dragging_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_dragging_cons_pool();
	temp_1 = copy_tree_using_dragging_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qdragging);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_dragging_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_dragging_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_dragging_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_dragging_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_dragging_cons_pool();
	temp_1 = copy_tree_using_dragging_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qdragging);
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

/* COPY-LIST-USING-DRAGGING-CONSES-1 */
Object copy_list_using_dragging_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(128,11);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_dragging_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_dragging_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_dragging_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_dragging_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_dragging_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qdragging);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_dragging_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_dragging_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_dragging_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_dragging_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_dragging_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qdragging);
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

/* RECLAIM-DRAGGING-CONS-1 */
Object reclaim_dragging_cons_1(dragging_cons)
    Object dragging_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(128,12);
    inline_note_reclaim_cons(dragging_cons,Qdragging);
    if (ISVREF(Available_dragging_conses_tail_vector,
	    IFIX(Current_thread_index))) {
	temp = ISVREF(Available_dragging_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = dragging_cons;
	temp = Available_dragging_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = dragging_cons;
    }
    else {
	temp = Available_dragging_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = dragging_cons;
	temp = Available_dragging_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = dragging_cons;
    }
    M_CDR(dragging_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-DRAGGING-LIST-1 */
Object reclaim_dragging_list_1(dragging_list)
    Object dragging_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(128,13);
    if (dragging_list) {
	last_1 = dragging_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qdragging);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qdragging);
	if (ISVREF(Available_dragging_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_dragging_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = dragging_list;
	    temp = Available_dragging_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_dragging_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = dragging_list;
	    temp = Available_dragging_conses_tail_vector;
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

/* RECLAIM-DRAGGING-LIST*-1 */
Object reclaim_dragging_list_star_1(dragging_list)
    Object dragging_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(128,14);
    if (CONSP(dragging_list)) {
	temp = last(dragging_list,_);
	M_CDR(temp) = Nil;
	if (dragging_list) {
	    last_1 = dragging_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qdragging);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qdragging);
	    if (ISVREF(Available_dragging_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_dragging_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = dragging_list;
		temp = Available_dragging_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_dragging_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = dragging_list;
		temp = Available_dragging_conses_tail_vector;
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

/* RECLAIM-DRAGGING-TREE-1 */
Object reclaim_dragging_tree_1(tree)
    Object tree;
{
    Object e, e2, dragging_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(128,15);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_dragging_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		dragging_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(dragging_cons,Qdragging);
		if (EQ(dragging_cons,e))
		    goto end_1;
		else if ( !TRUEP(dragging_cons))
		    goto end_1;
		else
		    dragging_cons = CDR(dragging_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_dragging_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_dragging_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_dragging_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_dragging_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_dragging_conses_tail_vector;
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

/* DELETE-DRAGGING-ELEMENT-1 */
Object delete_dragging_element_1(element,dragging_list)
    Object element, dragging_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(128,16);
    if (dragging_list) {
	if (EQ(element,M_CAR(dragging_list))) {
	    temp = CDR(dragging_list);
	    inline_note_reclaim_cons(dragging_list,Qdragging);
	    if (ISVREF(Available_dragging_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_dragging_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = dragging_list;
		temp_1 = Available_dragging_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = dragging_list;
	    }
	    else {
		temp_1 = Available_dragging_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = dragging_list;
		temp_1 = Available_dragging_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = dragging_list;
	    }
	    M_CDR(dragging_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = dragging_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qdragging);
		if (ISVREF(Available_dragging_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_dragging_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_dragging_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_dragging_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_dragging_conses_tail_vector;
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
	    temp = dragging_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-DRAGGING-CONS-1 */
Object delete_dragging_cons_1(dragging_cons,dragging_list)
    Object dragging_cons, dragging_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(128,17);
    if (EQ(dragging_cons,dragging_list))
	temp = CDR(dragging_list);
    else {
	l_trailer_qm = Nil;
	l = dragging_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,dragging_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = dragging_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_dragging_cons_1(dragging_cons);
    return VALUES_1(temp);
}

/* RECLAIM-DRAGGING-LIST-FUNCTION */
Object reclaim_dragging_list_function(list_1)
    Object list_1;
{
    Object last_1, next_qm, temp, svref_arg_2;

    x_note_fn_call(128,18);
    if (list_1) {
	last_1 = list_1;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qdragging);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qdragging);
	if (ISVREF(Available_dragging_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_dragging_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = list_1;
	    temp = Available_dragging_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_dragging_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = list_1;
	    temp = Available_dragging_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
	return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* DRAGGING-CONS-FUNCTION */
Object dragging_cons_function(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(128,19);
    new_cons = ISVREF(Available_dragging_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_dragging_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_dragging_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_dragging_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_dragging_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qdragging);
    return VALUES_1(gensymed_symbol);
}

/* RECLAIM-DRAGGING-CONS-FUNCTION */
Object reclaim_dragging_cons_function(a_cons)
    Object a_cons;
{
    x_note_fn_call(128,20);
    return reclaim_dragging_cons_1(a_cons);
}

Object The_type_description_of_dragging_state = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_dragging_states, Qchain_of_available_dragging_states);

DEFINE_VARIABLE_WITH_SYMBOL(Dragging_state_count, Qdragging_state_count);

Object Chain_of_available_dragging_states_vector = UNBOUND;

/* DRAGGING-STATE-STRUCTURE-MEMORY-USAGE */
Object dragging_state_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(128,21);
    temp = Dragging_state_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)27L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-DRAGGING-STATE-COUNT */
Object outstanding_dragging_state_count()
{
    Object def_structure_dragging_state_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(128,22);
    gensymed_symbol = IFIX(Dragging_state_count);
    def_structure_dragging_state_variable = Chain_of_available_dragging_states;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_dragging_state_variable))
	goto end_loop;
    def_structure_dragging_state_variable = 
	    ISVREF(def_structure_dragging_state_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-DRAGGING-STATE-1 */
Object reclaim_dragging_state_1(dragging_state)
    Object dragging_state;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(128,23);
    inline_note_reclaim_cons(dragging_state,Nil);
    structure_being_reclaimed = dragging_state;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      release_mouse_pointers(ISVREF(dragging_state,(SI_Long)1L));
      SVREF(dragging_state,FIX((SI_Long)1L)) = Nil;
      reclaim_frame_serial_number(ISVREF(dragging_state,(SI_Long)2L));
      SVREF(dragging_state,FIX((SI_Long)2L)) = Nil;
      reclaim_dragging_list_1(ISVREF(dragging_state,(SI_Long)3L));
      SVREF(dragging_state,FIX((SI_Long)3L)) = Nil;
      reclaim_dragging_list_of_pane_cursors(ISVREF(dragging_state,
	      (SI_Long)26L));
      SVREF(dragging_state,FIX((SI_Long)26L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_dragging_states_vector,
	    IFIX(Current_thread_index));
    SVREF(dragging_state,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_dragging_states_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = dragging_state;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-DRAGGING-STATE */
Object reclaim_structure_for_dragging_state(dragging_state)
    Object dragging_state;
{
    x_note_fn_call(128,24);
    return reclaim_dragging_state_1(dragging_state);
}

static Object Qg2_defstruct_structure_name_dragging_state_g2_struct;  /* g2-defstruct-structure-name::dragging-state-g2-struct */

/* MAKE-PERMANENT-DRAGGING-STATE-STRUCTURE-INTERNAL */
Object make_permanent_dragging_state_structure_internal()
{
    Object def_structure_dragging_state_variable;
    Object defstruct_g2_dragging_state_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(128,25);
    def_structure_dragging_state_variable = Nil;
    atomic_incff_symval(Qdragging_state_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_dragging_state_variable = Nil;
	gensymed_symbol = (SI_Long)27L;
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
	defstruct_g2_dragging_state_variable = the_array;
	SVREF(defstruct_g2_dragging_state_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_dragging_state_g2_struct;
	SVREF(defstruct_g2_dragging_state_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_dragging_state_variable,FIX((SI_Long)2L)) = Nil;
	def_structure_dragging_state_variable = 
		defstruct_g2_dragging_state_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_dragging_state_variable);
}

/* MAKE-DRAGGING-STATE-1 */
Object make_dragging_state_1(dragging_style,objects_being_dragged,
	    window_for_objects_being_dragged,
	    image_plane_showing_objects_being_dragged_qm,
	    x_offset_of_objects_being_dragged,
	    y_offset_of_objects_being_dragged,external_connections_to_drag,
	    workspace_for_objects_being_dragged_qm,
	    mouse_up_exits_this_context_qm,
	    original_workspace_of_objects_being_dragged_qm)
    Object dragging_style, objects_being_dragged;
    Object window_for_objects_being_dragged;
    Object image_plane_showing_objects_being_dragged_qm;
    Object x_offset_of_objects_being_dragged;
    Object y_offset_of_objects_being_dragged, external_connections_to_drag;
    Object workspace_for_objects_being_dragged_qm;
    Object mouse_up_exits_this_context_qm;
    Object original_workspace_of_objects_being_dragged_qm;
{
    Object def_structure_dragging_state_variable, temp, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(128,26);
    def_structure_dragging_state_variable = 
	    ISVREF(Chain_of_available_dragging_states_vector,
	    IFIX(Current_thread_index));
    if (def_structure_dragging_state_variable) {
	temp = Chain_of_available_dragging_states_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_dragging_state_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_dragging_state_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_dragging_state_g2_struct;
    }
    else
	def_structure_dragging_state_variable = 
		make_permanent_dragging_state_structure_internal();
    inline_note_allocate_cons(def_structure_dragging_state_variable,Nil);
    SVREF(def_structure_dragging_state_variable,FIX((SI_Long)21L)) = 
	    dragging_style;
    SVREF(def_structure_dragging_state_variable,FIX((SI_Long)3L)) = 
	    objects_being_dragged;
    SVREF(def_structure_dragging_state_variable,FIX((SI_Long)4L)) = 
	    window_for_objects_being_dragged;
    SVREF(def_structure_dragging_state_variable,FIX((SI_Long)5L)) = 
	    image_plane_showing_objects_being_dragged_qm;
    SVREF(def_structure_dragging_state_variable,FIX((SI_Long)8L)) = 
	    x_offset_of_objects_being_dragged;
    SVREF(def_structure_dragging_state_variable,FIX((SI_Long)9L)) = 
	    y_offset_of_objects_being_dragged;
    SVREF(def_structure_dragging_state_variable,FIX((SI_Long)6L)) = 
	    external_connections_to_drag;
    SVREF(def_structure_dragging_state_variable,FIX((SI_Long)7L)) = 
	    workspace_for_objects_being_dragged_qm;
    SVREF(def_structure_dragging_state_variable,FIX((SI_Long)12L)) = 
	    mouse_up_exits_this_context_qm;
    SVREF(def_structure_dragging_state_variable,FIX((SI_Long)25L)) = 
	    original_workspace_of_objects_being_dragged_qm;
    SVREF(def_structure_dragging_state_variable,FIX((SI_Long)1L)) = Nil;
    temp = copy_of_current_frame_serial_number_function();
    SVREF(def_structure_dragging_state_variable,FIX((SI_Long)2L)) = temp;
    SVREF(def_structure_dragging_state_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_dragging_state_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_dragging_state_variable,FIX((SI_Long)13L)) = Nil;
    SVREF(def_structure_dragging_state_variable,FIX((SI_Long)14L)) = Nil;
    SVREF(def_structure_dragging_state_variable,FIX((SI_Long)15L)) = Nil;
    SVREF(def_structure_dragging_state_variable,FIX((SI_Long)16L)) = Nil;
    SVREF(def_structure_dragging_state_variable,FIX((SI_Long)17L)) = Nil;
    SVREF(def_structure_dragging_state_variable,FIX((SI_Long)18L)) = Nil;
    SVREF(def_structure_dragging_state_variable,FIX((SI_Long)19L)) = Nil;
    SVREF(def_structure_dragging_state_variable,FIX((SI_Long)20L)) = Nil;
    ISVREF(def_structure_dragging_state_variable,(SI_Long)22L) = 
	    FIX((SI_Long)1L);
    ISVREF(def_structure_dragging_state_variable,(SI_Long)23L) = 
	    FIX((SI_Long)1L);
    SVREF(def_structure_dragging_state_variable,FIX((SI_Long)24L)) = Nil;
    SVREF(def_structure_dragging_state_variable,FIX((SI_Long)26L)) = Nil;
    return VALUES_1(def_structure_dragging_state_variable);
}

/* RECLAIM-DRAGGING-LIST-OF-PANE-CURSORS */
Object reclaim_dragging_list_of_pane_cursors(l)
    Object l;
{
    Object x, ab_loop_list_;

    x_note_fn_call(128,27);
    x = Nil;
    ab_loop_list_ = l;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    x = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_graphics_tree_1(x);
    goto next_loop;
  end_loop:;
    return reclaim_dragging_list_1(l);
}

DEFINE_VARIABLE_WITH_SYMBOL(Explicit_dragger_x_in_window_qm, Qexplicit_dragger_x_in_window_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Explicit_dragger_y_in_window_qm, Qexplicit_dragger_y_in_window_qm);

static Object Qmove_objects_beyond_workspace_margin;  /* move-objects-beyond-workspace-margin */

/* COMPUTE-MOVEMENT-CONTRAINTS */
Object compute_movement_contraints(workspace,blocks,outline,
	    external_connections_qm)
    Object workspace, blocks, outline, external_connections_qm;
{
    Object first_block, x_step_qm, y_step_qm, left_qm, top_qm, right_qm;
    Object bottom_qm, left_limit_qm, top_limit_qm, right_limit_qm;
    Object bottom_limit_qm, block, ab_loop_list_, ab_loop_it_;
    char temp;
    Object result;

    x_note_fn_call(128,28);
    first_block = FIRST(blocks);
    x_step_qm = Nil;
    y_step_qm = Nil;
    left_qm = Nil;
    top_qm = Nil;
    right_qm = Nil;
    bottom_qm = Nil;
    result = compute_snap_grid_for_block(1,first_block);
    MVS_2(result,x_step_qm,y_step_qm);
    result = movement_limits_for_block(first_block);
    MVS_4(result,left_limit_qm,top_limit_qm,right_limit_qm,bottom_limit_qm);
    temp = TRUEP(left_limit_qm);
    if (temp);
    else {
	block = Nil;
	ab_loop_list_ = outline;
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	block = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_it_ =  
		!TRUEP(non_menu_choice_permitted_p(Qmove_objects_beyond_workspace_margin,
		block)) ? T : Nil;
	if (ab_loop_it_) {
	    temp = TRUEP(ab_loop_it_);
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = TRUEP(Qnil);
      end_1:;
    }
    if (temp) {
	result = compute_movement_limits_for_blocks(workspace,blocks,
		external_connections_qm,left_limit_qm,top_limit_qm,
		right_limit_qm,bottom_limit_qm);
	MVS_4(result,left_qm,top_qm,right_qm,bottom_qm);
    }
    return VALUES_6(x_step_qm,y_step_qm,left_qm,top_qm,right_qm,bottom_qm);
}

static Object Qg2_defstruct_structure_name_image_plane_g2_struct;  /* g2-defstruct-structure-name::image-plane-g2-struct */

static Object Qimage_plane_dragging_style;  /* image-plane-dragging-style */

static Object Qmove_dragging_style;  /* move-dragging-style */

static Object Qtransfer_dragging_style;  /* transfer-dragging-style */

static Object Qmove_workspaces_beyond_window_margin;  /* move-workspaces-beyond-window-margin */

/* ENTER-DRAGGING-CONTEXT-1 */
Object enter_dragging_context_1 varargs_1(int, n)
{
    Object image_plane_block_or_blocks_to_drag, x_offset_from_dragger;
    Object y_offset_from_dragger, specific_image_plane_qm;
    Object mouse_up_exits_this_context_qm, assume_transfer_case_qm;
    Object image_plane_case_qm, image_plane_to_drag_qm, blocks_to_drag_qm;
    Object first_block_qm, outline, external_connections_to_drag_qm;
    Object dragging_confined_p, dragging_style;
    Object window_for_objects_being_dragged;
    Object image_plane_showing_objects_being_dragged_qm;
    Object workspace_for_objects_being_dragged_qm;
    Object original_workspace_of_objects_being_dragged_qm, dragging_state;
    Object image_plane, x_offset_of_image_plane_from_dragger;
    Object y_offset_of_image_plane_from_dragger, temp, temp_1;
    Object minimum_left_edge, minimum_top_edge, maximum_right_edge;
    Object maximum_bottom_edge, x_step_qm, y_step_qm, left_qm, top_qm;
    Object right_qm, bottom_qm, gensymed_symbol, current_frame_transform_qm;
    Object current_image_x_scale, current_image_y_scale;
    Object current_x_origin_of_drawing, current_y_origin_of_drawing, scale;
    Object value;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, svref_new_value;
    SI_Long unshifted_result;
    char move_case_p;
    Declare_varargs_nonrelocating;
    Declare_special(5);
    Object result;

    x_note_fn_call(128,29);
    INIT_ARGS_nonrelocating();
    image_plane_block_or_blocks_to_drag = REQUIRED_ARG_nonrelocating();
    x_offset_from_dragger = REQUIRED_ARG_nonrelocating();
    y_offset_from_dragger = REQUIRED_ARG_nonrelocating();
    specific_image_plane_qm = REQUIRED_ARG_nonrelocating();
    mouse_up_exits_this_context_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : mouse_down_p();
    assume_transfer_case_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    image_plane_case_qm = 
	    SIMPLE_VECTOR_P(image_plane_block_or_blocks_to_drag) ? 
	    (EQ(ISVREF(image_plane_block_or_blocks_to_drag,(SI_Long)0L),
	    Qg2_defstruct_structure_name_image_plane_g2_struct) ? T : Nil) 
	    : Qnil;
    image_plane_to_drag_qm = image_plane_case_qm ? 
	    image_plane_block_or_blocks_to_drag : Nil;
    if (image_plane_case_qm)
	blocks_to_drag_qm = Nil;
    else if (CONSP(image_plane_block_or_blocks_to_drag))
	blocks_to_drag_qm = image_plane_block_or_blocks_to_drag;
    else
	blocks_to_drag_qm = 
		dragging_cons_1(image_plane_block_or_blocks_to_drag,Nil);
    first_block_qm = FIRST(blocks_to_drag_qm);
    if (image_plane_case_qm)
	result = make_outline_for_image_plane_to_drag(image_plane_to_drag_qm,
		x_offset_from_dragger,y_offset_from_dragger);
    else
	result = make_outline_for_blocks_to_drag(blocks_to_drag_qm,
		assume_transfer_case_qm);
    MVS_3(result,outline,external_connections_to_drag_qm,dragging_confined_p);
    if (image_plane_case_qm)
	dragging_style = Qimage_plane_dragging_style;
    else if (dragging_confined_p ||  !TRUEP(assume_transfer_case_qm))
	dragging_style = Qmove_dragging_style;
    else
	dragging_style = Qtransfer_dragging_style;
    move_case_p = EQ(dragging_style,Qmove_dragging_style);
    window_for_objects_being_dragged = ISVREF(Current_workstation,(SI_Long)1L);
    image_plane_showing_objects_being_dragged_qm = move_case_p ? 
	    specific_image_plane_qm : Qnil;
    workspace_for_objects_being_dragged_qm = move_case_p ? 
	    ISVREF(specific_image_plane_qm,(SI_Long)5L) : Qnil;
    mouse_up_exits_this_context_qm = mouse_up_exits_this_context_qm ? ( 
	    !TRUEP(loose_end_dragging_outline_p(outline)) ? T : Nil) : Qnil;
    original_workspace_of_objects_being_dragged_qm = blocks_to_drag_qm ? 
	    get_workspace_if_any(first_block_qm) : Qnil;
    dragging_state = make_dragging_state_1(dragging_style,outline,
	    window_for_objects_being_dragged,
	    image_plane_showing_objects_being_dragged_qm,
	    x_offset_from_dragger,y_offset_from_dragger,
	    external_connections_to_drag_qm,
	    workspace_for_objects_being_dragged_qm,
	    mouse_up_exits_this_context_qm,
	    original_workspace_of_objects_being_dragged_qm);
    Current_dragging_states = dragging_cons_1(dragging_state,
	    Current_dragging_states);
    enter_context_in_current_workstation(2,Qdragging,dragging_state);
    if (blocks_to_drag_qm)
	start_rendering_dragging_state_for_move_or_transfer(dragging_state);
    if (image_plane_case_qm) {
	if ( 
		!TRUEP(non_menu_choice_permitted_p(Qmove_workspaces_beyond_window_margin,
		ISVREF(image_plane_to_drag_qm,(SI_Long)5L)))) {
	    image_plane = image_plane_to_drag_qm;
	    x_offset_of_image_plane_from_dragger = x_offset_from_dragger;
	    y_offset_of_image_plane_from_dragger = y_offset_from_dragger;
	    temp = ISVREF(image_plane,(SI_Long)6L);
	    temp_1 = FIXNUM_MINUS(ISVREF(image_plane,(SI_Long)8L),
		    FIXNUM_MINUS(ISVREF(image_plane,(SI_Long)17L),
		    ISVREF(image_plane,(SI_Long)15L)));
	    minimum_left_edge = FIXNUM_ADD(FIXNUM_MIN(temp,temp_1),
		    x_offset_of_image_plane_from_dragger);
	    temp = ISVREF(image_plane,(SI_Long)7L);
	    temp_1 = FIXNUM_MINUS(ISVREF(image_plane,(SI_Long)9L),
		    FIXNUM_MINUS(ISVREF(image_plane,(SI_Long)18L),
		    ISVREF(image_plane,(SI_Long)16L)));
	    minimum_top_edge = FIXNUM_ADD(FIXNUM_MIN(temp,temp_1),
		    y_offset_of_image_plane_from_dragger);
	    temp = FIXNUM_MINUS(ISVREF(image_plane,(SI_Long)8L),
		    FIXNUM_MINUS(ISVREF(image_plane,(SI_Long)17L),
		    ISVREF(image_plane,(SI_Long)15L)));
	    temp_1 = ISVREF(image_plane,(SI_Long)6L);
	    maximum_right_edge = FIXNUM_ADD(FIXNUM_MAX(temp,temp_1),
		    x_offset_of_image_plane_from_dragger);
	    temp = FIXNUM_MINUS(ISVREF(image_plane,(SI_Long)9L),
		    FIXNUM_MINUS(ISVREF(image_plane,(SI_Long)18L),
		    ISVREF(image_plane,(SI_Long)16L)));
	    temp_1 = ISVREF(image_plane,(SI_Long)7L);
	    maximum_bottom_edge = FIXNUM_ADD(FIXNUM_MAX(temp,temp_1),
		    y_offset_of_image_plane_from_dragger);
	    SVREF(dragging_state,FIX((SI_Long)13L)) = minimum_left_edge;
	    SVREF(dragging_state,FIX((SI_Long)14L)) = minimum_top_edge;
	    SVREF(dragging_state,FIX((SI_Long)15L)) = maximum_right_edge;
	    return VALUES_1(SVREF(dragging_state,FIX((SI_Long)16L)) = 
		    maximum_bottom_edge);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (move_case_p) {
	result = compute_movement_contraints(ISVREF(specific_image_plane_qm,
		(SI_Long)5L),blocks_to_drag_qm,outline,
		external_connections_to_drag_qm);
	MVS_6(result,x_step_qm,y_step_qm,left_qm,top_qm,right_qm,bottom_qm);
	if (x_step_qm && y_step_qm) {
	    SVREF(dragging_state,FIX((SI_Long)22L)) = x_step_qm;
	    SVREF(dragging_state,FIX((SI_Long)23L)) = y_step_qm;
	}
	if (left_qm) {
	    SVREF(dragging_state,FIX((SI_Long)13L)) = left_qm;
	    SVREF(dragging_state,FIX((SI_Long)14L)) = top_qm;
	    SVREF(dragging_state,FIX((SI_Long)15L)) = right_qm;
	    return VALUES_1(SVREF(dragging_state,FIX((SI_Long)16L)) = 
		    bottom_qm);
	}
	else
	    return VALUES_1(Nil);
    }
    else {
	compute_snap_grid_for_transfer(1,dragging_state);
	gensymed_symbol = ISVREF(first_block_qm,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = IFIX(x_offset_from_dragger);
	svref_new_value = gensymed_symbol_1 + gensymed_symbol_2;
	ISVREF(dragging_state,(SI_Long)17L) = FIX(svref_new_value);
	gensymed_symbol = ISVREF(first_block_qm,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = IFIX(y_offset_from_dragger);
	svref_new_value = gensymed_symbol_1 + gensymed_symbol_2;
	ISVREF(dragging_state,(SI_Long)18L) = FIX(svref_new_value);
	if (specific_image_plane_qm) {
	    current_frame_transform_qm = Nil;
	    current_image_x_scale = ISVREF(specific_image_plane_qm,
		    (SI_Long)11L);
	    current_image_y_scale = ISVREF(specific_image_plane_qm,
		    (SI_Long)12L);
	    current_x_origin_of_drawing = ISVREF(specific_image_plane_qm,
		    (SI_Long)13L);
	    current_y_origin_of_drawing = ISVREF(specific_image_plane_qm,
		    (SI_Long)14L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
		    4);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
		      3);
		PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
			2);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
			  1);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
			    0);
		      gensymed_symbol_1 = IFIX(Current_x_origin_of_drawing);
		      scale = Current_image_x_scale;
		      gensymed_symbol = ISVREF(first_block_qm,(SI_Long)14L);
		      gensymed_symbol = gensymed_symbol ? 
			      ISVREF(gensymed_symbol,(SI_Long)0L) : 
			      FIX((SI_Long)0L);
		      value = gensymed_symbol;
		      if (IFIX(scale) == (SI_Long)4096L)
			  gensymed_symbol_2 = IFIX(value);
		      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			      scale) && FIXNUM_LT(scale,
			      Isqrt_of_most_positive_fixnum) && 
			      FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			      value) && FIXNUM_LT(value,
			      Isqrt_of_most_positive_fixnum)) {
			  unshifted_result = IFIX(FIXNUM_TIMES(scale,
				  value)) + (SI_Long)2048L;
			  gensymed_symbol_2 = unshifted_result >>  -  - 
				  (SI_Long)12L;
		      }
		      else
			  gensymed_symbol_2 = IFIX(scalef_function(scale,
				  value));
		      svref_new_value = gensymed_symbol_1 + gensymed_symbol_2;
		      ISVREF(dragging_state,(SI_Long)19L) = 
			      FIX(svref_new_value);
		      gensymed_symbol_1 = IFIX(Current_y_origin_of_drawing);
		      scale = Current_image_y_scale;
		      gensymed_symbol = ISVREF(first_block_qm,(SI_Long)14L);
		      gensymed_symbol = gensymed_symbol ? 
			      ISVREF(gensymed_symbol,(SI_Long)1L) : 
			      FIX((SI_Long)0L);
		      value = gensymed_symbol;
		      if (IFIX(scale) == (SI_Long)4096L)
			  gensymed_symbol_2 = IFIX(value);
		      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			      scale) && FIXNUM_LT(scale,
			      Isqrt_of_most_positive_fixnum) && 
			      FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			      value) && FIXNUM_LT(value,
			      Isqrt_of_most_positive_fixnum)) {
			  unshifted_result = IFIX(FIXNUM_TIMES(scale,
				  value)) + (SI_Long)2048L;
			  gensymed_symbol_2 = unshifted_result >>  -  - 
				  (SI_Long)12L;
		      }
		      else
			  gensymed_symbol_2 = IFIX(scalef_function(scale,
				  value));
		      svref_new_value = gensymed_symbol_1 + gensymed_symbol_2;
		      result = VALUES_1(ISVREF(dragging_state,
			      (SI_Long)20L) = FIX(svref_new_value));
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    return result;
	}
	else
	    return VALUES_1(Nil);
    }
}

/* COMPUTE-SNAP-GRID-FOR-TRANSFER */
Object compute_snap_grid_for_transfer varargs_1(int, n)
{
    Object dragging_state;
    Object workspace_qm, temp, temp_1, x_step_qm, y_step_qm, svref_new_value;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(128,30);
    INIT_ARGS_nonrelocating();
    dragging_state = REQUIRED_ARG_nonrelocating();
    workspace_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(ignore_snap_grid_in_transfer_operations_p())) {
	temp = ISVREF(dragging_state,(SI_Long)3L);
	temp_1 = FIRST(temp);
	temp = workspace_qm;
	if (temp);
	else
	    temp = ISVREF(dragging_state,(SI_Long)25L);
	result = compute_snap_grid_for_block(2,temp_1,temp);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,x_step_qm,y_step_qm);
    svref_new_value = x_step_qm;
    if (svref_new_value);
    else
	svref_new_value = FIX((SI_Long)1L);
    SVREF(dragging_state,FIX((SI_Long)22L)) = svref_new_value;
    svref_new_value = y_step_qm;
    if (svref_new_value);
    else
	svref_new_value = FIX((SI_Long)1L);
    return VALUES_1(SVREF(dragging_state,FIX((SI_Long)23L)) = svref_new_value);
}

/* COMPUTE-MOVEMENT-LIMITS-FOR-BLOCKS */
Object compute_movement_limits_for_blocks(workspace,blocks,connections,
	    left_qm,top_qm,right_qm,bottom_qm)
    Object workspace, blocks, connections, left_qm, top_qm, right_qm;
    Object bottom_qm;
{
    Object first_block, gensymed_symbol, workspace_margin, left, top, right;
    Object bottom, extreme_left_edge, extreme_top_edge, extreme_right_edge;
    Object extreme_bottom_edge;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, block_width, block_height;
    SI_Long left_width, right_width, center, top_height, bottom_height;
    SI_Long gensymed_symbol_3, minimum_left_edge, minimum_top_edge;
    SI_Long maximum_right_edge, maximum_bottom_edge;
    Object result;

    x_note_fn_call(128,31);
    first_block = FIRST(blocks);
    gensymed_symbol = ISVREF(first_block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(first_block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    block_width = gensymed_symbol_1 - gensymed_symbol_2;
    gensymed_symbol = ISVREF(first_block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(first_block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    block_height = gensymed_symbol_1 - gensymed_symbol_2;
    workspace_margin = ISVREF(workspace,(SI_Long)17L);
    gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(workspace_margin);
    left = FIX(gensymed_symbol_1 + gensymed_symbol_2);
    gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(workspace_margin);
    top = FIX(gensymed_symbol_1 + gensymed_symbol_2);
    gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(workspace_margin);
    right = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(workspace_margin);
    bottom = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    if (left_qm) {
	left = FIXNUM_MAX(left,left_qm);
	top = FIXNUM_MAX(top,top_qm);
	right = FIXNUM_MIN(right,right_qm);
	bottom = FIXNUM_MIN(bottom,bottom_qm);
	if (IFIX(FIXNUM_MINUS(right,left)) < block_width) {
	    left_width = block_width >>  -  - (SI_Long)1L;
	    right_width = block_width - left_width;
	    center = IFIX(FIXNUM_ADD(left,right)) >>  -  - (SI_Long)1L;
	    left = FIX(center - left_width);
	    right = FIX(center + right_width);
	}
	if (IFIX(FIXNUM_MINUS(bottom,top)) < block_height) {
	    top_height = block_height >>  -  - (SI_Long)1L;
	    bottom_height = block_height - top_height;
	    center = IFIX(FIXNUM_ADD(top,bottom)) >>  -  - (SI_Long)1L;
	    top = FIX(center - top_height);
	    bottom = FIX(center + bottom_height);
	}
    }
    result = determine_extreme_edges_of_blocks_and_connections(blocks,
	    connections,T);
    MVS_4(result,extreme_left_edge,extreme_top_edge,extreme_right_edge,
	    extreme_bottom_edge);
    gensymed_symbol_1 = IFIX(left);
    gensymed_symbol = ISVREF(first_block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    gensymed_symbol_3 = IFIX(extreme_left_edge);
    gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
    minimum_left_edge = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol_1 = IFIX(top);
    gensymed_symbol = ISVREF(first_block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    gensymed_symbol_3 = IFIX(extreme_top_edge);
    gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
    minimum_top_edge = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol_1 = IFIX(right);
    gensymed_symbol_2 = IFIX(extreme_right_edge);
    gensymed_symbol = ISVREF(first_block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_3 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
    maximum_right_edge = gensymed_symbol_1 - gensymed_symbol_2;
    gensymed_symbol_1 = IFIX(bottom);
    gensymed_symbol_2 = IFIX(extreme_bottom_edge);
    gensymed_symbol = ISVREF(first_block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_3 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
    maximum_bottom_edge = gensymed_symbol_1 - gensymed_symbol_2;
    return VALUES_4(FIX(minimum_left_edge),FIX(minimum_top_edge),
	    FIX(maximum_right_edge),FIX(maximum_bottom_edge));
}

static Object Qimage_plane;        /* image-plane */

static Object Qavailable_frame_vector;  /* available-frame-vector */

/* FRAMES-CURRENTLY-BEING-DRAGGED-HAVE-BEEN-DELETED-P */
Object frames_currently_being_dragged_have_been_deleted_p(dragging_state)
    Object dragging_state;
{
    Object objects_being_dragged, workspace_qm, temp, gensymed_symbol, x, y;
    Object xa, ya, block, ab_loop_list_, ab_loop_it_;
    char temp_1;

    x_note_fn_call(128,32);
    objects_being_dragged = ISVREF(dragging_state,(SI_Long)3L);
    if ( !TRUEP(objects_being_dragged))
	return VALUES_1(T);
    else if (EQ(CAR(objects_being_dragged),Qimage_plane)) {
	workspace_qm = THIRD(objects_being_dragged);
	temp =  !TRUEP(workspace_qm) ? T : Nil;
	if (temp)
	    return VALUES_1(temp);
	else {
	    gensymed_symbol = ISVREF(workspace_qm,(SI_Long)3L);
	    temp_1 = SIMPLE_VECTOR_P(workspace_qm) ? 
		    EQ(ISVREF(workspace_qm,(SI_Long)1L),
		    Qavailable_frame_vector) : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) 
			== (SI_Long)-1L : TRUEP(Nil);
	    if (temp_1);
	    else {
		x = gensymed_symbol;
		y = ISVREF(dragging_state,(SI_Long)2L);
		if (FIXNUMP(y))
		    temp_1 = FIXNUMP(x) ? FIXNUM_LT(y,x) : TRUEP(T);
		else if (FIXNUMP(x))
		    temp_1 = TRUEP(Nil);
		else {
		    xa = M_CAR(y);
		    ya = M_CAR(x);
		    temp_1 = FIXNUM_LT(xa,ya);
		    if (temp_1);
		    else
			temp_1 = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),
				M_CDR(x)) : TRUEP(Qnil);
		}
	    }
	    temp =  ! !temp_1 ? T : Nil;
	    if (temp)
		return VALUES_1(temp);
	    else
		return VALUES_1( !EQ(workspace_qm,
			ISVREF(SECOND(objects_being_dragged),(SI_Long)5L)) 
			? T : Nil);
	}
    }
    else {
	block = Nil;
	ab_loop_list_ = objects_being_dragged;
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	block = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol = ISVREF(block,(SI_Long)3L);
	temp_1 = SIMPLE_VECTOR_P(block) ? EQ(ISVREF(block,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp_1);
	else
	    temp_1 = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp_1);
	else {
	    x = gensymed_symbol;
	    y = ISVREF(dragging_state,(SI_Long)2L);
	    if (FIXNUMP(y))
		temp_1 = FIXNUMP(x) ? FIXNUM_LT(y,x) : TRUEP(T);
	    else if (FIXNUMP(x))
		temp_1 = TRUEP(Nil);
	    else {
		xa = M_CAR(y);
		ya = M_CAR(x);
		temp_1 = FIXNUM_LT(xa,ya);
		if (temp_1);
		else
		    temp_1 = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),
			    M_CDR(x)) : TRUEP(Qnil);
	    }
	}
	ab_loop_it_ =  ! !temp_1 ? T : Nil;
	if (ab_loop_it_)
	    return VALUES_1(ab_loop_it_);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Do_not_invoke_rules_for_user_icon_movement_qm, Qdo_not_invoke_rules_for_user_icon_movement_qm);

/* TRIGGER-USER-ICON-MOVEMENT-RULES-FOR-BLOCKS */
Object trigger_user_icon_movement_rules_for_blocks(block_or_blocks)
    Object block_or_blocks;
{
    Object block, ab_loop_list_;

    x_note_fn_call(128,33);
    if ( !TRUEP(Do_not_invoke_rules_for_user_icon_movement_qm)) {
	if (CONSP(block_or_blocks)) {
	    block = Nil;
	    ab_loop_list_ = block_or_blocks;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    block = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    invoke_rules_for_user_icon_movement_if_necessary(block);
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
	else if (block_or_blocks)
	    return invoke_rules_for_user_icon_movement_if_necessary(block_or_blocks);
	else
	    return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* GATHER-CONNECTIONS-FOR-BLOCK */
Object gather_connections_for_block(block,connection_list)
    Object block, connection_list;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, temp, ab_less_than_branch_qm_;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(128,34);
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)6L)) : Nil;
    ab_skip_list_form_ = gensymed_symbol;
    ab_skip_list_p_ = Nil;
    ab_next_node_ = Nil;
    ab_tail_node_ = Nil;
    ab_current_alist_ = Nil;
    ab_entry_cons_ = Nil;
    ab_connection_ = Nil;
    ab_connection_item_ = Nil;
    connection = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      gensymed_symbol = CDR(ab_skip_list_form_);
      if (CONSP(gensymed_symbol)) {
	  temp = M_CAR(gensymed_symbol);
	  temp_1 = SIMPLE_VECTOR_P(temp);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  temp = M_CDR(gensymed_symbol);
	  ab_skip_list_p_ = SIMPLE_VECTOR_P(temp) ? T : Nil;
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
    next_loop:
    next_loop_1:
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
	    next_loop_2:
	      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
	      if ( !TRUEP(ab_less_than_branch_qm_))
		  goto end_loop;
	      ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
	      ab_current_node_ = ab_less_than_branch_qm_;
	      goto next_loop_2;
	    end_loop:;
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
      if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_)
	  goto end_1;
      goto next_loop_1;
    end_loop_1:
    end_1:
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_2;
      connection = ab_connection_;
      if ( !TRUEP(memq_function(connection,connection_list)))
	  connection_list = gensym_cons_1(connection,connection_list);
      goto next_loop;
    end_loop_2:;
    POP_SPECIAL();
    return VALUES_1(connection_list);
}

/* CONNECTIONS-MOVED-FOR-BLOCKS-MOVED */
Object connections_moved_for_blocks_moved(block_or_blocks)
    Object block_or_blocks;
{
    Object connections, block, ab_loop_list_, temp, gensymed_symbol;

    x_note_fn_call(128,35);
    if (LISTP(block_or_blocks)) {
	connections = Nil;
	block = Nil;
	ab_loop_list_ = block_or_blocks;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	block = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	connections = gather_connections_for_block(block,connections);
	goto next_loop;
      end_loop:
	temp = connections;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else {
	gensymed_symbol = ACCESS_ONCE(ISVREF(block_or_blocks,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
	temp = copy_list_using_gensym_conses_1(gensymed_symbol);
    }
    return VALUES_1(temp);
}

/* VALID-WORKSTATION-CONTEXT-P-FOR-DRAGGING-STATE */
Object valid_workstation_context_p_for_dragging_state(dragging_state)
    Object dragging_state;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(128,36);
    gensymed_symbol = 
	    ISVREF(ISVREF(ISVREF(The_type_description_of_dragging_state,
	    (SI_Long)9L),(SI_Long)0L),(SI_Long)4L);
    gensymed_symbol_1 = dragging_state;
    if (inline_funcall_1(gensymed_symbol,gensymed_symbol_1) ? 
	    (EQ(ISVREF(dragging_state,(SI_Long)21L),Qmove_dragging_style) ?
	     TRUEP(valid_image_plane_p(ISVREF(dragging_state,
	    (SI_Long)5L))) : TRUEP(T)) : TRUEP(Nil))
	return VALUES_1( 
		!TRUEP(frames_currently_being_dragged_have_been_deleted_p(dragging_state)) 
		? T : Nil);
    else
	return VALUES_1(Nil);
}

/* MOUSE-MOTION-IN-DRAGGING-STATE */
Object mouse_motion_in_dragging_state(mouse_pointer)
    Object mouse_pointer;
{
    Object dragging_state, x_in_window, y_in_window;
    Object explicit_dragger_x_in_window_qm, explicit_dragger_y_in_window_qm;
    Declare_special(2);
    Object result;

    x_note_fn_call(128,37);
    dragging_state = 
	    workstation_context_specifics_blackboard_function(mouse_pointer);
    x_in_window = x_in_window_blackboard_function(mouse_pointer);
    y_in_window = y_in_window_blackboard_function(mouse_pointer);
    if (dragging_state && x_in_window && y_in_window) {
	explicit_dragger_x_in_window_qm = x_in_window;
	explicit_dragger_y_in_window_qm = y_in_window;
	PUSH_SPECIAL_WITH_SYMBOL(Explicit_dragger_y_in_window_qm,Qexplicit_dragger_y_in_window_qm,explicit_dragger_y_in_window_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Explicit_dragger_x_in_window_qm,Qexplicit_dragger_x_in_window_qm,explicit_dragger_x_in_window_qm,
		  0);
	    result = drag_outline_if_appropriate(dragging_state,Nil);
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* MOUSE-DOWN-IN-DRAGGING-STATE */
Object mouse_down_in_dragging_state(mouse_pointer)
    Object mouse_pointer;
{
    Object mouse_pointer_1, dragging_state, x_in_window, y_in_window;
    Object explicit_dragger_x_in_window_qm, explicit_dragger_y_in_window_qm;
    Declare_special(2);
    Object result;

    x_note_fn_call(128,38);
    mouse_pointer_1 = mouse_pointer_blackboard_function(mouse_pointer);
    dragging_state = 
	    workstation_context_specifics_blackboard_function(mouse_pointer);
    x_in_window = x_in_window_blackboard_function(mouse_pointer);
    y_in_window = y_in_window_blackboard_function(mouse_pointer);
    if (mouse_pointer_1 && dragging_state && x_in_window && y_in_window) {
	mouse_motion_in_dragging_state(mouse_pointer_1);
	explicit_dragger_x_in_window_qm = x_in_window;
	explicit_dragger_y_in_window_qm = y_in_window;
	PUSH_SPECIAL_WITH_SYMBOL(Explicit_dragger_y_in_window_qm,Qexplicit_dragger_y_in_window_qm,explicit_dragger_y_in_window_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Explicit_dragger_x_in_window_qm,Qexplicit_dragger_x_in_window_qm,explicit_dragger_x_in_window_qm,
		  0);
	    result = return_from_dragging_context(dragging_state);
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* MOUSE-UP-IN-DRAGGING-STATE */
Object mouse_up_in_dragging_state(mouse_pointer)
    Object mouse_pointer;
{
    Object mouse_pointer_1, dragging_state, x_in_window, y_in_window;
    Object explicit_dragger_x_in_window_qm, explicit_dragger_y_in_window_qm;
    Declare_special(2);
    Object result;

    x_note_fn_call(128,39);
    mouse_pointer_1 = mouse_pointer_blackboard_function(mouse_pointer);
    dragging_state = 
	    workstation_context_specifics_blackboard_function(mouse_pointer);
    x_in_window = x_in_window_blackboard_function(mouse_pointer);
    y_in_window = y_in_window_blackboard_function(mouse_pointer);
    if (mouse_pointer_1 && dragging_state && x_in_window && y_in_window) {
	mouse_motion_in_dragging_state(mouse_pointer_1);
	if (ISVREF(dragging_state,(SI_Long)12L)) {
	    explicit_dragger_x_in_window_qm = x_in_window;
	    explicit_dragger_y_in_window_qm = y_in_window;
	    PUSH_SPECIAL_WITH_SYMBOL(Explicit_dragger_y_in_window_qm,Qexplicit_dragger_y_in_window_qm,explicit_dragger_y_in_window_qm,
		    1);
	      PUSH_SPECIAL_WITH_SYMBOL(Explicit_dragger_x_in_window_qm,Qexplicit_dragger_x_in_window_qm,explicit_dragger_x_in_window_qm,
		      0);
		result = return_from_dragging_context(dragging_state);
	      POP_SPECIAL();
	    POP_SPECIAL();
	    return result;
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* CLEAN-UP-WORKSTATION-CONTEXT-FOR-DRAGGING-STATE */
Object clean_up_workstation_context_for_dragging_state(dragging_state)
    Object dragging_state;
{
    Object temp, objects_being_dragged, image_plane_qm, gensymed_symbol;
    Object gensymed_symbol_1;

    x_note_fn_call(128,40);
    temp = ISVREF(dragging_state,(SI_Long)21L);
    if (EQ(temp,Qimage_plane_dragging_style))
	erase_outline_of_image_plane_being_dragged(1,dragging_state);
    else {
	if ( 
		!TRUEP(frames_currently_being_dragged_have_been_deleted_p(dragging_state)))
	    stop_rendering_dragging_state_for_move_or_transfer(dragging_state);
	if ( !TRUEP(ISVREF(dragging_state,(SI_Long)7L))) {
	    objects_being_dragged = ISVREF(dragging_state,(SI_Long)3L);
	    SVREF(dragging_state,FIX((SI_Long)3L)) = Nil;
	    delete_blocks_from_list_in_limbo(objects_being_dragged,
		    ISVREF(dragging_state,(SI_Long)2L));
	    reclaim_dragging_list_1(objects_being_dragged);
	}
	image_plane_qm = ISVREF(dragging_state,(SI_Long)5L);
	if (image_plane_qm)
	    remove_image_plane_cursor(image_plane_qm,dragging_state);
    }
    Current_dragging_states = delete_dragging_element_1(dragging_state,
	    Current_dragging_states);
    gensymed_symbol = 
	    ISVREF(ISVREF(ISVREF(The_type_description_of_dragging_state,
	    (SI_Long)9L),(SI_Long)0L),(SI_Long)1L);
    gensymed_symbol_1 = dragging_state;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* DELETE-BLOCKS-FROM-LIST-IN-LIMBO */
Object delete_blocks_from_list_in_limbo(blocks,reference_serial_number)
    Object blocks, reference_serial_number;
{
    Object fsn, block, ab_loop_list_, gensymed_symbol, xa, ya;
    char temp;

    x_note_fn_call(128,41);
    fsn = copy_frame_serial_number(reference_serial_number);
    block = Nil;
    ab_loop_list_ = blocks;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    block = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = ISVREF(block,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(block) ? EQ(ISVREF(block,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(fsn))
	temp = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(fsn,gensymed_symbol) : 
		TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(fsn);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(fsn),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    if (temp);
    else {
	gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	temp = TRUEP(gensymed_symbol);
    }
    if ( !temp)
	delete_frame(block);
    goto next_loop;
  end_loop:;
    return reclaim_frame_serial_number(fsn);
}

static Object Qloose_end;          /* loose-end */

/* RETURN-FROM-DRAGGING-CONTEXT */
Object return_from_dragging_context(dragging_state)
    Object dragging_state;
{
    Object temp, svref_new_value, list_1, frame, symbol, gensymed_symbol;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;

    x_note_fn_call(128,42);
    temp = ISVREF(dragging_state,(SI_Long)21L);
    if (EQ(temp,Qimage_plane_dragging_style))
	return return_from_dragging_context_to_move_image_plane(dragging_state);
    else {
	if (ISVREF(dragging_state,(SI_Long)3L) && ISVREF(dragging_state,
		(SI_Long)5L)) {
	    svref_new_value = ISVREF(ISVREF(dragging_state,(SI_Long)5L),
		    (SI_Long)5L);
	    temp_1 = TRUEP(SVREF(dragging_state,FIX((SI_Long)7L)) = 
		    svref_new_value);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    list_1 = ISVREF(dragging_state,(SI_Long)3L);
	    if (CONSP(list_1) &&  !TRUEP(CDR(list_1))) {
		temp = ISVREF(dragging_state,(SI_Long)3L);
		frame = FIRST(temp);
		symbol = Qloose_end;
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(symbol,
			Class_description_gkbprop);
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
			temp_1 = (SI_Long)0L < gensymed_symbol_1;
		    }
		    else
			temp_1 = TRUEP(Nil);
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		return finish_connection_dragging(dragging_state);
	    else {
		temp = ISVREF(dragging_state,(SI_Long)21L);
		if (EQ(temp,Qmove_dragging_style))
		    return return_from_move_dragging_style(dragging_state);
		else if (EQ(temp,Qtransfer_dragging_style))
		    return return_from_transfer_dragging_style(dragging_state);
		else
		    return VALUES_1(Qnil);
	    }
	}
	else {
	    beep_at_user();
	    return abort_current_workstation_context(Qdragging);
	}
    }
}

static Object Qmove_image_plane_upon_continuation_after_dragging;  /* move-image-plane-upon-continuation-after-dragging */

/* ENTER-IMAGE-PLANE-DRAGGING-CONTEXT */
Object enter_image_plane_dragging_context varargs_1(int, n)
{
    Object image_plane, x_offset_from_dragger, y_offset_from_dragger;
    Object mouse_up_exits_this_context_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(128,43);
    INIT_ARGS_nonrelocating();
    image_plane = REQUIRED_ARG_nonrelocating();
    x_offset_from_dragger = REQUIRED_ARG_nonrelocating();
    y_offset_from_dragger = REQUIRED_ARG_nonrelocating();
    mouse_up_exits_this_context_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : mouse_down_p();
    END_ARGS_nonrelocating();
    establish_next_workstation_context_continuation(Qmove_image_plane_upon_continuation_after_dragging,
	    Nil,Nil,Nil);
    return enter_dragging_context_1(6,image_plane,x_offset_from_dragger,
	    y_offset_from_dragger,Nil,mouse_up_exits_this_context_qm,Nil);
}

/* RETURN-FROM-DRAGGING-CONTEXT-TO-MOVE-IMAGE-PLANE */
Object return_from_dragging_context_to_move_image_plane(dragging_state)
    Object dragging_state;
{
    Object temp, image_plane, x, u_1, step_qm, min_qm, max_qm, ur, y;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(128,44);
    temp = ISVREF(dragging_state,(SI_Long)3L);
    image_plane = SECOND(temp);
    x = Explicit_dragger_x_in_window_qm;
    if (x);
    else
	x = ISVREF(Current_workstation,(SI_Long)5L);
    u_1 = x;
    step_qm = ISVREF(dragging_state,(SI_Long)22L);
    min_qm = ISVREF(dragging_state,(SI_Long)13L);
    max_qm = ISVREF(dragging_state,(SI_Long)15L);
    ur = u_1;
    if (step_qm)
	ur = FIXNUM_TIMES(step_qm,l_round(u_1,step_qm));
    if (min_qm)
	ur = FIXNUM_MAX(ur,min_qm);
    if (max_qm)
	ur = FIXNUM_MIN(ur,max_qm);
    gensymed_symbol = IFIX(ur);
    gensymed_symbol_1 = IFIX(FIXNUM_ADD(ISVREF(image_plane,(SI_Long)15L),
	    ISVREF(dragging_state,(SI_Long)8L)));
    temp = FIX(gensymed_symbol - gensymed_symbol_1);
    y = Explicit_dragger_y_in_window_qm;
    if (y);
    else
	y = ISVREF(Current_workstation,(SI_Long)6L);
    u_1 = y;
    step_qm = ISVREF(dragging_state,(SI_Long)23L);
    min_qm = ISVREF(dragging_state,(SI_Long)14L);
    max_qm = ISVREF(dragging_state,(SI_Long)16L);
    ur = u_1;
    if (step_qm)
	ur = FIXNUM_TIMES(step_qm,l_round(u_1,step_qm));
    if (min_qm)
	ur = FIXNUM_MAX(ur,min_qm);
    if (max_qm)
	ur = FIXNUM_MIN(ur,max_qm);
    gensymed_symbol = IFIX(ur);
    gensymed_symbol_1 = IFIX(FIXNUM_ADD(ISVREF(image_plane,(SI_Long)16L),
	    ISVREF(dragging_state,(SI_Long)9L)));
    return return_from_current_workstation_context(4,Qdragging,image_plane,
	    temp,FIX(gensymed_symbol - gensymed_symbol_1));
}

/* MOVE-IMAGE-PLANE-UPON-CONTINUATION-AFTER-DRAGGING */
Object move_image_plane_upon_continuation_after_dragging(workstation_context)
    Object workstation_context;
{
    Object image_plane, delta_x_in_window, delta_y_in_window, workspace;

    x_note_fn_call(128,45);
    image_plane = ISVREF(Current_workstation,(SI_Long)33L);
    delta_x_in_window = ISVREF(Current_workstation,(SI_Long)34L);
    delta_y_in_window = ISVREF(Current_workstation,(SI_Long)35L);
    if ( !EQ(image_plane,Kabort)) {
	move_image_plane(image_plane,delta_x_in_window,delta_y_in_window);
	workspace = ISVREF(image_plane,(SI_Long)5L);
	if (workspace)
	    trigger_user_icon_movement_rules_for_blocks(workspace);
	return require_that_image_plane_be_visible(1,image_plane);
    }
    else
	return VALUES_1(Nil);
}

Object Constant_mouse_leeway = UNBOUND;

Object Scalable_mouse_leeway = UNBOUND;

static Object Qg2_defstruct_structure_name_connection_g2_struct;  /* g2-defstruct-structure-name::connection-g2-struct */

static Object Qjoined_connections;  /* joined-connections */

static Object Qadded_connection_to_block;  /* added-connection-to-block */

static Object Qmade_junction;      /* made-junction */

static Object Qdeleted_stub;       /* deleted-stub */

static Object Qconnection_style;   /* connection-style */

static Object Qdiagonal;           /* diagonal */

/* FINISH-CONNECTION-DRAGGING */
Object finish_connection_dragging(dragging_state)
    Object dragging_state;
{
    Object objects_being_dragged, final_image_plane, loose_end;
    Object connection_being_dragged, object_near_loose_end_qm, end_dragging_p;
    Object connection_type, connection_was_not_made_p, joined_connection;
    Object sub_class_bit_vector, exit_dragging_context_qm, link_1_delta;
    Object link_2_delta, scale, value, d1, d2, gensymed_symbol_3, plist;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, temp_1, maximum_mouse_leeway;
    char temp;
    Object result;

    x_note_fn_call(128,46);
    objects_being_dragged = ISVREF(dragging_state,(SI_Long)3L);
    final_image_plane = ISVREF(dragging_state,(SI_Long)5L);
    loose_end = FIRST(objects_being_dragged);
    connection_being_dragged = get_connection_for_loose_end(loose_end);
    object_near_loose_end_qm = 
	    find_object_near_loose_end_being_dragged(loose_end,
	    connection_being_dragged,final_image_plane);
    end_dragging_p = Nil;
    connection_type = Nil;
    connection_was_not_made_p = Nil;
    joined_connection = Nil;
    if (object_near_loose_end_qm) {
	if ( !(SIMPLE_VECTOR_P(object_near_loose_end_qm) && 
		EQ(ISVREF(object_near_loose_end_qm,(SI_Long)0L),
		Qg2_defstruct_structure_name_connection_g2_struct))) {
	    sub_class_bit_vector = ISVREF(ISVREF(object_near_loose_end_qm,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Loose_end_class_description,(SI_Long)18L));
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
		connection_type = Qjoined_connections;
		result = join_two_connections(loose_end,
			object_near_loose_end_qm);
		MVS_2(result,end_dragging_p,joined_connection);
	    }
	    else {
		connection_type = Qadded_connection_to_block;
		result = add_new_connection_to_block(2,loose_end,
			object_near_loose_end_qm);
		MVS_2(result,end_dragging_p,connection_was_not_made_p);
		if (G2_has_v5_mode_windows_p &&  
			!TRUEP(connection_was_not_made_p))
		    send_ws_representations_connection_moved(connection_being_dragged);
	    }
	}
	else {
	    connection_type = Qmade_junction;
	    end_dragging_p = make_junction(object_near_loose_end_qm,loose_end);
	    if (G2_has_v5_mode_windows_p) {
		send_ws_representations_connection_moved(connection_being_dragged);
		send_ws_representations_connection_moved(object_near_loose_end_qm);
	    }
	}
    }
    if (end_dragging_p) {
	invoke_connection_handler_if_any(connection_was_not_made_p ? 
		object_near_loose_end_qm : connection_being_dragged,
		ISVREF(ISVREF(ISVREF(dragging_state,(SI_Long)4L),
		(SI_Long)2L),(SI_Long)25L),connection_was_not_made_p ? 
		Qdeleted_stub : connection_type, 
		!TRUEP(connection_was_not_made_p) && EQ(connection_type,
		Qadded_connection_to_block) ? object_near_loose_end_qm : Qnil);
	if ( !TRUEP(connection_was_not_made_p)) {
	    if (EQ(connection_type,Qadded_connection_to_block)) {
		invoke_rules_for_direct_connection_chaining(connection_being_dragged,
			Nil);
		invoke_rules_for_indirect_connection_chaining(connection_being_dragged,
			Nil);
	    }
	    else if (EQ(connection_type,Qjoined_connections)) {
		invoke_rules_for_direct_connection_chaining(joined_connection,
			Nil);
		invoke_rules_for_indirect_connection_chaining(joined_connection,
			Nil);
	    }
	    else if (EQ(connection_type,Qmade_junction))
		invoke_rules_for_indirect_connection_chaining(connection_being_dragged,
			Nil);
	}
	return return_from_current_workstation_context(1,Qdragging);
    }
    else if ( !TRUEP(object_near_loose_end_qm)) {
	exit_dragging_context_qm = Nil;
	result = compute_stretched_links_of_connection_being_dragged(connection_being_dragged,
		loose_end);
	MVS_2(result,link_1_delta,link_2_delta);
	gensymed_symbol = IFIX(Constant_mouse_leeway);
	scale = ISVREF(final_image_plane,(SI_Long)11L);
	value = Scalable_mouse_leeway;
	if (IFIX(scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(value);
	else if ( !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		value) && FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)))
	    gensymed_symbol_1 = IFIX(inverse_scalef_function(scale,value));
	else if (IFIX(value) >= (SI_Long)0L) {
	    temp_1 = ((IFIX(value) << (SI_Long)12L) + (IFIX(scale) >>  -  
		    - (SI_Long)1L)) / IFIX(scale);
	    gensymed_symbol_1 = temp_1;
	}
	else {
	    temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << (SI_Long)12L) + 
		    (IFIX(scale) >>  -  - (SI_Long)1L)) / IFIX(scale);
	    temp_1 = IFIX(FIXNUM_NEGATE(FIX(temp_1)));
	    gensymed_symbol_1 = temp_1;
	}
	maximum_mouse_leeway = gensymed_symbol + gensymed_symbol_1;
	d1 = FIXNUM_ABS(link_1_delta);
	d2 = FIXNUM_ABS(link_2_delta);
	if (place_connection_if_orthogonal_qm(connection_being_dragged,d1,
		d2,FIX(maximum_mouse_leeway))) {
	    gensymed_symbol_3 = ACCESS_ONCE(ISVREF(loose_end,(SI_Long)14L));
	    gensymed_symbol_3 = gensymed_symbol_3 ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)5L)) : Nil;
	    update_connection_images(T,gensymed_symbol_3,
		    connection_being_dragged);
	    delete_last_bend_from_connection(connection_being_dragged,
		    loose_end);
	    gensymed_symbol_3 = ACCESS_ONCE(ISVREF(loose_end,(SI_Long)14L));
	    gensymed_symbol_3 = gensymed_symbol_3 ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)5L)) : Nil;
	    update_connection_images(Nil,gensymed_symbol_3,
		    connection_being_dragged);
	    exit_dragging_context_qm = T;
	}
	else {
	    gensymed_symbol_3 = ACCESS_ONCE(ISVREF(loose_end,(SI_Long)14L));
	    gensymed_symbol_3 = gensymed_symbol_3 ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)5L)) : Nil;
	    update_images_of_blocks_and_connections_being_moved(T,
		    gensymed_symbol_3,objects_being_dragged,
		    ISVREF(dragging_state,(SI_Long)6L));
	    if (loose_end_near_last_anchor_point_qm(d1,d2,
		    FIX(maximum_mouse_leeway)))
		exit_dragging_context_qm = 
			handle_connection_click_near_last_anchor_point(connection_being_dragged,
			loose_end);
	    else {
		plist = ISVREF(connection_being_dragged,(SI_Long)9L);
		if ( !(plist && EQ(getfq_function_no_default(plist,
			Qconnection_style),Qdiagonal)) ? IFIX(d1) < 
			maximum_mouse_leeway : TRUEP(Nil))
		    remove_kink_and_add_bend(connection_being_dragged,
			    loose_end,link_1_delta);
		else
		    add_bend_to_connection(connection_being_dragged,loose_end);
	    }
	    gensymed_symbol_3 = ACCESS_ONCE(ISVREF(loose_end,(SI_Long)14L));
	    gensymed_symbol_3 = gensymed_symbol_3 ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)5L)) : Nil;
	    update_images_of_blocks_and_connections_being_moved(Nil,
		    gensymed_symbol_3,objects_being_dragged,
		    ISVREF(dragging_state,(SI_Long)6L));
	}
	if (connection_being_dragged && G2_has_v5_mode_windows_p)
	    send_ws_representations_connection_moved(connection_being_dragged);
	if (exit_dragging_context_qm)
	    return return_from_current_workstation_context(1,Qdragging);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Qnil);
}

Object Classes_that_do_not_normally_connect = UNBOUND;

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* FIND-OBJECT-NEAR-LOOSE-END-BEING-DRAGGED */
Object find_object_near_loose_end_being_dragged(loose_end,connection,
	    final_image_plane)
    Object loose_end, connection, final_image_plane;
{
    Object objects_to_not_consider, object_qm, temp, temp_1, x2;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_2;

    x_note_fn_call(128,47);
    objects_to_not_consider = dragging_list_2(loose_end,connection);
    object_qm = Nil;
  next_loop:
    temp = Explicit_dragger_x_in_window_qm;
    if (temp);
    else
	temp = ISVREF(Current_workstation,(SI_Long)5L);
    temp_1 = Explicit_dragger_y_in_window_qm;
    if (temp_1);
    else
	temp_1 = ISVREF(Current_workstation,(SI_Long)6L);
    object_qm = find_object_near_mouse(temp,temp_1,final_image_plane,
	    objects_to_not_consider,Classes_that_do_not_normally_connect);
    if (object_qm) {
	if (SIMPLE_VECTOR_P(object_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(object_qm)) > (SI_Long)2L 
		&&  !EQ(ISVREF(object_qm,(SI_Long)1L),
		    Qavailable_frame_vector)) {
	    x2 = ISVREF(object_qm,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2 ? TRUEP(no_manual_connections_p(object_qm)) : TRUEP(Nil)) {
	sub_class_bit_vector = ISVREF(ISVREF(object_qm,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Loose_end_class_description,(SI_Long)18L));
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
	temp_2 =  !temp_2;
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2)
	objects_to_not_consider = dragging_cons_1(object_qm,
		objects_to_not_consider);
    else {
	temp_1 = object_qm;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp_1 = Qnil;
  end_1:;
    reclaim_dragging_list_1(objects_to_not_consider);
    return VALUES_1(temp_1);
}

/* SUSPEND-WORKSTATION-CONTEXT-FOR-DRAGGING-STATE */
Object suspend_workstation_context_for_dragging_state(dragging_state)
    Object dragging_state;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_new_value;

    x_note_fn_call(128,48);
    gensymed_symbol = 
	    ISVREF(ISVREF(ISVREF(The_type_description_of_dragging_state,
	    (SI_Long)9L),(SI_Long)0L),(SI_Long)6L);
    gensymed_symbol_1 = dragging_state;
    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    temp = ISVREF(dragging_state,(SI_Long)21L);
    if (EQ(temp,Qimage_plane_dragging_style)) {
	svref_new_value = erase_outline_of_image_plane_being_dragged(2,
		dragging_state,T);
	return VALUES_1(SVREF(dragging_state,FIX((SI_Long)26L)) = 
		svref_new_value);
    }
    else
	return VALUES_1(Nil);
}

/* RESUME-WORKSTATION-CONTEXT-FOR-DRAGGING-STATE */
Object resume_workstation_context_for_dragging_state(dragging_state)
    Object dragging_state;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_new_value;

    x_note_fn_call(128,49);
    gensymed_symbol = 
	    ISVREF(ISVREF(ISVREF(The_type_description_of_dragging_state,
	    (SI_Long)9L),(SI_Long)0L),(SI_Long)7L);
    gensymed_symbol_1 = dragging_state;
    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    temp = ISVREF(dragging_state,(SI_Long)21L);
    if (EQ(temp,Qimage_plane_dragging_style)) {
	svref_new_value = mouse_down_p();
	SVREF(dragging_state,FIX((SI_Long)12L)) = svref_new_value;
	temp = ISVREF(dragging_state,(SI_Long)26L);
	SVREF(dragging_state,FIX((SI_Long)26L)) = Nil;
	restore_outline_of_image_plane_being_dragged(dragging_state,temp);
	return drag_outline_if_appropriate(dragging_state,Nil);
    }
    else
	return VALUES_1(Nil);
}

Object The_type_description_of_move_dragging_state = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_move_dragging_states, Qchain_of_available_move_dragging_states);

DEFINE_VARIABLE_WITH_SYMBOL(Move_dragging_state_count, Qmove_dragging_state_count);

Object Chain_of_available_move_dragging_states_vector = UNBOUND;

/* MOVE-DRAGGING-STATE-STRUCTURE-MEMORY-USAGE */
Object move_dragging_state_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(128,50);
    temp = Move_dragging_state_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)3L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-MOVE-DRAGGING-STATE-COUNT */
Object outstanding_move_dragging_state_count()
{
    Object def_structure_move_dragging_state_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(128,51);
    gensymed_symbol = IFIX(Move_dragging_state_count);
    def_structure_move_dragging_state_variable = 
	    Chain_of_available_move_dragging_states;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_move_dragging_state_variable))
	goto end_loop;
    def_structure_move_dragging_state_variable = 
	    ISVREF(def_structure_move_dragging_state_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-MOVE-DRAGGING-STATE-1 */
Object reclaim_move_dragging_state_1(move_dragging_state)
    Object move_dragging_state;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(128,52);
    inline_note_reclaim_cons(move_dragging_state,Nil);
    structure_being_reclaimed = move_dragging_state;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      release_mouse_pointers(ISVREF(move_dragging_state,(SI_Long)1L));
      SVREF(move_dragging_state,FIX((SI_Long)1L)) = Nil;
      reclaim_frame_serial_number(ISVREF(move_dragging_state,(SI_Long)2L));
      SVREF(move_dragging_state,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_move_dragging_states_vector,
	    IFIX(Current_thread_index));
    SVREF(move_dragging_state,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_move_dragging_states_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = move_dragging_state;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-MOVE-DRAGGING-STATE */
Object reclaim_structure_for_move_dragging_state(move_dragging_state)
    Object move_dragging_state;
{
    x_note_fn_call(128,53);
    return reclaim_move_dragging_state_1(move_dragging_state);
}

static Object Qg2_defstruct_structure_name_move_dragging_state_g2_struct;  /* g2-defstruct-structure-name::move-dragging-state-g2-struct */

/* MAKE-PERMANENT-MOVE-DRAGGING-STATE-STRUCTURE-INTERNAL */
Object make_permanent_move_dragging_state_structure_internal()
{
    Object def_structure_move_dragging_state_variable;
    Object defstruct_g2_move_dragging_state_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(128,54);
    def_structure_move_dragging_state_variable = Nil;
    atomic_incff_symval(Qmove_dragging_state_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_move_dragging_state_variable = Nil;
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
	defstruct_g2_move_dragging_state_variable = the_array;
	SVREF(defstruct_g2_move_dragging_state_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_move_dragging_state_g2_struct;
	SVREF(defstruct_g2_move_dragging_state_variable,FIX((SI_Long)1L)) 
		= Nil;
	SVREF(defstruct_g2_move_dragging_state_variable,FIX((SI_Long)2L)) 
		= Nil;
	def_structure_move_dragging_state_variable = 
		defstruct_g2_move_dragging_state_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_move_dragging_state_variable);
}

/* MAKE-MOVE-DRAGGING-STATE-1 */
Object make_move_dragging_state_1()
{
    Object def_structure_move_dragging_state_variable, temp, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(128,55);
    def_structure_move_dragging_state_variable = 
	    ISVREF(Chain_of_available_move_dragging_states_vector,
	    IFIX(Current_thread_index));
    if (def_structure_move_dragging_state_variable) {
	temp = Chain_of_available_move_dragging_states_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_move_dragging_state_variable,(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_move_dragging_state_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_move_dragging_state_g2_struct;
    }
    else
	def_structure_move_dragging_state_variable = 
		make_permanent_move_dragging_state_structure_internal();
    inline_note_allocate_cons(def_structure_move_dragging_state_variable,Nil);
    SVREF(def_structure_move_dragging_state_variable,FIX((SI_Long)1L)) = Nil;
    temp = copy_of_current_frame_serial_number_function();
    SVREF(def_structure_move_dragging_state_variable,FIX((SI_Long)2L)) = temp;
    return VALUES_1(def_structure_move_dragging_state_variable);
}

static Object Qmove_dragging;      /* move-dragging */

static Object Qwrap_up_move_after_drag;  /* wrap-up-move-after-drag */

/* ENTER-MOVE-DRAGGING-CONTEXT */
Object enter_move_dragging_context varargs_1(int, n)
{
    Object block_or_blocks_to_drag;
    Object x_offset_from_dragger, y_offset_from_dragger, specific_image_plane;
    Object mouse_up_exits_this_context_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(128,56);
    INIT_ARGS_nonrelocating();
    block_or_blocks_to_drag = REQUIRED_ARG_nonrelocating();
    x_offset_from_dragger = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : FIX((SI_Long)0L);
    y_offset_from_dragger = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : FIX((SI_Long)0L);
    specific_image_plane = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    mouse_up_exits_this_context_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : mouse_down_p();
    END_ARGS_nonrelocating();
    enter_context_in_current_workstation(3,Qmove_dragging,
	    make_move_dragging_state_1(),Nil);
    establish_next_workstation_context_continuation(Qwrap_up_move_after_drag,
	    Nil,Nil,Nil);
    return enter_dragging_context_1(6,block_or_blocks_to_drag,
	    x_offset_from_dragger,y_offset_from_dragger,
	    specific_image_plane,mouse_up_exits_this_context_qm,Nil);
}

/* RETURN-FROM-MOVE-DRAGGING-STYLE */
Object return_from_move_dragging_style(dragging_state)
    Object dragging_state;
{
    x_note_fn_call(128,57);
    return return_from_current_workstation_context(2,Qdragging,
	    copy_list_using_gensym_conses_1(ISVREF(dragging_state,
	    (SI_Long)3L)));
}

/* WRAP-UP-MOVE-AFTER-DRAG */
Object wrap_up_move_after_drag(workstation_context)
    Object workstation_context;
{
    Object blocks;

    x_note_fn_call(128,58);
    blocks = ISVREF(Current_workstation,(SI_Long)33L);
    if (EQ(blocks,Kabort))
	return abort_current_workstation_context(Qmove_dragging);
    else {
	trigger_user_icon_movement_rules_for_blocks(blocks);
	reclaim_gensym_list_1(blocks);
	return return_from_current_workstation_context(1,Qmove_dragging);
    }
}

Object The_type_description_of_transfer_dragging_state = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_transfer_dragging_states, Qchain_of_available_transfer_dragging_states);

DEFINE_VARIABLE_WITH_SYMBOL(Transfer_dragging_state_count, Qtransfer_dragging_state_count);

Object Chain_of_available_transfer_dragging_states_vector = UNBOUND;

/* TRANSFER-DRAGGING-STATE-STRUCTURE-MEMORY-USAGE */
Object transfer_dragging_state_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(128,59);
    temp = Transfer_dragging_state_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-TRANSFER-DRAGGING-STATE-COUNT */
Object outstanding_transfer_dragging_state_count()
{
    Object def_structure_transfer_dragging_state_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(128,60);
    gensymed_symbol = IFIX(Transfer_dragging_state_count);
    def_structure_transfer_dragging_state_variable = 
	    Chain_of_available_transfer_dragging_states;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_transfer_dragging_state_variable))
	goto end_loop;
    def_structure_transfer_dragging_state_variable = 
	    ISVREF(def_structure_transfer_dragging_state_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-TRANSFER-DRAGGING-STATE-1 */
Object reclaim_transfer_dragging_state_1(transfer_dragging_state)
    Object transfer_dragging_state;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(128,61);
    inline_note_reclaim_cons(transfer_dragging_state,Nil);
    structure_being_reclaimed = transfer_dragging_state;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      release_mouse_pointers(ISVREF(transfer_dragging_state,(SI_Long)1L));
      SVREF(transfer_dragging_state,FIX((SI_Long)1L)) = Nil;
      reclaim_frame_serial_number(ISVREF(transfer_dragging_state,(SI_Long)2L));
      SVREF(transfer_dragging_state,FIX((SI_Long)2L)) = Nil;
      reclaim_gensym_list_function(ISVREF(transfer_dragging_state,
	      (SI_Long)3L));
      SVREF(transfer_dragging_state,FIX((SI_Long)3L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_transfer_dragging_states_vector,
	    IFIX(Current_thread_index));
    SVREF(transfer_dragging_state,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_transfer_dragging_states_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = transfer_dragging_state;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-TRANSFER-DRAGGING-STATE */
Object reclaim_structure_for_transfer_dragging_state(transfer_dragging_state)
    Object transfer_dragging_state;
{
    x_note_fn_call(128,62);
    return reclaim_transfer_dragging_state_1(transfer_dragging_state);
}

static Object Qg2_defstruct_structure_name_transfer_dragging_state_g2_struct;  /* g2-defstruct-structure-name::transfer-dragging-state-g2-struct */

/* MAKE-PERMANENT-TRANSFER-DRAGGING-STATE-STRUCTURE-INTERNAL */
Object make_permanent_transfer_dragging_state_structure_internal()
{
    Object def_structure_transfer_dragging_state_variable;
    Object defstruct_g2_transfer_dragging_state_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(128,63);
    def_structure_transfer_dragging_state_variable = Nil;
    atomic_incff_symval(Qtransfer_dragging_state_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_transfer_dragging_state_variable = Nil;
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
	defstruct_g2_transfer_dragging_state_variable = the_array;
	SVREF(defstruct_g2_transfer_dragging_state_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_transfer_dragging_state_g2_struct;
	SVREF(defstruct_g2_transfer_dragging_state_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_transfer_dragging_state_variable,
		FIX((SI_Long)2L)) = Nil;
	def_structure_transfer_dragging_state_variable = 
		defstruct_g2_transfer_dragging_state_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_transfer_dragging_state_variable);
}

/* MAKE-TRANSFER-DRAGGING-STATE-1 */
Object make_transfer_dragging_state_1()
{
    Object def_structure_transfer_dragging_state_variable, temp, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(128,64);
    def_structure_transfer_dragging_state_variable = 
	    ISVREF(Chain_of_available_transfer_dragging_states_vector,
	    IFIX(Current_thread_index));
    if (def_structure_transfer_dragging_state_variable) {
	temp = Chain_of_available_transfer_dragging_states_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_transfer_dragging_state_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_transfer_dragging_state_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_transfer_dragging_state_g2_struct;
    }
    else
	def_structure_transfer_dragging_state_variable = 
		make_permanent_transfer_dragging_state_structure_internal();
    inline_note_allocate_cons(def_structure_transfer_dragging_state_variable,
	    Nil);
    SVREF(def_structure_transfer_dragging_state_variable,FIX((SI_Long)1L)) 
	    = Nil;
    temp = copy_of_current_frame_serial_number_function();
    SVREF(def_structure_transfer_dragging_state_variable,FIX((SI_Long)2L)) 
	    = temp;
    SVREF(def_structure_transfer_dragging_state_variable,FIX((SI_Long)3L)) 
	    = Nil;
    SVREF(def_structure_transfer_dragging_state_variable,FIX((SI_Long)4L)) 
	    = Nil;
    SVREF(def_structure_transfer_dragging_state_variable,FIX((SI_Long)5L)) 
	    = Nil;
    return VALUES_1(def_structure_transfer_dragging_state_variable);
}

/* CLEAN-UP-WORKSTATION-CONTEXT-FOR-TRANSFER-DRAGGING-STATE */
Object clean_up_workstation_context_for_transfer_dragging_state(transfer_dragging_state)
    Object transfer_dragging_state;
{
    Object gensymed_symbol, blocks, external_connections, gensymed_symbol_1;

    x_note_fn_call(128,65);
    gensymed_symbol = ISVREF(transfer_dragging_state,(SI_Long)3L);
    blocks = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    external_connections = CAR(gensymed_symbol);
    if (ISVREF(transfer_dragging_state,(SI_Long)4L)) {
	delete_blocks_from_list_in_limbo(blocks,
		ISVREF(transfer_dragging_state,(SI_Long)4L));
	reclaim_frame_serial_number(ISVREF(transfer_dragging_state,
		(SI_Long)4L));
    }
    reclaim_gensym_list_1(external_connections);
    reclaim_gensym_list_1(blocks);
    gensymed_symbol = 
	    ISVREF(ISVREF(ISVREF(The_type_description_of_transfer_dragging_state,
	    (SI_Long)9L),(SI_Long)0L),(SI_Long)1L);
    gensymed_symbol_1 = transfer_dragging_state;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

static Object Qtransfer_dragging;  /* transfer-dragging */

static Object Qwrap_up_transfer_after_drag;  /* wrap-up-transfer-after-drag */

/* ENTER-TRANSFER-DRAGGING-CONTEXT */
Object enter_transfer_dragging_context varargs_1(int, n)
{
    Object block_or_blocks_to_drag;
    Object x_offset_from_dragger, y_offset_from_dragger;
    Object specific_image_plane_qm, mouse_up_exits_this_context_qm;
    Object select_transfered_objects_when_done, state_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(128,66);
    INIT_ARGS_nonrelocating();
    block_or_blocks_to_drag = REQUIRED_ARG_nonrelocating();
    x_offset_from_dragger = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : FIX((SI_Long)0L);
    y_offset_from_dragger = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : FIX((SI_Long)0L);
    specific_image_plane_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    mouse_up_exits_this_context_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : mouse_down_p();
    select_transfered_objects_when_done = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    state_1 = make_transfer_dragging_state_1();
    SVREF(state_1,FIX((SI_Long)5L)) = select_transfered_objects_when_done;
    enter_context_in_current_workstation(3,Qtransfer_dragging,state_1,Nil);
    if (ATOM(block_or_blocks_to_drag) ?  !TRUEP(block_transferable_p(1,
	    block_or_blocks_to_drag)) :  
	    !TRUEP(blocks_transferable_p(block_or_blocks_to_drag)))
	return abort_current_workstation_context(Qtransfer_dragging);
    else {
	establish_next_workstation_context_continuation(Qwrap_up_transfer_after_drag,
		Nil,Nil,Nil);
	return enter_dragging_context_1(6,block_or_blocks_to_drag,
		x_offset_from_dragger,y_offset_from_dragger,
		specific_image_plane_qm,mouse_up_exits_this_context_qm,T);
    }
}

/* RETURN-FROM-TRANSFER-DRAGGING-STYLE */
Object return_from_transfer_dragging_style(dragging_state)
    Object dragging_state;
{
    Object image_plane, current_frame_transform_qm, current_image_x_scale;
    Object current_image_y_scale, current_x_origin_of_drawing;
    Object current_y_origin_of_drawing, x_in_window, y_in_window, temp, block;
    Object scale, value, new_x_in_workspace, new_y_in_workspace, u_1, step_qm;
    Object min_qm, max_qm, ur, gensymed_symbol_2, gensymed_symbol_3;
    Object car_new_value, gensymed_symbol_4;
    SI_Long gensymed_symbol, temp_1, gensymed_symbol_1, car_new_value_1;
    Declare_special(5);

    x_note_fn_call(128,67);
    image_plane = ISVREF(dragging_state,(SI_Long)5L);
    current_frame_transform_qm = Nil;
    current_image_x_scale = ISVREF(image_plane,(SI_Long)11L);
    current_image_y_scale = ISVREF(image_plane,(SI_Long)12L);
    current_x_origin_of_drawing = ISVREF(image_plane,(SI_Long)13L);
    current_y_origin_of_drawing = ISVREF(image_plane,(SI_Long)14L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
	    4);
      PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
	      3);
	PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
		2);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
		  1);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
		    0);
	      x_in_window = Explicit_dragger_x_in_window_qm;
	      if (x_in_window);
	      else
		  x_in_window = ISVREF(Current_workstation,(SI_Long)5L);
	      y_in_window = Explicit_dragger_y_in_window_qm;
	      if (y_in_window);
	      else
		  y_in_window = ISVREF(Current_workstation,(SI_Long)6L);
	      temp = ISVREF(dragging_state,(SI_Long)3L);
	      block = FIRST(temp);
	      scale = Current_image_x_scale;
	      value = FIXNUM_MINUS(x_in_window,Current_x_origin_of_drawing);
	      if (IFIX(scale) == (SI_Long)4096L)
		  gensymed_symbol = IFIX(value);
	      else if ( !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		      value) && FIXNUM_LT(value,
		      Isqrt_of_most_positive_fixnum)))
		  gensymed_symbol = IFIX(inverse_scalef_function(scale,value));
	      else if (IFIX(value) >= (SI_Long)0L) {
		  temp_1 = ((IFIX(value) << (SI_Long)12L) + (IFIX(scale) 
			  >>  -  - (SI_Long)1L)) / IFIX(scale);
		  gensymed_symbol = temp_1;
	      }
	      else {
		  temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << (SI_Long)12L) + 
			  (IFIX(scale) >>  -  - (SI_Long)1L)) / IFIX(scale);
		  temp_1 = IFIX(FIXNUM_NEGATE(FIX(temp_1)));
		  gensymed_symbol = temp_1;
	      }
	      gensymed_symbol_1 = IFIX(ISVREF(dragging_state,(SI_Long)8L));
	      new_x_in_workspace = FIX(gensymed_symbol - gensymed_symbol_1);
	      scale = Current_image_y_scale;
	      value = FIXNUM_MINUS(y_in_window,Current_y_origin_of_drawing);
	      if (IFIX(scale) == (SI_Long)4096L)
		  gensymed_symbol = IFIX(value);
	      else if ( !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		      value) && FIXNUM_LT(value,
		      Isqrt_of_most_positive_fixnum)))
		  gensymed_symbol = IFIX(inverse_scalef_function(scale,value));
	      else if (IFIX(value) >= (SI_Long)0L) {
		  temp_1 = ((IFIX(value) << (SI_Long)12L) + (IFIX(scale) 
			  >>  -  - (SI_Long)1L)) / IFIX(scale);
		  gensymed_symbol = temp_1;
	      }
	      else {
		  temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << (SI_Long)12L) + 
			  (IFIX(scale) >>  -  - (SI_Long)1L)) / IFIX(scale);
		  temp_1 = IFIX(FIXNUM_NEGATE(FIX(temp_1)));
		  gensymed_symbol = temp_1;
	      }
	      gensymed_symbol_1 = IFIX(ISVREF(dragging_state,(SI_Long)9L));
	      new_y_in_workspace = FIX(gensymed_symbol - gensymed_symbol_1);
	      if ( !TRUEP(ignore_snap_grid_in_transfer_operations_p())) {
		  u_1 = new_x_in_workspace;
		  step_qm = ISVREF(dragging_state,(SI_Long)22L);
		  min_qm = ISVREF(dragging_state,(SI_Long)13L);
		  max_qm = ISVREF(dragging_state,(SI_Long)15L);
		  ur = u_1;
		  if (step_qm)
		      ur = FIXNUM_TIMES(step_qm,l_round(u_1,step_qm));
		  if (min_qm)
		      ur = FIXNUM_MAX(ur,min_qm);
		  if (max_qm)
		      ur = FIXNUM_MIN(ur,max_qm);
		  new_x_in_workspace = ur;
		  u_1 = new_y_in_workspace;
		  step_qm = ISVREF(dragging_state,(SI_Long)23L);
		  min_qm = ISVREF(dragging_state,(SI_Long)14L);
		  max_qm = ISVREF(dragging_state,(SI_Long)16L);
		  ur = u_1;
		  if (step_qm)
		      ur = FIXNUM_TIMES(step_qm,l_round(u_1,step_qm));
		  if (min_qm)
		      ur = FIXNUM_MAX(ur,min_qm);
		  if (max_qm)
		      ur = FIXNUM_MIN(ur,max_qm);
		  new_y_in_workspace = ur;
	      }
	      gensymed_symbol_2 = make_gensym_list_1(FIX((SI_Long)5L));
	      gensymed_symbol_3 = gensymed_symbol_2;
	      car_new_value = 
		      copy_list_using_gensym_conses_1(ISVREF(dragging_state,
		      (SI_Long)3L));
	      M_CAR(gensymed_symbol_3) = car_new_value;
	      gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	      car_new_value = 
		      copy_list_using_gensym_conses_1(ISVREF(dragging_state,
		      (SI_Long)6L));
	      M_CAR(gensymed_symbol_3) = car_new_value;
	      gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	      car_new_value = ISVREF(dragging_state,(SI_Long)7L);
	      M_CAR(gensymed_symbol_3) = car_new_value;
	      gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	      gensymed_symbol = IFIX(new_x_in_workspace);
	      gensymed_symbol_4 = ISVREF(block,(SI_Long)14L);
	      gensymed_symbol_4 = gensymed_symbol_4 ? 
		      ISVREF(gensymed_symbol_4,(SI_Long)0L) : FIX((SI_Long)0L);
	      gensymed_symbol_1 = IFIX(gensymed_symbol_4);
	      car_new_value_1 = gensymed_symbol - gensymed_symbol_1;
	      M_CAR(gensymed_symbol_3) = FIX(car_new_value_1);
	      gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	      gensymed_symbol = IFIX(new_y_in_workspace);
	      gensymed_symbol_4 = ISVREF(block,(SI_Long)14L);
	      gensymed_symbol_4 = gensymed_symbol_4 ? 
		      ISVREF(gensymed_symbol_4,(SI_Long)1L) : FIX((SI_Long)0L);
	      gensymed_symbol_1 = IFIX(gensymed_symbol_4);
	      car_new_value_1 = gensymed_symbol - gensymed_symbol_1;
	      M_CAR(gensymed_symbol_3) = FIX(car_new_value_1);
	      temp = gensymed_symbol_2;
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return return_from_current_workstation_context(2,Qdragging,temp);
}

/* WRAP-UP-TRANSFER-AFTER-DRAG */
Object wrap_up_transfer_after_drag(workstation_context)
    Object workstation_context;
{
    x_note_fn_call(128,68);
    return wrap_up_transfer_after_drag_1(workstation_context,
	    Qtransfer_dragging);
}

static Object string_constant;     /* "~a" */

static Object Qtransfer;           /* transfer */

static Object Qedit;               /* edit */

/* WRAP-UP-TRANSFER-AFTER-DRAG-1 */
Object wrap_up_transfer_after_drag_1(workstation_context,
	    transfer_dragging_mode)
    Object workstation_context, transfer_dragging_mode;
{
    Object transfer_return_information, gensymed_symbol, blocks;
    Object external_connections, workspace, delta_x_in_workspace;
    Object delta_y_in_workspace, transfer_dragging_state;
    Object frame_serial_number_setf_arg, old, new_1, svref_new_value;
    Object string_explaining_problem_qm, block, ab_loop_list_;
    Object operation_around_record_of_items_made_incomplete;
    Object recording_items_made_incomplete_qm;
    Object items_made_incomplete_were_recorded_qm, temp_1;
    char temp;
    Declare_special(3);
    Object result;

    x_note_fn_call(128,69);
    transfer_return_information = ISVREF(Current_workstation,(SI_Long)33L);
    if (EQ(transfer_return_information,Kabort))
	return abort_current_workstation_context(transfer_dragging_mode);
    else {
	gensymed_symbol = transfer_return_information;
	blocks = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	external_connections = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	workspace = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	delta_x_in_workspace = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	delta_y_in_workspace = CAR(gensymed_symbol);
	transfer_dragging_state = 
		Specific_structure_for_current_workstation_context;
	frame_serial_number_setf_arg = Current_frame_serial_number;
	old = ISVREF(transfer_dragging_state,(SI_Long)4L);
	new_1 = frame_serial_number_setf_arg;
	svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && 
		(FIXNUMP(new_1) ||  !TRUEP(new_1)) ? new_1 : 
		frame_serial_number_setf_helper_1(old,new_1);
	SVREF(transfer_dragging_state,FIX((SI_Long)4L)) = svref_new_value;
	svref_new_value = 
		copy_tree_using_gensym_conses_1(transfer_return_information);
	SVREF(transfer_dragging_state,FIX((SI_Long)3L)) = svref_new_value;
	string_explaining_problem_qm = 
		check_completion_of_transfer_after_drag(blocks,workspace);
	if (string_explaining_problem_qm) {
	    beep_at_user();
	    notify_user(2,string_constant,string_explaining_problem_qm);
	    reclaim_text_string(string_explaining_problem_qm);
	    return abort_current_workstation_context(transfer_dragging_mode);
	}
	else {
	    block = Nil;
	    ab_loop_list_ = blocks;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    block = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    temp = (SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
		    (SI_Long)262144L);
	    if (temp);
	    else
		temp = (SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)4L)) & 
			(SI_Long)1L);
	    if (temp);
	    else {
		gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
		gensymed_symbol = gensymed_symbol ? 
			ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
		temp = TRUEP(gensymed_symbol);
	    }
	    if ( !temp)
		recursive_schedule_task_to_invoke_creation_rules(block);
	    goto next_loop;
	  end_loop:;
	    operation_around_record_of_items_made_incomplete = Qtransfer;
	    PUSH_SPECIAL_WITH_SYMBOL(Operation_around_record_of_items_made_incomplete,Qoperation_around_record_of_items_made_incomplete,operation_around_record_of_items_made_incomplete,
		    2);
	      recording_items_made_incomplete_qm = 
		      EQ(Operation_around_record_of_items_made_incomplete,
		      Qedit) ? ( !TRUEP(ISVREF(Current_edit_state,
		      (SI_Long)57L)) ? T : Nil) : T;
	      PUSH_SPECIAL_WITH_SYMBOL(Recording_items_made_incomplete_qm,Qrecording_items_made_incomplete_qm,recording_items_made_incomplete_qm,
		      1);
		items_made_incomplete_were_recorded_qm = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Items_made_incomplete_were_recorded_qm,Qitems_made_incomplete_were_recorded_qm,items_made_incomplete_were_recorded_qm,
			0);
		  reclaim_items_made_incomplete_list();
		  transfer_grouped_blocks_with_their_external_connections(blocks,
			  external_connections,workspace,
			  delta_x_in_workspace,delta_y_in_workspace,Nil);
		  if (ISVREF(transfer_dragging_state,(SI_Long)5L) && 
			  selection_enabled_p(1,Current_workstation_window))
		      select_objects_after_transfer(workspace,blocks,
			      external_connections);
		  trigger_user_icon_movement_rules_for_blocks(blocks);
		  temp_1 = Items_made_incomplete_were_recorded_qm ? 
			  offer_to_recompile_after_transfer() : 
			  return_from_current_workstation_context(2,
			  transfer_dragging_mode,Qt);
		  reclaim_items_made_incomplete_list();
		  result = VALUES_1(temp_1);
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    return result;
	}
    }
}

static Object string_constant_1;   /* "Recompile the KB?  (~A)" */

static Object Qlaunch_compile_to_bring_kb_up_to_date_and_return_from_transfer_dragging;  /* launch-compile-to-bring-kb-up-to-date-and-return-from-transfer-dragging */

static Object Qreturn_from_current_workstation_context;  /* return-from-current-workstation-context */

static Object Qno_recompile;       /* no-recompile */

/* OFFER-TO-RECOMPILE-AFTER-TRANSFER */
Object offer_to_recompile_after_transfer()
{
    Object inner_text_string, temp;

    x_note_fn_call(128,70);
    inner_text_string = make_description_of_barrier_to_destabilization();
    temp = tformat_text_string(2,string_constant_1,inner_text_string);
    return enter_dialog(7,temp,Nil,Nil,
	    Qlaunch_compile_to_bring_kb_up_to_date_and_return_from_transfer_dragging,
	    slot_value_cons_1(inner_text_string,Nil),
	    Qreturn_from_current_workstation_context,
	    slot_value_list_2(Qtransfer_dragging,Qno_recompile));
}

static Object Qrecompile;          /* recompile */

/* LAUNCH-COMPILE-TO-BRING-KB-UP-TO-DATE-AND-RETURN-FROM-TRANSFER-DRAGGING */
Object launch_compile_to_bring_kb_up_to_date_and_return_from_transfer_dragging(additional_comment_string_qm)
    Object additional_comment_string_qm;
{
    x_note_fn_call(128,71);
    launch_compile_to_bring_kb_up_to_date(1,additional_comment_string_qm);
    return return_from_current_workstation_context(2,Qtransfer_dragging,
	    Qrecompile);
}

static Object string_constant_2;   /* "Cannot transfer items to non-KB workspaces!" */

static Object string_constant_3;   /* "Cannot place items on their subordinate workspace!" */

static Object string_constant_4;   /* "Cannot transfer items to proprietary workspaces!" */

static Object string_constant_5;   /* "Cannot transfer permanent items to transient workspaces!" */

static Object string_constant_6;   /* "Cannot transfer ~NF, because ~A" */

static Object string_constant_7;   /* "Cannot transfer to ~NF, because ~A" */

/* CHECK-COMPLETION-OF-TRANSFER-AFTER-DRAG */
Object check_completion_of_transfer_after_drag(blocks,workspace)
    Object blocks, workspace;
{
    Object uneditable_reason, uneditable_item, block, ab_loop_list_, reason;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(128,72);
    uneditable_reason = Nil;
    uneditable_item = Nil;
    block = Nil;
    ab_loop_list_ = blocks;
    reason = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    block = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    sub_class_bit_vector = ISVREF(ISVREF(workspace,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Non_kb_workspace_class_description,(SI_Long)18L));
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
	reason = string_constant_2;
    else if (ancestor_p(block,workspace))
	reason = string_constant_3;
    else if (in_order_p(workspace) &&  !EQ(get_workspace_if_any(block),
	    workspace))
	reason = string_constant_4;
    else if ((SI_Long)0L != (IFIX(ISVREF(workspace,(SI_Long)5L)) & 
	    (SI_Long)262144L) && (SI_Long)0L != (IFIX(ISVREF(block,
	    (SI_Long)4L)) & (SI_Long)1L))
	reason = string_constant_5;
    else {
	uneditable_reason = 
		reason_permanent_items_module_is_not_editable(1,block);
	if (uneditable_reason) {
	    uneditable_item = block;
	    reason = string_constant_6;
	}
	else {
	    uneditable_reason = 
		    reason_permanent_items_module_is_not_editable(1,workspace);
	    if (uneditable_reason) {
		uneditable_item = workspace;
		reason = string_constant_7;
	    }
	    else
		reason = Qnil;
	}
    }
    if (reason)
	return tformat_text_string(3,reason,uneditable_item,uneditable_reason);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* REENTER-EDITOR-IF-NOT-HAND-PLACED */
Object reenter_editor_if_not_hand_placed(workstation_context)
    Object workstation_context;
{
    x_note_fn_call(128,73);
    return VALUES_1(Nil);
}

/* DRAG-OUTLINE-IF-APPROPRIATE */
Object drag_outline_if_appropriate(dragging_state,
	    just_erase_if_currently_drawn_qm)
    Object dragging_state, just_erase_if_currently_drawn_qm;
{
    Object current_x_in_window_of_mouse_qm, current_y_in_window_of_mouse_qm;
    Object temp;
    char temp_1;

    x_note_fn_call(128,74);
    current_x_in_window_of_mouse_qm = Explicit_dragger_x_in_window_qm;
    if (current_x_in_window_of_mouse_qm);
    else
	current_x_in_window_of_mouse_qm = ISVREF(Current_workstation,
		(SI_Long)5L);
    current_y_in_window_of_mouse_qm = Explicit_dragger_y_in_window_qm;
    if (current_y_in_window_of_mouse_qm);
    else
	current_y_in_window_of_mouse_qm = ISVREF(Current_workstation,
		(SI_Long)6L);
    temp = ISVREF(dragging_state,(SI_Long)3L);
    temp = CAR(temp);
    if (EQ(temp,Qimage_plane)) {
	if (just_erase_if_currently_drawn_qm)
	    return erase_outline_of_image_plane_being_dragged(1,
		    dragging_state);
	else {
	    temp = ISVREF(dragging_state,(SI_Long)10L);
	    temp_1 =  !EQL(current_x_in_window_of_mouse_qm,temp);
	    if (temp_1);
	    else {
		temp = ISVREF(dragging_state,(SI_Long)11L);
		temp_1 =  !EQL(current_y_in_window_of_mouse_qm,temp);
	    }
	    if (temp_1)
		return move_outline_of_image_plane_being_dragged(dragging_state,
			current_x_in_window_of_mouse_qm,
			current_y_in_window_of_mouse_qm);
	    else
		return VALUES_1(Qnil);
	}
    }
    else if (ISVREF(dragging_state,(SI_Long)3L))
	return move_or_transfer_blocks_being_dragged_if_appropriate(dragging_state,
		current_x_in_window_of_mouse_qm,
		current_y_in_window_of_mouse_qm,
		just_erase_if_currently_drawn_qm);
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_image_plane_qm, Qcurrent_image_plane_qm);

/* MOVE-OR-TRANSFER-BLOCKS-BEING-DRAGGED-IF-APPROPRIATE */
Object move_or_transfer_blocks_being_dragged_if_appropriate(dragging_state,
	    dragger_x,dragger_y,just_erase_if_currently_drawn_qm)
    Object dragging_state, dragger_x, dragger_y;
    Object just_erase_if_currently_drawn_qm;
{
    Object objects_being_dragged, image_plane_qm, old_image_plane_qm;
    Object gensymed_symbol, current_image_plane_qm, new_image_plane_qm, temp_1;
    Object dragger_x_star, dragger_y_star, current_frame_transform_qm;
    Object current_image_x_scale, current_image_y_scale;
    Object current_x_origin_of_drawing, current_y_origin_of_drawing, scale;
    Object scale_1, value, step_qm, min_qm, max_qm, ur, dragger_x_in_workspace;
    Object dragger_y_in_workspace, workspace, first_block, x_1, u_2, y_1;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, temp_2, gensymed_symbol_3, x;
    SI_Long u_1, value_1, unshifted_result, y, delta_x_in_workspace;
    SI_Long delta_y_in_workspace;
    char same_image_plane_qm, temp;
    Declare_special(6);
    Object result;

    x_note_fn_call(128,75);
    objects_being_dragged = ISVREF(dragging_state,(SI_Long)3L);
    image_plane_qm = ISVREF(dragging_state,(SI_Long)5L);
    old_image_plane_qm = image_plane_qm && ISVREF(image_plane_qm,
	    (SI_Long)5L) ? image_plane_qm : Nil;
    if (EQ(ISVREF(dragging_state,(SI_Long)21L),Qtransfer_dragging_style)) {
	result = decode_window_position(ISVREF(dragging_state,(SI_Long)4L),
		dragger_x,dragger_y);
	gensymed_symbol = NTH_VALUE((SI_Long)1L, result);
	current_image_plane_qm = gensymed_symbol;
	PUSH_SPECIAL_WITH_SYMBOL(Current_image_plane_qm,Qcurrent_image_plane_qm,current_image_plane_qm,
		5);
	  new_image_plane_qm =  !TRUEP(just_erase_if_currently_drawn_qm) ? 
		  Current_image_plane_qm : Nil;
	  same_image_plane_qm = EQ(old_image_plane_qm,new_image_plane_qm);
	  temp =  !same_image_plane_qm;
	  if (temp);
	  else if (new_image_plane_qm) {
	      temp_1 = ISVREF(dragging_state,(SI_Long)10L);
	      temp =  !EQL(dragger_x,temp_1);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp);
	  else if (new_image_plane_qm) {
	      temp_1 = ISVREF(dragging_state,(SI_Long)11L);
	      temp =  !EQL(dragger_y,temp_1);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp);
	  else
	      temp = just_erase_if_currently_drawn_qm ? 
		      TRUEP(old_image_plane_qm) : TRUEP(Nil);
	  if (temp) {
	      dragger_x_star = dragger_x;
	      dragger_y_star = dragger_y;
	      if ( !same_image_plane_qm)
		  compute_snap_grid_for_transfer(2,dragging_state,
			  Current_image_plane_qm ? 
			  ISVREF(Current_image_plane_qm,(SI_Long)5L) : Nil);
	      if (Current_image_plane_qm) {
		  current_frame_transform_qm = Nil;
		  current_image_x_scale = ISVREF(Current_image_plane_qm,
			  (SI_Long)11L);
		  current_image_y_scale = ISVREF(Current_image_plane_qm,
			  (SI_Long)12L);
		  current_x_origin_of_drawing = 
			  ISVREF(Current_image_plane_qm,(SI_Long)13L);
		  current_y_origin_of_drawing = 
			  ISVREF(Current_image_plane_qm,(SI_Long)14L);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
			  4);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
			    3);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
			      2);
			PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
				1);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
				  0);
			    gensymed_symbol_1 = 
				    IFIX(Current_x_origin_of_drawing);
			    scale = Current_image_x_scale;
			    scale_1 = Current_image_x_scale;
			    value = FIXNUM_MINUS(dragger_x,
				    Current_x_origin_of_drawing);
			    if (IFIX(scale_1) == (SI_Long)4096L)
				gensymed_symbol_2 = IFIX(value);
			    else if ( 
				    !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				    value) && FIXNUM_LT(value,
				    Isqrt_of_most_positive_fixnum)))
				gensymed_symbol_2 = 
					IFIX(inverse_scalef_function(scale_1,
					value));
			    else if (IFIX(value) >= (SI_Long)0L) {
				temp_2 = ((IFIX(value) << (SI_Long)12L) + 
					(IFIX(scale_1) >>  -  - 
					(SI_Long)1L)) / IFIX(scale_1);
				gensymed_symbol_2 = temp_2;
			    }
			    else {
				temp_2 = ((IFIX(FIXNUM_NEGATE(value)) << 
					(SI_Long)12L) + (IFIX(scale_1) >>  
					-  - (SI_Long)1L)) / IFIX(scale_1);
				temp_2 = IFIX(FIXNUM_NEGATE(FIX(temp_2)));
				gensymed_symbol_2 = temp_2;
			    }
			    gensymed_symbol_3 = IFIX(ISVREF(dragging_state,
				    (SI_Long)8L));
			    x = gensymed_symbol_2 - gensymed_symbol_3;
			    u_1 = x;
			    step_qm = ISVREF(dragging_state,(SI_Long)22L);
			    min_qm = ISVREF(dragging_state,(SI_Long)13L);
			    max_qm = ISVREF(dragging_state,(SI_Long)15L);
			    ur = FIX(u_1);
			    if (step_qm)
				ur = FIXNUM_TIMES(step_qm,l_round(FIX(u_1),
					step_qm));
			    if (min_qm)
				ur = FIXNUM_MAX(ur,min_qm);
			    if (max_qm)
				ur = FIXNUM_MIN(ur,max_qm);
			    gensymed_symbol_2 = IFIX(ur);
			    gensymed_symbol_3 = IFIX(ISVREF(dragging_state,
				    (SI_Long)8L));
			    value_1 = gensymed_symbol_2 + gensymed_symbol_3;
			    if (IFIX(scale) == (SI_Long)4096L)
				gensymed_symbol_2 = value_1;
			    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				    scale) && FIXNUM_LT(scale,
				    Isqrt_of_most_positive_fixnum) && 
				    IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
				    < value_1 && value_1 < 
				    IFIX(Isqrt_of_most_positive_fixnum)) {
				unshifted_result = IFIX(scale) * value_1 + 
					(SI_Long)2048L;
				gensymed_symbol_2 = unshifted_result >>  - 
					 - (SI_Long)12L;
			    }
			    else
				gensymed_symbol_2 = 
					IFIX(scalef_function(scale,
					FIX(value_1)));
			    dragger_x_star = FIX(gensymed_symbol_1 + 
				    gensymed_symbol_2);
			    gensymed_symbol_1 = 
				    IFIX(Current_y_origin_of_drawing);
			    scale = Current_image_y_scale;
			    scale_1 = Current_image_y_scale;
			    value = FIXNUM_MINUS(dragger_y,
				    Current_y_origin_of_drawing);
			    if (IFIX(scale_1) == (SI_Long)4096L)
				gensymed_symbol_2 = IFIX(value);
			    else if ( 
				    !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				    value) && FIXNUM_LT(value,
				    Isqrt_of_most_positive_fixnum)))
				gensymed_symbol_2 = 
					IFIX(inverse_scalef_function(scale_1,
					value));
			    else if (IFIX(value) >= (SI_Long)0L) {
				temp_2 = ((IFIX(value) << (SI_Long)12L) + 
					(IFIX(scale_1) >>  -  - 
					(SI_Long)1L)) / IFIX(scale_1);
				gensymed_symbol_2 = temp_2;
			    }
			    else {
				temp_2 = ((IFIX(FIXNUM_NEGATE(value)) << 
					(SI_Long)12L) + (IFIX(scale_1) >>  
					-  - (SI_Long)1L)) / IFIX(scale_1);
				temp_2 = IFIX(FIXNUM_NEGATE(FIX(temp_2)));
				gensymed_symbol_2 = temp_2;
			    }
			    gensymed_symbol_3 = IFIX(ISVREF(dragging_state,
				    (SI_Long)9L));
			    y = gensymed_symbol_2 - gensymed_symbol_3;
			    u_1 = y;
			    step_qm = ISVREF(dragging_state,(SI_Long)23L);
			    min_qm = ISVREF(dragging_state,(SI_Long)14L);
			    max_qm = ISVREF(dragging_state,(SI_Long)16L);
			    ur = FIX(u_1);
			    if (step_qm)
				ur = FIXNUM_TIMES(step_qm,l_round(FIX(u_1),
					step_qm));
			    if (min_qm)
				ur = FIXNUM_MAX(ur,min_qm);
			    if (max_qm)
				ur = FIXNUM_MIN(ur,max_qm);
			    gensymed_symbol_2 = IFIX(ur);
			    gensymed_symbol_3 = IFIX(ISVREF(dragging_state,
				    (SI_Long)9L));
			    value_1 = gensymed_symbol_2 + gensymed_symbol_3;
			    if (IFIX(scale) == (SI_Long)4096L)
				gensymed_symbol_2 = value_1;
			    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				    scale) && FIXNUM_LT(scale,
				    Isqrt_of_most_positive_fixnum) && 
				    IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
				    < value_1 && value_1 < 
				    IFIX(Isqrt_of_most_positive_fixnum)) {
				unshifted_result = IFIX(scale) * value_1 + 
					(SI_Long)2048L;
				gensymed_symbol_2 = unshifted_result >>  - 
					 - (SI_Long)12L;
			    }
			    else
				gensymed_symbol_2 = 
					IFIX(scalef_function(scale,
					FIX(value_1)));
			    dragger_y_star = FIX(gensymed_symbol_1 + 
				    gensymed_symbol_2);
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
	      }
	      if (just_erase_if_currently_drawn_qm) {
		  if (old_image_plane_qm)
		      shift_and_draw_blocks_being_transferred(dragging_state,
			      old_image_plane_qm,dragger_x_star,
			      dragger_y_star,T,Nil);
	      }
	      else if (same_image_plane_qm) {
		  if (old_image_plane_qm)
		      shift_and_draw_blocks_being_transferred(dragging_state,
			      old_image_plane_qm,dragger_x_star,
			      dragger_y_star,T,T);
	      }
	      else {
		  if (old_image_plane_qm)
		      shift_and_draw_blocks_being_transferred(dragging_state,
			      old_image_plane_qm,dragger_x_star,
			      dragger_y_star,T,Nil);
		  if (new_image_plane_qm)
		      shift_and_draw_blocks_being_transferred(dragging_state,
			      new_image_plane_qm,dragger_x_star,
			      dragger_y_star,Nil,T);
	      }
	      SVREF(dragging_state,FIX((SI_Long)5L)) = new_image_plane_qm;
	      SVREF(dragging_state,FIX((SI_Long)10L)) = dragger_x;
	      result = VALUES_1(SVREF(dragging_state,FIX((SI_Long)11L)) = 
		      dragger_y);
	  }
	  else
	      result = VALUES_1(Nil);
	POP_SPECIAL();
	return result;
    }
    else if ( !TRUEP(old_image_plane_qm))
	return VALUES_1(Nil);
    else {
	temp_1 = ISVREF(dragging_state,(SI_Long)10L);
	temp =  !EQL(dragger_x,temp_1);
	if (temp);
	else {
	    temp_1 = ISVREF(dragging_state,(SI_Long)11L);
	    temp =  !EQL(dragger_y,temp_1);
	}
	if (temp);
	else
	    temp = TRUEP(just_erase_if_currently_drawn_qm);
	if (temp) {
	    dragger_x_in_workspace = Nil;
	    dragger_y_in_workspace = Nil;
	    workspace = ISVREF(old_image_plane_qm,(SI_Long)5L);
	    first_block = CAR(objects_being_dragged);
	    current_frame_transform_qm = Nil;
	    current_image_x_scale = ISVREF(old_image_plane_qm,(SI_Long)11L);
	    current_image_y_scale = ISVREF(old_image_plane_qm,(SI_Long)12L);
	    current_x_origin_of_drawing = ISVREF(old_image_plane_qm,
		    (SI_Long)13L);
	    current_y_origin_of_drawing = ISVREF(old_image_plane_qm,
		    (SI_Long)14L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
		    4);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
		      3);
		PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
			2);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
			  1);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
			    0);
		      scale = Current_image_x_scale;
		      value = FIXNUM_MINUS(dragger_x,
			      Current_x_origin_of_drawing);
		      if (IFIX(scale) == (SI_Long)4096L)
			  dragger_x_in_workspace = value;
		      else if ( 
			      !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			      value) && FIXNUM_LT(value,
			      Isqrt_of_most_positive_fixnum)))
			  dragger_x_in_workspace = 
				  inverse_scalef_function(scale,value);
		      else if (IFIX(value) >= (SI_Long)0L) {
			  temp_1 = FIX(((IFIX(value) << (SI_Long)12L) + 
				  (IFIX(scale) >>  -  - (SI_Long)1L)) / 
				  IFIX(scale));
			  dragger_x_in_workspace = temp_1;
		      }
		      else {
			  temp_2 = ((IFIX(FIXNUM_NEGATE(value)) << 
				  (SI_Long)12L) + (IFIX(scale) >>  -  - 
				  (SI_Long)1L)) / IFIX(scale);
			  temp_1 = FIXNUM_NEGATE(FIX(temp_2));
			  dragger_x_in_workspace = temp_1;
		      }
		      scale = Current_image_y_scale;
		      value = FIXNUM_MINUS(dragger_y,
			      Current_y_origin_of_drawing);
		      if (IFIX(scale) == (SI_Long)4096L)
			  dragger_y_in_workspace = value;
		      else if ( 
			      !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			      value) && FIXNUM_LT(value,
			      Isqrt_of_most_positive_fixnum)))
			  dragger_y_in_workspace = 
				  inverse_scalef_function(scale,value);
		      else if (IFIX(value) >= (SI_Long)0L) {
			  temp_1 = FIX(((IFIX(value) << (SI_Long)12L) + 
				  (IFIX(scale) >>  -  - (SI_Long)1L)) / 
				  IFIX(scale));
			  dragger_y_in_workspace = temp_1;
		      }
		      else {
			  temp_2 = ((IFIX(FIXNUM_NEGATE(value)) << 
				  (SI_Long)12L) + (IFIX(scale) >>  -  - 
				  (SI_Long)1L)) / IFIX(scale);
			  temp_1 = FIXNUM_NEGATE(FIX(temp_2));
			  dragger_y_in_workspace = temp_1;
		      }
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    x_1 = FIXNUM_MINUS(dragger_x_in_workspace,
		    ISVREF(dragging_state,(SI_Long)8L));
	    u_2 = x_1;
	    step_qm = ISVREF(dragging_state,(SI_Long)22L);
	    min_qm = ISVREF(dragging_state,(SI_Long)13L);
	    max_qm = ISVREF(dragging_state,(SI_Long)15L);
	    ur = u_2;
	    if (step_qm)
		ur = FIXNUM_TIMES(step_qm,l_round(u_2,step_qm));
	    if (min_qm)
		ur = FIXNUM_MAX(ur,min_qm);
	    if (max_qm)
		ur = FIXNUM_MIN(ur,max_qm);
	    gensymed_symbol_1 = IFIX(ur);
	    gensymed_symbol = ISVREF(first_block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    delta_x_in_workspace = gensymed_symbol_1 - gensymed_symbol_2;
	    y_1 = FIXNUM_MINUS(dragger_y_in_workspace,
		    ISVREF(dragging_state,(SI_Long)9L));
	    u_2 = y_1;
	    step_qm = ISVREF(dragging_state,(SI_Long)23L);
	    min_qm = ISVREF(dragging_state,(SI_Long)14L);
	    max_qm = ISVREF(dragging_state,(SI_Long)16L);
	    ur = u_2;
	    if (step_qm)
		ur = FIXNUM_TIMES(step_qm,l_round(u_2,step_qm));
	    if (min_qm)
		ur = FIXNUM_MAX(ur,min_qm);
	    if (max_qm)
		ur = FIXNUM_MIN(ur,max_qm);
	    gensymed_symbol_1 = IFIX(ur);
	    gensymed_symbol = ISVREF(first_block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    delta_y_in_workspace = gensymed_symbol_1 - gensymed_symbol_2;
	    shift_blocks_with_their_external_connections(9,
		    objects_being_dragged,ISVREF(dragging_state,
		    (SI_Long)6L),just_erase_if_currently_drawn_qm,
		    workspace,FIX(delta_x_in_workspace),
		    FIX(delta_y_in_workspace),Nil,Nil,T);
	    SVREF(dragging_state,FIX((SI_Long)10L)) = dragger_x;
	    return VALUES_1(SVREF(dragging_state,FIX((SI_Long)11L)) = 
		    dragger_y);
	}
	else
	    return VALUES_1(Nil);
    }
}

static Object Kxor;                /* :xor */

static Object Qwhite;              /* white */

static Object Qblack;              /* black */

static Object Qx11_window;         /* x11-window */

static Object Qtransparent;        /* transparent */

static Object Qbackground;         /* background */

static Object Qforeground;         /* foreground */

static Object Qworkspace_foreground;  /* workspace-foreground */

static Object Qicp;                /* icp */

static Object Qtelewindows;        /* telewindows */

static Object Qprinter;            /* printer */

/* SHIFT-AND-DRAW-BLOCKS-BEING-TRANSFERRED */
Object shift_and_draw_blocks_being_transferred(dragging_state,image_plane,
	    new_x_in_window,new_y_in_window,erase_qm,draw_qm)
    Object dragging_state, image_plane, new_x_in_window, new_y_in_window;
    Object erase_qm, draw_qm;
{
    Object gensym_window, left_edge_of_draw_area, top_edge_of_draw_area;
    Object right_edge_of_draw_area, bottom_edge_of_draw_area;
    Object current_image_x_scale, current_image_y_scale;
    Object current_x_origin_of_drawing, current_y_origin_of_drawing, temp;
    Object current_frame_transform_qm, current_window_1, drawing_on_window;
    Object current_drawing_transfer_mode, type_of_current_window;
    Object current_native_window_qm, current_color_map;
    Object current_background_color_value, current_foreground_color_value;
    Object defer_notifications_qm, current_pane, current_image_plane;
    Object loose_left_edge_of_visible_workspace_area;
    Object loose_top_edge_of_visible_workspace_area;
    Object loose_right_edge_of_visible_workspace_area;
    Object loose_bottom_edge_of_visible_workspace_area, color_or_metacolor;
    Object background_color_or_metacolor, outer_native_image_plane;
    Object current_native_image_plane, color_value, old_color_value;
    Object erase_instead_qm, icp_output_port_qm, icp_socket_qm;
    Object i_am_alive_info_qm, icp_output_port_qm_1, current_icp_port;
    Object current_icp_socket, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, aref_arg_1;
    char temp_1;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_stack_pointer;
    Declare_catch(3);
    Declare_special(54);
    Object result;

    x_note_fn_call(128,76);
    SAVE_STACK();
    gensym_window = ISVREF(ISVREF(image_plane,(SI_Long)2L),(SI_Long)2L);
    left_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)7L);
    top_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)8L);
    right_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)9L);
    bottom_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)10L);
    PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
	    53);
      PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
	      52);
	PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
		51);
	  PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
		  50);
	    current_image_x_scale = FIX((SI_Long)4096L);
	    current_image_y_scale = FIX((SI_Long)4096L);
	    current_x_origin_of_drawing = FIX((SI_Long)0L);
	    current_y_origin_of_drawing = FIX((SI_Long)0L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
		    49);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
		      48);
		PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
			47);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
			  46);
		    left_edge_of_draw_area = Left_edge_of_draw_area;
		    top_edge_of_draw_area = Top_edge_of_draw_area;
		    right_edge_of_draw_area = Right_edge_of_draw_area;
		    bottom_edge_of_draw_area = Bottom_edge_of_draw_area;
		    PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
			    45);
		      PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
			      44);
			PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
				43);
			  PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
				  42);
			    temp = ISVREF(image_plane,(SI_Long)6L);
			    Left_edge_of_draw_area = FIXNUM_MAX(temp,
				    Left_edge_of_draw_area);
			    temp = ISVREF(image_plane,(SI_Long)7L);
			    Top_edge_of_draw_area = FIXNUM_MAX(temp,
				    Top_edge_of_draw_area);
			    temp = ISVREF(image_plane,(SI_Long)8L);
			    Right_edge_of_draw_area = FIXNUM_MIN(temp,
				    Right_edge_of_draw_area);
			    temp = ISVREF(image_plane,(SI_Long)9L);
			    Bottom_edge_of_draw_area = FIXNUM_MIN(temp,
				    Bottom_edge_of_draw_area);
			    if (FIXNUM_LT(Left_edge_of_draw_area,
				    Right_edge_of_draw_area) && 
				    FIXNUM_LT(Top_edge_of_draw_area,
				    Bottom_edge_of_draw_area)) {
				left_edge_of_draw_area = 
					Left_edge_of_draw_area;
				top_edge_of_draw_area = Top_edge_of_draw_area;
				right_edge_of_draw_area = 
					Right_edge_of_draw_area;
				bottom_edge_of_draw_area = 
					Bottom_edge_of_draw_area;
				PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
					41);
				  PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
					  40);
				    PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
					    39);
				      PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
					      38);
					temp = ISVREF(image_plane,
						(SI_Long)19L);
					Left_edge_of_draw_area = 
						FIXNUM_MAX(temp,
						Left_edge_of_draw_area);
					temp = ISVREF(image_plane,
						(SI_Long)20L);
					Top_edge_of_draw_area = 
						FIXNUM_MAX(temp,
						Top_edge_of_draw_area);
					temp = ISVREF(image_plane,
						(SI_Long)21L);
					Right_edge_of_draw_area = 
						FIXNUM_MIN(temp,
						Right_edge_of_draw_area);
					temp = ISVREF(image_plane,
						(SI_Long)22L);
					Bottom_edge_of_draw_area = 
						FIXNUM_MIN(temp,
						Bottom_edge_of_draw_area);
					if (FIXNUM_LT(Left_edge_of_draw_area,
						Right_edge_of_draw_area) 
						&& 
						FIXNUM_LT(Top_edge_of_draw_area,
						Bottom_edge_of_draw_area)) {
					    current_frame_transform_qm = Nil;
					    current_image_x_scale = 
						    ISVREF(image_plane,
						    (SI_Long)11L);
					    current_image_y_scale = 
						    ISVREF(image_plane,
						    (SI_Long)12L);
					    current_x_origin_of_drawing = 
						    ISVREF(image_plane,
						    (SI_Long)13L);
					    current_y_origin_of_drawing = 
						    ISVREF(image_plane,
						    (SI_Long)14L);
					    PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
						    37);
					      PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
						      36);
						PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
							35);
						  PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
							  34);
						    PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
							    33);
						      LOCK(On_window_without_drawing);
						      if (PUSH_UNWIND_PROTECT(2)) 
								  {
							  current_window_1 
								  = 
								  ISVREF(ISVREF(image_plane,
								  (SI_Long)2L),
								  (SI_Long)2L);
							  PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
								  32);
							    drawing_on_window 
								    = Nil;
							    PUSH_SPECIAL_WITH_SYMBOL(Drawing_on_window,Qdrawing_on_window,drawing_on_window,
								    31);
							      current_drawing_transfer_mode 
								      = 
								      EQ(Current_drawing_transfer_mode,
								      Kxor) 
								      ? 
								      Current_drawing_transfer_mode 
								      : 
								      ISVREF(Current_window,
								      (SI_Long)30L);
							      PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
								      30);
								type_of_current_window 
									= 
									ISVREF(Current_window,
									(SI_Long)1L);
								PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
									29);
								  current_native_window_qm 
									  = 
									  ISVREF(Current_window,
									  (SI_Long)17L);
								  PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
									  28);
								    current_color_map 
									    = 
									    ISVREF(Current_window,
									    (SI_Long)20L);
								    PUSH_SPECIAL_WITH_SYMBOL(Current_color_map,Qcurrent_color_map,current_color_map,
									    27);
								      temp 
									      = 
									      ISVREF(Current_color_map,
									      (SI_Long)5L);
								      if (temp);
								      else
									  temp 
										  = 
										  map_to_color_value_1(Qwhite);
								      current_background_color_value 
									      = 
									      temp;
								      PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
									      26);
									temp 
										= 
										ISVREF(Current_color_map,
										(SI_Long)4L);
									if (temp);
									else
									    temp 
										    = 
										    map_to_color_value_1(Qblack);
									current_foreground_color_value 
										= 
										temp;
									PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
										25);
									  defer_notifications_qm 
										  = 
										  T;
									  PUSH_SPECIAL_WITH_SYMBOL(Defer_notifications_qm,Qdefer_notifications_qm,defer_notifications_qm,
										  24);
									    LOCK(On_window_with_drawing);
									    if (PUSH_UNWIND_PROTECT(1)) 
											{
										drawing_on_window 
											= 
											T;
										PUSH_SPECIAL_WITH_SYMBOL(Drawing_on_window,Qdrawing_on_window,drawing_on_window,
											23);
										  if (EQ(Type_of_current_window,
											  Qx11_window)) 
											      {
										      LOCK(For_image_plane);
										      if (PUSH_UNWIND_PROTECT(0)) 
												  {
											  current_pane 
												  = 
												  ISVREF(image_plane,
												  (SI_Long)2L);
											  current_image_plane 
												  = 
												  image_plane;
											  loose_left_edge_of_visible_workspace_area 
												  = 
												  ISVREF(image_plane,
												  (SI_Long)23L);
											  loose_top_edge_of_visible_workspace_area 
												  = 
												  ISVREF(image_plane,
												  (SI_Long)24L);
											  loose_right_edge_of_visible_workspace_area 
												  = 
												  ISVREF(image_plane,
												  (SI_Long)25L);
											  loose_bottom_edge_of_visible_workspace_area 
												  = 
												  ISVREF(image_plane,
												  (SI_Long)26L);
											  color_or_metacolor 
												  = 
												  ISVREF(image_plane,
												  (SI_Long)5L) 
												  ?
												   
												  ISVREF(ISVREF(image_plane,
												  (SI_Long)5L),
												  (SI_Long)22L) 
												  :
												   
												  Nil;
											  if (color_or_metacolor);
											  else
											      color_or_metacolor 
												      = 
												      Qblack;
											  if (EQ(color_or_metacolor,
												  Qtransparent) 
												  || 
												  EQ(color_or_metacolor,
												  Qbackground)) 
												      {
											      background_color_or_metacolor 
												      = 
												      ISVREF(image_plane,
												      (SI_Long)5L) 
												      ?
												       
												      ISVREF(ISVREF(image_plane,
												      (SI_Long)5L),
												      (SI_Long)21L) 
												      :
												       
												      Nil;
											      if (background_color_or_metacolor);
											      else
												  background_color_or_metacolor 
													  = 
													  Qwhite;
											      if (EQ(background_color_or_metacolor,
												      Qforeground) 
												      || 
												      EQ(background_color_or_metacolor,
												      Qworkspace_foreground)) 
													  {
												  temp 
													  = 
													  ISVREF(Current_color_map,
													  (SI_Long)4L);
												  if (temp);
												  else
												      temp 
													      = 
													      map_to_color_value_1(Qblack);
												  current_foreground_color_value 
													  = 
													  temp;
											      }
											      else if (EQ(background_color_or_metacolor,
												      Qtransparent) 
												      || 
												      EQ(background_color_or_metacolor,
												      Qbackground)) 
													  {
												  temp 
													  = 
													  ISVREF(Current_color_map,
													  (SI_Long)5L);
												  if (temp);
												  else
												      temp 
													      = 
													      map_to_color_value_1(Qwhite);
												  current_foreground_color_value 
													  = 
													  temp;
											      }
											      else
												  current_foreground_color_value 
													  = 
													  EQ(background_color_or_metacolor,
													  ISVREF(Current_color_map,
													  (SI_Long)6L)) 
													  ?
													   
													  ISVREF(Current_color_map,
													  (SI_Long)7L) 
													  :
													   
													  map_to_color_value_1(background_color_or_metacolor);
											  }
											  else if (EQ(color_or_metacolor,
												  Qforeground) 
												  || 
												  EQ(color_or_metacolor,
												  Qworkspace_foreground)) 
												      {
											      temp 
												      = 
												      ISVREF(Current_color_map,
												      (SI_Long)4L);
											      if (temp);
											      else
												  temp 
													  = 
													  map_to_color_value_1(Qblack);
											      current_foreground_color_value 
												      = 
												      temp;
											  }
											  else
											      current_foreground_color_value 
												      = 
												      EQ(color_or_metacolor,
												      ISVREF(Current_color_map,
												      (SI_Long)6L)) 
												      ?
												       
												      ISVREF(Current_color_map,
												      (SI_Long)7L) 
												      :
												       
												      map_to_color_value_1(color_or_metacolor);
											  PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
												  10);
											    PUSH_SPECIAL_WITH_SYMBOL(Loose_bottom_edge_of_visible_workspace_area,Qloose_bottom_edge_of_visible_workspace_area,loose_bottom_edge_of_visible_workspace_area,
												    9);
											      PUSH_SPECIAL_WITH_SYMBOL(Loose_right_edge_of_visible_workspace_area,Qloose_right_edge_of_visible_workspace_area,loose_right_edge_of_visible_workspace_area,
												      8);
												PUSH_SPECIAL_WITH_SYMBOL(Loose_top_edge_of_visible_workspace_area,Qloose_top_edge_of_visible_workspace_area,loose_top_edge_of_visible_workspace_area,
													7);
												  PUSH_SPECIAL_WITH_SYMBOL(Loose_left_edge_of_visible_workspace_area,Qloose_left_edge_of_visible_workspace_area,loose_left_edge_of_visible_workspace_area,
													  6);
												    PUSH_SPECIAL_WITH_SYMBOL(Current_image_plane,Qcurrent_image_plane,current_image_plane,
													    5);
												      PUSH_SPECIAL_WITH_SYMBOL(Current_pane,Qcurrent_pane,current_pane,
													      4);
													outer_native_image_plane 
														= 
														Current_native_image_plane;
													PUSH_SPECIAL_WITH_SYMBOL(Outer_native_image_plane,Qouter_native_image_plane,outer_native_image_plane,
														3);
													  current_native_image_plane 
														  = 
														  image_plane;
													  PUSH_SPECIAL_WITH_SYMBOL(Current_native_image_plane,Qcurrent_native_image_plane,current_native_image_plane,
														  2);
													    if ( 
														    !EQ(Outer_native_image_plane,
														    Current_native_image_plane))
														nip_begin_drawing(Current_native_image_plane);
													    color_or_metacolor 
														    = 
														    ISVREF(image_plane,
														    (SI_Long)5L) 
														    ?
														     
														    ISVREF(ISVREF(image_plane,
														    (SI_Long)5L),
														    (SI_Long)21L) 
														    :
														     
														    Nil;
													    if (color_or_metacolor);
													    else
														color_or_metacolor 
															= 
															Qwhite;
													    if (EQ(color_or_metacolor,
														    Qtransparent) 
														    || 
														    EQ(color_or_metacolor,
														    Qbackground)) 
															{
														color_value 
															= 
															ISVREF(Current_color_map,
															(SI_Long)5L);
														if (color_value);
														else
														    color_value 
															    = 
															    map_to_color_value_1(Qwhite);
													    }
													    else if (EQ(color_or_metacolor,
														    Qforeground) 
														    || 
														    EQ(color_or_metacolor,
														    Qworkspace_foreground)) 
															{
														temp 
															= 
															ISVREF(image_plane,
															(SI_Long)5L) 
															?
															 
															ISVREF(ISVREF(image_plane,
															(SI_Long)5L),
															(SI_Long)22L) 
															:
															 
															Nil;
														if (temp);
														else
														    temp 
															    = 
															    Qblack;
														color_or_metacolor 
															= 
															temp;
														if (EQ(color_or_metacolor,
															Qtransparent) 
															|| 
															EQ(color_or_metacolor,
															Qbackground)) 
															    {
														    background_color_or_metacolor 
															    = 
															    ISVREF(image_plane,
															    (SI_Long)5L) 
															    ?
															     
															    ISVREF(ISVREF(image_plane,
															    (SI_Long)5L),
															    (SI_Long)21L) 
															    :
															     
															    Nil;
														    if (background_color_or_metacolor);
														    else
															background_color_or_metacolor 
																= 
																Qwhite;
														    if (EQ(background_color_or_metacolor,
															    Qforeground) 
															    || 
															    EQ(background_color_or_metacolor,
															    Qworkspace_foreground)) 
																{
															color_value 
																= 
																ISVREF(Current_color_map,
																(SI_Long)4L);
															if (color_value);
															else
															    color_value 
																    = 
																    map_to_color_value_1(Qblack);
														    }
														    else if (EQ(background_color_or_metacolor,
															    Qtransparent) 
															    || 
															    EQ(background_color_or_metacolor,
															    Qbackground)) 
																{
															color_value 
																= 
																ISVREF(Current_color_map,
																(SI_Long)5L);
															if (color_value);
															else
															    color_value 
																    = 
																    map_to_color_value_1(Qwhite);
														    }
														    else
															color_value 
																= 
																EQ(background_color_or_metacolor,
																ISVREF(Current_color_map,
																(SI_Long)6L)) 
																?
																 
																ISVREF(Current_color_map,
																(SI_Long)7L) 
																:
																 
																map_to_color_value_1(background_color_or_metacolor);
														}
														else if (EQ(color_or_metacolor,
															Qforeground) 
															|| 
															EQ(color_or_metacolor,
															Qworkspace_foreground)) 
															    {
														    color_value 
															    = 
															    ISVREF(Current_color_map,
															    (SI_Long)4L);
														    if (color_value);
														    else
															color_value 
																= 
																map_to_color_value_1(Qblack);
														}
														else
														    color_value 
															    = 
															    EQ(color_or_metacolor,
															    ISVREF(Current_color_map,
															    (SI_Long)6L)) 
															    ?
															     
															    ISVREF(Current_color_map,
															    (SI_Long)7L) 
															    :
															     
															    map_to_color_value_1(color_or_metacolor);
													    }
													    else
														color_value 
															= 
															EQ(color_or_metacolor,
															ISVREF(Current_color_map,
															(SI_Long)6L)) 
															?
															 
															ISVREF(Current_color_map,
															(SI_Long)7L) 
															:
															 
															map_to_color_value_1(color_or_metacolor);
													    old_color_value 
														    = 
														    Current_background_color_value;
													    current_background_color_value 
														    = 
														    Current_background_color_value;
													    PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
														    1);
													      set_current_background_color_value(color_value);
													      if (erase_qm) 
															  {
														  erase_instead_qm 
															  = 
															  T;
														  PUSH_SPECIAL_WITH_SYMBOL(Erase_instead_qm,Qerase_instead_qm,erase_instead_qm,
															  0);
														    draw_image_plane_cursor_1(dragging_state);
														    if ( 
															    !TRUEP(draw_qm))
															remove_image_plane_cursor(image_plane,
																dragging_state);
														  POP_SPECIAL();
													      }
													      if (draw_qm) 
															  {
														  SVREF(dragging_state,
															  FIX((SI_Long)19L)) 
															  = 
															  new_x_in_window;
														  SVREF(dragging_state,
															  FIX((SI_Long)20L)) 
															  = 
															  new_y_in_window;
														  draw_image_plane_cursor_1(dragging_state);
														  add_image_plane_cursor(image_plane,
															  dragging_state);
													      }
													      set_current_background_color_value(old_color_value);
													    POP_SPECIAL();
													    if ( 
														    !EQ(Outer_native_image_plane,
														    Current_native_image_plane))
														nip_end_drawing(Current_native_image_plane);
													  POP_SPECIAL();
													  temp 
														  = 
														  Current_native_image_plane 
														  ?
														   
														  ( 
														  !EQ(image_plane,
														  Current_native_image_plane) 
														  ?
														   
														  nip_begin_drawing(Current_native_image_plane) 
														  :
														   
														  Nil) 
														  :
														   
														  Nil;
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
										      UNLOCK(For_image_plane);
										      CONTINUE_UNWINDING(0);
										      result = RESTORE_VALUES();
										      SAVE_VALUES(VALUES_1(result));
										      if (Flush_graphics_immediately_qm)
											  sync_graphics_on_current_window();
										  }
										  else if (EQ(Type_of_current_window,
											  Qicp)) 
											      {
										      icp_output_port_qm 
											      = 
											      ISVREF(Current_window,
											      (SI_Long)12L);
										      icp_socket_qm 
											      = 
											      icp_output_port_qm 
											      ?
											       
											      ISVREF(icp_output_port_qm,
											      (SI_Long)2L) 
											      :
											       
											      Qnil;
										      if (icp_socket_qm) 
												  {
											  i_am_alive_info_qm 
												  = 
												  ISVREF(icp_socket_qm,
												  (SI_Long)24L);
											  temp_1 
												  = 
												   
												  !TRUEP(i_am_alive_info_qm);
											  if (temp_1);
											  else
											      temp_1 
												      = 
												       
												      !TRUEP(Do_icp_flow_control_qm);
											  if (temp_1);
											  else
											      temp_1 
												      = 
												       
												      !TRUEP(ISVREF(i_am_alive_info_qm,
												      (SI_Long)2L));
										      }
										      else
											  temp_1 
												  = 
												  TRUEP(Nil);
										      if (temp_1) 
												  {
											  icp_output_port_qm_1 
												  = 
												  ISVREF(Current_window,
												  (SI_Long)12L);
											  if (icp_output_port_qm_1 
												  && 
												  icp_connection_open_p(ISVREF(icp_output_port_qm_1,
												  (SI_Long)2L))) 
												      {
											      current_icp_port 
												      = 
												      icp_output_port_qm_1;
											      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
												      22);
												current_icp_socket 
													= 
													ISVREF(Current_icp_port,
													(SI_Long)2L);
												PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
													21);
												  temp 
													  = 
													  IFIX(ISVREF(Current_icp_socket,
													  (SI_Long)22L)) 
													  >= 
													  (SI_Long)17L 
													  ?
													   
													  ISVREF(Current_icp_socket,
													  (SI_Long)53L) 
													  :
													   
													  Nil;
												  if (temp);
												  else
												      temp 
													      = 
													      EQ(ISVREF(Current_icp_socket,
													      (SI_Long)25L),
													      Qtelewindows) 
													      ?
													       T : Nil;
												  disable_resumability 
													  = 
													  temp;
												  PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
													  20);
												    number_of_icp_bytes_for_message_series 
													    = 
													    FIX((SI_Long)0L);
												    PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
													    19);
												      icp_buffers_for_message_group 
													      = 
													      Nil;
												      PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
													      18);
													icp_buffer_of_start_of_message_series_qm 
														= 
														Nil;
													PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
														17);
													  icp_byte_position_of_start_of_message_series_qm 
														  = 
														  Nil;
													  PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
														  16);
													    number_of_icp_bytes_to_fill_buffer 
														    = 
														    FIX((SI_Long)0L);
													    PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
														    15);
													      current_icp_buffer 
														      = 
														      Nil;
													      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
														      14);
														current_write_icp_byte_position 
															= 
															Nil;
														PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
															13);
														  number_of_icp_bytes_in_message_group 
															  = 
															  FIX((SI_Long)0L);
														  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
															  12);
														    writing_icp_message_group 
															    = 
															    FIXNUM_ADD1(Writing_icp_message_group);
														    PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
															    11);
														      gensymed_symbol 
															      = 
															      Nil;
														      gensymed_symbol_1 
															      = 
															      0.0;
														      gensymed_symbol_2 
															      = 
															      0.0;
														      if (Profiling_enabled_qm) 
																  {
															  gensymed_symbol 
																  = 
																  T;
															  gensymed_symbol_1 
																  = 
																  DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
																  (SI_Long)2L),
																  (SI_Long)0L);
															  gensymed_symbol_2 
																  = 
																  g2ext_unix_time_as_float();
															  aref_arg_1 
																  = 
																  ISVREF(Profiling_enabled_qm,
																  (SI_Long)2L);
															  DFLOAT_ISASET_1(aref_arg_1,
																  (SI_Long)0L,
																  gensymed_symbol_2);
														      }
														      if (icp_connection_open_p(Current_icp_socket) 
															      && 
															       
															      !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
																  {
															  synchronize_icp_on_window_with_drawing(Current_window,
																  Left_edge_of_draw_area,
																  Top_edge_of_draw_area,
																  Right_edge_of_draw_area,
																  Bottom_edge_of_draw_area);
															  LOCK(For_image_plane);
															  if (PUSH_UNWIND_PROTECT(0)) 
																      {
															      current_pane 
																      = 
																      ISVREF(image_plane,
																      (SI_Long)2L);
															      current_image_plane 
																      = 
																      image_plane;
															      loose_left_edge_of_visible_workspace_area 
																      = 
																      ISVREF(image_plane,
																      (SI_Long)23L);
															      loose_top_edge_of_visible_workspace_area 
																      = 
																      ISVREF(image_plane,
																      (SI_Long)24L);
															      loose_right_edge_of_visible_workspace_area 
																      = 
																      ISVREF(image_plane,
																      (SI_Long)25L);
															      loose_bottom_edge_of_visible_workspace_area 
																      = 
																      ISVREF(image_plane,
																      (SI_Long)26L);
															      color_or_metacolor 
																      = 
																      ISVREF(image_plane,
																      (SI_Long)5L) 
																      ?
																       
																      ISVREF(ISVREF(image_plane,
																      (SI_Long)5L),
																      (SI_Long)22L) 
																      :
																       
																      Nil;
															      if (color_or_metacolor);
															      else
																  color_or_metacolor 
																	  = 
																	  Qblack;
															      if (EQ(color_or_metacolor,
																      Qtransparent) 
																      || 
																      EQ(color_or_metacolor,
																      Qbackground)) 
																	  {
																  background_color_or_metacolor 
																	  = 
																	  ISVREF(image_plane,
																	  (SI_Long)5L) 
																	  ?
																	   
																	  ISVREF(ISVREF(image_plane,
																	  (SI_Long)5L),
																	  (SI_Long)21L) 
																	  :
																	   
																	  Nil;
																  if (background_color_or_metacolor);
																  else
																      background_color_or_metacolor 
																	      = 
																	      Qwhite;
																  if (EQ(background_color_or_metacolor,
																	  Qforeground) 
																	  || 
																	  EQ(background_color_or_metacolor,
																	  Qworkspace_foreground)) 
																	      {
																      temp 
																	      = 
																	      ISVREF(Current_color_map,
																	      (SI_Long)4L);
																      if (temp);
																      else
																	  temp 
																		  = 
																		  map_to_color_value_1(Qblack);
																      current_foreground_color_value 
																	      = 
																	      temp;
																  }
																  else if (EQ(background_color_or_metacolor,
																	  Qtransparent) 
																	  || 
																	  EQ(background_color_or_metacolor,
																	  Qbackground)) 
																	      {
																      temp 
																	      = 
																	      ISVREF(Current_color_map,
																	      (SI_Long)5L);
																      if (temp);
																      else
																	  temp 
																		  = 
																		  map_to_color_value_1(Qwhite);
																      current_foreground_color_value 
																	      = 
																	      temp;
																  }
																  else
																      current_foreground_color_value 
																	      = 
																	      EQ(background_color_or_metacolor,
																	      ISVREF(Current_color_map,
																	      (SI_Long)6L)) 
																	      ?
																	       
																	      ISVREF(Current_color_map,
																	      (SI_Long)7L) 
																	      :
																	       
																	      map_to_color_value_1(background_color_or_metacolor);
															      }
															      else if (EQ(color_or_metacolor,
																      Qforeground) 
																      || 
																      EQ(color_or_metacolor,
																      Qworkspace_foreground)) 
																	  {
																  temp 
																	  = 
																	  ISVREF(Current_color_map,
																	  (SI_Long)4L);
																  if (temp);
																  else
																      temp 
																	      = 
																	      map_to_color_value_1(Qblack);
																  current_foreground_color_value 
																	  = 
																	  temp;
															      }
															      else
																  current_foreground_color_value 
																	  = 
																	  EQ(color_or_metacolor,
																	  ISVREF(Current_color_map,
																	  (SI_Long)6L)) 
																	  ?
																	   
																	  ISVREF(Current_color_map,
																	  (SI_Long)7L) 
																	  :
																	   
																	  map_to_color_value_1(color_or_metacolor);
															      PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
																      10);
																PUSH_SPECIAL_WITH_SYMBOL(Loose_bottom_edge_of_visible_workspace_area,Qloose_bottom_edge_of_visible_workspace_area,loose_bottom_edge_of_visible_workspace_area,
																	9);
																  PUSH_SPECIAL_WITH_SYMBOL(Loose_right_edge_of_visible_workspace_area,Qloose_right_edge_of_visible_workspace_area,loose_right_edge_of_visible_workspace_area,
																	  8);
																    PUSH_SPECIAL_WITH_SYMBOL(Loose_top_edge_of_visible_workspace_area,Qloose_top_edge_of_visible_workspace_area,loose_top_edge_of_visible_workspace_area,
																	    7);
																      PUSH_SPECIAL_WITH_SYMBOL(Loose_left_edge_of_visible_workspace_area,Qloose_left_edge_of_visible_workspace_area,loose_left_edge_of_visible_workspace_area,
																	      6);
																	PUSH_SPECIAL_WITH_SYMBOL(Current_image_plane,Qcurrent_image_plane,current_image_plane,
																		5);
																	  PUSH_SPECIAL_WITH_SYMBOL(Current_pane,Qcurrent_pane,current_pane,
																		  4);
																	    outer_native_image_plane 
																		    = 
																		    Current_native_image_plane;
																	    PUSH_SPECIAL_WITH_SYMBOL(Outer_native_image_plane,Qouter_native_image_plane,outer_native_image_plane,
																		    3);
																	      current_native_image_plane 
																		      = 
																		      image_plane;
																	      PUSH_SPECIAL_WITH_SYMBOL(Current_native_image_plane,Qcurrent_native_image_plane,current_native_image_plane,
																		      2);
																		if ( 
																			!EQ(Outer_native_image_plane,
																			Current_native_image_plane))
																		    nip_begin_drawing(Current_native_image_plane);
																		color_or_metacolor 
																			= 
																			ISVREF(image_plane,
																			(SI_Long)5L) 
																			?
																			 
																			ISVREF(ISVREF(image_plane,
																			(SI_Long)5L),
																			(SI_Long)21L) 
																			:
																			 
																			Nil;
																		if (color_or_metacolor);
																		else
																		    color_or_metacolor 
																			    = 
																			    Qwhite;
																		if (EQ(color_or_metacolor,
																			Qtransparent) 
																			|| 
																			EQ(color_or_metacolor,
																			Qbackground)) 
																			    {
																		    color_value 
																			    = 
																			    ISVREF(Current_color_map,
																			    (SI_Long)5L);
																		    if (color_value);
																		    else
																			color_value 
																				= 
																				map_to_color_value_1(Qwhite);
																		}
																		else if (EQ(color_or_metacolor,
																			Qforeground) 
																			|| 
																			EQ(color_or_metacolor,
																			Qworkspace_foreground)) 
																			    {
																		    temp 
																			    = 
																			    ISVREF(image_plane,
																			    (SI_Long)5L) 
																			    ?
																			     
																			    ISVREF(ISVREF(image_plane,
																			    (SI_Long)5L),
																			    (SI_Long)22L) 
																			    :
																			     
																			    Nil;
																		    if (temp);
																		    else
																			temp 
																				= 
																				Qblack;
																		    color_or_metacolor 
																			    = 
																			    temp;
																		    if (EQ(color_or_metacolor,
																			    Qtransparent) 
																			    || 
																			    EQ(color_or_metacolor,
																			    Qbackground)) 
																				{
																			background_color_or_metacolor 
																				= 
																				ISVREF(image_plane,
																				(SI_Long)5L) 
																				?
																				 
																				ISVREF(ISVREF(image_plane,
																				(SI_Long)5L),
																				(SI_Long)21L) 
																				:
																				 
																				Nil;
																			if (background_color_or_metacolor);
																			else
																			    background_color_or_metacolor 
																				    = 
																				    Qwhite;
																			if (EQ(background_color_or_metacolor,
																				Qforeground) 
																				|| 
																				EQ(background_color_or_metacolor,
																				Qworkspace_foreground)) 
																				    {
																			    color_value 
																				    = 
																				    ISVREF(Current_color_map,
																				    (SI_Long)4L);
																			    if (color_value);
																			    else
																				color_value 
																					= 
																					map_to_color_value_1(Qblack);
																			}
																			else if (EQ(background_color_or_metacolor,
																				Qtransparent) 
																				|| 
																				EQ(background_color_or_metacolor,
																				Qbackground)) 
																				    {
																			    color_value 
																				    = 
																				    ISVREF(Current_color_map,
																				    (SI_Long)5L);
																			    if (color_value);
																			    else
																				color_value 
																					= 
																					map_to_color_value_1(Qwhite);
																			}
																			else
																			    color_value 
																				    = 
																				    EQ(background_color_or_metacolor,
																				    ISVREF(Current_color_map,
																				    (SI_Long)6L)) 
																				    ?
																				     
																				    ISVREF(Current_color_map,
																				    (SI_Long)7L) 
																				    :
																				     
																				    map_to_color_value_1(background_color_or_metacolor);
																		    }
																		    else if (EQ(color_or_metacolor,
																			    Qforeground) 
																			    || 
																			    EQ(color_or_metacolor,
																			    Qworkspace_foreground)) 
																				{
																			color_value 
																				= 
																				ISVREF(Current_color_map,
																				(SI_Long)4L);
																			if (color_value);
																			else
																			    color_value 
																				    = 
																				    map_to_color_value_1(Qblack);
																		    }
																		    else
																			color_value 
																				= 
																				EQ(color_or_metacolor,
																				ISVREF(Current_color_map,
																				(SI_Long)6L)) 
																				?
																				 
																				ISVREF(Current_color_map,
																				(SI_Long)7L) 
																				:
																				 
																				map_to_color_value_1(color_or_metacolor);
																		}
																		else
																		    color_value 
																			    = 
																			    EQ(color_or_metacolor,
																			    ISVREF(Current_color_map,
																			    (SI_Long)6L)) 
																			    ?
																			     
																			    ISVREF(Current_color_map,
																			    (SI_Long)7L) 
																			    :
																			     
																			    map_to_color_value_1(color_or_metacolor);
																		old_color_value 
																			= 
																			Current_background_color_value;
																		current_background_color_value 
																			= 
																			Current_background_color_value;
																		PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
																			1);
																		  set_current_background_color_value(color_value);
																		  if (erase_qm) 
																			      {
																		      erase_instead_qm 
																			      = 
																			      T;
																		      PUSH_SPECIAL_WITH_SYMBOL(Erase_instead_qm,Qerase_instead_qm,erase_instead_qm,
																			      0);
																			draw_image_plane_cursor_1(dragging_state);
																			if ( 
																				!TRUEP(draw_qm))
																			    remove_image_plane_cursor(image_plane,
																				    dragging_state);
																		      POP_SPECIAL();
																		  }
																		  if (draw_qm) 
																			      {
																		      SVREF(dragging_state,
																			      FIX((SI_Long)19L)) 
																			      = 
																			      new_x_in_window;
																		      SVREF(dragging_state,
																			      FIX((SI_Long)20L)) 
																			      = 
																			      new_y_in_window;
																		      draw_image_plane_cursor_1(dragging_state);
																		      add_image_plane_cursor(image_plane,
																			      dragging_state);
																		  }
																		  set_current_background_color_value(old_color_value);
																		POP_SPECIAL();
																		if ( 
																			!EQ(Outer_native_image_plane,
																			Current_native_image_plane))
																		    nip_end_drawing(Current_native_image_plane);
																	      POP_SPECIAL();
																	      temp 
																		      = 
																		      Current_native_image_plane 
																		      ?
																		       
																		      ( 
																		      !EQ(image_plane,
																		      Current_native_image_plane) 
																		      ?
																		       
																		      nip_begin_drawing(Current_native_image_plane) 
																		      :
																		       
																		      Nil) 
																		      :
																		       
																		      Nil;
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
															  UNLOCK(For_image_plane);
															  CONTINUE_UNWINDING(0);
															  result = RESTORE_VALUES();
															  temp 
																  = 
																  result;
															  if (Flush_graphics_immediately_qm 
																  && 
																  FIXNUM_NE(ISVREF(Current_icp_socket,
																  (SI_Long)15L),
																  Icp_connection_closed))
															      sync_graphics_on_current_window();
															  end_icp_message_group();
														      }
														      else
															  temp 
																  = 
																  Nil;
														      SAVE_VALUES(VALUES_1(temp));
														      if (Profiling_enabled_qm) 
																  {
															  gensymed_symbol_3 
																  = 
																  g2ext_unix_time_as_float();
															  gensymed_symbol_4 
																  = 
																  DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
																  (SI_Long)2L),
																  (SI_Long)0L);
															  gensymed_symbol_5 
																  = 
																  gensymed_symbol_3 
																  - 
																  gensymed_symbol_4;
															  aref_arg_1 
																  = 
																  ISVREF(Profiling_enabled_qm,
																  (SI_Long)6L);
															  aref_new_value 
																  = 
																  gensymed_symbol_5 
																  + 
																  DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
																  (SI_Long)6L),
																  (SI_Long)0L);
															  DFLOAT_ISASET_1(aref_arg_1,
																  (SI_Long)0L,
																  aref_new_value);
															  aref_arg_1 
																  = 
																  ISVREF(Profiling_enabled_qm,
																  (SI_Long)2L);
															  aref_new_value 
																  = 
																  gensymed_symbol 
																  ?
																   
																  gensymed_symbol_1 
																  + 
																  gensymed_symbol_5 
																  + 
																  (gensymed_symbol_4 
																  - 
																  gensymed_symbol_2) 
																  :
																   
																  gensymed_symbol_3;
															  DFLOAT_ISASET_1(aref_arg_1,
																  (SI_Long)0L,
																  aref_new_value);
														      }
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
											  else
											      SAVE_VALUES(VALUES_1(Nil));
										      }
										      else
											  SAVE_VALUES(VALUES_1(Nil));
										  }
										  else if (EQ(Type_of_current_window,
											  Qprinter)) 
											      {
										      LOCK(For_image_plane);
										      if (PUSH_UNWIND_PROTECT(0)) 
												  {
											  current_pane 
												  = 
												  ISVREF(image_plane,
												  (SI_Long)2L);
											  current_image_plane 
												  = 
												  image_plane;
											  loose_left_edge_of_visible_workspace_area 
												  = 
												  ISVREF(image_plane,
												  (SI_Long)23L);
											  loose_top_edge_of_visible_workspace_area 
												  = 
												  ISVREF(image_plane,
												  (SI_Long)24L);
											  loose_right_edge_of_visible_workspace_area 
												  = 
												  ISVREF(image_plane,
												  (SI_Long)25L);
											  loose_bottom_edge_of_visible_workspace_area 
												  = 
												  ISVREF(image_plane,
												  (SI_Long)26L);
											  color_or_metacolor 
												  = 
												  ISVREF(image_plane,
												  (SI_Long)5L) 
												  ?
												   
												  ISVREF(ISVREF(image_plane,
												  (SI_Long)5L),
												  (SI_Long)22L) 
												  :
												   
												  Nil;
											  if (color_or_metacolor);
											  else
											      color_or_metacolor 
												      = 
												      Qblack;
											  if (EQ(color_or_metacolor,
												  Qtransparent) 
												  || 
												  EQ(color_or_metacolor,
												  Qbackground)) 
												      {
											      background_color_or_metacolor 
												      = 
												      ISVREF(image_plane,
												      (SI_Long)5L) 
												      ?
												       
												      ISVREF(ISVREF(image_plane,
												      (SI_Long)5L),
												      (SI_Long)21L) 
												      :
												       
												      Nil;
											      if (background_color_or_metacolor);
											      else
												  background_color_or_metacolor 
													  = 
													  Qwhite;
											      if (EQ(background_color_or_metacolor,
												      Qforeground) 
												      || 
												      EQ(background_color_or_metacolor,
												      Qworkspace_foreground)) 
													  {
												  temp 
													  = 
													  ISVREF(Current_color_map,
													  (SI_Long)4L);
												  if (temp);
												  else
												      temp 
													      = 
													      map_to_color_value_1(Qblack);
												  current_foreground_color_value 
													  = 
													  temp;
											      }
											      else if (EQ(background_color_or_metacolor,
												      Qtransparent) 
												      || 
												      EQ(background_color_or_metacolor,
												      Qbackground)) 
													  {
												  temp 
													  = 
													  ISVREF(Current_color_map,
													  (SI_Long)5L);
												  if (temp);
												  else
												      temp 
													      = 
													      map_to_color_value_1(Qwhite);
												  current_foreground_color_value 
													  = 
													  temp;
											      }
											      else
												  current_foreground_color_value 
													  = 
													  EQ(background_color_or_metacolor,
													  ISVREF(Current_color_map,
													  (SI_Long)6L)) 
													  ?
													   
													  ISVREF(Current_color_map,
													  (SI_Long)7L) 
													  :
													   
													  map_to_color_value_1(background_color_or_metacolor);
											  }
											  else if (EQ(color_or_metacolor,
												  Qforeground) 
												  || 
												  EQ(color_or_metacolor,
												  Qworkspace_foreground)) 
												      {
											      temp 
												      = 
												      ISVREF(Current_color_map,
												      (SI_Long)4L);
											      if (temp);
											      else
												  temp 
													  = 
													  map_to_color_value_1(Qblack);
											      current_foreground_color_value 
												      = 
												      temp;
											  }
											  else
											      current_foreground_color_value 
												      = 
												      EQ(color_or_metacolor,
												      ISVREF(Current_color_map,
												      (SI_Long)6L)) 
												      ?
												       
												      ISVREF(Current_color_map,
												      (SI_Long)7L) 
												      :
												       
												      map_to_color_value_1(color_or_metacolor);
											  PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
												  10);
											    PUSH_SPECIAL_WITH_SYMBOL(Loose_bottom_edge_of_visible_workspace_area,Qloose_bottom_edge_of_visible_workspace_area,loose_bottom_edge_of_visible_workspace_area,
												    9);
											      PUSH_SPECIAL_WITH_SYMBOL(Loose_right_edge_of_visible_workspace_area,Qloose_right_edge_of_visible_workspace_area,loose_right_edge_of_visible_workspace_area,
												      8);
												PUSH_SPECIAL_WITH_SYMBOL(Loose_top_edge_of_visible_workspace_area,Qloose_top_edge_of_visible_workspace_area,loose_top_edge_of_visible_workspace_area,
													7);
												  PUSH_SPECIAL_WITH_SYMBOL(Loose_left_edge_of_visible_workspace_area,Qloose_left_edge_of_visible_workspace_area,loose_left_edge_of_visible_workspace_area,
													  6);
												    PUSH_SPECIAL_WITH_SYMBOL(Current_image_plane,Qcurrent_image_plane,current_image_plane,
													    5);
												      PUSH_SPECIAL_WITH_SYMBOL(Current_pane,Qcurrent_pane,current_pane,
													      4);
													outer_native_image_plane 
														= 
														Current_native_image_plane;
													PUSH_SPECIAL_WITH_SYMBOL(Outer_native_image_plane,Qouter_native_image_plane,outer_native_image_plane,
														3);
													  current_native_image_plane 
														  = 
														  image_plane;
													  PUSH_SPECIAL_WITH_SYMBOL(Current_native_image_plane,Qcurrent_native_image_plane,current_native_image_plane,
														  2);
													    if ( 
														    !EQ(Outer_native_image_plane,
														    Current_native_image_plane))
														nip_begin_drawing(Current_native_image_plane);
													    color_or_metacolor 
														    = 
														    ISVREF(image_plane,
														    (SI_Long)5L) 
														    ?
														     
														    ISVREF(ISVREF(image_plane,
														    (SI_Long)5L),
														    (SI_Long)21L) 
														    :
														     
														    Nil;
													    if (color_or_metacolor);
													    else
														color_or_metacolor 
															= 
															Qwhite;
													    if (EQ(color_or_metacolor,
														    Qtransparent) 
														    || 
														    EQ(color_or_metacolor,
														    Qbackground)) 
															{
														color_value 
															= 
															ISVREF(Current_color_map,
															(SI_Long)5L);
														if (color_value);
														else
														    color_value 
															    = 
															    map_to_color_value_1(Qwhite);
													    }
													    else if (EQ(color_or_metacolor,
														    Qforeground) 
														    || 
														    EQ(color_or_metacolor,
														    Qworkspace_foreground)) 
															{
														temp 
															= 
															ISVREF(image_plane,
															(SI_Long)5L) 
															?
															 
															ISVREF(ISVREF(image_plane,
															(SI_Long)5L),
															(SI_Long)22L) 
															:
															 
															Nil;
														if (temp);
														else
														    temp 
															    = 
															    Qblack;
														color_or_metacolor 
															= 
															temp;
														if (EQ(color_or_metacolor,
															Qtransparent) 
															|| 
															EQ(color_or_metacolor,
															Qbackground)) 
															    {
														    background_color_or_metacolor 
															    = 
															    ISVREF(image_plane,
															    (SI_Long)5L) 
															    ?
															     
															    ISVREF(ISVREF(image_plane,
															    (SI_Long)5L),
															    (SI_Long)21L) 
															    :
															     
															    Nil;
														    if (background_color_or_metacolor);
														    else
															background_color_or_metacolor 
																= 
																Qwhite;
														    if (EQ(background_color_or_metacolor,
															    Qforeground) 
															    || 
															    EQ(background_color_or_metacolor,
															    Qworkspace_foreground)) 
																{
															color_value 
																= 
																ISVREF(Current_color_map,
																(SI_Long)4L);
															if (color_value);
															else
															    color_value 
																    = 
																    map_to_color_value_1(Qblack);
														    }
														    else if (EQ(background_color_or_metacolor,
															    Qtransparent) 
															    || 
															    EQ(background_color_or_metacolor,
															    Qbackground)) 
																{
															color_value 
																= 
																ISVREF(Current_color_map,
																(SI_Long)5L);
															if (color_value);
															else
															    color_value 
																    = 
																    map_to_color_value_1(Qwhite);
														    }
														    else
															color_value 
																= 
																EQ(background_color_or_metacolor,
																ISVREF(Current_color_map,
																(SI_Long)6L)) 
																?
																 
																ISVREF(Current_color_map,
																(SI_Long)7L) 
																:
																 
																map_to_color_value_1(background_color_or_metacolor);
														}
														else if (EQ(color_or_metacolor,
															Qforeground) 
															|| 
															EQ(color_or_metacolor,
															Qworkspace_foreground)) 
															    {
														    color_value 
															    = 
															    ISVREF(Current_color_map,
															    (SI_Long)4L);
														    if (color_value);
														    else
															color_value 
																= 
																map_to_color_value_1(Qblack);
														}
														else
														    color_value 
															    = 
															    EQ(color_or_metacolor,
															    ISVREF(Current_color_map,
															    (SI_Long)6L)) 
															    ?
															     
															    ISVREF(Current_color_map,
															    (SI_Long)7L) 
															    :
															     
															    map_to_color_value_1(color_or_metacolor);
													    }
													    else
														color_value 
															= 
															EQ(color_or_metacolor,
															ISVREF(Current_color_map,
															(SI_Long)6L)) 
															?
															 
															ISVREF(Current_color_map,
															(SI_Long)7L) 
															:
															 
															map_to_color_value_1(color_or_metacolor);
													    old_color_value 
														    = 
														    Current_background_color_value;
													    current_background_color_value 
														    = 
														    Current_background_color_value;
													    PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
														    1);
													      set_current_background_color_value(color_value);
													      if (erase_qm) 
															  {
														  erase_instead_qm 
															  = 
															  T;
														  PUSH_SPECIAL_WITH_SYMBOL(Erase_instead_qm,Qerase_instead_qm,erase_instead_qm,
															  0);
														    draw_image_plane_cursor_1(dragging_state);
														    if ( 
															    !TRUEP(draw_qm))
															remove_image_plane_cursor(image_plane,
																dragging_state);
														  POP_SPECIAL();
													      }
													      if (draw_qm) 
															  {
														  SVREF(dragging_state,
															  FIX((SI_Long)19L)) 
															  = 
															  new_x_in_window;
														  SVREF(dragging_state,
															  FIX((SI_Long)20L)) 
															  = 
															  new_y_in_window;
														  draw_image_plane_cursor_1(dragging_state);
														  add_image_plane_cursor(image_plane,
															  dragging_state);
													      }
													      set_current_background_color_value(old_color_value);
													    POP_SPECIAL();
													    if ( 
														    !EQ(Outer_native_image_plane,
														    Current_native_image_plane))
														nip_end_drawing(Current_native_image_plane);
													  POP_SPECIAL();
													  if (Current_native_image_plane) 
														      {
													      if ( 
														      !EQ(image_plane,
														      Current_native_image_plane))
														  SAVE_VALUES(nip_begin_drawing(Current_native_image_plane));
													      else
														  SAVE_VALUES(VALUES_1(Nil));
													  }
													  else
													      SAVE_VALUES(VALUES_1(Nil));
													POP_SPECIAL();
												      POP_SPECIAL();
												    POP_SPECIAL();
												  POP_SPECIAL();
												POP_SPECIAL();
											      POP_SPECIAL();
											    POP_SPECIAL();
											  POP_SPECIAL();
										      }
										      POP_UNWIND_PROTECT(0);
										      UNLOCK(For_image_plane);
										      CONTINUE_UNWINDING(0);
										  }
										  else
										      SAVE_VALUES(VALUES_1(Qnil));
										POP_SPECIAL();
									    }
									    POP_UNWIND_PROTECT(1);
									    UNLOCK(On_window_with_drawing);
									    CONTINUE_UNWINDING(1);
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
						      POP_UNWIND_PROTECT(2);
						      UNLOCK(On_window_without_drawing);
						      CONTINUE_UNWINDING(2);
						      result = RESTORE_VALUES();
						    POP_SPECIAL();
						  POP_SPECIAL();
						POP_SPECIAL();
					      POP_SPECIAL();
					    POP_SPECIAL();
					}
					else
					    result = VALUES_1(Nil);
				      POP_SPECIAL();
				    POP_SPECIAL();
				  POP_SPECIAL();
				POP_SPECIAL();
			    }
			    else
				result = VALUES_1(Nil);
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
    RESTORE_STACK();
    return result;
}

static Object Kconnection_bleeding;  /* :connection-bleeding */

static Object Qdraw_blocks_and_connections_being_moved;  /* draw-blocks-and-connections-being-moved */

/* UPDATE-IMAGES-OF-BLOCKS-AND-CONNECTIONS-BEING-MOVED */
Object update_images_of_blocks_and_connections_being_moved(erase_qm,
	    workspace_enclosing_drawing,blocks,connections)
    Object erase_qm, workspace_enclosing_drawing, blocks, connections;
{
    Object first_block, current_drawing_transfer_mode;
    Object update_images_in_xor_overlay_p, bleeding_hack, extreme_left_edge;
    Object extreme_top_edge, extreme_right_edge, extreme_bottom_edge;
    Declare_special(2);
    Object result;

    x_note_fn_call(128,77);
    first_block = FIRST(blocks);
    current_drawing_transfer_mode = (SI_Long)0L != 
	    (IFIX(ISVREF(first_block,(SI_Long)5L)) & (SI_Long)1024L) ? 
	    Kxor : Current_drawing_transfer_mode;
    PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
	    1);
      update_images_in_xor_overlay_p = T;
      PUSH_SPECIAL_WITH_SYMBOL(Update_images_in_xor_overlay_p,Qupdate_images_in_xor_overlay_p,update_images_in_xor_overlay_p,
	      0);
	bleeding_hack = connections ? Kconnection_bleeding : Nil;
	result = determine_extreme_edges_of_blocks_and_connections(blocks,
		connections,Nil);
	MVS_4(result,extreme_left_edge,extreme_top_edge,extreme_right_edge,
		extreme_bottom_edge);
	result = update_images(11,erase_qm,first_block,
		workspace_enclosing_drawing,extreme_left_edge,
		extreme_top_edge,extreme_right_edge,extreme_bottom_edge,
		bleeding_hack,Qdraw_blocks_and_connections_being_moved,
		blocks,connections);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* DRAW-BLOCKS-AND-CONNECTIONS-BEING-MOVED */
Object draw_blocks_and_connections_being_moved(objects_being_dragged,
	    external_connections_to_drag)
    Object objects_being_dragged, external_connections_to_drag;
{
    Object block, transfer_mode, current_drawing_transfer_mode, ab_loop_list_;
    Object connection;
    char temp, already_in_synch;
    Declare_stack_pointer;
    Declare_special(1);
    Object result;

    x_note_fn_call(128,78);
    SAVE_STACK();
    if (objects_being_dragged) {
	block = FIRST(objects_being_dragged);
	temp = (SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
		(SI_Long)1024L);
    }
    else
	temp = TRUEP(Nil);
    transfer_mode = temp ? Kxor : Current_drawing_transfer_mode;
    already_in_synch = EQL(Current_drawing_transfer_mode,transfer_mode);
    current_drawing_transfer_mode = Current_drawing_transfer_mode;
    PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
	    0);
      if ( !already_in_synch) {
	  Current_drawing_transfer_mode = transfer_mode;
	  synchronize_transfer_mode();
      }
      block = Nil;
      ab_loop_list_ = objects_being_dragged;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      block = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      draw_block_possibly_with_frame(block,T);
      goto next_loop;
    end_loop:;
      connection = Nil;
      ab_loop_list_ = external_connections_to_drag;
    next_loop_1:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop_1;
      connection = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      if (memq_function(ISVREF(connection,(SI_Long)2L),objects_being_dragged))
	  draw_connection(connection,Nil);
      goto next_loop_1;
    end_loop_1:
      SAVE_VALUES(VALUES_1(Qnil));
    POP_SPECIAL();
    if ( !already_in_synch)
	synchronize_transfer_mode();
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* ADD-IMAGE-PLANE-CURSOR */
Object add_image_plane_cursor(image_plane,cursor)
    Object image_plane, cursor;
{
    Object graphics_push_modify_macro_arg, car_1, cdr_1, svref_new_value;

    x_note_fn_call(128,79);
    if ( !TRUEP(memq_function(cursor,ISVREF(image_plane,(SI_Long)27L)))) {
	graphics_push_modify_macro_arg = cursor;
	car_1 = graphics_push_modify_macro_arg;
	cdr_1 = ISVREF(image_plane,(SI_Long)27L);
	svref_new_value = graphics_cons_1(car_1,cdr_1);
	return VALUES_1(SVREF(image_plane,FIX((SI_Long)27L)) = 
		svref_new_value);
    }
    else
	return VALUES_1(Nil);
}

/* REMOVE-IMAGE-PLANE-CURSOR */
Object remove_image_plane_cursor(image_plane,cursor)
    Object image_plane, cursor;
{
    Object svref_new_value;

    x_note_fn_call(128,80);
    svref_new_value = delete_graphics_element_1(cursor,ISVREF(image_plane,
	    (SI_Long)27L));
    return VALUES_1(SVREF(image_plane,FIX((SI_Long)27L)) = svref_new_value);
}

/* CLEAN-UP-IMAGE-PLANE-CURSOR */
Object clean_up_image_plane_cursor(image_plane,cursor,
	    image_plane_serial_number)
    Object image_plane, cursor, image_plane_serial_number;
{
    x_note_fn_call(128,81);
    if (FIXNUM_EQ(ISVREF(image_plane,(SI_Long)1L),
	    image_plane_serial_number) && memq_function(cursor,
	    ISVREF(image_plane,(SI_Long)27L))) {
	draw_image_plane_cursor(image_plane,cursor);
	remove_image_plane_cursor(image_plane,cursor);
	return reclaim_image_plane_cursor(cursor);
    }
    else
	return VALUES_1(Nil);
}

/* ADD-IMAGE-PLANE-CURSORS-TO-CURRENT-WINDOW */
Object add_image_plane_cursors_to_current_window()
{
    Object c, left_edge_of_draw_area, top_edge_of_draw_area;
    Object right_edge_of_draw_area, bottom_edge_of_draw_area, temp;
    Object current_frame_transform_qm, current_image_x_scale;
    Object current_image_y_scale, current_x_origin_of_drawing;
    Object current_y_origin_of_drawing, cursor, ab_loop_list_;
    Declare_special(13);
    Object result;

    x_note_fn_call(128,82);
    c = Current_image_plane;
    if (ISVREF(c,(SI_Long)27L)) {
	left_edge_of_draw_area = Left_edge_of_draw_area;
	top_edge_of_draw_area = Top_edge_of_draw_area;
	right_edge_of_draw_area = Right_edge_of_draw_area;
	bottom_edge_of_draw_area = Bottom_edge_of_draw_area;
	PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
		12);
	  PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
		  11);
	    PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
		    10);
	      PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
		      9);
		temp = ISVREF(c,(SI_Long)6L);
		Left_edge_of_draw_area = FIXNUM_MAX(temp,
			Left_edge_of_draw_area);
		temp = ISVREF(c,(SI_Long)7L);
		Top_edge_of_draw_area = FIXNUM_MAX(temp,Top_edge_of_draw_area);
		temp = ISVREF(c,(SI_Long)8L);
		Right_edge_of_draw_area = FIXNUM_MIN(temp,
			Right_edge_of_draw_area);
		temp = ISVREF(c,(SI_Long)9L);
		Bottom_edge_of_draw_area = FIXNUM_MIN(temp,
			Bottom_edge_of_draw_area);
		if (FIXNUM_LT(Left_edge_of_draw_area,
			Right_edge_of_draw_area) && 
			FIXNUM_LT(Top_edge_of_draw_area,
			Bottom_edge_of_draw_area)) {
		    left_edge_of_draw_area = Left_edge_of_draw_area;
		    top_edge_of_draw_area = Top_edge_of_draw_area;
		    right_edge_of_draw_area = Right_edge_of_draw_area;
		    bottom_edge_of_draw_area = Bottom_edge_of_draw_area;
		    PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
			    8);
		      PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
			      7);
			PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
				6);
			  PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
				  5);
			    temp = ISVREF(c,(SI_Long)19L);
			    Left_edge_of_draw_area = FIXNUM_MAX(temp,
				    Left_edge_of_draw_area);
			    temp = ISVREF(c,(SI_Long)20L);
			    Top_edge_of_draw_area = FIXNUM_MAX(temp,
				    Top_edge_of_draw_area);
			    temp = ISVREF(c,(SI_Long)21L);
			    Right_edge_of_draw_area = FIXNUM_MIN(temp,
				    Right_edge_of_draw_area);
			    temp = ISVREF(c,(SI_Long)22L);
			    Bottom_edge_of_draw_area = FIXNUM_MIN(temp,
				    Bottom_edge_of_draw_area);
			    if (FIXNUM_LT(Left_edge_of_draw_area,
				    Right_edge_of_draw_area) && 
				    FIXNUM_LT(Top_edge_of_draw_area,
				    Bottom_edge_of_draw_area)) {
				current_frame_transform_qm = Nil;
				current_image_x_scale = ISVREF(c,(SI_Long)11L);
				current_image_y_scale = ISVREF(c,(SI_Long)12L);
				current_x_origin_of_drawing = ISVREF(c,
					(SI_Long)13L);
				current_y_origin_of_drawing = ISVREF(c,
					(SI_Long)14L);
				PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
					4);
				  PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
					  3);
				    PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
					    2);
				      PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
					      1);
					PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
						0);
					  cursor = Nil;
					  ab_loop_list_ = ISVREF(c,
						  (SI_Long)27L);
					next_loop:
					  if ( !TRUEP(ab_loop_list_))
					      goto end_loop;
					  cursor = M_CAR(ab_loop_list_);
					  ab_loop_list_ = M_CDR(ab_loop_list_);
					  draw_image_plane_cursor_1(cursor);
					  goto next_loop;
					end_loop:
					  result = VALUES_1(Qnil);
					POP_SPECIAL();
				      POP_SPECIAL();
				    POP_SPECIAL();
				  POP_SPECIAL();
				POP_SPECIAL();
			    }
			    else
				result = VALUES_1(Nil);
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		}
		else
		    result = VALUES_1(Nil);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* DRAW-IMAGE-PLANE-CURSOR-1 */
Object draw_image_plane_cursor_1(cursor)
    Object cursor;
{
    x_note_fn_call(128,83);
    if (SIMPLE_VECTOR_P(cursor) && EQ(ISVREF(cursor,(SI_Long)0L),
	    Qg2_defstruct_structure_name_dragging_state_g2_struct))
	return draw_block_or_blocks_in_dragging_state(cursor,ISVREF(cursor,
		(SI_Long)3L));
    else if (resize_cursor_p(cursor))
	return draw_resize_cursor(cursor);
    else if (selection_rectangle_cursor_p(cursor))
	return draw_selection_rectangle_cursor(cursor);
    else if (selection_highlight_cursor_p(cursor))
	return draw_selection_highlight(cursor);
    else
	return VALUES_1(Nil);
}

/* DRAW-IMAGE-PLANE-CURSOR */
Object draw_image_plane_cursor(image_plane,cursor)
    Object image_plane, cursor;
{
    Object gensym_window, left_edge_of_draw_area, top_edge_of_draw_area;
    Object right_edge_of_draw_area, bottom_edge_of_draw_area;
    Object current_image_x_scale, current_image_y_scale;
    Object current_x_origin_of_drawing, current_y_origin_of_drawing;
    Object current_window_1, drawing_on_window, current_drawing_transfer_mode;
    Object type_of_current_window, current_native_window_qm, current_color_map;
    Object temp, current_background_color_value;
    Object current_foreground_color_value, defer_notifications_qm;
    Object current_pane, current_image_plane;
    Object loose_left_edge_of_visible_workspace_area;
    Object loose_top_edge_of_visible_workspace_area;
    Object loose_right_edge_of_visible_workspace_area;
    Object loose_bottom_edge_of_visible_workspace_area, color_or_metacolor;
    Object background_color_or_metacolor, outer_native_image_plane;
    Object current_native_image_plane, color_value, old_color_value;
    Object current_frame_transform_qm, icp_output_port_qm, icp_socket_qm;
    Object i_am_alive_info_qm, icp_output_port_qm_1, current_icp_port;
    Object current_icp_socket, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, aref_arg_1;
    char already_in_synch, temp_1;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_stack_pointer;
    Declare_catch(3);
    Declare_special(54);
    Object result;

    x_note_fn_call(128,84);
    SAVE_STACK();
    gensym_window = ISVREF(ISVREF(image_plane,(SI_Long)2L),(SI_Long)2L);
    left_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)7L);
    top_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)8L);
    right_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)9L);
    bottom_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)10L);
    PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
	    53);
      PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
	      52);
	PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
		51);
	  PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
		  50);
	    current_image_x_scale = FIX((SI_Long)4096L);
	    current_image_y_scale = FIX((SI_Long)4096L);
	    current_x_origin_of_drawing = FIX((SI_Long)0L);
	    current_y_origin_of_drawing = FIX((SI_Long)0L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
		    49);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
		      48);
		PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
			47);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
			  46);
		    LOCK(On_window_without_drawing);
		    if (PUSH_UNWIND_PROTECT(2)) {
			current_window_1 = ISVREF(ISVREF(image_plane,
				(SI_Long)2L),(SI_Long)2L);
			PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
				45);
			  drawing_on_window = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Drawing_on_window,Qdrawing_on_window,drawing_on_window,
				  44);
			    current_drawing_transfer_mode = 
				    EQ(Current_drawing_transfer_mode,Kxor) 
				    ? Current_drawing_transfer_mode : 
				    ISVREF(Current_window,(SI_Long)30L);
			    PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
				    43);
			      type_of_current_window = 
				      ISVREF(Current_window,(SI_Long)1L);
			      PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
				      42);
				current_native_window_qm = 
					ISVREF(Current_window,(SI_Long)17L);
				PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
					41);
				  current_color_map = 
					  ISVREF(Current_window,(SI_Long)20L);
				  PUSH_SPECIAL_WITH_SYMBOL(Current_color_map,Qcurrent_color_map,current_color_map,
					  40);
				    temp = ISVREF(Current_color_map,
					    (SI_Long)5L);
				    if (temp);
				    else
					temp = map_to_color_value_1(Qwhite);
				    current_background_color_value = temp;
				    PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
					    39);
				      temp = ISVREF(Current_color_map,
					      (SI_Long)4L);
				      if (temp);
				      else
					  temp = map_to_color_value_1(Qblack);
				      current_foreground_color_value = temp;
				      PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
					      38);
					defer_notifications_qm = T;
					PUSH_SPECIAL_WITH_SYMBOL(Defer_notifications_qm,Qdefer_notifications_qm,defer_notifications_qm,
						37);
					  LOCK(On_window_with_drawing);
					  if (PUSH_UNWIND_PROTECT(1)) {
					      drawing_on_window = T;
					      PUSH_SPECIAL_WITH_SYMBOL(Drawing_on_window,Qdrawing_on_window,drawing_on_window,
						      36);
						if (EQ(Type_of_current_window,
							Qx11_window)) {
						    LOCK(For_image_plane);
						    if (PUSH_UNWIND_PROTECT(0)) 
								{
							current_pane = 
								ISVREF(image_plane,
								(SI_Long)2L);
							current_image_plane 
								= image_plane;
							loose_left_edge_of_visible_workspace_area 
								= 
								ISVREF(image_plane,
								(SI_Long)23L);
							loose_top_edge_of_visible_workspace_area 
								= 
								ISVREF(image_plane,
								(SI_Long)24L);
							loose_right_edge_of_visible_workspace_area 
								= 
								ISVREF(image_plane,
								(SI_Long)25L);
							loose_bottom_edge_of_visible_workspace_area 
								= 
								ISVREF(image_plane,
								(SI_Long)26L);
							color_or_metacolor 
								= 
								ISVREF(image_plane,
								(SI_Long)5L) 
								? 
								ISVREF(ISVREF(image_plane,
								(SI_Long)5L),
								(SI_Long)22L) 
								: Nil;
							if (color_or_metacolor);
							else
							    color_or_metacolor 
								    = Qblack;
							if (EQ(color_or_metacolor,
								Qtransparent) 
								|| 
								EQ(color_or_metacolor,
								Qbackground)) {
							    background_color_or_metacolor 
								    = 
								    ISVREF(image_plane,
								    (SI_Long)5L) 
								    ? 
								    ISVREF(ISVREF(image_plane,
								    (SI_Long)5L),
								    (SI_Long)21L) 
								    : Nil;
							    if (background_color_or_metacolor);
							    else
								background_color_or_metacolor 
									= 
									Qwhite;
							    if (EQ(background_color_or_metacolor,
								    Qforeground) 
								    || 
								    EQ(background_color_or_metacolor,
								    Qworkspace_foreground)) 
									{
								temp = 
									ISVREF(Current_color_map,
									(SI_Long)4L);
								if (temp);
								else
								    temp = 
									    map_to_color_value_1(Qblack);
								current_foreground_color_value 
									= temp;
							    }
							    else if (EQ(background_color_or_metacolor,
								    Qtransparent) 
								    || 
								    EQ(background_color_or_metacolor,
								    Qbackground)) 
									{
								temp = 
									ISVREF(Current_color_map,
									(SI_Long)5L);
								if (temp);
								else
								    temp = 
									    map_to_color_value_1(Qwhite);
								current_foreground_color_value 
									= temp;
							    }
							    else
								current_foreground_color_value 
									= 
									EQ(background_color_or_metacolor,
									ISVREF(Current_color_map,
									(SI_Long)6L)) 
									? 
									ISVREF(Current_color_map,
									(SI_Long)7L) 
									: 
									map_to_color_value_1(background_color_or_metacolor);
							}
							else if (EQ(color_or_metacolor,
								Qforeground) 
								|| 
								EQ(color_or_metacolor,
								Qworkspace_foreground)) 
								    {
							    temp = 
								    ISVREF(Current_color_map,
								    (SI_Long)4L);
							    if (temp);
							    else
								temp = 
									map_to_color_value_1(Qblack);
							    current_foreground_color_value 
								    = temp;
							}
							else
							    current_foreground_color_value 
								    = 
								    EQ(color_or_metacolor,
								    ISVREF(Current_color_map,
								    (SI_Long)6L)) 
								    ? 
								    ISVREF(Current_color_map,
								    (SI_Long)7L) 
								    : 
								    map_to_color_value_1(color_or_metacolor);
							PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
								23);
							  PUSH_SPECIAL_WITH_SYMBOL(Loose_bottom_edge_of_visible_workspace_area,Qloose_bottom_edge_of_visible_workspace_area,loose_bottom_edge_of_visible_workspace_area,
								  22);
							    PUSH_SPECIAL_WITH_SYMBOL(Loose_right_edge_of_visible_workspace_area,Qloose_right_edge_of_visible_workspace_area,loose_right_edge_of_visible_workspace_area,
								    21);
							      PUSH_SPECIAL_WITH_SYMBOL(Loose_top_edge_of_visible_workspace_area,Qloose_top_edge_of_visible_workspace_area,loose_top_edge_of_visible_workspace_area,
								      20);
								PUSH_SPECIAL_WITH_SYMBOL(Loose_left_edge_of_visible_workspace_area,Qloose_left_edge_of_visible_workspace_area,loose_left_edge_of_visible_workspace_area,
									19);
								  PUSH_SPECIAL_WITH_SYMBOL(Current_image_plane,Qcurrent_image_plane,current_image_plane,
									  18);
								    PUSH_SPECIAL_WITH_SYMBOL(Current_pane,Qcurrent_pane,current_pane,
									    17);
								      outer_native_image_plane 
									      = 
									      Current_native_image_plane;
								      PUSH_SPECIAL_WITH_SYMBOL(Outer_native_image_plane,Qouter_native_image_plane,outer_native_image_plane,
									      16);
									current_native_image_plane 
										= 
										image_plane;
									PUSH_SPECIAL_WITH_SYMBOL(Current_native_image_plane,Qcurrent_native_image_plane,current_native_image_plane,
										15);
									  if ( 
										  !EQ(Outer_native_image_plane,
										  Current_native_image_plane))
									      nip_begin_drawing(Current_native_image_plane);
									  color_or_metacolor 
										  = 
										  ISVREF(image_plane,
										  (SI_Long)5L) 
										  ?
										   
										  ISVREF(ISVREF(image_plane,
										  (SI_Long)5L),
										  (SI_Long)21L) 
										  :
										   
										  Nil;
									  if (color_or_metacolor);
									  else
									      color_or_metacolor 
										      = 
										      Qwhite;
									  if (EQ(color_or_metacolor,
										  Qtransparent) 
										  || 
										  EQ(color_or_metacolor,
										  Qbackground)) 
										      {
									      color_value 
										      = 
										      ISVREF(Current_color_map,
										      (SI_Long)5L);
									      if (color_value);
									      else
										  color_value 
											  = 
											  map_to_color_value_1(Qwhite);
									  }
									  else if (EQ(color_or_metacolor,
										  Qforeground) 
										  || 
										  EQ(color_or_metacolor,
										  Qworkspace_foreground)) 
										      {
									      temp 
										      = 
										      ISVREF(image_plane,
										      (SI_Long)5L) 
										      ?
										       
										      ISVREF(ISVREF(image_plane,
										      (SI_Long)5L),
										      (SI_Long)22L) 
										      :
										       
										      Nil;
									      if (temp);
									      else
										  temp 
											  = 
											  Qblack;
									      color_or_metacolor 
										      = 
										      temp;
									      if (EQ(color_or_metacolor,
										      Qtransparent) 
										      || 
										      EQ(color_or_metacolor,
										      Qbackground)) 
											  {
										  background_color_or_metacolor 
											  = 
											  ISVREF(image_plane,
											  (SI_Long)5L) 
											  ?
											   
											  ISVREF(ISVREF(image_plane,
											  (SI_Long)5L),
											  (SI_Long)21L) 
											  :
											   
											  Nil;
										  if (background_color_or_metacolor);
										  else
										      background_color_or_metacolor 
											      = 
											      Qwhite;
										  if (EQ(background_color_or_metacolor,
											  Qforeground) 
											  || 
											  EQ(background_color_or_metacolor,
											  Qworkspace_foreground)) 
											      {
										      color_value 
											      = 
											      ISVREF(Current_color_map,
											      (SI_Long)4L);
										      if (color_value);
										      else
											  color_value 
												  = 
												  map_to_color_value_1(Qblack);
										  }
										  else if (EQ(background_color_or_metacolor,
											  Qtransparent) 
											  || 
											  EQ(background_color_or_metacolor,
											  Qbackground)) 
											      {
										      color_value 
											      = 
											      ISVREF(Current_color_map,
											      (SI_Long)5L);
										      if (color_value);
										      else
											  color_value 
												  = 
												  map_to_color_value_1(Qwhite);
										  }
										  else
										      color_value 
											      = 
											      EQ(background_color_or_metacolor,
											      ISVREF(Current_color_map,
											      (SI_Long)6L)) 
											      ?
											       
											      ISVREF(Current_color_map,
											      (SI_Long)7L) 
											      :
											       
											      map_to_color_value_1(background_color_or_metacolor);
									      }
									      else if (EQ(color_or_metacolor,
										      Qforeground) 
										      || 
										      EQ(color_or_metacolor,
										      Qworkspace_foreground)) 
											  {
										  color_value 
											  = 
											  ISVREF(Current_color_map,
											  (SI_Long)4L);
										  if (color_value);
										  else
										      color_value 
											      = 
											      map_to_color_value_1(Qblack);
									      }
									      else
										  color_value 
											  = 
											  EQ(color_or_metacolor,
											  ISVREF(Current_color_map,
											  (SI_Long)6L)) 
											  ?
											   
											  ISVREF(Current_color_map,
											  (SI_Long)7L) 
											  :
											   
											  map_to_color_value_1(color_or_metacolor);
									  }
									  else
									      color_value 
										      = 
										      EQ(color_or_metacolor,
										      ISVREF(Current_color_map,
										      (SI_Long)6L)) 
										      ?
										       
										      ISVREF(Current_color_map,
										      (SI_Long)7L) 
										      :
										       
										      map_to_color_value_1(color_or_metacolor);
									  old_color_value 
										  = 
										  Current_background_color_value;
									  current_background_color_value 
										  = 
										  Current_background_color_value;
									  PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
										  14);
									    set_current_background_color_value(color_value);
									    left_edge_of_draw_area 
										    = 
										    Left_edge_of_draw_area;
									    top_edge_of_draw_area 
										    = 
										    Top_edge_of_draw_area;
									    right_edge_of_draw_area 
										    = 
										    Right_edge_of_draw_area;
									    bottom_edge_of_draw_area 
										    = 
										    Bottom_edge_of_draw_area;
									    PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
										    13);
									      PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
										      12);
										PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
											11);
										  PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
											  10);
										    temp 
											    = 
											    ISVREF(image_plane,
											    (SI_Long)6L);
										    Left_edge_of_draw_area 
											    = 
											    FIXNUM_MAX(temp,
											    Left_edge_of_draw_area);
										    temp 
											    = 
											    ISVREF(image_plane,
											    (SI_Long)7L);
										    Top_edge_of_draw_area 
											    = 
											    FIXNUM_MAX(temp,
											    Top_edge_of_draw_area);
										    temp 
											    = 
											    ISVREF(image_plane,
											    (SI_Long)8L);
										    Right_edge_of_draw_area 
											    = 
											    FIXNUM_MIN(temp,
											    Right_edge_of_draw_area);
										    temp 
											    = 
											    ISVREF(image_plane,
											    (SI_Long)9L);
										    Bottom_edge_of_draw_area 
											    = 
											    FIXNUM_MIN(temp,
											    Bottom_edge_of_draw_area);
										    if (FIXNUM_LT(Left_edge_of_draw_area,
											    Right_edge_of_draw_area) 
											    && 
											    FIXNUM_LT(Top_edge_of_draw_area,
											    Bottom_edge_of_draw_area)) 
												{
											left_edge_of_draw_area 
												= 
												Left_edge_of_draw_area;
											top_edge_of_draw_area 
												= 
												Top_edge_of_draw_area;
											right_edge_of_draw_area 
												= 
												Right_edge_of_draw_area;
											bottom_edge_of_draw_area 
												= 
												Bottom_edge_of_draw_area;
											PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
												9);
											  PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
												  8);
											    PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
												    7);
											      PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
												      6);
												temp 
													= 
													ISVREF(image_plane,
													(SI_Long)19L);
												Left_edge_of_draw_area 
													= 
													FIXNUM_MAX(temp,
													Left_edge_of_draw_area);
												temp 
													= 
													ISVREF(image_plane,
													(SI_Long)20L);
												Top_edge_of_draw_area 
													= 
													FIXNUM_MAX(temp,
													Top_edge_of_draw_area);
												temp 
													= 
													ISVREF(image_plane,
													(SI_Long)21L);
												Right_edge_of_draw_area 
													= 
													FIXNUM_MIN(temp,
													Right_edge_of_draw_area);
												temp 
													= 
													ISVREF(image_plane,
													(SI_Long)22L);
												Bottom_edge_of_draw_area 
													= 
													FIXNUM_MIN(temp,
													Bottom_edge_of_draw_area);
												if (FIXNUM_LT(Left_edge_of_draw_area,
													Right_edge_of_draw_area) 
													&& 
													FIXNUM_LT(Top_edge_of_draw_area,
													Bottom_edge_of_draw_area)) 
													    {
												    current_frame_transform_qm 
													    = 
													    Nil;
												    current_image_x_scale 
													    = 
													    ISVREF(image_plane,
													    (SI_Long)11L);
												    current_image_y_scale 
													    = 
													    ISVREF(image_plane,
													    (SI_Long)12L);
												    current_x_origin_of_drawing 
													    = 
													    ISVREF(image_plane,
													    (SI_Long)13L);
												    current_y_origin_of_drawing 
													    = 
													    ISVREF(image_plane,
													    (SI_Long)14L);
												    PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
													    5);
												      PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
													      4);
													PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
														3);
													  PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
														  2);
													    PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
														    1);
													      already_in_synch 
														      = 
														      EQ(Current_drawing_transfer_mode,
														      Kxor);
													      current_drawing_transfer_mode 
														      = 
														      Current_drawing_transfer_mode;
													      PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
														      0);
														if ( 
															!already_in_synch) 
															    {
														    Current_drawing_transfer_mode 
															    = 
															    Kxor;
														    synchronize_transfer_mode();
														}
														draw_image_plane_cursor_1(cursor);
													      POP_SPECIAL();
													      if ( 
														      !already_in_synch)
														  synchronize_transfer_mode();
													    POP_SPECIAL();
													  POP_SPECIAL();
													POP_SPECIAL();
												      POP_SPECIAL();
												    POP_SPECIAL();
												}
											      POP_SPECIAL();
											    POP_SPECIAL();
											  POP_SPECIAL();
											POP_SPECIAL();
										    }
										  POP_SPECIAL();
										POP_SPECIAL();
									      POP_SPECIAL();
									    POP_SPECIAL();
									    set_current_background_color_value(old_color_value);
									  POP_SPECIAL();
									  if ( 
										  !EQ(Outer_native_image_plane,
										  Current_native_image_plane))
									      nip_end_drawing(Current_native_image_plane);
									POP_SPECIAL();
									temp 
										= 
										Current_native_image_plane 
										?
										 
										( 
										!EQ(image_plane,
										Current_native_image_plane) 
										?
										 
										nip_begin_drawing(Current_native_image_plane) 
										:
										 
										Nil) 
										:
										 
										Nil;
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
						    UNLOCK(For_image_plane);
						    CONTINUE_UNWINDING(0);
						    result = RESTORE_VALUES();
						    SAVE_VALUES(VALUES_1(result));
						    if (Flush_graphics_immediately_qm)
							sync_graphics_on_current_window();
						}
						else if (EQ(Type_of_current_window,
							Qicp)) {
						    icp_output_port_qm = 
							    ISVREF(Current_window,
							    (SI_Long)12L);
						    icp_socket_qm = 
							    icp_output_port_qm 
							    ? 
							    ISVREF(icp_output_port_qm,
							    (SI_Long)2L) : 
							    Qnil;
						    if (icp_socket_qm) {
							i_am_alive_info_qm 
								= 
								ISVREF(icp_socket_qm,
								(SI_Long)24L);
							temp_1 =  
								!TRUEP(i_am_alive_info_qm);
							if (temp_1);
							else
							    temp_1 =  
								    !TRUEP(Do_icp_flow_control_qm);
							if (temp_1);
							else
							    temp_1 =  
								    !TRUEP(ISVREF(i_am_alive_info_qm,
								    (SI_Long)2L));
						    }
						    else
							temp_1 = TRUEP(Nil);
						    if (temp_1) {
							icp_output_port_qm_1 
								= 
								ISVREF(Current_window,
								(SI_Long)12L);
							if (icp_output_port_qm_1 
								&& 
								icp_connection_open_p(ISVREF(icp_output_port_qm_1,
								(SI_Long)2L))) 
								    {
							    current_icp_port 
								    = 
								    icp_output_port_qm_1;
							    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
								    35);
							      current_icp_socket 
								      = 
								      ISVREF(Current_icp_port,
								      (SI_Long)2L);
							      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
								      34);
								temp = 
									IFIX(ISVREF(Current_icp_socket,
									(SI_Long)22L)) 
									>= 
									(SI_Long)17L 
									? 
									ISVREF(Current_icp_socket,
									(SI_Long)53L) 
									: Nil;
								if (temp);
								else
								    temp = 
									    EQ(ISVREF(Current_icp_socket,
									    (SI_Long)25L),
									    Qtelewindows) 
									    ?
									     T : Nil;
								disable_resumability 
									= temp;
								PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
									33);
								  number_of_icp_bytes_for_message_series 
									  = 
									  FIX((SI_Long)0L);
								  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
									  32);
								    icp_buffers_for_message_group 
									    = 
									    Nil;
								    PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
									    31);
								      icp_buffer_of_start_of_message_series_qm 
									      = 
									      Nil;
								      PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
									      30);
									icp_byte_position_of_start_of_message_series_qm 
										= 
										Nil;
									PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
										29);
									  number_of_icp_bytes_to_fill_buffer 
										  = 
										  FIX((SI_Long)0L);
									  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
										  28);
									    current_icp_buffer 
										    = 
										    Nil;
									    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
										    27);
									      current_write_icp_byte_position 
										      = 
										      Nil;
									      PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
										      26);
										number_of_icp_bytes_in_message_group 
											= 
											FIX((SI_Long)0L);
										PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
											25);
										  writing_icp_message_group 
											  = 
											  FIXNUM_ADD1(Writing_icp_message_group);
										  PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
											  24);
										    gensymed_symbol 
											    = 
											    Nil;
										    gensymed_symbol_1 
											    = 
											    0.0;
										    gensymed_symbol_2 
											    = 
											    0.0;
										    if (Profiling_enabled_qm) 
												{
											gensymed_symbol 
												= 
												T;
											gensymed_symbol_1 
												= 
												DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
												(SI_Long)2L),
												(SI_Long)0L);
											gensymed_symbol_2 
												= 
												g2ext_unix_time_as_float();
											aref_arg_1 
												= 
												ISVREF(Profiling_enabled_qm,
												(SI_Long)2L);
											DFLOAT_ISASET_1(aref_arg_1,
												(SI_Long)0L,
												gensymed_symbol_2);
										    }
										    if (icp_connection_open_p(Current_icp_socket) 
											    && 
											     
											    !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
												{
											synchronize_icp_on_window_with_drawing(Current_window,
												Left_edge_of_draw_area,
												Top_edge_of_draw_area,
												Right_edge_of_draw_area,
												Bottom_edge_of_draw_area);
											LOCK(For_image_plane);
											if (PUSH_UNWIND_PROTECT(0)) 
												    {
											    current_pane 
												    = 
												    ISVREF(image_plane,
												    (SI_Long)2L);
											    current_image_plane 
												    = 
												    image_plane;
											    loose_left_edge_of_visible_workspace_area 
												    = 
												    ISVREF(image_plane,
												    (SI_Long)23L);
											    loose_top_edge_of_visible_workspace_area 
												    = 
												    ISVREF(image_plane,
												    (SI_Long)24L);
											    loose_right_edge_of_visible_workspace_area 
												    = 
												    ISVREF(image_plane,
												    (SI_Long)25L);
											    loose_bottom_edge_of_visible_workspace_area 
												    = 
												    ISVREF(image_plane,
												    (SI_Long)26L);
											    color_or_metacolor 
												    = 
												    ISVREF(image_plane,
												    (SI_Long)5L) 
												    ?
												     
												    ISVREF(ISVREF(image_plane,
												    (SI_Long)5L),
												    (SI_Long)22L) 
												    :
												     
												    Nil;
											    if (color_or_metacolor);
											    else
												color_or_metacolor 
													= 
													Qblack;
											    if (EQ(color_or_metacolor,
												    Qtransparent) 
												    || 
												    EQ(color_or_metacolor,
												    Qbackground)) 
													{
												background_color_or_metacolor 
													= 
													ISVREF(image_plane,
													(SI_Long)5L) 
													?
													 
													ISVREF(ISVREF(image_plane,
													(SI_Long)5L),
													(SI_Long)21L) 
													:
													 
													Nil;
												if (background_color_or_metacolor);
												else
												    background_color_or_metacolor 
													    = 
													    Qwhite;
												if (EQ(background_color_or_metacolor,
													Qforeground) 
													|| 
													EQ(background_color_or_metacolor,
													Qworkspace_foreground)) 
													    {
												    temp 
													    = 
													    ISVREF(Current_color_map,
													    (SI_Long)4L);
												    if (temp);
												    else
													temp 
														= 
														map_to_color_value_1(Qblack);
												    current_foreground_color_value 
													    = 
													    temp;
												}
												else if (EQ(background_color_or_metacolor,
													Qtransparent) 
													|| 
													EQ(background_color_or_metacolor,
													Qbackground)) 
													    {
												    temp 
													    = 
													    ISVREF(Current_color_map,
													    (SI_Long)5L);
												    if (temp);
												    else
													temp 
														= 
														map_to_color_value_1(Qwhite);
												    current_foreground_color_value 
													    = 
													    temp;
												}
												else
												    current_foreground_color_value 
													    = 
													    EQ(background_color_or_metacolor,
													    ISVREF(Current_color_map,
													    (SI_Long)6L)) 
													    ?
													     
													    ISVREF(Current_color_map,
													    (SI_Long)7L) 
													    :
													     
													    map_to_color_value_1(background_color_or_metacolor);
											    }
											    else if (EQ(color_or_metacolor,
												    Qforeground) 
												    || 
												    EQ(color_or_metacolor,
												    Qworkspace_foreground)) 
													{
												temp 
													= 
													ISVREF(Current_color_map,
													(SI_Long)4L);
												if (temp);
												else
												    temp 
													    = 
													    map_to_color_value_1(Qblack);
												current_foreground_color_value 
													= 
													temp;
											    }
											    else
												current_foreground_color_value 
													= 
													EQ(color_or_metacolor,
													ISVREF(Current_color_map,
													(SI_Long)6L)) 
													?
													 
													ISVREF(Current_color_map,
													(SI_Long)7L) 
													:
													 
													map_to_color_value_1(color_or_metacolor);
											    PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
												    23);
											      PUSH_SPECIAL_WITH_SYMBOL(Loose_bottom_edge_of_visible_workspace_area,Qloose_bottom_edge_of_visible_workspace_area,loose_bottom_edge_of_visible_workspace_area,
												      22);
												PUSH_SPECIAL_WITH_SYMBOL(Loose_right_edge_of_visible_workspace_area,Qloose_right_edge_of_visible_workspace_area,loose_right_edge_of_visible_workspace_area,
													21);
												  PUSH_SPECIAL_WITH_SYMBOL(Loose_top_edge_of_visible_workspace_area,Qloose_top_edge_of_visible_workspace_area,loose_top_edge_of_visible_workspace_area,
													  20);
												    PUSH_SPECIAL_WITH_SYMBOL(Loose_left_edge_of_visible_workspace_area,Qloose_left_edge_of_visible_workspace_area,loose_left_edge_of_visible_workspace_area,
													    19);
												      PUSH_SPECIAL_WITH_SYMBOL(Current_image_plane,Qcurrent_image_plane,current_image_plane,
													      18);
													PUSH_SPECIAL_WITH_SYMBOL(Current_pane,Qcurrent_pane,current_pane,
														17);
													  outer_native_image_plane 
														  = 
														  Current_native_image_plane;
													  PUSH_SPECIAL_WITH_SYMBOL(Outer_native_image_plane,Qouter_native_image_plane,outer_native_image_plane,
														  16);
													    current_native_image_plane 
														    = 
														    image_plane;
													    PUSH_SPECIAL_WITH_SYMBOL(Current_native_image_plane,Qcurrent_native_image_plane,current_native_image_plane,
														    15);
													      if ( 
														      !EQ(Outer_native_image_plane,
														      Current_native_image_plane))
														  nip_begin_drawing(Current_native_image_plane);
													      color_or_metacolor 
														      = 
														      ISVREF(image_plane,
														      (SI_Long)5L) 
														      ?
														       
														      ISVREF(ISVREF(image_plane,
														      (SI_Long)5L),
														      (SI_Long)21L) 
														      :
														       
														      Nil;
													      if (color_or_metacolor);
													      else
														  color_or_metacolor 
															  = 
															  Qwhite;
													      if (EQ(color_or_metacolor,
														      Qtransparent) 
														      || 
														      EQ(color_or_metacolor,
														      Qbackground)) 
															  {
														  color_value 
															  = 
															  ISVREF(Current_color_map,
															  (SI_Long)5L);
														  if (color_value);
														  else
														      color_value 
															      = 
															      map_to_color_value_1(Qwhite);
													      }
													      else if (EQ(color_or_metacolor,
														      Qforeground) 
														      || 
														      EQ(color_or_metacolor,
														      Qworkspace_foreground)) 
															  {
														  temp 
															  = 
															  ISVREF(image_plane,
															  (SI_Long)5L) 
															  ?
															   
															  ISVREF(ISVREF(image_plane,
															  (SI_Long)5L),
															  (SI_Long)22L) 
															  :
															   
															  Nil;
														  if (temp);
														  else
														      temp 
															      = 
															      Qblack;
														  color_or_metacolor 
															  = 
															  temp;
														  if (EQ(color_or_metacolor,
															  Qtransparent) 
															  || 
															  EQ(color_or_metacolor,
															  Qbackground)) 
															      {
														      background_color_or_metacolor 
															      = 
															      ISVREF(image_plane,
															      (SI_Long)5L) 
															      ?
															       
															      ISVREF(ISVREF(image_plane,
															      (SI_Long)5L),
															      (SI_Long)21L) 
															      :
															       
															      Nil;
														      if (background_color_or_metacolor);
														      else
															  background_color_or_metacolor 
																  = 
																  Qwhite;
														      if (EQ(background_color_or_metacolor,
															      Qforeground) 
															      || 
															      EQ(background_color_or_metacolor,
															      Qworkspace_foreground)) 
																  {
															  color_value 
																  = 
																  ISVREF(Current_color_map,
																  (SI_Long)4L);
															  if (color_value);
															  else
															      color_value 
																      = 
																      map_to_color_value_1(Qblack);
														      }
														      else if (EQ(background_color_or_metacolor,
															      Qtransparent) 
															      || 
															      EQ(background_color_or_metacolor,
															      Qbackground)) 
																  {
															  color_value 
																  = 
																  ISVREF(Current_color_map,
																  (SI_Long)5L);
															  if (color_value);
															  else
															      color_value 
																      = 
																      map_to_color_value_1(Qwhite);
														      }
														      else
															  color_value 
																  = 
																  EQ(background_color_or_metacolor,
																  ISVREF(Current_color_map,
																  (SI_Long)6L)) 
																  ?
																   
																  ISVREF(Current_color_map,
																  (SI_Long)7L) 
																  :
																   
																  map_to_color_value_1(background_color_or_metacolor);
														  }
														  else if (EQ(color_or_metacolor,
															  Qforeground) 
															  || 
															  EQ(color_or_metacolor,
															  Qworkspace_foreground)) 
															      {
														      color_value 
															      = 
															      ISVREF(Current_color_map,
															      (SI_Long)4L);
														      if (color_value);
														      else
															  color_value 
																  = 
																  map_to_color_value_1(Qblack);
														  }
														  else
														      color_value 
															      = 
															      EQ(color_or_metacolor,
															      ISVREF(Current_color_map,
															      (SI_Long)6L)) 
															      ?
															       
															      ISVREF(Current_color_map,
															      (SI_Long)7L) 
															      :
															       
															      map_to_color_value_1(color_or_metacolor);
													      }
													      else
														  color_value 
															  = 
															  EQ(color_or_metacolor,
															  ISVREF(Current_color_map,
															  (SI_Long)6L)) 
															  ?
															   
															  ISVREF(Current_color_map,
															  (SI_Long)7L) 
															  :
															   
															  map_to_color_value_1(color_or_metacolor);
													      old_color_value 
														      = 
														      Current_background_color_value;
													      current_background_color_value 
														      = 
														      Current_background_color_value;
													      PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
														      14);
														set_current_background_color_value(color_value);
														left_edge_of_draw_area 
															= 
															Left_edge_of_draw_area;
														top_edge_of_draw_area 
															= 
															Top_edge_of_draw_area;
														right_edge_of_draw_area 
															= 
															Right_edge_of_draw_area;
														bottom_edge_of_draw_area 
															= 
															Bottom_edge_of_draw_area;
														PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
															13);
														  PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
															  12);
														    PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
															    11);
														      PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
															      10);
															temp 
																= 
																ISVREF(image_plane,
																(SI_Long)6L);
															Left_edge_of_draw_area 
																= 
																FIXNUM_MAX(temp,
																Left_edge_of_draw_area);
															temp 
																= 
																ISVREF(image_plane,
																(SI_Long)7L);
															Top_edge_of_draw_area 
																= 
																FIXNUM_MAX(temp,
																Top_edge_of_draw_area);
															temp 
																= 
																ISVREF(image_plane,
																(SI_Long)8L);
															Right_edge_of_draw_area 
																= 
																FIXNUM_MIN(temp,
																Right_edge_of_draw_area);
															temp 
																= 
																ISVREF(image_plane,
																(SI_Long)9L);
															Bottom_edge_of_draw_area 
																= 
																FIXNUM_MIN(temp,
																Bottom_edge_of_draw_area);
															if (FIXNUM_LT(Left_edge_of_draw_area,
																Right_edge_of_draw_area) 
																&& 
																FIXNUM_LT(Top_edge_of_draw_area,
																Bottom_edge_of_draw_area)) 
																    {
															    left_edge_of_draw_area 
																    = 
																    Left_edge_of_draw_area;
															    top_edge_of_draw_area 
																    = 
																    Top_edge_of_draw_area;
															    right_edge_of_draw_area 
																    = 
																    Right_edge_of_draw_area;
															    bottom_edge_of_draw_area 
																    = 
																    Bottom_edge_of_draw_area;
															    PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
																    9);
															      PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
																      8);
																PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
																	7);
																  PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
																	  6);
																    temp 
																	    = 
																	    ISVREF(image_plane,
																	    (SI_Long)19L);
																    Left_edge_of_draw_area 
																	    = 
																	    FIXNUM_MAX(temp,
																	    Left_edge_of_draw_area);
																    temp 
																	    = 
																	    ISVREF(image_plane,
																	    (SI_Long)20L);
																    Top_edge_of_draw_area 
																	    = 
																	    FIXNUM_MAX(temp,
																	    Top_edge_of_draw_area);
																    temp 
																	    = 
																	    ISVREF(image_plane,
																	    (SI_Long)21L);
																    Right_edge_of_draw_area 
																	    = 
																	    FIXNUM_MIN(temp,
																	    Right_edge_of_draw_area);
																    temp 
																	    = 
																	    ISVREF(image_plane,
																	    (SI_Long)22L);
																    Bottom_edge_of_draw_area 
																	    = 
																	    FIXNUM_MIN(temp,
																	    Bottom_edge_of_draw_area);
																    if (FIXNUM_LT(Left_edge_of_draw_area,
																	    Right_edge_of_draw_area) 
																	    && 
																	    FIXNUM_LT(Top_edge_of_draw_area,
																	    Bottom_edge_of_draw_area)) 
																		{
																	current_frame_transform_qm 
																		= 
																		Nil;
																	current_image_x_scale 
																		= 
																		ISVREF(image_plane,
																		(SI_Long)11L);
																	current_image_y_scale 
																		= 
																		ISVREF(image_plane,
																		(SI_Long)12L);
																	current_x_origin_of_drawing 
																		= 
																		ISVREF(image_plane,
																		(SI_Long)13L);
																	current_y_origin_of_drawing 
																		= 
																		ISVREF(image_plane,
																		(SI_Long)14L);
																	PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
																		5);
																	  PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
																		  4);
																	    PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
																		    3);
																	      PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
																		      2);
																		PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
																			1);
																		  already_in_synch 
																			  = 
																			  EQ(Current_drawing_transfer_mode,
																			  Kxor);
																		  current_drawing_transfer_mode 
																			  = 
																			  Current_drawing_transfer_mode;
																		  PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
																			  0);
																		    if ( 
																			    !already_in_synch) 
																				{
																			Current_drawing_transfer_mode 
																				= 
																				Kxor;
																			synchronize_transfer_mode();
																		    }
																		    draw_image_plane_cursor_1(cursor);
																		  POP_SPECIAL();
																		  if ( 
																			  !already_in_synch)
																		      synchronize_transfer_mode();
																		POP_SPECIAL();
																	      POP_SPECIAL();
																	    POP_SPECIAL();
																	  POP_SPECIAL();
																	POP_SPECIAL();
																    }
																  POP_SPECIAL();
																POP_SPECIAL();
															      POP_SPECIAL();
															    POP_SPECIAL();
															}
														      POP_SPECIAL();
														    POP_SPECIAL();
														  POP_SPECIAL();
														POP_SPECIAL();
														set_current_background_color_value(old_color_value);
													      POP_SPECIAL();
													      if ( 
														      !EQ(Outer_native_image_plane,
														      Current_native_image_plane))
														  nip_end_drawing(Current_native_image_plane);
													    POP_SPECIAL();
													    temp 
														    = 
														    Current_native_image_plane 
														    ?
														     
														    ( 
														    !EQ(image_plane,
														    Current_native_image_plane) 
														    ?
														     
														    nip_begin_drawing(Current_native_image_plane) 
														    :
														     
														    Nil) 
														    :
														     
														    Nil;
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
											UNLOCK(For_image_plane);
											CONTINUE_UNWINDING(0);
											result = RESTORE_VALUES();
											temp 
												= 
												result;
											if (Flush_graphics_immediately_qm 
												&& 
												FIXNUM_NE(ISVREF(Current_icp_socket,
												(SI_Long)15L),
												Icp_connection_closed))
											    sync_graphics_on_current_window();
											end_icp_message_group();
										    }
										    else
											temp 
												= 
												Nil;
										    SAVE_VALUES(VALUES_1(temp));
										    if (Profiling_enabled_qm) 
												{
											gensymed_symbol_3 
												= 
												g2ext_unix_time_as_float();
											gensymed_symbol_4 
												= 
												DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
												(SI_Long)2L),
												(SI_Long)0L);
											gensymed_symbol_5 
												= 
												gensymed_symbol_3 
												- 
												gensymed_symbol_4;
											aref_arg_1 
												= 
												ISVREF(Profiling_enabled_qm,
												(SI_Long)6L);
											aref_new_value 
												= 
												gensymed_symbol_5 
												+ 
												DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
												(SI_Long)6L),
												(SI_Long)0L);
											DFLOAT_ISASET_1(aref_arg_1,
												(SI_Long)0L,
												aref_new_value);
											aref_arg_1 
												= 
												ISVREF(Profiling_enabled_qm,
												(SI_Long)2L);
											aref_new_value 
												= 
												gensymed_symbol 
												?
												 
												gensymed_symbol_1 
												+ 
												gensymed_symbol_5 
												+ 
												(gensymed_symbol_4 
												- 
												gensymed_symbol_2) 
												:
												 
												gensymed_symbol_3;
											DFLOAT_ISASET_1(aref_arg_1,
												(SI_Long)0L,
												aref_new_value);
										    }
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
							else
							    SAVE_VALUES(VALUES_1(Nil));
						    }
						    else
							SAVE_VALUES(VALUES_1(Nil));
						}
						else if (EQ(Type_of_current_window,
							Qprinter)) {
						    LOCK(For_image_plane);
						    if (PUSH_UNWIND_PROTECT(0)) 
								{
							current_pane = 
								ISVREF(image_plane,
								(SI_Long)2L);
							current_image_plane 
								= image_plane;
							loose_left_edge_of_visible_workspace_area 
								= 
								ISVREF(image_plane,
								(SI_Long)23L);
							loose_top_edge_of_visible_workspace_area 
								= 
								ISVREF(image_plane,
								(SI_Long)24L);
							loose_right_edge_of_visible_workspace_area 
								= 
								ISVREF(image_plane,
								(SI_Long)25L);
							loose_bottom_edge_of_visible_workspace_area 
								= 
								ISVREF(image_plane,
								(SI_Long)26L);
							color_or_metacolor 
								= 
								ISVREF(image_plane,
								(SI_Long)5L) 
								? 
								ISVREF(ISVREF(image_plane,
								(SI_Long)5L),
								(SI_Long)22L) 
								: Nil;
							if (color_or_metacolor);
							else
							    color_or_metacolor 
								    = Qblack;
							if (EQ(color_or_metacolor,
								Qtransparent) 
								|| 
								EQ(color_or_metacolor,
								Qbackground)) {
							    background_color_or_metacolor 
								    = 
								    ISVREF(image_plane,
								    (SI_Long)5L) 
								    ? 
								    ISVREF(ISVREF(image_plane,
								    (SI_Long)5L),
								    (SI_Long)21L) 
								    : Nil;
							    if (background_color_or_metacolor);
							    else
								background_color_or_metacolor 
									= 
									Qwhite;
							    if (EQ(background_color_or_metacolor,
								    Qforeground) 
								    || 
								    EQ(background_color_or_metacolor,
								    Qworkspace_foreground)) 
									{
								temp = 
									ISVREF(Current_color_map,
									(SI_Long)4L);
								if (temp);
								else
								    temp = 
									    map_to_color_value_1(Qblack);
								current_foreground_color_value 
									= temp;
							    }
							    else if (EQ(background_color_or_metacolor,
								    Qtransparent) 
								    || 
								    EQ(background_color_or_metacolor,
								    Qbackground)) 
									{
								temp = 
									ISVREF(Current_color_map,
									(SI_Long)5L);
								if (temp);
								else
								    temp = 
									    map_to_color_value_1(Qwhite);
								current_foreground_color_value 
									= temp;
							    }
							    else
								current_foreground_color_value 
									= 
									EQ(background_color_or_metacolor,
									ISVREF(Current_color_map,
									(SI_Long)6L)) 
									? 
									ISVREF(Current_color_map,
									(SI_Long)7L) 
									: 
									map_to_color_value_1(background_color_or_metacolor);
							}
							else if (EQ(color_or_metacolor,
								Qforeground) 
								|| 
								EQ(color_or_metacolor,
								Qworkspace_foreground)) 
								    {
							    temp = 
								    ISVREF(Current_color_map,
								    (SI_Long)4L);
							    if (temp);
							    else
								temp = 
									map_to_color_value_1(Qblack);
							    current_foreground_color_value 
								    = temp;
							}
							else
							    current_foreground_color_value 
								    = 
								    EQ(color_or_metacolor,
								    ISVREF(Current_color_map,
								    (SI_Long)6L)) 
								    ? 
								    ISVREF(Current_color_map,
								    (SI_Long)7L) 
								    : 
								    map_to_color_value_1(color_or_metacolor);
							PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
								23);
							  PUSH_SPECIAL_WITH_SYMBOL(Loose_bottom_edge_of_visible_workspace_area,Qloose_bottom_edge_of_visible_workspace_area,loose_bottom_edge_of_visible_workspace_area,
								  22);
							    PUSH_SPECIAL_WITH_SYMBOL(Loose_right_edge_of_visible_workspace_area,Qloose_right_edge_of_visible_workspace_area,loose_right_edge_of_visible_workspace_area,
								    21);
							      PUSH_SPECIAL_WITH_SYMBOL(Loose_top_edge_of_visible_workspace_area,Qloose_top_edge_of_visible_workspace_area,loose_top_edge_of_visible_workspace_area,
								      20);
								PUSH_SPECIAL_WITH_SYMBOL(Loose_left_edge_of_visible_workspace_area,Qloose_left_edge_of_visible_workspace_area,loose_left_edge_of_visible_workspace_area,
									19);
								  PUSH_SPECIAL_WITH_SYMBOL(Current_image_plane,Qcurrent_image_plane,current_image_plane,
									  18);
								    PUSH_SPECIAL_WITH_SYMBOL(Current_pane,Qcurrent_pane,current_pane,
									    17);
								      outer_native_image_plane 
									      = 
									      Current_native_image_plane;
								      PUSH_SPECIAL_WITH_SYMBOL(Outer_native_image_plane,Qouter_native_image_plane,outer_native_image_plane,
									      16);
									current_native_image_plane 
										= 
										image_plane;
									PUSH_SPECIAL_WITH_SYMBOL(Current_native_image_plane,Qcurrent_native_image_plane,current_native_image_plane,
										15);
									  if ( 
										  !EQ(Outer_native_image_plane,
										  Current_native_image_plane))
									      nip_begin_drawing(Current_native_image_plane);
									  color_or_metacolor 
										  = 
										  ISVREF(image_plane,
										  (SI_Long)5L) 
										  ?
										   
										  ISVREF(ISVREF(image_plane,
										  (SI_Long)5L),
										  (SI_Long)21L) 
										  :
										   
										  Nil;
									  if (color_or_metacolor);
									  else
									      color_or_metacolor 
										      = 
										      Qwhite;
									  if (EQ(color_or_metacolor,
										  Qtransparent) 
										  || 
										  EQ(color_or_metacolor,
										  Qbackground)) 
										      {
									      color_value 
										      = 
										      ISVREF(Current_color_map,
										      (SI_Long)5L);
									      if (color_value);
									      else
										  color_value 
											  = 
											  map_to_color_value_1(Qwhite);
									  }
									  else if (EQ(color_or_metacolor,
										  Qforeground) 
										  || 
										  EQ(color_or_metacolor,
										  Qworkspace_foreground)) 
										      {
									      temp 
										      = 
										      ISVREF(image_plane,
										      (SI_Long)5L) 
										      ?
										       
										      ISVREF(ISVREF(image_plane,
										      (SI_Long)5L),
										      (SI_Long)22L) 
										      :
										       
										      Nil;
									      if (temp);
									      else
										  temp 
											  = 
											  Qblack;
									      color_or_metacolor 
										      = 
										      temp;
									      if (EQ(color_or_metacolor,
										      Qtransparent) 
										      || 
										      EQ(color_or_metacolor,
										      Qbackground)) 
											  {
										  background_color_or_metacolor 
											  = 
											  ISVREF(image_plane,
											  (SI_Long)5L) 
											  ?
											   
											  ISVREF(ISVREF(image_plane,
											  (SI_Long)5L),
											  (SI_Long)21L) 
											  :
											   
											  Nil;
										  if (background_color_or_metacolor);
										  else
										      background_color_or_metacolor 
											      = 
											      Qwhite;
										  if (EQ(background_color_or_metacolor,
											  Qforeground) 
											  || 
											  EQ(background_color_or_metacolor,
											  Qworkspace_foreground)) 
											      {
										      color_value 
											      = 
											      ISVREF(Current_color_map,
											      (SI_Long)4L);
										      if (color_value);
										      else
											  color_value 
												  = 
												  map_to_color_value_1(Qblack);
										  }
										  else if (EQ(background_color_or_metacolor,
											  Qtransparent) 
											  || 
											  EQ(background_color_or_metacolor,
											  Qbackground)) 
											      {
										      color_value 
											      = 
											      ISVREF(Current_color_map,
											      (SI_Long)5L);
										      if (color_value);
										      else
											  color_value 
												  = 
												  map_to_color_value_1(Qwhite);
										  }
										  else
										      color_value 
											      = 
											      EQ(background_color_or_metacolor,
											      ISVREF(Current_color_map,
											      (SI_Long)6L)) 
											      ?
											       
											      ISVREF(Current_color_map,
											      (SI_Long)7L) 
											      :
											       
											      map_to_color_value_1(background_color_or_metacolor);
									      }
									      else if (EQ(color_or_metacolor,
										      Qforeground) 
										      || 
										      EQ(color_or_metacolor,
										      Qworkspace_foreground)) 
											  {
										  color_value 
											  = 
											  ISVREF(Current_color_map,
											  (SI_Long)4L);
										  if (color_value);
										  else
										      color_value 
											      = 
											      map_to_color_value_1(Qblack);
									      }
									      else
										  color_value 
											  = 
											  EQ(color_or_metacolor,
											  ISVREF(Current_color_map,
											  (SI_Long)6L)) 
											  ?
											   
											  ISVREF(Current_color_map,
											  (SI_Long)7L) 
											  :
											   
											  map_to_color_value_1(color_or_metacolor);
									  }
									  else
									      color_value 
										      = 
										      EQ(color_or_metacolor,
										      ISVREF(Current_color_map,
										      (SI_Long)6L)) 
										      ?
										       
										      ISVREF(Current_color_map,
										      (SI_Long)7L) 
										      :
										       
										      map_to_color_value_1(color_or_metacolor);
									  old_color_value 
										  = 
										  Current_background_color_value;
									  current_background_color_value 
										  = 
										  Current_background_color_value;
									  PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
										  14);
									    set_current_background_color_value(color_value);
									    left_edge_of_draw_area 
										    = 
										    Left_edge_of_draw_area;
									    top_edge_of_draw_area 
										    = 
										    Top_edge_of_draw_area;
									    right_edge_of_draw_area 
										    = 
										    Right_edge_of_draw_area;
									    bottom_edge_of_draw_area 
										    = 
										    Bottom_edge_of_draw_area;
									    PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
										    13);
									      PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
										      12);
										PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
											11);
										  PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
											  10);
										    temp 
											    = 
											    ISVREF(image_plane,
											    (SI_Long)6L);
										    Left_edge_of_draw_area 
											    = 
											    FIXNUM_MAX(temp,
											    Left_edge_of_draw_area);
										    temp 
											    = 
											    ISVREF(image_plane,
											    (SI_Long)7L);
										    Top_edge_of_draw_area 
											    = 
											    FIXNUM_MAX(temp,
											    Top_edge_of_draw_area);
										    temp 
											    = 
											    ISVREF(image_plane,
											    (SI_Long)8L);
										    Right_edge_of_draw_area 
											    = 
											    FIXNUM_MIN(temp,
											    Right_edge_of_draw_area);
										    temp 
											    = 
											    ISVREF(image_plane,
											    (SI_Long)9L);
										    Bottom_edge_of_draw_area 
											    = 
											    FIXNUM_MIN(temp,
											    Bottom_edge_of_draw_area);
										    if (FIXNUM_LT(Left_edge_of_draw_area,
											    Right_edge_of_draw_area) 
											    && 
											    FIXNUM_LT(Top_edge_of_draw_area,
											    Bottom_edge_of_draw_area)) 
												{
											left_edge_of_draw_area 
												= 
												Left_edge_of_draw_area;
											top_edge_of_draw_area 
												= 
												Top_edge_of_draw_area;
											right_edge_of_draw_area 
												= 
												Right_edge_of_draw_area;
											bottom_edge_of_draw_area 
												= 
												Bottom_edge_of_draw_area;
											PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
												9);
											  PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
												  8);
											    PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
												    7);
											      PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
												      6);
												temp 
													= 
													ISVREF(image_plane,
													(SI_Long)19L);
												Left_edge_of_draw_area 
													= 
													FIXNUM_MAX(temp,
													Left_edge_of_draw_area);
												temp 
													= 
													ISVREF(image_plane,
													(SI_Long)20L);
												Top_edge_of_draw_area 
													= 
													FIXNUM_MAX(temp,
													Top_edge_of_draw_area);
												temp 
													= 
													ISVREF(image_plane,
													(SI_Long)21L);
												Right_edge_of_draw_area 
													= 
													FIXNUM_MIN(temp,
													Right_edge_of_draw_area);
												temp 
													= 
													ISVREF(image_plane,
													(SI_Long)22L);
												Bottom_edge_of_draw_area 
													= 
													FIXNUM_MIN(temp,
													Bottom_edge_of_draw_area);
												if (FIXNUM_LT(Left_edge_of_draw_area,
													Right_edge_of_draw_area) 
													&& 
													FIXNUM_LT(Top_edge_of_draw_area,
													Bottom_edge_of_draw_area)) 
													    {
												    current_frame_transform_qm 
													    = 
													    Nil;
												    current_image_x_scale 
													    = 
													    ISVREF(image_plane,
													    (SI_Long)11L);
												    current_image_y_scale 
													    = 
													    ISVREF(image_plane,
													    (SI_Long)12L);
												    current_x_origin_of_drawing 
													    = 
													    ISVREF(image_plane,
													    (SI_Long)13L);
												    current_y_origin_of_drawing 
													    = 
													    ISVREF(image_plane,
													    (SI_Long)14L);
												    PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
													    5);
												      PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
													      4);
													PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
														3);
													  PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
														  2);
													    PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
														    1);
													      already_in_synch 
														      = 
														      EQ(Current_drawing_transfer_mode,
														      Kxor);
													      current_drawing_transfer_mode 
														      = 
														      Current_drawing_transfer_mode;
													      PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
														      0);
														if ( 
															!already_in_synch) 
															    {
														    Current_drawing_transfer_mode 
															    = 
															    Kxor;
														    synchronize_transfer_mode();
														}
														draw_image_plane_cursor_1(cursor);
													      POP_SPECIAL();
													      if ( 
														      !already_in_synch)
														  synchronize_transfer_mode();
													    POP_SPECIAL();
													  POP_SPECIAL();
													POP_SPECIAL();
												      POP_SPECIAL();
												    POP_SPECIAL();
												}
											      POP_SPECIAL();
											    POP_SPECIAL();
											  POP_SPECIAL();
											POP_SPECIAL();
										    }
										  POP_SPECIAL();
										POP_SPECIAL();
									      POP_SPECIAL();
									    POP_SPECIAL();
									    set_current_background_color_value(old_color_value);
									  POP_SPECIAL();
									  if ( 
										  !EQ(Outer_native_image_plane,
										  Current_native_image_plane))
									      nip_end_drawing(Current_native_image_plane);
									POP_SPECIAL();
									if (Current_native_image_plane) 
										    {
									    if ( 
										    !EQ(image_plane,
										    Current_native_image_plane))
										SAVE_VALUES(nip_begin_drawing(Current_native_image_plane));
									    else
										SAVE_VALUES(VALUES_1(Nil));
									}
									else
									    SAVE_VALUES(VALUES_1(Nil));
								      POP_SPECIAL();
								    POP_SPECIAL();
								  POP_SPECIAL();
								POP_SPECIAL();
							      POP_SPECIAL();
							    POP_SPECIAL();
							  POP_SPECIAL();
							POP_SPECIAL();
						    }
						    POP_UNWIND_PROTECT(0);
						    UNLOCK(For_image_plane);
						    CONTINUE_UNWINDING(0);
						}
						else
						    SAVE_VALUES(VALUES_1(Qnil));
					      POP_SPECIAL();
					  }
					  POP_UNWIND_PROTECT(1);
					  UNLOCK(On_window_with_drawing);
					  CONTINUE_UNWINDING(1);
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
		    POP_UNWIND_PROTECT(2);
		    UNLOCK(On_window_without_drawing);
		    CONTINUE_UNWINDING(2);
		    result = RESTORE_VALUES();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* RECLAIM-IMAGE-PLANE-CURSOR */
Object reclaim_image_plane_cursor(cursor)
    Object cursor;
{
    x_note_fn_call(128,85);
    if (SIMPLE_VECTOR_P(cursor) && EQ(ISVREF(cursor,(SI_Long)0L),
	    Qg2_defstruct_structure_name_dragging_state_g2_struct))
	return VALUES_1(SVREF(cursor,FIX((SI_Long)5L)) = Nil);
    else if (resize_cursor_p(cursor))
	return reclaim_resize_cursor(cursor);
    else if (selection_rectangle_cursor_p(cursor))
	return reclaim_graphics_list_1(cursor);
    else if (selection_highlight_cursor_p(cursor))
	return reclaim_graphics_list_1(cursor);
    else
	return VALUES_1(Nil);
}

/* RECLAIM-IMAGE-PLANE-CURSORS */
Object reclaim_image_plane_cursors(image_plane_cursors)
    Object image_plane_cursors;
{
    Object cursor, ab_loop_list_;

    x_note_fn_call(128,86);
    cursor = Nil;
    ab_loop_list_ = image_plane_cursors;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    cursor = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_image_plane_cursor(cursor);
    goto next_loop;
  end_loop:;
    return reclaim_graphics_list_1(image_plane_cursors);
}

/* DRAW-BLOCK-OR-BLOCKS-IN-DRAGGING-STATE */
Object draw_block_or_blocks_in_dragging_state(dragging_state,block_or_blocks)
    Object dragging_state, block_or_blocks;
{
    Object current_drawing_transfer_mode, first_block_qm, x_in_window;
    Object y_in_window, x_in_workspace, y_in_workspace, temp, scale, scale_1;
    Object value, temp_2, current_x_origin_of_drawing;
    Object current_y_origin_of_drawing, block, ab_loop_list_;
    SI_Long gensymed_symbol, gensymed_symbol_1, temp_1, value_1;
    SI_Long unshifted_result, gensymed_symbol_2;
    char already_in_synch, temp_3;
    Declare_stack_pointer;
    Declare_special(3);
    Object result;

    x_note_fn_call(128,87);
    SAVE_STACK();
    already_in_synch = EQ(Current_drawing_transfer_mode,Kxor);
    current_drawing_transfer_mode = Current_drawing_transfer_mode;
    PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
	    2);
      if ( !already_in_synch) {
	  Current_drawing_transfer_mode = Kxor;
	  synchronize_transfer_mode();
      }
      first_block_qm = car_or_atom(block_or_blocks);
      if (first_block_qm) {
	  x_in_window = ISVREF(dragging_state,(SI_Long)19L);
	  y_in_window = ISVREF(dragging_state,(SI_Long)20L);
	  x_in_workspace = ISVREF(dragging_state,(SI_Long)17L);
	  y_in_workspace = ISVREF(dragging_state,(SI_Long)18L);
	  if (EQ(ISVREF(Current_image_plane,(SI_Long)5L),
		  ISVREF(dragging_state,(SI_Long)25L))) {
	      temp = FIX((SI_Long)0L);
	      scale = Current_image_x_scale;
	      gensymed_symbol = IFIX(x_in_workspace);
	      scale_1 = Current_image_x_scale;
	      value = FIXNUM_MINUS(x_in_window,Current_x_origin_of_drawing);
	      if (IFIX(scale_1) == (SI_Long)4096L)
		  gensymed_symbol_1 = IFIX(value);
	      else if ( !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		      value) && FIXNUM_LT(value,
		      Isqrt_of_most_positive_fixnum)))
		  gensymed_symbol_1 = IFIX(inverse_scalef_function(scale_1,
			  value));
	      else if (IFIX(value) >= (SI_Long)0L) {
		  temp_1 = ((IFIX(value) << (SI_Long)12L) + (IFIX(scale_1) 
			  >>  -  - (SI_Long)1L)) / IFIX(scale_1);
		  gensymed_symbol_1 = temp_1;
	      }
	      else {
		  temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << (SI_Long)12L) + 
			  (IFIX(scale_1) >>  -  - (SI_Long)1L)) / 
			  IFIX(scale_1);
		  temp_1 = IFIX(FIXNUM_NEGATE(FIX(temp_1)));
		  gensymed_symbol_1 = temp_1;
	      }
	      value_1 = gensymed_symbol - gensymed_symbol_1;
	      if (IFIX(scale) == (SI_Long)4096L)
		  temp_2 = FIX(value_1);
	      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		      scale) && FIXNUM_LT(scale,
		      Isqrt_of_most_positive_fixnum) && 
		      IFIX(Minus_of_isqrt_of_most_positive_fixnum) < 
		      value_1 && value_1 < 
			  IFIX(Isqrt_of_most_positive_fixnum)) {
		  unshifted_result = IFIX(scale) * value_1 + (SI_Long)2048L;
		  temp_2 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	      }
	      else
		  temp_2 = scalef_function(scale,FIX(value_1));
	      temp_3 = NUM_EQ(temp,temp_2);
	  }
	  else
	      temp_3 = TRUEP(Nil);
	  if (temp_3) {
	      temp = FIX((SI_Long)0L);
	      scale = Current_image_y_scale;
	      gensymed_symbol = IFIX(y_in_workspace);
	      scale_1 = Current_image_y_scale;
	      value = FIXNUM_MINUS(y_in_window,Current_y_origin_of_drawing);
	      if (IFIX(scale_1) == (SI_Long)4096L)
		  gensymed_symbol_1 = IFIX(value);
	      else if ( !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		      value) && FIXNUM_LT(value,
		      Isqrt_of_most_positive_fixnum)))
		  gensymed_symbol_1 = IFIX(inverse_scalef_function(scale_1,
			  value));
	      else if (IFIX(value) >= (SI_Long)0L) {
		  temp_1 = ((IFIX(value) << (SI_Long)12L) + (IFIX(scale_1) 
			  >>  -  - (SI_Long)1L)) / IFIX(scale_1);
		  gensymed_symbol_1 = temp_1;
	      }
	      else {
		  temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << (SI_Long)12L) + 
			  (IFIX(scale_1) >>  -  - (SI_Long)1L)) / 
			  IFIX(scale_1);
		  temp_1 = IFIX(FIXNUM_NEGATE(FIX(temp_1)));
		  gensymed_symbol_1 = temp_1;
	      }
	      value_1 = gensymed_symbol - gensymed_symbol_1;
	      if (IFIX(scale) == (SI_Long)4096L)
		  temp_2 = FIX(value_1);
	      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		      scale) && FIXNUM_LT(scale,
		      Isqrt_of_most_positive_fixnum) && 
		      IFIX(Minus_of_isqrt_of_most_positive_fixnum) < 
		      value_1 && value_1 < 
			  IFIX(Isqrt_of_most_positive_fixnum)) {
		  unshifted_result = IFIX(scale) * value_1 + (SI_Long)2048L;
		  temp_2 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	      }
	      else
		  temp_2 = scalef_function(scale,FIX(value_1));
	      temp_3 = NUM_EQ(temp,temp_2);
	  }
	  else
	      temp_3 = TRUEP(Nil);
	  if ( !temp_3) {
	      gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	      scale = Current_image_x_scale;
	      gensymed_symbol_1 = IFIX(x_in_workspace);
	      scale_1 = Current_image_x_scale;
	      value = FIXNUM_MINUS(x_in_window,Current_x_origin_of_drawing);
	      if (IFIX(scale_1) == (SI_Long)4096L)
		  gensymed_symbol_2 = IFIX(value);
	      else if ( !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		      value) && FIXNUM_LT(value,
		      Isqrt_of_most_positive_fixnum)))
		  gensymed_symbol_2 = IFIX(inverse_scalef_function(scale_1,
			  value));
	      else if (IFIX(value) >= (SI_Long)0L) {
		  temp_1 = ((IFIX(value) << (SI_Long)12L) + (IFIX(scale_1) 
			  >>  -  - (SI_Long)1L)) / IFIX(scale_1);
		  gensymed_symbol_2 = temp_1;
	      }
	      else {
		  temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << (SI_Long)12L) + 
			  (IFIX(scale_1) >>  -  - (SI_Long)1L)) / 
			  IFIX(scale_1);
		  temp_1 = IFIX(FIXNUM_NEGATE(FIX(temp_1)));
		  gensymed_symbol_2 = temp_1;
	      }
	      value_1 = gensymed_symbol_1 - gensymed_symbol_2;
	      if (IFIX(scale) == (SI_Long)4096L)
		  gensymed_symbol_1 = value_1;
	      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		      scale) && FIXNUM_LT(scale,
		      Isqrt_of_most_positive_fixnum) && 
		      IFIX(Minus_of_isqrt_of_most_positive_fixnum) < 
		      value_1 && value_1 < 
			  IFIX(Isqrt_of_most_positive_fixnum)) {
		  unshifted_result = IFIX(scale) * value_1 + (SI_Long)2048L;
		  gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	      }
	      else
		  gensymed_symbol_1 = IFIX(scalef_function(scale,
			  FIX(value_1)));
	      current_x_origin_of_drawing = FIX(gensymed_symbol - 
		      gensymed_symbol_1);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
		      1);
		gensymed_symbol = IFIX(Current_y_origin_of_drawing);
		scale = Current_image_y_scale;
		gensymed_symbol_1 = IFIX(y_in_workspace);
		scale_1 = Current_image_y_scale;
		value = FIXNUM_MINUS(y_in_window,Current_y_origin_of_drawing);
		if (IFIX(scale_1) == (SI_Long)4096L)
		    gensymed_symbol_2 = IFIX(value);
		else if ( 
			!(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)))
		    gensymed_symbol_2 = 
			    IFIX(inverse_scalef_function(scale_1,value));
		else if (IFIX(value) >= (SI_Long)0L) {
		    temp_1 = ((IFIX(value) << (SI_Long)12L) + 
			    (IFIX(scale_1) >>  -  - (SI_Long)1L)) / 
			    IFIX(scale_1);
		    gensymed_symbol_2 = temp_1;
		}
		else {
		    temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << (SI_Long)12L) 
			    + (IFIX(scale_1) >>  -  - (SI_Long)1L)) / 
			    IFIX(scale_1);
		    temp_1 = IFIX(FIXNUM_NEGATE(FIX(temp_1)));
		    gensymed_symbol_2 = temp_1;
		}
		value_1 = gensymed_symbol_1 - gensymed_symbol_2;
		if (IFIX(scale) == (SI_Long)4096L)
		    gensymed_symbol_1 = value_1;
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			scale) && FIXNUM_LT(scale,
			Isqrt_of_most_positive_fixnum) && 
			IFIX(Minus_of_isqrt_of_most_positive_fixnum) < 
			value_1 && value_1 < 
			IFIX(Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(scale) * value_1 + (SI_Long)2048L;
		    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
		}
		else
		    gensymed_symbol_1 = IFIX(scalef_function(scale,
			    FIX(value_1)));
		current_y_origin_of_drawing = FIX(gensymed_symbol - 
			gensymed_symbol_1);
		PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
			0);
		  if (CONSP(block_or_blocks)) {
		      block = Nil;
		      ab_loop_list_ = block_or_blocks;
		    next_loop:
		      if ( !TRUEP(ab_loop_list_))
			  goto end_loop;
		      block = M_CAR(ab_loop_list_);
		      ab_loop_list_ = M_CDR(ab_loop_list_);
		      draw_block(block);
		      goto next_loop;
		    end_loop:
		      SAVE_VALUES(VALUES_1(Qnil));
		  }
		  else
		      SAVE_VALUES(draw_block(block_or_blocks));
		POP_SPECIAL();
	      POP_SPECIAL();
	  }
	  else
	      SAVE_VALUES(VALUES_1(Nil));
      }
      else
	  SAVE_VALUES(VALUES_1(Nil));
    POP_SPECIAL();
    if ( !already_in_synch)
	synchronize_transfer_mode();
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

Object Selection_highlight_line_width = UNBOUND;

/* SELECTION-HIGHLIGHT-CURSOR-P */
Object selection_highlight_cursor_p(cursor)
    Object cursor;
{
    Object temp, thing;
    char temp_1;

    x_note_fn_call(128,88);
    if (CONSP(cursor)) {
	temp = CAR(cursor);
	temp_1 =  !SYMBOLP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	thing = CAR(cursor);
	return VALUES_1( !(INLINE_DOUBLE_FLOAT_VECTOR_P(thing) != 
		(SI_Long)0L && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) == 
		(SI_Long)1L) ? T : Nil);
    }
    else
	return VALUES_1(Nil);
}

/* DRAW-OR-ERASE-ALL-SELECTION-HIGHLIGHTS */
Object draw_or_erase_all_selection_highlights(image_plane)
    Object image_plane;
{
    Object gensym_window, left_edge_of_draw_area, top_edge_of_draw_area;
    Object right_edge_of_draw_area, bottom_edge_of_draw_area;
    Object current_image_x_scale, current_image_y_scale;
    Object current_x_origin_of_drawing, current_y_origin_of_drawing;
    Object current_window_1, drawing_on_window, current_drawing_transfer_mode;
    Object type_of_current_window, current_native_window_qm, current_color_map;
    Object temp, current_background_color_value;
    Object current_foreground_color_value, defer_notifications_qm;
    Object current_pane, current_image_plane;
    Object loose_left_edge_of_visible_workspace_area;
    Object loose_top_edge_of_visible_workspace_area;
    Object loose_right_edge_of_visible_workspace_area;
    Object loose_bottom_edge_of_visible_workspace_area, color_or_metacolor;
    Object background_color_or_metacolor, outer_native_image_plane;
    Object current_native_image_plane, color_value, old_color_value;
    Object current_frame_transform_qm, tail, cursor, icp_output_port_qm;
    Object icp_socket_qm, i_am_alive_info_qm, icp_output_port_qm_1;
    Object current_icp_port, current_icp_socket, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, aref_arg_1;
    char already_in_synch, temp_1;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_stack_pointer;
    Declare_catch(3);
    Declare_special(54);
    Object result;

    x_note_fn_call(128,89);
    SAVE_STACK();
    if (ISVREF(image_plane,(SI_Long)27L)) {
	gensym_window = ISVREF(ISVREF(image_plane,(SI_Long)2L),(SI_Long)2L);
	left_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)7L);
	top_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)8L);
	right_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)9L);
	bottom_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)10L);
	PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
		53);
	  PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
		  52);
	    PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
		    51);
	      PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
		      50);
		current_image_x_scale = FIX((SI_Long)4096L);
		current_image_y_scale = FIX((SI_Long)4096L);
		current_x_origin_of_drawing = FIX((SI_Long)0L);
		current_y_origin_of_drawing = FIX((SI_Long)0L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
			49);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
			  48);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
			    47);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
			      46);
			LOCK(On_window_without_drawing);
			if (PUSH_UNWIND_PROTECT(2)) {
			    current_window_1 = ISVREF(ISVREF(image_plane,
				    (SI_Long)2L),(SI_Long)2L);
			    PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
				    45);
			      drawing_on_window = Nil;
			      PUSH_SPECIAL_WITH_SYMBOL(Drawing_on_window,Qdrawing_on_window,drawing_on_window,
				      44);
				current_drawing_transfer_mode = 
					EQ(Current_drawing_transfer_mode,
					Kxor) ? 
					Current_drawing_transfer_mode : 
					ISVREF(Current_window,(SI_Long)30L);
				PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
					43);
				  type_of_current_window = 
					  ISVREF(Current_window,(SI_Long)1L);
				  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
					  42);
				    current_native_window_qm = 
					    ISVREF(Current_window,
					    (SI_Long)17L);
				    PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
					    41);
				      current_color_map = 
					      ISVREF(Current_window,
					      (SI_Long)20L);
				      PUSH_SPECIAL_WITH_SYMBOL(Current_color_map,Qcurrent_color_map,current_color_map,
					      40);
					temp = ISVREF(Current_color_map,
						(SI_Long)5L);
					if (temp);
					else
					    temp = 
						    map_to_color_value_1(Qwhite);
					current_background_color_value = temp;
					PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
						39);
					  temp = ISVREF(Current_color_map,
						  (SI_Long)4L);
					  if (temp);
					  else
					      temp = 
						      map_to_color_value_1(Qblack);
					  current_foreground_color_value = 
						  temp;
					  PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
						  38);
					    defer_notifications_qm = T;
					    PUSH_SPECIAL_WITH_SYMBOL(Defer_notifications_qm,Qdefer_notifications_qm,defer_notifications_qm,
						    37);
					      LOCK(On_window_with_drawing);
					      if (PUSH_UNWIND_PROTECT(1)) {
						  drawing_on_window = T;
						  PUSH_SPECIAL_WITH_SYMBOL(Drawing_on_window,Qdrawing_on_window,drawing_on_window,
							  36);
						    if (EQ(Type_of_current_window,
							    Qx11_window)) {
							LOCK(For_image_plane);
							if (PUSH_UNWIND_PROTECT(0)) 
								    {
							    current_pane = 
								    ISVREF(image_plane,
								    (SI_Long)2L);
							    current_image_plane 
								    = 
								    image_plane;
							    loose_left_edge_of_visible_workspace_area 
								    = 
								    ISVREF(image_plane,
								    (SI_Long)23L);
							    loose_top_edge_of_visible_workspace_area 
								    = 
								    ISVREF(image_plane,
								    (SI_Long)24L);
							    loose_right_edge_of_visible_workspace_area 
								    = 
								    ISVREF(image_plane,
								    (SI_Long)25L);
							    loose_bottom_edge_of_visible_workspace_area 
								    = 
								    ISVREF(image_plane,
								    (SI_Long)26L);
							    color_or_metacolor 
								    = 
								    ISVREF(image_plane,
								    (SI_Long)5L) 
								    ? 
								    ISVREF(ISVREF(image_plane,
								    (SI_Long)5L),
								    (SI_Long)22L) 
								    : Nil;
							    if (color_or_metacolor);
							    else
								color_or_metacolor 
									= 
									Qblack;
							    if (EQ(color_or_metacolor,
								    Qtransparent) 
								    || 
								    EQ(color_or_metacolor,
								    Qbackground)) 
									{
								background_color_or_metacolor 
									= 
									ISVREF(image_plane,
									(SI_Long)5L) 
									? 
									ISVREF(ISVREF(image_plane,
									(SI_Long)5L),
									(SI_Long)21L) 
									: Nil;
								if (background_color_or_metacolor);
								else
								    background_color_or_metacolor 
									    = 
									    Qwhite;
								if (EQ(background_color_or_metacolor,
									Qforeground) 
									|| 
									EQ(background_color_or_metacolor,
									Qworkspace_foreground)) 
									    {
								    temp = 
									    ISVREF(Current_color_map,
									    (SI_Long)4L);
								    if (temp);
								    else
									temp 
										= 
										map_to_color_value_1(Qblack);
								    current_foreground_color_value 
									    = 
									    temp;
								}
								else if (EQ(background_color_or_metacolor,
									Qtransparent) 
									|| 
									EQ(background_color_or_metacolor,
									Qbackground)) 
									    {
								    temp = 
									    ISVREF(Current_color_map,
									    (SI_Long)5L);
								    if (temp);
								    else
									temp 
										= 
										map_to_color_value_1(Qwhite);
								    current_foreground_color_value 
									    = 
									    temp;
								}
								else
								    current_foreground_color_value 
									    = 
									    EQ(background_color_or_metacolor,
									    ISVREF(Current_color_map,
									    (SI_Long)6L)) 
									    ?
									     
									    ISVREF(Current_color_map,
									    (SI_Long)7L) 
									    :
									     
									    map_to_color_value_1(background_color_or_metacolor);
							    }
							    else if (EQ(color_or_metacolor,
								    Qforeground) 
								    || 
								    EQ(color_or_metacolor,
								    Qworkspace_foreground)) 
									{
								temp = 
									ISVREF(Current_color_map,
									(SI_Long)4L);
								if (temp);
								else
								    temp = 
									    map_to_color_value_1(Qblack);
								current_foreground_color_value 
									= temp;
							    }
							    else
								current_foreground_color_value 
									= 
									EQ(color_or_metacolor,
									ISVREF(Current_color_map,
									(SI_Long)6L)) 
									? 
									ISVREF(Current_color_map,
									(SI_Long)7L) 
									: 
									map_to_color_value_1(color_or_metacolor);
							    PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
								    23);
							      PUSH_SPECIAL_WITH_SYMBOL(Loose_bottom_edge_of_visible_workspace_area,Qloose_bottom_edge_of_visible_workspace_area,loose_bottom_edge_of_visible_workspace_area,
								      22);
								PUSH_SPECIAL_WITH_SYMBOL(Loose_right_edge_of_visible_workspace_area,Qloose_right_edge_of_visible_workspace_area,loose_right_edge_of_visible_workspace_area,
									21);
								  PUSH_SPECIAL_WITH_SYMBOL(Loose_top_edge_of_visible_workspace_area,Qloose_top_edge_of_visible_workspace_area,loose_top_edge_of_visible_workspace_area,
									  20);
								    PUSH_SPECIAL_WITH_SYMBOL(Loose_left_edge_of_visible_workspace_area,Qloose_left_edge_of_visible_workspace_area,loose_left_edge_of_visible_workspace_area,
									    19);
								      PUSH_SPECIAL_WITH_SYMBOL(Current_image_plane,Qcurrent_image_plane,current_image_plane,
									      18);
									PUSH_SPECIAL_WITH_SYMBOL(Current_pane,Qcurrent_pane,current_pane,
										17);
									  outer_native_image_plane 
										  = 
										  Current_native_image_plane;
									  PUSH_SPECIAL_WITH_SYMBOL(Outer_native_image_plane,Qouter_native_image_plane,outer_native_image_plane,
										  16);
									    current_native_image_plane 
										    = 
										    image_plane;
									    PUSH_SPECIAL_WITH_SYMBOL(Current_native_image_plane,Qcurrent_native_image_plane,current_native_image_plane,
										    15);
									      if ( 
										      !EQ(Outer_native_image_plane,
										      Current_native_image_plane))
										  nip_begin_drawing(Current_native_image_plane);
									      color_or_metacolor 
										      = 
										      ISVREF(image_plane,
										      (SI_Long)5L) 
										      ?
										       
										      ISVREF(ISVREF(image_plane,
										      (SI_Long)5L),
										      (SI_Long)21L) 
										      :
										       
										      Nil;
									      if (color_or_metacolor);
									      else
										  color_or_metacolor 
											  = 
											  Qwhite;
									      if (EQ(color_or_metacolor,
										      Qtransparent) 
										      || 
										      EQ(color_or_metacolor,
										      Qbackground)) 
											  {
										  color_value 
											  = 
											  ISVREF(Current_color_map,
											  (SI_Long)5L);
										  if (color_value);
										  else
										      color_value 
											      = 
											      map_to_color_value_1(Qwhite);
									      }
									      else if (EQ(color_or_metacolor,
										      Qforeground) 
										      || 
										      EQ(color_or_metacolor,
										      Qworkspace_foreground)) 
											  {
										  temp 
											  = 
											  ISVREF(image_plane,
											  (SI_Long)5L) 
											  ?
											   
											  ISVREF(ISVREF(image_plane,
											  (SI_Long)5L),
											  (SI_Long)22L) 
											  :
											   
											  Nil;
										  if (temp);
										  else
										      temp 
											      = 
											      Qblack;
										  color_or_metacolor 
											  = 
											  temp;
										  if (EQ(color_or_metacolor,
											  Qtransparent) 
											  || 
											  EQ(color_or_metacolor,
											  Qbackground)) 
											      {
										      background_color_or_metacolor 
											      = 
											      ISVREF(image_plane,
											      (SI_Long)5L) 
											      ?
											       
											      ISVREF(ISVREF(image_plane,
											      (SI_Long)5L),
											      (SI_Long)21L) 
											      :
											       
											      Nil;
										      if (background_color_or_metacolor);
										      else
											  background_color_or_metacolor 
												  = 
												  Qwhite;
										      if (EQ(background_color_or_metacolor,
											      Qforeground) 
											      || 
											      EQ(background_color_or_metacolor,
											      Qworkspace_foreground)) 
												  {
											  color_value 
												  = 
												  ISVREF(Current_color_map,
												  (SI_Long)4L);
											  if (color_value);
											  else
											      color_value 
												      = 
												      map_to_color_value_1(Qblack);
										      }
										      else if (EQ(background_color_or_metacolor,
											      Qtransparent) 
											      || 
											      EQ(background_color_or_metacolor,
											      Qbackground)) 
												  {
											  color_value 
												  = 
												  ISVREF(Current_color_map,
												  (SI_Long)5L);
											  if (color_value);
											  else
											      color_value 
												      = 
												      map_to_color_value_1(Qwhite);
										      }
										      else
											  color_value 
												  = 
												  EQ(background_color_or_metacolor,
												  ISVREF(Current_color_map,
												  (SI_Long)6L)) 
												  ?
												   
												  ISVREF(Current_color_map,
												  (SI_Long)7L) 
												  :
												   
												  map_to_color_value_1(background_color_or_metacolor);
										  }
										  else if (EQ(color_or_metacolor,
											  Qforeground) 
											  || 
											  EQ(color_or_metacolor,
											  Qworkspace_foreground)) 
											      {
										      color_value 
											      = 
											      ISVREF(Current_color_map,
											      (SI_Long)4L);
										      if (color_value);
										      else
											  color_value 
												  = 
												  map_to_color_value_1(Qblack);
										  }
										  else
										      color_value 
											      = 
											      EQ(color_or_metacolor,
											      ISVREF(Current_color_map,
											      (SI_Long)6L)) 
											      ?
											       
											      ISVREF(Current_color_map,
											      (SI_Long)7L) 
											      :
											       
											      map_to_color_value_1(color_or_metacolor);
									      }
									      else
										  color_value 
											  = 
											  EQ(color_or_metacolor,
											  ISVREF(Current_color_map,
											  (SI_Long)6L)) 
											  ?
											   
											  ISVREF(Current_color_map,
											  (SI_Long)7L) 
											  :
											   
											  map_to_color_value_1(color_or_metacolor);
									      old_color_value 
										      = 
										      Current_background_color_value;
									      current_background_color_value 
										      = 
										      Current_background_color_value;
									      PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
										      14);
										set_current_background_color_value(color_value);
										left_edge_of_draw_area 
											= 
											Left_edge_of_draw_area;
										top_edge_of_draw_area 
											= 
											Top_edge_of_draw_area;
										right_edge_of_draw_area 
											= 
											Right_edge_of_draw_area;
										bottom_edge_of_draw_area 
											= 
											Bottom_edge_of_draw_area;
										PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
											13);
										  PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
											  12);
										    PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
											    11);
										      PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
											      10);
											temp 
												= 
												ISVREF(image_plane,
												(SI_Long)6L);
											Left_edge_of_draw_area 
												= 
												FIXNUM_MAX(temp,
												Left_edge_of_draw_area);
											temp 
												= 
												ISVREF(image_plane,
												(SI_Long)7L);
											Top_edge_of_draw_area 
												= 
												FIXNUM_MAX(temp,
												Top_edge_of_draw_area);
											temp 
												= 
												ISVREF(image_plane,
												(SI_Long)8L);
											Right_edge_of_draw_area 
												= 
												FIXNUM_MIN(temp,
												Right_edge_of_draw_area);
											temp 
												= 
												ISVREF(image_plane,
												(SI_Long)9L);
											Bottom_edge_of_draw_area 
												= 
												FIXNUM_MIN(temp,
												Bottom_edge_of_draw_area);
											if (FIXNUM_LT(Left_edge_of_draw_area,
												Right_edge_of_draw_area) 
												&& 
												FIXNUM_LT(Top_edge_of_draw_area,
												Bottom_edge_of_draw_area)) 
												    {
											    left_edge_of_draw_area 
												    = 
												    Left_edge_of_draw_area;
											    top_edge_of_draw_area 
												    = 
												    Top_edge_of_draw_area;
											    right_edge_of_draw_area 
												    = 
												    Right_edge_of_draw_area;
											    bottom_edge_of_draw_area 
												    = 
												    Bottom_edge_of_draw_area;
											    PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
												    9);
											      PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
												      8);
												PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
													7);
												  PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
													  6);
												    temp 
													    = 
													    ISVREF(image_plane,
													    (SI_Long)19L);
												    Left_edge_of_draw_area 
													    = 
													    FIXNUM_MAX(temp,
													    Left_edge_of_draw_area);
												    temp 
													    = 
													    ISVREF(image_plane,
													    (SI_Long)20L);
												    Top_edge_of_draw_area 
													    = 
													    FIXNUM_MAX(temp,
													    Top_edge_of_draw_area);
												    temp 
													    = 
													    ISVREF(image_plane,
													    (SI_Long)21L);
												    Right_edge_of_draw_area 
													    = 
													    FIXNUM_MIN(temp,
													    Right_edge_of_draw_area);
												    temp 
													    = 
													    ISVREF(image_plane,
													    (SI_Long)22L);
												    Bottom_edge_of_draw_area 
													    = 
													    FIXNUM_MIN(temp,
													    Bottom_edge_of_draw_area);
												    if (FIXNUM_LT(Left_edge_of_draw_area,
													    Right_edge_of_draw_area) 
													    && 
													    FIXNUM_LT(Top_edge_of_draw_area,
													    Bottom_edge_of_draw_area)) 
														{
													current_frame_transform_qm 
														= 
														Nil;
													current_image_x_scale 
														= 
														ISVREF(image_plane,
														(SI_Long)11L);
													current_image_y_scale 
														= 
														ISVREF(image_plane,
														(SI_Long)12L);
													current_x_origin_of_drawing 
														= 
														ISVREF(image_plane,
														(SI_Long)13L);
													current_y_origin_of_drawing 
														= 
														ISVREF(image_plane,
														(SI_Long)14L);
													PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
														5);
													  PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
														  4);
													    PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
														    3);
													      PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
														      2);
														PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
															1);
														  already_in_synch 
															  = 
															  EQ(Current_drawing_transfer_mode,
															  Kxor);
														  current_drawing_transfer_mode 
															  = 
															  Current_drawing_transfer_mode;
														  PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
															  0);
														    if ( 
															    !already_in_synch) 
																{
															Current_drawing_transfer_mode 
																= 
																Kxor;
															synchronize_transfer_mode();
														    }
														    tail 
															    = 
															    ISVREF(image_plane,
															    (SI_Long)27L);
														    cursor 
															    = 
															    Nil;
														    for ( 
															    ; 
															    !ENDP(tail); 
															    tail 
															    = 
															    CDR(tail)) 
																{
															cursor 
																= 
																CAR(tail);
															if (selection_highlight_cursor_p(cursor))
															    draw_selection_highlight(cursor);
														    }
														  POP_SPECIAL();
														  if ( 
															  !already_in_synch)
														      synchronize_transfer_mode();
														POP_SPECIAL();
													      POP_SPECIAL();
													    POP_SPECIAL();
													  POP_SPECIAL();
													POP_SPECIAL();
												    }
												  POP_SPECIAL();
												POP_SPECIAL();
											      POP_SPECIAL();
											    POP_SPECIAL();
											}
										      POP_SPECIAL();
										    POP_SPECIAL();
										  POP_SPECIAL();
										POP_SPECIAL();
										set_current_background_color_value(old_color_value);
									      POP_SPECIAL();
									      if ( 
										      !EQ(Outer_native_image_plane,
										      Current_native_image_plane))
										  nip_end_drawing(Current_native_image_plane);
									    POP_SPECIAL();
									    temp 
										    = 
										    Current_native_image_plane 
										    ?
										     
										    ( 
										    !EQ(image_plane,
										    Current_native_image_plane) 
										    ?
										     
										    nip_begin_drawing(Current_native_image_plane) 
										    :
										     
										    Nil) 
										    :
										     
										    Nil;
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
							UNLOCK(For_image_plane);
							CONTINUE_UNWINDING(0);
							result = RESTORE_VALUES();
							SAVE_VALUES(VALUES_1(result));
							if (Flush_graphics_immediately_qm)
							    sync_graphics_on_current_window();
						    }
						    else if (EQ(Type_of_current_window,
							    Qicp)) {
							icp_output_port_qm 
								= 
								ISVREF(Current_window,
								(SI_Long)12L);
							icp_socket_qm = 
								icp_output_port_qm 
								? 
								ISVREF(icp_output_port_qm,
								(SI_Long)2L) 
								: Qnil;
							if (icp_socket_qm) {
							    i_am_alive_info_qm 
								    = 
								    ISVREF(icp_socket_qm,
								    (SI_Long)24L);
							    temp_1 =  
								    !TRUEP(i_am_alive_info_qm);
							    if (temp_1);
							    else
								temp_1 =  
									!TRUEP(Do_icp_flow_control_qm);
							    if (temp_1);
							    else
								temp_1 =  
									!TRUEP(ISVREF(i_am_alive_info_qm,
									(SI_Long)2L));
							}
							else
							    temp_1 = 
								    TRUEP(Nil);
							if (temp_1) {
							    icp_output_port_qm_1 
								    = 
								    ISVREF(Current_window,
								    (SI_Long)12L);
							    if (icp_output_port_qm_1 
								    && 
								    icp_connection_open_p(ISVREF(icp_output_port_qm_1,
								    (SI_Long)2L))) 
									{
								current_icp_port 
									= 
									icp_output_port_qm_1;
								PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
									35);
								  current_icp_socket 
									  = 
									  ISVREF(Current_icp_port,
									  (SI_Long)2L);
								  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
									  34);
								    temp = 
									    IFIX(ISVREF(Current_icp_socket,
									    (SI_Long)22L)) 
									    >= 
									    (SI_Long)17L 
									    ?
									     
									    ISVREF(Current_icp_socket,
									    (SI_Long)53L) 
									    :
									     
									    Nil;
								    if (temp);
								    else
									temp 
										= 
										EQ(ISVREF(Current_icp_socket,
										(SI_Long)25L),
										Qtelewindows) 
										?
										 T : Nil;
								    disable_resumability 
									    = 
									    temp;
								    PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
									    33);
								      number_of_icp_bytes_for_message_series 
									      = 
									      FIX((SI_Long)0L);
								      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
									      32);
									icp_buffers_for_message_group 
										= 
										Nil;
									PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
										31);
									  icp_buffer_of_start_of_message_series_qm 
										  = 
										  Nil;
									  PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
										  30);
									    icp_byte_position_of_start_of_message_series_qm 
										    = 
										    Nil;
									    PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
										    29);
									      number_of_icp_bytes_to_fill_buffer 
										      = 
										      FIX((SI_Long)0L);
									      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
										      28);
										current_icp_buffer 
											= 
											Nil;
										PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
											27);
										  current_write_icp_byte_position 
											  = 
											  Nil;
										  PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
											  26);
										    number_of_icp_bytes_in_message_group 
											    = 
											    FIX((SI_Long)0L);
										    PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
											    25);
										      writing_icp_message_group 
											      = 
											      FIXNUM_ADD1(Writing_icp_message_group);
										      PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
											      24);
											gensymed_symbol 
												= 
												Nil;
											gensymed_symbol_1 
												= 
												0.0;
											gensymed_symbol_2 
												= 
												0.0;
											if (Profiling_enabled_qm) 
												    {
											    gensymed_symbol 
												    = 
												    T;
											    gensymed_symbol_1 
												    = 
												    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
												    (SI_Long)2L),
												    (SI_Long)0L);
											    gensymed_symbol_2 
												    = 
												    g2ext_unix_time_as_float();
											    aref_arg_1 
												    = 
												    ISVREF(Profiling_enabled_qm,
												    (SI_Long)2L);
											    DFLOAT_ISASET_1(aref_arg_1,
												    (SI_Long)0L,
												    gensymed_symbol_2);
											}
											if (icp_connection_open_p(Current_icp_socket) 
												&& 
												 
												!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
												    {
											    synchronize_icp_on_window_with_drawing(Current_window,
												    Left_edge_of_draw_area,
												    Top_edge_of_draw_area,
												    Right_edge_of_draw_area,
												    Bottom_edge_of_draw_area);
											    LOCK(For_image_plane);
											    if (PUSH_UNWIND_PROTECT(0)) 
													{
												current_pane 
													= 
													ISVREF(image_plane,
													(SI_Long)2L);
												current_image_plane 
													= 
													image_plane;
												loose_left_edge_of_visible_workspace_area 
													= 
													ISVREF(image_plane,
													(SI_Long)23L);
												loose_top_edge_of_visible_workspace_area 
													= 
													ISVREF(image_plane,
													(SI_Long)24L);
												loose_right_edge_of_visible_workspace_area 
													= 
													ISVREF(image_plane,
													(SI_Long)25L);
												loose_bottom_edge_of_visible_workspace_area 
													= 
													ISVREF(image_plane,
													(SI_Long)26L);
												color_or_metacolor 
													= 
													ISVREF(image_plane,
													(SI_Long)5L) 
													?
													 
													ISVREF(ISVREF(image_plane,
													(SI_Long)5L),
													(SI_Long)22L) 
													:
													 
													Nil;
												if (color_or_metacolor);
												else
												    color_or_metacolor 
													    = 
													    Qblack;
												if (EQ(color_or_metacolor,
													Qtransparent) 
													|| 
													EQ(color_or_metacolor,
													Qbackground)) 
													    {
												    background_color_or_metacolor 
													    = 
													    ISVREF(image_plane,
													    (SI_Long)5L) 
													    ?
													     
													    ISVREF(ISVREF(image_plane,
													    (SI_Long)5L),
													    (SI_Long)21L) 
													    :
													     
													    Nil;
												    if (background_color_or_metacolor);
												    else
													background_color_or_metacolor 
														= 
														Qwhite;
												    if (EQ(background_color_or_metacolor,
													    Qforeground) 
													    || 
													    EQ(background_color_or_metacolor,
													    Qworkspace_foreground)) 
														{
													temp 
														= 
														ISVREF(Current_color_map,
														(SI_Long)4L);
													if (temp);
													else
													    temp 
														    = 
														    map_to_color_value_1(Qblack);
													current_foreground_color_value 
														= 
														temp;
												    }
												    else if (EQ(background_color_or_metacolor,
													    Qtransparent) 
													    || 
													    EQ(background_color_or_metacolor,
													    Qbackground)) 
														{
													temp 
														= 
														ISVREF(Current_color_map,
														(SI_Long)5L);
													if (temp);
													else
													    temp 
														    = 
														    map_to_color_value_1(Qwhite);
													current_foreground_color_value 
														= 
														temp;
												    }
												    else
													current_foreground_color_value 
														= 
														EQ(background_color_or_metacolor,
														ISVREF(Current_color_map,
														(SI_Long)6L)) 
														?
														 
														ISVREF(Current_color_map,
														(SI_Long)7L) 
														:
														 
														map_to_color_value_1(background_color_or_metacolor);
												}
												else if (EQ(color_or_metacolor,
													Qforeground) 
													|| 
													EQ(color_or_metacolor,
													Qworkspace_foreground)) 
													    {
												    temp 
													    = 
													    ISVREF(Current_color_map,
													    (SI_Long)4L);
												    if (temp);
												    else
													temp 
														= 
														map_to_color_value_1(Qblack);
												    current_foreground_color_value 
													    = 
													    temp;
												}
												else
												    current_foreground_color_value 
													    = 
													    EQ(color_or_metacolor,
													    ISVREF(Current_color_map,
													    (SI_Long)6L)) 
													    ?
													     
													    ISVREF(Current_color_map,
													    (SI_Long)7L) 
													    :
													     
													    map_to_color_value_1(color_or_metacolor);
												PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
													23);
												  PUSH_SPECIAL_WITH_SYMBOL(Loose_bottom_edge_of_visible_workspace_area,Qloose_bottom_edge_of_visible_workspace_area,loose_bottom_edge_of_visible_workspace_area,
													  22);
												    PUSH_SPECIAL_WITH_SYMBOL(Loose_right_edge_of_visible_workspace_area,Qloose_right_edge_of_visible_workspace_area,loose_right_edge_of_visible_workspace_area,
													    21);
												      PUSH_SPECIAL_WITH_SYMBOL(Loose_top_edge_of_visible_workspace_area,Qloose_top_edge_of_visible_workspace_area,loose_top_edge_of_visible_workspace_area,
													      20);
													PUSH_SPECIAL_WITH_SYMBOL(Loose_left_edge_of_visible_workspace_area,Qloose_left_edge_of_visible_workspace_area,loose_left_edge_of_visible_workspace_area,
														19);
													  PUSH_SPECIAL_WITH_SYMBOL(Current_image_plane,Qcurrent_image_plane,current_image_plane,
														  18);
													    PUSH_SPECIAL_WITH_SYMBOL(Current_pane,Qcurrent_pane,current_pane,
														    17);
													      outer_native_image_plane 
														      = 
														      Current_native_image_plane;
													      PUSH_SPECIAL_WITH_SYMBOL(Outer_native_image_plane,Qouter_native_image_plane,outer_native_image_plane,
														      16);
														current_native_image_plane 
															= 
															image_plane;
														PUSH_SPECIAL_WITH_SYMBOL(Current_native_image_plane,Qcurrent_native_image_plane,current_native_image_plane,
															15);
														  if ( 
															  !EQ(Outer_native_image_plane,
															  Current_native_image_plane))
														      nip_begin_drawing(Current_native_image_plane);
														  color_or_metacolor 
															  = 
															  ISVREF(image_plane,
															  (SI_Long)5L) 
															  ?
															   
															  ISVREF(ISVREF(image_plane,
															  (SI_Long)5L),
															  (SI_Long)21L) 
															  :
															   
															  Nil;
														  if (color_or_metacolor);
														  else
														      color_or_metacolor 
															      = 
															      Qwhite;
														  if (EQ(color_or_metacolor,
															  Qtransparent) 
															  || 
															  EQ(color_or_metacolor,
															  Qbackground)) 
															      {
														      color_value 
															      = 
															      ISVREF(Current_color_map,
															      (SI_Long)5L);
														      if (color_value);
														      else
															  color_value 
																  = 
																  map_to_color_value_1(Qwhite);
														  }
														  else if (EQ(color_or_metacolor,
															  Qforeground) 
															  || 
															  EQ(color_or_metacolor,
															  Qworkspace_foreground)) 
															      {
														      temp 
															      = 
															      ISVREF(image_plane,
															      (SI_Long)5L) 
															      ?
															       
															      ISVREF(ISVREF(image_plane,
															      (SI_Long)5L),
															      (SI_Long)22L) 
															      :
															       
															      Nil;
														      if (temp);
														      else
															  temp 
																  = 
																  Qblack;
														      color_or_metacolor 
															      = 
															      temp;
														      if (EQ(color_or_metacolor,
															      Qtransparent) 
															      || 
															      EQ(color_or_metacolor,
															      Qbackground)) 
																  {
															  background_color_or_metacolor 
																  = 
																  ISVREF(image_plane,
																  (SI_Long)5L) 
																  ?
																   
																  ISVREF(ISVREF(image_plane,
																  (SI_Long)5L),
																  (SI_Long)21L) 
																  :
																   
																  Nil;
															  if (background_color_or_metacolor);
															  else
															      background_color_or_metacolor 
																      = 
																      Qwhite;
															  if (EQ(background_color_or_metacolor,
																  Qforeground) 
																  || 
																  EQ(background_color_or_metacolor,
																  Qworkspace_foreground)) 
																      {
															      color_value 
																      = 
																      ISVREF(Current_color_map,
																      (SI_Long)4L);
															      if (color_value);
															      else
																  color_value 
																	  = 
																	  map_to_color_value_1(Qblack);
															  }
															  else if (EQ(background_color_or_metacolor,
																  Qtransparent) 
																  || 
																  EQ(background_color_or_metacolor,
																  Qbackground)) 
																      {
															      color_value 
																      = 
																      ISVREF(Current_color_map,
																      (SI_Long)5L);
															      if (color_value);
															      else
																  color_value 
																	  = 
																	  map_to_color_value_1(Qwhite);
															  }
															  else
															      color_value 
																      = 
																      EQ(background_color_or_metacolor,
																      ISVREF(Current_color_map,
																      (SI_Long)6L)) 
																      ?
																       
																      ISVREF(Current_color_map,
																      (SI_Long)7L) 
																      :
																       
																      map_to_color_value_1(background_color_or_metacolor);
														      }
														      else if (EQ(color_or_metacolor,
															      Qforeground) 
															      || 
															      EQ(color_or_metacolor,
															      Qworkspace_foreground)) 
																  {
															  color_value 
																  = 
																  ISVREF(Current_color_map,
																  (SI_Long)4L);
															  if (color_value);
															  else
															      color_value 
																      = 
																      map_to_color_value_1(Qblack);
														      }
														      else
															  color_value 
																  = 
																  EQ(color_or_metacolor,
																  ISVREF(Current_color_map,
																  (SI_Long)6L)) 
																  ?
																   
																  ISVREF(Current_color_map,
																  (SI_Long)7L) 
																  :
																   
																  map_to_color_value_1(color_or_metacolor);
														  }
														  else
														      color_value 
															      = 
															      EQ(color_or_metacolor,
															      ISVREF(Current_color_map,
															      (SI_Long)6L)) 
															      ?
															       
															      ISVREF(Current_color_map,
															      (SI_Long)7L) 
															      :
															       
															      map_to_color_value_1(color_or_metacolor);
														  old_color_value 
															  = 
															  Current_background_color_value;
														  current_background_color_value 
															  = 
															  Current_background_color_value;
														  PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
															  14);
														    set_current_background_color_value(color_value);
														    left_edge_of_draw_area 
															    = 
															    Left_edge_of_draw_area;
														    top_edge_of_draw_area 
															    = 
															    Top_edge_of_draw_area;
														    right_edge_of_draw_area 
															    = 
															    Right_edge_of_draw_area;
														    bottom_edge_of_draw_area 
															    = 
															    Bottom_edge_of_draw_area;
														    PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
															    13);
														      PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
															      12);
															PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
																11);
															  PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
																  10);
															    temp 
																    = 
																    ISVREF(image_plane,
																    (SI_Long)6L);
															    Left_edge_of_draw_area 
																    = 
																    FIXNUM_MAX(temp,
																    Left_edge_of_draw_area);
															    temp 
																    = 
																    ISVREF(image_plane,
																    (SI_Long)7L);
															    Top_edge_of_draw_area 
																    = 
																    FIXNUM_MAX(temp,
																    Top_edge_of_draw_area);
															    temp 
																    = 
																    ISVREF(image_plane,
																    (SI_Long)8L);
															    Right_edge_of_draw_area 
																    = 
																    FIXNUM_MIN(temp,
																    Right_edge_of_draw_area);
															    temp 
																    = 
																    ISVREF(image_plane,
																    (SI_Long)9L);
															    Bottom_edge_of_draw_area 
																    = 
																    FIXNUM_MIN(temp,
																    Bottom_edge_of_draw_area);
															    if (FIXNUM_LT(Left_edge_of_draw_area,
																    Right_edge_of_draw_area) 
																    && 
																    FIXNUM_LT(Top_edge_of_draw_area,
																    Bottom_edge_of_draw_area)) 
																	{
																left_edge_of_draw_area 
																	= 
																	Left_edge_of_draw_area;
																top_edge_of_draw_area 
																	= 
																	Top_edge_of_draw_area;
																right_edge_of_draw_area 
																	= 
																	Right_edge_of_draw_area;
																bottom_edge_of_draw_area 
																	= 
																	Bottom_edge_of_draw_area;
																PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
																	9);
																  PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
																	  8);
																    PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
																	    7);
																      PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
																	      6);
																	temp 
																		= 
																		ISVREF(image_plane,
																		(SI_Long)19L);
																	Left_edge_of_draw_area 
																		= 
																		FIXNUM_MAX(temp,
																		Left_edge_of_draw_area);
																	temp 
																		= 
																		ISVREF(image_plane,
																		(SI_Long)20L);
																	Top_edge_of_draw_area 
																		= 
																		FIXNUM_MAX(temp,
																		Top_edge_of_draw_area);
																	temp 
																		= 
																		ISVREF(image_plane,
																		(SI_Long)21L);
																	Right_edge_of_draw_area 
																		= 
																		FIXNUM_MIN(temp,
																		Right_edge_of_draw_area);
																	temp 
																		= 
																		ISVREF(image_plane,
																		(SI_Long)22L);
																	Bottom_edge_of_draw_area 
																		= 
																		FIXNUM_MIN(temp,
																		Bottom_edge_of_draw_area);
																	if (FIXNUM_LT(Left_edge_of_draw_area,
																		Right_edge_of_draw_area) 
																		&& 
																		FIXNUM_LT(Top_edge_of_draw_area,
																		Bottom_edge_of_draw_area)) 
																		    {
																	    current_frame_transform_qm 
																		    = 
																		    Nil;
																	    current_image_x_scale 
																		    = 
																		    ISVREF(image_plane,
																		    (SI_Long)11L);
																	    current_image_y_scale 
																		    = 
																		    ISVREF(image_plane,
																		    (SI_Long)12L);
																	    current_x_origin_of_drawing 
																		    = 
																		    ISVREF(image_plane,
																		    (SI_Long)13L);
																	    current_y_origin_of_drawing 
																		    = 
																		    ISVREF(image_plane,
																		    (SI_Long)14L);
																	    PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
																		    5);
																	      PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
																		      4);
																		PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
																			3);
																		  PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
																			  2);
																		    PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
																			    1);
																		      already_in_synch 
																			      = 
																			      EQ(Current_drawing_transfer_mode,
																			      Kxor);
																		      current_drawing_transfer_mode 
																			      = 
																			      Current_drawing_transfer_mode;
																		      PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
																			      0);
																			if ( 
																				!already_in_synch) 
																				    {
																			    Current_drawing_transfer_mode 
																				    = 
																				    Kxor;
																			    synchronize_transfer_mode();
																			}
																			tail 
																				= 
																				ISVREF(image_plane,
																				(SI_Long)27L);
																			cursor 
																				= 
																				Nil;
																			for ( 
																				; 
																				!ENDP(tail); 
																				tail 
																				= 
																				CDR(tail)) 
																				    {
																			    cursor 
																				    = 
																				    CAR(tail);
																			    if (selection_highlight_cursor_p(cursor))
																				draw_selection_highlight(cursor);
																			}
																		      POP_SPECIAL();
																		      if ( 
																			      !already_in_synch)
																			  synchronize_transfer_mode();
																		    POP_SPECIAL();
																		  POP_SPECIAL();
																		POP_SPECIAL();
																	      POP_SPECIAL();
																	    POP_SPECIAL();
																	}
																      POP_SPECIAL();
																    POP_SPECIAL();
																  POP_SPECIAL();
																POP_SPECIAL();
															    }
															  POP_SPECIAL();
															POP_SPECIAL();
														      POP_SPECIAL();
														    POP_SPECIAL();
														    set_current_background_color_value(old_color_value);
														  POP_SPECIAL();
														  if ( 
															  !EQ(Outer_native_image_plane,
															  Current_native_image_plane))
														      nip_end_drawing(Current_native_image_plane);
														POP_SPECIAL();
														temp 
															= 
															Current_native_image_plane 
															?
															 
															( 
															!EQ(image_plane,
															Current_native_image_plane) 
															?
															 
															nip_begin_drawing(Current_native_image_plane) 
															:
															 
															Nil) 
															:
															 
															Nil;
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
											    UNLOCK(For_image_plane);
											    CONTINUE_UNWINDING(0);
											    result = RESTORE_VALUES();
											    temp 
												    = 
												    result;
											    if (Flush_graphics_immediately_qm 
												    && 
												    FIXNUM_NE(ISVREF(Current_icp_socket,
												    (SI_Long)15L),
												    Icp_connection_closed))
												sync_graphics_on_current_window();
											    end_icp_message_group();
											}
											else
											    temp 
												    = 
												    Nil;
											SAVE_VALUES(VALUES_1(temp));
											if (Profiling_enabled_qm) 
												    {
											    gensymed_symbol_3 
												    = 
												    g2ext_unix_time_as_float();
											    gensymed_symbol_4 
												    = 
												    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
												    (SI_Long)2L),
												    (SI_Long)0L);
											    gensymed_symbol_5 
												    = 
												    gensymed_symbol_3 
												    - 
												    gensymed_symbol_4;
											    aref_arg_1 
												    = 
												    ISVREF(Profiling_enabled_qm,
												    (SI_Long)6L);
											    aref_new_value 
												    = 
												    gensymed_symbol_5 
												    + 
												    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
												    (SI_Long)6L),
												    (SI_Long)0L);
											    DFLOAT_ISASET_1(aref_arg_1,
												    (SI_Long)0L,
												    aref_new_value);
											    aref_arg_1 
												    = 
												    ISVREF(Profiling_enabled_qm,
												    (SI_Long)2L);
											    aref_new_value 
												    = 
												    gensymed_symbol 
												    ?
												     
												    gensymed_symbol_1 
												    + 
												    gensymed_symbol_5 
												    + 
												    (gensymed_symbol_4 
												    - 
												    gensymed_symbol_2) 
												    :
												     
												    gensymed_symbol_3;
											    DFLOAT_ISASET_1(aref_arg_1,
												    (SI_Long)0L,
												    aref_new_value);
											}
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
							    else
								SAVE_VALUES(VALUES_1(Nil));
							}
							else
							    SAVE_VALUES(VALUES_1(Nil));
						    }
						    else if (EQ(Type_of_current_window,
							    Qprinter)) {
							LOCK(For_image_plane);
							if (PUSH_UNWIND_PROTECT(0)) 
								    {
							    current_pane = 
								    ISVREF(image_plane,
								    (SI_Long)2L);
							    current_image_plane 
								    = 
								    image_plane;
							    loose_left_edge_of_visible_workspace_area 
								    = 
								    ISVREF(image_plane,
								    (SI_Long)23L);
							    loose_top_edge_of_visible_workspace_area 
								    = 
								    ISVREF(image_plane,
								    (SI_Long)24L);
							    loose_right_edge_of_visible_workspace_area 
								    = 
								    ISVREF(image_plane,
								    (SI_Long)25L);
							    loose_bottom_edge_of_visible_workspace_area 
								    = 
								    ISVREF(image_plane,
								    (SI_Long)26L);
							    color_or_metacolor 
								    = 
								    ISVREF(image_plane,
								    (SI_Long)5L) 
								    ? 
								    ISVREF(ISVREF(image_plane,
								    (SI_Long)5L),
								    (SI_Long)22L) 
								    : Nil;
							    if (color_or_metacolor);
							    else
								color_or_metacolor 
									= 
									Qblack;
							    if (EQ(color_or_metacolor,
								    Qtransparent) 
								    || 
								    EQ(color_or_metacolor,
								    Qbackground)) 
									{
								background_color_or_metacolor 
									= 
									ISVREF(image_plane,
									(SI_Long)5L) 
									? 
									ISVREF(ISVREF(image_plane,
									(SI_Long)5L),
									(SI_Long)21L) 
									: Nil;
								if (background_color_or_metacolor);
								else
								    background_color_or_metacolor 
									    = 
									    Qwhite;
								if (EQ(background_color_or_metacolor,
									Qforeground) 
									|| 
									EQ(background_color_or_metacolor,
									Qworkspace_foreground)) 
									    {
								    temp = 
									    ISVREF(Current_color_map,
									    (SI_Long)4L);
								    if (temp);
								    else
									temp 
										= 
										map_to_color_value_1(Qblack);
								    current_foreground_color_value 
									    = 
									    temp;
								}
								else if (EQ(background_color_or_metacolor,
									Qtransparent) 
									|| 
									EQ(background_color_or_metacolor,
									Qbackground)) 
									    {
								    temp = 
									    ISVREF(Current_color_map,
									    (SI_Long)5L);
								    if (temp);
								    else
									temp 
										= 
										map_to_color_value_1(Qwhite);
								    current_foreground_color_value 
									    = 
									    temp;
								}
								else
								    current_foreground_color_value 
									    = 
									    EQ(background_color_or_metacolor,
									    ISVREF(Current_color_map,
									    (SI_Long)6L)) 
									    ?
									     
									    ISVREF(Current_color_map,
									    (SI_Long)7L) 
									    :
									     
									    map_to_color_value_1(background_color_or_metacolor);
							    }
							    else if (EQ(color_or_metacolor,
								    Qforeground) 
								    || 
								    EQ(color_or_metacolor,
								    Qworkspace_foreground)) 
									{
								temp = 
									ISVREF(Current_color_map,
									(SI_Long)4L);
								if (temp);
								else
								    temp = 
									    map_to_color_value_1(Qblack);
								current_foreground_color_value 
									= temp;
							    }
							    else
								current_foreground_color_value 
									= 
									EQ(color_or_metacolor,
									ISVREF(Current_color_map,
									(SI_Long)6L)) 
									? 
									ISVREF(Current_color_map,
									(SI_Long)7L) 
									: 
									map_to_color_value_1(color_or_metacolor);
							    PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
								    23);
							      PUSH_SPECIAL_WITH_SYMBOL(Loose_bottom_edge_of_visible_workspace_area,Qloose_bottom_edge_of_visible_workspace_area,loose_bottom_edge_of_visible_workspace_area,
								      22);
								PUSH_SPECIAL_WITH_SYMBOL(Loose_right_edge_of_visible_workspace_area,Qloose_right_edge_of_visible_workspace_area,loose_right_edge_of_visible_workspace_area,
									21);
								  PUSH_SPECIAL_WITH_SYMBOL(Loose_top_edge_of_visible_workspace_area,Qloose_top_edge_of_visible_workspace_area,loose_top_edge_of_visible_workspace_area,
									  20);
								    PUSH_SPECIAL_WITH_SYMBOL(Loose_left_edge_of_visible_workspace_area,Qloose_left_edge_of_visible_workspace_area,loose_left_edge_of_visible_workspace_area,
									    19);
								      PUSH_SPECIAL_WITH_SYMBOL(Current_image_plane,Qcurrent_image_plane,current_image_plane,
									      18);
									PUSH_SPECIAL_WITH_SYMBOL(Current_pane,Qcurrent_pane,current_pane,
										17);
									  outer_native_image_plane 
										  = 
										  Current_native_image_plane;
									  PUSH_SPECIAL_WITH_SYMBOL(Outer_native_image_plane,Qouter_native_image_plane,outer_native_image_plane,
										  16);
									    current_native_image_plane 
										    = 
										    image_plane;
									    PUSH_SPECIAL_WITH_SYMBOL(Current_native_image_plane,Qcurrent_native_image_plane,current_native_image_plane,
										    15);
									      if ( 
										      !EQ(Outer_native_image_plane,
										      Current_native_image_plane))
										  nip_begin_drawing(Current_native_image_plane);
									      color_or_metacolor 
										      = 
										      ISVREF(image_plane,
										      (SI_Long)5L) 
										      ?
										       
										      ISVREF(ISVREF(image_plane,
										      (SI_Long)5L),
										      (SI_Long)21L) 
										      :
										       
										      Nil;
									      if (color_or_metacolor);
									      else
										  color_or_metacolor 
											  = 
											  Qwhite;
									      if (EQ(color_or_metacolor,
										      Qtransparent) 
										      || 
										      EQ(color_or_metacolor,
										      Qbackground)) 
											  {
										  color_value 
											  = 
											  ISVREF(Current_color_map,
											  (SI_Long)5L);
										  if (color_value);
										  else
										      color_value 
											      = 
											      map_to_color_value_1(Qwhite);
									      }
									      else if (EQ(color_or_metacolor,
										      Qforeground) 
										      || 
										      EQ(color_or_metacolor,
										      Qworkspace_foreground)) 
											  {
										  temp 
											  = 
											  ISVREF(image_plane,
											  (SI_Long)5L) 
											  ?
											   
											  ISVREF(ISVREF(image_plane,
											  (SI_Long)5L),
											  (SI_Long)22L) 
											  :
											   
											  Nil;
										  if (temp);
										  else
										      temp 
											      = 
											      Qblack;
										  color_or_metacolor 
											  = 
											  temp;
										  if (EQ(color_or_metacolor,
											  Qtransparent) 
											  || 
											  EQ(color_or_metacolor,
											  Qbackground)) 
											      {
										      background_color_or_metacolor 
											      = 
											      ISVREF(image_plane,
											      (SI_Long)5L) 
											      ?
											       
											      ISVREF(ISVREF(image_plane,
											      (SI_Long)5L),
											      (SI_Long)21L) 
											      :
											       
											      Nil;
										      if (background_color_or_metacolor);
										      else
											  background_color_or_metacolor 
												  = 
												  Qwhite;
										      if (EQ(background_color_or_metacolor,
											      Qforeground) 
											      || 
											      EQ(background_color_or_metacolor,
											      Qworkspace_foreground)) 
												  {
											  color_value 
												  = 
												  ISVREF(Current_color_map,
												  (SI_Long)4L);
											  if (color_value);
											  else
											      color_value 
												      = 
												      map_to_color_value_1(Qblack);
										      }
										      else if (EQ(background_color_or_metacolor,
											      Qtransparent) 
											      || 
											      EQ(background_color_or_metacolor,
											      Qbackground)) 
												  {
											  color_value 
												  = 
												  ISVREF(Current_color_map,
												  (SI_Long)5L);
											  if (color_value);
											  else
											      color_value 
												      = 
												      map_to_color_value_1(Qwhite);
										      }
										      else
											  color_value 
												  = 
												  EQ(background_color_or_metacolor,
												  ISVREF(Current_color_map,
												  (SI_Long)6L)) 
												  ?
												   
												  ISVREF(Current_color_map,
												  (SI_Long)7L) 
												  :
												   
												  map_to_color_value_1(background_color_or_metacolor);
										  }
										  else if (EQ(color_or_metacolor,
											  Qforeground) 
											  || 
											  EQ(color_or_metacolor,
											  Qworkspace_foreground)) 
											      {
										      color_value 
											      = 
											      ISVREF(Current_color_map,
											      (SI_Long)4L);
										      if (color_value);
										      else
											  color_value 
												  = 
												  map_to_color_value_1(Qblack);
										  }
										  else
										      color_value 
											      = 
											      EQ(color_or_metacolor,
											      ISVREF(Current_color_map,
											      (SI_Long)6L)) 
											      ?
											       
											      ISVREF(Current_color_map,
											      (SI_Long)7L) 
											      :
											       
											      map_to_color_value_1(color_or_metacolor);
									      }
									      else
										  color_value 
											  = 
											  EQ(color_or_metacolor,
											  ISVREF(Current_color_map,
											  (SI_Long)6L)) 
											  ?
											   
											  ISVREF(Current_color_map,
											  (SI_Long)7L) 
											  :
											   
											  map_to_color_value_1(color_or_metacolor);
									      old_color_value 
										      = 
										      Current_background_color_value;
									      current_background_color_value 
										      = 
										      Current_background_color_value;
									      PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
										      14);
										set_current_background_color_value(color_value);
										left_edge_of_draw_area 
											= 
											Left_edge_of_draw_area;
										top_edge_of_draw_area 
											= 
											Top_edge_of_draw_area;
										right_edge_of_draw_area 
											= 
											Right_edge_of_draw_area;
										bottom_edge_of_draw_area 
											= 
											Bottom_edge_of_draw_area;
										PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
											13);
										  PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
											  12);
										    PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
											    11);
										      PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
											      10);
											temp 
												= 
												ISVREF(image_plane,
												(SI_Long)6L);
											Left_edge_of_draw_area 
												= 
												FIXNUM_MAX(temp,
												Left_edge_of_draw_area);
											temp 
												= 
												ISVREF(image_plane,
												(SI_Long)7L);
											Top_edge_of_draw_area 
												= 
												FIXNUM_MAX(temp,
												Top_edge_of_draw_area);
											temp 
												= 
												ISVREF(image_plane,
												(SI_Long)8L);
											Right_edge_of_draw_area 
												= 
												FIXNUM_MIN(temp,
												Right_edge_of_draw_area);
											temp 
												= 
												ISVREF(image_plane,
												(SI_Long)9L);
											Bottom_edge_of_draw_area 
												= 
												FIXNUM_MIN(temp,
												Bottom_edge_of_draw_area);
											if (FIXNUM_LT(Left_edge_of_draw_area,
												Right_edge_of_draw_area) 
												&& 
												FIXNUM_LT(Top_edge_of_draw_area,
												Bottom_edge_of_draw_area)) 
												    {
											    left_edge_of_draw_area 
												    = 
												    Left_edge_of_draw_area;
											    top_edge_of_draw_area 
												    = 
												    Top_edge_of_draw_area;
											    right_edge_of_draw_area 
												    = 
												    Right_edge_of_draw_area;
											    bottom_edge_of_draw_area 
												    = 
												    Bottom_edge_of_draw_area;
											    PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
												    9);
											      PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
												      8);
												PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
													7);
												  PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
													  6);
												    temp 
													    = 
													    ISVREF(image_plane,
													    (SI_Long)19L);
												    Left_edge_of_draw_area 
													    = 
													    FIXNUM_MAX(temp,
													    Left_edge_of_draw_area);
												    temp 
													    = 
													    ISVREF(image_plane,
													    (SI_Long)20L);
												    Top_edge_of_draw_area 
													    = 
													    FIXNUM_MAX(temp,
													    Top_edge_of_draw_area);
												    temp 
													    = 
													    ISVREF(image_plane,
													    (SI_Long)21L);
												    Right_edge_of_draw_area 
													    = 
													    FIXNUM_MIN(temp,
													    Right_edge_of_draw_area);
												    temp 
													    = 
													    ISVREF(image_plane,
													    (SI_Long)22L);
												    Bottom_edge_of_draw_area 
													    = 
													    FIXNUM_MIN(temp,
													    Bottom_edge_of_draw_area);
												    if (FIXNUM_LT(Left_edge_of_draw_area,
													    Right_edge_of_draw_area) 
													    && 
													    FIXNUM_LT(Top_edge_of_draw_area,
													    Bottom_edge_of_draw_area)) 
														{
													current_frame_transform_qm 
														= 
														Nil;
													current_image_x_scale 
														= 
														ISVREF(image_plane,
														(SI_Long)11L);
													current_image_y_scale 
														= 
														ISVREF(image_plane,
														(SI_Long)12L);
													current_x_origin_of_drawing 
														= 
														ISVREF(image_plane,
														(SI_Long)13L);
													current_y_origin_of_drawing 
														= 
														ISVREF(image_plane,
														(SI_Long)14L);
													PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
														5);
													  PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
														  4);
													    PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
														    3);
													      PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
														      2);
														PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
															1);
														  already_in_synch 
															  = 
															  EQ(Current_drawing_transfer_mode,
															  Kxor);
														  current_drawing_transfer_mode 
															  = 
															  Current_drawing_transfer_mode;
														  PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
															  0);
														    if ( 
															    !already_in_synch) 
																{
															Current_drawing_transfer_mode 
																= 
																Kxor;
															synchronize_transfer_mode();
														    }
														    tail 
															    = 
															    ISVREF(image_plane,
															    (SI_Long)27L);
														    cursor 
															    = 
															    Nil;
														    for ( 
															    ; 
															    !ENDP(tail); 
															    tail 
															    = 
															    CDR(tail)) 
																{
															cursor 
																= 
																CAR(tail);
															if (selection_highlight_cursor_p(cursor))
															    draw_selection_highlight(cursor);
														    }
														  POP_SPECIAL();
														  if ( 
															  !already_in_synch)
														      synchronize_transfer_mode();
														POP_SPECIAL();
													      POP_SPECIAL();
													    POP_SPECIAL();
													  POP_SPECIAL();
													POP_SPECIAL();
												    }
												  POP_SPECIAL();
												POP_SPECIAL();
											      POP_SPECIAL();
											    POP_SPECIAL();
											}
										      POP_SPECIAL();
										    POP_SPECIAL();
										  POP_SPECIAL();
										POP_SPECIAL();
										set_current_background_color_value(old_color_value);
									      POP_SPECIAL();
									      if ( 
										      !EQ(Outer_native_image_plane,
										      Current_native_image_plane))
										  nip_end_drawing(Current_native_image_plane);
									    POP_SPECIAL();
									    if (Current_native_image_plane) 
											{
										if ( 
											!EQ(image_plane,
											Current_native_image_plane))
										    SAVE_VALUES(nip_begin_drawing(Current_native_image_plane));
										else
										    SAVE_VALUES(VALUES_1(Nil));
									    }
									    else
										SAVE_VALUES(VALUES_1(Nil));
									  POP_SPECIAL();
									POP_SPECIAL();
								      POP_SPECIAL();
								    POP_SPECIAL();
								  POP_SPECIAL();
								POP_SPECIAL();
							      POP_SPECIAL();
							    POP_SPECIAL();
							}
							POP_UNWIND_PROTECT(0);
							UNLOCK(For_image_plane);
							CONTINUE_UNWINDING(0);
						    }
						    else
							SAVE_VALUES(VALUES_1(Qnil));
						  POP_SPECIAL();
					      }
					      POP_UNWIND_PROTECT(1);
					      UNLOCK(On_window_with_drawing);
					      CONTINUE_UNWINDING(1);
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
			POP_UNWIND_PROTECT(2);
			UNLOCK(On_window_without_drawing);
			CONTINUE_UNWINDING(2);
			result = RESTORE_VALUES();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

/* ERASE-AND-RECLAIM-ALL-SELECTION-HIGHLIGHTS */
Object erase_and_reclaim_all_selection_highlights(image_plane)
    Object image_plane;
{
    Object list_1, cursor, next_list;

    x_note_fn_call(128,90);
    if (ISVREF(image_plane,(SI_Long)27L)) {
	draw_or_erase_all_selection_highlights(image_plane);
	list_1 = ISVREF(image_plane,(SI_Long)27L);
	cursor = Nil;
	next_list = Nil;
      next_loop:
	cursor = CAR(list_1);
	next_list = CDR(list_1);
	if ( !TRUEP(list_1))
	    goto end_loop;
	if (selection_highlight_cursor_p(cursor)) {
	    remove_image_plane_cursor(image_plane,cursor);
	    reclaim_image_plane_cursor(cursor);
	}
	list_1 = next_list;
	goto next_loop;
      end_loop:
	return VALUES_1(Nil);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* DRAW-SELECTION-HIGHLIGHT */
Object draw_selection_highlight(cursor)
    Object cursor;
{
    Object color_or_metacolor, color_value_1;

    x_note_fn_call(128,91);
    color_or_metacolor = SECOND(cursor);
    if (EQ(color_or_metacolor,Qbackground))
	color_value_1 = Current_background_color_value;
    else if (EQ(color_or_metacolor,Qforeground) || EQ(color_or_metacolor,
	    Qworkspace_foreground))
	color_value_1 = Current_foreground_color_value;
    else if (EQ(color_or_metacolor,Qtransparent))
	color_value_1 = Current_background_color_value;
    else
	color_value_1 = map_to_color_value(color_or_metacolor);
    return draw_selection_highlight_1(cursor,FIXNUM_LOGXOR(color_value_1,
	    Current_background_color_value));
}

/* DRAW-SELECTION-HIGHLIGHT-1 */
Object draw_selection_highlight_1(cursor,color_difference)
    Object cursor, color_difference;
{
    Object points, thick, current_drawing_transfer_mode, scale, value, temp;
    Object temp_1, temp_2, x, y, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, window_points;
    SI_Long gensymed_symbol, gensymed_symbol_1, unshifted_result;
    SI_Long gensymed_symbol_2;
    char already_in_synch;
    Declare_stack_pointer;
    Declare_special(1);
    Object result;

    x_note_fn_call(128,92);
    SAVE_STACK();
    if (image_plane_selected_p(Current_image_plane)) {
	points = CDDR(cursor);
	thick = Selection_highlight_line_width;
	already_in_synch = EQ(Current_drawing_transfer_mode,Kxor);
	current_drawing_transfer_mode = Current_drawing_transfer_mode;
	PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
		0);
	  if ( !already_in_synch) {
	      Current_drawing_transfer_mode = Kxor;
	      synchronize_transfer_mode();
	  }
	  if ( !TRUEP(nthcdr(FIX((SI_Long)4L),points))) {
	      gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	      scale = Current_image_x_scale;
	      value = FIRST(points);
	      if (IFIX(scale) == (SI_Long)4096L)
		  gensymed_symbol_1 = IFIX(value);
	      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		      scale) && FIXNUM_LT(scale,
		      Isqrt_of_most_positive_fixnum) && 
		      FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		      value) && FIXNUM_LT(value,
			  Isqrt_of_most_positive_fixnum)) {
		  unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			  (SI_Long)2048L;
		  gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	      }
	      else
		  gensymed_symbol_1 = IFIX(scalef_function(scale,value));
	      gensymed_symbol = gensymed_symbol + gensymed_symbol_1;
	      gensymed_symbol_1 = IFIX(thick);
	      temp = FIX(gensymed_symbol - gensymed_symbol_1);
	      gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	      scale = Current_image_y_scale;
	      value = SECOND(points);
	      if (IFIX(scale) == (SI_Long)4096L)
		  gensymed_symbol_1 = IFIX(value);
	      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		      scale) && FIXNUM_LT(scale,
		      Isqrt_of_most_positive_fixnum) && 
		      FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		      value) && FIXNUM_LT(value,
			  Isqrt_of_most_positive_fixnum)) {
		  unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			  (SI_Long)2048L;
		  gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	      }
	      else
		  gensymed_symbol_1 = IFIX(scalef_function(scale,value));
	      gensymed_symbol = gensymed_symbol + gensymed_symbol_1;
	      gensymed_symbol_1 = IFIX(thick);
	      temp_1 = FIX(gensymed_symbol - gensymed_symbol_1);
	      gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	      scale = Current_image_x_scale;
	      value = THIRD(points);
	      if (IFIX(scale) == (SI_Long)4096L)
		  gensymed_symbol_1 = IFIX(value);
	      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		      scale) && FIXNUM_LT(scale,
		      Isqrt_of_most_positive_fixnum) && 
		      FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		      value) && FIXNUM_LT(value,
			  Isqrt_of_most_positive_fixnum)) {
		  unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			  (SI_Long)2048L;
		  gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	      }
	      else
		  gensymed_symbol_1 = IFIX(scalef_function(scale,value));
	      gensymed_symbol = gensymed_symbol + gensymed_symbol_1;
	      gensymed_symbol_1 = IFIX(thick);
	      gensymed_symbol_2 = (SI_Long)1L;
	      temp_2 = FIX(gensymed_symbol + gensymed_symbol_1 + 
		      gensymed_symbol_2);
	      gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	      scale = Current_image_y_scale;
	      value = FOURTH(points);
	      if (IFIX(scale) == (SI_Long)4096L)
		  gensymed_symbol_1 = IFIX(value);
	      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		      scale) && FIXNUM_LT(scale,
		      Isqrt_of_most_positive_fixnum) && 
		      FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		      value) && FIXNUM_LT(value,
			  Isqrt_of_most_positive_fixnum)) {
		  unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			  (SI_Long)2048L;
		  gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	      }
	      else
		  gensymed_symbol_1 = IFIX(scalef_function(scale,value));
	      gensymed_symbol = gensymed_symbol + gensymed_symbol_1;
	      gensymed_symbol_1 = IFIX(thick);
	      gensymed_symbol_2 = (SI_Long)1L;
	      SAVE_VALUES(draw_rectangle_outline_in_window(temp,temp_1,
		      temp_2,FIX(gensymed_symbol + gensymed_symbol_1 + 
		      gensymed_symbol_2),color_difference,thick,thick));
	  }
	  else {
	      x = Nil;
	      y = Nil;
	      ab_loop_list_ = points;
	      ab_loopvar_ = Nil;
	      ab_loopvar__1 = Nil;
	      ab_loopvar__2 = Nil;
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	    next_loop:
	      x = CAR(ab_loop_list_);
	      temp_2 = CDR(ab_loop_list_);
	      y = CAR(temp_2);
	      gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	      if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
		  gensymed_symbol_1 = IFIX(x);
	      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		      Current_image_x_scale) && 
		      FIXNUM_LT(Current_image_x_scale,
		      Isqrt_of_most_positive_fixnum) && 
		      FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x) 
		      && FIXNUM_LT(x,Isqrt_of_most_positive_fixnum)) {
		  unshifted_result = 
			  IFIX(FIXNUM_TIMES(Current_image_x_scale,x)) + 
			  (SI_Long)2048L;
		  gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	      }
	      else
		  gensymed_symbol_1 = 
			  IFIX(scalef_function(Current_image_x_scale,x));
	      ab_loopvar__2 = gensym_cons_1(FIX(gensymed_symbol + 
		      gensymed_symbol_1),Nil);
	      if (ab_loopvar__1)
		  M_CDR(ab_loopvar__1) = ab_loopvar__2;
	      else
		  ab_loopvar_ = ab_loopvar__2;
	      ab_loopvar__1 = ab_loopvar__2;
	      gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	      if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
		  gensymed_symbol_1 = IFIX(y);
	      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		      Current_image_y_scale) && 
		      FIXNUM_LT(Current_image_y_scale,
		      Isqrt_of_most_positive_fixnum) && 
		      FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y) 
		      && FIXNUM_LT(y,Isqrt_of_most_positive_fixnum)) {
		  unshifted_result = 
			  IFIX(FIXNUM_TIMES(Current_image_y_scale,y)) + 
			  (SI_Long)2048L;
		  gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	      }
	      else
		  gensymed_symbol_1 = 
			  IFIX(scalef_function(Current_image_y_scale,y));
	      ab_loopvar__2 = gensym_cons_1(FIX(gensymed_symbol + 
		      gensymed_symbol_1),Nil);
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
	      window_points = ab_loopvar_;
	      goto end_1;
	      window_points = Qnil;
	    end_1:;
	      draw_wide_polyline(window_points,color_difference,thick,Nil,Nil);
	      SAVE_VALUES(reclaim_gensym_list_1(window_points));
	  }
	POP_SPECIAL();
	if ( !already_in_synch)
	    synchronize_transfer_mode();
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

/* MOVE-ALL-SELECTION-HIGHLIGHTS */
Object move_all_selection_highlights(workspace,blocks,external_connections,
	    delta_x_in_workspace,delta_y_in_workspace)
    Object workspace, blocks, external_connections, delta_x_in_workspace;
    Object delta_y_in_workspace;
{
    Object block, ab_loop_list_, gensymed_symbol, ab_queue_form_;
    Object ab_next_queue_element_, subblock, scope_conses, ab_node_stack_;
    Object ab_current_node_, ab_skip_list_form_, ab_skip_list_p_;
    Object ab_next_node_, ab_tail_node_, ab_current_alist_, ab_entry_cons_;
    Object ab_connection_, ab_connection_item_, connection, temp;
    Object ab_less_than_branch_qm_;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(128,93);
    block = Nil;
    ab_loop_list_ = blocks;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    block = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    move_selection_highlights(block,workspace,delta_x_in_workspace,
	    delta_y_in_workspace);
    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    subblock = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = constant_queue_next(ISVREF(ab_queue_form_,
		(SI_Long)2L),ab_queue_form_);
  next_loop_1:
    if ( !TRUEP(ab_next_queue_element_))
	goto end_loop_1;
    subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
    ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	    ab_queue_form_);
    move_selection_highlights(subblock,workspace,delta_x_in_workspace,
	    delta_y_in_workspace);
    goto next_loop_1;
  end_loop_1:;
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)6L)) : Nil;
    ab_skip_list_form_ = gensymed_symbol;
    ab_skip_list_p_ = Nil;
    ab_next_node_ = Nil;
    ab_tail_node_ = Nil;
    ab_current_alist_ = Nil;
    ab_entry_cons_ = Nil;
    ab_connection_ = Nil;
    ab_connection_item_ = Nil;
    connection = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      gensymed_symbol = CDR(ab_skip_list_form_);
      if (CONSP(gensymed_symbol)) {
	  temp = M_CAR(gensymed_symbol);
	  temp_1 = SIMPLE_VECTOR_P(temp);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  temp = M_CDR(gensymed_symbol);
	  ab_skip_list_p_ = SIMPLE_VECTOR_P(temp) ? T : Nil;
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
      if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_ 
	      && EQ(ISVREF(ab_connection_,(SI_Long)3L),block))
	  goto end_1;
      goto next_loop_3;
    end_loop_3:
    end_1:
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_4;
      connection = ab_connection_;
      if ( !TRUEP(memq_function(connection,external_connections)))
	  move_selection_highlights(connection,workspace,
		  delta_x_in_workspace,delta_y_in_workspace);
      goto next_loop_2;
    end_loop_4:;
    POP_SPECIAL();
    goto next_loop;
  end_loop:;
    connection = Nil;
    ab_loop_list_ = external_connections;
  next_loop_5:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_5;
    connection = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    recompute_selection_highlights(connection);
    goto next_loop_5;
  end_loop_5:
    return VALUES_1(Qnil);
}

/* MOVE-SELECTION-HIGHLIGHTS */
Object move_selection_highlights(selectable,workspace,dx,dy)
    Object selectable, workspace, dx, dy;
{
    Object current_image_plane, ab_loop_list_, cursors, gensym_window;
    Object left_edge_of_draw_area, top_edge_of_draw_area;
    Object right_edge_of_draw_area, bottom_edge_of_draw_area;
    Object current_image_x_scale, current_image_y_scale;
    Object current_x_origin_of_drawing, current_y_origin_of_drawing, temp;
    Object current_frame_transform_qm, current_window_1, drawing_on_window;
    Object current_drawing_transfer_mode, type_of_current_window;
    Object current_native_window_qm, current_color_map;
    Object current_background_color_value, current_foreground_color_value;
    Object defer_notifications_qm, current_pane;
    Object loose_left_edge_of_visible_workspace_area;
    Object loose_top_edge_of_visible_workspace_area;
    Object loose_right_edge_of_visible_workspace_area;
    Object loose_bottom_edge_of_visible_workspace_area, color_or_metacolor;
    Object background_color_or_metacolor, outer_native_image_plane;
    Object current_native_image_plane, color_value, old_color_value, tail;
    Object cursor, icp_output_port_qm, icp_socket_qm, i_am_alive_info_qm;
    Object icp_output_port_qm_1, current_icp_port, current_icp_socket;
    Object disable_resumability, number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, aref_arg_1;
    char temp_1;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_stack_pointer;
    Declare_catch(3);
    Declare_special(54);
    Object result;

    x_note_fn_call(128,94);
    SAVE_STACK();
    current_image_plane = Nil;
    ab_loop_list_ = ISVREF(workspace,(SI_Long)16L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_image_plane,Qcurrent_image_plane,current_image_plane,
	    53);
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      Current_image_plane = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      if ( !TRUEP(printing_image_plane_p(Current_image_plane))) {
	  cursors = find_selection_highlights(selectable,Current_image_plane);
	  if (cursors) {
	      gensym_window = ISVREF(ISVREF(Current_image_plane,
		      (SI_Long)2L),(SI_Long)2L);
	      left_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)7L);
	      top_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)8L);
	      right_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)9L);
	      bottom_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)10L);
	      PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
		      52);
		PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
			51);
		  PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
			  50);
		    PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
			    49);
		      current_image_x_scale = FIX((SI_Long)4096L);
		      current_image_y_scale = FIX((SI_Long)4096L);
		      current_x_origin_of_drawing = FIX((SI_Long)0L);
		      current_y_origin_of_drawing = FIX((SI_Long)0L);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
			      48);
			PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
				47);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
				  46);
			    PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
				    45);
			      left_edge_of_draw_area = Left_edge_of_draw_area;
			      top_edge_of_draw_area = Top_edge_of_draw_area;
			      right_edge_of_draw_area = 
				      Right_edge_of_draw_area;
			      bottom_edge_of_draw_area = 
				      Bottom_edge_of_draw_area;
			      PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
				      44);
				PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
					43);
				  PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
					  42);
				    PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
					    41);
				      temp = ISVREF(Current_image_plane,
					      (SI_Long)6L);
				      Left_edge_of_draw_area = 
					      FIXNUM_MAX(temp,
					      Left_edge_of_draw_area);
				      temp = ISVREF(Current_image_plane,
					      (SI_Long)7L);
				      Top_edge_of_draw_area = 
					      FIXNUM_MAX(temp,
					      Top_edge_of_draw_area);
				      temp = ISVREF(Current_image_plane,
					      (SI_Long)8L);
				      Right_edge_of_draw_area = 
					      FIXNUM_MIN(temp,
					      Right_edge_of_draw_area);
				      temp = ISVREF(Current_image_plane,
					      (SI_Long)9L);
				      Bottom_edge_of_draw_area = 
					      FIXNUM_MIN(temp,
					      Bottom_edge_of_draw_area);
				      if (FIXNUM_LT(Left_edge_of_draw_area,
					      Right_edge_of_draw_area) && 
					      FIXNUM_LT(Top_edge_of_draw_area,
					      Bottom_edge_of_draw_area)) {
					  left_edge_of_draw_area = 
						  Left_edge_of_draw_area;
					  top_edge_of_draw_area = 
						  Top_edge_of_draw_area;
					  right_edge_of_draw_area = 
						  Right_edge_of_draw_area;
					  bottom_edge_of_draw_area = 
						  Bottom_edge_of_draw_area;
					  PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
						  40);
					    PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
						    39);
					      PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
						      38);
						PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
							37);
						  temp = 
							  ISVREF(Current_image_plane,
							  (SI_Long)19L);
						  Left_edge_of_draw_area = 
							  FIXNUM_MAX(temp,
							  Left_edge_of_draw_area);
						  temp = 
							  ISVREF(Current_image_plane,
							  (SI_Long)20L);
						  Top_edge_of_draw_area = 
							  FIXNUM_MAX(temp,
							  Top_edge_of_draw_area);
						  temp = 
							  ISVREF(Current_image_plane,
							  (SI_Long)21L);
						  Right_edge_of_draw_area 
							  = 
							  FIXNUM_MIN(temp,
							  Right_edge_of_draw_area);
						  temp = 
							  ISVREF(Current_image_plane,
							  (SI_Long)22L);
						  Bottom_edge_of_draw_area 
							  = 
							  FIXNUM_MIN(temp,
							  Bottom_edge_of_draw_area);
						  if (FIXNUM_LT(Left_edge_of_draw_area,
							  Right_edge_of_draw_area) 
							  && 
							  FIXNUM_LT(Top_edge_of_draw_area,
							  Bottom_edge_of_draw_area)) 
							      {
						      current_frame_transform_qm 
							      = Nil;
						      current_image_x_scale 
							      = 
							      ISVREF(Current_image_plane,
							      (SI_Long)11L);
						      current_image_y_scale 
							      = 
							      ISVREF(Current_image_plane,
							      (SI_Long)12L);
						      current_x_origin_of_drawing 
							      = 
							      ISVREF(Current_image_plane,
							      (SI_Long)13L);
						      current_y_origin_of_drawing 
							      = 
							      ISVREF(Current_image_plane,
							      (SI_Long)14L);
						      PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
							      36);
							PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
								35);
							  PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
								  34);
							    PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
								    33);
							      PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
								      32);
								LOCK(On_window_without_drawing);
								if (PUSH_UNWIND_PROTECT(2)) 
									    {
								    current_window_1 
									    = 
									    ISVREF(ISVREF(Current_image_plane,
									    (SI_Long)2L),
									    (SI_Long)2L);
								    PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
									    31);
								      drawing_on_window 
									      = 
									      Nil;
								      PUSH_SPECIAL_WITH_SYMBOL(Drawing_on_window,Qdrawing_on_window,drawing_on_window,
									      30);
									current_drawing_transfer_mode 
										= 
										EQ(Current_drawing_transfer_mode,
										Kxor) 
										?
										 
										Current_drawing_transfer_mode 
										:
										 
										ISVREF(Current_window,
										(SI_Long)30L);
									PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
										29);
									  type_of_current_window 
										  = 
										  ISVREF(Current_window,
										  (SI_Long)1L);
									  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
										  28);
									    current_native_window_qm 
										    = 
										    ISVREF(Current_window,
										    (SI_Long)17L);
									    PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
										    27);
									      current_color_map 
										      = 
										      ISVREF(Current_window,
										      (SI_Long)20L);
									      PUSH_SPECIAL_WITH_SYMBOL(Current_color_map,Qcurrent_color_map,current_color_map,
										      26);
										temp 
											= 
											ISVREF(Current_color_map,
											(SI_Long)5L);
										if (temp);
										else
										    temp 
											    = 
											    map_to_color_value_1(Qwhite);
										current_background_color_value 
											= 
											temp;
										PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
											25);
										  temp 
											  = 
											  ISVREF(Current_color_map,
											  (SI_Long)4L);
										  if (temp);
										  else
										      temp 
											      = 
											      map_to_color_value_1(Qblack);
										  current_foreground_color_value 
											  = 
											  temp;
										  PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
											  24);
										    defer_notifications_qm 
											    = 
											    T;
										    PUSH_SPECIAL_WITH_SYMBOL(Defer_notifications_qm,Qdefer_notifications_qm,defer_notifications_qm,
											    23);
										      LOCK(On_window_with_drawing);
										      if (PUSH_UNWIND_PROTECT(1)) 
												  {
											  drawing_on_window 
												  = 
												  T;
											  PUSH_SPECIAL_WITH_SYMBOL(Drawing_on_window,Qdrawing_on_window,drawing_on_window,
												  22);
											    if (EQ(Type_of_current_window,
												    Qx11_window)) 
													{
												LOCK(For_image_plane);
												if (PUSH_UNWIND_PROTECT(0)) 
													    {
												    current_pane 
													    = 
													    ISVREF(Current_image_plane,
													    (SI_Long)2L);
												    current_image_plane 
													    = 
													    Current_image_plane;
												    loose_left_edge_of_visible_workspace_area 
													    = 
													    ISVREF(Current_image_plane,
													    (SI_Long)23L);
												    loose_top_edge_of_visible_workspace_area 
													    = 
													    ISVREF(Current_image_plane,
													    (SI_Long)24L);
												    loose_right_edge_of_visible_workspace_area 
													    = 
													    ISVREF(Current_image_plane,
													    (SI_Long)25L);
												    loose_bottom_edge_of_visible_workspace_area 
													    = 
													    ISVREF(Current_image_plane,
													    (SI_Long)26L);
												    color_or_metacolor 
													    = 
													    ISVREF(Current_image_plane,
													    (SI_Long)5L) 
													    ?
													     
													    ISVREF(ISVREF(Current_image_plane,
													    (SI_Long)5L),
													    (SI_Long)22L) 
													    :
													     
													    Nil;
												    if (color_or_metacolor);
												    else
													color_or_metacolor 
														= 
														Qblack;
												    if (EQ(color_or_metacolor,
													    Qtransparent) 
													    || 
													    EQ(color_or_metacolor,
													    Qbackground)) 
														{
													background_color_or_metacolor 
														= 
														ISVREF(Current_image_plane,
														(SI_Long)5L) 
														?
														 
														ISVREF(ISVREF(Current_image_plane,
														(SI_Long)5L),
														(SI_Long)21L) 
														:
														 
														Nil;
													if (background_color_or_metacolor);
													else
													    background_color_or_metacolor 
														    = 
														    Qwhite;
													if (EQ(background_color_or_metacolor,
														Qforeground) 
														|| 
														EQ(background_color_or_metacolor,
														Qworkspace_foreground)) 
														    {
													    temp 
														    = 
														    ISVREF(Current_color_map,
														    (SI_Long)4L);
													    if (temp);
													    else
														temp 
															= 
															map_to_color_value_1(Qblack);
													    current_foreground_color_value 
														    = 
														    temp;
													}
													else if (EQ(background_color_or_metacolor,
														Qtransparent) 
														|| 
														EQ(background_color_or_metacolor,
														Qbackground)) 
														    {
													    temp 
														    = 
														    ISVREF(Current_color_map,
														    (SI_Long)5L);
													    if (temp);
													    else
														temp 
															= 
															map_to_color_value_1(Qwhite);
													    current_foreground_color_value 
														    = 
														    temp;
													}
													else
													    current_foreground_color_value 
														    = 
														    EQ(background_color_or_metacolor,
														    ISVREF(Current_color_map,
														    (SI_Long)6L)) 
														    ?
														     
														    ISVREF(Current_color_map,
														    (SI_Long)7L) 
														    :
														     
														    map_to_color_value_1(background_color_or_metacolor);
												    }
												    else if (EQ(color_or_metacolor,
													    Qforeground) 
													    || 
													    EQ(color_or_metacolor,
													    Qworkspace_foreground)) 
														{
													temp 
														= 
														ISVREF(Current_color_map,
														(SI_Long)4L);
													if (temp);
													else
													    temp 
														    = 
														    map_to_color_value_1(Qblack);
													current_foreground_color_value 
														= 
														temp;
												    }
												    else
													current_foreground_color_value 
														= 
														EQ(color_or_metacolor,
														ISVREF(Current_color_map,
														(SI_Long)6L)) 
														?
														 
														ISVREF(Current_color_map,
														(SI_Long)7L) 
														:
														 
														map_to_color_value_1(color_or_metacolor);
												    PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
													    9);
												      PUSH_SPECIAL_WITH_SYMBOL(Loose_bottom_edge_of_visible_workspace_area,Qloose_bottom_edge_of_visible_workspace_area,loose_bottom_edge_of_visible_workspace_area,
													      8);
													PUSH_SPECIAL_WITH_SYMBOL(Loose_right_edge_of_visible_workspace_area,Qloose_right_edge_of_visible_workspace_area,loose_right_edge_of_visible_workspace_area,
														7);
													  PUSH_SPECIAL_WITH_SYMBOL(Loose_top_edge_of_visible_workspace_area,Qloose_top_edge_of_visible_workspace_area,loose_top_edge_of_visible_workspace_area,
														  6);
													    PUSH_SPECIAL_WITH_SYMBOL(Loose_left_edge_of_visible_workspace_area,Qloose_left_edge_of_visible_workspace_area,loose_left_edge_of_visible_workspace_area,
														    5);
													      PUSH_SPECIAL_WITH_SYMBOL(Current_image_plane,Qcurrent_image_plane,current_image_plane,
														      4);
														PUSH_SPECIAL_WITH_SYMBOL(Current_pane,Qcurrent_pane,current_pane,
															3);
														  outer_native_image_plane 
															  = 
															  Current_native_image_plane;
														  PUSH_SPECIAL_WITH_SYMBOL(Outer_native_image_plane,Qouter_native_image_plane,outer_native_image_plane,
															  2);
														    current_native_image_plane 
															    = 
															    Current_image_plane;
														    PUSH_SPECIAL_WITH_SYMBOL(Current_native_image_plane,Qcurrent_native_image_plane,current_native_image_plane,
															    1);
														      if ( 
															      !EQ(Outer_native_image_plane,
															      Current_native_image_plane))
															  nip_begin_drawing(Current_native_image_plane);
														      color_or_metacolor 
															      = 
															      ISVREF(Current_image_plane,
															      (SI_Long)5L) 
															      ?
															       
															      ISVREF(ISVREF(Current_image_plane,
															      (SI_Long)5L),
															      (SI_Long)21L) 
															      :
															       
															      Nil;
														      if (color_or_metacolor);
														      else
															  color_or_metacolor 
																  = 
																  Qwhite;
														      if (EQ(color_or_metacolor,
															      Qtransparent) 
															      || 
															      EQ(color_or_metacolor,
															      Qbackground)) 
																  {
															  color_value 
																  = 
																  ISVREF(Current_color_map,
																  (SI_Long)5L);
															  if (color_value);
															  else
															      color_value 
																      = 
																      map_to_color_value_1(Qwhite);
														      }
														      else if (EQ(color_or_metacolor,
															      Qforeground) 
															      || 
															      EQ(color_or_metacolor,
															      Qworkspace_foreground)) 
																  {
															  temp 
																  = 
																  ISVREF(Current_image_plane,
																  (SI_Long)5L) 
																  ?
																   
																  ISVREF(ISVREF(Current_image_plane,
																  (SI_Long)5L),
																  (SI_Long)22L) 
																  :
																   
																  Nil;
															  if (temp);
															  else
															      temp 
																      = 
																      Qblack;
															  color_or_metacolor 
																  = 
																  temp;
															  if (EQ(color_or_metacolor,
																  Qtransparent) 
																  || 
																  EQ(color_or_metacolor,
																  Qbackground)) 
																      {
															      background_color_or_metacolor 
																      = 
																      ISVREF(Current_image_plane,
																      (SI_Long)5L) 
																      ?
																       
																      ISVREF(ISVREF(Current_image_plane,
																      (SI_Long)5L),
																      (SI_Long)21L) 
																      :
																       
																      Nil;
															      if (background_color_or_metacolor);
															      else
																  background_color_or_metacolor 
																	  = 
																	  Qwhite;
															      if (EQ(background_color_or_metacolor,
																      Qforeground) 
																      || 
																      EQ(background_color_or_metacolor,
																      Qworkspace_foreground)) 
																	  {
																  color_value 
																	  = 
																	  ISVREF(Current_color_map,
																	  (SI_Long)4L);
																  if (color_value);
																  else
																      color_value 
																	      = 
																	      map_to_color_value_1(Qblack);
															      }
															      else if (EQ(background_color_or_metacolor,
																      Qtransparent) 
																      || 
																      EQ(background_color_or_metacolor,
																      Qbackground)) 
																	  {
																  color_value 
																	  = 
																	  ISVREF(Current_color_map,
																	  (SI_Long)5L);
																  if (color_value);
																  else
																      color_value 
																	      = 
																	      map_to_color_value_1(Qwhite);
															      }
															      else
																  color_value 
																	  = 
																	  EQ(background_color_or_metacolor,
																	  ISVREF(Current_color_map,
																	  (SI_Long)6L)) 
																	  ?
																	   
																	  ISVREF(Current_color_map,
																	  (SI_Long)7L) 
																	  :
																	   
																	  map_to_color_value_1(background_color_or_metacolor);
															  }
															  else if (EQ(color_or_metacolor,
																  Qforeground) 
																  || 
																  EQ(color_or_metacolor,
																  Qworkspace_foreground)) 
																      {
															      color_value 
																      = 
																      ISVREF(Current_color_map,
																      (SI_Long)4L);
															      if (color_value);
															      else
																  color_value 
																	  = 
																	  map_to_color_value_1(Qblack);
															  }
															  else
															      color_value 
																      = 
																      EQ(color_or_metacolor,
																      ISVREF(Current_color_map,
																      (SI_Long)6L)) 
																      ?
																       
																      ISVREF(Current_color_map,
																      (SI_Long)7L) 
																      :
																       
																      map_to_color_value_1(color_or_metacolor);
														      }
														      else
															  color_value 
																  = 
																  EQ(color_or_metacolor,
																  ISVREF(Current_color_map,
																  (SI_Long)6L)) 
																  ?
																   
																  ISVREF(Current_color_map,
																  (SI_Long)7L) 
																  :
																   
																  map_to_color_value_1(color_or_metacolor);
														      old_color_value 
															      = 
															      Current_background_color_value;
														      current_background_color_value 
															      = 
															      Current_background_color_value;
														      PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
															      0);
															set_current_background_color_value(color_value);
															tail 
																= 
																cursors;
															cursor 
																= 
																Nil;
															for ( 
																; 
																!ENDP(tail); 
																tail 
																= 
																CDR(tail)) 
																    {
															    cursor 
																    = 
																    CAR(tail);
															    move_selection_highlight(cursor,
																    dx,
																    dy);
															}
															set_current_background_color_value(old_color_value);
														      POP_SPECIAL();
														      if ( 
															      !EQ(Outer_native_image_plane,
															      Current_native_image_plane))
															  nip_end_drawing(Current_native_image_plane);
														    POP_SPECIAL();
														    if (Current_native_image_plane) 
																{
															if ( 
																!EQ(Current_image_plane,
																Current_native_image_plane))
															    nip_begin_drawing(Current_native_image_plane);
														    }
														  POP_SPECIAL();
														POP_SPECIAL();
													      POP_SPECIAL();
													    POP_SPECIAL();
													  POP_SPECIAL();
													POP_SPECIAL();
												      POP_SPECIAL();
												    POP_SPECIAL();
												}
												POP_UNWIND_PROTECT(0);
												UNLOCK(For_image_plane);
												CONTINUE_UNWINDING(0);
												if (Flush_graphics_immediately_qm)
												    sync_graphics_on_current_window();
											    }
											    else if (EQ(Type_of_current_window,
												    Qicp)) 
													{
												icp_output_port_qm 
													= 
													ISVREF(Current_window,
													(SI_Long)12L);
												icp_socket_qm 
													= 
													icp_output_port_qm 
													?
													 
													ISVREF(icp_output_port_qm,
													(SI_Long)2L) 
													:
													 
													Qnil;
												if (icp_socket_qm) 
													    {
												    i_am_alive_info_qm 
													    = 
													    ISVREF(icp_socket_qm,
													    (SI_Long)24L);
												    temp_1 
													    = 
													     
													    !TRUEP(i_am_alive_info_qm);
												    if (temp_1);
												    else
													temp_1 
														= 
														 
														!TRUEP(Do_icp_flow_control_qm);
												    if (temp_1);
												    else
													temp_1 
														= 
														 
														!TRUEP(ISVREF(i_am_alive_info_qm,
														(SI_Long)2L));
												}
												else
												    temp_1 
													    = 
													    TRUEP(Nil);
												if (temp_1) 
													    {
												    icp_output_port_qm_1 
													    = 
													    ISVREF(Current_window,
													    (SI_Long)12L);
												    if (icp_output_port_qm_1 
													    && 
													    icp_connection_open_p(ISVREF(icp_output_port_qm_1,
													    (SI_Long)2L))) 
														{
													current_icp_port 
														= 
														icp_output_port_qm_1;
													PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
														21);
													  current_icp_socket 
														  = 
														  ISVREF(Current_icp_port,
														  (SI_Long)2L);
													  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
														  20);
													    temp 
														    = 
														    IFIX(ISVREF(Current_icp_socket,
														    (SI_Long)22L)) 
														    >= 
														    (SI_Long)17L 
														    ?
														     
														    ISVREF(Current_icp_socket,
														    (SI_Long)53L) 
														    :
														     
														    Nil;
													    if (temp);
													    else
														temp 
															= 
															EQ(ISVREF(Current_icp_socket,
															(SI_Long)25L),
															Qtelewindows) 
															?
															 T : Nil;
													    disable_resumability 
														    = 
														    temp;
													    PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
														    19);
													      number_of_icp_bytes_for_message_series 
														      = 
														      FIX((SI_Long)0L);
													      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
														      18);
														icp_buffers_for_message_group 
															= 
															Nil;
														PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
															17);
														  icp_buffer_of_start_of_message_series_qm 
															  = 
															  Nil;
														  PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
															  16);
														    icp_byte_position_of_start_of_message_series_qm 
															    = 
															    Nil;
														    PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
															    15);
														      number_of_icp_bytes_to_fill_buffer 
															      = 
															      FIX((SI_Long)0L);
														      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
															      14);
															current_icp_buffer 
																= 
																Nil;
															PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
																13);
															  current_write_icp_byte_position 
																  = 
																  Nil;
															  PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
																  12);
															    number_of_icp_bytes_in_message_group 
																    = 
																    FIX((SI_Long)0L);
															    PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
																    11);
															      writing_icp_message_group 
																      = 
																      FIXNUM_ADD1(Writing_icp_message_group);
															      PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
																      10);
																gensymed_symbol 
																	= 
																	Nil;
																gensymed_symbol_1 
																	= 
																	0.0;
																gensymed_symbol_2 
																	= 
																	0.0;
																if (Profiling_enabled_qm) 
																	    {
																    gensymed_symbol 
																	    = 
																	    T;
																    gensymed_symbol_1 
																	    = 
																	    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
																	    (SI_Long)2L),
																	    (SI_Long)0L);
																    gensymed_symbol_2 
																	    = 
																	    g2ext_unix_time_as_float();
																    aref_arg_1 
																	    = 
																	    ISVREF(Profiling_enabled_qm,
																	    (SI_Long)2L);
																    DFLOAT_ISASET_1(aref_arg_1,
																	    (SI_Long)0L,
																	    gensymed_symbol_2);
																}
																if (icp_connection_open_p(Current_icp_socket) 
																	&& 
																	 
																	!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
																	    {
																    synchronize_icp_on_window_with_drawing(Current_window,
																	    Left_edge_of_draw_area,
																	    Top_edge_of_draw_area,
																	    Right_edge_of_draw_area,
																	    Bottom_edge_of_draw_area);
																    LOCK(For_image_plane);
																    if (PUSH_UNWIND_PROTECT(0)) 
																		{
																	current_pane 
																		= 
																		ISVREF(Current_image_plane,
																		(SI_Long)2L);
																	current_image_plane 
																		= 
																		Current_image_plane;
																	loose_left_edge_of_visible_workspace_area 
																		= 
																		ISVREF(Current_image_plane,
																		(SI_Long)23L);
																	loose_top_edge_of_visible_workspace_area 
																		= 
																		ISVREF(Current_image_plane,
																		(SI_Long)24L);
																	loose_right_edge_of_visible_workspace_area 
																		= 
																		ISVREF(Current_image_plane,
																		(SI_Long)25L);
																	loose_bottom_edge_of_visible_workspace_area 
																		= 
																		ISVREF(Current_image_plane,
																		(SI_Long)26L);
																	color_or_metacolor 
																		= 
																		ISVREF(Current_image_plane,
																		(SI_Long)5L) 
																		?
																		 
																		ISVREF(ISVREF(Current_image_plane,
																		(SI_Long)5L),
																		(SI_Long)22L) 
																		:
																		 
																		Nil;
																	if (color_or_metacolor);
																	else
																	    color_or_metacolor 
																		    = 
																		    Qblack;
																	if (EQ(color_or_metacolor,
																		Qtransparent) 
																		|| 
																		EQ(color_or_metacolor,
																		Qbackground)) 
																		    {
																	    background_color_or_metacolor 
																		    = 
																		    ISVREF(Current_image_plane,
																		    (SI_Long)5L) 
																		    ?
																		     
																		    ISVREF(ISVREF(Current_image_plane,
																		    (SI_Long)5L),
																		    (SI_Long)21L) 
																		    :
																		     
																		    Nil;
																	    if (background_color_or_metacolor);
																	    else
																		background_color_or_metacolor 
																			= 
																			Qwhite;
																	    if (EQ(background_color_or_metacolor,
																		    Qforeground) 
																		    || 
																		    EQ(background_color_or_metacolor,
																		    Qworkspace_foreground)) 
																			{
																		temp 
																			= 
																			ISVREF(Current_color_map,
																			(SI_Long)4L);
																		if (temp);
																		else
																		    temp 
																			    = 
																			    map_to_color_value_1(Qblack);
																		current_foreground_color_value 
																			= 
																			temp;
																	    }
																	    else if (EQ(background_color_or_metacolor,
																		    Qtransparent) 
																		    || 
																		    EQ(background_color_or_metacolor,
																		    Qbackground)) 
																			{
																		temp 
																			= 
																			ISVREF(Current_color_map,
																			(SI_Long)5L);
																		if (temp);
																		else
																		    temp 
																			    = 
																			    map_to_color_value_1(Qwhite);
																		current_foreground_color_value 
																			= 
																			temp;
																	    }
																	    else
																		current_foreground_color_value 
																			= 
																			EQ(background_color_or_metacolor,
																			ISVREF(Current_color_map,
																			(SI_Long)6L)) 
																			?
																			 
																			ISVREF(Current_color_map,
																			(SI_Long)7L) 
																			:
																			 
																			map_to_color_value_1(background_color_or_metacolor);
																	}
																	else if (EQ(color_or_metacolor,
																		Qforeground) 
																		|| 
																		EQ(color_or_metacolor,
																		Qworkspace_foreground)) 
																		    {
																	    temp 
																		    = 
																		    ISVREF(Current_color_map,
																		    (SI_Long)4L);
																	    if (temp);
																	    else
																		temp 
																			= 
																			map_to_color_value_1(Qblack);
																	    current_foreground_color_value 
																		    = 
																		    temp;
																	}
																	else
																	    current_foreground_color_value 
																		    = 
																		    EQ(color_or_metacolor,
																		    ISVREF(Current_color_map,
																		    (SI_Long)6L)) 
																		    ?
																		     
																		    ISVREF(Current_color_map,
																		    (SI_Long)7L) 
																		    :
																		     
																		    map_to_color_value_1(color_or_metacolor);
																	PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
																		9);
																	  PUSH_SPECIAL_WITH_SYMBOL(Loose_bottom_edge_of_visible_workspace_area,Qloose_bottom_edge_of_visible_workspace_area,loose_bottom_edge_of_visible_workspace_area,
																		  8);
																	    PUSH_SPECIAL_WITH_SYMBOL(Loose_right_edge_of_visible_workspace_area,Qloose_right_edge_of_visible_workspace_area,loose_right_edge_of_visible_workspace_area,
																		    7);
																	      PUSH_SPECIAL_WITH_SYMBOL(Loose_top_edge_of_visible_workspace_area,Qloose_top_edge_of_visible_workspace_area,loose_top_edge_of_visible_workspace_area,
																		      6);
																		PUSH_SPECIAL_WITH_SYMBOL(Loose_left_edge_of_visible_workspace_area,Qloose_left_edge_of_visible_workspace_area,loose_left_edge_of_visible_workspace_area,
																			5);
																		  PUSH_SPECIAL_WITH_SYMBOL(Current_image_plane,Qcurrent_image_plane,current_image_plane,
																			  4);
																		    PUSH_SPECIAL_WITH_SYMBOL(Current_pane,Qcurrent_pane,current_pane,
																			    3);
																		      outer_native_image_plane 
																			      = 
																			      Current_native_image_plane;
																		      PUSH_SPECIAL_WITH_SYMBOL(Outer_native_image_plane,Qouter_native_image_plane,outer_native_image_plane,
																			      2);
																			current_native_image_plane 
																				= 
																				Current_image_plane;
																			PUSH_SPECIAL_WITH_SYMBOL(Current_native_image_plane,Qcurrent_native_image_plane,current_native_image_plane,
																				1);
																			  if ( 
																				  !EQ(Outer_native_image_plane,
																				  Current_native_image_plane))
																			      nip_begin_drawing(Current_native_image_plane);
																			  color_or_metacolor 
																				  = 
																				  ISVREF(Current_image_plane,
																				  (SI_Long)5L) 
																				  ?
																				   
																				  ISVREF(ISVREF(Current_image_plane,
																				  (SI_Long)5L),
																				  (SI_Long)21L) 
																				  :
																				   
																				  Nil;
																			  if (color_or_metacolor);
																			  else
																			      color_or_metacolor 
																				      = 
																				      Qwhite;
																			  if (EQ(color_or_metacolor,
																				  Qtransparent) 
																				  || 
																				  EQ(color_or_metacolor,
																				  Qbackground)) 
																				      {
																			      color_value 
																				      = 
																				      ISVREF(Current_color_map,
																				      (SI_Long)5L);
																			      if (color_value);
																			      else
																				  color_value 
																					  = 
																					  map_to_color_value_1(Qwhite);
																			  }
																			  else if (EQ(color_or_metacolor,
																				  Qforeground) 
																				  || 
																				  EQ(color_or_metacolor,
																				  Qworkspace_foreground)) 
																				      {
																			      temp 
																				      = 
																				      ISVREF(Current_image_plane,
																				      (SI_Long)5L) 
																				      ?
																				       
																				      ISVREF(ISVREF(Current_image_plane,
																				      (SI_Long)5L),
																				      (SI_Long)22L) 
																				      :
																				       
																				      Nil;
																			      if (temp);
																			      else
																				  temp 
																					  = 
																					  Qblack;
																			      color_or_metacolor 
																				      = 
																				      temp;
																			      if (EQ(color_or_metacolor,
																				      Qtransparent) 
																				      || 
																				      EQ(color_or_metacolor,
																				      Qbackground)) 
																					  {
																				  background_color_or_metacolor 
																					  = 
																					  ISVREF(Current_image_plane,
																					  (SI_Long)5L) 
																					  ?
																					   
																					  ISVREF(ISVREF(Current_image_plane,
																					  (SI_Long)5L),
																					  (SI_Long)21L) 
																					  :
																					   
																					  Nil;
																				  if (background_color_or_metacolor);
																				  else
																				      background_color_or_metacolor 
																					      = 
																					      Qwhite;
																				  if (EQ(background_color_or_metacolor,
																					  Qforeground) 
																					  || 
																					  EQ(background_color_or_metacolor,
																					  Qworkspace_foreground)) 
																					      {
																				      color_value 
																					      = 
																					      ISVREF(Current_color_map,
																					      (SI_Long)4L);
																				      if (color_value);
																				      else
																					  color_value 
																						  = 
																						  map_to_color_value_1(Qblack);
																				  }
																				  else if (EQ(background_color_or_metacolor,
																					  Qtransparent) 
																					  || 
																					  EQ(background_color_or_metacolor,
																					  Qbackground)) 
																					      {
																				      color_value 
																					      = 
																					      ISVREF(Current_color_map,
																					      (SI_Long)5L);
																				      if (color_value);
																				      else
																					  color_value 
																						  = 
																						  map_to_color_value_1(Qwhite);
																				  }
																				  else
																				      color_value 
																					      = 
																					      EQ(background_color_or_metacolor,
																					      ISVREF(Current_color_map,
																					      (SI_Long)6L)) 
																					      ?
																					       
																					      ISVREF(Current_color_map,
																					      (SI_Long)7L) 
																					      :
																					       
																					      map_to_color_value_1(background_color_or_metacolor);
																			      }
																			      else if (EQ(color_or_metacolor,
																				      Qforeground) 
																				      || 
																				      EQ(color_or_metacolor,
																				      Qworkspace_foreground)) 
																					  {
																				  color_value 
																					  = 
																					  ISVREF(Current_color_map,
																					  (SI_Long)4L);
																				  if (color_value);
																				  else
																				      color_value 
																					      = 
																					      map_to_color_value_1(Qblack);
																			      }
																			      else
																				  color_value 
																					  = 
																					  EQ(color_or_metacolor,
																					  ISVREF(Current_color_map,
																					  (SI_Long)6L)) 
																					  ?
																					   
																					  ISVREF(Current_color_map,
																					  (SI_Long)7L) 
																					  :
																					   
																					  map_to_color_value_1(color_or_metacolor);
																			  }
																			  else
																			      color_value 
																				      = 
																				      EQ(color_or_metacolor,
																				      ISVREF(Current_color_map,
																				      (SI_Long)6L)) 
																				      ?
																				       
																				      ISVREF(Current_color_map,
																				      (SI_Long)7L) 
																				      :
																				       
																				      map_to_color_value_1(color_or_metacolor);
																			  old_color_value 
																				  = 
																				  Current_background_color_value;
																			  current_background_color_value 
																				  = 
																				  Current_background_color_value;
																			  PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
																				  0);
																			    set_current_background_color_value(color_value);
																			    tail 
																				    = 
																				    cursors;
																			    cursor 
																				    = 
																				    Nil;
																			    for ( 
																				    ; 
																				    !ENDP(tail); 
																				    tail 
																				    = 
																				    CDR(tail)) 
																					{
																				cursor 
																					= 
																					CAR(tail);
																				move_selection_highlight(cursor,
																					dx,
																					dy);
																			    }
																			    set_current_background_color_value(old_color_value);
																			  POP_SPECIAL();
																			  if ( 
																				  !EQ(Outer_native_image_plane,
																				  Current_native_image_plane))
																			      nip_end_drawing(Current_native_image_plane);
																			POP_SPECIAL();
																			if (Current_native_image_plane) 
																				    {
																			    if ( 
																				    !EQ(Current_image_plane,
																				    Current_native_image_plane))
																				nip_begin_drawing(Current_native_image_plane);
																			}
																		      POP_SPECIAL();
																		    POP_SPECIAL();
																		  POP_SPECIAL();
																		POP_SPECIAL();
																	      POP_SPECIAL();
																	    POP_SPECIAL();
																	  POP_SPECIAL();
																	POP_SPECIAL();
																    }
																    POP_UNWIND_PROTECT(0);
																    UNLOCK(For_image_plane);
																    CONTINUE_UNWINDING(0);
																    if (Flush_graphics_immediately_qm 
																	    && 
																	    FIXNUM_NE(ISVREF(Current_icp_socket,
																	    (SI_Long)15L),
																	    Icp_connection_closed))
																	sync_graphics_on_current_window();
																    end_icp_message_group();
																}
																if (Profiling_enabled_qm) 
																	    {
																    gensymed_symbol_3 
																	    = 
																	    g2ext_unix_time_as_float();
																    gensymed_symbol_4 
																	    = 
																	    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
																	    (SI_Long)2L),
																	    (SI_Long)0L);
																    gensymed_symbol_5 
																	    = 
																	    gensymed_symbol_3 
																	    - 
																	    gensymed_symbol_4;
																    aref_arg_1 
																	    = 
																	    ISVREF(Profiling_enabled_qm,
																	    (SI_Long)6L);
																    aref_new_value 
																	    = 
																	    gensymed_symbol_5 
																	    + 
																	    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
																	    (SI_Long)6L),
																	    (SI_Long)0L);
																    DFLOAT_ISASET_1(aref_arg_1,
																	    (SI_Long)0L,
																	    aref_new_value);
																    aref_arg_1 
																	    = 
																	    ISVREF(Profiling_enabled_qm,
																	    (SI_Long)2L);
																    aref_new_value 
																	    = 
																	    gensymed_symbol 
																	    ?
																	     
																	    gensymed_symbol_1 
																	    + 
																	    gensymed_symbol_5 
																	    + 
																	    (gensymed_symbol_4 
																	    - 
																	    gensymed_symbol_2) 
																	    :
																	     
																	    gensymed_symbol_3;
																    DFLOAT_ISASET_1(aref_arg_1,
																	    (SI_Long)0L,
																	    aref_new_value);
																}
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
											    }
											    else if (EQ(Type_of_current_window,
												    Qprinter)) 
													{
												LOCK(For_image_plane);
												if (PUSH_UNWIND_PROTECT(0)) 
													    {
												    current_pane 
													    = 
													    ISVREF(Current_image_plane,
													    (SI_Long)2L);
												    current_image_plane 
													    = 
													    Current_image_plane;
												    loose_left_edge_of_visible_workspace_area 
													    = 
													    ISVREF(Current_image_plane,
													    (SI_Long)23L);
												    loose_top_edge_of_visible_workspace_area 
													    = 
													    ISVREF(Current_image_plane,
													    (SI_Long)24L);
												    loose_right_edge_of_visible_workspace_area 
													    = 
													    ISVREF(Current_image_plane,
													    (SI_Long)25L);
												    loose_bottom_edge_of_visible_workspace_area 
													    = 
													    ISVREF(Current_image_plane,
													    (SI_Long)26L);
												    color_or_metacolor 
													    = 
													    ISVREF(Current_image_plane,
													    (SI_Long)5L) 
													    ?
													     
													    ISVREF(ISVREF(Current_image_plane,
													    (SI_Long)5L),
													    (SI_Long)22L) 
													    :
													     
													    Nil;
												    if (color_or_metacolor);
												    else
													color_or_metacolor 
														= 
														Qblack;
												    if (EQ(color_or_metacolor,
													    Qtransparent) 
													    || 
													    EQ(color_or_metacolor,
													    Qbackground)) 
														{
													background_color_or_metacolor 
														= 
														ISVREF(Current_image_plane,
														(SI_Long)5L) 
														?
														 
														ISVREF(ISVREF(Current_image_plane,
														(SI_Long)5L),
														(SI_Long)21L) 
														:
														 
														Nil;
													if (background_color_or_metacolor);
													else
													    background_color_or_metacolor 
														    = 
														    Qwhite;
													if (EQ(background_color_or_metacolor,
														Qforeground) 
														|| 
														EQ(background_color_or_metacolor,
														Qworkspace_foreground)) 
														    {
													    temp 
														    = 
														    ISVREF(Current_color_map,
														    (SI_Long)4L);
													    if (temp);
													    else
														temp 
															= 
															map_to_color_value_1(Qblack);
													    current_foreground_color_value 
														    = 
														    temp;
													}
													else if (EQ(background_color_or_metacolor,
														Qtransparent) 
														|| 
														EQ(background_color_or_metacolor,
														Qbackground)) 
														    {
													    temp 
														    = 
														    ISVREF(Current_color_map,
														    (SI_Long)5L);
													    if (temp);
													    else
														temp 
															= 
															map_to_color_value_1(Qwhite);
													    current_foreground_color_value 
														    = 
														    temp;
													}
													else
													    current_foreground_color_value 
														    = 
														    EQ(background_color_or_metacolor,
														    ISVREF(Current_color_map,
														    (SI_Long)6L)) 
														    ?
														     
														    ISVREF(Current_color_map,
														    (SI_Long)7L) 
														    :
														     
														    map_to_color_value_1(background_color_or_metacolor);
												    }
												    else if (EQ(color_or_metacolor,
													    Qforeground) 
													    || 
													    EQ(color_or_metacolor,
													    Qworkspace_foreground)) 
														{
													temp 
														= 
														ISVREF(Current_color_map,
														(SI_Long)4L);
													if (temp);
													else
													    temp 
														    = 
														    map_to_color_value_1(Qblack);
													current_foreground_color_value 
														= 
														temp;
												    }
												    else
													current_foreground_color_value 
														= 
														EQ(color_or_metacolor,
														ISVREF(Current_color_map,
														(SI_Long)6L)) 
														?
														 
														ISVREF(Current_color_map,
														(SI_Long)7L) 
														:
														 
														map_to_color_value_1(color_or_metacolor);
												    PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
													    9);
												      PUSH_SPECIAL_WITH_SYMBOL(Loose_bottom_edge_of_visible_workspace_area,Qloose_bottom_edge_of_visible_workspace_area,loose_bottom_edge_of_visible_workspace_area,
													      8);
													PUSH_SPECIAL_WITH_SYMBOL(Loose_right_edge_of_visible_workspace_area,Qloose_right_edge_of_visible_workspace_area,loose_right_edge_of_visible_workspace_area,
														7);
													  PUSH_SPECIAL_WITH_SYMBOL(Loose_top_edge_of_visible_workspace_area,Qloose_top_edge_of_visible_workspace_area,loose_top_edge_of_visible_workspace_area,
														  6);
													    PUSH_SPECIAL_WITH_SYMBOL(Loose_left_edge_of_visible_workspace_area,Qloose_left_edge_of_visible_workspace_area,loose_left_edge_of_visible_workspace_area,
														    5);
													      PUSH_SPECIAL_WITH_SYMBOL(Current_image_plane,Qcurrent_image_plane,current_image_plane,
														      4);
														PUSH_SPECIAL_WITH_SYMBOL(Current_pane,Qcurrent_pane,current_pane,
															3);
														  outer_native_image_plane 
															  = 
															  Current_native_image_plane;
														  PUSH_SPECIAL_WITH_SYMBOL(Outer_native_image_plane,Qouter_native_image_plane,outer_native_image_plane,
															  2);
														    current_native_image_plane 
															    = 
															    Current_image_plane;
														    PUSH_SPECIAL_WITH_SYMBOL(Current_native_image_plane,Qcurrent_native_image_plane,current_native_image_plane,
															    1);
														      if ( 
															      !EQ(Outer_native_image_plane,
															      Current_native_image_plane))
															  nip_begin_drawing(Current_native_image_plane);
														      color_or_metacolor 
															      = 
															      ISVREF(Current_image_plane,
															      (SI_Long)5L) 
															      ?
															       
															      ISVREF(ISVREF(Current_image_plane,
															      (SI_Long)5L),
															      (SI_Long)21L) 
															      :
															       
															      Nil;
														      if (color_or_metacolor);
														      else
															  color_or_metacolor 
																  = 
																  Qwhite;
														      if (EQ(color_or_metacolor,
															      Qtransparent) 
															      || 
															      EQ(color_or_metacolor,
															      Qbackground)) 
																  {
															  color_value 
																  = 
																  ISVREF(Current_color_map,
																  (SI_Long)5L);
															  if (color_value);
															  else
															      color_value 
																      = 
																      map_to_color_value_1(Qwhite);
														      }
														      else if (EQ(color_or_metacolor,
															      Qforeground) 
															      || 
															      EQ(color_or_metacolor,
															      Qworkspace_foreground)) 
																  {
															  temp 
																  = 
																  ISVREF(Current_image_plane,
																  (SI_Long)5L) 
																  ?
																   
																  ISVREF(ISVREF(Current_image_plane,
																  (SI_Long)5L),
																  (SI_Long)22L) 
																  :
																   
																  Nil;
															  if (temp);
															  else
															      temp 
																      = 
																      Qblack;
															  color_or_metacolor 
																  = 
																  temp;
															  if (EQ(color_or_metacolor,
																  Qtransparent) 
																  || 
																  EQ(color_or_metacolor,
																  Qbackground)) 
																      {
															      background_color_or_metacolor 
																      = 
																      ISVREF(Current_image_plane,
																      (SI_Long)5L) 
																      ?
																       
																      ISVREF(ISVREF(Current_image_plane,
																      (SI_Long)5L),
																      (SI_Long)21L) 
																      :
																       
																      Nil;
															      if (background_color_or_metacolor);
															      else
																  background_color_or_metacolor 
																	  = 
																	  Qwhite;
															      if (EQ(background_color_or_metacolor,
																      Qforeground) 
																      || 
																      EQ(background_color_or_metacolor,
																      Qworkspace_foreground)) 
																	  {
																  color_value 
																	  = 
																	  ISVREF(Current_color_map,
																	  (SI_Long)4L);
																  if (color_value);
																  else
																      color_value 
																	      = 
																	      map_to_color_value_1(Qblack);
															      }
															      else if (EQ(background_color_or_metacolor,
																      Qtransparent) 
																      || 
																      EQ(background_color_or_metacolor,
																      Qbackground)) 
																	  {
																  color_value 
																	  = 
																	  ISVREF(Current_color_map,
																	  (SI_Long)5L);
																  if (color_value);
																  else
																      color_value 
																	      = 
																	      map_to_color_value_1(Qwhite);
															      }
															      else
																  color_value 
																	  = 
																	  EQ(background_color_or_metacolor,
																	  ISVREF(Current_color_map,
																	  (SI_Long)6L)) 
																	  ?
																	   
																	  ISVREF(Current_color_map,
																	  (SI_Long)7L) 
																	  :
																	   
																	  map_to_color_value_1(background_color_or_metacolor);
															  }
															  else if (EQ(color_or_metacolor,
																  Qforeground) 
																  || 
																  EQ(color_or_metacolor,
																  Qworkspace_foreground)) 
																      {
															      color_value 
																      = 
																      ISVREF(Current_color_map,
																      (SI_Long)4L);
															      if (color_value);
															      else
																  color_value 
																	  = 
																	  map_to_color_value_1(Qblack);
															  }
															  else
															      color_value 
																      = 
																      EQ(color_or_metacolor,
																      ISVREF(Current_color_map,
																      (SI_Long)6L)) 
																      ?
																       
																      ISVREF(Current_color_map,
																      (SI_Long)7L) 
																      :
																       
																      map_to_color_value_1(color_or_metacolor);
														      }
														      else
															  color_value 
																  = 
																  EQ(color_or_metacolor,
																  ISVREF(Current_color_map,
																  (SI_Long)6L)) 
																  ?
																   
																  ISVREF(Current_color_map,
																  (SI_Long)7L) 
																  :
																   
																  map_to_color_value_1(color_or_metacolor);
														      old_color_value 
															      = 
															      Current_background_color_value;
														      current_background_color_value 
															      = 
															      Current_background_color_value;
														      PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
															      0);
															set_current_background_color_value(color_value);
															tail 
																= 
																cursors;
															cursor 
																= 
																Nil;
															for ( 
																; 
																!ENDP(tail); 
																tail 
																= 
																CDR(tail)) 
																    {
															    cursor 
																    = 
																    CAR(tail);
															    move_selection_highlight(cursor,
																    dx,
																    dy);
															}
															set_current_background_color_value(old_color_value);
														      POP_SPECIAL();
														      if ( 
															      !EQ(Outer_native_image_plane,
															      Current_native_image_plane))
															  nip_end_drawing(Current_native_image_plane);
														    POP_SPECIAL();
														    if (Current_native_image_plane) 
																{
															if ( 
																!EQ(Current_image_plane,
																Current_native_image_plane))
															    nip_begin_drawing(Current_native_image_plane);
														    }
														  POP_SPECIAL();
														POP_SPECIAL();
													      POP_SPECIAL();
													    POP_SPECIAL();
													  POP_SPECIAL();
													POP_SPECIAL();
												      POP_SPECIAL();
												    POP_SPECIAL();
												}
												POP_UNWIND_PROTECT(0);
												UNLOCK(For_image_plane);
												CONTINUE_UNWINDING(0);
											    }
											  POP_SPECIAL();
										      }
										      POP_UNWIND_PROTECT(1);
										      UNLOCK(On_window_with_drawing);
										      CONTINUE_UNWINDING(1);
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
								POP_UNWIND_PROTECT(2);
								UNLOCK(On_window_without_drawing);
								CONTINUE_UNWINDING(2);
							      POP_SPECIAL();
							    POP_SPECIAL();
							  POP_SPECIAL();
							POP_SPECIAL();
						      POP_SPECIAL();
						  }
						POP_SPECIAL();
					      POP_SPECIAL();
					    POP_SPECIAL();
					  POP_SPECIAL();
				      }
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
	      reclaim_dragging_list_1(cursors);
	  }
      }
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* CHANGE-COLOR-OF-SELECTION-HIGHLIGHT */
Object change_color_of_selection_highlight(image_plane,cursor,new_color)
    Object image_plane, cursor, new_color;
{
    Object old_color, current_image_plane, gensym_window;
    Object left_edge_of_draw_area, top_edge_of_draw_area;
    Object right_edge_of_draw_area, bottom_edge_of_draw_area;
    Object current_image_x_scale, current_image_y_scale;
    Object current_x_origin_of_drawing, current_y_origin_of_drawing, temp;
    Object current_frame_transform_qm, current_window_1, drawing_on_window;
    Object current_drawing_transfer_mode, type_of_current_window;
    Object current_native_window_qm, current_color_map;
    Object current_background_color_value, current_foreground_color_value;
    Object defer_notifications_qm, current_pane;
    Object loose_left_edge_of_visible_workspace_area;
    Object loose_top_edge_of_visible_workspace_area;
    Object loose_right_edge_of_visible_workspace_area;
    Object loose_bottom_edge_of_visible_workspace_area, color_or_metacolor;
    Object background_color_or_metacolor, outer_native_image_plane;
    Object current_native_image_plane, color_value, old_color_value;
    Object color_value_1, color_value_2, icp_output_port_qm, icp_socket_qm;
    Object i_am_alive_info_qm, icp_output_port_qm_1, current_icp_port;
    Object current_icp_socket, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, aref_arg_1;
    char temp_1;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_stack_pointer;
    Declare_catch(3);
    Declare_special(54);
    Object result;

    x_note_fn_call(128,95);
    SAVE_STACK();
    old_color = SECOND(cursor);
    M_SECOND(cursor) = new_color;
    current_image_plane = image_plane;
    gensym_window = ISVREF(ISVREF(image_plane,(SI_Long)2L),(SI_Long)2L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_image_plane,Qcurrent_image_plane,current_image_plane,
	    53);
      left_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)7L);
      top_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)8L);
      right_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)9L);
      bottom_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)10L);
      PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
	      52);
	PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
		51);
	  PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
		  50);
	    PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
		    49);
	      current_image_x_scale = FIX((SI_Long)4096L);
	      current_image_y_scale = FIX((SI_Long)4096L);
	      current_x_origin_of_drawing = FIX((SI_Long)0L);
	      current_y_origin_of_drawing = FIX((SI_Long)0L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
		      48);
		PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
			47);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
			  46);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
			    45);
		      left_edge_of_draw_area = Left_edge_of_draw_area;
		      top_edge_of_draw_area = Top_edge_of_draw_area;
		      right_edge_of_draw_area = Right_edge_of_draw_area;
		      bottom_edge_of_draw_area = Bottom_edge_of_draw_area;
		      PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
			      44);
			PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
				43);
			  PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
				  42);
			    PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
				    41);
			      temp = ISVREF(Current_image_plane,(SI_Long)6L);
			      Left_edge_of_draw_area = FIXNUM_MAX(temp,
				      Left_edge_of_draw_area);
			      temp = ISVREF(Current_image_plane,(SI_Long)7L);
			      Top_edge_of_draw_area = FIXNUM_MAX(temp,
				      Top_edge_of_draw_area);
			      temp = ISVREF(Current_image_plane,(SI_Long)8L);
			      Right_edge_of_draw_area = FIXNUM_MIN(temp,
				      Right_edge_of_draw_area);
			      temp = ISVREF(Current_image_plane,(SI_Long)9L);
			      Bottom_edge_of_draw_area = FIXNUM_MIN(temp,
				      Bottom_edge_of_draw_area);
			      if (FIXNUM_LT(Left_edge_of_draw_area,
				      Right_edge_of_draw_area) && 
				      FIXNUM_LT(Top_edge_of_draw_area,
				      Bottom_edge_of_draw_area)) {
				  left_edge_of_draw_area = 
					  Left_edge_of_draw_area;
				  top_edge_of_draw_area = 
					  Top_edge_of_draw_area;
				  right_edge_of_draw_area = 
					  Right_edge_of_draw_area;
				  bottom_edge_of_draw_area = 
					  Bottom_edge_of_draw_area;
				  PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
					  40);
				    PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
					    39);
				      PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
					      38);
					PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
						37);
					  temp = 
						  ISVREF(Current_image_plane,
						  (SI_Long)19L);
					  Left_edge_of_draw_area = 
						  FIXNUM_MAX(temp,
						  Left_edge_of_draw_area);
					  temp = 
						  ISVREF(Current_image_plane,
						  (SI_Long)20L);
					  Top_edge_of_draw_area = 
						  FIXNUM_MAX(temp,
						  Top_edge_of_draw_area);
					  temp = 
						  ISVREF(Current_image_plane,
						  (SI_Long)21L);
					  Right_edge_of_draw_area = 
						  FIXNUM_MIN(temp,
						  Right_edge_of_draw_area);
					  temp = 
						  ISVREF(Current_image_plane,
						  (SI_Long)22L);
					  Bottom_edge_of_draw_area = 
						  FIXNUM_MIN(temp,
						  Bottom_edge_of_draw_area);
					  if (FIXNUM_LT(Left_edge_of_draw_area,
						  Right_edge_of_draw_area) 
						  && 
						  FIXNUM_LT(Top_edge_of_draw_area,
						  Bottom_edge_of_draw_area)) {
					      current_frame_transform_qm = Nil;
					      current_image_x_scale = 
						      ISVREF(Current_image_plane,
						      (SI_Long)11L);
					      current_image_y_scale = 
						      ISVREF(Current_image_plane,
						      (SI_Long)12L);
					      current_x_origin_of_drawing 
						      = 
						      ISVREF(Current_image_plane,
						      (SI_Long)13L);
					      current_y_origin_of_drawing 
						      = 
						      ISVREF(Current_image_plane,
						      (SI_Long)14L);
					      PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
						      36);
						PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
							35);
						  PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
							  34);
						    PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
							    33);
						      PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
							      32);
							LOCK(On_window_without_drawing);
							if (PUSH_UNWIND_PROTECT(2)) 
								    {
							    current_window_1 
								    = 
								    ISVREF(ISVREF(Current_image_plane,
								    (SI_Long)2L),
								    (SI_Long)2L);
							    PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
								    31);
							      drawing_on_window 
								      = Nil;
							      PUSH_SPECIAL_WITH_SYMBOL(Drawing_on_window,Qdrawing_on_window,drawing_on_window,
								      30);
								current_drawing_transfer_mode 
									= 
									EQ(Current_drawing_transfer_mode,
									Kxor) 
									? 
									Current_drawing_transfer_mode 
									: 
									ISVREF(Current_window,
									(SI_Long)30L);
								PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
									29);
								  type_of_current_window 
									  = 
									  ISVREF(Current_window,
									  (SI_Long)1L);
								  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
									  28);
								    current_native_window_qm 
									    = 
									    ISVREF(Current_window,
									    (SI_Long)17L);
								    PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
									    27);
								      current_color_map 
									      = 
									      ISVREF(Current_window,
									      (SI_Long)20L);
								      PUSH_SPECIAL_WITH_SYMBOL(Current_color_map,Qcurrent_color_map,current_color_map,
									      26);
									temp 
										= 
										ISVREF(Current_color_map,
										(SI_Long)5L);
									if (temp);
									else
									    temp 
										    = 
										    map_to_color_value_1(Qwhite);
									current_background_color_value 
										= 
										temp;
									PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
										25);
									  temp 
										  = 
										  ISVREF(Current_color_map,
										  (SI_Long)4L);
									  if (temp);
									  else
									      temp 
										      = 
										      map_to_color_value_1(Qblack);
									  current_foreground_color_value 
										  = 
										  temp;
									  PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
										  24);
									    defer_notifications_qm 
										    = 
										    T;
									    PUSH_SPECIAL_WITH_SYMBOL(Defer_notifications_qm,Qdefer_notifications_qm,defer_notifications_qm,
										    23);
									      LOCK(On_window_with_drawing);
									      if (PUSH_UNWIND_PROTECT(1)) 
											  {
										  drawing_on_window 
											  = 
											  T;
										  PUSH_SPECIAL_WITH_SYMBOL(Drawing_on_window,Qdrawing_on_window,drawing_on_window,
											  22);
										    if (EQ(Type_of_current_window,
											    Qx11_window)) 
												{
											LOCK(For_image_plane);
											if (PUSH_UNWIND_PROTECT(0)) 
												    {
											    current_pane 
												    = 
												    ISVREF(Current_image_plane,
												    (SI_Long)2L);
											    current_image_plane 
												    = 
												    Current_image_plane;
											    loose_left_edge_of_visible_workspace_area 
												    = 
												    ISVREF(Current_image_plane,
												    (SI_Long)23L);
											    loose_top_edge_of_visible_workspace_area 
												    = 
												    ISVREF(Current_image_plane,
												    (SI_Long)24L);
											    loose_right_edge_of_visible_workspace_area 
												    = 
												    ISVREF(Current_image_plane,
												    (SI_Long)25L);
											    loose_bottom_edge_of_visible_workspace_area 
												    = 
												    ISVREF(Current_image_plane,
												    (SI_Long)26L);
											    color_or_metacolor 
												    = 
												    ISVREF(Current_image_plane,
												    (SI_Long)5L) 
												    ?
												     
												    ISVREF(ISVREF(Current_image_plane,
												    (SI_Long)5L),
												    (SI_Long)22L) 
												    :
												     
												    Nil;
											    if (color_or_metacolor);
											    else
												color_or_metacolor 
													= 
													Qblack;
											    if (EQ(color_or_metacolor,
												    Qtransparent) 
												    || 
												    EQ(color_or_metacolor,
												    Qbackground)) 
													{
												background_color_or_metacolor 
													= 
													ISVREF(Current_image_plane,
													(SI_Long)5L) 
													?
													 
													ISVREF(ISVREF(Current_image_plane,
													(SI_Long)5L),
													(SI_Long)21L) 
													:
													 
													Nil;
												if (background_color_or_metacolor);
												else
												    background_color_or_metacolor 
													    = 
													    Qwhite;
												if (EQ(background_color_or_metacolor,
													Qforeground) 
													|| 
													EQ(background_color_or_metacolor,
													Qworkspace_foreground)) 
													    {
												    temp 
													    = 
													    ISVREF(Current_color_map,
													    (SI_Long)4L);
												    if (temp);
												    else
													temp 
														= 
														map_to_color_value_1(Qblack);
												    current_foreground_color_value 
													    = 
													    temp;
												}
												else if (EQ(background_color_or_metacolor,
													Qtransparent) 
													|| 
													EQ(background_color_or_metacolor,
													Qbackground)) 
													    {
												    temp 
													    = 
													    ISVREF(Current_color_map,
													    (SI_Long)5L);
												    if (temp);
												    else
													temp 
														= 
														map_to_color_value_1(Qwhite);
												    current_foreground_color_value 
													    = 
													    temp;
												}
												else
												    current_foreground_color_value 
													    = 
													    EQ(background_color_or_metacolor,
													    ISVREF(Current_color_map,
													    (SI_Long)6L)) 
													    ?
													     
													    ISVREF(Current_color_map,
													    (SI_Long)7L) 
													    :
													     
													    map_to_color_value_1(background_color_or_metacolor);
											    }
											    else if (EQ(color_or_metacolor,
												    Qforeground) 
												    || 
												    EQ(color_or_metacolor,
												    Qworkspace_foreground)) 
													{
												temp 
													= 
													ISVREF(Current_color_map,
													(SI_Long)4L);
												if (temp);
												else
												    temp 
													    = 
													    map_to_color_value_1(Qblack);
												current_foreground_color_value 
													= 
													temp;
											    }
											    else
												current_foreground_color_value 
													= 
													EQ(color_or_metacolor,
													ISVREF(Current_color_map,
													(SI_Long)6L)) 
													?
													 
													ISVREF(Current_color_map,
													(SI_Long)7L) 
													:
													 
													map_to_color_value_1(color_or_metacolor);
											    PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
												    9);
											      PUSH_SPECIAL_WITH_SYMBOL(Loose_bottom_edge_of_visible_workspace_area,Qloose_bottom_edge_of_visible_workspace_area,loose_bottom_edge_of_visible_workspace_area,
												      8);
												PUSH_SPECIAL_WITH_SYMBOL(Loose_right_edge_of_visible_workspace_area,Qloose_right_edge_of_visible_workspace_area,loose_right_edge_of_visible_workspace_area,
													7);
												  PUSH_SPECIAL_WITH_SYMBOL(Loose_top_edge_of_visible_workspace_area,Qloose_top_edge_of_visible_workspace_area,loose_top_edge_of_visible_workspace_area,
													  6);
												    PUSH_SPECIAL_WITH_SYMBOL(Loose_left_edge_of_visible_workspace_area,Qloose_left_edge_of_visible_workspace_area,loose_left_edge_of_visible_workspace_area,
													    5);
												      PUSH_SPECIAL_WITH_SYMBOL(Current_image_plane,Qcurrent_image_plane,current_image_plane,
													      4);
													PUSH_SPECIAL_WITH_SYMBOL(Current_pane,Qcurrent_pane,current_pane,
														3);
													  outer_native_image_plane 
														  = 
														  Current_native_image_plane;
													  PUSH_SPECIAL_WITH_SYMBOL(Outer_native_image_plane,Qouter_native_image_plane,outer_native_image_plane,
														  2);
													    current_native_image_plane 
														    = 
														    Current_image_plane;
													    PUSH_SPECIAL_WITH_SYMBOL(Current_native_image_plane,Qcurrent_native_image_plane,current_native_image_plane,
														    1);
													      if ( 
														      !EQ(Outer_native_image_plane,
														      Current_native_image_plane))
														  nip_begin_drawing(Current_native_image_plane);
													      color_or_metacolor 
														      = 
														      ISVREF(Current_image_plane,
														      (SI_Long)5L) 
														      ?
														       
														      ISVREF(ISVREF(Current_image_plane,
														      (SI_Long)5L),
														      (SI_Long)21L) 
														      :
														       
														      Nil;
													      if (color_or_metacolor);
													      else
														  color_or_metacolor 
															  = 
															  Qwhite;
													      if (EQ(color_or_metacolor,
														      Qtransparent) 
														      || 
														      EQ(color_or_metacolor,
														      Qbackground)) 
															  {
														  color_value 
															  = 
															  ISVREF(Current_color_map,
															  (SI_Long)5L);
														  if (color_value);
														  else
														      color_value 
															      = 
															      map_to_color_value_1(Qwhite);
													      }
													      else if (EQ(color_or_metacolor,
														      Qforeground) 
														      || 
														      EQ(color_or_metacolor,
														      Qworkspace_foreground)) 
															  {
														  temp 
															  = 
															  ISVREF(Current_image_plane,
															  (SI_Long)5L) 
															  ?
															   
															  ISVREF(ISVREF(Current_image_plane,
															  (SI_Long)5L),
															  (SI_Long)22L) 
															  :
															   
															  Nil;
														  if (temp);
														  else
														      temp 
															      = 
															      Qblack;
														  color_or_metacolor 
															  = 
															  temp;
														  if (EQ(color_or_metacolor,
															  Qtransparent) 
															  || 
															  EQ(color_or_metacolor,
															  Qbackground)) 
															      {
														      background_color_or_metacolor 
															      = 
															      ISVREF(Current_image_plane,
															      (SI_Long)5L) 
															      ?
															       
															      ISVREF(ISVREF(Current_image_plane,
															      (SI_Long)5L),
															      (SI_Long)21L) 
															      :
															       
															      Nil;
														      if (background_color_or_metacolor);
														      else
															  background_color_or_metacolor 
																  = 
																  Qwhite;
														      if (EQ(background_color_or_metacolor,
															      Qforeground) 
															      || 
															      EQ(background_color_or_metacolor,
															      Qworkspace_foreground)) 
																  {
															  color_value 
																  = 
																  ISVREF(Current_color_map,
																  (SI_Long)4L);
															  if (color_value);
															  else
															      color_value 
																      = 
																      map_to_color_value_1(Qblack);
														      }
														      else if (EQ(background_color_or_metacolor,
															      Qtransparent) 
															      || 
															      EQ(background_color_or_metacolor,
															      Qbackground)) 
																  {
															  color_value 
																  = 
																  ISVREF(Current_color_map,
																  (SI_Long)5L);
															  if (color_value);
															  else
															      color_value 
																      = 
																      map_to_color_value_1(Qwhite);
														      }
														      else
															  color_value 
																  = 
																  EQ(background_color_or_metacolor,
																  ISVREF(Current_color_map,
																  (SI_Long)6L)) 
																  ?
																   
																  ISVREF(Current_color_map,
																  (SI_Long)7L) 
																  :
																   
																  map_to_color_value_1(background_color_or_metacolor);
														  }
														  else if (EQ(color_or_metacolor,
															  Qforeground) 
															  || 
															  EQ(color_or_metacolor,
															  Qworkspace_foreground)) 
															      {
														      color_value 
															      = 
															      ISVREF(Current_color_map,
															      (SI_Long)4L);
														      if (color_value);
														      else
															  color_value 
																  = 
																  map_to_color_value_1(Qblack);
														  }
														  else
														      color_value 
															      = 
															      EQ(color_or_metacolor,
															      ISVREF(Current_color_map,
															      (SI_Long)6L)) 
															      ?
															       
															      ISVREF(Current_color_map,
															      (SI_Long)7L) 
															      :
															       
															      map_to_color_value_1(color_or_metacolor);
													      }
													      else
														  color_value 
															  = 
															  EQ(color_or_metacolor,
															  ISVREF(Current_color_map,
															  (SI_Long)6L)) 
															  ?
															   
															  ISVREF(Current_color_map,
															  (SI_Long)7L) 
															  :
															   
															  map_to_color_value_1(color_or_metacolor);
													      old_color_value 
														      = 
														      Current_background_color_value;
													      current_background_color_value 
														      = 
														      Current_background_color_value;
													      PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
														      0);
														set_current_background_color_value(color_value);
														if (EQ(new_color,
															Qbackground))
														    color_value_1 
															    = 
															    Current_background_color_value;
														else if (EQ(new_color,
															Qforeground) 
															|| 
															EQ(new_color,
															Qworkspace_foreground))
														    color_value_1 
															    = 
															    Current_foreground_color_value;
														else if (EQ(new_color,
															Qtransparent))
														    color_value_1 
															    = 
															    Current_background_color_value;
														else
														    color_value_1 
															    = 
															    map_to_color_value(new_color);
														if (EQ(old_color,
															Qbackground))
														    color_value_2 
															    = 
															    Current_background_color_value;
														else if (EQ(old_color,
															Qforeground) 
															|| 
															EQ(old_color,
															Qworkspace_foreground))
														    color_value_2 
															    = 
															    Current_foreground_color_value;
														else if (EQ(old_color,
															Qtransparent))
														    color_value_2 
															    = 
															    Current_background_color_value;
														else
														    color_value_2 
															    = 
															    map_to_color_value(old_color);
														draw_selection_highlight_1(cursor,
															FIXNUM_LOGXOR(color_value_1,
															color_value_2));
														set_current_background_color_value(old_color_value);
													      POP_SPECIAL();
													      if ( 
														      !EQ(Outer_native_image_plane,
														      Current_native_image_plane))
														  nip_end_drawing(Current_native_image_plane);
													    POP_SPECIAL();
													    temp 
														    = 
														    Current_native_image_plane 
														    ?
														     
														    ( 
														    !EQ(Current_image_plane,
														    Current_native_image_plane) 
														    ?
														     
														    nip_begin_drawing(Current_native_image_plane) 
														    :
														     
														    Nil) 
														    :
														     
														    Nil;
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
											UNLOCK(For_image_plane);
											CONTINUE_UNWINDING(0);
											result = RESTORE_VALUES();
											SAVE_VALUES(VALUES_1(result));
											if (Flush_graphics_immediately_qm)
											    sync_graphics_on_current_window();
										    }
										    else if (EQ(Type_of_current_window,
											    Qicp)) 
												{
											icp_output_port_qm 
												= 
												ISVREF(Current_window,
												(SI_Long)12L);
											icp_socket_qm 
												= 
												icp_output_port_qm 
												?
												 
												ISVREF(icp_output_port_qm,
												(SI_Long)2L) 
												:
												 
												Qnil;
											if (icp_socket_qm) 
												    {
											    i_am_alive_info_qm 
												    = 
												    ISVREF(icp_socket_qm,
												    (SI_Long)24L);
											    temp_1 
												    = 
												     
												    !TRUEP(i_am_alive_info_qm);
											    if (temp_1);
											    else
												temp_1 
													= 
													 
													!TRUEP(Do_icp_flow_control_qm);
											    if (temp_1);
											    else
												temp_1 
													= 
													 
													!TRUEP(ISVREF(i_am_alive_info_qm,
													(SI_Long)2L));
											}
											else
											    temp_1 
												    = 
												    TRUEP(Nil);
											if (temp_1) 
												    {
											    icp_output_port_qm_1 
												    = 
												    ISVREF(Current_window,
												    (SI_Long)12L);
											    if (icp_output_port_qm_1 
												    && 
												    icp_connection_open_p(ISVREF(icp_output_port_qm_1,
												    (SI_Long)2L))) 
													{
												current_icp_port 
													= 
													icp_output_port_qm_1;
												PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
													21);
												  current_icp_socket 
													  = 
													  ISVREF(Current_icp_port,
													  (SI_Long)2L);
												  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
													  20);
												    temp 
													    = 
													    IFIX(ISVREF(Current_icp_socket,
													    (SI_Long)22L)) 
													    >= 
													    (SI_Long)17L 
													    ?
													     
													    ISVREF(Current_icp_socket,
													    (SI_Long)53L) 
													    :
													     
													    Nil;
												    if (temp);
												    else
													temp 
														= 
														EQ(ISVREF(Current_icp_socket,
														(SI_Long)25L),
														Qtelewindows) 
														?
														 T : Nil;
												    disable_resumability 
													    = 
													    temp;
												    PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
													    19);
												      number_of_icp_bytes_for_message_series 
													      = 
													      FIX((SI_Long)0L);
												      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
													      18);
													icp_buffers_for_message_group 
														= 
														Nil;
													PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
														17);
													  icp_buffer_of_start_of_message_series_qm 
														  = 
														  Nil;
													  PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
														  16);
													    icp_byte_position_of_start_of_message_series_qm 
														    = 
														    Nil;
													    PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
														    15);
													      number_of_icp_bytes_to_fill_buffer 
														      = 
														      FIX((SI_Long)0L);
													      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
														      14);
														current_icp_buffer 
															= 
															Nil;
														PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
															13);
														  current_write_icp_byte_position 
															  = 
															  Nil;
														  PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
															  12);
														    number_of_icp_bytes_in_message_group 
															    = 
															    FIX((SI_Long)0L);
														    PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
															    11);
														      writing_icp_message_group 
															      = 
															      FIXNUM_ADD1(Writing_icp_message_group);
														      PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
															      10);
															gensymed_symbol 
																= 
																Nil;
															gensymed_symbol_1 
																= 
																0.0;
															gensymed_symbol_2 
																= 
																0.0;
															if (Profiling_enabled_qm) 
																    {
															    gensymed_symbol 
																    = 
																    T;
															    gensymed_symbol_1 
																    = 
																    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
																    (SI_Long)2L),
																    (SI_Long)0L);
															    gensymed_symbol_2 
																    = 
																    g2ext_unix_time_as_float();
															    aref_arg_1 
																    = 
																    ISVREF(Profiling_enabled_qm,
																    (SI_Long)2L);
															    DFLOAT_ISASET_1(aref_arg_1,
																    (SI_Long)0L,
																    gensymed_symbol_2);
															}
															if (icp_connection_open_p(Current_icp_socket) 
																&& 
																 
																!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
																    {
															    synchronize_icp_on_window_with_drawing(Current_window,
																    Left_edge_of_draw_area,
																    Top_edge_of_draw_area,
																    Right_edge_of_draw_area,
																    Bottom_edge_of_draw_area);
															    LOCK(For_image_plane);
															    if (PUSH_UNWIND_PROTECT(0)) 
																	{
																current_pane 
																	= 
																	ISVREF(Current_image_plane,
																	(SI_Long)2L);
																current_image_plane 
																	= 
																	Current_image_plane;
																loose_left_edge_of_visible_workspace_area 
																	= 
																	ISVREF(Current_image_plane,
																	(SI_Long)23L);
																loose_top_edge_of_visible_workspace_area 
																	= 
																	ISVREF(Current_image_plane,
																	(SI_Long)24L);
																loose_right_edge_of_visible_workspace_area 
																	= 
																	ISVREF(Current_image_plane,
																	(SI_Long)25L);
																loose_bottom_edge_of_visible_workspace_area 
																	= 
																	ISVREF(Current_image_plane,
																	(SI_Long)26L);
																color_or_metacolor 
																	= 
																	ISVREF(Current_image_plane,
																	(SI_Long)5L) 
																	?
																	 
																	ISVREF(ISVREF(Current_image_plane,
																	(SI_Long)5L),
																	(SI_Long)22L) 
																	:
																	 
																	Nil;
																if (color_or_metacolor);
																else
																    color_or_metacolor 
																	    = 
																	    Qblack;
																if (EQ(color_or_metacolor,
																	Qtransparent) 
																	|| 
																	EQ(color_or_metacolor,
																	Qbackground)) 
																	    {
																    background_color_or_metacolor 
																	    = 
																	    ISVREF(Current_image_plane,
																	    (SI_Long)5L) 
																	    ?
																	     
																	    ISVREF(ISVREF(Current_image_plane,
																	    (SI_Long)5L),
																	    (SI_Long)21L) 
																	    :
																	     
																	    Nil;
																    if (background_color_or_metacolor);
																    else
																	background_color_or_metacolor 
																		= 
																		Qwhite;
																    if (EQ(background_color_or_metacolor,
																	    Qforeground) 
																	    || 
																	    EQ(background_color_or_metacolor,
																	    Qworkspace_foreground)) 
																		{
																	temp 
																		= 
																		ISVREF(Current_color_map,
																		(SI_Long)4L);
																	if (temp);
																	else
																	    temp 
																		    = 
																		    map_to_color_value_1(Qblack);
																	current_foreground_color_value 
																		= 
																		temp;
																    }
																    else if (EQ(background_color_or_metacolor,
																	    Qtransparent) 
																	    || 
																	    EQ(background_color_or_metacolor,
																	    Qbackground)) 
																		{
																	temp 
																		= 
																		ISVREF(Current_color_map,
																		(SI_Long)5L);
																	if (temp);
																	else
																	    temp 
																		    = 
																		    map_to_color_value_1(Qwhite);
																	current_foreground_color_value 
																		= 
																		temp;
																    }
																    else
																	current_foreground_color_value 
																		= 
																		EQ(background_color_or_metacolor,
																		ISVREF(Current_color_map,
																		(SI_Long)6L)) 
																		?
																		 
																		ISVREF(Current_color_map,
																		(SI_Long)7L) 
																		:
																		 
																		map_to_color_value_1(background_color_or_metacolor);
																}
																else if (EQ(color_or_metacolor,
																	Qforeground) 
																	|| 
																	EQ(color_or_metacolor,
																	Qworkspace_foreground)) 
																	    {
																    temp 
																	    = 
																	    ISVREF(Current_color_map,
																	    (SI_Long)4L);
																    if (temp);
																    else
																	temp 
																		= 
																		map_to_color_value_1(Qblack);
																    current_foreground_color_value 
																	    = 
																	    temp;
																}
																else
																    current_foreground_color_value 
																	    = 
																	    EQ(color_or_metacolor,
																	    ISVREF(Current_color_map,
																	    (SI_Long)6L)) 
																	    ?
																	     
																	    ISVREF(Current_color_map,
																	    (SI_Long)7L) 
																	    :
																	     
																	    map_to_color_value_1(color_or_metacolor);
																PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
																	9);
																  PUSH_SPECIAL_WITH_SYMBOL(Loose_bottom_edge_of_visible_workspace_area,Qloose_bottom_edge_of_visible_workspace_area,loose_bottom_edge_of_visible_workspace_area,
																	  8);
																    PUSH_SPECIAL_WITH_SYMBOL(Loose_right_edge_of_visible_workspace_area,Qloose_right_edge_of_visible_workspace_area,loose_right_edge_of_visible_workspace_area,
																	    7);
																      PUSH_SPECIAL_WITH_SYMBOL(Loose_top_edge_of_visible_workspace_area,Qloose_top_edge_of_visible_workspace_area,loose_top_edge_of_visible_workspace_area,
																	      6);
																	PUSH_SPECIAL_WITH_SYMBOL(Loose_left_edge_of_visible_workspace_area,Qloose_left_edge_of_visible_workspace_area,loose_left_edge_of_visible_workspace_area,
																		5);
																	  PUSH_SPECIAL_WITH_SYMBOL(Current_image_plane,Qcurrent_image_plane,current_image_plane,
																		  4);
																	    PUSH_SPECIAL_WITH_SYMBOL(Current_pane,Qcurrent_pane,current_pane,
																		    3);
																	      outer_native_image_plane 
																		      = 
																		      Current_native_image_plane;
																	      PUSH_SPECIAL_WITH_SYMBOL(Outer_native_image_plane,Qouter_native_image_plane,outer_native_image_plane,
																		      2);
																		current_native_image_plane 
																			= 
																			Current_image_plane;
																		PUSH_SPECIAL_WITH_SYMBOL(Current_native_image_plane,Qcurrent_native_image_plane,current_native_image_plane,
																			1);
																		  if ( 
																			  !EQ(Outer_native_image_plane,
																			  Current_native_image_plane))
																		      nip_begin_drawing(Current_native_image_plane);
																		  color_or_metacolor 
																			  = 
																			  ISVREF(Current_image_plane,
																			  (SI_Long)5L) 
																			  ?
																			   
																			  ISVREF(ISVREF(Current_image_plane,
																			  (SI_Long)5L),
																			  (SI_Long)21L) 
																			  :
																			   
																			  Nil;
																		  if (color_or_metacolor);
																		  else
																		      color_or_metacolor 
																			      = 
																			      Qwhite;
																		  if (EQ(color_or_metacolor,
																			  Qtransparent) 
																			  || 
																			  EQ(color_or_metacolor,
																			  Qbackground)) 
																			      {
																		      color_value 
																			      = 
																			      ISVREF(Current_color_map,
																			      (SI_Long)5L);
																		      if (color_value);
																		      else
																			  color_value 
																				  = 
																				  map_to_color_value_1(Qwhite);
																		  }
																		  else if (EQ(color_or_metacolor,
																			  Qforeground) 
																			  || 
																			  EQ(color_or_metacolor,
																			  Qworkspace_foreground)) 
																			      {
																		      temp 
																			      = 
																			      ISVREF(Current_image_plane,
																			      (SI_Long)5L) 
																			      ?
																			       
																			      ISVREF(ISVREF(Current_image_plane,
																			      (SI_Long)5L),
																			      (SI_Long)22L) 
																			      :
																			       
																			      Nil;
																		      if (temp);
																		      else
																			  temp 
																				  = 
																				  Qblack;
																		      color_or_metacolor 
																			      = 
																			      temp;
																		      if (EQ(color_or_metacolor,
																			      Qtransparent) 
																			      || 
																			      EQ(color_or_metacolor,
																			      Qbackground)) 
																				  {
																			  background_color_or_metacolor 
																				  = 
																				  ISVREF(Current_image_plane,
																				  (SI_Long)5L) 
																				  ?
																				   
																				  ISVREF(ISVREF(Current_image_plane,
																				  (SI_Long)5L),
																				  (SI_Long)21L) 
																				  :
																				   
																				  Nil;
																			  if (background_color_or_metacolor);
																			  else
																			      background_color_or_metacolor 
																				      = 
																				      Qwhite;
																			  if (EQ(background_color_or_metacolor,
																				  Qforeground) 
																				  || 
																				  EQ(background_color_or_metacolor,
																				  Qworkspace_foreground)) 
																				      {
																			      color_value 
																				      = 
																				      ISVREF(Current_color_map,
																				      (SI_Long)4L);
																			      if (color_value);
																			      else
																				  color_value 
																					  = 
																					  map_to_color_value_1(Qblack);
																			  }
																			  else if (EQ(background_color_or_metacolor,
																				  Qtransparent) 
																				  || 
																				  EQ(background_color_or_metacolor,
																				  Qbackground)) 
																				      {
																			      color_value 
																				      = 
																				      ISVREF(Current_color_map,
																				      (SI_Long)5L);
																			      if (color_value);
																			      else
																				  color_value 
																					  = 
																					  map_to_color_value_1(Qwhite);
																			  }
																			  else
																			      color_value 
																				      = 
																				      EQ(background_color_or_metacolor,
																				      ISVREF(Current_color_map,
																				      (SI_Long)6L)) 
																				      ?
																				       
																				      ISVREF(Current_color_map,
																				      (SI_Long)7L) 
																				      :
																				       
																				      map_to_color_value_1(background_color_or_metacolor);
																		      }
																		      else if (EQ(color_or_metacolor,
																			      Qforeground) 
																			      || 
																			      EQ(color_or_metacolor,
																			      Qworkspace_foreground)) 
																				  {
																			  color_value 
																				  = 
																				  ISVREF(Current_color_map,
																				  (SI_Long)4L);
																			  if (color_value);
																			  else
																			      color_value 
																				      = 
																				      map_to_color_value_1(Qblack);
																		      }
																		      else
																			  color_value 
																				  = 
																				  EQ(color_or_metacolor,
																				  ISVREF(Current_color_map,
																				  (SI_Long)6L)) 
																				  ?
																				   
																				  ISVREF(Current_color_map,
																				  (SI_Long)7L) 
																				  :
																				   
																				  map_to_color_value_1(color_or_metacolor);
																		  }
																		  else
																		      color_value 
																			      = 
																			      EQ(color_or_metacolor,
																			      ISVREF(Current_color_map,
																			      (SI_Long)6L)) 
																			      ?
																			       
																			      ISVREF(Current_color_map,
																			      (SI_Long)7L) 
																			      :
																			       
																			      map_to_color_value_1(color_or_metacolor);
																		  old_color_value 
																			  = 
																			  Current_background_color_value;
																		  current_background_color_value 
																			  = 
																			  Current_background_color_value;
																		  PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
																			  0);
																		    set_current_background_color_value(color_value);
																		    if (EQ(new_color,
																			    Qbackground))
																			color_value_1 
																				= 
																				Current_background_color_value;
																		    else if (EQ(new_color,
																			    Qforeground) 
																			    || 
																			    EQ(new_color,
																			    Qworkspace_foreground))
																			color_value_1 
																				= 
																				Current_foreground_color_value;
																		    else if (EQ(new_color,
																			    Qtransparent))
																			color_value_1 
																				= 
																				Current_background_color_value;
																		    else
																			color_value_1 
																				= 
																				map_to_color_value(new_color);
																		    if (EQ(old_color,
																			    Qbackground))
																			color_value_2 
																				= 
																				Current_background_color_value;
																		    else if (EQ(old_color,
																			    Qforeground) 
																			    || 
																			    EQ(old_color,
																			    Qworkspace_foreground))
																			color_value_2 
																				= 
																				Current_foreground_color_value;
																		    else if (EQ(old_color,
																			    Qtransparent))
																			color_value_2 
																				= 
																				Current_background_color_value;
																		    else
																			color_value_2 
																				= 
																				map_to_color_value(old_color);
																		    draw_selection_highlight_1(cursor,
																			    FIXNUM_LOGXOR(color_value_1,
																			    color_value_2));
																		    set_current_background_color_value(old_color_value);
																		  POP_SPECIAL();
																		  if ( 
																			  !EQ(Outer_native_image_plane,
																			  Current_native_image_plane))
																		      nip_end_drawing(Current_native_image_plane);
																		POP_SPECIAL();
																		temp 
																			= 
																			Current_native_image_plane 
																			?
																			 
																			( 
																			!EQ(Current_image_plane,
																			Current_native_image_plane) 
																			?
																			 
																			nip_begin_drawing(Current_native_image_plane) 
																			:
																			 
																			Nil) 
																			:
																			 
																			Nil;
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
															    UNLOCK(For_image_plane);
															    CONTINUE_UNWINDING(0);
															    result = RESTORE_VALUES();
															    temp 
																    = 
																    result;
															    if (Flush_graphics_immediately_qm 
																    && 
																    FIXNUM_NE(ISVREF(Current_icp_socket,
																    (SI_Long)15L),
																    Icp_connection_closed))
																sync_graphics_on_current_window();
															    end_icp_message_group();
															}
															else
															    temp 
																    = 
																    Nil;
															SAVE_VALUES(VALUES_1(temp));
															if (Profiling_enabled_qm) 
																    {
															    gensymed_symbol_3 
																    = 
																    g2ext_unix_time_as_float();
															    gensymed_symbol_4 
																    = 
																    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
																    (SI_Long)2L),
																    (SI_Long)0L);
															    gensymed_symbol_5 
																    = 
																    gensymed_symbol_3 
																    - 
																    gensymed_symbol_4;
															    aref_arg_1 
																    = 
																    ISVREF(Profiling_enabled_qm,
																    (SI_Long)6L);
															    aref_new_value 
																    = 
																    gensymed_symbol_5 
																    + 
																    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
																    (SI_Long)6L),
																    (SI_Long)0L);
															    DFLOAT_ISASET_1(aref_arg_1,
																    (SI_Long)0L,
																    aref_new_value);
															    aref_arg_1 
																    = 
																    ISVREF(Profiling_enabled_qm,
																    (SI_Long)2L);
															    aref_new_value 
																    = 
																    gensymed_symbol 
																    ?
																     
																    gensymed_symbol_1 
																    + 
																    gensymed_symbol_5 
																    + 
																    (gensymed_symbol_4 
																    - 
																    gensymed_symbol_2) 
																    :
																     
																    gensymed_symbol_3;
															    DFLOAT_ISASET_1(aref_arg_1,
																    (SI_Long)0L,
																    aref_new_value);
															}
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
											    else
												SAVE_VALUES(VALUES_1(Nil));
											}
											else
											    SAVE_VALUES(VALUES_1(Nil));
										    }
										    else if (EQ(Type_of_current_window,
											    Qprinter)) 
												{
											LOCK(For_image_plane);
											if (PUSH_UNWIND_PROTECT(0)) 
												    {
											    current_pane 
												    = 
												    ISVREF(Current_image_plane,
												    (SI_Long)2L);
											    current_image_plane 
												    = 
												    Current_image_plane;
											    loose_left_edge_of_visible_workspace_area 
												    = 
												    ISVREF(Current_image_plane,
												    (SI_Long)23L);
											    loose_top_edge_of_visible_workspace_area 
												    = 
												    ISVREF(Current_image_plane,
												    (SI_Long)24L);
											    loose_right_edge_of_visible_workspace_area 
												    = 
												    ISVREF(Current_image_plane,
												    (SI_Long)25L);
											    loose_bottom_edge_of_visible_workspace_area 
												    = 
												    ISVREF(Current_image_plane,
												    (SI_Long)26L);
											    color_or_metacolor 
												    = 
												    ISVREF(Current_image_plane,
												    (SI_Long)5L) 
												    ?
												     
												    ISVREF(ISVREF(Current_image_plane,
												    (SI_Long)5L),
												    (SI_Long)22L) 
												    :
												     
												    Nil;
											    if (color_or_metacolor);
											    else
												color_or_metacolor 
													= 
													Qblack;
											    if (EQ(color_or_metacolor,
												    Qtransparent) 
												    || 
												    EQ(color_or_metacolor,
												    Qbackground)) 
													{
												background_color_or_metacolor 
													= 
													ISVREF(Current_image_plane,
													(SI_Long)5L) 
													?
													 
													ISVREF(ISVREF(Current_image_plane,
													(SI_Long)5L),
													(SI_Long)21L) 
													:
													 
													Nil;
												if (background_color_or_metacolor);
												else
												    background_color_or_metacolor 
													    = 
													    Qwhite;
												if (EQ(background_color_or_metacolor,
													Qforeground) 
													|| 
													EQ(background_color_or_metacolor,
													Qworkspace_foreground)) 
													    {
												    temp 
													    = 
													    ISVREF(Current_color_map,
													    (SI_Long)4L);
												    if (temp);
												    else
													temp 
														= 
														map_to_color_value_1(Qblack);
												    current_foreground_color_value 
													    = 
													    temp;
												}
												else if (EQ(background_color_or_metacolor,
													Qtransparent) 
													|| 
													EQ(background_color_or_metacolor,
													Qbackground)) 
													    {
												    temp 
													    = 
													    ISVREF(Current_color_map,
													    (SI_Long)5L);
												    if (temp);
												    else
													temp 
														= 
														map_to_color_value_1(Qwhite);
												    current_foreground_color_value 
													    = 
													    temp;
												}
												else
												    current_foreground_color_value 
													    = 
													    EQ(background_color_or_metacolor,
													    ISVREF(Current_color_map,
													    (SI_Long)6L)) 
													    ?
													     
													    ISVREF(Current_color_map,
													    (SI_Long)7L) 
													    :
													     
													    map_to_color_value_1(background_color_or_metacolor);
											    }
											    else if (EQ(color_or_metacolor,
												    Qforeground) 
												    || 
												    EQ(color_or_metacolor,
												    Qworkspace_foreground)) 
													{
												temp 
													= 
													ISVREF(Current_color_map,
													(SI_Long)4L);
												if (temp);
												else
												    temp 
													    = 
													    map_to_color_value_1(Qblack);
												current_foreground_color_value 
													= 
													temp;
											    }
											    else
												current_foreground_color_value 
													= 
													EQ(color_or_metacolor,
													ISVREF(Current_color_map,
													(SI_Long)6L)) 
													?
													 
													ISVREF(Current_color_map,
													(SI_Long)7L) 
													:
													 
													map_to_color_value_1(color_or_metacolor);
											    PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
												    9);
											      PUSH_SPECIAL_WITH_SYMBOL(Loose_bottom_edge_of_visible_workspace_area,Qloose_bottom_edge_of_visible_workspace_area,loose_bottom_edge_of_visible_workspace_area,
												      8);
												PUSH_SPECIAL_WITH_SYMBOL(Loose_right_edge_of_visible_workspace_area,Qloose_right_edge_of_visible_workspace_area,loose_right_edge_of_visible_workspace_area,
													7);
												  PUSH_SPECIAL_WITH_SYMBOL(Loose_top_edge_of_visible_workspace_area,Qloose_top_edge_of_visible_workspace_area,loose_top_edge_of_visible_workspace_area,
													  6);
												    PUSH_SPECIAL_WITH_SYMBOL(Loose_left_edge_of_visible_workspace_area,Qloose_left_edge_of_visible_workspace_area,loose_left_edge_of_visible_workspace_area,
													    5);
												      PUSH_SPECIAL_WITH_SYMBOL(Current_image_plane,Qcurrent_image_plane,current_image_plane,
													      4);
													PUSH_SPECIAL_WITH_SYMBOL(Current_pane,Qcurrent_pane,current_pane,
														3);
													  outer_native_image_plane 
														  = 
														  Current_native_image_plane;
													  PUSH_SPECIAL_WITH_SYMBOL(Outer_native_image_plane,Qouter_native_image_plane,outer_native_image_plane,
														  2);
													    current_native_image_plane 
														    = 
														    Current_image_plane;
													    PUSH_SPECIAL_WITH_SYMBOL(Current_native_image_plane,Qcurrent_native_image_plane,current_native_image_plane,
														    1);
													      if ( 
														      !EQ(Outer_native_image_plane,
														      Current_native_image_plane))
														  nip_begin_drawing(Current_native_image_plane);
													      color_or_metacolor 
														      = 
														      ISVREF(Current_image_plane,
														      (SI_Long)5L) 
														      ?
														       
														      ISVREF(ISVREF(Current_image_plane,
														      (SI_Long)5L),
														      (SI_Long)21L) 
														      :
														       
														      Nil;
													      if (color_or_metacolor);
													      else
														  color_or_metacolor 
															  = 
															  Qwhite;
													      if (EQ(color_or_metacolor,
														      Qtransparent) 
														      || 
														      EQ(color_or_metacolor,
														      Qbackground)) 
															  {
														  color_value 
															  = 
															  ISVREF(Current_color_map,
															  (SI_Long)5L);
														  if (color_value);
														  else
														      color_value 
															      = 
															      map_to_color_value_1(Qwhite);
													      }
													      else if (EQ(color_or_metacolor,
														      Qforeground) 
														      || 
														      EQ(color_or_metacolor,
														      Qworkspace_foreground)) 
															  {
														  temp 
															  = 
															  ISVREF(Current_image_plane,
															  (SI_Long)5L) 
															  ?
															   
															  ISVREF(ISVREF(Current_image_plane,
															  (SI_Long)5L),
															  (SI_Long)22L) 
															  :
															   
															  Nil;
														  if (temp);
														  else
														      temp 
															      = 
															      Qblack;
														  color_or_metacolor 
															  = 
															  temp;
														  if (EQ(color_or_metacolor,
															  Qtransparent) 
															  || 
															  EQ(color_or_metacolor,
															  Qbackground)) 
															      {
														      background_color_or_metacolor 
															      = 
															      ISVREF(Current_image_plane,
															      (SI_Long)5L) 
															      ?
															       
															      ISVREF(ISVREF(Current_image_plane,
															      (SI_Long)5L),
															      (SI_Long)21L) 
															      :
															       
															      Nil;
														      if (background_color_or_metacolor);
														      else
															  background_color_or_metacolor 
																  = 
																  Qwhite;
														      if (EQ(background_color_or_metacolor,
															      Qforeground) 
															      || 
															      EQ(background_color_or_metacolor,
															      Qworkspace_foreground)) 
																  {
															  color_value 
																  = 
																  ISVREF(Current_color_map,
																  (SI_Long)4L);
															  if (color_value);
															  else
															      color_value 
																      = 
																      map_to_color_value_1(Qblack);
														      }
														      else if (EQ(background_color_or_metacolor,
															      Qtransparent) 
															      || 
															      EQ(background_color_or_metacolor,
															      Qbackground)) 
																  {
															  color_value 
																  = 
																  ISVREF(Current_color_map,
																  (SI_Long)5L);
															  if (color_value);
															  else
															      color_value 
																      = 
																      map_to_color_value_1(Qwhite);
														      }
														      else
															  color_value 
																  = 
																  EQ(background_color_or_metacolor,
																  ISVREF(Current_color_map,
																  (SI_Long)6L)) 
																  ?
																   
																  ISVREF(Current_color_map,
																  (SI_Long)7L) 
																  :
																   
																  map_to_color_value_1(background_color_or_metacolor);
														  }
														  else if (EQ(color_or_metacolor,
															  Qforeground) 
															  || 
															  EQ(color_or_metacolor,
															  Qworkspace_foreground)) 
															      {
														      color_value 
															      = 
															      ISVREF(Current_color_map,
															      (SI_Long)4L);
														      if (color_value);
														      else
															  color_value 
																  = 
																  map_to_color_value_1(Qblack);
														  }
														  else
														      color_value 
															      = 
															      EQ(color_or_metacolor,
															      ISVREF(Current_color_map,
															      (SI_Long)6L)) 
															      ?
															       
															      ISVREF(Current_color_map,
															      (SI_Long)7L) 
															      :
															       
															      map_to_color_value_1(color_or_metacolor);
													      }
													      else
														  color_value 
															  = 
															  EQ(color_or_metacolor,
															  ISVREF(Current_color_map,
															  (SI_Long)6L)) 
															  ?
															   
															  ISVREF(Current_color_map,
															  (SI_Long)7L) 
															  :
															   
															  map_to_color_value_1(color_or_metacolor);
													      old_color_value 
														      = 
														      Current_background_color_value;
													      current_background_color_value 
														      = 
														      Current_background_color_value;
													      PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
														      0);
														set_current_background_color_value(color_value);
														if (EQ(new_color,
															Qbackground))
														    color_value_1 
															    = 
															    Current_background_color_value;
														else if (EQ(new_color,
															Qforeground) 
															|| 
															EQ(new_color,
															Qworkspace_foreground))
														    color_value_1 
															    = 
															    Current_foreground_color_value;
														else if (EQ(new_color,
															Qtransparent))
														    color_value_1 
															    = 
															    Current_background_color_value;
														else
														    color_value_1 
															    = 
															    map_to_color_value(new_color);
														if (EQ(old_color,
															Qbackground))
														    color_value_2 
															    = 
															    Current_background_color_value;
														else if (EQ(old_color,
															Qforeground) 
															|| 
															EQ(old_color,
															Qworkspace_foreground))
														    color_value_2 
															    = 
															    Current_foreground_color_value;
														else if (EQ(old_color,
															Qtransparent))
														    color_value_2 
															    = 
															    Current_background_color_value;
														else
														    color_value_2 
															    = 
															    map_to_color_value(old_color);
														draw_selection_highlight_1(cursor,
															FIXNUM_LOGXOR(color_value_1,
															color_value_2));
														set_current_background_color_value(old_color_value);
													      POP_SPECIAL();
													      if ( 
														      !EQ(Outer_native_image_plane,
														      Current_native_image_plane))
														  nip_end_drawing(Current_native_image_plane);
													    POP_SPECIAL();
													    if (Current_native_image_plane) 
															{
														if ( 
															!EQ(Current_image_plane,
															Current_native_image_plane))
														    SAVE_VALUES(nip_begin_drawing(Current_native_image_plane));
														else
														    SAVE_VALUES(VALUES_1(Nil));
													    }
													    else
														SAVE_VALUES(VALUES_1(Nil));
													  POP_SPECIAL();
													POP_SPECIAL();
												      POP_SPECIAL();
												    POP_SPECIAL();
												  POP_SPECIAL();
												POP_SPECIAL();
											      POP_SPECIAL();
											    POP_SPECIAL();
											}
											POP_UNWIND_PROTECT(0);
											UNLOCK(For_image_plane);
											CONTINUE_UNWINDING(0);
										    }
										    else
											SAVE_VALUES(VALUES_1(Qnil));
										  POP_SPECIAL();
									      }
									      POP_UNWIND_PROTECT(1);
									      UNLOCK(On_window_with_drawing);
									      CONTINUE_UNWINDING(1);
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
							POP_UNWIND_PROTECT(2);
							UNLOCK(On_window_without_drawing);
							CONTINUE_UNWINDING(2);
							result = RESTORE_VALUES();
						      POP_SPECIAL();
						    POP_SPECIAL();
						  POP_SPECIAL();
						POP_SPECIAL();
					      POP_SPECIAL();
					  }
					  else
					      result = VALUES_1(Nil);
					POP_SPECIAL();
				      POP_SPECIAL();
				    POP_SPECIAL();
				  POP_SPECIAL();
			      }
			      else
				  result = VALUES_1(Nil);
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
    RESTORE_STACK();
    return result;
}

/* MOVE-SELECTION-HIGHLIGHT */
Object move_selection_highlight(cursor,dx,dy)
    Object cursor, dx, dy;
{
    Object current_drawing_transfer_mode, sublist, incff_1_arg, temp;
    char already_in_synch;
    Declare_stack_pointer;
    Declare_special(1);
    Object result;

    x_note_fn_call(128,96);
    SAVE_STACK();
    already_in_synch = EQ(Current_drawing_transfer_mode,Kxor);
    current_drawing_transfer_mode = Current_drawing_transfer_mode;
    PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
	    0);
      if ( !already_in_synch) {
	  Current_drawing_transfer_mode = Kxor;
	  synchronize_transfer_mode();
      }
      draw_selection_highlight(cursor);
      sublist = CDDR(cursor);
    next_loop:
      if ( !TRUEP(sublist))
	  goto end_loop;
      incff_1_arg = dx;
      temp = FIXNUM_ADD(CAR(sublist),incff_1_arg);
      M_CAR(sublist) = temp;
      incff_1_arg = dy;
      temp = FIXNUM_ADD(CADR(sublist),incff_1_arg);
      M_CADR(sublist) = temp;
      sublist = CDDR(sublist);
      goto next_loop;
    end_loop:;
      SAVE_VALUES(draw_selection_highlight(cursor));
    POP_SPECIAL();
    if ( !already_in_synch)
	synchronize_transfer_mode();
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* REPLACE-SELECTION-HIGHLIGHT */
Object replace_selection_highlight(sublist,new_cursor)
    Object sublist, new_cursor;
{
    Object old_cursor, current_drawing_transfer_mode;
    char already_in_synch;
    Declare_stack_pointer;
    Declare_special(1);
    Object result;

    x_note_fn_call(128,97);
    SAVE_STACK();
    old_cursor = CAR(sublist);
    already_in_synch = EQ(Current_drawing_transfer_mode,Kxor);
    current_drawing_transfer_mode = Current_drawing_transfer_mode;
    PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
	    0);
      if ( !already_in_synch) {
	  Current_drawing_transfer_mode = Kxor;
	  synchronize_transfer_mode();
      }
      draw_selection_highlight(old_cursor);
      M_CAR(sublist) = new_cursor;
      reclaim_selection_highlight(old_cursor);
      SAVE_VALUES(draw_selection_highlight(new_cursor));
    POP_SPECIAL();
    if ( !already_in_synch)
	synchronize_transfer_mode();
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* RECLAIM-SELECTION-HIGHLIGHT */
Object reclaim_selection_highlight(cursor)
    Object cursor;
{
    x_note_fn_call(128,98);
    return reclaim_graphics_list_1(cursor);
}

/* FIND-SELECTION-HIGHLIGHT */
Object find_selection_highlight(selectable_qm,image_plane)
    Object selectable_qm, image_plane;
{
    Object cursor, ab_loop_list_;

    x_note_fn_call(128,99);
    if (selectable_qm) {
	cursor = Nil;
	ab_loop_list_ = ISVREF(image_plane,(SI_Long)27L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	cursor = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (CONSP(cursor) && EQ(M_CAR(cursor),selectable_qm))
	    return VALUES_1(cursor);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* FIND-SELECTION-HIGHLIGHTS */
Object find_selection_highlights(thing,image_plane)
    Object thing, image_plane;
{
    Object cursor, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;

    x_note_fn_call(128,100);
    cursor = Nil;
    ab_loop_list_ = ISVREF(image_plane,(SI_Long)27L);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    cursor = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (selection_highlight_cursor_p(cursor) && (EQ(thing,FIRST(cursor)) 
	    || text_cell_p(FIRST(cursor)) && EQ(thing,
	    get_table_for_cell(FIRST(cursor))))) {
	ab_loopvar__2 = dragging_cons_1(cursor,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

/* FIND-SELECTION-HIGHLIGHT-POSITION */
Object find_selection_highlight_position(selectable,image_plane)
    Object selectable, image_plane;
{
    Object sublist, cursor;

    x_note_fn_call(128,101);
    sublist = ISVREF(image_plane,(SI_Long)27L);
    cursor = Nil;
  next_loop:
    if ( !TRUEP(sublist))
	goto end_loop;
    cursor = CAR(sublist);
    if (CONSP(cursor) && EQ(CAR(cursor),selectable))
	return VALUES_1(sublist);
    sublist = M_CDR(sublist);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* SELECTION-RECTANGLE-CURSOR-P */
Object selection_rectangle_cursor_p(cursor)
    Object cursor;
{
    Object temp;

    x_note_fn_call(128,102);
    if (CONSP(cursor)) {
	temp = CAR(cursor);
	return VALUES_1(SYMBOLP(temp) ? T : Nil);
    }
    else
	return VALUES_1(Nil);
}

/* DRAW-SELECTION-RECTANGLE-CURSOR */
Object draw_selection_rectangle_cursor(cursor)
    Object cursor;
{
    Object color_or_metacolor, temp;

    x_note_fn_call(128,103);
    color_or_metacolor = FIRST(cursor);
    if (EQ(color_or_metacolor,Qbackground))
	temp = Current_background_color_value;
    else if (EQ(color_or_metacolor,Qforeground) || EQ(color_or_metacolor,
	    Qworkspace_foreground))
	temp = Current_foreground_color_value;
    else if (EQ(color_or_metacolor,Qtransparent))
	temp = Current_background_color_value;
    else
	temp = map_to_color_value(color_or_metacolor);
    return draw_dotted_rectangle(temp,SECOND(cursor),THIRD(cursor),
	    FOURTH(cursor),FIFTH(cursor));
}

static Object Qab_dot;             /* dot */

/* DRAW-DOTTED-RECTANGLE */
Object draw_dotted_rectangle(color_value,x0,y0_1,x1,y1_1)
    Object color_value, x0, y0_1, x1, y1_1;
{
    Object gensymed_symbol, gensymed_symbol_1, points, color_difference;
    Object line_pattern, current_drawing_transfer_mode;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, unshifted_result;
    SI_Long car_new_value;
    char already_in_synch;
    Declare_stack_pointer;
    Declare_special(1);
    Object result;

    x_note_fn_call(128,104);
    SAVE_STACK();
    gensymed_symbol = make_gensym_list_1(FIX((SI_Long)10L));
    gensymed_symbol_1 = gensymed_symbol;
    gensymed_symbol_2 = IFIX(Current_x_origin_of_drawing);
    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	gensymed_symbol_3 = IFIX(x1);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x1) && 
	    FIXNUM_LT(x1,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,x1)) + 
		(SI_Long)2048L;
	gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_3 = IFIX(scalef_function(Current_image_x_scale,x1));
    car_new_value = gensymed_symbol_2 + gensymed_symbol_3;
    M_CAR(gensymed_symbol_1) = FIX(car_new_value);
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    gensymed_symbol_2 = IFIX(Current_y_origin_of_drawing);
    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	gensymed_symbol_3 = IFIX(y0_1);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y0_1) && 
	    FIXNUM_LT(y0_1,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,y0_1)) 
		+ (SI_Long)2048L;
	gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_3 = IFIX(scalef_function(Current_image_y_scale,y0_1));
    car_new_value = gensymed_symbol_2 + gensymed_symbol_3;
    M_CAR(gensymed_symbol_1) = FIX(car_new_value);
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    gensymed_symbol_2 = IFIX(Current_x_origin_of_drawing);
    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	gensymed_symbol_3 = IFIX(x0);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x0) && 
	    FIXNUM_LT(x0,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,x0)) + 
		(SI_Long)2048L;
	gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_3 = IFIX(scalef_function(Current_image_x_scale,x0));
    car_new_value = gensymed_symbol_2 + gensymed_symbol_3;
    M_CAR(gensymed_symbol_1) = FIX(car_new_value);
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    gensymed_symbol_2 = IFIX(Current_y_origin_of_drawing);
    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	gensymed_symbol_3 = IFIX(y0_1);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y0_1) && 
	    FIXNUM_LT(y0_1,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,y0_1)) 
		+ (SI_Long)2048L;
	gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_3 = IFIX(scalef_function(Current_image_y_scale,y0_1));
    car_new_value = gensymed_symbol_2 + gensymed_symbol_3;
    M_CAR(gensymed_symbol_1) = FIX(car_new_value);
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    gensymed_symbol_2 = IFIX(Current_x_origin_of_drawing);
    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	gensymed_symbol_3 = IFIX(x0);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x0) && 
	    FIXNUM_LT(x0,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,x0)) + 
		(SI_Long)2048L;
	gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_3 = IFIX(scalef_function(Current_image_x_scale,x0));
    car_new_value = gensymed_symbol_2 + gensymed_symbol_3;
    M_CAR(gensymed_symbol_1) = FIX(car_new_value);
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    gensymed_symbol_2 = IFIX(Current_y_origin_of_drawing);
    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	gensymed_symbol_3 = IFIX(y1_1);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y1_1) && 
	    FIXNUM_LT(y1_1,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,y1_1)) 
		+ (SI_Long)2048L;
	gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_3 = IFIX(scalef_function(Current_image_y_scale,y1_1));
    car_new_value = gensymed_symbol_2 + gensymed_symbol_3;
    M_CAR(gensymed_symbol_1) = FIX(car_new_value);
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    gensymed_symbol_2 = IFIX(Current_x_origin_of_drawing);
    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	gensymed_symbol_3 = IFIX(x1);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x1) && 
	    FIXNUM_LT(x1,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,x1)) + 
		(SI_Long)2048L;
	gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_3 = IFIX(scalef_function(Current_image_x_scale,x1));
    car_new_value = gensymed_symbol_2 + gensymed_symbol_3;
    M_CAR(gensymed_symbol_1) = FIX(car_new_value);
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    gensymed_symbol_2 = IFIX(Current_y_origin_of_drawing);
    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	gensymed_symbol_3 = IFIX(y1_1);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y1_1) && 
	    FIXNUM_LT(y1_1,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,y1_1)) 
		+ (SI_Long)2048L;
	gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_3 = IFIX(scalef_function(Current_image_y_scale,y1_1));
    car_new_value = gensymed_symbol_2 + gensymed_symbol_3;
    M_CAR(gensymed_symbol_1) = FIX(car_new_value);
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    gensymed_symbol_2 = IFIX(Current_x_origin_of_drawing);
    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	gensymed_symbol_3 = IFIX(x1);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x1) && 
	    FIXNUM_LT(x1,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,x1)) + 
		(SI_Long)2048L;
	gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_3 = IFIX(scalef_function(Current_image_x_scale,x1));
    car_new_value = gensymed_symbol_2 + gensymed_symbol_3;
    M_CAR(gensymed_symbol_1) = FIX(car_new_value);
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    gensymed_symbol_2 = IFIX(Current_y_origin_of_drawing);
    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	gensymed_symbol_3 = IFIX(y0_1);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y0_1) && 
	    FIXNUM_LT(y0_1,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,y0_1)) 
		+ (SI_Long)2048L;
	gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_3 = IFIX(scalef_function(Current_image_y_scale,y0_1));
    car_new_value = gensymed_symbol_2 + gensymed_symbol_3;
    M_CAR(gensymed_symbol_1) = FIX(car_new_value);
    points = gensymed_symbol;
    color_difference = FIXNUM_LOGXOR(color_value,
	    Current_background_color_value);
    line_pattern = Qab_dot;
    already_in_synch = EQ(Current_drawing_transfer_mode,Kxor);
    current_drawing_transfer_mode = Current_drawing_transfer_mode;
    PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
	    0);
      if ( !already_in_synch) {
	  Current_drawing_transfer_mode = Kxor;
	  synchronize_transfer_mode();
      }
      draw_wide_polyline(points,color_difference,FIX((SI_Long)0L),
	      line_pattern,Nil);
      SAVE_VALUES(reclaim_gensym_list_1(points));
    POP_SPECIAL();
    if ( !already_in_synch)
	synchronize_transfer_mode();
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object Qtree_ordering;      /* tree-ordering */

/* REMOVE-OBJECT-FROM-DRAGGING-CONTEXT */
Object remove_object_from_dragging_context(object_or_connection)
    Object object_or_connection;
{
    Object x2, object_is_a_frame_qm, dragging_state, ab_loop_list_, temp;
    Object stack, sub, tree_ordering_pop_store, cons_1, next_cons, svref_arg_2;
    Object temp_1, gensymed_symbol, ab_queue_form_, ab_next_queue_element_;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, infs, temp_2, temp_3;
    SI_Long svref_new_value;

    x_note_fn_call(128,105);
    if (SIMPLE_VECTOR_P(object_or_connection) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(object_or_connection)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(object_or_connection,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(object_or_connection,(SI_Long)1L);
	object_is_a_frame_qm = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	object_is_a_frame_qm = Nil;
    dragging_state = Nil;
    ab_loop_list_ = Current_dragging_states;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    dragging_state = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (object_is_a_frame_qm) {
	temp = delete_dragging_element_1(object_or_connection,
		ISVREF(dragging_state,(SI_Long)3L));
	SVREF(dragging_state,FIX((SI_Long)3L)) = temp;
    }
    else if (memq_function(object_or_connection,ISVREF(dragging_state,
	    (SI_Long)6L))) {
      next_loop_1:
	temp = delete_dragging_element_1(object_or_connection,
		ISVREF(dragging_state,(SI_Long)6L));
	if ( !TRUEP(memq_function(object_or_connection,
		SVREF(dragging_state,FIX((SI_Long)6L)) = temp)))
	    goto end_loop_1;
	goto next_loop_1;
      end_loop_1:;
    }
    goto next_loop;
  end_loop:
    if (object_is_a_frame_qm) {
	stack = tree_ordering_cons_1(object_or_connection,Nil);
	sub = Nil;
      next_loop_2:
	if ( !TRUEP(stack))
	    goto end_loop_2;
	tree_ordering_pop_store = Nil;
	cons_1 = stack;
	if (cons_1) {
	    tree_ordering_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qtree_ordering);
	    if (ISVREF(Available_tree_ordering_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_tree_ordering_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = cons_1;
		temp = Available_tree_ordering_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    else {
		temp = Available_tree_ordering_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
		temp = Available_tree_ordering_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	stack = next_cons;
	temp_1 = tree_ordering_pop_store;
	sub = Nil;
	if (EQ(temp_1,Tree_traversal_marker)) {
	    tree_ordering_pop_store = Nil;
	    cons_1 = stack;
	    if (cons_1) {
		tree_ordering_pop_store = M_CAR(cons_1);
		next_cons = M_CDR(cons_1);
		inline_note_reclaim_cons(cons_1,Qtree_ordering);
		if (ISVREF(Available_tree_ordering_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp = 
			    ISVREF(Available_tree_ordering_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp) = cons_1;
		    temp = Available_tree_ordering_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		}
		else {
		    temp = Available_tree_ordering_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		    temp = Available_tree_ordering_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		}
		M_CDR(cons_1) = Nil;
	    }
	    else
		next_cons = Nil;
	    stack = next_cons;
	    sub = tree_ordering_pop_store;
	}
	else if (IDENTITY(temp_1)) {
	    gensymed_symbol = ACCESS_ONCE(ISVREF(temp_1,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	    ab_queue_form_ = gensymed_symbol;
	    ab_next_queue_element_ = Nil;
	    gensymed_symbol = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	    if (ab_queue_form_)
		ab_next_queue_element_ = 
			constant_queue_next(ISVREF(ab_queue_form_,
			(SI_Long)2L),ab_queue_form_);
	  next_loop_3:
	    if ( !TRUEP(ab_next_queue_element_))
		goto end_loop_3;
	    gensymed_symbol = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	    ab_next_queue_element_ = 
		    constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	    ab_loopvar__2 = tree_ordering_cons_1(gensymed_symbol,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop_3;
	  end_loop_3:
	    infs = ab_loopvar_;
	    goto end_1;
	    infs = Qnil;
	  end_1:;
	    if ( !TRUEP(infs))
		sub = temp_1;
	    else {
		temp_2 = T ? infs : 
			copy_list_using_tree_ordering_conses_1(infs);
		temp_3 = tree_ordering_cons_1(Tree_traversal_marker,Nil);
		stack = nconc2(temp_2,nconc2(temp_3,
			nconc2(tree_ordering_cons_1(temp_1,Nil),stack)));
	    }
	}
	if (sub) {
	    svref_new_value = IFIX(ISVREF(sub,(SI_Long)5L)) &  ~(SI_Long)2048L;
	    ISVREF(sub,(SI_Long)5L) = FIX(svref_new_value);
	}
	goto next_loop_2;
      end_loop_2:
	if (stack)
	    reclaim_tree_ordering_list_1(stack);
    }
    return VALUES_1(Nil);
}

/* REMOVE-AS-BLOCK-BEING-DRAGGED */
Object remove_as_block_being_dragged(block)
    Object block;
{
    x_note_fn_call(128,106);
    erase_transfer_representations_of_block(block);
    remove_object_from_dragging_context(block);
    return remove_block_from_xor_overlay(block);
}

/* REMOVE-AS-BLOCK-BEING-MOVED */
Object remove_as_block_being_moved(block)
    Object block;
{
    Object still_being_transfered_qm, dragging_state, ab_loop_list_;
    Object svref_new_value;

    x_note_fn_call(128,107);
    still_being_transfered_qm = Nil;
    dragging_state = Nil;
    ab_loop_list_ = Current_dragging_states;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    dragging_state = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (memq_function(block,ISVREF(dragging_state,(SI_Long)3L))) {
	if (EQ(ISVREF(dragging_state,(SI_Long)21L),Qmove_dragging_style)) {
	    svref_new_value = delete_dragging_element_1(block,
		    ISVREF(dragging_state,(SI_Long)3L));
	    SVREF(dragging_state,FIX((SI_Long)3L)) = svref_new_value;
	}
	else if (EQ(ISVREF(dragging_state,(SI_Long)21L),
		Qtransfer_dragging_style))
	    still_being_transfered_qm = T;
    }
    goto next_loop;
  end_loop:
    if ( !TRUEP(still_being_transfered_qm))
	remove_block_from_xor_overlay(block);
    return VALUES_1(Qnil);
}

/* REMOVE-BLOCK-FROM-XOR-OVERLAY */
Object remove_block_from_xor_overlay(block)
    Object block;
{
    Object stack, sub, tree_ordering_pop_store, cons_1, next_cons, temp;
    Object svref_arg_2, temp_1, gensymed_symbol, ab_queue_form_;
    Object ab_next_queue_element_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object infs, temp_2, temp_3;
    SI_Long svref_new_value;
    char value;

    x_note_fn_call(128,108);
    update_images_of_block(block,T,Nil);
    stack = tree_ordering_cons_1(block,Nil);
    sub = Nil;
  next_loop:
    if ( !TRUEP(stack))
	goto end_loop;
    tree_ordering_pop_store = Nil;
    cons_1 = stack;
    if (cons_1) {
	tree_ordering_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qtree_ordering);
	if (ISVREF(Available_tree_ordering_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_tree_ordering_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_tree_ordering_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_tree_ordering_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_tree_ordering_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    stack = next_cons;
    temp_1 = tree_ordering_pop_store;
    sub = Nil;
    if (EQ(temp_1,Tree_traversal_marker)) {
	tree_ordering_pop_store = Nil;
	cons_1 = stack;
	if (cons_1) {
	    tree_ordering_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qtree_ordering);
	    if (ISVREF(Available_tree_ordering_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_tree_ordering_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = cons_1;
		temp = Available_tree_ordering_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    else {
		temp = Available_tree_ordering_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
		temp = Available_tree_ordering_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	stack = next_cons;
	sub = tree_ordering_pop_store;
    }
    else if (IDENTITY(temp_1)) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(temp_1,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	ab_queue_form_ = gensymed_symbol;
	ab_next_queue_element_ = Nil;
	gensymed_symbol = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	if (ab_queue_form_)
	    ab_next_queue_element_ = 
		    constant_queue_next(ISVREF(ab_queue_form_,(SI_Long)2L),
		    ab_queue_form_);
      next_loop_1:
	if ( !TRUEP(ab_next_queue_element_))
	    goto end_loop_1;
	gensymed_symbol = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	ab_next_queue_element_ = 
		constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	ab_loopvar__2 = tree_ordering_cons_1(gensymed_symbol,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_1;
      end_loop_1:
	infs = ab_loopvar_;
	goto end_1;
	infs = Qnil;
      end_1:;
	if ( !TRUEP(infs))
	    sub = temp_1;
	else {
	    temp_2 = T ? infs : copy_list_using_tree_ordering_conses_1(infs);
	    temp_3 = tree_ordering_cons_1(Tree_traversal_marker,Nil);
	    stack = nconc2(temp_2,nconc2(temp_3,
		    nconc2(tree_ordering_cons_1(temp_1,Nil),stack)));
	}
    }
    if (sub) {
	svref_new_value = IFIX(ISVREF(sub,(SI_Long)5L)) &  ~(SI_Long)2048L;
	ISVREF(sub,(SI_Long)5L) = FIX(svref_new_value);
	value = (SI_Long)0L != (IFIX(ISVREF(sub,(SI_Long)5L)) & (SI_Long)512L);
	if (value) {
	    svref_new_value = IFIX(ISVREF(sub,(SI_Long)5L)) | (SI_Long)1024L;
	    ISVREF(sub,(SI_Long)5L) = FIX(svref_new_value);
	}
	else {
	    svref_new_value = IFIX(ISVREF(sub,(SI_Long)5L)) &  ~(SI_Long)1024L;
	    ISVREF(sub,(SI_Long)5L) = FIX(svref_new_value);
	}
    }
    goto next_loop;
  end_loop:
    if (stack)
	reclaim_tree_ordering_list_1(stack);
    return update_images_of_block(block,Nil,Nil);
}

/* RECOMPUTE-EXTERNAL-CONNECTIONS-FOR-DRAGGING-STATES */
Object recompute_external_connections_for_dragging_states(block)
    Object block;
{
    Object dragging_state, ab_loop_list_, objects_being_dragged, new_objects;
    Object new_external_connections;
    Object result;

    x_note_fn_call(128,109);
    dragging_state = Nil;
    ab_loop_list_ = Current_dragging_states;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    dragging_state = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(ISVREF(dragging_state,(SI_Long)21L),Qmove_dragging_style) && 
	    memq_function(block,ISVREF(dragging_state,(SI_Long)3L))) {
	objects_being_dragged = 
		copy_list_using_dragging_conses_1(ISVREF(dragging_state,
		(SI_Long)3L));
	reclaim_dragging_list_1(ISVREF(dragging_state,(SI_Long)3L));
	reclaim_dragging_list_1(ISVREF(dragging_state,(SI_Long)6L));
	SVREF(dragging_state,FIX((SI_Long)3L)) = Nil;
	SVREF(dragging_state,FIX((SI_Long)6L)) = Nil;
	result = make_outline_for_blocks_to_drag(objects_being_dragged,T);
	MVS_2(result,new_objects,new_external_connections);
	SVREF(dragging_state,FIX((SI_Long)3L)) = new_objects;
	SVREF(dragging_state,FIX((SI_Long)6L)) = new_external_connections;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* REDRAW-TRANSFER-REPRESENTATIONS-OF-BLOCK */
Object redraw_transfer_representations_of_block(block,erase_p)
    Object block, erase_p;
{
    Object dragging_state, ab_loop_list_, dragger_x, dragger_y, image_plane;
    Object current_workstation_1, current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(12);
    Object result;

    x_note_fn_call(128,110);
    SAVE_STACK();
    if ((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & (SI_Long)2048L)) {
	dragging_state = Nil;
	ab_loop_list_ = Current_dragging_states;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	dragging_state = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(ISVREF(dragging_state,(SI_Long)21L),
		Qtransfer_dragging_style) && memq_function(block,
		ISVREF(dragging_state,(SI_Long)3L))) {
	    dragger_x = ISVREF(dragging_state,(SI_Long)10L);
	    dragger_y = ISVREF(dragging_state,(SI_Long)11L);
	    image_plane = ISVREF(dragging_state,(SI_Long)5L);
	    if (image_plane && ISVREF(image_plane,(SI_Long)5L)) {
		LOCK(For_workstation);
		if (PUSH_UNWIND_PROTECT(0)) {
		    current_workstation_1 = 
			    ISVREF(ISVREF(ISVREF(image_plane,(SI_Long)2L),
			    (SI_Long)2L),(SI_Long)2L);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
			    11);
		      current_workstation_window = 
			      ISVREF(Current_workstation,(SI_Long)1L);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_window,Qcurrent_workstation_window,current_workstation_window,
			      10);
			current_g2_window_for_this_workstation_qm = 
				ISVREF(Current_workstation,(SI_Long)25L);
			PUSH_SPECIAL_WITH_SYMBOL(Current_g2_window_for_this_workstation_qm,Qcurrent_g2_window_for_this_workstation_qm,current_g2_window_for_this_workstation_qm,
				9);
			  type_of_current_workstation_window = 
				  ISVREF(Current_workstation_window,
				  (SI_Long)1L);
			  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_window,Qtype_of_current_workstation_window,type_of_current_workstation_window,
				  8);
			    current_workstation_native_window_qm = 
				    ISVREF(Current_workstation_window,
				    (SI_Long)17L);
			    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
				    7);
			      temp = ISVREF(Current_workstation,(SI_Long)17L);
			      current_workstation_context = CAR(temp);
			      PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_context,Qcurrent_workstation_context,current_workstation_context,
				      6);
				type_of_current_workstation_context = 
					ISVREF(Current_workstation_context,
					(SI_Long)1L);
				PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_context,Qtype_of_current_workstation_context,type_of_current_workstation_context,
					5);
				  specific_structure_for_current_workstation_context 
					  = 
					  ISVREF(Current_workstation_context,
					  (SI_Long)2L);
				  PUSH_SPECIAL_WITH_SYMBOL(Specific_structure_for_current_workstation_context,Qspecific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
					  4);
				    current_workstation_detail_pane = 
					    detail_pane(Current_workstation_window);
				    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_detail_pane,Qcurrent_workstation_detail_pane,current_workstation_detail_pane,
					    3);
				      current_g2_user_mode_qm = 
					      ISVREF(Current_workstation,
					      (SI_Long)19L);
				      PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
					      2);
					new_g2_classic_ui_p = 
						get_value_for_current_workstation_new_g2_classic_ui_p();
					PUSH_SPECIAL_WITH_SYMBOL(New_g2_classic_ui_p,Qnew_g2_classic_ui_p,new_g2_classic_ui_p,
						1);
					  servicing_workstation_qm = T;
					  PUSH_SPECIAL_WITH_SYMBOL(Servicing_workstation_qm,Qservicing_workstation_qm,servicing_workstation_qm,
						  0);
					    shift_and_draw_blocks_being_transferred(dragging_state,
						    image_plane,dragger_x,
						    dragger_y,erase_p, 
						    !TRUEP(erase_p) ? T : Nil);
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
		POP_UNWIND_PROTECT(0);
		UNLOCK(For_workstation);
		CONTINUE_UNWINDING(0);
	    }
	}
	goto next_loop;
      end_loop:
	RESTORE_STACK();
	return VALUES_1(Qnil);
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

/* ERASE-TRANSFER-REPRESENTATIONS-OF-BLOCK */
Object erase_transfer_representations_of_block(block)
    Object block;
{
    Object dragging_state, ab_loop_list_, image_plane_qm, gensym_window;
    Object left_edge_of_draw_area, top_edge_of_draw_area;
    Object right_edge_of_draw_area, bottom_edge_of_draw_area;
    Object current_image_x_scale, current_image_y_scale;
    Object current_x_origin_of_drawing, current_y_origin_of_drawing, temp;
    Object current_frame_transform_qm, current_window_1, drawing_on_window;
    Object current_drawing_transfer_mode, type_of_current_window;
    Object current_native_window_qm, current_color_map;
    Object current_background_color_value, current_foreground_color_value;
    Object defer_notifications_qm, current_pane, current_image_plane;
    Object loose_left_edge_of_visible_workspace_area;
    Object loose_top_edge_of_visible_workspace_area;
    Object loose_right_edge_of_visible_workspace_area;
    Object loose_bottom_edge_of_visible_workspace_area, color_or_metacolor;
    Object background_color_or_metacolor, outer_native_image_plane;
    Object current_native_image_plane, color_value, old_color_value;
    Object icp_output_port_qm, icp_socket_qm, i_am_alive_info_qm;
    Object icp_output_port_qm_1, current_icp_port, current_icp_socket;
    Object disable_resumability, number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, aref_arg_1;
    char temp_1;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_stack_pointer;
    Declare_catch(3);
    Declare_special(53);
    Object result;

    x_note_fn_call(128,111);
    SAVE_STACK();
    dragging_state = Nil;
    ab_loop_list_ = Current_dragging_states;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    dragging_state = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(ISVREF(dragging_state,(SI_Long)21L),Qtransfer_dragging_style) 
	    && memq_function(block,ISVREF(dragging_state,(SI_Long)3L))) {
	image_plane_qm = ISVREF(dragging_state,(SI_Long)5L);
	if (image_plane_qm) {
	    gensym_window = ISVREF(ISVREF(image_plane_qm,(SI_Long)2L),
		    (SI_Long)2L);
	    left_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)7L);
	    top_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)8L);
	    right_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)9L);
	    bottom_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)10L);
	    PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
		    52);
	      PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
		      51);
		PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
			50);
		  PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
			  49);
		    current_image_x_scale = FIX((SI_Long)4096L);
		    current_image_y_scale = FIX((SI_Long)4096L);
		    current_x_origin_of_drawing = FIX((SI_Long)0L);
		    current_y_origin_of_drawing = FIX((SI_Long)0L);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
			    48);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
			      47);
			PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
				46);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
				  45);
			    left_edge_of_draw_area = Left_edge_of_draw_area;
			    top_edge_of_draw_area = Top_edge_of_draw_area;
			    right_edge_of_draw_area = Right_edge_of_draw_area;
			    bottom_edge_of_draw_area = 
				    Bottom_edge_of_draw_area;
			    PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
				    44);
			      PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
				      43);
				PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
					42);
				  PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
					  41);
				    temp = ISVREF(image_plane_qm,(SI_Long)6L);
				    Left_edge_of_draw_area = 
					    FIXNUM_MAX(temp,
					    Left_edge_of_draw_area);
				    temp = ISVREF(image_plane_qm,(SI_Long)7L);
				    Top_edge_of_draw_area = 
					    FIXNUM_MAX(temp,
					    Top_edge_of_draw_area);
				    temp = ISVREF(image_plane_qm,(SI_Long)8L);
				    Right_edge_of_draw_area = 
					    FIXNUM_MIN(temp,
					    Right_edge_of_draw_area);
				    temp = ISVREF(image_plane_qm,(SI_Long)9L);
				    Bottom_edge_of_draw_area = 
					    FIXNUM_MIN(temp,
					    Bottom_edge_of_draw_area);
				    if (FIXNUM_LT(Left_edge_of_draw_area,
					    Right_edge_of_draw_area) && 
					    FIXNUM_LT(Top_edge_of_draw_area,
					    Bottom_edge_of_draw_area)) {
					left_edge_of_draw_area = 
						Left_edge_of_draw_area;
					top_edge_of_draw_area = 
						Top_edge_of_draw_area;
					right_edge_of_draw_area = 
						Right_edge_of_draw_area;
					bottom_edge_of_draw_area = 
						Bottom_edge_of_draw_area;
					PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
						40);
					  PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
						  39);
					    PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
						    38);
					      PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
						      37);
						temp = 
							ISVREF(image_plane_qm,
							(SI_Long)19L);
						Left_edge_of_draw_area = 
							FIXNUM_MAX(temp,
							Left_edge_of_draw_area);
						temp = 
							ISVREF(image_plane_qm,
							(SI_Long)20L);
						Top_edge_of_draw_area = 
							FIXNUM_MAX(temp,
							Top_edge_of_draw_area);
						temp = 
							ISVREF(image_plane_qm,
							(SI_Long)21L);
						Right_edge_of_draw_area = 
							FIXNUM_MIN(temp,
							Right_edge_of_draw_area);
						temp = 
							ISVREF(image_plane_qm,
							(SI_Long)22L);
						Bottom_edge_of_draw_area = 
							FIXNUM_MIN(temp,
							Bottom_edge_of_draw_area);
						if (FIXNUM_LT(Left_edge_of_draw_area,
							Right_edge_of_draw_area) 
							&& 
							FIXNUM_LT(Top_edge_of_draw_area,
							Bottom_edge_of_draw_area)) 
							    {
						    current_frame_transform_qm 
							    = Nil;
						    current_image_x_scale 
							    = 
							    ISVREF(image_plane_qm,
							    (SI_Long)11L);
						    current_image_y_scale 
							    = 
							    ISVREF(image_plane_qm,
							    (SI_Long)12L);
						    current_x_origin_of_drawing 
							    = 
							    ISVREF(image_plane_qm,
							    (SI_Long)13L);
						    current_y_origin_of_drawing 
							    = 
							    ISVREF(image_plane_qm,
							    (SI_Long)14L);
						    PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
							    36);
						      PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
							      35);
							PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
								34);
							  PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
								  33);
							    PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
								    32);
							      LOCK(On_window_without_drawing);
							      if (PUSH_UNWIND_PROTECT(2)) 
									  {
								  current_window_1 
									  = 
									  ISVREF(ISVREF(image_plane_qm,
									  (SI_Long)2L),
									  (SI_Long)2L);
								  PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
									  31);
								    drawing_on_window 
									    = 
									    Nil;
								    PUSH_SPECIAL_WITH_SYMBOL(Drawing_on_window,Qdrawing_on_window,drawing_on_window,
									    30);
								      current_drawing_transfer_mode 
									      = 
									      EQ(Current_drawing_transfer_mode,
									      Kxor) 
									      ?
									       
									      Current_drawing_transfer_mode 
									      :
									       
									      ISVREF(Current_window,
									      (SI_Long)30L);
								      PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
									      29);
									type_of_current_window 
										= 
										ISVREF(Current_window,
										(SI_Long)1L);
									PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
										28);
									  current_native_window_qm 
										  = 
										  ISVREF(Current_window,
										  (SI_Long)17L);
									  PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
										  27);
									    current_color_map 
										    = 
										    ISVREF(Current_window,
										    (SI_Long)20L);
									    PUSH_SPECIAL_WITH_SYMBOL(Current_color_map,Qcurrent_color_map,current_color_map,
										    26);
									      temp 
										      = 
										      ISVREF(Current_color_map,
										      (SI_Long)5L);
									      if (temp);
									      else
										  temp 
											  = 
											  map_to_color_value_1(Qwhite);
									      current_background_color_value 
										      = 
										      temp;
									      PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
										      25);
										temp 
											= 
											ISVREF(Current_color_map,
											(SI_Long)4L);
										if (temp);
										else
										    temp 
											    = 
											    map_to_color_value_1(Qblack);
										current_foreground_color_value 
											= 
											temp;
										PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
											24);
										  defer_notifications_qm 
											  = 
											  T;
										  PUSH_SPECIAL_WITH_SYMBOL(Defer_notifications_qm,Qdefer_notifications_qm,defer_notifications_qm,
											  23);
										    LOCK(On_window_with_drawing);
										    if (PUSH_UNWIND_PROTECT(1)) 
												{
											drawing_on_window 
												= 
												T;
											PUSH_SPECIAL_WITH_SYMBOL(Drawing_on_window,Qdrawing_on_window,drawing_on_window,
												22);
											  if (EQ(Type_of_current_window,
												  Qx11_window)) 
												      {
											      LOCK(For_image_plane);
											      if (PUSH_UNWIND_PROTECT(0)) 
													  {
												  current_pane 
													  = 
													  ISVREF(image_plane_qm,
													  (SI_Long)2L);
												  current_image_plane 
													  = 
													  image_plane_qm;
												  loose_left_edge_of_visible_workspace_area 
													  = 
													  ISVREF(image_plane_qm,
													  (SI_Long)23L);
												  loose_top_edge_of_visible_workspace_area 
													  = 
													  ISVREF(image_plane_qm,
													  (SI_Long)24L);
												  loose_right_edge_of_visible_workspace_area 
													  = 
													  ISVREF(image_plane_qm,
													  (SI_Long)25L);
												  loose_bottom_edge_of_visible_workspace_area 
													  = 
													  ISVREF(image_plane_qm,
													  (SI_Long)26L);
												  color_or_metacolor 
													  = 
													  ISVREF(image_plane_qm,
													  (SI_Long)5L) 
													  ?
													   
													  ISVREF(ISVREF(image_plane_qm,
													  (SI_Long)5L),
													  (SI_Long)22L) 
													  :
													   
													  Nil;
												  if (color_or_metacolor);
												  else
												      color_or_metacolor 
													      = 
													      Qblack;
												  if (EQ(color_or_metacolor,
													  Qtransparent) 
													  || 
													  EQ(color_or_metacolor,
													  Qbackground)) 
													      {
												      background_color_or_metacolor 
													      = 
													      ISVREF(image_plane_qm,
													      (SI_Long)5L) 
													      ?
													       
													      ISVREF(ISVREF(image_plane_qm,
													      (SI_Long)5L),
													      (SI_Long)21L) 
													      :
													       
													      Nil;
												      if (background_color_or_metacolor);
												      else
													  background_color_or_metacolor 
														  = 
														  Qwhite;
												      if (EQ(background_color_or_metacolor,
													      Qforeground) 
													      || 
													      EQ(background_color_or_metacolor,
													      Qworkspace_foreground)) 
														  {
													  temp 
														  = 
														  ISVREF(Current_color_map,
														  (SI_Long)4L);
													  if (temp);
													  else
													      temp 
														      = 
														      map_to_color_value_1(Qblack);
													  current_foreground_color_value 
														  = 
														  temp;
												      }
												      else if (EQ(background_color_or_metacolor,
													      Qtransparent) 
													      || 
													      EQ(background_color_or_metacolor,
													      Qbackground)) 
														  {
													  temp 
														  = 
														  ISVREF(Current_color_map,
														  (SI_Long)5L);
													  if (temp);
													  else
													      temp 
														      = 
														      map_to_color_value_1(Qwhite);
													  current_foreground_color_value 
														  = 
														  temp;
												      }
												      else
													  current_foreground_color_value 
														  = 
														  EQ(background_color_or_metacolor,
														  ISVREF(Current_color_map,
														  (SI_Long)6L)) 
														  ?
														   
														  ISVREF(Current_color_map,
														  (SI_Long)7L) 
														  :
														   
														  map_to_color_value_1(background_color_or_metacolor);
												  }
												  else if (EQ(color_or_metacolor,
													  Qforeground) 
													  || 
													  EQ(color_or_metacolor,
													  Qworkspace_foreground)) 
													      {
												      temp 
													      = 
													      ISVREF(Current_color_map,
													      (SI_Long)4L);
												      if (temp);
												      else
													  temp 
														  = 
														  map_to_color_value_1(Qblack);
												      current_foreground_color_value 
													      = 
													      temp;
												  }
												  else
												      current_foreground_color_value 
													      = 
													      EQ(color_or_metacolor,
													      ISVREF(Current_color_map,
													      (SI_Long)6L)) 
													      ?
													       
													      ISVREF(Current_color_map,
													      (SI_Long)7L) 
													      :
													       
													      map_to_color_value_1(color_or_metacolor);
												  PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
													  9);
												    PUSH_SPECIAL_WITH_SYMBOL(Loose_bottom_edge_of_visible_workspace_area,Qloose_bottom_edge_of_visible_workspace_area,loose_bottom_edge_of_visible_workspace_area,
													    8);
												      PUSH_SPECIAL_WITH_SYMBOL(Loose_right_edge_of_visible_workspace_area,Qloose_right_edge_of_visible_workspace_area,loose_right_edge_of_visible_workspace_area,
													      7);
													PUSH_SPECIAL_WITH_SYMBOL(Loose_top_edge_of_visible_workspace_area,Qloose_top_edge_of_visible_workspace_area,loose_top_edge_of_visible_workspace_area,
														6);
													  PUSH_SPECIAL_WITH_SYMBOL(Loose_left_edge_of_visible_workspace_area,Qloose_left_edge_of_visible_workspace_area,loose_left_edge_of_visible_workspace_area,
														  5);
													    PUSH_SPECIAL_WITH_SYMBOL(Current_image_plane,Qcurrent_image_plane,current_image_plane,
														    4);
													      PUSH_SPECIAL_WITH_SYMBOL(Current_pane,Qcurrent_pane,current_pane,
														      3);
														outer_native_image_plane 
															= 
															Current_native_image_plane;
														PUSH_SPECIAL_WITH_SYMBOL(Outer_native_image_plane,Qouter_native_image_plane,outer_native_image_plane,
															2);
														  current_native_image_plane 
															  = 
															  image_plane_qm;
														  PUSH_SPECIAL_WITH_SYMBOL(Current_native_image_plane,Qcurrent_native_image_plane,current_native_image_plane,
															  1);
														    if ( 
															    !EQ(Outer_native_image_plane,
															    Current_native_image_plane))
															nip_begin_drawing(Current_native_image_plane);
														    color_or_metacolor 
															    = 
															    ISVREF(image_plane_qm,
															    (SI_Long)5L) 
															    ?
															     
															    ISVREF(ISVREF(image_plane_qm,
															    (SI_Long)5L),
															    (SI_Long)21L) 
															    :
															     
															    Nil;
														    if (color_or_metacolor);
														    else
															color_or_metacolor 
																= 
																Qwhite;
														    if (EQ(color_or_metacolor,
															    Qtransparent) 
															    || 
															    EQ(color_or_metacolor,
															    Qbackground)) 
																{
															color_value 
																= 
																ISVREF(Current_color_map,
																(SI_Long)5L);
															if (color_value);
															else
															    color_value 
																    = 
																    map_to_color_value_1(Qwhite);
														    }
														    else if (EQ(color_or_metacolor,
															    Qforeground) 
															    || 
															    EQ(color_or_metacolor,
															    Qworkspace_foreground)) 
																{
															temp 
																= 
																ISVREF(image_plane_qm,
																(SI_Long)5L) 
																?
																 
																ISVREF(ISVREF(image_plane_qm,
																(SI_Long)5L),
																(SI_Long)22L) 
																:
																 
																Nil;
															if (temp);
															else
															    temp 
																    = 
																    Qblack;
															color_or_metacolor 
																= 
																temp;
															if (EQ(color_or_metacolor,
																Qtransparent) 
																|| 
																EQ(color_or_metacolor,
																Qbackground)) 
																    {
															    background_color_or_metacolor 
																    = 
																    ISVREF(image_plane_qm,
																    (SI_Long)5L) 
																    ?
																     
																    ISVREF(ISVREF(image_plane_qm,
																    (SI_Long)5L),
																    (SI_Long)21L) 
																    :
																     
																    Nil;
															    if (background_color_or_metacolor);
															    else
																background_color_or_metacolor 
																	= 
																	Qwhite;
															    if (EQ(background_color_or_metacolor,
																    Qforeground) 
																    || 
																    EQ(background_color_or_metacolor,
																    Qworkspace_foreground)) 
																	{
																color_value 
																	= 
																	ISVREF(Current_color_map,
																	(SI_Long)4L);
																if (color_value);
																else
																    color_value 
																	    = 
																	    map_to_color_value_1(Qblack);
															    }
															    else if (EQ(background_color_or_metacolor,
																    Qtransparent) 
																    || 
																    EQ(background_color_or_metacolor,
																    Qbackground)) 
																	{
																color_value 
																	= 
																	ISVREF(Current_color_map,
																	(SI_Long)5L);
																if (color_value);
																else
																    color_value 
																	    = 
																	    map_to_color_value_1(Qwhite);
															    }
															    else
																color_value 
																	= 
																	EQ(background_color_or_metacolor,
																	ISVREF(Current_color_map,
																	(SI_Long)6L)) 
																	?
																	 
																	ISVREF(Current_color_map,
																	(SI_Long)7L) 
																	:
																	 
																	map_to_color_value_1(background_color_or_metacolor);
															}
															else if (EQ(color_or_metacolor,
																Qforeground) 
																|| 
																EQ(color_or_metacolor,
																Qworkspace_foreground)) 
																    {
															    color_value 
																    = 
																    ISVREF(Current_color_map,
																    (SI_Long)4L);
															    if (color_value);
															    else
																color_value 
																	= 
																	map_to_color_value_1(Qblack);
															}
															else
															    color_value 
																    = 
																    EQ(color_or_metacolor,
																    ISVREF(Current_color_map,
																    (SI_Long)6L)) 
																    ?
																     
																    ISVREF(Current_color_map,
																    (SI_Long)7L) 
																    :
																     
																    map_to_color_value_1(color_or_metacolor);
														    }
														    else
															color_value 
																= 
																EQ(color_or_metacolor,
																ISVREF(Current_color_map,
																(SI_Long)6L)) 
																?
																 
																ISVREF(Current_color_map,
																(SI_Long)7L) 
																:
																 
																map_to_color_value_1(color_or_metacolor);
														    old_color_value 
															    = 
															    Current_background_color_value;
														    current_background_color_value 
															    = 
															    Current_background_color_value;
														    PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
															    0);
														      set_current_background_color_value(color_value);
														      draw_block_or_blocks_in_dragging_state(dragging_state,
															      block);
														      set_current_background_color_value(old_color_value);
														    POP_SPECIAL();
														    if ( 
															    !EQ(Outer_native_image_plane,
															    Current_native_image_plane))
															nip_end_drawing(Current_native_image_plane);
														  POP_SPECIAL();
														  if (Current_native_image_plane) 
															      {
														      if ( 
															      !EQ(image_plane_qm,
															      Current_native_image_plane))
															  nip_begin_drawing(Current_native_image_plane);
														  }
														POP_SPECIAL();
													      POP_SPECIAL();
													    POP_SPECIAL();
													  POP_SPECIAL();
													POP_SPECIAL();
												      POP_SPECIAL();
												    POP_SPECIAL();
												  POP_SPECIAL();
											      }
											      POP_UNWIND_PROTECT(0);
											      UNLOCK(For_image_plane);
											      CONTINUE_UNWINDING(0);
											      if (Flush_graphics_immediately_qm)
												  sync_graphics_on_current_window();
											  }
											  else if (EQ(Type_of_current_window,
												  Qicp)) 
												      {
											      icp_output_port_qm 
												      = 
												      ISVREF(Current_window,
												      (SI_Long)12L);
											      icp_socket_qm 
												      = 
												      icp_output_port_qm 
												      ?
												       
												      ISVREF(icp_output_port_qm,
												      (SI_Long)2L) 
												      :
												       
												      Qnil;
											      if (icp_socket_qm) 
													  {
												  i_am_alive_info_qm 
													  = 
													  ISVREF(icp_socket_qm,
													  (SI_Long)24L);
												  temp_1 
													  = 
													   
													  !TRUEP(i_am_alive_info_qm);
												  if (temp_1);
												  else
												      temp_1 
													      = 
													       
													      !TRUEP(Do_icp_flow_control_qm);
												  if (temp_1);
												  else
												      temp_1 
													      = 
													       
													      !TRUEP(ISVREF(i_am_alive_info_qm,
													      (SI_Long)2L));
											      }
											      else
												  temp_1 
													  = 
													  TRUEP(Nil);
											      if (temp_1) 
													  {
												  icp_output_port_qm_1 
													  = 
													  ISVREF(Current_window,
													  (SI_Long)12L);
												  if (icp_output_port_qm_1 
													  && 
													  icp_connection_open_p(ISVREF(icp_output_port_qm_1,
													  (SI_Long)2L))) 
													      {
												      current_icp_port 
													      = 
													      icp_output_port_qm_1;
												      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
													      21);
													current_icp_socket 
														= 
														ISVREF(Current_icp_port,
														(SI_Long)2L);
													PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
														20);
													  temp 
														  = 
														  IFIX(ISVREF(Current_icp_socket,
														  (SI_Long)22L)) 
														  >= 
														  (SI_Long)17L 
														  ?
														   
														  ISVREF(Current_icp_socket,
														  (SI_Long)53L) 
														  :
														   
														  Nil;
													  if (temp);
													  else
													      temp 
														      = 
														      EQ(ISVREF(Current_icp_socket,
														      (SI_Long)25L),
														      Qtelewindows) 
														      ?
														       T : Nil;
													  disable_resumability 
														  = 
														  temp;
													  PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
														  19);
													    number_of_icp_bytes_for_message_series 
														    = 
														    FIX((SI_Long)0L);
													    PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
														    18);
													      icp_buffers_for_message_group 
														      = 
														      Nil;
													      PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
														      17);
														icp_buffer_of_start_of_message_series_qm 
															= 
															Nil;
														PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
															16);
														  icp_byte_position_of_start_of_message_series_qm 
															  = 
															  Nil;
														  PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
															  15);
														    number_of_icp_bytes_to_fill_buffer 
															    = 
															    FIX((SI_Long)0L);
														    PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
															    14);
														      current_icp_buffer 
															      = 
															      Nil;
														      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
															      13);
															current_write_icp_byte_position 
																= 
																Nil;
															PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
																12);
															  number_of_icp_bytes_in_message_group 
																  = 
																  FIX((SI_Long)0L);
															  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
																  11);
															    writing_icp_message_group 
																    = 
																    FIXNUM_ADD1(Writing_icp_message_group);
															    PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
																    10);
															      gensymed_symbol 
																      = 
																      Nil;
															      gensymed_symbol_1 
																      = 
																      0.0;
															      gensymed_symbol_2 
																      = 
																      0.0;
															      if (Profiling_enabled_qm) 
																	  {
																  gensymed_symbol 
																	  = 
																	  T;
																  gensymed_symbol_1 
																	  = 
																	  DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
																	  (SI_Long)2L),
																	  (SI_Long)0L);
																  gensymed_symbol_2 
																	  = 
																	  g2ext_unix_time_as_float();
																  aref_arg_1 
																	  = 
																	  ISVREF(Profiling_enabled_qm,
																	  (SI_Long)2L);
																  DFLOAT_ISASET_1(aref_arg_1,
																	  (SI_Long)0L,
																	  gensymed_symbol_2);
															      }
															      if (icp_connection_open_p(Current_icp_socket) 
																      && 
																       
																      !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
																	  {
																  synchronize_icp_on_window_with_drawing(Current_window,
																	  Left_edge_of_draw_area,
																	  Top_edge_of_draw_area,
																	  Right_edge_of_draw_area,
																	  Bottom_edge_of_draw_area);
																  LOCK(For_image_plane);
																  if (PUSH_UNWIND_PROTECT(0)) 
																	      {
																      current_pane 
																	      = 
																	      ISVREF(image_plane_qm,
																	      (SI_Long)2L);
																      current_image_plane 
																	      = 
																	      image_plane_qm;
																      loose_left_edge_of_visible_workspace_area 
																	      = 
																	      ISVREF(image_plane_qm,
																	      (SI_Long)23L);
																      loose_top_edge_of_visible_workspace_area 
																	      = 
																	      ISVREF(image_plane_qm,
																	      (SI_Long)24L);
																      loose_right_edge_of_visible_workspace_area 
																	      = 
																	      ISVREF(image_plane_qm,
																	      (SI_Long)25L);
																      loose_bottom_edge_of_visible_workspace_area 
																	      = 
																	      ISVREF(image_plane_qm,
																	      (SI_Long)26L);
																      color_or_metacolor 
																	      = 
																	      ISVREF(image_plane_qm,
																	      (SI_Long)5L) 
																	      ?
																	       
																	      ISVREF(ISVREF(image_plane_qm,
																	      (SI_Long)5L),
																	      (SI_Long)22L) 
																	      :
																	       
																	      Nil;
																      if (color_or_metacolor);
																      else
																	  color_or_metacolor 
																		  = 
																		  Qblack;
																      if (EQ(color_or_metacolor,
																	      Qtransparent) 
																	      || 
																	      EQ(color_or_metacolor,
																	      Qbackground)) 
																		  {
																	  background_color_or_metacolor 
																		  = 
																		  ISVREF(image_plane_qm,
																		  (SI_Long)5L) 
																		  ?
																		   
																		  ISVREF(ISVREF(image_plane_qm,
																		  (SI_Long)5L),
																		  (SI_Long)21L) 
																		  :
																		   
																		  Nil;
																	  if (background_color_or_metacolor);
																	  else
																	      background_color_or_metacolor 
																		      = 
																		      Qwhite;
																	  if (EQ(background_color_or_metacolor,
																		  Qforeground) 
																		  || 
																		  EQ(background_color_or_metacolor,
																		  Qworkspace_foreground)) 
																		      {
																	      temp 
																		      = 
																		      ISVREF(Current_color_map,
																		      (SI_Long)4L);
																	      if (temp);
																	      else
																		  temp 
																			  = 
																			  map_to_color_value_1(Qblack);
																	      current_foreground_color_value 
																		      = 
																		      temp;
																	  }
																	  else if (EQ(background_color_or_metacolor,
																		  Qtransparent) 
																		  || 
																		  EQ(background_color_or_metacolor,
																		  Qbackground)) 
																		      {
																	      temp 
																		      = 
																		      ISVREF(Current_color_map,
																		      (SI_Long)5L);
																	      if (temp);
																	      else
																		  temp 
																			  = 
																			  map_to_color_value_1(Qwhite);
																	      current_foreground_color_value 
																		      = 
																		      temp;
																	  }
																	  else
																	      current_foreground_color_value 
																		      = 
																		      EQ(background_color_or_metacolor,
																		      ISVREF(Current_color_map,
																		      (SI_Long)6L)) 
																		      ?
																		       
																		      ISVREF(Current_color_map,
																		      (SI_Long)7L) 
																		      :
																		       
																		      map_to_color_value_1(background_color_or_metacolor);
																      }
																      else if (EQ(color_or_metacolor,
																	      Qforeground) 
																	      || 
																	      EQ(color_or_metacolor,
																	      Qworkspace_foreground)) 
																		  {
																	  temp 
																		  = 
																		  ISVREF(Current_color_map,
																		  (SI_Long)4L);
																	  if (temp);
																	  else
																	      temp 
																		      = 
																		      map_to_color_value_1(Qblack);
																	  current_foreground_color_value 
																		  = 
																		  temp;
																      }
																      else
																	  current_foreground_color_value 
																		  = 
																		  EQ(color_or_metacolor,
																		  ISVREF(Current_color_map,
																		  (SI_Long)6L)) 
																		  ?
																		   
																		  ISVREF(Current_color_map,
																		  (SI_Long)7L) 
																		  :
																		   
																		  map_to_color_value_1(color_or_metacolor);
																      PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
																	      9);
																	PUSH_SPECIAL_WITH_SYMBOL(Loose_bottom_edge_of_visible_workspace_area,Qloose_bottom_edge_of_visible_workspace_area,loose_bottom_edge_of_visible_workspace_area,
																		8);
																	  PUSH_SPECIAL_WITH_SYMBOL(Loose_right_edge_of_visible_workspace_area,Qloose_right_edge_of_visible_workspace_area,loose_right_edge_of_visible_workspace_area,
																		  7);
																	    PUSH_SPECIAL_WITH_SYMBOL(Loose_top_edge_of_visible_workspace_area,Qloose_top_edge_of_visible_workspace_area,loose_top_edge_of_visible_workspace_area,
																		    6);
																	      PUSH_SPECIAL_WITH_SYMBOL(Loose_left_edge_of_visible_workspace_area,Qloose_left_edge_of_visible_workspace_area,loose_left_edge_of_visible_workspace_area,
																		      5);
																		PUSH_SPECIAL_WITH_SYMBOL(Current_image_plane,Qcurrent_image_plane,current_image_plane,
																			4);
																		  PUSH_SPECIAL_WITH_SYMBOL(Current_pane,Qcurrent_pane,current_pane,
																			  3);
																		    outer_native_image_plane 
																			    = 
																			    Current_native_image_plane;
																		    PUSH_SPECIAL_WITH_SYMBOL(Outer_native_image_plane,Qouter_native_image_plane,outer_native_image_plane,
																			    2);
																		      current_native_image_plane 
																			      = 
																			      image_plane_qm;
																		      PUSH_SPECIAL_WITH_SYMBOL(Current_native_image_plane,Qcurrent_native_image_plane,current_native_image_plane,
																			      1);
																			if ( 
																				!EQ(Outer_native_image_plane,
																				Current_native_image_plane))
																			    nip_begin_drawing(Current_native_image_plane);
																			color_or_metacolor 
																				= 
																				ISVREF(image_plane_qm,
																				(SI_Long)5L) 
																				?
																				 
																				ISVREF(ISVREF(image_plane_qm,
																				(SI_Long)5L),
																				(SI_Long)21L) 
																				:
																				 
																				Nil;
																			if (color_or_metacolor);
																			else
																			    color_or_metacolor 
																				    = 
																				    Qwhite;
																			if (EQ(color_or_metacolor,
																				Qtransparent) 
																				|| 
																				EQ(color_or_metacolor,
																				Qbackground)) 
																				    {
																			    color_value 
																				    = 
																				    ISVREF(Current_color_map,
																				    (SI_Long)5L);
																			    if (color_value);
																			    else
																				color_value 
																					= 
																					map_to_color_value_1(Qwhite);
																			}
																			else if (EQ(color_or_metacolor,
																				Qforeground) 
																				|| 
																				EQ(color_or_metacolor,
																				Qworkspace_foreground)) 
																				    {
																			    temp 
																				    = 
																				    ISVREF(image_plane_qm,
																				    (SI_Long)5L) 
																				    ?
																				     
																				    ISVREF(ISVREF(image_plane_qm,
																				    (SI_Long)5L),
																				    (SI_Long)22L) 
																				    :
																				     
																				    Nil;
																			    if (temp);
																			    else
																				temp 
																					= 
																					Qblack;
																			    color_or_metacolor 
																				    = 
																				    temp;
																			    if (EQ(color_or_metacolor,
																				    Qtransparent) 
																				    || 
																				    EQ(color_or_metacolor,
																				    Qbackground)) 
																					{
																				background_color_or_metacolor 
																					= 
																					ISVREF(image_plane_qm,
																					(SI_Long)5L) 
																					?
																					 
																					ISVREF(ISVREF(image_plane_qm,
																					(SI_Long)5L),
																					(SI_Long)21L) 
																					:
																					 
																					Nil;
																				if (background_color_or_metacolor);
																				else
																				    background_color_or_metacolor 
																					    = 
																					    Qwhite;
																				if (EQ(background_color_or_metacolor,
																					Qforeground) 
																					|| 
																					EQ(background_color_or_metacolor,
																					Qworkspace_foreground)) 
																					    {
																				    color_value 
																					    = 
																					    ISVREF(Current_color_map,
																					    (SI_Long)4L);
																				    if (color_value);
																				    else
																					color_value 
																						= 
																						map_to_color_value_1(Qblack);
																				}
																				else if (EQ(background_color_or_metacolor,
																					Qtransparent) 
																					|| 
																					EQ(background_color_or_metacolor,
																					Qbackground)) 
																					    {
																				    color_value 
																					    = 
																					    ISVREF(Current_color_map,
																					    (SI_Long)5L);
																				    if (color_value);
																				    else
																					color_value 
																						= 
																						map_to_color_value_1(Qwhite);
																				}
																				else
																				    color_value 
																					    = 
																					    EQ(background_color_or_metacolor,
																					    ISVREF(Current_color_map,
																					    (SI_Long)6L)) 
																					    ?
																					     
																					    ISVREF(Current_color_map,
																					    (SI_Long)7L) 
																					    :
																					     
																					    map_to_color_value_1(background_color_or_metacolor);
																			    }
																			    else if (EQ(color_or_metacolor,
																				    Qforeground) 
																				    || 
																				    EQ(color_or_metacolor,
																				    Qworkspace_foreground)) 
																					{
																				color_value 
																					= 
																					ISVREF(Current_color_map,
																					(SI_Long)4L);
																				if (color_value);
																				else
																				    color_value 
																					    = 
																					    map_to_color_value_1(Qblack);
																			    }
																			    else
																				color_value 
																					= 
																					EQ(color_or_metacolor,
																					ISVREF(Current_color_map,
																					(SI_Long)6L)) 
																					?
																					 
																					ISVREF(Current_color_map,
																					(SI_Long)7L) 
																					:
																					 
																					map_to_color_value_1(color_or_metacolor);
																			}
																			else
																			    color_value 
																				    = 
																				    EQ(color_or_metacolor,
																				    ISVREF(Current_color_map,
																				    (SI_Long)6L)) 
																				    ?
																				     
																				    ISVREF(Current_color_map,
																				    (SI_Long)7L) 
																				    :
																				     
																				    map_to_color_value_1(color_or_metacolor);
																			old_color_value 
																				= 
																				Current_background_color_value;
																			current_background_color_value 
																				= 
																				Current_background_color_value;
																			PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
																				0);
																			  set_current_background_color_value(color_value);
																			  draw_block_or_blocks_in_dragging_state(dragging_state,
																				  block);
																			  set_current_background_color_value(old_color_value);
																			POP_SPECIAL();
																			if ( 
																				!EQ(Outer_native_image_plane,
																				Current_native_image_plane))
																			    nip_end_drawing(Current_native_image_plane);
																		      POP_SPECIAL();
																		      if (Current_native_image_plane) 
																				  {
																			  if ( 
																				  !EQ(image_plane_qm,
																				  Current_native_image_plane))
																			      nip_begin_drawing(Current_native_image_plane);
																		      }
																		    POP_SPECIAL();
																		  POP_SPECIAL();
																		POP_SPECIAL();
																	      POP_SPECIAL();
																	    POP_SPECIAL();
																	  POP_SPECIAL();
																	POP_SPECIAL();
																      POP_SPECIAL();
																  }
																  POP_UNWIND_PROTECT(0);
																  UNLOCK(For_image_plane);
																  CONTINUE_UNWINDING(0);
																  if (Flush_graphics_immediately_qm 
																	  && 
																	  FIXNUM_NE(ISVREF(Current_icp_socket,
																	  (SI_Long)15L),
																	  Icp_connection_closed))
																      sync_graphics_on_current_window();
																  end_icp_message_group();
															      }
															      if (Profiling_enabled_qm) 
																	  {
																  gensymed_symbol_3 
																	  = 
																	  g2ext_unix_time_as_float();
																  gensymed_symbol_4 
																	  = 
																	  DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
																	  (SI_Long)2L),
																	  (SI_Long)0L);
																  gensymed_symbol_5 
																	  = 
																	  gensymed_symbol_3 
																	  - 
																	  gensymed_symbol_4;
																  aref_arg_1 
																	  = 
																	  ISVREF(Profiling_enabled_qm,
																	  (SI_Long)6L);
																  aref_new_value 
																	  = 
																	  gensymed_symbol_5 
																	  + 
																	  DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
																	  (SI_Long)6L),
																	  (SI_Long)0L);
																  DFLOAT_ISASET_1(aref_arg_1,
																	  (SI_Long)0L,
																	  aref_new_value);
																  aref_arg_1 
																	  = 
																	  ISVREF(Profiling_enabled_qm,
																	  (SI_Long)2L);
																  aref_new_value 
																	  = 
																	  gensymed_symbol 
																	  ?
																	   
																	  gensymed_symbol_1 
																	  + 
																	  gensymed_symbol_5 
																	  + 
																	  (gensymed_symbol_4 
																	  - 
																	  gensymed_symbol_2) 
																	  :
																	   
																	  gensymed_symbol_3;
																  DFLOAT_ISASET_1(aref_arg_1,
																	  (SI_Long)0L,
																	  aref_new_value);
															      }
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
											  }
											  else if (EQ(Type_of_current_window,
												  Qprinter)) 
												      {
											      LOCK(For_image_plane);
											      if (PUSH_UNWIND_PROTECT(0)) 
													  {
												  current_pane 
													  = 
													  ISVREF(image_plane_qm,
													  (SI_Long)2L);
												  current_image_plane 
													  = 
													  image_plane_qm;
												  loose_left_edge_of_visible_workspace_area 
													  = 
													  ISVREF(image_plane_qm,
													  (SI_Long)23L);
												  loose_top_edge_of_visible_workspace_area 
													  = 
													  ISVREF(image_plane_qm,
													  (SI_Long)24L);
												  loose_right_edge_of_visible_workspace_area 
													  = 
													  ISVREF(image_plane_qm,
													  (SI_Long)25L);
												  loose_bottom_edge_of_visible_workspace_area 
													  = 
													  ISVREF(image_plane_qm,
													  (SI_Long)26L);
												  color_or_metacolor 
													  = 
													  ISVREF(image_plane_qm,
													  (SI_Long)5L) 
													  ?
													   
													  ISVREF(ISVREF(image_plane_qm,
													  (SI_Long)5L),
													  (SI_Long)22L) 
													  :
													   
													  Nil;
												  if (color_or_metacolor);
												  else
												      color_or_metacolor 
													      = 
													      Qblack;
												  if (EQ(color_or_metacolor,
													  Qtransparent) 
													  || 
													  EQ(color_or_metacolor,
													  Qbackground)) 
													      {
												      background_color_or_metacolor 
													      = 
													      ISVREF(image_plane_qm,
													      (SI_Long)5L) 
													      ?
													       
													      ISVREF(ISVREF(image_plane_qm,
													      (SI_Long)5L),
													      (SI_Long)21L) 
													      :
													       
													      Nil;
												      if (background_color_or_metacolor);
												      else
													  background_color_or_metacolor 
														  = 
														  Qwhite;
												      if (EQ(background_color_or_metacolor,
													      Qforeground) 
													      || 
													      EQ(background_color_or_metacolor,
													      Qworkspace_foreground)) 
														  {
													  temp 
														  = 
														  ISVREF(Current_color_map,
														  (SI_Long)4L);
													  if (temp);
													  else
													      temp 
														      = 
														      map_to_color_value_1(Qblack);
													  current_foreground_color_value 
														  = 
														  temp;
												      }
												      else if (EQ(background_color_or_metacolor,
													      Qtransparent) 
													      || 
													      EQ(background_color_or_metacolor,
													      Qbackground)) 
														  {
													  temp 
														  = 
														  ISVREF(Current_color_map,
														  (SI_Long)5L);
													  if (temp);
													  else
													      temp 
														      = 
														      map_to_color_value_1(Qwhite);
													  current_foreground_color_value 
														  = 
														  temp;
												      }
												      else
													  current_foreground_color_value 
														  = 
														  EQ(background_color_or_metacolor,
														  ISVREF(Current_color_map,
														  (SI_Long)6L)) 
														  ?
														   
														  ISVREF(Current_color_map,
														  (SI_Long)7L) 
														  :
														   
														  map_to_color_value_1(background_color_or_metacolor);
												  }
												  else if (EQ(color_or_metacolor,
													  Qforeground) 
													  || 
													  EQ(color_or_metacolor,
													  Qworkspace_foreground)) 
													      {
												      temp 
													      = 
													      ISVREF(Current_color_map,
													      (SI_Long)4L);
												      if (temp);
												      else
													  temp 
														  = 
														  map_to_color_value_1(Qblack);
												      current_foreground_color_value 
													      = 
													      temp;
												  }
												  else
												      current_foreground_color_value 
													      = 
													      EQ(color_or_metacolor,
													      ISVREF(Current_color_map,
													      (SI_Long)6L)) 
													      ?
													       
													      ISVREF(Current_color_map,
													      (SI_Long)7L) 
													      :
													       
													      map_to_color_value_1(color_or_metacolor);
												  PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
													  9);
												    PUSH_SPECIAL_WITH_SYMBOL(Loose_bottom_edge_of_visible_workspace_area,Qloose_bottom_edge_of_visible_workspace_area,loose_bottom_edge_of_visible_workspace_area,
													    8);
												      PUSH_SPECIAL_WITH_SYMBOL(Loose_right_edge_of_visible_workspace_area,Qloose_right_edge_of_visible_workspace_area,loose_right_edge_of_visible_workspace_area,
													      7);
													PUSH_SPECIAL_WITH_SYMBOL(Loose_top_edge_of_visible_workspace_area,Qloose_top_edge_of_visible_workspace_area,loose_top_edge_of_visible_workspace_area,
														6);
													  PUSH_SPECIAL_WITH_SYMBOL(Loose_left_edge_of_visible_workspace_area,Qloose_left_edge_of_visible_workspace_area,loose_left_edge_of_visible_workspace_area,
														  5);
													    PUSH_SPECIAL_WITH_SYMBOL(Current_image_plane,Qcurrent_image_plane,current_image_plane,
														    4);
													      PUSH_SPECIAL_WITH_SYMBOL(Current_pane,Qcurrent_pane,current_pane,
														      3);
														outer_native_image_plane 
															= 
															Current_native_image_plane;
														PUSH_SPECIAL_WITH_SYMBOL(Outer_native_image_plane,Qouter_native_image_plane,outer_native_image_plane,
															2);
														  current_native_image_plane 
															  = 
															  image_plane_qm;
														  PUSH_SPECIAL_WITH_SYMBOL(Current_native_image_plane,Qcurrent_native_image_plane,current_native_image_plane,
															  1);
														    if ( 
															    !EQ(Outer_native_image_plane,
															    Current_native_image_plane))
															nip_begin_drawing(Current_native_image_plane);
														    color_or_metacolor 
															    = 
															    ISVREF(image_plane_qm,
															    (SI_Long)5L) 
															    ?
															     
															    ISVREF(ISVREF(image_plane_qm,
															    (SI_Long)5L),
															    (SI_Long)21L) 
															    :
															     
															    Nil;
														    if (color_or_metacolor);
														    else
															color_or_metacolor 
																= 
																Qwhite;
														    if (EQ(color_or_metacolor,
															    Qtransparent) 
															    || 
															    EQ(color_or_metacolor,
															    Qbackground)) 
																{
															color_value 
																= 
																ISVREF(Current_color_map,
																(SI_Long)5L);
															if (color_value);
															else
															    color_value 
																    = 
																    map_to_color_value_1(Qwhite);
														    }
														    else if (EQ(color_or_metacolor,
															    Qforeground) 
															    || 
															    EQ(color_or_metacolor,
															    Qworkspace_foreground)) 
																{
															temp 
																= 
																ISVREF(image_plane_qm,
																(SI_Long)5L) 
																?
																 
																ISVREF(ISVREF(image_plane_qm,
																(SI_Long)5L),
																(SI_Long)22L) 
																:
																 
																Nil;
															if (temp);
															else
															    temp 
																    = 
																    Qblack;
															color_or_metacolor 
																= 
																temp;
															if (EQ(color_or_metacolor,
																Qtransparent) 
																|| 
																EQ(color_or_metacolor,
																Qbackground)) 
																    {
															    background_color_or_metacolor 
																    = 
																    ISVREF(image_plane_qm,
																    (SI_Long)5L) 
																    ?
																     
																    ISVREF(ISVREF(image_plane_qm,
																    (SI_Long)5L),
																    (SI_Long)21L) 
																    :
																     
																    Nil;
															    if (background_color_or_metacolor);
															    else
																background_color_or_metacolor 
																	= 
																	Qwhite;
															    if (EQ(background_color_or_metacolor,
																    Qforeground) 
																    || 
																    EQ(background_color_or_metacolor,
																    Qworkspace_foreground)) 
																	{
																color_value 
																	= 
																	ISVREF(Current_color_map,
																	(SI_Long)4L);
																if (color_value);
																else
																    color_value 
																	    = 
																	    map_to_color_value_1(Qblack);
															    }
															    else if (EQ(background_color_or_metacolor,
																    Qtransparent) 
																    || 
																    EQ(background_color_or_metacolor,
																    Qbackground)) 
																	{
																color_value 
																	= 
																	ISVREF(Current_color_map,
																	(SI_Long)5L);
																if (color_value);
																else
																    color_value 
																	    = 
																	    map_to_color_value_1(Qwhite);
															    }
															    else
																color_value 
																	= 
																	EQ(background_color_or_metacolor,
																	ISVREF(Current_color_map,
																	(SI_Long)6L)) 
																	?
																	 
																	ISVREF(Current_color_map,
																	(SI_Long)7L) 
																	:
																	 
																	map_to_color_value_1(background_color_or_metacolor);
															}
															else if (EQ(color_or_metacolor,
																Qforeground) 
																|| 
																EQ(color_or_metacolor,
																Qworkspace_foreground)) 
																    {
															    color_value 
																    = 
																    ISVREF(Current_color_map,
																    (SI_Long)4L);
															    if (color_value);
															    else
																color_value 
																	= 
																	map_to_color_value_1(Qblack);
															}
															else
															    color_value 
																    = 
																    EQ(color_or_metacolor,
																    ISVREF(Current_color_map,
																    (SI_Long)6L)) 
																    ?
																     
																    ISVREF(Current_color_map,
																    (SI_Long)7L) 
																    :
																     
																    map_to_color_value_1(color_or_metacolor);
														    }
														    else
															color_value 
																= 
																EQ(color_or_metacolor,
																ISVREF(Current_color_map,
																(SI_Long)6L)) 
																?
																 
																ISVREF(Current_color_map,
																(SI_Long)7L) 
																:
																 
																map_to_color_value_1(color_or_metacolor);
														    old_color_value 
															    = 
															    Current_background_color_value;
														    current_background_color_value 
															    = 
															    Current_background_color_value;
														    PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
															    0);
														      set_current_background_color_value(color_value);
														      draw_block_or_blocks_in_dragging_state(dragging_state,
															      block);
														      set_current_background_color_value(old_color_value);
														    POP_SPECIAL();
														    if ( 
															    !EQ(Outer_native_image_plane,
															    Current_native_image_plane))
															nip_end_drawing(Current_native_image_plane);
														  POP_SPECIAL();
														  if (Current_native_image_plane) 
															      {
														      if ( 
															      !EQ(image_plane_qm,
															      Current_native_image_plane))
															  nip_begin_drawing(Current_native_image_plane);
														  }
														POP_SPECIAL();
													      POP_SPECIAL();
													    POP_SPECIAL();
													  POP_SPECIAL();
													POP_SPECIAL();
												      POP_SPECIAL();
												    POP_SPECIAL();
												  POP_SPECIAL();
											      }
											      POP_UNWIND_PROTECT(0);
											      UNLOCK(For_image_plane);
											      CONTINUE_UNWINDING(0);
											  }
											POP_SPECIAL();
										    }
										    POP_UNWIND_PROTECT(1);
										    UNLOCK(On_window_with_drawing);
										    CONTINUE_UNWINDING(1);
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
							      POP_UNWIND_PROTECT(2);
							      UNLOCK(On_window_without_drawing);
							      CONTINUE_UNWINDING(2);
							    POP_SPECIAL();
							  POP_SPECIAL();
							POP_SPECIAL();
						      POP_SPECIAL();
						    POP_SPECIAL();
						}
					      POP_SPECIAL();
					    POP_SPECIAL();
					  POP_SPECIAL();
					POP_SPECIAL();
				    }
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
    goto next_loop;
  end_loop:
    RESTORE_STACK();
    return VALUES_1(Qnil);
}

/* BLOCKS-TRANSFERABLE-P */
Object blocks_transferable_p(blocks)
    Object blocks;
{
    Object block, ab_loop_list_;

    x_note_fn_call(128,112);
    block = Nil;
    ab_loop_list_ = blocks;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    block = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(block_transferable_p(2,block,blocks)))
	return VALUES_1(Nil);
    goto next_loop;
  end_loop:
    return VALUES_1(T);
    return VALUES_1(Qnil);
}

/* BLOCK-TRANSFERABLE-P */
Object block_transferable_p varargs_1(int, n)
{
    Object block;
    Object other_blocks_to_be_transferred_qm, gensymed_symbol, superblock_qm;
    Object sub_class_bit_vector, scope_conses, ab_node_stack_;
    Object ab_current_node_, ab_skip_list_form_, ab_skip_list_p_;
    Object ab_next_node_, ab_tail_node_, ab_current_alist_, ab_entry_cons_;
    Object ab_connection_, ab_connection_item_, connection, ab_loop_it_;
    Object temp_1, ab_less_than_branch_qm_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_varargs_nonrelocating;
    Declare_special(1);

    x_note_fn_call(128,113);
    INIT_ARGS_nonrelocating();
    block = REQUIRED_ARG_nonrelocating();
    other_blocks_to_be_transferred_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    if (gensymed_symbol) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	superblock_qm = gensymed_symbol;
	if (superblock_qm) {
	    gensymed_symbol = ACCESS_ONCE(ISVREF(superblock_qm,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	    temp =  !TRUEP(gensymed_symbol);
	}
	else
	    temp = TRUEP(Nil);
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
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
    if (temp);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Workspace_name_box_class_description,
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
    if (temp);
    else
	temp = TRUEP(block_of_edit_workspace_p(block));
    if (temp);
    else {
	scope_conses = Scope_conses;
	ab_node_stack_ = Nil;
	ab_current_node_ = Nil;
	gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
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
	connection = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  ab_loop_it_ = Nil;
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
	next_loop:
	next_loop_1:
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
		next_loop_2:
		  ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			  (SI_Long)1L);
		  if ( !TRUEP(ab_less_than_branch_qm_))
		      goto end_loop;
		  ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
		  ab_current_node_ = ab_less_than_branch_qm_;
		  goto next_loop_2;
		end_loop:;
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
	  if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_)
	      goto end_1;
	  goto next_loop_1;
	end_loop_1:
	end_1:
	  if ( !TRUEP(ab_current_node_))
	      goto end_loop_2;
	  connection = ab_connection_;
	  ab_loop_it_ = connection_external_to_blocks_p(block,connection,
		  other_blocks_to_be_transferred_qm);
	  if (ab_loop_it_) {
	      temp = TRUEP(ab_loop_it_);
	      goto end_2;
	  }
	  goto next_loop;
	end_loop_2:
	  temp = TRUEP(Qnil);
	end_2:;
	POP_SPECIAL();
    }
    return VALUES_1( !temp ? T : Nil);
}

/* GROUP-BLOCKS-FOR-MOVE-OR-TRANSFER */
Object group_blocks_for_move_or_transfer(blocks)
    Object blocks;
{
    Object block, ab_loop_list_, scope_conses, ab_node_stack_;
    Object ab_current_node_, gensymed_symbol, ab_skip_list_form_;
    Object ab_skip_list_p_, ab_next_node_, ab_tail_node_, ab_current_alist_;
    Object ab_entry_cons_, ab_connection_, ab_connection_item_, connection;
    Object input_end_object, loose_end_maybe, temp, ab_less_than_branch_qm_;
    Object sub_class_bit_vector, cdr_new_value, external_connections_to_drag;
    Object dragging_confined_p;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(128,114);
    block = Nil;
    ab_loop_list_ = blocks;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    block = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)6L)) : Nil;
    ab_skip_list_form_ = gensymed_symbol;
    ab_skip_list_p_ = Nil;
    ab_next_node_ = Nil;
    ab_tail_node_ = Nil;
    ab_current_alist_ = Nil;
    ab_entry_cons_ = Nil;
    ab_connection_ = Nil;
    ab_connection_item_ = Nil;
    connection = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      input_end_object = Nil;
      loose_end_maybe = Nil;
      gensymed_symbol = CDR(ab_skip_list_form_);
      if (CONSP(gensymed_symbol)) {
	  temp = M_CAR(gensymed_symbol);
	  temp_1 = SIMPLE_VECTOR_P(temp);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  temp = M_CDR(gensymed_symbol);
	  ab_skip_list_p_ = SIMPLE_VECTOR_P(temp) ? T : Nil;
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
    next_loop_1:
    next_loop_2:
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
	    next_loop_3:
	      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
	      if ( !TRUEP(ab_less_than_branch_qm_))
		  goto end_loop_1;
	      ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
	      ab_current_node_ = ab_less_than_branch_qm_;
	      goto next_loop_3;
	    end_loop_1:;
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
      if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_)
	  goto end_1;
      goto next_loop_2;
    end_loop_2:
    end_1:
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_3;
      connection = ab_connection_;
      input_end_object = ISVREF(connection,(SI_Long)3L);
      loose_end_maybe = EQ(input_end_object,block) ? ISVREF(connection,
	      (SI_Long)2L) : input_end_object;
      sub_class_bit_vector = ISVREF(ISVREF(loose_end_maybe,(SI_Long)1L),
	      (SI_Long)19L);
      superior_class_bit_number = IFIX(ISVREF(Loose_end_class_description,
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
	  temp_1 = (SI_Long)0L < gensymed_symbol_1;
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  if ( !TRUEP(memq_function(loose_end_maybe,blocks))) {
	      cdr_new_value = dragging_cons_1(loose_end_maybe,CDR(blocks));
	      M_CDR(blocks) = cdr_new_value;
	  }
      }
      goto next_loop_1;
    end_loop_3:;
    POP_SPECIAL();
    goto next_loop;
  end_loop:;
    external_connections_to_drag = list_external_connections_to_drag(blocks);
    dragging_confined_p = external_connections_to_drag;
    if (dragging_confined_p);
    else
	dragging_confined_p = 
		check_if_dragging_confined_due_to_superblock(blocks);
    return VALUES_3(blocks,external_connections_to_drag,dragging_confined_p);
}

/* CONNECTION-EXTERNAL-TO-BLOCKS-P */
Object connection_external_to_blocks_p(block,connection,blocks)
    Object block, connection, blocks;
{
    Object output_end_object, other_block, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(128,115);
    output_end_object = ISVREF(connection,(SI_Long)2L);
    other_block = EQ(output_end_object,block) ? ISVREF(connection,
	    (SI_Long)3L) : output_end_object;
    if ( !TRUEP(memq_function(other_block,blocks))) {
	sub_class_bit_vector = ISVREF(ISVREF(other_block,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Loose_end_class_description,(SI_Long)18L));
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
	return VALUES_1( !temp ? T : Nil);
    }
    else
	return VALUES_1(Nil);
}

/* LIST-EXTERNAL-CONNECTIONS-TO-DRAG */
Object list_external_connections_to_drag(blocks)
    Object blocks;
{
    Object block, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object scope_conses, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, ab_loopvar__3, ab_loopvar__4, temp;
    Object ab_less_than_branch_qm_;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(128,116);
    block = Nil;
    ab_loop_list_ = blocks;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    block = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)6L)) : Nil;
    ab_skip_list_form_ = gensymed_symbol;
    ab_skip_list_p_ = Nil;
    ab_next_node_ = Nil;
    ab_tail_node_ = Nil;
    ab_current_alist_ = Nil;
    ab_entry_cons_ = Nil;
    ab_connection_ = Nil;
    ab_connection_item_ = Nil;
    connection = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar__2 = Nil;
      ab_loopvar__3 = Nil;
      ab_loopvar__4 = Nil;
      gensymed_symbol = CDR(ab_skip_list_form_);
      if (CONSP(gensymed_symbol)) {
	  temp = M_CAR(gensymed_symbol);
	  temp_1 = SIMPLE_VECTOR_P(temp);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  temp = M_CDR(gensymed_symbol);
	  ab_skip_list_p_ = SIMPLE_VECTOR_P(temp) ? T : Nil;
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
    next_loop_1:
    next_loop_2:
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
	    next_loop_3:
	      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
	      if ( !TRUEP(ab_less_than_branch_qm_))
		  goto end_loop_1;
	      ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
	      ab_current_node_ = ab_less_than_branch_qm_;
	      goto next_loop_3;
	    end_loop_1:;
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
      if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_)
	  goto end_1;
      goto next_loop_2;
    end_loop_2:
    end_1:
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_3;
      connection = ab_connection_;
      if (connection_external_to_blocks_p(block,connection,blocks)) {
	  ab_loopvar__4 = dragging_cons_1(connection,Nil);
	  if (ab_loopvar__3)
	      M_CDR(ab_loopvar__3) = ab_loopvar__4;
	  else
	      ab_loopvar__2 = ab_loopvar__4;
	  ab_loopvar__3 = ab_loopvar__4;
      }
      goto next_loop_1;
    end_loop_3:
      goto end_2;
      ab_loopvar__2 = Qnil;
    end_2:;
    POP_SPECIAL();
    if (ab_loopvar__2) {
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = last(ab_loopvar__2,_);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

/* CHECK-IF-DRAGGING-CONFINED-DUE-TO-SUPERBLOCK */
Object check_if_dragging_confined_due_to_superblock(blocks)
    Object blocks;
{
    Object block, ab_loop_list_, previous_superblock, superblock_qm;
    Object ab_loop_it_, ab_loop_iter_flag_, gensymed_symbol, temp;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;

    x_note_fn_call(128,117);
    block = Nil;
    ab_loop_list_ = blocks;
    previous_superblock = Nil;
    superblock_qm = Nil;
    ab_loop_it_ = Nil;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    block = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	previous_superblock = superblock_qm;
    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    superblock_qm = gensymed_symbol;
    temp = previous_superblock ? ( !EQ(previous_superblock,superblock_qm) ?
	     T : Nil) : Nil;
    if (temp);
    else if (superblock_qm) {
	sub_class_bit_vector = ISVREF(ISVREF(superblock_qm,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
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
	    temp_1 = (SI_Long)0L < gensymed_symbol_1;
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    gensymed_symbol = ACCESS_ONCE(ISVREF(superblock_qm,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	    temp = gensymed_symbol;
	    if (temp);
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Workspace_name_box_class_description,
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
		    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		    gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		    temp = (SI_Long)0L < gensymed_symbol_1 ? T : Nil;
		}
		else
		    temp = Nil;
	    }
	}
	else
	    temp = T;
    }
    else
	temp = Nil;
    ab_loop_it_ = temp;
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* LOOSE-END-DRAGGING-OUTLINE-P */
Object loose_end_dragging_outline_p(outline)
    Object outline;
{
    Object frame, symbol, gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(128,118);
    if ( !TRUEP(CDR(outline))) {
	frame = FIRST(outline);
	symbol = Qloose_end;
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(symbol,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,
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
		return VALUES_1((SI_Long)0L < gensymed_symbol_1 ? T : Nil);
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

/* MAKE-OUTLINE-FOR-BLOCKS-TO-DRAG */
Object make_outline_for_blocks_to_drag(blocks,transfer_case_qm)
    Object blocks, transfer_case_qm;
{
    Object external_connections_to_drag, confine_qm, loose_end, connection;
    Object gensymed_symbol, ab_loop_list_;
    Object result;

    x_note_fn_call(128,119);
    result = group_blocks_for_move_or_transfer(blocks);
    MVS_3(result,blocks,external_connections_to_drag,confine_qm);
    if (loose_end_dragging_outline_p(blocks)) {
	loose_end = FIRST(blocks);
	connection = FIRST(external_connections_to_drag);
	if (connection_is_straight_qm(connection)) {
	    gensymed_symbol = ACCESS_ONCE(ISVREF(loose_end,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	    update_connection_images(T,gensymed_symbol,connection);
	    toggle_side_for_loose_end(loose_end,connection);
	    gensymed_symbol = ACCESS_ONCE(ISVREF(loose_end,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	    update_connection_images(Nil,gensymed_symbol,connection);
	}
    }
    if (confine_qm ||  !TRUEP(transfer_case_qm)) {
	connection = Nil;
	ab_loop_list_ = external_connections_to_drag;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	connection = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	put_kink_into_connection_if_straight(connection,blocks);
	goto next_loop;
      end_loop:;
    }
    return VALUES_3(blocks,external_connections_to_drag,confine_qm);
}

static Object Kdraw_as_late_as_possible;  /* :draw-as-late-as-possible */

/* START-RENDERING-DRAGGING-STATE-FOR-MOVE-OR-TRANSFER */
Object start_rendering_dragging_state_for_move_or_transfer(dragging_state)
    Object dragging_state;
{
    Object blocks, external_connections_to_drag, workspace_qm;
    Object current_drawing_priority, region_invalidation_is_preferred, block;
    Object ab_loop_list_, stack, sub, tree_ordering_pop_store, cons_1;
    Object next_cons, temp, svref_arg_2, temp_1, gensymed_symbol;
    Object ab_queue_form_, ab_next_queue_element_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, infs, temp_2, temp_3;
    SI_Long svref_new_value;
    char value;
    Declare_special(2);
    Object result;

    x_note_fn_call(128,120);
    blocks = ISVREF(dragging_state,(SI_Long)3L);
    external_connections_to_drag = ISVREF(dragging_state,(SI_Long)6L);
    workspace_qm = get_workspace_if_any(FIRST(blocks));
    current_drawing_priority = Kdraw_as_late_as_possible;
    PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_priority,Qcurrent_drawing_priority,current_drawing_priority,
	    1);
      if (workspace_qm) {
	  region_invalidation_is_preferred = T;
	  PUSH_SPECIAL_WITH_SYMBOL(Region_invalidation_is_preferred,Qregion_invalidation_is_preferred,region_invalidation_is_preferred,
		  0);
	    update_images_of_blocks_and_connections_being_moved(T,
		    workspace_qm,blocks,external_connections_to_drag);
	  POP_SPECIAL();
      }
      block = Nil;
      ab_loop_list_ = blocks;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      block = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      if ( !((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
	      (SI_Long)2048L))) {
	  stack = tree_ordering_cons_1(block,Nil);
	  sub = Nil;
	next_loop_1:
	  if ( !TRUEP(stack))
	      goto end_loop_1;
	  tree_ordering_pop_store = Nil;
	  cons_1 = stack;
	  if (cons_1) {
	      tree_ordering_pop_store = M_CAR(cons_1);
	      next_cons = M_CDR(cons_1);
	      inline_note_reclaim_cons(cons_1,Qtree_ordering);
	      if (ISVREF(Available_tree_ordering_conses_tail_vector,
		      IFIX(Current_thread_index))) {
		  temp = ISVREF(Available_tree_ordering_conses_tail_vector,
			  IFIX(Current_thread_index));
		  M_CDR(temp) = cons_1;
		  temp = Available_tree_ordering_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp,svref_arg_2) = cons_1;
	      }
	      else {
		  temp = Available_tree_ordering_conses_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp,svref_arg_2) = cons_1;
		  temp = Available_tree_ordering_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp,svref_arg_2) = cons_1;
	      }
	      M_CDR(cons_1) = Nil;
	  }
	  else
	      next_cons = Nil;
	  stack = next_cons;
	  temp_1 = tree_ordering_pop_store;
	  sub = Nil;
	  if (EQ(temp_1,Tree_traversal_marker)) {
	      tree_ordering_pop_store = Nil;
	      cons_1 = stack;
	      if (cons_1) {
		  tree_ordering_pop_store = M_CAR(cons_1);
		  next_cons = M_CDR(cons_1);
		  inline_note_reclaim_cons(cons_1,Qtree_ordering);
		  if (ISVREF(Available_tree_ordering_conses_tail_vector,
			  IFIX(Current_thread_index))) {
		      temp = 
			      ISVREF(Available_tree_ordering_conses_tail_vector,
			      IFIX(Current_thread_index));
		      M_CDR(temp) = cons_1;
		      temp = Available_tree_ordering_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp,svref_arg_2) = cons_1;
		  }
		  else {
		      temp = Available_tree_ordering_conses_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp,svref_arg_2) = cons_1;
		      temp = Available_tree_ordering_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp,svref_arg_2) = cons_1;
		  }
		  M_CDR(cons_1) = Nil;
	      }
	      else
		  next_cons = Nil;
	      stack = next_cons;
	      sub = tree_ordering_pop_store;
	  }
	  else if (IDENTITY(temp_1)) {
	      gensymed_symbol = ACCESS_ONCE(ISVREF(temp_1,(SI_Long)14L));
	      gensymed_symbol = gensymed_symbol ? 
		      ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	      ab_queue_form_ = gensymed_symbol;
	      ab_next_queue_element_ = Nil;
	      gensymed_symbol = Nil;
	      ab_loopvar_ = Nil;
	      ab_loopvar__1 = Nil;
	      ab_loopvar__2 = Nil;
	      if (ab_queue_form_)
		  ab_next_queue_element_ = 
			  constant_queue_next(ISVREF(ab_queue_form_,
			  (SI_Long)2L),ab_queue_form_);
	    next_loop_2:
	      if ( !TRUEP(ab_next_queue_element_))
		  goto end_loop_2;
	      gensymed_symbol = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	      ab_next_queue_element_ = 
		      constant_queue_next(ab_next_queue_element_,
		      ab_queue_form_);
	      ab_loopvar__2 = tree_ordering_cons_1(gensymed_symbol,Nil);
	      if (ab_loopvar__1)
		  M_CDR(ab_loopvar__1) = ab_loopvar__2;
	      else
		  ab_loopvar_ = ab_loopvar__2;
	      ab_loopvar__1 = ab_loopvar__2;
	      goto next_loop_2;
	    end_loop_2:
	      infs = ab_loopvar_;
	      goto end_1;
	      infs = Qnil;
	    end_1:;
	      if ( !TRUEP(infs))
		  sub = temp_1;
	      else {
		  temp_2 = T ? infs : 
			  copy_list_using_tree_ordering_conses_1(infs);
		  temp_3 = tree_ordering_cons_1(Tree_traversal_marker,Nil);
		  stack = nconc2(temp_2,nconc2(temp_3,
			  nconc2(tree_ordering_cons_1(temp_1,Nil),stack)));
	      }
	  }
	  if (sub) {
	      svref_new_value = IFIX(ISVREF(sub,(SI_Long)5L)) | (SI_Long)2048L;
	      ISVREF(sub,(SI_Long)5L) = FIX(svref_new_value);
	      value = (SI_Long)0L != (IFIX(ISVREF(sub,(SI_Long)5L)) & 
		      (SI_Long)1024L);
	      if (value) {
		  svref_new_value = IFIX(ISVREF(sub,(SI_Long)5L)) | 
			  (SI_Long)512L;
		  ISVREF(sub,(SI_Long)5L) = FIX(svref_new_value);
	      }
	      else {
		  svref_new_value = IFIX(ISVREF(sub,(SI_Long)5L)) &  
			  ~(SI_Long)512L;
		  ISVREF(sub,(SI_Long)5L) = FIX(svref_new_value);
	      }
	      svref_new_value = IFIX(ISVREF(sub,(SI_Long)5L)) | (SI_Long)1024L;
	      ISVREF(sub,(SI_Long)5L) = FIX(svref_new_value);
	  }
	  goto next_loop_1;
	end_loop_1:
	  if (stack)
	      reclaim_tree_ordering_list_1(stack);
      }
      goto next_loop;
    end_loop:;
      if (workspace_qm)
	  result = force_workspace_drawing(workspace_qm);
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* STOP-RENDERING-DRAGGING-STATE-FOR-MOVE-OR-TRANSFER */
Object stop_rendering_dragging_state_for_move_or_transfer(dragging_state)
    Object dragging_state;
{
    Object blocks, external_connections_to_drag, workspace_qm, block;
    Object ab_loop_list_, ds, ab_loop_list__1, ab_loop_it_, stack, sub;
    Object tree_ordering_pop_store, cons_1, next_cons, temp_1, svref_arg_2;
    Object temp_2, gensymed_symbol, ab_queue_form_, ab_next_queue_element_;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, infs, temp_3, temp_4;
    Object current_drawing_priority, region_invalidation_is_preferred;
    SI_Long svref_new_value;
    char temp, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(128,121);
    blocks = ISVREF(dragging_state,(SI_Long)3L);
    external_connections_to_drag = ISVREF(dragging_state,(SI_Long)6L);
    workspace_qm = get_workspace_if_any(FIRST(blocks));
    drag_outline_if_appropriate(dragging_state,T);
    if (EQ(ISVREF(dragging_state,(SI_Long)21L),Qmove_dragging_style) || 
	    EQ(ISVREF(dragging_state,(SI_Long)21L),Qtransfer_dragging_style)) {
	block = Nil;
	ab_loop_list_ = blocks;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	block = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ds = Nil;
	ab_loop_list__1 = Current_dragging_states;
	ab_loop_it_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	ds = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if ( !EQ(ds,dragging_state)) {
	    ab_loop_it_ = member_eql(block,ISVREF(ds,(SI_Long)3L));
	    if (ab_loop_it_) {
		temp = TRUEP(ab_loop_it_);
		goto end_1;
	    }
	}
	goto next_loop_1;
      end_loop_1:
	temp = TRUEP(Qnil);
      end_1:;
	if ( !temp) {
	    stack = tree_ordering_cons_1(block,Nil);
	    sub = Nil;
	  next_loop_2:
	    if ( !TRUEP(stack))
		goto end_loop_2;
	    tree_ordering_pop_store = Nil;
	    cons_1 = stack;
	    if (cons_1) {
		tree_ordering_pop_store = M_CAR(cons_1);
		next_cons = M_CDR(cons_1);
		inline_note_reclaim_cons(cons_1,Qtree_ordering);
		if (ISVREF(Available_tree_ordering_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = 
			    ISVREF(Available_tree_ordering_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = cons_1;
		    temp_1 = Available_tree_ordering_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = cons_1;
		}
		else {
		    temp_1 = Available_tree_ordering_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = cons_1;
		    temp_1 = Available_tree_ordering_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = cons_1;
		}
		M_CDR(cons_1) = Nil;
	    }
	    else
		next_cons = Nil;
	    stack = next_cons;
	    temp_2 = tree_ordering_pop_store;
	    sub = Nil;
	    if (EQ(temp_2,Tree_traversal_marker)) {
		tree_ordering_pop_store = Nil;
		cons_1 = stack;
		if (cons_1) {
		    tree_ordering_pop_store = M_CAR(cons_1);
		    next_cons = M_CDR(cons_1);
		    inline_note_reclaim_cons(cons_1,Qtree_ordering);
		    if (ISVREF(Available_tree_ordering_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_1 = 
				ISVREF(Available_tree_ordering_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_1) = cons_1;
			temp_1 = Available_tree_ordering_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_1,svref_arg_2) = cons_1;
		    }
		    else {
			temp_1 = Available_tree_ordering_conses_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_1,svref_arg_2) = cons_1;
			temp_1 = Available_tree_ordering_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_1,svref_arg_2) = cons_1;
		    }
		    M_CDR(cons_1) = Nil;
		}
		else
		    next_cons = Nil;
		stack = next_cons;
		sub = tree_ordering_pop_store;
	    }
	    else if (IDENTITY(temp_2)) {
		gensymed_symbol = ACCESS_ONCE(ISVREF(temp_2,(SI_Long)14L));
		gensymed_symbol = gensymed_symbol ? 
			ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
		ab_queue_form_ = gensymed_symbol;
		ab_next_queue_element_ = Nil;
		gensymed_symbol = Nil;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ab_loopvar__2 = Nil;
		if (ab_queue_form_)
		    ab_next_queue_element_ = 
			    constant_queue_next(ISVREF(ab_queue_form_,
			    (SI_Long)2L),ab_queue_form_);
	      next_loop_3:
		if ( !TRUEP(ab_next_queue_element_))
		    goto end_loop_3;
		gensymed_symbol = ISVREF(ab_next_queue_element_,(SI_Long)4L);
		ab_next_queue_element_ = 
			constant_queue_next(ab_next_queue_element_,
			ab_queue_form_);
		ab_loopvar__2 = tree_ordering_cons_1(gensymed_symbol,Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
		goto next_loop_3;
	      end_loop_3:
		infs = ab_loopvar_;
		goto end_2;
		infs = Qnil;
	      end_2:;
		if ( !TRUEP(infs))
		    sub = temp_2;
		else {
		    temp_3 = T ? infs : 
			    copy_list_using_tree_ordering_conses_1(infs);
		    temp_4 = tree_ordering_cons_1(Tree_traversal_marker,Nil);
		    stack = nconc2(temp_3,nconc2(temp_4,
			    nconc2(tree_ordering_cons_1(temp_2,Nil),stack)));
		}
	    }
	    if (sub) {
		svref_new_value = IFIX(ISVREF(sub,(SI_Long)5L)) &  
			~(SI_Long)2048L;
		ISVREF(sub,(SI_Long)5L) = FIX(svref_new_value);
		value = (SI_Long)0L != (IFIX(ISVREF(sub,(SI_Long)5L)) & 
			(SI_Long)512L);
		if (value) {
		    svref_new_value = IFIX(ISVREF(sub,(SI_Long)5L)) | 
			    (SI_Long)1024L;
		    ISVREF(sub,(SI_Long)5L) = FIX(svref_new_value);
		}
		else {
		    svref_new_value = IFIX(ISVREF(sub,(SI_Long)5L)) &  
			    ~(SI_Long)1024L;
		    ISVREF(sub,(SI_Long)5L) = FIX(svref_new_value);
		}
	    }
	    goto next_loop_2;
	  end_loop_2:
	    if (stack)
		reclaim_tree_ordering_list_1(stack);
	}
	goto next_loop;
      end_loop:;
	if (workspace_qm) {
	    current_drawing_priority = Kdraw_as_late_as_possible;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_priority,Qcurrent_drawing_priority,current_drawing_priority,
		    1);
	      region_invalidation_is_preferred = T;
	      PUSH_SPECIAL_WITH_SYMBOL(Region_invalidation_is_preferred,Qregion_invalidation_is_preferred,region_invalidation_is_preferred,
		      0);
		result = update_images_of_blocks_and_connections_being_moved(Nil,
			workspace_qm,blocks,external_connections_to_drag);
	      POP_SPECIAL();
	    POP_SPECIAL();
	    return result;
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* SHIFT-BLOCKS-WITH-THEIR-EXTERNAL-CONNECTIONS */
Object shift_blocks_with_their_external_connections varargs_1(int, n)
{
    Object blocks, external_connections, just_erase_if_currently_drawn_qm;
    Object workspace, delta_x_in_workspace, delta_y_in_workspace;
    Object just_draw_qm, final_update_qm, all_blocks_are_in_xor_qm;
    Object region_invalidation_is_preferred;
    Object do_not_update_selection_highlights, block, ab_loop_list_;
    Object connection, ab_loop_list__1, extreme_left_edge, extreme_top_edge;
    Object extreme_right_edge, extreme_bottom_edge, current_draw_document_p;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(128,122);
    INIT_ARGS_nonrelocating();
    blocks = REQUIRED_ARG_nonrelocating();
    external_connections = REQUIRED_ARG_nonrelocating();
    just_erase_if_currently_drawn_qm = REQUIRED_ARG_nonrelocating();
    workspace = REQUIRED_ARG_nonrelocating();
    delta_x_in_workspace = REQUIRED_ARG_nonrelocating();
    delta_y_in_workspace = REQUIRED_ARG_nonrelocating();
    just_draw_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    final_update_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    all_blocks_are_in_xor_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(just_draw_qm)) {
	region_invalidation_is_preferred = all_blocks_are_in_xor_qm ? 
		Region_invalidation_is_preferred : T;
	PUSH_SPECIAL_WITH_SYMBOL(Region_invalidation_is_preferred,Qregion_invalidation_is_preferred,region_invalidation_is_preferred,
		0);
	  update_images_of_blocks_and_connections_being_moved(Qdelete,
		  workspace,blocks,external_connections);
	POP_SPECIAL();
    }
    if ( !TRUEP(just_erase_if_currently_drawn_qm)) {
	do_not_update_selection_highlights = T;
	PUSH_SPECIAL_WITH_SYMBOL(Do_not_update_selection_highlights,Qdo_not_update_selection_highlights,do_not_update_selection_highlights,
		0);
	  block = Nil;
	  ab_loop_list_ = blocks;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  block = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  shift_block(block,delta_x_in_workspace,delta_y_in_workspace);
	  connection = Nil;
	  ab_loop_list__1 = external_connections;
	next_loop_1:
	  if ( !TRUEP(ab_loop_list__1))
	      goto end_loop_1;
	  connection = M_CAR(ab_loop_list__1);
	  ab_loop_list__1 = M_CDR(ab_loop_list__1);
	  change_connection_deltas_for_object_being_dragged(connection,
		  block,delta_x_in_workspace,delta_y_in_workspace);
	  goto next_loop_1;
	end_loop_1:;
	  goto next_loop;
	end_loop:;
	POP_SPECIAL();
	result = determine_extreme_edges_of_blocks_and_connections(blocks,
		external_connections,Nil);
	MVS_4(result,extreme_left_edge,extreme_top_edge,extreme_right_edge,
		extreme_bottom_edge);
	current_draw_document_p = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_draw_document_p,Qcurrent_draw_document_p,current_draw_document_p,
		0);
	  enlarge_workspace_if_necessary(5,workspace,extreme_left_edge,
		  extreme_top_edge,extreme_right_edge,extreme_bottom_edge);
	POP_SPECIAL();
	if ( !TRUEP(show_selection_handles_p(0)))
	    move_all_selection_highlights(workspace,blocks,
		    external_connections,delta_x_in_workspace,
		    delta_y_in_workspace);
	region_invalidation_is_preferred = final_update_qm ? T : 
		Region_invalidation_is_preferred;
	PUSH_SPECIAL_WITH_SYMBOL(Region_invalidation_is_preferred,Qregion_invalidation_is_preferred,region_invalidation_is_preferred,
		0);
	  result = update_images_of_blocks_and_connections_being_moved(Nil,
		  workspace,blocks,external_connections);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* ADD-XOR-OVERLAY-TO-CURRENT-IMAGE-PLANE */
Object add_xor_overlay_to_current_image_plane()
{
    Object dragging_state, ab_loop_list_;

    x_note_fn_call(128,123);
    dragging_state = Nil;
    ab_loop_list_ = Current_dragging_states;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    dragging_state = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(ISVREF(dragging_state,(SI_Long)21L),Qmove_dragging_style) && 
	    EQ(ISVREF(dragging_state,(SI_Long)5L),Current_image_plane))
	draw_blocks_and_connections_being_moved(ISVREF(dragging_state,
		(SI_Long)3L),ISVREF(dragging_state,(SI_Long)6L));
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* ADD-CURSORS-TO-CURRENT-WINDOW */
Object add_cursors_to_current_window(left,top,right,bottom,pane_cursors_p,
	    image_plane_cursors_p,xor_overlay_p)
    Object left, top, right, bottom, pane_cursors_p, image_plane_cursors_p;
    Object xor_overlay_p;
{
    Object pane_cursor, ab_loop_list_;

    x_note_fn_call(128,124);
    if (pane_cursors_p) {
	pane_cursor = Nil;
	ab_loop_list_ = ISVREF(Current_pane,(SI_Long)6L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	pane_cursor = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	add_from_pane_cursor_to_current_window(Nil,pane_cursor,
		Current_pane,left,top,right,bottom);
	goto next_loop;
      end_loop:;
    }
    if (image_plane_cursors_p)
	add_image_plane_cursors_to_current_window();
    if (xor_overlay_p)
	return add_xor_overlay_to_current_image_plane();
    else
	return VALUES_1(Nil);
}

/* DETERMINE-EXTREME-EDGES-FOR-ITEM-BEING-MOVED */
Object determine_extreme_edges_for_item_being_moved(block)
    Object block;
{
    Object gensymed_symbol, extreme_left_edge_so_far, extreme_top_edge_so_far;
    Object extreme_right_edge_so_far, extreme_bottom_edge_so_far;
    Declare_special(4);
    Object result;

    x_note_fn_call(128,125);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    extreme_left_edge_so_far = gensymed_symbol;
    PUSH_SPECIAL_WITH_SYMBOL(Extreme_left_edge_so_far,Qextreme_left_edge_so_far,extreme_left_edge_so_far,
	    3);
      gensymed_symbol = ISVREF(block,(SI_Long)14L);
      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	      (SI_Long)1L) : FIX((SI_Long)0L);
      extreme_top_edge_so_far = gensymed_symbol;
      PUSH_SPECIAL_WITH_SYMBOL(Extreme_top_edge_so_far,Qextreme_top_edge_so_far,extreme_top_edge_so_far,
	      2);
	extreme_right_edge_so_far = Extreme_left_edge_so_far;
	PUSH_SPECIAL_WITH_SYMBOL(Extreme_right_edge_so_far,Qextreme_right_edge_so_far,extreme_right_edge_so_far,
		1);
	  extreme_bottom_edge_so_far = Extreme_top_edge_so_far;
	  PUSH_SPECIAL_WITH_SYMBOL(Extreme_bottom_edge_so_far,Qextreme_bottom_edge_so_far,extreme_bottom_edge_so_far,
		  0);
	    update_extreme_edges_from_block_bounds(block);
	    update_extreme_edges_for_item_being_moved(block);
	    result = VALUES_4(Extreme_left_edge_so_far,
		    Extreme_top_edge_so_far,Extreme_right_edge_so_far,
		    Extreme_bottom_edge_so_far);
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* UPDATE-EXTREME-EDGES-FOR-ITEM-BEING-MOVED */
Object update_extreme_edges_for_item_being_moved(block)
    Object block;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, other_end, temp;
    Object ab_less_than_branch_qm_, sub_class_bit_vector, ab_queue_form_;
    Object ab_next_queue_element_, subblock;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(128,126);
    update_extreme_edges_from_block_bounds(block);
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)6L)) : Nil;
    ab_skip_list_form_ = gensymed_symbol;
    ab_skip_list_p_ = Nil;
    ab_next_node_ = Nil;
    ab_tail_node_ = Nil;
    ab_current_alist_ = Nil;
    ab_entry_cons_ = Nil;
    ab_connection_ = Nil;
    ab_connection_item_ = Nil;
    connection = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      other_end = Nil;
      gensymed_symbol = CDR(ab_skip_list_form_);
      if (CONSP(gensymed_symbol)) {
	  temp = M_CAR(gensymed_symbol);
	  temp_1 = SIMPLE_VECTOR_P(temp);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  temp = M_CDR(gensymed_symbol);
	  ab_skip_list_p_ = SIMPLE_VECTOR_P(temp) ? T : Nil;
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
    next_loop:
    next_loop_1:
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
	    next_loop_2:
	      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
	      if ( !TRUEP(ab_less_than_branch_qm_))
		  goto end_loop;
	      ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
	      ab_current_node_ = ab_less_than_branch_qm_;
	      goto next_loop_2;
	    end_loop:;
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
      if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_)
	  goto end_1;
      goto next_loop_1;
    end_loop_1:
    end_1:
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_2;
      connection = ab_connection_;
      other_end = get_block_at_other_end_of_connection(connection,block);
      sub_class_bit_vector = ISVREF(ISVREF(other_end,(SI_Long)1L),
	      (SI_Long)19L);
      superior_class_bit_number = IFIX(ISVREF(Loose_end_class_description,
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
	  temp_1 = (SI_Long)0L < gensymed_symbol_1;
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1)
	  update_extreme_edges_from_connection(connection);
      goto next_loop;
    end_loop_2:;
    POP_SPECIAL();
    if ( !((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
		(SI_Long)32768L))) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	ab_queue_form_ = gensymed_symbol;
	ab_next_queue_element_ = Nil;
	subblock = Nil;
	if (ab_queue_form_)
	    ab_next_queue_element_ = 
		    constant_queue_next(ISVREF(ab_queue_form_,(SI_Long)2L),
		    ab_queue_form_);
      next_loop_3:
	if ( !TRUEP(ab_next_queue_element_))
	    goto end_loop_3;
	subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	ab_next_queue_element_ = 
		constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	update_extreme_edges_for_item_being_moved(subblock);
	goto next_loop_3;
      end_loop_3:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* MAKE-OUTLINE-FOR-IMAGE-PLANE-TO-DRAG */
Object make_outline_for_image_plane_to_drag(image_plane,
	    x_offset_from_dragger,y_offset_from_dragger)
    Object image_plane, x_offset_from_dragger, y_offset_from_dragger;
{
    Object temp, x_center, y_center, gensymed_symbol, gensymed_symbol_1;
    Object car_new_value;

    x_note_fn_call(128,127);
    temp = dragging_list_3(Qimage_plane,image_plane,ISVREF(image_plane,
	    (SI_Long)5L));
    x_center = FIXNUM_ADD(ISVREF(image_plane,(SI_Long)15L),
	    x_offset_from_dragger);
    y_center = FIXNUM_ADD(ISVREF(image_plane,(SI_Long)16L),
	    y_offset_from_dragger);
    gensymed_symbol = make_dragging_list_1(FIX((SI_Long)11L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = x_center;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = y_center;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = add_image_plane_border_as_pane_cursor(image_plane,
	    FIX((SI_Long)0L),FIX((SI_Long)0L));
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = x_center;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = y_center;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = add_plus_sign_as_pane_cursor(ISVREF(image_plane,
	    (SI_Long)2L),x_center,y_center,FIX((SI_Long)16L),
	    FIX((SI_Long)16L),FIX((SI_Long)4L),Qblack);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = x_center;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = y_center;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = add_plus_sign_as_pane_cursor(ISVREF(image_plane,
	    (SI_Long)2L),x_center,y_center,FIX((SI_Long)16L),
	    FIX((SI_Long)16L),FIX((SI_Long)4L),Qblack);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Nil;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Nil;
    temp = nconc2(temp,gensymed_symbol);
    return VALUES_3(temp,Nil,Nil);
}

/* ERASE-OUTLINE-OF-IMAGE-PLANE-BEING-DRAGGED */
Object erase_outline_of_image_plane_being_dragged varargs_1(int, n)
{
    Object dragging_state;
    Object return_copy_of_pane_cursors_qm, temp, objects_being_dragged, pane;
    Object pane_cursor, temp_1, ab_loop_list_, cddr_arg;
    Declare_varargs_nonrelocating;

    x_note_fn_call(128,128);
    INIT_ARGS_nonrelocating();
    dragging_state = REQUIRED_ARG_nonrelocating();
    return_copy_of_pane_cursors_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (return_copy_of_pane_cursors_qm) {
	temp = ISVREF(dragging_state,(SI_Long)3L);
	temp = CDDDR(temp);
	temp = 
		copy_list_using_dragging_conses_1(copy_tree_using_graphics_conses_1(CDDR(temp)));
    }
    else
	temp = Nil;
    objects_being_dragged = ISVREF(dragging_state,(SI_Long)3L);
    pane = ISVREF(CADR(objects_being_dragged),(SI_Long)2L);
    pane_cursor = Nil;
    temp_1 = CDDDR(objects_being_dragged);
    ab_loop_list_ = CDDR(temp_1);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    pane_cursor = M_CAR(ab_loop_list_);
    delete_pane_cursor(pane_cursor,pane);
    ab_loop_list_ = CDDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:
    temp_1 = CDDDR(objects_being_dragged);
    reclaim_dragging_list_1(CDDR(temp_1));
    cddr_arg = CDDDR(objects_being_dragged);
    M_CDDR(cddr_arg) = Nil;
    return VALUES_1(temp);
}

/* RESTORE-OUTLINE-OF-IMAGE-PLANE-BEING-DRAGGED */
Object restore_outline_of_image_plane_being_dragged(dragging_state,
	    saved_copy_of_pane_cursors)
    Object dragging_state, saved_copy_of_pane_cursors;
{
    Object temp, cddr_arg, objects_being_dragged, pane, pane_cursor;
    Object ab_loop_list_;

    x_note_fn_call(128,129);
    temp = ISVREF(dragging_state,(SI_Long)3L);
    cddr_arg = CDDDR(temp);
    M_CDDR(cddr_arg) = saved_copy_of_pane_cursors;
    objects_being_dragged = ISVREF(dragging_state,(SI_Long)3L);
    pane = ISVREF(CADR(objects_being_dragged),(SI_Long)2L);
    pane_cursor = Nil;
    temp = CDDDR(objects_being_dragged);
    ab_loop_list_ = CDDR(temp);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    pane_cursor = M_CAR(ab_loop_list_);
    add_pane_cursor(pane_cursor,pane);
    ab_loop_list_ = CDDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* MOVE-OUTLINE-OF-IMAGE-PLANE-BEING-DRAGGED */
Object move_outline_of_image_plane_being_dragged(dragging_state,dragger_x,
	    dragger_y)
    Object dragging_state, dragger_x, dragger_y;
{
    Object objects_being_dragged, basis_image_plane, pane, temp, l;
    Object pane_cursor, positions_and_rest, x_position_qm, y_position_qm;
    Object first_time_qm, ab_loop_iter_flag_, u_1, step_qm, min_qm, max_qm, ur;
    Object position_1;
    SI_Long gensymed_symbol, temp_1, gensymed_symbol_1, delta_x_in_window;
    SI_Long delta_y_in_window;

    x_note_fn_call(128,130);
    objects_being_dragged = ISVREF(dragging_state,(SI_Long)3L);
    basis_image_plane = CADR(objects_being_dragged);
    pane = ISVREF(basis_image_plane,(SI_Long)2L);
    temp = CDDDR(objects_being_dragged);
    l = CDDR(temp);
    pane_cursor = Nil;
    positions_and_rest = Nil;
    x_position_qm = Nil;
    y_position_qm = Nil;
    first_time_qm = T;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(l))
	goto end_loop;
    pane_cursor = CAR(l);
    positions_and_rest = CDR(l);
    x_position_qm = CAR(positions_and_rest);
    temp = CDR(positions_and_rest);
    y_position_qm = CAR(temp);
    if ( !TRUEP(ab_loop_iter_flag_))
	first_time_qm = Nil;
    if (x_position_qm) {
	u_1 = dragger_x;
	step_qm = ISVREF(dragging_state,(SI_Long)22L);
	min_qm = ISVREF(dragging_state,(SI_Long)13L);
	max_qm = ISVREF(dragging_state,(SI_Long)15L);
	ur = u_1;
	if (step_qm)
	    ur = FIXNUM_TIMES(step_qm,l_round(u_1,step_qm));
	if (min_qm)
	    ur = FIXNUM_MAX(ur,min_qm);
	if (max_qm)
	    ur = FIXNUM_MIN(ur,max_qm);
	position_1 = ur;
	gensymed_symbol = IFIX(position_1);
	temp_1 = IFIX(x_position_qm);
	SVREF(dragging_state,FIX((SI_Long)10L)) = dragger_x;
	M_CAR(positions_and_rest) = position_1;
	gensymed_symbol_1 = temp_1;
	delta_x_in_window = gensymed_symbol - gensymed_symbol_1;
	u_1 = dragger_y;
	step_qm = ISVREF(dragging_state,(SI_Long)23L);
	min_qm = ISVREF(dragging_state,(SI_Long)14L);
	max_qm = ISVREF(dragging_state,(SI_Long)16L);
	ur = u_1;
	if (step_qm)
	    ur = FIXNUM_TIMES(step_qm,l_round(u_1,step_qm));
	if (min_qm)
	    ur = FIXNUM_MAX(ur,min_qm);
	if (max_qm)
	    ur = FIXNUM_MIN(ur,max_qm);
	position_1 = ur;
	gensymed_symbol = IFIX(position_1);
	temp_1 = IFIX(y_position_qm);
	SVREF(dragging_state,FIX((SI_Long)11L)) = dragger_y;
	M_CADR(positions_and_rest) = position_1;
	gensymed_symbol_1 = temp_1;
	delta_y_in_window = gensymed_symbol - gensymed_symbol_1;
	if ( !(delta_x_in_window == (SI_Long)0L && delta_y_in_window == 
		(SI_Long)0L))
	    move_pane_cursor(pane_cursor,pane,FIX(delta_x_in_window),
		    FIX(delta_y_in_window));
    }
    ab_loop_iter_flag_ = Nil;
    l = CDDDR(l);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* MOVE-BLOCKS-WITH-THEIR-EXTERNAL-CONNECTIONS */
Object move_blocks_with_their_external_connections(block_or_blocks,
	    workspace,delta_x_in_workspace,delta_y_in_workspace)
    Object block_or_blocks, workspace, delta_x_in_workspace;
    Object delta_y_in_workspace;
{
    Object blocks, list_of_blocks, external_connections_to_drag, confine_qm;
    Object connection, ab_loop_list_;
    Object result;

    x_note_fn_call(128,131);
    blocks = ATOM(block_or_blocks) ? dragging_cons_1(block_or_blocks,Nil) :
	     copy_list_using_dragging_conses_1(block_or_blocks);
    result = group_blocks_for_move_or_transfer(blocks);
    MVS_3(result,list_of_blocks,external_connections_to_drag,confine_qm);
    if (confine_qm) {
	connection = Nil;
	ab_loop_list_ = external_connections_to_drag;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	connection = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	put_kink_into_connection_if_straight(connection,list_of_blocks);
	goto next_loop;
      end_loop:;
    }
    shift_blocks_with_their_external_connections(8,list_of_blocks,
	    external_connections_to_drag,Nil,workspace,
	    delta_x_in_workspace,delta_y_in_workspace,Nil,T);
    reclaim_dragging_list_1(list_of_blocks);
    return reclaim_dragging_list_1(external_connections_to_drag);
}

/* TRANSFER-BLOCKS-WITH-THEIR-EXTERNAL-CONNECTIONS */
Object transfer_blocks_with_their_external_connections(blocks,workspace_qm,
	    new_x_qm,new_y_qm,note_as_kb_state_change_qm)
    Object blocks, workspace_qm, new_x_qm, new_y_qm;
    Object note_as_kb_state_change_qm;
{
    Object list_of_blocks, external_connections_to_drag, confine_qm, temp;
    Object temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(128,132);
    PUSH_SPECIAL_WITH_SYMBOL(Note_as_kb_state_change_qm,Qnote_as_kb_state_change_qm,note_as_kb_state_change_qm,
	    0);
      blocks = ATOM(blocks) ? dragging_cons_1(blocks,Nil) : 
	      copy_list_using_dragging_conses_1(blocks);
      result = group_blocks_for_move_or_transfer(blocks);
      MVS_3(result,list_of_blocks,external_connections_to_drag,confine_qm);
      if (confine_qm) {
	  reclaim_dragging_list_1(external_connections_to_drag);
	  temp = item_to_transfer_connected_stack_error(blocks);
      }
      else {
	  temp =  !TRUEP(new_x_qm) ? FIX((SI_Long)0L) : 
		  FIXNUM_MINUS(new_x_qm,item_x_position(CAR(list_of_blocks)));
	  temp_1 =  !TRUEP(new_y_qm) ? FIX((SI_Long)0L) : 
		  FIXNUM_NEGATE(FIXNUM_MINUS(new_y_qm,
		  item_y_position(CAR(list_of_blocks))));
	  transfer_grouped_blocks_with_their_external_connections(list_of_blocks,
		  external_connections_to_drag,workspace_qm,temp,temp_1,
		  Note_as_kb_state_change_qm);
	  reclaim_dragging_list_1(list_of_blocks);
	  reclaim_dragging_list_1(external_connections_to_drag);
	  temp = Nil;
      }
      result = VALUES_1(temp);
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Transfer_in_progress, Qtransfer_in_progress);

DEFINE_VARIABLE_WITH_SYMBOL(Saved_position_or_next_lower_thing, Qsaved_position_or_next_lower_thing);

static Object Qjust_erase;         /* just-erase */

static Object Qworkspace_frame;    /* workspace-frame */

/* TRANSFER-GROUPED-BLOCKS-WITH-THEIR-EXTERNAL-CONNECTIONS */
Object transfer_grouped_blocks_with_their_external_connections(blocks,
	    external_connections,workspace_qm,delta_x_in_workspace,
	    delta_y_in_workspace,note_as_kb_state_change_qm)
    Object blocks, external_connections, workspace_qm, delta_x_in_workspace;
    Object delta_y_in_workspace, note_as_kb_state_change_qm;
{
    Object gensymed_symbol, original_workspace_qm, current_drawing_priority;
    Object region_invalidation_is_preferred;
    Object saved_position_or_next_lower_thing, block, ab_loop_list_;
    Object reversed_blocks, do_not_note_permanent_changes_p;
    Object transfer_in_progress;
    Declare_special(6);
    Object result;

    x_note_fn_call(128,133);
    PUSH_SPECIAL_WITH_SYMBOL(Note_as_kb_state_change_qm,Qnote_as_kb_state_change_qm,note_as_kb_state_change_qm,
	    5);
      gensymed_symbol = ACCESS_ONCE(ISVREF(CAR(blocks),(SI_Long)14L));
      gensymed_symbol = gensymed_symbol ? 
	      ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
      original_workspace_qm = gensymed_symbol;
      current_drawing_priority = Kdraw_as_late_as_possible;
      PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_priority,Qcurrent_drawing_priority,current_drawing_priority,
	      4);
	region_invalidation_is_preferred = T;
	saved_position_or_next_lower_thing = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Saved_position_or_next_lower_thing,Qsaved_position_or_next_lower_thing,saved_position_or_next_lower_thing,
		3);
	  PUSH_SPECIAL_WITH_SYMBOL(Region_invalidation_is_preferred,Qregion_invalidation_is_preferred,region_invalidation_is_preferred,
		  2);
	    if ( !EQ(original_workspace_qm,workspace_qm))
		note_modification_of_module_for_clear_text(workspace_qm,
			original_workspace_qm);
	    if (original_workspace_qm &&  !EQ(original_workspace_qm,
		    workspace_qm)) {
		block = Nil;
		ab_loop_list_ = blocks;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		block = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if ((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
			(SI_Long)2048L))
		    remove_as_block_being_moved(block);
		goto next_loop;
	      end_loop:;
		shift_blocks_with_their_external_connections(6,blocks,
			external_connections,Qjust_erase,
			original_workspace_qm,FIX((SI_Long)0L),
			FIX((SI_Long)0L));
	    }
	    if (workspace_qm) {
		if (Note_as_kb_state_change_qm)
		    note_kb_state_change(workspace_qm,Qworkspace_frame);
	    }
	    reversed_blocks = reverse_list_using_gensym_conses(blocks);
	    do_not_note_permanent_changes_p = Note_as_kb_state_change_qm;
	    transfer_in_progress = T;
	    PUSH_SPECIAL_WITH_SYMBOL(Transfer_in_progress,Qtransfer_in_progress,transfer_in_progress,
		    1);
	      PUSH_SPECIAL_WITH_SYMBOL(Do_not_note_permanent_changes_p,Qdo_not_note_permanent_changes_p,do_not_note_permanent_changes_p,
		      0);
		block = Nil;
		ab_loop_list_ = reversed_blocks;
	      next_loop_1:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_1;
		block = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		transfer_workspace_subblock(block,original_workspace_qm,
			workspace_qm);
		goto next_loop_1;
	      end_loop_1:;
	      POP_SPECIAL();
	    POP_SPECIAL();
	    if (workspace_qm)
		shift_blocks_with_their_external_connections(8,blocks,
			external_connections,Nil,workspace_qm,
			delta_x_in_workspace,delta_y_in_workspace, 
			!EQ(workspace_qm,original_workspace_qm) ? T : Nil,T);
	    block = Nil;
	    ab_loop_list_ = reversed_blocks;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    block = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (G2_has_v5_mode_windows_p)
		send_ws_representations_item_insert_as_subblock(block,
			workspace_qm,Saved_position_or_next_lower_thing);
	    if (workspace_qm &&  !EQ(original_workspace_qm,workspace_qm) 
		    && ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)16L))
		update_subscriptions_for_add_item_to_workspace(workspace_qm,
			block);
	    goto next_loop_2;
	  end_loop_2:;
	    reclaim_gensym_list_1(reversed_blocks);
	    if (original_workspace_qm &&  !EQ(original_workspace_qm,
		    workspace_qm))
		note_change_to_superior_of_block_or_blocks(blocks);
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
      force_process_drawing_if_appropriate();
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object Qab_gensym;          /* gensym */

/* NOTE-CHANGE-TO-SUPERIOR-OF-BLOCK-OR-BLOCKS */
Object note_change_to_superior_of_block_or_blocks(block_or_blocks)
    Object block_or_blocks;
{
    Object defer_consistency_analysis_qm, compiled_items_deferred_for_analysis;
    Object gensymed_symbol, block, ab_loop_list_, deferred_list_cons_qm, item;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, gensym_cons, temp, temp_1, svref_new_value_1;
    Object temp_2;
    SI_Long svref_new_value;
    Declare_special(2);

    x_note_fn_call(128,134);
    defer_consistency_analysis_qm = T;
    compiled_items_deferred_for_analysis = Nil;
    gensymed_symbol = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Compiled_items_deferred_for_analysis,Qcompiled_items_deferred_for_analysis,compiled_items_deferred_for_analysis,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Defer_consistency_analysis_qm,Qdefer_consistency_analysis_qm,defer_consistency_analysis_qm,
	      0);
	if (ATOM(block_or_blocks))
	    gensymed_symbol = 
		    note_dependent_or_stable_status_change(block_or_blocks);
	else {
	    block = Nil;
	    ab_loop_list_ = block_or_blocks;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    block = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    note_dependent_or_stable_status_change(block);
	    goto next_loop;
	  end_loop:
	    gensymed_symbol = Qnil;
	}
	Defer_consistency_analysis_qm = Nil;
	if (Compiled_items_deferred_for_analysis) {
	    deferred_list_cons_qm = Compiled_items_deferred_for_analysis;
	    item = Nil;
	  next_loop_1:
	    item = M_CAR(deferred_list_cons_qm);
	    if ( !(SIMPLE_VECTOR_P(item) && EQ(ISVREF(item,(SI_Long)1L),
		    Qavailable_frame_vector))) {
		gensymed_symbol_1 = ISVREF(item,(SI_Long)3L);
		if ( !(FIXNUMP(gensymed_symbol_1) ? 
			IFIX(gensymed_symbol_1) == (SI_Long)-1L : 
			    TRUEP(Nil))) {
		    gensymed_symbol_1 = ISVREF(ISVREF(ISVREF(ISVREF(item,
			    (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),
			    (SI_Long)1L);
		    gensymed_symbol_2 = item;
		    gensymed_symbol_3 = Nil;
		    gensymed_symbol_4 = Nil;
		    inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
			    gensymed_symbol_3,gensymed_symbol_4);
		}
		svref_new_value = IFIX(ISVREF(item,(SI_Long)5L)) &  
			~(SI_Long)1048576L;
		ISVREF(item,(SI_Long)5L) = FIX(svref_new_value);
	    }
	    if ( !TRUEP(M_CDR(deferred_list_cons_qm)))
		goto end_loop_1;
	    deferred_list_cons_qm = M_CDR(deferred_list_cons_qm);
	    goto next_loop_1;
	  end_loop_1:
	    if (Compiled_items_deferred_for_analysis &&  !((SI_Long)0L == 
		    inline_debugging_consing())) {
		gensym_cons = Compiled_items_deferred_for_analysis;
	      next_loop_2:
		inline_note_reclaim_cons(gensym_cons,Qab_gensym);
		if (EQ(gensym_cons,deferred_list_cons_qm))
		    goto end_1;
		else if ( !TRUEP(gensym_cons))
		    goto end_1;
		else
		    gensym_cons = CDR(gensym_cons);
		goto next_loop_2;
	      end_loop_2:
	      end_1:;
	    }
	    if (ISVREF(Available_gensym_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_gensym_conses_tail_vector,
			IFIX(Current_thread_index));
		temp_1 = Compiled_items_deferred_for_analysis;
		M_CDR(temp) = temp_1;
		temp = Available_gensym_conses_tail_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = deferred_list_cons_qm;
	    }
	    else {
		temp = Available_gensym_conses_vector;
		temp_1 = Current_thread_index;
		svref_new_value_1 = Compiled_items_deferred_for_analysis;
		SVREF(temp,temp_1) = svref_new_value_1;
		temp = Available_gensym_conses_tail_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = deferred_list_cons_qm;
	    }
	    M_CDR(deferred_list_cons_qm) = Nil;
	}
	temp_2 = gensymed_symbol;
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp_2);
}

/* TRANSFER-WORKSPACE-SUBBLOCK */
Object transfer_workspace_subblock(block,source_workspace_qm,
	    destination_workspace_qm)
    Object block, source_workspace_qm, destination_workspace_qm;
{
    Object source_module_qm, destination_module_qm, frame_serial_number;
    Object gensymed_symbol, xa, ya, gensymed_symbol_1, now_showing_qm;
    char temp;

    x_note_fn_call(128,135);
    source_module_qm = source_workspace_qm ? 
	    get_module_block_is_in(source_workspace_qm) : Nil;
    destination_module_qm = destination_workspace_qm ? 
	    get_module_block_is_in(destination_workspace_qm) : Nil;
    if (source_workspace_qm &&  !TRUEP(destination_workspace_qm) &&  
	    !EQ(destination_module_qm,source_module_qm))
	remove_as_inferior_block(block,source_workspace_qm);
    if (source_workspace_qm &&  !EQ(source_workspace_qm,
	    destination_workspace_qm)) {
	frame_serial_number = 
		copy_frame_serial_number(ISVREF(source_workspace_qm,
		(SI_Long)3L));
	remove_as_subblock(block,source_workspace_qm,T);
	gensymed_symbol = ISVREF(source_workspace_qm,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(source_workspace_qm) ? 
		EQ(ISVREF(source_workspace_qm,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else if (FIXNUMP(frame_serial_number))
	    temp = FIXNUMP(gensymed_symbol) ? 
		    FIXNUM_LT(frame_serial_number,gensymed_symbol) : TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(frame_serial_number);
	    ya = M_CAR(gensymed_symbol);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? 
			FIXNUM_LT(M_CDR(frame_serial_number),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
	if (temp)
	    source_workspace_qm = Nil;
	reclaim_frame_serial_number(frame_serial_number);
    }
    if ( !TRUEP(destination_workspace_qm)) {
	gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(block,(SI_Long)1L),
		(SI_Long)11L),(SI_Long)30L),(SI_Long)1L);
	gensymed_symbol_1 = block;
	inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    }
    else if ( !EQ(destination_workspace_qm,source_workspace_qm))
	add_subblock(block,destination_workspace_qm);
    if ( !EQ(source_workspace_qm,destination_workspace_qm)) {
	install_item_in_model_if_models_used(block);
	now_showing_qm = destination_workspace_qm && 
		(ISVREF(destination_workspace_qm,(SI_Long)16L) ||  
		!TRUEP(Nil) && 
		workspace_showing_on_ui_client_p(destination_workspace_qm)) 
		? T : Nil;
	if ( !EQ(source_workspace_qm && (ISVREF(source_workspace_qm,
		(SI_Long)16L) ||  !TRUEP(Nil) && 
		workspace_showing_on_ui_client_p(source_workspace_qm)) ? T 
		: Nil,now_showing_qm))
	    event_update_status_of_block_showing(block,Nil,now_showing_qm);
    }
    return VALUES_1(Nil);
}

Object Selection_handle_hit_distance = UNBOUND;

Object The_type_description_of_selection_handle_spot = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_selection_handle_spots, Qchain_of_available_selection_handle_spots);

DEFINE_VARIABLE_WITH_SYMBOL(Selection_handle_spot_count, Qselection_handle_spot_count);

Object Chain_of_available_selection_handle_spots_vector = UNBOUND;

/* SELECTION-HANDLE-SPOT-STRUCTURE-MEMORY-USAGE */
Object selection_handle_spot_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(128,136);
    temp = Selection_handle_spot_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)8L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-SELECTION-HANDLE-SPOT-COUNT */
Object outstanding_selection_handle_spot_count()
{
    Object def_structure_selection_handle_spot_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(128,137);
    gensymed_symbol = IFIX(Selection_handle_spot_count);
    def_structure_selection_handle_spot_variable = 
	    Chain_of_available_selection_handle_spots;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_selection_handle_spot_variable))
	goto end_loop;
    def_structure_selection_handle_spot_variable = 
	    ISVREF(def_structure_selection_handle_spot_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-SELECTION-HANDLE-SPOT-1 */
Object reclaim_selection_handle_spot_1(selection_handle_spot)
    Object selection_handle_spot;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(128,138);
    inline_note_reclaim_cons(selection_handle_spot,Nil);
    structure_being_reclaimed = selection_handle_spot;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_structure_if_any(ISVREF(selection_handle_spot,(SI_Long)2L));
      SVREF(selection_handle_spot,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_selection_handle_spots_vector,
	    IFIX(Current_thread_index));
    SVREF(selection_handle_spot,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_selection_handle_spots_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = selection_handle_spot;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-SELECTION-HANDLE-SPOT */
Object reclaim_structure_for_selection_handle_spot(selection_handle_spot)
    Object selection_handle_spot;
{
    x_note_fn_call(128,139);
    return reclaim_selection_handle_spot_1(selection_handle_spot);
}

static Object Qg2_defstruct_structure_name_selection_handle_spot_g2_struct;  /* g2-defstruct-structure-name::selection-handle-spot-g2-struct */

/* MAKE-PERMANENT-SELECTION-HANDLE-SPOT-STRUCTURE-INTERNAL */
Object make_permanent_selection_handle_spot_structure_internal()
{
    Object def_structure_selection_handle_spot_variable;
    Object defstruct_g2_selection_handle_spot_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(128,140);
    def_structure_selection_handle_spot_variable = Nil;
    atomic_incff_symval(Qselection_handle_spot_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_selection_handle_spot_variable = Nil;
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
	defstruct_g2_selection_handle_spot_variable = the_array;
	SVREF(defstruct_g2_selection_handle_spot_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_selection_handle_spot_g2_struct;
	SVREF(defstruct_g2_selection_handle_spot_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_selection_handle_spot_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_selection_handle_spot_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_selection_handle_spot_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_selection_handle_spot_variable,
		FIX((SI_Long)5L)) = Nil;
	def_structure_selection_handle_spot_variable = 
		defstruct_g2_selection_handle_spot_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_selection_handle_spot_variable);
}

/* MAKE-SELECTION-HANDLE-SPOT-1 */
Object make_selection_handle_spot_1()
{
    Object def_structure_selection_handle_spot_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(128,141);
    def_structure_selection_handle_spot_variable = 
	    ISVREF(Chain_of_available_selection_handle_spots_vector,
	    IFIX(Current_thread_index));
    if (def_structure_selection_handle_spot_variable) {
	svref_arg_1 = Chain_of_available_selection_handle_spots_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_selection_handle_spot_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_selection_handle_spot_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_selection_handle_spot_g2_struct;
    }
    else
	def_structure_selection_handle_spot_variable = 
		make_permanent_selection_handle_spot_structure_internal();
    inline_note_allocate_cons(def_structure_selection_handle_spot_variable,
	    Nil);
    SVREF(def_structure_selection_handle_spot_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_selection_handle_spot_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_selection_handle_spot_variable,FIX((SI_Long)3L)) = T;
    SVREF(def_structure_selection_handle_spot_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_selection_handle_spot_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_selection_handle_spot_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_selection_handle_spot_variable,FIX((SI_Long)7L)) = Nil;
    return VALUES_1(def_structure_selection_handle_spot_variable);
}

/* PUSH-SELECTION-HANDLE-SPOT */
Object push_selection_handle_spot(mouse_pointer,block,type,handle,
	    x_in_workspace,y_in_workspace)
    Object mouse_pointer, block, type, handle, x_in_workspace, y_in_workspace;
{
    Object spot;

    x_note_fn_call(128,142);
    spot = make_selection_handle_spot_1();
    SVREF(spot,FIX((SI_Long)6L)) = type;
    SVREF(spot,FIX((SI_Long)7L)) = handle;
    push_last_spot(mouse_pointer,spot,block);
    return VALUES_1(spot);
}

static Object Qvertex;             /* vertex */

static Object Qsize_all;           /* size-all */

static Object Qresize;             /* resize */

static Object Qtop;                /* top */

static Object Qbottom;             /* bottom */

static Object Qsize_ns;            /* size-ns */

static Object Qleft;               /* left */

static Object Qright;              /* right */

static Object Qsize_we;            /* size-we */

static Object Qtop_left;           /* top-left */

static Object Qbottom_right;       /* bottom-right */

static Object Qsize_nw_se;         /* size-nw-se */

static Object Qtop_right;          /* top-right */

static Object Qbottom_left;        /* bottom-left */

static Object Qsize_ne_sw;         /* size-ne-sw */

static Object Qdefault;            /* default */

/* SELECTION-HANDLE-MOUSE-CURSOR */
Object selection_handle_mouse_cursor(selection_handle_spot)
    Object selection_handle_spot;
{
    Object temp;

    x_note_fn_call(128,143);
    temp = ISVREF(selection_handle_spot,(SI_Long)6L);
    if (EQ(temp,Qvertex))
	return VALUES_1(Qsize_all);
    else if (EQ(temp,Qresize)) {
	temp = ISVREF(selection_handle_spot,(SI_Long)7L);
	if (EQ(temp,Qtop) || EQ(temp,Qbottom))
	    return VALUES_1(Qsize_ns);
	else if (EQ(temp,Qleft) || EQ(temp,Qright))
	    return VALUES_1(Qsize_we);
	else if (EQ(temp,Qtop_left) || EQ(temp,Qbottom_right))
	    return VALUES_1(Qsize_nw_se);
	else if (EQ(temp,Qtop_right) || EQ(temp,Qbottom_left))
	    return VALUES_1(Qsize_ne_sw);
	else
	    return VALUES_1(Qdefault);
    }
    else
	return VALUES_1(Qdefault);
}

/* GENERATE-SPOT-FOR-SELECTION-HANDLE */
Object generate_spot_for_selection_handle(block,mouse_pointer)
    Object block, mouse_pointer;
{
    Object image_plane, x_in_workspace, y_in_workspace, x_in_window;
    Object y_in_window, current_window_1, drawing_on_window;
    Object current_drawing_transfer_mode, type_of_current_window;
    Object current_native_window_qm, current_color_map, temp;
    Object current_background_color_value, current_foreground_color_value;
    Object current_frame_transform_qm, current_image_x_scale;
    Object current_image_y_scale, current_x_origin_of_drawing;
    Object current_y_origin_of_drawing, current_pane, current_image_plane;
    Object loose_left_edge_of_visible_workspace_area;
    Object loose_top_edge_of_visible_workspace_area;
    Object loose_right_edge_of_visible_workspace_area;
    Object loose_bottom_edge_of_visible_workspace_area, color_or_metacolor;
    Object background_color_or_metacolor, handle_positions, dist, handle_qm;
    Object x0, y0_1, name, x, y, ab_loop_list_, d;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long unshifted_result, d1, d2;
    double fd1, fd2;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(21);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(128,144);
    SAVE_STACK();
    image_plane = image_plane_blackboard_function(mouse_pointer);
    x_in_workspace = x_in_workspace_blackboard_function(mouse_pointer);
    y_in_workspace = y_in_workspace_blackboard_function(mouse_pointer);
    x_in_window = x_in_window_blackboard_function(mouse_pointer);
    y_in_window = y_in_window_blackboard_function(mouse_pointer);
    if (image_plane && x_in_workspace && y_in_workspace && x_in_window && 
	    y_in_window) {
	LOCK(On_window_without_drawing);
	if (PUSH_UNWIND_PROTECT(1)) {
	    current_window_1 = ISVREF(ISVREF(image_plane,(SI_Long)2L),
		    (SI_Long)2L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
		    20);
	      drawing_on_window = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Drawing_on_window,Qdrawing_on_window,drawing_on_window,
		      19);
		current_drawing_transfer_mode = 
			EQ(Current_drawing_transfer_mode,Kxor) ? 
			Current_drawing_transfer_mode : 
			ISVREF(Current_window,(SI_Long)30L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
			18);
		  type_of_current_window = ISVREF(Current_window,(SI_Long)1L);
		  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
			  17);
		    current_native_window_qm = ISVREF(Current_window,
			    (SI_Long)17L);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
			    16);
		      current_color_map = ISVREF(Current_window,(SI_Long)20L);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_color_map,Qcurrent_color_map,current_color_map,
			      15);
			temp = ISVREF(Current_color_map,(SI_Long)5L);
			if (temp);
			else
			    temp = map_to_color_value_1(Qwhite);
			current_background_color_value = temp;
			PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
				14);
			  temp = ISVREF(Current_color_map,(SI_Long)4L);
			  if (temp);
			  else
			      temp = map_to_color_value_1(Qblack);
			  current_foreground_color_value = temp;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
				  13);
			    current_frame_transform_qm = Nil;
			    current_image_x_scale = ISVREF(image_plane,
				    (SI_Long)11L);
			    current_image_y_scale = ISVREF(image_plane,
				    (SI_Long)12L);
			    current_x_origin_of_drawing = 
				    ISVREF(image_plane,(SI_Long)13L);
			    current_y_origin_of_drawing = 
				    ISVREF(image_plane,(SI_Long)14L);
			    PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
				    12);
			      PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
				      11);
				PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
					10);
				  PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
					  9);
				    PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
					    8);
				      LOCK(For_image_plane);
				      if (PUSH_UNWIND_PROTECT(0)) {
					  current_pane = 
						  ISVREF(image_plane,
						  (SI_Long)2L);
					  current_image_plane = image_plane;
					  loose_left_edge_of_visible_workspace_area 
						  = ISVREF(image_plane,
						  (SI_Long)23L);
					  loose_top_edge_of_visible_workspace_area 
						  = ISVREF(image_plane,
						  (SI_Long)24L);
					  loose_right_edge_of_visible_workspace_area 
						  = ISVREF(image_plane,
						  (SI_Long)25L);
					  loose_bottom_edge_of_visible_workspace_area 
						  = ISVREF(image_plane,
						  (SI_Long)26L);
					  color_or_metacolor = 
						  ISVREF(image_plane,
						  (SI_Long)5L) ? 
						  ISVREF(ISVREF(image_plane,
						  (SI_Long)5L),
						  (SI_Long)22L) : Nil;
					  if (color_or_metacolor);
					  else
					      color_or_metacolor = Qblack;
					  if (EQ(color_or_metacolor,
						  Qtransparent) || 
						  EQ(color_or_metacolor,
						  Qbackground)) {
					      background_color_or_metacolor 
						      = ISVREF(image_plane,
						      (SI_Long)5L) ? 
						      ISVREF(ISVREF(image_plane,
						      (SI_Long)5L),
						      (SI_Long)21L) : Nil;
					      if (background_color_or_metacolor);
					      else
						  background_color_or_metacolor 
							  = Qwhite;
					      if (EQ(background_color_or_metacolor,
						      Qforeground) || 
						      EQ(background_color_or_metacolor,
						      Qworkspace_foreground)) {
						  temp = 
							  ISVREF(Current_color_map,
							  (SI_Long)4L);
						  if (temp);
						  else
						      temp = 
							      map_to_color_value_1(Qblack);
						  current_foreground_color_value 
							  = temp;
					      }
					      else if (EQ(background_color_or_metacolor,
						      Qtransparent) || 
						      EQ(background_color_or_metacolor,
						      Qbackground)) {
						  temp = 
							  ISVREF(Current_color_map,
							  (SI_Long)5L);
						  if (temp);
						  else
						      temp = 
							      map_to_color_value_1(Qwhite);
						  current_foreground_color_value 
							  = temp;
					      }
					      else
						  current_foreground_color_value 
							  = 
							  EQ(background_color_or_metacolor,
							  ISVREF(Current_color_map,
							  (SI_Long)6L)) ? 
							  ISVREF(Current_color_map,
							  (SI_Long)7L) : 
							  map_to_color_value_1(background_color_or_metacolor);
					  }
					  else if (EQ(color_or_metacolor,
						  Qforeground) || 
						  EQ(color_or_metacolor,
						  Qworkspace_foreground)) {
					      temp = 
						      ISVREF(Current_color_map,
						      (SI_Long)4L);
					      if (temp);
					      else
						  temp = 
							  map_to_color_value_1(Qblack);
					      current_foreground_color_value 
						      = temp;
					  }
					  else
					      current_foreground_color_value 
						      = 
						      EQ(color_or_metacolor,
						      ISVREF(Current_color_map,
						      (SI_Long)6L)) ? 
						      ISVREF(Current_color_map,
						      (SI_Long)7L) : 
						      map_to_color_value_1(color_or_metacolor);
					  PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
						  7);
					    PUSH_SPECIAL_WITH_SYMBOL(Loose_bottom_edge_of_visible_workspace_area,Qloose_bottom_edge_of_visible_workspace_area,loose_bottom_edge_of_visible_workspace_area,
						    6);
					      PUSH_SPECIAL_WITH_SYMBOL(Loose_right_edge_of_visible_workspace_area,Qloose_right_edge_of_visible_workspace_area,loose_right_edge_of_visible_workspace_area,
						      5);
						PUSH_SPECIAL_WITH_SYMBOL(Loose_top_edge_of_visible_workspace_area,Qloose_top_edge_of_visible_workspace_area,loose_top_edge_of_visible_workspace_area,
							4);
						  PUSH_SPECIAL_WITH_SYMBOL(Loose_left_edge_of_visible_workspace_area,Qloose_left_edge_of_visible_workspace_area,loose_left_edge_of_visible_workspace_area,
							  3);
						    PUSH_SPECIAL_WITH_SYMBOL(Current_image_plane,Qcurrent_image_plane,current_image_plane,
							    2);
						      PUSH_SPECIAL_WITH_SYMBOL(Current_pane,Qcurrent_pane,current_pane,
							      1);
							color_or_metacolor 
								= 
								ISVREF(image_plane,
								(SI_Long)5L) 
								? 
								ISVREF(ISVREF(image_plane,
								(SI_Long)5L),
								(SI_Long)21L) 
								: Nil;
							if (color_or_metacolor);
							else
							    color_or_metacolor 
								    = Qwhite;
							if (EQ(color_or_metacolor,
								Qtransparent) 
								|| 
								EQ(color_or_metacolor,
								Qbackground)) {
							    temp = 
								    ISVREF(Current_color_map,
								    (SI_Long)5L);
							    if (temp);
							    else
								temp = 
									map_to_color_value_1(Qwhite);
							    current_background_color_value 
								    = temp;
							}
							else if (EQ(color_or_metacolor,
								Qforeground) 
								|| 
								EQ(color_or_metacolor,
								Qworkspace_foreground)) 
								    {
							    temp = 
								    ISVREF(image_plane,
								    (SI_Long)5L) 
								    ? 
								    ISVREF(ISVREF(image_plane,
								    (SI_Long)5L),
								    (SI_Long)22L) 
								    : Nil;
							    if (temp);
							    else
								temp = Qblack;
							    color_or_metacolor 
								    = temp;
							    if (EQ(color_or_metacolor,
								    Qtransparent) 
								    || 
								    EQ(color_or_metacolor,
								    Qbackground)) 
									{
								background_color_or_metacolor 
									= 
									ISVREF(image_plane,
									(SI_Long)5L) 
									? 
									ISVREF(ISVREF(image_plane,
									(SI_Long)5L),
									(SI_Long)21L) 
									: Nil;
								if (background_color_or_metacolor);
								else
								    background_color_or_metacolor 
									    = 
									    Qwhite;
								if (EQ(background_color_or_metacolor,
									Qforeground) 
									|| 
									EQ(background_color_or_metacolor,
									Qworkspace_foreground)) 
									    {
								    temp = 
									    ISVREF(Current_color_map,
									    (SI_Long)4L);
								    if (temp);
								    else
									temp 
										= 
										map_to_color_value_1(Qblack);
								    current_background_color_value 
									    = 
									    temp;
								}
								else if (EQ(background_color_or_metacolor,
									Qtransparent) 
									|| 
									EQ(background_color_or_metacolor,
									Qbackground)) 
									    {
								    temp = 
									    ISVREF(Current_color_map,
									    (SI_Long)5L);
								    if (temp);
								    else
									temp 
										= 
										map_to_color_value_1(Qwhite);
								    current_background_color_value 
									    = 
									    temp;
								}
								else
								    current_background_color_value 
									    = 
									    EQ(background_color_or_metacolor,
									    ISVREF(Current_color_map,
									    (SI_Long)6L)) 
									    ?
									     
									    ISVREF(Current_color_map,
									    (SI_Long)7L) 
									    :
									     
									    map_to_color_value_1(background_color_or_metacolor);
							    }
							    else if (EQ(color_or_metacolor,
								    Qforeground) 
								    || 
								    EQ(color_or_metacolor,
								    Qworkspace_foreground)) 
									{
								temp = 
									ISVREF(Current_color_map,
									(SI_Long)4L);
								if (temp);
								else
								    temp = 
									    map_to_color_value_1(Qblack);
								current_background_color_value 
									= temp;
							    }
							    else
								current_background_color_value 
									= 
									EQ(color_or_metacolor,
									ISVREF(Current_color_map,
									(SI_Long)6L)) 
									? 
									ISVREF(Current_color_map,
									(SI_Long)7L) 
									: 
									map_to_color_value_1(color_or_metacolor);
							}
							else
							    current_background_color_value 
								    = 
								    EQ(color_or_metacolor,
								    ISVREF(Current_color_map,
								    (SI_Long)6L)) 
								    ? 
								    ISVREF(Current_color_map,
								    (SI_Long)7L) 
								    : 
								    map_to_color_value_1(color_or_metacolor);
							PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
								0);
							  handle_positions 
								  = 
								  selection_handle_positions(block);
							  dist = 
								  Selection_handle_hit_distance;
							  handle_qm = Nil;
							  x0 = Nil;
							  y0_1 = Nil;
							  name = Nil;
							  x = Nil;
							  y = Nil;
							  ab_loop_list_ = 
								  handle_positions;
							  d = Nil;
							  if ( 
								  !TRUEP(ab_loop_list_))
							      goto end_loop;
							next_loop:
							  name = 
								  CAR(ab_loop_list_);
							  temp = 
								  CDR(ab_loop_list_);
							  x = CAR(temp);
							  temp = 
								  CDR(ab_loop_list_);
							  temp = CDR(temp);
							  y = CAR(temp);
							  gensymed_symbol 
								  = 
								  IFIX(x_in_window);
							  gensymed_symbol_1 
								  = 
								  IFIX(Current_x_origin_of_drawing);
							  if (IFIX(Current_image_x_scale) 
								  == 
								  (SI_Long)4096L)
							      gensymed_symbol_2 
								      = 
								      IFIX(x);
							  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
								  Current_image_x_scale) 
								  && 
								  FIXNUM_LT(Current_image_x_scale,
								  Isqrt_of_most_positive_fixnum) 
								  && 
								  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
								  x) && 
								  FIXNUM_LT(x,
								  Isqrt_of_most_positive_fixnum)) 
								      {
							      unshifted_result 
								      = 
								      IFIX(FIXNUM_TIMES(Current_image_x_scale,
								      x)) 
								      + 
								      (SI_Long)2048L;
							      gensymed_symbol_2 
								      = 
								      unshifted_result 
								      >>  
								      -  - 
								      (SI_Long)12L;
							  }
							  else
							      gensymed_symbol_2 
								      = 
								      IFIX(scalef_function(Current_image_x_scale,
								      x));
							  gensymed_symbol_1 
								  = 
								  gensymed_symbol_1 
								  + 
								  gensymed_symbol_2;
							  gensymed_symbol 
								  = 
								  gensymed_symbol 
								  - 
								  gensymed_symbol_1;
							  d1 = 
								  ABS(gensymed_symbol);
							  gensymed_symbol 
								  = 
								  IFIX(y_in_window);
							  gensymed_symbol_1 
								  = 
								  IFIX(Current_y_origin_of_drawing);
							  if (IFIX(Current_image_y_scale) 
								  == 
								  (SI_Long)4096L)
							      gensymed_symbol_2 
								      = 
								      IFIX(y);
							  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
								  Current_image_y_scale) 
								  && 
								  FIXNUM_LT(Current_image_y_scale,
								  Isqrt_of_most_positive_fixnum) 
								  && 
								  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
								  y) && 
								  FIXNUM_LT(y,
								  Isqrt_of_most_positive_fixnum)) 
								      {
							      unshifted_result 
								      = 
								      IFIX(FIXNUM_TIMES(Current_image_y_scale,
								      y)) 
								      + 
								      (SI_Long)2048L;
							      gensymed_symbol_2 
								      = 
								      unshifted_result 
								      >>  
								      -  - 
								      (SI_Long)12L;
							  }
							  else
							      gensymed_symbol_2 
								      = 
								      IFIX(scalef_function(Current_image_y_scale,
								      y));
							  gensymed_symbol_1 
								  = 
								  gensymed_symbol_1 
								  + 
								  gensymed_symbol_2;
							  gensymed_symbol 
								  = 
								  gensymed_symbol 
								  - 
								  gensymed_symbol_1;
							  d2 = 
								  ABS(gensymed_symbol);
							  if (d1 < 
								  IFIX(Maximum_x_or_y_separation_allowing_fixnum_vector_distance_calculation) 
								  && d2 < 
								  IFIX(Maximum_x_or_y_separation_allowing_fixnum_vector_distance_calculation))
							      d = 
								      isqrt(FIX(d1 
								      * d1 
								      + d2 
								      * d2));
							  else {
							      if (PUSH_LOCAL_ALLOCATION(Local_area,
								      0,0)) {
								  fd1 = 
									  (double)d1;
								  fd2 = 
									  (double)d2;
								  d = 
									  l_round(DOUBLE_TO_DOUBLE_FLOAT(sqrt(fd1 
									  * 
									  fd1 
									  + 
									  fd2 
									  * 
									  fd2)),
									  _);
							      }
							      POP_LOCAL_ALLOCATION(0,0);
							  }
							  if (FIXNUM_LT(d,
								  dist)) {
							      dist = d;
							      handle_qm = name;
							      x0 = x;
							      y0_1 = y;
							  }
							  ab_loop_list_ = 
								  CDDDR(ab_loop_list_);
							  if ( 
								  !TRUEP(ab_loop_list_))
							      goto end_loop;
							  goto next_loop;
							end_loop:;
							  reclaim_graphics_list_1(handle_positions);
							  if (handle_qm)
							      SAVE_VALUES(push_selection_handle_spot(mouse_pointer,
								      block,
								      Qresize,
								      handle_qm,
								      x0,
								      y0_1));
							  else
							      SAVE_VALUES(VALUES_1(Nil));
							POP_SPECIAL();
						      POP_SPECIAL();
						    POP_SPECIAL();
						  POP_SPECIAL();
						POP_SPECIAL();
					      POP_SPECIAL();
					    POP_SPECIAL();
					  POP_SPECIAL();
				      }
				      POP_UNWIND_PROTECT(0);
				      UNLOCK(For_image_plane);
				      CONTINUE_UNWINDING(0);
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
	POP_UNWIND_PROTECT(1);
	UNLOCK(On_window_without_drawing);
	CONTINUE_UNWINDING(1);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

/* SELECTION-HANDLE-POSITIONS */
Object selection_handle_positions(block)
    Object block;
{
    Object gensymed_symbol, left, top, right, bottom, gensymed_symbol_1;

    x_note_fn_call(128,145);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    left = gensymed_symbol;
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    top = gensymed_symbol;
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    right = gensymed_symbol;
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    bottom = gensymed_symbol;
    gensymed_symbol = make_graphics_list_1(FIX((SI_Long)12L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = Qtop_left;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = left;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = top;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qtop_right;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = right;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = top;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qbottom_right;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = right;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = bottom;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qbottom_left;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = left;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = bottom;
    return VALUES_1(gensymed_symbol);
}

/* ADJUST-RECTANGLE-EDGES */
Object adjust_rectangle_edges(edge_or_corner,left,top,right,bottom,dx,dy)
    Object edge_or_corner, left, top, right, bottom, dx, dy;
{
    Object incff_1_arg;

    x_note_fn_call(128,146);
    if (EQ(edge_or_corner,Qtop)) {
	incff_1_arg = dy;
	top = FIXNUM_ADD(top,incff_1_arg);
    }
    else if (EQ(edge_or_corner,Qleft)) {
	incff_1_arg = left;
	left = FIXNUM_ADD(left,incff_1_arg);
    }
    else if (EQ(edge_or_corner,Qbottom)) {
	incff_1_arg = dy;
	bottom = FIXNUM_ADD(bottom,incff_1_arg);
    }
    else if (EQ(edge_or_corner,Qright)) {
	incff_1_arg = dy;
	right = FIXNUM_ADD(right,incff_1_arg);
    }
    else if (EQ(edge_or_corner,Qtop_left)) {
	incff_1_arg = dx;
	left = FIXNUM_ADD(left,incff_1_arg);
	incff_1_arg = dy;
	top = FIXNUM_ADD(top,incff_1_arg);
    }
    else if (EQ(edge_or_corner,Qtop_right)) {
	incff_1_arg = dx;
	right = FIXNUM_ADD(right,incff_1_arg);
	incff_1_arg = dy;
	top = FIXNUM_ADD(top,incff_1_arg);
    }
    else if (EQ(edge_or_corner,Qbottom_right)) {
	incff_1_arg = dx;
	right = FIXNUM_ADD(right,incff_1_arg);
	incff_1_arg = dy;
	bottom = FIXNUM_ADD(bottom,incff_1_arg);
    }
    else if (EQ(edge_or_corner,Qbottom_left)) {
	incff_1_arg = dx;
	left = FIXNUM_ADD(left,incff_1_arg);
	incff_1_arg = dy;
	bottom = FIXNUM_ADD(bottom,incff_1_arg);
    }
    return VALUES_4(left,top,right,bottom);
}

DEFINE_VARIABLE_WITH_SYMBOL(Selection_handle_icon, Qselection_handle_icon);

static Object Qshow_selection_handles;  /* show-selection-handles */

/* SELECTION-HANDLES-VISIBLE-P */
Object selection_handles_visible_p(thing,image_plane)
    Object thing, image_plane;
{
    x_note_fn_call(128,147);
    if (get_lookup_slot_value_given_default(Drawing_parameters,
	    Qshow_selection_handles,T) && image_plane_selected_p(image_plane))
	return thing_selected_p(thing,image_plane);
    else
	return VALUES_1(Nil);
}

static Object Qicon_color_pattern;  /* icon-color-pattern */

static Object Qline;               /* line */

/* DRAW-SELECTION-HANDLE */
Object draw_selection_handle(icon_description,color,x_in_window,y_in_window)
    Object icon_description, color, x_in_window, y_in_window;
{
    Object current_image_x_scale, current_image_y_scale, scale, scale_1, value;
    Object current_x_origin_of_drawing, current_y_origin_of_drawing;
    Object icon_attributes_plist;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, temp;
    SI_Long value_1, unshifted_result;
    Declare_special(4);
    Object result;

    x_note_fn_call(128,148);
    current_image_x_scale = FIX((SI_Long)4096L);
    current_image_y_scale = FIX((SI_Long)4096L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
	    3);
      PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
	      2);
	gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	scale = Current_image_x_scale;
	gensymed_symbol_1 = IFIX(Selection_handle_radius);
	scale_1 = Current_image_x_scale;
	value = FIXNUM_MINUS(x_in_window,Current_x_origin_of_drawing);
	if (IFIX(scale_1) == (SI_Long)4096L)
	    gensymed_symbol_2 = IFIX(value);
	else if ( !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		value) && FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)))
	    gensymed_symbol_2 = IFIX(inverse_scalef_function(scale_1,value));
	else if (IFIX(value) >= (SI_Long)0L) {
	    temp = ((IFIX(value) << (SI_Long)12L) + (IFIX(scale_1) >>  -  
		    - (SI_Long)1L)) / IFIX(scale_1);
	    gensymed_symbol_2 = temp;
	}
	else {
	    temp = ((IFIX(FIXNUM_NEGATE(value)) << (SI_Long)12L) + 
		    (IFIX(scale_1) >>  -  - (SI_Long)1L)) / IFIX(scale_1);
	    temp = IFIX(FIXNUM_NEGATE(FIX(temp)));
	    gensymed_symbol_2 = temp;
	}
	value_1 = gensymed_symbol_1 - gensymed_symbol_2;
	if (IFIX(scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = value_1;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		&& FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value_1 && 
		value_1 < IFIX(Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(scale) * value_1 + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(scale,FIX(value_1)));
	current_x_origin_of_drawing = FIX(gensymed_symbol - gensymed_symbol_1);
	PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
		1);
	  gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	  scale = Current_image_y_scale;
	  gensymed_symbol_1 = IFIX(Selection_handle_radius);
	  scale_1 = Current_image_y_scale;
	  value = FIXNUM_MINUS(y_in_window,Current_y_origin_of_drawing);
	  if (IFIX(scale_1) == (SI_Long)4096L)
	      gensymed_symbol_2 = IFIX(value);
	  else if ( !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		  value) && FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)))
	      gensymed_symbol_2 = IFIX(inverse_scalef_function(scale_1,value));
	  else if (IFIX(value) >= (SI_Long)0L) {
	      temp = ((IFIX(value) << (SI_Long)12L) + (IFIX(scale_1) >>  - 
		       - (SI_Long)1L)) / IFIX(scale_1);
	      gensymed_symbol_2 = temp;
	  }
	  else {
	      temp = ((IFIX(FIXNUM_NEGATE(value)) << (SI_Long)12L) + 
		      (IFIX(scale_1) >>  -  - (SI_Long)1L)) / IFIX(scale_1);
	      temp = IFIX(FIXNUM_NEGATE(FIX(temp)));
	      gensymed_symbol_2 = temp;
	  }
	  value_1 = gensymed_symbol_1 - gensymed_symbol_2;
	  if (IFIX(scale) == (SI_Long)4096L)
	      gensymed_symbol_1 = value_1;
	  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		  && FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		  IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value_1 
		  && value_1 < IFIX(Isqrt_of_most_positive_fixnum)) {
	      unshifted_result = IFIX(scale) * value_1 + (SI_Long)2048L;
	      gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	  }
	  else
	      gensymed_symbol_1 = IFIX(scalef_function(scale,FIX(value_1)));
	  current_y_origin_of_drawing = FIX(gensymed_symbol - 
		  gensymed_symbol_1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
		  0);
	    icon_attributes_plist = slot_value_list_2(Qicon_color_pattern,
		    slot_value_list_2(slot_value_cons_1(Qfill,color),
		    slot_value_cons_1(Qline,Qforeground)));
	    draw_icon_from_description(icon_description,
		    icon_attributes_plist,FIX((SI_Long)0L),
		    FIX((SI_Long)0L),ISVREF(icon_description,(SI_Long)1L),
		    ISVREF(icon_description,(SI_Long)2L),Nil);
	    result = reclaim_slot_value_tree_1(icon_attributes_plist);
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* DRAW-SELECTION-HANDLES-FOR-BLOCK */
Object draw_selection_handles_for_block(block,color)
    Object block, color;
{
    Object icon_description, handles, name, x_in_workspace, y_in_workspace;
    Object ab_loop_list_, temp;
    SI_Long gensymed_symbol, gensymed_symbol_1, unshifted_result;

    x_note_fn_call(128,149);
    icon_description = ISVREF(SECOND(Selection_handle_icon),(SI_Long)16L);
    handles = selection_handle_positions(block);
    name = Nil;
    x_in_workspace = Nil;
    y_in_workspace = Nil;
    ab_loop_list_ = handles;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    name = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    x_in_workspace = CAR(temp);
    temp = CDR(ab_loop_list_);
    temp = CDR(temp);
    y_in_workspace = CAR(temp);
    gensymed_symbol = IFIX(Current_x_origin_of_drawing);
    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(x_in_workspace);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    x_in_workspace) && FIXNUM_LT(x_in_workspace,
	    Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		x_in_workspace)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		x_in_workspace));
    temp = FIX(gensymed_symbol + gensymed_symbol_1);
    gensymed_symbol = IFIX(Current_y_origin_of_drawing);
    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(y_in_workspace);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    y_in_workspace) && FIXNUM_LT(y_in_workspace,
	    Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		y_in_workspace)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		y_in_workspace));
    draw_selection_handle(icon_description,color,temp,FIX(gensymed_symbol 
	    + gensymed_symbol_1));
    ab_loop_list_ = CDDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:;
    return reclaim_graphics_list_1(handles);
}

static Object Qred;                /* red */

/* DRAW-SELECTION-HANDLES-FOR-CONNECTION */
Object draw_selection_handles_for_connection(connection,color)
    Object connection, color;
{
    Object vertices, icon_description, x_in_window, y_in_window, rest_1;
    Object ab_loop_list_, first_1, last_1, color_star, ab_loop_iter_flag_;
    Object temp, frame, symbol, gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;

    x_note_fn_call(128,150);
    vertices = compute_connection_vertices(connection);
    icon_description = ISVREF(SECOND(Selection_handle_icon),(SI_Long)16L);
    x_in_window = Nil;
    y_in_window = Nil;
    rest_1 = Nil;
    ab_loop_list_ = vertices;
    first_1 = T;
    last_1 = Nil;
    color_star = Nil;
    ab_loop_iter_flag_ = T;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    x_in_window = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    y_in_window = CAR(temp);
    temp = CDR(ab_loop_list_);
    rest_1 = CDR(temp);
    if ( !TRUEP(ab_loop_iter_flag_))
	first_1 = Nil;
    last_1 =  !TRUEP(rest_1) ? T : Nil;
    if (first_1) {
	frame = ISVREF(connection,(SI_Long)3L);
	symbol = Qloose_end;
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(symbol,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,
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
		temp_1 = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp_1 = TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_1 =  !temp_1;
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1);
    else if (last_1) {
	frame = ISVREF(connection,(SI_Long)2L);
	symbol = Qloose_end;
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(symbol,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,
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
		temp_1 = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp_1 = TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_1 =  !temp_1;
    }
    else
	temp_1 = TRUEP(Nil);
    color_star = temp_1 ? Qred : color;
    draw_selection_handle(icon_description,color_star,x_in_window,y_in_window);
    ab_loop_iter_flag_ = Nil;
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:;
    return reclaim_gensym_list_1(vertices);
}

/* DRAW-SELECTION-HANDLES-FOR-TEXT-CELL */
Object draw_selection_handles_for_text_cell(text_cell,color)
    Object text_cell, color;
{
    Object table_qm, left, top, right, bottom, thick, color_value, temp, scale;
    Object temp_1, temp_2;
    SI_Long tweak, gensymed_symbol, gensymed_symbol_1, unshifted_result, value;
    Object result;

    x_note_fn_call(128,151);
    table_qm = get_table_for_cell(text_cell);
    if (table_qm) {
	result = get_table_cell_edges(table_qm,text_cell);
	MVS_4(result,left,top,right,bottom);
	thick = FIXNUM_SUB1(Selection_highlight_line_width);
	tweak = CAR(text_cell) && IFIX(ISVREF(CAR(text_cell),
		(SI_Long)28L)) <= (SI_Long)1L ? (SI_Long)1L : (SI_Long)0L;
	if (EQ(color,Qbackground))
	    color_value = Current_background_color_value;
	else if (EQ(color,Qforeground) || EQ(color,Qworkspace_foreground))
	    color_value = Current_foreground_color_value;
	else if (EQ(color,Qtransparent))
	    color_value = Current_background_color_value;
	else
	    color_value = map_to_color_value(color);
	gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(left);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,left) && 
		FIXNUM_LT(left,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		    left)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		    left));
	temp = FIX(gensymed_symbol + gensymed_symbol_1);
	gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	scale = Current_image_y_scale;
	value = IFIX(top) - tweak;
	if (IFIX(scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = value;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		&& FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value && 
		value < IFIX(Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(scale,FIX(value)));
	temp_1 = FIX(gensymed_symbol + gensymed_symbol_1);
	gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(right);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,right) && 
		FIXNUM_LT(right,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		    right)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		    right));
	temp_2 = FIX(gensymed_symbol + gensymed_symbol_1);
	gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(bottom);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,bottom) 
		&& FIXNUM_LT(bottom,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		    bottom)) + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		    bottom));
	return paint_rectangle_outline_in_window(temp,temp_1,temp_2,
		FIX(gensymed_symbol + gensymed_symbol_1),color_value,thick,
		thick);
    }
    else
	return VALUES_1(Nil);
}

/* INVALIDATE-SELECTION-HANDLES */
Object invalidate_selection_handles(thing,image_plane)
    Object thing, image_plane;
{
    Object d, region, current_window_1, drawing_on_window;
    Object current_drawing_transfer_mode, type_of_current_window;
    Object current_native_window_qm, current_color_map, temp;
    Object current_background_color_value, current_foreground_color_value;
    Object current_frame_transform_qm, current_image_x_scale;
    Object current_image_y_scale, current_x_origin_of_drawing;
    Object current_y_origin_of_drawing, current_pane, current_image_plane;
    Object loose_left_edge_of_visible_workspace_area;
    Object loose_top_edge_of_visible_workspace_area;
    Object loose_right_edge_of_visible_workspace_area;
    Object loose_bottom_edge_of_visible_workspace_area, color_or_metacolor;
    Object background_color_or_metacolor, vertices, x_in_window, y_in_window;
    Object ab_loop_list_, x2, handles, name, x, y, table_qm, left, top, right;
    Object bottom, w, temp_2, temp_3, current_draw_paper_p;
    SI_Long gensymed_symbol, gensymed_symbol_1, unshifted_result;
    char temp_1;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(22);
    Object result;

    x_note_fn_call(128,152);
    SAVE_STACK();
    d = FIXNUM_ADD1(Selection_handle_radius);
    region = make_empty_region();
    LOCK(On_window_without_drawing);
    if (PUSH_UNWIND_PROTECT(1)) {
	current_window_1 = ISVREF(ISVREF(image_plane,(SI_Long)2L),(SI_Long)2L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
		21);
	  drawing_on_window = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Drawing_on_window,Qdrawing_on_window,drawing_on_window,
		  20);
	    current_drawing_transfer_mode = 
		    EQ(Current_drawing_transfer_mode,Kxor) ? 
		    Current_drawing_transfer_mode : ISVREF(Current_window,
		    (SI_Long)30L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
		    19);
	      type_of_current_window = ISVREF(Current_window,(SI_Long)1L);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
		      18);
		current_native_window_qm = ISVREF(Current_window,(SI_Long)17L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
			17);
		  current_color_map = ISVREF(Current_window,(SI_Long)20L);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_color_map,Qcurrent_color_map,current_color_map,
			  16);
		    temp = ISVREF(Current_color_map,(SI_Long)5L);
		    if (temp);
		    else
			temp = map_to_color_value_1(Qwhite);
		    current_background_color_value = temp;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
			    15);
		      temp = ISVREF(Current_color_map,(SI_Long)4L);
		      if (temp);
		      else
			  temp = map_to_color_value_1(Qblack);
		      current_foreground_color_value = temp;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
			      14);
			current_frame_transform_qm = Nil;
			current_image_x_scale = ISVREF(image_plane,
				(SI_Long)11L);
			current_image_y_scale = ISVREF(image_plane,
				(SI_Long)12L);
			current_x_origin_of_drawing = ISVREF(image_plane,
				(SI_Long)13L);
			current_y_origin_of_drawing = ISVREF(image_plane,
				(SI_Long)14L);
			PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
				13);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
				  12);
			    PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
				    11);
			      PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
				      10);
				PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
					9);
				  LOCK(For_image_plane);
				  if (PUSH_UNWIND_PROTECT(0)) {
				      current_pane = ISVREF(image_plane,
					      (SI_Long)2L);
				      current_image_plane = image_plane;
				      loose_left_edge_of_visible_workspace_area 
					      = ISVREF(image_plane,
					      (SI_Long)23L);
				      loose_top_edge_of_visible_workspace_area 
					      = ISVREF(image_plane,
					      (SI_Long)24L);
				      loose_right_edge_of_visible_workspace_area 
					      = ISVREF(image_plane,
					      (SI_Long)25L);
				      loose_bottom_edge_of_visible_workspace_area 
					      = ISVREF(image_plane,
					      (SI_Long)26L);
				      color_or_metacolor = 
					      ISVREF(image_plane,
					      (SI_Long)5L) ? 
					      ISVREF(ISVREF(image_plane,
					      (SI_Long)5L),(SI_Long)22L) : Nil;
				      if (color_or_metacolor);
				      else
					  color_or_metacolor = Qblack;
				      if (EQ(color_or_metacolor,
					      Qtransparent) || 
					      EQ(color_or_metacolor,
					      Qbackground)) {
					  background_color_or_metacolor = 
						  ISVREF(image_plane,
						  (SI_Long)5L) ? 
						  ISVREF(ISVREF(image_plane,
						  (SI_Long)5L),
						  (SI_Long)21L) : Nil;
					  if (background_color_or_metacolor);
					  else
					      background_color_or_metacolor 
						      = Qwhite;
					  if (EQ(background_color_or_metacolor,
						  Qforeground) || 
						  EQ(background_color_or_metacolor,
						  Qworkspace_foreground)) {
					      temp = 
						      ISVREF(Current_color_map,
						      (SI_Long)4L);
					      if (temp);
					      else
						  temp = 
							  map_to_color_value_1(Qblack);
					      current_foreground_color_value 
						      = temp;
					  }
					  else if (EQ(background_color_or_metacolor,
						  Qtransparent) || 
						  EQ(background_color_or_metacolor,
						  Qbackground)) {
					      temp = 
						      ISVREF(Current_color_map,
						      (SI_Long)5L);
					      if (temp);
					      else
						  temp = 
							  map_to_color_value_1(Qwhite);
					      current_foreground_color_value 
						      = temp;
					  }
					  else
					      current_foreground_color_value 
						      = 
						      EQ(background_color_or_metacolor,
						      ISVREF(Current_color_map,
						      (SI_Long)6L)) ? 
						      ISVREF(Current_color_map,
						      (SI_Long)7L) : 
						      map_to_color_value_1(background_color_or_metacolor);
				      }
				      else if (EQ(color_or_metacolor,
					      Qforeground) || 
					      EQ(color_or_metacolor,
					      Qworkspace_foreground)) {
					  temp = ISVREF(Current_color_map,
						  (SI_Long)4L);
					  if (temp);
					  else
					      temp = 
						      map_to_color_value_1(Qblack);
					  current_foreground_color_value = 
						  temp;
				      }
				      else
					  current_foreground_color_value = 
						  EQ(color_or_metacolor,
						  ISVREF(Current_color_map,
						  (SI_Long)6L)) ? 
						  ISVREF(Current_color_map,
						  (SI_Long)7L) : 
						  map_to_color_value_1(color_or_metacolor);
				      PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
					      8);
					PUSH_SPECIAL_WITH_SYMBOL(Loose_bottom_edge_of_visible_workspace_area,Qloose_bottom_edge_of_visible_workspace_area,loose_bottom_edge_of_visible_workspace_area,
						7);
					  PUSH_SPECIAL_WITH_SYMBOL(Loose_right_edge_of_visible_workspace_area,Qloose_right_edge_of_visible_workspace_area,loose_right_edge_of_visible_workspace_area,
						  6);
					    PUSH_SPECIAL_WITH_SYMBOL(Loose_top_edge_of_visible_workspace_area,Qloose_top_edge_of_visible_workspace_area,loose_top_edge_of_visible_workspace_area,
						    5);
					      PUSH_SPECIAL_WITH_SYMBOL(Loose_left_edge_of_visible_workspace_area,Qloose_left_edge_of_visible_workspace_area,loose_left_edge_of_visible_workspace_area,
						      4);
						PUSH_SPECIAL_WITH_SYMBOL(Current_image_plane,Qcurrent_image_plane,current_image_plane,
							3);
						  PUSH_SPECIAL_WITH_SYMBOL(Current_pane,Qcurrent_pane,current_pane,
							  2);
						    color_or_metacolor = 
							    ISVREF(image_plane,
							    (SI_Long)5L) ? 
							    ISVREF(ISVREF(image_plane,
							    (SI_Long)5L),
							    (SI_Long)21L) :
							     Nil;
						    if (color_or_metacolor);
						    else
							color_or_metacolor 
								= Qwhite;
						    if (EQ(color_or_metacolor,
							    Qtransparent) 
							    || 
							    EQ(color_or_metacolor,
							    Qbackground)) {
							temp = 
								ISVREF(Current_color_map,
								(SI_Long)5L);
							if (temp);
							else
							    temp = 
								    map_to_color_value_1(Qwhite);
							current_background_color_value 
								= temp;
						    }
						    else if (EQ(color_or_metacolor,
							    Qforeground) 
							    || 
							    EQ(color_or_metacolor,
							    Qworkspace_foreground)) 
								{
							temp = 
								ISVREF(image_plane,
								(SI_Long)5L) 
								? 
								ISVREF(ISVREF(image_plane,
								(SI_Long)5L),
								(SI_Long)22L) 
								: Nil;
							if (temp);
							else
							    temp = Qblack;
							color_or_metacolor 
								= temp;
							if (EQ(color_or_metacolor,
								Qtransparent) 
								|| 
								EQ(color_or_metacolor,
								Qbackground)) {
							    background_color_or_metacolor 
								    = 
								    ISVREF(image_plane,
								    (SI_Long)5L) 
								    ? 
								    ISVREF(ISVREF(image_plane,
								    (SI_Long)5L),
								    (SI_Long)21L) 
								    : Nil;
							    if (background_color_or_metacolor);
							    else
								background_color_or_metacolor 
									= 
									Qwhite;
							    if (EQ(background_color_or_metacolor,
								    Qforeground) 
								    || 
								    EQ(background_color_or_metacolor,
								    Qworkspace_foreground)) 
									{
								temp = 
									ISVREF(Current_color_map,
									(SI_Long)4L);
								if (temp);
								else
								    temp = 
									    map_to_color_value_1(Qblack);
								current_background_color_value 
									= temp;
							    }
							    else if (EQ(background_color_or_metacolor,
								    Qtransparent) 
								    || 
								    EQ(background_color_or_metacolor,
								    Qbackground)) 
									{
								temp = 
									ISVREF(Current_color_map,
									(SI_Long)5L);
								if (temp);
								else
								    temp = 
									    map_to_color_value_1(Qwhite);
								current_background_color_value 
									= temp;
							    }
							    else
								current_background_color_value 
									= 
									EQ(background_color_or_metacolor,
									ISVREF(Current_color_map,
									(SI_Long)6L)) 
									? 
									ISVREF(Current_color_map,
									(SI_Long)7L) 
									: 
									map_to_color_value_1(background_color_or_metacolor);
							}
							else if (EQ(color_or_metacolor,
								Qforeground) 
								|| 
								EQ(color_or_metacolor,
								Qworkspace_foreground)) 
								    {
							    temp = 
								    ISVREF(Current_color_map,
								    (SI_Long)4L);
							    if (temp);
							    else
								temp = 
									map_to_color_value_1(Qblack);
							    current_background_color_value 
								    = temp;
							}
							else
							    current_background_color_value 
								    = 
								    EQ(color_or_metacolor,
								    ISVREF(Current_color_map,
								    (SI_Long)6L)) 
								    ? 
								    ISVREF(Current_color_map,
								    (SI_Long)7L) 
								    : 
								    map_to_color_value_1(color_or_metacolor);
						    }
						    else
							current_background_color_value 
								= 
								EQ(color_or_metacolor,
								ISVREF(Current_color_map,
								(SI_Long)6L)) 
								? 
								ISVREF(Current_color_map,
								(SI_Long)7L) 
								: 
								map_to_color_value_1(color_or_metacolor);
						    PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
							    1);
						      if (SIMPLE_VECTOR_P(thing) 
							      && 
							      EQ(ISVREF(thing,
							      (SI_Long)0L),
							      Qg2_defstruct_structure_name_connection_g2_struct)) 
								  {
							  vertices = 
								  compute_connection_vertices(thing);
							  x_in_window = Nil;
							  y_in_window = Nil;
							  ab_loop_list_ = 
								  vertices;
							  if ( 
								  !TRUEP(ab_loop_list_))
							      goto end_loop;
							next_loop:
							  x_in_window = 
								  CAR(ab_loop_list_);
							  temp = 
								  CDR(ab_loop_list_);
							  y_in_window = 
								  CAR(temp);
							  region = 
								  add_rectangle_to_region(FIXNUM_MINUS(x_in_window,
								  d),
								  FIXNUM_MINUS(y_in_window,
								  d),
								  FIXNUM_ADD(x_in_window,
								  d),
								  FIXNUM_ADD(y_in_window,
								  d),region);
							  ab_loop_list_ = 
								  CDDR(ab_loop_list_);
							  if ( 
								  !TRUEP(ab_loop_list_))
							      goto end_loop;
							  goto next_loop;
							end_loop:;
							  reclaim_gensym_list_1(vertices);
						      }
						      else {
							  if (SIMPLE_VECTOR_P(thing) 
								  && 
								  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) 
								  > 
								  (SI_Long)2L 
								  &&  
								  !EQ(ISVREF(thing,
								  (SI_Long)1L),
								  Qavailable_frame_vector)) 
								      {
							      x2 = 
								      ISVREF(thing,
								      (SI_Long)1L);
							      temp_1 = 
								      SIMPLE_VECTOR_P(x2) 
								      && 
								      EQ(ISVREF(x2,
								      (SI_Long)0L),
								      Qg2_defstruct_structure_name_class_description_g2_struct) 
								      ? 
								      TRUEP(x2) 
								      : 
								      TRUEP(Qnil);
							  }
							  else
							      temp_1 = 
								      TRUEP(Nil);
							  if (temp_1) {
							      handles = 
								      selection_handle_positions(thing);
							      name = Nil;
							      x = Nil;
							      y = Nil;
							      ab_loop_list_ 
								      = 
								      handles;
							      x_in_window 
								      = Nil;
							      y_in_window 
								      = Nil;
							      if ( 
								      !TRUEP(ab_loop_list_))
								  goto end_loop_1;
							    next_loop_1:
							      name = 
								      CAR(ab_loop_list_);
							      temp = 
								      CDR(ab_loop_list_);
							      x = CAR(temp);
							      temp = 
								      CDR(ab_loop_list_);
							      temp = CDR(temp);
							      y = CAR(temp);
							      gensymed_symbol 
								      = 
								      IFIX(Current_x_origin_of_drawing);
							      if (IFIX(Current_image_x_scale) 
								      == 
								      (SI_Long)4096L)
								  gensymed_symbol_1 
									  = 
									  IFIX(x);
							      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
								      Current_image_x_scale) 
								      && 
								      FIXNUM_LT(Current_image_x_scale,
								      Isqrt_of_most_positive_fixnum) 
								      && 
								      FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
								      x) 
								      && 
								      FIXNUM_LT(x,
								      Isqrt_of_most_positive_fixnum)) 
									  {
								  unshifted_result 
									  = 
									  IFIX(FIXNUM_TIMES(Current_image_x_scale,
									  x)) 
									  + 
									  (SI_Long)2048L;
								  gensymed_symbol_1 
									  = 
									  unshifted_result 
									  >> 
									   
									  - 
									   
									  - 
									  (SI_Long)12L;
							      }
							      else
								  gensymed_symbol_1 
									  = 
									  IFIX(scalef_function(Current_image_x_scale,
									  x));
							      x_in_window 
								      = 
								      FIX(gensymed_symbol 
								      + 
								      gensymed_symbol_1);
							      gensymed_symbol 
								      = 
								      IFIX(Current_y_origin_of_drawing);
							      if (IFIX(Current_image_y_scale) 
								      == 
								      (SI_Long)4096L)
								  gensymed_symbol_1 
									  = 
									  IFIX(y);
							      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
								      Current_image_y_scale) 
								      && 
								      FIXNUM_LT(Current_image_y_scale,
								      Isqrt_of_most_positive_fixnum) 
								      && 
								      FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
								      y) 
								      && 
								      FIXNUM_LT(y,
								      Isqrt_of_most_positive_fixnum)) 
									  {
								  unshifted_result 
									  = 
									  IFIX(FIXNUM_TIMES(Current_image_y_scale,
									  y)) 
									  + 
									  (SI_Long)2048L;
								  gensymed_symbol_1 
									  = 
									  unshifted_result 
									  >> 
									   
									  - 
									   
									  - 
									  (SI_Long)12L;
							      }
							      else
								  gensymed_symbol_1 
									  = 
									  IFIX(scalef_function(Current_image_y_scale,
									  y));
							      y_in_window 
								      = 
								      FIX(gensymed_symbol 
								      + 
								      gensymed_symbol_1);
							      region = 
								      add_rectangle_to_region(FIXNUM_MINUS(x_in_window,
								      d),
								      FIXNUM_MINUS(y_in_window,
								      d),
								      FIXNUM_ADD(x_in_window,
								      d),
								      FIXNUM_ADD(y_in_window,
								      d),
								      region);
							      ab_loop_list_ 
								      = 
								      CDDDR(ab_loop_list_);
							      if ( 
								      !TRUEP(ab_loop_list_))
								  goto end_loop_1;
							      goto next_loop_1;
							    end_loop_1:;
							      reclaim_graphics_list_1(handles);
							  }
							  else if (text_cell_p(thing)) 
								      {
							      table_qm = 
								      get_table_for_cell(thing);
							      if (table_qm) {
								  result = get_table_cell_edges(table_qm,
									  thing);
								  MVS_4(result,
									  left,
									  top,
									  right,
									  bottom);
								  w = 
									  Selection_highlight_line_width;
								  gensymed_symbol 
									  = 
									  IFIX(Current_x_origin_of_drawing);
								  if (IFIX(Current_image_x_scale) 
									  == 
									  (SI_Long)4096L)
								      gensymed_symbol_1 
									      = 
									      IFIX(left);
								  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
									  Current_image_x_scale) 
									  && 
									  FIXNUM_LT(Current_image_x_scale,
									  Isqrt_of_most_positive_fixnum) 
									  && 
									  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
									  left) 
									  && 
									  FIXNUM_LT(left,
									  Isqrt_of_most_positive_fixnum)) 
									      {
								      unshifted_result 
									      = 
									      IFIX(FIXNUM_TIMES(Current_image_x_scale,
									      left)) 
									      + 
									      (SI_Long)2048L;
								      gensymed_symbol_1 
									      = 
									      unshifted_result 
									      >> 
									       
									      - 
									       
									      - 
									      (SI_Long)12L;
								  }
								  else
								      gensymed_symbol_1 
									      = 
									      IFIX(scalef_function(Current_image_x_scale,
									      left));
								  gensymed_symbol 
									  = 
									  gensymed_symbol 
									  + 
									  gensymed_symbol_1;
								  gensymed_symbol_1 
									  = 
									  IFIX(w);
								  temp_2 = 
									  FIX(gensymed_symbol 
									  - 
									  gensymed_symbol_1);
								  gensymed_symbol 
									  = 
									  IFIX(Current_y_origin_of_drawing);
								  if (IFIX(Current_image_y_scale) 
									  == 
									  (SI_Long)4096L)
								      gensymed_symbol_1 
									      = 
									      IFIX(top);
								  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
									  Current_image_y_scale) 
									  && 
									  FIXNUM_LT(Current_image_y_scale,
									  Isqrt_of_most_positive_fixnum) 
									  && 
									  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
									  top) 
									  && 
									  FIXNUM_LT(top,
									  Isqrt_of_most_positive_fixnum)) 
									      {
								      unshifted_result 
									      = 
									      IFIX(FIXNUM_TIMES(Current_image_y_scale,
									      top)) 
									      + 
									      (SI_Long)2048L;
								      gensymed_symbol_1 
									      = 
									      unshifted_result 
									      >> 
									       
									      - 
									       
									      - 
									      (SI_Long)12L;
								  }
								  else
								      gensymed_symbol_1 
									      = 
									      IFIX(scalef_function(Current_image_y_scale,
									      top));
								  gensymed_symbol 
									  = 
									  gensymed_symbol 
									  + 
									  gensymed_symbol_1;
								  gensymed_symbol_1 
									  = 
									  IFIX(w);
								  temp_3 = 
									  FIX(gensymed_symbol 
									  - 
									  gensymed_symbol_1);
								  gensymed_symbol 
									  = 
									  IFIX(Current_x_origin_of_drawing);
								  if (IFIX(Current_image_x_scale) 
									  == 
									  (SI_Long)4096L)
								      gensymed_symbol_1 
									      = 
									      IFIX(right);
								  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
									  Current_image_x_scale) 
									  && 
									  FIXNUM_LT(Current_image_x_scale,
									  Isqrt_of_most_positive_fixnum) 
									  && 
									  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
									  right) 
									  && 
									  FIXNUM_LT(right,
									  Isqrt_of_most_positive_fixnum)) 
									      {
								      unshifted_result 
									      = 
									      IFIX(FIXNUM_TIMES(Current_image_x_scale,
									      right)) 
									      + 
									      (SI_Long)2048L;
								      gensymed_symbol_1 
									      = 
									      unshifted_result 
									      >> 
									       
									      - 
									       
									      - 
									      (SI_Long)12L;
								  }
								  else
								      gensymed_symbol_1 
									      = 
									      IFIX(scalef_function(Current_image_x_scale,
									      right));
								  gensymed_symbol 
									  = 
									  gensymed_symbol 
									  + 
									  gensymed_symbol_1;
								  gensymed_symbol_1 
									  = 
									  IFIX(w);
								  temp = 
									  FIX(gensymed_symbol 
									  + 
									  gensymed_symbol_1);
								  gensymed_symbol 
									  = 
									  IFIX(Current_y_origin_of_drawing);
								  if (IFIX(Current_image_y_scale) 
									  == 
									  (SI_Long)4096L)
								      gensymed_symbol_1 
									      = 
									      IFIX(bottom);
								  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
									  Current_image_y_scale) 
									  && 
									  FIXNUM_LT(Current_image_y_scale,
									  Isqrt_of_most_positive_fixnum) 
									  && 
									  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
									  bottom) 
									  && 
									  FIXNUM_LT(bottom,
									  Isqrt_of_most_positive_fixnum)) 
									      {
								      unshifted_result 
									      = 
									      IFIX(FIXNUM_TIMES(Current_image_y_scale,
									      bottom)) 
									      + 
									      (SI_Long)2048L;
								      gensymed_symbol_1 
									      = 
									      unshifted_result 
									      >> 
									       
									      - 
									       
									      - 
									      (SI_Long)12L;
								  }
								  else
								      gensymed_symbol_1 
									      = 
									      IFIX(scalef_function(Current_image_y_scale,
									      bottom));
								  gensymed_symbol 
									  = 
									  gensymed_symbol 
									  + 
									  gensymed_symbol_1;
								  gensymed_symbol_1 
									  = 
									  IFIX(w);
								  region = 
									  add_rectangle_to_region(temp_2,
									  temp_3,
									  temp,
									  FIX(gensymed_symbol 
									  + 
									  gensymed_symbol_1),
									  region);
							      }
							  }
						      }
						      current_draw_paper_p 
							      = Nil;
						      PUSH_SPECIAL_WITH_SYMBOL(Current_draw_paper_p,Qcurrent_draw_paper_p,current_draw_paper_p,
							      0);
							invalidate_region_of_image_plane(image_plane,
								region);
						      POP_SPECIAL();
						      SAVE_VALUES(reclaim_region(region));
						    POP_SPECIAL();
						  POP_SPECIAL();
						POP_SPECIAL();
					      POP_SPECIAL();
					    POP_SPECIAL();
					  POP_SPECIAL();
					POP_SPECIAL();
				      POP_SPECIAL();
				  }
				  POP_UNWIND_PROTECT(0);
				  UNLOCK(For_image_plane);
				  CONTINUE_UNWINDING(0);
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
    POP_UNWIND_PROTECT(1);
    UNLOCK(On_window_without_drawing);
    CONTINUE_UNWINDING(1);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

Object The_type_description_of_drag_handle_state = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_drag_handle_states, Qchain_of_available_drag_handle_states);

DEFINE_VARIABLE_WITH_SYMBOL(Drag_handle_state_count, Qdrag_handle_state_count);

Object Chain_of_available_drag_handle_states_vector = UNBOUND;

/* DRAG-HANDLE-STATE-STRUCTURE-MEMORY-USAGE */
Object drag_handle_state_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(128,153);
    temp = Drag_handle_state_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)11L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-DRAG-HANDLE-STATE-COUNT */
Object outstanding_drag_handle_state_count()
{
    Object def_structure_drag_handle_state_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(128,154);
    gensymed_symbol = IFIX(Drag_handle_state_count);
    def_structure_drag_handle_state_variable = 
	    Chain_of_available_drag_handle_states;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_drag_handle_state_variable))
	goto end_loop;
    def_structure_drag_handle_state_variable = 
	    ISVREF(def_structure_drag_handle_state_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-DRAG-HANDLE-STATE-1 */
Object reclaim_drag_handle_state_1(drag_handle_state)
    Object drag_handle_state;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(128,155);
    inline_note_reclaim_cons(drag_handle_state,Nil);
    structure_being_reclaimed = drag_handle_state;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      release_mouse_pointers(ISVREF(drag_handle_state,(SI_Long)1L));
      SVREF(drag_handle_state,FIX((SI_Long)1L)) = Nil;
      reclaim_frame_serial_number(ISVREF(drag_handle_state,(SI_Long)2L));
      SVREF(drag_handle_state,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_drag_handle_states_vector,
	    IFIX(Current_thread_index));
    SVREF(drag_handle_state,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_drag_handle_states_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = drag_handle_state;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-DRAG-HANDLE-STATE */
Object reclaim_structure_for_drag_handle_state(drag_handle_state)
    Object drag_handle_state;
{
    x_note_fn_call(128,156);
    return reclaim_drag_handle_state_1(drag_handle_state);
}

static Object Qg2_defstruct_structure_name_drag_handle_state_g2_struct;  /* g2-defstruct-structure-name::drag-handle-state-g2-struct */

/* MAKE-PERMANENT-DRAG-HANDLE-STATE-STRUCTURE-INTERNAL */
Object make_permanent_drag_handle_state_structure_internal()
{
    Object def_structure_drag_handle_state_variable;
    Object defstruct_g2_drag_handle_state_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(128,157);
    def_structure_drag_handle_state_variable = Nil;
    atomic_incff_symval(Qdrag_handle_state_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_drag_handle_state_variable = Nil;
	gensymed_symbol = (SI_Long)11L;
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
	defstruct_g2_drag_handle_state_variable = the_array;
	SVREF(defstruct_g2_drag_handle_state_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_drag_handle_state_g2_struct;
	SVREF(defstruct_g2_drag_handle_state_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_drag_handle_state_variable,FIX((SI_Long)2L)) = Nil;
	def_structure_drag_handle_state_variable = 
		defstruct_g2_drag_handle_state_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_drag_handle_state_variable);
}

/* MAKE-DRAG-HANDLE-STATE-1 */
Object make_drag_handle_state_1()
{
    Object def_structure_drag_handle_state_variable, temp, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(128,158);
    def_structure_drag_handle_state_variable = 
	    ISVREF(Chain_of_available_drag_handle_states_vector,
	    IFIX(Current_thread_index));
    if (def_structure_drag_handle_state_variable) {
	temp = Chain_of_available_drag_handle_states_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_drag_handle_state_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_drag_handle_state_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_drag_handle_state_g2_struct;
    }
    else
	def_structure_drag_handle_state_variable = 
		make_permanent_drag_handle_state_structure_internal();
    inline_note_allocate_cons(def_structure_drag_handle_state_variable,Nil);
    SVREF(def_structure_drag_handle_state_variable,FIX((SI_Long)1L)) = Nil;
    temp = copy_of_current_frame_serial_number_function();
    SVREF(def_structure_drag_handle_state_variable,FIX((SI_Long)2L)) = temp;
    return VALUES_1(def_structure_drag_handle_state_variable);
}

static Object Qdrag_handle;        /* drag-handle */

/* ENTER-DRAG-HANDLE-CONTEXT-FUNCTION */
Object enter_drag_handle_context_function(target,type,handle,image_plane,
	    image_plane_serial_number,cursor,x_in_workspace,y_in_workspace)
    Object target, type, handle, image_plane, image_plane_serial_number;
    Object cursor, x_in_workspace, y_in_workspace;
{
    Object state_1;

    x_note_fn_call(128,159);
    state_1 = make_drag_handle_state_1();
    SVREF(state_1,FIX((SI_Long)3L)) = target;
    SVREF(state_1,FIX((SI_Long)4L)) = type;
    SVREF(state_1,FIX((SI_Long)5L)) = handle;
    SVREF(state_1,FIX((SI_Long)6L)) = image_plane;
    SVREF(state_1,FIX((SI_Long)7L)) = image_plane_serial_number;
    SVREF(state_1,FIX((SI_Long)8L)) = cursor;
    SVREF(state_1,FIX((SI_Long)9L)) = x_in_workspace;
    SVREF(state_1,FIX((SI_Long)10L)) = y_in_workspace;
    enter_context_in_current_workstation(3,Qdrag_handle,state_1,Qnil);
    return VALUES_1(state_1);
}

/* VALID-WORKSTATION-CONTEXT-P-FOR-DRAG-HANDLE-STATE */
Object valid_workstation_context_p_for_drag_handle_state(drag_handle_state)
    Object drag_handle_state;
{
    Object gensymed_symbol, gensymed_symbol_1, x, y, xa, ya;
    char temp;

    x_note_fn_call(128,160);
    gensymed_symbol = 
	    ISVREF(ISVREF(ISVREF(The_type_description_of_drag_handle_state,
	    (SI_Long)9L),(SI_Long)0L),(SI_Long)4L);
    gensymed_symbol_1 = drag_handle_state;
    if (inline_funcall_1(gensymed_symbol,gensymed_symbol_1)) {
	gensymed_symbol = ISVREF(car_or_atom(ISVREF(drag_handle_state,
		(SI_Long)3L)),(SI_Long)3L);
	x = car_or_atom(ISVREF(drag_handle_state,(SI_Long)3L));
	temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else {
	    x = gensymed_symbol;
	    y = ISVREF(drag_handle_state,(SI_Long)2L);
	    if (FIXNUMP(y))
		temp = FIXNUMP(x) ? FIXNUM_LT(y,x) : TRUEP(T);
	    else if (FIXNUMP(x))
		temp = TRUEP(Nil);
	    else {
		xa = M_CAR(y);
		ya = M_CAR(x);
		temp = FIXNUM_LT(xa,ya);
		if (temp);
		else
		    temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),M_CDR(x)) 
			    : TRUEP(Qnil);
	    }
	}
	return VALUES_1( !temp ? T : Nil);
    }
    else
	return VALUES_1(Nil);
}

/* CLEAN-UP-WORKSTATION-CONTEXT-FOR-DRAG-HANDLE-STATE */
Object clean_up_workstation_context_for_drag_handle_state(drag_handle_state)
    Object drag_handle_state;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(128,161);
    gensymed_symbol = 
	    ISVREF(ISVREF(ISVREF(The_type_description_of_drag_handle_state,
	    (SI_Long)9L),(SI_Long)0L),(SI_Long)1L);
    gensymed_symbol_1 = drag_handle_state;
    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    return clean_up_image_plane_cursor(ISVREF(drag_handle_state,
	    (SI_Long)6L),ISVREF(drag_handle_state,(SI_Long)8L),
	    ISVREF(drag_handle_state,(SI_Long)7L));
}

/* BEGIN-DRAGGING-SELECTION-HANDLE */
Object begin_dragging_selection_handle(image_plane,mouse_pointer,target,
	    handle_type,handle,x_in_workspace,y_in_workspace)
    Object image_plane, mouse_pointer, target, handle_type, handle;
    Object x_in_workspace, y_in_workspace;
{
    Object color, cursor, state_block;

    x_note_fn_call(128,162);
    color = ISVREF(image_plane,(SI_Long)5L) ? ISVREF(ISVREF(image_plane,
	    (SI_Long)5L),(SI_Long)22L) : Nil;
    if (color);
    else
	color = Qblack;
    cursor = EQ(handle_type,Qresize) ? create_resize_cursor(color,handle,
	    target) : Nil;
    state_block = enter_drag_handle_context_function(target,handle_type,
	    handle,image_plane,ISVREF(image_plane,(SI_Long)1L),cursor,
	    x_in_workspace,y_in_workspace);
    if (cursor) {
	add_image_plane_cursor(image_plane,cursor);
	draw_image_plane_cursor(image_plane,cursor);
    }
    return add_mouse_pointer_to_guardians_of_workstation_context(mouse_pointer,
	    state_block);
}

/* TRACK-MOUSE-FOR-DRAG-HANDLE */
Object track_mouse_for_drag_handle(mouse_pointer)
    Object mouse_pointer;
{
    Object state_1, x_in_window, y_in_window, item_or_items, item, handle;
    Object handle_type, cursor, image_plane, x_in_workspace, y_in_workspace;
    Object dx, dy;

    x_note_fn_call(128,163);
    state_1 = workstation_context_specifics_blackboard_function(mouse_pointer);
    x_in_window = x_in_window_blackboard_function(mouse_pointer);
    y_in_window = y_in_window_blackboard_function(mouse_pointer);
    if (state_1 && x_in_window && y_in_window) {
	item_or_items = ISVREF(state_1,(SI_Long)3L);
	item = car_or_atom(item_or_items);
	handle = ISVREF(state_1,(SI_Long)5L);
	handle_type = ISVREF(state_1,(SI_Long)4L);
	cursor = ISVREF(state_1,(SI_Long)8L);
	image_plane = ISVREF(state_1,(SI_Long)6L);
	x_in_workspace = x_within_workspace(2,x_in_window,image_plane);
	y_in_workspace = y_within_workspace(2,y_in_window,image_plane);
	dx = FIXNUM_MINUS(x_in_workspace,ISVREF(state_1,(SI_Long)9L));
	dy = FIXNUM_MINUS(y_in_workspace,ISVREF(state_1,(SI_Long)10L));
	if ( !(FIXNUM_EQ(dx,dy) && IFIX(dy) == (SI_Long)0L)) {
	    if (EQ(handle_type,Qvertex)) {
		move_connection_vertex_by(item,handle,dx,dy);
		SVREF(state_1,FIX((SI_Long)9L)) = x_in_workspace;
		return VALUES_1(SVREF(state_1,FIX((SI_Long)10L)) = 
			y_in_workspace);
	    }
	    else if (EQ(handle_type,Qresize))
		return move_resize_cursor(cursor,item,handle,image_plane,
			dx,dy);
	    else
		return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* FINISH-DRAG-HANDLE */
Object finish_drag_handle(mouse_pointer)
    Object mouse_pointer;
{
    Object state_1, mouse_pointer_1, temp;

    x_note_fn_call(128,164);
    state_1 = workstation_context_specifics_blackboard_function(mouse_pointer);
    mouse_pointer_1 = mouse_pointer_blackboard_function(mouse_pointer);
    if (state_1 && mouse_pointer_1) {
	track_mouse_for_drag_handle(mouse_pointer_1);
	temp = ISVREF(state_1,(SI_Long)4L);
	if (EQ(temp,Qvertex));
	else if (EQ(temp,Qresize))
	    resize_items_per_resize_cursor(ISVREF(state_1,(SI_Long)8L),
		    ISVREF(state_1,(SI_Long)5L),ISVREF(state_1,
		    (SI_Long)3L),ISVREF(state_1,(SI_Long)2L));
	return return_from_current_workstation_context(1,Qdrag_handle);
    }
    else
	return VALUES_1(Nil);
}

static Object Qfloat_array;        /* float-array */

/* CREATE-RESIZE-CURSOR */
Object create_resize_cursor(color,corner_being_moved,blocks)
    Object color, corner_being_moved, blocks;
{
    Object block, ab_loop_list_, left, top, right, bottom, x, y, width, height;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, gensymed_symbol, rects;
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float, resize_cursor_x_scale, resize_cursor_y_scale;
    Object resize_cursor_color, resize_cursor_rects;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(128,165);
    block = Nil;
    ab_loop_list_ = blocks;
    left = Nil;
    top = Nil;
    right = Nil;
    bottom = Nil;
    x = Nil;
    y = Nil;
    width = Nil;
    height = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    block = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    left = gensymed_symbol;
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    top = gensymed_symbol;
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    right = gensymed_symbol;
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    bottom = gensymed_symbol;
    x = left;
    y = top;
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    width = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    height = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    if (EQ(corner_being_moved,Qtop_left)) {
	x = right;
	y = bottom;
	width = FIXNUM_NEGATE(width);
	height = FIXNUM_NEGATE(height);
    }
    else if (EQ(corner_being_moved,Qtop_right)) {
	y = bottom;
	height = FIXNUM_NEGATE(height);
    }
    else if (EQ(corner_being_moved,Qbottom_left)) {
	x = right;
	width = FIXNUM_NEGATE(width);
    }
    ab_loopvar__2 = graphics_cons_1(graphics_list_4(x,y,width,height),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    rects = ab_loopvar_;
    goto end_1;
    rects = Qnil;
  end_1:;
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
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,1.0);
    resize_cursor_x_scale = new_float;
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
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,1.0);
    resize_cursor_y_scale = new_float;
    resize_cursor_color = color;
    resize_cursor_rects = rects;
    return graphics_cons_1(resize_cursor_x_scale,
	    graphics_cons_1(resize_cursor_y_scale,
	    graphics_cons_1(resize_cursor_color,resize_cursor_rects)));
}

/* RESIZE-CURSOR-P */
Object resize_cursor_p(cursor)
    Object cursor;
{
    Object thing;
    char temp;

    x_note_fn_call(128,166);
    if (CONSP(cursor)) {
	thing = M_CAR(cursor);
	temp = INLINE_DOUBLE_FLOAT_VECTOR_P(thing) != (SI_Long)0L ? 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) == (SI_Long)1L : 
		TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	thing = M_CAR(M_CDR(cursor));
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(thing) != (SI_Long)0L)
	    return VALUES_1(IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) == 
		    (SI_Long)1L ? T : Nil);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* RECLAIM-RESIZE-CURSOR */
Object reclaim_resize_cursor(cursor)
    Object cursor;
{
    Object managed_float, rect, ab_loop_list_;

    x_note_fn_call(128,167);
    managed_float = M_CAR(cursor);
    reclaim_managed_simple_float_array_of_length_1(managed_float);
    managed_float = M_CAR(M_CDR(cursor));
    reclaim_managed_simple_float_array_of_length_1(managed_float);
    rect = Nil;
    ab_loop_list_ = CDDDR(cursor);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    rect = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_graphics_list_1(rect);
    goto next_loop;
  end_loop:;
    return reclaim_graphics_list_1(cursor);
}

static Object float_constant;      /* 0.0 */

/* DRAW-RESIZE-CURSOR */
Object draw_resize_cursor(cursor)
    Object cursor;
{
    Object color_or_metacolor, color_value, x0, y0_1, width, height;
    Object ab_loop_list_, x1, y1_1, ab_loop_desetq_, temp;
    SI_Long temp_1;
    double x_scale, y_scale, temp_2;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(128,168);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	x_scale = DFLOAT_ISAREF_1(M_CAR(cursor),(SI_Long)0L);
	y_scale = DFLOAT_ISAREF_1(M_CAR(M_CDR(cursor)),(SI_Long)0L);
	color_or_metacolor = M_CAR(CDDR(cursor));
	if (EQ(color_or_metacolor,Qbackground))
	    color_value = Current_background_color_value;
	else if (EQ(color_or_metacolor,Qforeground) || 
		EQ(color_or_metacolor,Qworkspace_foreground))
	    color_value = Current_foreground_color_value;
	else if (EQ(color_or_metacolor,Qtransparent))
	    color_value = Current_background_color_value;
	else
	    color_value = map_to_color_value(color_or_metacolor);
	x0 = Nil;
	y0_1 = Nil;
	width = Nil;
	height = Nil;
	ab_loop_list_ = CDDDR(cursor);
	x1 = Nil;
	y1_1 = Nil;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	x0 = CAR(ab_loop_desetq_);
	temp = CDR(ab_loop_desetq_);
	y0_1 = CAR(temp);
	temp = CDR(ab_loop_desetq_);
	temp = CDR(temp);
	width = CAR(temp);
	temp = CDR(ab_loop_desetq_);
	temp = CDR(temp);
	temp = CDR(temp);
	height = CAR(temp);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp_1 = IFIX(x0);
	temp = lfloat(width,float_constant);
	temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	x1 = FIX(temp_1 + inline_floor_1(0.5 + x_scale * temp_2));
	temp_1 = IFIX(y0_1);
	temp = lfloat(height,float_constant);
	temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	y1_1 = FIX(temp_1 + inline_floor_1(0.5 + y_scale * temp_2));
	draw_dotted_rectangle(color_value,x0,y0_1,x1,y1_1);
	goto next_loop;
      end_loop:
	result = VALUES_1(Qnil);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* MOVE-RESIZE-CURSOR */
Object move_resize_cursor(cursor,item,handle,image_plane,dx,dy)
    Object cursor, item, handle, image_plane, dx, dy;
{
    Object gensymed_symbol, left, top, right, bottom, gensym_window;
    Object gensymed_symbol_1, left_edge_of_draw_area, top_edge_of_draw_area;
    Object right_edge_of_draw_area, bottom_edge_of_draw_area;
    Object current_image_x_scale, current_image_y_scale;
    Object current_x_origin_of_drawing, current_y_origin_of_drawing;
    Object current_window_1, drawing_on_window, current_drawing_transfer_mode;
    Object type_of_current_window, current_native_window_qm, current_color_map;
    Object temp_1, current_background_color_value;
    Object current_foreground_color_value, defer_notifications_qm;
    Object current_pane, current_image_plane;
    Object loose_left_edge_of_visible_workspace_area;
    Object loose_top_edge_of_visible_workspace_area;
    Object loose_right_edge_of_visible_workspace_area;
    Object loose_bottom_edge_of_visible_workspace_area, color_or_metacolor;
    Object background_color_or_metacolor, outer_native_image_plane;
    Object current_native_image_plane, color_value, old_color_value;
    Object current_frame_transform_qm, aref_arg_1, icp_output_port_qm;
    Object icp_socket_qm, i_am_alive_info_qm, icp_output_port_qm_1;
    Object current_icp_port, current_icp_socket, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;
    char already_in_synch, temp_2;
    double temp, gensymed_symbol_4, x_scale, y_scale, gensymed_symbol_5;
    double gensymed_symbol_6, gensymed_symbol_7, gensymed_symbol_8;
    double aref_new_value;
    Declare_stack_pointer;
    Declare_catch(3);
    Declare_special(54);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(128,169);
    SAVE_STACK();
    gensymed_symbol = ISVREF(item,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    left = gensymed_symbol;
    gensymed_symbol = ISVREF(item,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    top = gensymed_symbol;
    gensymed_symbol = ISVREF(item,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    right = gensymed_symbol;
    gensymed_symbol = ISVREF(item,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    bottom = gensymed_symbol;
    gensym_window = ISVREF(ISVREF(image_plane,(SI_Long)2L),(SI_Long)2L);
    result = adjust_rectangle_edges(handle,left,top,right,bottom,dx,dy);
    MVS_4(result,left,top,right,bottom);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	gensymed_symbol = float_constant;
	temp = (double)IFIX(FIXNUM_MINUS(right,left));
	gensymed_symbol_1 = ISVREF(item,(SI_Long)14L);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol_1);
	gensymed_symbol_1 = ISVREF(item,(SI_Long)14L);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol_1);
	gensymed_symbol_4 = temp / (double)(gensymed_symbol_2 - 
		gensymed_symbol_3);
	temp = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol);
	x_scale = MAX(temp,gensymed_symbol_4);
	gensymed_symbol = float_constant;
	temp = (double)IFIX(FIXNUM_MINUS(bottom,top));
	gensymed_symbol_1 = ISVREF(item,(SI_Long)14L);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol_1);
	gensymed_symbol_1 = ISVREF(item,(SI_Long)14L);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol_1);
	gensymed_symbol_4 = temp / (double)(gensymed_symbol_2 - 
		gensymed_symbol_3);
	temp = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol);
	y_scale = MAX(temp,gensymed_symbol_4);
	left_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)7L);
	top_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)8L);
	right_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)9L);
	bottom_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)10L);
	PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
		53);
	  PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
		  52);
	    PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
		    51);
	      PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
		      50);
		current_image_x_scale = FIX((SI_Long)4096L);
		current_image_y_scale = FIX((SI_Long)4096L);
		current_x_origin_of_drawing = FIX((SI_Long)0L);
		current_y_origin_of_drawing = FIX((SI_Long)0L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
			49);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
			  48);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
			    47);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
			      46);
			LOCK(On_window_without_drawing);
			if (PUSH_UNWIND_PROTECT(2)) {
			    current_window_1 = ISVREF(ISVREF(image_plane,
				    (SI_Long)2L),(SI_Long)2L);
			    PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
				    45);
			      drawing_on_window = Nil;
			      PUSH_SPECIAL_WITH_SYMBOL(Drawing_on_window,Qdrawing_on_window,drawing_on_window,
				      44);
				current_drawing_transfer_mode = 
					EQ(Current_drawing_transfer_mode,
					Kxor) ? 
					Current_drawing_transfer_mode : 
					ISVREF(Current_window,(SI_Long)30L);
				PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
					43);
				  type_of_current_window = 
					  ISVREF(Current_window,(SI_Long)1L);
				  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
					  42);
				    current_native_window_qm = 
					    ISVREF(Current_window,
					    (SI_Long)17L);
				    PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
					    41);
				      current_color_map = 
					      ISVREF(Current_window,
					      (SI_Long)20L);
				      PUSH_SPECIAL_WITH_SYMBOL(Current_color_map,Qcurrent_color_map,current_color_map,
					      40);
					temp_1 = ISVREF(Current_color_map,
						(SI_Long)5L);
					if (temp_1);
					else
					    temp_1 = 
						    map_to_color_value_1(Qwhite);
					current_background_color_value = 
						temp_1;
					PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
						39);
					  temp_1 = 
						  ISVREF(Current_color_map,
						  (SI_Long)4L);
					  if (temp_1);
					  else
					      temp_1 = 
						      map_to_color_value_1(Qblack);
					  current_foreground_color_value = 
						  temp_1;
					  PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
						  38);
					    defer_notifications_qm = T;
					    PUSH_SPECIAL_WITH_SYMBOL(Defer_notifications_qm,Qdefer_notifications_qm,defer_notifications_qm,
						    37);
					      LOCK(On_window_with_drawing);
					      if (PUSH_UNWIND_PROTECT(1)) {
						  drawing_on_window = T;
						  PUSH_SPECIAL_WITH_SYMBOL(Drawing_on_window,Qdrawing_on_window,drawing_on_window,
							  36);
						    if (EQ(Type_of_current_window,
							    Qx11_window)) {
							LOCK(For_image_plane);
							if (PUSH_UNWIND_PROTECT(0)) 
								    {
							    current_pane = 
								    ISVREF(image_plane,
								    (SI_Long)2L);
							    current_image_plane 
								    = 
								    image_plane;
							    loose_left_edge_of_visible_workspace_area 
								    = 
								    ISVREF(image_plane,
								    (SI_Long)23L);
							    loose_top_edge_of_visible_workspace_area 
								    = 
								    ISVREF(image_plane,
								    (SI_Long)24L);
							    loose_right_edge_of_visible_workspace_area 
								    = 
								    ISVREF(image_plane,
								    (SI_Long)25L);
							    loose_bottom_edge_of_visible_workspace_area 
								    = 
								    ISVREF(image_plane,
								    (SI_Long)26L);
							    color_or_metacolor 
								    = 
								    ISVREF(image_plane,
								    (SI_Long)5L) 
								    ? 
								    ISVREF(ISVREF(image_plane,
								    (SI_Long)5L),
								    (SI_Long)22L) 
								    : Nil;
							    if (color_or_metacolor);
							    else
								color_or_metacolor 
									= 
									Qblack;
							    if (EQ(color_or_metacolor,
								    Qtransparent) 
								    || 
								    EQ(color_or_metacolor,
								    Qbackground)) 
									{
								background_color_or_metacolor 
									= 
									ISVREF(image_plane,
									(SI_Long)5L) 
									? 
									ISVREF(ISVREF(image_plane,
									(SI_Long)5L),
									(SI_Long)21L) 
									: Nil;
								if (background_color_or_metacolor);
								else
								    background_color_or_metacolor 
									    = 
									    Qwhite;
								if (EQ(background_color_or_metacolor,
									Qforeground) 
									|| 
									EQ(background_color_or_metacolor,
									Qworkspace_foreground)) 
									    {
								    temp_1 
									    = 
									    ISVREF(Current_color_map,
									    (SI_Long)4L);
								    if (temp_1);
								    else
									temp_1 
										= 
										map_to_color_value_1(Qblack);
								    current_foreground_color_value 
									    = 
									    temp_1;
								}
								else if (EQ(background_color_or_metacolor,
									Qtransparent) 
									|| 
									EQ(background_color_or_metacolor,
									Qbackground)) 
									    {
								    temp_1 
									    = 
									    ISVREF(Current_color_map,
									    (SI_Long)5L);
								    if (temp_1);
								    else
									temp_1 
										= 
										map_to_color_value_1(Qwhite);
								    current_foreground_color_value 
									    = 
									    temp_1;
								}
								else
								    current_foreground_color_value 
									    = 
									    EQ(background_color_or_metacolor,
									    ISVREF(Current_color_map,
									    (SI_Long)6L)) 
									    ?
									     
									    ISVREF(Current_color_map,
									    (SI_Long)7L) 
									    :
									     
									    map_to_color_value_1(background_color_or_metacolor);
							    }
							    else if (EQ(color_or_metacolor,
								    Qforeground) 
								    || 
								    EQ(color_or_metacolor,
								    Qworkspace_foreground)) 
									{
								temp_1 = 
									ISVREF(Current_color_map,
									(SI_Long)4L);
								if (temp_1);
								else
								    temp_1 
									    = 
									    map_to_color_value_1(Qblack);
								current_foreground_color_value 
									= 
									temp_1;
							    }
							    else
								current_foreground_color_value 
									= 
									EQ(color_or_metacolor,
									ISVREF(Current_color_map,
									(SI_Long)6L)) 
									? 
									ISVREF(Current_color_map,
									(SI_Long)7L) 
									: 
									map_to_color_value_1(color_or_metacolor);
							    PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
								    23);
							      PUSH_SPECIAL_WITH_SYMBOL(Loose_bottom_edge_of_visible_workspace_area,Qloose_bottom_edge_of_visible_workspace_area,loose_bottom_edge_of_visible_workspace_area,
								      22);
								PUSH_SPECIAL_WITH_SYMBOL(Loose_right_edge_of_visible_workspace_area,Qloose_right_edge_of_visible_workspace_area,loose_right_edge_of_visible_workspace_area,
									21);
								  PUSH_SPECIAL_WITH_SYMBOL(Loose_top_edge_of_visible_workspace_area,Qloose_top_edge_of_visible_workspace_area,loose_top_edge_of_visible_workspace_area,
									  20);
								    PUSH_SPECIAL_WITH_SYMBOL(Loose_left_edge_of_visible_workspace_area,Qloose_left_edge_of_visible_workspace_area,loose_left_edge_of_visible_workspace_area,
									    19);
								      PUSH_SPECIAL_WITH_SYMBOL(Current_image_plane,Qcurrent_image_plane,current_image_plane,
									      18);
									PUSH_SPECIAL_WITH_SYMBOL(Current_pane,Qcurrent_pane,current_pane,
										17);
									  outer_native_image_plane 
										  = 
										  Current_native_image_plane;
									  PUSH_SPECIAL_WITH_SYMBOL(Outer_native_image_plane,Qouter_native_image_plane,outer_native_image_plane,
										  16);
									    current_native_image_plane 
										    = 
										    image_plane;
									    PUSH_SPECIAL_WITH_SYMBOL(Current_native_image_plane,Qcurrent_native_image_plane,current_native_image_plane,
										    15);
									      if ( 
										      !EQ(Outer_native_image_plane,
										      Current_native_image_plane))
										  nip_begin_drawing(Current_native_image_plane);
									      color_or_metacolor 
										      = 
										      ISVREF(image_plane,
										      (SI_Long)5L) 
										      ?
										       
										      ISVREF(ISVREF(image_plane,
										      (SI_Long)5L),
										      (SI_Long)21L) 
										      :
										       
										      Nil;
									      if (color_or_metacolor);
									      else
										  color_or_metacolor 
											  = 
											  Qwhite;
									      if (EQ(color_or_metacolor,
										      Qtransparent) 
										      || 
										      EQ(color_or_metacolor,
										      Qbackground)) 
											  {
										  color_value 
											  = 
											  ISVREF(Current_color_map,
											  (SI_Long)5L);
										  if (color_value);
										  else
										      color_value 
											      = 
											      map_to_color_value_1(Qwhite);
									      }
									      else if (EQ(color_or_metacolor,
										      Qforeground) 
										      || 
										      EQ(color_or_metacolor,
										      Qworkspace_foreground)) 
											  {
										  temp_1 
											  = 
											  ISVREF(image_plane,
											  (SI_Long)5L) 
											  ?
											   
											  ISVREF(ISVREF(image_plane,
											  (SI_Long)5L),
											  (SI_Long)22L) 
											  :
											   
											  Nil;
										  if (temp_1);
										  else
										      temp_1 
											      = 
											      Qblack;
										  color_or_metacolor 
											  = 
											  temp_1;
										  if (EQ(color_or_metacolor,
											  Qtransparent) 
											  || 
											  EQ(color_or_metacolor,
											  Qbackground)) 
											      {
										      background_color_or_metacolor 
											      = 
											      ISVREF(image_plane,
											      (SI_Long)5L) 
											      ?
											       
											      ISVREF(ISVREF(image_plane,
											      (SI_Long)5L),
											      (SI_Long)21L) 
											      :
											       
											      Nil;
										      if (background_color_or_metacolor);
										      else
											  background_color_or_metacolor 
												  = 
												  Qwhite;
										      if (EQ(background_color_or_metacolor,
											      Qforeground) 
											      || 
											      EQ(background_color_or_metacolor,
											      Qworkspace_foreground)) 
												  {
											  color_value 
												  = 
												  ISVREF(Current_color_map,
												  (SI_Long)4L);
											  if (color_value);
											  else
											      color_value 
												      = 
												      map_to_color_value_1(Qblack);
										      }
										      else if (EQ(background_color_or_metacolor,
											      Qtransparent) 
											      || 
											      EQ(background_color_or_metacolor,
											      Qbackground)) 
												  {
											  color_value 
												  = 
												  ISVREF(Current_color_map,
												  (SI_Long)5L);
											  if (color_value);
											  else
											      color_value 
												      = 
												      map_to_color_value_1(Qwhite);
										      }
										      else
											  color_value 
												  = 
												  EQ(background_color_or_metacolor,
												  ISVREF(Current_color_map,
												  (SI_Long)6L)) 
												  ?
												   
												  ISVREF(Current_color_map,
												  (SI_Long)7L) 
												  :
												   
												  map_to_color_value_1(background_color_or_metacolor);
										  }
										  else if (EQ(color_or_metacolor,
											  Qforeground) 
											  || 
											  EQ(color_or_metacolor,
											  Qworkspace_foreground)) 
											      {
										      color_value 
											      = 
											      ISVREF(Current_color_map,
											      (SI_Long)4L);
										      if (color_value);
										      else
											  color_value 
												  = 
												  map_to_color_value_1(Qblack);
										  }
										  else
										      color_value 
											      = 
											      EQ(color_or_metacolor,
											      ISVREF(Current_color_map,
											      (SI_Long)6L)) 
											      ?
											       
											      ISVREF(Current_color_map,
											      (SI_Long)7L) 
											      :
											       
											      map_to_color_value_1(color_or_metacolor);
									      }
									      else
										  color_value 
											  = 
											  EQ(color_or_metacolor,
											  ISVREF(Current_color_map,
											  (SI_Long)6L)) 
											  ?
											   
											  ISVREF(Current_color_map,
											  (SI_Long)7L) 
											  :
											   
											  map_to_color_value_1(color_or_metacolor);
									      old_color_value 
										      = 
										      Current_background_color_value;
									      current_background_color_value 
										      = 
										      Current_background_color_value;
									      PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
										      14);
										set_current_background_color_value(color_value);
										left_edge_of_draw_area 
											= 
											Left_edge_of_draw_area;
										top_edge_of_draw_area 
											= 
											Top_edge_of_draw_area;
										right_edge_of_draw_area 
											= 
											Right_edge_of_draw_area;
										bottom_edge_of_draw_area 
											= 
											Bottom_edge_of_draw_area;
										PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
											13);
										  PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
											  12);
										    PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
											    11);
										      PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
											      10);
											temp_1 
												= 
												ISVREF(image_plane,
												(SI_Long)6L);
											Left_edge_of_draw_area 
												= 
												FIXNUM_MAX(temp_1,
												Left_edge_of_draw_area);
											temp_1 
												= 
												ISVREF(image_plane,
												(SI_Long)7L);
											Top_edge_of_draw_area 
												= 
												FIXNUM_MAX(temp_1,
												Top_edge_of_draw_area);
											temp_1 
												= 
												ISVREF(image_plane,
												(SI_Long)8L);
											Right_edge_of_draw_area 
												= 
												FIXNUM_MIN(temp_1,
												Right_edge_of_draw_area);
											temp_1 
												= 
												ISVREF(image_plane,
												(SI_Long)9L);
											Bottom_edge_of_draw_area 
												= 
												FIXNUM_MIN(temp_1,
												Bottom_edge_of_draw_area);
											if (FIXNUM_LT(Left_edge_of_draw_area,
												Right_edge_of_draw_area) 
												&& 
												FIXNUM_LT(Top_edge_of_draw_area,
												Bottom_edge_of_draw_area)) 
												    {
											    left_edge_of_draw_area 
												    = 
												    Left_edge_of_draw_area;
											    top_edge_of_draw_area 
												    = 
												    Top_edge_of_draw_area;
											    right_edge_of_draw_area 
												    = 
												    Right_edge_of_draw_area;
											    bottom_edge_of_draw_area 
												    = 
												    Bottom_edge_of_draw_area;
											    PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
												    9);
											      PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
												      8);
												PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
													7);
												  PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
													  6);
												    temp_1 
													    = 
													    ISVREF(image_plane,
													    (SI_Long)19L);
												    Left_edge_of_draw_area 
													    = 
													    FIXNUM_MAX(temp_1,
													    Left_edge_of_draw_area);
												    temp_1 
													    = 
													    ISVREF(image_plane,
													    (SI_Long)20L);
												    Top_edge_of_draw_area 
													    = 
													    FIXNUM_MAX(temp_1,
													    Top_edge_of_draw_area);
												    temp_1 
													    = 
													    ISVREF(image_plane,
													    (SI_Long)21L);
												    Right_edge_of_draw_area 
													    = 
													    FIXNUM_MIN(temp_1,
													    Right_edge_of_draw_area);
												    temp_1 
													    = 
													    ISVREF(image_plane,
													    (SI_Long)22L);
												    Bottom_edge_of_draw_area 
													    = 
													    FIXNUM_MIN(temp_1,
													    Bottom_edge_of_draw_area);
												    if (FIXNUM_LT(Left_edge_of_draw_area,
													    Right_edge_of_draw_area) 
													    && 
													    FIXNUM_LT(Top_edge_of_draw_area,
													    Bottom_edge_of_draw_area)) 
														{
													current_frame_transform_qm 
														= 
														Nil;
													current_image_x_scale 
														= 
														ISVREF(image_plane,
														(SI_Long)11L);
													current_image_y_scale 
														= 
														ISVREF(image_plane,
														(SI_Long)12L);
													current_x_origin_of_drawing 
														= 
														ISVREF(image_plane,
														(SI_Long)13L);
													current_y_origin_of_drawing 
														= 
														ISVREF(image_plane,
														(SI_Long)14L);
													PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
														5);
													  PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
														  4);
													    PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
														    3);
													      PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
														      2);
														PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
															1);
														  already_in_synch 
															  = 
															  EQ(Current_drawing_transfer_mode,
															  Kxor);
														  current_drawing_transfer_mode 
															  = 
															  Current_drawing_transfer_mode;
														  PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
															  0);
														    if ( 
															    !already_in_synch) 
																{
															Current_drawing_transfer_mode 
																= 
																Kxor;
															synchronize_transfer_mode();
														    }
														    draw_resize_cursor(cursor);
														    aref_arg_1 
															    = 
															    M_CAR(cursor);
														    DFLOAT_ISASET_1(aref_arg_1,
															    (SI_Long)0L,
															    x_scale);
														    aref_arg_1 
															    = 
															    M_CAR(M_CDR(cursor));
														    DFLOAT_ISASET_1(aref_arg_1,
															    (SI_Long)0L,
															    y_scale);
														    draw_resize_cursor(cursor);
														  POP_SPECIAL();
														  if ( 
															  !already_in_synch)
														      synchronize_transfer_mode();
														POP_SPECIAL();
													      POP_SPECIAL();
													    POP_SPECIAL();
													  POP_SPECIAL();
													POP_SPECIAL();
												    }
												  POP_SPECIAL();
												POP_SPECIAL();
											      POP_SPECIAL();
											    POP_SPECIAL();
											}
										      POP_SPECIAL();
										    POP_SPECIAL();
										  POP_SPECIAL();
										POP_SPECIAL();
										set_current_background_color_value(old_color_value);
									      POP_SPECIAL();
									      if ( 
										      !EQ(Outer_native_image_plane,
										      Current_native_image_plane))
										  nip_end_drawing(Current_native_image_plane);
									    POP_SPECIAL();
									    temp_1 
										    = 
										    Current_native_image_plane 
										    ?
										     
										    ( 
										    !EQ(image_plane,
										    Current_native_image_plane) 
										    ?
										     
										    nip_begin_drawing(Current_native_image_plane) 
										    :
										     
										    Nil) 
										    :
										     
										    Nil;
									  POP_SPECIAL();
									POP_SPECIAL();
								      POP_SPECIAL();
								    POP_SPECIAL();
								  POP_SPECIAL();
								POP_SPECIAL();
							      POP_SPECIAL();
							    POP_SPECIAL();
							    SAVE_VALUES(VALUES_1(temp_1));
							}
							POP_UNWIND_PROTECT(0);
							UNLOCK(For_image_plane);
							CONTINUE_UNWINDING(0);
							result = RESTORE_VALUES();
							SAVE_VALUES(VALUES_1(result));
							if (Flush_graphics_immediately_qm)
							    sync_graphics_on_current_window();
						    }
						    else if (EQ(Type_of_current_window,
							    Qicp)) {
							icp_output_port_qm 
								= 
								ISVREF(Current_window,
								(SI_Long)12L);
							icp_socket_qm = 
								icp_output_port_qm 
								? 
								ISVREF(icp_output_port_qm,
								(SI_Long)2L) 
								: Qnil;
							if (icp_socket_qm) {
							    i_am_alive_info_qm 
								    = 
								    ISVREF(icp_socket_qm,
								    (SI_Long)24L);
							    temp_2 =  
								    !TRUEP(i_am_alive_info_qm);
							    if (temp_2);
							    else
								temp_2 =  
									!TRUEP(Do_icp_flow_control_qm);
							    if (temp_2);
							    else
								temp_2 =  
									!TRUEP(ISVREF(i_am_alive_info_qm,
									(SI_Long)2L));
							}
							else
							    temp_2 = 
								    TRUEP(Nil);
							if (temp_2) {
							    icp_output_port_qm_1 
								    = 
								    ISVREF(Current_window,
								    (SI_Long)12L);
							    if (icp_output_port_qm_1 
								    && 
								    icp_connection_open_p(ISVREF(icp_output_port_qm_1,
								    (SI_Long)2L))) 
									{
								current_icp_port 
									= 
									icp_output_port_qm_1;
								PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
									35);
								  current_icp_socket 
									  = 
									  ISVREF(Current_icp_port,
									  (SI_Long)2L);
								  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
									  34);
								    temp_1 
									    = 
									    IFIX(ISVREF(Current_icp_socket,
									    (SI_Long)22L)) 
									    >= 
									    (SI_Long)17L 
									    ?
									     
									    ISVREF(Current_icp_socket,
									    (SI_Long)53L) 
									    :
									     
									    Nil;
								    if (temp_1);
								    else
									temp_1 
										= 
										EQ(ISVREF(Current_icp_socket,
										(SI_Long)25L),
										Qtelewindows) 
										?
										 T : Nil;
								    disable_resumability 
									    = 
									    temp_1;
								    PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
									    33);
								      number_of_icp_bytes_for_message_series 
									      = 
									      FIX((SI_Long)0L);
								      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
									      32);
									icp_buffers_for_message_group 
										= 
										Nil;
									PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
										31);
									  icp_buffer_of_start_of_message_series_qm 
										  = 
										  Nil;
									  PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
										  30);
									    icp_byte_position_of_start_of_message_series_qm 
										    = 
										    Nil;
									    PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
										    29);
									      number_of_icp_bytes_to_fill_buffer 
										      = 
										      FIX((SI_Long)0L);
									      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
										      28);
										current_icp_buffer 
											= 
											Nil;
										PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
											27);
										  current_write_icp_byte_position 
											  = 
											  Nil;
										  PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
											  26);
										    number_of_icp_bytes_in_message_group 
											    = 
											    FIX((SI_Long)0L);
										    PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
											    25);
										      writing_icp_message_group 
											      = 
											      FIXNUM_ADD1(Writing_icp_message_group);
										      PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
											      24);
											gensymed_symbol 
												= 
												Nil;
											gensymed_symbol_4 
												= 
												0.0;
											gensymed_symbol_5 
												= 
												0.0;
											if (Profiling_enabled_qm) 
												    {
											    gensymed_symbol 
												    = 
												    T;
											    gensymed_symbol_4 
												    = 
												    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
												    (SI_Long)2L),
												    (SI_Long)0L);
											    gensymed_symbol_5 
												    = 
												    g2ext_unix_time_as_float();
											    aref_arg_1 
												    = 
												    ISVREF(Profiling_enabled_qm,
												    (SI_Long)2L);
											    DFLOAT_ISASET_1(aref_arg_1,
												    (SI_Long)0L,
												    gensymed_symbol_5);
											}
											if (icp_connection_open_p(Current_icp_socket) 
												&& 
												 
												!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
												    {
											    synchronize_icp_on_window_with_drawing(Current_window,
												    Left_edge_of_draw_area,
												    Top_edge_of_draw_area,
												    Right_edge_of_draw_area,
												    Bottom_edge_of_draw_area);
											    LOCK(For_image_plane);
											    if (PUSH_UNWIND_PROTECT(0)) 
													{
												current_pane 
													= 
													ISVREF(image_plane,
													(SI_Long)2L);
												current_image_plane 
													= 
													image_plane;
												loose_left_edge_of_visible_workspace_area 
													= 
													ISVREF(image_plane,
													(SI_Long)23L);
												loose_top_edge_of_visible_workspace_area 
													= 
													ISVREF(image_plane,
													(SI_Long)24L);
												loose_right_edge_of_visible_workspace_area 
													= 
													ISVREF(image_plane,
													(SI_Long)25L);
												loose_bottom_edge_of_visible_workspace_area 
													= 
													ISVREF(image_plane,
													(SI_Long)26L);
												color_or_metacolor 
													= 
													ISVREF(image_plane,
													(SI_Long)5L) 
													?
													 
													ISVREF(ISVREF(image_plane,
													(SI_Long)5L),
													(SI_Long)22L) 
													:
													 
													Nil;
												if (color_or_metacolor);
												else
												    color_or_metacolor 
													    = 
													    Qblack;
												if (EQ(color_or_metacolor,
													Qtransparent) 
													|| 
													EQ(color_or_metacolor,
													Qbackground)) 
													    {
												    background_color_or_metacolor 
													    = 
													    ISVREF(image_plane,
													    (SI_Long)5L) 
													    ?
													     
													    ISVREF(ISVREF(image_plane,
													    (SI_Long)5L),
													    (SI_Long)21L) 
													    :
													     
													    Nil;
												    if (background_color_or_metacolor);
												    else
													background_color_or_metacolor 
														= 
														Qwhite;
												    if (EQ(background_color_or_metacolor,
													    Qforeground) 
													    || 
													    EQ(background_color_or_metacolor,
													    Qworkspace_foreground)) 
														{
													temp_1 
														= 
														ISVREF(Current_color_map,
														(SI_Long)4L);
													if (temp_1);
													else
													    temp_1 
														    = 
														    map_to_color_value_1(Qblack);
													current_foreground_color_value 
														= 
														temp_1;
												    }
												    else if (EQ(background_color_or_metacolor,
													    Qtransparent) 
													    || 
													    EQ(background_color_or_metacolor,
													    Qbackground)) 
														{
													temp_1 
														= 
														ISVREF(Current_color_map,
														(SI_Long)5L);
													if (temp_1);
													else
													    temp_1 
														    = 
														    map_to_color_value_1(Qwhite);
													current_foreground_color_value 
														= 
														temp_1;
												    }
												    else
													current_foreground_color_value 
														= 
														EQ(background_color_or_metacolor,
														ISVREF(Current_color_map,
														(SI_Long)6L)) 
														?
														 
														ISVREF(Current_color_map,
														(SI_Long)7L) 
														:
														 
														map_to_color_value_1(background_color_or_metacolor);
												}
												else if (EQ(color_or_metacolor,
													Qforeground) 
													|| 
													EQ(color_or_metacolor,
													Qworkspace_foreground)) 
													    {
												    temp_1 
													    = 
													    ISVREF(Current_color_map,
													    (SI_Long)4L);
												    if (temp_1);
												    else
													temp_1 
														= 
														map_to_color_value_1(Qblack);
												    current_foreground_color_value 
													    = 
													    temp_1;
												}
												else
												    current_foreground_color_value 
													    = 
													    EQ(color_or_metacolor,
													    ISVREF(Current_color_map,
													    (SI_Long)6L)) 
													    ?
													     
													    ISVREF(Current_color_map,
													    (SI_Long)7L) 
													    :
													     
													    map_to_color_value_1(color_or_metacolor);
												PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
													23);
												  PUSH_SPECIAL_WITH_SYMBOL(Loose_bottom_edge_of_visible_workspace_area,Qloose_bottom_edge_of_visible_workspace_area,loose_bottom_edge_of_visible_workspace_area,
													  22);
												    PUSH_SPECIAL_WITH_SYMBOL(Loose_right_edge_of_visible_workspace_area,Qloose_right_edge_of_visible_workspace_area,loose_right_edge_of_visible_workspace_area,
													    21);
												      PUSH_SPECIAL_WITH_SYMBOL(Loose_top_edge_of_visible_workspace_area,Qloose_top_edge_of_visible_workspace_area,loose_top_edge_of_visible_workspace_area,
													      20);
													PUSH_SPECIAL_WITH_SYMBOL(Loose_left_edge_of_visible_workspace_area,Qloose_left_edge_of_visible_workspace_area,loose_left_edge_of_visible_workspace_area,
														19);
													  PUSH_SPECIAL_WITH_SYMBOL(Current_image_plane,Qcurrent_image_plane,current_image_plane,
														  18);
													    PUSH_SPECIAL_WITH_SYMBOL(Current_pane,Qcurrent_pane,current_pane,
														    17);
													      outer_native_image_plane 
														      = 
														      Current_native_image_plane;
													      PUSH_SPECIAL_WITH_SYMBOL(Outer_native_image_plane,Qouter_native_image_plane,outer_native_image_plane,
														      16);
														current_native_image_plane 
															= 
															image_plane;
														PUSH_SPECIAL_WITH_SYMBOL(Current_native_image_plane,Qcurrent_native_image_plane,current_native_image_plane,
															15);
														  if ( 
															  !EQ(Outer_native_image_plane,
															  Current_native_image_plane))
														      nip_begin_drawing(Current_native_image_plane);
														  color_or_metacolor 
															  = 
															  ISVREF(image_plane,
															  (SI_Long)5L) 
															  ?
															   
															  ISVREF(ISVREF(image_plane,
															  (SI_Long)5L),
															  (SI_Long)21L) 
															  :
															   
															  Nil;
														  if (color_or_metacolor);
														  else
														      color_or_metacolor 
															      = 
															      Qwhite;
														  if (EQ(color_or_metacolor,
															  Qtransparent) 
															  || 
															  EQ(color_or_metacolor,
															  Qbackground)) 
															      {
														      color_value 
															      = 
															      ISVREF(Current_color_map,
															      (SI_Long)5L);
														      if (color_value);
														      else
															  color_value 
																  = 
																  map_to_color_value_1(Qwhite);
														  }
														  else if (EQ(color_or_metacolor,
															  Qforeground) 
															  || 
															  EQ(color_or_metacolor,
															  Qworkspace_foreground)) 
															      {
														      temp_1 
															      = 
															      ISVREF(image_plane,
															      (SI_Long)5L) 
															      ?
															       
															      ISVREF(ISVREF(image_plane,
															      (SI_Long)5L),
															      (SI_Long)22L) 
															      :
															       
															      Nil;
														      if (temp_1);
														      else
															  temp_1 
																  = 
																  Qblack;
														      color_or_metacolor 
															      = 
															      temp_1;
														      if (EQ(color_or_metacolor,
															      Qtransparent) 
															      || 
															      EQ(color_or_metacolor,
															      Qbackground)) 
																  {
															  background_color_or_metacolor 
																  = 
																  ISVREF(image_plane,
																  (SI_Long)5L) 
																  ?
																   
																  ISVREF(ISVREF(image_plane,
																  (SI_Long)5L),
																  (SI_Long)21L) 
																  :
																   
																  Nil;
															  if (background_color_or_metacolor);
															  else
															      background_color_or_metacolor 
																      = 
																      Qwhite;
															  if (EQ(background_color_or_metacolor,
																  Qforeground) 
																  || 
																  EQ(background_color_or_metacolor,
																  Qworkspace_foreground)) 
																      {
															      color_value 
																      = 
																      ISVREF(Current_color_map,
																      (SI_Long)4L);
															      if (color_value);
															      else
																  color_value 
																	  = 
																	  map_to_color_value_1(Qblack);
															  }
															  else if (EQ(background_color_or_metacolor,
																  Qtransparent) 
																  || 
																  EQ(background_color_or_metacolor,
																  Qbackground)) 
																      {
															      color_value 
																      = 
																      ISVREF(Current_color_map,
																      (SI_Long)5L);
															      if (color_value);
															      else
																  color_value 
																	  = 
																	  map_to_color_value_1(Qwhite);
															  }
															  else
															      color_value 
																      = 
																      EQ(background_color_or_metacolor,
																      ISVREF(Current_color_map,
																      (SI_Long)6L)) 
																      ?
																       
																      ISVREF(Current_color_map,
																      (SI_Long)7L) 
																      :
																       
																      map_to_color_value_1(background_color_or_metacolor);
														      }
														      else if (EQ(color_or_metacolor,
															      Qforeground) 
															      || 
															      EQ(color_or_metacolor,
															      Qworkspace_foreground)) 
																  {
															  color_value 
																  = 
																  ISVREF(Current_color_map,
																  (SI_Long)4L);
															  if (color_value);
															  else
															      color_value 
																      = 
																      map_to_color_value_1(Qblack);
														      }
														      else
															  color_value 
																  = 
																  EQ(color_or_metacolor,
																  ISVREF(Current_color_map,
																  (SI_Long)6L)) 
																  ?
																   
																  ISVREF(Current_color_map,
																  (SI_Long)7L) 
																  :
																   
																  map_to_color_value_1(color_or_metacolor);
														  }
														  else
														      color_value 
															      = 
															      EQ(color_or_metacolor,
															      ISVREF(Current_color_map,
															      (SI_Long)6L)) 
															      ?
															       
															      ISVREF(Current_color_map,
															      (SI_Long)7L) 
															      :
															       
															      map_to_color_value_1(color_or_metacolor);
														  old_color_value 
															  = 
															  Current_background_color_value;
														  current_background_color_value 
															  = 
															  Current_background_color_value;
														  PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
															  14);
														    set_current_background_color_value(color_value);
														    left_edge_of_draw_area 
															    = 
															    Left_edge_of_draw_area;
														    top_edge_of_draw_area 
															    = 
															    Top_edge_of_draw_area;
														    right_edge_of_draw_area 
															    = 
															    Right_edge_of_draw_area;
														    bottom_edge_of_draw_area 
															    = 
															    Bottom_edge_of_draw_area;
														    PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
															    13);
														      PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
															      12);
															PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
																11);
															  PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
																  10);
															    temp_1 
																    = 
																    ISVREF(image_plane,
																    (SI_Long)6L);
															    Left_edge_of_draw_area 
																    = 
																    FIXNUM_MAX(temp_1,
																    Left_edge_of_draw_area);
															    temp_1 
																    = 
																    ISVREF(image_plane,
																    (SI_Long)7L);
															    Top_edge_of_draw_area 
																    = 
																    FIXNUM_MAX(temp_1,
																    Top_edge_of_draw_area);
															    temp_1 
																    = 
																    ISVREF(image_plane,
																    (SI_Long)8L);
															    Right_edge_of_draw_area 
																    = 
																    FIXNUM_MIN(temp_1,
																    Right_edge_of_draw_area);
															    temp_1 
																    = 
																    ISVREF(image_plane,
																    (SI_Long)9L);
															    Bottom_edge_of_draw_area 
																    = 
																    FIXNUM_MIN(temp_1,
																    Bottom_edge_of_draw_area);
															    if (FIXNUM_LT(Left_edge_of_draw_area,
																    Right_edge_of_draw_area) 
																    && 
																    FIXNUM_LT(Top_edge_of_draw_area,
																    Bottom_edge_of_draw_area)) 
																	{
																left_edge_of_draw_area 
																	= 
																	Left_edge_of_draw_area;
																top_edge_of_draw_area 
																	= 
																	Top_edge_of_draw_area;
																right_edge_of_draw_area 
																	= 
																	Right_edge_of_draw_area;
																bottom_edge_of_draw_area 
																	= 
																	Bottom_edge_of_draw_area;
																PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
																	9);
																  PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
																	  8);
																    PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
																	    7);
																      PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
																	      6);
																	temp_1 
																		= 
																		ISVREF(image_plane,
																		(SI_Long)19L);
																	Left_edge_of_draw_area 
																		= 
																		FIXNUM_MAX(temp_1,
																		Left_edge_of_draw_area);
																	temp_1 
																		= 
																		ISVREF(image_plane,
																		(SI_Long)20L);
																	Top_edge_of_draw_area 
																		= 
																		FIXNUM_MAX(temp_1,
																		Top_edge_of_draw_area);
																	temp_1 
																		= 
																		ISVREF(image_plane,
																		(SI_Long)21L);
																	Right_edge_of_draw_area 
																		= 
																		FIXNUM_MIN(temp_1,
																		Right_edge_of_draw_area);
																	temp_1 
																		= 
																		ISVREF(image_plane,
																		(SI_Long)22L);
																	Bottom_edge_of_draw_area 
																		= 
																		FIXNUM_MIN(temp_1,
																		Bottom_edge_of_draw_area);
																	if (FIXNUM_LT(Left_edge_of_draw_area,
																		Right_edge_of_draw_area) 
																		&& 
																		FIXNUM_LT(Top_edge_of_draw_area,
																		Bottom_edge_of_draw_area)) 
																		    {
																	    current_frame_transform_qm 
																		    = 
																		    Nil;
																	    current_image_x_scale 
																		    = 
																		    ISVREF(image_plane,
																		    (SI_Long)11L);
																	    current_image_y_scale 
																		    = 
																		    ISVREF(image_plane,
																		    (SI_Long)12L);
																	    current_x_origin_of_drawing 
																		    = 
																		    ISVREF(image_plane,
																		    (SI_Long)13L);
																	    current_y_origin_of_drawing 
																		    = 
																		    ISVREF(image_plane,
																		    (SI_Long)14L);
																	    PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
																		    5);
																	      PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
																		      4);
																		PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
																			3);
																		  PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
																			  2);
																		    PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
																			    1);
																		      already_in_synch 
																			      = 
																			      EQ(Current_drawing_transfer_mode,
																			      Kxor);
																		      current_drawing_transfer_mode 
																			      = 
																			      Current_drawing_transfer_mode;
																		      PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
																			      0);
																			if ( 
																				!already_in_synch) 
																				    {
																			    Current_drawing_transfer_mode 
																				    = 
																				    Kxor;
																			    synchronize_transfer_mode();
																			}
																			draw_resize_cursor(cursor);
																			aref_arg_1 
																				= 
																				M_CAR(cursor);
																			DFLOAT_ISASET_1(aref_arg_1,
																				(SI_Long)0L,
																				x_scale);
																			aref_arg_1 
																				= 
																				M_CAR(M_CDR(cursor));
																			DFLOAT_ISASET_1(aref_arg_1,
																				(SI_Long)0L,
																				y_scale);
																			draw_resize_cursor(cursor);
																		      POP_SPECIAL();
																		      if ( 
																			      !already_in_synch)
																			  synchronize_transfer_mode();
																		    POP_SPECIAL();
																		  POP_SPECIAL();
																		POP_SPECIAL();
																	      POP_SPECIAL();
																	    POP_SPECIAL();
																	}
																      POP_SPECIAL();
																    POP_SPECIAL();
																  POP_SPECIAL();
																POP_SPECIAL();
															    }
															  POP_SPECIAL();
															POP_SPECIAL();
														      POP_SPECIAL();
														    POP_SPECIAL();
														    set_current_background_color_value(old_color_value);
														  POP_SPECIAL();
														  if ( 
															  !EQ(Outer_native_image_plane,
															  Current_native_image_plane))
														      nip_end_drawing(Current_native_image_plane);
														POP_SPECIAL();
														temp_1 
															= 
															Current_native_image_plane 
															?
															 
															( 
															!EQ(image_plane,
															Current_native_image_plane) 
															?
															 
															nip_begin_drawing(Current_native_image_plane) 
															:
															 
															Nil) 
															:
															 
															Nil;
													      POP_SPECIAL();
													    POP_SPECIAL();
													  POP_SPECIAL();
													POP_SPECIAL();
												      POP_SPECIAL();
												    POP_SPECIAL();
												  POP_SPECIAL();
												POP_SPECIAL();
												SAVE_VALUES(VALUES_1(temp_1));
											    }
											    POP_UNWIND_PROTECT(0);
											    UNLOCK(For_image_plane);
											    CONTINUE_UNWINDING(0);
											    result = RESTORE_VALUES();
											    temp_1 
												    = 
												    result;
											    if (Flush_graphics_immediately_qm 
												    && 
												    FIXNUM_NE(ISVREF(Current_icp_socket,
												    (SI_Long)15L),
												    Icp_connection_closed))
												sync_graphics_on_current_window();
											    end_icp_message_group();
											}
											else
											    temp_1 
												    = 
												    Nil;
											SAVE_VALUES(VALUES_1(temp_1));
											if (Profiling_enabled_qm) 
												    {
											    gensymed_symbol_6 
												    = 
												    g2ext_unix_time_as_float();
											    gensymed_symbol_7 
												    = 
												    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
												    (SI_Long)2L),
												    (SI_Long)0L);
											    gensymed_symbol_8 
												    = 
												    gensymed_symbol_6 
												    - 
												    gensymed_symbol_7;
											    aref_arg_1 
												    = 
												    ISVREF(Profiling_enabled_qm,
												    (SI_Long)6L);
											    aref_new_value 
												    = 
												    gensymed_symbol_8 
												    + 
												    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
												    (SI_Long)6L),
												    (SI_Long)0L);
											    DFLOAT_ISASET_1(aref_arg_1,
												    (SI_Long)0L,
												    aref_new_value);
											    aref_arg_1 
												    = 
												    ISVREF(Profiling_enabled_qm,
												    (SI_Long)2L);
											    aref_new_value 
												    = 
												    gensymed_symbol 
												    ?
												     
												    gensymed_symbol_4 
												    + 
												    gensymed_symbol_8 
												    + 
												    (gensymed_symbol_7 
												    - 
												    gensymed_symbol_5) 
												    :
												     
												    gensymed_symbol_6;
											    DFLOAT_ISASET_1(aref_arg_1,
												    (SI_Long)0L,
												    aref_new_value);
											}
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
							    else
								SAVE_VALUES(VALUES_1(Nil));
							}
							else
							    SAVE_VALUES(VALUES_1(Nil));
						    }
						    else if (EQ(Type_of_current_window,
							    Qprinter)) {
							LOCK(For_image_plane);
							if (PUSH_UNWIND_PROTECT(0)) 
								    {
							    current_pane = 
								    ISVREF(image_plane,
								    (SI_Long)2L);
							    current_image_plane 
								    = 
								    image_plane;
							    loose_left_edge_of_visible_workspace_area 
								    = 
								    ISVREF(image_plane,
								    (SI_Long)23L);
							    loose_top_edge_of_visible_workspace_area 
								    = 
								    ISVREF(image_plane,
								    (SI_Long)24L);
							    loose_right_edge_of_visible_workspace_area 
								    = 
								    ISVREF(image_plane,
								    (SI_Long)25L);
							    loose_bottom_edge_of_visible_workspace_area 
								    = 
								    ISVREF(image_plane,
								    (SI_Long)26L);
							    color_or_metacolor 
								    = 
								    ISVREF(image_plane,
								    (SI_Long)5L) 
								    ? 
								    ISVREF(ISVREF(image_plane,
								    (SI_Long)5L),
								    (SI_Long)22L) 
								    : Nil;
							    if (color_or_metacolor);
							    else
								color_or_metacolor 
									= 
									Qblack;
							    if (EQ(color_or_metacolor,
								    Qtransparent) 
								    || 
								    EQ(color_or_metacolor,
								    Qbackground)) 
									{
								background_color_or_metacolor 
									= 
									ISVREF(image_plane,
									(SI_Long)5L) 
									? 
									ISVREF(ISVREF(image_plane,
									(SI_Long)5L),
									(SI_Long)21L) 
									: Nil;
								if (background_color_or_metacolor);
								else
								    background_color_or_metacolor 
									    = 
									    Qwhite;
								if (EQ(background_color_or_metacolor,
									Qforeground) 
									|| 
									EQ(background_color_or_metacolor,
									Qworkspace_foreground)) 
									    {
								    temp_1 
									    = 
									    ISVREF(Current_color_map,
									    (SI_Long)4L);
								    if (temp_1);
								    else
									temp_1 
										= 
										map_to_color_value_1(Qblack);
								    current_foreground_color_value 
									    = 
									    temp_1;
								}
								else if (EQ(background_color_or_metacolor,
									Qtransparent) 
									|| 
									EQ(background_color_or_metacolor,
									Qbackground)) 
									    {
								    temp_1 
									    = 
									    ISVREF(Current_color_map,
									    (SI_Long)5L);
								    if (temp_1);
								    else
									temp_1 
										= 
										map_to_color_value_1(Qwhite);
								    current_foreground_color_value 
									    = 
									    temp_1;
								}
								else
								    current_foreground_color_value 
									    = 
									    EQ(background_color_or_metacolor,
									    ISVREF(Current_color_map,
									    (SI_Long)6L)) 
									    ?
									     
									    ISVREF(Current_color_map,
									    (SI_Long)7L) 
									    :
									     
									    map_to_color_value_1(background_color_or_metacolor);
							    }
							    else if (EQ(color_or_metacolor,
								    Qforeground) 
								    || 
								    EQ(color_or_metacolor,
								    Qworkspace_foreground)) 
									{
								temp_1 = 
									ISVREF(Current_color_map,
									(SI_Long)4L);
								if (temp_1);
								else
								    temp_1 
									    = 
									    map_to_color_value_1(Qblack);
								current_foreground_color_value 
									= 
									temp_1;
							    }
							    else
								current_foreground_color_value 
									= 
									EQ(color_or_metacolor,
									ISVREF(Current_color_map,
									(SI_Long)6L)) 
									? 
									ISVREF(Current_color_map,
									(SI_Long)7L) 
									: 
									map_to_color_value_1(color_or_metacolor);
							    PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
								    23);
							      PUSH_SPECIAL_WITH_SYMBOL(Loose_bottom_edge_of_visible_workspace_area,Qloose_bottom_edge_of_visible_workspace_area,loose_bottom_edge_of_visible_workspace_area,
								      22);
								PUSH_SPECIAL_WITH_SYMBOL(Loose_right_edge_of_visible_workspace_area,Qloose_right_edge_of_visible_workspace_area,loose_right_edge_of_visible_workspace_area,
									21);
								  PUSH_SPECIAL_WITH_SYMBOL(Loose_top_edge_of_visible_workspace_area,Qloose_top_edge_of_visible_workspace_area,loose_top_edge_of_visible_workspace_area,
									  20);
								    PUSH_SPECIAL_WITH_SYMBOL(Loose_left_edge_of_visible_workspace_area,Qloose_left_edge_of_visible_workspace_area,loose_left_edge_of_visible_workspace_area,
									    19);
								      PUSH_SPECIAL_WITH_SYMBOL(Current_image_plane,Qcurrent_image_plane,current_image_plane,
									      18);
									PUSH_SPECIAL_WITH_SYMBOL(Current_pane,Qcurrent_pane,current_pane,
										17);
									  outer_native_image_plane 
										  = 
										  Current_native_image_plane;
									  PUSH_SPECIAL_WITH_SYMBOL(Outer_native_image_plane,Qouter_native_image_plane,outer_native_image_plane,
										  16);
									    current_native_image_plane 
										    = 
										    image_plane;
									    PUSH_SPECIAL_WITH_SYMBOL(Current_native_image_plane,Qcurrent_native_image_plane,current_native_image_plane,
										    15);
									      if ( 
										      !EQ(Outer_native_image_plane,
										      Current_native_image_plane))
										  nip_begin_drawing(Current_native_image_plane);
									      color_or_metacolor 
										      = 
										      ISVREF(image_plane,
										      (SI_Long)5L) 
										      ?
										       
										      ISVREF(ISVREF(image_plane,
										      (SI_Long)5L),
										      (SI_Long)21L) 
										      :
										       
										      Nil;
									      if (color_or_metacolor);
									      else
										  color_or_metacolor 
											  = 
											  Qwhite;
									      if (EQ(color_or_metacolor,
										      Qtransparent) 
										      || 
										      EQ(color_or_metacolor,
										      Qbackground)) 
											  {
										  color_value 
											  = 
											  ISVREF(Current_color_map,
											  (SI_Long)5L);
										  if (color_value);
										  else
										      color_value 
											      = 
											      map_to_color_value_1(Qwhite);
									      }
									      else if (EQ(color_or_metacolor,
										      Qforeground) 
										      || 
										      EQ(color_or_metacolor,
										      Qworkspace_foreground)) 
											  {
										  temp_1 
											  = 
											  ISVREF(image_plane,
											  (SI_Long)5L) 
											  ?
											   
											  ISVREF(ISVREF(image_plane,
											  (SI_Long)5L),
											  (SI_Long)22L) 
											  :
											   
											  Nil;
										  if (temp_1);
										  else
										      temp_1 
											      = 
											      Qblack;
										  color_or_metacolor 
											  = 
											  temp_1;
										  if (EQ(color_or_metacolor,
											  Qtransparent) 
											  || 
											  EQ(color_or_metacolor,
											  Qbackground)) 
											      {
										      background_color_or_metacolor 
											      = 
											      ISVREF(image_plane,
											      (SI_Long)5L) 
											      ?
											       
											      ISVREF(ISVREF(image_plane,
											      (SI_Long)5L),
											      (SI_Long)21L) 
											      :
											       
											      Nil;
										      if (background_color_or_metacolor);
										      else
											  background_color_or_metacolor 
												  = 
												  Qwhite;
										      if (EQ(background_color_or_metacolor,
											      Qforeground) 
											      || 
											      EQ(background_color_or_metacolor,
											      Qworkspace_foreground)) 
												  {
											  color_value 
												  = 
												  ISVREF(Current_color_map,
												  (SI_Long)4L);
											  if (color_value);
											  else
											      color_value 
												      = 
												      map_to_color_value_1(Qblack);
										      }
										      else if (EQ(background_color_or_metacolor,
											      Qtransparent) 
											      || 
											      EQ(background_color_or_metacolor,
											      Qbackground)) 
												  {
											  color_value 
												  = 
												  ISVREF(Current_color_map,
												  (SI_Long)5L);
											  if (color_value);
											  else
											      color_value 
												      = 
												      map_to_color_value_1(Qwhite);
										      }
										      else
											  color_value 
												  = 
												  EQ(background_color_or_metacolor,
												  ISVREF(Current_color_map,
												  (SI_Long)6L)) 
												  ?
												   
												  ISVREF(Current_color_map,
												  (SI_Long)7L) 
												  :
												   
												  map_to_color_value_1(background_color_or_metacolor);
										  }
										  else if (EQ(color_or_metacolor,
											  Qforeground) 
											  || 
											  EQ(color_or_metacolor,
											  Qworkspace_foreground)) 
											      {
										      color_value 
											      = 
											      ISVREF(Current_color_map,
											      (SI_Long)4L);
										      if (color_value);
										      else
											  color_value 
												  = 
												  map_to_color_value_1(Qblack);
										  }
										  else
										      color_value 
											      = 
											      EQ(color_or_metacolor,
											      ISVREF(Current_color_map,
											      (SI_Long)6L)) 
											      ?
											       
											      ISVREF(Current_color_map,
											      (SI_Long)7L) 
											      :
											       
											      map_to_color_value_1(color_or_metacolor);
									      }
									      else
										  color_value 
											  = 
											  EQ(color_or_metacolor,
											  ISVREF(Current_color_map,
											  (SI_Long)6L)) 
											  ?
											   
											  ISVREF(Current_color_map,
											  (SI_Long)7L) 
											  :
											   
											  map_to_color_value_1(color_or_metacolor);
									      old_color_value 
										      = 
										      Current_background_color_value;
									      current_background_color_value 
										      = 
										      Current_background_color_value;
									      PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
										      14);
										set_current_background_color_value(color_value);
										left_edge_of_draw_area 
											= 
											Left_edge_of_draw_area;
										top_edge_of_draw_area 
											= 
											Top_edge_of_draw_area;
										right_edge_of_draw_area 
											= 
											Right_edge_of_draw_area;
										bottom_edge_of_draw_area 
											= 
											Bottom_edge_of_draw_area;
										PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
											13);
										  PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
											  12);
										    PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
											    11);
										      PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
											      10);
											temp_1 
												= 
												ISVREF(image_plane,
												(SI_Long)6L);
											Left_edge_of_draw_area 
												= 
												FIXNUM_MAX(temp_1,
												Left_edge_of_draw_area);
											temp_1 
												= 
												ISVREF(image_plane,
												(SI_Long)7L);
											Top_edge_of_draw_area 
												= 
												FIXNUM_MAX(temp_1,
												Top_edge_of_draw_area);
											temp_1 
												= 
												ISVREF(image_plane,
												(SI_Long)8L);
											Right_edge_of_draw_area 
												= 
												FIXNUM_MIN(temp_1,
												Right_edge_of_draw_area);
											temp_1 
												= 
												ISVREF(image_plane,
												(SI_Long)9L);
											Bottom_edge_of_draw_area 
												= 
												FIXNUM_MIN(temp_1,
												Bottom_edge_of_draw_area);
											if (FIXNUM_LT(Left_edge_of_draw_area,
												Right_edge_of_draw_area) 
												&& 
												FIXNUM_LT(Top_edge_of_draw_area,
												Bottom_edge_of_draw_area)) 
												    {
											    left_edge_of_draw_area 
												    = 
												    Left_edge_of_draw_area;
											    top_edge_of_draw_area 
												    = 
												    Top_edge_of_draw_area;
											    right_edge_of_draw_area 
												    = 
												    Right_edge_of_draw_area;
											    bottom_edge_of_draw_area 
												    = 
												    Bottom_edge_of_draw_area;
											    PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
												    9);
											      PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
												      8);
												PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
													7);
												  PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
													  6);
												    temp_1 
													    = 
													    ISVREF(image_plane,
													    (SI_Long)19L);
												    Left_edge_of_draw_area 
													    = 
													    FIXNUM_MAX(temp_1,
													    Left_edge_of_draw_area);
												    temp_1 
													    = 
													    ISVREF(image_plane,
													    (SI_Long)20L);
												    Top_edge_of_draw_area 
													    = 
													    FIXNUM_MAX(temp_1,
													    Top_edge_of_draw_area);
												    temp_1 
													    = 
													    ISVREF(image_plane,
													    (SI_Long)21L);
												    Right_edge_of_draw_area 
													    = 
													    FIXNUM_MIN(temp_1,
													    Right_edge_of_draw_area);
												    temp_1 
													    = 
													    ISVREF(image_plane,
													    (SI_Long)22L);
												    Bottom_edge_of_draw_area 
													    = 
													    FIXNUM_MIN(temp_1,
													    Bottom_edge_of_draw_area);
												    if (FIXNUM_LT(Left_edge_of_draw_area,
													    Right_edge_of_draw_area) 
													    && 
													    FIXNUM_LT(Top_edge_of_draw_area,
													    Bottom_edge_of_draw_area)) 
														{
													current_frame_transform_qm 
														= 
														Nil;
													current_image_x_scale 
														= 
														ISVREF(image_plane,
														(SI_Long)11L);
													current_image_y_scale 
														= 
														ISVREF(image_plane,
														(SI_Long)12L);
													current_x_origin_of_drawing 
														= 
														ISVREF(image_plane,
														(SI_Long)13L);
													current_y_origin_of_drawing 
														= 
														ISVREF(image_plane,
														(SI_Long)14L);
													PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
														5);
													  PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
														  4);
													    PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
														    3);
													      PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
														      2);
														PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
															1);
														  already_in_synch 
															  = 
															  EQ(Current_drawing_transfer_mode,
															  Kxor);
														  current_drawing_transfer_mode 
															  = 
															  Current_drawing_transfer_mode;
														  PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
															  0);
														    if ( 
															    !already_in_synch) 
																{
															Current_drawing_transfer_mode 
																= 
																Kxor;
															synchronize_transfer_mode();
														    }
														    draw_resize_cursor(cursor);
														    aref_arg_1 
															    = 
															    M_CAR(cursor);
														    DFLOAT_ISASET_1(aref_arg_1,
															    (SI_Long)0L,
															    x_scale);
														    aref_arg_1 
															    = 
															    M_CAR(M_CDR(cursor));
														    DFLOAT_ISASET_1(aref_arg_1,
															    (SI_Long)0L,
															    y_scale);
														    draw_resize_cursor(cursor);
														  POP_SPECIAL();
														  if ( 
															  !already_in_synch)
														      synchronize_transfer_mode();
														POP_SPECIAL();
													      POP_SPECIAL();
													    POP_SPECIAL();
													  POP_SPECIAL();
													POP_SPECIAL();
												    }
												  POP_SPECIAL();
												POP_SPECIAL();
											      POP_SPECIAL();
											    POP_SPECIAL();
											}
										      POP_SPECIAL();
										    POP_SPECIAL();
										  POP_SPECIAL();
										POP_SPECIAL();
										set_current_background_color_value(old_color_value);
									      POP_SPECIAL();
									      if ( 
										      !EQ(Outer_native_image_plane,
										      Current_native_image_plane))
										  nip_end_drawing(Current_native_image_plane);
									    POP_SPECIAL();
									    if (Current_native_image_plane) 
											{
										if ( 
											!EQ(image_plane,
											Current_native_image_plane))
										    SAVE_VALUES(nip_begin_drawing(Current_native_image_plane));
										else
										    SAVE_VALUES(VALUES_1(Nil));
									    }
									    else
										SAVE_VALUES(VALUES_1(Nil));
									  POP_SPECIAL();
									POP_SPECIAL();
								      POP_SPECIAL();
								    POP_SPECIAL();
								  POP_SPECIAL();
								POP_SPECIAL();
							      POP_SPECIAL();
							    POP_SPECIAL();
							}
							POP_UNWIND_PROTECT(0);
							UNLOCK(For_image_plane);
							CONTINUE_UNWINDING(0);
						    }
						    else
							SAVE_VALUES(VALUES_1(Qnil));
						  POP_SPECIAL();
					      }
					      POP_UNWIND_PROTECT(1);
					      UNLOCK(On_window_with_drawing);
					      CONTINUE_UNWINDING(1);
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
			POP_UNWIND_PROTECT(2);
			UNLOCK(On_window_without_drawing);
			CONTINUE_UNWINDING(2);
			result = RESTORE_VALUES();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    POP_LOCAL_ALLOCATION(0,0);
    RESTORE_STACK();
    return result;
}

static Object Qis_resized_by_the_user;  /* is-resized-by-the-user */

/* RESIZE-ITEMS-PER-RESIZE-CURSOR */
Object resize_items_per_resize_cursor(cursor,corner_being_moved,items,
	    frame_serial_number)
    Object cursor, corner_being_moved, items, frame_serial_number;
{
    Object item, ab_loop_list_, gensymed_symbol, xa, ya, left, top, right;
    Object bottom;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    SI_Long new_width, new_height;
    char temp;
    double x_scale, y_scale;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(128,170);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	x_scale = DFLOAT_ISAREF_1(M_CAR(cursor),(SI_Long)0L);
	y_scale = DFLOAT_ISAREF_1(M_CAR(M_CDR(cursor)),(SI_Long)0L);
	item = Nil;
	ab_loop_list_ = items;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	item = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol = ISVREF(item,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(item) ? EQ(ISVREF(item,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else if (FIXNUMP(frame_serial_number))
	    temp = FIXNUMP(gensymed_symbol) ? 
		    FIXNUM_LT(frame_serial_number,gensymed_symbol) : TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(frame_serial_number);
	    ya = M_CAR(gensymed_symbol);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? 
			FIXNUM_LT(M_CDR(frame_serial_number),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
	if ( !temp) {
	    gensymed_symbol = ISVREF(item,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    left = gensymed_symbol;
	    gensymed_symbol = ISVREF(item,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    top = gensymed_symbol;
	    gensymed_symbol = ISVREF(item,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    right = gensymed_symbol;
	    gensymed_symbol = ISVREF(item,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    bottom = gensymed_symbol;
	    gensymed_symbol = ISVREF(item,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(item,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    new_width = inline_floor_1(0.5 + x_scale * 
		    (double)(gensymed_symbol_1 - gensymed_symbol_2));
	    gensymed_symbol = ISVREF(item,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(item,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    new_height = inline_floor_1(0.5 + y_scale * 
		    (double)(gensymed_symbol_1 - gensymed_symbol_2));
	    if (EQ(corner_being_moved,Qtop_left)) {
		top = FIX(IFIX(bottom) - new_height);
		left = FIX(IFIX(right) - new_width);
	    }
	    else if (EQ(corner_being_moved,Qtop_right)) {
		top = FIX(IFIX(bottom) - new_height);
		right = FIX(IFIX(left) + new_width);
	    }
	    else if (EQ(corner_being_moved,Qbottom_left)) {
		bottom = FIX(IFIX(top) + new_height);
		left = FIX(IFIX(right) - new_width);
	    }
	    else if (EQ(corner_being_moved,Qbottom_right)) {
		bottom = FIX(IFIX(top) + new_height);
		right = FIX(IFIX(left) + new_width);
	    }
	    else if (EQ(corner_being_moved,Qtop))
		top = FIX(IFIX(bottom) - new_height);
	    else if (EQ(corner_being_moved,Qleft))
		left = FIX(IFIX(right) - new_width);
	    else if (EQ(corner_being_moved,Qbottom))
		bottom = FIX(IFIX(top) + new_height);
	    else if (EQ(corner_being_moved,Qright))
		right = FIX(IFIX(left) + new_width);
	    change_size_per_bounding_rectangle(5,item,left,top,right,bottom);
	    invoke_rules_for_resizement_chaining(item,Qis_resized_by_the_user);
	}
	goto next_loop;
      end_loop:
	result = VALUES_1(Qnil);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

void moves_INIT()
{
    Object temp, reclaim_structure_for_dragging_state_1;
    Object valid_workstation_context_p_for_dragging_state_1;
    Object clean_up_workstation_context_for_dragging_state_1;
    Object suspend_workstation_context_for_dragging_state_1;
    Object resume_workstation_context_for_dragging_state_1;
    Object reclaim_structure_for_move_dragging_state_1;
    Object reclaim_structure_for_transfer_dragging_state_1;
    Object clean_up_workstation_context_for_transfer_dragging_state_1;
    Object reclaim_structure_for_selection_handle_spot_1, type_description;
    Object svref_new_value, reclaim_structure_for_drag_handle_state_1;
    Object valid_workstation_context_p_for_drag_handle_state_1;
    Object clean_up_workstation_context_for_drag_handle_state_1;
    Object AB_package, Qfinish_drag_handle, Qnew_style_event_handler;
    Object Qtrack_mouse_for_drag_handle, Qdrag_handle_state;
    Object Qclean_up_workstation_context, Qvalid_workstation_context_p;
    Object Qinternal, string_constant_21, Qabort_workstation_context;
    Object Qtop_level, Qselection_style_of_workstation_context_type;
    Object Qtop_level_with_mouse_tracking_is_selection_style;
    Object Qreclaim_structure, Qoutstanding_drag_handle_state_count;
    Object Qdrag_handle_state_structure_memory_usage, Qutilities2;
    Object string_constant_20, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_19, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qreclaim_rubber_stamp_widgets;
    Object list_constant_17, Qmoves, list_constant_16, list_constant_15;
    Object Qmake_iconic_entity_with_specific_icon_description, Kfuncall;
    Object list_constant_14, list_constant_13, list_constant_12;
    Object list_constant_11, list_constant_9, list_constant_10;
    Object list_constant_8, Qoutline, list_constant_6, list_constant_7;
    Object Qsolid_rectangle, list_constant_5, list_constant_4, Qpolychrome;
    Object Qitem, Qtype_of_frame_represented, Qabstract_type;
    Object Qimage_plane_spot, Qenclosing_spot_type, Qinnermost_spot_p;
    Object Qselection_handle_spot, Qoutstanding_selection_handle_spot_count;
    Object Qselection_handle_spot_structure_memory_usage, string_constant_18;
    Object string_constant_17, Qreenter_editor_if_not_hand_placed;
    Object Qtransfer_dragging_state, Qtop_level_is_selection_style;
    Object Qoutstanding_transfer_dragging_state_count;
    Object Qtransfer_dragging_state_structure_memory_usage, string_constant_16;
    Object string_constant_15, Qmove_dragging_state;
    Object Qoutstanding_move_dragging_state_count;
    Object Qmove_dragging_state_structure_memory_usage, string_constant_14;
    Object string_constant_13, Qdragging_state, Qresume_workstation_context;
    Object Qsuspend_workstation_context, list_constant_3, Qtrend_chart;
    Object Qfreeform_table, Qdefinition, Qbutton, Qmeter, Qdial, Qtext_box;
    Object Qtable, Qmouse_up_in_dragging_state, Qmouse_down_in_dragging_state;
    Object Qmouse_motion_in_dragging_state, string_constant_12;
    Object list_constant_2, Qscreen_layout, Qoutstanding_dragging_state_count;
    Object Qdragging_state_structure_memory_usage, string_constant_11;
    Object string_constant_10, string_constant_9;
    Object Qreclaim_dragging_cons_function, Qreclaim_dragging_list_function;
    Object string_constant_8, Qdragging_cons_memory_usage;
    Object Qoutstanding_dragging_conses, Qrun, list_constant_1;
    Object Qdragging_cons_counter_vector, Qmake_thread_array, list_constant;
    Object Qavailable_dragging_conses_tail_vector;
    Object Qavailable_dragging_conses_vector;

    x_note_fn_call(128,171);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qcurrent_dragging_states = STATIC_SYMBOL("CURRENT-DRAGGING-STATES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_dragging_states,
	    Current_dragging_states);
    Qmoves = STATIC_SYMBOL("MOVES",AB_package);
    Qreclaim_dragging_list_function = 
	    STATIC_SYMBOL("RECLAIM-DRAGGING-LIST-FUNCTION",AB_package);
    record_system_variable(Qcurrent_dragging_states,Qmoves,Nil,Qnil,Qnil,
	    Qreclaim_dragging_list_function,Qt);
    Qavailable_dragging_conses = STATIC_SYMBOL("AVAILABLE-DRAGGING-CONSES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_dragging_conses,
	    Available_dragging_conses);
    Qrun = STATIC_SYMBOL("RUN",AB_package);
    record_system_variable(Qavailable_dragging_conses,Qrun,Nil,Qnil,Qt,
	    Qnil,Qnil);
    Qavailable_dragging_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-DRAGGING-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_dragging_conses_tail,
	    Available_dragging_conses_tail);
    record_system_variable(Qavailable_dragging_conses_tail,Qrun,Nil,Qnil,
	    Qt,Qnil,Qnil);
    Qavailable_dragging_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-DRAGGING-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_dragging_conses_vector,
	    Available_dragging_conses_vector);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_thread_array = STATIC_SYMBOL("MAKE-THREAD-ARRAY",AB_package);
    list_constant = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,Qnil);
    record_system_variable(Qavailable_dragging_conses_vector,Qrun,
	    list_constant,Qnil,Qt,Qnil,Qnil);
    Qavailable_dragging_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-DRAGGING-CONSES-TAIL-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_dragging_conses_tail_vector,
	    Available_dragging_conses_tail_vector);
    record_system_variable(Qavailable_dragging_conses_tail_vector,Qrun,
	    list_constant,Qnil,Qt,Qnil,Qnil);
    Qdragging_cons_counter_vector = 
	    STATIC_SYMBOL("DRAGGING-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdragging_cons_counter_vector,
	    Dragging_cons_counter_vector);
    list_constant_1 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    FIX((SI_Long)0L));
    record_system_variable(Qdragging_cons_counter_vector,Qrun,
	    list_constant_1,Qnil,Qt,Qnil,Qnil);
    Qdragging_cons_counter = STATIC_SYMBOL("DRAGGING-CONS-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdragging_cons_counter,Dragging_cons_counter);
    record_system_variable(Qdragging_cons_counter,Qrun,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    Qoutstanding_dragging_conses = 
	    STATIC_SYMBOL("OUTSTANDING-DRAGGING-CONSES",AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_dragging_conses,
	    STATIC_FUNCTION(outstanding_dragging_conses,NIL,FALSE,0,0));
    Qdragging_cons_memory_usage = 
	    STATIC_SYMBOL("DRAGGING-CONS-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qdragging_cons_memory_usage,
	    STATIC_FUNCTION(dragging_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_8 = STATIC_STRING("1q83-Rvy9k83-Ruy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_dragging_conses);
    push_optimized_constant(Qdragging_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_8));
    Qdragging = STATIC_SYMBOL("DRAGGING",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_dragging_list_function,
	    STATIC_FUNCTION(reclaim_dragging_list_function,NIL,FALSE,1,1));
    Qreclaim_dragging_cons_function = 
	    STATIC_SYMBOL("RECLAIM-DRAGGING-CONS-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_dragging_cons_function,
	    STATIC_FUNCTION(reclaim_dragging_cons_function,NIL,FALSE,1,1));
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_dragging_state_g2_struct = 
	    STATIC_SYMBOL("DRAGGING-STATE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qdragging_state = STATIC_SYMBOL("DRAGGING-STATE",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_dragging_state_g2_struct,
	    Qdragging_state,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qdragging_state,
	    Qg2_defstruct_structure_name_dragging_state_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_dragging_state == UNBOUND)
	The_type_description_of_dragging_state = Nil;
    string_constant_9 = 
	    STATIC_STRING("43Dy8m83gny1o83gny83-Sy8n8k1l83-Sy0000001m1n8y83-3Ry1u83vIy83-7xy83-Gty83-=Ey83-HAy83-HGy83w3y83-H-y83-72y83-8Fy1m8x83-Syk3Nyk0k");
    string_constant_10 = STATIC_STRING("0");
    temp = The_type_description_of_dragging_state;
    The_type_description_of_dragging_state = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(LIST_2(string_constant_9,
	    string_constant_10)));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_dragging_state_g2_struct,
	    The_type_description_of_dragging_state,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qdragging_state,
	    The_type_description_of_dragging_state,Qtype_description_of_type);
    Qoutstanding_dragging_state_count = 
	    STATIC_SYMBOL("OUTSTANDING-DRAGGING-STATE-COUNT",AB_package);
    Qdragging_state_structure_memory_usage = 
	    STATIC_SYMBOL("DRAGGING-STATE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_11 = STATIC_STRING("1q83gny8s83-Rwy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_dragging_state_count);
    push_optimized_constant(Qdragging_state_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_11));
    Qchain_of_available_dragging_states = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-DRAGGING-STATES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_dragging_states,
	    Chain_of_available_dragging_states);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_dragging_states,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qdragging_state_count = STATIC_SYMBOL("DRAGGING-STATE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdragging_state_count,Dragging_state_count);
    record_system_variable(Qdragging_state_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_dragging_states_vector == UNBOUND)
	Chain_of_available_dragging_states_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qdragging_state_structure_memory_usage,
	    STATIC_FUNCTION(dragging_state_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_dragging_state_count,
	    STATIC_FUNCTION(outstanding_dragging_state_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_dragging_state_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_dragging_state,NIL,FALSE,
	    1,1);
    record_direct_structure_method(Qreclaim_structure,Qdragging_state,
	    reclaim_structure_for_dragging_state_1);
    Qtop_level_with_mouse_tracking_is_selection_style = 
	    STATIC_SYMBOL("TOP-LEVEL-WITH-MOUSE-TRACKING-IS-SELECTION-STYLE",
	    AB_package);
    Qselection_style_of_workstation_context_type = 
	    STATIC_SYMBOL("SELECTION-STYLE-OF-WORKSTATION-CONTEXT-TYPE",
	    AB_package);
    mutate_global_property(Qdragging_state,
	    Qtop_level_with_mouse_tracking_is_selection_style,
	    Qselection_style_of_workstation_context_type);
    Qtop_level = STATIC_SYMBOL("TOP-LEVEL",AB_package);
    Qscreen_layout = STATIC_SYMBOL("SCREEN-LAYOUT",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qdragging,Qscreen_layout);
    make_context_description(Qdragging,Qtop_level,Qnil,list_constant_2);
    Qmouse_up_in_dragging_state = 
	    STATIC_SYMBOL("MOUSE-UP-IN-DRAGGING-STATE",AB_package);
    Qmouse_down_in_dragging_state = 
	    STATIC_SYMBOL("MOUSE-DOWN-IN-DRAGGING-STATE",AB_package);
    Qmouse_motion_in_dragging_state = 
	    STATIC_SYMBOL("MOUSE-MOTION-IN-DRAGGING-STATE",AB_package);
    Qabort_workstation_context = STATIC_SYMBOL("ABORT-WORKSTATION-CONTEXT",
	    AB_package);
    string_constant_12 = 
	    STATIC_STRING("1o1n830-y8k9k1n830Dy8k9l1n830+y8k9m1n831-y8k9n");
    Qinternal = STATIC_SYMBOL("INTERNAL",AB_package);
    clear_optimized_constants();
    push_optimized_constant(Qmouse_up_in_dragging_state);
    push_optimized_constant(Qmouse_down_in_dragging_state);
    push_optimized_constant(Qmouse_motion_in_dragging_state);
    push_optimized_constant(Qabort_workstation_context);
    make_keymap(Qdragging,Qnil,
	    regenerate_optimized_constant(string_constant_12),Qinternal,
	    Qnil,Qnil,Qnil,Qnil);
    if (Explicit_dragger_x_in_window_qm == UNBOUND)
	Explicit_dragger_x_in_window_qm = Nil;
    if (Explicit_dragger_y_in_window_qm == UNBOUND)
	Explicit_dragger_y_in_window_qm = Nil;
    Qmove_objects_beyond_workspace_margin = 
	    STATIC_SYMBOL("MOVE-OBJECTS-BEYOND-WORKSPACE-MARGIN",AB_package);
    Qg2_defstruct_structure_name_image_plane_g2_struct = 
	    STATIC_SYMBOL("IMAGE-PLANE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qimage_plane_dragging_style = 
	    STATIC_SYMBOL("IMAGE-PLANE-DRAGGING-STYLE",AB_package);
    Qmove_dragging_style = STATIC_SYMBOL("MOVE-DRAGGING-STYLE",AB_package);
    Qtransfer_dragging_style = STATIC_SYMBOL("TRANSFER-DRAGGING-STYLE",
	    AB_package);
    Qmove_workspaces_beyond_window_margin = 
	    STATIC_SYMBOL("MOVE-WORKSPACES-BEYOND-WINDOW-MARGIN",AB_package);
    Qimage_plane = STATIC_SYMBOL("IMAGE-PLANE",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    if (Do_not_invoke_rules_for_user_icon_movement_qm == UNBOUND)
	Do_not_invoke_rules_for_user_icon_movement_qm = Nil;
    Qvalid_workstation_context_p = 
	    STATIC_SYMBOL("VALID-WORKSTATION-CONTEXT-P",AB_package);
    valid_workstation_context_p_for_dragging_state_1 = 
	    STATIC_FUNCTION(valid_workstation_context_p_for_dragging_state,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qvalid_workstation_context_p,
	    Qdragging_state,valid_workstation_context_p_for_dragging_state_1);
    Qnew_style_event_handler = STATIC_SYMBOL("NEW-STYLE-EVENT-HANDLER",
	    AB_package);
    mutate_global_property(Qmouse_motion_in_dragging_state,
	    Qmouse_motion_in_dragging_state,Qnew_style_event_handler);
    SET_SYMBOL_FUNCTION(Qmouse_motion_in_dragging_state,
	    STATIC_FUNCTION(mouse_motion_in_dragging_state,NIL,FALSE,1,1));
    mutate_global_property(Qmouse_down_in_dragging_state,
	    Qmouse_down_in_dragging_state,Qnew_style_event_handler);
    SET_SYMBOL_FUNCTION(Qmouse_down_in_dragging_state,
	    STATIC_FUNCTION(mouse_down_in_dragging_state,NIL,FALSE,1,1));
    mutate_global_property(Qmouse_up_in_dragging_state,
	    Qmouse_up_in_dragging_state,Qnew_style_event_handler);
    SET_SYMBOL_FUNCTION(Qmouse_up_in_dragging_state,
	    STATIC_FUNCTION(mouse_up_in_dragging_state,NIL,FALSE,1,1));
    Qclean_up_workstation_context = 
	    STATIC_SYMBOL("CLEAN-UP-WORKSTATION-CONTEXT",AB_package);
    clean_up_workstation_context_for_dragging_state_1 = 
	    STATIC_FUNCTION(clean_up_workstation_context_for_dragging_state,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qclean_up_workstation_context,
	    Qdragging_state,clean_up_workstation_context_for_dragging_state_1);
    Qloose_end = STATIC_SYMBOL("LOOSE-END",AB_package);
    Qmove_image_plane_upon_continuation_after_dragging = 
	    STATIC_SYMBOL("MOVE-IMAGE-PLANE-UPON-CONTINUATION-AFTER-DRAGGING",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmove_image_plane_upon_continuation_after_dragging,
	    STATIC_FUNCTION(move_image_plane_upon_continuation_after_dragging,
	    NIL,FALSE,1,1));
    Qg2_defstruct_structure_name_connection_g2_struct = 
	    STATIC_SYMBOL("CONNECTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qjoined_connections = STATIC_SYMBOL("JOINED-CONNECTIONS",AB_package);
    Qadded_connection_to_block = STATIC_SYMBOL("ADDED-CONNECTION-TO-BLOCK",
	    AB_package);
    Qmade_junction = STATIC_SYMBOL("MADE-JUNCTION",AB_package);
    Qdeleted_stub = STATIC_SYMBOL("DELETED-STUB",AB_package);
    Qconnection_style = STATIC_SYMBOL("CONNECTION-STYLE",AB_package);
    Qdiagonal = STATIC_SYMBOL("DIAGONAL",AB_package);
    Qtable = STATIC_SYMBOL("TABLE",AB_package);
    Qtext_box = STATIC_SYMBOL("TEXT-BOX",AB_package);
    Qdial = STATIC_SYMBOL("DIAL",AB_package);
    Qmeter = STATIC_SYMBOL("METER",AB_package);
    Qbutton = STATIC_SYMBOL("BUTTON",AB_package);
    Qdefinition = STATIC_SYMBOL("DEFINITION",AB_package);
    Qchart = STATIC_SYMBOL("CHART",AB_package);
    Qfreeform_table = STATIC_SYMBOL("FREEFORM-TABLE",AB_package);
    Qtrend_chart = STATIC_SYMBOL("TREND-CHART",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)9L,Qtable,Qtext_box,Qdial,
	    Qmeter,Qbutton,Qdefinition,Qchart,Qfreeform_table,Qtrend_chart);
    Classes_that_do_not_normally_connect = list_constant_3;
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qsuspend_workstation_context = 
	    STATIC_SYMBOL("SUSPEND-WORKSTATION-CONTEXT",AB_package);
    suspend_workstation_context_for_dragging_state_1 = 
	    STATIC_FUNCTION(suspend_workstation_context_for_dragging_state,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qsuspend_workstation_context,
	    Qdragging_state,suspend_workstation_context_for_dragging_state_1);
    Qresume_workstation_context = 
	    STATIC_SYMBOL("RESUME-WORKSTATION-CONTEXT",AB_package);
    resume_workstation_context_for_dragging_state_1 = 
	    STATIC_FUNCTION(resume_workstation_context_for_dragging_state,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qresume_workstation_context,
	    Qdragging_state,resume_workstation_context_for_dragging_state_1);
    Qg2_defstruct_structure_name_move_dragging_state_g2_struct = 
	    STATIC_SYMBOL("MOVE-DRAGGING-STATE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qmove_dragging_state = STATIC_SYMBOL("MOVE-DRAGGING-STATE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_move_dragging_state_g2_struct,
	    Qmove_dragging_state,Qab_name_of_unique_structure_type);
    mutate_global_property(Qmove_dragging_state,
	    Qg2_defstruct_structure_name_move_dragging_state_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_move_dragging_state == UNBOUND)
	The_type_description_of_move_dragging_state = Nil;
    string_constant_13 = 
	    STATIC_STRING("43Dy8m83kuy1o83kuy83-Sy8n8k1l83-Sy0000001m1n8y83-4uy01m8x83-Syknk0k0");
    temp = The_type_description_of_move_dragging_state;
    The_type_description_of_move_dragging_state = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_13));
    mutate_global_property(Qg2_defstruct_structure_name_move_dragging_state_g2_struct,
	    The_type_description_of_move_dragging_state,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qmove_dragging_state,
	    The_type_description_of_move_dragging_state,
	    Qtype_description_of_type);
    Qoutstanding_move_dragging_state_count = 
	    STATIC_SYMBOL("OUTSTANDING-MOVE-DRAGGING-STATE-COUNT",AB_package);
    Qmove_dragging_state_structure_memory_usage = 
	    STATIC_SYMBOL("MOVE-DRAGGING-STATE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_14 = STATIC_STRING("1q83kuy8s83-fly09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_move_dragging_state_count);
    push_optimized_constant(Qmove_dragging_state_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_14));
    Qchain_of_available_move_dragging_states = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-MOVE-DRAGGING-STATES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_move_dragging_states,
	    Chain_of_available_move_dragging_states);
    record_system_variable(Qchain_of_available_move_dragging_states,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qmove_dragging_state_count = STATIC_SYMBOL("MOVE-DRAGGING-STATE-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmove_dragging_state_count,
	    Move_dragging_state_count);
    record_system_variable(Qmove_dragging_state_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_move_dragging_states_vector == UNBOUND)
	Chain_of_available_move_dragging_states_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qmove_dragging_state_structure_memory_usage,
	    STATIC_FUNCTION(move_dragging_state_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_move_dragging_state_count,
	    STATIC_FUNCTION(outstanding_move_dragging_state_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_move_dragging_state_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_move_dragging_state,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qmove_dragging_state,
	    reclaim_structure_for_move_dragging_state_1);
    Qtop_level_is_selection_style = 
	    STATIC_SYMBOL("TOP-LEVEL-IS-SELECTION-STYLE",AB_package);
    mutate_global_property(Qmove_dragging_state,
	    Qtop_level_is_selection_style,
	    Qselection_style_of_workstation_context_type);
    Qmove_dragging = STATIC_SYMBOL("MOVE-DRAGGING",AB_package);
    make_context_description(Qmove_dragging,Qtop_level,Qnil,Qnil);
    Qwrap_up_move_after_drag = STATIC_SYMBOL("WRAP-UP-MOVE-AFTER-DRAG",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrap_up_move_after_drag,
	    STATIC_FUNCTION(wrap_up_move_after_drag,NIL,FALSE,1,1));
    Qg2_defstruct_structure_name_transfer_dragging_state_g2_struct = 
	    STATIC_SYMBOL("TRANSFER-DRAGGING-STATE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qtransfer_dragging_state = STATIC_SYMBOL("TRANSFER-DRAGGING-STATE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_transfer_dragging_state_g2_struct,
	    Qtransfer_dragging_state,Qab_name_of_unique_structure_type);
    mutate_global_property(Qtransfer_dragging_state,
	    Qg2_defstruct_structure_name_transfer_dragging_state_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_transfer_dragging_state == UNBOUND)
	The_type_description_of_transfer_dragging_state = Nil;
    string_constant_15 = 
	    STATIC_STRING("43Dy8m83nwy1o83nwy83-Sy8n8k1l83-Sy0000001m1n8y83-69y01m8x83-Sykqk0k0");
    temp = The_type_description_of_transfer_dragging_state;
    The_type_description_of_transfer_dragging_state = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_15));
    mutate_global_property(Qg2_defstruct_structure_name_transfer_dragging_state_g2_struct,
	    The_type_description_of_transfer_dragging_state,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qtransfer_dragging_state,
	    The_type_description_of_transfer_dragging_state,
	    Qtype_description_of_type);
    Qoutstanding_transfer_dragging_state_count = 
	    STATIC_SYMBOL("OUTSTANDING-TRANSFER-DRAGGING-STATE-COUNT",
	    AB_package);
    Qtransfer_dragging_state_structure_memory_usage = 
	    STATIC_SYMBOL("TRANSFER-DRAGGING-STATE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_16 = STATIC_STRING("1q83nwy8s83-tmy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_transfer_dragging_state_count);
    push_optimized_constant(Qtransfer_dragging_state_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_16));
    Qchain_of_available_transfer_dragging_states = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-TRANSFER-DRAGGING-STATES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_transfer_dragging_states,
	    Chain_of_available_transfer_dragging_states);
    record_system_variable(Qchain_of_available_transfer_dragging_states,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qtransfer_dragging_state_count = 
	    STATIC_SYMBOL("TRANSFER-DRAGGING-STATE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtransfer_dragging_state_count,
	    Transfer_dragging_state_count);
    record_system_variable(Qtransfer_dragging_state_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_transfer_dragging_states_vector == UNBOUND)
	Chain_of_available_transfer_dragging_states_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qtransfer_dragging_state_structure_memory_usage,
	    STATIC_FUNCTION(transfer_dragging_state_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_transfer_dragging_state_count,
	    STATIC_FUNCTION(outstanding_transfer_dragging_state_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_transfer_dragging_state_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_transfer_dragging_state,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qtransfer_dragging_state,
	    reclaim_structure_for_transfer_dragging_state_1);
    mutate_global_property(Qtransfer_dragging_state,
	    Qtop_level_is_selection_style,
	    Qselection_style_of_workstation_context_type);
    Qtransfer_dragging = STATIC_SYMBOL("TRANSFER-DRAGGING",AB_package);
    make_context_description(Qtransfer_dragging,Qtop_level,Qnil,Qnil);
    clean_up_workstation_context_for_transfer_dragging_state_1 = 
	    STATIC_FUNCTION(clean_up_workstation_context_for_transfer_dragging_state,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qclean_up_workstation_context,
	    Qtransfer_dragging_state,
	    clean_up_workstation_context_for_transfer_dragging_state_1);
    Qwrap_up_transfer_after_drag = 
	    STATIC_SYMBOL("WRAP-UP-TRANSFER-AFTER-DRAG",AB_package);
    SET_SYMBOL_FUNCTION(Qwrap_up_transfer_after_drag,
	    STATIC_FUNCTION(wrap_up_transfer_after_drag,NIL,FALSE,1,1));
    string_constant = STATIC_STRING("~a");
    Qtransfer = STATIC_SYMBOL("TRANSFER",AB_package);
    Qedit = STATIC_SYMBOL("EDIT",AB_package);
    string_constant_1 = STATIC_STRING("Recompile the KB\?  (~A)");
    Qlaunch_compile_to_bring_kb_up_to_date_and_return_from_transfer_dragging 
	    = 
	    STATIC_SYMBOL("LAUNCH-COMPILE-TO-BRING-KB-UP-TO-DATE-AND-RETURN-FROM-TRANSFER-DRAGGING",
	    AB_package);
    Qreturn_from_current_workstation_context = 
	    STATIC_SYMBOL("RETURN-FROM-CURRENT-WORKSTATION-CONTEXT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreturn_from_current_workstation_context,
	    STATIC_FUNCTION(return_from_current_workstation_context,NIL,
	    TRUE,1,4));
    Qno_recompile = STATIC_SYMBOL("NO-RECOMPILE",AB_package);
    Qrecompile = STATIC_SYMBOL("RECOMPILE",AB_package);
    SET_SYMBOL_FUNCTION(Qlaunch_compile_to_bring_kb_up_to_date_and_return_from_transfer_dragging,
	    STATIC_FUNCTION(launch_compile_to_bring_kb_up_to_date_and_return_from_transfer_dragging,
	    NIL,FALSE,1,1));
    string_constant_2 = 
	    STATIC_STRING("Cannot transfer items to non-KB workspaces!");
    string_constant_3 = 
	    STATIC_STRING("Cannot place items on their subordinate workspace!");
    string_constant_4 = 
	    STATIC_STRING("Cannot transfer items to proprietary workspaces!");
    string_constant_5 = 
	    STATIC_STRING("Cannot transfer permanent items to transient workspaces!");
    string_constant_6 = STATIC_STRING("Cannot transfer ~NF, because ~A");
    string_constant_7 = STATIC_STRING("Cannot transfer to ~NF, because ~A");
    Qreenter_editor_if_not_hand_placed = 
	    STATIC_SYMBOL("REENTER-EDITOR-IF-NOT-HAND-PLACED",AB_package);
    SET_SYMBOL_FUNCTION(Qreenter_editor_if_not_hand_placed,
	    STATIC_FUNCTION(reenter_editor_if_not_hand_placed,NIL,FALSE,1,1));
    Kxor = STATIC_SYMBOL("XOR",Pkeyword);
    Qwhite = STATIC_SYMBOL("WHITE",AB_package);
    Qblack = STATIC_SYMBOL("BLACK",AB_package);
    Qx11_window = STATIC_SYMBOL("X11-WINDOW",AB_package);
    Qtransparent = STATIC_SYMBOL("TRANSPARENT",AB_package);
    Qbackground = STATIC_SYMBOL("BACKGROUND",AB_package);
    Qforeground = STATIC_SYMBOL("FOREGROUND",AB_package);
    Qworkspace_foreground = STATIC_SYMBOL("WORKSPACE-FOREGROUND",AB_package);
    Qicp = STATIC_SYMBOL("ICP",AB_package);
    Qtelewindows = STATIC_SYMBOL("TELEWINDOWS",AB_package);
    Qprinter = STATIC_SYMBOL("PRINTER",AB_package);
    Kconnection_bleeding = STATIC_SYMBOL("CONNECTION-BLEEDING",Pkeyword);
    Qdraw_blocks_and_connections_being_moved = 
	    STATIC_SYMBOL("DRAW-BLOCKS-AND-CONNECTIONS-BEING-MOVED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdraw_blocks_and_connections_being_moved,
	    STATIC_FUNCTION(draw_blocks_and_connections_being_moved,NIL,
	    FALSE,2,2));
    Selection_highlight_line_width = FIX((SI_Long)3L);
    Qab_dot = STATIC_SYMBOL("DOT",AB_package);
    Qtree_ordering = STATIC_SYMBOL("TREE-ORDERING",AB_package);
    Kdraw_as_late_as_possible = STATIC_SYMBOL("DRAW-AS-LATE-AS-POSSIBLE",
	    Pkeyword);
    if (Transfer_in_progress == UNBOUND)
	Transfer_in_progress = Nil;
    Qsaved_position_or_next_lower_thing = 
	    STATIC_SYMBOL("SAVED-POSITION-OR-NEXT-LOWER-THING",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsaved_position_or_next_lower_thing,
	    Saved_position_or_next_lower_thing);
    record_system_variable(Qsaved_position_or_next_lower_thing,Qmoves,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qjust_erase = STATIC_SYMBOL("JUST-ERASE",AB_package);
    Qworkspace_frame = STATIC_SYMBOL("WORKSPACE-FRAME",AB_package);
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Selection_handle_hit_distance = FIX((SI_Long)4L);
    Qg2_defstruct_structure_name_selection_handle_spot_g2_struct = 
	    STATIC_SYMBOL("SELECTION-HANDLE-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qselection_handle_spot = STATIC_SYMBOL("SELECTION-HANDLE-SPOT",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_selection_handle_spot_g2_struct,
	    Qselection_handle_spot,Qab_name_of_unique_structure_type);
    mutate_global_property(Qselection_handle_spot,
	    Qg2_defstruct_structure_name_selection_handle_spot_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_selection_handle_spot == UNBOUND)
	The_type_description_of_selection_handle_spot = Nil;
    string_constant_17 = 
	    STATIC_STRING("43Dy8m83Zoy1p83Zoy83F=y83Qy8n8k1l83F=y0000001l1m8x83F=yksk0k0");
    temp = The_type_description_of_selection_handle_spot;
    The_type_description_of_selection_handle_spot = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_17));
    mutate_global_property(Qg2_defstruct_structure_name_selection_handle_spot_g2_struct,
	    The_type_description_of_selection_handle_spot,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qselection_handle_spot,
	    The_type_description_of_selection_handle_spot,
	    Qtype_description_of_type);
    Qoutstanding_selection_handle_spot_count = 
	    STATIC_SYMBOL("OUTSTANDING-SELECTION-HANDLE-SPOT-COUNT",
	    AB_package);
    Qselection_handle_spot_structure_memory_usage = 
	    STATIC_SYMBOL("SELECTION-HANDLE-SPOT-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_18 = STATIC_STRING("1q83Zoy8s83-o3y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_selection_handle_spot_count);
    push_optimized_constant(Qselection_handle_spot_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_18));
    Qchain_of_available_selection_handle_spots = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-SELECTION-HANDLE-SPOTS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_selection_handle_spots,
	    Chain_of_available_selection_handle_spots);
    record_system_variable(Qchain_of_available_selection_handle_spots,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qselection_handle_spot_count = 
	    STATIC_SYMBOL("SELECTION-HANDLE-SPOT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qselection_handle_spot_count,
	    Selection_handle_spot_count);
    record_system_variable(Qselection_handle_spot_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_selection_handle_spots_vector == UNBOUND)
	Chain_of_available_selection_handle_spots_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qselection_handle_spot_structure_memory_usage,
	    STATIC_FUNCTION(selection_handle_spot_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_selection_handle_spot_count,
	    STATIC_FUNCTION(outstanding_selection_handle_spot_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_selection_handle_spot_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_selection_handle_spot,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qselection_handle_spot,
	    reclaim_structure_for_selection_handle_spot_1);
    Qinnermost_spot_p = STATIC_SYMBOL("INNERMOST-SPOT-P",AB_package);
    Qenclosing_spot_type = STATIC_SYMBOL("ENCLOSING-SPOT-TYPE",AB_package);
    Qimage_plane_spot = STATIC_SYMBOL("IMAGE-PLANE-SPOT",AB_package);
    Qabstract_type = STATIC_SYMBOL("ABSTRACT-TYPE",AB_package);
    Qtype_of_frame_represented = STATIC_SYMBOL("TYPE-OF-FRAME-REPRESENTED",
	    AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qselection_handle_spot),
	    Qtype_description_of_type);
    svref_new_value = list_star(5,LIST_2(Qinnermost_spot_p,Qt),
	    LIST_2(Qenclosing_spot_type,Qimage_plane_spot),
	    LIST_2(Qabstract_type,Qnil),LIST_2(Qtype_of_frame_represented,
	    Qitem),ISVREF(type_description,(SI_Long)10L));
    SVREF(type_description,FIX((SI_Long)10L)) = svref_new_value;
    Qvertex = STATIC_SYMBOL("VERTEX",AB_package);
    Qsize_all = STATIC_SYMBOL("SIZE-ALL",AB_package);
    Qresize = STATIC_SYMBOL("RESIZE",AB_package);
    Qtop = STATIC_SYMBOL("TOP",AB_package);
    Qbottom = STATIC_SYMBOL("BOTTOM",AB_package);
    Qsize_ns = STATIC_SYMBOL("SIZE-NS",AB_package);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    Qsize_we = STATIC_SYMBOL("SIZE-WE",AB_package);
    Qtop_left = STATIC_SYMBOL("TOP-LEFT",AB_package);
    Qbottom_right = STATIC_SYMBOL("BOTTOM-RIGHT",AB_package);
    Qsize_nw_se = STATIC_SYMBOL("SIZE-NW-SE",AB_package);
    Qtop_right = STATIC_SYMBOL("TOP-RIGHT",AB_package);
    Qbottom_left = STATIC_SYMBOL("BOTTOM-LEFT",AB_package);
    Qsize_ne_sw = STATIC_SYMBOL("SIZE-NE-SW",AB_package);
    Qdefault = STATIC_SYMBOL("DEFAULT",AB_package);
    Selection_handle_radius = FIX((SI_Long)3L);
    Qselection_handle_icon = STATIC_SYMBOL("SELECTION-HANDLE-ICON",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qselection_handle_icon,Selection_handle_icon);
    Qmake_iconic_entity_with_specific_icon_description = 
	    STATIC_SYMBOL("MAKE-ICONIC-ENTITY-WITH-SPECIFIC-ICON-DESCRIPTION",
	    AB_package);
    Qpolychrome = STATIC_SYMBOL("POLYCHROME",AB_package);
    list_constant_4 = STATIC_CONS(Qfill,Qbackground);
    Qline = STATIC_SYMBOL("LINE",AB_package);
    list_constant_5 = STATIC_CONS(Qline,Qforeground);
    list_constant_12 = STATIC_LIST((SI_Long)3L,Qpolychrome,list_constant_4,
	    list_constant_5);
    Qsolid_rectangle = STATIC_SYMBOL("SOLID-RECTANGLE",AB_package);
    list_constant_6 = STATIC_CONS(FIX((SI_Long)0L),Qnil);
    list_constant_8 = STATIC_CONS(FIX((SI_Long)0L),list_constant_6);
    list_constant_7 = STATIC_CONS(FIX((SI_Long)6L),Qnil);
    list_constant_9 = STATIC_CONS(FIX((SI_Long)6L),list_constant_7);
    list_constant_13 = STATIC_LIST((SI_Long)3L,Qsolid_rectangle,
	    list_constant_8,list_constant_9);
    Qoutline = STATIC_SYMBOL("OUTLINE",AB_package);
    list_constant_10 = STATIC_CONS(FIX((SI_Long)0L),list_constant_7);
    list_constant_11 = STATIC_CONS(FIX((SI_Long)6L),list_constant_6);
    list_constant_14 = STATIC_LIST((SI_Long)5L,Qoutline,list_constant_8,
	    list_constant_10,list_constant_9,list_constant_11);
    list_constant_15 = STATIC_LIST((SI_Long)5L,list_constant_12,Qfill,
	    list_constant_13,Qline,list_constant_14);
    list_constant_16 = STATIC_CONS(Qnil,Qnil);
    list_constant_17 = STATIC_LIST_STAR((SI_Long)6L,Kfuncall,
	    Qmake_iconic_entity_with_specific_icon_description,
	    list_constant_15,FIX((SI_Long)6L),FIX((SI_Long)6L),
	    list_constant_16);
    Qreclaim_rubber_stamp_widgets = 
	    STATIC_SYMBOL("RECLAIM-RUBBER-STAMP-WIDGETS",AB_package);
    record_system_variable(Qselection_handle_icon,Qmoves,list_constant_17,
	    Qnil,Qnil,Qreclaim_rubber_stamp_widgets,Qt);
    Qshow_selection_handles = STATIC_SYMBOL("SHOW-SELECTION-HANDLES",
	    AB_package);
    Qicon_color_pattern = STATIC_SYMBOL("ICON-COLOR-PATTERN",AB_package);
    Qred = STATIC_SYMBOL("RED",AB_package);
    Qg2_defstruct_structure_name_drag_handle_state_g2_struct = 
	    STATIC_SYMBOL("DRAG-HANDLE-STATE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qdrag_handle_state = STATIC_SYMBOL("DRAG-HANDLE-STATE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_drag_handle_state_g2_struct,
	    Qdrag_handle_state,Qab_name_of_unique_structure_type);
    mutate_global_property(Qdrag_handle_state,
	    Qg2_defstruct_structure_name_drag_handle_state_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_drag_handle_state == UNBOUND)
	The_type_description_of_drag_handle_state = Nil;
    string_constant_19 = 
	    STATIC_STRING("43Dy8m83gmy1o83gmy83-Sy8n8k1l83-Sy0000001m1m8y83-3Qy1m8x83-Sykvk0k0");
    temp = The_type_description_of_drag_handle_state;
    The_type_description_of_drag_handle_state = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_19));
    mutate_global_property(Qg2_defstruct_structure_name_drag_handle_state_g2_struct,
	    The_type_description_of_drag_handle_state,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qdrag_handle_state,
	    The_type_description_of_drag_handle_state,
	    Qtype_description_of_type);
    Qoutstanding_drag_handle_state_count = 
	    STATIC_SYMBOL("OUTSTANDING-DRAG-HANDLE-STATE-COUNT",AB_package);
    Qdrag_handle_state_structure_memory_usage = 
	    STATIC_SYMBOL("DRAG-HANDLE-STATE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_20 = STATIC_STRING("1q83gmy8s83-Rty09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_drag_handle_state_count);
    push_optimized_constant(Qdrag_handle_state_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_20));
    Qchain_of_available_drag_handle_states = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-DRAG-HANDLE-STATES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_drag_handle_states,
	    Chain_of_available_drag_handle_states);
    record_system_variable(Qchain_of_available_drag_handle_states,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qdrag_handle_state_count = STATIC_SYMBOL("DRAG-HANDLE-STATE-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdrag_handle_state_count,
	    Drag_handle_state_count);
    record_system_variable(Qdrag_handle_state_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_drag_handle_states_vector == UNBOUND)
	Chain_of_available_drag_handle_states_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qdrag_handle_state_structure_memory_usage,
	    STATIC_FUNCTION(drag_handle_state_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_drag_handle_state_count,
	    STATIC_FUNCTION(outstanding_drag_handle_state_count,NIL,FALSE,
	    0,0));
    reclaim_structure_for_drag_handle_state_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_drag_handle_state,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qdrag_handle_state,
	    reclaim_structure_for_drag_handle_state_1);
    mutate_global_property(Qdrag_handle_state,
	    Qtop_level_with_mouse_tracking_is_selection_style,
	    Qselection_style_of_workstation_context_type);
    Qdrag_handle = STATIC_SYMBOL("DRAG-HANDLE",AB_package);
    make_context_description(Qdrag_handle,Qtop_level,Qnil,Qnil);
    Qtrack_mouse_for_drag_handle = 
	    STATIC_SYMBOL("TRACK-MOUSE-FOR-DRAG-HANDLE",AB_package);
    Qfinish_drag_handle = STATIC_SYMBOL("FINISH-DRAG-HANDLE",AB_package);
    string_constant_21 = 
	    STATIC_STRING("1p1n830+y8k9k1n830Dy8k9l1n830-y8k9l1n831-y8k9m1n30My8k9m");
    clear_optimized_constants();
    push_optimized_constant(Qtrack_mouse_for_drag_handle);
    push_optimized_constant(Qfinish_drag_handle);
    push_optimized_constant(Qabort_workstation_context);
    make_keymap(Qdrag_handle,Qdrag_handle,
	    regenerate_optimized_constant(string_constant_21),Qinternal,
	    Qnil,Qnil,Qnil,Qnil);
    add_keymap_to_workstation_context(Qdrag_handle,Qdrag_handle);
    valid_workstation_context_p_for_drag_handle_state_1 = 
	    STATIC_FUNCTION(valid_workstation_context_p_for_drag_handle_state,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qvalid_workstation_context_p,
	    Qdrag_handle_state,
	    valid_workstation_context_p_for_drag_handle_state_1);
    clean_up_workstation_context_for_drag_handle_state_1 = 
	    STATIC_FUNCTION(clean_up_workstation_context_for_drag_handle_state,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qclean_up_workstation_context,
	    Qdrag_handle_state,
	    clean_up_workstation_context_for_drag_handle_state_1);
    mutate_global_property(Qtrack_mouse_for_drag_handle,
	    Qtrack_mouse_for_drag_handle,Qnew_style_event_handler);
    SET_SYMBOL_FUNCTION(Qtrack_mouse_for_drag_handle,
	    STATIC_FUNCTION(track_mouse_for_drag_handle,NIL,FALSE,1,1));
    mutate_global_property(Qfinish_drag_handle,Qfinish_drag_handle,
	    Qnew_style_event_handler);
    SET_SYMBOL_FUNCTION(Qfinish_drag_handle,
	    STATIC_FUNCTION(finish_drag_handle,NIL,FALSE,1,1));
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    float_constant = STATIC_FLOAT(0.0);
    Qis_resized_by_the_user = STATIC_SYMBOL("IS-RESIZED-BY-THE-USER",
	    AB_package);
}
