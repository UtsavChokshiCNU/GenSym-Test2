/* chnng.c
 * Input file:  chaining.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "chnng.h"


Object Forward_chaining_list_kbprop = UNBOUND;

Object Cached_class_forward_chaining_list_kbprop = UNBOUND;

Object Backward_chaining_list_kbprop = UNBOUND;

Object Cached_class_backward_chaining_list_kbprop = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Available_installation_conses, Qavailable_installation_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_installation_conses_tail, Qavailable_installation_conses_tail);

Object Available_installation_conses_vector = UNBOUND;

Object Available_installation_conses_tail_vector = UNBOUND;

Object Installation_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Installation_cons_counter, Qinstallation_cons_counter);

/* OUTSTANDING-INSTALLATION-CONSES */
Object outstanding_installation_conses()
{
    Object temp;

    x_note_fn_call(153,0);
    temp = FIXNUM_MINUS(Installation_cons_counter,
	    length(Available_installation_conses));
    return VALUES_1(temp);
}

/* INSTALLATION-CONS-MEMORY-USAGE */
Object installation_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(153,1);
    temp = FIXNUM_TIMES(Installation_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-INSTALLATION-CONS-POOL */
Object replenish_installation_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(153,2);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qinstallation_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_installation_conses_vector,
	    IFIX(Current_thread_index))) {
	svref_arg_1 = Available_installation_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_installation_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_installation_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_installation_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Installation_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qinstallation;       /* installation */

/* INSTALLATION-CONS-1 */
Object installation_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(153,3);
    new_cons = ISVREF(Available_installation_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_installation_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_installation_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_installation_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_installation_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qinstallation);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-INSTALLATION-LIST-POOL */
Object replenish_installation_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(153,4);
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
    if (ISVREF(Available_installation_conses_vector,
	    IFIX(Current_thread_index))) {
	svref_arg_1 = Available_installation_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_installation_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_installation_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_installation_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qinstallation_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-INSTALLATION-LIST-1 */
Object make_installation_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(153,5);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_installation_conses_vector,
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
	replenish_installation_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_installation_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qinstallation);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_installation_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_installation_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_installation_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_installation_conses_tail_vector;
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

/* INSTALLATION-LIST-2 */
Object installation_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(153,6);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_installation_conses_vector,
	    IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_installation_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_installation_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qinstallation);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_installation_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_installation_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_installation_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_installation_conses_tail_vector;
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

/* INSTALLATION-LIST-3 */
Object installation_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(153,7);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_installation_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_installation_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_installation_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qinstallation);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_installation_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_installation_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_installation_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_installation_conses_tail_vector;
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

/* INSTALLATION-LIST-4 */
Object installation_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(153,8);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_installation_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_installation_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_installation_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qinstallation);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_installation_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_installation_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_installation_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_installation_conses_tail_vector;
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

/* INSTALLATION-LIST-TRACE-HOOK */
Object installation_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(153,9);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-INSTALLATION-CONSES-1 */
Object copy_tree_using_installation_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(153,10);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_installation_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_installation_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_installation_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_installation_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_installation_cons_pool();
	temp_1 = copy_tree_using_installation_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qinstallation);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_installation_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_installation_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_installation_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_installation_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_installation_cons_pool();
	temp_1 = 
		copy_tree_using_installation_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qinstallation);
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

/* COPY-LIST-USING-INSTALLATION-CONSES-1 */
Object copy_list_using_installation_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(153,11);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_installation_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_installation_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_installation_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_installation_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_installation_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qinstallation);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_installation_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_installation_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_installation_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_installation_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_installation_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qinstallation);
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

/* RECLAIM-INSTALLATION-CONS-1 */
Object reclaim_installation_cons_1(installation_cons)
    Object installation_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(153,12);
    inline_note_reclaim_cons(installation_cons,Qinstallation);
    if (ISVREF(Available_installation_conses_tail_vector,
	    IFIX(Current_thread_index))) {
	temp = ISVREF(Available_installation_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = installation_cons;
	temp = Available_installation_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = installation_cons;
    }
    else {
	temp = Available_installation_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = installation_cons;
	temp = Available_installation_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = installation_cons;
    }
    M_CDR(installation_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-INSTALLATION-LIST-1 */
Object reclaim_installation_list_1(installation_list)
    Object installation_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(153,13);
    if (installation_list) {
	last_1 = installation_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qinstallation);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qinstallation);
	if (ISVREF(Available_installation_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_installation_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = installation_list;
	    temp = Available_installation_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_installation_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = installation_list;
	    temp = Available_installation_conses_tail_vector;
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

/* RECLAIM-INSTALLATION-LIST*-1 */
Object reclaim_installation_list_star_1(installation_list)
    Object installation_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(153,14);
    if (CONSP(installation_list)) {
	temp = last(installation_list,_);
	M_CDR(temp) = Nil;
	if (installation_list) {
	    last_1 = installation_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qinstallation);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qinstallation);
	    if (ISVREF(Available_installation_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_installation_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = installation_list;
		temp = Available_installation_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_installation_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = installation_list;
		temp = Available_installation_conses_tail_vector;
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

/* RECLAIM-INSTALLATION-TREE-1 */
Object reclaim_installation_tree_1(tree)
    Object tree;
{
    Object e, e2, installation_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(153,15);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_installation_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		installation_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(installation_cons,Qinstallation);
		if (EQ(installation_cons,e))
		    goto end_1;
		else if ( !TRUEP(installation_cons))
		    goto end_1;
		else
		    installation_cons = CDR(installation_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_installation_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_installation_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_installation_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_installation_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_installation_conses_tail_vector;
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

/* DELETE-INSTALLATION-ELEMENT-1 */
Object delete_installation_element_1(element,installation_list)
    Object element, installation_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(153,16);
    if (installation_list) {
	if (EQ(element,M_CAR(installation_list))) {
	    temp = CDR(installation_list);
	    inline_note_reclaim_cons(installation_list,Qinstallation);
	    if (ISVREF(Available_installation_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_installation_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = installation_list;
		temp_1 = Available_installation_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = installation_list;
	    }
	    else {
		temp_1 = Available_installation_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = installation_list;
		temp_1 = Available_installation_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = installation_list;
	    }
	    M_CDR(installation_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = installation_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qinstallation);
		if (ISVREF(Available_installation_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = 
			    ISVREF(Available_installation_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_installation_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_installation_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_installation_conses_tail_vector;
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
	    temp = installation_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-INSTALLATION-CONS-1 */
Object delete_installation_cons_1(installation_cons,installation_list)
    Object installation_cons, installation_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(153,17);
    if (EQ(installation_cons,installation_list))
	temp = CDR(installation_list);
    else {
	l_trailer_qm = Nil;
	l = installation_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,installation_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = installation_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_installation_cons_1(installation_cons);
    return VALUES_1(temp);
}

/* EQUAL-FORWARD-CHAINING-LINK */
Object equal_forward_chaining_link(link1,link2)
    Object link1, link2;
{
    Object temp, temp_1;
    char temp_2;

    x_note_fn_call(153,18);
    if (EQ(ISVREF(link1,(SI_Long)2L),ISVREF(link2,(SI_Long)2L)) || 
	    equal_true_value_update_recipients(ISVREF(link1,(SI_Long)2L),
	    ISVREF(link2,(SI_Long)2L))) {
	temp = ISVREF(link1,(SI_Long)3L);
	temp_1 = ISVREF(link2,(SI_Long)3L);
	temp_2 = EQUAL(temp,temp_1);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	temp = ISVREF(link1,(SI_Long)4L);
	temp_1 = ISVREF(link2,(SI_Long)4L);
	temp_2 = EQUAL(temp,temp_1);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	temp = ISVREF(link1,(SI_Long)5L);
	temp_1 = ISVREF(link2,(SI_Long)5L);
	temp_2 = EQUAL(temp,temp_1);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	temp = ISVREF(link1,(SI_Long)6L);
	temp_1 = ISVREF(link2,(SI_Long)6L);
	temp_2 = EQUAL(temp,temp_1);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	temp = ISVREF(link1,(SI_Long)7L);
	temp_1 = ISVREF(link2,(SI_Long)7L);
	temp_2 = EQUAL(temp,temp_1);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	temp = ISVREF(link1,(SI_Long)8L);
	temp_1 = ISVREF(link2,(SI_Long)8L);
	temp_2 = EQUAL(temp,temp_1);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	temp = ISVREF(link1,(SI_Long)9L);
	temp_1 = ISVREF(link2,(SI_Long)9L);
	temp_2 = EQUAL(temp,temp_1);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	temp = ISVREF(link1,(SI_Long)10L);
	temp_1 = ISVREF(link2,(SI_Long)10L);
	return VALUES_1(EQUAL(temp,temp_1) ? T : Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qtrue_value_update_recipient;  /* true-value-update-recipient */

static Object Qdependent_frame_has_no_owner;  /* dependent-frame-has-no-owner */

/* MAKE-TRUE-VALUE-UPDATE-RECIPIENT */
Object make_true_value_update_recipient(true_value_update_function,
	    true_value_update_frame,true_value_update_argument)
    Object true_value_update_function, true_value_update_frame;
    Object true_value_update_argument;
{
    Object new_frame, current_block_of_dependent_frame, svref_new_value;
    Declare_special(1);

    x_note_fn_call(153,19);
    new_frame = make_frame(Qtrue_value_update_recipient);
    current_block_of_dependent_frame = Qdependent_frame_has_no_owner;
    PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
	    0);
      if (Noting_changes_to_kb_p)
	  note_change_to_dependent_frame_1();
      SVREF(new_frame,FIX((SI_Long)2L)) = true_value_update_function;
      if (Noting_changes_to_kb_p)
	  note_change_to_dependent_frame_1();
      SVREF(new_frame,FIX((SI_Long)3L)) = true_value_update_frame;
      if (Noting_changes_to_kb_p)
	  note_change_to_dependent_frame_1();
      svref_new_value = copy_for_slot_value(true_value_update_argument);
      SVREF(new_frame,FIX((SI_Long)4L)) = svref_new_value;
    POP_SPECIAL();
    return VALUES_1(new_frame);
}

/* COPY-FRAME-FOR-TRUE-VALUE-UPDATE-RECIPIENT */
Object copy_frame_for_true_value_update_recipient(true_value_update_recipient)
    Object true_value_update_recipient;
{
    x_note_fn_call(153,20);
    return make_true_value_update_recipient(ISVREF(true_value_update_recipient,
	    (SI_Long)2L),ISVREF(true_value_update_recipient,(SI_Long)3L),
	    ISVREF(true_value_update_recipient,(SI_Long)4L));
}

/* EQUAL-TRUE-VALUE-UPDATE-RECIPIENTS */
Object equal_true_value_update_recipients(thing1,thing2)
    Object thing1, thing2;
{
    Object sub_class_bit_vector, temp_1, temp_2;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(153,21);
    sub_class_bit_vector = ISVREF(ISVREF(thing1,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(True_value_update_recipient_class_description,
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
	sub_class_bit_vector = ISVREF(ISVREF(thing2,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(True_value_update_recipient_class_description,
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
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	temp_1 = ISVREF(thing1,(SI_Long)2L);
	temp_2 = ISVREF(thing2,(SI_Long)2L);
	temp = EQUAL(temp_1,temp_2);
    }
    else
	temp = TRUEP(Nil);
    if (temp ? EQ(ISVREF(thing1,(SI_Long)3L),ISVREF(thing2,(SI_Long)3L)) : 
	    TRUEP(Nil)) {
	temp_1 = ISVREF(thing1,(SI_Long)4L);
	temp_2 = ISVREF(thing2,(SI_Long)4L);
	return VALUES_1(EQUAL(temp_1,temp_2) ? T : Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qforward_chaining_link;  /* forward-chaining-link */

/* MAKE-FORWARD-CHAINING-LINK */
Object make_forward_chaining_link varargs_1(int, n)
{
    Object forward_link_recipient, forward_link_designation;
    Object forward_link_focus, forward_link_focus_local_name;
    Object forward_link_symbolic_value, forward_link_sense;
    Object forward_link_second_designation, forward_link_second_focus;
    Object forward_link_second_focus_local_name, new_frame;
    Object current_block_of_dependent_frame, svref_new_value;
    Declare_varargs_nonrelocating;
    Declare_special(1);

    x_note_fn_call(153,22);
    INIT_ARGS_nonrelocating();
    forward_link_recipient = REQUIRED_ARG_nonrelocating();
    forward_link_designation = REQUIRED_ARG_nonrelocating();
    forward_link_focus = REQUIRED_ARG_nonrelocating();
    forward_link_focus_local_name = REQUIRED_ARG_nonrelocating();
    forward_link_symbolic_value = REQUIRED_ARG_nonrelocating();
    forward_link_sense = REQUIRED_ARG_nonrelocating();
    forward_link_second_designation = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    forward_link_second_focus = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    forward_link_second_focus_local_name = OPTIONAL_ARG_P_nonrelocating() ?
	     OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    new_frame = make_frame(Qforward_chaining_link);
    current_block_of_dependent_frame = Qdependent_frame_has_no_owner;
    PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
	    0);
      if (Noting_changes_to_kb_p)
	  note_change_to_dependent_frame_1();
      svref_new_value = copy_for_slot_value(forward_link_recipient);
      SVREF(new_frame,FIX((SI_Long)2L)) = svref_new_value;
      if (Noting_changes_to_kb_p)
	  note_change_to_dependent_frame_1();
      svref_new_value = 
	      make_simple_designation_slot_value_copy(forward_link_designation);
      SVREF(new_frame,FIX((SI_Long)3L)) = svref_new_value;
      if (Noting_changes_to_kb_p)
	  note_change_to_dependent_frame_1();
      SVREF(new_frame,FIX((SI_Long)4L)) = forward_link_focus;
      if (Noting_changes_to_kb_p)
	  note_change_to_dependent_frame_1();
      SVREF(new_frame,FIX((SI_Long)5L)) = forward_link_focus_local_name;
      if (Noting_changes_to_kb_p)
	  note_change_to_dependent_frame_1();
      SVREF(new_frame,FIX((SI_Long)6L)) = forward_link_symbolic_value;
      if (Noting_changes_to_kb_p)
	  note_change_to_dependent_frame_1();
      SVREF(new_frame,FIX((SI_Long)7L)) = forward_link_sense;
      if (Noting_changes_to_kb_p)
	  note_change_to_dependent_frame_1();
      svref_new_value = 
	      make_simple_designation_slot_value_copy(forward_link_second_designation);
      SVREF(new_frame,FIX((SI_Long)8L)) = svref_new_value;
      if (Noting_changes_to_kb_p)
	  note_change_to_dependent_frame_1();
      SVREF(new_frame,FIX((SI_Long)9L)) = forward_link_second_focus;
      if (Noting_changes_to_kb_p)
	  note_change_to_dependent_frame_1();
      SVREF(new_frame,FIX((SI_Long)10L)) = 
	      forward_link_second_focus_local_name;
    POP_SPECIAL();
    return VALUES_1(new_frame);
}

/* COPY-FRAME-FOR-FORWARD-CHAINING-LINK */
Object copy_frame_for_forward_chaining_link(forward_chaining_link)
    Object forward_chaining_link;
{
    x_note_fn_call(153,23);
    return make_forward_chaining_link(9,ISVREF(forward_chaining_link,
	    (SI_Long)2L),ISVREF(forward_chaining_link,(SI_Long)3L),
	    ISVREF(forward_chaining_link,(SI_Long)4L),
	    ISVREF(forward_chaining_link,(SI_Long)5L),
	    ISVREF(forward_chaining_link,(SI_Long)6L),
	    ISVREF(forward_chaining_link,(SI_Long)7L),
	    ISVREF(forward_chaining_link,(SI_Long)8L),
	    ISVREF(forward_chaining_link,(SI_Long)9L),
	    ISVREF(forward_chaining_link,(SI_Long)10L));
}

Object The_type_description_of_event_detector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_event_detectors, Qchain_of_available_event_detectors);

DEFINE_VARIABLE_WITH_SYMBOL(Event_detector_count, Qevent_detector_count);

Object Chain_of_available_event_detectors_vector = UNBOUND;

/* EVENT-DETECTOR-STRUCTURE-MEMORY-USAGE */
Object event_detector_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(153,24);
    temp = Event_detector_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)5L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-EVENT-DETECTOR-COUNT */
Object outstanding_event_detector_count()
{
    Object def_structure_event_detector_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(153,25);
    gensymed_symbol = IFIX(Event_detector_count);
    def_structure_event_detector_variable = Chain_of_available_event_detectors;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_event_detector_variable))
	goto end_loop;
    def_structure_event_detector_variable = 
	    ISVREF(def_structure_event_detector_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-EVENT-DETECTOR-1 */
Object reclaim_event_detector_1(event_detector)
    Object event_detector;
{
    Object temp, svref_arg_2;

    x_note_fn_call(153,26);
    inline_note_reclaim_cons(event_detector,Nil);
    temp = ISVREF(Chain_of_available_event_detectors_vector,
	    IFIX(Current_thread_index));
    SVREF(event_detector,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_event_detectors_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = event_detector;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-EVENT-DETECTOR */
Object reclaim_structure_for_event_detector(event_detector)
    Object event_detector;
{
    x_note_fn_call(153,27);
    return reclaim_event_detector_1(event_detector);
}

static Object Qg2_defstruct_structure_name_event_detector_g2_struct;  /* g2-defstruct-structure-name::event-detector-g2-struct */

/* MAKE-PERMANENT-EVENT-DETECTOR-STRUCTURE-INTERNAL */
Object make_permanent_event_detector_structure_internal()
{
    Object def_structure_event_detector_variable;
    Object defstruct_g2_event_detector_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(153,28);
    def_structure_event_detector_variable = Nil;
    atomic_incff_symval(Qevent_detector_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_event_detector_variable = Nil;
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
	defstruct_g2_event_detector_variable = the_array;
	SVREF(defstruct_g2_event_detector_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_event_detector_g2_struct;
	def_structure_event_detector_variable = 
		defstruct_g2_event_detector_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_event_detector_variable);
}

/* MAKE-EVENT-DETECTOR-1 */
Object make_event_detector_1(event_detector_type,
	    event_detector_monitored_block,event_detector_consumer,
	    event_detector_extra_information)
    Object event_detector_type, event_detector_monitored_block;
    Object event_detector_consumer, event_detector_extra_information;
{
    Object def_structure_event_detector_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(153,29);
    def_structure_event_detector_variable = 
	    ISVREF(Chain_of_available_event_detectors_vector,
	    IFIX(Current_thread_index));
    if (def_structure_event_detector_variable) {
	svref_arg_1 = Chain_of_available_event_detectors_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_event_detector_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_event_detector_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_event_detector_g2_struct;
    }
    else
	def_structure_event_detector_variable = 
		make_permanent_event_detector_structure_internal();
    inline_note_allocate_cons(def_structure_event_detector_variable,Nil);
    SVREF(def_structure_event_detector_variable,FIX((SI_Long)1L)) = 
	    event_detector_type;
    SVREF(def_structure_event_detector_variable,FIX((SI_Long)2L)) = 
	    event_detector_monitored_block;
    SVREF(def_structure_event_detector_variable,FIX((SI_Long)3L)) = 
	    event_detector_consumer;
    SVREF(def_structure_event_detector_variable,FIX((SI_Long)4L)) = 
	    event_detector_extra_information;
    return VALUES_1(def_structure_event_detector_variable);
}

/* CHAINING-SYMBOL-FOR-DESIGNATION */
Object chaining_symbol_for_designation(designation)
    Object designation;
{
    x_note_fn_call(153,30);
    if (SYMBOLP(designation))
	return VALUES_1(designation);
    else
	return atomic_naming_element_of_role(role_of_designation(designation));
}

/* LOCAL-NAME-FOR-DESIGNATION */
Object local_name_for_designation(designation)
    Object designation;
{
    Object role;

    x_note_fn_call(153,31);
    role = role_of_designation(designation);
    if ( !TRUEP(role) || simple_role_p(role))
	return VALUES_1(Nil);
    else
	return VALUES_1(CDR(role));
}

/* SIMPLE-INSTALLATION-DESIGNATION */
Object simple_installation_designation(designation)
    Object designation;
{
    Object temp, temp_1, domain, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp_2;

    x_note_fn_call(153,32);
    if (ATOM(designation))
	return VALUES_1(designation);
    else {
	temp = FIRST(designation);
	temp_1 = simple_installation_role(designation);
	domain = Nil;
	ab_loop_list_ = CDDR(designation);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	domain = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = 
		installation_cons_1(simple_installation_designation(domain),
		Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	temp_2 = ab_loopvar_;
	goto end_1;
	temp_2 = Qnil;
      end_1:;
	return installation_cons_1(temp,installation_cons_1(temp_1,temp_2));
    }
}

/* SIMPLE-INSTALLATION-ROLE */
Object simple_installation_role(designation)
    Object designation;
{
    x_note_fn_call(153,33);
    return copy_tree_using_installation_conses_1(simple_role_of_role(role_of_designation(designation)));
}

/* MAKE-SIMPLE-DESIGNATION-SLOT-VALUE-COPY */
Object make_simple_designation_slot_value_copy(designation)
    Object designation;
{
    Object temp, temp_1, domain, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp_2;

    x_note_fn_call(153,34);
    if (ATOM(designation))
	return VALUES_1(designation);
    else {
	temp = FIRST(designation);
	temp_1 = make_simple_role_slot_value_copy(designation);
	domain = Nil;
	ab_loop_list_ = CDDR(designation);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	domain = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = 
		slot_value_cons_1(make_simple_designation_slot_value_copy(domain),
		Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	temp_2 = ab_loopvar_;
	goto end_1;
	temp_2 = Qnil;
      end_1:;
	return slot_value_cons_1(temp,slot_value_cons_1(temp_1,temp_2));
    }
}

/* MAKE-SIMPLE-ROLE-SLOT-VALUE-COPY */
Object make_simple_role_slot_value_copy(designation)
    Object designation;
{
    x_note_fn_call(153,35);
    return copy_tree_using_slot_value_conses_1(simple_role_of_role(role_of_designation(designation)));
}

/* CHAINING-FOCAL-ROLE-AND-LOCAL-NAME-FOR-DESIGNATION */
Object chaining_focal_role_and_local_name_for_designation(designation)
    Object designation;
{
    Object role, temp, temp_1;

    x_note_fn_call(153,36);
    if (CONSP(designation)) {
	role = role_of_designation(designation);
	temp = simple_role_of_role(role);
	if (SYMBOLP(temp) && domain_of_designation(designation))
	    return chaining_focal_role_and_local_name_for_designation(domain_of_designation(designation));
	else {
	    temp_1 = atomic_naming_element_of_role(role);
	    temp = get_explicitly_specified_local_name_of_role_if_any(role);
	    return VALUES_2(temp_1,temp);
	}
    }
    else
	return VALUES_2(Nil,Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Function_templates, Qfunction_templates);

/* DEF-FUNCTION-TEMPLATE */
Object def_function_template(new_function_template)
    Object new_function_template;
{
    Object gensymed_symbol, gensymed_symbol_1, template_name, template_cons;

    x_note_fn_call(153,37);
    gensymed_symbol = new_function_template;
    gensymed_symbol_1 = Function_templates;
    template_name = CAR(gensymed_symbol);
    template_cons = gensymed_symbol_1;
  next_loop:
    if ( !TRUEP(template_cons))
	goto end_loop;
    if (EQ(template_name,CAAR(template_cons))) {
	M_CAR(template_cons) = gensymed_symbol;
	return VALUES_1(template_name);
    }
    template_cons = M_CDR(template_cons);
    goto next_loop;
  end_loop:
    Function_templates = CONS(gensymed_symbol,gensymed_symbol_1);
    return VALUES_1(template_name);
    return VALUES_1(Qnil);
}

/* LOOKUP-FUNCTION-TEMPLATE */
Object lookup_function_template(function_name)
    Object function_name;
{
    x_note_fn_call(153,38);
    return assq_function(function_name,Function_templates);
}

DEFINE_VARIABLE_WITH_SYMBOL(Action_templates, Qaction_templates);

/* DEF-ACTION-TEMPLATE */
Object def_action_template(new_action_template)
    Object new_action_template;
{
    Object gensymed_symbol, gensymed_symbol_1, template_name, template_cons;

    x_note_fn_call(153,39);
    gensymed_symbol = new_action_template;
    gensymed_symbol_1 = Action_templates;
    template_name = CAR(gensymed_symbol);
    template_cons = gensymed_symbol_1;
  next_loop:
    if ( !TRUEP(template_cons))
	goto end_loop;
    if (EQ(template_name,CAAR(template_cons))) {
	M_CAR(template_cons) = gensymed_symbol;
	return VALUES_1(template_name);
    }
    template_cons = M_CDR(template_cons);
    goto next_loop;
  end_loop:
    Action_templates = CONS(gensymed_symbol,gensymed_symbol_1);
    return VALUES_1(template_name);
    return VALUES_1(Qnil);
}

/* LOOKUP-ACTION-TEMPLATE */
Object lookup_action_template(action_name)
    Object action_name;
{
    x_note_fn_call(153,40);
    return assq_function(action_name,Action_templates);
}

static Object Qparent_frame;       /* parent-frame */

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

static Object Qparent_attribute_name;  /* parent-attribute-name */

/* MAKE-PARENT-STACK */
Object make_parent_stack(entity)
    Object entity;
{
    Object child, parent_qm, parent_name_or_names_qm, parent_name_cons_qm;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, new_cons, temp;
    Object svref_arg_2, svref_new_value, gensymed_symbol, gensymed_symbol_1;
    Object temp_1, gensymed_symbol_2;

    x_note_fn_call(153,41);
    child = entity;
    parent_qm = Nil;
    parent_name_or_names_qm = Nil;
    parent_name_cons_qm = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    parent_qm = get_lookup_slot_value_given_default(child,Qparent_frame,Nil);
    if ( !TRUEP(parent_qm))
	goto end_loop;
    parent_name_or_names_qm = 
	    get_lookup_slot_value_given_default(parent_qm,
	    Qname_or_names_for_frame,Nil);
    if (parent_name_or_names_qm && SYMBOLP(parent_name_or_names_qm)) {
	new_cons = ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_eval_cons_pool();
	M_CAR(gensymed_symbol) = parent_name_or_names_qm;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qeval);
	parent_name_cons_qm = gensymed_symbol;
    }
    else
	parent_name_cons_qm = Nil;
    new_cons = ISVREF(Available_eval_conses_vector,IFIX(Current_thread_index));
    if (new_cons) {
	temp = Available_eval_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_eval_cons_pool();
    gensymed_symbol_1 = Nil;
  next_loop_1:
    temp_1 = ISVREF(Available_eval_conses_vector,IFIX(Current_thread_index));
    temp_1 = CDR(temp_1);
    temp_1 = CDR(temp_1);
    gensymed_symbol_1 = CDR(temp_1);
    if (gensymed_symbol_1)
	goto end_loop_1;
    replenish_eval_list_pool(FIX((SI_Long)3L));
    goto next_loop_1;
  end_loop_1:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_2 = ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index));
      next_loop_2:
	inline_note_allocate_cons(gensymed_symbol_2,Qeval);
	if (EQ(gensymed_symbol_2,gensymed_symbol_1))
	    goto end_loop_2;
	gensymed_symbol_2 = CDR(gensymed_symbol_2);
	goto next_loop_2;
      end_loop_2:;
    }
    temp_1 = ISVREF(Available_eval_conses_vector,IFIX(Current_thread_index));
    temp = Available_eval_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol_1);
    SVREF(temp,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
	    IFIX(Current_thread_index)))) {
	temp = Available_eval_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = Nil;
    }
    M_CDR(gensymed_symbol_1) = Nil;
    gensymed_symbol_1 = temp_1;
    goto end_1;
    gensymed_symbol_1 = Qnil;
  end_1:;
    gensymed_symbol_2 = gensymed_symbol_1;
    M_CAR(gensymed_symbol_2) = parent_qm;
    gensymed_symbol_2 = M_CDR(gensymed_symbol_2);
    temp = get_lookup_slot_value_given_default(child,
	    Qparent_attribute_name,Nil);
    M_CAR(gensymed_symbol_2) = temp;
    gensymed_symbol_2 = M_CDR(gensymed_symbol_2);
    temp = parent_name_cons_qm;
    if (temp);
    else
	temp = parent_name_or_names_qm;
    M_CAR(gensymed_symbol_2) = temp;
    gensymed_symbol_2 = M_CDR(gensymed_symbol_2);
    M_CAR(gensymed_symbol_2) = parent_name_cons_qm;
    M_CAR(gensymed_symbol) = gensymed_symbol_1;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qeval);
    ab_loopvar__2 = gensymed_symbol;
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    child = parent_qm;
    goto next_loop;
  end_loop:
    temp_1 = ab_loopvar_;
    goto end_2;
    temp_1 = Qnil;
  end_2:;
    return VALUES_1(temp_1);
}

/* RECLAIM-PARENT-STACK */
Object reclaim_parent_stack(parent_stack)
    Object parent_stack;
{
    Object trailer, current_entry_cons, entry, name_cons_cons, eval_cons, temp;
    Object svref_arg_2, temp_1;

    x_note_fn_call(153,42);
    if (parent_stack) {
	trailer = Nil;
	current_entry_cons = parent_stack;
	entry = Nil;
	name_cons_cons = Nil;
      next_loop:
	if ( !TRUEP(current_entry_cons))
	    goto end_loop;
	entry = M_CAR(current_entry_cons);
	name_cons_cons = M_CDR(M_CDR(M_CDR(entry)));
	if (M_CAR(name_cons_cons)) {
	    eval_cons = M_CAR(name_cons_cons);
	    inline_note_reclaim_cons(eval_cons,Qeval);
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = eval_cons;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = eval_cons;
	    }
	    else {
		temp = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = eval_cons;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = eval_cons;
	    }
	    M_CDR(eval_cons) = Nil;
	}
	if (entry &&  !((SI_Long)0L == inline_debugging_consing())) {
	    eval_cons = entry;
	  next_loop_1:
	    inline_note_reclaim_cons(eval_cons,Qeval);
	    if (EQ(eval_cons,name_cons_cons))
		goto end_1;
	    else if ( !TRUEP(eval_cons))
		goto end_1;
	    else
		eval_cons = CDR(eval_cons);
	    goto next_loop_1;
	  end_loop_1:
	  end_1:;
	}
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = entry;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = name_cons_cons;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = entry;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = name_cons_cons;
	}
	M_CDR(name_cons_cons) = Nil;
	trailer = current_entry_cons;
	current_entry_cons = M_CDR(current_entry_cons);
	goto next_loop;
      end_loop:
	if (parent_stack &&  !((SI_Long)0L == inline_debugging_consing())) {
	    eval_cons = parent_stack;
	  next_loop_2:
	    inline_note_reclaim_cons(eval_cons,Qeval);
	    if (EQ(eval_cons,trailer))
		goto end_2;
	    else if ( !TRUEP(eval_cons))
		goto end_2;
	    else
		eval_cons = CDR(eval_cons);
	    goto next_loop_2;
	  end_loop_2:
	  end_2:;
	}
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = parent_stack;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = trailer;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = parent_stack;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = trailer;
	}
	M_CDR(trailer) = Nil;
	temp_1 = Qnil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

static Object Qclass_qualified_name;  /* class-qualified-name */

/* FIND-REFERENCED-PARENT */
Object find_referenced_parent(parent_stack,designation)
    Object parent_stack, designation;
{
    Object parent_role, test_role, temp_1, slot_description_qm;
    Object domain_for_parent_qm, role, domain_qm, class_of_role_qm;
    Object parent_stack_entry, parent_frame, gensymed_symbol;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(153,43);
    if (parent_stack) {
	parent_role = M_CAR(M_CDR(M_CAR(parent_stack)));
	test_role = role_of_designation(designation);
	temp = EQ(parent_role,test_role);
	if (temp);
	else if (CONSP(test_role) && EQ(M_CAR(test_role),
		Qclass_qualified_name)) {
	    temp = CONSP(parent_role) && EQ(CONSP(test_role) ? 
		    M_CAR(M_CDR(test_role)) : Nil,M_CDR(parent_role)) ? 
		    EQ(CONSP(test_role) ? M_CAR(M_CDR(M_CDR(test_role))) : 
		    test_role,M_CAR(parent_role)) : TRUEP(Qnil);
	    if (temp);
	    else if (SYMBOLP(parent_role)) {
		temp_1 = CONSP(test_role) ? M_CAR(M_CDR(test_role)) : Nil;
		slot_description_qm = 
			get_slot_description_of_class_description_function(parent_role,
			ISVREF(M_CAR(M_CAR(parent_stack)),(SI_Long)1L),Nil);
		temp = EQ(temp_1,slot_description_qm ? 
			ISVREF(slot_description_qm,(SI_Long)3L) : Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    domain_for_parent_qm = domain_of_designation(designation);
	    if (domain_for_parent_qm) {
		role = Nil;
		domain_qm = Nil;
		class_of_role_qm = Nil;
		parent_stack_entry = CAR(parent_stack);
		parent_frame = Nil;
	      next_loop:
		parent_frame = M_CAR(parent_stack_entry);
		if (SYMBOLP(domain_for_parent_qm)) {
		    if (memq_function(domain_for_parent_qm,
			    M_CAR(M_CDR(M_CDR(parent_stack_entry)))))
			return VALUES_1(parent_frame);
		    else
			goto end_loop;
		}
		else {
		    role = role_of_designation(domain_for_parent_qm);
		    domain_qm = domain_of_designation(domain_for_parent_qm);
		    if (SYMBOLP(role)) {
			if (domain_qm) {
			    parent_stack = CDR(parent_stack);
			    parent_stack_entry = CAR(parent_stack);
			    if (parent_stack) {
				gensymed_symbol = 
					M_CAR(M_CDR(parent_stack_entry));
				temp = EQ(CONSP(gensymed_symbol) ? 
					M_CAR(gensymed_symbol) : 
					gensymed_symbol,role);
			    }
			    else
				temp = TRUEP(Nil);
			    if (temp)
				domain_for_parent_qm = domain_qm;
			    else
				goto end_loop;
			}
			else {
			    gensymed_symbol = 
				    lookup_global_or_kb_specific_property_value(role,
				    Class_description_gkbprop);
			    if (gensymed_symbol) {
				sub_class_bit_vector = 
					ISVREF(ISVREF(parent_frame,
					(SI_Long)1L),(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(gensymed_symbol,
					(SI_Long)18L));
				sub_class_vector_index = 
					superior_class_bit_number >>  -  - 
					(SI_Long)3L;
				if (sub_class_vector_index < 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					    {
				    gensymed_symbol_1 = 
					    UBYTE_8_ISAREF_1(sub_class_bit_vector,
					    sub_class_vector_index);
				    gensymed_symbol_2 = (SI_Long)1L;
				    gensymed_symbol_3 = 
					    superior_class_bit_number & 
					    (SI_Long)7L;
				    gensymed_symbol_2 = gensymed_symbol_2 
					    << gensymed_symbol_3;
				    gensymed_symbol_1 = gensymed_symbol_1 
					    & gensymed_symbol_2;
				    temp = (SI_Long)0L < gensymed_symbol_1;
				}
				else
				    temp = TRUEP(Nil);
			    }
			    else
				temp = TRUEP(Nil);
			    if (temp)
				return VALUES_1(parent_frame);
			    else
				goto end_loop;
			}
		    }
		    else {
			class_of_role_qm = 
				atomic_class_element_of_simple_role(role);
			if (class_of_role_qm) {
			    gensymed_symbol = 
				    lookup_global_or_kb_specific_property_value(class_of_role_qm,
				    Class_description_gkbprop);
			    if (gensymed_symbol) {
				sub_class_bit_vector = 
					ISVREF(ISVREF(parent_frame,
					(SI_Long)1L),(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(gensymed_symbol,
					(SI_Long)18L));
				sub_class_vector_index = 
					superior_class_bit_number >>  -  - 
					(SI_Long)3L;
				if (sub_class_vector_index < 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					    {
				    gensymed_symbol_1 = 
					    UBYTE_8_ISAREF_1(sub_class_bit_vector,
					    sub_class_vector_index);
				    gensymed_symbol_2 = (SI_Long)1L;
				    gensymed_symbol_3 = 
					    superior_class_bit_number & 
					    (SI_Long)7L;
				    gensymed_symbol_2 = gensymed_symbol_2 
					    << gensymed_symbol_3;
				    gensymed_symbol_1 = gensymed_symbol_1 
					    & gensymed_symbol_2;
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
			if (temp)
			    return VALUES_1(parent_frame);
			else
			    goto end_loop;
		    }
		}
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

DEFINE_VARIABLE_WITH_SYMBOL(Cached_classes_for_forward_chaining, Qcached_classes_for_forward_chaining);

DEFINE_VARIABLE_WITH_SYMBOL(Cached_classes_for_backward_chaining, Qcached_classes_for_backward_chaining);

/* DECACHE-CLASS-CHAINING-LISTS */
Object decache_class_chaining_lists()
{
    Object class_1, ab_loop_list_, cache, old_cache;

    x_note_fn_call(153,44);
    if (Cached_classes_for_backward_chaining) {
	class_1 = Nil;
	ab_loop_list_ = Cached_classes_for_backward_chaining;
	cache = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	class_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	cache = lookup_kb_specific_property_value(class_1,
		Cached_class_backward_chaining_list_kbprop);
	reclaim_eval_list_1(cache);
	mutate_kb_specific_property_value(class_1,Nil,
		Cached_class_backward_chaining_list_kbprop);
	goto next_loop;
      end_loop:;
	old_cache = Cached_classes_for_backward_chaining;
	if (CAS_SYMBOL(Qcached_classes_for_backward_chaining,old_cache,Nil))
	    reclaim_eval_list_1(old_cache);
    }
    if (Cached_classes_for_forward_chaining) {
	class_1 = Nil;
	ab_loop_list_ = Cached_classes_for_forward_chaining;
	cache = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	class_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	cache = lookup_kb_specific_property_value(class_1,
		Cached_class_forward_chaining_list_kbprop);
	reclaim_eval_list_1(cache);
	mutate_kb_specific_property_value(class_1,Nil,
		Cached_class_forward_chaining_list_kbprop);
	goto next_loop_1;
      end_loop_1:;
	old_cache = Cached_classes_for_forward_chaining;
	if (CAS_SYMBOL(Qcached_classes_for_forward_chaining,old_cache,Nil))
	    reclaim_eval_list_1(old_cache);
    }
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Links_and_objects, Qlinks_and_objects);

static Object Qitem;               /* item */

static Object Qeither;             /* either */

static Object Qreceives_a_value;   /* receives-a-value */

static Object Qloses_its_value;    /* loses-its-value */

/* COLLECT-FORWARD-CHAINING-FOR-LOGICAL-CLASS-REFERENCES */
Object collect_forward_chaining_for_logical_class_references(object,
	    new_value_sense,chaining_as_well_as_events_qm)
    Object object, new_value_sense, chaining_as_well_as_events_qm;
{
    Object link_1, class_description, classes, gensymed_symbol, list_1;
    Object cache_qm, ab_loop_list_, class_1, specific_list, new_value;
    Object old_value, link_sense, designation, temp, temp_2, role;
    Object continuation, expiration_qm, gensymed_symbol_1, gensymed_symbol_2;
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    char temp_1;
    Object result;

    x_note_fn_call(153,45);
    link_1 = Nil;
    class_description = ISVREF(object,(SI_Long)1L);
    classes = ISVREF(class_description,(SI_Long)2L);
    gensymed_symbol = M_CAR(classes);
    list_1 = INLINE_SYMBOL_PLIST(gensymed_symbol);
  next_loop:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop;
  end_loop:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_1:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Cached_class_forward_chaining_list_kbprop))
	goto end_loop_1;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_1;
  end_loop_1:
    cache_qm = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    if (cache_qm)
	ab_loop_list_ = M_CDR(cache_qm);
    else {
	class_1 = Nil;
	ab_loop_list_ = classes;
	specific_list = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	class_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	specific_list = lookup_kb_specific_property_value(class_1,
		Forward_chaining_list_kbprop);
	if (specific_list) {
	    specific_list = copy_list_using_eval_conses_1(specific_list);
	    if (cache_qm)
		cache_qm = nconc2(cache_qm,specific_list);
	    else
		cache_qm = specific_list;
	}
	if (EQ(class_1,Qitem))
	    goto end_loop_2;
	goto next_loop_2;
      end_loop_2:
	mutate_kb_specific_property_value(M_CAR(classes),eval_cons_1(Nil,
		cache_qm),Cached_class_forward_chaining_list_kbprop);
	new_value = eval_cons_1(M_CAR(classes),Nil);
	old_value = Nil;
      next_loop_3:
	old_value = Cached_classes_for_forward_chaining;
	M_CDR(new_value) = old_value;
	if (CAS_SYMBOL(Qcached_classes_for_forward_chaining,old_value,
		new_value))
	    goto end_loop_3;
	goto next_loop_3;
      end_loop_3:
	goto end_1;
      end_1:;
	ab_loop_list_ = cache_qm;
	goto end_2;
	ab_loop_list_ = Qnil;
      end_2:;
    }
    link_sense = Nil;
    designation = Nil;
  next_loop_4:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_4;
    link_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    link_sense = ISVREF(link_1,(SI_Long)7L);
    designation = ISVREF(link_1,(SI_Long)3L);
    if ((chaining_as_well_as_events_qm && (EQ(link_sense,Qeither) || 
	    EQ(new_value_sense,link_sense)) || EQ(link_sense,
	    Qreceives_a_value) || EQ(link_sense,Qloses_its_value)) &&  
	    !SYMBOLP(designation)) {
	if (domain_of_designation(designation)) {
	    temp = role_of_designation(designation);
	    temp_1 = SYMBOLP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_1 =  !temp_1;
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	temp_1 =  !TRUEP(domain_of_designation(designation));
	if (temp_1);
	else {
	    temp_2 = FIRST(designation);
	    temp = role_of_designation(designation);
	    result = serve_first_value_of_role_inverse(object,temp_2,temp,
		    domain_of_designation(designation));
	    MVS_3(result,role,continuation,expiration_qm);
	    if (expiration_qm) {
		if ( !(FIXNUMP(role) || SYMBOLP(role) || 
			SIMPLE_VECTOR_P(role)))
		    reclaim_if_evaluation_value_1(role);
	    }
	    if (continuation) {
		gensymed_symbol = M_CAR(continuation);
		gensymed_symbol_1 = Nil;
		gensymed_symbol_2 = continuation;
		inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
			gensymed_symbol_2);
	    }
	    temp_1 = TRUEP(expiration_qm);
	}
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
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
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_eval_cons_pool();
	M_CAR(gensymed_symbol) = link_1;
	M_CDR(gensymed_symbol) = object;
	inline_note_allocate_cons(gensymed_symbol,Qeval);
	new_value = eval_cons_1(gensymed_symbol,Nil);
	old_value = Nil;
      next_loop_5:
	old_value = Links_and_objects;
	M_CDR(new_value) = old_value;
	if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value))
	    goto end_loop_5;
	goto next_loop_5;
      end_loop_5:
	goto end_3;
      end_3:;
    }
    goto next_loop_4;
  end_loop_4:
    return VALUES_1(Qnil);
}

/* COLLECT-FORWARD-CHAINING-FOR-SYMBOLIC-CLASS-REFERENCES */
Object collect_forward_chaining_for_symbolic_class_references(object,
	    new_value,possible_values_qm,chaining_as_well_as_events_qm,
	    parent_of_variable_qm)
    Object object, new_value, possible_values_qm;
    Object chaining_as_well_as_events_qm, parent_of_variable_qm;
{
    Object link_1, class_description, classes, gensymed_symbol, list_1;
    Object cache_qm, ab_loop_list_, class_1, specific_list, new_value_1;
    Object old_value, symbolic_value, sense, designation, temp, temp_2, role;
    Object continuation, expiration_qm, gensymed_symbol_1, gensymed_symbol_2;
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    char temp_1;
    Object result;

    x_note_fn_call(153,46);
    link_1 = Nil;
    class_description = ISVREF(object,(SI_Long)1L);
    classes = ISVREF(class_description,(SI_Long)2L);
    gensymed_symbol = M_CAR(classes);
    list_1 = INLINE_SYMBOL_PLIST(gensymed_symbol);
  next_loop:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop;
  end_loop:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_1:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Cached_class_forward_chaining_list_kbprop))
	goto end_loop_1;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_1;
  end_loop_1:
    cache_qm = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    if (cache_qm)
	ab_loop_list_ = M_CDR(cache_qm);
    else {
	class_1 = Nil;
	ab_loop_list_ = classes;
	specific_list = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	class_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	specific_list = lookup_kb_specific_property_value(class_1,
		Forward_chaining_list_kbprop);
	if (specific_list) {
	    specific_list = copy_list_using_eval_conses_1(specific_list);
	    if (cache_qm)
		cache_qm = nconc2(cache_qm,specific_list);
	    else
		cache_qm = specific_list;
	}
	if (EQ(class_1,Qitem))
	    goto end_loop_2;
	goto next_loop_2;
      end_loop_2:
	mutate_kb_specific_property_value(M_CAR(classes),eval_cons_1(Nil,
		cache_qm),Cached_class_forward_chaining_list_kbprop);
	new_value_1 = eval_cons_1(M_CAR(classes),Nil);
	old_value = Nil;
      next_loop_3:
	old_value = Cached_classes_for_forward_chaining;
	M_CDR(new_value_1) = old_value;
	if (CAS_SYMBOL(Qcached_classes_for_forward_chaining,old_value,
		new_value_1))
	    goto end_loop_3;
	goto next_loop_3;
      end_loop_3:
	goto end_1;
      end_1:;
	ab_loop_list_ = cache_qm;
	goto end_2;
	ab_loop_list_ = Qnil;
      end_2:;
    }
    symbolic_value = Nil;
    sense = Nil;
    designation = Nil;
  next_loop_4:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_4;
    link_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    symbolic_value = ISVREF(link_1,(SI_Long)6L);
    sense = ISVREF(link_1,(SI_Long)7L);
    designation = ISVREF(link_1,(SI_Long)3L);
    if ((parent_of_variable_qm ? chaining_as_well_as_events_qm && 
	    (EQ(sense,T) && EQ(new_value,symbolic_value) ||  !TRUEP(sense) 
	    &&  !EQ(new_value,symbolic_value)) && memq_function(new_value,
	    possible_values_qm) : EQ(sense,Qreceives_a_value) || EQ(sense,
	    Qloses_its_value) || chaining_as_well_as_events_qm && 
	    (EQ(sense,T) && EQ(new_value,symbolic_value) || (EQ(sense,
	    Qeither) ||  !TRUEP(sense) &&  !EQ(new_value,symbolic_value)) 
	    && ( !TRUEP(possible_values_qm) || memq_function(new_value,
	    possible_values_qm)))) &&  !SYMBOLP(designation)) {
	if (domain_of_designation(designation)) {
	    temp = role_of_designation(designation);
	    temp_1 = SYMBOLP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_1 =  !temp_1;
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	temp_1 =  !TRUEP(domain_of_designation(designation));
	if (temp_1);
	else {
	    temp_2 = FIRST(designation);
	    temp = role_of_designation(designation);
	    result = serve_first_value_of_role_inverse(object,temp_2,temp,
		    domain_of_designation(designation));
	    MVS_3(result,role,continuation,expiration_qm);
	    if (expiration_qm) {
		if ( !(FIXNUMP(role) || SYMBOLP(role) || 
			SIMPLE_VECTOR_P(role)))
		    reclaim_if_evaluation_value_1(role);
	    }
	    if (continuation) {
		gensymed_symbol = M_CAR(continuation);
		gensymed_symbol_1 = Nil;
		gensymed_symbol_2 = continuation;
		inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
			gensymed_symbol_2);
	    }
	    temp_1 = TRUEP(expiration_qm);
	}
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
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
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_eval_cons_pool();
	M_CAR(gensymed_symbol) = link_1;
	M_CDR(gensymed_symbol) = object;
	inline_note_allocate_cons(gensymed_symbol,Qeval);
	new_value_1 = eval_cons_1(gensymed_symbol,Nil);
	old_value = Nil;
      next_loop_5:
	old_value = Links_and_objects;
	M_CDR(new_value_1) = old_value;
	if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value_1))
	    goto end_loop_5;
	goto next_loop_5;
      end_loop_5:
	goto end_3;
      end_3:;
    }
    goto next_loop_4;
  end_loop_4:
    return VALUES_1(Qnil);
}

/* COLLECT-FORWARD-CHAINING-FOR-GENERAL-CLASS-REFERENCES */
Object collect_forward_chaining_for_general_class_references(object,
	    chaining_as_well_as_events_qm)
    Object object, chaining_as_well_as_events_qm;
{
    Object link_1, class_description, classes, gensymed_symbol, list_1;
    Object cache_qm, ab_loop_list_, class_1, specific_list, new_value;
    Object old_value, link_sense, designation, temp, temp_2, role;
    Object continuation, expiration_qm, gensymed_symbol_1, gensymed_symbol_2;
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    char temp_1;
    Object result;

    x_note_fn_call(153,47);
    link_1 = Nil;
    class_description = ISVREF(object,(SI_Long)1L);
    classes = ISVREF(class_description,(SI_Long)2L);
    gensymed_symbol = M_CAR(classes);
    list_1 = INLINE_SYMBOL_PLIST(gensymed_symbol);
  next_loop:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop;
  end_loop:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_1:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Cached_class_forward_chaining_list_kbprop))
	goto end_loop_1;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_1;
  end_loop_1:
    cache_qm = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    if (cache_qm)
	ab_loop_list_ = M_CDR(cache_qm);
    else {
	class_1 = Nil;
	ab_loop_list_ = classes;
	specific_list = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	class_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	specific_list = lookup_kb_specific_property_value(class_1,
		Forward_chaining_list_kbprop);
	if (specific_list) {
	    specific_list = copy_list_using_eval_conses_1(specific_list);
	    if (cache_qm)
		cache_qm = nconc2(cache_qm,specific_list);
	    else
		cache_qm = specific_list;
	}
	if (EQ(class_1,Qitem))
	    goto end_loop_2;
	goto next_loop_2;
      end_loop_2:
	mutate_kb_specific_property_value(M_CAR(classes),eval_cons_1(Nil,
		cache_qm),Cached_class_forward_chaining_list_kbprop);
	new_value = eval_cons_1(M_CAR(classes),Nil);
	old_value = Nil;
      next_loop_3:
	old_value = Cached_classes_for_forward_chaining;
	M_CDR(new_value) = old_value;
	if (CAS_SYMBOL(Qcached_classes_for_forward_chaining,old_value,
		new_value))
	    goto end_loop_3;
	goto next_loop_3;
      end_loop_3:
	goto end_1;
      end_1:;
	ab_loop_list_ = cache_qm;
	goto end_2;
	ab_loop_list_ = Qnil;
      end_2:;
    }
    link_sense = Nil;
    designation = Nil;
  next_loop_4:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_4;
    link_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    link_sense = ISVREF(link_1,(SI_Long)7L);
    designation = ISVREF(link_1,(SI_Long)3L);
    if ((chaining_as_well_as_events_qm && (EQ(link_sense,Qeither) || 
	    EQ(link_sense,T) ||  !TRUEP(link_sense)) || EQ(link_sense,
	    Qreceives_a_value) || EQ(link_sense,Qloses_its_value)) &&  
	    !SYMBOLP(designation)) {
	if (domain_of_designation(designation)) {
	    temp = role_of_designation(designation);
	    temp_1 = SYMBOLP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_1 =  !temp_1;
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	temp_1 =  !TRUEP(domain_of_designation(designation));
	if (temp_1);
	else {
	    temp_2 = FIRST(designation);
	    temp = role_of_designation(designation);
	    result = serve_first_value_of_role_inverse(object,temp_2,temp,
		    domain_of_designation(designation));
	    MVS_3(result,role,continuation,expiration_qm);
	    if (expiration_qm) {
		if ( !(FIXNUMP(role) || SYMBOLP(role) || 
			SIMPLE_VECTOR_P(role)))
		    reclaim_if_evaluation_value_1(role);
	    }
	    if (continuation) {
		gensymed_symbol = M_CAR(continuation);
		gensymed_symbol_1 = Nil;
		gensymed_symbol_2 = continuation;
		inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
			gensymed_symbol_2);
	    }
	    temp_1 = TRUEP(expiration_qm);
	}
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
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
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_eval_cons_pool();
	M_CAR(gensymed_symbol) = link_1;
	M_CDR(gensymed_symbol) = object;
	inline_note_allocate_cons(gensymed_symbol,Qeval);
	new_value = eval_cons_1(gensymed_symbol,Nil);
	old_value = Nil;
      next_loop_5:
	old_value = Links_and_objects;
	M_CDR(new_value) = old_value;
	if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value))
	    goto end_loop_5;
	goto next_loop_5;
      end_loop_5:
	goto end_3;
      end_3:;
    }
    goto next_loop_4;
  end_loop_4:
    return VALUES_1(Qnil);
}

static Object string_constant;     /* "Notifying ~NF that a new value has been placed in ~NF." */

static Object Qforward_chaining;   /* forward-chaining */

/* INVOKE-RULES-FOR-FORWARD-CHAINING */
Object invoke_rules_for_forward_chaining(variable,new_managed_value,
	    data_type,chaining_as_well_as_events_qm,old_managed_value)
    Object variable, new_managed_value, data_type;
    Object chaining_as_well_as_events_qm, old_managed_value;
{
    Object needs_true_value_expiration_task_qm, old_extracted_value_qm;
    Object links_and_objects, trailer, link_entry_cons, link_entry, link_1;
    Object recipient, sub_class_bit_vector, temp_1, role_qm, local_name_qm;
    Object object_qm, temp_2, temp_3, eval_cons, svref_new_value, expiration;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(153,48);
    needs_true_value_expiration_task_qm = Nil;
    old_extracted_value_qm = Nil;
    links_and_objects = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Links_and_objects,Qlinks_and_objects,links_and_objects,
	    0);
      collect_rules_for_forward_chaining(variable,new_managed_value,
	      data_type,chaining_as_well_as_events_qm);
      if (Links_and_objects) {
	  trailer = Nil;
	  link_entry_cons = Links_and_objects;
	  link_entry = Nil;
	  link_1 = Nil;
	  recipient = Nil;
	next_loop:
	  if ( !TRUEP(link_entry_cons))
	      goto end_loop;
	  link_entry = M_CAR(link_entry_cons);
	  link_1 = M_CAR(link_entry);
	  recipient = ISVREF(link_1,(SI_Long)2L);
	  sub_class_bit_vector = ISVREF(ISVREF(recipient,(SI_Long)1L),
		  (SI_Long)19L);
	  superior_class_bit_number = 
		  IFIX(ISVREF(True_value_update_recipient_class_description,
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
	      if (designation_denotes_item_p(ISVREF(link_1,(SI_Long)3L),
		      variable)) {
		  if (ISVREF(recipient,(SI_Long)3L)) {
		      if ((IFIX(Tracing_message_level) > (SI_Long)1L || 
			      IFIX(Breakpoint_level) > (SI_Long)1L) &&  
			      !TRUEP(Debugging_reset) && 
			      ISVREF(Debugging_parameters,(SI_Long)22L))
			  tformat_major_trace_message_1(string_constant,
				  ISVREF(recipient,(SI_Long)3L),variable,
				  Nil,Nil,Nil,Nil,Nil,Nil,Nil);
		  }
		  sub_class_bit_vector = ISVREF(ISVREF(variable,
			  (SI_Long)1L),(SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Variable_class_description,
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
		      gensymed_symbol_1 = gensymed_symbol_1 << 
			      gensymed_symbol_2;
		      gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		      needs_true_value_expiration_task_qm = (SI_Long)0L < 
			      gensymed_symbol ? T : Nil;
		  }
		  else
		      needs_true_value_expiration_task_qm = Nil;
		  if ( !TRUEP(old_extracted_value_qm)) {
		      if (INLINE_DOUBLE_FLOAT_VECTOR_P(old_managed_value) 
			      != (SI_Long)0L && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_managed_value)) 
			      == (SI_Long)1L)
			  old_extracted_value_qm = 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(old_managed_value,
				  (SI_Long)0L));
		      else if (INLINE_LONG_VECTOR_P(old_managed_value) != 
			      (SI_Long)0L && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_managed_value)) 
			      == (SI_Long)1L)
			  old_extracted_value_qm = aref1(old_managed_value,
				  FIX((SI_Long)0L));
		      else
			  old_extracted_value_qm = old_managed_value;
		  }
		  funcall(7,SYMBOL_FUNCTION(ISVREF(recipient,(SI_Long)2L)),
			  ISVREF(recipient,(SI_Long)3L),ISVREF(recipient,
			  (SI_Long)4L),variable,Nil,old_extracted_value_qm,
			  Nil);
	      }
	  }
	  else if (EQ(ISVREF(link_1,(SI_Long)7L),Qloses_its_value)) {
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
	      if (temp)
		  needs_true_value_expiration_task_qm = T;
	  }
	  else {
	      temp_1 = ISVREF(recipient,(SI_Long)8L);
	      if ( !TRUEP(CAR(temp_1)) && ((SI_Long)0L != 
		      (IFIX(ISVREF(recipient,(SI_Long)5L)) & (SI_Long)1L) 
		      ||  !TRUEP(Inside_breakpoint_p) && (SI_Long)0L != 
		      (IFIX(ISVREF(recipient,(SI_Long)4L)) & 
		      (SI_Long)16777216L) &&  !((SI_Long)0L != 
		      (IFIX(ISVREF(recipient,(SI_Long)4L)) & 
			  (SI_Long)8192L)))) {
		  role_qm = ISVREF(link_1,(SI_Long)4L);
		  local_name_qm = role_qm ? ISVREF(link_1,(SI_Long)5L) : Nil;
		  object_qm = role_qm ? M_CDR(link_entry) : Nil;
		  if ((IFIX(Tracing_message_level) > (SI_Long)1L || 
			  IFIX(Breakpoint_level) > (SI_Long)1L) &&  
			  !TRUEP(Debugging_reset) && 
			  ISVREF(Debugging_parameters,(SI_Long)22L))
		      write_trace_message_for_forward_chaining(recipient,
			      variable,role_qm,local_name_qm,object_qm);
		  generate_and_schedule_rule_instances(recipient,role_qm,
			  local_name_qm,object_qm,Qforward_chaining,Nil,
			  ISVREF(recipient,(SI_Long)26L),Nil);
	      }
	  }
	  inline_note_reclaim_cons(link_entry,Qeval);
	  if (ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	      temp_2 = ISVREF(Available_eval_conses_tail_vector,
		      IFIX(Current_thread_index));
	      M_CDR(temp_2) = link_entry;
	      temp_2 = Available_eval_conses_tail_vector;
	      temp_3 = Current_thread_index;
	      SVREF(temp_2,temp_3) = link_entry;
	  }
	  else {
	      temp_2 = Available_eval_conses_vector;
	      temp_3 = Current_thread_index;
	      SVREF(temp_2,temp_3) = link_entry;
	      temp_2 = Available_eval_conses_tail_vector;
	      temp_3 = Current_thread_index;
	      SVREF(temp_2,temp_3) = link_entry;
	  }
	  M_CDR(link_entry) = Nil;
	  trailer = link_entry_cons;
	  link_entry_cons = M_CDR(link_entry_cons);
	  goto next_loop;
	end_loop:
	  if (Links_and_objects) {
	      if (Links_and_objects &&  !((SI_Long)0L == 
		      inline_debugging_consing())) {
		  eval_cons = Links_and_objects;
		next_loop_1:
		  inline_note_reclaim_cons(eval_cons,Qeval);
		  if (EQ(eval_cons,trailer))
		      goto end_1;
		  else if ( !TRUEP(eval_cons))
		      goto end_1;
		  else
		      eval_cons = CDR(eval_cons);
		  goto next_loop_1;
		end_loop_1:
		end_1:;
	      }
	      if (ISVREF(Available_eval_conses_tail_vector,
		      IFIX(Current_thread_index))) {
		  temp_2 = ISVREF(Available_eval_conses_tail_vector,
			  IFIX(Current_thread_index));
		  temp_3 = Links_and_objects;
		  M_CDR(temp_2) = temp_3;
		  temp_2 = Available_eval_conses_tail_vector;
		  temp_3 = Current_thread_index;
		  SVREF(temp_2,temp_3) = trailer;
	      }
	      else {
		  temp_2 = Available_eval_conses_vector;
		  temp_3 = Current_thread_index;
		  svref_new_value = Links_and_objects;
		  SVREF(temp_2,temp_3) = svref_new_value;
		  temp_2 = Available_eval_conses_tail_vector;
		  temp_3 = Current_thread_index;
		  SVREF(temp_2,temp_3) = trailer;
	      }
	      M_CDR(trailer) = Nil;
	      Links_and_objects = Nil;
	  }
      }
      if (needs_true_value_expiration_task_qm) {
	  expiration = ISVREF(variable,(SI_Long)26L);
	  if (FIXNUMP(expiration) && FIXNUM_GE(expiration,Gensym_time))
	      result = schedule_update_for_variable_expiration(variable);
	  else
	      result = VALUES_1(Nil);
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_1;   /* "Scheduling forward chaining to ~NF with ~NF as the ~A ~?
				    *                with local name ~A because a new value was placed in ~NF by ~NF."
				    */

static Object string_constant_2;   /* "Scheduling forward chaining to ~NF with ~NF as the ~A ~?
				    *                because a new value was placed in ~NF by ~NF."
				    */

static Object string_constant_3;   /* "Scheduling forward chaining to ~NF because a new value was ~?
				    *          placed in ~NF by ~NF."
				    */

/* WRITE-TRACE-MESSAGE-FOR-FORWARD-CHAINING */
Object write_trace_message_for_forward_chaining(rule,variable,role_qm,
	    local_name_qm,object_qm)
    Object rule, variable, role_qm, local_name_qm, object_qm;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object gensymed_symbol;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(153,49);
    if ((IFIX(Tracing_message_level) > (SI_Long)1L || 
	    IFIX(Breakpoint_level) > (SI_Long)1L) &&  
	    !TRUEP(Debugging_reset) && ISVREF(Debugging_parameters,
	    (SI_Long)22L)) {
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
		  if (role_qm) {
		      if (local_name_qm)
			  tformat(7,string_constant_1,rule,object_qm,
				  role_qm,local_name_qm,variable,
				  Current_computation_frame);
		      else
			  tformat(6,string_constant_2,rule,object_qm,
				  role_qm,variable,Current_computation_frame);
		  }
		  else
		      tformat(4,string_constant_3,rule,variable,
			      Current_computation_frame);
		  gensymed_symbol = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return write_major_trace_message_function(gensymed_symbol);
    }
    else
	return VALUES_1(Nil);
}

/* COLLECT-RULES-FOR-LOGICAL-FORWARD-CHAINING */
Object collect_rules_for_logical_forward_chaining(variable,new_value,
	    chaining_as_well_as_events_qm,parent_stack,variable_names_qm)
    Object variable, new_value, chaining_as_well_as_events_qm, parent_stack;
    Object variable_names_qm;
{
    Object name_for_variable, ab_loop_list_, link_1, list_1, ab_loop_list__1;
    Object link_sense, new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_value_1, old_value, parent_frame_qm;
    char new_value_sense;

    x_note_fn_call(153,50);
    new_value_sense = IFIX(new_value) > (SI_Long)0L;
    name_for_variable = Nil;
    ab_loop_list_ = variable_names_qm;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    name_for_variable = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    link_1 = Nil;
    list_1 = INLINE_SYMBOL_PLIST(name_for_variable);
  next_loop_1:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop_1;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_1;
  end_loop_1:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_2:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Forward_chaining_list_kbprop))
	goto end_loop_2;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_2;
  end_loop_2:
    ab_loop_list__1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    link_sense = Nil;
  next_loop_3:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_3;
    link_1 = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    link_sense = ISVREF(link_1,(SI_Long)7L);
    if (EQ(name_for_variable,ISVREF(link_1,(SI_Long)3L)) && 
	    (chaining_as_well_as_events_qm && (EQ(link_sense,Qeither) || 
	    EQ(new_value_sense ? T : Nil,link_sense)) || EQ(link_sense,
	    Qreceives_a_value) || EQ(link_sense,Qloses_its_value))) {
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
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_eval_cons_pool();
	M_CAR(gensymed_symbol) = link_1;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qeval);
	new_value_1 = eval_cons_1(gensymed_symbol,Nil);
	old_value = Nil;
      next_loop_4:
	old_value = Links_and_objects;
	M_CDR(new_value_1) = old_value;
	if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value_1))
	    goto end_loop_4;
	goto next_loop_4;
      end_loop_4:
	goto end_1;
      end_1:;
    }
    goto next_loop_3;
  end_loop_3:;
    goto next_loop;
  end_loop:;
    if (parent_stack) {
	link_1 = Nil;
	gensymed_symbol = M_CAR(M_CDR(M_CAR(parent_stack)));
	gensymed_symbol = CONSP(gensymed_symbol) ? M_CAR(gensymed_symbol) :
		 gensymed_symbol;
	list_1 = INLINE_SYMBOL_PLIST(gensymed_symbol);
      next_loop_5:
	if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
		Current_kb_specific_property_list_property_name))
	    goto end_loop_5;
	list_1 = M_CDR(M_CDR(list_1));
	goto next_loop_5;
      end_loop_5:
	list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
      next_loop_6:
	if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Forward_chaining_list_kbprop))
	    goto end_loop_6;
	list_1 = M_CDR(M_CDR(list_1));
	goto next_loop_6;
      end_loop_6:
	ab_loop_list_ = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
	link_sense = Nil;
      next_loop_7:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_7;
	link_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	link_sense = ISVREF(link_1,(SI_Long)7L);
	if (chaining_as_well_as_events_qm && (EQ(link_sense,Qeither) || 
		EQ(new_value_sense ? T : Nil,link_sense)) || EQ(link_sense,
		Qreceives_a_value) || EQ(link_sense,Qloses_its_value)) {
	    parent_frame_qm = find_referenced_parent(parent_stack,
		    ISVREF(link_1,(SI_Long)3L));
	    if (parent_frame_qm) {
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
		    gensymed_symbol = new_cons;
		}
		else
		    gensymed_symbol = Nil;
		if ( !TRUEP(gensymed_symbol))
		    gensymed_symbol = replenish_eval_cons_pool();
		M_CAR(gensymed_symbol) = link_1;
		M_CDR(gensymed_symbol) = parent_frame_qm;
		inline_note_allocate_cons(gensymed_symbol,Qeval);
		new_value_1 = eval_cons_1(gensymed_symbol,Nil);
		old_value = Nil;
	      next_loop_8:
		old_value = Links_and_objects;
		M_CDR(new_value_1) = old_value;
		if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value_1))
		    goto end_loop_8;
		goto next_loop_8;
	      end_loop_8:
		goto end_2;
	      end_2:;
	    }
	}
	goto next_loop_7;
      end_loop_7:;
    }
    return collect_forward_chaining_for_logical_class_references(variable,
	    new_value_sense ? T : Nil,chaining_as_well_as_events_qm);
}

/* COLLECT-RULES-FOR-SYMBOLIC-FORWARD-CHAINING */
Object collect_rules_for_symbolic_forward_chaining(variable,new_value,
	    chaining_as_well_as_events_qm,parent_stack,
	    variable_name_or_names_qm)
    Object variable, new_value, chaining_as_well_as_events_qm, parent_stack;
    Object variable_name_or_names_qm;
{
    Object possible_values_qm, parent_stack_entry, gensymed_symbol, temp;
    Object name_for_parent_qm, ab_loop_list_, link_1, list_1, ab_loop_list__1;
    Object symbolic_value, sense, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, new_value_1, old_value, link_symbolic_value;
    Object link_sense, parent_frame_qm, name_for_variable;
    char temp_1;

    x_note_fn_call(153,51);
    possible_values_qm = Nil;
    parent_stack_entry = CAR(parent_stack);
    if (parent_stack_entry) {
	gensymed_symbol = M_CAR(M_CDR(parent_stack_entry));
	temp = CONSP(gensymed_symbol) ? M_CAR(gensymed_symbol) : 
		gensymed_symbol;
	gensymed_symbol = M_CAR(M_CDR(parent_stack_entry));
	possible_values_qm = value_set_given_attribute_and_class(temp,
		CONSP(gensymed_symbol) ? M_CDR(gensymed_symbol) : 
		ISVREF(ISVREF(M_CAR(parent_stack_entry),(SI_Long)1L),
		(SI_Long)1L));
	if (possible_values_qm) {
	    gensymed_symbol = possible_values_qm;
	  next_loop:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop;
	    if (EQ(M_CAR(gensymed_symbol),new_value)) {
		temp_1 = TRUEP(gensymed_symbol);
		goto end_1;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop;
	  end_loop:
	    temp_1 = TRUEP(Qnil);
	  end_1:;
	    temp_1 =  !temp_1;
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    warn_of_inappropriate_value(new_value,variable,possible_values_qm);
	if (possible_values_qm) {
	    name_for_parent_qm = Nil;
	    ab_loop_list_ = M_CAR(M_CDR(M_CDR(parent_stack_entry)));
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    name_for_parent_qm = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    link_1 = Nil;
	    list_1 = INLINE_SYMBOL_PLIST(name_for_parent_qm);
	  next_loop_2:
	    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
		    Current_kb_specific_property_list_property_name))
		goto end_loop_2;
	    list_1 = M_CDR(M_CDR(list_1));
	    goto next_loop_2;
	  end_loop_2:
	    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
	  next_loop_3:
	    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
		    Forward_chaining_list_kbprop))
		goto end_loop_3;
	    list_1 = M_CDR(M_CDR(list_1));
	    goto next_loop_3;
	  end_loop_3:
	    ab_loop_list__1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
	    symbolic_value = Nil;
	    sense = Nil;
	  next_loop_4:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_4;
	    link_1 = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    symbolic_value = ISVREF(link_1,(SI_Long)6L);
	    sense = ISVREF(link_1,(SI_Long)7L);
	    if (T ? chaining_as_well_as_events_qm && (EQ(sense,T) && 
		    EQ(new_value,symbolic_value) ||  !TRUEP(sense) &&  
		    !EQ(new_value,symbolic_value)) && 
		    memq_function(new_value,possible_values_qm) : EQ(sense,
		    Qreceives_a_value) || EQ(sense,Qloses_its_value) || 
		    chaining_as_well_as_events_qm && (EQ(sense,T) && 
		    EQ(new_value,symbolic_value) || (EQ(sense,Qeither) ||  
		    !TRUEP(sense) &&  !EQ(new_value,symbolic_value)) && ( 
		    !TRUEP(possible_values_qm) || memq_function(new_value,
		    possible_values_qm)))) {
		temp = ISVREF(link_1,(SI_Long)3L);
		temp_1 = SYMBOLP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
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
		    gensymed_symbol = new_cons;
		}
		else
		    gensymed_symbol = Nil;
		if ( !TRUEP(gensymed_symbol))
		    gensymed_symbol = replenish_eval_cons_pool();
		M_CAR(gensymed_symbol) = link_1;
		M_CDR(gensymed_symbol) = Nil;
		inline_note_allocate_cons(gensymed_symbol,Qeval);
		new_value_1 = eval_cons_1(gensymed_symbol,Nil);
		old_value = Nil;
	      next_loop_5:
		old_value = Links_and_objects;
		M_CDR(new_value_1) = old_value;
		if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value_1))
		    goto end_loop_5;
		goto next_loop_5;
	      end_loop_5:
		goto end_2;
	      end_2:;
	    }
	    goto next_loop_4;
	  end_loop_4:;
	    goto next_loop_1;
	  end_loop_1:;
	}
	link_1 = Nil;
	gensymed_symbol = M_CAR(M_CDR(parent_stack_entry));
	gensymed_symbol = CONSP(gensymed_symbol) ? M_CAR(gensymed_symbol) :
		 gensymed_symbol;
	list_1 = INLINE_SYMBOL_PLIST(gensymed_symbol);
      next_loop_6:
	if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
		Current_kb_specific_property_list_property_name))
	    goto end_loop_6;
	list_1 = M_CDR(M_CDR(list_1));
	goto next_loop_6;
      end_loop_6:
	list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
      next_loop_7:
	if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Forward_chaining_list_kbprop))
	    goto end_loop_7;
	list_1 = M_CDR(M_CDR(list_1));
	goto next_loop_7;
      end_loop_7:
	ab_loop_list_ = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
	link_symbolic_value = Nil;
	link_sense = Nil;
      next_loop_8:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_8;
	link_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	link_symbolic_value = ISVREF(link_1,(SI_Long)6L);
	link_sense = ISVREF(link_1,(SI_Long)7L);
	if (Nil ? chaining_as_well_as_events_qm && (EQ(link_sense,T) && 
		EQ(new_value,link_symbolic_value) ||  !TRUEP(link_sense) 
		&&  !EQ(new_value,link_symbolic_value)) && 
		memq_function(new_value,possible_values_qm) : 
		EQ(link_sense,Qreceives_a_value) || EQ(link_sense,
		Qloses_its_value) || chaining_as_well_as_events_qm && 
		(EQ(link_sense,T) && EQ(new_value,link_symbolic_value) || 
		(EQ(link_sense,Qeither) ||  !TRUEP(link_sense) &&  
		!EQ(new_value,link_symbolic_value)) && ( 
		!TRUEP(possible_values_qm) || memq_function(new_value,
		possible_values_qm)))) {
	    parent_frame_qm = find_referenced_parent(parent_stack,
		    ISVREF(link_1,(SI_Long)3L));
	    if (parent_frame_qm) {
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
		    gensymed_symbol = new_cons;
		}
		else
		    gensymed_symbol = Nil;
		if ( !TRUEP(gensymed_symbol))
		    gensymed_symbol = replenish_eval_cons_pool();
		M_CAR(gensymed_symbol) = link_1;
		M_CDR(gensymed_symbol) = parent_frame_qm;
		inline_note_allocate_cons(gensymed_symbol,Qeval);
		new_value_1 = eval_cons_1(gensymed_symbol,Nil);
		old_value = Nil;
	      next_loop_9:
		old_value = Links_and_objects;
		M_CDR(new_value_1) = old_value;
		if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value_1))
		    goto end_loop_9;
		goto next_loop_9;
	      end_loop_9:
		goto end_3;
	      end_3:;
	    }
	}
	goto next_loop_8;
      end_loop_8:;
	if (possible_values_qm) {
	    collect_forward_chaining_for_symbolic_class_references(M_CAR(parent_stack_entry),
		    new_value,possible_values_qm,
		    chaining_as_well_as_events_qm,T);
	    if (CDR(parent_stack)) {
		parent_stack_entry = SECOND(parent_stack);
		link_1 = Nil;
		gensymed_symbol = M_CAR(M_CDR(parent_stack_entry));
		gensymed_symbol = CONSP(gensymed_symbol) ? 
			M_CAR(gensymed_symbol) : gensymed_symbol;
		list_1 = INLINE_SYMBOL_PLIST(gensymed_symbol);
	      next_loop_10:
		if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
			Current_kb_specific_property_list_property_name))
		    goto end_loop_10;
		list_1 = M_CDR(M_CDR(list_1));
		goto next_loop_10;
	      end_loop_10:
		list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
	      next_loop_11:
		if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
			Forward_chaining_list_kbprop))
		    goto end_loop_11;
		list_1 = M_CDR(M_CDR(list_1));
		goto next_loop_11;
	      end_loop_11:
		ab_loop_list_ = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
		link_symbolic_value = Nil;
		link_sense = Nil;
	      next_loop_12:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_12;
		link_1 = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		link_symbolic_value = ISVREF(link_1,(SI_Long)6L);
		link_sense = ISVREF(link_1,(SI_Long)7L);
		if (T ? chaining_as_well_as_events_qm && (EQ(link_sense,T) 
			&& EQ(new_value,link_symbolic_value) ||  
			!TRUEP(link_sense) &&  !EQ(new_value,
			link_symbolic_value)) && memq_function(new_value,
			possible_values_qm) : EQ(link_sense,
			Qreceives_a_value) || EQ(link_sense,
			Qloses_its_value) || chaining_as_well_as_events_qm 
			&& (EQ(link_sense,T) && EQ(new_value,
			link_symbolic_value) || (EQ(link_sense,Qeither) || 
			 !TRUEP(link_sense) &&  !EQ(new_value,
			link_symbolic_value)) && ( 
			!TRUEP(possible_values_qm) || 
			memq_function(new_value,possible_values_qm)))) {
		    parent_frame_qm = 
			    find_referenced_parent(CDR(parent_stack),
			    ISVREF(link_1,(SI_Long)3L));
		    if (parent_frame_qm) {
			new_cons = ISVREF(Available_eval_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    svref_arg_1 = Available_eval_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_eval_conses_vector,
				    IFIX(Current_thread_index)))) {
				svref_arg_1 = 
					Available_eval_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(svref_arg_1,svref_arg_2) = Nil;
			    }
			    gensymed_symbol = new_cons;
			}
			else
			    gensymed_symbol = Nil;
			if ( !TRUEP(gensymed_symbol))
			    gensymed_symbol = replenish_eval_cons_pool();
			M_CAR(gensymed_symbol) = link_1;
			M_CDR(gensymed_symbol) = parent_frame_qm;
			inline_note_allocate_cons(gensymed_symbol,Qeval);
			new_value_1 = eval_cons_1(gensymed_symbol,Nil);
			old_value = Nil;
		      next_loop_13:
			old_value = Links_and_objects;
			M_CDR(new_value_1) = old_value;
			if (CAS_SYMBOL(Qlinks_and_objects,old_value,
				new_value_1))
			    goto end_loop_13;
			goto next_loop_13;
		      end_loop_13:
			goto end_4;
		      end_4:;
		    }
		}
		goto next_loop_12;
	      end_loop_12:;
	    }
	}
    }
    name_for_variable = Nil;
    ab_loop_list_ = variable_name_or_names_qm;
  next_loop_14:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_14;
    name_for_variable = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    link_1 = Nil;
    list_1 = INLINE_SYMBOL_PLIST(name_for_variable);
  next_loop_15:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop_15;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_15;
  end_loop_15:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_16:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Forward_chaining_list_kbprop))
	goto end_loop_16;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_16;
  end_loop_16:
    ab_loop_list__1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    symbolic_value = Nil;
    sense = Nil;
  next_loop_17:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_17;
    link_1 = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    symbolic_value = ISVREF(link_1,(SI_Long)6L);
    sense = ISVREF(link_1,(SI_Long)7L);
    if (Nil ? chaining_as_well_as_events_qm && (EQ(sense,T) && 
	    EQ(new_value,symbolic_value) ||  !TRUEP(sense) &&  
	    !EQ(new_value,symbolic_value)) && memq_function(new_value,
	    possible_values_qm) : EQ(sense,Qreceives_a_value) || EQ(sense,
	    Qloses_its_value) || chaining_as_well_as_events_qm && 
	    (EQ(sense,T) && EQ(new_value,symbolic_value) || (EQ(sense,
	    Qeither) ||  !TRUEP(sense) &&  !EQ(new_value,symbolic_value)) 
	    && ( !TRUEP(possible_values_qm) || memq_function(new_value,
	    possible_values_qm)))) {
	temp = ISVREF(link_1,(SI_Long)3L);
	temp_1 = SYMBOLP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
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
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_eval_cons_pool();
	M_CAR(gensymed_symbol) = link_1;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qeval);
	new_value_1 = eval_cons_1(gensymed_symbol,Nil);
	old_value = Nil;
      next_loop_18:
	old_value = Links_and_objects;
	M_CDR(new_value_1) = old_value;
	if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value_1))
	    goto end_loop_18;
	goto next_loop_18;
      end_loop_18:
	goto end_5;
      end_5:;
    }
    goto next_loop_17;
  end_loop_17:;
    goto next_loop_14;
  end_loop_14:;
    return collect_forward_chaining_for_symbolic_class_references(variable,
	    new_value,possible_values_qm,chaining_as_well_as_events_qm,Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Initializing_items_needing_initialization, Qinitializing_items_needing_initialization);

static Object Qrecord_block_for_tformat;  /* record-block-for-tformat */

static Object string_constant_4;   /* "The value ~(~a~) is being stored into the symbolic variable ~NF but ~?
				    *        this value is not a member of the set of possible values for its ~?
				    *        attribute and class.  The set of possible values contains the ~?
				    *        element~a "
				    */

static Object string_constant_5;   /* "s" */

static Object string_constant_6;   /* "" */

static Object string_constant_7;   /* "and" */

/* WARN-OF-INAPPROPRIATE-VALUE */
Object warn_of_inappropriate_value(new_value,variable,possible_values)
    Object new_value, variable, possible_values;
{
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(7);

    x_note_fn_call(153,52);
    if ( !(Initializing_clear_text_p && 
	    Initializing_items_needing_initialization)) {
	if ((SI_Long)1L <= IFIX(Warning_message_level) &&  
		!TRUEP(Debugging_reset)) {
	    if ( !TRUEP(Defer_notifications_qm))
		break_out_of_debug_messages();
	    snapshots_of_related_blocks = Nil;
	    note_blocks_in_tformat = 
		    SYMBOL_FUNCTION(Qrecord_block_for_tformat);
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
			  tformat(4,string_constant_4,new_value,variable,
				  CDR(possible_values) ? string_constant_5 
				  : string_constant_6);
			  write_list_in_chicago_style(2,possible_values,
				  string_constant_7);
			  twrite_character(FIX((SI_Long)46L));
			  temp = copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		notify_user_1(temp);
		if (Snapshots_of_related_blocks) {
		    reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
		    Snapshots_of_related_blocks = Nil;
		}
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
    }
    return VALUES_1(Nil);
}

/* COLLECT-RULES-FOR-GENERAL-FORWARD-CHAINING */
Object collect_rules_for_general_forward_chaining(variable,
	    chaining_as_well_as_events_qm,parent_stack,
	    variable_name_or_names_qm)
    Object variable, chaining_as_well_as_events_qm, parent_stack;
    Object variable_name_or_names_qm;
{
    Object name_for_variable, ab_loop_list_, link_1, list_1, ab_loop_list__1;
    Object link_sense, temp, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol, new_value, old_value;
    Object parent_frame_qm;
    char temp_1;

    x_note_fn_call(153,53);
    name_for_variable = Nil;
    ab_loop_list_ = variable_name_or_names_qm;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    name_for_variable = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    link_1 = Nil;
    list_1 = INLINE_SYMBOL_PLIST(name_for_variable);
  next_loop_1:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop_1;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_1;
  end_loop_1:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_2:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Forward_chaining_list_kbprop))
	goto end_loop_2;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_2;
  end_loop_2:
    ab_loop_list__1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    link_sense = Nil;
  next_loop_3:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_3;
    link_1 = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    link_sense = ISVREF(link_1,(SI_Long)7L);
    if (chaining_as_well_as_events_qm && (EQ(link_sense,Qeither) || 
	    EQ(link_sense,T) ||  !TRUEP(link_sense)) || EQ(link_sense,
	    Qreceives_a_value) || EQ(link_sense,Qloses_its_value)) {
	temp = ISVREF(link_1,(SI_Long)3L);
	temp_1 = SYMBOLP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
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
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_eval_cons_pool();
	M_CAR(gensymed_symbol) = link_1;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qeval);
	new_value = eval_cons_1(gensymed_symbol,Nil);
	old_value = Nil;
      next_loop_4:
	old_value = Links_and_objects;
	M_CDR(new_value) = old_value;
	if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value))
	    goto end_loop_4;
	goto next_loop_4;
      end_loop_4:
	goto end_1;
      end_1:;
    }
    goto next_loop_3;
  end_loop_3:;
    goto next_loop;
  end_loop:;
    if (parent_stack) {
	link_1 = Nil;
	gensymed_symbol = M_CAR(M_CDR(M_CAR(parent_stack)));
	gensymed_symbol = CONSP(gensymed_symbol) ? M_CAR(gensymed_symbol) :
		 gensymed_symbol;
	list_1 = INLINE_SYMBOL_PLIST(gensymed_symbol);
      next_loop_5:
	if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
		Current_kb_specific_property_list_property_name))
	    goto end_loop_5;
	list_1 = M_CDR(M_CDR(list_1));
	goto next_loop_5;
      end_loop_5:
	list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
      next_loop_6:
	if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Forward_chaining_list_kbprop))
	    goto end_loop_6;
	list_1 = M_CDR(M_CDR(list_1));
	goto next_loop_6;
      end_loop_6:
	ab_loop_list_ = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
	link_sense = Nil;
      next_loop_7:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_7;
	link_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	link_sense = ISVREF(link_1,(SI_Long)7L);
	if (chaining_as_well_as_events_qm && (EQ(link_sense,Qeither) || 
		EQ(link_sense,T) ||  !TRUEP(link_sense)) || EQ(link_sense,
		Qreceives_a_value) || EQ(link_sense,Qloses_its_value)) {
	    parent_frame_qm = find_referenced_parent(parent_stack,
		    ISVREF(link_1,(SI_Long)3L));
	    if (parent_frame_qm) {
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
		    gensymed_symbol = new_cons;
		}
		else
		    gensymed_symbol = Nil;
		if ( !TRUEP(gensymed_symbol))
		    gensymed_symbol = replenish_eval_cons_pool();
		M_CAR(gensymed_symbol) = link_1;
		M_CDR(gensymed_symbol) = parent_frame_qm;
		inline_note_allocate_cons(gensymed_symbol,Qeval);
		new_value = eval_cons_1(gensymed_symbol,Nil);
		old_value = Nil;
	      next_loop_8:
		old_value = Links_and_objects;
		M_CDR(new_value) = old_value;
		if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value))
		    goto end_loop_8;
		goto next_loop_8;
	      end_loop_8:
		goto end_2;
	      end_2:;
	    }
	}
	goto next_loop_7;
      end_loop_7:;
    }
    return collect_forward_chaining_for_general_class_references(variable,
	    chaining_as_well_as_events_qm);
}

static Object Qtruth_value;        /* truth-value */

/* COLLECT-RULES-FOR-FORWARD-CHAINING */
Object collect_rules_for_forward_chaining(variable,new_value,data_type,
	    chaining_as_well_as_events_qm)
    Object variable, new_value, data_type, chaining_as_well_as_events_qm;
{
    Object variable_name_or_names_qm, variable_name_cons_qm, parent_stack;
    Object parent_entry_qm, event_detectors, event_detector, ab_loop_list_;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object triggerable_event_detectors, eval_pop_store, cons_1, next_cons;
    Object temp, svref_arg_2, temp_1;
    char temp_2;

    x_note_fn_call(153,54);
    variable_name_or_names_qm = 
	    get_lookup_slot_value_given_default(variable,
	    Qname_or_names_for_frame,Nil);
    if (variable_name_or_names_qm && SYMBOLP(variable_name_or_names_qm)) {
	variable_name_or_names_qm = eval_cons_1(variable_name_or_names_qm,Nil);
	variable_name_cons_qm = variable_name_or_names_qm;
    }
    else
	variable_name_cons_qm = Nil;
    parent_stack = make_parent_stack(variable);
    parent_entry_qm = parent_stack ? M_CAR(parent_stack) : Nil;
    event_detectors = ISVREF(variable,(SI_Long)15L);
    if (event_detectors) {
	event_detector = Nil;
	ab_loop_list_ = event_detectors;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	event_detector = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(ISVREF(event_detector,(SI_Long)1L),Qreceives_a_value) &&  
		!TRUEP(ISVREF(event_detector,(SI_Long)4L))) {
	    ab_loopvar__2 = eval_cons_1(event_detector,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	goto next_loop;
      end_loop:
	triggerable_event_detectors = ab_loopvar_;
	goto end_1;
	triggerable_event_detectors = Qnil;
      end_1:;
    }
    else
	triggerable_event_detectors = Nil;
    event_detector = Nil;
  next_loop_1:
    if ( !TRUEP(triggerable_event_detectors))
	goto end_loop_1;
    eval_pop_store = Nil;
    cons_1 = triggerable_event_detectors;
    if (cons_1) {
	eval_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    triggerable_event_detectors = next_cons;
    event_detector = eval_pop_store;
    trigger_event_detector(event_detector);
    goto next_loop_1;
  end_loop_1:;
    if (parent_entry_qm) {
	event_detectors = ISVREF(M_CAR(parent_entry_qm),(SI_Long)15L);
	if (event_detectors) {
	    event_detector = Nil;
	    ab_loop_list_ = event_detectors;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    event_detector = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (EQ(ISVREF(event_detector,(SI_Long)1L),Qreceives_a_value)) {
		temp_1 = ISVREF(event_detector,(SI_Long)4L);
		temp_2 = EQ(temp_1,
			get_lookup_slot_value_given_default(variable,
			Qparent_attribute_name,Nil));
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		ab_loopvar__2 = eval_cons_1(event_detector,Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
	    }
	    goto next_loop_2;
	  end_loop_2:
	    triggerable_event_detectors = ab_loopvar_;
	    goto end_2;
	    triggerable_event_detectors = Qnil;
	  end_2:;
	}
	else
	    triggerable_event_detectors = Nil;
	event_detector = Nil;
      next_loop_3:
	if ( !TRUEP(triggerable_event_detectors))
	    goto end_loop_3;
	eval_pop_store = Nil;
	cons_1 = triggerable_event_detectors;
	if (cons_1) {
	    eval_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qeval);
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = cons_1;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    else {
		temp = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	triggerable_event_detectors = next_cons;
	event_detector = eval_pop_store;
	trigger_event_detector(event_detector);
	goto next_loop_3;
      end_loop_3:;
    }
    if (EQ(data_type,Qtruth_value))
	collect_rules_for_logical_forward_chaining(variable,new_value,
		chaining_as_well_as_events_qm,parent_stack,
		variable_name_or_names_qm);
    else if (EQ(data_type,Qsymbol))
	collect_rules_for_symbolic_forward_chaining(variable,new_value,
		chaining_as_well_as_events_qm,parent_stack,
		variable_name_or_names_qm);
    else
	collect_rules_for_general_forward_chaining(variable,
		chaining_as_well_as_events_qm,parent_stack,
		variable_name_or_names_qm);
    if (variable_name_cons_qm) {
	inline_note_reclaim_cons(variable_name_cons_qm,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = variable_name_cons_qm;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = variable_name_cons_qm;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = variable_name_cons_qm;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = variable_name_cons_qm;
	}
	M_CDR(variable_name_cons_qm) = Nil;
    }
    return reclaim_parent_stack(parent_stack);
}

DEFINE_VARIABLE_WITH_SYMBOL(Names_and_info_for_chaining, Qnames_and_info_for_chaining);

DEFINE_VARIABLE_WITH_SYMBOL(Designations_in_rule, Qdesignations_in_rule);

static Object Qfor;                /* for */

static Object Qwhenever;           /* whenever */

/* NOTE-NAMES-AND-INFO-FOR-FORWARD-CHAINING-IN-RULE-TRANSLATION */
Object note_names_and_info_for_forward_chaining_in_rule_translation(translation,
	    rule,frame_flags)
    Object translation, rule, frame_flags;
{
    Object designations_in_rule, unabbreviated_designation_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(153,55);
    designations_in_rule = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Designations_in_rule,Qdesignations_in_rule,designations_in_rule,
	    0);
      unabbreviated_designation_qm = Nil;
    next_loop:
      if ( !(CONSP(translation) && EQ(FIRST(translation),Qfor)))
	  goto end_loop;
      unabbreviated_designation_qm = 
	      lookup_previous_reference_and_note_designation(SECOND(translation));
      if (unabbreviated_designation_qm && (SI_Long)0L != 
	      (IFIX(frame_flags) & (SI_Long)8L))
	  note_links_for_dynamic_roles(rule,unabbreviated_designation_qm);
      translation = THIRD(translation);
      goto next_loop;
    end_loop:;
      if ((SI_Long)0L != (IFIX(frame_flags) & (SI_Long)8L))
	  note_forward_chaining_given_antecedent(SECOND(translation),rule,T);
      else if (CONSP(translation) && EQ(CAR(translation),Qwhenever))
	  note_forward_chaining_given_event_antecedent(SECOND(translation),
		  rule);
      result = reclaim_slot_value(Designations_in_rule);
    POP_SPECIAL();
    return result;
}

/* NOTE-NAMES-AND-INFO-FOR-CELL-CHAINING-IN-EXPRESSION */
Object note_names_and_info_for_cell_chaining_in_expression(expression,
	    true_value_recipient)
    Object expression, true_value_recipient;
{
    Object designations_in_rule;
    Declare_special(1);
    Object result;

    x_note_fn_call(153,56);
    designations_in_rule = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Designations_in_rule,Qdesignations_in_rule,designations_in_rule,
	    0);
      note_forward_chaining_given_antecedent(expression,
	      true_value_recipient,Qeither);
      result = reclaim_slot_value(Designations_in_rule);
    POP_SPECIAL();
    return result;
}

/* NOTE-NAMES-AND-INFO-FOR-TRUE-VALUE-CHAINING-IN-EXPRESSION */
Object note_names_and_info_for_true_value_chaining_in_expression(expression,
	    true_value_recipient)
    Object expression, true_value_recipient;
{
    Object designations_in_rule;
    Declare_special(1);
    Object result;

    x_note_fn_call(153,57);
    designations_in_rule = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Designations_in_rule,Qdesignations_in_rule,designations_in_rule,
	    0);
      note_forward_chaining_given_antecedent(expression,
	      true_value_recipient,Qreceives_a_value);
      result = reclaim_slot_value(Designations_in_rule);
    POP_SPECIAL();
    return result;
}

static Object Qis;                 /* is */

static Object Qis_not;             /* is-not */

static Object Qis_not_related;     /* is-not-related */

static Object Qis_related;         /* is-related */

static Object Krelated_change;     /* :related-change */

static Object Knot_related;        /* :not-related */

static Object Krelated;            /* :related */

static Object list_constant;       /* # */

static Object list_constant_1;     /* # */

/* NOTE-FORWARD-CHAINING-GIVEN-ANTECEDENT */
Object note_forward_chaining_given_antecedent(expression,rule,sense)
    Object expression, rule, sense;
{
    Object unabbreviated_designation_qm, operator_1, temp, temp_1;
    Object gensymed_symbol, relation_name_expression, subject_designation;
    Object object_designation, function_template_qm, sub_expression;
    Object ab_loop_list_;
    char temp_2;

    x_note_fn_call(153,58);
    if ( !TRUEP(expression))
	return VALUES_1(Nil);
    else if (ATOM(expression) ? expression && SYMBOLP(expression) : 
	    TRUEP(designation_operator_or_giver_of_value_p(CAR(expression)))) {
	unabbreviated_designation_qm = 
		note_link_and_designations_for_forward_chaining(4,rule,
		expression,Nil,sense);
	if (unabbreviated_designation_qm)
	    return note_links_for_dynamic_roles(rule,
		    unabbreviated_designation_qm);
	else
	    return VALUES_1(Nil);
    }
    else if (CONSP(expression)) {
	operator_1 = M_CAR(expression);
	if ( !SYMBOLP(operator_1) || EQ(operator_1,Qquote))
	    return VALUES_1(Nil);
	else if (EQ(operator_1,Qis)) {
	    temp = SECOND(expression);
	    if (EQ(sense,Qeither) || EQ(sense,Qreceives_a_value))
		temp_1 = Nil;
	    else {
		temp_1 = THIRD(expression);
		temp_1 = SECOND(temp_1);
	    }
	    return note_link_and_designations_for_forward_chaining(4,rule,
		    temp,temp_1,sense);
	}
	else if (EQ(operator_1,Qis_not)) {
	    temp = SECOND(expression);
	    if (EQ(sense,Qeither) || EQ(sense,Qreceives_a_value))
		temp_1 = Nil;
	    else {
		temp_1 = THIRD(expression);
		temp_1 = SECOND(temp_1);
	    }
	    return note_link_and_designations_for_forward_chaining(4,rule,
		    temp,temp_1,EQ(sense,Qeither) || EQ(sense,
		    Qreceives_a_value) ? sense :  !TRUEP(sense) ? T : Nil);
	}
	else if (EQ(operator_1,Qis_not_related) || EQ(operator_1,
		    Qis_related)) {
	    gensymed_symbol = expression;
	    gensymed_symbol = CDR(gensymed_symbol);
	    relation_name_expression = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    subject_designation = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    object_designation = CAR(gensymed_symbol);
	    if (CONSP(relation_name_expression) && 
		    EQ(M_CAR(relation_name_expression),Qquote)) {
		temp_1 = SECOND(relation_name_expression);
		temp_2 = SYMBOLP(temp_1);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		temp_1 = SECOND(relation_name_expression);
		if (EQ(sense,Qeither) || EQ(sense,Qreceives_a_value))
		    temp = Krelated_change;
		else if ( !TRUEP(sense))
		    temp = EQ(operator_1,Qis_related) ? Knot_related : 
			    Krelated;
		else
		    temp = EQ(operator_1,Qis_related) ? Krelated : 
			    Knot_related;
		return note_link_and_designations_for_forward_chaining(5,
			rule,subject_designation,temp_1,temp,
			object_designation);
	    }
	    else
		return VALUES_1(Nil);
	}
	else {
	    if ( !EQ(sense,Qreceives_a_value)) {
		if (memq_function(operator_1,list_constant) &&  !EQ(sense,
			Qeither))
		    sense =  !TRUEP(sense) ? T : Nil;
		else if ( !TRUEP(logical_operator_p(operator_1)) &&  
			!TRUEP(memq_function(operator_1,list_constant_1)))
		    sense = Qeither;
	    }
	    function_template_qm = lookup_function_template(operator_1);
	    if ( !TRUEP(function_template_qm)) {
		sub_expression = Nil;
		ab_loop_list_ = CDR(expression);
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		sub_expression = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		note_forward_chaining_given_antecedent(sub_expression,rule,
			sense);
		goto next_loop;
	      end_loop:
		return VALUES_1(Qnil);
	    }
	    else
		return note_forward_chaining_given_antecedent_and_function_template(expression,
			function_template_qm,rule,sense);
	}
    }
    else
	return VALUES_1(Qnil);
}

static Object Qexpression;         /* expression */

static Object Qdesignation;        /* designation */

static Object Qscope;              /* scope */

static Object Qany;                /* any */

static Object Qother;              /* other */

/* NOTE-FORWARD-CHAINING-GIVEN-ANTECEDENT-AND-FUNCTION-TEMPLATE */
Object note_forward_chaining_given_antecedent_and_function_template(expression,
	    template_1,rule,sense)
    Object expression, template_1, rule, sense;
{
    Object sub_expression, ab_loop_list_, argument_type, ab_loop_list__1;
    Object designation;

    x_note_fn_call(153,59);
    sub_expression = Nil;
    ab_loop_list_ = CDR(expression);
    argument_type = Nil;
    ab_loop_list__1 = CDR(template_1);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    sub_expression = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop;
    argument_type = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if (EQ(argument_type,Qexpression))
	note_forward_chaining_given_antecedent(sub_expression,rule,sense);
    else if (EQ(argument_type,Qdesignation))
	note_links_for_dynamic_roles(rule,
		lookup_previous_reference_and_note_designation(sub_expression));
    else if (EQ(argument_type,Qscope)) {
	designation = slot_value_cons_1(Qany,
		copy_for_slot_value(sub_expression));
	note_links_for_dynamic_roles(rule,
		lookup_previous_reference_and_note_designation(designation));
	reclaim_slot_value(designation);
    }
    else if (EQ(argument_type,Qother));
    else;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* NOTE-FORWARD-CHAINING-GIVEN-EVENT-ANTECEDENT */
Object note_forward_chaining_given_event_antecedent(antecedent,rule)
    Object antecedent, rule;
{
    x_note_fn_call(153,60);
    return note_forward_chaining_given_event_logical_expression(CONSP(antecedent) 
	    && EQ(CAR(antecedent),Qand) ? SECOND(antecedent) : antecedent,
	    rule);
}

static Object Qab_or;              /* or */

static Object Qfails_to_receive_a_value;  /* fails-to-receive-a-value */

static Object Qis_moved;           /* is-moved */

static Object Qis_moved_by_the_user;  /* is-moved-by-the-user */

static Object Qis_moved_by_g2;     /* is-moved-by-g2 */

static Object Qis_resized_by_the_user;  /* is-resized-by-the-user */

static Object Qbecomes_related;    /* becomes-related */

static Object Qceases_to_be_related;  /* ceases-to-be-related */

static Object Qgeneric_event;      /* generic-event */

static Object Qhas_generic_event;  /* has-generic-event */

static Object Qis_activated;       /* is-activated */

static Object Qis_deactivated;     /* is-deactivated */

static Object Qis_enabled;         /* is-enabled */

static Object Qis_disabled;        /* is-disabled */

static Object Qis_created;         /* is-created */

static Object Qgeneric_becomes_related;  /* generic-becomes-related */

static Object Qgeneric_ceases_to_be_related;  /* generic-ceases-to-be-related */

static Object Qgeneric_directly_connected_to;  /* generic-directly-connected-to */

static Object Kconnected;          /* :connected */

static Object Qgeneric_directly_disconnected_from;  /* generic-directly-disconnected-from */

static Object list_constant_2;     /* # */

static Object Kdisconnected;       /* :disconnected */

static Object Qdirectly_connected_to;  /* directly-connected-to */

static Object Qdirectly_disconnected_from;  /* directly-disconnected-from */

static Object Qindirectly_connected_to;  /* indirectly-connected-to */

static Object Qindirectly_disconnected_from;  /* indirectly-disconnected-from */

static Object Qnupec_synchronization_occurs;  /* nupec-synchronization-occurs */

/* NOTE-FORWARD-CHAINING-GIVEN-EVENT-LOGICAL-EXPRESSION */
Object note_forward_chaining_given_event_logical_expression(expression,rule)
    Object expression, rule;
{
    Object operator_1, sub_expression, ab_loop_list_, temp, temp_1;
    Object class_specifier, code;
    char temp_2;

    x_note_fn_call(153,61);
    if (CONSP(expression)) {
	operator_1 = CAR(expression);
	if (EQ(operator_1,Qab_or)) {
	    sub_expression = Nil;
	    ab_loop_list_ = CDR(expression);
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    sub_expression = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    note_forward_chaining_given_event_logical_expression(sub_expression,
		    rule);
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
	else if (EQ(operator_1,Qreceives_a_value))
	    return note_link_and_designations_for_forward_chaining(4,rule,
		    SECOND(expression),Nil,Qreceives_a_value);
	else if (EQ(operator_1,Qfails_to_receive_a_value))
	    return note_link_and_designations_for_forward_chaining(4,rule,
		    SECOND(expression),Nil,Qfails_to_receive_a_value);
	else if (EQ(operator_1,Qis_moved))
	    return note_link_and_designations_for_forward_chaining(4,rule,
		    SECOND(expression),Nil,Qis_moved);
	else if (EQ(operator_1,Qis_moved_by_the_user))
	    return note_link_and_designations_for_forward_chaining(4,rule,
		    SECOND(expression),Nil,Qis_moved_by_the_user);
	else if (EQ(operator_1,Qis_moved_by_g2))
	    return note_link_and_designations_for_forward_chaining(4,rule,
		    SECOND(expression),Nil,Qis_moved_by_g2);
	else if (EQ(operator_1,Qis_resized_by_the_user))
	    return note_link_and_designations_for_forward_chaining(4,rule,
		    SECOND(expression),Nil,Qis_resized_by_the_user);
	else if (EQ(operator_1,Qbecomes_related)) {
	    temp = SECOND(expression);
	    return note_link_and_designations_for_forward_chaining(5,rule,
		    THIRD(expression),SECOND(temp),Krelated,
		    FOURTH(expression));
	}
	else if (EQ(operator_1,Qceases_to_be_related)) {
	    temp = SECOND(expression);
	    return note_link_and_designations_for_forward_chaining(5,rule,
		    THIRD(expression),SECOND(temp),Knot_related,
		    FOURTH(expression));
	}
	else if (EQ(operator_1,Qgeneric_event)) {
	    temp = THIRD(expression);
	    return note_link_and_designations_for_forward_chaining(5,rule,
		    SECOND(expression),SECOND(temp),Qhas_generic_event,
		    FOURTH(expression));
	}
	else if (EQ(operator_1,Qis_activated))
	    return note_link_and_designations_for_forward_chaining(4,rule,
		    SECOND(expression),Nil,Qis_activated);
	else if (EQ(operator_1,Qis_deactivated))
	    return note_link_and_designations_for_forward_chaining(4,rule,
		    SECOND(expression),Nil,Qis_deactivated);
	else if (EQ(operator_1,Qis_enabled))
	    return note_link_and_designations_for_forward_chaining(4,rule,
		    SECOND(expression),Nil,Qis_enabled);
	else if (EQ(operator_1,Qis_disabled))
	    return note_link_and_designations_for_forward_chaining(4,rule,
		    SECOND(expression),Nil,Qis_disabled);
	else if (EQ(operator_1,Qloses_its_value))
	    return note_link_and_designations_for_forward_chaining(4,rule,
		    SECOND(expression),Nil,Qloses_its_value);
	else if (EQ(operator_1,Qis_created))
	    return note_link_and_designations_for_forward_chaining(4,rule,
		    SECOND(expression),Nil,Qis_created);
	else if (EQ(operator_1,Qgeneric_becomes_related))
	    return note_link_and_designations_for_forward_chaining(5,rule,
		    SECOND(expression),Nil,Krelated,THIRD(expression));
	else if (EQ(operator_1,Qgeneric_ceases_to_be_related))
	    return note_link_and_designations_for_forward_chaining(5,rule,
		    SECOND(expression),Nil,Knot_related,THIRD(expression));
	else if (EQ(operator_1,Qgeneric_directly_connected_to)) {
	    temp_1 = SECOND(expression);
	    temp = filter_symbol_given_filter_expression(THIRD(expression));
	    return note_link_and_designations_for_forward_chaining(5,rule,
		    temp_1,temp,Kconnected,FOURTH(expression));
	}
	else if (EQ(operator_1,Qgeneric_directly_disconnected_from)) {
	    temp = filter_symbol_given_filter_expression(SECOND(expression));
	    return note_link_and_designations_for_forward_chaining(5,rule,
		    list_constant_2,temp,Kdisconnected,THIRD(expression));
	}
	else if (EQ(operator_1,Qdirectly_connected_to)) {
	    temp_1 = SECOND(expression);
	    temp = filter_symbol_given_filter_expression(THIRD(expression));
	    return note_link_and_designations_for_forward_chaining(5,rule,
		    temp_1,temp,Kconnected,FOURTH(expression));
	}
	else if (EQ(operator_1,Qdirectly_disconnected_from)) {
	    temp = SECOND(expression);
	    class_specifier = slot_value_list_2(Qany,SECOND(temp));
	    temp = filter_symbol_given_filter_expression(THIRD(expression));
	    note_link_and_designations_for_forward_chaining(5,rule,
		    class_specifier,temp,Kdisconnected,FOURTH(expression));
	    return reclaim_slot_value_list_1(class_specifier);
	}
	else if (EQ(operator_1,Qindirectly_connected_to))
	    return note_link_and_designations_for_forward_chaining(5,rule,
		    SECOND(expression),Nil,Kconnected,THIRD(expression));
	else if (EQ(operator_1,Qindirectly_disconnected_from))
	    return note_link_and_designations_for_forward_chaining(5,rule,
		    SECOND(expression),Nil,Kdisconnected,THIRD(expression));
	else {
	    if (EQ(operator_1,Qnupec_synchronization_occurs)) {
		code = M_CAR(M_CDR(Journal_shutout_scan_p));
		temp_2 = FIXNUMP(code) && (IFIX(code) & (SI_Long)256L) != 
			(SI_Long)0L ? 
			TRUEP(M_CAR(M_CDR(Cache_nupec_semantics_graph))) : 
			TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2)
		return note_link_and_designations_for_forward_chaining(4,
			rule,Qnupec_synchronization_occurs,Nil,
			Qnupec_synchronization_occurs);
	    else
		return VALUES_1(Nil);
	}
    }
    else
	return VALUES_1(Nil);
}

static Object Qno_filter;          /* no-filter */

/* FILTER-SYMBOL-GIVEN-FILTER-EXPRESSION */
Object filter_symbol_given_filter_expression(filter_expression)
    Object filter_expression;
{
    Object filter_symbol;

    x_note_fn_call(153,62);
    filter_symbol = SECOND(filter_expression);
    if (EQ(filter_symbol,Qno_filter))
	return VALUES_1(Nil);
    else
	return VALUES_1(filter_symbol);
}

static Object Qtrue;               /* true */

static Object Qfalse;              /* false */

/* NOTE-LINK-AND-DESIGNATIONS-FOR-FORWARD-CHAINING */
Object note_link_and_designations_for_forward_chaining varargs_1(int, n)
{
    Object rule, designation, symbolic_value_qm, sense_qm;
    Object second_designation_qm, unabbreviated_designation;
    Object second_unabbreviated_designation_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(153,63);
    INIT_ARGS_nonrelocating();
    rule = REQUIRED_ARG_nonrelocating();
    designation = REQUIRED_ARG_nonrelocating();
    symbolic_value_qm = REQUIRED_ARG_nonrelocating();
    sense_qm = REQUIRED_ARG_nonrelocating();
    second_designation_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !EQ(designation,Qtrue) &&  !EQ(designation,Qfalse)) {
	unabbreviated_designation = 
		lookup_previous_reference_and_note_designation(designation);
	second_unabbreviated_designation_qm = second_designation_qm ? 
		lookup_previous_reference_and_note_designation(second_designation_qm) 
		: Nil;
	if (invertible_designation_p(unabbreviated_designation) && ( 
		!TRUEP(second_unabbreviated_designation_qm) || 
		invertible_designation_p(second_unabbreviated_designation_qm)))
	    note_link_for_forward_chaining(5,rule,
		    unabbreviated_designation,symbolic_value_qm,sense_qm,
		    second_unabbreviated_designation_qm);
	return VALUES_1(unabbreviated_designation);
    }
    else
	return VALUES_1(Nil);
}

/* NOTE-DESIGNATION */
Object note_designation(designation)
    Object designation;
{
    Object temp;

    x_note_fn_call(153,64);
    if (CONSP(designation)) {
	temp = slot_value_cons_1(local_name_for_designation(designation),
		designation);
	Designations_in_rule = slot_value_cons_1(temp,Designations_in_rule);
	return VALUES_1(Designations_in_rule);
    }
    else
	return VALUES_1(Nil);
}

/* LOOKUP-PREVIOUS-REFERENCE-AND-NOTE-DESIGNATION */
Object lookup_previous_reference_and_note_designation(designation)
    Object designation;
{
    Object temp, local_designation_qm, previous_designation;
    Object referenced_element, entry, ab_loop_list_, naming_element;
    Object local_copy, local_parent_designation, temp_1;

    x_note_fn_call(153,65);
    if ( !TRUEP(designation) || ATOM(designation) &&  !SYMBOLP(designation))
	return VALUES_1(designation);
    else if (SYMBOLP(designation)) {
	temp = assq_function(designation,Designations_in_rule);
	local_designation_qm = CDR(temp);
	if (local_designation_qm)
	    return VALUES_1(local_designation_qm);
	else
	    return VALUES_1(designation);
    }
    else if (CONSP(designation) && IFIX(length(designation)) == (SI_Long)2L) {
	previous_designation = Nil;
	if (designation_requires_previous_reference_p(designation)) {
	    referenced_element = 
		    atomic_naming_element_of_designation(designation);
	    entry = Nil;
	    ab_loop_list_ = Designations_in_rule;
	    naming_element = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    entry = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    naming_element = atomic_naming_element_of_designation(CDR(entry));
	    if (EQ(referenced_element,naming_element)) {
		previous_designation = CDR(entry);
		goto end_loop;
	    }
	    goto next_loop;
	  end_loop:;
	}
	if (previous_designation)
	    return VALUES_1(previous_designation);
	else {
	    local_copy = copy_for_slot_value(designation);
	    note_designation(local_copy);
	    return VALUES_1(local_copy);
	}
    }
    else if (CONSP(designation) && IFIX(length(designation)) == (SI_Long)3L) {
	local_parent_designation = 
		lookup_previous_reference_and_note_designation(domain_of_designation(designation));
	temp_1 = FIRST(designation);
	temp = 
		copy_tree_using_slot_value_conses_1(role_of_designation(designation));
	local_copy = slot_value_list_3(temp_1,temp,
		copy_for_slot_value(local_parent_designation));
	note_designation(local_copy);
	return VALUES_1(local_copy);
    }
    else
	return VALUES_1(designation);
}

static Object Qthis_workspace;     /* this-workspace */

static Object Qthis_rule;          /* this-rule */

static Object Qframe_flags;        /* frame-flags */

/* NOTE-LINK-FOR-FORWARD-CHAINING */
Object note_link_for_forward_chaining varargs_1(int, n)
{
    Object rule, designation, symbolic_value_qm, sense_qm;
    Object second_focus_designation_qm, chaining_list_symbol;
    Object focus_symbol_for_link_qm, local_name_for_focus_qm;
    Object second_focus_symbol_for_link_qm, second_local_name_for_focus_qm;
    Object new_link, temp, entry, ab_loop_list_;
    SI_Long svref_new_value;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(153,66);
    INIT_ARGS_nonrelocating();
    rule = REQUIRED_ARG_nonrelocating();
    designation = REQUIRED_ARG_nonrelocating();
    symbolic_value_qm = REQUIRED_ARG_nonrelocating();
    sense_qm = REQUIRED_ARG_nonrelocating();
    second_focus_designation_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    chaining_list_symbol = chaining_symbol_for_designation(designation);
    focus_symbol_for_link_qm = Nil;
    local_name_for_focus_qm = Nil;
    second_focus_symbol_for_link_qm = Nil;
    second_local_name_for_focus_qm = Nil;
    new_link = Nil;
    result = chaining_focal_role_and_local_name_for_designation(designation);
    MVS_2(result,focus_symbol_for_link_qm,local_name_for_focus_qm);
    temp = role_name_of_role(role_of_designation(designation));
    if (EQ(temp,Qthis_workspace) || EQ(temp,Qthis_rule)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(rule,Qframe_flags);
	svref_new_value = IFIX(ISVREF(rule,(SI_Long)4L)) | (SI_Long)67108864L;
	ISVREF(rule,(SI_Long)4L) = FIX(svref_new_value);
    }
    if (second_focus_designation_qm) {
	result = chaining_focal_role_and_local_name_for_designation(second_focus_designation_qm);
	MVS_2(result,second_focus_symbol_for_link_qm,
		second_local_name_for_focus_qm);
    }
    new_link = make_forward_chaining_link(9,rule,designation,
	    focus_symbol_for_link_qm,local_name_for_focus_qm,
	    symbolic_value_qm,sense_qm,second_focus_designation_qm,
	    second_focus_symbol_for_link_qm,second_local_name_for_focus_qm);
    entry = Nil;
    ab_loop_list_ = Names_and_info_for_chaining;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(chaining_list_symbol,M_CAR(entry)) && 
	    equal_forward_chaining_link(new_link,M_CDR(entry))) {
	delete_frame(new_link);
	return VALUES_1(Nil);
    }
    goto next_loop;
  end_loop:
    Names_and_info_for_chaining = 
	    slot_value_cons_1(slot_value_cons_1(chaining_list_symbol,
	    new_link),Names_and_info_for_chaining);
    return VALUES_1(Qnil);
}

static Object Qrelated;            /* related */

/* NOTE-LINKS-FOR-DYNAMIC-ROLES */
Object note_links_for_dynamic_roles(rule,unabbreviated_designation)
    Object rule, unabbreviated_designation;
{
    Object role, domain_qm, temp;

    x_note_fn_call(153,67);
    if (CONSP(unabbreviated_designation)) {
	role = 
		simple_role_of_role(role_of_designation(unabbreviated_designation));
	domain_qm = domain_of_designation(unabbreviated_designation);
	if (CONSP(role) && 
		    invertible_designation_p(unabbreviated_designation)) {
	    temp = M_CAR(role);
	    if (EQ(temp,Qrelated))
		note_link_for_forward_chaining(5,rule,
			unabbreviated_designation,SECOND(role),Krelated,
			domain_qm);
	}
	if (domain_qm)
	    return note_links_for_dynamic_roles(rule,domain_qm);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qbackward_chaining_link;  /* backward-chaining-link */

/* MAKE-BACKWARD-CHAINING-LINK */
Object make_backward_chaining_link(backward_link_rule,
	    backward_link_designation,backward_link_focus,
	    backward_link_focus_local_name,backward_link_symbolic_value)
    Object backward_link_rule, backward_link_designation, backward_link_focus;
    Object backward_link_focus_local_name, backward_link_symbolic_value;
{
    Object new_frame, gensymed_symbol, old_current_block_of_dependent_frame;

    x_note_fn_call(153,68);
    new_frame = make_frame(Qbackward_chaining_link);
    gensymed_symbol = Nil;
    old_current_block_of_dependent_frame = Current_block_of_dependent_frame;
    Current_block_of_dependent_frame = Qdependent_frame_has_no_owner;
    if (Noting_changes_to_kb_p)
	note_change_to_dependent_frame_1();
    SVREF(new_frame,FIX((SI_Long)2L)) = backward_link_rule;
    if (Noting_changes_to_kb_p)
	note_change_to_dependent_frame_1();
    SVREF(new_frame,FIX((SI_Long)3L)) = backward_link_designation;
    if (Noting_changes_to_kb_p)
	note_change_to_dependent_frame_1();
    SVREF(new_frame,FIX((SI_Long)4L)) = backward_link_focus;
    if (Noting_changes_to_kb_p)
	note_change_to_dependent_frame_1();
    SVREF(new_frame,FIX((SI_Long)5L)) = backward_link_focus_local_name;
    if (Noting_changes_to_kb_p)
	note_change_to_dependent_frame_1();
    gensymed_symbol = SVREF(new_frame,FIX((SI_Long)6L)) = 
	    backward_link_symbolic_value;
    Current_block_of_dependent_frame = old_current_block_of_dependent_frame;
    return VALUES_1(new_frame);
}

/* COPY-FRAME-FOR-BACKWARD-CHAINING-LINK */
Object copy_frame_for_backward_chaining_link(backward_chaining_link)
    Object backward_chaining_link;
{
    x_note_fn_call(153,69);
    return make_backward_chaining_link(ISVREF(backward_chaining_link,
	    (SI_Long)2L),copy_for_slot_value(ISVREF(backward_chaining_link,
	    (SI_Long)3L)),ISVREF(backward_chaining_link,(SI_Long)4L),
	    ISVREF(backward_chaining_link,(SI_Long)5L),
	    ISVREF(backward_chaining_link,(SI_Long)6L));
}

/* GENERATE-FORWARD-AND-BACKWARD-CHAINING-LINKS */
Object generate_forward_and_backward_chaining_links(rule,translation)
    Object rule, translation;
{
    Object current_block_of_dependent_frame, names_and_info_for_chaining;
    Object frame_flags;
    Declare_special(2);
    Object result;

    x_note_fn_call(153,70);
    current_block_of_dependent_frame = Qdependent_frame_has_no_owner;
    PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
	    1);
      names_and_info_for_chaining = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Names_and_info_for_chaining,Qnames_and_info_for_chaining,names_and_info_for_chaining,
	      0);
	frame_flags = ISVREF(rule,(SI_Long)4L);
	note_names_and_info_for_forward_chaining_in_rule_translation(translation,
		rule,frame_flags);
	note_names_and_info_for_backward_chaining_in_rule_translation(translation,
		rule,frame_flags);
	result = VALUES_1(Names_and_info_for_chaining);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* INSTALL-CHAINING-LINKS */
Object install_chaining_links(chaining_links)
    Object chaining_links;
{
    Object name, link_1, ab_loop_list_, ab_loop_desetq_, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(153,71);
    if (chaining_links) {
	decache_class_chaining_lists();
	name = Nil;
	link_1 = Nil;
	ab_loop_list_ = chaining_links;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	name = CAR(ab_loop_desetq_);
	link_1 = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	sub_class_bit_vector = ISVREF(ISVREF(link_1,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Forward_chaining_link_class_description,
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
	    mutate_kb_specific_property_value(name,eval_cons_1(link_1,
		    lookup_kb_specific_property_value(name,
		    Forward_chaining_list_kbprop)),
		    Forward_chaining_list_kbprop);
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(link_1,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Backward_chaining_link_class_description,
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
		install_backward_chaining_link(name,link_1);
	    else;
	}
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* DEINSTALL-CHAINING-LINKS */
Object deinstall_chaining_links(chaining_links)
    Object chaining_links;
{
    Object name, link_1, ab_loop_list_, ab_loop_desetq_, sub_class_bit_vector;
    Object temp_1, temp_2;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(153,72);
    if (chaining_links) {
	decache_class_chaining_lists();
	name = Nil;
	link_1 = Nil;
	ab_loop_list_ = chaining_links;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	name = CAR(ab_loop_desetq_);
	link_1 = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	sub_class_bit_vector = ISVREF(ISVREF(link_1,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Forward_chaining_link_class_description,
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
	    temp_1 = name;
	    temp_2 = delete_eval_element_1(link_1,
		    lookup_kb_specific_property_value(name,
		    Forward_chaining_list_kbprop));
	    mutate_kb_specific_property_value(temp_1,temp_2,
		    Forward_chaining_list_kbprop);
	}
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(link_1,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Backward_chaining_link_class_description,
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
		deinstall_backward_chaining_link(name,link_1);
	    else;
	}
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* INSTALL-BACKWARD-CHAINING-LINK */
Object install_backward_chaining_link(name,backward_chaining_link)
    Object name, backward_chaining_link;
{
    Object designation, temp;
    char temp_1;

    x_note_fn_call(153,73);
    designation = ISVREF(backward_chaining_link,(SI_Long)3L);
    if (domain_of_designation(designation)) {
	temp = domain_of_designation(designation);
	temp_1 = SYMBOLP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	temp = nconc2(lookup_kb_specific_property_value(name,
		Backward_chaining_list_kbprop),
		eval_cons_1(backward_chaining_link,Nil));
	mutate_kb_specific_property_value(name,temp,
		Backward_chaining_list_kbprop);
    }
    else
	mutate_kb_specific_property_value(name,
		eval_cons_1(backward_chaining_link,
		lookup_kb_specific_property_value(name,
		Backward_chaining_list_kbprop)),Backward_chaining_list_kbprop);
    decache_class_chaining_lists();
    return VALUES_1(Nil);
}

/* DEINSTALL-BACKWARD-CHAINING-LINK */
Object deinstall_backward_chaining_link(name,backward_chaining_link)
    Object name, backward_chaining_link;
{
    Object temp;

    x_note_fn_call(153,74);
    temp = delete_eval_element_1(backward_chaining_link,
	    lookup_kb_specific_property_value(name,
	    Backward_chaining_list_kbprop));
    mutate_kb_specific_property_value(name,temp,Backward_chaining_list_kbprop);
    decache_class_chaining_lists();
    return VALUES_1(Nil);
}

/* NOTE-NAMES-AND-INFO-FOR-BACKWARD-CHAINING-IN-RULE-TRANSLATION */
Object note_names_and_info_for_backward_chaining_in_rule_translation(translation,
	    rule,frame_flags)
    Object translation, rule, frame_flags;
{
    Object designations_in_rule;
    Declare_special(1);
    Object result;

    x_note_fn_call(153,75);
    designations_in_rule = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Designations_in_rule,Qdesignations_in_rule,designations_in_rule,
	    0);
    next_loop:
      if ( !(CONSP(translation) && EQ(FIRST(translation),Qfor)))
	  goto end_loop;
      lookup_previous_reference_and_note_designation(SECOND(translation));
      translation = THIRD(translation);
      goto next_loop;
    end_loop:
      if ((SI_Long)0L != (IFIX(frame_flags) & (SI_Long)2L)) {
	  note_designations_in_antecedant(SECOND(translation));
	  note_names_and_info_for_backward_chaining_in_actions(THIRD(translation),
		  rule);
      }
      result = reclaim_slot_value(Designations_in_rule);
    POP_SPECIAL();
    return result;
}

/* NOTE-DESIGNATIONS-IN-ANTECEDANT */
Object note_designations_in_antecedant(expression)
    Object expression;
{
    Object operator_1, template_qm, sub_expression, ab_loop_list_;

    x_note_fn_call(153,76);
    if ( !TRUEP(expression))
	return VALUES_1(Nil);
    else if (ATOM(expression) ? expression && SYMBOLP(expression) : 
	    TRUEP(designation_operator_or_giver_of_value_p(CAR(expression))))
	return lookup_previous_reference_and_note_designation(expression);
    else if (CONSP(expression)) {
	operator_1 = FIRST(expression);
	if (SYMBOLP(operator_1) &&  !EQ(operator_1,Qquote)) {
	    template_qm = lookup_function_template(operator_1);
	    if ( !TRUEP(template_qm)) {
		sub_expression = Nil;
		ab_loop_list_ = CDR(expression);
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		sub_expression = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		note_designations_in_antecedant(sub_expression);
		goto next_loop;
	      end_loop:
		return VALUES_1(Qnil);
	    }
	    else
		return note_designations_in_antecedant_given_template(expression,
			template_qm);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Qnil);
}

/* NOTE-DESIGNATIONS-IN-ANTECEDANT-GIVEN-TEMPLATE */
Object note_designations_in_antecedant_given_template(expression,template_1)
    Object expression, template_1;
{
    Object argument, ab_loop_list_, argument_type, ab_loop_list__1;
    Object designation;

    x_note_fn_call(153,77);
    argument = Nil;
    ab_loop_list_ = CDR(expression);
    argument_type = Nil;
    ab_loop_list__1 = CDR(template_1);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop;
    argument_type = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if (EQ(argument_type,Qexpression))
	note_designations_in_antecedant(argument);
    else if (EQ(argument_type,Qdesignation))
	lookup_previous_reference_and_note_designation(argument);
    else if (EQ(argument_type,Qscope)) {
	designation = slot_value_cons_1(Qany,copy_for_slot_value(argument));
	lookup_previous_reference_and_note_designation(designation);
	reclaim_slot_value(designation);
    }
    else if (EQ(argument_type,Qother));
    else;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qin_order;           /* in-order */

static Object Qsimultaneously;     /* simultaneously */

static Object Qconclude_not;       /* conclude-not */

static Object Qconclude;           /* conclude */

/* NOTE-NAMES-AND-INFO-FOR-BACKWARD-CHAINING-IN-ACTIONS */
Object note_names_and_info_for_backward_chaining_in_actions(actions,rule)
    Object actions, rule;
{
    Object temp, action, ab_loop_list_;
    char temp_1;

    x_note_fn_call(153,78);
    if (CONSP(actions)) {
	temp = CAR(actions);
	if (EQ(temp,Qand) || EQ(temp,Qin_order) || EQ(temp,Qsimultaneously)) {
	    action = Nil;
	    ab_loop_list_ = CDR(actions);
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    action = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    note_names_and_info_for_backward_chaining_in_actions(action,rule);
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
	else if (EQ(temp,Qconclude_not))
	    return note_link_and_designations_for_backward_chaining(rule,
		    SECOND(actions),Nil);
	else if (EQ(temp,Qconclude)) {
	    temp = THIRD(actions);
	    if (CONSP(temp)) {
		temp = THIRD(actions);
		temp_1 = EQ(FIRST(temp),Qquote);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		temp = THIRD(actions);
		temp = SECOND(temp);
		temp_1 = SYMBOLP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		temp = THIRD(actions);
		return note_link_and_designations_for_backward_chaining(rule,
			SECOND(actions),SECOND(temp));
	    }
	    else
		return note_link_and_designations_for_backward_chaining(rule,
			SECOND(actions),Nil);
	}
	else
	    return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* NOTE-LINK-AND-DESIGNATIONS-FOR-BACKWARD-CHAINING */
Object note_link_and_designations_for_backward_chaining(rule,designation,
	    symbolic_value_qm)
    Object rule, designation, symbolic_value_qm;
{
    Object unabbreviated_designation;

    x_note_fn_call(153,79);
    unabbreviated_designation = 
	    lookup_previous_reference_and_note_designation(designation);
    if (invertible_designation_p(unabbreviated_designation))
	return note_link_for_backward_chaining(rule,
		unabbreviated_designation,symbolic_value_qm);
    else
	return VALUES_1(Nil);
}

/* NOTE-LINK-FOR-BACKWARD-CHAINING */
Object note_link_for_backward_chaining(rule,designation,symbolic_value_qm)
    Object rule, designation, symbolic_value_qm;
{
    Object chaining_symbol, focal_role_qm, local_name_for_focus_qm, new_link;
    Object temp, entry, ab_loop_list_, frame, symbol, gensymed_symbol;
    Object sub_class_bit_vector, link1, link2, temp_2;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Object result;

    x_note_fn_call(153,80);
    chaining_symbol = chaining_symbol_for_designation(designation);
    focal_role_qm = Nil;
    local_name_for_focus_qm = Nil;
    new_link = Nil;
    result = chaining_focal_role_and_local_name_for_designation(designation);
    MVS_2(result,focal_role_qm,local_name_for_focus_qm);
    temp = make_simple_designation_slot_value_copy(designation);
    new_link = make_backward_chaining_link(rule,temp,focal_role_qm,
	    local_name_for_focus_qm,symbolic_value_qm);
    entry = Nil;
    ab_loop_list_ = Names_and_info_for_chaining;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(chaining_symbol,M_CAR(entry))) {
	frame = M_CDR(entry);
	symbol = Qbackward_chaining_link;
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
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	link1 = new_link;
	link2 = M_CDR(entry);
	if (EQ(ISVREF(link1,(SI_Long)2L),ISVREF(link2,(SI_Long)2L))) {
	    temp_2 = ISVREF(link1,(SI_Long)3L);
	    temp = ISVREF(link2,(SI_Long)3L);
	    temp_1 = EQUAL(temp_2,temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    temp_2 = ISVREF(link1,(SI_Long)4L);
	    temp = ISVREF(link2,(SI_Long)4L);
	    temp_1 = EQUAL(temp_2,temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    temp_2 = ISVREF(link1,(SI_Long)5L);
	    temp = ISVREF(link2,(SI_Long)5L);
	    temp_1 = EQUAL(temp_2,temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    temp_2 = ISVREF(link1,(SI_Long)6L);
	    temp = ISVREF(link2,(SI_Long)6L);
	    temp_1 = EQUAL(temp_2,temp);
	}
	else
	    temp_1 = TRUEP(Nil);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	delete_frame(new_link);
	return VALUES_1(Nil);
    }
    goto next_loop;
  end_loop:
    Names_and_info_for_chaining = 
	    slot_value_cons_1(slot_value_cons_1(chaining_symbol,new_link),
	    Names_and_info_for_chaining);
    return VALUES_1(Qnil);
}

/* INVOKE-BACKWARD-CHAINING-FOR-SYMBOLIC-CLASS-REFERENCES */
Object invoke_backward_chaining_for_symbolic_class_references(object,
	    possible_values_qm,symbolic_value_required_qm)
    Object object, possible_values_qm, symbolic_value_required_qm;
{
    Object link_1, class_description, classes, gensymed_symbol, list_1;
    Object cache_qm, ab_loop_list_, class_1, specific_list, new_value;
    Object old_value, symbolic_value_qm, designation, temp;
    char temp_1;

    x_note_fn_call(153,81);
    link_1 = Nil;
    class_description = ISVREF(object,(SI_Long)1L);
    classes = ISVREF(class_description,(SI_Long)2L);
    gensymed_symbol = M_CAR(classes);
    list_1 = INLINE_SYMBOL_PLIST(gensymed_symbol);
  next_loop:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop;
  end_loop:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_1:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Cached_class_backward_chaining_list_kbprop))
	goto end_loop_1;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_1;
  end_loop_1:
    cache_qm = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    if (cache_qm)
	ab_loop_list_ = M_CDR(cache_qm);
    else {
	class_1 = Nil;
	ab_loop_list_ = classes;
	specific_list = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	class_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	specific_list = lookup_kb_specific_property_value(class_1,
		Backward_chaining_list_kbprop);
	if (specific_list) {
	    specific_list = copy_list_using_eval_conses_1(specific_list);
	    if (cache_qm)
		cache_qm = nconc2(cache_qm,specific_list);
	    else
		cache_qm = specific_list;
	}
	if (EQ(class_1,Qitem))
	    goto end_loop_2;
	goto next_loop_2;
      end_loop_2:
	mutate_kb_specific_property_value(M_CAR(classes),eval_cons_1(Nil,
		cache_qm),Cached_class_backward_chaining_list_kbprop);
	new_value = eval_cons_1(M_CAR(classes),Nil);
	old_value = Nil;
      next_loop_3:
	old_value = Cached_classes_for_backward_chaining;
	M_CDR(new_value) = old_value;
	if (CAS_SYMBOL(Qcached_classes_for_backward_chaining,old_value,
		new_value))
	    goto end_loop_3;
	goto next_loop_3;
      end_loop_3:
	goto end_1;
      end_1:;
	ab_loop_list_ = cache_qm;
	goto end_2;
	ab_loop_list_ = Qnil;
      end_2:;
    }
    symbolic_value_qm = Nil;
    designation = Nil;
  next_loop_4:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_4;
    link_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    symbolic_value_qm = ISVREF(link_1,(SI_Long)6L);
    designation = ISVREF(link_1,(SI_Long)3L);
    if (( !TRUEP(symbolic_value_required_qm) || symbolic_value_qm) && ( 
	    !TRUEP(symbolic_value_qm) ||  !TRUEP(possible_values_qm) || 
	    memq_function(symbolic_value_qm,possible_values_qm)) &&  
	    !SYMBOLP(designation)) {
	if (domain_of_designation(designation)) {
	    temp = role_of_designation(designation);
	    temp_1 = SYMBOLP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_1 =  !temp_1;
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	add_tuple_to_backward_link_list(link_1,object);
    goto next_loop_4;
  end_loop_4:
    return VALUES_1(Qnil);
}

/* INVOKE-BACKWARD-CHAINING-FOR-CLASS-REFERENCES */
Object invoke_backward_chaining_for_class_references(object)
    Object object;
{
    Object link_1, class_description, classes, gensymed_symbol, list_1;
    Object cache_qm, ab_loop_list_, class_1, specific_list, new_value;
    Object old_value, designation, temp;
    char temp_1;

    x_note_fn_call(153,82);
    link_1 = Nil;
    class_description = ISVREF(object,(SI_Long)1L);
    classes = ISVREF(class_description,(SI_Long)2L);
    gensymed_symbol = M_CAR(classes);
    list_1 = INLINE_SYMBOL_PLIST(gensymed_symbol);
  next_loop:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop;
  end_loop:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_1:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Cached_class_backward_chaining_list_kbprop))
	goto end_loop_1;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_1;
  end_loop_1:
    cache_qm = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    if (cache_qm)
	ab_loop_list_ = M_CDR(cache_qm);
    else {
	class_1 = Nil;
	ab_loop_list_ = classes;
	specific_list = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	class_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	specific_list = lookup_kb_specific_property_value(class_1,
		Backward_chaining_list_kbprop);
	if (specific_list) {
	    specific_list = copy_list_using_eval_conses_1(specific_list);
	    if (cache_qm)
		cache_qm = nconc2(cache_qm,specific_list);
	    else
		cache_qm = specific_list;
	}
	if (EQ(class_1,Qitem))
	    goto end_loop_2;
	goto next_loop_2;
      end_loop_2:
	mutate_kb_specific_property_value(M_CAR(classes),eval_cons_1(Nil,
		cache_qm),Cached_class_backward_chaining_list_kbprop);
	new_value = eval_cons_1(M_CAR(classes),Nil);
	old_value = Nil;
      next_loop_3:
	old_value = Cached_classes_for_backward_chaining;
	M_CDR(new_value) = old_value;
	if (CAS_SYMBOL(Qcached_classes_for_backward_chaining,old_value,
		new_value))
	    goto end_loop_3;
	goto next_loop_3;
      end_loop_3:
	goto end_1;
      end_1:;
	ab_loop_list_ = cache_qm;
	goto end_2;
	ab_loop_list_ = Qnil;
      end_2:;
    }
    designation = Nil;
  next_loop_4:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_4;
    link_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    designation = ISVREF(link_1,(SI_Long)3L);
    temp = ISVREF(link_1,(SI_Long)3L);
    if ( !SYMBOLP(temp)) {
	if (domain_of_designation(designation)) {
	    temp = role_of_designation(designation);
	    temp_1 = SYMBOLP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_1 =  !temp_1;
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	add_tuple_to_backward_link_list(link_1,object);
    goto next_loop_4;
  end_loop_4:
    return VALUES_1(Qnil);
}

/* ADD-TUPLE-TO-BACKWARD-LINK-LIST */
Object add_tuple_to_backward_link_list(link_1,object)
    Object link_1, object;
{
    Object new_precedence, new_cons, temp, svref_arg_2, svref_new_value;
    Object gensymed_symbol, gensymed_symbol_1, new_entry, splice_point;
    Object link_position, temp_1;

    x_note_fn_call(153,83);
    new_precedence = backward_chaining_precedence_function(ISVREF(link_1,
	    (SI_Long)2L));
    new_cons = ISVREF(Available_eval_conses_vector,IFIX(Current_thread_index));
    if (new_cons) {
	temp = Available_eval_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_eval_cons_pool();
    new_cons = ISVREF(Available_eval_conses_vector,IFIX(Current_thread_index));
    if (new_cons) {
	temp = Available_eval_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = Nil;
	}
	gensymed_symbol_1 = new_cons;
    }
    else
	gensymed_symbol_1 = Nil;
    if ( !TRUEP(gensymed_symbol_1))
	gensymed_symbol_1 = replenish_eval_cons_pool();
    M_CAR(gensymed_symbol_1) = link_1;
    M_CDR(gensymed_symbol_1) = object;
    inline_note_allocate_cons(gensymed_symbol_1,Qeval);
    M_CAR(gensymed_symbol) = gensymed_symbol_1;
    temp = Links_and_objects;
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qeval);
    new_entry = gensymed_symbol;
    splice_point = Nil;
    link_position = Links_and_objects;
  next_loop:
    if ( !TRUEP(link_position))
	goto end_loop;
    temp_1 = 
	    backward_chaining_precedence_function(ISVREF(M_CAR(M_CAR(link_position)),
	    (SI_Long)2L));
    if (NUM_LE(new_precedence,temp_1))
	goto end_loop;
    splice_point = link_position;
    link_position = M_CDR(link_position);
    goto next_loop;
  end_loop:
    if ( !TRUEP(splice_point))
	Links_and_objects = new_entry;
    else {
	temp = M_CDR(splice_point);
	M_CDR(new_entry) = temp;
	M_CDR(splice_point) = new_entry;
    }
    return VALUES_1(Qnil);
}

/* INVOKE-RULES-FOR-BACKWARD-CHAINING */
Object invoke_rules_for_backward_chaining(variable)
    Object variable;
{
    Object data_type, links_and_objects, svref_new_value;
    Declare_special(1);

    x_note_fn_call(153,84);
    if ( !TRUEP(ISVREF(variable,(SI_Long)42L))) {
	data_type = 
		type_specification_of_variable_or_parameter_value(variable);
	links_and_objects = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Links_and_objects,Qlinks_and_objects,links_and_objects,
		0);
	  collect_rules_for_backward_chaining(variable,data_type);
	  svref_new_value = Priority_of_current_task;
	  ISVREF(variable,(SI_Long)42L) = svref_new_value;
	  svref_new_value = Links_and_objects;
	  ISVREF(variable,(SI_Long)41L) = svref_new_value;
	POP_SPECIAL();
    }
    else
	maximize_priority_of_variable(variable,Priority_of_current_task);
    return execute_backward_chaining_for_rules(variable);
}

static Object Qg2_defstruct_structure_name_rule_instance_g2_struct;  /* g2-defstruct-structure-name::rule-instance-g2-struct */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* WITHDRAW-BACKWARD-CHAINING */
Object withdraw_backward_chaining(variable)
    Object variable;
{
    Object new_rules_qm, interest_list, gensymed_symbol;
    Object structure_being_reclaimed, temp, svref_arg_2, interesting_thing;
    Object ab_loop_list_, x2, sub_class_bit_vector, pruned_interest_list;
    Object last_1, next_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(153,85);
    new_rules_qm = ISVREF(variable,(SI_Long)41L);
    interest_list = ISVREF(variable,(SI_Long)35L);
    ISVREF(variable,(SI_Long)42L) = Nil;
    if (new_rules_qm) {
	reclaim_eval_tree_1(new_rules_qm);
	ISVREF(variable,(SI_Long)41L) = Nil;
    }
    if (ISVREF(variable,(SI_Long)34L))
	cancel_formula_for_backward_chaining(variable);
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = ISVREF(variable,(SI_Long)37L);
    if (CAS_SVREF(variable,(SI_Long)37L,gensymed_symbol,Nil)) {
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
    if (interest_list) {
	ISVREF(variable,(SI_Long)35L) = Nil;
	interesting_thing = Nil;
	ab_loop_list_ = interest_list;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	interesting_thing = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (SIMPLE_VECTOR_P(interesting_thing) && 
		EQ(ISVREF(interesting_thing,(SI_Long)0L),
		Qg2_defstruct_structure_name_rule_instance_g2_struct))
	    remove_request_for_rule_instance_invocation(interesting_thing,
		    variable);
	else {
	    if (SIMPLE_VECTOR_P(interesting_thing) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(interesting_thing)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(interesting_thing,
		    (SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(interesting_thing,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		sub_class_bit_vector = ISVREF(ISVREF(interesting_thing,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Variable_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		pruned_interest_list = delete_eval_element_1(variable,
			ISVREF(interesting_thing,(SI_Long)36L));
		ISVREF(interesting_thing,(SI_Long)36L) = pruned_interest_list;
		if ( !TRUEP(pruned_interest_list) &&  
			!TRUEP(ISVREF(interesting_thing,(SI_Long)38L)))
		    withdraw_backward_chaining(interesting_thing);
	    }
	}
	goto next_loop_1;
      end_loop_1:;
	if (Backward_chaining_displays)
	    update_backward_chaining_displays_function(variable);
	if (interest_list) {
	    last_1 = interest_list;
	    next_qm = Nil;
	  next_loop_2:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop_2;
	    inline_note_reclaim_cons(last_1,Qeval);
	    last_1 = next_qm;
	    goto next_loop_2;
	  end_loop_2:
	    inline_note_reclaim_cons(last_1,Qeval);
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = interest_list;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = interest_list;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    M_CDR(last_1) = Nil;
	}
    }
    gensymed_symbol = Nil;
  next_loop_3:
    gensymed_symbol = ISVREF(variable,(SI_Long)30L);
    if (CAS_SVREF(variable,(SI_Long)30L,gensymed_symbol,Nil)) {
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
	goto end_2;
    }
    goto next_loop_3;
  end_loop_3:
  end_2:;
    if ( !((SI_Long)0L != (IFIX(ISVREF(variable,(SI_Long)5L)) & (SI_Long)32L)))
	ISVREF(variable,(SI_Long)29L) = Nil;
    return VALUES_1(Nil);
}

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qexecute_backward_chaining_for_rules;  /* execute-backward-chaining-for-rules */

/* RULE-INSTANCE-COMPLETED */
Object rule_instance_completed(variable,rule_instance)
    Object variable, rule_instance;
{
    Object pruned_interests, schedule_task_qm, old, new_1;
    Object def_structure_schedule_task_variable, temp_1, svref_arg_2;
    Object svref_new_value, task, ctask, p, v, q, structure_being_reclaimed;
    char temp, g2_p;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(153,86);
    pruned_interests = delete_eval_element_1(rule_instance,ISVREF(variable,
	    (SI_Long)35L));
    ISVREF(variable,(SI_Long)35L) = pruned_interests;
    if (Backward_chaining_displays)
	update_backward_chaining_displays_function(variable);
    if ( !TRUEP(pruned_interests)) {
	schedule_task_qm = ISVREF(variable,(SI_Long)37L);
	temp =  !(schedule_task_qm && (ISVREF(schedule_task_qm,
		(SI_Long)6L) || EQ(schedule_task_qm,Current_schedule_task)));
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	old = Nil;
	new_1 = Nil;
      next_loop:
	old = ISVREF(variable,(SI_Long)37L);
	def_structure_schedule_task_variable = 
		ISVREF(Chain_of_available_schedule_tasks_vector,
		IFIX(Current_thread_index));
	if (def_structure_schedule_task_variable) {
	    temp_1 = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = ISVREF(def_structure_schedule_task_variable,
		    (SI_Long)0L);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
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
	temp_1 = ISVREF(task,(SI_Long)1L);
	aref_new_value = -1.0;
	DFLOAT_ISASET_1(temp_1,(SI_Long)1L,aref_new_value);
	temp_1 = ISVREF(variable,(SI_Long)42L);
	SVREF(task,FIX((SI_Long)4L)) = temp_1;
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)10L)) = Nil;
	g2_p =  !TRUEP(Nil);
	SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
	temp_1 = ISVREF(task,(SI_Long)1L);
	aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
		Current_real_time,(SI_Long)0L);
	DFLOAT_ISASET_1(temp_1,(SI_Long)0L,aref_new_value);
	SVREF(task,FIX((SI_Long)7L)) = Qexecute_backward_chaining_for_rules;
	temp_1 = SYMBOL_FUNCTION(Qexecute_backward_chaining_for_rules);
	SVREF(task,FIX((SI_Long)8L)) = temp_1;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
	SVREF(task,FIX((SI_Long)13L)) = variable;
	new_1 = task;
	if (CAS_SVREF(variable,(SI_Long)37L,old,new_1)) {
	    task = new_1;
	    ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
	    if (ctask);
	    else
		ctask = System_is_running;
	    p = ISVREF(task,(SI_Long)4L);
	    v = ctask ? Current_task_queue_vector : Deferred_task_queue_vector;
	    q = ISVREF(v,IFIX(p));
	    SVREF(task,FIX((SI_Long)11L)) = q;
	    temp_1 = constant_queue_push_right(q,task);
	    SVREF(task,FIX((SI_Long)6L)) = temp_1;
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
	    temp_1 = ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    SVREF(new_1,FIX((SI_Long)0L)) = temp_1;
	    temp_1 = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = new_1;
	}
	goto next_loop;
      end_loop:
      end_1:;
    }
    return VALUES_1(Nil);
}

/* ADD-RULE-INSTANCE-TO-VARIABLE-INTERESTS */
Object add_rule_instance_to_variable_interests(variable,rule_instance)
    Object variable, rule_instance;
{
    Object new_value, old_value;

    x_note_fn_call(153,87);
    new_value = eval_cons_1(rule_instance,Nil);
    old_value = Nil;
  next_loop:
    old_value = ISVREF(variable,(SI_Long)35L);
    M_CDR(new_value) = old_value;
    if (CAS_SVREF(variable,(SI_Long)35L,old_value,new_value))
	goto end_loop;
    goto next_loop;
  end_loop:
    goto end_1;
  end_1:;
    if (Backward_chaining_displays)
	update_backward_chaining_displays_function(variable);
    return VALUES_1(Nil);
}

static Object Qnever;              /* never */

/* EXECUTE-BACKWARD-CHAINING-FOR-RULES */
Object execute_backward_chaining_for_rules(variable)
    Object variable;
{
    Object new_rules, current_computation_frame, gensymed_symbol;
    Object structure_being_reclaimed, temp, svref_arg_2;
    Object expiration_time_of_current_value;
    Declare_special(2);

    x_note_fn_call(153,88);
    new_rules = ISVREF(variable,(SI_Long)41L);
    current_computation_frame = variable;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    1);
      if ( !TRUEP(new_rules) &&  !TRUEP(ISVREF(variable,(SI_Long)35L))) {
	  ISVREF(variable,(SI_Long)42L) = Nil;
	  gensymed_symbol = Nil;
	next_loop:
	  gensymed_symbol = ISVREF(variable,(SI_Long)37L);
	  if (CAS_SVREF(variable,(SI_Long)37L,gensymed_symbol,Nil)) {
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
	  expiration_time_of_current_value = ISVREF(variable,(SI_Long)26L);
	  if ( !(EQ(expiration_time_of_current_value,Qnever) || 
		  FIXNUM_GE(expiration_time_of_current_value,Gensym_time)))
	      task_to_detect_failure(variable);
      }
      else if ((SI_Long)0L != (IFIX(ISVREF(variable,(SI_Long)4L)) & 
	      (SI_Long)8L))
	  execute_depth_first_backward_chain(variable);
      else
	  execute_breadth_first_backward_chain(variable);
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qbackward_chaining;  /* backward-chaining */

/* EXECUTE-BREADTH-FIRST-BACKWARD-CHAIN */
Object execute_breadth_first_backward_chain(variable)
    Object variable;
{
    Object link_list, link_entry, ab_loop_list_, link_1, focal_role_qm, rule;
    Object temp, temp_1, svref_arg_2, last_1, next_qm;

    x_note_fn_call(153,89);
    link_list = ISVREF(variable,(SI_Long)41L);
    link_entry = Nil;
    ab_loop_list_ = link_list;
    link_1 = Nil;
    focal_role_qm = Nil;
    rule = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    link_entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    link_1 = CAR(link_entry);
    focal_role_qm = ISVREF(link_1,(SI_Long)4L);
    rule = ISVREF(link_1,(SI_Long)2L);
    temp = ISVREF(rule,(SI_Long)8L);
    if ( !TRUEP(CAR(temp)) && ((SI_Long)0L != (IFIX(ISVREF(rule,
	    (SI_Long)5L)) & (SI_Long)1L) ||  !TRUEP(Inside_breakpoint_p) 
	    && (SI_Long)0L != (IFIX(ISVREF(rule,(SI_Long)4L)) & 
	    (SI_Long)16777216L) &&  !((SI_Long)0L != (IFIX(ISVREF(rule,
	    (SI_Long)4L)) & (SI_Long)8192L)))) {
	if ((IFIX(Tracing_message_level) > (SI_Long)1L || 
		IFIX(Breakpoint_level) > (SI_Long)1L) &&  
		!TRUEP(Debugging_reset) && ISVREF(Debugging_parameters,
		(SI_Long)22L))
	    write_backward_chaining_trace_message(variable,link_1,
		    CDR(link_entry),Nil);
	if (focal_role_qm)
	    generate_and_schedule_rule_instances(rule,focal_role_qm,
		    ISVREF(link_1,(SI_Long)5L),CDR(link_entry),
		    Qbackward_chaining,variable,ISVREF(variable,
		    (SI_Long)42L),Nil);
	else
	    generate_and_schedule_rule_instances(rule,Nil,Nil,Nil,
		    Qbackward_chaining,variable,ISVREF(variable,
		    (SI_Long)42L),Nil);
    }
    inline_note_reclaim_cons(link_entry,Qeval);
    if (ISVREF(Available_eval_conses_tail_vector,IFIX(Current_thread_index))) {
	temp_1 = ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp_1) = link_entry;
	temp_1 = Available_eval_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp_1,svref_arg_2) = link_entry;
    }
    else {
	temp_1 = Available_eval_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp_1,svref_arg_2) = link_entry;
	temp_1 = Available_eval_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp_1,svref_arg_2) = link_entry;
    }
    M_CDR(link_entry) = Nil;
    goto next_loop;
  end_loop:
    if (link_list) {
	last_1 = link_list;
	next_qm = Nil;
      next_loop_1:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop_1;
	inline_note_reclaim_cons(last_1,Qeval);
	last_1 = next_qm;
	goto next_loop_1;
      end_loop_1:
	inline_note_reclaim_cons(last_1,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_1 = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_1) = link_list;
	    temp_1 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = last_1;
	}
	else {
	    temp_1 = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = link_list;
	    temp_1 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    ISVREF(variable,(SI_Long)41L) = Nil;
    if ( !TRUEP(ISVREF(variable,(SI_Long)35L))) {
	ISVREF(variable,(SI_Long)42L) = Nil;
	task_to_detect_failure(variable);
    }
    return VALUES_1(Qnil);
}

/* EXECUTE-DEPTH-FIRST-BACKWARD-CHAIN */
Object execute_depth_first_backward_chain(variable)
    Object variable;
{
    Object link_list, link_entry, link_1, focal_role_qm, rule;
    Object rest_of_links_qm, temp, temp_1, svref_arg_2;

    x_note_fn_call(153,90);
    if ( !TRUEP(ISVREF(variable,(SI_Long)35L))) {
	link_list = ISVREF(variable,(SI_Long)41L);
	link_entry = Nil;
	link_1 = Nil;
	focal_role_qm = Nil;
	rule = Nil;
	rest_of_links_qm = Nil;
      next_loop:
	if ( !TRUEP(link_list))
	    goto end_loop;
	link_entry = CAR(link_list);
	link_1 = CAR(link_entry);
	focal_role_qm = ISVREF(link_1,(SI_Long)4L);
	rule = ISVREF(link_1,(SI_Long)2L);
	rest_of_links_qm = CDR(link_list);
	temp = ISVREF(rule,(SI_Long)8L);
	if ( !TRUEP(CAR(temp)) && ((SI_Long)0L != (IFIX(ISVREF(rule,
		(SI_Long)5L)) & (SI_Long)1L) ||  
		!TRUEP(Inside_breakpoint_p) && (SI_Long)0L != 
		(IFIX(ISVREF(rule,(SI_Long)4L)) & (SI_Long)16777216L) &&  
		!((SI_Long)0L != (IFIX(ISVREF(rule,(SI_Long)4L)) & 
		(SI_Long)8192L)))) {
	    if ((IFIX(Tracing_message_level) > (SI_Long)1L || 
		    IFIX(Breakpoint_level) > (SI_Long)1L) &&  
		    !TRUEP(Debugging_reset) && ISVREF(Debugging_parameters,
		    (SI_Long)22L))
		write_backward_chaining_trace_message(variable,link_1,
			CDR(link_entry),T);
	    if (focal_role_qm)
		generate_and_schedule_rule_instances(rule,focal_role_qm,
			ISVREF(link_1,(SI_Long)5L),CDR(link_entry),
			Qbackward_chaining,variable,ISVREF(variable,
			(SI_Long)42L),Nil);
	    else
		generate_and_schedule_rule_instances(rule,Nil,Nil,Nil,
			Qbackward_chaining,variable,ISVREF(variable,
			(SI_Long)42L),Nil);
	}
	inline_note_reclaim_cons(link_list,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_1 = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_1) = link_list;
	    temp_1 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = link_list;
	}
	else {
	    temp_1 = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = link_list;
	    temp_1 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = link_list;
	}
	M_CDR(link_list) = Nil;
	inline_note_reclaim_cons(link_entry,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_1 = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_1) = link_entry;
	    temp_1 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = link_entry;
	}
	else {
	    temp_1 = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = link_entry;
	    temp_1 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = link_entry;
	}
	M_CDR(link_entry) = Nil;
	if (ISVREF(variable,(SI_Long)35L))
	    goto end_loop;
	if ( !TRUEP(rest_of_links_qm))
	    goto end_loop;
	link_list = rest_of_links_qm;
	goto next_loop;
      end_loop:
	ISVREF(variable,(SI_Long)41L) = rest_of_links_qm;
	if ( !TRUEP(ISVREF(variable,(SI_Long)35L))) {
	    ISVREF(variable,(SI_Long)42L) = Nil;
	    task_to_detect_failure(variable);
	}
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_8;   /* "depth first" */

static Object string_constant_9;   /* "breadth first" */

static Object string_constant_10;  /* "Scheduling ~NF for execution at priority ~a with ~NF as the ~a ~a ~?
				    *                while ~a backward chaining for the value of ~NF."
				    */

static Object string_constant_11;  /* "Scheduling ~NF for execution at priority ~a with ~NF as the ~a ~?
				    *                while ~a backward chaining for the value of ~NF."
				    */

static Object string_constant_12;  /* "Scheduling ~NF for execution at priority ~a while ~a ~?
				    *            backward chaining for the value of ~NF."
				    */

/* WRITE-BACKWARD-CHAINING-TRACE-MESSAGE */
Object write_backward_chaining_trace_message(variable,link_1,object_qm,
	    depth_first_qm)
    Object variable, link_1, object_qm, depth_first_qm;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object rule, focal_role_qm, local_name_qm, priority, chain_type;
    Object gensymed_symbol;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(153,91);
    if ((IFIX(Tracing_message_level) > (SI_Long)1L || 
	    IFIX(Breakpoint_level) > (SI_Long)1L) &&  
	    !TRUEP(Debugging_reset) && ISVREF(Debugging_parameters,
	    (SI_Long)22L)) {
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
		  rule = ISVREF(link_1,(SI_Long)2L);
		  focal_role_qm = ISVREF(link_1,(SI_Long)4L);
		  local_name_qm = ISVREF(link_1,(SI_Long)5L);
		  priority = ISVREF(variable,(SI_Long)42L);
		  chain_type = depth_first_qm ? string_constant_8 : 
			  string_constant_9;
		  if (focal_role_qm) {
		      if (local_name_qm)
			  tformat(8,string_constant_10,rule,priority,
				  object_qm,focal_role_qm,local_name_qm,
				  chain_type,variable);
		      else
			  tformat(7,string_constant_11,rule,priority,
				  object_qm,focal_role_qm,chain_type,variable);
		  }
		  else
		      tformat(5,string_constant_12,rule,priority,
			      chain_type,variable);
		  gensymed_symbol = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return write_major_trace_message_function(gensymed_symbol);
    }
    else
	return VALUES_1(Nil);
}

/* COLLECT-RULES-FOR-BACKWARD-CHAINING */
Object collect_rules_for_backward_chaining(variable,data_type)
    Object variable, data_type;
{
    Object name_or_names_for_variable_qm, variable_name_cons_qm, parent_stack;
    Object gensymed_symbol, temp, possible_values_qm, parent_stack_entry;
    Object symbolic_value_qm, link_1, list_1, ab_loop_list_, parent_frame_qm;
    Object name_for_parent, ab_loop_list__1, name_for_variable, temp_2;
    Object svref_arg_2;
    char temp_1;

    x_note_fn_call(153,92);
    name_or_names_for_variable_qm = 
	    get_lookup_slot_value_given_default(variable,
	    Qname_or_names_for_frame,Nil);
    if (name_or_names_for_variable_qm && 
	    SYMBOLP(name_or_names_for_variable_qm)) {
	name_or_names_for_variable_qm = 
		eval_cons_1(name_or_names_for_variable_qm,Nil);
	variable_name_cons_qm = name_or_names_for_variable_qm;
    }
    else
	variable_name_cons_qm = Nil;
    parent_stack = make_parent_stack(variable);
    if (EQ(data_type,Qsymbol) && parent_stack) {
	gensymed_symbol = M_CAR(M_CDR(CAR(parent_stack)));
	temp = CONSP(gensymed_symbol) ? M_CAR(gensymed_symbol) : 
		gensymed_symbol;
	gensymed_symbol = M_CAR(M_CDR(CAR(parent_stack)));
	possible_values_qm = value_set_given_attribute_and_class(temp,
		CONSP(gensymed_symbol) ? M_CDR(gensymed_symbol) : 
		ISVREF(ISVREF(M_CAR(CAR(parent_stack)),(SI_Long)1L),
		(SI_Long)1L));
    }
    else
	possible_values_qm = Nil;
    if (parent_stack) {
	parent_stack_entry = M_CAR(parent_stack);
	if (EQ(data_type,Qsymbol))
	    invoke_backward_chaining_for_symbolic_class_references(M_CAR(parent_stack_entry),
		    possible_values_qm,T);
	symbolic_value_qm = Nil;
	link_1 = Nil;
	gensymed_symbol = M_CAR(M_CDR(parent_stack_entry));
	gensymed_symbol = CONSP(gensymed_symbol) ? M_CAR(gensymed_symbol) :
		 gensymed_symbol;
	list_1 = INLINE_SYMBOL_PLIST(gensymed_symbol);
      next_loop:
	if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
		Current_kb_specific_property_list_property_name))
	    goto end_loop;
	list_1 = M_CDR(M_CDR(list_1));
	goto next_loop;
      end_loop:
	list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
      next_loop_1:
	if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Backward_chaining_list_kbprop))
	    goto end_loop_1;
	list_1 = M_CDR(M_CDR(list_1));
	goto next_loop_1;
      end_loop_1:
	ab_loop_list_ = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	link_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp_1 =  !EQ(data_type,Qsymbol);
	if (temp_1);
	else {
	    symbolic_value_qm = ISVREF(link_1,(SI_Long)6L);
	    temp_1 =  !TRUEP(symbolic_value_qm);
	    if (temp_1);
	    else
		temp_1 =  !TRUEP(possible_values_qm);
	    if (temp_1);
	    else
		temp_1 = TRUEP(memq_function(symbolic_value_qm,
			possible_values_qm));
	}
	if (temp_1) {
	    parent_frame_qm = find_referenced_parent(parent_stack,
		    ISVREF(link_1,(SI_Long)3L));
	    if (parent_frame_qm)
		add_tuple_to_backward_link_list(link_1,parent_frame_qm);
	}
	goto next_loop_2;
      end_loop_2:;
	if (EQ(data_type,Qsymbol)) {
	    name_for_parent = Nil;
	    ab_loop_list_ = M_CAR(M_CDR(M_CDR(parent_stack_entry)));
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_3;
	    name_for_parent = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    link_1 = Nil;
	    list_1 = INLINE_SYMBOL_PLIST(name_for_parent);
	  next_loop_4:
	    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
		    Current_kb_specific_property_list_property_name))
		goto end_loop_4;
	    list_1 = M_CDR(M_CDR(list_1));
	    goto next_loop_4;
	  end_loop_4:
	    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
	  next_loop_5:
	    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
		    Backward_chaining_list_kbprop))
		goto end_loop_5;
	    list_1 = M_CDR(M_CDR(list_1));
	    goto next_loop_5;
	  end_loop_5:
	    ab_loop_list__1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
	    symbolic_value_qm = Nil;
	  next_loop_6:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_6;
	    link_1 = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    symbolic_value_qm = ISVREF(link_1,(SI_Long)6L);
	    if (EQ(name_for_parent,ISVREF(link_1,(SI_Long)3L)) && 
		    symbolic_value_qm && ( !TRUEP(possible_values_qm) || 
		    memq_function(symbolic_value_qm,possible_values_qm)))
		add_tuple_to_backward_link_list(link_1,Nil);
	    goto next_loop_6;
	  end_loop_6:;
	    goto next_loop_3;
	  end_loop_3:;
	}
    }
    if (EQ(data_type,Qsymbol))
	invoke_backward_chaining_for_symbolic_class_references(variable,
		possible_values_qm,Nil);
    else
	invoke_backward_chaining_for_class_references(variable);
    name_for_variable = Nil;
    ab_loop_list_ = name_or_names_for_variable_qm;
  next_loop_7:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_7;
    name_for_variable = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    link_1 = Nil;
    list_1 = INLINE_SYMBOL_PLIST(name_for_variable);
  next_loop_8:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop_8;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_8;
  end_loop_8:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_9:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Backward_chaining_list_kbprop))
	goto end_loop_9;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_9;
  end_loop_9:
    ab_loop_list__1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    symbolic_value_qm = Nil;
  next_loop_10:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_10;
    link_1 = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if (EQ(name_for_variable,ISVREF(link_1,(SI_Long)3L))) {
	temp_1 =  !EQ(data_type,Qsymbol);
	if (temp_1);
	else {
	    symbolic_value_qm = ISVREF(link_1,(SI_Long)6L);
	    temp_1 =  !TRUEP(symbolic_value_qm);
	    if (temp_1);
	    else
		temp_1 =  !TRUEP(possible_values_qm);
	    if (temp_1);
	    else
		temp_1 = TRUEP(memq_function(symbolic_value_qm,
			possible_values_qm));
	}
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	add_tuple_to_backward_link_list(link_1,Nil);
    goto next_loop_10;
  end_loop_10:;
    goto next_loop_7;
  end_loop_7:;
    if (variable_name_cons_qm) {
	inline_note_reclaim_cons(variable_name_cons_qm,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_2 = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_2) = variable_name_cons_qm;
	    temp_2 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = variable_name_cons_qm;
	}
	else {
	    temp_2 = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = variable_name_cons_qm;
	    temp_2 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = variable_name_cons_qm;
	}
	M_CDR(variable_name_cons_qm) = Nil;
    }
    return reclaim_parent_stack(parent_stack);
}

static Object Qkb_workspace;       /* kb-workspace */

static Object Qrule;               /* rule */

/* INVOKE-RULES-FOR-MOVEMENT-CHAINING */
Object invoke_rules_for_movement_chaining varargs_1(int, n)
{
    Object object, mover;
    Object do_not_notify_ws_representations_p, x2;
    Object current_computation_frame_previously_bound_qm, links_and_objects;
    Object link_entry, ab_loop_list_, link_1, recipient, sub_class_bit_vector;
    Object temp_1, role_qm, local_name_qm, chain_object, gensymed_symbol_3;
    Object temp_2, temp_3, last_1, next_qm, svref_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(153,93);
    INIT_ARGS_nonrelocating();
    object = REQUIRED_ARG_nonrelocating();
    mover = REQUIRED_ARG_nonrelocating();
    do_not_notify_ws_representations_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(do_not_notify_ws_representations_p) && 
	    G2_has_v5_mode_windows_p &&  
	    !TRUEP(Ws_protocol_handle_moves_from_edge_change_p))
	send_ws_representations_item_moved(object,FIX((SI_Long)0L),
		FIX((SI_Long)0L));
    if (SIMPLE_VECTOR_P(Current_computation_frame) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_computation_frame)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(Current_computation_frame,
	    (SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(Current_computation_frame,(SI_Long)1L);
	current_computation_frame_previously_bound_qm = 
		SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	current_computation_frame_previously_bound_qm = Nil;
    links_and_objects = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Links_and_objects,Qlinks_and_objects,links_and_objects,
	    0);
      if ( !TRUEP(current_computation_frame_previously_bound_qm))
	  Current_computation_frame = object;
      collect_rules_for_movement_chaining(object,mover);
      link_entry = Nil;
      ab_loop_list_ = Links_and_objects;
      link_1 = Nil;
      recipient = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      link_entry = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      link_1 = CAR(link_entry);
      recipient = ISVREF(link_1,(SI_Long)2L);
      sub_class_bit_vector = ISVREF(ISVREF(recipient,(SI_Long)1L),
	      (SI_Long)19L);
      superior_class_bit_number = 
	      IFIX(ISVREF(True_value_update_recipient_class_description,
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
      if ( !temp) {
	  temp_1 = ISVREF(recipient,(SI_Long)8L);
	  temp =  !TRUEP(CAR(temp_1)) ? (SI_Long)0L != 
		  (IFIX(ISVREF(recipient,(SI_Long)5L)) & (SI_Long)1L) ||  
		  !TRUEP(Inside_breakpoint_p) && (SI_Long)0L != 
		  (IFIX(ISVREF(recipient,(SI_Long)4L)) & 
		  (SI_Long)16777216L) &&  !((SI_Long)0L != 
		  (IFIX(ISVREF(recipient,(SI_Long)4L)) & (SI_Long)8192L)) :
		   TRUEP(Nil);
      }
      else
	  temp = TRUEP(Nil);
      if (temp) {
	  role_qm = ISVREF(link_1,(SI_Long)4L);
	  local_name_qm = role_qm ? ISVREF(link_1,(SI_Long)5L) : Nil;
	  chain_object = role_qm ? CDR(link_entry) : Nil;
	  if (EQ(role_qm,Qkb_workspace)) {
	      if ((SI_Long)0L != (IFIX(ISVREF(recipient,(SI_Long)4L)) & 
		      (SI_Long)67108864L)) {
		  gensymed_symbol_3 = ACCESS_ONCE(ISVREF(recipient,
			  (SI_Long)14L));
		  gensymed_symbol_3 = gensymed_symbol_3 ? 
			  ACCESS_ONCE(ISVREF(gensymed_symbol_3,
			  (SI_Long)5L)) : Nil;
		  temp_1 = EQ(get_workspace_if_any(gensymed_symbol_3),
			  chain_object) ? T : Nil;
	      }
	      else
		  temp_1 = T;
	  }
	  else if (EQ(role_qm,Qrule))
	      temp_1 = (SI_Long)0L != (IFIX(ISVREF(recipient,(SI_Long)4L)) 
		      & (SI_Long)67108864L) ? (EQ(recipient,chain_object) ?
		       T : Nil) : T;
	  else if (EQ(role_qm,Qitem)) {
	      sub_class_bit_vector = ISVREF(ISVREF(chain_object,
		      (SI_Long)1L),(SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
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
	      temp_1 =  !temp ? T : Nil;
	  }
	  else
	      temp_1 = T;
	  if (temp_1) {
	      write_major_movement_chaining_trace_message(object,
		      chain_object,recipient,role_qm,mover);
	      generate_and_schedule_rule_instances(recipient,role_qm,
		      local_name_qm,chain_object,Qforward_chaining,Nil,
		      ISVREF(recipient,(SI_Long)26L),Nil);
	  }
      }
      inline_note_reclaim_cons(link_entry,Qeval);
      if (ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	  temp_2 = ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index));
	  M_CDR(temp_2) = link_entry;
	  temp_2 = Available_eval_conses_tail_vector;
	  temp_3 = Current_thread_index;
	  SVREF(temp_2,temp_3) = link_entry;
      }
      else {
	  temp_2 = Available_eval_conses_vector;
	  temp_3 = Current_thread_index;
	  SVREF(temp_2,temp_3) = link_entry;
	  temp_2 = Available_eval_conses_tail_vector;
	  temp_3 = Current_thread_index;
	  SVREF(temp_2,temp_3) = link_entry;
      }
      M_CDR(link_entry) = Nil;
      goto next_loop;
    end_loop:;
      if ( !TRUEP(current_computation_frame_previously_bound_qm))
	  Current_computation_frame = Nil;
      if (Links_and_objects) {
	  last_1 = Links_and_objects;
	  next_qm = Nil;
	next_loop_1:
	  next_qm = M_CDR(last_1);
	  if ( !TRUEP(next_qm))
	      goto end_loop_1;
	  inline_note_reclaim_cons(last_1,Qeval);
	  last_1 = next_qm;
	  goto next_loop_1;
	end_loop_1:
	  inline_note_reclaim_cons(last_1,Qeval);
	  if (ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	      temp_2 = ISVREF(Available_eval_conses_tail_vector,
		      IFIX(Current_thread_index));
	      temp_3 = Links_and_objects;
	      M_CDR(temp_2) = temp_3;
	      temp_2 = Available_eval_conses_tail_vector;
	      temp_3 = Current_thread_index;
	      SVREF(temp_2,temp_3) = last_1;
	  }
	  else {
	      temp_2 = Available_eval_conses_vector;
	      temp_3 = Current_thread_index;
	      svref_new_value = Links_and_objects;
	      SVREF(temp_2,temp_3) = svref_new_value;
	      temp_2 = Available_eval_conses_tail_vector;
	      temp_3 = Current_thread_index;
	      SVREF(temp_2,temp_3) = last_1;
	  }
	  M_CDR(last_1) = Nil;
	  result = VALUES_1(Nil);
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object string_constant_13;  /* "the user" */

static Object string_constant_14;  /* "Scheduling event chaining to ~nf with ~nf as ~a because ~nf was moved by ~nf." */

static Object string_constant_15;  /* "Scheduling event chaining to ~NF because ~NF was moved by ~NF." */

/* WRITE-MAJOR-MOVEMENT-CHAINING-TRACE-MESSAGE */
Object write_major_movement_chaining_trace_message(object,chain_object,
	    recipient,role_qm,mover)
    Object object, chain_object, recipient, role_qm, mover;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, gensymed_symbol;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(153,94);
    if ((IFIX(Tracing_message_level) > (SI_Long)1L || 
	    IFIX(Breakpoint_level) > (SI_Long)1L) &&  
	    !TRUEP(Debugging_reset) && ISVREF(Debugging_parameters,
	    (SI_Long)22L)) {
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
		  if (role_qm) {
		      if (EQ(mover,Qis_moved_by_the_user))
			  temp = string_constant_13;
		      else if (EQ(mover,Qis_moved_by_g2))
			  temp = Current_computation_frame;
		      else
			  temp = Qnil;
		      tformat(6,string_constant_14,recipient,chain_object,
			      role_qm,object,temp);
		  }
		  else {
		      if (EQ(mover,Qis_moved_by_the_user))
			  temp = string_constant_13;
		      else if (EQ(mover,Qis_moved_by_g2))
			  temp = Current_computation_frame;
		      else
			  temp = Qnil;
		      tformat(4,string_constant_15,recipient,object,temp);
		  }
		  gensymed_symbol = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return write_major_trace_message_function(gensymed_symbol);
    }
    else
	return VALUES_1(Nil);
}

/* COLLECT-RULES-FOR-MOVEMENT-CHAINING */
Object collect_rules_for_movement_chaining(object,mover)
    Object object, mover;
{
    Object object_names_qm, object_name_cons_qm, parent_stack, object_name;
    Object ab_loop_list_, link_1, list_1, ab_loop_list__1, stored_sense;
    Object new_cons, temp, svref_arg_2, svref_new_value, gensymed_symbol;
    Object new_value, old_value, parent_stack_entry, parent_frame_qm;
    Object class_description, classes, cache_qm, class_1, specific_list;
    Object designation, temp_1;
    char temp_2;

    x_note_fn_call(153,95);
    object_names_qm = get_lookup_slot_value_given_default(object,
	    Qname_or_names_for_frame,Nil);
    if (object_names_qm && SYMBOLP(object_names_qm)) {
	object_names_qm = eval_cons_1(object_names_qm,Nil);
	object_name_cons_qm = object_names_qm;
    }
    else
	object_name_cons_qm = Nil;
    parent_stack = make_parent_stack(object);
    object_name = Nil;
    ab_loop_list_ = object_names_qm;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    object_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    link_1 = Nil;
    list_1 = INLINE_SYMBOL_PLIST(object_name);
  next_loop_1:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop_1;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_1;
  end_loop_1:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_2:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Forward_chaining_list_kbprop))
	goto end_loop_2;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_2;
  end_loop_2:
    ab_loop_list__1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    stored_sense = Nil;
  next_loop_3:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_3;
    link_1 = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    stored_sense = ISVREF(link_1,(SI_Long)7L);
    if ((EQ(stored_sense,Qis_moved) || EQ(stored_sense,mover)) && 
	    EQ(object_name,ISVREF(link_1,(SI_Long)3L))) {
	new_cons = ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_eval_cons_pool();
	M_CAR(gensymed_symbol) = link_1;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qeval);
	new_value = eval_cons_1(gensymed_symbol,Nil);
	old_value = Nil;
      next_loop_4:
	old_value = Links_and_objects;
	M_CDR(new_value) = old_value;
	if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value))
	    goto end_loop_4;
	goto next_loop_4;
      end_loop_4:
	goto end_1;
      end_1:;
    }
    goto next_loop_3;
  end_loop_3:;
    goto next_loop;
  end_loop:;
    if (parent_stack) {
	parent_stack_entry = M_CAR(parent_stack);
	link_1 = Nil;
	gensymed_symbol = M_CAR(M_CDR(parent_stack_entry));
	gensymed_symbol = CONSP(gensymed_symbol) ? M_CAR(gensymed_symbol) :
		 gensymed_symbol;
	list_1 = INLINE_SYMBOL_PLIST(gensymed_symbol);
      next_loop_5:
	if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
		Current_kb_specific_property_list_property_name))
	    goto end_loop_5;
	list_1 = M_CDR(M_CDR(list_1));
	goto next_loop_5;
      end_loop_5:
	list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
      next_loop_6:
	if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Forward_chaining_list_kbprop))
	    goto end_loop_6;
	list_1 = M_CDR(M_CDR(list_1));
	goto next_loop_6;
      end_loop_6:
	ab_loop_list_ = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
	stored_sense = Nil;
      next_loop_7:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_7;
	link_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	stored_sense = ISVREF(link_1,(SI_Long)7L);
	if (EQ(stored_sense,Qis_moved) || EQ(stored_sense,mover)) {
	    parent_frame_qm = find_referenced_parent(parent_stack,
		    ISVREF(link_1,(SI_Long)3L));
	    if (parent_frame_qm) {
		new_cons = ISVREF(Available_eval_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    temp = Available_eval_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(temp,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
			    IFIX(Current_thread_index)))) {
			temp = Available_eval_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = Nil;
		    }
		    gensymed_symbol = new_cons;
		}
		else
		    gensymed_symbol = Nil;
		if ( !TRUEP(gensymed_symbol))
		    gensymed_symbol = replenish_eval_cons_pool();
		M_CAR(gensymed_symbol) = link_1;
		M_CDR(gensymed_symbol) = parent_frame_qm;
		inline_note_allocate_cons(gensymed_symbol,Qeval);
		new_value = eval_cons_1(gensymed_symbol,Nil);
		old_value = Nil;
	      next_loop_8:
		old_value = Links_and_objects;
		M_CDR(new_value) = old_value;
		if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value))
		    goto end_loop_8;
		goto next_loop_8;
	      end_loop_8:
		goto end_2;
	      end_2:;
	    }
	}
	goto next_loop_7;
      end_loop_7:;
    }
    link_1 = Nil;
    class_description = ISVREF(object,(SI_Long)1L);
    classes = ISVREF(class_description,(SI_Long)2L);
    gensymed_symbol = M_CAR(classes);
    list_1 = INLINE_SYMBOL_PLIST(gensymed_symbol);
  next_loop_9:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop_9;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_9;
  end_loop_9:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_10:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Cached_class_forward_chaining_list_kbprop))
	goto end_loop_10;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_10;
  end_loop_10:
    cache_qm = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    if (cache_qm)
	ab_loop_list_ = M_CDR(cache_qm);
    else {
	class_1 = Nil;
	ab_loop_list_ = classes;
	specific_list = Nil;
      next_loop_11:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_11;
	class_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	specific_list = lookup_kb_specific_property_value(class_1,
		Forward_chaining_list_kbprop);
	if (specific_list) {
	    specific_list = copy_list_using_eval_conses_1(specific_list);
	    if (cache_qm)
		cache_qm = nconc2(cache_qm,specific_list);
	    else
		cache_qm = specific_list;
	}
	if (EQ(class_1,Qitem))
	    goto end_loop_11;
	goto next_loop_11;
      end_loop_11:
	mutate_kb_specific_property_value(M_CAR(classes),eval_cons_1(Nil,
		cache_qm),Cached_class_forward_chaining_list_kbprop);
	new_value = eval_cons_1(M_CAR(classes),Nil);
	old_value = Nil;
      next_loop_12:
	old_value = Cached_classes_for_forward_chaining;
	M_CDR(new_value) = old_value;
	if (CAS_SYMBOL(Qcached_classes_for_forward_chaining,old_value,
		new_value))
	    goto end_loop_12;
	goto next_loop_12;
      end_loop_12:
	goto end_3;
      end_3:;
	ab_loop_list_ = cache_qm;
	goto end_4;
	ab_loop_list_ = Qnil;
      end_4:;
    }
    stored_sense = Nil;
    designation = Nil;
  next_loop_13:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_13;
    link_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    stored_sense = ISVREF(link_1,(SI_Long)7L);
    designation = ISVREF(link_1,(SI_Long)3L);
    if ((EQ(stored_sense,Qis_moved) || EQ(stored_sense,mover)) &&  
	    !SYMBOLP(designation)) {
	if (domain_of_designation(designation)) {
	    temp_1 = role_of_designation(designation);
	    temp_2 = SYMBOLP(temp_1);
	}
	else
	    temp_2 = TRUEP(Nil);
	temp_2 =  !temp_2;
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	new_cons = ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_eval_cons_pool();
	M_CAR(gensymed_symbol) = link_1;
	M_CDR(gensymed_symbol) = object;
	inline_note_allocate_cons(gensymed_symbol,Qeval);
	new_value = eval_cons_1(gensymed_symbol,Nil);
	old_value = Nil;
      next_loop_14:
	old_value = Links_and_objects;
	M_CDR(new_value) = old_value;
	if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value))
	    goto end_loop_14;
	goto next_loop_14;
      end_loop_14:
	goto end_5;
      end_5:;
    }
    goto next_loop_13;
  end_loop_13:;
    if (object_name_cons_qm) {
	inline_note_reclaim_cons(object_name_cons_qm,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = object_name_cons_qm;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = object_name_cons_qm;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = object_name_cons_qm;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = object_name_cons_qm;
	}
	M_CDR(object_name_cons_qm) = Nil;
    }
    return reclaim_parent_stack(parent_stack);
}

/* INVOKE-RULES-FOR-USER-ICON-MOVEMENT-IF-NECESSARY */
Object invoke_rules_for_user_icon_movement_if_necessary(block)
    Object block;
{
    Object current_computation_frame;
    Declare_special(1);
    Object result;

    x_note_fn_call(153,96);
    if (ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)16L)) {
	current_computation_frame = ISVREF(Current_workstation,(SI_Long)25L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		0);
	  if ( !TRUEP(Current_computation_frame))
	      Current_computation_frame = block;
	  result = invoke_rules_for_movement_chaining(2,block,
		  Qis_moved_by_the_user);
	POP_SPECIAL();
	return result;
    }
    else if (G2_has_v5_mode_windows_p &&  
	    !TRUEP(Ws_protocol_handle_moves_from_edge_change_p))
	return send_ws_representations_item_moved(block,FIX((SI_Long)0L),
		FIX((SI_Long)0L));
    else
	return VALUES_1(Qnil);
}

/* INVOKE-RULES-FOR-EXISTENTIAL-CHAINING */
Object invoke_rules_for_existential_chaining(object,key_sense,
	    precomputed_links_and_objects)
    Object object, key_sense, precomputed_links_and_objects;
{
    Object x2, current_computation_frame_previously_bound_qm;
    Object links_and_objects, link_entry, ab_loop_list_, link_1, recipient;
    Object sub_class_bit_vector, temp_1, role_qm, local_name_qm, chain_object;
    Object gensymed_symbol_3, temp_2, temp_3, last_1, next_qm, svref_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(1);

    x_note_fn_call(153,97);
    if (SIMPLE_VECTOR_P(Current_computation_frame) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_computation_frame)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(Current_computation_frame,
	    (SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(Current_computation_frame,(SI_Long)1L);
	current_computation_frame_previously_bound_qm = 
		SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	current_computation_frame_previously_bound_qm = Nil;
    links_and_objects = precomputed_links_and_objects;
    PUSH_SPECIAL_WITH_SYMBOL(Links_and_objects,Qlinks_and_objects,links_and_objects,
	    0);
      if ( !TRUEP(current_computation_frame_previously_bound_qm))
	  Current_computation_frame = object;
      if ( !TRUEP(precomputed_links_and_objects))
	  collect_rules_for_existential_chaining(object,key_sense);
      link_entry = Nil;
      ab_loop_list_ = Links_and_objects;
      link_1 = Nil;
      recipient = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      link_entry = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      link_1 = CAR(link_entry);
      recipient = ISVREF(link_1,(SI_Long)2L);
      sub_class_bit_vector = ISVREF(ISVREF(recipient,(SI_Long)1L),
	      (SI_Long)19L);
      superior_class_bit_number = 
	      IFIX(ISVREF(True_value_update_recipient_class_description,
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
      if ( !temp) {
	  temp_1 = ISVREF(recipient,(SI_Long)8L);
	  temp =  !TRUEP(CAR(temp_1)) ? (SI_Long)0L != 
		  (IFIX(ISVREF(recipient,(SI_Long)5L)) & (SI_Long)1L) ||  
		  !TRUEP(Inside_breakpoint_p) && (SI_Long)0L != 
		  (IFIX(ISVREF(recipient,(SI_Long)4L)) & 
		  (SI_Long)16777216L) &&  !((SI_Long)0L != 
		  (IFIX(ISVREF(recipient,(SI_Long)4L)) & (SI_Long)8192L)) :
		   TRUEP(Nil);
      }
      else
	  temp = TRUEP(Nil);
      if (temp) {
	  role_qm = ISVREF(link_1,(SI_Long)4L);
	  local_name_qm = role_qm ? ISVREF(link_1,(SI_Long)5L) : Nil;
	  chain_object = role_qm ? CDR(link_entry) : Nil;
	  if (EQ(role_qm,Qkb_workspace)) {
	      if ((SI_Long)0L != (IFIX(ISVREF(recipient,(SI_Long)4L)) & 
		      (SI_Long)67108864L)) {
		  gensymed_symbol_3 = ACCESS_ONCE(ISVREF(recipient,
			  (SI_Long)14L));
		  gensymed_symbol_3 = gensymed_symbol_3 ? 
			  ACCESS_ONCE(ISVREF(gensymed_symbol_3,
			  (SI_Long)5L)) : Nil;
		  temp_1 = EQ(get_workspace_if_any(gensymed_symbol_3),
			  chain_object) ? T : Nil;
	      }
	      else
		  temp_1 = T;
	  }
	  else if (EQ(role_qm,Qrule))
	      temp_1 = (SI_Long)0L != (IFIX(ISVREF(recipient,(SI_Long)4L)) 
		      & (SI_Long)67108864L) ? (EQ(recipient,chain_object) ?
		       T : Nil) : T;
	  else if (EQ(role_qm,Qitem)) {
	      sub_class_bit_vector = ISVREF(ISVREF(chain_object,
		      (SI_Long)1L),(SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
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
	      temp_1 =  !temp ? T : Nil;
	  }
	  else
	      temp_1 = T;
	  if (temp_1) {
	      write_major_existential_chaining_trace_message(object,
		      chain_object,recipient,role_qm,key_sense);
	      generate_and_schedule_rule_instances(recipient,role_qm,
		      local_name_qm,chain_object,Qforward_chaining,Nil,
		      ISVREF(recipient,(SI_Long)26L),Nil);
	  }
      }
      inline_note_reclaim_cons(link_entry,Qeval);
      if (ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	  temp_2 = ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index));
	  M_CDR(temp_2) = link_entry;
	  temp_2 = Available_eval_conses_tail_vector;
	  temp_3 = Current_thread_index;
	  SVREF(temp_2,temp_3) = link_entry;
      }
      else {
	  temp_2 = Available_eval_conses_vector;
	  temp_3 = Current_thread_index;
	  SVREF(temp_2,temp_3) = link_entry;
	  temp_2 = Available_eval_conses_tail_vector;
	  temp_3 = Current_thread_index;
	  SVREF(temp_2,temp_3) = link_entry;
      }
      M_CDR(link_entry) = Nil;
      goto next_loop;
    end_loop:;
      if ( !TRUEP(current_computation_frame_previously_bound_qm))
	  Current_computation_frame = Nil;
      if (Links_and_objects) {
	  last_1 = Links_and_objects;
	  next_qm = Nil;
	next_loop_1:
	  next_qm = M_CDR(last_1);
	  if ( !TRUEP(next_qm))
	      goto end_loop_1;
	  inline_note_reclaim_cons(last_1,Qeval);
	  last_1 = next_qm;
	  goto next_loop_1;
	end_loop_1:
	  inline_note_reclaim_cons(last_1,Qeval);
	  if (ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	      temp_2 = ISVREF(Available_eval_conses_tail_vector,
		      IFIX(Current_thread_index));
	      temp_3 = Links_and_objects;
	      M_CDR(temp_2) = temp_3;
	      temp_2 = Available_eval_conses_tail_vector;
	      temp_3 = Current_thread_index;
	      SVREF(temp_2,temp_3) = last_1;
	  }
	  else {
	      temp_2 = Available_eval_conses_vector;
	      temp_3 = Current_thread_index;
	      svref_new_value = Links_and_objects;
	      SVREF(temp_2,temp_3) = svref_new_value;
	      temp_2 = Available_eval_conses_tail_vector;
	      temp_3 = Current_thread_index;
	      SVREF(temp_2,temp_3) = last_1;
	  }
	  M_CDR(last_1) = Nil;
	  temp_1 = Nil;
      }
      else
	  temp_1 = Nil;
    POP_SPECIAL();
    return VALUES_1(temp_1);
}

static Object Qgsi_interface;      /* gsi-interface */

/* SAFE-INVOKE-RULES-FOR-EXISTENTIAL-CHAINING */
Object safe_invoke_rules_for_existential_chaining(object,key_sense,fsn,
	    precomputed_links_and_objects)
    Object object, key_sense, fsn, precomputed_links_and_objects;
{
    Object gensymed_symbol, xa, ya, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(153,98);
    gensymed_symbol = ISVREF(object,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(object) ? EQ(ISVREF(object,(SI_Long)1L),
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
    if ( !temp) {
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(Qgsi_interface,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(object,(SI_Long)1L),
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
		temp = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	temp = temp ? (SI_Long)0L != (IFIX(ISVREF(object,(SI_Long)4L)) & 
		(SI_Long)16777216L) : TRUEP(Nil);
	if (temp);
	else
	    temp = (SI_Long)0L != (IFIX(ISVREF(object,(SI_Long)4L)) & 
		    (SI_Long)1L);
	if (temp);
	else
	    temp = (SI_Long)0L != (IFIX(ISVREF(object,(SI_Long)5L)) & 
		    (SI_Long)262144L);
    }
    else
	temp = TRUEP(Nil);
    temp_1 = temp ? invoke_rules_for_existential_chaining(object,key_sense,
	    precomputed_links_and_objects) : Nil;
    return VALUES_1(temp_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Queue_existential_rules, Qqueue_existential_rules);

DEFINE_VARIABLE_WITH_SYMBOL(Queue_existential_rules_tail, Qqueue_existential_rules_tail);

static Object Qreclaim_frame_serial_number;  /* reclaim-frame-serial-number */

static Object Qsafe_invoke_rules_for_existential_chaining;  /* safe-invoke-rules-for-existential-chaining */

/* SCHEDULE-TASK-TO-INVOKE-EXISTENTIAL-RULES */
Object schedule_task_to_invoke_existential_rules(new_frame,sense)
    Object new_frame, sense;
{
    Object links_and_objects, fsn, qtail, new_tail, new_entry;
    Object structure_being_reclaimed, temp, svref_arg_2;
    Object def_structure_schedule_task_variable, svref_new_value, new_task;
    Declare_special(2);

    x_note_fn_call(153,99);
    if (ISVREF(ISVREF(new_frame,(SI_Long)1L),(SI_Long)16L)) {
	links_and_objects = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Links_and_objects,Qlinks_and_objects,links_and_objects,
		1);
	  collect_rules_for_existential_chaining(new_frame,sense);
	  if (Links_and_objects) {
	      fsn = ISVREF(new_frame,(SI_Long)3L);
	      qtail = Queue_existential_rules_tail;
	      if (qtail) {
		  new_tail = gensym_cons_1(Links_and_objects,Nil);
		  new_entry = gensym_cons_1(new_frame,gensym_cons_1(sense,
			  gensym_cons_1(copy_frame_serial_number(fsn),
			  new_tail)));
		  M_CDR(qtail) = new_entry;
		  Queue_existential_rules_tail = new_tail;
	      }
	      else if (Queue_existential_rules) {
		  new_tail = gensym_cons_1(Links_and_objects,Nil);
		  new_entry = gensym_cons_1(new_frame,gensym_cons_1(sense,
			  gensym_cons_1(copy_frame_serial_number(fsn),
			  new_tail)));
		  Queue_existential_rules = new_entry;
		  Queue_existential_rules_tail = new_tail;
	      }
	      else if (Scheduler_has_been_initialized_p) {
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
		      temp = 
			      ISVREF(Chain_of_available_schedule_tasks_vector,
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
		      svref_new_value = 
			      ISVREF(def_structure_schedule_task_variable,
			      (SI_Long)0L);
		      SVREF(temp,svref_arg_2) = svref_new_value;
		      SVREF(def_structure_schedule_task_variable,
			      FIX((SI_Long)0L)) = 
			      Qg2_defstruct_structure_name_schedule_task_g2_struct;
		  }
		  else
		      def_structure_schedule_task_variable = 
			      make_permanent_schedule_task_structure_internal();
		  inline_note_allocate_cons(def_structure_schedule_task_variable,
			  Nil);
		  SVREF(def_structure_schedule_task_variable,
			  FIX((SI_Long)2L)) = T;
		  SVREF(def_structure_schedule_task_variable,
			  FIX((SI_Long)9L)) = Nil;
		  new_task = def_structure_schedule_task_variable;
		  SVREF(new_task,FIX((SI_Long)4L)) = Higher_than_any_priority;
		  temp = gensym_list_3(Nil,Nil,Qreclaim_frame_serial_number);
		  SVREF(new_task,FIX((SI_Long)9L)) = temp;
		  SVREF(new_task,FIX((SI_Long)10L)) = Nil;
		  SVREF(new_task,FIX((SI_Long)7L)) = 
			  Qsafe_invoke_rules_for_existential_chaining;
		  temp = 
			  SYMBOL_FUNCTION(Qsafe_invoke_rules_for_existential_chaining);
		  SVREF(new_task,FIX((SI_Long)8L)) = temp;
		  ISVREF(new_task,(SI_Long)12L) = FIX((SI_Long)4L);
		  SVREF(new_task,FIX((SI_Long)13L)) = new_frame;
		  SVREF(new_task,FIX((SI_Long)14L)) = sense;
		  temp = copy_frame_serial_number(fsn);
		  SVREF(new_task,FIX((SI_Long)15L)) = temp;
		  temp = Links_and_objects;
		  SVREF(new_task,FIX((SI_Long)16L)) = temp;
		  temp = ISVREF(Immediate_task_queue_vector,(SI_Long)0L);
		  SVREF(new_task,FIX((SI_Long)11L)) = temp;
		  temp = 
			  constant_queue_push_right(ISVREF(Immediate_task_queue_vector,
			  (SI_Long)0L),new_task);
		  SVREF(new_task,FIX((SI_Long)6L)) = temp;
	      }
	  }
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

static Object Qg2_defstruct_structure_name_connection_g2_struct;  /* g2-defstruct-structure-name::connection-g2-struct */

static Object Qsimulation_details;  /* simulation-details */

/* RECURSIVE-SCHEDULE-TASK-TO-INVOKE-CREATION-RULES */
Object recursive_schedule_task_to_invoke_creation_rules(new_frame)
    Object new_frame;
{
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, subblock;
    Object x2, slot_description, class_description, ab_loop_list_, slot_value;
    Object vector_slot_index_qm, user_vector_slot_index_qm, slot_name;
    Object lookup_structure_qm, slot_index_qm, scope_conses, ab_node_stack_;
    Object ab_current_node_, ab_skip_list_form_, ab_skip_list_p_;
    Object ab_next_node_, ab_tail_node_, ab_current_alist_, ab_entry_cons_;
    Object ab_connection_, ab_connection_item_, connection;
    Object connection_frame_or_class, temp_1, ab_less_than_branch_qm_;
    Object sub_class_bit_vector, subworkspace, simulation_subtable_qm;
    SI_Long max_i, i, ab_loop_bind_, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_3;
    char temp;
    Declare_special(1);

    x_note_fn_call(153,100);
    schedule_task_to_invoke_existential_rules(new_frame,Qis_created);
    gensymed_symbol = ACCESS_ONCE(ISVREF(new_frame,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    subblock = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = constant_queue_next(ISVREF(ab_queue_form_,
		(SI_Long)2L),ab_queue_form_);
  next_loop:
    if ( !TRUEP(ab_next_queue_element_))
	goto end_loop;
    subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
    ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	    ab_queue_form_);
    if (SIMPLE_VECTOR_P(new_frame) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_frame)) > (SI_Long)2L &&  
	    !EQ(ISVREF(new_frame,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(new_frame,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	recursive_schedule_task_to_invoke_creation_rules(subblock);
    goto next_loop;
  end_loop:;
    slot_description = Nil;
    class_description = 
	    lookup_global_or_kb_specific_property_value(ISVREF(ISVREF(new_frame,
	    (SI_Long)1L),(SI_Long)1L),Class_description_gkbprop);
    ab_loop_list_ = ISVREF(class_description,(SI_Long)6L);
    slot_value = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    slot_description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (ISVREF(slot_description,(SI_Long)8L)) {
	vector_slot_index_qm = ISVREF(slot_description,(SI_Long)7L);
	if (vector_slot_index_qm)
	    slot_value = ISVREF(new_frame,IFIX(vector_slot_index_qm));
	else {
	    user_vector_slot_index_qm = ISVREF(slot_description,(SI_Long)8L);
	    if (user_vector_slot_index_qm)
		slot_value = ISVREF(ISVREF(new_frame,(SI_Long)0L),
			IFIX(user_vector_slot_index_qm));
	    else {
		slot_name = ISVREF(slot_description,(SI_Long)1L);
		lookup_structure_qm = ISVREF(new_frame,(SI_Long)0L);
		if (lookup_structure_qm) {
		    max_i = 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(lookup_structure_qm));
		    max_i = max_i - (SI_Long)1L;
		    i = IFIX(ISVREF(ISVREF(new_frame,(SI_Long)1L),
			    (SI_Long)15L));
		    ab_loop_bind_ = max_i;
		  next_loop_2:
		    if (i >= ab_loop_bind_)
			goto end_loop_2;
		    if (EQ(ISVREF(lookup_structure_qm,i),slot_name)) {
			slot_index_qm = FIX(i + (SI_Long)1L);
			goto end_1;
		    }
		    i = i + (SI_Long)2L;
		    goto next_loop_2;
		  end_loop_2:
		    slot_index_qm = Qnil;
		  end_1:;
		    slot_value = slot_index_qm ? 
			    ISVREF(lookup_structure_qm,
			    IFIX(slot_index_qm)) : ISVREF(slot_description,
			    (SI_Long)6L);
		}
		else
		    slot_value = ISVREF(slot_description,(SI_Long)6L);
	    }
	}
	if (SIMPLE_VECTOR_P(slot_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value)) > (SI_Long)2L 
		&&  !EQ(ISVREF(slot_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(slot_value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    recursive_schedule_task_to_invoke_creation_rules(slot_value);
    }
    goto next_loop_1;
  end_loop_1:;
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(new_frame,(SI_Long)14L));
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
      connection_frame_or_class = Nil;
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
    next_loop_3:
    next_loop_4:
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
	    next_loop_5:
	      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
	      if ( !TRUEP(ab_less_than_branch_qm_))
		  goto end_loop_3;
	      ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
	      ab_current_node_ = ab_less_than_branch_qm_;
	      goto next_loop_5;
	    end_loop_3:;
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
	      && EQ(ISVREF(ab_connection_,(SI_Long)3L),new_frame))
	  goto end_2;
      goto next_loop_4;
    end_loop_4:
    end_2:
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_5;
      connection = ab_connection_;
      connection_frame_or_class = SIMPLE_VECTOR_P(connection) && 
	      EQ(ISVREF(connection,(SI_Long)0L),
	      Qg2_defstruct_structure_name_connection_g2_struct) ? 
	      ISVREF(connection,(SI_Long)1L) : Nil;
      if (SIMPLE_VECTOR_P(connection_frame_or_class) && 
	      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_or_class)) > 
	      (SI_Long)2L &&  !EQ(ISVREF(connection_frame_or_class,
	      (SI_Long)1L),Qavailable_frame_vector)) {
	  x2 = ISVREF(connection_frame_or_class,(SI_Long)1L);
	  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		  Qg2_defstruct_structure_name_class_description_g2_struct) 
		  ? TRUEP(x2) : TRUEP(Qnil);
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  recursive_schedule_task_to_invoke_creation_rules(connection_frame_or_class);
      goto next_loop_3;
    end_loop_5:;
    POP_SPECIAL();
    sub_class_bit_vector = ISVREF(ISVREF(new_frame,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Entity_class_description,
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
	temp = (SI_Long)0L < gensymed_symbol_1;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	subworkspace = Nil;
	ab_loop_list_ = ISVREF(new_frame,(SI_Long)18L);
      next_loop_6:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_6;
	subworkspace = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	recursive_schedule_task_to_invoke_creation_rules(subworkspace);
	goto next_loop_6;
      end_loop_6:;
    }
    sub_class_bit_vector = ISVREF(ISVREF(new_frame,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Variable_class_description,
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
	temp = (SI_Long)0L < gensymed_symbol_1;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	simulation_subtable_qm = get_lookup_slot_value(new_frame,
		Qsimulation_details);
	if (simulation_subtable_qm) {
	    if (SIMPLE_VECTOR_P(simulation_subtable_qm) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(simulation_subtable_qm)) 
		    > (SI_Long)2L &&  !EQ(ISVREF(simulation_subtable_qm,
		    (SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(simulation_subtable_qm,(SI_Long)1L);
		gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? x2 : Qnil;
	    }
	    else
		gensymed_symbol = Nil;
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Simulation_subtable_class_description,
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
	if (temp)
	    recursive_schedule_task_to_invoke_creation_rules(simulation_subtable_qm);
    }
    return VALUES_1(Nil);
}

static Object string_constant_16;  /* "Scheduling event chaining to ~nf with ~nf as ~a because ~nf ~nf." */

static Object string_constant_17;  /* "Scheduling event chaining to ~NF because ~NF ~nf." */

/* WRITE-MAJOR-EXISTENTIAL-CHAINING-TRACE-MESSAGE */
Object write_major_existential_chaining_trace_message(object,chain_object,
	    recipient,role_qm,key_sense)
    Object object, chain_object, recipient, role_qm, key_sense;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object gensymed_symbol;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(153,101);
    if ((IFIX(Tracing_message_level) > (SI_Long)1L || 
	    IFIX(Breakpoint_level) > (SI_Long)1L) &&  
	    !TRUEP(Debugging_reset) && ISVREF(Debugging_parameters,
	    (SI_Long)22L)) {
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
		  if (role_qm)
		      tformat(6,string_constant_16,recipient,chain_object,
			      role_qm,object,
			      indicate_appropriate_existential_event(key_sense));
		  else
		      tformat(4,string_constant_17,recipient,object,
			      indicate_appropriate_existential_event(key_sense));
		  gensymed_symbol = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return write_major_trace_message_function(gensymed_symbol);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_18;  /* "was activated" */

static Object string_constant_19;  /* "was deactivated" */

static Object string_constant_20;  /* "was enabled" */

static Object string_constant_21;  /* "was disabled" */

static Object string_constant_22;  /* "was created" */

static Object string_constant_23;  /* "has lost its value" */

/* INDICATE-APPROPRIATE-EXISTENTIAL-EVENT */
Object indicate_appropriate_existential_event(key_sense)
    Object key_sense;
{
    x_note_fn_call(153,102);
    if (EQ(key_sense,Qis_activated))
	return VALUES_1(string_constant_18);
    else if (EQ(key_sense,Qis_deactivated))
	return VALUES_1(string_constant_19);
    else if (EQ(key_sense,Qis_enabled))
	return VALUES_1(string_constant_20);
    else if (EQ(key_sense,Qis_disabled))
	return VALUES_1(string_constant_21);
    else if (EQ(key_sense,Qis_created))
	return VALUES_1(string_constant_22);
    else if (EQ(key_sense,Qloses_its_value))
	return VALUES_1(string_constant_23);
    else
	return VALUES_1(Qnil);
}

/* COLLECT-RULES-FOR-EXISTENTIAL-CHAINING */
Object collect_rules_for_existential_chaining(object,key_sense)
    Object object, key_sense;
{
    Object object_names_qm, object_name_cons_qm, parent_stack, object_name;
    Object ab_loop_list_, link_1, list_1, ab_loop_list__1, stored_sense;
    Object new_cons, temp, svref_arg_2, svref_new_value, gensymed_symbol;
    Object new_value, old_value, parent_stack_entry, parent_frame_qm;
    Object class_description, classes, cache_qm, class_1, specific_list;
    Object designation, temp_1;
    char temp_2;

    x_note_fn_call(153,103);
    object_names_qm = get_lookup_slot_value_given_default(object,
	    Qname_or_names_for_frame,Nil);
    if (object_names_qm && SYMBOLP(object_names_qm)) {
	object_names_qm = eval_cons_1(object_names_qm,Nil);
	object_name_cons_qm = object_names_qm;
    }
    else
	object_name_cons_qm = Nil;
    parent_stack = make_parent_stack(object);
    object_name = Nil;
    ab_loop_list_ = object_names_qm;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    object_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    link_1 = Nil;
    list_1 = INLINE_SYMBOL_PLIST(object_name);
  next_loop_1:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop_1;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_1;
  end_loop_1:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_2:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Forward_chaining_list_kbprop))
	goto end_loop_2;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_2;
  end_loop_2:
    ab_loop_list__1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    stored_sense = Nil;
  next_loop_3:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_3;
    link_1 = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    stored_sense = ISVREF(link_1,(SI_Long)7L);
    if (EQ(stored_sense,key_sense) && EQ(object_name,ISVREF(link_1,
	    (SI_Long)3L))) {
	new_cons = ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_eval_cons_pool();
	M_CAR(gensymed_symbol) = link_1;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qeval);
	new_value = eval_cons_1(gensymed_symbol,Nil);
	old_value = Nil;
      next_loop_4:
	old_value = Links_and_objects;
	M_CDR(new_value) = old_value;
	if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value))
	    goto end_loop_4;
	goto next_loop_4;
      end_loop_4:
	goto end_1;
      end_1:;
    }
    goto next_loop_3;
  end_loop_3:;
    goto next_loop;
  end_loop:;
    if (parent_stack) {
	parent_stack_entry = M_CAR(parent_stack);
	link_1 = Nil;
	gensymed_symbol = M_CAR(M_CDR(parent_stack_entry));
	gensymed_symbol = CONSP(gensymed_symbol) ? M_CAR(gensymed_symbol) :
		 gensymed_symbol;
	list_1 = INLINE_SYMBOL_PLIST(gensymed_symbol);
      next_loop_5:
	if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
		Current_kb_specific_property_list_property_name))
	    goto end_loop_5;
	list_1 = M_CDR(M_CDR(list_1));
	goto next_loop_5;
      end_loop_5:
	list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
      next_loop_6:
	if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Forward_chaining_list_kbprop))
	    goto end_loop_6;
	list_1 = M_CDR(M_CDR(list_1));
	goto next_loop_6;
      end_loop_6:
	ab_loop_list_ = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
	stored_sense = Nil;
      next_loop_7:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_7;
	link_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	stored_sense = ISVREF(link_1,(SI_Long)7L);
	if (EQ(stored_sense,key_sense)) {
	    parent_frame_qm = find_referenced_parent(parent_stack,
		    ISVREF(link_1,(SI_Long)3L));
	    if (parent_frame_qm) {
		new_cons = ISVREF(Available_eval_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    temp = Available_eval_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(temp,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
			    IFIX(Current_thread_index)))) {
			temp = Available_eval_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = Nil;
		    }
		    gensymed_symbol = new_cons;
		}
		else
		    gensymed_symbol = Nil;
		if ( !TRUEP(gensymed_symbol))
		    gensymed_symbol = replenish_eval_cons_pool();
		M_CAR(gensymed_symbol) = link_1;
		M_CDR(gensymed_symbol) = parent_frame_qm;
		inline_note_allocate_cons(gensymed_symbol,Qeval);
		new_value = eval_cons_1(gensymed_symbol,Nil);
		old_value = Nil;
	      next_loop_8:
		old_value = Links_and_objects;
		M_CDR(new_value) = old_value;
		if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value))
		    goto end_loop_8;
		goto next_loop_8;
	      end_loop_8:
		goto end_2;
	      end_2:;
	    }
	}
	goto next_loop_7;
      end_loop_7:;
    }
    link_1 = Nil;
    class_description = ISVREF(object,(SI_Long)1L);
    classes = ISVREF(class_description,(SI_Long)2L);
    gensymed_symbol = M_CAR(classes);
    list_1 = INLINE_SYMBOL_PLIST(gensymed_symbol);
  next_loop_9:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop_9;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_9;
  end_loop_9:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_10:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Cached_class_forward_chaining_list_kbprop))
	goto end_loop_10;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_10;
  end_loop_10:
    cache_qm = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    if (cache_qm)
	ab_loop_list_ = M_CDR(cache_qm);
    else {
	class_1 = Nil;
	ab_loop_list_ = classes;
	specific_list = Nil;
      next_loop_11:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_11;
	class_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	specific_list = lookup_kb_specific_property_value(class_1,
		Forward_chaining_list_kbprop);
	if (specific_list) {
	    specific_list = copy_list_using_eval_conses_1(specific_list);
	    if (cache_qm)
		cache_qm = nconc2(cache_qm,specific_list);
	    else
		cache_qm = specific_list;
	}
	if (EQ(class_1,Qitem))
	    goto end_loop_11;
	goto next_loop_11;
      end_loop_11:
	mutate_kb_specific_property_value(M_CAR(classes),eval_cons_1(Nil,
		cache_qm),Cached_class_forward_chaining_list_kbprop);
	new_value = eval_cons_1(M_CAR(classes),Nil);
	old_value = Nil;
      next_loop_12:
	old_value = Cached_classes_for_forward_chaining;
	M_CDR(new_value) = old_value;
	if (CAS_SYMBOL(Qcached_classes_for_forward_chaining,old_value,
		new_value))
	    goto end_loop_12;
	goto next_loop_12;
      end_loop_12:
	goto end_3;
      end_3:;
	ab_loop_list_ = cache_qm;
	goto end_4;
	ab_loop_list_ = Qnil;
      end_4:;
    }
    stored_sense = Nil;
    designation = Nil;
  next_loop_13:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_13;
    link_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    stored_sense = ISVREF(link_1,(SI_Long)7L);
    designation = ISVREF(link_1,(SI_Long)3L);
    if (EQ(stored_sense,key_sense) &&  !SYMBOLP(designation)) {
	if (domain_of_designation(designation)) {
	    temp_1 = role_of_designation(designation);
	    temp_2 = SYMBOLP(temp_1);
	}
	else
	    temp_2 = TRUEP(Nil);
	temp_2 =  !temp_2;
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	new_cons = ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_eval_cons_pool();
	M_CAR(gensymed_symbol) = link_1;
	M_CDR(gensymed_symbol) = object;
	inline_note_allocate_cons(gensymed_symbol,Qeval);
	new_value = eval_cons_1(gensymed_symbol,Nil);
	old_value = Nil;
      next_loop_14:
	old_value = Links_and_objects;
	M_CDR(new_value) = old_value;
	if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value))
	    goto end_loop_14;
	goto next_loop_14;
      end_loop_14:
	goto end_5;
      end_5:;
    }
    goto next_loop_13;
  end_loop_13:;
    if (object_name_cons_qm) {
	inline_note_reclaim_cons(object_name_cons_qm,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = object_name_cons_qm;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = object_name_cons_qm;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = object_name_cons_qm;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = object_name_cons_qm;
	}
	M_CDR(object_name_cons_qm) = Nil;
    }
    return reclaim_parent_stack(parent_stack);
}

/* INVOKE-RULES-FOR-RESIZEMENT-CHAINING */
Object invoke_rules_for_resizement_chaining(object,resizer)
    Object object, resizer;
{
    Object x2, current_computation_frame_previously_bound_qm;
    Object links_and_objects, link_entry, ab_loop_list_, link_1, recipient;
    Object sub_class_bit_vector, temp_1, role_qm, local_name_qm, chain_object;
    Object gensymed_symbol_3, temp_2, temp_3, last_1, next_qm, svref_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(153,104);
    if (SIMPLE_VECTOR_P(Current_computation_frame) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_computation_frame)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(Current_computation_frame,
	    (SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(Current_computation_frame,(SI_Long)1L);
	current_computation_frame_previously_bound_qm = 
		SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	current_computation_frame_previously_bound_qm = Nil;
    links_and_objects = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Links_and_objects,Qlinks_and_objects,links_and_objects,
	    0);
      if ( !TRUEP(current_computation_frame_previously_bound_qm))
	  Current_computation_frame = object;
      collect_rules_for_resizement_chaining(object,resizer);
      link_entry = Nil;
      ab_loop_list_ = Links_and_objects;
      link_1 = Nil;
      recipient = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      link_entry = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      link_1 = CAR(link_entry);
      recipient = ISVREF(link_1,(SI_Long)2L);
      sub_class_bit_vector = ISVREF(ISVREF(recipient,(SI_Long)1L),
	      (SI_Long)19L);
      superior_class_bit_number = 
	      IFIX(ISVREF(True_value_update_recipient_class_description,
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
      if ( !temp) {
	  temp_1 = ISVREF(recipient,(SI_Long)8L);
	  temp =  !TRUEP(CAR(temp_1)) ? (SI_Long)0L != 
		  (IFIX(ISVREF(recipient,(SI_Long)5L)) & (SI_Long)1L) ||  
		  !TRUEP(Inside_breakpoint_p) && (SI_Long)0L != 
		  (IFIX(ISVREF(recipient,(SI_Long)4L)) & 
		  (SI_Long)16777216L) &&  !((SI_Long)0L != 
		  (IFIX(ISVREF(recipient,(SI_Long)4L)) & (SI_Long)8192L)) :
		   TRUEP(Nil);
      }
      else
	  temp = TRUEP(Nil);
      if (temp) {
	  role_qm = ISVREF(link_1,(SI_Long)4L);
	  local_name_qm = role_qm ? ISVREF(link_1,(SI_Long)5L) : Nil;
	  chain_object = role_qm ? CDR(link_entry) : Nil;
	  if (EQ(role_qm,Qkb_workspace)) {
	      if ((SI_Long)0L != (IFIX(ISVREF(recipient,(SI_Long)4L)) & 
		      (SI_Long)67108864L)) {
		  gensymed_symbol_3 = ACCESS_ONCE(ISVREF(recipient,
			  (SI_Long)14L));
		  gensymed_symbol_3 = gensymed_symbol_3 ? 
			  ACCESS_ONCE(ISVREF(gensymed_symbol_3,
			  (SI_Long)5L)) : Nil;
		  temp_1 = EQ(get_workspace_if_any(gensymed_symbol_3),
			  chain_object) ? T : Nil;
	      }
	      else
		  temp_1 = T;
	  }
	  else if (EQ(role_qm,Qrule))
	      temp_1 = (SI_Long)0L != (IFIX(ISVREF(recipient,(SI_Long)4L)) 
		      & (SI_Long)67108864L) ? (EQ(recipient,chain_object) ?
		       T : Nil) : T;
	  else if (EQ(role_qm,Qitem)) {
	      sub_class_bit_vector = ISVREF(ISVREF(chain_object,
		      (SI_Long)1L),(SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
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
	      temp_1 =  !temp ? T : Nil;
	  }
	  else
	      temp_1 = T;
	  if (temp_1) {
	      write_major_resizement_chaining_trace_message(object,
		      chain_object,recipient,role_qm,resizer);
	      generate_and_schedule_rule_instances(recipient,role_qm,
		      local_name_qm,chain_object,Qforward_chaining,Nil,
		      ISVREF(recipient,(SI_Long)26L),Nil);
	  }
      }
      inline_note_reclaim_cons(link_entry,Qeval);
      if (ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	  temp_2 = ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index));
	  M_CDR(temp_2) = link_entry;
	  temp_2 = Available_eval_conses_tail_vector;
	  temp_3 = Current_thread_index;
	  SVREF(temp_2,temp_3) = link_entry;
      }
      else {
	  temp_2 = Available_eval_conses_vector;
	  temp_3 = Current_thread_index;
	  SVREF(temp_2,temp_3) = link_entry;
	  temp_2 = Available_eval_conses_tail_vector;
	  temp_3 = Current_thread_index;
	  SVREF(temp_2,temp_3) = link_entry;
      }
      M_CDR(link_entry) = Nil;
      goto next_loop;
    end_loop:;
      if ( !TRUEP(current_computation_frame_previously_bound_qm))
	  Current_computation_frame = Nil;
      if (Links_and_objects) {
	  last_1 = Links_and_objects;
	  next_qm = Nil;
	next_loop_1:
	  next_qm = M_CDR(last_1);
	  if ( !TRUEP(next_qm))
	      goto end_loop_1;
	  inline_note_reclaim_cons(last_1,Qeval);
	  last_1 = next_qm;
	  goto next_loop_1;
	end_loop_1:
	  inline_note_reclaim_cons(last_1,Qeval);
	  if (ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	      temp_2 = ISVREF(Available_eval_conses_tail_vector,
		      IFIX(Current_thread_index));
	      temp_3 = Links_and_objects;
	      M_CDR(temp_2) = temp_3;
	      temp_2 = Available_eval_conses_tail_vector;
	      temp_3 = Current_thread_index;
	      SVREF(temp_2,temp_3) = last_1;
	  }
	  else {
	      temp_2 = Available_eval_conses_vector;
	      temp_3 = Current_thread_index;
	      svref_new_value = Links_and_objects;
	      SVREF(temp_2,temp_3) = svref_new_value;
	      temp_2 = Available_eval_conses_tail_vector;
	      temp_3 = Current_thread_index;
	      SVREF(temp_2,temp_3) = last_1;
	  }
	  M_CDR(last_1) = Nil;
	  result = VALUES_1(Nil);
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object string_constant_24;  /* "Scheduling event chaining to ~nf with ~nf as ~a because ~nf was resized by the user." */

static Object string_constant_25;  /* "Scheduling event chaining to ~NF because ~NF was resized by the user." */

/* WRITE-MAJOR-RESIZEMENT-CHAINING-TRACE-MESSAGE */
Object write_major_resizement_chaining_trace_message(object,chain_object,
	    recipient,role_qm,resizer)
    Object object, chain_object, recipient, role_qm, resizer;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object gensymed_symbol;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(153,105);
    if ((IFIX(Tracing_message_level) > (SI_Long)1L || 
	    IFIX(Breakpoint_level) > (SI_Long)1L) &&  
	    !TRUEP(Debugging_reset) && ISVREF(Debugging_parameters,
	    (SI_Long)22L)) {
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
		  if (role_qm)
		      tformat(5,string_constant_24,recipient,chain_object,
			      role_qm,object);
		  else
		      tformat(3,string_constant_25,recipient,object);
		  gensymed_symbol = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return write_major_trace_message_function(gensymed_symbol);
    }
    else
	return VALUES_1(Nil);
}

/* COLLECT-RULES-FOR-RESIZEMENT-CHAINING */
Object collect_rules_for_resizement_chaining(object,resizer)
    Object object, resizer;
{
    Object object_names_qm, object_name_cons_qm, parent_stack, object_name;
    Object ab_loop_list_, link_1, list_1, ab_loop_list__1, stored_sense;
    Object new_cons, temp, svref_arg_2, svref_new_value, gensymed_symbol;
    Object new_value, old_value, parent_stack_entry, parent_frame_qm;
    Object class_description, classes, cache_qm, class_1, specific_list;
    Object designation, temp_1;
    char temp_2;

    x_note_fn_call(153,106);
    object_names_qm = get_lookup_slot_value_given_default(object,
	    Qname_or_names_for_frame,Nil);
    if (object_names_qm && SYMBOLP(object_names_qm)) {
	object_names_qm = eval_cons_1(object_names_qm,Nil);
	object_name_cons_qm = object_names_qm;
    }
    else
	object_name_cons_qm = Nil;
    parent_stack = make_parent_stack(object);
    object_name = Nil;
    ab_loop_list_ = object_names_qm;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    object_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    link_1 = Nil;
    list_1 = INLINE_SYMBOL_PLIST(object_name);
  next_loop_1:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop_1;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_1;
  end_loop_1:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_2:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Forward_chaining_list_kbprop))
	goto end_loop_2;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_2;
  end_loop_2:
    ab_loop_list__1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    stored_sense = Nil;
  next_loop_3:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_3;
    link_1 = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    stored_sense = ISVREF(link_1,(SI_Long)7L);
    if (EQ(stored_sense,resizer) && EQ(object_name,ISVREF(link_1,
		(SI_Long)3L))) {
	new_cons = ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_eval_cons_pool();
	M_CAR(gensymed_symbol) = link_1;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qeval);
	new_value = eval_cons_1(gensymed_symbol,Nil);
	old_value = Nil;
      next_loop_4:
	old_value = Links_and_objects;
	M_CDR(new_value) = old_value;
	if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value))
	    goto end_loop_4;
	goto next_loop_4;
      end_loop_4:
	goto end_1;
      end_1:;
    }
    goto next_loop_3;
  end_loop_3:;
    goto next_loop;
  end_loop:;
    if (parent_stack) {
	parent_stack_entry = M_CAR(parent_stack);
	link_1 = Nil;
	gensymed_symbol = M_CAR(M_CDR(parent_stack_entry));
	gensymed_symbol = CONSP(gensymed_symbol) ? M_CAR(gensymed_symbol) :
		 gensymed_symbol;
	list_1 = INLINE_SYMBOL_PLIST(gensymed_symbol);
      next_loop_5:
	if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
		Current_kb_specific_property_list_property_name))
	    goto end_loop_5;
	list_1 = M_CDR(M_CDR(list_1));
	goto next_loop_5;
      end_loop_5:
	list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
      next_loop_6:
	if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Forward_chaining_list_kbprop))
	    goto end_loop_6;
	list_1 = M_CDR(M_CDR(list_1));
	goto next_loop_6;
      end_loop_6:
	ab_loop_list_ = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
	stored_sense = Nil;
      next_loop_7:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_7;
	link_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	stored_sense = ISVREF(link_1,(SI_Long)7L);
	if (EQ(stored_sense,resizer)) {
	    parent_frame_qm = find_referenced_parent(parent_stack,
		    ISVREF(link_1,(SI_Long)3L));
	    if (parent_frame_qm) {
		new_cons = ISVREF(Available_eval_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    temp = Available_eval_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(temp,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
			    IFIX(Current_thread_index)))) {
			temp = Available_eval_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = Nil;
		    }
		    gensymed_symbol = new_cons;
		}
		else
		    gensymed_symbol = Nil;
		if ( !TRUEP(gensymed_symbol))
		    gensymed_symbol = replenish_eval_cons_pool();
		M_CAR(gensymed_symbol) = link_1;
		M_CDR(gensymed_symbol) = parent_frame_qm;
		inline_note_allocate_cons(gensymed_symbol,Qeval);
		new_value = eval_cons_1(gensymed_symbol,Nil);
		old_value = Nil;
	      next_loop_8:
		old_value = Links_and_objects;
		M_CDR(new_value) = old_value;
		if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value))
		    goto end_loop_8;
		goto next_loop_8;
	      end_loop_8:
		goto end_2;
	      end_2:;
	    }
	}
	goto next_loop_7;
      end_loop_7:;
    }
    link_1 = Nil;
    class_description = ISVREF(object,(SI_Long)1L);
    classes = ISVREF(class_description,(SI_Long)2L);
    gensymed_symbol = M_CAR(classes);
    list_1 = INLINE_SYMBOL_PLIST(gensymed_symbol);
  next_loop_9:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop_9;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_9;
  end_loop_9:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_10:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Cached_class_forward_chaining_list_kbprop))
	goto end_loop_10;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_10;
  end_loop_10:
    cache_qm = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    if (cache_qm)
	ab_loop_list_ = M_CDR(cache_qm);
    else {
	class_1 = Nil;
	ab_loop_list_ = classes;
	specific_list = Nil;
      next_loop_11:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_11;
	class_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	specific_list = lookup_kb_specific_property_value(class_1,
		Forward_chaining_list_kbprop);
	if (specific_list) {
	    specific_list = copy_list_using_eval_conses_1(specific_list);
	    if (cache_qm)
		cache_qm = nconc2(cache_qm,specific_list);
	    else
		cache_qm = specific_list;
	}
	if (EQ(class_1,Qitem))
	    goto end_loop_11;
	goto next_loop_11;
      end_loop_11:
	mutate_kb_specific_property_value(M_CAR(classes),eval_cons_1(Nil,
		cache_qm),Cached_class_forward_chaining_list_kbprop);
	new_value = eval_cons_1(M_CAR(classes),Nil);
	old_value = Nil;
      next_loop_12:
	old_value = Cached_classes_for_forward_chaining;
	M_CDR(new_value) = old_value;
	if (CAS_SYMBOL(Qcached_classes_for_forward_chaining,old_value,
		new_value))
	    goto end_loop_12;
	goto next_loop_12;
      end_loop_12:
	goto end_3;
      end_3:;
	ab_loop_list_ = cache_qm;
	goto end_4;
	ab_loop_list_ = Qnil;
      end_4:;
    }
    stored_sense = Nil;
    designation = Nil;
  next_loop_13:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_13;
    link_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    stored_sense = ISVREF(link_1,(SI_Long)7L);
    designation = ISVREF(link_1,(SI_Long)3L);
    if (EQ(stored_sense,resizer) &&  !SYMBOLP(designation)) {
	if (domain_of_designation(designation)) {
	    temp_1 = role_of_designation(designation);
	    temp_2 = SYMBOLP(temp_1);
	}
	else
	    temp_2 = TRUEP(Nil);
	temp_2 =  !temp_2;
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	new_cons = ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_eval_cons_pool();
	M_CAR(gensymed_symbol) = link_1;
	M_CDR(gensymed_symbol) = object;
	inline_note_allocate_cons(gensymed_symbol,Qeval);
	new_value = eval_cons_1(gensymed_symbol,Nil);
	old_value = Nil;
      next_loop_14:
	old_value = Links_and_objects;
	M_CDR(new_value) = old_value;
	if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value))
	    goto end_loop_14;
	goto next_loop_14;
      end_loop_14:
	goto end_5;
      end_5:;
    }
    goto next_loop_13;
  end_loop_13:;
    if (object_name_cons_qm) {
	inline_note_reclaim_cons(object_name_cons_qm,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = object_name_cons_qm;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = object_name_cons_qm;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = object_name_cons_qm;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = object_name_cons_qm;
	}
	M_CDR(object_name_cons_qm) = Nil;
    }
    return reclaim_parent_stack(parent_stack);
}

/* INVOKE-RULES-FOR-FAILURE-CHAINING */
Object invoke_rules_for_failure_chaining(object)
    Object object;
{
    Object links_and_objects, link_entry, ab_loop_list_, link_1, recipient;
    Object sub_class_bit_vector, temp_1, role_qm, local_name_qm, chain_object;
    Object current_computation_frame, temp_2, temp_3, last_1, next_qm;
    Object svref_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(2);
    Object result;

    x_note_fn_call(153,107);
    links_and_objects = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Links_and_objects,Qlinks_and_objects,links_and_objects,
	    1);
      collect_rules_for_failure_chaining(object);
      link_entry = Nil;
      ab_loop_list_ = Links_and_objects;
      link_1 = Nil;
      recipient = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      link_entry = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      link_1 = CAR(link_entry);
      recipient = ISVREF(link_1,(SI_Long)2L);
      sub_class_bit_vector = ISVREF(ISVREF(recipient,(SI_Long)1L),
	      (SI_Long)19L);
      superior_class_bit_number = 
	      IFIX(ISVREF(True_value_update_recipient_class_description,
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
      if ( !temp) {
	  temp_1 = ISVREF(recipient,(SI_Long)8L);
	  temp =  !TRUEP(CAR(temp_1)) ? (SI_Long)0L != 
		  (IFIX(ISVREF(recipient,(SI_Long)5L)) & (SI_Long)1L) ||  
		  !TRUEP(Inside_breakpoint_p) && (SI_Long)0L != 
		  (IFIX(ISVREF(recipient,(SI_Long)4L)) & 
		  (SI_Long)16777216L) &&  !((SI_Long)0L != 
		  (IFIX(ISVREF(recipient,(SI_Long)4L)) & (SI_Long)8192L)) :
		   TRUEP(Nil);
      }
      else
	  temp = TRUEP(Nil);
      if (temp) {
	  role_qm = ISVREF(link_1,(SI_Long)4L);
	  local_name_qm = role_qm ? ISVREF(link_1,(SI_Long)5L) : Nil;
	  chain_object = role_qm ? CDR(link_entry) : Nil;
	  current_computation_frame = object;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		  0);
	    write_major_failure_chaining_trace_message(object,chain_object,
		    recipient,role_qm);
	    generate_and_schedule_rule_instances(recipient,role_qm,
		    local_name_qm,chain_object,Qforward_chaining,Nil,
		    ISVREF(recipient,(SI_Long)26L),Nil);
	  POP_SPECIAL();
      }
      inline_note_reclaim_cons(link_entry,Qeval);
      if (ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	  temp_2 = ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index));
	  M_CDR(temp_2) = link_entry;
	  temp_2 = Available_eval_conses_tail_vector;
	  temp_3 = Current_thread_index;
	  SVREF(temp_2,temp_3) = link_entry;
      }
      else {
	  temp_2 = Available_eval_conses_vector;
	  temp_3 = Current_thread_index;
	  SVREF(temp_2,temp_3) = link_entry;
	  temp_2 = Available_eval_conses_tail_vector;
	  temp_3 = Current_thread_index;
	  SVREF(temp_2,temp_3) = link_entry;
      }
      M_CDR(link_entry) = Nil;
      goto next_loop;
    end_loop:;
      if (Links_and_objects) {
	  last_1 = Links_and_objects;
	  next_qm = Nil;
	next_loop_1:
	  next_qm = M_CDR(last_1);
	  if ( !TRUEP(next_qm))
	      goto end_loop_1;
	  inline_note_reclaim_cons(last_1,Qeval);
	  last_1 = next_qm;
	  goto next_loop_1;
	end_loop_1:
	  inline_note_reclaim_cons(last_1,Qeval);
	  if (ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	      temp_2 = ISVREF(Available_eval_conses_tail_vector,
		      IFIX(Current_thread_index));
	      temp_3 = Links_and_objects;
	      M_CDR(temp_2) = temp_3;
	      temp_2 = Available_eval_conses_tail_vector;
	      temp_3 = Current_thread_index;
	      SVREF(temp_2,temp_3) = last_1;
	  }
	  else {
	      temp_2 = Available_eval_conses_vector;
	      temp_3 = Current_thread_index;
	      svref_new_value = Links_and_objects;
	      SVREF(temp_2,temp_3) = svref_new_value;
	      temp_2 = Available_eval_conses_tail_vector;
	      temp_3 = Current_thread_index;
	      SVREF(temp_2,temp_3) = last_1;
	  }
	  M_CDR(last_1) = Nil;
	  result = VALUES_1(Nil);
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object string_constant_26;  /* "Scheduling event chaining to ~NF with ~NF as ~A because ~NF failed ~?
				    *          to receive a value."
				    */

static Object string_constant_27;  /* "Scheduling event chaining to ~NF because ~NF failed to receive a value." */

/* WRITE-MAJOR-FAILURE-CHAINING-TRACE-MESSAGE */
Object write_major_failure_chaining_trace_message(object,chain_object,
	    recipient,role_qm)
    Object object, chain_object, recipient, role_qm;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object gensymed_symbol;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(153,108);
    if ((IFIX(Tracing_message_level) > (SI_Long)1L || 
	    IFIX(Breakpoint_level) > (SI_Long)1L) &&  
	    !TRUEP(Debugging_reset) && ISVREF(Debugging_parameters,
	    (SI_Long)22L)) {
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
		  if (role_qm)
		      tformat(5,string_constant_26,recipient,chain_object,
			      role_qm,object);
		  else
		      tformat(3,string_constant_27,recipient,object);
		  gensymed_symbol = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return write_major_trace_message_function(gensymed_symbol);
    }
    else
	return VALUES_1(Nil);
}

/* COLLECT-RULES-FOR-FAILURE-CHAINING */
Object collect_rules_for_failure_chaining(object)
    Object object;
{
    Object object_names_qm, object_name_cons_qm, parent_stack, object_name;
    Object ab_loop_list_, link_1, list_1, ab_loop_list__1, stored_sense;
    Object new_cons, temp, svref_arg_2, svref_new_value, gensymed_symbol;
    Object new_value, old_value, parent_stack_entry, parent_frame;
    Object class_description, classes, cache_qm, class_1, specific_list;
    Object designation, temp_1;
    char temp_2;

    x_note_fn_call(153,109);
    object_names_qm = get_lookup_slot_value_given_default(object,
	    Qname_or_names_for_frame,Nil);
    if (object_names_qm && SYMBOLP(object_names_qm)) {
	object_names_qm = eval_cons_1(object_names_qm,Nil);
	object_name_cons_qm = object_names_qm;
    }
    else
	object_name_cons_qm = Nil;
    parent_stack = make_parent_stack(object);
    object_name = Nil;
    ab_loop_list_ = object_names_qm;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    object_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    link_1 = Nil;
    list_1 = INLINE_SYMBOL_PLIST(object_name);
  next_loop_1:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop_1;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_1;
  end_loop_1:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_2:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Forward_chaining_list_kbprop))
	goto end_loop_2;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_2;
  end_loop_2:
    ab_loop_list__1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    stored_sense = Nil;
  next_loop_3:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_3;
    link_1 = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    stored_sense = ISVREF(link_1,(SI_Long)7L);
    if (EQ(stored_sense,Qfails_to_receive_a_value) && EQ(object_name,
	    ISVREF(link_1,(SI_Long)3L))) {
	new_cons = ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_eval_cons_pool();
	M_CAR(gensymed_symbol) = link_1;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qeval);
	new_value = eval_cons_1(gensymed_symbol,Nil);
	old_value = Nil;
      next_loop_4:
	old_value = Links_and_objects;
	M_CDR(new_value) = old_value;
	if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value))
	    goto end_loop_4;
	goto next_loop_4;
      end_loop_4:
	goto end_1;
      end_1:;
    }
    goto next_loop_3;
  end_loop_3:;
    goto next_loop;
  end_loop:;
    if (parent_stack) {
	parent_stack_entry = M_CAR(parent_stack);
	link_1 = Nil;
	gensymed_symbol = M_CAR(M_CDR(parent_stack_entry));
	gensymed_symbol = CONSP(gensymed_symbol) ? M_CAR(gensymed_symbol) :
		 gensymed_symbol;
	list_1 = INLINE_SYMBOL_PLIST(gensymed_symbol);
      next_loop_5:
	if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
		Current_kb_specific_property_list_property_name))
	    goto end_loop_5;
	list_1 = M_CDR(M_CDR(list_1));
	goto next_loop_5;
      end_loop_5:
	list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
      next_loop_6:
	if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Forward_chaining_list_kbprop))
	    goto end_loop_6;
	list_1 = M_CDR(M_CDR(list_1));
	goto next_loop_6;
      end_loop_6:
	ab_loop_list_ = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
	stored_sense = Nil;
      next_loop_7:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_7;
	link_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	stored_sense = ISVREF(link_1,(SI_Long)7L);
	if (EQ(stored_sense,Qfails_to_receive_a_value)) {
	    parent_frame = find_referenced_parent(parent_stack,
		    ISVREF(link_1,(SI_Long)3L));
	    if (parent_frame) {
		new_cons = ISVREF(Available_eval_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    temp = Available_eval_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(temp,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
			    IFIX(Current_thread_index)))) {
			temp = Available_eval_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = Nil;
		    }
		    gensymed_symbol = new_cons;
		}
		else
		    gensymed_symbol = Nil;
		if ( !TRUEP(gensymed_symbol))
		    gensymed_symbol = replenish_eval_cons_pool();
		M_CAR(gensymed_symbol) = link_1;
		M_CDR(gensymed_symbol) = parent_frame;
		inline_note_allocate_cons(gensymed_symbol,Qeval);
		new_value = eval_cons_1(gensymed_symbol,Nil);
		old_value = Nil;
	      next_loop_8:
		old_value = Links_and_objects;
		M_CDR(new_value) = old_value;
		if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value))
		    goto end_loop_8;
		goto next_loop_8;
	      end_loop_8:
		goto end_2;
	      end_2:;
	    }
	}
	goto next_loop_7;
      end_loop_7:;
    }
    link_1 = Nil;
    class_description = ISVREF(object,(SI_Long)1L);
    classes = ISVREF(class_description,(SI_Long)2L);
    gensymed_symbol = M_CAR(classes);
    list_1 = INLINE_SYMBOL_PLIST(gensymed_symbol);
  next_loop_9:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop_9;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_9;
  end_loop_9:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_10:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Cached_class_forward_chaining_list_kbprop))
	goto end_loop_10;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_10;
  end_loop_10:
    cache_qm = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    if (cache_qm)
	ab_loop_list_ = M_CDR(cache_qm);
    else {
	class_1 = Nil;
	ab_loop_list_ = classes;
	specific_list = Nil;
      next_loop_11:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_11;
	class_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	specific_list = lookup_kb_specific_property_value(class_1,
		Forward_chaining_list_kbprop);
	if (specific_list) {
	    specific_list = copy_list_using_eval_conses_1(specific_list);
	    if (cache_qm)
		cache_qm = nconc2(cache_qm,specific_list);
	    else
		cache_qm = specific_list;
	}
	if (EQ(class_1,Qitem))
	    goto end_loop_11;
	goto next_loop_11;
      end_loop_11:
	mutate_kb_specific_property_value(M_CAR(classes),eval_cons_1(Nil,
		cache_qm),Cached_class_forward_chaining_list_kbprop);
	new_value = eval_cons_1(M_CAR(classes),Nil);
	old_value = Nil;
      next_loop_12:
	old_value = Cached_classes_for_forward_chaining;
	M_CDR(new_value) = old_value;
	if (CAS_SYMBOL(Qcached_classes_for_forward_chaining,old_value,
		new_value))
	    goto end_loop_12;
	goto next_loop_12;
      end_loop_12:
	goto end_3;
      end_3:;
	ab_loop_list_ = cache_qm;
	goto end_4;
	ab_loop_list_ = Qnil;
      end_4:;
    }
    stored_sense = Nil;
    designation = Nil;
  next_loop_13:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_13;
    link_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    stored_sense = ISVREF(link_1,(SI_Long)7L);
    designation = ISVREF(link_1,(SI_Long)3L);
    if (EQ(stored_sense,Qfails_to_receive_a_value) &&  !SYMBOLP(designation)) {
	if (domain_of_designation(designation)) {
	    temp_1 = role_of_designation(designation);
	    temp_2 = SYMBOLP(temp_1);
	}
	else
	    temp_2 = TRUEP(Nil);
	temp_2 =  !temp_2;
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	new_cons = ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_eval_cons_pool();
	M_CAR(gensymed_symbol) = link_1;
	M_CDR(gensymed_symbol) = object;
	inline_note_allocate_cons(gensymed_symbol,Qeval);
	new_value = eval_cons_1(gensymed_symbol,Nil);
	old_value = Nil;
      next_loop_14:
	old_value = Links_and_objects;
	M_CDR(new_value) = old_value;
	if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value))
	    goto end_loop_14;
	goto next_loop_14;
      end_loop_14:
	goto end_5;
      end_5:;
    }
    goto next_loop_13;
  end_loop_13:;
    if (object_name_cons_qm) {
	inline_note_reclaim_cons(object_name_cons_qm,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = object_name_cons_qm;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = object_name_cons_qm;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = object_name_cons_qm;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = object_name_cons_qm;
	}
	M_CDR(object_name_cons_qm) = Nil;
    }
    return reclaim_parent_stack(parent_stack);
}

/* INSTALL-TRUE-VALUE-UPDATE */
Object install_true_value_update(update_function,frame_qm,extra_argument,
	    old_expression_qm,new_expression_qm)
    Object update_function, frame_qm, extra_argument, old_expression_qm;
    Object new_expression_qm;
{
    Object current_block_of_dependent_frame, names_and_info_for_chaining;
    Object update_function_spec, old_name_and_info, ab_loop_list_, old_name;
    Object old_link, chaining_link, ab_loop_list__1, temp, temp_1;
    Object new_name_and_info, new_name, new_link;
    Declare_special(2);
    Object result;

    x_note_fn_call(153,110);
    decache_class_chaining_lists();
    current_block_of_dependent_frame = Qdependent_frame_has_no_owner;
    PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
	    1);
      if (old_expression_qm) {
	  names_and_info_for_chaining = Nil;
	  update_function_spec = 
		  make_true_value_update_recipient(update_function,
		  frame_qm,extra_argument);
	  PUSH_SPECIAL_WITH_SYMBOL(Names_and_info_for_chaining,Qnames_and_info_for_chaining,names_and_info_for_chaining,
		  0);
	    note_names_and_info_for_true_value_chaining_in_expression(old_expression_qm,
		    update_function_spec);
	    delete_frame(update_function_spec);
	    old_name_and_info = Nil;
	    ab_loop_list_ = Names_and_info_for_chaining;
	    old_name = Nil;
	    old_link = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    old_name_and_info = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    old_name = CAR(old_name_and_info);
	    old_link = CDR(old_name_and_info);
	    chaining_link = Nil;
	    ab_loop_list__1 = lookup_kb_specific_property_value(old_name,
		    Forward_chaining_list_kbprop);
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_1;
	    chaining_link = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    if (equal_forward_chaining_link(old_link,chaining_link)) {
		temp = old_name;
		temp_1 = delete_eval_element_1(chaining_link,
			lookup_kb_specific_property_value(old_name,
			Forward_chaining_list_kbprop));
		mutate_kb_specific_property_value(temp,temp_1,
			Forward_chaining_list_kbprop);
		delete_frame(chaining_link);
	    }
	    goto next_loop_1;
	  end_loop_1:;
	    delete_frame(old_link);
	    reclaim_slot_value_cons_1(old_name_and_info);
	    goto next_loop;
	  end_loop:;
	    reclaim_slot_value_list_1(Names_and_info_for_chaining);
	  POP_SPECIAL();
      }
      if (new_expression_qm) {
	  names_and_info_for_chaining = Nil;
	  update_function_spec = 
		  make_true_value_update_recipient(update_function,
		  frame_qm,extra_argument);
	  PUSH_SPECIAL_WITH_SYMBOL(Names_and_info_for_chaining,Qnames_and_info_for_chaining,names_and_info_for_chaining,
		  0);
	    note_names_and_info_for_true_value_chaining_in_expression(new_expression_qm,
		    update_function_spec);
	    delete_frame(update_function_spec);
	    new_name_and_info = Nil;
	    ab_loop_list_ = Names_and_info_for_chaining;
	    new_name = Nil;
	    new_link = Nil;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    new_name_and_info = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    new_name = CAR(new_name_and_info);
	    new_link = CDR(new_name_and_info);
	    mutate_kb_specific_property_value(new_name,
		    eval_cons_1(new_link,
		    lookup_kb_specific_property_value(new_name,
		    Forward_chaining_list_kbprop)),
		    Forward_chaining_list_kbprop);
	    reclaim_slot_value_cons_1(new_name_and_info);
	    goto next_loop_2;
	  end_loop_2:;
	    result = reclaim_slot_value_list_1(Names_and_info_for_chaining);
	  POP_SPECIAL();
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* GENERATE-CELL-CHAINING-LINKS */
Object generate_cell_chaining_links(update_function,frame_qm,
	    extra_argument,expression)
    Object update_function, frame_qm, extra_argument, expression;
{
    Object names_and_info_for_chaining, update_function_spec;
    Declare_special(1);
    Object result;

    x_note_fn_call(153,111);
    names_and_info_for_chaining = Nil;
    update_function_spec = 
	    make_true_value_update_recipient(update_function,frame_qm,
	    extra_argument);
    PUSH_SPECIAL_WITH_SYMBOL(Names_and_info_for_chaining,Qnames_and_info_for_chaining,names_and_info_for_chaining,
	    0);
      note_names_and_info_for_cell_chaining_in_expression(expression,
	      update_function_spec);
      delete_frame(update_function_spec);
      result = VALUES_1(Names_and_info_for_chaining);
    POP_SPECIAL();
    return result;
}

/* REDIRECT-CHAINING-LINK-RECIPIENT */
Object redirect_chaining_link_recipient(forward_chaining_link,frame)
    Object forward_chaining_link, frame;
{
    Object recipient, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(153,112);
    recipient = ISVREF(forward_chaining_link,(SI_Long)2L);
    if (recipient) {
	sub_class_bit_vector = ISVREF(ISVREF(recipient,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(True_value_update_recipient_class_description,
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
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	if (Noting_changes_to_kb_p)
	    note_change_to_dependent_frame_1();
	return VALUES_1(SVREF(recipient,FIX((SI_Long)3L)) = frame);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_28;  /* "Notifying ~NF that ~NF has been forced to have no current value." */

/* INVOKE-UPDATE-FUNCTIONS-FOR-PUT-HAS-NO-CURRENT-VALUE */
Object invoke_update_functions_for_put_has_no_current_value(variable,old_value)
    Object variable, old_value;
{
    Object links_and_objects, gensymed_symbol, structure_being_reclaimed, temp;
    Object temp_1, link_entry, ab_loop_list_, link_1, recipient, last_1;
    Object next_qm, svref_new_value;
    Declare_special(2);

    x_note_fn_call(153,113);
    links_and_objects = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Links_and_objects,Qlinks_and_objects,links_and_objects,
	    1);
      gensymed_symbol = Nil;
    next_loop:
      gensymed_symbol = ISVREF(variable,(SI_Long)39L);
      if (CAS_SVREF(variable,(SI_Long)39L,gensymed_symbol,Nil)) {
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
	      temp_1 = Current_thread_index;
	      SVREF(temp,temp_1) = gensymed_symbol;
	  }
	  goto end_1;
      }
      goto next_loop;
    end_loop:
    end_1:;
      collect_links_for_put_has_no_current_value(variable);
      link_entry = Nil;
      ab_loop_list_ = Links_and_objects;
      link_1 = Nil;
      recipient = Nil;
    next_loop_1:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop_1;
      link_entry = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      link_1 = M_CAR(link_entry);
      recipient = ISVREF(link_1,(SI_Long)2L);
      if (ISVREF(recipient,(SI_Long)3L)) {
	  if ((IFIX(Tracing_message_level) > (SI_Long)1L || 
		  IFIX(Breakpoint_level) > (SI_Long)1L) &&  
		  !TRUEP(Debugging_reset) && ISVREF(Debugging_parameters,
		  (SI_Long)22L))
	      tformat_major_trace_message_1(string_constant_28,
		      ISVREF(recipient,(SI_Long)3L),variable,Nil,Nil,Nil,
		      Nil,Nil,Nil,Nil);
      }
      funcall(7,SYMBOL_FUNCTION(ISVREF(recipient,(SI_Long)2L)),
	      ISVREF(recipient,(SI_Long)3L),ISVREF(recipient,(SI_Long)4L),
	      variable,Nil,old_value,Nil);
      inline_note_reclaim_cons(link_entry,Qeval);
      if (ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	  temp = ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index));
	  M_CDR(temp) = link_entry;
	  temp = Available_eval_conses_tail_vector;
	  temp_1 = Current_thread_index;
	  SVREF(temp,temp_1) = link_entry;
      }
      else {
	  temp = Available_eval_conses_vector;
	  temp_1 = Current_thread_index;
	  SVREF(temp,temp_1) = link_entry;
	  temp = Available_eval_conses_tail_vector;
	  temp_1 = Current_thread_index;
	  SVREF(temp,temp_1) = link_entry;
      }
      M_CDR(link_entry) = Nil;
      goto next_loop_1;
    end_loop_1:;
      if (Links_and_objects) {
	  last_1 = Links_and_objects;
	  next_qm = Nil;
	next_loop_2:
	  next_qm = M_CDR(last_1);
	  if ( !TRUEP(next_qm))
	      goto end_loop_2;
	  inline_note_reclaim_cons(last_1,Qeval);
	  last_1 = next_qm;
	  goto next_loop_2;
	end_loop_2:
	  inline_note_reclaim_cons(last_1,Qeval);
	  if (ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	      temp = ISVREF(Available_eval_conses_tail_vector,
		      IFIX(Current_thread_index));
	      temp_1 = Links_and_objects;
	      M_CDR(temp) = temp_1;
	      temp = Available_eval_conses_tail_vector;
	      temp_1 = Current_thread_index;
	      SVREF(temp,temp_1) = last_1;
	  }
	  else {
	      temp = Available_eval_conses_vector;
	      temp_1 = Current_thread_index;
	      svref_new_value = Links_and_objects;
	      SVREF(temp,temp_1) = svref_new_value;
	      temp = Available_eval_conses_tail_vector;
	      temp_1 = Current_thread_index;
	      SVREF(temp,temp_1) = last_1;
	  }
	  M_CDR(last_1) = Nil;
      }
    POP_SPECIAL();
    return invoke_rules_for_existential_chaining(variable,Qloses_its_value,
	    Nil);
}

static Object string_constant_29;  /* "Notifying ~NF that the value of ~NF has expired." */

/* INVOKE-UPDATE-FUNCTIONS-FOR-EXPIRED-VALUE */
Object invoke_update_functions_for_expired_value(variable,old_value)
    Object variable, old_value;
{
    Object links_and_objects, gensymed_symbol, structure_being_reclaimed, temp;
    Object temp_1, link_entry, ab_loop_list_, link_1, recipient, last_1;
    Object next_qm, svref_new_value;
    Declare_special(2);

    x_note_fn_call(153,114);
    links_and_objects = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Links_and_objects,Qlinks_and_objects,links_and_objects,
	    1);
      gensymed_symbol = Nil;
    next_loop:
      gensymed_symbol = ISVREF(variable,(SI_Long)39L);
      if (CAS_SVREF(variable,(SI_Long)39L,gensymed_symbol,Nil)) {
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
	      temp_1 = Current_thread_index;
	      SVREF(temp,temp_1) = gensymed_symbol;
	  }
	  goto end_1;
      }
      goto next_loop;
    end_loop:
    end_1:;
      collect_links_for_put_has_no_current_value(variable);
      link_entry = Nil;
      ab_loop_list_ = Links_and_objects;
      link_1 = Nil;
      recipient = Nil;
    next_loop_1:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop_1;
      link_entry = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      link_1 = M_CAR(link_entry);
      recipient = ISVREF(link_1,(SI_Long)2L);
      if (ISVREF(recipient,(SI_Long)3L)) {
	  if ((IFIX(Tracing_message_level) > (SI_Long)1L || 
		  IFIX(Breakpoint_level) > (SI_Long)1L) &&  
		  !TRUEP(Debugging_reset) && ISVREF(Debugging_parameters,
		  (SI_Long)22L))
	      tformat_major_trace_message_1(string_constant_29,
		      ISVREF(recipient,(SI_Long)3L),variable,Nil,Nil,Nil,
		      Nil,Nil,Nil,Nil);
      }
      funcall(7,SYMBOL_FUNCTION(ISVREF(recipient,(SI_Long)2L)),
	      ISVREF(recipient,(SI_Long)3L),ISVREF(recipient,(SI_Long)4L),
	      variable,Nil,old_value,Nil);
      inline_note_reclaim_cons(link_entry,Qeval);
      if (ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	  temp = ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index));
	  M_CDR(temp) = link_entry;
	  temp = Available_eval_conses_tail_vector;
	  temp_1 = Current_thread_index;
	  SVREF(temp,temp_1) = link_entry;
      }
      else {
	  temp = Available_eval_conses_vector;
	  temp_1 = Current_thread_index;
	  SVREF(temp,temp_1) = link_entry;
	  temp = Available_eval_conses_tail_vector;
	  temp_1 = Current_thread_index;
	  SVREF(temp,temp_1) = link_entry;
      }
      M_CDR(link_entry) = Nil;
      goto next_loop_1;
    end_loop_1:;
      if (Links_and_objects) {
	  last_1 = Links_and_objects;
	  next_qm = Nil;
	next_loop_2:
	  next_qm = M_CDR(last_1);
	  if ( !TRUEP(next_qm))
	      goto end_loop_2;
	  inline_note_reclaim_cons(last_1,Qeval);
	  last_1 = next_qm;
	  goto next_loop_2;
	end_loop_2:
	  inline_note_reclaim_cons(last_1,Qeval);
	  if (ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	      temp = ISVREF(Available_eval_conses_tail_vector,
		      IFIX(Current_thread_index));
	      temp_1 = Links_and_objects;
	      M_CDR(temp) = temp_1;
	      temp = Available_eval_conses_tail_vector;
	      temp_1 = Current_thread_index;
	      SVREF(temp,temp_1) = last_1;
	  }
	  else {
	      temp = Available_eval_conses_vector;
	      temp_1 = Current_thread_index;
	      svref_new_value = Links_and_objects;
	      SVREF(temp,temp_1) = svref_new_value;
	      temp = Available_eval_conses_tail_vector;
	      temp_1 = Current_thread_index;
	      SVREF(temp,temp_1) = last_1;
	  }
	  M_CDR(last_1) = Nil;
      }
    POP_SPECIAL();
    return invoke_rules_for_existential_chaining(variable,Qloses_its_value,
	    Nil);
}

/* COLLECT-LINKS-FOR-PUT-HAS-NO-CURRENT-VALUE */
Object collect_links_for_put_has_no_current_value(object)
    Object object;
{
    Object object_names_qm, object_name_cons_qm, temp, temp_1;
    Object parent_attribute_slot_description, parent_attribute_qm, object_name;
    Object ab_loop_list_, link_1, list_1, ab_loop_list__1;
    Object sub_class_bit_vector, new_cons, temp_3, svref_arg_2;
    Object svref_new_value, gensymed_symbol_3, new_value, old_value;
    Object class_description, classes, cache_qm, class_1, specific_list;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_2;

    x_note_fn_call(153,115);
    object_names_qm = get_lookup_slot_value_given_default(object,
	    Qname_or_names_for_frame,Nil);
    if (object_names_qm && SYMBOLP(object_names_qm)) {
	object_names_qm = eval_cons_1(object_names_qm,Nil);
	object_name_cons_qm = object_names_qm;
    }
    else
	object_name_cons_qm = Nil;
    temp = get_lookup_slot_value_given_default(object,
	    Qparent_attribute_name,Nil);
    if (CONSP(temp)) {
	temp_1 = M_CAR(get_lookup_slot_value_given_default(object,
		Qparent_attribute_name,Nil));
	temp = ISVREF(get_lookup_slot_value_given_default(object,
		Qparent_frame,Nil),(SI_Long)1L);
	parent_attribute_slot_description = 
		get_slot_description_of_class_description_function(temp_1,
		temp,M_CDR(get_lookup_slot_value_given_default(object,
		Qparent_attribute_name,Nil)));
	parent_attribute_qm = ISVREF(parent_attribute_slot_description,
		(SI_Long)1L);
    }
    else
	parent_attribute_qm = get_lookup_slot_value_given_default(object,
		Qparent_attribute_name,Nil);
    object_name = Nil;
    ab_loop_list_ = object_names_qm;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    object_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    link_1 = Nil;
    list_1 = INLINE_SYMBOL_PLIST(object_name);
  next_loop_1:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop_1;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_1;
  end_loop_1:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_2:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Forward_chaining_list_kbprop))
	goto end_loop_2;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_2;
  end_loop_2:
    ab_loop_list__1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_3:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_3;
    link_1 = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    sub_class_bit_vector = ISVREF(ISVREF(link_1,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(True_value_update_recipient_class_description,
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
	temp_2 = (SI_Long)0L < gensymed_symbol;
    }
    else
	temp_2 = TRUEP(Nil);
    if ((temp_2 ? EQ(ISVREF(link_1,(SI_Long)7L),Qreceives_a_value) : 
	    TRUEP(Nil)) ? EQ(object_name,ISVREF(link_1,(SI_Long)3L)) : 
	    TRUEP(Nil)) {
	new_cons = ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_3 = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_3,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_3 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_3,svref_arg_2) = Nil;
	    }
	    gensymed_symbol_3 = new_cons;
	}
	else
	    gensymed_symbol_3 = Nil;
	if ( !TRUEP(gensymed_symbol_3))
	    gensymed_symbol_3 = replenish_eval_cons_pool();
	M_CAR(gensymed_symbol_3) = link_1;
	M_CDR(gensymed_symbol_3) = Nil;
	inline_note_allocate_cons(gensymed_symbol_3,Qeval);
	new_value = eval_cons_1(gensymed_symbol_3,Nil);
	old_value = Nil;
      next_loop_4:
	old_value = Links_and_objects;
	M_CDR(new_value) = old_value;
	if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value))
	    goto end_loop_4;
	goto next_loop_4;
      end_loop_4:
	goto end_1;
      end_1:;
    }
    goto next_loop_3;
  end_loop_3:;
    goto next_loop;
  end_loop:;
    if (parent_attribute_qm) {
	link_1 = Nil;
	list_1 = INLINE_SYMBOL_PLIST(parent_attribute_qm);
      next_loop_5:
	if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
		Current_kb_specific_property_list_property_name))
	    goto end_loop_5;
	list_1 = M_CDR(M_CDR(list_1));
	goto next_loop_5;
      end_loop_5:
	list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
      next_loop_6:
	if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Forward_chaining_list_kbprop))
	    goto end_loop_6;
	list_1 = M_CDR(M_CDR(list_1));
	goto next_loop_6;
      end_loop_6:
	ab_loop_list_ = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
      next_loop_7:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_7;
	link_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	sub_class_bit_vector = ISVREF(ISVREF(link_1,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(True_value_update_recipient_class_description,
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
	    temp_2 = (SI_Long)0L < gensymed_symbol;
	}
	else
	    temp_2 = TRUEP(Nil);
	if ((temp_2 ? EQ(ISVREF(link_1,(SI_Long)7L),Qreceives_a_value) : 
		TRUEP(Nil)) ? 
		TRUEP(designation_denotes_item_p(ISVREF(link_1,
		(SI_Long)3L),object)) : TRUEP(Nil)) {
	    new_cons = ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp_3 = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp_3,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_eval_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp_3 = Available_eval_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_3,svref_arg_2) = Nil;
		}
		gensymed_symbol_3 = new_cons;
	    }
	    else
		gensymed_symbol_3 = Nil;
	    if ( !TRUEP(gensymed_symbol_3))
		gensymed_symbol_3 = replenish_eval_cons_pool();
	    M_CAR(gensymed_symbol_3) = link_1;
	    M_CDR(gensymed_symbol_3) = Nil;
	    inline_note_allocate_cons(gensymed_symbol_3,Qeval);
	    new_value = eval_cons_1(gensymed_symbol_3,Nil);
	    old_value = Nil;
	  next_loop_8:
	    old_value = Links_and_objects;
	    M_CDR(new_value) = old_value;
	    if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value))
		goto end_loop_8;
	    goto next_loop_8;
	  end_loop_8:
	    goto end_2;
	  end_2:;
	}
	goto next_loop_7;
      end_loop_7:;
    }
    link_1 = Nil;
    class_description = ISVREF(object,(SI_Long)1L);
    classes = ISVREF(class_description,(SI_Long)2L);
    gensymed_symbol_3 = M_CAR(classes);
    list_1 = INLINE_SYMBOL_PLIST(gensymed_symbol_3);
  next_loop_9:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop_9;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_9;
  end_loop_9:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_10:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Cached_class_forward_chaining_list_kbprop))
	goto end_loop_10;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_10;
  end_loop_10:
    cache_qm = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    if (cache_qm)
	ab_loop_list_ = M_CDR(cache_qm);
    else {
	class_1 = Nil;
	ab_loop_list_ = classes;
	specific_list = Nil;
      next_loop_11:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_11;
	class_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	specific_list = lookup_kb_specific_property_value(class_1,
		Forward_chaining_list_kbprop);
	if (specific_list) {
	    specific_list = copy_list_using_eval_conses_1(specific_list);
	    if (cache_qm)
		cache_qm = nconc2(cache_qm,specific_list);
	    else
		cache_qm = specific_list;
	}
	if (EQ(class_1,Qitem))
	    goto end_loop_11;
	goto next_loop_11;
      end_loop_11:
	mutate_kb_specific_property_value(M_CAR(classes),eval_cons_1(Nil,
		cache_qm),Cached_class_forward_chaining_list_kbprop);
	new_value = eval_cons_1(M_CAR(classes),Nil);
	old_value = Nil;
      next_loop_12:
	old_value = Cached_classes_for_forward_chaining;
	M_CDR(new_value) = old_value;
	if (CAS_SYMBOL(Qcached_classes_for_forward_chaining,old_value,
		new_value))
	    goto end_loop_12;
	goto next_loop_12;
      end_loop_12:
	goto end_3;
      end_3:;
	ab_loop_list_ = cache_qm;
	goto end_4;
	ab_loop_list_ = Qnil;
      end_4:;
    }
  next_loop_13:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_13;
    link_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    sub_class_bit_vector = ISVREF(ISVREF(link_1,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(True_value_update_recipient_class_description,
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
	temp_2 = (SI_Long)0L < gensymed_symbol;
    }
    else
	temp_2 = TRUEP(Nil);
    if ((temp_2 ? EQ(ISVREF(link_1,(SI_Long)7L),Qreceives_a_value) : 
	    TRUEP(Nil)) ? TRUEP(designation_denotes_item_p(ISVREF(link_1,
	    (SI_Long)3L),object)) : TRUEP(Nil)) {
	new_cons = ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_3 = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_3,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_3 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_3,svref_arg_2) = Nil;
	    }
	    gensymed_symbol_3 = new_cons;
	}
	else
	    gensymed_symbol_3 = Nil;
	if ( !TRUEP(gensymed_symbol_3))
	    gensymed_symbol_3 = replenish_eval_cons_pool();
	M_CAR(gensymed_symbol_3) = link_1;
	M_CDR(gensymed_symbol_3) = Nil;
	inline_note_allocate_cons(gensymed_symbol_3,Qeval);
	new_value = eval_cons_1(gensymed_symbol_3,Nil);
	old_value = Nil;
      next_loop_14:
	old_value = Links_and_objects;
	M_CDR(new_value) = old_value;
	if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value))
	    goto end_loop_14;
	goto next_loop_14;
      end_loop_14:
	goto end_5;
      end_5:;
    }
    goto next_loop_13;
  end_loop_13:;
    if (object_name_cons_qm) {
	inline_note_reclaim_cons(object_name_cons_qm,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_3 = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_3) = object_name_cons_qm;
	    temp_3 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_3,svref_arg_2) = object_name_cons_qm;
	}
	else {
	    temp_3 = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_3,svref_arg_2) = object_name_cons_qm;
	    temp_3 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_3,svref_arg_2) = object_name_cons_qm;
	}
	M_CDR(object_name_cons_qm) = Nil;
    }
    return VALUES_1(Nil);
}

static Object string_constant_30;  /* "Executing update for ~NF because a new value was placed ~?
				    *                  in the ~a of ~NF."
				    */

/* INVOKE-RULES-FOR-ATTRIBUTE-CHANGE-CHAINING */
Object invoke_rules_for_attribute_change_chaining(parent_frame,
	    attribute_name,old_value,class_if_specific_qm)
    Object parent_frame, attribute_name, old_value, class_if_specific_qm;
{
    Object links_and_objects, trailer, link_entry_cons, link_entry, link_1;
    Object recipient, sub_class_bit_vector, temp_1, role_qm, local_name_qm;
    Object object_qm, temp_2, temp_3, eval_cons, svref_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(1);

    x_note_fn_call(153,116);
    links_and_objects = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Links_and_objects,Qlinks_and_objects,links_and_objects,
	    0);
      collect_links_for_attribute_change_chaining(parent_frame,attribute_name);
      if (Links_and_objects) {
	  trailer = Nil;
	  link_entry_cons = Links_and_objects;
	  link_entry = Nil;
	  link_1 = Nil;
	  recipient = Nil;
	next_loop:
	  if ( !TRUEP(link_entry_cons))
	      goto end_loop;
	  link_entry = M_CAR(link_entry_cons);
	  link_1 = M_CAR(link_entry);
	  recipient = ISVREF(link_1,(SI_Long)2L);
	  sub_class_bit_vector = ISVREF(ISVREF(recipient,(SI_Long)1L),
		  (SI_Long)19L);
	  superior_class_bit_number = 
		  IFIX(ISVREF(True_value_update_recipient_class_description,
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
	      if (designation_denotes_item_p(domain_of_designation(ISVREF(link_1,
		      (SI_Long)3L)),parent_frame)) {
		  if (ISVREF(recipient,(SI_Long)3L)) {
		      if ((IFIX(Tracing_message_level) > (SI_Long)1L || 
			      IFIX(Breakpoint_level) > (SI_Long)1L) &&  
			      !TRUEP(Debugging_reset) && 
			      ISVREF(Debugging_parameters,(SI_Long)22L))
			  tformat_major_trace_message_1(string_constant_30,
				  ISVREF(recipient,(SI_Long)3L),
				  attribute_name,parent_frame,Nil,Nil,Nil,
				  Nil,Nil,Nil);
		  }
		  funcall(7,SYMBOL_FUNCTION(ISVREF(recipient,(SI_Long)2L)),
			  ISVREF(recipient,(SI_Long)3L),ISVREF(recipient,
			  (SI_Long)4L),parent_frame,attribute_name,
			  old_value,class_if_specific_qm);
	      }
	  }
	  else {
	      temp_1 = ISVREF(recipient,(SI_Long)8L);
	      if ( !TRUEP(CAR(temp_1)) && ((SI_Long)0L != 
		      (IFIX(ISVREF(recipient,(SI_Long)5L)) & (SI_Long)1L) 
		      ||  !TRUEP(Inside_breakpoint_p) && (SI_Long)0L != 
		      (IFIX(ISVREF(recipient,(SI_Long)4L)) & 
		      (SI_Long)16777216L) &&  !((SI_Long)0L != 
		      (IFIX(ISVREF(recipient,(SI_Long)4L)) & 
		      (SI_Long)8192L))) &&  !TRUEP(Reading_kb_p)) {
		  role_qm = ISVREF(link_1,(SI_Long)4L);
		  local_name_qm = role_qm ? ISVREF(link_1,(SI_Long)5L) : Nil;
		  object_qm = role_qm ? CDR(link_entry) : Nil;
		  if ((IFIX(Tracing_message_level) > (SI_Long)1L || 
			  IFIX(Breakpoint_level) > (SI_Long)1L) &&  
			  !TRUEP(Debugging_reset) && 
			  ISVREF(Debugging_parameters,(SI_Long)22L))
		      write_major_attribute_chaining_message(recipient,
			      parent_frame,attribute_name,local_name_qm,
			      role_qm,object_qm);
		  generate_and_schedule_rule_instances(recipient,role_qm,
			  local_name_qm,object_qm,Qforward_chaining,Nil,
			  ISVREF(recipient,(SI_Long)26L),Nil);
	      }
	  }
	  inline_note_reclaim_cons(link_entry,Qeval);
	  if (ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	      temp_2 = ISVREF(Available_eval_conses_tail_vector,
		      IFIX(Current_thread_index));
	      M_CDR(temp_2) = link_entry;
	      temp_2 = Available_eval_conses_tail_vector;
	      temp_3 = Current_thread_index;
	      SVREF(temp_2,temp_3) = link_entry;
	  }
	  else {
	      temp_2 = Available_eval_conses_vector;
	      temp_3 = Current_thread_index;
	      SVREF(temp_2,temp_3) = link_entry;
	      temp_2 = Available_eval_conses_tail_vector;
	      temp_3 = Current_thread_index;
	      SVREF(temp_2,temp_3) = link_entry;
	  }
	  M_CDR(link_entry) = Nil;
	  trailer = link_entry_cons;
	  link_entry_cons = M_CDR(link_entry_cons);
	  goto next_loop;
	end_loop:
	  if (Links_and_objects &&  !((SI_Long)0L == 
		  inline_debugging_consing())) {
	      eval_cons = Links_and_objects;
	    next_loop_1:
	      inline_note_reclaim_cons(eval_cons,Qeval);
	      if (EQ(eval_cons,trailer))
		  goto end_1;
	      else if ( !TRUEP(eval_cons))
		  goto end_1;
	      else
		  eval_cons = CDR(eval_cons);
	      goto next_loop_1;
	    end_loop_1:
	    end_1:;
	  }
	  if (ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	      temp_2 = ISVREF(Available_eval_conses_tail_vector,
		      IFIX(Current_thread_index));
	      temp_3 = Links_and_objects;
	      M_CDR(temp_2) = temp_3;
	      temp_2 = Available_eval_conses_tail_vector;
	      temp_3 = Current_thread_index;
	      SVREF(temp_2,temp_3) = trailer;
	  }
	  else {
	      temp_2 = Available_eval_conses_vector;
	      temp_3 = Current_thread_index;
	      svref_new_value = Links_and_objects;
	      SVREF(temp_2,temp_3) = svref_new_value;
	      temp_2 = Available_eval_conses_tail_vector;
	      temp_3 = Current_thread_index;
	      SVREF(temp_2,temp_3) = trailer;
	  }
	  M_CDR(trailer) = Nil;
      }
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object string_constant_31;  /* "Scheduling forward chaining to ~NF with ~NF as ~?
				    *              the ~A with local name ~A because a new value ~?
				    *              was placed in the ~A of ~NF."
				    */

static Object string_constant_32;  /* "Scheduling forward chaining to ~NF with ~NF as the ~A ~?
				    *              because a new value was placed in the ~A of ~NF."
				    */

static Object string_constant_33;  /* "Scheduling forward chaining to ~NF because a new value was ~?
				    *          placed in the ~A of ~NF."
				    */

/* WRITE-MAJOR-ATTRIBUTE-CHAINING-MESSAGE */
Object write_major_attribute_chaining_message(recipient,parent_frame,
	    attribute_name,local_name_qm,role_qm,object_qm)
    Object recipient, parent_frame, attribute_name, local_name_qm, role_qm;
    Object object_qm;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object gensymed_symbol;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(153,117);
    if ((IFIX(Tracing_message_level) > (SI_Long)1L || 
	    IFIX(Breakpoint_level) > (SI_Long)1L) &&  
	    !TRUEP(Debugging_reset) && ISVREF(Debugging_parameters,
	    (SI_Long)22L)) {
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
		  if (role_qm) {
		      if (local_name_qm)
			  tformat(7,string_constant_31,recipient,object_qm,
				  role_qm,local_name_qm,attribute_name,
				  parent_frame);
		      else
			  tformat(6,string_constant_32,recipient,object_qm,
				  role_qm,attribute_name,parent_frame);
		  }
		  else
		      tformat(4,string_constant_33,recipient,
			      attribute_name,parent_frame);
		  gensymed_symbol = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return write_major_trace_message_function(gensymed_symbol);
    }
    else
	return VALUES_1(Nil);
}

static Object Qregistered_event_detectors;  /* registered-event-detectors */

/* CHAIN-FORWARD-FOR-ATTRIBUTE-IF-NECESSARY */
Object chain_forward_for_attribute_if_necessary(frame,attribute_name,
	    defining_class_qm)
    Object frame, attribute_name, defining_class_qm;
{
    Object lookup_structure_qm, slot_index_qm, list_1;
    Object current_computation_frame;
    SI_Long max_i, i, ab_loop_bind_;
    char temp;
    Declare_special(1);

    x_note_fn_call(153,118);
    lookup_structure_qm = ISVREF(frame,(SI_Long)0L);
    if (lookup_structure_qm) {
	max_i = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(lookup_structure_qm));
	max_i = max_i - (SI_Long)1L;
	i = IFIX(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)15L));
	ab_loop_bind_ = max_i;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	if (EQ(ISVREF(lookup_structure_qm,i),Qregistered_event_detectors)) {
	    slot_index_qm = FIX(i + (SI_Long)1L);
	    goto end_1;
	}
	i = i + (SI_Long)2L;
	goto next_loop;
      end_loop:
	slot_index_qm = Qnil;
      end_1:;
	temp = slot_index_qm ? TRUEP(ISVREF(lookup_structure_qm,
		IFIX(slot_index_qm))) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Qnil);
    if (temp);
    else {
	list_1 = INLINE_SYMBOL_PLIST(attribute_name);
      next_loop_1:
	if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
		Current_kb_specific_property_list_property_name))
	    goto end_loop_1;
	list_1 = M_CDR(M_CDR(list_1));
	goto next_loop_1;
      end_loop_1:
	list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
      next_loop_2:
	if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Forward_chaining_list_kbprop))
	    goto end_loop_2;
	list_1 = M_CDR(M_CDR(list_1));
	goto next_loop_2;
      end_loop_2:
	temp = list_1 ? TRUEP(M_CAR(M_CDR(list_1))) : TRUEP(Nil);
    }
    if (temp) {
	if (Current_computation_frame)
	    invoke_rules_for_attribute_change_chaining(frame,
		    attribute_name,Nil,defining_class_qm);
	else {
	    current_computation_frame = frame;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		    0);
	      invoke_rules_for_attribute_change_chaining(frame,
		      attribute_name,Nil,defining_class_qm);
	    POP_SPECIAL();
	}
    }
    return VALUES_1(Nil);
}

/* COLLECT-LINKS-FOR-ATTRIBUTE-CHANGE-CHAINING */
Object collect_links_for_attribute_change_chaining(parent_frame,attribute_name)
    Object parent_frame, attribute_name;
{
    Object event_detectors, event_detector, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, triggerable_event_detectors;
    Object eval_pop_store, cons_1, next_cons, temp, svref_arg_2;
    Object parent_names_qm, parent_name_cons_qm, parent_stack, link_1, list_1;
    Object stored_sense, gensymed_symbol, temp_1, gensymed_symbol_1;
    Object svref_new_value, frame_to_chain_qm, new_cons, new_value, old_value;

    x_note_fn_call(153,119);
    event_detectors = ISVREF(parent_frame,(SI_Long)15L);
    if (event_detectors) {
	event_detector = Nil;
	ab_loop_list_ = event_detectors;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	event_detector = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(ISVREF(event_detector,(SI_Long)1L),Qreceives_a_value) && 
		EQ(ISVREF(event_detector,(SI_Long)4L),attribute_name)) {
	    ab_loopvar__2 = eval_cons_1(event_detector,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	goto next_loop;
      end_loop:
	triggerable_event_detectors = ab_loopvar_;
	goto end_1;
	triggerable_event_detectors = Qnil;
      end_1:;
    }
    else
	triggerable_event_detectors = Nil;
    event_detector = Nil;
  next_loop_1:
    if ( !TRUEP(triggerable_event_detectors))
	goto end_loop_1;
    eval_pop_store = Nil;
    cons_1 = triggerable_event_detectors;
    if (cons_1) {
	eval_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    triggerable_event_detectors = next_cons;
    event_detector = eval_pop_store;
    trigger_event_detector(event_detector);
    goto next_loop_1;
  end_loop_1:;
    parent_names_qm = Nil;
    parent_name_cons_qm = Nil;
    parent_stack = Nil;
    link_1 = Nil;
    list_1 = INLINE_SYMBOL_PLIST(attribute_name);
  next_loop_2:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop_2;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_2;
  end_loop_2:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_3:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Forward_chaining_list_kbprop))
	goto end_loop_3;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_3;
  end_loop_3:
    ab_loop_list_ = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    stored_sense = Nil;
  next_loop_4:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_4;
    link_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    stored_sense = ISVREF(link_1,(SI_Long)7L);
    if (T && (EQ(stored_sense,Qeither) || EQ(stored_sense,T) ||  
	    !TRUEP(stored_sense)) || EQ(stored_sense,Qreceives_a_value) || 
	    EQ(stored_sense,Qloses_its_value)) {
	if ( !TRUEP(parent_stack)) {
	    parent_names_qm = 
		    get_lookup_slot_value_given_default(parent_frame,
		    Qname_or_names_for_frame,Nil);
	    parent_name_cons_qm = parent_names_qm && 
		    SYMBOLP(parent_names_qm) ? eval_cons_1(parent_names_qm,
		    Nil) : Nil;
	    gensymed_symbol = Nil;
	  next_loop_5:
	    temp_1 = ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index));
	    temp_1 = CDR(temp_1);
	    temp_1 = CDR(temp_1);
	    gensymed_symbol = CDR(temp_1);
	    if (gensymed_symbol)
		goto end_loop_5;
	    replenish_eval_list_pool(FIX((SI_Long)3L));
	    goto next_loop_5;
	  end_loop_5:
	    if ( !((SI_Long)0L == inline_debugging_consing())) {
		gensymed_symbol_1 = ISVREF(Available_eval_conses_vector,
			IFIX(Current_thread_index));
	      next_loop_6:
		inline_note_allocate_cons(gensymed_symbol_1,Qeval);
		if (EQ(gensymed_symbol_1,gensymed_symbol))
		    goto end_loop_6;
		gensymed_symbol_1 = CDR(gensymed_symbol_1);
		goto next_loop_6;
	      end_loop_6:;
	    }
	    temp_1 = ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index));
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = CDR(gensymed_symbol);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    M_CDR(gensymed_symbol) = Nil;
	    gensymed_symbol = temp_1;
	    goto end_2;
	    gensymed_symbol = Qnil;
	  end_2:;
	    gensymed_symbol_1 = gensymed_symbol;
	    M_CAR(gensymed_symbol_1) = parent_frame;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = attribute_name;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    temp = parent_name_cons_qm;
	    if (temp);
	    else
		temp = parent_names_qm;
	    M_CAR(gensymed_symbol_1) = temp;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = parent_name_cons_qm;
	    parent_stack = eval_cons_1(gensymed_symbol,
		    make_parent_stack(parent_frame));
	}
	frame_to_chain_qm = find_referenced_parent(parent_stack,
		ISVREF(link_1,(SI_Long)3L));
	if (frame_to_chain_qm) {
	    new_cons = ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_eval_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp = Available_eval_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = Nil;
		}
		gensymed_symbol = new_cons;
	    }
	    else
		gensymed_symbol = Nil;
	    if ( !TRUEP(gensymed_symbol))
		gensymed_symbol = replenish_eval_cons_pool();
	    M_CAR(gensymed_symbol) = link_1;
	    M_CDR(gensymed_symbol) = frame_to_chain_qm;
	    inline_note_allocate_cons(gensymed_symbol,Qeval);
	    new_value = eval_cons_1(gensymed_symbol,Nil);
	    old_value = Nil;
	  next_loop_7:
	    old_value = Links_and_objects;
	    M_CDR(new_value) = old_value;
	    if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value))
		goto end_loop_7;
	    goto next_loop_7;
	  end_loop_7:
	    goto end_3;
	  end_3:;
	}
    }
    goto next_loop_4;
  end_loop_4:
    if (parent_stack)
	reclaim_parent_stack(parent_stack);
    return VALUES_1(Nil);
}

/* INVOKE-RULES-FOR-RELATION-CHAINING */
Object invoke_rules_for_relation_chaining(relation,subject,object,
	    adding_relation_qm)
    Object relation, subject, object, adding_relation_qm;
{
    Object x2, current_computation_frame_previously_bound_qm;
    Object object_parent_stack, links_and_objects, role_qm, local_name_qm;
    Object chain_object, second_designation, second_role_qm;
    Object second_local_name_qm, second_chain_object_qm, link_entry;
    Object ab_loop_list_, link_1, recipient, sub_class_bit_vector, temp_1;
    Object constraint_alist, eval_cons, temp_2, temp_3, last_1, next_qm;
    Object svref_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(153,120);
    if (SIMPLE_VECTOR_P(Current_computation_frame) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_computation_frame)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(Current_computation_frame,
	    (SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(Current_computation_frame,(SI_Long)1L);
	current_computation_frame_previously_bound_qm = 
		SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	current_computation_frame_previously_bound_qm = Nil;
    object_parent_stack = make_parent_stack(object);
    links_and_objects = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Links_and_objects,Qlinks_and_objects,links_and_objects,
	    0);
      if ( !TRUEP(current_computation_frame_previously_bound_qm))
	  Current_computation_frame = subject;
      collect_rules_for_relation_chaining(relation,subject,adding_relation_qm);
      role_qm = Nil;
      local_name_qm = Nil;
      chain_object = Nil;
      second_designation = Nil;
      second_role_qm = Nil;
      second_local_name_qm = Nil;
      second_chain_object_qm = Nil;
      link_entry = Nil;
      ab_loop_list_ = Links_and_objects;
      link_1 = Nil;
      recipient = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      link_entry = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      link_1 = CAR(link_entry);
      recipient = ISVREF(link_1,(SI_Long)2L);
      sub_class_bit_vector = ISVREF(ISVREF(recipient,(SI_Long)1L),
	      (SI_Long)19L);
      superior_class_bit_number = 
	      IFIX(ISVREF(True_value_update_recipient_class_description,
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
      if ( !temp) {
	  temp_1 = ISVREF(recipient,(SI_Long)8L);
	  temp =  !TRUEP(CAR(temp_1)) ? (SI_Long)0L != 
		  (IFIX(ISVREF(recipient,(SI_Long)5L)) & (SI_Long)1L) ||  
		  !TRUEP(Inside_breakpoint_p) && (SI_Long)0L != 
		  (IFIX(ISVREF(recipient,(SI_Long)4L)) & 
		  (SI_Long)16777216L) &&  !((SI_Long)0L != 
		  (IFIX(ISVREF(recipient,(SI_Long)4L)) & (SI_Long)8192L)) :
		   TRUEP(Nil);
      }
      else
	  temp = TRUEP(Nil);
      if (temp) {
	  role_qm = ISVREF(link_1,(SI_Long)4L);
	  local_name_qm = role_qm ? ISVREF(link_1,(SI_Long)5L) : Nil;
	  chain_object = role_qm ? CDR(link_entry) : Nil;
	  second_designation = ISVREF(link_1,(SI_Long)8L);
	  second_role_qm = ISVREF(link_1,(SI_Long)9L);
	  second_local_name_qm = second_role_qm ? ISVREF(link_1,
		  (SI_Long)10L) : Nil;
	  second_chain_object_qm = second_role_qm ? 
		  (SYMBOLP(second_role_qm) && 
		  domain_of_designation(second_designation) ? 
		  find_referenced_parent(object_parent_stack,
		  second_designation) : 
		  designation_could_denote_item_p(second_designation,
		  object) ? object : Nil) : Nil;
	  if ( !(second_role_qm ?  !TRUEP(second_chain_object_qm) : 
		  second_designation &&  
		  !TRUEP(designation_could_denote_item_p(second_designation,
		  object)))) {
	      if ((IFIX(Tracing_message_level) > (SI_Long)1L || 
		      IFIX(Breakpoint_level) > (SI_Long)1L) &&  
		      !TRUEP(Debugging_reset) && 
		      ISVREF(Debugging_parameters,(SI_Long)22L))
		  write_major_relation_chaining_trace_message(relation,
			  role_qm,second_role_qm,recipient,chain_object,
			  second_chain_object_qm,local_name_qm,
			  second_local_name_qm,adding_relation_qm,subject,
			  object);
	      if (role_qm && second_role_qm) {
		  temp_1 = second_local_name_qm;
		  if (temp_1);
		  else
		      temp_1 = second_role_qm;
		  constraint_alist = eval_cons_1(eval_cons_1(temp_1,
			  second_chain_object_qm),Nil);
		  generate_and_schedule_rule_instances(recipient,role_qm,
			  local_name_qm,chain_object,Qforward_chaining,Nil,
			  ISVREF(recipient,(SI_Long)26L),constraint_alist);
		  eval_cons = CAR(constraint_alist);
		  inline_note_reclaim_cons(eval_cons,Qeval);
		  if (ISVREF(Available_eval_conses_tail_vector,
			  IFIX(Current_thread_index))) {
		      temp_2 = ISVREF(Available_eval_conses_tail_vector,
			      IFIX(Current_thread_index));
		      M_CDR(temp_2) = eval_cons;
		      temp_2 = Available_eval_conses_tail_vector;
		      temp_3 = Current_thread_index;
		      SVREF(temp_2,temp_3) = eval_cons;
		  }
		  else {
		      temp_2 = Available_eval_conses_vector;
		      temp_3 = Current_thread_index;
		      SVREF(temp_2,temp_3) = eval_cons;
		      temp_2 = Available_eval_conses_tail_vector;
		      temp_3 = Current_thread_index;
		      SVREF(temp_2,temp_3) = eval_cons;
		  }
		  M_CDR(eval_cons) = Nil;
		  inline_note_reclaim_cons(constraint_alist,Qeval);
		  if (ISVREF(Available_eval_conses_tail_vector,
			  IFIX(Current_thread_index))) {
		      temp_2 = ISVREF(Available_eval_conses_tail_vector,
			      IFIX(Current_thread_index));
		      M_CDR(temp_2) = constraint_alist;
		      temp_2 = Available_eval_conses_tail_vector;
		      temp_3 = Current_thread_index;
		      SVREF(temp_2,temp_3) = constraint_alist;
		  }
		  else {
		      temp_2 = Available_eval_conses_vector;
		      temp_3 = Current_thread_index;
		      SVREF(temp_2,temp_3) = constraint_alist;
		      temp_2 = Available_eval_conses_tail_vector;
		      temp_3 = Current_thread_index;
		      SVREF(temp_2,temp_3) = constraint_alist;
		  }
		  M_CDR(constraint_alist) = Nil;
	      }
	      else if (role_qm)
		  generate_and_schedule_rule_instances(recipient,role_qm,
			  local_name_qm,chain_object,Qforward_chaining,Nil,
			  ISVREF(recipient,(SI_Long)26L),Nil);
	      else if (second_role_qm)
		  generate_and_schedule_rule_instances(recipient,
			  second_role_qm,second_local_name_qm,
			  second_chain_object_qm,Qforward_chaining,Nil,
			  ISVREF(recipient,(SI_Long)26L),Nil);
	      else
		  generate_and_schedule_rule_instances(recipient,Nil,Nil,
			  Nil,Qforward_chaining,Nil,ISVREF(recipient,
			  (SI_Long)26L),Nil);
	  }
      }
      inline_note_reclaim_cons(link_entry,Qeval);
      if (ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	  temp_2 = ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index));
	  M_CDR(temp_2) = link_entry;
	  temp_2 = Available_eval_conses_tail_vector;
	  temp_3 = Current_thread_index;
	  SVREF(temp_2,temp_3) = link_entry;
      }
      else {
	  temp_2 = Available_eval_conses_vector;
	  temp_3 = Current_thread_index;
	  SVREF(temp_2,temp_3) = link_entry;
	  temp_2 = Available_eval_conses_tail_vector;
	  temp_3 = Current_thread_index;
	  SVREF(temp_2,temp_3) = link_entry;
      }
      M_CDR(link_entry) = Nil;
      goto next_loop;
    end_loop:;
      if ( !TRUEP(current_computation_frame_previously_bound_qm))
	  Current_computation_frame = Nil;
      if (Links_and_objects) {
	  last_1 = Links_and_objects;
	  next_qm = Nil;
	next_loop_1:
	  next_qm = M_CDR(last_1);
	  if ( !TRUEP(next_qm))
	      goto end_loop_1;
	  inline_note_reclaim_cons(last_1,Qeval);
	  last_1 = next_qm;
	  goto next_loop_1;
	end_loop_1:
	  inline_note_reclaim_cons(last_1,Qeval);
	  if (ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	      temp_2 = ISVREF(Available_eval_conses_tail_vector,
		      IFIX(Current_thread_index));
	      temp_3 = Links_and_objects;
	      M_CDR(temp_2) = temp_3;
	      temp_2 = Available_eval_conses_tail_vector;
	      temp_3 = Current_thread_index;
	      SVREF(temp_2,temp_3) = last_1;
	  }
	  else {
	      temp_2 = Available_eval_conses_vector;
	      temp_3 = Current_thread_index;
	      svref_new_value = Links_and_objects;
	      SVREF(temp_2,temp_3) = svref_new_value;
	      temp_2 = Available_eval_conses_tail_vector;
	      temp_3 = Current_thread_index;
	      SVREF(temp_2,temp_3) = last_1;
	  }
	  M_CDR(last_1) = Nil;
      }
      result = reclaim_parent_stack(object_parent_stack);
    POP_SPECIAL();
    return result;
}

static Object string_constant_34;  /* "Scheduling chaining to ~NF with ~NF as ~A and ~NF as ~A ~?
				    *           because a ~A relation was ~a for these items."
				    */

static Object string_constant_35;  /* "established" */

static Object string_constant_36;  /* "removed" */

static Object string_constant_37;  /* "Scheduling chaining to ~NF with ~NF as ~A ~?
				    *           because a ~A relation was ~A for ~NF and ~NF."
				    */

static Object string_constant_38;  /* "Scheduling chaining to ~NF ~?
				    *           because a ~A relation was ~A for ~NF and ~NF."
				    */

/* WRITE-MAJOR-RELATION-CHAINING-TRACE-MESSAGE */
Object write_major_relation_chaining_trace_message(relation,role_qm,
	    second_role_qm,recipient,chain_object,second_chain_object_qm,
	    local_name_qm,second_local_name_qm,adding_relation_qm,subject,
	    object)
    Object relation, role_qm, second_role_qm, recipient, chain_object;
    Object second_chain_object_qm, local_name_qm, second_local_name_qm;
    Object adding_relation_qm, subject, object;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, temp_1, gensymed_symbol;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(153,121);
    if ((IFIX(Tracing_message_level) > (SI_Long)1L || 
	    IFIX(Breakpoint_level) > (SI_Long)1L) &&  
	    !TRUEP(Debugging_reset) && ISVREF(Debugging_parameters,
	    (SI_Long)22L)) {
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
		  if (role_qm && second_role_qm) {
		      temp = local_name_qm;
		      if (temp);
		      else
			  temp = role_qm;
		      temp_1 = second_local_name_qm;
		      if (temp_1);
		      else
			  temp_1 = role_qm;
		      tformat(8,string_constant_34,recipient,chain_object,
			      temp,second_chain_object_qm,temp_1,relation,
			      adding_relation_qm ? string_constant_35 : 
			      string_constant_36);
		  }
		  else if (role_qm) {
		      temp = local_name_qm;
		      if (temp);
		      else
			  temp = role_qm;
		      tformat(8,string_constant_37,recipient,chain_object,
			      temp,relation,adding_relation_qm ? 
			      string_constant_35 : string_constant_36,
			      subject,object);
		  }
		  else if (second_role_qm) {
		      temp = second_local_name_qm;
		      if (temp);
		      else
			  temp = second_role_qm;
		      tformat(8,string_constant_37,recipient,
			      second_chain_object_qm,temp,relation,
			      adding_relation_qm ? string_constant_35 : 
			      string_constant_36,subject,object);
		  }
		  else
		      tformat(6,string_constant_38,recipient,relation,
			      adding_relation_qm ? string_constant_35 : 
			      string_constant_36,subject,object);
		  gensymed_symbol = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return write_major_trace_message_function(gensymed_symbol);
    }
    else
	return VALUES_1(Nil);
}

/* COLLECT-RULES-FOR-RELATION-CHAINING */
Object collect_rules_for_relation_chaining(relation,subject,adding_relation_qm)
    Object relation, subject, adding_relation_qm;
{
    Object subject_names_qm, subject_name_cons_qm, parent_stack, subject_name;
    Object ab_loop_list_, link_1, ab_loop_list__1, gensymed_symbol, new_cons;
    Object temp_1, svref_arg_2, svref_new_value, new_value, old_value;
    Object parent_stack_entry, parent_frame_qm, class_description, classes;
    Object list_1, cache_qm, class_1, specific_list, designation, temp_2;
    char temp;

    x_note_fn_call(153,122);
    subject_names_qm = get_lookup_slot_value_given_default(subject,
	    Qname_or_names_for_frame,Nil);
    if (subject_names_qm && SYMBOLP(subject_names_qm)) {
	subject_names_qm = eval_cons_1(subject_names_qm,Nil);
	subject_name_cons_qm = subject_names_qm;
    }
    else
	subject_name_cons_qm = Nil;
    parent_stack = make_parent_stack(subject);
    subject_name = Nil;
    ab_loop_list_ = subject_names_qm;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    subject_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    link_1 = Nil;
    ab_loop_list__1 = lookup_kb_specific_property_value(subject_name,
	    Forward_chaining_list_kbprop);
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    link_1 = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if (EQ(Nil,ISVREF(link_1,(SI_Long)6L)) || EQ(relation,ISVREF(link_1,
	    (SI_Long)6L))) {
	gensymed_symbol = ISVREF(link_1,(SI_Long)7L);
	temp = EQ(gensymed_symbol,Krelated_change);
	if (temp);
	else
	    temp = adding_relation_qm ? EQ(gensymed_symbol,Krelated) : 
		    EQ(gensymed_symbol,Knot_related);
    }
    else
	temp = TRUEP(Nil);
    if (temp ? EQ(subject_name,ISVREF(link_1,(SI_Long)3L)) : TRUEP(Nil)) {
	new_cons = ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_eval_cons_pool();
	M_CAR(gensymed_symbol) = link_1;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qeval);
	new_value = eval_cons_1(gensymed_symbol,Nil);
	old_value = Nil;
      next_loop_2:
	old_value = Links_and_objects;
	M_CDR(new_value) = old_value;
	if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value))
	    goto end_loop_2;
	goto next_loop_2;
      end_loop_2:
	goto end_1;
      end_1:;
    }
    goto next_loop_1;
  end_loop_1:;
    goto next_loop;
  end_loop:;
    if (parent_stack) {
	parent_stack_entry = M_CAR(parent_stack);
	link_1 = Nil;
	gensymed_symbol = M_CAR(M_CDR(parent_stack_entry));
	ab_loop_list_ = 
		lookup_kb_specific_property_value(CONSP(gensymed_symbol) ? 
		M_CAR(gensymed_symbol) : gensymed_symbol,
		Forward_chaining_list_kbprop);
      next_loop_3:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_3;
	link_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(Nil,ISVREF(link_1,(SI_Long)6L)) || EQ(relation,
		ISVREF(link_1,(SI_Long)6L))) {
	    gensymed_symbol = ISVREF(link_1,(SI_Long)7L);
	    temp = EQ(gensymed_symbol,Krelated_change);
	    if (temp);
	    else
		temp = adding_relation_qm ? EQ(gensymed_symbol,Krelated) : 
			EQ(gensymed_symbol,Knot_related);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    parent_frame_qm = find_referenced_parent(parent_stack,
		    ISVREF(link_1,(SI_Long)3L));
	    if (parent_frame_qm) {
		new_cons = ISVREF(Available_eval_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    temp_1 = Available_eval_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(temp_1,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
			    IFIX(Current_thread_index)))) {
			temp_1 = Available_eval_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_1,svref_arg_2) = Nil;
		    }
		    gensymed_symbol = new_cons;
		}
		else
		    gensymed_symbol = Nil;
		if ( !TRUEP(gensymed_symbol))
		    gensymed_symbol = replenish_eval_cons_pool();
		M_CAR(gensymed_symbol) = link_1;
		M_CDR(gensymed_symbol) = parent_frame_qm;
		inline_note_allocate_cons(gensymed_symbol,Qeval);
		new_value = eval_cons_1(gensymed_symbol,Nil);
		old_value = Nil;
	      next_loop_4:
		old_value = Links_and_objects;
		M_CDR(new_value) = old_value;
		if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value))
		    goto end_loop_4;
		goto next_loop_4;
	      end_loop_4:
		goto end_2;
	      end_2:;
	    }
	}
	goto next_loop_3;
      end_loop_3:;
    }
    link_1 = Nil;
    class_description = ISVREF(subject,(SI_Long)1L);
    classes = ISVREF(class_description,(SI_Long)2L);
    gensymed_symbol = M_CAR(classes);
    list_1 = INLINE_SYMBOL_PLIST(gensymed_symbol);
  next_loop_5:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop_5;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_5;
  end_loop_5:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_6:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Cached_class_forward_chaining_list_kbprop))
	goto end_loop_6;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_6;
  end_loop_6:
    cache_qm = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    if (cache_qm)
	ab_loop_list_ = M_CDR(cache_qm);
    else {
	class_1 = Nil;
	ab_loop_list_ = classes;
	specific_list = Nil;
      next_loop_7:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_7;
	class_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	specific_list = lookup_kb_specific_property_value(class_1,
		Forward_chaining_list_kbprop);
	if (specific_list) {
	    specific_list = copy_list_using_eval_conses_1(specific_list);
	    if (cache_qm)
		cache_qm = nconc2(cache_qm,specific_list);
	    else
		cache_qm = specific_list;
	}
	if (EQ(class_1,Qitem))
	    goto end_loop_7;
	goto next_loop_7;
      end_loop_7:
	mutate_kb_specific_property_value(M_CAR(classes),eval_cons_1(Nil,
		cache_qm),Cached_class_forward_chaining_list_kbprop);
	new_value = eval_cons_1(M_CAR(classes),Nil);
	old_value = Nil;
      next_loop_8:
	old_value = Cached_classes_for_forward_chaining;
	M_CDR(new_value) = old_value;
	if (CAS_SYMBOL(Qcached_classes_for_forward_chaining,old_value,
		new_value))
	    goto end_loop_8;
	goto next_loop_8;
      end_loop_8:
	goto end_3;
      end_3:;
	ab_loop_list_ = cache_qm;
	goto end_4;
	ab_loop_list_ = Qnil;
      end_4:;
    }
    designation = Nil;
  next_loop_9:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_9;
    link_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    designation = ISVREF(link_1,(SI_Long)3L);
    if (EQ(Nil,ISVREF(link_1,(SI_Long)6L)) || EQ(relation,ISVREF(link_1,
	    (SI_Long)6L))) {
	gensymed_symbol = ISVREF(link_1,(SI_Long)7L);
	temp = EQ(gensymed_symbol,Krelated_change);
	if (temp);
	else
	    temp = adding_relation_qm ? EQ(gensymed_symbol,Krelated) : 
		    EQ(gensymed_symbol,Knot_related);
    }
    else
	temp = TRUEP(Nil);
    if (temp ?  !SYMBOLP(designation) : TRUEP(Nil)) {
	if (domain_of_designation(designation)) {
	    temp_2 = role_of_designation(designation);
	    temp = SYMBOLP(temp_2);
	}
	else
	    temp = TRUEP(Nil);
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	new_cons = ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_eval_cons_pool();
	M_CAR(gensymed_symbol) = link_1;
	M_CDR(gensymed_symbol) = subject;
	inline_note_allocate_cons(gensymed_symbol,Qeval);
	new_value = eval_cons_1(gensymed_symbol,Nil);
	old_value = Nil;
      next_loop_10:
	old_value = Links_and_objects;
	M_CDR(new_value) = old_value;
	if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value))
	    goto end_loop_10;
	goto next_loop_10;
      end_loop_10:
	goto end_5;
      end_5:;
    }
    goto next_loop_9;
  end_loop_9:;
    if (subject_name_cons_qm) {
	inline_note_reclaim_cons(subject_name_cons_qm,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_1 = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_1) = subject_name_cons_qm;
	    temp_1 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = subject_name_cons_qm;
	}
	else {
	    temp_1 = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = subject_name_cons_qm;
	    temp_1 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = subject_name_cons_qm;
	}
	M_CDR(subject_name_cons_qm) = Nil;
    }
    return reclaim_parent_stack(parent_stack);
}

static Object Qloose_end;          /* loose-end */

/* INVOKE-RULES-FOR-DIRECT-CONNECTION-CHAINING */
Object invoke_rules_for_direct_connection_chaining(connection,disconnecting_qm)
    Object connection, disconnecting_qm;
{
    Object frame, symbol, gensymed_symbol, sub_class_bit_vector, class_1;
    Object transparent_class, ab_loop_list_, ab_loop_it_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(153,123);
    frame = ISVREF(connection,(SI_Long)3L);
    symbol = Qloose_end;
    gensymed_symbol = lookup_global_or_kb_specific_property_value(symbol,
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
    if ( !temp) {
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
    if (temp) {
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
		temp = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if ( !temp) {
	    class_1 = ISVREF(ISVREF(ISVREF(connection,(SI_Long)3L),
		    (SI_Long)1L),(SI_Long)1L);
	    transparent_class = Nil;
	    ab_loop_list_ = Transparent_classes_for_schematic_search;
	    ab_loop_it_ = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    transparent_class = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(class_1,
		    Class_description_gkbprop);
	    ab_loop_it_ = gensymed_symbol ? 
		    memq_function(transparent_class,ISVREF(gensymed_symbol,
		    (SI_Long)2L)) : Nil;
	    if (ab_loop_it_) {
		temp = TRUEP(ab_loop_it_);
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    temp = TRUEP(Qnil);
	  end_1:;
	    temp =  !temp;
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    invoke_rules_for_connection_chaining(connection,
		    ISVREF(connection,(SI_Long)3L),disconnecting_qm);
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
		temp = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if ( !temp) {
	    class_1 = ISVREF(ISVREF(ISVREF(connection,(SI_Long)2L),
		    (SI_Long)1L),(SI_Long)1L);
	    transparent_class = Nil;
	    ab_loop_list_ = Transparent_classes_for_schematic_search;
	    ab_loop_it_ = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    transparent_class = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(class_1,
		    Class_description_gkbprop);
	    ab_loop_it_ = gensymed_symbol ? 
		    memq_function(transparent_class,ISVREF(gensymed_symbol,
		    (SI_Long)2L)) : Nil;
	    if (ab_loop_it_) {
		temp = TRUEP(ab_loop_it_);
		goto end_2;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp = TRUEP(Qnil);
	  end_2:;
	    temp =  !temp;
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    return invoke_rules_for_connection_chaining(connection,
		    ISVREF(connection,(SI_Long)2L),disconnecting_qm);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* INVOKE-RULES-FOR-CONNECTION-CHAINING */
Object invoke_rules_for_connection_chaining(connection,block,disconnecting_qm)
    Object connection, block, disconnecting_qm;
{
    Object x2, current_computation_frame_previously_bound_qm;
    Object links_and_objects, role_qm, local_name_qm, chain_object;
    Object second_designation, second_role_qm, second_local_name_qm;
    Object second_chain_object_qm, link_entry, ab_loop_list_, link_1;
    Object recipient, sub_class_bit_vector, temp_1, constraint_alist;
    Object eval_cons, temp_2, temp_3, last_1, next_qm, svref_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(153,124);
    if (SIMPLE_VECTOR_P(Current_computation_frame) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_computation_frame)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(Current_computation_frame,
	    (SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(Current_computation_frame,(SI_Long)1L);
	current_computation_frame_previously_bound_qm = 
		SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	current_computation_frame_previously_bound_qm = Nil;
    links_and_objects = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Links_and_objects,Qlinks_and_objects,links_and_objects,
	    0);
      if ( !TRUEP(current_computation_frame_previously_bound_qm))
	  Current_computation_frame = block;
      collect_rules_for_connection_chaining(connection,block,disconnecting_qm);
      role_qm = Nil;
      local_name_qm = Nil;
      chain_object = Nil;
      second_designation = Nil;
      second_role_qm = Nil;
      second_local_name_qm = Nil;
      second_chain_object_qm = Nil;
      link_entry = Nil;
      ab_loop_list_ = Links_and_objects;
      link_1 = Nil;
      recipient = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      link_entry = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      link_1 = CAR(link_entry);
      recipient = ISVREF(link_1,(SI_Long)2L);
      sub_class_bit_vector = ISVREF(ISVREF(recipient,(SI_Long)1L),
	      (SI_Long)19L);
      superior_class_bit_number = 
	      IFIX(ISVREF(True_value_update_recipient_class_description,
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
      if ( !temp) {
	  temp_1 = ISVREF(recipient,(SI_Long)8L);
	  temp =  !TRUEP(CAR(temp_1)) ? (SI_Long)0L != 
		  (IFIX(ISVREF(recipient,(SI_Long)5L)) & (SI_Long)1L) ||  
		  !TRUEP(Inside_breakpoint_p) && (SI_Long)0L != 
		  (IFIX(ISVREF(recipient,(SI_Long)4L)) & 
		  (SI_Long)16777216L) &&  !((SI_Long)0L != 
		  (IFIX(ISVREF(recipient,(SI_Long)4L)) & (SI_Long)8192L)) :
		   TRUEP(Nil);
      }
      else
	  temp = TRUEP(Nil);
      if (temp) {
	  role_qm = ISVREF(link_1,(SI_Long)4L);
	  local_name_qm = role_qm ? ISVREF(link_1,(SI_Long)5L) : Nil;
	  chain_object = role_qm ? CDR(link_entry) : Nil;
	  second_designation = ISVREF(link_1,(SI_Long)8L);
	  second_role_qm = ISVREF(link_1,(SI_Long)9L);
	  second_local_name_qm = second_role_qm ? ISVREF(link_1,
		  (SI_Long)10L) : Nil;
	  second_chain_object_qm = second_role_qm ? 
		  (designation_could_denote_item_p(second_designation,
		  block) ? block : Nil) : Nil;
	  if ( !(second_role_qm &&  !TRUEP(second_chain_object_qm))) {
	      if ((IFIX(Tracing_message_level) > (SI_Long)1L || 
		      IFIX(Breakpoint_level) > (SI_Long)1L) &&  
		      !TRUEP(Debugging_reset) && 
		      ISVREF(Debugging_parameters,(SI_Long)22L))
		  write_major_connection_chaining_trace_message(role_qm,
			  second_role_qm,recipient,chain_object,
			  second_chain_object_qm,local_name_qm,
			  second_local_name_qm,disconnecting_qm,connection,
			  block);
	      if (role_qm && second_role_qm) {
		  temp_1 = second_local_name_qm;
		  if (temp_1);
		  else
		      temp_1 = second_role_qm;
		  constraint_alist = eval_cons_1(eval_cons_1(temp_1,
			  second_chain_object_qm),Nil);
		  generate_and_schedule_rule_instances(recipient,role_qm,
			  local_name_qm,chain_object,Qforward_chaining,Nil,
			  ISVREF(recipient,(SI_Long)26L),constraint_alist);
		  eval_cons = CAR(constraint_alist);
		  inline_note_reclaim_cons(eval_cons,Qeval);
		  if (ISVREF(Available_eval_conses_tail_vector,
			  IFIX(Current_thread_index))) {
		      temp_2 = ISVREF(Available_eval_conses_tail_vector,
			      IFIX(Current_thread_index));
		      M_CDR(temp_2) = eval_cons;
		      temp_2 = Available_eval_conses_tail_vector;
		      temp_3 = Current_thread_index;
		      SVREF(temp_2,temp_3) = eval_cons;
		  }
		  else {
		      temp_2 = Available_eval_conses_vector;
		      temp_3 = Current_thread_index;
		      SVREF(temp_2,temp_3) = eval_cons;
		      temp_2 = Available_eval_conses_tail_vector;
		      temp_3 = Current_thread_index;
		      SVREF(temp_2,temp_3) = eval_cons;
		  }
		  M_CDR(eval_cons) = Nil;
		  inline_note_reclaim_cons(constraint_alist,Qeval);
		  if (ISVREF(Available_eval_conses_tail_vector,
			  IFIX(Current_thread_index))) {
		      temp_2 = ISVREF(Available_eval_conses_tail_vector,
			      IFIX(Current_thread_index));
		      M_CDR(temp_2) = constraint_alist;
		      temp_2 = Available_eval_conses_tail_vector;
		      temp_3 = Current_thread_index;
		      SVREF(temp_2,temp_3) = constraint_alist;
		  }
		  else {
		      temp_2 = Available_eval_conses_vector;
		      temp_3 = Current_thread_index;
		      SVREF(temp_2,temp_3) = constraint_alist;
		      temp_2 = Available_eval_conses_tail_vector;
		      temp_3 = Current_thread_index;
		      SVREF(temp_2,temp_3) = constraint_alist;
		  }
		  M_CDR(constraint_alist) = Nil;
	      }
	      else if (role_qm)
		  generate_and_schedule_rule_instances(recipient,role_qm,
			  local_name_qm,chain_object,Qforward_chaining,Nil,
			  ISVREF(recipient,(SI_Long)26L),Nil);
	      else if (second_role_qm)
		  generate_and_schedule_rule_instances(recipient,
			  second_role_qm,second_local_name_qm,
			  second_chain_object_qm,Qforward_chaining,Nil,
			  ISVREF(recipient,(SI_Long)26L),Nil);
	      else
		  generate_and_schedule_rule_instances(recipient,Nil,Nil,
			  Nil,Qforward_chaining,Nil,ISVREF(recipient,
			  (SI_Long)26L),Nil);
	  }
      }
      inline_note_reclaim_cons(link_entry,Qeval);
      if (ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	  temp_2 = ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index));
	  M_CDR(temp_2) = link_entry;
	  temp_2 = Available_eval_conses_tail_vector;
	  temp_3 = Current_thread_index;
	  SVREF(temp_2,temp_3) = link_entry;
      }
      else {
	  temp_2 = Available_eval_conses_vector;
	  temp_3 = Current_thread_index;
	  SVREF(temp_2,temp_3) = link_entry;
	  temp_2 = Available_eval_conses_tail_vector;
	  temp_3 = Current_thread_index;
	  SVREF(temp_2,temp_3) = link_entry;
      }
      M_CDR(link_entry) = Nil;
      goto next_loop;
    end_loop:;
      if ( !TRUEP(current_computation_frame_previously_bound_qm))
	  Current_computation_frame = Nil;
      if (Links_and_objects) {
	  last_1 = Links_and_objects;
	  next_qm = Nil;
	next_loop_1:
	  next_qm = M_CDR(last_1);
	  if ( !TRUEP(next_qm))
	      goto end_loop_1;
	  inline_note_reclaim_cons(last_1,Qeval);
	  last_1 = next_qm;
	  goto next_loop_1;
	end_loop_1:
	  inline_note_reclaim_cons(last_1,Qeval);
	  if (ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	      temp_2 = ISVREF(Available_eval_conses_tail_vector,
		      IFIX(Current_thread_index));
	      temp_3 = Links_and_objects;
	      M_CDR(temp_2) = temp_3;
	      temp_2 = Available_eval_conses_tail_vector;
	      temp_3 = Current_thread_index;
	      SVREF(temp_2,temp_3) = last_1;
	  }
	  else {
	      temp_2 = Available_eval_conses_vector;
	      temp_3 = Current_thread_index;
	      svref_new_value = Links_and_objects;
	      SVREF(temp_2,temp_3) = svref_new_value;
	      temp_2 = Available_eval_conses_tail_vector;
	      temp_3 = Current_thread_index;
	      SVREF(temp_2,temp_3) = last_1;
	  }
	  M_CDR(last_1) = Nil;
	  result = VALUES_1(Nil);
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object string_constant_39;  /* "Scheduling chaining to ~NF with ~NF as ~A and ~NF as ~A ~?
				    *           because a connection was ~a for these items."
				    */

static Object string_constant_40;  /* "broken" */

static Object string_constant_41;  /* "made" */

static Object string_constant_42;  /* "Scheduling chaining to ~NF with ~NF as ~A ~?
				    *           because a connection of class ~A connected to ~NF was ~A."
				    */

static Object string_constant_43;  /* "Scheduling chaining to ~NF ~?
				    *           because a connection of class ~A connected to ~NF was ~A."
				    */

/* WRITE-MAJOR-CONNECTION-CHAINING-TRACE-MESSAGE */
Object write_major_connection_chaining_trace_message(role_qm,
	    second_role_qm,recipient,chain_object,second_chain_object_qm,
	    local_name_qm,second_local_name_qm,disconnecting_qm,
	    connection_structure,block)
    Object role_qm, second_role_qm, recipient, chain_object;
    Object second_chain_object_qm, local_name_qm, second_local_name_qm;
    Object disconnecting_qm, connection_structure, block;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, temp_1, connection_frame_or_class, gensymed_symbol;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(153,125);
    if ((IFIX(Tracing_message_level) > (SI_Long)1L || 
	    IFIX(Breakpoint_level) > (SI_Long)1L) &&  
	    !TRUEP(Debugging_reset) && ISVREF(Debugging_parameters,
	    (SI_Long)22L)) {
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
		  if (role_qm && second_role_qm) {
		      temp = local_name_qm;
		      if (temp);
		      else
			  temp = role_qm;
		      temp_1 = second_local_name_qm;
		      if (temp_1);
		      else
			  temp_1 = role_qm;
		      tformat(7,string_constant_39,recipient,chain_object,
			      temp,second_chain_object_qm,temp_1,
			      disconnecting_qm ? string_constant_40 : 
			      string_constant_41);
		  }
		  else if (role_qm) {
		      temp = local_name_qm;
		      if (temp);
		      else
			  temp = role_qm;
		      connection_frame_or_class = 
			      ISVREF(connection_structure,(SI_Long)1L);
		      tformat(7,string_constant_42,recipient,chain_object,
			      temp,SYMBOLP(connection_frame_or_class) ? 
			      connection_frame_or_class : 
			      ISVREF(ISVREF(connection_frame_or_class,
			      (SI_Long)1L),(SI_Long)1L),block,
			      disconnecting_qm ? string_constant_40 : 
			      string_constant_41);
		  }
		  else if (second_role_qm) {
		      temp = second_local_name_qm;
		      if (temp);
		      else
			  temp = second_role_qm;
		      connection_frame_or_class = 
			      ISVREF(connection_structure,(SI_Long)1L);
		      tformat(7,string_constant_42,recipient,
			      second_chain_object_qm,temp,
			      SYMBOLP(connection_frame_or_class) ? 
			      connection_frame_or_class : 
			      ISVREF(ISVREF(connection_frame_or_class,
			      (SI_Long)1L),(SI_Long)1L),block,
			      disconnecting_qm ? string_constant_40 : 
			      string_constant_41);
		  }
		  else {
		      connection_frame_or_class = 
			      ISVREF(connection_structure,(SI_Long)1L);
		      tformat(5,string_constant_43,recipient,
			      SYMBOLP(connection_frame_or_class) ? 
			      connection_frame_or_class : 
			      ISVREF(ISVREF(connection_frame_or_class,
			      (SI_Long)1L),(SI_Long)1L),block,
			      disconnecting_qm ? string_constant_40 : 
			      string_constant_41);
		  }
		  gensymed_symbol = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return write_major_trace_message_function(gensymed_symbol);
    }
    else
	return VALUES_1(Nil);
}

/* COLLECT-RULES-FOR-CONNECTION-CHAINING */
Object collect_rules_for_connection_chaining(connection_structure,block,
	    disconnecting_qm)
    Object connection_structure, block, disconnecting_qm;
{
    Object connection, subject_names_qm, subject_name_cons_qm, subject_name;
    Object ab_loop_list_, link_1, list_1, ab_loop_list__1, new_cons, temp;
    Object svref_arg_2, svref_new_value, gensymed_symbol, new_value, old_value;
    Object class_description, classes, cache_qm, class_1, specific_list;
    Object designation, temp_1;
    char temp_2;

    x_note_fn_call(153,126);
    connection = 
	    get_or_make_connection_frame_and_activate_if_appropriate(connection_structure);
    subject_names_qm = get_lookup_slot_value_given_default(connection,
	    Qname_or_names_for_frame,Nil);
    if (subject_names_qm && SYMBOLP(subject_names_qm)) {
	subject_names_qm = eval_cons_1(subject_names_qm,Nil);
	subject_name_cons_qm = subject_names_qm;
    }
    else
	subject_name_cons_qm = Nil;
    subject_name = Nil;
    ab_loop_list_ = subject_names_qm;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    subject_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    link_1 = Nil;
    list_1 = INLINE_SYMBOL_PLIST(subject_name);
  next_loop_1:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop_1;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_1;
  end_loop_1:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_2:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Forward_chaining_list_kbprop))
	goto end_loop_2;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_2;
  end_loop_2:
    ab_loop_list__1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_3:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_3;
    link_1 = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if (connection_satisfies_invoke_requirements_p(connection,block,link_1,
	    ISVREF(link_1,(SI_Long)7L),disconnecting_qm) && 
	    EQ(subject_name,ISVREF(link_1,(SI_Long)3L))) {
	new_cons = ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_eval_cons_pool();
	M_CAR(gensymed_symbol) = link_1;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qeval);
	new_value = eval_cons_1(gensymed_symbol,Nil);
	old_value = Nil;
      next_loop_4:
	old_value = Links_and_objects;
	M_CDR(new_value) = old_value;
	if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value))
	    goto end_loop_4;
	goto next_loop_4;
      end_loop_4:
	goto end_1;
      end_1:;
    }
    goto next_loop_3;
  end_loop_3:;
    goto next_loop;
  end_loop:;
    link_1 = Nil;
    class_description = ISVREF(connection,(SI_Long)1L);
    classes = ISVREF(class_description,(SI_Long)2L);
    gensymed_symbol = M_CAR(classes);
    list_1 = INLINE_SYMBOL_PLIST(gensymed_symbol);
  next_loop_5:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop_5;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_5;
  end_loop_5:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_6:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Cached_class_forward_chaining_list_kbprop))
	goto end_loop_6;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_6;
  end_loop_6:
    cache_qm = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    if (cache_qm)
	ab_loop_list_ = M_CDR(cache_qm);
    else {
	class_1 = Nil;
	ab_loop_list_ = classes;
	specific_list = Nil;
      next_loop_7:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_7;
	class_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	specific_list = lookup_kb_specific_property_value(class_1,
		Forward_chaining_list_kbprop);
	if (specific_list) {
	    specific_list = copy_list_using_eval_conses_1(specific_list);
	    if (cache_qm)
		cache_qm = nconc2(cache_qm,specific_list);
	    else
		cache_qm = specific_list;
	}
	if (EQ(class_1,Qitem))
	    goto end_loop_7;
	goto next_loop_7;
      end_loop_7:
	mutate_kb_specific_property_value(M_CAR(classes),eval_cons_1(Nil,
		cache_qm),Cached_class_forward_chaining_list_kbprop);
	new_value = eval_cons_1(M_CAR(classes),Nil);
	old_value = Nil;
      next_loop_8:
	old_value = Cached_classes_for_forward_chaining;
	M_CDR(new_value) = old_value;
	if (CAS_SYMBOL(Qcached_classes_for_forward_chaining,old_value,
		new_value))
	    goto end_loop_8;
	goto next_loop_8;
      end_loop_8:
	goto end_2;
      end_2:;
	ab_loop_list_ = cache_qm;
	goto end_3;
	ab_loop_list_ = Qnil;
      end_3:;
    }
    designation = Nil;
  next_loop_9:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_9;
    link_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    designation = ISVREF(link_1,(SI_Long)3L);
    if (connection_satisfies_invoke_requirements_p(connection,block,link_1,
	    ISVREF(link_1,(SI_Long)7L),disconnecting_qm) &&  
	    !SYMBOLP(designation)) {
	if (domain_of_designation(designation)) {
	    temp_1 = role_of_designation(designation);
	    temp_2 = SYMBOLP(temp_1);
	}
	else
	    temp_2 = TRUEP(Nil);
	temp_2 =  !temp_2;
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	new_cons = ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_eval_cons_pool();
	M_CAR(gensymed_symbol) = link_1;
	M_CDR(gensymed_symbol) = connection;
	inline_note_allocate_cons(gensymed_symbol,Qeval);
	new_value = eval_cons_1(gensymed_symbol,Nil);
	old_value = Nil;
      next_loop_10:
	old_value = Links_and_objects;
	M_CDR(new_value) = old_value;
	if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value))
	    goto end_loop_10;
	goto next_loop_10;
      end_loop_10:
	goto end_4;
      end_4:;
    }
    goto next_loop_9;
  end_loop_9:;
    if (subject_name_cons_qm) {
	inline_note_reclaim_cons(subject_name_cons_qm,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = subject_name_cons_qm;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = subject_name_cons_qm;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = subject_name_cons_qm;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = subject_name_cons_qm;
	}
	M_CDR(subject_name_cons_qm) = Nil;
	return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qat_an_input;        /* at-an-input */

static Object Qat_an_output;       /* at-an-output */

/* CONNECTION-SATISFIES-INVOKE-REQUIREMENTS-P */
Object connection_satisfies_invoke_requirements_p(connection,block,link_1,
	    stored_sense,disconnecting_qm)
    Object connection, block, link_1, stored_sense, disconnecting_qm;
{
    Object filter_name_qm, connection_structure, temp;

    x_note_fn_call(153,127);
    if ((disconnecting_qm ? EQ(stored_sense,Kdisconnected) : 
	    EQ(stored_sense,Kconnected)) && 
	    designation_could_denote_item_p(ISVREF(link_1,(SI_Long)8L),
		block)) {
	filter_name_qm = ISVREF(link_1,(SI_Long)6L);
	connection_structure = ISVREF(connection,(SI_Long)21L);
	temp =  !TRUEP(filter_name_qm) ? T : Nil;
	if (temp)
	    return VALUES_1(temp);
	else if (EQ(filter_name_qm,Qat_an_input)) {
	    if ( !((SI_Long)0L != (IFIX(ISVREF(connection_structure,
		    (SI_Long)7L)) & (SI_Long)1L)))
		return VALUES_1(EQ(ISVREF(connection_structure,
			(SI_Long)2L),block) ? T : Nil);
	    else
		return VALUES_1(Nil);
	}
	else if (EQ(filter_name_qm,Qat_an_output)) {
	    if ( !((SI_Long)0L != (IFIX(ISVREF(connection_structure,
		    (SI_Long)7L)) & (SI_Long)1L)))
		return VALUES_1(EQ(ISVREF(connection_structure,
			(SI_Long)3L),block) ? T : Nil);
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(EQ(filter_name_qm,
		    get_port_name_given_block_and_connection(2,block,
		    connection_structure)) ? T : Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qobject;             /* object */

/* INVOKE-RULES-FOR-INDIRECT-CONNECTION-CHAINING */
Object invoke_rules_for_indirect_connection_chaining(connection,
	    disconnecting_qm)
    Object connection, disconnecting_qm;
{
    Object connection_frame_1, input_end_entities_or_triples_found_in_search;
    Object output_end_entities_or_triples_found_in_search, input_set_entity;
    Object ab_loop_list_, output_set_entity, ab_loop_list__1;

    x_note_fn_call(153,128);
    connection_frame_1 = 
	    get_or_make_connection_frame_and_activate_if_appropriate(connection);
    input_end_entities_or_triples_found_in_search = 
	    search_for_entities_at_input_end(connection_frame_1,Qobject,Nil);
    output_end_entities_or_triples_found_in_search = 
	    search_for_entities_at_output_end(connection_frame_1,Qobject,Nil);
    input_set_entity = Nil;
    ab_loop_list_ = input_end_entities_or_triples_found_in_search;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    input_set_entity = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    output_set_entity = Nil;
    ab_loop_list__1 = output_end_entities_or_triples_found_in_search;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    output_set_entity = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    invoke_rules_for_indirect_connection_chaining_for_pair(connection_frame_1,
	    input_set_entity,output_set_entity,disconnecting_qm);
    invoke_rules_for_indirect_connection_chaining_for_pair(connection_frame_1,
	    output_set_entity,input_set_entity,disconnecting_qm);
    goto next_loop_1;
  end_loop_1:;
    goto next_loop;
  end_loop:;
    reclaim_eval_tree_1(input_end_entities_or_triples_found_in_search);
    return reclaim_eval_tree_1(output_end_entities_or_triples_found_in_search);
}

/* INVOKE-RULES-FOR-INDIRECT-CONNECTION-CHAINING-FOR-PAIR */
Object invoke_rules_for_indirect_connection_chaining_for_pair(connection_frame_1,
	    input_set_entity,output_set_entity,disconnecting_qm)
    Object connection_frame_1, input_set_entity, output_set_entity;
    Object disconnecting_qm;
{
    Object x2, current_computation_frame_previously_bound_qm;
    Object links_and_objects, role_qm, local_name_qm, chain_object;
    Object second_designation, second_role_qm, second_local_name_qm;
    Object second_chain_object_qm, link_entry, ab_loop_list_, link_1;
    Object recipient, sub_class_bit_vector, temp_1, constraint_alist;
    Object eval_cons, temp_2, temp_3, last_1, next_qm, svref_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(153,129);
    if (SIMPLE_VECTOR_P(Current_computation_frame) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_computation_frame)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(Current_computation_frame,
	    (SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(Current_computation_frame,(SI_Long)1L);
	current_computation_frame_previously_bound_qm = 
		SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	current_computation_frame_previously_bound_qm = Nil;
    links_and_objects = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Links_and_objects,Qlinks_and_objects,links_and_objects,
	    0);
      if ( !TRUEP(current_computation_frame_previously_bound_qm))
	  Current_computation_frame = input_set_entity;
      collect_rules_for_indirect_connection_chaining(connection_frame_1,
	      input_set_entity,output_set_entity,disconnecting_qm);
      role_qm = Nil;
      local_name_qm = Nil;
      chain_object = Nil;
      second_designation = Nil;
      second_role_qm = Nil;
      second_local_name_qm = Nil;
      second_chain_object_qm = Nil;
      link_entry = Nil;
      ab_loop_list_ = Links_and_objects;
      link_1 = Nil;
      recipient = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      link_entry = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      link_1 = CAR(link_entry);
      recipient = ISVREF(link_1,(SI_Long)2L);
      sub_class_bit_vector = ISVREF(ISVREF(recipient,(SI_Long)1L),
	      (SI_Long)19L);
      superior_class_bit_number = 
	      IFIX(ISVREF(True_value_update_recipient_class_description,
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
      if ( !temp) {
	  temp_1 = ISVREF(recipient,(SI_Long)8L);
	  temp =  !TRUEP(CAR(temp_1)) ? (SI_Long)0L != 
		  (IFIX(ISVREF(recipient,(SI_Long)5L)) & (SI_Long)1L) ||  
		  !TRUEP(Inside_breakpoint_p) && (SI_Long)0L != 
		  (IFIX(ISVREF(recipient,(SI_Long)4L)) & 
		  (SI_Long)16777216L) &&  !((SI_Long)0L != 
		  (IFIX(ISVREF(recipient,(SI_Long)4L)) & (SI_Long)8192L)) :
		   TRUEP(Nil);
      }
      else
	  temp = TRUEP(Nil);
      if (temp) {
	  role_qm = ISVREF(link_1,(SI_Long)4L);
	  local_name_qm = role_qm ? ISVREF(link_1,(SI_Long)5L) : Nil;
	  chain_object = role_qm ? CDR(link_entry) : Nil;
	  second_designation = ISVREF(link_1,(SI_Long)8L);
	  second_role_qm = ISVREF(link_1,(SI_Long)9L);
	  second_local_name_qm = second_role_qm ? ISVREF(link_1,
		  (SI_Long)10L) : Nil;
	  second_chain_object_qm = second_role_qm ? 
		  (designation_could_denote_item_p(second_designation,
		  output_set_entity) ? output_set_entity : Nil) : Nil;
	  if ( !(second_role_qm &&  !TRUEP(second_chain_object_qm))) {
	      if ((IFIX(Tracing_message_level) > (SI_Long)1L || 
		      IFIX(Breakpoint_level) > (SI_Long)1L) &&  
		      !TRUEP(Debugging_reset) && 
		      ISVREF(Debugging_parameters,(SI_Long)22L))
		  write_major_indirect_connection_chaining_trace_message(role_qm,
			  second_role_qm,recipient,chain_object,
			  second_chain_object_qm,local_name_qm,
			  second_local_name_qm,disconnecting_qm,
			  connection_frame_1,output_set_entity);
	      if (role_qm && second_role_qm) {
		  temp_1 = second_local_name_qm;
		  if (temp_1);
		  else
		      temp_1 = second_role_qm;
		  constraint_alist = eval_cons_1(eval_cons_1(temp_1,
			  second_chain_object_qm),Nil);
		  generate_and_schedule_rule_instances(recipient,role_qm,
			  local_name_qm,chain_object,Qforward_chaining,Nil,
			  ISVREF(recipient,(SI_Long)26L),constraint_alist);
		  eval_cons = CAR(constraint_alist);
		  inline_note_reclaim_cons(eval_cons,Qeval);
		  if (ISVREF(Available_eval_conses_tail_vector,
			  IFIX(Current_thread_index))) {
		      temp_2 = ISVREF(Available_eval_conses_tail_vector,
			      IFIX(Current_thread_index));
		      M_CDR(temp_2) = eval_cons;
		      temp_2 = Available_eval_conses_tail_vector;
		      temp_3 = Current_thread_index;
		      SVREF(temp_2,temp_3) = eval_cons;
		  }
		  else {
		      temp_2 = Available_eval_conses_vector;
		      temp_3 = Current_thread_index;
		      SVREF(temp_2,temp_3) = eval_cons;
		      temp_2 = Available_eval_conses_tail_vector;
		      temp_3 = Current_thread_index;
		      SVREF(temp_2,temp_3) = eval_cons;
		  }
		  M_CDR(eval_cons) = Nil;
		  inline_note_reclaim_cons(constraint_alist,Qeval);
		  if (ISVREF(Available_eval_conses_tail_vector,
			  IFIX(Current_thread_index))) {
		      temp_2 = ISVREF(Available_eval_conses_tail_vector,
			      IFIX(Current_thread_index));
		      M_CDR(temp_2) = constraint_alist;
		      temp_2 = Available_eval_conses_tail_vector;
		      temp_3 = Current_thread_index;
		      SVREF(temp_2,temp_3) = constraint_alist;
		  }
		  else {
		      temp_2 = Available_eval_conses_vector;
		      temp_3 = Current_thread_index;
		      SVREF(temp_2,temp_3) = constraint_alist;
		      temp_2 = Available_eval_conses_tail_vector;
		      temp_3 = Current_thread_index;
		      SVREF(temp_2,temp_3) = constraint_alist;
		  }
		  M_CDR(constraint_alist) = Nil;
	      }
	      else if (role_qm)
		  generate_and_schedule_rule_instances(recipient,role_qm,
			  local_name_qm,chain_object,Qforward_chaining,Nil,
			  ISVREF(recipient,(SI_Long)26L),Nil);
	      else if (second_role_qm)
		  generate_and_schedule_rule_instances(recipient,
			  second_role_qm,second_local_name_qm,
			  second_chain_object_qm,Qforward_chaining,Nil,
			  ISVREF(recipient,(SI_Long)26L),Nil);
	      else
		  generate_and_schedule_rule_instances(recipient,Nil,Nil,
			  Nil,Qforward_chaining,Nil,ISVREF(recipient,
			  (SI_Long)26L),Nil);
	  }
      }
      inline_note_reclaim_cons(link_entry,Qeval);
      if (ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	  temp_2 = ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index));
	  M_CDR(temp_2) = link_entry;
	  temp_2 = Available_eval_conses_tail_vector;
	  temp_3 = Current_thread_index;
	  SVREF(temp_2,temp_3) = link_entry;
      }
      else {
	  temp_2 = Available_eval_conses_vector;
	  temp_3 = Current_thread_index;
	  SVREF(temp_2,temp_3) = link_entry;
	  temp_2 = Available_eval_conses_tail_vector;
	  temp_3 = Current_thread_index;
	  SVREF(temp_2,temp_3) = link_entry;
      }
      M_CDR(link_entry) = Nil;
      goto next_loop;
    end_loop:;
      if ( !TRUEP(current_computation_frame_previously_bound_qm))
	  Current_computation_frame = Nil;
      if (Links_and_objects) {
	  last_1 = Links_and_objects;
	  next_qm = Nil;
	next_loop_1:
	  next_qm = M_CDR(last_1);
	  if ( !TRUEP(next_qm))
	      goto end_loop_1;
	  inline_note_reclaim_cons(last_1,Qeval);
	  last_1 = next_qm;
	  goto next_loop_1;
	end_loop_1:
	  inline_note_reclaim_cons(last_1,Qeval);
	  if (ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	      temp_2 = ISVREF(Available_eval_conses_tail_vector,
		      IFIX(Current_thread_index));
	      temp_3 = Links_and_objects;
	      M_CDR(temp_2) = temp_3;
	      temp_2 = Available_eval_conses_tail_vector;
	      temp_3 = Current_thread_index;
	      SVREF(temp_2,temp_3) = last_1;
	  }
	  else {
	      temp_2 = Available_eval_conses_vector;
	      temp_3 = Current_thread_index;
	      svref_new_value = Links_and_objects;
	      SVREF(temp_2,temp_3) = svref_new_value;
	      temp_2 = Available_eval_conses_tail_vector;
	      temp_3 = Current_thread_index;
	      SVREF(temp_2,temp_3) = last_1;
	  }
	  M_CDR(last_1) = Nil;
	  result = VALUES_1(Nil);
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* WRITE-MAJOR-INDIRECT-CONNECTION-CHAINING-TRACE-MESSAGE */
Object write_major_indirect_connection_chaining_trace_message(role_qm,
	    second_role_qm,recipient,chain_object,second_chain_object_qm,
	    local_name_qm,second_local_name_qm,disconnecting_qm,
	    connection_frame_1,output_set_entity)
    Object role_qm, second_role_qm, recipient, chain_object;
    Object second_chain_object_qm, local_name_qm, second_local_name_qm;
    Object disconnecting_qm, connection_frame_1, output_set_entity;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, temp_1, gensymed_symbol;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(153,130);
    if ((IFIX(Tracing_message_level) > (SI_Long)1L || 
	    IFIX(Breakpoint_level) > (SI_Long)1L) &&  
	    !TRUEP(Debugging_reset) && ISVREF(Debugging_parameters,
	    (SI_Long)22L)) {
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
		  if (role_qm && second_role_qm) {
		      temp = local_name_qm;
		      if (temp);
		      else
			  temp = role_qm;
		      temp_1 = second_local_name_qm;
		      if (temp_1);
		      else
			  temp_1 = role_qm;
		      tformat(7,string_constant_39,recipient,chain_object,
			      temp,second_chain_object_qm,temp_1,
			      disconnecting_qm ? string_constant_40 : 
			      string_constant_41);
		  }
		  else if (role_qm) {
		      temp = local_name_qm;
		      if (temp);
		      else
			  temp = role_qm;
		      tformat(7,string_constant_42,recipient,chain_object,
			      temp,ISVREF(ISVREF(connection_frame_1,
			      (SI_Long)1L),(SI_Long)1L),output_set_entity,
			      disconnecting_qm ? string_constant_40 : 
			      string_constant_41);
		  }
		  else if (second_role_qm) {
		      temp = second_local_name_qm;
		      if (temp);
		      else
			  temp = second_role_qm;
		      tformat(7,string_constant_42,recipient,
			      second_chain_object_qm,temp,
			      ISVREF(ISVREF(connection_frame_1,
			      (SI_Long)1L),(SI_Long)1L),output_set_entity,
			      disconnecting_qm ? string_constant_40 : 
			      string_constant_41);
		  }
		  else
		      tformat(5,string_constant_43,recipient,
			      ISVREF(ISVREF(connection_frame_1,
			      (SI_Long)1L),(SI_Long)1L),output_set_entity,
			      disconnecting_qm ? string_constant_40 : 
			      string_constant_41);
		  gensymed_symbol = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return write_major_trace_message_function(gensymed_symbol);
    }
    else
	return VALUES_1(Nil);
}

/* COLLECT-RULES-FOR-INDIRECT-CONNECTION-CHAINING */
Object collect_rules_for_indirect_connection_chaining(connection_frame_1,
	    input_set_entity,output_set_entity,disconnecting_qm)
    Object connection_frame_1, input_set_entity, output_set_entity;
    Object disconnecting_qm;
{
    Object subject_names_qm, subject_name_cons_qm, subject_name, ab_loop_list_;
    Object link_1, list_1, ab_loop_list__1, new_cons, temp, svref_arg_2;
    Object svref_new_value, gensymed_symbol, new_value, old_value;
    Object class_description, classes, cache_qm, class_1, specific_list;
    Object designation, temp_1;
    char temp_2;

    x_note_fn_call(153,131);
    subject_names_qm = 
	    get_lookup_slot_value_given_default(input_set_entity,
	    Qname_or_names_for_frame,Nil);
    if (subject_names_qm && SYMBOLP(subject_names_qm)) {
	subject_names_qm = eval_cons_1(subject_names_qm,Nil);
	subject_name_cons_qm = subject_names_qm;
    }
    else
	subject_name_cons_qm = Nil;
    subject_name = Nil;
    ab_loop_list_ = subject_names_qm;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    subject_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    link_1 = Nil;
    list_1 = INLINE_SYMBOL_PLIST(subject_name);
  next_loop_1:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop_1;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_1;
  end_loop_1:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_2:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Forward_chaining_list_kbprop))
	goto end_loop_2;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_2;
  end_loop_2:
    ab_loop_list__1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_3:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_3;
    link_1 = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if (input_and_output_set_entities_satisfy_invoke_requirements_p(connection_frame_1,
	    input_set_entity,output_set_entity,link_1,ISVREF(link_1,
	    (SI_Long)7L),disconnecting_qm) && EQ(subject_name,
	    ISVREF(link_1,(SI_Long)3L))) {
	new_cons = ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_eval_cons_pool();
	M_CAR(gensymed_symbol) = link_1;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qeval);
	new_value = eval_cons_1(gensymed_symbol,Nil);
	old_value = Nil;
      next_loop_4:
	old_value = Links_and_objects;
	M_CDR(new_value) = old_value;
	if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value))
	    goto end_loop_4;
	goto next_loop_4;
      end_loop_4:
	goto end_1;
      end_1:;
    }
    goto next_loop_3;
  end_loop_3:;
    goto next_loop;
  end_loop:;
    link_1 = Nil;
    class_description = ISVREF(input_set_entity,(SI_Long)1L);
    classes = ISVREF(class_description,(SI_Long)2L);
    gensymed_symbol = M_CAR(classes);
    list_1 = INLINE_SYMBOL_PLIST(gensymed_symbol);
  next_loop_5:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop_5;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_5;
  end_loop_5:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_6:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Cached_class_forward_chaining_list_kbprop))
	goto end_loop_6;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_6;
  end_loop_6:
    cache_qm = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    if (cache_qm)
	ab_loop_list_ = M_CDR(cache_qm);
    else {
	class_1 = Nil;
	ab_loop_list_ = classes;
	specific_list = Nil;
      next_loop_7:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_7;
	class_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	specific_list = lookup_kb_specific_property_value(class_1,
		Forward_chaining_list_kbprop);
	if (specific_list) {
	    specific_list = copy_list_using_eval_conses_1(specific_list);
	    if (cache_qm)
		cache_qm = nconc2(cache_qm,specific_list);
	    else
		cache_qm = specific_list;
	}
	if (EQ(class_1,Qitem))
	    goto end_loop_7;
	goto next_loop_7;
      end_loop_7:
	mutate_kb_specific_property_value(M_CAR(classes),eval_cons_1(Nil,
		cache_qm),Cached_class_forward_chaining_list_kbprop);
	new_value = eval_cons_1(M_CAR(classes),Nil);
	old_value = Nil;
      next_loop_8:
	old_value = Cached_classes_for_forward_chaining;
	M_CDR(new_value) = old_value;
	if (CAS_SYMBOL(Qcached_classes_for_forward_chaining,old_value,
		new_value))
	    goto end_loop_8;
	goto next_loop_8;
      end_loop_8:
	goto end_2;
      end_2:;
	ab_loop_list_ = cache_qm;
	goto end_3;
	ab_loop_list_ = Qnil;
      end_3:;
    }
    designation = Nil;
  next_loop_9:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_9;
    link_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    designation = ISVREF(link_1,(SI_Long)3L);
    if (input_and_output_set_entities_satisfy_invoke_requirements_p(connection_frame_1,
	    input_set_entity,output_set_entity,link_1,ISVREF(link_1,
	    (SI_Long)7L),disconnecting_qm) &&  !SYMBOLP(designation)) {
	if (domain_of_designation(designation)) {
	    temp_1 = role_of_designation(designation);
	    temp_2 = SYMBOLP(temp_1);
	}
	else
	    temp_2 = TRUEP(Nil);
	temp_2 =  !temp_2;
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	new_cons = ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_eval_cons_pool();
	M_CAR(gensymed_symbol) = link_1;
	M_CDR(gensymed_symbol) = input_set_entity;
	inline_note_allocate_cons(gensymed_symbol,Qeval);
	new_value = eval_cons_1(gensymed_symbol,Nil);
	old_value = Nil;
      next_loop_10:
	old_value = Links_and_objects;
	M_CDR(new_value) = old_value;
	if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value))
	    goto end_loop_10;
	goto next_loop_10;
      end_loop_10:
	goto end_4;
      end_4:;
    }
    goto next_loop_9;
  end_loop_9:;
    if (subject_name_cons_qm) {
	inline_note_reclaim_cons(subject_name_cons_qm,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = subject_name_cons_qm;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = subject_name_cons_qm;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = subject_name_cons_qm;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = subject_name_cons_qm;
	}
	M_CDR(subject_name_cons_qm) = Nil;
	return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* INPUT-AND-OUTPUT-SET-ENTITIES-SATISFY-INVOKE-REQUIREMENTS-P */
Object input_and_output_set_entities_satisfy_invoke_requirements_p(connection_frame_1,
	    input_set_entity,output_set_entity,link_1,stored_sense,
	    disconnecting_qm)
    Object connection_frame_1, input_set_entity, output_set_entity, link_1;
    Object stored_sense, disconnecting_qm;
{
    x_note_fn_call(153,132);
    if (disconnecting_qm ? EQ(stored_sense,Kdisconnected) : 
	    EQ(stored_sense,Kconnected))
	return designation_could_denote_item_p(ISVREF(link_1,(SI_Long)8L),
		output_set_entity);
    else
	return VALUES_1(Nil);
}

static Object string_constant_44;  /* "Scheduling event chaining to ~NF because a NUPEC synchronization ~?
				    *            has occurred."
				    */

/* INVOKE-RULES-FOR-NUPEC-SYNCHRONIZATION-CHAINING */
Object invoke_rules_for_nupec_synchronization_chaining()
{
    Object links_and_objects, link_entry, ab_loop_list_, link_1, recipient;
    Object sub_class_bit_vector, temp_1, temp_2, svref_arg_2;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(153,133);
    links_and_objects = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Links_and_objects,Qlinks_and_objects,links_and_objects,
	    0);
      collect_rules_for_nupec_synchronization_chaining();
      link_entry = Nil;
      ab_loop_list_ = Links_and_objects;
      link_1 = Nil;
      recipient = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      link_entry = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      link_1 = M_CAR(link_entry);
      recipient = ISVREF(link_1,(SI_Long)2L);
      sub_class_bit_vector = ISVREF(ISVREF(recipient,(SI_Long)1L),
	      (SI_Long)19L);
      superior_class_bit_number = 
	      IFIX(ISVREF(True_value_update_recipient_class_description,
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
      if ( !temp) {
	  temp_1 = ISVREF(recipient,(SI_Long)8L);
	  temp =  !TRUEP(CAR(temp_1)) ? (SI_Long)0L != 
		  (IFIX(ISVREF(recipient,(SI_Long)5L)) & (SI_Long)1L) ||  
		  !TRUEP(Inside_breakpoint_p) && (SI_Long)0L != 
		  (IFIX(ISVREF(recipient,(SI_Long)4L)) & 
		  (SI_Long)16777216L) &&  !((SI_Long)0L != 
		  (IFIX(ISVREF(recipient,(SI_Long)4L)) & (SI_Long)8192L)) :
		   TRUEP(Nil);
      }
      else
	  temp = TRUEP(Nil);
      if (temp) {
	  if ((IFIX(Tracing_message_level) > (SI_Long)1L || 
		  IFIX(Breakpoint_level) > (SI_Long)1L) &&  
		  !TRUEP(Debugging_reset) && ISVREF(Debugging_parameters,
		  (SI_Long)22L))
	      tformat_major_trace_message_1(string_constant_44,recipient,
		      Nil,Nil,Nil,Nil,Nil,Nil,Nil,Nil);
	  generate_and_schedule_rule_instances(recipient,Nil,Nil,Nil,
		  Qforward_chaining,Nil,ISVREF(recipient,(SI_Long)26L),Nil);
      }
      inline_note_reclaim_cons(link_entry,Qeval);
      if (ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	  temp_2 = ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index));
	  M_CDR(temp_2) = link_entry;
	  temp_2 = Available_eval_conses_tail_vector;
	  svref_arg_2 = Current_thread_index;
	  SVREF(temp_2,svref_arg_2) = link_entry;
      }
      else {
	  temp_2 = Available_eval_conses_vector;
	  svref_arg_2 = Current_thread_index;
	  SVREF(temp_2,svref_arg_2) = link_entry;
	  temp_2 = Available_eval_conses_tail_vector;
	  svref_arg_2 = Current_thread_index;
	  SVREF(temp_2,svref_arg_2) = link_entry;
      }
      M_CDR(link_entry) = Nil;
      goto next_loop;
    end_loop:;
      result = reclaim_eval_list_1(Links_and_objects);
    POP_SPECIAL();
    return result;
}

/* COLLECT-RULES-FOR-NUPEC-SYNCHRONIZATION-CHAINING */
Object collect_rules_for_nupec_synchronization_chaining()
{
    Object link_1, ab_loop_list_, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol, new_value, old_value;

    x_note_fn_call(153,134);
    link_1 = Nil;
    ab_loop_list_ = 
	    lookup_kb_specific_property_value(Qnupec_synchronization_occurs,
	    Forward_chaining_list_kbprop);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    link_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(ISVREF(link_1,(SI_Long)7L),Qnupec_synchronization_occurs)) {
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
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_eval_cons_pool();
	M_CAR(gensymed_symbol) = link_1;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qeval);
	new_value = eval_cons_1(gensymed_symbol,Nil);
	old_value = Nil;
      next_loop_1:
	old_value = Links_and_objects;
	M_CDR(new_value) = old_value;
	if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value))
	    goto end_loop_1;
	goto next_loop_1;
      end_loop_1:
	goto end_1;
      end_1:;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* INVOKE-RULES-FOR-GENERIC-EVENT-CHAINING */
Object invoke_rules_for_generic_event_chaining(event_name,item,event_object)
    Object event_name, item, event_object;
{
    Object x2, current_computation_frame_previously_bound_qm;
    Object links_and_objects, role_qm, local_name_qm, chain_object;
    Object second_designation, second_role_qm, second_local_name_qm;
    Object link_entry, ab_loop_list_, link_1, recipient, sub_class_bit_vector;
    Object temp_1, constraint_alist, eval_cons, temp_2, temp_3, last_1;
    Object next_qm, svref_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(153,135);
    if (SIMPLE_VECTOR_P(Current_computation_frame) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_computation_frame)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(Current_computation_frame,
	    (SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(Current_computation_frame,(SI_Long)1L);
	current_computation_frame_previously_bound_qm = 
		SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	current_computation_frame_previously_bound_qm = Nil;
    links_and_objects = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Links_and_objects,Qlinks_and_objects,links_and_objects,
	    0);
      if ( !TRUEP(current_computation_frame_previously_bound_qm))
	  Current_computation_frame = item;
      collect_links_for_generic_event_chaining(item,event_name);
      role_qm = Nil;
      local_name_qm = Nil;
      chain_object = Nil;
      second_designation = Nil;
      second_role_qm = Nil;
      second_local_name_qm = Nil;
      link_entry = Nil;
      ab_loop_list_ = Links_and_objects;
      link_1 = Nil;
      recipient = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      link_entry = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      link_1 = CAR(link_entry);
      recipient = ISVREF(link_1,(SI_Long)2L);
      sub_class_bit_vector = ISVREF(ISVREF(recipient,(SI_Long)1L),
	      (SI_Long)19L);
      superior_class_bit_number = 
	      IFIX(ISVREF(True_value_update_recipient_class_description,
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
      if ( !temp) {
	  temp_1 = ISVREF(recipient,(SI_Long)8L);
	  temp =  !TRUEP(CAR(temp_1)) ? (SI_Long)0L != 
		  (IFIX(ISVREF(recipient,(SI_Long)5L)) & (SI_Long)1L) ||  
		  !TRUEP(Inside_breakpoint_p) && (SI_Long)0L != 
		  (IFIX(ISVREF(recipient,(SI_Long)4L)) & 
		  (SI_Long)16777216L) &&  !((SI_Long)0L != 
		  (IFIX(ISVREF(recipient,(SI_Long)4L)) & (SI_Long)8192L)) :
		   TRUEP(Nil);
      }
      else
	  temp = TRUEP(Nil);
      if (temp) {
	  role_qm = ISVREF(link_1,(SI_Long)4L);
	  local_name_qm = role_qm ? ISVREF(link_1,(SI_Long)5L) : Qnil;
	  chain_object = role_qm ? CDR(link_entry) : Qnil;
	  second_designation = ISVREF(link_1,(SI_Long)8L);
	  second_role_qm = ISVREF(link_1,(SI_Long)9L);
	  second_local_name_qm = second_role_qm ? ISVREF(link_1,
		  (SI_Long)10L) : Qnil;
	  if (role_qm) {
	      temp_1 = second_local_name_qm;
	      if (temp_1);
	      else
		  temp_1 = second_role_qm;
	      constraint_alist = eval_cons_1(eval_cons_1(temp_1,
		      event_object),Nil);
	      generate_and_schedule_rule_instances(recipient,role_qm,
		      local_name_qm,chain_object,Qforward_chaining,Nil,
		      ISVREF(recipient,(SI_Long)26L),constraint_alist);
	      eval_cons = CAR(constraint_alist);
	      inline_note_reclaim_cons(eval_cons,Qeval);
	      if (ISVREF(Available_eval_conses_tail_vector,
		      IFIX(Current_thread_index))) {
		  temp_2 = ISVREF(Available_eval_conses_tail_vector,
			  IFIX(Current_thread_index));
		  M_CDR(temp_2) = eval_cons;
		  temp_2 = Available_eval_conses_tail_vector;
		  temp_3 = Current_thread_index;
		  SVREF(temp_2,temp_3) = eval_cons;
	      }
	      else {
		  temp_2 = Available_eval_conses_vector;
		  temp_3 = Current_thread_index;
		  SVREF(temp_2,temp_3) = eval_cons;
		  temp_2 = Available_eval_conses_tail_vector;
		  temp_3 = Current_thread_index;
		  SVREF(temp_2,temp_3) = eval_cons;
	      }
	      M_CDR(eval_cons) = Nil;
	      inline_note_reclaim_cons(constraint_alist,Qeval);
	      if (ISVREF(Available_eval_conses_tail_vector,
		      IFIX(Current_thread_index))) {
		  temp_2 = ISVREF(Available_eval_conses_tail_vector,
			  IFIX(Current_thread_index));
		  M_CDR(temp_2) = constraint_alist;
		  temp_2 = Available_eval_conses_tail_vector;
		  temp_3 = Current_thread_index;
		  SVREF(temp_2,temp_3) = constraint_alist;
	      }
	      else {
		  temp_2 = Available_eval_conses_vector;
		  temp_3 = Current_thread_index;
		  SVREF(temp_2,temp_3) = constraint_alist;
		  temp_2 = Available_eval_conses_tail_vector;
		  temp_3 = Current_thread_index;
		  SVREF(temp_2,temp_3) = constraint_alist;
	      }
	      M_CDR(constraint_alist) = Nil;
	  }
      }
      inline_note_reclaim_cons(link_entry,Qeval);
      if (ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	  temp_2 = ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index));
	  M_CDR(temp_2) = link_entry;
	  temp_2 = Available_eval_conses_tail_vector;
	  temp_3 = Current_thread_index;
	  SVREF(temp_2,temp_3) = link_entry;
      }
      else {
	  temp_2 = Available_eval_conses_vector;
	  temp_3 = Current_thread_index;
	  SVREF(temp_2,temp_3) = link_entry;
	  temp_2 = Available_eval_conses_tail_vector;
	  temp_3 = Current_thread_index;
	  SVREF(temp_2,temp_3) = link_entry;
      }
      M_CDR(link_entry) = Nil;
      goto next_loop;
    end_loop:;
      if ( !TRUEP(current_computation_frame_previously_bound_qm))
	  Current_computation_frame = Nil;
      if (Links_and_objects) {
	  last_1 = Links_and_objects;
	  next_qm = Nil;
	next_loop_1:
	  next_qm = M_CDR(last_1);
	  if ( !TRUEP(next_qm))
	      goto end_loop_1;
	  inline_note_reclaim_cons(last_1,Qeval);
	  last_1 = next_qm;
	  goto next_loop_1;
	end_loop_1:
	  inline_note_reclaim_cons(last_1,Qeval);
	  if (ISVREF(Available_eval_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	      temp_2 = ISVREF(Available_eval_conses_tail_vector,
		      IFIX(Current_thread_index));
	      temp_3 = Links_and_objects;
	      M_CDR(temp_2) = temp_3;
	      temp_2 = Available_eval_conses_tail_vector;
	      temp_3 = Current_thread_index;
	      SVREF(temp_2,temp_3) = last_1;
	  }
	  else {
	      temp_2 = Available_eval_conses_vector;
	      temp_3 = Current_thread_index;
	      svref_new_value = Links_and_objects;
	      SVREF(temp_2,temp_3) = svref_new_value;
	      temp_2 = Available_eval_conses_tail_vector;
	      temp_3 = Current_thread_index;
	      SVREF(temp_2,temp_3) = last_1;
	  }
	  M_CDR(last_1) = Nil;
	  result = VALUES_1(Nil);
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* G2-INVOKE-GENERIC-EVENT-RULES */
Object g2_invoke_generic_event_rules(event_name_ev,item,event_object)
    Object event_name_ev, item, event_object;
{
    Object temp, event_name;

    x_note_fn_call(153,136);
    temp = event_name_ev;
    event_name = temp;
    return invoke_rules_for_generic_event_chaining(event_name,item,
	    event_object);
}

/* GENERIC-EVENT-SENSE-MATCHES-P */
Object generic_event_sense_matches_p(link_1,event_name)
    Object link_1, event_name;
{
    Object temp;

    x_note_fn_call(153,137);
    temp = EQ(ISVREF(link_1,(SI_Long)7L),Qhas_generic_event) ? 
	    (EQ(ISVREF(link_1,(SI_Long)6L),event_name) ? T : Nil) : Qnil;
    return VALUES_1(temp);
}

/* COLLECT-LINKS-FOR-GENERIC-EVENT-CHAINING */
Object collect_links_for_generic_event_chaining(item,event_name)
    Object item, event_name;
{
    Object item_names_qm, item_name_cons_qm, parent_stack, item_name;
    Object ab_loop_list_, link_1, ab_loop_list__1, new_cons, temp, svref_arg_2;
    Object svref_new_value, gensymed_symbol, new_value, old_value;
    Object parent_stack_entry, parent_frame_qm, class_description, classes;
    Object list_1, cache_qm, class_1, specific_list, designation, temp_1;
    char temp_2;

    x_note_fn_call(153,138);
    item_names_qm = get_lookup_slot_value_given_default(item,
	    Qname_or_names_for_frame,Nil);
    if (item_names_qm && SYMBOLP(item_names_qm)) {
	item_names_qm = eval_cons_1(item_names_qm,Nil);
	item_name_cons_qm = item_names_qm;
    }
    else
	item_name_cons_qm = Nil;
    parent_stack = make_parent_stack(item);
    item_name = Nil;
    ab_loop_list_ = item_names_qm;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    item_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    link_1 = Nil;
    ab_loop_list__1 = lookup_kb_specific_property_value(item_name,
	    Forward_chaining_list_kbprop);
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    link_1 = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if (generic_event_sense_matches_p(link_1,event_name) && EQ(item_name,
	    ISVREF(link_1,(SI_Long)3L))) {
	new_cons = ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_eval_cons_pool();
	M_CAR(gensymed_symbol) = link_1;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qeval);
	new_value = eval_cons_1(gensymed_symbol,Nil);
	old_value = Nil;
      next_loop_2:
	old_value = Links_and_objects;
	M_CDR(new_value) = old_value;
	if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value))
	    goto end_loop_2;
	goto next_loop_2;
      end_loop_2:
	goto end_1;
      end_1:;
    }
    goto next_loop_1;
  end_loop_1:;
    goto next_loop;
  end_loop:;
    if (parent_stack) {
	parent_stack_entry = M_CAR(parent_stack);
	link_1 = Nil;
	gensymed_symbol = M_CAR(M_CDR(parent_stack_entry));
	ab_loop_list_ = 
		lookup_kb_specific_property_value(CONSP(gensymed_symbol) ? 
		M_CAR(gensymed_symbol) : gensymed_symbol,
		Forward_chaining_list_kbprop);
      next_loop_3:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_3;
	link_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (generic_event_sense_matches_p(link_1,event_name)) {
	    parent_frame_qm = find_referenced_parent(parent_stack,
		    ISVREF(link_1,(SI_Long)3L));
	    if (parent_frame_qm) {
		new_cons = ISVREF(Available_eval_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    temp = Available_eval_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(temp,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
			    IFIX(Current_thread_index)))) {
			temp = Available_eval_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = Nil;
		    }
		    gensymed_symbol = new_cons;
		}
		else
		    gensymed_symbol = Nil;
		if ( !TRUEP(gensymed_symbol))
		    gensymed_symbol = replenish_eval_cons_pool();
		M_CAR(gensymed_symbol) = link_1;
		M_CDR(gensymed_symbol) = parent_frame_qm;
		inline_note_allocate_cons(gensymed_symbol,Qeval);
		new_value = eval_cons_1(gensymed_symbol,Nil);
		old_value = Nil;
	      next_loop_4:
		old_value = Links_and_objects;
		M_CDR(new_value) = old_value;
		if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value))
		    goto end_loop_4;
		goto next_loop_4;
	      end_loop_4:
		goto end_2;
	      end_2:;
	    }
	}
	goto next_loop_3;
      end_loop_3:;
    }
    link_1 = Nil;
    class_description = ISVREF(item,(SI_Long)1L);
    classes = ISVREF(class_description,(SI_Long)2L);
    gensymed_symbol = M_CAR(classes);
    list_1 = INLINE_SYMBOL_PLIST(gensymed_symbol);
  next_loop_5:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop_5;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_5;
  end_loop_5:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_6:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Cached_class_forward_chaining_list_kbprop))
	goto end_loop_6;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_6;
  end_loop_6:
    cache_qm = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    if (cache_qm)
	ab_loop_list_ = M_CDR(cache_qm);
    else {
	class_1 = Nil;
	ab_loop_list_ = classes;
	specific_list = Nil;
      next_loop_7:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_7;
	class_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	specific_list = lookup_kb_specific_property_value(class_1,
		Forward_chaining_list_kbprop);
	if (specific_list) {
	    specific_list = copy_list_using_eval_conses_1(specific_list);
	    if (cache_qm)
		cache_qm = nconc2(cache_qm,specific_list);
	    else
		cache_qm = specific_list;
	}
	if (EQ(class_1,Qitem))
	    goto end_loop_7;
	goto next_loop_7;
      end_loop_7:
	mutate_kb_specific_property_value(M_CAR(classes),eval_cons_1(Nil,
		cache_qm),Cached_class_forward_chaining_list_kbprop);
	new_value = eval_cons_1(M_CAR(classes),Nil);
	old_value = Nil;
      next_loop_8:
	old_value = Cached_classes_for_forward_chaining;
	M_CDR(new_value) = old_value;
	if (CAS_SYMBOL(Qcached_classes_for_forward_chaining,old_value,
		new_value))
	    goto end_loop_8;
	goto next_loop_8;
      end_loop_8:
	goto end_3;
      end_3:;
	ab_loop_list_ = cache_qm;
	goto end_4;
	ab_loop_list_ = Qnil;
      end_4:;
    }
    designation = Nil;
  next_loop_9:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_9;
    link_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    designation = ISVREF(link_1,(SI_Long)3L);
    if (generic_event_sense_matches_p(link_1,event_name) &&  
	    !SYMBOLP(designation)) {
	if (domain_of_designation(designation)) {
	    temp_1 = role_of_designation(designation);
	    temp_2 = SYMBOLP(temp_1);
	}
	else
	    temp_2 = TRUEP(Nil);
	temp_2 =  !temp_2;
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	new_cons = ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_eval_cons_pool();
	M_CAR(gensymed_symbol) = link_1;
	M_CDR(gensymed_symbol) = item;
	inline_note_allocate_cons(gensymed_symbol,Qeval);
	new_value = eval_cons_1(gensymed_symbol,Nil);
	old_value = Nil;
      next_loop_10:
	old_value = Links_and_objects;
	M_CDR(new_value) = old_value;
	if (CAS_SYMBOL(Qlinks_and_objects,old_value,new_value))
	    goto end_loop_10;
	goto next_loop_10;
      end_loop_10:
	goto end_5;
      end_5:;
    }
    goto next_loop_9;
  end_loop_9:;
    if (item_name_cons_qm) {
	inline_note_reclaim_cons(item_name_cons_qm,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = item_name_cons_qm;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = item_name_cons_qm;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = item_name_cons_qm;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = item_name_cons_qm;
	}
	M_CDR(item_name_cons_qm) = Nil;
    }
    return reclaim_parent_stack(parent_stack);
}

static Object array_constant;      /* # */

static Object array_constant_1;    /* # */

/* MAYBE-GET-USER-SUPPLIED-FOCUS-LOCAL */
Object maybe_get_user_supplied_focus_local(class_name,local_name_qm)
    Object class_name, local_name_qm;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object text_to_check, text_to_check_length, local_name_text, end2;
    Object ab_loop_iter_flag_, temp_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, length1;
    SI_Long length2, index1, ab_loop_bind_, index2, ab_loop_bind__1;
    char temp;
    Declare_special(5);

    x_note_fn_call(153,139);
    if (local_name_qm) {
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
		  tformat(1,array_constant);
		  tformat(1,symbol_name_text_string(class_name));
		  tformat(1,array_constant_1);
		  text_to_check = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	text_to_check_length = text_string_length(text_to_check);
	local_name_text = symbol_name_text_string(local_name_qm);
	end2 = text_string_length(text_to_check);
	length1 = IFIX(text_to_check_length) - (SI_Long)0L;
	length2 = IFIX(end2) - (SI_Long)0L;
	if (length1 == length2) {
	    index1 = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(text_to_check_length);
	    index2 = (SI_Long)0L;
	    ab_loop_bind__1 = IFIX(end2);
	    ab_loop_iter_flag_ = T;
	  next_loop:
	    if (index1 >= ab_loop_bind_)
		goto end_loop;
	    if ( !TRUEP(ab_loop_iter_flag_))
		index2 = index2 + (SI_Long)1L;
	    if (index2 >= ab_loop_bind__1)
		goto end_loop;
	    if ( !(UBYTE_16_ISAREF_1(local_name_text,index1) == 
		    UBYTE_16_ISAREF_1(text_to_check,index2))) {
		temp = TRUEP(Nil);
		goto end_1;
	    }
	    ab_loop_iter_flag_ = Nil;
	    index1 = index1 + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    temp = TRUEP(T);
	    goto end_1;
	    temp = TRUEP(Qnil);
	  end_1:;
	}
	else
	    temp = TRUEP(Nil);
	temp_1 = (temp ? EQ(syntactically_numeric_substring_p(6,
		local_name_text,text_to_check_length,
		text_string_length(local_name_text),T,T,T),Qinteger) : 
		TRUEP(Nil)) ? Nil : local_name_qm;
	reclaim_text_string(text_to_check);
	return VALUES_1(temp_1);
    }
    else
	return VALUES_1(Nil);
}

/* COLLECTED-FOCUS-CLASS-NAMES-AND-LOCALS-EQUAL */
Object collected_focus_class_names_and_locals_equal(list1,list2)
    Object list1, list2;
{
    x_note_fn_call(153,140);
    if (EQ(M_CAR(list1),M_CAR(list2)))
	return VALUES_1(EQ(M_CAR(M_CDR(list1)),M_CAR(M_CDR(list2))) ? T : Nil);
    else
	return VALUES_1(Nil);
}

static Object Qcollected_focus_class_names_and_locals_equal;  /* collected-focus-class-names-and-locals-equal */

/* GET-FORWARD-CHAINING-NAMES-AND-LOCALS */
Object get_forward_chaining_names_and_locals(chaining_links)
    Object chaining_links;
{
    Object collected_roles, link_1, ab_loop_list_, forward_chaining_link_p;
    Object focus_role_qm, user_focus_local_qm, second_focus_role_qm;
    Object user_second_focus_local_qm, ab_loop_desetq_, sub_class_bit_vector;
    Object gensym_modify_macro_using_test_arg_1;
    Object gensym_modify_macro_using_test_arg_2, car_1, cdr_1, test;
    Object key_result, x_element, ab_loop_list__1, ab_loop_it_;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(153,141);
    collected_roles = Nil;
    link_1 = Nil;
    ab_loop_list_ = chaining_links;
    forward_chaining_link_p = Nil;
    focus_role_qm = Nil;
    user_focus_local_qm = Nil;
    second_focus_role_qm = Nil;
    user_second_focus_local_qm = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    link_1 = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    sub_class_bit_vector = ISVREF(ISVREF(link_1,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Forward_chaining_link_class_description,(SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_1 = (SI_Long)1L;
	gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	forward_chaining_link_p = (SI_Long)0L < gensymed_symbol ? T : Nil;
    }
    else
	forward_chaining_link_p = Nil;
    focus_role_qm = forward_chaining_link_p ? ISVREF(link_1,(SI_Long)4L) : Nil;
    user_focus_local_qm = focus_role_qm ? 
	    maybe_get_user_supplied_focus_local(focus_role_qm,
	    ISVREF(link_1,(SI_Long)5L)) : Nil;
    second_focus_role_qm = forward_chaining_link_p ? ISVREF(link_1,
	    (SI_Long)9L) : Nil;
    user_second_focus_local_qm = second_focus_role_qm ? 
	    maybe_get_user_supplied_focus_local(second_focus_role_qm,
	    ISVREF(link_1,(SI_Long)10L)) : Nil;
    if (focus_role_qm) {
	gensym_modify_macro_using_test_arg_1 = gensym_list_2(focus_role_qm,
		user_focus_local_qm);
	gensym_modify_macro_using_test_arg_2 = 
		SYMBOL_FUNCTION(Qcollected_focus_class_names_and_locals_equal);
	car_1 = gensym_modify_macro_using_test_arg_1;
	cdr_1 = collected_roles;
	test = gensym_modify_macro_using_test_arg_2;
	key_result = car_1;
	x_element = Nil;
	ab_loop_list__1 = cdr_1;
	ab_loop_it_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	x_element = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	ab_loop_it_ = FUNCALL_2(test,key_result,x_element);
	if (ab_loop_it_) {
	    temp = TRUEP(ab_loop_it_);
	    goto end_1;
	}
	goto next_loop_1;
      end_loop_1:
	temp = TRUEP(Qnil);
      end_1:;
	collected_roles = temp ? cdr_1 : gensym_cons_1(car_1,cdr_1);
    }
    if (second_focus_role_qm) {
	gensym_modify_macro_using_test_arg_1 = 
		gensym_list_2(second_focus_role_qm,user_second_focus_local_qm);
	gensym_modify_macro_using_test_arg_2 = 
		SYMBOL_FUNCTION(Qcollected_focus_class_names_and_locals_equal);
	car_1 = gensym_modify_macro_using_test_arg_1;
	cdr_1 = collected_roles;
	test = gensym_modify_macro_using_test_arg_2;
	key_result = car_1;
	x_element = Nil;
	ab_loop_list__1 = cdr_1;
	ab_loop_it_ = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_2;
	x_element = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	ab_loop_it_ = FUNCALL_2(test,key_result,x_element);
	if (ab_loop_it_) {
	    temp = TRUEP(ab_loop_it_);
	    goto end_2;
	}
	goto next_loop_2;
      end_loop_2:
	temp = TRUEP(Qnil);
      end_2:;
	collected_roles = temp ? cdr_1 : gensym_cons_1(car_1,cdr_1);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(collected_roles);
    return VALUES_1(Qnil);
}

static Object Qchaining_link_focus_class_name;  /* chaining-link-focus-class-name */

static Object Qchaining_link_focus_local_name_is_specified;  /* chaining-link-focus-local-name-is-specified */

static Object Qchaining_link_focus_local_name;  /* chaining-link-focus-local-name */

static Object Qab_structure;       /* structure */

/* GET-FORWARD-CHAINING-FOCUS-INFO-AS-SEQUENCE */
Object get_forward_chaining_focus_info_as_sequence(rule)
    Object rule;
{
    Object names_and_locals, class_name, local_name_qm, ab_loop_list_;
    Object structures, ab_loopvar_, ab_loopvar__1, ab_loop_desetq_, temp;
    Object gensymed_symbol, temp_1, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_2;

    x_note_fn_call(153,142);
    names_and_locals = 
	    get_forward_chaining_names_and_locals(rule_chaining_links_function(rule));
    class_name = Nil;
    local_name_qm = Nil;
    ab_loop_list_ = names_and_locals;
    structures = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    class_name = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    local_name_qm = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)6L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = 
		Qchaining_link_focus_class_name;
    else {
	temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp_1,FIX((SI_Long)1L)) = Qchaining_link_focus_class_name;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = class_name;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	temp_1 = temp_2 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
    }
    else {
	temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = class_name;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	svref_new_value = temp_2 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = 
		Qchaining_link_focus_local_name_is_specified;
    else {
	temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp_1,FIX((SI_Long)3L)) = 
		Qchaining_link_focus_local_name_is_specified;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = local_name_qm ? Evaluation_true_value : 
		Evaluation_false_value;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	temp_1 = temp_2 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
    }
    else {
	temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = local_name_qm ? Evaluation_true_value : 
		Evaluation_false_value;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	svref_new_value = temp_2 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp_1,FIX((SI_Long)4L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)7L)) = 
		Qchaining_link_focus_local_name;
    else {
	temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp_1,FIX((SI_Long)5L)) = Qchaining_link_focus_local_name;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = local_name_qm;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	temp_1 = temp_2 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp_1;
    }
    else {
	temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = local_name_qm;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	svref_new_value = temp_2 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp_1,FIX((SI_Long)6L)) = svref_new_value;
    }
    ab_loopvar__1 = eval_cons_1(eval_cons_1(gensymed_symbol,Qab_structure),
	    Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	structures = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    reclaim_gensym_tree_1(names_and_locals);
    return allocate_evaluation_sequence(structures);
    return VALUES_1(Qnil);
}

/* G2-GET-FORWARD-CHAINING-FOCUS-INFO */
Object g2_get_forward_chaining_focus_info(rule_as_evaluation_value)
    Object rule_as_evaluation_value;
{
    Object rule, value_1, temp;

    x_note_fn_call(153,143);
    rule = IDENTITY(rule_as_evaluation_value);
    value_1 = Nil;
    value_1 = get_forward_chaining_focus_info_as_sequence(rule);
    IDENTITY(rule_as_evaluation_value);
    temp = IDENTITY(value_1);
    return VALUES_1(temp);
}

/* GET-BACKWARD-CHAINING-RULES-FOR-VARIABLE */
Object get_backward_chaining_rules_for_variable(var)
    Object var;
{
    Object links_and_objects, link_1, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, ab_loop_desetq_, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(153,144);
    links_and_objects = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Links_and_objects,Qlinks_and_objects,links_and_objects,
	    0);
      collect_rules_for_backward_chaining(var,
	      type_specification_of_variable_or_parameter_value(var));
      link_1 = Nil;
      ab_loop_list_ = Links_and_objects;
      ab_loopvar_ = Nil;
      ab_loopvar__1 = Nil;
      ab_loopvar__2 = Nil;
      ab_loop_desetq_ = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      ab_loop_desetq_ = M_CAR(ab_loop_list_);
      link_1 = CAR(ab_loop_desetq_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      ab_loopvar__2 = eval_cons_1(ISVREF(link_1,(SI_Long)2L),Nil);
      if (ab_loopvar__1)
	  M_CDR(ab_loopvar__1) = ab_loopvar__2;
      else
	  ab_loopvar_ = ab_loopvar__2;
      ab_loopvar__1 = ab_loopvar__2;
      goto next_loop;
    end_loop:
      temp = ab_loopvar_;
      goto end_1;
      temp = Qnil;
    end_1:;
      reclaim_eval_tree_1(Links_and_objects);
      result = VALUES_1(temp);
    POP_SPECIAL();
    return result;
}

/* G2-GET-BACKWARD-CHAINING-RULES-FOR-VARIABLE */
Object g2_get_backward_chaining_rules_for_variable(var_as_evaluation_value)
    Object var_as_evaluation_value;
{
    Object var, value_1, temp;

    x_note_fn_call(153,145);
    var = IDENTITY(var_as_evaluation_value);
    value_1 = Nil;
    value_1 = 
	    allocate_evaluation_sequence(get_backward_chaining_rules_for_variable(var));
    IDENTITY(var_as_evaluation_value);
    temp = IDENTITY(value_1);
    return VALUES_1(temp);
}

void chaining_INIT()
{
    Object temp, temp_1, temp_2, reclaim_structure_for_event_detector_1;
    Object gensymed_symbol;
    Object Qg2_get_backward_chaining_rules_for_variable;
    Object Qfunction_keeps_procedure_environment_valid_qm, AB_package;
    Object Qg2_get_forward_chaining_focus_info, list_constant_6;
    Object Qg2_invoke_generic_event_rules, G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qclasses_which_define, Qcopy_frame;
    Object Qcopy_frame_for_backward_chaining_link, string_constant_60;
    Object list_constant_5, string_constant_59, string_constant_58;
    Object string_constant_46, Qconnection, Qfor_every_literal;
    Object Qthere_exists_literal, Qchaining, Qevent_detector;
    Object Qreclaim_structure, Qoutstanding_event_detector_count;
    Object Qevent_detector_structure_memory_usage, Qutilities2;
    Object string_constant_57, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_56, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object Qcopy_frame_for_forward_chaining_link;
    Object Qcopy_frame_for_true_value_update_recipient, string_constant_55;
    Object string_constant_54, string_constant_53, string_constant_52;
    Object string_constant_51, string_constant_50, string_constant_49;
    Object string_constant_48, string_constant_47, Qdependent_frame;
    Object string_constant_45, Qinstallation_cons_memory_usage;
    Object Qoutstanding_installation_conses, list_constant_4;
    Object Qinstallation_cons_counter_vector, Qmake_thread_array, Kfuncall;
    Object list_constant_3, Qavailable_installation_conses_tail_vector;
    Object Qavailable_installation_conses_vector;
    Object Qcached_class_backward_chaining_list;
    Object Qdo_not_carry_global_property_value_into_kbs_qm;
    Object Qbackward_chaining_list, Qcached_class_forward_chaining_list;
    Object Qforward_chaining_list;

    x_note_fn_call(153,146);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qforward_chaining_list = STATIC_SYMBOL("FORWARD-CHAINING-LIST",AB_package);
    Kb_specific_property_names = CONS(Qforward_chaining_list,
	    Kb_specific_property_names);
    Qdo_not_carry_global_property_value_into_kbs_qm = 
	    STATIC_SYMBOL("DO-NOT-CARRY-GLOBAL-PROPERTY-VALUE-INTO-KBS\?",
	    AB_package);
    mutate_global_property(Qforward_chaining_list,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Forward_chaining_list_kbprop = Qforward_chaining_list;
    Qcached_class_forward_chaining_list = 
	    STATIC_SYMBOL("CACHED-CLASS-FORWARD-CHAINING-LIST",AB_package);
    Kb_specific_property_names = CONS(Qcached_class_forward_chaining_list,
	    Kb_specific_property_names);
    mutate_global_property(Qcached_class_forward_chaining_list,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Cached_class_forward_chaining_list_kbprop = 
	    Qcached_class_forward_chaining_list;
    Qbackward_chaining_list = STATIC_SYMBOL("BACKWARD-CHAINING-LIST",
	    AB_package);
    Kb_specific_property_names = CONS(Qbackward_chaining_list,
	    Kb_specific_property_names);
    mutate_global_property(Qbackward_chaining_list,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Backward_chaining_list_kbprop = Qbackward_chaining_list;
    Qcached_class_backward_chaining_list = 
	    STATIC_SYMBOL("CACHED-CLASS-BACKWARD-CHAINING-LIST",AB_package);
    Kb_specific_property_names = CONS(Qcached_class_backward_chaining_list,
	    Kb_specific_property_names);
    mutate_global_property(Qcached_class_backward_chaining_list,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Cached_class_backward_chaining_list_kbprop = 
	    Qcached_class_backward_chaining_list;
    Qavailable_installation_conses = 
	    STATIC_SYMBOL("AVAILABLE-INSTALLATION-CONSES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_installation_conses,
	    Available_installation_conses);
    Qchaining = STATIC_SYMBOL("CHAINING",AB_package);
    record_system_variable(Qavailable_installation_conses,Qchaining,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_installation_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-INSTALLATION-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_installation_conses_tail,
	    Available_installation_conses_tail);
    record_system_variable(Qavailable_installation_conses_tail,Qchaining,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qavailable_installation_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-INSTALLATION-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_installation_conses_vector,
	    Available_installation_conses_vector);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_thread_array = STATIC_SYMBOL("MAKE-THREAD-ARRAY",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    Qnil);
    record_system_variable(Qavailable_installation_conses_vector,Qchaining,
	    list_constant_3,Qnil,Qt,Qnil,Qnil);
    Qavailable_installation_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-INSTALLATION-CONSES-TAIL-VECTOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_installation_conses_tail_vector,
	    Available_installation_conses_tail_vector);
    record_system_variable(Qavailable_installation_conses_tail_vector,
	    Qchaining,list_constant_3,Qnil,Qt,Qnil,Qnil);
    Qinstallation_cons_counter_vector = 
	    STATIC_SYMBOL("INSTALLATION-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qinstallation_cons_counter_vector,
	    Installation_cons_counter_vector);
    list_constant_4 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    FIX((SI_Long)0L));
    record_system_variable(Qinstallation_cons_counter_vector,Qchaining,
	    list_constant_4,Qnil,Qt,Qnil,Qnil);
    Qinstallation_cons_counter = STATIC_SYMBOL("INSTALLATION-CONS-COUNTER",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qinstallation_cons_counter,
	    Installation_cons_counter);
    record_system_variable(Qinstallation_cons_counter,Qchaining,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_installation_conses = 
	    STATIC_SYMBOL("OUTSTANDING-INSTALLATION-CONSES",AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_installation_conses,
	    STATIC_FUNCTION(outstanding_installation_conses,NIL,FALSE,0,0));
    Qinstallation_cons_memory_usage = 
	    STATIC_SYMBOL("INSTALLATION-CONS-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qinstallation_cons_memory_usage,
	    STATIC_FUNCTION(installation_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_45 = STATIC_STRING("1q83-aCy9k83-aBy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_installation_conses);
    push_optimized_constant(Qinstallation_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_45));
    Qinstallation = STATIC_SYMBOL("INSTALLATION",AB_package);
    Qforward_chaining_link = STATIC_SYMBOL("FORWARD-CHAINING-LINK",AB_package);
    Qdependent_frame = STATIC_SYMBOL("DEPENDENT-FRAME",AB_package);
    list_constant_5 = STATIC_CONS(Qdependent_frame,Qnil);
    check_if_superior_classes_are_defined(Qforward_chaining_link,
	    list_constant_5);
    string_constant_46 = STATIC_STRING("1l1l8t");
    string_constant_47 = 
	    STATIC_STRING("1t4z8r83M1y83M1y83M-y83M-y00001n1l8o1l8l1l83Cy000004z8r83M*y83M*y83M-y83M-y00001n1l8o1l8l1l83Cy000004z8r83M=y83M=y83M-y83M-y0000");
    string_constant_48 = 
	    STATIC_STRING("1n1l8o1l8l1l83Cy000004z8r83M0y83M0y83M-y83M-y00001n1l8o1l8l1l83Cy000004z8r83M6y83M6y83M-y83M-y00001n1l8o1l8l1l83Cy000004z8r83M5y");
    string_constant_49 = 
	    STATIC_STRING("83M5y83M-y83M-y00001n1l8o1l8l1l83Cy000004z8r83M2y83M2y83M-y83M-y00001n1l8o1l8l1l83Cy000004z8r83M3y83M3y83M-y83M-y00001n1l8o1l8l1");
    string_constant_50 = 
	    STATIC_STRING("l83Cy000004z8r83M4y83M4y83M-y83M-y00001n1l8o1l8l1l83Cy00000");
    string_constant_51 = 
	    STATIC_STRING("1v8q1n83M-y1l83=fy8t1p83M1y08o8l83Cy1p83M*y08o8l83Cy1p83M=y08o8l83Cy1p83M0y08o8l83Cy1p83M6y08o8l83Cy1p83M5y08o8l83Cy1p83M2y08o8l");
    string_constant_52 = STATIC_STRING("83Cy1p83M3y08o8l83Cy1p83M4y08o8l83Cy");
    temp = regenerate_optimized_constant(string_constant_46);
    temp_1 = regenerate_optimized_constant(LIST_4(string_constant_47,
	    string_constant_48,string_constant_49,string_constant_50));
    add_class_to_environment(9,Qforward_chaining_link,list_constant_5,Nil,
	    temp,Nil,temp_1,list_constant_5,
	    regenerate_optimized_constant(LIST_2(string_constant_51,
	    string_constant_52)),Nil);
    Forward_chaining_link_class_description = 
	    lookup_global_or_kb_specific_property_value(Qforward_chaining_link,
	    Class_description_gkbprop);
    Qtrue_value_update_recipient = 
	    STATIC_SYMBOL("TRUE-VALUE-UPDATE-RECIPIENT",AB_package);
    check_if_superior_classes_are_defined(Qtrue_value_update_recipient,
	    list_constant_5);
    string_constant_53 = 
	    STATIC_STRING("1n4z8r83cmy83cmy83cny83cny00001n1l8o1l8l1l83Cy000004z8r83cly83cly83cny83cny00001n1l8o1l8l1l83Cy000004z8r83cky83cky83cny83cny0000");
    string_constant_54 = STATIC_STRING("1n1l8o1l8l1l83Cy00000");
    string_constant_55 = 
	    STATIC_STRING("1p8q1n83cny1l83=fy8t1p83cmy08o8l83Cy1p83cly08o8l83Cy1p83cky08o8l83Cy");
    temp = regenerate_optimized_constant(string_constant_46);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_53,
	    string_constant_54));
    add_class_to_environment(9,Qtrue_value_update_recipient,
	    list_constant_5,Nil,temp,Nil,temp_1,list_constant_5,
	    regenerate_optimized_constant(string_constant_55),Nil);
    True_value_update_recipient_class_description = 
	    lookup_global_or_kb_specific_property_value(Qtrue_value_update_recipient,
	    Class_description_gkbprop);
    Qdependent_frame_has_no_owner = 
	    STATIC_SYMBOL("DEPENDENT-FRAME-HAS-NO-OWNER",AB_package);
    Qcopy_frame_for_true_value_update_recipient = 
	    STATIC_SYMBOL("COPY-FRAME-FOR-TRUE-VALUE-UPDATE-RECIPIENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcopy_frame_for_true_value_update_recipient,
	    STATIC_FUNCTION(copy_frame_for_true_value_update_recipient,NIL,
	    FALSE,1,1));
    Qcopy_frame = STATIC_SYMBOL("COPY-FRAME",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qcopy_frame_for_true_value_update_recipient);
    set_get(Qtrue_value_update_recipient,Qcopy_frame,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcopy_frame),
	    Qclasses_which_define);
    temp_2 = CONS(Qtrue_value_update_recipient,temp);
    mutate_global_property(Qcopy_frame,temp_2,Qclasses_which_define);
    Qcopy_frame_for_forward_chaining_link = 
	    STATIC_SYMBOL("COPY-FRAME-FOR-FORWARD-CHAINING-LINK",AB_package);
    SET_SYMBOL_FUNCTION(Qcopy_frame_for_forward_chaining_link,
	    STATIC_FUNCTION(copy_frame_for_forward_chaining_link,NIL,FALSE,
	    1,1));
    temp_2 = SYMBOL_FUNCTION(Qcopy_frame_for_forward_chaining_link);
    set_get(Qforward_chaining_link,Qcopy_frame,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcopy_frame),
	    Qclasses_which_define);
    temp_2 = CONS(Qforward_chaining_link,temp);
    mutate_global_property(Qcopy_frame,temp_2,Qclasses_which_define);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_event_detector_g2_struct = 
	    STATIC_SYMBOL("EVENT-DETECTOR-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qevent_detector = STATIC_SYMBOL("EVENT-DETECTOR",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_event_detector_g2_struct,
	    Qevent_detector,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qevent_detector,
	    Qg2_defstruct_structure_name_event_detector_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_event_detector == UNBOUND)
	The_type_description_of_event_detector = Nil;
    string_constant_56 = 
	    STATIC_STRING("43Dy8m83h9y1n83h9y8n8k1l8n0000001l1n8y83-3ay1o83vly83vky83viy83vjykpk0k0");
    temp = The_type_description_of_event_detector;
    The_type_description_of_event_detector = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_56));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_event_detector_g2_struct,
	    The_type_description_of_event_detector,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qevent_detector,
	    The_type_description_of_event_detector,Qtype_description_of_type);
    Qoutstanding_event_detector_count = 
	    STATIC_SYMBOL("OUTSTANDING-EVENT-DETECTOR-COUNT",AB_package);
    Qevent_detector_structure_memory_usage = 
	    STATIC_SYMBOL("EVENT-DETECTOR-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_57 = STATIC_STRING("1q83h9y8s83-T4y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_event_detector_count);
    push_optimized_constant(Qevent_detector_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_57));
    Qchain_of_available_event_detectors = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-EVENT-DETECTORS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_event_detectors,
	    Chain_of_available_event_detectors);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_event_detectors,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qevent_detector_count = STATIC_SYMBOL("EVENT-DETECTOR-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qevent_detector_count,Event_detector_count);
    record_system_variable(Qevent_detector_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_event_detectors_vector == UNBOUND)
	Chain_of_available_event_detectors_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qevent_detector_structure_memory_usage,
	    STATIC_FUNCTION(event_detector_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_event_detector_count,
	    STATIC_FUNCTION(outstanding_event_detector_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_event_detector_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_event_detector,NIL,FALSE,
	    1,1);
    record_direct_structure_method(Qreclaim_structure,Qevent_detector,
	    reclaim_structure_for_event_detector_1);
    if (Function_templates == UNBOUND)
	Function_templates = Nil;
    if (Action_templates == UNBOUND)
	Action_templates = Nil;
    Qparent_frame = STATIC_SYMBOL("PARENT-FRAME",AB_package);
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qparent_attribute_name = STATIC_SYMBOL("PARENT-ATTRIBUTE-NAME",AB_package);
    Qclass_qualified_name = STATIC_SYMBOL("CLASS-QUALIFIED-NAME",AB_package);
    Qcached_classes_for_forward_chaining = 
	    STATIC_SYMBOL("CACHED-CLASSES-FOR-FORWARD-CHAINING",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcached_classes_for_forward_chaining,
	    Cached_classes_for_forward_chaining);
    record_system_variable(Qcached_classes_for_forward_chaining,Qchaining,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qcached_classes_for_backward_chaining = 
	    STATIC_SYMBOL("CACHED-CLASSES-FOR-BACKWARD-CHAINING",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcached_classes_for_backward_chaining,
	    Cached_classes_for_backward_chaining);
    record_system_variable(Qcached_classes_for_backward_chaining,Qchaining,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qlinks_and_objects = STATIC_SYMBOL("*LINKS-AND-OBJECTS*",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlinks_and_objects,Links_and_objects);
    record_system_variable(Qlinks_and_objects,Qchaining,Nil,Qnil,Qnil,Qnil,
	    Qnil);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qeither = STATIC_SYMBOL("EITHER",AB_package);
    Qreceives_a_value = STATIC_SYMBOL("RECEIVES-A-VALUE",AB_package);
    Qloses_its_value = STATIC_SYMBOL("LOSES-ITS-VALUE",AB_package);
    string_constant = 
	    STATIC_STRING("Notifying ~NF that a new value has been placed in ~NF.");
    Qforward_chaining = STATIC_SYMBOL("FORWARD-CHAINING",AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_1 = 
	    STATIC_STRING("Scheduling forward chaining to ~NF with ~NF as the ~A ~\r\n               with local name ~A because a new value was placed in ~NF by ~NF.");
    string_constant_2 = 
	    STATIC_STRING("Scheduling forward chaining to ~NF with ~NF as the ~A ~\r\n               because a new value was placed in ~NF by ~NF.");
    string_constant_3 = 
	    STATIC_STRING("Scheduling forward chaining to ~NF because a new value was ~\r\n         placed in ~NF by ~NF.");
    Qrecord_block_for_tformat = STATIC_SYMBOL("RECORD-BLOCK-FOR-TFORMAT",
	    AB_package);
    string_constant_4 = 
	    string_append2(STATIC_STRING("The value ~(~a~) is being stored into the symbolic variable ~NF but ~\r\n       this value is not a member of the set of possible values for its ~\r\n       attribute and class.  "),
	    STATIC_STRING("The set of possible values contains the ~\r\n       element~a "));
    string_constant_5 = STATIC_STRING("s");
    string_constant_6 = STATIC_STRING("");
    string_constant_7 = STATIC_STRING("and");
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    if (Designations_in_rule == UNBOUND)
	Designations_in_rule = Nil;
    Qfor = STATIC_SYMBOL("FOR",AB_package);
    Qwhenever = STATIC_SYMBOL("WHENEVER",AB_package);
    Qis = STATIC_SYMBOL("IS",AB_package);
    Qis_not = STATIC_SYMBOL("IS-NOT",AB_package);
    Qis_not_related = STATIC_SYMBOL("IS-NOT-RELATED",AB_package);
    Qis_related = STATIC_SYMBOL("IS-RELATED",AB_package);
    Krelated_change = STATIC_SYMBOL("RELATED-CHANGE",Pkeyword);
    Knot_related = STATIC_SYMBOL("NOT-RELATED",Pkeyword);
    Krelated = STATIC_SYMBOL("RELATED",Pkeyword);
    Qfalse = STATIC_SYMBOL("FALSE",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qfalse,Qnot);
    Qthere_exists_literal = STATIC_SYMBOL("THERE-EXISTS-LITERAL",AB_package);
    Qfor_every_literal = STATIC_SYMBOL("FOR-EVERY-LITERAL",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qthere_exists_literal,
	    Qfor_every_literal);
    Qexpression = STATIC_SYMBOL("EXPRESSION",AB_package);
    Qdesignation = STATIC_SYMBOL("DESIGNATION",AB_package);
    Qscope = STATIC_SYMBOL("SCOPE",AB_package);
    Qany = STATIC_SYMBOL("ANY",AB_package);
    Qother = STATIC_SYMBOL("OTHER",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qfails_to_receive_a_value = STATIC_SYMBOL("FAILS-TO-RECEIVE-A-VALUE",
	    AB_package);
    Qis_moved = STATIC_SYMBOL("IS-MOVED",AB_package);
    Qis_moved_by_the_user = STATIC_SYMBOL("IS-MOVED-BY-THE-USER",AB_package);
    Qis_moved_by_g2 = STATIC_SYMBOL("IS-MOVED-BY-G2",AB_package);
    Qis_resized_by_the_user = STATIC_SYMBOL("IS-RESIZED-BY-THE-USER",
	    AB_package);
    Qbecomes_related = STATIC_SYMBOL("BECOMES-RELATED",AB_package);
    Qceases_to_be_related = STATIC_SYMBOL("CEASES-TO-BE-RELATED",AB_package);
    Qgeneric_event = STATIC_SYMBOL("GENERIC-EVENT",AB_package);
    Qhas_generic_event = STATIC_SYMBOL("HAS-GENERIC-EVENT",AB_package);
    Qis_activated = STATIC_SYMBOL("IS-ACTIVATED",AB_package);
    Qis_deactivated = STATIC_SYMBOL("IS-DEACTIVATED",AB_package);
    Qis_enabled = STATIC_SYMBOL("IS-ENABLED",AB_package);
    Qis_disabled = STATIC_SYMBOL("IS-DISABLED",AB_package);
    Qis_created = STATIC_SYMBOL("IS-CREATED",AB_package);
    Qgeneric_becomes_related = STATIC_SYMBOL("GENERIC-BECOMES-RELATED",
	    AB_package);
    Qgeneric_ceases_to_be_related = 
	    STATIC_SYMBOL("GENERIC-CEASES-TO-BE-RELATED",AB_package);
    Qgeneric_directly_connected_to = 
	    STATIC_SYMBOL("GENERIC-DIRECTLY-CONNECTED-TO",AB_package);
    Kconnected = STATIC_SYMBOL("CONNECTED",Pkeyword);
    Qgeneric_directly_disconnected_from = 
	    STATIC_SYMBOL("GENERIC-DIRECTLY-DISCONNECTED-FROM",AB_package);
    Qconnection = STATIC_SYMBOL("CONNECTION",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qany,Qconnection);
    Kdisconnected = STATIC_SYMBOL("DISCONNECTED",Pkeyword);
    Qdirectly_connected_to = STATIC_SYMBOL("DIRECTLY-CONNECTED-TO",AB_package);
    Qdirectly_disconnected_from = 
	    STATIC_SYMBOL("DIRECTLY-DISCONNECTED-FROM",AB_package);
    Qindirectly_connected_to = STATIC_SYMBOL("INDIRECTLY-CONNECTED-TO",
	    AB_package);
    Qindirectly_disconnected_from = 
	    STATIC_SYMBOL("INDIRECTLY-DISCONNECTED-FROM",AB_package);
    Qnupec_synchronization_occurs = 
	    STATIC_SYMBOL("NUPEC-SYNCHRONIZATION-OCCURS",AB_package);
    Qno_filter = STATIC_SYMBOL("NO-FILTER",AB_package);
    Qtrue = STATIC_SYMBOL("TRUE",AB_package);
    Qthis_workspace = STATIC_SYMBOL("THIS-WORKSPACE",AB_package);
    Qthis_rule = STATIC_SYMBOL("THIS-RULE",AB_package);
    Qframe_flags = STATIC_SYMBOL("FRAME-FLAGS",AB_package);
    Qrelated = STATIC_SYMBOL("RELATED",AB_package);
    Qbackward_chaining_link = STATIC_SYMBOL("BACKWARD-CHAINING-LINK",
	    AB_package);
    check_if_superior_classes_are_defined(Qbackward_chaining_link,
	    list_constant_5);
    string_constant_58 = 
	    STATIC_STRING("1p4z8r83H7y83H7y83H1y83H1y00001n1l8o1l8l1l83Cy000004z8r83H4y83H4y83H1y83H1y00001n1l8o1l8l1l83Cy000004z8r83H5y83H5y83H1y83H1y0000");
    string_constant_59 = 
	    STATIC_STRING("1n1l8o1l8l1l83Cy000004z8r83H6y83H6y83H1y83H1y00001n1l8o1l8l1l83Cy000004z8r83H8y83H8y83H1y83H1y00001n1l8o1l8l1l83Cy00000");
    string_constant_60 = 
	    STATIC_STRING("1r8q1n83H1y1l83=fy8t1p83H7y08o8l83Cy1p83H4y08o8l83Cy1p83H5y08o8l83Cy1p83H6y08o8l83Cy1p83H8y08o8l83Cy");
    temp = regenerate_optimized_constant(string_constant_46);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_58,
	    string_constant_59));
    add_class_to_environment(9,Qbackward_chaining_link,list_constant_5,Nil,
	    temp,Nil,temp_1,list_constant_5,
	    regenerate_optimized_constant(string_constant_60),Nil);
    Backward_chaining_link_class_description = 
	    lookup_global_or_kb_specific_property_value(Qbackward_chaining_link,
	    Class_description_gkbprop);
    Qcopy_frame_for_backward_chaining_link = 
	    STATIC_SYMBOL("COPY-FRAME-FOR-BACKWARD-CHAINING-LINK",AB_package);
    SET_SYMBOL_FUNCTION(Qcopy_frame_for_backward_chaining_link,
	    STATIC_FUNCTION(copy_frame_for_backward_chaining_link,NIL,
	    FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qcopy_frame_for_backward_chaining_link);
    set_get(Qbackward_chaining_link,Qcopy_frame,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcopy_frame),
	    Qclasses_which_define);
    temp_2 = CONS(Qbackward_chaining_link,temp);
    mutate_global_property(Qcopy_frame,temp_2,Qclasses_which_define);
    Qin_order = STATIC_SYMBOL("IN-ORDER",AB_package);
    Qsimultaneously = STATIC_SYMBOL("SIMULTANEOUSLY",AB_package);
    Qconclude_not = STATIC_SYMBOL("CONCLUDE-NOT",AB_package);
    Qconclude = STATIC_SYMBOL("CONCLUDE",AB_package);
    Qg2_defstruct_structure_name_rule_instance_g2_struct = 
	    STATIC_SYMBOL("RULE-INSTANCE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qexecute_backward_chaining_for_rules = 
	    STATIC_SYMBOL("EXECUTE-BACKWARD-CHAINING-FOR-RULES",AB_package);
    Qnever = STATIC_SYMBOL("NEVER",AB_package);
    SET_SYMBOL_FUNCTION(Qexecute_backward_chaining_for_rules,
	    STATIC_FUNCTION(execute_backward_chaining_for_rules,NIL,FALSE,
	    1,1));
    Qbackward_chaining = STATIC_SYMBOL("BACKWARD-CHAINING",AB_package);
    string_constant_8 = STATIC_STRING("depth first");
    string_constant_9 = STATIC_STRING("breadth first");
    string_constant_10 = 
	    STATIC_STRING("Scheduling ~NF for execution at priority ~a with ~NF as the ~a ~a ~\r\n               while ~a backward chaining for the value of ~NF.");
    string_constant_11 = 
	    STATIC_STRING("Scheduling ~NF for execution at priority ~a with ~NF as the ~a ~\r\n               while ~a backward chaining for the value of ~NF.");
    string_constant_12 = 
	    STATIC_STRING("Scheduling ~NF for execution at priority ~a while ~a ~\r\n           backward chaining for the value of ~NF.");
    Qkb_workspace = STATIC_SYMBOL("KB-WORKSPACE",AB_package);
    Qrule = STATIC_SYMBOL("RULE",AB_package);
    string_constant_13 = STATIC_STRING("the user");
    string_constant_14 = 
	    STATIC_STRING("Scheduling event chaining to ~nf with ~nf as ~a because ~nf was moved by ~nf.");
    string_constant_15 = 
	    STATIC_STRING("Scheduling event chaining to ~NF because ~NF was moved by ~NF.");
    Qgsi_interface = STATIC_SYMBOL("GSI-INTERFACE",AB_package);
    Qsafe_invoke_rules_for_existential_chaining = 
	    STATIC_SYMBOL("SAFE-INVOKE-RULES-FOR-EXISTENTIAL-CHAINING",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qsafe_invoke_rules_for_existential_chaining,
	    STATIC_FUNCTION(safe_invoke_rules_for_existential_chaining,NIL,
	    FALSE,4,4));
    if (Queue_existential_rules == UNBOUND)
	Queue_existential_rules = Nil;
    if (Queue_existential_rules_tail == UNBOUND)
	Queue_existential_rules_tail = Nil;
    Qreclaim_frame_serial_number = 
	    STATIC_SYMBOL("RECLAIM-FRAME-SERIAL-NUMBER",AB_package);
    Qg2_defstruct_structure_name_connection_g2_struct = 
	    STATIC_SYMBOL("CONNECTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qsimulation_details = STATIC_SYMBOL("SIMULATION-DETAILS",AB_package);
    string_constant_16 = 
	    STATIC_STRING("Scheduling event chaining to ~nf with ~nf as ~a because ~nf ~nf.");
    string_constant_17 = 
	    STATIC_STRING("Scheduling event chaining to ~NF because ~NF ~nf.");
    string_constant_18 = STATIC_STRING("was activated");
    string_constant_19 = STATIC_STRING("was deactivated");
    string_constant_20 = STATIC_STRING("was enabled");
    string_constant_21 = STATIC_STRING("was disabled");
    string_constant_22 = STATIC_STRING("was created");
    string_constant_23 = STATIC_STRING("has lost its value");
    string_constant_24 = 
	    STATIC_STRING("Scheduling event chaining to ~nf with ~nf as ~a because ~nf was resized by the user.");
    string_constant_25 = 
	    STATIC_STRING("Scheduling event chaining to ~NF because ~NF was resized by the user.");
    string_constant_26 = 
	    STATIC_STRING("Scheduling event chaining to ~NF with ~NF as ~A because ~NF failed ~\r\n         to receive a value.");
    string_constant_27 = 
	    STATIC_STRING("Scheduling event chaining to ~NF because ~NF failed to receive a value.");
    string_constant_28 = 
	    STATIC_STRING("Notifying ~NF that ~NF has been forced to have no current value.");
    string_constant_29 = 
	    STATIC_STRING("Notifying ~NF that the value of ~NF has expired.");
    string_constant_30 = 
	    STATIC_STRING("Executing update for ~NF because a new value was placed ~\r\n                 in the ~a of ~NF.");
    string_constant_31 = 
	    STATIC_STRING("Scheduling forward chaining to ~NF with ~NF as ~\r\n             the ~A with local name ~A because a new value ~\r\n             was placed in the ~A of ~NF.");
    string_constant_32 = 
	    STATIC_STRING("Scheduling forward chaining to ~NF with ~NF as the ~A ~\r\n             because a new value was placed in the ~A of ~NF.");
    string_constant_33 = 
	    STATIC_STRING("Scheduling forward chaining to ~NF because a new value was ~\r\n         placed in the ~A of ~NF.");
    Qregistered_event_detectors = 
	    STATIC_SYMBOL("REGISTERED-EVENT-DETECTORS",AB_package);
    string_constant_34 = 
	    STATIC_STRING("Scheduling chaining to ~NF with ~NF as ~A and ~NF as ~A ~\r\n          because a ~A relation was ~a for these items.");
    string_constant_35 = STATIC_STRING("established");
    string_constant_36 = STATIC_STRING("removed");
    string_constant_37 = 
	    STATIC_STRING("Scheduling chaining to ~NF with ~NF as ~A ~\r\n          because a ~A relation was ~A for ~NF and ~NF.");
    string_constant_38 = 
	    STATIC_STRING("Scheduling chaining to ~NF ~\r\n          because a ~A relation was ~A for ~NF and ~NF.");
    Qloose_end = STATIC_SYMBOL("LOOSE-END",AB_package);
    string_constant_39 = 
	    STATIC_STRING("Scheduling chaining to ~NF with ~NF as ~A and ~NF as ~A ~\r\n          because a connection was ~a for these items.");
    string_constant_40 = STATIC_STRING("broken");
    string_constant_41 = STATIC_STRING("made");
    string_constant_42 = 
	    STATIC_STRING("Scheduling chaining to ~NF with ~NF as ~A ~\r\n          because a connection of class ~A connected to ~NF was ~A.");
    string_constant_43 = 
	    STATIC_STRING("Scheduling chaining to ~NF ~\r\n          because a connection of class ~A connected to ~NF was ~A.");
    Qat_an_input = STATIC_SYMBOL("AT-AN-INPUT",AB_package);
    Qat_an_output = STATIC_SYMBOL("AT-AN-OUTPUT",AB_package);
    Qobject = STATIC_SYMBOL("OBJECT",AB_package);
    string_constant_44 = 
	    STATIC_STRING("Scheduling event chaining to ~NF because a NUPEC synchronization ~\r\n           has occurred.");
    Qg2_invoke_generic_event_rules = 
	    STATIC_SYMBOL("G2-INVOKE-GENERIC-EVENT-RULES",AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_invoke_generic_event_rules,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_invoke_generic_event_rules,
	    STATIC_FUNCTION(g2_invoke_generic_event_rules,NIL,FALSE,3,3));
    list_constant_6 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)57344L);
    array_constant_1 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    Qcollected_focus_class_names_and_locals_equal = 
	    STATIC_SYMBOL("COLLECTED-FOCUS-CLASS-NAMES-AND-LOCALS-EQUAL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcollected_focus_class_names_and_locals_equal,
	    STATIC_FUNCTION(collected_focus_class_names_and_locals_equal,
	    NIL,FALSE,2,2));
    Qchaining_link_focus_class_name = 
	    STATIC_SYMBOL("CHAINING-LINK-FOCUS-CLASS-NAME",AB_package);
    Qchaining_link_focus_local_name_is_specified = 
	    STATIC_SYMBOL("CHAINING-LINK-FOCUS-LOCAL-NAME-IS-SPECIFIED",
	    AB_package);
    Qchaining_link_focus_local_name = 
	    STATIC_SYMBOL("CHAINING-LINK-FOCUS-LOCAL-NAME",AB_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Qg2_get_forward_chaining_focus_info = 
	    STATIC_SYMBOL("G2-GET-FORWARD-CHAINING-FOCUS-INFO",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_get_forward_chaining_focus_info,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_forward_chaining_focus_info,
	    STATIC_FUNCTION(g2_get_forward_chaining_focus_info,NIL,FALSE,1,1));
    Qg2_get_backward_chaining_rules_for_variable = 
	    STATIC_SYMBOL("G2-GET-BACKWARD-CHAINING-RULES-FOR-VARIABLE",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_get_backward_chaining_rules_for_variable,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_backward_chaining_rules_for_variable,
	    STATIC_FUNCTION(g2_get_backward_chaining_rules_for_variable,
	    NIL,FALSE,1,1));
}
