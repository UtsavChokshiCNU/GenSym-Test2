/* java1.c
 * Input file:  java1.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "java1.h"


DEFINE_VARIABLE_WITH_SYMBOL(Available_java_conses, Qavailable_java_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_java_conses_tail, Qavailable_java_conses_tail);

Object Available_java_conses_vector = UNBOUND;

Object Available_java_conses_tail_vector = UNBOUND;

Object Java_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Java_cons_counter, Qjava_cons_counter);

/* OUTSTANDING-JAVA-CONSES */
Object outstanding_java_conses()
{
    Object temp;

    x_note_fn_call(249,0);
    temp = FIXNUM_MINUS(Java_cons_counter,length(Available_java_conses));
    return VALUES_1(temp);
}

/* JAVA-CONS-MEMORY-USAGE */
Object java_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(249,1);
    temp = FIXNUM_TIMES(Java_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-JAVA-CONS-POOL */
Object replenish_java_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(249,2);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qjava_cons_counter,Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_java_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_java_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_java_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_java_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_java_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Java_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qjava;               /* java */

/* JAVA-CONS-1 */
Object java_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(249,3);
    new_cons = ISVREF(Available_java_conses_vector,IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_java_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_java_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_java_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_java_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qjava);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-JAVA-LIST-POOL */
Object replenish_java_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(249,4);
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
    if (ISVREF(Available_java_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_java_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_java_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_java_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_java_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qjava_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-JAVA-LIST-1 */
Object make_java_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(249,5);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_java_conses_vector,
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
	replenish_java_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_java_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qjava);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_java_conses_vector,IFIX(Current_thread_index));
	svref_arg_1 = Available_java_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_java_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_java_conses_tail_vector;
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

/* JAVA-LIST-2 */
Object java_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(249,6);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_java_conses_vector,IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_java_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_java_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qjava);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_java_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_java_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_java_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_java_conses_tail_vector;
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

/* JAVA-LIST-3 */
Object java_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(249,7);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_java_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_java_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_java_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qjava);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_java_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_java_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_java_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_java_conses_tail_vector;
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

/* JAVA-LIST-4 */
Object java_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(249,8);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_java_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_java_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_java_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qjava);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_java_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_java_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_java_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_java_conses_tail_vector;
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

/* JAVA-LIST-TRACE-HOOK */
Object java_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(249,9);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-JAVA-CONSES-1 */
Object copy_tree_using_java_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(249,10);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_java_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_java_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_java_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_java_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_java_cons_pool();
	temp_1 = copy_tree_using_java_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qjava);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_java_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_java_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_java_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_java_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_java_cons_pool();
	temp_1 = copy_tree_using_java_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qjava);
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

/* COPY-LIST-USING-JAVA-CONSES-1 */
Object copy_list_using_java_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(249,11);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_java_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_java_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_java_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_java_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_java_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qjava);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_java_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_java_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_java_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_java_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_java_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qjava);
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

/* RECLAIM-JAVA-CONS-1 */
Object reclaim_java_cons_1(java_cons)
    Object java_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(249,12);
    inline_note_reclaim_cons(java_cons,Qjava);
    if (ISVREF(Available_java_conses_tail_vector,IFIX(Current_thread_index))) {
	temp = ISVREF(Available_java_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = java_cons;
	temp = Available_java_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = java_cons;
    }
    else {
	temp = Available_java_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = java_cons;
	temp = Available_java_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = java_cons;
    }
    M_CDR(java_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-JAVA-LIST-1 */
Object reclaim_java_list_1(java_list)
    Object java_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(249,13);
    if (java_list) {
	last_1 = java_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qjava);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qjava);
	if (ISVREF(Available_java_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_java_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = java_list;
	    temp = Available_java_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_java_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = java_list;
	    temp = Available_java_conses_tail_vector;
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

/* RECLAIM-JAVA-LIST*-1 */
Object reclaim_java_list_star_1(java_list)
    Object java_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(249,14);
    if (CONSP(java_list)) {
	temp = last(java_list,_);
	M_CDR(temp) = Nil;
	if (java_list) {
	    last_1 = java_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qjava);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qjava);
	    if (ISVREF(Available_java_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_java_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = java_list;
		temp = Available_java_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_java_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = java_list;
		temp = Available_java_conses_tail_vector;
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

/* RECLAIM-JAVA-TREE-1 */
Object reclaim_java_tree_1(tree)
    Object tree;
{
    Object e, e2, java_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(249,15);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_java_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		java_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(java_cons,Qjava);
		if (EQ(java_cons,e))
		    goto end_1;
		else if ( !TRUEP(java_cons))
		    goto end_1;
		else
		    java_cons = CDR(java_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_java_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_java_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_java_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_java_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_java_conses_tail_vector;
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

/* DELETE-JAVA-ELEMENT-1 */
Object delete_java_element_1(element,java_list)
    Object element, java_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(249,16);
    if (java_list) {
	if (EQ(element,M_CAR(java_list))) {
	    temp = CDR(java_list);
	    inline_note_reclaim_cons(java_list,Qjava);
	    if (ISVREF(Available_java_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_java_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = java_list;
		temp_1 = Available_java_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = java_list;
	    }
	    else {
		temp_1 = Available_java_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = java_list;
		temp_1 = Available_java_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = java_list;
	    }
	    M_CDR(java_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = java_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qjava);
		if (ISVREF(Available_java_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_java_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_java_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_java_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_java_conses_tail_vector;
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
	    temp = java_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-JAVA-CONS-1 */
Object delete_java_cons_1(java_cons,java_list)
    Object java_cons, java_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(249,17);
    if (EQ(java_cons,java_list))
	temp = CDR(java_list);
    else {
	l_trailer_qm = Nil;
	l = java_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,java_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = java_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_java_cons_1(java_cons);
    return VALUES_1(temp);
}

static Object Qexternal_procedure;  /* external-procedure */

static Object Qexternal_method_declaration;  /* external-method-declaration */

static Object Qincomplete;         /* incomplete */

/* INITIALIZE-FOR-EXTERNAL-PROCEDURE */
Object initialize_for_external_procedure(external_procedure)
    Object external_procedure;
{
    Object frame, sub_vector_qm, method_function_qm, gensymed_symbol;
    Object sub_class_bit_vector;
    SI_Long index_1, ab_loop_bind_, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_3;
    char temp;

    x_note_fn_call(249,18);
    frame = external_procedure;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)2L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qexternal_procedure)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	inline_funcall_1(method_function_qm,frame);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(Qexternal_method_declaration,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(external_procedure,
		(SI_Long)1L),(SI_Long)19L);
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
    if (temp);
    else
	temp = TRUEP(ISVREF(external_procedure,(SI_Long)20L));
    return update_frame_status(external_procedure,temp ? Nil : Qincomplete,
	    Nil);
}

/* CLEANUP-FOR-EXTERNAL-PROCEDURE */
Object cleanup_for_external_procedure(external_procedure)
    Object external_procedure;
{
    Object frame, sub_vector_qm, method_function_qm, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(249,19);
    frame = external_procedure;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qexternal_procedure)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	inline_funcall_1(method_function_qm,frame);
    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(external_procedure,
	    (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
    gensymed_symbol_1 = external_procedure;
    gensymed_symbol_2 = Nil;
    gensymed_symbol_3 = T;
    return inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
	    gensymed_symbol_2,gensymed_symbol_3);
}

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

/* INITIALIZE-FOR-EXTERNAL-METHOD-DECLARATION */
Object initialize_for_external_method_declaration(external_method_declaration)
    Object external_method_declaration;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(249,20);
    frame = external_method_declaration;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)2L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qexternal_method_declaration)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	inline_funcall_1(method_function_qm,frame);
    return update_frame_status(external_method_declaration,
	    get_lookup_slot_value_given_default(external_method_declaration,
	    Qname_or_names_for_frame,Nil) ? Qnil : Qincomplete,Nil);
}

static Object string_constant;     /* "~(~nq~)" */

static Object array_constant;      /* # */

/* WRITE-TW-METHOD-NAME-FROM-SLOT */
Object write_tw_method_name_from_slot(value,method)
    Object value, method;
{
    Object method_class_qm;

    x_note_fn_call(249,21);
    method_class_qm = ISVREF(method,(SI_Long)24L);
    if (value && method_class_qm)
	return tformat(3,string_constant,value,method_class_qm);
    else
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)4L));
}

static Object Qexternal_procedure_definition;  /* external-procedure-definition */

static Object Qexternal_method;    /* external-method */

static Object Qframe_status_and_notes;  /* frame-status-and-notes */

static Object Qstack_change;       /* stack-change */

static Object Qexternal_method_name;  /* external-method-name */

static Object Qexternal_method_class;  /* external-method-class */

/* PUT-EXTERNAL-PROCEDURE-DEFINITION */
Object put_external_procedure_definition(external_procedure,slot_value,
	    initializing_p)
    Object external_procedure, slot_value, initializing_p;
{
    Object old_gesture_function_qm, compiled_gesture, method_or_procedure_name;
    Object gensymed_symbol, sub_class_bit_vector, temp_1, type, class_1;
    Object result_1, current_flag_state_qm, slot_description, new_cons, temp_2;
    Object svref_arg_2, svref_new_value, gensymed_symbol_4;
    Object stack_of_slot_value_changes, gensymed_symbol_5, gensymed_symbol_6;
    Object frame_and_slot_or_atom, ab_loop_list_, ab_loop_it_;
    Object stack_change_pop_store, cons_1, next_cons;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long svref_new_value_1;
    char temp;
    Declare_special(1);

    x_note_fn_call(249,22);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(external_procedure,
		Qexternal_procedure_definition);
    SVREF(external_procedure,FIX((SI_Long)20L)) = slot_value;
    old_gesture_function_qm = ISVREF(external_procedure,(SI_Long)21L);
    compiled_gesture = CAR(slot_value);
    method_or_procedure_name = CAR(compiled_gesture);
    if (old_gesture_function_qm)
	reclaim_gesture_function(old_gesture_function_qm);
    if (compiled_gesture &&  !EQ(compiled_gesture,No_value)) {
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(Qexternal_method,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(external_procedure,
		    (SI_Long)1L),(SI_Long)19L);
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
		temp = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    temp_1 = CADR(compiled_gesture);
	    temp_1 = FIRST(temp_1);
	    type = CADR(temp_1);
	    class_1 = M_CAR(M_CDR(type));
	    result_1 = Nil;
	    current_flag_state_qm = Nil;
	    slot_description = 
		    get_slot_description_of_class_description_function(Qframe_status_and_notes,
		    ISVREF(external_procedure,(SI_Long)1L),Nil);
	    new_cons = ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp_2 = Available_stack_change_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp_2,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp_2 = Available_stack_change_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = Nil;
		}
		gensymed_symbol = new_cons;
	    }
	    else
		gensymed_symbol = Nil;
	    if ( !TRUEP(gensymed_symbol))
		gensymed_symbol = replenish_stack_change_cons_pool();
	    if (Nil)
		gensymed_symbol_4 = 
			nconc2(stack_change_list_2(external_procedure,
			slot_description),stack_change_cons_1(Nil,Nil));
	    else {
		new_cons = ISVREF(Available_stack_change_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    temp_2 = Available_stack_change_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(temp_2,svref_arg_2) = svref_new_value;
		    if ( 
			    !TRUEP(ISVREF(Available_stack_change_conses_vector,
			    IFIX(Current_thread_index)))) {
			temp_2 = Available_stack_change_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_2,svref_arg_2) = Nil;
		    }
		    gensymed_symbol_4 = new_cons;
		}
		else
		    gensymed_symbol_4 = Nil;
		if ( !TRUEP(gensymed_symbol_4))
		    gensymed_symbol_4 = replenish_stack_change_cons_pool();
		M_CAR(gensymed_symbol_4) = external_procedure;
		M_CDR(gensymed_symbol_4) = slot_description;
		inline_note_allocate_cons(gensymed_symbol_4,Qstack_change);
	    }
	    M_CAR(gensymed_symbol) = gensymed_symbol_4;
	    temp_2 = Stack_of_slot_value_changes;
	    M_CDR(gensymed_symbol) = temp_2;
	    inline_note_allocate_cons(gensymed_symbol,Qstack_change);
	    stack_of_slot_value_changes = gensymed_symbol;
	    PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
		    0);
	      current_flag_state_qm = (SI_Long)0L != 
		      (IFIX(ISVREF(external_procedure,(SI_Long)5L)) & 
		      (SI_Long)16777216L) ? T : Nil;
	      if ( !TRUEP(current_flag_state_qm)) {
		  gensymed_symbol = 
			  ISVREF(ISVREF(ISVREF(ISVREF(external_procedure,
			  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
		  gensymed_symbol_4 = external_procedure;
		  gensymed_symbol_5 = Nil;
		  gensymed_symbol_6 = T;
		  inline_funcall_3(gensymed_symbol,gensymed_symbol_4,
			  gensymed_symbol_5,gensymed_symbol_6);
		  svref_new_value_1 = IFIX(ISVREF(external_procedure,
			  (SI_Long)5L)) | (SI_Long)16777216L;
		  ISVREF(external_procedure,(SI_Long)5L) = 
			  FIX(svref_new_value_1);
	      }
	      change_slot_value(3,external_procedure,Qexternal_method_name,
		      method_or_procedure_name);
	      result_1 = change_slot_value(3,external_procedure,
		      Qexternal_method_class,class_1);
	      if ( !TRUEP(current_flag_state_qm)) {
		  svref_new_value_1 = IFIX(ISVREF(external_procedure,
			  (SI_Long)5L)) &  ~(SI_Long)16777216L;
		  ISVREF(external_procedure,(SI_Long)5L) = 
			  FIX(svref_new_value_1);
		  gensymed_symbol = 
			  ISVREF(ISVREF(ISVREF(ISVREF(external_procedure,
			  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
		  gensymed_symbol_4 = external_procedure;
		  gensymed_symbol_5 = T;
		  gensymed_symbol_6 = Nil;
		  inline_funcall_3(gensymed_symbol,gensymed_symbol_4,
			  gensymed_symbol_5,gensymed_symbol_6);
	      }
	      temp = TRUEP(Suppress_updating_of_slot_value_representations_qm);
	      if (temp);
	      else if (M_CDR(Stack_of_slot_value_changes)) {
		  frame_and_slot_or_atom = Nil;
		  ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
		  ab_loop_it_ = Nil;
		next_loop:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop;
		  frame_and_slot_or_atom = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  if (ATOM(frame_and_slot_or_atom))
		      goto end_loop;
		  temp = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
		  if (temp);
		  else {
		      temp_1 = M_CDR(frame_and_slot_or_atom);
		      temp = CONSP(temp_1) ? EQ(slot_description,
			      SECOND(frame_and_slot_or_atom)) && EQ(Nil,
			      THIRD(frame_and_slot_or_atom)) && EQ(Nil,
			      CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
		  }
		  ab_loop_it_ = temp ? (EQ(external_procedure,
			  M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
		  if (ab_loop_it_) {
		      temp = TRUEP(ab_loop_it_);
		      goto end_1;
		  }
		  goto next_loop;
		end_loop:
		  temp = TRUEP(Qnil);
		end_1:;
	      }
	      else
		  temp = TRUEP(Nil);
	      if ( !temp)
		  update_all_representations_of_slot(external_procedure,
			  slot_description,Nil,Nil);
	      if (ISVREF(slot_description,(SI_Long)14L))
		  update_frame_name_references(external_procedure);
	      stack_change_pop_store = Nil;
	      cons_1 = Stack_of_slot_value_changes;
	      if (cons_1) {
		  stack_change_pop_store = M_CAR(cons_1);
		  next_cons = M_CDR(cons_1);
		  inline_note_reclaim_cons(cons_1,Qstack_change);
		  if (ISVREF(Available_stack_change_conses_tail_vector,
			  IFIX(Current_thread_index))) {
		      temp_2 = 
			      ISVREF(Available_stack_change_conses_tail_vector,
			      IFIX(Current_thread_index));
		      M_CDR(temp_2) = cons_1;
		      temp_2 = Available_stack_change_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp_2,svref_arg_2) = cons_1;
		  }
		  else {
		      temp_2 = Available_stack_change_conses_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp_2,svref_arg_2) = cons_1;
		      temp_2 = Available_stack_change_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp_2,svref_arg_2) = cons_1;
		  }
		  M_CDR(cons_1) = Nil;
	      }
	      else
		  next_cons = Nil;
	      Stack_of_slot_value_changes = next_cons;
	      reclaim_stack_change_tree_1(stack_change_pop_store);
	      if (Stack_of_slot_value_changes) {
		  temp_1 = M_CAR(Stack_of_slot_value_changes);
		  temp = ATOM(temp_1);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp ?  
		      !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) 
		      : TRUEP(Nil))
		  do_deferred_updates_to_representations_in_tables();
	    POP_SPECIAL();
	}
	else {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(external_procedure,
			Qname_or_names_for_frame);
	    set_lookup_slot_value_1(external_procedure,
		    Qname_or_names_for_frame,method_or_procedure_name);
	}
	update_frame_status(external_procedure,Nil,Nil);
	temp_2 = emit_compiled_gesture(compiled_gesture);
	return VALUES_1(ISVREF(external_procedure,(SI_Long)21L) = temp_2);
    }
    else {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(external_procedure,
		    Qname_or_names_for_frame);
	set_lookup_slot_value_1(external_procedure,
		Qname_or_names_for_frame,Nil);
	update_frame_status(external_procedure,Qincomplete,Nil);
	return VALUES_1(ISVREF(external_procedure,(SI_Long)21L) = Nil);
    }
}

static Object array_constant_1;    /* # */

static Object array_constant_2;    /* # */

static Object Qtwrite;             /* twrite */

static Object string_constant_1;   /* " and " */

static Object string_constant_2;   /* ", " */

static Object string_constant_3;   /* "the class ~A" */

/* WRITE-DUPLICATE-CLASS-EXPORT-NOTE */
Object write_duplicate_class_export_note(particulars,gensymed_symbol)
    Object particulars, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(249,23);
    twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)45L));
    if (CDR(particulars)) {
	twrite_beginning_of_wide_string(array_constant_2,FIX((SI_Long)12L));
	temp = twrite_list_function(particulars,SYMBOL_FUNCTION(Qtwrite),
		Nil,string_constant_1,string_constant_2);
    }
    else
	temp = tformat(2,string_constant_3,CAR(particulars));
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* COM-EDIT-EXTERNAL-PROCEDURE */
Object com_edit_external_procedure(external_procedure)
    Object external_procedure;
{
    Object gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(249,24);
    if (of_class_p_function(external_procedure,Qexternal_procedure)) {
	if (type_of_slot_if_editable(2,ISVREF(ISVREF(external_procedure,
		(SI_Long)1L),(SI_Long)1L),Qexternal_procedure_definition)) {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(Qexternal_method_declaration,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(external_procedure,
			(SI_Long)1L),(SI_Long)19L);
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
	    temp =  !temp;
	}
	else
	    temp = TRUEP(Nil);
	temp = temp ?  
		!TRUEP(text_slots_in_frame_have_been_stripped_p(external_procedure)) 
		: TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return enter_editing_context(2,external_procedure,
		Qexternal_procedure_definition);
    else
	return VALUES_1(Nil);
}

/* EDIT-EXTERNAL-PROCEDURE-COMMAND-PURSUER */
Object edit_external_procedure_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, external_procedure;

    x_note_fn_call(249,25);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    external_procedure = CAR(gensymed_symbol);
    external_procedure = command_argument_value(external_procedure);
    if (EQ(external_procedure,Plus_missing_argument_plus))
	return VALUES_3(Qexternal_procedure,Qexternal_procedure,
		FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

static Object Qedit_external_procedure;  /* edit-external-procedure */

/* EDIT-EXTERNAL-PROCEDURE-COMMAND-TRANSLATOR */
Object edit_external_procedure_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object external_procedure, gensymed_symbol, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(249,26);
    external_procedure = 
	    find_frame_of_class_in_mouse_pointer(mouse_pointer,
	    Qexternal_procedure);
    if (external_procedure) {
	if (type_of_slot_if_editable(2,ISVREF(ISVREF(external_procedure,
		(SI_Long)1L),(SI_Long)1L),Qexternal_procedure_definition)) {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(Qexternal_method_declaration,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(external_procedure,
			(SI_Long)1L),(SI_Long)19L);
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
	    temp =  !temp;
	}
	else
	    temp = TRUEP(Nil);
	if (temp ?  
		!TRUEP(text_slots_in_frame_have_been_stripped_p(external_procedure)) 
		: TRUEP(Nil)) {
	    temp_1 = external_procedure;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    return make_partial_command(Qedit_external_procedure,
		    slot_value_cons_1(snapshot_command_argument(temp_1),Nil));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* RECLAIM-VISIBLE-CLASS-EXPORT-INFORMATION?-VALUE */
Object reclaim_visible_class_export_information_qm_value(export_info_qm,
	    gensymed_symbol)
    Object export_info_qm, gensymed_symbol;
{
    x_note_fn_call(249,27);
    if (export_info_qm)
	reclaim_external_class_info_list(export_info_qm);
    return VALUES_1(Nil);
}

/* WRITE-EXPORT-DEFINITION-LANGUAGE-FROM-SLOT */
Object write_export_definition_language_from_slot(slot_value,gensymed_symbol)
    Object slot_value, gensymed_symbol;
{
    x_note_fn_call(249,28);
    return twrite(slot_value);
}

static Object array_constant_3;    /* # */

/* WRITE-READ-ONLY-INSTANCE-METHODS-FROM-SLOT */
Object write_read_only_instance_methods_from_slot(slot_value_qm,
	    gensymed_symbol)
    Object slot_value_qm, gensymed_symbol;
{
    Object write_symbols_parsably_qm, qualified_symbol, ab_loop_list_;
    Object qualified_symbol_cons, ab_loop_iter_flag_;
    Declare_special(1);
    Object result;

    x_note_fn_call(249,29);
    if (slot_value_qm) {
	write_symbols_parsably_qm = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
		0);
	  qualified_symbol = Nil;
	  ab_loop_list_ = slot_value_qm;
	  qualified_symbol_cons = slot_value_qm;
	  ab_loop_iter_flag_ = T;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  qualified_symbol = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if ( !TRUEP(ab_loop_iter_flag_))
	      qualified_symbol_cons = M_CDR(qualified_symbol_cons);
	  if ( !TRUEP(qualified_symbol_cons))
	      goto end_loop;
	  twrite_symbol(1,qualified_symbol);
	  if (CDR(qualified_symbol_cons))
	      twrite_beginning_of_wide_string(array_constant_3,
		      FIX((SI_Long)2L));
	  ab_loop_iter_flag_ = Nil;
	  goto next_loop;
	end_loop:
	  result = VALUES_1(Qnil);
	POP_SPECIAL();
	return result;
    }
    else
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)4L));
}

static Object string_constant_4;   /* "the following classes have no corresponding definitions in G2: " */

static Object string_constant_5;   /* "the class ~S has no corresponding definition in G2" */

/* WRITE-NONEXISTENT-CLASSES-FOR-EXPORT-NOTE */
Object write_nonexistent_classes_for_export_note(nonexistent_classes_list,
	    export_definition)
    Object nonexistent_classes_list, export_definition;
{
    Object temp;

    x_note_fn_call(249,30);
    if (CDR(nonexistent_classes_list)) {
	tformat(1,string_constant_4);
	temp = twrite_list_function(nonexistent_classes_list,
		SYMBOL_FUNCTION(Qtwrite),Nil,string_constant_2,
		string_constant_2);
    }
    else
	temp = tformat(2,string_constant_5,CAR(nonexistent_classes_list));
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object string_constant_6;   /* "(~A) " */

static Object string_constant_7;   /* "the following static methods in class ~A ~
				    *              have no corresponding procedure definitions in G2: "
				    */

static Object string_constant_8;   /* "the static method ~A in class ~S ~
				    *               has no corresponding procedure definition in G2"
				    */

static Object array_constant_4;    /* # */

/* WRITE-NONEXISTENT-STATIC-METHODS-FOR-EXPORT-NOTE */
Object write_nonexistent_static_methods_for_export_note(particulars,
	    export_definition)
    Object particulars, export_definition;
{
    Object enumerate_p, class_name, nonexistent_methods, ab_loop_list_;
    Object particulars_cons, ab_loop_iter_flag_, ab_loop_desetq_;
    SI_Long index_1;

    x_note_fn_call(249,31);
    enumerate_p = CDR(particulars);
    class_name = Nil;
    nonexistent_methods = Nil;
    ab_loop_list_ = particulars;
    particulars_cons = particulars;
    index_1 = (SI_Long)0L;
    ab_loop_iter_flag_ = T;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    class_name = CAR(ab_loop_desetq_);
    nonexistent_methods = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	particulars_cons = M_CDR(particulars_cons);
    if ( !TRUEP(particulars_cons))
	goto end_loop;
    if ( !TRUEP(ab_loop_iter_flag_))
	index_1 = index_1 + (SI_Long)1L;
    if (enumerate_p)
	tformat(2,string_constant_6,FIX(index_1 + IFIX(Frame_note_index)));
    if (CDR(nonexistent_methods)) {
	tformat(2,string_constant_7,class_name);
	twrite_list_function(nonexistent_methods,SYMBOL_FUNCTION(Qtwrite),
		Nil,string_constant_2,string_constant_2);
    }
    else
	tformat(3,string_constant_8,CAR(nonexistent_methods),class_name);
    if (enumerate_p) {
	if (CDR(particulars_cons)) {
	    twrite_beginning_of_wide_string(array_constant_4,FIX((SI_Long)1L));
	    twrite_line_separator();
	}
    }
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    if (enumerate_p)
	Frame_note_index_skip = FIX(index_1 - (SI_Long)1L);
    GENSYM_RETURN_ONE(Qnil);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Analyzing_export_definition_for_consistency_p, Qanalyzing_export_definition_for_consistency_p);

/* ANALYZE-FOR-CONSISTENCY-FOR-EXPORT-DEFINITION */
Object analyze_for_consistency_for_export_definition(export_definition,
	    add_as_item_referring_to_name_qm,
	    delete_as_item_referring_to_name_qm)
    Object export_definition, add_as_item_referring_to_name_qm;
    Object delete_as_item_referring_to_name_qm;
{
    Object compiled_item_being_analyzed;
    Object analyzing_export_definition_for_consistency_p;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(4);
    Object result;

    x_note_fn_call(249,32);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Delete_as_item_referring_to_name_qm,Qdelete_as_item_referring_to_name_qm,delete_as_item_referring_to_name_qm,
	    3);
      PUSH_SPECIAL_WITH_SYMBOL(Add_as_item_referring_to_name_qm,Qadd_as_item_referring_to_name_qm,add_as_item_referring_to_name_qm,
	      2);
	if (Defer_consistency_analysis_qm &&  
		!TRUEP(Add_as_item_referring_to_name_qm) &&  
		!TRUEP(Delete_as_item_referring_to_name_qm))
	    result = defer_consistency_analysis_of_item(export_definition);
	else {
	    LOCK(Analyze_for_consistency_in_progress);
	    if (PUSH_UNWIND_PROTECT(0)) {
		if ( !TRUEP(Analyzing_export_definition_for_consistency_p)) {
		    compiled_item_being_analyzed = export_definition;
		    analyzing_export_definition_for_consistency_p = T;
		    PUSH_SPECIAL_WITH_SYMBOL(Analyzing_export_definition_for_consistency_p,Qanalyzing_export_definition_for_consistency_p,analyzing_export_definition_for_consistency_p,
			    1);
		      PUSH_SPECIAL_WITH_SYMBOL(Compiled_item_being_analyzed,Qcompiled_item_being_analyzed,compiled_item_being_analyzed,
			      0);
			delete_all_consistency_analysis_frame_notes(1,
				export_definition);
			SAVE_VALUES(analyze_export_definition_for_consistency(export_definition));
		      POP_SPECIAL();
		    POP_SPECIAL();
		}
		else
		    SAVE_VALUES(VALUES_1(Nil));
	    }
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Analyze_for_consistency_in_progress);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	}
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Qexport_definition_specification;  /* export-definition-specification */

static Object Qinterface;          /* interface */

static Object Qcode;               /* code */

/* ANALYZE-EXPORT-DEFINITION-FOR-CONSISTENCY */
Object analyze_export_definition_for_consistency(export_definition)
    Object export_definition;
{
    Object definition_spec, language, export_specs, exported_class;
    Object export_type, options, ab_loop_list_, ab_loop_desetq_, temp;

    x_note_fn_call(249,33);
    definition_spec = 
	    get_lookup_slot_value_given_default(export_definition,
	    Qexport_definition_specification,Nil);
    language = CAR(definition_spec);
    export_specs = CADR(definition_spec);
    if (EQ(language,Qjava)) {
	exported_class = Nil;
	export_type = Nil;
	options = Nil;
	ab_loop_list_ = export_specs;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	exported_class = CAR(ab_loop_desetq_);
	temp = CDR(ab_loop_desetq_);
	export_type = CAR(temp);
	temp = CDR(ab_loop_desetq_);
	temp = CDR(temp);
	options = CAR(temp);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(export_type,Qinterface) || EQ(export_type,Qcode) || 
		EQ(export_type,Qnil)) {
	    check_exported_classes(export_definition,exported_class);
	    check_external_static_methods(export_definition,exported_class,
		    options);
	}
	goto next_loop;
      end_loop:;
	check_external_static_method_info(export_definition);
	check_external_instance_method_info(export_definition);
    }
    return VALUES_1(Nil);
}

static Object Qduplicate_class_export_in_single_item;  /* duplicate-class-export-in-single-item */

/* CHECK-FOR-DUPLICATE-CLASS-IN-SINGLE-EXPORT-DEFINITION */
Object check_for_duplicate_class_in_single_export_definition(export_definition)
    Object export_definition;
{
    Object export_class, temp, ab_loop_list_, classes_encountered;
    Object ab_loop_desetq_;

    x_note_fn_call(249,34);
    delete_frame_note_if_any(Qduplicate_class_export_in_single_item,
	    export_definition);
    export_class = Nil;
    temp = get_lookup_slot_value_given_default(export_definition,
	    Qexport_definition_specification,Nil);
    ab_loop_list_ = CADR(temp);
    classes_encountered = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    export_class = CAR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (memq_function(export_class,classes_encountered)) {
	add_frame_note(2,Qduplicate_class_export_in_single_item,
		export_definition);
	goto end_loop;
    }
    else
	classes_encountered = java_cons_1(export_class,classes_encountered);
    goto next_loop;
  end_loop:
    reclaim_java_list_1(classes_encountered);
    return VALUES_1(Qnil);
}

static Object array_constant_5;    /* # */

static Object array_constant_6;    /* # */

/* WRITE-DUPLICATE-CLASS-EXPORT-IN-SINGLE-ITEM-NOTE */
Object write_duplicate_class_export_in_single_item_note(particulars,
	    gensymed_symbol)
    Object particulars, gensymed_symbol;
{
    x_note_fn_call(249,35);
    twrite_beginning_of_wide_string(array_constant_5,FIX((SI_Long)59L));
    GENSYM_RETURN_ONE(twrite_beginning_of_wide_string(array_constant_6,
	    FIX((SI_Long)35L)));
    return VALUES_1(Nil);
}

/* PUT-EXPORT-DEFINITION-SPECIFICATION */
Object put_export_definition_specification(export_definition,slot_value,
	    initializing_p)
    Object export_definition, slot_value, initializing_p;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3;

    x_note_fn_call(249,36);
    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(export_definition,
	    (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
    gensymed_symbol_1 = export_definition;
    gensymed_symbol_2 = Nil;
    gensymed_symbol_3 = T;
    inline_funcall_3(gensymed_symbol,gensymed_symbol_1,gensymed_symbol_2,
	    gensymed_symbol_3);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(export_definition,
		Qexport_definition_specification);
    set_lookup_slot_value_1(export_definition,
	    Qexport_definition_specification,slot_value);
    check_for_duplicate_class_in_single_export_definition(export_definition);
    update_all_external_method_info(export_definition);
    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(export_definition,
	    (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
    gensymed_symbol_1 = export_definition;
    gensymed_symbol_2 = T;
    gensymed_symbol_3 = Nil;
    return inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
	    gensymed_symbol_2,gensymed_symbol_3);
}

static Object Qexport_definition;  /* export-definition */

/* CLEANUP-FOR-EXPORT-DEFINITION */
Object cleanup_for_export_definition(export_definition)
    Object export_definition;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(249,37);
    frame = export_definition;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qexport_definition)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	inline_funcall_1(method_function_qm,frame);
    return change_slot_value(3,export_definition,
	    Qexport_definition_specification,Nil);
}

static Object Qstatic_methods;     /* static-methods */

static Object Qab_directory;       /* directory */

static Object Qimports;            /* imports */

static Object Qclass_path;         /* class-path */

static Object Qsuperior_class_override;  /* superior-class-override */

static Object Qincluded_instance_methods;  /* included-instance-methods */

static Object Qexcluded_instance_methods;  /* excluded-instance-methods */

static Object string_constant_9;   /* "class ~(~a~) with~%" */

static Object string_constant_10;  /* "  directory ~s" */

static Object string_constant_11;  /* " and~%" */

static Object string_constant_12;  /* "  imports ~" */

static Object Qtwrite_parsably;    /* twrite-parsably */

static Object string_constant_13;  /* "  package ~s" */

static Object string_constant_14;  /* "  class-path ~s" */

static Object string_constant_15;  /* "  superior-class-override ~(~a~)" */

static Object string_constant_16;  /* "  static-methods " */

static Object string_constant_17;  /* "  only the instance methods " */

static Object string_constant_18;  /* "  all instance methods except " */

static Object string_constant_19;  /* ";~%" */

/* WRITE-EXPORT-DEFINITION-SPECIFICATION-FROM-SLOT */
Object write_export_definition_specification_from_slot(slot_value,
	    gensymed_symbol)
    Object slot_value, gensymed_symbol;
{
    Object language, export_list, export_list_tail, class_name, options;
    Object static_methods_qm, directory_qm, imports_qm, package_qm;
    Object class_path_qm, superior_class_override_qm;
    Object included_instance_methods_qm, excluded_instance_methods_qm;
    Object option_count, options_written, temp, write_strings_parsably_qm;
    Declare_special(1);

    x_note_fn_call(249,38);
    language = CAR(slot_value);
    export_list = CADR(slot_value);
    if (EQ(language,Qjava)) {
	export_list_tail = export_list;
	class_name = Nil;
	options = Nil;
	static_methods_qm = Nil;
	directory_qm = Nil;
	imports_qm = Nil;
	package_qm = Nil;
	class_path_qm = Nil;
	superior_class_override_qm = Nil;
	included_instance_methods_qm = Nil;
	excluded_instance_methods_qm = Nil;
	option_count = Nil;
	options_written = Nil;
      next_loop:
	if ( !TRUEP(export_list_tail))
	    goto end_loop;
	temp = CAR(export_list_tail);
	class_name = CAR(temp);
	temp = CAR(export_list_tail);
	temp = CDR(temp);
	temp = CDR(temp);
	options = CAR(temp);
	temp = assq_function(Qstatic_methods,options);
	static_methods_qm = CADR(temp);
	temp = assq_function(Qab_directory,options);
	directory_qm = CADR(temp);
	temp = assq_function(Qimports,options);
	imports_qm = CADR(temp);
	temp = assq_function(Qpackage_type,options);
	package_qm = CADR(temp);
	temp = assq_function(Qclass_path,options);
	class_path_qm = CADR(temp);
	temp = assq_function(Qsuperior_class_override,options);
	superior_class_override_qm = CADR(temp);
	temp = assq_function(Qincluded_instance_methods,options);
	included_instance_methods_qm = CADR(temp);
	temp = assq_function(Qexcluded_instance_methods,options);
	excluded_instance_methods_qm = CADR(temp);
	option_count = length(options);
	options_written = FIX((SI_Long)0L);
	tformat(2,string_constant_9,class_name);
	if (directory_qm) {
	    options_written = FIXNUM_ADD1(options_written);
	    write_strings_parsably_qm = T;
	    PUSH_SPECIAL_WITH_SYMBOL(Write_strings_parsably_qm,Qwrite_strings_parsably_qm,write_strings_parsably_qm,
		    0);
	      tformat(2,string_constant_10,directory_qm);
	    POP_SPECIAL();
	    if (FIXNUM_LT(options_written,option_count))
		tformat(1,string_constant_11);
	}
	if (imports_qm) {
	    options_written = FIXNUM_ADD1(options_written);
	    tformat(1,string_constant_12);
	    twrite_list_function(imports_qm,
		    SYMBOL_FUNCTION(Qtwrite_parsably),Nil,
		    string_constant_2,string_constant_2);
	    if (FIXNUM_LT(options_written,option_count))
		tformat(1,string_constant_11);
	}
	if (package_qm) {
	    options_written = FIXNUM_ADD1(options_written);
	    write_strings_parsably_qm = T;
	    PUSH_SPECIAL_WITH_SYMBOL(Write_strings_parsably_qm,Qwrite_strings_parsably_qm,write_strings_parsably_qm,
		    0);
	      tformat(2,string_constant_13,package_qm);
	    POP_SPECIAL();
	    if (FIXNUM_LT(options_written,option_count))
		tformat(1,string_constant_11);
	}
	if (class_path_qm) {
	    options_written = FIXNUM_ADD1(options_written);
	    write_strings_parsably_qm = T;
	    PUSH_SPECIAL_WITH_SYMBOL(Write_strings_parsably_qm,Qwrite_strings_parsably_qm,write_strings_parsably_qm,
		    0);
	      tformat(2,string_constant_14,class_path_qm);
	    POP_SPECIAL();
	    if (FIXNUM_LT(options_written,option_count))
		tformat(1,string_constant_11);
	}
	if (superior_class_override_qm) {
	    options_written = FIXNUM_ADD1(options_written);
	    write_strings_parsably_qm = T;
	    PUSH_SPECIAL_WITH_SYMBOL(Write_strings_parsably_qm,Qwrite_strings_parsably_qm,write_strings_parsably_qm,
		    0);
	      tformat(2,string_constant_15,superior_class_override_qm);
	    POP_SPECIAL();
	    if (FIXNUM_LT(options_written,option_count))
		tformat(1,string_constant_11);
	}
	if (static_methods_qm) {
	    options_written = FIXNUM_ADD1(options_written);
	    tformat(1,string_constant_16);
	    twrite_list_function(static_methods_qm,
		    SYMBOL_FUNCTION(Qtwrite),Nil,string_constant_2,
		    string_constant_2);
	    if (FIXNUM_LT(options_written,option_count))
		tformat(1,string_constant_11);
	}
	if (included_instance_methods_qm) {
	    options_written = FIXNUM_ADD1(options_written);
	    tformat(1,string_constant_17);
	    twrite_list_function(included_instance_methods_qm,
		    SYMBOL_FUNCTION(Qtwrite),Nil,string_constant_2,
		    string_constant_2);
	    if (FIXNUM_LT(options_written,option_count))
		tformat(1,string_constant_11);
	}
	if (excluded_instance_methods_qm) {
	    options_written = FIXNUM_ADD1(options_written);
	    tformat(1,string_constant_18);
	    twrite_list_function(excluded_instance_methods_qm,
		    SYMBOL_FUNCTION(Qtwrite),Nil,string_constant_2,
		    string_constant_2);
	    if (FIXNUM_LT(options_written,option_count))
		tformat(1,string_constant_11);
	}
	if ( ! !TRUEP(CDR(export_list_tail)))
	    tformat(1,string_constant_19);
	export_list_tail = M_CDR(export_list_tail);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Collecting_frame_notes_for_class_export_p, Qcollecting_frame_notes_for_class_export_p);

DEFINE_VARIABLE_WITH_SYMBOL(Collected_frame_notes_for_class_export_qm, Qcollected_frame_notes_for_class_export_qm);

static Object Qexport_definition_language;  /* export-definition-language */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object array_constant_7;    /* # */

/* G2-EXPORT-DEFINITIONS */
Object g2_export_definitions(external_definition)
    Object external_definition;
{
    Object slot_value, language, export_list, additional_methods_qm;
    Object export_list_tail, class_name, interface_or_code, options;
    Object static_methods_qm, directory_qm, imports_qm, package_qm;
    Object class_path_qm, superior_class_override_qm, temp, static_method_list;
    Object collecting_frame_notes_for_class_export_p;
    Object collected_frame_notes_for_class_export_qm, temp_1;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object error_string_qm, error_string_qm_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(7);

    x_note_fn_call(249,39);
    if (EQ(get_lookup_slot_value(external_definition,
	    Qexport_definition_language),Qjava)) {
	slot_value = 
		get_lookup_slot_value_given_default(external_definition,
		Qexport_definition_specification,Nil);
	language = CAR(slot_value);
	export_list = CADR(slot_value);
	additional_methods_qm = CDR(export_list) ? Nil : 
		get_hand_coded_methods_for_class_if_any(external_definition);
	if (EQ(language,Qjava)) {
	    export_list_tail = export_list;
	    class_name = Nil;
	    interface_or_code = Nil;
	    options = Nil;
	    static_methods_qm = Nil;
	    directory_qm = Nil;
	    imports_qm = Nil;
	    package_qm = Nil;
	    class_path_qm = Nil;
	    superior_class_override_qm = Nil;
	  next_loop:
	    if ( !TRUEP(export_list_tail))
		goto end_loop;
	    temp = CAR(export_list_tail);
	    class_name = CAR(temp);
	    temp = CAR(export_list_tail);
	    temp = CDR(temp);
	    interface_or_code = CAR(temp);
	    temp = CAR(export_list_tail);
	    temp = CDR(temp);
	    temp = CDR(temp);
	    options = CAR(temp);
	    temp = assq_function(Qstatic_methods,options);
	    static_methods_qm = CADR(temp);
	    temp = assq_function(Qab_directory,options);
	    directory_qm = CADR(temp);
	    temp = assq_function(Qimports,options);
	    imports_qm = CADR(temp);
	    temp = assq_function(Qpackage_type,options);
	    package_qm = CADR(temp);
	    temp = assq_function(Qclass_path,options);
	    class_path_qm = CADR(temp);
	    temp = assq_function(Qsuperior_class_override,options);
	    superior_class_override_qm = CADR(temp);
	    if (EQ(interface_or_code,Qinterface) || EQ(interface_or_code,
		    Qcode) || EQ(interface_or_code,Qnil)) {
		static_method_list = 
			get_exported_static_methods_if_any(external_definition,
			class_name);
		collecting_frame_notes_for_class_export_p = T;
		PUSH_SPECIAL_WITH_SYMBOL(Collecting_frame_notes_for_class_export_p,Qcollecting_frame_notes_for_class_export_p,collecting_frame_notes_for_class_export_p,
			6);
		  collected_frame_notes_for_class_export_qm = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Collected_frame_notes_for_class_export_qm,Qcollected_frame_notes_for_class_export_qm,collected_frame_notes_for_class_export_qm,
			  5);
		    temp_1 = class_name;
		    current_wide_string_list = Qdo_not_use;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
			    4);
		      wide_string_bv16 = 
			      allocate_byte_vector_16(FIX((SI_Long)2048L + 
			      (SI_Long)3L));
		      bv16_length = 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
		      aref_arg_2 = bv16_length - (SI_Long)2L;
		      aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
		      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			      aref_new_value);
		      aref_arg_2 = bv16_length - (SI_Long)1L;
		      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
		      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			      aref_new_value);
		      UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,
			      (SI_Long)0L);
		      current_wide_string = wide_string_bv16;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
			      3);
			fill_pointer_for_current_wide_string = 
				FIX((SI_Long)0L);
			PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
				2);
			  length_1 = 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
			  total_length_of_current_wide_string = 
				  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
				  length_1 - (SI_Long)2L) + 
				  ((UBYTE_16_ISAREF_1(Current_wide_string,
				  length_1 - (SI_Long)1L) & 
				  (SI_Long)8191L) << (SI_Long)16L));
			  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
				  1);
			    current_twriting_output_type = Qwide_string;
			    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				    0);
			      twrite_general_string(directory_qm);
			      jwrite_symbol(2,class_name,T);
			      twrite_beginning_of_wide_string(array_constant_7,
				      FIX((SI_Long)5L));
			      temp = copy_out_current_wide_string();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		    error_string_qm = jemit_class_to_file(temp_1,
			    static_method_list,temp,package_qm,imports_qm,
			    class_path_qm,Nil,superior_class_override_qm,
			    additional_methods_qm);
		    error_string_qm_1 = error_string_qm;
		    update_mapping_problem_frame_notes_if_necessary(external_definition,
			    class_name,error_string_qm_1);
		  POP_SPECIAL();
		POP_SPECIAL();
		reclaim_slot_value_list_1(static_method_list);
		if (additional_methods_qm)
		    reclaim_text_string(additional_methods_qm);
	    }
	    export_list_tail = M_CDR(export_list_tail);
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

static Object Kstack_error;        /* :stack-error */

/* G2-EXPORT-DEFINITIONS-SYSTEM-RPC-INTERNAL */
Object g2_export_definitions_system_rpc_internal(gensymed_symbol,
	    export_definition)
    Object gensymed_symbol, export_definition;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(249,40);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    gensymed_symbol_1 = g2_export_definitions(export_definition);
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

Object The_type_description_of_java_symbol = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_java_symbols, Qchain_of_available_java_symbols);

DEFINE_VARIABLE_WITH_SYMBOL(Java_symbol_count, Qjava_symbol_count);

Object Chain_of_available_java_symbols_vector = UNBOUND;

/* JAVA-SYMBOL-STRUCTURE-MEMORY-USAGE */
Object java_symbol_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(249,41);
    temp = Java_symbol_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)3L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-JAVA-SYMBOL-COUNT */
Object outstanding_java_symbol_count()
{
    Object def_structure_java_symbol_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(249,42);
    gensymed_symbol = IFIX(Java_symbol_count);
    def_structure_java_symbol_variable = Chain_of_available_java_symbols;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_java_symbol_variable))
	goto end_loop;
    def_structure_java_symbol_variable = 
	    ISVREF(def_structure_java_symbol_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-JAVA-SYMBOL-1 */
Object reclaim_java_symbol_1(java_symbol)
    Object java_symbol;
{
    Object temp, svref_arg_2;

    x_note_fn_call(249,43);
    inline_note_reclaim_cons(java_symbol,Nil);
    temp = ISVREF(Chain_of_available_java_symbols_vector,
	    IFIX(Current_thread_index));
    SVREF(java_symbol,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_java_symbols_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = java_symbol;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-JAVA-SYMBOL */
Object reclaim_structure_for_java_symbol(java_symbol)
    Object java_symbol;
{
    x_note_fn_call(249,44);
    return reclaim_java_symbol_1(java_symbol);
}

static Object Qg2_defstruct_structure_name_java_symbol_g2_struct;  /* g2-defstruct-structure-name::java-symbol-g2-struct */

/* MAKE-PERMANENT-JAVA-SYMBOL-STRUCTURE-INTERNAL */
Object make_permanent_java_symbol_structure_internal()
{
    Object def_structure_java_symbol_variable;
    Object defstruct_g2_java_symbol_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(249,45);
    def_structure_java_symbol_variable = Nil;
    atomic_incff_symval(Qjava_symbol_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_java_symbol_variable = Nil;
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
	defstruct_g2_java_symbol_variable = the_array;
	SVREF(defstruct_g2_java_symbol_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_java_symbol_g2_struct;
	def_structure_java_symbol_variable = defstruct_g2_java_symbol_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_java_symbol_variable);
}

/* MAKE-JAVA-SYMBOL-1 */
Object make_java_symbol_1()
{
    Object def_structure_java_symbol_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(249,46);
    def_structure_java_symbol_variable = 
	    ISVREF(Chain_of_available_java_symbols_vector,
	    IFIX(Current_thread_index));
    if (def_structure_java_symbol_variable) {
	svref_arg_1 = Chain_of_available_java_symbols_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_java_symbol_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_java_symbol_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_java_symbol_g2_struct;
    }
    else
	def_structure_java_symbol_variable = 
		make_permanent_java_symbol_structure_internal();
    inline_note_allocate_cons(def_structure_java_symbol_variable,Nil);
    SVREF(def_structure_java_symbol_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_java_symbol_variable,FIX((SI_Long)2L)) = Nil;
    return VALUES_1(def_structure_java_symbol_variable);
}

DEFINE_VARIABLE_WITH_SYMBOL(The_java_symbol_table, Qthe_java_symbol_table);

/* GET-JAVA-SYMBOL-IF-ANY? */
Object get_java_symbol_if_any_qm(stringw_1)
    Object stringw_1;
{
    Object java_symbol, ab_loop_list_;

    x_note_fn_call(249,47);
    java_symbol = Nil;
    ab_loop_list_ = The_java_symbol_table;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    java_symbol = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (string_eq_w(stringw_1,ISVREF(java_symbol,(SI_Long)1L)))
	return VALUES_1(java_symbol);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* INTERN-JAVA-SYMBOL */
Object intern_java_symbol(stringw_1)
    Object stringw_1;
{
    Object java_symbol;

    x_note_fn_call(249,48);
    java_symbol = make_java_symbol_1();
    SVREF(java_symbol,FIX((SI_Long)1L)) = stringw_1;
    The_java_symbol_table = java_cons_1(java_symbol,The_java_symbol_table);
    return VALUES_1(java_symbol);
}

Object The_type_description_of_java_class = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_java_classs, Qchain_of_available_java_classs);

DEFINE_VARIABLE_WITH_SYMBOL(Java_class_count, Qjava_class_count);

Object Chain_of_available_java_classs_vector = UNBOUND;

/* JAVA-CLASS-STRUCTURE-MEMORY-USAGE */
Object java_class_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(249,49);
    temp = Java_class_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)14L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-JAVA-CLASS-COUNT */
Object outstanding_java_class_count()
{
    Object def_structure_java_class_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(249,50);
    gensymed_symbol = IFIX(Java_class_count);
    def_structure_java_class_variable = Chain_of_available_java_classs;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_java_class_variable))
	goto end_loop;
    def_structure_java_class_variable = 
	    ISVREF(def_structure_java_class_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-JAVA-CLASS-1 */
Object reclaim_java_class_1(java_class)
    Object java_class;
{
    Object temp, svref_arg_2;

    x_note_fn_call(249,51);
    inline_note_reclaim_cons(java_class,Nil);
    temp = ISVREF(Chain_of_available_java_classs_vector,
	    IFIX(Current_thread_index));
    SVREF(java_class,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_java_classs_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = java_class;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-JAVA-CLASS */
Object reclaim_structure_for_java_class(java_class)
    Object java_class;
{
    x_note_fn_call(249,52);
    return reclaim_java_class_1(java_class);
}

static Object Qg2_defstruct_structure_name_java_class_g2_struct;  /* g2-defstruct-structure-name::java-class-g2-struct */

/* MAKE-PERMANENT-JAVA-CLASS-STRUCTURE-INTERNAL */
Object make_permanent_java_class_structure_internal()
{
    Object def_structure_java_class_variable, defstruct_g2_java_class_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(249,53);
    def_structure_java_class_variable = Nil;
    atomic_incff_symval(Qjava_class_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_java_class_variable = Nil;
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
	defstruct_g2_java_class_variable = the_array;
	SVREF(defstruct_g2_java_class_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_java_class_g2_struct;
	def_structure_java_class_variable = defstruct_g2_java_class_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_java_class_variable);
}

/* MAKE-JAVA-CLASS-1 */
Object make_java_class_1()
{
    Object def_structure_java_class_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(249,54);
    def_structure_java_class_variable = 
	    ISVREF(Chain_of_available_java_classs_vector,
	    IFIX(Current_thread_index));
    if (def_structure_java_class_variable) {
	svref_arg_1 = Chain_of_available_java_classs_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_java_class_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_java_class_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_java_class_g2_struct;
    }
    else
	def_structure_java_class_variable = 
		make_permanent_java_class_structure_internal();
    inline_note_allocate_cons(def_structure_java_class_variable,Nil);
    SVREF(def_structure_java_class_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_java_class_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_java_class_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_java_class_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_java_class_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_java_class_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_java_class_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_java_class_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_java_class_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_java_class_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_java_class_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_java_class_variable,FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_java_class_variable,FIX((SI_Long)13L)) = Nil;
    return VALUES_1(def_structure_java_class_variable);
}

Object The_type_description_of_java_descriptor = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_java_descriptors, Qchain_of_available_java_descriptors);

DEFINE_VARIABLE_WITH_SYMBOL(Java_descriptor_count, Qjava_descriptor_count);

Object Chain_of_available_java_descriptors_vector = UNBOUND;

/* JAVA-DESCRIPTOR-STRUCTURE-MEMORY-USAGE */
Object java_descriptor_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(249,55);
    temp = Java_descriptor_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)4L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-JAVA-DESCRIPTOR-COUNT */
Object outstanding_java_descriptor_count()
{
    Object def_structure_java_descriptor_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(249,56);
    gensymed_symbol = IFIX(Java_descriptor_count);
    def_structure_java_descriptor_variable = 
	    Chain_of_available_java_descriptors;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_java_descriptor_variable))
	goto end_loop;
    def_structure_java_descriptor_variable = 
	    ISVREF(def_structure_java_descriptor_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-JAVA-DESCRIPTOR-1 */
Object reclaim_java_descriptor_1(java_descriptor)
    Object java_descriptor;
{
    Object temp, svref_arg_2;

    x_note_fn_call(249,57);
    inline_note_reclaim_cons(java_descriptor,Nil);
    temp = ISVREF(Chain_of_available_java_descriptors_vector,
	    IFIX(Current_thread_index));
    SVREF(java_descriptor,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_java_descriptors_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = java_descriptor;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-JAVA-DESCRIPTOR */
Object reclaim_structure_for_java_descriptor(java_descriptor)
    Object java_descriptor;
{
    x_note_fn_call(249,58);
    return reclaim_java_descriptor_1(java_descriptor);
}

static Object Qg2_defstruct_structure_name_java_descriptor_g2_struct;  /* g2-defstruct-structure-name::java-descriptor-g2-struct */

/* MAKE-PERMANENT-JAVA-DESCRIPTOR-STRUCTURE-INTERNAL */
Object make_permanent_java_descriptor_structure_internal()
{
    Object def_structure_java_descriptor_variable;
    Object defstruct_g2_java_descriptor_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(249,59);
    def_structure_java_descriptor_variable = Nil;
    atomic_incff_symval(Qjava_descriptor_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_java_descriptor_variable = Nil;
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
	defstruct_g2_java_descriptor_variable = the_array;
	SVREF(defstruct_g2_java_descriptor_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_java_descriptor_g2_struct;
	def_structure_java_descriptor_variable = 
		defstruct_g2_java_descriptor_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_java_descriptor_variable);
}

/* MAKE-JAVA-DESCRIPTOR-1 */
Object make_java_descriptor_1()
{
    Object def_structure_java_descriptor_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(249,60);
    def_structure_java_descriptor_variable = 
	    ISVREF(Chain_of_available_java_descriptors_vector,
	    IFIX(Current_thread_index));
    if (def_structure_java_descriptor_variable) {
	svref_arg_1 = Chain_of_available_java_descriptors_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_java_descriptor_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_java_descriptor_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_java_descriptor_g2_struct;
    }
    else
	def_structure_java_descriptor_variable = 
		make_permanent_java_descriptor_structure_internal();
    inline_note_allocate_cons(def_structure_java_descriptor_variable,Nil);
    SVREF(def_structure_java_descriptor_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_java_descriptor_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_java_descriptor_variable,FIX((SI_Long)3L)) = Nil;
    return VALUES_1(def_structure_java_descriptor_variable);
}

Object The_type_description_of_java_field = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_java_fields, Qchain_of_available_java_fields);

DEFINE_VARIABLE_WITH_SYMBOL(Java_field_count, Qjava_field_count);

Object Chain_of_available_java_fields_vector = UNBOUND;

/* JAVA-FIELD-STRUCTURE-MEMORY-USAGE */
Object java_field_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(249,61);
    temp = Java_field_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)8L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-JAVA-FIELD-COUNT */
Object outstanding_java_field_count()
{
    Object def_structure_java_field_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(249,62);
    gensymed_symbol = IFIX(Java_field_count);
    def_structure_java_field_variable = Chain_of_available_java_fields;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_java_field_variable))
	goto end_loop;
    def_structure_java_field_variable = 
	    ISVREF(def_structure_java_field_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-JAVA-FIELD-1 */
Object reclaim_java_field_1(java_field)
    Object java_field;
{
    Object temp, svref_arg_2;

    x_note_fn_call(249,63);
    inline_note_reclaim_cons(java_field,Nil);
    temp = ISVREF(Chain_of_available_java_fields_vector,
	    IFIX(Current_thread_index));
    SVREF(java_field,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_java_fields_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = java_field;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-JAVA-FIELD */
Object reclaim_structure_for_java_field(java_field)
    Object java_field;
{
    x_note_fn_call(249,64);
    return reclaim_java_field_1(java_field);
}

static Object Qg2_defstruct_structure_name_java_field_g2_struct;  /* g2-defstruct-structure-name::java-field-g2-struct */

/* MAKE-PERMANENT-JAVA-FIELD-STRUCTURE-INTERNAL */
Object make_permanent_java_field_structure_internal()
{
    Object def_structure_java_field_variable, defstruct_g2_java_field_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(249,65);
    def_structure_java_field_variable = Nil;
    atomic_incff_symval(Qjava_field_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_java_field_variable = Nil;
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
	defstruct_g2_java_field_variable = the_array;
	SVREF(defstruct_g2_java_field_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_java_field_g2_struct;
	def_structure_java_field_variable = defstruct_g2_java_field_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_java_field_variable);
}

/* MAKE-JAVA-FIELD-1 */
Object make_java_field_1()
{
    Object def_structure_java_field_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(249,66);
    def_structure_java_field_variable = 
	    ISVREF(Chain_of_available_java_fields_vector,
	    IFIX(Current_thread_index));
    if (def_structure_java_field_variable) {
	svref_arg_1 = Chain_of_available_java_fields_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_java_field_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_java_field_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_java_field_g2_struct;
    }
    else
	def_structure_java_field_variable = 
		make_permanent_java_field_structure_internal();
    inline_note_allocate_cons(def_structure_java_field_variable,Nil);
    SVREF(def_structure_java_field_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_java_field_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_java_field_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_java_field_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_java_field_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_java_field_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_java_field_variable,FIX((SI_Long)7L)) = Nil;
    return VALUES_1(def_structure_java_field_variable);
}

Object The_type_description_of_java_method = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_java_methods, Qchain_of_available_java_methods);

DEFINE_VARIABLE_WITH_SYMBOL(Java_method_count, Qjava_method_count);

Object Chain_of_available_java_methods_vector = UNBOUND;

/* JAVA-METHOD-STRUCTURE-MEMORY-USAGE */
Object java_method_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(249,67);
    temp = Java_method_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)10L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-JAVA-METHOD-COUNT */
Object outstanding_java_method_count()
{
    Object def_structure_java_method_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(249,68);
    gensymed_symbol = IFIX(Java_method_count);
    def_structure_java_method_variable = Chain_of_available_java_methods;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_java_method_variable))
	goto end_loop;
    def_structure_java_method_variable = 
	    ISVREF(def_structure_java_method_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-JAVA-METHOD-1 */
Object reclaim_java_method_1(java_method)
    Object java_method;
{
    Object temp, svref_arg_2;

    x_note_fn_call(249,69);
    inline_note_reclaim_cons(java_method,Nil);
    temp = ISVREF(Chain_of_available_java_methods_vector,
	    IFIX(Current_thread_index));
    SVREF(java_method,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_java_methods_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = java_method;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-JAVA-METHOD */
Object reclaim_structure_for_java_method(java_method)
    Object java_method;
{
    x_note_fn_call(249,70);
    return reclaim_java_method_1(java_method);
}

static Object Qg2_defstruct_structure_name_java_method_g2_struct;  /* g2-defstruct-structure-name::java-method-g2-struct */

/* MAKE-PERMANENT-JAVA-METHOD-STRUCTURE-INTERNAL */
Object make_permanent_java_method_structure_internal()
{
    Object def_structure_java_method_variable;
    Object defstruct_g2_java_method_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(249,71);
    def_structure_java_method_variable = Nil;
    atomic_incff_symval(Qjava_method_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_java_method_variable = Nil;
	gensymed_symbol = (SI_Long)10L;
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
	defstruct_g2_java_method_variable = the_array;
	SVREF(defstruct_g2_java_method_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_java_method_g2_struct;
	def_structure_java_method_variable = defstruct_g2_java_method_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_java_method_variable);
}

/* MAKE-JAVA-METHOD-1 */
Object make_java_method_1()
{
    Object def_structure_java_method_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(249,72);
    def_structure_java_method_variable = 
	    ISVREF(Chain_of_available_java_methods_vector,
	    IFIX(Current_thread_index));
    if (def_structure_java_method_variable) {
	svref_arg_1 = Chain_of_available_java_methods_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_java_method_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_java_method_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_java_method_g2_struct;
    }
    else
	def_structure_java_method_variable = 
		make_permanent_java_method_structure_internal();
    inline_note_allocate_cons(def_structure_java_method_variable,Nil);
    SVREF(def_structure_java_method_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_java_method_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_java_method_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_java_method_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_java_method_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_java_method_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_java_method_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_java_method_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_java_method_variable,FIX((SI_Long)9L)) = Nil;
    return VALUES_1(def_structure_java_method_variable);
}

Object The_type_description_of_java_code_exception = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_java_code_exceptions, Qchain_of_available_java_code_exceptions);

DEFINE_VARIABLE_WITH_SYMBOL(Java_code_exception_count, Qjava_code_exception_count);

Object Chain_of_available_java_code_exceptions_vector = UNBOUND;

/* JAVA-CODE-EXCEPTION-STRUCTURE-MEMORY-USAGE */
Object java_code_exception_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(249,73);
    temp = Java_code_exception_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)5L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-JAVA-CODE-EXCEPTION-COUNT */
Object outstanding_java_code_exception_count()
{
    Object def_structure_java_code_exception_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(249,74);
    gensymed_symbol = IFIX(Java_code_exception_count);
    def_structure_java_code_exception_variable = 
	    Chain_of_available_java_code_exceptions;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_java_code_exception_variable))
	goto end_loop;
    def_structure_java_code_exception_variable = 
	    ISVREF(def_structure_java_code_exception_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-JAVA-CODE-EXCEPTION-1 */
Object reclaim_java_code_exception_1(java_code_exception)
    Object java_code_exception;
{
    Object temp, svref_arg_2;

    x_note_fn_call(249,75);
    inline_note_reclaim_cons(java_code_exception,Nil);
    temp = ISVREF(Chain_of_available_java_code_exceptions_vector,
	    IFIX(Current_thread_index));
    SVREF(java_code_exception,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_java_code_exceptions_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = java_code_exception;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-JAVA-CODE-EXCEPTION */
Object reclaim_structure_for_java_code_exception(java_code_exception)
    Object java_code_exception;
{
    x_note_fn_call(249,76);
    return reclaim_java_code_exception_1(java_code_exception);
}

static Object Qg2_defstruct_structure_name_java_code_exception_g2_struct;  /* g2-defstruct-structure-name::java-code-exception-g2-struct */

/* MAKE-PERMANENT-JAVA-CODE-EXCEPTION-STRUCTURE-INTERNAL */
Object make_permanent_java_code_exception_structure_internal()
{
    Object def_structure_java_code_exception_variable;
    Object defstruct_g2_java_code_exception_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(249,77);
    def_structure_java_code_exception_variable = Nil;
    atomic_incff_symval(Qjava_code_exception_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_java_code_exception_variable = Nil;
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
	defstruct_g2_java_code_exception_variable = the_array;
	SVREF(defstruct_g2_java_code_exception_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_java_code_exception_g2_struct;
	def_structure_java_code_exception_variable = 
		defstruct_g2_java_code_exception_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_java_code_exception_variable);
}

/* MAKE-JAVA-CODE-EXCEPTION-1 */
Object make_java_code_exception_1()
{
    Object def_structure_java_code_exception_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(249,78);
    def_structure_java_code_exception_variable = 
	    ISVREF(Chain_of_available_java_code_exceptions_vector,
	    IFIX(Current_thread_index));
    if (def_structure_java_code_exception_variable) {
	svref_arg_1 = Chain_of_available_java_code_exceptions_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_java_code_exception_variable,(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_java_code_exception_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_java_code_exception_g2_struct;
    }
    else
	def_structure_java_code_exception_variable = 
		make_permanent_java_code_exception_structure_internal();
    inline_note_allocate_cons(def_structure_java_code_exception_variable,Nil);
    SVREF(def_structure_java_code_exception_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_java_code_exception_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_java_code_exception_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_java_code_exception_variable,FIX((SI_Long)4L)) = Nil;
    return VALUES_1(def_structure_java_code_exception_variable);
}

Object The_type_description_of_java_code = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_java_codes, Qchain_of_available_java_codes);

DEFINE_VARIABLE_WITH_SYMBOL(Java_code_count, Qjava_code_count);

Object Chain_of_available_java_codes_vector = UNBOUND;

/* JAVA-CODE-STRUCTURE-MEMORY-USAGE */
Object java_code_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(249,79);
    temp = Java_code_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-JAVA-CODE-COUNT */
Object outstanding_java_code_count()
{
    Object def_structure_java_code_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(249,80);
    gensymed_symbol = IFIX(Java_code_count);
    def_structure_java_code_variable = Chain_of_available_java_codes;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_java_code_variable))
	goto end_loop;
    def_structure_java_code_variable = 
	    ISVREF(def_structure_java_code_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-JAVA-CODE-1 */
Object reclaim_java_code_1(java_code)
    Object java_code;
{
    Object temp, svref_arg_2;

    x_note_fn_call(249,81);
    inline_note_reclaim_cons(java_code,Nil);
    temp = ISVREF(Chain_of_available_java_codes_vector,
	    IFIX(Current_thread_index));
    SVREF(java_code,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_java_codes_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = java_code;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-JAVA-CODE */
Object reclaim_structure_for_java_code(java_code)
    Object java_code;
{
    x_note_fn_call(249,82);
    return reclaim_java_code_1(java_code);
}

static Object Qg2_defstruct_structure_name_java_code_g2_struct;  /* g2-defstruct-structure-name::java-code-g2-struct */

/* MAKE-PERMANENT-JAVA-CODE-STRUCTURE-INTERNAL */
Object make_permanent_java_code_structure_internal()
{
    Object def_structure_java_code_variable, defstruct_g2_java_code_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(249,83);
    def_structure_java_code_variable = Nil;
    atomic_incff_symval(Qjava_code_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_java_code_variable = Nil;
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
	defstruct_g2_java_code_variable = the_array;
	SVREF(defstruct_g2_java_code_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_java_code_g2_struct;
	def_structure_java_code_variable = defstruct_g2_java_code_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_java_code_variable);
}

/* MAKE-JAVA-CODE-1 */
Object make_java_code_1()
{
    Object def_structure_java_code_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(249,84);
    def_structure_java_code_variable = 
	    ISVREF(Chain_of_available_java_codes_vector,
	    IFIX(Current_thread_index));
    if (def_structure_java_code_variable) {
	svref_arg_1 = Chain_of_available_java_codes_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_java_code_variable,(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_java_code_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_java_code_g2_struct;
    }
    else
	def_structure_java_code_variable = 
		make_permanent_java_code_structure_internal();
    inline_note_allocate_cons(def_structure_java_code_variable,Nil);
    SVREF(def_structure_java_code_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_java_code_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_java_code_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_java_code_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_java_code_variable,FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_java_code_variable);
}

Object The_type_description_of_class_file_stream = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_class_file_streams, Qchain_of_available_class_file_streams);

DEFINE_VARIABLE_WITH_SYMBOL(Class_file_stream_count, Qclass_file_stream_count);

Object Chain_of_available_class_file_streams_vector = UNBOUND;

/* CLASS-FILE-STREAM-STRUCTURE-MEMORY-USAGE */
Object class_file_stream_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(249,85);
    temp = Class_file_stream_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)3L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-CLASS-FILE-STREAM-COUNT */
Object outstanding_class_file_stream_count()
{
    Object def_structure_class_file_stream_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(249,86);
    gensymed_symbol = IFIX(Class_file_stream_count);
    def_structure_class_file_stream_variable = 
	    Chain_of_available_class_file_streams;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_class_file_stream_variable))
	goto end_loop;
    def_structure_class_file_stream_variable = 
	    ISVREF(def_structure_class_file_stream_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-CLASS-FILE-STREAM-1 */
Object reclaim_class_file_stream_1(class_file_stream)
    Object class_file_stream;
{
    Object temp, svref_arg_2;

    x_note_fn_call(249,87);
    inline_note_reclaim_cons(class_file_stream,Nil);
    temp = ISVREF(Chain_of_available_class_file_streams_vector,
	    IFIX(Current_thread_index));
    SVREF(class_file_stream,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_class_file_streams_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = class_file_stream;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-CLASS-FILE-STREAM */
Object reclaim_structure_for_class_file_stream(class_file_stream)
    Object class_file_stream;
{
    x_note_fn_call(249,88);
    return reclaim_class_file_stream_1(class_file_stream);
}

static Object Qg2_defstruct_structure_name_class_file_stream_g2_struct;  /* g2-defstruct-structure-name::class-file-stream-g2-struct */

/* MAKE-PERMANENT-CLASS-FILE-STREAM-STRUCTURE-INTERNAL */
Object make_permanent_class_file_stream_structure_internal()
{
    Object def_structure_class_file_stream_variable;
    Object defstruct_g2_class_file_stream_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(249,89);
    def_structure_class_file_stream_variable = Nil;
    atomic_incff_symval(Qclass_file_stream_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_class_file_stream_variable = Nil;
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
	defstruct_g2_class_file_stream_variable = the_array;
	SVREF(defstruct_g2_class_file_stream_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_class_file_stream_g2_struct;
	def_structure_class_file_stream_variable = 
		defstruct_g2_class_file_stream_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_class_file_stream_variable);
}

static Object Kjust_opened;        /* :just-opened */

/* MAKE-CLASS-FILE-STREAM-1 */
Object make_class_file_stream_1(class_file_stream_stream)
    Object class_file_stream_stream;
{
    Object def_structure_class_file_stream_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(249,90);
    def_structure_class_file_stream_variable = 
	    ISVREF(Chain_of_available_class_file_streams_vector,
	    IFIX(Current_thread_index));
    if (def_structure_class_file_stream_variable) {
	svref_arg_1 = Chain_of_available_class_file_streams_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_class_file_stream_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_class_file_stream_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_class_file_stream_g2_struct;
    }
    else
	def_structure_class_file_stream_variable = 
		make_permanent_class_file_stream_structure_internal();
    inline_note_allocate_cons(def_structure_class_file_stream_variable,Nil);
    SVREF(def_structure_class_file_stream_variable,FIX((SI_Long)2L)) = 
	    class_file_stream_stream;
    SVREF(def_structure_class_file_stream_variable,FIX((SI_Long)1L)) = 
	    Kjust_opened;
    return VALUES_1(def_structure_class_file_stream_variable);
}

static Object Qunexpected_end_of_file;  /* unexpected-end-of-file */

/* CFS-READ-BYTE */
Object cfs_read_byte(cfs)
    Object cfs;
{
    Object byte_qm;

    x_note_fn_call(249,91);
    byte_qm = read_byte(ISVREF(cfs,(SI_Long)2L),Nil,Nil);
    if ( !TRUEP(byte_qm))
	return error((SI_Long)2L,"class file reading error ~s",
		Qunexpected_end_of_file);
    else
	return VALUES_1(byte_qm);
}

/* CFS-READ-U1 */
Object cfs_read_u1(cfs)
    Object cfs;
{
    x_note_fn_call(249,92);
    return cfs_read_byte(cfs);
}

/* CFS-READ-U2 */
Object cfs_read_u2(cfs)
    Object cfs;
{
    SI_Long temp;

    x_note_fn_call(249,93);
    temp = IFIX(cfs_read_byte(cfs)) << (SI_Long)8L;
    return VALUES_1(FIX(temp + IFIX(cfs_read_byte(cfs))));
}

Object Debug_read_java_class_p = UNBOUND;

static Object list_constant;       /* # */

static Object Qbad_magic_number;   /* bad-magic-number */

/* READ-JAVA-CLASS */
Object read_java_class(filename)
    Object filename;
{
    Object jc, in, cfs, svref_new_value;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(249,94);
    SAVE_STACK();
    jc = make_java_class_1();
    in = lopen(3,filename,Kelement_type,list_constant);
    if (PUSH_UNWIND_PROTECT(0)) {
	cfs = make_class_file_stream_1(in);
	if ( !(IFIX(cfs_read_u2(cfs)) == (SI_Long)51966L && 
		IFIX(cfs_read_u2(cfs)) == (SI_Long)47806L))
	    error((SI_Long)2L,"class file reading error ~s",Qbad_magic_number);
	svref_new_value = cfs_read_u2(cfs);
	SVREF(jc,FIX((SI_Long)2L)) = svref_new_value;
	svref_new_value = cfs_read_u2(cfs);
	SVREF(jc,FIX((SI_Long)3L)) = svref_new_value;
	read_java_class_constant_pool(jc,cfs);
	svref_new_value = cfs_read_u2(cfs);
	SVREF(jc,FIX((SI_Long)6L)) = svref_new_value;
	read_java_class_this_class(jc,cfs);
	read_java_class_super_class(jc,cfs);
	read_java_class_interfaces(jc,cfs);
	read_java_class_fields(jc,cfs);
	read_java_class_methods(jc,cfs);
	SAVE_VALUES(VALUES_1(jc));
    }
    POP_UNWIND_PROTECT(0);
    if (STREAMP(in))
	lclose(1,in);
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object Qpublic;             /* public */

static Object Qprivate;            /* private */

static Object Qprotected;          /* protected */

static Object Qstatic;             /* static */

static Object Qfinal;              /* final */

static Object Qsynchronized;       /* synchronized */

static Object Qvolatile;           /* volatile */

static Object Qtransient;          /* transient */

static Object Qnative;             /* native */

static Object Qabstract;           /* abstract */

/* JAVA-MODIFIER-P */
Object java_modifier_p(thing,modifier)
    Object thing, modifier;
{
    Object flags, flag, temp;

    x_note_fn_call(249,95);
    if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
	    Qg2_defstruct_structure_name_java_class_g2_struct))
	flags = ISVREF(thing,(SI_Long)6L);
    else if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
	    Qg2_defstruct_structure_name_java_method_g2_struct))
	flags = ISVREF(thing,(SI_Long)1L);
    else if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
	    Qg2_defstruct_structure_name_java_field_g2_struct))
	flags = ISVREF(thing,(SI_Long)1L);
    else
	flags = error((SI_Long)2L,"~s is not a class, or method",thing);
    if (EQ(modifier,Qpublic))
	flag = Java_access_flag_public;
    else if (EQ(modifier,Qprivate))
	flag = Java_access_flag_private;
    else if (EQ(modifier,Qprotected))
	flag = Java_access_flag_protected;
    else if (EQ(modifier,Qstatic))
	flag = Java_access_flag_static;
    else if (EQ(modifier,Qfinal))
	flag = Java_access_flag_final;
    else if (EQ(modifier,Qsynchronized))
	flag = Java_access_flag_synchronized;
    else if (EQ(modifier,Qvolatile))
	flag = Java_access_flag_volatile;
    else if (EQ(modifier,Qtransient))
	flag = Java_access_flag_transient;
    else if (EQ(modifier,Qnative))
	flag = Java_access_flag_native;
    else if (EQ(modifier,Qinterface))
	flag = Java_access_flag_interface;
    else if (EQ(modifier,Qabstract))
	flag = Java_access_flag_abstract;
    else
	flag = error((SI_Long)2L,"unknown modifier ~s",modifier);
    temp = IFIX(FIXNUM_LOGAND(flag,flags)) != (SI_Long)0L ? T : Nil;
    return VALUES_1(temp);
}

static Object Qlong;               /* long */

static Object Qdouble;             /* double */

/* READ-JAVA-CLASS-CONSTANT-POOL */
Object read_java_class_constant_pool(java_class,class_file_stream)
    Object java_class, class_file_stream;
{
    Object constant_count, constant_vector, i, constant;
    SI_Long i_new_value;

    x_note_fn_call(249,96);
    constant_count = cfs_read_u2(class_file_stream);
    constant_vector = allocate_managed_simple_vector(constant_count);
    format((SI_Long)3L,T,"constant pool count =~S~%",constant_count);
    i = FIX((SI_Long)1L);
    constant = Nil;
  next_loop:
    if ( !FIXNUM_LT(i,constant_count))
	goto end_loop;
    constant = read_java_class_constant(class_file_stream);
    SVREF(constant_vector,i) = constant;
    if (Debug_read_java_class_p)
	format((SI_Long)4L,T,"Const i=~s is ~s~%",i,ISVREF(constant_vector,
		IFIX(i)));
    if (CONSP(constant) && (EQ(M_CAR(constant),Qlong) || 
	    EQ(M_CAR(constant),Qdouble))) {
	i_new_value = IFIX(i) + (SI_Long)2L;
	i = FIX(i_new_value);
    }
    else
	i = FIXNUM_ADD1(i);
    goto next_loop;
  end_loop:;
    return VALUES_1(SVREF(java_class,FIX((SI_Long)5L)) = constant_vector);
}

static Object Qunknown_constant_tag;  /* unknown-constant-tag */

static Object Qab_class;           /* class */

static Object Qfieldref;           /* fieldref */

static Object Qmethodref;          /* methodref */

static Object Qinterfacemethoddref;  /* interfacemethoddref */

static Object Qnameandtype;        /* nameandtype */

/* READ-JAVA-CLASS-CONSTANT */
Object read_java_class_constant(cfs)
    Object cfs;
{
    Object tag, temp, gensymed_symbol, gensymed_symbol_1, car_new_value;

    x_note_fn_call(249,97);
    tag = cfs_read_u1(cfs);
    if (Debug_read_java_class_p)
	format((SI_Long)3L,T,"tag=~s~%",tag);
    if ( !((SI_Long)1L <= IFIX(tag) && IFIX(tag) <= (SI_Long)12L))
	error((SI_Long)2L,"class file reading error ~s",Qunknown_constant_tag);
    temp = tag;
    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)127L))))
	return VALUES_1(Nil);
    else
	switch (INTEGER_TO_CHAR(temp)) {
	  case 7:
	    return java_list_2(Qab_class,cfs_read_u2(cfs));
	  case 9:
	    temp = cfs_read_u2(cfs);
	    return java_list_3(Qfieldref,temp,cfs_read_u2(cfs));
	  case 10:
	    temp = cfs_read_u2(cfs);
	    return java_list_3(Qmethodref,temp,cfs_read_u2(cfs));
	  case 11:
	    temp = cfs_read_u2(cfs);
	    return java_list_3(Qinterfacemethoddref,temp,cfs_read_u2(cfs));
	  case 8:
	    if (Debug_read_java_class_p)
		format((SI_Long)2L,T,"in the string case~%");
	    return java_list_2(Qstring,cfs_read_u2(cfs));
	  case 3:
	    temp = cfs_read_u2(cfs);
	    return java_list_3(Qinteger,temp,cfs_read_u2(cfs));
	  case 4:
	    temp = cfs_read_u2(cfs);
	    return java_list_3(Qinteger,temp,cfs_read_u2(cfs));
	  case 5:
	    gensymed_symbol = make_java_list_1(FIX((SI_Long)5L));
	    gensymed_symbol_1 = gensymed_symbol;
	    M_CAR(gensymed_symbol_1) = Qlong;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    car_new_value = cfs_read_u2(cfs);
	    M_CAR(gensymed_symbol_1) = car_new_value;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    car_new_value = cfs_read_u2(cfs);
	    M_CAR(gensymed_symbol_1) = car_new_value;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    car_new_value = cfs_read_u2(cfs);
	    M_CAR(gensymed_symbol_1) = car_new_value;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    car_new_value = cfs_read_u2(cfs);
	    M_CAR(gensymed_symbol_1) = car_new_value;
	    return VALUES_1(gensymed_symbol);
	  case 6:
	    gensymed_symbol = make_java_list_1(FIX((SI_Long)5L));
	    gensymed_symbol_1 = gensymed_symbol;
	    M_CAR(gensymed_symbol_1) = Qdouble;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    car_new_value = cfs_read_u2(cfs);
	    M_CAR(gensymed_symbol_1) = car_new_value;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    car_new_value = cfs_read_u2(cfs);
	    M_CAR(gensymed_symbol_1) = car_new_value;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    car_new_value = cfs_read_u2(cfs);
	    M_CAR(gensymed_symbol_1) = car_new_value;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    car_new_value = cfs_read_u2(cfs);
	    M_CAR(gensymed_symbol_1) = car_new_value;
	    return VALUES_1(gensymed_symbol);
	  case 12:
	    temp = cfs_read_u2(cfs);
	    return java_list_3(Qnameandtype,temp,cfs_read_u2(cfs));
	  case 1:
	    return read_java_utf8_string(cfs);
	  case 2:
	    return error((SI_Long)1L,"Joe didn\'t expect this");
	  default:
	    return VALUES_1(Nil);
	}
}

static Object Qbad_null_char;      /* bad-null-char */

static Object Qill_formed_utf8;    /* ill-formed-utf8 */

/* READ-JAVA-UTF8-STRING */
Object read_java_utf8_string(cfs)
    Object cfs;
{
    Object length_1, wide_string_bv16, stringw_1, i, unicode, byte_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, gensymed_symbol;
    SI_Long high_3_bits, temp;

    x_note_fn_call(249,98);
    length_1 = cfs_read_u2(cfs);
    wide_string_bv16 = allocate_byte_vector_16(FIX(IFIX(length_1) + 
	    (SI_Long)3L));
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
    aref_arg_2 = bv16_length - (SI_Long)2L;
    aref_new_value = IFIX(length_1) & (SI_Long)65535L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    aref_arg_2 = bv16_length - (SI_Long)1L;
    aref_new_value = (SI_Long)57344L | IFIX(length_1) >>  -  - (SI_Long)16L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    UBYTE_16_ISASET_1(wide_string_bv16,IFIX(length_1),(SI_Long)0L);
    stringw_1 = wide_string_bv16;
    i = FIX((SI_Long)0L);
    unicode = FIX((SI_Long)0L);
    byte_1 = Nil;
  next_loop:
    if ( !FIXNUM_LT(i,length_1))
	goto end_loop;
    byte_1 = cfs_read_u1(cfs);
    gensymed_symbol = IFIX(byte_1) & (SI_Long)128L;
    if (gensymed_symbol == (SI_Long)0L) {
	if ((SI_Long)0L == IFIX(byte_1))
	    error((SI_Long)2L,"class file reading error ~s",Qbad_null_char);
	unicode = byte_1;
    }
    else {
	high_3_bits = IFIX(byte_1) >>  -  - (SI_Long)5L;
	if (high_3_bits == (SI_Long)6L) {
	    temp = (IFIX(byte_1) & (SI_Long)31L) << (SI_Long)6L;
	    unicode = FIX(temp + (IFIX(cfs_read_u1(cfs)) & (SI_Long)63L));
	}
	else if (high_3_bits == (SI_Long)7L) {
	    temp = (IFIX(byte_1) & (SI_Long)15L) << (SI_Long)12L;
	    temp = temp + ((IFIX(cfs_read_u1(cfs)) & (SI_Long)63L) << 
		    (SI_Long)6L);
	    unicode = FIX(temp + (IFIX(cfs_read_u1(cfs)) & (SI_Long)63L));
	}
	else
	    error((SI_Long)2L,"class file reading error ~s",Qill_formed_utf8);
    }
    UBYTE_16_ISASET_1(stringw_1,IFIX(i),IFIX(unicode));
    i = FIXNUM_ADD1(i);
    goto next_loop;
  end_loop:;
    return VALUES_1(stringw_1);
}

/* GET-VALID-CONSTANT-POOL-ENTRY? */
Object get_valid_constant_pool_entry_qm(jc,index_1)
    Object jc, index_1;
{
    Object constant_pool, length_1;

    x_note_fn_call(249,99);
    constant_pool = ISVREF(jc,(SI_Long)5L);
    length_1 = SIMPLE_ARRAY_ANY_1_LENGTH(constant_pool);
    if ((SI_Long)0L < IFIX(index_1) && FIXNUM_LT(index_1,length_1))
	return VALUES_1(ISVREF(constant_pool,IFIX(index_1)));
    else
	return VALUES_1(Nil);
}

static Object Qutf8;               /* utf8 */

/* JAVA-CONSTANT-TYPE-P */
Object java_constant_type_p(constant,type)
    Object constant, type;
{
    x_note_fn_call(249,100);
    if (CONSP(constant))
	return VALUES_1(EQ(M_CAR(constant),type) ? T : Nil);
    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(constant) != (SI_Long)0L)
	return VALUES_1(EQ(type,Qutf8) ? T : Nil);
    else
	return error((SI_Long)1L,"um, uh");
}

static Object Qthis_class_index_out_of_range;  /* this-class-index-out-of-range */

static Object Qbad_this_class_constant;  /* bad-this-class-constant */

/* READ-JAVA-CLASS-THIS-CLASS */
Object read_java_class_this_class(jc,cfs)
    Object jc, cfs;
{
    Object index_1, constant_qm;

    x_note_fn_call(249,101);
    index_1 = cfs_read_u2(cfs);
    constant_qm = get_valid_constant_pool_entry_qm(jc,index_1);
    if ( !TRUEP(constant_qm))
	return error((SI_Long)2L,"class file reading error ~s",
		Qthis_class_index_out_of_range);
    else if (java_constant_type_p(constant_qm,Qab_class))
	return VALUES_1(SVREF(jc,FIX((SI_Long)7L)) = index_1);
    else
	return error((SI_Long)2L,"class file reading error ~s",
		Qbad_this_class_constant);
}

static Object Qredefining_java_dot_lang_dot_object_not;  /* redefining-java.lang.object-not */

static Object Qbad_super_class_index;  /* bad-super-class-index */

static Object Qbad_super_class_constant;  /* bad-super-class-constant */

/* READ-JAVA-CLASS-SUPER-CLASS */
Object read_java_class_super_class(jc,cfs)
    Object jc, cfs;
{
    Object index_1, constant_qm;

    x_note_fn_call(249,102);
    index_1 = cfs_read_u2(cfs);
    constant_qm = Nil;
    if (IFIX(index_1) == (SI_Long)0L)
	error((SI_Long)2L,"class file reading error ~s",
		Qredefining_java_dot_lang_dot_object_not);
    else
	constant_qm = get_valid_constant_pool_entry_qm(jc,index_1);
    if ( !TRUEP(constant_qm))
	return error((SI_Long)2L,"class file reading error ~s",
		Qbad_super_class_index);
    else if (java_constant_type_p(constant_qm,Qab_class))
	return VALUES_1(SVREF(jc,FIX((SI_Long)8L)) = index_1);
    else
	return error((SI_Long)2L,"class file reading error ~s",
		Qbad_super_class_constant);
}

static Object Qsuperinterface_is_not_class_constant;  /* superinterface-is-not-class-constant */

static Object Qinterface_index_out_of_range;  /* interface-index-out-of-range */

/* READ-JAVA-CLASS-INTERFACES */
Object read_java_class_interfaces(jc,cfs)
    Object jc, cfs;
{
    Object count_1, interfaces, index_1, constant_qm;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(249,103);
    count_1 = cfs_read_u2(cfs);
    interfaces = IFIX(count_1) > (SI_Long)0L ? 
	    allocate_managed_simple_vector(count_1) : Qnil;
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(count_1);
    index_1 = Nil;
    constant_qm = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    index_1 = cfs_read_u2(cfs);
    constant_qm = get_valid_constant_pool_entry_qm(jc,index_1);
    if (constant_qm && java_constant_type_p(constant_qm,Qab_class))
	ISVREF(interfaces,i) = index_1;
    else if (constant_qm)
	error((SI_Long)2L,"class file reading error ~s",
		Qsuperinterface_is_not_class_constant);
    else
	error((SI_Long)2L,"class file reading error ~s",
		Qinterface_index_out_of_range);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(SVREF(jc,FIX((SI_Long)9L)) = interfaces);
}

static Object Qfield;              /* field */

/* READ-JAVA-CLASS-FIELDS */
Object read_java_class_fields(jc,cfs)
    Object jc, cfs;
{
    Object count_1, fields, field, svref_new_value, temp, temp_1, temp_2;
    Object attributes, attribute;
    SI_Long i, ab_loop_bind_, i_1, ab_loop_bind__1;

    x_note_fn_call(249,104);
    count_1 = cfs_read_u2(cfs);
    fields = IFIX(count_1) > (SI_Long)0L ? 
	    allocate_managed_simple_vector(count_1) : Qnil;
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(count_1);
    field = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    field = make_java_field_1();
    svref_new_value = cfs_read_u2(cfs);
    SVREF(field,FIX((SI_Long)1L)) = svref_new_value;
    svref_new_value = cfs_read_u2(cfs);
    SVREF(field,FIX((SI_Long)2L)) = svref_new_value;
    svref_new_value = cfs_read_u2(cfs);
    SVREF(field,FIX((SI_Long)3L)) = svref_new_value;
    svref_new_value = read_java_attributes(jc,cfs,Qfield);
    SVREF(field,FIX((SI_Long)4L)) = svref_new_value;
    svref_new_value = 
	    get_next_type_from_java_descriptor(get_valid_constant_pool_entry_qm(jc,
	    ISVREF(field,(SI_Long)3L)),FIX((SI_Long)0L));
    SVREF(field,FIX((SI_Long)5L)) = svref_new_value;
    svref_new_value = 
	    java_name_string_gt_ab_symbol(get_valid_constant_pool_entry_qm(jc,
	    ISVREF(field,(SI_Long)2L)));
    SVREF(field,FIX((SI_Long)6L)) = svref_new_value;
    temp = get_valid_constant_pool_entry_qm(jc,ISVREF(field,(SI_Long)2L));
    temp_1 = ISVREF(field,(SI_Long)1L);
    temp_2 = get_valid_constant_pool_entry_qm(jc,ISVREF(field,(SI_Long)3L));
    format((SI_Long)6L,T,
	    "Field: ~s ~30T(flags=#x~4,\'0x) ~50Ttype=~s ~70T#attrs=~s~%",
	    temp,temp_1,temp_2, !TRUEP(ISVREF(field,(SI_Long)4L)) ? 
	    FIX((SI_Long)0L) : length(ISVREF(field,(SI_Long)4L)));
    if (ISVREF(field,(SI_Long)4L)) {
	attributes = ISVREF(field,(SI_Long)4L);
	i_1 = (SI_Long)0L;
	ab_loop_bind__1 = IFIX(length(attributes));
	attribute = Nil;
      next_loop_1:
	if (i_1 >= ab_loop_bind__1)
	    goto end_loop_1;
	attribute = ISVREF(attributes,i_1);
	format((SI_Long)4L,T,"  Attr ~s: ~s~%",FIX(i_1),attribute);
	i_1 = i_1 + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
    }
    ISVREF(fields,i) = field;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(SVREF(jc,FIX((SI_Long)10L)) = fields);
}

static Object Qab_method;          /* method */

/* READ-JAVA-CLASS-METHODS */
Object read_java_class_methods(jc,cfs)
    Object jc, cfs;
{
    Object count_1, methods, method, svref_new_value, argument_types;
    Object return_type_qm, temp, temp_1, temp_2, attributes, attribute;
    SI_Long i, ab_loop_bind_, i_1, ab_loop_bind__1;
    Object result;

    x_note_fn_call(249,105);
    count_1 = cfs_read_u2(cfs);
    methods = IFIX(count_1) > (SI_Long)0L ? 
	    allocate_managed_simple_vector(count_1) : Qnil;
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(count_1);
    method = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    method = make_java_method_1();
    svref_new_value = cfs_read_u2(cfs);
    SVREF(method,FIX((SI_Long)1L)) = svref_new_value;
    svref_new_value = cfs_read_u2(cfs);
    SVREF(method,FIX((SI_Long)2L)) = svref_new_value;
    svref_new_value = cfs_read_u2(cfs);
    SVREF(method,FIX((SI_Long)3L)) = svref_new_value;
    svref_new_value = read_java_attributes(jc,cfs,Qab_method);
    SVREF(method,FIX((SI_Long)4L)) = svref_new_value;
    svref_new_value = 
	    java_name_string_gt_ab_symbol(get_valid_constant_pool_entry_qm(jc,
	    ISVREF(method,(SI_Long)2L)));
    SVREF(method,FIX((SI_Long)8L)) = svref_new_value;
    result = get_prototype_from_java_descriptor(get_valid_constant_pool_entry_qm(jc,
	    ISVREF(method,(SI_Long)3L)));
    MVS_2(result,argument_types,return_type_qm);
    SVREF(method,FIX((SI_Long)6L)) = argument_types;
    SVREF(method,FIX((SI_Long)7L)) = return_type_qm;
    temp = get_valid_constant_pool_entry_qm(jc,ISVREF(method,(SI_Long)2L));
    temp_1 = ISVREF(method,(SI_Long)1L);
    temp_2 = get_valid_constant_pool_entry_qm(jc,ISVREF(method,(SI_Long)3L));
    format((SI_Long)6L,T,
	    "Method: ~s ~30T(flags=#x~4,\'0x) ~50Ttype=~s ~70T#attrs=~s~%",
	    temp,temp_1,temp_2, !TRUEP(ISVREF(method,(SI_Long)4L)) ? 
	    FIX((SI_Long)0L) : length(ISVREF(method,(SI_Long)4L)));
    if (ISVREF(method,(SI_Long)4L)) {
	attributes = ISVREF(method,(SI_Long)4L);
	i_1 = (SI_Long)0L;
	ab_loop_bind__1 = IFIX(length(attributes));
	attribute = Nil;
      next_loop_1:
	if (i_1 >= ab_loop_bind__1)
	    goto end_loop_1;
	attribute = ISVREF(attributes,i_1);
	format((SI_Long)4L,T,"  Attr ~s: ~s~%",FIX(i_1),attribute);
	i_1 = i_1 + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
    }
    ISVREF(methods,i) = method;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(SVREF(jc,FIX((SI_Long)11L)) = methods);
}

static Object Qattribute_name_not_utf8;  /* attribute-name-not-utf8 */

static Object Qattribute_name_index_out_of_range;  /* attribute-name-index-out-of-range */

static Object Qattribute_data_length_must_be_less_than_16777216;  /* attribute-data-length-must-be-less-than-16777216 */

static Object array_constant_8;    /* # */

static Object Qsource_file;        /* source-file */

static Object Qbad_source_file_attribute;  /* bad-source-file-attribute */

static Object array_constant_9;    /* # */

static Object Qab_constant_value;  /* constant-value */

static Object Qbad_constant_value_attribute;  /* bad-constant-value-attribute */

static Object array_constant_10;   /* # */

static Object array_constant_11;   /* # */

static Object array_constant_12;   /* # */

static Object array_constant_13;   /* # */

/* READ-JAVA-ATTRIBUTES */
Object read_java_attributes(jc,cfs,owner_type)
    Object jc, cfs, owner_type;
{
    Object count_1, attributes, attribute_name, attribute_length;
    Object attribute_name_index, attribute_name_constant_qm;
    Object attribute_length_high, attribute_length_low, attribute;
    Object source_file_index, source_file_constant_qm, constant_value_index;
    Object constant_value_constant_qm;
    SI_Long i, ab_loop_bind_, i_1, ab_loop_bind__1;

    x_note_fn_call(249,106);
    count_1 = cfs_read_u2(cfs);
    attributes = IFIX(count_1) > (SI_Long)0L ? 
	    allocate_managed_simple_vector(count_1) : Nil;
    attribute_name = Nil;
    attribute_length = FIX((SI_Long)0L);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(count_1);
    attribute_name_index = Nil;
    attribute_name_constant_qm = Nil;
    attribute_length_high = Nil;
    attribute_length_low = Nil;
    attribute = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    attribute_name_index = cfs_read_u2(cfs);
    attribute_name_constant_qm = get_valid_constant_pool_entry_qm(jc,
	    attribute_name_index);
    attribute_length_high = cfs_read_u2(cfs);
    attribute_length_low = cfs_read_u2(cfs);
    attribute = Nil;
    if (attribute_name_constant_qm && 
	    java_constant_type_p(attribute_name_constant_qm,Qutf8))
	attribute_name = attribute_name_constant_qm;
    else if (attribute_name_constant_qm)
	error((SI_Long)2L,"class file reading error ~s",
		Qattribute_name_not_utf8);
    else
	error((SI_Long)2L,"class file reading error ~s",
		Qattribute_name_index_out_of_range);
    if (IFIX(attribute_length_high) >>  -  - (SI_Long)8L == (SI_Long)0L)
	attribute_length = FIX((IFIX(attribute_length_high) << 
		(SI_Long)16L) + IFIX(attribute_length_low));
    else
	error((SI_Long)2L,"class file reading error ~s",
		Qattribute_data_length_must_be_less_than_16777216);
    if (string_eq_w(attribute_name,array_constant_8)) {
	source_file_index = cfs_read_u2(cfs);
	source_file_constant_qm = get_valid_constant_pool_entry_qm(jc,
		source_file_index);
	if (source_file_constant_qm && 
		java_constant_type_p(source_file_constant_qm,Qutf8))
	    attribute = java_list_2(Qsource_file,source_file_constant_qm);
	else
	    error((SI_Long)2L,"class file reading error ~s",
		    Qbad_source_file_attribute);
    }
    else if (string_eq_w(attribute_name,array_constant_9)) {
	constant_value_index = cfs_read_u2(cfs);
	constant_value_constant_qm = get_valid_constant_pool_entry_qm(jc,
		constant_value_index);
	if (constant_value_constant_qm && 
		(java_constant_type_p(constant_value_constant_qm,Qlong) || 
		java_constant_type_p(constant_value_constant_qm,Qfloat) || 
		java_constant_type_p(constant_value_constant_qm,Qdouble) 
		|| java_constant_type_p(constant_value_constant_qm,Qinteger)))
	    attribute = java_list_2(Qab_constant_value,
		    constant_value_constant_qm);
	else
	    error((SI_Long)2L,"class file reading error ~s",
		    Qbad_constant_value_attribute);
    }
    else if (string_eq_w(attribute_name,array_constant_10))
	attribute = java_list_2(Qcode,read_java_code(jc,cfs,owner_type));
    else if (string_eq_w(attribute_name,array_constant_11)) {
	i_1 = (SI_Long)0L;
	ab_loop_bind__1 = IFIX(attribute_length);
      next_loop_1:
	if (i_1 >= ab_loop_bind__1)
	    goto end_loop_1;
	cfs_read_u1(cfs);
	i_1 = i_1 + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
    }
    else if (string_eq_w(attribute_name,array_constant_12)) {
	i_1 = (SI_Long)0L;
	ab_loop_bind__1 = IFIX(attribute_length);
      next_loop_2:
	if (i_1 >= ab_loop_bind__1)
	    goto end_loop_2;
	cfs_read_u1(cfs);
	i_1 = i_1 + (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:;
    }
    else if (string_eq_w(attribute_name,array_constant_13)) {
	i_1 = (SI_Long)0L;
	ab_loop_bind__1 = IFIX(attribute_length);
      next_loop_3:
	if (i_1 >= ab_loop_bind__1)
	    goto end_loop_3;
	cfs_read_u1(cfs);
	i_1 = i_1 + (SI_Long)1L;
	goto next_loop_3;
      end_loop_3:;
    }
    else {
	format((SI_Long)3L,T,"UNKNOWN ATTR ~s , skipping~%",attribute_name);
	i_1 = (SI_Long)0L;
	ab_loop_bind__1 = IFIX(attribute_length);
      next_loop_4:
	if (i_1 >= ab_loop_bind__1)
	    goto end_loop_4;
	cfs_read_u1(cfs);
	i_1 = i_1 + (SI_Long)1L;
	goto next_loop_4;
      end_loop_4:;
    }
    ISVREF(attributes,i) = attribute;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(attributes);
    return VALUES_1(Qnil);
}

static Object Qbytecode_vectors_must_be_less_than_16777216;  /* bytecode-vectors-must-be-less-than-16777216 */

static Object Qend_pc_out_of_range;  /* end-pc-out-of-range */

static Object Qstart_pc_out_of_range;  /* start-pc-out-of-range */

static Object Qhandler_pc_out_of_range;  /* handler-pc-out-of-range */

static Object Qbad_exception_table_class;  /* bad-exception-table-class */

/* READ-JAVA-CODE */
Object read_java_code(jc,cfs,owner_type)
    Object jc, cfs, owner_type;
{
    Object code, bytecode_count, temp, bytecode_count_high, bytecode_count_low;
    Object bytecode_vector, exception_table_length, exception_table, exception;
    Object start_pc, end_pc, handler_pc, catch_type_index, constant_qm;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;

    x_note_fn_call(249,107);
    code = make_java_code_1();
    bytecode_count = Nil;
    temp = cfs_read_u2(cfs);
    SVREF(code,FIX((SI_Long)1L)) = temp;
    temp = cfs_read_u2(cfs);
    SVREF(code,FIX((SI_Long)2L)) = temp;
    bytecode_count_high = cfs_read_u2(cfs);
    bytecode_count_low = cfs_read_u2(cfs);
    if (IFIX(bytecode_count_high) >>  -  - (SI_Long)8L == (SI_Long)0L) {
	gensymed_symbol = IFIX(bytecode_count_high) & (SI_Long)255L;
	gensymed_symbol_1 = (SI_Long)16L;
	gensymed_symbol_1 = gensymed_symbol << gensymed_symbol_1;
	gensymed_symbol = IFIX(bytecode_count_low);
	bytecode_count = FIX(gensymed_symbol_1 + gensymed_symbol);
	bytecode_vector = allocate_byte_vector(bytecode_count);
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(bytecode_count);
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	temp = cfs_read_u1(cfs);
	UBYTE_8_ISASET_1(bytecode_vector,i,IFIX(temp));
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	SVREF(code,FIX((SI_Long)3L)) = bytecode_vector;
    }
    else
	error((SI_Long)2L,"class file reading error ~s",
		Qbytecode_vectors_must_be_less_than_16777216);
    exception_table_length = cfs_read_u2(cfs);
    exception_table = IFIX(exception_table_length) > (SI_Long)0L ? 
	    allocate_managed_simple_vector(exception_table_length) : Qnil;
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(exception_table_length);
    exception = Nil;
    start_pc = Nil;
    end_pc = Nil;
    handler_pc = Nil;
    catch_type_index = Nil;
  next_loop_1:
    if (i >= ab_loop_bind_)
	goto end_loop_1;
    exception = make_java_code_exception_1();
    start_pc = cfs_read_u2(cfs);
    end_pc = cfs_read_u2(cfs);
    handler_pc = cfs_read_u2(cfs);
    catch_type_index = cfs_read_u2(cfs);
    if ( !((SI_Long)-1L < IFIX(end_pc) && FIXNUM_LT(end_pc,bytecode_count)))
	error((SI_Long)2L,"class file reading error ~s",Qend_pc_out_of_range);
    if ( !((SI_Long)-1L < IFIX(start_pc) && FIXNUM_LT(start_pc,end_pc)))
	error((SI_Long)2L,"class file reading error ~s",
		Qstart_pc_out_of_range);
    if ( !((SI_Long)-1L < IFIX(handler_pc) && FIXNUM_LT(handler_pc,
	    bytecode_count)))
	error((SI_Long)2L,"class file reading error ~s",
		Qhandler_pc_out_of_range);
    constant_qm = get_valid_constant_pool_entry_qm(jc,catch_type_index);
    if ( !(constant_qm && java_constant_type_p(constant_qm,Qab_class)))
	error((SI_Long)2L,"class file reading error ~s",
		Qbad_exception_table_class);
    SVREF(exception,FIX((SI_Long)1L)) = start_pc;
    SVREF(exception,FIX((SI_Long)2L)) = end_pc;
    SVREF(exception,FIX((SI_Long)3L)) = handler_pc;
    SVREF(exception,FIX((SI_Long)4L)) = catch_type_index;
    ISVREF(exception_table,i) = exception;
    i = i + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    SVREF(code,FIX((SI_Long)4L)) = exception_table;
    temp = read_java_attributes(jc,cfs,Qcode);
    SVREF(code,FIX((SI_Long)5L)) = temp;
    return VALUES_1(code);
}

/* GET-PROTOTYPE-FROM-JAVA-DESCRIPTOR */
Object get_prototype_from_java_descriptor(descriptor)
    Object descriptor;
{
    Object argument_types, last_position, temp;
    SI_Long ch;
    Object result;

    x_note_fn_call(249,108);
    result = get_argument_types_from_java_descriptor(descriptor);
    MVS_2(result,argument_types,last_position);
    ch = UBYTE_16_ISAREF_1(descriptor,IFIX(last_position));
    if (ch == (SI_Long)86L)
	return VALUES_2(argument_types,Nil);
    else {
	temp = get_next_type_from_java_descriptor(descriptor,last_position);
	return VALUES_2(argument_types,temp);
    }
}

/* GET-ARGUMENT-TYPES-FROM-JAVA-DESCRIPTOR */
Object get_argument_types_from_java_descriptor(descriptor)
    Object descriptor;
{
    Object argument_types, i, ch, temp, temp_1, type, new_i;
    Object result;

    x_note_fn_call(249,109);
    argument_types = Qnil;
    i = FIX((SI_Long)1L);
    ch = Nil;
  next_loop:
    ch = FIX(UBYTE_16_ISAREF_1(descriptor,IFIX(i)));
    if (IFIX(ch) == (SI_Long)41L) {
	temp = nreverse(argument_types);
	temp_1 = FIXNUM_ADD1(i);
	return VALUES_2(temp,temp_1);
    }
    else {
	result = get_next_type_from_java_descriptor(descriptor,i);
	MVS_2(result,type,new_i);
	argument_types = java_cons_1(type,argument_types);
	i = new_i;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qint;                /* int */

static Object Qshort;              /* short */

static Object Qboolean;            /* boolean */

/* GET-NEXT-TYPE-FROM-JAVA-DESCRIPTOR */
Object get_next_type_from_java_descriptor(descriptor,position_1)
    Object descriptor, position_1;
{
    Object temp_1, sub_type, next_position;
    SI_Long temp;
    Object result;

    x_note_fn_call(249,110);
    temp = UBYTE_16_ISAREF_1(descriptor,IFIX(position_1));
    if ( !((SI_Long)-128L <= temp && temp <= (SI_Long)127L))
	return VALUES_1(Nil);
    else
	switch ((char)temp) {
	  case 66:
	    temp_1 = FIXNUM_ADD1(position_1);
	    return VALUES_2(Qbyte,temp_1);
	  case 67:
	    temp_1 = FIXNUM_ADD1(position_1);
	    return VALUES_2(Qchar,temp_1);
	  case 68:
	    temp_1 = FIXNUM_ADD1(position_1);
	    return VALUES_2(Qdouble,temp_1);
	  case 70:
	    temp_1 = FIXNUM_ADD1(position_1);
	    return VALUES_2(Qfloat,temp_1);
	  case 73:
	    temp_1 = FIXNUM_ADD1(position_1);
	    return VALUES_2(Qint,temp_1);
	  case 74:
	    temp_1 = FIXNUM_ADD1(position_1);
	    return VALUES_2(Qlong,temp_1);
	  case 83:
	    temp_1 = FIXNUM_ADD1(position_1);
	    return VALUES_2(Qshort,temp_1);
	  case 90:
	    temp_1 = FIXNUM_ADD1(position_1);
	    return VALUES_2(Qboolean,temp_1);
	  case 76:
	    return get_java_class_from_descriptor(descriptor,position_1);
	  case 91:
	    result = get_next_type_from_java_descriptor(descriptor,
		    FIXNUM_ADD1(position_1));
	    MVS_2(result,sub_type,next_position);
	    temp_1 = java_list_2(Qarray,sub_type);
	    return VALUES_2(temp_1,next_position);
	  default:
	    return VALUES_1(Nil);
	}
}

/* GET-JAVA-CLASS-FROM-DESCRIPTOR */
Object get_java_class_from_descriptor(descriptor,position_1)
    Object descriptor, position_1;
{
    Object last_start, path, ch, temp;
    SI_Long i;

    x_note_fn_call(249,111);
    last_start = Nil;
    path = Qnil;
    i = IFIX(FIXNUM_ADD1(position_1));
    ch = Nil;
  next_loop:
    ch = FIX(UBYTE_16_ISAREF_1(descriptor,i));
    if (IFIX(ch) == (SI_Long)47L || IFIX(ch) == (SI_Long)59L) {
	temp = text_string_substring(descriptor,last_start,FIX(i));
	path = java_cons_1(temp,path);
	last_start = Nil;
	if (IFIX(ch) == (SI_Long)59L) {
	    temp = nreverse(path);
	    return VALUES_2(temp,FIX(i + (SI_Long)1L));
	}
    }
    else if ( !TRUEP(last_start))
	last_start = FIX(i);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* JAVA-NAME-STRING->AB-SYMBOL */
Object java_name_string_gt_ab_symbol(string_1)
    Object string_1;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object ch, temp, schar_arg_2, schar_new_value, gensymed_symbol, thing_1;
    Object code, simple_or_wide_character, temp_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, i;
    SI_Long ab_loop_bind_;
    char thing;
    Declare_special(5);

    x_note_fn_call(249,112);
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
	      i = (SI_Long)0L;
	      ab_loop_bind_ = IFIX(text_string_length(string_1));
	      ch = Nil;
	    next_loop:
	      if (i >= ab_loop_bind_)
		  goto end_loop;
	      ch = FIX(UBYTE_16_ISAREF_1(string_1,i));
	      if (IFIX(ch) == (SI_Long)95L) {
		  if (EQ(Current_twriting_output_type,Qwide_string)) {
		      thing = '-';
		      twrite_wide_character(CHARACTERP(CHR(thing)) ? 
			      CHAR_CODE(CHR(thing)) : CHR(thing));
		  }
		  else {
		      if ( 
			      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			      Total_length_of_current_gensym_string))
			  extend_current_gensym_string(0);
		      temp = Current_gensym_string;
		      schar_arg_2 = Fill_pointer_for_current_gensym_string;
		      thing = '-';
		      schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
			      CHAR_CODE(CHR(thing)) : CHR(thing));
		      SET_SCHAR(temp,schar_arg_2,schar_new_value);
		      temp = 
			      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		      Fill_pointer_for_current_gensym_string = temp;
		  }
	      }
	      else {
		  gensymed_symbol = ch;
		  if ((SI_Long)65L <= IFIX(gensymed_symbol) && 
			  IFIX(gensymed_symbol) <= (SI_Long)90L) {
		      if (EQ(Current_twriting_output_type,Qwide_string)) {
			  thing = '-';
			  twrite_wide_character(CHARACTERP(CHR(thing)) ? 
				  CHAR_CODE(CHR(thing)) : CHR(thing));
		      }
		      else {
			  if ( 
				  !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				  Total_length_of_current_gensym_string))
			      extend_current_gensym_string(0);
			  temp = Current_gensym_string;
			  schar_arg_2 = Fill_pointer_for_current_gensym_string;
			  thing = '-';
			  schar_new_value = 
				  CODE_CHAR(CHARACTERP(CHR(thing)) ? 
				  CHAR_CODE(CHR(thing)) : CHR(thing));
			  SET_SCHAR(temp,schar_arg_2,schar_new_value);
			  temp = 
				  FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			  Fill_pointer_for_current_gensym_string = temp;
		      }
		      if (EQ(Current_twriting_output_type,Qwide_string)) {
			  thing_1 = ch;
			  twrite_wide_character(CHARACTERP(thing_1) ? 
				  CHAR_CODE(thing_1) : thing_1);
		      }
		      else {
			  if ( 
				  !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				  Total_length_of_current_gensym_string))
			      extend_current_gensym_string(0);
			  temp = Current_gensym_string;
			  schar_arg_2 = Fill_pointer_for_current_gensym_string;
			  thing_1 = ch;
			  schar_new_value = CODE_CHAR(CHARACTERP(thing_1) ?
				   CHAR_CODE(thing_1) : thing_1);
			  SET_SCHAR(temp,schar_arg_2,schar_new_value);
			  temp = 
				  FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			  Fill_pointer_for_current_gensym_string = temp;
		      }
		  }
		  else {
		      code = ch;
		      if (IFIX(code) < (SI_Long)127L)
			  simple_or_wide_character = (SI_Long)97L <= 
				  IFIX(code) && IFIX(code) <= 
				  (SI_Long)122L ? FIX(IFIX(code) + 
				  (SI_Long)-32L) : code;
		      else {
			  simple_or_wide_character = 
				  unicode_uppercase_if_lowercase(code);
			  if (simple_or_wide_character);
			  else
			      simple_or_wide_character = code;
		      }
		      if (EQ(Current_twriting_output_type,Qwide_string)) {
			  thing_1 = simple_or_wide_character;
			  twrite_wide_character(CHARACTERP(thing_1) ? 
				  CHAR_CODE(thing_1) : thing_1);
		      }
		      else {
			  if ( 
				  !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				  Total_length_of_current_gensym_string))
			      extend_current_gensym_string(0);
			  temp = Current_gensym_string;
			  schar_arg_2 = Fill_pointer_for_current_gensym_string;
			  thing_1 = simple_or_wide_character;
			  schar_new_value = CODE_CHAR(CHARACTERP(thing_1) ?
				   CHAR_CODE(thing_1) : thing_1);
			  SET_SCHAR(temp,schar_arg_2,schar_new_value);
			  temp = 
				  FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			  Fill_pointer_for_current_gensym_string = temp;
		      }
		  }
	      }
	      i = i + (SI_Long)1L;
	      goto next_loop;
	    end_loop:;
	      temp_1 = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return intern_text_string(1,temp_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_jemit_text_style_qm, Qcurrent_jemit_text_style_qm);

/* GET-GENSYM-LIST-OF-EXTERNAL-PROCEDURES */
Object get_gensym_list_of_external_procedures(sequence_of_symbols)
    Object sequence_of_symbols;
{
    Object gensymed_symbol, held_vector, external_procedure_name;
    Object external_procedure_qm, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object elt_1, validated_elt, static_methods;
    SI_Long next_index, length_1;

    x_note_fn_call(249,113);
    gensymed_symbol = sequence_of_symbols;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    external_procedure_name = Nil;
    external_procedure_qm = Nil;
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
    external_procedure_name = validated_elt;
    external_procedure_qm = 
	    get_instance_with_name_if_any(Qexternal_procedure,
	    external_procedure_name);
    if (external_procedure_qm) {
	ab_loopvar__2 = gensym_cons_1(external_procedure_qm,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    static_methods = ab_loopvar_;
    goto end_1;
    static_methods = Qnil;
  end_1:;
    return VALUES_1(static_methods);
}

DEFINE_VARIABLE_WITH_SYMBOL(Deferring_errors_for_class_export_p, Qdeferring_errors_for_class_export_p);

DEFINE_VARIABLE_WITH_SYMBOL(Deferred_errors_for_class_export_qm, Qdeferred_errors_for_class_export_qm);

static Object string_constant_20;  /* "JEMIT ERROR: ~a" */

static Object string_constant_21;  /* "unacceptable class for java emitter: ~A" */

/* G2-EMIT-CLASS-AS-JAVA */
Object g2_emit_class_as_java(class_name,static_methods,directory_1,
	    package_or_false,imports,class_path,unzipped_class_directory,
	    override_parent_qm)
    Object class_name, static_methods, directory_1, package_or_false, imports;
    Object class_path, unzipped_class_directory, override_parent_qm;
{
    Object class_description_qm, static_method_list, gensymed_symbol;
    Object held_vector, import_1, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object elt_1, validated_elt, import_list, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object wide_filename, ascii_filename, deferring_errors_for_class_export_p;
    Object deferred_errors_for_class_export_qm, error_1, ab_loop_list_;
    SI_Long next_index, length_1, bv16_length, aref_arg_2, aref_new_value;
    SI_Long length_2;
    Declare_special(5);

    x_note_fn_call(249,114);
    class_description_qm = 
	    lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop);
    static_method_list = 
	    get_gensym_list_of_external_procedures(static_methods);
    gensymed_symbol = imports;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    import_1 = Nil;
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
    import_1 = validated_elt;
    ab_loopvar__2 = gensym_cons_1(import_1,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    import_list = ab_loopvar_;
    goto end_1;
    import_list = Qnil;
  end_1:;
    if ( !SYMBOLP(override_parent_qm))
	override_parent_qm = Nil;
    if (class_description_qm && ISVREF(class_description_qm,(SI_Long)16L)) {
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
		  twrite(directory_1);
		  jwrite_symbol(2,class_name,T);
		  twrite_beginning_of_wide_string(array_constant_7,
			  FIX((SI_Long)5L));
		  wide_filename = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	ascii_filename = wide_string_to_gensym_string(wide_filename);
	reclaim_text_string(wide_filename);
	deferring_errors_for_class_export_p = T;
	PUSH_SPECIAL_WITH_SYMBOL(Deferring_errors_for_class_export_p,Qdeferring_errors_for_class_export_p,deferring_errors_for_class_export_p,
		1);
	  deferred_errors_for_class_export_qm = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Deferred_errors_for_class_export_qm,Qdeferred_errors_for_class_export_qm,deferred_errors_for_class_export_qm,
		  0);
	    jemit_class_to_file(class_name,static_method_list,
		    ascii_filename,EQ(package_or_false,
		    Evaluation_false_value) ? Nil : package_or_false,
		    import_list,class_path,unzipped_class_directory,
		    override_parent_qm,Nil);
	    error_1 = Nil;
	    ab_loop_list_ = Deferred_errors_for_class_export_qm;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    error_1 = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    Suppress_warning_message_header_qm = T;
	    if ((SI_Long)1L <= IFIX(Warning_message_level))
		give_warning_1(3,FIX((SI_Long)1L),string_constant_20,error_1);
	    Suppress_warning_message_header_qm = Nil;
	    goto next_loop_1;
	  end_loop_1:;
	    reclaim_slot_value(Deferred_errors_for_class_export_qm);
	  POP_SPECIAL();
	POP_SPECIAL();
	reclaim_gensym_string(ascii_filename);
    }
    else {
	Suppress_warning_message_header_qm = T;
	if ((SI_Long)1L <= IFIX(Warning_message_level))
	    give_warning_1(3,FIX((SI_Long)1L),string_constant_21,class_name);
	Suppress_warning_message_header_qm = Nil;
    }
    reclaim_evaluation_value(static_methods);
    reclaim_evaluation_value(imports);
    reclaim_gensym_list_1(static_method_list);
    return reclaim_gensym_list_1(import_list);
}

static Object Qunbound_in_protected_let;  /* unbound-in-protected-let */

static Object array_constant_14;   /* # */

/* JEMIT-CLASS-TO-STREAM */
Object jemit_class_to_stream(class_name,static_methods,package_qm,imports,
	    class_path,unzipped_directory,override_parent_qm,
	    additional_methods_qm,stream)
    Object class_name, static_methods, package_qm, imports, class_path;
    Object unzipped_directory, override_parent_qm, additional_methods_qm;
    Object stream;
{
    Object class_description;
    volatile Object methods;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(249,115);
    SAVE_STACK();
    class_description = Qunbound_in_protected_let;
    methods = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	class_description = 
		lookup_global_or_kb_specific_property_value(class_name,
		Class_description_gkbprop);
	methods = get_external_class_specific_methods(class_name);
	jemit_package(stream,package_qm);
	jemit_imports(stream,imports);
	jemit_class_header(stream,class_description,override_parent_qm);
	jemit_fields(stream,class_description);
	jemit_methods(stream,class_description,static_methods,T);
	jemit_methods(stream,class_description,methods,Nil);
	if (additional_methods_qm) {
	    joutput_line(stream,array_constant_14);
	    joutput_canned_text_with_indentation(stream,
		    additional_methods_qm,FIX((SI_Long)4L));
	}
	SAVE_VALUES(jemit_class_footer(stream));
    }
    POP_UNWIND_PROTECT(0);
    if (methods) {
	if ( !EQ(methods,Qunbound_in_protected_let))
	    reclaim_gensym_list_1(methods);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object Qtext_conversion_style;  /* text-conversion-style */

static Object Qutf_8_string;       /* utf-8-string */

static Object Qtext_conversion_style_for_purpose;  /* text-conversion-style-for-purpose */

static Object Kjemit_error;        /* :jemit-error */

/* JEMIT-CLASS-TO-FILE */
Object jemit_class_to_file(class_name,static_methods,filename,package_qm,
	    imports,class_path,unzipped_directory,override_parent_qm,
	    additional_methods_qm)
    Object class_name, static_methods, filename, package_qm, imports;
    Object class_path, unzipped_directory, override_parent_qm;
    Object additional_methods_qm;
{
    Object jemit_error_qm, temp, current_jemit_text_style_qm;
    volatile Object out_qm;
    Object error_text_string;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(1);
    Object result;

    x_note_fn_call(249,116);
    SAVE_STACK();
    jemit_error_qm = Nil;
    temp = 
	    get_text_conversion_style_structure_per_name(get_lookup_slot_value_given_default(Language_parameters,
	    Qtext_conversion_style,Nil));
    if (temp);
    else
	temp = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qutf_8_string),
		Qtext_conversion_style_for_purpose);
    current_jemit_text_style_qm = temp;
    PUSH_SPECIAL_WITH_SYMBOL(Current_jemit_text_style_qm,Qcurrent_jemit_text_style_qm,current_jemit_text_style_qm,
	    0);
      if (PUSH_CATCH(Kjemit_error,1)) {
	  out_qm = Qunbound_in_protected_let;
	  if (PUSH_UNWIND_PROTECT(0)) {
	      out_qm = g2_stream_open_for_output(filename);
	      if (out_qm)
		  jemit_class_to_stream(class_name,static_methods,
			  package_qm,imports,class_path,unzipped_directory,
			  override_parent_qm,additional_methods_qm,out_qm);
	  }
	  POP_UNWIND_PROTECT(0);
	  if (out_qm) {
	      if ( !EQ(out_qm,Qunbound_in_protected_let))
		  g2_stream_close(out_qm);
	  }
	  CONTINUE_UNWINDING(0);
	  POP_CATCH(1);
	  goto end_gensymed_symbol;
      }
      else
	  error_text_string = CATCH_VALUES();
      POP_CATCH(1);
      jemit_error_qm = error_text_string;
    end_gensymed_symbol:
      if (jemit_error_qm) {
	  Suppress_warning_message_header_qm = T;
	  if ((SI_Long)1L <= IFIX(Warning_message_level))
	      give_warning_1(3,FIX((SI_Long)1L),string_constant_20,
		      jemit_error_qm);
	  Suppress_warning_message_header_qm = Nil;
	  result = VALUES_1(jemit_error_qm);
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* JEMIT-ERROR */
Object jemit_error(text_string)
    Object text_string;
{
    Object result;

    x_note_fn_call(249,117);
    result = VALUES_1(text_string);
    THROW(Kjemit_error,result);
    return VALUES_1(Nil);
}

static Object Qjwith_output_to_text_string;  /* jwith-output-to-text-string */

/* JOUTPUT-LINE */
Object joutput_line(out,text_string)
    Object out, text_string;
{
    Object temp, schar_arg_2, schar_new_value;
    char thing;

    x_note_fn_call(249,118);
    if (EQ(out,Qjwith_output_to_text_string)) {
	twrite_general_string(text_string);
	if (Current_jemit_text_style_qm) {
	    if (EQ(Current_twriting_output_type,Qwide_string)) {
		thing = '\n';
		twrite_wide_character(CHARACTERP(CHR(thing)) ? 
			CHAR_CODE(CHR(thing)) : CHR(thing));
	    }
	    else {
		if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			Total_length_of_current_gensym_string))
		    extend_current_gensym_string(0);
		temp = Current_gensym_string;
		schar_arg_2 = Fill_pointer_for_current_gensym_string;
		thing = '\n';
		schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
			CHAR_CODE(CHR(thing)) : CHR(thing));
		SET_SCHAR(temp,schar_arg_2,schar_new_value);
		temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		Fill_pointer_for_current_gensym_string = temp;
	    }
	}
	else
	    twrite_line_separator();
    }
    else
	export_and_emit_text_line(text_string,Current_jemit_text_style_qm,out);
    return VALUES_1(Nil);
}

/* JOUTPUT-STRING */
Object joutput_string(out,text_string)
    Object out, text_string;
{
    x_note_fn_call(249,119);
    if (EQ(out,Qjwith_output_to_text_string))
	twrite_general_string(text_string);
    else
	export_and_emit_text_string(text_string,
		Current_jemit_text_style_qm,out);
    return VALUES_1(Nil);
}

/* JOUTPUT-CANNED-TEXT-WITH-INDENTATION */
Object joutput_canned_text_with_indentation(out,text_string,indentation)
    Object out, text_string, indentation;
{
    Object wide_string_bv16, canned_indentation, length_1;
    Object previous_newline_index, this_newline_index_qm, no_more_lines_p;
    Object this_substring, ab_loop_iter_flag_, this_wchar, temp, temp_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, index_1, ab_loop_bind_;
    SI_Long line_index, ab_loop_bind__1;

    x_note_fn_call(249,120);
    wide_string_bv16 = allocate_byte_vector_16(FIX(IFIX(indentation) + 
	    (SI_Long)3L));
    fill_wide_string_1(wide_string_bv16,FIX((SI_Long)32L),FIX((SI_Long)0L),
	    indentation);
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
    aref_arg_2 = bv16_length - (SI_Long)2L;
    aref_new_value = IFIX(indentation) & (SI_Long)65535L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    aref_arg_2 = bv16_length - (SI_Long)1L;
    aref_new_value = (SI_Long)57344L | IFIX(indentation) >>  -  - (SI_Long)16L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    UBYTE_16_ISASET_1(wide_string_bv16,IFIX(indentation),(SI_Long)0L);
    canned_indentation = wide_string_bv16;
    length_1 = text_string_length(text_string);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length_1);
    previous_newline_index = FIX((SI_Long)0L);
    this_newline_index_qm = Nil;
    no_more_lines_p = Nil;
    this_substring = Nil;
    ab_loop_iter_flag_ = T;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if ( !TRUEP(ab_loop_iter_flag_))
	previous_newline_index = FIXNUM_ADD1(this_newline_index_qm);
    line_index = IFIX(previous_newline_index);
    ab_loop_bind__1 = IFIX(length_1);
    this_wchar = Nil;
  next_loop_1:
    if (line_index >= ab_loop_bind__1)
	goto end_loop_1;
    this_wchar = FIX(UBYTE_16_ISAREF_1(text_string,line_index));
    if (newline_text_string_character_p(this_wchar)) {
	this_newline_index_qm = FIX(line_index);
	goto end_1;
    }
    line_index = line_index + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:
    this_newline_index_qm = Nil;
    goto end_1;
    this_newline_index_qm = Qnil;
  end_1:;
    no_more_lines_p =  !TRUEP(this_newline_index_qm) ? T : Nil;
    temp = previous_newline_index;
    temp_1 = this_newline_index_qm;
    if (temp_1);
    else
	temp_1 = length_1;
    this_substring = text_string_substring(text_string,temp,temp_1);
    if (EQ(out,Qjwith_output_to_text_string)) {
	twrite_general_string(canned_indentation);
	twrite_general_string(this_substring);
	twrite_line_separator();
    }
    else {
	export_and_emit_text_string(canned_indentation,
		Current_jemit_text_style_qm,out);
	export_and_emit_text_line(this_substring,
		Current_jemit_text_style_qm,out);
    }
    reclaim_text_string(this_substring);
    if (no_more_lines_p)
	goto end_loop;
    ab_loop_iter_flag_ = Nil;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    reclaim_text_string(canned_indentation);
    return VALUES_1(Nil);
}

static Object array_constant_15;   /* # */

static Object array_constant_16;   /* # */

/* JEMIT-PACKAGE */
Object jemit_package(out,package_qm)
    Object out, package_qm;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object text_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(249,121);
    if (package_qm) {
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
		  twrite_beginning_of_wide_string(array_constant_15,
			  FIX((SI_Long)8L));
		  twrite(package_qm);
		  twrite_beginning_of_wide_string(array_constant_4,
			  FIX((SI_Long)1L));
		  text_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	joutput_line(out,text_string);
	reclaim_text_string(text_string);
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
		  twrite_beginning_of_wide_string(array_constant_16,
			  FIX((SI_Long)1L));
		  text_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	joutput_line(out,text_string);
	return reclaim_text_string(text_string);
    }
    else
	return VALUES_1(Nil);
}

static Object array_constant_17;   /* # */

static Object array_constant_18;   /* # */

/* JEMIT-IMPORTS */
Object jemit_imports(out,imports)
    Object out, imports;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object text_string, import_1, ab_loop_list_;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(249,122);
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
	      twrite_beginning_of_wide_string(array_constant_17,
		      FIX((SI_Long)25L));
	      text_string = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    joutput_line(out,text_string);
    reclaim_text_string(text_string);
    import_1 = Nil;
    ab_loop_list_ = imports;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    import_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
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
	      twrite_beginning_of_wide_string(array_constant_18,
		      FIX((SI_Long)7L));
	      twrite(import_1);
	      twrite_beginning_of_wide_string(array_constant_4,
		      FIX((SI_Long)1L));
	      text_string = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    joutput_line(out,text_string);
    reclaim_text_string(text_string);
    goto next_loop;
  end_loop:;
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
	      twrite_beginning_of_wide_string(array_constant_16,
		      FIX((SI_Long)1L));
	      text_string = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    joutput_line(out,text_string);
    return reclaim_text_string(text_string);
}

static Object array_constant_19;   /* # */

static Object array_constant_20;   /* # */

static Object string_constant_22;  /* "Multiple Inheritance on ~a" */

static Object Qtw_user_item;       /* tw-user-item */

static Object array_constant_21;   /* # */

static Object array_constant_22;   /* # */

/* JEMIT-CLASS-HEADER */
Object jemit_class_header(out,class_description,override_parent_qm)
    Object out, class_description, override_parent_qm;
{
    Object class_name, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object direct_superiors, temp, text_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(249,123);
    class_name = ISVREF(class_description,(SI_Long)1L);
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
	      twrite_beginning_of_wide_string(array_constant_19,
		      FIX((SI_Long)13L));
	      jwrite_symbol(2,ISVREF(class_description,(SI_Long)1L),T);
	      twrite_beginning_of_wide_string(array_constant_20,
		      FIX((SI_Long)9L));
	      direct_superiors = 
		      lookup_global_or_kb_specific_property_value(class_name,
		      Direct_superior_classes_gkbprop);
	      if (CDR(direct_superiors))
		  jemit_error(tformat_text_string(2,string_constant_22,
			  class_name));
	      if ( !TRUEP(override_parent_qm) && EQ(CAR(direct_superiors),
		      Qtw_user_item))
		  twrite_beginning_of_wide_string(array_constant_21,
			  FIX((SI_Long)6L));
	      else {
		  temp = override_parent_qm;
		  if (temp);
		  else
		      temp = CAR(direct_superiors);
		  jwrite_symbol(2,temp,T);
	      }
	      text_string = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    joutput_line(out,text_string);
    reclaim_text_string(text_string);
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
	      twrite_beginning_of_wide_string(array_constant_22,
		      FIX((SI_Long)1L));
	      text_string = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    joutput_line(out,text_string);
    return reclaim_text_string(text_string);
}

/* JWRITE-SYMBOL */
Object jwrite_symbol varargs_1(int, n)
{
    Object symbol;
    Object class_p, mixed_case_reverses_case_p, symbol_name_1, len;
    Object ab_loop_it_, reverse_case_here_p, after_hyphen_p, ch;
    SI_Long index_1, ab_loop_bind_, i;
    Declare_varargs_nonrelocating;

    x_note_fn_call(249,124);
    INIT_ARGS_nonrelocating();
    symbol = REQUIRED_ARG_nonrelocating();
    class_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    mixed_case_reverses_case_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    symbol_name_1 = SYMBOL_NAME(symbol);
    len = length(symbol_name_1);
    if (mixed_case_reverses_case_p) {
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(len);
	ab_loop_it_ = Nil;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	ab_loop_it_ = LOWER_CASE_P(CHR(ICHAR(symbol_name_1,index_1))) ? T :
		 Nil;
	if (ab_loop_it_) {
	    reverse_case_here_p = ab_loop_it_;
	    goto end_1;
	}
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	reverse_case_here_p = Qnil;
      end_1:;
    }
    else
	reverse_case_here_p = Nil;
    if (reverse_case_here_p) {
	after_hyphen_p = class_p;
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(len);
	ch = Nil;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop_1;
	ch = CHR(ICHAR(symbol_name_1,i));
	if (EQ(ch,CHR('-')))
	    after_hyphen_p = T;
	else if (after_hyphen_p) {
	    after_hyphen_p = Nil;
	    twrite(CHAR_UPCASE(ch));
	}
	else if (LOWER_CASE_P(ch))
	    twrite(CHAR_UPCASE(ch));
	else
	    twrite(CHAR_DOWNCASE(ch));
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
    else {
	after_hyphen_p = class_p;
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(len);
	ch = Nil;
      next_loop_2:
	if (i >= ab_loop_bind_)
	    goto end_loop_2;
	ch = CHR(ICHAR(symbol_name_1,i));
	if (EQ(ch,CHR('-')))
	    after_hyphen_p = T;
	else if (after_hyphen_p) {
	    after_hyphen_p = Nil;
	    twrite(CHAR_UPCASE(ch));
	}
	else
	    twrite(CHAR_DOWNCASE(ch));
	i = i + (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:
	return VALUES_1(Qnil);
    }
}

static Object array_constant_23;   /* # */

static Object array_constant_24;   /* # */

static Object Qtext;               /* text */

static Object array_constant_25;   /* # */

static Object array_constant_26;   /* # */

static Object Qtruth_value;        /* truth-value */

static Object array_constant_27;   /* # */

static Object string_constant_23;  /* "~a is not supported" */

static Object Qinteger_array;      /* integer-array */

static Object array_constant_28;   /* # */

static Object Qfloat_array;        /* float-array */

static Object array_constant_29;   /* # */

static Object array_constant_30;   /* # */

static Object Qab_structure;       /* structure */

static Object array_constant_31;   /* # */

static Object Qab_or;              /* or */

static Object list_constant_1;     /* # */

static Object string_constant_24;  /* "strange type specification ~NT" */

/* JWRITE-TYPE-SPECIFICATION */
Object jwrite_type_specification(type_specification)
    Object type_specification;
{
    Object temp;

    x_note_fn_call(249,125);
    if (SYMBOLP(type_specification)) {
	if (EQ(type_specification,Qinteger))
	    return twrite_beginning_of_wide_string(array_constant_23,
		    FIX((SI_Long)3L));
	else if (EQ(type_specification,Qfloat))
	    return twrite_beginning_of_wide_string(array_constant_24,
		    FIX((SI_Long)6L));
	else if (EQ(type_specification,Qtext))
	    return twrite_beginning_of_wide_string(array_constant_25,
		    FIX((SI_Long)6L));
	else if (EQ(type_specification,Qsymbol))
	    return twrite_beginning_of_wide_string(array_constant_26,
		    FIX((SI_Long)6L));
	else if (EQ(type_specification,Qtruth_value))
	    return twrite_beginning_of_wide_string(array_constant_27,
		    FIX((SI_Long)7L));
	else
	    return jemit_error(tformat_text_string(1,string_constant_23));
    }
    else if (CONSP(type_specification)) {
	temp = CAR(type_specification);
	if (EQ(temp,Qab_class)) {
	    temp = CADR(type_specification);
	    if (EQ(temp,Qinteger_array))
		return twrite_beginning_of_wide_string(array_constant_28,
			FIX((SI_Long)5L));
	    else if (EQ(temp,Qfloat_array))
		return twrite_beginning_of_wide_string(array_constant_29,
			FIX((SI_Long)8L));
	    else
		return jwrite_symbol(2,CADR(type_specification),T);
	}
	else if (EQ(temp,Qsequence))
	    return twrite_beginning_of_wide_string(array_constant_30,
		    FIX((SI_Long)8L));
	else if (EQ(temp,Qab_structure))
	    return twrite_beginning_of_wide_string(array_constant_31,
		    FIX((SI_Long)9L));
	else if (EQ(temp,Qab_or)) {
	    if (EQUAL(type_specification,list_constant_1))
		return twrite_beginning_of_wide_string(array_constant_21,
			FIX((SI_Long)6L));
	    else
		return jemit_error(tformat_text_string(2,
			string_constant_24,type_specification));
	}
	else
	    return jemit_error(tformat_text_string(2,string_constant_24,
		    type_specification));
    }
    else
	return jemit_error(tformat_text_string(2,string_constant_24,
		type_specification));
}

/* JEMIT-FIELDS */
Object jemit_fields(out,class_description)
    Object out, class_description;
{
    x_note_fn_call(249,126);
    return jemit_fields_for_slot_names(out,class_description,
	    ISVREF(class_description,(SI_Long)7L));
}

/* GET-REALLY-OVERRIDED-UNIQUE-NAMES */
Object get_really_overrided_unique_names(class_description)
    Object class_description;
{
    Object local_names, override_names, override_name, ab_loop_list_;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2;

    x_note_fn_call(249,127);
    local_names = ISVREF(class_description,(SI_Long)7L);
    override_names = ISVREF(class_description,(SI_Long)8L);
    override_name = Nil;
    ab_loop_list_ = override_names;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    override_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(memq_function(override_name,local_names))) {
	ab_loopvar__2 = gensym_cons_1(override_name,Nil);
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

static Object array_constant_32;   /* # */

static Object array_constant_33;   /* # */

static Object array_constant_34;   /* # */

static Object array_constant_35;   /* # */

static Object string_constant_25;  /* "unsupported initial value for ~a" */

static Object string_constant_26;  /* "new Integer(~NV)" */

static Object string_constant_27;  /* "new Double(~NV)" */

static Object Kfuncall;            /* :funcall */

static Object Qinstantiate_object_in_attribute;  /* instantiate-object-in-attribute */

static Object array_constant_36;   /* # */

static Object array_constant_37;   /* # */

static Object array_constant_38;   /* # */

static Object array_constant_39;   /* # */

static Object string_constant_28;  /* "unsupported attribute initializer for ~a" */

static Object string_constant_29;  /* "unsupported data type in attribute ~a" */

/* JEMIT-FIELDS-FOR-SLOT-NAMES */
Object jemit_fields_for_slot_names(out,class_description,unique_names)
    Object out, class_description, unique_names;
{
    Object slot_name, ab_loop_list_, slot_description, type_specification;
    Object slot_init_form_qm, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object initial_value, casted_p, car_1, cdr_1, temp, managed_value;
    Object write_strings_parsably_qm, class_1, text_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp_1;
    Declare_special(6);

    x_note_fn_call(249,128);
    slot_name = Nil;
    ab_loop_list_ = unique_names;
    slot_description = Nil;
    type_specification = Nil;
    slot_init_form_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    slot_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    slot_description = 
	    get_slot_description_of_class_description_function(slot_name,
	    class_description,Nil);
    type_specification = ISVREF(slot_description,(SI_Long)5L);
    slot_init_form_qm = ISVREF(slot_description,(SI_Long)6L);
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    5);
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
	      4);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		3);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  2);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    1);
	      twrite_beginning_of_wide_string(array_constant_32,
		      FIX((SI_Long)11L));
	      jwrite_type_specification(type_specification);
	      twrite_beginning_of_wide_string(array_constant_16,
		      FIX((SI_Long)1L));
	      jwrite_symbol(1,ISVREF(slot_description,(SI_Long)2L));
	      if (slot_init_form_qm) {
		  initial_value = slot_init_form_qm;
		  casted_p = Nil;
		  if (CONSP(slot_init_form_qm)) {
		      car_1 = M_CAR(slot_init_form_qm);
		      cdr_1 = M_CDR(slot_init_form_qm);
		      if (CONSP(cdr_1)) {
			  temp = M_CAR(cdr_1);
			  temp_1 = SYMBOLP(temp);
		      }
		      else
			  temp_1 = TRUEP(Nil);
		      temp_1 = temp_1 ? slot_value_number_p(car_1) || 
			      text_string_p(car_1) || STRINGP(car_1) : 
			      TRUEP(Nil);
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  if (temp_1) {
		      managed_value = M_CAR(initial_value);
		      if (EQ(convert_type_or_unit_of_measure_to_type(M_CAR(M_CDR(initial_value))),
			      Qtruth_value)) {
			  if (FIXNUM_EQ(managed_value,Truth))
			      initial_value = Evaluation_true_value;
			  else if (FIXNUM_EQ(managed_value,Falsity))
			      initial_value = Evaluation_false_value;
			  else
			      initial_value = eval_cons_1(managed_value,
				      Qtruth_value);
		      }
		      else
			  initial_value = FIXNUMP(managed_value) || 
				  SYMBOLP(managed_value) ? managed_value : 
				  copy_evaluation_value_1(managed_value);
		      casted_p = T;
		  }
		  twrite_beginning_of_wide_string(array_constant_33,
			  FIX((SI_Long)3L));
		  if (SYMBOLP(type_specification)) {
		      if (EQ(type_specification,Qinteger) || 
			      EQ(type_specification,Qfloat))
			  twrite(initial_value);
		      else if (EQ(type_specification,Qtext)) {
			  write_strings_parsably_qm = T;
			  PUSH_SPECIAL_WITH_SYMBOL(Write_strings_parsably_qm,Qwrite_strings_parsably_qm,write_strings_parsably_qm,
				  0);
			    twrite_general_string(initial_value);
			  POP_SPECIAL();
		      }
		      else if (EQ(type_specification,Qsymbol)) {
			  twrite_beginning_of_wide_string(array_constant_34,
				  FIX((SI_Long)15L));
			  twrite(initial_value);
			  twrite_beginning_of_wide_string(array_constant_35,
				  FIX((SI_Long)2L));
		      }
		      else
			  jemit_error(tformat_text_string(2,
				  string_constant_25,
				  ISVREF(slot_description,(SI_Long)2L)));
		  }
		  else if (FIXNUMP(initial_value))
		      tformat(2,string_constant_26,initial_value);
		  else if (INLINE_DOUBLE_FLOAT_VECTOR_P(initial_value) != 
			  (SI_Long)0L && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(initial_value)) 
			  == (SI_Long)1L)
		      tformat(2,string_constant_27,initial_value);
		  else if (text_string_p(initial_value)) {
		      write_strings_parsably_qm = T;
		      PUSH_SPECIAL_WITH_SYMBOL(Write_strings_parsably_qm,Qwrite_strings_parsably_qm,write_strings_parsably_qm,
			      0);
			twrite_general_string(initial_value);
		      POP_SPECIAL();
		  }
		  else if (SYMBOLP(initial_value)) {
		      twrite_beginning_of_wide_string(array_constant_34,
			      FIX((SI_Long)15L));
		      twrite(initial_value);
		      twrite_beginning_of_wide_string(array_constant_35,
			      FIX((SI_Long)2L));
		  }
		  else if (CONSP(initial_value)) {
		      if (EQ(CAR(initial_value),Kfuncall) && 
			      EQ(CADR(initial_value),
			      Qinstantiate_object_in_attribute)) {
			  class_1 = CADDR(initial_value);
			  if (EQ(class_1,Qinteger_array))
			      twrite_beginning_of_wide_string(array_constant_36,
				      FIX((SI_Long)10L));
			  else if (EQ(class_1,Qfloat_array))
			      twrite_beginning_of_wide_string(array_constant_37,
				      FIX((SI_Long)13L));
			  else {
			      twrite_beginning_of_wide_string(array_constant_38,
				      FIX((SI_Long)4L));
			      jwrite_symbol(2,CADDR(initial_value),T);
			      twrite_beginning_of_wide_string(array_constant_39,
				      FIX((SI_Long)2L));
			  }
		      }
		      else
			  jemit_error(tformat_text_string(2,
				  string_constant_28,
				  ISVREF(slot_description,(SI_Long)2L)));
		  }
		  else
		      jemit_error(tformat_text_string(2,string_constant_29,
			      ISVREF(slot_description,(SI_Long)2L)));
		  if (casted_p)
		      reclaim_evaluation_value(initial_value);
	      }
	      twrite_beginning_of_wide_string(array_constant_4,
		      FIX((SI_Long)1L));
	      text_string = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    joutput_line(out,text_string);
    reclaim_text_string(text_string);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Collecting_exported_method_text_p, Qcollecting_exported_method_text_p);

DEFINE_VARIABLE_WITH_SYMBOL(List_of_exported_method_texts, Qlist_of_exported_method_texts);

/* JEMIT-METHODS */
Object jemit_methods(out,class_description,methods,static_p)
    Object out, class_description, methods, static_p;
{
    Object method, ab_loop_list_, exported_method_text_qm, temp;
    Object jemit_error_qm, this_method_stream, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object error_text_string, success_string, valid_string_qm, error_string_qm;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_catch(1);
    Declare_special(5);
    Object result;

    x_note_fn_call(249,129);
    method = Nil;
    ab_loop_list_ = methods;
    exported_method_text_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    method = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    exported_method_text_qm = Nil;
    temp = ISVREF(method,(SI_Long)20L);
    if (CAR(temp)) {
	jemit_error_qm = Nil;
	this_method_stream = Qjwith_output_to_text_string;
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
		  if (PUSH_CATCH(Kjemit_error,0)) {
		      jemit_method(this_method_stream,class_description,
			      method,static_p);
		      POP_CATCH(0);
		      goto end_gensymed_symbol;
		  }
		  else
		      error_text_string = CATCH_VALUES();
		  POP_CATCH(0);
		  jemit_error_qm = error_text_string;
		end_gensymed_symbol:
		  success_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	if (jemit_error_qm) {
	    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(success_string) != 
		    (SI_Long)0L)
		reclaim_wide_string(success_string);
	    result = VALUES_2(Nil,jemit_error_qm);
	}
	else
	    result = VALUES_2(success_string,Nil);
	MVS_2(result,valid_string_qm,error_string_qm);
	if (valid_string_qm) {
	    joutput_string(out,valid_string_qm);
	    if (Collecting_exported_method_text_p)
		exported_method_text_qm = valid_string_qm;
	    else
		reclaim_text_string(valid_string_qm);
	}
	else if (error_string_qm) {
	    if (Collecting_frame_notes_for_class_export_p)
		Collected_frame_notes_for_class_export_qm = 
			slot_value_cons_1(error_string_qm,
			Collected_frame_notes_for_class_export_qm);
	    else if (Deferring_errors_for_class_export_p)
		Deferred_errors_for_class_export_qm = 
			slot_value_cons_1(error_string_qm,
			Deferred_errors_for_class_export_qm);
	    else
		jemit_error(error_string_qm);
	}
    }
    if (Collecting_exported_method_text_p)
	List_of_exported_method_texts = 
		slot_value_cons_1(exported_method_text_qm,
		List_of_exported_method_texts);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object array_constant_40;   /* # */

/* JEMIT-CLASS-FOOTER */
Object jemit_class_footer(out)
    Object out;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object text_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(249,130);
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
	      twrite_beginning_of_wide_string(array_constant_40,
		      FIX((SI_Long)1L));
	      text_string = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    joutput_line(out,text_string);
    return reclaim_text_string(text_string);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_jemit_stream, Qcurrent_jemit_stream);

DEFINE_VARIABLE_WITH_SYMBOL(Current_jemit_indent, Qcurrent_jemit_indent);

DEFINE_VARIABLE_WITH_SYMBOL(Current_jemit_node_stack, Qcurrent_jemit_node_stack);

DEFINE_VARIABLE_WITH_SYMBOL(Current_jemit_compound_statement_list, Qcurrent_jemit_compound_statement_list);

DEFINE_VARIABLE_WITH_SYMBOL(Current_jemit_return_type_specification_qm, Qcurrent_jemit_return_type_specification_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Current_jemit_class_description, Qcurrent_jemit_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Current_jemit_class_object_table, Qcurrent_jemit_class_object_table);

DEFINE_VARIABLE_WITH_SYMBOL(Current_jemit_self_name, Qcurrent_jemit_self_name);

DEFINE_VARIABLE_WITH_SYMBOL(Current_jemit_locals, Qcurrent_jemit_locals);

DEFINE_VARIABLE_WITH_SYMBOL(Current_jemit_args, Qcurrent_jemit_args);

static Object array_constant_41;   /* # */

static Object array_constant_42;   /* # */

/* JEMIT-METHOD */
Object jemit_method(out,class_description,method,static_p)
    Object out, class_description, method, static_p;
{
    Object temp, compiled_gesture, name, current_jemit_args, returns;
    Object current_jemit_locals, body, current_jemit_class_object_table;
    Object current_jemit_stream, current_jemit_indent;
    Object current_jemit_node_stack, current_jemit_self_name;
    Object current_jemit_class_description;
    Object current_jemit_compound_statement_list;
    Object current_jemit_return_type_specification_qm;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object text_string, statement, ab_loop_list_;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, i;
    SI_Long ab_loop_bind_;
    Declare_special(15);
    Object result;

    x_note_fn_call(249,131);
    temp = ISVREF(method,(SI_Long)20L);
    compiled_gesture = CAR(temp);
    name = CAR(compiled_gesture);
    current_jemit_args = CADR(compiled_gesture);
    PUSH_SPECIAL_WITH_SYMBOL(Current_jemit_args,Qcurrent_jemit_args,current_jemit_args,
	    14);
      returns = CADDR(compiled_gesture);
      current_jemit_locals = CADDDR(compiled_gesture);
      PUSH_SPECIAL_WITH_SYMBOL(Current_jemit_locals,Qcurrent_jemit_locals,current_jemit_locals,
	      13);
	body = FIFTH(compiled_gesture);
	current_jemit_class_object_table = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_jemit_class_object_table,Qcurrent_jemit_class_object_table,current_jemit_class_object_table,
		12);
	  current_jemit_stream = out;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_jemit_stream,Qcurrent_jemit_stream,current_jemit_stream,
		  11);
	    current_jemit_indent = FIX((SI_Long)4L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_jemit_indent,Qcurrent_jemit_indent,current_jemit_indent,
		    10);
	      current_jemit_node_stack = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_jemit_node_stack,Qcurrent_jemit_node_stack,current_jemit_node_stack,
		      9);
		current_jemit_self_name = CAAR(Current_jemit_args);
		PUSH_SPECIAL_WITH_SYMBOL(Current_jemit_self_name,Qcurrent_jemit_self_name,current_jemit_self_name,
			8);
		  current_jemit_class_description = class_description;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_jemit_class_description,Qcurrent_jemit_class_description,current_jemit_class_description,
			  7);
		    current_jemit_compound_statement_list = CADR(body);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_jemit_compound_statement_list,Qcurrent_jemit_compound_statement_list,current_jemit_compound_statement_list,
			    6);
		      current_jemit_return_type_specification_qm = 
			      CAR(returns);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_jemit_return_type_specification_qm,Qcurrent_jemit_return_type_specification_qm,current_jemit_return_type_specification_qm,
			      5);
			result = separate_class_objects_from_real_code(body);
			MVS_2(result,body,Current_jemit_class_object_table);
			current_wide_string_list = Qdo_not_use;
			PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
				4);
			  wide_string_bv16 = 
				  allocate_byte_vector_16(FIX((SI_Long)2048L 
				  + (SI_Long)3L));
			  bv16_length = 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
			  aref_arg_2 = bv16_length - (SI_Long)2L;
			  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
			  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
				  aref_new_value);
			  aref_arg_2 = bv16_length - (SI_Long)1L;
			  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
			  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
				  aref_new_value);
			  UBYTE_16_ISASET_1(wide_string_bv16,
				  (SI_Long)2048L,(SI_Long)0L);
			  current_wide_string = wide_string_bv16;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
				  3);
			    fill_pointer_for_current_wide_string = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
				    2);
			      length_1 = 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
			      total_length_of_current_wide_string = 
				      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
				      length_1 - (SI_Long)2L) + 
				      ((UBYTE_16_ISAREF_1(Current_wide_string,
				      length_1 - (SI_Long)1L) & 
				      (SI_Long)8191L) << (SI_Long)16L));
			      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
				      1);
				current_twriting_output_type = Qwide_string;
				PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
					0);
				  i = (SI_Long)0L;
				  ab_loop_bind_ = IFIX(Current_jemit_indent);
				next_loop:
				  if (i >= ab_loop_bind_)
				      goto end_loop;
				  twrite_beginning_of_wide_string(array_constant_16,
					  FIX((SI_Long)1L));
				  i = i + (SI_Long)1L;
				  goto next_loop;
				end_loop:;
				  twrite_beginning_of_wide_string(array_constant_16,
					  FIX((SI_Long)1L));
				  text_string = copy_out_current_wide_string();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
			joutput_line(Current_jemit_stream,text_string);
			reclaim_text_string(text_string);
			jemit_compiled_method_prototype(class_description,
				name,Current_jemit_args,returns,static_p);
			current_wide_string_list = Qdo_not_use;
			PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
				4);
			  wide_string_bv16 = 
				  allocate_byte_vector_16(FIX((SI_Long)2048L 
				  + (SI_Long)3L));
			  bv16_length = 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
			  aref_arg_2 = bv16_length - (SI_Long)2L;
			  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
			  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
				  aref_new_value);
			  aref_arg_2 = bv16_length - (SI_Long)1L;
			  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
			  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
				  aref_new_value);
			  UBYTE_16_ISASET_1(wide_string_bv16,
				  (SI_Long)2048L,(SI_Long)0L);
			  current_wide_string = wide_string_bv16;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
				  3);
			    fill_pointer_for_current_wide_string = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
				    2);
			      length_1 = 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
			      total_length_of_current_wide_string = 
				      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
				      length_1 - (SI_Long)2L) + 
				      ((UBYTE_16_ISAREF_1(Current_wide_string,
				      length_1 - (SI_Long)1L) & 
				      (SI_Long)8191L) << (SI_Long)16L));
			      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
				      1);
				current_twriting_output_type = Qwide_string;
				PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
					0);
				  twrite_beginning_of_wide_string(array_constant_41,
					  FIX((SI_Long)5L));
				  text_string = copy_out_current_wide_string();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
			joutput_line(out,text_string);
			reclaim_text_string(text_string);
			jemit_compiled_method_locals(Current_jemit_locals);
			statement = Nil;
			ab_loop_list_ = body;
		      next_loop_1:
			if ( !TRUEP(ab_loop_list_))
			    goto end_loop_1;
			statement = M_CAR(ab_loop_list_);
			ab_loop_list_ = M_CDR(ab_loop_list_);
			jemit_compiled_gesture_statement(statement,
				FIX((SI_Long)4L),Nil);
			goto next_loop_1;
		      end_loop_1:;
			current_wide_string_list = Qdo_not_use;
			PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
				4);
			  wide_string_bv16 = 
				  allocate_byte_vector_16(FIX((SI_Long)2048L 
				  + (SI_Long)3L));
			  bv16_length = 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
			  aref_arg_2 = bv16_length - (SI_Long)2L;
			  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
			  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
				  aref_new_value);
			  aref_arg_2 = bv16_length - (SI_Long)1L;
			  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
			  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
				  aref_new_value);
			  UBYTE_16_ISASET_1(wide_string_bv16,
				  (SI_Long)2048L,(SI_Long)0L);
			  current_wide_string = wide_string_bv16;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
				  3);
			    fill_pointer_for_current_wide_string = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
				    2);
			      length_1 = 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
			      total_length_of_current_wide_string = 
				      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
				      length_1 - (SI_Long)2L) + 
				      ((UBYTE_16_ISAREF_1(Current_wide_string,
				      length_1 - (SI_Long)1L) & 
				      (SI_Long)8191L) << (SI_Long)16L));
			      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
				      1);
				current_twriting_output_type = Qwide_string;
				PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
					0);
				  twrite_beginning_of_wide_string(array_constant_42,
					  FIX((SI_Long)5L));
				  text_string = copy_out_current_wide_string();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
			joutput_line(out,text_string);
			reclaim_text_string(text_string);
			reclaim_gensym_list_1(body);
			result = reclaim_gensym_tree_1(Current_jemit_class_object_table);
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
    return result;
}

static Object Qlocal_assignment;   /* local-assignment */

static Object Qget_class;          /* get-class */

static Object Qsymbol_constant;    /* symbol-constant */

/* SEPARATE-CLASS-OBJECTS-FROM-REAL-CODE */
Object separate_class_objects_from_real_code(body)
    Object body;
{
    Object real_statements, pairs, statement, ab_loop_list_;
    Object statement_subforms, operation, temp, node, temp_1, operand;

    x_note_fn_call(249,132);
    real_statements = Qnil;
    pairs = Qnil;
    statement = Nil;
    ab_loop_list_ = CADR(body);
    statement_subforms = Nil;
    operation = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    statement = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    statement_subforms = CDR(statement);
    temp = THIRD(statement_subforms);
    operation = CADR(temp);
    if (EQ(CAR(statement),Qlocal_assignment) && EQ(operation,Qget_class)) {
	temp = CDR(statement);
	node = THIRD(temp);
	temp = CDR(statement);
	temp_1 = FIRST(temp);
	temp = CDDR(node);
	operand = CAR(temp);
	if (EQ(CADR(operand),Qsymbol_constant)) {
	    temp = CDDR(node);
	    temp = get_symbol_from_symbol_constant_node(CAR(temp));
	}
	else {
	    temp = CDDR(node);
	    temp = get_text_from_text_constant_node(CAR(temp));
	}
	pairs = gensym_cons_1(gensym_cons_1(temp_1,temp),pairs);
    }
    else
	real_statements = gensym_cons_1(statement,real_statements);
    goto next_loop;
  end_loop:
    temp_1 = nreverse(real_statements);
    temp = nreverse(pairs);
    return VALUES_2(temp_1,temp);
    return VALUES_1(Qnil);
}

static Object string_constant_30;  /* "multiple-return-statements not supported" */

static Object string_constant_31;  /* "~A-MAIN" */

static Object Qmain;               /* main */

static Object array_constant_43;   /* # */

static Object array_constant_44;   /* # */

static Object array_constant_45;   /* # */

static Object array_constant_46;   /* # */

static Object array_constant_47;   /* # */

static Object array_constant_48;   /* # */

/* JEMIT-COMPILED-METHOD-PROTOTYPE */
Object jemit_compiled_method_prototype(class_description,name,args,returns,
	    static_p)
    Object class_description, name, args, returns, static_p;
{
    Object class_name, main_name, main_symbol, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object tail, ab_loop_destructure_, type, temp, ab_loop_iter_flag_;
    Object text_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, i;
    SI_Long ab_loop_bind_;
    Declare_special(5);

    x_note_fn_call(249,133);
    if (CDR(returns))
	jemit_error(tformat_text_string(1,string_constant_30));
    if (static_p) {
	class_name = ISVREF(class_description,(SI_Long)1L);
	main_name = tformat_text_string(2,string_constant_31,class_name);
	main_symbol = intern_text_string(1,main_name);
	if (EQ(main_symbol,name))
	    name = Qmain;
    }
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
	      i = (SI_Long)0L;
	      ab_loop_bind_ = IFIX(Current_jemit_indent);
	    next_loop:
	      if (i >= ab_loop_bind_)
		  goto end_loop;
	      twrite_beginning_of_wide_string(array_constant_16,
		      FIX((SI_Long)1L));
	      i = i + (SI_Long)1L;
	      goto next_loop;
	    end_loop:;
	      twrite_beginning_of_wide_string(array_constant_43,
		      FIX((SI_Long)7L));
	      if (static_p)
		  twrite_beginning_of_wide_string(array_constant_44,
			  FIX((SI_Long)7L));
	      if ( !TRUEP(returns))
		  twrite_beginning_of_wide_string(array_constant_45,
			  FIX((SI_Long)4L));
	      else
		  jwrite_type_specification(CAR(returns));
	      twrite_beginning_of_wide_string(array_constant_16,
		      FIX((SI_Long)1L));
	      jwrite_symbol(1,name);
	      twrite_beginning_of_wide_string(array_constant_46,
		      FIX((SI_Long)2L));
	      if (EQ(name,Qmain))
		  twrite_beginning_of_wide_string(array_constant_47,
			  FIX((SI_Long)13L));
	      else {
		  tail = args;
		  ab_loop_destructure_ = CAR(args);
		  name = Nil;
		  type = Nil;
		  name = CAR(ab_loop_destructure_);
		  temp = CDR(ab_loop_destructure_);
		  type = CAR(temp);
		  ab_loop_iter_flag_ = T;
		next_loop_1:
		  if ( !TRUEP(tail))
		      goto end_loop_1;
		  if ( !TRUEP(ab_loop_iter_flag_)) {
		      temp = CAR(tail);
		      name = CAR(temp);
		      temp = CAR(tail);
		      temp = CDR(temp);
		      type = CAR(temp);
		  }
		  if (static_p ||  !EQ(tail,args)) {
		      jwrite_type_specification(type);
		      twrite_beginning_of_wide_string(array_constant_16,
			      FIX((SI_Long)1L));
		      jwrite_symbol(1,name);
		      if (CDR(tail))
			  twrite_beginning_of_wide_string(array_constant_3,
				  FIX((SI_Long)2L));
		  }
		  ab_loop_iter_flag_ = Nil;
		  tail = M_CDR(tail);
		  goto next_loop_1;
		end_loop_1:;
	      }
	      twrite_beginning_of_wide_string(array_constant_48,
		      FIX((SI_Long)1L));
	      text_string = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    joutput_line(Current_jemit_stream,text_string);
    return reclaim_text_string(text_string);
}

/* JEMIT-COMPILED-METHOD-LOCALS */
Object jemit_compiled_method_locals(locals)
    Object locals;
{
    Object current_jemit_indent, name, type, ab_loop_list_, ab_loop_desetq_;
    Object temp, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object text_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, i;
    SI_Long ab_loop_bind_;
    Declare_special(6);
    Object result;

    x_note_fn_call(249,134);
    current_jemit_indent = FIX(IFIX(Current_jemit_indent) + (SI_Long)4L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_jemit_indent,Qcurrent_jemit_indent,current_jemit_indent,
	    5);
      name = Nil;
      type = Nil;
      ab_loop_list_ = locals;
      ab_loop_desetq_ = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      ab_loop_desetq_ = M_CAR(ab_loop_list_);
      name = CAR(ab_loop_desetq_);
      temp = CDR(ab_loop_desetq_);
      type = CAR(temp);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      if ( !TRUEP(assq_function(name,Current_jemit_class_object_table))) {
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
		    i = (SI_Long)0L;
		    ab_loop_bind_ = IFIX(Current_jemit_indent);
		  next_loop_1:
		    if (i >= ab_loop_bind_)
			goto end_loop_1;
		    twrite_beginning_of_wide_string(array_constant_16,
			    FIX((SI_Long)1L));
		    i = i + (SI_Long)1L;
		    goto next_loop_1;
		  end_loop_1:;
		    jwrite_type_specification(type);
		    twrite_beginning_of_wide_string(array_constant_16,
			    FIX((SI_Long)1L));
		    jwrite_symbol(1,name);
		    twrite_beginning_of_wide_string(array_constant_4,
			    FIX((SI_Long)1L));
		    text_string = copy_out_current_wide_string();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  joutput_line(Current_jemit_stream,text_string);
	  reclaim_text_string(text_string);
      }
      goto next_loop;
    end_loop:;
      if (locals) {
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
		    i = (SI_Long)0L;
		    ab_loop_bind_ = IFIX(Current_jemit_indent);
		  next_loop_2:
		    if (i >= ab_loop_bind_)
			goto end_loop_2;
		    twrite_beginning_of_wide_string(array_constant_16,
			    FIX((SI_Long)1L));
		    i = i + (SI_Long)1L;
		    goto next_loop_2;
		  end_loop_2:;
		    twrite_beginning_of_wide_string(array_constant_16,
			    FIX((SI_Long)1L));
		    text_string = copy_out_current_wide_string();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  joutput_line(Current_jemit_stream,text_string);
	  result = reclaim_text_string(text_string);
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object string_constant_32;  /* " = " */

static Object Qchange_slot;        /* change-slot */

static Object Qchange_array_length;  /* change-array-length */

static Object array_constant_49;   /* # */

static Object array_constant_50;   /* # */

static Object array_constant_51;   /* # */

static Object Qab_if;              /* if */

static Object array_constant_52;   /* # */

static Object array_constant_53;   /* # */

static Object Qgesture_call;       /* gesture-call */

static Object Qrepeat;             /* repeat */

static Object array_constant_54;   /* # */

static Object Qexit_if;            /* exit-if */

static Object array_constant_55;   /* # */

static Object Qfor_loop_integer;   /* for-loop-integer */

static Object array_constant_56;   /* # */

static Object array_constant_57;   /* # */

static Object string_constant_33;  /* " <= " */

static Object string_constant_34;  /* " >= " */

static Object string_constant_35;  /* " += " */

static Object string_constant_36;  /* " -= " */

static Object array_constant_58;   /* # */

static Object string_constant_37;  /* "method must have return statement in all branches" */

static Object array_constant_59;   /* # */

static Object Qcompound_statement;  /* compound-statement */

/* JEMIT-COMPILED-GESTURE-STATEMENT */
Object jemit_compiled_gesture_statement(statement,indent_increment,
	    no_terminator_p)
    Object statement, indent_increment, no_terminator_p;
{
    Object statement_type, statement_subforms, current_jemit_indent;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object text_string, test_expression, then_clause, else_clause_qm;
    Object iteration_var_name, initial_value_expression;
    Object limit_value_expression, increment, increasing_p, loop_body;
    Object return_exp_list, fall_through_p, previous_statement_qm, temp;
    Object current_jemit_compound_statement_list, sub_statement, ab_loop_list_;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, i;
    SI_Long ab_loop_bind_;
    Declare_special(7);
    Object result;

    x_note_fn_call(249,135);
    statement_type = CAR(statement);
    statement_subforms = CDR(statement);
    current_jemit_indent = FIXNUM_ADD(Current_jemit_indent,indent_increment);
    PUSH_SPECIAL_WITH_SYMBOL(Current_jemit_indent,Qcurrent_jemit_indent,current_jemit_indent,
	    6);
      if (EQ(statement_type,Qlocal_assignment)) {
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
		    i = (SI_Long)0L;
		    ab_loop_bind_ = IFIX(Current_jemit_indent);
		  next_loop:
		    if (i >= ab_loop_bind_)
			goto end_loop;
		    twrite_beginning_of_wide_string(array_constant_16,
			    FIX((SI_Long)1L));
		    i = i + (SI_Long)1L;
		    goto next_loop;
		  end_loop:;
		    jwrite_symbol(1,FIRST(statement_subforms));
		    tformat(1,string_constant_32);
		    jemit_compiled_gesture_expression(THIRD(statement_subforms));
		    if ( !TRUEP(no_terminator_p))
			twrite_beginning_of_wide_string(array_constant_4,
				FIX((SI_Long)1L));
		    text_string = copy_out_current_wide_string();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  joutput_line(Current_jemit_stream,text_string);
	  result = reclaim_text_string(text_string);
      }
      else if (EQ(statement_type,Qchange_slot)) {
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
		    i = (SI_Long)0L;
		    ab_loop_bind_ = IFIX(Current_jemit_indent);
		  next_loop_1:
		    if (i >= ab_loop_bind_)
			goto end_loop_1;
		    twrite_beginning_of_wide_string(array_constant_16,
			    FIX((SI_Long)1L));
		    i = i + (SI_Long)1L;
		    goto next_loop_1;
		  end_loop_1:;
		    jwrite_field_reference(FIRST(statement_subforms),
			    SECOND(statement_subforms));
		    twrite_beginning_of_wide_string(array_constant_33,
			    FIX((SI_Long)3L));
		    jemit_compiled_gesture_expression(THIRD(statement_subforms));
		    if ( !TRUEP(no_terminator_p))
			twrite_beginning_of_wide_string(array_constant_4,
				FIX((SI_Long)1L));
		    text_string = copy_out_current_wide_string();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  joutput_line(Current_jemit_stream,text_string);
	  result = reclaim_text_string(text_string);
      }
      else if (EQ(statement_type,Qchange_array_length)) {
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
		    i = (SI_Long)0L;
		    ab_loop_bind_ = IFIX(Current_jemit_indent);
		  next_loop_2:
		    if (i >= ab_loop_bind_)
			goto end_loop_2;
		    twrite_beginning_of_wide_string(array_constant_16,
			    FIX((SI_Long)1L));
		    i = i + (SI_Long)1L;
		    goto next_loop_2;
		  end_loop_2:;
		    jemit_compiled_gesture_expression(FIRST(statement_subforms));
		    twrite_beginning_of_wide_string(array_constant_49,
			    FIX((SI_Long)7L));
		    jemit_array_type(FIRST(statement_subforms));
		    twrite_beginning_of_wide_string(array_constant_50,
			    FIX((SI_Long)1L));
		    jemit_compiled_gesture_expression(SECOND(statement_subforms));
		    twrite_beginning_of_wide_string(array_constant_51,
			    FIX((SI_Long)1L));
		    if ( !TRUEP(no_terminator_p))
			twrite_beginning_of_wide_string(array_constant_4,
				FIX((SI_Long)1L));
		    text_string = copy_out_current_wide_string();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  joutput_line(Current_jemit_stream,text_string);
	  result = reclaim_text_string(text_string);
      }
      else if (EQ(statement_type,Qab_if)) {
	  test_expression = FIRST(statement_subforms);
	  then_clause = SECOND(statement_subforms);
	  else_clause_qm = THIRD(statement_subforms);
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
		    i = (SI_Long)0L;
		    ab_loop_bind_ = IFIX(Current_jemit_indent);
		  next_loop_3:
		    if (i >= ab_loop_bind_)
			goto end_loop_3;
		    twrite_beginning_of_wide_string(array_constant_16,
			    FIX((SI_Long)1L));
		    i = i + (SI_Long)1L;
		    goto next_loop_3;
		  end_loop_3:;
		    twrite_beginning_of_wide_string(array_constant_52,
			    FIX((SI_Long)4L));
		    jemit_compiled_gesture_expression(test_expression);
		    twrite_beginning_of_wide_string(array_constant_48,
			    FIX((SI_Long)1L));
		    text_string = copy_out_current_wide_string();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  joutput_line(Current_jemit_stream,text_string);
	  reclaim_text_string(text_string);
	  jemit_compiled_gesture_statement(then_clause,FIX((SI_Long)4L),Nil);
	  if (else_clause_qm) {
	      current_jemit_indent = FIX((SI_Long)2L + 
		      IFIX(Current_jemit_indent));
	      PUSH_SPECIAL_WITH_SYMBOL(Current_jemit_indent,Qcurrent_jemit_indent,current_jemit_indent,
		      5);
		current_wide_string_list = Qdo_not_use;
		PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
			4);
		  wide_string_bv16 = 
			  allocate_byte_vector_16(FIX((SI_Long)2048L + 
			  (SI_Long)3L));
		  bv16_length = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
		  aref_arg_2 = bv16_length - (SI_Long)2L;
		  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
		  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			  aref_new_value);
		  aref_arg_2 = bv16_length - (SI_Long)1L;
		  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
		  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			  aref_new_value);
		  UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,
			  (SI_Long)0L);
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
			      ((UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			      (SI_Long)16L));
		      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			      1);
			current_twriting_output_type = Qwide_string;
			PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				0);
			  i = (SI_Long)0L;
			  ab_loop_bind_ = IFIX(Current_jemit_indent);
			next_loop_4:
			  if (i >= ab_loop_bind_)
			      goto end_loop_4;
			  twrite_beginning_of_wide_string(array_constant_16,
				  FIX((SI_Long)1L));
			  i = i + (SI_Long)1L;
			  goto next_loop_4;
			end_loop_4:;
			  twrite_beginning_of_wide_string(array_constant_53,
				  FIX((SI_Long)4L));
			  text_string = copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		joutput_line(Current_jemit_stream,text_string);
		reclaim_text_string(text_string);
	      POP_SPECIAL();
	      result = jemit_compiled_gesture_statement(else_clause_qm,
		      FIX((SI_Long)4L),no_terminator_p);
	  }
	  else
	      result = VALUES_1(Nil);
      }
      else if (EQ(statement_type,Qgesture_call))
	  result = jemit_call_statement(statement_subforms,no_terminator_p);
      else if (EQ(statement_type,Qrepeat)) {
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
		    i = (SI_Long)0L;
		    ab_loop_bind_ = IFIX(Current_jemit_indent);
		  next_loop_5:
		    if (i >= ab_loop_bind_)
			goto end_loop_5;
		    twrite_beginning_of_wide_string(array_constant_16,
			    FIX((SI_Long)1L));
		    i = i + (SI_Long)1L;
		    goto next_loop_5;
		  end_loop_5:;
		    twrite_beginning_of_wide_string(array_constant_54,
			    FIX((SI_Long)12L));
		    text_string = copy_out_current_wide_string();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  joutput_line(Current_jemit_stream,text_string);
	  reclaim_text_string(text_string);
	  result = jemit_compiled_gesture_statement(CAR(statement_subforms),
		  FIX((SI_Long)4L),no_terminator_p);
      }
      else if (EQ(statement_type,Qexit_if)) {
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
		    i = (SI_Long)0L;
		    ab_loop_bind_ = IFIX(Current_jemit_indent);
		  next_loop_6:
		    if (i >= ab_loop_bind_)
			goto end_loop_6;
		    twrite_beginning_of_wide_string(array_constant_16,
			    FIX((SI_Long)1L));
		    i = i + (SI_Long)1L;
		    goto next_loop_6;
		  end_loop_6:;
		    twrite_beginning_of_wide_string(array_constant_52,
			    FIX((SI_Long)4L));
		    jemit_compiled_gesture_expression(FIRST(statement_subforms));
		    twrite_beginning_of_wide_string(array_constant_55,
			    FIX((SI_Long)8L));
		    text_string = copy_out_current_wide_string();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  joutput_line(Current_jemit_stream,text_string);
	  result = reclaim_text_string(text_string);
      }
      else if (EQ(statement_type,Qfor_loop_integer)) {
	  iteration_var_name = FIRST(statement_subforms);
	  initial_value_expression = THIRD(statement_subforms);
	  limit_value_expression = FOURTH(statement_subforms);
	  increment = FIFTH(statement_subforms);
	  increasing_p = SIXTH(statement_subforms);
	  loop_body = SEVENTH(statement_subforms);
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
		    i = (SI_Long)0L;
		    ab_loop_bind_ = IFIX(Current_jemit_indent);
		  next_loop_7:
		    if (i >= ab_loop_bind_)
			goto end_loop_7;
		    twrite_beginning_of_wide_string(array_constant_16,
			    FIX((SI_Long)1L));
		    i = i + (SI_Long)1L;
		    goto next_loop_7;
		  end_loop_7:;
		    twrite_beginning_of_wide_string(array_constant_56,
			    FIX((SI_Long)5L));
		    jwrite_symbol(1,iteration_var_name);
		    twrite_beginning_of_wide_string(array_constant_33,
			    FIX((SI_Long)3L));
		    jemit_compiled_gesture_expression(initial_value_expression);
		    twrite_beginning_of_wide_string(array_constant_57,
			    FIX((SI_Long)3L));
		    jwrite_symbol(1,iteration_var_name);
		    twrite(increasing_p ? string_constant_33 : 
			    string_constant_34);
		    jemit_compiled_gesture_expression(limit_value_expression);
		    twrite_beginning_of_wide_string(array_constant_57,
			    FIX((SI_Long)3L));
		    jwrite_symbol(1,iteration_var_name);
		    twrite(increasing_p ? string_constant_35 : 
			    string_constant_36);
		    twrite(increment);
		    twrite_beginning_of_wide_string(array_constant_58,
			    FIX((SI_Long)3L));
		    text_string = copy_out_current_wide_string();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  joutput_line(Current_jemit_stream,text_string);
	  reclaim_text_string(text_string);
	  result = jemit_compiled_gesture_statement(loop_body,
		  FIX((SI_Long)4L),Nil);
      }
      else if (EQ(statement_type,Qreturn)) {
	  return_exp_list = FIRST(statement_subforms);
	  fall_through_p = SECOND(statement_subforms);
	  previous_statement_qm = previous_gesture_statement_qm(statement);
	  if (CDR(return_exp_list))
	      jemit_error(tformat_text_string(1,string_constant_30));
	  if (fall_through_p) {
	      if ( !TRUEP(previous_statement_qm) ||  
		      !EQ(CAR(previous_statement_qm),Qreturn)) {
		  temp =  
			  !TRUEP(Current_jemit_return_type_specification_qm) 
			  ? T : Nil;
		  if (temp)
		      result = VALUES_1(temp);
		  else
		      result = jemit_error(tformat_text_string(1,
			      string_constant_37));
	      }
	      else
		  result = VALUES_1(Qt);
	  }
	  else {
	      current_wide_string_list = Qdo_not_use;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		      4);
		wide_string_bv16 = 
			allocate_byte_vector_16(FIX((SI_Long)2048L + 
			(SI_Long)3L));
		bv16_length = 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
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
			    ((UBYTE_16_ISAREF_1(Current_wide_string,
			    length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			    (SI_Long)16L));
		    PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			    1);
		      current_twriting_output_type = Qwide_string;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			      0);
			i = (SI_Long)0L;
			ab_loop_bind_ = IFIX(Current_jemit_indent);
		      next_loop_8:
			if (i >= ab_loop_bind_)
			    goto end_loop_8;
			twrite_beginning_of_wide_string(array_constant_16,
				FIX((SI_Long)1L));
			i = i + (SI_Long)1L;
			goto next_loop_8;
		      end_loop_8:;
			twrite_beginning_of_wide_string(array_constant_59,
				FIX((SI_Long)7L));
			jemit_compiled_gesture_expression(CAR(return_exp_list));
			if ( !TRUEP(no_terminator_p))
			    twrite_beginning_of_wide_string(array_constant_4,
				    FIX((SI_Long)1L));
			text_string = copy_out_current_wide_string();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	      joutput_line(Current_jemit_stream,text_string);
	      result = reclaim_text_string(text_string);
	  }
      }
      else if (EQ(statement_type,Qcompound_statement)) {
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
		    i = (SI_Long)0L;
		    ab_loop_bind_ = IFIX(Current_jemit_indent);
		  next_loop_9:
		    if (i >= ab_loop_bind_)
			goto end_loop_9;
		    twrite_beginning_of_wide_string(array_constant_16,
			    FIX((SI_Long)1L));
		    i = i + (SI_Long)1L;
		    goto next_loop_9;
		  end_loop_9:;
		    twrite_beginning_of_wide_string(array_constant_22,
			    FIX((SI_Long)1L));
		    text_string = copy_out_current_wide_string();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  joutput_line(Current_jemit_stream,text_string);
	  reclaim_text_string(text_string);
	  current_jemit_compound_statement_list = FIRST(statement_subforms);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_jemit_compound_statement_list,Qcurrent_jemit_compound_statement_list,current_jemit_compound_statement_list,
		  0);
	    sub_statement = Nil;
	    ab_loop_list_ = FIRST(statement_subforms);
	  next_loop_10:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_10;
	    sub_statement = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    jemit_compiled_gesture_statement(sub_statement,
		    FIX((SI_Long)4L),Nil);
	    goto next_loop_10;
	  end_loop_10:;
	  POP_SPECIAL();
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
		    i = (SI_Long)0L;
		    ab_loop_bind_ = IFIX(Current_jemit_indent);
		  next_loop_11:
		    if (i >= ab_loop_bind_)
			goto end_loop_11;
		    twrite_beginning_of_wide_string(array_constant_16,
			    FIX((SI_Long)1L));
		    i = i + (SI_Long)1L;
		    goto next_loop_11;
		  end_loop_11:;
		    twrite_beginning_of_wide_string(array_constant_40,
			    FIX((SI_Long)1L));
		    text_string = copy_out_current_wide_string();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  joutput_line(Current_jemit_stream,text_string);
	  result = reclaim_text_string(text_string);
      }
      else
	  result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object string_constant_38;  /* "multiple assignments ~s not supported" */

static Object array_constant_60;   /* # */

/* JEMIT-CALL-STATEMENT */
Object jemit_call_statement(statement_subforms,no_terminator_p)
    Object statement_subforms, no_terminator_p;
{
    Object path, root, call_name, static_method_name_p, temp;
    Object assignment_variable_list, compiled_arg_list;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object compiled_arg, ab_loop_list_, non_comma_element, text_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, i;
    SI_Long ab_loop_bind_;
    Declare_special(5);
    Object result;

    x_note_fn_call(249,136);
    path = Nil;
    root = Nil;
    call_name = FIRST(statement_subforms);
    static_method_name_p = assq_function(call_name,
	    Current_jemit_class_object_table);
    if ( !TRUEP(static_method_name_p)) {
	temp = FOURTH(statement_subforms);
	result = get_method_arg_path_and_root(CAR(temp));
	MVS_2(result,path,root);
    }
    assignment_variable_list = SECOND(statement_subforms);
    compiled_arg_list = FOURTH(statement_subforms);
    if (CDR(assignment_variable_list))
	jemit_error(tformat_text_string(2,string_constant_38,
		assignment_variable_list));
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
	      i = (SI_Long)0L;
	      ab_loop_bind_ = IFIX(Current_jemit_indent);
	    next_loop:
	      if (i >= ab_loop_bind_)
		  goto end_loop;
	      twrite_beginning_of_wide_string(array_constant_16,
		      FIX((SI_Long)1L));
	      i = i + (SI_Long)1L;
	      goto next_loop;
	    end_loop:;
	      if (CAR(assignment_variable_list)) {
		  jwrite_symbol(1,FIRST(assignment_variable_list));
		  tformat(1,string_constant_32);
	      }
	      jwrite_method_call_name(root,path,call_name);
	      twrite_beginning_of_wide_string(array_constant_60,
		      FIX((SI_Long)1L));
	      compiled_arg = Nil;
	      ab_loop_list_ = static_method_name_p ? compiled_arg_list : 
		      CDR(compiled_arg_list);
	      non_comma_element = static_method_name_p ? 
		      CAR(compiled_arg_list) : CADR(compiled_arg_list);
	    next_loop_1:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_1;
	      compiled_arg = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      if ( !EQ(compiled_arg,non_comma_element))
		  twrite_beginning_of_wide_string(array_constant_3,
			  FIX((SI_Long)2L));
	      jemit_compiled_gesture_expression(compiled_arg);
	      goto next_loop_1;
	    end_loop_1:;
	      twrite_beginning_of_wide_string(array_constant_48,
		      FIX((SI_Long)1L));
	      if ( !TRUEP(no_terminator_p))
		  twrite_beginning_of_wide_string(array_constant_4,
			  FIX((SI_Long)1L));
	      text_string = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    joutput_line(Current_jemit_stream,text_string);
    return reclaim_text_string(text_string);
}

static Object array_constant_61;   /* # */

/* JWRITE-METHOD-CALL-NAME */
Object jwrite_method_call_name(root_qm,path,method_name)
    Object root_qm, path, method_name;
{
    Object method_name_included_p, temp, java_class_name, elt_1, ab_loop_list_;

    x_note_fn_call(249,137);
    method_name_included_p = Nil;
    if (root_qm && EQ(root_qm,Current_jemit_self_name));
    else if (assq_function(method_name,Current_jemit_class_object_table)) {
	method_name_included_p = T;
	temp = assq_function(method_name,Current_jemit_class_object_table);
	java_class_name = CDR(temp);
	if (SYMBOLP(java_class_name))
	    jwrite_symbol(2,java_class_name,T);
	else
	    twrite_general_string(java_class_name);
    }
    else {
	jwrite_symbol(1,root_qm);
	twrite_beginning_of_wide_string(array_constant_61,FIX((SI_Long)1L));
    }
    elt_1 = Nil;
    ab_loop_list_ = path;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    elt_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    jwrite_symbol(1,elt_1);
    twrite_beginning_of_wide_string(array_constant_61,FIX((SI_Long)1L));
    goto next_loop;
  end_loop:;
    if ( !TRUEP(method_name_included_p))
	return jwrite_symbol(1,method_name);
    else
	return VALUES_1(Nil);
}

static Object list_constant_2;     /* # */

static Object Qget_slot;           /* get-slot */

static Object Qfetch_local;        /* fetch-local */

static Object string_constant_39;  /* "first argument to call too complex" */

/* GET-METHOD-ARG-PATH-AND-ROOT */
Object get_method_arg_path_and_root(arg_node)
    Object arg_node;
{
    Object next_node, path, node, operation, args, temp;

    x_note_fn_call(249,138);
    next_node = Nil;
    path = Qnil;
    node = arg_node;
    operation = Nil;
    args = Nil;
  next_loop:
    operation = CADR(node);
    args = CDDR(node);
    if (member_eql(operation,list_constant_2))
	next_node = CAR(args);
    else if (EQ(operation,Qget_slot)) {
	temp = get_symbol_from_symbol_constant_node(SECOND(args));
	path = gensym_cons_1(temp,path);
	next_node = FIRST(args);
    }
    else if (EQ(operation,Qfetch_local))
	return VALUES_2(path,CAR(args));
    else
	jemit_error(tformat_text_string(1,string_constant_39));
    node = next_node;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* PREVIOUS-GESTURE-STATEMENT? */
Object previous_gesture_statement_qm(current_statement)
    Object current_statement;
{
    Object tail;

    x_note_fn_call(249,139);
    tail = Current_jemit_compound_statement_list;
  next_loop:
    if ( !TRUEP(tail))
	goto end_loop;
    if (EQ(CADR(tail),current_statement))
	return VALUES_1(CAR(tail));
    tail = M_CDR(tail);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* JWRITE-FIELD-REFERENCE */
Object jwrite_field_reference(slot_name,item_expression)
    Object slot_name, item_expression;
{
    Object name_qm, class_1;
    Object result;

    x_note_fn_call(249,140);
    result = get_local_name_and_type_of_item_expression_if_simple(item_expression);
    MVS_2(result,name_qm,class_1);
    if (name_qm)
	return jwrite_checked_field_reference(slot_name,name_qm,class_1);
    else {
	cerror((SI_Long)2L,"go on","emit slot existence check, Joe");
	jemit_compiled_gesture_expression(item_expression);
	twrite_beginning_of_wide_string(array_constant_61,FIX((SI_Long)1L));
	return jwrite_symbol(1,slot_name);
    }
}

static Object string_constant_40;  /* "cannot compile attribute of unknown class ~a" */

static Object string_constant_41;  /* "undefined slot/field ~a" */

/* JWRITE-CHECKED-FIELD-REFERENCE */
Object jwrite_checked_field_reference(slot_name,item_var_name,class_1)
    Object slot_name, item_var_name, class_1;
{
    Object class_description, temp, java_class_name;

    x_note_fn_call(249,141);
    if (EQ(item_var_name,Current_jemit_self_name))
	class_description = Current_jemit_class_description;
    else {
	if ( !TRUEP(lookup_global_or_kb_specific_property_value(class_1,
		Class_description_gkbprop)))
	    jemit_error(tformat_text_string(2,string_constant_40,class_1));
	class_description = 
		lookup_global_or_kb_specific_property_value(class_1,
		Class_description_gkbprop);
    }
    if (get_slot_description_of_class_description_function(slot_name,
	    class_description,Nil)) {
	if (EQ(item_var_name,Current_jemit_self_name))
	    return jwrite_symbol(1,slot_name);
	else {
	    jwrite_symbol(1,item_var_name);
	    twrite_beginning_of_wide_string(array_constant_61,
		    FIX((SI_Long)1L));
	    return jwrite_symbol(1,slot_name);
	}
    }
    else if (assq_function(item_var_name,Current_jemit_class_object_table)) {
	temp = assq_function(item_var_name,Current_jemit_class_object_table);
	java_class_name = CDR(temp);
	if (SYMBOLP(java_class_name))
	    jwrite_symbol(2,java_class_name,T);
	else
	    twrite(java_class_name);
	twrite_beginning_of_wide_string(array_constant_61,FIX((SI_Long)1L));
	return jwrite_symbol(1,slot_name);
    }
    else
	return jemit_error(tformat_text_string(2,string_constant_41,
		slot_name));
}

static Object list_constant_3;     /* # */

/* NODE-IS-SIMPLE-ITEM-EXPRESSION-P */
Object node_is_simple_item_expression_p(node)
    Object node;
{
    Object temp, sub_node;

    x_note_fn_call(249,142);
    if (memq_function(CADR(node),list_constant_3)) {
	temp = CDDR(node);
	sub_node = CAR(temp);
	temp = EQ(CADR(sub_node),Qfetch_local) ? 
		class_type_specification_p(CAR(sub_node)) : Qnil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qvalue2frame;        /* value2frame */

/* GET-LOCAL-NAME-AND-TYPE-OF-ITEM-EXPRESSION-IF-SIMPLE */
Object get_local_name_and_type_of_item_expression_if_simple(node)
    Object node;
{
    Object operation, temp, sub_node;

    x_note_fn_call(249,143);
    operation = CADR(node);
    if (EQ(operation,Qvalue2frame)) {
	temp = CDDR(node);
	sub_node = CAR(temp);
	if (EQ(CADR(sub_node),Qfetch_local) && 
		class_type_specification_p(CAR(sub_node))) {
	    temp = CDDR(sub_node);
	    return VALUES_2(CAR(temp),M_CAR(M_CDR(CAR(sub_node))));
	}
	else
	    return VALUES_1(Nil);
    }
    else if (EQ(operation,Qfetch_local)) {
	if (class_type_specification_p(CAR(node))) {
	    temp = CDDR(node);
	    return VALUES_2(CAR(temp),M_CAR(M_CDR(CAR(node))));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Qnil);
}

static Object list_constant_4;     /* # */

static Object list_constant_5;     /* # */

static Object string_constant_42;  /* "array type not simple enough" */

/* JEMIT-ARRAY-TYPE */
Object jemit_array_type(node)
    Object node;
{
    Object operation, array_class_qm, type, temp, item_node, slot_name;
    Object class_description_qm, slot_description_qm, slot_type;

    x_note_fn_call(249,144);
    operation = CADR(node);
    array_class_qm = Nil;
    if (EQ(operation,Qfetch_local)) {
	type = CAR(node);
	if (EQUAL(type,list_constant_4) || EQUAL(type,list_constant_5))
	    array_class_qm = CADR(type);
    }
    else if (EQ(operation,Qget_slot)) {
	temp = CDDR(node);
	item_node = CAR(temp);
	if (EQ(CADR(item_node),Qfetch_local)) {
	    temp = CDDR(node);
	    slot_name = get_symbol_from_symbol_constant_node(CADR(temp));
	    type = CAR(item_node);
	    if (class_type_specification_p(type)) {
		class_description_qm = 
			lookup_global_or_kb_specific_property_value(CADR(type),
			Class_description_gkbprop);
		slot_description_qm = class_description_qm ? 
			get_slot_description_of_class_description_function(slot_name,
			class_description_qm,Nil) : Qnil;
		slot_type = slot_description_qm ? 
			ISVREF(slot_description_qm,(SI_Long)5L) : Qnil;
		if (EQUAL(slot_type,list_constant_4) || EQUAL(slot_type,
			list_constant_5))
		    array_class_qm = CADR(slot_type);
	    }
	}
    }
    if (array_class_qm) {
	if (EQ(array_class_qm,Qfloat_array))
	    return twrite_beginning_of_wide_string(array_constant_24,
		    FIX((SI_Long)6L));
	else if (EQ(array_class_qm,Qinteger_array))
	    return twrite_beginning_of_wide_string(array_constant_23,
		    FIX((SI_Long)3L));
	else
	    return VALUES_1(Qnil);
    }
    else
	return jemit_error(tformat_text_string(1,string_constant_42));
}

Object Java_operator_precedence_list = UNBOUND;

/* JAVA-OPERATOR-TIGHTER-P */
Object java_operator_tighter_p(op1,op2)
    Object op1, op2;
{
    Object tail1, temp;

    x_note_fn_call(249,145);
    tail1 = memq_function(op1,Java_operator_precedence_list);
    temp = memq_function(op2,CDR(tail1));
    return VALUES_1(temp);
}

Object Equivalent_java_operator_prop = UNBOUND;

Object Equivalent_java_method_prop = UNBOUND;

Object Java_operator_precedence_prop = UNBOUND;

Object Java_operator_emitter_template_prop = UNBOUND;

/* JEMIT-COMPILED-GESTURE-EXPRESSION */
Object jemit_compiled_gesture_expression(node)
    Object node;
{
    x_note_fn_call(249,146);
    return jemit_compiled_gesture_expression_rec(tighten_gesture_value_node_type_information(node));
}

/* TIGHTEN-GESTURE-VALUE-NODE-TYPE-INFORMATION */
Object tighten_gesture_value_node_type_information(node)
    Object node;
{
    x_note_fn_call(249,147);
    return VALUES_1(node);
}

static Object list_constant_6;     /* # */

static Object Qtw_format_form;     /* tw-format-form */

static Object Qget_slot_or_no_item;  /* get-slot-or-no-item */

static Object string_constant_43;  /* "evaluated attribute/field names needs reflection API" */

static Object Qnew_class_instance;  /* new-class-instance */

static Object Qequivalent_java_operator;  /* equivalent-java-operator */

static Object Qequivalent_java_method;  /* equivalent-java-method */

static Object string_constant_44;  /* "unrecognized expression type ~a" */

static Object Qab_gensym;          /* gensym */

/* JEMIT-COMPILED-GESTURE-EXPRESSION-REC */
Object jemit_compiled_gesture_expression_rec(node)
    Object node;
{
    Object instruction_name, args, slot_name_node, item_node, gensym_pop_store;
    Object cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(249,148);
    Current_jemit_node_stack = gensym_cons_1(node,Current_jemit_node_stack);
    if (primitive_gesture_value_node_p(node))
	jemit_primitive_gesture_value_node(node);
    else {
	instruction_name = get_instruction_for_gesture_value_node(node);
	args = CDDR(node);
	if (member_eql(instruction_name,list_constant_6))
	    jemit_cast_expression(node);
	else if (EQ(instruction_name,Qtw_format_form))
	    jemit_format_expression(node);
	else if (EQ(instruction_name,Qget_slot_or_no_item) || 
		EQ(instruction_name,Qget_slot)) {
	    slot_name_node = SECOND(args);
	    item_node = FIRST(args);
	    if (EQ(CADR(slot_name_node),Qsymbol_constant))
		jwrite_field_reference(get_symbol_from_symbol_constant_node(slot_name_node),
			item_node);
	    else
		jemit_error(tformat_text_string(1,string_constant_43));
	}
	else if (EQ(instruction_name,Qnew_class_instance))
	    jemit_new_expression(node);
	else if (getfq_function_no_default(INLINE_SYMBOL_PLIST(instruction_name),
		Qequivalent_java_operator))
	    jemit_gesture_node_as_operator(node,
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(instruction_name),
		    Qequivalent_java_operator));
	else if (getfq_function_no_default(INLINE_SYMBOL_PLIST(instruction_name),
		Qequivalent_java_method));
	else
	    jemit_error(tformat_text_string(2,string_constant_44,
		    instruction_name));
    }
    gensym_pop_store = Nil;
    cons_1 = Current_jemit_node_stack;
    if (cons_1) {
	gensym_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qab_gensym);
	if (ISVREF(Available_gensym_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_gensym_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_gensym_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_gensym_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_gensym_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Current_jemit_node_stack = next_cons;
    return VALUES_1(gensym_pop_store);
}

static Object Qtext_constant;      /* text-constant */

static Object array_constant_62;   /* # */

/* JEMIT-FORMAT-EXPRESSION */
Object jemit_format_expression(node)
    Object node;
{
    Object res, sub_node, ab_loop_list_, node_operation, temp, args, arg;
    char temp_1;

    x_note_fn_call(249,149);
    res = Qnil;
    sub_node = Nil;
    ab_loop_list_ = CDDR(node);
    node_operation = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    sub_node = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    node_operation = CADR(sub_node);
    if (EQ(node_operation,Qtext_constant)) {
	temp = CDDR(sub_node);
	temp_1 = IFIX(text_string_length(CAR(temp))) == (SI_Long)0L;
    }
    else
	temp_1 = TRUEP(Nil);
    if ( !temp_1)
	res = gensym_cons_1(sub_node,res);
    goto next_loop;
  end_loop:
    args = res;
    goto end_1;
    args = Qnil;
  end_1:;
    arg = Nil;
    ab_loop_list_ = CDR(args);
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    arg = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !EQ(arg,CADR(args)))
	twrite_beginning_of_wide_string(array_constant_62,FIX((SI_Long)1L));
    jemit_compiled_gesture_expression_rec(arg);
    goto next_loop_1;
  end_loop_1:
    reclaim_gensym_list_1(args);
    return VALUES_1(Qnil);
}

static Object Qprimary;            /* primary */

static Object array_constant_63;   /* # */

/* JEMIT-NEW-EXPRESSION */
Object jemit_new_expression(node)
    Object node;
{
    Object precedence, temp, arg, class_name, needs_parens_p;

    x_note_fn_call(249,150);
    precedence = Qprimary;
    temp = CDDR(node);
    arg = CAR(temp);
    class_name = get_symbol_from_symbol_constant_node(arg);
    needs_parens_p = operator_needs_parens_p(precedence);
    if (needs_parens_p)
	twrite_beginning_of_wide_string(array_constant_60,FIX((SI_Long)1L));
    twrite_beginning_of_wide_string(array_constant_38,FIX((SI_Long)4L));
    jwrite_symbol(2,class_name,T);
    twrite_beginning_of_wide_string(array_constant_63,FIX((SI_Long)3L));
    if (needs_parens_p)
	return twrite_beginning_of_wide_string(array_constant_48,
		FIX((SI_Long)1L));
    else
	return VALUES_1(Nil);
}

static Object Qvalue2integer;      /* value2integer */

static Object Qvalue2float;        /* value2float */

static Object Qvalue2quantity;     /* value2quantity */

static Object Qvalue2text;         /* value2text */

static Object Qvalue2symbol;       /* value2symbol */

static Object Qvalue2truth_value;  /* value2truth-value */

static Object Qvalue2struct;       /* value2struct */

static Object list_constant_7;     /* # */

static Object Qvalue2sequence;     /* value2sequence */

static Object list_constant_8;     /* # */

static Object Qvalue2datum;        /* value2datum */

static Object Qdatum;              /* datum */

static Object Qint2float;          /* int2float */

static Object string_constant_45;  /* "real casts are NYI" */

static Object string_constant_46;  /* "attribute/field access expression too complex ~a" */

static Object string_constant_47;  /* "INTERNAL ERROR: could never cast ~s to ~NT" */

/* JEMIT-CAST-EXPRESSION */
Object jemit_cast_expression(node)
    Object node;
{
    Object instruction_name, args, operand, operand_instruction_name;
    Object operand_type_specification, type_node_qm, target_type_specification;
    Object get_slot_args, frame_arg_node, slot_name, frame_class, temp;
    Object frame_arg_local_name, slot_type_specification_qm;

    x_note_fn_call(249,151);
    instruction_name = CADR(node);
    args = CDDR(node);
    operand = CAR(args);
    operand_instruction_name = CADR(operand);
    operand_type_specification = CAR(operand);
    type_node_qm = CADR(args);
    if (EQ(instruction_name,Qvalue2integer))
	target_type_specification = Qinteger;
    else if (EQ(instruction_name,Qvalue2float))
	target_type_specification = Qfloat;
    else if (EQ(instruction_name,Qvalue2quantity))
	target_type_specification = Qnumber;
    else if (EQ(instruction_name,Qvalue2text))
	target_type_specification = Qtext;
    else if (EQ(instruction_name,Qvalue2symbol))
	target_type_specification = Qsymbol;
    else if (EQ(instruction_name,Qvalue2truth_value))
	target_type_specification = Qtruth_value;
    else if (EQ(instruction_name,Qvalue2struct))
	target_type_specification = list_constant_7;
    else if (EQ(instruction_name,Qvalue2sequence))
	target_type_specification = list_constant_8;
    else if (EQ(instruction_name,Qvalue2datum))
	target_type_specification = Qdatum;
    else if (EQ(instruction_name,Qvalue2frame))
	target_type_specification = gensym_list_2(Qab_class,type_node_qm);
    else if (EQ(instruction_name,Qint2float))
	target_type_specification = Qfloat;
    else
	target_type_specification = Qnil;
    if (EQ(operand_instruction_name,Qget_slot)) {
	get_slot_args = CDDR(operand);
	frame_arg_node = CAR(get_slot_args);
	slot_name = get_symbol_from_symbol_constant_node(CADR(get_slot_args));
	if (EQ(CADR(frame_arg_node),Qfetch_local) && 
		class_type_specification_p(CAR(frame_arg_node))) {
	    frame_class = M_CAR(M_CDR(CAR(frame_arg_node)));
	    temp = CDDR(frame_arg_node);
	    frame_arg_local_name = CAR(temp);
	    slot_type_specification_qm = 
		    get_slot_type_specification_of_g2_or_java_class(frame_class,
		    slot_name);
	    if (type_specification_subtype_p(slot_type_specification_qm,
		    target_type_specification))
		return jwrite_checked_field_reference(slot_name,
			frame_arg_local_name,frame_class);
	    else if ((EQUAL(slot_type_specification_qm,list_constant_5) || 
		    EQUAL(slot_type_specification_qm,list_constant_4)) && 
		    EQUAL(target_type_specification,list_constant_8))
		return jwrite_checked_field_reference(slot_name,
			frame_arg_local_name,frame_class);
	    else
		return jemit_error(tformat_text_string(1,string_constant_45));
	}
	else
	    return jemit_error(tformat_text_string(2,string_constant_46,
		    slot_name));
    }
    else if (type_specification_subtype_p(operand_type_specification,
	    target_type_specification)) {
	format((SI_Long)3L,T,"found unnecesssary cast~s~%",node);
	return jemit_compiled_gesture_expression_rec(operand);
    }
    else if (type_specifications_could_intersect_p(operand_type_specification,
	    target_type_specification))
	return jemit_cast_gesture_node(operand,target_type_specification);
    else if (EQ(operand_type_specification,Qinteger) && 
	    EQ(target_type_specification,Qfloat))
	return jemit_cast_gesture_node(operand,Qfloat);
    else if ((EQUAL(operand_type_specification,list_constant_5) || 
	    EQUAL(operand_type_specification,list_constant_4)) && 
	    EQUAL(target_type_specification,list_constant_8))
	return jemit_compiled_gesture_expression_rec(operand);
    else
	return jemit_error(tformat_text_string(3,string_constant_47,
		operand,target_type_specification));
}

static Object Qunary;              /* unary */

static Object array_constant_64;   /* # */

static Object array_constant_65;   /* # */

static Object array_constant_66;   /* # */

static Object string_constant_48;  /* "(" */

static Object string_constant_49;  /* ")" */

static Object string_constant_50;  /* "INTERNAL ERROR: unhandled cast ~NT" */

/* JEMIT-CAST-GESTURE-NODE */
Object jemit_cast_gesture_node(node,type_specification)
    Object node, type_specification;
{
    Object precedence, cast_string_qm, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object needs_parens_p;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(249,152);
    precedence = Qunary;
    if (SYMBOLP(type_specification)) {
	if (EQ(type_specification,Qinteger))
	    cast_string_qm = 
		    copy_constant_wide_string_given_length(array_constant_64,
		    FIX((SI_Long)5L));
	else if (EQ(type_specification,Qfloat))
	    cast_string_qm = 
		    copy_constant_wide_string_given_length(array_constant_65,
		    FIX((SI_Long)8L));
	else if (EQ(type_specification,Qtext))
	    cast_string_qm = 
		    copy_constant_wide_string_given_length(array_constant_66,
		    FIX((SI_Long)7L));
	else
	    cast_string_qm = Qnil;
    }
    else if (class_type_specification_p(type_specification)) {
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
		  tformat(1,string_constant_48);
		  jwrite_symbol(1,M_CAR(M_CDR(type_specification)));
		  tformat(1,string_constant_49);
		  cast_string_qm = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    else
	cast_string_qm = Qnil;
    needs_parens_p = operator_needs_parens_p(precedence);
    if ( !TRUEP(cast_string_qm))
	jemit_error(tformat_text_string(2,string_constant_50,
		type_specification));
    if (needs_parens_p)
	twrite_beginning_of_wide_string(array_constant_60,FIX((SI_Long)1L));
    twrite_general_string(cast_string_qm);
    reclaim_text_string(cast_string_qm);
    jemit_compiled_gesture_expression_rec(node);
    if (needs_parens_p)
	return twrite_beginning_of_wide_string(array_constant_48,
		FIX((SI_Long)1L));
    else
	return VALUES_1(Nil);
}

static Object string_constant_51;  /* "unknown slot, ~s, for class ~s " */

static Object string_constant_52;  /* "attribute/field access to non g2-defined classes is NYI" */

/* GET-SLOT-TYPE-SPECIFICATION-OF-G2-OR-JAVA-CLASS */
Object get_slot_type_specification_of_g2_or_java_class(class_name,slot_name)
    Object class_name, slot_name;
{
    Object class_description_qm, slot_description_qm;

    x_note_fn_call(249,153);
    class_description_qm = 
	    lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop);
    if (class_description_qm) {
	slot_description_qm = 
		get_slot_description_of_class_description_function(slot_name,
		class_description_qm,Nil);
	if (slot_description_qm)
	    return VALUES_1(ISVREF(slot_description_qm,(SI_Long)5L));
	else
	    return jemit_error(tformat_text_string(3,string_constant_51,
		    slot_name,class_name));
    }
    else
	return jemit_error(tformat_text_string(2,string_constant_52,
		slot_name));
}

/* GET-SYMBOL-FROM-SYMBOL-CONSTANT-NODE */
Object get_symbol_from_symbol_constant_node(node)
    Object node;
{
    Object temp;

    x_note_fn_call(249,154);
    if ( !EQ(CADR(node),Qsymbol_constant))
	error((SI_Long)2L,"not really a symbol-constant-node ~S",node);
    temp = CDDR(node);
    return VALUES_1(CAR(temp));
}

/* GET-TEXT-FROM-TEXT-CONSTANT-NODE */
Object get_text_from_text_constant_node(node)
    Object node;
{
    Object temp;

    x_note_fn_call(249,155);
    if ( !EQ(CADR(node),Qtext_constant))
	error((SI_Long)2L,"not really a text-constant-node ~S",node);
    temp = CDDR(node);
    return copy_text_string(CAR(temp));
}

static Object Qjava_operator_precedence;  /* java-operator-precedence */

/* OPERATOR-NEEDS-PARENS-P */
Object operator_needs_parens_p(precedence)
    Object precedence;
{
    Object outer_node_qm, outer_instruction_name_qm, temp;

    x_note_fn_call(249,156);
    outer_node_qm = CADR(Current_jemit_node_stack);
    outer_instruction_name_qm = outer_node_qm ? CADR(outer_node_qm) : Qnil;
    if (outer_instruction_name_qm) {
	temp = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(outer_instruction_name_qm),
		Qjava_operator_precedence);
	if (temp);
	else
	    temp = Qprimary;
	temp = java_operator_tighter_p(temp,precedence);
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qjava_operator_emitter_template;  /* java-operator-emitter-template */

static Object Qarg;                /* arg */

/* JEMIT-GESTURE-NODE-AS-OPERATOR */
Object jemit_gesture_node_as_operator(node,operator_1)
    Object node, operator_1;
{
    Object precedence, template_1, needs_parens_p, operand_spec, ab_loop_list_;
    Object temp;

    x_note_fn_call(249,157);
    precedence = getfq_function_no_default(INLINE_SYMBOL_PLIST(operator_1),
	    Qjava_operator_precedence);
    template_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(operator_1),
	    Qjava_operator_emitter_template);
    needs_parens_p = operator_needs_parens_p(precedence);
    if (needs_parens_p)
	twrite_beginning_of_wide_string(array_constant_60,FIX((SI_Long)1L));
    operand_spec = Nil;
    ab_loop_list_ = template_1;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    operand_spec = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (STRINGP(operand_spec) || text_string_p(operand_spec))
	twrite_general_string(operand_spec);
    else if (CONSP(operand_spec)) {
	temp = CAR(operand_spec);
	if (EQ(temp,Qarg))
	    jemit_compiled_gesture_expression_rec(nth(FIXNUM_SUB1(CADR(operand_spec)),
		    CDDR(node)));
    }
    goto next_loop;
  end_loop:;
    if (needs_parens_p)
	return twrite_beginning_of_wide_string(array_constant_48,
		FIX((SI_Long)1L));
    else
	return VALUES_1(Nil);
}

static Object Qfetch_local_or_no_item;  /* fetch-local-or-no-item */

static Object Qinteger_constant;   /* integer-constant */

static Object Qfloat_constant;     /* float-constant */

static Object Qlong_constant;      /* long-constant */

static Object string_constant_53;  /* "Symbol.intern(\"~A\")" */

static Object Qtruth_value_constant;  /* truth-value-constant */

static Object Qtrue;               /* true */

static Object array_constant_67;   /* # */

static Object Qfalse;              /* false */

static Object array_constant_68;   /* # */

static Object string_constant_54;  /* "Truth-Value constants (~a) not yet implemented" */

static Object string_constant_55;  /* "The value of (CADR NODE) (~s), is not one of (FETCH-LOCAL FETCH-LOCAL-OR-NO-ITEM INTEGER-CONSTANT FLOAT-CONSTANT LONG-CONSTANT SYMBOL-CONSTANT TEXT-CONSTANT TRUTH-VALUE-CONSTANT)." */

/* JEMIT-PRIMITIVE-GESTURE-VALUE-NODE */
Object jemit_primitive_gesture_value_node(node)
    Object node;
{
    Object args, temp, local_name, static_local_qm, write_strings_parsably_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(249,158);
    args = CDDR(node);
    temp = CADR(node);
    if (EQ(temp,Qfetch_local)) {
	local_name = CAR(args);
	temp = assq_function(local_name,Current_jemit_class_object_table);
	static_local_qm = CDR(temp);
	if (static_local_qm)
	    return twrite_general_string(static_local_qm);
	else
	    return jwrite_symbol(1,local_name);
    }
    else if (EQ(temp,Qfetch_local_or_no_item))
	return VALUES_1(Nil);
    else if (EQ(temp,Qinteger_constant))
	return twrite(CAR(args));
    else if (EQ(temp,Qfloat_constant))
	return twrite(CAR(args));
    else if (EQ(temp,Qlong_constant))
	return twrite(CAR(args));
    else if (EQ(temp,Qsymbol_constant))
	return tformat(2,string_constant_53,CAR(args));
    else if (EQ(temp,Qtext_constant)) {
	write_strings_parsably_qm = T;
	PUSH_SPECIAL_WITH_SYMBOL(Write_strings_parsably_qm,Qwrite_strings_parsably_qm,write_strings_parsably_qm,
		0);
	  result = twrite_general_string(CAR(args));
	POP_SPECIAL();
	return result;
    }
    else if (EQ(temp,Qtruth_value_constant)) {
	temp = CAR(args);
	if (EQ(temp,Qtrue))
	    return twrite_beginning_of_wide_string(array_constant_67,
		    FIX((SI_Long)4L));
	else if (EQ(temp,Qfalse))
	    return twrite_beginning_of_wide_string(array_constant_68,
		    FIX((SI_Long)5L));
	else
	    return jemit_error(tformat_text_string(2,string_constant_54,
		    CAR(args)));
    }
    else
	return errorn(2,string_constant_55,CADR(node));
}

void java1_INIT()
{
    Object temp, temp_1, temp_2, write_duplicate_class_export_note_1;
    Object com_edit_external_procedure_1;
    Object edit_external_procedure_command_pursuer_1;
    Object edit_external_procedure_command_translator_1;
    Object write_nonexistent_classes_for_export_note_1;
    Object write_nonexistent_static_methods_for_export_note_1;
    Object write_duplicate_class_export_in_single_item_note_1, gensymed_symbol;
    Object reclaim_structure_for_java_symbol_1;
    Object reclaim_structure_for_java_class_1;
    Object reclaim_structure_for_java_descriptor_1;
    Object reclaim_structure_for_java_field_1;
    Object reclaim_structure_for_java_method_1;
    Object reclaim_structure_for_java_code_exception_1;
    Object reclaim_structure_for_java_code_1;
    Object reclaim_structure_for_class_file_stream_1;
    Object list_constant_13, AB_package, Qarray_length, list_constant_41;
    Object string_constant_159, list_constant_21, Qarray_element;
    Object Qnth_sequence_element, list_constant_40, string_constant_158;
    Object list_constant_22, string_constant_157, Qconditional, Qif_expression;
    Object list_constant_39, list_constant_38, string_constant_156;
    Object string_constant_155, Qless_than_equal, Qless_than_equal_fixnum;
    Object Qgreater_than_equal_quantity, list_constant_37, list_constant_25;
    Object Qrelational, Qless_than, Qless_than_fixnum, Qless_than_quantity;
    Object list_constant_36, string_constant_154, Qgreater_than_equal;
    Object Qgreater_than_equal_fixnum, list_constant_35, Qgreater_than;
    Object Qgreater_than_fixnum, Qgreater_than_quantity, list_constant_34;
    Object string_constant_153, Qequal_fixnum, Qequal_quantity;
    Object list_constant_33, string_constant_152, Qequality, Qbitwise_and;
    Object list_constant_32, string_constant_151, Qbitwise_or;
    Object list_constant_31, string_constant_150, Qior, Qnegate, Qnegate_float;
    Object Qnegate_quantity, Qnegate_fixnum, list_constant_30;
    Object list_constant_29, string_constant_149, Qremainder, Qremainder_float;
    Object Qremainder_quantity, Qremainder_fixnum, list_constant_28;
    Object string_constant_148, Qmultiplicative, Qdivide, Qdivide_float;
    Object Qdivide_fixnum, list_constant_27, Qquotient, Qquotient_float;
    Object Qquotient_quantity, Qquotient_fixnum, string_constant_147;
    Object Qmultiply, Qmultiply_float, Qmultiply_quantity, Qmultiply_fixnum;
    Object list_constant_26, string_constant_146, Qsubtract, Qsubtract_float;
    Object Qsubtract_quantity, Qsubtract_fixnum, list_constant_24;
    Object string_constant_145, Qadditive, Qg2_add, Qadd_float, Qadd_quantity;
    Object Qadd_fixnum, list_constant_23, string_constant_144;
    Object list_constant_20, Qconditional_or, Qconditional_and, Qab_xor;
    Object Qshift, Qpostfix, list_constant_19, Qitem_or_datum, Qno_item;
    Object Qg2_emit_class_as_java;
    Object Qfunction_keeps_procedure_environment_valid_qm, Qclass_file_stream;
    Object Qreclaim_structure, Qoutstanding_class_file_stream_count;
    Object Qclass_file_stream_structure_memory_usage, Qutilities2;
    Object string_constant_143, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_142, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qjava_code;
    Object Qoutstanding_java_code_count, Qjava_code_structure_memory_usage;
    Object string_constant_141, string_constant_140, Qjava_code_exception;
    Object Qoutstanding_java_code_exception_count;
    Object Qjava_code_exception_structure_memory_usage, string_constant_139;
    Object string_constant_138, Qjava_method, Qoutstanding_java_method_count;
    Object Qjava_method_structure_memory_usage, string_constant_137;
    Object string_constant_136, Qjava_field, Qoutstanding_java_field_count;
    Object Qjava_field_structure_memory_usage, string_constant_135;
    Object string_constant_134, Qjava_descriptor;
    Object Qoutstanding_java_descriptor_count;
    Object Qjava_descriptor_structure_memory_usage, string_constant_133;
    Object string_constant_132, Qjava_class, Qoutstanding_java_class_count;
    Object Qjava_class_structure_memory_usage, string_constant_131;
    Object string_constant_130, Qjava_symbol, Qoutstanding_java_symbol_count;
    Object Qjava_symbol_structure_memory_usage, string_constant_129;
    Object string_constant_128, Qg2_export_definitions_system_rpc_internal;
    Object Qg2_export_definitions, Qsystem_defined_rpc, list_constant_18;
    Object list_constant_17, list_constant_16, string_constant_127;
    Object string_constant_126, string_constant_125, string_constant_124;
    Object string_constant_123, string_constant_122, Qslot_value_writer;
    Object Qwrite_export_definition_specification_from_slot;
    Object Qclasses_which_define, Qcleanup, Qcleanup_for_export_definition;
    Object Qslot_putter, Qput_export_definition_specification;
    Object Qframe_note_writer_1, Qanalyze_for_consistency;
    Object Qanalyze_for_consistency_for_export_definition;
    Object Qnonexistent_static_methods_for_export;
    Object Qnonexistent_classes_for_export;
    Object Qwrite_read_only_instance_methods_from_slot;
    Object Qread_only_instance_methods;
    Object Qwrite_export_definition_language_from_slot, Qslot_value_reclaimer;
    Object Qreclaim_visible_class_export_information_qm_value;
    Object Qvisible_class_export_information_qm, Qjava_methods;
    Object Qexport_specification, Qexport_language, string_constant_121;
    Object string_constant_120, string_constant_119, string_constant_118;
    Object string_constant_117, string_constant_116, string_constant_115;
    Object string_constant_114, string_constant_113, string_constant_112;
    Object string_constant_111, list_constant_15, Qcreate_icon_description;
    Object string_constant_110, string_constant_109, string_constant_108;
    Object string_constant_107, string_constant_106, string_constant_105;
    Object string_constant_104, string_constant_103, string_constant_102;
    Object string_constant_101, string_constant_89, string_constant_100;
    Object string_constant_99, string_constant_98, list_constant_14, Qitem;
    Object Qentity, Qedit, list_constant_12, Qduplicate_class_export;
    Object Qput_external_procedure_definition, Qwrite_tw_method_name_from_slot;
    Object Qtw_method_name, Qqualified_name, string_constant_97;
    Object string_constant_96, string_constant_95, string_constant_94;
    Object string_constant_93, Qicon_color, string_constant_92;
    Object string_constant_91, string_constant_90, string_constant_88;
    Object string_constant_87, string_constant_57, Qinitialize;
    Object Qinitialize_for_external_method_declaration, string_constant_86;
    Object string_constant_85, string_constant_84, string_constant_83;
    Object string_constant_82, string_constant_81, string_constant_80;
    Object string_constant_79, string_constant_78, string_constant_77;
    Object string_constant_76, string_constant_75;
    Object Qcleanup_for_external_procedure, Qinitialize_for_external_procedure;
    Object string_constant_74, string_constant_73, string_constant_72;
    Object string_constant_71, string_constant_70, string_constant_69;
    Object list_constant_11, string_constant_68, string_constant_67;
    Object string_constant_66, string_constant_65, string_constant_64;
    Object string_constant_63, string_constant_62, string_constant_61;
    Object string_constant_60, string_constant_59, string_constant_58;
    Object string_constant_56, Qjava_cons_memory_usage;
    Object Qoutstanding_java_conses, Qutilities1, list_constant_10;
    Object Qjava_cons_counter_vector, Qmake_thread_array, list_constant_9;
    Object Qavailable_java_conses_tail_vector, Qavailable_java_conses_vector;

    x_note_fn_call(249,159);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qavailable_java_conses = STATIC_SYMBOL("AVAILABLE-JAVA-CONSES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_java_conses,Available_java_conses);
    Qutilities1 = STATIC_SYMBOL("UTILITIES1",AB_package);
    record_system_variable(Qavailable_java_conses,Qutilities1,Nil,Qnil,Qt,
	    Qnil,Qnil);
    Qavailable_java_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-JAVA-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_java_conses_tail,
	    Available_java_conses_tail);
    record_system_variable(Qavailable_java_conses_tail,Qutilities1,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_java_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-JAVA-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_java_conses_vector,
	    Available_java_conses_vector);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_thread_array = STATIC_SYMBOL("MAKE-THREAD-ARRAY",AB_package);
    list_constant_9 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    Qnil);
    record_system_variable(Qavailable_java_conses_vector,Qutilities1,
	    list_constant_9,Qnil,Qt,Qnil,Qnil);
    Qavailable_java_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-JAVA-CONSES-TAIL-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_java_conses_tail_vector,
	    Available_java_conses_tail_vector);
    record_system_variable(Qavailable_java_conses_tail_vector,Qutilities1,
	    list_constant_9,Qnil,Qt,Qnil,Qnil);
    Qjava_cons_counter_vector = STATIC_SYMBOL("JAVA-CONS-COUNTER-VECTOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qjava_cons_counter_vector,
	    Java_cons_counter_vector);
    list_constant_10 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    FIX((SI_Long)0L));
    record_system_variable(Qjava_cons_counter_vector,Qutilities1,
	    list_constant_10,Qnil,Qt,Qnil,Qnil);
    Qjava_cons_counter = STATIC_SYMBOL("JAVA-CONS-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qjava_cons_counter,Java_cons_counter);
    record_system_variable(Qjava_cons_counter,Qutilities1,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    Qoutstanding_java_conses = STATIC_SYMBOL("OUTSTANDING-JAVA-CONSES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_java_conses,
	    STATIC_FUNCTION(outstanding_java_conses,NIL,FALSE,0,0));
    Qjava_cons_memory_usage = STATIC_SYMBOL("JAVA-CONS-MEMORY-USAGE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qjava_cons_memory_usage,
	    STATIC_FUNCTION(java_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_56 = STATIC_STRING("1q83-bOy9k83-bNy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_java_conses);
    push_optimized_constant(Qjava_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_56));
    Qjava = STATIC_SYMBOL("JAVA",AB_package);
    Qexternal_procedure = STATIC_SYMBOL("EXTERNAL-PROCEDURE",AB_package);
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    list_constant_11 = STATIC_LIST((SI_Long)2L,Qblock,Qentity);
    check_if_superior_classes_are_defined(Qexternal_procedure,
	    list_constant_11);
    string_constant_57 = STATIC_STRING("1l1l8t");
    Qcreate_icon_description = STATIC_SYMBOL("CREATE-ICON-DESCRIPTION",
	    AB_package);
    Qicon_color = STATIC_SYMBOL("ICON-COLOR",AB_package);
    string_constant_58 = 
	    STATIC_STRING("1r4z8r83--y83--y8358y8358y00001p1l8l1m8p83-*y1l83Ey1l83Uy1m83Dy53*syWill allow 0 or more author entries. each author entry may h");
    string_constant_59 = 
	    STATIC_STRING("ave a date. ~\nauthors: ([ name: symbol, date: gensym-time ] * ), editor-grammar: struct, defining-class: item, writable: true\n00");
    string_constant_60 = 
	    STATIC_STRING("0004z8r83-0y83-0y8358y8358y00001q1l8l1m8p83-0y1l83Fy1l83Ey1l83Uy1m83Dy53-Fy(to replace authors attribute; however, no documentat");
    string_constant_61 = 
	    STATIC_STRING("ion is available at this time)000004z8r83-Fy83-Fy8358y8358y00001q1l8l1m8p01l83Cy1l83Uy1l83*-y1m83Dy53MySee comment in class bloc");
    string_constant_62 = 
	    STATIC_STRING("k000004z8r8u8u8358y8358y01p8w9k3uy3uy1y1r83-1y2l83-Ly83-Wy2l83-ny83-gy2l83-my83-Ry2l9l83Ty2l83=-y83fy2l83=*y83*Gy83-Ly1n83jy1mkk");
    string_constant_63 = 
	    STATIC_STRING("1m3ky3ky83-ny1q83qy1q1mkk1m3kyk1m3hyn1mnn1mn3hy1mk3ky1n1mkk1m3kyk1m3hyn1n1mnn1mn3hy1mk3ky1n1mkk1m3hyn1mnn1n1mnn1mk3ky1mkk83-my1q");
    string_constant_64 = 
	    STATIC_STRING("83qy1q1m3hyn1m3kyk1m3ky3ky1mk3ky1mn3hy1m3hy3hy1n1m3hyn1m3kyk1m3ky3ky1n1m3ky3ky1mk3ky1mn3hy1n1m3hy3hy1m3hyn1m3ky3ky1n1m3ky3ky1mn3");
    string_constant_65 = 
	    STATIC_STRING("hy1m3hy3hy9l1p83Jy1mkk1mk3ky1m3ky3ky1m3kyk1o83Gy+s3-1y3-qy3-my3Zy3-eykp3A++y1ms3Hy83-Vy1o83Gy+s3-Cy3-ky3-hy3-Vykko3A++y1ms3Yy83-");
    string_constant_66 = 
	    STATIC_STRING("Vy1o83Oy1m3eyp1mpp1mp3fy83-ny1o83Oy1mp3fy1m3ey3fy1m3eyp001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class definition000004z8r");
    string_constant_67 = 
	    STATIC_STRING("8359y8359y8358y8358y00001q1n8p83Q2y83Gy1l8o1l8l1l83Cy1l83-3y1l83Uy000004z8r83L*y83L*y8358y8358y00001m1l8o1l8l000004z8r83L=y83L=y");
    string_constant_68 = STATIC_STRING("8358y8358y00001m1l8o1l8l00000");
    string_constant_69 = 
	    STATIC_STRING("1t8q1n8358y1m9k83-+y8t1n83--y01m8p83-*y1n83-0y01m8p83-0y1p83-Fy08l1m8p083Cy1m8u1p8w9l3uy3uy1y1r83-1y2l83-Ly83-Wy2l83-ny83-gy2l83");
    string_constant_70 = 
	    STATIC_STRING("-my83-Ry2l9m83Ty2l83=-y83fy2l83=*y83*Gy83-Ly1n83jy1mkk1m3ky3ky83-ny1q83qy1q1mkk1m3kyk1m3hyn1mnn1mn3hy1mk3ky1n1mkk1m3kyk1m3hyn1n1");
    string_constant_71 = 
	    STATIC_STRING("mnn1mn3hy1mk3ky1n1mkk1m3hyn1mnn1n1mnn1mk3ky1mkk83-my1q83qy1q1m3hyn1m3kyk1m3ky3ky1mk3ky1mn3hy1m3hy3hy1n1m3hyn1m3kyk1m3ky3ky1n1m3k");
    string_constant_72 = 
	    STATIC_STRING("y3ky1mk3ky1mn3hy1n1m3hy3hy1m3hyn1m3ky3ky1n1m3ky3ky1mn3hy1m3hy3hy9m1p83Jy1mkk1mk3ky1m3ky3ky1m3kyk1o83Gy5pExt\'l1ms3Hy83-Vy1o83Gy5o");
    string_constant_73 = 
	    STATIC_STRING("Proc1ms3Yy83-Vy1o83Oy1m3eyp1mpp1mp3fy83-ny1o83Oy1mp3fy1m3ey3fy1m3eyp1s8359y01n8p83Q2y83Gy8o8l83Cy83-3y83Uy1o83L*y08o8l1o83L=y08o");
    string_constant_74 = STATIC_STRING("8l");
    temp = regenerate_optimized_constant(string_constant_57);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    push_optimized_constant(Qicon_color);
    temp_1 = regenerate_optimized_constant(list(11,string_constant_58,
	    string_constant_59,string_constant_60,string_constant_61,
	    string_constant_62,string_constant_63,string_constant_64,
	    string_constant_65,string_constant_66,string_constant_67,
	    string_constant_68));
    clear_optimized_constants();
    push_optimized_constant(Qblock);
    push_optimized_constant(Qcreate_icon_description);
    push_optimized_constant(Qicon_color);
    add_class_to_environment(9,Qexternal_procedure,list_constant_11,Nil,
	    temp,Nil,temp_1,list_constant_11,
	    regenerate_optimized_constant(list(6,string_constant_69,
	    string_constant_70,string_constant_71,string_constant_72,
	    string_constant_73,string_constant_74)),Nil);
    Qexternal_method_declaration = 
	    STATIC_SYMBOL("EXTERNAL-METHOD-DECLARATION",AB_package);
    Qincomplete = STATIC_SYMBOL("INCOMPLETE",AB_package);
    Qinitialize_for_external_procedure = 
	    STATIC_SYMBOL("INITIALIZE-FOR-EXTERNAL-PROCEDURE",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_external_procedure,
	    STATIC_FUNCTION(initialize_for_external_procedure,NIL,FALSE,1,1));
    Qinitialize = STATIC_SYMBOL("INITIALIZE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qinitialize_for_external_procedure);
    set_get(Qexternal_procedure,Qinitialize,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp_2 = CONS(Qexternal_procedure,temp);
    mutate_global_property(Qinitialize,temp_2,Qclasses_which_define);
    Qcleanup_for_external_procedure = 
	    STATIC_SYMBOL("CLEANUP-FOR-EXTERNAL-PROCEDURE",AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_external_procedure,
	    STATIC_FUNCTION(cleanup_for_external_procedure,NIL,FALSE,1,1));
    Qcleanup = STATIC_SYMBOL("CLEANUP",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qcleanup_for_external_procedure);
    set_get(Qexternal_procedure,Qcleanup,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_2 = CONS(Qexternal_procedure,temp);
    mutate_global_property(Qcleanup,temp_2,Qclasses_which_define);
    list_constant_12 = STATIC_CONS(Qexternal_procedure,Qnil);
    check_if_superior_classes_are_defined(Qexternal_method_declaration,
	    list_constant_12);
    string_constant_75 = 
	    STATIC_STRING("1n4z8r83-Fy83-Fy83L+y83L+y00001q1l8l1m8p83-ky1l83Cy1l83Uy1l83*-y1m83Dy53MySee comment in class block000004z8r8u8u83L+y83L+y01p8w");
    string_constant_76 = 
	    STATIC_STRING("9k3uy3uy1y1r83-1y2l83-Ly83-Wy2l83-ny83-gy2l83-my83-Ry2l9l83Ty2l83=-y83fy2l83=*y83*Gy83-Ly1n83jy1mkk1m3ky3ky83-ny1q83qy1q1mkk1m3k");
    string_constant_77 = 
	    STATIC_STRING("yk1m3hyn1mnn1mn3hy1mk3ky1n1mkk1m3kyk1m3hyn1n1mnn1mn3hy1mk3ky1n1mkk1m3hyn1mnn1n1mnn1mk3ky1mkk83-my1q83qy1q1m3hyn1m3kyk1m3ky3ky1mk");
    string_constant_78 = 
	    STATIC_STRING("3ky1mn3hy1m3hy3hy1n1m3hyn1m3kyk1m3ky3ky1n1m3ky3ky1mk3ky1mn3hy1n1m3hy3hy1m3hyn1m3ky3ky1n1m3ky3ky1mn3hy1m3hy3hy9l1p83Jy1mkk1mk3ky1");
    string_constant_79 = 
	    STATIC_STRING("m3ky3ky1m3kyk1o83Gy+s3-1y3-qy3-my3Zy3-eykp3A++y1ms3Hy83-Vy1o83Gy+s3-0y3-Xy3-Vy3-eykko3A++y1ms3ay83-Vy1o83Oy1m3eyp1mpp1mp3fy83-ny");
    string_constant_80 = 
	    STATIC_STRING("1o83Oy1mp3fy1m3ey3fy1m3eyp001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class definition000004z8r8359y8359y83L+y83L+y00001s1m8");
    string_constant_81 = 
	    STATIC_STRING("p01l8o1l8l1l83Cy1l83Cy1l83-3y1l83-5y1l83Uy00000");
    string_constant_82 = 
	    STATIC_STRING("1p8q1n83L+y1l8358y8t1p83-Fy08l1m8p83-ky83Cy1m8u1p8w9k3uy3uy1y1r83-1y2l83-Ly83-Wy2l83-ny83-gy2l83-my83-Ry2l9l83Ty2l83=-y83fy2l83=");
    string_constant_83 = 
	    STATIC_STRING("*y83*Gy83-Ly1n83jy1mkk1m3ky3ky83-ny1q83qy1q1mkk1m3kyk1m3hyn1mnn1mn3hy1mk3ky1n1mkk1m3kyk1m3hyn1n1mnn1mn3hy1mk3ky1n1mkk1m3hyn1mnn1");
    string_constant_84 = 
	    STATIC_STRING("n1mnn1mk3ky1mkk83-my1q83qy1q1m3hyn1m3kyk1m3ky3ky1mk3ky1mn3hy1m3hy3hy1n1m3hyn1m3kyk1m3ky3ky1n1m3ky3ky1mk3ky1mn3hy1n1m3hy3hy1m3hyn");
    string_constant_85 = 
	    STATIC_STRING("1m3ky3ky1n1m3ky3ky1mn3hy1m3hy3hy9l1p83Jy1mkk1mk3ky1m3ky3ky1m3kyk1o83Gy5pExt\'l1ms3Hy83-Vy1o83Gy5oDecl1ms3ay83-Vy1o83Oy1m3eyp1mpp1");
    string_constant_86 = 
	    STATIC_STRING("mp3fy83-ny1o83Oy1mp3fy1m3ey3fy1m3eyp1t8359y01m8p08o8l83Cy83Cy83-3y83-5y");
    temp = regenerate_optimized_constant(string_constant_57);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    push_optimized_constant(Qicon_color);
    temp_1 = regenerate_optimized_constant(list(7,string_constant_75,
	    string_constant_76,string_constant_77,string_constant_78,
	    string_constant_79,string_constant_80,string_constant_81));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    push_optimized_constant(Qicon_color);
    add_class_to_environment(9,Qexternal_method_declaration,
	    list_constant_12,Nil,temp,Nil,temp_1,list_constant_12,
	    regenerate_optimized_constant(LIST_5(string_constant_82,
	    string_constant_83,string_constant_84,string_constant_85,
	    string_constant_86)),Nil);
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qinitialize_for_external_method_declaration = 
	    STATIC_SYMBOL("INITIALIZE-FOR-EXTERNAL-METHOD-DECLARATION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_external_method_declaration,
	    STATIC_FUNCTION(initialize_for_external_method_declaration,NIL,
	    FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qinitialize_for_external_method_declaration);
    set_get(Qexternal_method_declaration,Qinitialize,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp_2 = CONS(Qexternal_method_declaration,temp);
    mutate_global_property(Qinitialize,temp_2,Qclasses_which_define);
    Qexternal_method = STATIC_SYMBOL("EXTERNAL-METHOD",AB_package);
    check_if_superior_classes_are_defined(Qexternal_method,list_constant_12);
    string_constant_87 = 
	    STATIC_STRING("1n4z8r8u8u83Kwy83Kwy01p8w9k3uy3uy1y1r83-1y2l83-Ly83-Wy2l83-ny83-gy2l83-my83-Ry2l9l83Ty2l83=-y83fy2l83=*y83*Gy83-Ly1n83jy1mkk1m3k");
    string_constant_88 = 
	    STATIC_STRING("y3ky83-ny1q83qy1q1mkk1m3kyk1m3hyn1mnn1mn3hy1mk3ky1n1mkk1m3kyk1m3hyn1n1mnn1mn3hy1mk3ky1n1mkk1m3hyn1mnn1n1mnn1mk3ky1mkk83-my1q83qy");
    string_constant_89 = 
	    STATIC_STRING("1q1m3hyn1m3kyk1m3ky3ky1mk3ky1mn3hy1m3hy3hy1n1m3hyn1m3kyk1m3ky3ky1n1m3ky3ky1mk3ky1mn3hy1n1m3hy3hy1m3hyn1m3ky3ky1n1m3ky3ky1mn3hy1m");
    string_constant_90 = 
	    STATIC_STRING("3hy3hy9l1p83Jy1mkk1mk3ky1m3ky3ky1m3kyk1o83Gy+s3-1y3-qy3-my3Zy3-eykp3A++y1ms3Hy83-Vy1o83Gy+s3-9y3-Xy3-my3-aykko3A++y1mt3ay83-Vy1o");
    string_constant_91 = 
	    STATIC_STRING("83Oy1m3eyp1mpp1mp3fy83-ny1o83Oy1mp3fy1m3ey3fy1m3eyp001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class definition000004z8r83L-");
    string_constant_92 = 
	    STATIC_STRING("y83L-y83Kwy83Kwy00001p1l8o1l8l1l83Cy1l83Fy1m8p83cpy000004z8r83Kxy83Kxy83Kwy83Kwy00001n1l8o1l8l1l83Cy00000");
    string_constant_93 = 
	    STATIC_STRING("1p8q1n83Kwy1l8358y8t1m8u1p8w9k3uy3uy1y1r83-1y2l83-Ly83-Wy2l83-ny83-gy2l83-my83-Ry2l9l83Ty2l83=-y83fy2l83=*y83*Gy83-Ly1n83jy1mkk1");
    string_constant_94 = 
	    STATIC_STRING("m3ky3ky83-ny1q83qy1q1mkk1m3kyk1m3hyn1mnn1mn3hy1mk3ky1n1mkk1m3kyk1m3hyn1n1mnn1mn3hy1mk3ky1n1mkk1m3hyn1mnn1n1mnn1mk3ky1mkk83-my1q8");
    string_constant_95 = 
	    STATIC_STRING("3qy1q1m3hyn1m3kyk1m3ky3ky1mk3ky1mn3hy1m3hy3hy1n1m3hyn1m3kyk1m3ky3ky1n1m3ky3ky1mk3ky1mn3hy1n1m3hy3hy1m3hyn1m3ky3ky1n1m3ky3ky1mn3h");
    string_constant_96 = 
	    STATIC_STRING("y1m3hy3hy9l1p83Jy1mkk1mk3ky1m3ky3ky1m3kyk1o83Gy5pExt\'l1ms3Hy83-Vy1o83Gy5oMeth1mt3ay83-Vy1o83Oy1m3eyp1mpp1mp3fy83-ny1o83Oy1mp3fy1");
    string_constant_97 = 
	    STATIC_STRING("m3ey3fy1m3eyp1r83L-y08o8l83Cy83Fy1m8p83cpy1p83Kxy08o8l83Cy");
    temp = regenerate_optimized_constant(string_constant_57);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    push_optimized_constant(Qicon_color);
    temp_1 = regenerate_optimized_constant(list(6,string_constant_87,
	    string_constant_88,string_constant_89,string_constant_90,
	    string_constant_91,string_constant_92));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    push_optimized_constant(Qicon_color);
    add_class_to_environment(9,Qexternal_method,list_constant_12,Nil,temp,
	    Nil,temp_1,list_constant_12,
	    regenerate_optimized_constant(LIST_5(string_constant_93,
	    string_constant_94,string_constant_95,string_constant_96,
	    string_constant_97)),Nil);
    Qexternal_method_name = STATIC_SYMBOL("EXTERNAL-METHOD-NAME",AB_package);
    Qqualified_name = STATIC_SYMBOL("QUALIFIED-NAME",AB_package);
    alias_slot_name(3,Qexternal_method_name,Qqualified_name,Qexternal_method);
    string_constant = STATIC_STRING("~(~nq~)");
    list_constant_13 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    Qtw_method_name = STATIC_SYMBOL("TW-METHOD-NAME",AB_package);
    Qwrite_tw_method_name_from_slot = 
	    STATIC_SYMBOL("WRITE-TW-METHOD-NAME-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_tw_method_name_from_slot,
	    STATIC_FUNCTION(write_tw_method_name_from_slot,NIL,FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qtw_method_name,
	    SYMBOL_FUNCTION(Qwrite_tw_method_name_from_slot),
	    Qslot_value_writer);
    Qexternal_procedure_definition = 
	    STATIC_SYMBOL("EXTERNAL-PROCEDURE-DEFINITION",AB_package);
    Qframe_status_and_notes = STATIC_SYMBOL("FRAME-STATUS-AND-NOTES",
	    AB_package);
    Qstack_change = STATIC_SYMBOL("STACK-CHANGE",AB_package);
    Qexternal_method_class = STATIC_SYMBOL("EXTERNAL-METHOD-CLASS",AB_package);
    Qput_external_procedure_definition = 
	    STATIC_SYMBOL("PUT-EXTERNAL-PROCEDURE-DEFINITION",AB_package);
    SET_SYMBOL_FUNCTION(Qput_external_procedure_definition,
	    STATIC_FUNCTION(put_external_procedure_definition,NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qexternal_procedure_definition,
	    SYMBOL_FUNCTION(Qput_external_procedure_definition),Qslot_putter);
    Qduplicate_class_export = STATIC_SYMBOL("DUPLICATE-CLASS-EXPORT",
	    AB_package);
    Qframe_note_writer_1 = STATIC_SYMBOL("FRAME-NOTE-WRITER-1",AB_package);
    array_constant_1 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)16L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)17L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)19L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)20L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)21L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)24L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)25L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)26L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)27L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)28L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)29L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)30L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)31L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)32L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)33L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)34L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)35L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)36L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)37L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)38L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)39L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)40L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)41L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)42L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)43L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)44L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)46L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)47L,(SI_Long)57344L);
    array_constant_2 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)57344L);
    Qtwrite = STATIC_SYMBOL("TWRITE",AB_package);
    string_constant_1 = STATIC_STRING(" and ");
    string_constant_2 = STATIC_STRING(", ");
    string_constant_3 = STATIC_STRING("the class ~A");
    write_duplicate_class_export_note_1 = 
	    STATIC_FUNCTION(write_duplicate_class_export_note,NIL,FALSE,2,2);
    mutate_global_property(Qduplicate_class_export,
	    write_duplicate_class_export_note_1,Qframe_note_writer_1);
    Qedit_external_procedure = STATIC_SYMBOL("EDIT-EXTERNAL-PROCEDURE",
	    AB_package);
    Qedit = STATIC_SYMBOL("EDIT",AB_package);
    make_ui_command(5,Qedit_external_procedure,list_constant_12,Qnil,Qedit,
	    Qnil);
    com_edit_external_procedure_1 = 
	    STATIC_FUNCTION(com_edit_external_procedure,NIL,FALSE,1,1);
    set_ui_command_function(Qedit_external_procedure,
	    com_edit_external_procedure_1);
    edit_external_procedure_command_pursuer_1 = 
	    STATIC_FUNCTION(edit_external_procedure_command_pursuer,NIL,
	    FALSE,1,1);
    set_ui_command_pursuer(Qedit_external_procedure,
	    edit_external_procedure_command_pursuer_1);
    edit_external_procedure_command_translator_1 = 
	    STATIC_FUNCTION(edit_external_procedure_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qedit_external_procedure,
	    edit_external_procedure_command_translator_1);
    Qexport_definition = STATIC_SYMBOL("EXPORT-DEFINITION",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    list_constant_14 = STATIC_CONS(Qentity,Qnil);
    list_constant_15 = STATIC_CONS(Qitem,list_constant_14);
    check_if_superior_classes_are_defined(Qexport_definition,list_constant_15);
    string_constant_98 = STATIC_STRING("1m1l83Iy1l8t");
    string_constant_99 = 
	    STATIC_STRING("1q4z8r8u8u83Ksy83Ksy01p8w9k3ky3ky13Xy1z83-1y2l83-Ly83-Wy2l83-my83-Ry2l83-ny83-gy2l835Jy83Ty2l83UAy8334y2l83U9y83*Gy2l83UBy83fy2l");
    string_constant_100 = 
	    STATIC_STRING("83UCy83*Gy2l83UEy83fy2l83UDy83-gy2l83UFy83-Ry2l83aJy83fy2l835by83*2y2l835ay832Vy1l83-iy1l83-jy83-Ly1n83jy1mkk1m3ky3ky83-my1q83qy");
    string_constant_101 = 
	    STATIC_STRING("3hy3hy83-ny1o83Oy1mp3fy1m3ey3fy1m3eyp835Jy1p83Jy1mkk1mk3ky1m3ky3ky1m3kyk1o83Oy1m3eyp1mpp1mp3fy83aJy1r83qy1r1m3Ny3Ey1m3Ny3Oy1m3Ry");
    string_constant_102 = 
	    STATIC_STRING("3Oy1m3Ly3Ty1m3Fy3Oy1m3Jy3Oy1m3Jy3Ey1n1m3Ny3Oy1m3Ry3Oy1m3Ly3Ty1n1m3Ly3Ty1m3Ny3Ey1m3Ny3Oy1n1m3Ly3Ty1m3Fy3Oy1m3Jy3Oy1n1m3Jy3Oy1m3Jy");
    string_constant_103 = 
	    STATIC_STRING("3Ey1m3Ny3Ey1n1m3Ny3Ey1m3Ly3Ty1m3Jy3Oy83UAy1n83qy1n1m3Cyr1m3Cy3Hy1ms3Hy1n1m3Cyr1m3Cy3Hy1ms3Hy83U9y1n83qy1n1ms3Hy1m3Cyz1m3Ky3Hy1n1");
    string_constant_104 = 
	    STATIC_STRING("ms3Hy1m3Cyz1m3Ky3Hy83UBy1p83Oy1ms3Hy1m3Cyr1m3Ky3Hy1ms3Hy83UCy1n83jy1m3Jyt1m3Yy3Jy83UEy1p83Jy1m3Py3Gy1m3Py3Iy1m3Wy3Iy1m3Wy3Gy1p83");
    string_constant_105 = 
	    STATIC_STRING("Jy1m3Ly3Dy1m3Ly3Fy1m3Sy3Fy1m3Sy3Dy1p83Jy1m3Pyy1m3Py3Cy1m3Wy3Cy1m3Wyy1p83Jy1m3Lyv1m3Lyx1m3Syx1m3Syv1p83Jy1m3Iys1m3Iy3Ky1m3Zy3Ky1m");
    string_constant_106 = 
	    STATIC_STRING("3Zys83UDy1o83Oy1m3Yyt1m3Jyt1m3Jy3Jy83UFy1o83Oy1m3Yyt1m3Yy3Jy1m3Jy3Jy835by1o83Gy+s3-6y3-Ty3-oy3-Tykko3A++y1mt3dy83-Vy835ay1o83Gy+");
    string_constant_107 = 
	    STATIC_STRING("s3-6y3-Ty3-oy3-Tykko3A++y1mt3cy83-Vy1o83Gy+s3-6y3-Ty3-oy3-Tykko3A++y1ms3cy83-Vy001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY c");
    string_constant_108 = 
	    STATIC_STRING("lass definition000004z8r83Bxy83Bxy83Ksy83Ksy083DBy001m1l8l1m8p83Bxy000004z8r83C+y83C+y83Ksy83Ksy00001m1l8l1m8p83C+y000004z8r83e0");
    string_constant_109 = 
	    STATIC_STRING("y83e0y83Ksy83Ksy00001n1l8l1l83Hy1l83Ny000004z8r83N-y83N-y83Ksy83Ksy00001p1m8p83YYy1l8o1l8l1l83Hy1l83Fy000004z8r83GUy83GUy83Ksy83");
    string_constant_110 = 
	    STATIC_STRING("Ksy00001o1n8p83DCy83Gy1l8o1l8l1l83Cy00000");
    string_constant_111 = 
	    STATIC_STRING("1s8q1o83Ksy1m83Ry83-+y83Iy8t1m8u1p8w9k3ky3ky13Xy1z83-1y2l83-Ly83-Wy2l83-my83-Ry2l83-ny83-gy2l835Jy83Ty2l83UAy8334y2l83U9y83*Gy2l");
    string_constant_112 = 
	    STATIC_STRING("83UBy83fy2l83UCy83*Gy2l83UEy83fy2l83UDy83-gy2l83UFy83-Ry2l83aJy83fy2l835by83*2y2l835ay832Vy1l83-iy1l83-jy83-Ly1n83jy1mkk1m3ky3ky");
    string_constant_113 = 
	    STATIC_STRING("83-my1q83qy1q1m3hyn1m3kyk1m3ky3ky1mk3ky1mn3hy1m3hy3hy1n1m3hyn1m3kyk1m3ky3ky1n1m3ky3ky1mk3ky1mn3hy1n1m3hy3hy1m3hyn1m3ky3ky1n1m3ky");
    string_constant_114 = 
	    STATIC_STRING("3ky1mn3hy1m3hy3hy83-ny1o83Oy1mp3fy1m3ey3fy1m3eyp835Jy1p83Jy1mkk1mk3ky1m3ky3ky1m3kyk1o83Oy1m3eyp1mpp1mp3fy83aJy1r83qy1r1m3Ny3Ey1m");
    string_constant_115 = 
	    STATIC_STRING("3Ny3Oy1m3Ry3Oy1m3Ly3Ty1m3Fy3Oy1m3Jy3Oy1m3Jy3Ey1n1m3Ny3Oy1m3Ry3Oy1m3Ly3Ty1n1m3Ly3Ty1m3Ny3Ey1m3Ny3Oy1n1m3Ly3Ty1m3Fy3Oy1m3Jy3Oy1n1m");
    string_constant_116 = 
	    STATIC_STRING("3Jy3Oy1m3Jy3Ey1m3Ny3Ey1n1m3Ny3Ey1m3Ly3Ty1m3Jy3Oy83UAy1n83qy1n1m3Cyr1m3Cy3Hy1ms3Hy1n1m3Cyr1m3Cy3Hy1ms3Hy83U9y1n83qy1n1ms3Hy1m3Cyz");
    string_constant_117 = 
	    STATIC_STRING("1m3Ky3Hy1n1ms3Hy1m3Cyz1m3Ky3Hy83UBy1p83Oy1ms3Hy1m3Cyr1m3Ky3Hy1ms3Hy83UCy1n83jy1m3Jyt1m3Yy3Jy83UEy1p83Jy1m3Py3Gy1m3Py3Iy1m3Wy3Iy1");
    string_constant_118 = 
	    STATIC_STRING("m3Wy3Gy1p83Jy1m3Ly3Dy1m3Ly3Fy1m3Sy3Fy1m3Sy3Dy1p83Jy1m3Pyy1m3Py3Cy1m3Wy3Cy1m3Wyy1p83Jy1m3Lyv1m3Lyx1m3Syx1m3Syv1p83Jy1m3Iys1m3Iy3K");
    string_constant_119 = 
	    STATIC_STRING("y1m3Zy3Ky1m3Zys83UDy1o83Oy1m3Yyt1m3Jyt1m3Jy3Jy83UFy1o83Oy1m3Yyt1m3Yy3Jy1m3Jy3Jy835by1o83Gy+s3-6y3-Ty3-oy3-Tykko3A++y1mt3dy83-Vy8");
    string_constant_120 = 
	    STATIC_STRING("35ay1o83Gy+s3-6y3-Ty3-oy3-Tykko3A++y1mt3cy83-Vy1o83Gy+s3-6y3-Ty3-oy3-Tykko3A++y1ms3cy83-Vy1n83Bxy83DBy1m8p83Bxy1n83C+y01m8p83C+y");
    string_constant_121 = 
	    STATIC_STRING("1o83e0y083Hy83Ny1r83N-y01m8p83YYy8o8l83Hy83Fy1q83GUy01n8p83DCy83Gy8o8l83Cy");
    temp = regenerate_optimized_constant(string_constant_98);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(list(13,string_constant_99,
	    string_constant_100,string_constant_89,string_constant_101,
	    string_constant_102,string_constant_103,string_constant_104,
	    string_constant_105,string_constant_106,string_constant_107,
	    string_constant_108,string_constant_109,string_constant_110));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qexport_definition,list_constant_15,Nil,
	    temp,Nil,temp_1,list_constant_15,
	    regenerate_optimized_constant(list(11,string_constant_111,
	    string_constant_112,string_constant_113,string_constant_114,
	    string_constant_115,string_constant_116,string_constant_117,
	    string_constant_118,string_constant_119,string_constant_120,
	    string_constant_121)),Nil);
    Qexport_definition_language = 
	    STATIC_SYMBOL("EXPORT-DEFINITION-LANGUAGE",AB_package);
    Qexport_language = STATIC_SYMBOL("EXPORT-LANGUAGE",AB_package);
    alias_slot_name(3,Qexport_definition_language,Qexport_language,
	    Qexport_definition);
    Qexport_definition_specification = 
	    STATIC_SYMBOL("EXPORT-DEFINITION-SPECIFICATION",AB_package);
    Qexport_specification = STATIC_SYMBOL("EXPORT-SPECIFICATION",AB_package);
    alias_slot_name(3,Qexport_definition_specification,
	    Qexport_specification,Qexport_definition);
    Qjava_methods = STATIC_SYMBOL("JAVA-METHODS",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    alias_slot_name(3,Qjava_methods,Qtext,Qexport_definition);
    Qvisible_class_export_information_qm = 
	    STATIC_SYMBOL("VISIBLE-CLASS-EXPORT-INFORMATION\?",AB_package);
    Qreclaim_visible_class_export_information_qm_value = 
	    STATIC_SYMBOL("RECLAIM-VISIBLE-CLASS-EXPORT-INFORMATION\?-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_visible_class_export_information_qm_value,
	    STATIC_FUNCTION(reclaim_visible_class_export_information_qm_value,
	    NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qvisible_class_export_information_qm,
	    SYMBOL_FUNCTION(Qreclaim_visible_class_export_information_qm_value),
	    Qslot_value_reclaimer);
    Qwrite_export_definition_language_from_slot = 
	    STATIC_SYMBOL("WRITE-EXPORT-DEFINITION-LANGUAGE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_export_definition_language_from_slot,
	    STATIC_FUNCTION(write_export_definition_language_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qexport_definition_language,
	    SYMBOL_FUNCTION(Qwrite_export_definition_language_from_slot),
	    Qslot_value_writer);
    array_constant_3 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)57344L);
    Qread_only_instance_methods = 
	    STATIC_SYMBOL("READ-ONLY-INSTANCE-METHODS",AB_package);
    Qwrite_read_only_instance_methods_from_slot = 
	    STATIC_SYMBOL("WRITE-READ-ONLY-INSTANCE-METHODS-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_read_only_instance_methods_from_slot,
	    STATIC_FUNCTION(write_read_only_instance_methods_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qread_only_instance_methods,
	    SYMBOL_FUNCTION(Qwrite_read_only_instance_methods_from_slot),
	    Qslot_value_writer);
    Qnonexistent_classes_for_export = 
	    STATIC_SYMBOL("NONEXISTENT-CLASSES-FOR-EXPORT",AB_package);
    string_constant_4 = 
	    STATIC_STRING("the following classes have no corresponding definitions in G2: ");
    string_constant_5 = 
	    STATIC_STRING("the class ~S has no corresponding definition in G2");
    write_nonexistent_classes_for_export_note_1 = 
	    STATIC_FUNCTION(write_nonexistent_classes_for_export_note,NIL,
	    FALSE,2,2);
    mutate_global_property(Qnonexistent_classes_for_export,
	    write_nonexistent_classes_for_export_note_1,Qframe_note_writer_1);
    Qnonexistent_static_methods_for_export = 
	    STATIC_SYMBOL("NONEXISTENT-STATIC-METHODS-FOR-EXPORT",AB_package);
    string_constant_6 = STATIC_STRING("(~A) ");
    string_constant_7 = 
	    STATIC_STRING("the following static methods in class ~A ~\n             have no corresponding procedure definitions in G2: ");
    string_constant_8 = 
	    STATIC_STRING("the static method ~A in class ~S ~\n              has no corresponding procedure definition in G2");
    array_constant_4 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)59L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)57344L);
    write_nonexistent_static_methods_for_export_note_1 = 
	    STATIC_FUNCTION(write_nonexistent_static_methods_for_export_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qnonexistent_static_methods_for_export,
	    write_nonexistent_static_methods_for_export_note_1,
	    Qframe_note_writer_1);
    if (Analyzing_export_definition_for_consistency_p == UNBOUND)
	Analyzing_export_definition_for_consistency_p = Nil;
    temp_2 = adjoin(2,Qexport_definition,List_of_types_to_be_analyzed);
    List_of_types_to_be_analyzed = temp_2;
    Qanalyze_for_consistency_for_export_definition = 
	    STATIC_SYMBOL("ANALYZE-FOR-CONSISTENCY-FOR-EXPORT-DEFINITION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qanalyze_for_consistency_for_export_definition,
	    STATIC_FUNCTION(analyze_for_consistency_for_export_definition,
	    NIL,FALSE,3,3));
    Qanalyze_for_consistency = STATIC_SYMBOL("ANALYZE-FOR-CONSISTENCY",
	    AB_package);
    temp_2 = SYMBOL_FUNCTION(Qanalyze_for_consistency_for_export_definition);
    set_get(Qexport_definition,Qanalyze_for_consistency,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qanalyze_for_consistency),
	    Qclasses_which_define);
    temp_2 = CONS(Qexport_definition,temp);
    mutate_global_property(Qanalyze_for_consistency,temp_2,
	    Qclasses_which_define);
    Qinterface = STATIC_SYMBOL("INTERFACE",AB_package);
    Qcode = STATIC_SYMBOL("CODE",AB_package);
    Qduplicate_class_export_in_single_item = 
	    STATIC_SYMBOL("DUPLICATE-CLASS-EXPORT-IN-SINGLE-ITEM",AB_package);
    array_constant_5 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)64L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)9L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)10L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)11L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)12L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)13L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)16L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)17L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)19L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)20L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)21L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)22L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)25L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)26L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)27L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)28L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)29L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)30L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)31L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)32L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)33L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)34L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)35L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)36L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)37L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)38L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)39L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)40L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)41L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)42L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)43L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)44L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)45L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)46L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)47L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)48L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)49L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)50L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)51L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)52L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)53L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)54L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)55L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)56L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)57L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)58L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)62L,(SI_Long)59L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)63L,(SI_Long)57344L);
    array_constant_6 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)11L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)16L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)17L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)18L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)20L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)21L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)22L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)23L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)25L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)28L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)29L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)30L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)31L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)32L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)33L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)34L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)38L,(SI_Long)35L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)39L,(SI_Long)57344L);
    write_duplicate_class_export_in_single_item_note_1 = 
	    STATIC_FUNCTION(write_duplicate_class_export_in_single_item_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qduplicate_class_export_in_single_item,
	    write_duplicate_class_export_in_single_item_note_1,
	    Qframe_note_writer_1);
    Qput_export_definition_specification = 
	    STATIC_SYMBOL("PUT-EXPORT-DEFINITION-SPECIFICATION",AB_package);
    SET_SYMBOL_FUNCTION(Qput_export_definition_specification,
	    STATIC_FUNCTION(put_export_definition_specification,NIL,FALSE,
	    3,3));
    mutate_global_property(Qexport_definition_specification,
	    SYMBOL_FUNCTION(Qput_export_definition_specification),
	    Qslot_putter);
    Qcleanup_for_export_definition = 
	    STATIC_SYMBOL("CLEANUP-FOR-EXPORT-DEFINITION",AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_export_definition,
	    STATIC_FUNCTION(cleanup_for_export_definition,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qcleanup_for_export_definition);
    set_get(Qexport_definition,Qcleanup,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_2 = CONS(Qexport_definition,temp);
    mutate_global_property(Qcleanup,temp_2,Qclasses_which_define);
    Qstatic_methods = STATIC_SYMBOL("STATIC-METHODS",AB_package);
    Qab_directory = STATIC_SYMBOL("DIRECTORY",AB_package);
    Qimports = STATIC_SYMBOL("IMPORTS",AB_package);
    Qclass_path = STATIC_SYMBOL("CLASS-PATH",AB_package);
    Qsuperior_class_override = STATIC_SYMBOL("SUPERIOR-CLASS-OVERRIDE",
	    AB_package);
    Qincluded_instance_methods = STATIC_SYMBOL("INCLUDED-INSTANCE-METHODS",
	    AB_package);
    Qexcluded_instance_methods = STATIC_SYMBOL("EXCLUDED-INSTANCE-METHODS",
	    AB_package);
    string_constant_9 = STATIC_STRING("class ~(~a~) with~%");
    string_constant_10 = STATIC_STRING("  directory ~s");
    string_constant_11 = STATIC_STRING(" and~%");
    string_constant_12 = STATIC_STRING("  imports ~");
    Qtwrite_parsably = STATIC_SYMBOL("TWRITE-PARSABLY",AB_package);
    SET_SYMBOL_FUNCTION(Qtwrite_parsably,STATIC_FUNCTION(twrite_parsably,
	    NIL,FALSE,1,1));
    string_constant_13 = STATIC_STRING("  package ~s");
    string_constant_14 = STATIC_STRING("  class-path ~s");
    string_constant_15 = STATIC_STRING("  superior-class-override ~(~a~)");
    string_constant_16 = STATIC_STRING("  static-methods ");
    string_constant_17 = STATIC_STRING("  only the instance methods ");
    string_constant_18 = STATIC_STRING("  all instance methods except ");
    string_constant_19 = STATIC_STRING(";~%");
    Qwrite_export_definition_specification_from_slot = 
	    STATIC_SYMBOL("WRITE-EXPORT-DEFINITION-SPECIFICATION-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_export_definition_specification_from_slot,
	    STATIC_FUNCTION(write_export_definition_specification_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qexport_definition_specification,
	    SYMBOL_FUNCTION(Qwrite_export_definition_specification_from_slot),
	    Qslot_value_writer);
    string_constant_122 = 
	    STATIC_STRING("13Hy1n83Bxy1m9k83DBy83DBy1n83C+y83-bKy1m83DByl1n83-bKy83-bJy1ll1n83-bKy1n83-bJy1m9k83-Zy83-bKy2lln1n83-bJy1o1m9k83-Gy83-6y1m9k83");
    string_constant_123 = 
	    STATIC_STRING("=Fy83-bRy1nm83I2yo1n83-aNy1m9k83D0y83D0y1n83-aNy1m9k83I2y83I2y1n83-bRy83-bQy1ll1n83-bRy1n83-bQy1m9k83-ty83-bRy2lln1n83-bQy1m1m9k");
    string_constant_124 = 
	    STATIC_STRING("83-qry83-eey1m83-qrym1n83-bQy1p1m9k839Zy1m9k9l1m9k831Ly1m9k83-efy83-eey1m83-ZWyp1n83-bQy1p1m9k830*y1m9k831Ly1m9k83-efy1m9k83vny8");
    string_constant_125 = 
	    STATIC_STRING("3-eey1m83-TCyp1n83-bQy1m1m9k83v8y83-Uy1m83v8ym1n83-bQy1m1m9k839cy83-Uy1m839cym1n83-bQy1m1m9k83-ZGy83-bTy1m83-ZGym1n83-bQy1m1m9k8");
    string_constant_126 = 
	    STATIC_STRING("3-Mby83-Uy1m83-Mbym1n83-bQy1m1m9k83-rVy83-6y1m83-rVym1n83-eey83-6y1ll1n83-eey1n83-6y1m9k83vy83-eey2lln1n83-bTy83-Uy1ll1n83-bTy1n");
    string_constant_127 = STATIC_STRING("83-Uy1m9k83vy83-bTy2lln");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qthe);
    add_grammar_rules_function(regenerate_optimized_constant(list(6,
	    string_constant_122,string_constant_123,string_constant_124,
	    string_constant_125,string_constant_126,string_constant_127)));
    if (Collecting_frame_notes_for_class_export_p == UNBOUND)
	Collecting_frame_notes_for_class_export_p = Nil;
    if (Collected_frame_notes_for_class_export_qm == UNBOUND)
	Collected_frame_notes_for_class_export_qm = Nil;
    Qg2_export_definitions = STATIC_SYMBOL("G2-EXPORT-DEFINITIONS",AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_export_definitions,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    array_constant_7 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)106L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)57344L);
    SET_SYMBOL_FUNCTION(Qg2_export_definitions,
	    STATIC_FUNCTION(g2_export_definitions,NIL,FALSE,1,1));
    Qg2_export_definitions_system_rpc_internal = 
	    STATIC_SYMBOL("G2-EXPORT-DEFINITIONS-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    list_constant_16 = STATIC_LIST((SI_Long)2L,Qab_class,Qexport_definition);
    list_constant_17 = STATIC_LIST((SI_Long)3L,Qexport_definition,Ktype,
	    list_constant_16);
    list_constant_18 = STATIC_CONS(list_constant_17,Qnil);
    Qsystem_defined_rpc = STATIC_SYMBOL("SYSTEM-DEFINED-RPC",AB_package);
    mutate_global_property(Qg2_export_definitions,
	    make_system_rpc_1(Qg2_export_definitions_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_18,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp_2 = adjoin(2,Qg2_export_definitions,System_defined_rpcs);
    System_defined_rpcs = temp_2;
    Kstack_error = STATIC_SYMBOL("STACK-ERROR",Pkeyword);
    SET_SYMBOL_FUNCTION(Qg2_export_definitions_system_rpc_internal,
	    STATIC_FUNCTION(g2_export_definitions_system_rpc_internal,NIL,
	    FALSE,2,2));
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_java_symbol_g2_struct = 
	    STATIC_SYMBOL("JAVA-SYMBOL-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qjava_symbol = STATIC_SYMBOL("JAVA-SYMBOL",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_java_symbol_g2_struct,
	    Qjava_symbol,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qjava_symbol,
	    Qg2_defstruct_structure_name_java_symbol_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_java_symbol == UNBOUND)
	The_type_description_of_java_symbol = Nil;
    string_constant_128 = 
	    STATIC_STRING("43Dy8m83T6y1n83T6y8n8k1l8n0000000knk0k0");
    temp = The_type_description_of_java_symbol;
    The_type_description_of_java_symbol = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_128));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_java_symbol_g2_struct,
	    The_type_description_of_java_symbol,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qjava_symbol,
	    The_type_description_of_java_symbol,Qtype_description_of_type);
    Qoutstanding_java_symbol_count = 
	    STATIC_SYMBOL("OUTSTANDING-JAVA-SYMBOL-COUNT",AB_package);
    Qjava_symbol_structure_memory_usage = 
	    STATIC_SYMBOL("JAVA-SYMBOL-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_129 = STATIC_STRING("1q83T6y8s83-bWy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_java_symbol_count);
    push_optimized_constant(Qjava_symbol_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_129));
    Qchain_of_available_java_symbols = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-JAVA-SYMBOLS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_java_symbols,
	    Chain_of_available_java_symbols);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_java_symbols,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qjava_symbol_count = STATIC_SYMBOL("JAVA-SYMBOL-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qjava_symbol_count,Java_symbol_count);
    record_system_variable(Qjava_symbol_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_java_symbols_vector == UNBOUND)
	Chain_of_available_java_symbols_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qjava_symbol_structure_memory_usage,
	    STATIC_FUNCTION(java_symbol_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_java_symbol_count,
	    STATIC_FUNCTION(outstanding_java_symbol_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_java_symbol_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_java_symbol,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qjava_symbol,
	    reclaim_structure_for_java_symbol_1);
    if (The_java_symbol_table == UNBOUND)
	The_java_symbol_table = Nil;
    Qg2_defstruct_structure_name_java_class_g2_struct = 
	    STATIC_SYMBOL("JAVA-CLASS-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qjava_class = STATIC_SYMBOL("JAVA-CLASS",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_java_class_g2_struct,
	    Qjava_class,Qab_name_of_unique_structure_type);
    mutate_global_property(Qjava_class,
	    Qg2_defstruct_structure_name_java_class_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_java_class == UNBOUND)
	The_type_description_of_java_class = Nil;
    string_constant_130 = 
	    STATIC_STRING("43Dy8m83jWy1n83jWy8n8k1l8n0000000kyk0k0");
    temp = The_type_description_of_java_class;
    The_type_description_of_java_class = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_130));
    mutate_global_property(Qg2_defstruct_structure_name_java_class_g2_struct,
	    The_type_description_of_java_class,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qjava_class,The_type_description_of_java_class,
	    Qtype_description_of_type);
    Qoutstanding_java_class_count = 
	    STATIC_SYMBOL("OUTSTANDING-JAVA-CLASS-COUNT",AB_package);
    Qjava_class_structure_memory_usage = 
	    STATIC_SYMBOL("JAVA-CLASS-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_131 = STATIC_STRING("1q83jWy8s83-bIy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_java_class_count);
    push_optimized_constant(Qjava_class_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_131));
    Qchain_of_available_java_classs = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-JAVA-CLASSS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_java_classs,
	    Chain_of_available_java_classs);
    record_system_variable(Qchain_of_available_java_classs,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qjava_class_count = STATIC_SYMBOL("JAVA-CLASS-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qjava_class_count,Java_class_count);
    record_system_variable(Qjava_class_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_java_classs_vector == UNBOUND)
	Chain_of_available_java_classs_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qjava_class_structure_memory_usage,
	    STATIC_FUNCTION(java_class_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_java_class_count,
	    STATIC_FUNCTION(outstanding_java_class_count,NIL,FALSE,0,0));
    reclaim_structure_for_java_class_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_java_class,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qjava_class,
	    reclaim_structure_for_java_class_1);
    Qg2_defstruct_structure_name_java_descriptor_g2_struct = 
	    STATIC_SYMBOL("JAVA-DESCRIPTOR-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qjava_descriptor = STATIC_SYMBOL("JAVA-DESCRIPTOR",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_java_descriptor_g2_struct,
	    Qjava_descriptor,Qab_name_of_unique_structure_type);
    mutate_global_property(Qjava_descriptor,
	    Qg2_defstruct_structure_name_java_descriptor_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_java_descriptor == UNBOUND)
	The_type_description_of_java_descriptor = Nil;
    string_constant_132 = 
	    STATIC_STRING("43Dy8m83jcy1n83jcy8n8k1l8n0000000kok0k0");
    temp = The_type_description_of_java_descriptor;
    The_type_description_of_java_descriptor = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_132));
    mutate_global_property(Qg2_defstruct_structure_name_java_descriptor_g2_struct,
	    The_type_description_of_java_descriptor,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qjava_descriptor,
	    The_type_description_of_java_descriptor,Qtype_description_of_type);
    Qoutstanding_java_descriptor_count = 
	    STATIC_SYMBOL("OUTSTANDING-JAVA-DESCRIPTOR-COUNT",AB_package);
    Qjava_descriptor_structure_memory_usage = 
	    STATIC_SYMBOL("JAVA-DESCRIPTOR-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_133 = STATIC_STRING("1q83jcy8s83-bPy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_java_descriptor_count);
    push_optimized_constant(Qjava_descriptor_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_133));
    Qchain_of_available_java_descriptors = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-JAVA-DESCRIPTORS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_java_descriptors,
	    Chain_of_available_java_descriptors);
    record_system_variable(Qchain_of_available_java_descriptors,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qjava_descriptor_count = STATIC_SYMBOL("JAVA-DESCRIPTOR-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qjava_descriptor_count,Java_descriptor_count);
    record_system_variable(Qjava_descriptor_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_java_descriptors_vector == UNBOUND)
	Chain_of_available_java_descriptors_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qjava_descriptor_structure_memory_usage,
	    STATIC_FUNCTION(java_descriptor_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_java_descriptor_count,
	    STATIC_FUNCTION(outstanding_java_descriptor_count,NIL,FALSE,0,0));
    reclaim_structure_for_java_descriptor_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_java_descriptor,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qjava_descriptor,
	    reclaim_structure_for_java_descriptor_1);
    Qg2_defstruct_structure_name_java_field_g2_struct = 
	    STATIC_SYMBOL("JAVA-FIELD-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qjava_field = STATIC_SYMBOL("JAVA-FIELD",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_java_field_g2_struct,
	    Qjava_field,Qab_name_of_unique_structure_type);
    mutate_global_property(Qjava_field,
	    Qg2_defstruct_structure_name_java_field_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_java_field == UNBOUND)
	The_type_description_of_java_field = Nil;
    string_constant_134 = 
	    STATIC_STRING("43Dy8m83jey1n83jey8n8k1l8n0000000ksk0k0");
    temp = The_type_description_of_java_field;
    The_type_description_of_java_field = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_134));
    mutate_global_property(Qg2_defstruct_structure_name_java_field_g2_struct,
	    The_type_description_of_java_field,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qjava_field,The_type_description_of_java_field,
	    Qtype_description_of_type);
    Qoutstanding_java_field_count = 
	    STATIC_SYMBOL("OUTSTANDING-JAVA-FIELD-COUNT",AB_package);
    Qjava_field_structure_memory_usage = 
	    STATIC_SYMBOL("JAVA-FIELD-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_135 = STATIC_STRING("1q83jey8s83-bSy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_java_field_count);
    push_optimized_constant(Qjava_field_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_135));
    Qchain_of_available_java_fields = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-JAVA-FIELDS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_java_fields,
	    Chain_of_available_java_fields);
    record_system_variable(Qchain_of_available_java_fields,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qjava_field_count = STATIC_SYMBOL("JAVA-FIELD-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qjava_field_count,Java_field_count);
    record_system_variable(Qjava_field_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_java_fields_vector == UNBOUND)
	Chain_of_available_java_fields_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qjava_field_structure_memory_usage,
	    STATIC_FUNCTION(java_field_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_java_field_count,
	    STATIC_FUNCTION(outstanding_java_field_count,NIL,FALSE,0,0));
    reclaim_structure_for_java_field_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_java_field,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qjava_field,
	    reclaim_structure_for_java_field_1);
    Qg2_defstruct_structure_name_java_method_g2_struct = 
	    STATIC_SYMBOL("JAVA-METHOD-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qjava_method = STATIC_SYMBOL("JAVA-METHOD",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_java_method_g2_struct,
	    Qjava_method,Qab_name_of_unique_structure_type);
    mutate_global_property(Qjava_method,
	    Qg2_defstruct_structure_name_java_method_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_java_method == UNBOUND)
	The_type_description_of_java_method = Nil;
    string_constant_136 = 
	    STATIC_STRING("43Dy8m83jny1n83jny8n8k1l8n0000000kuk0k0");
    temp = The_type_description_of_java_method;
    The_type_description_of_java_method = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_136));
    mutate_global_property(Qg2_defstruct_structure_name_java_method_g2_struct,
	    The_type_description_of_java_method,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qjava_method,
	    The_type_description_of_java_method,Qtype_description_of_type);
    Qoutstanding_java_method_count = 
	    STATIC_SYMBOL("OUTSTANDING-JAVA-METHOD-COUNT",AB_package);
    Qjava_method_structure_memory_usage = 
	    STATIC_SYMBOL("JAVA-METHOD-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_137 = STATIC_STRING("1q83jny8s83-bUy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_java_method_count);
    push_optimized_constant(Qjava_method_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_137));
    Qchain_of_available_java_methods = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-JAVA-METHODS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_java_methods,
	    Chain_of_available_java_methods);
    record_system_variable(Qchain_of_available_java_methods,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qjava_method_count = STATIC_SYMBOL("JAVA-METHOD-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qjava_method_count,Java_method_count);
    record_system_variable(Qjava_method_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_java_methods_vector == UNBOUND)
	Chain_of_available_java_methods_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qjava_method_structure_memory_usage,
	    STATIC_FUNCTION(java_method_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_java_method_count,
	    STATIC_FUNCTION(outstanding_java_method_count,NIL,FALSE,0,0));
    reclaim_structure_for_java_method_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_java_method,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qjava_method,
	    reclaim_structure_for_java_method_1);
    Qg2_defstruct_structure_name_java_code_exception_g2_struct = 
	    STATIC_SYMBOL("JAVA-CODE-EXCEPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qjava_code_exception = STATIC_SYMBOL("JAVA-CODE-EXCEPTION",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_java_code_exception_g2_struct,
	    Qjava_code_exception,Qab_name_of_unique_structure_type);
    mutate_global_property(Qjava_code_exception,
	    Qg2_defstruct_structure_name_java_code_exception_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_java_code_exception == UNBOUND)
	The_type_description_of_java_code_exception = Nil;
    string_constant_138 = 
	    STATIC_STRING("43Dy8m83jby1n83jby8n8k1l8n0000000kpk0k0");
    temp = The_type_description_of_java_code_exception;
    The_type_description_of_java_code_exception = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_138));
    mutate_global_property(Qg2_defstruct_structure_name_java_code_exception_g2_struct,
	    The_type_description_of_java_code_exception,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qjava_code_exception,
	    The_type_description_of_java_code_exception,
	    Qtype_description_of_type);
    Qoutstanding_java_code_exception_count = 
	    STATIC_SYMBOL("OUTSTANDING-JAVA-CODE-EXCEPTION-COUNT",AB_package);
    Qjava_code_exception_structure_memory_usage = 
	    STATIC_SYMBOL("JAVA-CODE-EXCEPTION-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_139 = STATIC_STRING("1q83jby8s83-bMy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_java_code_exception_count);
    push_optimized_constant(Qjava_code_exception_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_139));
    Qchain_of_available_java_code_exceptions = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-JAVA-CODE-EXCEPTIONS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_java_code_exceptions,
	    Chain_of_available_java_code_exceptions);
    record_system_variable(Qchain_of_available_java_code_exceptions,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qjava_code_exception_count = STATIC_SYMBOL("JAVA-CODE-EXCEPTION-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qjava_code_exception_count,
	    Java_code_exception_count);
    record_system_variable(Qjava_code_exception_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_java_code_exceptions_vector == UNBOUND)
	Chain_of_available_java_code_exceptions_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qjava_code_exception_structure_memory_usage,
	    STATIC_FUNCTION(java_code_exception_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_java_code_exception_count,
	    STATIC_FUNCTION(outstanding_java_code_exception_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_java_code_exception_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_java_code_exception,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qjava_code_exception,
	    reclaim_structure_for_java_code_exception_1);
    Qg2_defstruct_structure_name_java_code_g2_struct = 
	    STATIC_SYMBOL("JAVA-CODE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qjava_code = STATIC_SYMBOL("JAVA-CODE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_java_code_g2_struct,
	    Qjava_code,Qab_name_of_unique_structure_type);
    mutate_global_property(Qjava_code,
	    Qg2_defstruct_structure_name_java_code_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_java_code == UNBOUND)
	The_type_description_of_java_code = Nil;
    string_constant_140 = 
	    STATIC_STRING("43Dy8m83jay1n83jay8n8k1l8n0000000kqk0k0");
    temp = The_type_description_of_java_code;
    The_type_description_of_java_code = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_140));
    mutate_global_property(Qg2_defstruct_structure_name_java_code_g2_struct,
	    The_type_description_of_java_code,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qjava_code,The_type_description_of_java_code,
	    Qtype_description_of_type);
    Qoutstanding_java_code_count = 
	    STATIC_SYMBOL("OUTSTANDING-JAVA-CODE-COUNT",AB_package);
    Qjava_code_structure_memory_usage = 
	    STATIC_SYMBOL("JAVA-CODE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_141 = STATIC_STRING("1q83jay8s83-bLy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_java_code_count);
    push_optimized_constant(Qjava_code_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_141));
    Qchain_of_available_java_codes = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-JAVA-CODES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_java_codes,
	    Chain_of_available_java_codes);
    record_system_variable(Qchain_of_available_java_codes,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qjava_code_count = STATIC_SYMBOL("JAVA-CODE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qjava_code_count,Java_code_count);
    record_system_variable(Qjava_code_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_java_codes_vector == UNBOUND)
	Chain_of_available_java_codes_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qjava_code_structure_memory_usage,
	    STATIC_FUNCTION(java_code_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_java_code_count,
	    STATIC_FUNCTION(outstanding_java_code_count,NIL,FALSE,0,0));
    reclaim_structure_for_java_code_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_java_code,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qjava_code,
	    reclaim_structure_for_java_code_1);
    Qg2_defstruct_structure_name_class_file_stream_g2_struct = 
	    STATIC_SYMBOL("CLASS-FILE-STREAM-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qclass_file_stream = STATIC_SYMBOL("CLASS-FILE-STREAM",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_class_file_stream_g2_struct,
	    Qclass_file_stream,Qab_name_of_unique_structure_type);
    mutate_global_property(Qclass_file_stream,
	    Qg2_defstruct_structure_name_class_file_stream_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_class_file_stream == UNBOUND)
	The_type_description_of_class_file_stream = Nil;
    string_constant_142 = 
	    STATIC_STRING("43Dy8m83fry1n83fry8n8k1l8n0000001l1n8y83-3Ay1l83s0yknk0k0");
    temp = The_type_description_of_class_file_stream;
    The_type_description_of_class_file_stream = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_142));
    mutate_global_property(Qg2_defstruct_structure_name_class_file_stream_g2_struct,
	    The_type_description_of_class_file_stream,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qclass_file_stream,
	    The_type_description_of_class_file_stream,
	    Qtype_description_of_type);
    Qoutstanding_class_file_stream_count = 
	    STATIC_SYMBOL("OUTSTANDING-CLASS-FILE-STREAM-COUNT",AB_package);
    Qclass_file_stream_structure_memory_usage = 
	    STATIC_SYMBOL("CLASS-FILE-STREAM-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_143 = STATIC_STRING("1q83fry8s83-MYy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_class_file_stream_count);
    push_optimized_constant(Qclass_file_stream_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_143));
    Qchain_of_available_class_file_streams = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-CLASS-FILE-STREAMS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_class_file_streams,
	    Chain_of_available_class_file_streams);
    record_system_variable(Qchain_of_available_class_file_streams,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qclass_file_stream_count = STATIC_SYMBOL("CLASS-FILE-STREAM-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qclass_file_stream_count,
	    Class_file_stream_count);
    record_system_variable(Qclass_file_stream_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_class_file_streams_vector == UNBOUND)
	Chain_of_available_class_file_streams_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qclass_file_stream_structure_memory_usage,
	    STATIC_FUNCTION(class_file_stream_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_class_file_stream_count,
	    STATIC_FUNCTION(outstanding_class_file_stream_count,NIL,FALSE,
	    0,0));
    reclaim_structure_for_class_file_stream_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_class_file_stream,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qclass_file_stream,
	    reclaim_structure_for_class_file_stream_1);
    Kjust_opened = STATIC_SYMBOL("JUST-OPENED",Pkeyword);
    Qunexpected_end_of_file = STATIC_SYMBOL("UNEXPECTED-END-OF-FILE",
	    AB_package);
    Debug_read_java_class_p = Nil;
    list_constant = STATIC_LIST((SI_Long)2L,Qunsigned_byte,FIX((SI_Long)8L));
    Qbad_magic_number = STATIC_SYMBOL("BAD-MAGIC-NUMBER",AB_package);
    Qpublic = STATIC_SYMBOL("PUBLIC",AB_package);
    Qprivate = STATIC_SYMBOL("PRIVATE",AB_package);
    Qprotected = STATIC_SYMBOL("PROTECTED",AB_package);
    Qstatic = STATIC_SYMBOL("STATIC",AB_package);
    Qfinal = STATIC_SYMBOL("FINAL",AB_package);
    Qsynchronized = STATIC_SYMBOL("SYNCHRONIZED",AB_package);
    Qvolatile = STATIC_SYMBOL("VOLATILE",AB_package);
    Qtransient = STATIC_SYMBOL("TRANSIENT",AB_package);
    Qnative = STATIC_SYMBOL("NATIVE",AB_package);
    Qabstract = STATIC_SYMBOL("ABSTRACT",AB_package);
    Qlong = STATIC_SYMBOL("LONG",AB_package);
    Qdouble = STATIC_SYMBOL("DOUBLE",AB_package);
    Qunknown_constant_tag = STATIC_SYMBOL("UNKNOWN-CONSTANT-TAG",AB_package);
    Qfieldref = STATIC_SYMBOL("FIELDREF",AB_package);
    Qmethodref = STATIC_SYMBOL("METHODREF",AB_package);
    Qinterfacemethoddref = STATIC_SYMBOL("INTERFACEMETHODDREF",AB_package);
    Qnameandtype = STATIC_SYMBOL("NAMEANDTYPE",AB_package);
    Qbad_null_char = STATIC_SYMBOL("BAD-NULL-CHAR",AB_package);
    Qill_formed_utf8 = STATIC_SYMBOL("ILL-FORMED-UTF8",AB_package);
    Qutf8 = STATIC_SYMBOL("UTF8",AB_package);
    Qthis_class_index_out_of_range = 
	    STATIC_SYMBOL("THIS-CLASS-INDEX-OUT-OF-RANGE",AB_package);
    Qbad_this_class_constant = STATIC_SYMBOL("BAD-THIS-CLASS-CONSTANT",
	    AB_package);
    Qredefining_java_dot_lang_dot_object_not = 
	    STATIC_SYMBOL("REDEFINING-JAVA.LANG.OBJECT-NOT",AB_package);
    Qbad_super_class_index = STATIC_SYMBOL("BAD-SUPER-CLASS-INDEX",AB_package);
    Qbad_super_class_constant = STATIC_SYMBOL("BAD-SUPER-CLASS-CONSTANT",
	    AB_package);
    Qsuperinterface_is_not_class_constant = 
	    STATIC_SYMBOL("SUPERINTERFACE-IS-NOT-CLASS-CONSTANT",AB_package);
    Qinterface_index_out_of_range = 
	    STATIC_SYMBOL("INTERFACE-INDEX-OUT-OF-RANGE",AB_package);
    Qfield = STATIC_SYMBOL("FIELD",AB_package);
    Qab_method = STATIC_SYMBOL("METHOD",AB_package);
    Qattribute_name_not_utf8 = STATIC_SYMBOL("ATTRIBUTE-NAME-NOT-UTF8",
	    AB_package);
    Qattribute_name_index_out_of_range = 
	    STATIC_SYMBOL("ATTRIBUTE-NAME-INDEX-OUT-OF-RANGE",AB_package);
    Qattribute_data_length_must_be_less_than_16777216 = 
	    STATIC_SYMBOL("ATTRIBUTE-DATA-LENGTH-MUST-BE-LESS-THAN-16777216",
	    AB_package);
    array_constant_8 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)8L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)15L,(SI_Long)57344L);
    Qsource_file = STATIC_SYMBOL("SOURCE-FILE",AB_package);
    Qbad_source_file_attribute = STATIC_SYMBOL("BAD-SOURCE-FILE-ATTRIBUTE",
	    AB_package);
    array_constant_9 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)8L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)10L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)11L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)14L,(SI_Long)13L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)15L,(SI_Long)57344L);
    Qab_constant_value = STATIC_SYMBOL("CONSTANT-VALUE",AB_package);
    Qbad_constant_value_attribute = 
	    STATIC_SYMBOL("BAD-CONSTANT-VALUE-ATTRIBUTE",AB_package);
    array_constant_10 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)57344L);
    array_constant_11 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)4L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)9L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)15L,(SI_Long)57344L);
    array_constant_12 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)4L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)5L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)9L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)10L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)11L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)12L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)13L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)23L,(SI_Long)57344L);
    array_constant_13 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)2L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)5L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)10L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)13L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)14L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)15L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)16L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)22L,(SI_Long)18L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)23L,(SI_Long)57344L);
    Qbytecode_vectors_must_be_less_than_16777216 = 
	    STATIC_SYMBOL("BYTECODE-VECTORS-MUST-BE-LESS-THAN-16777216",
	    AB_package);
    Qend_pc_out_of_range = STATIC_SYMBOL("END-PC-OUT-OF-RANGE",AB_package);
    Qstart_pc_out_of_range = STATIC_SYMBOL("START-PC-OUT-OF-RANGE",AB_package);
    Qhandler_pc_out_of_range = STATIC_SYMBOL("HANDLER-PC-OUT-OF-RANGE",
	    AB_package);
    Qbad_exception_table_class = STATIC_SYMBOL("BAD-EXCEPTION-TABLE-CLASS",
	    AB_package);
    Qint = STATIC_SYMBOL("INT",AB_package);
    Qshort = STATIC_SYMBOL("SHORT",AB_package);
    Qboolean = STATIC_SYMBOL("BOOLEAN",AB_package);
    if (Current_jemit_text_style_qm == UNBOUND)
	Current_jemit_text_style_qm = Nil;
    if (Deferring_errors_for_class_export_p == UNBOUND)
	Deferring_errors_for_class_export_p = Nil;
    if (Deferred_errors_for_class_export_qm == UNBOUND)
	Deferred_errors_for_class_export_qm = Nil;
    Qg2_emit_class_as_java = STATIC_SYMBOL("G2-EMIT-CLASS-AS-JAVA",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_emit_class_as_java,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_20 = STATIC_STRING("JEMIT ERROR: ~a");
    string_constant_21 = 
	    STATIC_STRING("unacceptable class for java emitter: ~A");
    SET_SYMBOL_FUNCTION(Qg2_emit_class_as_java,
	    STATIC_FUNCTION(g2_emit_class_as_java,NIL,FALSE,8,8));
    Qunbound_in_protected_let = STATIC_SYMBOL("UNBOUND-IN-PROTECTED-LET",
	    AB_package);
    array_constant_14 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)7L,(SI_Long)57344L);
    Qtext_conversion_style = STATIC_SYMBOL("TEXT-CONVERSION-STYLE",AB_package);
    Qutf_8_string = STATIC_SYMBOL("UTF-8-STRING",AB_package);
    Qtext_conversion_style_for_purpose = 
	    STATIC_SYMBOL("TEXT-CONVERSION-STYLE-FOR-PURPOSE",AB_package);
    Kjemit_error = STATIC_SYMBOL("JEMIT-ERROR",Pkeyword);
    Qjwith_output_to_text_string = 
	    STATIC_SYMBOL("JWITH-OUTPUT-TO-TEXT-STRING",AB_package);
    array_constant_15 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)0L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)2L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)3L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)5L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)15L,(SI_Long)57344L);
    array_constant_16 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)7L,(SI_Long)57344L);
    array_constant_17 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)1L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)7L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)8L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)9L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)10L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)11L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)14L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)15L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)16L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)17L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)18L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)19L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)20L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)21L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)22L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)23L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)24L,(SI_Long)59L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)30L,(SI_Long)25L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)31L,(SI_Long)57344L);
    array_constant_18 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)1L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)15L,(SI_Long)57344L);
    array_constant_19 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)0L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)2L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)5L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)7L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)8L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)11L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)14L,(SI_Long)13L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)15L,(SI_Long)57344L);
    array_constant_20 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)2L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)6L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)15L,(SI_Long)57344L);
    string_constant_22 = STATIC_STRING("Multiple Inheritance on ~a");
    Qtw_user_item = STATIC_SYMBOL("TW-USER-ITEM",AB_package);
    array_constant_21 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)0L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)1L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)2L,(SI_Long)106L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)15L,(SI_Long)57344L);
    array_constant_22 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)0L,(SI_Long)123L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)7L,(SI_Long)57344L);
    array_constant_23 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)7L,(SI_Long)57344L);
    array_constant_24 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)0L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)3L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)15L,(SI_Long)57344L);
    array_constant_25 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)5L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)15L,(SI_Long)57344L);
    array_constant_26 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)1L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)2L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)3L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)15L,(SI_Long)57344L);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    array_constant_27 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)0L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)15L,(SI_Long)57344L);
    string_constant_23 = STATIC_STRING("~a is not supported");
    Qinteger_array = STATIC_SYMBOL("INTEGER-ARRAY",AB_package);
    array_constant_28 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)3L,(SI_Long)91L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)4L,(SI_Long)93L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)7L,(SI_Long)57344L);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    array_constant_29 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)0L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)3L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)6L,(SI_Long)91L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)7L,(SI_Long)93L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)15L,(SI_Long)57344L);
    array_constant_30 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)2L,(SI_Long)113L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)6L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)15L,(SI_Long)57344L);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    array_constant_31 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)6L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)15L,(SI_Long)57344L);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qitem_or_datum = STATIC_SYMBOL("ITEM-OR-DATUM",AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_19 = STATIC_CONS(Qno_item,Qnil);
    list_constant_1 = STATIC_LIST((SI_Long)3L,Qab_or,Qitem_or_datum,
	    list_constant_19);
    string_constant_24 = STATIC_STRING("strange type specification ~NT");
    array_constant_32 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)4L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)5L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)6L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)7L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)9L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)15L,(SI_Long)57344L);
    array_constant_33 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)1L,(SI_Long)61L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)7L,(SI_Long)57344L);
    array_constant_34 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)1L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)2L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)3L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)6L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)11L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)12L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)13L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)14L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)23L,(SI_Long)57344L);
    array_constant_35 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)0L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)1L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)7L,(SI_Long)57344L);
    string_constant_25 = STATIC_STRING("unsupported initial value for ~a");
    string_constant_26 = STATIC_STRING("new Integer(~NV)");
    string_constant_27 = STATIC_STRING("new Double(~NV)");
    Qinstantiate_object_in_attribute = 
	    STATIC_SYMBOL("INSTANTIATE-OBJECT-IN-ATTRIBUTE",AB_package);
    array_constant_36 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)2L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)7L,(SI_Long)91L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)8L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)9L,(SI_Long)93L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)15L,(SI_Long)57344L);
    array_constant_37 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)2L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)6L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)7L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)8L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)10L,(SI_Long)91L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)11L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)12L,(SI_Long)93L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)14L,(SI_Long)13L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)15L,(SI_Long)57344L);
    array_constant_38 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)2L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)7L,(SI_Long)57344L);
    array_constant_39 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)0L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)1L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)7L,(SI_Long)57344L);
    string_constant_28 = 
	    STATIC_STRING("unsupported attribute initializer for ~a");
    string_constant_29 = 
	    STATIC_STRING("unsupported data type in attribute ~a");
    if (Collecting_exported_method_text_p == UNBOUND)
	Collecting_exported_method_text_p = Nil;
    if (List_of_exported_method_texts == UNBOUND)
	List_of_exported_method_texts = Nil;
    array_constant_40 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)0L,(SI_Long)125L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)7L,(SI_Long)57344L);
    if (Current_jemit_stream == UNBOUND)
	Current_jemit_stream = Nil;
    if (Current_jemit_indent == UNBOUND)
	Current_jemit_indent = Nil;
    if (Current_jemit_node_stack == UNBOUND)
	Current_jemit_node_stack = Nil;
    if (Current_jemit_compound_statement_list == UNBOUND)
	Current_jemit_compound_statement_list = Nil;
    if (Current_jemit_return_type_specification_qm == UNBOUND)
	Current_jemit_return_type_specification_qm = Nil;
    if (Current_jemit_class_description == UNBOUND)
	Current_jemit_class_description = Nil;
    if (Current_jemit_class_object_table == UNBOUND)
	Current_jemit_class_object_table = Nil;
    if (Current_jemit_self_name == UNBOUND)
	Current_jemit_self_name = Nil;
    if (Current_jemit_locals == UNBOUND)
	Current_jemit_locals = Nil;
    if (Current_jemit_args == UNBOUND)
	Current_jemit_args = Nil;
    array_constant_41 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)4L,(SI_Long)123L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)7L,(SI_Long)57344L);
    array_constant_42 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)4L,(SI_Long)125L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)7L,(SI_Long)57344L);
    Qlocal_assignment = STATIC_SYMBOL("LOCAL-ASSIGNMENT",AB_package);
    Qget_class = STATIC_SYMBOL("GET-CLASS",AB_package);
    Qsymbol_constant = STATIC_SYMBOL("SYMBOL-CONSTANT",AB_package);
    string_constant_30 = 
	    STATIC_STRING("multiple-return-statements not supported");
    string_constant_31 = STATIC_STRING("~A-MAIN");
    Qmain = STATIC_SYMBOL("MAIN",AB_package);
    array_constant_43 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)0L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)2L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)5L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)15L,(SI_Long)57344L);
    array_constant_44 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)5L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)15L,(SI_Long)57344L);
    array_constant_45 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)0L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)3L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)7L,(SI_Long)57344L);
    array_constant_46 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)1L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)7L,(SI_Long)57344L);
    array_constant_47 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)5L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)9L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)10L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)11L,(SI_Long)91L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)12L,(SI_Long)93L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)14L,(SI_Long)13L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)15L,(SI_Long)57344L);
    array_constant_48 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)0L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)7L,(SI_Long)57344L);
    string_constant_32 = STATIC_STRING(" = ");
    Qchange_slot = STATIC_SYMBOL("CHANGE-SLOT",AB_package);
    Qchange_array_length = STATIC_SYMBOL("CHANGE-ARRAY-LENGTH",AB_package);
    array_constant_49 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)1L,(SI_Long)61L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)5L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)15L,(SI_Long)57344L);
    array_constant_50 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)0L,(SI_Long)91L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)7L,(SI_Long)57344L);
    array_constant_51 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)0L,(SI_Long)93L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)7L,(SI_Long)57344L);
    Qab_if = STATIC_SYMBOL("IF",AB_package);
    array_constant_52 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)1L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)3L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)7L,(SI_Long)57344L);
    array_constant_53 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)0L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)1L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)7L,(SI_Long)57344L);
    Qgesture_call = STATIC_SYMBOL("GESTURE-CALL",AB_package);
    Qrepeat = STATIC_SYMBOL("REPEAT",AB_package);
    array_constant_54 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)0L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)6L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)9L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)11L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)15L,(SI_Long)57344L);
    Qexit_if = STATIC_SYMBOL("EXIT-IF",AB_package);
    array_constant_55 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)0L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)2L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)6L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)7L,(SI_Long)59L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)15L,(SI_Long)57344L);
    Qfor_loop_integer = STATIC_SYMBOL("FOR-LOOP-INTEGER",AB_package);
    array_constant_56 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)4L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)7L,(SI_Long)57344L);
    array_constant_57 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)1L,(SI_Long)59L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)7L,(SI_Long)57344L);
    string_constant_33 = STATIC_STRING(" <= ");
    string_constant_34 = STATIC_STRING(" >= ");
    string_constant_35 = STATIC_STRING(" += ");
    string_constant_36 = STATIC_STRING(" -= ");
    array_constant_58 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)1L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)7L,(SI_Long)57344L);
    string_constant_37 = 
	    STATIC_STRING("method must have return statement in all branches");
    array_constant_59 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)0L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)15L,(SI_Long)57344L);
    Qcompound_statement = STATIC_SYMBOL("COMPOUND-STATEMENT",AB_package);
    string_constant_38 = 
	    STATIC_STRING("multiple assignments ~s not supported");
    array_constant_60 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)0L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)7L,(SI_Long)57344L);
    array_constant_61 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)0L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)7L,(SI_Long)57344L);
    Qvalue2integer = STATIC_SYMBOL("VALUE2INTEGER",AB_package);
    Qvalue2quantity = STATIC_SYMBOL("VALUE2QUANTITY",AB_package);
    Qvalue2float = STATIC_SYMBOL("VALUE2FLOAT",AB_package);
    Qvalue2text = STATIC_SYMBOL("VALUE2TEXT",AB_package);
    Qvalue2symbol = STATIC_SYMBOL("VALUE2SYMBOL",AB_package);
    Qvalue2truth_value = STATIC_SYMBOL("VALUE2TRUTH-VALUE",AB_package);
    Qvalue2sequence = STATIC_SYMBOL("VALUE2SEQUENCE",AB_package);
    Qvalue2struct = STATIC_SYMBOL("VALUE2STRUCT",AB_package);
    Qvalue2datum = STATIC_SYMBOL("VALUE2DATUM",AB_package);
    Qvalue2frame = STATIC_SYMBOL("VALUE2FRAME",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)10L,Qvalue2integer,
	    Qvalue2quantity,Qvalue2float,Qvalue2text,Qvalue2symbol,
	    Qvalue2truth_value,Qvalue2sequence,Qvalue2struct,Qvalue2datum,
	    Qvalue2frame);
    Qget_slot = STATIC_SYMBOL("GET-SLOT",AB_package);
    Qfetch_local = STATIC_SYMBOL("FETCH-LOCAL",AB_package);
    string_constant_39 = STATIC_STRING("first argument to call too complex");
    string_constant_40 = 
	    STATIC_STRING("cannot compile attribute of unknown class ~a");
    string_constant_41 = STATIC_STRING("undefined slot/field ~a");
    list_constant_3 = STATIC_CONS(Qvalue2frame,Qnil);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qab_class,Qinteger_array);
    list_constant_5 = STATIC_LIST((SI_Long)2L,Qab_class,Qfloat_array);
    string_constant_42 = STATIC_STRING("array type not simple enough");
    Qprimary = STATIC_SYMBOL("PRIMARY",AB_package);
    Qpostfix = STATIC_SYMBOL("POSTFIX",AB_package);
    Qunary = STATIC_SYMBOL("UNARY",AB_package);
    Qmultiplicative = STATIC_SYMBOL("MULTIPLICATIVE",AB_package);
    Qadditive = STATIC_SYMBOL("ADDITIVE",AB_package);
    Qshift = STATIC_SYMBOL("SHIFT",AB_package);
    Qrelational = STATIC_SYMBOL("RELATIONAL",AB_package);
    Qequality = STATIC_SYMBOL("EQUALITY",AB_package);
    Qab_xor = STATIC_SYMBOL("XOR",AB_package);
    Qior = STATIC_SYMBOL("IOR",AB_package);
    Qconditional_and = STATIC_SYMBOL("CONDITIONAL-AND",AB_package);
    Qconditional_or = STATIC_SYMBOL("CONDITIONAL-OR",AB_package);
    Qconditional = STATIC_SYMBOL("CONDITIONAL",AB_package);
    list_constant_20 = STATIC_LIST((SI_Long)14L,Qprimary,Qpostfix,Qunary,
	    Qmultiplicative,Qadditive,Qshift,Qrelational,Qequality,Qand,
	    Qab_xor,Qior,Qconditional_and,Qconditional_or,Qconditional);
    Java_operator_precedence_list = list_constant_20;
    Qequivalent_java_operator = STATIC_SYMBOL("EQUIVALENT-JAVA-OPERATOR",
	    AB_package);
    Equivalent_java_operator_prop = Qequivalent_java_operator;
    Qequivalent_java_method = STATIC_SYMBOL("EQUIVALENT-JAVA-METHOD",
	    AB_package);
    Equivalent_java_method_prop = Qequivalent_java_method;
    Qjava_operator_precedence = STATIC_SYMBOL("JAVA-OPERATOR-PRECEDENCE",
	    AB_package);
    Java_operator_precedence_prop = Qjava_operator_precedence;
    Qjava_operator_emitter_template = 
	    STATIC_SYMBOL("JAVA-OPERATOR-EMITTER-TEMPLATE",AB_package);
    Java_operator_emitter_template_prop = Qjava_operator_emitter_template;
    Qg2_add = STATIC_SYMBOL("ADD",AB_package);
    mutate_global_property(Qg2_add,Qadditive,Qjava_operator_precedence);
    Qarg = STATIC_SYMBOL("ARG",AB_package);
    list_constant_21 = STATIC_LIST((SI_Long)2L,Qarg,FIX((SI_Long)1L));
    string_constant_144 = STATIC_STRING(" + ");
    list_constant_22 = STATIC_LIST((SI_Long)2L,Qarg,FIX((SI_Long)2L));
    list_constant_23 = STATIC_LIST((SI_Long)3L,list_constant_21,
	    string_constant_144,list_constant_22);
    mutate_global_property(Qg2_add,list_constant_23,
	    Qjava_operator_emitter_template);
    Qadd_fixnum = STATIC_SYMBOL("ADD-FIXNUM",AB_package);
    mutate_global_property(Qadd_fixnum,Qg2_add,Qequivalent_java_operator);
    Qadd_quantity = STATIC_SYMBOL("ADD-QUANTITY",AB_package);
    mutate_global_property(Qadd_quantity,Qg2_add,Qequivalent_java_operator);
    Qadd_float = STATIC_SYMBOL("ADD-FLOAT",AB_package);
    mutate_global_property(Qadd_float,Qg2_add,Qequivalent_java_operator);
    Qtw_format_form = STATIC_SYMBOL("TW-FORMAT-FORM",AB_package);
    mutate_global_property(Qtw_format_form,Qg2_add,Qequivalent_java_operator);
    Qsubtract = STATIC_SYMBOL("SUBTRACT",AB_package);
    mutate_global_property(Qsubtract,Qadditive,Qjava_operator_precedence);
    string_constant_145 = STATIC_STRING(" - ");
    list_constant_24 = STATIC_LIST((SI_Long)3L,list_constant_22,
	    string_constant_145,list_constant_21);
    mutate_global_property(Qsubtract,list_constant_24,
	    Qjava_operator_emitter_template);
    Qsubtract_fixnum = STATIC_SYMBOL("SUBTRACT-FIXNUM",AB_package);
    mutate_global_property(Qsubtract_fixnum,Qsubtract,
	    Qequivalent_java_operator);
    Qsubtract_quantity = STATIC_SYMBOL("SUBTRACT-QUANTITY",AB_package);
    mutate_global_property(Qsubtract_quantity,Qsubtract,
	    Qequivalent_java_operator);
    Qsubtract_float = STATIC_SYMBOL("SUBTRACT-FLOAT",AB_package);
    mutate_global_property(Qsubtract_float,Qsubtract,
	    Qequivalent_java_operator);
    Qmultiply = STATIC_SYMBOL("MULTIPLY",AB_package);
    mutate_global_property(Qmultiply,Qmultiplicative,
	    Qjava_operator_precedence);
    string_constant_146 = STATIC_STRING(" * ");
    list_constant_25 = STATIC_CONS(list_constant_22,Qnil);
    list_constant_26 = STATIC_LIST_STAR((SI_Long)3L,list_constant_21,
	    string_constant_146,list_constant_25);
    mutate_global_property(Qmultiply,list_constant_26,
	    Qjava_operator_emitter_template);
    Qmultiply_fixnum = STATIC_SYMBOL("MULTIPLY-FIXNUM",AB_package);
    mutate_global_property(Qmultiply_fixnum,Qmultiply,
	    Qequivalent_java_operator);
    Qmultiply_quantity = STATIC_SYMBOL("MULTIPLY-QUANTITY",AB_package);
    mutate_global_property(Qmultiply_quantity,Qmultiply,
	    Qequivalent_java_operator);
    Qmultiply_float = STATIC_SYMBOL("MULTIPLY-FLOAT",AB_package);
    mutate_global_property(Qmultiply_float,Qmultiply,
	    Qequivalent_java_operator);
    Qquotient = STATIC_SYMBOL("QUOTIENT",AB_package);
    mutate_global_property(Qquotient,Qmultiplicative,
	    Qjava_operator_precedence);
    string_constant_147 = STATIC_STRING(" / ");
    list_constant_27 = STATIC_LIST_STAR((SI_Long)3L,list_constant_21,
	    string_constant_147,list_constant_25);
    mutate_global_property(Qquotient,list_constant_27,
	    Qjava_operator_emitter_template);
    Qquotient_fixnum = STATIC_SYMBOL("QUOTIENT-FIXNUM",AB_package);
    mutate_global_property(Qquotient_fixnum,Qquotient,
	    Qequivalent_java_operator);
    Qquotient_quantity = STATIC_SYMBOL("QUOTIENT-QUANTITY",AB_package);
    mutate_global_property(Qquotient_quantity,Qquotient,
	    Qequivalent_java_operator);
    Qquotient_float = STATIC_SYMBOL("QUOTIENT-FLOAT",AB_package);
    mutate_global_property(Qquotient_float,Qquotient,
	    Qequivalent_java_operator);
    Qdivide = STATIC_SYMBOL("DIVIDE",AB_package);
    mutate_global_property(Qdivide,Qmultiplicative,Qjava_operator_precedence);
    mutate_global_property(Qdivide,list_constant_27,
	    Qjava_operator_emitter_template);
    Qdivide_fixnum = STATIC_SYMBOL("DIVIDE-FIXNUM",AB_package);
    mutate_global_property(Qdivide_fixnum,Qdivide,Qequivalent_java_operator);
    Qdivide_float = STATIC_SYMBOL("DIVIDE-FLOAT",AB_package);
    mutate_global_property(Qdivide_float,Qdivide,Qequivalent_java_operator);
    Qremainder = STATIC_SYMBOL("REMAINDER",AB_package);
    mutate_global_property(Qremainder,Qmultiplicative,
	    Qjava_operator_precedence);
    string_constant_148 = STATIC_STRING(" % ");
    list_constant_28 = STATIC_LIST_STAR((SI_Long)3L,list_constant_21,
	    string_constant_148,list_constant_25);
    mutate_global_property(Qremainder,list_constant_28,
	    Qjava_operator_emitter_template);
    Qremainder_fixnum = STATIC_SYMBOL("REMAINDER-FIXNUM",AB_package);
    mutate_global_property(Qremainder_fixnum,Qremainder,
	    Qequivalent_java_operator);
    Qremainder_quantity = STATIC_SYMBOL("REMAINDER-QUANTITY",AB_package);
    mutate_global_property(Qremainder_quantity,Qremainder,
	    Qequivalent_java_operator);
    Qremainder_float = STATIC_SYMBOL("REMAINDER-FLOAT",AB_package);
    mutate_global_property(Qremainder_float,Qremainder,
	    Qequivalent_java_operator);
    Qnegate = STATIC_SYMBOL("NEGATE",AB_package);
    mutate_global_property(Qnegate,Qunary,Qjava_operator_precedence);
    string_constant_149 = STATIC_STRING("-");
    list_constant_29 = STATIC_CONS(list_constant_21,Qnil);
    list_constant_30 = STATIC_CONS(string_constant_149,list_constant_29);
    mutate_global_property(Qnegate,list_constant_30,
	    Qjava_operator_emitter_template);
    Qnegate_fixnum = STATIC_SYMBOL("NEGATE-FIXNUM",AB_package);
    mutate_global_property(Qnegate_fixnum,Qnegate,Qequivalent_java_operator);
    Qnegate_quantity = STATIC_SYMBOL("NEGATE-QUANTITY",AB_package);
    mutate_global_property(Qnegate_quantity,Qnegate,Qequivalent_java_operator);
    Qnegate_float = STATIC_SYMBOL("NEGATE-FLOAT",AB_package);
    mutate_global_property(Qnegate_float,Qnegate,Qequivalent_java_operator);
    Qbitwise_or = STATIC_SYMBOL("BITWISE-OR",AB_package);
    mutate_global_property(Qbitwise_or,Qior,Qjava_operator_precedence);
    string_constant_150 = STATIC_STRING(" | ");
    list_constant_31 = STATIC_LIST_STAR((SI_Long)3L,list_constant_21,
	    string_constant_150,list_constant_25);
    mutate_global_property(Qbitwise_or,list_constant_31,
	    Qjava_operator_emitter_template);
    mutate_global_property(Qbitwise_or,Qbitwise_or,Qequivalent_java_operator);
    Qbitwise_and = STATIC_SYMBOL("BITWISE-AND",AB_package);
    mutate_global_property(Qbitwise_and,Qand,Qjava_operator_precedence);
    string_constant_151 = STATIC_STRING(" & ");
    list_constant_32 = STATIC_LIST_STAR((SI_Long)3L,list_constant_21,
	    string_constant_151,list_constant_25);
    mutate_global_property(Qbitwise_and,list_constant_32,
	    Qjava_operator_emitter_template);
    mutate_global_property(Qbitwise_and,Qbitwise_and,
	    Qequivalent_java_operator);
    mutate_global_property(Qequal,Qequality,Qjava_operator_precedence);
    string_constant_152 = STATIC_STRING(" == ");
    list_constant_33 = STATIC_LIST_STAR((SI_Long)3L,list_constant_21,
	    string_constant_152,list_constant_25);
    mutate_global_property(Qequal,list_constant_33,
	    Qjava_operator_emitter_template);
    Qequal_fixnum = STATIC_SYMBOL("EQUAL-FIXNUM",AB_package);
    mutate_global_property(Qequal_fixnum,Qequal,Qequivalent_java_operator);
    Qequal_quantity = STATIC_SYMBOL("EQUAL-QUANTITY",AB_package);
    mutate_global_property(Qequal_quantity,Qequal,Qequivalent_java_operator);
    mutate_global_property(Qequal_fixnum,Qequal,Qequivalent_java_operator);
    Qgreater_than = STATIC_SYMBOL("GREATER-THAN",AB_package);
    mutate_global_property(Qgreater_than,Qrelational,
	    Qjava_operator_precedence);
    string_constant_153 = STATIC_STRING(" > ");
    list_constant_34 = STATIC_LIST_STAR((SI_Long)3L,list_constant_21,
	    string_constant_153,list_constant_25);
    mutate_global_property(Qgreater_than,list_constant_34,
	    Qjava_operator_emitter_template);
    Qgreater_than_fixnum = STATIC_SYMBOL("GREATER-THAN-FIXNUM",AB_package);
    mutate_global_property(Qgreater_than_fixnum,Qgreater_than,
	    Qequivalent_java_operator);
    Qgreater_than_quantity = STATIC_SYMBOL("GREATER-THAN-QUANTITY",AB_package);
    mutate_global_property(Qgreater_than_quantity,Qgreater_than,
	    Qequivalent_java_operator);
    mutate_global_property(Qgreater_than_fixnum,Qgreater_than,
	    Qequivalent_java_operator);
    Qgreater_than_equal = STATIC_SYMBOL("GREATER-THAN-EQUAL",AB_package);
    mutate_global_property(Qgreater_than_equal,Qrelational,
	    Qjava_operator_precedence);
    list_constant_35 = STATIC_LIST_STAR((SI_Long)3L,list_constant_21,
	    string_constant_34,list_constant_25);
    mutate_global_property(Qgreater_than_equal,list_constant_35,
	    Qjava_operator_emitter_template);
    Qgreater_than_equal_fixnum = STATIC_SYMBOL("GREATER-THAN-EQUAL-FIXNUM",
	    AB_package);
    mutate_global_property(Qgreater_than_equal_fixnum,Qgreater_than_equal,
	    Qequivalent_java_operator);
    Qgreater_than_equal_quantity = 
	    STATIC_SYMBOL("GREATER-THAN-EQUAL-QUANTITY",AB_package);
    mutate_global_property(Qgreater_than_equal_quantity,
	    Qgreater_than_equal,Qequivalent_java_operator);
    mutate_global_property(Qgreater_than_equal_fixnum,Qgreater_than_equal,
	    Qequivalent_java_operator);
    Qless_than = STATIC_SYMBOL("LESS-THAN",AB_package);
    mutate_global_property(Qless_than,Qrelational,Qjava_operator_precedence);
    string_constant_154 = STATIC_STRING(" < ");
    list_constant_36 = STATIC_LIST_STAR((SI_Long)3L,list_constant_21,
	    string_constant_154,list_constant_25);
    mutate_global_property(Qless_than,list_constant_36,
	    Qjava_operator_emitter_template);
    Qless_than_fixnum = STATIC_SYMBOL("LESS-THAN-FIXNUM",AB_package);
    mutate_global_property(Qless_than_fixnum,Qless_than,
	    Qequivalent_java_operator);
    Qless_than_quantity = STATIC_SYMBOL("LESS-THAN-QUANTITY",AB_package);
    mutate_global_property(Qless_than_quantity,Qless_than,
	    Qequivalent_java_operator);
    mutate_global_property(Qless_than_fixnum,Qless_than,
	    Qequivalent_java_operator);
    Qless_than_equal = STATIC_SYMBOL("LESS-THAN-EQUAL",AB_package);
    mutate_global_property(Qless_than_equal,Qrelational,
	    Qjava_operator_precedence);
    list_constant_37 = STATIC_LIST_STAR((SI_Long)3L,list_constant_21,
	    string_constant_33,list_constant_25);
    mutate_global_property(Qless_than_equal,list_constant_37,
	    Qjava_operator_emitter_template);
    Qless_than_equal_fixnum = STATIC_SYMBOL("LESS-THAN-EQUAL-FIXNUM",
	    AB_package);
    mutate_global_property(Qless_than_equal_fixnum,Qless_than_equal,
	    Qequivalent_java_operator);
    mutate_global_property(Qgreater_than_equal_quantity,Qless_than_equal,
	    Qequivalent_java_operator);
    mutate_global_property(Qless_than_equal_fixnum,Qless_than_equal,
	    Qequivalent_java_operator);
    mutate_global_property(Qconditional,Qconditional,
	    Qjava_operator_precedence);
    string_constant_155 = STATIC_STRING(" \? ");
    string_constant_156 = STATIC_STRING(" : ");
    list_constant_38 = STATIC_LIST((SI_Long)2L,Qarg,FIX((SI_Long)3L));
    list_constant_39 = STATIC_LIST((SI_Long)5L,list_constant_21,
	    string_constant_155,list_constant_22,string_constant_156,
	    list_constant_38);
    mutate_global_property(Qconditional,list_constant_39,
	    Qjava_operator_emitter_template);
    Qif_expression = STATIC_SYMBOL("IF-EXPRESSION",AB_package);
    mutate_global_property(Qif_expression,Qconditional,
	    Qequivalent_java_operator);
    Qarray_element = STATIC_SYMBOL("ARRAY-ELEMENT",AB_package);
    mutate_global_property(Qarray_element,Qprimary,Qjava_operator_precedence);
    string_constant_157 = STATIC_STRING("[");
    string_constant_158 = STATIC_STRING("]");
    list_constant_40 = STATIC_LIST((SI_Long)4L,list_constant_21,
	    string_constant_157,list_constant_22,string_constant_158);
    mutate_global_property(Qarray_element,list_constant_40,
	    Qjava_operator_emitter_template);
    Qnth_sequence_element = STATIC_SYMBOL("NTH-SEQUENCE-ELEMENT",AB_package);
    mutate_global_property(Qnth_sequence_element,Qarray_element,
	    Qequivalent_java_operator);
    Qarray_length = STATIC_SYMBOL("ARRAY-LENGTH",AB_package);
    mutate_global_property(Qarray_length,Qprimary,Qjava_operator_precedence);
    string_constant_159 = STATIC_STRING(".length");
    list_constant_41 = STATIC_LIST((SI_Long)2L,list_constant_21,
	    string_constant_159);
    mutate_global_property(Qarray_length,list_constant_41,
	    Qjava_operator_emitter_template);
    mutate_global_property(Qarray_length,Qarray_length,
	    Qequivalent_java_operator);
    Qint2float = STATIC_SYMBOL("INT2FLOAT",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)11L,Qvalue2integer,
	    Qvalue2quantity,Qvalue2float,Qvalue2text,Qvalue2symbol,
	    Qvalue2truth_value,Qvalue2sequence,Qvalue2struct,Qvalue2datum,
	    Qvalue2frame,Qint2float);
    Qget_slot_or_no_item = STATIC_SYMBOL("GET-SLOT-OR-NO-ITEM",AB_package);
    string_constant_43 = 
	    STATIC_STRING("evaluated attribute/field names needs reflection API");
    Qnew_class_instance = STATIC_SYMBOL("NEW-CLASS-INSTANCE",AB_package);
    string_constant_44 = STATIC_STRING("unrecognized expression type ~a");
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qtext_constant = STATIC_SYMBOL("TEXT-CONSTANT",AB_package);
    array_constant_62 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)0L,(SI_Long)43L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)7L,(SI_Long)57344L);
    array_constant_63 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)1L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)2L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)7L,(SI_Long)57344L);
    list_constant_7 = STATIC_CONS(Qab_structure,Qnil);
    list_constant_8 = STATIC_CONS(Qsequence,Qnil);
    Qdatum = STATIC_SYMBOL("DATUM",AB_package);
    string_constant_45 = STATIC_STRING("real casts are NYI");
    string_constant_46 = 
	    STATIC_STRING("attribute/field access expression too complex ~a");
    string_constant_47 = 
	    STATIC_STRING("INTERNAL ERROR: could never cast ~s to ~NT");
    array_constant_64 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)0L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)4L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)7L,(SI_Long)57344L);
    array_constant_65 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)0L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)1L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)4L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)7L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)15L,(SI_Long)57344L);
    array_constant_66 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)0L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)1L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)6L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)15L,(SI_Long)57344L);
    string_constant_48 = STATIC_STRING("(");
    string_constant_49 = STATIC_STRING(")");
    string_constant_50 = STATIC_STRING("INTERNAL ERROR: unhandled cast ~NT");
    string_constant_51 = STATIC_STRING("unknown slot, ~s, for class ~s ");
    string_constant_52 = 
	    STATIC_STRING("attribute/field access to non g2-defined classes is NYI");
    Qfetch_local_or_no_item = STATIC_SYMBOL("FETCH-LOCAL-OR-NO-ITEM",
	    AB_package);
    Qinteger_constant = STATIC_SYMBOL("INTEGER-CONSTANT",AB_package);
    Qfloat_constant = STATIC_SYMBOL("FLOAT-CONSTANT",AB_package);
    Qlong_constant = STATIC_SYMBOL("LONG-CONSTANT",AB_package);
    string_constant_53 = STATIC_STRING("Symbol.intern(\"~A\")");
    Qtruth_value_constant = STATIC_SYMBOL("TRUTH-VALUE-CONSTANT",AB_package);
    Qtrue = STATIC_SYMBOL("TRUE",AB_package);
    array_constant_67 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)7L,(SI_Long)57344L);
    Qfalse = STATIC_SYMBOL("FALSE",AB_package);
    array_constant_68 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)7L,(SI_Long)57344L);
    string_constant_54 = 
	    STATIC_STRING("Truth-Value constants (~a) not yet implemented");
    string_constant_55 = 
	    string_append2(STATIC_STRING("The value of (CADR NODE) (~s), is not one of (FETCH-LOCAL FETCH-LOCAL-OR-NO-ITEM INTEGER-CONSTANT FLOAT-CONSTANT LONG-CONSTANT SYMBOL-CONSTANT TEXT-CONSTANT TRUTH-VALUE-CONSTA"),
	    STATIC_STRING("NT)."));
}
