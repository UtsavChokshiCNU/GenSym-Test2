/* wrmbt.c
 * Input file:  warmboot.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "wrmbt.h"


DEFINE_VARIABLE_WITH_SYMBOL(Available_warmboot_conses, Qavailable_warmboot_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_warmboot_conses_tail, Qavailable_warmboot_conses_tail);

Object Available_warmboot_conses_vector = UNBOUND;

Object Available_warmboot_conses_tail_vector = UNBOUND;

Object Warmboot_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Warmboot_cons_counter, Qwarmboot_cons_counter);

/* OUTSTANDING-WARMBOOT-CONSES */
Object outstanding_warmboot_conses()
{
    Object temp;

    x_note_fn_call(137,0);
    temp = FIXNUM_MINUS(Warmboot_cons_counter,
	    length(Available_warmboot_conses));
    return VALUES_1(temp);
}

/* WARMBOOT-CONS-MEMORY-USAGE */
Object warmboot_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(137,1);
    temp = FIXNUM_TIMES(Warmboot_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-WARMBOOT-CONS-POOL */
Object replenish_warmboot_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(137,2);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qwarmboot_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_warmboot_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_warmboot_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_warmboot_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_warmboot_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_warmboot_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Warmboot_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qwarmboot;           /* warmboot */

/* WARMBOOT-CONS-1 */
Object warmboot_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(137,3);
    new_cons = ISVREF(Available_warmboot_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_warmboot_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_warmboot_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_warmboot_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_warmboot_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qwarmboot);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-WARMBOOT-LIST-POOL */
Object replenish_warmboot_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(137,4);
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
    if (ISVREF(Available_warmboot_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_warmboot_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_warmboot_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_warmboot_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_warmboot_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qwarmboot_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-WARMBOOT-LIST-1 */
Object make_warmboot_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(137,5);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_warmboot_conses_vector,
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
	replenish_warmboot_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_warmboot_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qwarmboot);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_warmboot_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_warmboot_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_warmboot_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_warmboot_conses_tail_vector;
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

/* WARMBOOT-LIST-2 */
Object warmboot_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(137,6);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_warmboot_conses_vector,IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_warmboot_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_warmboot_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qwarmboot);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_warmboot_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_warmboot_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_warmboot_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_warmboot_conses_tail_vector;
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

/* WARMBOOT-LIST-3 */
Object warmboot_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(137,7);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_warmboot_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_warmboot_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_warmboot_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qwarmboot);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_warmboot_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_warmboot_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_warmboot_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_warmboot_conses_tail_vector;
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

/* WARMBOOT-LIST-4 */
Object warmboot_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(137,8);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_warmboot_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_warmboot_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_warmboot_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qwarmboot);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_warmboot_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_warmboot_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_warmboot_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_warmboot_conses_tail_vector;
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

/* WARMBOOT-LIST-TRACE-HOOK */
Object warmboot_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(137,9);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-WARMBOOT-CONSES-1 */
Object copy_tree_using_warmboot_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(137,10);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_warmboot_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_warmboot_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_warmboot_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_warmboot_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_warmboot_cons_pool();
	temp_1 = copy_tree_using_warmboot_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qwarmboot);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_warmboot_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_warmboot_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_warmboot_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_warmboot_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_warmboot_cons_pool();
	temp_1 = copy_tree_using_warmboot_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qwarmboot);
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

/* COPY-LIST-USING-WARMBOOT-CONSES-1 */
Object copy_list_using_warmboot_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(137,11);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_warmboot_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_warmboot_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_warmboot_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_warmboot_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_warmboot_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qwarmboot);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_warmboot_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_warmboot_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_warmboot_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_warmboot_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_warmboot_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qwarmboot);
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

