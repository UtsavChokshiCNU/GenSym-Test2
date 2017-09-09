/* rpcmn1.c
 * Input file:  rpc-common1.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "rpcmn1.h"


DEFINE_VARIABLE_WITH_SYMBOL(Available_proc_conses, Qavailable_proc_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_proc_conses_tail, Qavailable_proc_conses_tail);

Object Available_proc_conses_vector = UNBOUND;

Object Available_proc_conses_tail_vector = UNBOUND;

Object Proc_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Proc_cons_counter, Qproc_cons_counter);

/* OUTSTANDING-PROC-CONSES */
Object outstanding_proc_conses()
{
    Object temp;

    x_note_fn_call(157,0);
    temp = FIXNUM_MINUS(Proc_cons_counter,length(Available_proc_conses));
    return VALUES_1(temp);
}

/* PROC-CONS-MEMORY-USAGE */
Object proc_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(157,1);
    temp = FIXNUM_TIMES(Proc_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-PROC-CONS-POOL */
Object replenish_proc_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(157,2);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qproc_cons_counter,Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_proc_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_proc_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_proc_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_proc_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_proc_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Proc_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qproc;               /* proc */

/* PROC-CONS-1 */
Object proc_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(157,3);
    new_cons = ISVREF(Available_proc_conses_vector,IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_proc_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_proc_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_proc_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_proc_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qproc);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-PROC-LIST-POOL */
Object replenish_proc_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(157,4);
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
    if (ISVREF(Available_proc_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_proc_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_proc_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_proc_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_proc_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qproc_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-PROC-LIST-1 */
Object make_proc_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(157,5);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_proc_conses_vector,
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
	replenish_proc_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_proc_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qproc);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_proc_conses_vector,IFIX(Current_thread_index));
	svref_arg_1 = Available_proc_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_proc_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_proc_conses_tail_vector;
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

/* PROC-LIST-2 */
Object proc_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(157,6);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_proc_conses_vector,IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_proc_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_proc_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qproc);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_proc_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_proc_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_proc_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_proc_conses_tail_vector;
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

/* PROC-LIST-3 */
Object proc_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(157,7);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_proc_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_proc_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_proc_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qproc);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_proc_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_proc_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_proc_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_proc_conses_tail_vector;
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

/* PROC-LIST-4 */
Object proc_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(157,8);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_proc_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_proc_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_proc_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qproc);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_proc_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_proc_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_proc_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_proc_conses_tail_vector;
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

/* PROC-LIST-TRACE-HOOK */
Object proc_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(157,9);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-PROC-CONSES-1 */
Object copy_tree_using_proc_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(157,10);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_proc_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_proc_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_proc_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_proc_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_proc_cons_pool();
	temp_1 = copy_tree_using_proc_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qproc);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_proc_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_proc_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_proc_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_proc_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_proc_cons_pool();
	temp_1 = copy_tree_using_proc_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qproc);
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

/* COPY-LIST-USING-PROC-CONSES-1 */
Object copy_list_using_proc_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(157,11);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_proc_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_proc_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_proc_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_proc_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_proc_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qproc);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_proc_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_proc_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_proc_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_proc_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_proc_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qproc);
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

/* RECLAIM-PROC-CONS-1 */
Object reclaim_proc_cons_1(proc_cons)
    Object proc_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(157,12);
    inline_note_reclaim_cons(proc_cons,Qproc);
    if (ISVREF(Available_proc_conses_tail_vector,IFIX(Current_thread_index))) {
	temp = ISVREF(Available_proc_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = proc_cons;
	temp = Available_proc_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = proc_cons;
    }
    else {
	temp = Available_proc_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = proc_cons;
	temp = Available_proc_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = proc_cons;
    }
    M_CDR(proc_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-PROC-LIST-1 */
Object reclaim_proc_list_1(proc_list)
    Object proc_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(157,13);
    if (proc_list) {
	last_1 = proc_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qproc);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qproc);
	if (ISVREF(Available_proc_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_proc_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = proc_list;
	    temp = Available_proc_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_proc_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = proc_list;
	    temp = Available_proc_conses_tail_vector;
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

/* RECLAIM-PROC-LIST*-1 */
Object reclaim_proc_list_star_1(proc_list)
    Object proc_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(157,14);
    if (CONSP(proc_list)) {
	temp = last(proc_list,_);
	M_CDR(temp) = Nil;
	if (proc_list) {
	    last_1 = proc_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qproc);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qproc);
	    if (ISVREF(Available_proc_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_proc_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = proc_list;
		temp = Available_proc_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_proc_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = proc_list;
		temp = Available_proc_conses_tail_vector;
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

/* RECLAIM-PROC-TREE-1 */
Object reclaim_proc_tree_1(tree)
    Object tree;
{
    Object e, e2, proc_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(157,15);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_proc_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		proc_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(proc_cons,Qproc);
		if (EQ(proc_cons,e))
		    goto end_1;
		else if ( !TRUEP(proc_cons))
		    goto end_1;
		else
		    proc_cons = CDR(proc_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_proc_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_proc_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_proc_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_proc_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_proc_conses_tail_vector;
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

/* DELETE-PROC-ELEMENT-1 */
Object delete_proc_element_1(element,proc_list)
    Object element, proc_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(157,16);
    if (proc_list) {
	if (EQ(element,M_CAR(proc_list))) {
	    temp = CDR(proc_list);
	    inline_note_reclaim_cons(proc_list,Qproc);
	    if (ISVREF(Available_proc_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_proc_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = proc_list;
		temp_1 = Available_proc_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = proc_list;
	    }
	    else {
		temp_1 = Available_proc_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = proc_list;
		temp_1 = Available_proc_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = proc_list;
	    }
	    M_CDR(proc_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = proc_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qproc);
		if (ISVREF(Available_proc_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_proc_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_proc_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_proc_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_proc_conses_tail_vector;
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
	    temp = proc_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-PROC-CONS-1 */
Object delete_proc_cons_1(proc_cons,proc_list)
    Object proc_cons, proc_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(157,17);
    if (EQ(proc_cons,proc_list))
	temp = CDR(proc_list);
    else {
	l_trailer_qm = Nil;
	l = proc_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,proc_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = proc_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_proc_cons_1(proc_cons);
    return VALUES_1(temp);
}

Object The_type_description_of_gsi_local_function = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_gsi_local_functions, Qchain_of_available_gsi_local_functions);

DEFINE_VARIABLE_WITH_SYMBOL(Gsi_local_function_count, Qgsi_local_function_count);

Object Chain_of_available_gsi_local_functions_vector = UNBOUND;

/* GSI-LOCAL-FUNCTION-STRUCTURE-MEMORY-USAGE */
Object gsi_local_function_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(157,18);
    temp = Gsi_local_function_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)4L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-GSI-LOCAL-FUNCTION-COUNT */
Object outstanding_gsi_local_function_count()
{
    Object def_structure_gsi_local_function_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(157,19);
    gensymed_symbol = IFIX(Gsi_local_function_count);
    def_structure_gsi_local_function_variable = 
	    Chain_of_available_gsi_local_functions;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_gsi_local_function_variable))
	goto end_loop;
    def_structure_gsi_local_function_variable = 
	    ISVREF(def_structure_gsi_local_function_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-GSI-LOCAL-FUNCTION-1 */
Object reclaim_gsi_local_function_1(gsi_local_function)
    Object gsi_local_function;
{
    Object temp, svref_arg_2;

    x_note_fn_call(157,20);
    inline_note_reclaim_cons(gsi_local_function,Nil);
    temp = ISVREF(Chain_of_available_gsi_local_functions_vector,
	    IFIX(Current_thread_index));
    SVREF(gsi_local_function,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_gsi_local_functions_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = gsi_local_function;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GSI-LOCAL-FUNCTION */
Object reclaim_structure_for_gsi_local_function(gsi_local_function)
    Object gsi_local_function;
{
    x_note_fn_call(157,21);
    return reclaim_gsi_local_function_1(gsi_local_function);
}

static Object Qg2_defstruct_structure_name_gsi_local_function_g2_struct;  /* g2-defstruct-structure-name::gsi-local-function-g2-struct */

/* MAKE-PERMANENT-GSI-LOCAL-FUNCTION-STRUCTURE-INTERNAL */
Object make_permanent_gsi_local_function_structure_internal()
{
    Object def_structure_gsi_local_function_variable;
    Object defstruct_g2_gsi_local_function_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(157,22);
    def_structure_gsi_local_function_variable = Nil;
    atomic_incff_symval(Qgsi_local_function_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_gsi_local_function_variable = Nil;
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
	defstruct_g2_gsi_local_function_variable = the_array;
	SVREF(defstruct_g2_gsi_local_function_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gsi_local_function_g2_struct;
	def_structure_gsi_local_function_variable = 
		defstruct_g2_gsi_local_function_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_gsi_local_function_variable);
}

/* MAKE-GSI-LOCAL-FUNCTION-1 */
Object make_gsi_local_function_1()
{
    Object def_structure_gsi_local_function_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(157,23);
    def_structure_gsi_local_function_variable = 
	    ISVREF(Chain_of_available_gsi_local_functions_vector,
	    IFIX(Current_thread_index));
    if (def_structure_gsi_local_function_variable) {
	svref_arg_1 = Chain_of_available_gsi_local_functions_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_gsi_local_function_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_gsi_local_function_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_gsi_local_function_g2_struct;
    }
    else
	def_structure_gsi_local_function_variable = 
		make_permanent_gsi_local_function_structure_internal();
    inline_note_allocate_cons(def_structure_gsi_local_function_variable,Nil);
    SVREF(def_structure_gsi_local_function_variable,FIX((SI_Long)2L)) = Nil;
    return VALUES_1(def_structure_gsi_local_function_variable);
}

Object The_type_description_of_gsi_remote_procedure = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_gsi_remote_procedures, Qchain_of_available_gsi_remote_procedures);

DEFINE_VARIABLE_WITH_SYMBOL(Gsi_remote_procedure_count, Qgsi_remote_procedure_count);

Object Chain_of_available_gsi_remote_procedures_vector = UNBOUND;

/* GSI-REMOTE-PROCEDURE-STRUCTURE-MEMORY-USAGE */
Object gsi_remote_procedure_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(157,24);
    temp = Gsi_remote_procedure_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)13L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-GSI-REMOTE-PROCEDURE-COUNT */
Object outstanding_gsi_remote_procedure_count()
{
    Object def_structure_gsi_remote_procedure_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(157,25);
    gensymed_symbol = IFIX(Gsi_remote_procedure_count);
    def_structure_gsi_remote_procedure_variable = 
	    Chain_of_available_gsi_remote_procedures;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_gsi_remote_procedure_variable))
	goto end_loop;
    def_structure_gsi_remote_procedure_variable = 
	    ISVREF(def_structure_gsi_remote_procedure_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-GSI-REMOTE-PROCEDURE-INTERNAL-1 */
Object reclaim_gsi_remote_procedure_internal_1(gsi_remote_procedure)
    Object gsi_remote_procedure;
{
    Object temp, svref_arg_2;

    x_note_fn_call(157,26);
    inline_note_reclaim_cons(gsi_remote_procedure,Nil);
    temp = ISVREF(Chain_of_available_gsi_remote_procedures_vector,
	    IFIX(Current_thread_index));
    SVREF(gsi_remote_procedure,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_gsi_remote_procedures_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = gsi_remote_procedure;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GSI-REMOTE-PROCEDURE */
Object reclaim_structure_for_gsi_remote_procedure(gsi_remote_procedure)
    Object gsi_remote_procedure;
{
    x_note_fn_call(157,27);
    return reclaim_gsi_remote_procedure_internal_1(gsi_remote_procedure);
}

static Object Qg2_defstruct_structure_name_gsi_remote_procedure_g2_struct;  /* g2-defstruct-structure-name::gsi-remote-procedure-g2-struct */

/* MAKE-PERMANENT-GSI-REMOTE-PROCEDURE-STRUCTURE-INTERNAL */
Object make_permanent_gsi_remote_procedure_structure_internal()
{
    Object def_structure_gsi_remote_procedure_variable;
    Object defstruct_g2_gsi_remote_procedure_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(157,28);
    def_structure_gsi_remote_procedure_variable = Nil;
    atomic_incff_symval(Qgsi_remote_procedure_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_gsi_remote_procedure_variable = Nil;
	gensymed_symbol = (SI_Long)13L;
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
	defstruct_g2_gsi_remote_procedure_variable = the_array;
	SVREF(defstruct_g2_gsi_remote_procedure_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_gsi_remote_procedure_g2_struct;
	def_structure_gsi_remote_procedure_variable = 
		defstruct_g2_gsi_remote_procedure_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_gsi_remote_procedure_variable);
}

/* MAKE-GSI-REMOTE-PROCEDURE-1 */
Object make_gsi_remote_procedure_1()
{
    Object def_structure_gsi_remote_procedure_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(157,29);
    def_structure_gsi_remote_procedure_variable = 
	    ISVREF(Chain_of_available_gsi_remote_procedures_vector,
	    IFIX(Current_thread_index));
    if (def_structure_gsi_remote_procedure_variable) {
	svref_arg_1 = Chain_of_available_gsi_remote_procedures_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_gsi_remote_procedure_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_gsi_remote_procedure_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gsi_remote_procedure_g2_struct;
    }
    else
	def_structure_gsi_remote_procedure_variable = 
		make_permanent_gsi_remote_procedure_structure_internal();
    inline_note_allocate_cons(def_structure_gsi_remote_procedure_variable,Nil);
    SVREF(def_structure_gsi_remote_procedure_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_gsi_remote_procedure_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_gsi_remote_procedure_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_gsi_remote_procedure_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_gsi_remote_procedure_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_gsi_remote_procedure_variable,FIX((SI_Long)12L)) = Nil;
    return VALUES_1(def_structure_gsi_remote_procedure_variable);
}

/* RECLAIM-GSI-REMOTE-PROCEDURE */
Object reclaim_gsi_remote_procedure(remote_procedure)
    Object remote_procedure;
{
    Object remote_procedure_name_structure;

    x_note_fn_call(157,30);
    remote_procedure_name_structure = ISVREF(remote_procedure,(SI_Long)2L);
    if (remote_procedure_name_structure) {
	reclaim_remote_procedure_name(remote_procedure_name_structure);
	SVREF(remote_procedure,FIX((SI_Long)2L)) = Nil;
    }
    if (ISVREF(remote_procedure,(SI_Long)8L)) {
	reclaim_gensym_list_1(ISVREF(remote_procedure,(SI_Long)8L));
	SVREF(remote_procedure,FIX((SI_Long)8L)) = Nil;
    }
    if (ISVREF(remote_procedure,(SI_Long)9L)) {
	reclaim_gsi_tree_1(ISVREF(remote_procedure,(SI_Long)9L));
	SVREF(remote_procedure,FIX((SI_Long)9L)) = Nil;
    }
    if (ISVREF(remote_procedure,(SI_Long)10L)) {
	reclaim_gsi_tree_1(ISVREF(remote_procedure,(SI_Long)10L));
	SVREF(remote_procedure,FIX((SI_Long)10L)) = Nil;
    }
    if (ISVREF(remote_procedure,(SI_Long)11L)) {
	reclaim_gsi_tree_1(ISVREF(remote_procedure,(SI_Long)11L));
	SVREF(remote_procedure,FIX((SI_Long)11L)) = Nil;
    }
    if (ISVREF(remote_procedure,(SI_Long)12L)) {
	reclaim_gsi_tree_1(ISVREF(remote_procedure,(SI_Long)12L));
	SVREF(remote_procedure,FIX((SI_Long)12L)) = Nil;
    }
    return reclaim_gsi_remote_procedure_internal_1(remote_procedure);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_remote_procedure_identifier, Qcurrent_remote_procedure_identifier);

DEFINE_VARIABLE_WITH_SYMBOL(Current_invocation_remotely_started_p, Qcurrent_invocation_remotely_started_p);

DEFINE_VARIABLE_WITH_SYMBOL(Rpc_argument_count_override_qm, Qrpc_argument_count_override_qm);

Object The_type_description_of_remote_procedure_name = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_remote_procedure_names, Qchain_of_available_remote_procedure_names);

DEFINE_VARIABLE_WITH_SYMBOL(Remote_procedure_name_count, Qremote_procedure_name_count);

Object Chain_of_available_remote_procedure_names_vector = UNBOUND;

/* REMOTE-PROCEDURE-NAME-STRUCTURE-MEMORY-USAGE */
Object remote_procedure_name_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(157,31);
    temp = Remote_procedure_name_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)4L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-REMOTE-PROCEDURE-NAME-COUNT */
Object outstanding_remote_procedure_name_count()
{
    Object def_structure_remote_procedure_name_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(157,32);
    gensymed_symbol = IFIX(Remote_procedure_name_count);
    def_structure_remote_procedure_name_variable = 
	    Chain_of_available_remote_procedure_names;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_remote_procedure_name_variable))
	goto end_loop;
    def_structure_remote_procedure_name_variable = 
	    ISVREF(def_structure_remote_procedure_name_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-REMOTE-PROCEDURE-NAME-INTERNAL-1 */
Object reclaim_remote_procedure_name_internal_1(remote_procedure_name)
    Object remote_procedure_name;
{
    Object temp, svref_arg_2;

    x_note_fn_call(157,33);
    inline_note_reclaim_cons(remote_procedure_name,Nil);
    temp = ISVREF(Chain_of_available_remote_procedure_names_vector,
	    IFIX(Current_thread_index));
    SVREF(remote_procedure_name,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_remote_procedure_names_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = remote_procedure_name;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-REMOTE-PROCEDURE-NAME */
Object reclaim_structure_for_remote_procedure_name(remote_procedure_name)
    Object remote_procedure_name;
{
    x_note_fn_call(157,34);
    return reclaim_remote_procedure_name_internal_1(remote_procedure_name);
}

static Object Qg2_defstruct_structure_name_remote_procedure_name_g2_struct;  /* g2-defstruct-structure-name::remote-procedure-name-g2-struct */

/* MAKE-PERMANENT-REMOTE-PROCEDURE-NAME-STRUCTURE-INTERNAL */
Object make_permanent_remote_procedure_name_structure_internal()
{
    Object def_structure_remote_procedure_name_variable;
    Object defstruct_g2_remote_procedure_name_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(157,35);
    def_structure_remote_procedure_name_variable = Nil;
    atomic_incff_symval(Qremote_procedure_name_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_remote_procedure_name_variable = Nil;
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
	defstruct_g2_remote_procedure_name_variable = the_array;
	SVREF(defstruct_g2_remote_procedure_name_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_remote_procedure_name_g2_struct;
	def_structure_remote_procedure_name_variable = 
		defstruct_g2_remote_procedure_name_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_remote_procedure_name_variable);
}

/* MAKE-REMOTE-PROCEDURE-NAME-1 */
Object make_remote_procedure_name_1(remote_procedure_name_symbol)
    Object remote_procedure_name_symbol;
{
    Object def_structure_remote_procedure_name_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(157,36);
    def_structure_remote_procedure_name_variable = 
	    ISVREF(Chain_of_available_remote_procedure_names_vector,
	    IFIX(Current_thread_index));
    if (def_structure_remote_procedure_name_variable) {
	svref_arg_1 = Chain_of_available_remote_procedure_names_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_remote_procedure_name_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_remote_procedure_name_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_remote_procedure_name_g2_struct;
    }
    else
	def_structure_remote_procedure_name_variable = 
		make_permanent_remote_procedure_name_structure_internal();
    inline_note_allocate_cons(def_structure_remote_procedure_name_variable,
	    Nil);
    SVREF(def_structure_remote_procedure_name_variable,FIX((SI_Long)1L)) = 
	    remote_procedure_name_symbol;
    SVREF(def_structure_remote_procedure_name_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_remote_procedure_name_variable,FIX((SI_Long)3L)) = Nil;
    return VALUES_1(def_structure_remote_procedure_name_variable);
}

/* MAKE-REMOTE-PROCEDURE-NAME-FUNCTION */
Object make_remote_procedure_name_function(remote_procedure_name_symbol)
    Object remote_procedure_name_symbol;
{
    Object temp;

    x_note_fn_call(157,37);
    temp = make_remote_procedure_name_1(remote_procedure_name_symbol);
    return VALUES_1(temp);
}

/* RECLAIM-REMOTE-PROCEDURE-NAME */
Object reclaim_remote_procedure_name(remote_procedure_name)
    Object remote_procedure_name;
{
    Object temp, svref_arg_2;

    x_note_fn_call(157,38);
    reclaim_icp_object_map_for_remote_procedure_name(remote_procedure_name);
    inline_note_reclaim_cons(remote_procedure_name,Nil);
    temp = ISVREF(Chain_of_available_remote_procedure_names_vector,
	    IFIX(Current_thread_index));
    SVREF(remote_procedure_name,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_remote_procedure_names_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = remote_procedure_name;
    return VALUES_1(Nil);
}

/* RECLAIM-REMOTE-PROCEDURE-NAME-STRUCTURE */
Object reclaim_remote_procedure_name_structure(remote_procedure_name)
    Object remote_procedure_name;
{
    Object temp, svref_arg_2;

    x_note_fn_call(157,39);
    inline_note_reclaim_cons(remote_procedure_name,Nil);
    temp = ISVREF(Chain_of_available_remote_procedure_names_vector,
	    IFIX(Current_thread_index));
    SVREF(remote_procedure_name,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_remote_procedure_names_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = remote_procedure_name;
    return VALUES_1(Nil);
}

static Object Qinput;              /* input */

/* RECLAIM-REMOTE-PROCEDURE-NAME-FOR-CONNECTION-LOSS */
Object reclaim_remote_procedure_name_for_connection_loss(remote_procedure_name,
	    icp_port)
    Object remote_procedure_name, icp_port;
{
    x_note_fn_call(157,40);
    if (EQ(ISVREF(icp_port,(SI_Long)3L),Qinput))
	return reclaim_remote_procedure_name(remote_procedure_name);
    else
	return VALUES_1(Nil);
}

static Object Qstandard_icp_object_index_space;  /* standard-icp-object-index-space */

static Object Qestablish_new_object_index_for_remote_procedure_name;  /* establish-new-object-index-for-remote-procedure-name */

static Object string_constant;     /* "resumable icp synch error: ~S expected, ~S found" */

/* ESTABLISH-NEW-OBJECT-INDEX-FOR-REMOTE-PROCEDURE-NAME */
Object establish_new_object_index_for_remote_procedure_name varargs_1(int, n)
{
    Object remote_procedure_name, icp_port;
    Object send_enlarge_message_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, svref_new_value, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(157,41);
    INIT_ARGS_nonrelocating();
    remote_procedure_name = REQUIRED_ARG_nonrelocating();
    icp_port = REQUIRED_ARG_nonrelocating();
    send_enlarge_message_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    if (Disable_resumability) {
	result = assign_corresponding_icp_object_index(remote_procedure_name,
		Qstandard_icp_object_index_space,send_enlarge_message_p);
	MVS_2(result,corresponding_icp_object_index,
		new_index_limit_plus_one_qm);
	svref_new_value = gensym_cons_1(icp_port,
		gensym_cons_1(corresponding_icp_object_index,
		ISVREF(remote_procedure_name,(SI_Long)2L)));
	SVREF(remote_procedure_name,FIX((SI_Long)2L)) = svref_new_value;
	if (send_enlarge_message_p)
	    return VALUES_1(corresponding_icp_object_index);
	else
	    return VALUES_2(corresponding_icp_object_index,
		    new_index_limit_plus_one_qm);
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qestablish_new_object_index_for_remote_procedure_name,
		    top))
		return icp_error_internal(Qerror,string_constant,
			Qestablish_new_object_index_for_remote_procedure_name,
			top,Nil);
	}
	remote_procedure_name = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : remote_procedure_name;
	icp_port = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : icp_port;
	send_enlarge_message_p = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : send_enlarge_message_p;
	result = assign_corresponding_icp_object_index(remote_procedure_name,
		Qstandard_icp_object_index_space,send_enlarge_message_p);
	MVS_2(result,corresponding_icp_object_index,
		new_index_limit_plus_one_qm);
	svref_new_value = gensym_cons_1(icp_port,
		gensym_cons_1(corresponding_icp_object_index,
		ISVREF(remote_procedure_name,(SI_Long)2L)));
	SVREF(remote_procedure_name,FIX((SI_Long)2L)) = svref_new_value;
	if (send_enlarge_message_p)
	    return VALUES_1(corresponding_icp_object_index);
	else
	    return VALUES_2(corresponding_icp_object_index,
		    new_index_limit_plus_one_qm);
    }
}

static Object Qmake_corresponding_icp_remote_procedure_name;  /* make-corresponding-icp-remote-procedure-name */

/* MAKE-CORRESPONDING-ICP-REMOTE-PROCEDURE-NAME */
Object make_corresponding_icp_remote_procedure_name(remote_procedure_name)
    Object remote_procedure_name;
{
    Object writing_resumable_icp_messages_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, svref_new_value, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, v1, v2, v3;
    Declare_special(1);
    Object result;

    x_note_fn_call(157,42);
    if (Disable_resumability) {
	write_icp_maybe_suspend();
	writing_resumable_icp_messages_p = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Writing_resumable_icp_messages_p,Qwriting_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		0);
	  result = assign_corresponding_icp_object_index(remote_procedure_name,
		  Qstandard_icp_object_index_space,T);
	  MVS_2(result,corresponding_icp_object_index,
		  new_index_limit_plus_one_qm);
	  svref_new_value = gensym_cons_1(Current_icp_port,
		  gensym_cons_1(corresponding_icp_object_index,
		  ISVREF(remote_procedure_name,(SI_Long)2L)));
	  SVREF(remote_procedure_name,FIX((SI_Long)2L)) = svref_new_value;
	  if (T);
	  else {
	      temp = corresponding_icp_object_index;
	      corresponding_icp_object_index = temp;
	  }
	  if ( !TRUEP(Inhibit_corresponding_icp_object_making))
	      send_icp_define_remote_procedure_name(corresponding_icp_object_index,
		      ISVREF(remote_procedure_name,(SI_Long)1L));
	  result = VALUES_1(corresponding_icp_object_index);
	POP_SPECIAL();
	return result;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qmake_corresponding_icp_remote_procedure_name,top))
		return icp_error_internal(Qerror,string_constant,
			Qmake_corresponding_icp_remote_procedure_name,top,Nil);
	}
	remote_procedure_name = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : remote_procedure_name;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    temp = resumable_icp_pop();
	    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) 
		    && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		switch (INTEGER_TO_CHAR(temp)) {
		  case 1:
		    goto l1;
		    break;
		  case 2:
		    goto l2;
		    break;
		  default:
		    break;
		}
	}
      l1:
	if (EQ(icp_suspend_1,write_icp_maybe_suspend())) {
	    resumable_icp_push(FIX((SI_Long)1L));
	    result = VALUES_1(Icp_suspend);
	    goto end_block;
	}
      l2:
	writing_resumable_icp_messages_p = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Writing_resumable_icp_messages_p,Qwriting_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		0);
	  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()))
	      corresponding_icp_object_index = resumable_icp_pop();
	  else {
	      result = assign_corresponding_icp_object_index(remote_procedure_name,
		      Qstandard_icp_object_index_space,T);
	      MVS_2(result,corresponding_icp_object_index,
		      new_index_limit_plus_one_qm);
	      svref_new_value = gensym_cons_1(Current_icp_port,
		      gensym_cons_1(corresponding_icp_object_index,
		      ISVREF(remote_procedure_name,(SI_Long)2L)));
	      SVREF(remote_procedure_name,FIX((SI_Long)2L)) = svref_new_value;
	      if (T);
	      else {
		  temp = corresponding_icp_object_index;
		  corresponding_icp_object_index = temp;
	      }
	  }
	  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) ||  
		  !TRUEP(Inhibit_corresponding_icp_object_making)) {
	      if (EQ(icp_suspend_1,
		      send_icp_define_remote_procedure_name(corresponding_icp_object_index,
		      ISVREF(remote_procedure_name,(SI_Long)1L)))) {
		  resumable_icp_push(corresponding_icp_object_index);
		  resumable_icp_push(Writing_resumable_icp_messages_p);
		  resumable_icp_push(FIX((SI_Long)2L));
		  result = VALUES_1(Icp_suspend);
		  POP_SPECIAL();
		  goto end_block;
	      }
	  }
	  result = VALUES_1(corresponding_icp_object_index);
	POP_SPECIAL();
	goto end_block;
      end_block:
	MVS_3(result,v1,v2,v3);
	if (EQ(icp_suspend_1,v1)) {
	    resumable_icp_push(remote_procedure_name);
	    resumable_icp_push(Qmake_corresponding_icp_remote_procedure_name);
	    return VALUES_1(Icp_suspend);
	}
	return VALUES_3(v1,v2,v3);
    }
}

/* GET-ICP-OBJECT-INDEX-FOR-REMOTE-PROCEDURE-NAME */
Object get_icp_object_index_for_remote_procedure_name(remote_procedure_name,
	    icp_port)
    Object remote_procedure_name, icp_port;
{
    x_note_fn_call(157,43);
    return getfq_function_no_default(ISVREF(remote_procedure_name,
	    (SI_Long)2L),icp_port);
}

/* SET-ICP-OBJECT-INDEX-FOR-REMOTE-PROCEDURE-NAME */
Object set_icp_object_index_for_remote_procedure_name(remote_procedure_name,
	    corresponding_icp_object_index,icp_port)
    Object remote_procedure_name, corresponding_icp_object_index, icp_port;
{
    Object svref_new_value;

    x_note_fn_call(157,44);
    svref_new_value = gensym_cons_1(icp_port,
	    gensym_cons_1(corresponding_icp_object_index,
	    ISVREF(remote_procedure_name,(SI_Long)2L)));
    return VALUES_1(SVREF(remote_procedure_name,FIX((SI_Long)2L)) = 
	    svref_new_value);
}

/* RECLAIM-ICP-OBJECT-MAP-FOR-REMOTE-PROCEDURE-NAME */
Object reclaim_icp_object_map_for_remote_procedure_name(remote_procedure_name)
    Object remote_procedure_name;
{
    Object icp_object_map;

    x_note_fn_call(157,45);
    icp_object_map = ISVREF(remote_procedure_name,(SI_Long)2L);
    if (icp_object_map)
	return reclaim_icp_object_map(remote_procedure_name,icp_object_map,
		Qstandard_icp_object_index_space);
    else
	return VALUES_1(Nil);
}

static Object Qset_access_form_for_remote_procedure_name;  /* set-access-form-for-remote-procedure-name */

/* RECLAIM-ICP-PORT-ENTRY-FOR-REMOTE-PROCEDURE-NAME */
Object reclaim_icp_port_entry_for_remote_procedure_name(remote_procedure_name,
	    icp_port)
    Object remote_procedure_name, icp_port;
{
    x_note_fn_call(157,46);
    return reclaim_icp_port_entry(icp_port,remote_procedure_name,
	    ISVREF(remote_procedure_name,(SI_Long)2L),
	    Qset_access_form_for_remote_procedure_name);
}

/* SET-ACCESS-FORM-FOR-REMOTE-PROCEDURE-NAME */
Object set_access_form_for_remote_procedure_name(remote_procedure_name,
	    new_value)
    Object remote_procedure_name, new_value;
{
    x_note_fn_call(157,47);
    return VALUES_1(SVREF(remote_procedure_name,FIX((SI_Long)2L)) = new_value);
}

static Object Qsend_icp_define_remote_procedure_name;  /* send-icp-define-remote-procedure-name */

static Object Qcorresponding_icp_object_map_for_symbol;  /* corresponding-icp-object-map-for-symbol */

static Object Qdefine_remote_procedure_name;  /* define-remote-procedure-name */

static Object string_constant_1;   /* "[message]" */

static Object Qmessage;            /* message */

static Object Qcorresponding_icp_object_index;  /* corresponding-icp-object-index */

static Object string_constant_2;   /* "[value arg]" */

static Object Qargument;           /* argument */

static Object Qremote_procedure_name_symbol;  /* remote-procedure-name-symbol */

static Object string_constant_3;   /* "[object arg]" */

/* SEND-ICP-DEFINE-REMOTE-PROCEDURE-NAME */
Object send_icp_define_remote_procedure_name(corresponding_icp_object_index,
	    remote_procedure_name_symbol)
    Object corresponding_icp_object_index, remote_procedure_name_symbol;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, resumable_icp_state_1;
    Object icp_suspend_1, top, value, value_1;
    Declare_special(3);
    Object result;

    x_note_fn_call(157,48);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qsend_icp_define_remote_procedure_name;
	  }
	  temp_1 = 
		  getfq_function_no_default(INLINE_SYMBOL_PLIST(remote_procedure_name_symbol),
		  Qcorresponding_icp_object_map_for_symbol);
	  temp_1 = getfq_function_no_default(temp_1,Current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = 
		      make_corresponding_icp_symbol(remote_procedure_name_symbol);
	  remote_procedure_name_symbol = temp_1;
	  start_writing_icp_message(FIX((SI_Long)221L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qdefine_remote_procedure_name,string_constant_1,
			  Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_unsigned_integer(corresponding_icp_object_index);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qcorresponding_icp_object_index,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_unsigned_integer(corresponding_icp_object_index);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qremote_procedure_name_symbol,
				string_constant_3,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_corresponding_object_index(remote_procedure_name_symbol);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qremote_procedure_name_symbol,
				  string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_corresponding_object_index(remote_procedure_name_symbol);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qdefine_remote_procedure_name,
			    string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else {
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_unsigned_integer(corresponding_icp_object_index);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_unsigned_integer(corresponding_icp_object_index);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qremote_procedure_name_symbol,
			      string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_corresponding_object_index(remote_procedure_name_symbol);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qremote_procedure_name_symbol,
				string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_corresponding_object_index(remote_procedure_name_symbol);
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_define_remote_procedure_name,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qsend_icp_define_remote_procedure_name,top,Nil);
		goto end_send_icp_define_remote_procedure_name;
	    }
	}
	corresponding_icp_object_index = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : corresponding_icp_object_index;
	remote_procedure_name_symbol = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : remote_procedure_name_symbol;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qsend_icp_define_remote_procedure_name;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    case 3:
		      goto l3;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()))
	      value = resumable_icp_pop();
	  else {
	      temp_1 = 
		      getfq_function_no_default(INLINE_SYMBOL_PLIST(remote_procedure_name_symbol),
		      Qcorresponding_icp_object_map_for_symbol);
	      value = getfq_function_no_default(temp_1,Current_icp_port);
	  }
	  if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) && value)
	      remote_procedure_name_symbol = value;
	  else {
	      value_1 = 
		      make_corresponding_icp_symbol(remote_procedure_name_symbol);
	      if (EQ(icp_suspend_1,value_1)) {
		  resumable_icp_push(value);
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      remote_procedure_name_symbol = value_1;
	  }
	l2:
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)221L)))) {
	      resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l3:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qdefine_remote_procedure_name,string_constant_1,
			  Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    temp_1 = resumable_icp_pop();
		    if (! !(FIXNUMP(temp_1) && 
			    FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			    FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			switch (INTEGER_TO_CHAR(temp_1)) {
			  case 1:
			    goto l1_1;
			    break;
			  case 2:
			    goto l2_1;
			    break;
			  default:
			    break;
			}
		}
	      l1_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_unsigned_integer(corresponding_icp_object_index))) 
				  {
			  resumable_icp_push(FIX((SI_Long)1L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qcorresponding_icp_object_index,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_unsigned_integer(corresponding_icp_object_index))) 
			    {
		    resumable_icp_push(FIX((SI_Long)1L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l2_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qremote_procedure_name_symbol,
				string_constant_3,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_corresponding_object_index(remote_procedure_name_symbol))) 
				  {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qremote_procedure_name_symbol,
				  string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		      temp_1 = result_of_write;
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_corresponding_object_index(remote_procedure_name_symbol))) 
			    {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
		else
		    temp_1 = Nil;
		goto end_block_1;
	      end_block_1:
		if (EQ(icp_suspend_1,temp_1)) {
		    resumable_icp_push(FIX((SI_Long)3L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qdefine_remote_procedure_name,
			    string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else {
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  temp_1 = resumable_icp_pop();
		  if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
			  temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		      switch (INTEGER_TO_CHAR(temp_1)) {
			case 1:
			  goto l1_2;
			  break;
			case 2:
			  goto l2_2;
			  break;
			default:
			  break;
		      }
	      }
	    l1_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_unsigned_integer(corresponding_icp_object_index))) 
				{
			resumable_icp_push(FIX((SI_Long)1L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_unsigned_integer(corresponding_icp_object_index))) 
			  {
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l2_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qremote_procedure_name_symbol,
			      string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_corresponding_object_index(remote_procedure_name_symbol))) 
				{
			resumable_icp_push(FIX((SI_Long)2L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qremote_procedure_name_symbol,
				string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_corresponding_object_index(remote_procedure_name_symbol))) 
			  {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	      else
		  temp_1 = Nil;
	      goto end_block_2;
	    end_block_2:
	      if (EQ(icp_suspend_1,temp_1)) {
		  resumable_icp_push(FIX((SI_Long)3L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      else
		  temp_1 = Nil;
	  }
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(remote_procedure_name_symbol);
	      resumable_icp_push(corresponding_icp_object_index);
	      resumable_icp_push(Qsend_icp_define_remote_procedure_name);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_define_remote_procedure_name;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_define_remote_procedure_name:
    return result;
}

/* HANDLE-ICP-DEFINE-REMOTE-PROCEDURE-NAME--BODY */
Object handle_icp_define_remote_procedure_name__body(corresponding_icp_object_index,
	    remote_procedure_name_symbol)
    Object corresponding_icp_object_index, remote_procedure_name_symbol;
{
    Object new_remote_procedure_name;

    x_note_fn_call(157,49);
    new_remote_procedure_name = 
	    make_remote_procedure_name_1(remote_procedure_name_symbol);
    store_corresponding_icp_object(corresponding_icp_object_index,
	    new_remote_procedure_name);
    return VALUES_1(Nil);
}

static Object Qhandle_icp_define_remote_procedure_name;  /* handle-icp-define-remote-procedure-name */

static Object Qresumable_icp_list_end;  /* resumable-icp-list-end */

/* HANDLE-ICP-DEFINE-REMOTE-PROCEDURE-NAME */
Object handle_icp_define_remote_procedure_name()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read, corresponding_icp_object_index;
    Object index_1, index_space, remote_procedure_name_symbol;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(157,50);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qdefine_remote_procedure_name,string_constant_1,
			Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_unsigned_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    corresponding_icp_object_index = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  corresponding_icp_object_index = read_icp_unsigned_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qremote_procedure_name_symbol,
			      string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    index_1 = read_icp_corresponding_object_index();
		    index_space = Current_temporary_icp_object_index_space;
		    if (index_space);
		    else
			index_space = Current_standard_icp_object_index_space;
		    if (FIXNUMP(index_1)) {
			if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			    enlarge_index_space(index_space,index_1);
			result_of_read = ISVREF(ISVREF(ISVREF(index_space,
				(SI_Long)2L),IFIX(index_1) >>  -  - 
				(SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		    }
		    else
			result_of_read = Nil;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qremote_procedure_name_symbol,
				string_constant_3,Qargument,T,
				result_of_read,Nil,Nil);
		    remote_procedure_name_symbol = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  index_1 = read_icp_corresponding_object_index();
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      remote_procedure_name_symbol = 
			      ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      remote_procedure_name_symbol = Nil;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_define_remote_procedure_name__body(corresponding_icp_object_index,
			remote_procedure_name_symbol);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qdefine_remote_procedure_name,string_constant_1,
			  Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qcorresponding_icp_object_index,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_unsigned_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  corresponding_icp_object_index = result_of_read;
		POP_SPECIAL();
	    }
	    else
		corresponding_icp_object_index = read_icp_unsigned_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qremote_procedure_name_symbol,
			    string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  index_1 = read_icp_corresponding_object_index();
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      result_of_read = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      result_of_read = Nil;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qremote_procedure_name_symbol,
			      string_constant_3,Qargument,T,result_of_read,
			      Nil,Nil);
		  remote_procedure_name_symbol = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		index_1 = read_icp_corresponding_object_index();
		index_space = Current_temporary_icp_object_index_space;
		if (index_space);
		else
		    index_space = Current_standard_icp_object_index_space;
		if (FIXNUMP(index_1)) {
		    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			enlarge_index_space(index_space,index_1);
		    remote_procedure_name_symbol = 
			    ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			    IFIX(index_1) >>  -  - (SI_Long)10L),
			    IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    remote_procedure_name_symbol = Nil;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_define_remote_procedure_name__body(corresponding_icp_object_index,
		      remote_procedure_name_symbol);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_define_remote_procedure_name,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qhandle_icp_define_remote_procedure_name,top,Nil);
		goto end_handle_icp_define_remote_procedure_name;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qdefine_remote_procedure_name,string_constant_1,
			Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  corresponding_icp_object_index = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_unsigned_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_define_remote_procedure_name);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_define_remote_procedure_name;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    corresponding_icp_object_index = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_define_remote_procedure_name);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_remote_procedure_name;
		  }
		  corresponding_icp_object_index = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  remote_procedure_name_symbol = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qremote_procedure_name_symbol,
			      string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()))
			index_1 = resumable_icp_pop();
		    else {
			value = read_icp_corresponding_object_index();
			if (EQ(icp_suspend_1,value)) {
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(corresponding_icp_object_index);
			    resumable_icp_push(Qhandle_icp_define_remote_procedure_name);
			    result = VALUES_1(Icp_suspend);
			    POP_SPECIAL();
			    POP_SPECIAL();
			    goto end_handle_icp_define_remote_procedure_name;
			}
			index_1 = value;
		    }
		    index_space = Current_temporary_icp_object_index_space;
		    if (index_space);
		    else
			index_space = Current_standard_icp_object_index_space;
		    if (FIXNUMP(index_1)) {
			if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			    enlarge_index_space(index_space,index_1);
			result_of_read = ISVREF(ISVREF(ISVREF(index_space,
				(SI_Long)2L),IFIX(index_1) >>  -  - 
				(SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		    }
		    else
			result_of_read = Nil;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qremote_procedure_name_symbol,
				string_constant_3,Qargument,T,
				result_of_read,Nil,Nil);
		    remote_procedure_name_symbol = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			   TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()))
		      index_1 = resumable_icp_pop();
		  else {
		      value = read_icp_corresponding_object_index();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(corresponding_icp_object_index);
			  resumable_icp_push(Qhandle_icp_define_remote_procedure_name);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_define_remote_procedure_name;
		      }
		      index_1 = value;
		  }
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      remote_procedure_name_symbol = 
			      ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      remote_procedure_name_symbol = Nil;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_define_remote_procedure_name__body(corresponding_icp_object_index,
			remote_procedure_name_symbol);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qdefine_remote_procedure_name,string_constant_1,
			  Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		corresponding_icp_object_index = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qcorresponding_icp_object_index,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_define_remote_procedure_name);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_remote_procedure_name;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  corresponding_icp_object_index = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qhandle_icp_define_remote_procedure_name);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_define_remote_procedure_name;
		}
		corresponding_icp_object_index = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		remote_procedure_name_symbol = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qremote_procedure_name_symbol,
			    string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			   TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()))
		      index_1 = resumable_icp_pop();
		  else {
		      value = read_icp_corresponding_object_index();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(corresponding_icp_object_index);
			  resumable_icp_push(Qhandle_icp_define_remote_procedure_name);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_define_remote_procedure_name;
		      }
		      index_1 = value;
		  }
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      result_of_read = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      result_of_read = Nil;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qremote_procedure_name_symbol,
			      string_constant_3,Qargument,T,result_of_read,
			      Nil,Nil);
		  remote_procedure_name_symbol = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()))
		    index_1 = resumable_icp_pop();
		else {
		    value = read_icp_corresponding_object_index();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(corresponding_icp_object_index);
			resumable_icp_push(Qhandle_icp_define_remote_procedure_name);
			result = VALUES_1(Icp_suspend);
			goto end_handle_icp_define_remote_procedure_name;
		    }
		    index_1 = value;
		}
		index_space = Current_temporary_icp_object_index_space;
		if (index_space);
		else
		    index_space = Current_standard_icp_object_index_space;
		if (FIXNUMP(index_1)) {
		    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			enlarge_index_space(index_space,index_1);
		    remote_procedure_name_symbol = 
			    ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			    IFIX(index_1) >>  -  - (SI_Long)10L),
			    IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    remote_procedure_name_symbol = Nil;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_define_remote_procedure_name__body(corresponding_icp_object_index,
		      remote_procedure_name_symbol);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_define_remote_procedure_name:
    return result;
}

Object The_type_description_of_remote_procedure_identifier = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_remote_procedure_identifiers, Qchain_of_available_remote_procedure_identifiers);

DEFINE_VARIABLE_WITH_SYMBOL(Remote_procedure_identifier_count, Qremote_procedure_identifier_count);

Object Chain_of_available_remote_procedure_identifiers_vector = UNBOUND;

/* REMOTE-PROCEDURE-IDENTIFIER-STRUCTURE-MEMORY-USAGE */
Object remote_procedure_identifier_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(157,51);
    temp = Remote_procedure_identifier_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)11L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-REMOTE-PROCEDURE-IDENTIFIER-COUNT */
Object outstanding_remote_procedure_identifier_count()
{
    Object def_structure_remote_procedure_identifier_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(157,52);
    gensymed_symbol = IFIX(Remote_procedure_identifier_count);
    def_structure_remote_procedure_identifier_variable = 
	    Chain_of_available_remote_procedure_identifiers;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_remote_procedure_identifier_variable))
	goto end_loop;
    def_structure_remote_procedure_identifier_variable = 
	    ISVREF(def_structure_remote_procedure_identifier_variable,
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

/* RECLAIM-REMOTE-PROCEDURE-IDENTIFIER-1 */
Object reclaim_remote_procedure_identifier_1(remote_procedure_identifier)
    Object remote_procedure_identifier;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(157,53);
    inline_note_reclaim_cons(remote_procedure_identifier,Nil);
    structure_being_reclaimed = remote_procedure_identifier;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_icp_list_1(ISVREF(remote_procedure_identifier,(SI_Long)5L));
      SVREF(remote_procedure_identifier,FIX((SI_Long)5L)) = Nil;
      reclaim_remote_procedure_item_passing_info(ISVREF(remote_procedure_identifier,
	      (SI_Long)8L));
      SVREF(remote_procedure_identifier,FIX((SI_Long)8L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_remote_procedure_identifiers_vector,
	    IFIX(Current_thread_index));
    SVREF(remote_procedure_identifier,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_remote_procedure_identifiers_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = remote_procedure_identifier;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-REMOTE-PROCEDURE-IDENTIFIER */
Object reclaim_structure_for_remote_procedure_identifier(remote_procedure_identifier)
    Object remote_procedure_identifier;
{
    x_note_fn_call(157,54);
    return reclaim_remote_procedure_identifier_1(remote_procedure_identifier);
}

static Object Qg2_defstruct_structure_name_remote_procedure_identifier_g2_struct;  /* g2-defstruct-structure-name::remote-procedure-identifier-g2-struct */

/* MAKE-PERMANENT-REMOTE-PROCEDURE-IDENTIFIER-STRUCTURE-INTERNAL */
Object make_permanent_remote_procedure_identifier_structure_internal()
{
    Object def_structure_remote_procedure_identifier_variable;
    Object defstruct_g2_remote_procedure_identifier_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(157,55);
    def_structure_remote_procedure_identifier_variable = Nil;
    atomic_incff_symval(Qremote_procedure_identifier_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_remote_procedure_identifier_variable = Nil;
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
	defstruct_g2_remote_procedure_identifier_variable = the_array;
	SVREF(defstruct_g2_remote_procedure_identifier_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_remote_procedure_identifier_g2_struct;
	def_structure_remote_procedure_identifier_variable = 
		defstruct_g2_remote_procedure_identifier_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_remote_procedure_identifier_variable);
}

static Object Qoutstanding;        /* outstanding */

/* MAKE-REMOTE-PROCEDURE-IDENTIFIER-1 */
Object make_remote_procedure_identifier_1(remote_procedure_identifier_tag,
	    remote_procedure_item_passing_info)
    Object remote_procedure_identifier_tag, remote_procedure_item_passing_info;
{
    Object def_structure_remote_procedure_identifier_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(157,56);
    def_structure_remote_procedure_identifier_variable = 
	    ISVREF(Chain_of_available_remote_procedure_identifiers_vector,
	    IFIX(Current_thread_index));
    if (def_structure_remote_procedure_identifier_variable) {
	svref_arg_1 = Chain_of_available_remote_procedure_identifiers_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_remote_procedure_identifier_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_remote_procedure_identifier_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_remote_procedure_identifier_g2_struct;
    }
    else
	def_structure_remote_procedure_identifier_variable = 
		make_permanent_remote_procedure_identifier_structure_internal();
    inline_note_allocate_cons(def_structure_remote_procedure_identifier_variable,
	    Nil);
    SVREF(def_structure_remote_procedure_identifier_variable,
	    FIX((SI_Long)1L)) = remote_procedure_identifier_tag;
    SVREF(def_structure_remote_procedure_identifier_variable,
	    FIX((SI_Long)8L)) = remote_procedure_item_passing_info;
    SVREF(def_structure_remote_procedure_identifier_variable,
	    FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_remote_procedure_identifier_variable,
	    FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_remote_procedure_identifier_variable,
	    FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_remote_procedure_identifier_variable,
	    FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_remote_procedure_identifier_variable,
	    FIX((SI_Long)6L)) = Qoutstanding;
    SVREF(def_structure_remote_procedure_identifier_variable,
	    FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_remote_procedure_identifier_variable,
	    FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_remote_procedure_identifier_variable,
	    FIX((SI_Long)10L)) = Nil;
    return VALUES_1(def_structure_remote_procedure_identifier_variable);
}

/* MAKE-OUTGOING-REMOTE-PROCEDURE-IDENTIFIER */
Object make_outgoing_remote_procedure_identifier(tag,info)
    Object tag, info;
{
    Object temp;

    x_note_fn_call(157,57);
    temp = make_remote_procedure_identifier_1(tag,info);
    return VALUES_1(temp);
}

/* RECLAIM-OUTGOING-REMOTE-PROCEDURE-IDENTIFIER */
Object reclaim_outgoing_remote_procedure_identifier(remote_procedure_identifier)
    Object remote_procedure_identifier;
{
    Object temp;

    x_note_fn_call(157,58);
    SVREF(remote_procedure_identifier,FIX((SI_Long)9L)) = Nil;
    temp = reclaim_remote_procedure_identifier_1(remote_procedure_identifier);
    return VALUES_1(temp);
}

/* MAKE-INCOMING-REMOTE-PROCEDURE-IDENTIFIER */
Object make_incoming_remote_procedure_identifier(tag,info)
    Object tag, info;
{
    Object temp;

    x_note_fn_call(157,59);
    temp = make_remote_procedure_identifier_1(tag,info);
    return VALUES_1(temp);
}

/* RECLAIM-INCOMING-REMOTE-PROCEDURE-IDENTIFIER */
Object reclaim_incoming_remote_procedure_identifier(remote_procedure_identifier)
    Object remote_procedure_identifier;
{
    Object temp;

    x_note_fn_call(157,60);
    SVREF(remote_procedure_identifier,FIX((SI_Long)9L)) = Nil;
    temp = reclaim_remote_procedure_identifier_1(remote_procedure_identifier);
    return VALUES_1(temp);
}

/* MAKE-REMOTE-PROCEDURE-ITEM-INFO */
Object make_remote_procedure_item_info(included_attributes,
	    excluded_attributes,included_system_attributes,
	    include_all_system_attributes,
	    include_all_system_attributes_except,kind)
    Object included_attributes, excluded_attributes;
    Object included_system_attributes, include_all_system_attributes;
    Object include_all_system_attributes_except, kind;
{
    Object gensymed_symbol, gensymed_symbol_1, list_1, temp;

    x_note_fn_call(157,61);
    gensymed_symbol = make_gensym_list_1(FIX((SI_Long)6L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = included_attributes;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = excluded_attributes;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = included_system_attributes;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = include_all_system_attributes;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = include_all_system_attributes_except;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = kind;
    list_1 = gensymed_symbol;
    temp = intern_list(list_1);
    reclaim_gensym_list_1(list_1);
    return VALUES_1(temp);
}

/* MAKE-REMOTE-PROCEDURE-ITEM-INFO-OLD */
Object make_remote_procedure_item_info_old(included_attributes,
	    excluded_attributes,included_system_attributes,
	    include_all_system_attributes,kind)
    Object included_attributes, excluded_attributes;
    Object included_system_attributes, include_all_system_attributes, kind;
{
    Object gensymed_symbol, gensymed_symbol_1, list_1, temp;

    x_note_fn_call(157,62);
    gensymed_symbol = make_gensym_list_1(FIX((SI_Long)5L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = included_attributes;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = excluded_attributes;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = included_system_attributes;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = include_all_system_attributes;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = kind;
    list_1 = gensymed_symbol;
    temp = intern_list(list_1);
    reclaim_gensym_list_1(list_1);
    return VALUES_1(temp);
}

/* REMOTE-PROCEDURE-ITEM-INFO-INCLUDED-ATTRIBUTES */
Object remote_procedure_item_info_included_attributes(x)
    Object x;
{
    Object temp;

    x_note_fn_call(157,63);
    if (x) {
	temp = ISVREF(x,(SI_Long)1L);
	temp = FIRST(temp);
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* REMOTE-PROCEDURE-ITEM-INFO-EXCLUDED-ATTRIBUTES */
Object remote_procedure_item_info_excluded_attributes(x)
    Object x;
{
    Object temp;

    x_note_fn_call(157,64);
    if (x) {
	temp = ISVREF(x,(SI_Long)1L);
	temp = SECOND(temp);
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* REMOTE-PROCEDURE-ITEM-INFO-INCLUDED-SYSTEM-ATTRIBUTES */
Object remote_procedure_item_info_included_system_attributes(x)
    Object x;
{
    Object temp;

    x_note_fn_call(157,65);
    if (x) {
	temp = ISVREF(x,(SI_Long)1L);
	temp = THIRD(temp);
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* REMOTE-PROCEDURE-ITEM-INFO-INCLUDE-ALL-SYSTEM-ATTRIBUTES */
Object remote_procedure_item_info_include_all_system_attributes(x)
    Object x;
{
    Object temp;

    x_note_fn_call(157,66);
    if (x) {
	temp = ISVREF(x,(SI_Long)1L);
	temp = FOURTH(temp);
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* REMOTE-PROCEDURE-ITEM-INFO-INCLUDE-ALL-SYSTEM-ATTRIBUTES-EXCEPT */
Object remote_procedure_item_info_include_all_system_attributes_except(x)
    Object x;
{
    Object temp;

    x_note_fn_call(157,67);
    temp = x ? FIFTH(ISVREF(x,(SI_Long)1L)) : Nil;
    return VALUES_1(temp);
}

/* REMOTE-PROCEDURE-ITEM-INFO-KIND */
Object remote_procedure_item_info_kind(x)
    Object x;
{
    Object temp;

    x_note_fn_call(157,68);
    temp = x ? SIXTH(ISVREF(x,(SI_Long)1L)) : Nil;
    return VALUES_1(temp);
}

/* REMOTE-PROCEDURE-ITEM-INFO-KIND-FUNCTION */
Object remote_procedure_item_info_kind_function(x)
    Object x;
{
    Object temp;

    x_note_fn_call(157,69);
    temp = remote_procedure_item_info_kind(x);
    return VALUES_1(temp);
}

Object The_type_description_of_remote_procedure_item_passing_info = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_remote_procedure_item_passing_infos, Qchain_of_available_remote_procedure_item_passing_infos);

DEFINE_VARIABLE_WITH_SYMBOL(Remote_procedure_item_passing_info_count, Qremote_procedure_item_passing_info_count);

Object Chain_of_available_remote_procedure_item_passing_infos_vector = UNBOUND;

/* REMOTE-PROCEDURE-ITEM-PASSING-INFO-STRUCTURE-MEMORY-USAGE */
Object remote_procedure_item_passing_info_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(157,70);
    temp = Remote_procedure_item_passing_info_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)2L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-REMOTE-PROCEDURE-ITEM-PASSING-INFO-COUNT */
Object outstanding_remote_procedure_item_passing_info_count()
{
    Object def_structure_remote_procedure_item_passing_info_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(157,71);
    gensymed_symbol = IFIX(Remote_procedure_item_passing_info_count);
    def_structure_remote_procedure_item_passing_info_variable = 
	    Chain_of_available_remote_procedure_item_passing_infos;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_remote_procedure_item_passing_info_variable))
	goto end_loop;
    def_structure_remote_procedure_item_passing_info_variable = 
	    ISVREF(def_structure_remote_procedure_item_passing_info_variable,
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

/* RECLAIM-REMOTE-PROCEDURE-ITEM-PASSING-INFO-1-1 */
Object reclaim_remote_procedure_item_passing_info_1_1(remote_procedure_item_passing_info)
    Object remote_procedure_item_passing_info;
{
    Object temp, svref_arg_2;

    x_note_fn_call(157,72);
    inline_note_reclaim_cons(remote_procedure_item_passing_info,Nil);
    temp = 
	    ISVREF(Chain_of_available_remote_procedure_item_passing_infos_vector,
	    IFIX(Current_thread_index));
    SVREF(remote_procedure_item_passing_info,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_remote_procedure_item_passing_infos_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = remote_procedure_item_passing_info;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-REMOTE-PROCEDURE-ITEM-PASSING-INFO */
Object reclaim_structure_for_remote_procedure_item_passing_info(remote_procedure_item_passing_info)
    Object remote_procedure_item_passing_info;
{
    x_note_fn_call(157,73);
    return reclaim_remote_procedure_item_passing_info_1_1(remote_procedure_item_passing_info);
}

static Object Qg2_defstruct_structure_name_remote_procedure_item_passing_info_g2_struct;  /* g2-defstruct-structure-name::remote-procedure-item-passing-info-g2-struct */

/* MAKE-PERMANENT-REMOTE-PROCEDURE-ITEM-PASSING-INFO-STRUCTURE-INTERNAL */
Object make_permanent_remote_procedure_item_passing_info_structure_internal()
{
    Object def_structure_remote_procedure_item_passing_info_variable;
    Object defstruct_g2_remote_procedure_item_passing_info_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(157,74);
    def_structure_remote_procedure_item_passing_info_variable = Nil;
    atomic_incff_symval(Qremote_procedure_item_passing_info_count,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_remote_procedure_item_passing_info_variable = Nil;
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
	defstruct_g2_remote_procedure_item_passing_info_variable = the_array;
	SVREF(defstruct_g2_remote_procedure_item_passing_info_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_remote_procedure_item_passing_info_g2_struct;
	def_structure_remote_procedure_item_passing_info_variable = 
		defstruct_g2_remote_procedure_item_passing_info_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_remote_procedure_item_passing_info_variable);
}

/* MAKE-REMOTE-PROCEDURE-ITEM-PASSING-INFO-1-1 */
Object make_remote_procedure_item_passing_info_1_1(remote_procedure_item_passing_info_interned_varargsp_plus_item_info_list)
    Object remote_procedure_item_passing_info_interned_varargsp_plus_item_info_list;
{
    Object def_structure_remote_procedure_item_passing_info_variable;
    Object svref_arg_1, svref_arg_2, svref_new_value;

    x_note_fn_call(157,75);
    def_structure_remote_procedure_item_passing_info_variable = 
	    ISVREF(Chain_of_available_remote_procedure_item_passing_infos_vector,
	    IFIX(Current_thread_index));
    if (def_structure_remote_procedure_item_passing_info_variable) {
	svref_arg_1 = 
		Chain_of_available_remote_procedure_item_passing_infos_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_remote_procedure_item_passing_info_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_remote_procedure_item_passing_info_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_remote_procedure_item_passing_info_g2_struct;
    }
    else
	def_structure_remote_procedure_item_passing_info_variable = 
		make_permanent_remote_procedure_item_passing_info_structure_internal();
    inline_note_allocate_cons(def_structure_remote_procedure_item_passing_info_variable,
	    Nil);
    SVREF(def_structure_remote_procedure_item_passing_info_variable,
	    FIX((SI_Long)1L)) = 
	    remote_procedure_item_passing_info_interned_varargsp_plus_item_info_list;
    return VALUES_1(def_structure_remote_procedure_item_passing_info_variable);
}

/* RECLAIM-REMOTE-PROCEDURE-ITEM-PASSING-INFO */
Object reclaim_remote_procedure_item_passing_info(remote_procedure_item_passing_info)
    Object remote_procedure_item_passing_info;
{
    x_note_fn_call(157,76);
    if (SIMPLE_VECTOR_P(remote_procedure_item_passing_info) && 
	    EQ(ISVREF(remote_procedure_item_passing_info,(SI_Long)0L),
	    Qg2_defstruct_structure_name_remote_procedure_item_passing_info_g2_struct))
	reclaim_remote_procedure_item_passing_info_1_1(remote_procedure_item_passing_info);
    return VALUES_1(Nil);
}

Object The_type_description_of_interned_remote_procedure_item_passing_info = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_interned_remote_procedure_item_passing_infos, Qchain_of_available_interned_remote_procedure_item_passing_infos);

DEFINE_VARIABLE_WITH_SYMBOL(Interned_remote_procedure_item_passing_info_count, Qinterned_remote_procedure_item_passing_info_count);

Object Chain_of_available_interned_remote_procedure_item_passing_infos_vector = UNBOUND;

/* INTERNED-REMOTE-PROCEDURE-ITEM-PASSING-INFO-STRUCTURE-MEMORY-USAGE */
Object interned_remote_procedure_item_passing_info_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(157,77);
    temp = Interned_remote_procedure_item_passing_info_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)2L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-INTERNED-REMOTE-PROCEDURE-ITEM-PASSING-INFO-COUNT */
Object outstanding_interned_remote_procedure_item_passing_info_count()
{
    Object def_structure_interned_remote_procedure_item_passing_info_variable;
    Object count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(157,78);
    gensymed_symbol = IFIX(Interned_remote_procedure_item_passing_info_count);
    def_structure_interned_remote_procedure_item_passing_info_variable = 
	    Chain_of_available_interned_remote_procedure_item_passing_infos;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( 
	    !TRUEP(def_structure_interned_remote_procedure_item_passing_info_variable))
	goto end_loop;
    def_structure_interned_remote_procedure_item_passing_info_variable = 
	    ISVREF(def_structure_interned_remote_procedure_item_passing_info_variable,
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

/* RECLAIM-INTERNED-REMOTE-PROCEDURE-ITEM-PASSING-INFO-1 */
Object reclaim_interned_remote_procedure_item_passing_info_1(interned_remote_procedure_item_passing_info)
    Object interned_remote_procedure_item_passing_info;
{
    Object temp, svref_arg_2;

    x_note_fn_call(157,79);
    inline_note_reclaim_cons(interned_remote_procedure_item_passing_info,Nil);
    temp = 
	    ISVREF(Chain_of_available_interned_remote_procedure_item_passing_infos_vector,
	    IFIX(Current_thread_index));
    SVREF(interned_remote_procedure_item_passing_info,FIX((SI_Long)0L)) = temp;
    temp = 
	    Chain_of_available_interned_remote_procedure_item_passing_infos_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = interned_remote_procedure_item_passing_info;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-INTERNED-REMOTE-PROCEDURE-ITEM-PASSING-INFO */
Object reclaim_structure_for_interned_remote_procedure_item_passing_info(interned_remote_procedure_item_passing_info)
    Object interned_remote_procedure_item_passing_info;
{
    x_note_fn_call(157,80);
    return reclaim_interned_remote_procedure_item_passing_info_1(interned_remote_procedure_item_passing_info);
}

static Object Qg2_defstruct_structure_name_interned_remote_procedure_item_passing_info_g2_struct;  /* g2-defstruct-structure-name::interned-remote-procedure-item-passing-info-g2-struct */

/* MAKE-PERMANENT-INTERNED-REMOTE-PROCEDURE-ITEM-PASSING-INFO-STRUCTURE-INTERNAL */
Object make_permanent_interned_remote_procedure_item_passing_info_structure_internal()
{
    Object def_structure_interned_remote_procedure_item_passing_info_variable;
    Object defstruct_g2_interned_remote_procedure_item_passing_info_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(157,81);
    def_structure_interned_remote_procedure_item_passing_info_variable = Nil;
    atomic_incff_symval(Qinterned_remote_procedure_item_passing_info_count,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_interned_remote_procedure_item_passing_info_variable 
		= Nil;
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
	defstruct_g2_interned_remote_procedure_item_passing_info_variable 
		= the_array;
	SVREF(defstruct_g2_interned_remote_procedure_item_passing_info_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_interned_remote_procedure_item_passing_info_g2_struct;
	SVREF(defstruct_g2_interned_remote_procedure_item_passing_info_variable,
		FIX((SI_Long)1L)) = Nil;
	def_structure_interned_remote_procedure_item_passing_info_variable 
		= 
		defstruct_g2_interned_remote_procedure_item_passing_info_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_interned_remote_procedure_item_passing_info_variable);
}

/* MAKE-INTERNED-REMOTE-PROCEDURE-ITEM-PASSING-INFO-1-1 */
Object make_interned_remote_procedure_item_passing_info_1_1(remote_procedure_item_passing_info_interned_varargsp_plus_item_info_list)
    Object remote_procedure_item_passing_info_interned_varargsp_plus_item_info_list;
{
    Object def_structure_interned_remote_procedure_item_passing_info_variable;
    Object svref_arg_1, svref_arg_2, svref_new_value;

    x_note_fn_call(157,82);
    def_structure_interned_remote_procedure_item_passing_info_variable = 
	    ISVREF(Chain_of_available_interned_remote_procedure_item_passing_infos_vector,
	    IFIX(Current_thread_index));
    if (def_structure_interned_remote_procedure_item_passing_info_variable) {
	svref_arg_1 = 
		Chain_of_available_interned_remote_procedure_item_passing_infos_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_interned_remote_procedure_item_passing_info_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_interned_remote_procedure_item_passing_info_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_interned_remote_procedure_item_passing_info_g2_struct;
    }
    else
	def_structure_interned_remote_procedure_item_passing_info_variable 
		= 
		make_permanent_interned_remote_procedure_item_passing_info_structure_internal();
    inline_note_allocate_cons(def_structure_interned_remote_procedure_item_passing_info_variable,
	    Nil);
    SVREF(def_structure_interned_remote_procedure_item_passing_info_variable,
	    FIX((SI_Long)1L)) = 
	    remote_procedure_item_passing_info_interned_varargsp_plus_item_info_list;
    return VALUES_1(def_structure_interned_remote_procedure_item_passing_info_variable);
}

/* MAKE-REMOTE-PROCEDURE-ITEM-PASSING-INFO-FROM-SPECS */
Object make_remote_procedure_item_passing_info_from_specs(internedp,
	    included_attributes_spec,excluded_attributes_spec,
	    included_system_attributes_spec,
	    include_all_system_attributes_spec,
	    include_all_system_attributes_except_spec,kind_spec,varargs_p)
    Object internedp, included_attributes_spec, excluded_attributes_spec;
    Object included_system_attributes_spec, include_all_system_attributes_spec;
    Object include_all_system_attributes_except_spec, kind_spec, varargs_p;
{
    Object interned_list, temp;

    x_note_fn_call(157,83);
    interned_list = 
	    make_remote_procedure_item_passing_info_from_specs_1(included_attributes_spec,
	    excluded_attributes_spec,included_system_attributes_spec,
	    include_all_system_attributes_spec,
	    include_all_system_attributes_except_spec,kind_spec,varargs_p);
    temp = internedp ? 
	    make_interned_remote_procedure_item_passing_info_1_1(interned_list) 
	    : make_remote_procedure_item_passing_info_1_1(interned_list);
    return VALUES_1(temp);
}

/* MAKE-REMOTE-PROCEDURE-ITEM-PASSING-INFO-FROM-SPECS-1 */
Object make_remote_procedure_item_passing_info_from_specs_1(included_attributes_spec,
	    excluded_attributes_spec,included_system_attributes_spec,
	    include_all_system_attributes_spec,
	    include_all_system_attributes_except_spec,kind_spec,varargs_p)
    Object included_attributes_spec, excluded_attributes_spec;
    Object included_system_attributes_spec, include_all_system_attributes_spec;
    Object include_all_system_attributes_except_spec, kind_spec, varargs_p;
{
    Object incl_attr_tail, excl_attr_tail, incl_sys_attr_tail;
    Object incl_all_sys_attr_tail, incl_all_sys_attr_except_tail, kind_tail;
    Object incl_attr, excl_attr, incl_sys_attr, incl_all_sys_attr;
    Object incl_all_sys_except_attr, kind, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, list_of_interned_item_infos, list_to_intern, temp;

    x_note_fn_call(157,84);
    incl_attr_tail = included_attributes_spec;
    excl_attr_tail = excluded_attributes_spec;
    incl_sys_attr_tail = included_system_attributes_spec;
    incl_all_sys_attr_tail = include_all_system_attributes_spec;
    incl_all_sys_attr_except_tail = include_all_system_attributes_except_spec;
    kind_tail = kind_spec;
    incl_attr = Nil;
    excl_attr = Nil;
    incl_sys_attr = Nil;
    incl_all_sys_attr = Nil;
    incl_all_sys_except_attr = Nil;
    kind = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !(incl_attr_tail || excl_attr_tail || incl_sys_attr_tail || 
	    incl_all_sys_attr_tail || incl_all_sys_attr_except_tail || 
	    kind_tail))
	goto end_loop;
    incl_attr = CAR(incl_attr_tail);
    excl_attr = CAR(excl_attr_tail);
    incl_sys_attr = CAR(incl_sys_attr_tail);
    incl_all_sys_attr = CAR(incl_all_sys_attr_tail);
    incl_all_sys_except_attr = CAR(incl_all_sys_attr_except_tail);
    kind = CAR(kind_tail);
    ab_loopvar__2 = icp_cons_1(make_remote_procedure_item_info(incl_attr,
	    excl_attr,incl_sys_attr,incl_all_sys_attr,
	    incl_all_sys_except_attr,kind),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    incl_attr_tail = CDR(incl_attr_tail);
    excl_attr_tail = CDR(excl_attr_tail);
    incl_sys_attr_tail = CDR(incl_sys_attr_tail);
    incl_all_sys_attr_tail = CDR(incl_all_sys_attr_tail);
    incl_all_sys_attr_except_tail = CDR(incl_all_sys_attr_except_tail);
    kind_tail = CDR(kind_tail);
    goto next_loop;
  end_loop:
    list_of_interned_item_infos = ab_loopvar_;
    goto end_1;
    list_of_interned_item_infos = Qnil;
  end_1:;
    list_to_intern = icp_cons_1(varargs_p,list_of_interned_item_infos);
    temp = intern_list(list_to_intern);
    reclaim_icp_list_1(list_to_intern);
    return VALUES_1(temp);
}

/* RECLAIM-REMOTE-PROCEDURE-IDENTIFIER-FOR-CONNECTION-LOSS */
Object reclaim_remote_procedure_identifier_for_connection_loss(remote_procedure_identifier,
	    icp_port)
    Object remote_procedure_identifier, icp_port;
{
    x_note_fn_call(157,85);
    if (EQ(ISVREF(icp_port,(SI_Long)3L),Qinput))
	return abort_rpc_call_and_reclaim_identifier(remote_procedure_identifier);
    else
	return signal_error_to_rpc_caller_and_reclaim_identifier(remote_procedure_identifier);
}

static Object Qestablish_new_object_index_for_remote_procedure_identifier;  /* establish-new-object-index-for-remote-procedure-identifier */

/* ESTABLISH-NEW-OBJECT-INDEX-FOR-REMOTE-PROCEDURE-IDENTIFIER */
Object establish_new_object_index_for_remote_procedure_identifier varargs_1(int, n)
{
    Object remote_procedure_identifier, icp_port;
    Object send_enlarge_message_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, svref_new_value, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(157,86);
    INIT_ARGS_nonrelocating();
    remote_procedure_identifier = REQUIRED_ARG_nonrelocating();
    icp_port = REQUIRED_ARG_nonrelocating();
    send_enlarge_message_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    if (Disable_resumability) {
	result = assign_corresponding_icp_object_index(remote_procedure_identifier,
		Qstandard_icp_object_index_space,send_enlarge_message_p);
	MVS_2(result,corresponding_icp_object_index,
		new_index_limit_plus_one_qm);
	svref_new_value = gensym_cons_1(icp_port,
		gensym_cons_1(corresponding_icp_object_index,
		ISVREF(remote_procedure_identifier,(SI_Long)2L)));
	SVREF(remote_procedure_identifier,FIX((SI_Long)2L)) = svref_new_value;
	if (send_enlarge_message_p)
	    return VALUES_1(corresponding_icp_object_index);
	else
	    return VALUES_2(corresponding_icp_object_index,
		    new_index_limit_plus_one_qm);
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( 
		    !EQ(Qestablish_new_object_index_for_remote_procedure_identifier,
		    top))
		return icp_error_internal(Qerror,string_constant,
			Qestablish_new_object_index_for_remote_procedure_identifier,
			top,Nil);
	}
	remote_procedure_identifier = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : remote_procedure_identifier;
	icp_port = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : icp_port;
	send_enlarge_message_p = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : send_enlarge_message_p;
	result = assign_corresponding_icp_object_index(remote_procedure_identifier,
		Qstandard_icp_object_index_space,send_enlarge_message_p);
	MVS_2(result,corresponding_icp_object_index,
		new_index_limit_plus_one_qm);
	svref_new_value = gensym_cons_1(icp_port,
		gensym_cons_1(corresponding_icp_object_index,
		ISVREF(remote_procedure_identifier,(SI_Long)2L)));
	SVREF(remote_procedure_identifier,FIX((SI_Long)2L)) = svref_new_value;
	if (send_enlarge_message_p)
	    return VALUES_1(corresponding_icp_object_index);
	else
	    return VALUES_2(corresponding_icp_object_index,
		    new_index_limit_plus_one_qm);
    }
}

static Object Qmake_corresponding_icp_remote_procedure_identifier;  /* make-corresponding-icp-remote-procedure-identifier */

/* MAKE-CORRESPONDING-ICP-REMOTE-PROCEDURE-IDENTIFIER */
Object make_corresponding_icp_remote_procedure_identifier(remote_procedure_identifier)
    Object remote_procedure_identifier;
{
    Object writing_resumable_icp_messages_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, svref_new_value, temp;
    Object item_passing_info, varargsp, item_info, ab_loop_list_;
    Object included_attributes_spec, ab_loopvar_, ab_loopvar__1;
    Object excluded_attributes_spec, ab_loopvar__2;
    Object included_system_attributes_spec, ab_loopvar__3;
    Object include_all_system_attributes_spec, ab_loopvar__4;
    Object include_all_system_attributes_except_spec, ab_loopvar__5, kind_spec;
    Object ab_loopvar__6, resumable_icp_state_1, icp_suspend_1, top;
    Object ab_loopvar__7, ab_loopvar__8, ab_loopvar__9, ab_loopvar__10;
    Object ab_loopvar__11, gensymed_symbol, value, v1, v2, v3;
    Declare_special(1);
    Object result;

    x_note_fn_call(157,87);
    if (Disable_resumability) {
	write_icp_maybe_suspend();
	writing_resumable_icp_messages_p = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Writing_resumable_icp_messages_p,Qwriting_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		0);
	  result = assign_corresponding_icp_object_index(remote_procedure_identifier,
		  Qstandard_icp_object_index_space,T);
	  MVS_2(result,corresponding_icp_object_index,
		  new_index_limit_plus_one_qm);
	  svref_new_value = gensym_cons_1(Current_icp_port,
		  gensym_cons_1(corresponding_icp_object_index,
		  ISVREF(remote_procedure_identifier,(SI_Long)2L)));
	  SVREF(remote_procedure_identifier,FIX((SI_Long)2L)) = 
		  svref_new_value;
	  if (T);
	  else {
	      temp = corresponding_icp_object_index;
	      corresponding_icp_object_index = temp;
	  }
	  if ( !TRUEP(Inhibit_corresponding_icp_object_making)) {
	      item_passing_info = ISVREF(remote_procedure_identifier,
		      (SI_Long)8L);
	      temp = ISVREF(ISVREF(item_passing_info,(SI_Long)1L),(SI_Long)1L);
	      varargsp = CAR(temp);
	      item_info = Nil;
	      temp = ISVREF(ISVREF(item_passing_info,(SI_Long)1L),(SI_Long)1L);
	      ab_loop_list_ = CDR(temp);
	      included_attributes_spec = Nil;
	      ab_loopvar_ = Nil;
	      ab_loopvar__1 = Nil;
	      excluded_attributes_spec = Nil;
	      ab_loopvar__2 = Nil;
	      ab_loopvar__1 = Nil;
	      included_system_attributes_spec = Nil;
	      ab_loopvar__3 = Nil;
	      ab_loopvar__1 = Nil;
	      include_all_system_attributes_spec = Nil;
	      ab_loopvar__4 = Nil;
	      ab_loopvar__1 = Nil;
	      include_all_system_attributes_except_spec = Nil;
	      ab_loopvar__5 = Nil;
	      ab_loopvar__1 = Nil;
	      kind_spec = Nil;
	      ab_loopvar__6 = Nil;
	      ab_loopvar__1 = Nil;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      item_info = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      ab_loopvar__1 = 
		      gensym_cons_1(remote_procedure_item_info_included_attributes(item_info),
		      Nil);
	      if (ab_loopvar_)
		  M_CDR(ab_loopvar_) = ab_loopvar__1;
	      else
		  included_attributes_spec = ab_loopvar__1;
	      ab_loopvar_ = ab_loopvar__1;
	      ab_loopvar__1 = 
		      gensym_cons_1(remote_procedure_item_info_excluded_attributes(item_info),
		      Nil);
	      if (ab_loopvar__2)
		  M_CDR(ab_loopvar__2) = ab_loopvar__1;
	      else
		  excluded_attributes_spec = ab_loopvar__1;
	      ab_loopvar__2 = ab_loopvar__1;
	      ab_loopvar__1 = 
		      gensym_cons_1(remote_procedure_item_info_included_system_attributes(item_info),
		      Nil);
	      if (ab_loopvar__3)
		  M_CDR(ab_loopvar__3) = ab_loopvar__1;
	      else
		  included_system_attributes_spec = ab_loopvar__1;
	      ab_loopvar__3 = ab_loopvar__1;
	      ab_loopvar__1 = 
		      gensym_cons_1(remote_procedure_item_info_include_all_system_attributes(item_info),
		      Nil);
	      if (ab_loopvar__4)
		  M_CDR(ab_loopvar__4) = ab_loopvar__1;
	      else
		  include_all_system_attributes_spec = ab_loopvar__1;
	      ab_loopvar__4 = ab_loopvar__1;
	      ab_loopvar__1 = 
		      gensym_cons_1(remote_procedure_item_info_include_all_system_attributes_except(item_info),
		      Nil);
	      if (ab_loopvar__5)
		  M_CDR(ab_loopvar__5) = ab_loopvar__1;
	      else
		  include_all_system_attributes_except_spec = ab_loopvar__1;
	      ab_loopvar__5 = ab_loopvar__1;
	      ab_loopvar__1 = 
		      gensym_cons_1(remote_procedure_item_info_kind(item_info),
		      Nil);
	      if (ab_loopvar__6)
		  M_CDR(ab_loopvar__6) = ab_loopvar__1;
	      else
		  kind_spec = ab_loopvar__1;
	      ab_loopvar__6 = ab_loopvar__1;
	      goto next_loop;
	    end_loop:
	      send_icp_define_remote_procedure_identifier(corresponding_icp_object_index,
		      ISVREF(remote_procedure_identifier,(SI_Long)1L),
		      included_attributes_spec,excluded_attributes_spec,
		      included_system_attributes_spec,
		      include_all_system_attributes_spec,
		      include_all_system_attributes_except_spec,kind_spec,
		      varargsp);
	      reclaim_gensym_list_1(included_attributes_spec);
	      reclaim_gensym_list_1(excluded_attributes_spec);
	      reclaim_gensym_list_1(included_system_attributes_spec);
	      reclaim_gensym_list_1(include_all_system_attributes_spec);
	      reclaim_gensym_list_1(include_all_system_attributes_except_spec);
	      reclaim_gensym_list_1(kind_spec);
	      goto end_1;
	    end_1:;
	  }
	  result = VALUES_1(corresponding_icp_object_index);
	POP_SPECIAL();
	return result;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qmake_corresponding_icp_remote_procedure_identifier,top))
		return icp_error_internal(Qerror,string_constant,
			Qmake_corresponding_icp_remote_procedure_identifier,
			top,Nil);
	}
	remote_procedure_identifier = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : remote_procedure_identifier;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    temp = resumable_icp_pop();
	    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) 
		    && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		switch (INTEGER_TO_CHAR(temp)) {
		  case 1:
		    goto l1;
		    break;
		  case 2:
		    goto l2;
		    break;
		  default:
		    break;
		}
	}
      l1:
	if (EQ(icp_suspend_1,write_icp_maybe_suspend())) {
	    resumable_icp_push(FIX((SI_Long)1L));
	    result = VALUES_1(Icp_suspend);
	    goto end_block;
	}
      l2:
	writing_resumable_icp_messages_p = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Writing_resumable_icp_messages_p,Qwriting_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		0);
	  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()))
	      corresponding_icp_object_index = resumable_icp_pop();
	  else {
	      result = assign_corresponding_icp_object_index(remote_procedure_identifier,
		      Qstandard_icp_object_index_space,T);
	      MVS_2(result,corresponding_icp_object_index,
		      new_index_limit_plus_one_qm);
	      svref_new_value = gensym_cons_1(Current_icp_port,
		      gensym_cons_1(corresponding_icp_object_index,
		      ISVREF(remote_procedure_identifier,(SI_Long)2L)));
	      SVREF(remote_procedure_identifier,FIX((SI_Long)2L)) = 
		      svref_new_value;
	      if (T);
	      else {
		  temp = corresponding_icp_object_index;
		  corresponding_icp_object_index = temp;
	      }
	  }
	  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) ||  
		  !TRUEP(Inhibit_corresponding_icp_object_making)) {
	      item_passing_info = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : 
		      ISVREF(remote_procedure_identifier,(SI_Long)8L);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  varargsp = resumable_icp_pop();
	      else {
		  temp = ISVREF(ISVREF(item_passing_info,(SI_Long)1L),
			  (SI_Long)1L);
		  varargsp = CAR(temp);
	      }
	      item_info = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  ab_loop_list_ = resumable_icp_pop();
	      else {
		  temp = ISVREF(ISVREF(item_passing_info,(SI_Long)1L),
			  (SI_Long)1L);
		  ab_loop_list_ = CDR(temp);
	      }
	      included_attributes_spec = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      ab_loopvar_ = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      ab_loopvar__1 = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      excluded_attributes_spec = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      ab_loopvar__2 = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      ab_loopvar__3 = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      included_system_attributes_spec = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      ab_loopvar__4 = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      ab_loopvar__5 = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      include_all_system_attributes_spec = (resumable_icp_state_1 ?
		       TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      ab_loopvar__6 = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      ab_loopvar__7 = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      include_all_system_attributes_except_spec = 
		      (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
		       TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      ab_loopvar__8 = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      ab_loopvar__9 = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      kind_spec = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      ab_loopvar__10 = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      ab_loopvar__11 = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil))
		  goto resume;
	    next_loop_1:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_1;
	      item_info = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      ab_loopvar__1 = 
		      gensym_cons_1(remote_procedure_item_info_included_attributes(item_info),
		      Nil);
	      if (ab_loopvar_)
		  M_CDR(ab_loopvar_) = ab_loopvar__1;
	      else
		  included_attributes_spec = ab_loopvar__1;
	      ab_loopvar_ = ab_loopvar__1;
	      ab_loopvar__3 = 
		      gensym_cons_1(remote_procedure_item_info_excluded_attributes(item_info),
		      Nil);
	      if (ab_loopvar__2)
		  M_CDR(ab_loopvar__2) = ab_loopvar__3;
	      else
		  excluded_attributes_spec = ab_loopvar__3;
	      ab_loopvar__2 = ab_loopvar__3;
	      ab_loopvar__5 = 
		      gensym_cons_1(remote_procedure_item_info_included_system_attributes(item_info),
		      Nil);
	      if (ab_loopvar__4)
		  M_CDR(ab_loopvar__4) = ab_loopvar__5;
	      else
		  included_system_attributes_spec = ab_loopvar__5;
	      ab_loopvar__4 = ab_loopvar__5;
	      ab_loopvar__7 = 
		      gensym_cons_1(remote_procedure_item_info_include_all_system_attributes(item_info),
		      Nil);
	      if (ab_loopvar__6)
		  M_CDR(ab_loopvar__6) = ab_loopvar__7;
	      else
		  include_all_system_attributes_spec = ab_loopvar__7;
	      ab_loopvar__6 = ab_loopvar__7;
	      ab_loopvar__9 = 
		      gensym_cons_1(remote_procedure_item_info_include_all_system_attributes_except(item_info),
		      Nil);
	      if (ab_loopvar__8)
		  M_CDR(ab_loopvar__8) = ab_loopvar__9;
	      else
		  include_all_system_attributes_except_spec = ab_loopvar__9;
	      ab_loopvar__8 = ab_loopvar__9;
	      ab_loopvar__11 = 
		      gensym_cons_1(remote_procedure_item_info_kind(item_info),
		      Nil);
	      if (ab_loopvar__10)
		  M_CDR(ab_loopvar__10) = ab_loopvar__11;
	      else
		  kind_spec = ab_loopvar__11;
	      ab_loopvar__10 = ab_loopvar__11;
	      goto next_loop_1;
	    end_loop_1:
	    resume:
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  gensymed_symbol = resumable_icp_pop();
	      else {
		  value = 
			  send_icp_define_remote_procedure_identifier(corresponding_icp_object_index,
			  ISVREF(remote_procedure_identifier,(SI_Long)1L),
			  included_attributes_spec,
			  excluded_attributes_spec,
			  included_system_attributes_spec,
			  include_all_system_attributes_spec,
			  include_all_system_attributes_except_spec,
			  kind_spec,varargsp);
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(ab_loopvar__11);
		      resumable_icp_push(ab_loopvar__10);
		      resumable_icp_push(kind_spec);
		      resumable_icp_push(ab_loopvar__9);
		      resumable_icp_push(ab_loopvar__8);
		      resumable_icp_push(include_all_system_attributes_except_spec);
		      resumable_icp_push(ab_loopvar__7);
		      resumable_icp_push(ab_loopvar__6);
		      resumable_icp_push(include_all_system_attributes_spec);
		      resumable_icp_push(ab_loopvar__5);
		      resumable_icp_push(ab_loopvar__4);
		      resumable_icp_push(included_system_attributes_spec);
		      resumable_icp_push(ab_loopvar__3);
		      resumable_icp_push(ab_loopvar__2);
		      resumable_icp_push(excluded_attributes_spec);
		      resumable_icp_push(ab_loopvar__1);
		      resumable_icp_push(ab_loopvar_);
		      resumable_icp_push(included_attributes_spec);
		      resumable_icp_push(ab_loop_list_);
		      resumable_icp_push(item_info);
		      resumable_icp_push(varargsp);
		      resumable_icp_push(item_passing_info);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Writing_resumable_icp_messages_p);
		      resumable_icp_push(FIX((SI_Long)2L));
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_block;
		  }
		  gensymed_symbol = value;
	      }
	      reclaim_gensym_list_1(included_attributes_spec);
	      reclaim_gensym_list_1(excluded_attributes_spec);
	      reclaim_gensym_list_1(included_system_attributes_spec);
	      reclaim_gensym_list_1(include_all_system_attributes_spec);
	      reclaim_gensym_list_1(include_all_system_attributes_except_spec);
	      reclaim_gensym_list_1(kind_spec);
	      goto end_2;
	    end_2:;
	  }
	  result = VALUES_1(corresponding_icp_object_index);
	POP_SPECIAL();
	goto end_block;
      end_block:
	MVS_3(result,v1,v2,v3);
	if (EQ(icp_suspend_1,v1)) {
	    resumable_icp_push(remote_procedure_identifier);
	    resumable_icp_push(Qmake_corresponding_icp_remote_procedure_identifier);
	    return VALUES_1(Icp_suspend);
	}
	return VALUES_3(v1,v2,v3);
    }
}

/* GET-ICP-OBJECT-INDEX-FOR-REMOTE-PROCEDURE-IDENTIFIER */
Object get_icp_object_index_for_remote_procedure_identifier(remote_procedure_identifier,
	    icp_port)
    Object remote_procedure_identifier, icp_port;
{
    x_note_fn_call(157,88);
    return getfq_function_no_default(ISVREF(remote_procedure_identifier,
	    (SI_Long)2L),icp_port);
}

/* SET-ICP-OBJECT-INDEX-FOR-REMOTE-PROCEDURE-IDENTIFIER */
Object set_icp_object_index_for_remote_procedure_identifier(remote_procedure_identifier,
	    corresponding_icp_object_index,icp_port)
    Object remote_procedure_identifier, corresponding_icp_object_index;
    Object icp_port;
{
    Object svref_new_value;

    x_note_fn_call(157,89);
    svref_new_value = gensym_cons_1(icp_port,
	    gensym_cons_1(corresponding_icp_object_index,
	    ISVREF(remote_procedure_identifier,(SI_Long)2L)));
    return VALUES_1(SVREF(remote_procedure_identifier,FIX((SI_Long)2L)) = 
	    svref_new_value);
}

/* RECLAIM-ICP-OBJECT-MAP-FOR-REMOTE-PROCEDURE-IDENTIFIER */
Object reclaim_icp_object_map_for_remote_procedure_identifier(remote_procedure_identifier)
    Object remote_procedure_identifier;
{
    Object icp_object_map;

    x_note_fn_call(157,90);
    icp_object_map = ISVREF(remote_procedure_identifier,(SI_Long)2L);
    if (icp_object_map)
	return reclaim_icp_object_map(remote_procedure_identifier,
		icp_object_map,Qstandard_icp_object_index_space);
    else
	return VALUES_1(Nil);
}

static Object Qset_access_form_for_remote_procedure_identifier;  /* set-access-form-for-remote-procedure-identifier */

/* RECLAIM-ICP-PORT-ENTRY-FOR-REMOTE-PROCEDURE-IDENTIFIER */
Object reclaim_icp_port_entry_for_remote_procedure_identifier(remote_procedure_identifier,
	    icp_port)
    Object remote_procedure_identifier, icp_port;
{
    x_note_fn_call(157,91);
    return reclaim_icp_port_entry(icp_port,remote_procedure_identifier,
	    ISVREF(remote_procedure_identifier,(SI_Long)2L),
	    Qset_access_form_for_remote_procedure_identifier);
}

/* SET-ACCESS-FORM-FOR-REMOTE-PROCEDURE-IDENTIFIER */
Object set_access_form_for_remote_procedure_identifier(remote_procedure_identifier,
	    new_value)
    Object remote_procedure_identifier, new_value;
{
    x_note_fn_call(157,92);
    return VALUES_1(SVREF(remote_procedure_identifier,FIX((SI_Long)2L)) = 
	    new_value);
}

static Object Qsend_icp_define_remote_procedure_identifier;  /* send-icp-define-remote-procedure-identifier */

static Object Qdefine_remote_procedure_identifier;  /* define-remote-procedure-identifier */

static Object Qremote_procedure_identifier_tag;  /* remote-procedure-identifier-tag */

static Object Qlist_of_included_return_attributes;  /* list-of-included-return-attributes */

static Object Qlist_of_excluded_return_attributes;  /* list-of-excluded-return-attributes */

static Object Qlist_of_included_return_system_attributes;  /* list-of-included-return-system-attributes */

static Object Qlist_of_include_all_return_system_attributes;  /* list-of-include-all-return-system-attributes */

static Object Qlist_of_include_all_return_system_attributes_except;  /* list-of-include-all-return-system-attributes-except */

static Object Qlist_of_return_kinds;  /* list-of-return-kinds */

static Object Qremote_procedure_varargs_p;  /* remote-procedure-varargs-p */

/* SEND-ICP-DEFINE-REMOTE-PROCEDURE-IDENTIFIER */
Object send_icp_define_remote_procedure_identifier(corresponding_icp_object_index,
	    remote_procedure_identifier_tag,
	    list_of_included_return_attributes,
	    list_of_excluded_return_attributes,
	    list_of_included_return_system_attributes,
	    list_of_include_all_return_system_attributes,
	    list_of_include_all_return_system_attributes_except,
	    list_of_return_kinds,remote_procedure_varargs_p)
    Object corresponding_icp_object_index, remote_procedure_identifier_tag;
    Object list_of_included_return_attributes;
    Object list_of_excluded_return_attributes;
    Object list_of_included_return_system_attributes;
    Object list_of_include_all_return_system_attributes;
    Object list_of_include_all_return_system_attributes_except;
    Object list_of_return_kinds, remote_procedure_varargs_p;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(3);
    Object result;

    x_note_fn_call(157,93);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_define_remote_procedure_identifier;
	  }
	  start_writing_icp_message(FIX((SI_Long)222L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qdefine_remote_procedure_identifier,
			  string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_unsigned_integer(corresponding_icp_object_index);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qcorresponding_icp_object_index,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_unsigned_integer(corresponding_icp_object_index);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qremote_procedure_identifier_tag,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_unsigned_integer(remote_procedure_identifier_tag);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qremote_procedure_identifier_tag,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_unsigned_integer(remote_procedure_identifier_tag);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qlist_of_included_return_attributes,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_list_of_included_return_attributes(list_of_included_return_attributes);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qlist_of_included_return_attributes,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_list_of_included_return_attributes(list_of_included_return_attributes);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qlist_of_excluded_return_attributes,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_list_of_excluded_return_attributes(list_of_excluded_return_attributes);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qlist_of_excluded_return_attributes,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_list_of_excluded_return_attributes(list_of_excluded_return_attributes);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qlist_of_included_return_system_attributes,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_list_of_included_return_system_attributes(list_of_included_return_system_attributes);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qlist_of_included_return_system_attributes,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_list_of_included_return_system_attributes(list_of_included_return_system_attributes);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qlist_of_include_all_return_system_attributes,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_list_of_include_all_return_system_attributes(list_of_include_all_return_system_attributes);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qlist_of_include_all_return_system_attributes,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_list_of_include_all_return_system_attributes(list_of_include_all_return_system_attributes);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qlist_of_include_all_return_system_attributes_except,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_list_of_include_all_return_system_attributes_except(list_of_include_all_return_system_attributes_except);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qlist_of_include_all_return_system_attributes_except,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_list_of_include_all_return_system_attributes_except(list_of_include_all_return_system_attributes_except);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qlist_of_return_kinds,string_constant_2,
				Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_list_of_return_kinds(list_of_return_kinds);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qlist_of_return_kinds,string_constant_2,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_list_of_return_kinds(list_of_return_kinds);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qremote_procedure_varargs_p,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_remote_procedure_varargs_p(remote_procedure_varargs_p);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qremote_procedure_varargs_p,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_remote_procedure_varargs_p(remote_procedure_varargs_p);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qdefine_remote_procedure_identifier,
			    string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else {
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_unsigned_integer(corresponding_icp_object_index);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_unsigned_integer(corresponding_icp_object_index);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qremote_procedure_identifier_tag,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_unsigned_integer(remote_procedure_identifier_tag);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qremote_procedure_identifier_tag,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_unsigned_integer(remote_procedure_identifier_tag);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qlist_of_included_return_attributes,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_list_of_included_return_attributes(list_of_included_return_attributes);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qlist_of_included_return_attributes,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_list_of_included_return_attributes(list_of_included_return_attributes);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qlist_of_excluded_return_attributes,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_list_of_excluded_return_attributes(list_of_excluded_return_attributes);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qlist_of_excluded_return_attributes,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_list_of_excluded_return_attributes(list_of_excluded_return_attributes);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qlist_of_included_return_system_attributes,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_list_of_included_return_system_attributes(list_of_included_return_system_attributes);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qlist_of_included_return_system_attributes,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_list_of_included_return_system_attributes(list_of_included_return_system_attributes);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qlist_of_include_all_return_system_attributes,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_list_of_include_all_return_system_attributes(list_of_include_all_return_system_attributes);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qlist_of_include_all_return_system_attributes,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_list_of_include_all_return_system_attributes(list_of_include_all_return_system_attributes);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qlist_of_include_all_return_system_attributes_except,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_list_of_include_all_return_system_attributes_except(list_of_include_all_return_system_attributes_except);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qlist_of_include_all_return_system_attributes_except,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_list_of_include_all_return_system_attributes_except(list_of_include_all_return_system_attributes_except);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qlist_of_return_kinds,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_list_of_return_kinds(list_of_return_kinds);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qlist_of_return_kinds,string_constant_2,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_list_of_return_kinds(list_of_return_kinds);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qremote_procedure_varargs_p,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_remote_procedure_varargs_p(remote_procedure_varargs_p);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qremote_procedure_varargs_p,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_remote_procedure_varargs_p(remote_procedure_varargs_p);
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_define_remote_procedure_identifier,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qsend_icp_define_remote_procedure_identifier,top,Nil);
		goto end_send_icp_define_remote_procedure_identifier;
	    }
	}
	corresponding_icp_object_index = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : corresponding_icp_object_index;
	remote_procedure_identifier_tag = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : remote_procedure_identifier_tag;
	list_of_included_return_attributes = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : list_of_included_return_attributes;
	list_of_excluded_return_attributes = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : list_of_excluded_return_attributes;
	list_of_included_return_system_attributes = (resumable_icp_state_1 
		? TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : 
		list_of_included_return_system_attributes;
	list_of_include_all_return_system_attributes = 
		(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : 
		list_of_include_all_return_system_attributes;
	list_of_include_all_return_system_attributes_except = 
		(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : 
		list_of_include_all_return_system_attributes_except;
	list_of_return_kinds = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : list_of_return_kinds;
	remote_procedure_varargs_p = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : remote_procedure_varargs_p;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_define_remote_procedure_identifier;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)222L)))) {
	      resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qdefine_remote_procedure_identifier,
			  string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    temp_1 = resumable_icp_pop();
		    if (! !(FIXNUMP(temp_1) && 
			    FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			    FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			switch (INTEGER_TO_CHAR(temp_1)) {
			  case 1:
			    goto l1_1;
			    break;
			  case 2:
			    goto l2_1;
			    break;
			  case 3:
			    goto l3;
			    break;
			  case 4:
			    goto l4;
			    break;
			  case 5:
			    goto l5;
			    break;
			  case 6:
			    goto l6;
			    break;
			  case 7:
			    goto l7;
			    break;
			  case 8:
			    goto l8;
			    break;
			  case 9:
			    goto l9;
			    break;
			  default:
			    break;
			}
		}
	      l1_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_unsigned_integer(corresponding_icp_object_index))) 
				  {
			  resumable_icp_push(FIX((SI_Long)1L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qcorresponding_icp_object_index,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_unsigned_integer(corresponding_icp_object_index))) 
			    {
		    resumable_icp_push(FIX((SI_Long)1L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l2_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qremote_procedure_identifier_tag,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_unsigned_integer(remote_procedure_identifier_tag))) 
				  {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qremote_procedure_identifier_tag,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_unsigned_integer(remote_procedure_identifier_tag))) 
			    {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l3:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qlist_of_included_return_attributes,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_list_of_included_return_attributes(list_of_included_return_attributes))) 
				  {
			  resumable_icp_push(FIX((SI_Long)3L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qlist_of_included_return_attributes,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_list_of_included_return_attributes(list_of_included_return_attributes))) 
			    {
		    resumable_icp_push(FIX((SI_Long)3L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l4:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qlist_of_excluded_return_attributes,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_list_of_excluded_return_attributes(list_of_excluded_return_attributes))) 
				  {
			  resumable_icp_push(FIX((SI_Long)4L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qlist_of_excluded_return_attributes,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_list_of_excluded_return_attributes(list_of_excluded_return_attributes))) 
			    {
		    resumable_icp_push(FIX((SI_Long)4L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l5:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qlist_of_included_return_system_attributes,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_list_of_included_return_system_attributes(list_of_included_return_system_attributes))) 
				  {
			  resumable_icp_push(FIX((SI_Long)5L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qlist_of_included_return_system_attributes,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_list_of_included_return_system_attributes(list_of_included_return_system_attributes))) 
			    {
		    resumable_icp_push(FIX((SI_Long)5L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l6:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qlist_of_include_all_return_system_attributes,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_list_of_include_all_return_system_attributes(list_of_include_all_return_system_attributes))) 
				  {
			  resumable_icp_push(FIX((SI_Long)6L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qlist_of_include_all_return_system_attributes,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_list_of_include_all_return_system_attributes(list_of_include_all_return_system_attributes))) 
			    {
		    resumable_icp_push(FIX((SI_Long)6L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l7:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qlist_of_include_all_return_system_attributes_except,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_list_of_include_all_return_system_attributes_except(list_of_include_all_return_system_attributes_except))) 
				  {
			  resumable_icp_push(FIX((SI_Long)7L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qlist_of_include_all_return_system_attributes_except,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_list_of_include_all_return_system_attributes_except(list_of_include_all_return_system_attributes_except))) 
			    {
		    resumable_icp_push(FIX((SI_Long)7L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l8:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qlist_of_return_kinds,string_constant_2,
				Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_list_of_return_kinds(list_of_return_kinds))) 
				  {
			  resumable_icp_push(FIX((SI_Long)8L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qlist_of_return_kinds,string_constant_2,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_list_of_return_kinds(list_of_return_kinds))) 
			    {
		    resumable_icp_push(FIX((SI_Long)8L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l9:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qremote_procedure_varargs_p,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_remote_procedure_varargs_p(remote_procedure_varargs_p))) 
				  {
			  resumable_icp_push(FIX((SI_Long)9L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qremote_procedure_varargs_p,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      temp_1 = result_of_write;
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_remote_procedure_varargs_p(remote_procedure_varargs_p))) 
			    {
		    resumable_icp_push(FIX((SI_Long)9L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
		else
		    temp_1 = Nil;
		goto end_block_1;
	      end_block_1:
		if (EQ(icp_suspend_1,temp_1)) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qdefine_remote_procedure_identifier,
			    string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else {
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  temp_1 = resumable_icp_pop();
		  if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
			  temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		      switch (INTEGER_TO_CHAR(temp_1)) {
			case 1:
			  goto l1_2;
			  break;
			case 2:
			  goto l2_2;
			  break;
			case 3:
			  goto l3_1;
			  break;
			case 4:
			  goto l4_1;
			  break;
			case 5:
			  goto l5_1;
			  break;
			case 6:
			  goto l6_1;
			  break;
			case 7:
			  goto l7_1;
			  break;
			case 8:
			  goto l8_1;
			  break;
			case 9:
			  goto l9_1;
			  break;
			default:
			  break;
		      }
	      }
	    l1_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_unsigned_integer(corresponding_icp_object_index))) 
				{
			resumable_icp_push(FIX((SI_Long)1L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_unsigned_integer(corresponding_icp_object_index))) 
			  {
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l2_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qremote_procedure_identifier_tag,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_unsigned_integer(remote_procedure_identifier_tag))) 
				{
			resumable_icp_push(FIX((SI_Long)2L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qremote_procedure_identifier_tag,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_unsigned_integer(remote_procedure_identifier_tag))) 
			  {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l3_1:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qlist_of_included_return_attributes,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_list_of_included_return_attributes(list_of_included_return_attributes))) 
				{
			resumable_icp_push(FIX((SI_Long)3L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qlist_of_included_return_attributes,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_list_of_included_return_attributes(list_of_included_return_attributes))) 
			  {
		  resumable_icp_push(FIX((SI_Long)3L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l4_1:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qlist_of_excluded_return_attributes,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_list_of_excluded_return_attributes(list_of_excluded_return_attributes))) 
				{
			resumable_icp_push(FIX((SI_Long)4L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qlist_of_excluded_return_attributes,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_list_of_excluded_return_attributes(list_of_excluded_return_attributes))) 
			  {
		  resumable_icp_push(FIX((SI_Long)4L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l5_1:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qlist_of_included_return_system_attributes,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_list_of_included_return_system_attributes(list_of_included_return_system_attributes))) 
				{
			resumable_icp_push(FIX((SI_Long)5L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qlist_of_included_return_system_attributes,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_list_of_included_return_system_attributes(list_of_included_return_system_attributes))) 
			  {
		  resumable_icp_push(FIX((SI_Long)5L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l6_1:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qlist_of_include_all_return_system_attributes,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_list_of_include_all_return_system_attributes(list_of_include_all_return_system_attributes))) 
				{
			resumable_icp_push(FIX((SI_Long)6L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qlist_of_include_all_return_system_attributes,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_list_of_include_all_return_system_attributes(list_of_include_all_return_system_attributes))) 
			  {
		  resumable_icp_push(FIX((SI_Long)6L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l7_1:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qlist_of_include_all_return_system_attributes_except,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_list_of_include_all_return_system_attributes_except(list_of_include_all_return_system_attributes_except))) 
				{
			resumable_icp_push(FIX((SI_Long)7L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qlist_of_include_all_return_system_attributes_except,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_list_of_include_all_return_system_attributes_except(list_of_include_all_return_system_attributes_except))) 
			  {
		  resumable_icp_push(FIX((SI_Long)7L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l8_1:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qlist_of_return_kinds,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_list_of_return_kinds(list_of_return_kinds))) 
				{
			resumable_icp_push(FIX((SI_Long)8L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qlist_of_return_kinds,string_constant_2,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_list_of_return_kinds(list_of_return_kinds))) {
		  resumable_icp_push(FIX((SI_Long)8L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l9_1:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qremote_procedure_varargs_p,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_remote_procedure_varargs_p(remote_procedure_varargs_p))) 
				{
			resumable_icp_push(FIX((SI_Long)9L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qremote_procedure_varargs_p,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_remote_procedure_varargs_p(remote_procedure_varargs_p))) 
			  {
		  resumable_icp_push(FIX((SI_Long)9L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	      else
		  temp_1 = Nil;
	      goto end_block_2;
	    end_block_2:
	      if (EQ(icp_suspend_1,temp_1)) {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      else
		  temp_1 = Nil;
	  }
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(remote_procedure_varargs_p);
	      resumable_icp_push(list_of_return_kinds);
	      resumable_icp_push(list_of_include_all_return_system_attributes_except);
	      resumable_icp_push(list_of_include_all_return_system_attributes);
	      resumable_icp_push(list_of_included_return_system_attributes);
	      resumable_icp_push(list_of_excluded_return_attributes);
	      resumable_icp_push(list_of_included_return_attributes);
	      resumable_icp_push(remote_procedure_identifier_tag);
	      resumable_icp_push(corresponding_icp_object_index);
	      resumable_icp_push(Qsend_icp_define_remote_procedure_identifier);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_define_remote_procedure_identifier;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_define_remote_procedure_identifier:
    return result;
}

/* HANDLE-ICP-DEFINE-REMOTE-PROCEDURE-IDENTIFIER--BODY */
Object handle_icp_define_remote_procedure_identifier__body(corresponding_icp_object_index,
	    remote_procedure_identifier_tag,
	    list_of_included_return_attributes,
	    list_of_excluded_return_attributes,
	    list_of_included_return_system_attributes,
	    list_of_include_all_return_system_attributes,
	    list_of_include_all_return_system_attributes_except,
	    list_of_return_kinds,remote_procedure_varargs_p)
    Object corresponding_icp_object_index, remote_procedure_identifier_tag;
    Object list_of_included_return_attributes;
    Object list_of_excluded_return_attributes;
    Object list_of_included_return_system_attributes;
    Object list_of_include_all_return_system_attributes;
    Object list_of_include_all_return_system_attributes_except;
    Object list_of_return_kinds, remote_procedure_varargs_p;
{
    Object new_remote_procedure_identifier;

    x_note_fn_call(157,94);
    new_remote_procedure_identifier = 
	    make_incoming_remote_procedure_identifier(remote_procedure_identifier_tag,
	    make_remote_procedure_item_passing_info_from_specs(Nil,
	    list_of_included_return_attributes,
	    list_of_excluded_return_attributes,
	    list_of_included_return_system_attributes,
	    list_of_include_all_return_system_attributes,
	    list_of_include_all_return_system_attributes_except,
	    list_of_return_kinds,remote_procedure_varargs_p));
    reclaim_icp_tree_1(list_of_included_return_attributes);
    reclaim_icp_tree_1(list_of_excluded_return_attributes);
    reclaim_icp_tree_1(list_of_included_return_system_attributes);
    reclaim_icp_tree_1(list_of_include_all_return_system_attributes);
    reclaim_icp_tree_1(list_of_include_all_return_system_attributes_except);
    reclaim_icp_tree_1(list_of_return_kinds);
    store_corresponding_icp_object(corresponding_icp_object_index,
	    new_remote_procedure_identifier);
    return VALUES_1(Nil);
}

static Object Qhandle_icp_define_remote_procedure_identifier;  /* handle-icp-define-remote-procedure-identifier */

/* HANDLE-ICP-DEFINE-REMOTE-PROCEDURE-IDENTIFIER */
Object handle_icp_define_remote_procedure_identifier()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read, corresponding_icp_object_index;
    Object remote_procedure_identifier_tag, list_of_included_return_attributes;
    Object list_of_excluded_return_attributes;
    Object list_of_included_return_system_attributes;
    Object list_of_include_all_return_system_attributes;
    Object list_of_include_all_return_system_attributes_except;
    Object list_of_return_kinds, remote_procedure_varargs_p;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(157,95);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qdefine_remote_procedure_identifier,
			string_constant_1,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_unsigned_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    corresponding_icp_object_index = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  corresponding_icp_object_index = read_icp_unsigned_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qremote_procedure_identifier_tag,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_unsigned_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qremote_procedure_identifier_tag,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    remote_procedure_identifier_tag = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  remote_procedure_identifier_tag = 
			  read_icp_unsigned_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qlist_of_included_return_attributes,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = 
			    read_icp_list_of_included_return_attributes();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qlist_of_included_return_attributes,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    list_of_included_return_attributes = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  list_of_included_return_attributes = 
			  read_icp_list_of_included_return_attributes();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qlist_of_excluded_return_attributes,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = 
			    read_icp_list_of_excluded_return_attributes();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qlist_of_excluded_return_attributes,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    list_of_excluded_return_attributes = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  list_of_excluded_return_attributes = 
			  read_icp_list_of_excluded_return_attributes();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qlist_of_included_return_system_attributes,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = 
			    read_icp_list_of_included_return_system_attributes();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qlist_of_included_return_system_attributes,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    list_of_included_return_system_attributes = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  list_of_included_return_system_attributes = 
			  read_icp_list_of_included_return_system_attributes();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qlist_of_include_all_return_system_attributes,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = 
			    read_icp_list_of_include_all_return_system_attributes();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qlist_of_include_all_return_system_attributes,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    list_of_include_all_return_system_attributes = 
			    result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  list_of_include_all_return_system_attributes = 
			  read_icp_list_of_include_all_return_system_attributes();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qlist_of_include_all_return_system_attributes_except,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = 
			    read_icp_list_of_include_all_return_system_attributes_except();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qlist_of_include_all_return_system_attributes_except,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    list_of_include_all_return_system_attributes_except = 
			    result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  list_of_include_all_return_system_attributes_except = 
			  read_icp_list_of_include_all_return_system_attributes_except();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qlist_of_return_kinds,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_list_of_return_kinds();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qlist_of_return_kinds,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    list_of_return_kinds = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  list_of_return_kinds = read_icp_list_of_return_kinds();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qremote_procedure_varargs_p,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_remote_procedure_varargs_p();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qremote_procedure_varargs_p,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    remote_procedure_varargs_p = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  remote_procedure_varargs_p = 
			  read_icp_remote_procedure_varargs_p();
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_define_remote_procedure_identifier__body(corresponding_icp_object_index,
			remote_procedure_identifier_tag,
			list_of_included_return_attributes,
			list_of_excluded_return_attributes,
			list_of_included_return_system_attributes,
			list_of_include_all_return_system_attributes,
			list_of_include_all_return_system_attributes_except,
			list_of_return_kinds,remote_procedure_varargs_p);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qdefine_remote_procedure_identifier,
			  string_constant_1,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qcorresponding_icp_object_index,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_unsigned_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  corresponding_icp_object_index = result_of_read;
		POP_SPECIAL();
	    }
	    else
		corresponding_icp_object_index = read_icp_unsigned_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qremote_procedure_identifier_tag,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_unsigned_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qremote_procedure_identifier_tag,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  remote_procedure_identifier_tag = result_of_read;
		POP_SPECIAL();
	    }
	    else
		remote_procedure_identifier_tag = read_icp_unsigned_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qlist_of_included_return_attributes,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = 
			  read_icp_list_of_included_return_attributes();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qlist_of_included_return_attributes,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  list_of_included_return_attributes = result_of_read;
		POP_SPECIAL();
	    }
	    else
		list_of_included_return_attributes = 
			read_icp_list_of_included_return_attributes();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qlist_of_excluded_return_attributes,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = 
			  read_icp_list_of_excluded_return_attributes();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qlist_of_excluded_return_attributes,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  list_of_excluded_return_attributes = result_of_read;
		POP_SPECIAL();
	    }
	    else
		list_of_excluded_return_attributes = 
			read_icp_list_of_excluded_return_attributes();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qlist_of_included_return_system_attributes,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = 
			  read_icp_list_of_included_return_system_attributes();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qlist_of_included_return_system_attributes,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  list_of_included_return_system_attributes = result_of_read;
		POP_SPECIAL();
	    }
	    else
		list_of_included_return_system_attributes = 
			read_icp_list_of_included_return_system_attributes();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qlist_of_include_all_return_system_attributes,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = 
			  read_icp_list_of_include_all_return_system_attributes();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qlist_of_include_all_return_system_attributes,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  list_of_include_all_return_system_attributes = 
			  result_of_read;
		POP_SPECIAL();
	    }
	    else
		list_of_include_all_return_system_attributes = 
			read_icp_list_of_include_all_return_system_attributes();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qlist_of_include_all_return_system_attributes_except,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = 
			  read_icp_list_of_include_all_return_system_attributes_except();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qlist_of_include_all_return_system_attributes_except,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  list_of_include_all_return_system_attributes_except = 
			  result_of_read;
		POP_SPECIAL();
	    }
	    else
		list_of_include_all_return_system_attributes_except = 
			read_icp_list_of_include_all_return_system_attributes_except();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qlist_of_return_kinds,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_list_of_return_kinds();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qlist_of_return_kinds,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  list_of_return_kinds = result_of_read;
		POP_SPECIAL();
	    }
	    else
		list_of_return_kinds = read_icp_list_of_return_kinds();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qremote_procedure_varargs_p,string_constant_2,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_remote_procedure_varargs_p();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qremote_procedure_varargs_p,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  remote_procedure_varargs_p = result_of_read;
		POP_SPECIAL();
	    }
	    else
		remote_procedure_varargs_p = 
			read_icp_remote_procedure_varargs_p();
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_define_remote_procedure_identifier__body(corresponding_icp_object_index,
		      remote_procedure_identifier_tag,
		      list_of_included_return_attributes,
		      list_of_excluded_return_attributes,
		      list_of_included_return_system_attributes,
		      list_of_include_all_return_system_attributes,
		      list_of_include_all_return_system_attributes_except,
		      list_of_return_kinds,remote_procedure_varargs_p);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_define_remote_procedure_identifier,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qhandle_icp_define_remote_procedure_identifier,top,
			Nil);
		goto end_handle_icp_define_remote_procedure_identifier;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qdefine_remote_procedure_identifier,
			string_constant_1,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  corresponding_icp_object_index = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_unsigned_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_define_remote_procedure_identifier;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    corresponding_icp_object_index = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_remote_procedure_identifier;
		  }
		  corresponding_icp_object_index = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  remote_procedure_identifier_tag = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qremote_procedure_identifier_tag,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_unsigned_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(corresponding_icp_object_index);
			resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_define_remote_procedure_identifier;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qremote_procedure_identifier_tag,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    remote_procedure_identifier_tag = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_remote_procedure_identifier;
		  }
		  remote_procedure_identifier_tag = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  list_of_included_return_attributes = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qlist_of_included_return_attributes,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_list_of_included_return_attributes();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(remote_procedure_identifier_tag);
			resumable_icp_push(corresponding_icp_object_index);
			resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_define_remote_procedure_identifier;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qlist_of_included_return_attributes,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    list_of_included_return_attributes = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_list_of_included_return_attributes();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(remote_procedure_identifier_tag);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_remote_procedure_identifier;
		  }
		  list_of_included_return_attributes = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  list_of_excluded_return_attributes = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qlist_of_excluded_return_attributes,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_list_of_excluded_return_attributes();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(list_of_included_return_attributes);
			resumable_icp_push(remote_procedure_identifier_tag);
			resumable_icp_push(corresponding_icp_object_index);
			resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_define_remote_procedure_identifier;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qlist_of_excluded_return_attributes,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    list_of_excluded_return_attributes = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_list_of_excluded_return_attributes();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(list_of_included_return_attributes);
		      resumable_icp_push(remote_procedure_identifier_tag);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_remote_procedure_identifier;
		  }
		  list_of_excluded_return_attributes = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  list_of_included_return_system_attributes = 
			  resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qlist_of_included_return_system_attributes,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = 
			    read_icp_list_of_included_return_system_attributes();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(list_of_excluded_return_attributes);
			resumable_icp_push(list_of_included_return_attributes);
			resumable_icp_push(remote_procedure_identifier_tag);
			resumable_icp_push(corresponding_icp_object_index);
			resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_define_remote_procedure_identifier;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qlist_of_included_return_system_attributes,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    list_of_included_return_system_attributes = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_list_of_included_return_system_attributes();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(list_of_excluded_return_attributes);
		      resumable_icp_push(list_of_included_return_attributes);
		      resumable_icp_push(remote_procedure_identifier_tag);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_remote_procedure_identifier;
		  }
		  list_of_included_return_system_attributes = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  list_of_include_all_return_system_attributes = 
			  resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qlist_of_include_all_return_system_attributes,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = 
			    read_icp_list_of_include_all_return_system_attributes();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(list_of_included_return_system_attributes);
			resumable_icp_push(list_of_excluded_return_attributes);
			resumable_icp_push(list_of_included_return_attributes);
			resumable_icp_push(remote_procedure_identifier_tag);
			resumable_icp_push(corresponding_icp_object_index);
			resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_define_remote_procedure_identifier;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qlist_of_include_all_return_system_attributes,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    list_of_include_all_return_system_attributes = 
			    result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = 
			  read_icp_list_of_include_all_return_system_attributes();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(list_of_included_return_system_attributes);
		      resumable_icp_push(list_of_excluded_return_attributes);
		      resumable_icp_push(list_of_included_return_attributes);
		      resumable_icp_push(remote_procedure_identifier_tag);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_remote_procedure_identifier;
		  }
		  list_of_include_all_return_system_attributes = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  list_of_include_all_return_system_attributes_except = 
			  resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qlist_of_include_all_return_system_attributes_except,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = 
			    read_icp_list_of_include_all_return_system_attributes_except();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(list_of_include_all_return_system_attributes);
			resumable_icp_push(list_of_included_return_system_attributes);
			resumable_icp_push(list_of_excluded_return_attributes);
			resumable_icp_push(list_of_included_return_attributes);
			resumable_icp_push(remote_procedure_identifier_tag);
			resumable_icp_push(corresponding_icp_object_index);
			resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_define_remote_procedure_identifier;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qlist_of_include_all_return_system_attributes_except,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    list_of_include_all_return_system_attributes_except = 
			    result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = 
			  read_icp_list_of_include_all_return_system_attributes_except();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(list_of_include_all_return_system_attributes);
		      resumable_icp_push(list_of_included_return_system_attributes);
		      resumable_icp_push(list_of_excluded_return_attributes);
		      resumable_icp_push(list_of_included_return_attributes);
		      resumable_icp_push(remote_procedure_identifier_tag);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_remote_procedure_identifier;
		  }
		  list_of_include_all_return_system_attributes_except = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  list_of_return_kinds = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qlist_of_return_kinds,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_list_of_return_kinds();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(list_of_include_all_return_system_attributes_except);
			resumable_icp_push(list_of_include_all_return_system_attributes);
			resumable_icp_push(list_of_included_return_system_attributes);
			resumable_icp_push(list_of_excluded_return_attributes);
			resumable_icp_push(list_of_included_return_attributes);
			resumable_icp_push(remote_procedure_identifier_tag);
			resumable_icp_push(corresponding_icp_object_index);
			resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_define_remote_procedure_identifier;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qlist_of_return_kinds,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    list_of_return_kinds = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_list_of_return_kinds();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(list_of_include_all_return_system_attributes_except);
		      resumable_icp_push(list_of_include_all_return_system_attributes);
		      resumable_icp_push(list_of_included_return_system_attributes);
		      resumable_icp_push(list_of_excluded_return_attributes);
		      resumable_icp_push(list_of_included_return_attributes);
		      resumable_icp_push(remote_procedure_identifier_tag);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_remote_procedure_identifier;
		  }
		  list_of_return_kinds = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  remote_procedure_varargs_p = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qremote_procedure_varargs_p,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_remote_procedure_varargs_p();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(list_of_return_kinds);
			resumable_icp_push(list_of_include_all_return_system_attributes_except);
			resumable_icp_push(list_of_include_all_return_system_attributes);
			resumable_icp_push(list_of_included_return_system_attributes);
			resumable_icp_push(list_of_excluded_return_attributes);
			resumable_icp_push(list_of_included_return_attributes);
			resumable_icp_push(remote_procedure_identifier_tag);
			resumable_icp_push(corresponding_icp_object_index);
			resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_define_remote_procedure_identifier;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qremote_procedure_varargs_p,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    remote_procedure_varargs_p = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_remote_procedure_varargs_p();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(list_of_return_kinds);
		      resumable_icp_push(list_of_include_all_return_system_attributes_except);
		      resumable_icp_push(list_of_include_all_return_system_attributes);
		      resumable_icp_push(list_of_included_return_system_attributes);
		      resumable_icp_push(list_of_excluded_return_attributes);
		      resumable_icp_push(list_of_included_return_attributes);
		      resumable_icp_push(remote_procedure_identifier_tag);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_remote_procedure_identifier;
		  }
		  remote_procedure_varargs_p = value;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_define_remote_procedure_identifier__body(corresponding_icp_object_index,
			remote_procedure_identifier_tag,
			list_of_included_return_attributes,
			list_of_excluded_return_attributes,
			list_of_included_return_system_attributes,
			list_of_include_all_return_system_attributes,
			list_of_include_all_return_system_attributes_except,
			list_of_return_kinds,remote_procedure_varargs_p);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qdefine_remote_procedure_identifier,
			  string_constant_1,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		corresponding_icp_object_index = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qcorresponding_icp_object_index,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_remote_procedure_identifier;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  corresponding_icp_object_index = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_define_remote_procedure_identifier;
		}
		corresponding_icp_object_index = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		remote_procedure_identifier_tag = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qremote_procedure_identifier_tag,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_remote_procedure_identifier;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qremote_procedure_identifier_tag,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  remote_procedure_identifier_tag = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(corresponding_icp_object_index);
		    resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_define_remote_procedure_identifier;
		}
		remote_procedure_identifier_tag = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		list_of_included_return_attributes = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qlist_of_included_return_attributes,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_list_of_included_return_attributes();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(remote_procedure_identifier_tag);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_remote_procedure_identifier;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qlist_of_included_return_attributes,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  list_of_included_return_attributes = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_list_of_included_return_attributes();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(remote_procedure_identifier_tag);
		    resumable_icp_push(corresponding_icp_object_index);
		    resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_define_remote_procedure_identifier;
		}
		list_of_included_return_attributes = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		list_of_excluded_return_attributes = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qlist_of_excluded_return_attributes,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_list_of_excluded_return_attributes();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(list_of_included_return_attributes);
		      resumable_icp_push(remote_procedure_identifier_tag);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_remote_procedure_identifier;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qlist_of_excluded_return_attributes,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  list_of_excluded_return_attributes = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_list_of_excluded_return_attributes();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(list_of_included_return_attributes);
		    resumable_icp_push(remote_procedure_identifier_tag);
		    resumable_icp_push(corresponding_icp_object_index);
		    resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_define_remote_procedure_identifier;
		}
		list_of_excluded_return_attributes = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		list_of_included_return_system_attributes = 
			resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qlist_of_included_return_system_attributes,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_list_of_included_return_system_attributes();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(list_of_excluded_return_attributes);
		      resumable_icp_push(list_of_included_return_attributes);
		      resumable_icp_push(remote_procedure_identifier_tag);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_remote_procedure_identifier;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qlist_of_included_return_system_attributes,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  list_of_included_return_system_attributes = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_list_of_included_return_system_attributes();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(list_of_excluded_return_attributes);
		    resumable_icp_push(list_of_included_return_attributes);
		    resumable_icp_push(remote_procedure_identifier_tag);
		    resumable_icp_push(corresponding_icp_object_index);
		    resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_define_remote_procedure_identifier;
		}
		list_of_included_return_system_attributes = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		list_of_include_all_return_system_attributes = 
			resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qlist_of_include_all_return_system_attributes,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = 
			  read_icp_list_of_include_all_return_system_attributes();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(list_of_included_return_system_attributes);
		      resumable_icp_push(list_of_excluded_return_attributes);
		      resumable_icp_push(list_of_included_return_attributes);
		      resumable_icp_push(remote_procedure_identifier_tag);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_remote_procedure_identifier;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qlist_of_include_all_return_system_attributes,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  list_of_include_all_return_system_attributes = 
			  result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = 
			read_icp_list_of_include_all_return_system_attributes();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(list_of_included_return_system_attributes);
		    resumable_icp_push(list_of_excluded_return_attributes);
		    resumable_icp_push(list_of_included_return_attributes);
		    resumable_icp_push(remote_procedure_identifier_tag);
		    resumable_icp_push(corresponding_icp_object_index);
		    resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_define_remote_procedure_identifier;
		}
		list_of_include_all_return_system_attributes = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		list_of_include_all_return_system_attributes_except = 
			resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qlist_of_include_all_return_system_attributes_except,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = 
			  read_icp_list_of_include_all_return_system_attributes_except();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(list_of_include_all_return_system_attributes);
		      resumable_icp_push(list_of_included_return_system_attributes);
		      resumable_icp_push(list_of_excluded_return_attributes);
		      resumable_icp_push(list_of_included_return_attributes);
		      resumable_icp_push(remote_procedure_identifier_tag);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_remote_procedure_identifier;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qlist_of_include_all_return_system_attributes_except,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  list_of_include_all_return_system_attributes_except = 
			  result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = 
			read_icp_list_of_include_all_return_system_attributes_except();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(list_of_include_all_return_system_attributes);
		    resumable_icp_push(list_of_included_return_system_attributes);
		    resumable_icp_push(list_of_excluded_return_attributes);
		    resumable_icp_push(list_of_included_return_attributes);
		    resumable_icp_push(remote_procedure_identifier_tag);
		    resumable_icp_push(corresponding_icp_object_index);
		    resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_define_remote_procedure_identifier;
		}
		list_of_include_all_return_system_attributes_except = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		list_of_return_kinds = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qlist_of_return_kinds,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_list_of_return_kinds();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(list_of_include_all_return_system_attributes_except);
		      resumable_icp_push(list_of_include_all_return_system_attributes);
		      resumable_icp_push(list_of_included_return_system_attributes);
		      resumable_icp_push(list_of_excluded_return_attributes);
		      resumable_icp_push(list_of_included_return_attributes);
		      resumable_icp_push(remote_procedure_identifier_tag);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_remote_procedure_identifier;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qlist_of_return_kinds,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  list_of_return_kinds = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_list_of_return_kinds();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(list_of_include_all_return_system_attributes_except);
		    resumable_icp_push(list_of_include_all_return_system_attributes);
		    resumable_icp_push(list_of_included_return_system_attributes);
		    resumable_icp_push(list_of_excluded_return_attributes);
		    resumable_icp_push(list_of_included_return_attributes);
		    resumable_icp_push(remote_procedure_identifier_tag);
		    resumable_icp_push(corresponding_icp_object_index);
		    resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_define_remote_procedure_identifier;
		}
		list_of_return_kinds = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		remote_procedure_varargs_p = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qremote_procedure_varargs_p,string_constant_2,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_remote_procedure_varargs_p();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(list_of_return_kinds);
		      resumable_icp_push(list_of_include_all_return_system_attributes_except);
		      resumable_icp_push(list_of_include_all_return_system_attributes);
		      resumable_icp_push(list_of_included_return_system_attributes);
		      resumable_icp_push(list_of_excluded_return_attributes);
		      resumable_icp_push(list_of_included_return_attributes);
		      resumable_icp_push(remote_procedure_identifier_tag);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_remote_procedure_identifier;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qremote_procedure_varargs_p,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  remote_procedure_varargs_p = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_remote_procedure_varargs_p();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(list_of_return_kinds);
		    resumable_icp_push(list_of_include_all_return_system_attributes_except);
		    resumable_icp_push(list_of_include_all_return_system_attributes);
		    resumable_icp_push(list_of_included_return_system_attributes);
		    resumable_icp_push(list_of_excluded_return_attributes);
		    resumable_icp_push(list_of_included_return_attributes);
		    resumable_icp_push(remote_procedure_identifier_tag);
		    resumable_icp_push(corresponding_icp_object_index);
		    resumable_icp_push(Qhandle_icp_define_remote_procedure_identifier);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_define_remote_procedure_identifier;
		}
		remote_procedure_varargs_p = value;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_define_remote_procedure_identifier__body(corresponding_icp_object_index,
		      remote_procedure_identifier_tag,
		      list_of_included_return_attributes,
		      list_of_excluded_return_attributes,
		      list_of_included_return_system_attributes,
		      list_of_include_all_return_system_attributes,
		      list_of_include_all_return_system_attributes_except,
		      list_of_return_kinds,remote_procedure_varargs_p);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_define_remote_procedure_identifier:
    return result;
}

/* RECLAIM-RPC-ARGUMENT-LIST */
Object reclaim_rpc_argument_list(list_1,do_not_reclaim_arguments)
    Object list_1, do_not_reclaim_arguments;
{
    Object value, ab_loop_list_;

    x_note_fn_call(157,96);
    if (list_1) {
	if ( !TRUEP(do_not_reclaim_arguments)) {
	    value = Nil;
	    ab_loop_list_ = list_1;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    value = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !(FIXNUMP(value) || SYMBOLP(value) || SIMPLE_VECTOR_P(value)))
		reclaim_if_evaluation_value_1(value);
	    goto next_loop;
	  end_loop:;
	}
	reclaim_eval_list_1(list_1);
    }
    return VALUES_1(Nil);
}

static Object Qhandle;             /* handle */

static Object Qvalue;              /* value */

static Object Qreference;          /* reference */

static Object Qcopy;               /* copy */

static Object Qby_copy_with_handle;  /* by-copy-with-handle */

/* RECLAIM-TRANSFORMED-RPC-ARGUMENT-LIST */
Object reclaim_transformed_rpc_argument_list(list_1,do_not_reclaim_arguments)
    Object list_1, do_not_reclaim_arguments;
{
    Object value, ab_loop_list_, argument, temp;

    x_note_fn_call(157,97);
    if (list_1) {
	value = Nil;
	ab_loop_list_ = list_1;
	argument = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	value = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (CONSP(value)) {
	    temp = CAR(value);
	    if (EQ(temp,Qhandle) || EQ(temp,Qvalue) || EQ(temp,Qreference)) {
		temp = CDR(value);
		reclaim_icp_cons_1(value);
		argument = temp;
	    }
	    else if (EQ(temp,Qcopy) || EQ(temp,Qby_copy_with_handle)) {
		temp = CADR(value);
		reclaim_icp_list_1(value);
		argument = temp;
	    }
	    else
		argument = value;
	}
	else
	    argument = value;
	if ( !TRUEP(do_not_reclaim_arguments)) {
	    if ( !(FIXNUMP(argument) || SYMBOLP(argument) || 
		    SIMPLE_VECTOR_P(argument)))
		reclaim_if_evaluation_value_1(argument);
	}
	goto next_loop;
      end_loop:;
	reclaim_eval_list_1(list_1);
    }
    return VALUES_1(Nil);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* RECLAIM-UNPROCESSED-RPC-ARGUMENT-LIST */
Object reclaim_unprocessed_rpc_argument_list varargs_1(int, n)
{
    Object list_1, initial_rpc_frame_serial_number;
    Object nargs_to_skip_qm, value, ab_loop_list_, x2, x, y, xa, ya;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(157,98);
    INIT_ARGS_nonrelocating();
    list_1 = REQUIRED_ARG_nonrelocating();
    initial_rpc_frame_serial_number = REQUIRED_ARG_nonrelocating();
    nargs_to_skip_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (list_1) {
	value = Nil;
	ab_loop_list_ = nargs_to_skip_qm ? nthcdr(nargs_to_skip_qm,list_1) 
		: list_1;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	value = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (SIMPLE_VECTOR_P(value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > (SI_Long)2L &&  
		!EQ(ISVREF(value,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    if ((SI_Long)0L != (IFIX(ISVREF(value,(SI_Long)5L)) & 
		    (SI_Long)262144L)) {
		x = initial_rpc_frame_serial_number;
		y = ISVREF(value,(SI_Long)3L);
		if (FIXNUMP(x))
		    temp = FIXNUMP(y) ? FIXNUM_LT(x,y) : TRUEP(T);
		else if (FIXNUMP(y))
		    temp = TRUEP(Nil);
		else {
		    xa = M_CAR(x);
		    ya = M_CAR(y);
		    temp = FIXNUM_LT(xa,ya);
		    if (temp);
		    else
			temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(x),
				M_CDR(y)) : TRUEP(Qnil);
		}
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		delete_frame(value);
	}
	else if ( !(FIXNUMP(value) || SYMBOLP(value) || 
		SIMPLE_VECTOR_P(value)))
	    reclaim_if_evaluation_value_1(value);
	goto next_loop;
      end_loop:;
	return reclaim_eval_list_1(list_1);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Write_remote_value_items_kind, Qwrite_remote_value_items_kind);

DEFINE_VARIABLE_WITH_SYMBOL(Gsi_remote_value_creates_instance_p, Qgsi_remote_value_creates_instance_p);

DEFINE_VARIABLE_WITH_SYMBOL(Gsi_remote_value_conses_logical_p, Qgsi_remote_value_conses_logical_p);

DEFINE_VARIABLE_WITH_SYMBOL(Write_value_of_gsi_item_p, Qwrite_value_of_gsi_item_p);

DEFINE_VARIABLE_WITH_SYMBOL(Remote_value_is_binary_p, Qremote_value_is_binary_p);

DEFINE_VARIABLE_WITH_SYMBOL(Remote_value_known_typetag, Qremote_value_known_typetag);

static Object Qlong;               /* long */

static Object Qtruth_value;        /* truth-value */

static Object Qtext;               /* text */

static Object Qunsigned_short_vector;  /* unsigned-short-vector */

static Object Qab_structure;       /* structure */

static Object Qunsigned_vector_16;  /* unsigned-vector-16 */

static Object Qitem;               /* item */

static Object Qwrite_icp_remote_value_1;  /* write-icp-remote-value-1 */

static Object Qtrue;               /* true */

static Object Qfalse;              /* false */

/* WRITE-ICP-REMOTE-VALUE-1 */
Object write_icp_remote_value_1(remote_value_1)
    Object remote_value_1;
{
    Object temp, typecode, cdr_1, thing, value, result_1, temp_2;
    Object resumable_icp_state_1, icp_suspend_1, top, test, value_1;
    SI_Long length_1;
    char temp_1;

    x_note_fn_call(157,99);
    if (Disable_resumability) {
	if (Remote_value_known_typetag) {
	    temp = Remote_value_known_typetag;
	    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		    FIX((SI_Long)127L))))
		typecode = Nil;
	    else
		switch (INTEGER_TO_CHAR(temp)) {
		  case 0:
		    typecode = Qnull;
		    break;
		  case 1:
		    typecode = Qinteger;
		    break;
		  case 51:
		    typecode = Qlong;
		    break;
		  case 5:
		    typecode = Qtruth_value;
		    break;
		  case 6:
		    typecode = Qfloat;
		    break;
		  case 4:
		    typecode = Qtext;
		    break;
		  case 11:
		    typecode = Qunsigned_short_vector;
		    break;
		  default:
		    typecode = Nil;
		    break;
		}
	}
	else if (Remote_value_is_binary_p)
	    typecode = Qunsigned_short_vector;
	else if ( !TRUEP(remote_value_1))
	    typecode = Qnull;
	else if (FIXNUMP(remote_value_1))
	    typecode = Qinteger;
	else if (INLINE_LONG_VECTOR_P(remote_value_1) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(remote_value_1)) == (SI_Long)1L)
	    typecode = Qlong;
	else if (CONSP(remote_value_1)) {
	    cdr_1 = M_CDR(remote_value_1);
	    if (EQ(cdr_1,Qtruth_value))
		typecode = Qtruth_value;
	    else if (EQ(cdr_1,Qsequence))
		typecode = Qsequence;
	    else if (EQ(cdr_1,Qab_structure))
		typecode = Qab_structure;
	    else if (EQ(cdr_1,Qunsigned_vector_16))
		typecode = Qunsigned_short_vector;
	    else
		typecode = Qnull;
	}
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(remote_value_1) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(remote_value_1)) == (SI_Long)1L)
	    typecode = Qfloat;
	else if (remote_value_1 && SYMBOLP(remote_value_1))
	    typecode = Qsymbol;
	else {
	    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(remote_value_1) != 
		    (SI_Long)0L) {
		length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(remote_value_1));
		temp_1 = (SI_Long)1L == UBYTE_16_ISAREF_1(remote_value_1,
			UBYTE_16_ISAREF_1(remote_value_1,length_1 - 
			(SI_Long)2L) + ((UBYTE_16_ISAREF_1(remote_value_1,
			length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			(SI_Long)16L));
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		typecode = Qunsigned_short_vector;
	    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(remote_value_1) != 
		    (SI_Long)0L)
		typecode = Qtext;
	    else {
		if (SIMPLE_VECTOR_P(remote_value_1) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(remote_value_1)) > 
			(SI_Long)2L) {
		    temp_1 = EQ(ISVREF(remote_value_1,(SI_Long)1L),
			    Qavailable_frame_vector);
		    if (temp_1);
		    else {
			thing = ISVREF(remote_value_1,(SI_Long)1L);
			temp_1 = SIMPLE_VECTOR_P(thing) ? EQ(ISVREF(thing,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				: TRUEP(Qnil);
		    }
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1)
		    typecode = Qitem;
		else if (SIMPLE_VECTOR_P(remote_value_1) && 
			EQ(ISVREF(remote_value_1,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct))
		    typecode = Qitem;
		else
		    typecode = Qnull;
	    }
	}
	if (EQ(typecode,Qnull)) {
	    value = remote_value_1;
	    result_1 = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)8L ? ( !TRUEP(Remote_value_known_typetag) ? 
		    write_icp_byte(FIX((SI_Long)0L)) : Nil) : 
		    write_icp_byte(FIX((SI_Long)0L));
	    temp = result_1;
	}
	else if (EQ(typecode,Qinteger)) {
	    value = remote_value_1;
	    if (IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= (SI_Long)8L) {
		if ( !TRUEP(Remote_value_known_typetag))
		    write_icp_byte(FIX((SI_Long)1L));
	    }
	    else
		write_icp_byte(FIX((SI_Long)1L));
	    result_1 = write_icp_integer(value);
	    temp = result_1;
	}
	else if (EQ(typecode,Qlong)) {
	    value = remote_value_1;
	    temp = ISVREF(Current_icp_socket,(SI_Long)21L);
	    temp_2 = ISVREF(Current_icp_socket,(SI_Long)22L);
	    if (IFIX(FIXNUM_MIN(temp,temp_2)) >= (SI_Long)30L) {
		if (IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
			(SI_Long)8L) {
		    if ( !TRUEP(Remote_value_known_typetag))
			write_icp_byte(FIX((SI_Long)51L));
		}
		else
		    write_icp_byte(FIX((SI_Long)51L));
		result_1 = write_icp_managed_long(value);
	    }
	    else
		result_1 = Nil;
	    temp = result_1;
	}
	else if (EQ(typecode,Qtruth_value)) {
	    value = M_CAR(remote_value_1);
	    if (IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= (SI_Long)8L) {
		if ( !TRUEP(Remote_value_known_typetag))
		    write_icp_byte(FIX((SI_Long)5L));
	    }
	    else
		write_icp_byte(FIX((SI_Long)5L));
	    result_1 = write_icp_integer(value);
	    temp = result_1;
	}
	else if (EQ(typecode,Qfloat)) {
	    value = remote_value_1;
	    if (IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= (SI_Long)2L) {
		if (IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
			(SI_Long)8L) {
		    if ( !TRUEP(Remote_value_known_typetag))
			write_icp_byte(FIX((SI_Long)6L));
		}
		else
		    write_icp_byte(FIX((SI_Long)6L));
		result_1 = write_icp_managed_double_float(value);
	    }
	    else {
		write_icp_byte(FIX((SI_Long)2L));
		result_1 = write_icp_float(value);
	    }
	    temp = result_1;
	}
	else if (EQ(typecode,Qsymbol)) {
	    value = remote_value_1;
	    result_1 = write_icp_symbol_as_value_type(value);
	    temp = result_1;
	}
	else if (EQ(typecode,Qtext)) {
	    value = remote_value_1;
	    if (IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= (SI_Long)8L) {
		if ( !TRUEP(Remote_value_known_typetag))
		    write_icp_byte(FIX((SI_Long)4L));
	    }
	    else
		write_icp_byte(FIX((SI_Long)4L));
	    result_1 = write_icp_text_string(value);
	    temp = result_1;
	}
	else if (EQ(typecode,Qunsigned_short_vector)) {
	    value = CONSP(remote_value_1) ? M_CAR(remote_value_1) : 
		    remote_value_1;
	    if (IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
			(SI_Long)14L) {
		if (IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
			(SI_Long)8L) {
		    if ( !TRUEP(Remote_value_known_typetag))
			write_icp_byte(FIX((SI_Long)11L));
		}
		else
		    write_icp_byte(FIX((SI_Long)11L));
		result_1 = write_icp_wide_string(value);
	    }
	    else {
		if (IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
			(SI_Long)8L) {
		    if ( !TRUEP(Remote_value_known_typetag))
			write_icp_byte(FIX((SI_Long)4L));
		}
		else
		    write_icp_byte(FIX((SI_Long)4L));
		result_1 = write_icp_text_string(value);
	    }
	    temp = result_1;
	}
	else if (EQ(typecode,Qhandle)) {
	    value = remote_value_1;
	    if (IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= (SI_Long)8L) {
		if ( !TRUEP(Remote_value_known_typetag))
		    write_icp_byte(FIX((SI_Long)8L));
	    }
	    else
		write_icp_byte(FIX((SI_Long)8L));
	    result_1 = write_icp_fixnum(value);
	    temp = result_1;
	}
	else if (EQ(typecode,Qab_structure)) {
	    value = remote_value_1;
	    if (IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= (SI_Long)8L) {
		if (IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
			(SI_Long)8L) {
		    if ( !TRUEP(Remote_value_known_typetag))
			write_icp_byte(FIX((SI_Long)50L));
		}
		else
		    write_icp_byte(FIX((SI_Long)50L));
		result_1 = write_icp_evaluation_structure(value);
	    }
	    else
		result_1 = write_icp_byte(FIX((SI_Long)0L));
	    temp = result_1;
	}
	else if (EQ(typecode,Qsequence)) {
	    value = remote_value_1;
	    result_1 = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)8L ? write_icp_evaluation_sequence(value) : 
		    write_icp_byte(FIX((SI_Long)0L));
	    temp = result_1;
	}
	else if (EQ(typecode,Qitem)) {
	    value = remote_value_1;
	    result_1 = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)8L ? write_icp_item(value) : 
		    write_icp_byte(FIX((SI_Long)0L));
	    temp = result_1;
	}
	else
	    temp = write_icp_byte(FIX((SI_Long)0L));
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qwrite_icp_remote_value_1,top))
		return icp_error_internal(Qerror,string_constant,
			Qwrite_icp_remote_value_1,top,Nil);
	}
	remote_value_1 = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : remote_value_1;
	if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  !TRUEP(resumable_icp_pop_list_if_end_marker()))
	    typecode = resumable_icp_pop();
	else if (Remote_value_known_typetag) {
	    temp = Remote_value_known_typetag;
	    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		    FIX((SI_Long)127L))))
		typecode = Nil;
	    else
		switch (INTEGER_TO_CHAR(temp)) {
		  case 0:
		    typecode = Qnull;
		    break;
		  case 1:
		    typecode = Qinteger;
		    break;
		  case 51:
		    typecode = Qlong;
		    break;
		  case 5:
		    typecode = Qtruth_value;
		    break;
		  case 6:
		    typecode = Qfloat;
		    break;
		  case 4:
		    typecode = Qtext;
		    break;
		  case 11:
		    typecode = Qunsigned_short_vector;
		    break;
		  default:
		    typecode = Nil;
		    break;
		}
	}
	else if (Remote_value_is_binary_p)
	    typecode = Qunsigned_short_vector;
	else if ( !TRUEP(remote_value_1))
	    typecode = Qnull;
	else if (FIXNUMP(remote_value_1))
	    typecode = Qinteger;
	else if (INLINE_LONG_VECTOR_P(remote_value_1) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(remote_value_1)) == (SI_Long)1L)
	    typecode = Qlong;
	else if (CONSP(remote_value_1)) {
	    cdr_1 = M_CDR(remote_value_1);
	    if (EQ(cdr_1,Qtruth_value))
		typecode = Qtruth_value;
	    else if (EQ(cdr_1,Qsequence))
		typecode = Qsequence;
	    else if (EQ(cdr_1,Qab_structure))
		typecode = Qab_structure;
	    else if (EQ(cdr_1,Qunsigned_vector_16))
		typecode = Qunsigned_short_vector;
	    else
		typecode = Qnull;
	}
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(remote_value_1) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(remote_value_1)) == (SI_Long)1L)
	    typecode = Qfloat;
	else if (remote_value_1 && SYMBOLP(remote_value_1))
	    typecode = Qsymbol;
	else {
	    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(remote_value_1) != 
		    (SI_Long)0L) {
		length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(remote_value_1));
		temp_1 = (SI_Long)1L == UBYTE_16_ISAREF_1(remote_value_1,
			UBYTE_16_ISAREF_1(remote_value_1,length_1 - 
			(SI_Long)2L) + ((UBYTE_16_ISAREF_1(remote_value_1,
			length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			(SI_Long)16L));
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		typecode = Qunsigned_short_vector;
	    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(remote_value_1) != 
		    (SI_Long)0L)
		typecode = Qtext;
	    else {
		if (SIMPLE_VECTOR_P(remote_value_1) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(remote_value_1)) > 
			(SI_Long)2L) {
		    temp_1 = EQ(ISVREF(remote_value_1,(SI_Long)1L),
			    Qavailable_frame_vector);
		    if (temp_1);
		    else {
			thing = ISVREF(remote_value_1,(SI_Long)1L);
			temp_1 = SIMPLE_VECTOR_P(thing) ? EQ(ISVREF(thing,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				: TRUEP(Qnil);
		    }
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1)
		    typecode = Qitem;
		else if (SIMPLE_VECTOR_P(remote_value_1) && 
			EQ(ISVREF(remote_value_1,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct))
		    typecode = Qitem;
		else
		    typecode = Qnull;
	    }
	}
	test = Nil;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    test = resumable_icp_pop();
	    temp_1 = TRUEP(test);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1 ? EQ(test,Qtrue) : EQ(typecode,Qnull)) {
	    value = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : remote_value_1;
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		result_1 = resumable_icp_pop();
	    else {
		test = Nil;
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    test = resumable_icp_pop();
		    temp_1 = TRUEP(test);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1 ? EQ(test,Qtrue) : 
			IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
			(SI_Long)8L) {
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) ||  
			    !TRUEP(Remote_value_known_typetag)) {
			value_1 = write_icp_byte(FIX((SI_Long)0L));
			if (EQ(icp_suspend_1,value_1)) {
			    resumable_icp_push(Qtrue);
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(value);
			    resumable_icp_push(Qtrue);
			    resumable_icp_push(typecode);
			    resumable_icp_push(remote_value_1);
			    resumable_icp_push(Qwrite_icp_remote_value_1);
			    return VALUES_1(Icp_suspend);
			}
			result_1 = value_1;
		    }
		    else
			result_1 = Nil;
		}
		else {
		    value_1 = write_icp_byte(FIX((SI_Long)0L));
		    if (EQ(icp_suspend_1,value_1)) {
			resumable_icp_push(Qfalse);
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(value);
			resumable_icp_push(Qtrue);
			resumable_icp_push(typecode);
			resumable_icp_push(remote_value_1);
			resumable_icp_push(Qwrite_icp_remote_value_1);
			return VALUES_1(Icp_suspend);
		    }
		    result_1 = value_1;
		}
	    }
	    temp = result_1;
	}
	else {
	    test = Nil;
	    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) {
		test = resumable_icp_pop();
		temp_1 = TRUEP(test);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? EQ(test,Qtrue) : EQ(typecode,Qinteger)) {
		value = (resumable_icp_state_1 ? 
			TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			resumable_icp_pop() : remote_value_1;
		if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()))
		    result_1 = resumable_icp_pop();
		else {
		    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
			    : TRUEP(Nil)) {
			temp = resumable_icp_pop();
			if (! !(FIXNUMP(temp) && 
				FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
				FIXNUM_LE(temp,FIX((SI_Long)127L))))
			    switch (INTEGER_TO_CHAR(temp)) {
			      case 1:
				goto l1;
				break;
			      case 2:
				goto l2;
				break;
			      default:
				break;
			    }
		    }
		  l1:
		    test = Nil;
		    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
			    : TRUEP(Nil)) {
			test = resumable_icp_pop();
			temp_1 = TRUEP(test);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1 ? EQ(test,Qtrue) : 
			    IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) 
			    >= (SI_Long)8L) {
			if ((resumable_icp_state_1 ? 
				TRUEP(Resumable_icp_state) : TRUEP(Nil)) 
				||  !TRUEP(Remote_value_known_typetag)) {
			    if (EQ(icp_suspend_1,
				    write_icp_byte(FIX((SI_Long)1L)))) {
				resumable_icp_push(Qtrue);
				resumable_icp_push(FIX((SI_Long)1L));
				value_1 = Icp_suspend;
				goto end_block;
			    }
			}
		    }
		    else if (EQ(icp_suspend_1,
			    write_icp_byte(FIX((SI_Long)1L)))) {
			resumable_icp_push(Qfalse);
			resumable_icp_push(FIX((SI_Long)1L));
			value_1 = Icp_suspend;
			goto end_block;
		    }
		  l2:
		    value_1 = write_icp_integer(value);
		    if (EQ(icp_suspend_1,value_1)) {
			resumable_icp_push(FIX((SI_Long)2L));
			value_1 = Icp_suspend;
			goto end_block;
		    }
		    goto end_block;
		  end_block:
		    if (EQ(icp_suspend_1,value_1)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(value);
			resumable_icp_push(Qtrue);
			resumable_icp_push(Qfalse);
			resumable_icp_push(typecode);
			resumable_icp_push(remote_value_1);
			resumable_icp_push(Qwrite_icp_remote_value_1);
			return VALUES_1(Icp_suspend);
		    }
		    result_1 = value_1;
		}
		temp = result_1;
	    }
	    else {
		test = Nil;
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    test = resumable_icp_pop();
		    temp_1 = TRUEP(test);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1 ? EQ(test,Qtrue) : EQ(typecode,Qlong)) {
		    value = (resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()) 
			    ? resumable_icp_pop() : remote_value_1;
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()))
			result_1 = resumable_icp_pop();
		    else {
			temp_1 = resumable_icp_state_1 ? 
				TRUEP(Resumable_icp_state) : TRUEP(Nil);
			if (temp_1);
			else {
			    temp_2 = ISVREF(Current_icp_socket,(SI_Long)21L);
			    temp = ISVREF(Current_icp_socket,(SI_Long)22L);
			    temp_1 = IFIX(FIXNUM_MIN(temp_2,temp)) >= 
				    (SI_Long)30L;
			}
			if (temp_1) {
			    if (resumable_icp_state_1 ? 
				    TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
				temp = resumable_icp_pop();
				if (! !(FIXNUMP(temp) && 
					FIXNUM_LE(FIX((SI_Long)-128L),
					temp) && FIXNUM_LE(temp,
					FIX((SI_Long)127L))))
				    switch (INTEGER_TO_CHAR(temp)) {
				      case 1:
					goto l1_1;
					break;
				      case 2:
					goto l2_1;
					break;
				      default:
					break;
				    }
			    }
			  l1_1:
			    test = Nil;
			    if (resumable_icp_state_1 ? 
				    TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
				test = resumable_icp_pop();
				temp_1 = TRUEP(test);
			    }
			    else
				temp_1 = TRUEP(Nil);
			    if (temp_1 ? EQ(test,Qtrue) : 
				    IFIX(ISVREF(Current_icp_socket,
				    (SI_Long)22L)) >= (SI_Long)8L) {
				if ((resumable_icp_state_1 ? 
					TRUEP(Resumable_icp_state) : 
					TRUEP(Nil)) ||  
					!TRUEP(Remote_value_known_typetag)) {
				    if (EQ(icp_suspend_1,
					    write_icp_byte(FIX((SI_Long)51L)))) 
						{
					resumable_icp_push(Qtrue);
					resumable_icp_push(FIX((SI_Long)1L));
					value_1 = Icp_suspend;
					goto end_block_1;
				    }
				}
			    }
			    else if (EQ(icp_suspend_1,
				    write_icp_byte(FIX((SI_Long)51L)))) {
				resumable_icp_push(Qfalse);
				resumable_icp_push(FIX((SI_Long)1L));
				value_1 = Icp_suspend;
				goto end_block_1;
			    }
			  l2_1:
			    value_1 = write_icp_managed_long(value);
			    if (EQ(icp_suspend_1,value_1)) {
				resumable_icp_push(FIX((SI_Long)2L));
				value_1 = Icp_suspend;
				goto end_block_1;
			    }
			    goto end_block_1;
			  end_block_1:
			    if (EQ(icp_suspend_1,value_1)) {
				resumable_icp_push(Qresumable_icp_list_end);
				resumable_icp_push(value);
				resumable_icp_push(Qtrue);
				resumable_icp_push(Qfalse);
				resumable_icp_push(Qfalse);
				resumable_icp_push(typecode);
				resumable_icp_push(remote_value_1);
				resumable_icp_push(Qwrite_icp_remote_value_1);
				return VALUES_1(Icp_suspend);
			    }
			    result_1 = value_1;
			}
			else
			    result_1 = Nil;
		    }
		    temp = result_1;
		}
		else {
		    test = Nil;
		    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
			    : TRUEP(Nil)) {
			test = resumable_icp_pop();
			temp_1 = TRUEP(test);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1 ? EQ(test,Qtrue) : EQ(typecode,Qtruth_value)) {
			value = (resumable_icp_state_1 ? 
				TRUEP(Resumable_icp_state) : TRUEP(Nil)) 
				&&  
				!TRUEP(resumable_icp_pop_list_if_end_marker()) 
				? resumable_icp_pop() : M_CAR(remote_value_1);
			if ((resumable_icp_state_1 ? 
				TRUEP(Resumable_icp_state) : TRUEP(Nil)) 
				&&  
				!TRUEP(resumable_icp_pop_list_if_end_marker()))
			    result_1 = resumable_icp_pop();
			else {
			    if (resumable_icp_state_1 ? 
				    TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
				temp = resumable_icp_pop();
				if (! !(FIXNUMP(temp) && 
					FIXNUM_LE(FIX((SI_Long)-128L),
					temp) && FIXNUM_LE(temp,
					FIX((SI_Long)127L))))
				    switch (INTEGER_TO_CHAR(temp)) {
				      case 1:
					goto l1_2;
					break;
				      case 2:
					goto l2_2;
					break;
				      default:
					break;
				    }
			    }
			  l1_2:
			    test = Nil;
			    if (resumable_icp_state_1 ? 
				    TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
				test = resumable_icp_pop();
				temp_1 = TRUEP(test);
			    }
			    else
				temp_1 = TRUEP(Nil);
			    if (temp_1 ? EQ(test,Qtrue) : 
				    IFIX(ISVREF(Current_icp_socket,
				    (SI_Long)22L)) >= (SI_Long)8L) {
				if ((resumable_icp_state_1 ? 
					TRUEP(Resumable_icp_state) : 
					TRUEP(Nil)) ||  
					!TRUEP(Remote_value_known_typetag)) {
				    if (EQ(icp_suspend_1,
					    write_icp_byte(FIX((SI_Long)5L)))) 
						{
					resumable_icp_push(Qtrue);
					resumable_icp_push(FIX((SI_Long)1L));
					value_1 = Icp_suspend;
					goto end_block_2;
				    }
				}
			    }
			    else if (EQ(icp_suspend_1,
				    write_icp_byte(FIX((SI_Long)5L)))) {
				resumable_icp_push(Qfalse);
				resumable_icp_push(FIX((SI_Long)1L));
				value_1 = Icp_suspend;
				goto end_block_2;
			    }
			  l2_2:
			    value_1 = write_icp_integer(value);
			    if (EQ(icp_suspend_1,value_1)) {
				resumable_icp_push(FIX((SI_Long)2L));
				value_1 = Icp_suspend;
				goto end_block_2;
			    }
			    goto end_block_2;
			  end_block_2:
			    if (EQ(icp_suspend_1,value_1)) {
				resumable_icp_push(Qresumable_icp_list_end);
				resumable_icp_push(value);
				resumable_icp_push(Qtrue);
				resumable_icp_push(Qfalse);
				resumable_icp_push(Qfalse);
				resumable_icp_push(Qfalse);
				resumable_icp_push(typecode);
				resumable_icp_push(remote_value_1);
				resumable_icp_push(Qwrite_icp_remote_value_1);
				return VALUES_1(Icp_suspend);
			    }
			    result_1 = value_1;
			}
			temp = result_1;
		    }
		    else {
			test = Nil;
			if (resumable_icp_state_1 ? 
				TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
			    test = resumable_icp_pop();
			    temp_1 = TRUEP(test);
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1 ? EQ(test,Qtrue) : EQ(typecode,Qfloat)) {
			    value = (resumable_icp_state_1 ? 
				    TRUEP(Resumable_icp_state) : 
				    TRUEP(Nil)) &&  
				    !TRUEP(resumable_icp_pop_list_if_end_marker()) 
				    ? resumable_icp_pop() : remote_value_1;
			    if ((resumable_icp_state_1 ? 
				    TRUEP(Resumable_icp_state) : 
				    TRUEP(Nil)) &&  
				    !TRUEP(resumable_icp_pop_list_if_end_marker()))
				result_1 = resumable_icp_pop();
			    else {
				test = Nil;
				if (resumable_icp_state_1 ? 
					TRUEP(Resumable_icp_state) : 
					TRUEP(Nil)) {
				    test = resumable_icp_pop();
				    temp_1 = TRUEP(test);
				}
				else
				    temp_1 = TRUEP(Nil);
				if (temp_1 ? EQ(test,Qtrue) : 
					IFIX(ISVREF(Current_icp_socket,
					(SI_Long)22L)) >= (SI_Long)2L) {
				    if (resumable_icp_state_1 ? 
					    TRUEP(Resumable_icp_state) : 
					    TRUEP(Nil)) {
					temp = resumable_icp_pop();
					if (! !(FIXNUMP(temp) && 
						FIXNUM_LE(FIX((SI_Long)-128L),
						temp) && FIXNUM_LE(temp,
						FIX((SI_Long)127L))))
					    switch (INTEGER_TO_CHAR(temp)) {
					      case 1:
						goto l1_3;
						break;
					      case 2:
						goto l2_3;
						break;
					      default:
						break;
					    }
				    }
				  l1_3:
				    test = Nil;
				    if (resumable_icp_state_1 ? 
					    TRUEP(Resumable_icp_state) : 
					    TRUEP(Nil)) {
					test = resumable_icp_pop();
					temp_1 = TRUEP(test);
				    }
				    else
					temp_1 = TRUEP(Nil);
				    if (temp_1 ? EQ(test,Qtrue) : 
					    IFIX(ISVREF(Current_icp_socket,
					    (SI_Long)22L)) >= (SI_Long)8L) {
					if ((resumable_icp_state_1 ? 
						TRUEP(Resumable_icp_state) 
						: TRUEP(Nil)) ||  
						!TRUEP(Remote_value_known_typetag)) 
						    {
					    if (EQ(icp_suspend_1,
						    write_icp_byte(FIX((SI_Long)6L)))) 
							{
						resumable_icp_push(Qtrue);
						resumable_icp_push(FIX((SI_Long)1L));
						value_1 = Icp_suspend;
						goto end_block_3;
					    }
					}
				    }
				    else if (EQ(icp_suspend_1,
					    write_icp_byte(FIX((SI_Long)6L)))) 
						{
					resumable_icp_push(Qfalse);
					resumable_icp_push(FIX((SI_Long)1L));
					value_1 = Icp_suspend;
					goto end_block_3;
				    }
				  l2_3:
				    value_1 = 
					    write_icp_managed_double_float(value);
				    if (EQ(icp_suspend_1,value_1)) {
					resumable_icp_push(FIX((SI_Long)2L));
					value_1 = Icp_suspend;
					goto end_block_3;
				    }
				    goto end_block_3;
				  end_block_3:
				    if (EQ(icp_suspend_1,value_1)) {
					resumable_icp_push(Qtrue);
					resumable_icp_push(Qresumable_icp_list_end);
					resumable_icp_push(value);
					resumable_icp_push(Qtrue);
					resumable_icp_push(Qfalse);
					resumable_icp_push(Qfalse);
					resumable_icp_push(Qfalse);
					resumable_icp_push(Qfalse);
					resumable_icp_push(typecode);
					resumable_icp_push(remote_value_1);
					resumable_icp_push(Qwrite_icp_remote_value_1);
					return VALUES_1(Icp_suspend);
				    }
				    result_1 = value_1;
				}
				else {
				    if (resumable_icp_state_1 ? 
					    TRUEP(Resumable_icp_state) : 
					    TRUEP(Nil)) {
					temp = resumable_icp_pop();
					if (! !(FIXNUMP(temp) && 
						FIXNUM_LE(FIX((SI_Long)-128L),
						temp) && FIXNUM_LE(temp,
						FIX((SI_Long)127L))))
					    switch (INTEGER_TO_CHAR(temp)) {
					      case 1:
						goto l1_4;
						break;
					      case 2:
						goto l2_4;
						break;
					      default:
						break;
					    }
				    }
				  l1_4:
				    if (EQ(icp_suspend_1,
					    write_icp_byte(FIX((SI_Long)2L)))) 
						{
					resumable_icp_push(FIX((SI_Long)1L));
					value_1 = Icp_suspend;
					goto end_block_4;
				    }
				  l2_4:
				    value_1 = write_icp_float(value);
				    if (EQ(icp_suspend_1,value_1)) {
					resumable_icp_push(FIX((SI_Long)2L));
					value_1 = Icp_suspend;
					goto end_block_4;
				    }
				    goto end_block_4;
				  end_block_4:
				    if (EQ(icp_suspend_1,value_1)) {
					resumable_icp_push(Qfalse);
					resumable_icp_push(Qresumable_icp_list_end);
					resumable_icp_push(value);
					resumable_icp_push(Qtrue);
					resumable_icp_push(Qfalse);
					resumable_icp_push(Qfalse);
					resumable_icp_push(Qfalse);
					resumable_icp_push(Qfalse);
					resumable_icp_push(typecode);
					resumable_icp_push(remote_value_1);
					resumable_icp_push(Qwrite_icp_remote_value_1);
					return VALUES_1(Icp_suspend);
				    }
				    result_1 = value_1;
				}
			    }
			    temp = result_1;
			}
			else {
			    test = Nil;
			    if (resumable_icp_state_1 ? 
				    TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
				test = resumable_icp_pop();
				temp_1 = TRUEP(test);
			    }
			    else
				temp_1 = TRUEP(Nil);
			    if (temp_1 ? EQ(test,Qtrue) : EQ(typecode,
					Qsymbol)) {
				value = (resumable_icp_state_1 ? 
					TRUEP(Resumable_icp_state) : 
					TRUEP(Nil)) &&  
					!TRUEP(resumable_icp_pop_list_if_end_marker()) 
					? resumable_icp_pop() : remote_value_1;
				if ((resumable_icp_state_1 ? 
					TRUEP(Resumable_icp_state) : 
					TRUEP(Nil)) &&  
					!TRUEP(resumable_icp_pop_list_if_end_marker()))
				    result_1 = resumable_icp_pop();
				else {
				    value_1 = 
					    write_icp_symbol_as_value_type(value);
				    if (EQ(icp_suspend_1,value_1)) {
					resumable_icp_push(Qresumable_icp_list_end);
					resumable_icp_push(value);
					resumable_icp_push(Qtrue);
					resumable_icp_push(Qfalse);
					resumable_icp_push(Qfalse);
					resumable_icp_push(Qfalse);
					resumable_icp_push(Qfalse);
					resumable_icp_push(Qfalse);
					resumable_icp_push(typecode);
					resumable_icp_push(remote_value_1);
					resumable_icp_push(Qwrite_icp_remote_value_1);
					return VALUES_1(Icp_suspend);
				    }
				    result_1 = value_1;
				}
				temp = result_1;
			    }
			    else {
				test = Nil;
				if (resumable_icp_state_1 ? 
					TRUEP(Resumable_icp_state) : 
					TRUEP(Nil)) {
				    test = resumable_icp_pop();
				    temp_1 = TRUEP(test);
				}
				else
				    temp_1 = TRUEP(Nil);
				if (temp_1 ? EQ(test,Qtrue) : EQ(typecode,
					Qtext)) {
				    value = (resumable_icp_state_1 ? 
					    TRUEP(Resumable_icp_state) : 
					    TRUEP(Nil)) &&  
					    !TRUEP(resumable_icp_pop_list_if_end_marker()) 
					    ? resumable_icp_pop() : 
					    remote_value_1;
				    if ((resumable_icp_state_1 ? 
					    TRUEP(Resumable_icp_state) : 
					    TRUEP(Nil)) &&  
					    !TRUEP(resumable_icp_pop_list_if_end_marker()))
					result_1 = resumable_icp_pop();
				    else {
					if (resumable_icp_state_1 ? 
						TRUEP(Resumable_icp_state) 
						: TRUEP(Nil)) {
					    temp = resumable_icp_pop();
					    if (! !(FIXNUMP(temp) && 
						    FIXNUM_LE(FIX((SI_Long)-128L),
						    temp) && 
						    FIXNUM_LE(temp,
						    FIX((SI_Long)127L))))
						switch (INTEGER_TO_CHAR(temp)) 
							    {
						  case 1:
						    goto l1_5;
						    break;
						  case 2:
						    goto l2_5;
						    break;
						  default:
						    break;
						}
					}
				      l1_5:
					test = Nil;
					if (resumable_icp_state_1 ? 
						TRUEP(Resumable_icp_state) 
						: TRUEP(Nil)) {
					    test = resumable_icp_pop();
					    temp_1 = TRUEP(test);
					}
					else
					    temp_1 = TRUEP(Nil);
					if (temp_1 ? EQ(test,Qtrue) : 
						IFIX(ISVREF(Current_icp_socket,
						(SI_Long)22L)) >= 
						    (SI_Long)8L) {
					    if ((resumable_icp_state_1 ? 
						    TRUEP(Resumable_icp_state) 
						    : TRUEP(Nil)) ||  
						    !TRUEP(Remote_value_known_typetag)) 
							{
						if (EQ(icp_suspend_1,
							write_icp_byte(FIX((SI_Long)4L)))) 
							    {
						    resumable_icp_push(Qtrue);
						    resumable_icp_push(FIX((SI_Long)1L));
						    value_1 = Icp_suspend;
						    goto end_block_5;
						}
					    }
					}
					else if (EQ(icp_suspend_1,
						write_icp_byte(FIX((SI_Long)4L)))) 
						    {
					    resumable_icp_push(Qfalse);
					    resumable_icp_push(FIX((SI_Long)1L));
					    value_1 = Icp_suspend;
					    goto end_block_5;
					}
				      l2_5:
					value_1 = write_icp_text_string(value);
					if (EQ(icp_suspend_1,value_1)) {
					    resumable_icp_push(FIX((SI_Long)2L));
					    value_1 = Icp_suspend;
					    goto end_block_5;
					}
					goto end_block_5;
				      end_block_5:
					if (EQ(icp_suspend_1,value_1)) {
					    resumable_icp_push(Qresumable_icp_list_end);
					    resumable_icp_push(value);
					    resumable_icp_push(Qtrue);
					    resumable_icp_push(Qfalse);
					    resumable_icp_push(Qfalse);
					    resumable_icp_push(Qfalse);
					    resumable_icp_push(Qfalse);
					    resumable_icp_push(Qfalse);
					    resumable_icp_push(Qfalse);
					    resumable_icp_push(typecode);
					    resumable_icp_push(remote_value_1);
					    resumable_icp_push(Qwrite_icp_remote_value_1);
					    return VALUES_1(Icp_suspend);
					}
					result_1 = value_1;
				    }
				    temp = result_1;
				}
				else {
				    test = Nil;
				    if (resumable_icp_state_1 ? 
					    TRUEP(Resumable_icp_state) : 
					    TRUEP(Nil)) {
					test = resumable_icp_pop();
					temp_1 = TRUEP(test);
				    }
				    else
					temp_1 = TRUEP(Nil);
				    if (temp_1 ? EQ(test,Qtrue) : 
					    EQ(typecode,
					    Qunsigned_short_vector)) {
					value = (resumable_icp_state_1 ? 
						TRUEP(Resumable_icp_state) 
						: TRUEP(Nil)) &&  
						!TRUEP(resumable_icp_pop_list_if_end_marker()) 
						? resumable_icp_pop() : 
						CONSP(remote_value_1) ? 
						M_CAR(remote_value_1) : 
						remote_value_1;
					if ((resumable_icp_state_1 ? 
						TRUEP(Resumable_icp_state) 
						: TRUEP(Nil)) &&  
						!TRUEP(resumable_icp_pop_list_if_end_marker()))
					    result_1 = resumable_icp_pop();
					else {
					    test = Nil;
					    if (resumable_icp_state_1 ? 
						    TRUEP(Resumable_icp_state) 
						    : TRUEP(Nil)) {
						test = resumable_icp_pop();
						temp_1 = TRUEP(test);
					    }
					    else
						temp_1 = TRUEP(Nil);
					    if (temp_1 ? EQ(test,Qtrue) : 
						    IFIX(ISVREF(Current_icp_socket,
						    (SI_Long)22L)) >= 
						    (SI_Long)14L) {
						if (resumable_icp_state_1 ?
							 
							TRUEP(Resumable_icp_state) 
							: TRUEP(Nil)) {
						    temp = resumable_icp_pop();
						    if (! !(FIXNUMP(temp) 
							    && 
							    FIXNUM_LE(FIX((SI_Long)-128L),
							    temp) && 
							    FIXNUM_LE(temp,
							    FIX((SI_Long)127L))))
							switch (INTEGER_TO_CHAR(temp)) 
								    {
							  case 1:
							    goto l1_6;
							    break;
							  case 2:
							    goto l2_6;
							    break;
							  default:
							    break;
							}
						}
					      l1_6:
						test = Nil;
						if (resumable_icp_state_1 ?
							 
							TRUEP(Resumable_icp_state) 
							: TRUEP(Nil)) {
						    test = resumable_icp_pop();
						    temp_1 = TRUEP(test);
						}
						else
						    temp_1 = TRUEP(Nil);
						if (temp_1 ? EQ(test,
							Qtrue) : 
							IFIX(ISVREF(Current_icp_socket,
							(SI_Long)22L)) >= 
							(SI_Long)8L) {
						    if ((resumable_icp_state_1 
							    ? 
							    TRUEP(Resumable_icp_state) 
							    : TRUEP(Nil)) 
							    ||  
							    !TRUEP(Remote_value_known_typetag)) 
								{
							if (EQ(icp_suspend_1,
								write_icp_byte(FIX((SI_Long)11L)))) 
								    {
							    resumable_icp_push(Qtrue);
							    resumable_icp_push(FIX((SI_Long)1L));
							    value_1 = 
								    Icp_suspend;
							    goto end_block_6;
							}
						    }
						}
						else if (EQ(icp_suspend_1,
							write_icp_byte(FIX((SI_Long)11L)))) 
							    {
						    resumable_icp_push(Qfalse);
						    resumable_icp_push(FIX((SI_Long)1L));
						    value_1 = Icp_suspend;
						    goto end_block_6;
						}
					      l2_6:
						value_1 = 
							write_icp_wide_string(value);
						if (EQ(icp_suspend_1,
							    value_1)) {
						    resumable_icp_push(FIX((SI_Long)2L));
						    value_1 = Icp_suspend;
						    goto end_block_6;
						}
						goto end_block_6;
					      end_block_6:
						if (EQ(icp_suspend_1,
							    value_1)) {
						    resumable_icp_push(Qtrue);
						    resumable_icp_push(Qresumable_icp_list_end);
						    resumable_icp_push(value);
						    resumable_icp_push(Qtrue);
						    resumable_icp_push(Qfalse);
						    resumable_icp_push(Qfalse);
						    resumable_icp_push(Qfalse);
						    resumable_icp_push(Qfalse);
						    resumable_icp_push(Qfalse);
						    resumable_icp_push(Qfalse);
						    resumable_icp_push(Qfalse);
						    resumable_icp_push(typecode);
						    resumable_icp_push(remote_value_1);
						    resumable_icp_push(Qwrite_icp_remote_value_1);
						    return VALUES_1(Icp_suspend);
						}
						result_1 = value_1;
					    }
					    else {
						if (resumable_icp_state_1 ?
							 
							TRUEP(Resumable_icp_state) 
							: TRUEP(Nil)) {
						    temp = resumable_icp_pop();
						    if (! !(FIXNUMP(temp) 
							    && 
							    FIXNUM_LE(FIX((SI_Long)-128L),
							    temp) && 
							    FIXNUM_LE(temp,
							    FIX((SI_Long)127L))))
							switch (INTEGER_TO_CHAR(temp)) 
								    {
							  case 1:
							    goto l1_7;
							    break;
							  case 2:
							    goto l2_7;
							    break;
							  default:
							    break;
							}
						}
					      l1_7:
						test = Nil;
						if (resumable_icp_state_1 ?
							 
							TRUEP(Resumable_icp_state) 
							: TRUEP(Nil)) {
						    test = resumable_icp_pop();
						    temp_1 = TRUEP(test);
						}
						else
						    temp_1 = TRUEP(Nil);
						if (temp_1 ? EQ(test,
							Qtrue) : 
							IFIX(ISVREF(Current_icp_socket,
							(SI_Long)22L)) >= 
							(SI_Long)8L) {
						    if ((resumable_icp_state_1 
							    ? 
							    TRUEP(Resumable_icp_state) 
							    : TRUEP(Nil)) 
							    ||  
							    !TRUEP(Remote_value_known_typetag)) 
								{
							if (EQ(icp_suspend_1,
								write_icp_byte(FIX((SI_Long)4L)))) 
								    {
							    resumable_icp_push(Qtrue);
							    resumable_icp_push(FIX((SI_Long)1L));
							    value_1 = 
								    Icp_suspend;
							    goto end_block_7;
							}
						    }
						}
						else if (EQ(icp_suspend_1,
							write_icp_byte(FIX((SI_Long)4L)))) 
							    {
						    resumable_icp_push(Qfalse);
						    resumable_icp_push(FIX((SI_Long)1L));
						    value_1 = Icp_suspend;
						    goto end_block_7;
						}
					      l2_7:
						value_1 = 
							write_icp_text_string(value);
						if (EQ(icp_suspend_1,
							    value_1)) {
						    resumable_icp_push(FIX((SI_Long)2L));
						    value_1 = Icp_suspend;
						    goto end_block_7;
						}
						goto end_block_7;
					      end_block_7:
						if (EQ(icp_suspend_1,
							    value_1)) {
						    resumable_icp_push(Qfalse);
						    resumable_icp_push(Qresumable_icp_list_end);
						    resumable_icp_push(value);
						    resumable_icp_push(Qtrue);
						    resumable_icp_push(Qfalse);
						    resumable_icp_push(Qfalse);
						    resumable_icp_push(Qfalse);
						    resumable_icp_push(Qfalse);
						    resumable_icp_push(Qfalse);
						    resumable_icp_push(Qfalse);
						    resumable_icp_push(Qfalse);
						    resumable_icp_push(typecode);
						    resumable_icp_push(remote_value_1);
						    resumable_icp_push(Qwrite_icp_remote_value_1);
						    return VALUES_1(Icp_suspend);
						}
						result_1 = value_1;
					    }
					}
					temp = result_1;
				    }
				    else {
					test = Nil;
					if (resumable_icp_state_1 ? 
						TRUEP(Resumable_icp_state) 
						: TRUEP(Nil)) {
					    test = resumable_icp_pop();
					    temp_1 = TRUEP(test);
					}
					else
					    temp_1 = TRUEP(Nil);
					if (temp_1 ? EQ(test,Qtrue) : 
						EQ(typecode,Qhandle)) {
					    value = (resumable_icp_state_1 
						    ? 
						    TRUEP(Resumable_icp_state) 
						    : TRUEP(Nil)) &&  
						    !TRUEP(resumable_icp_pop_list_if_end_marker()) 
						    ? resumable_icp_pop() :
						     remote_value_1;
					    if ((resumable_icp_state_1 ? 
						    TRUEP(Resumable_icp_state) 
						    : TRUEP(Nil)) &&  
						    !TRUEP(resumable_icp_pop_list_if_end_marker()))
						result_1 = resumable_icp_pop();
					    else {
						if (resumable_icp_state_1 ?
							 
							TRUEP(Resumable_icp_state) 
							: TRUEP(Nil)) {
						    temp = resumable_icp_pop();
						    if (! !(FIXNUMP(temp) 
							    && 
							    FIXNUM_LE(FIX((SI_Long)-128L),
							    temp) && 
							    FIXNUM_LE(temp,
							    FIX((SI_Long)127L))))
							switch (INTEGER_TO_CHAR(temp)) 
								    {
							  case 1:
							    goto l1_8;
							    break;
							  case 2:
							    goto l2_8;
							    break;
							  default:
							    break;
							}
						}
					      l1_8:
						test = Nil;
						if (resumable_icp_state_1 ?
							 
							TRUEP(Resumable_icp_state) 
							: TRUEP(Nil)) {
						    test = resumable_icp_pop();
						    temp_1 = TRUEP(test);
						}
						else
						    temp_1 = TRUEP(Nil);
						if (temp_1 ? EQ(test,
							Qtrue) : 
							IFIX(ISVREF(Current_icp_socket,
							(SI_Long)22L)) >= 
							(SI_Long)8L) {
						    if ((resumable_icp_state_1 
							    ? 
							    TRUEP(Resumable_icp_state) 
							    : TRUEP(Nil)) 
							    ||  
							    !TRUEP(Remote_value_known_typetag)) 
								{
							if (EQ(icp_suspend_1,
								write_icp_byte(FIX((SI_Long)8L)))) 
								    {
							    resumable_icp_push(Qtrue);
							    resumable_icp_push(FIX((SI_Long)1L));
							    value_1 = 
								    Icp_suspend;
							    goto end_block_8;
							}
						    }
						}
						else if (EQ(icp_suspend_1,
							write_icp_byte(FIX((SI_Long)8L)))) 
							    {
						    resumable_icp_push(Qfalse);
						    resumable_icp_push(FIX((SI_Long)1L));
						    value_1 = Icp_suspend;
						    goto end_block_8;
						}
					      l2_8:
						value_1 = 
							write_icp_fixnum(value);
						if (EQ(icp_suspend_1,
							    value_1)) {
						    resumable_icp_push(FIX((SI_Long)2L));
						    value_1 = Icp_suspend;
						    goto end_block_8;
						}
						goto end_block_8;
					      end_block_8:
						if (EQ(icp_suspend_1,
							    value_1)) {
						    resumable_icp_push(Qresumable_icp_list_end);
						    resumable_icp_push(value);
						    resumable_icp_push(Qtrue);
						    resumable_icp_push(Qfalse);
						    resumable_icp_push(Qfalse);
						    resumable_icp_push(Qfalse);
						    resumable_icp_push(Qfalse);
						    resumable_icp_push(Qfalse);
						    resumable_icp_push(Qfalse);
						    resumable_icp_push(Qfalse);
						    resumable_icp_push(Qfalse);
						    resumable_icp_push(typecode);
						    resumable_icp_push(remote_value_1);
						    resumable_icp_push(Qwrite_icp_remote_value_1);
						    return VALUES_1(Icp_suspend);
						}
						result_1 = value_1;
					    }
					    temp = result_1;
					}
					else {
					    test = Nil;
					    if (resumable_icp_state_1 ? 
						    TRUEP(Resumable_icp_state) 
						    : TRUEP(Nil)) {
						test = resumable_icp_pop();
						temp_1 = TRUEP(test);
					    }
					    else
						temp_1 = TRUEP(Nil);
					    if (temp_1 ? EQ(test,Qtrue) : 
						    EQ(typecode,
							Qab_structure)) {
						value = 
							(resumable_icp_state_1 
							? 
							TRUEP(Resumable_icp_state) 
							: TRUEP(Nil)) &&  
							!TRUEP(resumable_icp_pop_list_if_end_marker()) 
							? 
							resumable_icp_pop() 
							: remote_value_1;
						if ((resumable_icp_state_1 
							? 
							TRUEP(Resumable_icp_state) 
							: TRUEP(Nil)) &&  
							!TRUEP(resumable_icp_pop_list_if_end_marker()))
						    result_1 = 
							    resumable_icp_pop();
						else {
						    test = Nil;
						    if (resumable_icp_state_1 
							    ? 
							    TRUEP(Resumable_icp_state) 
							    : TRUEP(Nil)) {
							test = 
								resumable_icp_pop();
							temp_1 = TRUEP(test);
						    }
						    else
							temp_1 = TRUEP(Nil);
						    if (temp_1 ? EQ(test,
							    Qtrue) : 
							    IFIX(ISVREF(Current_icp_socket,
							    (SI_Long)22L)) 
							    >= (SI_Long)8L) {
							if (resumable_icp_state_1 
								? 
								TRUEP(Resumable_icp_state) 
								: TRUEP(Nil)) {
							    temp = 
								    resumable_icp_pop();
							    if (! 
								    !(FIXNUMP(temp) 
								    && 
								    FIXNUM_LE(FIX((SI_Long)-128L),
								    temp) 
								    && 
								    FIXNUM_LE(temp,
								    FIX((SI_Long)127L))))
								switch (INTEGER_TO_CHAR(temp)) 
									    {
								  case 1:
								    goto l1_9;
								    break;
								  case 2:
								    goto l2_9;
								    break;
								  default:
								    break;
								}
							}
						      l1_9:
							test = Nil;
							if (resumable_icp_state_1 
								? 
								TRUEP(Resumable_icp_state) 
								: TRUEP(Nil)) {
							    test = 
								    resumable_icp_pop();
							    temp_1 = 
								    TRUEP(test);
							}
							else
							    temp_1 = 
								    TRUEP(Nil);
							if (temp_1 ? 
								EQ(test,
								Qtrue) : 
								IFIX(ISVREF(Current_icp_socket,
								(SI_Long)22L)) 
								>= 
								    (SI_Long)8L) {
							    if ((resumable_icp_state_1 
								    ? 
								    TRUEP(Resumable_icp_state) 
								    : 
								    TRUEP(Nil)) 
								    ||  
								    !TRUEP(Remote_value_known_typetag)) 
									{
								if (EQ(icp_suspend_1,
									write_icp_byte(FIX((SI_Long)50L)))) 
									    {
								    resumable_icp_push(Qtrue);
								    resumable_icp_push(FIX((SI_Long)1L));
								    value_1 
									    = 
									    Icp_suspend;
								    goto end_block_9;
								}
							    }
							}
							else if (EQ(icp_suspend_1,
								write_icp_byte(FIX((SI_Long)50L)))) 
								    {
							    resumable_icp_push(Qfalse);
							    resumable_icp_push(FIX((SI_Long)1L));
							    value_1 = 
								    Icp_suspend;
							    goto end_block_9;
							}
						      l2_9:
							value_1 = 
								write_icp_evaluation_structure(value);
							if (EQ(icp_suspend_1,
								value_1)) {
							    resumable_icp_push(FIX((SI_Long)2L));
							    value_1 = 
								    Icp_suspend;
							    goto end_block_9;
							}
							goto end_block_9;
						      end_block_9:
							if (EQ(icp_suspend_1,
								value_1)) {
							    resumable_icp_push(Qtrue);
							    resumable_icp_push(Qresumable_icp_list_end);
							    resumable_icp_push(value);
							    resumable_icp_push(Qtrue);
							    resumable_icp_push(Qfalse);
							    resumable_icp_push(Qfalse);
							    resumable_icp_push(Qfalse);
							    resumable_icp_push(Qfalse);
							    resumable_icp_push(Qfalse);
							    resumable_icp_push(Qfalse);
							    resumable_icp_push(Qfalse);
							    resumable_icp_push(Qfalse);
							    resumable_icp_push(Qfalse);
							    resumable_icp_push(typecode);
							    resumable_icp_push(remote_value_1);
							    resumable_icp_push(Qwrite_icp_remote_value_1);
							    return VALUES_1(Icp_suspend);
							}
							result_1 = value_1;
						    }
						    else {
							value_1 = 
								write_icp_byte(FIX((SI_Long)0L));
							if (EQ(icp_suspend_1,
								value_1)) {
							    resumable_icp_push(Qfalse);
							    resumable_icp_push(Qresumable_icp_list_end);
							    resumable_icp_push(value);
							    resumable_icp_push(Qtrue);
							    resumable_icp_push(Qfalse);
							    resumable_icp_push(Qfalse);
							    resumable_icp_push(Qfalse);
							    resumable_icp_push(Qfalse);
							    resumable_icp_push(Qfalse);
							    resumable_icp_push(Qfalse);
							    resumable_icp_push(Qfalse);
							    resumable_icp_push(Qfalse);
							    resumable_icp_push(Qfalse);
							    resumable_icp_push(typecode);
							    resumable_icp_push(remote_value_1);
							    resumable_icp_push(Qwrite_icp_remote_value_1);
							    return VALUES_1(Icp_suspend);
							}
							result_1 = value_1;
						    }
						}
						temp = result_1;
					    }
					    else {
						test = Nil;
						if (resumable_icp_state_1 ?
							 
							TRUEP(Resumable_icp_state) 
							: TRUEP(Nil)) {
						    test = resumable_icp_pop();
						    temp_1 = TRUEP(test);
						}
						else
						    temp_1 = TRUEP(Nil);
						if (temp_1 ? EQ(test,
							Qtrue) : 
							EQ(typecode,
							    Qsequence)) {
						    value = 
							    (resumable_icp_state_1 
							    ? 
							    TRUEP(Resumable_icp_state) 
							    : TRUEP(Nil)) 
							    &&  
							    !TRUEP(resumable_icp_pop_list_if_end_marker()) 
							    ? 
							    resumable_icp_pop() 
							    : remote_value_1;
						    if ((resumable_icp_state_1 
							    ? 
							    TRUEP(Resumable_icp_state) 
							    : TRUEP(Nil)) 
							    &&  
							    !TRUEP(resumable_icp_pop_list_if_end_marker()))
							result_1 = 
								resumable_icp_pop();
						    else {
							test = Nil;
							if (resumable_icp_state_1 
								? 
								TRUEP(Resumable_icp_state) 
								: TRUEP(Nil)) {
							    test = 
								    resumable_icp_pop();
							    temp_1 = 
								    TRUEP(test);
							}
							else
							    temp_1 = 
								    TRUEP(Nil);
							if (temp_1 ? 
								EQ(test,
								Qtrue) : 
								IFIX(ISVREF(Current_icp_socket,
								(SI_Long)22L)) 
								>= 
								    (SI_Long)8L) {
							    value_1 = 
								    write_icp_evaluation_sequence(value);
							    if (EQ(icp_suspend_1,
								    value_1)) {
								resumable_icp_push(Qtrue);
								resumable_icp_push(Qresumable_icp_list_end);
								resumable_icp_push(value);
								resumable_icp_push(Qtrue);
								resumable_icp_push(Qfalse);
								resumable_icp_push(Qfalse);
								resumable_icp_push(Qfalse);
								resumable_icp_push(Qfalse);
								resumable_icp_push(Qfalse);
								resumable_icp_push(Qfalse);
								resumable_icp_push(Qfalse);
								resumable_icp_push(Qfalse);
								resumable_icp_push(Qfalse);
								resumable_icp_push(Qfalse);
								resumable_icp_push(typecode);
								resumable_icp_push(remote_value_1);
								resumable_icp_push(Qwrite_icp_remote_value_1);
								return VALUES_1(Icp_suspend);
							    }
							    result_1 = value_1;
							}
							else {
							    value_1 = 
								    write_icp_byte(FIX((SI_Long)0L));
							    if (EQ(icp_suspend_1,
								    value_1)) {
								resumable_icp_push(Qfalse);
								resumable_icp_push(Qresumable_icp_list_end);
								resumable_icp_push(value);
								resumable_icp_push(Qtrue);
								resumable_icp_push(Qfalse);
								resumable_icp_push(Qfalse);
								resumable_icp_push(Qfalse);
								resumable_icp_push(Qfalse);
								resumable_icp_push(Qfalse);
								resumable_icp_push(Qfalse);
								resumable_icp_push(Qfalse);
								resumable_icp_push(Qfalse);
								resumable_icp_push(Qfalse);
								resumable_icp_push(Qfalse);
								resumable_icp_push(typecode);
								resumable_icp_push(remote_value_1);
								resumable_icp_push(Qwrite_icp_remote_value_1);
								return VALUES_1(Icp_suspend);
							    }
							    result_1 = value_1;
							}
						    }
						    temp = result_1;
						}
						else {
						    test = Nil;
						    if (resumable_icp_state_1 
							    ? 
							    TRUEP(Resumable_icp_state) 
							    : TRUEP(Nil)) {
							test = 
								resumable_icp_pop();
							temp_1 = TRUEP(test);
						    }
						    else
							temp_1 = TRUEP(Nil);
						    if (temp_1 ? EQ(test,
							    Qtrue) : 
							    EQ(typecode,
								Qitem)) {
							value = 
								(resumable_icp_state_1 
								? 
								TRUEP(Resumable_icp_state) 
								: 
								TRUEP(Nil)) 
								&&  
								!TRUEP(resumable_icp_pop_list_if_end_marker()) 
								? 
								resumable_icp_pop() 
								: 
								remote_value_1;
							if ((resumable_icp_state_1 
								? 
								TRUEP(Resumable_icp_state) 
								: 
								TRUEP(Nil)) 
								&&  
								!TRUEP(resumable_icp_pop_list_if_end_marker()))
							    result_1 = 
								    resumable_icp_pop();
							else {
							    test = Nil;
							    if (resumable_icp_state_1 
								    ? 
								    TRUEP(Resumable_icp_state) 
								    : 
								    TRUEP(Nil)) 
									{
								test = 
									resumable_icp_pop();
								temp_1 = 
									TRUEP(test);
							    }
							    else
								temp_1 = 
									TRUEP(Nil);
							    if (temp_1 ? 
								    EQ(test,
								    Qtrue) 
								    : 
								    IFIX(ISVREF(Current_icp_socket,
								    (SI_Long)22L)) 
								    >= 
								    (SI_Long)8L) 
									{
								value_1 = 
									write_icp_item(value);
								if (EQ(icp_suspend_1,
									value_1)) 
									    {
								    resumable_icp_push(Qtrue);
								    resumable_icp_push(Qresumable_icp_list_end);
								    resumable_icp_push(value);
								    resumable_icp_push(Qtrue);
								    resumable_icp_push(Qfalse);
								    resumable_icp_push(Qfalse);
								    resumable_icp_push(Qfalse);
								    resumable_icp_push(Qfalse);
								    resumable_icp_push(Qfalse);
								    resumable_icp_push(Qfalse);
								    resumable_icp_push(Qfalse);
								    resumable_icp_push(Qfalse);
								    resumable_icp_push(Qfalse);
								    resumable_icp_push(Qfalse);
								    resumable_icp_push(Qfalse);
								    resumable_icp_push(typecode);
								    resumable_icp_push(remote_value_1);
								    resumable_icp_push(Qwrite_icp_remote_value_1);
								    return VALUES_1(Icp_suspend);
								}
								result_1 = 
									value_1;
							    }
							    else {
								value_1 = 
									write_icp_byte(FIX((SI_Long)0L));
								if (EQ(icp_suspend_1,
									value_1)) 
									    {
								    resumable_icp_push(Qfalse);
								    resumable_icp_push(Qresumable_icp_list_end);
								    resumable_icp_push(value);
								    resumable_icp_push(Qtrue);
								    resumable_icp_push(Qfalse);
								    resumable_icp_push(Qfalse);
								    resumable_icp_push(Qfalse);
								    resumable_icp_push(Qfalse);
								    resumable_icp_push(Qfalse);
								    resumable_icp_push(Qfalse);
								    resumable_icp_push(Qfalse);
								    resumable_icp_push(Qfalse);
								    resumable_icp_push(Qfalse);
								    resumable_icp_push(Qfalse);
								    resumable_icp_push(Qfalse);
								    resumable_icp_push(typecode);
								    resumable_icp_push(remote_value_1);
								    resumable_icp_push(Qwrite_icp_remote_value_1);
								    return VALUES_1(Icp_suspend);
								}
								result_1 = 
									value_1;
							    }
							}
							temp = result_1;
						    }
						    else if ((resumable_icp_state_1 
							    ? 
							    TRUEP(Resumable_icp_state) 
							    : TRUEP(Nil)) 
								|| T) {
							value_1 = 
								write_icp_byte(FIX((SI_Long)0L));
							if (EQ(icp_suspend_1,
								value_1)) {
							    resumable_icp_push(Qfalse);
							    resumable_icp_push(Qfalse);
							    resumable_icp_push(Qfalse);
							    resumable_icp_push(Qfalse);
							    resumable_icp_push(Qfalse);
							    resumable_icp_push(Qfalse);
							    resumable_icp_push(Qfalse);
							    resumable_icp_push(Qfalse);
							    resumable_icp_push(Qfalse);
							    resumable_icp_push(Qfalse);
							    resumable_icp_push(Qfalse);
							    resumable_icp_push(Qfalse);
							    resumable_icp_push(typecode);
							    resumable_icp_push(remote_value_1);
							    resumable_icp_push(Qwrite_icp_remote_value_1);
							    return VALUES_1(Icp_suspend);
							}
							temp = value_1;
						    }
						    else
							temp = Qnil;
						}
					    }
					}
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
    return VALUES_1(temp);
}

static Object string_constant_4;   /* "Unknown type tag ~a in READ-ICP-REMOTE-VALUE" */

static Object Qread_icp_remote_value_1;  /* read-icp-remote-value-1 */

/* READ-ICP-REMOTE-VALUE-1 */
Object read_icp_remote_value_1()
{
    Object value_p, temp, value, symbol, type_tag, gensymed_symbol, string_1;
    Object wide_string_bv16, resumable_icp_state_1, icp_suspend_1, top, key;
    Object test, value_1, value_2, arg1;
    SI_Long length_1;
    char temp_1;

    x_note_fn_call(157,100);
    if (Disable_resumability) {
	value_p = Nil;
	if (IFIX(ISVREF(Current_icp_socket,(SI_Long)21L)) >= (SI_Long)8L) {
	    temp = Remote_value_known_typetag;
	    if (temp);
	    else
		temp = peek_icp_byte();
	}
	else
	    temp = peek_icp_byte();
	if ( !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
		FIXNUM_LE(temp,FIX((SI_Long)127L))))
	    value = Nil;
	else
	    switch (INTEGER_TO_CHAR(temp)) {
	      case 60:
	      case 61:
	      case 74:
	      case 62:
	      case 64:
	      case 65:
	      case 66:
	      case 63:
		value_p = T;
		value = read_icp_item();
		break;
	      case 70:
	      case 73:
	      case 71:
	      case 72:
	      case 75:
	      case 3:
		symbol = read_icp_symbol_as_value_type();
		value = symbol;
		break;
	      case 49:
	      case 67:
		value = read_icp_evaluation_sequence();
		break;
	      default:
		value = Nil;
		break;
	    }
	if (value || value_p)
	    temp = value;
	else {
	    if (IFIX(ISVREF(Current_icp_socket,(SI_Long)21L)) >= (SI_Long)8L) {
		type_tag = Remote_value_known_typetag;
		if (type_tag);
		else
		    type_tag = read_icp_byte();
	    }
	    else
		type_tag = read_icp_byte();
	    temp = type_tag;
	    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		    FIX((SI_Long)127L))))
		temp = icp_error_internal(Qerror,string_constant_4,
			type_tag,Nil,Nil);
	    else
		switch (INTEGER_TO_CHAR(temp)) {
		  case 0:
		    temp = Nil;
		    break;
		  case 5:
		    gensymed_symbol = read_icp_integer();
		    if (FIXNUM_EQ(gensymed_symbol,Truth))
			temp = Evaluation_true_value;
		    else if (FIXNUM_EQ(gensymed_symbol,Falsity))
			temp = Evaluation_false_value;
		    else
			temp = eval_cons_1(gensymed_symbol,Qtruth_value);
		    break;
		  case 1:
		    temp = read_icp_fixnum();
		    break;
		  case 51:
		    temp = read_icp_managed_long();
		    break;
		  case 6:
		    temp = read_icp_managed_double_float();
		    break;
		  case 2:
		    temp = read_icp_float();
		    break;
		  case 4:
		    temp = read_icp_text_string();
		    break;
		  case 68:
		    string_1 = read_icp_gensym_string();
		    temp = gensym_string_to_wide_string(string_1);
		    reclaim_gensym_string(string_1);
		    break;
		  case 69:
		    temp = read_icp_wide_string();
		    break;
		  case 11:
		    wide_string_bv16 = read_icp_wide_string();
		    length_1 = 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
		    length_1 = UBYTE_16_ISAREF_1(wide_string_bv16,length_1 
			    - (SI_Long)2L) + 
			    ((UBYTE_16_ISAREF_1(wide_string_bv16,length_1 
			    - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
		    UBYTE_16_ISASET_1(wide_string_bv16,length_1,(SI_Long)1L);
		    temp = 
			    maybe_make_evaluation_unsigned_vector_16(wide_string_bv16);
		    break;
		  case 50:
		    temp = read_icp_evaluation_structure();
		    break;
		  case 8:
		    temp = read_icp_fixnum();
		    break;
		  default:
		    temp = icp_error_internal(Qerror,string_constant_4,
			    type_tag,Nil,Nil);
		    break;
		}
	}
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qread_icp_remote_value_1,top))
		return icp_error_internal(Qerror,string_constant,
			Qread_icp_remote_value_1,top,Nil);
	}
	value_p = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : Nil;
	if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  !TRUEP(resumable_icp_pop_list_if_end_marker()))
	    value = resumable_icp_pop();
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		key = resumable_icp_pop();
	    else {
		test = Nil;
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    test = resumable_icp_pop();
		    temp_1 = TRUEP(test);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1 ? EQ(test,Qtrue) : 
			IFIX(ISVREF(Current_icp_socket,(SI_Long)21L)) >= 
			(SI_Long)8L) {
		    value_1 = (resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()) 
			    ? resumable_icp_pop() : Remote_value_known_typetag;
		    if ( !(resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) && 
			    value_1)
			key = value_1;
		    else {
			value_2 = peek_icp_byte();
			if (EQ(icp_suspend_1,value_2)) {
			    resumable_icp_push(value_1);
			    resumable_icp_push(Qtrue);
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(value_p);
			    resumable_icp_push(Qread_icp_remote_value_1);
			    return VALUES_1(Icp_suspend);
			}
			key = value_2;
		    }
		}
		else {
		    value_1 = peek_icp_byte();
		    if (EQ(icp_suspend_1,value_1)) {
			resumable_icp_push(Qfalse);
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(value_p);
			resumable_icp_push(Qread_icp_remote_value_1);
			return VALUES_1(Icp_suspend);
		    }
		    key = value_1;
		}
	    }
	    temp = key;
	    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		    FIX((SI_Long)127L))))
		value = Nil;
	    else
		switch (INTEGER_TO_CHAR(temp)) {
		  case 60:
		  case 61:
		  case 74:
		  case 62:
		  case 64:
		  case 65:
		  case 66:
		  case 63:
		    if ( !(resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)))
			value_p = T;
		    value_1 = read_icp_item();
		    if (EQ(icp_suspend_1,value_1)) {
			resumable_icp_push(key);
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(value_p);
			resumable_icp_push(Qread_icp_remote_value_1);
			return VALUES_1(Icp_suspend);
		    }
		    value = value_1;
		    break;
		  case 70:
		  case 73:
		  case 71:
		  case 72:
		  case 75:
		  case 3:
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()))
			symbol = resumable_icp_pop();
		    else {
			value_1 = read_icp_symbol_as_value_type();
			if (EQ(icp_suspend_1,value_1)) {
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(key);
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(value_p);
			    resumable_icp_push(Qread_icp_remote_value_1);
			    return VALUES_1(Icp_suspend);
			}
			symbol = value_1;
		    }
		    value = symbol;
		    break;
		  case 49:
		  case 67:
		    value_1 = read_icp_evaluation_sequence();
		    if (EQ(icp_suspend_1,value_1)) {
			resumable_icp_push(key);
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(value_p);
			resumable_icp_push(Qread_icp_remote_value_1);
			return VALUES_1(Icp_suspend);
		    }
		    value = value_1;
		    break;
		  default:
		    value = Nil;
		    break;
		}
	}
	if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) && (value || value_p))
	    temp = value;
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		type_tag = resumable_icp_pop();
	    else {
		test = Nil;
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    test = resumable_icp_pop();
		    temp_1 = TRUEP(test);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1 ? EQ(test,Qtrue) : 
			IFIX(ISVREF(Current_icp_socket,(SI_Long)21L)) >= 
			(SI_Long)8L) {
		    value_1 = (resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()) 
			    ? resumable_icp_pop() : Remote_value_known_typetag;
		    if ( !(resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) && 
			    value_1)
			type_tag = value_1;
		    else {
			value_2 = read_icp_byte();
			if (EQ(icp_suspend_1,value_2)) {
			    resumable_icp_push(value_1);
			    resumable_icp_push(Qtrue);
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(value);
			    resumable_icp_push(value_p);
			    resumable_icp_push(Qread_icp_remote_value_1);
			    return VALUES_1(Icp_suspend);
			}
			type_tag = value_2;
		    }
		}
		else {
		    value_1 = read_icp_byte();
		    if (EQ(icp_suspend_1,value_1)) {
			resumable_icp_push(Qfalse);
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(value);
			resumable_icp_push(value_p);
			resumable_icp_push(Qread_icp_remote_value_1);
			return VALUES_1(Icp_suspend);
		    }
		    type_tag = value_1;
		}
	    }
	    key = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : type_tag;
	    temp = key;
	    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		    FIX((SI_Long)127L)))) {
		value_1 = icp_error_internal(Qerror,string_constant_4,
			type_tag,Nil,Nil);
		if (EQ(icp_suspend_1,value_1)) {
		    resumable_icp_push(key);
		    resumable_icp_push(type_tag);
		    resumable_icp_push(value);
		    resumable_icp_push(value_p);
		    resumable_icp_push(Qread_icp_remote_value_1);
		    return VALUES_1(Icp_suspend);
		}
		temp = value_1;
	    }
	    else
		switch (INTEGER_TO_CHAR(temp)) {
		  case 0:
		    temp = Nil;
		    break;
		  case 5:
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()))
			arg1 = resumable_icp_pop();
		    else {
			value_1 = read_icp_integer();
			if (EQ(icp_suspend_1,value_1)) {
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(key);
			    resumable_icp_push(type_tag);
			    resumable_icp_push(value);
			    resumable_icp_push(value_p);
			    resumable_icp_push(Qread_icp_remote_value_1);
			    return VALUES_1(Icp_suspend);
			}
			arg1 = value_1;
		    }
		    if (FIXNUM_EQ(arg1,Truth))
			temp = Evaluation_true_value;
		    else if (FIXNUM_EQ(arg1,Falsity))
			temp = Evaluation_false_value;
		    else
			temp = eval_cons_1(arg1,Qtruth_value);
		    break;
		  case 1:
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()))
			arg1 = resumable_icp_pop();
		    else {
			value_1 = read_icp_fixnum();
			if (EQ(icp_suspend_1,value_1)) {
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(key);
			    resumable_icp_push(type_tag);
			    resumable_icp_push(value);
			    resumable_icp_push(value_p);
			    resumable_icp_push(Qread_icp_remote_value_1);
			    return VALUES_1(Icp_suspend);
			}
			arg1 = value_1;
		    }
		    temp = arg1;
		    break;
		  case 51:
		    value_1 = read_icp_managed_long();
		    if (EQ(icp_suspend_1,value_1)) {
			resumable_icp_push(key);
			resumable_icp_push(type_tag);
			resumable_icp_push(value);
			resumable_icp_push(value_p);
			resumable_icp_push(Qread_icp_remote_value_1);
			return VALUES_1(Icp_suspend);
		    }
		    temp = value_1;
		    break;
		  case 6:
		    value_1 = read_icp_managed_double_float();
		    if (EQ(icp_suspend_1,value_1)) {
			resumable_icp_push(key);
			resumable_icp_push(type_tag);
			resumable_icp_push(value);
			resumable_icp_push(value_p);
			resumable_icp_push(Qread_icp_remote_value_1);
			return VALUES_1(Icp_suspend);
		    }
		    temp = value_1;
		    break;
		  case 2:
		    value_1 = read_icp_float();
		    if (EQ(icp_suspend_1,value_1)) {
			resumable_icp_push(key);
			resumable_icp_push(type_tag);
			resumable_icp_push(value);
			resumable_icp_push(value_p);
			resumable_icp_push(Qread_icp_remote_value_1);
			return VALUES_1(Icp_suspend);
		    }
		    temp = value_1;
		    break;
		  case 4:
		    value_1 = read_icp_text_string();
		    if (EQ(icp_suspend_1,value_1)) {
			resumable_icp_push(key);
			resumable_icp_push(type_tag);
			resumable_icp_push(value);
			resumable_icp_push(value_p);
			resumable_icp_push(Qread_icp_remote_value_1);
			return VALUES_1(Icp_suspend);
		    }
		    temp = value_1;
		    break;
		  case 68:
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()))
			string_1 = resumable_icp_pop();
		    else {
			value_1 = read_icp_gensym_string();
			if (EQ(icp_suspend_1,value_1)) {
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(key);
			    resumable_icp_push(type_tag);
			    resumable_icp_push(value);
			    resumable_icp_push(value_p);
			    resumable_icp_push(Qread_icp_remote_value_1);
			    return VALUES_1(Icp_suspend);
			}
			string_1 = value_1;
		    }
		    temp = gensym_string_to_wide_string(string_1);
		    reclaim_gensym_string(string_1);
		    break;
		  case 69:
		    value_1 = read_icp_wide_string();
		    if (EQ(icp_suspend_1,value_1)) {
			resumable_icp_push(key);
			resumable_icp_push(type_tag);
			resumable_icp_push(value);
			resumable_icp_push(value_p);
			resumable_icp_push(Qread_icp_remote_value_1);
			return VALUES_1(Icp_suspend);
		    }
		    temp = value_1;
		    break;
		  case 11:
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()))
			arg1 = resumable_icp_pop();
		    else {
			if ((resumable_icp_state_1 ? 
				TRUEP(Resumable_icp_state) : TRUEP(Nil)) 
				&&  
				!TRUEP(resumable_icp_pop_list_if_end_marker()))
			    wide_string_bv16 = resumable_icp_pop();
			else {
			    value_1 = read_icp_wide_string();
			    if (EQ(icp_suspend_1,value_1)) {
				resumable_icp_push(Qresumable_icp_list_end);
				resumable_icp_push(Qresumable_icp_list_end);
				resumable_icp_push(key);
				resumable_icp_push(type_tag);
				resumable_icp_push(value);
				resumable_icp_push(value_p);
				resumable_icp_push(Qread_icp_remote_value_1);
				return VALUES_1(Icp_suspend);
			    }
			    wide_string_bv16 = value_1;
			}
			length_1 = 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
			length_1 = UBYTE_16_ISAREF_1(wide_string_bv16,
				length_1 - (SI_Long)2L) + 
				((UBYTE_16_ISAREF_1(wide_string_bv16,
				length_1 - (SI_Long)1L) & (SI_Long)8191L) 
				<< (SI_Long)16L);
			UBYTE_16_ISASET_1(wide_string_bv16,length_1,
				(SI_Long)1L);
			arg1 = wide_string_bv16;
		    }
		    temp = maybe_make_evaluation_unsigned_vector_16(arg1);
		    break;
		  case 50:
		    value_1 = read_icp_evaluation_structure();
		    if (EQ(icp_suspend_1,value_1)) {
			resumable_icp_push(key);
			resumable_icp_push(type_tag);
			resumable_icp_push(value);
			resumable_icp_push(value_p);
			resumable_icp_push(Qread_icp_remote_value_1);
			return VALUES_1(Icp_suspend);
		    }
		    temp = value_1;
		    break;
		  case 8:
		    value_1 = read_icp_fixnum();
		    if (EQ(icp_suspend_1,value_1)) {
			resumable_icp_push(key);
			resumable_icp_push(type_tag);
			resumable_icp_push(value);
			resumable_icp_push(value_p);
			resumable_icp_push(Qread_icp_remote_value_1);
			return VALUES_1(Icp_suspend);
		    }
		    temp = value_1;
		    break;
		  default:
		    value_1 = icp_error_internal(Qerror,string_constant_4,
			    type_tag,Nil,Nil);
		    if (EQ(icp_suspend_1,value_1)) {
			resumable_icp_push(key);
			resumable_icp_push(type_tag);
			resumable_icp_push(value);
			resumable_icp_push(value_p);
			resumable_icp_push(Qread_icp_remote_value_1);
			return VALUES_1(Icp_suspend);
		    }
		    temp = value_1;
		    break;
		}
	}
    }
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Item_copy_index_space, Qitem_copy_index_space);

static Object Qremote_value;       /* remote-value */

static Object string_constant_5;   /* "[value]" */

static Object Qunbound;            /* unbound */

static Object Qwrite_icp_remote_value;  /* write-icp-remote-value */

/* WRITE-ICP-REMOTE-VALUE */
Object write_icp_remote_value(remote_value)
    Object remote_value;
{
    Object tracep, byte_count_before, current_icp_write_trace_level;
    Object item_copy_index_space, current_computation_flags, temp;
    Object result_of_write, resumable_icp_state_1, icp_suspend_1, top, test;
    Object gensymed_symbol, value;
    char temp_1;
    Declare_special(3);
    Object result;

    x_note_fn_call(157,101);
    if (Disable_resumability) {
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,Qremote_value,
			string_constant_5,Qvalue,T,remote_value,Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    2);
	      if (EQ(Qunbound,Item_copy_index_space)) {
		  item_copy_index_space = Nil;
		  current_computation_flags = Current_computation_flags;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
			  1);
		    PUSH_SPECIAL_WITH_SYMBOL(Item_copy_index_space,Qitem_copy_index_space,item_copy_index_space,
			    0);
		      if (ISVREF(Current_icp_socket,(SI_Long)48L))
			  Current_computation_flags = 
				  FIX(IFIX(Current_computation_flags) | 
				  (SI_Long)16L);
		      else
			  Current_computation_flags = 
				  FIX(IFIX(Current_computation_flags) &  
				  ~(SI_Long)16L);
		      temp = write_icp_remote_value_1(remote_value);
		      if (Item_copy_index_space)
			  reclaim_index_space_1(Item_copy_index_space);
		      result_of_write = temp;
		    POP_SPECIAL();
		  POP_SPECIAL();
	      }
	      else
		  result_of_write = write_icp_remote_value_1(remote_value);
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qremote_value,string_constant_5,Qvalue,Nil,Nil,
			  Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else if (EQ(Qunbound,Item_copy_index_space)) {
	    item_copy_index_space = Nil;
	    current_computation_flags = Current_computation_flags;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		    1);
	      PUSH_SPECIAL_WITH_SYMBOL(Item_copy_index_space,Qitem_copy_index_space,item_copy_index_space,
		      0);
		if (ISVREF(Current_icp_socket,(SI_Long)48L))
		    Current_computation_flags = 
			    FIX(IFIX(Current_computation_flags) | 
			    (SI_Long)16L);
		else
		    Current_computation_flags = 
			    FIX(IFIX(Current_computation_flags) &  
			    ~(SI_Long)16L);
		temp = write_icp_remote_value_1(remote_value);
		if (Item_copy_index_space)
		    reclaim_index_space_1(Item_copy_index_space);
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	else
	    temp = write_icp_remote_value_1(remote_value);
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qwrite_icp_remote_value,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qwrite_icp_remote_value,top,Nil);
		goto end_write_icp_remote_value;
	    }
	}
	remote_value = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
		: TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : remote_value;
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,Qremote_value,
			string_constant_5,Qvalue,T,remote_value,Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    2);
	      test = Nil;
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  test = resumable_icp_pop();
		  temp_1 = TRUEP(test);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if (temp_1 ? EQ(test,Qtrue) : EQ(Qunbound,
			  Item_copy_index_space)) {
		  item_copy_index_space = (resumable_icp_state_1 ? 
			  TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			  resumable_icp_pop() : Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Item_copy_index_space,Qitem_copy_index_space,item_copy_index_space,
			  1);
		    current_computation_flags = (resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()) 
			    ? resumable_icp_pop() : Current_computation_flags;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
			    0);
		      if ( !(resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil))) {
			  if (ISVREF(Current_icp_socket,(SI_Long)48L))
			      Current_computation_flags = 
				      FIX(IFIX(Current_computation_flags) 
				      | (SI_Long)16L);
			  else
			      Current_computation_flags = 
				      FIX(IFIX(Current_computation_flags) 
				      &  ~(SI_Long)16L);
		      }
		      if ((resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			      !TRUEP(resumable_icp_pop_list_if_end_marker()))
			  gensymed_symbol = resumable_icp_pop();
		      else {
			  value = write_icp_remote_value_1(remote_value);
			  if (EQ(icp_suspend_1,value)) {
			      resumable_icp_push(Qresumable_icp_list_end);
			      resumable_icp_push(Current_computation_flags);
			      resumable_icp_push(Item_copy_index_space);
			      resumable_icp_push(Qtrue);
			      resumable_icp_push(remote_value);
			      resumable_icp_push(Qwrite_icp_remote_value);
			      result = VALUES_1(Icp_suspend);
			      POP_SPECIAL();
			      POP_SPECIAL();
			      POP_SPECIAL();
			      goto end_write_icp_remote_value;
			  }
			  gensymed_symbol = value;
		      }
		      if (Item_copy_index_space)
			  reclaim_index_space_1(Item_copy_index_space);
		      result_of_write = gensymed_symbol;
		    POP_SPECIAL();
		  POP_SPECIAL();
	      }
	      else {
		  value = write_icp_remote_value_1(remote_value);
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qfalse);
		      resumable_icp_push(remote_value);
		      resumable_icp_push(Qwrite_icp_remote_value);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_write_icp_remote_value;
		  }
		  result_of_write = value;
	      }
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qremote_value,string_constant_5,Qvalue,Nil,Nil,
			  Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else {
	    test = Nil;
	    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) {
		test = resumable_icp_pop();
		temp_1 = TRUEP(test);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? EQ(test,Qtrue) : EQ(Qunbound,Item_copy_index_space)) {
		item_copy_index_space = (resumable_icp_state_1 ? 
			TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			resumable_icp_pop() : Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Item_copy_index_space,Qitem_copy_index_space,item_copy_index_space,
			1);
		  current_computation_flags = (resumable_icp_state_1 ? 
			  TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			  resumable_icp_pop() : Current_computation_flags;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
			  0);
		    if ( !(resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil))) {
			if (ISVREF(Current_icp_socket,(SI_Long)48L))
			    Current_computation_flags = 
				    FIX(IFIX(Current_computation_flags) | 
				    (SI_Long)16L);
			else
			    Current_computation_flags = 
				    FIX(IFIX(Current_computation_flags) &  
				    ~(SI_Long)16L);
		    }
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()))
			gensymed_symbol = resumable_icp_pop();
		    else {
			value = write_icp_remote_value_1(remote_value);
			if (EQ(icp_suspend_1,value)) {
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(Current_computation_flags);
			    resumable_icp_push(Item_copy_index_space);
			    resumable_icp_push(Qtrue);
			    resumable_icp_push(remote_value);
			    resumable_icp_push(Qwrite_icp_remote_value);
			    result = VALUES_1(Icp_suspend);
			    POP_SPECIAL();
			    POP_SPECIAL();
			    goto end_write_icp_remote_value;
			}
			gensymed_symbol = value;
		    }
		    if (Item_copy_index_space)
			reclaim_index_space_1(Item_copy_index_space);
		    temp = gensymed_symbol;
		  POP_SPECIAL();
		POP_SPECIAL();
	    }
	    else {
		value = write_icp_remote_value_1(remote_value);
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qfalse);
		    resumable_icp_push(remote_value);
		    resumable_icp_push(Qwrite_icp_remote_value);
		    result = VALUES_1(Icp_suspend);
		    goto end_write_icp_remote_value;
		}
		temp = value;
	    }
	}
    }
    result = VALUES_1(temp);
  end_write_icp_remote_value:
    return result;
}

static Object Qread_icp_remote_value;  /* read-icp-remote-value */

/* READ-ICP-REMOTE-VALUE */
Object read_icp_remote_value()
{
    Object tracep, byte_count_before, current_icp_read_trace_level;
    Object item_copy_index_space, current_computation_flags, temp;
    Object result_of_read, resumable_icp_state_1, icp_suspend_1, top, test;
    Object gensymed_symbol, value;
    char temp_1;
    Declare_special(3);
    Object result;

    x_note_fn_call(157,102);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qremote_value,
			string_constant_5,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    2);
	      if (EQ(Qunbound,Item_copy_index_space)) {
		  item_copy_index_space = Nil;
		  current_computation_flags = Current_computation_flags;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
			  1);
		    PUSH_SPECIAL_WITH_SYMBOL(Item_copy_index_space,Qitem_copy_index_space,item_copy_index_space,
			    0);
		      if (ISVREF(Current_icp_socket,(SI_Long)48L))
			  Current_computation_flags = 
				  FIX(IFIX(Current_computation_flags) | 
				  (SI_Long)16L);
		      else
			  Current_computation_flags = 
				  FIX(IFIX(Current_computation_flags) &  
				  ~(SI_Long)16L);
		      temp = read_icp_remote_value_1();
		      if (Item_copy_index_space)
			  reclaim_index_space_1(Item_copy_index_space);
		      result_of_read = temp;
		    POP_SPECIAL();
		  POP_SPECIAL();
	      }
	      else
		  result_of_read = read_icp_remote_value_1();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qremote_value,string_constant_5,Qvalue,T,
			  result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else if (EQ(Qunbound,Item_copy_index_space)) {
	    item_copy_index_space = Nil;
	    current_computation_flags = Current_computation_flags;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		    1);
	      PUSH_SPECIAL_WITH_SYMBOL(Item_copy_index_space,Qitem_copy_index_space,item_copy_index_space,
		      0);
		if (ISVREF(Current_icp_socket,(SI_Long)48L))
		    Current_computation_flags = 
			    FIX(IFIX(Current_computation_flags) | 
			    (SI_Long)16L);
		else
		    Current_computation_flags = 
			    FIX(IFIX(Current_computation_flags) &  
			    ~(SI_Long)16L);
		temp = read_icp_remote_value_1();
		if (Item_copy_index_space)
		    reclaim_index_space_1(Item_copy_index_space);
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	else
	    temp = read_icp_remote_value_1();
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qread_icp_remote_value,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qread_icp_remote_value,top,Nil);
		goto end_read_icp_remote_value;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qremote_value,
			string_constant_5,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    2);
	      test = Nil;
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  test = resumable_icp_pop();
		  temp_1 = TRUEP(test);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if (temp_1 ? EQ(test,Qtrue) : EQ(Qunbound,
			  Item_copy_index_space)) {
		  item_copy_index_space = (resumable_icp_state_1 ? 
			  TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			  resumable_icp_pop() : Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Item_copy_index_space,Qitem_copy_index_space,item_copy_index_space,
			  1);
		    current_computation_flags = (resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()) 
			    ? resumable_icp_pop() : Current_computation_flags;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
			    0);
		      if ( !(resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil))) {
			  if (ISVREF(Current_icp_socket,(SI_Long)48L))
			      Current_computation_flags = 
				      FIX(IFIX(Current_computation_flags) 
				      | (SI_Long)16L);
			  else
			      Current_computation_flags = 
				      FIX(IFIX(Current_computation_flags) 
				      &  ~(SI_Long)16L);
		      }
		      if ((resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			      !TRUEP(resumable_icp_pop_list_if_end_marker()))
			  gensymed_symbol = resumable_icp_pop();
		      else {
			  value = read_icp_remote_value_1();
			  if (EQ(icp_suspend_1,value)) {
			      resumable_icp_push(Qresumable_icp_list_end);
			      resumable_icp_push(Current_computation_flags);
			      resumable_icp_push(Item_copy_index_space);
			      resumable_icp_push(Qtrue);
			      resumable_icp_push(Qread_icp_remote_value);
			      result = VALUES_1(Icp_suspend);
			      POP_SPECIAL();
			      POP_SPECIAL();
			      POP_SPECIAL();
			      goto end_read_icp_remote_value;
			  }
			  gensymed_symbol = value;
		      }
		      if (Item_copy_index_space)
			  reclaim_index_space_1(Item_copy_index_space);
		      result_of_read = gensymed_symbol;
		    POP_SPECIAL();
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_remote_value_1();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qfalse);
		      resumable_icp_push(Qread_icp_remote_value);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_remote_value;
		  }
		  result_of_read = value;
	      }
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qremote_value,string_constant_5,Qvalue,T,
			  result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    test = Nil;
	    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) {
		test = resumable_icp_pop();
		temp_1 = TRUEP(test);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? EQ(test,Qtrue) : EQ(Qunbound,Item_copy_index_space)) {
		item_copy_index_space = (resumable_icp_state_1 ? 
			TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			resumable_icp_pop() : Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Item_copy_index_space,Qitem_copy_index_space,item_copy_index_space,
			1);
		  current_computation_flags = (resumable_icp_state_1 ? 
			  TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			  resumable_icp_pop() : Current_computation_flags;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
			  0);
		    if ( !(resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil))) {
			if (ISVREF(Current_icp_socket,(SI_Long)48L))
			    Current_computation_flags = 
				    FIX(IFIX(Current_computation_flags) | 
				    (SI_Long)16L);
			else
			    Current_computation_flags = 
				    FIX(IFIX(Current_computation_flags) &  
				    ~(SI_Long)16L);
		    }
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()))
			gensymed_symbol = resumable_icp_pop();
		    else {
			value = read_icp_remote_value_1();
			if (EQ(icp_suspend_1,value)) {
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(Current_computation_flags);
			    resumable_icp_push(Item_copy_index_space);
			    resumable_icp_push(Qtrue);
			    resumable_icp_push(Qread_icp_remote_value);
			    result = VALUES_1(Icp_suspend);
			    POP_SPECIAL();
			    POP_SPECIAL();
			    goto end_read_icp_remote_value;
			}
			gensymed_symbol = value;
		    }
		    if (Item_copy_index_space)
			reclaim_index_space_1(Item_copy_index_space);
		    temp = gensymed_symbol;
		  POP_SPECIAL();
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_remote_value_1();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qfalse);
		    resumable_icp_push(Qread_icp_remote_value);
		    result = VALUES_1(Icp_suspend);
		    goto end_read_icp_remote_value;
		}
		temp = value;
	    }
	}
    }
    result = VALUES_1(temp);
  end_read_icp_remote_value:
    return result;
}

static Object Qgsi_permanent_remote_value;  /* gsi-permanent-remote-value */

static Object Qread_icp_gsi_permanent_remote_value;  /* read-icp-gsi-permanent-remote-value */

/* READ-ICP-GSI-PERMANENT-REMOTE-VALUE */
Object read_icp_gsi_permanent_remote_value()
{
    Object tracep, byte_count_before, current_icp_read_trace_level;
    Object result_of_read, temp, resumable_icp_state_1, icp_suspend_1, top;
    Object value;
    Declare_special(1);
    Object result;

    x_note_fn_call(157,103);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qgsi_permanent_remote_value,
			string_constant_5,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      result_of_read = read_icp_remote_value();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qgsi_permanent_remote_value,string_constant_5,
			  Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else
	    temp = read_icp_remote_value();
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qread_icp_gsi_permanent_remote_value,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qread_icp_gsi_permanent_remote_value,top,Nil);
		goto end_read_icp_gsi_permanent_remote_value;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qgsi_permanent_remote_value,
			string_constant_5,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      value = read_icp_remote_value();
	      if (EQ(icp_suspend_1,value)) {
		  resumable_icp_push(Qread_icp_gsi_permanent_remote_value);
		  result = VALUES_1(Icp_suspend);
		  POP_SPECIAL();
		  goto end_read_icp_gsi_permanent_remote_value;
	      }
	      result_of_read = value;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qgsi_permanent_remote_value,string_constant_5,
			  Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    value = read_icp_remote_value();
	    if (EQ(icp_suspend_1,value)) {
		resumable_icp_push(Qread_icp_gsi_permanent_remote_value);
		result = VALUES_1(Icp_suspend);
		goto end_read_icp_gsi_permanent_remote_value;
	    }
	    temp = value;
	}
    }
    result = VALUES_1(temp);
  end_read_icp_gsi_permanent_remote_value:
    return result;
}

static Object Qwrite_icp_gsi_permanent_remote_value;  /* write-icp-gsi-permanent-remote-value */

/* WRITE-ICP-GSI-PERMANENT-REMOTE-VALUE */
Object write_icp_gsi_permanent_remote_value(gsi_permanent_remote_value)
    Object gsi_permanent_remote_value;
{
    Object tracep, byte_count_before, current_icp_write_trace_level;
    Object result_of_write, temp, resumable_icp_state_1, icp_suspend_1, top;
    Object value;
    Declare_special(1);
    Object result;

    x_note_fn_call(157,104);
    if (Disable_resumability) {
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,Qgsi_permanent_remote_value,
			string_constant_5,Qvalue,T,
			gsi_permanent_remote_value,Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      result_of_write = 
		      write_icp_remote_value(gsi_permanent_remote_value);
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qgsi_permanent_remote_value,string_constant_5,
			  Qvalue,Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else
	    temp = write_icp_remote_value(gsi_permanent_remote_value);
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qwrite_icp_gsi_permanent_remote_value,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qwrite_icp_gsi_permanent_remote_value,top,Nil);
		goto end_write_icp_gsi_permanent_remote_value;
	    }
	}
	gsi_permanent_remote_value = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : gsi_permanent_remote_value;
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,Qgsi_permanent_remote_value,
			string_constant_5,Qvalue,T,
			gsi_permanent_remote_value,Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      value = write_icp_remote_value(gsi_permanent_remote_value);
	      if (EQ(icp_suspend_1,value)) {
		  resumable_icp_push(gsi_permanent_remote_value);
		  resumable_icp_push(Qwrite_icp_gsi_permanent_remote_value);
		  result = VALUES_1(Icp_suspend);
		  POP_SPECIAL();
		  goto end_write_icp_gsi_permanent_remote_value;
	      }
	      result_of_write = value;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qgsi_permanent_remote_value,string_constant_5,
			  Qvalue,Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else {
	    value = write_icp_remote_value(gsi_permanent_remote_value);
	    if (EQ(icp_suspend_1,value)) {
		resumable_icp_push(gsi_permanent_remote_value);
		resumable_icp_push(Qwrite_icp_gsi_permanent_remote_value);
		result = VALUES_1(Icp_suspend);
		goto end_write_icp_gsi_permanent_remote_value;
	    }
	    temp = value;
	}
    }
    result = VALUES_1(temp);
  end_write_icp_gsi_permanent_remote_value:
    return result;
}

/* RECLAIM-REMOTE-VALUE */
Object reclaim_remote_value(remote_value)
    Object remote_value;
{
    x_note_fn_call(157,105);
    if ( !(FIXNUMP(remote_value) || SYMBOLP(remote_value) || 
	    SIMPLE_VECTOR_P(remote_value)))
	reclaim_if_evaluation_value_1(remote_value);
    return VALUES_1(Nil);
}

static Object Qevaluation_sequence;  /* evaluation-sequence */

static Object Qread_icp_evaluation_sequence;  /* read-icp-evaluation-sequence */

/* READ-ICP-EVALUATION-SEQUENCE */
Object read_icp_evaluation_sequence()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, temp;
    Object typetag, length_1, remote_value_known_typetag, value;
    Object converted_value, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object result_of_read, resumable_icp_state_1, icp_suspend_1, top, arg1;
    Object key, value_1;
    SI_Long i, ab_loop_bind_;
    Declare_special(2);
    Object result;

    x_note_fn_call(157,106);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qevaluation_sequence,
			string_constant_5,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      temp = read_icp_byte();
	      if ( !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) 
		      && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		  typetag = Nil;
	      else
		  switch (INTEGER_TO_CHAR(temp)) {
		    case 67:
		      typetag = read_icp_byte();
		      break;
		    case 49:
		      typetag = FIX((SI_Long)8L);
		      break;
		    default:
		      typetag = Nil;
		      break;
		  }
	      length_1 = read_icp_fixnum();
	      remote_value_known_typetag = IFIX(typetag) == (SI_Long)8L ? 
		      Nil : typetag;
	      PUSH_SPECIAL_WITH_SYMBOL(Remote_value_known_typetag,Qremote_value_known_typetag,remote_value_known_typetag,
		      0);
		i = (SI_Long)0L;
		ab_loop_bind_ = IFIX(length_1);
		value = Nil;
		converted_value = Nil;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ab_loopvar__2 = Nil;
	      next_loop:
		if (i >= ab_loop_bind_)
		    goto end_loop;
		value = read_icp_remote_value();
		converted_value = CONSP(value) && EQ(M_CDR(value),
			Qunsigned_vector_16) ? M_CAR(value) : value;
		ab_loopvar__2 = eval_cons_1(converted_value,Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
		i = i + (SI_Long)1L;
		goto next_loop;
	      end_loop:
		temp = ab_loopvar_;
		goto end_1;
		temp = Qnil;
	      end_1:;
	      POP_SPECIAL();
	      result_of_read = allocate_evaluation_sequence(temp);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qevaluation_sequence,string_constant_5,Qvalue,T,
			  result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    temp = read_icp_byte();
	    if ( !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
		    FIXNUM_LE(temp,FIX((SI_Long)127L))))
		typetag = Nil;
	    else
		switch (INTEGER_TO_CHAR(temp)) {
		  case 67:
		    typetag = read_icp_byte();
		    break;
		  case 49:
		    typetag = FIX((SI_Long)8L);
		    break;
		  default:
		    typetag = Nil;
		    break;
		}
	    length_1 = read_icp_fixnum();
	    remote_value_known_typetag = IFIX(typetag) == (SI_Long)8L ? 
		    Nil : typetag;
	    PUSH_SPECIAL_WITH_SYMBOL(Remote_value_known_typetag,Qremote_value_known_typetag,remote_value_known_typetag,
		    0);
	      i = (SI_Long)0L;
	      ab_loop_bind_ = IFIX(length_1);
	      value = Nil;
	      converted_value = Nil;
	      ab_loopvar_ = Nil;
	      ab_loopvar__1 = Nil;
	      ab_loopvar__2 = Nil;
	    next_loop_1:
	      if (i >= ab_loop_bind_)
		  goto end_loop_1;
	      value = read_icp_remote_value();
	      converted_value = CONSP(value) && EQ(M_CDR(value),
		      Qunsigned_vector_16) ? M_CAR(value) : value;
	      ab_loopvar__2 = eval_cons_1(converted_value,Nil);
	      if (ab_loopvar__1)
		  M_CDR(ab_loopvar__1) = ab_loopvar__2;
	      else
		  ab_loopvar_ = ab_loopvar__2;
	      ab_loopvar__1 = ab_loopvar__2;
	      i = i + (SI_Long)1L;
	      goto next_loop_1;
	    end_loop_1:
	      temp = ab_loopvar_;
	      goto end_2;
	      temp = Qnil;
	    end_2:;
	    POP_SPECIAL();
	    temp = allocate_evaluation_sequence(temp);
	}
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qread_icp_evaluation_sequence,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qread_icp_evaluation_sequence,top,Nil);
		goto end_read_icp_evaluation_sequence;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qevaluation_sequence,
			string_constant_5,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  arg1 = resumable_icp_pop();
	      else {
		  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			   TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()))
		      typetag = resumable_icp_pop();
		  else {
		      if ((resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			      !TRUEP(resumable_icp_pop_list_if_end_marker()))
			  key = resumable_icp_pop();
		      else {
			  value_1 = read_icp_byte();
			  if (EQ(icp_suspend_1,value_1)) {
			      resumable_icp_push(Qresumable_icp_list_end);
			      resumable_icp_push(Qresumable_icp_list_end);
			      resumable_icp_push(Qresumable_icp_list_end);
			      resumable_icp_push(Qread_icp_evaluation_sequence);
			      result = VALUES_1(Icp_suspend);
			      POP_SPECIAL();
			      goto end_read_icp_evaluation_sequence;
			  }
			  key = value_1;
		      }
		      if ( !(FIXNUMP(key) && FIXNUM_LE(FIX((SI_Long)-128L),
			      key) && FIXNUM_LE(key,FIX((SI_Long)127L))))
			  typetag = Nil;
		      else
			  switch (INTEGER_TO_CHAR(key)) {
			    case 67:
			      value_1 = read_icp_byte();
			      if (EQ(icp_suspend_1,value_1)) {
				  resumable_icp_push(key);
				  resumable_icp_push(Qresumable_icp_list_end);
				  resumable_icp_push(Qresumable_icp_list_end);
				  resumable_icp_push(Qread_icp_evaluation_sequence);
				  result = VALUES_1(Icp_suspend);
				  POP_SPECIAL();
				  goto end_read_icp_evaluation_sequence;
			      }
			      typetag = value_1;
			      break;
			    case 49:
			      typetag = FIX((SI_Long)8L);
			      break;
			    default:
			      typetag = Nil;
			      break;
			  }
		  }
		  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			   TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()))
		      length_1 = resumable_icp_pop();
		  else {
		      value_1 = read_icp_fixnum();
		      if (EQ(icp_suspend_1,value_1)) {
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(typetag);
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qread_icp_evaluation_sequence);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_read_icp_evaluation_sequence;
		      }
		      length_1 = value_1;
		  }
		  remote_value_known_typetag = (resumable_icp_state_1 ? 
			  TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			  resumable_icp_pop() : IFIX(typetag) == 
			  (SI_Long)8L ? Nil : typetag;
		  PUSH_SPECIAL_WITH_SYMBOL(Remote_value_known_typetag,Qremote_value_known_typetag,remote_value_known_typetag,
			  0);
		    i = (resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()) 
			    ? IFIX(resumable_icp_pop()) : (SI_Long)0L;
		    ab_loop_bind_ = (resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()) 
			    ? IFIX(resumable_icp_pop()) : IFIX(length_1);
		    value = (resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()) 
			    ? resumable_icp_pop() : Nil;
		    converted_value = (resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()) 
			    ? resumable_icp_pop() : Nil;
		    ab_loopvar_ = (resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()) 
			    ? resumable_icp_pop() : Nil;
		    ab_loopvar__1 = (resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()) 
			    ? resumable_icp_pop() : Nil;
		    ab_loopvar__2 = (resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()) 
			    ? resumable_icp_pop() : Nil;
		    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
			    : TRUEP(Nil))
			goto resume;
		  next_loop_2:
		    if (i >= ab_loop_bind_)
			goto end_loop_2;
		  resume:
		    value_1 = read_icp_remote_value();
		    if (EQ(icp_suspend_1,value_1)) {
			resumable_icp_push(ab_loopvar__2);
			resumable_icp_push(ab_loopvar__1);
			resumable_icp_push(ab_loopvar_);
			resumable_icp_push(converted_value);
			resumable_icp_push(value);
			resumable_icp_push(FIX(ab_loop_bind_));
			resumable_icp_push(FIX(i));
			resumable_icp_push(Remote_value_known_typetag);
			resumable_icp_push(length_1);
			resumable_icp_push(typetag);
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qread_icp_evaluation_sequence);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_read_icp_evaluation_sequence;
		    }
		    value = value_1;
		    converted_value = CONSP(value) && EQ(M_CDR(value),
			    Qunsigned_vector_16) ? M_CAR(value) : value;
		    ab_loopvar__2 = eval_cons_1(converted_value,Nil);
		    if (ab_loopvar__1)
			M_CDR(ab_loopvar__1) = ab_loopvar__2;
		    else
			ab_loopvar_ = ab_loopvar__2;
		    ab_loopvar__1 = ab_loopvar__2;
		    i = i + (SI_Long)1L;
		    goto next_loop_2;
		  end_loop_2:
		    arg1 = ab_loopvar_;
		    goto end_3;
		    arg1 = Qnil;
		  end_3:;
		  POP_SPECIAL();
	      }
	      result_of_read = allocate_evaluation_sequence(arg1);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qevaluation_sequence,string_constant_5,Qvalue,T,
			  result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		arg1 = resumable_icp_pop();
	    else {
		if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()))
		    typetag = resumable_icp_pop();
		else {
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()))
			key = resumable_icp_pop();
		    else {
			value_1 = read_icp_byte();
			if (EQ(icp_suspend_1,value_1)) {
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(Qread_icp_evaluation_sequence);
			    result = VALUES_1(Icp_suspend);
			    goto end_read_icp_evaluation_sequence;
			}
			key = value_1;
		    }
		    if ( !(FIXNUMP(key) && FIXNUM_LE(FIX((SI_Long)-128L),
			    key) && FIXNUM_LE(key,FIX((SI_Long)127L))))
			typetag = Nil;
		    else
			switch (INTEGER_TO_CHAR(key)) {
			  case 67:
			    value_1 = read_icp_byte();
			    if (EQ(icp_suspend_1,value_1)) {
				resumable_icp_push(key);
				resumable_icp_push(Qresumable_icp_list_end);
				resumable_icp_push(Qresumable_icp_list_end);
				resumable_icp_push(Qread_icp_evaluation_sequence);
				result = VALUES_1(Icp_suspend);
				goto end_read_icp_evaluation_sequence;
			    }
			    typetag = value_1;
			    break;
			  case 49:
			    typetag = FIX((SI_Long)8L);
			    break;
			  default:
			    typetag = Nil;
			    break;
			}
		}
		if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()))
		    length_1 = resumable_icp_pop();
		else {
		    value_1 = read_icp_fixnum();
		    if (EQ(icp_suspend_1,value_1)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(typetag);
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qread_icp_evaluation_sequence);
			result = VALUES_1(Icp_suspend);
			goto end_read_icp_evaluation_sequence;
		    }
		    length_1 = value_1;
		}
		remote_value_known_typetag = (resumable_icp_state_1 ? 
			TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			resumable_icp_pop() : IFIX(typetag) == (SI_Long)8L 
			? Nil : typetag;
		PUSH_SPECIAL_WITH_SYMBOL(Remote_value_known_typetag,Qremote_value_known_typetag,remote_value_known_typetag,
			0);
		  i = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			   TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			  IFIX(resumable_icp_pop()) : (SI_Long)0L;
		  ab_loop_bind_ = (resumable_icp_state_1 ? 
			  TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			  IFIX(resumable_icp_pop()) : IFIX(length_1);
		  value = (resumable_icp_state_1 ? 
			  TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			  resumable_icp_pop() : Nil;
		  converted_value = (resumable_icp_state_1 ? 
			  TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			  resumable_icp_pop() : Nil;
		  ab_loopvar_ = (resumable_icp_state_1 ? 
			  TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			  resumable_icp_pop() : Nil;
		  ab_loopvar__1 = (resumable_icp_state_1 ? 
			  TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			  resumable_icp_pop() : Nil;
		  ab_loopvar__2 = (resumable_icp_state_1 ? 
			  TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			  resumable_icp_pop() : Nil;
		  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			  TRUEP(Nil))
		      goto resume_1;
		next_loop_3:
		  if (i >= ab_loop_bind_)
		      goto end_loop_3;
		resume_1:
		  value_1 = read_icp_remote_value();
		  if (EQ(icp_suspend_1,value_1)) {
		      resumable_icp_push(ab_loopvar__2);
		      resumable_icp_push(ab_loopvar__1);
		      resumable_icp_push(ab_loopvar_);
		      resumable_icp_push(converted_value);
		      resumable_icp_push(value);
		      resumable_icp_push(FIX(ab_loop_bind_));
		      resumable_icp_push(FIX(i));
		      resumable_icp_push(Remote_value_known_typetag);
		      resumable_icp_push(length_1);
		      resumable_icp_push(typetag);
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qread_icp_evaluation_sequence);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_evaluation_sequence;
		  }
		  value = value_1;
		  converted_value = CONSP(value) && EQ(M_CDR(value),
			  Qunsigned_vector_16) ? M_CAR(value) : value;
		  ab_loopvar__2 = eval_cons_1(converted_value,Nil);
		  if (ab_loopvar__1)
		      M_CDR(ab_loopvar__1) = ab_loopvar__2;
		  else
		      ab_loopvar_ = ab_loopvar__2;
		  ab_loopvar__1 = ab_loopvar__2;
		  i = i + (SI_Long)1L;
		  goto next_loop_3;
		end_loop_3:
		  arg1 = ab_loopvar_;
		  goto end_4;
		  arg1 = Qnil;
		end_4:;
		POP_SPECIAL();
	    }
	    temp = allocate_evaluation_sequence(arg1);
	}
    }
    result = VALUES_1(temp);
  end_read_icp_evaluation_sequence:
    return result;
}

static Object Qwrite_icp_evaluation_sequence;  /* write-icp-evaluation-sequence */

/* WRITE-ICP-EVALUATION-SEQUENCE */
Object write_icp_evaluation_sequence(evaluation_sequence)
    Object evaluation_sequence;
{
    Object tracep, byte_count_before, current_icp_write_trace_level;
    Object known_type, type, gensymed_symbol, held_vector, value, elt_1;
    Object validated_elt, temp, typecode, cdr_1, thing, internal_value;
    Object result_1, typetag, remote_value_known_typetag, result_of_write;
    Object resumable_icp_state_1, icp_suspend_1, top, test, v1, v2, v3;
    SI_Long next_index, length_1, length_2;
    char temp_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(157,107);
    if (Disable_resumability) {
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,Qevaluation_sequence,
			string_constant_5,Qvalue,T,evaluation_sequence,Nil,
			Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    1);
	      known_type = Nil;
	      type = known_type;
	      gensymed_symbol = evaluation_sequence;
	      held_vector = Nil;
	      next_index = (SI_Long)1L;
	      length_1 = (SI_Long)0L;
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
		      (SI_Long)10L) + (SI_Long)2L),next_index & 
		      (SI_Long)1023L);
	      validated_elt = elt_1 ? 
		      validate_item_or_evaluation_value(elt_1,Nil,Nil) : Nil;
	      next_index = next_index + (SI_Long)1L;
	      value = validated_elt;
	      if (Remote_value_known_typetag) {
		  temp = Remote_value_known_typetag;
		  if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
			  FIXNUM_LE(temp,FIX((SI_Long)127L))))
		      typecode = Nil;
		  else
		      switch (INTEGER_TO_CHAR(temp)) {
			case 0:
			  typecode = Qnull;
			  break;
			case 1:
			  typecode = Qinteger;
			  break;
			case 51:
			  typecode = Qlong;
			  break;
			case 5:
			  typecode = Qtruth_value;
			  break;
			case 6:
			  typecode = Qfloat;
			  break;
			case 4:
			  typecode = Qtext;
			  break;
			case 11:
			  typecode = Qunsigned_short_vector;
			  break;
			default:
			  typecode = Nil;
			  break;
		      }
	      }
	      else if (Remote_value_is_binary_p)
		  typecode = Qunsigned_short_vector;
	      else if ( !TRUEP(value))
		  typecode = Qnull;
	      else if (FIXNUMP(value))
		  typecode = Qinteger;
	      else if (INLINE_LONG_VECTOR_P(value) != (SI_Long)0L && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		  typecode = Qlong;
	      else if (CONSP(value)) {
		  cdr_1 = M_CDR(value);
		  if (EQ(cdr_1,Qtruth_value))
		      typecode = Qtruth_value;
		  else if (EQ(cdr_1,Qsequence))
		      typecode = Qsequence;
		  else if (EQ(cdr_1,Qab_structure))
		      typecode = Qab_structure;
		  else if (EQ(cdr_1,Qunsigned_vector_16))
		      typecode = Qunsigned_short_vector;
		  else
		      typecode = Qnull;
	      }
	      else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L 
		      && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		  typecode = Qfloat;
	      else if (value && SYMBOLP(value))
		  typecode = Qsymbol;
	      else {
		  if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) != (SI_Long)0L) {
		      length_2 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value));
		      temp_1 = (SI_Long)1L == UBYTE_16_ISAREF_1(value,
			      UBYTE_16_ISAREF_1(value,length_2 - 
			      (SI_Long)2L) + ((UBYTE_16_ISAREF_1(value,
			      length_2 - (SI_Long)1L) & (SI_Long)8191L) << 
			      (SI_Long)16L));
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  if (temp_1)
		      typecode = Qunsigned_short_vector;
		  else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) != 
			  (SI_Long)0L)
		      typecode = Qtext;
		  else {
		      if (SIMPLE_VECTOR_P(value) && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > 
			      (SI_Long)2L) {
			  temp_1 = EQ(ISVREF(value,(SI_Long)1L),
				  Qavailable_frame_vector);
			  if (temp_1);
			  else {
			      thing = ISVREF(value,(SI_Long)1L);
			      temp_1 = SIMPLE_VECTOR_P(thing) ? 
				      EQ(ISVREF(thing,(SI_Long)0L),
				      Qg2_defstruct_structure_name_class_description_g2_struct) 
				      : TRUEP(Qnil);
			  }
		      }
		      else
			  temp_1 = TRUEP(Nil);
		      if (temp_1)
			  typecode = Qitem;
		      else if (SIMPLE_VECTOR_P(value) && EQ(ISVREF(value,
			      (SI_Long)0L),
			      Qg2_defstruct_structure_name_class_description_g2_struct))
			  typecode = Qitem;
		      else
			  typecode = Qnull;
		  }
	      }
	      if (EQ(typecode,Qnull)) {
		  internal_value = value;
		  if ( !TRUEP(type)) {
		      type = Qnull;
		      result_1 = type;
		  }
		  else if ( !EQ(type,Qnull)) {
		      type = Qt;
		      goto end_loop;
		  }
		  else
		      result_1 = Qnil;
	      }
	      else if (EQ(typecode,Qinteger)) {
		  internal_value = value;
		  if ( !TRUEP(type)) {
		      type = Qinteger;
		      result_1 = type;
		  }
		  else if ( !EQ(type,Qinteger)) {
		      type = Qt;
		      goto end_loop;
		  }
		  else
		      result_1 = Qnil;
	      }
	      else if (EQ(typecode,Qtruth_value)) {
		  internal_value = M_CAR(value);
		  if ( !TRUEP(type)) {
		      type = Qtruth_value;
		      result_1 = type;
		  }
		  else if ( !EQ(type,Qtruth_value)) {
		      type = Qt;
		      goto end_loop;
		  }
		  else
		      result_1 = Qnil;
	      }
	      else if (EQ(typecode,Qfloat)) {
		  internal_value = value;
		  if ( !TRUEP(type)) {
		      type = Qfloat;
		      result_1 = type;
		  }
		  else if ( !EQ(type,Qfloat)) {
		      type = Qt;
		      goto end_loop;
		  }
		  else
		      result_1 = Qnil;
	      }
	      else if (EQ(typecode,Qtext)) {
		  internal_value = value;
		  if ( !TRUEP(type)) {
		      type = Qtext;
		      result_1 = type;
		  }
		  else if ( !EQ(type,Qtext)) {
		      type = Qt;
		      goto end_loop;
		  }
		  else
		      result_1 = Qnil;
	      }
	      else if (EQ(typecode,Qunsigned_short_vector)) {
		  internal_value = CONSP(value) ? M_CAR(value) : value;
		  if ( !TRUEP(type)) {
		      type = Qunsigned_short_vector;
		      result_1 = type;
		  }
		  else if ( !EQ(type,Qunsigned_short_vector)) {
		      type = Qt;
		      goto end_loop;
		  }
		  else
		      result_1 = Qnil;
	      }
	      else {
		  type = Qt;
		  goto end_loop;
	      }
	      goto next_loop;
	    end_loop:;
	      if (EQ(type,Qnull))
		  typetag = FIX((SI_Long)0L);
	      else if (EQ(type,Qinteger))
		  typetag = FIX((SI_Long)1L);
	      else if (EQ(type,Qlong))
		  typetag = FIX((SI_Long)51L);
	      else if (EQ(type,Qtruth_value))
		  typetag = FIX((SI_Long)5L);
	      else if (EQ(type,Qfloat))
		  typetag = FIX((SI_Long)6L);
	      else if (EQ(type,Qtext))
		  typetag = FIX((SI_Long)4L);
	      else if (EQ(type,Qunsigned_short_vector))
		  typetag = FIX((SI_Long)11L);
	      else
		  typetag = Nil;
	      remote_value_known_typetag = typetag;
	      PUSH_SPECIAL_WITH_SYMBOL(Remote_value_known_typetag,Qremote_value_known_typetag,remote_value_known_typetag,
		      0);
		if (typetag) {
		    write_icp_byte(FIX((SI_Long)67L));
		    write_icp_byte(typetag);
		}
		else
		    write_icp_byte(FIX((SI_Long)49L));
		write_icp_fixnum(FIXNUM_SUB1(ISVREF(M_CAR(evaluation_sequence),
			(SI_Long)1L)));
		gensymed_symbol = evaluation_sequence;
		held_vector = Nil;
		next_index = (SI_Long)1L;
		length_1 = (SI_Long)0L;
		value = Nil;
		held_vector = M_CAR(gensymed_symbol);
		length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	      next_loop_1:
		if (next_index >= length_1)
		    goto end_loop_1;
		elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
			Maximum_in_place_array_size) ? ISVREF(held_vector,
			next_index + IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector,(next_index >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),next_index & 
			(SI_Long)1023L);
		validated_elt = elt_1 ? 
			validate_item_or_evaluation_value(elt_1,Nil,Nil) : Nil;
		next_index = next_index + (SI_Long)1L;
		value = validated_elt;
		write_icp_remote_value(value);
		goto next_loop_1;
	      end_loop_1:
		result_of_write = Qnil;
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qevaluation_sequence,string_constant_5,Qvalue,
			  Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else {
	    known_type = Nil;
	    type = known_type;
	    gensymed_symbol = evaluation_sequence;
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_1 = (SI_Long)0L;
	    value = Nil;
	    held_vector = M_CAR(gensymed_symbol);
	    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	  next_loop_2:
	    if (next_index >= length_1)
		goto end_loop_2;
	    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    next_index + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	    validated_elt = elt_1 ? 
		    validate_item_or_evaluation_value(elt_1,Nil,Nil) : Nil;
	    next_index = next_index + (SI_Long)1L;
	    value = validated_elt;
	    if (Remote_value_known_typetag) {
		temp = Remote_value_known_typetag;
		if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
			FIXNUM_LE(temp,FIX((SI_Long)127L))))
		    typecode = Nil;
		else
		    switch (INTEGER_TO_CHAR(temp)) {
		      case 0:
			typecode = Qnull;
			break;
		      case 1:
			typecode = Qinteger;
			break;
		      case 51:
			typecode = Qlong;
			break;
		      case 5:
			typecode = Qtruth_value;
			break;
		      case 6:
			typecode = Qfloat;
			break;
		      case 4:
			typecode = Qtext;
			break;
		      case 11:
			typecode = Qunsigned_short_vector;
			break;
		      default:
			typecode = Nil;
			break;
		    }
	    }
	    else if (Remote_value_is_binary_p)
		typecode = Qunsigned_short_vector;
	    else if ( !TRUEP(value))
		typecode = Qnull;
	    else if (FIXNUMP(value))
		typecode = Qinteger;
	    else if (INLINE_LONG_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		typecode = Qlong;
	    else if (CONSP(value)) {
		cdr_1 = M_CDR(value);
		if (EQ(cdr_1,Qtruth_value))
		    typecode = Qtruth_value;
		else if (EQ(cdr_1,Qsequence))
		    typecode = Qsequence;
		else if (EQ(cdr_1,Qab_structure))
		    typecode = Qab_structure;
		else if (EQ(cdr_1,Qunsigned_vector_16))
		    typecode = Qunsigned_short_vector;
		else
		    typecode = Qnull;
	    }
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		typecode = Qfloat;
	    else if (value && SYMBOLP(value))
		typecode = Qsymbol;
	    else {
		if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) != (SI_Long)0L) {
		    length_2 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value));
		    temp_1 = (SI_Long)1L == UBYTE_16_ISAREF_1(value,
			    UBYTE_16_ISAREF_1(value,length_2 - 
			    (SI_Long)2L) + ((UBYTE_16_ISAREF_1(value,
			    length_2 - (SI_Long)1L) & (SI_Long)8191L) << 
			    (SI_Long)16L));
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1)
		    typecode = Qunsigned_short_vector;
		else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) != 
			(SI_Long)0L)
		    typecode = Qtext;
		else {
		    if (SIMPLE_VECTOR_P(value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > 
			    (SI_Long)2L) {
			temp_1 = EQ(ISVREF(value,(SI_Long)1L),
				Qavailable_frame_vector);
			if (temp_1);
			else {
			    thing = ISVREF(value,(SI_Long)1L);
			    temp_1 = SIMPLE_VECTOR_P(thing) ? 
				    EQ(ISVREF(thing,(SI_Long)0L),
				    Qg2_defstruct_structure_name_class_description_g2_struct) 
				    : TRUEP(Qnil);
			}
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1)
			typecode = Qitem;
		    else if (SIMPLE_VECTOR_P(value) && EQ(ISVREF(value,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct))
			typecode = Qitem;
		    else
			typecode = Qnull;
		}
	    }
	    if (EQ(typecode,Qnull)) {
		internal_value = value;
		if ( !TRUEP(type)) {
		    type = Qnull;
		    result_1 = type;
		}
		else if ( !EQ(type,Qnull)) {
		    type = Qt;
		    goto end_loop_2;
		}
		else
		    result_1 = Qnil;
	    }
	    else if (EQ(typecode,Qinteger)) {
		internal_value = value;
		if ( !TRUEP(type)) {
		    type = Qinteger;
		    result_1 = type;
		}
		else if ( !EQ(type,Qinteger)) {
		    type = Qt;
		    goto end_loop_2;
		}
		else
		    result_1 = Qnil;
	    }
	    else if (EQ(typecode,Qtruth_value)) {
		internal_value = M_CAR(value);
		if ( !TRUEP(type)) {
		    type = Qtruth_value;
		    result_1 = type;
		}
		else if ( !EQ(type,Qtruth_value)) {
		    type = Qt;
		    goto end_loop_2;
		}
		else
		    result_1 = Qnil;
	    }
	    else if (EQ(typecode,Qfloat)) {
		internal_value = value;
		if ( !TRUEP(type)) {
		    type = Qfloat;
		    result_1 = type;
		}
		else if ( !EQ(type,Qfloat)) {
		    type = Qt;
		    goto end_loop_2;
		}
		else
		    result_1 = Qnil;
	    }
	    else if (EQ(typecode,Qtext)) {
		internal_value = value;
		if ( !TRUEP(type)) {
		    type = Qtext;
		    result_1 = type;
		}
		else if ( !EQ(type,Qtext)) {
		    type = Qt;
		    goto end_loop_2;
		}
		else
		    result_1 = Qnil;
	    }
	    else if (EQ(typecode,Qunsigned_short_vector)) {
		internal_value = CONSP(value) ? M_CAR(value) : value;
		if ( !TRUEP(type)) {
		    type = Qunsigned_short_vector;
		    result_1 = type;
		}
		else if ( !EQ(type,Qunsigned_short_vector)) {
		    type = Qt;
		    goto end_loop_2;
		}
		else
		    result_1 = Qnil;
	    }
	    else {
		type = Qt;
		goto end_loop_2;
	    }
	    goto next_loop_2;
	  end_loop_2:;
	    if (EQ(type,Qnull))
		typetag = FIX((SI_Long)0L);
	    else if (EQ(type,Qinteger))
		typetag = FIX((SI_Long)1L);
	    else if (EQ(type,Qlong))
		typetag = FIX((SI_Long)51L);
	    else if (EQ(type,Qtruth_value))
		typetag = FIX((SI_Long)5L);
	    else if (EQ(type,Qfloat))
		typetag = FIX((SI_Long)6L);
	    else if (EQ(type,Qtext))
		typetag = FIX((SI_Long)4L);
	    else if (EQ(type,Qunsigned_short_vector))
		typetag = FIX((SI_Long)11L);
	    else
		typetag = Nil;
	    remote_value_known_typetag = typetag;
	    PUSH_SPECIAL_WITH_SYMBOL(Remote_value_known_typetag,Qremote_value_known_typetag,remote_value_known_typetag,
		    0);
	      if (typetag) {
		  write_icp_byte(FIX((SI_Long)67L));
		  write_icp_byte(typetag);
	      }
	      else
		  write_icp_byte(FIX((SI_Long)49L));
	      write_icp_fixnum(FIXNUM_SUB1(ISVREF(M_CAR(evaluation_sequence),
		      (SI_Long)1L)));
	      gensymed_symbol = evaluation_sequence;
	      held_vector = Nil;
	      next_index = (SI_Long)1L;
	      length_1 = (SI_Long)0L;
	      value = Nil;
	      held_vector = M_CAR(gensymed_symbol);
	      length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	    next_loop_3:
	      if (next_index >= length_1)
		  goto end_loop_3;
	      elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		      Maximum_in_place_array_size) ? ISVREF(held_vector,
		      next_index + IFIX(Managed_array_index_offset)) : 
		      ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L),next_index & 
		      (SI_Long)1023L);
	      validated_elt = elt_1 ? 
		      validate_item_or_evaluation_value(elt_1,Nil,Nil) : Nil;
	      next_index = next_index + (SI_Long)1L;
	      value = validated_elt;
	      write_icp_remote_value(value);
	      goto next_loop_3;
	    end_loop_3:
	      temp = Qnil;
	    POP_SPECIAL();
	}
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qwrite_icp_evaluation_sequence,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qwrite_icp_evaluation_sequence,top,Nil);
		goto end_write_icp_evaluation_sequence;
	    }
	}
	evaluation_sequence = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : evaluation_sequence;
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,Qevaluation_sequence,
			string_constant_5,Qvalue,T,evaluation_sequence,Nil,
			Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    1);
	      known_type = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  typetag = resumable_icp_pop();
	      else {
		  type = (resumable_icp_state_1 ? 
			  TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			  resumable_icp_pop() : known_type;
		  gensymed_symbol = evaluation_sequence;
		  held_vector = Nil;
		  next_index = (SI_Long)1L;
		  length_1 = (SI_Long)0L;
		  value = Nil;
		  held_vector = M_CAR(gensymed_symbol);
		  length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
		next_loop_4:
		  if (next_index >= length_1)
		      goto end_loop_4;
		  elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
			  Maximum_in_place_array_size) ? 
			  ISVREF(held_vector,next_index + 
			  IFIX(Managed_array_index_offset)) : 
			  ISVREF(ISVREF(held_vector,(next_index >>  -  - 
			  (SI_Long)10L) + (SI_Long)2L),next_index & 
			  (SI_Long)1023L);
		  validated_elt = elt_1 ? 
			  validate_item_or_evaluation_value(elt_1,Nil,Nil) 
			  : Nil;
		  next_index = next_index + (SI_Long)1L;
		  value = validated_elt;
		  if (Remote_value_known_typetag) {
		      temp = Remote_value_known_typetag;
		      if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
			      FIXNUM_LE(temp,FIX((SI_Long)127L))))
			  typecode = Nil;
		      else
			  switch (INTEGER_TO_CHAR(temp)) {
			    case 0:
			      typecode = Qnull;
			      break;
			    case 1:
			      typecode = Qinteger;
			      break;
			    case 51:
			      typecode = Qlong;
			      break;
			    case 5:
			      typecode = Qtruth_value;
			      break;
			    case 6:
			      typecode = Qfloat;
			      break;
			    case 4:
			      typecode = Qtext;
			      break;
			    case 11:
			      typecode = Qunsigned_short_vector;
			      break;
			    default:
			      typecode = Nil;
			      break;
			  }
		  }
		  else if (Remote_value_is_binary_p)
		      typecode = Qunsigned_short_vector;
		  else if ( !TRUEP(value))
		      typecode = Qnull;
		  else if (FIXNUMP(value))
		      typecode = Qinteger;
		  else if (INLINE_LONG_VECTOR_P(value) != (SI_Long)0L && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			  (SI_Long)1L)
		      typecode = Qlong;
		  else if (CONSP(value)) {
		      cdr_1 = M_CDR(value);
		      if (EQ(cdr_1,Qtruth_value))
			  typecode = Qtruth_value;
		      else if (EQ(cdr_1,Qsequence))
			  typecode = Qsequence;
		      else if (EQ(cdr_1,Qab_structure))
			  typecode = Qab_structure;
		      else if (EQ(cdr_1,Qunsigned_vector_16))
			  typecode = Qunsigned_short_vector;
		      else
			  typecode = Qnull;
		  }
		  else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != 
			  (SI_Long)0L && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			  (SI_Long)1L)
		      typecode = Qfloat;
		  else if (value && SYMBOLP(value))
		      typecode = Qsymbol;
		  else {
		      if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) != 
			      (SI_Long)0L) {
			  length_2 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value));
			  temp_1 = (SI_Long)1L == UBYTE_16_ISAREF_1(value,
				  UBYTE_16_ISAREF_1(value,length_2 - 
				  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(value,
				  length_2 - (SI_Long)1L) & 
				  (SI_Long)8191L) << (SI_Long)16L));
		      }
		      else
			  temp_1 = TRUEP(Nil);
		      if (temp_1)
			  typecode = Qunsigned_short_vector;
		      else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) != 
			      (SI_Long)0L)
			  typecode = Qtext;
		      else {
			  if (SIMPLE_VECTOR_P(value) && 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > 
				  (SI_Long)2L) {
			      temp_1 = EQ(ISVREF(value,(SI_Long)1L),
				      Qavailable_frame_vector);
			      if (temp_1);
			      else {
				  thing = ISVREF(value,(SI_Long)1L);
				  temp_1 = SIMPLE_VECTOR_P(thing) ? 
					  EQ(ISVREF(thing,(SI_Long)0L),
					  Qg2_defstruct_structure_name_class_description_g2_struct) 
					  : TRUEP(Qnil);
			      }
			  }
			  else
			      temp_1 = TRUEP(Nil);
			  if (temp_1)
			      typecode = Qitem;
			  else if (SIMPLE_VECTOR_P(value) && 
				  EQ(ISVREF(value,(SI_Long)0L),
				  Qg2_defstruct_structure_name_class_description_g2_struct))
			      typecode = Qitem;
			  else
			      typecode = Qnull;
		      }
		  }
		  if (EQ(typecode,Qnull)) {
		      internal_value = value;
		      if ( !TRUEP(type)) {
			  type = Qnull;
			  result_1 = type;
		      }
		      else if ( !EQ(type,Qnull)) {
			  type = Qt;
			  goto end_loop_4;
		      }
		      else
			  result_1 = Qnil;
		  }
		  else if (EQ(typecode,Qinteger)) {
		      internal_value = value;
		      if ( !TRUEP(type)) {
			  type = Qinteger;
			  result_1 = type;
		      }
		      else if ( !EQ(type,Qinteger)) {
			  type = Qt;
			  goto end_loop_4;
		      }
		      else
			  result_1 = Qnil;
		  }
		  else if (EQ(typecode,Qtruth_value)) {
		      internal_value = M_CAR(value);
		      if ( !TRUEP(type)) {
			  type = Qtruth_value;
			  result_1 = type;
		      }
		      else if ( !EQ(type,Qtruth_value)) {
			  type = Qt;
			  goto end_loop_4;
		      }
		      else
			  result_1 = Qnil;
		  }
		  else if (EQ(typecode,Qfloat)) {
		      internal_value = value;
		      if ( !TRUEP(type)) {
			  type = Qfloat;
			  result_1 = type;
		      }
		      else if ( !EQ(type,Qfloat)) {
			  type = Qt;
			  goto end_loop_4;
		      }
		      else
			  result_1 = Qnil;
		  }
		  else if (EQ(typecode,Qtext)) {
		      internal_value = value;
		      if ( !TRUEP(type)) {
			  type = Qtext;
			  result_1 = type;
		      }
		      else if ( !EQ(type,Qtext)) {
			  type = Qt;
			  goto end_loop_4;
		      }
		      else
			  result_1 = Qnil;
		  }
		  else if (EQ(typecode,Qunsigned_short_vector)) {
		      internal_value = CONSP(value) ? M_CAR(value) : value;
		      if ( !TRUEP(type)) {
			  type = Qunsigned_short_vector;
			  result_1 = type;
		      }
		      else if ( !EQ(type,Qunsigned_short_vector)) {
			  type = Qt;
			  goto end_loop_4;
		      }
		      else
			  result_1 = Qnil;
		  }
		  else {
		      type = Qt;
		      goto end_loop_4;
		  }
		  goto next_loop_4;
		end_loop_4:;
		  if (EQ(type,Qnull))
		      typetag = FIX((SI_Long)0L);
		  else if (EQ(type,Qinteger))
		      typetag = FIX((SI_Long)1L);
		  else if (EQ(type,Qlong))
		      typetag = FIX((SI_Long)51L);
		  else if (EQ(type,Qtruth_value))
		      typetag = FIX((SI_Long)5L);
		  else if (EQ(type,Qfloat))
		      typetag = FIX((SI_Long)6L);
		  else if (EQ(type,Qtext))
		      typetag = FIX((SI_Long)4L);
		  else if (EQ(type,Qunsigned_short_vector))
		      typetag = FIX((SI_Long)11L);
		  else
		      typetag = Nil;
	      }
	      remote_value_known_typetag = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : typetag;
	      PUSH_SPECIAL_WITH_SYMBOL(Remote_value_known_typetag,Qremote_value_known_typetag,remote_value_known_typetag,
		      0);
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    temp = resumable_icp_pop();
		    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			    temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
			switch (INTEGER_TO_CHAR(temp)) {
			  case 1:
			    goto l1;
			    break;
			  case 2:
			    goto l2;
			    break;
			  case 3:
			    goto l3;
			    break;
			  default:
			    break;
			}
		}
	      l1:
		test = Nil;
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    test = resumable_icp_pop();
		    temp_1 = TRUEP(test);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1 ? EQ(test,Qtrue) : TRUEP(typetag)) {
		    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
			    : TRUEP(Nil)) {
			temp = resumable_icp_pop();
			if (! !(FIXNUMP(temp) && 
				FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
				FIXNUM_LE(temp,FIX((SI_Long)127L))))
			    switch (INTEGER_TO_CHAR(temp)) {
			      case 1:
				goto l1_1;
				break;
			      case 2:
				goto l2_1;
				break;
			      default:
				break;
			    }
		    }
		  l1_1:
		    if (EQ(icp_suspend_1,write_icp_byte(FIX((SI_Long)67L)))) {
			resumable_icp_push(FIX((SI_Long)1L));
			temp = Icp_suspend;
			goto end_block;
		    }
		  l2_1:
		    if (EQ(icp_suspend_1,write_icp_byte(typetag))) {
			resumable_icp_push(FIX((SI_Long)2L));
			temp = Icp_suspend;
			goto end_block;
		    }
		    else
			temp = Nil;
		    goto end_block;
		  end_block:
		    if (EQ(icp_suspend_1,temp)) {
			resumable_icp_push(Qtrue);
			resumable_icp_push(FIX((SI_Long)1L));
			result = VALUES_1(Icp_suspend);
			goto end_block_1;
		    }
		}
		else if ((resumable_icp_state_1 ? 
			TRUEP(Resumable_icp_state) : TRUEP(Nil)) || T) {
		    if (EQ(icp_suspend_1,write_icp_byte(FIX((SI_Long)49L)))) {
			resumable_icp_push(Qfalse);
			resumable_icp_push(FIX((SI_Long)1L));
			result = VALUES_1(Icp_suspend);
			goto end_block_1;
		    }
		}
	      l2:
		if (EQ(icp_suspend_1,
			write_icp_fixnum(FIXNUM_SUB1(ISVREF(M_CAR(evaluation_sequence),
			(SI_Long)1L))))) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    result = VALUES_1(Icp_suspend);
		    goto end_block_1;
		}
	      l3:
		gensymed_symbol = (resumable_icp_state_1 ? 
			TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			resumable_icp_pop() : evaluation_sequence;
		held_vector = (resumable_icp_state_1 ? 
			TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			resumable_icp_pop() : Nil;
		next_index = (resumable_icp_state_1 ? 
			TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			IFIX(resumable_icp_pop()) : (SI_Long)1L;
		length_1 = (resumable_icp_state_1 ? 
			TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			IFIX(resumable_icp_pop()) : (SI_Long)0L;
		value = (resumable_icp_state_1 ? 
			TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			resumable_icp_pop() : Nil;
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil))
		    goto resume;
		held_vector = M_CAR(gensymed_symbol);
		length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	      next_loop_5:
		if (next_index >= length_1)
		    goto end_loop_5;
		elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
			Maximum_in_place_array_size) ? ISVREF(held_vector,
			next_index + IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector,(next_index >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),next_index & 
			(SI_Long)1023L);
		validated_elt = elt_1 ? 
			validate_item_or_evaluation_value(elt_1,Nil,Nil) : Nil;
		next_index = next_index + (SI_Long)1L;
		value = validated_elt;
	      resume:
		if (EQ(icp_suspend_1,write_icp_remote_value(value))) {
		    resumable_icp_push(value);
		    resumable_icp_push(FIX(length_1));
		    resumable_icp_push(FIX(next_index));
		    resumable_icp_push(held_vector);
		    resumable_icp_push(gensymed_symbol);
		    resumable_icp_push(FIX((SI_Long)3L));
		    result = VALUES_1(Icp_suspend);
		    goto end_block_1;
		}
		goto next_loop_5;
	      end_loop_5:
		result = VALUES_1(Qnil);
		goto end_block_1;
	      end_block_1:
		MVS_3(result,v1,v2,v3);
		if (EQ(icp_suspend_1,v1)) {
		    resumable_icp_push(Remote_value_known_typetag);
		    resumable_icp_push(typetag);
		    resumable_icp_push(known_type);
		    resumable_icp_push(evaluation_sequence);
		    resumable_icp_push(Qwrite_icp_evaluation_sequence);
		    result = VALUES_1(Icp_suspend);
		    POP_SPECIAL();
		    POP_SPECIAL();
		    goto end_write_icp_evaluation_sequence;
		}
		temp = v1;
		result_of_write = temp;
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qevaluation_sequence,string_constant_5,Qvalue,
			  Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else {
	    known_type = (resumable_icp_state_1 ? 
		    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : Nil;
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		typetag = resumable_icp_pop();
	    else {
		type = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
			: TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			resumable_icp_pop() : known_type;
		gensymed_symbol = evaluation_sequence;
		held_vector = Nil;
		next_index = (SI_Long)1L;
		length_1 = (SI_Long)0L;
		value = Nil;
		held_vector = M_CAR(gensymed_symbol);
		length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	      next_loop_6:
		if (next_index >= length_1)
		    goto end_loop_6;
		elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
			Maximum_in_place_array_size) ? ISVREF(held_vector,
			next_index + IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector,(next_index >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),next_index & 
			(SI_Long)1023L);
		validated_elt = elt_1 ? 
			validate_item_or_evaluation_value(elt_1,Nil,Nil) : Nil;
		next_index = next_index + (SI_Long)1L;
		value = validated_elt;
		if (Remote_value_known_typetag) {
		    temp = Remote_value_known_typetag;
		    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
			    FIXNUM_LE(temp,FIX((SI_Long)127L))))
			typecode = Nil;
		    else
			switch (INTEGER_TO_CHAR(temp)) {
			  case 0:
			    typecode = Qnull;
			    break;
			  case 1:
			    typecode = Qinteger;
			    break;
			  case 51:
			    typecode = Qlong;
			    break;
			  case 5:
			    typecode = Qtruth_value;
			    break;
			  case 6:
			    typecode = Qfloat;
			    break;
			  case 4:
			    typecode = Qtext;
			    break;
			  case 11:
			    typecode = Qunsigned_short_vector;
			    break;
			  default:
			    typecode = Nil;
			    break;
			}
		}
		else if (Remote_value_is_binary_p)
		    typecode = Qunsigned_short_vector;
		else if ( !TRUEP(value))
		    typecode = Qnull;
		else if (FIXNUMP(value))
		    typecode = Qinteger;
		else if (INLINE_LONG_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		    typecode = Qlong;
		else if (CONSP(value)) {
		    cdr_1 = M_CDR(value);
		    if (EQ(cdr_1,Qtruth_value))
			typecode = Qtruth_value;
		    else if (EQ(cdr_1,Qsequence))
			typecode = Qsequence;
		    else if (EQ(cdr_1,Qab_structure))
			typecode = Qab_structure;
		    else if (EQ(cdr_1,Qunsigned_vector_16))
			typecode = Qunsigned_short_vector;
		    else
			typecode = Qnull;
		}
		else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		    typecode = Qfloat;
		else if (value && SYMBOLP(value))
		    typecode = Qsymbol;
		else {
		    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) != 
				(SI_Long)0L) {
			length_2 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value));
			temp_1 = (SI_Long)1L == UBYTE_16_ISAREF_1(value,
				UBYTE_16_ISAREF_1(value,length_2 - 
				(SI_Long)2L) + ((UBYTE_16_ISAREF_1(value,
				length_2 - (SI_Long)1L) & (SI_Long)8191L) 
				<< (SI_Long)16L));
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1)
			typecode = Qunsigned_short_vector;
		    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) != 
			    (SI_Long)0L)
			typecode = Qtext;
		    else {
			if (SIMPLE_VECTOR_P(value) && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > 
				(SI_Long)2L) {
			    temp_1 = EQ(ISVREF(value,(SI_Long)1L),
				    Qavailable_frame_vector);
			    if (temp_1);
			    else {
				thing = ISVREF(value,(SI_Long)1L);
				temp_1 = SIMPLE_VECTOR_P(thing) ? 
					EQ(ISVREF(thing,(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					: TRUEP(Qnil);
			    }
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1)
			    typecode = Qitem;
			else if (SIMPLE_VECTOR_P(value) && EQ(ISVREF(value,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct))
			    typecode = Qitem;
			else
			    typecode = Qnull;
		    }
		}
		if (EQ(typecode,Qnull)) {
		    internal_value = value;
		    if ( !TRUEP(type)) {
			type = Qnull;
			result_1 = type;
		    }
		    else if ( !EQ(type,Qnull)) {
			type = Qt;
			goto end_loop_6;
		    }
		    else
			result_1 = Qnil;
		}
		else if (EQ(typecode,Qinteger)) {
		    internal_value = value;
		    if ( !TRUEP(type)) {
			type = Qinteger;
			result_1 = type;
		    }
		    else if ( !EQ(type,Qinteger)) {
			type = Qt;
			goto end_loop_6;
		    }
		    else
			result_1 = Qnil;
		}
		else if (EQ(typecode,Qtruth_value)) {
		    internal_value = M_CAR(value);
		    if ( !TRUEP(type)) {
			type = Qtruth_value;
			result_1 = type;
		    }
		    else if ( !EQ(type,Qtruth_value)) {
			type = Qt;
			goto end_loop_6;
		    }
		    else
			result_1 = Qnil;
		}
		else if (EQ(typecode,Qfloat)) {
		    internal_value = value;
		    if ( !TRUEP(type)) {
			type = Qfloat;
			result_1 = type;
		    }
		    else if ( !EQ(type,Qfloat)) {
			type = Qt;
			goto end_loop_6;
		    }
		    else
			result_1 = Qnil;
		}
		else if (EQ(typecode,Qtext)) {
		    internal_value = value;
		    if ( !TRUEP(type)) {
			type = Qtext;
			result_1 = type;
		    }
		    else if ( !EQ(type,Qtext)) {
			type = Qt;
			goto end_loop_6;
		    }
		    else
			result_1 = Qnil;
		}
		else if (EQ(typecode,Qunsigned_short_vector)) {
		    internal_value = CONSP(value) ? M_CAR(value) : value;
		    if ( !TRUEP(type)) {
			type = Qunsigned_short_vector;
			result_1 = type;
		    }
		    else if ( !EQ(type,Qunsigned_short_vector)) {
			type = Qt;
			goto end_loop_6;
		    }
		    else
			result_1 = Qnil;
		}
		else {
		    type = Qt;
		    goto end_loop_6;
		}
		goto next_loop_6;
	      end_loop_6:;
		if (EQ(type,Qnull))
		    typetag = FIX((SI_Long)0L);
		else if (EQ(type,Qinteger))
		    typetag = FIX((SI_Long)1L);
		else if (EQ(type,Qlong))
		    typetag = FIX((SI_Long)51L);
		else if (EQ(type,Qtruth_value))
		    typetag = FIX((SI_Long)5L);
		else if (EQ(type,Qfloat))
		    typetag = FIX((SI_Long)6L);
		else if (EQ(type,Qtext))
		    typetag = FIX((SI_Long)4L);
		else if (EQ(type,Qunsigned_short_vector))
		    typetag = FIX((SI_Long)11L);
		else
		    typetag = Nil;
	    }
	    remote_value_known_typetag = (resumable_icp_state_1 ? 
		    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : typetag;
	    PUSH_SPECIAL_WITH_SYMBOL(Remote_value_known_typetag,Qremote_value_known_typetag,remote_value_known_typetag,
		    0);
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  temp = resumable_icp_pop();
		  if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			  temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		      switch (INTEGER_TO_CHAR(temp)) {
			case 1:
			  goto l1_2;
			  break;
			case 2:
			  goto l2_2;
			  break;
			case 3:
			  goto l3_1;
			  break;
			default:
			  break;
		      }
	      }
	    l1_2:
	      test = Nil;
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  test = resumable_icp_pop();
		  temp_1 = TRUEP(test);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if (temp_1 ? EQ(test,Qtrue) : TRUEP(typetag)) {
		  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			  TRUEP(Nil)) {
		      temp = resumable_icp_pop();
		      if (! !(FIXNUMP(temp) && 
			      FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
			      FIXNUM_LE(temp,FIX((SI_Long)127L))))
			  switch (INTEGER_TO_CHAR(temp)) {
			    case 1:
			      goto l1_3;
			      break;
			    case 2:
			      goto l2_3;
			      break;
			    default:
			      break;
			  }
		  }
		l1_3:
		  if (EQ(icp_suspend_1,write_icp_byte(FIX((SI_Long)67L)))) {
		      resumable_icp_push(FIX((SI_Long)1L));
		      temp = Icp_suspend;
		      goto end_block_2;
		  }
		l2_3:
		  if (EQ(icp_suspend_1,write_icp_byte(typetag))) {
		      resumable_icp_push(FIX((SI_Long)2L));
		      temp = Icp_suspend;
		      goto end_block_2;
		  }
		  else
		      temp = Nil;
		  goto end_block_2;
		end_block_2:
		  if (EQ(icp_suspend_1,temp)) {
		      resumable_icp_push(Qtrue);
		      resumable_icp_push(FIX((SI_Long)1L));
		      result = VALUES_1(Icp_suspend);
		      goto end_block_3;
		  }
	      }
	      else if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
		      : TRUEP(Nil)) || T) {
		  if (EQ(icp_suspend_1,write_icp_byte(FIX((SI_Long)49L)))) {
		      resumable_icp_push(Qfalse);
		      resumable_icp_push(FIX((SI_Long)1L));
		      result = VALUES_1(Icp_suspend);
		      goto end_block_3;
		  }
	      }
	    l2_2:
	      if (EQ(icp_suspend_1,
		      write_icp_fixnum(FIXNUM_SUB1(ISVREF(M_CAR(evaluation_sequence),
		      (SI_Long)1L))))) {
		  resumable_icp_push(FIX((SI_Long)2L));
		  result = VALUES_1(Icp_suspend);
		  goto end_block_3;
	      }
	    l3_1:
	      gensymed_symbol = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : evaluation_sequence;
	      held_vector = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      next_index = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      IFIX(resumable_icp_pop()) : (SI_Long)1L;
	      length_1 = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      IFIX(resumable_icp_pop()) : (SI_Long)0L;
	      value = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
		       TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil))
		  goto resume_1;
	      held_vector = M_CAR(gensymed_symbol);
	      length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	    next_loop_7:
	      if (next_index >= length_1)
		  goto end_loop_7;
	      elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		      Maximum_in_place_array_size) ? ISVREF(held_vector,
		      next_index + IFIX(Managed_array_index_offset)) : 
		      ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L),next_index & 
		      (SI_Long)1023L);
	      validated_elt = elt_1 ? 
		      validate_item_or_evaluation_value(elt_1,Nil,Nil) : Nil;
	      next_index = next_index + (SI_Long)1L;
	      value = validated_elt;
	    resume_1:
	      if (EQ(icp_suspend_1,write_icp_remote_value(value))) {
		  resumable_icp_push(value);
		  resumable_icp_push(FIX(length_1));
		  resumable_icp_push(FIX(next_index));
		  resumable_icp_push(held_vector);
		  resumable_icp_push(gensymed_symbol);
		  resumable_icp_push(FIX((SI_Long)3L));
		  result = VALUES_1(Icp_suspend);
		  goto end_block_3;
	      }
	      goto next_loop_7;
	    end_loop_7:
	      result = VALUES_1(Qnil);
	      goto end_block_3;
	    end_block_3:
	      MVS_3(result,v1,v2,v3);
	      if (EQ(icp_suspend_1,v1)) {
		  resumable_icp_push(Remote_value_known_typetag);
		  resumable_icp_push(typetag);
		  resumable_icp_push(known_type);
		  resumable_icp_push(evaluation_sequence);
		  resumable_icp_push(Qwrite_icp_evaluation_sequence);
		  result = VALUES_1(Icp_suspend);
		  POP_SPECIAL();
		  goto end_write_icp_evaluation_sequence;
	      }
	      temp = v1;
	    POP_SPECIAL();
	}
    }
    result = VALUES_1(temp);
  end_write_icp_evaluation_sequence:
    return result;
}

static Object Qread_evaluation_structure_from_list;  /* read-evaluation-structure-from-list */

/* READ-EVALUATION-STRUCTURE-FROM-LIST */
Object read_evaluation_structure_from_list(so_far,list_1)
    Object so_far, list_1;
{
    Object attribute, ab_loop_list_, value, converted_value;
    Object converted_attribute, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object plist, temp, resumable_icp_state_1, icp_suspend_1, top, arg1;
    Object value_1;

    x_note_fn_call(157,108);
    if (Disable_resumability) {
	attribute = Nil;
	ab_loop_list_ = list_1;
	value = Nil;
	converted_value = Nil;
	converted_attribute = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	attribute = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	value = read_icp_remote_value();
	converted_value = CONSP(value) && EQ(M_CDR(value),
		Qunsigned_vector_16) ? M_CAR(value) : value;
	converted_attribute = ATOM(attribute) ? attribute :  
		!TRUEP(SECOND(attribute)) ? THIRD(attribute) : 
		make_unique_slot_name_symbol(SECOND(attribute),
		THIRD(attribute));
	ab_loopvar__2 = eval_cons_1(converted_attribute,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	ab_loopvar__2 = eval_cons_1(converted_value,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	plist = ab_loopvar_;
	goto end_1;
	plist = Qnil;
      end_1:;
	temp = allocate_evaluation_structure(so_far ? nconc2(so_far,plist) 
		: plist);
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qread_evaluation_structure_from_list,top))
		return icp_error_internal(Qerror,string_constant,
			Qread_evaluation_structure_from_list,top,Nil);
	}
	so_far = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : so_far;
	list_1 = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : list_1;
	if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  !TRUEP(resumable_icp_pop_list_if_end_marker()))
	    arg1 = resumable_icp_pop();
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		plist = resumable_icp_pop();
	    else {
		attribute = (resumable_icp_state_1 ? 
			TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			resumable_icp_pop() : Nil;
		ab_loop_list_ = (resumable_icp_state_1 ? 
			TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			resumable_icp_pop() : list_1;
		value = (resumable_icp_state_1 ? 
			TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			resumable_icp_pop() : Nil;
		converted_value = (resumable_icp_state_1 ? 
			TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			resumable_icp_pop() : Nil;
		converted_attribute = (resumable_icp_state_1 ? 
			TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			resumable_icp_pop() : Nil;
		ab_loopvar_ = (resumable_icp_state_1 ? 
			TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			resumable_icp_pop() : Nil;
		ab_loopvar__1 = (resumable_icp_state_1 ? 
			TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			resumable_icp_pop() : Nil;
		ab_loopvar__2 = (resumable_icp_state_1 ? 
			TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			resumable_icp_pop() : Nil;
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil))
		    goto resume;
	      next_loop_1:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_1;
		attribute = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
	      resume:
		value_1 = read_icp_remote_value();
		if (EQ(icp_suspend_1,value_1)) {
		    resumable_icp_push(ab_loopvar__2);
		    resumable_icp_push(ab_loopvar__1);
		    resumable_icp_push(ab_loopvar_);
		    resumable_icp_push(converted_attribute);
		    resumable_icp_push(converted_value);
		    resumable_icp_push(value);
		    resumable_icp_push(ab_loop_list_);
		    resumable_icp_push(attribute);
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(list_1);
		    resumable_icp_push(so_far);
		    resumable_icp_push(Qread_evaluation_structure_from_list);
		    return VALUES_1(Icp_suspend);
		}
		value = value_1;
		converted_value = CONSP(value) && EQ(M_CDR(value),
			Qunsigned_vector_16) ? M_CAR(value) : value;
		converted_attribute = ATOM(attribute) ? attribute :  
			!TRUEP(SECOND(attribute)) ? THIRD(attribute) : 
			make_unique_slot_name_symbol(SECOND(attribute),
			THIRD(attribute));
		ab_loopvar__2 = eval_cons_1(converted_attribute,Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
		ab_loopvar__2 = eval_cons_1(converted_value,Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
		goto next_loop_1;
	      end_loop_1:
		plist = ab_loopvar_;
		goto end_2;
		plist = Qnil;
	      end_2:;
	    }
	    arg1 = so_far ? nconc2(so_far,plist) : plist;
	}
	temp = allocate_evaluation_structure(arg1);
    }
    return VALUES_1(temp);
}

static Object Qevaluation_structure;  /* evaluation-structure */

static Object Qread_icp_evaluation_structure;  /* read-icp-evaluation-structure */

/* READ-ICP-EVALUATION-STRUCTURE */
Object read_icp_evaluation_structure()
{
    Object tracep, byte_count_before, current_icp_read_trace_level;
    Object result_of_read, temp, resumable_icp_state_1, icp_suspend_1, top;
    Object arg1, arg2, arg1_1, value;
    Declare_special(1);
    Object result;

    x_note_fn_call(157,109);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qevaluation_structure,
			string_constant_5,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      result_of_read = read_evaluation_structure_from_list(Nil,
		      ISVREF(read_icp_interned_list_as_value_type(),
		      (SI_Long)1L));
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qevaluation_structure,string_constant_5,Qvalue,T,
			  result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else
	    temp = read_evaluation_structure_from_list(Nil,
		    ISVREF(read_icp_interned_list_as_value_type(),
		    (SI_Long)1L));
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qread_icp_evaluation_structure,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qread_icp_evaluation_structure,top,Nil);
		goto end_read_icp_evaluation_structure;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qevaluation_structure,
			string_constant_5,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      arg1 = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  arg2 = resumable_icp_pop();
	      else {
		  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			   TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()))
		      arg1_1 = resumable_icp_pop();
		  else {
		      value = read_icp_interned_list_as_value_type();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(arg1);
			  resumable_icp_push(Qread_icp_evaluation_structure);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_read_icp_evaluation_structure;
		      }
		      arg1_1 = value;
		  }
		  arg2 = (resumable_icp_state_1 ? 
			  TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			  resumable_icp_pop() : FIX((SI_Long)1L);
		  arg2 = ISVREF(arg1_1,IFIX(arg2));
	      }
	      value = read_evaluation_structure_from_list(arg1,arg2);
	      if (EQ(icp_suspend_1,value)) {
		  resumable_icp_push(arg2);
		  resumable_icp_push(arg1);
		  resumable_icp_push(Qread_icp_evaluation_structure);
		  result = VALUES_1(Icp_suspend);
		  POP_SPECIAL();
		  goto end_read_icp_evaluation_structure;
	      }
	      result_of_read = value;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qevaluation_structure,string_constant_5,Qvalue,T,
			  result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    arg1 = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : Nil;
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		arg2 = resumable_icp_pop();
	    else {
		if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()))
		    arg1_1 = resumable_icp_pop();
		else {
		    value = read_icp_interned_list_as_value_type();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(arg1);
			resumable_icp_push(Qread_icp_evaluation_structure);
			result = VALUES_1(Icp_suspend);
			goto end_read_icp_evaluation_structure;
		    }
		    arg1_1 = value;
		}
		arg2 = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
			: TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			resumable_icp_pop() : FIX((SI_Long)1L);
		arg2 = ISVREF(arg1_1,IFIX(arg2));
	    }
	    value = read_evaluation_structure_from_list(arg1,arg2);
	    if (EQ(icp_suspend_1,value)) {
		resumable_icp_push(arg2);
		resumable_icp_push(arg1);
		resumable_icp_push(Qread_icp_evaluation_structure);
		result = VALUES_1(Icp_suspend);
		goto end_read_icp_evaluation_structure;
	    }
	    temp = value;
	}
    }
    result = VALUES_1(temp);
  end_read_icp_evaluation_structure:
    return result;
}

static Object Qinterned_list_table;  /* interned-list-table */

/* INTERN-ATTRIBUTES-OF-STRUCTURE */
Object intern_attributes_of_structure(structure)
    Object structure;
{
    Object accumulating_list_p, list_1, element, root, table, entry_or_table;
    Object entry, gensymed_symbol, held_vector, key, attribute_value, val;
    Object temp, element_copy, e, cdr_new_value, element_count_1, root_1;
    Object held_vector_1, entry_or_table_1, entry_1, result_1;
    SI_Long element_count, next_index, length_1, gensymed_symbol_1, limit;
    SI_Long next_index_1, length_2;

    x_note_fn_call(157,110);
    element_count = (SI_Long)0L;
    accumulating_list_p = Nil;
    list_1 = Nil;
    element = Nil;
    root = Nil;
    table = Nil;
    entry_or_table = Nil;
    entry = Nil;
    gensymed_symbol = structure;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    key = Nil;
    attribute_value = Nil;
    val = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    key = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
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
    val = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
    next_index = next_index + (SI_Long)2L;
    element = key;
    element_count = element_count + (SI_Long)1L;
    if (element_count == (SI_Long)1L) {
	root = SYMBOLP(element) ? element : Nil;
	if (root) {
	    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(root),
		    Qinterned_list_table);
	    if (temp);
	    else {
		accumulating_list_p = T;
		Interned_list_symbols = interned_list_cons(root,
			Interned_list_symbols);
		temp = root;
		temp = mutate_global_property(temp,interned_list_cons(Nil,
			Nil),Qinterned_list_table);
	    }
	    table = temp;
	}
	else {
	    temp = Interned_list_non_symbol_root;
	    if (temp);
	    else {
		Interned_list_non_symbol_root = interned_list_cons(Nil,Nil);
		temp = Interned_list_non_symbol_root;
	    }
	    table = temp;
	}
	if (accumulating_list_p && root)
	    list_1 = interned_list_cons(root,list_1);
	entry_or_table = table;
	entry = Nil;
    }
    if ( !(element_count == (SI_Long)1L && root)) {
	if (CONSP(entry_or_table))
	    table = entry_or_table;
	else {
	    table = interned_list_cons(entry_or_table,Nil);
	    M_CDR(entry) = table;
	}
	temp = SYMBOLP(element) ? assq_function(element,CDR(table)) : 
		ab_assoc_equal(element,CDR(table));
	if (temp);
	else {
	    element_copy = CONSP(element) ? 
		    copy_tree_for_interned_list(element) : element;
	    e = interned_list_cons(element_copy,Nil);
	    cdr_new_value = interned_list_cons(e,CDR(table));
	    M_CDR(table) = cdr_new_value;
	    if ( !TRUEP(accumulating_list_p)) {
		accumulating_list_p = T;
		element_count_1 = FIX((SI_Long)0L);
		element = Nil;
		root_1 = Nil;
		table = Nil;
		entry_or_table = Nil;
		entry = Nil;
		limit = element_count - (SI_Long)1L;
		gensymed_symbol = structure;
		held_vector_1 = Nil;
		next_index_1 = (SI_Long)1L;
		length_2 = (SI_Long)0L;
		key = Nil;
		attribute_value = Nil;
		val = Nil;
		held_vector_1 = M_CAR(gensymed_symbol);
		length_2 = IFIX(ISVREF(held_vector_1,(SI_Long)1L));
	      next_loop_1:
		if (next_index_1 >= length_2)
		    goto end_loop_1;
		key = FIXNUM_LE(ISVREF(held_vector_1,(SI_Long)1L),
			Maximum_in_place_array_size) ? 
			ISVREF(held_vector_1,next_index_1 + 
			IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector_1,(next_index_1 >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),next_index_1 & 
			(SI_Long)1023L);
		gensymed_symbol_1 = next_index_1 + (SI_Long)1L;
		attribute_value = FIXNUM_LE(ISVREF(held_vector_1,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(held_vector_1,gensymed_symbol_1 + 
			IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector_1,(gensymed_symbol_1 >>  
			-  - (SI_Long)10L) + (SI_Long)2L),
			gensymed_symbol_1 & (SI_Long)1023L);
		val = validate_item_or_evaluation_value(attribute_value,
			Nil,Nil);
		next_index_1 = next_index_1 + (SI_Long)2L;
		if (limit == IFIX(element_count_1))
		    goto end_list_so_far_block;
		element = key;
		element_count_1 = FIXNUM_ADD1(element_count_1);
		if (IFIX(element_count_1) == (SI_Long)1L) {
		    root_1 = SYMBOLP(element) ? element : Nil;
		    if (root_1) {
			temp = 
				getfq_function_no_default(INLINE_SYMBOL_PLIST(root_1),
				Qinterned_list_table);
			if (temp);
			else
			    temp = Nil;
			table = temp;
		    }
		    else {
			temp = Interned_list_non_symbol_root;
			if (temp);
			else
			    temp = Nil;
			table = temp;
		    }
		    if (accumulating_list_p && root_1)
			list_1 = interned_list_cons(root_1,list_1);
		    entry_or_table = table;
		    entry = Nil;
		}
		if ( !(IFIX(element_count_1) == (SI_Long)1L && root_1)) {
		    table = CONSP(entry_or_table) ? entry_or_table : Nil;
		    temp = SYMBOLP(element) ? assq_function(element,
			    CDR(table)) : ab_assoc_equal(element,CDR(table));
		    if (temp);
		    else
			temp = Nil;
		    entry = temp;
		    if (accumulating_list_p)
			list_1 = interned_list_cons(CAR(entry),list_1);
		    entry_or_table = CDR(entry);
		}
		goto next_loop_1;
	      end_loop_1:;
	      end_list_so_far_block:;
	    }
	    temp = e;
	}
	entry = temp;
	if (accumulating_list_p)
	    list_1 = interned_list_cons(CAR(entry),list_1);
	entry_or_table = CDR(entry);
    }
    goto next_loop;
  end_loop:;
    if ((SI_Long)0L == element_count) {
	temp = Interned_list_nil;
	if (temp);
	else {
	    Interned_list_nil = make_interned_list_1(Nil);
	    temp = Interned_list_nil;
	}
    }
    else {
	temp = CONSP(entry_or_table) ? CAR(entry_or_table) : entry_or_table;
	if (temp);
	else {
	    if ( !TRUEP(accumulating_list_p)) {
		accumulating_list_p = T;
		element_count_1 = FIX((SI_Long)0L);
		element = Nil;
		root = Nil;
		table = Nil;
		entry_or_table_1 = Nil;
		entry_1 = Nil;
		limit = element_count;
		gensymed_symbol = structure;
		held_vector = Nil;
		next_index = (SI_Long)1L;
		length_1 = (SI_Long)0L;
		key = Nil;
		attribute_value = Nil;
		val = Nil;
		held_vector = M_CAR(gensymed_symbol);
		length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	      next_loop_2:
		if (next_index >= length_1)
		    goto end_loop_2;
		key = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
			Maximum_in_place_array_size) ? ISVREF(held_vector,
			next_index + IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector,(next_index >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),next_index & 
			(SI_Long)1023L);
		gensymed_symbol_1 = next_index + (SI_Long)1L;
		attribute_value = FIXNUM_LE(ISVREF(held_vector,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(held_vector,gensymed_symbol_1 + 
			IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  - 
			 - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 
			& (SI_Long)1023L);
		val = validate_item_or_evaluation_value(attribute_value,
			Nil,Nil);
		next_index = next_index + (SI_Long)2L;
		if (limit == IFIX(element_count_1))
		    goto end_list_so_far_block_1;
		element = key;
		element_count_1 = FIXNUM_ADD1(element_count_1);
		if (IFIX(element_count_1) == (SI_Long)1L) {
		    root = SYMBOLP(element) ? element : Nil;
		    if (root) {
			temp = 
				getfq_function_no_default(INLINE_SYMBOL_PLIST(root),
				Qinterned_list_table);
			if (temp);
			else
			    temp = Nil;
			table = temp;
		    }
		    else {
			temp = Interned_list_non_symbol_root;
			if (temp);
			else
			    temp = Nil;
			table = temp;
		    }
		    if (accumulating_list_p && root)
			list_1 = interned_list_cons(root,list_1);
		    entry_or_table_1 = table;
		    entry_1 = Nil;
		}
		if ( !(IFIX(element_count_1) == (SI_Long)1L && root)) {
		    table = CONSP(entry_or_table_1) ? entry_or_table_1 : Nil;
		    temp = SYMBOLP(element) ? assq_function(element,
			    CDR(table)) : ab_assoc_equal(element,CDR(table));
		    if (temp);
		    else
			temp = Nil;
		    entry_1 = temp;
		    if (accumulating_list_p)
			list_1 = interned_list_cons(CAR(entry_1),list_1);
		    entry_or_table_1 = CDR(entry_1);
		}
		goto next_loop_2;
	      end_loop_2:;
	      end_list_so_far_block_1:;
	    }
	    result_1 = make_interned_list_1(nreverse(list_1));
	    if (CONSP(entry_or_table))
		temp = M_CAR(entry_or_table) = result_1;
	    else
		temp = M_CDR(entry) = result_1;
	}
    }
    return VALUES_1(temp);
}

/* INTERN-ATTRIBUTES-OF-GSI-STRUCTURE */
Object intern_attributes_of_gsi_structure(gsi_item)
    Object gsi_item;
{
    x_note_fn_call(157,111);
    return VALUES_1(Nil);
}

static Object Qwrite_icp_evaluation_structure;  /* write-icp-evaluation-structure */

/* WRITE-ICP-EVALUATION-STRUCTURE */
Object write_icp_evaluation_structure(evaluation_structure)
    Object evaluation_structure;
{
    Object tracep, byte_count_before, current_icp_write_trace_level;
    Object gensymed_symbol, held_vector, attribute_value, attribute_value_1;
    Object result_of_write, temp, resumable_icp_state_1, icp_suspend_1, top;
    Object v1, v2, v3;
    SI_Long next_index, length_1, gensymed_symbol_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(157,112);
    if (Disable_resumability) {
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,Qevaluation_structure,
			string_constant_5,Qvalue,T,evaluation_structure,
			Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      write_icp_interned_list_as_value_type(intern_attributes_of_structure(evaluation_structure));
	      gensymed_symbol = evaluation_structure;
	      held_vector = Nil;
	      next_index = (SI_Long)1L;
	      length_1 = (SI_Long)0L;
	      attribute_value = Nil;
	      attribute_value_1 = Nil;
	      held_vector = M_CAR(gensymed_symbol);
	      length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	    next_loop:
	      if (next_index >= length_1)
		  goto end_loop;
	      gensymed_symbol_1 = next_index + (SI_Long)1L;
	      attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		      Maximum_in_place_array_size) ? ISVREF(held_vector,
		      gensymed_symbol_1 + 
		      IFIX(Managed_array_index_offset)) : 
		      ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  
		      - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		      (SI_Long)1023L);
	      attribute_value_1 = 
		      validate_item_or_evaluation_value(attribute_value,
		      Nil,Nil);
	      next_index = next_index + (SI_Long)2L;
	      write_icp_remote_value(attribute_value_1);
	      goto next_loop;
	    end_loop:
	      result_of_write = Qnil;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qevaluation_structure,string_constant_5,Qvalue,
			  Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else {
	    write_icp_interned_list_as_value_type(intern_attributes_of_structure(evaluation_structure));
	    gensymed_symbol = evaluation_structure;
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_1 = (SI_Long)0L;
	    attribute_value = Nil;
	    attribute_value_1 = Nil;
	    held_vector = M_CAR(gensymed_symbol);
	    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	  next_loop_1:
	    if (next_index >= length_1)
		goto end_loop_1;
	    gensymed_symbol_1 = next_index + (SI_Long)1L;
	    attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    gensymed_symbol_1 + IFIX(Managed_array_index_offset)) :
		     ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		    (SI_Long)1023L);
	    attribute_value_1 = 
		    validate_item_or_evaluation_value(attribute_value,Nil,Nil);
	    next_index = next_index + (SI_Long)2L;
	    write_icp_remote_value(attribute_value_1);
	    goto next_loop_1;
	  end_loop_1:
	    temp = Qnil;
	}
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qwrite_icp_evaluation_structure,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qwrite_icp_evaluation_structure,top,Nil);
		goto end_write_icp_evaluation_structure;
	    }
	}
	evaluation_structure = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : evaluation_structure;
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,Qevaluation_structure,
			string_constant_5,Qvalue,T,evaluation_structure,
			Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  temp = resumable_icp_pop();
		  if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			  temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		      switch (INTEGER_TO_CHAR(temp)) {
			case 1:
			  goto l1;
			  break;
			case 2:
			  goto l2;
			  break;
			default:
			  break;
		      }
	      }
	    l1:
	      if (EQ(icp_suspend_1,
		      write_icp_interned_list_as_value_type(intern_attributes_of_structure(evaluation_structure)))) 
			  {
		  resumable_icp_push(FIX((SI_Long)1L));
		  result = VALUES_1(Icp_suspend);
		  goto end_block;
	      }
	    l2:
	      gensymed_symbol = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : evaluation_structure;
	      held_vector = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      next_index = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      IFIX(resumable_icp_pop()) : (SI_Long)1L;
	      length_1 = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      IFIX(resumable_icp_pop()) : (SI_Long)0L;
	      attribute_value = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      attribute_value_1 = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil))
		  goto resume;
	      held_vector = M_CAR(gensymed_symbol);
	      length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	    next_loop_2:
	      if (next_index >= length_1)
		  goto end_loop_2;
	      gensymed_symbol_1 = next_index + (SI_Long)1L;
	      attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		      Maximum_in_place_array_size) ? ISVREF(held_vector,
		      gensymed_symbol_1 + 
		      IFIX(Managed_array_index_offset)) : 
		      ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  
		      - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		      (SI_Long)1023L);
	      attribute_value_1 = 
		      validate_item_or_evaluation_value(attribute_value,
		      Nil,Nil);
	      next_index = next_index + (SI_Long)2L;
	    resume:
	      if (EQ(icp_suspend_1,
			  write_icp_remote_value(attribute_value_1))) {
		  resumable_icp_push(attribute_value_1);
		  resumable_icp_push(attribute_value);
		  resumable_icp_push(FIX(length_1));
		  resumable_icp_push(FIX(next_index));
		  resumable_icp_push(held_vector);
		  resumable_icp_push(gensymed_symbol);
		  resumable_icp_push(FIX((SI_Long)2L));
		  result = VALUES_1(Icp_suspend);
		  goto end_block;
	      }
	      goto next_loop_2;
	    end_loop_2:
	      result = VALUES_1(Qnil);
	      goto end_block;
	    end_block:
	      MVS_3(result,v1,v2,v3);
	      if (EQ(icp_suspend_1,v1)) {
		  resumable_icp_push(evaluation_structure);
		  resumable_icp_push(Qwrite_icp_evaluation_structure);
		  result = VALUES_1(Icp_suspend);
		  POP_SPECIAL();
		  goto end_write_icp_evaluation_structure;
	      }
	      temp = v1;
	      result_of_write = temp;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qevaluation_structure,string_constant_5,Qvalue,
			  Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else {
	    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) {
		temp = resumable_icp_pop();
		if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		    switch (INTEGER_TO_CHAR(temp)) {
		      case 1:
			goto l1_1;
			break;
		      case 2:
			goto l2_1;
			break;
		      default:
			break;
		    }
	    }
	  l1_1:
	    if (EQ(icp_suspend_1,
		    write_icp_interned_list_as_value_type(intern_attributes_of_structure(evaluation_structure)))) 
			{
		resumable_icp_push(FIX((SI_Long)1L));
		result = VALUES_1(Icp_suspend);
		goto end_block_1;
	    }
	  l2_1:
	    gensymed_symbol = (resumable_icp_state_1 ? 
		    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : evaluation_structure;
	    held_vector = (resumable_icp_state_1 ? 
		    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : Nil;
	    next_index = (resumable_icp_state_1 ? 
		    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    IFIX(resumable_icp_pop()) : (SI_Long)1L;
	    length_1 = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
		    : TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    IFIX(resumable_icp_pop()) : (SI_Long)0L;
	    attribute_value = (resumable_icp_state_1 ? 
		    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : Nil;
	    attribute_value_1 = (resumable_icp_state_1 ? 
		    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : Nil;
	    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil))
		goto resume_1;
	    held_vector = M_CAR(gensymed_symbol);
	    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	  next_loop_3:
	    if (next_index >= length_1)
		goto end_loop_3;
	    gensymed_symbol_1 = next_index + (SI_Long)1L;
	    attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    gensymed_symbol_1 + IFIX(Managed_array_index_offset)) :
		     ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		    (SI_Long)1023L);
	    attribute_value_1 = 
		    validate_item_or_evaluation_value(attribute_value,Nil,Nil);
	    next_index = next_index + (SI_Long)2L;
	  resume_1:
	    if (EQ(icp_suspend_1,write_icp_remote_value(attribute_value_1))) {
		resumable_icp_push(attribute_value_1);
		resumable_icp_push(attribute_value);
		resumable_icp_push(FIX(length_1));
		resumable_icp_push(FIX(next_index));
		resumable_icp_push(held_vector);
		resumable_icp_push(gensymed_symbol);
		resumable_icp_push(FIX((SI_Long)2L));
		result = VALUES_1(Icp_suspend);
		goto end_block_1;
	    }
	    goto next_loop_3;
	  end_loop_3:
	    result = VALUES_1(Qnil);
	    goto end_block_1;
	  end_block_1:
	    MVS_3(result,v1,v2,v3);
	    if (EQ(icp_suspend_1,v1)) {
		resumable_icp_push(evaluation_structure);
		resumable_icp_push(Qwrite_icp_evaluation_structure);
		result = VALUES_1(Icp_suspend);
		goto end_write_icp_evaluation_structure;
	    }
	    temp = v1;
	}
    }
    result = VALUES_1(temp);
  end_write_icp_evaluation_structure:
    return result;
}

static Object Qsend_icp_rpc_asynchronous_abort;  /* send-icp-rpc-asynchronous-abort */

static Object Qrpc_asynchronous_abort;  /* rpc-asynchronous-abort */

static Object Qprocedure_to_abort_qm;  /* procedure-to-abort? */

/* SEND-ICP-RPC-ASYNCHRONOUS-ABORT */
Object send_icp_rpc_asynchronous_abort(procedure_to_abort_qm)
    Object procedure_to_abort_qm;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, resumable_icp_state_1;
    Object icp_suspend_1, top, value, value_1;
    Declare_special(3);
    Object result;

    x_note_fn_call(157,113);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qsend_icp_rpc_asynchronous_abort;
	  }
	  temp_1 = getfq_function_no_default(ISVREF(procedure_to_abort_qm,
		  (SI_Long)2L),Current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = 
		      make_corresponding_icp_remote_procedure_identifier(procedure_to_abort_qm);
	  procedure_to_abort_qm = temp_1;
	  start_writing_icp_message(FIX((SI_Long)235L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qrpc_asynchronous_abort,
			  string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qprocedure_to_abort_qm,string_constant_3,
				Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_corresponding_object_index(procedure_to_abort_qm);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qprocedure_to_abort_qm,string_constant_3,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_corresponding_object_index(procedure_to_abort_qm);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qrpc_asynchronous_abort,string_constant_1,
			    Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qprocedure_to_abort_qm,
			  string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		result_of_write = 
			write_icp_corresponding_object_index(procedure_to_abort_qm);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qprocedure_to_abort_qm,string_constant_3,
			    Qargument,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else
	      write_icp_corresponding_object_index(procedure_to_abort_qm);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_rpc_asynchronous_abort,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qsend_icp_rpc_asynchronous_abort,top,Nil);
		goto end_send_icp_rpc_asynchronous_abort;
	    }
	}
	procedure_to_abort_qm = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : procedure_to_abort_qm;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qsend_icp_rpc_asynchronous_abort;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    case 3:
		      goto l3;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  value = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		  resumable_icp_pop() : 
		  getfq_function_no_default(ISVREF(procedure_to_abort_qm,
		  (SI_Long)2L),Current_icp_port);
	  if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) && value)
	      procedure_to_abort_qm = value;
	  else {
	      value_1 = 
		      make_corresponding_icp_remote_procedure_identifier(procedure_to_abort_qm);
	      if (EQ(icp_suspend_1,value_1)) {
		  resumable_icp_push(value);
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      procedure_to_abort_qm = value_1;
	  }
	l2:
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)235L)))) {
	      resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l3:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qrpc_asynchronous_abort,
			  string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qprocedure_to_abort_qm,string_constant_3,
				Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_corresponding_object_index(procedure_to_abort_qm))) 
				  {
			  resumable_icp_push(FIX((SI_Long)3L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  POP_SPECIAL();
			  goto end_block;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qprocedure_to_abort_qm,string_constant_3,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_corresponding_object_index(procedure_to_abort_qm))) 
			    {
		    resumable_icp_push(FIX((SI_Long)3L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qrpc_asynchronous_abort,string_constant_1,
			    Qmessage,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qprocedure_to_abort_qm,
			  string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		if (EQ(icp_suspend_1,
			write_icp_corresponding_object_index(procedure_to_abort_qm))) 
			    {
		    resumable_icp_push(FIX((SI_Long)3L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qprocedure_to_abort_qm,string_constant_3,
			    Qargument,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (EQ(icp_suspend_1,
		  write_icp_corresponding_object_index(procedure_to_abort_qm))) 
		      {
	      resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(procedure_to_abort_qm);
	      resumable_icp_push(Qsend_icp_rpc_asynchronous_abort);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_rpc_asynchronous_abort;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_rpc_asynchronous_abort:
    return result;
}

static Object Qasync_abort;        /* async-abort */

static Object Qreturned;           /* returned */

static Object Qtelewindows;        /* telewindows */

/* HANDLE-ICP-RPC-ASYNCHRONOUS-ABORT--BODY */
Object handle_icp_rpc_asynchronous_abort__body(procedure_to_abort_qm)
    Object procedure_to_abort_qm;
{
    Object state_1, current_icp_port, current_icp_socket, temp;
    Object disable_resumability, number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, aref_arg_1;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_special(12);

    x_note_fn_call(157,114);
    if (procedure_to_abort_qm) {
	state_1 = ISVREF(procedure_to_abort_qm,(SI_Long)6L);
	if (EQ(state_1,Qoutstanding)) {
	    SVREF(procedure_to_abort_qm,FIX((SI_Long)6L)) = Qasync_abort;
	    receive_remote_procedure_asynchronous_abort(Current_icp_socket,
		    procedure_to_abort_qm);
	}
	if (EQ(state_1,Qoutstanding) || EQ(state_1,Qreturned)) {
	    current_icp_port = ISVREF(Current_icp_socket,(SI_Long)4L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		    11);
	      current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
		      10);
		temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
			(SI_Long)17L ? ISVREF(Current_icp_socket,
			(SI_Long)53L) : Nil;
		if (temp);
		else
		    temp = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
			    Qtelewindows) ? T : Nil;
		disable_resumability = temp;
		PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
			9);
		  number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
		  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
			  8);
		    icp_buffers_for_message_group = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
			    7);
		      icp_buffer_of_start_of_message_series_qm = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
			      6);
			icp_byte_position_of_start_of_message_series_qm = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
				5);
			  number_of_icp_bytes_to_fill_buffer = 
				  FIX((SI_Long)0L);
			  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
				  4);
			    current_icp_buffer = Nil;
			    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
				    3);
			      current_write_icp_byte_position = Nil;
			      PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
				      2);
				number_of_icp_bytes_in_message_group = 
					FIX((SI_Long)0L);
				PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
					1);
				  writing_icp_message_group = 
					  FIXNUM_ADD1(Writing_icp_message_group);
				  PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
					  0);
				    gensymed_symbol = Nil;
				    gensymed_symbol_1 = 0.0;
				    gensymed_symbol_2 = 0.0;
				    if (Profiling_enabled_qm) {
					gensymed_symbol = T;
					gensymed_symbol_1 = 
						DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						(SI_Long)2L),(SI_Long)0L);
					gensymed_symbol_2 = 
						g2ext_unix_time_as_float();
					aref_arg_1 = 
						ISVREF(Profiling_enabled_qm,
						(SI_Long)2L);
					DFLOAT_ISASET_1(aref_arg_1,
						(SI_Long)0L,gensymed_symbol_2);
				    }
				    if (icp_connection_open_p(Current_icp_socket) 
					    &&  
					    !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
						{
					send_icp_rpc_acknowledge_abort(ISVREF(procedure_to_abort_qm,
						(SI_Long)1L));
					end_icp_message_group();
				    }
				    if (Profiling_enabled_qm) {
					gensymed_symbol_3 = 
						g2ext_unix_time_as_float();
					gensymed_symbol_4 = 
						DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						(SI_Long)2L),(SI_Long)0L);
					gensymed_symbol_5 = 
						gensymed_symbol_3 - 
						gensymed_symbol_4;
					aref_arg_1 = 
						ISVREF(Profiling_enabled_qm,
						(SI_Long)6L);
					aref_new_value = gensymed_symbol_5 
						+ 
						DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						(SI_Long)6L),(SI_Long)0L);
					DFLOAT_ISASET_1(aref_arg_1,
						(SI_Long)0L,aref_new_value);
					aref_arg_1 = 
						ISVREF(Profiling_enabled_qm,
						(SI_Long)2L);
					aref_new_value = gensymed_symbol ? 
						gensymed_symbol_1 + 
						gensymed_symbol_5 + 
						(gensymed_symbol_4 - 
						gensymed_symbol_2) : 
						gensymed_symbol_3;
					DFLOAT_ISASET_1(aref_arg_1,
						(SI_Long)0L,aref_new_value);
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
    return VALUES_1(Nil);
}

static Object Qhandle_icp_rpc_asynchronous_abort;  /* handle-icp-rpc-asynchronous-abort */

/* HANDLE-ICP-RPC-ASYNCHRONOUS-ABORT */
Object handle_icp_rpc_asynchronous_abort()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, index_1, index_space, result_of_read;
    Object procedure_to_abort_qm, abort_for_icp_catcher_qm, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(157,115);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qrpc_asynchronous_abort,
			string_constant_1,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qprocedure_to_abort_qm,
			      string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    index_1 = read_icp_corresponding_object_index();
		    index_space = Current_temporary_icp_object_index_space;
		    if (index_space);
		    else
			index_space = Current_standard_icp_object_index_space;
		    if (FIXNUMP(index_1)) {
			if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			    enlarge_index_space(index_space,index_1);
			result_of_read = ISVREF(ISVREF(ISVREF(index_space,
				(SI_Long)2L),IFIX(index_1) >>  -  - 
				(SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		    }
		    else
			result_of_read = Nil;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qprocedure_to_abort_qm,string_constant_3,
				Qargument,T,result_of_read,Nil,Nil);
		    procedure_to_abort_qm = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  index_1 = read_icp_corresponding_object_index();
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      procedure_to_abort_qm = 
			      ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      procedure_to_abort_qm = Nil;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_rpc_asynchronous_abort__body(procedure_to_abort_qm);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qrpc_asynchronous_abort,string_constant_1,
			  Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qprocedure_to_abort_qm,
			    string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  index_1 = read_icp_corresponding_object_index();
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      result_of_read = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      result_of_read = Nil;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qprocedure_to_abort_qm,string_constant_3,
			      Qargument,T,result_of_read,Nil,Nil);
		  procedure_to_abort_qm = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		index_1 = read_icp_corresponding_object_index();
		index_space = Current_temporary_icp_object_index_space;
		if (index_space);
		else
		    index_space = Current_standard_icp_object_index_space;
		if (FIXNUMP(index_1)) {
		    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			enlarge_index_space(index_space,index_1);
		    procedure_to_abort_qm = 
			    ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			    IFIX(index_1) >>  -  - (SI_Long)10L),
			    IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    procedure_to_abort_qm = Nil;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_rpc_asynchronous_abort__body(procedure_to_abort_qm);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_rpc_asynchronous_abort,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qhandle_icp_rpc_asynchronous_abort,top,Nil);
		goto end_handle_icp_rpc_asynchronous_abort;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qrpc_asynchronous_abort,
			string_constant_1,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  procedure_to_abort_qm = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qprocedure_to_abort_qm,
			      string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()))
			index_1 = resumable_icp_pop();
		    else {
			value = read_icp_corresponding_object_index();
			if (EQ(icp_suspend_1,value)) {
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(Qhandle_icp_rpc_asynchronous_abort);
			    result = VALUES_1(Icp_suspend);
			    POP_SPECIAL();
			    POP_SPECIAL();
			    goto end_handle_icp_rpc_asynchronous_abort;
			}
			index_1 = value;
		    }
		    index_space = Current_temporary_icp_object_index_space;
		    if (index_space);
		    else
			index_space = Current_standard_icp_object_index_space;
		    if (FIXNUMP(index_1)) {
			if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			    enlarge_index_space(index_space,index_1);
			result_of_read = ISVREF(ISVREF(ISVREF(index_space,
				(SI_Long)2L),IFIX(index_1) >>  -  - 
				(SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		    }
		    else
			result_of_read = Nil;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qprocedure_to_abort_qm,string_constant_3,
				Qargument,T,result_of_read,Nil,Nil);
		    procedure_to_abort_qm = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			   TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()))
		      index_1 = resumable_icp_pop();
		  else {
		      value = read_icp_corresponding_object_index();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qhandle_icp_rpc_asynchronous_abort);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_rpc_asynchronous_abort;
		      }
		      index_1 = value;
		  }
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      procedure_to_abort_qm = 
			      ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      procedure_to_abort_qm = Nil;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_rpc_asynchronous_abort__body(procedure_to_abort_qm);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qrpc_asynchronous_abort,string_constant_1,
			  Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		procedure_to_abort_qm = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qprocedure_to_abort_qm,
			    string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			   TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()))
		      index_1 = resumable_icp_pop();
		  else {
		      value = read_icp_corresponding_object_index();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qhandle_icp_rpc_asynchronous_abort);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_rpc_asynchronous_abort;
		      }
		      index_1 = value;
		  }
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      result_of_read = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      result_of_read = Nil;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qprocedure_to_abort_qm,string_constant_3,
			      Qargument,T,result_of_read,Nil,Nil);
		  procedure_to_abort_qm = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()))
		    index_1 = resumable_icp_pop();
		else {
		    value = read_icp_corresponding_object_index();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_rpc_asynchronous_abort);
			result = VALUES_1(Icp_suspend);
			goto end_handle_icp_rpc_asynchronous_abort;
		    }
		    index_1 = value;
		}
		index_space = Current_temporary_icp_object_index_space;
		if (index_space);
		else
		    index_space = Current_standard_icp_object_index_space;
		if (FIXNUMP(index_1)) {
		    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			enlarge_index_space(index_space,index_1);
		    procedure_to_abort_qm = 
			    ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			    IFIX(index_1) >>  -  - (SI_Long)10L),
			    IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    procedure_to_abort_qm = Nil;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_rpc_asynchronous_abort__body(procedure_to_abort_qm);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_rpc_asynchronous_abort:
    return result;
}

static Object Qsend_icp_rpc_acknowledge_abort;  /* send-icp-rpc-acknowledge-abort */

static Object Qrpc_acknowledge_abort;  /* rpc-acknowledge-abort */

static Object Qprocedure_index;    /* procedure-index */

/* SEND-ICP-RPC-ACKNOWLEDGE-ABORT */
Object send_icp_rpc_acknowledge_abort(procedure_index)
    Object procedure_index;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(3);
    Object result;

    x_note_fn_call(157,116);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qsend_icp_rpc_acknowledge_abort;
	  }
	  start_writing_icp_message(FIX((SI_Long)240L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qrpc_acknowledge_abort,
			  string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qprocedure_index,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_unsigned_integer(procedure_index);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qprocedure_index,string_constant_2,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_unsigned_integer(procedure_index);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qrpc_acknowledge_abort,string_constant_1,
			    Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qprocedure_index,
			  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		result_of_write = write_icp_unsigned_integer(procedure_index);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qprocedure_index,string_constant_2,Qargument,
			    Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else
	      write_icp_unsigned_integer(procedure_index);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_rpc_acknowledge_abort,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qsend_icp_rpc_acknowledge_abort,top,Nil);
		goto end_send_icp_rpc_acknowledge_abort;
	    }
	}
	procedure_index = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : procedure_index;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qsend_icp_rpc_acknowledge_abort;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)240L)))) {
	      resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qrpc_acknowledge_abort,
			  string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qprocedure_index,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_unsigned_integer(procedure_index))) {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  POP_SPECIAL();
			  goto end_block;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qprocedure_index,string_constant_2,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_unsigned_integer(procedure_index))) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qrpc_acknowledge_abort,string_constant_1,
			    Qmessage,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qprocedure_index,
			  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		if (EQ(icp_suspend_1,
			write_icp_unsigned_integer(procedure_index))) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qprocedure_index,string_constant_2,Qargument,
			    Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (EQ(icp_suspend_1,
		  write_icp_unsigned_integer(procedure_index))) {
	      resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(procedure_index);
	      resumable_icp_push(Qsend_icp_rpc_acknowledge_abort);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_rpc_acknowledge_abort;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_rpc_acknowledge_abort:
    return result;
}

/* HANDLE-ICP-RPC-ACKNOWLEDGE-ABORT--BODY */
Object handle_icp_rpc_acknowledge_abort__body(procedure_index)
    Object procedure_index;
{
    Object identifier_qm;

    x_note_fn_call(157,117);
    identifier_qm = 
	    lookup_remote_procedure_identifier_from_index(procedure_index);
    if (identifier_qm) {
	if (ISVREF(identifier_qm,(SI_Long)9L))
	    reclaim_outgoing_remote_procedure_identifier_and_index(identifier_qm);
	else
	    rpc_acknowledge_abort_error(identifier_qm);
    }
    else
	rpc_acknowledge_abort_error(procedure_index);
    return VALUES_1(Nil);
}

static Object Qhandle_icp_rpc_acknowledge_abort;  /* handle-icp-rpc-acknowledge-abort */

/* HANDLE-ICP-RPC-ACKNOWLEDGE-ABORT */
Object handle_icp_rpc_acknowledge_abort()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read, procedure_index;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(157,118);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qrpc_acknowledge_abort,
			string_constant_1,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qprocedure_index,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_unsigned_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qprocedure_index,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    procedure_index = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  procedure_index = read_icp_unsigned_integer();
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_rpc_acknowledge_abort__body(procedure_index);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qrpc_acknowledge_abort,string_constant_1,
			  Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qprocedure_index,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_unsigned_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qprocedure_index,string_constant_2,Qargument,
			      T,result_of_read,Nil,Nil);
		  procedure_index = result_of_read;
		POP_SPECIAL();
	    }
	    else
		procedure_index = read_icp_unsigned_integer();
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_rpc_acknowledge_abort__body(procedure_index);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_rpc_acknowledge_abort,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qhandle_icp_rpc_acknowledge_abort,top,Nil);
		goto end_handle_icp_rpc_acknowledge_abort;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qrpc_acknowledge_abort,
			string_constant_1,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  procedure_index = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qprocedure_index,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_unsigned_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_rpc_acknowledge_abort);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_rpc_acknowledge_abort;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qprocedure_index,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    procedure_index = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_rpc_acknowledge_abort);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_rpc_acknowledge_abort;
		  }
		  procedure_index = value;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_rpc_acknowledge_abort__body(procedure_index);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qrpc_acknowledge_abort,string_constant_1,
			  Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		procedure_index = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qprocedure_index,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_rpc_acknowledge_abort);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_rpc_acknowledge_abort;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qprocedure_index,string_constant_2,Qargument,
			      T,result_of_read,Nil,Nil);
		  procedure_index = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qhandle_icp_rpc_acknowledge_abort);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_rpc_acknowledge_abort;
		}
		procedure_index = value;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_rpc_acknowledge_abort__body(procedure_index);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_rpc_acknowledge_abort:
    return result;
}

static Object string_constant_6;   /* "Received a rpc-acknowledge-abort message with no remote-procedure-identifier" */

static Object string_constant_7;   /* "Received an unexpected rpc-acknowledge-abort message" */

static Object string_constant_8;   /* "~%Error in rpc-acknowledge-abort, for ~NF ~A~
				    *        ~%~A: ~A~%"
				    */

/* RPC-ACKNOWLEDGE-ABORT-ERROR */
Object rpc_acknowledge_abort_error(identifier_or_index)
    Object identifier_or_index;
{
    Object description, temp, temp_1;

    x_note_fn_call(157,119);
    description = icp_socket_description(Current_icp_socket);
    temp = ISVREF(Current_icp_socket,(SI_Long)5L);
    temp_1 = FIXNUMP(identifier_or_index) ? string_constant_6 : 
	    string_constant_7;
    notify_user_at_console(5,string_constant_8,temp,description,temp_1,
	    FIXNUMP(identifier_or_index) ? identifier_or_index : 
	    ISVREF(identifier_or_index,(SI_Long)10L));
    reclaim_text_string(description);
    return VALUES_1(Nil);
}

Object Maximum_concurrent_remote_procedure_calls = UNBOUND;

static Object Qremote_procedure_identifier_map;  /* remote-procedure-identifier-map */

/* MAKE-INITIAL-REMOTE-PROCEDURE-IDENTIFIER-ARRAY */
Object make_initial_remote_procedure_identifier_array()
{
    Object map_1;

    x_note_fn_call(157,120);
    map_1 = make_index_space_1(Qremote_procedure_identifier_map,Nil);
    enlarge_index_space(map_1,FIX((SI_Long)20L));
    assign_index_in_index_space(map_1);
    return VALUES_1(map_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Remote_procedure_identifier_array, Qremote_procedure_identifier_array);

/* MAKE-OUTGOING-REMOTE-PROCEDURE-IDENTIFIER-WITH-INFO */
Object make_outgoing_remote_procedure_identifier_with_info(return_included_attributes_spec,
	    return_excluded_attributes_spec,
	    return_included_system_attributes_spec,
	    return_include_all_system_attributes_spec,
	    return_include_all_system_attributes_except_spec,
	    return_kind_spec,return_varargs_p)
    Object return_included_attributes_spec, return_excluded_attributes_spec;
    Object return_included_system_attributes_spec;
    Object return_include_all_system_attributes_spec;
    Object return_include_all_system_attributes_except_spec, return_kind_spec;
    Object return_varargs_p;
{
    Object map_1, index_1, identifier, svref_arg_1;
    SI_Long svref_arg_2;

    x_note_fn_call(157,121);
    map_1 = Remote_procedure_identifier_array;
    index_1 = assign_index_in_index_space(map_1);
    identifier = make_outgoing_remote_procedure_identifier(index_1,
	    make_remote_procedure_item_passing_info_from_specs(Nil,
	    return_included_attributes_spec,
	    return_excluded_attributes_spec,
	    return_included_system_attributes_spec,
	    return_include_all_system_attributes_spec,
	    return_include_all_system_attributes_except_spec,
	    return_kind_spec,return_varargs_p));
    if (FIXNUM_GE(index_1,ISVREF(map_1,(SI_Long)4L)))
	enlarge_index_space(map_1,index_1);
    svref_arg_1 = ISVREF(ISVREF(map_1,(SI_Long)2L),IFIX(index_1) >>  -  - 
	    (SI_Long)10L);
    svref_arg_2 = IFIX(index_1) & (SI_Long)1023L;
    ISVREF(svref_arg_1,svref_arg_2) = identifier;
    return VALUES_1(identifier);
}

/* RECLAIM-OUTGOING-REMOTE-PROCEDURE-IDENTIFIER-AND-INDEX */
Object reclaim_outgoing_remote_procedure_identifier_and_index(remote_procedure_identifier)
    Object remote_procedure_identifier;
{
    Object map_1, index_1, svref_arg_1;
    SI_Long svref_arg_2;

    x_note_fn_call(157,122);
    map_1 = Remote_procedure_identifier_array;
    index_1 = ISVREF(remote_procedure_identifier,(SI_Long)1L);
    reclaim_icp_object_map_for_remote_procedure_identifier(remote_procedure_identifier);
    if (FIXNUM_GE(index_1,ISVREF(map_1,(SI_Long)4L)))
	enlarge_index_space(map_1,index_1);
    svref_arg_1 = ISVREF(ISVREF(map_1,(SI_Long)2L),IFIX(index_1) >>  -  - 
	    (SI_Long)10L);
    svref_arg_2 = IFIX(index_1) & (SI_Long)1023L;
    ISVREF(svref_arg_1,svref_arg_2) = Nil;
    deassign_index_in_index_space(index_1,map_1);
    reclaim_outgoing_remote_procedure_identifier(remote_procedure_identifier);
    return VALUES_1(Nil);
}

/* LOOKUP-REMOTE-PROCEDURE-IDENTIFIER-FROM-INDEX */
Object lookup_remote_procedure_identifier_from_index(procedure_index)
    Object procedure_index;
{
    Object vector_1, temp;
    SI_Long index_1;

    x_note_fn_call(157,123);
    vector_1 = ISVREF(Remote_procedure_identifier_array,(SI_Long)2L);
    index_1 = IFIX(procedure_index) >>  -  - (SI_Long)10L;
    vector_1 = vector_1 && index_1 < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1)) ? ISVREF(vector_1,
	    index_1) : Qnil;
    index_1 = IFIX(procedure_index) & (SI_Long)1023L;
    temp = vector_1 && index_1 < IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1)) 
	    ? ISVREF(vector_1,index_1) : Qnil;
    return VALUES_1(temp);
}

/* RECLAIM-OUTGOING-REMOTE-PROCEDURE-IDENTIFIER-FROM-INDEX */
Object reclaim_outgoing_remote_procedure_identifier_from_index(procedure_index)
    Object procedure_index;
{
    Object identifier_qm;

    x_note_fn_call(157,124);
    identifier_qm = 
	    lookup_remote_procedure_identifier_from_index(procedure_index);
    if (identifier_qm)
	reclaim_outgoing_remote_procedure_identifier_and_index(identifier_qm);
    return VALUES_1(Nil);
}

/* GSI-DEFINE-NEW-REMOTE-PROCEDURE */
Object gsi_define_new_remote_procedure(local_handle)
    Object local_handle;
{
    Object svref_new_value;

    x_note_fn_call(157,125);
    svref_new_value = make_remote_procedure_name_1(ISVREF(local_handle,
	    (SI_Long)1L));
    return VALUES_1(SVREF(local_handle,FIX((SI_Long)2L)) = svref_new_value);
}

static Object Qindex_space;        /* index-space */

static Object Qg2_defstruct_structure_name_interned_list_g2_struct;  /* g2-defstruct-structure-name::interned-list-g2-struct */

/* WRITE-ICP-INDEX-SPACE */
Object write_icp_index_space(index_space)
    Object index_space;
{
    Object tracep, byte_count_before, current_icp_write_trace_level;
    Object last_index, thing, index_1, writing_resumable_icp_messages_p, x2;
    Object result_of_write;
    SI_Long i, ab_loop_bind_;
    char temp;
    Declare_special(2);
    Object result;

    x_note_fn_call(157,126);
    if (Icp_write_trace_cutoff_level_qm) {
	tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	if (tracep);
	else
	    tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= (SI_Long)4L ?
		     T : Nil;
	if (tracep) {
	    emit_icp_write_trace(T,Nil,Nil,Qindex_space,string_constant_5,
		    Qvalue,T,index_space,Nil,Nil);
	    byte_count_before = instantaneous_icp_writer_byte_count();
	}
	else
	    byte_count_before = Nil;
	current_icp_write_trace_level = 
		FIXNUM_ADD1(Current_icp_write_trace_level);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		1);
	  last_index = ISVREF(index_space,(SI_Long)3L);
	  write_icp_unsigned_integer(FIXNUM_ADD1(last_index));
	  i = (SI_Long)0L;
	  ab_loop_bind_ = IFIX(last_index);
	  thing = Nil;
	next_loop:
	  if (i > ab_loop_bind_)
	      goto end_loop;
	  if (i >= IFIX(ISVREF(index_space,(SI_Long)4L)))
	      enlarge_index_space(index_space,FIX(i));
	  thing = ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),i >>  -  - 
		  (SI_Long)10L),i & (SI_Long)1023L);
	  if (SYMBOLP(thing))
	      write_icp_symbol_as_value_type(thing);
	  else if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
		  Qg2_defstruct_structure_name_interned_list_g2_struct)) {
	      write_icp_byte(FIX((SI_Long)90L));
	      write_icp_interned_list_as_value_type(thing);
	  }
	  else if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
		  Qg2_defstruct_structure_name_remote_procedure_name_g2_struct)) 
		      {
	      index_1 = 
		      get_icp_object_index_for_remote_procedure_name(thing,
		      Current_icp_port);
	      if (index_1) {
		  write_icp_byte(FIX((SI_Long)70L));
		  write_icp_corresponding_object_index(index_1);
	      }
	      else {
		  write_icp_byte(FIX((SI_Long)91L));
		  write_icp_maybe_suspend();
		  writing_resumable_icp_messages_p = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Writing_resumable_icp_messages_p,Qwriting_resumable_icp_messages_p,writing_resumable_icp_messages_p,
			  0);
		    write_icp_corresponding_object_index(establish_new_object_index_for_remote_procedure_name(3,
			    thing,Current_icp_port,Nil));
		    write_icp_symbol_as_value_type(ISVREF(thing,(SI_Long)1L));
		  POP_SPECIAL();
	      }
	  }
	  else {
	      temp = SIMPLE_VECTOR_P(thing) ? EQ(ISVREF(thing,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      : TRUEP(Qnil);
	      if (temp);
	      else if (SIMPLE_VECTOR_P(thing) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) > (SI_Long)2L 
		      &&  !EQ(ISVREF(thing,(SI_Long)1L),
		      Qavailable_frame_vector)) {
		  x2 = ISVREF(thing,(SI_Long)1L);
		  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp)
		  write_icp_item_reference_1_function(thing);
	      else
		  write_icp_byte(FIX((SI_Long)0L));
	  }
	  i = i + (SI_Long)1L;
	  goto next_loop;
	end_loop:
	  result_of_write = Qnil;
	  if (tracep)
	      emit_icp_write_trace(Nil,byte_count_before,
		      instantaneous_icp_writer_byte_count(),Qindex_space,
		      string_constant_5,Qvalue,Nil,Nil,Nil,Nil);
	  result = VALUES_1(result_of_write);
	POP_SPECIAL();
	return result;
    }
    else {
	last_index = ISVREF(index_space,(SI_Long)3L);
	write_icp_unsigned_integer(FIXNUM_ADD1(last_index));
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(last_index);
	thing = Nil;
      next_loop_1:
	if (i > ab_loop_bind_)
	    goto end_loop_1;
	if (i >= IFIX(ISVREF(index_space,(SI_Long)4L)))
	    enlarge_index_space(index_space,FIX(i));
	thing = ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),i >>  -  - 
		(SI_Long)10L),i & (SI_Long)1023L);
	if (SYMBOLP(thing))
	    write_icp_symbol_as_value_type(thing);
	else if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
		Qg2_defstruct_structure_name_interned_list_g2_struct)) {
	    write_icp_byte(FIX((SI_Long)90L));
	    write_icp_interned_list_as_value_type(thing);
	}
	else if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
		Qg2_defstruct_structure_name_remote_procedure_name_g2_struct)) 
		    {
	    index_1 = get_icp_object_index_for_remote_procedure_name(thing,
		    Current_icp_port);
	    if (index_1) {
		write_icp_byte(FIX((SI_Long)70L));
		write_icp_corresponding_object_index(index_1);
	    }
	    else {
		write_icp_byte(FIX((SI_Long)91L));
		write_icp_maybe_suspend();
		writing_resumable_icp_messages_p = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Writing_resumable_icp_messages_p,Qwriting_resumable_icp_messages_p,writing_resumable_icp_messages_p,
			0);
		  write_icp_corresponding_object_index(establish_new_object_index_for_remote_procedure_name(3,
			  thing,Current_icp_port,Nil));
		  write_icp_symbol_as_value_type(ISVREF(thing,(SI_Long)1L));
		POP_SPECIAL();
	    }
	}
	else {
	    temp = SIMPLE_VECTOR_P(thing) ? EQ(ISVREF(thing,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    : TRUEP(Qnil);
	    if (temp);
	    else if (SIMPLE_VECTOR_P(thing) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(thing,(SI_Long)1L),
			Qavailable_frame_vector)) {
		x2 = ISVREF(thing,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		write_icp_item_reference_1_function(thing);
	    else
		write_icp_byte(FIX((SI_Long)0L));
	}
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
}

static Object Qtemporary_icp_object_index_space;  /* temporary-icp-object-index-space */

/* READ-ICP-INDEX-SPACE */
Object read_icp_index_space()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, size;
    Object last_index, index_space, thing, temp, svref_arg_1, result_of_read;
    SI_Long i, ab_loop_bind_, svref_arg_2;
    Declare_special(1);
    Object result;

    x_note_fn_call(157,127);
    if (Icp_read_trace_cutoff_level_qm) {
	tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	if (tracep);
	else
	    tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= (SI_Long)4L ? 
		    T : Nil;
	if (tracep) {
	    emit_icp_read_trace(T,Nil,Nil,Qindex_space,string_constant_5,
		    Qvalue,Nil,Nil,Nil,Nil);
	    byte_count_before = instantaneous_icp_reader_byte_count();
	}
	else
	    byte_count_before = Nil;
	current_icp_read_trace_level = 
		FIXNUM_ADD1(Current_icp_read_trace_level);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		0);
	  size = read_icp_unsigned_integer();
	  last_index = FIXNUM_SUB1(size);
	  index_space = 
		  make_index_space_1(Qtemporary_icp_object_index_space,Nil);
	  SVREF(index_space,FIX((SI_Long)3L)) = last_index;
	  i = (SI_Long)0L;
	  ab_loop_bind_ = IFIX(last_index);
	  thing = Nil;
	next_loop:
	  if (i > ab_loop_bind_)
	      goto end_loop;
	  temp = peek_icp_byte();
	  if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		  FIX((SI_Long)127L))))
	      thing = Nil;
	  else
	      switch (INTEGER_TO_CHAR(temp)) {
		case 70:
		case 71:
		case 72:
		case 75:
		case 3:
		  thing = read_icp_symbol_as_value_type();
		  break;
		case 91:
		  read_icp_byte();
		  temp = read_icp_corresponding_object_index();
		  thing = store_corresponding_icp_object(temp,
			  make_remote_procedure_name_1(read_icp_symbol_as_value_type()));
		  break;
		case 90:
		  read_icp_byte();
		  thing = read_icp_interned_list_as_value_type();
		  break;
		case 60:
		case 61:
		case 62:
		  thing = read_icp_item_reference();
		  break;
		default:
		  thing = Nil;
		  break;
	      }
	  if (i >= IFIX(ISVREF(index_space,(SI_Long)4L)))
	      enlarge_index_space(index_space,FIX(i));
	  svref_arg_1 = ISVREF(ISVREF(index_space,(SI_Long)2L),i >>  -  - 
		  (SI_Long)10L);
	  svref_arg_2 = i & (SI_Long)1023L;
	  ISVREF(svref_arg_1,svref_arg_2) = thing;
	  i = i + (SI_Long)1L;
	  goto next_loop;
	end_loop:;
	  result_of_read = index_space;
	  if (tracep)
	      emit_icp_read_trace(Nil,byte_count_before,
		      instantaneous_icp_reader_byte_count(),Qindex_space,
		      string_constant_5,Qvalue,T,result_of_read,Nil,Nil);
	  result = VALUES_1(result_of_read);
	POP_SPECIAL();
	return result;
    }
    else {
	size = read_icp_unsigned_integer();
	last_index = FIXNUM_SUB1(size);
	index_space = make_index_space_1(Qtemporary_icp_object_index_space,
		Nil);
	SVREF(index_space,FIX((SI_Long)3L)) = last_index;
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(last_index);
	thing = Nil;
      next_loop_1:
	if (i > ab_loop_bind_)
	    goto end_loop_1;
	temp = peek_icp_byte();
	if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		FIX((SI_Long)127L))))
	    thing = Nil;
	else
	    switch (INTEGER_TO_CHAR(temp)) {
	      case 70:
	      case 71:
	      case 72:
	      case 75:
	      case 3:
		thing = read_icp_symbol_as_value_type();
		break;
	      case 91:
		read_icp_byte();
		temp = read_icp_corresponding_object_index();
		thing = store_corresponding_icp_object(temp,
			make_remote_procedure_name_1(read_icp_symbol_as_value_type()));
		break;
	      case 90:
		read_icp_byte();
		thing = read_icp_interned_list_as_value_type();
		break;
	      case 60:
	      case 61:
	      case 62:
		thing = read_icp_item_reference();
		break;
	      default:
		thing = Nil;
		break;
	    }
	if (i >= IFIX(ISVREF(index_space,(SI_Long)4L)))
	    enlarge_index_space(index_space,FIX(i));
	svref_arg_1 = ISVREF(ISVREF(index_space,(SI_Long)2L),i >>  -  - 
		(SI_Long)10L);
	svref_arg_2 = i & (SI_Long)1023L;
	ISVREF(svref_arg_1,svref_arg_2) = thing;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
	return VALUES_1(index_space);
    }
}

static Object Qsend_icp_define_temporary_index_space;  /* send-icp-define-temporary-index-space */

static Object Qdefine_temporary_index_space;  /* define-temporary-index-space */

/* SEND-ICP-DEFINE-TEMPORARY-INDEX-SPACE */
Object send_icp_define_temporary_index_space(index_space)
    Object index_space;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write;
    Declare_special(3);

    x_note_fn_call(157,128);
    index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
    PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
	    2);
      if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
	      Size_of_basic_backtrace_information),
	      Maximum_index_in_backtrace_stack_for_internal_error)) {
	  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp;
	  temp = Backtrace_stack_for_internal_error;
	  svref_arg_2 = Index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp;
	  temp = Backtrace_stack_for_internal_error;
	  svref_arg_2 = Index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = Nil;
	  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp;
	  temp = Backtrace_stack_for_internal_error;
	  svref_arg_2 = Index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = Qsend_icp_define_temporary_index_space;
      }
      start_writing_icp_message(FIX((SI_Long)301L));
      if (Icp_write_trace_cutoff_level_qm) {
	  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	  if (tracep);
	  else
	      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
		      (SI_Long)2L ? T : Nil;
	  if (tracep) {
	      emit_icp_write_trace(T,Nil,Nil,Qdefine_temporary_index_space,
		      string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
	      byte_count_before = instantaneous_icp_writer_byte_count();
	  }
	  else
	      byte_count_before = Nil;
	  current_icp_write_trace_level = 
		  FIXNUM_ADD1(Current_icp_write_trace_level);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		  1);
	    if (Icp_write_trace_cutoff_level_qm) {
		tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		if (tracep_1);
		else
		    tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			    (SI_Long)3L ? T : Nil;
		if (tracep_1) {
		    emit_icp_write_trace(T,Nil,Nil,Qindex_space,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before_1 = 
			    instantaneous_icp_writer_byte_count();
		}
		else
		    byte_count_before_1 = Nil;
		current_icp_write_trace_level = 
			FIXNUM_ADD1(Current_icp_write_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			0);
		  result_of_write = write_icp_index_space(index_space);
		  if (tracep_1)
		      emit_icp_write_trace(Nil,byte_count_before_1,
			      instantaneous_icp_writer_byte_count(),
			      Qindex_space,string_constant_2,Qargument,Nil,
			      Nil,Nil,Nil);
		POP_SPECIAL();
	    }
	    else
		result_of_write = write_icp_index_space(index_space);
	    if (tracep)
		emit_icp_write_trace(Nil,byte_count_before,
			instantaneous_icp_writer_byte_count(),
			Qdefine_temporary_index_space,string_constant_1,
			Qmessage,Nil,Nil,Nil,Nil);
	  POP_SPECIAL();
      }
      else if (Icp_write_trace_cutoff_level_qm) {
	  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	  if (tracep);
	  else
	      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
		      (SI_Long)3L ? T : Nil;
	  if (tracep) {
	      emit_icp_write_trace(T,Nil,Nil,Qindex_space,
		      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
	      byte_count_before = instantaneous_icp_writer_byte_count();
	  }
	  else
	      byte_count_before = Nil;
	  current_icp_write_trace_level = 
		  FIXNUM_ADD1(Current_icp_write_trace_level);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		  0);
	    result_of_write = write_icp_index_space(index_space);
	    if (tracep)
		emit_icp_write_trace(Nil,byte_count_before,
			instantaneous_icp_writer_byte_count(),Qindex_space,
			string_constant_2,Qargument,Nil,Nil,Nil,Nil);
	  POP_SPECIAL();
      }
      else
	  write_icp_index_space(index_space);
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* HANDLE-ICP-DEFINE-TEMPORARY-INDEX-SPACE--BODY */
Object handle_icp_define_temporary_index_space__body(index_space)
    Object index_space;
{
    Object svref_arg_1;

    x_note_fn_call(157,129);
    svref_arg_1 = Current_icp_port;
    SVREF(svref_arg_1,FIX((SI_Long)19L)) = index_space;
    Current_temporary_icp_object_index_space = index_space;
    return VALUES_1(Nil);
}

/* HANDLE-ICP-DEFINE-TEMPORARY-INDEX-SPACE */
Object handle_icp_define_temporary_index_space()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read, index_space;
    Declare_special(2);

    x_note_fn_call(157,130);
    if (Icp_read_trace_cutoff_level_qm) {
	tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	if (tracep);
	else
	    tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= (SI_Long)2L ? 
		    T : Nil;
	if (tracep) {
	    emit_icp_read_trace(T,Nil,Nil,Qdefine_temporary_index_space,
		    string_constant_1,Qmessage,Nil,Nil,Nil,T);
	    byte_count_before = instantaneous_icp_reader_byte_count();
	}
	else
	    byte_count_before = Nil;
	current_icp_read_trace_level = 
		FIXNUM_ADD1(Current_icp_read_trace_level);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		1);
	  if (Icp_read_trace_cutoff_level_qm) {
	      if (Icp_read_trace_cutoff_level_qm) {
		  tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep_1);
		  else
		      tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
	      }
	      else
		  tracep_1 = Nil;
	      if (tracep_1) {
		  emit_icp_read_trace(T,Nil,Nil,Qindex_space,
			  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before_1 = instantaneous_icp_reader_byte_count();
	      }
	      else
		  byte_count_before_1 = Nil;
	      current_icp_read_trace_level = 
		      FIXNUM_ADD1(Current_icp_read_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		      0);
		result_of_read = read_icp_index_space();
		if (tracep_1)
		    emit_icp_read_trace(Nil,byte_count_before_1,
			    instantaneous_icp_reader_byte_count(),
			    Qindex_space,string_constant_2,Qargument,T,
			    result_of_read,Nil,Nil);
		index_space = result_of_read;
	      POP_SPECIAL();
	  }
	  else
	      index_space = read_icp_index_space();
	  result_of_read = 
		  handle_icp_define_temporary_index_space__body(index_space);
	  if (tracep)
	      emit_icp_read_trace(Nil,byte_count_before,
		      instantaneous_icp_reader_byte_count(),
		      Qdefine_temporary_index_space,string_constant_1,
		      Qmessage,Nil,result_of_read,Nil,T);
	POP_SPECIAL();
    }
    else {
	if (Icp_read_trace_cutoff_level_qm) {
	    if (Icp_read_trace_cutoff_level_qm) {
		tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		if (tracep);
		else
		    tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			    (SI_Long)3L ? T : Nil;
	    }
	    else
		tracep = Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qindex_space,
			string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      result_of_read = read_icp_index_space();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qindex_space,string_constant_2,Qargument,T,
			  result_of_read,Nil,Nil);
	      index_space = result_of_read;
	    POP_SPECIAL();
	}
	else
	    index_space = read_icp_index_space();
	handle_icp_define_temporary_index_space__body(index_space);
    }
    return VALUES_1(Nil);
}

static Object Qsend_icp_release_temporary_index_space;  /* send-icp-release-temporary-index-space */

static Object Qrelease_temporary_index_space;  /* release-temporary-index-space */

/* SEND-ICP-RELEASE-TEMPORARY-INDEX-SPACE */
Object send_icp_release_temporary_index_space()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, result_of_write;
    Declare_special(2);

    x_note_fn_call(157,131);
    index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
    PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
	    1);
      if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
	      Size_of_basic_backtrace_information),
	      Maximum_index_in_backtrace_stack_for_internal_error)) {
	  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp;
	  temp = Backtrace_stack_for_internal_error;
	  svref_arg_2 = Index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp;
	  temp = Backtrace_stack_for_internal_error;
	  svref_arg_2 = Index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = Nil;
	  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp;
	  temp = Backtrace_stack_for_internal_error;
	  svref_arg_2 = Index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = Qsend_icp_release_temporary_index_space;
      }
      start_writing_icp_message(FIX((SI_Long)302L));
      if (Icp_write_trace_cutoff_level_qm) {
	  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	  if (tracep);
	  else
	      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
		      (SI_Long)2L ? T : Nil;
	  if (tracep) {
	      emit_icp_write_trace(T,Nil,Nil,
		      Qrelease_temporary_index_space,string_constant_1,
		      Qmessage,Nil,Nil,Nil,Nil);
	      byte_count_before = instantaneous_icp_writer_byte_count();
	  }
	  else
	      byte_count_before = Nil;
	  current_icp_write_trace_level = 
		  FIXNUM_ADD1(Current_icp_write_trace_level);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		  0);
	    result_of_write = Nil;
	    if (tracep)
		emit_icp_write_trace(Nil,byte_count_before,
			instantaneous_icp_writer_byte_count(),
			Qrelease_temporary_index_space,string_constant_1,
			Qmessage,Nil,Nil,Nil,Nil);
	  POP_SPECIAL();
      }
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* HANDLE-ICP-RELEASE-TEMPORARY-INDEX-SPACE--BODY */
Object handle_icp_release_temporary_index_space__body()
{
    Object svref_arg_1;

    x_note_fn_call(157,132);
    reclaim_if_index_space(ISVREF(Current_icp_port,(SI_Long)19L));
    svref_arg_1 = Current_icp_port;
    SVREF(svref_arg_1,FIX((SI_Long)19L)) = Nil;
    Current_temporary_icp_object_index_space = Nil;
    return VALUES_1(Nil);
}

/* HANDLE-ICP-RELEASE-TEMPORARY-INDEX-SPACE */
Object handle_icp_release_temporary_index_space()
{
    Object tracep, byte_count_before, current_icp_read_trace_level;
    Object result_of_read;
    Declare_special(1);

    x_note_fn_call(157,133);
    if (Icp_read_trace_cutoff_level_qm) {
	tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	if (tracep);
	else
	    tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= (SI_Long)2L ? 
		    T : Nil;
	if (tracep) {
	    emit_icp_read_trace(T,Nil,Nil,Qrelease_temporary_index_space,
		    string_constant_1,Qmessage,Nil,Nil,Nil,T);
	    byte_count_before = instantaneous_icp_reader_byte_count();
	}
	else
	    byte_count_before = Nil;
	current_icp_read_trace_level = 
		FIXNUM_ADD1(Current_icp_read_trace_level);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		0);
	  result_of_read = handle_icp_release_temporary_index_space__body();
	  if (tracep)
	      emit_icp_read_trace(Nil,byte_count_before,
		      instantaneous_icp_reader_byte_count(),
		      Qrelease_temporary_index_space,string_constant_1,
		      Qmessage,Nil,result_of_read,Nil,T);
	POP_SPECIAL();
    }
    else
	handle_icp_release_temporary_index_space__body();
    return VALUES_1(Nil);
}

void rpc_common1_INIT()
{
    Object temp, reclaim_structure_for_gsi_local_function_1;
    Object reclaim_structure_for_gsi_remote_procedure_1;
    Object reclaim_structure_for_remote_procedure_name_1;
    Object reclaim_structure_for_remote_procedure_identifier_1;
    Object reclaim_structure_for_remote_procedure_item_passing_info_1;
    Object reclaim_structure_for_interned_remote_procedure_item_passing_info_1;
    Object Qhandle_icp_release_temporary_index_space, AB_package;
    Object Qhandle_icp_define_temporary_index_space;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, list_constant_4, Qrpc_common1;
    Object Qmake_initial_remote_procedure_identifier_array, Kfuncall;
    Object Qreclaim_icp_port_entry_for_remote_procedure_identifier;
    Object Qreclaim_remote_procedure_identifier_for_connection_loss;
    Object Qreclaim_incoming_remote_procedure_identifier;
    Object Qremote_procedure_identifier, list_constant_3;
    Object Qicp_object_map_for_remote_procedure_identifier;
    Object Qinterned_remote_procedure_item_passing_info, Qreclaim_structure;
    Object Qoutstanding_interned_remote_procedure_item_passing_info_count;
    Object Qinterned_remote_procedure_item_passing_info_structure_memory_usage;
    Object Qutilities2, string_constant_21, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_20, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object Qremote_procedure_item_passing_info;
    Object Qoutstanding_remote_procedure_item_passing_info_count;
    Object Qremote_procedure_item_passing_info_structure_memory_usage;
    Object string_constant_19, string_constant_18;
    Object Qoutstanding_remote_procedure_identifier_count;
    Object Qremote_procedure_identifier_structure_memory_usage;
    Object string_constant_17, string_constant_16;
    Object Qreclaim_icp_port_entry_for_remote_procedure_name;
    Object Qreclaim_remote_procedure_name_for_connection_loss;
    Object Qreclaim_remote_procedure_name_structure, Qremote_procedure_name;
    Object list_constant_2, Qicp_object_map_for_remote_procedure_name;
    Object Qoutstanding_remote_procedure_name_count;
    Object Qremote_procedure_name_structure_memory_usage, string_constant_15;
    Object string_constant_14, Qgsi_remote_procedure;
    Object Qoutstanding_gsi_remote_procedure_count;
    Object Qgsi_remote_procedure_structure_memory_usage, string_constant_13;
    Object string_constant_12, Qgsi_local_function;
    Object Qoutstanding_gsi_local_function_count;
    Object Qgsi_local_function_structure_memory_usage, string_constant_11;
    Object string_constant_10, string_constant_9, Qproc_cons_memory_usage;
    Object Qoutstanding_proc_conses, list_constant_1;
    Object Qproc_cons_counter_vector, Qmake_thread_array, list_constant;
    Object Qavailable_proc_conses_tail_vector, Qavailable_proc_conses_vector;

    x_note_fn_call(157,134);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qavailable_proc_conses = STATIC_SYMBOL("AVAILABLE-PROC-CONSES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_proc_conses,Available_proc_conses);
    Qrpc_common1 = STATIC_SYMBOL("RPC-COMMON1",AB_package);
    record_system_variable(Qavailable_proc_conses,Qrpc_common1,Nil,Qnil,Qt,
	    Qnil,Qnil);
    Qavailable_proc_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-PROC-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_proc_conses_tail,
	    Available_proc_conses_tail);
    record_system_variable(Qavailable_proc_conses_tail,Qrpc_common1,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_proc_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-PROC-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_proc_conses_vector,
	    Available_proc_conses_vector);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_thread_array = STATIC_SYMBOL("MAKE-THREAD-ARRAY",AB_package);
    list_constant = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,Qnil);
    record_system_variable(Qavailable_proc_conses_vector,Qrpc_common1,
	    list_constant,Qnil,Qt,Qnil,Qnil);
    Qavailable_proc_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-PROC-CONSES-TAIL-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_proc_conses_tail_vector,
	    Available_proc_conses_tail_vector);
    record_system_variable(Qavailable_proc_conses_tail_vector,Qrpc_common1,
	    list_constant,Qnil,Qt,Qnil,Qnil);
    Qproc_cons_counter_vector = STATIC_SYMBOL("PROC-CONS-COUNTER-VECTOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qproc_cons_counter_vector,
	    Proc_cons_counter_vector);
    list_constant_1 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    FIX((SI_Long)0L));
    record_system_variable(Qproc_cons_counter_vector,Qrpc_common1,
	    list_constant_1,Qnil,Qt,Qnil,Qnil);
    Qproc_cons_counter = STATIC_SYMBOL("PROC-CONS-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qproc_cons_counter,Proc_cons_counter);
    record_system_variable(Qproc_cons_counter,Qrpc_common1,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_proc_conses = STATIC_SYMBOL("OUTSTANDING-PROC-CONSES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_proc_conses,
	    STATIC_FUNCTION(outstanding_proc_conses,NIL,FALSE,0,0));
    Qproc_cons_memory_usage = STATIC_SYMBOL("PROC-CONS-MEMORY-USAGE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qproc_cons_memory_usage,
	    STATIC_FUNCTION(proc_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_9 = STATIC_STRING("1q83-jny9k83-jmy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_proc_conses);
    push_optimized_constant(Qproc_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_9));
    Qproc = STATIC_SYMBOL("PROC",AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_gsi_local_function_g2_struct = 
	    STATIC_SYMBOL("GSI-LOCAL-FUNCTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qgsi_local_function = STATIC_SYMBOL("GSI-LOCAL-FUNCTION",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_gsi_local_function_g2_struct,
	    Qgsi_local_function,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qgsi_local_function,
	    Qg2_defstruct_structure_name_gsi_local_function_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_gsi_local_function == UNBOUND)
	The_type_description_of_gsi_local_function = Nil;
    string_constant_10 = 
	    STATIC_STRING("43Dy8m83iKy1n83iKy8n8k1l8n0000000kok0k0");
    temp = The_type_description_of_gsi_local_function;
    The_type_description_of_gsi_local_function = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_10));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_gsi_local_function_g2_struct,
	    The_type_description_of_gsi_local_function,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qgsi_local_function,
	    The_type_description_of_gsi_local_function,
	    Qtype_description_of_type);
    Qoutstanding_gsi_local_function_count = 
	    STATIC_SYMBOL("OUTSTANDING-GSI-LOCAL-FUNCTION-COUNT",AB_package);
    Qgsi_local_function_structure_memory_usage = 
	    STATIC_SYMBOL("GSI-LOCAL-FUNCTION-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_11 = STATIC_STRING("1q83iKy8s83-XUy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_gsi_local_function_count);
    push_optimized_constant(Qgsi_local_function_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_11));
    Qchain_of_available_gsi_local_functions = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-GSI-LOCAL-FUNCTIONS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_gsi_local_functions,
	    Chain_of_available_gsi_local_functions);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_gsi_local_functions,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qgsi_local_function_count = STATIC_SYMBOL("GSI-LOCAL-FUNCTION-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgsi_local_function_count,
	    Gsi_local_function_count);
    record_system_variable(Qgsi_local_function_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_gsi_local_functions_vector == UNBOUND)
	Chain_of_available_gsi_local_functions_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qgsi_local_function_structure_memory_usage,
	    STATIC_FUNCTION(gsi_local_function_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_gsi_local_function_count,
	    STATIC_FUNCTION(outstanding_gsi_local_function_count,NIL,FALSE,
	    0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_gsi_local_function_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_gsi_local_function,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qgsi_local_function,
	    reclaim_structure_for_gsi_local_function_1);
    Qg2_defstruct_structure_name_gsi_remote_procedure_g2_struct = 
	    STATIC_SYMBOL("GSI-REMOTE-PROCEDURE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qgsi_remote_procedure = STATIC_SYMBOL("GSI-REMOTE-PROCEDURE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_gsi_remote_procedure_g2_struct,
	    Qgsi_remote_procedure,Qab_name_of_unique_structure_type);
    mutate_global_property(Qgsi_remote_procedure,
	    Qg2_defstruct_structure_name_gsi_remote_procedure_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_gsi_remote_procedure == UNBOUND)
	The_type_description_of_gsi_remote_procedure = Nil;
    string_constant_12 = 
	    STATIC_STRING("43Dy8m83iLy1n83iLy8n8k1l8n0000001l1m83My83-ASykxk0k0");
    temp = The_type_description_of_gsi_remote_procedure;
    The_type_description_of_gsi_remote_procedure = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_12));
    mutate_global_property(Qg2_defstruct_structure_name_gsi_remote_procedure_g2_struct,
	    The_type_description_of_gsi_remote_procedure,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qgsi_remote_procedure,
	    The_type_description_of_gsi_remote_procedure,
	    Qtype_description_of_type);
    Qoutstanding_gsi_remote_procedure_count = 
	    STATIC_SYMBOL("OUTSTANDING-GSI-REMOTE-PROCEDURE-COUNT",AB_package);
    Qgsi_remote_procedure_structure_memory_usage = 
	    STATIC_SYMBOL("GSI-REMOTE-PROCEDURE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_13 = STATIC_STRING("1q83iLy8s83-XVy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_gsi_remote_procedure_count);
    push_optimized_constant(Qgsi_remote_procedure_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_13));
    Qchain_of_available_gsi_remote_procedures = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-GSI-REMOTE-PROCEDURES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_gsi_remote_procedures,
	    Chain_of_available_gsi_remote_procedures);
    record_system_variable(Qchain_of_available_gsi_remote_procedures,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qgsi_remote_procedure_count = 
	    STATIC_SYMBOL("GSI-REMOTE-PROCEDURE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgsi_remote_procedure_count,
	    Gsi_remote_procedure_count);
    record_system_variable(Qgsi_remote_procedure_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_gsi_remote_procedures_vector == UNBOUND)
	Chain_of_available_gsi_remote_procedures_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qgsi_remote_procedure_structure_memory_usage,
	    STATIC_FUNCTION(gsi_remote_procedure_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_gsi_remote_procedure_count,
	    STATIC_FUNCTION(outstanding_gsi_remote_procedure_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_gsi_remote_procedure_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_gsi_remote_procedure,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qgsi_remote_procedure,
	    reclaim_structure_for_gsi_remote_procedure_1);
    if (Current_remote_procedure_identifier == UNBOUND)
	Current_remote_procedure_identifier = Nil;
    if (Current_invocation_remotely_started_p == UNBOUND)
	Current_invocation_remotely_started_p = Nil;
    if (Rpc_argument_count_override_qm == UNBOUND)
	Rpc_argument_count_override_qm = Nil;
    Qg2_defstruct_structure_name_remote_procedure_name_g2_struct = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-NAME-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qremote_procedure_name = STATIC_SYMBOL("REMOTE-PROCEDURE-NAME",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_remote_procedure_name_g2_struct,
	    Qremote_procedure_name,Qab_name_of_unique_structure_type);
    mutate_global_property(Qremote_procedure_name,
	    Qg2_defstruct_structure_name_remote_procedure_name_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_remote_procedure_name == UNBOUND)
	The_type_description_of_remote_procedure_name = Nil;
    string_constant_14 = 
	    STATIC_STRING("43Dy8m8369y1n8369y8n8k1l8n0000001m1n8y83-5Ry1l83-Bjy1m83My83-B+ykok0k0");
    temp = The_type_description_of_remote_procedure_name;
    The_type_description_of_remote_procedure_name = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_14));
    mutate_global_property(Qg2_defstruct_structure_name_remote_procedure_name_g2_struct,
	    The_type_description_of_remote_procedure_name,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qremote_procedure_name,
	    The_type_description_of_remote_procedure_name,
	    Qtype_description_of_type);
    Qoutstanding_remote_procedure_name_count = 
	    STATIC_SYMBOL("OUTSTANDING-REMOTE-PROCEDURE-NAME-COUNT",
	    AB_package);
    Qremote_procedure_name_structure_memory_usage = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-NAME-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_15 = STATIC_STRING("1q8369y8s83-m5y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_remote_procedure_name_count);
    push_optimized_constant(Qremote_procedure_name_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_15));
    Qchain_of_available_remote_procedure_names = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-REMOTE-PROCEDURE-NAMES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_remote_procedure_names,
	    Chain_of_available_remote_procedure_names);
    record_system_variable(Qchain_of_available_remote_procedure_names,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qremote_procedure_name_count = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-NAME-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qremote_procedure_name_count,
	    Remote_procedure_name_count);
    record_system_variable(Qremote_procedure_name_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_remote_procedure_names_vector == UNBOUND)
	Chain_of_available_remote_procedure_names_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qremote_procedure_name_structure_memory_usage,
	    STATIC_FUNCTION(remote_procedure_name_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_remote_procedure_name_count,
	    STATIC_FUNCTION(outstanding_remote_procedure_name_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_remote_procedure_name_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_remote_procedure_name,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qremote_procedure_name,
	    reclaim_structure_for_remote_procedure_name_1);
    Qinput = STATIC_SYMBOL("INPUT",AB_package);
    Qstandard_icp_object_index_space = 
	    STATIC_SYMBOL("STANDARD-ICP-OBJECT-INDEX-SPACE",AB_package);
    Qestablish_new_object_index_for_remote_procedure_name = 
	    STATIC_SYMBOL("ESTABLISH-NEW-OBJECT-INDEX-FOR-REMOTE-PROCEDURE-NAME",
	    AB_package);
    string_constant = 
	    STATIC_STRING("resumable icp synch error: ~S expected, ~S found");
    SET_SYMBOL_FUNCTION(Qestablish_new_object_index_for_remote_procedure_name,
	    STATIC_FUNCTION(establish_new_object_index_for_remote_procedure_name,
	    NIL,TRUE,2,3));
    Qmake_corresponding_icp_remote_procedure_name = 
	    STATIC_SYMBOL("MAKE-CORRESPONDING-ICP-REMOTE-PROCEDURE-NAME",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmake_corresponding_icp_remote_procedure_name,
	    STATIC_FUNCTION(make_corresponding_icp_remote_procedure_name,
	    NIL,FALSE,1,1));
    Qset_access_form_for_remote_procedure_name = 
	    STATIC_SYMBOL("SET-ACCESS-FORM-FOR-REMOTE-PROCEDURE-NAME",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qset_access_form_for_remote_procedure_name,
	    STATIC_FUNCTION(set_access_form_for_remote_procedure_name,NIL,
	    FALSE,2,2));
    Qicp_object_map_for_remote_procedure_name = 
	    STATIC_SYMBOL("ICP-OBJECT-MAP-FOR-REMOTE-PROCEDURE-NAME",
	    AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)2L,
	    Qicp_object_map_for_remote_procedure_name,Qremote_procedure_name);
    initialize_icp_object_type_compile(Qremote_procedure_name,
	    Qstandard_icp_object_index_space,list_constant_2);
    Qreclaim_remote_procedure_name_structure = 
	    STATIC_SYMBOL("RECLAIM-REMOTE-PROCEDURE-NAME-STRUCTURE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_remote_procedure_name_structure,
	    STATIC_FUNCTION(reclaim_remote_procedure_name_structure,NIL,
	    FALSE,1,1));
    Qreclaim_remote_procedure_name_for_connection_loss = 
	    STATIC_SYMBOL("RECLAIM-REMOTE-PROCEDURE-NAME-FOR-CONNECTION-LOSS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_remote_procedure_name_for_connection_loss,
	    STATIC_FUNCTION(reclaim_remote_procedure_name_for_connection_loss,
	    NIL,FALSE,2,2));
    Qreclaim_icp_port_entry_for_remote_procedure_name = 
	    STATIC_SYMBOL("RECLAIM-ICP-PORT-ENTRY-FOR-REMOTE-PROCEDURE-NAME",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_icp_port_entry_for_remote_procedure_name,
	    STATIC_FUNCTION(reclaim_icp_port_entry_for_remote_procedure_name,
	    NIL,FALSE,2,2));
    initialize_icp_object_type(Qremote_procedure_name,
	    Qreclaim_remote_procedure_name_structure,
	    Qreclaim_remote_procedure_name_for_connection_loss,
	    Qreclaim_icp_port_entry_for_remote_procedure_name);
    Qsend_icp_define_remote_procedure_name = 
	    STATIC_SYMBOL("SEND-ICP-DEFINE-REMOTE-PROCEDURE-NAME",AB_package);
    Qcorresponding_icp_object_map_for_symbol = 
	    STATIC_SYMBOL("CORRESPONDING-ICP-OBJECT-MAP-FOR-SYMBOL",
	    AB_package);
    Qdefine_remote_procedure_name = 
	    STATIC_SYMBOL("DEFINE-REMOTE-PROCEDURE-NAME",AB_package);
    string_constant_1 = STATIC_STRING("[message]");
    Qmessage = STATIC_SYMBOL("MESSAGE",AB_package);
    Qcorresponding_icp_object_index = 
	    STATIC_SYMBOL("CORRESPONDING-ICP-OBJECT-INDEX",AB_package);
    string_constant_2 = STATIC_STRING("[value arg]");
    Qargument = STATIC_SYMBOL("ARGUMENT",AB_package);
    Qremote_procedure_name_symbol = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-NAME-SYMBOL",AB_package);
    string_constant_3 = STATIC_STRING("[object arg]");
    SET_SYMBOL_FUNCTION(Qsend_icp_define_remote_procedure_name,
	    STATIC_FUNCTION(send_icp_define_remote_procedure_name,NIL,
	    FALSE,2,2));
    Qhandle_icp_define_remote_procedure_name = 
	    STATIC_SYMBOL("HANDLE-ICP-DEFINE-REMOTE-PROCEDURE-NAME",
	    AB_package);
    Qresumable_icp_list_end = STATIC_SYMBOL("RESUMABLE-ICP-LIST-END",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_define_remote_procedure_name,
	    STATIC_FUNCTION(handle_icp_define_remote_procedure_name,NIL,
	    FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_define_remote_procedure_name,
	    FIX((SI_Long)221L));
    Qg2_defstruct_structure_name_remote_procedure_identifier_g2_struct = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-IDENTIFIER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qremote_procedure_identifier = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-IDENTIFIER",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_remote_procedure_identifier_g2_struct,
	    Qremote_procedure_identifier,Qab_name_of_unique_structure_type);
    mutate_global_property(Qremote_procedure_identifier,
	    Qg2_defstruct_structure_name_remote_procedure_identifier_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_remote_procedure_identifier == UNBOUND)
	The_type_description_of_remote_procedure_identifier = Nil;
    string_constant_16 = 
	    STATIC_STRING("43Dy8m83mGy1n83mGy8n8k1l8n0000001l1n8y83-5Py1m83-Bhy8368ykvk0k0");
    temp = The_type_description_of_remote_procedure_identifier;
    The_type_description_of_remote_procedure_identifier = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_16));
    mutate_global_property(Qg2_defstruct_structure_name_remote_procedure_identifier_g2_struct,
	    The_type_description_of_remote_procedure_identifier,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qremote_procedure_identifier,
	    The_type_description_of_remote_procedure_identifier,
	    Qtype_description_of_type);
    Qoutstanding_remote_procedure_identifier_count = 
	    STATIC_SYMBOL("OUTSTANDING-REMOTE-PROCEDURE-IDENTIFIER-COUNT",
	    AB_package);
    Qremote_procedure_identifier_structure_memory_usage = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-IDENTIFIER-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_17 = STATIC_STRING("1q83mGy8s83-m4y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_remote_procedure_identifier_count);
    push_optimized_constant(Qremote_procedure_identifier_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_17));
    Qchain_of_available_remote_procedure_identifiers = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-REMOTE-PROCEDURE-IDENTIFIERS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_remote_procedure_identifiers,
	    Chain_of_available_remote_procedure_identifiers);
    record_system_variable(Qchain_of_available_remote_procedure_identifiers,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qremote_procedure_identifier_count = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-IDENTIFIER-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qremote_procedure_identifier_count,
	    Remote_procedure_identifier_count);
    record_system_variable(Qremote_procedure_identifier_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_remote_procedure_identifiers_vector == UNBOUND)
	Chain_of_available_remote_procedure_identifiers_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qremote_procedure_identifier_structure_memory_usage,
	    STATIC_FUNCTION(remote_procedure_identifier_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_remote_procedure_identifier_count,
	    STATIC_FUNCTION(outstanding_remote_procedure_identifier_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_remote_procedure_identifier_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_remote_procedure_identifier,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qremote_procedure_identifier,
	    reclaim_structure_for_remote_procedure_identifier_1);
    Qoutstanding = STATIC_SYMBOL("OUTSTANDING",AB_package);
    Qg2_defstruct_structure_name_remote_procedure_item_passing_info_g2_struct 
	    = STATIC_SYMBOL("REMOTE-PROCEDURE-ITEM-PASSING-INFO-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qremote_procedure_item_passing_info = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-ITEM-PASSING-INFO",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_remote_procedure_item_passing_info_g2_struct,
	    Qremote_procedure_item_passing_info,
	    Qab_name_of_unique_structure_type);
    mutate_global_property(Qremote_procedure_item_passing_info,
	    Qg2_defstruct_structure_name_remote_procedure_item_passing_info_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_remote_procedure_item_passing_info == UNBOUND)
	The_type_description_of_remote_procedure_item_passing_info = Nil;
    string_constant_18 = 
	    STATIC_STRING("43Dy8m8368y1n8368y8n8k1l8n0000001m1n8y83-5Qy1l83Yty1m83My83-Axykmk0k0");
    temp = The_type_description_of_remote_procedure_item_passing_info;
    The_type_description_of_remote_procedure_item_passing_info = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_18));
    mutate_global_property(Qg2_defstruct_structure_name_remote_procedure_item_passing_info_g2_struct,
	    The_type_description_of_remote_procedure_item_passing_info,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qremote_procedure_item_passing_info,
	    The_type_description_of_remote_procedure_item_passing_info,
	    Qtype_description_of_type);
    Qoutstanding_remote_procedure_item_passing_info_count = 
	    STATIC_SYMBOL("OUTSTANDING-REMOTE-PROCEDURE-ITEM-PASSING-INFO-COUNT",
	    AB_package);
    Qremote_procedure_item_passing_info_structure_memory_usage = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-ITEM-PASSING-INFO-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_19 = STATIC_STRING("1q8368y8s83-Biy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_remote_procedure_item_passing_info_count);
    push_optimized_constant(Qremote_procedure_item_passing_info_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_19));
    Qchain_of_available_remote_procedure_item_passing_infos = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-REMOTE-PROCEDURE-ITEM-PASSING-INFOS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_remote_procedure_item_passing_infos,
	    Chain_of_available_remote_procedure_item_passing_infos);
    record_system_variable(Qchain_of_available_remote_procedure_item_passing_infos,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qremote_procedure_item_passing_info_count = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-ITEM-PASSING-INFO-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qremote_procedure_item_passing_info_count,
	    Remote_procedure_item_passing_info_count);
    record_system_variable(Qremote_procedure_item_passing_info_count,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_remote_procedure_item_passing_infos_vector == 
	    UNBOUND)
	Chain_of_available_remote_procedure_item_passing_infos_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qremote_procedure_item_passing_info_structure_memory_usage,
	    STATIC_FUNCTION(remote_procedure_item_passing_info_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_remote_procedure_item_passing_info_count,
	    STATIC_FUNCTION(outstanding_remote_procedure_item_passing_info_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_remote_procedure_item_passing_info_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_remote_procedure_item_passing_info,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qremote_procedure_item_passing_info,
	    reclaim_structure_for_remote_procedure_item_passing_info_1);
    Qg2_defstruct_structure_name_interned_remote_procedure_item_passing_info_g2_struct 
	    = 
	    STATIC_SYMBOL("INTERNED-REMOTE-PROCEDURE-ITEM-PASSING-INFO-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qinterned_remote_procedure_item_passing_info = 
	    STATIC_SYMBOL("INTERNED-REMOTE-PROCEDURE-ITEM-PASSING-INFO",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_interned_remote_procedure_item_passing_info_g2_struct,
	    Qinterned_remote_procedure_item_passing_info,
	    Qab_name_of_unique_structure_type);
    mutate_global_property(Qinterned_remote_procedure_item_passing_info,
	    Qg2_defstruct_structure_name_interned_remote_procedure_item_passing_info_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_interned_remote_procedure_item_passing_info 
	    == UNBOUND)
	The_type_description_of_interned_remote_procedure_item_passing_info 
		= Nil;
    string_constant_20 = 
	    STATIC_STRING("43Dy8m83j7y1o83j7y8368y8n8k1l8368y0000001m1m8x8368y1n8y83-4ey1l83Ytykmk0k0");
    temp = The_type_description_of_interned_remote_procedure_item_passing_info;
    The_type_description_of_interned_remote_procedure_item_passing_info = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_20));
    mutate_global_property(Qg2_defstruct_structure_name_interned_remote_procedure_item_passing_info_g2_struct,
	    The_type_description_of_interned_remote_procedure_item_passing_info,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qinterned_remote_procedure_item_passing_info,
	    The_type_description_of_interned_remote_procedure_item_passing_info,
	    Qtype_description_of_type);
    Qoutstanding_interned_remote_procedure_item_passing_info_count = 
	    STATIC_SYMBOL("OUTSTANDING-INTERNED-REMOTE-PROCEDURE-ITEM-PASSING-INFO-COUNT",
	    AB_package);
    Qinterned_remote_procedure_item_passing_info_structure_memory_usage = 
	    STATIC_SYMBOL("INTERNED-REMOTE-PROCEDURE-ITEM-PASSING-INFO-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_21 = STATIC_STRING("1q83j7y8s83-aQy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_interned_remote_procedure_item_passing_info_count);
    push_optimized_constant(Qinterned_remote_procedure_item_passing_info_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_21));
    Qchain_of_available_interned_remote_procedure_item_passing_infos = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-INTERNED-REMOTE-PROCEDURE-ITEM-PASSING-INFOS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_interned_remote_procedure_item_passing_infos,
	    Chain_of_available_interned_remote_procedure_item_passing_infos);
    record_system_variable(Qchain_of_available_interned_remote_procedure_item_passing_infos,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qinterned_remote_procedure_item_passing_info_count = 
	    STATIC_SYMBOL("INTERNED-REMOTE-PROCEDURE-ITEM-PASSING-INFO-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qinterned_remote_procedure_item_passing_info_count,
	    Interned_remote_procedure_item_passing_info_count);
    record_system_variable(Qinterned_remote_procedure_item_passing_info_count,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_interned_remote_procedure_item_passing_infos_vector 
	    == UNBOUND)
	Chain_of_available_interned_remote_procedure_item_passing_infos_vector 
		= make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qinterned_remote_procedure_item_passing_info_structure_memory_usage,
	    STATIC_FUNCTION(interned_remote_procedure_item_passing_info_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_interned_remote_procedure_item_passing_info_count,
	    STATIC_FUNCTION(outstanding_interned_remote_procedure_item_passing_info_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_interned_remote_procedure_item_passing_info_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_interned_remote_procedure_item_passing_info,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qinterned_remote_procedure_item_passing_info,
	    reclaim_structure_for_interned_remote_procedure_item_passing_info_1);
    Qestablish_new_object_index_for_remote_procedure_identifier = 
	    STATIC_SYMBOL("ESTABLISH-NEW-OBJECT-INDEX-FOR-REMOTE-PROCEDURE-IDENTIFIER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qestablish_new_object_index_for_remote_procedure_identifier,
	    STATIC_FUNCTION(establish_new_object_index_for_remote_procedure_identifier,
	    NIL,TRUE,2,3));
    Qmake_corresponding_icp_remote_procedure_identifier = 
	    STATIC_SYMBOL("MAKE-CORRESPONDING-ICP-REMOTE-PROCEDURE-IDENTIFIER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmake_corresponding_icp_remote_procedure_identifier,
	    STATIC_FUNCTION(make_corresponding_icp_remote_procedure_identifier,
	    NIL,FALSE,1,1));
    Qset_access_form_for_remote_procedure_identifier = 
	    STATIC_SYMBOL("SET-ACCESS-FORM-FOR-REMOTE-PROCEDURE-IDENTIFIER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qset_access_form_for_remote_procedure_identifier,
	    STATIC_FUNCTION(set_access_form_for_remote_procedure_identifier,
	    NIL,FALSE,2,2));
    Qicp_object_map_for_remote_procedure_identifier = 
	    STATIC_SYMBOL("ICP-OBJECT-MAP-FOR-REMOTE-PROCEDURE-IDENTIFIER",
	    AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)2L,
	    Qicp_object_map_for_remote_procedure_identifier,
	    Qremote_procedure_identifier);
    initialize_icp_object_type_compile(Qremote_procedure_identifier,
	    Qstandard_icp_object_index_space,list_constant_3);
    Qreclaim_incoming_remote_procedure_identifier = 
	    STATIC_SYMBOL("RECLAIM-INCOMING-REMOTE-PROCEDURE-IDENTIFIER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_incoming_remote_procedure_identifier,
	    STATIC_FUNCTION(reclaim_incoming_remote_procedure_identifier,
	    NIL,FALSE,1,1));
    Qreclaim_remote_procedure_identifier_for_connection_loss = 
	    STATIC_SYMBOL("RECLAIM-REMOTE-PROCEDURE-IDENTIFIER-FOR-CONNECTION-LOSS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_remote_procedure_identifier_for_connection_loss,
	    STATIC_FUNCTION(reclaim_remote_procedure_identifier_for_connection_loss,
	    NIL,FALSE,2,2));
    Qreclaim_icp_port_entry_for_remote_procedure_identifier = 
	    STATIC_SYMBOL("RECLAIM-ICP-PORT-ENTRY-FOR-REMOTE-PROCEDURE-IDENTIFIER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_icp_port_entry_for_remote_procedure_identifier,
	    STATIC_FUNCTION(reclaim_icp_port_entry_for_remote_procedure_identifier,
	    NIL,FALSE,2,2));
    initialize_icp_object_type(Qremote_procedure_identifier,
	    Qreclaim_incoming_remote_procedure_identifier,
	    Qreclaim_remote_procedure_identifier_for_connection_loss,
	    Qreclaim_icp_port_entry_for_remote_procedure_identifier);
    Qsend_icp_define_remote_procedure_identifier = 
	    STATIC_SYMBOL("SEND-ICP-DEFINE-REMOTE-PROCEDURE-IDENTIFIER",
	    AB_package);
    Qdefine_remote_procedure_identifier = 
	    STATIC_SYMBOL("DEFINE-REMOTE-PROCEDURE-IDENTIFIER",AB_package);
    Qremote_procedure_identifier_tag = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-IDENTIFIER-TAG",AB_package);
    Qlist_of_included_return_attributes = 
	    STATIC_SYMBOL("LIST-OF-INCLUDED-RETURN-ATTRIBUTES",AB_package);
    Qlist_of_excluded_return_attributes = 
	    STATIC_SYMBOL("LIST-OF-EXCLUDED-RETURN-ATTRIBUTES",AB_package);
    Qlist_of_included_return_system_attributes = 
	    STATIC_SYMBOL("LIST-OF-INCLUDED-RETURN-SYSTEM-ATTRIBUTES",
	    AB_package);
    Qlist_of_include_all_return_system_attributes = 
	    STATIC_SYMBOL("LIST-OF-INCLUDE-ALL-RETURN-SYSTEM-ATTRIBUTES",
	    AB_package);
    Qlist_of_include_all_return_system_attributes_except = 
	    STATIC_SYMBOL("LIST-OF-INCLUDE-ALL-RETURN-SYSTEM-ATTRIBUTES-EXCEPT",
	    AB_package);
    Qlist_of_return_kinds = STATIC_SYMBOL("LIST-OF-RETURN-KINDS",AB_package);
    Qremote_procedure_varargs_p = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-VARARGS-P",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_define_remote_procedure_identifier,
	    STATIC_FUNCTION(send_icp_define_remote_procedure_identifier,
	    NIL,FALSE,9,9));
    Qhandle_icp_define_remote_procedure_identifier = 
	    STATIC_SYMBOL("HANDLE-ICP-DEFINE-REMOTE-PROCEDURE-IDENTIFIER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_define_remote_procedure_identifier,
	    STATIC_FUNCTION(handle_icp_define_remote_procedure_identifier,
	    NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_define_remote_procedure_identifier,
	    FIX((SI_Long)222L));
    Qhandle = STATIC_SYMBOL("HANDLE",AB_package);
    Qvalue = STATIC_SYMBOL("VALUE",AB_package);
    Qreference = STATIC_SYMBOL("REFERENCE",AB_package);
    Qcopy = STATIC_SYMBOL("COPY",AB_package);
    Qby_copy_with_handle = STATIC_SYMBOL("BY-COPY-WITH-HANDLE",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    if (Write_remote_value_items_kind == UNBOUND)
	Write_remote_value_items_kind = Qcopy;
    if (Gsi_remote_value_creates_instance_p == UNBOUND)
	Gsi_remote_value_creates_instance_p = T;
    if (Gsi_remote_value_conses_logical_p == UNBOUND)
	Gsi_remote_value_conses_logical_p = Nil;
    if (Write_value_of_gsi_item_p == UNBOUND)
	Write_value_of_gsi_item_p = Nil;
    if (Remote_value_is_binary_p == UNBOUND)
	Remote_value_is_binary_p = Nil;
    Qremote_value_known_typetag = 
	    STATIC_SYMBOL("REMOTE-VALUE-KNOWN-TYPETAG",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qremote_value_known_typetag,
	    Remote_value_known_typetag);
    record_system_variable(Qremote_value_known_typetag,Qrpc_common1,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qlong = STATIC_SYMBOL("LONG",AB_package);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qunsigned_short_vector = STATIC_SYMBOL("UNSIGNED-SHORT-VECTOR",AB_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Qunsigned_vector_16 = STATIC_SYMBOL("UNSIGNED-VECTOR-16",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qwrite_icp_remote_value_1 = STATIC_SYMBOL("WRITE-ICP-REMOTE-VALUE-1",
	    AB_package);
    Qtrue = STATIC_SYMBOL("TRUE",AB_package);
    Qfalse = STATIC_SYMBOL("FALSE",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_icp_remote_value_1,
	    STATIC_FUNCTION(write_icp_remote_value_1,NIL,FALSE,1,1));
    string_constant_4 = 
	    STATIC_STRING("Unknown type tag ~a in READ-ICP-REMOTE-VALUE");
    Qread_icp_remote_value_1 = STATIC_SYMBOL("READ-ICP-REMOTE-VALUE-1",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qread_icp_remote_value_1,
	    STATIC_FUNCTION(read_icp_remote_value_1,NIL,FALSE,0,0));
    Qunbound = STATIC_SYMBOL("UNBOUND",AB_package);
    if (Item_copy_index_space == UNBOUND)
	Item_copy_index_space = Qunbound;
    Qremote_value = STATIC_SYMBOL("REMOTE-VALUE",AB_package);
    string_constant_5 = STATIC_STRING("[value]");
    Qwrite_icp_remote_value = STATIC_SYMBOL("WRITE-ICP-REMOTE-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_icp_remote_value,
	    STATIC_FUNCTION(write_icp_remote_value,NIL,FALSE,1,1));
    Qread_icp_remote_value = STATIC_SYMBOL("READ-ICP-REMOTE-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qread_icp_remote_value,
	    STATIC_FUNCTION(read_icp_remote_value,NIL,FALSE,0,0));
    Qgsi_permanent_remote_value = 
	    STATIC_SYMBOL("GSI-PERMANENT-REMOTE-VALUE",AB_package);
    Qread_icp_gsi_permanent_remote_value = 
	    STATIC_SYMBOL("READ-ICP-GSI-PERMANENT-REMOTE-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qread_icp_gsi_permanent_remote_value,
	    STATIC_FUNCTION(read_icp_gsi_permanent_remote_value,NIL,FALSE,
	    0,0));
    Qwrite_icp_gsi_permanent_remote_value = 
	    STATIC_SYMBOL("WRITE-ICP-GSI-PERMANENT-REMOTE-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_icp_gsi_permanent_remote_value,
	    STATIC_FUNCTION(write_icp_gsi_permanent_remote_value,NIL,FALSE,
	    1,1));
    Qevaluation_sequence = STATIC_SYMBOL("EVALUATION-SEQUENCE",AB_package);
    Qread_icp_evaluation_sequence = 
	    STATIC_SYMBOL("READ-ICP-EVALUATION-SEQUENCE",AB_package);
    SET_SYMBOL_FUNCTION(Qread_icp_evaluation_sequence,
	    STATIC_FUNCTION(read_icp_evaluation_sequence,NIL,FALSE,0,0));
    Qwrite_icp_evaluation_sequence = 
	    STATIC_SYMBOL("WRITE-ICP-EVALUATION-SEQUENCE",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_icp_evaluation_sequence,
	    STATIC_FUNCTION(write_icp_evaluation_sequence,NIL,FALSE,1,1));
    Qread_evaluation_structure_from_list = 
	    STATIC_SYMBOL("READ-EVALUATION-STRUCTURE-FROM-LIST",AB_package);
    SET_SYMBOL_FUNCTION(Qread_evaluation_structure_from_list,
	    STATIC_FUNCTION(read_evaluation_structure_from_list,NIL,FALSE,
	    2,2));
    Qevaluation_structure = STATIC_SYMBOL("EVALUATION-STRUCTURE",AB_package);
    Qread_icp_evaluation_structure = 
	    STATIC_SYMBOL("READ-ICP-EVALUATION-STRUCTURE",AB_package);
    SET_SYMBOL_FUNCTION(Qread_icp_evaluation_structure,
	    STATIC_FUNCTION(read_icp_evaluation_structure,NIL,FALSE,0,0));
    Qinterned_list_table = STATIC_SYMBOL("INTERNED-LIST-TABLE",AB_package);
    Qwrite_icp_evaluation_structure = 
	    STATIC_SYMBOL("WRITE-ICP-EVALUATION-STRUCTURE",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_icp_evaluation_structure,
	    STATIC_FUNCTION(write_icp_evaluation_structure,NIL,FALSE,1,1));
    Qsend_icp_rpc_asynchronous_abort = 
	    STATIC_SYMBOL("SEND-ICP-RPC-ASYNCHRONOUS-ABORT",AB_package);
    Qrpc_asynchronous_abort = STATIC_SYMBOL("RPC-ASYNCHRONOUS-ABORT",
	    AB_package);
    Qprocedure_to_abort_qm = STATIC_SYMBOL("PROCEDURE-TO-ABORT\?",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_rpc_asynchronous_abort,
	    STATIC_FUNCTION(send_icp_rpc_asynchronous_abort,NIL,FALSE,1,1));
    Qasync_abort = STATIC_SYMBOL("ASYNC-ABORT",AB_package);
    Qreturned = STATIC_SYMBOL("RETURNED",AB_package);
    Qtelewindows = STATIC_SYMBOL("TELEWINDOWS",AB_package);
    Qhandle_icp_rpc_asynchronous_abort = 
	    STATIC_SYMBOL("HANDLE-ICP-RPC-ASYNCHRONOUS-ABORT",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_rpc_asynchronous_abort,
	    STATIC_FUNCTION(handle_icp_rpc_asynchronous_abort,NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_rpc_asynchronous_abort,
	    FIX((SI_Long)235L));
    Qsend_icp_rpc_acknowledge_abort = 
	    STATIC_SYMBOL("SEND-ICP-RPC-ACKNOWLEDGE-ABORT",AB_package);
    Qrpc_acknowledge_abort = STATIC_SYMBOL("RPC-ACKNOWLEDGE-ABORT",AB_package);
    Qprocedure_index = STATIC_SYMBOL("PROCEDURE-INDEX",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_rpc_acknowledge_abort,
	    STATIC_FUNCTION(send_icp_rpc_acknowledge_abort,NIL,FALSE,1,1));
    Qhandle_icp_rpc_acknowledge_abort = 
	    STATIC_SYMBOL("HANDLE-ICP-RPC-ACKNOWLEDGE-ABORT",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_rpc_acknowledge_abort,
	    STATIC_FUNCTION(handle_icp_rpc_acknowledge_abort,NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_rpc_acknowledge_abort,
	    FIX((SI_Long)240L));
    string_constant_6 = 
	    STATIC_STRING("Received a rpc-acknowledge-abort message with no remote-procedure-identifier");
    string_constant_7 = 
	    STATIC_STRING("Received an unexpected rpc-acknowledge-abort message");
    string_constant_8 = 
	    STATIC_STRING("~%Error in rpc-acknowledge-abort, for ~NF ~A~\n       ~%~A: ~A~%");
    Maximum_concurrent_remote_procedure_calls = FIX((SI_Long)4096L);
    Qremote_procedure_identifier_map = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-IDENTIFIER-MAP",AB_package);
    Qremote_procedure_identifier_array = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-IDENTIFIER-ARRAY",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qremote_procedure_identifier_array,
	    Remote_procedure_identifier_array);
    Qmake_initial_remote_procedure_identifier_array = 
	    STATIC_SYMBOL("MAKE-INITIAL-REMOTE-PROCEDURE-IDENTIFIER-ARRAY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmake_initial_remote_procedure_identifier_array,
	    STATIC_FUNCTION(make_initial_remote_procedure_identifier_array,
	    NIL,FALSE,0,0));
    list_constant_4 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qmake_initial_remote_procedure_identifier_array);
    record_system_variable(Qremote_procedure_identifier_array,Qrpc_common1,
	    list_constant_4,Qnil,Qnil,Qnil,Qnil);
    Qindex_space = STATIC_SYMBOL("INDEX-SPACE",AB_package);
    Qg2_defstruct_structure_name_interned_list_g2_struct = 
	    STATIC_SYMBOL("INTERNED-LIST-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qtemporary_icp_object_index_space = 
	    STATIC_SYMBOL("TEMPORARY-ICP-OBJECT-INDEX-SPACE",AB_package);
    Qsend_icp_define_temporary_index_space = 
	    STATIC_SYMBOL("SEND-ICP-DEFINE-TEMPORARY-INDEX-SPACE",AB_package);
    Qdefine_temporary_index_space = 
	    STATIC_SYMBOL("DEFINE-TEMPORARY-INDEX-SPACE",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_define_temporary_index_space,
	    STATIC_FUNCTION(send_icp_define_temporary_index_space,NIL,
	    FALSE,1,1));
    Qhandle_icp_define_temporary_index_space = 
	    STATIC_SYMBOL("HANDLE-ICP-DEFINE-TEMPORARY-INDEX-SPACE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_define_temporary_index_space,
	    STATIC_FUNCTION(handle_icp_define_temporary_index_space,NIL,
	    FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_define_temporary_index_space,
	    FIX((SI_Long)301L));
    Qsend_icp_release_temporary_index_space = 
	    STATIC_SYMBOL("SEND-ICP-RELEASE-TEMPORARY-INDEX-SPACE",AB_package);
    Qrelease_temporary_index_space = 
	    STATIC_SYMBOL("RELEASE-TEMPORARY-INDEX-SPACE",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_release_temporary_index_space,
	    STATIC_FUNCTION(send_icp_release_temporary_index_space,NIL,
	    FALSE,0,0));
    Qhandle_icp_release_temporary_index_space = 
	    STATIC_SYMBOL("HANDLE-ICP-RELEASE-TEMPORARY-INDEX-SPACE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_release_temporary_index_space,
	    STATIC_FUNCTION(handle_icp_release_temporary_index_space,NIL,
	    FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_release_temporary_index_space,
	    FIX((SI_Long)302L));
}
