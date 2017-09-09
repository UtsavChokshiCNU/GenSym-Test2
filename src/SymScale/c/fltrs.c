/* fltrs.c
 * Input file:  filters.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "fltrs.h"


DEFINE_VARIABLE_WITH_SYMBOL(Available_filter_conses, Qavailable_filter_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_filter_conses_tail, Qavailable_filter_conses_tail);

Object Available_filter_conses_vector = UNBOUND;

Object Available_filter_conses_tail_vector = UNBOUND;

Object Filter_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Filter_cons_counter, Qfilter_cons_counter);

/* OUTSTANDING-FILTER-CONSES */
Object outstanding_filter_conses()
{
    Object temp;

    x_note_fn_call(180,0);
    temp = FIXNUM_MINUS(Filter_cons_counter,length(Available_filter_conses));
    return VALUES_1(temp);
}

/* FILTER-CONS-MEMORY-USAGE */
Object filter_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(180,1);
    temp = FIXNUM_TIMES(Filter_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-FILTER-CONS-POOL */
Object replenish_filter_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(180,2);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qfilter_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_filter_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_filter_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_filter_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_filter_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_filter_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Filter_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qfilter;             /* filter */

/* FILTER-CONS-1 */
Object filter_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(180,3);
    new_cons = ISVREF(Available_filter_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_filter_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_filter_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_filter_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_filter_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qfilter);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-FILTER-LIST-POOL */
Object replenish_filter_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(180,4);
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
    if (ISVREF(Available_filter_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_filter_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_filter_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_filter_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_filter_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qfilter_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-FILTER-LIST-1 */
Object make_filter_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(180,5);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_filter_conses_vector,
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
	replenish_filter_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_filter_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qfilter);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_filter_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_filter_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_filter_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_filter_conses_tail_vector;
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

/* FILTER-LIST-2 */
Object filter_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(180,6);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_filter_conses_vector,IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_filter_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_filter_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qfilter);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_filter_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_filter_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_filter_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_filter_conses_tail_vector;
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

/* FILTER-LIST-3 */
Object filter_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(180,7);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_filter_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_filter_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_filter_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qfilter);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_filter_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_filter_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_filter_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_filter_conses_tail_vector;
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

/* FILTER-LIST-4 */
Object filter_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(180,8);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_filter_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_filter_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_filter_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qfilter);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_filter_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_filter_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_filter_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_filter_conses_tail_vector;
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

/* FILTER-LIST-TRACE-HOOK */
Object filter_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(180,9);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-FILTER-CONSES-1 */
Object copy_tree_using_filter_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(180,10);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_filter_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_filter_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_filter_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_filter_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_filter_cons_pool();
	temp_1 = copy_tree_using_filter_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qfilter);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_filter_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_filter_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_filter_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_filter_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_filter_cons_pool();
	temp_1 = copy_tree_using_filter_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qfilter);
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

/* COPY-LIST-USING-FILTER-CONSES-1 */
Object copy_list_using_filter_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(180,11);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_filter_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_filter_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_filter_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_filter_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_filter_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qfilter);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_filter_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_filter_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_filter_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_filter_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_filter_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qfilter);
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

/* RECLAIM-FILTER-CONS-1 */
Object reclaim_filter_cons_1(filter_cons)
    Object filter_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(180,12);
    inline_note_reclaim_cons(filter_cons,Qfilter);
    if (ISVREF(Available_filter_conses_tail_vector,
		IFIX(Current_thread_index))) {
	temp = ISVREF(Available_filter_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = filter_cons;
	temp = Available_filter_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = filter_cons;
    }
    else {
	temp = Available_filter_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = filter_cons;
	temp = Available_filter_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = filter_cons;
    }
    M_CDR(filter_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-FILTER-LIST-1 */
Object reclaim_filter_list_1(filter_list)
    Object filter_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(180,13);
    if (filter_list) {
	last_1 = filter_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qfilter);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qfilter);
	if (ISVREF(Available_filter_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_filter_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = filter_list;
	    temp = Available_filter_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_filter_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = filter_list;
	    temp = Available_filter_conses_tail_vector;
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

/* RECLAIM-FILTER-LIST*-1 */
Object reclaim_filter_list_star_1(filter_list)
    Object filter_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(180,14);
    if (CONSP(filter_list)) {
	temp = last(filter_list,_);
	M_CDR(temp) = Nil;
	if (filter_list) {
	    last_1 = filter_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qfilter);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qfilter);
	    if (ISVREF(Available_filter_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_filter_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = filter_list;
		temp = Available_filter_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_filter_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = filter_list;
		temp = Available_filter_conses_tail_vector;
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

/* RECLAIM-FILTER-TREE-1 */
Object reclaim_filter_tree_1(tree)
    Object tree;
{
    Object e, e2, filter_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(180,15);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_filter_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		filter_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(filter_cons,Qfilter);
		if (EQ(filter_cons,e))
		    goto end_1;
		else if ( !TRUEP(filter_cons))
		    goto end_1;
		else
		    filter_cons = CDR(filter_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_filter_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_filter_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_filter_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_filter_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_filter_conses_tail_vector;
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

/* DELETE-FILTER-ELEMENT-1 */
Object delete_filter_element_1(element,filter_list)
    Object element, filter_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(180,16);
    if (filter_list) {
	if (EQ(element,M_CAR(filter_list))) {
	    temp = CDR(filter_list);
	    inline_note_reclaim_cons(filter_list,Qfilter);
	    if (ISVREF(Available_filter_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_filter_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = filter_list;
		temp_1 = Available_filter_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = filter_list;
	    }
	    else {
		temp_1 = Available_filter_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = filter_list;
		temp_1 = Available_filter_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = filter_list;
	    }
	    M_CDR(filter_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = filter_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qfilter);
		if (ISVREF(Available_filter_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_filter_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_filter_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_filter_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_filter_conses_tail_vector;
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
	    temp = filter_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-FILTER-CONS-1 */
Object delete_filter_cons_1(filter_cons,filter_list)
    Object filter_cons, filter_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(180,17);
    if (EQ(filter_cons,filter_list))
	temp = CDR(filter_list);
    else {
	l_trailer_qm = Nil;
	l = filter_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,filter_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = filter_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_filter_cons_1(filter_cons);
    return VALUES_1(temp);
}

/* RECLAIM-FILTER-LIST-FUNCTION */
Object reclaim_filter_list_function(list_1)
    Object list_1;
{
    Object last_1, next_qm, temp, svref_arg_2;

    x_note_fn_call(180,18);
    if (list_1) {
	last_1 = list_1;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qfilter);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qfilter);
	if (ISVREF(Available_filter_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_filter_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = list_1;
	    temp = Available_filter_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_filter_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = list_1;
	    temp = Available_filter_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
	return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* RECLAIM-FILTER-TREE-FUNCTION */
Object reclaim_filter_tree_function(list_1)
    Object list_1;
{
    x_note_fn_call(180,19);
    return reclaim_filter_tree_1(list_1);
}

/* FILTER-CONS-FUNCTION */
Object filter_cons_function(car_1,cdr_1)
    Object car_1, cdr_1;
{
    x_note_fn_call(180,20);
    return filter_cons_1(car_1,cdr_1);
}

/* FILTER-COPY */
Object filter_copy(thing)
    Object thing;
{
    x_note_fn_call(180,21);
    if (CONSP(thing))
	return copy_tree_using_filter_conses_1(thing);
    else
	return VALUES_1(thing);
}

static Object Quser_mode_is_not_a_symbol;  /* user-mode-is-not-a-symbol */

static Object Quser_mode_may_not_be_nil;  /* user-mode-may-not-be-nil */

static Object Q;                   /* || */

static Object Quser_mode_may_not_be_an_empty_string;  /* user-mode-may-not-be-an-empty-string */

static Object Qproprietary;        /* proprietary */

static Object Qcannot_enter_proprietary_mode;  /* cannot-enter-proprietary-mode */

/* VALIDATE-AS-POSSIBLE-USER-MODE */
Object validate_as_possible_user_mode(user_mode)
    Object user_mode;
{
    Object temp;

    x_note_fn_call(180,22);
    temp =  !SYMBOLP(user_mode) ? Quser_mode_is_not_a_symbol : Nil;
    if (temp);
    else
	temp =  !TRUEP(user_mode) ? Quser_mode_may_not_be_nil : Nil;
    if (temp);
    else
	temp = EQ(user_mode,Q) ? Quser_mode_may_not_be_an_empty_string : Nil;
    if (temp);
    else
	temp = EQ(user_mode,Qproprietary) ? Qcannot_enter_proprietary_mode 
		: Nil;
    return VALUES_1(temp);
}

/* COMPILE-G2-USER-MODE-FOR-LOGIN-FOR-SLOT */
Object compile_g2_user_mode_for_login_for_slot varargs_1(int, n)
{
    Object parsed_user_mode, frame, gensymed_symbol;
    Declare_varargs_nonrelocating;

    x_note_fn_call(180,23);
    INIT_ARGS_nonrelocating();
    parsed_user_mode = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return check_and_install_new_g2_user_mode_for_login(parsed_user_mode,
	    frame);
}

static Object Qg2_login_user_name_qm;  /* g2-login-user-name? */

static Object Qui_client_session;  /* ui-client-session */

static Object Qui_client_session_user_name;  /* ui-client-session-user-name */

static Object Qg2_user_name;       /* g2-user-name */

static Object string_constant;     /* "Attempting to change the user-mode on an item for which that is not defined: ~NF" */

/* CHECK-AND-INSTALL-NEW-G2-USER-MODE-FOR-LOGIN */
Object check_and_install_new_g2_user_mode_for_login(parsed_user_mode,frame)
    Object parsed_user_mode, frame;
{
    Object trouble_qm, gensymed_symbol, sub_class_bit_vector, temp_1;
    Object gensymed_symbol_4, top_of_stack, message_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(180,24);
    trouble_qm = Nil;
    trouble_qm = validate_as_possible_user_mode(parsed_user_mode);
    if ( !TRUEP(trouble_qm)) {
	gensymed_symbol = ISVREF(frame,(SI_Long)1L);
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(G2_login_class_description,
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
	    temp_1 = get_slot_value_function(frame,Qg2_login_user_name_qm,Nil);
	else {
	    gensymed_symbol_4 = 
		    lookup_global_or_kb_specific_property_value(Qui_client_session,
		    Class_description_gkbprop);
	    if (gensymed_symbol_4) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_4,
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
	    if (temp)
		temp_1 = get_slot_value_function(frame,
			Qui_client_session_user_name,Nil);
	    else {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(G2_window_class_description,(SI_Long)18L));
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
		if (temp)
		    temp_1 = get_slot_value_function(frame,Qg2_user_name,Nil);
		else {
		    top_of_stack = Cached_top_of_stack;
		    message_1 = tformat_stack_error_text_string(2,
			    string_constant,frame);
		    temp_1 = raw_stack_error_named_error(top_of_stack,
			    message_1);
		}
	    }
	}
	trouble_qm = validate_user_mode_for_user(temp_1,parsed_user_mode);
    }
    if ( !TRUEP(trouble_qm))
	update_user_mode_state(frame,parsed_user_mode);
    if (trouble_qm) {
	if (SYMBOLP(trouble_qm))
	    trouble_qm = string_for_localized_symbol(trouble_qm);
	return VALUES_2(Bad_phrase,trouble_qm);
    }
    else
	return VALUES_1(parsed_user_mode);
}

static Object array_constant;      /* # */

static Object Qnone;               /* none */

/* COMPILE-G2-USER-MODE-FOR-LOGIN?-FOR-SLOT */
Object compile_g2_user_mode_for_login_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(180,25);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(parse_result,Qproprietary)) {
	temp = Bad_phrase;
	temp_1 = copy_constant_wide_string_given_length(array_constant,
		FIX((SI_Long)34L));
	return VALUES_2(temp,temp_1);
    }
    else if (EQ(parse_result,Qnone))
	return VALUES_1(Nil);
    else
	return VALUES_1(parse_result);
}

static Object list_constant;       /* # */

/* G2-USER-MODE-FOR-LOGIN-EVALUATION-SETTER */
Object g2_user_mode_for_login_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(180,26);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      Qsymbol,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_g2_user_mode_for_login_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_g2_user_mode_for_login_evaluation_setter:
    return result;
}

/* G2-USER-MODE-FOR-LOGIN-EVALUATION-GETTER */
Object g2_user_mode_for_login_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(180,27);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

/* G2-USER-MODE-FOR-LOGIN?-EVALUATION-GETTER */
Object g2_user_mode_for_login_qm_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(180,28);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

Object Item_menu_choices = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Table_menu_choices, Qtable_menu_choices);

DEFINE_VARIABLE_WITH_SYMBOL(Global_keyboard_command_choices, Qglobal_keyboard_command_choices);

DEFINE_VARIABLE_WITH_SYMBOL(Main_menu_choices, Qmain_menu_choices);

DEFINE_VARIABLE_WITH_SYMBOL(Workspace_menu_choices, Qworkspace_menu_choices);

Object Menu_and_attribute_visibility_configurations_restriction_types = UNBOUND;

Object Menu_configuration_operation_types = UNBOUND;

static Object Qg2;                 /* g2 */

static Object Qexecute;            /* execute */

static Object Qinform;             /* inform */

static Object Qconnect;            /* connect */

static Object Qgsi;                /* gsi */

static Object Qtelewindows;        /* telewindows */

static Object Qnetwork_access;     /* network-access */

/* FIX-NETWORK-CONFIGURATION-CLAUSE */
Object fix_network_configuration_clause(raw_network_configuration)
    Object raw_network_configuration;
{
    Object network_configuration, network_options, raw_network_option;
    Object ab_loop_list_, product_or_products, configuration, product;
    Object ab_loop_list__1, temp, temp_1, gensymed_symbol, gensymed_symbol_1;
    Object temp_2;

    x_note_fn_call(180,29);
    network_configuration = 
	    fix_object_configuration_clause(raw_network_configuration);
    network_options = Nil;
    raw_network_option = Nil;
    ab_loop_list_ = REST(network_configuration);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    raw_network_option = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    product_or_products = FIRST(raw_network_option);
    if (CONSP(product_or_products)) {
	configuration = SECOND(raw_network_option);
	product = Nil;
	ab_loop_list__1 = CDR(product_or_products);
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	product = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	temp = product;
	temp_1 = copy_list_using_phrase_conses(configuration);
	if (EQ(product,Qg2)) {
	    gensymed_symbol = make_phrase_list(FIX((SI_Long)5L));
	    gensymed_symbol_1 = gensymed_symbol;
	    M_CAR(gensymed_symbol_1) = Qexecute;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = Qinform;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = Qread;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = Qwrite;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = Qconnect;
	    temp_2 = gensymed_symbol;
	}
	else if (EQ(product,Qgsi))
	    temp_2 = phrase_list_3(Qexecute,Qinform,Qconnect);
	else if (EQ(product,Qtelewindows))
	    temp_2 = phrase_cons(Qconnect,Nil);
	else
	    temp_2 = Qnil;
	network_options = phrase_cons(phrase_list_4(temp,Nil,temp_1,
		temp_2),network_options);
	goto next_loop_1;
      end_loop_1:;
    }
    else
	network_options = phrase_cons(raw_network_option,network_options);
    goto next_loop;
  end_loop:;
    return phrase_cons(Qnetwork_access,nreverse(network_options));
}

static Object list_constant_1;     /* # */

/* FIX-OBJECT-CONFIGURATION-CLAUSE */
Object fix_object_configuration_clause(form)
    Object form;
{
    x_note_fn_call(180,30);
    if (memq_function(SECOND(form),list_constant_1))
	return phrase_cons(FIRST(form),CDDR(form));
    else
	return VALUES_1(form);
}

/* MASSAGE-USER-DECLARATION-CLAUSE */
Object massage_user_declaration_clause(user_declaration_clause)
    Object user_declaration_clause;
{
    Object form, temp, temp_1, temp_2, p, v, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, ab_loop_desetq_;

    x_note_fn_call(180,31);
    form = user_declaration_clause;
    if (memq_function(THIRD(form),list_constant_1))
	form = phrase_cons(FIRST(form),phrase_cons(SECOND(form),CDDDR(form)));
    temp = THIRD(form);
    if (CONSP(temp)) {
	temp_1 = FIRST(form);
	temp_2 = SECOND(form);
	p = Nil;
	v = Nil;
	ab_loop_list_ = CDDR(form);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	p = CAR(ab_loop_desetq_);
	temp = CDR(ab_loop_desetq_);
	v = CAR(temp);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = phrase_cons(p,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	ab_loopvar__2 = phrase_cons(v,Nil);
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
	return phrase_cons(temp_1,phrase_cons(temp_2,temp));
    }
    else
	return VALUES_1(form);
}

static Object Qno_manual_connections;  /* no-manual-connections */

static Object Qmanual_connections;  /* manual-connections */

static Object Qitem;               /* item */

/* MAKE-DECLARATION-CLAUSE-FOR-ITEM-CONFIGURATION */
Object make_declaration_clause_for_item_configuration varargs_1(int, n)
{
    Object property_1, value;
    Object class_qm, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(180,32);
    INIT_ARGS_nonrelocating();
    property_1 = REQUIRED_ARG_nonrelocating();
    value = REQUIRED_ARG_nonrelocating();
    class_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (EQ(property_1,Qno_manual_connections)) {
	property_1 = Qmanual_connections;
	value =  !TRUEP(value) ? T : Nil;
    }
    temp = class_qm;
    if (temp);
    else
	temp = Qitem;
    return slot_value_list_4(Qdeclaration,slot_value_cons_1(temp,Nil),
	    property_1,value ? T : Nil);
}

/* STRING-TO-DISPLAY-FOR-KEYBOARD-SYMBOL */
Object string_to_display_for_keyboard_symbol(keysym,do_not_downcase_qm)
    Object keysym, do_not_downcase_qm;
{
    Object temp;

    x_note_fn_call(180,33);
    temp = copy_symbol_name(2,keysym,Nil);
    return VALUES_1(temp);
}

static Object Qfor_filters;        /* for-filters */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object Qat;                 /* @ */

static Object array_constant_1;    /* # */

/* STRING-TO-INSERT-FOR-KEYBOARD-SYMBOL */
Object string_to_insert_for_keyboard_symbol(keysym)
    Object keysym;
{
    Object write_symbols_parsably_qm, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(6);

    x_note_fn_call(180,34);
    write_symbols_parsably_qm = Qfor_filters;
    PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
	    5);
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
		    length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
		    (SI_Long)16L));
	    PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		    1);
	      current_twriting_output_type = Qwide_string;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		      0);
		if (EQ(keysym,Qat))
		    twrite_beginning_of_wide_string(array_constant_1,
			    FIX((SI_Long)2L));
		else
		    twrite_key_code(key_code_function(keysym,Nil,T));
		temp = copy_out_current_wide_string();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

static Object list_constant_2;     /* # */

/* FIX-ITEM-FILTER-PHRASE */
Object fix_item_filter_phrase(phrase)
    Object phrase;
{
    x_note_fn_call(180,35);
    if ( !TRUEP(phrase))
	return VALUES_1(Nil);
    else if (ATOM(phrase))
	return VALUES_1(phrase);
    else if (memq_function(FIRST(phrase),list_constant_2))
	return VALUES_1(CDR(phrase));
    else
	return VALUES_1(phrase);
}

static Object array_constant_2;    /* # */

/* GRID-SPEC-MUST-BE-POSITIVE */
Object grid_spec_must_be_positive(grid_spec)
    Object grid_spec;
{
    Object temp, temp_1;

    x_note_fn_call(180,36);
    if (IFIX(CAR(grid_spec)) > (SI_Long)0L && IFIX(CDR(grid_spec)) > 
	    (SI_Long)0L)
	return VALUES_1(grid_spec);
    else {
	temp = Bad_phrase;
	temp_1 = copy_constant_wide_string_given_length(array_constant_2,
		FIX((SI_Long)44L));
	return VALUES_2(temp,temp_1);
    }
}

static Object string_constant_1;   /* "double-clicking " */

static Object string_constant_2;   /* "clicking " */

static Object string_constant_3;   /* "pressing " */

static Object string_constant_4;   /* "releasing " */

static Object string_constant_5;   /* "any mouse button" */

static Object string_constant_6;   /* "the left mouse button" */

static Object string_constant_7;   /* "the middle mouse button" */

static Object string_constant_8;   /* "the right mouse button" */

/* TWRITE-MOUSE-BUTTON-FOR-FILTERS */
Object twrite_mouse_button_for_filters(key_code)
    Object key_code;
{
    Object unicode, gensymed_symbol, temp, key;

    x_note_fn_call(180,37);
    if (IFIX(FIXNUM_LOGAND(key_code,Double_bit)) != (SI_Long)0L) {
	key_code = FIXNUM_LOGAND(Double_mask,key_code);
	twrite(string_constant_1);
    }
    else {
	if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	    unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	    gensymed_symbol = num_len(3,FIX((SI_Long)0L),unicode,
		    FIX((SI_Long)127L)) ? unicode : Illegal_key_index;
	}
	else
	    gensymed_symbol = FIXNUM_LOGAND(Key_index_bits,key_code);
	if (IFIX(gensymed_symbol) == (SI_Long)779L || 
		IFIX(gensymed_symbol) == (SI_Long)812L || 
		IFIX(gensymed_symbol) == (SI_Long)813L || 
		IFIX(gensymed_symbol) == (SI_Long)814L)
	    twrite(string_constant_2);
	else {
	    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
		unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
		temp = num_len(3,FIX((SI_Long)0L),unicode,
			FIX((SI_Long)127L)) ? unicode : Illegal_key_index;
	    }
	    else
		temp = FIXNUM_LOGAND(Key_index_bits,key_code);
	    if (EQ(temp,FIX((SI_Long)770L)) || EQ(temp,FIX((SI_Long)772L)) 
		    || EQ(temp,FIX((SI_Long)774L)) || EQ(temp,
		    FIX((SI_Long)776L)))
		twrite(string_constant_3);
	    else
		twrite(string_constant_4);
	}
    }
    twrite_key_modifier_bits(key_code,Nil);
    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	key = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) ? 
		unicode : Illegal_key_index;
    }
    else
	key = FIXNUM_LOGAND(Key_index_bits,key_code);
    if (IFIX(key) == (SI_Long)770L || IFIX(key) == (SI_Long)769L || 
	    IFIX(key) == (SI_Long)779L)
	return twrite(string_constant_5);
    else if (IFIX(key) == (SI_Long)772L || IFIX(key) == (SI_Long)773L || 
	    IFIX(key) == (SI_Long)812L)
	return twrite(string_constant_6);
    else if (IFIX(key) == (SI_Long)774L || IFIX(key) == (SI_Long)775L || 
	    IFIX(key) == (SI_Long)813L)
	return twrite(string_constant_7);
    else if (IFIX(key) == (SI_Long)776L || IFIX(key) == (SI_Long)777L || 
	    IFIX(key) == (SI_Long)814L)
	return twrite(string_constant_8);
    else
	return VALUES_1(Nil);
}

static Object Qany_mouse_button;   /* any-mouse-button */

static Object Qclicking;           /* clicking */

static Object Qmouse_select;       /* mouse-select */

static Object Qpressing;           /* pressing */

static Object Qmouse_down;         /* mouse-down */

static Object Qreleasing;          /* releasing */

static Object Qmouse_up;           /* mouse-up */

static Object Qdouble_clicking;    /* double-clicking */

static Object Qleft_mouse_button;  /* left-mouse-button */

static Object Qmouse_left_select;  /* mouse-left-select */

static Object Qmouse_left_down;    /* mouse-left-down */

static Object Qmouse_left_up;      /* mouse-left-up */

static Object Qmiddle_mouse_button;  /* middle-mouse-button */

static Object Qmouse_middle_select;  /* mouse-middle-select */

static Object Qmouse_middle_down;  /* mouse-middle-down */

static Object Qmouse_middle_up;    /* mouse-middle-up */

static Object Qright_mouse_button;  /* right-mouse-button */

static Object Qmouse_right_select;  /* mouse-right-select */

static Object Qmouse_right_down;   /* mouse-right-down */

static Object Qmouse_right_up;     /* mouse-right-up */

/* DISAMBIGUATE-MOUSE-BUTTON */
Object disambiguate_mouse_button(pseudo_button,ui_clause_type)
    Object pseudo_button, ui_clause_type;
{
    Object temp;

    x_note_fn_call(180,38);
    if (EQ(pseudo_button,Qany_mouse_button)) {
	if (EQ(ui_clause_type,Qclicking))
	    temp = Qmouse_select;
	else if (EQ(ui_clause_type,Qpressing))
	    temp = Qmouse_down;
	else if (EQ(ui_clause_type,Qreleasing))
	    temp = Qmouse_up;
	else if (EQ(ui_clause_type,Qdouble_clicking))
	    temp = Qmouse_select;
	else
	    temp = Qnil;
    }
    else if (EQ(pseudo_button,Qleft_mouse_button)) {
	if (EQ(ui_clause_type,Qclicking))
	    temp = Qmouse_left_select;
	else if (EQ(ui_clause_type,Qpressing))
	    temp = Qmouse_left_down;
	else if (EQ(ui_clause_type,Qreleasing))
	    temp = Qmouse_left_up;
	else if (EQ(ui_clause_type,Qdouble_clicking))
	    temp = Qmouse_left_select;
	else
	    temp = Qnil;
    }
    else if (EQ(pseudo_button,Qmiddle_mouse_button)) {
	if (EQ(ui_clause_type,Qclicking))
	    temp = Qmouse_middle_select;
	else if (EQ(ui_clause_type,Qpressing))
	    temp = Qmouse_middle_down;
	else if (EQ(ui_clause_type,Qreleasing))
	    temp = Qmouse_middle_up;
	else if (EQ(ui_clause_type,Qdouble_clicking))
	    temp = Qmouse_middle_select;
	else
	    temp = Qnil;
    }
    else if (EQ(pseudo_button,Qright_mouse_button)) {
	if (EQ(ui_clause_type,Qclicking))
	    temp = Qmouse_right_select;
	else if (EQ(ui_clause_type,Qpressing))
	    temp = Qmouse_right_down;
	else if (EQ(ui_clause_type,Qreleasing))
	    temp = Qmouse_right_up;
	else if (EQ(ui_clause_type,Qdouble_clicking))
	    temp = Qmouse_right_select;
	else
	    temp = Qnil;
    }
    else
	temp = Qnil;
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(pseudo_button);
}

static Object Qdouble;             /* double */

/* DISAMBIGUATE-MOUSE-BUTTON-IN-PHRASE */
Object disambiguate_mouse_button_in_phrase(phrase,ui_clause_type)
    Object phrase, ui_clause_type;
{
    Object key_spec, element, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2;

    x_note_fn_call(180,39);
    if (ATOM(phrase))
	key_spec = disambiguate_mouse_button(phrase,ui_clause_type);
    else {
	element = Nil;
	ab_loop_list_ = phrase;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = phrase_cons(disambiguate_mouse_button(element,
		ui_clause_type),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	key_spec = ab_loopvar_;
	goto end_1;
	key_spec = Qnil;
      end_1:;
    }
    if (EQ(ui_clause_type,Qdouble_clicking)) {
	if (ATOM(key_spec))
	    return phrase_list_2(Qdouble,key_spec);
	else
	    return phrase_cons(Qdouble,key_spec);
    }
    else
	return VALUES_1(key_spec);
}

static Object Qtyping;             /* typing */

static Object Qrolling;            /* rolling */

static Object Qhovering;           /* hovering */

static Object Qselecting;          /* selecting */

static Object Qcm;                 /* \, */

static Object string_constant_9;   /* "Not a known keyboard symbol" */

static Object string_constant_10;  /* "You are not allowed to rebind control+y" */

/* PARSE-USER-INTERFACE-GESTURE */
Object parse_user_interface_gesture(phrase)
    Object phrase;
{
    Object type, key_spec, key_code, action, classes, type_to_store, temp;

    x_note_fn_call(180,40);
    type = FIRST(phrase);
    key_spec = disambiguate_mouse_button_in_phrase(SECOND(phrase),type);
    key_code = key_code_from_list(key_spec);
    action = THIRD(phrase);
    classes = FOURTH(phrase);
    if (EQ(type,Qpressing))
	type_to_store = Qclicking;
    else if (EQ(type,Qreleasing))
	type_to_store = Qclicking;
    else if (EQ(type,Qclicking))
	type_to_store = type;
    else if (EQ(type,Qdouble_clicking))
	type_to_store = Qclicking;
    else if (EQ(type,Qtyping))
	type_to_store = Qpressing;
    else if (EQ(type,Qrolling))
	type_to_store = Qpressing;
    else if (EQ(type,Qhovering))
	type_to_store = Qpressing;
    else if (EQ(type,Qselecting))
	type_to_store = type;
    else
	type_to_store = type;
    if (CONSP(classes) && EQ(CAR(classes),Qcm))
	classes = CDR(classes);
    if (FIXNUM_EQ(Illegal_key_code,key_code))
	return VALUES_2(Bad_phrase,string_constant_9);
    else if (FIXNUM_EQ(key_code,FIX((SI_Long)25L)))
	return VALUES_2(Bad_phrase,string_constant_10);
    else if (CONSP(action)) {
	temp = copy_list_using_phrase_conses(action);
	return phrase_list_4(type_to_store,key_code,temp,classes);
    }
    else
	return phrase_list_4(type_to_store,key_code,action,classes);
}

/* PARSE-USER-INTERFACE-KEY-CHORD */
Object parse_user_interface_key_chord(chord)
    Object chord;
{
    Object chord_old_value;

    x_note_fn_call(180,41);
    if (CONSP(chord))
	chord = phrase_flatten_tree(chord);
    if (EQ(FIRST(chord),Qplus)) {
	chord_old_value = chord;
	chord = REST(chord_old_value);
    }
    return VALUES_1(chord);
}

/* REMOVE-SEPARATOR-SYMBOL-FROM-PHRASE */
Object remove_separator_symbol_from_phrase(phrase)
    Object phrase;
{
    x_note_fn_call(180,42);
    return VALUES_1(CDR(phrase));
}

DEFINE_VARIABLE_WITH_SYMBOL(Non_menu_choices, Qnon_menu_choices);

static Object Qnothing;            /* nothing */

/* PROHIBIT-NOTHING */
Object prohibit_nothing(form)
    Object form;
{
    x_note_fn_call(180,43);
    if (memq_function(Qnothing,form))
	return VALUES_1(Bad_phrase);
    else
	return VALUES_1(form);
}

/* CONS-CAR-CDDR */
Object cons_car_cddr(value)
    Object value;
{
    x_note_fn_call(180,44);
    return phrase_cons(CAR(value),CDDR(value));
}

static Object Qsc;                 /* \; */

/* FIX-MODE-RESTRICTION */
Object fix_mode_restriction(form)
    Object form;
{
    x_note_fn_call(180,45);
    if (EQ(THIRD(form),Qsc))
	return phrase_cons(FIRST(form),phrase_cons(SECOND(form),CDDDR(form)));
    else
	return phrase_list_3(FIRST(form),SECOND(form),CDDR(form));
}

static Object Qworkspace;          /* workspace */

/* DONT-INCLUDE-WORKSPACE */
Object dont_include_workspace(form)
    Object form;
{
    x_note_fn_call(180,46);
    if (EQ(form,Qworkspace) || CONSP(form) && memq_function(Qworkspace,form))
	return VALUES_1(Bad_phrase);
    else
	return VALUES_1(form);
}

/* FIX-ASSOCIATIVE-LIST */
Object fix_associative_list(form,n_1)
    Object form, n_1;
{
    Object list_qm, l, item, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object ab_loop_iter_flag_;
    SI_Long i;

    x_note_fn_call(180,47);
    list_qm = nth(n_1,form);
    l = form;
    item = Nil;
    i = (SI_Long)0L;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(l))
	goto end_loop;
    item = CAR(l);
    if ( !TRUEP(ab_loop_iter_flag_))
	i = i + (SI_Long)1L;
    if ((SI_Long)0L == i ||  !TRUEP(memq_function(item,CDR(l)))) {
	ab_loopvar__2 = phrase_cons(i == IFIX(n_1) ? (CONSP(list_qm) && 
		memq_function(CAR(list_qm),list_constant_2) ? CDR(list_qm) 
		: phrase_cons(list_qm,Nil)) : item,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    ab_loop_iter_flag_ = Nil;
    l = M_CDR(l);
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

/* FIX-TAILING-ASSOCIATIVE-LIST */
Object fix_tailing_associative_list(form,n_1)
    Object form, n_1;
{
    Object tail, l, item, front, ab_loopvar_, ab_loopvar__1;
    Object ab_loop_iter_flag_, ll, ab_loop_it_;
    SI_Long i, ab_loop_bind_;
    char temp;

    x_note_fn_call(180,48);
    tail = nthcdr(n_1,form);
    i = (SI_Long)1L;
    ab_loop_bind_ = IFIX(n_1);
    l = form;
    item = Nil;
    front = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loop_iter_flag_ = T;
  next_loop:
    if (i > ab_loop_bind_)
	goto end_loop;
    if ( !TRUEP(ab_loop_iter_flag_))
	l = M_CDR(l);
    if ( !TRUEP(l))
	goto end_loop;
    item = CAR(l);
    ll = CDR(l);
    ab_loop_it_ = Nil;
  next_loop_1:
    if (EQ(ll,tail))
	goto end_loop_1;
    ab_loop_it_ = EQ(CAR(ll),item) ? T : Nil;
    if (ab_loop_it_) {
	temp = TRUEP(ab_loop_it_);
	goto end_1;
    }
    ll = CDR(ll);
    goto next_loop_1;
  end_loop_1:
    temp = TRUEP(Qnil);
  end_1:;
    if ( !temp) {
	ab_loopvar__1 = phrase_cons(item,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    front = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
    }
    ab_loop_iter_flag_ = Nil;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(nconc2(front,CONSP(tail) && memq_function(CAR(tail),
	    list_constant_2) ? CDR(tail) : phrase_cons(tail,Nil)));
    return VALUES_1(Qnil);
}

/* WRITE-OBJECT-CONFIGURATION-FROM-SLOT */
Object write_object_configuration_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(180,49);
    return write_object_configuration(value);
}

static Object Qobject_configuration;  /* object-configuration */

/* RECLAIM-OBJECT-CONFIGURATION-VALUE */
Object reclaim_object_configuration_value(value,frame)
    Object value, frame;
{
    x_note_fn_call(180,50);
    add_or_delete_mode_names_from_item_configuration(value,T);
    reclaim_slot_value(value);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,Qobject_configuration);
    set_lookup_slot_value_1(frame,Qobject_configuration,Nil);
    return VALUES_1(Nil);
}

static Object string_constant_11;  /* ";~%" */

static Object string_constant_12;  /* "none" */

/* WRITE-OBJECT-CONFIGURATION */
Object write_object_configuration(object_configuration)
    Object object_configuration;
{
    Object length_1, some_1, clause;
    SI_Long i;

    x_note_fn_call(180,51);
    length_1 = length(object_configuration);
    some_1 = Nil;
    i = IFIX(FIXNUM_SUB1(length_1));
    clause = Nil;
  next_loop:
    if (i < (SI_Long)0L)
	goto end_loop;
    clause = nth(FIX(i),object_configuration);
    if (some_1)
	tformat(1,string_constant_11);
    write_object_configuration_clause(clause);
    some_1 = T;
    i = i - (SI_Long)1L;
    goto next_loop;
  end_loop:
    if ( !TRUEP(some_1))
	twrite(string_constant_12);
    return VALUES_1(Qnil);
}

static Object Qconfigure;          /* configure */

static Object Quser_interface;     /* user-interface */

static Object string_constant_13;  /* "configure the user interface as follows:~%" */

static Object string_constant_14;  /* "declare" */

static Object string_constant_15;  /* " ~(~a~a~)" */

static Object string_constant_16;  /* "" */

static Object string_constant_17;  /* "not " */

static Object string_constant_18;  /* "declare properties" */

static Object string_constant_19;  /* " of" */

static Object string_constant_20;  /* " as follows:~%  " */

static Object string_constant_21;  /* ", " */

static Object string_constant_22;  /* "set up network access as follows:" */

static Object string_constant_23;  /* "~%    " */

static Object string_constant_24;  /* ",~%    " */

static Object Qinclude_additionally;  /* include-additionally */

static Object string_constant_25;  /* "allow" */

static Object Qexclude_additionally;  /* exclude-additionally */

static Object string_constant_26;  /* "prohibit" */

static Object Qexclude_absolutely;  /* exclude-absolutely */

static Object string_constant_27;  /* "prohibit absolutely" */

static Object Qinclude;            /* include */

static Object string_constant_28;  /* "allow precisely" */

static Object Qexclude;            /* exclude */

static Object string_constant_29;  /* "prohibit precisely" */

static Object string_constant_30;  /* " " */

static Object Qab_or;              /* or */

static Object string_constant_31;  /* " access" */

static Object string_constant_32;  /* " to " */

static Object Qany;                /* any */

static Object string_constant_33;  /* " by G2" */

static Object string_constant_34;  /* " by GSI" */

static Object string_constant_35;  /* " by Telewindows" */

static Object Qg2_and_gsi;         /* g2-and-gsi */

static Object string_constant_36;  /* " by G2 and GSI" */

static Object Qg2_and_telewindows;  /* g2-and-telewindows */

static Object string_constant_37;  /* " by G2 and Telewindows" */

static Object string_constant_38;  /* "restrict proprietary items as follows:" */

static Object string_constant_39;  /* "~%  " */

static Object string_constant_40;  /* ";~%  " */

static Object Qcomment;            /* comment */

static Object string_constant_41;  /* "comment as follows:" */

static Object string_constant_42;  /* "~%   " */

static Object string_constant_43;  /* ",~%   " */

static Object string_constant_44;  /* "~(~a: ~s~)" */

/* WRITE-OBJECT-CONFIGURATION-CLAUSE */
Object write_object_configuration_clause(clause)
    Object clause;
{
    Object temp, gensymed_symbol, property_1, value, class_spec, plist;
    Object sublist, last_item, accessor, classes, inclusion, access_types;
    Object ab_loop_list_, first_1, ab_loop_iter_flag_, ab_loop_desetq_;
    Object restriction_clause, symbol, string_qm, temp_1;

    x_note_fn_call(180,52);
    temp = FIRST(clause);
    if (EQ(temp,Qconfigure) || EQ(temp,Quser_interface)) {
	tformat(1,string_constant_13);
	return write_user_restrictions(CDR(clause));
    }
    else if (EQ(temp,Qdeclare)) {
	gensymed_symbol = CDR(clause);
	property_1 = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	value = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	class_spec = CAR(gensymed_symbol);
	twrite(string_constant_14);
	write_list_of_classes_in_object_configuration(1,class_spec);
	return tformat(3,string_constant_15,value ? string_constant_16 : 
		string_constant_17,property_1);
    }
    else if (EQ(temp,Qdeclaration)) {
	class_spec = M_CAR(M_CDR(clause));
	plist = M_CDR(M_CDR(clause));
	twrite(string_constant_18);
	if (class_spec) {
	    twrite(string_constant_19);
	    write_list_of_classes_in_object_configuration(1,class_spec);
	}
	tformat(1,string_constant_20);
	sublist = plist;
	property_1 = Nil;
	value = Nil;
	last_item = Nil;
      next_loop:
	if ( !TRUEP(sublist))
	    goto end_loop;
	property_1 = CAR(sublist);
	temp = CDR(sublist);
	value = CAR(temp);
	last_item =  !TRUEP(CDDR(sublist)) ? T : Nil;
	if ( !TRUEP(value))
	    twrite(string_constant_17);
	twrite_symbol(1,property_1);
	if ( !TRUEP(last_item))
	    twrite(string_constant_21);
	sublist = CDDR(sublist);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else if (EQ(temp,Qnetwork_access)) {
	twrite(string_constant_22);
	temp = SECOND(clause);
	if (CONSP(temp)) {
	    accessor = Nil;
	    classes = Nil;
	    inclusion = Nil;
	    access_types = Nil;
	    ab_loop_list_ = CDR(clause);
	    first_1 = T;
	    ab_loop_iter_flag_ = T;
	    ab_loop_desetq_ = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    ab_loop_desetq_ = M_CAR(ab_loop_list_);
	    accessor = CAR(ab_loop_desetq_);
	    temp = CDR(ab_loop_desetq_);
	    classes = CAR(temp);
	    temp = CDR(ab_loop_desetq_);
	    temp = CDR(temp);
	    inclusion = CAR(temp);
	    temp = CDR(ab_loop_desetq_);
	    temp = CDR(temp);
	    temp = CDR(temp);
	    access_types = CAR(temp);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(ab_loop_iter_flag_))
		first_1 = Nil;
	    if (first_1)
		tformat(1,string_constant_23);
	    else
		tformat(1,string_constant_24);
	    if (EQ(inclusion,Qinclude_additionally))
		twrite(string_constant_25);
	    else if (EQ(inclusion,Qexclude_additionally))
		twrite(string_constant_26);
	    else if (EQ(inclusion,Qexclude_absolutely))
		twrite(string_constant_27);
	    else if (EQ(inclusion,Qinclude))
		twrite(string_constant_28);
	    else if (EQ(inclusion,Qexclude))
		twrite(string_constant_29);
	    if (access_types) {
		twrite(string_constant_30);
		write_symbol_list(3,access_types,Qcm,Qab_or);
	    }
	    twrite(string_constant_31);
	    if (classes)
		write_list_of_classes_in_object_configuration(2,classes,
			string_constant_32);
	    if (EQ(accessor,Qany));
	    else if (EQ(accessor,Qg2))
		twrite(string_constant_33);
	    else if (EQ(accessor,Qgsi))
		twrite(string_constant_34);
	    else if (EQ(accessor,Qtelewindows))
		twrite(string_constant_35);
	    else if (EQ(accessor,Qg2_and_gsi))
		twrite(string_constant_36);
	    else if (EQ(accessor,Qg2_and_telewindows))
		twrite(string_constant_37);
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_1;
	  end_loop_1:
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (EQ(temp,Qproprietary)) {
	twrite(string_constant_38);
	restriction_clause = Nil;
	ab_loop_list_ = CDR(clause);
	first_1 = T;
	ab_loop_iter_flag_ = T;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	restriction_clause = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    first_1 = Nil;
	if (first_1)
	    tformat(1,string_constant_39);
	else
	    tformat(1,string_constant_40);
	write_restriction_clause(restriction_clause);
	ab_loop_iter_flag_ = Nil;
	goto next_loop_2;
      end_loop_2:
	return VALUES_1(Qnil);
    }
    else if (EQ(temp,Qcomment)) {
	twrite(string_constant_41);
	symbol = Nil;
	string_qm = Nil;
	ab_loop_list_ = CDR(clause);
	first_1 = T;
	ab_loop_iter_flag_ = T;
	ab_loop_desetq_ = Nil;
      next_loop_3:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_3;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	symbol = CAR(ab_loop_desetq_);
	temp = CDR(ab_loop_desetq_);
	string_qm = CAR(temp);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    first_1 = Nil;
	if (first_1)
	    tformat(1,string_constant_42);
	else
	    tformat(1,string_constant_43);
	temp = symbol;
	temp_1 = string_qm;
	if (temp_1);
	else
	    temp_1 = Qnone;
	tformat(3,string_constant_44,temp,temp_1);
	ab_loop_iter_flag_ = Nil;
	goto next_loop_3;
      end_loop_3:
	return VALUES_1(Qnil);
    }
    else
	return twrite(clause);
}

static Object string_constant_45;  /* "~(~Athis ~A~)" */

static Object string_constant_46;  /* "~Aany " */

/* WRITE-LIST-OF-CLASSES-IN-OBJECT-CONFIGURATION */
Object write_list_of_classes_in_object_configuration varargs_1(int, n)
{
    Object classes;
    Object prefix, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(180,53);
    INIT_ARGS_nonrelocating();
    classes = REQUIRED_ARG_nonrelocating();
    prefix = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : string_constant_30;
    END_ARGS_nonrelocating();
    temp =  !TRUEP(classes) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else if (ATOM(classes))
	return tformat(3,string_constant_45,prefix,classes);
    else {
	tformat(2,string_constant_46,prefix);
	return write_symbol_list(3,classes,Qcm,Qab_or);
    }
}

/* WRITE-USER-RESTRICTIONS */
Object write_user_restrictions(user_restrictions)
    Object user_restrictions;
{
    Object length_1;
    SI_Long i;

    x_note_fn_call(180,54);
    if ( !TRUEP(user_restrictions))
	return twrite(string_constant_12);
    else {
	length_1 = length(user_restrictions);
	i = IFIX(FIXNUM_SUB1(length_1));
      next_loop:
	if (i < (SI_Long)0L)
	    goto end_loop;
	write_mode_restriction(nth(FIX(i),user_restrictions));
	if (i > (SI_Long)0L)
	    tformat(1,string_constant_11);
	i = i - (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

static Object string_constant_47;  /* "when in " */

static Object string_constant_48;  /* "unless in " */

static Object string_constant_49;  /* "nothing" */

static Object string_constant_50;  /* " mode:~%  " */

/* WRITE-MODE-RESTRICTION */
Object write_mode_restriction(mode_restriction)
    Object mode_restriction;
{
    Object restriction_clauses, length_1;
    SI_Long i;

    x_note_fn_call(180,55);
    twrite(EQ(FIRST(mode_restriction),Qwhen) ? string_constant_47 : 
	    string_constant_48);
    write_symbol_list(4,SECOND(mode_restriction),Nil,Qab_or,
	    string_constant_49);
    tformat(1,string_constant_50);
    restriction_clauses = CDDR(mode_restriction);
    length_1 = length(restriction_clauses);
    i = IFIX(FIXNUM_SUB1(length_1));
  next_loop:
    if (i < (SI_Long)0L)
	goto end_loop;
    write_restriction_clause(nth(FIX(i),restriction_clauses));
    if (i > (SI_Long)0L)
	tformat(1,string_constant_40);
    i = i - (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object string_constant_51;  /* "rolling " */

static Object string_constant_52;  /* "the mouse wheel forward" */

static Object string_constant_53;  /* "the mouse wheel backward" */

static Object string_constant_54;  /* "hovering " */

static Object string_constant_55;  /* "the mouse" */

static Object string_constant_56;  /* "typing " */

/* TWRITE-KEY-CODE-FOR-FILTERS */
Object twrite_key_code_for_filters(key_code)
    Object key_code;
{
    Object unicode, key, write_symbols_parsably_qm, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object string_1, write_strings_parsably_qm;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(6);
    Object result;

    x_note_fn_call(180,56);
    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	key = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) ? 
		unicode : Illegal_key_index;
    }
    else
	key = FIXNUM_LOGAND(Key_index_bits,key_code);
    if (IFIX(key) == (SI_Long)780L) {
	twrite(string_constant_51);
	twrite_key_modifier_bits(key_code,Nil);
	return twrite(string_constant_52);
    }
    else if (IFIX(key) == (SI_Long)781L) {
	twrite(string_constant_51);
	twrite_key_modifier_bits(key_code,Nil);
	return twrite(string_constant_53);
    }
    else if (IFIX(key) == (SI_Long)782L) {
	twrite(string_constant_54);
	twrite_key_modifier_bits(key_code,Nil);
	return twrite(string_constant_55);
    }
    else {
	twrite(string_constant_56);
	write_symbols_parsably_qm = Qfor_filters;
	PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
		5);
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
		    twrite_key_code(key_code);
		    string_1 = copy_out_current_wide_string();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  write_strings_parsably_qm = T;
	  PUSH_SPECIAL_WITH_SYMBOL(Write_strings_parsably_qm,Qwrite_strings_parsably_qm,write_strings_parsably_qm,
		  0);
	    nstring_downcasew(string_1);
	    twrite_general_string(string_1);
	    result = reclaim_text_string(string_1);
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
}

static Object string_constant_57;  /* "~( ~a ~a~)" */

static Object string_constant_58;  /* " ~a " */

/* TWRITE-CLASS-SPEC-FOR-RESTRICTIONS */
Object twrite_class_spec_for_restrictions(class_spec,this_string,any_string)
    Object class_spec, this_string, any_string;
{
    Object temp;

    x_note_fn_call(180,57);
    temp =  !TRUEP(class_spec) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else if (ATOM(class_spec))
	return tformat(3,string_constant_57,this_string,class_spec);
    else {
	tformat(2,string_constant_58,any_string);
	return write_symbol_list(3,class_spec,Qcm,Qab_or);
    }
}

static Object Qmain_menu;          /* main-menu */

static Object string_constant_59;  /* "main menu choices" */

static Object Qglobal_keyboard_command;  /* global-keyboard-command */

static Object string_constant_60;  /* "global keyboard commands" */

static Object Qworkspace_menu;     /* workspace-menu */

static Object string_constant_61;  /* "menu choices for" */

static Object Qnon_menu;           /* non-menu */

static Object string_constant_62;  /* "non-menu choices for" */

static Object string_constant_63;  /* "selecting any" */

static Object Qdoes;               /* does */

static Object Qimplies;            /* implies */

static Object Qselecting_absolutely;  /* selecting-absolutely */

static Object Qdoes_absolutely;    /* does-absolutely */

static Object Qimplies_absolutely;  /* implies-absolutely */

static Object Qvisibility;         /* visibility */

static Object string_constant_64;  /* "attributes visible for" */

static Object Qtable;              /* table */

static Object string_constant_65;  /* "table menu choices for any" */

static Object string_constant_66;  /* "table menu choices for the" */

static Object Qconstrain;          /* constrain */

static Object Qmoving;             /* moving */

static Object string_constant_67;  /* "constrain moving" */

static Object string_constant_68;  /* "this" */

static Object string_constant_69;  /* "any" */

static Object string_constant_70;  /* " such that the item aligns on the grid (~d,~d)" */

static Object Qrectangle;          /* rectangle */

static Object string_constant_71;  /* " to the rectangle (~d,~d,~d,~d)" */

/* WRITE-RESTRICTION-CLAUSE */
Object write_restriction_clause(restriction_clause)
    Object restriction_clause;
{
    Object temp, temp_1, gensymed_symbol, kind, class_spec, info, dx, dy, left;
    Object right, bottom, top;

    x_note_fn_call(180,58);
    temp = FIRST(restriction_clause);
    if (EQ(temp,Qmain_menu))
	return write_restriction_clause_1(5,string_constant_59,Nil,Nil,
		SECOND(restriction_clause),CDDR(restriction_clause));
    else if (EQ(temp,Qglobal_keyboard_command))
	return write_restriction_clause_1(5,string_constant_60,Nil,Nil,
		SECOND(restriction_clause),CDDR(restriction_clause));
    else if (EQ(temp,Qworkspace_menu))
	return write_restriction_clause_1(5,string_constant_61,Nil,
		SECOND(restriction_clause),THIRD(restriction_clause),
		CDDDR(restriction_clause));
    else if (EQ(temp,Qnon_menu))
	return write_restriction_clause_1(5,string_constant_62,Nil,
		SECOND(restriction_clause),THIRD(restriction_clause),
		CDDDR(restriction_clause));
    else if (EQ(temp,Qselecting)) {
	temp = SECOND(restriction_clause);
	temp_1 = THIRD(restriction_clause);
	return write_restriction_clause_1(5,string_constant_63,Nil,temp,
		EQ(temp_1,Qnothing) ? Qdoes : Qimplies,
		THIRD(restriction_clause));
    }
    else if (EQ(temp,Qselecting_absolutely)) {
	temp = SECOND(restriction_clause);
	temp_1 = THIRD(restriction_clause);
	return write_restriction_clause_1(5,string_constant_63,Nil,temp,
		EQ(temp_1,Qnothing) ? Qdoes_absolutely : 
		Qimplies_absolutely,THIRD(restriction_clause));
    }
    else if (EQ(temp,Qvisibility))
	return write_restriction_clause_1(5,string_constant_64,Nil,
		SECOND(restriction_clause),FOURTH(restriction_clause),
		THIRD(restriction_clause));
    else if (EQ(temp,Qtable))
	return write_restriction_clause_1(5, 
		!TRUEP(THIRD(restriction_clause)) ? string_constant_65 : 
		string_constant_66,THIRD(restriction_clause) ? 
		THIRD(restriction_clause) : Nil,SECOND(restriction_clause),
		FOURTH(restriction_clause),CDDDDR(restriction_clause));
    else if (EQ(temp,Qclicking) || EQ(temp,Qpressing))
	return write_user_interface_clause(restriction_clause);
    else if (EQ(temp,Qconstrain)) {
	gensymed_symbol = CDR(restriction_clause);
	kind = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	class_spec = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	info = CAR(gensymed_symbol);
	if (EQ(kind,Qmoving)) {
	    gensymed_symbol = info;
	    dx = CAR(gensymed_symbol);
	    dy = CDR(gensymed_symbol);
	    tformat(1,string_constant_67);
	    twrite_class_spec_for_restrictions(class_spec,
		    string_constant_68,string_constant_69);
	    return tformat(3,string_constant_70,dx,dy);
	}
	else if (EQ(kind,Qrectangle)) {
	    gensymed_symbol = info;
	    left = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    right = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    bottom = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    top = CAR(gensymed_symbol);
	    tformat(1,string_constant_67);
	    twrite_class_spec_for_restrictions(class_spec,
		    string_constant_68,string_constant_69);
	    return tformat(5,string_constant_71,left,right,bottom,top);
	}
	else
	    return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Qnil);
}

static Object string_constant_72;  /* "over this" */

static Object string_constant_73;  /* "over any" */

static Object string_constant_74;  /* "on this" */

static Object string_constant_75;  /* "on any" */

static Object string_constant_76;  /* " does nothing" */

static Object string_constant_77;  /* " implies " */

static Object Quser_mouse_tracking;  /* user-mouse-tracking */

static Object string_constant_78;  /* "~( starts ~a as the mouse tracks" */

static Object string_constant_79;  /* " continuously over" */

static Object string_constant_80;  /* " over" */

/* WRITE-USER-INTERFACE-CLAUSE */
Object write_user_interface_clause(user_interface_clause)
    Object user_interface_clause;
{
    Object type, key_code, action, class_spec, write_symbols_in_lower_case_qm;
    Object unicode, temp, gensymed_symbol, procedure_name, motion;
    SI_Long temp_2;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(180,59);
    type = FIRST(user_interface_clause);
    key_code = SECOND(user_interface_clause);
    action = THIRD(user_interface_clause);
    class_spec = FOURTH(user_interface_clause);
    write_symbols_in_lower_case_qm = T;
    PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
	    0);
      if (EQ(type,Qclicking))
	  twrite_mouse_button_for_filters(key_code);
      else if (EQ(type,Qpressing))
	  twrite_key_code_for_filters(key_code);
      else
	  twrite(type);
      if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	  unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	  temp = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) ? 
		  unicode : Illegal_key_index;
      }
      else
	  temp = FIXNUM_LOGAND(Key_index_bits,key_code);
      temp_1 = EQ(temp,FIX((SI_Long)780L));
      if (temp_1);
      else
	  temp_1 = EQ(temp,FIX((SI_Long)781L));
      if (temp_1);
      else {
	  if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	      unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	      temp_2 = num_len(3,FIX((SI_Long)0L),unicode,
		      FIX((SI_Long)127L)) ? IFIX(unicode) : 
		      IFIX(Illegal_key_index);
	  }
	  else
	      temp_2 = IFIX(FIXNUM_LOGAND(Key_index_bits,key_code));
	  temp_1 = temp_2 == (SI_Long)782L;
      }
      if (temp_1)
	  twrite_class_spec_for_restrictions(class_spec,string_constant_72,
		  string_constant_73);
      else
	  twrite_class_spec_for_restrictions(class_spec,string_constant_74,
		  string_constant_75);
      if (EQ(action,Qnothing))
	  result = twrite(string_constant_76);
      else if (ATOM(action)) {
	  tformat(1,string_constant_77);
	  result = twrite(action);
      }
      else if (EQ(CAR(action),Quser_mouse_tracking)) {
	  gensymed_symbol = CDR(action);
	  procedure_name = CAR(gensymed_symbol);
	  gensymed_symbol = CDR(gensymed_symbol);
	  class_spec = CAR(gensymed_symbol);
	  gensymed_symbol = CDR(gensymed_symbol);
	  motion = CAR(gensymed_symbol);
	  tformat(2,string_constant_78,procedure_name);
	  if (motion)
	      twrite(string_constant_79);
	  else
	      twrite(string_constant_80);
	  result = twrite_class_spec_for_restrictions(class_spec,
		  string_constant_68,string_constant_69);
      }
      else
	  result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object Qclass_qualified_name;  /* class-qualified-name */

static Object string_constant_81;  /* " of " */

static Object string_constant_82;  /* " of any " */

static Object string_constant_83;  /* "does " */

static Object string_constant_84;  /* "absolutely does " */

static Object string_constant_85;  /* "implies " */

static Object string_constant_86;  /* "absolutely implies " */

static Object string_constant_87;  /* "include: " */

static Object string_constant_88;  /* "exclude: " */

static Object string_constant_89;  /* "include additionally: " */

static Object string_constant_90;  /* "exclude additionally: " */

static Object string_constant_91;  /* "exclude absolutely: " */

static Object Qwrite_name_denotation;  /* write-name-denotation */

/* WRITE-RESTRICTION-CLAUSE-1 */
Object write_restriction_clause_1 varargs_1(int, n)
{
    Object activity_description, attribute_name_or_list_qm;
    Object object_description_or_list_qm, restriction_type_qm;
    Object choice_or_choice_list;
    Object write_period_at_end_qm, temp, schar_arg_2, schar_new_value;
    Object name_or_class_qualified_name_list, temp_1;
    SI_Long thing;
    Declare_varargs_nonrelocating;

    x_note_fn_call(180,60);
    INIT_ARGS_nonrelocating();
    activity_description = REQUIRED_ARG_nonrelocating();
    attribute_name_or_list_qm = REQUIRED_ARG_nonrelocating();
    object_description_or_list_qm = REQUIRED_ARG_nonrelocating();
    restriction_type_qm = REQUIRED_ARG_nonrelocating();
    choice_or_choice_list = REQUIRED_ARG_nonrelocating();
    write_period_at_end_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    twrite_general_string(activity_description);
    if (EQ(Current_twriting_output_type,Qwide_string)) {
	thing = (SI_Long)32L;
	twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
    }
    else {
	if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		Total_length_of_current_gensym_string))
	    extend_current_gensym_string(0);
	temp = Current_gensym_string;
	schar_arg_2 = Fill_pointer_for_current_gensym_string;
	thing = (SI_Long)32L;
	schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
	SET_SCHAR(temp,schar_arg_2,schar_new_value);
	temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	Fill_pointer_for_current_gensym_string = temp;
    }
    if (attribute_name_or_list_qm) {
	if ( !TRUEP(object_description_or_list_qm))
	    error((SI_Long)1L,
		    "attribute-name-or-list\? but no object-description-or-list\?");
	if (ATOM(attribute_name_or_list_qm))
	    twrite(attribute_name_or_list_qm);
	else {
	    name_or_class_qualified_name_list = CAR(attribute_name_or_list_qm);
	    if (CONSP(name_or_class_qualified_name_list) && 
		    EQ(M_CAR(name_or_class_qualified_name_list),
		    Qclass_qualified_name))
		write_name_denotation(CAR(attribute_name_or_list_qm));
	    else
		write_symbol_list(4,attribute_name_or_list_qm,Nil,Qab_or,
			string_constant_49);
	}
	twrite(text_string_p(object_description_or_list_qm) ? 
		string_constant_81 : string_constant_82);
    }
    if (object_description_or_list_qm) {
	if (ATOM(object_description_or_list_qm))
	    twrite(object_description_or_list_qm);
	else
	    write_symbol_list(4,object_description_or_list_qm,Nil,Qab_or,
		    string_constant_49);
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = (SI_Long)32L;
	    twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = (SI_Long)32L;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp;
	}
    }
    if (restriction_type_qm) {
	if (EQ(restriction_type_qm,Qdoes))
	    temp_1 = string_constant_83;
	else if (EQ(restriction_type_qm,Qdoes_absolutely))
	    temp_1 = string_constant_84;
	else if (EQ(restriction_type_qm,Qimplies))
	    temp_1 = string_constant_85;
	else if (EQ(restriction_type_qm,Qimplies_absolutely))
	    temp_1 = string_constant_86;
	else if (EQ(restriction_type_qm,Qinclude))
	    temp_1 = string_constant_87;
	else if (EQ(restriction_type_qm,Qexclude))
	    temp_1 = string_constant_88;
	else if (EQ(restriction_type_qm,Qinclude_additionally))
	    temp_1 = string_constant_89;
	else if (EQ(restriction_type_qm,Qexclude_additionally))
	    temp_1 = string_constant_90;
	else if (EQ(restriction_type_qm,Qexclude_absolutely))
	    temp_1 = string_constant_91;
	else
	    temp_1 = Qnil;
	twrite(temp_1);
    }
    if (EQ(restriction_type_qm,Qimplies) || EQ(restriction_type_qm,
	    Qimplies_absolutely) || EQ(restriction_type_qm,Qdoes) || 
	    EQ(restriction_type_qm,Qdoes_absolutely))
	twrite(choice_or_choice_list);
    else
	twrite_list_function(choice_or_choice_list,
		SYMBOL_FUNCTION(Qwrite_name_denotation),string_constant_49,
		Nil,string_constant_21);
    if (write_period_at_end_qm) {
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = (SI_Long)46L;
	    return twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = (SI_Long)46L;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp;
	    return VALUES_1(Fill_pointer_for_current_gensym_string);
	}
    }
    else
	return VALUES_1(Nil);
}

/* ADD-OR-DELETE-MODE-NAMES-FROM-DIRECTORY-OF-NAMES */
Object add_or_delete_mode_names_from_directory_of_names(mode_restrictions,
	    delete_case_qm)
    Object mode_restrictions, delete_case_qm;
{
    Object mode_restriction, ab_loop_list_, mode_name, ab_loop_list__1;

    x_note_fn_call(180,61);
    mode_restriction = Nil;
    ab_loop_list_ = mode_restrictions;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    mode_restriction = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mode_name = Nil;
    ab_loop_list__1 = SECOND(mode_restriction);
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    mode_name = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    add_or_delete_mode_name_from_directory_of_names(mode_name,delete_case_qm);
    goto next_loop_1;
  end_loop_1:;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object list_constant_3;     /* # */

static Object Qdelete_from_directory_of_names;  /* delete-from-directory-of-names */

static Object Qadd_to_directory_of_names;  /* add-to-directory-of-names */

static Object Qnon_built_in_g2_user_mode;  /* non-built-in-g2-user-mode */

/* ADD-OR-DELETE-MODE-NAME-FROM-DIRECTORY-OF-NAMES */
Object add_or_delete_mode_name_from_directory_of_names(mode_name,
	    delete_case_qm)
    Object mode_name, delete_case_qm;
{
    Object temp;

    x_note_fn_call(180,62);
    if ( !TRUEP(memq_function(mode_name,list_constant_3))) {
	temp = SYMBOL_FUNCTION(delete_case_qm ? 
		Qdelete_from_directory_of_names : Qadd_to_directory_of_names);
	return FUNCALL_2(temp,mode_name,Qnon_built_in_g2_user_mode);
    }
    else
	return VALUES_1(Nil);
}

static Object list_constant_4;     /* # */

/* ADD-OR-DELETE-MODE-NAMES-FROM-ITEM-CONFIGURATION */
Object add_or_delete_mode_names_from_item_configuration(item_configuration,
	    delete_qm)
    Object item_configuration, delete_qm;
{
    Object clause, ab_loop_list_;

    x_note_fn_call(180,63);
    clause = Nil;
    ab_loop_list_ = item_configuration;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    clause = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (memq_function(FIRST(clause),list_constant_4))
	add_or_delete_mode_names_from_directory_of_names(CDR(clause),
		delete_qm);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qglobal_keyboard_command_user_restrictions;  /* global-keyboard-command-user-restrictions */

/* GLOBAL-KEYBOARD-COMMAND-USER-RESTRICTIONS-FUNCTION */
Object global_keyboard_command_user_restrictions_function(frame)
    Object frame;
{
    Object temp;

    x_note_fn_call(180,64);
    temp = get_lookup_slot_value_given_default(frame,
	    Qglobal_keyboard_command_user_restrictions,Nil);
    return VALUES_1(temp);
}

static Object Qmain_menu_user_restrictions;  /* main-menu-user-restrictions */

/* MAIN-MENU-USER-RESTRICTIONS-FUNCTION */
Object main_menu_user_restrictions_function(frame)
    Object frame;
{
    Object temp;

    x_note_fn_call(180,65);
    temp = get_lookup_slot_value_given_default(frame,
	    Qmain_menu_user_restrictions,Nil);
    return VALUES_1(temp);
}

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

static Object Qnote_status_of_simulated_product_authorization;  /* note-status-of-simulated-product-authorization */

/* INITIALIZE-AFTER-READING-FOR-KB-CONFIGURATION */
Object initialize_after_reading_for_kb_configuration(kb_configuration)
    Object kb_configuration;
{
    Object temp, frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;
    Declare_special(1);
    Object result;

    x_note_fn_call(180,66);
    PUSH_SPECIAL_WITH_SYMBOL(Kb_configuration,Qkb_configuration,kb_configuration,
	    0);
      if (EQ(get_lookup_slot_value_given_default(Kb_configuration,
	      Qname_or_names_for_frame,Nil),Qkb_restrictions)) {
	  temp = Kb_configuration;
	  put_name_or_names_for_frame(temp,
		  compute_name_of_system_frame(Qkb_configuration),Nil);
      }
      frame = Kb_configuration;
      sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
	      (SI_Long)11L),(SI_Long)4L);
      index_1 = (SI_Long)0L;
      ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	      (SI_Long)3L;
    next_loop:
      if (index_1 >= ab_loop_bind_)
	  goto end_loop;
      if (EQ(ISVREF(sub_vector_qm,index_1),Qkb_configuration)) {
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
      result = delete_frame_note_if_any(Qnote_status_of_simulated_product_authorization,
	      Kb_configuration);
    POP_SPECIAL();
    return result;
}

static Object Qinitial_g2_user_mode_for_this_kb;  /* initial-g2-user-mode-for-this-kb */

/* INSTALL-SYSTEM-TABLE-FOR-KB-CONFIGURATION */
Object install_system_table_for_kb_configuration(kb_configuration)
    Object kb_configuration;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(180,67);
    PUSH_SPECIAL_WITH_SYMBOL(Kb_configuration,Qkb_configuration,kb_configuration,
	    0);
      add_or_delete_mode_names_from_directory_of_names(get_lookup_slot_value_given_default(Kb_configuration,
	      Qmain_menu_user_restrictions,Nil),Nil);
      add_or_delete_mode_names_from_directory_of_names(get_lookup_slot_value_given_default(Kb_configuration,
	      Qglobal_keyboard_command_user_restrictions,Nil),Nil);
      if (get_lookup_slot_value_given_default(Kb_configuration,
	      Qinitial_g2_user_mode_for_this_kb,Nil))
	  add_or_delete_mode_name_from_directory_of_names(get_lookup_slot_value_given_default(Kb_configuration,
		  Qinitial_g2_user_mode_for_this_kb,Nil),Nil);
      result = setup_current_simulated_product_authorization();
    POP_SPECIAL();
    return result;
}

/* DEINSTALL-SYSTEM-TABLE-FOR-KB-CONFIGURATION */
Object deinstall_system_table_for_kb_configuration(kb_configuration)
    Object kb_configuration;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(180,68);
    PUSH_SPECIAL_WITH_SYMBOL(Kb_configuration,Qkb_configuration,kb_configuration,
	    0);
      add_or_delete_mode_names_from_directory_of_names(get_lookup_slot_value_given_default(Kb_configuration,
	      Qmain_menu_user_restrictions,Nil),T);
      add_or_delete_mode_names_from_directory_of_names(get_lookup_slot_value_given_default(Kb_configuration,
	      Qglobal_keyboard_command_user_restrictions,Nil),T);
      if (get_lookup_slot_value_given_default(Kb_configuration,
	      Qinitial_g2_user_mode_for_this_kb,Nil))
	  add_or_delete_mode_name_from_directory_of_names(get_lookup_slot_value_given_default(Kb_configuration,
		  Qinitial_g2_user_mode_for_this_kb,Nil),T);
      result = setup_current_simulated_product_authorization();
    POP_SPECIAL();
    return result;
}

/* COMPILE-MAIN-MENU-RESTRICTIONS-FOR-SLOT */
Object compile_main_menu_restrictions_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(180,69);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_user_restrictions(parse_result,T);
}

/* COMPILE-GLOBAL-KEYBOARD-COMMAND-RESTRICTIONS-FOR-SLOT */
Object compile_global_keyboard_command_restrictions_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(180,70);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_user_restrictions(parse_result,T);
}

/* PUT-MAIN-MENU-USER-RESTRICTIONS */
Object put_main_menu_user_restrictions(kb_restrictions_instance,
	    main_menu_user_restrictions,gensymed_symbol)
    Object kb_restrictions_instance, main_menu_user_restrictions;
    Object gensymed_symbol;
{
    x_note_fn_call(180,71);
    if (system_table_installed_p(kb_restrictions_instance)) {
	add_or_delete_mode_names_from_directory_of_names(get_lookup_slot_value_given_default(kb_restrictions_instance,
		Qmain_menu_user_restrictions,Nil),T);
	add_or_delete_mode_names_from_directory_of_names(main_menu_user_restrictions,
		Nil);
    }
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(kb_restrictions_instance,
		Qmain_menu_user_restrictions);
    set_lookup_slot_value_1(kb_restrictions_instance,
	    Qmain_menu_user_restrictions,main_menu_user_restrictions);
    if (system_table_installed_p(kb_restrictions_instance))
	decache_dynamic_menus(1,Qkb_configuration);
    return VALUES_1(main_menu_user_restrictions);
}

/* PUT-GLOBAL-KEYBOARD-COMMAND-USER-RESTRICTIONS */
Object put_global_keyboard_command_user_restrictions(kb_restrictions_instance,
	    global_keyboard_command_user_restrictions,gensymed_symbol)
    Object kb_restrictions_instance, global_keyboard_command_user_restrictions;
    Object gensymed_symbol;
{
    x_note_fn_call(180,72);
    if (system_table_installed_p(kb_restrictions_instance)) {
	add_or_delete_mode_names_from_directory_of_names(get_lookup_slot_value_given_default(kb_restrictions_instance,
		Qglobal_keyboard_command_user_restrictions,Nil),T);
	add_or_delete_mode_names_from_directory_of_names(global_keyboard_command_user_restrictions,
		Nil);
    }
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(kb_restrictions_instance,
		Qglobal_keyboard_command_user_restrictions);
    set_lookup_slot_value_1(kb_restrictions_instance,
	    Qglobal_keyboard_command_user_restrictions,
	    global_keyboard_command_user_restrictions);
    if (system_table_installed_p(kb_restrictions_instance))
	decache_dynamic_menus(1,Qkb_configuration);
    return VALUES_1(global_keyboard_command_user_restrictions);
}

/* COMPILE-USER-RESTRICTIONS-FOR-SLOT */
Object compile_user_restrictions_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(180,73);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_user_restrictions(parse_result,Nil);
}

static Object Qadministrator;      /* administrator */

static Object string_constant_92;  /* "You may not restrict administrator mode." */

static Object string_constant_93;  /* "You may not restrict proprietary mode here." */

static Object string_constant_94;  /* "You may not restrict proprietary mode using UNLESS." */

/* COMPILE-USER-RESTRICTIONS */
Object compile_user_restrictions(form,disallow_proprietary_mode_qm)
    Object form, disallow_proprietary_mode_qm;
{
    Object unreversed_form, mode_restriction, ab_loop_list_, when_or_unless;
    Object administrator_qm, proprietary_qm, problem_string_qm, temp, temp_1;
    Object cddr_new_value;

    x_note_fn_call(180,74);
    if ( !TRUEP(form))
	return VALUES_1(Nil);
    else if (EQ(form,Qnone))
	return VALUES_1(Nil);
    else {
	unreversed_form = CDR(form);
	mode_restriction = Nil;
	ab_loop_list_ = unreversed_form;
	when_or_unless = Nil;
	administrator_qm = Nil;
	proprietary_qm = Nil;
	problem_string_qm = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	mode_restriction = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	when_or_unless = FIRST(mode_restriction);
	administrator_qm = memq_function(Qadministrator,
		SECOND(mode_restriction));
	proprietary_qm = memq_function(Qproprietary,SECOND(mode_restriction));
	if (administrator_qm && EQ(when_or_unless,Qwhen))
	    problem_string_qm = string_constant_92;
	else if (proprietary_qm && disallow_proprietary_mode_qm)
	    problem_string_qm = string_constant_93;
	else if (proprietary_qm && EQ(when_or_unless,Qunless))
	    problem_string_qm = string_constant_94;
	else
	    problem_string_qm = Qnil;
	if (problem_string_qm) {
	    temp = Bad_phrase;
	    temp_1 = copy_text_string(problem_string_qm);
	    return VALUES_2(temp,temp_1);
	}
	goto next_loop;
      end_loop:
	mode_restriction = Nil;
	ab_loop_list_ = unreversed_form;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	mode_restriction = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	cddr_new_value = nreverse(CDDR(mode_restriction));
	M_CDDR(mode_restriction) = cddr_new_value;
	goto next_loop_1;
      end_loop_1:
	return nreverse(unreversed_form);
	return VALUES_1(Qnil);
	return VALUES_1(Qnil);
    }
}

static Object Quser_restrictions;  /* user-restrictions */

/* PUT-USER-RESTRICTIONS */
Object put_user_restrictions(kb_frame,user_restrictions,initializing_qm)
    Object kb_frame, user_restrictions, initializing_qm;
{
    Object temp, old_value;

    x_note_fn_call(180,75);
    if ( !TRUEP(initializing_qm) && in_order_p(kb_frame)) {
	reclaim_slot_value(user_restrictions);
	temp = get_lookup_slot_value_given_default(kb_frame,
		Quser_restrictions,Nil);
	return VALUES_2(temp,T);
    }
    else {
	add_or_delete_mode_names_from_directory_of_names(get_lookup_slot_value_given_default(kb_frame,
		Quser_restrictions,Nil),T);
	add_or_delete_mode_names_from_directory_of_names(user_restrictions,
		Nil);
	old_value = get_lookup_slot_value_given_default(kb_frame,
		Quser_restrictions,Nil);
	set_non_savable_lookup_slot_value(kb_frame,Quser_restrictions,Nil);
	reclaim_slot_value(old_value);
	copy_user_restrictions_into_object_configuration(kb_frame,
		user_restrictions);
	reclaim_slot_value(user_restrictions);
	temp = get_lookup_slot_value(kb_frame,Qobject_configuration);
	return VALUES_2(temp,T);
    }
}

static Object Qclass_restrictions;  /* class-restrictions */

/* PUT-CLASS-RESTRICTIONS */
Object put_class_restrictions(definition,class_restrictions,initializing_qm)
    Object definition, class_restrictions, initializing_qm;
{
    Object temp, old_value;

    x_note_fn_call(180,76);
    if ( !TRUEP(initializing_qm) && in_order_p(definition)) {
	reclaim_slot_value(class_restrictions);
	temp = get_lookup_slot_value_given_default(definition,
		Qclass_restrictions,Nil);
	return VALUES_2(temp,T);
    }
    else {
	add_or_delete_mode_names_from_directory_of_names(get_lookup_slot_value_given_default(definition,
		Qclass_restrictions,Nil),T);
	add_or_delete_mode_names_from_directory_of_names(class_restrictions,
		Nil);
	old_value = get_lookup_slot_value_given_default(definition,
		Qclass_restrictions,Nil);
	set_non_savable_lookup_slot_value(definition,Qclass_restrictions,Nil);
	reclaim_slot_value(old_value);
	copy_class_restrictions_into_instance_configuration(definition,
		class_restrictions);
	reclaim_slot_value(class_restrictions);
	temp = get_lookup_slot_value_given_default(definition,
		Qclass_restrictions,Nil);
	return VALUES_2(temp,T);
    }
}

static Object Qchanging_mode;      /* changing-mode */

/* PUT-INITIAL-G2-USER-MODE-FOR-THIS-KB */
Object put_initial_g2_user_mode_for_this_kb(kb_restrictions_instance,
	    new_value,initializing_qm)
    Object kb_restrictions_instance, new_value, initializing_qm;
{
    Object workstation, ab_loop_list_;

    x_note_fn_call(180,77);
    if (system_table_installed_p(kb_restrictions_instance)) {
	if ( !(initializing_qm ||  
		!TRUEP(get_lookup_slot_value_given_default(kb_restrictions_instance,
		Qinitial_g2_user_mode_for_this_kb,Nil))))
	    add_or_delete_mode_name_from_directory_of_names(get_lookup_slot_value_given_default(kb_restrictions_instance,
		    Qinitial_g2_user_mode_for_this_kb,Nil),T);
	if ( ! !TRUEP(new_value))
	    add_or_delete_mode_name_from_directory_of_names(new_value,Nil);
    }
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(kb_restrictions_instance,
		Qinitial_g2_user_mode_for_this_kb);
    set_lookup_slot_value_1(kb_restrictions_instance,
	    Qinitial_g2_user_mode_for_this_kb,new_value);
    if (System_is_running &&  !TRUEP(System_has_paused)) {
	workstation = Nil;
	ab_loop_list_ = Workstations_in_service;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	workstation = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	enter_change_user_mode_in_running(Qchanging_mode,workstation);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* WRITE-MAIN-MENU-RESTRICTIONS-FROM-SLOT */
Object write_main_menu_restrictions_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(180,78);
    return write_user_restrictions(value);
}

/* WRITE-GLOBAL-KEYBOARD-COMMAND-RESTRICTIONS-FROM-SLOT */
Object write_global_keyboard_command_restrictions_from_slot(value,
	    gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(180,79);
    return write_user_restrictions(value);
}

/* WRITE-USER-RESTRICTIONS-FROM-SLOT */
Object write_user_restrictions_from_slot(value,kb_frame)
    Object value, kb_frame;
{
    x_note_fn_call(180,80);
    return write_user_restrictions_from_object_configuration(get_lookup_slot_value(kb_frame,
	    Qobject_configuration));
}

/* WRITE-CLASS-RESTRICTIONS-FROM-SLOT */
Object write_class_restrictions_from_slot(value,definition)
    Object value, definition;
{
    x_note_fn_call(180,81);
    return write_user_restrictions_from_object_configuration(ISVREF(definition,
	    (SI_Long)23L));
}

/* WRITE-USER-RESTRICTIONS-FROM-OBJECT-CONFIGURATION */
Object write_user_restrictions_from_object_configuration(object_configuration)
    Object object_configuration;
{
    Object length_1, some_1, clause;
    SI_Long i;

    x_note_fn_call(180,82);
    length_1 = length(object_configuration);
    some_1 = Nil;
    i = IFIX(FIXNUM_SUB1(length_1));
    clause = Nil;
  next_loop:
    if (i < (SI_Long)0L)
	goto end_loop;
    clause = nth(FIX(i),object_configuration);
    if (memq_function(FIRST(clause),list_constant_4)) {
	if (some_1)
	    tformat(1,string_constant_11);
	write_user_restrictions(CDR(clause));
	some_1 = T;
    }
    i = i - (SI_Long)1L;
    goto next_loop;
  end_loop:
    if ( !TRUEP(some_1))
	twrite(string_constant_12);
    return VALUES_1(Qnil);
}

/* ENSURE-USER-INTERFACE-SECTION */
Object ensure_user_interface_section(item)
    Object item;
{
    Object temp, clause, slot_value_push_modify_macro_arg, car_1, cdr_1;
    Object object_configuration_new_value;

    x_note_fn_call(180,83);
    temp = assq_function(Quser_interface,get_lookup_slot_value(item,
	    Qobject_configuration));
    if (temp)
	return VALUES_1(temp);
    else {
	clause = slot_value_cons_1(Quser_interface,Nil);
	slot_value_push_modify_macro_arg = clause;
	car_1 = slot_value_push_modify_macro_arg;
	cdr_1 = get_lookup_slot_value(item,Qobject_configuration);
	object_configuration_new_value = slot_value_cons_1(car_1,cdr_1);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(item,Qobject_configuration);
	set_lookup_slot_value_1(item,Qobject_configuration,
		object_configuration_new_value);
	return VALUES_1(clause);
    }
}

/* ENSURE-PROPRIETARY-SECTION */
Object ensure_proprietary_section(item)
    Object item;
{
    Object temp, clause, slot_value_push_modify_macro_arg, car_1, cdr_1;
    Object object_configuration_new_value;

    x_note_fn_call(180,84);
    temp = assq_function(Qproprietary,get_lookup_slot_value(item,
	    Qobject_configuration));
    if (temp)
	return VALUES_1(temp);
    else {
	clause = slot_value_cons_1(Qproprietary,Nil);
	slot_value_push_modify_macro_arg = clause;
	car_1 = slot_value_push_modify_macro_arg;
	cdr_1 = get_lookup_slot_value(item,Qobject_configuration);
	object_configuration_new_value = slot_value_cons_1(car_1,cdr_1);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(item,Qobject_configuration);
	set_lookup_slot_value_1(item,Qobject_configuration,
		object_configuration_new_value);
	return VALUES_1(clause);
    }
}

/* ENSURE-USER-MODE-SECTION */
Object ensure_user_mode_section(item,when_or_unless,mode)
    Object item, when_or_unless, mode;
{
    Object user_interface_section, clause, ab_loop_list_, type, modes, temp;
    Object slot_value_push_modify_macro_arg, car_1, cdr_1, cdr_new_value;

    x_note_fn_call(180,85);
    if (EQ(mode,Qproprietary))
	return ensure_proprietary_section(item);
    else {
	user_interface_section = ensure_user_interface_section(item);
	clause = Nil;
	ab_loop_list_ = CDR(user_interface_section);
	type = Nil;
	modes = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	clause = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	type = CAR(clause);
	temp = CDR(clause);
	modes = CAR(temp);
	if (EQ(type,when_or_unless) && EQ(FIRST(modes),mode) &&  
		!TRUEP(REST(modes))) {
	    temp = clause;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
	if (temp)
	    return VALUES_1(temp);
	else {
	    clause = slot_value_list_2(when_or_unless,
		    slot_value_cons_1(mode,Nil));
	    slot_value_push_modify_macro_arg = clause;
	    car_1 = slot_value_push_modify_macro_arg;
	    cdr_1 = CDR(user_interface_section);
	    cdr_new_value = slot_value_cons_1(car_1,cdr_1);
	    M_CDR(user_interface_section) = cdr_new_value;
	    return VALUES_1(clause);
	}
    }
}

/* ENSURE-USER-INTERFACE-CLAUSE */
Object ensure_user_interface_clause(item,when_or_unless,mode,pattern)
    Object item, when_or_unless, mode, pattern;
{
    Object proprietary_section, clauses, clause, ab_loop_list_, binding_qm;
    Object binding, pattern_element, ab_loop_list__1, clause_element;
    Object ab_loop_list__2, star_qm, temp_1, slot_value_push_modify_macro_arg;
    Object car_1, cdr_1, temp_2, user_mode_section;
    char temp;

    x_note_fn_call(180,86);
    if (EQ(mode,Qproprietary)) {
	proprietary_section = ensure_proprietary_section(item);
	clauses = CDR(proprietary_section);
	clause = Nil;
	ab_loop_list_ = clauses;
	binding_qm = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	clause = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	binding = Nil;
	if (FIXNUM_EQ(length(clause),length(pattern))) {
	    pattern_element = Nil;
	    ab_loop_list__1 = pattern;
	    clause_element = Nil;
	    ab_loop_list__2 = clause;
	    star_qm = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_1;
	    pattern_element = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    if ( !TRUEP(ab_loop_list__2))
		goto end_loop_1;
	    clause_element = M_CAR(ab_loop_list__2);
	    ab_loop_list__2 = M_CDR(ab_loop_list__2);
	    star_qm = EQ(pattern_element,Qstar) ? T : Nil;
	    if (star_qm)
		binding = clause_element;
	    if ( !(star_qm || EQUAL(pattern_element,clause_element))) {
		temp = TRUEP(Nil);
		goto end_1;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp = TRUEP(T);
	    goto end_1;
	    temp = TRUEP(Qnil);
	  end_1:;
	}
	else
	    temp = TRUEP(Nil);
	binding_qm = temp ? binding : Nil;
	if (binding_qm) {
	    temp_1 = clause;
	    goto end_2;
	}
	goto next_loop;
      end_loop:
	temp_1 = Qnil;
      end_2:;
	if (temp_1)
	    return VALUES_1(temp_1);
	else {
	    clause = copy_list_using_slot_value_conses_1(pattern);
	    slot_value_push_modify_macro_arg = clause;
	    car_1 = slot_value_push_modify_macro_arg;
	    cdr_1 = CDR(proprietary_section);
	    temp_2 = slot_value_cons_1(car_1,cdr_1);
	    M_CDR(proprietary_section) = temp_2;
	    return VALUES_1(clause);
	}
    }
    else {
	user_mode_section = ensure_user_mode_section(item,when_or_unless,mode);
	clauses = CDDR(user_mode_section);
	clause = Nil;
	ab_loop_list_ = clauses;
	binding_qm = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	clause = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	binding = Nil;
	if (FIXNUM_EQ(length(clause),length(pattern))) {
	    pattern_element = Nil;
	    ab_loop_list__1 = pattern;
	    clause_element = Nil;
	    ab_loop_list__2 = clause;
	    star_qm = Nil;
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_3;
	    pattern_element = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    if ( !TRUEP(ab_loop_list__2))
		goto end_loop_3;
	    clause_element = M_CAR(ab_loop_list__2);
	    ab_loop_list__2 = M_CDR(ab_loop_list__2);
	    star_qm = EQ(pattern_element,Qstar) ? T : Nil;
	    if (star_qm)
		binding = clause_element;
	    if ( !(star_qm || EQUAL(pattern_element,clause_element))) {
		temp = TRUEP(Nil);
		goto end_3;
	    }
	    goto next_loop_3;
	  end_loop_3:
	    temp = TRUEP(T);
	    goto end_3;
	    temp = TRUEP(Qnil);
	  end_3:;
	}
	else
	    temp = TRUEP(Nil);
	binding_qm = temp ? binding : Nil;
	if (binding_qm) {
	    temp_1 = clause;
	    goto end_4;
	}
	goto next_loop_2;
      end_loop_2:
	temp_1 = Qnil;
      end_4:;
	if (temp_1)
	    return VALUES_1(temp_1);
	else {
	    clause = copy_list_using_slot_value_conses_1(pattern);
	    slot_value_push_modify_macro_arg = clause;
	    car_1 = slot_value_push_modify_macro_arg;
	    cdr_1 = CDDR(user_mode_section);
	    temp_2 = slot_value_cons_1(car_1,cdr_1);
	    M_CDDR(user_mode_section) = temp_2;
	    return VALUES_1(clause);
	}
    }
}

/* FIND-USER-INTERFACE-CLAUSE */
Object find_user_interface_clause(item,when_or_unless,mode,pattern)
    Object item, when_or_unless, mode, pattern;
{
    Object major_clause, ab_loop_list_, clauses, clause, ab_loop_list__1;
    Object binding_qm, binding, pattern_element, ab_loop_list__2;
    Object clause_element, ab_loop_list__3, star_qm, clause_qm, mode_clause;
    Object type, modes, temp_1, ab_loop_list__4;
    char temp;
    Object result;

    x_note_fn_call(180,87);
    if (EQ(mode,Qproprietary)) {
	major_clause = Nil;
	ab_loop_list_ = get_lookup_slot_value(item,Qobject_configuration);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	major_clause = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(FIRST(major_clause),Qproprietary)) {
	    clauses = CDR(major_clause);
	    clause = Nil;
	    ab_loop_list__1 = clauses;
	    binding_qm = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_1;
	    clause = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    binding = Nil;
	    if (FIXNUM_EQ(length(clause),length(pattern))) {
		pattern_element = Nil;
		ab_loop_list__2 = pattern;
		clause_element = Nil;
		ab_loop_list__3 = clause;
		star_qm = Nil;
	      next_loop_2:
		if ( !TRUEP(ab_loop_list__2))
		    goto end_loop_2;
		pattern_element = M_CAR(ab_loop_list__2);
		ab_loop_list__2 = M_CDR(ab_loop_list__2);
		if ( !TRUEP(ab_loop_list__3))
		    goto end_loop_2;
		clause_element = M_CAR(ab_loop_list__3);
		ab_loop_list__3 = M_CDR(ab_loop_list__3);
		star_qm = EQ(pattern_element,Qstar) ? T : Nil;
		if (star_qm)
		    binding = clause_element;
		if ( !(star_qm || EQUAL(pattern_element,clause_element))) {
		    temp = TRUEP(Nil);
		    goto end_1;
		}
		goto next_loop_2;
	      end_loop_2:
		temp = TRUEP(T);
		goto end_1;
		temp = TRUEP(Qnil);
	      end_1:;
	    }
	    else
		temp = TRUEP(Nil);
	    binding_qm = temp ? binding : Nil;
	    if (binding_qm) {
		result = VALUES_2(clause,binding_qm);
		goto end_2;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    result = VALUES_1(Qnil);
	  end_2:;
	    MVS_2(result,clause_qm,binding_qm);
	    if (clause_qm)
		return VALUES_2(clause_qm,binding_qm);
	}
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else {
	major_clause = Nil;
	ab_loop_list_ = get_lookup_slot_value(item,Qobject_configuration);
      next_loop_3:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_3;
	major_clause = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (memq_function(FIRST(major_clause),list_constant_4)) {
	    mode_clause = Nil;
	    ab_loop_list__1 = CDR(major_clause);
	    type = Nil;
	    modes = Nil;
	  next_loop_4:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_4;
	    mode_clause = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    type = CAR(mode_clause);
	    temp_1 = CDR(mode_clause);
	    modes = CAR(temp_1);
	    if (EQ(type,when_or_unless) && EQ(FIRST(modes),mode) &&  
		    !TRUEP(REST(modes))) {
		clauses = CDDR(mode_clause);
		clause = Nil;
		ab_loop_list__2 = clauses;
		binding_qm = Nil;
	      next_loop_5:
		if ( !TRUEP(ab_loop_list__2))
		    goto end_loop_5;
		clause = M_CAR(ab_loop_list__2);
		ab_loop_list__2 = M_CDR(ab_loop_list__2);
		binding = Nil;
		if (FIXNUM_EQ(length(clause),length(pattern))) {
		    pattern_element = Nil;
		    ab_loop_list__3 = pattern;
		    clause_element = Nil;
		    ab_loop_list__4 = clause;
		    star_qm = Nil;
		  next_loop_6:
		    if ( !TRUEP(ab_loop_list__3))
			goto end_loop_6;
		    pattern_element = M_CAR(ab_loop_list__3);
		    ab_loop_list__3 = M_CDR(ab_loop_list__3);
		    if ( !TRUEP(ab_loop_list__4))
			goto end_loop_6;
		    clause_element = M_CAR(ab_loop_list__4);
		    ab_loop_list__4 = M_CDR(ab_loop_list__4);
		    star_qm = EQ(pattern_element,Qstar) ? T : Nil;
		    if (star_qm)
			binding = clause_element;
		    if ( !(star_qm || EQUAL(pattern_element,clause_element))) {
			temp = TRUEP(Nil);
			goto end_3;
		    }
		    goto next_loop_6;
		  end_loop_6:
		    temp = TRUEP(T);
		    goto end_3;
		    temp = TRUEP(Qnil);
		  end_3:;
		}
		else
		    temp = TRUEP(Nil);
		binding_qm = temp ? binding : Nil;
		if (binding_qm) {
		    result = VALUES_2(clause,binding_qm);
		    goto end_4;
		}
		goto next_loop_5;
	      end_loop_5:
		result = VALUES_1(Qnil);
	      end_4:;
		MVS_2(result,clause_qm,binding_qm);
		if (clause_qm)
		    return VALUES_2(clause_qm,binding_qm);
	    }
	    goto next_loop_4;
	  end_loop_4:;
	}
	goto next_loop_3;
      end_loop_3:
	return VALUES_1(Qnil);
    }
}

/* DELETE-USER-INTERFACE-CLAUSE */
Object delete_user_interface_clause(item,mode,clause)
    Object item, mode, clause;
{
    Object major_clause, ab_loop_list_, gensymed_symbol, temp_1, temp_2;
    Object mode_clause, ab_loop_list__1;
    char temp;

    x_note_fn_call(180,88);
    if (EQ(mode,Qproprietary)) {
	major_clause = Nil;
	ab_loop_list_ = get_lookup_slot_value(item,Qobject_configuration);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	major_clause = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(FIRST(major_clause),Qproprietary)) {
	    gensymed_symbol = CDR(major_clause);
	  next_loop_1:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_1;
	    if (EQ(M_CAR(gensymed_symbol),clause)) {
		temp = TRUEP(gensymed_symbol);
		goto end_1;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_1;
	  end_loop_1:
	    temp = TRUEP(Qnil);
	  end_1:;
	    if (temp) {
		temp_1 = delete_slot_value_element_1(clause,CDR(major_clause));
		M_CDR(major_clause) = temp_1;
		if ( !TRUEP(CDR(major_clause))) {
		    temp_2 = major_clause;
		    temp_1 = delete_slot_value_element_1(temp_2,
			    get_lookup_slot_value(item,Qobject_configuration));
		    if (Noting_changes_to_kb_p)
			note_change_to_block_1(item,Qobject_configuration);
		    set_lookup_slot_value_1(item,Qobject_configuration,temp_1);
		    reclaim_slot_value_tree_1(major_clause);
		}
		return VALUES_1(clause);
	    }
	}
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else {
	major_clause = Nil;
	ab_loop_list_ = get_lookup_slot_value(item,Qobject_configuration);
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	major_clause = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (memq_function(FIRST(major_clause),list_constant_4)) {
	    mode_clause = Nil;
	    ab_loop_list__1 = CDR(major_clause);
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_3;
	    mode_clause = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    gensymed_symbol = CDDR(mode_clause);
	  next_loop_4:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_4;
	    if (EQ(M_CAR(gensymed_symbol),clause)) {
		temp = TRUEP(gensymed_symbol);
		goto end_2;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_4;
	  end_loop_4:
	    temp = TRUEP(Qnil);
	  end_2:;
	    if (temp) {
		temp_1 = delete_slot_value_element_1(clause,CDDR(mode_clause));
		M_CDDR(mode_clause) = temp_1;
		if ( !TRUEP(CDDR(mode_clause))) {
		    temp_1 = delete_slot_value_element_1(mode_clause,
			    CDR(major_clause));
		    M_CDR(major_clause) = temp_1;
		    reclaim_slot_value_tree_1(mode_clause);
		    if ( !TRUEP(CDR(major_clause))) {
			temp_2 = major_clause;
			temp_1 = delete_slot_value_element_1(temp_2,
				get_lookup_slot_value(item,
				Qobject_configuration));
			if (Noting_changes_to_kb_p)
			    note_change_to_block_1(item,Qobject_configuration);
			set_lookup_slot_value_1(item,Qobject_configuration,
				temp_1);
			reclaim_slot_value_tree_1(major_clause);
		    }
		}
		return VALUES_1(clause);
	    }
	    goto next_loop_3;
	  end_loop_3:;
	}
	goto next_loop_2;
      end_loop_2:
	return VALUES_1(Qnil);
    }
}

static Object string_constant_95;  /* "The type of clause must be the symbol WHEN or UNLESS." */

static Object string_constant_96;  /* "Proprietary restrictions require a clause type of WHEN." */

static Object list_constant_5;     /* # */

/* G2-SET-MOVEMENT-LIMITS */
Object g2_set_movement_limits(item_as_evaluation_value,
	    when_or_unless_as_evaluation_value,
	    user_mode_as_evaluation_value,left_as_evaluation_value,
	    right_as_evaluation_value,bottom_as_evaluation_value,
	    top_as_evaluation_value)
    Object item_as_evaluation_value, when_or_unless_as_evaluation_value;
    Object user_mode_as_evaluation_value, left_as_evaluation_value;
    Object right_as_evaluation_value, bottom_as_evaluation_value;
    Object top_as_evaluation_value;
{
    Object item, when_or_unless, user_mode, left, right, bottom, top;
    Object top_of_stack, message_1, temp, old_value, new_value, clause;
    Object rectangle, fourth_new_value;

    x_note_fn_call(180,89);
    item = IDENTITY(item_as_evaluation_value);
    when_or_unless = when_or_unless_as_evaluation_value;
    user_mode = user_mode_as_evaluation_value;
    left = left_as_evaluation_value;
    right = right_as_evaluation_value;
    bottom = bottom_as_evaluation_value;
    top = top_as_evaluation_value;
    if ( !(EQ(when_or_unless,Qwhen) || EQ(when_or_unless,Qunless))) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_95);
	raw_stack_error_named_error(top_of_stack,message_1);
	temp = Nil;
    }
    else if (EQ(when_or_unless,Qwhen) && EQ(user_mode,Qadministrator)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_92);
	raw_stack_error_named_error(top_of_stack,message_1);
	temp = Nil;
    }
    else if (EQ(when_or_unless,Qunless) && EQ(user_mode,Qproprietary)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_96);
	raw_stack_error_named_error(top_of_stack,message_1);
	temp = Nil;
    }
    else
	temp = T;
    if (temp) {
	old_value = get_lookup_slot_value(item,Qobject_configuration);
	new_value = copy_for_slot_value(old_value);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(item,Qobject_configuration);
	set_lookup_slot_value_1(item,Qobject_configuration,new_value);
	clause = ensure_user_interface_clause(item,when_or_unless,
		user_mode,list_constant_5);
	rectangle = FOURTH(clause);
	if (EQ(rectangle,Qstar)) {
	    fourth_new_value = slot_value_list_4(left,right,bottom,top);
	    M_FOURTH(clause) = fourth_new_value;
	}
	else if (CONSP(rectangle)) {
	    M_FIRST(rectangle) = left;
	    M_SECOND(rectangle) = right;
	    M_THIRD(rectangle) = bottom;
	    M_FOURTH(rectangle) = top;
	}
	new_value = get_lookup_slot_value(item,Qobject_configuration);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(item,Qobject_configuration);
	set_lookup_slot_value_1(item,Qobject_configuration,old_value);
	if (EQUAL(old_value,new_value))
	    reclaim_slot_value(new_value);
	else
	    change_slot_value(3,item,Qobject_configuration,new_value);
    }
    IDENTITY(item_as_evaluation_value);
    return VALUES_0();
}

static Object Qtruth_value;        /* truth-value */

/* G2-GET-MOVEMENT-LIMITS */
Object g2_get_movement_limits(item_as_evaluation_value,
	    when_or_unless_as_evaluation_value,user_mode_as_evaluation_value)
    Object item_as_evaluation_value, when_or_unless_as_evaluation_value;
    Object user_mode_as_evaluation_value;
{
    Object item, when_or_unless, user_mode, value_1, value_2, value_3, value_4;
    Object value_5, clause_qm, rectangle_qm, gensymed_symbol, left, right;
    Object bottom, top, temp, temp_1, temp_2, temp_3, temp_4;
    Object result;

    x_note_fn_call(180,90);
    item = IDENTITY(item_as_evaluation_value);
    when_or_unless = when_or_unless_as_evaluation_value;
    user_mode = user_mode_as_evaluation_value;
    value_1 = Nil;
    value_2 = Nil;
    value_3 = Nil;
    value_4 = Nil;
    value_5 = Nil;
    clause_qm = find_user_interface_clause(item,when_or_unless,user_mode,
	    list_constant_5);
    rectangle_qm = clause_qm ? FOURTH(clause_qm) : Qnil;
    if (rectangle_qm) {
	gensymed_symbol = rectangle_qm;
	left = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	right = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	bottom = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	top = CAR(gensymed_symbol);
	result = VALUES_5(left,right,bottom,top,Truth);
    }
    else
	result = VALUES_5(FIX((SI_Long)0L),FIX((SI_Long)0L),
		FIX((SI_Long)0L),FIX((SI_Long)0L),Falsity);
    MVS_5(result,value_1,value_2,value_3,value_4,value_5);
    IDENTITY(item_as_evaluation_value);
    temp = value_1;
    temp_1 = value_2;
    temp_2 = value_3;
    temp_3 = value_4;
    if (FIXNUM_EQ(value_5,Truth))
	temp_4 = Evaluation_true_value;
    else if (FIXNUM_EQ(value_5,Falsity))
	temp_4 = Evaluation_false_value;
    else
	temp_4 = eval_cons_1(value_5,Qtruth_value);
    return VALUES_5(temp,temp_1,temp_2,temp_3,temp_4);
}

/* G2-CLEAR-MOVEMENT-LIMITS */
Object g2_clear_movement_limits(item_as_evaluation_value,
	    when_or_unless_as_evaluation_value,user_mode_as_evaluation_value)
    Object item_as_evaluation_value, when_or_unless_as_evaluation_value;
    Object user_mode_as_evaluation_value;
{
    Object item, when_or_unless, user_mode, old_value, new_value, clause_qm;

    x_note_fn_call(180,91);
    item = IDENTITY(item_as_evaluation_value);
    when_or_unless = when_or_unless_as_evaluation_value;
    user_mode = user_mode_as_evaluation_value;
    old_value = get_lookup_slot_value(item,Qobject_configuration);
    new_value = copy_for_slot_value(old_value);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(item,Qobject_configuration);
    set_lookup_slot_value_1(item,Qobject_configuration,new_value);
    clause_qm = find_user_interface_clause(item,when_or_unless,user_mode,
	    list_constant_5);
    if (clause_qm) {
	delete_user_interface_clause(item,user_mode,clause_qm);
	reclaim_slot_value_tree_1(clause_qm);
    }
    new_value = get_lookup_slot_value(item,Qobject_configuration);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(item,Qobject_configuration);
    set_lookup_slot_value_1(item,Qobject_configuration,old_value);
    if (EQUAL(old_value,new_value))
	reclaim_slot_value(new_value);
    else
	change_slot_value(3,item,Qobject_configuration,new_value);
    IDENTITY(item_as_evaluation_value);
    return VALUES_0();
}

static Object list_constant_6;     /* # */

/* G2-SET-MOVEMENT-GRID */
Object g2_set_movement_grid(item_as_evaluation_value,
	    when_or_unless_as_evaluation_value,
	    user_mode_as_evaluation_value,dx_as_evaluation_value,
	    dy_as_evaluation_value)
    Object item_as_evaluation_value, when_or_unless_as_evaluation_value;
    Object user_mode_as_evaluation_value, dx_as_evaluation_value;
    Object dy_as_evaluation_value;
{
    Object item, when_or_unless, user_mode, dx, dy, top_of_stack, message_1;
    Object temp, old_value, new_value, clause, grid, temp_1;
    Declare_special(1);

    x_note_fn_call(180,92);
    item = IDENTITY(item_as_evaluation_value);
    when_or_unless = when_or_unless_as_evaluation_value;
    user_mode = user_mode_as_evaluation_value;
    dx = dx_as_evaluation_value;
    dy = dy_as_evaluation_value;
    if ( !(EQ(when_or_unless,Qwhen) || EQ(when_or_unless,Qunless))) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_95);
	raw_stack_error_named_error(top_of_stack,message_1);
	temp = Nil;
    }
    else if (EQ(when_or_unless,Qwhen) && EQ(user_mode,Qadministrator)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_92);
	raw_stack_error_named_error(top_of_stack,message_1);
	temp = Nil;
    }
    else if (EQ(when_or_unless,Qunless) && EQ(user_mode,Qproprietary)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_96);
	raw_stack_error_named_error(top_of_stack,message_1);
	temp = Nil;
    }
    else
	temp = T;
    if (temp) {
	old_value = get_lookup_slot_value(item,Qobject_configuration);
	new_value = copy_for_slot_value(old_value);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(item,Qobject_configuration);
	set_lookup_slot_value_1(item,Qobject_configuration,new_value);
	clause = ensure_user_interface_clause(item,when_or_unless,
		user_mode,list_constant_6);
	grid = FOURTH(clause);
	PUSH_SPECIAL_WITH_SYMBOL(Grid,Qgrid,grid,0);
	  if (EQ(Grid,Qstar)) {
	      temp_1 = slot_value_cons_1(dx,dy);
	      M_FOURTH(clause) = temp_1;
	  }
	  else if (CONSP(Grid)) {
	      temp_1 = Grid;
	      M_CAR(temp_1) = dx;
	      temp_1 = Grid;
	      M_CDR(temp_1) = dy;
	  }
	POP_SPECIAL();
	new_value = get_lookup_slot_value(item,Qobject_configuration);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(item,Qobject_configuration);
	set_lookup_slot_value_1(item,Qobject_configuration,old_value);
	if (EQUAL(old_value,new_value))
	    reclaim_slot_value(new_value);
	else
	    change_slot_value(3,item,Qobject_configuration,new_value);
    }
    IDENTITY(item_as_evaluation_value);
    return VALUES_0();
}

/* G2-GET-MOVEMENT-GRID */
Object g2_get_movement_grid(item_as_evaluation_value,
	    when_or_unless_as_evaluation_value,user_mode_as_evaluation_value)
    Object item_as_evaluation_value, when_or_unless_as_evaluation_value;
    Object user_mode_as_evaluation_value;
{
    Object item, when_or_unless, user_mode, value_1, value_2, value_3;
    Object clause_qm, grid_qm, temp, temp_1, temp_2;
    Object result;

    x_note_fn_call(180,93);
    item = IDENTITY(item_as_evaluation_value);
    when_or_unless = when_or_unless_as_evaluation_value;
    user_mode = user_mode_as_evaluation_value;
    value_1 = Nil;
    value_2 = Nil;
    value_3 = Nil;
    clause_qm = find_user_interface_clause(item,when_or_unless,user_mode,
	    list_constant_6);
    grid_qm = clause_qm ? FOURTH(clause_qm) : Qnil;
    if (grid_qm)
	result = VALUES_3(CAR(grid_qm),CDR(grid_qm),Truth);
    else
	result = VALUES_3(FIX((SI_Long)0L),FIX((SI_Long)0L),Falsity);
    MVS_3(result,value_1,value_2,value_3);
    IDENTITY(item_as_evaluation_value);
    temp = value_1;
    temp_1 = value_2;
    if (FIXNUM_EQ(value_3,Truth))
	temp_2 = Evaluation_true_value;
    else if (FIXNUM_EQ(value_3,Falsity))
	temp_2 = Evaluation_false_value;
    else
	temp_2 = eval_cons_1(value_3,Qtruth_value);
    return VALUES_3(temp,temp_1,temp_2);
}

/* G2-CLEAR-MOVEMENT-GRID */
Object g2_clear_movement_grid(item_as_evaluation_value,
	    when_or_unless_as_evaluation_value,user_mode_as_evaluation_value)
    Object item_as_evaluation_value, when_or_unless_as_evaluation_value;
    Object user_mode_as_evaluation_value;
{
    Object item, when_or_unless, user_mode, old_value, new_value, clause_qm;

    x_note_fn_call(180,94);
    item = IDENTITY(item_as_evaluation_value);
    when_or_unless = when_or_unless_as_evaluation_value;
    user_mode = user_mode_as_evaluation_value;
    old_value = get_lookup_slot_value(item,Qobject_configuration);
    new_value = copy_for_slot_value(old_value);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(item,Qobject_configuration);
    set_lookup_slot_value_1(item,Qobject_configuration,new_value);
    clause_qm = find_user_interface_clause(item,when_or_unless,user_mode,
	    list_constant_6);
    if (clause_qm) {
	delete_user_interface_clause(item,user_mode,clause_qm);
	reclaim_slot_value_tree_1(clause_qm);
    }
    new_value = get_lookup_slot_value(item,Qobject_configuration);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(item,Qobject_configuration);
    set_lookup_slot_value_1(item,Qobject_configuration,old_value);
    if (EQUAL(old_value,new_value))
	reclaim_slot_value(new_value);
    else
	change_slot_value(3,item,Qobject_configuration,new_value);
    IDENTITY(item_as_evaluation_value);
    return VALUES_0();
}

static Object Qframe_status_and_notes;  /* frame-status-and-notes */

static Object Qstack_change;       /* stack-change */

static Object Qitem_configuration;  /* item-configuration */

/* PUT-OBJECT-CONFIGURATION */
Object put_object_configuration(block,new_configuration,initializing_qm)
    Object block, new_configuration, initializing_qm;
{
    Object temp, old_configuration, result_1, current_flag_state_qm;
    Object slot_description, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, gensymed_symbol_1, stack_of_slot_value_changes;
    Object gensymed_symbol_2, gensymed_symbol_3, frame_and_slot_or_atom;
    Object ab_loop_list_, ab_loop_it_, stack_change_pop_store, cons_1;
    Object next_cons;
    SI_Long svref_new_value_1;
    char temp_2;
    Declare_special(1);

    x_note_fn_call(180,95);
    if ( !TRUEP(initializing_qm) && in_order_p(block)) {
	reclaim_slot_value(new_configuration);
	temp = get_lookup_slot_value(block,Qobject_configuration);
	return VALUES_2(temp,T);
    }
    else {
	old_configuration = get_lookup_slot_value(block,Qobject_configuration);
	new_configuration = massage_configuration_value(new_configuration);
	add_or_delete_mode_names_from_item_configuration(old_configuration,T);
	add_or_delete_mode_names_from_item_configuration(new_configuration,
		Nil);
	result_1 = Nil;
	current_flag_state_qm = Nil;
	slot_description = 
		get_slot_description_of_class_description_function(Qframe_status_and_notes,
		ISVREF(block,(SI_Long)1L),Nil);
	new_cons = ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_stack_change_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_stack_change_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_stack_change_cons_pool();
	if (Nil)
	    gensymed_symbol_1 = nconc2(stack_change_list_2(block,
		    slot_description),stack_change_cons_1(Nil,Nil));
	else {
	    new_cons = ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp_1 = Available_stack_change_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp_1,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp_1 = Available_stack_change_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = Nil;
		}
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_stack_change_cons_pool();
	    M_CAR(gensymed_symbol_1) = block;
	    M_CDR(gensymed_symbol_1) = slot_description;
	    inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
	}
	M_CAR(gensymed_symbol) = gensymed_symbol_1;
	temp_1 = Stack_of_slot_value_changes;
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qstack_change);
	stack_of_slot_value_changes = gensymed_symbol;
	PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
		0);
	  current_flag_state_qm = (SI_Long)0L != (IFIX(ISVREF(block,
		  (SI_Long)5L)) & (SI_Long)16777216L) ? T : Nil;
	  if ( !TRUEP(current_flag_state_qm)) {
	      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(block,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	      gensymed_symbol_1 = block;
	      gensymed_symbol_2 = Nil;
	      gensymed_symbol_3 = T;
	      inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		      gensymed_symbol_2,gensymed_symbol_3);
	      svref_new_value_1 = IFIX(ISVREF(block,(SI_Long)5L)) | 
		      (SI_Long)16777216L;
	      ISVREF(block,(SI_Long)5L) = FIX(svref_new_value_1);
	  }
	  if (Noting_changes_to_kb_p)
	      note_change_to_block_1(block,Qobject_configuration);
	  result_1 = set_lookup_slot_value_1(block,Qobject_configuration,
		  new_configuration);
	  if ( !TRUEP(current_flag_state_qm)) {
	      svref_new_value_1 = IFIX(ISVREF(block,(SI_Long)5L)) &  
		      ~(SI_Long)16777216L;
	      ISVREF(block,(SI_Long)5L) = FIX(svref_new_value_1);
	      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(block,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	      gensymed_symbol_1 = block;
	      gensymed_symbol_2 = T;
	      gensymed_symbol_3 = Nil;
	      inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		      gensymed_symbol_2,gensymed_symbol_3);
	  }
	  temp_2 = TRUEP(Suppress_updating_of_slot_value_representations_qm);
	  if (temp_2);
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
	      temp_2 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	      if (temp_2);
	      else {
		  temp = M_CDR(frame_and_slot_or_atom);
		  temp_2 = CONSP(temp) ? EQ(slot_description,
			  SECOND(frame_and_slot_or_atom)) && EQ(Nil,
			  THIRD(frame_and_slot_or_atom)) && EQ(Nil,
			  CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	      }
	      ab_loop_it_ = temp_2 ? (EQ(block,
		      M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
	      if (ab_loop_it_) {
		  temp_2 = TRUEP(ab_loop_it_);
		  goto end_1;
	      }
	      goto next_loop;
	    end_loop:
	      temp_2 = TRUEP(Qnil);
	    end_1:;
	  }
	  else
	      temp_2 = TRUEP(Nil);
	  if ( !temp_2)
	      update_all_representations_of_slot(block,slot_description,
		      Nil,Nil);
	  if (ISVREF(slot_description,(SI_Long)14L))
	      update_frame_name_references(block);
	  stack_change_pop_store = Nil;
	  cons_1 = Stack_of_slot_value_changes;
	  if (cons_1) {
	      stack_change_pop_store = M_CAR(cons_1);
	      next_cons = M_CDR(cons_1);
	      inline_note_reclaim_cons(cons_1,Qstack_change);
	      if (ISVREF(Available_stack_change_conses_tail_vector,
		      IFIX(Current_thread_index))) {
		  temp_1 = 
			  ISVREF(Available_stack_change_conses_tail_vector,
			  IFIX(Current_thread_index));
		  M_CDR(temp_1) = cons_1;
		  temp_1 = Available_stack_change_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp_1,svref_arg_2) = cons_1;
	      }
	      else {
		  temp_1 = Available_stack_change_conses_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp_1,svref_arg_2) = cons_1;
		  temp_1 = Available_stack_change_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp_1,svref_arg_2) = cons_1;
	      }
	      M_CDR(cons_1) = Nil;
	  }
	  else
	      next_cons = Nil;
	  Stack_of_slot_value_changes = next_cons;
	  reclaim_stack_change_tree_1(stack_change_pop_store);
	  if (Stack_of_slot_value_changes) {
	      temp = M_CAR(Stack_of_slot_value_changes);
	      temp_2 = ATOM(temp);
	  }
	  else
	      temp_2 = TRUEP(Nil);
	  if (temp_2 ?  
		  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) : 
		  TRUEP(Nil))
	      do_deferred_updates_to_representations_in_tables();
	POP_SPECIAL();
	if ( !EQUAL(old_configuration,new_configuration))
	    propagate_change_in_object_configuration(Qitem_configuration,
		    block,old_configuration,new_configuration);
	return VALUES_2(new_configuration,Nil);
    }
}

static Object Qinstance_configuration;  /* instance-configuration */

/* PUT-INSTANCE-CONFIGURATION */
Object put_instance_configuration(definition,new_configuration,initializing_qm)
    Object definition, new_configuration, initializing_qm;
{
    Object temp, old_configuration, result_1, current_flag_state_qm;
    Object slot_description, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, gensymed_symbol_1, stack_of_slot_value_changes;
    Object gensymed_symbol_2, gensymed_symbol_3, frame_and_slot_or_atom;
    Object ab_loop_list_, ab_loop_it_, stack_change_pop_store, cons_1;
    Object next_cons;
    SI_Long svref_new_value_1;
    char temp_2;
    Declare_special(1);

    x_note_fn_call(180,96);
    if ( !TRUEP(initializing_qm) && in_order_p(definition)) {
	reclaim_slot_value(new_configuration);
	temp = ISVREF(definition,(SI_Long)23L);
	return VALUES_2(temp,T);
    }
    else {
	old_configuration = ISVREF(definition,(SI_Long)23L);
	new_configuration = massage_configuration_value(new_configuration);
	add_or_delete_mode_names_from_item_configuration(old_configuration,T);
	add_or_delete_mode_names_from_item_configuration(new_configuration,
		Nil);
	result_1 = Nil;
	current_flag_state_qm = Nil;
	slot_description = 
		get_slot_description_of_class_description_function(Qframe_status_and_notes,
		ISVREF(definition,(SI_Long)1L),Nil);
	new_cons = ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_stack_change_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_stack_change_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_stack_change_cons_pool();
	if (Nil)
	    gensymed_symbol_1 = nconc2(stack_change_list_2(definition,
		    slot_description),stack_change_cons_1(Nil,Nil));
	else {
	    new_cons = ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp_1 = Available_stack_change_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp_1,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp_1 = Available_stack_change_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = Nil;
		}
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_stack_change_cons_pool();
	    M_CAR(gensymed_symbol_1) = definition;
	    M_CDR(gensymed_symbol_1) = slot_description;
	    inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
	}
	M_CAR(gensymed_symbol) = gensymed_symbol_1;
	temp_1 = Stack_of_slot_value_changes;
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qstack_change);
	stack_of_slot_value_changes = gensymed_symbol;
	PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
		0);
	  current_flag_state_qm = (SI_Long)0L != (IFIX(ISVREF(definition,
		  (SI_Long)5L)) & (SI_Long)16777216L) ? T : Nil;
	  if ( !TRUEP(current_flag_state_qm)) {
	      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(definition,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	      gensymed_symbol_1 = definition;
	      gensymed_symbol_2 = Nil;
	      gensymed_symbol_3 = T;
	      inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		      gensymed_symbol_2,gensymed_symbol_3);
	      svref_new_value_1 = IFIX(ISVREF(definition,(SI_Long)5L)) | 
		      (SI_Long)16777216L;
	      ISVREF(definition,(SI_Long)5L) = FIX(svref_new_value_1);
	  }
	  if (Noting_changes_to_kb_p)
	      note_change_to_block_1(definition,Qinstance_configuration);
	  result_1 = SVREF(definition,FIX((SI_Long)23L)) = new_configuration;
	  if ( !TRUEP(current_flag_state_qm)) {
	      svref_new_value_1 = IFIX(ISVREF(definition,(SI_Long)5L)) &  
		      ~(SI_Long)16777216L;
	      ISVREF(definition,(SI_Long)5L) = FIX(svref_new_value_1);
	      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(definition,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	      gensymed_symbol_1 = definition;
	      gensymed_symbol_2 = T;
	      gensymed_symbol_3 = Nil;
	      inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		      gensymed_symbol_2,gensymed_symbol_3);
	  }
	  temp_2 = TRUEP(Suppress_updating_of_slot_value_representations_qm);
	  if (temp_2);
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
	      temp_2 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	      if (temp_2);
	      else {
		  temp = M_CDR(frame_and_slot_or_atom);
		  temp_2 = CONSP(temp) ? EQ(slot_description,
			  SECOND(frame_and_slot_or_atom)) && EQ(Nil,
			  THIRD(frame_and_slot_or_atom)) && EQ(Nil,
			  CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	      }
	      ab_loop_it_ = temp_2 ? (EQ(definition,
		      M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
	      if (ab_loop_it_) {
		  temp_2 = TRUEP(ab_loop_it_);
		  goto end_1;
	      }
	      goto next_loop;
	    end_loop:
	      temp_2 = TRUEP(Qnil);
	    end_1:;
	  }
	  else
	      temp_2 = TRUEP(Nil);
	  if ( !temp_2)
	      update_all_representations_of_slot(definition,
		      slot_description,Nil,Nil);
	  if (ISVREF(slot_description,(SI_Long)14L))
	      update_frame_name_references(definition);
	  stack_change_pop_store = Nil;
	  cons_1 = Stack_of_slot_value_changes;
	  if (cons_1) {
	      stack_change_pop_store = M_CAR(cons_1);
	      next_cons = M_CDR(cons_1);
	      inline_note_reclaim_cons(cons_1,Qstack_change);
	      if (ISVREF(Available_stack_change_conses_tail_vector,
		      IFIX(Current_thread_index))) {
		  temp_1 = 
			  ISVREF(Available_stack_change_conses_tail_vector,
			  IFIX(Current_thread_index));
		  M_CDR(temp_1) = cons_1;
		  temp_1 = Available_stack_change_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp_1,svref_arg_2) = cons_1;
	      }
	      else {
		  temp_1 = Available_stack_change_conses_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp_1,svref_arg_2) = cons_1;
		  temp_1 = Available_stack_change_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp_1,svref_arg_2) = cons_1;
	      }
	      M_CDR(cons_1) = Nil;
	  }
	  else
	      next_cons = Nil;
	  Stack_of_slot_value_changes = next_cons;
	  reclaim_stack_change_tree_1(stack_change_pop_store);
	  if (Stack_of_slot_value_changes) {
	      temp = M_CAR(Stack_of_slot_value_changes);
	      temp_2 = ATOM(temp);
	  }
	  else
	      temp_2 = TRUEP(Nil);
	  if (temp_2 ?  
		  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) : 
		  TRUEP(Nil))
	      do_deferred_updates_to_representations_in_tables();
	POP_SPECIAL();
	if ( !EQUAL(old_configuration,new_configuration))
	    propagate_change_in_object_configuration(Qinstance_configuration,
		    definition,old_configuration,new_configuration);
	return VALUES_1(Nil);
    }
}

/* RECLAIM-INSTANCE-CONFIGURATION-VALUE */
Object reclaim_instance_configuration_value(value,frame)
    Object value, frame;
{
    x_note_fn_call(180,97);
    add_or_delete_mode_names_from_item_configuration(value,T);
    reclaim_slot_value(value);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,Qinstance_configuration);
    SVREF(frame,FIX((SI_Long)23L)) = Nil;
    return VALUES_1(Nil);
}

/* MASSAGE-CONFIGURATION-VALUE */
Object massage_configuration_value(configuration)
    Object configuration;
{
    Object clause, ab_loop_list_, gensymed_symbol, property_1, value, class_1;

    x_note_fn_call(180,98);
    clause = Nil;
    ab_loop_list_ = configuration;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    clause = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (CONSP(clause) && EQ(M_CAR(clause),Qdeclare)) {
	gensymed_symbol = CDR(clause);
	property_1 = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	value = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	class_1 = CAR(gensymed_symbol);
	M_FIRST(clause) = Qdeclaration;
	M_SECOND(clause) = class_1;
	M_THIRD(clause) = property_1;
	M_FOURTH(clause) = value;
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(configuration);
}

static Object Qstable_hierarchy;   /* stable-hierarchy */

static Object Qinlineable;         /* inlineable */

static Object Qstable_for_dependent_compilations;  /* stable-for-dependent-compilations */

static Object Qindependent_for_all_compilations;  /* independent-for-all-compilations */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qab_gensym;          /* gensym */

/* PROPAGATE-CHANGE-IN-OBJECT-CONFIGURATION */
Object propagate_change_in_object_configuration(type_of_configuration,
	    block,old_configuration,new_configuration)
    Object type_of_configuration, block, old_configuration, new_configuration;
{
    Object temp, temp_1, all_items_processed_qm, x2, gensymed_symbol;
    Object gensymed_symbol_1, sub_class_bit_vector, scope_conses, ab_loopvar_;
    Object ab_loopvar__1, item, gensymed_symbol_5, gensymed_symbol_6;
    Object defer_consistency_analysis_qm, compiled_items_deferred_for_analysis;
    Object deferred_list_cons_qm, gensym_cons, temp_3, temp_4;
    Object svref_new_value_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    SI_Long svref_new_value;
    char stable_hierarchy_change_qm, inline_change_qm;
    char stable_for_dependent_compilations_change_qm;
    char independent_for_all_compilations_change_qm, temp_2;
    Declare_special(3);

    x_note_fn_call(180,99);
    temp = get_property_clause(old_configuration,Qstable_hierarchy);
    temp_1 = get_property_clause(new_configuration,Qstable_hierarchy);
    stable_hierarchy_change_qm =  !EQUAL(temp,temp_1);
    temp = get_property_clause(old_configuration,Qinlineable);
    temp_1 = get_property_clause(new_configuration,Qinlineable);
    inline_change_qm =  !EQUAL(temp,temp_1);
    temp = get_property_clause(old_configuration,
	    Qstable_for_dependent_compilations);
    temp_1 = get_property_clause(new_configuration,
	    Qstable_for_dependent_compilations);
    stable_for_dependent_compilations_change_qm =  !EQUAL(temp,temp_1);
    temp = get_property_clause(old_configuration,
	    Qindependent_for_all_compilations);
    temp_1 = get_property_clause(new_configuration,
	    Qindependent_for_all_compilations);
    independent_for_all_compilations_change_qm =  !EQUAL(temp,temp_1);
    all_items_processed_qm = Nil;
    if (SIMPLE_VECTOR_P(block) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(block)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(block,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(block,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	gensymed_symbol_1 = 
		lookup_global_or_kb_specific_property_value(Qkb_configuration,
		Class_description_gkbprop);
	if (gensymed_symbol_1) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_1,
		    (SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol_2 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_3 = (SI_Long)1L;
		gensymed_symbol_4 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
		gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
		temp_2 = (SI_Long)0L < gensymed_symbol_2;
	    }
	    else
		temp_2 = TRUEP(Nil);
	}
	else
	    temp_2 = TRUEP(Nil);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2 ? TRUEP(system_table_installed_p(block)) : TRUEP(Nil))
	decache_dynamic_menus(1,Qkb_configuration);
    if (stable_for_dependent_compilations_change_qm || 
	    independent_for_all_compilations_change_qm) {
	if (EQ(type_of_configuration,Qitem_configuration) && EQ(block,
		Kb_restrictions)) {
	    scope_conses = Scope_conses;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    item = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
	      ab_loopvar_ = collect_subclasses(Qitem);
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
		  temp_2 =  !TRUEP(ab_loopvar__1);
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      if (temp_2)
		  goto end_loop_1;
	      item = ab_loopvar__1;
	      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(item,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	      gensymed_symbol_1 = item;
	      gensymed_symbol_5 = Nil;
	      gensymed_symbol_6 = Nil;
	      inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		      gensymed_symbol_5,gensymed_symbol_6);
	      goto next_loop;
	    end_loop_1:;
	    POP_SPECIAL();
	    all_items_processed_qm = T;
	}
	else if (EQ(type_of_configuration,Qinstance_configuration) && 
		get_lookup_slot_value_given_default(block,
		Qname_or_names_for_frame,Nil)) {
	    defer_consistency_analysis_qm = T;
	    compiled_items_deferred_for_analysis = Nil;
	    gensymed_symbol = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Compiled_items_deferred_for_analysis,Qcompiled_items_deferred_for_analysis,compiled_items_deferred_for_analysis,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Defer_consistency_analysis_qm,Qdefer_consistency_analysis_qm,defer_consistency_analysis_qm,
		      1);
		scope_conses = Scope_conses;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		item = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			0);
		  ab_loopvar_ = 
			  collect_subclasses(get_lookup_slot_value_given_default(block,
			  Qname_or_names_for_frame,Nil));
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
		      temp_2 =  !TRUEP(ab_loopvar__1);
		  }
		  else
		      temp_2 = TRUEP(Nil);
		  if (temp_2)
		      goto end_loop_3;
		  item = ab_loopvar__1;
		  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
		  handle_dependent_or_stable_status_change_for_item(item);
		  goto next_loop_2;
		end_loop_3:
		  gensymed_symbol = Qnil;
		POP_SPECIAL();
		Defer_consistency_analysis_qm = Nil;
		if (Compiled_items_deferred_for_analysis) {
		    deferred_list_cons_qm = 
			    Compiled_items_deferred_for_analysis;
		    item = Nil;
		  next_loop_4:
		    item = M_CAR(deferred_list_cons_qm);
		    if ( !(SIMPLE_VECTOR_P(item) && EQ(ISVREF(item,
			    (SI_Long)1L),Qavailable_frame_vector))) {
			gensymed_symbol = ISVREF(item,(SI_Long)3L);
			if ( !(FIXNUMP(gensymed_symbol) ? 
				IFIX(gensymed_symbol) == (SI_Long)-1L : 
				TRUEP(Nil))) {
			    gensymed_symbol = 
				    ISVREF(ISVREF(ISVREF(ISVREF(item,
				    (SI_Long)1L),(SI_Long)11L),
				    (SI_Long)3L),(SI_Long)1L);
			    gensymed_symbol_1 = item;
			    gensymed_symbol_5 = Nil;
			    gensymed_symbol_6 = Nil;
			    inline_funcall_3(gensymed_symbol,
				    gensymed_symbol_1,gensymed_symbol_5,
				    gensymed_symbol_6);
			}
			svref_new_value = IFIX(ISVREF(item,(SI_Long)5L)) & 
				 ~(SI_Long)1048576L;
			ISVREF(item,(SI_Long)5L) = FIX(svref_new_value);
		    }
		    if ( !TRUEP(M_CDR(deferred_list_cons_qm)))
			goto end_loop_4;
		    deferred_list_cons_qm = M_CDR(deferred_list_cons_qm);
		    goto next_loop_4;
		  end_loop_4:
		    if (Compiled_items_deferred_for_analysis &&  
			    !((SI_Long)0L == inline_debugging_consing())) {
			gensym_cons = Compiled_items_deferred_for_analysis;
		      next_loop_5:
			inline_note_reclaim_cons(gensym_cons,Qab_gensym);
			if (EQ(gensym_cons,deferred_list_cons_qm))
			    goto end_1;
			else if ( !TRUEP(gensym_cons))
			    goto end_1;
			else
			    gensym_cons = CDR(gensym_cons);
			goto next_loop_5;
		      end_loop_5:
		      end_1:;
		    }
		    if (ISVREF(Available_gensym_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_3 = 
				ISVREF(Available_gensym_conses_tail_vector,
				IFIX(Current_thread_index));
			temp_4 = Compiled_items_deferred_for_analysis;
			M_CDR(temp_3) = temp_4;
			temp_3 = Available_gensym_conses_tail_vector;
			temp_4 = Current_thread_index;
			SVREF(temp_3,temp_4) = deferred_list_cons_qm;
		    }
		    else {
			temp_3 = Available_gensym_conses_vector;
			temp_4 = Current_thread_index;
			svref_new_value_1 = 
				Compiled_items_deferred_for_analysis;
			SVREF(temp_3,temp_4) = svref_new_value_1;
			temp_3 = Available_gensym_conses_tail_vector;
			temp_4 = Current_thread_index;
			SVREF(temp_3,temp_4) = deferred_list_cons_qm;
		    }
		    M_CDR(deferred_list_cons_qm) = Nil;
		}
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	else {
	    defer_consistency_analysis_qm = T;
	    compiled_items_deferred_for_analysis = Nil;
	    gensymed_symbol = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Compiled_items_deferred_for_analysis,Qcompiled_items_deferred_for_analysis,compiled_items_deferred_for_analysis,
		    1);
	      PUSH_SPECIAL_WITH_SYMBOL(Defer_consistency_analysis_qm,Qdefer_consistency_analysis_qm,defer_consistency_analysis_qm,
		      0);
		gensymed_symbol = 
			note_dependent_or_stable_status_change(block);
		Defer_consistency_analysis_qm = Nil;
		if (Compiled_items_deferred_for_analysis) {
		    deferred_list_cons_qm = 
			    Compiled_items_deferred_for_analysis;
		    item = Nil;
		  next_loop_6:
		    item = M_CAR(deferred_list_cons_qm);
		    if ( !(SIMPLE_VECTOR_P(item) && EQ(ISVREF(item,
			    (SI_Long)1L),Qavailable_frame_vector))) {
			gensymed_symbol = ISVREF(item,(SI_Long)3L);
			if ( !(FIXNUMP(gensymed_symbol) ? 
				IFIX(gensymed_symbol) == (SI_Long)-1L : 
				TRUEP(Nil))) {
			    gensymed_symbol = 
				    ISVREF(ISVREF(ISVREF(ISVREF(item,
				    (SI_Long)1L),(SI_Long)11L),
				    (SI_Long)3L),(SI_Long)1L);
			    gensymed_symbol_1 = item;
			    gensymed_symbol_5 = Nil;
			    gensymed_symbol_6 = Nil;
			    inline_funcall_3(gensymed_symbol,
				    gensymed_symbol_1,gensymed_symbol_5,
				    gensymed_symbol_6);
			}
			svref_new_value = IFIX(ISVREF(item,(SI_Long)5L)) & 
				 ~(SI_Long)1048576L;
			ISVREF(item,(SI_Long)5L) = FIX(svref_new_value);
		    }
		    if ( !TRUEP(M_CDR(deferred_list_cons_qm)))
			goto end_loop_6;
		    deferred_list_cons_qm = M_CDR(deferred_list_cons_qm);
		    goto next_loop_6;
		  end_loop_6:
		    if (Compiled_items_deferred_for_analysis &&  
			    !((SI_Long)0L == inline_debugging_consing())) {
			gensym_cons = Compiled_items_deferred_for_analysis;
		      next_loop_7:
			inline_note_reclaim_cons(gensym_cons,Qab_gensym);
			if (EQ(gensym_cons,deferred_list_cons_qm))
			    goto end_2;
			else if ( !TRUEP(gensym_cons))
			    goto end_2;
			else
			    gensym_cons = CDR(gensym_cons);
			goto next_loop_7;
		      end_loop_7:
		      end_2:;
		    }
		    if (ISVREF(Available_gensym_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_3 = 
				ISVREF(Available_gensym_conses_tail_vector,
				IFIX(Current_thread_index));
			temp_4 = Compiled_items_deferred_for_analysis;
			M_CDR(temp_3) = temp_4;
			temp_3 = Available_gensym_conses_tail_vector;
			temp_4 = Current_thread_index;
			SVREF(temp_3,temp_4) = deferred_list_cons_qm;
		    }
		    else {
			temp_3 = Available_gensym_conses_vector;
			temp_4 = Current_thread_index;
			svref_new_value_1 = 
				Compiled_items_deferred_for_analysis;
			SVREF(temp_3,temp_4) = svref_new_value_1;
			temp_3 = Available_gensym_conses_tail_vector;
			temp_4 = Current_thread_index;
			SVREF(temp_3,temp_4) = deferred_list_cons_qm;
		    }
		    M_CDR(deferred_list_cons_qm) = Nil;
		}
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
    }
    if (stable_hierarchy_change_qm &&  !TRUEP(all_items_processed_qm))
	return handle_stable_hierarchy_or_inline_status_change_for_item(1,
		block);
    else if (inline_change_qm &&  !TRUEP(all_items_processed_qm))
	return handle_stable_hierarchy_or_inline_status_change_for_item(2,
		block,T);
    else
	return VALUES_1(Qnil);
}

/* NOTE-DEPENDENT-OR-STABLE-STATUS-CHANGE */
Object note_dependent_or_stable_status_change(block)
    Object block;
{
    Object temp;

    x_note_fn_call(180,100);
    temp = 
	    handle_dependent_or_stable_status_change_for_item_for_filters(block,
	    Nil);
    return VALUES_1(temp);
}

static Object Qhandle_dependent_or_stable_status_change_for_item_for_filters;  /* handle-dependent-or-stable-status-change-for-item-for-filters */

/* HANDLE-DEPENDENT-OR-STABLE-STATUS-CHANGE-FOR-ITEM-FOR-FILTERS */
Object handle_dependent_or_stable_status_change_for_item_for_filters(block,
	    parent_1)
    Object block, parent_1;
{
    Object temp;

    x_note_fn_call(180,101);
    if (ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)16L))
	handle_dependent_or_stable_status_change_for_item(block);
    temp = funcall_function_to_inferior_blocks(block,
	    SYMBOL_FUNCTION(Qhandle_dependent_or_stable_status_change_for_item_for_filters));
    return VALUES_1(temp);
}

static Object Qframe_style;        /* frame-style */

/* PUT-FRAME-STYLE */
Object put_frame_style(workspace,frame_style,initializing_qm)
    Object workspace, frame_style, initializing_qm;
{
    Object old_frame_style, result_1, current_flag_state_qm, slot_description;
    Object new_cons, temp, svref_arg_2, svref_new_value, gensymed_symbol;
    Object gensymed_symbol_1, stack_of_slot_value_changes, gensymed_symbol_2;
    Object gensymed_symbol_3, frame_and_slot_or_atom, ab_loop_list_;
    Object ab_loop_it_, temp_2, stack_change_pop_store, cons_1, next_cons;
    SI_Long svref_new_value_1;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(180,102);
    old_frame_style = get_lookup_slot_value(workspace,Qframe_style);
    result_1 = Nil;
    current_flag_state_qm = Nil;
    slot_description = 
	    get_slot_description_of_class_description_function(Qframe_status_and_notes,
	    ISVREF(workspace,(SI_Long)1L),Nil);
    new_cons = ISVREF(Available_stack_change_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp = Available_stack_change_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp = Available_stack_change_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_stack_change_cons_pool();
    if (Nil)
	gensymed_symbol_1 = nconc2(stack_change_list_2(workspace,
		slot_description),stack_change_cons_1(Nil,Nil));
    else {
	new_cons = ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_stack_change_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_stack_change_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol_1 = new_cons;
	}
	else
	    gensymed_symbol_1 = Nil;
	if ( !TRUEP(gensymed_symbol_1))
	    gensymed_symbol_1 = replenish_stack_change_cons_pool();
	M_CAR(gensymed_symbol_1) = workspace;
	M_CDR(gensymed_symbol_1) = slot_description;
	inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
    }
    M_CAR(gensymed_symbol) = gensymed_symbol_1;
    temp = Stack_of_slot_value_changes;
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qstack_change);
    stack_of_slot_value_changes = gensymed_symbol;
    PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
	    0);
      current_flag_state_qm = (SI_Long)0L != (IFIX(ISVREF(workspace,
	      (SI_Long)5L)) & (SI_Long)16777216L) ? T : Nil;
      if ( !TRUEP(current_flag_state_qm)) {
	  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(workspace,
		  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	  gensymed_symbol_1 = workspace;
	  gensymed_symbol_2 = Nil;
	  gensymed_symbol_3 = T;
	  inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		  gensymed_symbol_2,gensymed_symbol_3);
	  svref_new_value_1 = IFIX(ISVREF(workspace,(SI_Long)5L)) | 
		  (SI_Long)16777216L;
	  ISVREF(workspace,(SI_Long)5L) = FIX(svref_new_value_1);
      }
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(workspace,Qframe_style);
      result_1 = set_lookup_slot_value_1(workspace,Qframe_style,frame_style);
      if ( !TRUEP(current_flag_state_qm)) {
	  svref_new_value_1 = IFIX(ISVREF(workspace,(SI_Long)5L)) &  
		  ~(SI_Long)16777216L;
	  ISVREF(workspace,(SI_Long)5L) = FIX(svref_new_value_1);
	  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(workspace,
		  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	  gensymed_symbol_1 = workspace;
	  gensymed_symbol_2 = T;
	  gensymed_symbol_3 = Nil;
	  inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		  gensymed_symbol_2,gensymed_symbol_3);
      }
      temp_1 = TRUEP(Suppress_updating_of_slot_value_representations_qm);
      if (temp_1);
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
	  temp_1 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	  if (temp_1);
	  else {
	      temp_2 = M_CDR(frame_and_slot_or_atom);
	      temp_1 = CONSP(temp_2) ? EQ(slot_description,
		      SECOND(frame_and_slot_or_atom)) && EQ(Nil,
		      THIRD(frame_and_slot_or_atom)) && EQ(Nil,
		      CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	  }
	  ab_loop_it_ = temp_1 ? (EQ(workspace,
		  M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
	  if (ab_loop_it_) {
	      temp_1 = TRUEP(ab_loop_it_);
	      goto end_1;
	  }
	  goto next_loop;
	end_loop:
	  temp_1 = TRUEP(Qnil);
	end_1:;
      }
      else
	  temp_1 = TRUEP(Nil);
      if ( !temp_1)
	  update_all_representations_of_slot(workspace,slot_description,
		  Nil,Nil);
      if (ISVREF(slot_description,(SI_Long)14L))
	  update_frame_name_references(workspace);
      stack_change_pop_store = Nil;
      cons_1 = Stack_of_slot_value_changes;
      if (cons_1) {
	  stack_change_pop_store = M_CAR(cons_1);
	  next_cons = M_CDR(cons_1);
	  inline_note_reclaim_cons(cons_1,Qstack_change);
	  if (ISVREF(Available_stack_change_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	      temp = ISVREF(Available_stack_change_conses_tail_vector,
		      IFIX(Current_thread_index));
	      M_CDR(temp) = cons_1;
	      temp = Available_stack_change_conses_tail_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = cons_1;
	  }
	  else {
	      temp = Available_stack_change_conses_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = cons_1;
	      temp = Available_stack_change_conses_tail_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = cons_1;
	  }
	  M_CDR(cons_1) = Nil;
      }
      else
	  next_cons = Nil;
      Stack_of_slot_value_changes = next_cons;
      reclaim_stack_change_tree_1(stack_change_pop_store);
      if (Stack_of_slot_value_changes) {
	  temp_2 = M_CAR(Stack_of_slot_value_changes);
	  temp_1 = ATOM(temp_2);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1 ?  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) :
	       TRUEP(Nil))
	  do_deferred_updates_to_representations_in_tables();
    POP_SPECIAL();
    if ( !(initializing_qm || EQUAL(frame_style,old_frame_style)))
	reconsider_formatting(workspace);
    return VALUES_2(frame_style,Nil);
}

/* COMPILE-OBJECT-CONFIGURATION-FOR-SLOT */
Object compile_object_configuration_for_slot varargs_1(int, n)
{
    Object parse_result, frame_for_this_parse, gensymed_symbol;
    Declare_varargs_nonrelocating;

    x_note_fn_call(180,103);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame_for_this_parse = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (CONSP(parse_result) && EQ(FIRST(parse_result),Qsc))
	parse_result = CDR(parse_result);
    return compile_object_configuration(parse_result,frame_for_this_parse);
}

static Object string_constant_97;  /* "The network access type `connect' is only valid in the KB-CONFIGURATION system table." */

/* COMPILE-OBJECT-CONFIGURATION */
Object compile_object_configuration(form,frame_for_this_parse)
    Object form, frame_for_this_parse;
{
    Object trouble_qm, result_1, clause, ab_loop_list_, answer, string_1;
    Object phrase, ab_loop_list__1, access_types, gensymed_symbol;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Object result;

    x_note_fn_call(180,104);
    trouble_qm = Nil;
    result_1 = Nil;
    if ( !( !TRUEP(form) || EQ(form,Qnone))) {
	clause = Nil;
	ab_loop_list_ = form;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	clause = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (trouble_qm)
	    goto end_loop;
	if (memq_function(FIRST(clause),list_constant_4)) {
	    result = compile_user_restrictions(clause,T);
	    MVS_2(result,answer,string_1);
	    if (EQ(answer,Bad_phrase))
		trouble_qm = string_1;
	    else
		M_CDR(clause) = answer;
	}
	else if (EQ(FIRST(clause),Qnetwork_access)) {
	    phrase = Nil;
	    ab_loop_list__1 = CDR(clause);
	    access_types = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_1;
	    phrase = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    access_types = FOURTH(phrase);
	    if (memq_function(Qconnect,access_types)) {
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(Qkb_restrictions,
			Class_description_gkbprop);
		if (gensymed_symbol) {
		    sub_class_bit_vector = 
			    ISVREF(ISVREF(frame_for_this_parse,
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
	    if (temp)
		trouble_qm = copy_text_string(string_constant_97);
	    goto next_loop_1;
	  end_loop_1:;
	}
	if ( !( !TRUEP(clause) || CONSP(clause) &&  !TRUEP(CDR(clause))))
	    result_1 = phrase_cons(clause,result_1);
	goto next_loop;
      end_loop:;
	if (trouble_qm)
	    return VALUES_2(Bad_phrase,trouble_qm);
	else
	    return VALUES_1(result_1);
    }
    else
	return VALUES_1(Nil);
}

Object Things_to_rename_in_restrictions = UNBOUND;

/* RENAME-SLOTS-IN-RESTRICTIONS */
Object rename_slots_in_restrictions(restrictions)
    Object restrictions;
{
    Object element, temp, new_element_qm;

    x_note_fn_call(180,105);
    if (CONSP(restrictions)) {
	element = CAR(restrictions);
	temp = assq_function(element,Things_to_rename_in_restrictions);
	new_element_qm = SECOND(temp);
	if (new_element_qm)
	    M_CAR(restrictions) = new_element_qm;
	rename_slots_in_restrictions(CAR(restrictions));
	rename_slots_in_restrictions(CDR(restrictions));
    }
    return VALUES_1(restrictions);
}

/* CONVERT-USER-RESTRICTIONS-INTO-OBJECT-CONFIGURATION */
Object convert_user_restrictions_into_object_configuration(object_configuration,
	    user_restrictions)
    Object object_configuration, user_restrictions;
{
    Object user_interface_clauses, proprietary_clauses, mode_restriction;
    Object ab_loop_list_, when_or_unless, modes, body, proprietary_p;
    Object new_modes, mode, ab_loop_list__1, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp, ui, prop, new_object_configuration, clause;

    x_note_fn_call(180,106);
    user_interface_clauses = Nil;
    proprietary_clauses = Nil;
    mode_restriction = Nil;
    ab_loop_list_ = user_restrictions;
    when_or_unless = Nil;
    modes = Nil;
    body = Nil;
    proprietary_p = Nil;
    new_modes = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    mode_restriction = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    when_or_unless = FIRST(mode_restriction);
    modes = SECOND(mode_restriction);
    body = CDDR(mode_restriction);
    proprietary_p = memq_function(Qproprietary,modes);
    mode = Nil;
    ab_loop_list__1 = modes;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    mode = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if ( !EQ(mode,Qproprietary)) {
	ab_loopvar__2 = slot_value_cons_1(mode,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop_1;
  end_loop_1:
    new_modes = ab_loopvar_;
    goto end_1;
    new_modes = Qnil;
  end_1:;
    if (proprietary_p)
	proprietary_clauses = nconc2(proprietary_clauses,
		copy_tree_using_slot_value_conses_1(body));
    if (new_modes) {
	temp = user_interface_clauses;
	user_interface_clauses = nconc2(temp,
		slot_value_cons_1(nconc2(slot_value_list_2(when_or_unless,
		new_modes),copy_tree_using_slot_value_conses_1(body)),Nil));
    }
    goto next_loop;
  end_loop:;
    ui = user_interface_clauses ? slot_value_cons_1(Quser_interface,
	    user_interface_clauses) : Qnil;
    prop = proprietary_clauses ? slot_value_cons_1(Qproprietary,
	    proprietary_clauses) : Qnil;
    new_object_configuration = Nil;
    clause = Nil;
    ab_loop_list_ = object_configuration;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    clause = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (memq_function(FIRST(clause),list_constant_4)) {
	if (ui) {
	    new_object_configuration = slot_value_cons_1(ui,
		    new_object_configuration);
	    ui = Nil;
	}
    }
    else if (EQ(FIRST(clause),Qproprietary)) {
	if (prop) {
	    new_object_configuration = slot_value_cons_1(prop,
		    new_object_configuration);
	    prop = Nil;
	}
    }
    else
	new_object_configuration = 
		slot_value_cons_1(copy_tree_using_slot_value_conses_1(clause),
		new_object_configuration);
    goto next_loop_2;
  end_loop_2:;
    new_object_configuration = nreverse(new_object_configuration);
    if (ui)
	new_object_configuration = nconc2(new_object_configuration,
		slot_value_cons_1(ui,Nil));
    if (prop)
	new_object_configuration = nconc2(new_object_configuration,
		slot_value_cons_1(prop,Nil));
    return rename_slots_in_restrictions(new_object_configuration);
}

/* COPY-USER-RESTRICTIONS-INTO-OBJECT-CONFIGURATION */
Object copy_user_restrictions_into_object_configuration(block,
	    user_restrictions)
    Object block, user_restrictions;
{
    Object old_object_configuration, new_object_configuration;

    x_note_fn_call(180,107);
    old_object_configuration = get_lookup_slot_value(block,
	    Qobject_configuration);
    new_object_configuration = 
	    convert_user_restrictions_into_object_configuration(old_object_configuration,
	    user_restrictions);
    if ( !EQ(old_object_configuration,get_slot_init_form(2,
	    ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)1L),
	    Qobject_configuration)))
	reclaim_slot_value_list_1(old_object_configuration);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(block,Qobject_configuration);
    set_lookup_slot_value_1(block,Qobject_configuration,
	    new_object_configuration);
    update_representations_of_slot_value(2,block,Qobject_configuration);
    return VALUES_1(new_object_configuration);
}

/* COPY-CLASS-RESTRICTIONS-INTO-INSTANCE-CONFIGURATION */
Object copy_class_restrictions_into_instance_configuration(block,
	    class_restrictions)
    Object block, class_restrictions;
{
    Object old_object_configuration, new_object_configuration;

    x_note_fn_call(180,108);
    old_object_configuration = ISVREF(block,(SI_Long)23L);
    new_object_configuration = 
	    convert_user_restrictions_into_object_configuration(old_object_configuration,
	    class_restrictions);
    if ( !EQ(old_object_configuration,get_slot_init_form(2,
	    ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)1L),
	    Qinstance_configuration)))
	reclaim_slot_value_list_1(old_object_configuration);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(block,Qinstance_configuration);
    SVREF(block,FIX((SI_Long)23L)) = new_object_configuration;
    update_representations_of_slot_value(2,block,Qinstance_configuration);
    return VALUES_1(new_object_configuration);
}

static Object Qtable_of_values;    /* table-of-values */

static Object Qconnection;         /* connection */

/* FRAME-MATCHES-RESTRICTION-CLASS-SPEC */
Object frame_matches_restriction_class_spec(frame_qm,class_spec,
	    current_frame_qm)
    Object frame_qm, class_spec, current_frame_qm;
{
    Object temp, class_description, class_for_restrictions;
    Object sub_class_bit_vector, gensymed_symbol_3, class_1, ab_loop_list_;
    Object ab_loop_it_;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(180,109);
    if ( !TRUEP(class_spec))
	temp = T;
    else if ( !TRUEP(frame_qm))
	temp = Nil;
    else if (ATOM(class_spec)) {
	if (EQ(frame_qm,current_frame_qm)) {
	    class_description = SIMPLE_VECTOR_P(frame_qm) && 
		    EQ(ISVREF(frame_qm,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? frame_qm : ISVREF(frame_qm,(SI_Long)1L);
	    class_for_restrictions = class_spec;
	    if (EQ(class_for_restrictions,Qitem)) {
		temp = ISVREF(class_description,(SI_Long)16L);
		if (temp);
		else {
		    sub_class_bit_vector = ISVREF(class_description,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Name_box_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
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
			temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
		    }
		    else
			temp = Nil;
		}
		if (temp);
		else
		    temp = EQ(ISVREF(class_description,(SI_Long)1L),
			    Qtable) ? T : Nil;
		if (temp);
		else {
		    sub_class_bit_vector = ISVREF(class_description,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Arrow_button_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
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
			temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
		    }
		    else
			temp = Nil;
		}
		if (temp);
		else {
		    sub_class_bit_vector = ISVREF(class_description,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Scrap_class_description,(SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
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
			temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
		    }
		    else
			temp = Nil;
		}
		if (temp);
		else {
		    sub_class_bit_vector = ISVREF(class_description,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Loose_end_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
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
			temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
		    }
		    else
			temp = Nil;
		}
		if (temp);
		else {
		    gensymed_symbol_3 = 
			    lookup_global_or_kb_specific_property_value(Qtable_of_values,
			    Class_description_gkbprop);
		    if (gensymed_symbol_3) {
			sub_class_bit_vector = ISVREF(class_description,
				(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(gensymed_symbol_3,(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_1 = (SI_Long)1L;
			    gensymed_symbol_2 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_1 = gensymed_symbol_1 << 
				    gensymed_symbol_2;
			    gensymed_symbol = gensymed_symbol & 
				    gensymed_symbol_1;
			    temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
			}
			else
			    temp = Nil;
		    }
		    else
			temp = Nil;
		}
		if (temp);
		else {
		    sub_class_bit_vector = ISVREF(class_description,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Explanation_table_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
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
			temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
		    }
		    else
			temp = Nil;
		}
		if (temp);
		else {
		    sub_class_bit_vector = ISVREF(class_description,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Ok_class_description,(SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
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
			temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
		    }
		    else
			temp = Nil;
		}
		if (temp);
		else {
		    sub_class_bit_vector = ISVREF(class_description,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Authorized_user_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
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
			temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
		    }
		    else
			temp = Nil;
		}
	    }
	    else if (EQ(class_for_restrictions,Qconnection)) {
		sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
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
		    temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
		}
		else
		    temp = Nil;
		if (temp);
		else {
		    sub_class_bit_vector = ISVREF(class_description,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Loose_end_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
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
			temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
		    }
		    else
			temp = Nil;
		}
	    }
	    else {
		gensymed_symbol_3 = 
			lookup_global_or_kb_specific_property_value(class_for_restrictions,
			Class_description_gkbprop);
		if (gensymed_symbol_3) {
		    sub_class_bit_vector = ISVREF(class_description,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_3,(SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
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
			temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
		    }
		    else
			temp = Nil;
		}
		else
		    temp = Nil;
	    }
	}
	else
	    temp = Nil;
    }
    else {
	class_description = SIMPLE_VECTOR_P(frame_qm) && 
		EQ(ISVREF(frame_qm,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 frame_qm : ISVREF(frame_qm,(SI_Long)1L);
	class_1 = Nil;
	ab_loop_list_ = class_spec;
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	class_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(class_1,Qitem)) {
	    temp = ISVREF(class_description,(SI_Long)16L);
	    if (temp);
	    else {
		sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Name_box_class_description,(SI_Long)18L));
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
		    temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
		}
		else
		    temp = Nil;
	    }
	    if (temp);
	    else
		temp = EQ(ISVREF(class_description,(SI_Long)1L),Qtable) ? 
			T : Nil;
	    if (temp);
	    else {
		sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Arrow_button_class_description,
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
		    temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
		}
		else
		    temp = Nil;
	    }
	    if (temp);
	    else {
		sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Scrap_class_description,(SI_Long)18L));
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
		    temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
		}
		else
		    temp = Nil;
	    }
	    if (temp);
	    else {
		sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Loose_end_class_description,(SI_Long)18L));
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
		    temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
		}
		else
		    temp = Nil;
	    }
	    if (temp);
	    else {
		gensymed_symbol_3 = 
			lookup_global_or_kb_specific_property_value(Qtable_of_values,
			Class_description_gkbprop);
		if (gensymed_symbol_3) {
		    sub_class_bit_vector = ISVREF(class_description,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_3,(SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
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
			temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
		    }
		    else
			temp = Nil;
		}
		else
		    temp = Nil;
	    }
	    if (temp);
	    else {
		sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Explanation_table_class_description,
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
		    temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
		}
		else
		    temp = Nil;
	    }
	    if (temp);
	    else {
		sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Ok_class_description,(SI_Long)18L));
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
		    temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
		}
		else
		    temp = Nil;
	    }
	    if (temp);
	    else {
		sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Authorized_user_class_description,
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
		    temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
		}
		else
		    temp = Nil;
	    }
	    ab_loop_it_ = temp;
	}
	else if (EQ(class_1,Qconnection)) {
	    sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
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
		temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
	    }
	    else
		temp = Nil;
	    if (temp);
	    else {
		sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Loose_end_class_description,(SI_Long)18L));
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
		    temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
		}
		else
		    temp = Nil;
	    }
	    ab_loop_it_ = temp;
	}
	else {
	    gensymed_symbol_3 = 
		    lookup_global_or_kb_specific_property_value(class_1,
		    Class_description_gkbprop);
	    if (gensymed_symbol_3) {
		sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_3,
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
		    ab_loop_it_ = (SI_Long)0L < gensymed_symbol ? T : Nil;
		}
		else
		    ab_loop_it_ = Nil;
	    }
	    else
		ab_loop_it_ = Nil;
	}
	if (ab_loop_it_) {
	    temp = ab_loop_it_;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

/* CLASS-DESCRIPTION-MATCHES-RESTRICTION-CLASS-SPEC */
Object class_description_matches_restriction_class_spec(class_description,
	    class_spec,current_frame_qm)
    Object class_description, class_spec, current_frame_qm;
{
    Object temp, sub_class_bit_vector, gensymed_symbol_3, class_1;
    Object ab_loop_list_, ab_loop_it_;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(180,110);
    if ( !TRUEP(class_spec)) {
	if (EQ(Qitem,Qitem)) {
	    temp = ISVREF(class_description,(SI_Long)16L);
	    if (temp);
	    else {
		sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Name_box_class_description,(SI_Long)18L));
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
		    temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
		}
		else
		    temp = Nil;
	    }
	    if (temp);
	    else
		temp = EQ(ISVREF(class_description,(SI_Long)1L),Qtable) ? 
			T : Nil;
	    if (temp);
	    else {
		sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Arrow_button_class_description,
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
		    temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
		}
		else
		    temp = Nil;
	    }
	    if (temp);
	    else {
		sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Scrap_class_description,(SI_Long)18L));
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
		    temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
		}
		else
		    temp = Nil;
	    }
	    if (temp);
	    else {
		sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Loose_end_class_description,(SI_Long)18L));
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
		    temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
		}
		else
		    temp = Nil;
	    }
	    if (temp);
	    else {
		gensymed_symbol_3 = 
			lookup_global_or_kb_specific_property_value(Qtable_of_values,
			Class_description_gkbprop);
		if (gensymed_symbol_3) {
		    sub_class_bit_vector = ISVREF(class_description,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_3,(SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
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
			temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
		    }
		    else
			temp = Nil;
		}
		else
		    temp = Nil;
	    }
	    if (temp);
	    else {
		sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Explanation_table_class_description,
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
		    temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
		}
		else
		    temp = Nil;
	    }
	    if (temp);
	    else {
		sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Ok_class_description,(SI_Long)18L));
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
		    temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
		}
		else
		    temp = Nil;
	    }
	    if (temp)
		return VALUES_1(temp);
	    else {
		sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Authorized_user_class_description,
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
		    return VALUES_1((SI_Long)0L < gensymed_symbol ? T : Nil);
		}
		else
		    return VALUES_1(Nil);
	    }
	}
	else if (EQ(Qitem,Qconnection)) {
	    sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
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
		temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
	    }
	    else
		temp = Nil;
	    if (temp)
		return VALUES_1(temp);
	    else {
		sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Loose_end_class_description,(SI_Long)18L));
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
		    return VALUES_1((SI_Long)0L < gensymed_symbol ? T : Nil);
		}
		else
		    return VALUES_1(Nil);
	    }
	}
	else
	    return VALUES_1(ISVREF(class_description,(SI_Long)16L));
    }
    else if (ATOM(class_spec))
	return VALUES_1(Nil);
    else {
	class_1 = Nil;
	ab_loop_list_ = class_spec;
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	class_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(class_1,Qitem)) {
	    temp = ISVREF(class_description,(SI_Long)16L);
	    if (temp);
	    else {
		sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Name_box_class_description,(SI_Long)18L));
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
		    temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
		}
		else
		    temp = Nil;
	    }
	    if (temp);
	    else
		temp = EQ(ISVREF(class_description,(SI_Long)1L),Qtable) ? 
			T : Nil;
	    if (temp);
	    else {
		sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Arrow_button_class_description,
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
		    temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
		}
		else
		    temp = Nil;
	    }
	    if (temp);
	    else {
		sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Scrap_class_description,(SI_Long)18L));
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
		    temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
		}
		else
		    temp = Nil;
	    }
	    if (temp);
	    else {
		sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Loose_end_class_description,(SI_Long)18L));
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
		    temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
		}
		else
		    temp = Nil;
	    }
	    if (temp);
	    else {
		gensymed_symbol_3 = 
			lookup_global_or_kb_specific_property_value(Qtable_of_values,
			Class_description_gkbprop);
		if (gensymed_symbol_3) {
		    sub_class_bit_vector = ISVREF(class_description,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_3,(SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
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
			temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
		    }
		    else
			temp = Nil;
		}
		else
		    temp = Nil;
	    }
	    if (temp);
	    else {
		sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Explanation_table_class_description,
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
		    temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
		}
		else
		    temp = Nil;
	    }
	    if (temp);
	    else {
		sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Ok_class_description,(SI_Long)18L));
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
		    temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
		}
		else
		    temp = Nil;
	    }
	    if (temp);
	    else {
		sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Authorized_user_class_description,
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
		    temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
		}
		else
		    temp = Nil;
	    }
	    ab_loop_it_ = temp;
	}
	else if (EQ(class_1,Qconnection)) {
	    sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
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
		temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
	    }
	    else
		temp = Nil;
	    if (temp);
	    else {
		sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Loose_end_class_description,(SI_Long)18L));
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
		    temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
		}
		else
		    temp = Nil;
	    }
	    ab_loop_it_ = temp;
	}
	else {
	    gensymed_symbol_3 = 
		    lookup_global_or_kb_specific_property_value(class_1,
		    Class_description_gkbprop);
	    if (gensymed_symbol_3) {
		sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_3,
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
		    ab_loop_it_ = (SI_Long)0L < gensymed_symbol ? T : Nil;
		}
		else
		    ab_loop_it_ = Nil;
	    }
	    else
		ab_loop_it_ = Nil;
	}
	if (ab_loop_it_)
	    return VALUES_1(ab_loop_it_);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

/* CLASS-IS-VISIBLE-TO-USER-P */
Object class_is_visible_to_user_p(class_name)
    Object class_name;
{
    x_note_fn_call(180,111);
    return VALUES_1(ISVREF(lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop),(SI_Long)16L));
}

/* CLASS-DEFINITION-NAME */
Object class_definition_name(class_definition)
    Object class_definition;
{
    Object temp, x2;
    char temp_1;

    x_note_fn_call(180,112);
    if (CONSP(class_definition)) {
	temp = SECOND(class_definition);
	return VALUES_1(FIRST(temp));
    }
    else {
	if (SIMPLE_VECTOR_P(class_definition) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(class_definition)) > 
		(SI_Long)2L &&  !EQ(ISVREF(class_definition,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(class_definition,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    return get_lookup_slot_value_given_default(class_definition,
		    Qname_or_names_for_frame,Nil);
	else
	    return VALUES_1(class_definition);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Superior_frame_for_restrictions_frame_qm, Qsuperior_frame_for_restrictions_frame_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Superior_frame_for_restrictions_superior_qm, Qsuperior_frame_for_restrictions_superior_qm);

/* FIX-UP-DOUBLE-CLICK-CONFIGURATION-CLAUSES */
Object fix_up_double_click_configuration_clauses(configuration)
    Object configuration;
{
    Object top_clause, ab_loop_list_, mode_clause, ab_loop_list__1, clause;
    Object ab_loop_list__2, key_code, unicode, temp, second_new_value;
    char temp_1;

    x_note_fn_call(180,113);
    top_clause = Nil;
    ab_loop_list_ = configuration;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    top_clause = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (memq_function(FIRST(top_clause),list_constant_4)) {
	mode_clause = Nil;
	ab_loop_list__1 = CDR(top_clause);
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	mode_clause = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	clause = Nil;
	ab_loop_list__2 = CDDR(mode_clause);
      next_loop_2:
	if ( !TRUEP(ab_loop_list__2))
	    goto end_loop_2;
	clause = M_CAR(ab_loop_list__2);
	ab_loop_list__2 = M_CDR(ab_loop_list__2);
	if (EQ(FIRST(clause),Qclicking) && 
		IFIX(FIXNUM_LOGAND(SECOND(clause),Double_bit)) != 
		    (SI_Long)0L) {
	    key_code = SECOND(clause);
	    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
		unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
		temp = num_len(3,FIX((SI_Long)0L),unicode,
			FIX((SI_Long)127L)) ? unicode : Illegal_key_index;
	    }
	    else
		temp = FIXNUM_LOGAND(Key_index_bits,key_code);
	    temp_1 = EQ(temp,FIX((SI_Long)770L));
	    if (temp_1);
	    else
		temp_1 = EQ(temp,FIX((SI_Long)772L));
	    if (temp_1);
	    else
		temp_1 = EQ(temp,FIX((SI_Long)774L));
	    if (temp_1);
	    else
		temp_1 = EQ(temp,FIX((SI_Long)776L));
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    second_new_value = 
		    convert_mouse_code_to_mouse_select(SECOND(clause));
	    M_SECOND(clause) = second_new_value;
	}
	goto next_loop_2;
      end_loop_2:;
	goto next_loop_1;
      end_loop_1:;
    }
    else if (EQ(FIRST(top_clause),Qproprietary)) {
	clause = Nil;
	ab_loop_list__1 = CDR(top_clause);
      next_loop_3:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_3;
	clause = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if (EQ(FIRST(clause),Qclicking) && 
		IFIX(FIXNUM_LOGAND(SECOND(clause),Double_bit)) != 
		    (SI_Long)0L) {
	    key_code = SECOND(clause);
	    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
		unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
		temp = num_len(3,FIX((SI_Long)0L),unicode,
			FIX((SI_Long)127L)) ? unicode : Illegal_key_index;
	    }
	    else
		temp = FIXNUM_LOGAND(Key_index_bits,key_code);
	    temp_1 = EQ(temp,FIX((SI_Long)770L));
	    if (temp_1);
	    else
		temp_1 = EQ(temp,FIX((SI_Long)772L));
	    if (temp_1);
	    else
		temp_1 = EQ(temp,FIX((SI_Long)774L));
	    if (temp_1);
	    else
		temp_1 = EQ(temp,FIX((SI_Long)776L));
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    second_new_value = 
		    convert_mouse_code_to_mouse_select(SECOND(clause));
	    M_SECOND(clause) = second_new_value;
	}
	goto next_loop_3;
      end_loop_3:;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(G2_identification_for_write_locks, Qg2_identification_for_write_locks);

static Object Qgensym_string;      /* gensym-string */

static Object string_constant_98;  /* "~A:~A:~A" */

static Object string_constant_99;  /* "TCPIP" */

static Object string_constant_100;  /* " [" */

static Object string_constant_101;  /* "-" */

static Object string_constant_102;  /* ":" */

static Object string_constant_103;  /* "] " */

static Object string_constant_104;  /* " (~A)~%" */

/* G2-IDENTIFICATION-FOR-WRITE-LOCKS */
Object g2_identification_for_write_locks()
{
    Object temp, current_gensym_string, fill_pointer_for_current_gensym_string;
    Object total_length_of_current_gensym_string, current_twriting_output_type;
    Object temp_1, mf, seconds, minutes, hours, date, months, years, user;
    Object found;
    Declare_special(4);
    Object result;

    x_note_fn_call(180,114);
    temp = G2_identification_for_write_locks;
    if (temp);
    else {
	current_gensym_string = 
		obtain_simple_gensym_string(FIX((SI_Long)2048L));
	PUSH_SPECIAL_WITH_SYMBOL(Current_gensym_string,Qcurrent_gensym_string,current_gensym_string,
		3);
	  fill_pointer_for_current_gensym_string = FIX((SI_Long)0L);
	  PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_gensym_string,Qfill_pointer_for_current_gensym_string,fill_pointer_for_current_gensym_string,
		  2);
	    total_length_of_current_gensym_string = FIX((SI_Long)2048L);
	    PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_gensym_string,Qtotal_length_of_current_gensym_string,total_length_of_current_gensym_string,
		    1);
	      current_twriting_output_type = Qgensym_string;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		      0);
		temp = Local_host_name;
		temp_1 = Tcp_listener_port_number;
		if (temp_1);
		else
		    temp_1 = string_constant_16;
		tformat(4,string_constant_98,temp,string_constant_99,temp_1);
		mf = 
			reconstruct_g2_time_at_start(G2_time_at_start_as_text_string);
		result = decode_unix_time_as_managed_float(mf);
		MVS_6(result,seconds,minutes,hours,date,months,years);
		reclaim_managed_simple_float_array_of_length_1(mf);
		tformat(1,string_constant_100);
		twrite_n_digit_number_with_0_pad(FIX((SI_Long)4L),years);
		tformat(1,string_constant_101);
		twrite_n_digit_number_with_0_pad(FIX((SI_Long)2L),months);
		tformat(1,string_constant_101);
		twrite_n_digit_number_with_0_pad(FIX((SI_Long)2L),date);
		tformat(1,string_constant_30);
		twrite_n_digit_number_with_0_pad(FIX((SI_Long)2L),hours);
		tformat(1,string_constant_102);
		twrite_n_digit_number_with_0_pad(FIX((SI_Long)2L),minutes);
		tformat(1,string_constant_102);
		twrite_n_digit_number_with_0_pad(FIX((SI_Long)2L),seconds);
		tformat(1,string_constant_103);
		result = get_current_user_name();
		MVS_2(result,user,found);
		if (found)
		    tformat(2,string_constant_104,user);
		G2_identification_for_write_locks = 
			copy_out_current_gensym_string();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = G2_identification_for_write_locks;
    }
    return VALUES_1(temp);
}

Object Module_is_explictly_editable_p_kbprop = UNBOUND;

static Object Qitem_is_explicitly_editable;  /* item-is-explicitly-editable */

/* ITEM-EXPLICITLY-EDITABLE-P */
Object item_explicitly_editable_p(item)
    Object item;
{
    Object temp, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_1;

    x_note_fn_call(180,115);
    temp =  !(Source_code_control_support_enabled_p || 
	    Restrict_edits_to_modules_having_read_only_files_p) ? T : Nil;
    if (temp);
    else
	temp = get_lookup_slot_value_given_default(item,
		Qitem_is_explicitly_editable,Nil);
    if (temp);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Block_class_description,
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
	    temp_1 = (SI_Long)0L < gensymed_symbol;
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? 
		block_is_invisible_to_unsavable_change_protection_p(item) :
		 Nil;
    }
    return VALUES_1(temp);
}

static Object Qunsavable_change_protection;  /* unsavable-change-protection */

static Object Qdefault_unsavable_change_protection;  /* default-unsavable-change-protection */

/* REASON-PERMANENT-ITEMS-ATTRIBUTE-IS-NOT-EDITABLE */
Object reason_permanent_items_attribute_is_not_editable varargs_1(int, n)
{
    Object item, slot_name;
    Object class_qualifier_qm, slot_description_qm, class_1;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(180,116);
    INIT_ARGS_nonrelocating();
    item = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    class_qualifier_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    slot_description_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = TRUEP(In_recompile_item_p);
    if (temp);
    else {
	class_1 = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)1L);
	temp =  !TRUEP(class_qualifier_qm) && EQ(class_1,
		Qsaving_parameters) ? EQ(slot_name,
		Qunsavable_change_protection) || EQ(item,
		Saving_parameters) && EQ(slot_name,
		Qdefault_unsavable_change_protection) : TRUEP(Qnil);
    }
    if (temp);
    else
	temp = slot_description_qm ? 
		TRUEP(reason_to_exclude_slot_description_for_compute_class_description_node_attributes(slot_description_qm)) 
		: TRUEP(Qnil);
    if ( !temp)
	return reason_permanent_items_module_is_not_editable(1,item);
    else
	return VALUES_1(Nil);
}

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qwarn_about_editing_item;  /* warn-about-editing-item */

/* REASON-PERMANENT-ITEMS-MODULE-IS-NOT-EDITABLE */
Object reason_permanent_items_module_is_not_editable varargs_1(int, n)
{
    Object item;
    Object allow_warning_p, x2, gensymed_symbol, module_qm;
    Object reason_module_is_not_editable, structure_being_reclaimed, temp_1;
    Object svref_arg_2, def_structure_schedule_task_variable, svref_new_value;
    Object new_task, temp_2;
    char temp;
    Declare_varargs_nonrelocating;
    Declare_special(1);

    x_note_fn_call(180,117);
    INIT_ARGS_nonrelocating();
    item = REQUIRED_ARG_nonrelocating();
    allow_warning_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(In_recompile_item_p)) {
	if (SIMPLE_VECTOR_P(item) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) 
		> (SI_Long)2L &&  !EQ(ISVREF(item,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	temp = gensymed_symbol ? TRUEP(ISVREF(gensymed_symbol,
		(SI_Long)16L)) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if ((temp ? (SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)4L)) & 
	    (SI_Long)1L) : TRUEP(Nil)) ?  
	    !TRUEP(item_explicitly_editable_p(item)) : TRUEP(Nil)) {
	module_qm = get_module_block_is_in(item);
	if (module_qm) {
	    if ( !TRUEP(lookup_kb_specific_property_value(module_qm,
		    Module_is_explictly_editable_p_kbprop))) {
		reason_module_is_not_editable = 
			get_reason_module_is_not_editable(1,module_qm);
		if (reason_module_is_not_editable && allow_warning_p && 
			warn_on_unsavable_change_p(module_qm)) {
		    if ( !TRUEP(memq_function(item,
			    Items_warned_in_edit_warning_context))) {
			if (Nil) {
			    if (EQ(Nil,Current_schedule_task))
				Current_schedule_task = Nil;
			    if (ISVREF(Nil,(SI_Long)6L))
				cancel_and_reclaim_scheduled_queue_element_1(Nil);
			    inline_note_reclaim_cons(Nil,Nil);
			    structure_being_reclaimed = Nil;
			    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
				    0);
			      reclaim_schedule_task_args(ISVREF(Nil,
				      (SI_Long)9L));
			      SVREF(Nil,FIX((SI_Long)9L)) = Nil;
			    POP_SPECIAL();
			    temp_1 = 
				    ISVREF(Chain_of_available_schedule_tasks_vector,
				    IFIX(Current_thread_index));
			    SVREF(Nil,FIX((SI_Long)0L)) = temp_1;
			    temp_1 = Chain_of_available_schedule_tasks_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = Nil;
			}
			def_structure_schedule_task_variable = 
				ISVREF(Chain_of_available_schedule_tasks_vector,
				IFIX(Current_thread_index));
			if (def_structure_schedule_task_variable) {
			    temp_1 = Chain_of_available_schedule_tasks_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = 
				    ISVREF(def_structure_schedule_task_variable,
				    (SI_Long)0L);
			    SVREF(temp_1,svref_arg_2) = svref_new_value;
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
			SVREF(new_task,FIX((SI_Long)4L)) = 
				Higher_than_any_priority;
			SVREF(new_task,FIX((SI_Long)9L)) = Nil;
			SVREF(new_task,FIX((SI_Long)10L)) = Nil;
			SVREF(new_task,FIX((SI_Long)7L)) = 
				Qwarn_about_editing_item;
			temp_1 = SYMBOL_FUNCTION(Qwarn_about_editing_item);
			SVREF(new_task,FIX((SI_Long)8L)) = temp_1;
			ISVREF(new_task,(SI_Long)12L) = FIX((SI_Long)3L);
			SVREF(new_task,FIX((SI_Long)13L)) = item;
			temp_1 = copy_frame_serial_number(ISVREF(item,
				(SI_Long)3L));
			SVREF(new_task,FIX((SI_Long)14L)) = temp_1;
			temp_2 = current_workstation_if_usable_for_dialog(Nil);
			if (temp_2);
			else
			    temp_2 = get_current_ui_client_interface();
			temp_1 = slot_value_list_3(module_qm,
				reason_module_is_not_editable,temp_2);
			SVREF(new_task,FIX((SI_Long)15L)) = temp_1;
			temp_1 = ISVREF(Immediate_task_queue_vector,
				(SI_Long)0L);
			SVREF(new_task,FIX((SI_Long)11L)) = temp_1;
			temp_1 = 
				constant_queue_push_right(ISVREF(Immediate_task_queue_vector,
				(SI_Long)0L),new_task);
			SVREF(new_task,FIX((SI_Long)6L)) = temp_1;
			if (In_edit_warning_context_p)
			    Items_warned_in_edit_warning_context = 
				    gensym_cons_1(item,
				    Items_warned_in_edit_warning_context);
		    }
		}
		if ( !TRUEP(allow_unsavable_change_p(module_qm)))
		    return VALUES_1(reason_module_is_not_editable);
		else
		    return VALUES_1(Nil);
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

/* ITEM-IS-EITHER-NOT-PERMANENT-OR-FROM-AN-EDITABLE-MODULE-P */
Object item_is_either_not_permanent_or_from_an_editable_module_p(item)
    Object item;
{
    Object temp;

    x_note_fn_call(180,118);
    temp =  !TRUEP(reason_permanent_items_module_is_not_editable(2,item,
	    T)) ? T : Nil;
    return VALUES_1(temp);
}

/* G2-ITEM-IS-EDITABLE */
Object g2_item_is_editable(item)
    Object item;
{
    Object temp, thing, temp_1;

    x_note_fn_call(180,119);
    temp = item_is_either_not_permanent_or_from_an_editable_module_p(item) 
	    ? Evaluation_true_value : Evaluation_false_value;
    thing = reason_permanent_items_module_is_not_editable(1,item);
    temp_1 = INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L ? 
	    copy_text_string(thing) : thing;
    return VALUES_2(temp,temp_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(See_also_for_warn_about_editing_item, Qsee_also_for_warn_about_editing_item);

static Object Qtext;               /* text */

static Object string_constant_105;  /* "Cannot edit ~NF, because ~A.  ~A" */

static Object Qedit_item_warning;  /* edit-item-warning */

static Object Quneditable_item;    /* uneditable-item */

static Object Qbutton;             /* button */

static Object array_constant_3;    /* # */

static Object Qok;                 /* ok */

static Object array_constant_4;    /* # */

static Object Qallow_edits_to;     /* allow-edits-to */

static Object Qcheck_box;          /* check-box */

static Object array_constant_5;    /* # */

static Object array_constant_6;    /* # */

static Object array_constant_7;    /* # */

static Object Qmodule;             /* module */

static Object Qt2_continuation_for_warn_about_editing_item;  /* t2-continuation-for-warn-about-editing-item */

static Object Qedits_not_allowed_on_item;  /* edits-not-allowed-on-item */

static Object Qrecord_block_for_tformat;  /* record-block-for-tformat */

static Object string_constant_106;  /* "Cannot edit ~NF, because ~A.  ~
				     *                      See the saving-parameters and the server-parameters."
				     */

/* WARN-ABOUT-EDITING-ITEM */
Object warn_about_editing_item(item,frame_serial_number,arg_list)
    Object item, frame_serial_number, arg_list;
{
    Object gensymed_symbol, temp, xa, ya, module_qm, reason;
    Object workstation_or_ui_client_interface_qm, workstation_qm;
    Object ui_client_interface_qm, x2, gensymed_symbol_1, car_new_value;
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp_1;
    Declare_special(7);

    x_note_fn_call(180,120);
    gensymed_symbol = ISVREF(item,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(item) ? (EQ(ISVREF(item,(SI_Long)1L),
	    Qavailable_frame_vector) ? T : Nil) : Qnil;
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? (IFIX(gensymed_symbol) == 
		(SI_Long)-1L ? T : Nil) : Nil;
    if (temp);
    else if (FIXNUMP(frame_serial_number))
	temp = FIXNUMP(gensymed_symbol) ? (FIXNUM_LT(frame_serial_number,
		gensymed_symbol) ? T : Nil) : T;
    else if (FIXNUMP(gensymed_symbol))
	temp = Nil;
    else {
	xa = M_CAR(frame_serial_number);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya) ? T : Nil;
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? 
		    (FIXNUM_LT(M_CDR(frame_serial_number),
		    M_CDR(gensymed_symbol)) ? T : Nil) : Qnil;
    }
    reclaim_frame_serial_number(frame_serial_number);
    if ( !TRUEP(temp)) {
	module_qm = FIRST(arg_list);
	reason = SECOND(arg_list);
	workstation_or_ui_client_interface_qm = THIRD(arg_list);
	workstation_qm = Nil;
	ui_client_interface_qm = Nil;
	reclaim_slot_value_list_1(arg_list);
	if (workstation_or_ui_client_interface_qm) {
	    if (SIMPLE_VECTOR_P(workstation_or_ui_client_interface_qm) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(workstation_or_ui_client_interface_qm)) 
		    > (SI_Long)2L &&  
		    !EQ(ISVREF(workstation_or_ui_client_interface_qm,
		    (SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(workstation_or_ui_client_interface_qm,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_1 =  !temp_1;
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    workstation_qm = workstation_or_ui_client_interface_qm;
	    warn_about_editing_item_for_workstation(workstation_qm,item,
		    module_qm,reason);
	}
	else {
	    ui_client_interface_qm = workstation_or_ui_client_interface_qm;
	    if (ui_client_interface_qm) {
		gensymed_symbol = make_eval_list_1(FIX((SI_Long)7L));
		gensymed_symbol_1 = gensymed_symbol;
		car_new_value = eval_list_3(Qtext,tformat_text_string(4,
			string_constant_105,item,reason,
			See_also_for_warn_about_editing_item),
			Qedit_item_warning);
		M_CAR(gensymed_symbol_1) = car_new_value;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		car_new_value = eval_list_3(Qitem,item,Quneditable_item);
		M_CAR(gensymed_symbol_1) = car_new_value;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		car_new_value = eval_list_3(Qbutton,
			copy_text_string(array_constant_3),Qok);
		M_CAR(gensymed_symbol_1) = car_new_value;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		car_new_value = eval_list_3(Qtext,
			copy_text_string(array_constant_4),Qallow_edits_to);
		M_CAR(gensymed_symbol_1) = car_new_value;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		car_new_value = eval_list_4(Qcheck_box,
			copy_text_string(array_constant_5),Qitem,Nil);
		M_CAR(gensymed_symbol_1) = car_new_value;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		car_new_value = eval_list_4(Qcheck_box,
			copy_text_string(array_constant_6),Qworkspace,Nil);
		M_CAR(gensymed_symbol_1) = car_new_value;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		car_new_value = eval_list_4(Qcheck_box,
			copy_text_string(array_constant_7),Qmodule,Nil);
		M_CAR(gensymed_symbol_1) = car_new_value;
		temp = 
			slot_value_list_3(Qt2_continuation_for_warn_about_editing_item,
			item,copy_frame_serial_number(ISVREF(item,
			(SI_Long)3L)));
		enter_dialog_for_t2(5,Qedits_not_allowed_on_item,
			gensymed_symbol,temp,ui_client_interface_qm,Nil);
	    }
	    else {
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
			      record_block_for_tformat(get_saving_parameters(module_qm));
			      tformat(3,string_constant_106,item,reason);
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
    }
    return VALUES_1(Nil);
}

/* WARN-ABOUT-EDITING-ITEM-FOR-WORKSTATION */
Object warn_about_editing_item_for_workstation(workstation,item,module_qm,
	    reason)
    Object workstation, item, module_qm, reason;
{
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

    x_note_fn_call(180,121);
    SAVE_STACK();
    LOCK(For_workstation);
    if (PUSH_UNWIND_PROTECT(0)) {
	current_workstation_1 = workstation;
	PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
		11);
	  current_workstation_window = ISVREF(Current_workstation,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_window,Qcurrent_workstation_window,current_workstation_window,
		  10);
	    current_g2_window_for_this_workstation_qm = 
		    ISVREF(Current_workstation,(SI_Long)25L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_g2_window_for_this_workstation_qm,Qcurrent_g2_window_for_this_workstation_qm,current_g2_window_for_this_workstation_qm,
		    9);
	      type_of_current_workstation_window = 
		      ISVREF(Current_workstation_window,(SI_Long)1L);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_window,Qtype_of_current_workstation_window,type_of_current_workstation_window,
		      8);
		current_workstation_native_window_qm = 
			ISVREF(Current_workstation_window,(SI_Long)17L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
			7);
		  temp = ISVREF(Current_workstation,(SI_Long)17L);
		  current_workstation_context = CAR(temp);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_context,Qcurrent_workstation_context,current_workstation_context,
			  6);
		    type_of_current_workstation_context = 
			    ISVREF(Current_workstation_context,(SI_Long)1L);
		    PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_context,Qtype_of_current_workstation_context,type_of_current_workstation_context,
			    5);
		      specific_structure_for_current_workstation_context = 
			      ISVREF(Current_workstation_context,(SI_Long)2L);
		      PUSH_SPECIAL_WITH_SYMBOL(Specific_structure_for_current_workstation_context,Qspecific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
			      4);
			current_workstation_detail_pane = 
				detail_pane(Current_workstation_window);
			PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_detail_pane,Qcurrent_workstation_detail_pane,current_workstation_detail_pane,
				3);
			  current_g2_user_mode_qm = 
				  ISVREF(Current_workstation,(SI_Long)19L);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
				  2);
			    new_g2_classic_ui_p = 
				    get_value_for_current_workstation_new_g2_classic_ui_p();
			    PUSH_SPECIAL_WITH_SYMBOL(New_g2_classic_ui_p,Qnew_g2_classic_ui_p,new_g2_classic_ui_p,
				    1);
			      servicing_workstation_qm = T;
			      PUSH_SPECIAL_WITH_SYMBOL(Servicing_workstation_qm,Qservicing_workstation_qm,servicing_workstation_qm,
				      0);
				SAVE_VALUES(warn_about_editing_item_for_workstation_1(item,
					module_qm,reason));
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
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object Qwarn_about_editing_item_callback;  /* warn-about-editing-item-callback */

static Object list_constant_7;     /* # */

/* WARN-ABOUT-EDITING-ITEM-FOR-WORKSTATION-1 */
Object warn_about_editing_item_for_workstation_1(item,module_qm,reason)
    Object item, module_qm, reason;
{
    Object temp, temp_1, temp_2;

    x_note_fn_call(180,122);
    temp = tformat_text_string(4,string_constant_105,item,reason,
	    See_also_for_warn_about_editing_item);
    temp_1 = copy_constant_wide_string_given_length(array_constant_3,
	    FIX((SI_Long)2L));
    temp_2 = slot_value_list_2(item,copy_frame_serial_number(ISVREF(item,
	    (SI_Long)3L)));
    enter_dialog(9,temp,temp_1,Qnone,Qwarn_about_editing_item_callback,
	    temp_2,Nil,Nil,ISVREF(ISVREF(Current_workstation,(SI_Long)11L),
	    (SI_Long)2L),ISVREF(ISVREF(Current_workstation,(SI_Long)11L),
	    (SI_Long)3L));
    return add_check_boxes_to_current_dialog(copy_text_string(array_constant_4),
	    list_constant_7);
}

/* T2-CONTINUATION-FOR-WARN-ABOUT-EDITING-ITEM */
Object t2_continuation_for_warn_about_editing_item(sequence_number,
	    client_item,item,fsn)
    Object sequence_number, client_item, item, fsn;
{
    Object check_box_list;
    Object result;

    x_note_fn_call(180,123);
    result = leave_dialog_for_t2(sequence_number);
    check_box_list = NTH_VALUE((SI_Long)1L, result);
    remove_dialog_info_from_ui_client_interface_dialog_list(sequence_number,
	    ISVREF(client_item,(SI_Long)26L));
    return warn_about_editing_item_callback(item,fsn,check_box_list);
}

static Object Qtoplevel_workspace;  /* toplevel-workspace */

/* WARN-ABOUT-EDITING-ITEM-CALLBACK */
Object warn_about_editing_item_callback(item,fsn,alist)
    Object item, fsn, alist;
{
    Object gensymed_symbol, xa, ya, type, value, ab_loop_list_;
    Object ab_loop_desetq_, workspace;
    char temp;

    x_note_fn_call(180,124);
    gensymed_symbol = ISVREF(item,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(item) ? EQ(ISVREF(item,(SI_Long)1L),
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
	type = Nil;
	value = Nil;
	ab_loop_list_ = alist;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	type = CAR(ab_loop_desetq_);
	value = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (value) {
	    if (EQ(type,Qitem))
		g2_set_item_explicitly_editable(item);
	    else if (EQ(type,Qworkspace)) {
		workspace = get_workspace_if_any(item);
		if (workspace)
		    g2_set_item_and_all_its_subblocks_explicitly_editable(workspace);
	    }
	    else if (EQ(type,Qtoplevel_workspace));
	    else if (EQ(type,Qmodule))
		g2_set_all_items_in_module_explicitly_editable(item);
	}
	goto next_loop;
      end_loop:;
    }
    reclaim_frame_serial_number(fsn);
    reclaim_slot_value_tree_1(alist);
    return VALUES_1(Nil);
}

/* G2-SET-ITEM-EXPLICITLY-EDITABLE */
Object g2_set_item_explicitly_editable(item)
    Object item;
{
    x_note_fn_call(180,125);
    return set_non_savable_lookup_slot_value(item,
	    Qitem_is_explicitly_editable,T);
}

/* G2-SET-ITEM-AND-ALL-ITS-SUBBLOCKS-EXPLICITLY-EDITABLE */
Object g2_set_item_and_all_its_subblocks_explicitly_editable(item)
    Object item;
{
    Object sub_class_bit_vector, gensymed_symbol_3, ab_queue_form_;
    Object ab_next_queue_element_, subblock;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(180,126);
    set_non_savable_lookup_slot_value(item,Qitem_is_explicitly_editable,T);
    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Block_class_description,
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
	gensymed_symbol_3 = ACCESS_ONCE(ISVREF(item,(SI_Long)14L));
	gensymed_symbol_3 = gensymed_symbol_3 ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)4L)) : Nil;
	ab_queue_form_ = gensymed_symbol_3;
	ab_next_queue_element_ = Nil;
	subblock = Nil;
	if (ab_queue_form_)
	    ab_next_queue_element_ = 
		    constant_queue_next(ISVREF(ab_queue_form_,(SI_Long)2L),
		    ab_queue_form_);
      next_loop:
	if ( !TRUEP(ab_next_queue_element_))
	    goto end_loop;
	subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	ab_next_queue_element_ = 
		constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	g2_set_item_and_all_its_subblocks_explicitly_editable(subblock);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* G2-SET-ALL-ITEMS-IN-MODULE-EXPLICITLY-EDITABLE */
Object g2_set_all_items_in_module_explicitly_editable(item_or_module)
    Object item_or_module;
{
    Object x2;
    char temp;

    x_note_fn_call(180,127);
    if (SIMPLE_VECTOR_P(item_or_module) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_module)) > (SI_Long)2L 
	    &&  !EQ(ISVREF(item_or_module,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(item_or_module,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	item_or_module = get_module_block_is_in(item_or_module);
    if (item_or_module && SYMBOLP(item_or_module))
	return mutate_kb_specific_property_value(item_or_module,T,
		Module_is_explictly_editable_p_kbprop);
    else
	return VALUES_1(Nil);
}

static Object Qreason_module_is_not_editable;  /* reason-module-is-not-editable */

static Object Qunknown;            /* unknown */

/* GET-REASON-MODULE-IS-NOT-EDITABLE */
Object get_reason_module_is_not_editable varargs_1(int, n)
{
    Object module;
    Object do_not_check_out_for_editing_p, reason_module_is_not_editable;
    Object pathname_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(180,128);
    INIT_ARGS_nonrelocating();
    module = REQUIRED_ARG_nonrelocating();
    do_not_check_out_for_editing_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    reason_module_is_not_editable = 
	    lookup_kb_specific_property_value_with_default(module,
	    Qreason_module_is_not_editable,Qunknown);
    if (do_not_check_out_for_editing_p || EQ(reason_module_is_not_editable,
	    Qunknown)) {
	pathname_qm = get_true_pathname_of_module_if_any(module);
	reason_module_is_not_editable = pathname_qm ? 
		check_if_module_is_editable(module,pathname_qm,
		do_not_check_out_for_editing_p) : Nil;
	if ( !TRUEP(do_not_check_out_for_editing_p))
	    set_reason_module_is_not_editable(module,
		    reason_module_is_not_editable);
    }
    return VALUES_1(reason_module_is_not_editable);
}

/* RECOMPUTE-EDITABILITY-OF-MODULES */
Object recompute_editability_of_modules()
{
    Object modules_with_unsaved_changes_1, suite, ab_loop_list_;
    Object module_information_instance, module_name;

    x_note_fn_call(180,129);
    modules_with_unsaved_changes_1 = modules_with_unsaved_changes();
    suite = Nil;
    ab_loop_list_ = Modules_and_system_tables_a_list;
    module_information_instance = Nil;
    module_name = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    suite = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    module_information_instance = FIRST(suite);
    module_name = ISVREF(module_information_instance,(SI_Long)23L);
    if (module_name) {
	set_reason_module_is_not_editable(module_name,Qunknown);
	mutate_kb_specific_property_value(module_name,Qunknown,
		Module_is_writable_p_kbprop);
	get_reason_module_is_not_editable(2,module_name, 
		!TRUEP(memq_function(module_name,
		modules_with_unsaved_changes_1)) ? T : Nil);
    }
    goto next_loop;
  end_loop:
    reclaim_gensym_list_1(modules_with_unsaved_changes_1);
    return VALUES_1(Nil);
}

static Object Qmodule_file_is_checked_out_for_writing_by_current_user;  /* module-file-is-checked-out-for-writing-by-current-user */

static Object Qscc_unedit;         /* scc-unedit */

/* UNEDIT-UP-TO-DATE-MODULES */
Object unedit_up_to_date_modules()
{
    Object suite, ab_loop_list_, module_information_instance, module_name;
    Object pathname_qm;

    x_note_fn_call(180,130);
    suite = Nil;
    ab_loop_list_ = Modules_and_system_tables_a_list;
    module_information_instance = Nil;
    module_name = Nil;
    pathname_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    suite = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    module_information_instance = FIRST(suite);
    module_name = ISVREF(module_information_instance,(SI_Long)23L);
    pathname_qm = get_true_pathname_of_module_if_any(module_name);
    if (module_name && pathname_qm && 
	    currently_checked_out_file_is_up_to_date_p(pathname_qm) && 
	    get_lookup_slot_value_given_default(get_saving_parameters(module_name),
	    Qmodule_file_is_checked_out_for_writing_by_current_user,Nil))
	do_scc_command(2,Qscc_unedit,pathname_qm);
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

static Object string_constant_107;  /* "the directory of the file for module ~A is not a directory" */

static Object string_constant_108;  /* "the directory of the file for module ~A is not writable" */

static Object string_constant_109;  /* "the file for module ~A is read only" */

/* CHECK-IF-MODULE-IS-EDITABLE */
Object check_if_module_is_editable(module,pathname_1,
	    do_not_check_out_for_editing_p)
    Object module, pathname_1, do_not_check_out_for_editing_p;
{
    Object namestring_as_gensym_string_1, reason_module_is_not_editable;
    Object writable_p, scc_p, directory_1, temp, error_string_qm;

    x_note_fn_call(180,131);
    namestring_as_gensym_string_1 = namestring_as_gensym_string(pathname_1);
    reason_module_is_not_editable = 
	    lookup_kb_specific_property_value_with_default(module,
	    Qreason_module_is_not_editable,Qunknown);
    writable_p = lookup_kb_specific_property_value(module,
	    Module_is_writable_p_kbprop);
    if (EQ(reason_module_is_not_editable,Qunknown)) {
	scc_p = file_is_in_source_code_control_p(pathname_1);
	if (scc_p)
	    reason_module_is_not_editable = 
		    reason_that_the_current_user_is_not_the_only_editor(pathname_1,
		    do_not_check_out_for_editing_p);
	else if (Restrict_edits_to_modules_having_read_only_files_p) {
	    directory_1 = gensym_namestring_of_directory_as_file(pathname_1);
	    if ( !TRUEP(g2_stream_directory_p(directory_1)))
		temp = tformat_text_string(2,string_constant_107,module);
	    else if ( !TRUEP(g2_stream_file_is_writable_p(directory_1)))
		temp = tformat_text_string(2,string_constant_108,module);
	    else
		temp = Qnil;
	    reclaim_text_string(directory_1);
	    if (temp);
	    else
		temp =  !(do_not_check_out_for_editing_p && scc_p) && 
			g2_stream_file_is_readable_p(namestring_as_gensym_string_1) 
			&&  
			!TRUEP(g2_stream_file_is_writable_p(namestring_as_gensym_string_1)) 
			? tformat_text_string(2,string_constant_109,
			module) : Nil;
	    reason_module_is_not_editable = temp;
	}
	else
	    reason_module_is_not_editable = Qnil;
	writable_p =  !TRUEP(reason_module_is_not_editable) ? T : Nil;
	mutate_kb_specific_property_value(module,writable_p,
		Module_is_writable_p_kbprop);
    }
    if ( !(reason_module_is_not_editable || 
	    lookup_kb_specific_property_value(module,
	    Module_is_locked_p_kbprop))) {
	error_string_qm = 
		try_to_obtain_write_lock_for_kb(namestring_as_gensym_string_1);
	if ( !TRUEP(error_string_qm))
	    mutate_kb_specific_property_value(module,T,
		    Module_is_locked_p_kbprop);
	else {
	    if ( !TRUEP(do_not_check_out_for_editing_p))
		mutate_kb_specific_property_value(module,Nil,
			Module_is_writable_p_kbprop);
	    reason_module_is_not_editable = error_string_qm;
	}
    }
    reclaim_gensym_string(namestring_as_gensym_string_1);
    return VALUES_1(reason_module_is_not_editable);
}

/* KEY-CODE-MATCH-FOR-FILTERS-P */
Object key_code_match_for_filters_p(key_code_in_event_qm,
	    key_code_in_filters_qm)
    Object key_code_in_event_qm, key_code_in_filters_qm;
{
    Object unicode, gensymed_symbol, temp_1, key, temp_2;
    SI_Long arg, arg_1, arg_2;
    char temp;

    x_note_fn_call(180,132);
    if (key_code_in_filters_qm) {
	arg = (SI_Long)769L;
	if (IFIX(FIXNUM_LOGAND(key_code_in_filters_qm,Unicode_bit)) != 
		(SI_Long)0L) {
	    unicode = FIXNUM_LOGAND(Unicode_character_bits,
		    key_code_in_filters_qm);
	    arg_1 = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) 
		    ? IFIX(unicode) : IFIX(Illegal_key_index);
	}
	else
	    arg_1 = IFIX(FIXNUM_LOGAND(Key_index_bits,key_code_in_filters_qm));
	arg_2 = (SI_Long)779L;
	temp = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
	if (temp);
	else {
	    if (IFIX(FIXNUM_LOGAND(key_code_in_filters_qm,Unicode_bit)) != 
		    (SI_Long)0L) {
		unicode = FIXNUM_LOGAND(Unicode_character_bits,
			key_code_in_filters_qm);
		gensymed_symbol = num_len(3,FIX((SI_Long)0L),unicode,
			FIX((SI_Long)127L)) ? unicode : Illegal_key_index;
	    }
	    else
		gensymed_symbol = FIXNUM_LOGAND(Key_index_bits,
			key_code_in_filters_qm);
	    temp = IFIX(gensymed_symbol) == (SI_Long)779L;
	    if (temp);
	    else
		temp = IFIX(gensymed_symbol) == (SI_Long)812L;
	    if (temp);
	    else
		temp = IFIX(gensymed_symbol) == (SI_Long)813L;
	    if (temp);
	    else
		temp = IFIX(gensymed_symbol) == (SI_Long)814L;
	}
	if (temp);
	else {
	    if (IFIX(FIXNUM_LOGAND(key_code_in_filters_qm,Unicode_bit)) != 
		    (SI_Long)0L) {
		unicode = FIXNUM_LOGAND(Unicode_character_bits,
			key_code_in_filters_qm);
		gensymed_symbol = num_len(3,FIX((SI_Long)0L),unicode,
			FIX((SI_Long)127L)) ? unicode : Illegal_key_index;
	    }
	    else
		gensymed_symbol = FIXNUM_LOGAND(Key_index_bits,
			key_code_in_filters_qm);
	    temp = IFIX(gensymed_symbol) == (SI_Long)778L;
	    if (temp);
	    else
		temp = IFIX(gensymed_symbol) == (SI_Long)815L;
	    if (temp);
	    else
		temp = IFIX(gensymed_symbol) == (SI_Long)816L;
	    if (temp);
	    else
		temp = IFIX(gensymed_symbol) == (SI_Long)817L;
	}
    }
    else
	temp = TRUEP(Nil);
    if ((temp ?  !(IFIX(FIXNUM_LOGAND(key_code_in_filters_qm,Double_bit)) 
	    != (SI_Long)0L) : TRUEP(Nil)) ? TRUEP(key_code_in_event_qm) : 
	    TRUEP(Nil))
	key_code_in_event_qm = FIXNUM_LOGAND(key_code_in_event_qm,Double_mask);
    if (key_code_in_filters_qm) {
	temp_1 =  !TRUEP(key_code_in_event_qm) ? T : Nil;
	if (temp_1);
	else
	    temp_1 = FIXNUM_EQ(key_code_in_event_qm,
		    key_code_in_filters_qm) ? T : Nil;
	if (temp_1)
	    return VALUES_1(temp_1);
	else if (FIXNUM_EQ(FIXNUM_LOGAND(Key_modifier_bits,
		key_code_in_event_qm),FIXNUM_LOGAND(Key_modifier_bits,
		key_code_in_filters_qm))) {
	    if (IFIX(FIXNUM_LOGAND(key_code_in_filters_qm,Unicode_bit)) != 
		    (SI_Long)0L) {
		unicode = FIXNUM_LOGAND(Unicode_character_bits,
			key_code_in_filters_qm);
		temp_1 = num_len(3,FIX((SI_Long)0L),unicode,
			FIX((SI_Long)127L)) ? unicode : Illegal_key_index;
	    }
	    else
		temp_1 = FIXNUM_LOGAND(Key_index_bits,key_code_in_filters_qm);
	    if (EQ(temp_1,FIX((SI_Long)769L)) || EQ(temp_1,
		    FIX((SI_Long)773L)) || EQ(temp_1,FIX((SI_Long)775L)) 
		    || EQ(temp_1,FIX((SI_Long)777L))) {
		if (IFIX(FIXNUM_LOGAND(key_code_in_event_qm,Unicode_bit)) 
			!= (SI_Long)0L) {
		    unicode = FIXNUM_LOGAND(Unicode_character_bits,
			    key_code_in_event_qm);
		    gensymed_symbol = num_len(3,FIX((SI_Long)0L),unicode,
			    FIX((SI_Long)127L)) ? unicode : Illegal_key_index;
		}
		else
		    gensymed_symbol = FIXNUM_LOGAND(Key_index_bits,
			    key_code_in_event_qm);
		temp = IFIX(gensymed_symbol) == (SI_Long)779L;
		if (temp);
		else
		    temp = IFIX(gensymed_symbol) == (SI_Long)812L;
		if (temp);
		else
		    temp = IFIX(gensymed_symbol) == (SI_Long)813L;
		if (temp);
		else
		    temp = IFIX(gensymed_symbol) == (SI_Long)814L;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		temp_1 = key_code_mouse_button_name(key_code_in_event_qm);
		temp_1 = EQ(temp_1,
			key_code_mouse_button_name(key_code_in_filters_qm)) 
			? T : Nil;
	    }
	    else
		temp_1 = Nil;
	    if (temp_1)
		return VALUES_1(temp_1);
	    else {
		if (IFIX(FIXNUM_LOGAND(key_code_in_filters_qm,
			Unicode_bit)) != (SI_Long)0L) {
		    unicode = FIXNUM_LOGAND(Unicode_character_bits,
			    key_code_in_filters_qm);
		    key = num_len(3,FIX((SI_Long)0L),unicode,
			    FIX((SI_Long)127L)) ? unicode : Illegal_key_index;
		}
		else
		    key = FIXNUM_LOGAND(Key_index_bits,key_code_in_filters_qm);
		if (IFIX(key) == (SI_Long)770L) {
		    if (IFIX(FIXNUM_LOGAND(key_code_in_event_qm,
			    Unicode_bit)) != (SI_Long)0L) {
			unicode = FIXNUM_LOGAND(Unicode_character_bits,
				key_code_in_event_qm);
			temp_1 = num_len(3,FIX((SI_Long)0L),unicode,
				FIX((SI_Long)127L)) ? unicode : 
				Illegal_key_index;
		    }
		    else
			temp_1 = FIXNUM_LOGAND(Key_index_bits,
				key_code_in_event_qm);
		    temp_2 = EQ(temp_1,FIX((SI_Long)770L)) ? T : Nil;
		    if (temp_2);
		    else
			temp_2 = EQ(temp_1,FIX((SI_Long)772L)) ? T : Nil;
		    if (temp_2);
		    else
			temp_2 = EQ(temp_1,FIX((SI_Long)774L)) ? T : Nil;
		    if (temp_2)
			return VALUES_1(temp_2);
		    else
			return VALUES_1(EQ(temp_1,FIX((SI_Long)776L)) ? T :
				 Nil);
		}
		else if (IFIX(key) == (SI_Long)769L) {
		    if (IFIX(FIXNUM_LOGAND(key_code_in_event_qm,
			    Unicode_bit)) != (SI_Long)0L) {
			unicode = FIXNUM_LOGAND(Unicode_character_bits,
				key_code_in_event_qm);
			gensymed_symbol = num_len(3,FIX((SI_Long)0L),
				unicode,FIX((SI_Long)127L)) ? unicode : 
				Illegal_key_index;
		    }
		    else
			gensymed_symbol = FIXNUM_LOGAND(Key_index_bits,
				key_code_in_event_qm);
		    temp_1 = IFIX(gensymed_symbol) == (SI_Long)779L ? T : Nil;
		    if (temp_1);
		    else
			temp_1 = IFIX(gensymed_symbol) == (SI_Long)812L ? 
				T : Nil;
		    if (temp_1);
		    else
			temp_1 = IFIX(gensymed_symbol) == (SI_Long)813L ? 
				T : Nil;
		    if (temp_1);
		    else
			temp_1 = IFIX(gensymed_symbol) == (SI_Long)814L ? 
				T : Nil;
		    if (temp_1)
			return VALUES_1(temp_1);
		    else {
			if (IFIX(FIXNUM_LOGAND(key_code_in_event_qm,
				Unicode_bit)) != (SI_Long)0L) {
			    unicode = FIXNUM_LOGAND(Unicode_character_bits,
				    key_code_in_event_qm);
			    temp_1 = num_len(3,FIX((SI_Long)0L),unicode,
				    FIX((SI_Long)127L)) ? unicode : 
				    Illegal_key_index;
			}
			else
			    temp_1 = FIXNUM_LOGAND(Key_index_bits,
				    key_code_in_event_qm);
			temp_2 = EQ(temp_1,FIX((SI_Long)769L)) ? T : Nil;
			if (temp_2);
			else
			    temp_2 = EQ(temp_1,FIX((SI_Long)773L)) ? T : Nil;
			if (temp_2);
			else
			    temp_2 = EQ(temp_1,FIX((SI_Long)775L)) ? T : Nil;
			if (temp_2)
			    return VALUES_1(temp_2);
			else
			    return VALUES_1(EQ(temp_1,FIX((SI_Long)777L)) ?
				     T : Nil);
		    }
		}
		else if (IFIX(key) == (SI_Long)779L) {
		    if (IFIX(FIXNUM_LOGAND(key_code_in_event_qm,
			    Unicode_bit)) != (SI_Long)0L) {
			unicode = FIXNUM_LOGAND(Unicode_character_bits,
				key_code_in_event_qm);
			gensymed_symbol = num_len(3,FIX((SI_Long)0L),
				unicode,FIX((SI_Long)127L)) ? unicode : 
				Illegal_key_index;
		    }
		    else
			gensymed_symbol = FIXNUM_LOGAND(Key_index_bits,
				key_code_in_event_qm);
		    temp_1 = IFIX(gensymed_symbol) == (SI_Long)779L ? T : Nil;
		    if (temp_1);
		    else
			temp_1 = IFIX(gensymed_symbol) == (SI_Long)812L ? 
				T : Nil;
		    if (temp_1);
		    else
			temp_1 = IFIX(gensymed_symbol) == (SI_Long)813L ? 
				T : Nil;
		    if (temp_1)
			return VALUES_1(temp_1);
		    else
			return VALUES_1(IFIX(gensymed_symbol) == 
				(SI_Long)814L ? T : Nil);
		}
		else
		    return VALUES_1(Qnil);
	    }
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object list_constant_8;     /* # */

/* MAP-OVER-MATCHING-USER-INTERFACE-CLAUSES-1 */
Object map_over_matching_user_interface_clauses_1(clauses,key_code_qm,
	    frame_qm,location,function,arg_1,arg_2)
    Object clauses, key_code_qm, frame_qm, location, function, arg_1, arg_2;
{
    Object clause, ab_loop_list_, specified_key_code_qm, class_spec_qm;
    Object key_matches_qm, temp;
    char temp_1;
    Object result;

    x_note_fn_call(180,133);
    clause = Nil;
    ab_loop_list_ = clauses;
    specified_key_code_qm = Nil;
    class_spec_qm = Nil;
    key_matches_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    clause = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = FIRST(clause);
    if (EQ(temp,Qpressing) || EQ(temp,Qclicking))
	specified_key_code_qm = SECOND(clause);
    else if (EQ(temp,Qselecting) || EQ(temp,Qselecting_absolutely))
	specified_key_code_qm = FIX((SI_Long)779L);
    else if (EQ(temp,Qworkspace_menu)) {
	if ( !TRUEP(selection_enabled_p(0))) {
	    temp = FIRST(clause);
	    if (EQ(temp,Qworkspace_menu))
		temp = THIRD(clause);
	    else if (EQ(temp,Qtable))
		temp = FOURTH(clause);
	    else if (EQ(temp,Qnon_menu))
		temp = THIRD(clause);
	    else if (EQ(temp,Qmain_menu))
		temp = SECOND(clause);
	    else if (EQ(temp,Qglobal_keyboard_command))
		temp = SECOND(clause);
	    else
		temp = Qnil;
	    temp_1 = TRUEP(memq_function(temp,list_constant_8));
	}
	else
	    temp_1 = TRUEP(Nil);
	specified_key_code_qm = temp_1 ? FIX((SI_Long)779L) : Nil;
    }
    else
	specified_key_code_qm = Qnil;
    temp = FIRST(clause);
    if (EQ(temp,Qpressing) || EQ(temp,Qclicking))
	class_spec_qm = FOURTH(clause);
    else if (EQ(temp,Qselecting) || EQ(temp,Qselecting_absolutely))
	class_spec_qm = SECOND(clause);
    else if (EQ(temp,Qworkspace_menu))
	class_spec_qm = SECOND(clause);
    else if (EQ(temp,Qtable))
	class_spec_qm = SECOND(clause);
    else if (EQ(temp,Qnon_menu))
	class_spec_qm = SECOND(clause);
    else if (EQ(temp,Qglobal_keyboard_command))
	class_spec_qm = Nil;
    else if (EQ(temp,Qconstrain))
	class_spec_qm = THIRD(clause);
    else
	class_spec_qm = Qnil;
    key_matches_qm = key_code_match_for_filters_p(key_code_qm,
	    specified_key_code_qm);
    if (key_matches_qm && frame_matches_restriction_class_spec(frame_qm,
	    class_spec_qm,location)) {
	result = FUNCALL_3(function,clause,arg_1,arg_2);
	MVS_2(result,arg_1,arg_2);
    }
    goto next_loop;
  end_loop:;
    return VALUES_2(arg_1,arg_2);
}

/* MAP-OVER-MATCHING-USER-INTERFACE-CLAUSES */
Object map_over_matching_user_interface_clauses varargs_1(int, n)
{
    Object mode, key_code_qm, frame_qm, function;
    Object positional_frame_qm, arg_1, arg_2, proprietary_qm;
    Object traversing_class_hierarchy_qm, the_class_inheritance_path;
    Object original_item_or_class_description_qm;
    Object frame_with_modified_superior_qm, x2, class_description_qm, location;
    Object annotations, clause, ab_loop_list_, mode_annotation;
    Object ab_loop_list__1, type, modes, the_class_inheritance_path_old_value;
    Object temp_1, class_name, defn;
    char temp;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(180,134);
    INIT_ARGS_nonrelocating();
    mode = REQUIRED_ARG_nonrelocating();
    key_code_qm = REQUIRED_ARG_nonrelocating();
    frame_qm = REQUIRED_ARG_nonrelocating();
    function = REQUIRED_ARG_nonrelocating();
    positional_frame_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    arg_1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    arg_2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    if (positional_frame_qm)
	proprietary_qm = in_order_p(positional_frame_qm);
    else if (frame_qm)
	proprietary_qm = in_order_p(frame_qm);
    else
	proprietary_qm = Qnil;
    traversing_class_hierarchy_qm = Nil;
    the_class_inheritance_path = Nil;
    original_item_or_class_description_qm = frame_qm;
    frame_with_modified_superior_qm = Superior_frame_for_restrictions_frame_qm;
    if (SIMPLE_VECTOR_P(original_item_or_class_description_qm) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(original_item_or_class_description_qm)) 
	    > (SI_Long)2L &&  
	    !EQ(ISVREF(original_item_or_class_description_qm,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(original_item_or_class_description_qm,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	class_description_qm = 
		ISVREF(original_item_or_class_description_qm,(SI_Long)1L);
    else if (SIMPLE_VECTOR_P(original_item_or_class_description_qm) && 
	    EQ(ISVREF(original_item_or_class_description_qm,(SI_Long)0L),
	    Qg2_defstruct_structure_name_class_description_g2_struct))
	class_description_qm = original_item_or_class_description_qm;
    else
	class_description_qm = Qnil;
    location = positional_frame_qm;
    if (location);
    else {
	if (SIMPLE_VECTOR_P(original_item_or_class_description_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(original_item_or_class_description_qm)) 
		> (SI_Long)2L &&  
		!EQ(ISVREF(original_item_or_class_description_qm,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(original_item_or_class_description_qm,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	location = temp ? original_item_or_class_description_qm : 
		Kb_restrictions;
    }
    annotations = Nil;
  next_loop:
    if ( !TRUEP(location))
	goto end_loop;
    if ( !TRUEP(traversing_class_hierarchy_qm))
	annotations = get_lookup_slot_value(location,Qobject_configuration);
    else {
	if (SIMPLE_VECTOR_P(location) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(location)) > (SI_Long)2L && 
		 !EQ(ISVREF(location,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(location,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if ( !temp)
	    annotations = Nil;
	else
	    annotations = ISVREF(location,(SI_Long)23L);
    }
    clause = Nil;
    ab_loop_list_ = annotations;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    clause = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (memq_function(FIRST(clause),list_constant_4)) {
	mode_annotation = Nil;
	ab_loop_list__1 = CDR(clause);
      next_loop_2:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_2;
	mode_annotation = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	temp =  !TRUEP(mode);
	if (temp);
	else {
	    type = FIRST(mode_annotation);
	    modes = SECOND(mode_annotation);
	    if (EQ(type,Qwhen))
		temp = TRUEP(memq_function(mode,modes));
	    else if (EQ(type,Qunless))
		temp =  !EQ(mode,Qadministrator) ?  
			!TRUEP(memq_function(mode,modes)) : TRUEP(Qnil);
	    else
		temp = TRUEP(Qnil);
	}
	if (temp) {
	    result = map_over_matching_user_interface_clauses_1(CDDR(mode_annotation),
		    key_code_qm,frame_qm,location,function,arg_1,arg_2);
	    MVS_2(result,arg_1,arg_2);
	}
	goto next_loop_2;
      end_loop_2:;
    }
    else if (EQ(FIRST(clause),Qproprietary)) {
	temp = TRUEP(proprietary_qm);
	if (temp);
	else {
	    if (traversing_class_hierarchy_qm) {
		if (SIMPLE_VECTOR_P(location) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(location)) > 
			(SI_Long)2L &&  !EQ(ISVREF(location,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(location,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	    temp = temp ? TRUEP(in_order_p(location)) : TRUEP(Nil);
	}
	if (temp) {
	    result = map_over_matching_user_interface_clauses_1(CDR(clause),
		    key_code_qm,frame_qm,location,function,arg_1,arg_2);
	    MVS_2(result,arg_1,arg_2);
	}
    }
    goto next_loop_1;
  end_loop_1:;
    if (traversing_class_hierarchy_qm) {
	the_class_inheritance_path_old_value = the_class_inheritance_path;
	temp_1 = FIRST(the_class_inheritance_path_old_value);
	the_class_inheritance_path = 
		REST(the_class_inheritance_path_old_value);
	class_name = temp_1;
	defn = class_name &&  !EQ(class_name,Qitem) ? 
		lookup_global_or_kb_specific_property_value(class_name,
		Class_definition_gkbprop) : Qnil;
	location = CONSP(defn) ? class_name : defn;
    }
    else if (EQ(location,Kb_restrictions)) {
	if (class_description_qm) {
	    traversing_class_hierarchy_qm = T;
	    the_class_inheritance_path = ISVREF(class_description_qm,
		    (SI_Long)2L);
	    the_class_inheritance_path_old_value = the_class_inheritance_path;
	    temp_1 = FIRST(the_class_inheritance_path_old_value);
	    the_class_inheritance_path = 
		    REST(the_class_inheritance_path_old_value);
	    class_name = temp_1;
	    defn = class_name ? 
		    lookup_global_or_kb_specific_property_value(class_name,
		    Class_definition_gkbprop) : Qnil;
	    location = CONSP(defn) ? class_name : defn;
	}
	else
	    location = Nil;
    }
    else if (EQ(location,frame_with_modified_superior_qm)) {
	frame_with_modified_superior_qm = Nil;
	location = Superior_frame_for_restrictions_superior_qm;
    }
    else {
	location = superior_frame(location);
	if (location);
	else
	    location = Kb_restrictions;
    }
    goto next_loop;
  end_loop:;
    return VALUES_2(arg_1,arg_2);
}

static Object Qmenu;               /* menu */

static Object Qinternal;           /* internal */

static Object Quser;               /* user */

/* EVENT-INTERPRETATION-FOR-CLAUSE */
Object event_interpretation_for_clause(clause)
    Object clause;
{
    Object temp, action_qm;
    char temp_1;

    x_note_fn_call(180,135);
    temp = FIRST(clause);
    if (EQ(temp,Qpressing) || EQ(temp,Qclicking))
	action_qm = THIRD(clause);
    else if (EQ(temp,Qselecting) || EQ(temp,Qselecting_absolutely))
	action_qm = THIRD(clause);
    else if (EQ(temp,Qworkspace_menu)) {
	if ( !TRUEP(selection_enabled_p(0))) {
	    temp = FIRST(clause);
	    if (EQ(temp,Qworkspace_menu))
		temp = THIRD(clause);
	    else if (EQ(temp,Qtable))
		temp = FOURTH(clause);
	    else if (EQ(temp,Qnon_menu))
		temp = THIRD(clause);
	    else if (EQ(temp,Qmain_menu))
		temp = SECOND(clause);
	    else if (EQ(temp,Qglobal_keyboard_command))
		temp = SECOND(clause);
	    else
		temp = Qnil;
	    temp_1 = TRUEP(memq_function(temp,list_constant_8));
	}
	else
	    temp_1 = TRUEP(Nil);
	action_qm = temp_1 ? Qmenu : Nil;
    }
    else
	action_qm = Qnil;
    if ( !TRUEP(action_qm))
	return VALUES_1(Nil);
    else if (EQ(action_qm,Qnothing))
	return make_event_interpretation(Qinternal,action_qm,Nil);
    else if (EQ(FIRST(clause),Qworkspace_menu) && EQ(action_qm,Qmenu))
	return make_event_interpretation(Qinternal,action_qm,Nil);
    else {
	temp = car_or_atom(action_qm);
	return make_event_interpretation(Quser,temp,cdr_or_atom(action_qm));
    }
}

static Object Qabsolute;           /* absolute */

static Object Qdone;               /* done */

/* INTERPRET-EVENT-VIA-OBJECT-CONFIGURATION-1 */
Object interpret_event_via_object_configuration_1(clause,interpretation_qm,
	    state_1)
    Object clause, interpretation_qm, state_1;
{
    Object new_interpretation_qm, new_state, temp;
    char absolute_qm, temp_1;

    x_note_fn_call(180,136);
    absolute_qm = EQ(FIRST(clause),Qselecting_absolutely);
    new_interpretation_qm = interpretation_qm;
    new_state = state_1;
    temp = FIRST(clause);
    if (EQ(temp,Qpressing) || EQ(temp,Qclicking))
	temp = THIRD(clause);
    else if (EQ(temp,Qselecting) || EQ(temp,Qselecting_absolutely))
	temp = THIRD(clause);
    else if (EQ(temp,Qworkspace_menu)) {
	if ( !TRUEP(selection_enabled_p(0))) {
	    temp = FIRST(clause);
	    if (EQ(temp,Qworkspace_menu))
		temp = THIRD(clause);
	    else if (EQ(temp,Qtable))
		temp = FOURTH(clause);
	    else if (EQ(temp,Qnon_menu))
		temp = THIRD(clause);
	    else if (EQ(temp,Qmain_menu))
		temp = SECOND(clause);
	    else if (EQ(temp,Qglobal_keyboard_command))
		temp = SECOND(clause);
	    else
		temp = Qnil;
	    temp_1 = TRUEP(memq_function(temp,list_constant_8));
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? Qmenu : Nil;
    }
    else
	temp = Qnil;
    if ( !TRUEP(temp));
    else if ( !TRUEP(state_1)) {
	new_interpretation_qm = event_interpretation_for_clause(clause);
	if (new_interpretation_qm)
	    new_state = absolute_qm ? Qabsolute : T;
    }
    else if ( !absolute_qm);
    else {
	new_interpretation_qm = event_interpretation_for_clause(clause);
	if ( !TRUEP(new_interpretation_qm));
	else if (EQ(state_1,T))
	    state_1 = Qabsolute;
	else if (EQ(state_1,Qabsolute)) {
	    reclaim_event_interpretation(new_interpretation_qm);
	    new_interpretation_qm = make_event_interpretation(Qinternal,
		    Qnothing,Nil);
	    state_1 = Qdone;
	}
	else if (EQ(state_1,Qdone));
    }
    if (interpretation_qm &&  !EQ(new_interpretation_qm,interpretation_qm))
	reclaim_event_interpretation(interpretation_qm);
    return VALUES_2(new_interpretation_qm,new_state);
}

static Object Qinterpret_event_via_object_configuration_1;  /* interpret-event-via-object-configuration-1 */

/* LOOKUP-KEY-IN-ITEM-CONFIGURATION */
Object lookup_key_in_item_configuration(keymap,keycode,spot)
    Object keymap, keycode, spot;
{
    Object unicode, frame_qm;
    SI_Long temp;

    x_note_fn_call(180,137);
    if (IFIX(FIXNUM_LOGAND(keycode,Unicode_bit)) != (SI_Long)0L) {
	unicode = FIXNUM_LOGAND(Unicode_character_bits,keycode);
	temp = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) ? 
		IFIX(unicode) : IFIX(Illegal_key_index);
    }
    else
	temp = IFIX(FIXNUM_LOGAND(Key_index_bits,keycode));
    if ( !(temp == (SI_Long)771L)) {
	frame_qm = most_interesting_frame_in_spot(spot);
	return map_over_matching_user_interface_clauses(4,
		Current_g2_user_mode_qm,keycode,frame_qm,
		SYMBOL_FUNCTION(Qinterpret_event_via_object_configuration_1));
    }
    else
	return VALUES_1(Nil);
}

static Object Qprocedure;          /* procedure */

/* MAP-OVER-EXTERNAL-NAMES-IN-OBJECT-CONFIGURATION */
Object map_over_external_names_in_object_configuration(compiled_function,
	    object_configuration)
    Object compiled_function, object_configuration;
{
    Object annotation, ab_loop_list_, temp, mode_annotation, ab_loop_list__1;
    Object clause, ab_loop_list__2;
    char temp_1;

    x_note_fn_call(180,138);
    annotation = Nil;
    ab_loop_list_ = object_configuration;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    annotation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (CONSP(annotation)) {
	temp = FIRST(annotation);
	if (EQ(temp,Qconfigure) || EQ(temp,Quser_interface)) {
	    mode_annotation = Nil;
	    ab_loop_list__1 = CDR(annotation);
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_1;
	    mode_annotation = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    clause = Nil;
	    ab_loop_list__2 = CDDR(mode_annotation);
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list__2))
		goto end_loop_2;
	    clause = M_CAR(ab_loop_list__2);
	    ab_loop_list__2 = M_CDR(ab_loop_list__2);
	    if (EQ(FIRST(clause),Qclicking)) {
		temp = THIRD(clause);
		temp_1 = CONSP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		temp = THIRD(clause);
		temp_1 = EQ(FIRST(temp),Quser_mouse_tracking);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		temp = THIRD(clause);
		FUNCALL_2(compiled_function,SECOND(temp),Qprocedure);
	    }
	    goto next_loop_2;
	  end_loop_2:;
	    goto next_loop_1;
	  end_loop_1:;
	}
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Currently_active_event_handlers_via_object_configuration, Qcurrently_active_event_handlers_via_object_configuration);

/* CURRENTLY-ACTIVE-EVENT-HANDLERS-VIA-OBJECT-CONFIGURATION-1 */
Object currently_active_event_handlers_via_object_configuration_1(clause,
	    arg_1,arg_2)
    Object clause, arg_1, arg_2;
{
    Object temp, key_code, class_spec, action_qm;
    char temp_1;

    x_note_fn_call(180,139);
    temp = FIRST(clause);
    if (EQ(temp,Qpressing) || EQ(temp,Qclicking))
	key_code = SECOND(clause);
    else if (EQ(temp,Qselecting) || EQ(temp,Qselecting_absolutely))
	key_code = FIX((SI_Long)779L);
    else if (EQ(temp,Qworkspace_menu)) {
	if ( !TRUEP(selection_enabled_p(0))) {
	    temp = FIRST(clause);
	    if (EQ(temp,Qworkspace_menu))
		temp = THIRD(clause);
	    else if (EQ(temp,Qtable))
		temp = FOURTH(clause);
	    else if (EQ(temp,Qnon_menu))
		temp = THIRD(clause);
	    else if (EQ(temp,Qmain_menu))
		temp = SECOND(clause);
	    else if (EQ(temp,Qglobal_keyboard_command))
		temp = SECOND(clause);
	    else
		temp = Qnil;
	    temp_1 = TRUEP(memq_function(temp,list_constant_8));
	}
	else
	    temp_1 = TRUEP(Nil);
	key_code = temp_1 ? FIX((SI_Long)779L) : Nil;
    }
    else
	key_code = Qnil;
    temp = FIRST(clause);
    if (EQ(temp,Qpressing) || EQ(temp,Qclicking))
	class_spec = FOURTH(clause);
    else if (EQ(temp,Qselecting) || EQ(temp,Qselecting_absolutely))
	class_spec = SECOND(clause);
    else if (EQ(temp,Qworkspace_menu))
	class_spec = SECOND(clause);
    else if (EQ(temp,Qtable))
	class_spec = SECOND(clause);
    else if (EQ(temp,Qnon_menu))
	class_spec = SECOND(clause);
    else if (EQ(temp,Qglobal_keyboard_command))
	class_spec = Nil;
    else if (EQ(temp,Qconstrain))
	class_spec = THIRD(clause);
    else
	class_spec = Qnil;
    if (class_spec);
    else
	class_spec = T;
    temp = FIRST(clause);
    if (EQ(temp,Qpressing) || EQ(temp,Qclicking))
	action_qm = THIRD(clause);
    else if (EQ(temp,Qselecting) || EQ(temp,Qselecting_absolutely))
	action_qm = THIRD(clause);
    else if (EQ(temp,Qworkspace_menu)) {
	if ( !TRUEP(selection_enabled_p(0))) {
	    temp = FIRST(clause);
	    if (EQ(temp,Qworkspace_menu))
		temp = THIRD(clause);
	    else if (EQ(temp,Qtable))
		temp = FOURTH(clause);
	    else if (EQ(temp,Qnon_menu))
		temp = THIRD(clause);
	    else if (EQ(temp,Qmain_menu))
		temp = SECOND(clause);
	    else if (EQ(temp,Qglobal_keyboard_command))
		temp = SECOND(clause);
	    else
		temp = Qnil;
	    temp_1 = TRUEP(memq_function(temp,list_constant_8));
	}
	else
	    temp_1 = TRUEP(Nil);
	action_qm = temp_1 ? Qmenu : Nil;
    }
    else
	action_qm = Qnil;
    if (action_qm) {
	temp = filter_copy(class_spec);
	temp = filter_cons_1(key_code,filter_cons_1(filter_cons_1(temp,
		filter_cons_1(filter_copy(action_qm),Nil)),Nil));
	Currently_active_event_handlers_via_object_configuration = 
		filter_cons_1(temp,
		Currently_active_event_handlers_via_object_configuration);
    }
    return VALUES_1(Nil);
}

static Object Qcurrently_active_event_handlers_via_object_configuration_1;  /* currently-active-event-handlers-via-object-configuration-1 */

/* KEY-BINDINGS-DUE-TO-OBJECT-CONFIGURATIONS */
Object key_bindings_due_to_object_configurations(frame_qm)
    Object frame_qm;
{
    Object currently_active_event_handlers_via_object_configuration;
    Declare_special(1);
    Object result;

    x_note_fn_call(180,140);
    currently_active_event_handlers_via_object_configuration = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Currently_active_event_handlers_via_object_configuration,Qcurrently_active_event_handlers_via_object_configuration,currently_active_event_handlers_via_object_configuration,
	    0);
      map_over_matching_user_interface_clauses(4,Current_g2_user_mode_qm,
	      Nil,frame_qm,
	      SYMBOL_FUNCTION(Qcurrently_active_event_handlers_via_object_configuration_1));
      result = VALUES_1(Currently_active_event_handlers_via_object_configuration);
    POP_SPECIAL();
    return result;
}

/* KEY-BINDINGS-FOR-CLASS-DESCRIPTION-ON-WORKSPACE-1 */
Object key_bindings_for_class_description_on_workspace_1(clause,alist,arg2)
    Object clause, alist, arg2;
{
    Object temp, key_code_qm, a, interpretation_plus_state, interpretation_qm;
    Object state_1, new_interpretation, new_state;
    char temp_1;
    Object result;

    x_note_fn_call(180,141);
    temp = FIRST(clause);
    if (EQ(temp,Qpressing) || EQ(temp,Qclicking))
	key_code_qm = SECOND(clause);
    else if (EQ(temp,Qselecting) || EQ(temp,Qselecting_absolutely))
	key_code_qm = FIX((SI_Long)779L);
    else if (EQ(temp,Qworkspace_menu)) {
	if ( !TRUEP(selection_enabled_p(0))) {
	    temp = FIRST(clause);
	    if (EQ(temp,Qworkspace_menu))
		temp = THIRD(clause);
	    else if (EQ(temp,Qtable))
		temp = FOURTH(clause);
	    else if (EQ(temp,Qnon_menu))
		temp = THIRD(clause);
	    else if (EQ(temp,Qmain_menu))
		temp = SECOND(clause);
	    else if (EQ(temp,Qglobal_keyboard_command))
		temp = SECOND(clause);
	    else
		temp = Qnil;
	    temp_1 = TRUEP(memq_function(temp,list_constant_8));
	}
	else
	    temp_1 = TRUEP(Nil);
	key_code_qm = temp_1 ? FIX((SI_Long)779L) : Nil;
    }
    else
	key_code_qm = Qnil;
    a = assq_function(key_code_qm,alist);
    interpretation_plus_state = CDR(a);
    interpretation_qm = CAR(interpretation_plus_state);
    state_1 = CDR(interpretation_plus_state);
    if ( !TRUEP(key_code_qm))
	return VALUES_2(alist,Nil);
    else {
	result = interpret_event_via_object_configuration_1(clause,
		interpretation_qm,state_1);
	MVS_2(result,new_interpretation,new_state);
	if ( !TRUEP(interpretation_plus_state)) {
	    interpretation_plus_state = slot_value_cons_1(Nil,Nil);
	    a = slot_value_cons_1(key_code_qm,interpretation_plus_state);
	    alist = slot_value_cons_1(a,alist);
	}
	M_CAR(interpretation_plus_state) = new_interpretation;
	M_CDR(interpretation_plus_state) = new_state;
	return VALUES_2(alist,Nil);
    }
}

static Object Qkey_bindings_for_class_description_on_workspace_1;  /* key-bindings-for-class-description-on-workspace-1 */

/* KEY-BINDINGS-FOR-CLASS-DESCRIPTION-ON-WORKSPACE */
Object key_bindings_for_class_description_on_workspace(class_description,
	    workspace)
    Object class_description, workspace;
{
    x_note_fn_call(180,142);
    return map_over_matching_user_interface_clauses(5,
	    Current_g2_user_mode_qm,Nil,class_description,
	    SYMBOL_FUNCTION(Qkey_bindings_for_class_description_on_workspace_1),
	    workspace);
}

/* OLE-DROP-ALLOWED-P */
Object ole_drop_allowed_p(workspace,class_1)
    Object workspace, class_1;
{
    x_note_fn_call(180,143);
    return VALUES_1(Nil);
}

/* COMMAND-IS-EXCLUDED-ABSOLUTELY-P */
Object command_is_excluded_absolutely_p varargs_1(int, n)
{
    Object command_name, frame_qm;
    Object positional_frame_qm, proprietary_qm, user_mode_qm;
    Object traversing_class_hierarchy_qm, the_class_inheritance_path;
    Object original_item_or_class_description_qm;
    Object frame_with_modified_superior_qm, x2, class_description_qm, location;
    Object annotations, toplevel_clause, ab_loop_list_, mode_annotation;
    Object ab_loop_list__1, type, modes, clause, ab_loop_list__2;
    Object class_spec_qm, absolute_exclusions, temp_1, gensymed_symbol;
    Object the_class_inheritance_path_old_value, class_name, defn;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(180,144);
    INIT_ARGS_nonrelocating();
    command_name = REQUIRED_ARG_nonrelocating();
    frame_qm = REQUIRED_ARG_nonrelocating();
    positional_frame_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (positional_frame_qm)
	proprietary_qm = in_order_p(positional_frame_qm);
    else if (frame_qm)
	proprietary_qm = in_order_p(frame_qm);
    else
	proprietary_qm = Qnil;
    user_mode_qm = BOUNDP(Qcurrent_g2_user_mode_qm) ? 
	    Current_g2_user_mode_qm : Qadministrator;
    traversing_class_hierarchy_qm = Nil;
    the_class_inheritance_path = Nil;
    original_item_or_class_description_qm = frame_qm;
    frame_with_modified_superior_qm = Superior_frame_for_restrictions_frame_qm;
    if (SIMPLE_VECTOR_P(original_item_or_class_description_qm) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(original_item_or_class_description_qm)) 
	    > (SI_Long)2L &&  
	    !EQ(ISVREF(original_item_or_class_description_qm,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(original_item_or_class_description_qm,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	class_description_qm = 
		ISVREF(original_item_or_class_description_qm,(SI_Long)1L);
    else if (SIMPLE_VECTOR_P(original_item_or_class_description_qm) && 
	    EQ(ISVREF(original_item_or_class_description_qm,(SI_Long)0L),
	    Qg2_defstruct_structure_name_class_description_g2_struct))
	class_description_qm = original_item_or_class_description_qm;
    else
	class_description_qm = Qnil;
    location = positional_frame_qm;
    if (location);
    else {
	if (SIMPLE_VECTOR_P(original_item_or_class_description_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(original_item_or_class_description_qm)) 
		> (SI_Long)2L &&  
		!EQ(ISVREF(original_item_or_class_description_qm,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(original_item_or_class_description_qm,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	location = temp ? original_item_or_class_description_qm : 
		Kb_restrictions;
    }
    annotations = Nil;
  next_loop:
    if ( !TRUEP(location))
	goto end_loop;
    if ( !TRUEP(traversing_class_hierarchy_qm))
	annotations = get_lookup_slot_value(location,Qobject_configuration);
    else {
	if (SIMPLE_VECTOR_P(location) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(location)) > (SI_Long)2L && 
		 !EQ(ISVREF(location,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(location,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if ( !temp)
	    annotations = Nil;
	else
	    annotations = ISVREF(location,(SI_Long)23L);
    }
    toplevel_clause = Nil;
    ab_loop_list_ = annotations;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    toplevel_clause = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (memq_function(FIRST(toplevel_clause),list_constant_4)) {
	mode_annotation = Nil;
	ab_loop_list__1 = CDR(toplevel_clause);
      next_loop_2:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_2;
	mode_annotation = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	temp =  !TRUEP(user_mode_qm);
	if (temp);
	else {
	    type = FIRST(mode_annotation);
	    modes = SECOND(mode_annotation);
	    if (EQ(type,Qwhen))
		temp = TRUEP(memq_function(user_mode_qm,modes));
	    else if (EQ(type,Qunless))
		temp =  !EQ(user_mode_qm,Qadministrator) ?  
			!TRUEP(memq_function(user_mode_qm,modes)) : 
			TRUEP(Qnil);
	    else
		temp = TRUEP(Qnil);
	}
	if (temp) {
	    clause = Nil;
	    ab_loop_list__2 = CDDR(mode_annotation);
	    class_spec_qm = Nil;
	    absolute_exclusions = Nil;
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list__2))
		goto end_loop_3;
	    clause = M_CAR(ab_loop_list__2);
	    ab_loop_list__2 = M_CDR(ab_loop_list__2);
	    temp_1 = FIRST(clause);
	    if (EQ(temp_1,Qpressing) || EQ(temp_1,Qclicking))
		class_spec_qm = FOURTH(clause);
	    else if (EQ(temp_1,Qselecting) || EQ(temp_1,Qselecting_absolutely))
		class_spec_qm = SECOND(clause);
	    else if (EQ(temp_1,Qworkspace_menu))
		class_spec_qm = SECOND(clause);
	    else if (EQ(temp_1,Qtable))
		class_spec_qm = SECOND(clause);
	    else if (EQ(temp_1,Qnon_menu))
		class_spec_qm = SECOND(clause);
	    else if (EQ(temp_1,Qglobal_keyboard_command))
		class_spec_qm = Nil;
	    else if (EQ(temp_1,Qconstrain))
		class_spec_qm = THIRD(clause);
	    else
		class_spec_qm = Qnil;
	    temp_1 = FIRST(clause);
	    if (EQ(temp_1,Qworkspace_menu))
		temp_1 = THIRD(clause);
	    else if (EQ(temp_1,Qtable))
		temp_1 = FOURTH(clause);
	    else if (EQ(temp_1,Qnon_menu))
		temp_1 = THIRD(clause);
	    else if (EQ(temp_1,Qmain_menu))
		temp_1 = SECOND(clause);
	    else if (EQ(temp_1,Qglobal_keyboard_command))
		temp_1 = SECOND(clause);
	    else
		temp_1 = Qnil;
	    if (EQ(temp_1,Qexclude_absolutely)) {
		temp_1 = FIRST(clause);
		if (EQ(temp_1,Qworkspace_menu))
		    absolute_exclusions = CDDDR(clause);
		else if (EQ(temp_1,Qtable))
		    absolute_exclusions = CDDDDR(clause);
		else if (EQ(temp_1,Qnon_menu))
		    absolute_exclusions = CDDDR(clause);
		else if (EQ(temp_1,Qmain_menu))
		    absolute_exclusions = CDDR(clause);
		else if (EQ(temp_1,Qglobal_keyboard_command))
		    absolute_exclusions = CDDR(clause);
		else
		    absolute_exclusions = Qnil;
	    }
	    else
		absolute_exclusions = Nil;
	    if (absolute_exclusions && 
		    frame_matches_restriction_class_spec(frame_qm,
		    class_spec_qm,location)) {
		gensymed_symbol = absolute_exclusions;
	      next_loop_4:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_4;
		if (EQ(M_CAR(gensymed_symbol),command_name)) {
		    temp = TRUEP(gensymed_symbol);
		    goto end_1;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_4;
	      end_loop_4:
		temp = TRUEP(Qnil);
	      end_1:;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		return VALUES_1(clause);
	    goto next_loop_3;
	  end_loop_3:;
	}
	goto next_loop_2;
      end_loop_2:;
    }
    else if (EQ(FIRST(toplevel_clause),Qproprietary)) {
	temp = TRUEP(proprietary_qm);
	if (temp);
	else {
	    if (traversing_class_hierarchy_qm) {
		if (SIMPLE_VECTOR_P(location) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(location)) > 
			(SI_Long)2L &&  !EQ(ISVREF(location,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(location,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	    temp = temp ? TRUEP(in_order_p(location)) : TRUEP(Nil);
	}
	if (temp) {
	    clause = Nil;
	    ab_loop_list__1 = CDR(toplevel_clause);
	    class_spec_qm = Nil;
	    absolute_exclusions = Nil;
	  next_loop_5:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_5;
	    clause = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    temp_1 = FIRST(clause);
	    if (EQ(temp_1,Qpressing) || EQ(temp_1,Qclicking))
		class_spec_qm = FOURTH(clause);
	    else if (EQ(temp_1,Qselecting) || EQ(temp_1,Qselecting_absolutely))
		class_spec_qm = SECOND(clause);
	    else if (EQ(temp_1,Qworkspace_menu))
		class_spec_qm = SECOND(clause);
	    else if (EQ(temp_1,Qtable))
		class_spec_qm = SECOND(clause);
	    else if (EQ(temp_1,Qnon_menu))
		class_spec_qm = SECOND(clause);
	    else if (EQ(temp_1,Qglobal_keyboard_command))
		class_spec_qm = Nil;
	    else if (EQ(temp_1,Qconstrain))
		class_spec_qm = THIRD(clause);
	    else
		class_spec_qm = Qnil;
	    temp_1 = FIRST(clause);
	    if (EQ(temp_1,Qworkspace_menu))
		temp_1 = THIRD(clause);
	    else if (EQ(temp_1,Qtable))
		temp_1 = FOURTH(clause);
	    else if (EQ(temp_1,Qnon_menu))
		temp_1 = THIRD(clause);
	    else if (EQ(temp_1,Qmain_menu))
		temp_1 = SECOND(clause);
	    else if (EQ(temp_1,Qglobal_keyboard_command))
		temp_1 = SECOND(clause);
	    else
		temp_1 = Qnil;
	    if (EQ(temp_1,Qexclude_absolutely)) {
		temp_1 = FIRST(clause);
		if (EQ(temp_1,Qworkspace_menu))
		    absolute_exclusions = CDDDR(clause);
		else if (EQ(temp_1,Qtable))
		    absolute_exclusions = CDDDDR(clause);
		else if (EQ(temp_1,Qnon_menu))
		    absolute_exclusions = CDDDR(clause);
		else if (EQ(temp_1,Qmain_menu))
		    absolute_exclusions = CDDR(clause);
		else if (EQ(temp_1,Qglobal_keyboard_command))
		    absolute_exclusions = CDDR(clause);
		else
		    absolute_exclusions = Qnil;
	    }
	    else
		absolute_exclusions = Nil;
	    if (absolute_exclusions && 
		    frame_matches_restriction_class_spec(frame_qm,
		    class_spec_qm,location)) {
		gensymed_symbol = absolute_exclusions;
	      next_loop_6:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_6;
		if (EQ(M_CAR(gensymed_symbol),command_name)) {
		    temp = TRUEP(gensymed_symbol);
		    goto end_2;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_6;
	      end_loop_6:
		temp = TRUEP(Qnil);
	      end_2:;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		return VALUES_1(clause);
	    goto next_loop_5;
	  end_loop_5:;
	}
    }
    else {
	gensymed_symbol = FIRST(toplevel_clause);
	if (EQ(gensymed_symbol,Qwhen) || EQ(gensymed_symbol,Qunless)) {
	    temp =  !TRUEP(user_mode_qm);
	    if (temp);
	    else {
		type = FIRST(toplevel_clause);
		modes = SECOND(toplevel_clause);
		if (EQ(type,Qwhen))
		    temp = TRUEP(memq_function(user_mode_qm,modes));
		else if (EQ(type,Qunless))
		    temp =  !EQ(user_mode_qm,Qadministrator) ?  
			    !TRUEP(memq_function(user_mode_qm,modes)) : 
			    TRUEP(Qnil);
		else
		    temp = TRUEP(Qnil);
	    }
	    if (temp) {
		clause = Nil;
		ab_loop_list__1 = CDDR(toplevel_clause);
		class_spec_qm = Nil;
		absolute_exclusions = Nil;
	      next_loop_7:
		if ( !TRUEP(ab_loop_list__1))
		    goto end_loop_7;
		clause = M_CAR(ab_loop_list__1);
		ab_loop_list__1 = M_CDR(ab_loop_list__1);
		temp_1 = FIRST(clause);
		if (EQ(temp_1,Qpressing) || EQ(temp_1,Qclicking))
		    class_spec_qm = FOURTH(clause);
		else if (EQ(temp_1,Qselecting) || EQ(temp_1,
			Qselecting_absolutely))
		    class_spec_qm = SECOND(clause);
		else if (EQ(temp_1,Qworkspace_menu))
		    class_spec_qm = SECOND(clause);
		else if (EQ(temp_1,Qtable))
		    class_spec_qm = SECOND(clause);
		else if (EQ(temp_1,Qnon_menu))
		    class_spec_qm = SECOND(clause);
		else if (EQ(temp_1,Qglobal_keyboard_command))
		    class_spec_qm = Nil;
		else if (EQ(temp_1,Qconstrain))
		    class_spec_qm = THIRD(clause);
		else
		    class_spec_qm = Qnil;
		temp_1 = FIRST(clause);
		if (EQ(temp_1,Qworkspace_menu))
		    temp_1 = THIRD(clause);
		else if (EQ(temp_1,Qtable))
		    temp_1 = FOURTH(clause);
		else if (EQ(temp_1,Qnon_menu))
		    temp_1 = THIRD(clause);
		else if (EQ(temp_1,Qmain_menu))
		    temp_1 = SECOND(clause);
		else if (EQ(temp_1,Qglobal_keyboard_command))
		    temp_1 = SECOND(clause);
		else
		    temp_1 = Qnil;
		if (EQ(temp_1,Qexclude_absolutely)) {
		    temp_1 = FIRST(clause);
		    if (EQ(temp_1,Qworkspace_menu))
			absolute_exclusions = CDDDR(clause);
		    else if (EQ(temp_1,Qtable))
			absolute_exclusions = CDDDDR(clause);
		    else if (EQ(temp_1,Qnon_menu))
			absolute_exclusions = CDDDR(clause);
		    else if (EQ(temp_1,Qmain_menu))
			absolute_exclusions = CDDR(clause);
		    else if (EQ(temp_1,Qglobal_keyboard_command))
			absolute_exclusions = CDDR(clause);
		    else
			absolute_exclusions = Qnil;
		}
		else
		    absolute_exclusions = Nil;
		if (absolute_exclusions && 
			frame_matches_restriction_class_spec(frame_qm,
			class_spec_qm,location)) {
		    gensymed_symbol = absolute_exclusions;
		  next_loop_8:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_8;
		    if (EQ(M_CAR(gensymed_symbol),command_name)) {
			temp = TRUEP(gensymed_symbol);
			goto end_3;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_8;
		  end_loop_8:
		    temp = TRUEP(Qnil);
		  end_3:;
		}
		else
		    temp = TRUEP(Nil);
		if (temp)
		    return VALUES_1(clause);
		goto next_loop_7;
	      end_loop_7:;
	    }
	}
    }
    goto next_loop_1;
  end_loop_1:;
    if (traversing_class_hierarchy_qm) {
	the_class_inheritance_path_old_value = the_class_inheritance_path;
	temp_1 = FIRST(the_class_inheritance_path_old_value);
	the_class_inheritance_path = 
		REST(the_class_inheritance_path_old_value);
	class_name = temp_1;
	defn = class_name &&  !EQ(class_name,Qitem) ? 
		lookup_global_or_kb_specific_property_value(class_name,
		Class_definition_gkbprop) : Qnil;
	location = CONSP(defn) ? class_name : defn;
    }
    else if (EQ(location,Kb_restrictions)) {
	if (class_description_qm) {
	    traversing_class_hierarchy_qm = T;
	    the_class_inheritance_path = ISVREF(class_description_qm,
		    (SI_Long)2L);
	    the_class_inheritance_path_old_value = the_class_inheritance_path;
	    temp_1 = FIRST(the_class_inheritance_path_old_value);
	    the_class_inheritance_path = 
		    REST(the_class_inheritance_path_old_value);
	    class_name = temp_1;
	    defn = class_name ? 
		    lookup_global_or_kb_specific_property_value(class_name,
		    Class_definition_gkbprop) : Qnil;
	    location = CONSP(defn) ? class_name : defn;
	}
	else
	    location = Nil;
    }
    else if (EQ(location,frame_with_modified_superior_qm)) {
	frame_with_modified_superior_qm = Nil;
	location = Superior_frame_for_restrictions_superior_qm;
    }
    else {
	location = superior_frame(location);
	if (location);
	else
	    location = Kb_restrictions;
    }
    goto next_loop;
  end_loop:;
    traversing_class_hierarchy_qm = Nil;
    location = Nil;
    toplevel_clause = Nil;
    ab_loop_list_ = get_lookup_slot_value_given_default(Kb_configuration,
	    Qmain_menu_user_restrictions,Nil);
  next_loop_9:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_9;
    toplevel_clause = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (memq_function(FIRST(toplevel_clause),list_constant_4)) {
	mode_annotation = Nil;
	ab_loop_list__1 = CDR(toplevel_clause);
      next_loop_10:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_10;
	mode_annotation = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	temp =  !TRUEP(user_mode_qm);
	if (temp);
	else {
	    type = FIRST(mode_annotation);
	    modes = SECOND(mode_annotation);
	    if (EQ(type,Qwhen))
		temp = TRUEP(memq_function(user_mode_qm,modes));
	    else if (EQ(type,Qunless))
		temp =  !EQ(user_mode_qm,Qadministrator) ?  
			!TRUEP(memq_function(user_mode_qm,modes)) : 
			TRUEP(Qnil);
	    else
		temp = TRUEP(Qnil);
	}
	if (temp) {
	    clause = Nil;
	    ab_loop_list__2 = CDDR(mode_annotation);
	    class_spec_qm = Nil;
	    absolute_exclusions = Nil;
	  next_loop_11:
	    if ( !TRUEP(ab_loop_list__2))
		goto end_loop_11;
	    clause = M_CAR(ab_loop_list__2);
	    ab_loop_list__2 = M_CDR(ab_loop_list__2);
	    temp_1 = FIRST(clause);
	    if (EQ(temp_1,Qpressing) || EQ(temp_1,Qclicking))
		class_spec_qm = FOURTH(clause);
	    else if (EQ(temp_1,Qselecting) || EQ(temp_1,Qselecting_absolutely))
		class_spec_qm = SECOND(clause);
	    else if (EQ(temp_1,Qworkspace_menu))
		class_spec_qm = SECOND(clause);
	    else if (EQ(temp_1,Qtable))
		class_spec_qm = SECOND(clause);
	    else if (EQ(temp_1,Qnon_menu))
		class_spec_qm = SECOND(clause);
	    else if (EQ(temp_1,Qglobal_keyboard_command))
		class_spec_qm = Nil;
	    else if (EQ(temp_1,Qconstrain))
		class_spec_qm = THIRD(clause);
	    else
		class_spec_qm = Qnil;
	    temp_1 = FIRST(clause);
	    if (EQ(temp_1,Qworkspace_menu))
		temp_1 = THIRD(clause);
	    else if (EQ(temp_1,Qtable))
		temp_1 = FOURTH(clause);
	    else if (EQ(temp_1,Qnon_menu))
		temp_1 = THIRD(clause);
	    else if (EQ(temp_1,Qmain_menu))
		temp_1 = SECOND(clause);
	    else if (EQ(temp_1,Qglobal_keyboard_command))
		temp_1 = SECOND(clause);
	    else
		temp_1 = Qnil;
	    if (EQ(temp_1,Qexclude_absolutely)) {
		temp_1 = FIRST(clause);
		if (EQ(temp_1,Qworkspace_menu))
		    absolute_exclusions = CDDDR(clause);
		else if (EQ(temp_1,Qtable))
		    absolute_exclusions = CDDDDR(clause);
		else if (EQ(temp_1,Qnon_menu))
		    absolute_exclusions = CDDDR(clause);
		else if (EQ(temp_1,Qmain_menu))
		    absolute_exclusions = CDDR(clause);
		else if (EQ(temp_1,Qglobal_keyboard_command))
		    absolute_exclusions = CDDR(clause);
		else
		    absolute_exclusions = Qnil;
	    }
	    else
		absolute_exclusions = Nil;
	    if (absolute_exclusions && 
		    frame_matches_restriction_class_spec(frame_qm,
		    class_spec_qm,location)) {
		gensymed_symbol = absolute_exclusions;
	      next_loop_12:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_12;
		if (EQ(M_CAR(gensymed_symbol),command_name)) {
		    temp = TRUEP(gensymed_symbol);
		    goto end_4;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_12;
	      end_loop_12:
		temp = TRUEP(Qnil);
	      end_4:;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		return VALUES_1(clause);
	    goto next_loop_11;
	  end_loop_11:;
	}
	goto next_loop_10;
      end_loop_10:;
    }
    else if (EQ(FIRST(toplevel_clause),Qproprietary)) {
	temp = TRUEP(proprietary_qm);
	if (temp);
	else {
	    if (traversing_class_hierarchy_qm) {
		if (SIMPLE_VECTOR_P(location) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(location)) > 
			(SI_Long)2L &&  !EQ(ISVREF(location,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(location,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	    temp = temp ? TRUEP(in_order_p(location)) : TRUEP(Nil);
	}
	if (temp) {
	    clause = Nil;
	    ab_loop_list__1 = CDR(toplevel_clause);
	    class_spec_qm = Nil;
	    absolute_exclusions = Nil;
	  next_loop_13:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_13;
	    clause = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    temp_1 = FIRST(clause);
	    if (EQ(temp_1,Qpressing) || EQ(temp_1,Qclicking))
		class_spec_qm = FOURTH(clause);
	    else if (EQ(temp_1,Qselecting) || EQ(temp_1,Qselecting_absolutely))
		class_spec_qm = SECOND(clause);
	    else if (EQ(temp_1,Qworkspace_menu))
		class_spec_qm = SECOND(clause);
	    else if (EQ(temp_1,Qtable))
		class_spec_qm = SECOND(clause);
	    else if (EQ(temp_1,Qnon_menu))
		class_spec_qm = SECOND(clause);
	    else if (EQ(temp_1,Qglobal_keyboard_command))
		class_spec_qm = Nil;
	    else if (EQ(temp_1,Qconstrain))
		class_spec_qm = THIRD(clause);
	    else
		class_spec_qm = Qnil;
	    temp_1 = FIRST(clause);
	    if (EQ(temp_1,Qworkspace_menu))
		temp_1 = THIRD(clause);
	    else if (EQ(temp_1,Qtable))
		temp_1 = FOURTH(clause);
	    else if (EQ(temp_1,Qnon_menu))
		temp_1 = THIRD(clause);
	    else if (EQ(temp_1,Qmain_menu))
		temp_1 = SECOND(clause);
	    else if (EQ(temp_1,Qglobal_keyboard_command))
		temp_1 = SECOND(clause);
	    else
		temp_1 = Qnil;
	    if (EQ(temp_1,Qexclude_absolutely)) {
		temp_1 = FIRST(clause);
		if (EQ(temp_1,Qworkspace_menu))
		    absolute_exclusions = CDDDR(clause);
		else if (EQ(temp_1,Qtable))
		    absolute_exclusions = CDDDDR(clause);
		else if (EQ(temp_1,Qnon_menu))
		    absolute_exclusions = CDDDR(clause);
		else if (EQ(temp_1,Qmain_menu))
		    absolute_exclusions = CDDR(clause);
		else if (EQ(temp_1,Qglobal_keyboard_command))
		    absolute_exclusions = CDDR(clause);
		else
		    absolute_exclusions = Qnil;
	    }
	    else
		absolute_exclusions = Nil;
	    if (absolute_exclusions && 
		    frame_matches_restriction_class_spec(frame_qm,
		    class_spec_qm,location)) {
		gensymed_symbol = absolute_exclusions;
	      next_loop_14:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_14;
		if (EQ(M_CAR(gensymed_symbol),command_name)) {
		    temp = TRUEP(gensymed_symbol);
		    goto end_5;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_14;
	      end_loop_14:
		temp = TRUEP(Qnil);
	      end_5:;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		return VALUES_1(clause);
	    goto next_loop_13;
	  end_loop_13:;
	}
    }
    else {
	gensymed_symbol = FIRST(toplevel_clause);
	if (EQ(gensymed_symbol,Qwhen) || EQ(gensymed_symbol,Qunless)) {
	    temp =  !TRUEP(user_mode_qm);
	    if (temp);
	    else {
		type = FIRST(toplevel_clause);
		modes = SECOND(toplevel_clause);
		if (EQ(type,Qwhen))
		    temp = TRUEP(memq_function(user_mode_qm,modes));
		else if (EQ(type,Qunless))
		    temp =  !EQ(user_mode_qm,Qadministrator) ?  
			    !TRUEP(memq_function(user_mode_qm,modes)) : 
			    TRUEP(Qnil);
		else
		    temp = TRUEP(Qnil);
	    }
	    if (temp) {
		clause = Nil;
		ab_loop_list__1 = CDDR(toplevel_clause);
		class_spec_qm = Nil;
		absolute_exclusions = Nil;
	      next_loop_15:
		if ( !TRUEP(ab_loop_list__1))
		    goto end_loop_15;
		clause = M_CAR(ab_loop_list__1);
		ab_loop_list__1 = M_CDR(ab_loop_list__1);
		temp_1 = FIRST(clause);
		if (EQ(temp_1,Qpressing) || EQ(temp_1,Qclicking))
		    class_spec_qm = FOURTH(clause);
		else if (EQ(temp_1,Qselecting) || EQ(temp_1,
			Qselecting_absolutely))
		    class_spec_qm = SECOND(clause);
		else if (EQ(temp_1,Qworkspace_menu))
		    class_spec_qm = SECOND(clause);
		else if (EQ(temp_1,Qtable))
		    class_spec_qm = SECOND(clause);
		else if (EQ(temp_1,Qnon_menu))
		    class_spec_qm = SECOND(clause);
		else if (EQ(temp_1,Qglobal_keyboard_command))
		    class_spec_qm = Nil;
		else if (EQ(temp_1,Qconstrain))
		    class_spec_qm = THIRD(clause);
		else
		    class_spec_qm = Qnil;
		temp_1 = FIRST(clause);
		if (EQ(temp_1,Qworkspace_menu))
		    temp_1 = THIRD(clause);
		else if (EQ(temp_1,Qtable))
		    temp_1 = FOURTH(clause);
		else if (EQ(temp_1,Qnon_menu))
		    temp_1 = THIRD(clause);
		else if (EQ(temp_1,Qmain_menu))
		    temp_1 = SECOND(clause);
		else if (EQ(temp_1,Qglobal_keyboard_command))
		    temp_1 = SECOND(clause);
		else
		    temp_1 = Qnil;
		if (EQ(temp_1,Qexclude_absolutely)) {
		    temp_1 = FIRST(clause);
		    if (EQ(temp_1,Qworkspace_menu))
			absolute_exclusions = CDDDR(clause);
		    else if (EQ(temp_1,Qtable))
			absolute_exclusions = CDDDDR(clause);
		    else if (EQ(temp_1,Qnon_menu))
			absolute_exclusions = CDDDR(clause);
		    else if (EQ(temp_1,Qmain_menu))
			absolute_exclusions = CDDR(clause);
		    else if (EQ(temp_1,Qglobal_keyboard_command))
			absolute_exclusions = CDDR(clause);
		    else
			absolute_exclusions = Qnil;
		}
		else
		    absolute_exclusions = Nil;
		if (absolute_exclusions && 
			frame_matches_restriction_class_spec(frame_qm,
			class_spec_qm,location)) {
		    gensymed_symbol = absolute_exclusions;
		  next_loop_16:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_16;
		    if (EQ(M_CAR(gensymed_symbol),command_name)) {
			temp = TRUEP(gensymed_symbol);
			goto end_6;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_16;
		  end_loop_16:
		    temp = TRUEP(Qnil);
		  end_6:;
		}
		else
		    temp = TRUEP(Nil);
		if (temp)
		    return VALUES_1(clause);
		goto next_loop_15;
	      end_loop_15:;
	    }
	}
    }
    goto next_loop_9;
  end_loop_9:;
    toplevel_clause = Nil;
    ab_loop_list_ = get_lookup_slot_value_given_default(Kb_configuration,
	    Qglobal_keyboard_command_user_restrictions,Nil);
  next_loop_17:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_17;
    toplevel_clause = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (memq_function(FIRST(toplevel_clause),list_constant_4)) {
	mode_annotation = Nil;
	ab_loop_list__1 = CDR(toplevel_clause);
      next_loop_18:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_18;
	mode_annotation = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	temp =  !TRUEP(user_mode_qm);
	if (temp);
	else {
	    type = FIRST(mode_annotation);
	    modes = SECOND(mode_annotation);
	    if (EQ(type,Qwhen))
		temp = TRUEP(memq_function(user_mode_qm,modes));
	    else if (EQ(type,Qunless))
		temp =  !EQ(user_mode_qm,Qadministrator) ?  
			!TRUEP(memq_function(user_mode_qm,modes)) : 
			TRUEP(Qnil);
	    else
		temp = TRUEP(Qnil);
	}
	if (temp) {
	    clause = Nil;
	    ab_loop_list__2 = CDDR(mode_annotation);
	    class_spec_qm = Nil;
	    absolute_exclusions = Nil;
	  next_loop_19:
	    if ( !TRUEP(ab_loop_list__2))
		goto end_loop_19;
	    clause = M_CAR(ab_loop_list__2);
	    ab_loop_list__2 = M_CDR(ab_loop_list__2);
	    temp_1 = FIRST(clause);
	    if (EQ(temp_1,Qpressing) || EQ(temp_1,Qclicking))
		class_spec_qm = FOURTH(clause);
	    else if (EQ(temp_1,Qselecting) || EQ(temp_1,Qselecting_absolutely))
		class_spec_qm = SECOND(clause);
	    else if (EQ(temp_1,Qworkspace_menu))
		class_spec_qm = SECOND(clause);
	    else if (EQ(temp_1,Qtable))
		class_spec_qm = SECOND(clause);
	    else if (EQ(temp_1,Qnon_menu))
		class_spec_qm = SECOND(clause);
	    else if (EQ(temp_1,Qglobal_keyboard_command))
		class_spec_qm = Nil;
	    else if (EQ(temp_1,Qconstrain))
		class_spec_qm = THIRD(clause);
	    else
		class_spec_qm = Qnil;
	    temp_1 = FIRST(clause);
	    if (EQ(temp_1,Qworkspace_menu))
		temp_1 = THIRD(clause);
	    else if (EQ(temp_1,Qtable))
		temp_1 = FOURTH(clause);
	    else if (EQ(temp_1,Qnon_menu))
		temp_1 = THIRD(clause);
	    else if (EQ(temp_1,Qmain_menu))
		temp_1 = SECOND(clause);
	    else if (EQ(temp_1,Qglobal_keyboard_command))
		temp_1 = SECOND(clause);
	    else
		temp_1 = Qnil;
	    if (EQ(temp_1,Qexclude_absolutely)) {
		temp_1 = FIRST(clause);
		if (EQ(temp_1,Qworkspace_menu))
		    absolute_exclusions = CDDDR(clause);
		else if (EQ(temp_1,Qtable))
		    absolute_exclusions = CDDDDR(clause);
		else if (EQ(temp_1,Qnon_menu))
		    absolute_exclusions = CDDDR(clause);
		else if (EQ(temp_1,Qmain_menu))
		    absolute_exclusions = CDDR(clause);
		else if (EQ(temp_1,Qglobal_keyboard_command))
		    absolute_exclusions = CDDR(clause);
		else
		    absolute_exclusions = Qnil;
	    }
	    else
		absolute_exclusions = Nil;
	    if (absolute_exclusions && 
		    frame_matches_restriction_class_spec(frame_qm,
		    class_spec_qm,location)) {
		gensymed_symbol = absolute_exclusions;
	      next_loop_20:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_20;
		if (EQ(M_CAR(gensymed_symbol),command_name)) {
		    temp = TRUEP(gensymed_symbol);
		    goto end_7;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_20;
	      end_loop_20:
		temp = TRUEP(Qnil);
	      end_7:;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		return VALUES_1(clause);
	    goto next_loop_19;
	  end_loop_19:;
	}
	goto next_loop_18;
      end_loop_18:;
    }
    else if (EQ(FIRST(toplevel_clause),Qproprietary)) {
	temp = TRUEP(proprietary_qm);
	if (temp);
	else {
	    if (traversing_class_hierarchy_qm) {
		if (SIMPLE_VECTOR_P(location) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(location)) > 
			(SI_Long)2L &&  !EQ(ISVREF(location,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(location,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	    temp = temp ? TRUEP(in_order_p(location)) : TRUEP(Nil);
	}
	if (temp) {
	    clause = Nil;
	    ab_loop_list__1 = CDR(toplevel_clause);
	    class_spec_qm = Nil;
	    absolute_exclusions = Nil;
	  next_loop_21:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_21;
	    clause = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    temp_1 = FIRST(clause);
	    if (EQ(temp_1,Qpressing) || EQ(temp_1,Qclicking))
		class_spec_qm = FOURTH(clause);
	    else if (EQ(temp_1,Qselecting) || EQ(temp_1,Qselecting_absolutely))
		class_spec_qm = SECOND(clause);
	    else if (EQ(temp_1,Qworkspace_menu))
		class_spec_qm = SECOND(clause);
	    else if (EQ(temp_1,Qtable))
		class_spec_qm = SECOND(clause);
	    else if (EQ(temp_1,Qnon_menu))
		class_spec_qm = SECOND(clause);
	    else if (EQ(temp_1,Qglobal_keyboard_command))
		class_spec_qm = Nil;
	    else if (EQ(temp_1,Qconstrain))
		class_spec_qm = THIRD(clause);
	    else
		class_spec_qm = Qnil;
	    temp_1 = FIRST(clause);
	    if (EQ(temp_1,Qworkspace_menu))
		temp_1 = THIRD(clause);
	    else if (EQ(temp_1,Qtable))
		temp_1 = FOURTH(clause);
	    else if (EQ(temp_1,Qnon_menu))
		temp_1 = THIRD(clause);
	    else if (EQ(temp_1,Qmain_menu))
		temp_1 = SECOND(clause);
	    else if (EQ(temp_1,Qglobal_keyboard_command))
		temp_1 = SECOND(clause);
	    else
		temp_1 = Qnil;
	    if (EQ(temp_1,Qexclude_absolutely)) {
		temp_1 = FIRST(clause);
		if (EQ(temp_1,Qworkspace_menu))
		    absolute_exclusions = CDDDR(clause);
		else if (EQ(temp_1,Qtable))
		    absolute_exclusions = CDDDDR(clause);
		else if (EQ(temp_1,Qnon_menu))
		    absolute_exclusions = CDDDR(clause);
		else if (EQ(temp_1,Qmain_menu))
		    absolute_exclusions = CDDR(clause);
		else if (EQ(temp_1,Qglobal_keyboard_command))
		    absolute_exclusions = CDDR(clause);
		else
		    absolute_exclusions = Qnil;
	    }
	    else
		absolute_exclusions = Nil;
	    if (absolute_exclusions && 
		    frame_matches_restriction_class_spec(frame_qm,
		    class_spec_qm,location)) {
		gensymed_symbol = absolute_exclusions;
	      next_loop_22:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_22;
		if (EQ(M_CAR(gensymed_symbol),command_name)) {
		    temp = TRUEP(gensymed_symbol);
		    goto end_8;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_22;
	      end_loop_22:
		temp = TRUEP(Qnil);
	      end_8:;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		return VALUES_1(clause);
	    goto next_loop_21;
	  end_loop_21:;
	}
    }
    else {
	gensymed_symbol = FIRST(toplevel_clause);
	if (EQ(gensymed_symbol,Qwhen) || EQ(gensymed_symbol,Qunless)) {
	    temp =  !TRUEP(user_mode_qm);
	    if (temp);
	    else {
		type = FIRST(toplevel_clause);
		modes = SECOND(toplevel_clause);
		if (EQ(type,Qwhen))
		    temp = TRUEP(memq_function(user_mode_qm,modes));
		else if (EQ(type,Qunless))
		    temp =  !EQ(user_mode_qm,Qadministrator) ?  
			    !TRUEP(memq_function(user_mode_qm,modes)) : 
			    TRUEP(Qnil);
		else
		    temp = TRUEP(Qnil);
	    }
	    if (temp) {
		clause = Nil;
		ab_loop_list__1 = CDDR(toplevel_clause);
		class_spec_qm = Nil;
		absolute_exclusions = Nil;
	      next_loop_23:
		if ( !TRUEP(ab_loop_list__1))
		    goto end_loop_23;
		clause = M_CAR(ab_loop_list__1);
		ab_loop_list__1 = M_CDR(ab_loop_list__1);
		temp_1 = FIRST(clause);
		if (EQ(temp_1,Qpressing) || EQ(temp_1,Qclicking))
		    class_spec_qm = FOURTH(clause);
		else if (EQ(temp_1,Qselecting) || EQ(temp_1,
			Qselecting_absolutely))
		    class_spec_qm = SECOND(clause);
		else if (EQ(temp_1,Qworkspace_menu))
		    class_spec_qm = SECOND(clause);
		else if (EQ(temp_1,Qtable))
		    class_spec_qm = SECOND(clause);
		else if (EQ(temp_1,Qnon_menu))
		    class_spec_qm = SECOND(clause);
		else if (EQ(temp_1,Qglobal_keyboard_command))
		    class_spec_qm = Nil;
		else if (EQ(temp_1,Qconstrain))
		    class_spec_qm = THIRD(clause);
		else
		    class_spec_qm = Qnil;
		temp_1 = FIRST(clause);
		if (EQ(temp_1,Qworkspace_menu))
		    temp_1 = THIRD(clause);
		else if (EQ(temp_1,Qtable))
		    temp_1 = FOURTH(clause);
		else if (EQ(temp_1,Qnon_menu))
		    temp_1 = THIRD(clause);
		else if (EQ(temp_1,Qmain_menu))
		    temp_1 = SECOND(clause);
		else if (EQ(temp_1,Qglobal_keyboard_command))
		    temp_1 = SECOND(clause);
		else
		    temp_1 = Qnil;
		if (EQ(temp_1,Qexclude_absolutely)) {
		    temp_1 = FIRST(clause);
		    if (EQ(temp_1,Qworkspace_menu))
			absolute_exclusions = CDDDR(clause);
		    else if (EQ(temp_1,Qtable))
			absolute_exclusions = CDDDDR(clause);
		    else if (EQ(temp_1,Qnon_menu))
			absolute_exclusions = CDDDR(clause);
		    else if (EQ(temp_1,Qmain_menu))
			absolute_exclusions = CDDR(clause);
		    else if (EQ(temp_1,Qglobal_keyboard_command))
			absolute_exclusions = CDDR(clause);
		    else
			absolute_exclusions = Qnil;
		}
		else
		    absolute_exclusions = Nil;
		if (absolute_exclusions && 
			frame_matches_restriction_class_spec(frame_qm,
			class_spec_qm,location)) {
		    gensymed_symbol = absolute_exclusions;
		  next_loop_24:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_24;
		    if (EQ(M_CAR(gensymed_symbol),command_name)) {
			temp = TRUEP(gensymed_symbol);
			goto end_9;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_24;
		  end_loop_24:
		    temp = TRUEP(Qnil);
		  end_9:;
		}
		else
		    temp = TRUEP(Nil);
		if (temp)
		    return VALUES_1(clause);
		goto next_loop_23;
	      end_loop_23:;
	    }
	}
    }
    goto next_loop_17;
  end_loop_17:;
    return VALUES_1(Nil);
}

static Object string_constant_110;  /* "User Defined Commands" */

/* DESCRIBE-ITEM-CONFIGURATION-KEYMAP */
Object describe_item_configuration_keymap(keymap,frame_qm)
    Object keymap, frame_qm;
{
    Object key_bindings, temp;

    x_note_fn_call(180,145);
    key_bindings = key_bindings_due_to_object_configurations(frame_qm);
    temp = describe_keymap_into_table_rows(tformat_text_string(1,
	    string_constant_110),key_bindings);
    reclaim_filter_tree_1(key_bindings);
    return VALUES_1(temp);
}

/* GET-PROPERTY-VALUE-IN-OBJECT-CONFIGURATION */
Object get_property_value_in_object_configuration(block,property_1,default_1)
    Object block, property_1, default_1;
{
    Object traversing_class_hierarchy_qm, the_class_inheritance_path;
    Object original_item_or_class_description_qm;
    Object frame_with_modified_superior_qm, x2, class_description_qm, place;
    Object object_configuration, clause, ab_loop_list_, p, v, ab_loop_list__1;
    Object temp_1, value, the_class_inheritance_path_old_value, class_name;
    Object defn;
    char temp;

    x_note_fn_call(180,146);
    traversing_class_hierarchy_qm = Nil;
    the_class_inheritance_path = Nil;
    original_item_or_class_description_qm = block;
    frame_with_modified_superior_qm = Superior_frame_for_restrictions_frame_qm;
    if (SIMPLE_VECTOR_P(original_item_or_class_description_qm) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(original_item_or_class_description_qm)) 
	    > (SI_Long)2L &&  
	    !EQ(ISVREF(original_item_or_class_description_qm,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(original_item_or_class_description_qm,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	class_description_qm = 
		ISVREF(original_item_or_class_description_qm,(SI_Long)1L);
    else if (SIMPLE_VECTOR_P(original_item_or_class_description_qm) && 
	    EQ(ISVREF(original_item_or_class_description_qm,(SI_Long)0L),
	    Qg2_defstruct_structure_name_class_description_g2_struct))
	class_description_qm = original_item_or_class_description_qm;
    else
	class_description_qm = Qnil;
    place = Nil;
    if (place);
    else {
	if (SIMPLE_VECTOR_P(original_item_or_class_description_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(original_item_or_class_description_qm)) 
		> (SI_Long)2L &&  
		!EQ(ISVREF(original_item_or_class_description_qm,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(original_item_or_class_description_qm,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	place = temp ? original_item_or_class_description_qm : Kb_restrictions;
    }
    object_configuration = Nil;
  next_loop:
    if ( !TRUEP(place))
	goto end_loop;
    if ( !TRUEP(traversing_class_hierarchy_qm))
	object_configuration = get_lookup_slot_value(place,
		Qobject_configuration);
    else {
	if (SIMPLE_VECTOR_P(place) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(place)) > (SI_Long)2L &&  
		!EQ(ISVREF(place,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(place,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if ( !temp)
	    object_configuration = Nil;
	else
	    object_configuration = ISVREF(place,(SI_Long)23L);
    }
    clause = Nil;
    ab_loop_list_ = object_configuration;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    clause = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(FIRST(clause),Qdeclaration) && 
	    frame_matches_restriction_class_spec(block,
	    M_CAR(M_CDR(clause)),place)) {
	p = Nil;
	v = Nil;
	ab_loop_list__1 = M_CDR(M_CDR(clause));
      next_loop_2:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_2;
	p = CAR(ab_loop_list__1);
	temp_1 = CDR(ab_loop_list__1);
	v = CAR(temp_1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if (EQ(p,property_1)) {
	    value = v;
	    goto end_1;
	}
	goto next_loop_2;
      end_loop_2:
	value = clause;
	goto end_1;
	value = Qnil;
      end_1:;
	if ( !EQ(value,clause)) {
	    temp_1 = value;
	    goto end_search;
	}
    }
    goto next_loop_1;
  end_loop_1:;
    if (traversing_class_hierarchy_qm) {
	the_class_inheritance_path_old_value = the_class_inheritance_path;
	temp_1 = FIRST(the_class_inheritance_path_old_value);
	the_class_inheritance_path = 
		REST(the_class_inheritance_path_old_value);
	class_name = temp_1;
	defn = class_name &&  !EQ(class_name,Qitem) ? 
		lookup_global_or_kb_specific_property_value(class_name,
		Class_definition_gkbprop) : Qnil;
	place = CONSP(defn) ? class_name : defn;
    }
    else if (EQ(place,Kb_restrictions)) {
	if (class_description_qm) {
	    traversing_class_hierarchy_qm = T;
	    the_class_inheritance_path = ISVREF(class_description_qm,
		    (SI_Long)2L);
	    the_class_inheritance_path_old_value = the_class_inheritance_path;
	    temp_1 = FIRST(the_class_inheritance_path_old_value);
	    the_class_inheritance_path = 
		    REST(the_class_inheritance_path_old_value);
	    class_name = temp_1;
	    defn = class_name ? 
		    lookup_global_or_kb_specific_property_value(class_name,
		    Class_definition_gkbprop) : Qnil;
	    place = CONSP(defn) ? class_name : defn;
	}
	else
	    place = Nil;
    }
    else if (EQ(place,frame_with_modified_superior_qm)) {
	frame_with_modified_superior_qm = Nil;
	place = Superior_frame_for_restrictions_superior_qm;
    }
    else {
	place = superior_frame(place);
	if (place);
	else
	    place = Kb_restrictions;
    }
    goto next_loop;
  end_loop:;
    temp_1 = default_1;
  end_search:
    return VALUES_1(temp_1);
}

/* GET-COMMENT-IN-OBJECT-CONFIGURATION */
Object get_comment_in_object_configuration(block,symbol)
    Object block, symbol;
{
    Object traversing_class_hierarchy_qm, the_class_inheritance_path;
    Object original_item_or_class_description_qm;
    Object frame_with_modified_superior_qm, x2, class_description_qm, place;
    Object object_configuration, clause, ab_loop_list_, spot, temp_1;
    Object the_class_inheritance_path_old_value, class_name, defn;
    char temp;

    x_note_fn_call(180,147);
    traversing_class_hierarchy_qm = Nil;
    the_class_inheritance_path = Nil;
    original_item_or_class_description_qm = block;
    frame_with_modified_superior_qm = Superior_frame_for_restrictions_frame_qm;
    if (SIMPLE_VECTOR_P(original_item_or_class_description_qm) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(original_item_or_class_description_qm)) 
	    > (SI_Long)2L &&  
	    !EQ(ISVREF(original_item_or_class_description_qm,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(original_item_or_class_description_qm,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	class_description_qm = 
		ISVREF(original_item_or_class_description_qm,(SI_Long)1L);
    else if (SIMPLE_VECTOR_P(original_item_or_class_description_qm) && 
	    EQ(ISVREF(original_item_or_class_description_qm,(SI_Long)0L),
	    Qg2_defstruct_structure_name_class_description_g2_struct))
	class_description_qm = original_item_or_class_description_qm;
    else
	class_description_qm = Qnil;
    place = Nil;
    if (place);
    else {
	if (SIMPLE_VECTOR_P(original_item_or_class_description_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(original_item_or_class_description_qm)) 
		> (SI_Long)2L &&  
		!EQ(ISVREF(original_item_or_class_description_qm,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(original_item_or_class_description_qm,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	place = temp ? original_item_or_class_description_qm : Kb_restrictions;
    }
    object_configuration = Nil;
  next_loop:
    if ( !TRUEP(place))
	goto end_loop;
    if ( !TRUEP(traversing_class_hierarchy_qm))
	object_configuration = get_lookup_slot_value(place,
		Qobject_configuration);
    else {
	if (SIMPLE_VECTOR_P(place) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(place)) > (SI_Long)2L &&  
		!EQ(ISVREF(place,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(place,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if ( !temp)
	    object_configuration = Nil;
	else
	    object_configuration = ISVREF(place,(SI_Long)23L);
    }
    clause = Nil;
    ab_loop_list_ = object_configuration;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    clause = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(FIRST(clause),Qcomment)) {
	spot = assq_function(symbol,CDR(clause));
	if (spot) {
	    temp_1 = SECOND(spot);
	    goto end_search;
	}
    }
    goto next_loop_1;
  end_loop_1:;
    if (traversing_class_hierarchy_qm) {
	the_class_inheritance_path_old_value = the_class_inheritance_path;
	temp_1 = FIRST(the_class_inheritance_path_old_value);
	the_class_inheritance_path = 
		REST(the_class_inheritance_path_old_value);
	class_name = temp_1;
	defn = class_name &&  !EQ(class_name,Qitem) ? 
		lookup_global_or_kb_specific_property_value(class_name,
		Class_definition_gkbprop) : Qnil;
	place = CONSP(defn) ? class_name : defn;
    }
    else if (EQ(place,Kb_restrictions)) {
	if (class_description_qm) {
	    traversing_class_hierarchy_qm = T;
	    the_class_inheritance_path = ISVREF(class_description_qm,
		    (SI_Long)2L);
	    the_class_inheritance_path_old_value = the_class_inheritance_path;
	    temp_1 = FIRST(the_class_inheritance_path_old_value);
	    the_class_inheritance_path = 
		    REST(the_class_inheritance_path_old_value);
	    class_name = temp_1;
	    defn = class_name ? 
		    lookup_global_or_kb_specific_property_value(class_name,
		    Class_definition_gkbprop) : Qnil;
	    place = CONSP(defn) ? class_name : defn;
	}
	else
	    place = Nil;
    }
    else if (EQ(place,frame_with_modified_superior_qm)) {
	frame_with_modified_superior_qm = Nil;
	place = Superior_frame_for_restrictions_superior_qm;
    }
    else {
	place = superior_frame(place);
	if (place);
	else
	    place = Kb_restrictions;
    }
    goto next_loop;
  end_loop:
    temp_1 = Qnil;
  end_search:
    return VALUES_1(temp_1);
}

/* GET-PROPERTY-CLAUSE */
Object get_property_clause(object_configuration,property_1)
    Object object_configuration, property_1;
{
    Object clause, ab_loop_list_, p, v, ab_loop_list__1, ab_loop_it_, temp;
    char temp_1;

    x_note_fn_call(180,148);
    clause = Nil;
    ab_loop_list_ = object_configuration;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    clause = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(FIRST(clause),Qdeclaration)) {
	p = Nil;
	v = Nil;
	ab_loop_list__1 = M_CDR(M_CDR(clause));
	ab_loop_it_ = Nil;
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
      next_loop_1:
	p = CAR(ab_loop_list__1);
	temp = CDR(ab_loop_list__1);
	v = CAR(temp);
	ab_loop_it_ = EQ(p,property_1) ? T : Nil;
	if (ab_loop_it_) {
	    temp_1 = TRUEP(ab_loop_it_);
	    goto end_1;
	}
	ab_loop_list__1 = CDDR(ab_loop_list__1);
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	goto next_loop_1;
      end_loop_1:
	temp_1 = TRUEP(Qnil);
      end_1:;
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	return VALUES_1(clause);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qkb_workspace;       /* kb-workspace */

/* CLASS-OF-BLOCK-FOR-OBJECT-CONFIGURATION */
Object class_of_block_for_object_configuration(block)
    Object block;
{
    Object class_of_block;

    x_note_fn_call(180,149);
    class_of_block = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)1L);
    if (EQ(class_of_block,Qworkspace) || EQ(class_of_block,Qkb_workspace))
	return VALUES_1(Qworkspace);
    else
	return VALUES_1(class_of_block);
}

/* BLOCK-CAN-BE-DEPENDENT-P */
Object block_can_be_dependent_p(block)
    Object block;
{
    x_note_fn_call(180,150);
    return VALUES_1( 
	    !TRUEP(get_property_value_in_object_configuration(block,
	    Qindependent_for_all_compilations,Nil)) ? T : Nil);
}

/* BLOCK-IS-UNSTABLE-P */
Object block_is_unstable_p(block)
    Object block;
{
    x_note_fn_call(180,151);
    return VALUES_1( 
	    !TRUEP(get_property_value_in_object_configuration(block,
	    Qstable_for_dependent_compilations,Nil)) ? T : Nil);
}

static Object Qoptimizable;        /* optimizable */

/* BLOCK-IS-OPTIMIZABLE-P */
Object block_is_optimizable_p(block)
    Object block;
{
    x_note_fn_call(180,152);
    return get_property_value_in_object_configuration(block,Qoptimizable,T);
}

/* BLOCK-HAS-STABLE-HEIRARCHY-P */
Object block_has_stable_heirarchy_p(block)
    Object block;
{
    x_note_fn_call(180,153);
    return get_property_value_in_object_configuration(block,
	    Qstable_hierarchy,Nil);
}

static Object Qinvisible_to_unsavable_change_protection;  /* invisible-to-unsavable-change-protection */

/* BLOCK-IS-INVISIBLE-TO-UNSAVABLE-CHANGE-PROTECTION-P */
Object block_is_invisible_to_unsavable_change_protection_p(block)
    Object block;
{
    x_note_fn_call(180,154);
    return get_property_value_in_object_configuration(block,
	    Qinvisible_to_unsavable_change_protection,Nil);
}

/* NO-MANUAL-CONNECTIONS-P */
Object no_manual_connections_p(object)
    Object object;
{
    x_note_fn_call(180,155);
    return VALUES_1( 
	    !TRUEP(get_property_value_in_object_configuration(object,
	    Qmanual_connections,T)) ? T : Nil);
}

static Object Qsubworkspace_connection_posts;  /* subworkspace-connection-posts */

/* SUBWORKSPACE-CONNECTION-POSTS-P */
Object subworkspace_connection_posts_p(object)
    Object object;
{
    x_note_fn_call(180,156);
    if ( !TRUEP(Disable_subworkspace_connection_posts))
	return get_property_value_in_object_configuration(object,
		Qsubworkspace_connection_posts,Nil);
    else
	return VALUES_1(Nil);
}

static Object list_constant_9;     /* # */

/* GRID-ALIGNMENT-CONSTRAINT-FOR-BLOCK */
Object grid_alignment_constraint_for_block(block)
    Object block;
{
    Object mode, proprietary_qm, traversing_class_hierarchy_qm;
    Object the_class_inheritance_path, original_item_or_class_description_qm;
    Object frame_with_modified_superior_qm, x2, class_description_qm, place;
    Object clauses, top_clause, ab_loop_list_, mode_clause, ab_loop_list__1;
    Object type, modes, clause, ab_loop_list__2, binding_qm, binding;
    Object pattern_element, ab_loop_list__3, clause_element, ab_loop_list__4;
    Object star_qm, temp_1, gensymed_symbol, dx, dy;
    Object the_class_inheritance_path_old_value, class_name, defn;
    char temp;

    x_note_fn_call(180,157);
    mode = BOUNDP(Qcurrent_g2_user_mode_qm) ? Current_g2_user_mode_qm : Nil;
    proprietary_qm = block ? in_order_p(block) : Qnil;
    traversing_class_hierarchy_qm = Nil;
    the_class_inheritance_path = Nil;
    original_item_or_class_description_qm = block;
    frame_with_modified_superior_qm = Superior_frame_for_restrictions_frame_qm;
    if (SIMPLE_VECTOR_P(original_item_or_class_description_qm) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(original_item_or_class_description_qm)) 
	    > (SI_Long)2L &&  
	    !EQ(ISVREF(original_item_or_class_description_qm,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(original_item_or_class_description_qm,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	class_description_qm = 
		ISVREF(original_item_or_class_description_qm,(SI_Long)1L);
    else if (SIMPLE_VECTOR_P(original_item_or_class_description_qm) && 
	    EQ(ISVREF(original_item_or_class_description_qm,(SI_Long)0L),
	    Qg2_defstruct_structure_name_class_description_g2_struct))
	class_description_qm = original_item_or_class_description_qm;
    else
	class_description_qm = Qnil;
    place = Nil;
    if (place);
    else {
	if (SIMPLE_VECTOR_P(original_item_or_class_description_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(original_item_or_class_description_qm)) 
		> (SI_Long)2L &&  
		!EQ(ISVREF(original_item_or_class_description_qm,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(original_item_or_class_description_qm,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	place = temp ? original_item_or_class_description_qm : Kb_restrictions;
    }
    clauses = Nil;
  next_loop:
    if ( !TRUEP(place))
	goto end_loop;
    if ( !TRUEP(traversing_class_hierarchy_qm))
	clauses = get_lookup_slot_value(place,Qobject_configuration);
    else {
	if (SIMPLE_VECTOR_P(place) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(place)) > (SI_Long)2L &&  
		!EQ(ISVREF(place,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(place,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if ( !temp)
	    clauses = Nil;
	else
	    clauses = ISVREF(place,(SI_Long)23L);
    }
    top_clause = Nil;
    ab_loop_list_ = clauses;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    top_clause = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (memq_function(FIRST(top_clause),list_constant_4)) {
	mode_clause = Nil;
	ab_loop_list__1 = CDR(top_clause);
      next_loop_2:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_2;
	mode_clause = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	temp =  !TRUEP(mode);
	if (temp);
	else {
	    type = FIRST(mode_clause);
	    modes = SECOND(mode_clause);
	    if (EQ(type,Qwhen))
		temp = TRUEP(memq_function(mode,modes));
	    else if (EQ(type,Qunless))
		temp =  !EQ(mode,Qadministrator) ?  
			!TRUEP(memq_function(mode,modes)) : TRUEP(Qnil);
	    else
		temp = TRUEP(Qnil);
	}
	if (temp) {
	    clause = Nil;
	    ab_loop_list__2 = CDDR(mode_clause);
	    binding_qm = Nil;
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list__2))
		goto end_loop_3;
	    clause = M_CAR(ab_loop_list__2);
	    ab_loop_list__2 = M_CDR(ab_loop_list__2);
	    binding = Nil;
	    if (FIXNUM_EQ(length(clause),length(list_constant_9))) {
		pattern_element = Nil;
		ab_loop_list__3 = list_constant_9;
		clause_element = Nil;
		ab_loop_list__4 = clause;
		star_qm = Nil;
	      next_loop_4:
		if ( !TRUEP(ab_loop_list__3))
		    goto end_loop_4;
		pattern_element = M_CAR(ab_loop_list__3);
		ab_loop_list__3 = M_CDR(ab_loop_list__3);
		if ( !TRUEP(ab_loop_list__4))
		    goto end_loop_4;
		clause_element = M_CAR(ab_loop_list__4);
		ab_loop_list__4 = M_CDR(ab_loop_list__4);
		star_qm = EQ(pattern_element,Qstar) ? T : Nil;
		if (star_qm)
		    binding = clause_element;
		if ( !(star_qm || EQUAL(pattern_element,clause_element))) {
		    temp = TRUEP(Nil);
		    goto end_1;
		}
		goto next_loop_4;
	      end_loop_4:
		temp = TRUEP(T);
		goto end_1;
		temp = TRUEP(Qnil);
	      end_1:;
	    }
	    else
		temp = TRUEP(Nil);
	    binding_qm = temp ? binding : Nil;
	    if (binding_qm) {
		temp_1 = FIRST(clause);
		if (EQ(temp_1,Qpressing) || EQ(temp_1,Qclicking))
		    temp_1 = FOURTH(clause);
		else if (EQ(temp_1,Qselecting) || EQ(temp_1,
			Qselecting_absolutely))
		    temp_1 = SECOND(clause);
		else if (EQ(temp_1,Qworkspace_menu))
		    temp_1 = SECOND(clause);
		else if (EQ(temp_1,Qtable))
		    temp_1 = SECOND(clause);
		else if (EQ(temp_1,Qnon_menu))
		    temp_1 = SECOND(clause);
		else if (EQ(temp_1,Qglobal_keyboard_command))
		    temp_1 = Nil;
		else if (EQ(temp_1,Qconstrain))
		    temp_1 = THIRD(clause);
		else
		    temp_1 = Qnil;
		temp = TRUEP(frame_matches_restriction_class_spec(block,
			temp_1,place));
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		gensymed_symbol = FOURTH(clause);
		dx = CAR(gensymed_symbol);
		dy = CDR(gensymed_symbol);
		return VALUES_2(dx,dy);
	    }
	    goto next_loop_3;
	  end_loop_3:;
	}
	goto next_loop_2;
      end_loop_2:;
    }
    else if (EQ(FIRST(top_clause),Qproprietary)) {
	temp = TRUEP(proprietary_qm);
	if (temp);
	else {
	    if (traversing_class_hierarchy_qm) {
		if (SIMPLE_VECTOR_P(place) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(place)) > 
			(SI_Long)2L &&  !EQ(ISVREF(place,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(place,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	    temp = temp ? TRUEP(in_order_p(place)) : TRUEP(Nil);
	}
	if (temp) {
	    clause = Nil;
	    ab_loop_list__1 = CDR(top_clause);
	    binding_qm = Nil;
	  next_loop_5:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_5;
	    clause = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    binding = Nil;
	    if (FIXNUM_EQ(length(clause),length(list_constant_9))) {
		pattern_element = Nil;
		ab_loop_list__2 = list_constant_9;
		clause_element = Nil;
		ab_loop_list__3 = clause;
		star_qm = Nil;
	      next_loop_6:
		if ( !TRUEP(ab_loop_list__2))
		    goto end_loop_6;
		pattern_element = M_CAR(ab_loop_list__2);
		ab_loop_list__2 = M_CDR(ab_loop_list__2);
		if ( !TRUEP(ab_loop_list__3))
		    goto end_loop_6;
		clause_element = M_CAR(ab_loop_list__3);
		ab_loop_list__3 = M_CDR(ab_loop_list__3);
		star_qm = EQ(pattern_element,Qstar) ? T : Nil;
		if (star_qm)
		    binding = clause_element;
		if ( !(star_qm || EQUAL(pattern_element,clause_element))) {
		    temp = TRUEP(Nil);
		    goto end_2;
		}
		goto next_loop_6;
	      end_loop_6:
		temp = TRUEP(T);
		goto end_2;
		temp = TRUEP(Qnil);
	      end_2:;
	    }
	    else
		temp = TRUEP(Nil);
	    binding_qm = temp ? binding : Nil;
	    if (binding_qm) {
		temp_1 = FIRST(clause);
		if (EQ(temp_1,Qpressing) || EQ(temp_1,Qclicking))
		    temp_1 = FOURTH(clause);
		else if (EQ(temp_1,Qselecting) || EQ(temp_1,
			Qselecting_absolutely))
		    temp_1 = SECOND(clause);
		else if (EQ(temp_1,Qworkspace_menu))
		    temp_1 = SECOND(clause);
		else if (EQ(temp_1,Qtable))
		    temp_1 = SECOND(clause);
		else if (EQ(temp_1,Qnon_menu))
		    temp_1 = SECOND(clause);
		else if (EQ(temp_1,Qglobal_keyboard_command))
		    temp_1 = Nil;
		else if (EQ(temp_1,Qconstrain))
		    temp_1 = THIRD(clause);
		else
		    temp_1 = Qnil;
		temp = TRUEP(frame_matches_restriction_class_spec(block,
			temp_1,place));
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		gensymed_symbol = FOURTH(clause);
		dx = CAR(gensymed_symbol);
		dy = CDR(gensymed_symbol);
		return VALUES_2(dx,dy);
	    }
	    goto next_loop_5;
	  end_loop_5:;
	}
    }
    goto next_loop_1;
  end_loop_1:;
    if (traversing_class_hierarchy_qm) {
	the_class_inheritance_path_old_value = the_class_inheritance_path;
	temp_1 = FIRST(the_class_inheritance_path_old_value);
	the_class_inheritance_path = 
		REST(the_class_inheritance_path_old_value);
	class_name = temp_1;
	defn = class_name &&  !EQ(class_name,Qitem) ? 
		lookup_global_or_kb_specific_property_value(class_name,
		Class_definition_gkbprop) : Qnil;
	place = CONSP(defn) ? class_name : defn;
    }
    else if (EQ(place,Kb_restrictions)) {
	if (class_description_qm) {
	    traversing_class_hierarchy_qm = T;
	    the_class_inheritance_path = ISVREF(class_description_qm,
		    (SI_Long)2L);
	    the_class_inheritance_path_old_value = the_class_inheritance_path;
	    temp_1 = FIRST(the_class_inheritance_path_old_value);
	    the_class_inheritance_path = 
		    REST(the_class_inheritance_path_old_value);
	    class_name = temp_1;
	    defn = class_name ? 
		    lookup_global_or_kb_specific_property_value(class_name,
		    Class_definition_gkbprop) : Qnil;
	    place = CONSP(defn) ? class_name : defn;
	}
	else
	    place = Nil;
    }
    else if (EQ(place,frame_with_modified_superior_qm)) {
	frame_with_modified_superior_qm = Nil;
	place = Superior_frame_for_restrictions_superior_qm;
    }
    else {
	place = superior_frame(place);
	if (place);
	else
	    place = Kb_restrictions;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object list_constant_10;    /* # */

/* MOVEMENT-LIMITS-FOR-BLOCK */
Object movement_limits_for_block(block)
    Object block;
{
    Object mode, proprietary_qm, traversing_class_hierarchy_qm;
    Object the_class_inheritance_path, original_item_or_class_description_qm;
    Object frame_with_modified_superior_qm, x2, class_description_qm, place;
    Object clauses, top_clause, ab_loop_list_, mode_clause, ab_loop_list__1;
    Object type, modes, clause, ab_loop_list__2, binding_qm, binding;
    Object pattern_element, ab_loop_list__3, clause_element, ab_loop_list__4;
    Object star_qm, temp_1, gensymed_symbol, left, right, bottom, top, temp_2;
    Object the_class_inheritance_path_old_value, class_name, defn;
    char temp;

    x_note_fn_call(180,158);
    mode = BOUNDP(Qcurrent_g2_user_mode_qm) ? Current_g2_user_mode_qm : Nil;
    proprietary_qm = block ? in_order_p(block) : Qnil;
    traversing_class_hierarchy_qm = Nil;
    the_class_inheritance_path = Nil;
    original_item_or_class_description_qm = block;
    frame_with_modified_superior_qm = Superior_frame_for_restrictions_frame_qm;
    if (SIMPLE_VECTOR_P(original_item_or_class_description_qm) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(original_item_or_class_description_qm)) 
	    > (SI_Long)2L &&  
	    !EQ(ISVREF(original_item_or_class_description_qm,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(original_item_or_class_description_qm,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	class_description_qm = 
		ISVREF(original_item_or_class_description_qm,(SI_Long)1L);
    else if (SIMPLE_VECTOR_P(original_item_or_class_description_qm) && 
	    EQ(ISVREF(original_item_or_class_description_qm,(SI_Long)0L),
	    Qg2_defstruct_structure_name_class_description_g2_struct))
	class_description_qm = original_item_or_class_description_qm;
    else
	class_description_qm = Qnil;
    place = Nil;
    if (place);
    else {
	if (SIMPLE_VECTOR_P(original_item_or_class_description_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(original_item_or_class_description_qm)) 
		> (SI_Long)2L &&  
		!EQ(ISVREF(original_item_or_class_description_qm,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(original_item_or_class_description_qm,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	place = temp ? original_item_or_class_description_qm : Kb_restrictions;
    }
    clauses = Nil;
  next_loop:
    if ( !TRUEP(place))
	goto end_loop;
    if ( !TRUEP(traversing_class_hierarchy_qm))
	clauses = get_lookup_slot_value(place,Qobject_configuration);
    else {
	if (SIMPLE_VECTOR_P(place) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(place)) > (SI_Long)2L &&  
		!EQ(ISVREF(place,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(place,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if ( !temp)
	    clauses = Nil;
	else
	    clauses = ISVREF(place,(SI_Long)23L);
    }
    top_clause = Nil;
    ab_loop_list_ = clauses;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    top_clause = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (memq_function(FIRST(top_clause),list_constant_4)) {
	mode_clause = Nil;
	ab_loop_list__1 = CDR(top_clause);
      next_loop_2:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_2;
	mode_clause = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	temp =  !TRUEP(mode);
	if (temp);
	else {
	    type = FIRST(mode_clause);
	    modes = SECOND(mode_clause);
	    if (EQ(type,Qwhen))
		temp = TRUEP(memq_function(mode,modes));
	    else if (EQ(type,Qunless))
		temp =  !EQ(mode,Qadministrator) ?  
			!TRUEP(memq_function(mode,modes)) : TRUEP(Qnil);
	    else
		temp = TRUEP(Qnil);
	}
	if (temp) {
	    clause = Nil;
	    ab_loop_list__2 = CDDR(mode_clause);
	    binding_qm = Nil;
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list__2))
		goto end_loop_3;
	    clause = M_CAR(ab_loop_list__2);
	    ab_loop_list__2 = M_CDR(ab_loop_list__2);
	    binding = Nil;
	    if (FIXNUM_EQ(length(clause),length(list_constant_10))) {
		pattern_element = Nil;
		ab_loop_list__3 = list_constant_10;
		clause_element = Nil;
		ab_loop_list__4 = clause;
		star_qm = Nil;
	      next_loop_4:
		if ( !TRUEP(ab_loop_list__3))
		    goto end_loop_4;
		pattern_element = M_CAR(ab_loop_list__3);
		ab_loop_list__3 = M_CDR(ab_loop_list__3);
		if ( !TRUEP(ab_loop_list__4))
		    goto end_loop_4;
		clause_element = M_CAR(ab_loop_list__4);
		ab_loop_list__4 = M_CDR(ab_loop_list__4);
		star_qm = EQ(pattern_element,Qstar) ? T : Nil;
		if (star_qm)
		    binding = clause_element;
		if ( !(star_qm || EQUAL(pattern_element,clause_element))) {
		    temp = TRUEP(Nil);
		    goto end_1;
		}
		goto next_loop_4;
	      end_loop_4:
		temp = TRUEP(T);
		goto end_1;
		temp = TRUEP(Qnil);
	      end_1:;
	    }
	    else
		temp = TRUEP(Nil);
	    binding_qm = temp ? binding : Nil;
	    if (binding_qm) {
		temp_1 = FIRST(clause);
		if (EQ(temp_1,Qpressing) || EQ(temp_1,Qclicking))
		    temp_1 = FOURTH(clause);
		else if (EQ(temp_1,Qselecting) || EQ(temp_1,
			Qselecting_absolutely))
		    temp_1 = SECOND(clause);
		else if (EQ(temp_1,Qworkspace_menu))
		    temp_1 = SECOND(clause);
		else if (EQ(temp_1,Qtable))
		    temp_1 = SECOND(clause);
		else if (EQ(temp_1,Qnon_menu))
		    temp_1 = SECOND(clause);
		else if (EQ(temp_1,Qglobal_keyboard_command))
		    temp_1 = Nil;
		else if (EQ(temp_1,Qconstrain))
		    temp_1 = THIRD(clause);
		else
		    temp_1 = Qnil;
		temp = TRUEP(frame_matches_restriction_class_spec(block,
			temp_1,place));
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		gensymed_symbol = FOURTH(clause);
		left = CAR(gensymed_symbol);
		gensymed_symbol = CDR(gensymed_symbol);
		right = CAR(gensymed_symbol);
		gensymed_symbol = CDR(gensymed_symbol);
		bottom = CAR(gensymed_symbol);
		gensymed_symbol = CDR(gensymed_symbol);
		top = CAR(gensymed_symbol);
		temp_2 = FIXNUM_NEGATE(top);
		temp_1 = FIXNUM_NEGATE(bottom);
		return VALUES_4(left,temp_2,right,temp_1);
	    }
	    goto next_loop_3;
	  end_loop_3:;
	}
	goto next_loop_2;
      end_loop_2:;
    }
    else if (EQ(FIRST(top_clause),Qproprietary)) {
	temp = TRUEP(proprietary_qm);
	if (temp);
	else {
	    if (traversing_class_hierarchy_qm) {
		if (SIMPLE_VECTOR_P(place) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(place)) > 
			(SI_Long)2L &&  !EQ(ISVREF(place,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(place,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	    temp = temp ? TRUEP(in_order_p(place)) : TRUEP(Nil);
	}
	if (temp) {
	    clause = Nil;
	    ab_loop_list__1 = CDR(top_clause);
	    binding_qm = Nil;
	  next_loop_5:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_5;
	    clause = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    binding = Nil;
	    if (FIXNUM_EQ(length(clause),length(list_constant_10))) {
		pattern_element = Nil;
		ab_loop_list__2 = list_constant_10;
		clause_element = Nil;
		ab_loop_list__3 = clause;
		star_qm = Nil;
	      next_loop_6:
		if ( !TRUEP(ab_loop_list__2))
		    goto end_loop_6;
		pattern_element = M_CAR(ab_loop_list__2);
		ab_loop_list__2 = M_CDR(ab_loop_list__2);
		if ( !TRUEP(ab_loop_list__3))
		    goto end_loop_6;
		clause_element = M_CAR(ab_loop_list__3);
		ab_loop_list__3 = M_CDR(ab_loop_list__3);
		star_qm = EQ(pattern_element,Qstar) ? T : Nil;
		if (star_qm)
		    binding = clause_element;
		if ( !(star_qm || EQUAL(pattern_element,clause_element))) {
		    temp = TRUEP(Nil);
		    goto end_2;
		}
		goto next_loop_6;
	      end_loop_6:
		temp = TRUEP(T);
		goto end_2;
		temp = TRUEP(Qnil);
	      end_2:;
	    }
	    else
		temp = TRUEP(Nil);
	    binding_qm = temp ? binding : Nil;
	    if (binding_qm) {
		temp_1 = FIRST(clause);
		if (EQ(temp_1,Qpressing) || EQ(temp_1,Qclicking))
		    temp_1 = FOURTH(clause);
		else if (EQ(temp_1,Qselecting) || EQ(temp_1,
			Qselecting_absolutely))
		    temp_1 = SECOND(clause);
		else if (EQ(temp_1,Qworkspace_menu))
		    temp_1 = SECOND(clause);
		else if (EQ(temp_1,Qtable))
		    temp_1 = SECOND(clause);
		else if (EQ(temp_1,Qnon_menu))
		    temp_1 = SECOND(clause);
		else if (EQ(temp_1,Qglobal_keyboard_command))
		    temp_1 = Nil;
		else if (EQ(temp_1,Qconstrain))
		    temp_1 = THIRD(clause);
		else
		    temp_1 = Qnil;
		temp = TRUEP(frame_matches_restriction_class_spec(block,
			temp_1,place));
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		gensymed_symbol = FOURTH(clause);
		left = CAR(gensymed_symbol);
		gensymed_symbol = CDR(gensymed_symbol);
		right = CAR(gensymed_symbol);
		gensymed_symbol = CDR(gensymed_symbol);
		bottom = CAR(gensymed_symbol);
		gensymed_symbol = CDR(gensymed_symbol);
		top = CAR(gensymed_symbol);
		temp_2 = FIXNUM_NEGATE(top);
		temp_1 = FIXNUM_NEGATE(bottom);
		return VALUES_4(left,temp_2,right,temp_1);
	    }
	    goto next_loop_5;
	  end_loop_5:;
	}
    }
    goto next_loop_1;
  end_loop_1:;
    if (traversing_class_hierarchy_qm) {
	the_class_inheritance_path_old_value = the_class_inheritance_path;
	temp_1 = FIRST(the_class_inheritance_path_old_value);
	the_class_inheritance_path = 
		REST(the_class_inheritance_path_old_value);
	class_name = temp_1;
	defn = class_name &&  !EQ(class_name,Qitem) ? 
		lookup_global_or_kb_specific_property_value(class_name,
		Class_definition_gkbprop) : Qnil;
	place = CONSP(defn) ? class_name : defn;
    }
    else if (EQ(place,Kb_restrictions)) {
	if (class_description_qm) {
	    traversing_class_hierarchy_qm = T;
	    the_class_inheritance_path = ISVREF(class_description_qm,
		    (SI_Long)2L);
	    the_class_inheritance_path_old_value = the_class_inheritance_path;
	    temp_1 = FIRST(the_class_inheritance_path_old_value);
	    the_class_inheritance_path = 
		    REST(the_class_inheritance_path_old_value);
	    class_name = temp_1;
	    defn = class_name ? 
		    lookup_global_or_kb_specific_property_value(class_name,
		    Class_definition_gkbprop) : Qnil;
	    place = CONSP(defn) ? class_name : defn;
	}
	else
	    place = Nil;
    }
    else if (EQ(place,frame_with_modified_superior_qm)) {
	frame_with_modified_superior_qm = Nil;
	place = Superior_frame_for_restrictions_superior_qm;
    }
    else {
	place = superior_frame(place);
	if (place);
	else
	    place = Kb_restrictions;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* COMPUTE-SNAP-GRID-FOR-BLOCK */
Object compute_snap_grid_for_block varargs_1(int, n)
{
    Object block;
    Object prospective_workspace_of_block_qm, x_step_qm, y_step_qm;
    Object workspace_qm, gensymed_symbol, frame, symbol, sub_class_bit_vector;
    Object superior_frame_for_restrictions_frame_qm;
    Object superior_frame_for_restrictions_superior_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_varargs_nonrelocating;
    Declare_special(2);
    Object result;

    x_note_fn_call(180,159);
    INIT_ARGS_nonrelocating();
    block = REQUIRED_ARG_nonrelocating();
    prospective_workspace_of_block_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    x_step_qm = Nil;
    y_step_qm = Nil;
    workspace_qm = prospective_workspace_of_block_qm;
    if (workspace_qm);
    else {
	gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	if (gensymed_symbol) {
	    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	    frame = gensymed_symbol;
	    symbol = Qworkspace;
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(symbol,
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
	if (temp) {
	    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	    workspace_qm = gensymed_symbol;
	}
	else
	    workspace_qm = Nil;
    }
    if (workspace_qm) {
	superior_frame_for_restrictions_frame_qm = block;
	superior_frame_for_restrictions_superior_qm = workspace_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Superior_frame_for_restrictions_superior_qm,Qsuperior_frame_for_restrictions_superior_qm,superior_frame_for_restrictions_superior_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Superior_frame_for_restrictions_frame_qm,Qsuperior_frame_for_restrictions_frame_qm,superior_frame_for_restrictions_frame_qm,
		  0);
	    result = grid_alignment_constraint_for_block(block);
	    MVS_2(result,x_step_qm,y_step_qm);
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if ( !(x_step_qm || y_step_qm)) {
	result = get_global_snap_grid();
	MVS_2(result,x_step_qm,y_step_qm);
    }
    return VALUES_2(x_step_qm,y_step_qm);
}

/* COMPUTE-NEW-RESTRICTION-SET */
Object compute_new_restriction_set(old_set,additions,complement_set_1,
	    complement_set_2)
    Object old_set, additions, complement_set_1, complement_set_2;
{
    Object element, ab_loop_list_, new_stuff, ab_loopvar_, ab_loopvar__1, temp;

    x_note_fn_call(180,160);
    element = Nil;
    ab_loop_list_ = additions;
    new_stuff = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !(memq_function(element,complement_set_1) || 
	    memq_function(element,complement_set_2) || 
	    memq_function(element,old_set))) {
	ab_loopvar__1 = filter_cons_1(element,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    new_stuff = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
    }
    goto next_loop;
  end_loop:
    temp = nconc2(old_set,new_stuff);
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* REMOVE-FROM-RESTRICTION-SET */
Object remove_from_restriction_set(set_1,removals)
    Object set_1, removals;
{
    Object element, ab_loop_list_, temp;

    x_note_fn_call(180,161);
    element = Nil;
    ab_loop_list_ = removals;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    set_1 = delete_filter_element_1(element,set_1);
    goto next_loop;
  end_loop:
    temp = set_1;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* G2-XOR */
Object g2_xor(x,y)
    Object x, y;
{
    x_note_fn_call(180,162);
    if (x)
	return VALUES_1( !TRUEP(y) ? T : Nil);
    else
	return VALUES_1(y);
}

/* G2-EQUIV */
Object g2_equiv(x,y)
    Object x, y;
{
    x_note_fn_call(180,163);
    if (x)
	return VALUES_1(y);
    else
	return VALUES_1( !TRUEP(y) ? T : Nil);
}

/* G2-SET-EQUIVALENT */
Object g2_set_equivalent(s1_1,s2_1)
    Object s1_1, s2_1;
{
    x_note_fn_call(180,164);
    if (g2_subset(s1_1,s2_1))
	return g2_subset(s2_1,s1_1);
    else
	return VALUES_1(Nil);
}

/* G2-SUBSET */
Object g2_subset(small_set,large_set)
    Object small_set, large_set;
{
    Object elt_1, ab_loop_list_;

    x_note_fn_call(180,165);
    elt_1 = Nil;
    ab_loop_list_ = small_set;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    elt_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(memq_function(elt_1,large_set)))
	return VALUES_1(Nil);
    goto next_loop;
  end_loop:
    return VALUES_1(T);
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Permitted_restriction_set, Qpermitted_restriction_set);

DEFINE_VARIABLE_WITH_SYMBOL(Prohibited_restriction_set, Qprohibited_restriction_set);

DEFINE_VARIABLE_WITH_SYMBOL(Absolutely_prohibited_restriction_set, Qabsolutely_prohibited_restriction_set);

DEFINE_VARIABLE_WITH_SYMBOL(Absolutely_selected_choice_qm, Qabsolutely_selected_choice_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Conditional_selected_choice_qm, Qconditional_selected_choice_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Conditional_termination_state_qm, Qconditional_termination_state_qm);

/* RECLAIM-PERMITTED-RESTRICTION-SET */
Object reclaim_permitted_restriction_set()
{
    x_note_fn_call(180,166);
    reclaim_filter_list_1(Permitted_restriction_set);
    Permitted_restriction_set = Nil;
    return VALUES_1(Permitted_restriction_set);
}

/* RECLAIM-PROHIBITED-RESTRICTION-SET */
Object reclaim_prohibited_restriction_set()
{
    x_note_fn_call(180,167);
    reclaim_filter_list_1(Prohibited_restriction_set);
    Prohibited_restriction_set = Nil;
    return VALUES_1(Prohibited_restriction_set);
}

/* RECLAIM-ABSOLUTELY-PROHIBITED-RESTRICTION-SET */
Object reclaim_absolutely_prohibited_restriction_set()
{
    x_note_fn_call(180,168);
    reclaim_filter_list_1(Absolutely_prohibited_restriction_set);
    Absolutely_prohibited_restriction_set = Nil;
    return VALUES_1(Absolutely_prohibited_restriction_set);
}

static Object Qpermitted;          /* permitted */

static Object Qprohibited;         /* prohibited */

/* FILTER-NEW-RESTRICTION-SET */
Object filter_new_restriction_set(restriction_type,additions)
    Object restriction_type, additions;
{
    x_note_fn_call(180,169);
    if (EQ(restriction_type,Qinclude) || EQ(restriction_type,
	    Qinclude_additionally)) {
	Permitted_restriction_set = 
		compute_new_restriction_set(Permitted_restriction_set,
		additions,Prohibited_restriction_set,
		Absolutely_prohibited_restriction_set);
	if (EQ(restriction_type,Qinclude))
	    Conditional_termination_state_qm = Qpermitted;
    }
    else if (EQ(restriction_type,Qexclude) || EQ(restriction_type,
	    Qexclude_additionally)) {
	Prohibited_restriction_set = 
		compute_new_restriction_set(Prohibited_restriction_set,
		additions,Permitted_restriction_set,Nil);
	if (EQ(restriction_type,Qexclude))
	    Conditional_termination_state_qm = Qprohibited;
    }
    else if (EQ(restriction_type,Qexclude_absolutely)) {
	Absolutely_prohibited_restriction_set = 
		compute_new_restriction_set(Absolutely_prohibited_restriction_set,
		additions,Nil,Nil);
	Permitted_restriction_set = 
		remove_from_restriction_set(Permitted_restriction_set,
		additions);
	Prohibited_restriction_set = 
		compute_new_restriction_set(Prohibited_restriction_set,
		additions,Permitted_restriction_set,Nil);
    }
    return VALUES_1(Nil);
}

static Object list_constant_11;    /* # */

static Object list_constant_12;    /* # */

static Object list_constant_13;    /* # */

/* NETWORK-ACCESS-ALLOWED-P */
Object network_access_allowed_p varargs_1(int, n)
{
    Object access_agent, access_type;
    Object frame_qm, access_allowed_qm, already_found_a_clause_qm;
    Object traversing_class_hierarchy_qm, the_class_inheritance_path;
    Object original_item_or_class_description_qm;
    Object frame_with_modified_superior_qm, x2, class_description_qm, place;
    Object object_configuration, annotation, ab_loop_list_, network_clause;
    Object ab_loop_list__1, access_agents, class_spec, inclexcl, access_types;
    Object temp_1, temp_2, the_class_inheritance_path_old_value, class_name;
    Object defn;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(180,170);
    INIT_ARGS_nonrelocating();
    access_agent = REQUIRED_ARG_nonrelocating();
    access_type = REQUIRED_ARG_nonrelocating();
    frame_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    access_allowed_qm = T;
    already_found_a_clause_qm = Nil;
    traversing_class_hierarchy_qm = Nil;
    the_class_inheritance_path = Nil;
    original_item_or_class_description_qm = frame_qm;
    frame_with_modified_superior_qm = Superior_frame_for_restrictions_frame_qm;
    if (SIMPLE_VECTOR_P(original_item_or_class_description_qm) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(original_item_or_class_description_qm)) 
	    > (SI_Long)2L &&  
	    !EQ(ISVREF(original_item_or_class_description_qm,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(original_item_or_class_description_qm,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	class_description_qm = 
		ISVREF(original_item_or_class_description_qm,(SI_Long)1L);
    else if (SIMPLE_VECTOR_P(original_item_or_class_description_qm) && 
	    EQ(ISVREF(original_item_or_class_description_qm,(SI_Long)0L),
	    Qg2_defstruct_structure_name_class_description_g2_struct))
	class_description_qm = original_item_or_class_description_qm;
    else
	class_description_qm = Qnil;
    place = Nil;
    if (place);
    else {
	if (SIMPLE_VECTOR_P(original_item_or_class_description_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(original_item_or_class_description_qm)) 
		> (SI_Long)2L &&  
		!EQ(ISVREF(original_item_or_class_description_qm,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(original_item_or_class_description_qm,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	place = temp ? original_item_or_class_description_qm : Kb_restrictions;
    }
    object_configuration = Nil;
  next_loop:
    if ( !TRUEP(place))
	goto end_loop;
    if ( !TRUEP(traversing_class_hierarchy_qm))
	object_configuration = get_lookup_slot_value(place,
		Qobject_configuration);
    else {
	if (SIMPLE_VECTOR_P(place) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(place)) > (SI_Long)2L &&  
		!EQ(ISVREF(place,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(place,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if ( !temp)
	    object_configuration = Nil;
	else
	    object_configuration = ISVREF(place,(SI_Long)23L);
    }
    annotation = Nil;
    ab_loop_list_ = object_configuration;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    annotation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(FIRST(annotation),Qnetwork_access)) {
	network_clause = Nil;
	ab_loop_list__1 = CDR(annotation);
	access_agents = Nil;
	class_spec = Nil;
	inclexcl = Nil;
	access_types = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_2;
	network_clause = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	access_agents = FIRST(network_clause);
	class_spec = SECOND(network_clause);
	inclexcl = THIRD(network_clause);
	access_types = FOURTH(network_clause);
	if (frame_matches_restriction_class_spec(frame_qm,class_spec,place)) {
	    temp_1 = access_agents;
	    if (EQ(access_agent,Qgsi))
		temp_2 = list_constant_11;
	    else if (EQ(access_agent,Qg2))
		temp_2 = list_constant_12;
	    else if (EQ(access_agent,Qtelewindows))
		temp_2 = list_constant_13;
	    else
		temp_2 = Nil;
	    temp = TRUEP(memq_function(temp_1,temp_2));
	}
	else
	    temp = TRUEP(Nil);
	if (temp ?  !TRUEP(access_types) || memq_function(access_type,
		access_types) : TRUEP(Nil)) {
	    if (EQ(inclexcl,Qinclude_additionally)) {
		if ( !TRUEP(already_found_a_clause_qm))
		    access_allowed_qm = T;
	    }
	    else if (EQ(inclexcl,Qexclude_additionally)) {
		if ( !TRUEP(already_found_a_clause_qm))
		    access_allowed_qm = Nil;
	    }
	    else if (EQ(inclexcl,Qexclude_absolutely)) {
		access_allowed_qm = Nil;
		goto end_standard_search;
	    }
	    already_found_a_clause_qm = T;
	}
	goto next_loop_2;
      end_loop_2:;
    }
    goto next_loop_1;
  end_loop_1:;
    if (traversing_class_hierarchy_qm) {
	the_class_inheritance_path_old_value = the_class_inheritance_path;
	temp_1 = FIRST(the_class_inheritance_path_old_value);
	the_class_inheritance_path = 
		REST(the_class_inheritance_path_old_value);
	class_name = temp_1;
	defn = class_name &&  !EQ(class_name,Qitem) ? 
		lookup_global_or_kb_specific_property_value(class_name,
		Class_definition_gkbprop) : Qnil;
	place = CONSP(defn) ? class_name : defn;
    }
    else if (EQ(place,Kb_restrictions)) {
	if (class_description_qm) {
	    traversing_class_hierarchy_qm = T;
	    the_class_inheritance_path = ISVREF(class_description_qm,
		    (SI_Long)2L);
	    the_class_inheritance_path_old_value = the_class_inheritance_path;
	    temp_1 = FIRST(the_class_inheritance_path_old_value);
	    the_class_inheritance_path = 
		    REST(the_class_inheritance_path_old_value);
	    class_name = temp_1;
	    defn = class_name ? 
		    lookup_global_or_kb_specific_property_value(class_name,
		    Class_definition_gkbprop) : Qnil;
	    place = CONSP(defn) ? class_name : defn;
	}
	else
	    place = Nil;
    }
    else if (EQ(place,frame_with_modified_superior_qm)) {
	frame_with_modified_superior_qm = Nil;
	place = Superior_frame_for_restrictions_superior_qm;
    }
    else {
	place = superior_frame(place);
	if (place);
	else
	    place = Kb_restrictions;
    }
    goto next_loop;
  end_loop:;
  end_standard_search:
    return VALUES_1(access_allowed_qm);
}

/* COMPUTE-MAIN-MENU-RESTRICTIONS */
Object compute_main_menu_restrictions()
{
    x_note_fn_call(180,171);
    return compute_user_restrictions_in_kb_restrictions(get_lookup_slot_value_given_default(Kb_restrictions,
	    Qmain_menu_user_restrictions,Nil));
}

/* MAIN-MENU-COMMAND-PERMITTED-P */
Object main_menu_command_permitted_p(command_name)
    Object command_name;
{
    Object restrictions, permitted_qm, temp;
    Object result;

    x_note_fn_call(180,172);
    result = compute_main_menu_restrictions();
    MVS_2(result,restrictions,permitted_qm);
    temp = memq_function(command_name,restrictions) ? permitted_qm :  
	    !TRUEP(permitted_qm) ? T : Nil;
    reclaim_filter_list_function(restrictions);
    return VALUES_1(temp);
}

/* COMPUTE-GLOBAL-KEYBOARD-RESTRICTIONS */
Object compute_global_keyboard_restrictions()
{
    x_note_fn_call(180,173);
    return compute_user_restrictions_in_kb_restrictions(get_lookup_slot_value_given_default(Kb_restrictions,
	    Qglobal_keyboard_command_user_restrictions,Nil));
}

/* GLOBAL-KEYBOARD-COMMAND-PERMITTED-P */
Object global_keyboard_command_permitted_p(command_name)
    Object command_name;
{
    Object restrictions, permitted_qm, temp;
    Object result;

    x_note_fn_call(180,174);
    result = compute_global_keyboard_restrictions();
    MVS_2(result,restrictions,permitted_qm);
    temp = memq_function(command_name,restrictions) ? permitted_qm :  
	    !TRUEP(permitted_qm) ? T : Nil;
    reclaim_filter_list_function(restrictions);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Choice_conflict, Qchoice_conflict);

static Object list_constant_14;    /* # */

static Object Qfilter_workspace_menu_restriction;  /* filter-workspace-menu-restriction */

/* COMPUTE-MENU-RESTRICTIONS-FOR-CLICK-ON-WORKSPACE */
Object compute_menu_restrictions_for_click_on_workspace(item)
    Object item;
{
    Object permitted_restriction_set, prohibited_restriction_set;
    Object absolutely_prohibited_restriction_set;
    Object absolutely_selected_choice_qm, conditional_selected_choice_qm;
    Object conditional_termination_state_qm;
    Declare_special(6);
    Object result;

    x_note_fn_call(180,175);
    permitted_restriction_set = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Permitted_restriction_set,Qpermitted_restriction_set,permitted_restriction_set,
	    5);
      prohibited_restriction_set = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Prohibited_restriction_set,Qprohibited_restriction_set,prohibited_restriction_set,
	      4);
	absolutely_prohibited_restriction_set = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Absolutely_prohibited_restriction_set,Qabsolutely_prohibited_restriction_set,absolutely_prohibited_restriction_set,
		3);
	  absolutely_selected_choice_qm = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Absolutely_selected_choice_qm,Qabsolutely_selected_choice_qm,absolutely_selected_choice_qm,
		  2);
	    conditional_selected_choice_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Conditional_selected_choice_qm,Qconditional_selected_choice_qm,conditional_selected_choice_qm,
		    1);
	      conditional_termination_state_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Conditional_termination_state_qm,Qconditional_termination_state_qm,conditional_termination_state_qm,
		      0);
		result = filter_restrictions_for_item(item,
			list_constant_14,
			SYMBOL_FUNCTION(Qfilter_workspace_menu_restriction),
			Nil);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object list_constant_15;    /* # */

/* COMPUTE-MENU-RESTRICTIONS-FOR-WORKSPACE */
Object compute_menu_restrictions_for_workspace(item)
    Object item;
{
    Object permitted_restriction_set, prohibited_restriction_set;
    Object absolutely_prohibited_restriction_set;
    Object absolutely_selected_choice_qm, conditional_selected_choice_qm;
    Object conditional_termination_state_qm;
    Declare_special(6);
    Object result;

    x_note_fn_call(180,176);
    permitted_restriction_set = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Permitted_restriction_set,Qpermitted_restriction_set,permitted_restriction_set,
	    5);
      prohibited_restriction_set = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Prohibited_restriction_set,Qprohibited_restriction_set,prohibited_restriction_set,
	      4);
	absolutely_prohibited_restriction_set = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Absolutely_prohibited_restriction_set,Qabsolutely_prohibited_restriction_set,absolutely_prohibited_restriction_set,
		3);
	  absolutely_selected_choice_qm = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Absolutely_selected_choice_qm,Qabsolutely_selected_choice_qm,absolutely_selected_choice_qm,
		  2);
	    conditional_selected_choice_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Conditional_selected_choice_qm,Qconditional_selected_choice_qm,conditional_selected_choice_qm,
		    1);
	      conditional_termination_state_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Conditional_termination_state_qm,Qconditional_termination_state_qm,conditional_termination_state_qm,
		      0);
		result = filter_restrictions_for_item(item,
			list_constant_15,
			SYMBOL_FUNCTION(Qfilter_workspace_menu_restriction),
			Nil);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* ITEM-MENU-COMMAND-PERMITTED-P */
Object item_menu_command_permitted_p(command_name,item)
    Object command_name, item;
{
    Object restrictions, permitted_qm, temp;
    Object result;

    x_note_fn_call(180,177);
    result = compute_menu_restrictions_for_workspace(item);
    MVS_2(result,restrictions,permitted_qm);
    temp = memq_function(command_name,restrictions) ? permitted_qm :  
	    !TRUEP(permitted_qm) ? T : Nil;
    reclaim_filter_list_function(restrictions);
    return VALUES_1(temp);
}

/* FILTER-WORKSPACE-MENU-RESTRICTION */
Object filter_workspace_menu_restriction(restriction_clause,item,current_item)
    Object restriction_clause, item, current_item;
{
    Object activity_type;

    x_note_fn_call(180,178);
    if (frame_matches_restriction_class_spec(item,
	    SECOND(restriction_clause),current_item)) {
	activity_type = FIRST(restriction_clause);
	if (EQ(activity_type,Qworkspace_menu))
	    filter_new_restriction_set(THIRD(restriction_clause),
		    CDDDR(restriction_clause));
	else if (EQ(activity_type,Qselecting))
	    Conditional_selected_choice_qm = THIRD(restriction_clause);
	else if (EQ(activity_type,Qselecting_absolutely))
	    Absolutely_selected_choice_qm = Absolutely_selected_choice_qm ?
		     Choice_conflict : THIRD(restriction_clause);
    }
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Exact_class_names_for_menu_restrictions, Qexact_class_names_for_menu_restrictions);

/* FILTER-MENU-RESTRICTION-FOR-KB */
Object filter_menu_restriction_for_kb(restriction_clause,item,current_item)
    Object restriction_clause, item, current_item;
{
    Object class_spec_qm, temp, class_name, ab_loop_list_, ab_loop_it_;

    x_note_fn_call(180,179);
    if (EQ(FIRST(restriction_clause),Qworkspace_menu)) {
	class_spec_qm = SECOND(restriction_clause);
	if ( !TRUEP(class_spec_qm))
	    temp = T;
	else if (memq_function(class_spec_qm,
		Exact_class_names_for_menu_restrictions))
	    temp = T;
	else if (ATOM(class_spec_qm))
	    temp = Nil;
	else {
	    class_name = Nil;
	    ab_loop_list_ = Exact_class_names_for_menu_restrictions;
	    ab_loop_it_ = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    class_name = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = memq_function(class_name,class_spec_qm);
	    if (ab_loop_it_) {
		temp = ab_loop_it_;
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    temp = Qnil;
	  end_1:;
	}
	if (temp)
	    filter_new_restriction_set(THIRD(restriction_clause),
		    CDDDR(restriction_clause));
    }
    return VALUES_1(Nil);
}

static Object Qglobal_keyboard;    /* global-keyboard */

static Object Qitem_menu;          /* item-menu */

static Object list_constant_16;    /* # */

static Object list_constant_17;    /* # */

static Object Qfilter_menu_restriction_for_kb;  /* filter-menu-restriction-for-kb */

/* COMPUTE-RESTRICTIONS-OF-TYPE */
Object compute_restrictions_of_type varargs_1(int, n)
{
    Object type;
    Object frame_qm, exact_class_names_for_menu_restrictions;
    Object permitted_restriction_set, prohibited_restriction_set;
    Object absolutely_prohibited_restriction_set;
    Object absolutely_selected_choice_qm, conditional_selected_choice_qm;
    Object conditional_termination_state_qm;
    Declare_varargs_nonrelocating;
    Declare_special(7);
    Object result;

    x_note_fn_call(180,180);
    INIT_ARGS_nonrelocating();
    type = REQUIRED_ARG_nonrelocating();
    frame_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (EQ(type,Qmain_menu))
	return compute_main_menu_restrictions();
    else if (EQ(type,Qglobal_keyboard))
	return compute_global_keyboard_restrictions();
    else if (EQ(type,Qworkspace_menu) || EQ(type,Qitem_menu)) {
	if (frame_qm)
	    return compute_menu_restrictions_for_workspace(frame_qm);
	else {
	    if (EQ(type,Qworkspace_menu))
		exact_class_names_for_menu_restrictions = list_constant_16;
	    else if (EQ(type,Qitem_menu))
		exact_class_names_for_menu_restrictions = list_constant_17;
	    else
		exact_class_names_for_menu_restrictions = Qnil;
	    PUSH_SPECIAL_WITH_SYMBOL(Exact_class_names_for_menu_restrictions,Qexact_class_names_for_menu_restrictions,exact_class_names_for_menu_restrictions,
		    6);
	      permitted_restriction_set = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Permitted_restriction_set,Qpermitted_restriction_set,permitted_restriction_set,
		      5);
		prohibited_restriction_set = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Prohibited_restriction_set,Qprohibited_restriction_set,prohibited_restriction_set,
			4);
		  absolutely_prohibited_restriction_set = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Absolutely_prohibited_restriction_set,Qabsolutely_prohibited_restriction_set,absolutely_prohibited_restriction_set,
			  3);
		    absolutely_selected_choice_qm = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Absolutely_selected_choice_qm,Qabsolutely_selected_choice_qm,absolutely_selected_choice_qm,
			    2);
		      conditional_selected_choice_qm = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Conditional_selected_choice_qm,Qconditional_selected_choice_qm,conditional_selected_choice_qm,
			      1);
			conditional_termination_state_qm = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Conditional_termination_state_qm,Qconditional_termination_state_qm,conditional_termination_state_qm,
				0);
			  result = filter_restrictions_for_item(Nil,
				  list_constant_15,
				  SYMBOL_FUNCTION(Qfilter_menu_restriction_for_kb),
				  Nil);
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    return result;
	}
    }
    else
	return VALUES_1(Qnil);
}

static Object list_constant_18;    /* # */

/* COMPUTE-ALL-RESTRICTIONS */
Object compute_all_restrictions varargs_1(int, n)
{
    Object user_mode;
    Object frame_qm, current_g2_user_mode_qm, result_1, type, ab_loop_list_;
    Object restrictions, permitted_qm;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(180,181);
    INIT_ARGS_nonrelocating();
    user_mode = REQUIRED_ARG_nonrelocating();
    frame_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    current_g2_user_mode_qm = user_mode;
    result_1 = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
	    0);
      type = Nil;
      ab_loop_list_ = list_constant_18;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      type = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      result = compute_restrictions_of_type(2,type,frame_qm);
      MVS_2(result,restrictions,permitted_qm);
      if (restrictions || permitted_qm)
	  result_1 = filter_cons_1(filter_cons_1(type,
		  filter_cons_1(permitted_qm,restrictions)),result_1);
      goto next_loop;
    end_loop:;
      result = VALUES_1(result_1);
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Slot_description_for_restrictions, Qslot_description_for_restrictions);

DEFINE_VARIABLE_WITH_SYMBOL(Slot_alias_for_restrictions, Qslot_alias_for_restrictions);

/* INCLUDE-SLOT-IN-ATTRIBUTE-TABLE-P */
Object include_slot_in_attribute_table_p(item,aliased_slot_name,defining_class)
    Object item, aliased_slot_name, defining_class;
{
    x_note_fn_call(180,182);
    return include_slot_in_attribute_table_for_mode_p(item,
	    aliased_slot_name,defining_class,Servicing_workstation_qm ? 
	    Current_g2_user_mode_qm : Qadministrator);
}

static Object Qmake_g2_secure_qm;  /* make-g2-secure? */

static Object Qfile_progress;      /* file-progress */

static Object Qkb_search_state;    /* kb-search-state */

static Object Qproprietary_package;  /* proprietary-package */

static Object Qmodule_this_is_part_of_qm;  /* module-this-is-part-of? */

static Object Qab_class;           /* class */

static Object list_constant_19;    /* # */

static Object Qfilter_visibility_restrictions;  /* filter-visibility-restrictions */

static Object Qis_visible;         /* is-visible */

static Object Qis_not_visible;     /* is-not-visible */

/* INCLUDE-SLOT-IN-ATTRIBUTE-TABLE-FOR-MODE-P */
Object include_slot_in_attribute_table_for_mode_p(item_or_class_description,
	    aliased_slot_name,defining_class,user_mode)
    Object item_or_class_description, aliased_slot_name, defining_class;
    Object user_mode;
{
    Object current_g2_user_mode_qm, x2, framep, class_description;
    Object sub_class_bit_vector, gensymed_symbol_3, temp_1;
    Object slot_alias_for_restrictions, slot_name_or_alias, class_or_frame_qm;
    Object slot_description_for_restrictions, permitted_restriction_set;
    Object prohibited_restriction_set, absolutely_prohibited_restriction_set;
    Object absolutely_selected_choice_qm, conditional_selected_choice_qm;
    Object conditional_termination_state_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(9);
    Object result;

    x_note_fn_call(180,183);
    current_g2_user_mode_qm = user_mode;
    PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
	    8);
      if (SIMPLE_VECTOR_P(item_or_class_description) && 
	      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_class_description)) > 
	      (SI_Long)2L &&  !EQ(ISVREF(item_or_class_description,
	      (SI_Long)1L),Qavailable_frame_vector)) {
	  x2 = ISVREF(item_or_class_description,(SI_Long)1L);
	  framep = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		  Qg2_defstruct_structure_name_class_description_g2_struct) 
		  ? x2 : Qnil;
      }
      else
	  framep = Nil;
      class_description = framep ? ISVREF(item_or_class_description,
	      (SI_Long)1L) : item_or_class_description;
      if (EQ(aliased_slot_name,Qmake_g2_secure_qm)) {
	  sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
	  superior_class_bit_number = IFIX(ISVREF(Ok_class_description,
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
	  if (Relations_tag_list)
	      result = VALUES_1(ISVREF(Current_workstation,(SI_Long)29L));
	  else
	      result = VALUES_1(Nil);
      }
      else {
	  gensymed_symbol_3 = 
		  lookup_global_or_kb_specific_property_value(Qfile_progress,
		  Class_description_gkbprop);
	  if (gensymed_symbol_3) {
	      sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
	      superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_3,
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
	  if (temp);
	  else {
	      gensymed_symbol_3 = 
		      lookup_global_or_kb_specific_property_value(Qkb_search_state,
		      Class_description_gkbprop);
	      if (gensymed_symbol_3) {
		  sub_class_bit_vector = ISVREF(class_description,
			  (SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(gensymed_symbol_3,(SI_Long)18L));
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
		      temp = (SI_Long)0L < gensymed_symbol;
		  }
		  else
		      temp = TRUEP(Nil);
	      }
	      else
		  temp = TRUEP(Nil);
	  }
	  if (temp);
	  else {
	      sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Icon_editor_table_info_frame_class_description,
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
	  if (temp)
	      result = VALUES_1(T);
	  else {
	      sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(G2_login_class_description,(SI_Long)18L));
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
		  result = VALUES_1(T);
	      else {
		  if ( !EQ(aliased_slot_name,Qproprietary_package) || 
			  Package_preparation_mode || framep && 
			  in_order_p(item_or_class_description)) {
		      sub_class_bit_vector = ISVREF(class_description,
			      (SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(Kb_workspace_class_description,
			      (SI_Long)18L));
		      sub_class_vector_index = superior_class_bit_number 
			      >>  -  - (SI_Long)3L;
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
			  gensymed_symbol = gensymed_symbol & 
				  gensymed_symbol_1;
			  temp = (SI_Long)0L < gensymed_symbol;
		      }
		      else
			  temp = TRUEP(Nil);
		      temp =  !temp;
		      if (temp);
		      else {
			  temp_1 = 
				  get_alias_for_slot_name_if_any(Qmodule_this_is_part_of_qm,
				  Qkb_workspace);
			  if (temp_1);
			  else
			      temp_1 = Qmodule_this_is_part_of_qm;
			  temp =  !EQ(aliased_slot_name,temp_1);
		      }
		      if (temp);
		      else
			  temp = framep ?  
				  !TRUEP(ISVREF(item_or_class_description,
				  (SI_Long)18L)) : TRUEP(Qnil);
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp) {
		      slot_alias_for_restrictions = aliased_slot_name;
		      if ( !EQ(aliased_slot_name,Qab_class)) {
			  slot_name_or_alias = aliased_slot_name;
			  class_or_frame_qm = ISVREF(class_description,
				  (SI_Long)1L);
			  temp_1 = 
				  get_slot_name_for_alias_if_any(slot_name_or_alias,
				  class_or_frame_qm);
			  if (temp_1);
			  else
			      temp_1 = slot_name_or_alias;
			  slot_description_for_restrictions = 
				  get_slot_description_of_class_description_function(temp_1,
				  class_description,defining_class);
		      }
		      else
			  slot_description_for_restrictions = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Slot_description_for_restrictions,Qslot_description_for_restrictions,slot_description_for_restrictions,
			      7);
			PUSH_SPECIAL_WITH_SYMBOL(Slot_alias_for_restrictions,Qslot_alias_for_restrictions,slot_alias_for_restrictions,
				6);
			  if ( !TRUEP(Slot_description_for_restrictions))
			      result = VALUES_1(T);
			  else {
			      permitted_restriction_set = Nil;
			      PUSH_SPECIAL_WITH_SYMBOL(Permitted_restriction_set,Qpermitted_restriction_set,permitted_restriction_set,
				      5);
				prohibited_restriction_set = Nil;
				PUSH_SPECIAL_WITH_SYMBOL(Prohibited_restriction_set,Qprohibited_restriction_set,prohibited_restriction_set,
					4);
				  absolutely_prohibited_restriction_set = Nil;
				  PUSH_SPECIAL_WITH_SYMBOL(Absolutely_prohibited_restriction_set,Qabsolutely_prohibited_restriction_set,absolutely_prohibited_restriction_set,
					  3);
				    absolutely_selected_choice_qm = Nil;
				    PUSH_SPECIAL_WITH_SYMBOL(Absolutely_selected_choice_qm,Qabsolutely_selected_choice_qm,absolutely_selected_choice_qm,
					    2);
				      conditional_selected_choice_qm = Nil;
				      PUSH_SPECIAL_WITH_SYMBOL(Conditional_selected_choice_qm,Qconditional_selected_choice_qm,conditional_selected_choice_qm,
					      1);
					conditional_termination_state_qm = Nil;
					PUSH_SPECIAL_WITH_SYMBOL(Conditional_termination_state_qm,Qconditional_termination_state_qm,conditional_termination_state_qm,
						0);
					  temp_1 = 
						  filter_restrictions_for_item(item_or_class_description,
						  list_constant_19,
						  SYMBOL_FUNCTION(Qfilter_visibility_restrictions),
						  T);
					  if (EQ(temp_1,Qis_visible) || 
						  EQ(temp_1,Qnil))
					      result = VALUES_1(T);
					  else if (EQ(temp_1,Qis_not_visible))
					      result = VALUES_1(Nil);
					  else
					      result = VALUES_1(Qnil);
					POP_SPECIAL();
				      POP_SPECIAL();
				    POP_SPECIAL();
				  POP_SPECIAL();
				POP_SPECIAL();
			      POP_SPECIAL();
			  }
			POP_SPECIAL();
		      POP_SPECIAL();
		  }
		  else
		      result = VALUES_1(Nil);
	      }
	  }
      }
    POP_SPECIAL();
    return result;
}

/* FILTER-VISIBILITY-RESTRICTIONS */
Object filter_visibility_restrictions(restriction_clause,
	    item_or_class_description,current_item)
    Object restriction_clause, item_or_class_description, current_item;
{
    Object x2, name_denotations, restriction_type, class_description;
    Object name_denotation, ab_loop_list_, ab_loop_it_, temp_1;
    Object slot_name_or_alias, class_or_frame_qm, temp_2, slot_in_list_p;
    char temp;

    x_note_fn_call(180,184);
    if (SIMPLE_VECTOR_P(item_or_class_description) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_class_description)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(item_or_class_description,
	    (SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(item_or_class_description,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp ? 
	    TRUEP(frame_matches_restriction_class_spec(item_or_class_description,
	    SECOND(restriction_clause),current_item)) : 
	    TRUEP(class_description_matches_restriction_class_spec(item_or_class_description,
	    SECOND(restriction_clause),current_item))) {
	name_denotations = THIRD(restriction_clause);
	restriction_type = FOURTH(restriction_clause);
	if (SIMPLE_VECTOR_P(item_or_class_description) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_class_description)) 
		> (SI_Long)2L &&  !EQ(ISVREF(item_or_class_description,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_class_description,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	class_description = temp ? ISVREF(item_or_class_description,
		(SI_Long)1L) : item_or_class_description;
	if (EQ(restriction_type,Qinclude) || EQ(restriction_type,
		Qinclude_additionally)) {
	    name_denotation = Nil;
	    ab_loop_list_ = name_denotations;
	    ab_loop_it_ = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    name_denotation = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (EQ(Slot_alias_for_restrictions,CONSP(name_denotation) ? 
		    M_CAR(M_CDR(M_CDR(name_denotation))) : name_denotation)) {
		temp_1 = Slot_description_for_restrictions;
		slot_name_or_alias = CONSP(name_denotation) ? 
			M_CAR(M_CDR(M_CDR(name_denotation))) : name_denotation;
		class_or_frame_qm = ISVREF(class_description,(SI_Long)1L);
		temp_2 = get_slot_name_for_alias_if_any(slot_name_or_alias,
			class_or_frame_qm);
		if (temp_2);
		else
		    temp_2 = slot_name_or_alias;
		ab_loop_it_ = EQ(temp_1,
			get_slot_description_of_class_description_function(temp_2,
			class_description,CONSP(name_denotation) ? 
			M_CAR(M_CDR(name_denotation)) : Nil)) ? T : Nil;
	    }
	    else
		ab_loop_it_ = Nil;
	    if (ab_loop_it_) {
		slot_in_list_p = ab_loop_it_;
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    slot_in_list_p = Qnil;
	  end_1:;
	}
	else {
	    name_denotation = Nil;
	    ab_loop_list_ = name_denotations;
	    ab_loop_it_ = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    name_denotation = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (EQ(name_denotation,
		    ISVREF(Slot_description_for_restrictions,(SI_Long)1L)) 
		    || EQ(Slot_alias_for_restrictions,
		    CONSP(name_denotation) ? 
		    M_CAR(M_CDR(M_CDR(name_denotation))) : name_denotation)) {
		temp_2 =  !(CONSP(name_denotation) ? 
			TRUEP(M_CAR(M_CDR(name_denotation))) : TRUEP(Nil)) 
			? T : Nil;
		if (temp_2);
		else {
		    temp_1 = Slot_description_for_restrictions;
		    slot_name_or_alias = CONSP(name_denotation) ? 
			    M_CAR(M_CDR(M_CDR(name_denotation))) : 
			    name_denotation;
		    class_or_frame_qm = ISVREF(class_description,(SI_Long)1L);
		    temp_2 = 
			    get_slot_name_for_alias_if_any(slot_name_or_alias,
			    class_or_frame_qm);
		    if (temp_2);
		    else
			temp_2 = slot_name_or_alias;
		    temp_2 = EQ(temp_1,
			    get_slot_description_of_class_description_function(temp_2,
			    class_description,CONSP(name_denotation) ? 
			    M_CAR(M_CDR(name_denotation)) : Nil)) ? T : Nil;
		}
		ab_loop_it_ = temp_2;
	    }
	    else
		ab_loop_it_ = Nil;
	    if (ab_loop_it_) {
		slot_in_list_p = ab_loop_it_;
		goto end_2;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    slot_in_list_p = Qnil;
	  end_2:;
	}
	if (EQ(restriction_type,Qinclude) || EQ(restriction_type,
		Qinclude_additionally)) {
	    if (slot_in_list_p) {
		Conditional_termination_state_qm = Qis_visible;
		temp_2 = Nil;
	    }
	    else if (EQ(restriction_type,Qinclude)) {
		Conditional_termination_state_qm = Qis_not_visible;
		temp_2 = T;
	    }
	    else
		temp_2 = Nil;
	}
	else if (EQ(restriction_type,Qexclude) || EQ(restriction_type,
		Qexclude_additionally) || EQ(restriction_type,
		Qexclude_absolutely)) {
	    if (slot_in_list_p) {
		Conditional_termination_state_qm = Qis_not_visible;
		temp_2 = T;
	    }
	    else if (EQ(restriction_type,Qexclude)) {
		Conditional_termination_state_qm = Qis_visible;
		temp_2 = Nil;
	    }
	    else
		temp_2 = Nil;
	}
	else
	    temp_2 = Qnil;
    }
    else
	temp_2 = Nil;
    return VALUES_1(temp_2);
}

/* FILTER-ATTRIBUTE-VISIBILITY-RESTRICTIONS */
Object filter_attribute_visibility_restrictions(restriction_clause,item,
	    current_item)
    Object restriction_clause, item, current_item;
{
    Object slot_names, restriction_type;

    x_note_fn_call(180,185);
    if (frame_matches_restriction_class_spec(item,
	    SECOND(restriction_clause),current_item)) {
	slot_names = THIRD(restriction_clause);
	restriction_type = FOURTH(restriction_clause);
	filter_new_restriction_set(restriction_type,slot_names);
    }
    return VALUES_1(Nil);
}

static Object Qfilter_attribute_visibility_restrictions;  /* filter-attribute-visibility-restrictions */

/* COMPUTE-VISIBLE-SLOTS-FOR-ATTRIBUTE-TABLE */
Object compute_visible_slots_for_attribute_table(item)
    Object item;
{
    Object permitted_restriction_set, prohibited_restriction_set;
    Object absolutely_prohibited_restriction_set;
    Object absolutely_selected_choice_qm, conditional_selected_choice_qm;
    Object conditional_termination_state_qm;
    Declare_special(6);
    Object result;

    x_note_fn_call(180,186);
    permitted_restriction_set = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Permitted_restriction_set,Qpermitted_restriction_set,permitted_restriction_set,
	    5);
      prohibited_restriction_set = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Prohibited_restriction_set,Qprohibited_restriction_set,prohibited_restriction_set,
	      4);
	absolutely_prohibited_restriction_set = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Absolutely_prohibited_restriction_set,Qabsolutely_prohibited_restriction_set,absolutely_prohibited_restriction_set,
		3);
	  absolutely_selected_choice_qm = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Absolutely_selected_choice_qm,Qabsolutely_selected_choice_qm,absolutely_selected_choice_qm,
		  2);
	    conditional_selected_choice_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Conditional_selected_choice_qm,Qconditional_selected_choice_qm,conditional_selected_choice_qm,
		    1);
	      conditional_termination_state_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Conditional_termination_state_qm,Qconditional_termination_state_qm,conditional_termination_state_qm,
		      0);
		result = filter_restrictions_for_item(item,
			list_constant_19,
			SYMBOL_FUNCTION(Qfilter_attribute_visibility_restrictions),
			Nil);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qincludes;           /* includes */

/* FILTER-TABLE-RESTRICTIONS */
Object filter_table_restrictions(restriction_clause,item,current_item)
    Object restriction_clause, item, current_item;
{
    Object name_denotations, name_denotation, ab_loop_list_, ab_loop_it_;
    Object temp_1, slot_name_or_alias, class_or_frame_qm, temp_2;
    char temp;

    x_note_fn_call(180,187);
    if (frame_matches_restriction_class_spec(item,
	    SECOND(restriction_clause),current_item)) {
	name_denotations = THIRD(restriction_clause);
	temp =  !TRUEP(name_denotations);
	if (temp);
	else if (Slot_description_for_restrictions) {
	    if (EQ(Qincludes,Qinclude) || EQ(Qincludes,
			Qinclude_additionally)) {
		name_denotation = Nil;
		ab_loop_list_ = name_denotations;
		ab_loop_it_ = Nil;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		name_denotation = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if (EQ(Slot_alias_for_restrictions,CONSP(name_denotation) ?
			 M_CAR(M_CDR(M_CDR(name_denotation))) : 
			name_denotation)) {
		    temp_1 = Slot_description_for_restrictions;
		    slot_name_or_alias = CONSP(name_denotation) ? 
			    M_CAR(M_CDR(M_CDR(name_denotation))) : 
			    name_denotation;
		    class_or_frame_qm = ISVREF(item,(SI_Long)1L);
		    temp_2 = 
			    get_slot_name_for_alias_if_any(slot_name_or_alias,
			    class_or_frame_qm);
		    if (temp_2);
		    else
			temp_2 = slot_name_or_alias;
		    ab_loop_it_ = EQ(temp_1,
			    get_slot_description_of_class_description_function(temp_2,
			    item,CONSP(name_denotation) ? 
			    M_CAR(M_CDR(name_denotation)) : Nil)) ? T : Nil;
		}
		else
		    ab_loop_it_ = Nil;
		if (ab_loop_it_) {
		    temp = TRUEP(ab_loop_it_);
		    goto end_1;
		}
		goto next_loop;
	      end_loop:
		temp = TRUEP(Qnil);
	      end_1:;
	    }
	    else {
		name_denotation = Nil;
		ab_loop_list_ = name_denotations;
		ab_loop_it_ = Nil;
	      next_loop_1:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_1;
		name_denotation = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if (EQ(name_denotation,
			ISVREF(Slot_description_for_restrictions,
			(SI_Long)1L)) || EQ(Slot_alias_for_restrictions,
			CONSP(name_denotation) ? 
			M_CAR(M_CDR(M_CDR(name_denotation))) : 
			name_denotation)) {
		    temp_2 =  !(CONSP(name_denotation) ? 
			    TRUEP(M_CAR(M_CDR(name_denotation))) : 
			    TRUEP(Nil)) ? T : Nil;
		    if (temp_2);
		    else {
			temp_1 = Slot_description_for_restrictions;
			slot_name_or_alias = CONSP(name_denotation) ? 
				M_CAR(M_CDR(M_CDR(name_denotation))) : 
				name_denotation;
			class_or_frame_qm = ISVREF(item,(SI_Long)1L);
			temp_2 = 
				get_slot_name_for_alias_if_any(slot_name_or_alias,
				class_or_frame_qm);
			if (temp_2);
			else
			    temp_2 = slot_name_or_alias;
			temp_2 = EQ(temp_1,
				get_slot_description_of_class_description_function(temp_2,
				item,CONSP(name_denotation) ? 
				M_CAR(M_CDR(name_denotation)) : Nil)) ? T :
				 Nil;
		    }
		    ab_loop_it_ = temp_2;
		}
		else
		    ab_loop_it_ = Nil;
		if (ab_loop_it_) {
		    temp = TRUEP(ab_loop_it_);
		    goto end_2;
		}
		goto next_loop_1;
	      end_loop_1:
		temp = TRUEP(Qnil);
	      end_2:;
	    }
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    filter_new_restriction_set(FOURTH(restriction_clause),
		    CDDDDR(restriction_clause));
    }
    return VALUES_1(Nil);
}

static Object list_constant_20;    /* # */

static Object Qfilter_table_restrictions;  /* filter-table-restrictions */

/* COMPUTE-MENU-RESTRICTIONS-FOR-CLICK-ON-TABLE */
Object compute_menu_restrictions_for_click_on_table(item,
	    slot_name_or_alias_qm,defining_class)
    Object item, slot_name_or_alias_qm, defining_class;
{
    Object permitted_restriction_set, prohibited_restriction_set;
    Object absolutely_prohibited_restriction_set;
    Object absolutely_selected_choice_qm, conditional_selected_choice_qm;
    Object conditional_termination_state_qm, slot_alias_for_restrictions;
    Object slot_name_or_alias, class_description, class_or_frame_qm, temp;
    Object slot_description_for_restrictions;
    Declare_special(8);
    Object result;

    x_note_fn_call(180,188);
    permitted_restriction_set = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Permitted_restriction_set,Qpermitted_restriction_set,permitted_restriction_set,
	    7);
      prohibited_restriction_set = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Prohibited_restriction_set,Qprohibited_restriction_set,prohibited_restriction_set,
	      6);
	absolutely_prohibited_restriction_set = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Absolutely_prohibited_restriction_set,Qabsolutely_prohibited_restriction_set,absolutely_prohibited_restriction_set,
		5);
	  absolutely_selected_choice_qm = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Absolutely_selected_choice_qm,Qabsolutely_selected_choice_qm,absolutely_selected_choice_qm,
		  4);
	    conditional_selected_choice_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Conditional_selected_choice_qm,Qconditional_selected_choice_qm,conditional_selected_choice_qm,
		    3);
	      conditional_termination_state_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Conditional_termination_state_qm,Qconditional_termination_state_qm,conditional_termination_state_qm,
		      2);
		slot_alias_for_restrictions = slot_name_or_alias_qm;
		if (slot_name_or_alias_qm) {
		    slot_name_or_alias = slot_name_or_alias_qm;
		    class_description = ISVREF(item,(SI_Long)1L);
		    class_or_frame_qm = ISVREF(class_description,(SI_Long)1L);
		    temp = 
			    get_slot_name_for_alias_if_any(slot_name_or_alias,
			    class_or_frame_qm);
		    if (temp);
		    else
			temp = slot_name_or_alias;
		    slot_description_for_restrictions = 
			    get_slot_description_of_class_description_function(temp,
			    class_description,defining_class);
		}
		else
		    slot_description_for_restrictions = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Slot_description_for_restrictions,Qslot_description_for_restrictions,slot_description_for_restrictions,
			1);
		  PUSH_SPECIAL_WITH_SYMBOL(Slot_alias_for_restrictions,Qslot_alias_for_restrictions,slot_alias_for_restrictions,
			  0);
		    result = filter_restrictions_for_item(item,
			    list_constant_20,
			    SYMBOL_FUNCTION(Qfilter_table_restrictions),Nil);
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

/* FILTER-NON-MENU-RESTRICTION */
Object filter_non_menu_restriction(restriction_clause,item,current_item)
    Object restriction_clause, item, current_item;
{
    x_note_fn_call(180,189);
    if (frame_matches_restriction_class_spec(item,
	    SECOND(restriction_clause),current_item))
	filter_new_restriction_set(THIRD(restriction_clause),
		CDDDR(restriction_clause));
    return VALUES_1(Nil);
}

static Object list_constant_21;    /* # */

static Object Qfilter_non_menu_restriction;  /* filter-non-menu-restriction */

/* COMPUTE-NON-MENU-RESTRICTIONS-FOR-ITEM */
Object compute_non_menu_restrictions_for_item(item_qm)
    Object item_qm;
{
    Object permitted_restriction_set, prohibited_restriction_set;
    Object absolutely_prohibited_restriction_set;
    Object absolutely_selected_choice_qm, conditional_selected_choice_qm;
    Object conditional_termination_state_qm;
    Declare_special(6);
    Object result;

    x_note_fn_call(180,190);
    permitted_restriction_set = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Permitted_restriction_set,Qpermitted_restriction_set,permitted_restriction_set,
	    5);
      prohibited_restriction_set = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Prohibited_restriction_set,Qprohibited_restriction_set,prohibited_restriction_set,
	      4);
	absolutely_prohibited_restriction_set = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Absolutely_prohibited_restriction_set,Qabsolutely_prohibited_restriction_set,absolutely_prohibited_restriction_set,
		3);
	  absolutely_selected_choice_qm = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Absolutely_selected_choice_qm,Qabsolutely_selected_choice_qm,absolutely_selected_choice_qm,
		  2);
	    conditional_selected_choice_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Conditional_selected_choice_qm,Qconditional_selected_choice_qm,conditional_selected_choice_qm,
		    1);
	      conditional_termination_state_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Conditional_termination_state_qm,Qconditional_termination_state_qm,conditional_termination_state_qm,
		      0);
		result = filter_restrictions_for_item(item_qm,
			list_constant_21,
			SYMBOL_FUNCTION(Qfilter_non_menu_restriction),Nil);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* NON-MENU-CHOICE-PERMITTED-P */
Object non_menu_choice_permitted_p(non_menu_choice,item_qm)
    Object non_menu_choice, item_qm;
{
    Object restrictions, permitted_qm, temp, last_1, next_qm, temp_1;
    Object svref_arg_2;
    Object result;

    x_note_fn_call(180,191);
    result = compute_non_menu_restrictions_for_item(item_qm);
    MVS_2(result,restrictions,permitted_qm);
    temp = memq_function(non_menu_choice,restrictions) ? permitted_qm :  
	    !TRUEP(permitted_qm) ? T : Nil;
    if (restrictions) {
	last_1 = restrictions;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qfilter);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qfilter);
	if (ISVREF(Available_filter_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_1 = ISVREF(Available_filter_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_1) = restrictions;
	    temp_1 = Available_filter_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = last_1;
	}
	else {
	    temp_1 = Available_filter_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = restrictions;
	    temp_1 = Available_filter_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    return VALUES_1(temp);
}

static Object Qshow_workspace;     /* show-workspace */

/* WORKSPACES-CAN-BE-SHOWN-AT-THIS-KB-LEVEL-P */
Object workspaces_can_be_shown_at_this_kb_level_p(block,workstation)
    Object block, workstation;
{
    Object temp, workspace_qm, current_g2_user_mode_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(180,192);
    temp =  !TRUEP(ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)16L)) ? T : Nil;
    if (temp);
    else {
	workspace_qm = get_workspace_if_any(block);
	temp = workspace_qm ? ( !TRUEP(ISVREF(ISVREF(workspace_qm,
		(SI_Long)1L),(SI_Long)16L)) ? T : Nil) : Qnil;
    }
    if (temp)
	return VALUES_1(temp);
    else {
	current_g2_user_mode_qm = ISVREF(workstation,(SI_Long)19L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
		0);
	  result = non_menu_choice_permitted_p(Qshow_workspace,block);
	POP_SPECIAL();
	return result;
    }
}

static Object string_constant_111;  /* "Item configuration for ~NF" */

static Object string_constant_112;  /* "Selecting this item" */

static Object string_constant_113;  /* "Menus for this item" */

static Object string_constant_114;  /* "Non-menu choices for this item" */

static Object string_constant_115;  /* "Table menus for this item" */

static Object Qroot;               /* root */

static Object Qdo_not_put_in_attribute_tables_if_null;  /* do-not-put-in-attribute-tables-if-null */

static Object string_constant_116;  /* "Table menus for the" */

static Object string_constant_117;  /* "this item" */

static Object string_constant_118;  /* "There are no table restrictions for the ~a of this item." */

static Object string_constant_119;  /* "The attribute ~(~a::~a~) is not visible." */

static Object string_constant_120;  /* "The attribute ~a is not visible." */

static Object string_constant_121;  /* "Item configuration on the KB:" */

static Object string_constant_122;  /* "Instance configuration on ~nf:" */

static Object string_constant_123;  /* "Item configuration on ~nf:" */

static Object string_constant_124;  /* "~%" */

static Object Qclass_format;       /* class-format */

static Object Qborderless_free_text_format;  /* borderless-free-text-format */

static Object Qfont_for_descriptions;  /* font-for-descriptions */

static Object Qattributes_table_format;  /* attributes-table-format */

/* MAKE-TABLE-DESCRIBING-RESTRICTIONS */
Object make_table_describing_restrictions(item)
    Object item;
{
    Object write_symbols_in_lower_case_qm, choice_restrictions, include_qm;
    Object single_action_for_click_qm, header, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_1, selecting_clauses, non_menu_choices, table_menu_choices;
    Object text_strings, class_1, class_description, temp_2, temp_3;
    Object slot_description, ab_loop_list_, slot_name, class_qualifier_qm;
    Object slot_features, type_of_slot, alias_qm, gensymed_symbol;
    Object sub_class_bit_vector, aliased_slot_name;
    Object choice_restrictions_for_slot, include_for_slot_qm, text_string_qm;
    Object visibility_restrictions, active_restrictions, list_1;
    Object traversing_class_hierarchy_qm, the_class_inheritance_path;
    Object original_item_or_class_description_qm;
    Object frame_with_modified_superior_qm, x2, class_description_qm, place;
    Object object_configuration, the_class_inheritance_path_old_value;
    Object class_name, defn, potential_restrictions;
    Object rows_of_text_strings_for_text_cells, l, format_1;
    Object ab_loop_iter_flag_;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(8);
    Object result;

    x_note_fn_call(180,193);
    write_symbols_in_lower_case_qm = T;
    PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
	    7);
      choice_restrictions = Nil;
      include_qm = Nil;
      single_action_for_click_qm = Nil;
      header = slot_value_cons_1(tformat_text_string(2,string_constant_111,
	      item),Nil);
      result = compute_menu_restrictions_for_click_on_workspace(item);
      MVS_3(result,choice_restrictions,include_qm,single_action_for_click_qm);
      temp = TRUEP(choice_restrictions);
      if (temp);
      else
	  temp = TRUEP(single_action_for_click_qm);
      if (temp) {
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
		    if (single_action_for_click_qm)
			write_restriction_clause_1(6,string_constant_112,
				Nil,Nil,EQ(single_action_for_click_qm,
				Qnothing) ? Qdoes : Qimplies,
				single_action_for_click_qm,T);
		    else
			write_restriction_clause_1(6,string_constant_113,
				Nil,Nil,include_qm ? Qinclude : Qexclude,
				choice_restrictions,T);
		    temp_1 = copy_out_current_wide_string();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  temp_1 = slot_value_cons_1(temp_1,Nil);
	  if (choice_restrictions)
	      reclaim_filter_list_1(choice_restrictions);
	  selecting_clauses = temp_1;
      }
      else
	  selecting_clauses = Nil;
      result = compute_non_menu_restrictions_for_item(item);
      MVS_2(result,choice_restrictions,include_qm);
      if (choice_restrictions) {
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
		    write_restriction_clause_1(6,string_constant_114,Nil,
			    Nil,include_qm ? Qinclude : Qexclude,
			    choice_restrictions,T);
		    temp_1 = copy_out_current_wide_string();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  temp_1 = slot_value_cons_1(temp_1,Nil);
	  reclaim_filter_list_1(choice_restrictions);
	  non_menu_choices = temp_1;
      }
      else
	  non_menu_choices = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Non_menu_choices,Qnon_menu_choices,non_menu_choices,
	      6);
	result = compute_menu_restrictions_for_click_on_table(item,Nil,Nil);
	MVS_2(result,choice_restrictions,include_qm);
	if (choice_restrictions) {
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
		      write_restriction_clause_1(6,string_constant_115,Nil,
			      Nil,include_qm ? Qinclude : Qexclude,
			      choice_restrictions,T);
		      temp_1 = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    table_menu_choices = slot_value_cons_1(temp_1,Nil);
	}
	else
	    table_menu_choices = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Table_menu_choices,Qtable_menu_choices,table_menu_choices,
		5);
	  text_strings = Nil;
	  class_1 = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)1L);
	  class_description = ISVREF(item,(SI_Long)1L);
	  temp_2 = Mutable_slot_description_list_head;
	  temp_3 = Pseudo_class_slot_description;
	  M_CAR(temp_2) = temp_3;
	  temp_2 = Mutable_slot_description_list_head;
	  temp_3 = ISVREF(class_description,(SI_Long)6L);
	  M_CDR(temp_2) = temp_3;
	  slot_description = Nil;
	  ab_loop_list_ = Mutable_slot_description_list_head;
	  slot_name = Nil;
	  class_qualifier_qm = Nil;
	  slot_features = Nil;
	  type_of_slot = Nil;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  slot_description = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  slot_name = ISVREF(slot_description,(SI_Long)2L);
	  if ( !(EQ(slot_name,Qab_class) && EQ(Qroot,
		  ISVREF(slot_description,(SI_Long)3L)))) {
	      if ( ! !TRUEP(ISVREF(slot_description,(SI_Long)8L))) {
		  temp_1 = ISVREF(slot_description,(SI_Long)3L);
		  temp =  !EQ(temp_1,
			  ISVREF(get_slot_description_of_class_description_function(ISVREF(slot_description,
			  (SI_Long)2L),class_description,Nil),(SI_Long)3L));
	      }
	      else
		  temp = TRUEP(Nil);
	      class_qualifier_qm = temp ? ISVREF(slot_description,
		      (SI_Long)3L) : Nil;
	  }
	  else
	      class_qualifier_qm = Nil;
	  slot_features = ISVREF(slot_description,(SI_Long)9L);
	  type_of_slot = assq_function(Qtype,slot_features);
	  if (type_of_slot &&  
		  !TRUEP(do_not_put_slot_in_attribute_tables_p(3,
		  slot_description,Nil,item)) && ( 
		  !TRUEP(assq_function(Qdo_not_put_in_attribute_tables_if_null,
		  slot_features)) || get_slot_description_value(item,
		  slot_description)) && SECOND(type_of_slot)) {
	      alias_qm = get_alias_for_slot_name_if_any(slot_name,class_1);
	      if ( !TRUEP(Nil) || slot_denotation_member(slot_name,
		      class_qualifier_qm,Nil) || (alias_qm ? 
		      TRUEP(slot_denotation_member(alias_qm,
		      class_qualifier_qm,Nil)) : TRUEP(Nil))) {
		  temp =  !TRUEP(Nil);
		  if (temp);
		  else {
		      temp_1 = alias_qm;
		      if (temp_1);
		      else
			  temp_1 = slot_name;
		      temp = TRUEP(include_slot_in_attribute_table_p(item,
			      temp_1,class_qualifier_qm));
		  }
		  if (temp);
		  else {
		      gensymed_symbol = 
			      lookup_global_or_kb_specific_property_value(Qfile_progress,
			      Class_description_gkbprop);
		      if (gensymed_symbol) {
			  sub_class_bit_vector = ISVREF(ISVREF(item,
				  (SI_Long)1L),(SI_Long)19L);
			  superior_class_bit_number = 
				  IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
				      superior_class_bit_number & (SI_Long)7L;
			      gensymed_symbol_2 = gensymed_symbol_2 << 
				      gensymed_symbol_3;
			      gensymed_symbol_1 = gensymed_symbol_1 & 
				      gensymed_symbol_2;
			      temp = (SI_Long)0L < gensymed_symbol_1;
			  }
			  else
			      temp = TRUEP(Nil);
		      }
		      else
			  temp = TRUEP(Nil);
		  }
		  if (temp);
		  else
		      temp = EQ(slot_name,Qab_class) ? EQ(Qroot,
			      ISVREF(slot_description,(SI_Long)3L)) : 
			      TRUEP(Qnil);
	      }
	      else
		  temp = TRUEP(Nil);
	      if ((temp ?  !TRUEP(Nil) ||  
		      !(slot_denotation_member(slot_name,
		      class_qualifier_qm,Nil) || (alias_qm ? 
		      TRUEP(slot_denotation_member(alias_qm,
		      class_qualifier_qm,Nil)) : TRUEP(Nil))) : 
		      TRUEP(Nil)) ?  !TRUEP(Nil) || 
		      type_slot_feature_assq_if_editable(slot_features) : 
		      TRUEP(Nil)) {
		  aliased_slot_name = alias_qm;
		  if (aliased_slot_name);
		  else
		      aliased_slot_name = slot_name;
		  if (include_slot_in_attribute_table_p(item,
			  aliased_slot_name,class_qualifier_qm)) {
		      result = compute_menu_restrictions_for_click_on_table(item,
			      aliased_slot_name,Nil);
		      MVS_2(result,choice_restrictions_for_slot,
			      include_for_slot_qm);
		      if (g2_xor(include_qm,include_for_slot_qm) ||  
			      !TRUEP(g2_set_equivalent(choice_restrictions,
			      choice_restrictions_for_slot))) {
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
				    if (choice_restrictions_for_slot)
					write_restriction_clause_1(6,
						string_constant_116,
						aliased_slot_name,
						string_constant_117,
						include_qm ? Qinclude : 
						Qexclude,
						choice_restrictions_for_slot,
						T);
				    else
					tformat(2,string_constant_118,
						aliased_slot_name);
				    text_string_qm = 
					    copy_out_current_wide_string();
				  POP_SPECIAL();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
		      }
		      else
			  text_string_qm = Nil;
		  }
		  else
		      text_string_qm = class_qualifier_qm ? 
			      tformat_text_string(3,string_constant_119,
			      class_qualifier_qm,aliased_slot_name) : 
			      tformat_text_string(2,string_constant_120,
			      aliased_slot_name);
		  if (text_string_qm)
		      text_strings = slot_value_cons_1(text_string_qm,
			      text_strings);
	      }
	  }
	  goto next_loop;
	end_loop:;
	  temp_1 = nreverse(text_strings);
	  if (choice_restrictions)
	      reclaim_filter_list_1(choice_restrictions);
	  visibility_restrictions = temp_1;
	  temp_1 = Non_menu_choices;
	  active_restrictions = nconc2(selecting_clauses,nconc2(temp_1,
		  nconc2(Table_menu_choices,visibility_restrictions)));
	  list_1 = Nil;
	  traversing_class_hierarchy_qm = Nil;
	  the_class_inheritance_path = Nil;
	  original_item_or_class_description_qm = item;
	  frame_with_modified_superior_qm = 
		  Superior_frame_for_restrictions_frame_qm;
	  if (SIMPLE_VECTOR_P(original_item_or_class_description_qm) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(original_item_or_class_description_qm)) 
		  > (SI_Long)2L &&  
		  !EQ(ISVREF(original_item_or_class_description_qm,
		  (SI_Long)1L),Qavailable_frame_vector)) {
	      x2 = ISVREF(original_item_or_class_description_qm,(SI_Long)1L);
	      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp)
	      class_description_qm = 
		      ISVREF(original_item_or_class_description_qm,
		      (SI_Long)1L);
	  else if (SIMPLE_VECTOR_P(original_item_or_class_description_qm) 
		  && EQ(ISVREF(original_item_or_class_description_qm,
		  (SI_Long)0L),
		  Qg2_defstruct_structure_name_class_description_g2_struct))
	      class_description_qm = original_item_or_class_description_qm;
	  else
	      class_description_qm = Qnil;
	  place = Nil;
	  if (place);
	  else {
	      if (SIMPLE_VECTOR_P(original_item_or_class_description_qm) 
		      && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(original_item_or_class_description_qm)) 
		      > (SI_Long)2L &&  
		      !EQ(ISVREF(original_item_or_class_description_qm,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(original_item_or_class_description_qm,
			  (SI_Long)1L);
		  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp = TRUEP(Nil);
	      place = temp ? original_item_or_class_description_qm : 
		      Kb_restrictions;
	  }
	  object_configuration = Nil;
	next_loop_1:
	  if ( !TRUEP(place))
	      goto end_loop_1;
	  if ( !TRUEP(traversing_class_hierarchy_qm))
	      object_configuration = get_lookup_slot_value(place,
		      Qobject_configuration);
	  else {
	      if (SIMPLE_VECTOR_P(place) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(place)) > (SI_Long)2L 
		      &&  !EQ(ISVREF(place,(SI_Long)1L),
		      Qavailable_frame_vector)) {
		  x2 = ISVREF(place,(SI_Long)1L);
		  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp = TRUEP(Nil);
	      if ( !temp)
		  object_configuration = Nil;
	      else
		  object_configuration = ISVREF(place,(SI_Long)23L);
	  }
	  if (class_is_visible_to_user_p(traversing_class_hierarchy_qm ? 
		  class_definition_name(place) : ISVREF(ISVREF(place,
		  (SI_Long)1L),(SI_Long)1L))) {
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
			if (EQ(place,Kb_restrictions))
			    twrite(string_constant_121);
			else
			    tformat(2,traversing_class_hierarchy_qm ? 
				    string_constant_122 : 
				    string_constant_123,place);
			if (object_configuration)
			    tformat(1,string_constant_124);
			else
			    twrite(string_constant_30);
			write_object_configuration(object_configuration);
			temp_1 = copy_out_current_wide_string();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	      list_1 = slot_value_cons_1(temp_1,list_1);
	  }
	  if (traversing_class_hierarchy_qm) {
	      the_class_inheritance_path_old_value = 
		      the_class_inheritance_path;
	      temp_1 = FIRST(the_class_inheritance_path_old_value);
	      the_class_inheritance_path = 
		      REST(the_class_inheritance_path_old_value);
	      class_name = temp_1;
	      defn = class_name &&  !EQ(class_name,Qitem) ? 
		      lookup_global_or_kb_specific_property_value(class_name,
		      Class_definition_gkbprop) : Qnil;
	      place = CONSP(defn) ? class_name : defn;
	  }
	  else if (EQ(place,Kb_restrictions)) {
	      if (class_description_qm) {
		  traversing_class_hierarchy_qm = T;
		  the_class_inheritance_path = ISVREF(class_description_qm,
			  (SI_Long)2L);
		  the_class_inheritance_path_old_value = 
			  the_class_inheritance_path;
		  temp_1 = FIRST(the_class_inheritance_path_old_value);
		  the_class_inheritance_path = 
			  REST(the_class_inheritance_path_old_value);
		  class_name = temp_1;
		  defn = class_name ? 
			  lookup_global_or_kb_specific_property_value(class_name,
			  Class_definition_gkbprop) : Qnil;
		  place = CONSP(defn) ? class_name : defn;
	      }
	      else
		  place = Nil;
	  }
	  else if (EQ(place,frame_with_modified_superior_qm)) {
	      frame_with_modified_superior_qm = Nil;
	      place = Superior_frame_for_restrictions_superior_qm;
	  }
	  else {
	      place = superior_frame(place);
	      if (place);
	      else
		  place = Kb_restrictions;
	  }
	  goto next_loop_1;
	end_loop_1:;
	  potential_restrictions = nreverse(list_1);
	  rows_of_text_strings_for_text_cells = active_restrictions ? 
		  nconc2(header,nconc2(active_restrictions,
		  nconc2(make_table_spacer_cells(1,FIX((SI_Long)2L)),
		  potential_restrictions))) : nconc2(header,
		  potential_restrictions);
	  l = rows_of_text_strings_for_text_cells;
	  format_1 = Qclass_format;
	  ab_loop_iter_flag_ = T;
	next_loop_2:
	  if ( !TRUEP(l))
	      goto end_loop_2;
	  if ( !TRUEP(ab_loop_iter_flag_))
	      format_1 = 
		      choose_font_format_per_fonts_table(Qborderless_free_text_format,
		      Qfont_for_descriptions);
	  if (text_string_p(CAR(l))) {
	      temp_2 = slot_value_cons_1(make_text_cell(2,
		      slot_value_cons_1(CAR(l),Nil),format_1),Nil);
	      M_CAR(l) = temp_2;
	  }
	  ab_loop_iter_flag_ = Nil;
	  l = M_CDR(l);
	  goto next_loop_2;
	end_loop_2:
	  temp_1 = rows_of_text_strings_for_text_cells;
	  goto end_1;
	  temp_1 = Qnil;
	end_1:;
	  result = make_or_reformat_table(3,temp_1,New_g2_classic_ui_p ? 
		  get_ui_parameter(1,Qattributes_table_format) : 
		  Qattributes_table_format,Nil);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_filters_search_result, Qcurrent_filters_search_result);

DEFINE_VARIABLE_WITH_SYMBOL(Contains_proprietary_p_1, Qcontains_proprietary_p_1);

/* CONTAINS-PROPRIETARY-P-1 */
Object contains_proprietary_p_1(block,superior_block)
    Object block, superior_block;
{
    Object temp;

    x_note_fn_call(180,194);
    if (in_order_p(block)) {
	Current_filters_search_result = T;
	temp = Current_filters_search_result;
    }
    else
	temp = funcall_function_to_inferior_blocks(block,
		Contains_proprietary_p_1);
    return VALUES_1(temp);
}

/* CONTAINS-PROPRIETARY-P */
Object contains_proprietary_p(block)
    Object block;
{
    Object current_filters_search_result;
    Declare_special(1);
    Object result;

    x_note_fn_call(180,195);
    current_filters_search_result = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_filters_search_result,Qcurrent_filters_search_result,current_filters_search_result,
	    0);
      contains_proprietary_p_1(block,Nil);
      result = VALUES_1(Current_filters_search_result);
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Contains_either_really_transient_or_proprietary_p_1, Qcontains_either_really_transient_or_proprietary_p_1);

/* CONTAINS-EITHER-REALLY-TRANSIENT-OR-PROPRIETARY-P-1 */
Object contains_either_really_transient_or_proprietary_p_1(block,
	    superior_block)
    Object block, superior_block;
{
    Object temp;

    x_note_fn_call(180,196);
    if (in_order_p(block)) {
	Current_filters_search_result = T;
	temp = Current_filters_search_result;
    }
    else if ((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
	    (SI_Long)262144L) &&  !((SI_Long)0L != (IFIX(ISVREF(block,
	    (SI_Long)5L)) & (SI_Long)131072L))) {
	Current_filters_search_result = T;
	temp = Current_filters_search_result;
    }
    else
	temp = funcall_function_to_inferior_blocks(block,
		Contains_either_really_transient_or_proprietary_p_1);
    return VALUES_1(temp);
}

/* CONTAINS-EITHER-REALLY-TRANSIENT-OR-PROPRIETARY-P */
Object contains_either_really_transient_or_proprietary_p(block)
    Object block;
{
    Object current_filters_search_result;
    Declare_special(1);
    Object result;

    x_note_fn_call(180,197);
    current_filters_search_result = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_filters_search_result,Qcurrent_filters_search_result,current_filters_search_result,
	    0);
      contains_either_really_transient_or_proprietary_p_1(block,Nil);
      result = VALUES_1(Current_filters_search_result);
    POP_SPECIAL();
    return result;
}

Object Info_for_restrictable_frame_system_operation_prop = UNBOUND;

static Object list_constant_22;    /* # */

static Object Qfree_text;          /* free-text */

static Object Qview_attribute;     /* view-attribute */

/* ATTRIBUTE-IS-VISIBLE-VIA-THE-TEXT-OF-P */
Object attribute_is_visible_via_the_text_of_p(frame,aliased_slot_name,
	    class_qualifier_qm)
    Object frame, aliased_slot_name, class_qualifier_qm;
{
    Object temp, x2, gensymed_symbol, sub_class_bit_vector, gensymed_symbol_4;
    Object slot_name_or_alias, class_description, defining_class;
    Object class_or_frame_qm, slot_description_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;

    x_note_fn_call(180,198);
    temp = memq_function(aliased_slot_name,list_constant_22);
    if (temp);
    else {
	if (SIMPLE_VECTOR_P(frame) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame)) > (SI_Long)2L &&  
		!EQ(ISVREF(frame,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(frame,(SI_Long)1L);
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
		    IFIX(ISVREF(Message_class_description,(SI_Long)18L));
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
	if (temp_1);
	else {
	    if (SIMPLE_VECTOR_P(frame) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(frame,(SI_Long)1L),
			Qavailable_frame_vector)) {
		x2 = ISVREF(frame,(SI_Long)1L);
		gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? x2 : Qnil;
	    }
	    else
		gensymed_symbol = Nil;
	    if (gensymed_symbol) {
		gensymed_symbol_4 = 
			lookup_global_or_kb_specific_property_value(Qfree_text,
			Class_description_gkbprop);
		if (gensymed_symbol_4) {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_4,(SI_Long)18L));
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
	}
	temp = temp_1 ? (EQ(aliased_slot_name,Qtext) ? T : Nil) : Nil;
    }
    if (temp)
	return VALUES_1(temp);
    else {
	slot_name_or_alias = aliased_slot_name;
	class_description = ISVREF(frame,(SI_Long)1L);
	defining_class = class_qualifier_qm;
	class_or_frame_qm = ISVREF(class_description,(SI_Long)1L);
	temp = get_slot_name_for_alias_if_any(slot_name_or_alias,
		class_or_frame_qm);
	if (temp);
	else
	    temp = slot_name_or_alias;
	slot_description_qm = 
		get_slot_description_of_class_description_function(temp,
		class_description,defining_class);
	if (slot_description_qm)
	    return attribute_operation_is_allowed_p(Qview_attribute,frame,
		    aliased_slot_name,ISVREF(slot_description_qm,(SI_Long)3L));
	else
	    return VALUES_1(Nil);
    }
}

/* FRAME-SYSTEM-OPERATION-IS-ALLOWED-P */
Object frame_system_operation_is_allowed_p(frame_system_operation,block)
    Object frame_system_operation, block;
{
    x_note_fn_call(180,199);
    return frame_or_attribute_operation_is_allowed_p(frame_system_operation,
	    block,Nil,Nil);
}

/* ATTRIBUTE-OPERATION-IS-ALLOWED-P */
Object attribute_operation_is_allowed_p(attribute_operation,block,
	    aliased_slot_name,defining_class)
    Object attribute_operation, block, aliased_slot_name, defining_class;
{
    x_note_fn_call(180,200);
    return frame_or_attribute_operation_is_allowed_p(attribute_operation,
	    block,aliased_slot_name,defining_class);
}

static Object Qedit_attribute;     /* edit-attribute */

/* EDIT-ATTRIBUTE-ALLOWED-P */
Object edit_attribute_allowed_p(frame,internal_slot_name,defining_class_qm)
    Object frame, internal_slot_name, defining_class_qm;
{
    Object defining_class, temp;

    x_note_fn_call(180,201);
    defining_class = defining_class_qm;
    if (defining_class);
    else
	defining_class = 
		ISVREF(get_slot_description_of_class_description_function(internal_slot_name,
		ISVREF(frame,(SI_Long)1L),Nil),(SI_Long)3L);
    temp = get_alias_for_slot_name_if_any(internal_slot_name,frame);
    if (temp);
    else
	temp = internal_slot_name;
    return attribute_operation_is_allowed_p(Qedit_attribute,frame,temp,
	    defining_class);
}

/* FRAME-OR-ATTRIBUTE-OPERATION-IS-ALLOWED-P */
Object frame_or_attribute_operation_is_allowed_p(frame_system_operation,
	    block,aliased_slot_name_qm,defining_class_qm)
    Object frame_system_operation, block, aliased_slot_name_qm;
    Object defining_class_qm;
{
    Object temp;

    x_note_fn_call(180,202);
    temp = Servicing_workstation_qm ? Current_g2_user_mode_qm : Qnil;
    if (temp);
    else
	temp = Qadministrator;
    return frame_or_attribute_operation_is_allowed_for_mode_p(frame_system_operation,
	    block,aliased_slot_name_qm,defining_class_qm,temp);
}

static Object Qinfo_for_restrictable_frame_system_operation;  /* info-for-restrictable-frame-system-operation */

static Object Qrestricted_if_it_is_proprietary;  /* restricted-if-it-is-proprietary */

static Object Qrestricted_if_it_contains_proprietary_or_when_runtime_contains_never_permanent_transients;  /* restricted-if-it-contains-proprietary-or-when-runtime-contains-never-permanent-transients */

static Object Qrestricted_if_it_contains_proprietary;  /* restricted-if-it-contains-proprietary */

static Object Qrestricted_if_slot_not_visible;  /* restricted-if-slot-not-visible */

static Object Qrestricted_by_these_input_operations_on_slot;  /* restricted-by-these-input-operations-on-slot */

static Object Qrestricted_by_these_input_operations_on_block;  /* restricted-by-these-input-operations-on-block */

static Object Qrestricted_if_all_attributes_are_not_visible;  /* restricted-if-all-attributes-are-not-visible */

/* FRAME-OR-ATTRIBUTE-OPERATION-IS-ALLOWED-FOR-MODE-P */
Object frame_or_attribute_operation_is_allowed_for_mode_p(frame_system_operation,
	    block,aliased_slot_name_qm,defining_class_qm,user_mode)
    Object frame_system_operation, block, aliased_slot_name_qm;
    Object defining_class_qm, user_mode;
{
    Object info_for_restrictable_frame_system_operation;
    Object how_implicitly_restricted, optional_args, ab_loop_list_;
    Object ab_loop_desetq_, current_g2_user_mode_qm;
    Object choices_that_imply_restriction, choice_restrictions, permitted_qm;
    Object choice, result_1, ab_loop_it_, non_menu_choice, ab_loop_list__1;
    Object slot_names;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(180,203);
    info_for_restrictable_frame_system_operation = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(frame_system_operation),
	    Qinfo_for_restrictable_frame_system_operation);
    how_implicitly_restricted = Nil;
    optional_args = Nil;
    ab_loop_list_ = info_for_restrictable_frame_system_operation;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    how_implicitly_restricted = CAR(ab_loop_desetq_);
    optional_args = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(how_implicitly_restricted,Qrestricted_if_it_is_proprietary)) {
	if (in_order_p(block))
	    return VALUES_1(Nil);
    }
    else if (EQ(how_implicitly_restricted,
	    Qrestricted_if_it_contains_proprietary_or_when_runtime_contains_never_permanent_transients)) 
		{
	if (Nil ? 
		TRUEP(contains_either_really_transient_or_proprietary_p(block)) 
		: TRUEP(contains_proprietary_p(block)))
	    return VALUES_1(Nil);
    }
    else if (EQ(how_implicitly_restricted,
	    Qrestricted_if_it_contains_proprietary)) {
	if (contains_proprietary_p(block))
	    return VALUES_1(Nil);
    }
    else if (EQ(how_implicitly_restricted,Qrestricted_if_slot_not_visible)) {
	current_g2_user_mode_qm = user_mode;
	PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
		0);
	  result = include_slot_in_attribute_table_p(block,
		  aliased_slot_name_qm,defining_class_qm);
	POP_SPECIAL();
	return result;
    }
    else if (EQ(how_implicitly_restricted,
	    Qrestricted_by_these_input_operations_on_slot)) {
	choices_that_imply_restriction = optional_args;
	current_g2_user_mode_qm = user_mode;
	PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
		0);
	  result = compute_menu_restrictions_for_click_on_table(block,
		  aliased_slot_name_qm,defining_class_qm);
	POP_SPECIAL();
	MVS_2(result,choice_restrictions,permitted_qm);
	if (permitted_qm) {
	    choice = Nil;
	    ab_loop_list_ = choices_that_imply_restriction;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    choice = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(memq_function(choice,choice_restrictions))) {
		result_1 = Nil;
		goto end_1;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    result_1 = T;
	    goto end_1;
	    result_1 = Qnil;
	  end_1:;
	}
	else {
	    choice = Nil;
	    ab_loop_list_ = choices_that_imply_restriction;
	    ab_loop_it_ = Nil;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    choice = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = memq_function(choice,choice_restrictions);
	    if (ab_loop_it_) {
		temp = TRUEP(ab_loop_it_);
		goto end_2;
	    }
	    goto next_loop_2;
	  end_loop_2:
	    temp = TRUEP(Qnil);
	  end_2:;
	    result_1 =  !temp ? T : Nil;
	}
	reclaim_filter_list_1(choice_restrictions);
	return VALUES_1(result_1);
    }
    else if (EQ(how_implicitly_restricted,
	    Qrestricted_by_these_input_operations_on_block)) {
	choices_that_imply_restriction = optional_args;
	current_g2_user_mode_qm = user_mode;
	PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
		0);
	  non_menu_choice = Nil;
	  ab_loop_list__1 = choices_that_imply_restriction;
	next_loop_3:
	  if ( !TRUEP(ab_loop_list__1))
	      goto end_loop_3;
	  non_menu_choice = M_CAR(ab_loop_list__1);
	  ab_loop_list__1 = M_CDR(ab_loop_list__1);
	  if ( !TRUEP(non_menu_choice_permitted_p(non_menu_choice,block))) {
	      temp = TRUEP(Nil);
	      goto end_3;
	  }
	  goto next_loop_3;
	end_loop_3:
	  temp = TRUEP(T);
	  goto end_3;
	  temp = TRUEP(Qnil);
	end_3:;
	POP_SPECIAL();
	if ( !temp)
	    return VALUES_1(Nil);
    }
    else if (EQ(how_implicitly_restricted,
	    Qrestricted_if_all_attributes_are_not_visible)) {
	current_g2_user_mode_qm = user_mode;
	PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
		0);
	  result = compute_visible_slots_for_attribute_table(block);
	POP_SPECIAL();
	MVS_2(result,slot_names,permitted_qm);
	if (permitted_qm &&  !TRUEP(slot_names))
	    return VALUES_1(Nil);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(T);
    return VALUES_1(Qnil);
}

/* FILTER-RESTRICTIONS-FOR-ITEM */
Object filter_restrictions_for_item(item_or_class_description_qm,keywords,
	    simple_compiled_function,filtering_visibility_restrictions_qm)
    Object item_or_class_description_qm, keywords, simple_compiled_function;
    Object filtering_visibility_restrictions_qm;
{
    Object x2, proprietary_qm, traversing_class_hierarchy_qm;
    Object the_class_inheritance_path, original_item_or_class_description_qm;
    Object frame_with_modified_superior_qm, class_description_qm, location;
    Object object_configuration, clause, ab_loop_list_, mode_restriction;
    Object ab_loop_list__1, mode_list, temp_1, restriction_clause;
    Object ab_loop_list__2, operation_type, restriction_type;
    Object the_class_inheritance_path_old_value, class_name, defn;
    char temp;

    x_note_fn_call(180,204);
    if (item_or_class_description_qm) {
	if (SIMPLE_VECTOR_P(item_or_class_description_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_class_description_qm)) 
		> (SI_Long)2L &&  !EQ(ISVREF(item_or_class_description_qm,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_class_description_qm,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    proprietary_qm = temp ? in_order_p(item_or_class_description_qm) : Nil;
    traversing_class_hierarchy_qm = Nil;
    the_class_inheritance_path = Nil;
    original_item_or_class_description_qm = item_or_class_description_qm;
    frame_with_modified_superior_qm = Superior_frame_for_restrictions_frame_qm;
    if (SIMPLE_VECTOR_P(original_item_or_class_description_qm) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(original_item_or_class_description_qm)) 
	    > (SI_Long)2L &&  
	    !EQ(ISVREF(original_item_or_class_description_qm,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(original_item_or_class_description_qm,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	class_description_qm = 
		ISVREF(original_item_or_class_description_qm,(SI_Long)1L);
    else if (SIMPLE_VECTOR_P(original_item_or_class_description_qm) && 
	    EQ(ISVREF(original_item_or_class_description_qm,(SI_Long)0L),
	    Qg2_defstruct_structure_name_class_description_g2_struct))
	class_description_qm = original_item_or_class_description_qm;
    else
	class_description_qm = Qnil;
    location = Nil;
    if (location);
    else {
	if (SIMPLE_VECTOR_P(original_item_or_class_description_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(original_item_or_class_description_qm)) 
		> (SI_Long)2L &&  
		!EQ(ISVREF(original_item_or_class_description_qm,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(original_item_or_class_description_qm,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	location = temp ? original_item_or_class_description_qm : 
		Kb_restrictions;
    }
    object_configuration = Nil;
  next_loop:
    if ( !TRUEP(location))
	goto end_loop;
    if ( !TRUEP(traversing_class_hierarchy_qm))
	object_configuration = get_lookup_slot_value(location,
		Qobject_configuration);
    else {
	if (SIMPLE_VECTOR_P(location) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(location)) > (SI_Long)2L && 
		 !EQ(ISVREF(location,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(location,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if ( !temp)
	    object_configuration = Nil;
	else
	    object_configuration = ISVREF(location,(SI_Long)23L);
    }
    clause = Nil;
    ab_loop_list_ = object_configuration;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    clause = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (memq_function(FIRST(clause),list_constant_4)) {
	mode_restriction = Nil;
	ab_loop_list__1 = CDR(clause);
	mode_list = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_2;
	mode_restriction = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	mode_list = SECOND(mode_restriction);
	temp_1 = FIRST(mode_restriction);
	if (EQ(temp_1,Qwhen))
	    temp_1 = memq_function(Current_g2_user_mode_qm,mode_list);
	else if (EQ(temp_1,Qunless))
	    temp_1 =  !EQ(Current_g2_user_mode_qm,Qadministrator) ? ( 
		    !TRUEP(memq_function(Current_g2_user_mode_qm,
		    mode_list)) ? T : Nil) : Qnil;
	else
	    temp_1 = Qnil;
	if (temp_1) {
	    restriction_clause = Nil;
	    ab_loop_list__2 = CDDR(mode_restriction);
	    operation_type = Nil;
	    restriction_type = Nil;
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list__2))
		goto end_loop_3;
	    restriction_clause = M_CAR(ab_loop_list__2);
	    ab_loop_list__2 = M_CDR(ab_loop_list__2);
	    operation_type = FIRST(restriction_clause);
	    temp_1 = FIRST(restriction_clause);
	    if (EQ(temp_1,Qmain_menu) || EQ(temp_1,Qglobal_keyboard_command))
		restriction_type = SECOND(restriction_clause);
	    else if (EQ(temp_1,Qworkspace_menu) || EQ(temp_1,Qnon_menu))
		restriction_type = THIRD(restriction_clause);
	    else if (EQ(temp_1,Qvisibility) || EQ(temp_1,Qtable))
		restriction_type = FOURTH(restriction_clause);
	    else if (EQ(temp_1,Qselecting)) {
		temp_1 = THIRD(restriction_clause);
		restriction_type = EQ(temp_1,Qnothing) ? Qdoes : Qimplies;
	    }
	    else if (EQ(temp_1,Qselecting_absolutely)) {
		temp_1 = THIRD(restriction_clause);
		restriction_type = EQ(temp_1,Qnothing) ? Qdoes_absolutely :
			 Qimplies_absolutely;
	    }
	    else
		restriction_type = Qnil;
	    if (memq_function(operation_type,keywords) && ( 
		    !TRUEP(Conditional_selected_choice_qm) &&  
		    !TRUEP(Conditional_termination_state_qm) || 
		    EQ(operation_type,Qselecting_absolutely) || 
		    EQ(restriction_type,Qexclude_absolutely))) {
		if (inline_funcall_3(simple_compiled_function,
			restriction_clause,item_or_class_description_qm,
			location))
		    goto end_standard_search;
	    }
	    goto next_loop_3;
	  end_loop_3:;
	}
	goto next_loop_2;
      end_loop_2:;
    }
    else if (EQ(FIRST(clause),Qproprietary)) {
	temp = TRUEP(proprietary_qm);
	if (temp);
	else {
	    if (traversing_class_hierarchy_qm) {
		if (SIMPLE_VECTOR_P(location) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(location)) > 
			(SI_Long)2L &&  !EQ(ISVREF(location,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(location,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	    temp = temp ? TRUEP(in_order_p(location)) : TRUEP(Nil);
	}
	if (temp) {
	    restriction_clause = Nil;
	    ab_loop_list__1 = CDR(clause);
	    operation_type = Nil;
	    restriction_type = Nil;
	  next_loop_4:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_4;
	    restriction_clause = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    operation_type = FIRST(restriction_clause);
	    temp_1 = FIRST(restriction_clause);
	    if (EQ(temp_1,Qmain_menu) || EQ(temp_1,Qglobal_keyboard_command))
		restriction_type = SECOND(restriction_clause);
	    else if (EQ(temp_1,Qworkspace_menu) || EQ(temp_1,Qnon_menu))
		restriction_type = THIRD(restriction_clause);
	    else if (EQ(temp_1,Qvisibility) || EQ(temp_1,Qtable))
		restriction_type = FOURTH(restriction_clause);
	    else if (EQ(temp_1,Qselecting)) {
		temp_1 = THIRD(restriction_clause);
		restriction_type = EQ(temp_1,Qnothing) ? Qdoes : Qimplies;
	    }
	    else if (EQ(temp_1,Qselecting_absolutely)) {
		temp_1 = THIRD(restriction_clause);
		restriction_type = EQ(temp_1,Qnothing) ? Qdoes_absolutely :
			 Qimplies_absolutely;
	    }
	    else
		restriction_type = Qnil;
	    if (memq_function(operation_type,keywords) && ( 
		    !TRUEP(Conditional_selected_choice_qm) &&  
		    !TRUEP(Conditional_termination_state_qm) || 
		    EQ(operation_type,Qselecting_absolutely) || 
		    EQ(restriction_type,Qexclude_absolutely))) {
		if (inline_funcall_3(simple_compiled_function,
			restriction_clause,item_or_class_description_qm,
			location))
		    goto end_standard_search;
	    }
	    goto next_loop_4;
	  end_loop_4:;
	}
    }
    goto next_loop_1;
  end_loop_1:;
    if (traversing_class_hierarchy_qm) {
	the_class_inheritance_path_old_value = the_class_inheritance_path;
	temp_1 = FIRST(the_class_inheritance_path_old_value);
	the_class_inheritance_path = 
		REST(the_class_inheritance_path_old_value);
	class_name = temp_1;
	defn = class_name &&  !EQ(class_name,Qitem) ? 
		lookup_global_or_kb_specific_property_value(class_name,
		Class_definition_gkbprop) : Qnil;
	location = CONSP(defn) ? class_name : defn;
    }
    else if (EQ(location,Kb_restrictions)) {
	if (class_description_qm) {
	    traversing_class_hierarchy_qm = T;
	    the_class_inheritance_path = ISVREF(class_description_qm,
		    (SI_Long)2L);
	    the_class_inheritance_path_old_value = the_class_inheritance_path;
	    temp_1 = FIRST(the_class_inheritance_path_old_value);
	    the_class_inheritance_path = 
		    REST(the_class_inheritance_path_old_value);
	    class_name = temp_1;
	    defn = class_name ? 
		    lookup_global_or_kb_specific_property_value(class_name,
		    Class_definition_gkbprop) : Qnil;
	    location = CONSP(defn) ? class_name : defn;
	}
	else
	    location = Nil;
    }
    else if (EQ(location,frame_with_modified_superior_qm)) {
	frame_with_modified_superior_qm = Nil;
	location = Superior_frame_for_restrictions_superior_qm;
    }
    else {
	location = superior_frame(location);
	if (location);
	else
	    location = Kb_restrictions;
    }
    goto next_loop;
  end_loop:;
  end_standard_search:;
    if (filtering_visibility_restrictions_qm)
	return VALUES_1(Conditional_termination_state_qm);
    else if (Absolutely_selected_choice_qm) {
	reclaim_permitted_restriction_set();
	reclaim_prohibited_restriction_set();
	if (memq_function(Absolutely_selected_choice_qm,
		Absolutely_prohibited_restriction_set) || 
		EQ(Absolutely_selected_choice_qm,Choice_conflict)) {
	    reclaim_absolutely_prohibited_restriction_set();
	    return VALUES_3(Nil,Nil,Qnothing);
	}
	else {
	    reclaim_absolutely_prohibited_restriction_set();
	    return VALUES_3(Nil,Nil,Absolutely_selected_choice_qm);
	}
    }
    else if (Conditional_selected_choice_qm) {
	reclaim_permitted_restriction_set();
	reclaim_prohibited_restriction_set();
	if (memq_function(Conditional_selected_choice_qm,
		Absolutely_prohibited_restriction_set)) {
	    reclaim_absolutely_prohibited_restriction_set();
	    return VALUES_3(Nil,Nil,Qnothing);
	}
	else {
	    reclaim_absolutely_prohibited_restriction_set();
	    return VALUES_3(Nil,Nil,Conditional_selected_choice_qm);
	}
    }
    else if (EQ(Conditional_termination_state_qm,Qpermitted)) {
	reclaim_prohibited_restriction_set();
	reclaim_absolutely_prohibited_restriction_set();
	return VALUES_2(Permitted_restriction_set,T);
    }
    else {
	reclaim_permitted_restriction_set();
	reclaim_absolutely_prohibited_restriction_set();
	return VALUES_2(Prohibited_restriction_set,Nil);
    }
}

/* COMPUTE-USER-RESTRICTIONS-IN-KB-RESTRICTIONS */
Object compute_user_restrictions_in_kb_restrictions(user_restrictions_in_slot_of_kb_restrictions)
    Object user_restrictions_in_slot_of_kb_restrictions;
{
    Object permitted_set, prohibited_set, absolutely_prohibited_set;
    Object termination_state_qm, mode_restriction, ab_loop_list_;
    Object restricted_mode_qm, restriction_clause, ab_loop_list__1;
    Object restriction_type, additions;

    x_note_fn_call(180,205);
    if (EQ(Current_g2_user_mode_qm,Qadministrator))
	return VALUES_2(Nil,Nil);
    else {
	permitted_set = Nil;
	prohibited_set = Nil;
	absolutely_prohibited_set = Nil;
	termination_state_qm = Nil;
	mode_restriction = Nil;
	ab_loop_list_ = user_restrictions_in_slot_of_kb_restrictions;
	restricted_mode_qm = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	mode_restriction = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	restricted_mode_qm = memq_function(Current_g2_user_mode_qm,
		SECOND(mode_restriction));
	if (EQ(FIRST(mode_restriction),Qwhen) ? TRUEP(restricted_mode_qm) :
		  !TRUEP(restricted_mode_qm)) {
	    restriction_clause = Nil;
	    ab_loop_list__1 = CDDR(mode_restriction);
	    restriction_type = Nil;
	    additions = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_1;
	    restriction_clause = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    restriction_type = SECOND(restriction_clause);
	    additions = CDDR(restriction_clause);
	    if (EQ(restriction_type,Qinclude) || EQ(restriction_type,
		    Qinclude_additionally)) {
		if ( !TRUEP(termination_state_qm)) {
		    permitted_set = 
			    compute_new_restriction_set(permitted_set,
			    additions,prohibited_set,
			    absolutely_prohibited_set);
		    if (EQ(restriction_type,Qinclude))
			termination_state_qm = Qinclude;
		}
	    }
	    else if (EQ(restriction_type,Qexclude) || EQ(restriction_type,
		    Qexclude_additionally)) {
		if ( !TRUEP(termination_state_qm)) {
		    prohibited_set = 
			    compute_new_restriction_set(prohibited_set,
			    additions,permitted_set,Nil);
		    if (EQ(restriction_type,Qexclude))
			termination_state_qm = Qexclude;
		}
	    }
	    else if (EQ(restriction_type,Qexclude_absolutely)) {
		absolutely_prohibited_set = 
			compute_new_restriction_set(absolutely_prohibited_set,
			additions,Nil,Nil);
		permitted_set = remove_from_restriction_set(permitted_set,
			additions);
		prohibited_set = 
			compute_new_restriction_set(prohibited_set,
			additions,Nil,Nil);
	    }
	    goto next_loop_1;
	  end_loop_1:;
	}
	goto next_loop;
      end_loop:
	if (EQ(termination_state_qm,Qinclude)) {
	    reclaim_filter_list_1(prohibited_set);
	    reclaim_filter_list_1(absolutely_prohibited_set);
	    return VALUES_2(permitted_set,T);
	}
	else {
	    reclaim_filter_list_1(permitted_set);
	    reclaim_filter_list_1(absolutely_prohibited_set);
	    return VALUES_2(prohibited_set,Nil);
	}
	return VALUES_1(Qnil);
    }
}

static Object Qsimulated_optional_modules;  /* simulated-optional-modules */

/* SETUP-CURRENT-SIMULATED-PRODUCT-AUTHORIZATION */
Object setup_current_simulated_product_authorization()
{
    Object simulating_p, atomic_products_authorized_1;

    x_note_fn_call(180,206);
    simulating_p = system_table_installed_p(Kb_restrictions) ? ( !EQ(Qt,
	    get_lookup_slot_value_given_default(Kb_restrictions,
	    Qsimulated_optional_modules,T)) ? T : Nil) : Qnil;
    atomic_products_authorized_1 = atomic_products_authorized(simulating_p 
	    ? get_lookup_slot_value_given_default(Kb_restrictions,
	    Qsimulated_optional_modules,T) : 
	    Authorized_products_of_this_machine);
    delete_frame_note_if_any(Qnote_status_of_simulated_product_authorization,
	    Kb_restrictions);
    setup_atomic_products_for_simulation(atomic_products_authorized_1);
    if (simulating_p)
	add_frame_note(2,Qnote_status_of_simulated_product_authorization,
		Kb_restrictions);
    optimize_telewindows_z_layer_model();
    start_adaptive_font_fallback();
    invoke_interlace_abstraction_if_offered();
    return reclaim_slot_value_list_1(atomic_products_authorized_1);
}

static Object Qsimulation_state;   /* simulation-state */

/* SETUP-ATOMIC-PRODUCTS-FOR-SIMULATION */
Object setup_atomic_products_for_simulation(list_of_atomic_products)
    Object list_of_atomic_products;
{
    Object product, atomic_product_p, ab_loop_list_, simulated_state_qm;
    Object ab_loop_desetq_, temp, second_new_value;

    x_note_fn_call(180,207);
    product = Nil;
    atomic_product_p = Nil;
    ab_loop_list_ = Optional_modules_map;
    simulated_state_qm = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    product = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    atomic_product_p = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    simulated_state_qm = get(product,Qsimulation_state,_);
    if (atomic_product_p) {
	second_new_value = memq_function(product,list_of_atomic_products) ?
		 FIRST(simulated_state_qm) : Nil;
	M_SECOND(simulated_state_qm) = second_new_value;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qoffline;            /* offline */

static Object list_constant_23;    /* # */

/* ATOMIC-PRODUCTS-AUTHORIZED */
Object atomic_products_authorized(visible_products_authorized)
    Object visible_products_authorized;
{
    Object result_1, visible_product, ab_loop_list_, visible_product_bits;
    Object atomic_product_p, ab_loop_desetq_, temp;
    Object slot_value_modify_macro_using_test_arg_1, car_1, cdr_1, key_result;
    Object x_element, ab_loop_list__1, ab_loop_it_, known_product;
    Object known_product_bits, known_atomic_product_p, ab_loop_list__2;
    Object disabled_product;
    char temp_1;

    x_note_fn_call(180,208);
    result_1 = Nil;
    visible_product = Nil;
    ab_loop_list_ = visible_products_authorized;
    visible_product_bits = Nil;
    atomic_product_p = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    visible_product = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_desetq_ = assq_function(visible_product,Optional_modules_map);
    temp = CDR(ab_loop_desetq_);
    visible_product_bits = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    atomic_product_p = CAR(temp);
    if (atomic_product_p) {
	slot_value_modify_macro_using_test_arg_1 = visible_product;
	car_1 = slot_value_modify_macro_using_test_arg_1;
	cdr_1 = result_1;
	key_result = car_1;
	x_element = Nil;
	ab_loop_list__1 = cdr_1;
	ab_loop_it_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	x_element = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	ab_loop_it_ = EQL(key_result,x_element) ? T : Nil;
	if (ab_loop_it_) {
	    temp_1 = TRUEP(ab_loop_it_);
	    goto end_1;
	}
	goto next_loop_1;
      end_loop_1:
	temp_1 = TRUEP(Qnil);
      end_1:;
	result_1 = temp_1 ? cdr_1 : slot_value_cons_1(car_1,cdr_1);
    }
    else {
	known_product = Nil;
	known_product_bits = Nil;
	known_atomic_product_p = Nil;
	ab_loop_list__1 = Optional_modules_map;
	ab_loop_desetq_ = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_2;
	ab_loop_desetq_ = M_CAR(ab_loop_list__1);
	known_product = CAR(ab_loop_desetq_);
	temp = CDR(ab_loop_desetq_);
	known_product_bits = CAR(temp);
	temp = CDR(ab_loop_desetq_);
	temp = CDR(temp);
	known_atomic_product_p = CAR(temp);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if (known_atomic_product_p) {
	    if ( !FIXNUM_ZEROP(FIXNUM_LOGAND(known_product_bits,
		    visible_product_bits))) {
		slot_value_modify_macro_using_test_arg_1 = known_product;
		car_1 = slot_value_modify_macro_using_test_arg_1;
		cdr_1 = result_1;
		key_result = car_1;
		x_element = Nil;
		ab_loop_list__2 = cdr_1;
		ab_loop_it_ = Nil;
	      next_loop_3:
		if ( !TRUEP(ab_loop_list__2))
		    goto end_loop_3;
		x_element = M_CAR(ab_loop_list__2);
		ab_loop_list__2 = M_CDR(ab_loop_list__2);
		ab_loop_it_ = EQL(key_result,x_element) ? T : Nil;
		if (ab_loop_it_) {
		    temp_1 = TRUEP(ab_loop_it_);
		    goto end_2;
		}
		goto next_loop_3;
	      end_loop_3:
		temp_1 = TRUEP(Qnil);
	      end_2:;
		result_1 = temp_1 ? cdr_1 : slot_value_cons_1(car_1,cdr_1);
	    }
	}
	goto next_loop_2;
      end_loop_2:;
    }
    goto next_loop;
  end_loop:
    if (memq_function(Qoffline,visible_products_authorized)) {
	disabled_product = Nil;
	ab_loop_list_ = list_constant_23;
      next_loop_4:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_4;
	disabled_product = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(memq_function(disabled_product,
		visible_products_authorized)))
	    result_1 = delete_slot_value_element_1(disabled_product,result_1);
	goto next_loop_4;
      end_loop_4:;
    }
    return VALUES_1(result_1);
    return VALUES_1(Qnil);
}

/* WRITE-PSUEUDO-AUTHORIZED-OPTIONAL-MODULES-FROM-SLOT */
Object write_psueudo_authorized_optional_modules_from_slot(value,
	    gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(180,209);
    return write_symbol_list(1,Authorized_products_of_this_machine);
}

static Object string_constant_125;  /* "do not simulate" */

/* WRITE-SIMULATED-PRODUCTS?-FROM-SLOT */
Object write_simulated_products_qm_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(180,210);
    if (EQ(value,Qt))
	return tformat(1,string_constant_125);
    else
	return write_symbol_list(1,value);
}

/* COMPILE-SIMULATED-PRODUCTS?-FOR-SLOT */
Object compile_simulated_products_qm_for_slot varargs_1(int, n)
{
    Object parse, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(180,211);
    INIT_ARGS_nonrelocating();
    parse = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (CONSP(parse))
	return VALUES_1(REST(parse));
    else if (EQ(Qnone,parse))
	return VALUES_1(Nil);
    else if (EQ(Qt,parse))
	return VALUES_1(parse);
    else if (ATOM(parse))
	return phrase_cons(parse,Nil);
    else
	return VALUES_1(parse);
}

/* PUT-SIMULATED-OPTIONAL-MODULES */
Object put_simulated_optional_modules(kb_restrictions_instance,
	    simulated_products_qm,gensymed_symbol)
    Object kb_restrictions_instance, simulated_products_qm, gensymed_symbol;
{
    x_note_fn_call(180,212);
    set_non_savable_lookup_slot_value(kb_restrictions_instance,
	    Qsimulated_optional_modules,simulated_products_qm);
    if (system_table_installed_p(kb_restrictions_instance))
	setup_current_simulated_product_authorization();
    return VALUES_1(simulated_products_qm);
}

static Object list_constant_24;    /* # */

static Object string_constant_126;  /* "G2 is currently simulating ~A ~A license for this machine with the following details." */

static Object string_constant_127;  /* "an" */

static Object string_constant_128;  /* "a" */

static Object list_constant_25;    /* # */

static Object string_constant_129;  /* "  Warning: the simulation does not include ~L,| ~
				     *                   because ~a not licensed."
				     */

static Object string_constant_130;  /* "they are" */

static Object string_constant_131;  /* "it is" */

static Object string_constant_132;  /* "  Warning: you cannot simulate ~A ~A license on this machine." */

static Object string_constant_133;  /* "  The simulation includes ~L,&." */

static Object string_constant_134;  /* "  Licensed only for OFFLINE." */

static Object string_constant_135;  /* "  Simulating the limited OFFLINE license." */

static Object string_constant_136;  /* "  The ~S package is included, but ~L,& ~
				     *                     ~a not included because of OFFLINE."
				     */

static Object string_constant_137;  /* "are" */

static Object string_constant_138;  /* "is" */

static Object string_constant_139;  /* "  The simulation does not include ~L,|." */

/* WRITE-NOTE-STATUS-OF-SIMULATED-PRODUCT-AUTHORIZATION-NOTE */
Object write_note_status_of_simulated_product_authorization_note(particulars,
	    gensymed_symbol)
    Object particulars, gensymed_symbol;
{
    Object temp, simulated_optional_modules, write_symbols_in_lower_case_qm;
    Object offline_is_forced_qm, offline_is_simulated_qm, forced_license_level;
    Object simulated_license_level, result_1, p, ab_loop_list_;
    Object visible_atomic_products_suppressed_by_offline;
    Object visible_atomic_products_forced_to_not_simulate;
    Object visible_atomic_products_not_being_simulated;
    Object visible_atomic_products_being_simulated;
    Object visible_non_atomic_products_being_simulated, visible_product;
    Object visible_bits, atomic_p, invisible_p, ab_loop_desetq_;
    Object simulated_product, ab_loop_list__1, simulated_bits, ab_loop_it_;
    Object minimum_license, non_atomic_product;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(180,213);
    temp = get_lookup_slot_value_given_default(Kb_restrictions,
	    Qsimulated_optional_modules,T);
    if (LISTP(temp)) {
	simulated_optional_modules = 
		get_lookup_slot_value_given_default(Kb_restrictions,
		Qsimulated_optional_modules,T);
	write_symbols_in_lower_case_qm = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
		0);
	  offline_is_forced_qm = memq_function(Qoffline,
		  Authorized_products_of_this_machine);
	  offline_is_simulated_qm = memq_function(Qoffline,
		  get_lookup_slot_value_given_default(Kb_restrictions,
		  Qsimulated_optional_modules,T));
	  forced_license_level = 
		  license_level(Authorized_products_of_this_machine);
	  simulated_license_level = license_level(simulated_optional_modules);
	  if (offline_is_forced_qm || offline_is_simulated_qm) {
	      result_1 = Nil;
	      p = Nil;
	      ab_loop_list_ = list_constant_24;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      p = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      if (offline_is_forced_qm &&  !TRUEP(memq_function(p,
		      Authorized_products_of_this_machine)) || 
		      offline_is_simulated_qm &&  !TRUEP(memq_function(p,
		      simulated_optional_modules)))
		  result_1 = slot_value_cons_1(p,result_1);
	      goto next_loop;
	    end_loop:
	      visible_atomic_products_suppressed_by_offline = result_1;
	      goto end_1;
	      visible_atomic_products_suppressed_by_offline = Qnil;
	    end_1:;
	  }
	  else
	      visible_atomic_products_suppressed_by_offline = Nil;
	  visible_atomic_products_forced_to_not_simulate = Nil;
	  visible_atomic_products_not_being_simulated = Nil;
	  visible_atomic_products_being_simulated = Nil;
	  visible_non_atomic_products_being_simulated = Nil;
	  visible_product = Nil;
	  visible_bits = Nil;
	  atomic_p = Nil;
	  invisible_p = Nil;
	  ab_loop_list_ = Optional_modules_map;
	  ab_loop_desetq_ = Nil;
	next_loop_1:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_1;
	  ab_loop_desetq_ = M_CAR(ab_loop_list_);
	  visible_product = CAR(ab_loop_desetq_);
	  temp = CDR(ab_loop_desetq_);
	  visible_bits = CAR(temp);
	  temp = CDR(ab_loop_desetq_);
	  temp = CDR(temp);
	  atomic_p = CAR(temp);
	  temp = CDR(ab_loop_desetq_);
	  temp = CDR(temp);
	  temp = CDR(temp);
	  invisible_p = CAR(temp);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if ( !TRUEP(invisible_p)) {
	      if (atomic_p &&  !TRUEP(memq_function(visible_product,
		      visible_atomic_products_suppressed_by_offline))) {
		  simulated_product = Nil;
		  ab_loop_list__1 = simulated_optional_modules;
		  simulated_bits = Nil;
		  ab_loop_it_ = Nil;
		  ab_loop_desetq_ = Nil;
		next_loop_2:
		  if ( !TRUEP(ab_loop_list__1))
		      goto end_loop_2;
		  simulated_product = M_CAR(ab_loop_list__1);
		  ab_loop_list__1 = M_CDR(ab_loop_list__1);
		  ab_loop_desetq_ = assq_function(simulated_product,
			  Optional_modules_map);
		  temp = CDR(ab_loop_desetq_);
		  simulated_bits = CAR(temp);
		  ab_loop_it_ =  
			  !FIXNUM_ZEROP(FIXNUM_LOGAND(simulated_bits,
			  visible_bits)) ? T : Nil;
		  if (ab_loop_it_) {
		      temp_1 = TRUEP(ab_loop_it_);
		      goto end_2;
		  }
		  goto next_loop_2;
		end_loop_2:
		  temp_1 = TRUEP(Qnil);
		end_2:;
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if (temp_1) {
		  if (visible_atomic_product_maybe_simulated_on_this_machine_p(visible_product))
		      visible_atomic_products_being_simulated = 
			      slot_value_cons_1(visible_product,
			      visible_atomic_products_being_simulated);
		  else
		      visible_atomic_products_forced_to_not_simulate = 
			      slot_value_cons_1(visible_product,
			      visible_atomic_products_forced_to_not_simulate);
	      }
	      else if (atomic_p)
		  visible_atomic_products_not_being_simulated = 
			  slot_value_cons_1(visible_product,
			  visible_atomic_products_not_being_simulated);
	      else if (EQ(Qoffline,visible_product));
	      else if (memq_function(visible_product,
		      simulated_optional_modules))
		  visible_non_atomic_products_being_simulated = 
			  slot_value_cons_1(visible_product,
			  visible_non_atomic_products_being_simulated);
	  }
	  goto next_loop_1;
	end_loop_1:;
	  minimum_license = FIXNUM_MIN(forced_license_level,
		  simulated_license_level);
	  tformat(3,string_constant_126,(SI_Long)0L == 
		  IFIX(minimum_license) ? string_constant_127 : 
		  string_constant_128,getf(list_constant_25,
		  minimum_license,_));
	  if (visible_atomic_products_forced_to_not_simulate)
	      tformat(3,string_constant_129,
		      visible_atomic_products_forced_to_not_simulate,
		      CDR(visible_atomic_products_forced_to_not_simulate) ?
		       string_constant_130 : string_constant_131);
	  if (FIXNUM_LT(forced_license_level,simulated_license_level))
	      tformat(3,string_constant_132,(SI_Long)0L == 
		      IFIX(simulated_license_level) ? string_constant_127 :
		       string_constant_128,getf(list_constant_25,
		      simulated_license_level,_));
	  if (visible_atomic_products_being_simulated)
	      tformat(2,string_constant_133,
		      visible_atomic_products_being_simulated);
	  if (offline_is_forced_qm)
	      tformat(1,string_constant_134);
	  if (offline_is_simulated_qm)
	      tformat(1,string_constant_135);
	  if (visible_non_atomic_products_being_simulated && 
		  visible_atomic_products_suppressed_by_offline) {
	      non_atomic_product = Nil;
	      ab_loop_list_ = visible_non_atomic_products_being_simulated;
	    next_loop_3:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_3;
	      non_atomic_product = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      tformat(4,string_constant_136,non_atomic_product,
		      visible_atomic_products_suppressed_by_offline,
		      CDR(visible_atomic_products_suppressed_by_offline) ? 
		      string_constant_137 : string_constant_138);
	      goto next_loop_3;
	    end_loop_3:;
	  }
	  if (visible_atomic_products_not_being_simulated)
	      tformat(2,string_constant_139,
		      visible_atomic_products_not_being_simulated);
	  reclaim_slot_value_list_1(visible_atomic_products_forced_to_not_simulate);
	  reclaim_slot_value_list_1(visible_atomic_products_suppressed_by_offline);
	  reclaim_slot_value_list_1(visible_atomic_products_not_being_simulated);
	  reclaim_slot_value_list_1(visible_atomic_products_being_simulated);
	  temp = 
		  reclaim_slot_value_list_1(visible_non_atomic_products_being_simulated);
	POP_SPECIAL();
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object Qembedded;           /* embedded */

static Object Qruntime;            /* runtime */

static Object Qrestricted_use;     /* restricted-use */

/* LICENSE-LEVEL */
Object license_level(authorized_products)
    Object authorized_products;
{
    Object product, ab_loop_list_, temp;

    x_note_fn_call(180,214);
    product = Nil;
    ab_loop_list_ = authorized_products;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    product = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(product,Qembedded)) {
	temp = FIX((SI_Long)0L);
	goto end_1;
    }
    else if (EQ(product,Qruntime)) {
	temp = FIX((SI_Long)1L);
	goto end_1;
    }
    else if (EQ(product,Qrestricted_use)) {
	temp = FIX((SI_Long)2L);
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(FIX((SI_Long)3L));
}

static Object Qg1;                 /* g1 */

/* VISIBLE-ATOMIC-PRODUCT-MAYBE-SIMULATED-ON-THIS-MACHINE-P */
Object visible_atomic_product_maybe_simulated_on_this_machine_p(product)
    Object product;
{
    Object temp, code, authorized_product, ab_loop_list_, product_bits;
    Object atomic_p, invisible_p, ab_loop_desetq_;

    x_note_fn_call(180,215);
    temp = memq_function(product,Authorized_products_of_this_machine);
    if (temp);
    else
	temp = EQ(product,Qg1) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else {
	code = M_CAR(M_CDR(assq_function(product,Optional_modules_map)));
	authorized_product = Nil;
	ab_loop_list_ = Authorized_products_of_this_machine;
	product_bits = Nil;
	atomic_p = Nil;
	invisible_p = Nil;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	authorized_product = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_desetq_ = assq_function(authorized_product,
		Optional_modules_map);
	temp = CDR(ab_loop_desetq_);
	product_bits = CAR(temp);
	temp = CDR(ab_loop_desetq_);
	temp = CDR(temp);
	atomic_p = CAR(temp);
	temp = CDR(ab_loop_desetq_);
	temp = CDR(temp);
	temp = CDR(temp);
	invisible_p = CAR(temp);
	if ( !FIXNUM_ZEROP(FIXNUM_LOGAND(code,product_bits)))
	    return VALUES_1(T);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

/* G2-DESCRIBE-G2-LICENSE */
Object g2_describe_g2_license()
{
    Object value_1, temp;

    x_note_fn_call(180,216);
    value_1 = Nil;
    value_1 = Text_representation_of_our_ok_object;
    temp = copy_as_wide_string(value_1);
    return VALUES_1(temp);
}

/* SET-INHERIT-STDIO-HANDLES */
Object set_inherit_stdio_handles(new_value)
    Object new_value;
{
    x_note_fn_call(180,217);
    return VALUES_1(FIX(g2ext_set_inherit_stdio_handles(IFIX(new_value))));
}

DEFINE_VARIABLE_WITH_SYMBOL(Foremost_attribute_for_multiplexed_chaining_qm, Qforemost_attribute_for_multiplexed_chaining_qm);

static Object array_constant_8;    /* # */

static Object array_constant_9;    /* # */

/* MARSHALL-EXCEPTIONAL-FLOAT-ARGUMENTS */
Object marshall_exceptional_float_arguments()
{
    Object machine_id_tag, position_of_machine_id_qm, ok_text_length;
    Object this_char, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, thing, temp_1, schar_arg_2, schar_new_value;
    SI_Long i, ab_loop_bind_, bv16_length, aref_arg_2, aref_new_value;
    SI_Long length_1, i2;
    Declare_special(5);

    x_note_fn_call(180,218);
    if (Foremost_attribute_for_multiplexed_chaining_qm)
	return copy_text_string(Foremost_attribute_for_multiplexed_chaining_qm);
    else {
	machine_id_tag = array_constant_8;
	position_of_machine_id_qm = 
		text_string_search_simple(machine_id_tag,
		Text_representation_of_our_ok_object);
	if (position_of_machine_id_qm) {
	    ok_text_length = 
		    text_string_length(Text_representation_of_our_ok_object);
	    i = IFIX(FIXNUM_ADD(position_of_machine_id_qm,
		    text_string_length(machine_id_tag)));
	    ab_loop_bind_ = IFIX(ok_text_length);
	    this_char = Nil;
	  next_loop:
	    if (i >= ab_loop_bind_)
		goto end_loop;
	    this_char = 
		    FIX(UBYTE_16_ISAREF_1(Text_representation_of_our_ok_object,
		    i));
	    if (EQ(this_char,FIX((SI_Long)34L))) {
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
			  i2 = i + (SI_Long)1L;
			  ab_loop_bind_ = IFIX(ok_text_length);
			  this_char = Nil;
			next_loop_1:
			  if (i2 >= ab_loop_bind_)
			      goto end_loop_1;
			  this_char = 
				  FIX(UBYTE_16_ISAREF_1(Text_representation_of_our_ok_object,
				  i2));
			  temp = this_char;
			  if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
				  FIXNUM_LE(temp,FIX((SI_Long)127L)))) {
			      if (EQ(Current_twriting_output_type,
				      Qwide_string)) {
				  thing = this_char;
				  twrite_wide_character(CHARACTERP(thing) ?
					   CHAR_CODE(thing) : thing);
			      }
			      else {
				  if ( 
					  !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
					  Total_length_of_current_gensym_string))
				      extend_current_gensym_string(0);
				  temp_1 = Current_gensym_string;
				  schar_arg_2 = 
					  Fill_pointer_for_current_gensym_string;
				  thing = this_char;
				  schar_new_value = 
					  CODE_CHAR(CHARACTERP(thing) ? 
					  CHAR_CODE(thing) : thing);
				  SET_SCHAR(temp_1,schar_arg_2,
					  schar_new_value);
				  temp_1 = 
					  FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
				  Fill_pointer_for_current_gensym_string = 
					  temp_1;
			      }
			  }
			  else
			      switch (INTEGER_TO_CHAR(temp)) {
				case 34:
				  goto end_loop_1;
				  break;
				default:
				  if (EQ(Current_twriting_output_type,
					  Qwide_string)) {
				      thing = this_char;
				      twrite_wide_character(CHARACTERP(thing) 
					      ? CHAR_CODE(thing) : thing);
				  }
				  else {
				      if ( 
					      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
					      Total_length_of_current_gensym_string))
					  extend_current_gensym_string(0);
				      temp_1 = Current_gensym_string;
				      schar_arg_2 = 
					      Fill_pointer_for_current_gensym_string;
				      thing = this_char;
				      schar_new_value = 
					      CODE_CHAR(CHARACTERP(thing) ?
					       CHAR_CODE(thing) : thing);
				      SET_SCHAR(temp_1,schar_arg_2,
					      schar_new_value);
				      temp_1 = 
					      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
				      Fill_pointer_for_current_gensym_string 
					      = temp_1;
				  }
				  break;
			      }
			  i2 = i2 + (SI_Long)1L;
			  goto next_loop_1;
			end_loop_1:;
			  Foremost_attribute_for_multiplexed_chaining_qm = 
				  copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		return copy_text_string(Foremost_attribute_for_multiplexed_chaining_qm);
	    }
	    i = i + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    return copy_constant_wide_string_given_length(array_constant_9,
		    FIX((SI_Long)0L));
	    return VALUES_1(Qnil);
	}
	else
	    return copy_constant_wide_string_given_length(array_constant_9,
		    FIX((SI_Long)0L));
    }
}

/* GET-G2-LICENSE-LEVEL */
Object get_g2_license_level()
{
    Object temp, temp_1;

    x_note_fn_call(180,219);
    if (BOUNDP(Qkb_restrictions) && Kb_restrictions && 
	    system_table_installed_p(Kb_restrictions) &&  !EQ(Qt,
	    get_lookup_slot_value_given_default(Kb_restrictions,
	    Qsimulated_optional_modules,T))) {
	temp = 
		license_level(get_lookup_slot_value_given_default(Kb_restrictions,
		Qsimulated_optional_modules,T));
	temp_1 = license_level(Authorized_products_of_this_machine);
	return VALUES_1(FIXNUM_MIN(temp,temp_1));
    }
    else
	return license_level(Authorized_products_of_this_machine);
}

static Object Qthis;               /* this */

/* FIX-ACCEPTABLE-APPLICABLE-ITEMS-FOR-OBJECT-CONFIGURATION */
Object fix_acceptable_applicable_items_for_object_configuration(evaluation_value)
    Object evaluation_value;
{
    Object gensymed_symbol, held_vector, element, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, elt_1, validated_elt, thing, temp;
    SI_Long next_index, length_1;

    x_note_fn_call(180,220);
    if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),Qsequence)) {
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	element = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop:
	if (next_index >= length_1)
	    goto end_loop;
	elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	element = validated_elt;
	ab_loopvar__2 = phrase_cons(element,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	thing = ab_loopvar_;
	goto end_1;
	thing = Qnil;
      end_1:;
	temp = EQ(CAR(thing),Qthis) &&  !TRUEP(CDDR(thing)) && CDR(thing) ?
		 CADR(thing) : thing;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* MAKE-ACCEPTABLE-APPLICABLE-ITEMS-FOR-OBJECT-CONFIGURATION */
Object make_acceptable_applicable_items_for_object_configuration(slot_value)
    Object slot_value;
{
    Object element, ab_loop_list_, gensymed_symbol, ab_loopvar_, ab_loopvar__1;
    Object thing, temp;

    x_note_fn_call(180,221);
    if ( !TRUEP(slot_value))
	return VALUES_1(slot_value);
    else if (CONSP(slot_value)) {
	element = Nil;
	ab_loop_list_ = slot_value;
	gensymed_symbol = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__1 = eval_cons_1(element,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    gensymed_symbol = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop;
      end_loop:
	return allocate_evaluation_sequence(gensymed_symbol);
	return VALUES_1(Qnil);
    }
    else {
	thing = gensym_list_2(Qthis,slot_value);
	element = Nil;
	ab_loop_list_ = thing;
	gensymed_symbol = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__1 = eval_cons_1(element,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    gensymed_symbol = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop_1;
      end_loop_1:
	temp = allocate_evaluation_sequence(gensymed_symbol);
	goto end_1;
	temp = Qnil;
      end_1:;
	reclaim_gensym_list_1(thing);
	return VALUES_1(temp);
    }
}

/* DIFFERENTIATE-PRESSING-FROM-RELEASING */
Object differentiate_pressing_from_releasing(key_code)
    Object key_code;
{
    Object unicode, gensymed_symbol, temp;

    x_note_fn_call(180,222);
    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	gensymed_symbol = num_len(3,FIX((SI_Long)0L),unicode,
		FIX((SI_Long)127L)) ? unicode : Illegal_key_index;
    }
    else
	gensymed_symbol = FIXNUM_LOGAND(Key_index_bits,key_code);
    if (IFIX(gensymed_symbol) == (SI_Long)779L || IFIX(gensymed_symbol) == 
	    (SI_Long)812L || IFIX(gensymed_symbol) == (SI_Long)813L || 
	    IFIX(gensymed_symbol) == (SI_Long)814L)
	return VALUES_1(Qclicking);
    else {
	if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	    unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	    temp = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) ?
		     unicode : Illegal_key_index;
	}
	else
	    temp = FIXNUM_LOGAND(Key_index_bits,key_code);
	if (EQ(temp,FIX((SI_Long)769L)) || EQ(temp,FIX((SI_Long)773L)) || 
		EQ(temp,FIX((SI_Long)775L)) || EQ(temp,FIX((SI_Long)777L)))
	    return VALUES_1(Qreleasing);
	else
	    return VALUES_1(Qpressing);
    }
}

static Object list_constant_26;    /* # */

static Object list_constant_27;    /* # */

/* MENU-AND-ATTRIBUTE-VISIBILITY-CONFIGURATIONS-RESTRICTION-TYPE-EVALUATION-SETTER */
Object menu_and_attribute_visibility_configurations_restriction_type_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(180,223);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_26))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_27,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_menu_and_attribute_visibility_configurations_restriction_type_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_menu_and_attribute_visibility_configurations_restriction_type_evaluation_setter:
    return result;
}

/* MENU-AND-ATTRIBUTE-VISIBILITY-CONFIGURATIONS-RESTRICTION-TYPE-EVALUATION-GETTER */
Object menu_and_attribute_visibility_configurations_restriction_type_evaluation_getter(slot_value,
	    frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(180,224);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object list_constant_28;    /* # */

static Object list_constant_29;    /* # */

/* TABLE-MENU-CHOICE-EVALUATION-SETTER */
Object table_menu_choice_evaluation_setter(menu_choice,frame,
	    slot_description,gensymed_symbol)
    Object menu_choice, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(180,225);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(menu_choice,
			  list_constant_28))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(menu_choice,
			      list_constant_29,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_table_menu_choice_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(menu_choice);
  end_table_menu_choice_evaluation_setter:
    return result;
}

/* TABLE-MENU-CHOICE-EVALUATION-GETTER */
Object table_menu_choice_evaluation_getter(menu_choice,frame,slot_description)
    Object menu_choice, frame, slot_description;
{
    x_note_fn_call(180,226);
    GENSYM_RETURN_ONE(menu_choice);
    return VALUES_1(Nil);
}

static Object list_constant_30;    /* # */

static Object list_constant_31;    /* # */

static Object Qtable_menu_choice;  /* table-menu-choice */

static Object Qcategory_evaluator_interface;  /* category-evaluator-interface */

/* TABLE-MENU-CHOICES-EVALUATION-SETTER */
Object table_menu_choices_evaluation_setter(menu_choices,frame,
	    slot_description,gensymed_symbol)
    Object menu_choices, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object menu_choice_element, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object elt_1, validated_elt, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, parse_result_or_bad_phrase, error_string_qm;
    SI_Long next_index, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(180,227);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(menu_choices,
			  list_constant_30))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(menu_choices,
			      list_constant_31,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_table_menu_choices_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = menu_choices;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    menu_choice_element = Nil;
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
    menu_choice_element = validated_elt;
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtable_menu_choice),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = menu_choice_element;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	temp_1 = parse_result_or_bad_phrase;
    ab_loopvar__2 = phrase_cons(temp_1,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    result = VALUES_1(ab_loopvar_);
    goto end_1;
    result = VALUES_1(Qnil);
  end_1:;
  end_safe_category_setter_calling_block:
  end_table_menu_choices_evaluation_setter:
    return result;
}

/* TABLE-MENU-CHOICES-EVALUATION-GETTER */
Object table_menu_choices_evaluation_getter(internal_menu_choices,frame,
	    slot_description)
    Object internal_menu_choices, frame, slot_description;
{
    Object source_menu_choice_element, ab_loop_list_, gensymed_symbol;
    Object ab_loopvar_, ab_loopvar__1, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, temp;

    x_note_fn_call(180,228);
    source_menu_choice_element = Nil;
    ab_loop_list_ = internal_menu_choices;
    gensymed_symbol = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    source_menu_choice_element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtable_menu_choice),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = source_menu_choice_element;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	temp = Nil;
    ab_loopvar__1 = eval_cons_1(temp,Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	gensymed_symbol = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    temp = allocate_evaluation_sequence(gensymed_symbol);
    goto end_1;
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_32;    /* # */

static Object list_constant_33;    /* # */

/* MENU-CHOICES-EVALUATION-SETTER */
Object menu_choices_evaluation_setter(menu_choices,frame,slot_description,
	    gensymed_symbol)
    Object menu_choices, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object menu_choice_element, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object elt_1, validated_elt;
    SI_Long next_index, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(180,229);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(menu_choices,
			  list_constant_32))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(menu_choices,
			      list_constant_33,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_menu_choices_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = menu_choices;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    menu_choice_element = Nil;
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
    menu_choice_element = validated_elt;
    ab_loopvar__2 = phrase_cons(menu_choice_element,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    result = VALUES_1(ab_loopvar_);
    goto end_1;
    result = VALUES_1(Qnil);
  end_1:;
  end_menu_choices_evaluation_setter:
    return result;
}

/* MENU-CHOICES-EVALUATION-GETTER */
Object menu_choices_evaluation_getter(internal_menu_choices,frame,
	    slot_description)
    Object internal_menu_choices, frame, slot_description;
{
    Object source_menu_choice_element, ab_loop_list_, gensymed_symbol;
    Object ab_loopvar_, ab_loopvar__1, temp;

    x_note_fn_call(180,230);
    source_menu_choice_element = Nil;
    ab_loop_list_ = internal_menu_choices;
    gensymed_symbol = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    source_menu_choice_element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__1 = eval_cons_1(source_menu_choice_element,Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	gensymed_symbol = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    temp = allocate_evaluation_sequence(gensymed_symbol);
    goto end_1;
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_34;    /* # */

static Object list_constant_35;    /* # */

static Object Qoperation_type;     /* operation-type */

static Object Qtable_menu;         /* table-menu */

static Object Qattribute_visibility;  /* attribute-visibility */

static Object Qapplicable_attributes;  /* applicable-attributes */

static Object Qapplicable_items;   /* applicable-items */

static Object Qrestriction_type;   /* restriction-type */

static Object Qmenu_choices;       /* menu-choices */

/* TABLE-MENU-CONFIGURATIONS-EVALUATION-SETTER */
Object table_menu_configurations_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, op_type, temp_2;
    Object gensymed_symbol_1, held_vector, attribute_element, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, elt_1, validated_elt;
    Object category_evaluator_interface, function, gensymed_symbol_2;
    Object gensymed_symbol_3, gensymed_symbol_4, parse_result_or_bad_phrase;
    Object error_string_qm;
    SI_Long next_index, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(180,231);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_34))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_35,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_table_menu_configurations_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    op_type = estructure_slot(gensymed_symbol,Qoperation_type,Nil);
    if (EQ(op_type,Qitem_menu))
	temp = Qworkspace_menu;
    else if (EQ(op_type,Qtable_menu))
	temp = Qtable;
    else if (EQ(op_type,Qattribute_visibility))
	temp = Qvisibility;
    else if (EQ(op_type,Qtyping))
	temp = Qpressing;
    else if (EQ(op_type,Qpressing) || EQ(op_type,Qreleasing))
	temp = Qclicking;
    else if (EQ(op_type,Qmoving))
	temp = Qconstrain;
    else
	temp = op_type;
    if ( !TRUEP(estructure_slot(gensymed_symbol,Qapplicable_attributes,Nil))) {
	temp_1 = 
		fix_acceptable_applicable_items_for_object_configuration(estructure_slot(gensymed_symbol,
		Qapplicable_items,Nil));
	temp_2 = phrase_list_2(temp_1,estructure_slot(gensymed_symbol,
		Qrestriction_type,Nil));
    }
    else {
	temp_1 = 
		fix_acceptable_applicable_items_for_object_configuration(estructure_slot(gensymed_symbol,
		Qapplicable_items,Nil));
	gensymed_symbol_1 = estructure_slot(gensymed_symbol,
		Qapplicable_attributes,Nil);
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	attribute_element = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	held_vector = M_CAR(gensymed_symbol_1);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop:
	if (next_index >= length_1)
	    goto end_loop;
	elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	attribute_element = validated_elt;
	ab_loopvar__2 = phrase_cons(attribute_element,Nil);
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
	temp_2 = phrase_list_3(temp_1,temp_2,
		estructure_slot(gensymed_symbol,Qrestriction_type,Nil));
    }
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtable_menu_choices),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol = estructure_slot(gensymed_symbol,Qmenu_choices,Nil);
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	temp_1 = parse_result_or_bad_phrase;
    result = phrase_cons(temp,nconc2(temp_2,temp_1));
  end_safe_category_setter_calling_block:
  end_table_menu_configurations_evaluation_setter:
    return result;
}

static Object Qpressing_or_releasing;  /* pressing-or-releasing */

/* TABLE-MENU-CONFIGURATIONS-EVALUATION-GETTER */
Object table_menu_configurations_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, int_op_type, temp, internal_operation_type;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object source_attribute_element, ab_loop_list_, ab_loopvar_, ab_loopvar__1;

    x_note_fn_call(180,232);
    gensymed_symbol = allocate_evaluation_structure(Nil);
    int_op_type = CAR(slot_value);
    if (EQ(int_op_type,Qworkspace_menu))
	temp = Qitem_menu;
    else if (EQ(int_op_type,Qtable))
	temp = Qtable_menu;
    else if (EQ(int_op_type,Qvisibility))
	temp = Qattribute_visibility;
    else if (EQ(int_op_type,Qpressing))
	temp = Qtyping;
    else if (EQ(int_op_type,Qclicking))
	temp = Qpressing_or_releasing;
    else if (EQ(int_op_type,Qconstrain))
	temp = Qmoving;
    else
	temp = int_op_type;
    set_evaluation_structure_slot(gensymed_symbol,Qoperation_type,temp);
    internal_operation_type = CAR(slot_value);
    set_evaluation_structure_slot(gensymed_symbol,Qrestriction_type,
	    EQ(internal_operation_type,Qtable) || 
	    EQ(internal_operation_type,Qvisibility) ? FOURTH(slot_value) : 
	    THIRD(slot_value));
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtable_menu_choices),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	internal_operation_type = CAR(slot_value);
	gensymed_symbol_2 = EQ(internal_operation_type,Qtable) ? 
		CDDDDR(slot_value) : CDDDR(slot_value);
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	temp = Nil;
    set_evaluation_structure_slot(gensymed_symbol,Qmenu_choices,temp);
    source_attribute_element = Nil;
    ab_loop_list_ = EQ(CAR(slot_value),Qtable) ? THIRD(slot_value) : Nil;
    gensymed_symbol_1 = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    source_attribute_element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__1 = eval_cons_1(source_attribute_element,Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	gensymed_symbol_1 = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    temp = allocate_evaluation_sequence(gensymed_symbol_1);
    goto end_1;
    temp = Qnil;
  end_1:;
    set_evaluation_structure_slot(gensymed_symbol,Qapplicable_attributes,temp);
    set_evaluation_structure_slot(gensymed_symbol,Qapplicable_items,
	    make_acceptable_applicable_items_for_object_configuration(SECOND(slot_value)));
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object list_constant_36;    /* # */

static Object list_constant_37;    /* # */

/* MENU-CONFIGURATIONS-EVALUATION-SETTER */
Object menu_configurations_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, op_type, temp_2;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object parse_result_or_bad_phrase, error_string_qm;
    Declare_special(5);
    Object result;

    x_note_fn_call(180,233);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_36))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_37,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_menu_configurations_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    op_type = estructure_slot(gensymed_symbol,Qoperation_type,Nil);
    if (EQ(op_type,Qitem_menu))
	temp_2 = Qworkspace_menu;
    else if (EQ(op_type,Qtable_menu))
	temp_2 = Qtable;
    else if (EQ(op_type,Qattribute_visibility))
	temp_2 = Qvisibility;
    else if (EQ(op_type,Qtyping))
	temp_2 = Qpressing;
    else if (EQ(op_type,Qpressing) || EQ(op_type,Qreleasing))
	temp_2 = Qclicking;
    else if (EQ(op_type,Qmoving))
	temp_2 = Qconstrain;
    else
	temp_2 = op_type;
    temp_1 = 
	    fix_acceptable_applicable_items_for_object_configuration(estructure_slot(gensymed_symbol,
	    Qapplicable_items,Nil));
    temp = phrase_list_2(temp_1,estructure_slot(gensymed_symbol,
	    Qrestriction_type,Nil));
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qmenu_choices),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol = estructure_slot(gensymed_symbol,Qmenu_choices,Nil);
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	temp_1 = parse_result_or_bad_phrase;
    result = phrase_cons(temp_2,nconc2(temp,temp_1));
  end_safe_category_setter_calling_block:
  end_menu_configurations_evaluation_setter:
    return result;
}

/* MENU-CONFIGURATIONS-EVALUATION-GETTER */
Object menu_configurations_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, int_op_type, temp, internal_operation_type;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;

    x_note_fn_call(180,234);
    gensymed_symbol = allocate_evaluation_structure(Nil);
    int_op_type = CAR(slot_value);
    if (EQ(int_op_type,Qworkspace_menu))
	temp = Qitem_menu;
    else if (EQ(int_op_type,Qtable))
	temp = Qtable_menu;
    else if (EQ(int_op_type,Qvisibility))
	temp = Qattribute_visibility;
    else if (EQ(int_op_type,Qpressing))
	temp = Qtyping;
    else if (EQ(int_op_type,Qclicking))
	temp = Qpressing_or_releasing;
    else if (EQ(int_op_type,Qconstrain))
	temp = Qmoving;
    else
	temp = int_op_type;
    set_evaluation_structure_slot(gensymed_symbol,Qoperation_type,temp);
    internal_operation_type = CAR(slot_value);
    set_evaluation_structure_slot(gensymed_symbol,Qrestriction_type,
	    EQ(internal_operation_type,Qtable) || 
	    EQ(internal_operation_type,Qvisibility) ? FOURTH(slot_value) : 
	    THIRD(slot_value));
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qmenu_choices),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	internal_operation_type = CAR(slot_value);
	gensymed_symbol_2 = EQ(internal_operation_type,Qtable) ? 
		CDDDDR(slot_value) : CDDDR(slot_value);
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	temp = Nil;
    set_evaluation_structure_slot(gensymed_symbol,Qmenu_choices,temp);
    set_evaluation_structure_slot(gensymed_symbol,Qapplicable_items,
	    make_acceptable_applicable_items_for_object_configuration(SECOND(slot_value)));
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object list_constant_38;    /* # */

static Object list_constant_39;    /* # */

static Object Qattributes;         /* attributes */

/* ATTRIBUTE-VISIBILITY-CONFIGURATIONS-EVALUATION-SETTER */
Object attribute_visibility_configurations_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, op_type;
    Object gensymed_symbol_1, held_vector, attribute_element, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, elt_1, validated_elt, temp_2;
    SI_Long next_index, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(180,235);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_38))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_39,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_attribute_visibility_configurations_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    op_type = estructure_slot(gensymed_symbol,Qoperation_type,Nil);
    if (EQ(op_type,Qitem_menu))
	temp = Qworkspace_menu;
    else if (EQ(op_type,Qtable_menu))
	temp = Qtable;
    else if (EQ(op_type,Qattribute_visibility))
	temp = Qvisibility;
    else if (EQ(op_type,Qtyping))
	temp = Qpressing;
    else if (EQ(op_type,Qpressing) || EQ(op_type,Qreleasing))
	temp = Qclicking;
    else if (EQ(op_type,Qmoving))
	temp = Qconstrain;
    else
	temp = op_type;
    temp_1 = 
	    fix_acceptable_applicable_items_for_object_configuration(estructure_slot(gensymed_symbol,
	    Qapplicable_items,Nil));
    gensymed_symbol_1 = estructure_slot(gensymed_symbol,Qattributes,Nil);
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    attribute_element = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    held_vector = M_CAR(gensymed_symbol_1);
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
    attribute_element = validated_elt;
    ab_loopvar__2 = phrase_cons(attribute_element,Nil);
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
    result = phrase_cons(temp,phrase_list_3(temp_1,temp_2,
	    estructure_slot(gensymed_symbol,Qrestriction_type,Nil)));
  end_attribute_visibility_configurations_evaluation_setter:
    return result;
}

/* ATTRIBUTE-VISIBILITY-CONFIGURATIONS-EVALUATION-GETTER */
Object attribute_visibility_configurations_evaluation_getter(slot_value,
	    frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, int_op_type, temp, source_attribute_element;
    Object ab_loop_list_, gensymed_symbol_1, ab_loopvar_, ab_loopvar__1;
    Object internal_operation_type;

    x_note_fn_call(180,236);
    gensymed_symbol = allocate_evaluation_structure(Nil);
    int_op_type = CAR(slot_value);
    if (EQ(int_op_type,Qworkspace_menu))
	temp = Qitem_menu;
    else if (EQ(int_op_type,Qtable))
	temp = Qtable_menu;
    else if (EQ(int_op_type,Qvisibility))
	temp = Qattribute_visibility;
    else if (EQ(int_op_type,Qpressing))
	temp = Qtyping;
    else if (EQ(int_op_type,Qclicking))
	temp = Qpressing_or_releasing;
    else if (EQ(int_op_type,Qconstrain))
	temp = Qmoving;
    else
	temp = int_op_type;
    set_evaluation_structure_slot(gensymed_symbol,Qoperation_type,temp);
    source_attribute_element = Nil;
    ab_loop_list_ = THIRD(slot_value);
    gensymed_symbol_1 = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    source_attribute_element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__1 = eval_cons_1(source_attribute_element,Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	gensymed_symbol_1 = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    temp = allocate_evaluation_sequence(gensymed_symbol_1);
    goto end_1;
    temp = Qnil;
  end_1:;
    set_evaluation_structure_slot(gensymed_symbol,Qattributes,temp);
    internal_operation_type = CAR(slot_value);
    set_evaluation_structure_slot(gensymed_symbol,Qrestriction_type,
	    EQ(internal_operation_type,Qtable) || 
	    EQ(internal_operation_type,Qvisibility) ? FOURTH(slot_value) : 
	    THIRD(slot_value));
    set_evaluation_structure_slot(gensymed_symbol,Qapplicable_items,
	    make_acceptable_applicable_items_for_object_configuration(SECOND(slot_value)));
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object list_constant_40;    /* # */

static Object list_constant_41;    /* # */

static Object Qmouse_tracking_applicable_items;  /* mouse-tracking-applicable-items */

static Object Qmouse_motion_tracking_qm;  /* mouse-motion-tracking? */

static Object Qmouse_tracking_procedure_name;  /* mouse-tracking-procedure-name */

static Object Qmotion;             /* motion */

/* USER-INTERFACE-CONSEQUENT-ACTION-EVALUATION-SETTER */
Object user_interface_consequent_action_evaluation_setter(consequent_action,
	    frame,slot_description,gensymed_symbol)
    Object consequent_action, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object mouse_tracking_applicable_items_info;
    Declare_special(5);
    Object result;

    x_note_fn_call(180,237);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(consequent_action,
			  list_constant_40))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(consequent_action,
			      list_constant_41,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_user_interface_consequent_action_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (SYMBOLP(consequent_action))
	result = VALUES_1(consequent_action);
    else {
	gensymed_symbol = consequent_action;
	mouse_tracking_applicable_items_info = 
		fix_acceptable_applicable_items_for_object_configuration(estructure_slot(gensymed_symbol,
		Qmouse_tracking_applicable_items,Nil));
	if ( !TRUEP(estructure_slot(gensymed_symbol,
		Qmouse_motion_tracking_qm,Nil)))
	    result = phrase_list_3(Quser_mouse_tracking,
		    estructure_slot(gensymed_symbol,
		    Qmouse_tracking_procedure_name,Nil),
		    mouse_tracking_applicable_items_info);
	else
	    result = phrase_list_4(Quser_mouse_tracking,
		    estructure_slot(gensymed_symbol,
		    Qmouse_tracking_procedure_name,Nil),
		    mouse_tracking_applicable_items_info,Qmotion);
    }
  end_user_interface_consequent_action_evaluation_setter:
    return result;
}

/* USER-INTERFACE-CONSEQUENT-ACTION-EVALUATION-GETTER */
Object user_interface_consequent_action_evaluation_getter(source_consequent_action,
	    frame,slot_description)
    Object source_consequent_action, frame, slot_description;
{
    Object gensymed_symbol, gensymed_symbol_1;
    Object source_mouse_tracking_procedure_name;
    Object source_mouse_tracking_applicable_items, source_mouse_motion, value;
    Object temp;

    x_note_fn_call(180,238);
    if (CONSP(source_consequent_action)) {
	gensymed_symbol = allocate_evaluation_structure(Nil);
	gensymed_symbol_1 = source_consequent_action;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	source_mouse_tracking_procedure_name = CAR(gensymed_symbol_1);
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	source_mouse_tracking_applicable_items = CAR(gensymed_symbol_1);
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	source_mouse_motion = CAR(gensymed_symbol_1);
	set_evaluation_structure_slot(gensymed_symbol,
		Qmouse_tracking_procedure_name,
		source_mouse_tracking_procedure_name);
	value = 
		make_acceptable_applicable_items_for_object_configuration(source_mouse_tracking_applicable_items);
	if (value)
	    set_evaluation_structure_slot(gensymed_symbol,
		    Qmouse_tracking_applicable_items,value);
	if (source_mouse_motion)
	    set_evaluation_structure_slot(gensymed_symbol,
		    Qmouse_motion_tracking_qm,Evaluation_true_value);
	temp = gensymed_symbol;
    }
    else
	temp = source_consequent_action;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_42;    /* # */

static Object list_constant_43;    /* # */

/* MODIFIER-KEY-EVALUATION-SETTER */
Object modifier_key_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(180,239);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_42))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_43,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_modifier_key_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_modifier_key_evaluation_setter:
    return result;
}

/* MODIFIER-KEY-EVALUATION-GETTER */
Object modifier_key_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(180,240);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object list_constant_44;    /* # */

static Object list_constant_45;    /* # */

/* KEYBOARD-SYMBOL-EVALUATION-SETTER */
Object keyboard_symbol_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(180,241);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_44))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_45,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_keyboard_symbol_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_keyboard_symbol_evaluation_setter:
    return result;
}

/* KEYBOARD-SYMBOL-EVALUATION-GETTER */
Object keyboard_symbol_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(180,242);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object list_constant_46;    /* # */

static Object list_constant_47;    /* # */

/* MOUSE-BUTTON-EVALUATION-SETTER */
Object mouse_button_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(180,243);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_46))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_47,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_mouse_button_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_mouse_button_evaluation_setter:
    return result;
}

/* MOUSE-BUTTON-EVALUATION-GETTER */
Object mouse_button_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(180,244);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

/* EXPORTED-KEY-MODIFIER-BITS */
Object exported_key_modifier_bits(key_code)
    Object key_code;
{
    Object unicode;
    SI_Long gensymed_symbol, arg, arg_1, arg_2, gensymed_symbol_1;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(180,245);
    gensymed_symbol = IFIX(FIXNUM_LOGAND(key_code,Shift_bit)) != 
	    (SI_Long)0L ? (SI_Long)1L : (SI_Long)0L;
    temp = IFIX(FIXNUM_LOGAND(key_code,Control_bit)) != (SI_Long)0L;
    if (temp);
    else {
	arg = (SI_Long)0L;
	if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	    unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	    arg_1 = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) 
		    ? IFIX(unicode) : IFIX(Illegal_key_index);
	}
	else
	    arg_1 = IFIX(FIXNUM_LOGAND(Key_index_bits,key_code));
	arg_2 = (SI_Long)31L;
	temp = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
    }
    gensymed_symbol_1 = temp ? (SI_Long)2L : (SI_Long)0L;
    gensymed_symbol_2 = IFIX(FIXNUM_LOGAND(key_code,Alternate_bit)) != 
	    (SI_Long)0L ? (SI_Long)4L : (SI_Long)0L;
    gensymed_symbol_3 = IFIX(FIXNUM_LOGAND(key_code,Double_bit)) != 
	    (SI_Long)0L ? (SI_Long)8L : (SI_Long)0L;
    return VALUES_1(FIX(gensymed_symbol | gensymed_symbol_1 | 
	    gensymed_symbol_2 | gensymed_symbol_3));
}

/* KEY-SYMBOL */
Object key_symbol(key_code)
    Object key_code;
{
    Object unicode, index1, index2;
    SI_Long arg, arg_1, arg_2;

    x_note_fn_call(180,246);
    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	index1 = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) ? 
		unicode : Illegal_key_index;
    }
    else
	index1 = FIXNUM_LOGAND(Key_index_bits,key_code);
    arg = (SI_Long)0L;
    if (IFIX(FIXNUM_LOGAND(index1,Unicode_bit)) != (SI_Long)0L) {
	unicode = FIXNUM_LOGAND(Unicode_character_bits,index1);
	arg_1 = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) ? 
		IFIX(unicode) : IFIX(Illegal_key_index);
    }
    else
	arg_1 = IFIX(FIXNUM_LOGAND(Key_index_bits,index1));
    arg_2 = (SI_Long)31L;
    index2 = arg <= arg_1 && arg_1 <= arg_2 ? FIX(IFIX(index1) | 
	    (SI_Long)64L) : index1;
    arg = (SI_Long)97L;
    if (IFIX(FIXNUM_LOGAND(index2,Unicode_bit)) != (SI_Long)0L) {
	unicode = FIXNUM_LOGAND(Unicode_character_bits,index2);
	arg_1 = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) ? 
		IFIX(unicode) : IFIX(Illegal_key_index);
    }
    else
	arg_1 = IFIX(FIXNUM_LOGAND(Key_index_bits,index2));
    arg_2 = (SI_Long)122L;
    return convert_key_code_to_key_symbol(arg <= arg_1 && arg_1 <= arg_2 ? 
	    FIX(IFIX(index2) ^ (SI_Long)32L) : index2);
}

static Object list_constant_48;    /* # */

static Object list_constant_49;    /* # */

static Object Qkeyboard_symbol;    /* keyboard-symbol */

static Object Qmodifiers;          /* modifiers */

static Object Qcontrol;            /* control */

static Object Qshift;              /* shift */

static Object Qalt;                /* alt */

/* USER-INTERFACE-KEY-CHORD-EVALUATION-SETTER */
Object user_interface_key_chord_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, key_spec;
    Declare_special(5);
    Object result;

    x_note_fn_call(180,247);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_48))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_49,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_user_interface_key_chord_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    key_spec = gensym_cons_1(estructure_slot(gensymed_symbol,
	    Qkeyboard_symbol,Nil),Nil);
    if ((IFIX(estructure_slot(gensymed_symbol,Qmodifiers,Nil)) & 
	    (SI_Long)2L) != (SI_Long)0L)
	key_spec = gensym_cons_1(Qcontrol,key_spec);
    if ((IFIX(estructure_slot(gensymed_symbol,Qmodifiers,Nil)) & 
	    (SI_Long)1L) != (SI_Long)0L)
	key_spec = gensym_cons_1(Qshift,key_spec);
    if ((IFIX(estructure_slot(gensymed_symbol,Qmodifiers,Nil)) & 
	    (SI_Long)4L) != (SI_Long)0L)
	key_spec = gensym_cons_1(Qalt,key_spec);
    temp_1 = key_code_function(key_spec,Nil,T);
    reclaim_gensym_list_1(key_spec);
    result = VALUES_1(temp_1);
  end_user_interface_key_chord_evaluation_setter:
    return result;
}

/* USER-INTERFACE-KEY-CHORD-EVALUATION-GETTER */
Object user_interface_key_chord_evaluation_getter(key_code,frame,
	    slot_description)
    Object key_code, frame, slot_description;
{
    Object gensymed_symbol, unicode;
    SI_Long arg, arg_1, arg_2;

    x_note_fn_call(180,248);
    gensymed_symbol = allocate_evaluation_structure(Nil);
    arg = (SI_Long)65L;
    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	arg_1 = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) ? 
		IFIX(unicode) : IFIX(Illegal_key_index);
    }
    else
	arg_1 = IFIX(FIXNUM_LOGAND(Key_index_bits,key_code));
    arg_2 = (SI_Long)90L;
    if (arg <= arg_1 && arg_1 <= arg_2)
	key_code = FIX(IFIX(key_code) ^ (SI_Long)32L | IFIX(Shift_bit));
    set_evaluation_structure_slot(gensymed_symbol,Qkeyboard_symbol,
	    key_symbol(key_code));
    set_evaluation_structure_slot(gensymed_symbol,Qmodifiers,
	    exported_key_modifier_bits(key_code));
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object list_constant_50;    /* # */

static Object list_constant_51;    /* # */

static Object Quser_interface_consequent_action;  /* user-interface-consequent-action */

static Object Qconsequent_action;  /* consequent-action */

static Object Quser_interface_key_chord;  /* user-interface-key-chord */

static Object Qkey_code;           /* key-code */

/* CONFIGURE-KEYSTROKE-EVALUATION-SETTER */
Object configure_keystroke_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, op_type;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object gensymed_symbol_5, parse_result_or_bad_phrase, error_string_qm;
    Object consequent_action_info, applicable_items_info, internal_key_code;
    Declare_special(5);
    Object result;

    x_note_fn_call(180,249);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_50))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_51,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_configure_keystroke_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    op_type = estructure_slot(gensymed_symbol,Qoperation_type,Nil);
    if (EQ(op_type,Qitem_menu))
	temp_1 = Qworkspace_menu;
    else if (EQ(op_type,Qtable_menu))
	temp_1 = Qtable;
    else if (EQ(op_type,Qattribute_visibility))
	temp_1 = Qvisibility;
    else if (EQ(op_type,Qtyping))
	temp_1 = Qpressing;
    else if (EQ(op_type,Qpressing) || EQ(op_type,Qreleasing))
	temp_1 = Qclicking;
    else if (EQ(op_type,Qmoving))
	temp_1 = Qconstrain;
    else
	temp_1 = op_type;
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Quser_interface_consequent_action),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = estructure_slot(gensymed_symbol,
		Qconsequent_action,Nil);
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	gensymed_symbol_5 = Nil;
	result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4,gensymed_symbol_5);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	consequent_action_info = parse_result_or_bad_phrase;
    applicable_items_info = 
	    fix_acceptable_applicable_items_for_object_configuration(estructure_slot(gensymed_symbol,
	    Qapplicable_items,Nil));
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Quser_interface_key_chord),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol = estructure_slot(gensymed_symbol,Qkey_code,Nil);
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	internal_key_code = parse_result_or_bad_phrase;
    result = phrase_cons(temp_1,phrase_list_3(internal_key_code,
	    consequent_action_info,applicable_items_info));
  end_safe_category_setter_calling_block:
  end_configure_keystroke_evaluation_setter:
    return result;
}

/* CONFIGURE-KEYSTROKE-EVALUATION-GETTER */
Object configure_keystroke_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, int_op_type, temp, gensymed_symbol_1;
    Object source_key_code, source_consequent_action, source_applicable_items;
    Object category_evaluator_interface, function, gensymed_symbol_2;
    Object gensymed_symbol_3, gensymed_symbol_4, value;

    x_note_fn_call(180,250);
    gensymed_symbol = allocate_evaluation_structure(Nil);
    int_op_type = CAR(slot_value);
    if (EQ(int_op_type,Qworkspace_menu))
	temp = Qitem_menu;
    else if (EQ(int_op_type,Qtable))
	temp = Qtable_menu;
    else if (EQ(int_op_type,Qvisibility))
	temp = Qattribute_visibility;
    else if (EQ(int_op_type,Qpressing))
	temp = Qtyping;
    else if (EQ(int_op_type,Qclicking))
	temp = Qpressing_or_releasing;
    else if (EQ(int_op_type,Qconstrain))
	temp = Qmoving;
    else
	temp = int_op_type;
    set_evaluation_structure_slot(gensymed_symbol,Qoperation_type,temp);
    gensymed_symbol_1 = slot_value;
    gensymed_symbol_1 = CDR(gensymed_symbol_1);
    source_key_code = CAR(gensymed_symbol_1);
    gensymed_symbol_1 = CDR(gensymed_symbol_1);
    source_consequent_action = CAR(gensymed_symbol_1);
    gensymed_symbol_1 = CDR(gensymed_symbol_1);
    source_applicable_items = CAR(gensymed_symbol_1);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Quser_interface_key_chord),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = source_key_code;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	temp = Nil;
    set_evaluation_structure_slot(gensymed_symbol,Qkey_code,temp);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Quser_interface_consequent_action),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = source_consequent_action;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	temp = Nil;
    set_evaluation_structure_slot(gensymed_symbol,Qconsequent_action,temp);
    value = 
	    make_acceptable_applicable_items_for_object_configuration(source_applicable_items);
    if (value)
	set_evaluation_structure_slot(gensymed_symbol,Qapplicable_items,value);
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object Qleft;               /* left */

static Object Qmiddle;             /* middle */

static Object Qright;              /* right */

/* IMPORT-MOUSE-CHORD */
Object import_mouse_chord(operation_type,modifiers,button)
    Object operation_type, modifiers, button;
{
    Object key_spec, mouse_key_name, temp;

    x_note_fn_call(180,251);
    key_spec = Nil;
    if ((IFIX(modifiers) & (SI_Long)2L) != (SI_Long)0L)
	key_spec = gensym_cons_1(Qcontrol,key_spec);
    if ((IFIX(modifiers) & (SI_Long)1L) != (SI_Long)0L)
	key_spec = gensym_cons_1(Qshift,key_spec);
    if ((IFIX(modifiers) & (SI_Long)4L) != (SI_Long)0L)
	key_spec = gensym_cons_1(Qalt,key_spec);
    if ((IFIX(modifiers) & (SI_Long)8L) != (SI_Long)0L)
	key_spec = gensym_cons_1(Qdouble,key_spec);
    if (EQ(operation_type,Qpressing)) {
	if (EQ(button,Qleft))
	    mouse_key_name = Qmouse_left_down;
	else if (EQ(button,Qmiddle))
	    mouse_key_name = Qmouse_middle_down;
	else if (EQ(button,Qright))
	    mouse_key_name = Qmouse_right_down;
	else if (EQ(button,Qany))
	    mouse_key_name = Qmouse_down;
	else
	    mouse_key_name = Qnil;
    }
    else if (EQ(operation_type,Qreleasing)) {
	if (EQ(button,Qleft))
	    mouse_key_name = Qmouse_left_up;
	else if (EQ(button,Qmiddle))
	    mouse_key_name = Qmouse_middle_up;
	else if (EQ(button,Qright))
	    mouse_key_name = Qmouse_right_up;
	else if (EQ(button,Qany))
	    mouse_key_name = Qmouse_up;
	else
	    mouse_key_name = Qnil;
    }
    else if (EQ(operation_type,Qclicking)) {
	if (EQ(button,Qleft))
	    mouse_key_name = Qmouse_left_select;
	else if (EQ(button,Qmiddle))
	    mouse_key_name = Qmouse_middle_select;
	else if (EQ(button,Qright))
	    mouse_key_name = Qmouse_right_select;
	else if (EQ(button,Qany))
	    mouse_key_name = Qmouse_select;
	else
	    mouse_key_name = Qnil;
    }
    else
	mouse_key_name = Qmouse_select;
    key_spec = gensym_cons_1(mouse_key_name,key_spec);
    temp = key_code_function(key_spec,Nil,T);
    reclaim_gensym_list_1(key_spec);
    return VALUES_1(temp);
}

static Object list_constant_52;    /* # */

static Object string_constant_140;  /* "The double-bit is permitted only with operation-type PRESSING." */

/* CHECK-FOR-DISALLOWED-MOUSE-CHORD */
Object check_for_disallowed_mouse_chord(operation_type,modifiers,button)
    Object operation_type, modifiers, button;
{
    x_note_fn_call(180,252);
    if ((IFIX(modifiers) & (SI_Long)8L) != (SI_Long)0L &&  
	    !TRUEP(memq_function(operation_type,list_constant_52)))
	return VALUES_1(string_constant_140);
    else
	return VALUES_1(Nil);
}

static Object list_constant_53;    /* # */

static Object list_constant_54;    /* # */

static Object Qmouse_button;       /* mouse-button */

/* CONFIGURE-MOUSE-CLICK-EVALUATION-SETTER */
Object configure_mouse_click_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, gensymed_symbol_1;
    Object error_message_qm, op_type, category_evaluator_interface, function;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object gensymed_symbol_5, parse_result_or_bad_phrase, error_string_qm;
    Object consequent_action_info, applicable_items_info, temp_2;
    Object internal_key_code;
    Declare_special(5);
    Object result;

    x_note_fn_call(180,253);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_53))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_54,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_configure_mouse_click_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    gensymed_symbol_1 = estructure_slot(gensymed_symbol,Qkey_code,Nil);
    temp = estructure_slot(gensymed_symbol,Qoperation_type,Nil);
    temp_1 = estructure_slot(gensymed_symbol_1,Qmodifiers,Nil);
    error_message_qm = check_for_disallowed_mouse_chord(temp,temp_1,
	    estructure_slot(gensymed_symbol_1,Qmouse_button,Nil));
    if (error_message_qm) {
	temp = Bad_phrase;
	temp_1 = copy_text_string(error_message_qm);
	result = VALUES_2(temp,temp_1);
    }
    else {
	op_type = estructure_slot(gensymed_symbol,Qoperation_type,Nil);
	if (EQ(op_type,Qitem_menu))
	    temp_1 = Qworkspace_menu;
	else if (EQ(op_type,Qtable_menu))
	    temp_1 = Qtable;
	else if (EQ(op_type,Qattribute_visibility))
	    temp_1 = Qvisibility;
	else if (EQ(op_type,Qtyping))
	    temp_1 = Qpressing;
	else if (EQ(op_type,Qpressing) || EQ(op_type,Qreleasing))
	    temp_1 = Qclicking;
	else if (EQ(op_type,Qmoving))
	    temp_1 = Qconstrain;
	else
	    temp_1 = op_type;
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Quser_interface_consequent_action),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol_2 = estructure_slot(gensymed_symbol,
		    Qconsequent_action,Nil);
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    gensymed_symbol_5 = Nil;
	    result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3,gensymed_symbol_4,gensymed_symbol_5);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    consequent_action_info = parse_result_or_bad_phrase;
	applicable_items_info = 
		fix_acceptable_applicable_items_for_object_configuration(estructure_slot(gensymed_symbol,
		Qapplicable_items,Nil));
	gensymed_symbol_1 = estructure_slot(gensymed_symbol,Qkey_code,Nil);
	temp_2 = estructure_slot(gensymed_symbol,Qoperation_type,Nil);
	temp = estructure_slot(gensymed_symbol_1,Qmodifiers,Nil);
	internal_key_code = import_mouse_chord(temp_2,temp,
		estructure_slot(gensymed_symbol_1,Qmouse_button,Nil));
	result = phrase_cons(temp_1,phrase_list_3(internal_key_code,
		consequent_action_info,applicable_items_info));
    }
  end_safe_category_setter_calling_block:
  end_configure_mouse_click_evaluation_setter:
    return result;
}

/* CONFIGURE-MOUSE-CLICK-EVALUATION-GETTER */
Object configure_mouse_click_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, int_op_type, external_type, gensymed_symbol_1;
    Object source_key_code, source_consequent_action, source_applicable_items;
    Object unicode, category_evaluator_interface, function, gensymed_symbol_2;
    Object gensymed_symbol_3, gensymed_symbol_4, temp, value;
    SI_Long arg, arg_1, arg_2;

    x_note_fn_call(180,254);
    gensymed_symbol = allocate_evaluation_structure(Nil);
    int_op_type = CAR(slot_value);
    if (EQ(int_op_type,Qworkspace_menu))
	external_type = Qitem_menu;
    else if (EQ(int_op_type,Qtable))
	external_type = Qtable_menu;
    else if (EQ(int_op_type,Qvisibility))
	external_type = Qattribute_visibility;
    else if (EQ(int_op_type,Qpressing))
	external_type = Qtyping;
    else if (EQ(int_op_type,Qclicking))
	external_type = Qpressing_or_releasing;
    else if (EQ(int_op_type,Qconstrain))
	external_type = Qmoving;
    else
	external_type = int_op_type;
    set_evaluation_structure_slot(gensymed_symbol,Qoperation_type,
	    EQ(external_type,Qpressing_or_releasing) ? 
	    differentiate_pressing_from_releasing(CADR(slot_value)) : 
	    external_type);
    gensymed_symbol_1 = slot_value;
    gensymed_symbol_1 = CDR(gensymed_symbol_1);
    source_key_code = CAR(gensymed_symbol_1);
    gensymed_symbol_1 = CDR(gensymed_symbol_1);
    source_consequent_action = CAR(gensymed_symbol_1);
    gensymed_symbol_1 = CDR(gensymed_symbol_1);
    source_applicable_items = CAR(gensymed_symbol_1);
    gensymed_symbol_1 = allocate_evaluation_structure(Nil);
    arg = (SI_Long)65L;
    if (IFIX(FIXNUM_LOGAND(source_key_code,Unicode_bit)) != (SI_Long)0L) {
	unicode = FIXNUM_LOGAND(Unicode_character_bits,source_key_code);
	arg_1 = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) ? 
		IFIX(unicode) : IFIX(Illegal_key_index);
    }
    else
	arg_1 = IFIX(FIXNUM_LOGAND(Key_index_bits,source_key_code));
    arg_2 = (SI_Long)90L;
    if (arg <= arg_1 && arg_1 <= arg_2)
	source_key_code = FIX(IFIX(source_key_code) ^ (SI_Long)32L | 
		IFIX(Shift_bit));
    set_evaluation_structure_slot(gensymed_symbol_1,Qmouse_button,
	    key_code_mouse_button_name(source_key_code));
    set_evaluation_structure_slot(gensymed_symbol_1,Qmodifiers,
	    exported_key_modifier_bits(source_key_code));
    set_evaluation_structure_slot(gensymed_symbol,Qkey_code,gensymed_symbol_1);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Quser_interface_consequent_action),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = source_consequent_action;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	temp = Nil;
    set_evaluation_structure_slot(gensymed_symbol,Qconsequent_action,temp);
    value = 
	    make_acceptable_applicable_items_for_object_configuration(source_applicable_items);
    if (value)
	set_evaluation_structure_slot(gensymed_symbol,Qapplicable_items,value);
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object list_constant_55;    /* # */

static Object list_constant_56;    /* # */

/* CONFIGURE-SELECTION-EVALUATION-SETTER */
Object configure_selection_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, op_type;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object gensymed_symbol_5, parse_result_or_bad_phrase, error_string_qm;
    Object consequent_action_info, applicable_items_info;
    Declare_special(5);
    Object result;

    x_note_fn_call(180,255);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_55))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_56,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_configure_selection_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    op_type = estructure_slot(gensymed_symbol,Qoperation_type,Nil);
    if (EQ(op_type,Qitem_menu))
	temp_1 = Qworkspace_menu;
    else if (EQ(op_type,Qtable_menu))
	temp_1 = Qtable;
    else if (EQ(op_type,Qattribute_visibility))
	temp_1 = Qvisibility;
    else if (EQ(op_type,Qtyping))
	temp_1 = Qpressing;
    else if (EQ(op_type,Qpressing) || EQ(op_type,Qreleasing))
	temp_1 = Qclicking;
    else if (EQ(op_type,Qmoving))
	temp_1 = Qconstrain;
    else
	temp_1 = op_type;
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Quser_interface_consequent_action),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = estructure_slot(gensymed_symbol,
		Qconsequent_action,Nil);
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	gensymed_symbol_5 = Nil;
	result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4,gensymed_symbol_5);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	consequent_action_info = parse_result_or_bad_phrase;
    applicable_items_info = 
	    fix_acceptable_applicable_items_for_object_configuration(estructure_slot(gensymed_symbol,
	    Qapplicable_items,Nil));
    result = phrase_cons(temp_1,phrase_list_2(applicable_items_info,
	    consequent_action_info));
  end_safe_category_setter_calling_block:
  end_configure_selection_evaluation_setter:
    return result;
}

/* CONFIGURE-SELECTION-EVALUATION-GETTER */
Object configure_selection_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, gensymed_symbol_1, internal_operation_type;
    Object source_applicable_items, source_consequent_action, int_op_type;
    Object temp, value;

    x_note_fn_call(180,256);
    gensymed_symbol = allocate_evaluation_structure(Nil);
    gensymed_symbol_1 = slot_value;
    internal_operation_type = CAR(gensymed_symbol_1);
    gensymed_symbol_1 = CDR(gensymed_symbol_1);
    source_applicable_items = CAR(gensymed_symbol_1);
    gensymed_symbol_1 = CDR(gensymed_symbol_1);
    source_consequent_action = CAR(gensymed_symbol_1);
    int_op_type = internal_operation_type;
    if (EQ(int_op_type,Qworkspace_menu))
	temp = Qitem_menu;
    else if (EQ(int_op_type,Qtable))
	temp = Qtable_menu;
    else if (EQ(int_op_type,Qvisibility))
	temp = Qattribute_visibility;
    else if (EQ(int_op_type,Qpressing))
	temp = Qtyping;
    else if (EQ(int_op_type,Qclicking))
	temp = Qpressing_or_releasing;
    else if (EQ(int_op_type,Qconstrain))
	temp = Qmoving;
    else
	temp = int_op_type;
    set_evaluation_structure_slot(gensymed_symbol,Qoperation_type,temp);
    set_evaluation_structure_slot(gensymed_symbol,Qconsequent_action,
	    source_consequent_action);
    value = 
	    make_acceptable_applicable_items_for_object_configuration(source_applicable_items);
    if (value)
	set_evaluation_structure_slot(gensymed_symbol,Qapplicable_items,value);
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object list_constant_57;    /* # */

static Object list_constant_58;    /* # */

static Object Qleft_edge;          /* left-edge */

static Object Qright_edge;         /* right-edge */

static Object Qtop_edge;           /* top-edge */

static Object Qbottom_edge;        /* bottom-edge */

/* RECTANGLE-EVALUATION-SETTER */
Object rectangle_evaluation_setter(evaluation_value,frame,slot_description,
	    gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, temp_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(180,257);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_57))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_58,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_rectangle_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    temp_2 = estructure_slot(gensymed_symbol,Qleft_edge,Nil);
    temp = estructure_slot(gensymed_symbol,Qright_edge,Nil);
    temp_1 = estructure_slot(gensymed_symbol,Qtop_edge,Nil);
    result = phrase_list_4(temp_2,temp,temp_1,
	    estructure_slot(gensymed_symbol,Qbottom_edge,Nil));
  end_rectangle_evaluation_setter:
    return result;
}

/* RECTANGLE-EVALUATION-GETTER */
Object rectangle_evaluation_getter(source_constrained_region,frame,
	    slot_description)
    Object source_constrained_region, frame, slot_description;
{
    Object gensymed_symbol, gensymed_symbol_1, source_left_edge;
    Object source_right_edge, source_top_edge, source_bottom_edge;

    x_note_fn_call(180,258);
    gensymed_symbol = allocate_evaluation_structure(Nil);
    gensymed_symbol_1 = source_constrained_region;
    source_left_edge = CAR(gensymed_symbol_1);
    gensymed_symbol_1 = CDR(gensymed_symbol_1);
    source_right_edge = CAR(gensymed_symbol_1);
    gensymed_symbol_1 = CDR(gensymed_symbol_1);
    source_top_edge = CAR(gensymed_symbol_1);
    gensymed_symbol_1 = CDR(gensymed_symbol_1);
    source_bottom_edge = CAR(gensymed_symbol_1);
    set_evaluation_structure_slot(gensymed_symbol,Qleft_edge,source_left_edge);
    set_evaluation_structure_slot(gensymed_symbol,Qright_edge,
	    source_right_edge);
    set_evaluation_structure_slot(gensymed_symbol,Qtop_edge,source_top_edge);
    set_evaluation_structure_slot(gensymed_symbol,Qbottom_edge,
	    source_bottom_edge);
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object list_constant_59;    /* # */

static Object list_constant_60;    /* # */

static Object Qx_grid_length;      /* x-grid-length */

static Object string_constant_141;  /* "The x-grid-length, ~NV, must be positive" */

static Object Qy_grid_length;      /* y-grid-length */

static Object string_constant_142;  /* "The y-grid-length, ~NV, must be positive" */

/* GRID-EVALUATION-SETTER */
Object grid_evaluation_setter(evaluation_value,frame,slot_description,
	    gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(180,259);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_59))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_60,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_grid_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if ( !((SI_Long)0L < IFIX(estructure_slot(gensymed_symbol,
	    Qx_grid_length,Nil)))) {
	temp = Bad_phrase;
	temp_1 = tformat_text_string(2,string_constant_141,
		estructure_slot(gensymed_symbol,Qx_grid_length,Nil));
	result = VALUES_2(temp,temp_1);
    }
    else if ( !((SI_Long)0L < IFIX(estructure_slot(gensymed_symbol,
	    Qy_grid_length,Nil)))) {
	temp = Bad_phrase;
	temp_1 = tformat_text_string(2,string_constant_142,
		estructure_slot(gensymed_symbol,Qy_grid_length,Nil));
	result = VALUES_2(temp,temp_1);
    }
    else {
	temp_1 = estructure_slot(gensymed_symbol,Qx_grid_length,Nil);
	result = phrase_cons(temp_1,estructure_slot(gensymed_symbol,
		Qy_grid_length,Nil));
    }
  end_grid_evaluation_setter:
    return result;
}

/* GRID-EVALUATION-GETTER */
Object grid_evaluation_getter(source_constrained_region,frame,slot_description)
    Object source_constrained_region, frame, slot_description;
{
    Object gensymed_symbol;

    x_note_fn_call(180,260);
    gensymed_symbol = allocate_evaluation_structure(Nil);
    set_evaluation_structure_slot(gensymed_symbol,Qx_grid_length,
	    CAR(source_constrained_region));
    set_evaluation_structure_slot(gensymed_symbol,Qy_grid_length,
	    CDR(source_constrained_region));
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object list_constant_61;    /* # */

static Object list_constant_62;    /* # */

static Object Qtype_of_region;     /* type-of-region */

static Object Qconstrained_region;  /* constrained-region */

/* CONSTRAIN-MOVEMENT-OF-ITEMS-EVALUATION-SETTER */
Object constrain_movement_of_items_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object applicable_items_info, type_of_region_info;
    Object constrained_region_category_name, category_evaluator_interface;
    Object function, gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, parse_result_or_bad_phrase, error_string_qm;
    Object constrained_region_info;
    Declare_special(5);
    Object result;

    x_note_fn_call(180,261);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_61))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_62,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_constrain_movement_of_items_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    applicable_items_info = 
	    fix_acceptable_applicable_items_for_object_configuration(estructure_slot(gensymed_symbol,
	    Qapplicable_items,Nil));
    type_of_region_info = EQ(estructure_slot(gensymed_symbol,
	    Qtype_of_region,Nil),Qrectangle) ? 
	    estructure_slot(gensymed_symbol,Qtype_of_region,Nil) : Qmoving;
    constrained_region_category_name = estructure_slot(gensymed_symbol,
	    Qtype_of_region,Nil);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(constrained_region_category_name),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol = estructure_slot(gensymed_symbol,
		Qconstrained_region,Nil);
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	constrained_region_info = parse_result_or_bad_phrase;
    result = phrase_list_4(Qconstrain,type_of_region_info,
	    applicable_items_info,constrained_region_info);
  end_safe_category_setter_calling_block:
  end_constrain_movement_of_items_evaluation_setter:
    return result;
}

/* CONSTRAIN-MOVEMENT-OF-ITEMS-EVALUATION-GETTER */
Object constrain_movement_of_items_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, gensymed_symbol_1, source_type_of_region;
    Object source_applicable_items, source_constrained_region;
    Object category_evaluator_interface, function, gensymed_symbol_2;
    Object gensymed_symbol_3, gensymed_symbol_4, temp;

    x_note_fn_call(180,262);
    gensymed_symbol = allocate_evaluation_structure(Nil);
    gensymed_symbol_1 = slot_value;
    gensymed_symbol_1 = CDR(gensymed_symbol_1);
    source_type_of_region = CAR(gensymed_symbol_1);
    gensymed_symbol_1 = CDR(gensymed_symbol_1);
    source_applicable_items = CAR(gensymed_symbol_1);
    gensymed_symbol_1 = CDR(gensymed_symbol_1);
    source_constrained_region = CAR(gensymed_symbol_1);
    set_evaluation_structure_slot(gensymed_symbol,Qoperation_type,Qmoving);
    set_evaluation_structure_slot(gensymed_symbol,Qtype_of_region,
	    EQ(source_type_of_region,Qmoving) ? Qgrid : Qrectangle);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(estructure_slot(gensymed_symbol,
	    Qtype_of_region,Nil)),Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = source_constrained_region;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	temp = Nil;
    set_evaluation_structure_slot(gensymed_symbol,Qconstrained_region,temp);
    set_evaluation_structure_slot(gensymed_symbol,Qapplicable_items,
	    make_acceptable_applicable_items_for_object_configuration(source_applicable_items));
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object list_constant_63;    /* # */

static Object list_constant_64;    /* # */

static Object Qmenu_configurations;  /* menu-configurations */

static Object Qtable_menu_configurations;  /* table-menu-configurations */

static Object Qattribute_visibility_configurations;  /* attribute-visibility-configurations */

static Object Qconfigure_mouse_click;  /* configure-mouse-click */

static Object Qconfigure_keystroke;  /* configure-keystroke */

static Object Qconfigure_selection;  /* configure-selection */

static Object Qconstrain_movement_of_items;  /* constrain-movement-of-items */

/* RESTRICT-PROPRIETARY-ITEMS-AND-CONFIGURE-USER-INTERFACE-STATEMENT-EVALUATION-SETTER */
Object restrict_proprietary_items_and_configure_user_interface_statement_evaluation_setter(statement_element,
	    frame,slot_description,gensymed_symbol)
    Object statement_element, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, external_type;
    Object op_type, internal_operation_type, category_name_for_operation_type;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object parse_result_or_bad_phrase, error_string_qm;
    Declare_special(5);
    Object result;

    x_note_fn_call(180,263);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(statement_element,
			  list_constant_63))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(statement_element,
			      list_constant_64,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_restrict_proprietary_items_and_configure_user_interface_statement_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    external_type = estructure_slot(statement_element,Qoperation_type,Nil);
    op_type = external_type;
    if (EQ(op_type,Qitem_menu))
	internal_operation_type = Qworkspace_menu;
    else if (EQ(op_type,Qtable_menu))
	internal_operation_type = Qtable;
    else if (EQ(op_type,Qattribute_visibility))
	internal_operation_type = Qvisibility;
    else if (EQ(op_type,Qtyping))
	internal_operation_type = Qpressing;
    else if (EQ(op_type,Qpressing) || EQ(op_type,Qreleasing))
	internal_operation_type = Qclicking;
    else if (EQ(op_type,Qmoving))
	internal_operation_type = Qconstrain;
    else
	internal_operation_type = op_type;
    if (EQ(internal_operation_type,Qworkspace_menu) || 
	    EQ(internal_operation_type,Qitem_menu) || 
	    EQ(internal_operation_type,Qnon_menu))
	category_name_for_operation_type = Qmenu_configurations;
    else if (EQ(internal_operation_type,Qtable))
	category_name_for_operation_type = Qtable_menu_configurations;
    else if (EQ(internal_operation_type,Qvisibility))
	category_name_for_operation_type = 
		Qattribute_visibility_configurations;
    else if (EQ(internal_operation_type,Qclicking))
	category_name_for_operation_type = Qconfigure_mouse_click;
    else if (EQ(internal_operation_type,Qpressing))
	category_name_for_operation_type = Qconfigure_keystroke;
    else if (EQ(internal_operation_type,Qhovering))
	category_name_for_operation_type = Qconfigure_keystroke;
    else if (EQ(internal_operation_type,Qselecting) || 
	    EQ(internal_operation_type,Qselecting_absolutely))
	category_name_for_operation_type = Qconfigure_selection;
    else if (EQ(internal_operation_type,Qconstrain))
	category_name_for_operation_type = Qconstrain_movement_of_items;
    else
	category_name_for_operation_type = Qnil;
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(category_name_for_operation_type),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = statement_element;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	result = VALUES_1(parse_result_or_bad_phrase);
  end_safe_category_setter_calling_block:
  end_restrict_proprietary_items_and_configure_user_interface_statement_evaluation_setter:
    return result;
}

/* RESTRICT-PROPRIETARY-ITEMS-AND-CONFIGURE-USER-INTERFACE-STATEMENT-EVALUATION-GETTER */
Object restrict_proprietary_items_and_configure_user_interface_statement_evaluation_getter(statement_element,
	    frame,slot_description)
    Object statement_element, frame, slot_description;
{
    Object internal_operation_type, category_name_for_operation_type;
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp;

    x_note_fn_call(180,264);
    internal_operation_type = CAR(statement_element);
    if (EQ(internal_operation_type,Qworkspace_menu) || 
	    EQ(internal_operation_type,Qitem_menu) || 
	    EQ(internal_operation_type,Qnon_menu))
	category_name_for_operation_type = Qmenu_configurations;
    else if (EQ(internal_operation_type,Qtable))
	category_name_for_operation_type = Qtable_menu_configurations;
    else if (EQ(internal_operation_type,Qvisibility))
	category_name_for_operation_type = 
		Qattribute_visibility_configurations;
    else if (EQ(internal_operation_type,Qclicking))
	category_name_for_operation_type = Qconfigure_mouse_click;
    else if (EQ(internal_operation_type,Qpressing))
	category_name_for_operation_type = Qconfigure_keystroke;
    else if (EQ(internal_operation_type,Qhovering))
	category_name_for_operation_type = Qconfigure_keystroke;
    else if (EQ(internal_operation_type,Qselecting) || 
	    EQ(internal_operation_type,Qselecting_absolutely))
	category_name_for_operation_type = Qconfigure_selection;
    else if (EQ(internal_operation_type,Qconstrain))
	category_name_for_operation_type = Qconstrain_movement_of_items;
    else
	category_name_for_operation_type = Qnil;
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(category_name_for_operation_type),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = statement_element;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3);
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_65;    /* # */

static Object list_constant_66;    /* # */

static Object Qrestrict_proprietary_items_and_configure_user_interface_statement;  /* restrict-proprietary-items-and-configure-user-interface-statement */

/* CONFIGURE-USER-INTERFACE-STATEMENTS-EVALUATION-SETTER */
Object configure_user_interface_statements_evaluation_setter(statements,
	    frame,slot_description,gensymed_symbol)
    Object statements, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object statement_element, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_1;
    Object validated_elt, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, parse_result_or_bad_phrase, error_string_qm;
    SI_Long next_index, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(180,265);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(statements,
			  list_constant_65))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(statements,
			      list_constant_66,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_configure_user_interface_statements_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = statements;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    statement_element = Nil;
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
    statement_element = validated_elt;
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qrestrict_proprietary_items_and_configure_user_interface_statement),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = statement_element;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	temp_1 = parse_result_or_bad_phrase;
    ab_loopvar__2 = phrase_cons(temp_1,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    result = VALUES_1(ab_loopvar_);
    goto end_1;
    result = VALUES_1(Qnil);
  end_1:;
  end_safe_category_setter_calling_block:
  end_configure_user_interface_statements_evaluation_setter:
    return result;
}

/* CONFIGURE-USER-INTERFACE-STATEMENTS-EVALUATION-GETTER */
Object configure_user_interface_statements_evaluation_getter(statements,
	    frame,slot_description)
    Object statements, frame, slot_description;
{
    Object statement_element, ab_loop_list_, gensymed_symbol, ab_loopvar_;
    Object ab_loopvar__1, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, temp;

    x_note_fn_call(180,266);
    statement_element = Nil;
    ab_loop_list_ = statements;
    gensymed_symbol = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    statement_element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qrestrict_proprietary_items_and_configure_user_interface_statement),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = statement_element;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	temp = Nil;
    ab_loopvar__1 = eval_cons_1(temp,Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	gensymed_symbol = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    temp = allocate_evaluation_sequence(gensymed_symbol);
    goto end_1;
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(nreverse_evaluation_sequence(temp));
    return VALUES_1(Nil);
}

static Object list_constant_67;    /* # */

static Object list_constant_68;    /* # */

static Object Qnegative;           /* negative */

static Object Qmodes;              /* modes */

/* APPLICABLE-USER-MODES-EVALUATION-SETTER */
Object applicable_user_modes_evaluation_setter(applicable_user_modes,frame,
	    slot_description,gensymed_symbol)
    Object applicable_user_modes, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector, mode;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_1, validated_elt;
    SI_Long next_index, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(180,267);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(applicable_user_modes,
			  list_constant_67))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(applicable_user_modes,
			      list_constant_68,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_applicable_user_modes_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = applicable_user_modes;
    temp_1 = estructure_slot(gensymed_symbol,Qnegative,Nil);
    temp = CONSP(temp_1) && EQ(M_CDR(estructure_slot(gensymed_symbol,
	    Qnegative,Nil)),Qtruth_value) && 
	    evaluation_truth_value_is_true_p(estructure_slot(gensymed_symbol,
	    Qnegative,Nil)) ? Qunless : Qwhen;
    gensymed_symbol = estructure_slot(gensymed_symbol,Qmodes,Nil);
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    mode = Nil;
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
    mode = validated_elt;
    ab_loopvar__2 = phrase_cons(mode,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    temp_1 = ab_loopvar_;
    goto end_1;
    temp_1 = Qnil;
  end_1:;
    result = phrase_list_2(temp,temp_1);
  end_applicable_user_modes_evaluation_setter:
    return result;
}

/* APPLICABLE-USER-MODES-EVALUATION-GETTER */
Object applicable_user_modes_evaluation_getter(configure_user_interface_info,
	    frame,slot_description)
    Object configure_user_interface_info, frame, slot_description;
{
    Object gensymed_symbol;

    x_note_fn_call(180,268);
    gensymed_symbol = allocate_evaluation_structure(Nil);
    set_evaluation_structure_slot(gensymed_symbol,Qnegative,
	    EQ(CAR(configure_user_interface_info),Qunless) ? 
	    Evaluation_true_value : Evaluation_false_value);
    set_evaluation_structure_slot(gensymed_symbol,Qmodes,
	    allocate_evaluation_sequence(copy_list_using_eval_conses_1(SECOND(configure_user_interface_info))));
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object list_constant_69;    /* # */

static Object list_constant_70;    /* # */

static Object Qapplicable_user_modes;  /* applicable-user-modes */

static Object Qconfigure_user_interface_statements;  /* configure-user-interface-statements */

static Object Qstatements;         /* statements */

/* CONFIGURE-USER-INTERFACE-EVALUATION-SETTER */
Object configure_user_interface_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object configure_user_interface_info, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, elt_1, validated_elt, category_evaluator_interface;
    Object function, gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, gensymed_symbol_5, parse_result_or_bad_phrase;
    Object error_string_qm;
    SI_Long next_index, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(180,269);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_69))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_70,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_configure_user_interface_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    configure_user_interface_info = Nil;
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
    configure_user_interface_info = validated_elt;
    gensymed_symbol = configure_user_interface_info;
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qapplicable_user_modes),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = estructure_slot(gensymed_symbol,
		Qapplicable_user_modes,Nil);
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	gensymed_symbol_5 = Nil;
	result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4,gensymed_symbol_5);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	temp = parse_result_or_bad_phrase;
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qconfigure_user_interface_statements),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol = estructure_slot(gensymed_symbol,Qstatements,Nil);
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	temp_1 = parse_result_or_bad_phrase;
    ab_loopvar__2 = phrase_cons(nconc2(temp,temp_1),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    result = VALUES_1(ab_loopvar_);
    goto end_1;
    result = VALUES_1(Qnil);
  end_1:;
  end_safe_category_setter_calling_block:
  end_configure_user_interface_evaluation_setter:
    return result;
}

/* CONFIGURE-USER-INTERFACE-EVALUATION-GETTER */
Object configure_user_interface_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object configure_user_interface_info, ab_loop_list_, gensymed_symbol;
    Object ab_loopvar_, ab_loopvar__1, gensymed_symbol_1;
    Object category_evaluator_interface, function, gensymed_symbol_2;
    Object gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5, temp;

    x_note_fn_call(180,270);
    configure_user_interface_info = Nil;
    ab_loop_list_ = slot_value;
    gensymed_symbol = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    configure_user_interface_info = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol_1 = allocate_evaluation_structure(Nil);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qapplicable_user_modes),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol_2 = function;
	gensymed_symbol_3 = configure_user_interface_info;
	gensymed_symbol_4 = Nil;
	gensymed_symbol_5 = Nil;
	temp = inline_funcall_3(gensymed_symbol_2,gensymed_symbol_3,
		gensymed_symbol_4,gensymed_symbol_5);
    }
    else
	temp = Nil;
    set_evaluation_structure_slot(gensymed_symbol_1,Qapplicable_user_modes,
	    temp);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qconfigure_user_interface_statements),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol_2 = function;
	gensymed_symbol_3 = CDDR(configure_user_interface_info);
	gensymed_symbol_4 = Nil;
	gensymed_symbol_5 = Nil;
	temp = inline_funcall_3(gensymed_symbol_2,gensymed_symbol_3,
		gensymed_symbol_4,gensymed_symbol_5);
    }
    else
	temp = Nil;
    set_evaluation_structure_slot(gensymed_symbol_1,Qstatements,temp);
    ab_loopvar__1 = eval_cons_1(gensymed_symbol_1,Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	gensymed_symbol = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    temp = allocate_evaluation_sequence(gensymed_symbol);
    goto end_1;
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(nreverse_evaluation_sequence(temp));
    return VALUES_1(Nil);
}

static Object list_constant_71;    /* # */

/* RESTRICT-PROPRIETARY-ITEMS-EVALUATION-SETTER */
Object restrict_proprietary_items_evaluation_setter(statements,frame,
	    slot_description,gensymed_symbol)
    Object statements, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object statement_element, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_1;
    Object validated_elt, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, parse_result_or_bad_phrase, error_string_qm;
    SI_Long next_index, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(180,271);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(statements,
			  list_constant_71))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(statements,
			      list_constant_66,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_restrict_proprietary_items_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = statements;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    statement_element = Nil;
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
    statement_element = validated_elt;
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qrestrict_proprietary_items_and_configure_user_interface_statement),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = statement_element;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	temp_1 = parse_result_or_bad_phrase;
    ab_loopvar__2 = phrase_cons(temp_1,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    result = VALUES_1(ab_loopvar_);
    goto end_1;
    result = VALUES_1(Qnil);
  end_1:;
  end_safe_category_setter_calling_block:
  end_restrict_proprietary_items_evaluation_setter:
    return result;
}

/* RESTRICT-PROPRIETARY-ITEMS-EVALUATION-GETTER */
Object restrict_proprietary_items_evaluation_getter(statements,frame,
	    slot_description)
    Object statements, frame, slot_description;
{
    Object statement_element, ab_loop_list_, gensymed_symbol, ab_loopvar_;
    Object ab_loopvar__1, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, temp;

    x_note_fn_call(180,272);
    statement_element = Nil;
    ab_loop_list_ = statements;
    gensymed_symbol = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    statement_element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qrestrict_proprietary_items_and_configure_user_interface_statement),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = statement_element;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	temp = Nil;
    ab_loopvar__1 = eval_cons_1(temp,Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	gensymed_symbol = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    temp = allocate_evaluation_sequence(gensymed_symbol);
    goto end_1;
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_72;    /* # */

static Object list_constant_73;    /* # */

static Object Qallow;              /* allow */

static Object Qprohibit;           /* prohibit */

static Object Qprohibit_absolutely;  /* prohibit-absolutely */

static Object Qaccess_types;       /* access-types */

static Object Qaccess_agent;       /* access-agent */

/* SET-UP-NETWORK-ACCESS-EVALUATION-SETTER */
Object set_up_network_access_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object set_up_network_access_info, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, elt_1, validated_elt, internal_restriction_type;
    Object gensymed_symbol_1, held_vector_1, access_type_element;
    Object ab_loopvar__3, ab_loopvar__4, access_types_info;
    Object applicable_items_info;
    SI_Long next_index, length_1, next_index_1, length_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(180,273);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_72))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_73,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_set_up_network_access_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    set_up_network_access_info = Nil;
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
    set_up_network_access_info = validated_elt;
    gensymed_symbol = set_up_network_access_info;
    temp_1 = estructure_slot(gensymed_symbol,Qrestriction_type,Nil);
    if (EQ(temp_1,Qallow))
	internal_restriction_type = Qinclude_additionally;
    else if (EQ(temp_1,Qprohibit))
	internal_restriction_type = Qexclude_additionally;
    else if (EQ(temp_1,Qprohibit_absolutely))
	internal_restriction_type = Qexclude_absolutely;
    else
	internal_restriction_type = Qnil;
    gensymed_symbol_1 = estructure_slot(gensymed_symbol,Qaccess_types,Nil);
    held_vector_1 = Nil;
    next_index_1 = (SI_Long)1L;
    length_2 = (SI_Long)0L;
    access_type_element = Nil;
    ab_loopvar__2 = Nil;
    ab_loopvar__3 = Nil;
    ab_loopvar__4 = Nil;
    held_vector_1 = M_CAR(gensymed_symbol_1);
    length_2 = IFIX(ISVREF(held_vector_1,(SI_Long)1L));
  next_loop_1:
    if (next_index_1 >= length_2)
	goto end_loop_1;
    elt_1 = FIXNUM_LE(ISVREF(held_vector_1,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector_1,
	    next_index_1 + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(held_vector_1,(next_index_1 >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),next_index_1 & (SI_Long)1023L);
    validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	    Nil) : Nil;
    next_index_1 = next_index_1 + (SI_Long)1L;
    access_type_element = validated_elt;
    ab_loopvar__4 = phrase_cons(access_type_element,Nil);
    if (ab_loopvar__3)
	M_CDR(ab_loopvar__3) = ab_loopvar__4;
    else
	ab_loopvar__2 = ab_loopvar__4;
    ab_loopvar__3 = ab_loopvar__4;
    goto next_loop_1;
  end_loop_1:
    access_types_info = ab_loopvar__2;
    goto end_1;
    access_types_info = Qnil;
  end_1:;
    applicable_items_info = 
	    fix_acceptable_applicable_items_for_object_configuration(estructure_slot(gensymed_symbol,
	    Qapplicable_items,Nil));
    ab_loopvar__2 = 
	    phrase_cons(phrase_list_4(estructure_slot(gensymed_symbol,
	    Qaccess_agent,Nil),applicable_items_info,
	    internal_restriction_type,access_types_info),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    result = VALUES_1(ab_loopvar_);
    goto end_2;
    result = VALUES_1(Qnil);
  end_2:;
  end_set_up_network_access_evaluation_setter:
    return result;
}

/* SET-UP-NETWORK-ACCESS-EVALUATION-GETTER */
Object set_up_network_access_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object set_up_network_access_info, ab_loop_list_, gensymed_symbol;
    Object ab_loopvar_, ab_loopvar__1, gensymed_symbol_1, gensymed_symbol_2;
    Object source_access_agent, source_applicable_items;
    Object source_restriction_type, source_access_types, temp;
    Object source_access_type_element, ab_loop_list__1, ab_loopvar__2, value;

    x_note_fn_call(180,274);
    set_up_network_access_info = Nil;
    ab_loop_list_ = slot_value;
    gensymed_symbol = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    set_up_network_access_info = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol_1 = allocate_evaluation_structure(Nil);
    gensymed_symbol_2 = set_up_network_access_info;
    source_access_agent = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    source_applicable_items = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    source_restriction_type = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = CDR(gensymed_symbol_2);
    source_access_types = CAR(gensymed_symbol_2);
    if (EQ(source_restriction_type,Qinclude_additionally))
	temp = Qallow;
    else if (EQ(source_restriction_type,Qexclude_additionally))
	temp = Qprohibit;
    else if (EQ(source_restriction_type,Qexclude_absolutely))
	temp = Qprohibit_absolutely;
    else
	temp = Qnil;
    set_evaluation_structure_slot(gensymed_symbol_1,Qrestriction_type,temp);
    set_evaluation_structure_slot(gensymed_symbol_1,Qaccess_agent,
	    source_access_agent);
    source_access_type_element = Nil;
    ab_loop_list__1 = source_access_types;
    gensymed_symbol_2 = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    source_access_type_element = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    ab_loopvar__2 = eval_cons_1(source_access_type_element,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	gensymed_symbol_2 = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop_1;
  end_loop_1:
    temp = allocate_evaluation_sequence(gensymed_symbol_2);
    goto end_1;
    temp = Qnil;
  end_1:;
    set_evaluation_structure_slot(gensymed_symbol_1,Qaccess_types,temp);
    value = 
	    make_acceptable_applicable_items_for_object_configuration(source_applicable_items);
    if (value)
	set_evaluation_structure_slot(gensymed_symbol_1,Qapplicable_items,
		value);
    ab_loopvar__1 = eval_cons_1(gensymed_symbol_1,Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	gensymed_symbol = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    temp = allocate_evaluation_sequence(gensymed_symbol);
    goto end_2;
    temp = Qnil;
  end_2:;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

Object Declared_properties_attributes = UNBOUND;

static Object list_constant_74;    /* # */

static Object list_constant_75;    /* # */

static Object Qdeclared_properties;  /* declared-properties */

/* DECLARE-PROPERTIES-EVALUATION-SETTER */
Object declare_properties_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, gensymed_symbol_1;
    Object held_vector, property_name, attribute_value, property_value;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, declared_properties_info;
    Object applicable_items_info;
    SI_Long next_index, length_1, gensymed_symbol_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(180,275);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_74))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_75,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_declare_properties_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    gensymed_symbol_1 = estructure_slot(gensymed_symbol,
	    Qdeclared_properties,Nil);
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    property_name = Nil;
    attribute_value = Nil;
    property_value = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    held_vector = M_CAR(gensymed_symbol_1);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    property_name = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    gensymed_symbol_2 = next_index + (SI_Long)1L;
    attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,
	    gensymed_symbol_2 + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(held_vector,(gensymed_symbol_2 >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_2 & (SI_Long)1023L);
    property_value = validate_item_or_evaluation_value(attribute_value,Nil,
	    Nil);
    next_index = next_index + (SI_Long)2L;
    if (memq_function(property_name,Declared_properties_attributes)) {
	ab_loopvar__2 = phrase_cons(property_name,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	ab_loopvar__2 = 
		phrase_cons(evaluation_truth_value_is_true_p(property_value),
		Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    declared_properties_info = ab_loopvar_;
    goto end_1;
    declared_properties_info = Qnil;
  end_1:;
    applicable_items_info = 
	    fix_acceptable_applicable_items_for_object_configuration(estructure_slot(gensymed_symbol,
	    Qapplicable_items,Nil));
    result = phrase_cons(applicable_items_info,declared_properties_info);
  end_declare_properties_evaluation_setter:
    return result;
}

/* DECLARE-PROPERTIES-EVALUATION-GETTER */
Object declare_properties_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object features_list, feature_name, feature_value, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, temp, declared_properties_value;
    Object applicable_items_value, gensymed_symbol;

    x_note_fn_call(180,276);
    features_list = CDR(slot_value);
    feature_name = Nil;
    feature_value = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(features_list))
	goto end_loop;
    feature_name = CAR(features_list);
    feature_value = CADR(features_list);
    ab_loopvar__2 = eval_cons_1(feature_name,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    ab_loopvar__2 = eval_cons_1(feature_value ? Evaluation_true_value : 
	    Evaluation_false_value,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    features_list = CDDR(features_list);
    goto next_loop;
  end_loop:
    temp = ab_loopvar_;
    goto end_1;
    temp = Qnil;
  end_1:;
    declared_properties_value = allocate_evaluation_structure(temp);
    applicable_items_value = 
	    make_acceptable_applicable_items_for_object_configuration(CAR(slot_value));
    gensymed_symbol = allocate_evaluation_structure(Nil);
    set_evaluation_structure_slot(gensymed_symbol,Qdeclared_properties,
	    declared_properties_value);
    if ( ! !TRUEP(applicable_items_value))
	set_evaluation_structure_slot(gensymed_symbol,Qapplicable_items,
		applicable_items_value);
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object list_constant_76;    /* # */

static Object list_constant_77;    /* # */

static Object Qtag_name;           /* tag-name */

static Object Qassociated_text;    /* associated-text */

/* COMMENT-EVALUATION-SETTER */
Object comment_evaluation_setter(evaluation_value,frame,slot_description,
	    gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object element, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_1;
    Object validated_elt;
    SI_Long next_index, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(180,277);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_76))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_77,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_comment_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    element = Nil;
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
    element = validated_elt;
    gensymed_symbol = element;
    temp_1 = estructure_slot(gensymed_symbol,Qtag_name,Nil);
    ab_loopvar__2 = phrase_cons(phrase_list_2(temp_1,
	    INLINE_UNSIGNED_BYTE_16_VECTOR_P(estructure_slot(gensymed_symbol,
	    Qassociated_text,Nil)) != (SI_Long)0L ? 
	    copy_for_phrase(estructure_slot(gensymed_symbol,
	    Qassociated_text,Nil)) : Qnone),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    result = VALUES_1(ab_loopvar_);
    goto end_1;
    result = VALUES_1(Qnil);
  end_1:;
  end_comment_evaluation_setter:
    return result;
}

/* COMMENT-EVALUATION-GETTER */
Object comment_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object element, ab_loop_list_, gensymed_symbol, ab_loopvar_, ab_loopvar__1;
    Object gensymed_symbol_1, value, temp;

    x_note_fn_call(180,278);
    element = Nil;
    ab_loop_list_ = slot_value;
    gensymed_symbol = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol_1 = allocate_evaluation_structure(Nil);
    set_evaluation_structure_slot(gensymed_symbol_1,Qtag_name,CAR(element));
    value = text_string_p(CADR(element)) ? 
	    copy_as_wide_string(CADR(element)) : Nil;
    if (value)
	set_evaluation_structure_slot(gensymed_symbol_1,Qassociated_text,
		value);
    ab_loopvar__1 = eval_cons_1(gensymed_symbol_1,Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	gensymed_symbol = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    temp = allocate_evaluation_sequence(gensymed_symbol);
    goto end_1;
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_78;    /* # */

static Object list_constant_79;    /* # */

static Object Qconfigure_user_interface;  /* configure-user-interface */

static Object Qrestrict_proprietary_items;  /* restrict-proprietary-items */

static Object Qset_up_network_access;  /* set-up-network-access */

static Object Qdeclare_properties;  /* declare-properties */

static Object Qclauses;            /* clauses */

/* OBJECT-CONFIGURATION-SPEC-EVALUATION-SETTER */
Object object_configuration_spec_evaluation_setter(object_configuration_info,
	    frame,slot_description,gensymed_symbol)
    Object object_configuration_info, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, external_name;
    Object internal_configuration_type_name, category_name;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object parse_result_or_bad_phrase, error_string_qm;
    Declare_special(5);
    Object result;

    x_note_fn_call(180,279);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(object_configuration_info,
			  list_constant_78))) {
		      temp = Bad_phrase;
		      temp_1 = 
			      type_error_in_setter(object_configuration_info,
			      list_constant_79,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_object_configuration_spec_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = object_configuration_info;
    external_name = estructure_slot(gensymed_symbol,Qtype,Nil);
    if (EQ(external_name,Qconfigure_user_interface))
	internal_configuration_type_name = Quser_interface;
    else if (EQ(external_name,Qrestrict_proprietary_items))
	internal_configuration_type_name = Qproprietary;
    else if (EQ(external_name,Qset_up_network_access))
	internal_configuration_type_name = Qnetwork_access;
    else if (EQ(external_name,Qdeclare_properties))
	internal_configuration_type_name = Qdeclaration;
    else if (EQ(external_name,Qcomment))
	internal_configuration_type_name = Qcomment;
    else
	internal_configuration_type_name = Qnil;
    category_name = estructure_slot(gensymed_symbol,Qtype,Nil);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(category_name),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol = estructure_slot(gensymed_symbol,Qclauses,Nil);
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	temp_1 = parse_result_or_bad_phrase;
    result = phrase_cons(internal_configuration_type_name,temp_1);
  end_safe_category_setter_calling_block:
  end_object_configuration_spec_evaluation_setter:
    return result;
}

/* OBJECT-CONFIGURATION-SPEC-EVALUATION-GETTER */
Object object_configuration_spec_evaluation_getter(object_configuration_info,
	    frame,slot_description)
    Object object_configuration_info, frame, slot_description;
{
    Object gensymed_symbol, internal_type_name, internal_name;
    Object external_type_name, category_name, category_evaluator_interface;
    Object function, gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, temp;

    x_note_fn_call(180,280);
    gensymed_symbol = allocate_evaluation_structure(Nil);
    internal_type_name = CAR(object_configuration_info);
    internal_name = internal_type_name;
    if (EQ(internal_name,Quser_interface))
	external_type_name = Qconfigure_user_interface;
    else if (EQ(internal_name,Qproprietary))
	external_type_name = Qrestrict_proprietary_items;
    else if (EQ(internal_name,Qnetwork_access))
	external_type_name = Qset_up_network_access;
    else if (EQ(internal_name,Qdeclaration))
	external_type_name = Qdeclare_properties;
    else if (EQ(internal_name,Qcomment))
	external_type_name = Qcomment;
    else
	external_type_name = Qnil;
    category_name = external_type_name;
    set_evaluation_structure_slot(gensymed_symbol,Qtype,external_type_name);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(category_name),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = CDR(object_configuration_info);
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	temp = Nil;
    set_evaluation_structure_slot(gensymed_symbol,Qclauses,temp);
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object list_constant_80;    /* # */

static Object list_constant_81;    /* # */

static Object list_constant_82;    /* # */

static Object list_constant_83;    /* # */

static Object Qobject_configuration_spec;  /* object-configuration-spec */

static Object string_constant_143;  /* "~NT " */

static Object string_constant_144;  /* "~NV must be one of the following types: ~a" */

/* OBJECT-CONFIGURATION-EVALUATION-SETTER */
Object object_configuration_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object object_configuration_info, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, elt_1, validated_elt, category_evaluator_interface;
    Object function, gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, parse_result_or_bad_phrase, error_string_qm;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string;
    SI_Long next_index, length_1, bv16_length, aref_arg_2, aref_new_value;
    SI_Long length_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(180,281);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_80))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_81,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_object_configuration_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_82))
	result = VALUES_1(Qnone);
    else if (type_specification_type_p(gensymed_symbol,list_constant_83)) {
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	object_configuration_info = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop:
	if (next_index >= length_1)
	    goto end_loop;
	elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	object_configuration_info = validated_elt;
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qobject_configuration_spec),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = object_configuration_info;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    temp_1 = parse_result_or_bad_phrase;
	ab_loopvar__2 = phrase_cons(temp_1,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	temp_1 = ab_loopvar_;
	goto end_1;
	temp_1 = Qnil;
      end_1:;
	result = phrase_cons(Qsc,temp_1);
      end_safe_category_setter_calling_block:;
    }
    else {
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
		  tformat(2,string_constant_143,list_constant_82);
		  tformat(2,string_constant_143,list_constant_83);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_144,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_object_configuration_evaluation_setter:
    return result;
}

/* OBJECT-CONFIGURATION-EVALUATION-GETTER */
Object object_configuration_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object object_configuration_info, ab_loop_list_, gensymed_symbol;
    Object ab_loopvar_, ab_loopvar__1, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, temp;

    x_note_fn_call(180,282);
    if (slot_value) {
	object_configuration_info = Nil;
	ab_loop_list_ = slot_value;
	gensymed_symbol = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	object_configuration_info = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qobject_configuration_spec),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol_2 = object_configuration_info;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    temp = Nil;
	ab_loopvar__1 = eval_cons_1(temp,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    gensymed_symbol = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop;
      end_loop:
	temp = allocate_evaluation_sequence(gensymed_symbol);
	goto end_1;
	temp = Qnil;
      end_1:;
	temp = nreverse_evaluation_sequence(temp);
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_84;    /* # */

static Object list_constant_85;    /* # */

/* MAIN-MENU-RESTRICTIONS-STATEMENTS-EVALUATION-SETTER */
Object main_menu_restrictions_statements_evaluation_setter(statements,
	    frame,slot_description,gensymed_symbol)
    Object statements, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object statement_element, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_1;
    Object validated_elt, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, parse_result_or_bad_phrase, error_string_qm;
    SI_Long next_index, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(180,283);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(statements,
			  list_constant_84))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(statements,
			      list_constant_85,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_main_menu_restrictions_statements_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = statements;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    statement_element = Nil;
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
    statement_element = validated_elt;
    gensymed_symbol = statement_element;
    temp = estructure_slot(gensymed_symbol,Qrestriction_type,Nil);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qmenu_choices),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol = estructure_slot(gensymed_symbol,Qmenu_choices,Nil);
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	temp_1 = parse_result_or_bad_phrase;
    ab_loopvar__2 = phrase_cons(phrase_cons(Qmain_menu,phrase_cons(temp,
	    temp_1)),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    result = VALUES_1(ab_loopvar_);
    goto end_1;
    result = VALUES_1(Qnil);
  end_1:;
  end_safe_category_setter_calling_block:
  end_main_menu_restrictions_statements_evaluation_setter:
    return result;
}

/* MAIN-MENU-RESTRICTIONS-STATEMENTS-EVALUATION-GETTER */
Object main_menu_restrictions_statements_evaluation_getter(main_menu_restriction_info,
	    frame,slot_description)
    Object main_menu_restriction_info, frame, slot_description;
{
    Object statement_info, ab_loop_list_, gensymed_symbol, ab_loopvar_;
    Object ab_loopvar__1, gensymed_symbol_1, category_evaluator_interface;
    Object function, gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object gensymed_symbol_5, temp;

    x_note_fn_call(180,284);
    statement_info = Nil;
    ab_loop_list_ = CDDR(main_menu_restriction_info);
    gensymed_symbol = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    statement_info = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol_1 = allocate_evaluation_structure(Nil);
    set_evaluation_structure_slot(gensymed_symbol_1,Qrestriction_type,
	    SECOND(statement_info));
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qmenu_choices),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol_2 = function;
	gensymed_symbol_3 = CDDR(statement_info);
	gensymed_symbol_4 = Nil;
	gensymed_symbol_5 = Nil;
	temp = inline_funcall_3(gensymed_symbol_2,gensymed_symbol_3,
		gensymed_symbol_4,gensymed_symbol_5);
    }
    else
	temp = Nil;
    set_evaluation_structure_slot(gensymed_symbol_1,Qmenu_choices,temp);
    ab_loopvar__1 = eval_cons_1(gensymed_symbol_1,Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	gensymed_symbol = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    temp = allocate_evaluation_sequence(gensymed_symbol);
    goto end_1;
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(nreverse_evaluation_sequence(temp));
    return VALUES_1(Nil);
}

static Object list_constant_86;    /* # */

static Object list_constant_87;    /* # */

static Object Qmain_menu_restrictions_statements;  /* main-menu-restrictions-statements */

/* MAIN-MENU-RESTRICTIONS-EVALUATION-SETTER */
Object main_menu_restrictions_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object main_menu_restriction_info, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, elt_1, validated_elt, category_evaluator_interface;
    Object function, gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, gensymed_symbol_5, parse_result_or_bad_phrase;
    Object error_string_qm, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string;
    SI_Long next_index, length_1, bv16_length, aref_arg_2, aref_new_value;
    SI_Long length_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(180,285);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_86))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_87,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_main_menu_restrictions_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_82))
	result = VALUES_1(Qnone);
    else if (type_specification_type_p(gensymed_symbol,list_constant_83)) {
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	main_menu_restriction_info = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop:
	if (next_index >= length_1)
	    goto end_loop;
	elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	main_menu_restriction_info = validated_elt;
	gensymed_symbol = main_menu_restriction_info;
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qapplicable_user_modes),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol_2 = estructure_slot(gensymed_symbol,
		    Qapplicable_user_modes,Nil);
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    gensymed_symbol_5 = Nil;
	    result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3,gensymed_symbol_4,gensymed_symbol_5);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    temp = parse_result_or_bad_phrase;
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qmain_menu_restrictions_statements),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol = estructure_slot(gensymed_symbol,Qstatements,Nil);
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    temp_1 = parse_result_or_bad_phrase;
	ab_loopvar__2 = phrase_cons(nconc2(temp,temp_1),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	temp_1 = ab_loopvar_;
	goto end_1;
	temp_1 = Qnil;
      end_1:;
	result = phrase_cons(Qsc,temp_1);
    }
    else {
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
		  tformat(2,string_constant_143,list_constant_82);
		  tformat(2,string_constant_143,list_constant_83);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_144,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_safe_category_setter_calling_block:
  end_main_menu_restrictions_evaluation_setter:
    return result;
}

/* MAIN-MENU-RESTRICTIONS-EVALUATION-GETTER */
Object main_menu_restrictions_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object main_menu_restriction_info, ab_loop_list_, gensymed_symbol;
    Object ab_loopvar_, ab_loopvar__1, gensymed_symbol_1;
    Object category_evaluator_interface, function, gensymed_symbol_2;
    Object gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5, temp;

    x_note_fn_call(180,286);
    if (slot_value) {
	main_menu_restriction_info = Nil;
	ab_loop_list_ = slot_value;
	gensymed_symbol = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	main_menu_restriction_info = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol_1 = allocate_evaluation_structure(Nil);
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qapplicable_user_modes),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol_2 = function;
	    gensymed_symbol_3 = main_menu_restriction_info;
	    gensymed_symbol_4 = Nil;
	    gensymed_symbol_5 = Nil;
	    temp = inline_funcall_3(gensymed_symbol_2,gensymed_symbol_3,
		    gensymed_symbol_4,gensymed_symbol_5);
	}
	else
	    temp = Nil;
	set_evaluation_structure_slot(gensymed_symbol_1,
		Qapplicable_user_modes,temp);
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qmain_menu_restrictions_statements),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol_2 = function;
	    gensymed_symbol_3 = main_menu_restriction_info;
	    gensymed_symbol_4 = Nil;
	    gensymed_symbol_5 = Nil;
	    temp = inline_funcall_3(gensymed_symbol_2,gensymed_symbol_3,
		    gensymed_symbol_4,gensymed_symbol_5);
	}
	else
	    temp = Nil;
	set_evaluation_structure_slot(gensymed_symbol_1,Qstatements,temp);
	ab_loopvar__1 = eval_cons_1(gensymed_symbol_1,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    gensymed_symbol = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop;
      end_loop:
	temp = allocate_evaluation_sequence(gensymed_symbol);
	goto end_1;
	temp = Qnil;
      end_1:;
	temp = nreverse_evaluation_sequence(temp);
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_88;    /* # */

static Object list_constant_89;    /* # */

static Object Qcommand_choices;    /* command-choices */

/* GLOBAL-KEYBOARD-COMMAND-RESTRICTIONS-STATEMENTS-EVALUATION-SETTER */
Object global_keyboard_command_restrictions_statements_evaluation_setter(statements,
	    frame,slot_description,gensymed_symbol)
    Object statements, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object statement_element, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_1;
    Object validated_elt, restriction_type_info, held_vector_1;
    Object command_choice_element, ab_loopvar__3, ab_loopvar__4;
    SI_Long next_index, length_1, next_index_1, length_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(180,287);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(statements,
			  list_constant_88))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(statements,
			      list_constant_89,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_global_keyboard_command_restrictions_statements_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = statements;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    statement_element = Nil;
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
    statement_element = validated_elt;
    gensymed_symbol = statement_element;
    restriction_type_info = phrase_list_2(Qglobal_keyboard_command,
	    estructure_slot(gensymed_symbol,Qrestriction_type,Nil));
    gensymed_symbol = estructure_slot(gensymed_symbol,Qcommand_choices,Nil);
    held_vector_1 = Nil;
    next_index_1 = (SI_Long)1L;
    length_2 = (SI_Long)0L;
    command_choice_element = Nil;
    ab_loopvar__2 = Nil;
    ab_loopvar__3 = Nil;
    ab_loopvar__4 = Nil;
    held_vector_1 = M_CAR(gensymed_symbol);
    length_2 = IFIX(ISVREF(held_vector_1,(SI_Long)1L));
  next_loop_1:
    if (next_index_1 >= length_2)
	goto end_loop_1;
    elt_1 = FIXNUM_LE(ISVREF(held_vector_1,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector_1,
	    next_index_1 + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(held_vector_1,(next_index_1 >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),next_index_1 & (SI_Long)1023L);
    validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	    Nil) : Nil;
    next_index_1 = next_index_1 + (SI_Long)1L;
    command_choice_element = validated_elt;
    ab_loopvar__4 = phrase_cons(command_choice_element,Nil);
    if (ab_loopvar__3)
	M_CDR(ab_loopvar__3) = ab_loopvar__4;
    else
	ab_loopvar__2 = ab_loopvar__4;
    ab_loopvar__3 = ab_loopvar__4;
    goto next_loop_1;
  end_loop_1:
    temp_1 = ab_loopvar__2;
    goto end_1;
    temp_1 = Qnil;
  end_1:;
    ab_loopvar__2 = phrase_cons(nconc2(restriction_type_info,temp_1),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    result = VALUES_1(ab_loopvar_);
    goto end_2;
    result = VALUES_1(Qnil);
  end_2:;
  end_global_keyboard_command_restrictions_statements_evaluation_setter:
    return result;
}

/* GLOBAL-KEYBOARD-COMMAND-RESTRICTIONS-STATEMENTS-EVALUATION-GETTER */
Object global_keyboard_command_restrictions_statements_evaluation_getter(global_keyboard_command_restriction_info,
	    frame,slot_description)
    Object global_keyboard_command_restriction_info, frame, slot_description;
{
    Object statement_info, ab_loop_list_, gensymed_symbol, ab_loopvar_;
    Object ab_loopvar__1, gensymed_symbol_1, command_choice_element;
    Object ab_loop_list__1, gensymed_symbol_2, ab_loopvar__2, temp;

    x_note_fn_call(180,288);
    statement_info = Nil;
    ab_loop_list_ = CDDR(global_keyboard_command_restriction_info);
    gensymed_symbol = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    statement_info = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol_1 = allocate_evaluation_structure(Nil);
    set_evaluation_structure_slot(gensymed_symbol_1,Qrestriction_type,
	    SECOND(statement_info));
    command_choice_element = Nil;
    ab_loop_list__1 = CDDR(statement_info);
    gensymed_symbol_2 = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    command_choice_element = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    ab_loopvar__2 = eval_cons_1(command_choice_element,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	gensymed_symbol_2 = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop_1;
  end_loop_1:
    temp = allocate_evaluation_sequence(gensymed_symbol_2);
    goto end_1;
    temp = Qnil;
  end_1:;
    set_evaluation_structure_slot(gensymed_symbol_1,Qcommand_choices,temp);
    ab_loopvar__1 = eval_cons_1(gensymed_symbol_1,Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	gensymed_symbol = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    temp = allocate_evaluation_sequence(gensymed_symbol);
    goto end_2;
    temp = Qnil;
  end_2:;
    GENSYM_RETURN_ONE(nreverse_evaluation_sequence(temp));
    return VALUES_1(Nil);
}

static Object list_constant_90;    /* # */

static Object list_constant_91;    /* # */

static Object Qglobal_keyboard_command_restrictions_statements;  /* global-keyboard-command-restrictions-statements */

/* GLOBAL-KEYBOARD-COMMAND-RESTRICTIONS-EVALUATION-SETTER */
Object global_keyboard_command_restrictions_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object global_keyboard_command_restriction_info, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, elt_1, validated_elt;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object gensymed_symbol_5, parse_result_or_bad_phrase, error_string_qm;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string;
    SI_Long next_index, length_1, bv16_length, aref_arg_2, aref_new_value;
    SI_Long length_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(180,289);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_90))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_91,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_global_keyboard_command_restrictions_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_82))
	result = VALUES_1(Qnone);
    else if (type_specification_type_p(gensymed_symbol,list_constant_83)) {
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	global_keyboard_command_restriction_info = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop:
	if (next_index >= length_1)
	    goto end_loop;
	elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	global_keyboard_command_restriction_info = validated_elt;
	gensymed_symbol = global_keyboard_command_restriction_info;
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qapplicable_user_modes),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol_2 = estructure_slot(gensymed_symbol,
		    Qapplicable_user_modes,Nil);
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    gensymed_symbol_5 = Nil;
	    result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3,gensymed_symbol_4,gensymed_symbol_5);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    temp = parse_result_or_bad_phrase;
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qglobal_keyboard_command_restrictions_statements),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol = estructure_slot(gensymed_symbol,Qstatements,Nil);
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    temp_1 = parse_result_or_bad_phrase;
	ab_loopvar__2 = phrase_cons(nconc2(temp,temp_1),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	temp_1 = ab_loopvar_;
	goto end_1;
	temp_1 = Qnil;
      end_1:;
	result = phrase_cons(Qsc,temp_1);
    }
    else {
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
		  tformat(2,string_constant_143,list_constant_82);
		  tformat(2,string_constant_143,list_constant_83);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_144,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_safe_category_setter_calling_block:
  end_global_keyboard_command_restrictions_evaluation_setter:
    return result;
}

/* GLOBAL-KEYBOARD-COMMAND-RESTRICTIONS-EVALUATION-GETTER */
Object global_keyboard_command_restrictions_evaluation_getter(slot_value,
	    frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object global_keyboard_command_restriction_info, ab_loop_list_;
    Object gensymed_symbol, ab_loopvar_, ab_loopvar__1, gensymed_symbol_1;
    Object category_evaluator_interface, function, gensymed_symbol_2;
    Object gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5, temp;

    x_note_fn_call(180,290);
    if (slot_value) {
	global_keyboard_command_restriction_info = Nil;
	ab_loop_list_ = slot_value;
	gensymed_symbol = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	global_keyboard_command_restriction_info = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol_1 = allocate_evaluation_structure(Nil);
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qapplicable_user_modes),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol_2 = function;
	    gensymed_symbol_3 = global_keyboard_command_restriction_info;
	    gensymed_symbol_4 = Nil;
	    gensymed_symbol_5 = Nil;
	    temp = inline_funcall_3(gensymed_symbol_2,gensymed_symbol_3,
		    gensymed_symbol_4,gensymed_symbol_5);
	}
	else
	    temp = Nil;
	set_evaluation_structure_slot(gensymed_symbol_1,
		Qapplicable_user_modes,temp);
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qglobal_keyboard_command_restrictions_statements),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol_2 = function;
	    gensymed_symbol_3 = global_keyboard_command_restriction_info;
	    gensymed_symbol_4 = Nil;
	    gensymed_symbol_5 = Nil;
	    temp = inline_funcall_3(gensymed_symbol_2,gensymed_symbol_3,
		    gensymed_symbol_4,gensymed_symbol_5);
	}
	else
	    temp = Nil;
	set_evaluation_structure_slot(gensymed_symbol_1,Qstatements,temp);
	ab_loopvar__1 = eval_cons_1(gensymed_symbol_1,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    gensymed_symbol = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop;
      end_loop:
	temp = allocate_evaluation_sequence(gensymed_symbol);
	goto end_1;
	temp = Qnil;
      end_1:;
	temp = nreverse_evaluation_sequence(temp);
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* PSUEUDO-AUTHORIZED-OPTIONAL-MODULES-EVALUATION-GETTER */
Object psueudo_authorized_optional_modules_evaluation_getter(slot_value,
	    frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object element, ab_loop_list_, gensymed_symbol, ab_loopvar_, ab_loopvar__1;
    Object temp;

    x_note_fn_call(180,291);
    element = Nil;
    ab_loop_list_ = Authorized_products_of_this_machine;
    gensymed_symbol = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__1 = eval_cons_1(element,Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	gensymed_symbol = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    temp = allocate_evaluation_sequence(gensymed_symbol);
    goto end_1;
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_92;    /* # */

static Object list_constant_93;    /* # */

static Object Qdo_not_simulate;    /* do-not-simulate */

static Object string_constant_145;  /* "Illegal value ~NV" */

/* SIMULATED-PRODUCTS?-EVALUATION-SETTER */
Object simulated_products_qm_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object element, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_1;
    Object validated_elt, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string;
    SI_Long next_index, length_1, bv16_length, aref_arg_2, aref_new_value;
    SI_Long length_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(180,292);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_92))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_93,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_simulated_products_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_82))
	result = VALUES_1(Qnone);
    else if (type_specification_type_p(gensymed_symbol,Qsymbol)) {
	if (EQ(evaluation_value,Qdo_not_simulate))
	    result = VALUES_1(T);
	else {
	    temp = Bad_phrase;
	    temp_1 = tformat_text_string(2,string_constant_145,
		    evaluation_value);
	    result = VALUES_2(temp,temp_1);
	}
    }
    else if (type_specification_type_p(gensymed_symbol,list_constant_83)) {
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	element = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop:
	if (next_index >= length_1)
	    goto end_loop;
	elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	element = validated_elt;
	ab_loopvar__2 = phrase_cons(element,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	temp_1 = ab_loopvar_;
	goto end_1;
	temp_1 = Qnil;
      end_1:;
	result = phrase_cons(Qcm,temp_1);
    }
    else {
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
		  tformat(2,string_constant_143,list_constant_82);
		  tformat(2,string_constant_143,Qsymbol);
		  tformat(2,string_constant_143,list_constant_83);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_144,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_simulated_products_qm_evaluation_setter:
    return result;
}

/* SIMULATED-PRODUCTS?-EVALUATION-GETTER */
Object simulated_products_qm_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp, element, ab_loop_list_, gensymed_symbol, ab_loopvar_;
    Object ab_loopvar__1;

    x_note_fn_call(180,293);
    if (slot_value) {
	if (EQ(slot_value,T))
	    temp = Qdo_not_simulate;
	else {
	    element = Nil;
	    ab_loop_list_ = slot_value;
	    gensymed_symbol = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    element = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loopvar__1 = eval_cons_1(element,Nil);
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		gensymed_symbol = ab_loopvar__1;
	    ab_loopvar_ = ab_loopvar__1;
	    goto next_loop;
	  end_loop:
	    temp = allocate_evaluation_sequence(gensymed_symbol);
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object Qg2_login_user_mode;  /* g2-login-user-mode */

static Object Qfloat_array;        /* float-array */

static Object Quser_mode_aliases;  /* user-mode-aliases */

/* MAKE-NEW-ALIAS */
Object make_new_alias(g2_login)
    Object g2_login;
{
    Object alias, alias_name, alias_parent, amf_available_array_cons_qm;
    Object amf_array, temp, temp_1, amf_result, new_float, temp_2;
    Object scope_conses, ab_loopvar_, ab_loopvar__1, item;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_3;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(180,294);
    alias = make_user_mode_alias_1();
    alias_name = get_lookup_slot_value_given_default(g2_login,
	    Qg2_login_user_name_qm,Nil);
    alias_parent = get_lookup_slot_value_given_default(g2_login,
	    Qg2_login_user_mode,Nil);
    SVREF(alias,FIX((SI_Long)1L)) = alias_name;
    SVREF(alias,FIX((SI_Long)2L)) = alias_parent;
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
    aref_new_value = g2ext_unix_time_as_float();
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
    SVREF(alias,FIX((SI_Long)3L)) = new_float;
    temp = Current_g2_user_mode_qm;
    SVREF(alias,FIX((SI_Long)4L)) = temp;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Kb_configuration,Quser_mode_aliases);
    temp_2 = Kb_configuration;
    set_lookup_slot_value_1(temp_2,Quser_mode_aliases,gensym_cons_1(alias,
	    get_lookup_slot_value_given_default(Kb_configuration,
	    Quser_mode_aliases,Nil)));
    add_or_delete_mode_name_from_directory_of_names(alias_name,Nil);
    add_alias_to_configuration(Qmain_menu_user_restrictions,
	    Kb_configuration,alias_name,alias_parent);
    add_alias_to_configuration(Qglobal_keyboard_command_user_restrictions,
	    Kb_configuration,alias_name,alias_parent);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    item = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qitem);
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
      item = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      add_alias_to_configuration(Qobject_configuration,item,alias_name,
	      alias_parent);
      sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
      superior_class_bit_number = 
	      IFIX(ISVREF(Class_definition_class_description,(SI_Long)18L));
      sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
      if (sub_class_vector_index < 
	      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	  gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		  sub_class_vector_index);
	  gensymed_symbol_1 = (SI_Long)1L;
	  gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	  gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	  gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	  temp_3 = (SI_Long)0L < gensymed_symbol;
      }
      else
	  temp_3 = TRUEP(Nil);
      if (temp_3)
	  add_alias_to_configuration(Qinstance_configuration,item,
		  alias_name,alias_parent);
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    return VALUES_1(T);
}

void filters_INIT()
{
    Object g2_user_mode_for_login_evaluation_setter_1;
    Object g2_user_mode_for_login_evaluation_getter_1;
    Object g2_user_mode_for_login_qm_evaluation_getter_1, temp, temp_1, temp_2;
    Object gensymed_symbol;
    Object write_note_status_of_simulated_product_authorization_note_1;
    Object menu_and_attribute_visibility_configurations_restriction_type_evaluation_setter_1;
    Object menu_and_attribute_visibility_configurations_restriction_type_evaluation_getter_1;
    Object table_menu_choice_evaluation_setter_1;
    Object table_menu_choice_evaluation_getter_1;
    Object table_menu_choices_evaluation_setter_1;
    Object table_menu_choices_evaluation_getter_1;
    Object menu_choices_evaluation_setter_1, menu_choices_evaluation_getter_1;
    Object table_menu_configurations_evaluation_setter_1;
    Object table_menu_configurations_evaluation_getter_1;
    Object menu_configurations_evaluation_setter_1;
    Object menu_configurations_evaluation_getter_1;
    Object attribute_visibility_configurations_evaluation_setter_1;
    Object attribute_visibility_configurations_evaluation_getter_1;
    Object user_interface_consequent_action_evaluation_setter_1;
    Object user_interface_consequent_action_evaluation_getter_1;
    Object modifier_key_evaluation_setter_1, modifier_key_evaluation_getter_1;
    Object keyboard_symbol_evaluation_setter_1;
    Object keyboard_symbol_evaluation_getter_1;
    Object mouse_button_evaluation_setter_1, mouse_button_evaluation_getter_1;
    Object user_interface_key_chord_evaluation_setter_1;
    Object user_interface_key_chord_evaluation_getter_1;
    Object configure_keystroke_evaluation_setter_1;
    Object configure_keystroke_evaluation_getter_1;
    Object configure_mouse_click_evaluation_setter_1;
    Object configure_mouse_click_evaluation_getter_1;
    Object configure_selection_evaluation_setter_1;
    Object configure_selection_evaluation_getter_1;
    Object rectangle_evaluation_setter_1, rectangle_evaluation_getter_1;
    Object grid_evaluation_setter_1, grid_evaluation_getter_1;
    Object constrain_movement_of_items_evaluation_setter_1;
    Object constrain_movement_of_items_evaluation_getter_1;
    Object restrict_proprietary_items_and_configure_user_interface_statement_evaluation_setter_1;
    Object restrict_proprietary_items_and_configure_user_interface_statement_evaluation_getter_1;
    Object configure_user_interface_statements_evaluation_setter_1;
    Object configure_user_interface_statements_evaluation_getter_1;
    Object applicable_user_modes_evaluation_setter_1;
    Object applicable_user_modes_evaluation_getter_1;
    Object configure_user_interface_evaluation_setter_1;
    Object configure_user_interface_evaluation_getter_1;
    Object restrict_proprietary_items_evaluation_setter_1;
    Object restrict_proprietary_items_evaluation_getter_1;
    Object set_up_network_access_evaluation_setter_1;
    Object set_up_network_access_evaluation_getter_1;
    Object declare_properties_evaluation_setter_1;
    Object declare_properties_evaluation_getter_1, comment_evaluation_setter_1;
    Object comment_evaluation_getter_1;
    Object object_configuration_spec_evaluation_setter_1;
    Object object_configuration_spec_evaluation_getter_1;
    Object object_configuration_evaluation_setter_1;
    Object object_configuration_evaluation_getter_1;
    Object main_menu_restrictions_statements_evaluation_setter_1;
    Object main_menu_restrictions_statements_evaluation_getter_1;
    Object main_menu_restrictions_evaluation_setter_1;
    Object main_menu_restrictions_evaluation_getter_1;
    Object global_keyboard_command_restrictions_statements_evaluation_setter_1;
    Object global_keyboard_command_restrictions_statements_evaluation_getter_1;
    Object global_keyboard_command_restrictions_evaluation_setter_1;
    Object global_keyboard_command_restrictions_evaluation_getter_1;
    Object psueudo_authorized_optional_modules_evaluation_getter_1;
    Object simulated_products_qm_evaluation_setter_1;
    Object simulated_products_qm_evaluation_getter_1;
    Object AB_package, Qsimulated_products_qm, Qnamed, list_constant_175;
    Object list_constant_311, Qtype_specification_simple_expansion;
    Object list_constant_310, Qpsueudo_authorized_optional_modules;
    Object list_constant_150, Qglobal_keyboard_command_restrictions;
    Object list_constant_309, list_constant_234, list_constant_308;
    Object list_constant_297, list_constant_307, Qab_structure;
    Object list_constant_306, list_constant_242, list_constant_285;
    Object list_constant_305, list_constant_304, list_constant_303;
    Object list_constant_302, list_constant_152, list_constant_301;
    Object list_constant_300, list_constant_102, Qmain_menu_restrictions;
    Object list_constant_299, list_constant_298, list_constant_296;
    Object list_constant_245, list_constant_295, list_constant_294;
    Object list_constant_293, list_constant_292, list_constant_291;
    Object list_constant_290, list_constant_289, list_constant_288;
    Object list_constant_171, list_constant_287, list_constant_104;
    Object list_constant_286, list_constant_284, list_constant_283;
    Object list_constant_282, list_constant_281, list_constant_280;
    Object list_constant_279, list_constant_278, list_constant_148;
    Object list_constant_277, list_constant_276, list_constant_275;
    Object list_constant_274, list_constant_273, list_constant_272;
    Object list_constant_271, list_constant_161, list_constant_270;
    Object list_constant_269, list_constant_268, list_constant_267;
    Object list_constant_257, list_constant_266, list_constant_265;
    Object list_constant_264, list_constant_263, list_constant_262;
    Object list_constant_261, list_constant_260, list_constant_259;
    Object list_constant_258, list_constant_235, Qexternal_simulation;
    Object Qactivatable_subworkspace, Qdeclared_properties_attributes;
    Object list_constant_256, list_constant_255, list_constant_254;
    Object list_constant_253, list_constant_252, list_constant_251;
    Object list_constant_250, Qtelewindows_and_gsi;
    Object Qg2_and_telewindows_and_gsi, list_constant_249, list_constant_248;
    Object list_constant_247, list_constant_246, list_constant_244;
    Object list_constant_243, list_constant_241, list_constant_240;
    Object list_constant_239, list_constant_238, list_constant_237;
    Object list_constant_236, Qunreserved_symbol, list_constant_233;
    Object list_constant_232, list_constant_231, list_constant_230;
    Object list_constant_229, list_constant_228, list_constant_227;
    Object list_constant_226, list_constant_225, list_constant_224;
    Object list_constant_223, list_constant_222, list_constant_221;
    Object list_constant_220, list_constant_219, list_constant_212;
    Object list_constant_218, list_constant_217, list_constant_216;
    Object list_constant_215, list_constant_214, list_constant_213;
    Object list_constant_211, list_constant_210, list_constant_209;
    Object list_constant_203, list_constant_208, list_constant_207;
    Object list_constant_206, list_constant_205, list_constant_204;
    Object list_constant_193, list_constant_202, list_constant_201;
    Object list_constant_191, list_constant_200, list_constant_199;
    Object list_constant_198, list_constant_197, list_constant_196;
    Object list_constant_183, list_constant_195, list_constant_194;
    Object list_constant_192, list_constant_190, list_constant_189;
    Object list_constant_188, list_constant_187, list_constant_186;
    Object list_constant_185, list_constant_184, list_constant_112;
    Object Qmodifier_key, list_constant_182, list_constant_181;
    Object list_constant_180, list_constant_179, list_constant_178;
    Object list_constant_177, list_constant_176, list_constant_174;
    Object list_constant_99, list_constant_173, list_constant_172;
    Object list_constant_170, list_constant_169, list_constant_168;
    Object list_constant_167, list_constant_166, list_constant_165;
    Object list_constant_164, list_constant_163, list_constant_162;
    Object list_constant_157, list_constant_160, list_constant_159;
    Object list_constant_155, list_constant_158, list_constant_108;
    Object list_constant_156, list_constant_154, list_constant_153;
    Object list_constant_151, list_constant_149, list_constant_147;
    Object list_constant_101;
    Object Qmenu_and_attribute_visibility_configurations_restriction_type;
    Object list_constant_107, Qmarshall_exceptional_float_arguments;
    Object list_constant_96, Qfunction_keeps_procedure_environment_valid_qm;
    Object Qset_inherit_stdio_handles, Qg2_describe_g2_license, Qlicense_level;
    Object Qframe_note_writer_1, string_constant_264, string_constant_263;
    Object string_constant_262, string_constant_261, Qgfi, Qicp, Qslot_putter;
    Object Qput_simulated_optional_modules, string_constant_260;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler, Qcompile_simulated_products_qm_for_slot;
    Object Qslot_value_writer, Qwrite_simulated_products_qm_from_slot;
    Object Qwrite_psueudo_authorized_optional_modules_from_slot;
    Object list_constant_146, list_constant_145, list_constant_144;
    Object Qblock_visible_to_inspect, list_constant_143, list_constant_142;
    Object Qmake_permanent, list_constant_141, list_constant_138;
    Object Qmake_transient, list_constant_140, Qchange_set_of_inferiors;
    Object list_constant_139, Qclone_block, Qchange_superior;
    Object list_constant_137, list_constant_136, list_constant_135;
    Object list_constant_134, list_constant_133, Qedit, list_constant_132;
    Object list_constant_131, list_constant_130;
    Object Qg2_set_all_items_in_module_explicitly_editable;
    Object Qg2_set_item_and_all_its_subblocks_explicitly_editable;
    Object Qg2_set_item_explicitly_editable, list_constant_129;
    Object list_constant_128, list_constant_127, string_constant_259;
    Object string_constant_258, string_constant_257, Qg2_item_is_editable;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qmodule_is_explictly_editable_p;
    Object Qdo_not_carry_global_property_value_into_kbs_qm, list_constant_126;
    Object list_constant_125, list_constant_124, list_constant_123;
    Object list_constant_122, list_constant_121, list_constant_120;
    Object list_constant_119, Qattribute_initializations, Qdefault_settings;
    Object Qclass_specific_attributes, Qattributes_specific_to_class;
    Object Qdirect_superior_classes, Qsuperior_class, list_constant_118;
    Object Qdescribe_configuration, Qdescribe_restrictions;
    Object Qcompile_object_configuration_for_slot, Qput_frame_style;
    Object Qslot_value_reclaimer, Qreclaim_instance_configuration_value;
    Object Qput_instance_configuration, Qput_object_configuration;
    Object Qg2_clear_movement_grid, Qg2_get_movement_grid;
    Object Qg2_set_movement_grid, list_constant_117, Qg2_clear_movement_limits;
    Object Qg2_get_movement_limits, Qg2_set_movement_limits;
    Object Qwrite_class_restrictions_from_slot;
    Object Qwrite_user_restrictions_from_slot;
    Object Qwrite_global_keyboard_command_restrictions_from_slot;
    Object Qwrite_main_menu_restrictions_from_slot;
    Object Qput_initial_g2_user_mode_for_this_kb, Qput_class_restrictions;
    Object Qput_user_restrictions, Qcompile_user_restrictions_for_slot;
    Object Qput_global_keyboard_command_user_restrictions;
    Object Qput_main_menu_user_restrictions;
    Object Qcompile_global_keyboard_command_restrictions_for_slot;
    Object Qcompile_main_menu_restrictions_for_slot, Qclasses_which_define;
    Object Qdeinstall_system_table;
    Object Qdeinstall_system_table_for_kb_configuration, Qinstall_system_table;
    Object Qinstall_system_table_for_kb_configuration;
    Object Qkeyboard_command_restrictions, Qauthorized_optional_modules;
    Object Qauthorized_optional_modules_for_this_machine;
    Object Qinitialize_after_reading;
    Object Qinitialize_after_reading_for_kb_configuration;
    Object Qsubstitute_class_and_kb_flags, list_constant_116, Qfilters;
    Object Kfuncall, Ksystem_frame, string_constant_256, list_constant_115;
    Object string_constant_255, string_constant_245, string_constant_254;
    Object string_constant_253, string_constant_252, list_constant_114;
    Object string_constant_251, string_constant_250, string_constant_249;
    Object string_constant_248, string_constant_247, string_constant_246;
    Object Qsystem_table, Qreclaim_object_configuration_value;
    Object Qwrite_object_configuration_from_slot;
    Object Qfix_tailing_associative_list, Qfix_associative_list;
    Object Qdont_include_workspace, Qfix_mode_restriction, Qcons_car_cddr;
    Object Qnon_menu_choice, Qitem_menu_choice, Qitem_menu_choices;
    Object Qworkspace_menu_choice, string_constant_244;
    Object Qsystem_or_user_defined_attribute_name, Qattribute_names_or;
    Object string_constant_243;
    Object Qconvert_class_qualified_list_to_keyword_symbol;
    Object Quser_attribute_name, Quser_attribute_names, string_constant_242;
    Object string_constant_241, Qattribute_names, Qrestrictable_class;
    Object Qrestrictable_classes, Qprohibit_nothing, string_constant_240;
    Object string_constant_239, string_constant_238, Qselect_area;
    Object list_constant_113, Qselect_object, Qallow_selection_of_text;
    Object Qallow_selection_of_outside_text_from_editor;
    Object Qdo_not_clear_text_for_edit_in_place, Qmenus_for_edit_in_place;
    Object Qoption_buttons_for_edit_in_place, Qfull_editor, Qclick_to_edit;
    Object Qscale_workspace, Qmove_workspaces_beyond_window_margin;
    Object Qmove_workspace, Qmove_connection;
    Object Qmove_objects_beyond_workspace_margin, Qmove_object;
    Object string_constant_237, string_constant_236, string_constant_235;
    Object string_constant_234, string_constant_233, string_constant_232;
    Object string_constant_231, string_constant_230, string_constant_229;
    Object string_constant_228, string_constant_227, string_constant_226;
    Object string_constant_225, string_constant_224, string_constant_223;
    Object string_constant_222, Quser_restriction_clause;
    Object Quser_restriction_clause_list, string_constant_221;
    Object Quser_mode_restriction, string_constant_220, Qcomment_option;
    Object Qcomment_options, string_constant_219;
    Object Qproprietary_restriction_clause;
    Object Qproprietary_restriction_clause_list, string_constant_218;
    Object Qfix_object_configuration_clause, string_constant_217;
    Object string_constant_216, Qremove_separator_symbol_from_phrase;
    Object string_constant_215, Qmodifier_key_list, string_constant_214;
    Object string_constant_213, Qparse_user_interface_key_chord;
    Object string_constant_212, string_constant_211, string_constant_210;
    Object string_constant_209, string_constant_208, string_constant_207;
    Object Qparse_user_interface_gesture, string_constant_206;
    Object Qgrid_spec_must_be_positive, string_constant_205;
    Object Qfix_item_filter_phrase, string_constant_204, string_constant_203;
    Object string_constant_202, Quser_restrictable_class;
    Object Quser_restrictable_classes, string_constant_201;
    Object string_constant_200, string_constant_199, string_constant_198;
    Object string_constant_197, string_constant_196, string_constant_195;
    Object string_constant_194, string_constant_193, string_constant_192;
    Object string_constant_191, string_constant_190, string_constant_189;
    Object string_constant_188, Qstring_to_insert_for_keyboard_symbol;
    Object Qstring_to_display_for_keyboard_symbol, list_constant_111, Qcol, Q9;
    Object Q8, Q7, Q6, Q5, Q4, Q3, Q2, Q1, Q0, Qescape, Qlinefeed, Qtab;
    Object Qbackspace, Qf12, Qf11, Qf10, Qf9, Qf8, Qf7, Qf6, Qf5, Qf4, Qf3;
    Object Qf2, Qf1, list_constant_110, Qct, Qcbt, Qobt, Qz, Qy, Qx, Qw, Qv;
    Object Qu, Qs, Qr, Qq, Qp, Qo, Qn, Qm, Ql, Qk, Qj, Qi, Qh, Qg, Qf, Qe, Qd;
    Object Qc, Qb, Qa, Qqm, list_constant_109, Qredo, Qinsert, Qhelp, Qenter;
    Object Qmouse_hover, Qmouse_wheel_backward, Qmouse_wheel_forward, Qdot;
    Object Qcp, Qop, Qqu, Qab_and, Qpct, Qdol, Qno, Qdq, Qex, Qcb, Qab_or_1;
    Object Qob, Qbq, Q_, Qnext_screen, Qprevious_screen, Qright_arrow;
    Object Qleft_arrow, Qdown_arrow, Qup_arrow, Qclear_screen, Qabort_g2;
    Object Qselect, Qpause, Qend, Qbegin, Qhome, Quser_annotation_clause;
    Object Quser_annotation_clause_list, string_constant_187;
    Object Quser_mode_annotation, Quser_mode_annotations, string_constant_186;
    Object string_constant_185, string_constant_184, string_constant_183;
    Object string_constant_182, string_constant_181, string_constant_180;
    Object string_constant_179, string_constant_178, string_constant_177;
    Object string_constant_176, Qnetwork_accessing_product;
    Object Qnetwork_accessing_product_list, Qg2_network_access_type;
    Object Qg2_network_access_type_list, Qcommon_network_access_type;
    Object Qcommon_network_access_type_list, string_constant_175;
    Object string_constant_174, string_constant_173, string_constant_172;
    Object string_constant_171, string_constant_170, string_constant_169;
    Object string_constant_168, string_constant_167, Qnetwork_access_option;
    Object Qnetwork_access_options, string_constant_166, string_constant_165;
    Object string_constant_164, Quser_declaration_element, Quser_declarations;
    Object Qmassage_user_declaration_clause, string_constant_163;
    Object string_constant_162, string_constant_161, string_constant_160;
    Object Qfix_network_configuration_clause, string_constant_159;
    Object string_constant_158, Qobject_configuration_clause;
    Object list_constant_106, list_constant_105, Qdo_not_single_step;
    Object Qsingle_step, Qredo_layout_of_g2gl_body;
    Object Qexecute_g2gl_process_workspace;
    Object Qclean_up_g2gl_compilation_postings_on_body;
    Object Qcompile_g2gl_process_workspace, Qtoggle_visible_grid;
    Object Qview_change_log, Qab_describe, Qoperate_on_area, Qmiscellany;
    Object Qdisable, Qenable, Qdelete_workspace, Qshrink_wrap, Qdrop_to_bottom;
    Object Qlift_to_top, Qgo_to_superior, Qhide_workspace, Qmove, Qcolor;
    Object Qclone_workspace, Qname, Qnew_button, Qnew_free_text;
    Object Qnew_definition, Qnew_display, Qnew_rule, Qnew_object;
    Object Qremove_do_not_strip_text_mark, Qremove_do_not_strip_text_mark_star;
    Object Qmark_not_to_strip_text, Qmark_not_to_strip_text_star;
    Object Qremove_strip_text_mark_star, Qremove_strip_text_mark;
    Object Qmark_to_strip_text_star, Qmark_to_strip_text, Qprint_to_server;
    Object Qg2gl_system_attributes, Qprocess_display_attributes;
    Object Qdelete_process_instance, Qresume_process_instance;
    Object Qpause_process_instance, Qbring_up_source;
    Object Qremove_all_temporary_breakpoints;
    Object Qdo_not_break_on_execution_faults, Qbreak_on_execution_faults;
    Object Qclose_and_continue, list_constant_103, Qload_attribute_file;
    Object Qdisconnect_from_foreign_image, Qconnect_to_foreign_image;
    Object Qreinstall_authorized_users, Qchange_password, Qlog_out;
    Object Qclose_telewindows_connection, Qnetwork_info, Qneatly_stack_windows;
    Object Qnew_title_block, Qdelete_module, Qcreate_new_module, Qshort_menus;
    Object Qlong_menus, Qchange_mode, Qrun_options, Qsystem_tables, Qsave_kb;
    Object Qmerge_kb, Qload_kb, Qload_merge_save, Qget_workspace;
    Object Qtable_of_attributes_pane, Qnew_workspace, Qab_restart, Qreset;
    Object Qresume, Qstart, Qprint_window, Qlaunch_online_help;
    Object Qremove_tracing_and_breakpoints, Qenable_all_items;
    Object Qhighlight_invoked_rules, Qdo_not_highlight_invoked_rules;
    Object Qleave_simulate_proprietary_mode, Qenter_simulate_proprietary_mode;
    Object Qflush_change_log_for_entire_kb, Qmake_workspaces_proprietary_now;
    Object Qstrip_texts_now, Qleave_package_preparation_mode;
    Object Qenter_package_preparation_mode, Qturn_off_all_explanation_caching;
    Object Qturn_on_all_explanation_caching, Qshut_down_g2, Qclear_kb;
    Object Qwrite_g2_stats, Qfour_times_the_scale, Qone_quarter_the_scale;
    Object Qtwenty_percent_wider, Qtwenty_percent_narrower;
    Object Qtwenty_percent_bigger, Qtwenty_percent_smaller;
    Object Qmaximum_scale_to_fit, Qscale_to_fit, Qcenter_origin;
    Object Qshift_down_one_percent, Qshift_right_one_percent;
    Object Qshift_up_one_percent, Qshift_left_one_percent;
    Object Qshift_down_ten_percent, Qshift_right_ten_percent;
    Object Qshift_up_ten_percent, Qshift_left_ten_percent, Qcirculate_down;
    Object Qcirculate_up, Qnormalized_full_scale, Qfull_scale, Qrefresh;
    Object list_constant_100, Qshow_text, Qshow_value, Qtransfer_original;
    Object Qdelete_original, Qgo_to_original, Qchange_size;
    Object Qhide_attribute_display, Qdelete_name_of_attribute;
    Object Qadd_name_of_attribute, Qdelete_attribute, Qadd_another_attribute;
    Object Qshow_attribute_display, Qclone, Qtransfer, Qedit_icon;
    Object Qchoose_existing_class, Qadd_optional_subtable;
    Object Qshow_subtable_of_unsaved_attributes, Qchange_to, Qchange_to_yes;
    Object Qchange_to_no, Qdelete_subtable, Qsubtable, Qgo_to_item;
    Object Qhide_table, Qhide, Qdynamic_generic_rule_display;
    Object Qdescribe_chaining, Qdynamic_backward_chaining, Qsubtables;
    Object Qadd_subtable, Qshow_summary_of_text, list_constant_98;
    Object Qdynamic_rule_invocation_display, Qexecute_g2gl_process;
    Object Qclean_up_g2gl_compilation_postings_on_process;
    Object Qcompile_g2gl_process, Qgo_to_message_origin;
    Object Qtable_of_hidden_attributes, Qshow_unsaved_attributes, Qfont;
    Object Qalign_text, Qchange_min_size, Qclone_as_trend_chart;
    Object Qgo_to_referenced_item, Qhide_name, Qdelete_column, Qdelete_row;
    Object Qadd_column, Qadd_row, Qother_edits, Qedit_cell_format;
    Object Qedit_cell_expression, Qcreate_subworkspace;
    Object Qrestore_to_normal_size, Qrotate_reflect;
    Object Qadd_stub_for_local_handler, Qremove_temporary_breakpoint;
    Object Qset_temporary_breakpoint, Qcreate_instance, Qgo_to_subworkspace;
    Object Qglobal_keyboard_command_choice, Qmain_menu_choice;
    Object string_constant_157, string_constant_156;
    Object Qglobal_keyboard_command_restriction_clause;
    Object Qglobal_keyboard_command_restriction_clause_list;
    Object Qmain_menu_restriction_clause, Qmain_menu_restriction_clause_list;
    Object string_constant_155, string_constant_154;
    Object Qsimplify_associative_operation, string_constant_153;
    Object string_constant_152, string_constant_151;
    Object Qglobal_keyboard_command_mode_restriction;
    Object Qmain_menu_mode_restriction, Qg2_user_mode_for_login_qm;
    Object list_constant_97, Qno_item, Qg2_user_mode_for_login;
    Object Qcompile_g2_user_mode_for_login_qm_for_slot;
    Object Qcompile_g2_user_mode_for_login_for_slot, Qwrite_symbol_from_slot;
    Object Qg2_user_mode, string_constant_150, string_constant_149;
    Object string_constant_148, string_constant_147, string_constant_146;
    Object Qfilter_cons_memory_usage, Qoutstanding_filter_conses, Qutilities1;
    Object list_constant_95, Qfilter_cons_counter_vector, Qmake_thread_array;
    Object list_constant_94, Qavailable_filter_conses_tail_vector;
    Object Qavailable_filter_conses_vector;

    x_note_fn_call(180,295);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qavailable_filter_conses = STATIC_SYMBOL("AVAILABLE-FILTER-CONSES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_filter_conses,
	    Available_filter_conses);
    Qutilities1 = STATIC_SYMBOL("UTILITIES1",AB_package);
    record_system_variable(Qavailable_filter_conses,Qutilities1,Nil,Qnil,
	    Qt,Qnil,Qnil);
    Qavailable_filter_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-FILTER-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_filter_conses_tail,
	    Available_filter_conses_tail);
    record_system_variable(Qavailable_filter_conses_tail,Qutilities1,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_filter_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-FILTER-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_filter_conses_vector,
	    Available_filter_conses_vector);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_thread_array = STATIC_SYMBOL("MAKE-THREAD-ARRAY",AB_package);
    list_constant_94 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    Qnil);
    record_system_variable(Qavailable_filter_conses_vector,Qutilities1,
	    list_constant_94,Qnil,Qt,Qnil,Qnil);
    Qavailable_filter_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-FILTER-CONSES-TAIL-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_filter_conses_tail_vector,
	    Available_filter_conses_tail_vector);
    record_system_variable(Qavailable_filter_conses_tail_vector,
	    Qutilities1,list_constant_94,Qnil,Qt,Qnil,Qnil);
    Qfilter_cons_counter_vector = 
	    STATIC_SYMBOL("FILTER-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qfilter_cons_counter_vector,
	    Filter_cons_counter_vector);
    list_constant_95 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    FIX((SI_Long)0L));
    record_system_variable(Qfilter_cons_counter_vector,Qutilities1,
	    list_constant_95,Qnil,Qt,Qnil,Qnil);
    Qfilter_cons_counter = STATIC_SYMBOL("FILTER-CONS-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qfilter_cons_counter,Filter_cons_counter);
    record_system_variable(Qfilter_cons_counter,Qutilities1,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_filter_conses = STATIC_SYMBOL("OUTSTANDING-FILTER-CONSES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_filter_conses,
	    STATIC_FUNCTION(outstanding_filter_conses,NIL,FALSE,0,0));
    Qfilter_cons_memory_usage = STATIC_SYMBOL("FILTER-CONS-MEMORY-USAGE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qfilter_cons_memory_usage,
	    STATIC_FUNCTION(filter_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_146 = STATIC_STRING("1q83-U-y9k83-U+y09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_filter_conses);
    push_optimized_constant(Qfilter_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_146));
    Qfilter = STATIC_SYMBOL("FILTER",AB_package);
    Quser_mode_is_not_a_symbol = STATIC_SYMBOL("USER-MODE-IS-NOT-A-SYMBOL",
	    AB_package);
    Quser_mode_may_not_be_nil = STATIC_SYMBOL("USER-MODE-MAY-NOT-BE-NIL",
	    AB_package);
    Q = STATIC_SYMBOL("",AB_package);
    Quser_mode_may_not_be_an_empty_string = 
	    STATIC_SYMBOL("USER-MODE-MAY-NOT-BE-AN-EMPTY-STRING",AB_package);
    Qproprietary = STATIC_SYMBOL("PROPRIETARY",AB_package);
    Qcannot_enter_proprietary_mode = 
	    STATIC_SYMBOL("CANNOT-ENTER-PROPRIETARY-MODE",AB_package);
    string_constant_147 = STATIC_STRING("1l1m836uy831=y");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_147));
    string_constant_148 = STATIC_STRING("1m1m831=y83-7Ty1m831=y1m9k833ey");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_148));
    string_constant_149 = STATIC_STRING("1l1m83-7Ty83-2y");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_149));
    string_constant_150 = STATIC_STRING("1m1m83CBy831=y1m83CBy1m9k83Zy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_150));
    Qg2_user_mode = STATIC_SYMBOL("G2-USER-MODE",AB_package);
    Qwrite_symbol_from_slot = STATIC_SYMBOL("WRITE-SYMBOL-FROM-SLOT",
	    AB_package);
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qg2_user_mode,
	    SYMBOL_FUNCTION(Qwrite_symbol_from_slot),Qslot_value_writer);
    Qg2_user_mode_for_login = STATIC_SYMBOL("G2-USER-MODE-FOR-LOGIN",
	    AB_package);
    mutate_global_property(Qg2_user_mode_for_login,
	    SYMBOL_FUNCTION(Qwrite_symbol_from_slot),Qslot_value_writer);
    Qg2_user_mode_for_login_qm = STATIC_SYMBOL("G2-USER-MODE-FOR-LOGIN\?",
	    AB_package);
    mutate_global_property(Qg2_user_mode_for_login_qm,
	    SYMBOL_FUNCTION(Qwrite_symbol_from_slot),Qslot_value_writer);
    Qcompile_g2_user_mode_for_login_for_slot = 
	    STATIC_SYMBOL("COMPILE-G2-USER-MODE-FOR-LOGIN-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_g2_user_mode_for_login_for_slot,
	    STATIC_FUNCTION(compile_g2_user_mode_for_login_for_slot,NIL,
	    TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qg2_user_mode_for_login,
	    SYMBOL_FUNCTION(Qcompile_g2_user_mode_for_login_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qg2_user_mode_for_login,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qg2_login_user_name_qm = STATIC_SYMBOL("G2-LOGIN-USER-NAME\?",AB_package);
    Qui_client_session = STATIC_SYMBOL("UI-CLIENT-SESSION",AB_package);
    Qui_client_session_user_name = 
	    STATIC_SYMBOL("UI-CLIENT-SESSION-USER-NAME",AB_package);
    Qg2_user_name = STATIC_SYMBOL("G2-USER-NAME",AB_package);
    string_constant = 
	    STATIC_STRING("Attempting to change the user-mode on an item for which that is not defined: ~NF");
    list_constant_96 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_96,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)89L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)17L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)18L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)19L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)20L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)21L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)24L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)25L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)26L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)27L,(SI_Long)89L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)28L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)29L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)30L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)31L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)32L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)33L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)38L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)39L,(SI_Long)57344L);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Qcompile_g2_user_mode_for_login_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-G2-USER-MODE-FOR-LOGIN\?-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_g2_user_mode_for_login_qm_for_slot,
	    STATIC_FUNCTION(compile_g2_user_mode_for_login_qm_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qg2_user_mode_for_login_qm,
	    SYMBOL_FUNCTION(Qcompile_g2_user_mode_for_login_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qg2_user_mode_for_login_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    set_property_value_function(get_symbol_properties_function(Qg2_user_mode_for_login),
	    Qtype_specification_simple_expansion,Qsymbol);
    define_type_specification_explicit_complex_type(Qg2_user_mode_for_login,
	    Qsymbol);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qnamed,Qg2_user_mode_for_login);
    g2_user_mode_for_login_evaluation_setter_1 = 
	    STATIC_FUNCTION(g2_user_mode_for_login_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qg2_user_mode_for_login,
	    g2_user_mode_for_login_evaluation_setter_1);
    g2_user_mode_for_login_evaluation_getter_1 = 
	    STATIC_FUNCTION(g2_user_mode_for_login_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qg2_user_mode_for_login,
	    g2_user_mode_for_login_evaluation_getter_1);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_82 = STATIC_CONS(Qno_item,Qnil);
    list_constant_97 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_82,
	    Qsymbol);
    set_property_value_function(get_symbol_properties_function(Qg2_user_mode_for_login_qm),
	    Qtype_specification_simple_expansion,list_constant_97);
    define_type_specification_explicit_complex_type(Qg2_user_mode_for_login_qm,
	    list_constant_97);
    g2_user_mode_for_login_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(g2_user_mode_for_login_qm_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qg2_user_mode_for_login_qm,
	    g2_user_mode_for_login_qm_evaluation_getter_1);
    Qmain_menu_restrictions = STATIC_SYMBOL("MAIN-MENU-RESTRICTIONS",
	    AB_package);
    Qmain_menu_mode_restriction = 
	    STATIC_SYMBOL("MAIN-MENU-MODE-RESTRICTION",AB_package);
    Qsc = STATIC_SYMBOL(";",AB_package);
    add_grammar_rules_for_list(5,Qmain_menu_restrictions,
	    Qmain_menu_mode_restriction,Qsc,Qnil,Qnone);
    Qglobal_keyboard_command_restrictions = 
	    STATIC_SYMBOL("GLOBAL-KEYBOARD-COMMAND-RESTRICTIONS",AB_package);
    Qglobal_keyboard_command_mode_restriction = 
	    STATIC_SYMBOL("GLOBAL-KEYBOARD-COMMAND-MODE-RESTRICTION",
	    AB_package);
    add_grammar_rules_for_list(5,Qglobal_keyboard_command_restrictions,
	    Qglobal_keyboard_command_mode_restriction,Qsc,Qnil,Qnone);
    Qfix_mode_restriction = STATIC_SYMBOL("FIX-MODE-RESTRICTION",AB_package);
    string_constant_151 = 
	    STATIC_STRING("1l1o83-dSy1p83Fuy1m9k83*Xy839Sy1m9k83-Py83-dUy2mlnp9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qfix_mode_restriction);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_151));
    string_constant_152 = STATIC_STRING("1m1m83Fuy1m9k837ey1m83Fuy1m9k83ALy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_152));
    Qcons_car_cddr = STATIC_SYMBOL("CONS-CAR-CDDR",AB_package);
    string_constant_153 = 
	    STATIC_STRING("1n1n839Sy1m836uy1m9k83-fLy1ll1n839Sy1o836uy1m9k83=Uy836uy1m9k83-fLy1mln1o839Sy1o836uy1m9k83vy83-6vy1m9k83-fLy2lln9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qcons_car_cddr);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_153));
    Qsimplify_associative_operation = 
	    STATIC_SYMBOL("SIMPLIFY-ASSOCIATIVE-OPERATION",AB_package);
    string_constant_154 = 
	    STATIC_STRING("1m1o83-6vy1n836uy1m9k83vy83-6vy1nmln1l9l1n83-6vy1o836uy1m9k83vy1m9k83=Uy836uy1nmlo");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_154));
    string_constant_155 = 
	    STATIC_STRING("1l1o83-Way1p83Fuy1m9k83*Xy839Sy1m9k83-Py83-Wcy2mlnp9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qfix_mode_restriction);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_155));
    Qmain_menu_restriction_clause_list = 
	    STATIC_SYMBOL("MAIN-MENU-RESTRICTION-CLAUSE-LIST",AB_package);
    Qmain_menu_restriction_clause = 
	    STATIC_SYMBOL("MAIN-MENU-RESTRICTION-CLAUSE",AB_package);
    add_grammar_rules_for_list(5,Qmain_menu_restriction_clause_list,
	    Qmain_menu_restriction_clause,Qsc,Qnil,Qnil);
    Qglobal_keyboard_command_restriction_clause_list = 
	    STATIC_SYMBOL("GLOBAL-KEYBOARD-COMMAND-RESTRICTION-CLAUSE-LIST",
	    AB_package);
    Qglobal_keyboard_command_restriction_clause = 
	    STATIC_SYMBOL("GLOBAL-KEYBOARD-COMMAND-RESTRICTION-CLAUSE",
	    AB_package);
    add_grammar_rules_for_list(5,
	    Qglobal_keyboard_command_restriction_clause_list,
	    Qglobal_keyboard_command_restriction_clause,Qsc,Qnil,Qnil);
    Qmenu = STATIC_SYMBOL("MENU",AB_package);
    Qfix_tailing_associative_list = 
	    STATIC_SYMBOL("FIX-TAILING-ASSOCIATIVE-LIST",AB_package);
    string_constant_156 = 
	    STATIC_STRING("1l1o83-dTy1p1m9k83-dQy1m9k9l1m9k83s*y83mLy83-dRy2m839Oyop1m9mm");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qmenu);
    push_optimized_constant(Qfix_tailing_associative_list);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_156));
    string_constant_157 = 
	    STATIC_STRING("1l1o83-Wby1p1m9k83-WXy1m9k83-c+y1m9k83-NCy83mLy83-WZy2m83-WYyop1m9lm");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qfix_tailing_associative_list);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_157));
    Qmain_menu_choices = STATIC_SYMBOL("MAIN-MENU-CHOICES",AB_package);
    Qmain_menu_choice = STATIC_SYMBOL("MAIN-MENU-CHOICE",AB_package);
    Qcm = STATIC_SYMBOL(",",AB_package);
    add_grammar_rules_for_list(5,Qmain_menu_choices,Qmain_menu_choice,Qcm,
	    Qnil,Qnil);
    Qglobal_keyboard_command_choices = 
	    STATIC_SYMBOL("GLOBAL-KEYBOARD-COMMAND-CHOICES",AB_package);
    Qglobal_keyboard_command_choice = 
	    STATIC_SYMBOL("GLOBAL-KEYBOARD-COMMAND-CHOICE",AB_package);
    add_grammar_rules_for_list(5,Qglobal_keyboard_command_choices,
	    Qglobal_keyboard_command_choice,Qcm,Qnil,Qnil);
    Qlift_to_top = STATIC_SYMBOL("LIFT-TO-TOP",AB_package);
    Qdrop_to_bottom = STATIC_SYMBOL("DROP-TO-BOTTOM",AB_package);
    Qgo_to_referenced_item = STATIC_SYMBOL("GO-TO-REFERENCED-ITEM",AB_package);
    Qclone_as_trend_chart = STATIC_SYMBOL("CLONE-AS-TREND-CHART",AB_package);
    Qtable = STATIC_SYMBOL("TABLE",AB_package);
    Qedit = STATIC_SYMBOL("EDIT",AB_package);
    Qtransfer = STATIC_SYMBOL("TRANSFER",AB_package);
    Qmove = STATIC_SYMBOL("MOVE",AB_package);
    Qclone = STATIC_SYMBOL("CLONE",AB_package);
    Qchange_min_size = STATIC_SYMBOL("CHANGE-MIN-SIZE",AB_package);
    Qalign_text = STATIC_SYMBOL("ALIGN-TEXT",AB_package);
    Qfont = STATIC_SYMBOL("FONT",AB_package);
    Qshow_unsaved_attributes = STATIC_SYMBOL("SHOW-UNSAVED-ATTRIBUTES",
	    AB_package);
    Qtable_of_hidden_attributes = 
	    STATIC_SYMBOL("TABLE-OF-HIDDEN-ATTRIBUTES",AB_package);
    Qcolor = STATIC_SYMBOL("COLOR",AB_package);
    Qgo_to_message_origin = STATIC_SYMBOL("GO-TO-MESSAGE-ORIGIN",AB_package);
    Qenable = STATIC_SYMBOL("ENABLE",AB_package);
    Qdisable = STATIC_SYMBOL("DISABLE",AB_package);
    Qab_describe = STATIC_SYMBOL("DESCRIBE",AB_package);
    Qview_change_log = STATIC_SYMBOL("VIEW-CHANGE-LOG",AB_package);
    Qcompile_g2gl_process = STATIC_SYMBOL("COMPILE-G2GL-PROCESS",AB_package);
    Qclean_up_g2gl_compilation_postings_on_process = 
	    STATIC_SYMBOL("CLEAN-UP-G2GL-COMPILATION-POSTINGS-ON-PROCESS",
	    AB_package);
    Qexecute_g2gl_process = STATIC_SYMBOL("EXECUTE-G2GL-PROCESS",AB_package);
    Qdynamic_rule_invocation_display = 
	    STATIC_SYMBOL("DYNAMIC-RULE-INVOCATION-DISPLAY",AB_package);
    Qdescribe_configuration = STATIC_SYMBOL("DESCRIBE-CONFIGURATION",
	    AB_package);
    Qmark_to_strip_text = STATIC_SYMBOL("MARK-TO-STRIP-TEXT",AB_package);
    Qmark_to_strip_text_star = STATIC_SYMBOL("MARK-TO-STRIP-TEXT-*",
	    AB_package);
    Qremove_strip_text_mark = STATIC_SYMBOL("REMOVE-STRIP-TEXT-MARK",
	    AB_package);
    Qremove_strip_text_mark_star = 
	    STATIC_SYMBOL("REMOVE-STRIP-TEXT-MARK-*",AB_package);
    Qmark_not_to_strip_text_star = 
	    STATIC_SYMBOL("MARK-NOT-TO-STRIP-TEXT-*",AB_package);
    Qmark_not_to_strip_text = STATIC_SYMBOL("MARK-NOT-TO-STRIP-TEXT",
	    AB_package);
    Qremove_do_not_strip_text_mark_star = 
	    STATIC_SYMBOL("REMOVE-DO-NOT-STRIP-TEXT-MARK-*",AB_package);
    Qremove_do_not_strip_text_mark = 
	    STATIC_SYMBOL("REMOVE-DO-NOT-STRIP-TEXT-MARK",AB_package);
    Qgo_to_subworkspace = STATIC_SYMBOL("GO-TO-SUBWORKSPACE",AB_package);
    Qcreate_instance = STATIC_SYMBOL("CREATE-INSTANCE",AB_package);
    Qset_temporary_breakpoint = STATIC_SYMBOL("SET-TEMPORARY-BREAKPOINT",
	    AB_package);
    Qremove_temporary_breakpoint = 
	    STATIC_SYMBOL("REMOVE-TEMPORARY-BREAKPOINT",AB_package);
    Qadd_stub_for_local_handler = 
	    STATIC_SYMBOL("ADD-STUB-FOR-LOCAL-HANDLER",AB_package);
    Qedit_icon = STATIC_SYMBOL("EDIT-ICON",AB_package);
    Qtable_of_values = STATIC_SYMBOL("TABLE-OF-VALUES",AB_package);
    Qname = STATIC_SYMBOL("NAME",AB_package);
    Qrotate_reflect = STATIC_SYMBOL("ROTATE-REFLECT",AB_package);
    Qchange_size = STATIC_SYMBOL("CHANGE-SIZE",AB_package);
    Qrestore_to_normal_size = STATIC_SYMBOL("RESTORE-TO-NORMAL-SIZE",
	    AB_package);
    Qdynamic_backward_chaining = STATIC_SYMBOL("DYNAMIC-BACKWARD-CHAINING",
	    AB_package);
    Qdescribe_chaining = STATIC_SYMBOL("DESCRIBE-CHAINING",AB_package);
    Qdynamic_generic_rule_display = 
	    STATIC_SYMBOL("DYNAMIC-GENERIC-RULE-DISPLAY",AB_package);
    Qcreate_subworkspace = STATIC_SYMBOL("CREATE-SUBWORKSPACE",AB_package);
    Qedit_cell_expression = STATIC_SYMBOL("EDIT-CELL-EXPRESSION",AB_package);
    Qedit_cell_format = STATIC_SYMBOL("EDIT-CELL-FORMAT",AB_package);
    Qother_edits = STATIC_SYMBOL("OTHER-EDITS",AB_package);
    Qadd_row = STATIC_SYMBOL("ADD-ROW",AB_package);
    Qadd_column = STATIC_SYMBOL("ADD-COLUMN",AB_package);
    Qdelete_row = STATIC_SYMBOL("DELETE-ROW",AB_package);
    Qdelete_column = STATIC_SYMBOL("DELETE-COLUMN",AB_package);
    Qhide_name = STATIC_SYMBOL("HIDE-NAME",AB_package);
    list_constant_98 = STATIC_LIST((SI_Long)26L,Qmark_not_to_strip_text,
	    Qremove_do_not_strip_text_mark_star,
	    Qremove_do_not_strip_text_mark,Qgo_to_subworkspace,
	    Qcreate_instance,Qset_temporary_breakpoint,
	    Qremove_temporary_breakpoint,Qadd_stub_for_local_handler,
	    Qedit_icon,Qtable_of_values,Qname,Qrotate_reflect,Qchange_size,
	    Qrestore_to_normal_size,Qdynamic_backward_chaining,
	    Qdescribe_chaining,Qdynamic_generic_rule_display,
	    Qcreate_subworkspace,Qedit_cell_expression,Qedit_cell_format,
	    Qother_edits,Qadd_row,Qadd_column,Qdelete_row,Qdelete_column,
	    Qhide_name);
    list_constant_99 = STATIC_LIST_STAR((SI_Long)32L,Qlift_to_top,
	    Qdrop_to_bottom,Qgo_to_referenced_item,Qclone_as_trend_chart,
	    Qtable,Qedit,Qtransfer,Qmove,Qclone,Qchange_min_size,
	    Qalign_text,Qfont,Qshow_unsaved_attributes,
	    Qtable_of_hidden_attributes,Qcolor,Qdelete,
	    Qgo_to_message_origin,Qenable,Qdisable,Qab_describe,
	    Qview_change_log,Qcompile_g2gl_process,
	    Qclean_up_g2gl_compilation_postings_on_process,
	    Qexecute_g2gl_process,Qdynamic_rule_invocation_display,
	    Qdescribe_configuration,Qmark_to_strip_text,
	    Qmark_to_strip_text_star,Qremove_strip_text_mark,
	    Qremove_strip_text_mark_star,Qmark_not_to_strip_text_star,
	    list_constant_98);
    Item_menu_choices = list_constant_99;
    Qsubtable = STATIC_SYMBOL("SUBTABLE",AB_package);
    Qdelete_subtable = STATIC_SYMBOL("DELETE-SUBTABLE",AB_package);
    Qchange_to_no = STATIC_SYMBOL("CHANGE-TO-NO",AB_package);
    Qchange_to_yes = STATIC_SYMBOL("CHANGE-TO-YES",AB_package);
    Qchange_to = STATIC_SYMBOL("CHANGE-TO",AB_package);
    Qshow_subtable_of_unsaved_attributes = 
	    STATIC_SYMBOL("SHOW-SUBTABLE-OF-UNSAVED-ATTRIBUTES",AB_package);
    Qadd_optional_subtable = STATIC_SYMBOL("ADD-OPTIONAL-SUBTABLE",AB_package);
    Qchoose_existing_class = STATIC_SYMBOL("CHOOSE-EXISTING-CLASS",AB_package);
    Qshow_attribute_display = STATIC_SYMBOL("SHOW-ATTRIBUTE-DISPLAY",
	    AB_package);
    Qadd_another_attribute = STATIC_SYMBOL("ADD-ANOTHER-ATTRIBUTE",AB_package);
    Qdelete_attribute = STATIC_SYMBOL("DELETE-ATTRIBUTE",AB_package);
    Qadd_name_of_attribute = STATIC_SYMBOL("ADD-NAME-OF-ATTRIBUTE",AB_package);
    Qdelete_name_of_attribute = STATIC_SYMBOL("DELETE-NAME-OF-ATTRIBUTE",
	    AB_package);
    Qhide_attribute_display = STATIC_SYMBOL("HIDE-ATTRIBUTE-DISPLAY",
	    AB_package);
    Qgo_to_original = STATIC_SYMBOL("GO-TO-ORIGINAL",AB_package);
    Qdelete_original = STATIC_SYMBOL("DELETE-ORIGINAL",AB_package);
    Qtransfer_original = STATIC_SYMBOL("TRANSFER-ORIGINAL",AB_package);
    Qshow_value = STATIC_SYMBOL("SHOW-VALUE",AB_package);
    Qshow_text = STATIC_SYMBOL("SHOW-TEXT",AB_package);
    Qshow_summary_of_text = STATIC_SYMBOL("SHOW-SUMMARY-OF-TEXT",AB_package);
    Qadd_subtable = STATIC_SYMBOL("ADD-SUBTABLE",AB_package);
    Qsubtables = STATIC_SYMBOL("SUBTABLES",AB_package);
    Qhide = STATIC_SYMBOL("HIDE",AB_package);
    Qhide_table = STATIC_SYMBOL("HIDE-TABLE",AB_package);
    Qgo_to_item = STATIC_SYMBOL("GO-TO-ITEM",AB_package);
    list_constant_100 = STATIC_LIST((SI_Long)18L,Qshow_summary_of_text,
	    Qadd_subtable,Qsubtables,Qdynamic_backward_chaining,
	    Qdescribe_chaining,Qdynamic_generic_rule_display,Qhide,Qdelete,
	    Qhide_table,Qmark_to_strip_text,Qmark_to_strip_text_star,
	    Qremove_strip_text_mark,Qremove_strip_text_mark_star,
	    Qmark_not_to_strip_text_star,Qmark_not_to_strip_text,
	    Qremove_do_not_strip_text_mark_star,
	    Qremove_do_not_strip_text_mark,Qgo_to_item);
    list_constant_101 = STATIC_LIST_STAR((SI_Long)32L,Qsubtable,
	    Qdelete_subtable,Qchange_to_no,Qchange_to_yes,Qchange_to,
	    Qshow_subtable_of_unsaved_attributes,Qadd_optional_subtable,
	    Qtable,Qchoose_existing_class,Qedit,Qedit_icon,Qtransfer,Qmove,
	    Qclone,Qshow_attribute_display,Qadd_another_attribute,
	    Qdelete_attribute,Qadd_name_of_attribute,
	    Qdelete_name_of_attribute,Qhide_attribute_display,Qchange_size,
	    Qenable,Qdisable,Qgo_to_original,Qdelete_original,
	    Qtransfer_original,Qdescribe_configuration,Qab_describe,
	    Qview_change_log,Qshow_value,Qshow_text,list_constant_100);
    if (Table_menu_choices == UNBOUND)
	Table_menu_choices = list_constant_101;
    SET_SYMBOL_VALUE_LOCATION(Qglobal_keyboard_command_choices,
	    Global_keyboard_command_choices);
    Qpause = STATIC_SYMBOL("PAUSE",AB_package);
    Qrefresh = STATIC_SYMBOL("REFRESH",AB_package);
    Qhelp = STATIC_SYMBOL("HELP",AB_package);
    Qfull_scale = STATIC_SYMBOL("FULL-SCALE",AB_package);
    Qnormalized_full_scale = STATIC_SYMBOL("NORMALIZED-FULL-SCALE",AB_package);
    Qcirculate_up = STATIC_SYMBOL("CIRCULATE-UP",AB_package);
    SET_SYMBOL_FUNCTION(Qcirculate_up,STATIC_FUNCTION(circulate_up,NIL,
	    FALSE,1,1));
    Qcirculate_down = STATIC_SYMBOL("CIRCULATE-DOWN",AB_package);
    SET_SYMBOL_FUNCTION(Qcirculate_down,STATIC_FUNCTION(circulate_down,NIL,
	    FALSE,1,1));
    Qshift_left_ten_percent = STATIC_SYMBOL("SHIFT-LEFT-TEN-PERCENT",
	    AB_package);
    Qshift_up_ten_percent = STATIC_SYMBOL("SHIFT-UP-TEN-PERCENT",AB_package);
    Qshift_right_ten_percent = STATIC_SYMBOL("SHIFT-RIGHT-TEN-PERCENT",
	    AB_package);
    Qshift_down_ten_percent = STATIC_SYMBOL("SHIFT-DOWN-TEN-PERCENT",
	    AB_package);
    Qshift_left_one_percent = STATIC_SYMBOL("SHIFT-LEFT-ONE-PERCENT",
	    AB_package);
    Qshift_up_one_percent = STATIC_SYMBOL("SHIFT-UP-ONE-PERCENT",AB_package);
    Qshift_right_one_percent = STATIC_SYMBOL("SHIFT-RIGHT-ONE-PERCENT",
	    AB_package);
    Qshift_down_one_percent = STATIC_SYMBOL("SHIFT-DOWN-ONE-PERCENT",
	    AB_package);
    Qcenter_origin = STATIC_SYMBOL("CENTER-ORIGIN",AB_package);
    Qscale_to_fit = STATIC_SYMBOL("SCALE-TO-FIT",AB_package);
    Qmaximum_scale_to_fit = STATIC_SYMBOL("MAXIMUM-SCALE-TO-FIT",AB_package);
    Qtwenty_percent_smaller = STATIC_SYMBOL("TWENTY-PERCENT-SMALLER",
	    AB_package);
    Qtwenty_percent_bigger = STATIC_SYMBOL("TWENTY-PERCENT-BIGGER",AB_package);
    Qtwenty_percent_narrower = STATIC_SYMBOL("TWENTY-PERCENT-NARROWER",
	    AB_package);
    Qtwenty_percent_wider = STATIC_SYMBOL("TWENTY-PERCENT-WIDER",AB_package);
    Qone_quarter_the_scale = STATIC_SYMBOL("ONE-QUARTER-THE-SCALE",AB_package);
    Qfour_times_the_scale = STATIC_SYMBOL("FOUR-TIMES-THE-SCALE",AB_package);
    Qtoggle_visible_grid = STATIC_SYMBOL("TOGGLE-VISIBLE-GRID",AB_package);
    SET_SYMBOL_FUNCTION(Qtoggle_visible_grid,
	    STATIC_FUNCTION(toggle_visible_grid,NIL,FALSE,1,1));
    list_constant_102 = STATIC_LIST((SI_Long)27L,Qpause,Qrefresh,Qhelp,
	    Qfull_scale,Qnormalized_full_scale,Qlift_to_top,
	    Qdrop_to_bottom,Qcirculate_up,Qcirculate_down,
	    Qshift_left_ten_percent,Qshift_up_ten_percent,
	    Qshift_right_ten_percent,Qshift_down_ten_percent,
	    Qshift_left_one_percent,Qshift_up_one_percent,
	    Qshift_right_one_percent,Qshift_down_one_percent,
	    Qcenter_origin,Qscale_to_fit,Qmaximum_scale_to_fit,
	    Qtwenty_percent_smaller,Qtwenty_percent_bigger,
	    Qtwenty_percent_narrower,Qtwenty_percent_wider,
	    Qone_quarter_the_scale,Qfour_times_the_scale,Qtoggle_visible_grid);
    if (Global_keyboard_command_choices == UNBOUND)
	Global_keyboard_command_choices = list_constant_102;
    SET_SYMBOL_VALUE_LOCATION(Qmain_menu_choices,Main_menu_choices);
    Qstart = STATIC_SYMBOL("START",AB_package);
    Qresume = STATIC_SYMBOL("RESUME",AB_package);
    Qreset = STATIC_SYMBOL("RESET",AB_package);
    Qab_restart = STATIC_SYMBOL("RESTART",AB_package);
    Qnew_workspace = STATIC_SYMBOL("NEW-WORKSPACE",AB_package);
    Qtable_of_attributes_pane = STATIC_SYMBOL("TABLE-OF-ATTRIBUTES-PANE",
	    AB_package);
    Qget_workspace = STATIC_SYMBOL("GET-WORKSPACE",AB_package);
    Qload_merge_save = STATIC_SYMBOL("LOAD-MERGE-SAVE",AB_package);
    Qload_kb = STATIC_SYMBOL("LOAD-KB",AB_package);
    Qmerge_kb = STATIC_SYMBOL("MERGE-KB",AB_package);
    Qsave_kb = STATIC_SYMBOL("SAVE-KB",AB_package);
    Qsystem_tables = STATIC_SYMBOL("SYSTEM-TABLES",AB_package);
    Qrun_options = STATIC_SYMBOL("RUN-OPTIONS",AB_package);
    Qchange_mode = STATIC_SYMBOL("CHANGE-MODE",AB_package);
    SET_SYMBOL_FUNCTION(Qchange_mode,STATIC_FUNCTION(change_mode,NIL,FALSE,
	    0,0));
    Qmiscellany = STATIC_SYMBOL("MISCELLANY",AB_package);
    Qlong_menus = STATIC_SYMBOL("LONG-MENUS",AB_package);
    Qshort_menus = STATIC_SYMBOL("SHORT-MENUS",AB_package);
    Qcreate_new_module = STATIC_SYMBOL("CREATE-NEW-MODULE",AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_new_module,
	    STATIC_FUNCTION(create_new_module,NIL,FALSE,1,1));
    Qdelete_module = STATIC_SYMBOL("DELETE-MODULE",AB_package);
    Qnew_title_block = STATIC_SYMBOL("NEW-TITLE-BLOCK",AB_package);
    Qneatly_stack_windows = STATIC_SYMBOL("NEATLY-STACK-WINDOWS",AB_package);
    Qnetwork_info = STATIC_SYMBOL("NETWORK-INFO",AB_package);
    Qclose_telewindows_connection = 
	    STATIC_SYMBOL("CLOSE-TELEWINDOWS-CONNECTION",AB_package);
    SET_SYMBOL_FUNCTION(Qclose_telewindows_connection,
	    STATIC_FUNCTION(close_telewindows_connection,NIL,FALSE,1,1));
    Qlog_out = STATIC_SYMBOL("LOG-OUT",AB_package);
    Qchange_password = STATIC_SYMBOL("CHANGE-PASSWORD",AB_package);
    Qreinstall_authorized_users = 
	    STATIC_SYMBOL("REINSTALL-AUTHORIZED-USERS",AB_package);
    SET_SYMBOL_FUNCTION(Qreinstall_authorized_users,
	    STATIC_FUNCTION(reinstall_authorized_users,NIL,FALSE,0,0));
    Qconnect_to_foreign_image = STATIC_SYMBOL("CONNECT-TO-FOREIGN-IMAGE",
	    AB_package);
    Qdisconnect_from_foreign_image = 
	    STATIC_SYMBOL("DISCONNECT-FROM-FOREIGN-IMAGE",AB_package);
    Qload_attribute_file = STATIC_SYMBOL("LOAD-ATTRIBUTE-FILE",AB_package);
    Qwrite_g2_stats = STATIC_SYMBOL("WRITE-G2-STATS",AB_package);
    Qclear_kb = STATIC_SYMBOL("CLEAR-KB",AB_package);
    Qshut_down_g2 = STATIC_SYMBOL("SHUT-DOWN-G2",AB_package);
    Qturn_on_all_explanation_caching = 
	    STATIC_SYMBOL("TURN-ON-ALL-EXPLANATION-CACHING",AB_package);
    Qturn_off_all_explanation_caching = 
	    STATIC_SYMBOL("TURN-OFF-ALL-EXPLANATION-CACHING",AB_package);
    Qenter_package_preparation_mode = 
	    STATIC_SYMBOL("ENTER-PACKAGE-PREPARATION-MODE",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_package_preparation_mode,
	    STATIC_FUNCTION(enter_package_preparation_mode,NIL,FALSE,0,0));
    Qleave_package_preparation_mode = 
	    STATIC_SYMBOL("LEAVE-PACKAGE-PREPARATION-MODE",AB_package);
    SET_SYMBOL_FUNCTION(Qleave_package_preparation_mode,
	    STATIC_FUNCTION(leave_package_preparation_mode,NIL,FALSE,0,0));
    Qstrip_texts_now = STATIC_SYMBOL("STRIP-TEXTS-NOW",AB_package);
    Qmake_workspaces_proprietary_now = 
	    STATIC_SYMBOL("MAKE-WORKSPACES-PROPRIETARY-NOW",AB_package);
    Qflush_change_log_for_entire_kb = 
	    STATIC_SYMBOL("FLUSH-CHANGE-LOG-FOR-ENTIRE-KB",AB_package);
    Qenter_simulate_proprietary_mode = 
	    STATIC_SYMBOL("ENTER-SIMULATE-PROPRIETARY-MODE",AB_package);
    Qleave_simulate_proprietary_mode = 
	    STATIC_SYMBOL("LEAVE-SIMULATE-PROPRIETARY-MODE",AB_package);
    Qdo_not_highlight_invoked_rules = 
	    STATIC_SYMBOL("DO-NOT-HIGHLIGHT-INVOKED-RULES",AB_package);
    Qhighlight_invoked_rules = STATIC_SYMBOL("HIGHLIGHT-INVOKED-RULES",
	    AB_package);
    Qenable_all_items = STATIC_SYMBOL("ENABLE-ALL-ITEMS",AB_package);
    Qremove_tracing_and_breakpoints = 
	    STATIC_SYMBOL("REMOVE-TRACING-AND-BREAKPOINTS",AB_package);
    SET_SYMBOL_FUNCTION(Qremove_tracing_and_breakpoints,
	    STATIC_FUNCTION(remove_tracing_and_breakpoints,NIL,FALSE,0,0));
    Qlaunch_online_help = STATIC_SYMBOL("LAUNCH-ONLINE-HELP",AB_package);
    Qprint_window = STATIC_SYMBOL("PRINT-WINDOW",AB_package);
    list_constant_103 = STATIC_LIST((SI_Long)18L,Qwrite_g2_stats,Qclear_kb,
	    Qshut_down_g2,Qturn_on_all_explanation_caching,
	    Qturn_off_all_explanation_caching,
	    Qenter_package_preparation_mode,
	    Qleave_package_preparation_mode,Qstrip_texts_now,
	    Qmake_workspaces_proprietary_now,
	    Qflush_change_log_for_entire_kb,
	    Qenter_simulate_proprietary_mode,
	    Qleave_simulate_proprietary_mode,
	    Qdo_not_highlight_invoked_rules,Qhighlight_invoked_rules,
	    Qenable_all_items,Qremove_tracing_and_breakpoints,
	    Qlaunch_online_help,Qprint_window);
    list_constant_104 = STATIC_LIST_STAR((SI_Long)32L,Qstart,Qpause,
	    Qresume,Qreset,Qab_restart,Qnew_workspace,
	    Qtable_of_attributes_pane,Qget_workspace,Qinspect,
	    Qload_merge_save,Qload_kb,Qmerge_kb,Qsave_kb,Qsystem_tables,
	    Qrun_options,Qchange_mode,Qmiscellany,Qlong_menus,Qshort_menus,
	    Qcreate_new_module,Qdelete_module,Qnew_title_block,
	    Qneatly_stack_windows,Qnetwork_info,
	    Qclose_telewindows_connection,Qlog_out,Qchange_password,
	    Qreinstall_authorized_users,Qconnect_to_foreign_image,
	    Qdisconnect_from_foreign_image,Qload_attribute_file,
	    list_constant_103);
    if (Main_menu_choices == UNBOUND)
	Main_menu_choices = list_constant_104;
    Qnew_object = STATIC_SYMBOL("NEW-OBJECT",AB_package);
    Qnew_rule = STATIC_SYMBOL("NEW-RULE",AB_package);
    Qnew_display = STATIC_SYMBOL("NEW-DISPLAY",AB_package);
    Qnew_definition = STATIC_SYMBOL("NEW-DEFINITION",AB_package);
    Qnew_free_text = STATIC_SYMBOL("NEW-FREE-TEXT",AB_package);
    Qnew_button = STATIC_SYMBOL("NEW-BUTTON",AB_package);
    Qclone_workspace = STATIC_SYMBOL("CLONE-WORKSPACE",AB_package);
    Qhide_workspace = STATIC_SYMBOL("HIDE-WORKSPACE",AB_package);
    Qgo_to_superior = STATIC_SYMBOL("GO-TO-SUPERIOR",AB_package);
    Qshrink_wrap = STATIC_SYMBOL("SHRINK-WRAP",AB_package);
    Qdelete_workspace = STATIC_SYMBOL("DELETE-WORKSPACE",AB_package);
    Qmain_menu = STATIC_SYMBOL("MAIN-MENU",AB_package);
    Qoperate_on_area = STATIC_SYMBOL("OPERATE-ON-AREA",AB_package);
    Qcompile_g2gl_process_workspace = 
	    STATIC_SYMBOL("COMPILE-G2GL-PROCESS-WORKSPACE",AB_package);
    Qclean_up_g2gl_compilation_postings_on_body = 
	    STATIC_SYMBOL("CLEAN-UP-G2GL-COMPILATION-POSTINGS-ON-BODY",
	    AB_package);
    Qexecute_g2gl_process_workspace = 
	    STATIC_SYMBOL("EXECUTE-G2GL-PROCESS-WORKSPACE",AB_package);
    Qredo_layout_of_g2gl_body = STATIC_SYMBOL("REDO-LAYOUT-OF-G2GL-BODY",
	    AB_package);
    Qsingle_step = STATIC_SYMBOL("SINGLE-STEP",AB_package);
    Qdo_not_single_step = STATIC_SYMBOL("DO-NOT-SINGLE-STEP",AB_package);
    Qclose_and_continue = STATIC_SYMBOL("CLOSE-AND-CONTINUE",AB_package);
    Qbreak_on_execution_faults = STATIC_SYMBOL("BREAK-ON-EXECUTION-FAULTS",
	    AB_package);
    Qdo_not_break_on_execution_faults = 
	    STATIC_SYMBOL("DO-NOT-BREAK-ON-EXECUTION-FAULTS",AB_package);
    Qremove_all_temporary_breakpoints = 
	    STATIC_SYMBOL("REMOVE-ALL-TEMPORARY-BREAKPOINTS",AB_package);
    Qbring_up_source = STATIC_SYMBOL("BRING-UP-SOURCE",AB_package);
    Qpause_process_instance = STATIC_SYMBOL("PAUSE-PROCESS-INSTANCE",
	    AB_package);
    Qresume_process_instance = STATIC_SYMBOL("RESUME-PROCESS-INSTANCE",
	    AB_package);
    Qdelete_process_instance = STATIC_SYMBOL("DELETE-PROCESS-INSTANCE",
	    AB_package);
    Qprocess_display_attributes = 
	    STATIC_SYMBOL("PROCESS-DISPLAY-ATTRIBUTES",AB_package);
    Qg2gl_system_attributes = STATIC_SYMBOL("G2GL-SYSTEM-ATTRIBUTES",
	    AB_package);
    Qprint_to_server = STATIC_SYMBOL("PRINT-TO-SERVER",AB_package);
    list_constant_105 = STATIC_LIST((SI_Long)21L,Qclose_and_continue,
	    Qbreak_on_execution_faults,Qdo_not_break_on_execution_faults,
	    Qremove_all_temporary_breakpoints,Qbring_up_source,
	    Qpause_process_instance,Qresume_process_instance,
	    Qdelete_process_instance,Qprocess_display_attributes,
	    Qg2gl_system_attributes,Qdescribe_configuration,Qprint,
	    Qprint_to_server,Qmark_to_strip_text,Qmark_to_strip_text_star,
	    Qremove_strip_text_mark,Qremove_strip_text_mark_star,
	    Qmark_not_to_strip_text_star,Qmark_not_to_strip_text,
	    Qremove_do_not_strip_text_mark_star,
	    Qremove_do_not_strip_text_mark);
    list_constant_106 = STATIC_LIST_STAR((SI_Long)32L,Qnew_object,
	    Qnew_rule,Qnew_display,Qnew_definition,Qnew_free_text,
	    Qnew_button,Qname,Qclone_workspace,Qtable,Qcolor,Qmove,
	    Qhide_workspace,Qgo_to_superior,Qlift_to_top,Qdrop_to_bottom,
	    Qshrink_wrap,Qdelete_workspace,Qenable,Qdisable,Qmiscellany,
	    Qmain_menu,Qoperate_on_area,Qab_describe,Qview_change_log,
	    Qtoggle_visible_grid,Qcompile_g2gl_process_workspace,
	    Qclean_up_g2gl_compilation_postings_on_body,
	    Qexecute_g2gl_process_workspace,Qredo_layout_of_g2gl_body,
	    Qsingle_step,Qdo_not_single_step,list_constant_105);
    if (Workspace_menu_choices == UNBOUND)
	Workspace_menu_choices = list_constant_106;
    Qinclude = STATIC_SYMBOL("INCLUDE",AB_package);
    Qinclude_additionally = STATIC_SYMBOL("INCLUDE-ADDITIONALLY",AB_package);
    Qexclude = STATIC_SYMBOL("EXCLUDE",AB_package);
    Qexclude_additionally = STATIC_SYMBOL("EXCLUDE-ADDITIONALLY",AB_package);
    Qexclude_absolutely = STATIC_SYMBOL("EXCLUDE-ABSOLUTELY",AB_package);
    list_constant_107 = STATIC_LIST((SI_Long)5L,Qinclude,
	    Qinclude_additionally,Qexclude,Qexclude_additionally,
	    Qexclude_absolutely);
    Menu_and_attribute_visibility_configurations_restriction_types = 
	    list_constant_107;
    Qworkspace_menu = STATIC_SYMBOL("WORKSPACE-MENU",AB_package);
    Qitem_menu = STATIC_SYMBOL("ITEM-MENU",AB_package);
    Qnon_menu = STATIC_SYMBOL("NON-MENU",AB_package);
    list_constant_108 = STATIC_LIST((SI_Long)3L,Qworkspace_menu,Qitem_menu,
	    Qnon_menu);
    Menu_configuration_operation_types = list_constant_108;
    Qobject_configuration = STATIC_SYMBOL("OBJECT-CONFIGURATION",AB_package);
    Qobject_configuration_clause = 
	    STATIC_SYMBOL("OBJECT-CONFIGURATION-CLAUSE",AB_package);
    add_grammar_rules_for_list(5,Qobject_configuration,
	    Qobject_configuration_clause,Qsc,Qnil,Qnone);
    string_constant_158 = 
	    STATIC_STRING("1p1m83-hJy83sly1m83-hJy83sky1m83-hJy83-Bqy1m83-hJy83-G1y1m83-hJy83-G0y");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_158));
    Qfix_object_configuration_clause = 
	    STATIC_SYMBOL("FIX-OBJECT-CONFIGURATION-CLAUSE",AB_package);
    string_constant_159 = 
	    STATIC_STRING("1l1o83sly1q1m9k83-Noy1m9k9l1m9k83oIy1m9k83D0y837jy83-vny2l83Fjyq9m");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qfix_object_configuration_clause);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_159));
    Qg2 = STATIC_SYMBOL("G2",AB_package);
    Qexecute = STATIC_SYMBOL("EXECUTE",AB_package);
    Qinform = STATIC_SYMBOL("INFORM",AB_package);
    Qconnect = STATIC_SYMBOL("CONNECT",AB_package);
    Qgsi = STATIC_SYMBOL("GSI",AB_package);
    Qtelewindows = STATIC_SYMBOL("TELEWINDOWS",AB_package);
    Qnetwork_access = STATIC_SYMBOL("NETWORK-ACCESS",AB_package);
    Qfix_network_configuration_clause = 
	    STATIC_SYMBOL("FIX-NETWORK-CONFIGURATION-CLAUSE",AB_package);
    SET_SYMBOL_FUNCTION(Qfix_network_configuration_clause,
	    STATIC_FUNCTION(fix_network_configuration_clause,NIL,FALSE,1,1));
    string_constant_160 = 
	    STATIC_STRING("1l1o83sky1q1m9k9l1m9k837by1m9k83-7Hy1m9k83Aby837jy83-gOy2l83-gMyq9m");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qset);
    push_optimized_constant(Qfix_network_configuration_clause);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_160));
    string_constant_161 = 
	    STATIC_STRING("1l1o83-G0y1n1m9k83-NDy837jy83-NFy2l83-NDyn9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qfix_object_configuration_clause);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_161));
    string_constant_162 = 
	    STATIC_STRING("1l1m837jy1n1m9k83*5y1m9k83-UMy1m9k83-Py");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_162));
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qsc,Qcm);
    SET_SYMBOL_FUNCTION(Qfix_object_configuration_clause,
	    STATIC_FUNCTION(fix_object_configuration_clause,NIL,FALSE,1,1));
    Qmassage_user_declaration_clause = 
	    STATIC_SYMBOL("MASSAGE-USER-DECLARATION-CLAUSE",AB_package);
    string_constant_163 = 
	    STATIC_STRING("1m1o83-G1y1o1m9k83gXy1m9k83-kYy837jy83-vhy2m83umy0o9l1o83-G1y1q1m9k83gXy1m9k83-kYy1m9k83-Ty8399y837jy83-vhy2m83umyoq9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qmassage_user_declaration_clause);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_163));
    SET_SYMBOL_FUNCTION(Qmassage_user_declaration_clause,
	    STATIC_FUNCTION(massage_user_declaration_clause,NIL,FALSE,1,1));
    Quser_declarations = STATIC_SYMBOL("USER-DECLARATIONS",AB_package);
    Quser_declaration_element = STATIC_SYMBOL("USER-DECLARATION-ELEMENT",
	    AB_package);
    add_grammar_rules_for_list(5,Quser_declarations,
	    Quser_declaration_element,Qcm,Qnil,Qnil);
    string_constant_164 = 
	    STATIC_STRING("1m1n83-vgy83wry1ml8k1n83-vgy1m1m9k9l83wry1mm0");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnot);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_164));
    string_constant_165 = 
	    STATIC_STRING("1u1m83wry1m9k83-qVy1m83wry1m9k83-Zfy1m83wry1m9k83-qWy1m83wry1m9k83pPy1m83wry1m9k83w7y1m83wry1m9k83-dey1m83wry1m9k83-E1y1m83wry1m");
    string_constant_166 = 
	    STATIC_STRING("9k83-hsy1m83wry1m9k83-a=y1m83wry1m9k83-aby");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_165,
	    string_constant_166)));
    Qno_manual_connections = STATIC_SYMBOL("NO-MANUAL-CONNECTIONS",AB_package);
    Qmanual_connections = STATIC_SYMBOL("MANUAL-CONNECTIONS",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qnetwork_access_options = STATIC_SYMBOL("NETWORK-ACCESS-OPTIONS",
	    AB_package);
    Qnetwork_access_option = STATIC_SYMBOL("NETWORK-ACCESS-OPTION",AB_package);
    add_grammar_rules_for_list(5,Qnetwork_access_options,
	    Qnetwork_access_option,Qcm,Qnil,Qnil);
    string_constant_167 = 
	    STATIC_STRING("1v1n83-gNy1o83-7Jy1m9k83Aby1m9k83*ty83-gQy1mol1n83-gNy1m83-7Jy83sMy1o83=by0lm1n83-gNy1m83-0+y83s6y1o83=by0lm1n83-gNy1m83-7Jy83xb");
    string_constant_168 = 
	    STATIC_STRING("y1o830Jy0lm1n83-gNy1o83-7Jy83sMy1m9k83=3y8399y1o83=byolm1n83-gNy1o83-7Jy83xby1m9k83=3y8399y1o830Jyolm1n83-gNy1o83-7Jy83sMy1m9k83");
    string_constant_169 = 
	    STATIC_STRING("*ty83-7Iy1oo0lm1n83-gNy1o83-7Jy83xby1m9k83*ty1m9k830Jy1o830Jy0lm1n83-gNy1o83-0+y83s6y1m9k83*ty83s4y1oo0lm1n83-gNy1q83-7Jy83sMy1m");
    string_constant_170 = 
	    STATIC_STRING("9k83=3y8399y1m9k83*ty83-7Iy1oqolm1n83-gNy1q83-7Jy83xby1m9k83=3y8399y1m9k83*ty1m9k830Jy1o830Jyolm");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_4(string_constant_167,
	    string_constant_168,string_constant_169,string_constant_170)));
    string_constant_171 = 
	    STATIC_STRING("1n1n83-7Jy1m9k837gy83ivy1n83-7Jy1m9k83-9Uy836ny1n83-7Jy1m1m9k83-9Uy1m9k83pJy83voy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_171));
    string_constant_172 = 
	    STATIC_STRING("1m1n83-0+y1m9k837gy83ivy1n83-0+y1m9k83-9Uy836ny");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_172));
    Qfix_item_filter_phrase = STATIC_SYMBOL("FIX-ITEM-FILTER-PHRASE",
	    AB_package);
    string_constant_173 = STATIC_STRING("1l1o83sMy1m83-NLy1m9k83Abyl9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qfix_item_filter_phrase);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_173));
    string_constant_174 = STATIC_STRING("1l1o83xby1m83-VTy1m9k83Abyl9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qfix_item_filter_phrase);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_174));
    string_constant_175 = STATIC_STRING("1l1o83s6y1m83s5y1m9k83Aby1ll9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qfix_item_filter_phrase);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_175));
    Qcommon_network_access_type_list = 
	    STATIC_SYMBOL("COMMON-NETWORK-ACCESS-TYPE-LIST",AB_package);
    Qcommon_network_access_type = 
	    STATIC_SYMBOL("COMMON-NETWORK-ACCESS-TYPE",AB_package);
    add_grammar_rules_for_list(5,Qcommon_network_access_type_list,
	    Qcommon_network_access_type,Qcm,Qab_or,Qnil);
    Qg2_network_access_type_list = 
	    STATIC_SYMBOL("G2-NETWORK-ACCESS-TYPE-LIST",AB_package);
    Qg2_network_access_type = STATIC_SYMBOL("G2-NETWORK-ACCESS-TYPE",
	    AB_package);
    add_grammar_rules_for_list(5,Qg2_network_access_type_list,
	    Qg2_network_access_type,Qcm,Qab_or,Qnil);
    Qnetwork_accessing_product_list = 
	    STATIC_SYMBOL("NETWORK-ACCESSING-PRODUCT-LIST",AB_package);
    Qnetwork_accessing_product = STATIC_SYMBOL("NETWORK-ACCESSING-PRODUCT",
	    AB_package);
    add_grammar_rules_for_list(5,Qnetwork_accessing_product_list,
	    Qnetwork_accessing_product,Qcm,Qab_or,Qnil);
    string_constant_176 = 
	    STATIC_STRING("1m1m83-NKy1m9k83-=Wy1m83-NKy1m9k83-TEy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_176));
    string_constant_177 = STATIC_STRING("1m1m83-VSy1m9k9l1m83-VSy1m9k9m");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qread);
    push_optimized_constant(Qwrite);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_177));
    string_constant_178 = STATIC_STRING("1l1m83s5y1m9k836iy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_178));
    string_constant_179 = 
	    STATIC_STRING("1o1m83-7Iy1m9k830Jy1m83-7Iy1m9k831Jy1n83-7Iy1n1m9k830Jy1m9k83-ty1m9k831Jy83xMy1n83-7Iy1n1m9k831Jy1m9k83-ty1m9k830Jy83xMy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_179));
    string_constant_180 = 
	    STATIC_STRING("1z1m83s4y1m9k830Jy1m83s4y1m9k83-EVy1m83s4y1m9k831Jy1n83s4y1n1m9k830Jy1m9k83-ty1m9k831Jy83xMy1n83s4y1p1m9k830Jy1m9k83-ty1m9k831Jy");
    string_constant_181 = 
	    STATIC_STRING("1m9k83-ty1m9k83-EVy83-VHy1n83s4y1n1m9k830Jy1m9k83-ty1m9k83-EVy83-VGy1n83s4y1p1m9k830Jy1m9k83-ty1m9k83-EVy1m9k83-ty1m9k831Jy83-VH");
    string_constant_182 = 
	    STATIC_STRING("y1n83s4y1n1m9k831Jy1m9k83-ty1m9k830Jy83xMy1n83s4y1p1m9k831Jy1m9k83-ty1m9k830Jy1m9k83-ty1m9k83-EVy83-VHy1n83s4y1n1m9k831Jy1m9k83-");
    string_constant_183 = 
	    STATIC_STRING("ty1m9k83-EVy83-sIy1n83s4y1p1m9k831Jy1m9k83-ty1m9k83-EVy1m9k83-ty1m9k831Jy83-VHy1n83s4y1n1m9k83-EVy1m9k83-ty1m9k830Jy83-VGy1n83s4");
    string_constant_184 = 
	    STATIC_STRING("y1p1m9k83-EVy1m9k83-ty1m9k830Jy1m9k83-ty1m9k831Jy83-VHy1n83s4y1n1m9k83-EVy1m9k83-ty1m9k831Jy83-sIy1n83s4y1p1m9k83-EVy1m9k83-ty1m");
    string_constant_185 = STATIC_STRING("9k831Jy1m9k83-ty1m9k830Jy83-VHy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(list(6,
	    string_constant_180,string_constant_181,string_constant_182,
	    string_constant_183,string_constant_184,string_constant_185)));
    string_constant_186 = 
	    STATIC_STRING("1n1m83-gPy1m9k830Jy1m83-gPy1m9k831Jy1m83-gPy1m9k83-EVy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_186));
    Quser_mode_annotations = STATIC_SYMBOL("USER-MODE-ANNOTATIONS",AB_package);
    Quser_mode_annotation = STATIC_SYMBOL("USER-MODE-ANNOTATION",AB_package);
    add_grammar_rules_for_list(5,Quser_mode_annotations,
	    Quser_mode_annotation,Qsc,Qnil,Qnil);
    string_constant_187 = 
	    STATIC_STRING("1l1o83-vmy1p83Fuy1m9k83*Xy839Sy1m9k83-Py83-vfy2mlnp9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qfix_mode_restriction);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_187));
    Quser_annotation_clause_list = 
	    STATIC_SYMBOL("USER-ANNOTATION-CLAUSE-LIST",AB_package);
    Quser_annotation_clause = STATIC_SYMBOL("USER-ANNOTATION-CLAUSE",
	    AB_package);
    add_grammar_rules_for_list(5,Quser_annotation_clause_list,
	    Quser_annotation_clause,Qsc,Qnil,Qnil);
    Qfor_filters = STATIC_SYMBOL("FOR-FILTERS",AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    Qat = STATIC_SYMBOL("@",AB_package);
    array_constant_1 = STATIC_ARRAY(list_constant_96,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)64L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)64L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    Qkeyboard_symbol = STATIC_SYMBOL("KEYBOARD-SYMBOL",AB_package);
    Qf1 = STATIC_SYMBOL("F1",AB_package);
    Qf2 = STATIC_SYMBOL("F2",AB_package);
    Qf3 = STATIC_SYMBOL("F3",AB_package);
    Qf4 = STATIC_SYMBOL("F4",AB_package);
    Qf5 = STATIC_SYMBOL("F5",AB_package);
    Qf6 = STATIC_SYMBOL("F6",AB_package);
    Qf7 = STATIC_SYMBOL("F7",AB_package);
    Qf8 = STATIC_SYMBOL("F8",AB_package);
    Qf9 = STATIC_SYMBOL("F9",AB_package);
    Qf10 = STATIC_SYMBOL("F10",AB_package);
    Qf11 = STATIC_SYMBOL("F11",AB_package);
    Qf12 = STATIC_SYMBOL("F12",AB_package);
    Qbackspace = STATIC_SYMBOL("BACKSPACE",AB_package);
    Qtab = STATIC_SYMBOL("TAB",AB_package);
    Qlinefeed = STATIC_SYMBOL("LINEFEED",AB_package);
    Qescape = STATIC_SYMBOL("ESCAPE",AB_package);
    Q0 = STATIC_SYMBOL("0",AB_package);
    Q1 = STATIC_SYMBOL("1",AB_package);
    Q2 = STATIC_SYMBOL("2",AB_package);
    Q3 = STATIC_SYMBOL("3",AB_package);
    Q4 = STATIC_SYMBOL("4",AB_package);
    Q5 = STATIC_SYMBOL("5",AB_package);
    Q6 = STATIC_SYMBOL("6",AB_package);
    Q7 = STATIC_SYMBOL("7",AB_package);
    Q8 = STATIC_SYMBOL("8",AB_package);
    Q9 = STATIC_SYMBOL("9",AB_package);
    Qcol = STATIC_SYMBOL(":",AB_package);
    Qqm = STATIC_SYMBOL("\?",AB_package);
    Qa = STATIC_SYMBOL("A",AB_package);
    Qb = STATIC_SYMBOL("B",AB_package);
    Qc = STATIC_SYMBOL("C",AB_package);
    Qd = STATIC_SYMBOL("D",AB_package);
    Qe = STATIC_SYMBOL("E",AB_package);
    Qf = STATIC_SYMBOL("F",AB_package);
    Qg = STATIC_SYMBOL("G",AB_package);
    Qh = STATIC_SYMBOL("H",AB_package);
    Qi = STATIC_SYMBOL("I",AB_package);
    Qj = STATIC_SYMBOL("J",AB_package);
    Qk = STATIC_SYMBOL("K",AB_package);
    Ql = STATIC_SYMBOL("L",AB_package);
    Qm = STATIC_SYMBOL("M",AB_package);
    Qn = STATIC_SYMBOL("N",AB_package);
    Qo = STATIC_SYMBOL("O",AB_package);
    Qp = STATIC_SYMBOL("P",AB_package);
    Qq = STATIC_SYMBOL("Q",AB_package);
    Qr = STATIC_SYMBOL("R",AB_package);
    Qs = STATIC_SYMBOL("S",AB_package);
    Qu = STATIC_SYMBOL("U",AB_package);
    Qv = STATIC_SYMBOL("V",AB_package);
    Qw = STATIC_SYMBOL("W",AB_package);
    Qx = STATIC_SYMBOL("X",AB_package);
    Qy = STATIC_SYMBOL("Y",AB_package);
    Qz = STATIC_SYMBOL("Z",AB_package);
    Qobt = STATIC_SYMBOL("[",AB_package);
    Qcbt = STATIC_SYMBOL("]",AB_package);
    Qct = STATIC_SYMBOL("^",AB_package);
    Q_ = STATIC_SYMBOL("_",AB_package);
    Qbq = STATIC_SYMBOL("`",AB_package);
    Qob = STATIC_SYMBOL("{",AB_package);
    Qab_or_1 = STATIC_SYMBOL("|",AB_package);
    Qcb = STATIC_SYMBOL("}",AB_package);
    Qex = STATIC_SYMBOL("!",AB_package);
    Qdq = STATIC_SYMBOL("\"",AB_package);
    Qno = STATIC_SYMBOL("#",AB_package);
    Qdol = STATIC_SYMBOL("$",AB_package);
    Qpct = STATIC_SYMBOL("%",AB_package);
    Qab_and = STATIC_SYMBOL("&",AB_package);
    Qqu = STATIC_SYMBOL("\'",AB_package);
    Qop = STATIC_SYMBOL("(",AB_package);
    Qcp = STATIC_SYMBOL(")",AB_package);
    Qdot = STATIC_SYMBOL(".",AB_package);
    Qmouse_wheel_forward = STATIC_SYMBOL("MOUSE-WHEEL-FORWARD",AB_package);
    Qmouse_wheel_backward = STATIC_SYMBOL("MOUSE-WHEEL-BACKWARD",AB_package);
    Qmouse_hover = STATIC_SYMBOL("MOUSE-HOVER",AB_package);
    Qenter = STATIC_SYMBOL("ENTER",AB_package);
    Qinsert = STATIC_SYMBOL("INSERT",AB_package);
    Qredo = STATIC_SYMBOL("REDO",AB_package);
    Qhome = STATIC_SYMBOL("HOME",AB_package);
    Qbegin = STATIC_SYMBOL("BEGIN",AB_package);
    Qend = STATIC_SYMBOL("END",AB_package);
    Qselect = STATIC_SYMBOL("SELECT",AB_package);
    Qabort_g2 = STATIC_SYMBOL("ABORT",AB_package);
    Qclear_screen = STATIC_SYMBOL("CLEAR-SCREEN",AB_package);
    Qup_arrow = STATIC_SYMBOL("UP-ARROW",AB_package);
    Qdown_arrow = STATIC_SYMBOL("DOWN-ARROW",AB_package);
    Qleft_arrow = STATIC_SYMBOL("LEFT-ARROW",AB_package);
    Qright_arrow = STATIC_SYMBOL("RIGHT-ARROW",AB_package);
    Qprevious_screen = STATIC_SYMBOL("PREVIOUS-SCREEN",AB_package);
    Qnext_screen = STATIC_SYMBOL("NEXT-SCREEN",AB_package);
    list_constant_109 = STATIC_LIST((SI_Long)16L,Qfind,Qhome,Qbegin,Qend,
	    Qpause,Qselect,Qprint,Qexecute,Qabort_g2,Qclear_screen,
	    Qup_arrow,Qdown_arrow,Qleft_arrow,Qright_arrow,
	    Qprevious_screen,Qnext_screen);
    list_constant_110 = STATIC_LIST_STAR((SI_Long)32L,Q_,Qbq,Qob,Qab_or_1,
	    Qcb,Qspace,Qex,Qdq,Qno,Qdol,Qpct,Qab_and,Qqu,Qop,Qcp,Qstar,
	    Qplus,Qcm,Qminus,Qdot,Qslash,Qdelete,Qmouse_wheel_forward,
	    Qmouse_wheel_backward,Qmouse_hover,Qbreak,Qenter,Qhelp,Qinsert,
	    Qredo,Qmenu,list_constant_109);
    list_constant_111 = STATIC_LIST_STAR((SI_Long)32L,Qnum_gt,Qqm,Qa,Qb,Qc,
	    Qd,Qe,Qf,Qg,Qh,Qi,Qj,Qk,Ql,Qm,Qn,Qo,Qp,Qq,Qr,Qs,Qt,Qu,Qv,Qw,Qx,
	    Qy,Qz,Qobt,Qcbt,Qct,list_constant_110);
    list_constant_112 = STATIC_LIST_STAR((SI_Long)32L,Qf1,Qf2,Qf3,Qf4,Qf5,
	    Qf6,Qf7,Qf8,Qf9,Qf10,Qf11,Qf12,Qbackspace,Qtab,Qlinefeed,
	    Qreturn,Qescape,Q0,Q1,Q2,Q3,Q4,Q5,Q6,Q7,Q8,Q9,Qcol,Qsc,Qnum_lt,
	    Qnum_eq,list_constant_111);
    Qstring_to_display_for_keyboard_symbol = 
	    STATIC_SYMBOL("STRING-TO-DISPLAY-FOR-KEYBOARD-SYMBOL",AB_package);
    SET_SYMBOL_FUNCTION(Qstring_to_display_for_keyboard_symbol,
	    STATIC_FUNCTION(string_to_display_for_keyboard_symbol,NIL,
	    FALSE,2,2));
    Qstring_to_insert_for_keyboard_symbol = 
	    STATIC_SYMBOL("STRING-TO-INSERT-FOR-KEYBOARD-SYMBOL",AB_package);
    SET_SYMBOL_FUNCTION(Qstring_to_insert_for_keyboard_symbol,
	    STATIC_FUNCTION(string_to_insert_for_keyboard_symbol,NIL,FALSE,
	    1,1));
    def_semi_open_category_1(5,Qkeyboard_symbol,list_constant_112,Qsymbol,
	    SYMBOL_FUNCTION(Qstring_to_display_for_keyboard_symbol),
	    SYMBOL_FUNCTION(Qstring_to_insert_for_keyboard_symbol));
    string_constant_188 = 
	    STATIC_STRING("1n1m83-vey83oMy1m83-vey83fvy1m83-vey83gGy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_188));
    string_constant_189 = 
	    STATIC_STRING("1m1n83gGy1w1m9k83-ORy1m9k83-fwy8399y1m9k83FHy1m9k8319y1m9k9l1m9k83Ry1m9k83-JRy1m9k830Py1m9k9l1m9k83Qxy83--ey1ol83-fwynw1n83gGy1r");
    string_constant_190 = 
	    STATIC_STRING("1m9k83-ORy1m9k83-fwy8399y1m9k83=3y1m9k9l1m9k83Ygy83Ygy1ol83Ygynr");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qthe);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_189,
	    string_constant_190)));
    string_constant_191 = 
	    STATIC_STRING("1o1m83-70y1m9k83BGy1m83-70y1m9k83-Rqy1m83-70y1m9k839ky1m83-70y1m9k83-m1y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_191));
    Qparse_user_interface_gesture = 
	    STATIC_SYMBOL("PARSE-USER-INTERFACE-GESTURE",AB_package);
    Quser_mouse_tracking = STATIC_SYMBOL("USER-MOUSE-TRACKING",AB_package);
    string_constant_192 = 
	    STATIC_STRING("1x1o83fvy1n83-70y83-G4y83-=Hy1nlmn9k1o83fvy1p83-70y83-G4y1m9l830Py83-Gxy83-=Jy1olmpo9k1o83fvy1p83-70y83-G4y1m9l830Py8399y83-=Iy1");
    string_constant_193 = 
	    STATIC_STRING("olmpo9k1o83fvy1w1m9l839ky83-G4y1m9l830Py8399y1m9l83-qmy834Ry1m9l83*5y1m9l9m1m9l83E-y1m9l83-tjy1m9l83lHy8399y1o839kym1n9nqwo9k1o8");
    string_constant_194 = 
	    STATIC_STRING("3fvy1x1m9l839ky83-G4y1m9l830Py8399y1m9l83-qmy834Ry1m9l83*5y1m9l9m1m9l83E-y1m9l83-tjy1m9l83-Ody1m9l83lHy8399y1o839kym1o9nqx83-fby");
    string_constant_195 = 
	    STATIC_STRING("o9k1o83fvy1n1m9l83-ufy83-G2y83-=Hy1n83-ufymn9k1o83fvy1p1m9l83-ufy83-G2y1m9l830Py83-Gxy83-=Jy1o83-ufympo9k1o83fvy1p1m9l83-ufy83-G");
    string_constant_196 = 
	    STATIC_STRING("2y1m9l830Py8399y83-=Iy1o83-ufympo9k1o83fvy1n1m9l83-nEy83-73y83-=Hy1n83-nEymn9k1o83fvy1p1m9l83-nEy83-73y1m9l83lHy83-Gxy83-=Jy1o83");
    string_constant_197 = 
	    STATIC_STRING("-nEympo9k1o83fvy1p1m9l83-nEy83-73y1m9l83lHy8399y83-=Iy1o83-nEympo9k1o83fvy1p1m9l83-YIy83-71y1m9l83lHy83-Gxy83-=Jy1o83-YIympo9k1o");
    string_constant_198 = 
	    STATIC_STRING("83fvy1p1m9l83-YIy83-71y1m9l83lHy8399y83-=Iy1o83-YIympo9k");
    clear_optimized_constants();
    push_optimized_constant(Qparse_user_interface_gesture);
    push_optimized_constant(Qquote);
    push_optimized_constant(Qthe);
    push_optimized_constant(Quser_mouse_tracking);
    add_grammar_rules_function(regenerate_optimized_constant(list(7,
	    string_constant_192,string_constant_193,string_constant_194,
	    string_constant_195,string_constant_196,string_constant_197,
	    string_constant_198)));
    Qnothing = STATIC_SYMBOL("NOTHING",AB_package);
    string_constant_199 = 
	    STATIC_STRING("1n1n83-=Hy1m1m9k83Cpy83-2hym1n83-=Hy1m1m9k83Cpy83--0ym1n83-=Hy1m1m9k838By1m9k9l9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnothing);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_199));
    string_constant_200 = 
	    STATIC_STRING("1m1n83-=Jy1m1m9k83Cpy83obym1n83-=Jy1m1m9k838By1m9k9l9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnothing);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_200));
    string_constant_201 = 
	    STATIC_STRING("1m1n83-=Iy1m1m9k83Cpy83jPym1n83-=Iy1m1m9k838By1m9k9l9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnothing);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_201));
    Quser_restrictable_classes = STATIC_SYMBOL("USER-RESTRICTABLE-CLASSES",
	    AB_package);
    Quser_restrictable_class = STATIC_SYMBOL("USER-RESTRICTABLE-CLASS",
	    AB_package);
    add_grammar_rules_for_list(5,Quser_restrictable_classes,
	    Quser_restrictable_class,Qcm,Qab_or,Qnil);
    string_constant_202 = 
	    STATIC_STRING("1n1m83-vqy83-Gy1m83-vqy1m9k835ny1m83-vqy1m9k83*qy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_202));
    string_constant_203 = 
	    STATIC_STRING("1m1o8399y1m1m9k83=by83-vrym9l1o8399y1m1m9k837Zy1m9k83Rym9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qfix_item_filter_phrase);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_203));
    string_constant_204 = 
	    STATIC_STRING("1l1n83-Gxy1m1m9k83=by1m9k83*qy1l83*qy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_204));
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qcm,Qsc);
    SET_SYMBOL_FUNCTION(Qfix_item_filter_phrase,
	    STATIC_FUNCTION(fix_item_filter_phrase,NIL,FALSE,1,1));
    Qgrid_spec_must_be_positive = 
	    STATIC_SYMBOL("GRID-SPEC-MUST-BE-POSITIVE",AB_package);
    string_constant_205 = 
	    STATIC_STRING("1l1o83--ey1p1m9k83-9y83-ey1m9k83vy83-ey1m9k83-Ay2lmo9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qgrid_spec_must_be_positive);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_205));
    array_constant_2 = STATIC_ARRAY(list_constant_96,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)10L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)13L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)16L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)17L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)18L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)19L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)20L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)21L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)23L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)24L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)25L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)26L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)28L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)29L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)30L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)31L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)32L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)33L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)34L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)35L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)36L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)37L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)38L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)39L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)40L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)41L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)42L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)43L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)46L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)47L,(SI_Long)57344L);
    SET_SYMBOL_FUNCTION(Qgrid_spec_must_be_positive,
	    STATIC_FUNCTION(grid_spec_must_be_positive,NIL,FALSE,1,1));
    set_grammar_transform_can_return_bad_phrase_p(Qgrid_spec_must_be_positive);
    string_constant_206 = 
	    STATIC_STRING("1l1n83Ygy1t1m9k83-9y83Sy1m9k83vy83Sy1m9k83vy83Sy1m9k83vy83Sy1m9k83-Ay1omoqs");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_206));
    string_constant_1 = STATIC_STRING("double-clicking ");
    string_constant_2 = STATIC_STRING("clicking ");
    string_constant_3 = STATIC_STRING("pressing ");
    string_constant_4 = STATIC_STRING("releasing ");
    string_constant_5 = STATIC_STRING("any mouse button");
    string_constant_6 = STATIC_STRING("the left mouse button");
    string_constant_7 = STATIC_STRING("the middle mouse button");
    string_constant_8 = STATIC_STRING("the right mouse button");
    Qany_mouse_button = STATIC_SYMBOL("ANY-MOUSE-BUTTON",AB_package);
    Qclicking = STATIC_SYMBOL("CLICKING",AB_package);
    Qmouse_select = STATIC_SYMBOL("MOUSE-SELECT",AB_package);
    Qpressing = STATIC_SYMBOL("PRESSING",AB_package);
    Qmouse_down = STATIC_SYMBOL("MOUSE-DOWN",AB_package);
    Qreleasing = STATIC_SYMBOL("RELEASING",AB_package);
    Qmouse_up = STATIC_SYMBOL("MOUSE-UP",AB_package);
    Qdouble_clicking = STATIC_SYMBOL("DOUBLE-CLICKING",AB_package);
    Qleft_mouse_button = STATIC_SYMBOL("LEFT-MOUSE-BUTTON",AB_package);
    Qmouse_left_select = STATIC_SYMBOL("MOUSE-LEFT-SELECT",AB_package);
    Qmouse_left_down = STATIC_SYMBOL("MOUSE-LEFT-DOWN",AB_package);
    Qmouse_left_up = STATIC_SYMBOL("MOUSE-LEFT-UP",AB_package);
    Qmiddle_mouse_button = STATIC_SYMBOL("MIDDLE-MOUSE-BUTTON",AB_package);
    Qmouse_middle_select = STATIC_SYMBOL("MOUSE-MIDDLE-SELECT",AB_package);
    Qmouse_middle_down = STATIC_SYMBOL("MOUSE-MIDDLE-DOWN",AB_package);
    Qmouse_middle_up = STATIC_SYMBOL("MOUSE-MIDDLE-UP",AB_package);
    Qright_mouse_button = STATIC_SYMBOL("RIGHT-MOUSE-BUTTON",AB_package);
    Qmouse_right_select = STATIC_SYMBOL("MOUSE-RIGHT-SELECT",AB_package);
    Qmouse_right_down = STATIC_SYMBOL("MOUSE-RIGHT-DOWN",AB_package);
    Qmouse_right_up = STATIC_SYMBOL("MOUSE-RIGHT-UP",AB_package);
    Qdouble = STATIC_SYMBOL("DOUBLE",AB_package);
    Qtyping = STATIC_SYMBOL("TYPING",AB_package);
    Qrolling = STATIC_SYMBOL("ROLLING",AB_package);
    Qhovering = STATIC_SYMBOL("HOVERING",AB_package);
    Qselecting = STATIC_SYMBOL("SELECTING",AB_package);
    string_constant_9 = STATIC_STRING("Not a known keyboard symbol");
    string_constant_10 = 
	    STATIC_STRING("You are not allowed to rebind control+y");
    SET_SYMBOL_FUNCTION(Qparse_user_interface_gesture,
	    STATIC_FUNCTION(parse_user_interface_gesture,NIL,FALSE,1,1));
    set_grammar_transform_can_return_bad_phrase_p(Qparse_user_interface_gesture);
    Qparse_user_interface_key_chord = 
	    STATIC_SYMBOL("PARSE-USER-INTERFACE-KEY-CHORD",AB_package);
    SET_SYMBOL_FUNCTION(Qparse_user_interface_key_chord,
	    STATIC_FUNCTION(parse_user_interface_key_chord,NIL,FALSE,1,1));
    string_constant_207 = 
	    STATIC_STRING("1n1m83-G2y83-c*y1o83-G2y1n83Dry1m9k9l83-c*y1mln9m1m83-G2y83-Uy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qplus);
    push_optimized_constant(Qparse_user_interface_key_chord);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_207));
    string_constant_208 = 
	    STATIC_STRING("1m1n83wny1o1m9k9l1m9k83E-y1m9k83-wvy1m9k83hRy83-fhy1n83wny1o1m9k9l1m9k83E-y1m9k83-wvy1m9k83fIy83-fgy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qthe);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_208));
    string_constant_209 = 
	    STATIC_STRING("1m1m83-73y83wny1o83-73y1n83Dry1m9k9l83wny1mln9m");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qplus);
    push_optimized_constant(Qparse_user_interface_key_chord);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_209));
    string_constant_210 = 
	    STATIC_STRING("1m1n83-71y1m1m9k9l1m9k83E-y1l83-fdy1o83-71y1o83Dry1m9k9m1m9k9l1m9k83E-y1ml83-fdy9n");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qplus);
    push_optimized_constant(Qparse_user_interface_key_chord);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_210));
    string_constant_211 = 
	    STATIC_STRING("1o1n83-G3y1n1m9k83=by1m9k83E-y1m9k833hy1l83-Jjy1n83-G3y1o1m9k9l1m9k83*hy1m9k83E-y1m9k833hy1l83-cLy1n83-G3y1o1m9k9l1m9k83-egy1m9k");
    string_constant_212 = 
	    STATIC_STRING("83E-y1m9k833hy1l83-ehy1n83-G3y1o1m9k9l1m9k83-by1m9k83E-y1m9k833hy1l83-n4y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qthe);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_211,
	    string_constant_212)));
    string_constant_213 = 
	    STATIC_STRING("1m1m83-G4y83-G3y1o83-G4y1n83Dry1m9k9l83-G3y1mln9m");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qplus);
    push_optimized_constant(Qparse_user_interface_key_chord);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_213));
    string_constant_214 = 
	    STATIC_STRING("1n1m83-fOy1m9k83Ioy1m83-fOy1m9k83-oXy1m83-fOy1m9k83-Jby");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_214));
    Qmodifier_key_list = STATIC_SYMBOL("MODIFIER-KEY-LIST",AB_package);
    Qmodifier_key = STATIC_SYMBOL("MODIFIER-KEY",AB_package);
    add_grammar_rules_for_list(5,Qmodifier_key_list,Qmodifier_key,Qplus,
	    Qnil,Qnil);
    Qremove_separator_symbol_from_phrase = 
	    STATIC_SYMBOL("REMOVE-SEPARATOR-SYMBOL-FROM-PHRASE",AB_package);
    string_constant_215 = STATIC_STRING("1l1o83Dry83-fPyl9k");
    clear_optimized_constants();
    push_optimized_constant(Qremove_separator_symbol_from_phrase);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_215));
    SET_SYMBOL_FUNCTION(Qremove_separator_symbol_from_phrase,
	    STATIC_FUNCTION(remove_separator_symbol_from_phrase,NIL,FALSE,
	    1,1));
    string_constant_216 = 
	    STATIC_STRING("1m1n83-hQy1n1m9k83-Ty8399y1m9k83*Iym1n83-hQy1m9k83*Iy0");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_216));
    string_constant_217 = 
	    STATIC_STRING("1l1n83lEy1p1m9k83-9y83Sy1m9k83vy83Sy1m9k83-Ay1mmo");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_217));
    string_constant_218 = 
	    STATIC_STRING("1l1o83-Bqy1p1m9k83-mWy1m9k839qy1m9k83jRy837jy83-kcy2l839qyp9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qfix_object_configuration_clause);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_218));
    Qproprietary_restriction_clause_list = 
	    STATIC_SYMBOL("PROPRIETARY-RESTRICTION-CLAUSE-LIST",AB_package);
    Qproprietary_restriction_clause = 
	    STATIC_SYMBOL("PROPRIETARY-RESTRICTION-CLAUSE",AB_package);
    add_grammar_rules_for_list(5,Qproprietary_restriction_clause_list,
	    Qproprietary_restriction_clause,Qsc,Qnil,Qnil);
    string_constant_219 = 
	    STATIC_STRING("1n1m83-kby83oMy1m83-kby83fvy1m83-kby83gGy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_219));
    Qcomment_options = STATIC_SYMBOL("COMMENT-OPTIONS",AB_package);
    Qcomment_option = STATIC_SYMBOL("COMMENT-OPTION",AB_package);
    add_grammar_rules_for_list(5,Qcomment_options,Qcomment_option,Qcm,Qnil,
	    Qnil);
    string_constant_220 = STATIC_STRING("1l1n83-NEy1n83-2y1m9k83-Py83-xy1mln");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_220));
    Quser_restrictions = STATIC_SYMBOL("USER-RESTRICTIONS",AB_package);
    Quser_mode_restriction = STATIC_SYMBOL("USER-MODE-RESTRICTION",AB_package);
    add_grammar_rules_for_list(5,Quser_restrictions,Quser_mode_restriction,
	    Qsc,Qnil,Qnone);
    string_constant_221 = 
	    STATIC_STRING("1l1o83-voy1p83Fuy1m9k83*Xy839Sy1m9k83-Py83-vsy2mlnp9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qfix_mode_restriction);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_221));
    Quser_restriction_clause_list = 
	    STATIC_SYMBOL("USER-RESTRICTION-CLAUSE-LIST",AB_package);
    Quser_restriction_clause = STATIC_SYMBOL("USER-RESTRICTION-CLAUSE",
	    AB_package);
    add_grammar_rules_for_list(5,Quser_restriction_clause_list,
	    Quser_restriction_clause,Qsc,Qnil,Qnil);
    string_constant_222 = 
	    STATIC_STRING("1r1m83oMy83-H*y1m83oMy83-0*y1m83oMy83-7Vy1m83oMy83-H2y1m83oMy83-00y1m83oMy83-DGy1m83oMy83-EMy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_222));
    Qprohibit_nothing = STATIC_SYMBOL("PROHIBIT-NOTHING",AB_package);
    Qfix_associative_list = STATIC_SYMBOL("FIX-ASSOCIATIVE-LIST",AB_package);
    Qdont_include_workspace = STATIC_SYMBOL("DONT-INCLUDE-WORKSPACE",
	    AB_package);
    string_constant_223 = 
	    STATIC_STRING("13Sy1p83-H*y1q1m9k9l1m9k83s*y1m9k83=Iy1m9k83*qy83mLy83-xSy2n834uy1l83*qypq9m1m9nn1n83-H*y1q1m9k9l1m9k83s*y1m9k83=Iy1m9k83*qy83-Z");
    string_constant_224 = 
	    STATIC_STRING("Sy1m9k9o1n834uy1l83*qyp1q83-0*y1p1m9k9l1m9k83s*y83-UVy83mLy83-bAy2n834uynop9m1m9nn1m9pl1o83-0*y1p1m9k9l1m9k83s*y83-UVy83-ZSy1m9k");
    string_constant_225 = 
	    STATIC_STRING("9o1n834uyno1m9pl1o83-UVy1m1m9k83=Iy83-mYym9q1q83-7Vy1q1m9k83-guy1m9k83s*y1m9k83=Iy83-mYy83mLy83-gwy2n83-guyopq9m1m9nn1m9pl1o83-7");
    string_constant_226 = 
	    STATIC_STRING("Vy1q1m9k83-guy1m9k83s*y1m9k83=Iy83-mYy83-ZSy1m9k9o1n83-guyop1m9pl1o83-H2y1p1m9k83-o0y1m9k83=by1m9k83*qy1m9k83Cpy83oby1n83-o0y1l8");
    string_constant_227 = 
	    STATIC_STRING("3*qyp9m1o83-H2y1q1m9k83-o0y1m9k83=by1m9k83*qy1m9k83pJy1m9k83Cpy83oby1n83-o1y1l83*qyq9m1n83-H2y1p1m9k83-o0y1m9k83=by1m9k83*qy1m9k");
    string_constant_228 = 
	    STATIC_STRING("838By1m9k9o1n83-o0y1l83*qy9o1n83-H2y1q1m9k83-o0y1m9k83=by1m9k83*qy1m9k83pJy1m9k838By1m9k9o1n83-o1y1l83*qy9o1p83-00y1p1m9k83-o0y1");
    string_constant_229 = 
	    STATIC_STRING("m9k83=by83-mYy1m9k83Cpy83jPy1n83-o0ynp9m1m9pl1p83-00y1q1m9k83-o0y1m9k83=by83-mYy1m9k83pJy1m9k83Cpy83jPy1n83-o1ynq9m1m9pl1o83-00y");
    string_constant_230 = 
	    STATIC_STRING("1p1m9k83-o0y1m9k83=by83-mYy1m9k838By1m9k9o1n83-o0yn9o1m9pl1o83-00y1q1m9k83-o0y1m9k83=by83-mYy1m9k83pJy1m9k838By1m9k9o1n83-o1yn9o");
    string_constant_231 = 
	    STATIC_STRING("1m9pl1q83-DGy1q1m9k83Gry1m9k83-Gdy1m9k83=Iy83-mYy83mLy83fDy1o83Fryoqp9m1m9pl1m9pm1o83-DGy1q1m9k83Gry1m9k83-Gdy1m9k83=Iy83-mYy83-");
    string_constant_232 = 
	    STATIC_STRING("ZSy1m9k9o1o83Fryo0p1m9pl1r83-EMy1v1m9k83*Jy1m9k9l1m9k83s*y1m9k83=Iy1m9k9r83-K5y1m9k83-Ty1m9k83=by83-mYy83mLy83-s+y2o83*Jytquv9m1");
    string_constant_233 = 
	    STATIC_STRING("m9no1m9pl1m9pm1p83-EMy1v1m9k83*Jy1m9k9l1m9k83s*y1m9k83=Iy1m9k9r83-K5y1m9k83-Ty1m9k83=by83-mYy83-ZSy1m9k9o1o83*Jytqu1m9pl1m9pm1q8");
    string_constant_234 = 
	    STATIC_STRING("3-EMy1s1m9k83*Jy1m9k9l1m9k83s*y1m9k83=Iy1m9k83=by83-mYy83mLy83-s+y2o83*Jyq0rs9m1m9no1m9pl1o83-EMy1s1m9k83*Jy1m9k9l1m9k83s*y1m9k8");
    string_constant_235 = 
	    STATIC_STRING("3=Iy1m9k83=by83-mYy83-ZSy1m9k9o1o83*Jyq0r1m9pl1n83mLy1m83-mZy1m9k83-Pyl1m83-mZy1m9k83*Yy1n83-mZy1m1m9k83*Yy1m9k83-JIy83ivy1m83-m");
    string_constant_236 = 
	    STATIC_STRING("Zy1m9k83Bvy1n83-mZy1m1m9k83Bvy1m9k83-JIy836ny1n83-mZy1m1m9k83Bvy1m9k83pJy83voy1n83-ZSy1m1m9k83*Yy1m9k83-Pyl1n83-ZSy1m1m9k83Bvy1m");
    string_constant_237 = 
	    STATIC_STRING("9k83-Pyl1m83-mXy83-Gy1m83-mXy1m9k835ny1m83jPy834oy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qmenu);
    push_optimized_constant(Qprohibit_nothing);
    push_optimized_constant(Qfix_tailing_associative_list);
    push_optimized_constant(Qnothing);
    push_optimized_constant(Qfix_associative_list);
    push_optimized_constant(Qdont_include_workspace);
    push_optimized_constant(Qthe);
    add_grammar_rules_function(regenerate_optimized_constant(list(15,
	    string_constant_223,string_constant_224,string_constant_225,
	    string_constant_226,string_constant_227,string_constant_228,
	    string_constant_229,string_constant_230,string_constant_231,
	    string_constant_232,string_constant_233,string_constant_234,
	    string_constant_235,string_constant_236,string_constant_237)));
    Qmove_object = STATIC_SYMBOL("MOVE-OBJECT",AB_package);
    Qmove_objects_beyond_workspace_margin = 
	    STATIC_SYMBOL("MOVE-OBJECTS-BEYOND-WORKSPACE-MARGIN",AB_package);
    Qmove_connection = STATIC_SYMBOL("MOVE-CONNECTION",AB_package);
    Qmove_workspace = STATIC_SYMBOL("MOVE-WORKSPACE",AB_package);
    Qmove_workspaces_beyond_window_margin = 
	    STATIC_SYMBOL("MOVE-WORKSPACES-BEYOND-WINDOW-MARGIN",AB_package);
    Qshow_workspace = STATIC_SYMBOL("SHOW-WORKSPACE",AB_package);
    Qscale_workspace = STATIC_SYMBOL("SCALE-WORKSPACE",AB_package);
    Qclick_to_edit = STATIC_SYMBOL("CLICK-TO-EDIT",AB_package);
    Qfull_editor = STATIC_SYMBOL("FULL-EDITOR",AB_package);
    Qoption_buttons_for_edit_in_place = 
	    STATIC_SYMBOL("OPTION-BUTTONS-FOR-EDIT-IN-PLACE",AB_package);
    Qmenus_for_edit_in_place = STATIC_SYMBOL("MENUS-FOR-EDIT-IN-PLACE",
	    AB_package);
    Qdo_not_clear_text_for_edit_in_place = 
	    STATIC_SYMBOL("DO-NOT-CLEAR-TEXT-FOR-EDIT-IN-PLACE",AB_package);
    Qallow_selection_of_outside_text_from_editor = 
	    STATIC_SYMBOL("ALLOW-SELECTION-OF-OUTSIDE-TEXT-FROM-EDITOR",
	    AB_package);
    Qallow_selection_of_text = STATIC_SYMBOL("ALLOW-SELECTION-OF-TEXT",
	    AB_package);
    Qselect_area = STATIC_SYMBOL("SELECT-AREA",AB_package);
    Qselect_object = STATIC_SYMBOL("SELECT-OBJECT",AB_package);
    list_constant_113 = STATIC_LIST((SI_Long)16L,Qmove_object,
	    Qmove_objects_beyond_workspace_margin,Qmove_connection,
	    Qmove_workspace,Qmove_workspaces_beyond_window_margin,
	    Qshow_workspace,Qscale_workspace,Qclick_to_edit,Qfull_editor,
	    Qoption_buttons_for_edit_in_place,Qmenus_for_edit_in_place,
	    Qdo_not_clear_text_for_edit_in_place,
	    Qallow_selection_of_outside_text_from_editor,
	    Qallow_selection_of_text,Qselect_area,Qselect_object);
    if (Non_menu_choices == UNBOUND)
	Non_menu_choices = list_constant_113;
    string_constant_238 = 
	    STATIC_STRING("13Cy1m83-gvy1m9k83-fmy1m83-gvy1m9k83-fny1m83-gvy1m9k83-fky1m83-gvy1m9k83W3y1m83-gvy1m9k83-fuy1m83-gvy1m9k9l1m83-gvy1m9k83-nYy1m8");
    string_constant_239 = 
	    STATIC_STRING("3-gvy1m9k83-Mhy1m83-gvy1m9k83-VBy1m83-gvy1m9k83-hty1m83-gvy1m9k83-ePy1m83-gvy1m9k83-Rhy1m83-gvy1m9k83-JYy1m83-gvy1m9k83-JZy1m83-");
    string_constant_240 = STATIC_STRING("gvy1m9k9m1m83-gvy1m9k83-o+y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qshow_workspace);
    push_optimized_constant(Qselect_area);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_3(string_constant_238,
	    string_constant_239,string_constant_240)));
    SET_SYMBOL_FUNCTION(Qprohibit_nothing,STATIC_FUNCTION(prohibit_nothing,
	    NIL,FALSE,1,1));
    set_grammar_transform_can_return_bad_phrase_p(Qprohibit_nothing);
    Qrestrictable_classes = STATIC_SYMBOL("RESTRICTABLE-CLASSES",AB_package);
    Qrestrictable_class = STATIC_SYMBOL("RESTRICTABLE-CLASS",AB_package);
    add_grammar_rules_for_list(5,Qrestrictable_classes,Qrestrictable_class,
	    Qcm,Qab_or,Qnil);
    Qattribute_names = STATIC_SYMBOL("ATTRIBUTE-NAMES",AB_package);
    Qsystem_or_user_defined_attribute_name = 
	    STATIC_SYMBOL("SYSTEM-OR-USER-DEFINED-ATTRIBUTE-NAME",AB_package);
    add_grammar_rules_for_list(5,Qattribute_names,
	    Qsystem_or_user_defined_attribute_name,Qcm,Qnil,Qnil);
    Qconvert_class_qualified_list_to_keyword_symbol = 
	    STATIC_SYMBOL("CONVERT-CLASS-QUALIFIED-LIST-TO-KEYWORD-SYMBOL",
	    AB_package);
    string_constant_241 = 
	    STATIC_STRING("1n1m836Iy83FJy1m836Iy83*my1o836Iy1n83-Gy1m9k83=my83*my1n830=yln9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qconvert_class_qualified_list_to_keyword_symbol);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_241));
    string_constant_242 = 
	    STATIC_STRING("1n1m83nay83FJy1m83nay83*my1n83nay1n83-Gy1m9k83=my83*my1n830=yln");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_242));
    Quser_attribute_names = STATIC_SYMBOL("USER-ATTRIBUTE-NAMES",AB_package);
    Quser_attribute_name = STATIC_SYMBOL("USER-ATTRIBUTE-NAME",AB_package);
    add_grammar_rules_for_list(5,Quser_attribute_names,
	    Quser_attribute_name,Qcm,Qnil,Qnil);
    string_constant_243 = 
	    STATIC_STRING("1m1m83dey83*my1o83dey1n83-Gy1m9k83=my83*my1n830=yln9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qconvert_class_qualified_list_to_keyword_symbol);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_243));
    Qattribute_names_or = STATIC_SYMBOL("ATTRIBUTE-NAMES-OR",AB_package);
    add_grammar_rules_for_list(5,Qattribute_names_or,
	    Qsystem_or_user_defined_attribute_name,Qcm,Qab_or,Qnil);
    string_constant_244 = STATIC_STRING("1l1m83FJy83-6y");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_244));
    Qworkspace_menu_choices = STATIC_SYMBOL("WORKSPACE-MENU-CHOICES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qworkspace_menu_choices,Workspace_menu_choices);
    Qworkspace_menu_choice = STATIC_SYMBOL("WORKSPACE-MENU-CHOICE",AB_package);
    add_grammar_rules_for_list(5,Qworkspace_menu_choices,
	    Qworkspace_menu_choice,Qcm,Qnil,Qnil);
    Qitem_menu_choices = STATIC_SYMBOL("ITEM-MENU-CHOICES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qitem_menu_choices,Item_menu_choices);
    Qitem_menu_choice = STATIC_SYMBOL("ITEM-MENU-CHOICE",AB_package);
    add_grammar_rules_for_list(5,Qitem_menu_choices,Qitem_menu_choice,Qcm,
	    Qnil,Qnil);
    Qnon_menu_choices = STATIC_SYMBOL("NON-MENU-CHOICES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qnon_menu_choices,Non_menu_choices);
    Qnon_menu_choice = STATIC_SYMBOL("NON-MENU-CHOICE",AB_package);
    add_grammar_rules_for_list(5,Qnon_menu_choices,Qnon_menu_choice,Qcm,
	    Qnil,Qnil);
    Qtable_menu_choices = STATIC_SYMBOL("TABLE-MENU-CHOICES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtable_menu_choices,Table_menu_choices);
    Qtable_menu_choice = STATIC_SYMBOL("TABLE-MENU-CHOICE",AB_package);
    add_grammar_rules_for_list(5,Qtable_menu_choices,Qtable_menu_choice,
	    Qcm,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qcons_car_cddr,STATIC_FUNCTION(cons_car_cddr,NIL,
	    FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qfix_mode_restriction,
	    STATIC_FUNCTION(fix_mode_restriction,NIL,FALSE,1,1));
    Qworkspace = STATIC_SYMBOL("WORKSPACE",AB_package);
    SET_SYMBOL_FUNCTION(Qdont_include_workspace,
	    STATIC_FUNCTION(dont_include_workspace,NIL,FALSE,1,1));
    set_grammar_transform_can_return_bad_phrase_p(Qdont_include_workspace);
    SET_SYMBOL_FUNCTION(Qfix_associative_list,
	    STATIC_FUNCTION(fix_associative_list,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qfix_tailing_associative_list,
	    STATIC_FUNCTION(fix_tailing_associative_list,NIL,FALSE,2,2));
    Qwrite_object_configuration_from_slot = 
	    STATIC_SYMBOL("WRITE-OBJECT-CONFIGURATION-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_object_configuration_from_slot,
	    STATIC_FUNCTION(write_object_configuration_from_slot,NIL,FALSE,
	    2,2));
    mutate_global_property(Qobject_configuration,
	    SYMBOL_FUNCTION(Qwrite_object_configuration_from_slot),
	    Qslot_value_writer);
    Qreclaim_object_configuration_value = 
	    STATIC_SYMBOL("RECLAIM-OBJECT-CONFIGURATION-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_object_configuration_value,
	    STATIC_FUNCTION(reclaim_object_configuration_value,NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qobject_configuration,
	    SYMBOL_FUNCTION(Qreclaim_object_configuration_value),
	    Qslot_value_reclaimer);
    string_constant_11 = STATIC_STRING(";~%");
    string_constant_12 = STATIC_STRING("none");
    Qconfigure = STATIC_SYMBOL("CONFIGURE",AB_package);
    Quser_interface = STATIC_SYMBOL("USER-INTERFACE",AB_package);
    string_constant_13 = 
	    STATIC_STRING("configure the user interface as follows:~%");
    string_constant_14 = STATIC_STRING("declare");
    string_constant_15 = STATIC_STRING(" ~(~a~a~)");
    string_constant_16 = STATIC_STRING("");
    string_constant_17 = STATIC_STRING("not ");
    string_constant_18 = STATIC_STRING("declare properties");
    string_constant_19 = STATIC_STRING(" of");
    string_constant_20 = STATIC_STRING(" as follows:~%  ");
    string_constant_21 = STATIC_STRING(", ");
    string_constant_22 = STATIC_STRING("set up network access as follows:");
    string_constant_23 = STATIC_STRING("~%    ");
    string_constant_24 = STATIC_STRING(",~%    ");
    string_constant_25 = STATIC_STRING("allow");
    string_constant_26 = STATIC_STRING("prohibit");
    string_constant_27 = STATIC_STRING("prohibit absolutely");
    string_constant_28 = STATIC_STRING("allow precisely");
    string_constant_29 = STATIC_STRING("prohibit precisely");
    string_constant_30 = STATIC_STRING(" ");
    string_constant_31 = STATIC_STRING(" access");
    string_constant_32 = STATIC_STRING(" to ");
    Qany = STATIC_SYMBOL("ANY",AB_package);
    string_constant_33 = STATIC_STRING(" by G2");
    string_constant_34 = STATIC_STRING(" by GSI");
    string_constant_35 = STATIC_STRING(" by Telewindows");
    Qg2_and_gsi = STATIC_SYMBOL("G2-AND-GSI",AB_package);
    string_constant_36 = STATIC_STRING(" by G2 and GSI");
    Qg2_and_telewindows = STATIC_SYMBOL("G2-AND-TELEWINDOWS",AB_package);
    string_constant_37 = STATIC_STRING(" by G2 and Telewindows");
    string_constant_38 = 
	    STATIC_STRING("restrict proprietary items as follows:");
    string_constant_39 = STATIC_STRING("~%  ");
    string_constant_40 = STATIC_STRING(";~%  ");
    Qcomment = STATIC_SYMBOL("COMMENT",AB_package);
    string_constant_41 = STATIC_STRING("comment as follows:");
    string_constant_42 = STATIC_STRING("~%   ");
    string_constant_43 = STATIC_STRING(",~%   ");
    string_constant_44 = STATIC_STRING("~(~a: ~s~)");
    string_constant_45 = STATIC_STRING("~(~Athis ~A~)");
    string_constant_46 = STATIC_STRING("~Aany ");
    string_constant_47 = STATIC_STRING("when in ");
    string_constant_48 = STATIC_STRING("unless in ");
    string_constant_49 = STATIC_STRING("nothing");
    string_constant_50 = STATIC_STRING(" mode:~%  ");
    string_constant_51 = STATIC_STRING("rolling ");
    string_constant_52 = STATIC_STRING("the mouse wheel forward");
    string_constant_53 = STATIC_STRING("the mouse wheel backward");
    string_constant_54 = STATIC_STRING("hovering ");
    string_constant_55 = STATIC_STRING("the mouse");
    string_constant_56 = STATIC_STRING("typing ");
    string_constant_57 = STATIC_STRING("~( ~a ~a~)");
    string_constant_58 = STATIC_STRING(" ~a ");
    string_constant_59 = STATIC_STRING("main menu choices");
    Qglobal_keyboard_command = STATIC_SYMBOL("GLOBAL-KEYBOARD-COMMAND",
	    AB_package);
    string_constant_60 = STATIC_STRING("global keyboard commands");
    string_constant_61 = STATIC_STRING("menu choices for");
    string_constant_62 = STATIC_STRING("non-menu choices for");
    string_constant_63 = STATIC_STRING("selecting any");
    Qdoes = STATIC_SYMBOL("DOES",AB_package);
    Qimplies = STATIC_SYMBOL("IMPLIES",AB_package);
    Qselecting_absolutely = STATIC_SYMBOL("SELECTING-ABSOLUTELY",AB_package);
    Qdoes_absolutely = STATIC_SYMBOL("DOES-ABSOLUTELY",AB_package);
    Qimplies_absolutely = STATIC_SYMBOL("IMPLIES-ABSOLUTELY",AB_package);
    Qvisibility = STATIC_SYMBOL("VISIBILITY",AB_package);
    string_constant_64 = STATIC_STRING("attributes visible for");
    string_constant_65 = STATIC_STRING("table menu choices for any");
    string_constant_66 = STATIC_STRING("table menu choices for the");
    Qconstrain = STATIC_SYMBOL("CONSTRAIN",AB_package);
    Qmoving = STATIC_SYMBOL("MOVING",AB_package);
    string_constant_67 = STATIC_STRING("constrain moving");
    string_constant_68 = STATIC_STRING("this");
    string_constant_69 = STATIC_STRING("any");
    string_constant_70 = 
	    STATIC_STRING(" such that the item aligns on the grid (~d,~d)");
    Qrectangle = STATIC_SYMBOL("RECTANGLE",AB_package);
    string_constant_71 = STATIC_STRING(" to the rectangle (~d,~d,~d,~d)");
    string_constant_72 = STATIC_STRING("over this");
    string_constant_73 = STATIC_STRING("over any");
    string_constant_74 = STATIC_STRING("on this");
    string_constant_75 = STATIC_STRING("on any");
    string_constant_76 = STATIC_STRING(" does nothing");
    string_constant_77 = STATIC_STRING(" implies ");
    string_constant_78 = STATIC_STRING("~( starts ~a as the mouse tracks");
    string_constant_79 = STATIC_STRING(" continuously over");
    string_constant_80 = STATIC_STRING(" over");
    Qclass_qualified_name = STATIC_SYMBOL("CLASS-QUALIFIED-NAME",AB_package);
    string_constant_81 = STATIC_STRING(" of ");
    string_constant_82 = STATIC_STRING(" of any ");
    string_constant_83 = STATIC_STRING("does ");
    string_constant_84 = STATIC_STRING("absolutely does ");
    string_constant_85 = STATIC_STRING("implies ");
    string_constant_86 = STATIC_STRING("absolutely implies ");
    string_constant_87 = STATIC_STRING("include: ");
    string_constant_88 = STATIC_STRING("exclude: ");
    string_constant_89 = STATIC_STRING("include additionally: ");
    string_constant_90 = STATIC_STRING("exclude additionally: ");
    string_constant_91 = STATIC_STRING("exclude absolutely: ");
    Qwrite_name_denotation = STATIC_SYMBOL("WRITE-NAME-DENOTATION",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_name_denotation,
	    STATIC_FUNCTION(write_name_denotation,NIL,FALSE,1,1));
    Qadministrator = STATIC_SYMBOL("ADMINISTRATOR",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qadministrator,Qproprietary);
    Qdelete_from_directory_of_names = 
	    STATIC_SYMBOL("DELETE-FROM-DIRECTORY-OF-NAMES",AB_package);
    Qadd_to_directory_of_names = STATIC_SYMBOL("ADD-TO-DIRECTORY-OF-NAMES",
	    AB_package);
    Qnon_built_in_g2_user_mode = STATIC_SYMBOL("NON-BUILT-IN-G2-USER-MODE",
	    AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qconfigure,Quser_interface);
    Qkb_restrictions = STATIC_SYMBOL("KB-RESTRICTIONS",AB_package);
    Qsystem_table = STATIC_SYMBOL("SYSTEM-TABLE",AB_package);
    list_constant_114 = STATIC_CONS(Qsystem_table,Qnil);
    check_if_superior_classes_are_defined(Qkb_restrictions,list_constant_114);
    string_constant_245 = STATIC_STRING("1l1l83ey");
    string_constant_246 = 
	    STATIC_STRING("1s4z8r830jy830jy839Dy839Dy01l1m83Fjy1p83ALy1l833ey1o834uy1l83Ry836ny830Fy1o83Fry1l839Dy1n83Ufy83TSy83S8y83Bvy1o83Fry1l83Ry1l835X");
    string_constant_247 = 
	    STATIC_STRING("y836ny001o1l8l1l83Ey1m8p830jy1m83Dy53=EyObject-configuration is aliased to item-configuration. ~\nThe value is a list of ( <I>con");
    string_constant_248 = 
	    STATIC_STRING("figuration-expression</I> * ), writable = true. ~\nWill we read and write the individual configuration expressions as text\?000004");
    string_constant_249 = 
	    STATIC_STRING("z8r83Ufy83Ufy839Dy839Dy00001m1l8l1m8p83Uey000004z8r83Qdy83Qdy839Dy839Dy00001m1l8l1m8p83Qcy000004z8r83S8y83S8y839Dy839Dy00001m1l8");
    string_constant_250 = 
	    STATIC_STRING("l1m8p83CBy000004z8r83Z=y83Z=y839Dy839Dy00001l1l8l000004z8r83Gwy83Gwy839Dy839Dy00001o1l8l1l83Fy1l83Hy1m8p83YNy000004z8r83a7y83a7y");
    string_constant_251 = 
	    STATIC_STRING("839Dy839Dy08k001n1l8l1l83Hy1m8p83F0y000004z8r83Fly83Fly839Dy839Dy00001m1l8l1l83Cy00000");
    string_constant_252 = 
	    STATIC_STRING("1u8q1n839Dy1l83-sy83ey1m830jy1l1m83Fjy1p83ALy1l833ey1o834uy1l83Ry836ny830Fy1o83Fry1l839Dy1n83Ufy83TSy83S8y83Bvy1o83Fry1l83Ry1l83");
    string_constant_253 = 
	    STATIC_STRING("5Xy836ny1o83Ufy08l1m8p83Uey1o83Qdy08l1m8p83Qcy1o83S8y08l1m8p83CBy1n83Z=y08l1q83Gwy08l83Fy83Hy1m8p83YNy1p83a7y8k8l83Hy1m8p83F0y1o");
    string_constant_254 = STATIC_STRING("83Fly08l83Cy");
    temp = regenerate_optimized_constant(string_constant_245);
    temp_1 = regenerate_optimized_constant(list(6,string_constant_246,
	    string_constant_247,string_constant_248,string_constant_249,
	    string_constant_250,string_constant_251));
    add_class_to_environment(9,Qkb_restrictions,list_constant_114,Nil,temp,
	    Nil,temp_1,list_constant_114,
	    regenerate_optimized_constant(LIST_3(string_constant_252,
	    string_constant_253,string_constant_254)),Nil);
    Qkb_configuration = STATIC_SYMBOL("KB-CONFIGURATION",AB_package);
    list_constant_115 = STATIC_CONS(Qkb_restrictions,Qnil);
    check_if_superior_classes_are_defined(Qkb_configuration,list_constant_115);
    string_constant_255 = STATIC_STRING("0");
    string_constant_256 = STATIC_STRING("1m8q1n83-1Wy1l839Dy83ey");
    temp = regenerate_optimized_constant(string_constant_245);
    temp_1 = regenerate_optimized_constant(string_constant_255);
    add_class_to_environment(9,Qkb_configuration,list_constant_115,Nil,
	    temp,Nil,temp_1,list_constant_115,
	    regenerate_optimized_constant(string_constant_256),Nil);
    Qfilters = STATIC_SYMBOL("FILTERS",AB_package);
    Ksystem_frame = STATIC_SYMBOL("SYSTEM-FRAME",Pkeyword);
    record_system_variable(Qkb_configuration,Qfilters,Ksystem_frame,Qnil,
	    Qnil,Qnil,Qt);
    list_constant_116 = STATIC_LIST((SI_Long)3L,Kfuncall,Qsymbol_value,
	    Qkb_configuration);
    record_system_variable(Qkb_restrictions,Qfilters,list_constant_116,
	    Qnil,Qnil,Qnil,Qt);
    Qglobal_keyboard_command_user_restrictions = 
	    STATIC_SYMBOL("GLOBAL-KEYBOARD-COMMAND-USER-RESTRICTIONS",
	    AB_package);
    Qmain_menu_user_restrictions = 
	    STATIC_SYMBOL("MAIN-MENU-USER-RESTRICTIONS",AB_package);
    Qsubstitute_class_and_kb_flags = 
	    STATIC_SYMBOL("SUBSTITUTE-CLASS-AND-KB-FLAGS",AB_package);
    mutate_global_property(Qkb_restrictions,CONS(Qkb_configuration,
	    Kb_format_revision_for_kb_restrictions_reclassification),
	    Qsubstitute_class_and_kb_flags);
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qnote_status_of_simulated_product_authorization = 
	    STATIC_SYMBOL("NOTE-STATUS-OF-SIMULATED-PRODUCT-AUTHORIZATION",
	    AB_package);
    Qinitialize_after_reading_for_kb_configuration = 
	    STATIC_SYMBOL("INITIALIZE-AFTER-READING-FOR-KB-CONFIGURATION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_after_reading_for_kb_configuration,
	    STATIC_FUNCTION(initialize_after_reading_for_kb_configuration,
	    NIL,FALSE,1,1));
    Qinitialize_after_reading = STATIC_SYMBOL("INITIALIZE-AFTER-READING",
	    AB_package);
    temp_2 = SYMBOL_FUNCTION(Qinitialize_after_reading_for_kb_configuration);
    set_get(Qkb_configuration,Qinitialize_after_reading,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize_after_reading),
	    Qclasses_which_define);
    temp_2 = CONS(Qkb_configuration,temp);
    mutate_global_property(Qinitialize_after_reading,temp_2,
	    Qclasses_which_define);
    Qauthorized_optional_modules_for_this_machine = 
	    STATIC_SYMBOL("AUTHORIZED-OPTIONAL-MODULES-FOR-THIS-MACHINE",
	    AB_package);
    Qauthorized_optional_modules = 
	    STATIC_SYMBOL("AUTHORIZED-OPTIONAL-MODULES",AB_package);
    alias_slot_name(3,Qauthorized_optional_modules_for_this_machine,
	    Qauthorized_optional_modules,Qkb_restrictions);
    Qkeyboard_command_restrictions = 
	    STATIC_SYMBOL("KEYBOARD-COMMAND-RESTRICTIONS",AB_package);
    alias_slot_name(3,Qglobal_keyboard_command_user_restrictions,
	    Qkeyboard_command_restrictions,Qnil);
    Qinitial_g2_user_mode_for_this_kb = 
	    STATIC_SYMBOL("INITIAL-G2-USER-MODE-FOR-THIS-KB",AB_package);
    Qinstall_system_table_for_kb_configuration = 
	    STATIC_SYMBOL("INSTALL-SYSTEM-TABLE-FOR-KB-CONFIGURATION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinstall_system_table_for_kb_configuration,
	    STATIC_FUNCTION(install_system_table_for_kb_configuration,NIL,
	    FALSE,1,1));
    Qinstall_system_table = STATIC_SYMBOL("INSTALL-SYSTEM-TABLE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qinstall_system_table_for_kb_configuration);
    set_get(Qkb_configuration,Qinstall_system_table,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinstall_system_table),
	    Qclasses_which_define);
    temp_2 = CONS(Qkb_configuration,temp);
    mutate_global_property(Qinstall_system_table,temp_2,Qclasses_which_define);
    Qdeinstall_system_table_for_kb_configuration = 
	    STATIC_SYMBOL("DEINSTALL-SYSTEM-TABLE-FOR-KB-CONFIGURATION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdeinstall_system_table_for_kb_configuration,
	    STATIC_FUNCTION(deinstall_system_table_for_kb_configuration,
	    NIL,FALSE,1,1));
    Qdeinstall_system_table = STATIC_SYMBOL("DEINSTALL-SYSTEM-TABLE",
	    AB_package);
    temp_2 = SYMBOL_FUNCTION(Qdeinstall_system_table_for_kb_configuration);
    set_get(Qkb_configuration,Qdeinstall_system_table,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeinstall_system_table),
	    Qclasses_which_define);
    temp_2 = CONS(Qkb_configuration,temp);
    mutate_global_property(Qdeinstall_system_table,temp_2,
	    Qclasses_which_define);
    Qcompile_main_menu_restrictions_for_slot = 
	    STATIC_SYMBOL("COMPILE-MAIN-MENU-RESTRICTIONS-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_main_menu_restrictions_for_slot,
	    STATIC_FUNCTION(compile_main_menu_restrictions_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qmain_menu_restrictions,
	    SYMBOL_FUNCTION(Qcompile_main_menu_restrictions_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qmain_menu_restrictions,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_global_keyboard_command_restrictions_for_slot = 
	    STATIC_SYMBOL("COMPILE-GLOBAL-KEYBOARD-COMMAND-RESTRICTIONS-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_global_keyboard_command_restrictions_for_slot,
	    STATIC_FUNCTION(compile_global_keyboard_command_restrictions_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qglobal_keyboard_command_restrictions,
	    SYMBOL_FUNCTION(Qcompile_global_keyboard_command_restrictions_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qglobal_keyboard_command_restrictions,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qput_main_menu_user_restrictions = 
	    STATIC_SYMBOL("PUT-MAIN-MENU-USER-RESTRICTIONS",AB_package);
    SET_SYMBOL_FUNCTION(Qput_main_menu_user_restrictions,
	    STATIC_FUNCTION(put_main_menu_user_restrictions,NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qmain_menu_user_restrictions,
	    SYMBOL_FUNCTION(Qput_main_menu_user_restrictions),Qslot_putter);
    Qput_global_keyboard_command_user_restrictions = 
	    STATIC_SYMBOL("PUT-GLOBAL-KEYBOARD-COMMAND-USER-RESTRICTIONS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_global_keyboard_command_user_restrictions,
	    STATIC_FUNCTION(put_global_keyboard_command_user_restrictions,
	    NIL,FALSE,3,3));
    mutate_global_property(Qglobal_keyboard_command_user_restrictions,
	    SYMBOL_FUNCTION(Qput_global_keyboard_command_user_restrictions),
	    Qslot_putter);
    Qcompile_user_restrictions_for_slot = 
	    STATIC_SYMBOL("COMPILE-USER-RESTRICTIONS-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_user_restrictions_for_slot,
	    STATIC_FUNCTION(compile_user_restrictions_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Quser_restrictions,
	    SYMBOL_FUNCTION(Qcompile_user_restrictions_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Quser_restrictions,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_92 = 
	    STATIC_STRING("You may not restrict administrator mode.");
    string_constant_93 = 
	    STATIC_STRING("You may not restrict proprietary mode here.");
    string_constant_94 = 
	    STATIC_STRING("You may not restrict proprietary mode using UNLESS.");
    Qput_user_restrictions = STATIC_SYMBOL("PUT-USER-RESTRICTIONS",AB_package);
    SET_SYMBOL_FUNCTION(Qput_user_restrictions,
	    STATIC_FUNCTION(put_user_restrictions,NIL,FALSE,3,3));
    mutate_global_property(Quser_restrictions,
	    SYMBOL_FUNCTION(Qput_user_restrictions),Qslot_putter);
    Qclass_restrictions = STATIC_SYMBOL("CLASS-RESTRICTIONS",AB_package);
    Qput_class_restrictions = STATIC_SYMBOL("PUT-CLASS-RESTRICTIONS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_class_restrictions,
	    STATIC_FUNCTION(put_class_restrictions,NIL,FALSE,3,3));
    mutate_global_property(Qclass_restrictions,
	    SYMBOL_FUNCTION(Qput_class_restrictions),Qslot_putter);
    Qchanging_mode = STATIC_SYMBOL("CHANGING-MODE",AB_package);
    Qput_initial_g2_user_mode_for_this_kb = 
	    STATIC_SYMBOL("PUT-INITIAL-G2-USER-MODE-FOR-THIS-KB",AB_package);
    SET_SYMBOL_FUNCTION(Qput_initial_g2_user_mode_for_this_kb,
	    STATIC_FUNCTION(put_initial_g2_user_mode_for_this_kb,NIL,FALSE,
	    3,3));
    mutate_global_property(Qinitial_g2_user_mode_for_this_kb,
	    SYMBOL_FUNCTION(Qput_initial_g2_user_mode_for_this_kb),
	    Qslot_putter);
    Qwrite_main_menu_restrictions_from_slot = 
	    STATIC_SYMBOL("WRITE-MAIN-MENU-RESTRICTIONS-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_main_menu_restrictions_from_slot,
	    STATIC_FUNCTION(write_main_menu_restrictions_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qmain_menu_restrictions,
	    SYMBOL_FUNCTION(Qwrite_main_menu_restrictions_from_slot),
	    Qslot_value_writer);
    Qwrite_global_keyboard_command_restrictions_from_slot = 
	    STATIC_SYMBOL("WRITE-GLOBAL-KEYBOARD-COMMAND-RESTRICTIONS-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_global_keyboard_command_restrictions_from_slot,
	    STATIC_FUNCTION(write_global_keyboard_command_restrictions_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qglobal_keyboard_command_restrictions,
	    SYMBOL_FUNCTION(Qwrite_global_keyboard_command_restrictions_from_slot),
	    Qslot_value_writer);
    Qwrite_user_restrictions_from_slot = 
	    STATIC_SYMBOL("WRITE-USER-RESTRICTIONS-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_user_restrictions_from_slot,
	    STATIC_FUNCTION(write_user_restrictions_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Quser_restrictions,
	    SYMBOL_FUNCTION(Qwrite_user_restrictions_from_slot),
	    Qslot_value_writer);
    Qwrite_class_restrictions_from_slot = 
	    STATIC_SYMBOL("WRITE-CLASS-RESTRICTIONS-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_class_restrictions_from_slot,
	    STATIC_FUNCTION(write_class_restrictions_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qclass_restrictions,
	    SYMBOL_FUNCTION(Qwrite_class_restrictions_from_slot),
	    Qslot_value_writer);
    Qg2_set_movement_limits = STATIC_SYMBOL("G2-SET-MOVEMENT-LIMITS",
	    AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_set_movement_limits,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_95 = 
	    STATIC_STRING("The type of clause must be the symbol WHEN or UNLESS.");
    string_constant_96 = 
	    STATIC_STRING("Proprietary restrictions require a clause type of WHEN.");
    list_constant_5 = STATIC_LIST((SI_Long)4L,Qconstrain,Qrectangle,Qitem,
	    Qstar);
    SET_SYMBOL_FUNCTION(Qg2_set_movement_limits,
	    STATIC_FUNCTION(g2_set_movement_limits,NIL,FALSE,7,7));
    Qg2_get_movement_limits = STATIC_SYMBOL("G2-GET-MOVEMENT-LIMITS",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_get_movement_limits,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_get_movement_limits,
	    STATIC_FUNCTION(g2_get_movement_limits,NIL,FALSE,3,3));
    Qg2_clear_movement_limits = STATIC_SYMBOL("G2-CLEAR-MOVEMENT-LIMITS",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_clear_movement_limits,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_clear_movement_limits,
	    STATIC_FUNCTION(g2_clear_movement_limits,NIL,FALSE,3,3));
    Qg2_set_movement_grid = STATIC_SYMBOL("G2-SET-MOVEMENT-GRID",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_set_movement_grid,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    list_constant_117 = STATIC_LIST((SI_Long)2L,Qitem,Qstar);
    list_constant_6 = STATIC_LIST_STAR((SI_Long)3L,Qconstrain,Qmoving,
	    list_constant_117);
    SET_SYMBOL_FUNCTION(Qg2_set_movement_grid,
	    STATIC_FUNCTION(g2_set_movement_grid,NIL,FALSE,5,5));
    Qg2_get_movement_grid = STATIC_SYMBOL("G2-GET-MOVEMENT-GRID",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_movement_grid,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_movement_grid,
	    STATIC_FUNCTION(g2_get_movement_grid,NIL,FALSE,3,3));
    Qg2_clear_movement_grid = STATIC_SYMBOL("G2-CLEAR-MOVEMENT-GRID",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_clear_movement_grid,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_clear_movement_grid,
	    STATIC_FUNCTION(g2_clear_movement_grid,NIL,FALSE,3,3));
    Qframe_status_and_notes = STATIC_SYMBOL("FRAME-STATUS-AND-NOTES",
	    AB_package);
    Qstack_change = STATIC_SYMBOL("STACK-CHANGE",AB_package);
    Qitem_configuration = STATIC_SYMBOL("ITEM-CONFIGURATION",AB_package);
    Qput_object_configuration = STATIC_SYMBOL("PUT-OBJECT-CONFIGURATION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_object_configuration,
	    STATIC_FUNCTION(put_object_configuration,NIL,FALSE,3,3));
    mutate_global_property(Qobject_configuration,
	    SYMBOL_FUNCTION(Qput_object_configuration),Qslot_putter);
    Qinstance_configuration = STATIC_SYMBOL("INSTANCE-CONFIGURATION",
	    AB_package);
    Qput_instance_configuration = 
	    STATIC_SYMBOL("PUT-INSTANCE-CONFIGURATION",AB_package);
    SET_SYMBOL_FUNCTION(Qput_instance_configuration,
	    STATIC_FUNCTION(put_instance_configuration,NIL,FALSE,3,3));
    mutate_global_property(Qinstance_configuration,
	    SYMBOL_FUNCTION(Qput_instance_configuration),Qslot_putter);
    Qreclaim_instance_configuration_value = 
	    STATIC_SYMBOL("RECLAIM-INSTANCE-CONFIGURATION-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_instance_configuration_value,
	    STATIC_FUNCTION(reclaim_instance_configuration_value,NIL,FALSE,
	    2,2));
    mutate_global_property(Qinstance_configuration,
	    SYMBOL_FUNCTION(Qreclaim_instance_configuration_value),
	    Qslot_value_reclaimer);
    Qstable_hierarchy = STATIC_SYMBOL("STABLE-HIERARCHY",AB_package);
    Qinlineable = STATIC_SYMBOL("INLINEABLE",AB_package);
    Qstable_for_dependent_compilations = 
	    STATIC_SYMBOL("STABLE-FOR-DEPENDENT-COMPILATIONS",AB_package);
    Qindependent_for_all_compilations = 
	    STATIC_SYMBOL("INDEPENDENT-FOR-ALL-COMPILATIONS",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qhandle_dependent_or_stable_status_change_for_item_for_filters = 
	    STATIC_SYMBOL("HANDLE-DEPENDENT-OR-STABLE-STATUS-CHANGE-FOR-ITEM-FOR-FILTERS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_dependent_or_stable_status_change_for_item_for_filters,
	    STATIC_FUNCTION(handle_dependent_or_stable_status_change_for_item_for_filters,
	    NIL,FALSE,2,2));
    Qframe_style = STATIC_SYMBOL("FRAME-STYLE",AB_package);
    Qput_frame_style = STATIC_SYMBOL("PUT-FRAME-STYLE",AB_package);
    SET_SYMBOL_FUNCTION(Qput_frame_style,STATIC_FUNCTION(put_frame_style,
	    NIL,FALSE,3,3));
    mutate_global_property(Qframe_style,SYMBOL_FUNCTION(Qput_frame_style),
	    Qslot_putter);
    Qcompile_object_configuration_for_slot = 
	    STATIC_SYMBOL("COMPILE-OBJECT-CONFIGURATION-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_object_configuration_for_slot,
	    STATIC_FUNCTION(compile_object_configuration_for_slot,NIL,TRUE,
	    3,6));
    mutate_global_property(Qobject_configuration,
	    SYMBOL_FUNCTION(Qcompile_object_configuration_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qobject_configuration,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_97 = 
	    STATIC_STRING("The network access type `connect\' is only valid in the KB-CONFIGURATION system table.");
    list_constant_119 = STATIC_LIST((SI_Long)2L,Quser_restrictions,
	    Qitem_configuration);
    list_constant_120 = STATIC_LIST((SI_Long)2L,Qclass_restrictions,
	    Qinstance_configuration);
    Qdescribe_restrictions = STATIC_SYMBOL("DESCRIBE-RESTRICTIONS",AB_package);
    list_constant_121 = STATIC_LIST((SI_Long)2L,Qdescribe_restrictions,
	    Qdescribe_configuration);
    list_constant_118 = STATIC_CONS(Qkb_configuration,Qnil);
    list_constant_122 = STATIC_CONS(Qkb_restrictions,list_constant_118);
    Qsuperior_class = STATIC_SYMBOL("SUPERIOR-CLASS",AB_package);
    Qdirect_superior_classes = STATIC_SYMBOL("DIRECT-SUPERIOR-CLASSES",
	    AB_package);
    list_constant_123 = STATIC_LIST((SI_Long)2L,Qsuperior_class,
	    Qdirect_superior_classes);
    Qattributes_specific_to_class = 
	    STATIC_SYMBOL("ATTRIBUTES-SPECIFIC-TO-CLASS",AB_package);
    Qclass_specific_attributes = STATIC_SYMBOL("CLASS-SPECIFIC-ATTRIBUTES",
	    AB_package);
    list_constant_124 = STATIC_LIST((SI_Long)2L,
	    Qattributes_specific_to_class,Qclass_specific_attributes);
    Qdefault_settings = STATIC_SYMBOL("DEFAULT-SETTINGS",AB_package);
    Qattribute_initializations = STATIC_SYMBOL("ATTRIBUTE-INITIALIZATIONS",
	    AB_package);
    list_constant_125 = STATIC_LIST((SI_Long)2L,Qdefault_settings,
	    Qattribute_initializations);
    list_constant_126 = STATIC_LIST((SI_Long)7L,list_constant_119,
	    list_constant_120,list_constant_121,list_constant_122,
	    list_constant_123,list_constant_124,list_constant_125);
    Things_to_rename_in_restrictions = list_constant_126;
    Qconnection = STATIC_SYMBOL("CONNECTION",AB_package);
    if (Superior_frame_for_restrictions_frame_qm == UNBOUND)
	Superior_frame_for_restrictions_frame_qm = Nil;
    if (Superior_frame_for_restrictions_superior_qm == UNBOUND)
	Superior_frame_for_restrictions_superior_qm = Nil;
    if (G2_identification_for_write_locks == UNBOUND)
	G2_identification_for_write_locks = Nil;
    Qgensym_string = STATIC_SYMBOL("GENSYM-STRING",AB_package);
    string_constant_98 = STATIC_STRING("~A:~A:~A");
    string_constant_99 = STATIC_STRING("TCPIP");
    string_constant_100 = STATIC_STRING(" [");
    string_constant_101 = STATIC_STRING("-");
    string_constant_102 = STATIC_STRING(":");
    string_constant_103 = STATIC_STRING("] ");
    string_constant_104 = STATIC_STRING(" (~A)~%");
    if (Restrict_edits_to_modules_having_read_only_files_p == UNBOUND)
	Restrict_edits_to_modules_having_read_only_files_p = Nil;
    Qmodule_is_explictly_editable_p = 
	    STATIC_SYMBOL("MODULE-IS-EXPLICTLY-EDITABLE-P",AB_package);
    Kb_specific_property_names = CONS(Qmodule_is_explictly_editable_p,
	    Kb_specific_property_names);
    Qdo_not_carry_global_property_value_into_kbs_qm = 
	    STATIC_SYMBOL("DO-NOT-CARRY-GLOBAL-PROPERTY-VALUE-INTO-KBS\?",
	    AB_package);
    mutate_global_property(Qmodule_is_explictly_editable_p,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Module_is_explictly_editable_p_kbprop = Qmodule_is_explictly_editable_p;
    Qitem_is_explicitly_editable = 
	    STATIC_SYMBOL("ITEM-IS-EXPLICITLY-EDITABLE",AB_package);
    Qsaving_parameters = STATIC_SYMBOL("SAVING-PARAMETERS",AB_package);
    Qunsavable_change_protection = 
	    STATIC_SYMBOL("UNSAVABLE-CHANGE-PROTECTION",AB_package);
    Qdefault_unsavable_change_protection = 
	    STATIC_SYMBOL("DEFAULT-UNSAVABLE-CHANGE-PROTECTION",AB_package);
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qwarn_about_editing_item = STATIC_SYMBOL("WARN-ABOUT-EDITING-ITEM",
	    AB_package);
    Qg2_item_is_editable = STATIC_SYMBOL("G2-ITEM-IS-EDITABLE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_item_is_editable,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_item_is_editable,
	    STATIC_FUNCTION(g2_item_is_editable,NIL,FALSE,1,1));
    string_constant_257 = 
	    STATIC_STRING("(To turn off these warnings, or to allow edits for all items, edit the saving-parameters.)");
    if (See_also_for_warn_about_editing_item == UNBOUND)
	See_also_for_warn_about_editing_item = string_constant_257;
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    string_constant_105 = STATIC_STRING("Cannot edit ~NF, because ~A.  ~A");
    Qedit_item_warning = STATIC_SYMBOL("EDIT-ITEM-WARNING",AB_package);
    Quneditable_item = STATIC_SYMBOL("UNEDITABLE-ITEM",AB_package);
    Qbutton = STATIC_SYMBOL("BUTTON",AB_package);
    array_constant_3 = STATIC_ARRAY(list_constant_96,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)57344L);
    Qok = STATIC_SYMBOL("OK",AB_package);
    array_constant_4 = STATIC_ARRAY(list_constant_96,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)13L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)23L,(SI_Long)57344L);
    Qallow_edits_to = STATIC_SYMBOL("ALLOW-EDITS-TO",AB_package);
    Qcheck_box = STATIC_SYMBOL("CHECK-BOX",AB_package);
    array_constant_5 = STATIC_ARRAY(list_constant_96,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)57344L);
    array_constant_6 = STATIC_ARRAY(list_constant_96,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)9L,(SI_Long)39L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)12L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)13L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)16L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)17L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)18L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)19L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)20L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)22L,(SI_Long)21L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)23L,(SI_Long)57344L);
    array_constant_7 = STATIC_ARRAY(list_constant_96,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)8L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)9L,(SI_Long)39L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)12L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)13L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)16L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)22L,(SI_Long)18L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)23L,(SI_Long)57344L);
    Qmodule = STATIC_SYMBOL("MODULE",AB_package);
    Qt2_continuation_for_warn_about_editing_item = 
	    STATIC_SYMBOL("T2-CONTINUATION-FOR-WARN-ABOUT-EDITING-ITEM",
	    AB_package);
    Qedits_not_allowed_on_item = STATIC_SYMBOL("EDITS-NOT-ALLOWED-ON-ITEM",
	    AB_package);
    Qrecord_block_for_tformat = STATIC_SYMBOL("RECORD-BLOCK-FOR-TFORMAT",
	    AB_package);
    string_constant_106 = 
	    STATIC_STRING("Cannot edit ~NF, because ~A.  ~\n                     See the saving-parameters and the server-parameters.");
    SET_SYMBOL_FUNCTION(Qwarn_about_editing_item,
	    STATIC_FUNCTION(warn_about_editing_item,NIL,FALSE,3,3));
    Qwarn_about_editing_item_callback = 
	    STATIC_SYMBOL("WARN-ABOUT-EDITING-ITEM-CALLBACK",AB_package);
    string_constant_117 = STATIC_STRING("this item");
    list_constant_127 = STATIC_LIST((SI_Long)2L,string_constant_117,Qitem);
    string_constant_258 = STATIC_STRING("this item\'s workspace");
    list_constant_128 = STATIC_LIST((SI_Long)2L,string_constant_258,
	    Qworkspace);
    string_constant_259 = STATIC_STRING("this item\'s module");
    list_constant_129 = STATIC_LIST((SI_Long)2L,string_constant_259,Qmodule);
    list_constant_7 = STATIC_LIST((SI_Long)3L,list_constant_127,
	    list_constant_128,list_constant_129);
    SET_SYMBOL_FUNCTION(Qt2_continuation_for_warn_about_editing_item,
	    STATIC_FUNCTION(t2_continuation_for_warn_about_editing_item,
	    NIL,FALSE,4,4));
    Qtoplevel_workspace = STATIC_SYMBOL("TOPLEVEL-WORKSPACE",AB_package);
    SET_SYMBOL_FUNCTION(Qwarn_about_editing_item_callback,
	    STATIC_FUNCTION(warn_about_editing_item_callback,NIL,FALSE,3,3));
    Qg2_set_item_explicitly_editable = 
	    STATIC_SYMBOL("G2-SET-ITEM-EXPLICITLY-EDITABLE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_set_item_explicitly_editable,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_set_item_explicitly_editable,
	    STATIC_FUNCTION(g2_set_item_explicitly_editable,NIL,FALSE,1,1));
    Qg2_set_item_and_all_its_subblocks_explicitly_editable = 
	    STATIC_SYMBOL("G2-SET-ITEM-AND-ALL-ITS-SUBBLOCKS-EXPLICITLY-EDITABLE",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_set_item_and_all_its_subblocks_explicitly_editable,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_set_item_and_all_its_subblocks_explicitly_editable,
	    STATIC_FUNCTION(g2_set_item_and_all_its_subblocks_explicitly_editable,
	    NIL,FALSE,1,1));
    Qg2_set_all_items_in_module_explicitly_editable = 
	    STATIC_SYMBOL("G2-SET-ALL-ITEMS-IN-MODULE-EXPLICITLY-EDITABLE",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_set_all_items_in_module_explicitly_editable,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_set_all_items_in_module_explicitly_editable,
	    STATIC_FUNCTION(g2_set_all_items_in_module_explicitly_editable,
	    NIL,FALSE,1,1));
    Qreason_module_is_not_editable = 
	    STATIC_SYMBOL("REASON-MODULE-IS-NOT-EDITABLE",AB_package);
    Qunknown = STATIC_SYMBOL("UNKNOWN",AB_package);
    Qmodule_file_is_checked_out_for_writing_by_current_user = 
	    STATIC_SYMBOL("MODULE-FILE-IS-CHECKED-OUT-FOR-WRITING-BY-CURRENT-USER",
	    AB_package);
    Qscc_unedit = STATIC_SYMBOL("SCC-UNEDIT",AB_package);
    string_constant_107 = 
	    STATIC_STRING("the directory of the file for module ~A is not a directory");
    string_constant_108 = 
	    STATIC_STRING("the directory of the file for module ~A is not writable");
    string_constant_109 = STATIC_STRING("the file for module ~A is read only");
    list_constant_8 = STATIC_LIST((SI_Long)2L,Qinclude,Qexclude);
    Qinternal = STATIC_SYMBOL("INTERNAL",AB_package);
    Quser = STATIC_SYMBOL("USER",AB_package);
    Qabsolute = STATIC_SYMBOL("ABSOLUTE",AB_package);
    Qdone = STATIC_SYMBOL("DONE",AB_package);
    Qinterpret_event_via_object_configuration_1 = 
	    STATIC_SYMBOL("INTERPRET-EVENT-VIA-OBJECT-CONFIGURATION-1",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinterpret_event_via_object_configuration_1,
	    STATIC_FUNCTION(interpret_event_via_object_configuration_1,NIL,
	    FALSE,3,3));
    Qprocedure = STATIC_SYMBOL("PROCEDURE",AB_package);
    Qcurrently_active_event_handlers_via_object_configuration_1 = 
	    STATIC_SYMBOL("CURRENTLY-ACTIVE-EVENT-HANDLERS-VIA-OBJECT-CONFIGURATION-1",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcurrently_active_event_handlers_via_object_configuration_1,
	    STATIC_FUNCTION(currently_active_event_handlers_via_object_configuration_1,
	    NIL,FALSE,3,3));
    Qkey_bindings_for_class_description_on_workspace_1 = 
	    STATIC_SYMBOL("KEY-BINDINGS-FOR-CLASS-DESCRIPTION-ON-WORKSPACE-1",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qkey_bindings_for_class_description_on_workspace_1,
	    STATIC_FUNCTION(key_bindings_for_class_description_on_workspace_1,
	    NIL,FALSE,3,3));
    Qcurrent_g2_user_mode_qm = STATIC_SYMBOL("CURRENT-G2-USER-MODE\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_g2_user_mode_qm,
	    Current_g2_user_mode_qm);
    string_constant_110 = STATIC_STRING("User Defined Commands");
    Qkb_workspace = STATIC_SYMBOL("KB-WORKSPACE",AB_package);
    Qoptimizable = STATIC_SYMBOL("OPTIMIZABLE",AB_package);
    Qinvisible_to_unsavable_change_protection = 
	    STATIC_SYMBOL("INVISIBLE-TO-UNSAVABLE-CHANGE-PROTECTION",
	    AB_package);
    if (Disable_subworkspace_connection_posts == UNBOUND)
	Disable_subworkspace_connection_posts = Nil;
    Qsubworkspace_connection_posts = 
	    STATIC_SYMBOL("SUBWORKSPACE-CONNECTION-POSTS",AB_package);
    list_constant_130 = STATIC_CONS(Qstar,Qnil);
    list_constant_9 = STATIC_LIST_STAR((SI_Long)4L,Qconstrain,Qmoving,
	    Qstar,list_constant_130);
    list_constant_131 = STATIC_CONS(Qstar,list_constant_130);
    list_constant_10 = STATIC_LIST_STAR((SI_Long)3L,Qconstrain,Qrectangle,
	    list_constant_131);
    Qpermitted = STATIC_SYMBOL("PERMITTED",AB_package);
    Qprohibited = STATIC_SYMBOL("PROHIBITED",AB_package);
    Qg2_and_telewindows_and_gsi = 
	    STATIC_SYMBOL("G2-AND-TELEWINDOWS-AND-GSI",AB_package);
    list_constant_11 = STATIC_LIST((SI_Long)4L,Qany,
	    Qg2_and_telewindows_and_gsi,Qg2_and_gsi,Qgsi);
    list_constant_12 = STATIC_LIST((SI_Long)5L,Qany,
	    Qg2_and_telewindows_and_gsi,Qg2_and_gsi,Qg2_and_telewindows,Qg2);
    list_constant_13 = STATIC_LIST((SI_Long)4L,Qany,
	    Qg2_and_telewindows_and_gsi,Qg2_and_telewindows,Qtelewindows);
    Qchoice_conflict = STATIC_SYMBOL("CHOICE-CONFLICT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchoice_conflict,Choice_conflict);
    if (Choice_conflict == UNBOUND)
	Choice_conflict = LIST_1(Qchoice_conflict);
    list_constant_14 = STATIC_LIST((SI_Long)3L,Qworkspace_menu,Qselecting,
	    Qselecting_absolutely);
    Qfilter_workspace_menu_restriction = 
	    STATIC_SYMBOL("FILTER-WORKSPACE-MENU-RESTRICTION",AB_package);
    list_constant_15 = STATIC_CONS(Qworkspace_menu,Qnil);
    SET_SYMBOL_FUNCTION(Qfilter_workspace_menu_restriction,
	    STATIC_FUNCTION(filter_workspace_menu_restriction,NIL,FALSE,3,3));
    Qglobal_keyboard = STATIC_SYMBOL("GLOBAL-KEYBOARD",AB_package);
    list_constant_132 = STATIC_CONS(Qworkspace,Qnil);
    list_constant_16 = STATIC_CONS(Qitem,list_constant_132);
    list_constant_17 = STATIC_CONS(Qitem,Qnil);
    Qfilter_menu_restriction_for_kb = 
	    STATIC_SYMBOL("FILTER-MENU-RESTRICTION-FOR-KB",AB_package);
    SET_SYMBOL_FUNCTION(Qfilter_menu_restriction_for_kb,
	    STATIC_FUNCTION(filter_menu_restriction_for_kb,NIL,FALSE,3,3));
    list_constant_18 = STATIC_LIST((SI_Long)4L,Qmain_menu,Qworkspace_menu,
	    Qitem_menu,Qglobal_keyboard);
    Qmake_g2_secure_qm = STATIC_SYMBOL("MAKE-G2-SECURE\?",AB_package);
    Qfile_progress = STATIC_SYMBOL("FILE-PROGRESS",AB_package);
    Qkb_search_state = STATIC_SYMBOL("KB-SEARCH-STATE",AB_package);
    Qproprietary_package = STATIC_SYMBOL("PROPRIETARY-PACKAGE",AB_package);
    Qmodule_this_is_part_of_qm = STATIC_SYMBOL("MODULE-THIS-IS-PART-OF\?",
	    AB_package);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    list_constant_19 = STATIC_CONS(Qvisibility,Qnil);
    Qfilter_visibility_restrictions = 
	    STATIC_SYMBOL("FILTER-VISIBILITY-RESTRICTIONS",AB_package);
    Qis_visible = STATIC_SYMBOL("IS-VISIBLE",AB_package);
    Qis_not_visible = STATIC_SYMBOL("IS-NOT-VISIBLE",AB_package);
    SET_SYMBOL_FUNCTION(Qfilter_visibility_restrictions,
	    STATIC_FUNCTION(filter_visibility_restrictions,NIL,FALSE,3,3));
    Qfilter_attribute_visibility_restrictions = 
	    STATIC_SYMBOL("FILTER-ATTRIBUTE-VISIBILITY-RESTRICTIONS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qfilter_attribute_visibility_restrictions,
	    STATIC_FUNCTION(filter_attribute_visibility_restrictions,NIL,
	    FALSE,3,3));
    Qincludes = STATIC_SYMBOL("INCLUDES",AB_package);
    list_constant_20 = STATIC_CONS(Qtable,Qnil);
    Qfilter_table_restrictions = STATIC_SYMBOL("FILTER-TABLE-RESTRICTIONS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qfilter_table_restrictions,
	    STATIC_FUNCTION(filter_table_restrictions,NIL,FALSE,3,3));
    list_constant_21 = STATIC_CONS(Qnon_menu,Qnil);
    Qfilter_non_menu_restriction = 
	    STATIC_SYMBOL("FILTER-NON-MENU-RESTRICTION",AB_package);
    SET_SYMBOL_FUNCTION(Qfilter_non_menu_restriction,
	    STATIC_FUNCTION(filter_non_menu_restriction,NIL,FALSE,3,3));
    string_constant_111 = STATIC_STRING("Item configuration for ~NF");
    string_constant_112 = STATIC_STRING("Selecting this item");
    string_constant_113 = STATIC_STRING("Menus for this item");
    string_constant_114 = STATIC_STRING("Non-menu choices for this item");
    string_constant_115 = STATIC_STRING("Table menus for this item");
    Qroot = STATIC_SYMBOL("ROOT",AB_package);
    Qdo_not_put_in_attribute_tables_if_null = 
	    STATIC_SYMBOL("DO-NOT-PUT-IN-ATTRIBUTE-TABLES-IF-NULL",AB_package);
    string_constant_116 = STATIC_STRING("Table menus for the");
    string_constant_118 = 
	    STATIC_STRING("There are no table restrictions for the ~a of this item.");
    string_constant_119 = 
	    STATIC_STRING("The attribute ~(~a::~a~) is not visible.");
    string_constant_120 = STATIC_STRING("The attribute ~a is not visible.");
    string_constant_121 = STATIC_STRING("Item configuration on the KB:");
    string_constant_122 = STATIC_STRING("Instance configuration on ~nf:");
    string_constant_123 = STATIC_STRING("Item configuration on ~nf:");
    string_constant_124 = STATIC_STRING("~%");
    Qclass_format = STATIC_SYMBOL("CLASS-FORMAT",AB_package);
    Qborderless_free_text_format = 
	    STATIC_SYMBOL("BORDERLESS-FREE-TEXT-FORMAT",AB_package);
    Qfont_for_descriptions = STATIC_SYMBOL("FONT-FOR-DESCRIPTIONS",AB_package);
    Qattributes_table_format = STATIC_SYMBOL("ATTRIBUTES-TABLE-FORMAT",
	    AB_package);
    Qcontains_proprietary_p_1 = STATIC_SYMBOL("CONTAINS-PROPRIETARY-P-1",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcontains_proprietary_p_1,
	    STATIC_FUNCTION(contains_proprietary_p_1,NIL,FALSE,2,2));
    SET_SYMBOL_VALUE_LOCATION(Qcontains_proprietary_p_1,
	    Contains_proprietary_p_1);
    Contains_proprietary_p_1 = SYMBOL_FUNCTION(Qcontains_proprietary_p_1);
    Qcontains_either_really_transient_or_proprietary_p_1 = 
	    STATIC_SYMBOL("CONTAINS-EITHER-REALLY-TRANSIENT-OR-PROPRIETARY-P-1",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcontains_either_really_transient_or_proprietary_p_1,
	    STATIC_FUNCTION(contains_either_really_transient_or_proprietary_p_1,
	    NIL,FALSE,2,2));
    SET_SYMBOL_VALUE_LOCATION(Qcontains_either_really_transient_or_proprietary_p_1,
	    Contains_either_really_transient_or_proprietary_p_1);
    Contains_either_really_transient_or_proprietary_p_1 = 
	    SYMBOL_FUNCTION(Qcontains_either_really_transient_or_proprietary_p_1);
    Qinfo_for_restrictable_frame_system_operation = 
	    STATIC_SYMBOL("INFO-FOR-RESTRICTABLE-FRAME-SYSTEM-OPERATION",
	    AB_package);
    Info_for_restrictable_frame_system_operation_prop = 
	    Qinfo_for_restrictable_frame_system_operation;
    Qedit_attribute = STATIC_SYMBOL("EDIT-ATTRIBUTE",AB_package);
    Qrestricted_by_these_input_operations_on_slot = 
	    STATIC_SYMBOL("RESTRICTED-BY-THESE-INPUT-OPERATIONS-ON-SLOT",
	    AB_package);
    list_constant_133 = STATIC_LIST((SI_Long)2L,
	    Qrestricted_by_these_input_operations_on_slot,Qedit);
    list_constant_134 = STATIC_CONS(list_constant_133,Qnil);
    mutate_global_property(Qedit_attribute,list_constant_134,
	    Qinfo_for_restrictable_frame_system_operation);
    Qview_attribute = STATIC_SYMBOL("VIEW-ATTRIBUTE",AB_package);
    Qrestricted_if_slot_not_visible = 
	    STATIC_SYMBOL("RESTRICTED-IF-SLOT-NOT-VISIBLE",AB_package);
    list_constant_135 = STATIC_CONS(Qrestricted_if_slot_not_visible,Qnil);
    list_constant_136 = STATIC_CONS(list_constant_135,Qnil);
    mutate_global_property(Qview_attribute,list_constant_136,
	    Qinfo_for_restrictable_frame_system_operation);
    list_constant_22 = STATIC_LIST((SI_Long)2L,Quser_restrictions,
	    Qclass_restrictions);
    Qfree_text = STATIC_SYMBOL("FREE-TEXT",AB_package);
    Qchange_superior = STATIC_SYMBOL("CHANGE-SUPERIOR",AB_package);
    Qrestricted_if_it_contains_proprietary = 
	    STATIC_SYMBOL("RESTRICTED-IF-IT-CONTAINS-PROPRIETARY",AB_package);
    list_constant_137 = STATIC_CONS(Qrestricted_if_it_contains_proprietary,
	    Qnil);
    list_constant_138 = STATIC_CONS(list_constant_137,Qnil);
    mutate_global_property(Qchange_superior,list_constant_138,
	    Qinfo_for_restrictable_frame_system_operation);
    Qclone_block = STATIC_SYMBOL("CLONE-BLOCK",AB_package);
    mutate_global_property(Qclone_block,list_constant_138,
	    Qinfo_for_restrictable_frame_system_operation);
    Qchange_set_of_inferiors = STATIC_SYMBOL("CHANGE-SET-OF-INFERIORS",
	    AB_package);
    Qrestricted_if_it_is_proprietary = 
	    STATIC_SYMBOL("RESTRICTED-IF-IT-IS-PROPRIETARY",AB_package);
    list_constant_139 = STATIC_CONS(Qrestricted_if_it_is_proprietary,Qnil);
    list_constant_140 = STATIC_CONS(list_constant_139,Qnil);
    mutate_global_property(Qchange_set_of_inferiors,list_constant_140,
	    Qinfo_for_restrictable_frame_system_operation);
    Qmake_transient = STATIC_SYMBOL("MAKE-TRANSIENT",AB_package);
    mutate_global_property(Qmake_transient,list_constant_138,
	    Qinfo_for_restrictable_frame_system_operation);
    Qmake_permanent = STATIC_SYMBOL("MAKE-PERMANENT",AB_package);
    Qrestricted_if_it_contains_proprietary_or_when_runtime_contains_never_permanent_transients 
	    = 
	    STATIC_SYMBOL("RESTRICTED-IF-IT-CONTAINS-PROPRIETARY-OR-WHEN-RUNTIME-CONTAINS-NEVER-PERMANENT-TRANSIENTS",
	    AB_package);
    list_constant_141 = 
	    STATIC_CONS(Qrestricted_if_it_contains_proprietary_or_when_runtime_contains_never_permanent_transients,
	    Qnil);
    list_constant_142 = STATIC_CONS(list_constant_141,Qnil);
    mutate_global_property(Qmake_permanent,list_constant_142,
	    Qinfo_for_restrictable_frame_system_operation);
    Qblock_visible_to_inspect = STATIC_SYMBOL("BLOCK-VISIBLE-TO-INSPECT",
	    AB_package);
    Qrestricted_if_all_attributes_are_not_visible = 
	    STATIC_SYMBOL("RESTRICTED-IF-ALL-ATTRIBUTES-ARE-NOT-VISIBLE",
	    AB_package);
    list_constant_143 = 
	    STATIC_CONS(Qrestricted_if_all_attributes_are_not_visible,Qnil);
    list_constant_144 = STATIC_CONS(list_constant_143,Qnil);
    mutate_global_property(Qblock_visible_to_inspect,list_constant_144,
	    Qinfo_for_restrictable_frame_system_operation);
    Qrestricted_by_these_input_operations_on_block = 
	    STATIC_SYMBOL("RESTRICTED-BY-THESE-INPUT-OPERATIONS-ON-BLOCK",
	    AB_package);
    list_constant_145 = STATIC_LIST((SI_Long)2L,
	    Qrestricted_by_these_input_operations_on_block,Qshow_workspace);
    list_constant_146 = STATIC_CONS(list_constant_145,Qnil);
    mutate_global_property(Qshow_workspace,list_constant_146,
	    Qinfo_for_restrictable_frame_system_operation);
    Qsimulated_optional_modules = 
	    STATIC_SYMBOL("SIMULATED-OPTIONAL-MODULES",AB_package);
    Qsimulation_state = STATIC_SYMBOL("SIMULATION-STATE",AB_package);
    Qoffline = STATIC_SYMBOL("OFFLINE",AB_package);
    Qgfi = STATIC_SYMBOL("GFI",AB_package);
    Qicp = STATIC_SYMBOL("ICP",AB_package);
    list_constant_23 = STATIC_LIST((SI_Long)3L,Qgsi,Qgfi,Qicp);
    Qpsueudo_authorized_optional_modules = 
	    STATIC_SYMBOL("PSUEUDO-AUTHORIZED-OPTIONAL-MODULES",AB_package);
    Qwrite_psueudo_authorized_optional_modules_from_slot = 
	    STATIC_SYMBOL("WRITE-PSUEUDO-AUTHORIZED-OPTIONAL-MODULES-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_psueudo_authorized_optional_modules_from_slot,
	    STATIC_FUNCTION(write_psueudo_authorized_optional_modules_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qpsueudo_authorized_optional_modules,
	    SYMBOL_FUNCTION(Qwrite_psueudo_authorized_optional_modules_from_slot),
	    Qslot_value_writer);
    string_constant_125 = STATIC_STRING("do not simulate");
    Qsimulated_products_qm = STATIC_SYMBOL("SIMULATED-PRODUCTS\?",AB_package);
    Qwrite_simulated_products_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-SIMULATED-PRODUCTS\?-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_simulated_products_qm_from_slot,
	    STATIC_FUNCTION(write_simulated_products_qm_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qsimulated_products_qm,
	    SYMBOL_FUNCTION(Qwrite_simulated_products_qm_from_slot),
	    Qslot_value_writer);
    Qcompile_simulated_products_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-SIMULATED-PRODUCTS\?-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_simulated_products_qm_for_slot,
	    STATIC_FUNCTION(compile_simulated_products_qm_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qsimulated_products_qm,
	    SYMBOL_FUNCTION(Qcompile_simulated_products_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qsimulated_products_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_260 = 
	    STATIC_STRING("1m1n83F0y1n1m9k830Iy1m9k9l1m9k83-pVy8k1m83F0y839py");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnot);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_260));
    Qput_simulated_optional_modules = 
	    STATIC_SYMBOL("PUT-SIMULATED-OPTIONAL-MODULES",AB_package);
    SET_SYMBOL_FUNCTION(Qput_simulated_optional_modules,
	    STATIC_FUNCTION(put_simulated_optional_modules,NIL,FALSE,3,3));
    mutate_global_property(Qsimulated_optional_modules,
	    SYMBOL_FUNCTION(Qput_simulated_optional_modules),Qslot_putter);
    Qframe_note_writer_1 = STATIC_SYMBOL("FRAME-NOTE-WRITER-1",AB_package);
    list_constant_24 = STATIC_LIST((SI_Long)3L,Qgsi,Qicp,Qgfi);
    string_constant_126 = 
	    STATIC_STRING("G2 is currently simulating ~A ~A license for this machine with the following details.");
    string_constant_127 = STATIC_STRING("an");
    string_constant_128 = STATIC_STRING("a");
    string_constant_261 = STATIC_STRING("embedded");
    string_constant_262 = STATIC_STRING("runtime");
    string_constant_263 = STATIC_STRING("restricted-use");
    string_constant_264 = STATIC_STRING("development");
    list_constant_25 = STATIC_LIST((SI_Long)8L,FIX((SI_Long)0L),
	    string_constant_261,FIX((SI_Long)1L),string_constant_262,
	    FIX((SI_Long)2L),string_constant_263,FIX((SI_Long)3L),
	    string_constant_264);
    string_constant_129 = 
	    STATIC_STRING("  Warning: the simulation does not include ~L,| ~\n                  because ~a not licensed.");
    string_constant_130 = STATIC_STRING("they are");
    string_constant_131 = STATIC_STRING("it is");
    string_constant_132 = 
	    STATIC_STRING("  Warning: you cannot simulate ~A ~A license on this machine.");
    string_constant_133 = STATIC_STRING("  The simulation includes ~L,&.");
    string_constant_134 = STATIC_STRING("  Licensed only for OFFLINE.");
    string_constant_135 = 
	    STATIC_STRING("  Simulating the limited OFFLINE license.");
    string_constant_136 = 
	    STATIC_STRING("  The ~S package is included, but ~L,& ~\n                    ~a not included because of OFFLINE.");
    string_constant_137 = STATIC_STRING("are");
    string_constant_138 = STATIC_STRING("is");
    string_constant_139 = 
	    STATIC_STRING("  The simulation does not include ~L,|.");
    write_note_status_of_simulated_product_authorization_note_1 = 
	    STATIC_FUNCTION(write_note_status_of_simulated_product_authorization_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qnote_status_of_simulated_product_authorization,
	    write_note_status_of_simulated_product_authorization_note_1,
	    Qframe_note_writer_1);
    Qembedded = STATIC_SYMBOL("EMBEDDED",AB_package);
    Qruntime = STATIC_SYMBOL("RUNTIME",AB_package);
    Qrestricted_use = STATIC_SYMBOL("RESTRICTED-USE",AB_package);
    Qlicense_level = STATIC_SYMBOL("LICENSE-LEVEL",AB_package);
    SET_SYMBOL_FUNCTION(Qlicense_level,STATIC_FUNCTION(license_level,NIL,
	    FALSE,1,1));
    Qg1 = STATIC_SYMBOL("G1",AB_package);
    Qg2_describe_g2_license = STATIC_SYMBOL("G2-DESCRIBE-G2-LICENSE",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_describe_g2_license,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_describe_g2_license,
	    STATIC_FUNCTION(g2_describe_g2_license,NIL,FALSE,0,0));
    Qset_inherit_stdio_handles = STATIC_SYMBOL("SET-INHERIT-STDIO-HANDLES",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qset_inherit_stdio_handles,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qset_inherit_stdio_handles,
	    STATIC_FUNCTION(set_inherit_stdio_handles,NIL,FALSE,1,1));
    if (Foremost_attribute_for_multiplexed_chaining_qm == UNBOUND)
	Foremost_attribute_for_multiplexed_chaining_qm = Nil;
    Qmarshall_exceptional_float_arguments = 
	    STATIC_SYMBOL("MARSHALL-EXCEPTIONAL-FLOAT-ARGUMENTS",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qmarshall_exceptional_float_arguments,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    array_constant_8 = STATIC_ARRAY(list_constant_96,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)9L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)15L,(SI_Long)57344L);
    array_constant_9 = STATIC_ARRAY(list_constant_96,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)57344L);
    SET_SYMBOL_FUNCTION(Qmarshall_exceptional_float_arguments,
	    STATIC_FUNCTION(marshall_exceptional_float_arguments,NIL,FALSE,
	    0,0));
    Qthis = STATIC_SYMBOL("THIS",AB_package);
    Qmenu_and_attribute_visibility_configurations_restriction_type = 
	    STATIC_SYMBOL("MENU-AND-ATTRIBUTE-VISIBILITY-CONFIGURATIONS-RESTRICTION-TYPE",
	    AB_package);
    set_property_value_function(get_symbol_properties_function(Qmenu_and_attribute_visibility_configurations_restriction_type),
	    Qtype_specification_simple_expansion,Qnil);
    list_constant_27 = STATIC_CONS(Qmember,list_constant_107);
    define_type_specification_explicit_complex_type(Qmenu_and_attribute_visibility_configurations_restriction_type,
	    list_constant_27);
    list_constant_26 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qmenu_and_attribute_visibility_configurations_restriction_type);
    menu_and_attribute_visibility_configurations_restriction_type_evaluation_setter_1 
	    = 
	    STATIC_FUNCTION(menu_and_attribute_visibility_configurations_restriction_type_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qmenu_and_attribute_visibility_configurations_restriction_type,
	    menu_and_attribute_visibility_configurations_restriction_type_evaluation_setter_1);
    menu_and_attribute_visibility_configurations_restriction_type_evaluation_getter_1 
	    = 
	    STATIC_FUNCTION(menu_and_attribute_visibility_configurations_restriction_type_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qmenu_and_attribute_visibility_configurations_restriction_type,
	    menu_and_attribute_visibility_configurations_restriction_type_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qtable_menu_choice),
	    Qtype_specification_simple_expansion,Qnil);
    list_constant_29 = STATIC_CONS(Qmember,list_constant_101);
    define_type_specification_explicit_complex_type(Qtable_menu_choice,
	    list_constant_29);
    list_constant_28 = STATIC_LIST((SI_Long)2L,Qnamed,Qtable_menu_choice);
    table_menu_choice_evaluation_setter_1 = 
	    STATIC_FUNCTION(table_menu_choice_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qtable_menu_choice,
	    table_menu_choice_evaluation_setter_1);
    table_menu_choice_evaluation_getter_1 = 
	    STATIC_FUNCTION(table_menu_choice_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qtable_menu_choice,
	    table_menu_choice_evaluation_getter_1);
    list_constant_83 = STATIC_CONS(Qsequence,Qnil);
    set_property_value_function(get_symbol_properties_function(Qtable_menu_choices),
	    Qtype_specification_simple_expansion,list_constant_83);
    list_constant_147 = STATIC_CONS(FIX((SI_Long)0L),Qnil);
    list_constant_31 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_28,list_constant_147);
    define_type_specification_explicit_complex_type(Qtable_menu_choices,
	    list_constant_31);
    list_constant_30 = STATIC_LIST((SI_Long)2L,Qnamed,Qtable_menu_choices);
    Qcategory_evaluator_interface = 
	    STATIC_SYMBOL("CATEGORY-EVALUATOR-INTERFACE",AB_package);
    table_menu_choices_evaluation_setter_1 = 
	    STATIC_FUNCTION(table_menu_choices_evaluation_setter,NIL,FALSE,
	    4,4);
    set_evaluation_value_to_category_function(Qtable_menu_choices,
	    table_menu_choices_evaluation_setter_1);
    table_menu_choices_evaluation_getter_1 = 
	    STATIC_FUNCTION(table_menu_choices_evaluation_getter,NIL,FALSE,
	    3,3);
    set_slot_value_to_evaluation_value_function(Qtable_menu_choices,
	    table_menu_choices_evaluation_getter_1);
    Qmenu_choices = STATIC_SYMBOL("MENU-CHOICES",AB_package);
    set_property_value_function(get_symbol_properties_function(Qmenu_choices),
	    Qtype_specification_simple_expansion,list_constant_83);
    list_constant_33 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,Qsymbol,
	    list_constant_147);
    define_type_specification_explicit_complex_type(Qmenu_choices,
	    list_constant_33);
    list_constant_32 = STATIC_LIST((SI_Long)2L,Qnamed,Qmenu_choices);
    menu_choices_evaluation_setter_1 = 
	    STATIC_FUNCTION(menu_choices_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qmenu_choices,
	    menu_choices_evaluation_setter_1);
    menu_choices_evaluation_getter_1 = 
	    STATIC_FUNCTION(menu_choices_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qmenu_choices,
	    menu_choices_evaluation_getter_1);
    Qtable_menu_configurations = STATIC_SYMBOL("TABLE-MENU-CONFIGURATIONS",
	    AB_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    list_constant_148 = STATIC_CONS(Qab_structure,Qnil);
    set_property_value_function(get_symbol_properties_function(Qtable_menu_configurations),
	    Qtype_specification_simple_expansion,list_constant_148);
    Qoperation_type = STATIC_SYMBOL("OPERATION-TYPE",AB_package);
    Qtable_menu = STATIC_SYMBOL("TABLE-MENU",AB_package);
    list_constant_149 = STATIC_LIST((SI_Long)2L,Qmember,Qtable_menu);
    list_constant_151 = STATIC_LIST((SI_Long)2L,Qoperation_type,
	    list_constant_149);
    Qrestriction_type = STATIC_SYMBOL("RESTRICTION-TYPE",AB_package);
    list_constant_152 = STATIC_LIST((SI_Long)2L,Qrestriction_type,
	    list_constant_26);
    list_constant_153 = STATIC_LIST((SI_Long)2L,Qmenu_choices,
	    list_constant_30);
    Qapplicable_attributes = STATIC_SYMBOL("APPLICABLE-ATTRIBUTES",AB_package);
    list_constant_154 = STATIC_LIST((SI_Long)2L,Qapplicable_attributes,
	    list_constant_33);
    Qapplicable_items = STATIC_SYMBOL("APPLICABLE-ITEMS",AB_package);
    list_constant_150 = STATIC_LIST((SI_Long)3L,Qsequence,Qsymbol,
	    FIX((SI_Long)1L));
    list_constant_155 = STATIC_LIST((SI_Long)2L,Qapplicable_items,
	    list_constant_150);
    list_constant_156 = STATIC_LIST((SI_Long)5L,list_constant_151,
	    list_constant_152,list_constant_153,list_constant_154,
	    list_constant_155);
    list_constant_157 = STATIC_LIST((SI_Long)5L,Qand,Qoperation_type,
	    Qmenu_choices,Qapplicable_items,Qrestriction_type);
    list_constant_35 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_156,list_constant_157);
    define_type_specification_explicit_complex_type(Qtable_menu_configurations,
	    list_constant_35);
    list_constant_34 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qtable_menu_configurations);
    Qattribute_visibility = STATIC_SYMBOL("ATTRIBUTE-VISIBILITY",AB_package);
    table_menu_configurations_evaluation_setter_1 = 
	    STATIC_FUNCTION(table_menu_configurations_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qtable_menu_configurations,
	    table_menu_configurations_evaluation_setter_1);
    Qpressing_or_releasing = STATIC_SYMBOL("PRESSING-OR-RELEASING",AB_package);
    table_menu_configurations_evaluation_getter_1 = 
	    STATIC_FUNCTION(table_menu_configurations_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qtable_menu_configurations,
	    table_menu_configurations_evaluation_getter_1);
    Qmenu_configurations = STATIC_SYMBOL("MENU-CONFIGURATIONS",AB_package);
    set_property_value_function(get_symbol_properties_function(Qmenu_configurations),
	    Qtype_specification_simple_expansion,list_constant_148);
    list_constant_158 = STATIC_CONS(Qmember,list_constant_108);
    list_constant_159 = STATIC_LIST((SI_Long)2L,Qoperation_type,
	    list_constant_158);
    list_constant_160 = STATIC_LIST((SI_Long)2L,Qmenu_choices,
	    list_constant_32);
    list_constant_161 = STATIC_CONS(list_constant_155,Qnil);
    list_constant_162 = STATIC_LIST_STAR((SI_Long)4L,list_constant_159,
	    list_constant_152,list_constant_160,list_constant_161);
    list_constant_163 = STATIC_CONS(list_constant_157,Qnil);
    list_constant_37 = STATIC_LIST_STAR((SI_Long)3L,Qab_structure,
	    list_constant_162,list_constant_163);
    define_type_specification_explicit_complex_type(Qmenu_configurations,
	    list_constant_37);
    list_constant_36 = STATIC_LIST((SI_Long)2L,Qnamed,Qmenu_configurations);
    menu_configurations_evaluation_setter_1 = 
	    STATIC_FUNCTION(menu_configurations_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qmenu_configurations,
	    menu_configurations_evaluation_setter_1);
    menu_configurations_evaluation_getter_1 = 
	    STATIC_FUNCTION(menu_configurations_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qmenu_configurations,
	    menu_configurations_evaluation_getter_1);
    Qattribute_visibility_configurations = 
	    STATIC_SYMBOL("ATTRIBUTE-VISIBILITY-CONFIGURATIONS",AB_package);
    set_property_value_function(get_symbol_properties_function(Qattribute_visibility_configurations),
	    Qtype_specification_simple_expansion,list_constant_148);
    list_constant_164 = STATIC_LIST((SI_Long)2L,Qmember,Qattribute_visibility);
    list_constant_166 = STATIC_LIST((SI_Long)2L,Qoperation_type,
	    list_constant_164);
    Qattributes = STATIC_SYMBOL("ATTRIBUTES",AB_package);
    list_constant_165 = STATIC_CONS(list_constant_33,Qnil);
    list_constant_167 = STATIC_CONS(Qattributes,list_constant_165);
    list_constant_169 = STATIC_LIST_STAR((SI_Long)4L,list_constant_166,
	    list_constant_152,list_constant_167,list_constant_161);
    list_constant_168 = STATIC_LIST((SI_Long)2L,Qapplicable_items,
	    Qrestriction_type);
    list_constant_170 = STATIC_LIST_STAR((SI_Long)4L,Qand,Qoperation_type,
	    Qattributes,list_constant_168);
    list_constant_39 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_169,list_constant_170);
    define_type_specification_explicit_complex_type(Qattribute_visibility_configurations,
	    list_constant_39);
    list_constant_38 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qattribute_visibility_configurations);
    attribute_visibility_configurations_evaluation_setter_1 = 
	    STATIC_FUNCTION(attribute_visibility_configurations_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qattribute_visibility_configurations,
	    attribute_visibility_configurations_evaluation_setter_1);
    attribute_visibility_configurations_evaluation_getter_1 = 
	    STATIC_FUNCTION(attribute_visibility_configurations_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qattribute_visibility_configurations,
	    attribute_visibility_configurations_evaluation_getter_1);
    Quser_interface_consequent_action = 
	    STATIC_SYMBOL("USER-INTERFACE-CONSEQUENT-ACTION",AB_package);
    list_constant_171 = STATIC_CONS(Qsymbol,Qnil);
    list_constant_172 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qnil,
	    list_constant_171);
    list_constant_173 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_172,
	    list_constant_148);
    set_property_value_function(get_symbol_properties_function(Quser_interface_consequent_action),
	    Qtype_specification_simple_expansion,list_constant_173);
    list_constant_174 = STATIC_CONS(Qmember,list_constant_99);
    list_constant_181 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,
	    list_constant_174,list_constant_171);
    Qmouse_tracking_procedure_name = 
	    STATIC_SYMBOL("MOUSE-TRACKING-PROCEDURE-NAME",AB_package);
    list_constant_176 = STATIC_CONS(Qmouse_tracking_procedure_name,
	    list_constant_171);
    Qmouse_tracking_applicable_items = 
	    STATIC_SYMBOL("MOUSE-TRACKING-APPLICABLE-ITEMS",AB_package);
    list_constant_175 = STATIC_CONS(list_constant_150,Qnil);
    list_constant_177 = STATIC_CONS(Qmouse_tracking_applicable_items,
	    list_constant_175);
    Qmouse_motion_tracking_qm = STATIC_SYMBOL("MOUSE-MOTION-TRACKING\?",
	    AB_package);
    list_constant_178 = STATIC_LIST((SI_Long)2L,Qmouse_motion_tracking_qm,
	    Qtruth_value);
    list_constant_179 = STATIC_LIST((SI_Long)3L,list_constant_176,
	    list_constant_177,list_constant_178);
    list_constant_180 = STATIC_LIST((SI_Long)3L,Qand,
	    Qmouse_tracking_procedure_name,Qmouse_tracking_applicable_items);
    list_constant_182 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_179,list_constant_180);
    list_constant_41 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_181,
	    list_constant_182);
    define_type_specification_explicit_complex_type(Quser_interface_consequent_action,
	    list_constant_41);
    list_constant_40 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Quser_interface_consequent_action);
    Qmotion = STATIC_SYMBOL("MOTION",AB_package);
    user_interface_consequent_action_evaluation_setter_1 = 
	    STATIC_FUNCTION(user_interface_consequent_action_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Quser_interface_consequent_action,
	    user_interface_consequent_action_evaluation_setter_1);
    user_interface_consequent_action_evaluation_getter_1 = 
	    STATIC_FUNCTION(user_interface_consequent_action_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Quser_interface_consequent_action,
	    user_interface_consequent_action_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qmodifier_key),
	    Qtype_specification_simple_expansion,Qnil);
    Qcontrol = STATIC_SYMBOL("CONTROL",AB_package);
    Qshift = STATIC_SYMBOL("SHIFT",AB_package);
    Qalt = STATIC_SYMBOL("ALT",AB_package);
    list_constant_43 = STATIC_LIST((SI_Long)4L,Qmember,Qcontrol,Qshift,Qalt);
    define_type_specification_explicit_complex_type(Qmodifier_key,
	    list_constant_43);
    list_constant_42 = STATIC_LIST((SI_Long)2L,Qnamed,Qmodifier_key);
    modifier_key_evaluation_setter_1 = 
	    STATIC_FUNCTION(modifier_key_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qmodifier_key,
	    modifier_key_evaluation_setter_1);
    modifier_key_evaluation_getter_1 = 
	    STATIC_FUNCTION(modifier_key_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qmodifier_key,
	    modifier_key_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qkeyboard_symbol),
	    Qtype_specification_simple_expansion,Qnil);
    list_constant_45 = STATIC_CONS(Qmember,list_constant_112);
    define_type_specification_explicit_complex_type(Qkeyboard_symbol,
	    list_constant_45);
    list_constant_44 = STATIC_LIST((SI_Long)2L,Qnamed,Qkeyboard_symbol);
    keyboard_symbol_evaluation_setter_1 = 
	    STATIC_FUNCTION(keyboard_symbol_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qkeyboard_symbol,
	    keyboard_symbol_evaluation_setter_1);
    keyboard_symbol_evaluation_getter_1 = 
	    STATIC_FUNCTION(keyboard_symbol_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qkeyboard_symbol,
	    keyboard_symbol_evaluation_getter_1);
    Qmouse_button = STATIC_SYMBOL("MOUSE-BUTTON",AB_package);
    set_property_value_function(get_symbol_properties_function(Qmouse_button),
	    Qtype_specification_simple_expansion,Qnil);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qmiddle = STATIC_SYMBOL("MIDDLE",AB_package);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    list_constant_47 = STATIC_LIST((SI_Long)5L,Qmember,Qany,Qleft,Qmiddle,
	    Qright);
    define_type_specification_explicit_complex_type(Qmouse_button,
	    list_constant_47);
    list_constant_46 = STATIC_LIST((SI_Long)2L,Qnamed,Qmouse_button);
    mouse_button_evaluation_setter_1 = 
	    STATIC_FUNCTION(mouse_button_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qmouse_button,
	    mouse_button_evaluation_setter_1);
    mouse_button_evaluation_getter_1 = 
	    STATIC_FUNCTION(mouse_button_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qmouse_button,
	    mouse_button_evaluation_getter_1);
    Quser_interface_key_chord = STATIC_SYMBOL("USER-INTERFACE-KEY-CHORD",
	    AB_package);
    set_property_value_function(get_symbol_properties_function(Quser_interface_key_chord),
	    Qtype_specification_simple_expansion,list_constant_148);
    Qmodifiers = STATIC_SYMBOL("MODIFIERS",AB_package);
    list_constant_183 = STATIC_LIST((SI_Long)2L,Qmodifiers,Qinteger);
    list_constant_184 = STATIC_LIST((SI_Long)2L,Qkeyboard_symbol,
	    list_constant_44);
    list_constant_186 = STATIC_LIST((SI_Long)2L,list_constant_183,
	    list_constant_184);
    list_constant_185 = STATIC_CONS(Qkeyboard_symbol,Qnil);
    list_constant_187 = STATIC_LIST_STAR((SI_Long)3L,Qand,Qmodifiers,
	    list_constant_185);
    list_constant_49 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_186,list_constant_187);
    define_type_specification_explicit_complex_type(Quser_interface_key_chord,
	    list_constant_49);
    list_constant_48 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Quser_interface_key_chord);
    user_interface_key_chord_evaluation_setter_1 = 
	    STATIC_FUNCTION(user_interface_key_chord_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Quser_interface_key_chord,
	    user_interface_key_chord_evaluation_setter_1);
    user_interface_key_chord_evaluation_getter_1 = 
	    STATIC_FUNCTION(user_interface_key_chord_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Quser_interface_key_chord,
	    user_interface_key_chord_evaluation_getter_1);
    Qconfigure_keystroke = STATIC_SYMBOL("CONFIGURE-KEYSTROKE",AB_package);
    set_property_value_function(get_symbol_properties_function(Qconfigure_keystroke),
	    Qtype_specification_simple_expansion,list_constant_148);
    list_constant_188 = STATIC_LIST((SI_Long)3L,Qmember,Qtyping,Qhovering);
    list_constant_189 = STATIC_LIST((SI_Long)2L,Qoperation_type,
	    list_constant_188);
    Qkey_code = STATIC_SYMBOL("KEY-CODE",AB_package);
    list_constant_190 = STATIC_LIST((SI_Long)2L,Qkey_code,list_constant_48);
    Qconsequent_action = STATIC_SYMBOL("CONSEQUENT-ACTION",AB_package);
    list_constant_191 = STATIC_LIST((SI_Long)2L,Qconsequent_action,
	    list_constant_40);
    list_constant_192 = STATIC_LIST_STAR((SI_Long)4L,list_constant_189,
	    list_constant_190,list_constant_191,list_constant_161);
    list_constant_193 = STATIC_LIST((SI_Long)4L,Qand,Qoperation_type,
	    Qkey_code,Qconsequent_action);
    list_constant_51 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_192,list_constant_193);
    define_type_specification_explicit_complex_type(Qconfigure_keystroke,
	    list_constant_51);
    list_constant_50 = STATIC_LIST((SI_Long)2L,Qnamed,Qconfigure_keystroke);
    configure_keystroke_evaluation_setter_1 = 
	    STATIC_FUNCTION(configure_keystroke_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qconfigure_keystroke,
	    configure_keystroke_evaluation_setter_1);
    configure_keystroke_evaluation_getter_1 = 
	    STATIC_FUNCTION(configure_keystroke_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qconfigure_keystroke,
	    configure_keystroke_evaluation_getter_1);
    list_constant_52 = STATIC_LIST((SI_Long)2L,Qpressing,Qclicking);
    string_constant_140 = 
	    STATIC_STRING("The double-bit is permitted only with operation-type PRESSING.");
    Qconfigure_mouse_click = STATIC_SYMBOL("CONFIGURE-MOUSE-CLICK",AB_package);
    set_property_value_function(get_symbol_properties_function(Qconfigure_mouse_click),
	    Qtype_specification_simple_expansion,list_constant_148);
    list_constant_194 = STATIC_CONS(Qclicking,Qnil);
    list_constant_195 = STATIC_LIST_STAR((SI_Long)4L,Qmember,Qpressing,
	    Qreleasing,list_constant_194);
    list_constant_201 = STATIC_LIST((SI_Long)2L,Qoperation_type,
	    list_constant_195);
    list_constant_196 = STATIC_LIST((SI_Long)2L,Qmouse_button,
	    list_constant_46);
    list_constant_198 = STATIC_LIST((SI_Long)2L,list_constant_183,
	    list_constant_196);
    list_constant_197 = STATIC_CONS(Qmouse_button,Qnil);
    list_constant_199 = STATIC_CONS(Qand,list_constant_197);
    list_constant_200 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_198,list_constant_199);
    list_constant_202 = STATIC_LIST((SI_Long)2L,Qkey_code,list_constant_200);
    list_constant_203 = STATIC_CONS(list_constant_191,list_constant_161);
    list_constant_204 = STATIC_LIST_STAR((SI_Long)3L,list_constant_201,
	    list_constant_202,list_constant_203);
    list_constant_205 = STATIC_CONS(list_constant_193,Qnil);
    list_constant_54 = STATIC_LIST_STAR((SI_Long)3L,Qab_structure,
	    list_constant_204,list_constant_205);
    define_type_specification_explicit_complex_type(Qconfigure_mouse_click,
	    list_constant_54);
    list_constant_53 = STATIC_LIST((SI_Long)2L,Qnamed,Qconfigure_mouse_click);
    configure_mouse_click_evaluation_setter_1 = 
	    STATIC_FUNCTION(configure_mouse_click_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qconfigure_mouse_click,
	    configure_mouse_click_evaluation_setter_1);
    configure_mouse_click_evaluation_getter_1 = 
	    STATIC_FUNCTION(configure_mouse_click_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qconfigure_mouse_click,
	    configure_mouse_click_evaluation_getter_1);
    Qconfigure_selection = STATIC_SYMBOL("CONFIGURE-SELECTION",AB_package);
    set_property_value_function(get_symbol_properties_function(Qconfigure_selection),
	    Qtype_specification_simple_expansion,list_constant_148);
    list_constant_206 = STATIC_LIST((SI_Long)2L,Qselecting,
	    Qselecting_absolutely);
    list_constant_207 = STATIC_CONS(Qmember,list_constant_206);
    list_constant_208 = STATIC_LIST((SI_Long)2L,Qoperation_type,
	    list_constant_207);
    list_constant_210 = STATIC_CONS(list_constant_208,list_constant_203);
    list_constant_209 = STATIC_CONS(Qconsequent_action,Qnil);
    list_constant_211 = STATIC_LIST_STAR((SI_Long)3L,Qand,Qoperation_type,
	    list_constant_209);
    list_constant_56 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_210,list_constant_211);
    define_type_specification_explicit_complex_type(Qconfigure_selection,
	    list_constant_56);
    list_constant_55 = STATIC_LIST((SI_Long)2L,Qnamed,Qconfigure_selection);
    configure_selection_evaluation_setter_1 = 
	    STATIC_FUNCTION(configure_selection_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qconfigure_selection,
	    configure_selection_evaluation_setter_1);
    configure_selection_evaluation_getter_1 = 
	    STATIC_FUNCTION(configure_selection_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qconfigure_selection,
	    configure_selection_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qrectangle),
	    Qtype_specification_simple_expansion,list_constant_148);
    Qleft_edge = STATIC_SYMBOL("LEFT-EDGE",AB_package);
    list_constant_212 = STATIC_CONS(Qinteger,Qnil);
    list_constant_213 = STATIC_CONS(Qleft_edge,list_constant_212);
    Qright_edge = STATIC_SYMBOL("RIGHT-EDGE",AB_package);
    list_constant_214 = STATIC_CONS(Qright_edge,list_constant_212);
    Qtop_edge = STATIC_SYMBOL("TOP-EDGE",AB_package);
    list_constant_215 = STATIC_CONS(Qtop_edge,list_constant_212);
    Qbottom_edge = STATIC_SYMBOL("BOTTOM-EDGE",AB_package);
    list_constant_216 = STATIC_CONS(Qbottom_edge,list_constant_212);
    list_constant_217 = STATIC_LIST((SI_Long)4L,list_constant_213,
	    list_constant_214,list_constant_215,list_constant_216);
    list_constant_218 = STATIC_LIST((SI_Long)5L,Qand,Qleft_edge,
	    Qright_edge,Qtop_edge,Qbottom_edge);
    list_constant_58 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_217,list_constant_218);
    define_type_specification_explicit_complex_type(Qrectangle,
	    list_constant_58);
    list_constant_57 = STATIC_LIST((SI_Long)2L,Qnamed,Qrectangle);
    rectangle_evaluation_setter_1 = 
	    STATIC_FUNCTION(rectangle_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qrectangle,
	    rectangle_evaluation_setter_1);
    rectangle_evaluation_getter_1 = 
	    STATIC_FUNCTION(rectangle_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qrectangle,
	    rectangle_evaluation_getter_1);
    Qgrid = STATIC_SYMBOL("GRID",AB_package);
    set_property_value_function(get_symbol_properties_function(Qgrid),
	    Qtype_specification_simple_expansion,list_constant_148);
    Qx_grid_length = STATIC_SYMBOL("X-GRID-LENGTH",AB_package);
    list_constant_219 = STATIC_CONS(Qx_grid_length,list_constant_212);
    Qy_grid_length = STATIC_SYMBOL("Y-GRID-LENGTH",AB_package);
    list_constant_220 = STATIC_CONS(Qy_grid_length,list_constant_212);
    list_constant_221 = STATIC_LIST((SI_Long)2L,list_constant_219,
	    list_constant_220);
    list_constant_222 = STATIC_LIST((SI_Long)3L,Qand,Qx_grid_length,
	    Qy_grid_length);
    list_constant_60 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_221,list_constant_222);
    define_type_specification_explicit_complex_type(Qgrid,list_constant_60);
    list_constant_59 = STATIC_LIST((SI_Long)2L,Qnamed,Qgrid);
    string_constant_141 = 
	    STATIC_STRING("The x-grid-length, ~NV, must be positive");
    string_constant_142 = 
	    STATIC_STRING("The y-grid-length, ~NV, must be positive");
    grid_evaluation_setter_1 = STATIC_FUNCTION(grid_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qgrid,grid_evaluation_setter_1);
    grid_evaluation_getter_1 = STATIC_FUNCTION(grid_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qgrid,
	    grid_evaluation_getter_1);
    Qconstrain_movement_of_items = 
	    STATIC_SYMBOL("CONSTRAIN-MOVEMENT-OF-ITEMS",AB_package);
    set_property_value_function(get_symbol_properties_function(Qconstrain_movement_of_items),
	    Qtype_specification_simple_expansion,list_constant_148);
    list_constant_223 = STATIC_LIST((SI_Long)2L,Qmember,Qmoving);
    list_constant_227 = STATIC_LIST((SI_Long)2L,Qoperation_type,
	    list_constant_223);
    Qtype_of_region = STATIC_SYMBOL("TYPE-OF-REGION",AB_package);
    list_constant_224 = STATIC_CONS(Qgrid,Qnil);
    list_constant_225 = STATIC_LIST_STAR((SI_Long)3L,Qmember,Qrectangle,
	    list_constant_224);
    list_constant_228 = STATIC_LIST((SI_Long)2L,Qtype_of_region,
	    list_constant_225);
    Qconstrained_region = STATIC_SYMBOL("CONSTRAINED-REGION",AB_package);
    list_constant_226 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_57,
	    list_constant_59);
    list_constant_229 = STATIC_LIST((SI_Long)2L,Qconstrained_region,
	    list_constant_226);
    list_constant_230 = STATIC_LIST_STAR((SI_Long)4L,list_constant_227,
	    list_constant_228,list_constant_229,list_constant_161);
    list_constant_231 = STATIC_LIST((SI_Long)5L,Qand,Qoperation_type,
	    Qtype_of_region,Qconstrained_region,Qapplicable_items);
    list_constant_62 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_230,list_constant_231);
    define_type_specification_explicit_complex_type(Qconstrain_movement_of_items,
	    list_constant_62);
    list_constant_61 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qconstrain_movement_of_items);
    constrain_movement_of_items_evaluation_setter_1 = 
	    STATIC_FUNCTION(constrain_movement_of_items_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qconstrain_movement_of_items,
	    constrain_movement_of_items_evaluation_setter_1);
    constrain_movement_of_items_evaluation_getter_1 = 
	    STATIC_FUNCTION(constrain_movement_of_items_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qconstrain_movement_of_items,
	    constrain_movement_of_items_evaluation_getter_1);
    Qrestrict_proprietary_items_and_configure_user_interface_statement = 
	    STATIC_SYMBOL("RESTRICT-PROPRIETARY-ITEMS-AND-CONFIGURE-USER-INTERFACE-STATEMENT",
	    AB_package);
    list_constant_232 = STATIC_CONS(Qnil,Qnil);
    list_constant_233 = STATIC_LIST_STAR((SI_Long)8L,Qab_or,Qnil,Qnil,Qnil,
	    Qnil,Qnil,Qnil,list_constant_232);
    set_property_value_function(get_symbol_properties_function(Qrestrict_proprietary_items_and_configure_user_interface_statement),
	    Qtype_specification_simple_expansion,list_constant_233);
    list_constant_64 = STATIC_LIST((SI_Long)8L,Qab_or,list_constant_36,
	    list_constant_34,list_constant_38,list_constant_53,
	    list_constant_50,list_constant_55,list_constant_61);
    define_type_specification_explicit_complex_type(Qrestrict_proprietary_items_and_configure_user_interface_statement,
	    list_constant_64);
    list_constant_63 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qrestrict_proprietary_items_and_configure_user_interface_statement);
    restrict_proprietary_items_and_configure_user_interface_statement_evaluation_setter_1 
	    = 
	    STATIC_FUNCTION(restrict_proprietary_items_and_configure_user_interface_statement_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qrestrict_proprietary_items_and_configure_user_interface_statement,
	    restrict_proprietary_items_and_configure_user_interface_statement_evaluation_setter_1);
    restrict_proprietary_items_and_configure_user_interface_statement_evaluation_getter_1 
	    = 
	    STATIC_FUNCTION(restrict_proprietary_items_and_configure_user_interface_statement_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qrestrict_proprietary_items_and_configure_user_interface_statement,
	    restrict_proprietary_items_and_configure_user_interface_statement_evaluation_getter_1);
    Qconfigure_user_interface_statements = 
	    STATIC_SYMBOL("CONFIGURE-USER-INTERFACE-STATEMENTS",AB_package);
    set_property_value_function(get_symbol_properties_function(Qconfigure_user_interface_statements),
	    Qtype_specification_simple_expansion,list_constant_83);
    list_constant_234 = STATIC_CONS(FIX((SI_Long)1L),Qnil);
    list_constant_66 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_63,list_constant_234);
    define_type_specification_explicit_complex_type(Qconfigure_user_interface_statements,
	    list_constant_66);
    list_constant_65 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qconfigure_user_interface_statements);
    configure_user_interface_statements_evaluation_setter_1 = 
	    STATIC_FUNCTION(configure_user_interface_statements_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qconfigure_user_interface_statements,
	    configure_user_interface_statements_evaluation_setter_1);
    configure_user_interface_statements_evaluation_getter_1 = 
	    STATIC_FUNCTION(configure_user_interface_statements_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qconfigure_user_interface_statements,
	    configure_user_interface_statements_evaluation_getter_1);
    Qapplicable_user_modes = STATIC_SYMBOL("APPLICABLE-USER-MODES",AB_package);
    set_property_value_function(get_symbol_properties_function(Qapplicable_user_modes),
	    Qtype_specification_simple_expansion,list_constant_148);
    Qnegative = STATIC_SYMBOL("NEGATIVE",AB_package);
    list_constant_235 = STATIC_CONS(Qtruth_value,Qnil);
    list_constant_238 = STATIC_CONS(Qnegative,list_constant_235);
    Qmodes = STATIC_SYMBOL("MODES",AB_package);
    Qunreserved_symbol = STATIC_SYMBOL("UNRESERVED-SYMBOL",AB_package);
    list_constant_236 = STATIC_LIST((SI_Long)2L,Qnamed,Qunreserved_symbol);
    list_constant_237 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_236,list_constant_234);
    list_constant_239 = STATIC_LIST((SI_Long)2L,Qmodes,list_constant_237);
    list_constant_240 = STATIC_LIST((SI_Long)2L,list_constant_238,
	    list_constant_239);
    list_constant_241 = STATIC_LIST((SI_Long)2L,Qand,Qmodes);
    list_constant_68 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_240,list_constant_241);
    define_type_specification_explicit_complex_type(Qapplicable_user_modes,
	    list_constant_68);
    list_constant_67 = STATIC_LIST((SI_Long)2L,Qnamed,Qapplicable_user_modes);
    applicable_user_modes_evaluation_setter_1 = 
	    STATIC_FUNCTION(applicable_user_modes_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qapplicable_user_modes,
	    applicable_user_modes_evaluation_setter_1);
    applicable_user_modes_evaluation_getter_1 = 
	    STATIC_FUNCTION(applicable_user_modes_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qapplicable_user_modes,
	    applicable_user_modes_evaluation_getter_1);
    Qconfigure_user_interface = STATIC_SYMBOL("CONFIGURE-USER-INTERFACE",
	    AB_package);
    set_property_value_function(get_symbol_properties_function(Qconfigure_user_interface),
	    Qtype_specification_simple_expansion,list_constant_83);
    list_constant_242 = STATIC_LIST((SI_Long)2L,Qapplicable_user_modes,
	    list_constant_67);
    Qstatements = STATIC_SYMBOL("STATEMENTS",AB_package);
    list_constant_243 = STATIC_LIST((SI_Long)2L,Qstatements,list_constant_65);
    list_constant_244 = STATIC_LIST((SI_Long)2L,list_constant_242,
	    list_constant_243);
    list_constant_245 = STATIC_LIST((SI_Long)3L,Qand,
	    Qapplicable_user_modes,Qstatements);
    list_constant_246 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_244,list_constant_245);
    list_constant_70 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_246,list_constant_234);
    define_type_specification_explicit_complex_type(Qconfigure_user_interface,
	    list_constant_70);
    list_constant_69 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qconfigure_user_interface);
    configure_user_interface_evaluation_setter_1 = 
	    STATIC_FUNCTION(configure_user_interface_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qconfigure_user_interface,
	    configure_user_interface_evaluation_setter_1);
    configure_user_interface_evaluation_getter_1 = 
	    STATIC_FUNCTION(configure_user_interface_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qconfigure_user_interface,
	    configure_user_interface_evaluation_getter_1);
    Qrestrict_proprietary_items = 
	    STATIC_SYMBOL("RESTRICT-PROPRIETARY-ITEMS",AB_package);
    set_property_value_function(get_symbol_properties_function(Qrestrict_proprietary_items),
	    Qtype_specification_simple_expansion,list_constant_83);
    define_type_specification_explicit_complex_type(Qrestrict_proprietary_items,
	    list_constant_66);
    list_constant_71 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qrestrict_proprietary_items);
    restrict_proprietary_items_evaluation_setter_1 = 
	    STATIC_FUNCTION(restrict_proprietary_items_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qrestrict_proprietary_items,
	    restrict_proprietary_items_evaluation_setter_1);
    restrict_proprietary_items_evaluation_getter_1 = 
	    STATIC_FUNCTION(restrict_proprietary_items_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qrestrict_proprietary_items,
	    restrict_proprietary_items_evaluation_getter_1);
    Qset_up_network_access = STATIC_SYMBOL("SET-UP-NETWORK-ACCESS",AB_package);
    set_property_value_function(get_symbol_properties_function(Qset_up_network_access),
	    Qtype_specification_simple_expansion,list_constant_83);
    Qallow = STATIC_SYMBOL("ALLOW",AB_package);
    Qprohibit = STATIC_SYMBOL("PROHIBIT",AB_package);
    Qprohibit_absolutely = STATIC_SYMBOL("PROHIBIT-ABSOLUTELY",AB_package);
    list_constant_247 = STATIC_LIST((SI_Long)4L,Qmember,Qallow,Qprohibit,
	    Qprohibit_absolutely);
    list_constant_251 = STATIC_LIST((SI_Long)2L,Qrestriction_type,
	    list_constant_247);
    Qaccess_types = STATIC_SYMBOL("ACCESS-TYPES",AB_package);
    list_constant_248 = STATIC_LIST((SI_Long)6L,Qmember,Qexecute,Qconnect,
	    Qinform,Qread,Qwrite);
    list_constant_249 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_248,list_constant_234);
    list_constant_252 = STATIC_LIST((SI_Long)2L,Qaccess_types,
	    list_constant_249);
    Qaccess_agent = STATIC_SYMBOL("ACCESS-AGENT",AB_package);
    Qtelewindows_and_gsi = STATIC_SYMBOL("TELEWINDOWS-AND-GSI",AB_package);
    list_constant_250 = STATIC_LIST((SI_Long)8L,Qmember,Qany,Qg2,Qgsi,
	    Qg2_and_gsi,Qg2_and_telewindows,Qg2_and_telewindows_and_gsi,
	    Qtelewindows_and_gsi);
    list_constant_253 = STATIC_LIST((SI_Long)2L,Qaccess_agent,
	    list_constant_250);
    list_constant_254 = STATIC_LIST_STAR((SI_Long)4L,list_constant_251,
	    list_constant_252,list_constant_253,list_constant_161);
    list_constant_255 = STATIC_LIST((SI_Long)4L,Qand,Qrestriction_type,
	    Qaccess_types,Qaccess_agent);
    list_constant_256 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_254,list_constant_255);
    list_constant_73 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_256,list_constant_234);
    define_type_specification_explicit_complex_type(Qset_up_network_access,
	    list_constant_73);
    list_constant_72 = STATIC_LIST((SI_Long)2L,Qnamed,Qset_up_network_access);
    set_up_network_access_evaluation_setter_1 = 
	    STATIC_FUNCTION(set_up_network_access_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qset_up_network_access,
	    set_up_network_access_evaluation_setter_1);
    set_up_network_access_evaluation_getter_1 = 
	    STATIC_FUNCTION(set_up_network_access_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qset_up_network_access,
	    set_up_network_access_evaluation_getter_1);
    Qdeclared_properties_attributes = 
	    STATIC_SYMBOL("DECLARED-PROPERTIES-ATTRIBUTES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdeclared_properties_attributes,
	    Declared_properties_attributes);
    Qactivatable_subworkspace = STATIC_SYMBOL("ACTIVATABLE-SUBWORKSPACE",
	    AB_package);
    Qexternal_simulation = STATIC_SYMBOL("EXTERNAL-SIMULATION",AB_package);
    list_constant_257 = STATIC_LIST((SI_Long)9L,
	    Qindependent_for_all_compilations,
	    Qstable_for_dependent_compilations,Qstable_hierarchy,
	    Qmanual_connections,Qoptimizable,Qinlineable,
	    Qactivatable_subworkspace,Qexternal_simulation,
	    Qsubworkspace_connection_posts);
    SET_SYMBOL_VALUE(Qdeclared_properties_attributes,list_constant_257);
    Qdeclare_properties = STATIC_SYMBOL("DECLARE-PROPERTIES",AB_package);
    set_property_value_function(get_symbol_properties_function(Qdeclare_properties),
	    Qtype_specification_simple_expansion,list_constant_148);
    Qdeclared_properties = STATIC_SYMBOL("DECLARED-PROPERTIES",AB_package);
    list_constant_258 = STATIC_CONS(Qindependent_for_all_compilations,
	    list_constant_235);
    list_constant_259 = STATIC_CONS(Qstable_for_dependent_compilations,
	    list_constant_235);
    list_constant_260 = STATIC_CONS(Qstable_hierarchy,list_constant_235);
    list_constant_261 = STATIC_CONS(Qmanual_connections,list_constant_235);
    list_constant_262 = STATIC_CONS(Qoptimizable,list_constant_235);
    list_constant_263 = STATIC_CONS(Qinlineable,list_constant_235);
    list_constant_264 = STATIC_CONS(Qactivatable_subworkspace,
	    list_constant_235);
    list_constant_265 = STATIC_CONS(Qexternal_simulation,list_constant_235);
    list_constant_266 = STATIC_CONS(Qsubworkspace_connection_posts,
	    list_constant_235);
    list_constant_267 = STATIC_LIST((SI_Long)9L,list_constant_258,
	    list_constant_259,list_constant_260,list_constant_261,
	    list_constant_262,list_constant_263,list_constant_264,
	    list_constant_265,list_constant_266);
    list_constant_268 = STATIC_CONS(Qab_or,list_constant_257);
    list_constant_269 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_267,list_constant_268);
    list_constant_270 = STATIC_LIST((SI_Long)2L,Qdeclared_properties,
	    list_constant_269);
    list_constant_271 = STATIC_CONS(list_constant_270,list_constant_161);
    list_constant_272 = STATIC_LIST((SI_Long)2L,Qand,Qdeclared_properties);
    list_constant_75 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_271,list_constant_272);
    define_type_specification_explicit_complex_type(Qdeclare_properties,
	    list_constant_75);
    list_constant_74 = STATIC_LIST((SI_Long)2L,Qnamed,Qdeclare_properties);
    declare_properties_evaluation_setter_1 = 
	    STATIC_FUNCTION(declare_properties_evaluation_setter,NIL,FALSE,
	    4,4);
    set_evaluation_value_to_category_function(Qdeclare_properties,
	    declare_properties_evaluation_setter_1);
    declare_properties_evaluation_getter_1 = 
	    STATIC_FUNCTION(declare_properties_evaluation_getter,NIL,FALSE,
	    3,3);
    set_slot_value_to_evaluation_value_function(Qdeclare_properties,
	    declare_properties_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qcomment),
	    Qtype_specification_simple_expansion,list_constant_83);
    Qtag_name = STATIC_SYMBOL("TAG-NAME",AB_package);
    list_constant_273 = STATIC_CONS(Qtag_name,list_constant_171);
    Qassociated_text = STATIC_SYMBOL("ASSOCIATED-TEXT",AB_package);
    list_constant_274 = STATIC_LIST((SI_Long)2L,Qassociated_text,Qtext);
    list_constant_275 = STATIC_LIST((SI_Long)2L,list_constant_273,
	    list_constant_274);
    list_constant_276 = STATIC_LIST((SI_Long)2L,Qand,Qtag_name);
    list_constant_277 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_275,list_constant_276);
    list_constant_77 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_277,list_constant_234);
    define_type_specification_explicit_complex_type(Qcomment,list_constant_77);
    list_constant_76 = STATIC_LIST((SI_Long)2L,Qnamed,Qcomment);
    comment_evaluation_setter_1 = 
	    STATIC_FUNCTION(comment_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qcomment,
	    comment_evaluation_setter_1);
    comment_evaluation_getter_1 = 
	    STATIC_FUNCTION(comment_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qcomment,
	    comment_evaluation_getter_1);
    Qobject_configuration_spec = STATIC_SYMBOL("OBJECT-CONFIGURATION-SPEC",
	    AB_package);
    set_property_value_function(get_symbol_properties_function(Qobject_configuration_spec),
	    Qtype_specification_simple_expansion,list_constant_148);
    list_constant_278 = STATIC_CONS(Qcomment,Qnil);
    list_constant_279 = STATIC_LIST_STAR((SI_Long)6L,Qmember,
	    Qconfigure_user_interface,Qrestrict_proprietary_items,
	    Qset_up_network_access,Qdeclare_properties,list_constant_278);
    list_constant_281 = STATIC_LIST((SI_Long)2L,Qtype,list_constant_279);
    Qclauses = STATIC_SYMBOL("CLAUSES",AB_package);
    list_constant_280 = STATIC_LIST((SI_Long)6L,Qab_or,list_constant_69,
	    list_constant_71,list_constant_72,list_constant_74,
	    list_constant_76);
    list_constant_282 = STATIC_LIST((SI_Long)2L,Qclauses,list_constant_280);
    list_constant_283 = STATIC_LIST((SI_Long)2L,list_constant_281,
	    list_constant_282);
    list_constant_284 = STATIC_LIST((SI_Long)3L,Qand,Qtype,Qclauses);
    list_constant_79 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_283,list_constant_284);
    define_type_specification_explicit_complex_type(Qobject_configuration_spec,
	    list_constant_79);
    list_constant_78 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qobject_configuration_spec);
    object_configuration_spec_evaluation_setter_1 = 
	    STATIC_FUNCTION(object_configuration_spec_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qobject_configuration_spec,
	    object_configuration_spec_evaluation_setter_1);
    object_configuration_spec_evaluation_getter_1 = 
	    STATIC_FUNCTION(object_configuration_spec_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qobject_configuration_spec,
	    object_configuration_spec_evaluation_getter_1);
    list_constant_285 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_82,
	    list_constant_83);
    set_property_value_function(get_symbol_properties_function(Qobject_configuration),
	    Qtype_specification_simple_expansion,list_constant_285);
    list_constant_286 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_78,list_constant_234);
    list_constant_81 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_82,
	    list_constant_286);
    define_type_specification_explicit_complex_type(Qobject_configuration,
	    list_constant_81);
    list_constant_80 = STATIC_LIST((SI_Long)2L,Qnamed,Qobject_configuration);
    string_constant_143 = STATIC_STRING("~NT ");
    string_constant_144 = 
	    STATIC_STRING("~NV must be one of the following types: ~a");
    object_configuration_evaluation_setter_1 = 
	    STATIC_FUNCTION(object_configuration_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qobject_configuration,
	    object_configuration_evaluation_setter_1);
    object_configuration_evaluation_getter_1 = 
	    STATIC_FUNCTION(object_configuration_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qobject_configuration,
	    object_configuration_evaluation_getter_1);
    Qmain_menu_restrictions_statements = 
	    STATIC_SYMBOL("MAIN-MENU-RESTRICTIONS-STATEMENTS",AB_package);
    set_property_value_function(get_symbol_properties_function(Qmain_menu_restrictions_statements),
	    Qtype_specification_simple_expansion,list_constant_83);
    list_constant_287 = STATIC_CONS(Qmember,list_constant_104);
    list_constant_288 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,
	    list_constant_287,list_constant_171);
    list_constant_289 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_288,list_constant_234);
    list_constant_290 = STATIC_LIST((SI_Long)2L,Qmenu_choices,
	    list_constant_289);
    list_constant_292 = STATIC_LIST((SI_Long)2L,list_constant_152,
	    list_constant_290);
    list_constant_291 = STATIC_CONS(Qmenu_choices,Qnil);
    list_constant_293 = STATIC_LIST_STAR((SI_Long)3L,Qand,
	    Qrestriction_type,list_constant_291);
    list_constant_294 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_292,list_constant_293);
    list_constant_85 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_294,list_constant_234);
    define_type_specification_explicit_complex_type(Qmain_menu_restrictions_statements,
	    list_constant_85);
    list_constant_84 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qmain_menu_restrictions_statements);
    main_menu_restrictions_statements_evaluation_setter_1 = 
	    STATIC_FUNCTION(main_menu_restrictions_statements_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qmain_menu_restrictions_statements,
	    main_menu_restrictions_statements_evaluation_setter_1);
    main_menu_restrictions_statements_evaluation_getter_1 = 
	    STATIC_FUNCTION(main_menu_restrictions_statements_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qmain_menu_restrictions_statements,
	    main_menu_restrictions_statements_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qmain_menu_restrictions),
	    Qtype_specification_simple_expansion,list_constant_285);
    list_constant_295 = STATIC_LIST((SI_Long)2L,Qstatements,list_constant_84);
    list_constant_296 = STATIC_LIST((SI_Long)2L,list_constant_242,
	    list_constant_295);
    list_constant_297 = STATIC_CONS(list_constant_245,Qnil);
    list_constant_298 = STATIC_LIST_STAR((SI_Long)3L,Qab_structure,
	    list_constant_296,list_constant_297);
    list_constant_299 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_298,list_constant_234);
    list_constant_87 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_82,
	    list_constant_299);
    define_type_specification_explicit_complex_type(Qmain_menu_restrictions,
	    list_constant_87);
    list_constant_86 = STATIC_LIST((SI_Long)2L,Qnamed,Qmain_menu_restrictions);
    main_menu_restrictions_evaluation_setter_1 = 
	    STATIC_FUNCTION(main_menu_restrictions_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qmain_menu_restrictions,
	    main_menu_restrictions_evaluation_setter_1);
    main_menu_restrictions_evaluation_getter_1 = 
	    STATIC_FUNCTION(main_menu_restrictions_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qmain_menu_restrictions,
	    main_menu_restrictions_evaluation_getter_1);
    Qglobal_keyboard_command_restrictions_statements = 
	    STATIC_SYMBOL("GLOBAL-KEYBOARD-COMMAND-RESTRICTIONS-STATEMENTS",
	    AB_package);
    set_property_value_function(get_symbol_properties_function(Qglobal_keyboard_command_restrictions_statements),
	    Qtype_specification_simple_expansion,list_constant_83);
    Qcommand_choices = STATIC_SYMBOL("COMMAND-CHOICES",AB_package);
    list_constant_300 = STATIC_CONS(Qmember,list_constant_102);
    list_constant_301 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_300,list_constant_234);
    list_constant_302 = STATIC_LIST((SI_Long)2L,Qcommand_choices,
	    list_constant_301);
    list_constant_303 = STATIC_LIST((SI_Long)2L,list_constant_152,
	    list_constant_302);
    list_constant_304 = STATIC_LIST((SI_Long)3L,Qand,Qrestriction_type,
	    Qcommand_choices);
    list_constant_305 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_303,list_constant_304);
    list_constant_89 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_305,list_constant_234);
    define_type_specification_explicit_complex_type(Qglobal_keyboard_command_restrictions_statements,
	    list_constant_89);
    list_constant_88 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qglobal_keyboard_command_restrictions_statements);
    global_keyboard_command_restrictions_statements_evaluation_setter_1 = 
	    STATIC_FUNCTION(global_keyboard_command_restrictions_statements_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qglobal_keyboard_command_restrictions_statements,
	    global_keyboard_command_restrictions_statements_evaluation_setter_1);
    global_keyboard_command_restrictions_statements_evaluation_getter_1 = 
	    STATIC_FUNCTION(global_keyboard_command_restrictions_statements_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qglobal_keyboard_command_restrictions_statements,
	    global_keyboard_command_restrictions_statements_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qglobal_keyboard_command_restrictions),
	    Qtype_specification_simple_expansion,list_constant_285);
    list_constant_306 = STATIC_LIST((SI_Long)2L,Qstatements,list_constant_88);
    list_constant_307 = STATIC_LIST((SI_Long)2L,list_constant_242,
	    list_constant_306);
    list_constant_308 = STATIC_LIST_STAR((SI_Long)3L,Qab_structure,
	    list_constant_307,list_constant_297);
    list_constant_309 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_308,list_constant_234);
    list_constant_91 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_82,
	    list_constant_309);
    define_type_specification_explicit_complex_type(Qglobal_keyboard_command_restrictions,
	    list_constant_91);
    list_constant_90 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qglobal_keyboard_command_restrictions);
    global_keyboard_command_restrictions_evaluation_setter_1 = 
	    STATIC_FUNCTION(global_keyboard_command_restrictions_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qglobal_keyboard_command_restrictions,
	    global_keyboard_command_restrictions_evaluation_setter_1);
    global_keyboard_command_restrictions_evaluation_getter_1 = 
	    STATIC_FUNCTION(global_keyboard_command_restrictions_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qglobal_keyboard_command_restrictions,
	    global_keyboard_command_restrictions_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qpsueudo_authorized_optional_modules),
	    Qtype_specification_simple_expansion,list_constant_83);
    define_type_specification_explicit_complex_type(Qpsueudo_authorized_optional_modules,
	    list_constant_150);
    psueudo_authorized_optional_modules_evaluation_getter_1 = 
	    STATIC_FUNCTION(psueudo_authorized_optional_modules_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qpsueudo_authorized_optional_modules,
	    psueudo_authorized_optional_modules_evaluation_getter_1);
    list_constant_310 = STATIC_CONS(list_constant_83,Qnil);
    list_constant_311 = STATIC_LIST_STAR((SI_Long)4L,Qab_or,
	    list_constant_82,Qsymbol,list_constant_310);
    set_property_value_function(get_symbol_properties_function(Qsimulated_products_qm),
	    Qtype_specification_simple_expansion,list_constant_311);
    list_constant_93 = STATIC_LIST_STAR((SI_Long)4L,Qab_or,
	    list_constant_82,Qsymbol,list_constant_175);
    define_type_specification_explicit_complex_type(Qsimulated_products_qm,
	    list_constant_93);
    list_constant_92 = STATIC_LIST((SI_Long)2L,Qnamed,Qsimulated_products_qm);
    Qdo_not_simulate = STATIC_SYMBOL("DO-NOT-SIMULATE",AB_package);
    string_constant_145 = STATIC_STRING("Illegal value ~NV");
    simulated_products_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(simulated_products_qm_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qsimulated_products_qm,
	    simulated_products_qm_evaluation_setter_1);
    simulated_products_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(simulated_products_qm_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qsimulated_products_qm,
	    simulated_products_qm_evaluation_getter_1);
    Qg2_login_user_mode = STATIC_SYMBOL("G2-LOGIN-USER-MODE",AB_package);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Quser_mode_aliases = STATIC_SYMBOL("USER-MODE-ALIASES",AB_package);
}
