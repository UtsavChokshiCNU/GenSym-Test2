/* int1.c
 * Input file:  int1.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "int1.h"


DEFINE_VARIABLE_WITH_SYMBOL(Available_icp_conses, Qavailable_icp_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_icp_conses_tail, Qavailable_icp_conses_tail);

Object Available_icp_conses_vector = UNBOUND;

Object Available_icp_conses_tail_vector = UNBOUND;

Object Icp_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Icp_cons_counter, Qicp_cons_counter);

/* OUTSTANDING-ICP-CONSES */
Object outstanding_icp_conses()
{
    Object temp;

    x_note_fn_call(47,0);
    temp = FIXNUM_MINUS(Icp_cons_counter,length(Available_icp_conses));
    return VALUES_1(temp);
}

/* ICP-CONS-MEMORY-USAGE */
Object icp_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(47,1);
    temp = FIXNUM_TIMES(Icp_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-ICP-CONS-POOL */
Object replenish_icp_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(47,2);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qicp_cons_counter,Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_icp_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_icp_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_icp_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_icp_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_icp_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Icp_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qicp;                /* icp */

/* ICP-CONS-1 */
Object icp_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(47,3);
    new_cons = ISVREF(Available_icp_conses_vector,IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_icp_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_icp_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_icp_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_icp_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qicp);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-ICP-LIST-POOL */
Object replenish_icp_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(47,4);
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
    if (ISVREF(Available_icp_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_icp_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_icp_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_icp_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_icp_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qicp_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-ICP-LIST-1 */
Object make_icp_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(47,5);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_icp_conses_vector,
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
	replenish_icp_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_icp_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qicp);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_icp_conses_vector,IFIX(Current_thread_index));
	svref_arg_1 = Available_icp_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_icp_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_icp_conses_tail_vector;
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

/* ICP-LIST-2 */
Object icp_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(47,6);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_icp_conses_vector,IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_icp_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_icp_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qicp);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_icp_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_icp_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_icp_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_icp_conses_tail_vector;
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

/* ICP-LIST-3 */
Object icp_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(47,7);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_icp_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_icp_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_icp_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qicp);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_icp_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_icp_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_icp_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_icp_conses_tail_vector;
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

/* ICP-LIST-4 */
Object icp_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(47,8);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_icp_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_icp_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_icp_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qicp);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_icp_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_icp_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_icp_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_icp_conses_tail_vector;
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

/* ICP-LIST-TRACE-HOOK */
Object icp_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(47,9);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-ICP-CONSES-1 */
Object copy_tree_using_icp_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(47,10);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_icp_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_icp_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_icp_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_icp_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_icp_cons_pool();
	temp_1 = copy_tree_using_icp_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qicp);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_icp_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_icp_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_icp_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_icp_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_icp_cons_pool();
	temp_1 = copy_tree_using_icp_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qicp);
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

/* COPY-LIST-USING-ICP-CONSES-1 */
Object copy_list_using_icp_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(47,11);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_icp_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_icp_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_icp_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_icp_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_icp_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qicp);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_icp_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_icp_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_icp_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_icp_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_icp_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qicp);
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

/* RECLAIM-ICP-CONS-1 */
Object reclaim_icp_cons_1(icp_cons)
    Object icp_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(47,12);
    inline_note_reclaim_cons(icp_cons,Qicp);
    if (ISVREF(Available_icp_conses_tail_vector,IFIX(Current_thread_index))) {
	temp = ISVREF(Available_icp_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = icp_cons;
	temp = Available_icp_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = icp_cons;
    }
    else {
	temp = Available_icp_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = icp_cons;
	temp = Available_icp_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = icp_cons;
    }
    M_CDR(icp_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-ICP-LIST-1 */
Object reclaim_icp_list_1(icp_list)
    Object icp_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(47,13);
    if (icp_list) {
	last_1 = icp_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qicp);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qicp);
	if (ISVREF(Available_icp_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_icp_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = icp_list;
	    temp = Available_icp_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_icp_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = icp_list;
	    temp = Available_icp_conses_tail_vector;
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

/* RECLAIM-ICP-LIST*-1 */
Object reclaim_icp_list_star_1(icp_list)
    Object icp_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(47,14);
    if (CONSP(icp_list)) {
	temp = last(icp_list,_);
	M_CDR(temp) = Nil;
	if (icp_list) {
	    last_1 = icp_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qicp);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qicp);
	    if (ISVREF(Available_icp_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_icp_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = icp_list;
		temp = Available_icp_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_icp_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = icp_list;
		temp = Available_icp_conses_tail_vector;
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

/* RECLAIM-ICP-TREE-1 */
Object reclaim_icp_tree_1(tree)
    Object tree;
{
    Object e, e2, icp_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(47,15);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_icp_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		icp_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(icp_cons,Qicp);
		if (EQ(icp_cons,e))
		    goto end_1;
		else if ( !TRUEP(icp_cons))
		    goto end_1;
		else
		    icp_cons = CDR(icp_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_icp_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_icp_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_icp_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_icp_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_icp_conses_tail_vector;
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

/* DELETE-ICP-ELEMENT-1 */
Object delete_icp_element_1(element,icp_list)
    Object element, icp_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(47,16);
    if (icp_list) {
	if (EQ(element,M_CAR(icp_list))) {
	    temp = CDR(icp_list);
	    inline_note_reclaim_cons(icp_list,Qicp);
	    if (ISVREF(Available_icp_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_icp_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = icp_list;
		temp_1 = Available_icp_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = icp_list;
	    }
	    else {
		temp_1 = Available_icp_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = icp_list;
		temp_1 = Available_icp_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = icp_list;
	    }
	    M_CDR(icp_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = icp_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qicp);
		if (ISVREF(Available_icp_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_icp_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_icp_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_icp_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_icp_conses_tail_vector;
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
	    temp = icp_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-ICP-CONS-1 */
Object delete_icp_cons_1(icp_cons,icp_list)
    Object icp_cons, icp_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(47,17);
    if (EQ(icp_cons,icp_list))
	temp = CDR(icp_list);
    else {
	l_trailer_qm = Nil;
	l = icp_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,icp_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = icp_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_icp_cons_1(icp_cons);
    return VALUES_1(temp);
}

/* COPY-LIST-USING-ICP-CONSES-FUNCTION */
Object copy_list_using_icp_conses_function(list_qm)
    Object list_qm;
{
    x_note_fn_call(47,18);
    if (list_qm)
	return copy_list_using_icp_conses_1(list_qm);
    else
	return VALUES_1(Nil);
}

/* RECLAIM-ICP-LIST-FUNCTION */
Object reclaim_icp_list_function(list_qm)
    Object list_qm;
{
    x_note_fn_call(47,19);
    if (list_qm)
	return reclaim_icp_list_1(list_qm);
    else
	return VALUES_1(Nil);
}

/* RECLAIM-ICP-TREE-WITH-TEXT-STRINGS */
Object reclaim_icp_tree_with_text_strings(tree)
    Object tree;
{
    Object tail, car_1, next_tail;

    x_note_fn_call(47,20);
    tail = tree;
    car_1 = Nil;
    next_tail = Nil;
  next_loop:
    if (ATOM(tail))
	goto end_loop;
    car_1 = CAR(tail);
    next_tail = CDR(tail);
    reclaim_icp_tree_with_text_strings(car_1);
    reclaim_icp_cons_1(tail);
    tail = next_tail;
    goto next_loop;
  end_loop:
    if (text_string_p(tail))
	reclaim_text_string(tail);
    return VALUES_1(Nil);
}

Object Blank_traced_icp_byte_column = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Trace_skip_data_service_i_am_alive_messages_p, Qtrace_skip_data_service_i_am_alive_messages_p);

DEFINE_VARIABLE_WITH_SYMBOL(Icp_trace_print_message_series_p, Qicp_trace_print_message_series_p);

Object Function_for_icp_value_reader_qm_prop = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Icp_read_trace_cutoff_level_qm, Qicp_read_trace_cutoff_level_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Current_icp_read_trace_level, Qcurrent_icp_read_trace_level);

DEFINE_VARIABLE_WITH_SYMBOL(Number_of_icp_bytes_left_in_message_series, Qnumber_of_icp_bytes_left_in_message_series);

DEFINE_VARIABLE_WITH_SYMBOL(Number_of_icp_bytes_ready_to_read, Qnumber_of_icp_bytes_ready_to_read);

/* INSTANTANEOUS-ICP-READER-BYTE-COUNT */
Object instantaneous_icp_reader_byte_count()
{
    Object temp;

    x_note_fn_call(47,21);
    temp = 
	    FIXNUM_NEGATE(FIXNUM_ADD(Number_of_icp_bytes_left_in_message_series,
	    Number_of_icp_bytes_ready_to_read));
    return VALUES_1(temp);
}

static Object Qmessage_series;     /* message-series */

static Object string_constant;     /* "" */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_1;   /* "~a" */

static Object string_constant_2;   /* "~&~areading ~a~@[ ~a~]~%" */

static Object string_constant_3;   /* "~&~a~a ~a~@[ ~a~]~:[~;: ~s~]~%" */

/* EMIT-ICP-READ-TRACE */
Object emit_icp_read_trace(this_is_prologue_p,byte_count_before_qm,
	    byte_count_after_qm,name_of_reader,qualifier_string_qm,
	    trace_type,report_icp_value_p,icp_value_qm,no_padding_p,message_p)
    Object this_is_prologue_p, byte_count_before_qm, byte_count_after_qm;
    Object name_of_reader, qualifier_string_qm, trace_type, report_icp_value_p;
    Object icp_value_qm, no_padding_p, message_p;
{
    Object tformat_fresh_line_is_newline_p, padding, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, index_1;
    SI_Long ab_loop_bind_, gensymed_symbol, gensymed_symbol_1, byte_delta;
    Declare_special(5);

    x_note_fn_call(47,22);
    if ((EQ(Icp_read_trace_cutoff_level_qm,T) || 
	    FIXNUM_GT(Icp_read_trace_cutoff_level_qm,
	    Current_icp_read_trace_level)) && ( !EQ(trace_type,
	    Qmessage_series) || Icp_trace_print_message_series_p) && 
	    (this_is_prologue_p ? Icp_read_trace_cutoff_level_qm && 
	    (EQ(Icp_read_trace_cutoff_level_qm,T) || 
	    IFIX(Icp_read_trace_cutoff_level_qm) >= (SI_Long)3L) : TRUEP(T))) {
	tformat_fresh_line_is_newline_p = Nil;
	if (no_padding_p)
	    padding = string_constant;
	else {
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
		      index_1 = (SI_Long)0L;
		      ab_loop_bind_ = IFIX(Current_icp_read_trace_level);
		    next_loop:
		      if (index_1 > ab_loop_bind_)
			  goto end_loop;
		      tformat(2,string_constant_1,
			      Blank_traced_icp_byte_column);
		      index_1 = index_1 + (SI_Long)1L;
		      goto next_loop;
		    end_loop:;
		      padding = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	PUSH_SPECIAL_WITH_SYMBOL(Tformat_fresh_line_is_newline_p,Qtformat_fresh_line_is_newline_p,tformat_fresh_line_is_newline_p,
		0);
	  if (this_is_prologue_p)
	      notify_user_in_parent_window(4,string_constant_2,padding,
		      name_of_reader,qualifier_string_qm);
	  else {
	      gensymed_symbol = IFIX(FIXNUM_MINUS(byte_count_after_qm,
		      byte_count_before_qm));
	      gensymed_symbol_1 = message_p ? (SI_Long)1L : (SI_Long)0L;
	      byte_delta = gensymed_symbol + gensymed_symbol_1;
	      notify_user_in_parent_window(7,string_constant_3,padding,
		      FIX(byte_delta * (SI_Long)2L),name_of_reader,
		      qualifier_string_qm,report_icp_value_p,icp_value_qm);
	  }
	  if ( !TRUEP(no_padding_p))
	      reclaim_text_string(padding);
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

Object Function_for_icp_value_writer_qm_prop = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Icp_write_trace_cutoff_level_qm, Qicp_write_trace_cutoff_level_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Current_icp_write_trace_level, Qcurrent_icp_write_trace_level);

DEFINE_VARIABLE_WITH_SYMBOL(Number_of_icp_bytes_for_message_series, Qnumber_of_icp_bytes_for_message_series);

DEFINE_VARIABLE_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer, Qnumber_of_icp_bytes_to_fill_buffer);

/* INSTANTANEOUS-ICP-WRITER-BYTE-COUNT */
Object instantaneous_icp_writer_byte_count()
{
    Object temp;

    x_note_fn_call(47,23);
    temp = FIXNUM_MINUS(Number_of_icp_bytes_for_message_series,
	    Number_of_icp_bytes_to_fill_buffer);
    return VALUES_1(temp);
}

static Object string_constant_4;   /* "~&~awriting ~a~@[ ~a~]~:[~;: ~s~]~%" */

/* EMIT-ICP-WRITE-TRACE */
Object emit_icp_write_trace(this_is_prologue_p,byte_count_before_qm,
	    byte_count_after_qm,name_of_writer,qualifier_string_qm,
	    trace_type,report_icp_value_p,icp_value_qm,no_padding_p,message_p)
    Object this_is_prologue_p, byte_count_before_qm, byte_count_after_qm;
    Object name_of_writer, qualifier_string_qm, trace_type, report_icp_value_p;
    Object icp_value_qm, no_padding_p, message_p;
{
    Object tformat_fresh_line_is_newline_p, padding, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, index_1;
    SI_Long ab_loop_bind_, gensymed_symbol, gensymed_symbol_1, byte_delta;
    Declare_special(5);

    x_note_fn_call(47,24);
    if ((EQ(Icp_write_trace_cutoff_level_qm,T) || 
	    FIXNUM_GT(Icp_write_trace_cutoff_level_qm,
	    Current_icp_write_trace_level)) && ( !EQ(trace_type,
	    Qmessage_series) || Icp_trace_print_message_series_p) && 
	    (this_is_prologue_p ? EQ(Icp_write_trace_cutoff_level_qm,T) || 
	    IFIX(Icp_write_trace_cutoff_level_qm) >= (SI_Long)3L : TRUEP(T))) {
	tformat_fresh_line_is_newline_p = Nil;
	if (no_padding_p)
	    padding = string_constant;
	else {
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
		      index_1 = (SI_Long)0L;
		      ab_loop_bind_ = IFIX(Current_icp_write_trace_level);
		    next_loop:
		      if (index_1 > ab_loop_bind_)
			  goto end_loop;
		      tformat(2,string_constant_1,
			      Blank_traced_icp_byte_column);
		      index_1 = index_1 + (SI_Long)1L;
		      goto next_loop;
		    end_loop:;
		      padding = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	PUSH_SPECIAL_WITH_SYMBOL(Tformat_fresh_line_is_newline_p,Qtformat_fresh_line_is_newline_p,tformat_fresh_line_is_newline_p,
		0);
	  if (this_is_prologue_p)
	      notify_user_in_parent_window(6,string_constant_4,padding,
		      name_of_writer,qualifier_string_qm,
		      report_icp_value_p,icp_value_qm);
	  else {
	      gensymed_symbol = IFIX(FIXNUM_MINUS(byte_count_after_qm,
		      byte_count_before_qm));
	      gensymed_symbol_1 = message_p ? (SI_Long)1L : (SI_Long)0L;
	      byte_delta = gensymed_symbol + gensymed_symbol_1;
	      notify_user_in_parent_window(7,string_constant_3,padding,
		      FIX(byte_delta * (SI_Long)2L),name_of_writer,
		      qualifier_string_qm,report_icp_value_p,icp_value_qm);
	  }
	  if ( !TRUEP(no_padding_p))
	      reclaim_text_string(padding);
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Icp_trace_level_descriptions, Qicp_trace_level_descriptions);

static Object Qetc;                /* etc */

/* DESCRIBE-ICP-TRACE-LEVEL */
Object describe_icp_trace_level(user_level,read_or_write_string)
    Object user_level, read_or_write_string;
{
    Object temp, code, description, ab_loop_list_, max_known_level;
    Object ab_loop_desetq_;

    x_note_fn_call(47,25);
    if (EQ(user_level,Qnil) || EQ(user_level,Qt) || EQ(user_level,
	    FIX((SI_Long)0L))) {
	format((SI_Long)3L,T,"~&ICP ~as:~%",read_or_write_string);
	temp = assoc_eql(user_level,Icp_trace_level_descriptions);
	return format((SI_Long)3L,T,"~&  ~a.~%",CDR(temp));
    }
    else {
	format((SI_Long)4L,T,"~&ICP ~a tracing at level ~s:~%",
		read_or_write_string,user_level);
	code = Nil;
	description = Nil;
	ab_loop_list_ = Icp_trace_level_descriptions;
	max_known_level = FIX((SI_Long)0L);
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	code = CAR(ab_loop_desetq_);
	description = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (NUMBERP(code) && FIXNUM_PLUSP(code)) {
	    max_known_level = FIXNUM_MAX(max_known_level,code);
	    if (FIXNUM_GE(user_level,code))
		format((SI_Long)3L,T,"~&  ~a.~%",description);
	}
	goto next_loop;
      end_loop:
	if (FIXNUM_GT(user_level,max_known_level)) {
	    temp = assq_function(Qetc,Icp_trace_level_descriptions);
	    format((SI_Long)3L,T,"~&  ~a.~%",CDR(temp));
	}
	return VALUES_1(Qnil);
    }
}

static Object list_constant;       /* # */

/* VALIDATE-ICP-TRACE-CUTOFF-VALUE */
Object validate_icp_trace_cutoff_value(cutoff_value,read_or_write_string,
	    previous_level)
    Object cutoff_value, read_or_write_string, previous_level;
{
    x_note_fn_call(47,26);
    if (FIXNUMP(cutoff_value) || memq_function(cutoff_value,list_constant))
	return VALUES_1(T);
    else
	return format((SI_Long)5L,T,
		"~&ICP-TRACE: expected a fixnum, T, or NIL -- got ~s.~%ICP ~a tracing level remains ~s.",
		cutoff_value,read_or_write_string,previous_level);
}

static Object Qsame;               /* same */

static Object Qqm;                 /* ? */

static Object string_constant_5;   /* "read" */

static Object QREAD;               /* |read| */

static Object string_constant_6;   /* "write" */

static Object list_constant_1;     /* # */

/* ICP-TRACE */
Object icp_trace(read_cutoff,write_cutoff)
    Object read_cutoff, write_cutoff;
{
    Object bad_settings, temp;

    x_note_fn_call(47,27);
    bad_settings = Nil;
    if (EQ(read_cutoff,Qsame));
    else if (EQ(read_cutoff,Qqm))
	describe_icp_trace_level(Icp_read_trace_cutoff_level_qm,
		string_constant_5);
    else if (validate_icp_trace_cutoff_value(read_cutoff,string_constant_5,
	    Icp_read_trace_cutoff_level_qm))
	Icp_read_trace_cutoff_level_qm = read_cutoff;
    else
	bad_settings = icp_cons_1(QREAD,bad_settings);
    if (EQ(write_cutoff,Qsame));
    else if (EQ(write_cutoff,Qqm))
	describe_icp_trace_level(Icp_write_trace_cutoff_level_qm,
		string_constant_6);
    else if (validate_icp_trace_cutoff_value(write_cutoff,
	    string_constant_6,Icp_write_trace_cutoff_level_qm))
	Icp_write_trace_cutoff_level_qm = write_cutoff;
    else
	bad_settings = icp_cons_1(Qwrite,bad_settings);
    if (IFIX(length(bad_settings)) == (SI_Long)1L) {
	temp = CAR(bad_settings);
	if (EQ(temp,QREAD)) {
	    if (memq_function(write_cutoff,list_constant_1))
		format((SI_Long)3L,T,"~&Write tracing unchanged at ~s.~%",
			Icp_write_trace_cutoff_level_qm);
	    else
		format((SI_Long)3L,T,
			"~&Write tracing successfully changed to ~s.~%",
			Icp_write_trace_cutoff_level_qm);
	}
	else if (EQ(temp,Qwrite)) {
	    if (memq_function(read_cutoff,list_constant_1))
		format((SI_Long)3L,T,"~&Read tracing unchanged at ~s.~%",
			Icp_read_trace_cutoff_level_qm);
	    else
		format((SI_Long)3L,T,
			"~&Read tracing successfully changed to ~s.~%",
			Icp_read_trace_cutoff_level_qm);
	}
    }
    return reclaim_icp_list_1(bad_settings);
}

/* ICP-UNTRACE */
Object icp_untrace()
{
    x_note_fn_call(47,28);
    Icp_read_trace_cutoff_level_qm = Nil;
    Icp_write_trace_cutoff_level_qm = Nil;
    return VALUES_1(Icp_write_trace_cutoff_level_qm);
}

static Object Qicp_log_intensity;  /* icp-log-intensity */

static Object string_constant_7;   /* "Specified icp-log-intensity option value may be an integer from 0 to 6:~%~%
				    *         0: Code will take tracing branches, but will not print trace messages~%
				    *         1: Message series will be traced~%
				    *         2: Messages will be traced~%
				    *         3: Message argument names will be traced~%
				    *         4: Top-level message values will be traced~%
				    *         5: Embedded message values will be traced~%
				    *         6: All levels will be traced~%~%
				    *         Assuming no tracing~%"
				    */

/* SET-ICP-TRACING-LEVEL-FROM-COMMAND-LINE */
Object set_icp_tracing_level_from_command_line()
{
    Object trace_level;

    x_note_fn_call(47,29);
    trace_level = getf(Command_line_arguments,Qicp_log_intensity,_);
    if (trace_level) {
	if (IFIX(trace_level) == (SI_Long)7L)
	    return notify_user(1,string_constant_7);
	else if (IFIX(trace_level) == (SI_Long)6L)
	    return icp_trace(T,T);
	else if (IFIX(trace_level) == (SI_Long)5L)
	    return icp_trace(T,T);
	else
	    return icp_trace(trace_level,trace_level);
    }
    else
	return VALUES_1(Nil);
}

Object Data_service_i_am_alive_messages = UNBOUND;

Object Equivalent_icp_value_type_prop = UNBOUND;

Object Icp_value_reader_function_prop = UNBOUND;

Object Icp_value_write_function_prop = UNBOUND;

Object Icp_value_reclaimer_prop = UNBOUND;

Object Name_of_corresponding_icp_object_index_space_prop = UNBOUND;

Object Access_form_for_corresponding_icp_object_map_prop = UNBOUND;

Object Reclaimer_for_icp_port_entry_prop = UNBOUND;

Object Reclaimer_for_icp_object_prop = UNBOUND;

Object Shutdown_reclaimer_for_icp_object_prop = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Deregister_corresponding_object_qm, Qderegister_corresponding_object_qm);

DEFINE_VARIABLE_WITH_SYMBOL(All_index_space_names, Qall_index_space_names);

DEFINE_VARIABLE_WITH_SYMBOL(Inhibit_corresponding_icp_object_making, Qinhibit_corresponding_icp_object_making);

static Object Qname_of_corresponding_icp_object_index_space;  /* name-of-corresponding-icp-object-index-space */

static Object Qaccess_form_for_corresponding_icp_object_map;  /* access-form-for-corresponding-icp-object-map */

/* INITIALIZE-ICP-OBJECT-TYPE-COMPILE */
Object initialize_icp_object_type_compile(icp_object_type,
	    name_of_corresponding_icp_object_index_space,
	    access_form_for_corresponding_icp_object_map)
    Object icp_object_type, name_of_corresponding_icp_object_index_space;
    Object access_form_for_corresponding_icp_object_map;
{
    x_note_fn_call(47,30);
    mutate_global_property(icp_object_type,
	    name_of_corresponding_icp_object_index_space,
	    Qname_of_corresponding_icp_object_index_space);
    mutate_global_property(icp_object_type,
	    access_form_for_corresponding_icp_object_map,
	    Qaccess_form_for_corresponding_icp_object_map);
    return VALUES_1(icp_object_type);
}

static Object Qreclaimer_for_icp_object;  /* reclaimer-for-icp-object */

static Object Qshutdown_reclaimer_for_icp_object;  /* shutdown-reclaimer-for-icp-object */

static Object Qreclaimer_for_icp_port_entry;  /* reclaimer-for-icp-port-entry */

/* INITIALIZE-ICP-OBJECT-TYPE */
Object initialize_icp_object_type(icp_object_type,icp_object_reclaimer_qm,
	    icp_object_shutdown_reclaimer_qm,
	    name_of_function_to_reclaim_icp_port_entry)
    Object icp_object_type, icp_object_reclaimer_qm;
    Object icp_object_shutdown_reclaimer_qm;
    Object name_of_function_to_reclaim_icp_port_entry;
{
    x_note_fn_call(47,31);
    mutate_global_property(icp_object_type,icp_object_reclaimer_qm ? 
	    SYMBOL_FUNCTION(icp_object_reclaimer_qm) : Nil,
	    Qreclaimer_for_icp_object);
    mutate_global_property(icp_object_type,
	    icp_object_shutdown_reclaimer_qm ? 
	    SYMBOL_FUNCTION(icp_object_shutdown_reclaimer_qm) : Nil,
	    Qshutdown_reclaimer_for_icp_object);
    mutate_global_property(icp_object_type,
	    SYMBOL_FUNCTION(name_of_function_to_reclaim_icp_port_entry),
	    Qreclaimer_for_icp_port_entry);
    return VALUES_1(icp_object_type);
}

static Object Qab_name_of_unique_structure_type;  /* ab-name-of-unique-structure-type */

static Object Qregistered_item;    /* registered-item */

static Object Qstandard_icp_object_index_space;  /* standard-icp-object-index-space */

static Object Qfont_map;           /* font-map */

/* ICP-OBJECT-TYPE-GIVEN-ICP-OBJECT */
Object icp_object_type_given_icp_object(icp_object,
	    name_of_corresponding_icp_object_index_space)
    Object icp_object, name_of_corresponding_icp_object_index_space;
{
    Object type, temp;

    x_note_fn_call(47,32);
    if (SIMPLE_VECTOR_P(icp_object)) {
	type = ISVREF(icp_object,(SI_Long)0L);
	temp = SYMBOLP(type) && EQ(SYMBOL_PACKAGE(type),
		The_g2_defstruct_package) ? 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(type),
		Qab_name_of_unique_structure_type) : Nil;
	if (temp);
	else
	    temp = framep_function(icp_object) ? Qregistered_item : Nil;
    }
    else if (SYMBOLP(icp_object))
	temp = EQ(name_of_corresponding_icp_object_index_space,
		Qstandard_icp_object_index_space) ? Qsymbol : Nil;
    else if (CONSP(icp_object))
	temp = Qfont_map;
    else
	temp = Nil;
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Icp_message_handler_array, Qicp_message_handler_array);

DEFINE_VARIABLE_WITH_SYMBOL(Icp_message_handler_name_array, Qicp_message_handler_name_array);

DEFINE_VARIABLE_WITH_SYMBOL(Icp_printing_message_handler_array, Qicp_printing_message_handler_array);

Object Icp_message_type_code_prop = UNBOUND;

Object Priority_for_icp_priority_category_prop = UNBOUND;

Object Icp_priority_category_for_message_prop = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Icp_priority_categories_for_gsi, Qicp_priority_categories_for_gsi);

static Object Qgspan;              /* gspan */

static Object Qicp_priority_category_for_message;  /* icp-priority-category-for-message */

static Object Qicp_message_type_code;  /* icp-message-type-code */

/* ADD-ICP-MESSAGE-TYPE-CODE */
Object add_icp_message_type_code(icp_message_type,icp_message_type_code,
	    category)
    Object icp_message_type, icp_message_type_code, category;
{
    x_note_fn_call(47,33);
    if ( !EQ(category,Qgspan))
	mutate_global_property(icp_message_type,category,
		Qicp_priority_category_for_message);
    return mutate_global_property(icp_message_type,icp_message_type_code,
	    Qicp_message_type_code);
}

/* ADD-ICP-MESSAGE-HANDLER */
Object add_icp_message_handler(handler_name,icp_message_type_code)
    Object handler_name, icp_message_type_code;
{
    Object svref_arg_1, svref_new_value;

    x_note_fn_call(47,34);
    svref_arg_1 = Icp_message_handler_name_array;
    SVREF(svref_arg_1,icp_message_type_code) = handler_name;
    svref_arg_1 = Icp_message_handler_array;
    svref_new_value = SYMBOL_FUNCTION(handler_name);
    SVREF(svref_arg_1,icp_message_type_code) = svref_new_value;
    return VALUES_1(handler_name);
}

DEFINE_VARIABLE_WITH_SYMBOL(Active_icp_sockets, Qactive_icp_sockets);

/* ADD-TO-ACTIVE-ICP-SOCKETS */
Object add_to_active_icp_sockets(icp_socket)
    Object icp_socket;
{
    x_note_fn_call(47,35);
    Active_icp_sockets = icp_cons_1(icp_socket,Active_icp_sockets);
    return VALUES_1(Active_icp_sockets);
}

DEFINE_VARIABLE_WITH_SYMBOL(Maximum_object_passing_bandwidth, Qmaximum_object_passing_bandwidth);

Object Icp_socket_shutdown_handshake_timeout = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Icp_socket_connect_negotiation_timeout_default, Qicp_socket_connect_negotiation_timeout_default);

Object Icp_connection_closed = UNBOUND;

Object Icp_connection_connect_in_progress = UNBOUND;

Object Icp_connection_running = UNBOUND;

Object Icp_connection_shutdown_acknowledgement_rundown = UNBOUND;

Object Icp_connection_awaiting_acknowledgement = UNBOUND;

Object Icp_socket_listening = UNBOUND;

Object Icp_socket_error = UNBOUND;

Object Newest_icp_version = UNBOUND;

Object Gsi_connection_initializing = UNBOUND;

Object Gsi_connection_established = UNBOUND;

Object The_type_description_of_socket = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_sockets, Qchain_of_available_sockets);

DEFINE_VARIABLE_WITH_SYMBOL(Socket_count, Qsocket_count);

Object Chain_of_available_sockets_vector = UNBOUND;

/* SOCKET-STRUCTURE-MEMORY-USAGE */
Object socket_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(47,36);
    temp = Socket_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)1L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-SOCKET-COUNT */
Object outstanding_socket_count()
{
    Object def_structure_socket_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(47,37);
    gensymed_symbol = IFIX(Socket_count);
    def_structure_socket_variable = Chain_of_available_sockets;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_socket_variable))
	goto end_loop;
    def_structure_socket_variable = ISVREF(def_structure_socket_variable,
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

/* RECLAIM-SOCKET-1 */
Object reclaim_socket_1(socket_1)
    Object socket_1;
{
    Object temp, svref_arg_2;

    x_note_fn_call(47,38);
    inline_note_reclaim_cons(socket_1,Nil);
    temp = ISVREF(Chain_of_available_sockets_vector,
	    IFIX(Current_thread_index));
    SVREF(socket_1,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_sockets_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = socket_1;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-SOCKET */
Object reclaim_structure_for_socket(socket_1)
    Object socket_1;
{
    x_note_fn_call(47,39);
    return reclaim_socket_1(socket_1);
}

static Object Qg2_defstruct_structure_name_socket_g2_struct;  /* g2-defstruct-structure-name::socket-g2-struct */

/* MAKE-PERMANENT-SOCKET-STRUCTURE-INTERNAL */
Object make_permanent_socket_structure_internal()
{
    Object def_structure_socket_variable, defstruct_g2_socket_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(47,40);
    def_structure_socket_variable = Nil;
    atomic_incff_symval(Qsocket_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_socket_variable = Nil;
	gensymed_symbol = (SI_Long)1L;
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
	defstruct_g2_socket_variable = the_array;
	SVREF(defstruct_g2_socket_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_socket_g2_struct;
	def_structure_socket_variable = defstruct_g2_socket_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_socket_variable);
}

/* MAKE-SOCKET-1 */
Object make_socket_1()
{
    Object def_structure_socket_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(47,41);
    def_structure_socket_variable = 
	    ISVREF(Chain_of_available_sockets_vector,
	    IFIX(Current_thread_index));
    if (def_structure_socket_variable) {
	svref_arg_1 = Chain_of_available_sockets_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_socket_variable,(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_socket_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_socket_g2_struct;
    }
    else
	def_structure_socket_variable = 
		make_permanent_socket_structure_internal();
    inline_note_allocate_cons(def_structure_socket_variable,Nil);
    return VALUES_1(def_structure_socket_variable);
}

Object The_type_description_of_icp_socket = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_icp_sockets, Qchain_of_available_icp_sockets);

DEFINE_VARIABLE_WITH_SYMBOL(Icp_socket_count, Qicp_socket_count);

Object Chain_of_available_icp_sockets_vector = UNBOUND;

/* ICP-SOCKET-STRUCTURE-MEMORY-USAGE */
Object icp_socket_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(47,42);
    temp = Icp_socket_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)56L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ICP-SOCKET-COUNT */
Object outstanding_icp_socket_count()
{
    Object def_structure_icp_socket_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(47,43);
    gensymed_symbol = IFIX(Icp_socket_count);
    def_structure_icp_socket_variable = Chain_of_available_icp_sockets;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_icp_socket_variable))
	goto end_loop;
    def_structure_icp_socket_variable = 
	    ISVREF(def_structure_icp_socket_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ICP-SOCKET-INTERNAL-1 */
Object reclaim_icp_socket_internal_1(icp_socket)
    Object icp_socket;
{
    Object structure_being_reclaimed, thing, gensymed_symbol, temp;
    Object svref_arg_2;
    Declare_special(2);

    x_note_fn_call(47,44);
    inline_note_reclaim_cons(icp_socket,Nil);
    structure_being_reclaimed = icp_socket;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    1);
      thing = ISVREF(icp_socket,(SI_Long)2L);
      if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	  reclaim_wide_string(thing);
      SVREF(icp_socket,FIX((SI_Long)2L)) = Nil;
      reclaim_enclosing_interface_frame_serial_number(ISVREF(icp_socket,
	      (SI_Long)6L));
      SVREF(icp_socket,FIX((SI_Long)6L)) = Nil;
      reclaim_icp_callbacks(ISVREF(icp_socket,(SI_Long)10L));
      SVREF(icp_socket,FIX((SI_Long)10L)) = Nil;
      reclaim_icp_callbacks(ISVREF(icp_socket,(SI_Long)11L));
      SVREF(icp_socket,FIX((SI_Long)11L)) = Nil;
      reclaim_icp_callbacks(ISVREF(icp_socket,(SI_Long)12L));
      SVREF(icp_socket,FIX((SI_Long)12L)) = Nil;
      reclaim_icp_callbacks(ISVREF(icp_socket,(SI_Long)13L));
      SVREF(icp_socket,FIX((SI_Long)13L)) = Nil;
      reclaim_icp_callbacks(ISVREF(icp_socket,(SI_Long)14L));
      SVREF(icp_socket,FIX((SI_Long)14L)) = Nil;
      gensymed_symbol = Nil;
    next_loop:
      gensymed_symbol = ISVREF(icp_socket,(SI_Long)16L);
      if (CAS_SVREF(icp_socket,(SI_Long)16L,gensymed_symbol,Nil)) {
	  if (gensymed_symbol) {
	      if (EQ(gensymed_symbol,Current_schedule_task))
		  Current_schedule_task = Nil;
	      if (ISVREF(gensymed_symbol,(SI_Long)6L))
		  cancel_and_reclaim_scheduled_queue_element_1(gensymed_symbol);
	      inline_note_reclaim_cons(gensymed_symbol,Nil);
	      structure_being_reclaimed = gensymed_symbol;
	      PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		      0);
		reclaim_schedule_task_args(ISVREF(gensymed_symbol,
			(SI_Long)9L));
		SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Nil;
	      POP_SPECIAL();
	      temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		      IFIX(Current_thread_index));
	      SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp;
	      temp = Chain_of_available_schedule_tasks_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = gensymed_symbol;
	  }
	  goto end_1;
      }
      goto next_loop;
    end_loop:
    end_1:;
      SVREF(icp_socket,FIX((SI_Long)16L)) = Nil;
      reclaim_icp_version_info(ISVREF(icp_socket,(SI_Long)19L));
      SVREF(icp_socket,FIX((SI_Long)19L)) = Nil;
      reclaim_i_am_alive_info_qm(ISVREF(icp_socket,(SI_Long)24L));
      SVREF(icp_socket,FIX((SI_Long)24L)) = Nil;
      reclaim_gsi_extension_data_for_gsi(ISVREF(icp_socket,(SI_Long)29L));
      SVREF(icp_socket,FIX((SI_Long)29L)) = Nil;
      gensymed_symbol = Nil;
    next_loop_1:
      gensymed_symbol = ISVREF(icp_socket,(SI_Long)34L);
      if (CAS_SVREF(icp_socket,(SI_Long)34L,gensymed_symbol,Nil)) {
	  if (gensymed_symbol) {
	      if (EQ(gensymed_symbol,Current_schedule_task))
		  Current_schedule_task = Nil;
	      if (ISVREF(gensymed_symbol,(SI_Long)6L))
		  cancel_and_reclaim_scheduled_queue_element_1(gensymed_symbol);
	      inline_note_reclaim_cons(gensymed_symbol,Nil);
	      structure_being_reclaimed = gensymed_symbol;
	      PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		      0);
		reclaim_schedule_task_args(ISVREF(gensymed_symbol,
			(SI_Long)9L));
		SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Nil;
	      POP_SPECIAL();
	      temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		      IFIX(Current_thread_index));
	      SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp;
	      temp = Chain_of_available_schedule_tasks_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = gensymed_symbol;
	  }
	  goto end_2;
      }
      goto next_loop_1;
    end_loop_1:
    end_2:;
      SVREF(icp_socket,FIX((SI_Long)34L)) = Nil;
      gensymed_symbol = Nil;
    next_loop_2:
      gensymed_symbol = ISVREF(icp_socket,(SI_Long)35L);
      if (CAS_SVREF(icp_socket,(SI_Long)35L,gensymed_symbol,Nil)) {
	  if (gensymed_symbol) {
	      if (EQ(gensymed_symbol,Current_schedule_task))
		  Current_schedule_task = Nil;
	      if (ISVREF(gensymed_symbol,(SI_Long)6L))
		  cancel_and_reclaim_scheduled_queue_element_1(gensymed_symbol);
	      inline_note_reclaim_cons(gensymed_symbol,Nil);
	      structure_being_reclaimed = gensymed_symbol;
	      PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		      0);
		reclaim_schedule_task_args(ISVREF(gensymed_symbol,
			(SI_Long)9L));
		SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Nil;
	      POP_SPECIAL();
	      temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		      IFIX(Current_thread_index));
	      SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp;
	      temp = Chain_of_available_schedule_tasks_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = gensymed_symbol;
	  }
	  goto end_3;
      }
      goto next_loop_2;
    end_loop_2:
    end_3:;
      SVREF(icp_socket,FIX((SI_Long)35L)) = Nil;
      gensymed_symbol = Nil;
    next_loop_3:
      gensymed_symbol = ISVREF(icp_socket,(SI_Long)36L);
      if (CAS_SVREF(icp_socket,(SI_Long)36L,gensymed_symbol,Nil)) {
	  if (gensymed_symbol) {
	      if (EQ(gensymed_symbol,Current_schedule_task))
		  Current_schedule_task = Nil;
	      if (ISVREF(gensymed_symbol,(SI_Long)6L))
		  cancel_and_reclaim_scheduled_queue_element_1(gensymed_symbol);
	      inline_note_reclaim_cons(gensymed_symbol,Nil);
	      structure_being_reclaimed = gensymed_symbol;
	      PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		      0);
		reclaim_schedule_task_args(ISVREF(gensymed_symbol,
			(SI_Long)9L));
		SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Nil;
	      POP_SPECIAL();
	      temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		      IFIX(Current_thread_index));
	      SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp;
	      temp = Chain_of_available_schedule_tasks_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = gensymed_symbol;
	  }
	  goto end_4;
      }
      goto next_loop_3;
    end_loop_3:
    end_4:;
      SVREF(icp_socket,FIX((SI_Long)36L)) = Nil;
      reclaim_resumable_icp_output_task_queue_vector(ISVREF(icp_socket,
	      (SI_Long)37L));
      SVREF(icp_socket,FIX((SI_Long)37L)) = Nil;
      reclaim_remote_procedure_call_start_map(ISVREF(icp_socket,(SI_Long)41L));
      SVREF(icp_socket,FIX((SI_Long)41L)) = Nil;
      gensymed_symbol = Nil;
    next_loop_4:
      gensymed_symbol = ISVREF(icp_socket,(SI_Long)43L);
      if (CAS_SVREF(icp_socket,(SI_Long)43L,gensymed_symbol,Nil)) {
	  if (gensymed_symbol) {
	      if (EQ(gensymed_symbol,Current_schedule_task))
		  Current_schedule_task = Nil;
	      if (ISVREF(gensymed_symbol,(SI_Long)6L))
		  cancel_and_reclaim_scheduled_queue_element_1(gensymed_symbol);
	      inline_note_reclaim_cons(gensymed_symbol,Nil);
	      structure_being_reclaimed = gensymed_symbol;
	      PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		      0);
		reclaim_schedule_task_args(ISVREF(gensymed_symbol,
			(SI_Long)9L));
		SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Nil;
	      POP_SPECIAL();
	      temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		      IFIX(Current_thread_index));
	      SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp;
	      temp = Chain_of_available_schedule_tasks_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = gensymed_symbol;
	  }
	  goto end_5;
      }
      goto next_loop_4;
    end_loop_4:
    end_5:;
      SVREF(icp_socket,FIX((SI_Long)43L)) = Nil;
      gensymed_symbol = Nil;
    next_loop_5:
      gensymed_symbol = ISVREF(icp_socket,(SI_Long)44L);
      if (CAS_SVREF(icp_socket,(SI_Long)44L,gensymed_symbol,Nil)) {
	  if (gensymed_symbol) {
	      if (EQ(gensymed_symbol,Current_schedule_task))
		  Current_schedule_task = Nil;
	      if (ISVREF(gensymed_symbol,(SI_Long)6L))
		  cancel_and_reclaim_scheduled_queue_element_1(gensymed_symbol);
	      inline_note_reclaim_cons(gensymed_symbol,Nil);
	      structure_being_reclaimed = gensymed_symbol;
	      PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		      0);
		reclaim_schedule_task_args(ISVREF(gensymed_symbol,
			(SI_Long)9L));
		SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Nil;
	      POP_SPECIAL();
	      temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		      IFIX(Current_thread_index));
	      SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp;
	      temp = Chain_of_available_schedule_tasks_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = gensymed_symbol;
	  }
	  goto end_6;
      }
      goto next_loop_5;
    end_loop_5:
    end_6:;
      SVREF(icp_socket,FIX((SI_Long)44L)) = Nil;
      gensymed_symbol = Nil;
    next_loop_6:
      gensymed_symbol = ISVREF(icp_socket,(SI_Long)45L);
      if (CAS_SVREF(icp_socket,(SI_Long)45L,gensymed_symbol,Nil)) {
	  if (gensymed_symbol) {
	      if (EQ(gensymed_symbol,Current_schedule_task))
		  Current_schedule_task = Nil;
	      if (ISVREF(gensymed_symbol,(SI_Long)6L))
		  cancel_and_reclaim_scheduled_queue_element_1(gensymed_symbol);
	      inline_note_reclaim_cons(gensymed_symbol,Nil);
	      structure_being_reclaimed = gensymed_symbol;
	      PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		      0);
		reclaim_schedule_task_args(ISVREF(gensymed_symbol,
			(SI_Long)9L));
		SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Nil;
	      POP_SPECIAL();
	      temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		      IFIX(Current_thread_index));
	      SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp;
	      temp = Chain_of_available_schedule_tasks_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = gensymed_symbol;
	  }
	  goto end_7;
      }
      goto next_loop_6;
    end_loop_6:
    end_7:;
      SVREF(icp_socket,FIX((SI_Long)45L)) = Nil;
      reclaim_icp_tree_1(ISVREF(icp_socket,(SI_Long)46L));
      SVREF(icp_socket,FIX((SI_Long)46L)) = Nil;
      gensymed_symbol = Nil;
    next_loop_7:
      gensymed_symbol = ISVREF(icp_socket,(SI_Long)47L);
      if (CAS_SVREF(icp_socket,(SI_Long)47L,gensymed_symbol,Nil)) {
	  if (gensymed_symbol) {
	      if (EQ(gensymed_symbol,Current_schedule_task))
		  Current_schedule_task = Nil;
	      if (ISVREF(gensymed_symbol,(SI_Long)6L))
		  cancel_and_reclaim_scheduled_queue_element_1(gensymed_symbol);
	      inline_note_reclaim_cons(gensymed_symbol,Nil);
	      structure_being_reclaimed = gensymed_symbol;
	      PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		      0);
		reclaim_schedule_task_args(ISVREF(gensymed_symbol,
			(SI_Long)9L));
		SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Nil;
	      POP_SPECIAL();
	      temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		      IFIX(Current_thread_index));
	      SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp;
	      temp = Chain_of_available_schedule_tasks_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = gensymed_symbol;
	  }
	  goto end_8;
      }
      goto next_loop_7;
    end_loop_7:
    end_8:;
      SVREF(icp_socket,FIX((SI_Long)47L)) = Nil;
      gensymed_symbol = Nil;
    next_loop_8:
      gensymed_symbol = ISVREF(icp_socket,(SI_Long)51L);
      if (CAS_SVREF(icp_socket,(SI_Long)51L,gensymed_symbol,Nil)) {
	  if (gensymed_symbol) {
	      if (EQ(gensymed_symbol,Current_schedule_task))
		  Current_schedule_task = Nil;
	      if (ISVREF(gensymed_symbol,(SI_Long)6L))
		  cancel_and_reclaim_scheduled_queue_element_1(gensymed_symbol);
	      inline_note_reclaim_cons(gensymed_symbol,Nil);
	      structure_being_reclaimed = gensymed_symbol;
	      PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		      0);
		reclaim_schedule_task_args(ISVREF(gensymed_symbol,
			(SI_Long)9L));
		SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Nil;
	      POP_SPECIAL();
	      temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		      IFIX(Current_thread_index));
	      SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp;
	      temp = Chain_of_available_schedule_tasks_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = gensymed_symbol;
	  }
	  goto end_9;
      }
      goto next_loop_8;
    end_loop_8:
    end_9:;
      SVREF(icp_socket,FIX((SI_Long)51L)) = Nil;
      thing = ISVREF(icp_socket,(SI_Long)54L);
      if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	  reclaim_wide_string(thing);
      SVREF(icp_socket,FIX((SI_Long)54L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_icp_sockets_vector,
	    IFIX(Current_thread_index));
    SVREF(icp_socket,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_icp_sockets_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = icp_socket;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ICP-SOCKET */
Object reclaim_structure_for_icp_socket(icp_socket)
    Object icp_socket;
{
    x_note_fn_call(47,45);
    return reclaim_icp_socket_internal_1(icp_socket);
}

static Object Qg2_defstruct_structure_name_icp_socket_g2_struct;  /* g2-defstruct-structure-name::icp-socket-g2-struct */

/* MAKE-PERMANENT-ICP-SOCKET-STRUCTURE-INTERNAL */
Object make_permanent_icp_socket_structure_internal()
{
    Object def_structure_icp_socket_variable, defstruct_g2_icp_socket_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(47,46);
    def_structure_icp_socket_variable = Nil;
    atomic_incff_symval(Qicp_socket_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_icp_socket_variable = Nil;
	gensymed_symbol = (SI_Long)56L;
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
	defstruct_g2_icp_socket_variable = the_array;
	SVREF(defstruct_g2_icp_socket_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_icp_socket_g2_struct;
	def_structure_icp_socket_variable = defstruct_g2_icp_socket_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_icp_socket_variable);
}

static Object Qinitial;            /* initial */

static Object Qunknown;            /* unknown */

/* MAKE-ICP-SOCKET-STRUCTURE-1 */
Object make_icp_socket_structure_1(type_of_icp_connection,
	    icp_connection_name,icp_connection_state,listener_socket,
	    icp_socket_local_system_name)
    Object type_of_icp_connection, icp_connection_name, icp_connection_state;
    Object listener_socket, icp_socket_local_system_name;
{
    Object def_structure_icp_socket_variable, temp, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(47,47);
    def_structure_icp_socket_variable = 
	    ISVREF(Chain_of_available_icp_sockets_vector,
	    IFIX(Current_thread_index));
    if (def_structure_icp_socket_variable) {
	temp = Chain_of_available_icp_sockets_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_icp_socket_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_icp_socket_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_icp_socket_g2_struct;
    }
    else
	def_structure_icp_socket_variable = 
		make_permanent_icp_socket_structure_internal();
    inline_note_allocate_cons(def_structure_icp_socket_variable,Nil);
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)1L)) = 
	    type_of_icp_connection;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)2L)) = 
	    icp_connection_name;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)15L)) = 
	    icp_connection_state;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)33L)) = 
	    listener_socket;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)49L)) = 
	    icp_socket_local_system_name;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)13L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)14L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)16L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)17L)) = T;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)18L)) = Qinitial;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)19L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)20L)) = Nil;
    ISVREF(def_structure_icp_socket_variable,(SI_Long)21L) = FIX((SI_Long)0L);
    ISVREF(def_structure_icp_socket_variable,(SI_Long)22L) = FIX((SI_Long)0L);
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)23L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)24L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)25L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)26L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)27L)) = Nil;
    ISVREF(def_structure_icp_socket_variable,(SI_Long)28L) = FIX((SI_Long)1L);
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)29L)) = Nil;
    temp = Maximum_object_passing_bandwidth;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)30L)) = temp;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)31L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)32L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)34L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)35L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)36L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)37L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)38L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)39L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)40L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)41L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)42L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)43L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)44L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)45L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)46L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)47L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)48L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)50L)) = Qunknown;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)51L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)52L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)53L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)54L)) = Nil;
    SVREF(def_structure_icp_socket_variable,FIX((SI_Long)55L)) = Nil;
    return VALUES_1(def_structure_icp_socket_variable);
}

