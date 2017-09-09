/* token.c
 * Input file:  token.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "token.h"


DEFINE_VARIABLE_WITH_SYMBOL(Available_token_conses, Qavailable_token_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_token_conses_tail, Qavailable_token_conses_tail);

Object Available_token_conses_vector = UNBOUND;

Object Available_token_conses_tail_vector = UNBOUND;

Object Token_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Token_cons_counter, Qtoken_cons_counter);

/* OUTSTANDING-TOKEN-CONSES */
Object outstanding_token_conses()
{
    Object temp;

    x_note_fn_call(31,0);
    temp = FIXNUM_MINUS(Token_cons_counter,length(Available_token_conses));
    return VALUES_1(temp);
}

/* TOKEN-CONS-MEMORY-USAGE */
Object token_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(31,1);
    temp = FIXNUM_TIMES(Token_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-TOKEN-CONS-POOL */
Object replenish_token_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(31,2);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qtoken_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_token_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_token_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_token_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_token_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_token_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Token_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qtoken;              /* token */

/* TOKEN-CONS-1 */
Object token_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(31,3);
    new_cons = ISVREF(Available_token_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_token_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_token_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_token_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_token_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qtoken);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-TOKEN-LIST-POOL */
Object replenish_token_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(31,4);
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
    if (ISVREF(Available_token_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_token_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_token_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_token_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_token_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qtoken_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-TOKEN-LIST-1 */
Object make_token_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(31,5);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_token_conses_vector,
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
	replenish_token_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_token_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qtoken);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_token_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_token_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_token_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_token_conses_tail_vector;
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

/* TOKEN-LIST-2 */
Object token_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(31,6);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_token_conses_vector,IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_token_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_token_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qtoken);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_token_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_token_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_token_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_token_conses_tail_vector;
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

/* TOKEN-LIST-3 */
Object token_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(31,7);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_token_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_token_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_token_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qtoken);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_token_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_token_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_token_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_token_conses_tail_vector;
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

/* TOKEN-LIST-4 */
Object token_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(31,8);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_token_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_token_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_token_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qtoken);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_token_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_token_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_token_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_token_conses_tail_vector;
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

/* TOKEN-LIST-TRACE-HOOK */
Object token_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(31,9);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-TOKEN-CONSES-1 */
Object copy_tree_using_token_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(31,10);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_token_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_token_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_token_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_token_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_token_cons_pool();
	temp_1 = copy_tree_using_token_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qtoken);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_token_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_token_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_token_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_token_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_token_cons_pool();
	temp_1 = copy_tree_using_token_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qtoken);
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

/* COPY-LIST-USING-TOKEN-CONSES-1 */
Object copy_list_using_token_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(31,11);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_token_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_token_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_token_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_token_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_token_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qtoken);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_token_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_token_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_token_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_token_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_token_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qtoken);
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