/* RECLAIM-WARMBOOT-CONS-1 */
Object reclaim_warmboot_cons_1(warmboot_cons)
    Object warmboot_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(137,12);
    inline_note_reclaim_cons(warmboot_cons,Qwarmboot);
    if (ISVREF(Available_warmboot_conses_tail_vector,
	    IFIX(Current_thread_index))) {
	temp = ISVREF(Available_warmboot_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = warmboot_cons;
	temp = Available_warmboot_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = warmboot_cons;
    }
    else {
	temp = Available_warmboot_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = warmboot_cons;
	temp = Available_warmboot_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = warmboot_cons;
    }
    M_CDR(warmboot_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-WARMBOOT-LIST-1 */
Object reclaim_warmboot_list_1(warmboot_list)
    Object warmboot_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(137,13);
    if (warmboot_list) {
	last_1 = warmboot_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qwarmboot);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qwarmboot);
	if (ISVREF(Available_warmboot_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_warmboot_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = warmboot_list;
	    temp = Available_warmboot_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_warmboot_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = warmboot_list;
	    temp = Available_warmboot_conses_tail_vector;
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

/* RECLAIM-WARMBOOT-LIST*-1 */
Object reclaim_warmboot_list_star_1(warmboot_list)
    Object warmboot_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(137,14);
    if (CONSP(warmboot_list)) {
	temp = last(warmboot_list,_);
	M_CDR(temp) = Nil;
	if (warmboot_list) {
	    last_1 = warmboot_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qwarmboot);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qwarmboot);
	    if (ISVREF(Available_warmboot_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_warmboot_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = warmboot_list;
		temp = Available_warmboot_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_warmboot_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = warmboot_list;
		temp = Available_warmboot_conses_tail_vector;
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

/* RECLAIM-WARMBOOT-TREE-1 */
Object reclaim_warmboot_tree_1(tree)
    Object tree;
{
    Object e, e2, warmboot_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(137,15);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_warmboot_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		warmboot_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(warmboot_cons,Qwarmboot);
		if (EQ(warmboot_cons,e))
		    goto end_1;
		else if ( !TRUEP(warmboot_cons))
		    goto end_1;
		else
		    warmboot_cons = CDR(warmboot_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_warmboot_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_warmboot_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_warmboot_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_warmboot_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_warmboot_conses_tail_vector;
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

/* DELETE-WARMBOOT-ELEMENT-1 */
Object delete_warmboot_element_1(element,warmboot_list)
    Object element, warmboot_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(137,16);
    if (warmboot_list) {
	if (EQ(element,M_CAR(warmboot_list))) {
	    temp = CDR(warmboot_list);
	    inline_note_reclaim_cons(warmboot_list,Qwarmboot);
	    if (ISVREF(Available_warmboot_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_warmboot_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = warmboot_list;
		temp_1 = Available_warmboot_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = warmboot_list;
	    }
	    else {
		temp_1 = Available_warmboot_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = warmboot_list;
		temp_1 = Available_warmboot_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = warmboot_list;
	    }
	    M_CDR(warmboot_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = warmboot_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qwarmboot);
		if (ISVREF(Available_warmboot_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_warmboot_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_warmboot_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_warmboot_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_warmboot_conses_tail_vector;
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
	    temp = warmboot_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-WARMBOOT-CONS-1 */
Object delete_warmboot_cons_1(warmboot_cons,warmboot_list)
    Object warmboot_cons, warmboot_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(137,17);
    if (EQ(warmboot_cons,warmboot_list))
	temp = CDR(warmboot_list);
    else {
	l_trailer_qm = Nil;
	l = warmboot_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,warmboot_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = warmboot_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_warmboot_cons_1(warmboot_cons);
    return VALUES_1(temp);
}

static Object Qwarmboot_kb;        /* warmboot-kb */

static Object array_constant;      /* # */

static Object Qscheduler_mode;     /* scheduler-mode */

static Object Qprocedure;          /* procedure */

static Object list_constant;       /* # */

/* WARMBOOT-KB */
Object warmboot_kb varargs_1(int, n)
{
    Object pathname_1;
    Object catch_up_qm, index_of_top_of_backtrace_stack, temp, svref_arg_2;
    Object warmbooting_qm, warmbooting_with_catch_up_qm;
    Object blocks_to_delete_after_unsquirreling;
    Object copy_of_current_kb_pathname_qm, warmboot_read_kb_succeeded_qm;
    Object temp_1, temp_2, scope_conses, ab_loopvar_, ab_loopvar__1, block;
    Object warmboot_procedure_qm, old_computation_frame;
    Object old_computation_component_particulars;
    char temp_3;
    Declare_varargs_nonrelocating;
    Declare_special(5);
    Object result;

    x_note_fn_call(137,18);
    INIT_ARGS_nonrelocating();
    pathname_1 = REQUIRED_ARG_nonrelocating();
    catch_up_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
    PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
	    4);
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
	  SVREF(temp,svref_arg_2) = Qwarmboot_kb;
      }
      warmbooting_qm = T;
      PUSH_SPECIAL_WITH_SYMBOL(Warmbooting_qm,Qwarmbooting_qm,warmbooting_qm,
	      3);
	warmbooting_with_catch_up_qm = catch_up_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Warmbooting_with_catch_up_qm,Qwarmbooting_with_catch_up_qm,warmbooting_with_catch_up_qm,
		2);
	  blocks_to_delete_after_unsquirreling = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Blocks_to_delete_after_unsquirreling,Qblocks_to_delete_after_unsquirreling,blocks_to_delete_after_unsquirreling,
		  1);
	    copy_of_current_kb_pathname_qm = Current_kb_pathname_qm ? 
		    copy_gensym_pathname(Current_kb_pathname_qm) : Qnil;
	    warmboot_read_kb_succeeded_qm = Nil;
	    warmboot_read_kb_succeeded_qm = read_kb(Nil,pathname_1,T,T,Nil,
		    Nil,copy_of_current_kb_pathname_qm);
	    if (copy_of_current_kb_pathname_qm) {
		reclaim_gensym_pathname(copy_of_current_kb_pathname_qm);
		copy_of_current_kb_pathname_qm = Nil;
	    }
	    if ( !TRUEP(warmboot_read_kb_succeeded_qm)) {
		result = VALUES_1(Nil);
		POP_SPECIAL();
		POP_SPECIAL();
		POP_SPECIAL();
		POP_SPECIAL();
		goto end_warmboot_kb;
	    }
	    if (Warmbooting_with_catch_up_qm) {
		temp_1 = 
			convert_text_string_to_text(copy_constant_wide_string_given_length(array_constant,
			FIX((SI_Long)19L)));
		temp_2 = Timing_parameters;
		parse_text_for_slot(4,temp_1,temp_2,
			get_slot_description_of_class_description_function(Qscheduler_mode,
			ISVREF(Timing_parameters,(SI_Long)1L),Nil),T);
	    }
	    system_start();
	    if (System_is_running) {
		scope_conses = Scope_conses;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		block = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			0);
		  ab_loopvar_ = collect_subclasses(Qblock);
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
		      temp_3 =  !TRUEP(ab_loopvar__1);
		  }
		  else
		      temp_3 = TRUEP(Nil);
		  if (temp_3)
		      goto end_loop_1;
		  block = ab_loopvar__1;
		  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
		  unsquirrel_data_for_block(block);
		  goto next_loop;
		end_loop_1:;
		POP_SPECIAL();
		update_all_indexed_attribute_hash_tables();
		delete_blocks_after_unsquirreling();
		warmboot_procedure_qm = 
			get_instance_with_name_if_any(Qprocedure,Qwarmboot);
		if (warmboot_procedure_qm && 
			runnable_p_function(warmboot_procedure_qm)) {
		    old_computation_frame = Current_computation_frame;
		    old_computation_component_particulars = 
			    Current_computation_component_particulars;
		    Current_computation_frame = warmboot_procedure_qm;
		    Current_computation_component_particulars = Nil;
		    if (error_text_p(start_procedure_invocation_in_place(warmboot_procedure_qm,
			    Nil,Nil,FIX((SI_Long)0L),FIX((SI_Long)0L),
			    FIX((SI_Long)0L),Nil,list_constant,Nil,Nil,Nil)))
			schedule_all_cyclic_rules();
		    Current_computation_frame = old_computation_frame;
		    Current_computation_component_particulars = 
			    old_computation_component_particulars;
		}
		else
		    schedule_all_cyclic_rules();
		simulate_until_consistent_with_gensym_time();
		result = VALUES_1(T);
	    }
	    else
		result = VALUES_1(Nil);
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
  end_warmboot_kb:
    return result;
}

/* COMPLETE-WARMBOOTING-AFTER-SYSTEM-START */
Object complete_warmbooting_after_system_start(completion_form)
    Object completion_form;
{
    Object gensymed_symbol, blocks_to_delete_after_unsquirreling, scope_conses;
    Object ab_loopvar_, ab_loopvar__1, block, warmboot_procedure_qm;
    Object old_computation_frame, old_computation_component_particulars;
    char temp;
    Declare_special(2);
    Object result;

    x_note_fn_call(137,19);
    gensymed_symbol = completion_form;
    gensymed_symbol = CDR(gensymed_symbol);
    blocks_to_delete_after_unsquirreling = CAR(gensymed_symbol);
    PUSH_SPECIAL_WITH_SYMBOL(Blocks_to_delete_after_unsquirreling,Qblocks_to_delete_after_unsquirreling,blocks_to_delete_after_unsquirreling,
	    1);
      if (System_is_running) {
	  scope_conses = Scope_conses;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  block = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    ab_loopvar_ = collect_subclasses(Qblock);
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
	    block = ab_loopvar__1;
	    ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	    unsquirrel_data_for_block(block);
	    goto next_loop;
	  end_loop_1:;
	  POP_SPECIAL();
	  update_all_indexed_attribute_hash_tables();
	  delete_blocks_after_unsquirreling();
	  warmboot_procedure_qm = get_instance_with_name_if_any(Qprocedure,
		  Qwarmboot);
	  if (warmboot_procedure_qm && 
		  runnable_p_function(warmboot_procedure_qm)) {
	      old_computation_frame = Current_computation_frame;
	      old_computation_component_particulars = 
		      Current_computation_component_particulars;
	      Current_computation_frame = warmboot_procedure_qm;
	      Current_computation_component_particulars = Nil;
	      if (error_text_p(start_procedure_invocation_in_place(warmboot_procedure_qm,
		      Nil,Nil,FIX((SI_Long)0L),FIX((SI_Long)0L),
		      FIX((SI_Long)0L),Nil,list_constant,Nil,Nil,Nil)))
		  schedule_all_cyclic_rules();
	      Current_computation_frame = old_computation_frame;
	      Current_computation_component_particulars = 
		      old_computation_component_particulars;
	  }
	  else
	      schedule_all_cyclic_rules();
	  simulate_until_consistent_with_gensym_time();
      }
      result = reclaim_warmboot_list_1(completion_form);
    POP_SPECIAL();
    return result;
}

/* FINISH-WARMBOOTING */
Object finish_warmbooting(x)
    Object x;
{
    x_note_fn_call(137,20);
    return schedule_all_cyclic_rules();
}

static Object Qnever;              /* never */

/* READ-RUNTIME-DATA-FOR-BLOCK */
Object read_runtime_data_for_block(block)
    Object block;
{
    Object character_1, temp, read_kb_buffer_index_new_value, temp_1, temp_2;
    Object temp_3, next_element, history_buffer, location_information;
    SI_Long svref_new_value;
    Object result;

    x_note_fn_call(137,21);
    character_1 = Nil;
  next_loop:
    if ( !TRUEP(Read_kb_buffer_index))
	character_1 = Nil;
    else if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
	read_kb_buffer_index_new_value = FIXNUM_ADD1(Read_kb_buffer_index);
	Read_kb_buffer_index = read_kb_buffer_index_new_value;
	character_1 = temp;
    }
    else
	character_1 = read_next_char_for_kb_from_refilled_buffer();
    temp = CHAR_CODE(character_1);
    if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)127L))))
	switch (INTEGER_TO_CHAR(temp)) {
	  case 33:
	    return VALUES_0();
	    break;
	  case 84:
	    svref_new_value = IFIX(ISVREF(block,(SI_Long)5L)) | 
		    (SI_Long)262144L;
	    ISVREF(block,(SI_Long)5L) = FIX(svref_new_value);
	    break;
	  case 75:
	    svref_new_value = IFIX(ISVREF(block,(SI_Long)5L)) | (SI_Long)32L;
	    ISVREF(block,(SI_Long)5L) = FIX(svref_new_value);
	    break;
	  case 86:
	    temp = character_1;
	    temp_1 = read_element_for_kb_with_temporary_floats(Nil);
	    if ( !TRUEP(Read_kb_buffer_index))
		character_1 = Nil;
	    else if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
		temp_2 = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
		read_kb_buffer_index_new_value = 
			FIXNUM_ADD1(Read_kb_buffer_index);
		Read_kb_buffer_index = read_kb_buffer_index_new_value;
		character_1 = temp_2;
	    }
	    else
		character_1 = read_next_char_for_kb_from_refilled_buffer();
	    if (EQ(character_1,CHR('G')))
		temp_2 = Some_time_ago;
	    else {
		read_kb_buffer_index_new_value = 
			FIXNUM_SUB1(Read_kb_buffer_index);
		Read_kb_buffer_index = read_kb_buffer_index_new_value;
		temp_2 = read_element_for_kb(Nil);
	    }
	    if ( !TRUEP(Read_kb_buffer_index))
		character_1 = Nil;
	    else if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
		temp_3 = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
		read_kb_buffer_index_new_value = 
			FIXNUM_ADD1(Read_kb_buffer_index);
		Read_kb_buffer_index = read_kb_buffer_index_new_value;
		character_1 = temp_3;
	    }
	    else
		character_1 = read_next_char_for_kb_from_refilled_buffer();
	    if (EQ(character_1,CHR('X')))
		temp_3 = Qnever;
	    else if (EQ(character_1,CHR('G')))
		temp_3 = Some_time_ago;
	    else {
		read_kb_buffer_index_new_value = 
			FIXNUM_SUB1(Read_kb_buffer_index);
		Read_kb_buffer_index = read_kb_buffer_index_new_value;
		temp_3 = read_element_for_kb(Nil);
	    }
	    squirrel_away_data_in_block(5,block,temp,temp_1,temp_2,temp_3);
	    break;
	  case 80:
	    temp = character_1;
	    temp_1 = read_element_for_kb_with_temporary_floats(Nil);
	    if ( !TRUEP(Read_kb_buffer_index))
		character_1 = Nil;
	    else if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
		temp_2 = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
		read_kb_buffer_index_new_value = 
			FIXNUM_ADD1(Read_kb_buffer_index);
		Read_kb_buffer_index = read_kb_buffer_index_new_value;
		character_1 = temp_2;
	    }
	    else
		character_1 = read_next_char_for_kb_from_refilled_buffer();
	    if (CHAR_EQ(character_1,CHR('G')))
		temp_2 = Some_time_ago;
	    else {
		read_kb_buffer_index_new_value = 
			FIXNUM_SUB1(Read_kb_buffer_index);
		Read_kb_buffer_index = read_kb_buffer_index_new_value;
		temp_2 = read_element_for_kb(Nil);
	    }
	    squirrel_away_data_in_block(4,block,temp,temp_1,temp_2);
	    break;
	  case 83:
	    next_element = read_element_for_kb_with_temporary_floats(Nil);
	    if ( !(IFIX(Kb_flags) >= (SI_Long)242L) && EQ(next_element,
		    No_value))
		next_element = Simulation_no_value;
	    squirrel_away_data_in_block(3,block,character_1,next_element);
	    break;
	  case 72:
	  case 74:
	    temp = character_1;
	    squirrel_away_data_in_block(3,block,temp,
		    read_history_buffer_for_block(2,block,character_1));
	    break;
	  case 66:
	    result = read_history_buffer_and_location_for_block();
	    MVS_2(result,history_buffer,location_information);
	    squirrel_away_data_in_block(4,block,character_1,history_buffer,
		    location_information);
	    break;
	  case 82:
	    temp = character_1;
	    squirrel_away_data_in_block(3,block,temp,read_element_for_kb(Nil));
	    break;
	  case 65:
	    temp = character_1;
	    squirrel_away_data_in_block(3,block,temp,read_array_data(block));
	    break;
	  case 76:
	    temp = character_1;
	    squirrel_away_data_in_block(3,block,temp,read_list_data(block));
	    break;
	  case 79:
	    temp = character_1;
	    squirrel_away_data_in_block(3,block,temp,
		    read_hash_table_data(block));
	    break;
	  default:
	    break;
	}
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* READ-ELEMENT-FOR-KB-WITH-TEMPORARY-FLOATS */
Object read_element_for_kb_with_temporary_floats(top_level_qm)
    Object top_level_qm;
{
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(137,22);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
	result = read_element_for_kb(top_level_qm);
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

static Object Qsquirreled_data;    /* squirreled-data */

/* SQUIRREL-AWAY-DATA-IN-BLOCK */
Object squirrel_away_data_in_block varargs_1(int, n)
{
    Object block, key, data_element_1;
    Object data_element_2_qm, data_element_3_qm, temp;
    Object slot_value_push_modify_macro_arg, car_1, cdr_1;
    Object squirreled_data_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(137,23);
    INIT_ARGS_nonrelocating();
    block = REQUIRED_ARG_nonrelocating();
    key = REQUIRED_ARG_nonrelocating();
    data_element_1 = REQUIRED_ARG_nonrelocating();
    data_element_2_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    data_element_3_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = slot_value_list_2(key,data_element_1);
    slot_value_push_modify_macro_arg = nconc2(temp,
	    nconc2(data_element_2_qm ? slot_value_cons_1(data_element_2_qm,
	    Nil) : Nil,data_element_3_qm ? 
	    slot_value_cons_1(data_element_3_qm,Nil) : Nil));
    car_1 = slot_value_push_modify_macro_arg;
    cdr_1 = get_lookup_slot_value_given_default(block,Qsquirreled_data,Nil);
    squirreled_data_new_value = slot_value_cons_1(car_1,cdr_1);
    return set_non_savable_lookup_slot_value(block,Qsquirreled_data,
	    squirreled_data_new_value);
}

/* READ-PAST-RUNTIME-DATA-FOR-BLOCK */
Object read_past_runtime_data_for_block(print_qm)
    Object print_qm;
{
    Object create_frames_and_connections_reading_past_qm, character_1, temp;
    Object read_kb_buffer_index_new_value, number_of_elements;
    SI_Long ab_loop_repeat_;
    char variable_current_status_case_qm;
    Declare_special(1);

    x_note_fn_call(137,24);
    create_frames_and_connections_reading_past_qm = T;
    PUSH_SPECIAL_WITH_SYMBOL(Create_frames_and_connections_reading_past_qm,Qcreate_frames_and_connections_reading_past_qm,create_frames_and_connections_reading_past_qm,
	    0);
      character_1 = Nil;
    next_loop:
      if ( !TRUEP(Read_kb_buffer_index))
	  character_1 = Nil;
      else if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
	  temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
	  read_kb_buffer_index_new_value = FIXNUM_ADD1(Read_kb_buffer_index);
	  Read_kb_buffer_index = read_kb_buffer_index_new_value;
	  character_1 = temp;
      }
      else
	  character_1 = read_next_char_for_kb_from_refilled_buffer();
      if (print_qm)
	  format((SI_Long)3L,T,"~c",character_1);
      temp = CHAR_CODE(character_1);
      if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	      FIX((SI_Long)127L))))
	  switch (INTEGER_TO_CHAR(temp)) {
	    case 33:
	      if (print_qm)
		  format((SI_Long)2L,T,"; end of runtime data~%");
	      goto end_1;
	      break;
	    case 84:
	    case 75:
	      break;
	    case 86:
	    case 80:
	      variable_current_status_case_qm = CHAR_EQ(character_1,CHR('V'));
	      read_past_element_for_kb(print_qm);
	      if ( !TRUEP(Read_kb_buffer_index))
		  character_1 = Nil;
	      else if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
		  temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
		  read_kb_buffer_index_new_value = 
			  FIXNUM_ADD1(Read_kb_buffer_index);
		  Read_kb_buffer_index = read_kb_buffer_index_new_value;
		  character_1 = temp;
	      }
	      else
		  character_1 = read_next_char_for_kb_from_refilled_buffer();
	      if ( !EQ(character_1,CHR('G'))) {
		  read_kb_buffer_index_new_value = 
			  FIXNUM_SUB1(Read_kb_buffer_index);
		  Read_kb_buffer_index = read_kb_buffer_index_new_value;
		  read_past_element_for_kb(print_qm);
	      }
	      if (variable_current_status_case_qm) {
		  if ( !TRUEP(Read_kb_buffer_index))
		      character_1 = Nil;
		  else if (FIXNUM_LT(Read_kb_buffer_index,
			  Read_kb_buffer_length)) {
		      temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
		      read_kb_buffer_index_new_value = 
			      FIXNUM_ADD1(Read_kb_buffer_index);
		      Read_kb_buffer_index = read_kb_buffer_index_new_value;
		      character_1 = temp;
		  }
		  else
		      character_1 = 
			      read_next_char_for_kb_from_refilled_buffer();
		  if (EQ(character_1,CHR('X')));
		  else if (EQ(character_1,CHR('G')));
		  else {
		      read_kb_buffer_index_new_value = 
			      FIXNUM_SUB1(Read_kb_buffer_index);
		      Read_kb_buffer_index = read_kb_buffer_index_new_value;
		      read_past_element_for_kb(print_qm);
		  }
	      }
	      break;
	    case 83:
	      if ( !TRUEP(Read_kb_buffer_index))
		  character_1 = Nil;
	      else if (FIXNUM_LT(Read_kb_buffer_index,Read_kb_buffer_length)) {
		  temp = SCHAR(Read_kb_buffer,Read_kb_buffer_index);
		  read_kb_buffer_index_new_value = 
			  FIXNUM_ADD1(Read_kb_buffer_index);
		  Read_kb_buffer_index = read_kb_buffer_index_new_value;
		  character_1 = temp;
	      }
	      else
		  character_1 = read_next_char_for_kb_from_refilled_buffer();
	      if (EQ(character_1,CHR('X')));
	      else {
		  read_kb_buffer_index_new_value = 
			  FIXNUM_SUB1(Read_kb_buffer_index);
		  Read_kb_buffer_index = read_kb_buffer_index_new_value;
		  read_past_element_for_kb(print_qm);
	      }
	      break;
	    case 72:
	    case 74:
	      read_past_history_buffer_for_block(print_qm);
	      break;
	    case 66:
	      read_past_history_buffer_and_location_for_block(print_qm);
	      break;
	    case 82:
	      read_past_element_for_kb(print_qm);
	      break;
	    case 65:
	    case 76:
	      number_of_elements = read_element_for_kb(Nil);
	      if (print_qm)
		  format((SI_Long)4L,T,"~%; ~a contents -- ~d elements:~%",
			  CHAR_EQ(character_1,CHR('V')) ? Qvector : Qlist,
			  number_of_elements);
	      ab_loop_repeat_ = IFIX(number_of_elements);
	    next_loop_1:
	      if ( !((SI_Long)0L < ab_loop_repeat_))
		  goto end_loop;
	      ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	      read_past_element_for_kb(print_qm);
	      goto next_loop_1;
	    end_loop:;
	      if (print_qm)
		  format((SI_Long)4L,T,
			  "~%; end ~a contents -- ~d elements~%",
			  CHAR_EQ(character_1,CHR('V')) ? Qvector : Qlist,
			  number_of_elements);
	      break;
	    default:
	      break;
	  }
      goto next_loop;
    end_loop_1:
    end_1:;
    POP_SPECIAL();
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Initialization_inhibit, Qinitialization_inhibit);

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qui_client_item;     /* ui-client-item */