/* RECLAIM-REMOTE-PROCEDURE-CALL-START-MAP */
Object reclaim_remote_procedure_call_start_map(map_1)
    Object map_1;
{
    x_note_fn_call(47,48);
    if (map_1)
	reclaim_index_space_1(map_1);
    return VALUES_1(Nil);
}

/* RECLAIM-ENCLOSING-INTERFACE-FRAME-SERIAL-NUMBER */
Object reclaim_enclosing_interface_frame_serial_number(frame_serial_number)
    Object frame_serial_number;
{
    x_note_fn_call(47,49);
    reclaim_frame_serial_number(frame_serial_number);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_icp_callback_conses, Qavailable_icp_callback_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_icp_callback_conses_tail, Qavailable_icp_callback_conses_tail);

Object Available_icp_callback_conses_vector = UNBOUND;

Object Available_icp_callback_conses_tail_vector = UNBOUND;

Object Icp_callback_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Icp_callback_cons_counter, Qicp_callback_cons_counter);

/* OUTSTANDING-ICP-CALLBACK-CONSES */
Object outstanding_icp_callback_conses()
{
    Object temp;

    x_note_fn_call(47,50);
    temp = FIXNUM_MINUS(Icp_callback_cons_counter,
	    length(Available_icp_callback_conses));
    return VALUES_1(temp);
}

/* ICP-CALLBACK-CONS-MEMORY-USAGE */
Object icp_callback_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(47,51);
    temp = FIXNUM_TIMES(Icp_callback_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-ICP-CALLBACK-CONS-POOL */
Object replenish_icp_callback_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(47,52);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qicp_callback_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_icp_callback_conses_vector,
	    IFIX(Current_thread_index))) {
	svref_arg_1 = Available_icp_callback_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_icp_callback_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_icp_callback_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_icp_callback_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Icp_callback_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qicp_callback;       /* icp-callback */

/* ICP-CALLBACK-CONS-1 */
Object icp_callback_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(47,53);
    new_cons = ISVREF(Available_icp_callback_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_icp_callback_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_icp_callback_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_icp_callback_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_icp_callback_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qicp_callback);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-ICP-CALLBACK-LIST-POOL */
Object replenish_icp_callback_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(47,54);
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
    if (ISVREF(Available_icp_callback_conses_vector,
	    IFIX(Current_thread_index))) {
	svref_arg_1 = Available_icp_callback_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_icp_callback_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_icp_callback_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_icp_callback_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qicp_callback_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-ICP-CALLBACK-LIST-1 */
Object make_icp_callback_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(47,55);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_icp_callback_conses_vector,
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
	replenish_icp_callback_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_icp_callback_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qicp_callback);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_icp_callback_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_icp_callback_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_icp_callback_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_icp_callback_conses_tail_vector;
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

/* ICP-CALLBACK-LIST-2 */
Object icp_callback_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(47,56);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_icp_callback_conses_vector,
	    IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_icp_callback_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_icp_callback_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qicp_callback);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_icp_callback_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_icp_callback_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_icp_callback_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_icp_callback_conses_tail_vector;
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

/* ICP-CALLBACK-LIST-3 */
Object icp_callback_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(47,57);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_icp_callback_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_icp_callback_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_icp_callback_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qicp_callback);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_icp_callback_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_icp_callback_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_icp_callback_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_icp_callback_conses_tail_vector;
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

/* ICP-CALLBACK-LIST-4 */
Object icp_callback_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(47,58);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_icp_callback_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_icp_callback_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_icp_callback_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qicp_callback);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_icp_callback_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_icp_callback_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_icp_callback_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_icp_callback_conses_tail_vector;
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

/* ICP-CALLBACK-LIST-TRACE-HOOK */
Object icp_callback_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(47,59);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-ICP-CALLBACK-CONSES-1 */
Object copy_tree_using_icp_callback_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(47,60);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_icp_callback_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_icp_callback_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_icp_callback_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_icp_callback_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_icp_callback_cons_pool();
	temp_1 = copy_tree_using_icp_callback_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qicp_callback);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_icp_callback_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_icp_callback_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_icp_callback_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_icp_callback_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_icp_callback_cons_pool();
	temp_1 = 
		copy_tree_using_icp_callback_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qicp_callback);
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

/* COPY-LIST-USING-ICP-CALLBACK-CONSES-1 */
Object copy_list_using_icp_callback_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(47,61);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_icp_callback_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_icp_callback_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_icp_callback_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_icp_callback_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_icp_callback_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qicp_callback);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_icp_callback_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_icp_callback_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_icp_callback_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_icp_callback_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_icp_callback_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qicp_callback);
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