/* RECLAIM-TOKEN-CONS-1 */
Object reclaim_token_cons_1(token_cons)
    Object token_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(31,12);
    inline_note_reclaim_cons(token_cons,Qtoken);
    if (ISVREF(Available_token_conses_tail_vector,
		IFIX(Current_thread_index))) {
	temp = ISVREF(Available_token_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = token_cons;
	temp = Available_token_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = token_cons;
    }
    else {
	temp = Available_token_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = token_cons;
	temp = Available_token_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = token_cons;
    }
    M_CDR(token_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-TOKEN-LIST-1 */
Object reclaim_token_list_1(token_list)
    Object token_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(31,13);
    if (token_list) {
	last_1 = token_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qtoken);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qtoken);
	if (ISVREF(Available_token_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_token_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = token_list;
	    temp = Available_token_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_token_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = token_list;
	    temp = Available_token_conses_tail_vector;
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

/* RECLAIM-TOKEN-LIST*-1 */
Object reclaim_token_list_star_1(token_list)
    Object token_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(31,14);
    if (CONSP(token_list)) {
	temp = last(token_list,_);
	M_CDR(temp) = Nil;
	if (token_list) {
	    last_1 = token_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qtoken);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qtoken);
	    if (ISVREF(Available_token_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_token_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = token_list;
		temp = Available_token_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_token_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = token_list;
		temp = Available_token_conses_tail_vector;
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

/* RECLAIM-TOKEN-TREE-1 */
Object reclaim_token_tree_1(tree)
    Object tree;
{
    Object e, e2, token_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(31,15);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_token_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		token_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(token_cons,Qtoken);
		if (EQ(token_cons,e))
		    goto end_1;
		else if ( !TRUEP(token_cons))
		    goto end_1;
		else
		    token_cons = CDR(token_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_token_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_token_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_token_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_token_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_token_conses_tail_vector;
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

/* DELETE-TOKEN-ELEMENT-1 */
Object delete_token_element_1(element,token_list)
    Object element, token_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(31,16);
    if (token_list) {
	if (EQ(element,M_CAR(token_list))) {
	    temp = CDR(token_list);
	    inline_note_reclaim_cons(token_list,Qtoken);
	    if (ISVREF(Available_token_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_token_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = token_list;
		temp_1 = Available_token_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = token_list;
	    }
	    else {
		temp_1 = Available_token_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = token_list;
		temp_1 = Available_token_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = token_list;
	    }
	    M_CDR(token_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = token_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qtoken);
		if (ISVREF(Available_token_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_token_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_token_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_token_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_token_conses_tail_vector;
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
	    temp = token_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-TOKEN-CONS-1 */
Object delete_token_cons_1(token_cons,token_list)
    Object token_cons, token_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(31,17);
    if (EQ(token_cons,token_list))
	temp = CDR(token_list);
    else {
	l_trailer_qm = Nil;
	l = token_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,token_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = token_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_token_cons_1(token_cons);
    return VALUES_1(temp);
}

/* TOKEN-REVERSE */
Object token_reverse(list_1)
    Object list_1;
{
    Object new_list, element, ab_loop_list_, temp;

    x_note_fn_call(31,18);
    new_list = Qnil;
    element = Nil;
    ab_loop_list_ = list_1;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    new_list = token_cons_1(element,new_list);
    goto next_loop;
  end_loop:
    temp = new_list;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

Object The_type_description_of_lexing_table = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_lexing_tables, Qchain_of_available_lexing_tables);

DEFINE_VARIABLE_WITH_SYMBOL(Lexing_table_count, Qlexing_table_count);

Object Chain_of_available_lexing_tables_vector = UNBOUND;

/* LEXING-TABLE-STRUCTURE-MEMORY-USAGE */
Object lexing_table_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(31,19);
    temp = Lexing_table_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)4L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-LEXING-TABLE-COUNT */
Object outstanding_lexing_table_count()
{
    Object def_structure_lexing_table_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(31,20);
    gensymed_symbol = IFIX(Lexing_table_count);
    def_structure_lexing_table_variable = Chain_of_available_lexing_tables;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_lexing_table_variable))
	goto end_loop;
    def_structure_lexing_table_variable = 
	    ISVREF(def_structure_lexing_table_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-LEXING-TABLE-1 */
Object reclaim_lexing_table_1(lexing_table)
    Object lexing_table;
{
    Object temp, svref_arg_2;

    x_note_fn_call(31,21);
    inline_note_reclaim_cons(lexing_table,Nil);
    temp = ISVREF(Chain_of_available_lexing_tables_vector,
	    IFIX(Current_thread_index));
    SVREF(lexing_table,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_lexing_tables_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = lexing_table;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-LEXING-TABLE */
Object reclaim_structure_for_lexing_table(lexing_table)
    Object lexing_table;
{
    x_note_fn_call(31,22);
    return reclaim_lexing_table_1(lexing_table);
}

static Object Qg2_defstruct_structure_name_lexing_table_g2_struct;  /* g2-defstruct-structure-name::lexing-table-g2-struct */

/* MAKE-PERMANENT-LEXING-TABLE-STRUCTURE-INTERNAL */
Object make_permanent_lexing_table_structure_internal()
{
    Object def_structure_lexing_table_variable;
    Object defstruct_g2_lexing_table_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(31,23);
    def_structure_lexing_table_variable = Nil;
    atomic_incff_symval(Qlexing_table_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_lexing_table_variable = Nil;
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
	defstruct_g2_lexing_table_variable = the_array;
	SVREF(defstruct_g2_lexing_table_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_lexing_table_g2_struct;
	def_structure_lexing_table_variable = 
		defstruct_g2_lexing_table_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_lexing_table_variable);
}

/* MAKE-LEXING-TABLE-1 */
Object make_lexing_table_1()
{
    Object def_structure_lexing_table_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(31,24);
    def_structure_lexing_table_variable = 
	    ISVREF(Chain_of_available_lexing_tables_vector,
	    IFIX(Current_thread_index));
    if (def_structure_lexing_table_variable) {
	svref_arg_1 = Chain_of_available_lexing_tables_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_lexing_table_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_lexing_table_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_lexing_table_g2_struct;
    }
    else
	def_structure_lexing_table_variable = 
		make_permanent_lexing_table_structure_internal();
    inline_note_allocate_cons(def_structure_lexing_table_variable,Nil);
    SVREF(def_structure_lexing_table_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_lexing_table_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_lexing_table_variable,FIX((SI_Long)3L)) = Nil;
    return VALUES_1(def_structure_lexing_table_variable);
}

Object The_type_description_of_internal_token = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_internal_tokens, Qchain_of_available_internal_tokens);

DEFINE_VARIABLE_WITH_SYMBOL(Internal_token_count, Qinternal_token_count);

Object Chain_of_available_internal_tokens_vector = UNBOUND;

/* INTERNAL-TOKEN-STRUCTURE-MEMORY-USAGE */
Object internal_token_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(31,25);
    temp = Internal_token_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)4L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-INTERNAL-TOKEN-COUNT */
Object outstanding_internal_token_count()
{
    Object def_structure_internal_token_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(31,26);
    gensymed_symbol = IFIX(Internal_token_count);
    def_structure_internal_token_variable = Chain_of_available_internal_tokens;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_internal_token_variable))
	goto end_loop;
    def_structure_internal_token_variable = 
	    ISVREF(def_structure_internal_token_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-INTERNAL-TOKEN-1 */
Object reclaim_internal_token_1(internal_token)
    Object internal_token;
{
    Object temp, svref_arg_2;

    x_note_fn_call(31,27);
    inline_note_reclaim_cons(internal_token,Nil);
    temp = ISVREF(Chain_of_available_internal_tokens_vector,
	    IFIX(Current_thread_index));
    SVREF(internal_token,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_internal_tokens_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = internal_token;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-INTERNAL-TOKEN */
Object reclaim_structure_for_internal_token(internal_token)
    Object internal_token;
{
    x_note_fn_call(31,28);
    return reclaim_internal_token_1(internal_token);
}

static Object Qg2_defstruct_structure_name_internal_token_g2_struct;  /* g2-defstruct-structure-name::internal-token-g2-struct */

/* MAKE-PERMANENT-INTERNAL-TOKEN-STRUCTURE-INTERNAL */
Object make_permanent_internal_token_structure_internal()
{
    Object def_structure_internal_token_variable;
    Object defstruct_g2_internal_token_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(31,29);
    def_structure_internal_token_variable = Nil;
    atomic_incff_symval(Qinternal_token_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_internal_token_variable = Nil;
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
	defstruct_g2_internal_token_variable = the_array;
	SVREF(defstruct_g2_internal_token_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_internal_token_g2_struct;
	def_structure_internal_token_variable = 
		defstruct_g2_internal_token_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_internal_token_variable);
}

static Object Qalphabet_normalized_symbol_from_text_string;  /* alphabet-normalized-symbol-from-text-string */

/* MAKE-INTERNAL-TOKEN-1 */
Object make_internal_token_1()
{
    Object def_structure_internal_token_variable, temp, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(31,30);
    def_structure_internal_token_variable = 
	    ISVREF(Chain_of_available_internal_tokens_vector,
	    IFIX(Current_thread_index));
    if (def_structure_internal_token_variable) {
	temp = Chain_of_available_internal_tokens_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_internal_token_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_internal_token_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_internal_token_g2_struct;
    }
    else
	def_structure_internal_token_variable = 
		make_permanent_internal_token_structure_internal();
    inline_note_allocate_cons(def_structure_internal_token_variable,Nil);
    SVREF(def_structure_internal_token_variable,FIX((SI_Long)1L)) = Nil;
    temp = SYMBOL_FUNCTION(Qalphabet_normalized_symbol_from_text_string);
    SVREF(def_structure_internal_token_variable,FIX((SI_Long)2L)) = temp;
    SVREF(def_structure_internal_token_variable,FIX((SI_Long)3L)) = Nil;
    return VALUES_1(def_structure_internal_token_variable);
}

Object The_type_description_of_fsm_state = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_fsm_states, Qchain_of_available_fsm_states);

DEFINE_VARIABLE_WITH_SYMBOL(Fsm_state_count, Qfsm_state_count);

Object Chain_of_available_fsm_states_vector = UNBOUND;

/* FSM-STATE-STRUCTURE-MEMORY-USAGE */
Object fsm_state_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(31,31);
    temp = Fsm_state_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)4L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-FSM-STATE-COUNT */
Object outstanding_fsm_state_count()
{
    Object def_structure_fsm_state_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(31,32);
    gensymed_symbol = IFIX(Fsm_state_count);
    def_structure_fsm_state_variable = Chain_of_available_fsm_states;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_fsm_state_variable))
	goto end_loop;
    def_structure_fsm_state_variable = 
	    ISVREF(def_structure_fsm_state_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-FSM-STATE-1 */
Object reclaim_fsm_state_1(fsm_state)
    Object fsm_state;
{
    Object temp, svref_arg_2;

    x_note_fn_call(31,33);
    inline_note_reclaim_cons(fsm_state,Nil);
    temp = ISVREF(Chain_of_available_fsm_states_vector,
	    IFIX(Current_thread_index));
    SVREF(fsm_state,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_fsm_states_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = fsm_state;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-FSM-STATE */
Object reclaim_structure_for_fsm_state(fsm_state)
    Object fsm_state;
{
    x_note_fn_call(31,34);
    return reclaim_fsm_state_1(fsm_state);
}

static Object Qg2_defstruct_structure_name_fsm_state_g2_struct;  /* g2-defstruct-structure-name::fsm-state-g2-struct */

/* MAKE-PERMANENT-FSM-STATE-STRUCTURE-INTERNAL */
Object make_permanent_fsm_state_structure_internal()
{
    Object def_structure_fsm_state_variable, defstruct_g2_fsm_state_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(31,35);
    def_structure_fsm_state_variable = Nil;
    atomic_incff_symval(Qfsm_state_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_fsm_state_variable = Nil;
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
	defstruct_g2_fsm_state_variable = the_array;
	SVREF(defstruct_g2_fsm_state_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_fsm_state_g2_struct;
	def_structure_fsm_state_variable = defstruct_g2_fsm_state_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_fsm_state_variable);
}

/* MAKE-FSM-STATE-1 */
Object make_fsm_state_1()
{
    Object def_structure_fsm_state_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(31,36);
    def_structure_fsm_state_variable = 
	    ISVREF(Chain_of_available_fsm_states_vector,
	    IFIX(Current_thread_index));
    if (def_structure_fsm_state_variable) {
	svref_arg_1 = Chain_of_available_fsm_states_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_fsm_state_variable,(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_fsm_state_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_fsm_state_g2_struct;
    }
    else
	def_structure_fsm_state_variable = 
		make_permanent_fsm_state_structure_internal();
    inline_note_allocate_cons(def_structure_fsm_state_variable,Nil);
    SVREF(def_structure_fsm_state_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_fsm_state_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_fsm_state_variable,FIX((SI_Long)3L)) = Nil;
    return VALUES_1(def_structure_fsm_state_variable);
}

Object The_type_description_of_state_transition = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_state_transitions, Qchain_of_available_state_transitions);

DEFINE_VARIABLE_WITH_SYMBOL(State_transition_count, Qstate_transition_count);

Object Chain_of_available_state_transitions_vector = UNBOUND;

/* STATE-TRANSITION-STRUCTURE-MEMORY-USAGE */
Object state_transition_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(31,37);
    temp = State_transition_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-STATE-TRANSITION-COUNT */
Object outstanding_state_transition_count()
{
    Object def_structure_state_transition_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(31,38);
    gensymed_symbol = IFIX(State_transition_count);
    def_structure_state_transition_variable = 
	    Chain_of_available_state_transitions;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_state_transition_variable))
	goto end_loop;
    def_structure_state_transition_variable = 
	    ISVREF(def_structure_state_transition_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-STATE-TRANSITION-1 */
Object reclaim_state_transition_1(state_transition)
    Object state_transition;
{
    Object temp, svref_arg_2;

    x_note_fn_call(31,39);
    inline_note_reclaim_cons(state_transition,Nil);
    temp = ISVREF(Chain_of_available_state_transitions_vector,
	    IFIX(Current_thread_index));
    SVREF(state_transition,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_state_transitions_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = state_transition;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-STATE-TRANSITION */
Object reclaim_structure_for_state_transition(state_transition)
    Object state_transition;
{
    x_note_fn_call(31,40);
    return reclaim_state_transition_1(state_transition);
}

static Object Qg2_defstruct_structure_name_state_transition_g2_struct;  /* g2-defstruct-structure-name::state-transition-g2-struct */

/* MAKE-PERMANENT-STATE-TRANSITION-STRUCTURE-INTERNAL */
Object make_permanent_state_transition_structure_internal()
{
    Object def_structure_state_transition_variable;
    Object defstruct_g2_state_transition_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(31,41);
    def_structure_state_transition_variable = Nil;
    atomic_incff_symval(Qstate_transition_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_state_transition_variable = Nil;
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
	defstruct_g2_state_transition_variable = the_array;
	SVREF(defstruct_g2_state_transition_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_state_transition_g2_struct;
	def_structure_state_transition_variable = 
		defstruct_g2_state_transition_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_state_transition_variable);
}

/* MAKE-STATE-TRANSITION-1 */
Object make_state_transition_1()
{
    Object def_structure_state_transition_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(31,42);
    def_structure_state_transition_variable = 
	    ISVREF(Chain_of_available_state_transitions_vector,
	    IFIX(Current_thread_index));
    if (def_structure_state_transition_variable) {
	svref_arg_1 = Chain_of_available_state_transitions_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_state_transition_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_state_transition_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_state_transition_g2_struct;
    }
    else
	def_structure_state_transition_variable = 
		make_permanent_state_transition_structure_internal();
    inline_note_allocate_cons(def_structure_state_transition_variable,Nil);
    SVREF(def_structure_state_transition_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_state_transition_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_state_transition_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_state_transition_variable,FIX((SI_Long)4L)) = 
	    State_transition_user_defined_transition_test_sentinel;
    SVREF(def_structure_state_transition_variable,FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_state_transition_variable);
}

Object The_type_description_of_parse_object = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_parse_objects, Qchain_of_available_parse_objects);

DEFINE_VARIABLE_WITH_SYMBOL(Parse_object_count, Qparse_object_count);

Object Chain_of_available_parse_objects_vector = UNBOUND;

/* PARSE-OBJECT-STRUCTURE-MEMORY-USAGE */
Object parse_object_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(31,43);
    temp = Parse_object_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)5L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-PARSE-OBJECT-COUNT */
Object outstanding_parse_object_count()
{
    Object def_structure_parse_object_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(31,44);
    gensymed_symbol = IFIX(Parse_object_count);
    def_structure_parse_object_variable = Chain_of_available_parse_objects;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_parse_object_variable))
	goto end_loop;
    def_structure_parse_object_variable = 
	    ISVREF(def_structure_parse_object_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-PARSE-OBJECT-1 */
Object reclaim_parse_object_1(parse_object)
    Object parse_object;
{
    Object temp, svref_arg_2;

    x_note_fn_call(31,45);
    inline_note_reclaim_cons(parse_object,Nil);
    temp = ISVREF(Chain_of_available_parse_objects_vector,
	    IFIX(Current_thread_index));
    SVREF(parse_object,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_parse_objects_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = parse_object;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-PARSE-OBJECT */
Object reclaim_structure_for_parse_object(parse_object)
    Object parse_object;
{
    x_note_fn_call(31,46);
    return reclaim_parse_object_1(parse_object);
}

static Object Qg2_defstruct_structure_name_parse_object_g2_struct;  /* g2-defstruct-structure-name::parse-object-g2-struct */

/* MAKE-PERMANENT-PARSE-OBJECT-STRUCTURE-INTERNAL */
Object make_permanent_parse_object_structure_internal()
{
    Object def_structure_parse_object_variable;
    Object defstruct_g2_parse_object_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(31,47);
    def_structure_parse_object_variable = Nil;
    atomic_incff_symval(Qparse_object_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_parse_object_variable = Nil;
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
	defstruct_g2_parse_object_variable = the_array;
	SVREF(defstruct_g2_parse_object_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_parse_object_g2_struct;
	def_structure_parse_object_variable = 
		defstruct_g2_parse_object_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_parse_object_variable);
}

/* MAKE-PARSE-OBJECT-1 */
Object make_parse_object_1()
{
    Object def_structure_parse_object_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(31,48);
    def_structure_parse_object_variable = 
	    ISVREF(Chain_of_available_parse_objects_vector,
	    IFIX(Current_thread_index));
    if (def_structure_parse_object_variable) {
	svref_arg_1 = Chain_of_available_parse_objects_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_parse_object_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_parse_object_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_parse_object_g2_struct;
    }
    else
	def_structure_parse_object_variable = 
		make_permanent_parse_object_structure_internal();
    inline_note_allocate_cons(def_structure_parse_object_variable,Nil);
    SVREF(def_structure_parse_object_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_parse_object_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_parse_object_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_parse_object_variable,FIX((SI_Long)4L)) = Nil;
    return VALUES_1(def_structure_parse_object_variable);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_lexing_rule_number, Qcurrent_lexing_rule_number);

DEFINE_VARIABLE_WITH_SYMBOL(Current_character, Qcurrent_character);

/* EMPTY-LEXING-TABLE */
Object empty_lexing_table()
{
    Object current_lexing_rule_number, empty_lexer, root_node, temp;
    Declare_special(1);

    x_note_fn_call(31,49);
    current_lexing_rule_number = FIX((SI_Long)0L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_lexing_rule_number,Qcurrent_lexing_rule_number,current_lexing_rule_number,
	    0);
      empty_lexer = make_lexing_table_1();
      root_node = create_fsm_state();
      SVREF(empty_lexer,FIX((SI_Long)1L)) = root_node;
      temp = empty_lexer;
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* CREATE-FSM-STATE */
Object create_fsm_state()
{
    Object new_state, svref_new_value;

    x_note_fn_call(31,50);
    new_state = make_fsm_state_1();
    svref_new_value = token_cons_1(Current_lexing_rule_number,Nil);
    SVREF(new_state,FIX((SI_Long)1L)) = svref_new_value;
    SVREF(new_state,FIX((SI_Long)2L)) = Nil;
    return VALUES_1(new_state);
}

/* CREATE-STANDARD-STATE-TRANSITION */
Object create_standard_state_transition(test,args,next)
    Object test, args, next;
{
    Object the_transition, index_1, specific, ab_loop_list_, ab_loop_desetq_;
    Object temp, svref_new_value, arg_count;

    x_note_fn_call(31,51);
    the_transition = make_state_transition_1();
    SVREF(the_transition,FIX((SI_Long)1L)) = test;
    SVREF(the_transition,FIX((SI_Long)2L)) = args;
    SVREF(the_transition,FIX((SI_Long)3L)) = next;
    index_1 = Nil;
    specific = Nil;
    ab_loop_list_ = Alphabet_standard_state_transition_tests;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    index_1 = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    specific = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(test,specific)) {
	svref_new_value = index_1;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    svref_new_value = FIX((SI_Long)-1L);
    goto end_1;
    svref_new_value = Qnil;
  end_1:;
    SVREF(the_transition,FIX((SI_Long)4L)) = svref_new_value;
    arg_count = length(args);
    if (FIXNUM_GT(arg_count,Maximum_state_transition_args))
	error((SI_Long)1L,"Too many state transition arguments");
    SVREF(the_transition,FIX((SI_Long)5L)) = arg_count;
    return VALUES_1(the_transition);
}

/* CREATE-NONSTANDARD-STATE-TRANSITION */
Object create_nonstandard_state_transition(test,args,next)
    Object test, args, next;
{
    Object the_transition, arg_count;

    x_note_fn_call(31,52);
    the_transition = make_state_transition_1();
    SVREF(the_transition,FIX((SI_Long)1L)) = test;
    SVREF(the_transition,FIX((SI_Long)2L)) = args;
    SVREF(the_transition,FIX((SI_Long)3L)) = next;
    SVREF(the_transition,FIX((SI_Long)4L)) = 
	    State_transition_user_defined_transition_test_sentinel;
    arg_count = length(args);
    if (FIXNUM_GT(arg_count,Maximum_state_transition_args))
	error((SI_Long)1L,"Too many state transition arguments");
    SVREF(the_transition,FIX((SI_Long)5L)) = arg_count;
    return VALUES_1(the_transition);
}

/* CREATE-EPSILON-STATE-TRANSITION */
Object create_epsilon_state_transition(next)
    Object next;
{
    Object the_transition;

    x_note_fn_call(31,53);
    the_transition = make_state_transition_1();
    SVREF(the_transition,FIX((SI_Long)1L)) = Nil;
    SVREF(the_transition,FIX((SI_Long)2L)) = Nil;
    SVREF(the_transition,FIX((SI_Long)3L)) = next;
    SVREF(the_transition,FIX((SI_Long)4L)) = 
	    State_transition_user_defined_transition_test_sentinel;
    ISVREF(the_transition,(SI_Long)5L) = FIX((SI_Long)0L);
    return VALUES_1(the_transition);
}

/* RECLAIM-TRANSITION */
Object reclaim_transition(transition)
    Object transition;
{
    Object args, temp;

    x_note_fn_call(31,54);
    args = ISVREF(transition,(SI_Long)2L);
    if (CONSP(args))
	reclaim_token_tree_1(args);
    temp = reclaim_state_transition_1(transition);
    return VALUES_1(temp);
}

/* TRANSITION= */
Object transition_eq(transition_1,transition_2)
    Object transition_1, transition_2;
{
    Object temp, temp_1;

    x_note_fn_call(31,55);
    if (transition_2 && EQ(ISVREF(transition_1,(SI_Long)1L),
	    ISVREF(transition_2,(SI_Long)1L)) && EQ(ISVREF(transition_1,
	    (SI_Long)3L),ISVREF(transition_2,(SI_Long)3L))) {
	temp = ISVREF(transition_1,(SI_Long)2L);
	temp_1 = ISVREF(transition_2,(SI_Long)2L);
	temp_1 = EQUAL(temp,temp_1) ? T : Nil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* REPLICATE-TRANSITION */
Object replicate_transition(old_transition,new_destination)
    Object old_transition, new_destination;
{
    Object new_transition, old_args, svref_new_value;

    x_note_fn_call(31,56);
    new_transition = make_state_transition_1();
    old_args = ISVREF(old_transition,(SI_Long)2L);
    svref_new_value = ISVREF(old_transition,(SI_Long)1L);
    SVREF(new_transition,FIX((SI_Long)1L)) = svref_new_value;
    svref_new_value = CONSP(old_args) ? 
	    copy_tree_using_token_conses_1(old_args) : old_args;
    SVREF(new_transition,FIX((SI_Long)2L)) = svref_new_value;
    SVREF(new_transition,FIX((SI_Long)3L)) = new_destination;
    svref_new_value = ISVREF(old_transition,(SI_Long)4L);
    SVREF(new_transition,FIX((SI_Long)4L)) = svref_new_value;
    svref_new_value = ISVREF(old_transition,(SI_Long)5L);
    SVREF(new_transition,FIX((SI_Long)5L)) = svref_new_value;
    return VALUES_1(new_transition);
}

/* CREATE-PARSE-OBJECT */
Object create_parse_object(type,value)
    Object type, value;
{
    Object the_parse_object;

    x_note_fn_call(31,57);
    the_parse_object = make_parse_object_1();
    SVREF(the_parse_object,FIX((SI_Long)1L)) = type;
    SVREF(the_parse_object,FIX((SI_Long)4L)) = value;
    return VALUES_1(the_parse_object);
}

/* DESTRUCTIVE-BUBBLE-SORT */
Object destructive_bubble_sort(list_1,less_than_predicate)
    Object list_1, less_than_predicate;
{
    Object pointer, smallest, element, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, car_new_value;

    x_note_fn_call(31,58);
    pointer = list_1;
  next_loop:
    if ( !TRUEP(pointer))
	goto end_loop;
    smallest = CAR(pointer);
    element = pointer;
  next_loop_1:
    if ( !TRUEP(element))
	goto end_loop_1;
    gensymed_symbol = less_than_predicate;
    gensymed_symbol_1 = CAR(element);
    gensymed_symbol_2 = smallest;
    if (inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2)) {
	car_new_value = CAR(element);
	M_CAR(pointer) = car_new_value;
	M_CAR(element) = smallest;
	smallest = CAR(pointer);
    }
    element = M_CDR(element);
    goto next_loop_1;
  end_loop_1:;
    pointer = CDR(pointer);
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* TOKEN-COPY-OF-LIST-WITHOUT-DUPLICATES */
Object token_copy_of_list_without_duplicates(list_1,eql_test)
    Object list_1, eql_test;
{
    Object result_list, duplicate_list, element, ab_loop_list_, temp;

    x_note_fn_call(31,59);
    result_list = Qnil;
    duplicate_list = Qnil;
    element = Nil;
    ab_loop_list_ = list_1;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (member(4,element,result_list,Ktest,eql_test))
	duplicate_list = token_cons_1(element,duplicate_list);
    else
	result_list = token_cons_1(element,result_list);
    goto next_loop;
  end_loop:
    temp = nreverse(result_list);
    return VALUES_2(temp,duplicate_list);
    return VALUES_1(Qnil);
}

/* SORT-LIST-DESTRUCTIVELY-SEPARATING-DUPLICATES */
Object sort_list_destructively_separating_duplicates(list_1,less_than_test,
	    eql_test)
    Object list_1, less_than_test, eql_test;
{
    Declare_stack_pointer;
    Object result;

    x_note_fn_call(31,60);
    SAVE_STACK();
    destructive_bubble_sort(list_1,less_than_test);
    SAVE_VALUES(token_copy_of_list_without_duplicates(list_1,eql_test));
    reclaim_token_list_1(list_1);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* RANGE< */
Object range_lt(range_a,range_b)
    Object range_a, range_b;
{
    Object temp;

    x_note_fn_call(31,61);
    temp = FIXNUM_LT(CAR(range_a),CAR(range_b)) ? T : Nil;
    return VALUES_1(temp);
}

Object Null_pattern = UNBOUND;

/* CHARACTER-CLASS-MEMBER-P */
Object character_class_member_p(element,class_list)
    Object element, class_list;
{
    Object class_member, ab_loop_list_, ab_loop_it_, temp;
    SI_Long arg, arg_1, arg_2;

    x_note_fn_call(31,62);
    class_member = Nil;
    ab_loop_list_ = class_list;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    class_member = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    arg = IFIX(CAR(class_member));
    arg_1 = IFIX(element);
    arg_2 = IFIX(CDR(class_member));
    ab_loop_it_ = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
    if (ab_loop_it_) {
	temp = ab_loop_it_;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

static Object Qrange_lt;           /* range< */

/* SORT-STANDARDIZED-CHARACTER-CLASS */
Object sort_standardized_character_class(class_members_list)
    Object class_members_list;
{
    x_note_fn_call(31,63);
    destructive_bubble_sort(class_members_list,SYMBOL_FUNCTION(Qrange_lt));
    return VALUES_1(class_members_list);
}

static Object string_constant;     /* "Pairs must be *DOTTED* lists." */

/* STANDARDIZE-CHARACTER-CLASS-LIST */
Object standardize_character_class_list(character_class_list)
    Object character_class_list;
{
    Object reversed_list, element, ab_loop_list_, revised_list, first_1;
    Object last_1, temp_1, temp_2;
    SI_Long arg, arg_1, arg_2;
    char temp;

    x_note_fn_call(31,64);
    reversed_list = token_reverse(character_class_list);
    element = Nil;
    ab_loop_list_ = reversed_list;
    revised_list = Qnil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (FIXNUMP(element)) {
	arg = IFIX(Alphabet_min_code);
	arg_1 = IFIX(element);
	arg_2 = IFIX(Alphabet_max_code);
	temp = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	revised_list = token_cons_1(token_cons_1(element,element),
		revised_list);
    else if (LISTP(element)) {
	first_1 = CAR(element);
	last_1 = CDR(element);
	if (FIXNUMP(first_1)) {
	    arg = IFIX(Alphabet_min_code);
	    arg_1 = IFIX(first_1);
	    arg_2 = IFIX(Alphabet_max_code);
	    temp = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    if (FIXNUMP(last_1)) {
		arg = IFIX(Alphabet_min_code);
		arg_1 = IFIX(last_1);
		arg_2 = IFIX(Alphabet_max_code);
		temp = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    revised_list = token_cons_1(token_cons_1(FIXNUM_MIN(first_1,
		    last_1),FIXNUM_MAX(first_1,last_1)),revised_list);
	else {
	    temp_1 = format((SI_Long)3L,Nil,
		    "Bad member of character class: ~s.  ",element);
	    if (CONSP(element)) {
		temp_2 = CDR(element);
		temp = CONSP(temp_2);
	    }
	    else
		temp = TRUEP(Nil);
	    errorn(1,format((SI_Long)4L,Nil,"~a~a",temp_1,temp ? 
		    string_constant : format((SI_Long)4L,Nil,
		    "Elements must be fixnums ~%         between ~d and ~d inclusive.",
		    Alphabet_min_code,Alphabet_max_code)));
	}
    }
    else {
	temp_1 = format((SI_Long)3L,Nil,
		"Bad member of character class: ~s.  ",element);
	if (CONSP(element)) {
	    temp_2 = CDR(element);
	    temp = CONSP(temp_2);
	}
	else
	    temp = TRUEP(Nil);
	errorn(1,format((SI_Long)4L,Nil,"~a~a",temp_1,temp ? 
		string_constant : format((SI_Long)4L,Nil,
		"Elements must be fixnums ~%         between ~d and ~d inclusive.",
		Alphabet_min_code,Alphabet_max_code)));
    }
    goto next_loop;
  end_loop:
    sort_standardized_character_class(revised_list);
    reclaim_token_list_1(reversed_list);
    temp_1 = revised_list;
    goto end_1;
    temp_1 = Qnil;
  end_1:;
    return VALUES_1(temp_1);
}

/* INVERT-RANGE */
Object invert_range(range_list)
    Object range_list;
{
    Object first_member, inverted_list, rest_of_list, this_1, next, last_this;
    Object first_next, difference, temp;

    x_note_fn_call(31,65);
    first_member = CAAR(range_list);
    if (FIXNUM_EQ(first_member,Alphabet_min_code))
	inverted_list = Qnil;
    else if (FIXNUM_EQ(FIXNUM_SUB1(first_member),Alphabet_min_code))
	inverted_list = token_cons_1(token_cons_1(Alphabet_min_code,
		Alphabet_min_code),Nil);
    else
	inverted_list = token_cons_1(token_cons_1(Alphabet_min_code,
		FIXNUM_SUB1(first_member)),Nil);
    rest_of_list = range_list;
    this_1 = Nil;
    next = Nil;
    last_this = Nil;
    first_next = Nil;
    difference = Nil;
  next_loop:
    if ( !TRUEP(rest_of_list))
	goto end_loop;
    this_1 = CAR(rest_of_list);
    next = CADR(rest_of_list);
    last_this = CDR(this_1);
    first_next = CAR(next);
    difference = first_next && last_this ? FIXNUM_MINUS(first_next,
	    last_this) : Qnil;
    if ( !TRUEP(difference) || IFIX(difference) < (SI_Long)2L);
    else if (IFIX(difference) == (SI_Long)2L)
	inverted_list = token_cons_1(token_cons_1(FIXNUM_SUB1(first_next),
		FIXNUM_SUB1(first_next)),inverted_list);
    else
	inverted_list = token_cons_1(token_cons_1(FIXNUM_ADD1(last_this),
		FIXNUM_SUB1(first_next)),inverted_list);
    rest_of_list = M_CDR(rest_of_list);
    goto next_loop;
  end_loop:
    if (FIXNUM_EQ(last_this,Alphabet_max_code))
	inverted_list = token_cons_1(token_cons_1(Alphabet_max_code,
		Alphabet_max_code),inverted_list);
    else
	inverted_list = token_cons_1(token_cons_1(FIXNUM_ADD1(last_this),
		Alphabet_max_code),inverted_list);
    temp = nreverse(inverted_list);
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* STANDARDIZE-INVERTED-CHARACTER-CLASS-LIST */
Object standardize_inverted_character_class_list(class_members_list)
    Object class_members_list;
{
    Object standardized_tree, inverted_tree;

    x_note_fn_call(31,66);
    standardized_tree = standardize_character_class_list(class_members_list);
    inverted_tree = invert_range(standardized_tree);
    reclaim_token_tree_1(standardized_tree);
    return VALUES_1(inverted_tree);
}

Object Regular_expression_metacharacters = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Built_in_character_codes, Qbuilt_in_character_codes);

DEFINE_VARIABLE_WITH_SYMBOL(Current_tokenizer, Qcurrent_tokenizer);

DEFINE_VARIABLE_WITH_SYMBOL(Current_start_state, Qcurrent_start_state);

DEFINE_VARIABLE_WITH_SYMBOL(Current_lexing_strings, Qcurrent_lexing_strings);

DEFINE_VARIABLE_WITH_SYMBOL(Current_lexing_patterns, Qcurrent_lexing_patterns);

DEFINE_VARIABLE_WITH_SYMBOL(Current_anchor_p, Qcurrent_anchor_p);

DEFINE_VARIABLE_WITH_SYMBOL(Known_regexp_functions, Qknown_regexp_functions);

/* GET-ALL-STATES */
Object get_all_states()
{
    Object to_be_done, current_state_qm, done_already, current_transitions;
    Object transition, ab_loop_list_, dest, gensymed_symbol, token_pop_store;
    Object cons_1, next_cons, temp_1, svref_arg_2, temp_2;
    char temp;

    x_note_fn_call(31,67);
    to_be_done = Qnil;
    current_state_qm = Current_start_state;
    done_already = current_state_qm ? token_cons_1(current_state_qm,Nil) : 
	    Qnil;
    current_transitions = Nil;
  next_loop:
    if ( !TRUEP(current_state_qm))
	goto end_loop;
    current_transitions = ISVREF(current_state_qm,(SI_Long)3L);
    transition = Nil;
    ab_loop_list_ = current_transitions;
    dest = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    transition = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    dest = ISVREF(transition,(SI_Long)3L);
    gensymed_symbol = done_already;
  next_loop_2:
    if ( !TRUEP(gensymed_symbol))
	goto end_loop_2;
    if (EQ(M_CAR(gensymed_symbol),dest)) {
	temp = TRUEP(gensymed_symbol);
	goto end_1;
    }
    gensymed_symbol = M_CDR(gensymed_symbol);
    goto next_loop_2;
  end_loop_2:
    temp = TRUEP(Qnil);
  end_1:;
    if ( !temp) {
	gensymed_symbol = to_be_done;
      next_loop_3:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_3;
	if (EQ(M_CAR(gensymed_symbol),dest)) {
	    temp = TRUEP(gensymed_symbol);
	    goto end_2;
	}
	gensymed_symbol = M_CDR(gensymed_symbol);
	goto next_loop_3;
      end_loop_3:
	temp = TRUEP(Qnil);
      end_2:;
	to_be_done = temp ? to_be_done : token_cons_1(dest,to_be_done);
    }
    goto next_loop_1;
  end_loop_1:;
    token_pop_store = Nil;
    cons_1 = to_be_done;
    if (cons_1) {
	token_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qtoken);
	if (ISVREF(Available_token_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_1 = ISVREF(Available_token_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_1) = cons_1;
	    temp_1 = Available_token_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = cons_1;
	}
	else {
	    temp_1 = Available_token_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = cons_1;
	    temp_1 = Available_token_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    to_be_done = next_cons;
    current_state_qm = token_pop_store;
    if (current_state_qm)
	done_already = token_cons_1(current_state_qm,done_already);
    goto next_loop;
  end_loop:
    temp_2 = done_already;
    goto end_3;
    temp_2 = Qnil;
  end_3:;
    return VALUES_1(temp_2);
}

/* GET-ALL-STATES-FROM-TOKENIZER */
Object get_all_states_from_tokenizer(lexing_table)
    Object lexing_table;
{
    Object current_tokenizer, current_start_state, current_anchor_p, temp;
    Declare_special(3);

    x_note_fn_call(31,68);
    current_tokenizer = lexing_table;
    PUSH_SPECIAL_WITH_SYMBOL(Current_tokenizer,Qcurrent_tokenizer,current_tokenizer,
	    2);
      current_start_state = ISVREF(Current_tokenizer,(SI_Long)1L);
      PUSH_SPECIAL_WITH_SYMBOL(Current_start_state,Qcurrent_start_state,current_start_state,
	      1);
	current_anchor_p = ISVREF(Current_tokenizer,(SI_Long)3L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_anchor_p,Qcurrent_anchor_p,current_anchor_p,
		0);
	  temp = get_all_states();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* RECLAIM-TOKENIZING-STATE */
Object reclaim_tokenizing_state(state_1)
    Object state_1;
{
    Object current_transitions, next_transition, ab_loop_list_;

    x_note_fn_call(31,69);
    current_transitions = ISVREF(state_1,(SI_Long)3L);
    reclaim_token_list_1(ISVREF(state_1,(SI_Long)1L));
    next_transition = Nil;
    ab_loop_list_ = current_transitions;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    next_transition = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_transition(next_transition);
    goto next_loop;
  end_loop:;
    reclaim_token_list_1(current_transitions);
    reclaim_fsm_state_1(state_1);
    return VALUES_1(Nil);
}

/* RECLAIM-DFA */
Object reclaim_dfa(lexing_table)
    Object lexing_table;
{
    Object list_of_states, token_array, state_1, ab_loop_list_, token_qm;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(31,70);
    list_of_states = get_all_states_from_tokenizer(lexing_table);
    token_array = ISVREF(lexing_table,(SI_Long)2L);
    state_1 = Nil;
    ab_loop_list_ = list_of_states;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    state_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_tokenizing_state(state_1);
    goto next_loop;
  end_loop:;
    reclaim_token_list_1(list_of_states);
    if (token_array) {
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(length(token_array));
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop_1;
	token_qm = ISVREF(token_array,i);
	if (token_qm)
	    reclaim_internal_token_1(token_qm);
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
	reclaim_managed_simple_vector(ISVREF(lexing_table,(SI_Long)2L));
    }
    reclaim_lexing_table_1(lexing_table);
    return VALUES_1(Nil);
}

/* RECLAIM-NFA */
Object reclaim_nfa(lexing_table)
    Object lexing_table;
{
    Object list_of_states, state_1, ab_loop_list_;

    x_note_fn_call(31,71);
    list_of_states = get_all_states_from_tokenizer(lexing_table);
    state_1 = Nil;
    ab_loop_list_ = list_of_states;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    state_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_tokenizing_state(state_1);
    goto next_loop;
  end_loop:;
    reclaim_token_list_1(list_of_states);
    reclaim_lexing_table_1(lexing_table);
    return VALUES_1(Nil);
}

/* RECLAIM-DFA-IF-ANY */
Object reclaim_dfa_if_any(lexing_table)
    Object lexing_table;
{
    x_note_fn_call(31,72);
    if (lexing_table)
	reclaim_dfa(lexing_table);
    return VALUES_1(Nil);
}

Object Regexp_evaluator_prop = UNBOUND;

static Object Qregexp_evaluator;   /* regexp-evaluator */

/* COMPILE-PATTERN-REC */
Object compile_pattern_rec(exp_1,in_node,out_node)
    Object exp_1, in_node, out_node;
{
    Object operator_1, evaluator_function;

    x_note_fn_call(31,73);
    if (FIXNUMP(exp_1))
	pattern_transform_canonical(exp_1,in_node,out_node);
    else if (LISTP(exp_1)) {
	operator_1 = CAR(exp_1);
	evaluator_function = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(operator_1),
		Qregexp_evaluator);
	if (evaluator_function)
	    inline_funcall_3(evaluator_function,exp_1,in_node,out_node);
	else
	    error((SI_Long)2L,"Unknown regular expression operator: ~s",
		    operator_1);
    }
    else
	error((SI_Long)2L,"Bad parse of regular expression: ~s~%",exp_1);
    return VALUES_1(Nil);
}

/* PATTERN-TRANSFORM-CANONICAL */
Object pattern_transform_canonical(exp_1,in_node,out_node)
    Object exp_1, in_node, out_node;
{
    Object token_push_modify_macro_arg, car_1, cdr_1, svref_new_value;

    x_note_fn_call(31,74);
    token_push_modify_macro_arg = 
	    create_standard_state_transition(Alphabet_equality_st_test,
	    token_cons_1(exp_1,Nil),out_node);
    car_1 = token_push_modify_macro_arg;
    cdr_1 = ISVREF(in_node,(SI_Long)3L);
    svref_new_value = token_cons_1(car_1,cdr_1);
    SVREF(in_node,FIX((SI_Long)3L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* PATTERN-TRANSFORM-NIL */
Object pattern_transform_nil(exp_1,in_node,out_node)
    Object exp_1, in_node, out_node;
{
    Object token_push_modify_macro_arg, car_1, cdr_1, svref_new_value;

    x_note_fn_call(31,75);
    token_push_modify_macro_arg = create_epsilon_state_transition(out_node);
    car_1 = token_push_modify_macro_arg;
    cdr_1 = ISVREF(in_node,(SI_Long)3L);
    svref_new_value = token_cons_1(car_1,cdr_1);
    SVREF(in_node,FIX((SI_Long)3L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* PATTERN-TRANSFORM-TEST */
Object pattern_transform_test(exp_1,in_node,out_node)
    Object exp_1, in_node, out_node;
{
    Object new_trans, token_push_modify_macro_arg, car_1, cdr_1;
    Object svref_new_value;

    x_note_fn_call(31,76);
    new_trans = create_nonstandard_state_transition(CADR(exp_1),
	    copy_tree_using_token_conses_1(CDDR(exp_1)),out_node);
    token_push_modify_macro_arg = new_trans;
    car_1 = token_push_modify_macro_arg;
    cdr_1 = ISVREF(in_node,(SI_Long)3L);
    svref_new_value = token_cons_1(car_1,cdr_1);
    SVREF(in_node,FIX((SI_Long)3L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* PATTERN-TRANSFORM-SEQ */
Object pattern_transform_seq(exp_1,in_node,out_node)
    Object exp_1, in_node, out_node;
{
    Object prev_node, arg_tail, arg, next_node;

    x_note_fn_call(31,77);
    prev_node = in_node;
    arg_tail = CDR(exp_1);
    arg = Nil;
    next_node = Nil;
  next_loop:
    if ( !TRUEP(arg_tail))
	goto end_loop;
    arg = CAR(arg_tail);
    next_node = CDR(arg_tail) ? create_fsm_state() : out_node;
    compile_pattern_rec(arg,prev_node,next_node);
    prev_node = next_node;
    arg_tail = M_CDR(arg_tail);
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* PATTERN-TRANSFORM-EITHER */
Object pattern_transform_either(exp_1,in_node,out_node)
    Object exp_1, in_node, out_node;
{
    Object arg, ab_loop_list_, new_start, new_end, token_push_modify_macro_arg;
    Object car_1, cdr_1, svref_new_value;

    x_note_fn_call(31,78);
    arg = Nil;
    ab_loop_list_ = CDR(exp_1);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    arg = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    new_start = create_fsm_state();
    new_end = create_fsm_state();
    token_push_modify_macro_arg = create_epsilon_state_transition(new_start);
    car_1 = token_push_modify_macro_arg;
    cdr_1 = ISVREF(in_node,(SI_Long)3L);
    svref_new_value = token_cons_1(car_1,cdr_1);
    SVREF(in_node,FIX((SI_Long)3L)) = svref_new_value;
    token_push_modify_macro_arg = create_epsilon_state_transition(out_node);
    car_1 = token_push_modify_macro_arg;
    cdr_1 = ISVREF(new_end,(SI_Long)3L);
    svref_new_value = token_cons_1(car_1,cdr_1);
    SVREF(new_end,FIX((SI_Long)3L)) = svref_new_value;
    compile_pattern_rec(arg,new_start,new_end);
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* PATTERN-TRANSFORM-KLEENE */
Object pattern_transform_kleene(exp_1,in_node,out_node)
    Object exp_1, in_node, out_node;
{
    Object new_in_node, new_out_node, token_push_modify_macro_arg, car_1;
    Object cdr_1, svref_new_value;

    x_note_fn_call(31,79);
    if ( ! !TRUEP(CDDR(exp_1)))
	error((SI_Long)1L,"Kleene Star takes one sub-expression.");
    new_in_node = create_fsm_state();
    new_out_node = create_fsm_state();
    token_push_modify_macro_arg = create_epsilon_state_transition(new_in_node);
    car_1 = token_push_modify_macro_arg;
    cdr_1 = ISVREF(in_node,(SI_Long)3L);
    svref_new_value = token_cons_1(car_1,cdr_1);
    SVREF(in_node,FIX((SI_Long)3L)) = svref_new_value;
    token_push_modify_macro_arg = create_epsilon_state_transition(out_node);
    car_1 = token_push_modify_macro_arg;
    cdr_1 = ISVREF(in_node,(SI_Long)3L);
    svref_new_value = token_cons_1(car_1,cdr_1);
    SVREF(in_node,FIX((SI_Long)3L)) = svref_new_value;
    token_push_modify_macro_arg = create_epsilon_state_transition(out_node);
    car_1 = token_push_modify_macro_arg;
    cdr_1 = ISVREF(new_out_node,(SI_Long)3L);
    svref_new_value = token_cons_1(car_1,cdr_1);
    SVREF(new_out_node,FIX((SI_Long)3L)) = svref_new_value;
    token_push_modify_macro_arg = create_epsilon_state_transition(new_in_node);
    car_1 = token_push_modify_macro_arg;
    cdr_1 = ISVREF(new_out_node,(SI_Long)3L);
    svref_new_value = token_cons_1(car_1,cdr_1);
    SVREF(new_out_node,FIX((SI_Long)3L)) = svref_new_value;
    compile_pattern_rec(CADR(exp_1),new_in_node,new_out_node);
    return VALUES_1(Nil);
}

/* PATTERN-TRANSFORM-PATTERN */
Object pattern_transform_pattern(exp_1,in_node,out_node)
    Object exp_1, in_node, out_node;
{
    Object lookup, pattern_name;

    x_note_fn_call(31,80);
    lookup = Nil;
    pattern_name = Nil;
    if ( !TRUEP(CDR(exp_1)))
	error((SI_Long)1L,"Pattern requires one argument.");
    else if (CDDR(exp_1))
	error((SI_Long)1L,"Pattern takes only one argument.");
    else {
	pattern_name = CADR(exp_1);
	if ( !TRUEP(pattern_name))
	    error((SI_Long)1L,"Nil is an invalid pattern name.");
	else if ( !SYMBOLP(pattern_name))
	    error((SI_Long)2L,
		    "Pattern names must be symbols; ~s is not valid.",
		    pattern_name);
	else {
	    lookup = assq_function(pattern_name,Current_lexing_patterns);
	    if ( !TRUEP(lookup))
		error((SI_Long)2L,"Pattern ~s not found",pattern_name);
	    else
		compile_pattern_rec(CADR(lookup),in_node,out_node);
	}
    }
    return VALUES_1(Nil);
}

/* PATTERN-TRANSFORM-PLUS */
Object pattern_transform_plus(exp_1,in_node,out_node)
    Object exp_1, in_node, out_node;
{
    Object new_in_node, new_out_node, token_push_modify_macro_arg, car_1;
    Object cdr_1, svref_new_value;

    x_note_fn_call(31,81);
    if ( ! !TRUEP(CDDR(exp_1)))
	error((SI_Long)1L,"Kleene plus takes one sub-expression.");
    new_in_node = create_fsm_state();
    new_out_node = create_fsm_state();
    token_push_modify_macro_arg = create_epsilon_state_transition(new_in_node);
    car_1 = token_push_modify_macro_arg;
    cdr_1 = ISVREF(in_node,(SI_Long)3L);
    svref_new_value = token_cons_1(car_1,cdr_1);
    SVREF(in_node,FIX((SI_Long)3L)) = svref_new_value;
    token_push_modify_macro_arg = create_epsilon_state_transition(out_node);
    car_1 = token_push_modify_macro_arg;
    cdr_1 = ISVREF(new_out_node,(SI_Long)3L);
    svref_new_value = token_cons_1(car_1,cdr_1);
    SVREF(new_out_node,FIX((SI_Long)3L)) = svref_new_value;
    token_push_modify_macro_arg = create_epsilon_state_transition(new_in_node);
    car_1 = token_push_modify_macro_arg;
    cdr_1 = ISVREF(new_out_node,(SI_Long)3L);
    svref_new_value = token_cons_1(car_1,cdr_1);
    SVREF(new_out_node,FIX((SI_Long)3L)) = svref_new_value;
    compile_pattern_rec(CADR(exp_1),new_in_node,new_out_node);
    return VALUES_1(Nil);
}

/* PATTERN-TRANSFORM-MAYBE */
Object pattern_transform_maybe(exp_1,in_node,out_node)
    Object exp_1, in_node, out_node;
{
    Object new_in_node, new_out_node, token_push_modify_macro_arg, car_1;
    Object cdr_1, svref_new_value;

    x_note_fn_call(31,82);
    if ( ! !TRUEP(CDDR(exp_1)))
	error((SI_Long)1L,"Maybe takes one sub-expression.");
    new_in_node = create_fsm_state();
    new_out_node = create_fsm_state();
    token_push_modify_macro_arg = create_epsilon_state_transition(new_in_node);
    car_1 = token_push_modify_macro_arg;
    cdr_1 = ISVREF(in_node,(SI_Long)3L);
    svref_new_value = token_cons_1(car_1,cdr_1);
    SVREF(in_node,FIX((SI_Long)3L)) = svref_new_value;
    token_push_modify_macro_arg = create_epsilon_state_transition(out_node);
    car_1 = token_push_modify_macro_arg;
    cdr_1 = ISVREF(in_node,(SI_Long)3L);
    svref_new_value = token_cons_1(car_1,cdr_1);
    SVREF(in_node,FIX((SI_Long)3L)) = svref_new_value;
    token_push_modify_macro_arg = create_epsilon_state_transition(out_node);
    car_1 = token_push_modify_macro_arg;
    cdr_1 = ISVREF(new_out_node,(SI_Long)3L);
    svref_new_value = token_cons_1(car_1,cdr_1);
    SVREF(new_out_node,FIX((SI_Long)3L)) = svref_new_value;
    compile_pattern_rec(CADR(exp_1),new_in_node,new_out_node);
    return VALUES_1(Nil);
}

/* PATTERN-TRANSFORM-DOT */
Object pattern_transform_dot(exp_1,in_node,out_node)
    Object exp_1, in_node, out_node;
{
    Object new_trans, token_push_modify_macro_arg, car_1, cdr_1;
    Object svref_new_value;

    x_note_fn_call(31,83);
    if ( ! !TRUEP(CDR(exp_1)))
	error((SI_Long)1L,"Dot does not take arguments.");
    new_trans = 
	    create_standard_state_transition(Alphabet_canonical_element_st_test,
	    Nil,out_node);
    token_push_modify_macro_arg = new_trans;
    car_1 = token_push_modify_macro_arg;
    cdr_1 = ISVREF(in_node,(SI_Long)3L);
    svref_new_value = token_cons_1(car_1,cdr_1);
    SVREF(in_node,FIX((SI_Long)3L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* PATTERN-TRANSFORM-CHARACTER-CLASS */
Object pattern_transform_character_class(exp_1,in_node,out_node)
    Object exp_1, in_node, out_node;
{
    Object temp, token_push_modify_macro_arg, car_1, cdr_1, svref_new_value;

    x_note_fn_call(31,84);
    if ( ! !TRUEP(CDDR(exp_1)))
	error((SI_Long)1L,"Range takes only one argument");
    temp = Alphabet_character_class_st_test;
    token_push_modify_macro_arg = create_standard_state_transition(temp,
	    token_cons_1(standardize_character_class_list(CADR(exp_1)),
	    Nil),out_node);
    car_1 = token_push_modify_macro_arg;
    cdr_1 = ISVREF(in_node,(SI_Long)3L);
    svref_new_value = token_cons_1(car_1,cdr_1);
    SVREF(in_node,FIX((SI_Long)3L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* PATTERN-TRANSFORM-INVERTED-CLASS */
Object pattern_transform_inverted_class(exp_1,in_node,out_node)
    Object exp_1, in_node, out_node;
{
    Object temp, token_push_modify_macro_arg, car_1, cdr_1, svref_new_value;

    x_note_fn_call(31,85);
    if ( ! !TRUEP(CDDR(exp_1)))
	error((SI_Long)1L,"Range takes only one argument");
    temp = CADR(exp_1);
    if ( !LISTP(temp))
	error((SI_Long)1L,"The argument to inverted class must be a LIST.");
    temp = Alphabet_character_class_st_test;
    token_push_modify_macro_arg = create_standard_state_transition(temp,
	    token_cons_1(standardize_inverted_character_class_list(CADR(exp_1)),
	    Nil),out_node);
    car_1 = token_push_modify_macro_arg;
    cdr_1 = ISVREF(in_node,(SI_Long)3L);
    svref_new_value = token_cons_1(car_1,cdr_1);
    SVREF(in_node,FIX((SI_Long)3L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* SIMPLE-COMPILED-MAKE-UNINITIALIZED-PERMANENT-ARRAY */
Object simple_compiled_make_uninitialized_permanent_array(length_1)
    Object length_1;
{
    Object temp;

    x_note_fn_call(31,86);
    temp = make_array(1,length_1);
    return VALUES_1(temp);
}

/* COMPILE-TOKEN-DEFINITION */
Object compile_token_definition(token_def)
    Object token_def;
{
    Object start_node, end_node, svref_new_value;

    x_note_fn_call(31,87);
    start_node = create_fsm_state();
    end_node = create_fsm_state();
    compile_pattern_rec(token_def,start_node,end_node);
    svref_new_value = Current_lexing_rule_number;
    SVREF(end_node,FIX((SI_Long)2L)) = svref_new_value;
    return VALUES_1(start_node);
}

static Object Qanchor;             /* anchor */

/* COMPILE-LEXING-TABLE-FOR-NFA */
Object compile_lexing_table_for_nfa(pattern_and_token_defs,array_maker)
    Object pattern_and_token_defs, array_maker;
{
    Object token_defs, current_lexing_patterns, current_lexing_rule_number;
    Object gensymed_symbol, gensymed_symbol_1, current_tokens, nfa_tokenizer;
    Object root_node, token_type, token_expression, token_action;
    Object ab_loop_list_, ab_loop_iter_flag_, ab_loop_desetq_, temp, new_token;
    Object svref_new_value, start_node, token_push_modify_macro_arg, car_1;
    Object cdr_1;
    SI_Long i;
    Declare_special(2);

    x_note_fn_call(31,88);
    token_defs = M_CDR(pattern_and_token_defs);
    current_lexing_patterns = M_CAR(pattern_and_token_defs);
    PUSH_SPECIAL_WITH_SYMBOL(Current_lexing_patterns,Qcurrent_lexing_patterns,current_lexing_patterns,
	    1);
      current_lexing_rule_number = FIX((SI_Long)0L);
      PUSH_SPECIAL_WITH_SYMBOL(Current_lexing_rule_number,Qcurrent_lexing_rule_number,current_lexing_rule_number,
	      0);
	gensymed_symbol = array_maker;
	gensymed_symbol_1 = length(token_defs);
	current_tokens = inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	nfa_tokenizer = make_lexing_table_1();
	root_node = create_fsm_state();
	SVREF(nfa_tokenizer,FIX((SI_Long)1L)) = root_node;
	token_type = Nil;
	token_expression = Nil;
	token_action = Nil;
	ab_loop_list_ = token_defs;
	i = (SI_Long)0L;
	ab_loop_iter_flag_ = T;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	token_type = CAR(ab_loop_desetq_);
	temp = CDR(ab_loop_desetq_);
	token_expression = CAR(temp);
	temp = CDR(ab_loop_desetq_);
	temp = CDR(temp);
	token_action = CAR(temp);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    i = i + (SI_Long)1L;
	if (CONSP(token_expression) && EQ(M_CAR(token_expression),Qanchor)) {
	    token_expression = CADR(token_expression);
	    if ( !TRUEP(CDR(token_defs)))
		SVREF(nfa_tokenizer,FIX((SI_Long)3L)) = T;
	}
	Current_lexing_rule_number = FIX(i);
	new_token = make_internal_token_1();
	SVREF(new_token,FIX((SI_Long)1L)) = token_type;
	ISVREF(new_token,(SI_Long)3L) = FIX(i);
	if (token_action) {
	    svref_new_value = SYMBOL_FUNCTION(token_action);
	    SVREF(new_token,FIX((SI_Long)2L)) = svref_new_value;
	}
	ISVREF(current_tokens,i) = new_token;
	start_node = compile_token_definition(token_expression);
	token_push_modify_macro_arg = 
		create_epsilon_state_transition(start_node);
	car_1 = token_push_modify_macro_arg;
	cdr_1 = ISVREF(root_node,(SI_Long)3L);
	svref_new_value = token_cons_1(car_1,cdr_1);
	SVREF(root_node,FIX((SI_Long)3L)) = svref_new_value;
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:;
	SVREF(nfa_tokenizer,FIX((SI_Long)2L)) = current_tokens;
	temp = nfa_tokenizer;
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* INSERT-FIXNUM-INTO-SORTED-LIST-USING-TOKEN-CONSES */
Object insert_fixnum_into_sorted_list_using_token_conses(new_fixnum,list_1)
    Object new_fixnum, list_1;
{
    Object temp, list_to_insert, rest_of_list, cdr_new_value;

    x_note_fn_call(31,89);
    if ( !TRUEP(list_1))
	temp = token_cons_1(new_fixnum,Nil);
    else if (FIXNUM_EQ(new_fixnum,CAR(list_1)))
	temp = list_1;
    else if (FIXNUM_LT(new_fixnum,CAR(list_1)))
	temp = token_cons_1(new_fixnum,list_1);
    else {
	list_to_insert = Nil;
	rest_of_list = list_1;
      next_loop:
	if ( !TRUEP(CADR(rest_of_list))) {
	    list_to_insert = token_cons_1(new_fixnum,Nil);
	    M_CDR(rest_of_list) = list_to_insert;
	    goto end_loop;
	}
	if (FIXNUM_EQ(CADR(rest_of_list),new_fixnum)) {
	    reclaim_token_list_1(list_to_insert);
	    goto end_loop;
	}
	if (FIXNUM_GT(CADR(rest_of_list),new_fixnum)) {
	    list_to_insert = token_cons_1(new_fixnum,Nil);
	    cdr_new_value = CDR(rest_of_list);
	    M_CDR(list_to_insert) = cdr_new_value;
	    M_CDR(rest_of_list) = list_to_insert;
	    goto end_loop;
	}
	rest_of_list = CDR(rest_of_list);
	goto next_loop;
      end_loop:
	temp = list_1;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

/* E-CLOSURE */
Object e_closure(set_of_states)
    Object set_of_states;
{
    Object stack_qm, ep_closure, next_state, current_transitions;
    Object token_pop_store, cons_1, next_cons, temp, svref_arg_2, transition;
    Object ab_loop_list_, test, destination, gensymed_symbol, temp_2;
    char temp_1;

    x_note_fn_call(31,90);
    stack_qm = copy_list_using_token_conses_1(set_of_states);
    ep_closure = copy_list_using_token_conses_1(set_of_states);
    next_state = Nil;
    current_transitions = Nil;
  next_loop:
    if ( !TRUEP(stack_qm))
	goto end_loop;
    token_pop_store = Nil;
    cons_1 = stack_qm;
    if (cons_1) {
	token_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qtoken);
	if (ISVREF(Available_token_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_token_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_token_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_token_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_token_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    stack_qm = next_cons;
    next_state = token_pop_store;
    current_transitions = ISVREF(next_state,(SI_Long)3L);
    transition = Nil;
    ab_loop_list_ = current_transitions;
    test = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    transition = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    test = ISVREF(transition,(SI_Long)1L);
    if ( !TRUEP(test)) {
	destination = ISVREF(transition,(SI_Long)3L);
	gensymed_symbol = ep_closure;
      next_loop_2:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_2;
	if (EQ(M_CAR(gensymed_symbol),destination)) {
	    temp_1 = TRUEP(gensymed_symbol);
	    goto end_1;
	}
	gensymed_symbol = M_CDR(gensymed_symbol);
	goto next_loop_2;
      end_loop_2:
	temp_1 = TRUEP(Qnil);
      end_1:;
	if ( !temp_1) {
	    ep_closure = token_cons_1(destination,ep_closure);
	    stack_qm = token_cons_1(destination,stack_qm);
	}
    }
    goto next_loop_1;
  end_loop_1:;
    goto next_loop;
  end_loop:
    temp_2 = ep_closure;
    goto end_2;
    temp_2 = Qnil;
  end_2:;
    return VALUES_1(temp_2);
}

/* E-CLOSURE-OF-SINGLE-STATE */
Object e_closure_of_single_state(state_1)
    Object state_1;
{
    Object bogus_temp_list, single_states_closure;

    x_note_fn_call(31,91);
    bogus_temp_list = token_cons_1(state_1,Nil);
    single_states_closure = e_closure(bogus_temp_list);
    reclaim_token_list_1(bogus_temp_list);
    return VALUES_1(single_states_closure);
}

/* TOKENS-RECOGNIZED */
Object tokens_recognized(closure)
    Object closure;
{
    Object nfa_state, ab_loop_list_, dfa_should_accept_qm;
    Object dfa_associated_rules, nfa_associated_rule, temp;

    x_note_fn_call(31,92);
    nfa_state = Nil;
    ab_loop_list_ = closure;
    dfa_should_accept_qm = Nil;
    dfa_associated_rules = Qnil;
    nfa_associated_rule = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    nfa_state = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = ISVREF(nfa_state,(SI_Long)1L);
    nfa_associated_rule = CAR(temp);
    dfa_associated_rules = 
	    insert_fixnum_into_sorted_list_using_token_conses(nfa_associated_rule,
	    dfa_associated_rules);
    if (ISVREF(nfa_state,(SI_Long)2L) && ( !TRUEP(dfa_should_accept_qm) || 
	    FIXNUM_LT(nfa_associated_rule,dfa_should_accept_qm)))
	dfa_should_accept_qm = nfa_associated_rule;
    goto next_loop;
  end_loop:
    return VALUES_2(dfa_associated_rules,dfa_should_accept_qm);
    return VALUES_1(Qnil);
}

/* CREATE-FSM-STATE-FOR-DFA */
Object create_fsm_state_for_dfa(nfa_states)
    Object nfa_states;
{
    Object new_state, rules, accepts_qm;
    Object result;

    x_note_fn_call(31,93);
    new_state = create_fsm_state();
    result = tokens_recognized(nfa_states);
    MVS_2(result,rules,accepts_qm);
    reclaim_token_list_1(ISVREF(new_state,(SI_Long)1L));
    SVREF(new_state,FIX((SI_Long)1L)) = rules;
    SVREF(new_state,FIX((SI_Long)2L)) = accepts_qm;
    return VALUES_1(new_state);
}

/* TRANSITION-RELATIONSHIP */
Object transition_relationship(transition_1,transition_2)
    Object transition_1, transition_2;
{
    Object temp;

    x_note_fn_call(31,94);
    temp = alphabet_transition_relationship(ISVREF(transition_1,
	    (SI_Long)1L),ISVREF(transition_1,(SI_Long)2L),
	    ISVREF(transition_2,(SI_Long)1L),ISVREF(transition_2,(SI_Long)2L));
    return VALUES_1(temp);
}

static Object Qequiv;              /* equiv */

static Object Qsub2;               /* sub2 */

static Object Qab_sub1;            /* sub1 */

static Object Qdisjoint;           /* disjoint */

static Object Qoverlap;            /* overlap */

/* ALPHABET-TRANSITION-RELATIONSHIP */
Object alphabet_transition_relationship(test1,args1,test2,args2)
    Object test1, args1, test2, args2;
{
    Object temp, temp_1, gensymed_symbol;
    char temp_2;

    x_note_fn_call(31,95);
    if (EQ(test1,test2) && EQUAL(args1,args2))
	temp = Qequiv;
    else if ( !TRUEP(test2))
	temp = Qsub2;
    else if (EQ(test1,Alphabet_canonical_element_st_test))
	temp = Qsub2;
    else if (EQ(test2,Alphabet_canonical_element_st_test))
	temp = Qab_sub1;
    else if (EQ(test1,Alphabet_character_class_st_test) && EQ(test2,
	    Alphabet_character_class_st_test))
	temp = character_class_relationship(CAR(args1),CAR(args2));
    else if (EQ(test1,Alphabet_equality_st_test)) {
	if (EQ(test2,Alphabet_equality_st_test)) {
	    temp_1 = CAR(args1);
	    temp = CAR(args2);
	    temp = EQUAL(temp_1,temp) ? Qequiv : Qdisjoint;
	}
	else if (APPLY_2(test2,CAR(args1),args2)) {
	    gensymed_symbol = Alphabet_preds_with_card_gt_2;
	  next_loop:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop;
	    if (EQ(M_CAR(gensymed_symbol),test2)) {
		temp_2 = TRUEP(gensymed_symbol);
		goto end_1;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop;
	  end_loop:
	    temp_2 = TRUEP(Qnil);
	  end_1:;
	    if (temp_2)
		temp = Qab_sub1;
	    else if (EQ(test2,Alphabet_character_class_st_test))
		temp = Qab_sub1;
	    else if (IFIX(Alphabet_cardinality) < (SI_Long)2L)
		temp = Qequiv;
	    else
		temp = Qdisjoint;
	}
	else
	    temp = Qdisjoint;
    }
    else if (EQ(test2,Alphabet_equality_st_test)) {
	if (APPLY_2(test1,CAR(args2),args1)) {
	    gensymed_symbol = Alphabet_preds_with_card_gt_2;
	  next_loop_1:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_1;
	    if (EQ(M_CAR(gensymed_symbol),test1)) {
		temp_2 = TRUEP(gensymed_symbol);
		goto end_2;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_1;
	  end_loop_1:
	    temp_2 = TRUEP(Qnil);
	  end_2:;
	    if (temp_2)
		temp = Qsub2;
	    else if (EQ(test1,Alphabet_character_class_st_test))
		temp = Qsub2;
	    else if (IFIX(Alphabet_cardinality) < (SI_Long)2L)
		temp = Qequiv;
	    else
		temp = Qdisjoint;
	}
	else
	    temp = Qdisjoint;
    }
    else
	temp = Qoverlap;
    return VALUES_1(temp);
}

/* TRANSITIONS-ARE-COMPATIBLE? */
Object transitions_are_compatible_qm(transition_1,transition_2)
    Object transition_1, transition_2;
{
    Object transition_relationship_1, temp;

    x_note_fn_call(31,96);
    transition_relationship_1 = transition_relationship(transition_1,
	    transition_2);
    temp = EQ(transition_relationship_1,Qequiv) ? T : Nil;
    if (temp);
    else
	temp = EQ(transition_relationship_1,Qab_sub1) ? T : Nil;
    return VALUES_1(temp);
}

/* POSSIBLE-MOVES */
Object possible_moves(allowed_transitions,attempted_transition)
    Object allowed_transitions, attempted_transition;
{
    Object all_moves, allowed_transition, ab_loop_list_;
    Object add_this_destination_p, dest, gensymed_symbol, answer, temp_1;
    char temp;

    x_note_fn_call(31,97);
    if (ISVREF(attempted_transition,(SI_Long)1L)) {
	all_moves = Qnil;
	allowed_transition = Nil;
	ab_loop_list_ = allowed_transitions;
	add_this_destination_p = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	allowed_transition = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	add_this_destination_p = 
		transitions_are_compatible_qm(attempted_transition,
		allowed_transition);
	if (add_this_destination_p) {
	    dest = ISVREF(allowed_transition,(SI_Long)3L);
	    gensymed_symbol = all_moves;
	  next_loop_1:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_1;
	    if (EQ(M_CAR(gensymed_symbol),dest)) {
		temp = TRUEP(gensymed_symbol);
		goto end_1;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_1;
	  end_loop_1:
	    temp = TRUEP(Qnil);
	  end_1:;
	    if ( !temp)
		all_moves = token_cons_1(dest,all_moves);
	}
	goto next_loop;
      end_loop:
	answer = e_closure(all_moves);
	reclaim_token_list_1(all_moves);
	temp_1 = answer;
	goto end_2;
	temp_1 = Qnil;
      end_2:;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* ALL-TRANSITIONS-FROM */
Object all_transitions_from(list_of_nfa_states)
    Object list_of_nfa_states;
{
    Object state_1, ab_loop_list_, all_transitions, collated_transitions;
    Object trans, ab_loop_list__1, temp;

    x_note_fn_call(31,98);
    state_1 = Nil;
    ab_loop_list_ = list_of_nfa_states;
    all_transitions = Qnil;
    collated_transitions = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    state_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    trans = Nil;
    ab_loop_list__1 = ISVREF(state_1,(SI_Long)3L);
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    trans = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    all_transitions = token_cons_1(trans,all_transitions);
    goto next_loop_1;
  end_loop_1:;
    goto next_loop;
  end_loop:
    collated_transitions = copy_list_using_token_conses_1(all_transitions);
    reclaim_token_list_1(all_transitions);
    temp = collated_transitions;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* EQUIVALENT-SETS-OF-NFA-STATES-P */
Object equivalent_sets_of_nfa_states_p(list1,list2)
    Object list1, list2;
{
    Object same, element, ab_loop_list_, gensymed_symbol;
    char temp;

    x_note_fn_call(31,99);
    same = T;
    element = Nil;
    ab_loop_list_ = list2;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(same))
	goto end_loop;
    gensymed_symbol = list1;
  next_loop_1:
    if ( !TRUEP(gensymed_symbol))
	goto end_loop_1;
    if (EQ(M_CAR(gensymed_symbol),element)) {
	temp = TRUEP(gensymed_symbol);
	goto end_1;
    }
    gensymed_symbol = M_CDR(gensymed_symbol);
    goto next_loop_1;
  end_loop_1:
    temp = TRUEP(Qnil);
  end_1:;
    if ( !temp)
	same = Nil;
    goto next_loop;
  end_loop:;
    element = Nil;
    ab_loop_list_ = list1;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(same))
	goto end_loop_2;
    gensymed_symbol = list2;
  next_loop_3:
    if ( !TRUEP(gensymed_symbol))
	goto end_loop_3;
    if (EQ(M_CAR(gensymed_symbol),element)) {
	temp = TRUEP(gensymed_symbol);
	goto end_2;
    }
    gensymed_symbol = M_CDR(gensymed_symbol);
    goto next_loop_3;
  end_loop_3:
    temp = TRUEP(Qnil);
  end_2:;
    if ( !temp)
	same = Nil;
    goto next_loop_2;
  end_loop_2:;
    return VALUES_1(same);
}

/* DUPLICATE-DFA-STATE? */
Object duplicate_dfa_state_qm(new_states_represented,
	    mapping_of_dfa_states_to_nfa_states_1,
	    mapping_of_dfa_states_to_nfa_states_2)
    Object new_states_represented, mapping_of_dfa_states_to_nfa_states_1;
    Object mapping_of_dfa_states_to_nfa_states_2;
{
    Object dfa_state, nfa_states, ab_loop_list_, ab_loop_desetq_, temp;

    x_note_fn_call(31,100);
    if (new_states_represented) {
	dfa_state = Nil;
	nfa_states = Nil;
	ab_loop_list_ = mapping_of_dfa_states_to_nfa_states_1;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	dfa_state = CAR(ab_loop_desetq_);
	nfa_states = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (equivalent_sets_of_nfa_states_p(new_states_represented,
		    nfa_states)) {
	    temp = dfa_state;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	dfa_state = Nil;
	nfa_states = Nil;
	ab_loop_list_ = mapping_of_dfa_states_to_nfa_states_2;
	ab_loop_desetq_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	dfa_state = CAR(ab_loop_desetq_);
	nfa_states = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (equivalent_sets_of_nfa_states_p(new_states_represented,
		    nfa_states)) {
	    temp = dfa_state;
	    goto end_2;
	}
	goto next_loop_1;
      end_loop_1:
	temp = Nil;
	goto end_2;
	temp = Qnil;
      end_2:;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* TRANSITION-SUBSET-P */
Object transition_subset_p(transition_1,transition_2)
    Object transition_1, transition_2;
{
    Object relationship, temp;

    x_note_fn_call(31,101);
    relationship = transition_relationship(transition_1,transition_2);
    temp = EQ(relationship,Qab_sub1) ? T : Nil;
    return VALUES_1(temp);
}

/* TRANSITION-HIGHER-PRIORITY */
Object transition_higher_priority(trans_1,trans_2)
    Object trans_1, trans_2;
{
    Object dest_1, dest_2, temp_1, temp_2;
    char temp;

    x_note_fn_call(31,102);
    dest_1 = ISVREF(trans_1,(SI_Long)3L);
    dest_2 = trans_2 ? ISVREF(trans_2,(SI_Long)3L) : Qnil;
    temp =  !TRUEP(dest_2);
    if (temp);
    else {
	temp_1 = ISVREF(dest_1,(SI_Long)1L);
	temp_2 = ISVREF(dest_2,(SI_Long)1L);
	temp = FIXNUM_GT(CAR(temp_1),CAR(temp_2));
    }
    if (temp)
	temp_2 = Nil;
    else {
	temp_2 = ISVREF(dest_1,(SI_Long)1L);
	temp_1 = ISVREF(dest_2,(SI_Long)1L);
	if (FIXNUM_LT(CAR(temp_2),CAR(temp_1)))
	    temp_2 = T;
	else if (ISVREF(dest_1,(SI_Long)2L) &&  !TRUEP(ISVREF(dest_2,
		(SI_Long)2L)))
	    temp_2 = T;
	else if ( !TRUEP(ISVREF(dest_1,(SI_Long)2L)) && ISVREF(dest_2,
		(SI_Long)2L))
	    temp_2 = Nil;
	else
	    temp_2 = transition_subset_p(trans_1,trans_2);
    }
    return VALUES_1(temp_2);
}

static Object Qtransition_higher_priority;  /* transition-higher-priority */

static Object Qtransition_eq;      /* transition= */

/* SORT-TRANSITIONS-DESTRUCTIVELY */
Object sort_transitions_destructively(source_state)
    Object source_state;
{
    Object sorted_list, duplicates, transition, ab_loop_list_;
    Object result;

    x_note_fn_call(31,103);
    result = sort_list_destructively_separating_duplicates(ISVREF(source_state,
	    (SI_Long)3L),SYMBOL_FUNCTION(Qtransition_higher_priority),
	    SYMBOL_FUNCTION(Qtransition_eq));
    MVS_2(result,sorted_list,duplicates);
    SVREF(source_state,FIX((SI_Long)3L)) = sorted_list;
    transition = Nil;
    ab_loop_list_ = duplicates;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    transition = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_transition(transition);
    goto next_loop;
  end_loop:
    reclaim_token_list_1(duplicates);
    return VALUES_1(Nil);
}

/* MAP-DESTINATIONS */
Object map_destinations(source_state,old_mappings)
    Object source_state, old_mappings;
{
    Object temp, current_nfa_states, current_transitions, new_mappings;
    Object nfa_transition, ab_loop_list_, nfa_destinations_qm, dfa_destination;
    Object is_duplicate_qm, new_trans, token_push_modify_macro_arg, car_1;
    Object cdr_1, svref_new_value;

    x_note_fn_call(31,104);
    temp = assq_function(source_state,old_mappings);
    current_nfa_states = CDR(temp);
    current_transitions = all_transitions_from(current_nfa_states);
    new_mappings = Qnil;
    nfa_transition = Nil;
    ab_loop_list_ = current_transitions;
    nfa_destinations_qm = Nil;
    dfa_destination = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    nfa_transition = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    nfa_destinations_qm = possible_moves(current_transitions,nfa_transition);
    if (nfa_destinations_qm) {
	is_duplicate_qm = duplicate_dfa_state_qm(nfa_destinations_qm,
		old_mappings,new_mappings);
	if (is_duplicate_qm) {
	    dfa_destination = is_duplicate_qm;
	    reclaim_token_list_1(nfa_destinations_qm);
	}
	else {
	    dfa_destination = create_fsm_state_for_dfa(nfa_destinations_qm);
	    nfa_destinations_qm = token_cons_1(dfa_destination,
		    nfa_destinations_qm);
	    new_mappings = token_cons_1(nfa_destinations_qm,new_mappings);
	}
	new_trans = replicate_transition(nfa_transition,dfa_destination);
	token_push_modify_macro_arg = new_trans;
	car_1 = token_push_modify_macro_arg;
	cdr_1 = ISVREF(source_state,(SI_Long)3L);
	svref_new_value = token_cons_1(car_1,cdr_1);
	SVREF(source_state,FIX((SI_Long)3L)) = svref_new_value;
    }
    goto next_loop;
  end_loop:
    sort_transitions_destructively(source_state);
    reclaim_token_list_1(current_transitions);
    temp = new_mappings;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* CREATE-DETERMINISTIC-LEXER */
Object create_deterministic_lexer(nondeterministic_lexer)
    Object nondeterministic_lexer;
{
    Object deterministic_lexer, initial_nfa_states, new_start_state;
    Object unmarked_dfa_states, mappings_of_dfa_states_to_nfa_states;
    Object new_mappings, current_state_qm, token_pop_store, cons_1, next_cons;
    Object temp, svref_arg_2, new_mapping, temp_1;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(31,105);
    deterministic_lexer = make_lexing_table_1();
    initial_nfa_states = 
	    e_closure_of_single_state(ISVREF(nondeterministic_lexer,
	    (SI_Long)1L));
    new_start_state = create_fsm_state_for_dfa(initial_nfa_states);
    unmarked_dfa_states = token_cons_1(new_start_state,Nil);
    mappings_of_dfa_states_to_nfa_states = 
	    token_cons_1(token_cons_1(new_start_state,initial_nfa_states),Nil);
    new_mappings = Nil;
    current_state_qm = Nil;
  next_loop:
    token_pop_store = Nil;
    cons_1 = unmarked_dfa_states;
    if (cons_1) {
	token_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qtoken);
	if (ISVREF(Available_token_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_token_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_token_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_token_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_token_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    unmarked_dfa_states = next_cons;
    current_state_qm = token_pop_store;
    if ( !TRUEP(current_state_qm))
	goto end_loop;
    new_mappings = map_destinations(current_state_qm,
	    mappings_of_dfa_states_to_nfa_states);
    if (new_mappings) {
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(length(new_mappings));
	new_mapping = Nil;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop_1;
	token_pop_store = Nil;
	cons_1 = new_mappings;
	if (cons_1) {
	    token_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qtoken);
	    if (ISVREF(Available_token_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_token_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = cons_1;
		temp = Available_token_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    else {
		temp = Available_token_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
		temp = Available_token_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	new_mappings = next_cons;
	new_mapping = token_pop_store;
	unmarked_dfa_states = token_cons_1(CAR(new_mapping),
		unmarked_dfa_states);
	mappings_of_dfa_states_to_nfa_states = token_cons_1(new_mapping,
		mappings_of_dfa_states_to_nfa_states);
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
    }
    goto next_loop;
  end_loop:
    reclaim_token_tree_1(mappings_of_dfa_states_to_nfa_states);
    temp = ISVREF(nondeterministic_lexer,(SI_Long)2L);
    SVREF(deterministic_lexer,FIX((SI_Long)2L)) = temp;
    SVREF(nondeterministic_lexer,FIX((SI_Long)2L)) = Nil;
    SVREF(deterministic_lexer,FIX((SI_Long)1L)) = new_start_state;
    temp = ISVREF(nondeterministic_lexer,(SI_Long)3L);
    SVREF(deterministic_lexer,FIX((SI_Long)3L)) = temp;
    temp_1 = deterministic_lexer;
    goto end_1;
    temp_1 = Qnil;
  end_1:;
    return VALUES_1(temp_1);
}

static Object Qallocate_managed_simple_vector;  /* allocate-managed-simple-vector */

/* COMPILE-LEXING-TABLE */
Object compile_lexing_table(token_defs)
    Object token_defs;
{
    Object temp, the_nfa, the_dfa;

    x_note_fn_call(31,106);
    if ( !TRUEP(token_defs))
	temp = empty_lexing_table();
    else {
	the_nfa = compile_lexing_table_for_nfa(token_defs,
		SYMBOL_FUNCTION(Qallocate_managed_simple_vector));
	the_dfa = create_deterministic_lexer(the_nfa);
	reclaim_nfa(the_nfa);
	temp = the_dfa;
    }
    return VALUES_1(temp);
}

static Object Qsimple_compiled_make_uninitialized_permanent_array;  /* simple-compiled-make-uninitialized-permanent-array */

/* COMPILE-PERMANENT-LEXING-TABLE */
Object compile_permanent_lexing_table(token_defs)
    Object token_defs;
{
    Object temp, the_nfa, the_dfa;

    x_note_fn_call(31,107);
    if ( !TRUEP(token_defs))
	temp = empty_lexing_table();
    else {
	the_nfa = compile_lexing_table_for_nfa(token_defs,
		SYMBOL_FUNCTION(Qsimple_compiled_make_uninitialized_permanent_array));
	the_dfa = create_deterministic_lexer(the_nfa);
	reclaim_nfa(the_nfa);
	temp = the_dfa;
    }
    return VALUES_1(temp);
}

Object No_tokenizer_match_token_type = UNBOUND;

/* APPLY-STATE-TRANSITION-TEST-TO-ARGS */
Object apply_state_transition_test_to_args(transition,element)
    Object transition, element;
{
    Object temp, element_1, class_member, ab_loop_list_, ab_loop_it_;
    Object simple_compiled_function, argument_list, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4;
    SI_Long arg, arg_1, arg_2;
    char temp_1;

    x_note_fn_call(31,108);
    if (FIXNUM_NE(ISVREF(transition,(SI_Long)4L),
	    State_transition_user_defined_transition_test_sentinel)) {
	temp = ISVREF(transition,(SI_Long)4L);
	if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		FIX((SI_Long)127L))))
	    temp_1 = TRUEP(Nil);
	else
	    switch (INTEGER_TO_CHAR(temp)) {
	      case 2:
		element_1 = element;
		class_member = Nil;
		ab_loop_list_ = M_CAR(ISVREF(transition,(SI_Long)2L));
		ab_loop_it_ = Nil;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		class_member = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		arg = IFIX(CAR(class_member));
		arg_1 = IFIX(element_1);
		arg_2 = IFIX(CDR(class_member));
		ab_loop_it_ = arg <= arg_1 ? (arg_1 <= arg_2 ? T : Nil) : Qnil;
		if (ab_loop_it_) {
		    temp_1 = TRUEP(ab_loop_it_);
		    goto end_1;
		}
		goto next_loop;
	      end_loop:
		temp_1 = TRUEP(Qnil);
	      end_1:;
		break;
	      case 1:
		temp_1 = FIXNUM_EQ(element,M_CAR(ISVREF(transition,
			(SI_Long)2L)));
		break;
	      case 0:
		temp_1 = FIXNUMP(element);
		break;
	      default:
		temp_1 = TRUEP(Nil);
		break;
	    }
    }
    else {
	simple_compiled_function = ISVREF(transition,(SI_Long)1L);
	argument_list = ISVREF(transition,(SI_Long)2L);
	temp = ISVREF(transition,(SI_Long)5L);
	if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		FIX((SI_Long)127L))))
	    temp_1 = TRUEP(Nil);
	else
	    switch (INTEGER_TO_CHAR(temp)) {
	      case 0:
		temp_1 = TRUEP(inline_funcall_1(simple_compiled_function,
			element));
		break;
	      case 1:
		gensymed_symbol = simple_compiled_function;
		gensymed_symbol_1 = element;
		temp = M_CAR(argument_list);
		argument_list = M_CDR(argument_list);
		gensymed_symbol_2 = temp;
		temp_1 = TRUEP(inline_funcall_2(gensymed_symbol,
			gensymed_symbol_1,gensymed_symbol_2));
		break;
	      case 2:
		gensymed_symbol = simple_compiled_function;
		gensymed_symbol_1 = element;
		temp = M_CAR(argument_list);
		argument_list = M_CDR(argument_list);
		gensymed_symbol_2 = temp;
		temp = M_CAR(argument_list);
		argument_list = M_CDR(argument_list);
		gensymed_symbol_3 = temp;
		temp_1 = TRUEP(inline_funcall_3(gensymed_symbol,
			gensymed_symbol_1,gensymed_symbol_2,
			gensymed_symbol_3));
		break;
	      case 3:
		gensymed_symbol = simple_compiled_function;
		gensymed_symbol_1 = element;
		temp = M_CAR(argument_list);
		argument_list = M_CDR(argument_list);
		gensymed_symbol_2 = temp;
		temp = M_CAR(argument_list);
		argument_list = M_CDR(argument_list);
		gensymed_symbol_3 = temp;
		temp = M_CAR(argument_list);
		argument_list = M_CDR(argument_list);
		gensymed_symbol_4 = temp;
		temp_1 = TRUEP(inline_funcall_4(gensymed_symbol,
			gensymed_symbol_1,gensymed_symbol_2,
			gensymed_symbol_3,gensymed_symbol_4));
		break;
	      default:
		temp_1 = TRUEP(Nil);
		break;
	    }
    }
    temp = temp_1 ? ISVREF(transition,(SI_Long)3L) : Nil;
    return VALUES_1(temp);
}

static Object Qdo_nothing;         /* do-nothing */

/* GET-LONGEST-TOKEN-BETWEEN-POSITIONS */
Object get_longest_token_between_positions(string_1,start_index,end_index)
    Object string_1, start_index, end_index;
{
    Object index_when_last_token_accepted, current_token, start_state, index_1;
    Object current_character, current_parse_state, next_parse_state;
    Object token_accepted_by_this_state, action_on_last_token;
    Object last_token_accepted, ab_loop_iter_flag_, transition, ab_loop_list_;
    Object answer, temp, svref_new_value;
    Declare_special(1);

    x_note_fn_call(31,109);
    index_when_last_token_accepted = Nil;
    current_token = Nil;
    start_state = Current_start_state;
    index_1 = start_index;
    current_character = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_character,Qcurrent_character,current_character,
	    0);
      current_parse_state = start_state;
      next_parse_state = Nil;
      token_accepted_by_this_state = Nil;
      action_on_last_token = Nil;
      last_token_accepted = Nil;
      ab_loop_iter_flag_ = T;
    next_loop:
      Current_character = FIXNUM_LT(index_1,end_index) ? 
	      FIX(UBYTE_16_ISAREF_1(string_1,IFIX(index_1))) : Qnil;
      if ( !TRUEP(ab_loop_iter_flag_))
	  current_parse_state = next_parse_state;
      if (Current_character && current_parse_state) {
	  transition = Nil;
	  ab_loop_list_ = ISVREF(current_parse_state,(SI_Long)3L);
	  answer = Nil;
	next_loop_1:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  transition = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  answer = apply_state_transition_test_to_args(transition,
		  Current_character);
	  if (answer) {
	      next_parse_state = answer;
	      goto end_1;
	  }
	  goto next_loop_1;
	end_loop:
	  next_parse_state = Qnil;
	end_1:;
      }
      else
	  next_parse_state = Nil;
      token_accepted_by_this_state = next_parse_state ? 
	      ISVREF(next_parse_state,(SI_Long)2L) : Qnil;
      if ( !TRUEP(current_parse_state))
	  goto end_loop_1;
      if (token_accepted_by_this_state) {
	  last_token_accepted = token_accepted_by_this_state;
	  index_when_last_token_accepted = index_1;
      }
      index_1 = FIXNUM_ADD1(index_1);
      ab_loop_iter_flag_ = Nil;
      goto next_loop;
    end_loop_1:
      if ( !TRUEP(last_token_accepted)) {
	  temp = Nil;
	  goto end_2;
      }
      else
	  action_on_last_token = ISVREF(ISVREF(ISVREF(Current_tokenizer,
		  (SI_Long)2L),IFIX(last_token_accepted)),(SI_Long)1L);
      if (EQ(action_on_last_token,Qdo_nothing))
	  temp = get_longest_token_between_positions(string_1,
		  FIXNUM_ADD1(index_when_last_token_accepted),end_index);
      else {
	  current_token = create_parse_object(Nil,Nil);
	  SVREF(current_token,FIX((SI_Long)1L)) = action_on_last_token;
	  SVREF(current_token,FIX((SI_Long)2L)) = start_index;
	  svref_new_value = FIXNUM_ADD1(index_when_last_token_accepted);
	  SVREF(current_token,FIX((SI_Long)3L)) = svref_new_value;
	  temp = current_token;
      }
      goto end_2;
      temp = Qnil;
    end_2:;
    POP_SPECIAL();
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Preprocessing_tokenizer, Qpreprocessing_tokenizer);

/* GET-NEXT-TOKEN-FROM-TEXT-STRING-1 */
Object get_next_token_from_text_string_1(text_string,start_index,end_index_qm)
    Object text_string, start_index, end_index_qm;
{
    Object end_index, index_1, token, nil_token, temp;
    SI_Long length_1, index_new_value;

    x_note_fn_call(31,110);
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(text_string));
    length_1 = UBYTE_16_ISAREF_1(text_string,length_1 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(text_string,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L);
    end_index = end_index_qm && length_1 > IFIX(end_index_qm) ? 
	    end_index_qm : FIX(length_1);
    index_1 = start_index;
    token = Nil;
    if (FIXNUM_GT(index_1,end_index)) {
	nil_token = create_parse_object(Nil,Nil);
	SVREF(nil_token,FIX((SI_Long)1L)) = No_tokenizer_match_token_type;
	SVREF(nil_token,FIX((SI_Long)2L)) = No_tokenizer_match_start_index;
	SVREF(nil_token,FIX((SI_Long)3L)) = No_tokenizer_match_end_index;
	temp = nil_token;
    }
    else if (Current_anchor_p) {
	token = get_longest_token_between_positions(text_string,index_1,
		end_index);
	temp = token;
	if (temp);
	else {
	    nil_token = create_parse_object(Nil,Nil);
	    SVREF(nil_token,FIX((SI_Long)1L)) = No_tokenizer_match_token_type;
	    SVREF(nil_token,FIX((SI_Long)2L)) = No_tokenizer_match_start_index;
	    SVREF(nil_token,FIX((SI_Long)3L)) = No_tokenizer_match_end_index;
	    temp = nil_token;
	}
    }
    else {
      next_loop:
	if ( !( !TRUEP(token) && FIXNUM_LT(index_1,end_index)))
	    goto end_loop;
	token = get_longest_token_between_positions(text_string,index_1,
		end_index);
	if (UBYTE_16_ISAREF_1(text_string,IFIX(index_1)) == 
		IFIX(Alphabet_escape_character) && EQ(Current_tokenizer,
		Preprocessing_tokenizer)) {
	    index_new_value = IFIX(index_1) + (SI_Long)2L;
	    index_1 = FIX(index_new_value);
	}
	else
	    index_1 = FIXNUM_ADD1(index_1);
	goto next_loop;
      end_loop:
	temp = token;
	if (temp);
	else {
	    nil_token = create_parse_object(Nil,Nil);
	    SVREF(nil_token,FIX((SI_Long)1L)) = No_tokenizer_match_token_type;
	    SVREF(nil_token,FIX((SI_Long)2L)) = No_tokenizer_match_start_index;
	    SVREF(nil_token,FIX((SI_Long)3L)) = No_tokenizer_match_end_index;
	    temp = nil_token;
	}
    }
    return VALUES_1(temp);
}

/* LEXEME */
Object lexeme(string_1,token)
    Object string_1, token;
{
    Object end_index, temp, start, wide_string_bv16, result_1, gensymed_symbol;
    Object gensymed_symbol_2;
    SI_Long part_length, bv16_length, aref_arg_2, aref_new_value;
    SI_Long gensymed_symbol_1, gensymed_symbol_3, gensymed_symbol_4;

    x_note_fn_call(31,111);
    end_index = ISVREF(token,(SI_Long)3L);
    if (FIXNUM_EQ(end_index,No_tokenizer_match_end_index))
	temp = Nil;
    else {
	start = ISVREF(token,(SI_Long)2L);
	part_length = IFIX(FIXNUM_MINUS(end_index,start));
	wide_string_bv16 = allocate_byte_vector_16(FIX(part_length + 
		(SI_Long)3L));
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	aref_arg_2 = bv16_length - (SI_Long)2L;
	aref_new_value = part_length & (SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	aref_arg_2 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | part_length >>  -  - (SI_Long)16L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	UBYTE_16_ISASET_1(wide_string_bv16,part_length,(SI_Long)0L);
	result_1 = wide_string_bv16;
	gensymed_symbol = string_1;
	gensymed_symbol_1 = IFIX(start);
	gensymed_symbol_2 = result_1;
	gensymed_symbol_3 = (SI_Long)0L;
	gensymed_symbol_4 = part_length;
	INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
		gensymed_symbol_1,
		UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
		gensymed_symbol_3,gensymed_symbol_4);
	temp = result_1;
    }
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(G2_standard_tokenizer, Qg2_standard_tokenizer);

DEFINE_VARIABLE_WITH_SYMBOL(G2_simple_tokenizer, Qg2_simple_tokenizer);

DEFINE_VARIABLE_WITH_SYMBOL(G2_load_kb_tokenizer, Qg2_load_kb_tokenizer);

DEFINE_VARIABLE_WITH_SYMBOL(G2_tokenizer_tokenizer, Qg2_tokenizer_tokenizer);

DEFINE_VARIABLE_WITH_SYMBOL(G2_symbol_tokenizer, Qg2_symbol_tokenizer);

DEFINE_VARIABLE_WITH_SYMBOL(G2_comment_tokenizer, Qg2_comment_tokenizer);

DEFINE_VARIABLE_WITH_SYMBOL(Regular_expression_tokenizer, Qregular_expression_tokenizer);

/* REGULAR-EXPRESSION-LEXEME */
Object regular_expression_lexeme(string_1,token)
    Object string_1, token;
{
    Object end_index, temp;

    x_note_fn_call(31,112);
    end_index = ISVREF(token,(SI_Long)3L);
    temp = FIXNUM_EQ(end_index,No_tokenizer_match_end_index) ? Nil : 
	    FIX(UBYTE_16_ISAREF_1(string_1,IFIX(FIXNUM_SUB1(end_index))));
    return VALUES_1(temp);
}

Object The_type_description_of_text_tokenization_state = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_text_tokenization_states, Qchain_of_available_text_tokenization_states);

DEFINE_VARIABLE_WITH_SYMBOL(Text_tokenization_state_count, Qtext_tokenization_state_count);

Object Chain_of_available_text_tokenization_states_vector = UNBOUND;

/* TEXT-TOKENIZATION-STATE-STRUCTURE-MEMORY-USAGE */
Object text_tokenization_state_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(31,113);
    temp = Text_tokenization_state_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)17L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-TEXT-TOKENIZATION-STATE-COUNT */
Object outstanding_text_tokenization_state_count()
{
    Object def_structure_text_tokenization_state_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(31,114);
    gensymed_symbol = IFIX(Text_tokenization_state_count);
    def_structure_text_tokenization_state_variable = 
	    Chain_of_available_text_tokenization_states;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_text_tokenization_state_variable))
	goto end_loop;
    def_structure_text_tokenization_state_variable = 
	    ISVREF(def_structure_text_tokenization_state_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-TEXT-TOKENIZATION-STATE-1 */
Object reclaim_text_tokenization_state_1(text_tokenization_state)
    Object text_tokenization_state;
{
    Object temp, svref_arg_2;

    x_note_fn_call(31,115);
    inline_note_reclaim_cons(text_tokenization_state,Nil);
    temp = ISVREF(Chain_of_available_text_tokenization_states_vector,
	    IFIX(Current_thread_index));
    SVREF(text_tokenization_state,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_text_tokenization_states_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = text_tokenization_state;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-TEXT-TOKENIZATION-STATE */
Object reclaim_structure_for_text_tokenization_state(text_tokenization_state)
    Object text_tokenization_state;
{
    x_note_fn_call(31,116);
    return reclaim_text_tokenization_state_1(text_tokenization_state);
}

static Object Qg2_defstruct_structure_name_text_tokenization_state_g2_struct;  /* g2-defstruct-structure-name::text-tokenization-state-g2-struct */

/* MAKE-PERMANENT-TEXT-TOKENIZATION-STATE-STRUCTURE-INTERNAL */
Object make_permanent_text_tokenization_state_structure_internal()
{
    Object def_structure_text_tokenization_state_variable;
    Object defstruct_g2_text_tokenization_state_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(31,117);
    def_structure_text_tokenization_state_variable = Nil;
    atomic_incff_symval(Qtext_tokenization_state_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_text_tokenization_state_variable = Nil;
	gensymed_symbol = (SI_Long)17L;
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
	defstruct_g2_text_tokenization_state_variable = the_array;
	SVREF(defstruct_g2_text_tokenization_state_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_text_tokenization_state_g2_struct;
	def_structure_text_tokenization_state_variable = 
		defstruct_g2_text_tokenization_state_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_text_tokenization_state_variable);
}

/* MAKE-TEXT-TOKENIZATION-STATE-1 */
Object make_text_tokenization_state_1()
{
    Object def_structure_text_tokenization_state_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(31,118);
    def_structure_text_tokenization_state_variable = 
	    ISVREF(Chain_of_available_text_tokenization_states_vector,
	    IFIX(Current_thread_index));
    if (def_structure_text_tokenization_state_variable) {
	svref_arg_1 = Chain_of_available_text_tokenization_states_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_text_tokenization_state_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_text_tokenization_state_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_text_tokenization_state_g2_struct;
    }
    else
	def_structure_text_tokenization_state_variable = 
		make_permanent_text_tokenization_state_structure_internal();
    inline_note_allocate_cons(def_structure_text_tokenization_state_variable,
	    Nil);
    SVREF(def_structure_text_tokenization_state_variable,FIX((SI_Long)2L)) 
	    = Nil;
    ISVREF(def_structure_text_tokenization_state_variable,(SI_Long)3L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_text_tokenization_state_variable,(SI_Long)4L) = 
	    FIX((SI_Long)1L);
    SVREF(def_structure_text_tokenization_state_variable,FIX((SI_Long)7L)) 
	    = Nil;
    SVREF(def_structure_text_tokenization_state_variable,FIX((SI_Long)8L)) 
	    = Nil;
    SVREF(def_structure_text_tokenization_state_variable,FIX((SI_Long)9L)) 
	    = Nil;
    SVREF(def_structure_text_tokenization_state_variable,
	    FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_text_tokenization_state_variable,
	    FIX((SI_Long)12L)) = Nil;
    ISVREF(def_structure_text_tokenization_state_variable,(SI_Long)15L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_text_tokenization_state_variable,
	    FIX((SI_Long)16L)) = Nil;
    return VALUES_1(def_structure_text_tokenization_state_variable);
}

Object The_type_description_of_g2_token = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_g2_tokens, Qchain_of_available_g2_tokens);

DEFINE_VARIABLE_WITH_SYMBOL(G2_token_count, Qg2_token_count);

Object Chain_of_available_g2_tokens_vector = UNBOUND;

/* G2-TOKEN-STRUCTURE-MEMORY-USAGE */
Object g2_token_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(31,119);
    temp = G2_token_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)7L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-G2-TOKEN-COUNT */
Object outstanding_g2_token_count()
{
    Object def_structure_g2_token_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(31,120);
    gensymed_symbol = IFIX(G2_token_count);
    def_structure_g2_token_variable = Chain_of_available_g2_tokens;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_g2_token_variable))
	goto end_loop;
    def_structure_g2_token_variable = 
	    ISVREF(def_structure_g2_token_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-G2-TOKEN-1 */
Object reclaim_g2_token_1(g2_token)
    Object g2_token;
{
    Object temp, svref_arg_2;

    x_note_fn_call(31,121);
    inline_note_reclaim_cons(g2_token,Nil);
    temp = ISVREF(Chain_of_available_g2_tokens_vector,
	    IFIX(Current_thread_index));
    SVREF(g2_token,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_g2_tokens_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = g2_token;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-G2-TOKEN */
Object reclaim_structure_for_g2_token(g2_token)
    Object g2_token;
{
    x_note_fn_call(31,122);
    return reclaim_g2_token_1(g2_token);
}

static Object Qg2_defstruct_structure_name_g2_token_g2_struct;  /* g2-defstruct-structure-name::g2-token-g2-struct */

/* MAKE-PERMANENT-G2-TOKEN-STRUCTURE-INTERNAL */
Object make_permanent_g2_token_structure_internal()
{
    Object def_structure_g2_token_variable, defstruct_g2_g2_token_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(31,123);
    def_structure_g2_token_variable = Nil;
    atomic_incff_symval(Qg2_token_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_g2_token_variable = Nil;
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
	defstruct_g2_g2_token_variable = the_array;
	SVREF(defstruct_g2_g2_token_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_g2_token_g2_struct;
	def_structure_g2_token_variable = defstruct_g2_g2_token_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_g2_token_variable);
}

/* MAKE-G2-TOKEN-1 */
Object make_g2_token_1()
{
    Object def_structure_g2_token_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(31,124);
    def_structure_g2_token_variable = 
	    ISVREF(Chain_of_available_g2_tokens_vector,
	    IFIX(Current_thread_index));
    if (def_structure_g2_token_variable) {
	svref_arg_1 = Chain_of_available_g2_tokens_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_g2_token_variable,(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_g2_token_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_g2_token_g2_struct;
    }
    else
	def_structure_g2_token_variable = 
		make_permanent_g2_token_structure_internal();
    inline_note_allocate_cons(def_structure_g2_token_variable,Nil);
    SVREF(def_structure_g2_token_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_g2_token_variable,FIX((SI_Long)6L)) = Nil;
    return VALUES_1(def_structure_g2_token_variable);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_text_tokenization_state, Qcurrent_text_tokenization_state);

DEFINE_VARIABLE_WITH_SYMBOL(Tokenize_with_editing_context_p, Qtokenize_with_editing_context_p);

Object Tokenizer_illegal_character_error_message = UNBOUND;

/* STATE-ACCEPTS-TOKEN-P */
Object state_accepts_token_p(tokenizer_state,token_type)
    Object tokenizer_state, token_type;
{
    Object token_index, temp;

    x_note_fn_call(31,125);
    token_index = ISVREF(tokenizer_state,(SI_Long)2L);
    temp = token_index ? (EQ(ISVREF(ISVREF(ISVREF(Current_tokenizer,
	    (SI_Long)2L),IFIX(token_index)),(SI_Long)1L),token_type) ? T : 
	    Nil) : Qnil;
    return VALUES_1(temp);
}

/* STATE-POTENTIALLY-ACCEPTS-TOKEN-P */
Object state_potentially_accepts_token_p(tokenizer_state,token_type)
    Object tokenizer_state, token_type;
{
    Object token_number, ab_loop_list_, token_symbol, ab_loop_it_, temp;

    x_note_fn_call(31,126);
    token_number = Nil;
    ab_loop_list_ = ISVREF(tokenizer_state,(SI_Long)1L);
    token_symbol = Nil;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    token_number = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    token_symbol = ISVREF(ISVREF(ISVREF(Current_tokenizer,(SI_Long)2L),
	    IFIX(token_number)),(SI_Long)1L);
    ab_loop_it_ = EQ(token_symbol,token_type) ? T : Nil;
    if (ab_loop_it_) {
	temp = ab_loop_it_;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

static Object Qcomment;            /* comment */

static Object Qsingle_line_comment;  /* single-line-comment */

/* GET-NEXT-WIDE-CHARACTER-FROM-TEXT */
Object get_next_wide_character_from_text(tokenizer_state)
    Object tokenizer_state;
{
    Object svref_arg_1, svref_new_value;

    x_note_fn_call(31,127);
    get_next_wide_character_from_text_1();
    if (EQ(FIX((SI_Long)46L),ISVREF(Current_text_tokenization_state,
	    (SI_Long)2L)) &&  
	    !TRUEP(ISVREF(Current_text_tokenization_state,(SI_Long)16L)) 
	    &&  !(state_accepts_token_p(tokenizer_state,Qcomment) || 
	    state_accepts_token_p(tokenizer_state,Qsingle_line_comment))) {
	svref_arg_1 = Current_text_tokenization_state;
	svref_new_value = FIXNUM_ADD1(ISVREF(svref_arg_1,(SI_Long)15L));
	SVREF(svref_arg_1,FIX((SI_Long)15L)) = svref_new_value;
    }
    else {
	svref_arg_1 = Current_text_tokenization_state;
	ISVREF(svref_arg_1,(SI_Long)15L) = FIX((SI_Long)0L);
    }
    if (EQ(FIX((SI_Long)64L),ISVREF(Current_text_tokenization_state,
	    (SI_Long)2L))) {
	svref_arg_1 = Current_text_tokenization_state;
	SVREF(svref_arg_1,FIX((SI_Long)16L)) = T;
    }
    else {
	svref_arg_1 = Current_text_tokenization_state;
	SVREF(svref_arg_1,FIX((SI_Long)16L)) = Nil;
    }
    return VALUES_1(Nil);
}

/* GET-NEXT-WIDE-CHARACTER-FROM-TEXT-1 */
Object get_next_wide_character_from_text_1()
{
    Object svref_arg_1, temp, temp_1, svref_old_value, svref_new_value;
    Object svref_new_value_1, text_line, line_length, lost_space;
    Object next_text_tail_qm;
    SI_Long svref_new_value_2;
    char temp_2;
    Object result;

    x_note_fn_call(31,128);
  next_loop:
    if (ISVREF(Current_text_tokenization_state,(SI_Long)7L) && 
	    (FIXNUM_GT(ISVREF(Current_text_tokenization_state,(SI_Long)4L),
	    ISVREF(Current_text_tokenization_state,(SI_Long)8L)) || 
	    FIXNUM_EQ(ISVREF(Current_text_tokenization_state,(SI_Long)4L),
	    ISVREF(Current_text_tokenization_state,(SI_Long)8L)) && 
	    FIXNUM_GE(ISVREF(Current_text_tokenization_state,(SI_Long)3L),
	    ISVREF(Current_text_tokenization_state,(SI_Long)7L)))) {
	svref_arg_1 = Current_text_tokenization_state;
	temp = FIXNUM_ADD1(ISVREF(svref_arg_1,(SI_Long)3L));
	SVREF(svref_arg_1,FIX((SI_Long)3L)) = temp;
	svref_arg_1 = Current_text_tokenization_state;
	SVREF(svref_arg_1,FIX((SI_Long)2L)) = Nil;
	goto end_loop;
    }
    else {
	if (FIXNUM_GE(ISVREF(Current_text_tokenization_state,(SI_Long)3L),
		ISVREF(Current_text_tokenization_state,(SI_Long)5L))) {
	    temp_1 = FIXNUM_MINUS(ISVREF(Current_text_tokenization_state,
		    (SI_Long)3L),ISVREF(Current_text_tokenization_state,
		    (SI_Long)5L));
	    temp_2 = FIXNUM_GE(temp_1,
		    FIXNUMP(ISVREF(Current_text_tokenization_state,
		    (SI_Long)6L)) ? ISVREF(Current_text_tokenization_state,
		    (SI_Long)6L) : 
		    text_string_length(ISVREF(Current_text_tokenization_state,
		    (SI_Long)6L)));
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    svref_arg_1 = Current_text_tokenization_state;
	    temp = FIXNUM_ADD1(ISVREF(svref_arg_1,(SI_Long)4L));
	    SVREF(svref_arg_1,FIX((SI_Long)4L)) = temp;
	    svref_arg_1 = Current_text_tokenization_state;
	    temp = ISVREF(Current_text_tokenization_state,(SI_Long)3L);
	    SVREF(svref_arg_1,FIX((SI_Long)14L)) = temp;
	    svref_arg_1 = Current_text_tokenization_state;
	    ISVREF(svref_arg_1,(SI_Long)3L) = FIX((SI_Long)0L);
	    if ( !TRUEP(ISVREF(Current_text_tokenization_state,
			(SI_Long)12L))) {
		svref_arg_1 = Current_text_tokenization_state;
		SVREF(svref_arg_1,FIX((SI_Long)2L)) = Nil;
		svref_arg_1 = Current_text_tokenization_state;
		temp = FIXNUM_SUB1(ISVREF(svref_arg_1,(SI_Long)4L));
		SVREF(svref_arg_1,FIX((SI_Long)4L)) = temp;
		svref_arg_1 = Current_text_tokenization_state;
		temp = ISVREF(Current_text_tokenization_state,(SI_Long)14L);
		SVREF(svref_arg_1,FIX((SI_Long)3L)) = temp;
		svref_arg_1 = Current_text_tokenization_state;
		SVREF(svref_arg_1,FIX((SI_Long)14L)) = Nil;
		goto end_loop;
	    }
	    svref_arg_1 = Current_text_tokenization_state;
	    svref_old_value = ISVREF(svref_arg_1,(SI_Long)10L);
	    temp = Current_text_tokenization_state;
	    svref_new_value = ISVREF(temp,(SI_Long)11L);
	    svref_new_value_1 = ISVREF(Current_text_tokenization_state,
		    (SI_Long)12L);
	    SVREF(svref_arg_1,FIX((SI_Long)10L)) = svref_new_value;
	    SVREF(temp,FIX((SI_Long)11L)) = svref_new_value_1;
	    result = get_next_text_line(ISVREF(Current_text_tokenization_state,
		    (SI_Long)11L));
	    MVS_4(result,text_line,line_length,lost_space,next_text_tail_qm);
	    svref_arg_1 = Current_text_tokenization_state;
	    temp = ISVREF(Current_text_tokenization_state,(SI_Long)3L);
	    SVREF(svref_arg_1,FIX((SI_Long)14L)) = temp;
	    svref_arg_1 = Current_text_tokenization_state;
	    SVREF(svref_arg_1,FIX((SI_Long)1L)) = text_line;
	    svref_arg_1 = Current_text_tokenization_state;
	    temp = ISVREF(Current_text_tokenization_state,(SI_Long)7L) && 
		    FIXNUM_EQ(ISVREF(Current_text_tokenization_state,
		    (SI_Long)4L),ISVREF(Current_text_tokenization_state,
		    (SI_Long)8L)) && 
		    FIXNUM_LT(ISVREF(Current_text_tokenization_state,
		    (SI_Long)7L),line_length) ? 
		    ISVREF(Current_text_tokenization_state,(SI_Long)7L) : 
		    line_length;
	    SVREF(svref_arg_1,FIX((SI_Long)5L)) = temp;
	    svref_arg_1 = Current_text_tokenization_state;
	    SVREF(svref_arg_1,FIX((SI_Long)6L)) = lost_space;
	    svref_arg_1 = Current_text_tokenization_state;
	    SVREF(svref_arg_1,FIX((SI_Long)12L)) = next_text_tail_qm;
	}
	else if (FIXNUM_LT(ISVREF(Current_text_tokenization_state,
		(SI_Long)3L),ISVREF(Current_text_tokenization_state,
		(SI_Long)5L))) {
	    svref_arg_1 = Current_text_tokenization_state;
	    svref_new_value_2 = 
		    UBYTE_16_ISAREF_1(ISVREF(Current_text_tokenization_state,
		    (SI_Long)1L),
		    IFIX(ISVREF(Current_text_tokenization_state,(SI_Long)3L)));
	    ISVREF(svref_arg_1,(SI_Long)2L) = FIX(svref_new_value_2);
	    svref_arg_1 = Current_text_tokenization_state;
	    temp = FIXNUM_ADD1(ISVREF(svref_arg_1,(SI_Long)3L));
	    SVREF(svref_arg_1,FIX((SI_Long)3L)) = temp;
	    goto end_loop;
	}
	else {
	    svref_arg_1 = Current_text_tokenization_state;
	    svref_new_value_2 = 
		    FIXNUMP(ISVREF(Current_text_tokenization_state,
		    (SI_Long)6L)) ? (SI_Long)32L : 
		    UBYTE_16_ISAREF_1(ISVREF(Current_text_tokenization_state,
		    (SI_Long)6L),
		    IFIX(FIXNUM_MINUS(ISVREF(Current_text_tokenization_state,
		    (SI_Long)3L),ISVREF(Current_text_tokenization_state,
		    (SI_Long)5L))));
	    ISVREF(svref_arg_1,(SI_Long)2L) = FIX(svref_new_value_2);
	    svref_arg_1 = Current_text_tokenization_state;
	    temp = FIXNUM_ADD1(ISVREF(svref_arg_1,(SI_Long)3L));
	    SVREF(svref_arg_1,FIX((SI_Long)3L)) = temp;
	    goto end_loop;
	}
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Nil);
}

/* DETERMINE-LEXEME-FOR-COMPLETED-TOKEN */
Object determine_lexeme_for_completed_token(last_valid_state)
    Object last_valid_state;
{
    Object internal_token, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_3, temp;
    SI_Long gensymed_symbol_2;

    x_note_fn_call(31,129);
    internal_token = ISVREF(ISVREF(Current_tokenizer,(SI_Long)2L),
	    IFIX(ISVREF(last_valid_state,(SI_Long)2L)));
    gensymed_symbol = ISVREF(internal_token,(SI_Long)2L);
    gensymed_symbol_1 = Current_wide_string;
    gensymed_symbol_2 = (SI_Long)0L;
    gensymed_symbol_3 = Fill_pointer_for_current_wide_string;
    temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
	    FIX(gensymed_symbol_2),gensymed_symbol_3);
    return VALUES_1(temp);
}

static Object Qleft_string;        /* left-string */

static Object Qmiddle_string;      /* middle-string */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object Qjava_symbol;        /* java-symbol */

/* DETERMINE-LEXEME-FOR-PARTIAL-TOKEN */
Object determine_lexeme_for_partial_token(partial_types)
    Object partial_types;
{
    Object gensymed_symbol, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object i, char_1, temp_2, aref_arg_2, temp_3;
    SI_Long bv16_length, temp_1, aref_new_value, length_1;
    char temp;
    Declare_special(5);

    x_note_fn_call(31,130);
    gensymed_symbol = partial_types;
  next_loop:
    if ( !TRUEP(gensymed_symbol))
	goto end_loop;
    if (EQ(M_CAR(gensymed_symbol),Qleft_string)) {
	temp = TRUEP(gensymed_symbol);
	goto end_1;
    }
    gensymed_symbol = M_CDR(gensymed_symbol);
    goto next_loop;
  end_loop:
    temp = TRUEP(Qnil);
  end_1:;
    if (temp);
    else {
	gensymed_symbol = partial_types;
      next_loop_1:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_1;
	if (EQ(M_CAR(gensymed_symbol),Qmiddle_string)) {
	    temp = TRUEP(gensymed_symbol);
	    goto end_2;
	}
	gensymed_symbol = M_CDR(gensymed_symbol);
	goto next_loop_1;
      end_loop_1:
	temp = TRUEP(Qnil);
      end_2:;
    }
    if (temp) {
	current_wide_string_list = Qdo_not_use;
	PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		4);
	  wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
		  (SI_Long)3L));
	  bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	  temp_1 = bv16_length - (SI_Long)2L;
	  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
	  UBYTE_16_ISASET_1(wide_string_bv16,temp_1,aref_new_value);
	  temp_1 = bv16_length - (SI_Long)1L;
	  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	  UBYTE_16_ISASET_1(wide_string_bv16,temp_1,aref_new_value);
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
		  i = FIX((SI_Long)1L);
		  char_1 = Nil;
		next_loop_2:
		  if (FIXNUM_GE(i,Fill_pointer_for_current_wide_string))
		      goto end_loop_2;
		  char_1 = FIX(UBYTE_16_ISAREF_1(Current_wide_string,IFIX(i)));
		  if (IFIX(char_1) == (SI_Long)64L) {
		      i = FIXNUM_ADD1(i);
		      if ( !FIXNUM_EQ(i,
				  Fill_pointer_for_current_wide_string)) {
			  if ( 
				  !FIXNUM_LT(Fill_pointer_for_current_wide_string,
				  Total_length_of_current_wide_string))
			      extend_current_wide_string(Fill_pointer_for_current_wide_string);
			  temp_2 = Current_wide_string;
			  aref_arg_2 = Fill_pointer_for_current_wide_string;
			  temp_1 = UBYTE_16_ISAREF_1(Current_wide_string,
				  IFIX(i));
			  UBYTE_16_ISASET_1(temp_2,IFIX(aref_arg_2),temp_1);
			  temp_2 = 
				  FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
			  Fill_pointer_for_current_wide_string = temp_2;
		      }
		  }
		  else {
		      if ( !FIXNUM_LT(Fill_pointer_for_current_wide_string,
			      Total_length_of_current_wide_string))
			  extend_current_wide_string(Fill_pointer_for_current_wide_string);
		      temp_2 = Current_wide_string;
		      aref_arg_2 = Fill_pointer_for_current_wide_string;
		      UBYTE_16_ISASET_1(temp_2,IFIX(aref_arg_2),IFIX(char_1));
		      temp_2 = 
			      FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
		      Fill_pointer_for_current_wide_string = temp_2;
		  }
		  i = FIXNUM_ADD1(i);
		  goto next_loop_2;
		end_loop_2:;
		  temp_3 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    else {
	gensymed_symbol = partial_types;
      next_loop_3:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_3;
	if (EQ(M_CAR(gensymed_symbol),Qjava_symbol)) {
	    temp = TRUEP(gensymed_symbol);
	    goto end_3;
	}
	gensymed_symbol = M_CDR(gensymed_symbol);
	goto next_loop_3;
      end_loop_3:
	temp = TRUEP(Qnil);
      end_3:;
	if (temp)
	    temp_3 = 
		    alphabet_substring_for_symbol_function(Current_wide_string,
		    FIX((SI_Long)0L),Fill_pointer_for_current_wide_string,Nil);
	else
	    temp_3 = 
		    alphabet_substring_for_symbol_function(Current_wide_string,
		    FIX((SI_Long)0L),Fill_pointer_for_current_wide_string,T);
    }
    return VALUES_1(temp_3);
}

/* BOGUS-PUNCTUATION-P */
Object bogus_punctuation_p(token_name)
    Object token_name;
{
    Object ambiguous_character, potential_type, immediate_type, ab_loop_list_;
    Object ab_loop_it_, ab_loop_desetq_, temp;

    x_note_fn_call(31,131);
    ambiguous_character = Nil;
    potential_type = Nil;
    immediate_type = Nil;
    ab_loop_list_ = Generally_ambiguous_characters_in_g2_tokenization;
    ab_loop_it_ = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    ambiguous_character = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    potential_type = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CAR(temp);
    immediate_type = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ = EQ(token_name,immediate_type) && 
	    UBYTE_16_ISAREF_1(Current_wide_string,(SI_Long)0L) == 
	    IFIX(ambiguous_character) ? 
	    partial_string_acceptable_p_function(potential_type,
	    ISVREF(Current_text_tokenization_state,(SI_Long)4L),
	    ISVREF(Current_text_tokenization_state,(SI_Long)3L)) : Qnil;
    if (ab_loop_it_) {
	temp = ab_loop_it_;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* COMPLETED-TOKEN-P */
Object completed_token_p(last_valid_index,return_only_completed_tokens_p,
	    degenerate_case_p,self_terminating_p)
    Object last_valid_index, return_only_completed_tokens_p, degenerate_case_p;
    Object self_terminating_p;
{
    Object temp;

    x_note_fn_call(31,132);
    if (last_valid_index) {
	temp = return_only_completed_tokens_p;
	if (temp);
	else if ( !TRUEP(degenerate_case_p)) {
	    temp = self_terminating_p;
	    if (temp);
	    else if (FIXNUM_NE(last_valid_index,
		    ISVREF(Current_text_tokenization_state,(SI_Long)3L))) {
		temp = FIXNUM_NE(ISVREF(Current_text_tokenization_state,
			(SI_Long)4L),
			ISVREF(Current_text_tokenization_state,
			(SI_Long)8L)) ? T : Nil;
		if (temp);
		else
		    temp = 
			    FIXNUM_LT(ISVREF(Current_text_tokenization_state,
			    (SI_Long)3L),
			    ISVREF(Current_text_tokenization_state,
			    (SI_Long)7L)) ? T : Nil;
	    }
	    else
		temp = Nil;
	}
	else
	    temp = Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qquoted_character;   /* quoted-character */

static Object Qwhole_string;       /* whole-string */

static Object Qright_string;       /* right-string */

static Object Qself_terminating_punctuation_mark;  /* self-terminating-punctuation-mark */

static Object Qjava_character_literal;  /* java-character-literal */

static Object Qpunctuation_mark;   /* punctuation-mark */

static Object list_constant;       /* # */

static Object list_constant_1;     /* # */

static Object Qdisambiguated_token;  /* disambiguated-token */

static Object list_constant_2;     /* # */

/* ENCAPSULATE-INFORMATION-INTO-TOKEN */
Object encapsulate_information_into_token(last_valid_state,last_valid_index)
    Object last_valid_state, last_valid_index;
{
    Object token, token_name_qm, associated_rules_on_last_state;
    Object self_terminating_p, bogus_punctuation_p_1, doing_nothing_p, temp;
    Object temp_1, completed_token_p_1, type_or_partial_types, return_token;
    Object prev_ci, temp_2, svref_new_value;
    char return_only_completed_tokens_p;
    Object result;

    x_note_fn_call(31,133);
    token = ISVREF(last_valid_state,(SI_Long)2L);
    token_name_qm = token ? ISVREF(ISVREF(ISVREF(Current_tokenizer,
	    (SI_Long)2L),IFIX(token)),(SI_Long)1L) : Qnil;
    associated_rules_on_last_state = ISVREF(last_valid_state,(SI_Long)1L);
    self_terminating_p = EQ(token_name_qm,Qquoted_character) ? T : Nil;
    if (self_terminating_p);
    else
	self_terminating_p = EQ(token_name_qm,Qwhole_string) ? T : Nil;
    if (self_terminating_p);
    else
	self_terminating_p = EQ(token_name_qm,Qleft_string) ? T : Nil;
    if (self_terminating_p);
    else
	self_terminating_p = EQ(token_name_qm,Qmiddle_string) ? T : Nil;
    if (self_terminating_p);
    else
	self_terminating_p = EQ(token_name_qm,Qright_string) ? T : Nil;
    if (self_terminating_p);
    else
	self_terminating_p = EQ(token_name_qm,
		Qself_terminating_punctuation_mark) ? T : Nil;
    if (self_terminating_p);
    else
	self_terminating_p = EQ(token_name_qm,Qjava_character_literal) ? T 
		: Nil;
    bogus_punctuation_p_1 = bogus_punctuation_p(token_name_qm);
    doing_nothing_p = state_potentially_accepts_token_p(last_valid_state,
	    Qdo_nothing);
    return_only_completed_tokens_p =  
	    !TRUEP(ISVREF(Current_text_tokenization_state,(SI_Long)9L));
    if (token_name_qm) {
	temp = bogus_punctuation_p_1;
	if (temp);
	else
	    temp = doing_nothing_p;
	temp_1 = self_terminating_p;
	if (temp_1);
	else
	    temp_1 =  !TRUEP(associated_rules_on_last_state) ? T : Nil;
	completed_token_p_1 = completed_token_p(last_valid_index,
		return_only_completed_tokens_p ? T : Nil,temp,temp_1);
    }
    else
	completed_token_p_1 = Nil;
    type_or_partial_types = completed_token_p_1 || 
	    return_only_completed_tokens_p ? token_name_qm : 
	    partial_tokens_for_state(associated_rules_on_last_state);
    return_token = make_g2_token_1();
    if (EQ(type_or_partial_types,Qself_terminating_punctuation_mark))
	type_or_partial_types = Qpunctuation_mark;
    if (token_name_qm && EQUAL(type_or_partial_types,list_constant)) {
	type_or_partial_types = Qcomment;
	completed_token_p_1 = T;
    }
    if (token_name_qm && EQUAL(type_or_partial_types,list_constant_1)) {
	type_or_partial_types = Qsingle_line_comment;
	completed_token_p_1 = T;
    }
    if (EQ(type_or_partial_types,Qdisambiguated_token) || 
	    EQUAL(type_or_partial_types,list_constant_2)) {
	if (IFIX(ISVREF(Current_text_tokenization_state,(SI_Long)3L)) == 
		(SI_Long)0L) {
	    if (ISVREF(Current_text_tokenization_state,(SI_Long)10L)) {
		if (EQ(ISVREF(Current_text_tokenization_state,
			(SI_Long)10L),FIX((SI_Long)-1L)));
		else {
		    result = find_previous_character_if_any(FIX((SI_Long)2L),
			    ISVREF(Current_text_tokenization_state,
			    (SI_Long)3L),
			    ISVREF(Current_text_tokenization_state,
			    (SI_Long)10L),
			    ISVREF(Current_text_tokenization_state,
			    (SI_Long)10L));
		    prev_ci = NTH_VALUE((SI_Long)1L, result);
		    temp_2 = Current_text_tokenization_state;
		    svref_new_value = FIXNUM_SUB1(ISVREF(temp_2,(SI_Long)4L));
		    SVREF(temp_2,FIX((SI_Long)4L)) = svref_new_value;
		    temp_2 = Current_text_tokenization_state;
		    SVREF(temp_2,FIX((SI_Long)3L)) = prev_ci;
		    temp_2 = Current_text_tokenization_state;
		    svref_new_value = 
			    ISVREF(Current_text_tokenization_state,
			    (SI_Long)10L);
		    SVREF(temp_2,FIX((SI_Long)11L)) = svref_new_value;
		    temp_2 = Current_text_tokenization_state;
		    ISVREF(temp_2,(SI_Long)10L) = FIX((SI_Long)-1L);
		}
	    }
	}
	else {
	    temp_2 = Current_text_tokenization_state;
	    svref_new_value = FIXNUM_SUB1(ISVREF(temp_2,(SI_Long)3L));
	    SVREF(temp_2,FIX((SI_Long)3L)) = svref_new_value;
	}
	type_or_partial_types = Qsymbol;
	self_terminating_p = Nil;
	completed_token_p_1 = T;
	temp_2 = 
		alphabet_normalized_symbol_from_text_string(Current_wide_string,
		FIX((SI_Long)0L),
		FIXNUM_SUB1(Fill_pointer_for_current_wide_string));
    }
    else if (completed_token_p_1)
	temp_2 = determine_lexeme_for_completed_token(last_valid_state);
    else
	temp_2 = determine_lexeme_for_partial_token(type_or_partial_types);
    SVREF(return_token,FIX((SI_Long)2L)) = temp_2;
    SVREF(return_token,FIX((SI_Long)6L)) = self_terminating_p;
    temp_2 = ISVREF(Current_text_tokenization_state,(SI_Long)4L);
    SVREF(return_token,FIX((SI_Long)3L)) = temp_2;
    temp_2 = ISVREF(Current_text_tokenization_state,(SI_Long)3L);
    SVREF(return_token,FIX((SI_Long)4L)) = temp_2;
    temp_2 = completed_token_p_1 ? ISVREF(Current_text_tokenization_state,
	    (SI_Long)11L) : Qnil;
    SVREF(return_token,FIX((SI_Long)5L)) = temp_2;
    temp_2 = managed_float_p_function(ISVREF(return_token,(SI_Long)2L)) ? 
	    Qfloat : type_or_partial_types;
    SVREF(return_token,FIX((SI_Long)1L)) = temp_2;
    return VALUES_1(return_token);
}

static Object Qellipsis;           /* ellipsis */

/* RETURN-VALUE-FOR-CURRENT-TOKENIZATION-STATE */
Object return_value_for_current_tokenization_state(last_valid_index,
	    last_valid_state)
    Object last_valid_index, last_valid_state;
{
    Object return_token, temp, svref_new_value, token;
    char temp_1;

    x_note_fn_call(31,134);
    if ((SI_Long)3L <= IFIX(ISVREF(Current_text_tokenization_state,
	    (SI_Long)15L))) {
	return_token = make_g2_token_1();
	SVREF(return_token,FIX((SI_Long)2L)) = Nil;
	SVREF(return_token,FIX((SI_Long)1L)) = Qellipsis;
	temp = ISVREF(Current_text_tokenization_state,(SI_Long)4L);
	SVREF(return_token,FIX((SI_Long)3L)) = temp;
	temp = ISVREF(Current_text_tokenization_state,(SI_Long)3L);
	SVREF(return_token,FIX((SI_Long)4L)) = temp;
	SVREF(return_token,FIX((SI_Long)5L)) = Nil;
	SVREF(return_token,FIX((SI_Long)6L)) = Nil;
	return VALUES_1(return_token);
    }
    else if ( !TRUEP(last_valid_state)) {
	if ( !TRUEP(ISVREF(Current_text_tokenization_state,(SI_Long)12L)) 
		&& FIXNUM_LE(ISVREF(Current_text_tokenization_state,
		(SI_Long)5L),ISVREF(Current_text_tokenization_state,
		(SI_Long)3L))) {
	    temp = Current_text_tokenization_state;
	    SVREF(temp,FIX((SI_Long)3L)) = Nil;
	    temp = Current_text_tokenization_state;
	    SVREF(temp,FIX((SI_Long)4L)) = Nil;
	    return_token = make_g2_token_1();
	    SVREF(return_token,FIX((SI_Long)2L)) = Nil;
	    SVREF(return_token,FIX((SI_Long)1L)) = Nil;
	    SVREF(return_token,FIX((SI_Long)3L)) = Nil;
	    SVREF(return_token,FIX((SI_Long)4L)) = Nil;
	    SVREF(return_token,FIX((SI_Long)5L)) = Nil;
	    SVREF(return_token,FIX((SI_Long)6L)) = Nil;
	    return VALUES_1(return_token);
	}
	else if ( !TRUEP(ISVREF(Current_text_tokenization_state,
		    (SI_Long)2L))) {
	    temp = Current_text_tokenization_state;
	    svref_new_value = FIXNUM_SUB1(ISVREF(temp,(SI_Long)3L));
	    SVREF(temp,FIX((SI_Long)3L)) = svref_new_value;
	    return_token = make_g2_token_1();
	    SVREF(return_token,FIX((SI_Long)2L)) = Nil;
	    SVREF(return_token,FIX((SI_Long)1L)) = Nil;
	    temp = ISVREF(Current_text_tokenization_state,(SI_Long)4L);
	    SVREF(return_token,FIX((SI_Long)3L)) = temp;
	    temp = ISVREF(Current_text_tokenization_state,(SI_Long)3L);
	    SVREF(return_token,FIX((SI_Long)4L)) = temp;
	    SVREF(return_token,FIX((SI_Long)5L)) = Nil;
	    SVREF(return_token,FIX((SI_Long)6L)) = Nil;
	    return VALUES_1(return_token);
	}
	else {
	    return_token = make_g2_token_1();
	    temp = Tokenizer_illegal_character_error_message;
	    SVREF(return_token,FIX((SI_Long)2L)) = temp;
	    SVREF(return_token,FIX((SI_Long)1L)) = Nil;
	    temp = ISVREF(Current_text_tokenization_state,(SI_Long)4L);
	    SVREF(return_token,FIX((SI_Long)3L)) = temp;
	    temp = ISVREF(Current_text_tokenization_state,(SI_Long)3L);
	    SVREF(return_token,FIX((SI_Long)4L)) = temp;
	    SVREF(return_token,FIX((SI_Long)5L)) = Nil;
	    SVREF(return_token,FIX((SI_Long)6L)) = Nil;
	    return VALUES_1(return_token);
	}
    }
    else {
	if (last_valid_state && ISVREF(last_valid_state,(SI_Long)2L)) {
	    token = ISVREF(last_valid_state,(SI_Long)2L);
	    temp_1 = EQ(Qdo_nothing,token ? 
		    ISVREF(ISVREF(ISVREF(Current_tokenizer,(SI_Long)2L),
		    IFIX(token)),(SI_Long)1L) : Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    if (ISVREF(Current_text_tokenization_state,(SI_Long)2L)) {
		temp = Current_text_tokenization_state;
		svref_new_value = FIXNUM_SUB1(ISVREF(temp,(SI_Long)3L));
		SVREF(temp,FIX((SI_Long)3L)) = svref_new_value;
	    }
	    Fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	    temp = Current_text_tokenization_state;
	    ISVREF(temp,(SI_Long)15L) = FIX((SI_Long)0L);
	    return get_next_token_or_partial_tokens_from_text();
	}
	else {
	    if (ISVREF(Current_text_tokenization_state,(SI_Long)2L)) {
		last_valid_index = FIXNUM_SUB1(last_valid_index);
		temp = Current_text_tokenization_state;
		svref_new_value = FIXNUM_SUB1(ISVREF(temp,(SI_Long)3L));
		SVREF(temp,FIX((SI_Long)3L)) = svref_new_value;
	    }
	    else if (FIXNUM_GT(ISVREF(Current_text_tokenization_state,
		    (SI_Long)3L),ISVREF(Current_text_tokenization_state,
		    (SI_Long)5L))) {
		temp = Current_text_tokenization_state;
		svref_new_value = FIXNUM_SUB1(ISVREF(temp,(SI_Long)3L));
		SVREF(temp,FIX((SI_Long)3L)) = svref_new_value;
	    }
	    return encapsulate_information_into_token(last_valid_state,
		    last_valid_index);
	}
    }
}

static Object Qcbt;                /* ] */

/* GET-NEXT-TOKEN-OR-PARTIAL-TOKENS-FROM-TEXT */
Object get_next_token_or_partial_tokens_from_text()
{
    Object start_state, last_valid_index, last_valid_state, token_too_long_p;
    Object active_parse_state, current_character, next_parse_state;
    Object short_circuit_p, associated_rules_on_next_state, transition;
    Object ab_loop_list_, answer, temp, temp_1, aref_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(31,135);
    get_next_wide_character_from_text(Current_start_state);
    start_state = Current_start_state;
    last_valid_index = Nil;
    last_valid_state = Nil;
    token_too_long_p = Nil;
    active_parse_state = start_state;
    current_character = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_character,Qcurrent_character,current_character,
	    0);
      next_parse_state = Nil;
      short_circuit_p = Nil;
      associated_rules_on_next_state = Nil;
    next_loop:
      if ( !TRUEP(ISVREF(Current_text_tokenization_state,(SI_Long)2L)))
	  goto end_loop;
      if ((SI_Long)3L <= IFIX(ISVREF(Current_text_tokenization_state,
	      (SI_Long)15L)))
	  goto end_loop;
      Current_character = ISVREF(Current_text_tokenization_state,(SI_Long)2L);
      if (Current_character && active_parse_state) {
	  transition = Nil;
	  ab_loop_list_ = ISVREF(active_parse_state,(SI_Long)3L);
	  answer = Nil;
	next_loop_1:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_1;
	  transition = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  answer = apply_state_transition_test_to_args(transition,
		  Current_character);
	  if (answer) {
	      next_parse_state = answer;
	      goto end_1;
	  }
	  goto next_loop_1;
	end_loop_1:
	  next_parse_state = Qnil;
	end_1:;
      }
      else
	  next_parse_state = Nil;
      short_circuit_p = Fill_pointer_for_current_wide_string && 
	      (SI_Long)0L == IFIX(Fill_pointer_for_current_wide_string) && 
	      (SI_Long)93L == IFIX(ISVREF(Current_text_tokenization_state,
	      (SI_Long)2L)) ? 
	      instance_of_token_acceptable_in_current_edit_state_p(Qcbt,
	      ISVREF(Current_text_tokenization_state,(SI_Long)4L),
	      ISVREF(Current_text_tokenization_state,(SI_Long)3L)) : Qnil;
      if (short_circuit_p) {
	  last_valid_state = next_parse_state;
	  if ( !FIXNUM_LT(Fill_pointer_for_current_wide_string,
		  Total_length_of_current_wide_string))
	      extend_current_wide_string(Fill_pointer_for_current_wide_string);
	  temp = Current_wide_string;
	  temp_1 = Fill_pointer_for_current_wide_string;
	  aref_new_value = Current_character;
	  UBYTE_16_ISASET_1(temp,IFIX(temp_1),IFIX(aref_new_value));
	  temp = FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
	  Fill_pointer_for_current_wide_string = temp;
	  last_valid_index = ISVREF(Current_text_tokenization_state,
		  (SI_Long)3L);
	  temp = Current_text_tokenization_state;
	  temp_1 = FIXNUM_ADD1(ISVREF(temp,(SI_Long)3L));
	  SVREF(temp,FIX((SI_Long)3L)) = temp_1;
	  active_parse_state = Nil;
      }
      if ( !TRUEP(active_parse_state))
	  goto end_loop;
      associated_rules_on_next_state = next_parse_state ? 
	      ISVREF(next_parse_state,(SI_Long)1L) : Qnil;
      if (associated_rules_on_next_state) {
	  last_valid_index = ISVREF(Current_text_tokenization_state,
		  (SI_Long)3L);
	  last_valid_state = next_parse_state;
      }
      if (next_parse_state) {
	  if (FIXNUM_LT(Fill_pointer_for_current_wide_string,
		  Maximum_length_for_user_text_strings)) {
	      if ( !FIXNUM_LT(Fill_pointer_for_current_wide_string,
		      Total_length_of_current_wide_string))
		  extend_current_wide_string(Fill_pointer_for_current_wide_string);
	      temp = Current_wide_string;
	      temp_1 = Fill_pointer_for_current_wide_string;
	      aref_new_value = Current_character;
	      UBYTE_16_ISASET_1(temp,IFIX(temp_1),IFIX(aref_new_value));
	      temp = FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
	      Fill_pointer_for_current_wide_string = temp;
	  }
	  else if ( !TRUEP(token_too_long_p)) {
	      token_too_long_p = T;
	      warn_of_too_long_token_truncation();
	  }
	  get_next_wide_character_from_text(next_parse_state);
      }
      active_parse_state = next_parse_state;
      goto next_loop;
    end_loop:
      result = return_value_for_current_tokenization_state(last_valid_index,
	      last_valid_state);
      goto end_2;
      result = VALUES_1(Qnil);
    end_2:;
    POP_SPECIAL();
    return result;
}

static Object string_constant_1;   /* "Warning: a token (starting with: ~a...) must be ~
				    *        truncated because it is too long, more than ~d characters."
				    */

/* WARN-OF-TOO-LONG-TOKEN-TRUNCATION */
Object warn_of_too_long_token_truncation()
{
    Object string_beginning, gensymed_symbol, gensymed_symbol_2;
    SI_Long n_1, arg, arg_1, arg_2, gensymed_symbol_1, gensymed_symbol_3;
    SI_Long gensymed_symbol_4, bv16_length, aref_arg_2, aref_new_value;
    char temp;

    x_note_fn_call(31,136);
    n_1 = (SI_Long)20L;
    string_beginning = make_stringw_function(FIX(n_1),Nil);
    if (EQ(Current_wide_string,string_beginning)) {
	if ((SI_Long)0L == n_1)
	    temp = TRUEP(T);
	else {
	    temp = (SI_Long)0L < (SI_Long)0L ? (SI_Long)0L < n_1 : TRUEP(Qnil);
	    if (temp);
	    else {
		arg = (SI_Long)0L;
		arg_1 = (SI_Long)0L;
		arg_2 = (SI_Long)0L + (n_1 - (SI_Long)0L);
		temp = arg < arg_1 ? arg_1 < arg_2 : TRUEP(Qnil);
	    }
	    if (temp) {
		copy_byte_vector_16_portion_carefully(Current_wide_string,
			FIX((SI_Long)0L),string_beginning,FIX((SI_Long)0L),
			FIX(n_1 - (SI_Long)0L));
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
	gensymed_symbol = Current_wide_string;
	gensymed_symbol_1 = (SI_Long)0L;
	gensymed_symbol_2 = string_beginning;
	gensymed_symbol_3 = (SI_Long)0L;
	gensymed_symbol_4 = n_1 - (SI_Long)0L;
	INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
		gensymed_symbol_1,
		UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
		gensymed_symbol_3,gensymed_symbol_4);
    }
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_beginning));
    aref_arg_2 = bv16_length - (SI_Long)2L;
    aref_new_value = n_1 & (SI_Long)65535L;
    UBYTE_16_ISASET_1(string_beginning,aref_arg_2,aref_new_value);
    aref_arg_2 = bv16_length - (SI_Long)1L;
    aref_new_value = (SI_Long)57344L | n_1 >>  -  - (SI_Long)16L;
    UBYTE_16_ISASET_1(string_beginning,aref_arg_2,aref_new_value);
    UBYTE_16_ISASET_1(string_beginning,n_1,(SI_Long)0L);
    return notify_user_at_console(3,string_constant_1,string_beginning,
	    Maximum_length_for_user_text_strings);
}

/* NEW-GET-NEXT-TOKEN-FROM-WIDE-TEXT-IF-AVAILABLE-1 */
Object new_get_next_token_from_wide_text_if_available_1(tokenizer,
	    text_tail,line_index,character_index,end_line_index_qm,
	    end_character_index_qm,return_partial_tokens_qm)
    Object tokenizer, text_tail, line_index, character_index;
    Object end_line_index_qm, end_character_index_qm, return_partial_tokens_qm;
{
    Object current_tokenizer, current_start_state, current_anchor_p;
    Object svref_arg_1, text_line, line_length, lost_space, next_text_tail_qm;
    Object svref_new_value, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object gensymed_symbol, new_token, token_value;
    Object token_type_or_partial_types, line_index_for_end_of_token;
    Object character_index_after_token, next_text_tail, self_terminating_p;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(8);
    Object result;

    x_note_fn_call(31,137);
    current_tokenizer = tokenizer;
    PUSH_SPECIAL_WITH_SYMBOL(Current_tokenizer,Qcurrent_tokenizer,current_tokenizer,
	    7);
      current_start_state = ISVREF(Current_tokenizer,(SI_Long)1L);
      PUSH_SPECIAL_WITH_SYMBOL(Current_start_state,Qcurrent_start_state,current_start_state,
	      6);
	current_anchor_p = ISVREF(Current_tokenizer,(SI_Long)3L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_anchor_p,Qcurrent_anchor_p,current_anchor_p,
		5);
	  svref_arg_1 = Current_text_tokenization_state;
	  SVREF(svref_arg_1,FIX((SI_Long)3L)) = character_index;
	  svref_arg_1 = Current_text_tokenization_state;
	  SVREF(svref_arg_1,FIX((SI_Long)4L)) = line_index;
	  svref_arg_1 = Current_text_tokenization_state;
	  SVREF(svref_arg_1,FIX((SI_Long)11L)) = text_tail;
	  svref_arg_1 = Current_text_tokenization_state;
	  SVREF(svref_arg_1,FIX((SI_Long)7L)) = end_character_index_qm;
	  svref_arg_1 = Current_text_tokenization_state;
	  SVREF(svref_arg_1,FIX((SI_Long)8L)) = end_line_index_qm;
	  svref_arg_1 = Current_text_tokenization_state;
	  SVREF(svref_arg_1,FIX((SI_Long)9L)) = return_partial_tokens_qm;
	  result = get_next_text_line(ISVREF(Current_text_tokenization_state,
		  (SI_Long)11L));
	  MVS_4(result,text_line,line_length,lost_space,next_text_tail_qm);
	  svref_arg_1 = Current_text_tokenization_state;
	  svref_new_value = ISVREF(Current_text_tokenization_state,
		  (SI_Long)3L);
	  SVREF(svref_arg_1,FIX((SI_Long)14L)) = svref_new_value;
	  svref_arg_1 = Current_text_tokenization_state;
	  SVREF(svref_arg_1,FIX((SI_Long)1L)) = text_line;
	  svref_arg_1 = Current_text_tokenization_state;
	  svref_new_value = ISVREF(Current_text_tokenization_state,
		  (SI_Long)7L) && 
		  FIXNUM_EQ(ISVREF(Current_text_tokenization_state,
		  (SI_Long)4L),ISVREF(Current_text_tokenization_state,
		  (SI_Long)8L)) && 
		  FIXNUM_LT(ISVREF(Current_text_tokenization_state,
		  (SI_Long)7L),line_length) ? 
		  ISVREF(Current_text_tokenization_state,(SI_Long)7L) : 
		  line_length;
	  SVREF(svref_arg_1,FIX((SI_Long)5L)) = svref_new_value;
	  svref_arg_1 = Current_text_tokenization_state;
	  SVREF(svref_arg_1,FIX((SI_Long)6L)) = lost_space;
	  svref_arg_1 = Current_text_tokenization_state;
	  SVREF(svref_arg_1,FIX((SI_Long)12L)) = next_text_tail_qm;
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
		    gensymed_symbol = 
			    get_next_token_or_partial_tokens_from_text();
		    reclaim_wide_string(Current_wide_string);
		    new_token = gensymed_symbol;
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  token_value = ISVREF(new_token,(SI_Long)2L);
	  token_type_or_partial_types = ISVREF(new_token,(SI_Long)1L);
	  line_index_for_end_of_token = ISVREF(new_token,(SI_Long)3L);
	  character_index_after_token = ISVREF(new_token,(SI_Long)4L);
	  next_text_tail = ISVREF(new_token,(SI_Long)5L);
	  self_terminating_p = ISVREF(new_token,(SI_Long)6L);
	  if (ATOM(token_type_or_partial_types) && 
		  (EQ(token_type_or_partial_types,Qwhole_string) || 
		  EQ(token_type_or_partial_types,Qleft_string) || 
		  EQ(token_type_or_partial_types,Qright_string) || 
		  EQ(token_type_or_partial_types,Qmiddle_string)) && 
		  Tokenize_with_editing_context_p)
	      note_use_of_text_string_in_phrase(token_value);
	  reclaim_g2_token_1(new_token);
	  result = VALUES_6(token_value,token_type_or_partial_types,
		  line_index_for_end_of_token,character_index_after_token,
		  next_text_tail,self_terminating_p);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* TOKENIZE-TEXT-STRING */
Object tokenize_text_string(text_string_qm,tokenizer)
    Object text_string_qm, tokenizer;
{
    Object char_index_qm, return_value, text, temp, token_value, temp_1;
    Object character_index_after_token;
    Object result;

    x_note_fn_call(31,138);
    if (text_string_qm) {
	char_index_qm = FIX((SI_Long)0L);
	return_value = Qnil;
	text = token_cons_1(text_string_qm,Nil);
      next_loop:
	if ( !TRUEP(char_index_qm))
	    goto end_loop;
	result = new_get_next_token_from_wide_text_if_available_1(tokenizer,
		text,FIX((SI_Long)0L),char_index_qm,Nil,Nil,Nil);
	MVS_4(result,token_value,temp_1,temp_1,character_index_after_token);
	char_index_qm = character_index_after_token;
	if (token_value)
	    return_value = token_cons_1(token_value,return_value);
	goto next_loop;
      end_loop:
	reclaim_token_cons_1(text);
	temp_1 = nreverse(return_value);
	goto end_1;
	temp_1 = Qnil;
      end_1:;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

void token_INIT()
{
    Object temp, reclaim_structure_for_lexing_table_1;
    Object reclaim_structure_for_internal_token_1;
    Object reclaim_structure_for_fsm_state_1;
    Object reclaim_structure_for_state_transition_1;
    Object reclaim_structure_for_parse_object_1, wide_string_bv16, tmp;
    Object aref_new_value_1, pattern, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, ab_loop_desetq_;
    Object reclaim_structure_for_text_tokenization_state_1;
    Object reclaim_structure_for_g2_token_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, arg, arg_1, arg_2;
    char temp_1;
    Object AB_package, array_constant_9, list_constant_5, Qg2_token;
    Object Qreclaim_structure, Qoutstanding_g2_token_count;
    Object Qg2_token_structure_memory_usage, Qutilities2, string_constant_16;
    Object Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_15, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qtext_tokenization_state;
    Object Qoutstanding_text_tokenization_state_count;
    Object Qtext_tokenization_state_structure_memory_usage, string_constant_14;
    Object string_constant_13, Qfalse, Qno_tokenizer_match_token_type;
    Object Qalphabet_transition_relationship;
    Object Qpattern_transform_inverted_class, Qinverted_class;
    Object Qpattern_transform_character_class, Qcharacter_class;
    Object Qpattern_transform_dot, Qab_dot, Qpattern_transform_maybe, Qmaybe;
    Object Qpattern_transform_plus, Qab_plus, Qpattern_transform_pattern;
    Object Qpattern, Qpattern_transform_kleene, Qkleene;
    Object Qpattern_transform_either, Qeither, Qpattern_transform_seq, Qseq;
    Object Qpattern_transform_test, Qtest, Qpattern_transform_nil;
    Object Qpattern_transform_canonical, Qcanonical, array_constant_8;
    Object Qright_bracket, array_constant_7, Qleft_bracket, array_constant_6;
    Object Qdouble_quote, array_constant_5, Qwhitespace, array_constant_4;
    Object Qalphanumeric, array_constant_3, Qg2symbol, array_constant_2;
    Object Qhexadecimal, array_constant_1, Qnumeric, array_constant;
    Object Qalphabetic, Qcharacter_class_member_p, Qparse_object;
    Object Qoutstanding_parse_object_count;
    Object Qparse_object_structure_memory_usage, string_constant_12;
    Object string_constant_11, Qstate_transition;
    Object Qoutstanding_state_transition_count;
    Object Qstate_transition_structure_memory_usage, string_constant_10;
    Object string_constant_9, Qfsm_state, Qoutstanding_fsm_state_count;
    Object Qfsm_state_structure_memory_usage, string_constant_8;
    Object string_constant_7, Qinternal_token;
    Object Qoutstanding_internal_token_count;
    Object Qinternal_token_structure_memory_usage, string_constant_6;
    Object string_constant_5, Qlexing_table, Qoutstanding_lexing_table_count;
    Object Qlexing_table_structure_memory_usage, string_constant_4;
    Object string_constant_3, string_constant_2, Qtoken_cons_memory_usage;
    Object Qoutstanding_token_conses, list_constant_4;
    Object Qtoken_cons_counter_vector, Qmake_thread_array, Kfuncall;
    Object list_constant_3, Qavailable_token_conses_tail_vector;
    Object Qavailable_token_conses_vector;

    x_note_fn_call(31,139);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qavailable_token_conses = STATIC_SYMBOL("AVAILABLE-TOKEN-CONSES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_token_conses,Available_token_conses);
    Qtoken = STATIC_SYMBOL("TOKEN",AB_package);
    record_system_variable(Qavailable_token_conses,Qtoken,Nil,Qnil,Qt,Qnil,
	    Qnil);
    Qavailable_token_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-TOKEN-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_token_conses_tail,
	    Available_token_conses_tail);
    record_system_variable(Qavailable_token_conses_tail,Qtoken,Nil,Qnil,Qt,
	    Qnil,Qnil);
    Qavailable_token_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-TOKEN-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_token_conses_vector,
	    Available_token_conses_vector);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_thread_array = STATIC_SYMBOL("MAKE-THREAD-ARRAY",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    Qnil);
    record_system_variable(Qavailable_token_conses_vector,Qtoken,
	    list_constant_3,Qnil,Qt,Qnil,Qnil);
    Qavailable_token_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-TOKEN-CONSES-TAIL-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_token_conses_tail_vector,
	    Available_token_conses_tail_vector);
    record_system_variable(Qavailable_token_conses_tail_vector,Qtoken,
	    list_constant_3,Qnil,Qt,Qnil,Qnil);
    Qtoken_cons_counter_vector = STATIC_SYMBOL("TOKEN-CONS-COUNTER-VECTOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtoken_cons_counter_vector,
	    Token_cons_counter_vector);
    list_constant_4 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    FIX((SI_Long)0L));
    record_system_variable(Qtoken_cons_counter_vector,Qtoken,
	    list_constant_4,Qnil,Qt,Qnil,Qnil);
    Qtoken_cons_counter = STATIC_SYMBOL("TOKEN-CONS-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtoken_cons_counter,Token_cons_counter);
    record_system_variable(Qtoken_cons_counter,Qtoken,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    Qoutstanding_token_conses = STATIC_SYMBOL("OUTSTANDING-TOKEN-CONSES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_token_conses,
	    STATIC_FUNCTION(outstanding_token_conses,NIL,FALSE,0,0));
    Qtoken_cons_memory_usage = STATIC_SYMBOL("TOKEN-CONS-MEMORY-USAGE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qtoken_cons_memory_usage,
	    STATIC_FUNCTION(token_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_2 = STATIC_STRING("1q83-tUy9k83-tTy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_token_conses);
    push_optimized_constant(Qtoken_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_2));
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_lexing_table_g2_struct = 
	    STATIC_SYMBOL("LEXING-TABLE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qlexing_table = STATIC_SYMBOL("LEXING-TABLE",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_lexing_table_g2_struct,
	    Qlexing_table,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qlexing_table,
	    Qg2_defstruct_structure_name_lexing_table_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_lexing_table == UNBOUND)
	The_type_description_of_lexing_table = Nil;
    string_constant_3 = 
	    STATIC_STRING("43Dy8m837Ay1n837Ay8n8k1l8n0000000kok0k0");
    temp = The_type_description_of_lexing_table;
    The_type_description_of_lexing_table = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_3));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_lexing_table_g2_struct,
	    The_type_description_of_lexing_table,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qlexing_table,
	    The_type_description_of_lexing_table,Qtype_description_of_type);
    Qoutstanding_lexing_table_count = 
	    STATIC_SYMBOL("OUTSTANDING-LEXING-TABLE-COUNT",AB_package);
    Qlexing_table_structure_memory_usage = 
	    STATIC_SYMBOL("LEXING-TABLE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_4 = STATIC_STRING("1q837Ay8s83-cZy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_lexing_table_count);
    push_optimized_constant(Qlexing_table_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_4));
    Qchain_of_available_lexing_tables = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-LEXING-TABLES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_lexing_tables,
	    Chain_of_available_lexing_tables);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_lexing_tables,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qlexing_table_count = STATIC_SYMBOL("LEXING-TABLE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlexing_table_count,Lexing_table_count);
    record_system_variable(Qlexing_table_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_lexing_tables_vector == UNBOUND)
	Chain_of_available_lexing_tables_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qlexing_table_structure_memory_usage,
	    STATIC_FUNCTION(lexing_table_structure_memory_usage,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_lexing_table_count,
	    STATIC_FUNCTION(outstanding_lexing_table_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_lexing_table_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_lexing_table,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qlexing_table,
	    reclaim_structure_for_lexing_table_1);
    Qg2_defstruct_structure_name_internal_token_g2_struct = 
	    STATIC_SYMBOL("INTERNAL-TOKEN-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qinternal_token = STATIC_SYMBOL("INTERNAL-TOKEN",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_internal_token_g2_struct,
	    Qinternal_token,Qab_name_of_unique_structure_type);
    mutate_global_property(Qinternal_token,
	    Qg2_defstruct_structure_name_internal_token_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_internal_token == UNBOUND)
	The_type_description_of_internal_token = Nil;
    string_constant_5 = 
	    STATIC_STRING("43Dy8m83j5y1n83j5y8n8k1l8n0000000kok0k0");
    temp = The_type_description_of_internal_token;
    The_type_description_of_internal_token = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_5));
    mutate_global_property(Qg2_defstruct_structure_name_internal_token_g2_struct,
	    The_type_description_of_internal_token,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qinternal_token,
	    The_type_description_of_internal_token,Qtype_description_of_type);
    Qoutstanding_internal_token_count = 
	    STATIC_SYMBOL("OUTSTANDING-INTERNAL-TOKEN-COUNT",AB_package);
    Qinternal_token_structure_memory_usage = 
	    STATIC_SYMBOL("INTERNAL-TOKEN-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_6 = STATIC_STRING("1q83j5y8s83-aOy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_internal_token_count);
    push_optimized_constant(Qinternal_token_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_6));
    Qchain_of_available_internal_tokens = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-INTERNAL-TOKENS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_internal_tokens,
	    Chain_of_available_internal_tokens);
    record_system_variable(Qchain_of_available_internal_tokens,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qinternal_token_count = STATIC_SYMBOL("INTERNAL-TOKEN-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qinternal_token_count,Internal_token_count);
    record_system_variable(Qinternal_token_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_internal_tokens_vector == UNBOUND)
	Chain_of_available_internal_tokens_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qinternal_token_structure_memory_usage,
	    STATIC_FUNCTION(internal_token_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_internal_token_count,
	    STATIC_FUNCTION(outstanding_internal_token_count,NIL,FALSE,0,0));
    reclaim_structure_for_internal_token_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_internal_token,NIL,FALSE,
	    1,1);
    record_direct_structure_method(Qreclaim_structure,Qinternal_token,
	    reclaim_structure_for_internal_token_1);
    Qalphabet_normalized_symbol_from_text_string = 
	    STATIC_SYMBOL("ALPHABET-NORMALIZED-SYMBOL-FROM-TEXT-STRING",
	    AB_package);
    Qg2_defstruct_structure_name_fsm_state_g2_struct = 
	    STATIC_SYMBOL("FSM-STATE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qfsm_state = STATIC_SYMBOL("FSM-STATE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_fsm_state_g2_struct,
	    Qfsm_state,Qab_name_of_unique_structure_type);
    mutate_global_property(Qfsm_state,
	    Qg2_defstruct_structure_name_fsm_state_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_fsm_state == UNBOUND)
	The_type_description_of_fsm_state = Nil;
    string_constant_7 = 
	    STATIC_STRING("43Dy8m83hWy1n83hWy8n8k1l8n0000000kok0k0");
    temp = The_type_description_of_fsm_state;
    The_type_description_of_fsm_state = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_7));
    mutate_global_property(Qg2_defstruct_structure_name_fsm_state_g2_struct,
	    The_type_description_of_fsm_state,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qfsm_state,The_type_description_of_fsm_state,
	    Qtype_description_of_type);
    Qoutstanding_fsm_state_count = 
	    STATIC_SYMBOL("OUTSTANDING-FSM-STATE-COUNT",AB_package);
    Qfsm_state_structure_memory_usage = 
	    STATIC_SYMBOL("FSM-STATE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_8 = STATIC_STRING("1q83hWy8s83-V8y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_fsm_state_count);
    push_optimized_constant(Qfsm_state_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_8));
    Qchain_of_available_fsm_states = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-FSM-STATES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_fsm_states,
	    Chain_of_available_fsm_states);
    record_system_variable(Qchain_of_available_fsm_states,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qfsm_state_count = STATIC_SYMBOL("FSM-STATE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qfsm_state_count,Fsm_state_count);
    record_system_variable(Qfsm_state_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_fsm_states_vector == UNBOUND)
	Chain_of_available_fsm_states_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qfsm_state_structure_memory_usage,
	    STATIC_FUNCTION(fsm_state_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_fsm_state_count,
	    STATIC_FUNCTION(outstanding_fsm_state_count,NIL,FALSE,0,0));
    reclaim_structure_for_fsm_state_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_fsm_state,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qfsm_state,
	    reclaim_structure_for_fsm_state_1);
    Qg2_defstruct_structure_name_state_transition_g2_struct = 
	    STATIC_SYMBOL("STATE-TRANSITION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qstate_transition = STATIC_SYMBOL("STATE-TRANSITION",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_state_transition_g2_struct,
	    Qstate_transition,Qab_name_of_unique_structure_type);
    mutate_global_property(Qstate_transition,
	    Qg2_defstruct_structure_name_state_transition_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_state_transition == UNBOUND)
	The_type_description_of_state_transition = Nil;
    string_constant_9 = 
	    STATIC_STRING("43Dy8m83nPy1n83nPy8n8k1l8n0000000kqk0k0");
    temp = The_type_description_of_state_transition;
    The_type_description_of_state_transition = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_9));
    mutate_global_property(Qg2_defstruct_structure_name_state_transition_g2_struct,
	    The_type_description_of_state_transition,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qstate_transition,
	    The_type_description_of_state_transition,
	    Qtype_description_of_type);
    Qoutstanding_state_transition_count = 
	    STATIC_SYMBOL("OUTSTANDING-STATE-TRANSITION-COUNT",AB_package);
    Qstate_transition_structure_memory_usage = 
	    STATIC_SYMBOL("STATE-TRANSITION-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_10 = STATIC_STRING("1q83nPy8s83-qny09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_state_transition_count);
    push_optimized_constant(Qstate_transition_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_10));
    Qchain_of_available_state_transitions = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-STATE-TRANSITIONS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_state_transitions,
	    Chain_of_available_state_transitions);
    record_system_variable(Qchain_of_available_state_transitions,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qstate_transition_count = STATIC_SYMBOL("STATE-TRANSITION-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qstate_transition_count,State_transition_count);
    record_system_variable(Qstate_transition_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_state_transitions_vector == UNBOUND)
	Chain_of_available_state_transitions_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qstate_transition_structure_memory_usage,
	    STATIC_FUNCTION(state_transition_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_state_transition_count,
	    STATIC_FUNCTION(outstanding_state_transition_count,NIL,FALSE,0,0));
    reclaim_structure_for_state_transition_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_state_transition,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qstate_transition,
	    reclaim_structure_for_state_transition_1);
    Qg2_defstruct_structure_name_parse_object_g2_struct = 
	    STATIC_SYMBOL("PARSE-OBJECT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qparse_object = STATIC_SYMBOL("PARSE-OBJECT",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_parse_object_g2_struct,
	    Qparse_object,Qab_name_of_unique_structure_type);
    mutate_global_property(Qparse_object,
	    Qg2_defstruct_structure_name_parse_object_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_parse_object == UNBOUND)
	The_type_description_of_parse_object = Nil;
    string_constant_11 = 
	    STATIC_STRING("43Dy8m83lNy1n83lNy8n8k1l8n0000000kpk0k0");
    temp = The_type_description_of_parse_object;
    The_type_description_of_parse_object = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_11));
    mutate_global_property(Qg2_defstruct_structure_name_parse_object_g2_struct,
	    The_type_description_of_parse_object,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qparse_object,
	    The_type_description_of_parse_object,Qtype_description_of_type);
    Qoutstanding_parse_object_count = 
	    STATIC_SYMBOL("OUTSTANDING-PARSE-OBJECT-COUNT",AB_package);
    Qparse_object_structure_memory_usage = 
	    STATIC_SYMBOL("PARSE-OBJECT-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_12 = STATIC_STRING("1q83lNy8s83-iLy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_parse_object_count);
    push_optimized_constant(Qparse_object_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_12));
    Qchain_of_available_parse_objects = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-PARSE-OBJECTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_parse_objects,
	    Chain_of_available_parse_objects);
    record_system_variable(Qchain_of_available_parse_objects,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qparse_object_count = STATIC_SYMBOL("PARSE-OBJECT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qparse_object_count,Parse_object_count);
    record_system_variable(Qparse_object_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_parse_objects_vector == UNBOUND)
	Chain_of_available_parse_objects_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qparse_object_structure_memory_usage,
	    STATIC_FUNCTION(parse_object_structure_memory_usage,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_parse_object_count,
	    STATIC_FUNCTION(outstanding_parse_object_count,NIL,FALSE,0,0));
    reclaim_structure_for_parse_object_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_parse_object,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qparse_object,
	    reclaim_structure_for_parse_object_1);
    if (Current_lexing_rule_number == UNBOUND)
	Current_lexing_rule_number = FIX((SI_Long)0L);
    if (Current_character == UNBOUND)
	Current_character = Nil;
    wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2L + (SI_Long)3L));
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
    aref_arg_2 = bv16_length - (SI_Long)2L;
    aref_new_value = (SI_Long)2L & (SI_Long)65535L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    aref_arg_2 = bv16_length - (SI_Long)1L;
    aref_new_value = (SI_Long)57344L | (SI_Long)0L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2L,(SI_Long)0L);
    tmp = wide_string_bv16;
    aref_new_value_1 = Alphabet_character_class_open;
    UBYTE_16_ISASET_1(tmp,(SI_Long)0L,IFIX(aref_new_value_1));
    aref_new_value_1 = Alphabet_character_class_close;
    UBYTE_16_ISASET_1(tmp,(SI_Long)1L,IFIX(aref_new_value_1));
    Null_pattern = tmp;
    Qcharacter_class_member_p = STATIC_SYMBOL("CHARACTER-CLASS-MEMBER-P",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcharacter_class_member_p,
	    STATIC_FUNCTION(character_class_member_p,NIL,FALSE,2,2));
    Qrange_lt = STATIC_SYMBOL("RANGE<",AB_package);
    SET_SYMBOL_FUNCTION(Qrange_lt,STATIC_FUNCTION(range_lt,NIL,FALSE,2,2));
    string_constant = STATIC_STRING("Pairs must be *DOTTED* lists.");
    pattern = Nil;
    ab_loop_list_ = Regular_expression_tokens;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    temp = CDR(ab_loop_desetq_);
    pattern = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (FIXNUMP(pattern)) {
	arg = IFIX(Alphabet_min_code);
	arg_1 = IFIX(pattern);
	arg_2 = IFIX(Alphabet_max_code);
	temp_1 = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	ab_loopvar__2 = LIST_1(pattern);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    Regular_expression_metacharacters = ab_loopvar_;
    goto end_1;
    Regular_expression_metacharacters = Qnil;
  end_1:;
    if (Built_in_character_codes == UNBOUND)
	Built_in_character_codes = Qnil;
    Qalphabetic = STATIC_SYMBOL("ALPHABETIC",AB_package);
    list_constant_5 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_5,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)123L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)90L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)125L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)57344L);
    Built_in_character_codes = token_cons_1(token_cons_1(Qalphabetic,
	    array_constant),Built_in_character_codes);
    Qnumeric = STATIC_SYMBOL("NUMERIC",AB_package);
    array_constant_1 = STATIC_ARRAY(list_constant_5,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)123L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)57L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)125L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    Built_in_character_codes = token_cons_1(token_cons_1(Qnumeric,
	    array_constant_1),Built_in_character_codes);
    Qhexadecimal = STATIC_SYMBOL("HEXADECIMAL",AB_package);
    array_constant_2 = STATIC_ARRAY(list_constant_5,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)123L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)57L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)10L,(SI_Long)125L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)57344L);
    Built_in_character_codes = token_cons_1(token_cons_1(Qhexadecimal,
	    array_constant_2),Built_in_character_codes);
    Qg2symbol = STATIC_SYMBOL("G2SYMBOL",AB_package);
    array_constant_3 = STATIC_ARRAY(list_constant_5,(SI_Long)1L,
	    FIX((SI_Long)80L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)123L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)31L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)39L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)39L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)10L,(SI_Long)92L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)11L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)12L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)13L,(SI_Long)92L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)16L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)17L,(SI_Long)57L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)18L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)19L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)20L,(SI_Long)90L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)21L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)22L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)23L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)24L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)25L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)26L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)27L,(SI_Long)127L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)28L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)29L,(SI_Long)160L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)30L,(SI_Long)164L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)31L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)32L,(SI_Long)164L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)33L,(SI_Long)166L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)34L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)35L,(SI_Long)168L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)36L,(SI_Long)170L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)37L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)38L,(SI_Long)170L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)39L,(SI_Long)172L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)40L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)41L,(SI_Long)173L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)42L,(SI_Long)175L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)43L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)44L,(SI_Long)186L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)45L,(SI_Long)188L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)46L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)47L,(SI_Long)190L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)48L,(SI_Long)192L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)49L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)50L,(SI_Long)401L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)51L,(SI_Long)403L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)52L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)53L,(SI_Long)8225L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)54L,(SI_Long)8227L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)55L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)56L,(SI_Long)8231L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)57L,(SI_Long)8234L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)58L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)59L,(SI_Long)8481L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)60L,(SI_Long)8483L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)61L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)62L,(SI_Long)65535L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)63L,(SI_Long)125L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)78L,(SI_Long)64L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)79L,(SI_Long)57344L);
    Built_in_character_codes = token_cons_1(token_cons_1(Qg2symbol,
	    array_constant_3),Built_in_character_codes);
    Qalphanumeric = STATIC_SYMBOL("ALPHANUMERIC",AB_package);
    array_constant_4 = STATIC_ARRAY(list_constant_5,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)123L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)57L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)90L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)125L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)57344L);
    Built_in_character_codes = token_cons_1(token_cons_1(Qalphanumeric,
	    array_constant_4),Built_in_character_codes);
    Qwhitespace = STATIC_SYMBOL("WHITESPACE",AB_package);
    array_constant_5 = STATIC_ARRAY(list_constant_5,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)123L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)8232L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)13L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)8233L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)125L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)57344L);
    Built_in_character_codes = token_cons_1(token_cons_1(Qwhitespace,
	    array_constant_5),Built_in_character_codes);
    Qdouble_quote = STATIC_SYMBOL("DOUBLE-QUOTE",AB_package);
    array_constant_6 = STATIC_ARRAY(list_constant_5,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)123L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)125L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)57344L);
    Built_in_character_codes = token_cons_1(token_cons_1(Qdouble_quote,
	    array_constant_6),Built_in_character_codes);
    Qleft_bracket = STATIC_SYMBOL("LEFT-BRACKET",AB_package);
    array_constant_7 = STATIC_ARRAY(list_constant_5,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)123L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)91L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)125L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)57344L);
    Built_in_character_codes = token_cons_1(token_cons_1(Qleft_bracket,
	    array_constant_7),Built_in_character_codes);
    Qright_bracket = STATIC_SYMBOL("RIGHT-BRACKET",AB_package);
    array_constant_8 = STATIC_ARRAY(list_constant_5,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)123L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)93L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)125L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)57344L);
    Built_in_character_codes = token_cons_1(token_cons_1(Qright_bracket,
	    array_constant_8),Built_in_character_codes);
    if (Current_tokenizer == UNBOUND)
	Current_tokenizer = Nil;
    if (Current_start_state == UNBOUND)
	Current_start_state = Nil;
    if (Current_lexing_strings == UNBOUND)
	Current_lexing_strings = Qnil;
    if (Current_lexing_patterns == UNBOUND)
	Current_lexing_patterns = Qnil;
    if (Current_anchor_p == UNBOUND)
	Current_anchor_p = Nil;
    if (Known_regexp_functions == UNBOUND)
	Known_regexp_functions = Qnil;
    Qregexp_evaluator = STATIC_SYMBOL("REGEXP-EVALUATOR",AB_package);
    Regexp_evaluator_prop = Qregexp_evaluator;
    Qcanonical = STATIC_SYMBOL("CANONICAL",AB_package);
    Known_regexp_functions = token_cons_1(Qcanonical,Known_regexp_functions);
    Qpattern_transform_canonical = 
	    STATIC_SYMBOL("PATTERN-TRANSFORM-CANONICAL",AB_package);
    SET_SYMBOL_FUNCTION(Qpattern_transform_canonical,
	    STATIC_FUNCTION(pattern_transform_canonical,NIL,FALSE,3,3));
    mutate_global_property(Qcanonical,
	    SYMBOL_FUNCTION(Qpattern_transform_canonical),Qregexp_evaluator);
    Known_regexp_functions = token_cons_1(Qnil,Known_regexp_functions);
    Qpattern_transform_nil = STATIC_SYMBOL("PATTERN-TRANSFORM-NIL",AB_package);
    SET_SYMBOL_FUNCTION(Qpattern_transform_nil,
	    STATIC_FUNCTION(pattern_transform_nil,NIL,FALSE,3,3));
    mutate_global_property(Qnil,SYMBOL_FUNCTION(Qpattern_transform_nil),
	    Qregexp_evaluator);
    Qtest = STATIC_SYMBOL("TEST",AB_package);
    Known_regexp_functions = token_cons_1(Qtest,Known_regexp_functions);
    Qpattern_transform_test = STATIC_SYMBOL("PATTERN-TRANSFORM-TEST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpattern_transform_test,
	    STATIC_FUNCTION(pattern_transform_test,NIL,FALSE,3,3));
    mutate_global_property(Qtest,SYMBOL_FUNCTION(Qpattern_transform_test),
	    Qregexp_evaluator);
    Qseq = STATIC_SYMBOL("SEQ",AB_package);
    Known_regexp_functions = token_cons_1(Qseq,Known_regexp_functions);
    Qpattern_transform_seq = STATIC_SYMBOL("PATTERN-TRANSFORM-SEQ",AB_package);
    SET_SYMBOL_FUNCTION(Qpattern_transform_seq,
	    STATIC_FUNCTION(pattern_transform_seq,NIL,FALSE,3,3));
    mutate_global_property(Qseq,SYMBOL_FUNCTION(Qpattern_transform_seq),
	    Qregexp_evaluator);
    Qeither = STATIC_SYMBOL("EITHER",AB_package);
    Known_regexp_functions = token_cons_1(Qeither,Known_regexp_functions);
    Qpattern_transform_either = STATIC_SYMBOL("PATTERN-TRANSFORM-EITHER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpattern_transform_either,
	    STATIC_FUNCTION(pattern_transform_either,NIL,FALSE,3,3));
    mutate_global_property(Qeither,
	    SYMBOL_FUNCTION(Qpattern_transform_either),Qregexp_evaluator);
    Qkleene = STATIC_SYMBOL("KLEENE",AB_package);
    Known_regexp_functions = token_cons_1(Qkleene,Known_regexp_functions);
    Qpattern_transform_kleene = STATIC_SYMBOL("PATTERN-TRANSFORM-KLEENE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpattern_transform_kleene,
	    STATIC_FUNCTION(pattern_transform_kleene,NIL,FALSE,3,3));
    mutate_global_property(Qkleene,
	    SYMBOL_FUNCTION(Qpattern_transform_kleene),Qregexp_evaluator);
    Qpattern = STATIC_SYMBOL("PATTERN",AB_package);
    Known_regexp_functions = token_cons_1(Qpattern,Known_regexp_functions);
    Qpattern_transform_pattern = STATIC_SYMBOL("PATTERN-TRANSFORM-PATTERN",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpattern_transform_pattern,
	    STATIC_FUNCTION(pattern_transform_pattern,NIL,FALSE,3,3));
    mutate_global_property(Qpattern,
	    SYMBOL_FUNCTION(Qpattern_transform_pattern),Qregexp_evaluator);
    Qab_plus = STATIC_SYMBOL("PLUS",AB_package);
    Known_regexp_functions = token_cons_1(Qab_plus,Known_regexp_functions);
    Qpattern_transform_plus = STATIC_SYMBOL("PATTERN-TRANSFORM-PLUS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpattern_transform_plus,
	    STATIC_FUNCTION(pattern_transform_plus,NIL,FALSE,3,3));
    mutate_global_property(Qab_plus,
	    SYMBOL_FUNCTION(Qpattern_transform_plus),Qregexp_evaluator);
    Qmaybe = STATIC_SYMBOL("MAYBE",AB_package);
    Known_regexp_functions = token_cons_1(Qmaybe,Known_regexp_functions);
    Qpattern_transform_maybe = STATIC_SYMBOL("PATTERN-TRANSFORM-MAYBE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpattern_transform_maybe,
	    STATIC_FUNCTION(pattern_transform_maybe,NIL,FALSE,3,3));
    mutate_global_property(Qmaybe,
	    SYMBOL_FUNCTION(Qpattern_transform_maybe),Qregexp_evaluator);
    Qab_dot = STATIC_SYMBOL("DOT",AB_package);
    Known_regexp_functions = token_cons_1(Qab_dot,Known_regexp_functions);
    Qpattern_transform_dot = STATIC_SYMBOL("PATTERN-TRANSFORM-DOT",AB_package);
    SET_SYMBOL_FUNCTION(Qpattern_transform_dot,
	    STATIC_FUNCTION(pattern_transform_dot,NIL,FALSE,3,3));
    mutate_global_property(Qab_dot,SYMBOL_FUNCTION(Qpattern_transform_dot),
	    Qregexp_evaluator);
    Qcharacter_class = STATIC_SYMBOL("CHARACTER-CLASS",AB_package);
    Known_regexp_functions = token_cons_1(Qcharacter_class,
	    Known_regexp_functions);
    Qpattern_transform_character_class = 
	    STATIC_SYMBOL("PATTERN-TRANSFORM-CHARACTER-CLASS",AB_package);
    SET_SYMBOL_FUNCTION(Qpattern_transform_character_class,
	    STATIC_FUNCTION(pattern_transform_character_class,NIL,FALSE,3,3));
    mutate_global_property(Qcharacter_class,
	    SYMBOL_FUNCTION(Qpattern_transform_character_class),
	    Qregexp_evaluator);
    Qinverted_class = STATIC_SYMBOL("INVERTED-CLASS",AB_package);
    Known_regexp_functions = token_cons_1(Qinverted_class,
	    Known_regexp_functions);
    Qpattern_transform_inverted_class = 
	    STATIC_SYMBOL("PATTERN-TRANSFORM-INVERTED-CLASS",AB_package);
    SET_SYMBOL_FUNCTION(Qpattern_transform_inverted_class,
	    STATIC_FUNCTION(pattern_transform_inverted_class,NIL,FALSE,3,3));
    mutate_global_property(Qinverted_class,
	    SYMBOL_FUNCTION(Qpattern_transform_inverted_class),
	    Qregexp_evaluator);
    Qanchor = STATIC_SYMBOL("ANCHOR",AB_package);
    Qequiv = STATIC_SYMBOL("EQUIV",AB_package);
    Qsub2 = STATIC_SYMBOL("SUB2",AB_package);
    Qab_sub1 = STATIC_SYMBOL("SUB1",AB_package);
    Qdisjoint = STATIC_SYMBOL("DISJOINT",AB_package);
    Qoverlap = STATIC_SYMBOL("OVERLAP",AB_package);
    Qalphabet_transition_relationship = 
	    STATIC_SYMBOL("ALPHABET-TRANSITION-RELATIONSHIP",AB_package);
    SET_SYMBOL_FUNCTION(Qalphabet_transition_relationship,
	    STATIC_FUNCTION(alphabet_transition_relationship,NIL,FALSE,4,4));
    Qtransition_higher_priority = 
	    STATIC_SYMBOL("TRANSITION-HIGHER-PRIORITY",AB_package);
    SET_SYMBOL_FUNCTION(Qtransition_higher_priority,
	    STATIC_FUNCTION(transition_higher_priority,NIL,FALSE,2,2));
    Qtransition_eq = STATIC_SYMBOL("TRANSITION=",AB_package);
    SET_SYMBOL_FUNCTION(Qtransition_eq,STATIC_FUNCTION(transition_eq,NIL,
	    FALSE,2,2));
    Qallocate_managed_simple_vector = 
	    STATIC_SYMBOL("ALLOCATE-MANAGED-SIMPLE-VECTOR",AB_package);
    SET_SYMBOL_FUNCTION(Qallocate_managed_simple_vector,
	    STATIC_FUNCTION(allocate_managed_simple_vector,NIL,FALSE,1,1));
    Qsimple_compiled_make_uninitialized_permanent_array = 
	    STATIC_SYMBOL("SIMPLE-COMPILED-MAKE-UNINITIALIZED-PERMANENT-ARRAY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qsimple_compiled_make_uninitialized_permanent_array,
	    STATIC_FUNCTION(simple_compiled_make_uninitialized_permanent_array,
	    NIL,FALSE,1,1));
    Qno_tokenizer_match_token_type = 
	    STATIC_SYMBOL("NO-TOKENIZER-MATCH-TOKEN-TYPE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qno_tokenizer_match_token_type,
	    No_tokenizer_match_token_type);
    Qfalse = STATIC_SYMBOL("FALSE",AB_package);
    SET_SYMBOL_VALUE(Qno_tokenizer_match_token_type,Qfalse);
    Qdo_nothing = STATIC_SYMBOL("DO-NOTHING",AB_package);
    G2_standard_tokenizer = compile_permanent_lexing_table(G2_standard_tokens);
    G2_simple_tokenizer = compile_permanent_lexing_table(G2_simple_tokens);
    G2_load_kb_tokenizer = compile_permanent_lexing_table(Load_kb_tokens);
    G2_tokenizer_tokenizer = compile_permanent_lexing_table(Tokenizer_tokens);
    G2_symbol_tokenizer = compile_permanent_lexing_table(G2_symbol_tokens);
    G2_comment_tokenizer = 
	    compile_permanent_lexing_table(G2_comment_recognizing_tokens);
    Regular_expression_tokenizer = 
	    compile_permanent_lexing_table(Regular_expression_tokens);
    Current_tokenizer = Regular_expression_tokenizer;
    Current_start_state = ISVREF(Regular_expression_tokenizer,(SI_Long)1L);
    Qg2_defstruct_structure_name_text_tokenization_state_g2_struct = 
	    STATIC_SYMBOL("TEXT-TOKENIZATION-STATE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qtext_tokenization_state = STATIC_SYMBOL("TEXT-TOKENIZATION-STATE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_text_tokenization_state_g2_struct,
	    Qtext_tokenization_state,Qab_name_of_unique_structure_type);
    mutate_global_property(Qtext_tokenization_state,
	    Qg2_defstruct_structure_name_text_tokenization_state_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_text_tokenization_state == UNBOUND)
	The_type_description_of_text_tokenization_state = Nil;
    string_constant_13 = 
	    STATIC_STRING("43Dy8m83nny1n83nny8n8k1l8n0000000k3Dyk0k0");
    temp = The_type_description_of_text_tokenization_state;
    The_type_description_of_text_tokenization_state = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_13));
    mutate_global_property(Qg2_defstruct_structure_name_text_tokenization_state_g2_struct,
	    The_type_description_of_text_tokenization_state,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qtext_tokenization_state,
	    The_type_description_of_text_tokenization_state,
	    Qtype_description_of_type);
    Qoutstanding_text_tokenization_state_count = 
	    STATIC_SYMBOL("OUTSTANDING-TEXT-TOKENIZATION-STATE-COUNT",
	    AB_package);
    Qtext_tokenization_state_structure_memory_usage = 
	    STATIC_SYMBOL("TEXT-TOKENIZATION-STATE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_14 = STATIC_STRING("1q83nny8s83-sby09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_text_tokenization_state_count);
    push_optimized_constant(Qtext_tokenization_state_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_14));
    Qchain_of_available_text_tokenization_states = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-TEXT-TOKENIZATION-STATES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_text_tokenization_states,
	    Chain_of_available_text_tokenization_states);
    record_system_variable(Qchain_of_available_text_tokenization_states,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qtext_tokenization_state_count = 
	    STATIC_SYMBOL("TEXT-TOKENIZATION-STATE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtext_tokenization_state_count,
	    Text_tokenization_state_count);
    record_system_variable(Qtext_tokenization_state_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_text_tokenization_states_vector == UNBOUND)
	Chain_of_available_text_tokenization_states_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qtext_tokenization_state_structure_memory_usage,
	    STATIC_FUNCTION(text_tokenization_state_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_text_tokenization_state_count,
	    STATIC_FUNCTION(outstanding_text_tokenization_state_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_text_tokenization_state_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_text_tokenization_state,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qtext_tokenization_state,
	    reclaim_structure_for_text_tokenization_state_1);
    Qg2_defstruct_structure_name_g2_token_g2_struct = 
	    STATIC_SYMBOL("G2-TOKEN-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_token = STATIC_SYMBOL("G2-TOKEN",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_g2_token_g2_struct,
	    Qg2_token,Qab_name_of_unique_structure_type);
    mutate_global_property(Qg2_token,
	    Qg2_defstruct_structure_name_g2_token_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_g2_token == UNBOUND)
	The_type_description_of_g2_token = Nil;
    string_constant_15 = 
	    STATIC_STRING("43Dy8m83hey1n83hey8n8k1l8n0000000krk0k0");
    temp = The_type_description_of_g2_token;
    The_type_description_of_g2_token = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_15));
    mutate_global_property(Qg2_defstruct_structure_name_g2_token_g2_struct,
	    The_type_description_of_g2_token,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qg2_token,The_type_description_of_g2_token,
	    Qtype_description_of_type);
    Qoutstanding_g2_token_count = 
	    STATIC_SYMBOL("OUTSTANDING-G2-TOKEN-COUNT",AB_package);
    Qg2_token_structure_memory_usage = 
	    STATIC_SYMBOL("G2-TOKEN-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_16 = STATIC_STRING("1q83hey8s83-VZy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_g2_token_count);
    push_optimized_constant(Qg2_token_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_16));
    Qchain_of_available_g2_tokens = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-G2-TOKENS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_g2_tokens,
	    Chain_of_available_g2_tokens);
    record_system_variable(Qchain_of_available_g2_tokens,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qg2_token_count = STATIC_SYMBOL("G2-TOKEN-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2_token_count,G2_token_count);
    record_system_variable(Qg2_token_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_g2_tokens_vector == UNBOUND)
	Chain_of_available_g2_tokens_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qg2_token_structure_memory_usage,
	    STATIC_FUNCTION(g2_token_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_g2_token_count,
	    STATIC_FUNCTION(outstanding_g2_token_count,NIL,FALSE,0,0));
    reclaim_structure_for_g2_token_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_g2_token,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qg2_token,
	    reclaim_structure_for_g2_token_1);
    if (Current_text_tokenization_state == UNBOUND)
	Current_text_tokenization_state = make_text_tokenization_state_1();
    if (Tokenize_with_editing_context_p == UNBOUND)
	Tokenize_with_editing_context_p = Nil;
    array_constant_9 = STATIC_ARRAY(list_constant_5,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)9L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)11L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)12L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)13L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)14L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)16L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)19L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)21L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)22L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)23L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)25L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)26L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)27L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)28L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)29L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)30L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)31L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)32L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)33L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)34L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)35L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)38L,(SI_Long)36L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)39L,(SI_Long)57344L);
    Tokenizer_illegal_character_error_message = array_constant_9;
    Qcomment = STATIC_SYMBOL("COMMENT",AB_package);
    Qsingle_line_comment = STATIC_SYMBOL("SINGLE-LINE-COMMENT",AB_package);
    Qleft_string = STATIC_SYMBOL("LEFT-STRING",AB_package);
    Qmiddle_string = STATIC_SYMBOL("MIDDLE-STRING",AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    Qjava_symbol = STATIC_SYMBOL("JAVA-SYMBOL",AB_package);
    Qquoted_character = STATIC_SYMBOL("QUOTED-CHARACTER",AB_package);
    Qwhole_string = STATIC_SYMBOL("WHOLE-STRING",AB_package);
    Qright_string = STATIC_SYMBOL("RIGHT-STRING",AB_package);
    Qself_terminating_punctuation_mark = 
	    STATIC_SYMBOL("SELF-TERMINATING-PUNCTUATION-MARK",AB_package);
    Qjava_character_literal = STATIC_SYMBOL("JAVA-CHARACTER-LITERAL",
	    AB_package);
    Qpunctuation_mark = STATIC_SYMBOL("PUNCTUATION-MARK",AB_package);
    list_constant = STATIC_CONS(Qcomment,Qnil);
    list_constant_1 = STATIC_CONS(Qsingle_line_comment,Qnil);
    Qdisambiguated_token = STATIC_SYMBOL("DISAMBIGUATED-TOKEN",AB_package);
    list_constant_2 = STATIC_CONS(Qdisambiguated_token,Qnil);
    Qellipsis = STATIC_SYMBOL("ELLIPSIS",AB_package);
    Qcbt = STATIC_SYMBOL("]",AB_package);
    string_constant_1 = 
	    STATIC_STRING("Warning: a token (starting with: ~a...) must be ~\n       truncated because it is too long, more than ~d characters.");
}