/* DELETE-BLOCKS-AFTER-UNSQUIRRELING */
Object delete_blocks_after_unsquirreling()
{
    Object frame_serial_number, frame, ab_loop_list_, gensymed_symbol, xa, ya;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(137,25);
    frame_serial_number = 
	    copy_frame_serial_number(Current_frame_serial_number);
    frame = Nil;
    ab_loop_list_ = Blocks_to_delete_after_unsquirreling;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    frame = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = ISVREF(frame,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(frame) ? EQ(ISVREF(frame,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(frame_serial_number))
	temp = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(frame_serial_number,
		gensymed_symbol) : TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(frame_serial_number);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(frame_serial_number),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    if ( !temp) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(frame,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	if (gensymed_symbol) {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(Qui_client_item,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,
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
		    temp = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp = TRUEP(Nil);
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
	delete_frame(frame);
    goto next_loop;
  end_loop:
    reclaim_frame_serial_number(frame_serial_number);
    reclaim_gensym_list_1(Blocks_to_delete_after_unsquirreling);
    return VALUES_1(Qnil);
}

void warmboot_INIT()
{
    Object AB_package, list_constant_4, string_constant_1, Kfuncall;
    Object Qfinish_warmbooting, list_constant_3, string_constant;
    Object Qwarmboot_cons_memory_usage, Qoutstanding_warmboot_conses;
    Object Qutilities1, list_constant_2, Qwarmboot_cons_counter_vector;
    Object Qmake_thread_array, list_constant_1;
    Object Qavailable_warmboot_conses_tail_vector;
    Object Qavailable_warmboot_conses_vector;

    x_note_fn_call(137,26);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qavailable_warmboot_conses = STATIC_SYMBOL("AVAILABLE-WARMBOOT-CONSES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_warmboot_conses,
	    Available_warmboot_conses);
    Qutilities1 = STATIC_SYMBOL("UTILITIES1",AB_package);
    record_system_variable(Qavailable_warmboot_conses,Qutilities1,Nil,Qnil,
	    Qt,Qnil,Qnil);
    Qavailable_warmboot_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-WARMBOOT-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_warmboot_conses_tail,
	    Available_warmboot_conses_tail);
    record_system_variable(Qavailable_warmboot_conses_tail,Qutilities1,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_warmboot_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-WARMBOOT-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_warmboot_conses_vector,
	    Available_warmboot_conses_vector);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_thread_array = STATIC_SYMBOL("MAKE-THREAD-ARRAY",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    Qnil);
    record_system_variable(Qavailable_warmboot_conses_vector,Qutilities1,
	    list_constant_1,Qnil,Qt,Qnil,Qnil);
    Qavailable_warmboot_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-WARMBOOT-CONSES-TAIL-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_warmboot_conses_tail_vector,
	    Available_warmboot_conses_tail_vector);
    record_system_variable(Qavailable_warmboot_conses_tail_vector,
	    Qutilities1,list_constant_1,Qnil,Qt,Qnil,Qnil);
    Qwarmboot_cons_counter_vector = 
	    STATIC_SYMBOL("WARMBOOT-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qwarmboot_cons_counter_vector,
	    Warmboot_cons_counter_vector);
    list_constant_2 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    FIX((SI_Long)0L));
    record_system_variable(Qwarmboot_cons_counter_vector,Qutilities1,
	    list_constant_2,Qnil,Qt,Qnil,Qnil);
    Qwarmboot_cons_counter = STATIC_SYMBOL("WARMBOOT-CONS-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qwarmboot_cons_counter,Warmboot_cons_counter);
    record_system_variable(Qwarmboot_cons_counter,Qutilities1,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_warmboot_conses = 
	    STATIC_SYMBOL("OUTSTANDING-WARMBOOT-CONSES",AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_warmboot_conses,
	    STATIC_FUNCTION(outstanding_warmboot_conses,NIL,FALSE,0,0));
    Qwarmboot_cons_memory_usage = 
	    STATIC_SYMBOL("WARMBOOT-CONS-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qwarmboot_cons_memory_usage,
	    STATIC_FUNCTION(warmboot_cons_memory_usage,NIL,FALSE,0,0));
    string_constant = STATIC_STRING("1q83-wqy9k83-wpy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_warmboot_conses);
    push_optimized_constant(Qwarmboot_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant));
    Qwarmboot = STATIC_SYMBOL("WARMBOOT",AB_package);
    Qwarmboot_kb = STATIC_SYMBOL("WARMBOOT-KB",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_3,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)16L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)17L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)19L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)57344L);
    Qscheduler_mode = STATIC_SYMBOL("SCHEDULER-MODE",AB_package);
    Qprocedure = STATIC_SYMBOL("PROCEDURE",AB_package);
    Qfinish_warmbooting = STATIC_SYMBOL("FINISH-WARMBOOTING",AB_package);
    list_constant = STATIC_CONS(Qfinish_warmbooting,Qnil);
    SET_SYMBOL_FUNCTION(Qwarmboot_kb,STATIC_FUNCTION(warmboot_kb,NIL,TRUE,
	    1,2));
    SET_SYMBOL_FUNCTION(Qfinish_warmbooting,
	    STATIC_FUNCTION(finish_warmbooting,NIL,FALSE,1,1));
    Qnever = STATIC_SYMBOL("NEVER",AB_package);
    Qsquirreled_data = STATIC_SYMBOL("SQUIRRELED-DATA",AB_package);
    Qinitialization_inhibit = STATIC_SYMBOL("INITIALIZATION-INHIBIT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qinitialization_inhibit,Initialization_inhibit);
    string_constant_1 = STATIC_STRING("initialization-inhibit");
    list_constant_4 = STATIC_LIST((SI_Long)3L,Kfuncall,Qgentemp,
	    string_constant_1);
    record_system_variable(Qinitialization_inhibit,Qwarmboot,
	    list_constant_4,Qnil,Qnil,Qnil,Qnil);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qui_client_item = STATIC_SYMBOL("UI-CLIENT-ITEM",AB_package);
}