/* RECLAIM-ICP-CALLBACK-CONS-1 */
Object reclaim_icp_callback_cons_1(icp_callback_cons)
    Object icp_callback_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(47,62);
    inline_note_reclaim_cons(icp_callback_cons,Qicp_callback);
    if (ISVREF(Available_icp_callback_conses_tail_vector,
	    IFIX(Current_thread_index))) {
	temp = ISVREF(Available_icp_callback_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = icp_callback_cons;
	temp = Available_icp_callback_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = icp_callback_cons;
    }
    else {
	temp = Available_icp_callback_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = icp_callback_cons;
	temp = Available_icp_callback_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = icp_callback_cons;
    }
    M_CDR(icp_callback_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-ICP-CALLBACK-LIST-1 */
Object reclaim_icp_callback_list_1(icp_callback_list)
    Object icp_callback_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(47,63);
    if (icp_callback_list) {
	last_1 = icp_callback_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qicp_callback);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qicp_callback);
	if (ISVREF(Available_icp_callback_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_icp_callback_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = icp_callback_list;
	    temp = Available_icp_callback_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_icp_callback_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = icp_callback_list;
	    temp = Available_icp_callback_conses_tail_vector;
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

/* RECLAIM-ICP-CALLBACK-LIST*-1 */
Object reclaim_icp_callback_list_star_1(icp_callback_list)
    Object icp_callback_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(47,64);
    if (CONSP(icp_callback_list)) {
	temp = last(icp_callback_list,_);
	M_CDR(temp) = Nil;
	if (icp_callback_list) {
	    last_1 = icp_callback_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qicp_callback);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qicp_callback);
	    if (ISVREF(Available_icp_callback_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_icp_callback_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = icp_callback_list;
		temp = Available_icp_callback_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_icp_callback_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = icp_callback_list;
		temp = Available_icp_callback_conses_tail_vector;
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

/* RECLAIM-ICP-CALLBACK-TREE-1 */
Object reclaim_icp_callback_tree_1(tree)
    Object tree;
{
    Object e, e2, icp_callback_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(47,65);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_icp_callback_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		icp_callback_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(icp_callback_cons,Qicp_callback);
		if (EQ(icp_callback_cons,e))
		    goto end_1;
		else if ( !TRUEP(icp_callback_cons))
		    goto end_1;
		else
		    icp_callback_cons = CDR(icp_callback_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_icp_callback_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_icp_callback_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_icp_callback_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_icp_callback_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_icp_callback_conses_tail_vector;
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

/* DELETE-ICP-CALLBACK-ELEMENT-1 */
Object delete_icp_callback_element_1(element,icp_callback_list)
    Object element, icp_callback_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(47,66);
    if (icp_callback_list) {
	if (EQ(element,M_CAR(icp_callback_list))) {
	    temp = CDR(icp_callback_list);
	    inline_note_reclaim_cons(icp_callback_list,Qicp_callback);
	    if (ISVREF(Available_icp_callback_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_icp_callback_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = icp_callback_list;
		temp_1 = Available_icp_callback_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = icp_callback_list;
	    }
	    else {
		temp_1 = Available_icp_callback_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = icp_callback_list;
		temp_1 = Available_icp_callback_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = icp_callback_list;
	    }
	    M_CDR(icp_callback_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = icp_callback_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qicp_callback);
		if (ISVREF(Available_icp_callback_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = 
			    ISVREF(Available_icp_callback_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_icp_callback_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_icp_callback_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_icp_callback_conses_tail_vector;
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
	    temp = icp_callback_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-ICP-CALLBACK-CONS-1 */
Object delete_icp_callback_cons_1(icp_callback_cons,icp_callback_list)
    Object icp_callback_cons, icp_callback_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(47,67);
    if (EQ(icp_callback_cons,icp_callback_list))
	temp = CDR(icp_callback_list);
    else {
	l_trailer_qm = Nil;
	l = icp_callback_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,icp_callback_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = icp_callback_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_icp_callback_cons_1(icp_callback_cons);
    return VALUES_1(temp);
}

/* RECLAIM-ICP-CALLBACKS */
Object reclaim_icp_callbacks(callbacks)
    Object callbacks;
{
    x_note_fn_call(47,68);
    reclaim_icp_callback_list_1(callbacks);
    return VALUES_1(Nil);
}

/* EXECUTE-ICP-CONNECTION-LOSS-CALLBACKS */
Object execute_icp_connection_loss_callbacks(icp_socket,clean_qm)
    Object icp_socket, clean_qm;
{
    Object callback_functions, callback_function, ab_loop_list_;

    x_note_fn_call(47,69);
    callback_functions = ISVREF(icp_socket,(SI_Long)10L);
    callback_function = Nil;
    ab_loop_list_ = callback_functions;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    callback_function = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    FUNCALL_2(callback_function,icp_socket,clean_qm);
    goto next_loop;
  end_loop:;
    deregister_all_icp_connection_loss_callbacks(icp_socket);
    return VALUES_1(Nil);
}

/* REGISTER-ICP-CONNECTION-LOSS-CALLBACK */
Object register_icp_connection_loss_callback(callback_function,icp_socket)
    Object callback_function, icp_socket;
{
    Object icp_callback_push_modify_macro_arg, car_1, cdr_1, svref_new_value;

    x_note_fn_call(47,70);
    icp_callback_push_modify_macro_arg = callback_function;
    car_1 = icp_callback_push_modify_macro_arg;
    cdr_1 = ISVREF(icp_socket,(SI_Long)10L);
    svref_new_value = icp_callback_cons_1(car_1,cdr_1);
    SVREF(icp_socket,FIX((SI_Long)10L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-ICP-CONNECTION-LOSS-CALLBACKS */
Object reclaim_icp_connection_loss_callbacks(callbacks)
    Object callbacks;
{
    x_note_fn_call(47,71);
    reclaim_icp_callback_list_1(callbacks);
    return VALUES_1(Nil);
}

/* DEREGISTER-ALL-ICP-CONNECTION-LOSS-CALLBACKS */
Object deregister_all_icp_connection_loss_callbacks(icp_socket)
    Object icp_socket;
{
    Object callback_functions_qm;

    x_note_fn_call(47,72);
    callback_functions_qm = ISVREF(icp_socket,(SI_Long)10L);
    if (callback_functions_qm) {
	reclaim_icp_callback_list_1(callback_functions_qm);
	SVREF(icp_socket,FIX((SI_Long)10L)) = Nil;
    }
    return VALUES_1(Nil);
}

/* EXECUTE-ICP-CONNECT-CALLBACKS */
Object execute_icp_connect_callbacks(icp_socket)
    Object icp_socket;
{
    Object callback_functions, callback_function, ab_loop_list_;

    x_note_fn_call(47,73);
    callback_functions = ISVREF(icp_socket,(SI_Long)11L);
    callback_function = Nil;
    ab_loop_list_ = callback_functions;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    callback_function = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    FUNCALL_1(callback_function,icp_socket);
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* REGISTER-ICP-CONNECT-CALLBACK */
Object register_icp_connect_callback(callback_function,icp_socket)
    Object callback_function, icp_socket;
{
    Object icp_callback_push_modify_macro_arg, car_1, cdr_1, svref_new_value;

    x_note_fn_call(47,74);
    icp_callback_push_modify_macro_arg = callback_function;
    car_1 = icp_callback_push_modify_macro_arg;
    cdr_1 = ISVREF(icp_socket,(SI_Long)11L);
    svref_new_value = icp_callback_cons_1(car_1,cdr_1);
    SVREF(icp_socket,FIX((SI_Long)11L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-ICP-CONNECT-CALLBACKS */
Object reclaim_icp_connect_callbacks(callbacks)
    Object callbacks;
{
    x_note_fn_call(47,75);
    reclaim_icp_callback_list_1(callbacks);
    return VALUES_1(Nil);
}

/* DEREGISTER-ALL-ICP-CONNECT-CALLBACKS */
Object deregister_all_icp_connect_callbacks(icp_socket)
    Object icp_socket;
{
    Object callback_functions_qm;

    x_note_fn_call(47,76);
    callback_functions_qm = ISVREF(icp_socket,(SI_Long)11L);
    if (callback_functions_qm) {
	reclaim_icp_callback_list_1(callback_functions_qm);
	SVREF(icp_socket,FIX((SI_Long)11L)) = Nil;
    }
    return VALUES_1(Nil);
}

/* EXECUTE-ICP-ACCEPT-CALLBACKS */
Object execute_icp_accept_callbacks(icp_socket,nascent_socket)
    Object icp_socket, nascent_socket;
{
    Object callback_functions, callback_function, ab_loop_list_;

    x_note_fn_call(47,77);
    callback_functions = ISVREF(icp_socket,(SI_Long)12L);
    callback_function = Nil;
    ab_loop_list_ = callback_functions;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    callback_function = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    FUNCALL_2(callback_function,icp_socket,nascent_socket);
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* REGISTER-ICP-ACCEPT-CALLBACK */
Object register_icp_accept_callback(callback_function,icp_socket)
    Object callback_function, icp_socket;
{
    Object icp_callback_push_modify_macro_arg, car_1, cdr_1, svref_new_value;

    x_note_fn_call(47,78);
    icp_callback_push_modify_macro_arg = callback_function;
    car_1 = icp_callback_push_modify_macro_arg;
    cdr_1 = ISVREF(icp_socket,(SI_Long)12L);
    svref_new_value = icp_callback_cons_1(car_1,cdr_1);
    SVREF(icp_socket,FIX((SI_Long)12L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-ICP-ACCEPT-CALLBACKS */
Object reclaim_icp_accept_callbacks(callbacks)
    Object callbacks;
{
    x_note_fn_call(47,79);
    reclaim_icp_callback_list_1(callbacks);
    return VALUES_1(Nil);
}

/* DEREGISTER-ALL-ICP-ACCEPT-CALLBACKS */
Object deregister_all_icp_accept_callbacks(icp_socket)
    Object icp_socket;
{
    Object callback_functions_qm;

    x_note_fn_call(47,80);
    callback_functions_qm = ISVREF(icp_socket,(SI_Long)12L);
    if (callback_functions_qm) {
	reclaim_icp_callback_list_1(callback_functions_qm);
	SVREF(icp_socket,FIX((SI_Long)12L)) = Nil;
    }
    return VALUES_1(Nil);
}

/* EXECUTE-ICP-READ-CALLBACKS */
Object execute_icp_read_callbacks(icp_socket,readable_qm)
    Object icp_socket, readable_qm;
{
    Object callback_functions, callback_function, ab_loop_list_;

    x_note_fn_call(47,81);
    callback_functions = ISVREF(icp_socket,(SI_Long)14L);
    callback_function = Nil;
    ab_loop_list_ = callback_functions;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    callback_function = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    FUNCALL_2(callback_function,icp_socket,readable_qm);
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* REGISTER-ICP-READ-CALLBACK */
Object register_icp_read_callback(callback_function,icp_socket)
    Object callback_function, icp_socket;
{
    Object icp_callback_push_modify_macro_arg, car_1, cdr_1, svref_new_value;

    x_note_fn_call(47,82);
    icp_callback_push_modify_macro_arg = callback_function;
    car_1 = icp_callback_push_modify_macro_arg;
    cdr_1 = ISVREF(icp_socket,(SI_Long)14L);
    svref_new_value = icp_callback_cons_1(car_1,cdr_1);
    SVREF(icp_socket,FIX((SI_Long)14L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-ICP-READ-CALLBACKS */
Object reclaim_icp_read_callbacks(callbacks)
    Object callbacks;
{
    x_note_fn_call(47,83);
    reclaim_icp_callback_list_1(callbacks);
    return VALUES_1(Nil);
}

/* DEREGISTER-ALL-ICP-READ-CALLBACKS */
Object deregister_all_icp_read_callbacks(icp_socket)
    Object icp_socket;
{
    Object callback_functions_qm;

    x_note_fn_call(47,84);
    callback_functions_qm = ISVREF(icp_socket,(SI_Long)14L);
    if (callback_functions_qm) {
	reclaim_icp_callback_list_1(callback_functions_qm);
	SVREF(icp_socket,FIX((SI_Long)14L)) = Nil;
    }
    return VALUES_1(Nil);
}

/* EXECUTE-ICP-WRITE-CALLBACKS */
Object execute_icp_write_callbacks(icp_socket,writable_qm)
    Object icp_socket, writable_qm;
{
    Object callback_functions, callback_function, ab_loop_list_;

    x_note_fn_call(47,85);
    callback_functions = ISVREF(icp_socket,(SI_Long)13L);
    callback_function = Nil;
    ab_loop_list_ = callback_functions;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    callback_function = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    FUNCALL_2(callback_function,icp_socket,writable_qm);
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* REGISTER-ICP-WRITE-CALLBACK */
Object register_icp_write_callback(callback_function,icp_socket)
    Object callback_function, icp_socket;
{
    Object icp_callback_push_modify_macro_arg, car_1, cdr_1, svref_new_value;

    x_note_fn_call(47,86);
    icp_callback_push_modify_macro_arg = callback_function;
    car_1 = icp_callback_push_modify_macro_arg;
    cdr_1 = ISVREF(icp_socket,(SI_Long)13L);
    svref_new_value = icp_callback_cons_1(car_1,cdr_1);
    SVREF(icp_socket,FIX((SI_Long)13L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-ICP-WRITE-CALLBACKS */
Object reclaim_icp_write_callbacks(callbacks)
    Object callbacks;
{
    x_note_fn_call(47,87);
    reclaim_icp_callback_list_1(callbacks);
    return VALUES_1(Nil);
}

/* DEREGISTER-ALL-ICP-WRITE-CALLBACKS */
Object deregister_all_icp_write_callbacks(icp_socket)
    Object icp_socket;
{
    Object callback_functions_qm;

    x_note_fn_call(47,88);
    callback_functions_qm = ISVREF(icp_socket,(SI_Long)13L);
    if (callback_functions_qm) {
	reclaim_icp_callback_list_1(callback_functions_qm);
	SVREF(icp_socket,FIX((SI_Long)13L)) = Nil;
    }
    return VALUES_1(Nil);
}

/* NOT-A-LISTENER-P */
Object not_a_listener_p(icp_socket)
    Object icp_socket;
{
    Object temp;

    x_note_fn_call(47,89);
    temp = FIXNUM_NE(ISVREF(icp_socket,(SI_Long)15L),Icp_socket_listening) 
	    ? T : Nil;
    return VALUES_1(temp);
}

static Object array_constant;      /* # */

static Object array_constant_1;    /* # */

/* TWRITE-ICP-SOCKET-CONNECTION-NAME */
Object twrite_icp_socket_connection_name(icp_socket)
    Object icp_socket;
{
    Object name, accept_pos, pos, remote_name, char_1, code;
    Object simple_or_wide_character, thing, temp, schar_arg_2, schar_new_value;
    SI_Long limit1, length_1, name_length, i, ab_loop_bind_, thing_1;

    x_note_fn_call(47,90);
    name = stringw(ISVREF(icp_socket,(SI_Long)2L));
    limit1 = (SI_Long)8L;
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(name));
    name_length = UBYTE_16_ISAREF_1(name,length_1 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(name,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L);
    accept_pos = limit1 < name_length ? search(4,array_constant,name,Kend1,
	    FIX(limit1)) : Nil;
    pos = accept_pos;
    if (pos);
    else
	pos = search(4,array_constant_1,name,Kend1,FIX((SI_Long)1L));
    if (pos);
    else
	pos = FIX(name_length);
    remote_name = accept_pos ? get_remote_host_name(icp_socket) : Nil;
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(pos);
    char_1 = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    char_1 = FIX(UBYTE_16_ISAREF_1(name,i));
    if ( !(IFIX(char_1) == (SI_Long)95L)) {
	code = char_1;
	if (IFIX(code) < (SI_Long)127L)
	    simple_or_wide_character = (SI_Long)97L <= IFIX(code) && 
		    IFIX(code) <= (SI_Long)122L ? FIX(IFIX(code) + 
		    (SI_Long)-32L) : code;
	else {
	    simple_or_wide_character = unicode_uppercase_if_lowercase(code);
	    if (simple_or_wide_character);
	    else
		simple_or_wide_character = code;
	}
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = simple_or_wide_character;
	    twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) : 
		    thing);
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = simple_or_wide_character;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp;
	}
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    if (remote_name) {
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing_1 = (SI_Long)58L;
	    twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
		    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing_1 = (SI_Long)58L;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing_1)) ? 
		    CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp;
	}
	twrite_general_string(remote_name);
    }
    else {
	i = IFIX(pos);
	ab_loop_bind_ = name_length;
	char_1 = Nil;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop_1;
	char_1 = FIX(UBYTE_16_ISAREF_1(name,i));
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = char_1;
	    twrite_wide_character(CHARACTERP(thing) ? CHAR_CODE(thing) : 
		    thing);
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = char_1;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp;
	}
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
    }
    return VALUES_1(Nil);
}

static Object string_constant_8;   /* "ICP-SOCKET " */

static Object list_constant_2;     /* # */

static Object list_constant_3;     /* # */

static Object string_constant_9;   /* " in state ~D (~a)" */

/* ICP-SOCKET-DESCRIPTION */
Object icp_socket_description(icp_socket)
    Object icp_socket;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, icp_socket_state, temp_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(47,91);
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
	      tformat(1,string_constant_8);
	      twrite_icp_socket_connection_name(icp_socket);
	      temp = ISVREF(icp_socket,(SI_Long)15L);
	      icp_socket_state = ISVREF(icp_socket,(SI_Long)15L);
	      temp_1 = assq_function(icp_socket_state,list_constant_2);
	      if (temp_1);
	      else
		  temp_1 = list_constant_3;
	      tformat(3,string_constant_9,temp,SECOND(temp_1));
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* RECLAIM-GSI-EXTENSION-DATA-FOR-GSI */
Object reclaim_gsi_extension_data_for_gsi(extension_data)
    Object extension_data;
{
    x_note_fn_call(47,92);
    return VALUES_1(Nil);
}

Object The_type_description_of_i_am_alive_info = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_i_am_alive_infos, Qchain_of_available_i_am_alive_infos);

DEFINE_VARIABLE_WITH_SYMBOL(I_am_alive_info_count, Qi_am_alive_info_count);

Object Chain_of_available_i_am_alive_infos_vector = UNBOUND;

/* I-AM-ALIVE-INFO-STRUCTURE-MEMORY-USAGE */
Object i_am_alive_info_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(47,93);
    temp = I_am_alive_info_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)18L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-I-AM-ALIVE-INFO-COUNT */
Object outstanding_i_am_alive_info_count()
{
    Object def_structure_i_am_alive_info_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(47,94);
    gensymed_symbol = IFIX(I_am_alive_info_count);
    def_structure_i_am_alive_info_variable = 
	    Chain_of_available_i_am_alive_infos;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_i_am_alive_info_variable))
	goto end_loop;
    def_structure_i_am_alive_info_variable = 
	    ISVREF(def_structure_i_am_alive_info_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-I-AM-ALIVE-INFO-1 */
Object reclaim_i_am_alive_info_1(i_am_alive_info)
    Object i_am_alive_info;
{
    Object structure_being_reclaimed, gensymed_symbol, temp, svref_arg_2;
    Declare_special(2);

    x_note_fn_call(47,95);
    inline_note_reclaim_cons(i_am_alive_info,Nil);
    structure_being_reclaimed = i_am_alive_info;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    1);
      reclaim_things_to_update_when_unclogged_qm(ISVREF(i_am_alive_info,
	      (SI_Long)11L));
      SVREF(i_am_alive_info,FIX((SI_Long)11L)) = Nil;
      reclaim_icp_tree_1(ISVREF(i_am_alive_info,(SI_Long)12L));
      SVREF(i_am_alive_info,FIX((SI_Long)12L)) = Nil;
      gensymed_symbol = Nil;
    next_loop:
      gensymed_symbol = ISVREF(i_am_alive_info,(SI_Long)17L);
      if (CAS_SVREF(i_am_alive_info,(SI_Long)17L,gensymed_symbol,Nil)) {
	  if (gensymed_symbol) {
	      if (EQ(gensymed_symbol,Current_schedule_task))
		  Current_schedule_task = Nil;
	      if (ISVREF(gensymed_symbol,(SI_Long)6L))
		  cancel_and_reclaim_scheduled_queue_element_1(gensymed_symbol);
	      inline_note_reclaim_cons(gensymed_symbol,Nil);
	      structure_being_reclaimed = gensymed_symbol;
	      PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		      0);
		reclaim_schedule_task_args(ISVREF(gensymed_symbol,
			(SI_Long)9L));
		SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Nil;
	      POP_SPECIAL();
	      temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		      IFIX(Current_thread_index));
	      SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp;
	      temp = Chain_of_available_schedule_tasks_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = gensymed_symbol;
	  }
	  goto end_1;
      }
      goto next_loop;
    end_loop:
    end_1:;
      SVREF(i_am_alive_info,FIX((SI_Long)17L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_i_am_alive_infos_vector,
	    IFIX(Current_thread_index));
    SVREF(i_am_alive_info,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_i_am_alive_infos_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = i_am_alive_info;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-I-AM-ALIVE-INFO */
Object reclaim_structure_for_i_am_alive_info(i_am_alive_info)
    Object i_am_alive_info;
{
    x_note_fn_call(47,96);
    return reclaim_i_am_alive_info_1(i_am_alive_info);
}

static Object Qg2_defstruct_structure_name_i_am_alive_info_g2_struct;  /* g2-defstruct-structure-name::i-am-alive-info-g2-struct */

/* MAKE-PERMANENT-I-AM-ALIVE-INFO-STRUCTURE-INTERNAL */
Object make_permanent_i_am_alive_info_structure_internal()
{
    Object def_structure_i_am_alive_info_variable;
    Object defstruct_g2_i_am_alive_info_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(47,97);
    def_structure_i_am_alive_info_variable = Nil;
    atomic_incff_symval(Qi_am_alive_info_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_i_am_alive_info_variable = Nil;
	gensymed_symbol = (SI_Long)18L;
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
	defstruct_g2_i_am_alive_info_variable = the_array;
	SVREF(defstruct_g2_i_am_alive_info_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_i_am_alive_info_g2_struct;
	def_structure_i_am_alive_info_variable = 
		defstruct_g2_i_am_alive_info_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_i_am_alive_info_variable);
}

/* MAKE-I-AM-ALIVE-INFO-1 */
Object make_i_am_alive_info_1()
{
    Object def_structure_i_am_alive_info_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(47,98);
    def_structure_i_am_alive_info_variable = 
	    ISVREF(Chain_of_available_i_am_alive_infos_vector,
	    IFIX(Current_thread_index));
    if (def_structure_i_am_alive_info_variable) {
	svref_arg_1 = Chain_of_available_i_am_alive_infos_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_i_am_alive_info_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_i_am_alive_info_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_i_am_alive_info_g2_struct;
    }
    else
	def_structure_i_am_alive_info_variable = 
		make_permanent_i_am_alive_info_structure_internal();
    inline_note_allocate_cons(def_structure_i_am_alive_info_variable,Nil);
    SVREF(def_structure_i_am_alive_info_variable,FIX((SI_Long)1L)) = T;
    SVREF(def_structure_i_am_alive_info_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_i_am_alive_info_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_i_am_alive_info_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_i_am_alive_info_variable,FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_i_am_alive_info_variable,FIX((SI_Long)15L)) = Nil;
    ISVREF(def_structure_i_am_alive_info_variable,(SI_Long)16L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_i_am_alive_info_variable,FIX((SI_Long)17L)) = Nil;
    return VALUES_1(def_structure_i_am_alive_info_variable);
}

/* RECLAIM-I-AM-ALIVE-INFO? */
Object reclaim_i_am_alive_info_qm(i_am_alive_info_qm)
    Object i_am_alive_info_qm;
{
    x_note_fn_call(47,99);
    if (i_am_alive_info_qm)
	return reclaim_i_am_alive_info_1(i_am_alive_info_qm);
    else
	return VALUES_1(Nil);
}

/* RECLAIM-THINGS-TO-UPDATE-WHEN-UNCLOGGED? */
Object reclaim_things_to_update_when_unclogged_qm(things_to_update_when_unclogged_qm)
    Object things_to_update_when_unclogged_qm;
{
    x_note_fn_call(47,100);
    return reclaim_gensym_list_1(things_to_update_when_unclogged_qm);
}

DEFINE_VARIABLE_WITH_SYMBOL(Highest_icp_socket_session_id, Qhighest_icp_socket_session_id);

static Object Qtemporary_output;   /* temporary-output */

static Object Qinput;              /* input */

static Object Qoutput;             /* output */

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qicp_connection_timeout_task_1;  /* icp-connection-timeout-task-1 */

/* MAKE-ICP-SOCKET */
Object make_icp_socket(icp_connection_name,type_of_icp_connection,
	    icp_connection_input_handle,icp_connection_output_handle_qm,
	    receive_while_handling_icp_input_qm,
	    transmit_while_writing_icp_qm,icp_connection_open_p_1,
	    parent_listener_qm,local_system_name,connect_timeout)
    Object icp_connection_name, type_of_icp_connection;
    Object icp_connection_input_handle, icp_connection_output_handle_qm;
    Object receive_while_handling_icp_input_qm, transmit_while_writing_icp_qm;
    Object icp_connection_open_p_1, parent_listener_qm, local_system_name;
    Object connect_timeout;
{
    Object icp_connection_state, icp_socket, temp, old, new_1;
    Object def_structure_schedule_task_variable, svref_arg_2, svref_new_value;
    Object task, ctask, p, v, q, structure_being_reclaimed;
    char g2_p;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(47,101);
    icp_connection_state = icp_connection_open_p_1 ? 
	    Icp_connection_running : Icp_connection_closed;
    icp_socket = make_icp_socket_structure_1(type_of_icp_connection,
	    icp_connection_name,icp_connection_state,parent_listener_qm,
	    local_system_name);
    temp =  !EQ(type_of_icp_connection,Qtemporary_output) ? 
	    make_icp_port(icp_connection_input_handle,icp_socket,Qinput,
	    receive_while_handling_icp_input_qm) : Nil;
    SVREF(icp_socket,FIX((SI_Long)3L)) = temp;
    temp = icp_connection_output_handle_qm || EQ(type_of_icp_connection,
	    Qtemporary_output) ? 
	    make_icp_port(icp_connection_output_handle_qm,icp_socket,
	    Qoutput,transmit_while_writing_icp_qm) : Nil;
    SVREF(icp_socket,FIX((SI_Long)4L)) = temp;
    temp = FIXNUM_ADD1(Highest_icp_socket_session_id);
    Highest_icp_socket_session_id = temp;
    temp = Highest_icp_socket_session_id;
    SVREF(icp_socket,FIX((SI_Long)40L)) = temp;
    if (FIXNUMP(connect_timeout)) {
	old = Nil;
	new_1 = Nil;
      next_loop:
	old = ISVREF(icp_socket,(SI_Long)16L);
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
	aref_new_value = -1.0;
	DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	SVREF(task,FIX((SI_Long)4L)) = Lowest_system_priority;
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)10L)) = Nil;
	g2_p =  !TRUEP(T);
	SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
		Current_real_time,(SI_Long)0L);
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	SVREF(task,FIX((SI_Long)7L)) = Qicp_connection_timeout_task_1;
	temp = SYMBOL_FUNCTION(Qicp_connection_timeout_task_1);
	SVREF(task,FIX((SI_Long)8L)) = temp;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)2L);
	SVREF(task,FIX((SI_Long)13L)) = icp_socket;
	SVREF(task,FIX((SI_Long)14L)) = connect_timeout;
	new_1 = task;
	if (CAS_SVREF(icp_socket,(SI_Long)16L,old,new_1)) {
	    task = new_1;
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
	goto next_loop;
      end_loop:
      end_1:;
    }
    return VALUES_1(icp_socket);
}

static Object Qicp_connection_timeout_task_2;  /* icp-connection-timeout-task-2 */

/* ICP-CONNECTION-TIMEOUT-TASK-1 */
Object icp_connection_timeout_task_1(icp_socket,connect_timeout)
    Object icp_socket, connect_timeout;
{
    Object gensymed_symbol, structure_being_reclaimed, temp, svref_arg_2, old;
    Object new_1, def_structure_schedule_task_variable, svref_new_value, task;
    char svref_new_value_1;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(47,102);
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = ISVREF(icp_socket,(SI_Long)16L);
    if (CAS_SVREF(icp_socket,(SI_Long)16L,gensymed_symbol,Nil)) {
	if (gensymed_symbol) {
	    if (EQ(gensymed_symbol,Current_schedule_task))
		Current_schedule_task = Nil;
	    if (ISVREF(gensymed_symbol,(SI_Long)6L))
		cancel_and_reclaim_scheduled_queue_element_1(gensymed_symbol);
	    inline_note_reclaim_cons(gensymed_symbol,Nil);
	    structure_being_reclaimed = gensymed_symbol;
	    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		    0);
	      reclaim_schedule_task_args(ISVREF(gensymed_symbol,(SI_Long)9L));
	      SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Nil;
	    POP_SPECIAL();
	    temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp;
	    temp = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = gensymed_symbol;
	}
	goto end_1;
    }
    goto next_loop;
  end_loop:
  end_1:;
    old = Nil;
    new_1 = Nil;
  next_loop_1:
    old = ISVREF(icp_socket,(SI_Long)16L);
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
    aref_new_value = DFLOAT_ISAREF_1(Current_real_time,(SI_Long)0L) + 
	    (double)IFIX(connect_timeout);
    DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
    temp = ISVREF(task,(SI_Long)1L);
    aref_new_value = -1.0;
    DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
    svref_new_value_1 =  !TRUEP(T);
    SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
    SVREF(task,FIX((SI_Long)4L)) = Lowest_system_priority;
    SVREF(task,FIX((SI_Long)5L)) = Nil;
    SVREF(task,FIX((SI_Long)9L)) = Nil;
    SVREF(task,FIX((SI_Long)10L)) = Nil;
    SVREF(task,FIX((SI_Long)7L)) = Qicp_connection_timeout_task_2;
    temp = SYMBOL_FUNCTION(Qicp_connection_timeout_task_2);
    SVREF(task,FIX((SI_Long)8L)) = temp;
    ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
    SVREF(task,FIX((SI_Long)13L)) = icp_socket;
    new_1 = task;
    if (CAS_SVREF(icp_socket,(SI_Long)16L,old,new_1)) {
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
	goto end_2;
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
  end_2:;
    return VALUES_1(Nil);
}

static Object Qconnection_attempt_timed_out;  /* connection-attempt-timed-out */

/* ICP-CONNECTION-TIMEOUT-TASK-2 */
Object icp_connection_timeout_task_2(icp_socket)
    Object icp_socket;
{
    Object gensymed_symbol, structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(47,103);
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = ISVREF(icp_socket,(SI_Long)16L);
    if (CAS_SVREF(icp_socket,(SI_Long)16L,gensymed_symbol,Nil)) {
	if (gensymed_symbol) {
	    if (EQ(gensymed_symbol,Current_schedule_task))
		Current_schedule_task = Nil;
	    if (ISVREF(gensymed_symbol,(SI_Long)6L))
		cancel_and_reclaim_scheduled_queue_element_1(gensymed_symbol);
	    inline_note_reclaim_cons(gensymed_symbol,Nil);
	    structure_being_reclaimed = gensymed_symbol;
	    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		    0);
	      reclaim_schedule_task_args(ISVREF(gensymed_symbol,(SI_Long)9L));
	      SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Nil;
	    POP_SPECIAL();
	    temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp;
	    temp = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = gensymed_symbol;
	}
	goto end_1;
    }
    goto next_loop;
  end_loop:
  end_1:;
    shutdown_icp_socket_connection(2,icp_socket,Qconnection_attempt_timed_out);
    return VALUES_1(Nil);
}

/* ICP-CONNECTION-OPEN-P */
Object icp_connection_open_p(icp_socket_structure)
    Object icp_socket_structure;
{
    Object icp_connection_state, temp;

    x_note_fn_call(47,104);
    icp_connection_state = ISVREF(icp_socket_structure,(SI_Long)15L);
    temp =  !(FIXNUM_EQ(icp_connection_state,Icp_connection_closed) || 
	    FIXNUM_EQ(icp_connection_state,
	    Icp_connection_awaiting_acknowledgement) || 
	    FIXNUM_EQ(icp_connection_state,
	    Icp_connection_connect_in_progress)) ? T : Nil;
    return VALUES_1(temp);
}

/* ICP-CONNECTION-IN-PROGRESS-P */
Object icp_connection_in_progress_p(icp_socket_structure)
    Object icp_socket_structure;
{
    Object icp_connection_state, temp;

    x_note_fn_call(47,105);
    icp_connection_state = ISVREF(icp_socket_structure,(SI_Long)15L);
    temp = FIXNUM_EQ(icp_connection_state,
	    Icp_connection_connect_in_progress) ? T : Nil;
    return VALUES_1(temp);
}

/* ICP-CONNECTION-BEING-SHUTDOWN? */
Object icp_connection_being_shutdown_qm(icp_socket_structure)
    Object icp_socket_structure;
{
    Object connection_state, temp;

    x_note_fn_call(47,106);
    connection_state = ISVREF(icp_socket_structure,(SI_Long)15L);
    temp = FIXNUM_EQ(connection_state,
	    Icp_connection_awaiting_acknowledgement) ? T : Nil;
    if (temp);
    else
	temp = FIXNUM_EQ(connection_state,
		Icp_connection_shutdown_acknowledgement_rundown) ? T : Nil;
    return VALUES_1(temp);
}

/* ICP-CONNECTION-CAN-PROCESS-MESSAGES? */
Object icp_connection_can_process_messages_qm(icp_socket_structure)
    Object icp_socket_structure;
{
    Object connection_state, temp;

    x_note_fn_call(47,107);
    connection_state = ISVREF(icp_socket_structure,(SI_Long)15L);
    temp = FIXNUM_EQ(connection_state,Icp_connection_running) ? T : Nil;
    if (temp);
    else
	temp = FIXNUM_EQ(connection_state,
		Icp_connection_awaiting_acknowledgement) ? T : Nil;
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_frame_serial_number_to_item_table_hash_vector_67_vectors, Qavailable_frame_serial_number_to_item_table_hash_vector_67_vectors);

DEFINE_VARIABLE_WITH_SYMBOL(Count_of_frame_serial_number_to_item_table_hash_vector_67_vectors, Qcount_of_frame_serial_number_to_item_table_hash_vector_67_vectors);

Object Available_frame_serial_number_to_item_table_hash_vector_67_vectors_vector = UNBOUND;

/* FRAME-SERIAL-NUMBER-TO-ITEM-TABLE-HASH-VECTOR-67-VECTOR-MEMORY-USAGE */
Object frame_serial_number_to_item_table_hash_vector_67_vector_memory_usage()
{
    Object temp;

    x_note_fn_call(47,108);
    temp = Count_of_frame_serial_number_to_item_table_hash_vector_67_vectors;
    temp = FIXNUM_TIMES(temp,bytes_per_typed_simple_array(T,
	    FIX((SI_Long)67L)));
    return VALUES_1(temp);
}

/* OUT-FRAME-SERIAL-NUMBER-TO-ITEM-TABLE-HASH-VECTOR-67-VECTORS */
Object out_frame_serial_number_to_item_table_hash_vector_67_vectors()
{
    Object temp;

    x_note_fn_call(47,109);
    temp = 
	    FIXNUM_MINUS(Count_of_frame_serial_number_to_item_table_hash_vector_67_vectors,
	    length(Available_frame_serial_number_to_item_table_hash_vector_67_vectors));
    return VALUES_1(temp);
}

/* MAKE-PERMANENT-FRAME-SERIAL-NUMBER-TO-ITEM-TABLE-HASH-VECTOR-67-VECTOR-INTERNAL */
Object make_permanent_frame_serial_number_to_item_table_hash_vector_67_vector_internal()
{
    Object temp;
    XDeclare_area(1);

    x_note_fn_call(47,110);
    atomic_incff_symval(Qcount_of_frame_serial_number_to_item_table_hash_vector_67_vectors,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0))
	temp = make_array(3,FIX((SI_Long)67L),Kinitial_element,Nil);
    POP_AREA(0);
    return VALUES_1(temp);
}

static Object Qvector_pool;        /* vector-pool */

/* MAKE-FRAME-SERIAL-NUMBER-TO-ITEM-TABLE-HASH-VECTOR */
Object make_frame_serial_number_to_item_table_hash_vector()
{
    Object temp, svref_arg_1, svref_arg_2, temp_1, vector_pool_cons, temp_2;
    Object svref_arg_2_1;

    x_note_fn_call(47,111);
    if (ISVREF(Available_frame_serial_number_to_item_table_hash_vector_67_vectors_vector,
	    IFIX(Current_thread_index))) {
	temp = 
		M_CAR(ISVREF(Available_frame_serial_number_to_item_table_hash_vector_67_vectors_vector,
		IFIX(Current_thread_index)));
	svref_arg_1 = 
		Available_frame_serial_number_to_item_table_hash_vector_67_vectors_vector;
	svref_arg_2 = Current_thread_index;
	temp_1 = 
		M_CDR(ISVREF(Available_frame_serial_number_to_item_table_hash_vector_67_vectors_vector,
		IFIX(Current_thread_index)));
	vector_pool_cons = 
		ISVREF(Available_frame_serial_number_to_item_table_hash_vector_67_vectors_vector,
		IFIX(Current_thread_index));
	inline_note_reclaim_cons(vector_pool_cons,Qvector_pool);
	if (ISVREF(Available_vector_pool_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_2 = ISVREF(Available_vector_pool_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_2) = vector_pool_cons;
	    temp_2 = Available_vector_pool_conses_tail_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2_1) = vector_pool_cons;
	}
	else {
	    temp_2 = Available_vector_pool_conses_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2_1) = vector_pool_cons;
	    temp_2 = Available_vector_pool_conses_tail_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2_1) = vector_pool_cons;
	}
	M_CDR(vector_pool_cons) = Nil;
	SVREF(svref_arg_1,svref_arg_2) = temp_1;
    }
    else
	temp = 
		make_permanent_frame_serial_number_to_item_table_hash_vector_67_vector_internal();
    return VALUES_1(temp);
}

/* RECLAIM-FRAME-SERIAL-NUMBER-TO-ITEM-TABLE-HASH-VECTOR */
Object reclaim_frame_serial_number_to_item_table_hash_vector(frame_serial_number_to_item_table_hash_vector_67_vector)
    Object frame_serial_number_to_item_table_hash_vector_67_vector;
{
    Object svref_arg_1, svref_arg_2, new_cons, temp, svref_arg_2_1;
    Object svref_new_value, gensymed_symbol;

    x_note_fn_call(47,112);
    svref_arg_1 = 
	    Available_frame_serial_number_to_item_table_hash_vector_67_vectors_vector;
    svref_arg_2 = Current_thread_index;
    new_cons = ISVREF(Available_vector_pool_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp = Available_vector_pool_conses_vector;
	svref_arg_2_1 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp,svref_arg_2_1) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_vector_pool_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp = Available_vector_pool_conses_tail_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp,svref_arg_2_1) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_vector_pool_cons_pool();
    M_CAR(gensymed_symbol) = 
	    frame_serial_number_to_item_table_hash_vector_67_vector;
    temp = 
	    ISVREF(Available_frame_serial_number_to_item_table_hash_vector_67_vectors_vector,
	    IFIX(Current_thread_index));
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qvector_pool);
    SVREF(svref_arg_1,svref_arg_2) = gensymed_symbol;
    return VALUES_1(Nil);
}

static Object Qsentinel_node;      /* sentinel-node */

static Object Qhead;               /* head */

static Object Qtail;               /* tail */

/* MAKE-FRAME-SERIAL-NUMBER-TO-ITEM-TABLE-TREE-FOR-HASH-SKIP-LIST-SENTINEL */
Object make_frame_serial_number_to_item_table_tree_for_hash_skip_list_sentinel(hash,
	    tail)
    Object hash, tail;
{
    Object node, next, svref_new_value;
    SI_Long i;

    x_note_fn_call(47,113);
    node = make_skip_list_element_1(hash,Qsentinel_node,tail ? Qhead : 
	    Qtail,FIX((SI_Long)31L));
    next = allocate_managed_simple_vector_for_skip_list(FIX((SI_Long)32L));
    i = (SI_Long)0L;
  next_loop:
    if (i > (SI_Long)31L)
	goto end_loop;
    svref_new_value = MAKE_ATOMIC_REF(tail,(SI_Long)0L);
    ISVREF(next,i) = svref_new_value;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    SVREF(node,FIX((SI_Long)0L)) = next;
    return VALUES_1(node);
}

/* MUTATE-FRAME-SERIAL-NUMBER-TO-ITEM-TABLE-TREE-FOR-HASH-SKIP-LIST-ENTRY */
Object mutate_frame_serial_number_to_item_table_tree_for_hash_skip_list_entry(node,
	    new_key,new_entry)
    Object node, new_key, new_entry;
{
    x_note_fn_call(47,114);
    note_item_deleted_from_frame_serial_number_table(ISVREF(node,(SI_Long)3L));
    SVREF(node,FIX((SI_Long)2L)) = new_key;
    SVREF(node,FIX((SI_Long)3L)) = new_entry;
    return VALUES_1(Nil);
}

Object Fp_mutate_frame_serial_number_to_item_table_tree_for_hash_skip_list_entry = UNBOUND;

/* CLEAR-FRAME-SERIAL-NUMBER-TO-ITEM-TABLE-TREE */
Object clear_frame_serial_number_to_item_table_tree(frame_serial_number_to_item_table_tree_for_hash_skip_list)
    Object frame_serial_number_to_item_table_tree_for_hash_skip_list;
{
    Object head, tail, element_qm, key_qm, temp, old_entry;
    Object result;

    x_note_fn_call(47,115);
    head = 
	    M_CAR(M_CDR(frame_serial_number_to_item_table_tree_for_hash_skip_list));
    tail = 
	    M_CDR(M_CDR(frame_serial_number_to_item_table_tree_for_hash_skip_list));
    element_qm = Nil;
    key_qm = Nil;
  next_loop:
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    key_qm = ISVREF(element_qm,(SI_Long)2L);
    if ( ! !EQ(element_qm,tail))
	goto end_loop;
    temp = key_qm;
    result = delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),temp,
	    frame_serial_number_to_item_table_tree_for_hash_skip_list,
	    FIX((SI_Long)31L),sxhashw(key_qm));
    old_entry = NTH_VALUE((SI_Long)1L, result);
    if (old_entry)
	note_item_deleted_from_frame_serial_number_table(old_entry);
    goto next_loop;
  end_loop:;
    return VALUES_1(frame_serial_number_to_item_table_tree_for_hash_skip_list);
}

static Object Qframe_serial_number_to_item_table_tree_for_hash;  /* frame-serial-number-to-item-table-tree-for-hash */

static Object Qlookup;             /* lookup */

/* MAKE-FRAME-SERIAL-NUMBER-TO-ITEM-TABLE */
Object make_frame_serial_number_to_item_table()
{
    Object new_vector, tail, head, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol, gensymed_symbol_1, temp;
    SI_Long index_1;

    x_note_fn_call(47,116);
    new_vector = make_frame_serial_number_to_item_table_hash_vector();
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)67L)
	goto end_loop;
    tail = 
	    make_frame_serial_number_to_item_table_tree_for_hash_skip_list_sentinel(Most_positive_fixnum,
	    Nil);
    head = 
	    make_frame_serial_number_to_item_table_tree_for_hash_skip_list_sentinel(Most_negative_fixnum,
	    tail);
    new_cons = ISVREF(Available_lookup_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_lookup_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_lookup_cons_pool();
    M_CAR(gensymed_symbol) = Qframe_serial_number_to_item_table_tree_for_hash;
    new_cons = ISVREF(Available_lookup_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_lookup_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol_1 = new_cons;
    }
    else
	gensymed_symbol_1 = Nil;
    if ( !TRUEP(gensymed_symbol_1))
	gensymed_symbol_1 = replenish_lookup_cons_pool();
    M_CAR(gensymed_symbol_1) = head;
    M_CDR(gensymed_symbol_1) = tail;
    inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
    M_CDR(gensymed_symbol) = gensymed_symbol_1;
    inline_note_allocate_cons(gensymed_symbol,Qlookup);
    ISVREF(new_vector,index_1) = gensymed_symbol;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = new_vector;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* FLATTEN-FRAME-SERIAL-NUMBER-TO-ITEM-TABLE */
Object flatten_frame_serial_number_to_item_table(frame_serial_number_to_item_table_hash_table)
    Object frame_serial_number_to_item_table_hash_table;
{
    Object result_1, subtree, temp;
    SI_Long index_1;

    x_note_fn_call(47,117);
    result_1 = Nil;
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)67L)
	goto end_loop;
    subtree = ISVREF(frame_serial_number_to_item_table_hash_table,index_1);
    if (subtree) {
	temp = flatten_skip_list(CDR(subtree));
	result_1 = nconc2(temp,result_1);
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(result_1);
}

/* CLEAR-FRAME-SERIAL-NUMBER-TO-ITEM-TABLE */
Object clear_frame_serial_number_to_item_table(frame_serial_number_to_item_table_hash_table)
    Object frame_serial_number_to_item_table_hash_table;
{
    SI_Long index_1;

    x_note_fn_call(47,118);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)67L)
	goto end_loop;
    clear_frame_serial_number_to_item_table_tree(ISVREF(frame_serial_number_to_item_table_hash_table,
	    index_1));
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* RECLAIM-FRAME-SERIAL-NUMBER-TO-ITEM-TABLE */
Object reclaim_frame_serial_number_to_item_table(frame_serial_number_to_item_table_hash_table)
    Object frame_serial_number_to_item_table_hash_table;
{
    Object frame_serial_number_to_item_table_tree_for_hash_skip_list, head;
    Object tail, element_qm, key_qm, temp, old_entry, last_1, next_qm, temp_1;
    Object svref_arg_2;
    SI_Long index_1;
    Object result;

    x_note_fn_call(47,119);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)67L)
	goto end_loop;
    frame_serial_number_to_item_table_tree_for_hash_skip_list = 
	    ISVREF(frame_serial_number_to_item_table_hash_table,index_1);
    head = 
	    M_CAR(M_CDR(frame_serial_number_to_item_table_tree_for_hash_skip_list));
    tail = 
	    M_CDR(M_CDR(frame_serial_number_to_item_table_tree_for_hash_skip_list));
    element_qm = Nil;
    key_qm = Nil;
  next_loop_1:
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    key_qm = ISVREF(element_qm,(SI_Long)2L);
    if ( ! !EQ(element_qm,tail))
	goto end_loop_1;
    temp = key_qm;
    result = delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),temp,
	    frame_serial_number_to_item_table_tree_for_hash_skip_list,
	    FIX((SI_Long)31L),sxhashw(key_qm));
    old_entry = NTH_VALUE((SI_Long)1L, result);
    if (old_entry)
	note_item_deleted_from_frame_serial_number_table(old_entry);
    goto next_loop_1;
  end_loop_1:
    reclaim_skip_list_element(head);
    reclaim_skip_list_element(tail);
    M_CDDR(frame_serial_number_to_item_table_tree_for_hash_skip_list) = Nil;
    M_CADR(frame_serial_number_to_item_table_tree_for_hash_skip_list) = Nil;
    M_CAR(frame_serial_number_to_item_table_tree_for_hash_skip_list) = Nil;
    if (frame_serial_number_to_item_table_tree_for_hash_skip_list) {
	last_1 = frame_serial_number_to_item_table_tree_for_hash_skip_list;
	next_qm = Nil;
      next_loop_2:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop_2;
	inline_note_reclaim_cons(last_1,Qlookup);
	last_1 = next_qm;
	goto next_loop_2;
      end_loop_2:
	inline_note_reclaim_cons(last_1,Qlookup);
	if (ISVREF(Available_lookup_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_1 = ISVREF(Available_lookup_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_1) = 
		    frame_serial_number_to_item_table_tree_for_hash_skip_list;
	    temp_1 = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = last_1;
	}
	else {
	    temp_1 = Available_lookup_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = 
		    frame_serial_number_to_item_table_tree_for_hash_skip_list;
	    temp_1 = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    ISVREF(frame_serial_number_to_item_table_hash_table,index_1) = Nil;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    temp = 
	    reclaim_frame_serial_number_to_item_table_hash_vector(frame_serial_number_to_item_table_hash_table);
    return VALUES_1(temp);
}

/* RECLAIM-IF-FRAME-SERIAL-NUMBER-TO-ITEM-TABLE */
Object reclaim_if_frame_serial_number_to_item_table(table_qm)
    Object table_qm;
{
    x_note_fn_call(47,120);
    if (table_qm)
	reclaim_frame_serial_number_to_item_table(table_qm);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_variable_fill_icp_buffer_4096_vectors, Qavailable_variable_fill_icp_buffer_4096_vectors);

DEFINE_VARIABLE_WITH_SYMBOL(Count_of_variable_fill_icp_buffer_4096_vectors, Qcount_of_variable_fill_icp_buffer_4096_vectors);

Object Available_variable_fill_icp_buffer_4096_vectors_vector = UNBOUND;

static Object list_constant_4;     /* # */

/* VARIABLE-FILL-ICP-BUFFER-4096-VECTOR-MEMORY-USAGE */
Object variable_fill_icp_buffer_4096_vector_memory_usage()
{
    Object temp;

    x_note_fn_call(47,121);
    temp = Count_of_variable_fill_icp_buffer_4096_vectors;
    temp = FIXNUM_TIMES(temp,bytes_per_typed_simple_array(list_constant_4,
	    FIX((SI_Long)4096L)));
    return VALUES_1(temp);
}

/* OUT-VARIABLE-FILL-ICP-BUFFER-4096-VECTORS */
Object out_variable_fill_icp_buffer_4096_vectors()
{
    Object temp;

    x_note_fn_call(47,122);
    temp = FIXNUM_MINUS(Count_of_variable_fill_icp_buffer_4096_vectors,
	    length(Available_variable_fill_icp_buffer_4096_vectors));
    return VALUES_1(temp);
}

/* MAKE-PERMANENT-VARIABLE-FILL-ICP-BUFFER-4096-VECTOR-INTERNAL */
Object make_permanent_variable_fill_icp_buffer_4096_vector_internal()
{
    Object temp;
    XDeclare_area(1);

    x_note_fn_call(47,123);
    atomic_incff_symval(Qcount_of_variable_fill_icp_buffer_4096_vectors,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0))
	temp = make_array(3,FIX((SI_Long)4096L),Kelement_type,list_constant_4);
    POP_AREA(0);
    return VALUES_1(temp);
}

/* MAKE-VARIABLE-FILL-ICP-BUFFER */
Object make_variable_fill_icp_buffer()
{
    Object temp, svref_arg_1, svref_arg_2, temp_1, vector_pool_cons, temp_2;
    Object svref_arg_2_1;

    x_note_fn_call(47,124);
    if (ISVREF(Available_variable_fill_icp_buffer_4096_vectors_vector,
	    IFIX(Current_thread_index))) {
	temp = 
		M_CAR(ISVREF(Available_variable_fill_icp_buffer_4096_vectors_vector,
		IFIX(Current_thread_index)));
	svref_arg_1 = Available_variable_fill_icp_buffer_4096_vectors_vector;
	svref_arg_2 = Current_thread_index;
	temp_1 = 
		M_CDR(ISVREF(Available_variable_fill_icp_buffer_4096_vectors_vector,
		IFIX(Current_thread_index)));
	vector_pool_cons = 
		ISVREF(Available_variable_fill_icp_buffer_4096_vectors_vector,
		IFIX(Current_thread_index));
	inline_note_reclaim_cons(vector_pool_cons,Qvector_pool);
	if (ISVREF(Available_vector_pool_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_2 = ISVREF(Available_vector_pool_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_2) = vector_pool_cons;
	    temp_2 = Available_vector_pool_conses_tail_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2_1) = vector_pool_cons;
	}
	else {
	    temp_2 = Available_vector_pool_conses_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2_1) = vector_pool_cons;
	    temp_2 = Available_vector_pool_conses_tail_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2_1) = vector_pool_cons;
	}
	M_CDR(vector_pool_cons) = Nil;
	SVREF(svref_arg_1,svref_arg_2) = temp_1;
    }
    else
	temp = make_permanent_variable_fill_icp_buffer_4096_vector_internal();
    return VALUES_1(temp);
}

/* RECLAIM-VARIABLE-FILL-ICP-BUFFER */
Object reclaim_variable_fill_icp_buffer(variable_fill_icp_buffer_4096_vector)
    Object variable_fill_icp_buffer_4096_vector;
{
    Object svref_arg_1, svref_arg_2, new_cons, temp, svref_arg_2_1;
    Object svref_new_value, gensymed_symbol;

    x_note_fn_call(47,125);
    svref_arg_1 = Available_variable_fill_icp_buffer_4096_vectors_vector;
    svref_arg_2 = Current_thread_index;
    new_cons = ISVREF(Available_vector_pool_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp = Available_vector_pool_conses_vector;
	svref_arg_2_1 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp,svref_arg_2_1) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_vector_pool_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp = Available_vector_pool_conses_tail_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp,svref_arg_2_1) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_vector_pool_cons_pool();
    M_CAR(gensymed_symbol) = variable_fill_icp_buffer_4096_vector;
    temp = ISVREF(Available_variable_fill_icp_buffer_4096_vectors_vector,
	    IFIX(Current_thread_index));
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qvector_pool);
    SVREF(svref_arg_1,svref_arg_2) = gensymed_symbol;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Recycled_variable_fill_icp_buffers, Qrecycled_variable_fill_icp_buffers);

DEFINE_VARIABLE_WITH_SYMBOL(Transmitted_variable_fill_icp_buffers, Qtransmitted_variable_fill_icp_buffers);

DEFINE_VARIABLE_WITH_SYMBOL(Available_icp_buffer_ref_count_conses, Qavailable_icp_buffer_ref_count_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_icp_buffer_ref_count_conses_tail, Qavailable_icp_buffer_ref_count_conses_tail);

Object Available_icp_buffer_ref_count_conses_vector = UNBOUND;

Object Available_icp_buffer_ref_count_conses_tail_vector = UNBOUND;

Object Icp_buffer_ref_count_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Icp_buffer_ref_count_cons_counter, Qicp_buffer_ref_count_cons_counter);

/* OUTSTANDING-ICP-BUFFER-REF-COUNT-CONSES */
Object outstanding_icp_buffer_ref_count_conses()
{
    Object temp;

    x_note_fn_call(47,126);
    temp = FIXNUM_MINUS(Icp_buffer_ref_count_cons_counter,
	    length(Available_icp_buffer_ref_count_conses));
    return VALUES_1(temp);
}

/* ICP-BUFFER-REF-COUNT-CONS-MEMORY-USAGE */
Object icp_buffer_ref_count_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(47,127);
    temp = FIXNUM_TIMES(Icp_buffer_ref_count_cons_counter,
	    ltimes(FIX((SI_Long)2L),Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-ICP-BUFFER-REF-COUNT-CONS-POOL */
Object replenish_icp_buffer_ref_count_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(47,128);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qicp_buffer_ref_count_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_icp_buffer_ref_count_conses_vector,
	    IFIX(Current_thread_index))) {
	svref_arg_1 = Available_icp_buffer_ref_count_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_icp_buffer_ref_count_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_icp_buffer_ref_count_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_icp_buffer_ref_count_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Icp_buffer_ref_count_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qicp_buffer_ref_count;  /* icp-buffer-ref-count */

/* ICP-BUFFER-REF-COUNT-CONS-1 */
Object icp_buffer_ref_count_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(47,129);
    new_cons = ISVREF(Available_icp_buffer_ref_count_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_icp_buffer_ref_count_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_icp_buffer_ref_count_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_icp_buffer_ref_count_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_icp_buffer_ref_count_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qicp_buffer_ref_count);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-ICP-BUFFER-REF-COUNT-LIST-POOL */
Object replenish_icp_buffer_ref_count_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(47,130);
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
    if (ISVREF(Available_icp_buffer_ref_count_conses_vector,
	    IFIX(Current_thread_index))) {
	svref_arg_1 = Available_icp_buffer_ref_count_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_icp_buffer_ref_count_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_icp_buffer_ref_count_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_icp_buffer_ref_count_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qicp_buffer_ref_count_cons_counter,
	    FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-ICP-BUFFER-REF-COUNT-LIST-1 */
Object make_icp_buffer_ref_count_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(47,131);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = 
		ISVREF(Available_icp_buffer_ref_count_conses_vector,
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
	replenish_icp_buffer_ref_count_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = 
		    ISVREF(Available_icp_buffer_ref_count_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qicp_buffer_ref_count);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_icp_buffer_ref_count_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_icp_buffer_ref_count_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_icp_buffer_ref_count_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_icp_buffer_ref_count_conses_tail_vector;
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

/* ICP-BUFFER-REF-COUNT-LIST-2 */
Object icp_buffer_ref_count_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(47,132);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_icp_buffer_ref_count_conses_vector,
	    IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_icp_buffer_ref_count_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = 
		ISVREF(Available_icp_buffer_ref_count_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qicp_buffer_ref_count);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_icp_buffer_ref_count_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_icp_buffer_ref_count_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_icp_buffer_ref_count_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_icp_buffer_ref_count_conses_tail_vector;
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

/* ICP-BUFFER-REF-COUNT-LIST-3 */
Object icp_buffer_ref_count_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(47,133);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_icp_buffer_ref_count_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_icp_buffer_ref_count_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = 
		ISVREF(Available_icp_buffer_ref_count_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qicp_buffer_ref_count);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_icp_buffer_ref_count_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_icp_buffer_ref_count_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_icp_buffer_ref_count_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_icp_buffer_ref_count_conses_tail_vector;
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

/* ICP-BUFFER-REF-COUNT-LIST-4 */
Object icp_buffer_ref_count_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(47,134);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_icp_buffer_ref_count_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_icp_buffer_ref_count_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = 
		ISVREF(Available_icp_buffer_ref_count_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qicp_buffer_ref_count);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_icp_buffer_ref_count_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_icp_buffer_ref_count_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_icp_buffer_ref_count_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_icp_buffer_ref_count_conses_tail_vector;
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

/* ICP-BUFFER-REF-COUNT-LIST-TRACE-HOOK */
Object icp_buffer_ref_count_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(47,135);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-ICP-BUFFER-REF-COUNT-CONSES-1 */
Object copy_tree_using_icp_buffer_ref_count_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(47,136);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_icp_buffer_ref_count_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_icp_buffer_ref_count_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( 
		    !TRUEP(ISVREF(Available_icp_buffer_ref_count_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_icp_buffer_ref_count_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_icp_buffer_ref_count_cons_pool();
	temp_1 = copy_tree_using_icp_buffer_ref_count_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qicp_buffer_ref_count);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_icp_buffer_ref_count_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_icp_buffer_ref_count_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( 
		    !TRUEP(ISVREF(Available_icp_buffer_ref_count_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_icp_buffer_ref_count_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_icp_buffer_ref_count_cons_pool();
	temp_1 = 
		copy_tree_using_icp_buffer_ref_count_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qicp_buffer_ref_count);
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

/* COPY-LIST-USING-ICP-BUFFER-REF-COUNT-CONSES-1 */
Object copy_list_using_icp_buffer_ref_count_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(47,137);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_icp_buffer_ref_count_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_icp_buffer_ref_count_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( 
		    !TRUEP(ISVREF(Available_icp_buffer_ref_count_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_icp_buffer_ref_count_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_icp_buffer_ref_count_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qicp_buffer_ref_count);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_icp_buffer_ref_count_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_icp_buffer_ref_count_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( 
		    !TRUEP(ISVREF(Available_icp_buffer_ref_count_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_icp_buffer_ref_count_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_icp_buffer_ref_count_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qicp_buffer_ref_count);
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

/* RECLAIM-ICP-BUFFER-REF-COUNT-CONS-1 */
Object reclaim_icp_buffer_ref_count_cons_1(icp_buffer_ref_count_cons)
    Object icp_buffer_ref_count_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(47,138);
    inline_note_reclaim_cons(icp_buffer_ref_count_cons,Qicp_buffer_ref_count);
    if (ISVREF(Available_icp_buffer_ref_count_conses_tail_vector,
	    IFIX(Current_thread_index))) {
	temp = ISVREF(Available_icp_buffer_ref_count_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = icp_buffer_ref_count_cons;
	temp = Available_icp_buffer_ref_count_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = icp_buffer_ref_count_cons;
    }
    else {
	temp = Available_icp_buffer_ref_count_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = icp_buffer_ref_count_cons;
	temp = Available_icp_buffer_ref_count_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = icp_buffer_ref_count_cons;
    }
    M_CDR(icp_buffer_ref_count_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-ICP-BUFFER-REF-COUNT-LIST-1 */
Object reclaim_icp_buffer_ref_count_list_1(icp_buffer_ref_count_list)
    Object icp_buffer_ref_count_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(47,139);
    if (icp_buffer_ref_count_list) {
	last_1 = icp_buffer_ref_count_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qicp_buffer_ref_count);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qicp_buffer_ref_count);
	if (ISVREF(Available_icp_buffer_ref_count_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = 
		    ISVREF(Available_icp_buffer_ref_count_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = icp_buffer_ref_count_list;
	    temp = Available_icp_buffer_ref_count_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_icp_buffer_ref_count_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = icp_buffer_ref_count_list;
	    temp = Available_icp_buffer_ref_count_conses_tail_vector;
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

/* RECLAIM-ICP-BUFFER-REF-COUNT-LIST*-1 */
Object reclaim_icp_buffer_ref_count_list_star_1(icp_buffer_ref_count_list)
    Object icp_buffer_ref_count_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(47,140);
    if (CONSP(icp_buffer_ref_count_list)) {
	temp = last(icp_buffer_ref_count_list,_);
	M_CDR(temp) = Nil;
	if (icp_buffer_ref_count_list) {
	    last_1 = icp_buffer_ref_count_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qicp_buffer_ref_count);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qicp_buffer_ref_count);
	    if (ISVREF(Available_icp_buffer_ref_count_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = 
			ISVREF(Available_icp_buffer_ref_count_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = icp_buffer_ref_count_list;
		temp = Available_icp_buffer_ref_count_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_icp_buffer_ref_count_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = icp_buffer_ref_count_list;
		temp = Available_icp_buffer_ref_count_conses_tail_vector;
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

/* RECLAIM-ICP-BUFFER-REF-COUNT-TREE-1 */
Object reclaim_icp_buffer_ref_count_tree_1(tree)
    Object tree;
{
    Object e, e2, icp_buffer_ref_count_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(47,141);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_icp_buffer_ref_count_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		icp_buffer_ref_count_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(icp_buffer_ref_count_cons,
			Qicp_buffer_ref_count);
		if (EQ(icp_buffer_ref_count_cons,e))
		    goto end_1;
		else if ( !TRUEP(icp_buffer_ref_count_cons))
		    goto end_1;
		else
		    icp_buffer_ref_count_cons = CDR(icp_buffer_ref_count_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_icp_buffer_ref_count_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = 
			ISVREF(Available_icp_buffer_ref_count_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_icp_buffer_ref_count_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_icp_buffer_ref_count_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_icp_buffer_ref_count_conses_tail_vector;
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

/* DELETE-ICP-BUFFER-REF-COUNT-ELEMENT-1 */
Object delete_icp_buffer_ref_count_element_1(element,icp_buffer_ref_count_list)
    Object element, icp_buffer_ref_count_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(47,142);
    if (icp_buffer_ref_count_list) {
	if (EQ(element,M_CAR(icp_buffer_ref_count_list))) {
	    temp = CDR(icp_buffer_ref_count_list);
	    inline_note_reclaim_cons(icp_buffer_ref_count_list,
		    Qicp_buffer_ref_count);
	    if (ISVREF(Available_icp_buffer_ref_count_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = 
			ISVREF(Available_icp_buffer_ref_count_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = icp_buffer_ref_count_list;
		temp_1 = Available_icp_buffer_ref_count_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = icp_buffer_ref_count_list;
	    }
	    else {
		temp_1 = Available_icp_buffer_ref_count_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = icp_buffer_ref_count_list;
		temp_1 = Available_icp_buffer_ref_count_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = icp_buffer_ref_count_list;
	    }
	    M_CDR(icp_buffer_ref_count_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = icp_buffer_ref_count_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qicp_buffer_ref_count);
		if (ISVREF(Available_icp_buffer_ref_count_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = 
			    ISVREF(Available_icp_buffer_ref_count_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_icp_buffer_ref_count_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_icp_buffer_ref_count_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_icp_buffer_ref_count_conses_tail_vector;
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
	    temp = icp_buffer_ref_count_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-ICP-BUFFER-REF-COUNT-CONS-1 */
Object delete_icp_buffer_ref_count_cons_1(icp_buffer_ref_count_cons,
	    icp_buffer_ref_count_list)
    Object icp_buffer_ref_count_cons, icp_buffer_ref_count_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(47,143);
    if (EQ(icp_buffer_ref_count_cons,icp_buffer_ref_count_list))
	temp = CDR(icp_buffer_ref_count_list);
    else {
	l_trailer_qm = Nil;
	l = icp_buffer_ref_count_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,icp_buffer_ref_count_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = icp_buffer_ref_count_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_icp_buffer_ref_count_cons_1(icp_buffer_ref_count_cons);
    return VALUES_1(temp);
}

Object The_type_description_of_icp_buffer = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_icp_buffers, Qchain_of_available_icp_buffers);

DEFINE_VARIABLE_WITH_SYMBOL(Icp_buffer_count, Qicp_buffer_count);

Object Chain_of_available_icp_buffers_vector = UNBOUND;

/* ICP-BUFFER-STRUCTURE-MEMORY-USAGE */
Object icp_buffer_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(47,144);
    temp = Icp_buffer_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ICP-BUFFER-COUNT */
Object outstanding_icp_buffer_count()
{
    Object def_structure_icp_buffer_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(47,145);
    gensymed_symbol = IFIX(Icp_buffer_count);
    def_structure_icp_buffer_variable = Chain_of_available_icp_buffers;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_icp_buffer_variable))
	goto end_loop;
    def_structure_icp_buffer_variable = 
	    ISVREF(def_structure_icp_buffer_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ICP-BUFFER-INTERNAL-1 */
Object reclaim_icp_buffer_internal_1(icp_buffer)
    Object icp_buffer;
{
    Object structure_being_reclaimed, vector_1, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(47,146);
    inline_note_reclaim_cons(icp_buffer,Nil);
    structure_being_reclaimed = icp_buffer;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      vector_1 = ISVREF(icp_buffer,(SI_Long)4L);
      if (vector_1)
	  reclaim_variable_fill_icp_buffer(vector_1);
      SVREF(icp_buffer,FIX((SI_Long)4L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_icp_buffers_vector,
	    IFIX(Current_thread_index));
    SVREF(icp_buffer,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_icp_buffers_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = icp_buffer;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ICP-BUFFER */
Object reclaim_structure_for_icp_buffer(icp_buffer)
    Object icp_buffer;
{
    x_note_fn_call(47,147);
    return reclaim_icp_buffer_internal_1(icp_buffer);
}

static Object Qg2_defstruct_structure_name_icp_buffer_g2_struct;  /* g2-defstruct-structure-name::icp-buffer-g2-struct */

/* MAKE-PERMANENT-ICP-BUFFER-STRUCTURE-INTERNAL */
Object make_permanent_icp_buffer_structure_internal()
{
    Object def_structure_icp_buffer_variable, defstruct_g2_icp_buffer_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(47,148);
    def_structure_icp_buffer_variable = Nil;
    atomic_incff_symval(Qicp_buffer_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_icp_buffer_variable = Nil;
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
	defstruct_g2_icp_buffer_variable = the_array;
	SVREF(defstruct_g2_icp_buffer_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_icp_buffer_g2_struct;
	def_structure_icp_buffer_variable = defstruct_g2_icp_buffer_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_icp_buffer_variable);
}

/* MAKE-ICP-BUFFER-INTERNAL-1 */
Object make_icp_buffer_internal_1(icp_buffer_vector)
    Object icp_buffer_vector;
{
    Object def_structure_icp_buffer_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(47,149);
    def_structure_icp_buffer_variable = 
	    ISVREF(Chain_of_available_icp_buffers_vector,
	    IFIX(Current_thread_index));
    if (def_structure_icp_buffer_variable) {
	svref_arg_1 = Chain_of_available_icp_buffers_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_icp_buffer_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_icp_buffer_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_icp_buffer_g2_struct;
    }
    else
	def_structure_icp_buffer_variable = 
		make_permanent_icp_buffer_structure_internal();
    inline_note_allocate_cons(def_structure_icp_buffer_variable,Nil);
    SVREF(def_structure_icp_buffer_variable,FIX((SI_Long)4L)) = 
	    icp_buffer_vector;
    SVREF(def_structure_icp_buffer_variable,FIX((SI_Long)1L)) = Nil;
    ISVREF(def_structure_icp_buffer_variable,(SI_Long)2L) = FIX((SI_Long)0L);
    ISVREF(def_structure_icp_buffer_variable,(SI_Long)3L) = FIX((SI_Long)0L);
    SVREF(def_structure_icp_buffer_variable,FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_icp_buffer_variable);
}

DEFINE_VARIABLE_WITH_SYMBOL(Recycled_icp_buffers, Qrecycled_icp_buffers);

/* RECLAIM-ICP-BUFFER */
Object reclaim_icp_buffer(icp_buffer)
    Object icp_buffer;
{
    Object ref, car_new_value;

    x_note_fn_call(47,150);
    ref = ISVREF(icp_buffer,(SI_Long)5L);
    if (ref) {
	car_new_value = FIXNUM_SUB1(CAR(ref));
	if ((SI_Long)0L == IFIX(M_CAR(ref) = car_new_value))
	    reclaim_icp_buffer_ref_count_cons_1(ref);
	else
	    SVREF(icp_buffer,FIX((SI_Long)4L)) = Nil;
	SVREF(icp_buffer,FIX((SI_Long)5L)) = Nil;
    }
    reclaim_icp_buffer_internal_1(icp_buffer);
    return VALUES_1(Nil);
}

/* COPY-ICP-BUFFER */
Object copy_icp_buffer(buffer)
    Object buffer;
{
    Object copy, temp, ref;

    x_note_fn_call(47,151);
    copy = make_icp_buffer_internal_1(ISVREF(buffer,(SI_Long)4L));
    temp = ISVREF(buffer,(SI_Long)2L);
    SVREF(copy,FIX((SI_Long)2L)) = temp;
    temp = ISVREF(buffer,(SI_Long)3L);
    SVREF(copy,FIX((SI_Long)3L)) = temp;
    ref = ISVREF(buffer,(SI_Long)5L);
    if ( !TRUEP(ref)) {
	ref = icp_buffer_ref_count_cons_1(FIX((SI_Long)1L),Nil);
	SVREF(buffer,FIX((SI_Long)5L)) = ref;
    }
    temp = FIXNUM_ADD1(CAR(ref));
    M_CAR(ref) = temp;
    SVREF(copy,FIX((SI_Long)5L)) = ref;
    return VALUES_1(copy);
}

/* ENSURE-ICP-BUFFER-VECTOR-WRITABILITY */
Object ensure_icp_buffer_vector_writability(buffer,ref)
    Object buffer, ref;
{
    Object temp;

    x_note_fn_call(47,152);
    if (ref) {
	temp = FIXNUM_SUB1(CAR(ref));
	M_CAR(ref) = temp;
	SVREF(buffer,FIX((SI_Long)5L)) = Nil;
	if ( !((SI_Long)0L == IFIX(CAR(ref)))) {
	    temp = copy_icp_buffer_vector(ISVREF(buffer,(SI_Long)4L),
		    make_variable_fill_icp_buffer(),ISVREF(buffer,
		    (SI_Long)2L),ISVREF(buffer,(SI_Long)3L));
	    SVREF(buffer,FIX((SI_Long)4L)) = temp;
	}
    }
    return VALUES_1(Nil);
}

/* COPY-ICP-BUFFER-VECTOR */
Object copy_icp_buffer_vector(buffer_vector,copy_vector,buffer_start,
	    buffer_end)
    Object buffer_vector, copy_vector, buffer_start, buffer_end;
{
    SI_Long icp_byte_index, ab_loop_bind_, aref_new_value;

    x_note_fn_call(47,153);
    icp_byte_index = IFIX(buffer_start);
    ab_loop_bind_ = IFIX(buffer_end);
  next_loop:
    if (icp_byte_index >= ab_loop_bind_)
	goto end_loop;
    aref_new_value = UBYTE_8_ISAREF_1(buffer_vector,icp_byte_index);
    UBYTE_8_ISASET_1(copy_vector,icp_byte_index,aref_new_value);
    icp_byte_index = icp_byte_index + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(copy_vector);
}

/* COPY-ICP-BUFFER-CHAIN */
Object copy_icp_buffer_chain(buffer_chain)
    Object buffer_chain;
{
    Object first_copy, previous_buffer, buffer, previous_copy, copy;
    Object ab_loop_iter_flag_, temp;

    x_note_fn_call(47,154);
    if (buffer_chain) {
	first_copy = copy_icp_buffer(buffer_chain);
	previous_buffer = buffer_chain;
	buffer = Nil;
	previous_copy = first_copy;
	copy = Nil;
	ab_loop_iter_flag_ = T;
      next_loop:
	buffer = ISVREF(previous_buffer,(SI_Long)1L);
	if ( !TRUEP(buffer))
	    goto end_loop;
	if ( !TRUEP(ab_loop_iter_flag_))
	    previous_copy = copy;
	copy = copy_icp_buffer(buffer);
	SVREF(previous_copy,FIX((SI_Long)1L)) = copy;
	ab_loop_iter_flag_ = Nil;
	previous_buffer = buffer;
	goto next_loop;
      end_loop:
	temp = first_copy;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

Object The_type_description_of_icp_port = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_icp_ports, Qchain_of_available_icp_ports);

DEFINE_VARIABLE_WITH_SYMBOL(Icp_port_count, Qicp_port_count);

Object Chain_of_available_icp_ports_vector = UNBOUND;

/* ICP-PORT-STRUCTURE-MEMORY-USAGE */
Object icp_port_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(47,155);
    temp = Icp_port_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)20L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ICP-PORT-COUNT */
Object outstanding_icp_port_count()
{
    Object def_structure_icp_port_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(47,156);
    gensymed_symbol = IFIX(Icp_port_count);
    def_structure_icp_port_variable = Chain_of_available_icp_ports;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_icp_port_variable))
	goto end_loop;
    def_structure_icp_port_variable = 
	    ISVREF(def_structure_icp_port_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ICP-PORT-INTERNAL-1 */
Object reclaim_icp_port_internal_1(icp_port)
    Object icp_port;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(47,157);
    inline_note_reclaim_cons(icp_port,Nil);
    structure_being_reclaimed = icp_port;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_if_index_space(ISVREF(icp_port,(SI_Long)8L));
      SVREF(icp_port,FIX((SI_Long)8L)) = Nil;
      reclaim_if_index_space(ISVREF(icp_port,(SI_Long)9L));
      SVREF(icp_port,FIX((SI_Long)9L)) = Nil;
      reclaim_if_index_space(ISVREF(icp_port,(SI_Long)10L));
      SVREF(icp_port,FIX((SI_Long)10L)) = Nil;
      reclaim_if_frame_serial_number_to_item_table(ISVREF(icp_port,
	      (SI_Long)11L));
      SVREF(icp_port,FIX((SI_Long)11L)) = Nil;
      nil_out_car_of_cons(ISVREF(icp_port,(SI_Long)18L));
      SVREF(icp_port,FIX((SI_Long)18L)) = Nil;
      reclaim_if_index_space(ISVREF(icp_port,(SI_Long)19L));
      SVREF(icp_port,FIX((SI_Long)19L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_icp_ports_vector,
	    IFIX(Current_thread_index));
    SVREF(icp_port,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_icp_ports_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = icp_port;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ICP-PORT */
Object reclaim_structure_for_icp_port(icp_port)
    Object icp_port;
{
    x_note_fn_call(47,158);
    return reclaim_icp_port_internal_1(icp_port);
}

static Object Qg2_defstruct_structure_name_icp_port_g2_struct;  /* g2-defstruct-structure-name::icp-port-g2-struct */

/* MAKE-PERMANENT-ICP-PORT-STRUCTURE-INTERNAL */
Object make_permanent_icp_port_structure_internal()
{
    Object def_structure_icp_port_variable, defstruct_g2_icp_port_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(47,159);
    def_structure_icp_port_variable = Nil;
    atomic_incff_symval(Qicp_port_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_icp_port_variable = Nil;
	gensymed_symbol = (SI_Long)20L;
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
	defstruct_g2_icp_port_variable = the_array;
	SVREF(defstruct_g2_icp_port_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_icp_port_g2_struct;
	def_structure_icp_port_variable = defstruct_g2_icp_port_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_icp_port_variable);
}

/* MAKE-ICP-PORT-STRUCTURE-1 */
Object make_icp_port_structure_1(icp_connection_handle,parent_icp_socket,
	    icp_port_direction,receive_or_transmit_directly_qm)
    Object icp_connection_handle, parent_icp_socket, icp_port_direction;
    Object receive_or_transmit_directly_qm;
{
    Object def_structure_icp_port_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(47,160);
    def_structure_icp_port_variable = 
	    ISVREF(Chain_of_available_icp_ports_vector,
	    IFIX(Current_thread_index));
    if (def_structure_icp_port_variable) {
	svref_arg_1 = Chain_of_available_icp_ports_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_icp_port_variable,(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_icp_port_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_icp_port_g2_struct;
    }
    else
	def_structure_icp_port_variable = 
		make_permanent_icp_port_structure_internal();
    inline_note_allocate_cons(def_structure_icp_port_variable,Nil);
    SVREF(def_structure_icp_port_variable,FIX((SI_Long)1L)) = 
	    icp_connection_handle;
    SVREF(def_structure_icp_port_variable,FIX((SI_Long)2L)) = 
	    parent_icp_socket;
    SVREF(def_structure_icp_port_variable,FIX((SI_Long)3L)) = 
	    icp_port_direction;
    SVREF(def_structure_icp_port_variable,FIX((SI_Long)5L)) = 
	    receive_or_transmit_directly_qm;
    SVREF(def_structure_icp_port_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_icp_port_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_icp_port_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_icp_port_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_icp_port_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_icp_port_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_icp_port_variable,FIX((SI_Long)11L)) = Nil;
    ISVREF(def_structure_icp_port_variable,(SI_Long)14L) = FIX((SI_Long)0L);
    SVREF(def_structure_icp_port_variable,FIX((SI_Long)15L)) = Nil;
    SVREF(def_structure_icp_port_variable,FIX((SI_Long)16L)) = Nil;
    ISVREF(def_structure_icp_port_variable,(SI_Long)17L) = FIX((SI_Long)0L);
    SVREF(def_structure_icp_port_variable,FIX((SI_Long)18L)) = Nil;
    SVREF(def_structure_icp_port_variable,FIX((SI_Long)19L)) = Nil;
    return VALUES_1(def_structure_icp_port_variable);
}

/* SET-SOCKET-DEBUG-STATUS */
Object set_socket_debug_status(icp_socket,status)
    Object icp_socket, status;
{
    x_note_fn_call(47,161);
    return VALUES_1(FIX(g2ext_set_debug_status(IFIX(ISVREF(ISVREF(icp_socket,
	    (SI_Long)3L),(SI_Long)1L)),IFIX(status))));
}

/* NIL-OUT-CAR-OF-CONS */
Object nil_out_car_of_cons(cons_qm)
    Object cons_qm;
{
    Object temp;

    x_note_fn_call(47,162);
    if (cons_qm)
	temp = M_CAR(cons_qm) = Nil;
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qitem_index_space;   /* item-index-space */

/* ITEM-INDEX-SPACE */
Object item_index_space(icp_port)
    Object icp_port;
{
    Object temp;

    x_note_fn_call(47,163);
    temp = ISVREF(icp_port,(SI_Long)9L);
    if (temp);
    else {
	temp = set_up_icp_object_index_space(Qitem_index_space);
	SVREF(icp_port,FIX((SI_Long)9L)) = temp;
    }
    return VALUES_1(temp);
}

static Object Qitem_with_handle_index_space;  /* item-with-handle-index-space */

/* ITEM-WITH-HANDLE-INDEX-SPACE */
Object item_with_handle_index_space(icp_port)
    Object icp_port;
{
    Object temp;

    x_note_fn_call(47,164);
    temp = ISVREF(icp_port,(SI_Long)10L);
    if (temp);
    else {
	temp = set_up_icp_object_index_space(Qitem_with_handle_index_space);
	SVREF(icp_port,FIX((SI_Long)10L)) = temp;
    }
    return VALUES_1(temp);
}

/* REGISTER-ITEM-WITH-HANDLE-ON-PORT */
Object register_item_with_handle_on_port(index_1,item,icp_port)
    Object index_1, item, icp_port;
{
    Object index_space, vector_1, object, svref_arg_1;
    SI_Long index_2, svref_arg_2;

    x_note_fn_call(47,165);
    index_space = item_with_handle_index_space(icp_port);
    vector_1 = ISVREF(index_space,(SI_Long)2L);
    index_2 = IFIX(index_1) >>  -  - (SI_Long)10L;
    vector_1 = vector_1 && index_2 < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1)) ? ISVREF(vector_1,
	    index_2) : Qnil;
    index_2 = IFIX(index_1) & (SI_Long)1023L;
    object = gensym_cons_1(item,vector_1 && index_2 < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1)) ? ISVREF(vector_1,
	    index_2) : Qnil);
    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
	enlarge_index_space(index_space,index_1);
    svref_arg_1 = ISVREF(ISVREF(index_space,(SI_Long)2L),IFIX(index_1) >>  
	    -  - (SI_Long)10L);
    svref_arg_2 = IFIX(index_1) & (SI_Long)1023L;
    return VALUES_1(ISVREF(svref_arg_1,svref_arg_2) = object);
}

/* DEREGISTER-ITEM-WITH-HANDLE-ON-PORT */
Object deregister_item_with_handle_on_port(index_1,item,icp_port)
    Object index_1, item, icp_port;
{
    Object index_space, vector_1, object, svref_arg_1;
    SI_Long index_2, svref_arg_2;

    x_note_fn_call(47,166);
    index_space = item_with_handle_index_space(icp_port);
    vector_1 = ISVREF(index_space,(SI_Long)2L);
    index_2 = IFIX(index_1) >>  -  - (SI_Long)10L;
    vector_1 = vector_1 && index_2 < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1)) ? ISVREF(vector_1,
	    index_2) : Qnil;
    index_2 = IFIX(index_1) & (SI_Long)1023L;
    object = delete_gensym_element_1(item,vector_1 && index_2 < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1)) ? ISVREF(vector_1,
	    index_2) : Qnil);
    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
	enlarge_index_space(index_space,index_1);
    svref_arg_1 = ISVREF(ISVREF(index_space,(SI_Long)2L),IFIX(index_1) >>  
	    -  - (SI_Long)10L);
    svref_arg_2 = IFIX(index_1) & (SI_Long)1023L;
    return VALUES_1(ISVREF(svref_arg_1,svref_arg_2) = object);
}

/* ITEMS-REGISTERED-WITH-HANDLE-ON-PORT */
Object items_registered_with_handle_on_port(index_1,icp_port)
    Object index_1, icp_port;
{
    Object index_space, vector_1, temp;
    SI_Long index_2;

    x_note_fn_call(47,167);
    if (ISVREF(icp_port,(SI_Long)10L)) {
	index_space = item_with_handle_index_space(icp_port);
	vector_1 = ISVREF(index_space,(SI_Long)2L);
	index_2 = IFIX(index_1) >>  -  - (SI_Long)10L;
	vector_1 = vector_1 && index_2 < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1)) ? 
		ISVREF(vector_1,index_2) : Qnil;
	index_2 = IFIX(index_1) & (SI_Long)1023L;
	temp = vector_1 && index_2 < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1)) ? 
		ISVREF(vector_1,index_2) : Qnil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* CLEAR-ITEMS-REGISTERED-WITH-HANDLE-ON-PORT */
Object clear_items_registered_with_handle_on_port(index_1,icp_port)
    Object index_1, icp_port;
{
    Object index_space, svref_arg_1;
    SI_Long svref_arg_2;

    x_note_fn_call(47,168);
    index_space = item_with_handle_index_space(icp_port);
    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
	enlarge_index_space(index_space,index_1);
    svref_arg_1 = ISVREF(ISVREF(index_space,(SI_Long)2L),IFIX(index_1) >>  
	    -  - (SI_Long)10L);
    svref_arg_2 = IFIX(index_1) & (SI_Long)1023L;
    return VALUES_1(ISVREF(svref_arg_1,svref_arg_2) = Nil);
}

/* FRAME-SERIAL-NUMBER-TO-ITEM-TABLE */
Object frame_serial_number_to_item_table(icp_port)
    Object icp_port;
{
    Object temp;

    x_note_fn_call(47,169);
    temp = ISVREF(icp_port,(SI_Long)11L);
    if (temp);
    else {
	temp = make_frame_serial_number_to_item_table();
	SVREF(icp_port,FIX((SI_Long)11L)) = temp;
    }
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_icp_port, Qcurrent_icp_port);

DEFINE_VARIABLE_WITH_SYMBOL(Current_icp_socket, Qcurrent_icp_socket);

DEFINE_VARIABLE_WITH_SYMBOL(Current_standard_icp_object_index_space, Qcurrent_standard_icp_object_index_space);

DEFINE_VARIABLE_WITH_SYMBOL(Current_temporary_icp_object_index_space, Qcurrent_temporary_icp_object_index_space);

static Object Qg2;                 /* g2 */

static Object Qframe_serial_number;  /* frame-serial-number */

/* GET-FROM-ICP-PORT */
Object get_from_icp_port(icp_port,icp_object_index,
	    name_of_corresponding_icp_object_index_space)
    Object icp_port, icp_object_index;
    Object name_of_corresponding_icp_object_index_space;
{
    Object port, index_space_name, icp_socket, temp, temp_1, index_space;
    Object skip_list, key_value, marked, pred, curr, succ, reference;
    Object entry_hash;
    SI_Long gensymed_symbol, temp_2, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_;
    Object result;

    x_note_fn_call(47,170);
    port = icp_port;
    if (EQ(name_of_corresponding_icp_object_index_space,
	    Qstandard_icp_object_index_space))
	index_space_name = Qstandard_icp_object_index_space;
    else if (EQ(name_of_corresponding_icp_object_index_space,
	    Qitem_index_space)) {
	icp_socket = ISVREF(port,(SI_Long)2L);
	if (Inhibit_corresponding_icp_object_making)
	    index_space_name = Qstandard_icp_object_index_space;
	else if (EQ(Qg2,ISVREF(icp_socket,(SI_Long)25L))) {
	    if (EQ(ISVREF(port,(SI_Long)3L),Qoutput))
		index_space_name = Qitem_index_space;
	    else {
		temp = ISVREF(icp_socket,(SI_Long)21L);
		temp_1 = ISVREF(icp_socket,(SI_Long)22L);
		index_space_name = IFIX(FIXNUM_MIN(temp,temp_1)) >= 
			(SI_Long)21L ? Qitem_index_space : 
			Qframe_serial_number;
	    }
	}
	else {
	    temp = ISVREF(icp_socket,(SI_Long)21L);
	    temp_1 = ISVREF(icp_socket,(SI_Long)22L);
	    index_space_name = IFIX(FIXNUM_MIN(temp,temp_1)) >= 
		    (SI_Long)10L ? Qitem_index_space : 
		    Qstandard_icp_object_index_space;
	}
    }
    else if (EQ(name_of_corresponding_icp_object_index_space,
	    Qframe_serial_number))
	index_space_name = EQ(ISVREF(port,(SI_Long)3L),Qoutput) ? 
		Qitem_index_space : Qframe_serial_number;
    else
	index_space_name = Qstandard_icp_object_index_space;
    if (EQ(index_space_name,Qstandard_icp_object_index_space))
	index_space = ISVREF(icp_port,(SI_Long)8L);
    else if (EQ(index_space_name,Qitem_index_space))
	index_space = item_index_space(icp_port);
    else if (EQ(index_space_name,Qframe_serial_number))
	index_space = frame_serial_number_to_item_table(icp_port);
    else
	index_space = Qnil;
    if (EQ(index_space_name,Qframe_serial_number)) {
	gensymed_symbol = IFIX(sxhashw(icp_object_index));
	temp_2 = gensymed_symbol % (SI_Long)67L;
	temp_1 = SVREF(index_space,FIX(temp_2));
	skip_list = CDR(temp_1);
	key_value = icp_object_index;
	key_hash_value = gensymed_symbol;
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
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_2:
	if ( !TRUEP(marked))
	    goto end_loop_1;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_2;
      end_loop_1:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
	temp_1 = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		(EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
    }
    else {
	if (FIXNUM_GE(icp_object_index,ISVREF(index_space,(SI_Long)4L)))
	    enlarge_index_space(index_space,icp_object_index);
	temp_1 = ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
		IFIX(icp_object_index) >>  -  - (SI_Long)10L),
		IFIX(icp_object_index) & (SI_Long)1023L);
    }
    return VALUES_1(temp_1);
}

/* GET-FROM-ICP-PORT-IF-ANY */
Object get_from_icp_port_if_any(icp_port,icp_object_index,
	    name_of_corresponding_icp_object_index_space)
    Object icp_port, icp_object_index;
    Object name_of_corresponding_icp_object_index_space;
{
    Object port, index_space_name, icp_socket, temp, temp_1, index_space;
    Object skip_list, key_value, marked, pred, curr, succ, reference;
    Object entry_hash, vector_1;
    SI_Long gensymed_symbol, temp_2, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_, index_1;
    Object result;

    x_note_fn_call(47,171);
    port = icp_port;
    if (EQ(name_of_corresponding_icp_object_index_space,
	    Qstandard_icp_object_index_space))
	index_space_name = Qstandard_icp_object_index_space;
    else if (EQ(name_of_corresponding_icp_object_index_space,
	    Qitem_index_space)) {
	icp_socket = ISVREF(port,(SI_Long)2L);
	if (Inhibit_corresponding_icp_object_making)
	    index_space_name = Qstandard_icp_object_index_space;
	else if (EQ(Qg2,ISVREF(icp_socket,(SI_Long)25L))) {
	    if (EQ(ISVREF(port,(SI_Long)3L),Qoutput))
		index_space_name = Qitem_index_space;
	    else {
		temp = ISVREF(icp_socket,(SI_Long)21L);
		temp_1 = ISVREF(icp_socket,(SI_Long)22L);
		index_space_name = IFIX(FIXNUM_MIN(temp,temp_1)) >= 
			(SI_Long)21L ? Qitem_index_space : 
			Qframe_serial_number;
	    }
	}
	else {
	    temp = ISVREF(icp_socket,(SI_Long)21L);
	    temp_1 = ISVREF(icp_socket,(SI_Long)22L);
	    index_space_name = IFIX(FIXNUM_MIN(temp,temp_1)) >= 
		    (SI_Long)10L ? Qitem_index_space : 
		    Qstandard_icp_object_index_space;
	}
    }
    else if (EQ(name_of_corresponding_icp_object_index_space,
	    Qframe_serial_number))
	index_space_name = EQ(ISVREF(port,(SI_Long)3L),Qoutput) ? 
		Qitem_index_space : Qframe_serial_number;
    else
	index_space_name = Qstandard_icp_object_index_space;
    if (EQ(index_space_name,Qstandard_icp_object_index_space))
	index_space = ISVREF(icp_port,(SI_Long)8L);
    else if (EQ(index_space_name,Qitem_index_space))
	index_space = item_index_space(icp_port);
    else if (EQ(index_space_name,Qframe_serial_number))
	index_space = frame_serial_number_to_item_table(icp_port);
    else
	index_space = Qnil;
    if (EQ(index_space_name,Qframe_serial_number)) {
	gensymed_symbol = IFIX(sxhashw(icp_object_index));
	temp_2 = gensymed_symbol % (SI_Long)67L;
	temp_1 = SVREF(index_space,FIX(temp_2));
	skip_list = CDR(temp_1);
	key_value = icp_object_index;
	key_hash_value = gensymed_symbol;
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
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_2:
	if ( !TRUEP(marked))
	    goto end_loop_1;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_2;
      end_loop_1:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
	temp_1 = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		(EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
    }
    else {
	vector_1 = ISVREF(index_space,(SI_Long)2L);
	index_1 = IFIX(icp_object_index) >>  -  - (SI_Long)10L;
	vector_1 = vector_1 && index_1 < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1)) ? 
		ISVREF(vector_1,index_1) : Qnil;
	index_1 = IFIX(icp_object_index) & (SI_Long)1023L;
	temp_1 = vector_1 && index_1 < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1)) ? 
		ISVREF(vector_1,index_1) : Qnil;
    }
    return VALUES_1(temp_1);
}

/* SET-IN-ICP-PORT */
Object set_in_icp_port(icp_port,icp_object_index,
	    name_of_corresponding_icp_object_index_space,new_value)
    Object icp_port, icp_object_index;
    Object name_of_corresponding_icp_object_index_space, new_value;
{
    Object port, index_space_name, icp_socket, temp, temp_1, index_space;
    Object svref_arg_1;
    SI_Long gensymed_symbol, temp_2, svref_arg_2;

    x_note_fn_call(47,172);
    port = icp_port;
    if (EQ(name_of_corresponding_icp_object_index_space,
	    Qstandard_icp_object_index_space))
	index_space_name = Qstandard_icp_object_index_space;
    else if (EQ(name_of_corresponding_icp_object_index_space,
	    Qitem_index_space)) {
	icp_socket = ISVREF(port,(SI_Long)2L);
	if (Inhibit_corresponding_icp_object_making)
	    index_space_name = Qstandard_icp_object_index_space;
	else if (EQ(Qg2,ISVREF(icp_socket,(SI_Long)25L))) {
	    if (EQ(ISVREF(port,(SI_Long)3L),Qoutput))
		index_space_name = Qitem_index_space;
	    else {
		temp = ISVREF(icp_socket,(SI_Long)21L);
		temp_1 = ISVREF(icp_socket,(SI_Long)22L);
		index_space_name = IFIX(FIXNUM_MIN(temp,temp_1)) >= 
			(SI_Long)21L ? Qitem_index_space : 
			Qframe_serial_number;
	    }
	}
	else {
	    temp = ISVREF(icp_socket,(SI_Long)21L);
	    temp_1 = ISVREF(icp_socket,(SI_Long)22L);
	    index_space_name = IFIX(FIXNUM_MIN(temp,temp_1)) >= 
		    (SI_Long)10L ? Qitem_index_space : 
		    Qstandard_icp_object_index_space;
	}
    }
    else if (EQ(name_of_corresponding_icp_object_index_space,
	    Qframe_serial_number))
	index_space_name = EQ(ISVREF(port,(SI_Long)3L),Qoutput) ? 
		Qitem_index_space : Qframe_serial_number;
    else
	index_space_name = Qstandard_icp_object_index_space;
    if (EQ(index_space_name,Qstandard_icp_object_index_space))
	index_space = ISVREF(icp_port,(SI_Long)8L);
    else if (EQ(index_space_name,Qitem_index_space))
	index_space = item_index_space(icp_port);
    else if (EQ(index_space_name,Qframe_serial_number))
	index_space = frame_serial_number_to_item_table(icp_port);
    else
	index_space = Qnil;
    if (EQ(index_space_name,Qframe_serial_number)) {
	gensymed_symbol = IFIX(sxhashw(icp_object_index));
	temp_2 = gensymed_symbol % (SI_Long)67L;
	temp_1 = set_skip_list_entry(SVREF(index_space,FIX(temp_2)),
		FIX((SI_Long)31L),Qeq,
		Fp_mutate_frame_serial_number_to_item_table_tree_for_hash_skip_list_entry,
		T,icp_object_index,FIX(gensymed_symbol),new_value);
    }
    else {
	if (FIXNUM_GE(icp_object_index,ISVREF(index_space,(SI_Long)4L)))
	    enlarge_index_space(index_space,icp_object_index);
	svref_arg_1 = ISVREF(ISVREF(index_space,(SI_Long)2L),
		IFIX(icp_object_index) >>  -  - (SI_Long)10L);
	svref_arg_2 = IFIX(icp_object_index) & (SI_Long)1023L;
	temp_1 = ISVREF(svref_arg_1,svref_arg_2) = new_value;
    }
    return VALUES_1(temp_1);
}

/* MAKE-ICP-PORT */
Object make_icp_port(icp_connection_handle,parent_icp_socket,
	    icp_port_direction,receive_or_transmit_directly_qm)
    Object icp_connection_handle, parent_icp_socket, icp_port_direction;
    Object receive_or_transmit_directly_qm;
{
    Object current_icp_port, icp_buffer, svref_arg_1, svref_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(47,173);
    current_icp_port = make_icp_port_structure_1(icp_connection_handle,
	    parent_icp_socket,icp_port_direction,
	    receive_or_transmit_directly_qm);
    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
	    0);
      icp_buffer = make_icp_buffer_internal_1(make_variable_fill_icp_buffer());
      svref_arg_1 = Current_icp_port;
      svref_new_value = 
	      set_up_icp_object_index_space(Qstandard_icp_object_index_space);
      SVREF(svref_arg_1,FIX((SI_Long)8L)) = svref_new_value;
      svref_arg_1 = Current_icp_port;
      SVREF(svref_arg_1,FIX((SI_Long)12L)) = icp_buffer;
      svref_arg_1 = Current_icp_port;
      SVREF(svref_arg_1,FIX((SI_Long)13L)) = icp_buffer;
      if (EQ(icp_port_direction,Qinput)) {
	  svref_arg_1 = Current_icp_port;
	  SVREF(svref_arg_1,FIX((SI_Long)4L)) = Qinitial;
      }
      result = VALUES_1(Current_icp_port);
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Do_not_reclaim_runs_while_inactive_entries, Qdo_not_reclaim_runs_while_inactive_entries);

/* RECLAIM-ICP-OBJECT-MAP */
Object reclaim_icp_object_map(icp_object,icp_object_map,
	    name_of_corresponding_icp_object_index_space)
    Object icp_object, icp_object_map;
    Object name_of_corresponding_icp_object_index_space;
{
    Object map_tail, next_map_tail, icp_port, index_1, temp;

    x_note_fn_call(47,174);
    map_tail = icp_object_map;
    next_map_tail = Nil;
    icp_port = Nil;
    index_1 = Nil;
  next_loop:
    if ( !TRUEP(map_tail))
	goto end_loop;
    next_map_tail = CDDR(map_tail);
    icp_port = CAR(map_tail);
    temp = CDR(map_tail);
    index_1 = CAR(temp);
    if ( !(Do_not_reclaim_runs_while_inactive_entries && 
	    ISVREF(ISVREF(icp_port,(SI_Long)2L),(SI_Long)48L)))
	reclaim_index_space_location_and_corresponding_objects(icp_object,
		icp_port,index_1,name_of_corresponding_icp_object_index_space);
    map_tail = next_map_tail;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* RECLAIM-ICP-PORT-ENTRY */
Object reclaim_icp_port_entry(icp_port,icp_object,icp_object_map,
	    name_of_function_to_set_object_map)
    Object icp_port, icp_object, icp_object_map;
    Object name_of_function_to_set_object_map;
{
    Object map_entry_tail, rest_of_map_entries, cddr_new_value;

    x_note_fn_call(47,175);
    map_entry_tail = Nil;
    rest_of_map_entries = icp_object_map;
  next_loop:
    if ( !TRUEP(rest_of_map_entries))
	goto end_loop;
    if (EQ(CAR(rest_of_map_entries),icp_port)) {
	if (map_entry_tail) {
	    cddr_new_value = CDDR(rest_of_map_entries);
	    M_CDDR(map_entry_tail) = cddr_new_value;
	}
	else
	    FUNCALL_2(name_of_function_to_set_object_map,icp_object,
		    CDDR(rest_of_map_entries));
	reclaim_gensym_cons_1(CDR(rest_of_map_entries));
	reclaim_gensym_cons_1(rest_of_map_entries);
	goto end_1;
    }
    map_entry_tail = rest_of_map_entries;
    rest_of_map_entries = CDDR(rest_of_map_entries);
    goto next_loop;
  end_loop:
  end_1:;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Icp_output_ports_to_flush, Qicp_output_ports_to_flush);

DEFINE_VARIABLE_WITH_SYMBOL(With_icp_buffer_coelescing_scope_qm, Qwith_icp_buffer_coelescing_scope_qm);

/* FLUSH-ICP-OUTPUT-PORTS */
Object flush_icp_output_ports()
{
    Object gensymed_symbol, aref_arg_1, ports_to_flush, icp_output_port_qm;
    Object ab_loop_list_;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;

    x_note_fn_call(47,176);
    if (Icp_output_ports_to_flush) {
	gensymed_symbol = Nil;
	gensymed_symbol_1 = 0.0;
	gensymed_symbol_2 = 0.0;
	if (Profiling_enabled_qm) {
	    gensymed_symbol = T;
	    gensymed_symbol_1 = 
		    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
		    (SI_Long)2L),(SI_Long)0L);
	    gensymed_symbol_2 = g2ext_unix_time_as_float();
	    aref_arg_1 = ISVREF(Profiling_enabled_qm,(SI_Long)2L);
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,gensymed_symbol_2);
	}
	ports_to_flush = Icp_output_ports_to_flush;
	Icp_output_ports_to_flush = Nil;
	icp_output_port_qm = Nil;
	ab_loop_list_ = ports_to_flush;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	icp_output_port_qm = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (icp_output_port_qm) {
	    SVREF(icp_output_port_qm,FIX((SI_Long)18L)) = Nil;
	    transmit_icp_output_if_ready(icp_output_port_qm,T);
	}
	goto next_loop;
      end_loop:;
	reclaim_gensym_list_1(ports_to_flush);
	if (Profiling_enabled_qm) {
	    gensymed_symbol_3 = g2ext_unix_time_as_float();
	    gensymed_symbol_4 = 
		    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
		    (SI_Long)2L),(SI_Long)0L);
	    gensymed_symbol_5 = gensymed_symbol_3 - gensymed_symbol_4;
	    aref_arg_1 = ISVREF(Profiling_enabled_qm,(SI_Long)6L);
	    aref_new_value = gensymed_symbol_5 + 
		    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
		    (SI_Long)6L),(SI_Long)0L);
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    aref_arg_1 = ISVREF(Profiling_enabled_qm,(SI_Long)2L);
	    aref_new_value = gensymed_symbol ? gensymed_symbol_1 + 
		    gensymed_symbol_5 + (gensymed_symbol_4 - 
		    gensymed_symbol_2) : gensymed_symbol_3;
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	}
    }
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Disable_resumability, Qdisable_resumability);

DEFINE_VARIABLE_WITH_SYMBOL(Resumable_icp_state, Qresumable_icp_state);

DEFINE_VARIABLE_WITH_SYMBOL(Icp_suspend, Qicp_suspend);

/* RESUMABLE-ICP-PUSH */
Object resumable_icp_push(form)
    Object form;
{
    x_note_fn_call(47,177);
    Resumable_icp_state = icp_cons_1(form,Resumable_icp_state);
    return VALUES_1(form);
}

/* RESUMABLE-ICP-POP */
Object resumable_icp_pop()
{
    Object icp_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(47,178);
    icp_pop_store = Nil;
    cons_1 = Resumable_icp_state;
    if (cons_1) {
	icp_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qicp);
	if (ISVREF(Available_icp_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_icp_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_icp_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_icp_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_icp_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Resumable_icp_state = next_cons;
    return VALUES_1(icp_pop_store);
}

static Object Qresumable_icp_list_end;  /* resumable-icp-list-end */

/* RESUMABLE-ICP-POP-LIST-IF-END-MARKER */
Object resumable_icp_pop_list_if_end_marker()
{
    Object icp_pop_store, cons_1, next_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(47,179);
    if (EQ(Qresumable_icp_list_end,CAR(Resumable_icp_state))) {
	icp_pop_store = Nil;
	cons_1 = Resumable_icp_state;
	if (cons_1) {
	    icp_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qicp);
	    if (ISVREF(Available_icp_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_icp_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = cons_1;
		temp = Available_icp_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    else {
		temp = Available_icp_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
		temp = Available_icp_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	Resumable_icp_state = next_cons;
	temp_1 = T;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Trif_block_value_alist, Qtrif_block_value_alist);

void int1_INIT()
{
    Object the_array, temp, reclaim_structure_for_socket_1;
    Object reclaim_structure_for_icp_socket_1;
    Object reclaim_structure_for_i_am_alive_info_1;
    Object reclaim_structure_for_icp_buffer_1;
    Object reclaim_structure_for_icp_port_1;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    Object AB_package, Qsuspend, Qflush_icp_output_ports, Qint1, Qicp_port;
    Object Qreclaim_structure, Qoutstanding_icp_port_count;
    Object Qicp_port_structure_memory_usage, Qutilities2, string_constant_33;
    Object Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_32, Qunique_structure_type_of_ab_name_qm;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qint2, Qicp_buffer;
    Object Qoutstanding_icp_buffer_count, Qicp_buffer_structure_memory_usage;
    Object string_constant_31, string_constant_30, string_constant_29;
    Object Qicp_buffer_ref_count_cons_memory_usage;
    Object Qoutstanding_icp_buffer_ref_count_conses, list_constant_6;
    Object Qicp_buffer_ref_count_cons_counter_vector, list_constant_5;
    Object Qavailable_icp_buffer_ref_count_conses_tail_vector;
    Object Qavailable_icp_buffer_ref_count_conses_vector;
    Object Qout_variable_fill_icp_buffer_4096_vectors;
    Object Qvariable_fill_icp_buffer_4096_vector_memory_usage;
    Object string_constant_28;
    Object Qmutate_frame_serial_number_to_item_table_tree_for_hash_skip_list_entry;
    Object Qout_frame_serial_number_to_item_table_hash_vector_67_vectors;
    Object Qframe_serial_number_to_item_table_hash_vector_67_vector_memory_usage;
    Object string_constant_27, Qi_am_alive_info;
    Object Qoutstanding_i_am_alive_info_count;
    Object Qi_am_alive_info_structure_memory_usage, string_constant_26;
    Object string_constant_25, Qbizzare_state, list_constant_28;
    Object list_constant_27, list_constant_26, list_constant_25;
    Object list_constant_24, list_constant_23, list_constant_22;
    Object list_constant_21, Qlistening, Qawaiting_acknowledgement;
    Object Qshutdown_acknowledgement_rundown, Qshutdown_requested, Qrunning;
    Object Qconnect_in_progress, Qclosed, list_constant_20, string_constant_24;
    Object Qicp_callback_cons_memory_usage, Qoutstanding_icp_callback_conses;
    Object Qicp_callback_cons_counter_vector;
    Object Qavailable_icp_callback_conses_tail_vector;
    Object Qavailable_icp_callback_conses_vector, Qicp_socket;
    Object Qoutstanding_icp_socket_count, Qicp_socket_structure_memory_usage;
    Object string_constant_23, string_constant_22, Qsocket;
    Object Qoutstanding_socket_count, Qsocket_structure_memory_usage;
    Object string_constant_21, string_constant_20, Qnative_long_icp_version;
    Object Qsupports_font_in_grid_view_icp_version;
    Object Qdialog_component_with_font_icp_version;
    Object Qcompressed_image_data_chunk_icp_version;
    Object Qtransparent_color_index_icp_version;
    Object Qremote_procedure_include_all_system_attributes_except_icp_version;
    Object Qsend_text_of_expressions_for_g2ds_icp_version;
    Object Qlong_string_icp_version, Qintern_keyword_icp_version;
    Object Qno_frame_serial_index_space_icp_version;
    Object Qdo_not_reformat_message_icp_version;
    Object Qt2_supports_item_layer_change;
    Object Qg2_supports_update_with_delete_icp_version;
    Object Qsupports_new_references_icp_version, Qno_licence_icp_version;
    Object Qgsi_sends_returned_gsi_sensor_as_reference_icp_version;
    Object Qsupports_non_resumability_icp_version;
    Object Qreturn_g2ds_version_sends_class_icp_version;
    Object Qby_copy_with_handle_supports_references_icp_version;
    Object Qdata_servers_can_run_while_inactive_version;
    Object Qindependent_layered_rendering_version;
    Object Qunsigned_short_vector_icp_version;
    Object Qderegister_icp_objects_icp_version, Qabort_icp_task_icp_version;
    Object Qacknowledge_deregister_corresponding_icp_object_icp_version;
    Object Qitem_reference_icp_version;
    Object Qgsi_dataservice_uses_full_remote_value_protocol_icp_version;
    Object Qvalues_as_handle_icp_version, Qitem_index_space_icp_version;
    Object Qderegister_original_icp_object_icp_version;
    Object Qderegister_corresponding_icp_object_index_space_name_icp_version;
    Object Qrpc_use_value_structure_using_unix_time_icp_version;
    Object Qnew_remote_procedure_identifer_protocol_icp_version;
    Object Qremote_procedure_varargs_p_icp_version;
    Object Qno_telewindows_clogging_icp_version;
    Object Qremote_procedure_include_all_system_attributes_icp_version;
    Object Qresumable_gsi_ds_icp_version;
    Object Qrel4_rpc_protocol_supports_non_objects_icp_version;
    Object Qdoes_not_require_enlarge_corresponding_icp_object_index_space_icp_version;
    Object Qvalue_vector_names_are_symbols_icp_version;
    Object Qnew_rpc_kinds_icp_version, Qresumable_icp_version;
    Object Qevaluation_sequences_and_structures_icp_version;
    Object Qsupports_optional_remote_value_tags_icp_version;
    Object Qremote_value_supports_item_icp_version;
    Object Qsupports_icp_version_protocol_icp_version;
    Object Qwriting_coalesced_icp_message_group_icp_version;
    Object Qwide_strings_icp_version, Qg2_version_reply_to_gsi_icp_version;
    Object Qnew_connect_scheme_icp_version, Qshutdown_protocol_icp_version;
    Object Qgsi_timestamp_as_float_icp_version;
    Object Qgsi_item_registration_icp_version, Qpass_item_as_copy_icp_version;
    Object Qpass_item_as_handle_icp_version;
    Object Qremote_procedure_include_attribute_icp_version;
    Object Qds_update_interval_as_float_icp_version;
    Object Qrelease_4_dot_0_icp_version, Qrelease_3_dot_0_icp_version;
    Object Qdouble_float_icp_version;
    Object Qmodify_gsi_sensor_definition_icp_version;
    Object Qreclaim_remote_corresponding_object_icp_version;
    Object Qrelease_2_dot_0_icp_version, Qrelease_1_dot_0_icp_version;
    Object Qgsi_uninitialized_context, Qgsi_undefined_context;
    Object Qlist_sys_drives_response, Qprint_native_window;
    Object Qmanage_tabular_view, Qchoose_directory, Qaccept_custom_dialog;
    Object Qnms_append_control_ex, Qspecify_text_box_extensions;
    Object Qmanage_property_grid, Qmanage_dialog, Qtabbed_mdi_mode;
    Object Qspecify_grid_view_cells, Qmanage_logbook, Qmanage_ui_properties;
    Object Qhtml_help_ex, Qsimple_dialog_ex, Qmanage_pane;
    Object Qshow_custom_dialog_ex, Qselect_tabular_view_rows;
    Object Qmanage_grid_view, Qmanage_chart_view;
    Object Qadd_ellipse_to_current_window, Qadd_polygon_to_current_window;
    Object Qmanage_shortcut_bar, Qnative_printing_ex, Qmanage_editor;
    Object Qdebugger_dialog, Qmanage_html_view, Qmanage_tree_view;
    Object Qfile_dialog_ex, Qmanage_status_bar, Qnms_modify_control;
    Object Qend_replace_tabular_view_row, Qreplace_tabular_view_cell;
    Object Qstart_replace_tabular_view_row, Qabort_dialog_query;
    Object Qfinish_dialog_query, Qadd_to_dialog_query, Qstart_dialog_query;
    Object Qdelete_tabular_view_row, Qend_add_tabular_view_row;
    Object Qadd_tabular_view_cell, Qstart_add_tabular_view_row;
    Object Qadd_tabular_view_column, Qstart_add_tabular_view;
    Object Qlist_directory_response, Qquery_custom_dialog;
    Object Qabort_dialog_update, Qend_dialog_update, Qdialog_component_update;
    Object Qstart_dialog_update, Qnms_set_theme, Qnms_delete_control;
    Object Qnms_append_control, Qnms_create_control, Qset_dialog_locked;
    Object Qadd_dialog_component_with_font, Qabort_custom_dialog;
    Object Qshow_custom_dialog, Qadd_dialog_component, Qstart_custom_dialog;
    Object Qtw_command, Qmega_refresh, Qmanage_scrollbars, Qscroll_window;
    Object Qstack_windows, Qredirect_window, Qmanage_window, Qcreate_window;
    Object Qreset_native_controls, Qmanage_native_control, Qbasic_dialog;
    Object Qmanage_progress_bar, Qmanage_native_icons;
    Object Qpaint_line_of_text_in_current_window;
    Object Qpaint_icon_in_current_window, Qnative_printing_start_page;
    Object Qnative_printing_control, Qnative_printing_dialog;
    Object Qnms_set_iconsize, Qnms_set_menu_flags, Qnms_enable_items;
    Object Qnms_append_special, Qnms_reset, Qnms_dismiss;
    Object Qnms_modify_menu_item, Qnms_enable_menu_item, Qnms_check_radio_item;
    Object Qnms_check_menu_item, Qnms_pop_up_menu, Qnms_set_menu_bar;
    Object Qnms_append_menu_item, Qnms_delete_menu, Qnms_create_menu;
    Object Qshow_window_with_geometry, Qset_window_show_status, Qhtml_help;
    Object Qfile_dialog, Qlaunch_peer_window, Qdraw_offscreen;
    Object Qadd_wide_polyline_to_current_window;
    Object Qstipple_rectangle_in_current_scratchpad_raster, Qgsi_ds;
    Object Qreset_data_server, Qstart_data_server;
    Object Qrequest_paste_availability_status;
    Object Qenable_or_disable_clipboard_polling;
    Object Qupdate_paste_availability_status;
    Object Qrequest_paste_of_cut_buffer_text, Qpaste_from_telewindows_to_g2;
    Object Qcopy_text_string_to_cut_buffer, Qrpc, Qcreate_item_reference;
    Object Qresumable_rpc_error_to_caller, Qresumable_rpc_error;
    Object Qdefine_resumable_remote_procedure_identifier, Qintern_list;
    Object Qsave_user_settings_for_telewindows, Qgsi;
    Object Qreturn_initialize_gsi_interface_status, Qinitialize_gsi_interface;
    Object Qset_telewindows_connection_license_info, Qacknowledge_shutdown;
    Object Qset_window_license_level, Qreroute_telewindow;
    Object Qshift_position_of_mouse_in_window;
    Object Qset_position_of_mouse_in_window, Qstop_mouse_tracking_in_window;
    Object Qstart_mouse_tracking_in_window, Qderegister_icp_objects;
    Object Qacknowledge_deregister_corresponding_icp_object;
    Object Qderegister_original_icp_object;
    Object Qderegister_corresponding_icp_object;
    Object Qregister_corresponding_icp_object;
    Object Qupdate_object_passing_network_resources;
    Object Qcontinue_building_resumable_object;
    Object Qshut_down_foreign_server_context, Qkill_foreign_function_server;
    Object Qsignal_foreign_function_error, Qreturn_foreign_function_value;
    Object Qcall_foreign_function, Qprovide_foreign_function_registry;
    Object Qrequest_foreign_function_registry, Qno_license;
    Object Qconnection_shutdown_imminent, Qconnection_denied;
    Object Qrelease_temporary_index_space, Qdefine_temporary_index_space;
    Object Qremote_eval, Qpaint_from_line_of_text_to_current_scratchpad_raster;
    Object Qspeedup_end_values, Qspeedup_value, Qspeedup_begin_values;
    Object Qspeedup_end_tagnames, Qspeedup_tagname;
    Object Qspeedup_input_or_output_tagnames, Qspeedup_begin_tagnames;
    Object Qabort_icp_task, Qresumable_rpc_return_values, Qresumable_rpc_call;
    Object Qresumable_rpc_start, Qresume_icp_task, Qstart_icp_task;
    Object Qrpc_acknowledge_abort, Qrpc_resume, Qrpc_suspend;
    Object Qrpc_return_values, Qrpc_synchronous_abort, Qrpc_asynchronous_abort;
    Object Qrpc_continue_from_error, Qrpc_error_to_caller, Qrpc_error;
    Object Qrpc_call, Qrpc_start, Qinitialize_server_g2ds_interface;
    Object Qdefine_remote_procedure_identifier, Qdefine_remote_procedure_name;
    Object Qdefine_color_map, Qset_window_title, Qset_scroll_info;
    Object Qsimple_dialog, Qpost_native_menu;
    Object Qpaint_clearing_rectangle_in_current_scratchpad_raster;
    Object Qset_graph_rendering_foreground_only_mode;
    Object Qpaint_icon_background_image_in_current_window, Qping_drawing_reply;
    Object Qping_drawing, Qforce_graphics_on_window;
    Object Qchange_image_palette_of_window;
    Object Qpaint_image_in_current_scratchpad_raster;
    Object Qpaint_image_in_current_window, Qimage_data_chunk;
    Object Qbegin_making_image_data;
    Object Qupdate_ring_raster_for_graph_given_color_values_2, Qi_am_alive;
    Object Qmessage_group_id, Qpaint_icon_onto_graph_raster;
    Object Qpaint_marker_onto_graph_raster, Qdelete_icp_object_for_process;
    Object Qclear_data_clipping_rectangles, Qprepare_for_painting_graph;
    Object Qupdate_ring_raster_for_graph_given_color_values;
    Object Qset_plot_pattern_to_use, Qupdate_graph_data_extrema;
    Object Qupdate_graph_dateline;
    Object Qmake_graph_rendering_structure_if_necessary;
    Object Qadd_from_graph_rendering_to_current_window;
    Object Qbegin_making_graph_rendering, Qconnection_info;
    Object Qend_simulation_output_for_cycle, Qend_simulation_input_for_cycle;
    Object Qinitialize_external_simulator;
    Object Qend_simulation_output_vector_for_object, Qsimulation_output_value;
    Object Qbegin_simulation_output_vector_for_object;
    Object Qresume_external_simulator, Qpause_external_simulator;
    Object Qshutdown_external_simulator;
    Object Qend_simulation_input_vector_for_object, Qsimulation_input_value;
    Object Qsimulation_keyword, Qbegin_simulation_input_vector_for_object;
    Object Qend_simulation_initialization_vector_for_object;
    Object Qsimulation_initialization_value;
    Object Qdefine_external_simulation_object;
    Object Qnew_externally_simulated_object, Qole;
    Object Qole_object_transfer_milestone, Qinitiate_ole_object_transfer;
    Object Qrequest_ole_object_transfer, Qprovide_ole_object_information;
    Object Qrequest_ole_object_information, Qintern_keyword;
    Object Qregion_extrema_for_stored_raster, Qbegin_making_icon_rendering;
    Object Qmake_tiling_pattern, Qadd_to_list_of_symbols;
    Object Qreceive_values_for_gsi_sensors;
    Object Qreceive_timestamped_gsi_sensor_value_vector;
    Object Qreceive_gsi_sensor_value_vector, Qdefine_gsi_interface;
    Object Qreceive_value_for_gsi_sensor_with_timestamp, Qdefine_gsi_sensor;
    Object Qstop_sending_values_for_sensors_in_list, Qsend_data_values_if_any;
    Object Qresume_data_server, Qpause_data_server, Qshut_down_data_server;
    Object Qinitialize_data_server, Qreceive_value_for_gsi_sensor;
    Object Qreceive_value_for_ping_request, Qreturn_peer_version;
    Object Qwrite_user_message_string, Qset_values_for_sensors_in_list;
    Object Qget_values_for_sensors_in_list, Qend_sensor_list;
    Object Qload_sensor_list_element, Qbegin_sensor_list;
    Object Qmodify_gsi_sensor_definition;
    Object Qpaint_filled_polygon_in_current_scratchpad_raster;
    Object Qspawn_remote_executable;
    Object Qorient_and_paint_line_of_text_to_current_scratchpad_raster;
    Object Qkill_remote_process_reply, Qremote_process_exists_p_reply;
    Object Qspawn_remote_process_reply, Qkill_remote_process;
    Object Qremote_process_exists_p, Qspawn_remote_process;
    Object Qscroll_rectangle_in_current_window, Qbeep_in_window;
    Object Qadd_from_line_of_text_to_current_window;
    Object Qcopy_from_tiling_pattern_to_current_window;
    Object Qadd_downward_sloping_line_to_current_window;
    Object Qadd_upward_sloping_line_to_current_window;
    Object Qadd_from_icon_rendering_to_current_window;
    Object Qadd_solid_rectangle_to_current_window;
    Object Qpaint_solid_rectangle_in_current_window;
    Object Qpaint_point_in_current_scratchpad_raster;
    Object Qpaint_wide_line_in_current_scratchpad_raster;
    Object Qpaint_filled_triangle_in_current_scratchpad_raster;
    Object Qpaint_arc_or_circle_in_current_scratchpad_raster;
    Object Qpaint_line_in_current_scratchpad_raster;
    Object Qpaint_solid_rectangle_in_current_scratchpad_raster;
    Object Qinitialize_scratchpad_raster, Qset_up_palette;
    Object Qbegin_window_update, Qtw, Qdefine_gensym_window;
    Object Qtelewindows_stop_mouse_tracking, Qtelewindows_start_mouse_tracking;
    Object Qextended_telewindows_workstation_event;
    Object Qtelewindows_workstation_event, Qinitialize_ntw_workstation;
    Object Qinitialize_telewindows_workstation, Qdefine_dummy_object;
    Object Qend_message_block, Qnop;
    Object Qenlarge_corresponding_icp_object_index_space, Qreset_your_memory;
    Object Qi_have_restarted, Qrestart_yourself, list_constant_19;
    Object Qpriority_for_icp_priority_category, Qview, Qdata_service, Qg2_ds;
    Object Qdefault_print_handler_for_icp_messages, list_constant_18;
    Object Qicp_value_reclaimer, Qicp_value_write_function;
    Object Qicp_value_reader_function, Qequivalent_icp_value_type;
    Object list_constant_17, Qg2ds_server_status;
    Object Qg2ds_send_data_values_if_any, Qicp_trace, list_constant_16;
    Object list_constant_15, list_constant_14, list_constant_13;
    Object list_constant_12, list_constant_11, list_constant_10;
    Object list_constant_9, list_constant_8, list_constant_7;
    Object string_constant_19, string_constant_18, string_constant_17;
    Object string_constant_16, string_constant_15, string_constant_14;
    Object string_constant_13, string_constant_12;
    Object Qfunction_for_icp_value_writer_qm;
    Object Qfunction_for_icp_value_reader_qm, string_constant_11;
    Object Qblank_traced_icp_byte_column, string_constant_10;
    Object Qicp_cons_memory_usage, Qoutstanding_icp_conses;
    Object Qicp_cons_counter_vector, Qmake_thread_array, Kfuncall;
    Object Qavailable_icp_conses_tail_vector, Qavailable_icp_conses_vector;

    x_note_fn_call(47,180);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qavailable_icp_conses = STATIC_SYMBOL("AVAILABLE-ICP-CONSES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_icp_conses,Available_icp_conses);
    Qint1 = STATIC_SYMBOL("INT1",AB_package);
    record_system_variable(Qavailable_icp_conses,Qint1,Nil,Qnil,Qt,Qnil,Qnil);
    Qavailable_icp_conses_tail = STATIC_SYMBOL("AVAILABLE-ICP-CONSES-TAIL",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_icp_conses_tail,
	    Available_icp_conses_tail);
    record_system_variable(Qavailable_icp_conses_tail,Qint1,Nil,Qnil,Qt,
	    Qnil,Qnil);
    Qavailable_icp_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-ICP-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_icp_conses_vector,
	    Available_icp_conses_vector);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_thread_array = STATIC_SYMBOL("MAKE-THREAD-ARRAY",AB_package);
    list_constant_5 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    Qnil);
    record_system_variable(Qavailable_icp_conses_vector,Qint1,
	    list_constant_5,Qnil,Qt,Qnil,Qnil);
    Qavailable_icp_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-ICP-CONSES-TAIL-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_icp_conses_tail_vector,
	    Available_icp_conses_tail_vector);
    record_system_variable(Qavailable_icp_conses_tail_vector,Qint1,
	    list_constant_5,Qnil,Qt,Qnil,Qnil);
    Qicp_cons_counter_vector = STATIC_SYMBOL("ICP-CONS-COUNTER-VECTOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qicp_cons_counter_vector,
	    Icp_cons_counter_vector);
    list_constant_6 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    FIX((SI_Long)0L));
    record_system_variable(Qicp_cons_counter_vector,Qint1,list_constant_6,
	    Qnil,Qt,Qnil,Qnil);
    Qicp_cons_counter = STATIC_SYMBOL("ICP-CONS-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qicp_cons_counter,Icp_cons_counter);
    record_system_variable(Qicp_cons_counter,Qint1,FIX((SI_Long)0L),Qnil,
	    Qt,Qnil,Qnil);
    Qoutstanding_icp_conses = STATIC_SYMBOL("OUTSTANDING-ICP-CONSES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_icp_conses,
	    STATIC_FUNCTION(outstanding_icp_conses,NIL,FALSE,0,0));
    Qicp_cons_memory_usage = STATIC_SYMBOL("ICP-CONS-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qicp_cons_memory_usage,
	    STATIC_FUNCTION(icp_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_10 = STATIC_STRING("1q83-Yoy9k83-Yny09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_icp_conses);
    push_optimized_constant(Qicp_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_10));
    Qicp = STATIC_SYMBOL("ICP",AB_package);
    Qblank_traced_icp_byte_column = 
	    STATIC_SYMBOL("BLANK-TRACED-ICP-BYTE-COLUMN",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qblank_traced_icp_byte_column,
	    Blank_traced_icp_byte_column);
    string_constant_11 = STATIC_STRING("|  ");
    SET_SYMBOL_VALUE(Qblank_traced_icp_byte_column,string_constant_11);
    if (Trace_skip_data_service_i_am_alive_messages_p == UNBOUND)
	Trace_skip_data_service_i_am_alive_messages_p = Nil;
    if (Icp_trace_print_message_series_p == UNBOUND)
	Icp_trace_print_message_series_p = T;
    Qfunction_for_icp_value_reader_qm = 
	    STATIC_SYMBOL("FUNCTION-FOR-ICP-VALUE-READER\?",AB_package);
    Function_for_icp_value_reader_qm_prop = Qfunction_for_icp_value_reader_qm;
    if (Icp_read_trace_cutoff_level_qm == UNBOUND)
	Icp_read_trace_cutoff_level_qm = Nil;
    if (Current_icp_read_trace_level == UNBOUND)
	Current_icp_read_trace_level = FIX((SI_Long)0L);
    Qmessage_series = STATIC_SYMBOL("MESSAGE-SERIES",AB_package);
    string_constant = STATIC_STRING("");
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_1 = STATIC_STRING("~a");
    string_constant_2 = STATIC_STRING("~&~areading ~a~@[ ~a~]~%");
    string_constant_3 = STATIC_STRING("~&~a~a ~a~@[ ~a~]~:[~;: ~s~]~%");
    Qfunction_for_icp_value_writer_qm = 
	    STATIC_SYMBOL("FUNCTION-FOR-ICP-VALUE-WRITER\?",AB_package);
    Function_for_icp_value_writer_qm_prop = Qfunction_for_icp_value_writer_qm;
    if (Icp_write_trace_cutoff_level_qm == UNBOUND)
	Icp_write_trace_cutoff_level_qm = Nil;
    if (Current_icp_write_trace_level == UNBOUND)
	Current_icp_write_trace_level = FIX((SI_Long)0L);
    string_constant_4 = STATIC_STRING("~&~awriting ~a~@[ ~a~]~:[~;: ~s~]~%");
    string_constant_12 = STATIC_STRING("No tracing");
    list_constant_7 = STATIC_CONS(Qnil,string_constant_12);
    string_constant_13 = 
	    STATIC_STRING("Code will take tracing branches, but will not print trace messages");
    list_constant_8 = STATIC_CONS(FIX((SI_Long)0L),string_constant_13);
    string_constant_14 = STATIC_STRING("Message series will be traced");
    list_constant_9 = STATIC_CONS(FIX((SI_Long)1L),string_constant_14);
    string_constant_15 = STATIC_STRING("Messages will be traced");
    list_constant_10 = STATIC_CONS(FIX((SI_Long)2L),string_constant_15);
    string_constant_16 = 
	    STATIC_STRING("Message argument names will be traced");
    list_constant_11 = STATIC_CONS(FIX((SI_Long)3L),string_constant_16);
    string_constant_17 = 
	    STATIC_STRING("Top-level message values will be traced");
    list_constant_12 = STATIC_CONS(FIX((SI_Long)4L),string_constant_17);
    Qetc = STATIC_SYMBOL("ETC",AB_package);
    string_constant_18 = 
	    STATIC_STRING("Embedded message values will be traced");
    list_constant_13 = STATIC_CONS(Qetc,string_constant_18);
    string_constant_19 = STATIC_STRING("All levels will be traced");
    list_constant_14 = STATIC_CONS(Qt,string_constant_19);
    list_constant_15 = STATIC_LIST((SI_Long)8L,list_constant_7,
	    list_constant_8,list_constant_9,list_constant_10,
	    list_constant_11,list_constant_12,list_constant_13,
	    list_constant_14);
    if (Icp_trace_level_descriptions == UNBOUND)
	Icp_trace_level_descriptions = list_constant_15;
    list_constant_16 = STATIC_CONS(Qnil,Qnil);
    list_constant = STATIC_CONS(Qt,list_constant_16);
    Qsame = STATIC_SYMBOL("SAME",AB_package);
    Qqm = STATIC_SYMBOL("\?",AB_package);
    string_constant_5 = STATIC_STRING("read");
    QREAD = STATIC_SYMBOL("read",AB_package);
    string_constant_6 = STATIC_STRING("write");
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qsame,Qqm);
    Qicp_trace = STATIC_SYMBOL("ICP-TRACE",AB_package);
    SET_SYMBOL_FUNCTION(Qicp_trace,STATIC_FUNCTION(icp_trace,NIL,FALSE,2,2));
    Qicp_log_intensity = STATIC_SYMBOL("ICP-LOG-INTENSITY",AB_package);
    string_constant_7 = string_appendn(3,
	    STATIC_STRING("Specified icp-log-intensity option value may be an integer from 0 to 6:~%~%\n        0: Code will take tracing branches, but will not print trace messages~%\n        1: Message "),
	    STATIC_STRING("series will be traced~%\n        2: Messages will be traced~%\n        3: Message argument names will be traced~%\n        4: Top-level message values will be traced~%\n        5:"),
	    STATIC_STRING(" Embedded message values will be traced~%\n        6: All levels will be traced~%~%\n        Assuming no tracing~%"));
    Qi_am_alive = STATIC_SYMBOL("I-AM-ALIVE",AB_package);
    Qmessage_group_id = STATIC_SYMBOL("MESSAGE-GROUP-ID",AB_package);
    Qg2ds_send_data_values_if_any = 
	    STATIC_SYMBOL("G2DS-SEND-DATA-VALUES-IF-ANY",AB_package);
    Qg2ds_server_status = STATIC_SYMBOL("G2DS-SERVER-STATUS",AB_package);
    list_constant_17 = STATIC_LIST((SI_Long)4L,Qi_am_alive,
	    Qmessage_group_id,Qg2ds_send_data_values_if_any,
	    Qg2ds_server_status);
    Data_service_i_am_alive_messages = list_constant_17;
    Qequivalent_icp_value_type = STATIC_SYMBOL("EQUIVALENT-ICP-VALUE-TYPE",
	    AB_package);
    Equivalent_icp_value_type_prop = Qequivalent_icp_value_type;
    Qicp_value_reader_function = STATIC_SYMBOL("ICP-VALUE-READER-FUNCTION",
	    AB_package);
    Icp_value_reader_function_prop = Qicp_value_reader_function;
    Qicp_value_write_function = STATIC_SYMBOL("ICP-VALUE-WRITE-FUNCTION",
	    AB_package);
    Icp_value_write_function_prop = Qicp_value_write_function;
    Qicp_value_reclaimer = STATIC_SYMBOL("ICP-VALUE-RECLAIMER",AB_package);
    Icp_value_reclaimer_prop = Qicp_value_reclaimer;
    Qname_of_corresponding_icp_object_index_space = 
	    STATIC_SYMBOL("NAME-OF-CORRESPONDING-ICP-OBJECT-INDEX-SPACE",
	    AB_package);
    Name_of_corresponding_icp_object_index_space_prop = 
	    Qname_of_corresponding_icp_object_index_space;
    Qaccess_form_for_corresponding_icp_object_map = 
	    STATIC_SYMBOL("ACCESS-FORM-FOR-CORRESPONDING-ICP-OBJECT-MAP",
	    AB_package);
    Access_form_for_corresponding_icp_object_map_prop = 
	    Qaccess_form_for_corresponding_icp_object_map;
    Qreclaimer_for_icp_port_entry = 
	    STATIC_SYMBOL("RECLAIMER-FOR-ICP-PORT-ENTRY",AB_package);
    Reclaimer_for_icp_port_entry_prop = Qreclaimer_for_icp_port_entry;
    Qreclaimer_for_icp_object = STATIC_SYMBOL("RECLAIMER-FOR-ICP-OBJECT",
	    AB_package);
    Reclaimer_for_icp_object_prop = Qreclaimer_for_icp_object;
    Qshutdown_reclaimer_for_icp_object = 
	    STATIC_SYMBOL("SHUTDOWN-RECLAIMER-FOR-ICP-OBJECT",AB_package);
    Shutdown_reclaimer_for_icp_object_prop = 
	    Qshutdown_reclaimer_for_icp_object;
    Qdelete_corresponding_object_qm = 
	    STATIC_SYMBOL("DELETE-CORRESPONDING-OBJECT\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdelete_corresponding_object_qm,
	    Delete_corresponding_object_qm);
    record_system_variable(Qdelete_corresponding_object_qm,Qint1,T,Qnil,
	    Qnil,Qnil,Qnil);
    Qderegister_corresponding_object_qm = 
	    STATIC_SYMBOL("DEREGISTER-CORRESPONDING-OBJECT\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qderegister_corresponding_object_qm,
	    Deregister_corresponding_object_qm);
    record_system_variable(Qderegister_corresponding_object_qm,Qint1,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qitem_index_space = STATIC_SYMBOL("ITEM-INDEX-SPACE",AB_package);
    Qstandard_icp_object_index_space = 
	    STATIC_SYMBOL("STANDARD-ICP-OBJECT-INDEX-SPACE",AB_package);
    list_constant_18 = STATIC_LIST((SI_Long)2L,Qitem_index_space,
	    Qstandard_icp_object_index_space);
    if (All_index_space_names == UNBOUND)
	All_index_space_names = list_constant_18;
    if (Inhibit_corresponding_icp_object_making == UNBOUND)
	Inhibit_corresponding_icp_object_making = Nil;
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    Qregistered_item = STATIC_SYMBOL("REGISTERED-ITEM",AB_package);
    Qfont_map = STATIC_SYMBOL("FONT-MAP",AB_package);
    if (Icp_message_handler_array == UNBOUND) {
	gensymed_symbol = (SI_Long)750L;
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
	Icp_message_handler_array = the_array;
    }
    if (Icp_message_handler_name_array == UNBOUND) {
	gensymed_symbol = (SI_Long)750L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop_1;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
	Icp_message_handler_name_array = the_array;
    }
    Qdefault_print_handler_for_icp_messages = 
	    STATIC_SYMBOL("DEFAULT-PRINT-HANDLER-FOR-ICP-MESSAGES",AB_package);
    if (Icp_printing_message_handler_array == UNBOUND)
	Icp_printing_message_handler_array = make_array(3,
		FIX((SI_Long)750L),Kinitial_element,
		Qdefault_print_handler_for_icp_messages);
    Qicp_message_type_code = STATIC_SYMBOL("ICP-MESSAGE-TYPE-CODE",AB_package);
    Icp_message_type_code_prop = Qicp_message_type_code;
    Qpriority_for_icp_priority_category = 
	    STATIC_SYMBOL("PRIORITY-FOR-ICP-PRIORITY-CATEGORY",AB_package);
    Priority_for_icp_priority_category_prop = 
	    Qpriority_for_icp_priority_category;
    Qicp_priority_category_for_message = 
	    STATIC_SYMBOL("ICP-PRIORITY-CATEGORY-FOR-MESSAGE",AB_package);
    Icp_priority_category_for_message_prop = 
	    Qicp_priority_category_for_message;
    mutate_global_property(Qicp,Qicp,Qpriority_for_icp_priority_category);
    mutate_global_property(Qi_am_alive,Qi_am_alive,
	    Qpriority_for_icp_priority_category);
    Qrpc = STATIC_SYMBOL("RPC",AB_package);
    mutate_global_property(Qrpc,Qrpc,Qpriority_for_icp_priority_category);
    Qgsi = STATIC_SYMBOL("GSI",AB_package);
    mutate_global_property(Qgsi,Qgsi,Qpriority_for_icp_priority_category);
    Qgsi_ds = STATIC_SYMBOL("GSI-DS",AB_package);
    Qdata_service = STATIC_SYMBOL("DATA-SERVICE",AB_package);
    mutate_global_property(Qgsi_ds,Qdata_service,
	    Qpriority_for_icp_priority_category);
    Qg2_ds = STATIC_SYMBOL("G2-DS",AB_package);
    mutate_global_property(Qg2_ds,Qdata_service,
	    Qpriority_for_icp_priority_category);
    Qtw = STATIC_SYMBOL("TW",AB_package);
    mutate_global_property(Qtw,Qtw,Qpriority_for_icp_priority_category);
    Qgspan = STATIC_SYMBOL("GSPAN",AB_package);
    mutate_global_property(Qgspan,Qgspan,Qpriority_for_icp_priority_category);
    Qview = STATIC_SYMBOL("VIEW",AB_package);
    mutate_global_property(Qview,Qview,Qpriority_for_icp_priority_category);
    Qole = STATIC_SYMBOL("OLE",AB_package);
    mutate_global_property(Qole,Qole,Qpriority_for_icp_priority_category);
    Qstart_icp_task = STATIC_SYMBOL("START-ICP-TASK",AB_package);
    Qresume_icp_task = STATIC_SYMBOL("RESUME-ICP-TASK",AB_package);
    list_constant_19 = STATIC_LIST((SI_Long)6L,Qicp,Qstart_icp_task,
	    Qresume_icp_task,Qrpc,Qgsi,Qgsi_ds);
    if (Icp_priority_categories_for_gsi == UNBOUND)
	Icp_priority_categories_for_gsi = list_constant_19;
    Qrestart_yourself = STATIC_SYMBOL("RESTART-YOURSELF",AB_package);
    add_icp_message_type_code(Qrestart_yourself,FIX((SI_Long)11L),Qnil);
    Qi_have_restarted = STATIC_SYMBOL("I-HAVE-RESTARTED",AB_package);
    add_icp_message_type_code(Qi_have_restarted,FIX((SI_Long)12L),Qnil);
    Qreset_your_memory = STATIC_SYMBOL("RESET-YOUR-MEMORY",AB_package);
    add_icp_message_type_code(Qreset_your_memory,FIX((SI_Long)13L),Qnil);
    add_icp_message_type_code(Qi_am_alive,FIX((SI_Long)14L),Qi_am_alive);
    Qenlarge_corresponding_icp_object_index_space = 
	    STATIC_SYMBOL("ENLARGE-CORRESPONDING-ICP-OBJECT-INDEX-SPACE",
	    AB_package);
    add_icp_message_type_code(Qenlarge_corresponding_icp_object_index_space,
	    FIX((SI_Long)15L),Qrpc);
    Qnop = STATIC_SYMBOL("NOP",AB_package);
    add_icp_message_type_code(Qnop,FIX((SI_Long)16L),Qicp);
    Qend_message_block = STATIC_SYMBOL("END-MESSAGE-BLOCK",AB_package);
    add_icp_message_type_code(Qend_message_block,FIX((SI_Long)17L),Qicp);
    Qdefine_dummy_object = STATIC_SYMBOL("DEFINE-DUMMY-OBJECT",AB_package);
    add_icp_message_type_code(Qdefine_dummy_object,FIX((SI_Long)18L),Qnil);
    Qinitialize_telewindows_workstation = 
	    STATIC_SYMBOL("INITIALIZE-TELEWINDOWS-WORKSTATION",AB_package);
    add_icp_message_type_code(Qinitialize_telewindows_workstation,
	    FIX((SI_Long)19L),Qtw);
    Qinitialize_ntw_workstation = 
	    STATIC_SYMBOL("INITIALIZE-NTW-WORKSTATION",AB_package);
    add_icp_message_type_code(Qinitialize_ntw_workstation,
	    FIX((SI_Long)405L),Qtw);
    Qtelewindows_workstation_event = 
	    STATIC_SYMBOL("TELEWINDOWS-WORKSTATION-EVENT",AB_package);
    add_icp_message_type_code(Qtelewindows_workstation_event,
	    FIX((SI_Long)24L),Qtw);
    Qextended_telewindows_workstation_event = 
	    STATIC_SYMBOL("EXTENDED-TELEWINDOWS-WORKSTATION-EVENT",AB_package);
    add_icp_message_type_code(Qextended_telewindows_workstation_event,
	    FIX((SI_Long)25L),Qnil);
    Qtelewindows_start_mouse_tracking = 
	    STATIC_SYMBOL("TELEWINDOWS-START-MOUSE-TRACKING",AB_package);
    add_icp_message_type_code(Qtelewindows_start_mouse_tracking,
	    FIX((SI_Long)26L),Qtw);
    Qtelewindows_stop_mouse_tracking = 
	    STATIC_SYMBOL("TELEWINDOWS-STOP-MOUSE-TRACKING",AB_package);
    add_icp_message_type_code(Qtelewindows_stop_mouse_tracking,
	    FIX((SI_Long)27L),Qtw);
    Qdefine_gensym_window = STATIC_SYMBOL("DEFINE-GENSYM-WINDOW",AB_package);
    add_icp_message_type_code(Qdefine_gensym_window,FIX((SI_Long)30L),Qtw);
    Qbegin_window_update = STATIC_SYMBOL("BEGIN-WINDOW-UPDATE",AB_package);
    add_icp_message_type_code(Qbegin_window_update,FIX((SI_Long)21L),Qnil);
    Qset_up_palette = STATIC_SYMBOL("SET-UP-PALETTE",AB_package);
    add_icp_message_type_code(Qset_up_palette,FIX((SI_Long)23L),Qnil);
    Qinitialize_scratchpad_raster = 
	    STATIC_SYMBOL("INITIALIZE-SCRATCHPAD-RASTER",AB_package);
    add_icp_message_type_code(Qinitialize_scratchpad_raster,
	    FIX((SI_Long)31L),Qnil);
    Qpaint_solid_rectangle_in_current_scratchpad_raster = 
	    STATIC_SYMBOL("PAINT-SOLID-RECTANGLE-IN-CURRENT-SCRATCHPAD-RASTER",
	    AB_package);
    add_icp_message_type_code(Qpaint_solid_rectangle_in_current_scratchpad_raster,
	    FIX((SI_Long)32L),Qnil);
    Qpaint_line_in_current_scratchpad_raster = 
	    STATIC_SYMBOL("PAINT-LINE-IN-CURRENT-SCRATCHPAD-RASTER",
	    AB_package);
    add_icp_message_type_code(Qpaint_line_in_current_scratchpad_raster,
	    FIX((SI_Long)33L),Qnil);
    Qpaint_arc_or_circle_in_current_scratchpad_raster = 
	    STATIC_SYMBOL("PAINT-ARC-OR-CIRCLE-IN-CURRENT-SCRATCHPAD-RASTER",
	    AB_package);
    add_icp_message_type_code(Qpaint_arc_or_circle_in_current_scratchpad_raster,
	    FIX((SI_Long)34L),Qnil);
    Qpaint_filled_triangle_in_current_scratchpad_raster = 
	    STATIC_SYMBOL("PAINT-FILLED-TRIANGLE-IN-CURRENT-SCRATCHPAD-RASTER",
	    AB_package);
    add_icp_message_type_code(Qpaint_filled_triangle_in_current_scratchpad_raster,
	    FIX((SI_Long)35L),Qnil);
    Qpaint_wide_line_in_current_scratchpad_raster = 
	    STATIC_SYMBOL("PAINT-WIDE-LINE-IN-CURRENT-SCRATCHPAD-RASTER",
	    AB_package);
    add_icp_message_type_code(Qpaint_wide_line_in_current_scratchpad_raster,
	    FIX((SI_Long)36L),Qnil);
    Qpaint_point_in_current_scratchpad_raster = 
	    STATIC_SYMBOL("PAINT-POINT-IN-CURRENT-SCRATCHPAD-RASTER",
	    AB_package);
    add_icp_message_type_code(Qpaint_point_in_current_scratchpad_raster,
	    FIX((SI_Long)37L),Qnil);
    Qpaint_solid_rectangle_in_current_window = 
	    STATIC_SYMBOL("PAINT-SOLID-RECTANGLE-IN-CURRENT-WINDOW",
	    AB_package);
    add_icp_message_type_code(Qpaint_solid_rectangle_in_current_window,
	    FIX((SI_Long)41L),Qnil);
    Qadd_solid_rectangle_to_current_window = 
	    STATIC_SYMBOL("ADD-SOLID-RECTANGLE-TO-CURRENT-WINDOW",AB_package);
    add_icp_message_type_code(Qadd_solid_rectangle_to_current_window,
	    FIX((SI_Long)42L),Qnil);
    Qadd_from_icon_rendering_to_current_window = 
	    STATIC_SYMBOL("ADD-FROM-ICON-RENDERING-TO-CURRENT-WINDOW",
	    AB_package);
    add_icp_message_type_code(Qadd_from_icon_rendering_to_current_window,
	    FIX((SI_Long)43L),Qnil);
    Qadd_upward_sloping_line_to_current_window = 
	    STATIC_SYMBOL("ADD-UPWARD-SLOPING-LINE-TO-CURRENT-WINDOW",
	    AB_package);
    add_icp_message_type_code(Qadd_upward_sloping_line_to_current_window,
	    FIX((SI_Long)44L),Qnil);
    Qadd_downward_sloping_line_to_current_window = 
	    STATIC_SYMBOL("ADD-DOWNWARD-SLOPING-LINE-TO-CURRENT-WINDOW",
	    AB_package);
    add_icp_message_type_code(Qadd_downward_sloping_line_to_current_window,
	    FIX((SI_Long)45L),Qnil);
    Qcopy_from_tiling_pattern_to_current_window = 
	    STATIC_SYMBOL("COPY-FROM-TILING-PATTERN-TO-CURRENT-WINDOW",
	    AB_package);
    add_icp_message_type_code(Qcopy_from_tiling_pattern_to_current_window,
	    FIX((SI_Long)46L),Qnil);
    Qadd_from_line_of_text_to_current_window = 
	    STATIC_SYMBOL("ADD-FROM-LINE-OF-TEXT-TO-CURRENT-WINDOW",
	    AB_package);
    add_icp_message_type_code(Qadd_from_line_of_text_to_current_window,
	    FIX((SI_Long)47L),Qnil);
    Qbeep_in_window = STATIC_SYMBOL("BEEP-IN-WINDOW",AB_package);
    add_icp_message_type_code(Qbeep_in_window,FIX((SI_Long)48L),Qnil);
    Qscroll_rectangle_in_current_window = 
	    STATIC_SYMBOL("SCROLL-RECTANGLE-IN-CURRENT-WINDOW",AB_package);
    add_icp_message_type_code(Qscroll_rectangle_in_current_window,
	    FIX((SI_Long)49L),Qnil);
    Qspawn_remote_process = STATIC_SYMBOL("SPAWN-REMOTE-PROCESS",AB_package);
    add_icp_message_type_code(Qspawn_remote_process,FIX((SI_Long)50L),Qnil);
    Qremote_process_exists_p = STATIC_SYMBOL("REMOTE-PROCESS-EXISTS-P",
	    AB_package);
    add_icp_message_type_code(Qremote_process_exists_p,FIX((SI_Long)51L),Qnil);
    Qkill_remote_process = STATIC_SYMBOL("KILL-REMOTE-PROCESS",AB_package);
    add_icp_message_type_code(Qkill_remote_process,FIX((SI_Long)52L),Qnil);
    Qspawn_remote_process_reply = 
	    STATIC_SYMBOL("SPAWN-REMOTE-PROCESS-REPLY",AB_package);
    add_icp_message_type_code(Qspawn_remote_process_reply,
	    FIX((SI_Long)53L),Qnil);
    Qremote_process_exists_p_reply = 
	    STATIC_SYMBOL("REMOTE-PROCESS-EXISTS-P-REPLY",AB_package);
    add_icp_message_type_code(Qremote_process_exists_p_reply,
	    FIX((SI_Long)54L),Qnil);
    Qkill_remote_process_reply = STATIC_SYMBOL("KILL-REMOTE-PROCESS-REPLY",
	    AB_package);
    add_icp_message_type_code(Qkill_remote_process_reply,FIX((SI_Long)55L),
	    Qnil);
    Qorient_and_paint_line_of_text_to_current_scratchpad_raster = 
	    STATIC_SYMBOL("ORIENT-AND-PAINT-LINE-OF-TEXT-TO-CURRENT-SCRATCHPAD-RASTER",
	    AB_package);
    add_icp_message_type_code(Qorient_and_paint_line_of_text_to_current_scratchpad_raster,
	    FIX((SI_Long)56L),Qnil);
    Qspawn_remote_executable = STATIC_SYMBOL("SPAWN-REMOTE-EXECUTABLE",
	    AB_package);
    add_icp_message_type_code(Qspawn_remote_executable,FIX((SI_Long)57L),Qnil);
    Qpaint_filled_polygon_in_current_scratchpad_raster = 
	    STATIC_SYMBOL("PAINT-FILLED-POLYGON-IN-CURRENT-SCRATCHPAD-RASTER",
	    AB_package);
    add_icp_message_type_code(Qpaint_filled_polygon_in_current_scratchpad_raster,
	    FIX((SI_Long)58L),Qnil);
    Qmodify_gsi_sensor_definition = 
	    STATIC_SYMBOL("MODIFY-GSI-SENSOR-DEFINITION",AB_package);
    add_icp_message_type_code(Qmodify_gsi_sensor_definition,
	    FIX((SI_Long)59L),Qgsi_ds);
    Qbegin_sensor_list = STATIC_SYMBOL("BEGIN-SENSOR-LIST",AB_package);
    add_icp_message_type_code(Qbegin_sensor_list,FIX((SI_Long)60L),Qgsi_ds);
    Qload_sensor_list_element = STATIC_SYMBOL("LOAD-SENSOR-LIST-ELEMENT",
	    AB_package);
    add_icp_message_type_code(Qload_sensor_list_element,FIX((SI_Long)61L),
	    Qgsi_ds);
    Qend_sensor_list = STATIC_SYMBOL("END-SENSOR-LIST",AB_package);
    add_icp_message_type_code(Qend_sensor_list,FIX((SI_Long)62L),Qgsi_ds);
    Qget_values_for_sensors_in_list = 
	    STATIC_SYMBOL("GET-VALUES-FOR-SENSORS-IN-LIST",AB_package);
    add_icp_message_type_code(Qget_values_for_sensors_in_list,
	    FIX((SI_Long)63L),Qgsi_ds);
    Qset_values_for_sensors_in_list = 
	    STATIC_SYMBOL("SET-VALUES-FOR-SENSORS-IN-LIST",AB_package);
    add_icp_message_type_code(Qset_values_for_sensors_in_list,
	    FIX((SI_Long)64L),Qgsi_ds);
    Qwrite_user_message_string = STATIC_SYMBOL("WRITE-USER-MESSAGE-STRING",
	    AB_package);
    add_icp_message_type_code(Qwrite_user_message_string,FIX((SI_Long)65L),
	    Qgsi);
    Qreturn_peer_version = STATIC_SYMBOL("RETURN-PEER-VERSION",AB_package);
    add_icp_message_type_code(Qreturn_peer_version,FIX((SI_Long)66L),Qgsi);
    Qreceive_value_for_ping_request = 
	    STATIC_SYMBOL("RECEIVE-VALUE-FOR-PING-REQUEST",AB_package);
    add_icp_message_type_code(Qreceive_value_for_ping_request,
	    FIX((SI_Long)67L),Qgsi_ds);
    Qreceive_value_for_gsi_sensor = 
	    STATIC_SYMBOL("RECEIVE-VALUE-FOR-GSI-SENSOR",AB_package);
    add_icp_message_type_code(Qreceive_value_for_gsi_sensor,
	    FIX((SI_Long)68L),Qgsi_ds);
    Qinitialize_data_server = STATIC_SYMBOL("INITIALIZE-DATA-SERVER",
	    AB_package);
    add_icp_message_type_code(Qinitialize_data_server,FIX((SI_Long)69L),
	    Qgsi_ds);
    Qshut_down_data_server = STATIC_SYMBOL("SHUT-DOWN-DATA-SERVER",AB_package);
    add_icp_message_type_code(Qshut_down_data_server,FIX((SI_Long)70L),Qicp);
    Qpause_data_server = STATIC_SYMBOL("PAUSE-DATA-SERVER",AB_package);
    add_icp_message_type_code(Qpause_data_server,FIX((SI_Long)71L),Qgsi_ds);
    Qresume_data_server = STATIC_SYMBOL("RESUME-DATA-SERVER",AB_package);
    add_icp_message_type_code(Qresume_data_server,FIX((SI_Long)72L),Qgsi_ds);
    Qsend_data_values_if_any = STATIC_SYMBOL("SEND-DATA-VALUES-IF-ANY",
	    AB_package);
    add_icp_message_type_code(Qsend_data_values_if_any,FIX((SI_Long)73L),Qgsi);
    Qstop_sending_values_for_sensors_in_list = 
	    STATIC_SYMBOL("STOP-SENDING-VALUES-FOR-SENSORS-IN-LIST",
	    AB_package);
    add_icp_message_type_code(Qstop_sending_values_for_sensors_in_list,
	    FIX((SI_Long)74L),Qgsi_ds);
    Qdefine_gsi_sensor = STATIC_SYMBOL("DEFINE-GSI-SENSOR",AB_package);
    add_icp_message_type_code(Qdefine_gsi_sensor,FIX((SI_Long)75L),Qgsi_ds);
    Qreceive_value_for_gsi_sensor_with_timestamp = 
	    STATIC_SYMBOL("RECEIVE-VALUE-FOR-GSI-SENSOR-WITH-TIMESTAMP",
	    AB_package);
    add_icp_message_type_code(Qreceive_value_for_gsi_sensor_with_timestamp,
	    FIX((SI_Long)76L),Qgsi_ds);
    Qdefine_gsi_interface = STATIC_SYMBOL("DEFINE-GSI-INTERFACE",AB_package);
    add_icp_message_type_code(Qdefine_gsi_interface,FIX((SI_Long)77L),Qgsi_ds);
    Qreceive_gsi_sensor_value_vector = 
	    STATIC_SYMBOL("RECEIVE-GSI-SENSOR-VALUE-VECTOR",AB_package);
    add_icp_message_type_code(Qreceive_gsi_sensor_value_vector,
	    FIX((SI_Long)78L),Qgsi_ds);
    Qreceive_timestamped_gsi_sensor_value_vector = 
	    STATIC_SYMBOL("RECEIVE-TIMESTAMPED-GSI-SENSOR-VALUE-VECTOR",
	    AB_package);
    add_icp_message_type_code(Qreceive_timestamped_gsi_sensor_value_vector,
	    FIX((SI_Long)79L),Qgsi_ds);
    Qreceive_values_for_gsi_sensors = 
	    STATIC_SYMBOL("RECEIVE-VALUES-FOR-GSI-SENSORS",AB_package);
    add_icp_message_type_code(Qreceive_values_for_gsi_sensors,
	    FIX((SI_Long)80L),Qgsi_ds);
    add_icp_message_type_code(Qintern,FIX((SI_Long)81L),Qrpc);
    Qadd_to_list_of_symbols = STATIC_SYMBOL("ADD-TO-LIST-OF-SYMBOLS",
	    AB_package);
    add_icp_message_type_code(Qadd_to_list_of_symbols,FIX((SI_Long)82L),Qrpc);
    Qmake_tiling_pattern = STATIC_SYMBOL("MAKE-TILING-PATTERN",AB_package);
    add_icp_message_type_code(Qmake_tiling_pattern,FIX((SI_Long)83L),Qnil);
    Qbegin_making_icon_rendering = 
	    STATIC_SYMBOL("BEGIN-MAKING-ICON-RENDERING",AB_package);
    add_icp_message_type_code(Qbegin_making_icon_rendering,
	    FIX((SI_Long)84L),Qnil);
    Qregion_extrema_for_stored_raster = 
	    STATIC_SYMBOL("REGION-EXTREMA-FOR-STORED-RASTER",AB_package);
    add_icp_message_type_code(Qregion_extrema_for_stored_raster,
	    FIX((SI_Long)85L),Qnil);
    Qintern_keyword = STATIC_SYMBOL("INTERN-KEYWORD",AB_package);
    add_icp_message_type_code(Qintern_keyword,FIX((SI_Long)86L),Qrpc);
    Qrequest_ole_object_information = 
	    STATIC_SYMBOL("REQUEST-OLE-OBJECT-INFORMATION",AB_package);
    add_icp_message_type_code(Qrequest_ole_object_information,
	    FIX((SI_Long)100L),Qole);
    Qprovide_ole_object_information = 
	    STATIC_SYMBOL("PROVIDE-OLE-OBJECT-INFORMATION",AB_package);
    add_icp_message_type_code(Qprovide_ole_object_information,
	    FIX((SI_Long)101L),Qole);
    Qrequest_ole_object_transfer = 
	    STATIC_SYMBOL("REQUEST-OLE-OBJECT-TRANSFER",AB_package);
    add_icp_message_type_code(Qrequest_ole_object_transfer,
	    FIX((SI_Long)102L),Qole);
    Qinitiate_ole_object_transfer = 
	    STATIC_SYMBOL("INITIATE-OLE-OBJECT-TRANSFER",AB_package);
    add_icp_message_type_code(Qinitiate_ole_object_transfer,
	    FIX((SI_Long)103L),Qole);
    Qole_object_transfer_milestone = 
	    STATIC_SYMBOL("OLE-OBJECT-TRANSFER-MILESTONE",AB_package);
    add_icp_message_type_code(Qole_object_transfer_milestone,
	    FIX((SI_Long)104L),Qole);
    Qnew_externally_simulated_object = 
	    STATIC_SYMBOL("NEW-EXTERNALLY-SIMULATED-OBJECT",AB_package);
    add_icp_message_type_code(Qnew_externally_simulated_object,
	    FIX((SI_Long)120L),Qnil);
    Qdefine_external_simulation_object = 
	    STATIC_SYMBOL("DEFINE-EXTERNAL-SIMULATION-OBJECT",AB_package);
    add_icp_message_type_code(Qdefine_external_simulation_object,
	    FIX((SI_Long)121L),Qnil);
    Qsimulation_initialization_value = 
	    STATIC_SYMBOL("SIMULATION-INITIALIZATION-VALUE",AB_package);
    add_icp_message_type_code(Qsimulation_initialization_value,
	    FIX((SI_Long)122L),Qnil);
    Qend_simulation_initialization_vector_for_object = 
	    STATIC_SYMBOL("END-SIMULATION-INITIALIZATION-VECTOR-FOR-OBJECT",
	    AB_package);
    add_icp_message_type_code(Qend_simulation_initialization_vector_for_object,
	    FIX((SI_Long)123L),Qnil);
    Qbegin_simulation_input_vector_for_object = 
	    STATIC_SYMBOL("BEGIN-SIMULATION-INPUT-VECTOR-FOR-OBJECT",
	    AB_package);
    add_icp_message_type_code(Qbegin_simulation_input_vector_for_object,
	    FIX((SI_Long)124L),Qnil);
    Qsimulation_keyword = STATIC_SYMBOL("SIMULATION-KEYWORD",AB_package);
    add_icp_message_type_code(Qsimulation_keyword,FIX((SI_Long)125L),Qnil);
    Qsimulation_input_value = STATIC_SYMBOL("SIMULATION-INPUT-VALUE",
	    AB_package);
    add_icp_message_type_code(Qsimulation_input_value,FIX((SI_Long)126L),Qnil);
    Qend_simulation_input_vector_for_object = 
	    STATIC_SYMBOL("END-SIMULATION-INPUT-VECTOR-FOR-OBJECT",AB_package);
    add_icp_message_type_code(Qend_simulation_input_vector_for_object,
	    FIX((SI_Long)127L),Qnil);
    Qshutdown_external_simulator = 
	    STATIC_SYMBOL("SHUTDOWN-EXTERNAL-SIMULATOR",AB_package);
    add_icp_message_type_code(Qshutdown_external_simulator,
	    FIX((SI_Long)128L),Qnil);
    Qpause_external_simulator = STATIC_SYMBOL("PAUSE-EXTERNAL-SIMULATOR",
	    AB_package);
    add_icp_message_type_code(Qpause_external_simulator,FIX((SI_Long)129L),
	    Qnil);
    Qresume_external_simulator = STATIC_SYMBOL("RESUME-EXTERNAL-SIMULATOR",
	    AB_package);
    add_icp_message_type_code(Qresume_external_simulator,
	    FIX((SI_Long)130L),Qnil);
    Qbegin_simulation_output_vector_for_object = 
	    STATIC_SYMBOL("BEGIN-SIMULATION-OUTPUT-VECTOR-FOR-OBJECT",
	    AB_package);
    add_icp_message_type_code(Qbegin_simulation_output_vector_for_object,
	    FIX((SI_Long)131L),Qnil);
    Qsimulation_output_value = STATIC_SYMBOL("SIMULATION-OUTPUT-VALUE",
	    AB_package);
    add_icp_message_type_code(Qsimulation_output_value,FIX((SI_Long)132L),
	    Qnil);
    Qend_simulation_output_vector_for_object = 
	    STATIC_SYMBOL("END-SIMULATION-OUTPUT-VECTOR-FOR-OBJECT",
	    AB_package);
    add_icp_message_type_code(Qend_simulation_output_vector_for_object,
	    FIX((SI_Long)133L),Qnil);
    Qinitialize_external_simulator = 
	    STATIC_SYMBOL("INITIALIZE-EXTERNAL-SIMULATOR",AB_package);
    add_icp_message_type_code(Qinitialize_external_simulator,
	    FIX((SI_Long)134L),Qnil);
    Qend_simulation_input_for_cycle = 
	    STATIC_SYMBOL("END-SIMULATION-INPUT-FOR-CYCLE",AB_package);
    add_icp_message_type_code(Qend_simulation_input_for_cycle,
	    FIX((SI_Long)135L),Qnil);
    Qend_simulation_output_for_cycle = 
	    STATIC_SYMBOL("END-SIMULATION-OUTPUT-FOR-CYCLE",AB_package);
    add_icp_message_type_code(Qend_simulation_output_for_cycle,
	    FIX((SI_Long)136L),Qnil);
    Qconnection_info = STATIC_SYMBOL("CONNECTION-INFO",AB_package);
    add_icp_message_type_code(Qconnection_info,FIX((SI_Long)137L),Qnil);
    Qbegin_making_graph_rendering = 
	    STATIC_SYMBOL("BEGIN-MAKING-GRAPH-RENDERING",AB_package);
    add_icp_message_type_code(Qbegin_making_graph_rendering,
	    FIX((SI_Long)150L),Qnil);
    Qadd_from_graph_rendering_to_current_window = 
	    STATIC_SYMBOL("ADD-FROM-GRAPH-RENDERING-TO-CURRENT-WINDOW",
	    AB_package);
    add_icp_message_type_code(Qadd_from_graph_rendering_to_current_window,
	    FIX((SI_Long)151L),Qnil);
    Qmake_graph_rendering_structure_if_necessary = 
	    STATIC_SYMBOL("MAKE-GRAPH-RENDERING-STRUCTURE-IF-NECESSARY",
	    AB_package);
    add_icp_message_type_code(Qmake_graph_rendering_structure_if_necessary,
	    FIX((SI_Long)152L),Qnil);
    Qupdate_graph_dateline = STATIC_SYMBOL("UPDATE-GRAPH-DATELINE",AB_package);
    add_icp_message_type_code(Qupdate_graph_dateline,FIX((SI_Long)153L),Qnil);
    Qupdate_graph_data_extrema = STATIC_SYMBOL("UPDATE-GRAPH-DATA-EXTREMA",
	    AB_package);
    add_icp_message_type_code(Qupdate_graph_data_extrema,
	    FIX((SI_Long)154L),Qnil);
    Qset_plot_pattern_to_use = STATIC_SYMBOL("SET-PLOT-PATTERN-TO-USE",
	    AB_package);
    add_icp_message_type_code(Qset_plot_pattern_to_use,FIX((SI_Long)156L),
	    Qnil);
    Qupdate_ring_raster_for_graph_given_color_values = 
	    STATIC_SYMBOL("UPDATE-RING-RASTER-FOR-GRAPH-GIVEN-COLOR-VALUES",
	    AB_package);
    add_icp_message_type_code(Qupdate_ring_raster_for_graph_given_color_values,
	    FIX((SI_Long)157L),Qnil);
    Qprepare_for_painting_graph = 
	    STATIC_SYMBOL("PREPARE-FOR-PAINTING-GRAPH",AB_package);
    add_icp_message_type_code(Qprepare_for_painting_graph,
	    FIX((SI_Long)158L),Qnil);
    Qclear_data_clipping_rectangles = 
	    STATIC_SYMBOL("CLEAR-DATA-CLIPPING-RECTANGLES",AB_package);
    add_icp_message_type_code(Qclear_data_clipping_rectangles,
	    FIX((SI_Long)162L),Qnil);
    Qdelete_icp_object_for_process = 
	    STATIC_SYMBOL("DELETE-ICP-OBJECT-FOR-PROCESS",AB_package);
    add_icp_message_type_code(Qdelete_icp_object_for_process,
	    FIX((SI_Long)163L),Qrpc);
    Qpaint_marker_onto_graph_raster = 
	    STATIC_SYMBOL("PAINT-MARKER-ONTO-GRAPH-RASTER",AB_package);
    add_icp_message_type_code(Qpaint_marker_onto_graph_raster,
	    FIX((SI_Long)164L),Qnil);
    Qpaint_icon_onto_graph_raster = 
	    STATIC_SYMBOL("PAINT-ICON-ONTO-GRAPH-RASTER",AB_package);
    add_icp_message_type_code(Qpaint_icon_onto_graph_raster,
	    FIX((SI_Long)165L),Qnil);
    add_icp_message_type_code(Qmessage_group_id,FIX((SI_Long)181L),
	    Qi_am_alive);
    Qupdate_ring_raster_for_graph_given_color_values_2 = 
	    STATIC_SYMBOL("UPDATE-RING-RASTER-FOR-GRAPH-GIVEN-COLOR-VALUES-2",
	    AB_package);
    add_icp_message_type_code(Qupdate_ring_raster_for_graph_given_color_values_2,
	    FIX((SI_Long)182L),Qnil);
    Qbegin_making_image_data = STATIC_SYMBOL("BEGIN-MAKING-IMAGE-DATA",
	    AB_package);
    add_icp_message_type_code(Qbegin_making_image_data,FIX((SI_Long)183L),
	    Qnil);
    Qimage_data_chunk = STATIC_SYMBOL("IMAGE-DATA-CHUNK",AB_package);
    add_icp_message_type_code(Qimage_data_chunk,FIX((SI_Long)184L),Qnil);
    Qpaint_image_in_current_window = 
	    STATIC_SYMBOL("PAINT-IMAGE-IN-CURRENT-WINDOW",AB_package);
    add_icp_message_type_code(Qpaint_image_in_current_window,
	    FIX((SI_Long)185L),Qnil);
    Qpaint_image_in_current_scratchpad_raster = 
	    STATIC_SYMBOL("PAINT-IMAGE-IN-CURRENT-SCRATCHPAD-RASTER",
	    AB_package);
    add_icp_message_type_code(Qpaint_image_in_current_scratchpad_raster,
	    FIX((SI_Long)186L),Qnil);
    Qchange_image_palette_of_window = 
	    STATIC_SYMBOL("CHANGE-IMAGE-PALETTE-OF-WINDOW",AB_package);
    add_icp_message_type_code(Qchange_image_palette_of_window,
	    FIX((SI_Long)187L),Qnil);
    Qforce_graphics_on_window = STATIC_SYMBOL("FORCE-GRAPHICS-ON-WINDOW",
	    AB_package);
    add_icp_message_type_code(Qforce_graphics_on_window,FIX((SI_Long)188L),
	    Qnil);
    Qping_drawing = STATIC_SYMBOL("PING-DRAWING",AB_package);
    add_icp_message_type_code(Qping_drawing,FIX((SI_Long)189L),Qnil);
    Qping_drawing_reply = STATIC_SYMBOL("PING-DRAWING-REPLY",AB_package);
    add_icp_message_type_code(Qping_drawing_reply,FIX((SI_Long)190L),Qnil);
    Qpaint_icon_background_image_in_current_window = 
	    STATIC_SYMBOL("PAINT-ICON-BACKGROUND-IMAGE-IN-CURRENT-WINDOW",
	    AB_package);
    add_icp_message_type_code(Qpaint_icon_background_image_in_current_window,
	    FIX((SI_Long)191L),Qnil);
    Qset_graph_rendering_foreground_only_mode = 
	    STATIC_SYMBOL("SET-GRAPH-RENDERING-FOREGROUND-ONLY-MODE",
	    AB_package);
    add_icp_message_type_code(Qset_graph_rendering_foreground_only_mode,
	    FIX((SI_Long)192L),Qnil);
    Qpaint_clearing_rectangle_in_current_scratchpad_raster = 
	    STATIC_SYMBOL("PAINT-CLEARING-RECTANGLE-IN-CURRENT-SCRATCHPAD-RASTER",
	    AB_package);
    add_icp_message_type_code(Qpaint_clearing_rectangle_in_current_scratchpad_raster,
	    FIX((SI_Long)193L),Qnil);
    Qpost_native_menu = STATIC_SYMBOL("POST-NATIVE-MENU",AB_package);
    add_icp_message_type_code(Qpost_native_menu,FIX((SI_Long)194L),Qnil);
    Qsimple_dialog = STATIC_SYMBOL("SIMPLE-DIALOG",AB_package);
    add_icp_message_type_code(Qsimple_dialog,FIX((SI_Long)195L),Qnil);
    Qset_scroll_info = STATIC_SYMBOL("SET-SCROLL-INFO",AB_package);
    add_icp_message_type_code(Qset_scroll_info,FIX((SI_Long)196L),Qnil);
    Qset_window_title = STATIC_SYMBOL("SET-WINDOW-TITLE",AB_package);
    add_icp_message_type_code(Qset_window_title,FIX((SI_Long)197L),Qnil);
    Qdefine_color_map = STATIC_SYMBOL("DEFINE-COLOR-MAP",AB_package);
    add_icp_message_type_code(Qdefine_color_map,FIX((SI_Long)210L),Qnil);
    Qdefine_remote_procedure_name = 
	    STATIC_SYMBOL("DEFINE-REMOTE-PROCEDURE-NAME",AB_package);
    add_icp_message_type_code(Qdefine_remote_procedure_name,
	    FIX((SI_Long)221L),Qrpc);
    Qdefine_remote_procedure_identifier = 
	    STATIC_SYMBOL("DEFINE-REMOTE-PROCEDURE-IDENTIFIER",AB_package);
    add_icp_message_type_code(Qdefine_remote_procedure_identifier,
	    FIX((SI_Long)222L),Qrpc);
    Qinitialize_server_g2ds_interface = 
	    STATIC_SYMBOL("INITIALIZE-SERVER-G2DS-INTERFACE",AB_package);
    add_icp_message_type_code(Qinitialize_server_g2ds_interface,
	    FIX((SI_Long)223L),Qnil);
    Qrpc_start = STATIC_SYMBOL("RPC-START",AB_package);
    add_icp_message_type_code(Qrpc_start,FIX((SI_Long)230L),Qrpc);
    Qrpc_call = STATIC_SYMBOL("RPC-CALL",AB_package);
    add_icp_message_type_code(Qrpc_call,FIX((SI_Long)231L),Qrpc);
    Qrpc_error = STATIC_SYMBOL("RPC-ERROR",AB_package);
    add_icp_message_type_code(Qrpc_error,FIX((SI_Long)232L),Qrpc);
    Qrpc_error_to_caller = STATIC_SYMBOL("RPC-ERROR-TO-CALLER",AB_package);
    add_icp_message_type_code(Qrpc_error_to_caller,FIX((SI_Long)233L),Qrpc);
    Qrpc_continue_from_error = STATIC_SYMBOL("RPC-CONTINUE-FROM-ERROR",
	    AB_package);
    add_icp_message_type_code(Qrpc_continue_from_error,FIX((SI_Long)234L),
	    Qrpc);
    Qrpc_asynchronous_abort = STATIC_SYMBOL("RPC-ASYNCHRONOUS-ABORT",
	    AB_package);
    add_icp_message_type_code(Qrpc_asynchronous_abort,FIX((SI_Long)235L),Qrpc);
    Qrpc_synchronous_abort = STATIC_SYMBOL("RPC-SYNCHRONOUS-ABORT",AB_package);
    add_icp_message_type_code(Qrpc_synchronous_abort,FIX((SI_Long)236L),Qrpc);
    Qrpc_return_values = STATIC_SYMBOL("RPC-RETURN-VALUES",AB_package);
    add_icp_message_type_code(Qrpc_return_values,FIX((SI_Long)237L),Qrpc);
    Qrpc_suspend = STATIC_SYMBOL("RPC-SUSPEND",AB_package);
    add_icp_message_type_code(Qrpc_suspend,FIX((SI_Long)238L),Qrpc);
    Qrpc_resume = STATIC_SYMBOL("RPC-RESUME",AB_package);
    add_icp_message_type_code(Qrpc_resume,FIX((SI_Long)239L),Qrpc);
    Qrpc_acknowledge_abort = STATIC_SYMBOL("RPC-ACKNOWLEDGE-ABORT",AB_package);
    add_icp_message_type_code(Qrpc_acknowledge_abort,FIX((SI_Long)240L),Qrpc);
    add_icp_message_type_code(Qstart_icp_task,FIX((SI_Long)245L),
	    Qstart_icp_task);
    add_icp_message_type_code(Qresume_icp_task,FIX((SI_Long)246L),
	    Qresume_icp_task);
    Qresumable_rpc_start = STATIC_SYMBOL("RESUMABLE-RPC-START",AB_package);
    add_icp_message_type_code(Qresumable_rpc_start,FIX((SI_Long)247L),Qrpc);
    Qresumable_rpc_call = STATIC_SYMBOL("RESUMABLE-RPC-CALL",AB_package);
    add_icp_message_type_code(Qresumable_rpc_call,FIX((SI_Long)248L),Qrpc);
    Qresumable_rpc_return_values = 
	    STATIC_SYMBOL("RESUMABLE-RPC-RETURN-VALUES",AB_package);
    add_icp_message_type_code(Qresumable_rpc_return_values,
	    FIX((SI_Long)249L),Qrpc);
    Qabort_icp_task = STATIC_SYMBOL("ABORT-ICP-TASK",AB_package);
    add_icp_message_type_code(Qabort_icp_task,FIX((SI_Long)250L),Qicp);
    Qspeedup_begin_tagnames = STATIC_SYMBOL("SPEEDUP-BEGIN-TAGNAMES",
	    AB_package);
    add_icp_message_type_code(Qspeedup_begin_tagnames,FIX((SI_Long)251L),Qnil);
    Qspeedup_input_or_output_tagnames = 
	    STATIC_SYMBOL("SPEEDUP-INPUT-OR-OUTPUT-TAGNAMES",AB_package);
    add_icp_message_type_code(Qspeedup_input_or_output_tagnames,
	    FIX((SI_Long)252L),Qnil);
    Qspeedup_tagname = STATIC_SYMBOL("SPEEDUP-TAGNAME",AB_package);
    add_icp_message_type_code(Qspeedup_tagname,FIX((SI_Long)253L),Qnil);
    Qspeedup_end_tagnames = STATIC_SYMBOL("SPEEDUP-END-TAGNAMES",AB_package);
    add_icp_message_type_code(Qspeedup_end_tagnames,FIX((SI_Long)254L),Qnil);
    Qspeedup_begin_values = STATIC_SYMBOL("SPEEDUP-BEGIN-VALUES",AB_package);
    add_icp_message_type_code(Qspeedup_begin_values,FIX((SI_Long)255L),Qnil);
    Qspeedup_value = STATIC_SYMBOL("SPEEDUP-VALUE",AB_package);
    add_icp_message_type_code(Qspeedup_value,FIX((SI_Long)256L),Qnil);
    Qspeedup_end_values = STATIC_SYMBOL("SPEEDUP-END-VALUES",AB_package);
    add_icp_message_type_code(Qspeedup_end_values,FIX((SI_Long)257L),Qnil);
    Qpaint_from_line_of_text_to_current_scratchpad_raster = 
	    STATIC_SYMBOL("PAINT-FROM-LINE-OF-TEXT-TO-CURRENT-SCRATCHPAD-RASTER",
	    AB_package);
    add_icp_message_type_code(Qpaint_from_line_of_text_to_current_scratchpad_raster,
	    FIX((SI_Long)271L),Qnil);
    Qremote_eval = STATIC_SYMBOL("REMOTE-EVAL",AB_package);
    add_icp_message_type_code(Qremote_eval,FIX((SI_Long)300L),Qnil);
    Qdefine_temporary_index_space = 
	    STATIC_SYMBOL("DEFINE-TEMPORARY-INDEX-SPACE",AB_package);
    add_icp_message_type_code(Qdefine_temporary_index_space,
	    FIX((SI_Long)301L),Qrpc);
    Qrelease_temporary_index_space = 
	    STATIC_SYMBOL("RELEASE-TEMPORARY-INDEX-SPACE",AB_package);
    add_icp_message_type_code(Qrelease_temporary_index_space,
	    FIX((SI_Long)302L),Qrpc);
    Qconnection_denied = STATIC_SYMBOL("CONNECTION-DENIED",AB_package);
    add_icp_message_type_code(Qconnection_denied,FIX((SI_Long)305L),Qicp);
    Qconnection_shutdown_imminent = 
	    STATIC_SYMBOL("CONNECTION-SHUTDOWN-IMMINENT",AB_package);
    add_icp_message_type_code(Qconnection_shutdown_imminent,
	    FIX((SI_Long)306L),Qicp);
    Qno_license = STATIC_SYMBOL("NO-LICENSE",AB_package);
    add_icp_message_type_code(Qno_license,FIX((SI_Long)307L),Qicp);
    Qrequest_foreign_function_registry = 
	    STATIC_SYMBOL("REQUEST-FOREIGN-FUNCTION-REGISTRY",AB_package);
    add_icp_message_type_code(Qrequest_foreign_function_registry,
	    FIX((SI_Long)311L),Qnil);
    Qprovide_foreign_function_registry = 
	    STATIC_SYMBOL("PROVIDE-FOREIGN-FUNCTION-REGISTRY",AB_package);
    add_icp_message_type_code(Qprovide_foreign_function_registry,
	    FIX((SI_Long)312L),Qnil);
    Qcall_foreign_function = STATIC_SYMBOL("CALL-FOREIGN-FUNCTION",AB_package);
    add_icp_message_type_code(Qcall_foreign_function,FIX((SI_Long)313L),Qnil);
    Qreturn_foreign_function_value = 
	    STATIC_SYMBOL("RETURN-FOREIGN-FUNCTION-VALUE",AB_package);
    add_icp_message_type_code(Qreturn_foreign_function_value,
	    FIX((SI_Long)314L),Qnil);
    Qsignal_foreign_function_error = 
	    STATIC_SYMBOL("SIGNAL-FOREIGN-FUNCTION-ERROR",AB_package);
    add_icp_message_type_code(Qsignal_foreign_function_error,
	    FIX((SI_Long)315L),Qnil);
    Qkill_foreign_function_server = 
	    STATIC_SYMBOL("KILL-FOREIGN-FUNCTION-SERVER",AB_package);
    add_icp_message_type_code(Qkill_foreign_function_server,
	    FIX((SI_Long)316L),Qnil);
    Qshut_down_foreign_server_context = 
	    STATIC_SYMBOL("SHUT-DOWN-FOREIGN-SERVER-CONTEXT",AB_package);
    add_icp_message_type_code(Qshut_down_foreign_server_context,
	    FIX((SI_Long)317L),Qnil);
    Qcontinue_building_resumable_object = 
	    STATIC_SYMBOL("CONTINUE-BUILDING-RESUMABLE-OBJECT",AB_package);
    add_icp_message_type_code(Qcontinue_building_resumable_object,
	    FIX((SI_Long)320L),Qrpc);
    Qupdate_object_passing_network_resources = 
	    STATIC_SYMBOL("UPDATE-OBJECT-PASSING-NETWORK-RESOURCES",
	    AB_package);
    add_icp_message_type_code(Qupdate_object_passing_network_resources,
	    FIX((SI_Long)321L),Qrpc);
    Qregister_corresponding_icp_object = 
	    STATIC_SYMBOL("REGISTER-CORRESPONDING-ICP-OBJECT",AB_package);
    add_icp_message_type_code(Qregister_corresponding_icp_object,
	    FIX((SI_Long)322L),Qrpc);
    Qderegister_corresponding_icp_object = 
	    STATIC_SYMBOL("DEREGISTER-CORRESPONDING-ICP-OBJECT",AB_package);
    add_icp_message_type_code(Qderegister_corresponding_icp_object,
	    FIX((SI_Long)323L),Qrpc);
    Qderegister_original_icp_object = 
	    STATIC_SYMBOL("DEREGISTER-ORIGINAL-ICP-OBJECT",AB_package);
    add_icp_message_type_code(Qderegister_original_icp_object,
	    FIX((SI_Long)324L),Qrpc);
    Qacknowledge_deregister_corresponding_icp_object = 
	    STATIC_SYMBOL("ACKNOWLEDGE-DEREGISTER-CORRESPONDING-ICP-OBJECT",
	    AB_package);
    add_icp_message_type_code(Qacknowledge_deregister_corresponding_icp_object,
	    FIX((SI_Long)325L),Qrpc);
    Qderegister_icp_objects = STATIC_SYMBOL("DEREGISTER-ICP-OBJECTS",
	    AB_package);
    add_icp_message_type_code(Qderegister_icp_objects,FIX((SI_Long)326L),Qrpc);
    Qstart_mouse_tracking_in_window = 
	    STATIC_SYMBOL("START-MOUSE-TRACKING-IN-WINDOW",AB_package);
    add_icp_message_type_code(Qstart_mouse_tracking_in_window,
	    FIX((SI_Long)330L),Qnil);
    Qstop_mouse_tracking_in_window = 
	    STATIC_SYMBOL("STOP-MOUSE-TRACKING-IN-WINDOW",AB_package);
    add_icp_message_type_code(Qstop_mouse_tracking_in_window,
	    FIX((SI_Long)331L),Qnil);
    Qset_position_of_mouse_in_window = 
	    STATIC_SYMBOL("SET-POSITION-OF-MOUSE-IN-WINDOW",AB_package);
    add_icp_message_type_code(Qset_position_of_mouse_in_window,
	    FIX((SI_Long)332L),Qnil);
    Qshift_position_of_mouse_in_window = 
	    STATIC_SYMBOL("SHIFT-POSITION-OF-MOUSE-IN-WINDOW",AB_package);
    add_icp_message_type_code(Qshift_position_of_mouse_in_window,
	    FIX((SI_Long)333L),Qnil);
    Qreroute_telewindow = STATIC_SYMBOL("REROUTE-TELEWINDOW",AB_package);
    add_icp_message_type_code(Qreroute_telewindow,FIX((SI_Long)334L),Qnil);
    Qset_window_license_level = STATIC_SYMBOL("SET-WINDOW-LICENSE-LEVEL",
	    AB_package);
    add_icp_message_type_code(Qset_window_license_level,FIX((SI_Long)335L),
	    Qnil);
    Qacknowledge_shutdown = STATIC_SYMBOL("ACKNOWLEDGE-SHUTDOWN",AB_package);
    add_icp_message_type_code(Qacknowledge_shutdown,FIX((SI_Long)336L),Qicp);
    Qset_telewindows_connection_license_info = 
	    STATIC_SYMBOL("SET-TELEWINDOWS-CONNECTION-LICENSE-INFO",
	    AB_package);
    add_icp_message_type_code(Qset_telewindows_connection_license_info,
	    FIX((SI_Long)337L),Qnil);
    Qinitialize_gsi_interface = STATIC_SYMBOL("INITIALIZE-GSI-INTERFACE",
	    AB_package);
    add_icp_message_type_code(Qinitialize_gsi_interface,FIX((SI_Long)338L),
	    Qgsi);
    Qreturn_initialize_gsi_interface_status = 
	    STATIC_SYMBOL("RETURN-INITIALIZE-GSI-INTERFACE-STATUS",AB_package);
    add_icp_message_type_code(Qreturn_initialize_gsi_interface_status,
	    FIX((SI_Long)339L),Qgsi);
    Qsave_user_settings_for_telewindows = 
	    STATIC_SYMBOL("SAVE-USER-SETTINGS-FOR-TELEWINDOWS",AB_package);
    add_icp_message_type_code(Qsave_user_settings_for_telewindows,
	    FIX((SI_Long)350L),Qnil);
    Qintern_list = STATIC_SYMBOL("INTERN-LIST",AB_package);
    add_icp_message_type_code(Qintern_list,FIX((SI_Long)351L),Qrpc);
    Qdefine_resumable_remote_procedure_identifier = 
	    STATIC_SYMBOL("DEFINE-RESUMABLE-REMOTE-PROCEDURE-IDENTIFIER",
	    AB_package);
    add_icp_message_type_code(Qdefine_resumable_remote_procedure_identifier,
	    FIX((SI_Long)352L),Qrpc);
    Qresumable_rpc_error = STATIC_SYMBOL("RESUMABLE-RPC-ERROR",AB_package);
    add_icp_message_type_code(Qresumable_rpc_error,FIX((SI_Long)353L),Qrpc);
    Qresumable_rpc_error_to_caller = 
	    STATIC_SYMBOL("RESUMABLE-RPC-ERROR-TO-CALLER",AB_package);
    add_icp_message_type_code(Qresumable_rpc_error_to_caller,
	    FIX((SI_Long)354L),Qrpc);
    Qcreate_item_reference = STATIC_SYMBOL("CREATE-ITEM-REFERENCE",AB_package);
    add_icp_message_type_code(Qcreate_item_reference,FIX((SI_Long)355L),Qrpc);
    Qcopy_text_string_to_cut_buffer = 
	    STATIC_SYMBOL("COPY-TEXT-STRING-TO-CUT-BUFFER",AB_package);
    add_icp_message_type_code(Qcopy_text_string_to_cut_buffer,
	    FIX((SI_Long)357L),Qnil);
    Qpaste_from_telewindows_to_g2 = 
	    STATIC_SYMBOL("PASTE-FROM-TELEWINDOWS-TO-G2",AB_package);
    add_icp_message_type_code(Qpaste_from_telewindows_to_g2,
	    FIX((SI_Long)358L),Qnil);
    Qrequest_paste_of_cut_buffer_text = 
	    STATIC_SYMBOL("REQUEST-PASTE-OF-CUT-BUFFER-TEXT",AB_package);
    add_icp_message_type_code(Qrequest_paste_of_cut_buffer_text,
	    FIX((SI_Long)359L),Qnil);
    Qupdate_paste_availability_status = 
	    STATIC_SYMBOL("UPDATE-PASTE-AVAILABILITY-STATUS",AB_package);
    add_icp_message_type_code(Qupdate_paste_availability_status,
	    FIX((SI_Long)360L),Qnil);
    Qenable_or_disable_clipboard_polling = 
	    STATIC_SYMBOL("ENABLE-OR-DISABLE-CLIPBOARD-POLLING",AB_package);
    add_icp_message_type_code(Qenable_or_disable_clipboard_polling,
	    FIX((SI_Long)361L),Qnil);
    Qrequest_paste_availability_status = 
	    STATIC_SYMBOL("REQUEST-PASTE-AVAILABILITY-STATUS",AB_package);
    add_icp_message_type_code(Qrequest_paste_availability_status,
	    FIX((SI_Long)362L),Qnil);
    Qstart_data_server = STATIC_SYMBOL("START-DATA-SERVER",AB_package);
    add_icp_message_type_code(Qstart_data_server,FIX((SI_Long)363L),Qgsi_ds);
    Qreset_data_server = STATIC_SYMBOL("RESET-DATA-SERVER",AB_package);
    add_icp_message_type_code(Qreset_data_server,FIX((SI_Long)364L),Qgsi_ds);
    Qstipple_rectangle_in_current_scratchpad_raster = 
	    STATIC_SYMBOL("STIPPLE-RECTANGLE-IN-CURRENT-SCRATCHPAD-RASTER",
	    AB_package);
    add_icp_message_type_code(Qstipple_rectangle_in_current_scratchpad_raster,
	    FIX((SI_Long)365L),Qnil);
    Qadd_wide_polyline_to_current_window = 
	    STATIC_SYMBOL("ADD-WIDE-POLYLINE-TO-CURRENT-WINDOW",AB_package);
    add_icp_message_type_code(Qadd_wide_polyline_to_current_window,
	    FIX((SI_Long)366L),Qnil);
    Qdraw_offscreen = STATIC_SYMBOL("DRAW-OFFSCREEN",AB_package);
    add_icp_message_type_code(Qdraw_offscreen,FIX((SI_Long)367L),Qnil);
    Qlaunch_peer_window = STATIC_SYMBOL("LAUNCH-PEER-WINDOW",AB_package);
    add_icp_message_type_code(Qlaunch_peer_window,FIX((SI_Long)368L),Qnil);
    Qfile_dialog = STATIC_SYMBOL("FILE-DIALOG",AB_package);
    add_icp_message_type_code(Qfile_dialog,FIX((SI_Long)369L),Qnil);
    Qhtml_help = STATIC_SYMBOL("HTML-HELP",AB_package);
    add_icp_message_type_code(Qhtml_help,FIX((SI_Long)370L),Qnil);
    Qset_window_show_status = STATIC_SYMBOL("SET-WINDOW-SHOW-STATUS",
	    AB_package);
    add_icp_message_type_code(Qset_window_show_status,FIX((SI_Long)371L),Qnil);
    Qshow_window_with_geometry = STATIC_SYMBOL("SHOW-WINDOW-WITH-GEOMETRY",
	    AB_package);
    add_icp_message_type_code(Qshow_window_with_geometry,
	    FIX((SI_Long)372L),Qnil);
    Qnms_create_menu = STATIC_SYMBOL("NMS-CREATE-MENU",AB_package);
    add_icp_message_type_code(Qnms_create_menu,FIX((SI_Long)500L),Qnil);
    Qnms_delete_menu = STATIC_SYMBOL("NMS-DELETE-MENU",AB_package);
    add_icp_message_type_code(Qnms_delete_menu,FIX((SI_Long)501L),Qnil);
    Qnms_append_menu_item = STATIC_SYMBOL("NMS-APPEND-MENU-ITEM",AB_package);
    add_icp_message_type_code(Qnms_append_menu_item,FIX((SI_Long)502L),Qnil);
    Qnms_set_menu_bar = STATIC_SYMBOL("NMS-SET-MENU-BAR",AB_package);
    add_icp_message_type_code(Qnms_set_menu_bar,FIX((SI_Long)503L),Qnil);
    Qnms_pop_up_menu = STATIC_SYMBOL("NMS-POP-UP-MENU",AB_package);
    add_icp_message_type_code(Qnms_pop_up_menu,FIX((SI_Long)504L),Qnil);
    Qnms_check_menu_item = STATIC_SYMBOL("NMS-CHECK-MENU-ITEM",AB_package);
    add_icp_message_type_code(Qnms_check_menu_item,FIX((SI_Long)505L),Qnil);
    Qnms_check_radio_item = STATIC_SYMBOL("NMS-CHECK-RADIO-ITEM",AB_package);
    add_icp_message_type_code(Qnms_check_radio_item,FIX((SI_Long)506L),Qnil);
    Qnms_enable_menu_item = STATIC_SYMBOL("NMS-ENABLE-MENU-ITEM",AB_package);
    add_icp_message_type_code(Qnms_enable_menu_item,FIX((SI_Long)507L),Qnil);
    Qnms_modify_menu_item = STATIC_SYMBOL("NMS-MODIFY-MENU-ITEM",AB_package);
    add_icp_message_type_code(Qnms_modify_menu_item,FIX((SI_Long)508L),Qnil);
    Qnms_dismiss = STATIC_SYMBOL("NMS-DISMISS",AB_package);
    add_icp_message_type_code(Qnms_dismiss,FIX((SI_Long)509L),Qnil);
    Qnms_reset = STATIC_SYMBOL("NMS-RESET",AB_package);
    add_icp_message_type_code(Qnms_reset,FIX((SI_Long)510L),Qnil);
    Qnms_append_special = STATIC_SYMBOL("NMS-APPEND-SPECIAL",AB_package);
    add_icp_message_type_code(Qnms_append_special,FIX((SI_Long)511L),Qnil);
    Qnms_enable_items = STATIC_SYMBOL("NMS-ENABLE-ITEMS",AB_package);
    add_icp_message_type_code(Qnms_enable_items,FIX((SI_Long)512L),Qnil);
    Qnms_set_menu_flags = STATIC_SYMBOL("NMS-SET-MENU-FLAGS",AB_package);
    add_icp_message_type_code(Qnms_set_menu_flags,FIX((SI_Long)518L),Qnil);
    Qnms_set_iconsize = STATIC_SYMBOL("NMS-SET-ICONSIZE",AB_package);
    add_icp_message_type_code(Qnms_set_iconsize,FIX((SI_Long)591L),Qnil);
    Qnative_printing_dialog = STATIC_SYMBOL("NATIVE-PRINTING-DIALOG",
	    AB_package);
    add_icp_message_type_code(Qnative_printing_dialog,FIX((SI_Long)513L),Qnil);
    Qnative_printing_control = STATIC_SYMBOL("NATIVE-PRINTING-CONTROL",
	    AB_package);
    add_icp_message_type_code(Qnative_printing_control,FIX((SI_Long)514L),
	    Qnil);
    Qnative_printing_start_page = 
	    STATIC_SYMBOL("NATIVE-PRINTING-START-PAGE",AB_package);
    add_icp_message_type_code(Qnative_printing_start_page,
	    FIX((SI_Long)515L),Qnil);
    Qpaint_icon_in_current_window = 
	    STATIC_SYMBOL("PAINT-ICON-IN-CURRENT-WINDOW",AB_package);
    add_icp_message_type_code(Qpaint_icon_in_current_window,
	    FIX((SI_Long)516L),Qnil);
    Qpaint_line_of_text_in_current_window = 
	    STATIC_SYMBOL("PAINT-LINE-OF-TEXT-IN-CURRENT-WINDOW",AB_package);
    add_icp_message_type_code(Qpaint_line_of_text_in_current_window,
	    FIX((SI_Long)517L),Qnil);
    Qmanage_native_icons = STATIC_SYMBOL("MANAGE-NATIVE-ICONS",AB_package);
    add_icp_message_type_code(Qmanage_native_icons,FIX((SI_Long)519L),Qnil);
    Qmanage_progress_bar = STATIC_SYMBOL("MANAGE-PROGRESS-BAR",AB_package);
    add_icp_message_type_code(Qmanage_progress_bar,FIX((SI_Long)520L),Qnil);
    Qbasic_dialog = STATIC_SYMBOL("BASIC-DIALOG",AB_package);
    add_icp_message_type_code(Qbasic_dialog,FIX((SI_Long)521L),Qnil);
    Qmanage_native_control = STATIC_SYMBOL("MANAGE-NATIVE-CONTROL",AB_package);
    add_icp_message_type_code(Qmanage_native_control,FIX((SI_Long)522L),Qnil);
    Qreset_native_controls = STATIC_SYMBOL("RESET-NATIVE-CONTROLS",AB_package);
    add_icp_message_type_code(Qreset_native_controls,FIX((SI_Long)523L),Qnil);
    Qcreate_window = STATIC_SYMBOL("CREATE-WINDOW",AB_package);
    add_icp_message_type_code(Qcreate_window,FIX((SI_Long)524L),Qnil);
    Qmanage_window = STATIC_SYMBOL("MANAGE-WINDOW",AB_package);
    add_icp_message_type_code(Qmanage_window,FIX((SI_Long)525L),Qnil);
    Qredirect_window = STATIC_SYMBOL("REDIRECT-WINDOW",AB_package);
    add_icp_message_type_code(Qredirect_window,FIX((SI_Long)526L),Qnil);
    Qstack_windows = STATIC_SYMBOL("STACK-WINDOWS",AB_package);
    add_icp_message_type_code(Qstack_windows,FIX((SI_Long)527L),Qnil);
    Qscroll_window = STATIC_SYMBOL("SCROLL-WINDOW",AB_package);
    add_icp_message_type_code(Qscroll_window,FIX((SI_Long)528L),Qnil);
    Qmanage_scrollbars = STATIC_SYMBOL("MANAGE-SCROLLBARS",AB_package);
    add_icp_message_type_code(Qmanage_scrollbars,FIX((SI_Long)529L),Qnil);
    Qmega_refresh = STATIC_SYMBOL("MEGA-REFRESH",AB_package);
    add_icp_message_type_code(Qmega_refresh,FIX((SI_Long)530L),Qnil);
    Qtw_command = STATIC_SYMBOL("TW-COMMAND",AB_package);
    add_icp_message_type_code(Qtw_command,FIX((SI_Long)531L),Qnil);
    Qstart_custom_dialog = STATIC_SYMBOL("START-CUSTOM-DIALOG",AB_package);
    add_icp_message_type_code(Qstart_custom_dialog,FIX((SI_Long)532L),Qnil);
    Qadd_dialog_component = STATIC_SYMBOL("ADD-DIALOG-COMPONENT",AB_package);
    add_icp_message_type_code(Qadd_dialog_component,FIX((SI_Long)533L),Qnil);
    Qshow_custom_dialog = STATIC_SYMBOL("SHOW-CUSTOM-DIALOG",AB_package);
    add_icp_message_type_code(Qshow_custom_dialog,FIX((SI_Long)534L),Qnil);
    Qabort_custom_dialog = STATIC_SYMBOL("ABORT-CUSTOM-DIALOG",AB_package);
    add_icp_message_type_code(Qabort_custom_dialog,FIX((SI_Long)535L),Qnil);
    Qadd_dialog_component_with_font = 
	    STATIC_SYMBOL("ADD-DIALOG-COMPONENT-WITH-FONT",AB_package);
    add_icp_message_type_code(Qadd_dialog_component_with_font,
	    FIX((SI_Long)594L),Qnil);
    Qset_dialog_locked = STATIC_SYMBOL("SET-DIALOG-LOCKED",AB_package);
    add_icp_message_type_code(Qset_dialog_locked,FIX((SI_Long)592L),Qnil);
    Qnms_create_control = STATIC_SYMBOL("NMS-CREATE-CONTROL",AB_package);
    add_icp_message_type_code(Qnms_create_control,FIX((SI_Long)536L),Qnil);
    Qnms_append_control = STATIC_SYMBOL("NMS-APPEND-CONTROL",AB_package);
    add_icp_message_type_code(Qnms_append_control,FIX((SI_Long)537L),Qnil);
    Qnms_delete_control = STATIC_SYMBOL("NMS-DELETE-CONTROL",AB_package);
    add_icp_message_type_code(Qnms_delete_control,FIX((SI_Long)538L),Qnil);
    Qnms_set_theme = STATIC_SYMBOL("NMS-SET-THEME",AB_package);
    add_icp_message_type_code(Qnms_set_theme,FIX((SI_Long)539L),Qnil);
    Qstart_dialog_update = STATIC_SYMBOL("START-DIALOG-UPDATE",AB_package);
    add_icp_message_type_code(Qstart_dialog_update,FIX((SI_Long)540L),Qnil);
    Qdialog_component_update = STATIC_SYMBOL("DIALOG-COMPONENT-UPDATE",
	    AB_package);
    add_icp_message_type_code(Qdialog_component_update,FIX((SI_Long)541L),
	    Qnil);
    Qend_dialog_update = STATIC_SYMBOL("END-DIALOG-UPDATE",AB_package);
    add_icp_message_type_code(Qend_dialog_update,FIX((SI_Long)542L),Qnil);
    Qabort_dialog_update = STATIC_SYMBOL("ABORT-DIALOG-UPDATE",AB_package);
    add_icp_message_type_code(Qabort_dialog_update,FIX((SI_Long)543L),Qnil);
    Qquery_custom_dialog = STATIC_SYMBOL("QUERY-CUSTOM-DIALOG",AB_package);
    add_icp_message_type_code(Qquery_custom_dialog,FIX((SI_Long)544L),Qnil);
    Qlist_directory_response = STATIC_SYMBOL("LIST-DIRECTORY-RESPONSE",
	    AB_package);
    add_icp_message_type_code(Qlist_directory_response,FIX((SI_Long)545L),
	    Qnil);
    Qstart_add_tabular_view = STATIC_SYMBOL("START-ADD-TABULAR-VIEW",
	    AB_package);
    add_icp_message_type_code(Qstart_add_tabular_view,FIX((SI_Long)546L),Qnil);
    Qadd_tabular_view_column = STATIC_SYMBOL("ADD-TABULAR-VIEW-COLUMN",
	    AB_package);
    add_icp_message_type_code(Qadd_tabular_view_column,FIX((SI_Long)548L),
	    Qnil);
    Qstart_add_tabular_view_row = 
	    STATIC_SYMBOL("START-ADD-TABULAR-VIEW-ROW",AB_package);
    add_icp_message_type_code(Qstart_add_tabular_view_row,
	    FIX((SI_Long)550L),Qnil);
    Qadd_tabular_view_cell = STATIC_SYMBOL("ADD-TABULAR-VIEW-CELL",AB_package);
    add_icp_message_type_code(Qadd_tabular_view_cell,FIX((SI_Long)551L),Qnil);
    Qend_add_tabular_view_row = STATIC_SYMBOL("END-ADD-TABULAR-VIEW-ROW",
	    AB_package);
    add_icp_message_type_code(Qend_add_tabular_view_row,FIX((SI_Long)552L),
	    Qnil);
    Qdelete_tabular_view_row = STATIC_SYMBOL("DELETE-TABULAR-VIEW-ROW",
	    AB_package);
    add_icp_message_type_code(Qdelete_tabular_view_row,FIX((SI_Long)554L),
	    Qnil);
    Qstart_dialog_query = STATIC_SYMBOL("START-DIALOG-QUERY",AB_package);
    add_icp_message_type_code(Qstart_dialog_query,FIX((SI_Long)555L),Qnil);
    Qadd_to_dialog_query = STATIC_SYMBOL("ADD-TO-DIALOG-QUERY",AB_package);
    add_icp_message_type_code(Qadd_to_dialog_query,FIX((SI_Long)556L),Qnil);
    Qfinish_dialog_query = STATIC_SYMBOL("FINISH-DIALOG-QUERY",AB_package);
    add_icp_message_type_code(Qfinish_dialog_query,FIX((SI_Long)557L),Qnil);
    Qabort_dialog_query = STATIC_SYMBOL("ABORT-DIALOG-QUERY",AB_package);
    add_icp_message_type_code(Qabort_dialog_query,FIX((SI_Long)558L),Qnil);
    Qstart_replace_tabular_view_row = 
	    STATIC_SYMBOL("START-REPLACE-TABULAR-VIEW-ROW",AB_package);
    add_icp_message_type_code(Qstart_replace_tabular_view_row,
	    FIX((SI_Long)559L),Qnil);
    Qreplace_tabular_view_cell = STATIC_SYMBOL("REPLACE-TABULAR-VIEW-CELL",
	    AB_package);
    add_icp_message_type_code(Qreplace_tabular_view_cell,
	    FIX((SI_Long)560L),Qnil);
    Qend_replace_tabular_view_row = 
	    STATIC_SYMBOL("END-REPLACE-TABULAR-VIEW-ROW",AB_package);
    add_icp_message_type_code(Qend_replace_tabular_view_row,
	    FIX((SI_Long)561L),Qnil);
    Qnms_modify_control = STATIC_SYMBOL("NMS-MODIFY-CONTROL",AB_package);
    add_icp_message_type_code(Qnms_modify_control,FIX((SI_Long)562L),Qnil);
    Qmanage_status_bar = STATIC_SYMBOL("MANAGE-STATUS-BAR",AB_package);
    add_icp_message_type_code(Qmanage_status_bar,FIX((SI_Long)563L),Qnil);
    Qfile_dialog_ex = STATIC_SYMBOL("FILE-DIALOG-EX",AB_package);
    add_icp_message_type_code(Qfile_dialog_ex,FIX((SI_Long)564L),Qnil);
    Qmanage_tree_view = STATIC_SYMBOL("MANAGE-TREE-VIEW",AB_package);
    add_icp_message_type_code(Qmanage_tree_view,FIX((SI_Long)565L),Qnil);
    Qmanage_html_view = STATIC_SYMBOL("MANAGE-HTML-VIEW",AB_package);
    add_icp_message_type_code(Qmanage_html_view,FIX((SI_Long)566L),Qnil);
    Qdebugger_dialog = STATIC_SYMBOL("DEBUGGER-DIALOG",AB_package);
    add_icp_message_type_code(Qdebugger_dialog,FIX((SI_Long)567L),Qnil);
    Qmanage_editor = STATIC_SYMBOL("MANAGE-EDITOR",AB_package);
    add_icp_message_type_code(Qmanage_editor,FIX((SI_Long)568L),Qnil);
    Qnative_printing_ex = STATIC_SYMBOL("NATIVE-PRINTING-EX",AB_package);
    add_icp_message_type_code(Qnative_printing_ex,FIX((SI_Long)569L),Qnil);
    Qmanage_shortcut_bar = STATIC_SYMBOL("MANAGE-SHORTCUT-BAR",AB_package);
    add_icp_message_type_code(Qmanage_shortcut_bar,FIX((SI_Long)570L),Qnil);
    Qadd_polygon_to_current_window = 
	    STATIC_SYMBOL("ADD-POLYGON-TO-CURRENT-WINDOW",AB_package);
    add_icp_message_type_code(Qadd_polygon_to_current_window,
	    FIX((SI_Long)571L),Qnil);
    Qadd_ellipse_to_current_window = 
	    STATIC_SYMBOL("ADD-ELLIPSE-TO-CURRENT-WINDOW",AB_package);
    add_icp_message_type_code(Qadd_ellipse_to_current_window,
	    FIX((SI_Long)572L),Qnil);
    Qmanage_chart_view = STATIC_SYMBOL("MANAGE-CHART-VIEW",AB_package);
    add_icp_message_type_code(Qmanage_chart_view,FIX((SI_Long)573L),Qnil);
    Qmanage_grid_view = STATIC_SYMBOL("MANAGE-GRID-VIEW",AB_package);
    add_icp_message_type_code(Qmanage_grid_view,FIX((SI_Long)574L),Qnil);
    Qselect_tabular_view_rows = STATIC_SYMBOL("SELECT-TABULAR-VIEW-ROWS",
	    AB_package);
    add_icp_message_type_code(Qselect_tabular_view_rows,FIX((SI_Long)575L),
	    Qnil);
    Qshow_custom_dialog_ex = STATIC_SYMBOL("SHOW-CUSTOM-DIALOG-EX",AB_package);
    add_icp_message_type_code(Qshow_custom_dialog_ex,FIX((SI_Long)576L),Qnil);
    Qmanage_pane = STATIC_SYMBOL("MANAGE-PANE",AB_package);
    add_icp_message_type_code(Qmanage_pane,FIX((SI_Long)577L),Qnil);
    Qsimple_dialog_ex = STATIC_SYMBOL("SIMPLE-DIALOG-EX",AB_package);
    add_icp_message_type_code(Qsimple_dialog_ex,FIX((SI_Long)578L),Qnil);
    Qhtml_help_ex = STATIC_SYMBOL("HTML-HELP-EX",AB_package);
    add_icp_message_type_code(Qhtml_help_ex,FIX((SI_Long)579L),Qnil);
    Qmanage_ui_properties = STATIC_SYMBOL("MANAGE-UI-PROPERTIES",AB_package);
    add_icp_message_type_code(Qmanage_ui_properties,FIX((SI_Long)580L),Qnil);
    Qmanage_logbook = STATIC_SYMBOL("MANAGE-LOGBOOK",AB_package);
    add_icp_message_type_code(Qmanage_logbook,FIX((SI_Long)581L),Qnil);
    Qspecify_grid_view_cells = STATIC_SYMBOL("SPECIFY-GRID-VIEW-CELLS",
	    AB_package);
    add_icp_message_type_code(Qspecify_grid_view_cells,FIX((SI_Long)582L),
	    Qnil);
    Qtabbed_mdi_mode = STATIC_SYMBOL("TABBED-MDI-MODE",AB_package);
    add_icp_message_type_code(Qtabbed_mdi_mode,FIX((SI_Long)583L),Qnil);
    Qmanage_dialog = STATIC_SYMBOL("MANAGE-DIALOG",AB_package);
    add_icp_message_type_code(Qmanage_dialog,FIX((SI_Long)584L),Qnil);
    Qmanage_property_grid = STATIC_SYMBOL("MANAGE-PROPERTY-GRID",AB_package);
    add_icp_message_type_code(Qmanage_property_grid,FIX((SI_Long)585L),Qnil);
    Qspecify_text_box_extensions = 
	    STATIC_SYMBOL("SPECIFY-TEXT-BOX-EXTENSIONS",AB_package);
    add_icp_message_type_code(Qspecify_text_box_extensions,
	    FIX((SI_Long)586L),Qnil);
    Qnms_append_control_ex = STATIC_SYMBOL("NMS-APPEND-CONTROL-EX",AB_package);
    add_icp_message_type_code(Qnms_append_control_ex,FIX((SI_Long)587L),Qnil);
    Qaccept_custom_dialog = STATIC_SYMBOL("ACCEPT-CUSTOM-DIALOG",AB_package);
    add_icp_message_type_code(Qaccept_custom_dialog,FIX((SI_Long)588L),Qnil);
    Qchoose_directory = STATIC_SYMBOL("CHOOSE-DIRECTORY",AB_package);
    add_icp_message_type_code(Qchoose_directory,FIX((SI_Long)589L),Qnil);
    Qmanage_tabular_view = STATIC_SYMBOL("MANAGE-TABULAR-VIEW",AB_package);
    add_icp_message_type_code(Qmanage_tabular_view,FIX((SI_Long)590L),Qnil);
    Qprint_native_window = STATIC_SYMBOL("PRINT-NATIVE-WINDOW",AB_package);
    add_icp_message_type_code(Qprint_native_window,FIX((SI_Long)593L),Qnil);
    Qlist_sys_drives_response = STATIC_SYMBOL("LIST-SYS-DRIVES-RESPONSE",
	    AB_package);
    add_icp_message_type_code(Qlist_sys_drives_response,FIX((SI_Long)600L),
	    Qnil);
    if (Active_icp_sockets == UNBOUND)
	Active_icp_sockets = Nil;
    Qgsi_undefined_context = STATIC_SYMBOL("GSI-UNDEFINED-CONTEXT",AB_package);
    SET_SYMBOL_VALUE(Qgsi_undefined_context,FIX((SI_Long)-1L));
    Qgsi_uninitialized_context = STATIC_SYMBOL("GSI-UNINITIALIZED-CONTEXT",
	    AB_package);
    SET_SYMBOL_VALUE(Qgsi_uninitialized_context,FIX((SI_Long)-2L));
    if (Maximum_object_passing_bandwidth == UNBOUND)
	Maximum_object_passing_bandwidth = FIX((SI_Long)8192L);
    Icp_socket_shutdown_handshake_timeout = FIX((SI_Long)15L);
    if (Icp_socket_connect_negotiation_timeout_default == UNBOUND)
	Icp_socket_connect_negotiation_timeout_default = FIX((SI_Long)60L 
		* IFIX(Fixnum_time_units_per_second));
    Icp_connection_closed = FIX((SI_Long)0L);
    Icp_connection_connect_in_progress = FIX((SI_Long)1L);
    Icp_connection_running = FIX((SI_Long)2L);
    Icp_connection_shutdown_acknowledgement_rundown = FIX((SI_Long)4L);
    Icp_connection_awaiting_acknowledgement = FIX((SI_Long)5L);
    Icp_socket_listening = FIX((SI_Long)6L);
    Icp_socket_error = FIX((SI_Long)7L);
    Qrelease_1_dot_0_icp_version = STATIC_SYMBOL("RELEASE-1.0-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qrelease_1_dot_0_icp_version,FIX((SI_Long)1L));
    Qrelease_2_dot_0_icp_version = STATIC_SYMBOL("RELEASE-2.0-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qrelease_2_dot_0_icp_version,FIX((SI_Long)2L));
    Qreclaim_remote_corresponding_object_icp_version = 
	    STATIC_SYMBOL("RECLAIM-REMOTE-CORRESPONDING-OBJECT-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qreclaim_remote_corresponding_object_icp_version,
	    FIX((SI_Long)2L));
    Qmodify_gsi_sensor_definition_icp_version = 
	    STATIC_SYMBOL("MODIFY-GSI-SENSOR-DEFINITION-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qmodify_gsi_sensor_definition_icp_version,
	    FIX((SI_Long)2L));
    Qdouble_float_icp_version = STATIC_SYMBOL("DOUBLE-FLOAT-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qdouble_float_icp_version,FIX((SI_Long)2L));
    Qrelease_3_dot_0_icp_version = STATIC_SYMBOL("RELEASE-3.0-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qrelease_3_dot_0_icp_version,FIX((SI_Long)4L));
    Qrelease_4_dot_0_icp_version = STATIC_SYMBOL("RELEASE-4.0-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qrelease_4_dot_0_icp_version,FIX((SI_Long)5L));
    Qds_update_interval_as_float_icp_version = 
	    STATIC_SYMBOL("DS-UPDATE-INTERVAL-AS-FLOAT-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qds_update_interval_as_float_icp_version,
	    FIX((SI_Long)5L));
    Qremote_procedure_include_attribute_icp_version = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-INCLUDE-ATTRIBUTE-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qremote_procedure_include_attribute_icp_version,
	    FIX((SI_Long)5L));
    Qpass_item_as_handle_icp_version = 
	    STATIC_SYMBOL("PASS-ITEM-AS-HANDLE-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qpass_item_as_handle_icp_version,FIX((SI_Long)5L));
    Qpass_item_as_copy_icp_version = 
	    STATIC_SYMBOL("PASS-ITEM-AS-COPY-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qpass_item_as_copy_icp_version,FIX((SI_Long)5L));
    Qgsi_item_registration_icp_version = 
	    STATIC_SYMBOL("GSI-ITEM-REGISTRATION-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qgsi_item_registration_icp_version,FIX((SI_Long)5L));
    Qgsi_timestamp_as_float_icp_version = 
	    STATIC_SYMBOL("GSI-TIMESTAMP-AS-FLOAT-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qgsi_timestamp_as_float_icp_version,FIX((SI_Long)5L));
    Qshutdown_protocol_icp_version = 
	    STATIC_SYMBOL("SHUTDOWN-PROTOCOL-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qshutdown_protocol_icp_version,FIX((SI_Long)5L));
    Qnew_connect_scheme_icp_version = 
	    STATIC_SYMBOL("NEW-CONNECT-SCHEME-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qnew_connect_scheme_icp_version,FIX((SI_Long)5L));
    Qg2_version_reply_to_gsi_icp_version = 
	    STATIC_SYMBOL("G2-VERSION-REPLY-TO-GSI-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qg2_version_reply_to_gsi_icp_version,FIX((SI_Long)5L));
    Qwide_strings_icp_version = STATIC_SYMBOL("WIDE-STRINGS-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qwide_strings_icp_version,FIX((SI_Long)6L));
    Qwriting_coalesced_icp_message_group_icp_version = 
	    STATIC_SYMBOL("WRITING-COALESCED-ICP-MESSAGE-GROUP-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qwriting_coalesced_icp_message_group_icp_version,
	    FIX((SI_Long)7L));
    Qsupports_icp_version_protocol_icp_version = 
	    STATIC_SYMBOL("SUPPORTS-ICP-VERSION-PROTOCOL-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qsupports_icp_version_protocol_icp_version,
	    FIX((SI_Long)8L));
    Qremote_value_supports_item_icp_version = 
	    STATIC_SYMBOL("REMOTE-VALUE-SUPPORTS-ITEM-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qremote_value_supports_item_icp_version,FIX((SI_Long)8L));
    Qsupports_optional_remote_value_tags_icp_version = 
	    STATIC_SYMBOL("SUPPORTS-OPTIONAL-REMOTE-VALUE-TAGS-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qsupports_optional_remote_value_tags_icp_version,
	    FIX((SI_Long)8L));
    Qevaluation_sequences_and_structures_icp_version = 
	    STATIC_SYMBOL("EVALUATION-SEQUENCES-AND-STRUCTURES-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qevaluation_sequences_and_structures_icp_version,
	    FIX((SI_Long)8L));
    Qresumable_icp_version = STATIC_SYMBOL("RESUMABLE-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qresumable_icp_version,FIX((SI_Long)8L));
    Qnew_rpc_kinds_icp_version = STATIC_SYMBOL("NEW-RPC-KINDS-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qnew_rpc_kinds_icp_version,FIX((SI_Long)8L));
    Qvalue_vector_names_are_symbols_icp_version = 
	    STATIC_SYMBOL("VALUE-VECTOR-NAMES-ARE-SYMBOLS-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qvalue_vector_names_are_symbols_icp_version,
	    FIX((SI_Long)8L));
    Qdoes_not_require_enlarge_corresponding_icp_object_index_space_icp_version 
	    = 
	    STATIC_SYMBOL("DOES-NOT-REQUIRE-ENLARGE-CORRESPONDING-ICP-OBJECT-INDEX-SPACE-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qdoes_not_require_enlarge_corresponding_icp_object_index_space_icp_version,
	    FIX((SI_Long)8L));
    Qrel4_rpc_protocol_supports_non_objects_icp_version = 
	    STATIC_SYMBOL("REL4-RPC-PROTOCOL-SUPPORTS-NON-OBJECTS-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qrel4_rpc_protocol_supports_non_objects_icp_version,
	    FIX((SI_Long)8L));
    Qresumable_gsi_ds_icp_version = 
	    STATIC_SYMBOL("RESUMABLE-GSI-DS-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qresumable_gsi_ds_icp_version,FIX((SI_Long)9L));
    Qremote_procedure_include_all_system_attributes_icp_version = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-INCLUDE-ALL-SYSTEM-ATTRIBUTES-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qremote_procedure_include_all_system_attributes_icp_version,
	    FIX((SI_Long)9L));
    Qno_telewindows_clogging_icp_version = 
	    STATIC_SYMBOL("NO-TELEWINDOWS-CLOGGING-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qno_telewindows_clogging_icp_version,FIX((SI_Long)9L));
    Qremote_procedure_varargs_p_icp_version = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-VARARGS-P-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qremote_procedure_varargs_p_icp_version,FIX((SI_Long)9L));
    Qnew_remote_procedure_identifer_protocol_icp_version = 
	    STATIC_SYMBOL("NEW-REMOTE-PROCEDURE-IDENTIFER-PROTOCOL-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qnew_remote_procedure_identifer_protocol_icp_version,
	    FIX((SI_Long)9L));
    Qrpc_use_value_structure_using_unix_time_icp_version = 
	    STATIC_SYMBOL("RPC-USE-VALUE-STRUCTURE-USING-UNIX-TIME-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qrpc_use_value_structure_using_unix_time_icp_version,
	    FIX((SI_Long)10L));
    Qderegister_corresponding_icp_object_index_space_name_icp_version = 
	    STATIC_SYMBOL("DEREGISTER-CORRESPONDING-ICP-OBJECT-INDEX-SPACE-NAME-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qderegister_corresponding_icp_object_index_space_name_icp_version,
	    FIX((SI_Long)10L));
    Qderegister_original_icp_object_icp_version = 
	    STATIC_SYMBOL("DEREGISTER-ORIGINAL-ICP-OBJECT-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qderegister_original_icp_object_icp_version,
	    FIX((SI_Long)10L));
    Qitem_index_space_icp_version = 
	    STATIC_SYMBOL("ITEM-INDEX-SPACE-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qitem_index_space_icp_version,FIX((SI_Long)10L));
    Qvalues_as_handle_icp_version = 
	    STATIC_SYMBOL("VALUES-AS-HANDLE-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qvalues_as_handle_icp_version,FIX((SI_Long)10L));
    Qgsi_dataservice_uses_full_remote_value_protocol_icp_version = 
	    STATIC_SYMBOL("GSI-DATASERVICE-USES-FULL-REMOTE-VALUE-PROTOCOL-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qgsi_dataservice_uses_full_remote_value_protocol_icp_version,
	    FIX((SI_Long)11L));
    Qitem_reference_icp_version = 
	    STATIC_SYMBOL("ITEM-REFERENCE-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qitem_reference_icp_version,FIX((SI_Long)12L));
    Qacknowledge_deregister_corresponding_icp_object_icp_version = 
	    STATIC_SYMBOL("ACKNOWLEDGE-DEREGISTER-CORRESPONDING-ICP-OBJECT-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qacknowledge_deregister_corresponding_icp_object_icp_version,
	    FIX((SI_Long)12L));
    Qabort_icp_task_icp_version = 
	    STATIC_SYMBOL("ABORT-ICP-TASK-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qabort_icp_task_icp_version,FIX((SI_Long)13L));
    Qderegister_icp_objects_icp_version = 
	    STATIC_SYMBOL("DEREGISTER-ICP-OBJECTS-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qderegister_icp_objects_icp_version,FIX((SI_Long)13L));
    Qunsigned_short_vector_icp_version = 
	    STATIC_SYMBOL("UNSIGNED-SHORT-VECTOR-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qunsigned_short_vector_icp_version,FIX((SI_Long)14L));
    Qindependent_layered_rendering_version = 
	    STATIC_SYMBOL("INDEPENDENT-LAYERED-RENDERING-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qindependent_layered_rendering_version,FIX((SI_Long)15L));
    Qdata_servers_can_run_while_inactive_version = 
	    STATIC_SYMBOL("DATA-SERVERS-CAN-RUN-WHILE-INACTIVE-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qdata_servers_can_run_while_inactive_version,
	    FIX((SI_Long)15L));
    Qby_copy_with_handle_supports_references_icp_version = 
	    STATIC_SYMBOL("BY-COPY-WITH-HANDLE-SUPPORTS-REFERENCES-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qby_copy_with_handle_supports_references_icp_version,
	    FIX((SI_Long)16L));
    Qreturn_g2ds_version_sends_class_icp_version = 
	    STATIC_SYMBOL("RETURN-G2DS-VERSION-SENDS-CLASS-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qreturn_g2ds_version_sends_class_icp_version,
	    FIX((SI_Long)17L));
    Qsupports_non_resumability_icp_version = 
	    STATIC_SYMBOL("SUPPORTS-NON-RESUMABILITY-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qsupports_non_resumability_icp_version,FIX((SI_Long)17L));
    Qgsi_sends_returned_gsi_sensor_as_reference_icp_version = 
	    STATIC_SYMBOL("GSI-SENDS-RETURNED-GSI-SENSOR-AS-REFERENCE-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qgsi_sends_returned_gsi_sensor_as_reference_icp_version,
	    FIX((SI_Long)18L));
    Qno_licence_icp_version = STATIC_SYMBOL("NO-LICENCE-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qno_licence_icp_version,FIX((SI_Long)18L));
    Qsupports_new_references_icp_version = 
	    STATIC_SYMBOL("SUPPORTS-NEW-REFERENCES-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qsupports_new_references_icp_version,FIX((SI_Long)18L));
    Qg2_supports_update_with_delete_icp_version = 
	    STATIC_SYMBOL("G2-SUPPORTS-UPDATE-WITH-DELETE-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2_supports_update_with_delete_icp_version,
	    FIX((SI_Long)19L));
    Qt2_supports_item_layer_change = 
	    STATIC_SYMBOL("T2-SUPPORTS-ITEM-LAYER-CHANGE",AB_package);
    SET_SYMBOL_VALUE(Qt2_supports_item_layer_change,FIX((SI_Long)20L));
    Qdo_not_reformat_message_icp_version = 
	    STATIC_SYMBOL("DO-NOT-REFORMAT-MESSAGE-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qdo_not_reformat_message_icp_version,FIX((SI_Long)21L));
    Qno_frame_serial_index_space_icp_version = 
	    STATIC_SYMBOL("NO-FRAME-SERIAL-INDEX-SPACE-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qno_frame_serial_index_space_icp_version,
	    FIX((SI_Long)21L));
    Qintern_keyword_icp_version = 
	    STATIC_SYMBOL("INTERN-KEYWORD-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qintern_keyword_icp_version,FIX((SI_Long)22L));
    Qlong_string_icp_version = STATIC_SYMBOL("LONG-STRING-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qlong_string_icp_version,FIX((SI_Long)23L));
    Qsend_text_of_expressions_for_g2ds_icp_version = 
	    STATIC_SYMBOL("SEND-TEXT-OF-EXPRESSIONS-FOR-G2DS-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qsend_text_of_expressions_for_g2ds_icp_version,
	    FIX((SI_Long)24L));
    Qremote_procedure_include_all_system_attributes_except_icp_version = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-INCLUDE-ALL-SYSTEM-ATTRIBUTES-EXCEPT-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qremote_procedure_include_all_system_attributes_except_icp_version,
	    FIX((SI_Long)25L));
    Qtransparent_color_index_icp_version = 
	    STATIC_SYMBOL("TRANSPARENT-COLOR-INDEX-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qtransparent_color_index_icp_version,FIX((SI_Long)26L));
    Qcompressed_image_data_chunk_icp_version = 
	    STATIC_SYMBOL("COMPRESSED-IMAGE-DATA-CHUNK-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qcompressed_image_data_chunk_icp_version,
	    FIX((SI_Long)27L));
    Qdialog_component_with_font_icp_version = 
	    STATIC_SYMBOL("DIALOG-COMPONENT-WITH-FONT-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qdialog_component_with_font_icp_version,
	    FIX((SI_Long)28L));
    Qsupports_font_in_grid_view_icp_version = 
	    STATIC_SYMBOL("SUPPORTS-FONT-IN-GRID-VIEW-ICP-VERSION",AB_package);
    SET_SYMBOL_VALUE(Qsupports_font_in_grid_view_icp_version,
	    FIX((SI_Long)29L));
    Qnative_long_icp_version = STATIC_SYMBOL("NATIVE-LONG-ICP-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE(Qnative_long_icp_version,FIX((SI_Long)30L));
    Newest_icp_version = FIX((SI_Long)30L);
    Gsi_connection_initializing = FIX((SI_Long)1L);
    Gsi_connection_established = FIX((SI_Long)2L);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_socket_g2_struct = 
	    STATIC_SYMBOL("SOCKET-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qsocket = STATIC_SYMBOL("SOCKET",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_socket_g2_struct,
	    Qsocket,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qsocket,
	    Qg2_defstruct_structure_name_socket_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_socket == UNBOUND)
	The_type_description_of_socket = Nil;
    string_constant_20 = 
	    STATIC_STRING("43Dy8m832ky1n832ky8n8k1l8n0000000klk0k0");
    temp = The_type_description_of_socket;
    The_type_description_of_socket = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_20));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_socket_g2_struct,
	    The_type_description_of_socket,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qsocket,The_type_description_of_socket,
	    Qtype_description_of_type);
    Qoutstanding_socket_count = STATIC_SYMBOL("OUTSTANDING-SOCKET-COUNT",
	    AB_package);
    Qsocket_structure_memory_usage = 
	    STATIC_SYMBOL("SOCKET-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_21 = STATIC_STRING("1q832ky8s83-qCy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_socket_count);
    push_optimized_constant(Qsocket_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_21));
    Qchain_of_available_sockets = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-SOCKETS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_sockets,
	    Chain_of_available_sockets);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_sockets,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qsocket_count = STATIC_SYMBOL("SOCKET-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsocket_count,Socket_count);
    record_system_variable(Qsocket_count,Qutilities2,FIX((SI_Long)0L),Qnil,
	    Qt,Qnil,Qnil);
    if (Chain_of_available_sockets_vector == UNBOUND)
	Chain_of_available_sockets_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qsocket_structure_memory_usage,
	    STATIC_FUNCTION(socket_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_socket_count,
	    STATIC_FUNCTION(outstanding_socket_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_socket_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_socket,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qsocket,
	    reclaim_structure_for_socket_1);
    Qg2_defstruct_structure_name_icp_socket_g2_struct = 
	    STATIC_SYMBOL("ICP-SOCKET-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qicp_socket = STATIC_SYMBOL("ICP-SOCKET",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_icp_socket_g2_struct,
	    Qicp_socket,Qab_name_of_unique_structure_type);
    mutate_global_property(Qicp_socket,
	    Qg2_defstruct_structure_name_icp_socket_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_icp_socket == UNBOUND)
	The_type_description_of_icp_socket = Nil;
    string_constant_22 = 
	    STATIC_STRING("43Dy8m83ily1o83ily832ky8n8k1l832ky0000001n1m8x832ky1n8y83-4Ry1p83-FQy83-==y83-=0y83-2Ly83-=3y1m83My83-AZyk3qyk0k0");
    temp = The_type_description_of_icp_socket;
    The_type_description_of_icp_socket = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_22));
    mutate_global_property(Qg2_defstruct_structure_name_icp_socket_g2_struct,
	    The_type_description_of_icp_socket,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qicp_socket,The_type_description_of_icp_socket,
	    Qtype_description_of_type);
    Qoutstanding_icp_socket_count = 
	    STATIC_SYMBOL("OUTSTANDING-ICP-SOCKET-COUNT",AB_package);
    Qicp_socket_structure_memory_usage = 
	    STATIC_SYMBOL("ICP-SOCKET-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_23 = STATIC_STRING("1q83ily8s83-Yry09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_icp_socket_count);
    push_optimized_constant(Qicp_socket_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_23));
    Qchain_of_available_icp_sockets = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ICP-SOCKETS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_icp_sockets,
	    Chain_of_available_icp_sockets);
    record_system_variable(Qchain_of_available_icp_sockets,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qicp_socket_count = STATIC_SYMBOL("ICP-SOCKET-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qicp_socket_count,Icp_socket_count);
    record_system_variable(Qicp_socket_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_icp_sockets_vector == UNBOUND)
	Chain_of_available_icp_sockets_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qicp_socket_structure_memory_usage,
	    STATIC_FUNCTION(icp_socket_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_icp_socket_count,
	    STATIC_FUNCTION(outstanding_icp_socket_count,NIL,FALSE,0,0));
    reclaim_structure_for_icp_socket_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_icp_socket,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qicp_socket,
	    reclaim_structure_for_icp_socket_1);
    Qinitial = STATIC_SYMBOL("INITIAL",AB_package);
    Qunknown = STATIC_SYMBOL("UNKNOWN",AB_package);
    Qavailable_icp_callback_conses = 
	    STATIC_SYMBOL("AVAILABLE-ICP-CALLBACK-CONSES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_icp_callback_conses,
	    Available_icp_callback_conses);
    record_system_variable(Qavailable_icp_callback_conses,Qint1,Nil,Qnil,
	    Qt,Qnil,Qnil);
    Qavailable_icp_callback_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-ICP-CALLBACK-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_icp_callback_conses_tail,
	    Available_icp_callback_conses_tail);
    record_system_variable(Qavailable_icp_callback_conses_tail,Qint1,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_icp_callback_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-ICP-CALLBACK-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_icp_callback_conses_vector,
	    Available_icp_callback_conses_vector);
    record_system_variable(Qavailable_icp_callback_conses_vector,Qint1,
	    list_constant_5,Qnil,Qt,Qnil,Qnil);
    Qavailable_icp_callback_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-ICP-CALLBACK-CONSES-TAIL-VECTOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_icp_callback_conses_tail_vector,
	    Available_icp_callback_conses_tail_vector);
    record_system_variable(Qavailable_icp_callback_conses_tail_vector,
	    Qint1,list_constant_5,Qnil,Qt,Qnil,Qnil);
    Qicp_callback_cons_counter_vector = 
	    STATIC_SYMBOL("ICP-CALLBACK-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qicp_callback_cons_counter_vector,
	    Icp_callback_cons_counter_vector);
    record_system_variable(Qicp_callback_cons_counter_vector,Qint1,
	    list_constant_6,Qnil,Qt,Qnil,Qnil);
    Qicp_callback_cons_counter = STATIC_SYMBOL("ICP-CALLBACK-CONS-COUNTER",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qicp_callback_cons_counter,
	    Icp_callback_cons_counter);
    record_system_variable(Qicp_callback_cons_counter,Qint1,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_icp_callback_conses = 
	    STATIC_SYMBOL("OUTSTANDING-ICP-CALLBACK-CONSES",AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_icp_callback_conses,
	    STATIC_FUNCTION(outstanding_icp_callback_conses,NIL,FALSE,0,0));
    Qicp_callback_cons_memory_usage = 
	    STATIC_SYMBOL("ICP-CALLBACK-CONS-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qicp_callback_cons_memory_usage,
	    STATIC_FUNCTION(icp_callback_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_24 = STATIC_STRING("1q83-=-y9k83-=+y09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_icp_callback_conses);
    push_optimized_constant(Qicp_callback_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_24));
    Qicp_callback = STATIC_SYMBOL("ICP-CALLBACK",AB_package);
    list_constant_20 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)57344L);
    array_constant_1 = STATIC_ARRAY(list_constant_20,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    string_constant_8 = STATIC_STRING("ICP-SOCKET ");
    Qclosed = STATIC_SYMBOL("CLOSED",AB_package);
    list_constant_21 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)0L),Qclosed);
    Qconnect_in_progress = STATIC_SYMBOL("CONNECT-IN-PROGRESS",AB_package);
    list_constant_22 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)1L),
	    Qconnect_in_progress);
    Qrunning = STATIC_SYMBOL("RUNNING",AB_package);
    list_constant_23 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)2L),Qrunning);
    Qshutdown_requested = STATIC_SYMBOL("SHUTDOWN-REQUESTED",AB_package);
    list_constant_24 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)3L),
	    Qshutdown_requested);
    Qshutdown_acknowledgement_rundown = 
	    STATIC_SYMBOL("SHUTDOWN-ACKNOWLEDGEMENT-RUNDOWN",AB_package);
    list_constant_25 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)4L),
	    Qshutdown_acknowledgement_rundown);
    Qawaiting_acknowledgement = STATIC_SYMBOL("AWAITING-ACKNOWLEDGEMENT",
	    AB_package);
    list_constant_26 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)5L),
	    Qawaiting_acknowledgement);
    Qlistening = STATIC_SYMBOL("LISTENING",AB_package);
    list_constant_27 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)6L),Qlistening);
    list_constant_28 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)7L),Qerror);
    list_constant_2 = STATIC_LIST((SI_Long)8L,list_constant_21,
	    list_constant_22,list_constant_23,list_constant_24,
	    list_constant_25,list_constant_26,list_constant_27,
	    list_constant_28);
    Qbizzare_state = STATIC_SYMBOL("BIZZARE-STATE",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qnil,Qbizzare_state);
    string_constant_9 = STATIC_STRING(" in state ~D (~a)");
    Qg2_defstruct_structure_name_i_am_alive_info_g2_struct = 
	    STATIC_SYMBOL("I-AM-ALIVE-INFO-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qi_am_alive_info = STATIC_SYMBOL("I-AM-ALIVE-INFO",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_i_am_alive_info_g2_struct,
	    Qi_am_alive_info,Qab_name_of_unique_structure_type);
    mutate_global_property(Qi_am_alive_info,
	    Qg2_defstruct_structure_name_i_am_alive_info_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_i_am_alive_info == UNBOUND)
	The_type_description_of_i_am_alive_info = Nil;
    string_constant_25 = 
	    STATIC_STRING("43Dy8m83iYy1n83iYy8n8k1l8n0000001l1m831uy831Jyk3Eyk0k0");
    temp = The_type_description_of_i_am_alive_info;
    The_type_description_of_i_am_alive_info = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_25));
    mutate_global_property(Qg2_defstruct_structure_name_i_am_alive_info_g2_struct,
	    The_type_description_of_i_am_alive_info,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qi_am_alive_info,
	    The_type_description_of_i_am_alive_info,Qtype_description_of_type);
    Qoutstanding_i_am_alive_info_count = 
	    STATIC_SYMBOL("OUTSTANDING-I-AM-ALIVE-INFO-COUNT",AB_package);
    Qi_am_alive_info_structure_memory_usage = 
	    STATIC_SYMBOL("I-AM-ALIVE-INFO-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_26 = STATIC_STRING("1q83iYy8s83-YLy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_i_am_alive_info_count);
    push_optimized_constant(Qi_am_alive_info_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_26));
    Qchain_of_available_i_am_alive_infos = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-I-AM-ALIVE-INFOS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_i_am_alive_infos,
	    Chain_of_available_i_am_alive_infos);
    record_system_variable(Qchain_of_available_i_am_alive_infos,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qi_am_alive_info_count = STATIC_SYMBOL("I-AM-ALIVE-INFO-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qi_am_alive_info_count,I_am_alive_info_count);
    record_system_variable(Qi_am_alive_info_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_i_am_alive_infos_vector == UNBOUND)
	Chain_of_available_i_am_alive_infos_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qi_am_alive_info_structure_memory_usage,
	    STATIC_FUNCTION(i_am_alive_info_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_i_am_alive_info_count,
	    STATIC_FUNCTION(outstanding_i_am_alive_info_count,NIL,FALSE,0,0));
    reclaim_structure_for_i_am_alive_info_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_i_am_alive_info,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qi_am_alive_info,
	    reclaim_structure_for_i_am_alive_info_1);
    Qhighest_icp_socket_session_id = 
	    STATIC_SYMBOL("HIGHEST-ICP-SOCKET-SESSION-ID",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qhighest_icp_socket_session_id,
	    Highest_icp_socket_session_id);
    record_system_variable(Qhighest_icp_socket_session_id,Qint1,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qtemporary_output = STATIC_SYMBOL("TEMPORARY-OUTPUT",AB_package);
    Qinput = STATIC_SYMBOL("INPUT",AB_package);
    Qoutput = STATIC_SYMBOL("OUTPUT",AB_package);
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qicp_connection_timeout_task_1 = 
	    STATIC_SYMBOL("ICP-CONNECTION-TIMEOUT-TASK-1",AB_package);
    Qicp_connection_timeout_task_2 = 
	    STATIC_SYMBOL("ICP-CONNECTION-TIMEOUT-TASK-2",AB_package);
    SET_SYMBOL_FUNCTION(Qicp_connection_timeout_task_1,
	    STATIC_FUNCTION(icp_connection_timeout_task_1,NIL,FALSE,2,2));
    Qconnection_attempt_timed_out = 
	    STATIC_SYMBOL("CONNECTION-ATTEMPT-TIMED-OUT",AB_package);
    SET_SYMBOL_FUNCTION(Qicp_connection_timeout_task_2,
	    STATIC_FUNCTION(icp_connection_timeout_task_2,NIL,FALSE,1,1));
    Qavailable_frame_serial_number_to_item_table_hash_vector_67_vectors = 
	    STATIC_SYMBOL("AVAILABLE-FRAME-SERIAL-NUMBER-TO-ITEM-TABLE-HASH-VECTOR-67-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_frame_serial_number_to_item_table_hash_vector_67_vectors,
	    Available_frame_serial_number_to_item_table_hash_vector_67_vectors);
    record_system_variable(Qavailable_frame_serial_number_to_item_table_hash_vector_67_vectors,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcount_of_frame_serial_number_to_item_table_hash_vector_67_vectors = 
	    STATIC_SYMBOL("COUNT-OF-FRAME-SERIAL-NUMBER-TO-ITEM-TABLE-HASH-VECTOR-67-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcount_of_frame_serial_number_to_item_table_hash_vector_67_vectors,
	    Count_of_frame_serial_number_to_item_table_hash_vector_67_vectors);
    record_system_variable(Qcount_of_frame_serial_number_to_item_table_hash_vector_67_vectors,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Available_frame_serial_number_to_item_table_hash_vector_67_vectors_vector 
	    == UNBOUND)
	Available_frame_serial_number_to_item_table_hash_vector_67_vectors_vector 
		= make_thread_array(Nil);
    Qout_frame_serial_number_to_item_table_hash_vector_67_vectors = 
	    STATIC_SYMBOL("OUT-FRAME-SERIAL-NUMBER-TO-ITEM-TABLE-HASH-VECTOR-67-VECTORS",
	    AB_package);
    Qframe_serial_number_to_item_table_hash_vector_67_vector_memory_usage 
	    = 
	    STATIC_SYMBOL("FRAME-SERIAL-NUMBER-TO-ITEM-TABLE-HASH-VECTOR-67-VECTOR-MEMORY-USAGE",
	    AB_package);
    string_constant_27 = STATIC_STRING("1q83-V3y83*9y83-Ory09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qout_frame_serial_number_to_item_table_hash_vector_67_vectors);
    push_optimized_constant(Qframe_serial_number_to_item_table_hash_vector_67_vector_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_27));
    SET_SYMBOL_FUNCTION(Qframe_serial_number_to_item_table_hash_vector_67_vector_memory_usage,
	    STATIC_FUNCTION(frame_serial_number_to_item_table_hash_vector_67_vector_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qout_frame_serial_number_to_item_table_hash_vector_67_vectors,
	    STATIC_FUNCTION(out_frame_serial_number_to_item_table_hash_vector_67_vectors,
	    NIL,FALSE,0,0));
    Qvector_pool = STATIC_SYMBOL("VECTOR-POOL",AB_package);
    Qsentinel_node = STATIC_SYMBOL("SENTINEL-NODE",AB_package);
    Qhead = STATIC_SYMBOL("HEAD",AB_package);
    Qtail = STATIC_SYMBOL("TAIL",AB_package);
    Qmutate_frame_serial_number_to_item_table_tree_for_hash_skip_list_entry 
	    = 
	    STATIC_SYMBOL("MUTATE-FRAME-SERIAL-NUMBER-TO-ITEM-TABLE-TREE-FOR-HASH-SKIP-LIST-ENTRY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmutate_frame_serial_number_to_item_table_tree_for_hash_skip_list_entry,
	    STATIC_FUNCTION(mutate_frame_serial_number_to_item_table_tree_for_hash_skip_list_entry,
	    NIL,FALSE,3,3));
    Fp_mutate_frame_serial_number_to_item_table_tree_for_hash_skip_list_entry 
	    = 
	    SYMBOL_FUNCTION(Qmutate_frame_serial_number_to_item_table_tree_for_hash_skip_list_entry);
    Qframe_serial_number_to_item_table_tree_for_hash = 
	    STATIC_SYMBOL("FRAME-SERIAL-NUMBER-TO-ITEM-TABLE-TREE-FOR-HASH",
	    AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qavailable_variable_fill_icp_buffer_4096_vectors = 
	    STATIC_SYMBOL("AVAILABLE-VARIABLE-FILL-ICP-BUFFER-4096-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_variable_fill_icp_buffer_4096_vectors,
	    Available_variable_fill_icp_buffer_4096_vectors);
    record_system_variable(Qavailable_variable_fill_icp_buffer_4096_vectors,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcount_of_variable_fill_icp_buffer_4096_vectors = 
	    STATIC_SYMBOL("COUNT-OF-VARIABLE-FILL-ICP-BUFFER-4096-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcount_of_variable_fill_icp_buffer_4096_vectors,
	    Count_of_variable_fill_icp_buffer_4096_vectors);
    record_system_variable(Qcount_of_variable_fill_icp_buffer_4096_vectors,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Available_variable_fill_icp_buffer_4096_vectors_vector == UNBOUND)
	Available_variable_fill_icp_buffer_4096_vectors_vector = 
		make_thread_array(Nil);
    Qout_variable_fill_icp_buffer_4096_vectors = 
	    STATIC_SYMBOL("OUT-VARIABLE-FILL-ICP-BUFFER-4096-VECTORS",
	    AB_package);
    Qvariable_fill_icp_buffer_4096_vector_memory_usage = 
	    STATIC_SYMBOL("VARIABLE-FILL-ICP-BUFFER-4096-VECTOR-MEMORY-USAGE",
	    AB_package);
    string_constant_28 = 
	    STATIC_STRING("1q83-wDy1n83a1y1m83oFys1l3-++y83-PIy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qout_variable_fill_icp_buffer_4096_vectors);
    push_optimized_constant(Qvariable_fill_icp_buffer_4096_vector_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_28));
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,FIX((SI_Long)8L));
    SET_SYMBOL_FUNCTION(Qvariable_fill_icp_buffer_4096_vector_memory_usage,
	    STATIC_FUNCTION(variable_fill_icp_buffer_4096_vector_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qout_variable_fill_icp_buffer_4096_vectors,
	    STATIC_FUNCTION(out_variable_fill_icp_buffer_4096_vectors,NIL,
	    FALSE,0,0));
    Qrecycled_variable_fill_icp_buffers = 
	    STATIC_SYMBOL("RECYCLED-VARIABLE-FILL-ICP-BUFFERS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qrecycled_variable_fill_icp_buffers,
	    Recycled_variable_fill_icp_buffers);
    Qint2 = STATIC_SYMBOL("INT2",AB_package);
    record_system_variable(Qrecycled_variable_fill_icp_buffers,Qint2,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qtransmitted_variable_fill_icp_buffers = 
	    STATIC_SYMBOL("TRANSMITTED-VARIABLE-FILL-ICP-BUFFERS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtransmitted_variable_fill_icp_buffers,
	    Transmitted_variable_fill_icp_buffers);
    record_system_variable(Qtransmitted_variable_fill_icp_buffers,Qint2,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qavailable_icp_buffer_ref_count_conses = 
	    STATIC_SYMBOL("AVAILABLE-ICP-BUFFER-REF-COUNT-CONSES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_icp_buffer_ref_count_conses,
	    Available_icp_buffer_ref_count_conses);
    record_system_variable(Qavailable_icp_buffer_ref_count_conses,Qint1,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qavailable_icp_buffer_ref_count_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-ICP-BUFFER-REF-COUNT-CONSES-TAIL",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_icp_buffer_ref_count_conses_tail,
	    Available_icp_buffer_ref_count_conses_tail);
    record_system_variable(Qavailable_icp_buffer_ref_count_conses_tail,
	    Qint1,Nil,Qnil,Qt,Qnil,Qnil);
    Qavailable_icp_buffer_ref_count_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-ICP-BUFFER-REF-COUNT-CONSES-VECTOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_icp_buffer_ref_count_conses_vector,
	    Available_icp_buffer_ref_count_conses_vector);
    record_system_variable(Qavailable_icp_buffer_ref_count_conses_vector,
	    Qint1,list_constant_5,Qnil,Qt,Qnil,Qnil);
    Qavailable_icp_buffer_ref_count_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-ICP-BUFFER-REF-COUNT-CONSES-TAIL-VECTOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_icp_buffer_ref_count_conses_tail_vector,
	    Available_icp_buffer_ref_count_conses_tail_vector);
    record_system_variable(Qavailable_icp_buffer_ref_count_conses_tail_vector,
	    Qint1,list_constant_5,Qnil,Qt,Qnil,Qnil);
    Qicp_buffer_ref_count_cons_counter_vector = 
	    STATIC_SYMBOL("ICP-BUFFER-REF-COUNT-CONS-COUNTER-VECTOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qicp_buffer_ref_count_cons_counter_vector,
	    Icp_buffer_ref_count_cons_counter_vector);
    record_system_variable(Qicp_buffer_ref_count_cons_counter_vector,Qint1,
	    list_constant_6,Qnil,Qt,Qnil,Qnil);
    Qicp_buffer_ref_count_cons_counter = 
	    STATIC_SYMBOL("ICP-BUFFER-REF-COUNT-CONS-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qicp_buffer_ref_count_cons_counter,
	    Icp_buffer_ref_count_cons_counter);
    record_system_variable(Qicp_buffer_ref_count_cons_counter,Qint1,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_icp_buffer_ref_count_conses = 
	    STATIC_SYMBOL("OUTSTANDING-ICP-BUFFER-REF-COUNT-CONSES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_icp_buffer_ref_count_conses,
	    STATIC_FUNCTION(outstanding_icp_buffer_ref_count_conses,NIL,
	    FALSE,0,0));
    Qicp_buffer_ref_count_cons_memory_usage = 
	    STATIC_SYMBOL("ICP-BUFFER-REF-COUNT-CONS-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qicp_buffer_ref_count_cons_memory_usage,
	    STATIC_FUNCTION(icp_buffer_ref_count_cons_memory_usage,NIL,
	    FALSE,0,0));
    string_constant_29 = STATIC_STRING("1q83-Ymy9k83-Yly09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_icp_buffer_ref_count_conses);
    push_optimized_constant(Qicp_buffer_ref_count_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_29));
    Qicp_buffer_ref_count = STATIC_SYMBOL("ICP-BUFFER-REF-COUNT",AB_package);
    Qg2_defstruct_structure_name_icp_buffer_g2_struct = 
	    STATIC_SYMBOL("ICP-BUFFER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qicp_buffer = STATIC_SYMBOL("ICP-BUFFER",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_icp_buffer_g2_struct,
	    Qicp_buffer,Qab_name_of_unique_structure_type);
    mutate_global_property(Qicp_buffer,
	    Qg2_defstruct_structure_name_icp_buffer_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_icp_buffer == UNBOUND)
	The_type_description_of_icp_buffer = Nil;
    string_constant_30 = 
	    STATIC_STRING("43Dy8m83iiy1n83iiy8n8k1l8n0000001m1n8y83-4Oy1l83-*xy1m83My83-AXykqk0k0");
    temp = The_type_description_of_icp_buffer;
    The_type_description_of_icp_buffer = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_30));
    mutate_global_property(Qg2_defstruct_structure_name_icp_buffer_g2_struct,
	    The_type_description_of_icp_buffer,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qicp_buffer,The_type_description_of_icp_buffer,
	    Qtype_description_of_type);
    Qoutstanding_icp_buffer_count = 
	    STATIC_SYMBOL("OUTSTANDING-ICP-BUFFER-COUNT",AB_package);
    Qicp_buffer_structure_memory_usage = 
	    STATIC_SYMBOL("ICP-BUFFER-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_31 = STATIC_STRING("1q83iiy8s83-Yky09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_icp_buffer_count);
    push_optimized_constant(Qicp_buffer_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_31));
    Qchain_of_available_icp_buffers = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ICP-BUFFERS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_icp_buffers,
	    Chain_of_available_icp_buffers);
    record_system_variable(Qchain_of_available_icp_buffers,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qicp_buffer_count = STATIC_SYMBOL("ICP-BUFFER-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qicp_buffer_count,Icp_buffer_count);
    record_system_variable(Qicp_buffer_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_icp_buffers_vector == UNBOUND)
	Chain_of_available_icp_buffers_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qicp_buffer_structure_memory_usage,
	    STATIC_FUNCTION(icp_buffer_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_icp_buffer_count,
	    STATIC_FUNCTION(outstanding_icp_buffer_count,NIL,FALSE,0,0));
    reclaim_structure_for_icp_buffer_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_icp_buffer,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qicp_buffer,
	    reclaim_structure_for_icp_buffer_1);
    Qrecycled_icp_buffers = STATIC_SYMBOL("RECYCLED-ICP-BUFFERS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qrecycled_icp_buffers,Recycled_icp_buffers);
    record_system_variable(Qrecycled_icp_buffers,Qint2,Nil,Qnil,Qnil,Qnil,
	    Qnil);
    Qg2_defstruct_structure_name_icp_port_g2_struct = 
	    STATIC_SYMBOL("ICP-PORT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qicp_port = STATIC_SYMBOL("ICP-PORT",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_icp_port_g2_struct,
	    Qicp_port,Qab_name_of_unique_structure_type);
    mutate_global_property(Qicp_port,
	    Qg2_defstruct_structure_name_icp_port_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_icp_port == UNBOUND)
	The_type_description_of_icp_port = Nil;
    string_constant_32 = 
	    STATIC_STRING("43Dy8m83ijy1n83ijy8n8k1l8n0000001m1n8y83-4Py1o83-=*y83-8gy83-=1y83-A=y1m83My83-AYyk3Gyk0k0");
    temp = The_type_description_of_icp_port;
    The_type_description_of_icp_port = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_32));
    mutate_global_property(Qg2_defstruct_structure_name_icp_port_g2_struct,
	    The_type_description_of_icp_port,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qicp_port,The_type_description_of_icp_port,
	    Qtype_description_of_type);
    Qoutstanding_icp_port_count = 
	    STATIC_SYMBOL("OUTSTANDING-ICP-PORT-COUNT",AB_package);
    Qicp_port_structure_memory_usage = 
	    STATIC_SYMBOL("ICP-PORT-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_33 = STATIC_STRING("1q83ijy8s83-Ypy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_icp_port_count);
    push_optimized_constant(Qicp_port_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_33));
    Qchain_of_available_icp_ports = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ICP-PORTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_icp_ports,
	    Chain_of_available_icp_ports);
    record_system_variable(Qchain_of_available_icp_ports,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qicp_port_count = STATIC_SYMBOL("ICP-PORT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qicp_port_count,Icp_port_count);
    record_system_variable(Qicp_port_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_icp_ports_vector == UNBOUND)
	Chain_of_available_icp_ports_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qicp_port_structure_memory_usage,
	    STATIC_FUNCTION(icp_port_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_icp_port_count,
	    STATIC_FUNCTION(outstanding_icp_port_count,NIL,FALSE,0,0));
    reclaim_structure_for_icp_port_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_icp_port,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qicp_port,
	    reclaim_structure_for_icp_port_1);
    SET_SYMBOL_FUNCTION(Qitem_index_space,STATIC_FUNCTION(item_index_space,
	    NIL,FALSE,1,1));
    Qitem_with_handle_index_space = 
	    STATIC_SYMBOL("ITEM-WITH-HANDLE-INDEX-SPACE",AB_package);
    SET_SYMBOL_FUNCTION(Qitem_with_handle_index_space,
	    STATIC_FUNCTION(item_with_handle_index_space,NIL,FALSE,1,1));
    Qcurrent_icp_port = STATIC_SYMBOL("CURRENT-ICP-PORT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_icp_port,Current_icp_port);
    record_system_variable(Qcurrent_icp_port,Qint1,Nil,Qnil,Qnil,Qnil,Qnil);
    if (Current_icp_socket == UNBOUND)
	Current_icp_socket = Nil;
    Qcurrent_standard_icp_object_index_space = 
	    STATIC_SYMBOL("CURRENT-STANDARD-ICP-OBJECT-INDEX-SPACE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_standard_icp_object_index_space,
	    Current_standard_icp_object_index_space);
    record_system_variable(Qcurrent_standard_icp_object_index_space,Qint1,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qcurrent_temporary_icp_object_index_space = 
	    STATIC_SYMBOL("CURRENT-TEMPORARY-ICP-OBJECT-INDEX-SPACE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_temporary_icp_object_index_space,
	    Current_temporary_icp_object_index_space);
    record_system_variable(Qcurrent_temporary_icp_object_index_space,Qint1,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2 = STATIC_SYMBOL("G2",AB_package);
    Qframe_serial_number = STATIC_SYMBOL("FRAME-SERIAL-NUMBER",AB_package);
    if (Do_not_reclaim_runs_while_inactive_entries == UNBOUND)
	Do_not_reclaim_runs_while_inactive_entries = Nil;
    if (Icp_output_ports_to_flush == UNBOUND)
	Icp_output_ports_to_flush = Nil;
    if (With_icp_buffer_coelescing_scope_qm == UNBOUND)
	With_icp_buffer_coelescing_scope_qm = Nil;
    Qflush_icp_output_ports = STATIC_SYMBOL("FLUSH-ICP-OUTPUT-PORTS",
	    AB_package);
    def_bombout_clean_up_function(Qflush_icp_output_ports);
    SET_SYMBOL_FUNCTION(Qflush_icp_output_ports,
	    STATIC_FUNCTION(flush_icp_output_ports,NIL,FALSE,0,0));
    if (Disable_resumability == UNBOUND)
	Disable_resumability = Nil;
    if (Resumable_icp_state == UNBOUND)
	Resumable_icp_state = Nil;
    Qsuspend = STATIC_SYMBOL("SUSPEND",AB_package);
    if (Icp_suspend == UNBOUND)
	Icp_suspend = LIST_1(Qsuspend);
    Qresumable_icp_list_end = STATIC_SYMBOL("RESUMABLE-ICP-LIST-END",
	    AB_package);
    if (Trif_block_value_alist == UNBOUND)
	Trif_block_value_alist = Nil;
}
