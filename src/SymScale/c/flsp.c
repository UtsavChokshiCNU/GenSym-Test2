/* flsp.c
 * Input file:  file-sysproc.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "flsp.h"


DEFINE_VARIABLE_WITH_SYMBOL(Available_sysproc_conses, Qavailable_sysproc_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_sysproc_conses_tail, Qavailable_sysproc_conses_tail);

Object Available_sysproc_conses_vector = UNBOUND;

Object Available_sysproc_conses_tail_vector = UNBOUND;

Object Sysproc_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Sysproc_cons_counter, Qsysproc_cons_counter);

/* OUTSTANDING-SYSPROC-CONSES */
Object outstanding_sysproc_conses()
{
    Object temp;

    x_note_fn_call(164,0);
    temp = FIXNUM_MINUS(Sysproc_cons_counter,length(Available_sysproc_conses));
    return VALUES_1(temp);
}

/* SYSPROC-CONS-MEMORY-USAGE */
Object sysproc_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(164,1);
    temp = FIXNUM_TIMES(Sysproc_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-SYSPROC-CONS-POOL */
Object replenish_sysproc_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(164,2);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qsysproc_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_sysproc_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_sysproc_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_sysproc_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_sysproc_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_sysproc_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Sysproc_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qsysproc;            /* sysproc */

/* SYSPROC-CONS-1 */
Object sysproc_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(164,3);
    new_cons = ISVREF(Available_sysproc_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_sysproc_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_sysproc_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_sysproc_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_sysproc_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qsysproc);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-SYSPROC-LIST-POOL */
Object replenish_sysproc_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(164,4);
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
    if (ISVREF(Available_sysproc_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_sysproc_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_sysproc_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_sysproc_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_sysproc_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qsysproc_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-SYSPROC-LIST-1 */
Object make_sysproc_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(164,5);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_sysproc_conses_vector,
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
	replenish_sysproc_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_sysproc_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qsysproc);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_sysproc_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_sysproc_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_sysproc_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_sysproc_conses_tail_vector;
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

/* SYSPROC-LIST-2 */
Object sysproc_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(164,6);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_sysproc_conses_vector,IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_sysproc_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_sysproc_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qsysproc);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_sysproc_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_sysproc_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_sysproc_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_sysproc_conses_tail_vector;
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

/* SYSPROC-LIST-3 */
Object sysproc_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(164,7);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_sysproc_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_sysproc_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_sysproc_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qsysproc);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_sysproc_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_sysproc_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_sysproc_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_sysproc_conses_tail_vector;
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

/* SYSPROC-LIST-4 */
Object sysproc_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(164,8);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_sysproc_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_sysproc_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_sysproc_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qsysproc);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_sysproc_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_sysproc_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_sysproc_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_sysproc_conses_tail_vector;
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

/* SYSPROC-LIST-TRACE-HOOK */
Object sysproc_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(164,9);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-SYSPROC-CONSES-1 */
Object copy_tree_using_sysproc_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(164,10);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_sysproc_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_sysproc_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_sysproc_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_sysproc_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_sysproc_cons_pool();
	temp_1 = copy_tree_using_sysproc_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qsysproc);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_sysproc_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_sysproc_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_sysproc_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_sysproc_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_sysproc_cons_pool();
	temp_1 = copy_tree_using_sysproc_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qsysproc);
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

/* COPY-LIST-USING-SYSPROC-CONSES-1 */
Object copy_list_using_sysproc_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(164,11);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_sysproc_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_sysproc_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_sysproc_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_sysproc_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_sysproc_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qsysproc);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_sysproc_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_sysproc_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_sysproc_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_sysproc_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_sysproc_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qsysproc);
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

/* RECLAIM-SYSPROC-CONS-1 */
Object reclaim_sysproc_cons_1(sysproc_cons)
    Object sysproc_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(164,12);
    inline_note_reclaim_cons(sysproc_cons,Qsysproc);
    if (ISVREF(Available_sysproc_conses_tail_vector,
	    IFIX(Current_thread_index))) {
	temp = ISVREF(Available_sysproc_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = sysproc_cons;
	temp = Available_sysproc_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = sysproc_cons;
    }
    else {
	temp = Available_sysproc_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = sysproc_cons;
	temp = Available_sysproc_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = sysproc_cons;
    }
    M_CDR(sysproc_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-SYSPROC-LIST-1 */
Object reclaim_sysproc_list_1(sysproc_list)
    Object sysproc_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(164,13);
    if (sysproc_list) {
	last_1 = sysproc_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qsysproc);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qsysproc);
	if (ISVREF(Available_sysproc_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_sysproc_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = sysproc_list;
	    temp = Available_sysproc_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_sysproc_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = sysproc_list;
	    temp = Available_sysproc_conses_tail_vector;
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

/* RECLAIM-SYSPROC-LIST*-1 */
Object reclaim_sysproc_list_star_1(sysproc_list)
    Object sysproc_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(164,14);
    if (CONSP(sysproc_list)) {
	temp = last(sysproc_list,_);
	M_CDR(temp) = Nil;
	if (sysproc_list) {
	    last_1 = sysproc_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qsysproc);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qsysproc);
	    if (ISVREF(Available_sysproc_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_sysproc_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = sysproc_list;
		temp = Available_sysproc_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_sysproc_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = sysproc_list;
		temp = Available_sysproc_conses_tail_vector;
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

/* RECLAIM-SYSPROC-TREE-1 */
Object reclaim_sysproc_tree_1(tree)
    Object tree;
{
    Object e, e2, sysproc_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(164,15);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_sysproc_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		sysproc_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(sysproc_cons,Qsysproc);
		if (EQ(sysproc_cons,e))
		    goto end_1;
		else if ( !TRUEP(sysproc_cons))
		    goto end_1;
		else
		    sysproc_cons = CDR(sysproc_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_sysproc_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_sysproc_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_sysproc_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_sysproc_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_sysproc_conses_tail_vector;
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

/* DELETE-SYSPROC-ELEMENT-1 */
Object delete_sysproc_element_1(element,sysproc_list)
    Object element, sysproc_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(164,16);
    if (sysproc_list) {
	if (EQ(element,M_CAR(sysproc_list))) {
	    temp = CDR(sysproc_list);
	    inline_note_reclaim_cons(sysproc_list,Qsysproc);
	    if (ISVREF(Available_sysproc_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_sysproc_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = sysproc_list;
		temp_1 = Available_sysproc_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = sysproc_list;
	    }
	    else {
		temp_1 = Available_sysproc_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = sysproc_list;
		temp_1 = Available_sysproc_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = sysproc_list;
	    }
	    M_CDR(sysproc_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = sysproc_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qsysproc);
		if (ISVREF(Available_sysproc_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_sysproc_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_sysproc_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_sysproc_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_sysproc_conses_tail_vector;
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
	    temp = sysproc_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-SYSPROC-CONS-1 */
Object delete_sysproc_cons_1(sysproc_cons,sysproc_list)
    Object sysproc_cons, sysproc_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(164,17);
    if (EQ(sysproc_cons,sysproc_list))
	temp = CDR(sysproc_list);
    else {
	l_trailer_qm = Nil;
	l = sysproc_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,sysproc_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = sysproc_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_sysproc_cons_1(sysproc_cons);
    return VALUES_1(temp);
}

/* RECLAIM-SYSPROC-LIST-FUNCTION */
Object reclaim_sysproc_list_function(sysproc_list)
    Object sysproc_list;
{
    x_note_fn_call(164,18);
    return reclaim_sysproc_list_1(sysproc_list);
}

static Object Qg2_directory_pathname;  /* g2-directory-pathname */

/* WRITE-NAME-OF-FILE-FROM-SLOT */
Object write_name_of_file_from_slot(namestring_1,gensymed_symbol)
    Object namestring_1, gensymed_symbol;
{
    Object namestring_as_text;

    x_note_fn_call(164,19);
    namestring_as_text = import_text_string(2,namestring_1,
	    Qg2_directory_pathname);
    twrite_general_string(namestring_as_text);
    return reclaim_text_string(namestring_as_text);
}

static Object Qg2_stream;          /* g2-stream */

/* CLEANUP-FOR-G2-STREAM */
Object cleanup_for_g2_stream(g2_stream)
    Object g2_stream;
{
    Object frame, sub_vector_qm, method_function_qm, internal_g2_stream_qm;
    Object buffer_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(164,20);
    frame = g2_stream;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qg2_stream)) {
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
    internal_g2_stream_qm = ISVREF(g2_stream,(SI_Long)26L);
    if (internal_g2_stream_qm) {
	g2_stream_close(internal_g2_stream_qm);
	ISVREF(g2_stream,(SI_Long)26L) = Nil;
    }
    buffer_qm = ISVREF(g2_stream,(SI_Long)27L);
    if (buffer_qm)
	reclaim_text_string(buffer_qm);
    return VALUES_1(ISVREF(g2_stream,(SI_Long)27L) = Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(G2_stream_status_slot_description, Qg2_stream_status_slot_description);

DEFINE_VARIABLE_WITH_SYMBOL(Name_of_file_slot_description, Qname_of_file_slot_description);

DEFINE_VARIABLE_WITH_SYMBOL(Access_direction_slot_description, Qaccess_direction_slot_description);

DEFINE_VARIABLE_WITH_SYMBOL(Position_in_file_slot_description, Qposition_in_file_slot_description);

DEFINE_VARIABLE_WITH_SYMBOL(File_system_slot_description, Qfile_system_slot_description);

/* RECLAIM-INTERNAL-STRUCTURE-FOR-TEXT-CONVERSION-STYLE-VALUE */
Object reclaim_internal_structure_for_text_conversion_style_value(text_conversion_style,
	    gensymed_symbol)
    Object text_conversion_style, gensymed_symbol;
{
    x_note_fn_call(164,21);
    reclaim_transcode_text_conversion_style_1(text_conversion_style);
    return VALUES_1(Nil);
}

static Object Qtext_conversion_style;  /* text-conversion-style */

/* INITIALIZE-AFTER-READING-FOR-TEXT-CONVERSION-STYLE */
Object initialize_after_reading_for_text_conversion_style(text_conversion_style)
    Object text_conversion_style;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(164,22);
    frame = text_conversion_style;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)4L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qtext_conversion_style)) {
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
    return update_internal_structure_for_text_conversion_style(text_conversion_style);
}

/* INITIALIZE-FOR-TEXT-CONVERSION-STYLE */
Object initialize_for_text_conversion_style(text_conversion_style)
    Object text_conversion_style;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(164,23);
    frame = text_conversion_style;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)2L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qtext_conversion_style)) {
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
    return update_internal_structure_for_text_conversion_style(text_conversion_style);
}

static Object list_constant;       /* # */

static Object list_constant_1;     /* # */

static Object Qnone;               /* none */

/* TEXT-CONVERSION-STYLE-NAME?-EVALUATION-SETTER */
Object text_conversion_style_name_qm_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(164,24);
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
			      list_constant_1,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_text_conversion_style_name_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (evaluation_value)
	result = VALUES_1(evaluation_value);
    else
	result = VALUES_1(Qnone);
  end_text_conversion_style_name_qm_evaluation_setter:
    return result;
}

/* TEXT-CONVERSION-STYLE-NAME?-EVALUATION-GETTER */
Object text_conversion_style_name_qm_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(164,25);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object Qframe_status_and_notes;  /* frame-status-and-notes */

static Object Qstack_change;       /* stack-change */

/* PUT-TEXT-CONVERSION-STYLE */
Object put_text_conversion_style(language_parameters,
	    text_conversion_style_name_qm,gensymed_symbol)
    Object language_parameters, text_conversion_style_name_qm, gensymed_symbol;
{
    Object result_1, current_flag_state_qm, slot_description, new_cons, temp;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object stack_of_slot_value_changes, gensymed_symbol_2, gensymed_symbol_3;
    Object frame_and_slot_or_atom, ab_loop_list_, ab_loop_it_, temp_2;
    Object stack_change_pop_store, cons_1, next_cons;
    SI_Long svref_new_value_1;
    char temp_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(164,26);
    PUSH_SPECIAL_WITH_SYMBOL(Language_parameters,Qlanguage_parameters,language_parameters,
	    1);
      result_1 = Nil;
      current_flag_state_qm = Nil;
      slot_description = 
	      get_slot_description_of_class_description_function(Qframe_status_and_notes,
	      ISVREF(Language_parameters,(SI_Long)1L),Nil);
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
	  gensymed_symbol_1 = 
		  nconc2(stack_change_list_2(Language_parameters,
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
	  temp = Language_parameters;
	  M_CAR(gensymed_symbol_1) = temp;
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
	current_flag_state_qm = (SI_Long)0L != 
		(IFIX(ISVREF(Language_parameters,(SI_Long)5L)) & 
		(SI_Long)16777216L) ? T : Nil;
	if ( !TRUEP(current_flag_state_qm)) {
	    gensymed_symbol = 
		    ISVREF(ISVREF(ISVREF(ISVREF(Language_parameters,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	    gensymed_symbol_1 = Language_parameters;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = T;
	    inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	    temp = Language_parameters;
	    svref_new_value_1 = IFIX(ISVREF(Language_parameters,
		    (SI_Long)5L)) | (SI_Long)16777216L;
	    ISVREF(temp,(SI_Long)5L) = FIX(svref_new_value_1);
	}
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(Language_parameters,Qtext_conversion_style);
	result_1 = set_lookup_slot_value_1(Language_parameters,
		Qtext_conversion_style,text_conversion_style_name_qm);
	if ( !TRUEP(current_flag_state_qm)) {
	    temp = Language_parameters;
	    svref_new_value_1 = IFIX(ISVREF(Language_parameters,
		    (SI_Long)5L)) &  ~(SI_Long)16777216L;
	    ISVREF(temp,(SI_Long)5L) = FIX(svref_new_value_1);
	    gensymed_symbol = 
		    ISVREF(ISVREF(ISVREF(ISVREF(Language_parameters,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	    gensymed_symbol_1 = Language_parameters;
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
	    ab_loop_it_ = temp_1 ? (EQ(Language_parameters,
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
	    update_all_representations_of_slot(Language_parameters,
		    slot_description,Nil,Nil);
	if (ISVREF(slot_description,(SI_Long)14L))
	    update_frame_name_references(Language_parameters);
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
	if (temp_1 ?  
		!TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) : 
		TRUEP(Nil))
	    do_deferred_updates_to_representations_in_tables();
      POP_SPECIAL();
      result = VALUES_1(text_conversion_style_name_qm);
    POP_SPECIAL();
    return result;
}

/* COMPILE-TEXT-CONVERSION-STYLE-NAME?-FOR-SLOT */
Object compile_text_conversion_style_name_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(164,27);
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
    if (EQ(parse_result,Qnone))
	return VALUES_1(Nil);
    else
	return VALUES_1(parse_result);
}

static Object array_constant;      /* # */

/* WRITE-TEXT-CONVERSION-STYLE-NAME?-FROM-SLOT */
Object write_text_conversion_style_name_qm_from_slot(style_name_qm,
	    gensymed_symbol)
    Object style_name_qm, gensymed_symbol;
{
    x_note_fn_call(164,28);
    if (style_name_qm)
	return twrite_symbol(2,style_name_qm,T);
    else
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)4L));
}

static Object Qinternal_structure_for_text_conversion_style;  /* internal-structure-for-text-conversion-style */

/* GET-TEXT-CONVERSION-STYLE-STRUCTURE-PER-NAME */
Object get_text_conversion_style_structure_per_name(style_name)
    Object style_name;
{
    Object named_style_frame_qm, temp;

    x_note_fn_call(164,29);
    named_style_frame_qm = 
	    get_instance_with_name_if_any(Qtext_conversion_style,style_name);
    temp = named_style_frame_qm ? 
	    get_lookup_slot_value_given_default(named_style_frame_qm,
	    Qinternal_structure_for_text_conversion_style,Nil) : Nil;
    return VALUES_1(temp);
}

/* COME-UP-WITH-TEXT-CONVERSION-STYLE-STRUCTURE */
Object come_up_with_text_conversion_style_structure(name_qm,
	    utf_g_ascii_as_much_as_possible_option_qm)
    Object name_qm, utf_g_ascii_as_much_as_possible_option_qm;
{
    Object temp;

    x_note_fn_call(164,30);
    temp = name_qm ? get_text_conversion_style_structure_per_name(name_qm) 
	    : Nil;
    if (temp);
    else
	temp = get_lookup_slot_value_given_default(Language_parameters,
		Qtext_conversion_style,Nil) ? 
		get_text_conversion_style_structure_per_name(get_lookup_slot_value_given_default(Language_parameters,
		Qtext_conversion_style,Nil)) : Nil;
    if (temp);
    else
	temp = utf_g_ascii_as_much_as_possible_option_qm ? 
		Utf_g_ascii_as_much_as_possible_conversion_style : Nil;
    if (temp);
    else
	temp = Default_text_conversion_style;
    return VALUES_1(temp);
}

/* CREATE-INTERNAL-STRUCTURE-FOR-TEXT-CONVERSION-STYLE */
Object create_internal_structure_for_text_conversion_style()
{
    x_note_fn_call(164,31);
    return make_transcode_text_conversion_style_1();
}

static Object Qexternal_character_set;  /* external-character-set */

static Object Qunconvertible_character_spec;  /* unconvertible-character-spec */

static Object Qexternal_line_separator;  /* external-line-separator */

static Object Qhan_unification_mode;  /* han-unification-mode */

/* UPDATE-INTERNAL-STRUCTURE-FOR-TEXT-CONVERSION-STYLE */
Object update_internal_structure_for_text_conversion_style(text_conversion_style)
    Object text_conversion_style;
{
    Object f, s, svref_new_value;

    x_note_fn_call(164,32);
    f = text_conversion_style;
    s = get_lookup_slot_value_given_default(text_conversion_style,
	    Qinternal_structure_for_text_conversion_style,Nil);
    if ( !TRUEP(get_lookup_slot_value_given_default(f,
	    Qinternal_structure_for_text_conversion_style,Nil)))
	s = set_non_savable_lookup_slot_value(f,
		Qinternal_structure_for_text_conversion_style,
		make_transcode_text_conversion_style_1());
    svref_new_value = get_lookup_slot_value(f,Qexternal_character_set);
    SVREF(s,FIX((SI_Long)2L)) = svref_new_value;
    svref_new_value = get_lookup_slot_value_given_default(f,
	    Qunconvertible_character_spec,Nil) ? 
	    get_lookup_slot_value_given_default(f,
	    Qunconvertible_character_spec,Nil) : Nil;
    SVREF(s,FIX((SI_Long)3L)) = svref_new_value;
    svref_new_value = get_lookup_slot_value(f,Qexternal_line_separator);
    SVREF(s,FIX((SI_Long)4L)) = svref_new_value;
    svref_new_value = get_lookup_slot_value(f,Qhan_unification_mode);
    return VALUES_1(SVREF(s,FIX((SI_Long)5L)) = svref_new_value);
}

/* PUT-EXTERNAL-CHARACTER-SET */
Object put_external_character_set(text_conversion_style,value,gensymed_symbol)
    Object text_conversion_style, value, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(164,33);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(text_conversion_style,Qexternal_character_set);
    temp = set_lookup_slot_value_1(text_conversion_style,
	    Qexternal_character_set,value);
    update_internal_structure_for_text_conversion_style(text_conversion_style);
    return VALUES_1(temp);
}

/* PUT-UNCONVERTIBLE-CHARACTER-SPEC */
Object put_unconvertible_character_spec(text_conversion_style,value,
	    gensymed_symbol)
    Object text_conversion_style, value, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(164,34);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(text_conversion_style,
		Qunconvertible_character_spec);
    temp = set_lookup_slot_value_1(text_conversion_style,
	    Qunconvertible_character_spec,value);
    update_internal_structure_for_text_conversion_style(text_conversion_style);
    return VALUES_1(temp);
}

/* PUT-EXTERNAL-LINE-SEPARATOR */
Object put_external_line_separator(text_conversion_style,value,gensymed_symbol)
    Object text_conversion_style, value, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(164,35);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(text_conversion_style,Qexternal_line_separator);
    temp = set_lookup_slot_value_1(text_conversion_style,
	    Qexternal_line_separator,value);
    update_internal_structure_for_text_conversion_style(text_conversion_style);
    return VALUES_1(temp);
}

/* PUT-HAN-UNIFICATION-MODE */
Object put_han_unification_mode(text_conversion_style,value,gensymed_symbol)
    Object text_conversion_style, value, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(164,36);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(text_conversion_style,Qhan_unification_mode);
    temp = set_lookup_slot_value_1(text_conversion_style,
	    Qhan_unification_mode,value);
    update_internal_structure_for_text_conversion_style(text_conversion_style);
    return VALUES_1(temp);
}

static Object string_constant;     /* "Text must contain a single character" */

static Object string_constant_1;   /* "Character code must be an integer between 0 and 65535" */

/* COMPILE-UNCONVERTIBLE-CHARACTER-SPEC-FOR-SLOT */
Object compile_unconvertible_character_spec_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(164,37);
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
    if (text_string_p(parse_result)) {
	if ( !(IFIX(lengthw(parse_result)) == (SI_Long)1L)) {
	    temp = Bad_phrase;
	    temp_1 = tformat_text_string(1,string_constant);
	    return VALUES_2(temp,temp_1);
	}
	else
	    return VALUES_1(FIX(UBYTE_16_ISAREF_1(parse_result,(SI_Long)0L)));
    }
    else if (FIXNUMP(parse_result)) {
	if ( !((SI_Long)0L <= IFIX(parse_result) && IFIX(parse_result) <= 
		(SI_Long)65535L)) {
	    temp = Bad_phrase;
	    temp_1 = tformat_text_string(1,string_constant_1);
	    return VALUES_2(temp,temp_1);
	}
	else
	    return VALUES_1(parse_result);
    }
    else if (EQ(parse_result,Qnone))
	return VALUES_1(Nil);
    else
	return VALUES_1(Qt);
}

static Object string_constant_2;   /* "none" */

static Object string_constant_3;   /* "~c" */

/* WRITE-UNCONVERTIBLE-CHARACTER-SPEC-FROM-SLOT */
Object write_unconvertible_character_spec_from_slot(slot_value,gensymed_symbol)
    Object slot_value, gensymed_symbol;
{
    Object temp_string;

    x_note_fn_call(164,38);
    if ( !TRUEP(slot_value))
	return tformat(1,string_constant_2);
    else {
	temp_string = tformat_text_string(2,string_constant_3,slot_value);
	twrite_parsably(temp_string);
	return reclaim_text_string(temp_string);
    }
}

static Object Qcr;                 /* cr */

static Object Qlf;                 /* lf */

static Object Qcrlf;               /* crlf */

/* WRITE-LINE-SEPARATOR-FROM-SLOT */
Object write_line_separator_from_slot(slot_value,gensymed_symbol)
    Object slot_value, gensymed_symbol;
{
    x_note_fn_call(164,39);
    if (EQ(slot_value,Qcr) || EQ(slot_value,Qlf) || EQ(slot_value,Qcrlf))
	return twrite_symbol(2,slot_value,T);
    else
	return twrite_symbol(1,slot_value);
}

Object Preferred_spelling_for_character_set_prop = UNBOUND;

static Object string_constant_4;   /* "unknown" */

static Object Qpreferred_spelling_for_character_set;  /* preferred-spelling-for-character-set */

static Object string_constant_5;   /* "~a" */

/* WRITE-CHARACTER-SET-FROM-SLOT */
Object write_character_set_from_slot(slot_value,gensymed_symbol)
    Object slot_value, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(164,40);
    if ( !TRUEP(slot_value))
	return tformat(1,string_constant_4);
    else {
	temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(slot_value),
		Qpreferred_spelling_for_character_set);
	if (temp);
	else
	    temp = slot_value;
	return tformat(2,string_constant_5,temp);
    }
}

static Object Kfirst_of_each_word;  /* :first-of-each-word */

/* WRITE-HAN-UNIFICATION-MODE-FROM-SLOT */
Object write_han_unification_mode_from_slot(slot_value,gensymed_symbol)
    Object slot_value, gensymed_symbol;
{
    x_note_fn_call(164,41);
    if ( !TRUEP(slot_value))
	return tformat(1,string_constant_4);
    else
	return twrite_symbol_into_text_string(2,slot_value,
		Kfirst_of_each_word);
}

static Object Qgeneralized_dos;    /* generalized-dos */

static Object Qdos;                /* dos */

static Object Qwin32;              /* win32 */

/* GET-FILESYSTEM-FROM-G2-STREAM-FOR-USER */
Object get_filesystem_from_g2_stream_for_user(g2_stream)
    Object g2_stream;
{
    Object pathname_1, internal_file_system_name, temp;

    x_note_fn_call(164,42);
    pathname_1 = g2_stream_find_active_pathname(g2_stream);
    internal_file_system_name = ISVREF(pathname_1,(SI_Long)8L);
    if (EQ(internal_file_system_name,Qgeneralized_dos)) {
	if (EQ(G2_operating_system,Qdos))
	    temp = Qdos;
	else if (EQ(G2_operating_system,Qwin32))
	    temp = Qwin32;
	else
	    temp = Qnil;
    }
    else
	temp = internal_file_system_name;
    return VALUES_1(temp);
}

static Object Qopen_for_read;      /* open-for-read */

static Object Qinput;              /* input */

static Object Qfailed_to_open_for_read;  /* failed-to-open-for-read */

static Object Qclosed;             /* closed */

static Object string_constant_6;   /* "" */

/* OPEN-FILE-FOR-READ-LISP-SIDE */
Object open_file_for_read_lisp_side(g2_filestring)
    Object g2_filestring;
{
    Object filestring, g2_stream_frame, internal_stream_qm, position_1;
    Object filesystem, svref_new_value, temp;

    x_note_fn_call(164,43);
    filestring = export_text_string(2,g2_filestring,Qg2_directory_pathname);
    g2_stream_frame = make_transient_item(Qg2_stream);
    internal_stream_qm = EQ(Local_file_system,Qwin32) || 
	    EQ(Local_file_system,Qdos) ? 
	    g2_stream_open_for_random_access_binary_input(filestring) : 
	    g2_stream_open_for_input(filestring);
    if (internal_stream_qm) {
	position_1 = g2_stream_get_file_position(internal_stream_qm);
	filesystem = 
		get_filesystem_from_g2_stream_for_user(internal_stream_qm);
	if ( !EQ(Qopen_for_read,ISVREF(g2_stream_frame,(SI_Long)24L)))
	    change_slot_description_value_function(g2_stream_frame,
		    G2_stream_status_slot_description,Qopen_for_read,Nil,Nil);
	if (internal_stream_qm) {
	    svref_new_value = Internal_status_of_most_recent_file_operation;
	    ISVREF(g2_stream_frame,(SI_Long)25L) = svref_new_value;
	}
	change_slot_description_value_function(g2_stream_frame,
		Name_of_file_slot_description,g2_filestring,Nil,Nil);
	change_slot_description_value_function(g2_stream_frame,
		Access_direction_slot_description,Qinput,Nil,Nil);
	change_slot_description_value_function(g2_stream_frame,
		Position_in_file_slot_description,position_1,Nil,Nil);
	ISVREF(g2_stream_frame,(SI_Long)26L) = internal_stream_qm;
	change_slot_description_value_function(g2_stream_frame,
		File_system_slot_description,filesystem,Nil,Nil);
	svref_new_value = 
		obtain_simple_text_string(Size_of_g2_stream_frame_input_buffer);
	ISVREF(g2_stream_frame,(SI_Long)27L) = svref_new_value;
    }
    else {
	if ( !EQ(Qfailed_to_open_for_read,ISVREF(g2_stream_frame,
		(SI_Long)24L)))
	    change_slot_description_value_function(g2_stream_frame,
		    G2_stream_status_slot_description,
		    Qfailed_to_open_for_read,Nil,Nil);
	if (internal_stream_qm) {
	    svref_new_value = Internal_status_of_most_recent_file_operation;
	    ISVREF(g2_stream_frame,(SI_Long)25L) = svref_new_value;
	}
	change_slot_description_value_function(g2_stream_frame,
		Name_of_file_slot_description,g2_filestring,Nil,Nil);
	change_slot_description_value_function(g2_stream_frame,
		Access_direction_slot_description,Qclosed,Nil,Nil);
    }
    reclaim_text_string(filestring);
    temp = internal_stream_qm ? copy_as_wide_string(string_constant_6) : 
	    most_recent_file_operation_status_as_text();
    return VALUES_2(g2_stream_frame,temp);
}

static Object Qopen_for_write;     /* open-for-write */

static Object Qoutput;             /* output */

static Object Qfailed_to_open_for_write;  /* failed-to-open-for-write */

/* OPEN-FILE-FOR-WRITE-LISP-SIDE */
Object open_file_for_write_lisp_side(g2_filestring)
    Object g2_filestring;
{
    Object filestring, g2_stream_frame, internal_stream_qm, position_1;
    Object filesystem, svref_new_value, temp;

    x_note_fn_call(164,44);
    filestring = export_text_string(2,g2_filestring,Qg2_directory_pathname);
    g2_stream_frame = make_transient_item(Qg2_stream);
    internal_stream_qm = EQ(Local_file_system,Qwin32) || 
	    EQ(Local_file_system,Qdos) ? 
	    g2_stream_open_for_binary_output(filestring) : 
	    g2_stream_open_for_output(filestring);
    if (internal_stream_qm) {
	position_1 = g2_stream_get_file_position(internal_stream_qm);
	filesystem = 
		get_filesystem_from_g2_stream_for_user(internal_stream_qm);
	if ( !EQ(Qopen_for_write,ISVREF(g2_stream_frame,(SI_Long)24L)))
	    change_slot_description_value_function(g2_stream_frame,
		    G2_stream_status_slot_description,Qopen_for_write,Nil,Nil);
	if (internal_stream_qm) {
	    svref_new_value = Internal_status_of_most_recent_file_operation;
	    ISVREF(g2_stream_frame,(SI_Long)25L) = svref_new_value;
	}
	change_slot_description_value_function(g2_stream_frame,
		Name_of_file_slot_description,g2_filestring,Nil,Nil);
	change_slot_description_value_function(g2_stream_frame,
		Access_direction_slot_description,Qoutput,Nil,Nil);
	change_slot_description_value_function(g2_stream_frame,
		Position_in_file_slot_description,position_1,Nil,Nil);
	ISVREF(g2_stream_frame,(SI_Long)26L) = internal_stream_qm;
	change_slot_description_value_function(g2_stream_frame,
		File_system_slot_description,filesystem,Nil,Nil);
    }
    else {
	if ( !EQ(Qfailed_to_open_for_write,ISVREF(g2_stream_frame,
		(SI_Long)24L)))
	    change_slot_description_value_function(g2_stream_frame,
		    G2_stream_status_slot_description,
		    Qfailed_to_open_for_write,Nil,Nil);
	if (internal_stream_qm) {
	    svref_new_value = Internal_status_of_most_recent_file_operation;
	    ISVREF(g2_stream_frame,(SI_Long)25L) = svref_new_value;
	}
	change_slot_description_value_function(g2_stream_frame,
		Name_of_file_slot_description,g2_filestring,Nil,Nil);
	change_slot_description_value_function(g2_stream_frame,
		Access_direction_slot_description,Qclosed,Nil,Nil);
    }
    reclaim_text_string(filestring);
    temp = internal_stream_qm ? copy_as_wide_string(string_constant_6) : 
	    most_recent_file_operation_status_as_text();
    return VALUES_2(g2_stream_frame,temp);
}

static Object Qopen_for_append;    /* open-for-append */

static Object Qfailed_to_open_for_append;  /* failed-to-open-for-append */

/* OPEN-FILE-FOR-APPEND-LISP-SIDE */
Object open_file_for_append_lisp_side(g2_filestring,create_it)
    Object g2_filestring, create_it;
{
    Object filestring, g2_stream_frame, temp, create_if_does_not_exist_p;
    Object internal_stream_qm, position_1, filesystem, svref_new_value;

    x_note_fn_call(164,45);
    filestring = export_text_string(2,g2_filestring,Qg2_directory_pathname);
    g2_stream_frame = make_transient_item(Qg2_stream);
    temp = FIXNUM_GE(M_CAR(create_it),ISVREF(Inference_engine_parameters,
	    (SI_Long)26L)) ? T : Nil;
    if ( !(EQ(create_it,Evaluation_true_value) || EQ(create_it,
	    Evaluation_false_value)))
	reclaim_eval_cons_1(create_it);
    create_if_does_not_exist_p = temp;
    internal_stream_qm = EQ(Local_file_system,Qwin32) || 
	    EQ(Local_file_system,Qdos) ? 
	    g2_stream_open_for_binary_appending(filestring,
	    create_if_does_not_exist_p) : 
	    g2_stream_open_for_appending(filestring,
	    create_if_does_not_exist_p);
    if (internal_stream_qm) {
	position_1 = g2_stream_get_file_position(internal_stream_qm);
	filesystem = 
		get_filesystem_from_g2_stream_for_user(internal_stream_qm);
	if ( !EQ(Qopen_for_append,ISVREF(g2_stream_frame,(SI_Long)24L)))
	    change_slot_description_value_function(g2_stream_frame,
		    G2_stream_status_slot_description,Qopen_for_append,Nil,
		    Nil);
	if (internal_stream_qm) {
	    svref_new_value = Internal_status_of_most_recent_file_operation;
	    ISVREF(g2_stream_frame,(SI_Long)25L) = svref_new_value;
	}
	change_slot_description_value_function(g2_stream_frame,
		Name_of_file_slot_description,g2_filestring,Nil,Nil);
	change_slot_description_value_function(g2_stream_frame,
		Access_direction_slot_description,Qoutput,Nil,Nil);
	change_slot_description_value_function(g2_stream_frame,
		Position_in_file_slot_description,position_1,Nil,Nil);
	ISVREF(g2_stream_frame,(SI_Long)26L) = internal_stream_qm;
	change_slot_description_value_function(g2_stream_frame,
		File_system_slot_description,filesystem,Nil,Nil);
    }
    else {
	if ( !EQ(Qfailed_to_open_for_append,ISVREF(g2_stream_frame,
		(SI_Long)24L)))
	    change_slot_description_value_function(g2_stream_frame,
		    G2_stream_status_slot_description,
		    Qfailed_to_open_for_append,Nil,Nil);
	if (internal_stream_qm) {
	    svref_new_value = Internal_status_of_most_recent_file_operation;
	    ISVREF(g2_stream_frame,(SI_Long)25L) = svref_new_value;
	}
	change_slot_description_value_function(g2_stream_frame,
		Name_of_file_slot_description,g2_filestring,Nil,Nil);
	change_slot_description_value_function(g2_stream_frame,
		Access_direction_slot_description,Qclosed,Nil,Nil);
    }
    reclaim_text_string(filestring);
    temp = internal_stream_qm ? copy_as_wide_string(string_constant_6) : 
	    most_recent_file_operation_status_as_text();
    return VALUES_2(g2_stream_frame,temp);
}

static Object Qopen_for_read_and_write;  /* open-for-read-and-write */

static Object Qinput_and_output;   /* input-and-output */

static Object Qfailed_to_open_for_read_and_write;  /* failed-to-open-for-read-and-write */

/* OPEN-FILE-FOR-READ-AND-WRITE-LISP-SIDE */
Object open_file_for_read_and_write_lisp_side(g2_filestring)
    Object g2_filestring;
{
    Object filestring, g2_stream_frame, internal_stream_qm, position_1;
    Object filesystem, svref_new_value, temp;

    x_note_fn_call(164,46);
    filestring = export_text_string(2,g2_filestring,Qg2_directory_pathname);
    g2_stream_frame = make_transient_item(Qg2_stream);
    internal_stream_qm = EQ(Local_file_system,Qwin32) || 
	    EQ(Local_file_system,Qdos) ? 
	    g2_stream_open_for_random_access_binary_io(filestring) : 
	    g2_stream_open_for_random_access_io(filestring);
    if (internal_stream_qm) {
	position_1 = g2_stream_get_file_position(internal_stream_qm);
	filesystem = 
		get_filesystem_from_g2_stream_for_user(internal_stream_qm);
	if ( !EQ(Qopen_for_read_and_write,ISVREF(g2_stream_frame,
		(SI_Long)24L)))
	    change_slot_description_value_function(g2_stream_frame,
		    G2_stream_status_slot_description,
		    Qopen_for_read_and_write,Nil,Nil);
	if (internal_stream_qm) {
	    svref_new_value = Internal_status_of_most_recent_file_operation;
	    ISVREF(g2_stream_frame,(SI_Long)25L) = svref_new_value;
	}
	change_slot_description_value_function(g2_stream_frame,
		Name_of_file_slot_description,g2_filestring,Nil,Nil);
	change_slot_description_value_function(g2_stream_frame,
		Access_direction_slot_description,Qinput_and_output,Nil,Nil);
	change_slot_description_value_function(g2_stream_frame,
		Position_in_file_slot_description,position_1,Nil,Nil);
	ISVREF(g2_stream_frame,(SI_Long)26L) = internal_stream_qm;
	change_slot_description_value_function(g2_stream_frame,
		File_system_slot_description,filesystem,Nil,Nil);
	svref_new_value = 
		obtain_simple_text_string(Size_of_g2_stream_frame_input_buffer);
	ISVREF(g2_stream_frame,(SI_Long)27L) = svref_new_value;
    }
    else {
	if ( !EQ(Qfailed_to_open_for_read_and_write,ISVREF(g2_stream_frame,
		(SI_Long)24L)))
	    change_slot_description_value_function(g2_stream_frame,
		    G2_stream_status_slot_description,
		    Qfailed_to_open_for_read_and_write,Nil,Nil);
	if (internal_stream_qm) {
	    svref_new_value = Internal_status_of_most_recent_file_operation;
	    ISVREF(g2_stream_frame,(SI_Long)25L) = svref_new_value;
	}
	change_slot_description_value_function(g2_stream_frame,
		Name_of_file_slot_description,g2_filestring,Nil,Nil);
	change_slot_description_value_function(g2_stream_frame,
		Access_direction_slot_description,Qclosed,Nil,Nil);
    }
    reclaim_text_string(filestring);
    temp = internal_stream_qm ? copy_as_wide_string(string_constant_6) : 
	    most_recent_file_operation_status_as_text();
    return VALUES_2(g2_stream_frame,temp);
}

/* CLOSE-FILE-LISP-SIDE-UNWRAPPED */
Object close_file_lisp_side_unwrapped(g2_stream_frame)
    Object g2_stream_frame;
{
    x_note_fn_call(164,47);
    delete_frame(g2_stream_frame);
    return VALUES_1(T);
}

/* CLOSE-FILE-LISP-SIDE */
Object close_file_lisp_side(g2_stream_frame)
    Object g2_stream_frame;
{
    Object status, temp, temp_1;

    x_note_fn_call(164,48);
    status = close_file_lisp_side_unwrapped(g2_stream_frame);
    if (status) {
	temp = Evaluation_true_value;
	temp_1 = copy_as_wide_string(string_constant_6);
	return VALUES_2(temp,temp_1);
    }
    else {
	temp = Evaluation_false_value;
	temp_1 = most_recent_file_operation_status_as_text();
	return VALUES_2(temp,temp_1);
    }
}

static Object Qsuccessfully_closed;  /* successfully-closed */

static Object Qfailed_to_close;    /* failed-to-close */

static Object Qtried_to_close_when_already_closed;  /* tried-to-close-when-already-closed */

/* CLOSE-FILE-LEAVING-STREAM-LISP-SIDE-UNWRAPPED */
Object close_file_leaving_stream_lisp_side_unwrapped(g2_stream_frame)
    Object g2_stream_frame;
{
    Object internal_g2_stream_qm, svref_new_value;

    x_note_fn_call(164,49);
    internal_g2_stream_qm = ISVREF(g2_stream_frame,(SI_Long)26L);
    if (internal_g2_stream_qm) {
	if (g2_stream_close(internal_g2_stream_qm)) {
	    if ( !EQ(Qsuccessfully_closed,ISVREF(g2_stream_frame,
		    (SI_Long)24L)))
		change_slot_description_value_function(g2_stream_frame,
			G2_stream_status_slot_description,
			Qsuccessfully_closed,Nil,Nil);
	    if (internal_g2_stream_qm) {
		svref_new_value = 
			Internal_status_of_most_recent_file_operation;
		ISVREF(g2_stream_frame,(SI_Long)25L) = svref_new_value;
	    }
	    change_slot_description_value_function(g2_stream_frame,
		    Access_direction_slot_description,Qclosed,Nil,Nil);
	    change_slot_description_value_function(g2_stream_frame,
		    Position_in_file_slot_description,Nil,Nil,Nil);
	    ISVREF(g2_stream_frame,(SI_Long)26L) = Nil;
	    change_slot_description_value_function(g2_stream_frame,
		    File_system_slot_description,Nil,Nil,Nil);
	    return VALUES_1(T);
	}
	else {
	    if ( !EQ(Qfailed_to_close,ISVREF(g2_stream_frame,(SI_Long)24L)))
		change_slot_description_value_function(g2_stream_frame,
			G2_stream_status_slot_description,Qfailed_to_close,
			Nil,Nil);
	    if (internal_g2_stream_qm) {
		svref_new_value = 
			Internal_status_of_most_recent_file_operation;
		ISVREF(g2_stream_frame,(SI_Long)25L) = svref_new_value;
	    }
	    change_slot_description_value_function(g2_stream_frame,
		    Access_direction_slot_description,Nil,Nil,Nil);
	    change_slot_description_value_function(g2_stream_frame,
		    Position_in_file_slot_description,Nil,Nil,Nil);
	    ISVREF(g2_stream_frame,(SI_Long)26L) = Nil;
	    change_slot_description_value_function(g2_stream_frame,
		    File_system_slot_description,Nil,Nil,Nil);
	    return VALUES_1(Nil);
	}
    }
    else {
	if ( !EQ(Qtried_to_close_when_already_closed,
		ISVREF(g2_stream_frame,(SI_Long)24L)))
	    change_slot_description_value_function(g2_stream_frame,
		    G2_stream_status_slot_description,
		    Qtried_to_close_when_already_closed,Nil,Nil);
	if (internal_g2_stream_qm) {
	    svref_new_value = Internal_status_of_most_recent_file_operation;
	    ISVREF(g2_stream_frame,(SI_Long)25L) = svref_new_value;
	}
	return VALUES_1(Nil);
    }
}

/* CLOSE-FILE-LEAVING-STREAM-LISP-SIDE */
Object close_file_leaving_stream_lisp_side(g2_stream_frame)
    Object g2_stream_frame;
{
    Object status;

    x_note_fn_call(164,50);
    status = close_file_lisp_side_unwrapped(g2_stream_frame);
    if (status)
	return VALUES_1(Evaluation_true_value);
    else
	return VALUES_1(Evaluation_false_value);
}

/* CLOSE-ALL-OPEN-G2-STREAMS-LISP-SIDE */
Object close_all_open_g2_streams_lisp_side()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, g2_stream_frame;
    Object cumulative_result, this_result;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(164,51);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    g2_stream_frame = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      cumulative_result = T;
      ab_loopvar_ = collect_subclasses(Qg2_stream);
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
      g2_stream_frame = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      if (ISVREF(g2_stream_frame,(SI_Long)26L)) {
	  this_result = close_file_lisp_side_unwrapped(g2_stream_frame);
	  cumulative_result = cumulative_result ? this_result : Qnil;
      }
      goto next_loop;
    end_loop_1:
      if (cumulative_result)
	  result = VALUES_1(Evaluation_true_value);
      else
	  result = VALUES_1(Evaluation_false_value);
      goto end_1;
      result = VALUES_1(Qnil);
    end_1:;
    POP_SPECIAL();
    return result;
}

static Object string_constant_7;   /* "Tried to set file position past end-of-file" */

static Object Qsuccessfully_updated_position;  /* successfully-updated-position */

static Object Qfailed_to_update_position;  /* failed-to-update-position */

static Object Qtried_to_update_position_when_closed;  /* tried-to-update-position-when-closed */

static Object string_constant_8;   /* "Cannot update position of closed stream" */

/* SET-FILE-POSITION-LISP-SIDE */
Object set_file_position_lisp_side(g2_stream_frame,g2_new_position,
	    extend_file_if_necessary)
    Object g2_stream_frame, g2_new_position, extend_file_if_necessary;
{
    Object internal_g2_stream_qm, temp, extend_file_if_necessary_p;
    Object new_position, position_at_eof_qm, successful_p, temp_1;
    Object svref_new_value;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(164,52);
    internal_g2_stream_qm = ISVREF(g2_stream_frame,(SI_Long)26L);
    temp = evaluation_truth_value_is_true_p(extend_file_if_necessary);
    if ( !(EQ(extend_file_if_necessary,Evaluation_true_value) || 
	    EQ(extend_file_if_necessary,Evaluation_false_value)))
	reclaim_eval_cons_1(extend_file_if_necessary);
    extend_file_if_necessary_p = temp;
    if (internal_g2_stream_qm) {
	temp = g2_new_position;
	new_position = temp;
	position_at_eof_qm = g2_stream_file_length(internal_g2_stream_qm);
	successful_p = Nil;
	if (position_at_eof_qm) {
	    if (FIXNUM_GT(new_position,position_at_eof_qm) && 
		    extend_file_if_necessary_p) {
		if (g2_stream_set_file_position(internal_g2_stream_qm,
			position_at_eof_qm,FIX((SI_Long)0L))) {
		    index_1 = (SI_Long)0L;
		    ab_loop_bind_ = IFIX(FIXNUM_MINUS(new_position,
			    position_at_eof_qm));
		  next_loop:
		    if (index_1 >= ab_loop_bind_)
			goto end_loop;
		    if ( !TRUEP(g2_stream_write_char(CHR(' '),
			    internal_g2_stream_qm))) {
			successful_p = Nil;
			goto end_1;
		    }
		    index_1 = index_1 + (SI_Long)1L;
		    goto next_loop;
		  end_loop:
		    successful_p = T;
		    goto end_1;
		    successful_p = Qnil;
		  end_1:;
		}
		else
		    successful_p = Nil;
	    }
	    else if (FIXNUM_GT(new_position,position_at_eof_qm)) {
		temp_1 = Evaluation_false_value;
		temp = copy_as_wide_string(string_constant_7);
		return VALUES_2(temp_1,temp);
	    }
	    else
		successful_p = 
			g2_stream_set_file_position(internal_g2_stream_qm,
			new_position,FIX((SI_Long)0L));
	}
	if (successful_p) {
	    ISVREF(g2_stream_frame,(SI_Long)30L) = new_position;
	    ISVREF(g2_stream_frame,(SI_Long)28L) = FIX((SI_Long)0L);
	    ISVREF(g2_stream_frame,(SI_Long)29L) = FIX((SI_Long)0L);
	    if ( !EQ(Qsuccessfully_updated_position,ISVREF(g2_stream_frame,
		    (SI_Long)24L)))
		change_slot_description_value_function(g2_stream_frame,
			G2_stream_status_slot_description,
			Qsuccessfully_updated_position,Nil,Nil);
	    if (internal_g2_stream_qm) {
		svref_new_value = 
			Internal_status_of_most_recent_file_operation;
		ISVREF(g2_stream_frame,(SI_Long)25L) = svref_new_value;
	    }
	    change_slot_description_value_function(g2_stream_frame,
		    Position_in_file_slot_description,new_position,Nil,Nil);
	    temp_1 = Evaluation_true_value;
	    temp = copy_as_wide_string(string_constant_6);
	    return VALUES_2(temp_1,temp);
	}
	else {
	    if ( !EQ(Qfailed_to_update_position,ISVREF(g2_stream_frame,
		    (SI_Long)24L)))
		change_slot_description_value_function(g2_stream_frame,
			G2_stream_status_slot_description,
			Qfailed_to_update_position,Nil,Nil);
	    if (internal_g2_stream_qm) {
		svref_new_value = 
			Internal_status_of_most_recent_file_operation;
		ISVREF(g2_stream_frame,(SI_Long)25L) = svref_new_value;
	    }
	    temp_1 = Evaluation_false_value;
	    temp = most_recent_file_operation_status_as_text();
	    return VALUES_2(temp_1,temp);
	}
    }
    else {
	if ( !EQ(Qtried_to_update_position_when_closed,
		ISVREF(g2_stream_frame,(SI_Long)24L)))
	    change_slot_description_value_function(g2_stream_frame,
		    G2_stream_status_slot_description,
		    Qtried_to_update_position_when_closed,Nil,Nil);
	if (internal_g2_stream_qm) {
	    svref_new_value = Internal_status_of_most_recent_file_operation;
	    ISVREF(g2_stream_frame,(SI_Long)25L) = svref_new_value;
	}
	temp_1 = Evaluation_false_value;
	temp = copy_as_wide_string(string_constant_8);
	return VALUES_2(temp_1,temp);
    }
}

/* RENAME-FILE-LISP-SIDE */
Object rename_file_lisp_side(g2_old_filestring,g2_new_filestring)
    Object g2_old_filestring, g2_new_filestring;
{
    Object old_filestring, new_filestring, successful_p, temp, temp_1;

    x_note_fn_call(164,53);
    old_filestring = export_text_string(2,g2_old_filestring,
	    Qg2_directory_pathname);
    new_filestring = export_text_string(2,g2_new_filestring,
	    Qg2_directory_pathname);
    successful_p = g2_stream_rename_file(old_filestring,new_filestring);
    reclaim_text_string(g2_old_filestring);
    reclaim_text_string(g2_new_filestring);
    reclaim_text_string(old_filestring);
    reclaim_text_string(new_filestring);
    if (successful_p) {
	temp = Evaluation_true_value;
	temp_1 = copy_as_wide_string(string_constant_6);
	return VALUES_2(temp,temp_1);
    }
    else {
	temp = Evaluation_false_value;
	temp_1 = most_recent_file_operation_status_as_text();
	return VALUES_2(temp,temp_1);
    }
}

/* COPY-FILE-LISP-SIDE */
Object copy_file_lisp_side(g2_old_filestring,g2_new_filestring)
    Object g2_old_filestring, g2_new_filestring;
{
    Object old_filestring, new_filestring, successful_p, temp, temp_1;

    x_note_fn_call(164,54);
    old_filestring = export_text_string(2,g2_old_filestring,
	    Qg2_directory_pathname);
    new_filestring = export_text_string(2,g2_new_filestring,
	    Qg2_directory_pathname);
    successful_p = g2_stream_copy_file(old_filestring,new_filestring);
    reclaim_text_string(g2_old_filestring);
    reclaim_text_string(g2_new_filestring);
    reclaim_text_string(old_filestring);
    reclaim_text_string(new_filestring);
    if (successful_p) {
	temp = Evaluation_true_value;
	temp_1 = copy_as_wide_string(string_constant_6);
	return VALUES_2(temp,temp_1);
    }
    else {
	temp = Evaluation_false_value;
	temp_1 = most_recent_file_operation_status_as_text();
	return VALUES_2(temp,temp_1);
    }
}

/* DELETE-FILE-LISP-SIDE */
Object delete_file_lisp_side(g2_filestring)
    Object g2_filestring;
{
    Object filestring, successful_p, temp, temp_1;

    x_note_fn_call(164,55);
    filestring = export_text_string(2,g2_filestring,Qg2_directory_pathname);
    successful_p = g2_stream_delete_file(filestring);
    reclaim_text_string(g2_filestring);
    reclaim_text_string(filestring);
    if (successful_p) {
	temp = Evaluation_true_value;
	temp_1 = copy_as_wide_string(string_constant_6);
	return VALUES_2(temp,temp_1);
    }
    else {
	temp = Evaluation_false_value;
	temp_1 = most_recent_file_operation_status_as_text();
	return VALUES_2(temp,temp_1);
    }
}

static Object Qtried_read_line_on_stream_not_opened_for_read;  /* tried-read-line-on-stream-not-opened-for-read */

static Object Qunicode;            /* unicode */

static Object Qunicode_byte_swapped;  /* unicode-byte-swapped */

static Object Qunicode_ucs_2;      /* unicode-ucs-2 */

static Object Qunicode_ucs_2_byte_swapped;  /* unicode-ucs-2-byte-swapped */

static Object Qus_ascii;           /* us-ascii */

static Object Qlatin_1;            /* latin-1 */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object Qutf_g;              /* utf-g */

static Object Qab_gensym;          /* gensym */

static Object Qend_of_file_reached;  /* end-of-file-reached */

static Object Qerror_during_read_line;  /* error-during-read-line */

static Object Qline_truncated_during_read;  /* line-truncated-during-read */

static Object Qsuccessfully_read_line;  /* successfully-read-line */

static Object Qtried_read_line_when_closed;  /* tried-read-line-when-closed */

/* READ-LINE-LISP-SIDE */
Object read_line_lisp_side(g2_stream_frame)
    Object g2_stream_frame;
{
    Object internal_g2_stream_qm, result_text_string_qm, status_symbol;
    Object g2_input_stream, buffer, string_length_exceeded_p, style, temp;
    Object gensymed_symbol, charset, n_octets_per_character;
    Object n_2_octet_byte_swapped_p, preimported_p, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object character_qm, count_of_characters_read_qm, temp_4, incff_1_arg_1;
    Object peeked_character_qm, decff_1_arg, aref_arg_2;
    Object utf_g_uninteresting_so_far_p, temp_5, gensymed_symbol_3;
    Object gensymed_symbol_4, gensymed_symbol_5, gensymed_symbol_6;
    Object gensymed_symbol_7;
    SI_Long position_1, available_characters, offset, initial_file_position;
    SI_Long temp_1, bv16_length, aref_new_value, length_1, temp_2;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, incff_1_arg, char_1, char_2;
    SI_Long lead_octet, trail_octet, position_2;
    char temp_3;
    Declare_special(5);
    Object result;

    x_note_fn_call(164,56);
    internal_g2_stream_qm = ISVREF(g2_stream_frame,(SI_Long)26L);
    result_text_string_qm = Nil;
    if ( !(EQ(ISVREF(g2_stream_frame,(SI_Long)22L),Qinput) || 
	    EQ(ISVREF(g2_stream_frame,(SI_Long)22L),Qinput_and_output)))
	status_symbol = Qtried_read_line_on_stream_not_opened_for_read;
    else if (internal_g2_stream_qm) {
	g2_input_stream = internal_g2_stream_qm;
	position_1 = IFIX(ISVREF(g2_stream_frame,(SI_Long)28L));
	available_characters = IFIX(ISVREF(g2_stream_frame,(SI_Long)29L));
	buffer = ISVREF(g2_stream_frame,(SI_Long)27L);
	offset = IFIX(ISVREF(g2_stream_frame,(SI_Long)30L));
	initial_file_position = offset + position_1;
	string_length_exceeded_p = Nil;
	if ( !TRUEP(ISVREF(g2_stream_frame,(SI_Long)31L))) {
	    style = 
		    come_up_with_text_conversion_style_structure(get_lookup_slot_value_given_default(g2_stream_frame,
		    Qtext_conversion_style,Nil),Nil);
	    ISVREF(g2_stream_frame,(SI_Long)31L) = T;
	    temp = ISVREF(style,(SI_Long)2L);
	    ISVREF(g2_stream_frame,(SI_Long)32L) = temp;
	    gensymed_symbol = ISVREF(style,(SI_Long)2L);
	    temp_1 = EQ(gensymed_symbol,Qunicode) || EQ(gensymed_symbol,
		    Qunicode_byte_swapped) || EQ(gensymed_symbol,
		    Qunicode_ucs_2) || EQ(gensymed_symbol,
		    Qunicode_ucs_2_byte_swapped) ? (SI_Long)2L : (SI_Long)1L;
	    ISVREF(g2_stream_frame,(SI_Long)33L) = FIX(temp_1);
	    gensymed_symbol = ISVREF(style,(SI_Long)2L);
	    temp = EQ(gensymed_symbol,Qunicode_byte_swapped) || 
		    EQ(gensymed_symbol,Qunicode_ucs_2_byte_swapped) ? T : Nil;
	    ISVREF(g2_stream_frame,(SI_Long)34L) = temp;
	    gensymed_symbol = ISVREF(style,(SI_Long)2L);
	    temp = EQ(gensymed_symbol,Qus_ascii) ? T : Nil;
	    if (temp);
	    else
		temp = EQ(gensymed_symbol,Qlatin_1) ? T : Nil;
	    if (temp);
	    else
		temp = EQ(gensymed_symbol,Qunicode) ? T : Nil;
	    if (temp);
	    else
		temp = EQ(gensymed_symbol,Qunicode_byte_swapped) ? T : Nil;
	    if (temp);
	    else
		temp = EQ(gensymed_symbol,Qunicode_ucs_2) ? T : Nil;
	    if (temp);
	    else
		temp = EQ(gensymed_symbol,Qunicode_ucs_2_byte_swapped) ? T 
			: Nil;
	    ISVREF(g2_stream_frame,(SI_Long)35L) = temp;
	}
	charset = ISVREF(g2_stream_frame,(SI_Long)32L);
	n_octets_per_character = ISVREF(g2_stream_frame,(SI_Long)33L);
	n_2_octet_byte_swapped_p = ISVREF(g2_stream_frame,(SI_Long)34L);
	preimported_p = ISVREF(g2_stream_frame,(SI_Long)35L);
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
		  if (IFIX(n_octets_per_character) == (SI_Long)2L) {
		      character_qm = Nil;
		    next_loop:
		      temp_2 = position_1;
		      gensymed_symbol_1 = available_characters;
		      gensymed_symbol_2 = IFIX(n_octets_per_character) == 
			      (SI_Long)2L ? (SI_Long)1L : (SI_Long)0L;
		      temp_3 = temp_2 < gensymed_symbol_1 - gensymed_symbol_2;
		      if (temp_3);
		      else {
			  count_of_characters_read_qm = 
				  g2_stream_read_octets_into_wide_string_buffer(buffer,
				  Size_of_g2_stream_frame_input_buffer,
				  g2_input_stream);
			  temp_4 = count_of_characters_read_qm;
			  if (temp_4);
			  else
			      temp_4 = FIX((SI_Long)0L);
			  available_characters = IFIX(temp_4);
			  incff_1_arg = position_1;
			  offset = offset + incff_1_arg;
			  position_1 = (SI_Long)0L;
			  temp_3 = available_characters > 
				  (IFIX(n_octets_per_character) == 
				  (SI_Long)2L ? (SI_Long)1L : (SI_Long)0L);
		      }
		      if (temp_3) {
			  char_1 = UBYTE_16_ISAREF_1(buffer,position_1);
			  char_2 = (SI_Long)0L;
			  if (IFIX(n_octets_per_character) == (SI_Long)2L) {
			      char_2 = UBYTE_16_ISAREF_1(buffer,position_1 
				      + (SI_Long)1L);
			      if (n_2_octet_byte_swapped_p) {
				  lead_octet = char_2;
				  trail_octet = char_1;
				  gensymed_symbol_2 = lead_octet & 
					  (SI_Long)255L;
				  gensymed_symbol_1 = (SI_Long)8L;
				  gensymed_symbol_1 = gensymed_symbol_2 << 
					  gensymed_symbol_1;
				  gensymed_symbol_2 = trail_octet & 
					  (SI_Long)255L;
				  char_1 = gensymed_symbol_1 | 
					  gensymed_symbol_2;
			      }
			      else {
				  lead_octet = char_1;
				  trail_octet = char_2;
				  gensymed_symbol_2 = lead_octet & 
					  (SI_Long)255L;
				  gensymed_symbol_1 = (SI_Long)8L;
				  gensymed_symbol_1 = gensymed_symbol_2 << 
					  gensymed_symbol_1;
				  gensymed_symbol_2 = trail_octet & 
					  (SI_Long)255L;
				  char_1 = gensymed_symbol_1 | 
					  gensymed_symbol_2;
			      }
			  }
			  incff_1_arg_1 = n_octets_per_character;
			  position_1 = position_1 + IFIX(incff_1_arg_1);
			  character_qm = FIX(char_1);
		      }
		      else
			  character_qm = Nil;
		      if ( !TRUEP(character_qm) || IFIX(character_qm) == 
			      (SI_Long)10L || IFIX(character_qm) == 
			      (SI_Long)8232L || IFIX(character_qm) == 
			      (SI_Long)8233L)
			  goto end_loop;
		      else if (IFIX(character_qm) == (SI_Long)13L) {
			  temp_2 = position_1;
			  gensymed_symbol_1 = available_characters;
			  gensymed_symbol_2 = IFIX(n_octets_per_character) 
				  == (SI_Long)2L ? (SI_Long)1L : (SI_Long)0L;
			  temp_3 = temp_2 < gensymed_symbol_1 - 
				  gensymed_symbol_2;
			  if (temp_3);
			  else {
			      count_of_characters_read_qm = 
				      g2_stream_read_octets_into_wide_string_buffer(buffer,
				      Size_of_g2_stream_frame_input_buffer,
				      g2_input_stream);
			      temp_4 = count_of_characters_read_qm;
			      if (temp_4);
			      else
				  temp_4 = FIX((SI_Long)0L);
			      available_characters = IFIX(temp_4);
			      incff_1_arg = position_1;
			      offset = offset + incff_1_arg;
			      position_1 = (SI_Long)0L;
			      temp_3 = available_characters > 
				      (IFIX(n_octets_per_character) == 
				      (SI_Long)2L ? (SI_Long)1L : (SI_Long)0L);
			  }
			  if (temp_3) {
			      char_1 = UBYTE_16_ISAREF_1(buffer,position_1);
			      char_2 = (SI_Long)0L;
			      if (IFIX(n_octets_per_character) == 
					  (SI_Long)2L) {
				  char_2 = UBYTE_16_ISAREF_1(buffer,
					  position_1 + (SI_Long)1L);
				  if (n_2_octet_byte_swapped_p) {
				      lead_octet = char_2;
				      trail_octet = char_1;
				      gensymed_symbol_2 = lead_octet & 
					      (SI_Long)255L;
				      gensymed_symbol_1 = (SI_Long)8L;
				      gensymed_symbol_1 = 
					      gensymed_symbol_2 << 
					      gensymed_symbol_1;
				      gensymed_symbol_2 = trail_octet & 
					      (SI_Long)255L;
				      char_1 = gensymed_symbol_1 | 
					      gensymed_symbol_2;
				  }
				  else {
				      lead_octet = char_1;
				      trail_octet = char_2;
				      gensymed_symbol_2 = lead_octet & 
					      (SI_Long)255L;
				      gensymed_symbol_1 = (SI_Long)8L;
				      gensymed_symbol_1 = 
					      gensymed_symbol_2 << 
					      gensymed_symbol_1;
				      gensymed_symbol_2 = trail_octet & 
					      (SI_Long)255L;
				      char_1 = gensymed_symbol_1 | 
					      gensymed_symbol_2;
				  }
			      }
			      incff_1_arg_1 = n_octets_per_character;
			      position_1 = position_1 + IFIX(incff_1_arg_1);
			      peeked_character_qm = FIX(char_1);
			  }
			  else
			      peeked_character_qm = Nil;
			  if ( !(peeked_character_qm && 
				  IFIX(peeked_character_qm) == (SI_Long)10L)) {
			      decff_1_arg = n_octets_per_character;
			      position_1 = position_1 - IFIX(decff_1_arg);
			  }
			  goto end_loop;
		      }
		      else {
			  if (FIXNUM_GE(Fill_pointer_for_current_wide_string,
				  Maximum_length_for_user_text_strings)) {
			      string_length_exceeded_p = T;
			      goto end_loop;
			  }
			  if ( 
				  !FIXNUM_LT(Fill_pointer_for_current_wide_string,
				  Total_length_of_current_wide_string))
			      extend_current_wide_string(Fill_pointer_for_current_wide_string);
			  temp = Current_wide_string;
			  aref_arg_2 = Fill_pointer_for_current_wide_string;
			  UBYTE_16_ISASET_1(temp,IFIX(aref_arg_2),
				  IFIX(character_qm));
			  temp = 
				  FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
			  Fill_pointer_for_current_wide_string = temp;
		      }
		      goto next_loop;
		    end_loop:
		    nil:;
		  }
		  else if (EQ(charset,Qutf_g) || EQ(charset,Qab_gensym)) {
		      character_qm = Nil;
		      utf_g_uninteresting_so_far_p = EQ(charset,Qutf_g) ? 
			      T : Nil;
		      if (utf_g_uninteresting_so_far_p);
		      else
			  utf_g_uninteresting_so_far_p = EQ(charset,
				  Qab_gensym) ? T : Nil;
		    next_loop_1:
		      temp_2 = position_1;
		      gensymed_symbol_1 = available_characters;
		      gensymed_symbol_2 = IFIX(n_octets_per_character) == 
			      (SI_Long)2L ? (SI_Long)1L : (SI_Long)0L;
		      temp_3 = temp_2 < gensymed_symbol_1 - gensymed_symbol_2;
		      if (temp_3);
		      else {
			  count_of_characters_read_qm = 
				  g2_stream_read_octets_into_wide_string_buffer(buffer,
				  Size_of_g2_stream_frame_input_buffer,
				  g2_input_stream);
			  temp_4 = count_of_characters_read_qm;
			  if (temp_4);
			  else
			      temp_4 = FIX((SI_Long)0L);
			  available_characters = IFIX(temp_4);
			  incff_1_arg = position_1;
			  offset = offset + incff_1_arg;
			  position_1 = (SI_Long)0L;
			  temp_3 = available_characters > 
				  (IFIX(n_octets_per_character) == 
				  (SI_Long)2L ? (SI_Long)1L : (SI_Long)0L);
		      }
		      if (temp_3) {
			  char_1 = UBYTE_16_ISAREF_1(buffer,position_1);
			  char_2 = (SI_Long)0L;
			  if (IFIX(n_octets_per_character) == (SI_Long)2L) {
			      char_2 = UBYTE_16_ISAREF_1(buffer,position_1 
				      + (SI_Long)1L);
			      if (n_2_octet_byte_swapped_p) {
				  lead_octet = char_2;
				  trail_octet = char_1;
				  gensymed_symbol_2 = lead_octet & 
					  (SI_Long)255L;
				  gensymed_symbol_1 = (SI_Long)8L;
				  gensymed_symbol_1 = gensymed_symbol_2 << 
					  gensymed_symbol_1;
				  gensymed_symbol_2 = trail_octet & 
					  (SI_Long)255L;
				  char_1 = gensymed_symbol_1 | 
					  gensymed_symbol_2;
			      }
			      else {
				  lead_octet = char_1;
				  trail_octet = char_2;
				  gensymed_symbol_2 = lead_octet & 
					  (SI_Long)255L;
				  gensymed_symbol_1 = (SI_Long)8L;
				  gensymed_symbol_1 = gensymed_symbol_2 << 
					  gensymed_symbol_1;
				  gensymed_symbol_2 = trail_octet & 
					  (SI_Long)255L;
				  char_1 = gensymed_symbol_1 | 
					  gensymed_symbol_2;
			      }
			  }
			  incff_1_arg_1 = n_octets_per_character;
			  position_1 = position_1 + IFIX(incff_1_arg_1);
			  character_qm = FIX(char_1);
		      }
		      else
			  character_qm = Nil;
		      if ( !TRUEP(character_qm) || IFIX(character_qm) == 
			      (SI_Long)10L)
			  goto end_loop_1;
		      else if (IFIX(character_qm) == (SI_Long)13L) {
			  temp_2 = position_1;
			  gensymed_symbol_1 = available_characters;
			  gensymed_symbol_2 = IFIX(n_octets_per_character) 
				  == (SI_Long)2L ? (SI_Long)1L : (SI_Long)0L;
			  temp_3 = temp_2 < gensymed_symbol_1 - 
				  gensymed_symbol_2;
			  if (temp_3);
			  else {
			      count_of_characters_read_qm = 
				      g2_stream_read_octets_into_wide_string_buffer(buffer,
				      Size_of_g2_stream_frame_input_buffer,
				      g2_input_stream);
			      temp_4 = count_of_characters_read_qm;
			      if (temp_4);
			      else
				  temp_4 = FIX((SI_Long)0L);
			      available_characters = IFIX(temp_4);
			      incff_1_arg = position_1;
			      offset = offset + incff_1_arg;
			      position_1 = (SI_Long)0L;
			      temp_3 = available_characters > 
				      (IFIX(n_octets_per_character) == 
				      (SI_Long)2L ? (SI_Long)1L : (SI_Long)0L);
			  }
			  if (temp_3) {
			      char_1 = UBYTE_16_ISAREF_1(buffer,position_1);
			      char_2 = (SI_Long)0L;
			      if (IFIX(n_octets_per_character) == 
					  (SI_Long)2L) {
				  char_2 = UBYTE_16_ISAREF_1(buffer,
					  position_1 + (SI_Long)1L);
				  if (n_2_octet_byte_swapped_p) {
				      lead_octet = char_2;
				      trail_octet = char_1;
				      gensymed_symbol_2 = lead_octet & 
					      (SI_Long)255L;
				      gensymed_symbol_1 = (SI_Long)8L;
				      gensymed_symbol_1 = 
					      gensymed_symbol_2 << 
					      gensymed_symbol_1;
				      gensymed_symbol_2 = trail_octet & 
					      (SI_Long)255L;
				      char_1 = gensymed_symbol_1 | 
					      gensymed_symbol_2;
				  }
				  else {
				      lead_octet = char_1;
				      trail_octet = char_2;
				      gensymed_symbol_2 = lead_octet & 
					      (SI_Long)255L;
				      gensymed_symbol_1 = (SI_Long)8L;
				      gensymed_symbol_1 = 
					      gensymed_symbol_2 << 
					      gensymed_symbol_1;
				      gensymed_symbol_2 = trail_octet & 
					      (SI_Long)255L;
				      char_1 = gensymed_symbol_1 | 
					      gensymed_symbol_2;
				  }
			      }
			      incff_1_arg_1 = n_octets_per_character;
			      position_1 = position_1 + IFIX(incff_1_arg_1);
			      peeked_character_qm = FIX(char_1);
			  }
			  else
			      peeked_character_qm = Nil;
			  if ( !(peeked_character_qm && 
				  IFIX(peeked_character_qm) == (SI_Long)10L)) {
			      decff_1_arg = n_octets_per_character;
			      position_1 = position_1 - IFIX(decff_1_arg);
			  }
			  goto end_loop_1;
		      }
		      else {
			  if (FIXNUM_GE(Fill_pointer_for_current_wide_string,
				  Maximum_length_for_user_text_strings)) {
			      string_length_exceeded_p = T;
			      goto end_loop_1;
			  }
			  if (utf_g_uninteresting_so_far_p && 
				  (IFIX(character_qm) == (SI_Long)126L || 
				  IFIX(character_qm) == (SI_Long)64L || 
				  IFIX(character_qm) == (SI_Long)92L))
			      utf_g_uninteresting_so_far_p = Nil;
			  if ( 
				  !FIXNUM_LT(Fill_pointer_for_current_wide_string,
				  Total_length_of_current_wide_string))
			      extend_current_wide_string(Fill_pointer_for_current_wide_string);
			  temp = Current_wide_string;
			  aref_arg_2 = Fill_pointer_for_current_wide_string;
			  UBYTE_16_ISASET_1(temp,IFIX(aref_arg_2),
				  IFIX(character_qm));
			  temp = 
				  FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
			  Fill_pointer_for_current_wide_string = temp;
		      }
		      goto next_loop_1;
		    end_loop_1:
		      if (utf_g_uninteresting_so_far_p && (EQ(charset,
			      Qutf_g) || EQ(charset,Qab_gensym)))
			  preimported_p = T;
		  }
		  else {
		      character_qm = Nil;
		    next_loop_2:
		      temp_2 = position_1;
		      gensymed_symbol_1 = available_characters;
		      gensymed_symbol_2 = IFIX(n_octets_per_character) == 
			      (SI_Long)2L ? (SI_Long)1L : (SI_Long)0L;
		      temp_3 = temp_2 < gensymed_symbol_1 - gensymed_symbol_2;
		      if (temp_3);
		      else {
			  count_of_characters_read_qm = 
				  g2_stream_read_octets_into_wide_string_buffer(buffer,
				  Size_of_g2_stream_frame_input_buffer,
				  g2_input_stream);
			  temp_4 = count_of_characters_read_qm;
			  if (temp_4);
			  else
			      temp_4 = FIX((SI_Long)0L);
			  available_characters = IFIX(temp_4);
			  incff_1_arg = position_1;
			  offset = offset + incff_1_arg;
			  position_1 = (SI_Long)0L;
			  temp_3 = available_characters > 
				  (IFIX(n_octets_per_character) == 
				  (SI_Long)2L ? (SI_Long)1L : (SI_Long)0L);
		      }
		      if (temp_3) {
			  char_1 = UBYTE_16_ISAREF_1(buffer,position_1);
			  char_2 = (SI_Long)0L;
			  if (IFIX(n_octets_per_character) == (SI_Long)2L) {
			      char_2 = UBYTE_16_ISAREF_1(buffer,position_1 
				      + (SI_Long)1L);
			      if (n_2_octet_byte_swapped_p) {
				  lead_octet = char_2;
				  trail_octet = char_1;
				  gensymed_symbol_2 = lead_octet & 
					  (SI_Long)255L;
				  gensymed_symbol_1 = (SI_Long)8L;
				  gensymed_symbol_1 = gensymed_symbol_2 << 
					  gensymed_symbol_1;
				  gensymed_symbol_2 = trail_octet & 
					  (SI_Long)255L;
				  char_1 = gensymed_symbol_1 | 
					  gensymed_symbol_2;
			      }
			      else {
				  lead_octet = char_1;
				  trail_octet = char_2;
				  gensymed_symbol_2 = lead_octet & 
					  (SI_Long)255L;
				  gensymed_symbol_1 = (SI_Long)8L;
				  gensymed_symbol_1 = gensymed_symbol_2 << 
					  gensymed_symbol_1;
				  gensymed_symbol_2 = trail_octet & 
					  (SI_Long)255L;
				  char_1 = gensymed_symbol_1 | 
					  gensymed_symbol_2;
			      }
			  }
			  incff_1_arg_1 = n_octets_per_character;
			  position_1 = position_1 + IFIX(incff_1_arg_1);
			  character_qm = FIX(char_1);
		      }
		      else
			  character_qm = Nil;
		      if ( !TRUEP(character_qm) || IFIX(character_qm) == 
			      (SI_Long)10L)
			  goto end_loop_2;
		      else if (IFIX(character_qm) == (SI_Long)13L) {
			  temp_2 = position_1;
			  gensymed_symbol_1 = available_characters;
			  gensymed_symbol_2 = IFIX(n_octets_per_character) 
				  == (SI_Long)2L ? (SI_Long)1L : (SI_Long)0L;
			  temp_3 = temp_2 < gensymed_symbol_1 - 
				  gensymed_symbol_2;
			  if (temp_3);
			  else {
			      count_of_characters_read_qm = 
				      g2_stream_read_octets_into_wide_string_buffer(buffer,
				      Size_of_g2_stream_frame_input_buffer,
				      g2_input_stream);
			      temp_4 = count_of_characters_read_qm;
			      if (temp_4);
			      else
				  temp_4 = FIX((SI_Long)0L);
			      available_characters = IFIX(temp_4);
			      incff_1_arg = position_1;
			      offset = offset + incff_1_arg;
			      position_1 = (SI_Long)0L;
			      temp_3 = available_characters > 
				      (IFIX(n_octets_per_character) == 
				      (SI_Long)2L ? (SI_Long)1L : (SI_Long)0L);
			  }
			  if (temp_3) {
			      char_1 = UBYTE_16_ISAREF_1(buffer,position_1);
			      char_2 = (SI_Long)0L;
			      if (IFIX(n_octets_per_character) == 
					  (SI_Long)2L) {
				  char_2 = UBYTE_16_ISAREF_1(buffer,
					  position_1 + (SI_Long)1L);
				  if (n_2_octet_byte_swapped_p) {
				      lead_octet = char_2;
				      trail_octet = char_1;
				      gensymed_symbol_2 = lead_octet & 
					      (SI_Long)255L;
				      gensymed_symbol_1 = (SI_Long)8L;
				      gensymed_symbol_1 = 
					      gensymed_symbol_2 << 
					      gensymed_symbol_1;
				      gensymed_symbol_2 = trail_octet & 
					      (SI_Long)255L;
				      char_1 = gensymed_symbol_1 | 
					      gensymed_symbol_2;
				  }
				  else {
				      lead_octet = char_1;
				      trail_octet = char_2;
				      gensymed_symbol_2 = lead_octet & 
					      (SI_Long)255L;
				      gensymed_symbol_1 = (SI_Long)8L;
				      gensymed_symbol_1 = 
					      gensymed_symbol_2 << 
					      gensymed_symbol_1;
				      gensymed_symbol_2 = trail_octet & 
					      (SI_Long)255L;
				      char_1 = gensymed_symbol_1 | 
					      gensymed_symbol_2;
				  }
			      }
			      incff_1_arg_1 = n_octets_per_character;
			      position_1 = position_1 + IFIX(incff_1_arg_1);
			      peeked_character_qm = FIX(char_1);
			  }
			  else
			      peeked_character_qm = Nil;
			  if ( !(peeked_character_qm && 
				  IFIX(peeked_character_qm) == (SI_Long)10L)) {
			      decff_1_arg = n_octets_per_character;
			      position_1 = position_1 - IFIX(decff_1_arg);
			  }
			  goto end_loop_2;
		      }
		      else {
			  if (FIXNUM_GE(Fill_pointer_for_current_wide_string,
				  Maximum_length_for_user_text_strings)) {
			      string_length_exceeded_p = T;
			      goto end_loop_2;
			  }
			  if ( 
				  !FIXNUM_LT(Fill_pointer_for_current_wide_string,
				  Total_length_of_current_wide_string))
			      extend_current_wide_string(Fill_pointer_for_current_wide_string);
			  temp = Current_wide_string;
			  aref_arg_2 = Fill_pointer_for_current_wide_string;
			  UBYTE_16_ISASET_1(temp,IFIX(aref_arg_2),
				  IFIX(character_qm));
			  temp = 
				  FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
			  Fill_pointer_for_current_wide_string = temp;
		      }
		      goto next_loop_2;
		    end_loop_2:
		    nil_1:;
		  }
		  if ( !(offset + position_1 > initial_file_position)) {
		      if (g2_stream_eof_p(internal_g2_stream_qm))
			  result = VALUES_1(Qend_of_file_reached);
		      else
			  result = VALUES_1(Qerror_during_read_line);
		  }
		  else {
		      position_2 = offset + position_1;
		      change_slot_description_value_function(g2_stream_frame,
			      Position_in_file_slot_description,
			      FIX(position_2),Nil,Nil);
		      if (preimported_p)
			  result_text_string_qm = copy_current_wide_string();
		      else {
			  temp_5 = Current_wide_string;
			  temp_4 = 
				  come_up_with_text_conversion_style_structure(get_lookup_slot_value_given_default(g2_stream_frame,
				  Qtext_conversion_style,Nil),Nil);
			  result_text_string_qm = 
				  import_text_string_per_text_conversion_style(4,
				  temp_5,temp_4,FIX((SI_Long)0L),
				  Fill_pointer_for_current_wide_string);
		      }
		      if (string_length_exceeded_p)
			  result = VALUES_1(Qline_truncated_during_read);
		      else
			  result = VALUES_1(Qsuccessfully_read_line);
		  }
		  MVS_6(result,gensymed_symbol,gensymed_symbol_3,
			  gensymed_symbol_4,gensymed_symbol_5,
			  gensymed_symbol_6,gensymed_symbol_7);
		  reclaim_wide_string(Current_wide_string);
		  temp_4 = gensymed_symbol;
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	ISVREF(g2_stream_frame,(SI_Long)28L) = FIX(position_1);
	ISVREF(g2_stream_frame,(SI_Long)29L) = FIX(available_characters);
	ISVREF(g2_stream_frame,(SI_Long)30L) = FIX(offset);
	status_symbol = temp_4;
    }
    else
	status_symbol = Qtried_read_line_when_closed;
    if ( !EQ(status_symbol,ISVREF(g2_stream_frame,(SI_Long)24L)))
	change_slot_description_value_function(g2_stream_frame,
		G2_stream_status_slot_description,status_symbol,Nil,Nil);
    if (internal_g2_stream_qm) {
	temp = Internal_status_of_most_recent_file_operation;
	ISVREF(g2_stream_frame,(SI_Long)25L) = temp;
    }
    temp_4 = result_text_string_qm;
    if (temp_4);
    else {
	wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)0L + 
		(SI_Long)3L));
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	temp_1 = bv16_length - (SI_Long)2L;
	aref_new_value = (SI_Long)0L & (SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16,temp_1,aref_new_value);
	temp_1 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	UBYTE_16_ISASET_1(wide_string_bv16,temp_1,aref_new_value);
	UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)0L,(SI_Long)0L);
	temp_4 = wide_string_bv16;
    }
    return VALUES_2(temp_4,status_symbol);
}

/* READ-NEXT-CHAR-FOR-G2-STREAM-FRAME */
Object read_next_char_for_g2_stream_frame(g2_stream_frame,g2_input_stream)
    Object g2_stream_frame, g2_input_stream;
{
    Object buffer, string_length_exceeded_p, style, svref_new_value;
    Object gensymed_symbol, charset, n_octets_per_character;
    Object n_2_octet_byte_swapped_p, preimported_p;
    Object count_of_characters_read_qm, temp_2, incff_1_arg_1;
    SI_Long position_1, available_characters, offset, initial_file_position;
    SI_Long svref_new_value_1, temp, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long incff_1_arg, char_1, char_2, lead_octet, trail_octet;
    char temp_1;

    x_note_fn_call(164,57);
    position_1 = IFIX(ISVREF(g2_stream_frame,(SI_Long)28L));
    available_characters = IFIX(ISVREF(g2_stream_frame,(SI_Long)29L));
    buffer = ISVREF(g2_stream_frame,(SI_Long)27L);
    offset = IFIX(ISVREF(g2_stream_frame,(SI_Long)30L));
    initial_file_position = offset + position_1;
    string_length_exceeded_p = Nil;
    if ( !TRUEP(ISVREF(g2_stream_frame,(SI_Long)31L))) {
	style = 
		come_up_with_text_conversion_style_structure(get_lookup_slot_value_given_default(g2_stream_frame,
		Qtext_conversion_style,Nil),Nil);
	ISVREF(g2_stream_frame,(SI_Long)31L) = T;
	svref_new_value = ISVREF(style,(SI_Long)2L);
	ISVREF(g2_stream_frame,(SI_Long)32L) = svref_new_value;
	gensymed_symbol = ISVREF(style,(SI_Long)2L);
	svref_new_value_1 = EQ(gensymed_symbol,Qunicode) || 
		EQ(gensymed_symbol,Qunicode_byte_swapped) || 
		EQ(gensymed_symbol,Qunicode_ucs_2) || EQ(gensymed_symbol,
		Qunicode_ucs_2_byte_swapped) ? (SI_Long)2L : (SI_Long)1L;
	ISVREF(g2_stream_frame,(SI_Long)33L) = FIX(svref_new_value_1);
	gensymed_symbol = ISVREF(style,(SI_Long)2L);
	svref_new_value = EQ(gensymed_symbol,Qunicode_byte_swapped) || 
		EQ(gensymed_symbol,Qunicode_ucs_2_byte_swapped) ? T : Nil;
	ISVREF(g2_stream_frame,(SI_Long)34L) = svref_new_value;
	gensymed_symbol = ISVREF(style,(SI_Long)2L);
	svref_new_value = EQ(gensymed_symbol,Qus_ascii) ? T : Nil;
	if (svref_new_value);
	else
	    svref_new_value = EQ(gensymed_symbol,Qlatin_1) ? T : Nil;
	if (svref_new_value);
	else
	    svref_new_value = EQ(gensymed_symbol,Qunicode) ? T : Nil;
	if (svref_new_value);
	else
	    svref_new_value = EQ(gensymed_symbol,Qunicode_byte_swapped) ? 
		    T : Nil;
	if (svref_new_value);
	else
	    svref_new_value = EQ(gensymed_symbol,Qunicode_ucs_2) ? T : Nil;
	if (svref_new_value);
	else
	    svref_new_value = EQ(gensymed_symbol,
		    Qunicode_ucs_2_byte_swapped) ? T : Nil;
	ISVREF(g2_stream_frame,(SI_Long)35L) = svref_new_value;
    }
    charset = ISVREF(g2_stream_frame,(SI_Long)32L);
    n_octets_per_character = ISVREF(g2_stream_frame,(SI_Long)33L);
    n_2_octet_byte_swapped_p = ISVREF(g2_stream_frame,(SI_Long)34L);
    preimported_p = ISVREF(g2_stream_frame,(SI_Long)35L);
    temp = position_1;
    gensymed_symbol_1 = available_characters;
    gensymed_symbol_2 = IFIX(n_octets_per_character) == (SI_Long)2L ? 
	    (SI_Long)1L : (SI_Long)0L;
    temp_1 = temp < gensymed_symbol_1 - gensymed_symbol_2;
    if (temp_1);
    else {
	count_of_characters_read_qm = 
		g2_stream_read_octets_into_wide_string_buffer(buffer,
		Size_of_g2_stream_frame_input_buffer,g2_input_stream);
	temp_2 = count_of_characters_read_qm;
	if (temp_2);
	else
	    temp_2 = FIX((SI_Long)0L);
	available_characters = IFIX(temp_2);
	incff_1_arg = position_1;
	offset = offset + incff_1_arg;
	position_1 = (SI_Long)0L;
	temp_1 = available_characters > (IFIX(n_octets_per_character) == 
		(SI_Long)2L ? (SI_Long)1L : (SI_Long)0L);
    }
    if (temp_1) {
	char_1 = UBYTE_16_ISAREF_1(buffer,position_1);
	char_2 = (SI_Long)0L;
	if (IFIX(n_octets_per_character) == (SI_Long)2L) {
	    char_2 = UBYTE_16_ISAREF_1(buffer,position_1 + (SI_Long)1L);
	    if (n_2_octet_byte_swapped_p) {
		lead_octet = char_2;
		trail_octet = char_1;
		gensymed_symbol_2 = lead_octet & (SI_Long)255L;
		gensymed_symbol_1 = (SI_Long)8L;
		gensymed_symbol_1 = gensymed_symbol_2 << gensymed_symbol_1;
		gensymed_symbol_2 = trail_octet & (SI_Long)255L;
		char_1 = gensymed_symbol_1 | gensymed_symbol_2;
	    }
	    else {
		lead_octet = char_1;
		trail_octet = char_2;
		gensymed_symbol_2 = lead_octet & (SI_Long)255L;
		gensymed_symbol_1 = (SI_Long)8L;
		gensymed_symbol_1 = gensymed_symbol_2 << gensymed_symbol_1;
		gensymed_symbol_2 = trail_octet & (SI_Long)255L;
		char_1 = gensymed_symbol_1 | gensymed_symbol_2;
	    }
	}
	incff_1_arg_1 = n_octets_per_character;
	position_1 = position_1 + IFIX(incff_1_arg_1);
	temp_2 = FIX(char_1);
    }
    else
	temp_2 = Nil;
    ISVREF(g2_stream_frame,(SI_Long)28L) = FIX(position_1);
    ISVREF(g2_stream_frame,(SI_Long)29L) = FIX(available_characters);
    ISVREF(g2_stream_frame,(SI_Long)30L) = FIX(offset);
    return VALUES_1(temp_2);
}

static Object Qtried_read_byte_on_stream_not_opened_for_read;  /* tried-read-byte-on-stream-not-opened-for-read */

static Object Qsuccessfully_read_byte;  /* successfully-read-byte */

static Object Qerror_during_read_byte;  /* error-during-read-byte */

static Object Qtried_read_byte_when_closed;  /* tried-read-byte-when-closed */

/* READ-BYTE-LISP-SIDE */
Object read_byte_lisp_side(g2_stream_frame)
    Object g2_stream_frame;
{
    Object internal_g2_stream_qm, byte_value_qm, status_symbol, ascii_char_qm;
    Object position_1, svref_new_value, temp;

    x_note_fn_call(164,58);
    internal_g2_stream_qm = ISVREF(g2_stream_frame,(SI_Long)26L);
    byte_value_qm = Nil;
    if ( !(EQ(ISVREF(g2_stream_frame,(SI_Long)22L),Qinput) || 
	    EQ(ISVREF(g2_stream_frame,(SI_Long)22L),Qinput_and_output)))
	status_symbol = Qtried_read_byte_on_stream_not_opened_for_read;
    else if (internal_g2_stream_qm) {
	ascii_char_qm = read_next_char_for_g2_stream_frame(g2_stream_frame,
		internal_g2_stream_qm);
	if (ascii_char_qm) {
	    position_1 = FIXNUM_ADD(ISVREF(g2_stream_frame,(SI_Long)30L),
		    ISVREF(g2_stream_frame,(SI_Long)28L));
	    change_slot_description_value_function(g2_stream_frame,
		    Position_in_file_slot_description,position_1,Nil,Nil);
	    byte_value_qm = FIXNUM_LOGAND(ascii_char_qm,Byte_range_0_255_mask);
	    status_symbol = Qsuccessfully_read_byte;
	}
	else if (g2_stream_eof_p(internal_g2_stream_qm))
	    status_symbol = Qend_of_file_reached;
	else
	    status_symbol = Qerror_during_read_byte;
    }
    else
	status_symbol = Qtried_read_byte_when_closed;
    if ( !EQ(status_symbol,ISVREF(g2_stream_frame,(SI_Long)24L)))
	change_slot_description_value_function(g2_stream_frame,
		G2_stream_status_slot_description,status_symbol,Nil,Nil);
    if (internal_g2_stream_qm) {
	svref_new_value = Internal_status_of_most_recent_file_operation;
	ISVREF(g2_stream_frame,(SI_Long)25L) = svref_new_value;
    }
    temp = byte_value_qm;
    if (temp);
    else
	temp = FIX((SI_Long)-1L);
    return VALUES_2(temp,status_symbol);
}

static Object string_constant_9;   /* "Request to read ~d bytes which exceeds the ~
				    *                     maximum G2 text length, ~d"
				    */

static Object Qtried_read_bytes_on_stream_not_opened_for_read;  /* tried-read-bytes-on-stream-not-opened-for-read */

static Object Qtext_truncated_during_read;  /* text-truncated-during-read */

static Object Qsuccessfully_read_bytes;  /* successfully-read-bytes */

static Object Qerror_during_read_bytes;  /* error-during-read-bytes */

static Object Qtried_read_bytes_when_closed;  /* tried-read-bytes-when-closed */

/* READ-BYTES-AS-TEXT-LISP-SIDE */
Object read_bytes_as_text_lisp_side(n_1,g2_stream_frame)
    Object n_1, g2_stream_frame;
{
    Object top_of_stack, message_1, internal_g2_stream_qm;
    Object result_text_string_qm, status_symbol, g2_input_stream, buffer;
    Object string_length_exceeded_p, style, temp, gensymed_symbol, charset;
    Object n_octets_per_character, n_2_octet_byte_swapped_p, preimported_p;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object ascii_char_qm, count_of_characters_read_qm, temp_4, incff_1_arg_1;
    Object aref_arg_2, aref_new_value_1, gensymed_symbol_3, gensymed_symbol_4;
    Object gensymed_symbol_5, gensymed_symbol_6, gensymed_symbol_7;
    SI_Long position_1, available_characters, offset, initial_file_position;
    SI_Long temp_1, bv16_length, aref_new_value, length_1, ab_loop_repeat_;
    SI_Long temp_2, gensymed_symbol_1, gensymed_symbol_2, incff_1_arg, char_1;
    SI_Long char_2, lead_octet, trail_octet, position_2;
    char temp_3;
    Declare_special(5);
    Object result;

    x_note_fn_call(164,59);
    if (FIXNUM_GT(n_1,Maximum_length_for_user_text_strings)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_9,
		n_1,Maximum_length_for_user_text_strings);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    internal_g2_stream_qm = ISVREF(g2_stream_frame,(SI_Long)26L);
    result_text_string_qm = Nil;
    status_symbol = Nil;
    if ( !(EQ(ISVREF(g2_stream_frame,(SI_Long)22L),Qinput) || 
	    EQ(ISVREF(g2_stream_frame,(SI_Long)22L),Qinput_and_output)))
	status_symbol = Qtried_read_bytes_on_stream_not_opened_for_read;
    else if (internal_g2_stream_qm) {
	g2_input_stream = internal_g2_stream_qm;
	position_1 = IFIX(ISVREF(g2_stream_frame,(SI_Long)28L));
	available_characters = IFIX(ISVREF(g2_stream_frame,(SI_Long)29L));
	buffer = ISVREF(g2_stream_frame,(SI_Long)27L);
	offset = IFIX(ISVREF(g2_stream_frame,(SI_Long)30L));
	initial_file_position = offset + position_1;
	string_length_exceeded_p = Nil;
	if ( !TRUEP(ISVREF(g2_stream_frame,(SI_Long)31L))) {
	    style = 
		    come_up_with_text_conversion_style_structure(get_lookup_slot_value_given_default(g2_stream_frame,
		    Qtext_conversion_style,Nil),Nil);
	    ISVREF(g2_stream_frame,(SI_Long)31L) = T;
	    temp = ISVREF(style,(SI_Long)2L);
	    ISVREF(g2_stream_frame,(SI_Long)32L) = temp;
	    gensymed_symbol = ISVREF(style,(SI_Long)2L);
	    temp_1 = EQ(gensymed_symbol,Qunicode) || EQ(gensymed_symbol,
		    Qunicode_byte_swapped) || EQ(gensymed_symbol,
		    Qunicode_ucs_2) || EQ(gensymed_symbol,
		    Qunicode_ucs_2_byte_swapped) ? (SI_Long)2L : (SI_Long)1L;
	    ISVREF(g2_stream_frame,(SI_Long)33L) = FIX(temp_1);
	    gensymed_symbol = ISVREF(style,(SI_Long)2L);
	    temp = EQ(gensymed_symbol,Qunicode_byte_swapped) || 
		    EQ(gensymed_symbol,Qunicode_ucs_2_byte_swapped) ? T : Nil;
	    ISVREF(g2_stream_frame,(SI_Long)34L) = temp;
	    gensymed_symbol = ISVREF(style,(SI_Long)2L);
	    temp = EQ(gensymed_symbol,Qus_ascii) ? T : Nil;
	    if (temp);
	    else
		temp = EQ(gensymed_symbol,Qlatin_1) ? T : Nil;
	    if (temp);
	    else
		temp = EQ(gensymed_symbol,Qunicode) ? T : Nil;
	    if (temp);
	    else
		temp = EQ(gensymed_symbol,Qunicode_byte_swapped) ? T : Nil;
	    if (temp);
	    else
		temp = EQ(gensymed_symbol,Qunicode_ucs_2) ? T : Nil;
	    if (temp);
	    else
		temp = EQ(gensymed_symbol,Qunicode_ucs_2_byte_swapped) ? T 
			: Nil;
	    ISVREF(g2_stream_frame,(SI_Long)35L) = temp;
	}
	charset = ISVREF(g2_stream_frame,(SI_Long)32L);
	n_octets_per_character = ISVREF(g2_stream_frame,(SI_Long)33L);
	n_2_octet_byte_swapped_p = ISVREF(g2_stream_frame,(SI_Long)34L);
	preimported_p = ISVREF(g2_stream_frame,(SI_Long)35L);
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
		  ab_loop_repeat_ = IFIX(n_1);
		  ascii_char_qm = Nil;
		next_loop:
		  if ( !((SI_Long)0L < ab_loop_repeat_))
		      goto end_loop;
		  ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		  temp_2 = position_1;
		  gensymed_symbol_1 = available_characters;
		  gensymed_symbol_2 = IFIX(n_octets_per_character) == 
			  (SI_Long)2L ? (SI_Long)1L : (SI_Long)0L;
		  temp_3 = temp_2 < gensymed_symbol_1 - gensymed_symbol_2;
		  if (temp_3);
		  else {
		      count_of_characters_read_qm = 
			      g2_stream_read_octets_into_wide_string_buffer(buffer,
			      Size_of_g2_stream_frame_input_buffer,
			      g2_input_stream);
		      temp_4 = count_of_characters_read_qm;
		      if (temp_4);
		      else
			  temp_4 = FIX((SI_Long)0L);
		      available_characters = IFIX(temp_4);
		      incff_1_arg = position_1;
		      offset = offset + incff_1_arg;
		      position_1 = (SI_Long)0L;
		      temp_3 = available_characters > 
			      (IFIX(n_octets_per_character) == (SI_Long)2L 
			      ? (SI_Long)1L : (SI_Long)0L);
		  }
		  if (temp_3) {
		      char_1 = UBYTE_16_ISAREF_1(buffer,position_1);
		      char_2 = (SI_Long)0L;
		      if (IFIX(n_octets_per_character) == (SI_Long)2L) {
			  char_2 = UBYTE_16_ISAREF_1(buffer,position_1 + 
				  (SI_Long)1L);
			  if (n_2_octet_byte_swapped_p) {
			      lead_octet = char_2;
			      trail_octet = char_1;
			      gensymed_symbol_2 = lead_octet & (SI_Long)255L;
			      gensymed_symbol_1 = (SI_Long)8L;
			      gensymed_symbol_1 = gensymed_symbol_2 << 
				      gensymed_symbol_1;
			      gensymed_symbol_2 = trail_octet & (SI_Long)255L;
			      char_1 = gensymed_symbol_1 | gensymed_symbol_2;
			  }
			  else {
			      lead_octet = char_1;
			      trail_octet = char_2;
			      gensymed_symbol_2 = lead_octet & (SI_Long)255L;
			      gensymed_symbol_1 = (SI_Long)8L;
			      gensymed_symbol_1 = gensymed_symbol_2 << 
				      gensymed_symbol_1;
			      gensymed_symbol_2 = trail_octet & (SI_Long)255L;
			      char_1 = gensymed_symbol_1 | gensymed_symbol_2;
			  }
		      }
		      incff_1_arg_1 = n_octets_per_character;
		      position_1 = position_1 + IFIX(incff_1_arg_1);
		      ascii_char_qm = FIX(char_1);
		  }
		  else
		      ascii_char_qm = Nil;
		  if ( !TRUEP(ascii_char_qm))
		      goto end_loop;
		  if ( !FIXNUM_LT(Fill_pointer_for_current_wide_string,
			  Total_length_of_current_wide_string))
		      extend_current_wide_string(Fill_pointer_for_current_wide_string);
		  temp = Current_wide_string;
		  aref_arg_2 = Fill_pointer_for_current_wide_string;
		  aref_new_value_1 = FIXNUM_LOGAND(ascii_char_qm,
			  Byte_range_0_255_mask);
		  UBYTE_16_ISASET_1(temp,IFIX(aref_arg_2),
			  IFIX(aref_new_value_1));
		  temp = FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
		  Fill_pointer_for_current_wide_string = temp;
		  if (FIXNUM_GE(Fill_pointer_for_current_wide_string,
			  Maximum_length_for_user_text_strings)) {
		      string_length_exceeded_p = T;
		      goto end_loop;
		  }
		  goto next_loop;
		end_loop:
		  position_2 = offset + position_1;
		  change_slot_description_value_function(g2_stream_frame,
			  Position_in_file_slot_description,
			  FIX(position_2),Nil,Nil);
		  result_text_string_qm = copy_current_wide_string();
		  if (string_length_exceeded_p)
		      status_symbol = Qtext_truncated_during_read;
		  else if (ascii_char_qm)
		      status_symbol = Qsuccessfully_read_bytes;
		  else if (g2_stream_eof_p(internal_g2_stream_qm))
		      status_symbol = Qend_of_file_reached;
		  else
		      status_symbol = Qerror_during_read_bytes;
		  result = VALUES_1(Qnil);
		  MVS_6(result,gensymed_symbol,gensymed_symbol_3,
			  gensymed_symbol_4,gensymed_symbol_5,
			  gensymed_symbol_6,gensymed_symbol_7);
		  reclaim_wide_string(Current_wide_string);
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	ISVREF(g2_stream_frame,(SI_Long)28L) = FIX(position_1);
	ISVREF(g2_stream_frame,(SI_Long)29L) = FIX(available_characters);
	ISVREF(g2_stream_frame,(SI_Long)30L) = FIX(offset);
    }
    else
	status_symbol = Qtried_read_bytes_when_closed;
    if ( !EQ(status_symbol,ISVREF(g2_stream_frame,(SI_Long)24L)))
	change_slot_description_value_function(g2_stream_frame,
		G2_stream_status_slot_description,status_symbol,Nil,Nil);
    if (internal_g2_stream_qm) {
	temp = Internal_status_of_most_recent_file_operation;
	ISVREF(g2_stream_frame,(SI_Long)25L) = temp;
    }
    temp_4 = result_text_string_qm;
    if (temp_4);
    else {
	wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)0L + 
		(SI_Long)3L));
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	temp_1 = bv16_length - (SI_Long)2L;
	aref_new_value = (SI_Long)0L & (SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16,temp_1,aref_new_value);
	temp_1 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	UBYTE_16_ISASET_1(wide_string_bv16,temp_1,aref_new_value);
	UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)0L,(SI_Long)0L);
	temp_4 = wide_string_bv16;
    }
    return VALUES_2(temp_4,status_symbol);
}

/* WRITE-LINE-LISP-SIDE */
Object write_line_lisp_side(g2_new_line,g2_stream_frame)
    Object g2_new_line, g2_stream_frame;
{
    x_note_fn_call(164,60);
    return write_string_or_line_lisp_side_internal(g2_new_line,
	    g2_stream_frame,T,
	    come_up_with_text_conversion_style_structure(get_lookup_slot_value_given_default(g2_stream_frame,
	    Qtext_conversion_style,Nil),T));
}

/* WRITE-STRING-LISP-SIDE */
Object write_string_lisp_side(g2_new_string,g2_stream_frame)
    Object g2_new_string, g2_stream_frame;
{
    x_note_fn_call(164,61);
    return write_string_or_line_lisp_side_internal(g2_new_string,
	    g2_stream_frame,Nil,
	    come_up_with_text_conversion_style_structure(get_lookup_slot_value_given_default(g2_stream_frame,
	    Qtext_conversion_style,Nil),T));
}

static Object Qutf_g_string;       /* utf-g-string */

static Object Qtext_conversion_style_for_purpose;  /* text-conversion-style-for-purpose */

/* WRITE-LINE-IN-GENSYM-CHARSET-LISP-SIDE */
Object write_line_in_gensym_charset_lisp_side(g2_new_line,g2_stream_frame)
    Object g2_new_line, g2_stream_frame;
{
    x_note_fn_call(164,62);
    return write_string_or_line_lisp_side_internal(g2_new_line,
	    g2_stream_frame,T,
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qutf_g_string),
	    Qtext_conversion_style_for_purpose));
}

/* WRITE-STRING-IN-GENSYM-CHARSET-LISP-SIDE */
Object write_string_in_gensym_charset_lisp_side(g2_new_string,g2_stream_frame)
    Object g2_new_string, g2_stream_frame;
{
    x_note_fn_call(164,63);
    return write_string_or_line_lisp_side_internal(g2_new_string,
	    g2_stream_frame,Nil,
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qutf_g_string),
	    Qtext_conversion_style_for_purpose));
}

static Object Qsuccessfully_wrote_line;  /* successfully-wrote-line */

static Object Qsuccessfully_wrote_string;  /* successfully-wrote-string */

static Object Qerror_during_write_line;  /* error-during-write-line */

static Object Qerror_during_write_string;  /* error-during-write-string */

static Object Qtried_write_line_when_closed;  /* tried-write-line-when-closed */

static Object Qtried_write_string_when_closed;  /* tried-write-string-when-closed */

static Object string_constant_10;  /* "Cannot write-line to closed stream" */

static Object string_constant_11;  /* "Cannot write-string to closed stream" */

/* WRITE-STRING-OR-LINE-LISP-SIDE-INTERNAL */
Object write_string_or_line_lisp_side_internal(string_1,g2_stream_frame,
	    line_case_qm,transcode_text_conversion_style)
    Object string_1, g2_stream_frame, line_case_qm;
    Object transcode_text_conversion_style;
{
    Object internal_g2_stream_qm, temp, successful_p, position_qm, status;
    Object svref_new_value, temp_1;

    x_note_fn_call(164,64);
    internal_g2_stream_qm = ISVREF(g2_stream_frame,(SI_Long)26L);
    if (internal_g2_stream_qm) {
	temp = line_case_qm ? export_and_emit_text_line(string_1,
		transcode_text_conversion_style,internal_g2_stream_qm) : 
		export_and_emit_text_string(string_1,
		transcode_text_conversion_style,internal_g2_stream_qm);
	reclaim_text_string(string_1);
	successful_p = temp;
	position_qm = successful_p ? 
		g2_stream_get_file_position(internal_g2_stream_qm) : Nil;
	if (ISVREF(g2_stream_frame,(SI_Long)27L)) {
	    ISVREF(g2_stream_frame,(SI_Long)28L) = FIX((SI_Long)0L);
	    ISVREF(g2_stream_frame,(SI_Long)29L) = FIX((SI_Long)0L);
	}
	if (successful_p) {
	    status = line_case_qm ? Qsuccessfully_wrote_line : 
		    Qsuccessfully_wrote_string;
	    if ( !EQ(status,ISVREF(g2_stream_frame,(SI_Long)24L)))
		change_slot_description_value_function(g2_stream_frame,
			G2_stream_status_slot_description,status,Nil,Nil);
	    if (internal_g2_stream_qm) {
		svref_new_value = 
			Internal_status_of_most_recent_file_operation;
		ISVREF(g2_stream_frame,(SI_Long)25L) = svref_new_value;
	    }
	    change_slot_description_value_function(g2_stream_frame,
		    Position_in_file_slot_description,position_qm,Nil,Nil);
	    if (ISVREF(g2_stream_frame,(SI_Long)27L))
		ISVREF(g2_stream_frame,(SI_Long)30L) = position_qm;
	    temp_1 = Evaluation_true_value;
	    temp = copy_as_wide_string(string_constant_6);
	    return VALUES_2(temp_1,temp);
	}
	else {
	    status = line_case_qm ? Qerror_during_write_line : 
		    Qerror_during_write_string;
	    if ( !EQ(status,ISVREF(g2_stream_frame,(SI_Long)24L)))
		change_slot_description_value_function(g2_stream_frame,
			G2_stream_status_slot_description,status,Nil,Nil);
	    if (internal_g2_stream_qm) {
		svref_new_value = 
			Internal_status_of_most_recent_file_operation;
		ISVREF(g2_stream_frame,(SI_Long)25L) = svref_new_value;
	    }
	    temp_1 = Evaluation_false_value;
	    temp = most_recent_file_operation_status_as_text();
	    return VALUES_2(temp_1,temp);
	}
    }
    else {
	status = line_case_qm ? Qtried_write_line_when_closed : 
		Qtried_write_string_when_closed;
	if ( !EQ(status,ISVREF(g2_stream_frame,(SI_Long)24L)))
	    change_slot_description_value_function(g2_stream_frame,
		    G2_stream_status_slot_description,status,Nil,Nil);
	if (internal_g2_stream_qm) {
	    svref_new_value = Internal_status_of_most_recent_file_operation;
	    ISVREF(g2_stream_frame,(SI_Long)25L) = svref_new_value;
	}
	temp_1 = Evaluation_false_value;
	temp = copy_as_wide_string(line_case_qm ? string_constant_10 : 
		string_constant_11);
	return VALUES_2(temp_1,temp);
    }
}

static Object Qsuccessfully_wrote_byte;  /* successfully-wrote-byte */

static Object Qerror_during_write_byte;  /* error-during-write-byte */

static Object Qtried_write_byte_when_closed;  /* tried-write-byte-when-closed */

/* WRITE-BYTE-LISP-SIDE */
Object write_byte_lisp_side(g2_new_byte,g2_stream_frame)
    Object g2_new_byte, g2_stream_frame;
{
    Object internal_g2_stream_qm, new_byte, successful_p, position_qm;
    Object position_1, svref_new_value, temp;

    x_note_fn_call(164,65);
    internal_g2_stream_qm = ISVREF(g2_stream_frame,(SI_Long)26L);
    if (internal_g2_stream_qm) {
	new_byte = g2_new_byte;
	successful_p = g2_stream_write_ascii_byte(new_byte,
		internal_g2_stream_qm);
	position_qm = successful_p ? 
		g2_stream_get_file_position(internal_g2_stream_qm) : Nil;
	if (ISVREF(g2_stream_frame,(SI_Long)27L)) {
	    ISVREF(g2_stream_frame,(SI_Long)28L) = FIX((SI_Long)0L);
	    ISVREF(g2_stream_frame,(SI_Long)29L) = FIX((SI_Long)0L);
	}
	if (successful_p) {
	    position_1 = g2_stream_get_file_position(internal_g2_stream_qm);
	    if ( !EQ(Qsuccessfully_wrote_byte,ISVREF(g2_stream_frame,
		    (SI_Long)24L)))
		change_slot_description_value_function(g2_stream_frame,
			G2_stream_status_slot_description,
			Qsuccessfully_wrote_byte,Nil,Nil);
	    if (internal_g2_stream_qm) {
		svref_new_value = 
			Internal_status_of_most_recent_file_operation;
		ISVREF(g2_stream_frame,(SI_Long)25L) = svref_new_value;
	    }
	    change_slot_description_value_function(g2_stream_frame,
		    Position_in_file_slot_description,position_1,Nil,Nil);
	    if (ISVREF(g2_stream_frame,(SI_Long)27L))
		ISVREF(g2_stream_frame,(SI_Long)30L) = position_qm;
	    temp = Evaluation_true_value;
	}
	else {
	    if ( !EQ(Qerror_during_write_byte,ISVREF(g2_stream_frame,
		    (SI_Long)24L)))
		change_slot_description_value_function(g2_stream_frame,
			G2_stream_status_slot_description,
			Qerror_during_write_byte,Nil,Nil);
	    if (internal_g2_stream_qm) {
		svref_new_value = 
			Internal_status_of_most_recent_file_operation;
		ISVREF(g2_stream_frame,(SI_Long)25L) = svref_new_value;
	    }
	    temp = Evaluation_false_value;
	}
    }
    else {
	if ( !EQ(Qtried_write_byte_when_closed,ISVREF(g2_stream_frame,
		(SI_Long)24L)))
	    change_slot_description_value_function(g2_stream_frame,
		    G2_stream_status_slot_description,
		    Qtried_write_byte_when_closed,Nil,Nil);
	if (internal_g2_stream_qm) {
	    svref_new_value = Internal_status_of_most_recent_file_operation;
	    ISVREF(g2_stream_frame,(SI_Long)25L) = svref_new_value;
	}
	temp = Evaluation_false_value;
    }
    return VALUES_1(temp);
}

static Object string_constant_12;  /* "Request to write bytes of non-sequence value ~a" */

/* WRITE-BYTES-LISP-SIDE */
Object write_bytes_lisp_side(sequence,g2_stream_frame)
    Object sequence, g2_stream_frame;
{
    Object internal_g2_stream_qm, top_of_stack, message_1, buffer;
    Object gensymed_symbol, held_vector, byte_1, ab_loop_iter_flag_, elt_1;
    Object validated_elt, temp, temp_1, successful_p, position_qm, position_1;
    SI_Long next_index, length_1, index_1, gensymed_symbol_1;

    x_note_fn_call(164,66);
    internal_g2_stream_qm = ISVREF(g2_stream_frame,(SI_Long)26L);
    if (internal_g2_stream_qm) {
	if ( !(CONSP(sequence) && EQ(M_CDR(sequence),Qsequence))) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_12,sequence);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	buffer = 
		obtain_simple_gensym_string(FIXNUM_SUB1(ISVREF(M_CAR(sequence),
		(SI_Long)1L)));
	gensymed_symbol = sequence;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	byte_1 = Nil;
	index_1 = (SI_Long)0L;
	ab_loop_iter_flag_ = T;
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
	byte_1 = validated_elt;
	if ( !TRUEP(ab_loop_iter_flag_))
	    index_1 = index_1 + (SI_Long)1L;
	gensymed_symbol_1 = (SI_Long)255L & IFIX(byte_1);
	temp = CODE_CHAR(FIX(gensymed_symbol_1));
	SET_ISCHAR(buffer,index_1,ICHAR_CODE(temp));
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:;
	temp_1 = g2_stream_write_from_buffer(buffer,
		SIMPLE_ARRAY_ANY_1_LENGTH(buffer),internal_g2_stream_qm);
	reclaim_simple_gensym_string(buffer);
	successful_p = temp_1;
	position_qm = successful_p ? 
		g2_stream_get_file_position(internal_g2_stream_qm) : Nil;
	if (ISVREF(g2_stream_frame,(SI_Long)27L)) {
	    ISVREF(g2_stream_frame,(SI_Long)28L) = FIX((SI_Long)0L);
	    ISVREF(g2_stream_frame,(SI_Long)29L) = FIX((SI_Long)0L);
	}
	if (successful_p) {
	    position_1 = g2_stream_get_file_position(internal_g2_stream_qm);
	    if ( !EQ(Qsuccessfully_wrote_byte,ISVREF(g2_stream_frame,
		    (SI_Long)24L)))
		change_slot_description_value_function(g2_stream_frame,
			G2_stream_status_slot_description,
			Qsuccessfully_wrote_byte,Nil,Nil);
	    if (internal_g2_stream_qm) {
		temp = Internal_status_of_most_recent_file_operation;
		ISVREF(g2_stream_frame,(SI_Long)25L) = temp;
	    }
	    change_slot_description_value_function(g2_stream_frame,
		    Position_in_file_slot_description,position_1,Nil,Nil);
	    if (ISVREF(g2_stream_frame,(SI_Long)27L))
		ISVREF(g2_stream_frame,(SI_Long)30L) = position_qm;
	    temp_1 = Evaluation_true_value;
	}
	else {
	    if ( !EQ(Qerror_during_write_byte,ISVREF(g2_stream_frame,
		    (SI_Long)24L)))
		change_slot_description_value_function(g2_stream_frame,
			G2_stream_status_slot_description,
			Qerror_during_write_byte,Nil,Nil);
	    if (internal_g2_stream_qm) {
		temp = Internal_status_of_most_recent_file_operation;
		ISVREF(g2_stream_frame,(SI_Long)25L) = temp;
	    }
	    temp_1 = Evaluation_false_value;
	}
    }
    else {
	if ( !EQ(Qtried_write_byte_when_closed,ISVREF(g2_stream_frame,
		(SI_Long)24L)))
	    change_slot_description_value_function(g2_stream_frame,
		    G2_stream_status_slot_description,
		    Qtried_write_byte_when_closed,Nil,Nil);
	if (internal_g2_stream_qm) {
	    temp = Internal_status_of_most_recent_file_operation;
	    ISVREF(g2_stream_frame,(SI_Long)25L) = temp;
	}
	temp_1 = Evaluation_false_value;
    }
    return VALUES_1(temp_1);
}

/* FLOAT-TO-BYTES-LISP-SIDE */
Object float_to_bytes_lisp_side(g2_float)
    Object g2_float;
{
    Object bytes_1_and_2, bytes_3_and_4, bytes_5_and_6, bytes_7_and_8, temp;
    Object temp_1, temp_2, temp_3, temp_4, temp_5, temp_6, temp_7;
    SI_Long b0, b1, b2, b3;
    double g2_float_value;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(164,67);
    bytes_1_and_2 = Nil;
    bytes_3_and_4 = Nil;
    bytes_5_and_6 = Nil;
    bytes_7_and_8 = Nil;
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	g2_float_value = DFLOAT_ISAREF_1(g2_float,(SI_Long)0L);
	g2ext_foreign_partition_float(g2_float_value,
		UBYTE_16_SARRAY_TO_USHORT_PTR(Partition_float_union));
	b0 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)0L);
	b1 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)1L);
	b2 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)2L);
	b3 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)3L);
	result = VALUES_4(FIX(b0),FIX(b1),FIX(b2),FIX(b3));
	MVS_4(result,bytes_1_and_2,bytes_3_and_4,bytes_5_and_6,bytes_7_and_8);
    }
    POP_LOCAL_ALLOCATION(0,0);
    reclaim_managed_simple_float_array_of_length_1(g2_float);
    temp = FIX(IFIX(bytes_1_and_2) >>  -  - (SI_Long)8L & 
	    IFIX(Byte_range_0_255_mask));
    temp_1 = FIXNUM_LOGAND(bytes_1_and_2,Byte_range_0_255_mask);
    temp_2 = FIX(IFIX(bytes_3_and_4) >>  -  - (SI_Long)8L & 
	    IFIX(Byte_range_0_255_mask));
    temp_3 = FIXNUM_LOGAND(bytes_3_and_4,Byte_range_0_255_mask);
    temp_4 = FIX(IFIX(bytes_5_and_6) >>  -  - (SI_Long)8L & 
	    IFIX(Byte_range_0_255_mask));
    temp_5 = FIXNUM_LOGAND(bytes_5_and_6,Byte_range_0_255_mask);
    temp_6 = FIX(IFIX(bytes_7_and_8) >>  -  - (SI_Long)8L & 
	    IFIX(Byte_range_0_255_mask));
    temp_7 = FIXNUM_LOGAND(bytes_7_and_8,Byte_range_0_255_mask);
    return VALUES_8(temp,temp_1,temp_2,temp_3,temp_4,temp_5,temp_6,temp_7);
}

static Object Qfloat_array;        /* float-array */

/* BYTES-TO-FLOAT-LISP-SIDE */
Object bytes_to_float_lisp_side(byte1,byte2,byte3,byte4,byte5,byte6,byte7,
	    byte8)
    Object byte1, byte2, byte3, byte4, byte5, byte6, byte7, byte8;
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float;
    SI_Long bytes_1_and_2, bytes_3_and_4, bytes_5_and_6, bytes_7_and_8, b0, b1;
    SI_Long b2, b3;
    double g2_float_value;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(164,68);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	bytes_1_and_2 = IFIX(FIXNUM_LOGAND(byte1,Byte_range_0_255_mask)) 
		<< (SI_Long)8L | IFIX(FIXNUM_LOGAND(byte2,
		Byte_range_0_255_mask));
	bytes_3_and_4 = IFIX(FIXNUM_LOGAND(byte3,Byte_range_0_255_mask)) 
		<< (SI_Long)8L | IFIX(FIXNUM_LOGAND(byte4,
		Byte_range_0_255_mask));
	bytes_5_and_6 = IFIX(FIXNUM_LOGAND(byte5,Byte_range_0_255_mask)) 
		<< (SI_Long)8L | IFIX(FIXNUM_LOGAND(byte6,
		Byte_range_0_255_mask));
	bytes_7_and_8 = IFIX(FIXNUM_LOGAND(byte7,Byte_range_0_255_mask)) 
		<< (SI_Long)8L | IFIX(FIXNUM_LOGAND(byte8,
		Byte_range_0_255_mask));
	b0 = bytes_1_and_2;
	b1 = bytes_3_and_4;
	b2 = bytes_5_and_6;
	b3 = bytes_7_and_8;
	g2_float_value = g2ext_foreign_reconstruct_float(b0,b1,b2,b3);
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
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,g2_float_value);
	result = VALUES_1(new_float);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* FILE-HOST-STRING-LISP-SIDE */
Object file_host_string_lisp_side(g2_filestring)
    Object g2_filestring;
{
    Object filestring, raw_component_string, component_string;

    x_note_fn_call(164,69);
    filestring = export_text_string(2,g2_filestring,Qg2_directory_pathname);
    raw_component_string = gensym_host_namestring(1,filestring);
    component_string = import_text_string(2,raw_component_string,
	    Qg2_directory_pathname);
    reclaim_text_string(g2_filestring);
    reclaim_text_string(filestring);
    reclaim_text_string(raw_component_string);
    return VALUES_1(component_string);
}

/* FILE-DEVICE-STRING-LISP-SIDE */
Object file_device_string_lisp_side(g2_filestring)
    Object g2_filestring;
{
    Object filestring, raw_component_string, component_string;

    x_note_fn_call(164,70);
    filestring = export_text_string(2,g2_filestring,Qg2_directory_pathname);
    raw_component_string = gensym_device_namestring(1,filestring);
    component_string = import_text_string(2,raw_component_string,
	    Qg2_directory_pathname);
    reclaim_text_string(g2_filestring);
    reclaim_text_string(filestring);
    reclaim_text_string(raw_component_string);
    return VALUES_1(component_string);
}

/* FILE-DIRECTORY-STRING-LISP-SIDE */
Object file_directory_string_lisp_side(g2_filestring)
    Object g2_filestring;
{
    Object filestring, raw_component_string, component_string;

    x_note_fn_call(164,71);
    filestring = export_text_string(2,g2_filestring,Qg2_directory_pathname);
    raw_component_string = gensym_directory_namestring(1,filestring);
    component_string = import_text_string(2,raw_component_string,
	    Qg2_directory_pathname);
    reclaim_text_string(g2_filestring);
    reclaim_text_string(filestring);
    reclaim_text_string(raw_component_string);
    return VALUES_1(component_string);
}

static Object Qtext_list;          /* text-list */

static Object Kabsolute;           /* :absolute */

static Object Krelative;           /* :relative */

/* FILE-DIRECTORY-STRING-TO-LIST-LISP-SIDE */
Object file_directory_string_to_list_lisp_side(g2_filestring)
    Object g2_filestring;
{
    Object filestring, pathname_qm, list_frame, directory_component;
    Object ab_loop_list_, converted_component;

    x_note_fn_call(164,72);
    filestring = export_text_string(2,g2_filestring,Qg2_directory_pathname);
    pathname_qm = gensym_pathname(filestring);
    list_frame = make_transient_item(Qtext_list);
    if (pathname_qm) {
	directory_component = Nil;
	ab_loop_list_ = ISVREF(pathname_qm,(SI_Long)3L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	directory_component = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(directory_component,Kabsolute));
	else if (EQ(directory_component,Krelative));
	else if (EQ(directory_component,Kup))
	    g2_list_remove_first(1,list_frame);
	else {
	    converted_component = import_text_string(2,directory_component,
		    Qg2_directory_pathname);
	    g2_list_insert_at_end(2,converted_component,list_frame);
	}
	goto next_loop;
      end_loop:;
    }
    reclaim_text_string(g2_filestring);
    reclaim_text_string(filestring);
    if (pathname_qm)
	reclaim_gensym_pathname(pathname_qm);
    return VALUES_1(list_frame);
}

/* FILE-DIRECTORY-LIST-TO-STRING-LISP-SIDE */
Object file_directory_list_to_string_lisp_side(text_list_frame)
    Object text_list_frame;
{
    Object ab_loopvar_, ab_loopvar__1, element, ab_loopvar__2, ab_loopvar__3;
    Object ab_loopvar__4, temp, directory_components, directory_pathname;
    Object raw_directory_namestring, directory_namestring_1;

    x_note_fn_call(164,73);
    ab_loopvar_ = ISVREF(text_list_frame,(SI_Long)20L);
    ab_loopvar__1 = Nil;
    element = Nil;
    ab_loopvar__2 = Nil;
    ab_loopvar__3 = Nil;
    ab_loopvar__4 = Nil;
    ab_loopvar__1 = ab_loopvar_ ? 
	    g2_list_structure_next(ISVREF(ab_loopvar_,(SI_Long)2L),
	    ab_loopvar_) : Nil;
  next_loop:
    if ( !TRUEP(ab_loopvar__1))
	goto end_loop;
    element = ISVREF(ab_loopvar__1,(SI_Long)4L);
    ab_loopvar__1 = g2_list_structure_next(ab_loopvar__1,ab_loopvar_);
    ab_loopvar__4 = path_cons_1(element,Nil);
    if (ab_loopvar__3)
	M_CDR(ab_loopvar__3) = ab_loopvar__4;
    else
	ab_loopvar__2 = ab_loopvar__4;
    ab_loopvar__3 = ab_loopvar__4;
    goto next_loop;
  end_loop:
    temp = ab_loopvar__2;
    goto end_1;
    temp = Qnil;
  end_1:;
    directory_components = path_cons_1(Kabsolute,temp);
    directory_pathname = gensym_make_pathname_with_copied_components(Nil,
	    Nil,directory_components,Nil,Nil,Nil,Nil);
    raw_directory_namestring = gensym_namestring(1,directory_pathname);
    directory_namestring_1 = import_text_string(2,raw_directory_namestring,
	    Qg2_directory_pathname);
    temp = directory_namestring_1;
    reclaim_path_list_1(directory_components);
    reclaim_text_string(raw_directory_namestring);
    reclaim_gensym_pathname(directory_pathname);
    return VALUES_1(temp);
}

/* FILE-BASE-NAME-STRING-LISP-SIDE */
Object file_base_name_string_lisp_side(g2_filestring)
    Object g2_filestring;
{
    Object filestring, raw_component_string, component_string;

    x_note_fn_call(164,74);
    filestring = export_text_string(2,g2_filestring,Qg2_directory_pathname);
    raw_component_string = gensym_base_namestring(1,filestring);
    component_string = import_text_string(2,raw_component_string,
	    Qg2_directory_pathname);
    reclaim_text_string(g2_filestring);
    reclaim_text_string(filestring);
    reclaim_text_string(raw_component_string);
    return VALUES_1(component_string);
}

/* FILE-EXTENSION-STRING-LISP-SIDE */
Object file_extension_string_lisp_side(g2_filestring)
    Object g2_filestring;
{
    Object filestring, raw_component_string, component_string;

    x_note_fn_call(164,75);
    filestring = export_text_string(2,g2_filestring,Qg2_directory_pathname);
    raw_component_string = gensym_type_namestring(1,filestring);
    component_string = import_text_string(2,raw_component_string,
	    Qg2_directory_pathname);
    reclaim_text_string(g2_filestring);
    reclaim_text_string(filestring);
    reclaim_text_string(raw_component_string);
    return VALUES_1(component_string);
}

/* FILE-VERSION-STRING-LISP-SIDE */
Object file_version_string_lisp_side(g2_filestring)
    Object g2_filestring;
{
    Object filestring, raw_component_string, component_string;

    x_note_fn_call(164,76);
    filestring = export_text_string(2,g2_filestring,Qg2_directory_pathname);
    raw_component_string = gensym_version_namestring(1,filestring);
    component_string = import_text_string(2,raw_component_string,
	    Qg2_directory_pathname);
    reclaim_text_string(g2_filestring);
    reclaim_text_string(filestring);
    reclaim_text_string(raw_component_string);
    return VALUES_1(component_string);
}

static Object Qunbound_in_protected_let;  /* unbound-in-protected-let */

static Object string_constant_13;  /* "~a~a~a~a~a~a" */

/* COLLECT-INTO-FILESTRING-LISP-SIDE */
Object collect_into_filestring_lisp_side(g2_host_string,g2_device_string,
	    g2_directory_string,g2_root_name_string,g2_type_string,
	    g2_version_string)
    Object g2_host_string, g2_device_string, g2_directory_string;
    Object g2_root_name_string, g2_type_string, g2_version_string;
{
    volatile Object host_string;
    volatile Object device_string;
    volatile Object directory_string;
    volatile Object root_name_string;
    volatile Object type_string;
    volatile Object version_string;
    volatile Object raw_collected_string;
    Object collected_string;
    volatile Object pathname_from_collected_string_qm;
    Object temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(164,77);
    SAVE_STACK();
    host_string = Qunbound_in_protected_let;
    device_string = Qunbound_in_protected_let;
    directory_string = Qunbound_in_protected_let;
    root_name_string = Qunbound_in_protected_let;
    type_string = Qunbound_in_protected_let;
    version_string = Qunbound_in_protected_let;
    raw_collected_string = Qunbound_in_protected_let;
    collected_string = Qunbound_in_protected_let;
    pathname_from_collected_string_qm = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	host_string = export_text_string(2,g2_host_string,
		Qg2_directory_pathname);
	device_string = export_text_string(2,g2_device_string,
		Qg2_directory_pathname);
	directory_string = export_text_string(2,g2_directory_string,
		Qg2_directory_pathname);
	root_name_string = export_text_string(2,g2_root_name_string,
		Qg2_directory_pathname);
	type_string = export_text_string(2,g2_type_string,
		Qg2_directory_pathname);
	version_string = export_text_string(2,g2_version_string,
		Qg2_directory_pathname);
	raw_collected_string = tformat_text_string(7,string_constant_13,
		host_string,device_string,directory_string,
		root_name_string,type_string,version_string);
	collected_string = import_text_string(2,raw_collected_string,
		Qg2_directory_pathname);
	pathname_from_collected_string_qm = gensym_pathname(collected_string);
	temp = pathname_from_collected_string_qm ? collected_string : 
		copy_as_wide_string(string_constant_6);
	SAVE_VALUES(VALUES_1(temp));
	reclaim_text_string(g2_host_string);
	reclaim_text_string(g2_device_string);
	reclaim_text_string(g2_directory_string);
	reclaim_text_string(g2_root_name_string);
	reclaim_text_string(g2_type_string);
	reclaim_text_string(g2_version_string);
    }
    POP_UNWIND_PROTECT(0);
    if (pathname_from_collected_string_qm) {
	if ( !EQ(pathname_from_collected_string_qm,Qunbound_in_protected_let))
	    reclaim_gensym_pathname(pathname_from_collected_string_qm);
    }
    if (raw_collected_string) {
	if ( !EQ(raw_collected_string,Qunbound_in_protected_let))
	    reclaim_text_string(raw_collected_string);
    }
    if (version_string) {
	if ( !EQ(version_string,Qunbound_in_protected_let))
	    reclaim_text_string(version_string);
    }
    if (type_string) {
	if ( !EQ(type_string,Qunbound_in_protected_let))
	    reclaim_text_string(type_string);
    }
    if (root_name_string) {
	if ( !EQ(root_name_string,Qunbound_in_protected_let))
	    reclaim_text_string(root_name_string);
    }
    if (directory_string) {
	if ( !EQ(directory_string,Qunbound_in_protected_let))
	    reclaim_text_string(directory_string);
    }
    if (device_string) {
	if ( !EQ(device_string,Qunbound_in_protected_let))
	    reclaim_text_string(device_string);
    }
    if (host_string) {
	if ( !EQ(host_string,Qunbound_in_protected_let))
	    reclaim_text_string(host_string);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* PARTITION-FILESTRING-LISP-SIDE */
Object partition_filestring_lisp_side(g2_filestring)
    Object g2_filestring;
{
    volatile Object filestring;
    volatile Object pathname_qm;
    Object temp, namestring_1, host_string, device_string, directory_string;
    Object base_string, type_string, version_string, temp_1, temp_2, temp_3;
    Object temp_4, temp_5;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(164,78);
    SAVE_STACK();
    filestring = Qunbound_in_protected_let;
    pathname_qm = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	temp = export_text_string(2,g2_filestring,Qg2_directory_pathname);
	reclaim_text_string(g2_filestring);
	filestring = temp;
	pathname_qm = gensym_pathname(filestring);
	if (pathname_qm) {
	    namestring_1 = gensym_host_namestring(1,pathname_qm);
	    temp = import_text_string(2,namestring_1,Qg2_directory_pathname);
	    reclaim_text_string(namestring_1);
	    host_string = temp;
	    namestring_1 = gensym_device_namestring(1,pathname_qm);
	    temp = import_text_string(2,namestring_1,Qg2_directory_pathname);
	    reclaim_text_string(namestring_1);
	    device_string = temp;
	    namestring_1 = gensym_directory_namestring(1,pathname_qm);
	    temp = import_text_string(2,namestring_1,Qg2_directory_pathname);
	    reclaim_text_string(namestring_1);
	    directory_string = temp;
	    namestring_1 = gensym_base_namestring(1,pathname_qm);
	    temp = import_text_string(2,namestring_1,Qg2_directory_pathname);
	    reclaim_text_string(namestring_1);
	    base_string = temp;
	    namestring_1 = gensym_type_namestring(1,pathname_qm);
	    temp = import_text_string(2,namestring_1,Qg2_directory_pathname);
	    reclaim_text_string(namestring_1);
	    type_string = temp;
	    namestring_1 = gensym_version_namestring(1,pathname_qm);
	    temp = import_text_string(2,namestring_1,Qg2_directory_pathname);
	    reclaim_text_string(namestring_1);
	    version_string = temp;
	    SAVE_VALUES(VALUES_6(host_string,device_string,
		    directory_string,base_string,type_string,version_string));
	}
	else {
	    temp_1 = copy_as_wide_string(string_constant_6);
	    temp_2 = copy_as_wide_string(string_constant_6);
	    temp_3 = copy_as_wide_string(string_constant_6);
	    temp_4 = copy_as_wide_string(string_constant_6);
	    temp_5 = copy_as_wide_string(string_constant_6);
	    temp = copy_as_wide_string(string_constant_6);
	    SAVE_VALUES(VALUES_6(temp_1,temp_2,temp_3,temp_4,temp_5,temp));
	}
    }
    POP_UNWIND_PROTECT(0);
    if (pathname_qm) {
	if ( !EQ(pathname_qm,Qunbound_in_protected_let))
	    reclaim_gensym_pathname(pathname_qm);
    }
    if (filestring) {
	if ( !EQ(filestring,Qunbound_in_protected_let))
	    reclaim_text_string(filestring);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* TYPE-OF-FILE-SYSTEM-LISP-SIDE */
Object type_of_file_system_lisp_side()
{
    x_note_fn_call(164,79);
    return VALUES_1(Local_file_system);
}

static Object Qg2_directory_pathname_w;  /* g2-directory-pathname-w */

/* FILE-EXISTS-LISP-SIDE */
Object file_exists_lisp_side(g2_filestring)
    Object g2_filestring;
{
    Object filestring, exists_p, temp;

    x_note_fn_call(164,80);
    filestring = export_text_string(2,g2_filestring,Qg2_directory_pathname_w);
    exists_p = g2_stream_probe_file_for_exist(filestring);
    temp = exists_p ? Evaluation_true_value : Evaluation_false_value;
    reclaim_text_string(g2_filestring);
    reclaim_text_string(filestring);
    return VALUES_1(temp);
}

/* FILE-NAMES-ARE-IDENTICAL-LISP-SIDE */
Object file_names_are_identical_lisp_side(g2_filestring_1,g2_filestring_2)
    Object g2_filestring_1, g2_filestring_2;
{
    Object filestring_1, filestring_2, pathname_1_qm, pathname_2_qm, temp;

    x_note_fn_call(164,81);
    filestring_1 = export_text_string(2,g2_filestring_1,
	    Qg2_directory_pathname);
    filestring_2 = export_text_string(2,g2_filestring_2,
	    Qg2_directory_pathname);
    pathname_1_qm = gensym_pathname(filestring_1);
    pathname_2_qm = gensym_pathname(filestring_2);
    temp = pathname_1_qm && pathname_2_qm && 
	    gensym_pathnames_equal_enough_p(pathname_1_qm,pathname_2_qm) ? 
	    Evaluation_true_value : Evaluation_false_value;
    reclaim_evaluation_value(g2_filestring_1);
    reclaim_evaluation_value(g2_filestring_2);
    reclaim_text_string(filestring_1);
    reclaim_text_string(filestring_2);
    if (pathname_1_qm)
	reclaim_gensym_pathname(pathname_1_qm);
    if (pathname_2_qm)
	reclaim_gensym_pathname(pathname_2_qm);
    return VALUES_1(temp);
}

static Object Qsuccessfully_obtained_file_length;  /* successfully-obtained-file-length */

static Object Qerror_getting_file_length;  /* error-getting-file-length */

static Object Qtried_to_get_length_when_closed;  /* tried-to-get-length-when-closed */

static Object string_constant_14;  /* "Cannot get length of closed stream" */

/* LENGTH-OF-FILE-LISP-SIDE */
Object length_of_file_lisp_side(g2_stream_frame)
    Object g2_stream_frame;
{
    Object internal_g2_stream_qm, file_length_qm, svref_new_value, temp;

    x_note_fn_call(164,82);
    internal_g2_stream_qm = ISVREF(g2_stream_frame,(SI_Long)26L);
    if (internal_g2_stream_qm) {
	file_length_qm = g2_stream_file_length(internal_g2_stream_qm);
	if (file_length_qm) {
	    if ( !EQ(Qsuccessfully_obtained_file_length,
		    ISVREF(g2_stream_frame,(SI_Long)24L)))
		change_slot_description_value_function(g2_stream_frame,
			G2_stream_status_slot_description,
			Qsuccessfully_obtained_file_length,Nil,Nil);
	    if (internal_g2_stream_qm) {
		svref_new_value = 
			Internal_status_of_most_recent_file_operation;
		ISVREF(g2_stream_frame,(SI_Long)25L) = svref_new_value;
	    }
	    temp = copy_as_wide_string(string_constant_6);
	    return VALUES_2(file_length_qm,temp);
	}
	else {
	    if ( !EQ(Qerror_getting_file_length,ISVREF(g2_stream_frame,
		    (SI_Long)24L)))
		change_slot_description_value_function(g2_stream_frame,
			G2_stream_status_slot_description,
			Qerror_getting_file_length,Nil,Nil);
	    if (internal_g2_stream_qm) {
		svref_new_value = 
			Internal_status_of_most_recent_file_operation;
		ISVREF(g2_stream_frame,(SI_Long)25L) = svref_new_value;
	    }
	    temp = most_recent_file_operation_status_as_text();
	    return VALUES_2(FIX((SI_Long)-1L),temp);
	}
    }
    else {
	if ( !EQ(Qtried_to_get_length_when_closed,ISVREF(g2_stream_frame,
		(SI_Long)24L)))
	    change_slot_description_value_function(g2_stream_frame,
		    G2_stream_status_slot_description,
		    Qtried_to_get_length_when_closed,Nil,Nil);
	if (internal_g2_stream_qm) {
	    svref_new_value = Internal_status_of_most_recent_file_operation;
	    ISVREF(g2_stream_frame,(SI_Long)25L) = svref_new_value;
	}
	temp = copy_as_wide_string(string_constant_14);
	return VALUES_2(FIX((SI_Long)-1L),temp);
    }
}

/* LATEST-DATE-FILE-WAS-MODIFIED-LISP-SIDE */
Object latest_date_file_was_modified_lisp_side(g2_filestring)
    Object g2_filestring;
{
    Object filestring, modification_date_qm, temp, amf_available_array_cons_qm;
    Object amf_array, temp_1, temp_2, amf_result, new_float;

    x_note_fn_call(164,83);
    filestring = export_text_string(2,g2_filestring,Qg2_directory_pathname);
    modification_date_qm = g2_stream_file_modification_date(filestring);
    reclaim_text_string(g2_filestring);
    reclaim_text_string(filestring);
    if (modification_date_qm) {
	temp = copy_as_wide_string(string_constant_6);
	return VALUES_2(modification_date_qm,temp);
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
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,-1.0);
	temp = most_recent_file_operation_status_as_text();
	return VALUES_2(new_float,temp);
    }
}

/* LATEST-DATE-FILE-WAS-ACCESSED-LISP-SIDE */
Object latest_date_file_was_accessed_lisp_side(g2_filestring)
    Object g2_filestring;
{
    Object filestring, access_date_qm, temp, amf_available_array_cons_qm;
    Object amf_array, temp_1, temp_2, amf_result, new_float;

    x_note_fn_call(164,84);
    filestring = export_text_string(2,g2_filestring,Qg2_directory_pathname);
    access_date_qm = EQ(Local_file_system,Qwin32) || EQ(Local_file_system,
	    Qdos) ? g2_stream_file_modification_date(filestring) : 
	    g2_stream_file_access_date(filestring);
    reclaim_text_string(g2_filestring);
    reclaim_text_string(filestring);
    if (access_date_qm) {
	temp = copy_as_wide_string(string_constant_6);
	return VALUES_2(access_date_qm,temp);
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
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,-1.0);
	temp = most_recent_file_operation_status_as_text();
	return VALUES_2(new_float,temp);
    }
}

/* LATEST-DATE-FILE-ATTRIBUTES-WERE-CHANGED-LISP-SIDE */
Object latest_date_file_attributes_were_changed_lisp_side(g2_filestring)
    Object g2_filestring;
{
    Object filestring, change_date_qm, temp, amf_available_array_cons_qm;
    Object amf_array, temp_1, temp_2, amf_result, new_float;

    x_note_fn_call(164,85);
    filestring = export_text_string(2,g2_filestring,Qg2_directory_pathname);
    change_date_qm = g2_stream_file_status_change_date(filestring);
    reclaim_text_string(g2_filestring);
    reclaim_text_string(filestring);
    if (change_date_qm) {
	temp = copy_as_wide_string(string_constant_6);
	return VALUES_2(change_date_qm,temp);
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
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,-1.0);
	temp = most_recent_file_operation_status_as_text();
	return VALUES_2(new_float,temp);
    }
}

/* DIRECTORY-EXISTS-LISP-SIDE */
Object directory_exists_lisp_side(g2_filestring)
    Object g2_filestring;
{
    volatile Object filestring;
    volatile Object directory_as_file_qm;
    Object temp, current_local_filename_parser;
    Object current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p, pathname_qm;
    volatile Object directory_as_namestring;
    Object exists_p;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(1);
    Object result;

    x_note_fn_call(164,86);
    SAVE_STACK();
    filestring = Qunbound_in_protected_let;
    directory_as_file_qm = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(1)) {
	filestring = export_text_string(2,g2_filestring,
		Qg2_directory_pathname);
	temp = gensym_directory_as_file(filestring);
	if (temp);
	else {
	    current_local_filename_parser = Local_filename_parser;
	    current_local_namestring_generator = Local_namestring_generator;
	    convert_file_strings_to_uppercase_p = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
		    Qconvert_file_strings_to_uppercase_p);
	    PUSH_SPECIAL_WITH_SYMBOL(Convert_file_strings_to_uppercase_p,Qconvert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
		    0);
	      pathname_qm = convert_to_gensym_pathname(filestring,
		      current_local_filename_parser,
		      current_local_namestring_generator);
	      temp = pathname_qm;
	    POP_SPECIAL();
	}
	directory_as_file_qm = temp;
	if (directory_as_file_qm) {
	    directory_as_namestring = Qunbound_in_protected_let;
	    exists_p = Qunbound_in_protected_let;
	    if (PUSH_UNWIND_PROTECT(0)) {
		directory_as_namestring = gensym_namestring(1,
			directory_as_file_qm);
		exists_p = g2_stream_directory_p(directory_as_namestring);
		SAVE_VALUES(VALUES_1(exists_p ? Evaluation_true_value : 
			Evaluation_false_value));
	    }
	    POP_UNWIND_PROTECT(0);
	    if (directory_as_namestring) {
		if ( !EQ(directory_as_namestring,Qunbound_in_protected_let))
		    reclaim_text_string(directory_as_namestring);
	    }
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	    temp = result;
	}
	else
	    temp = Evaluation_false_value;
	SAVE_VALUES(VALUES_1(temp));
	reclaim_text_string(g2_filestring);
    }
    POP_UNWIND_PROTECT(1);
    if (directory_as_file_qm) {
	if ( !EQ(directory_as_file_qm,Qunbound_in_protected_let)) {
	    if (directory_as_file_qm)
		reclaim_gensym_pathname(directory_as_file_qm);
	}
    }
    if (filestring) {
	if ( !EQ(filestring,Qunbound_in_protected_let))
	    reclaim_text_string(filestring);
    }
    CONTINUE_UNWINDING(1);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* FILES-IN-DIRECTORY-LISP-SIDE */
Object files_in_directory_lisp_side(g2_directory_string)
    Object g2_directory_string;
{
    volatile Object directory_string;
    volatile Object directory_pathname_qm;
    Object accept_any_version_component_p;
    Object canonical_wild_directory_pathname_qm;
    volatile Object pathnames_in_directory;
    Object list_frame, pathname_in_directory, ab_loop_list_;
    volatile Object filestring_in_directory;
    Object converted_filestring, temp, temp_1;
    Declare_stack_pointer;
    Declare_catch(3);
    Declare_special(1);
    Object result;

    x_note_fn_call(164,87);
    SAVE_STACK();
    directory_string = Qunbound_in_protected_let;
    directory_pathname_qm = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(2)) {
	directory_string = export_text_string(2,g2_directory_string,
		Qg2_directory_pathname);
	accept_any_version_component_p = T;
	PUSH_SPECIAL_WITH_SYMBOL(Accept_any_version_component_p,Qaccept_any_version_component_p,accept_any_version_component_p,
		0);
	  directory_pathname_qm = gensym_pathname(directory_string);
	POP_SPECIAL();
	if (directory_pathname_qm) {
	    canonical_wild_directory_pathname_qm = 
		    make_canonical_wild_directory_pathname_if_possible(directory_pathname_qm,
		    directory_string);
	    if (canonical_wild_directory_pathname_qm) {
		reclaim_gensym_pathname(directory_pathname_qm);
		directory_pathname_qm = canonical_wild_directory_pathname_qm;
	    }
	}
	pathnames_in_directory = Qunbound_in_protected_let;
	list_frame = Qunbound_in_protected_let;
	if (PUSH_UNWIND_PROTECT(1)) {
	    pathnames_in_directory = gensym_directory(1,directory_pathname_qm);
	    list_frame = make_transient_item(Qtext_list);
	    pathname_in_directory = Nil;
	    ab_loop_list_ = pathnames_in_directory;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    pathname_in_directory = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (ISVREF(pathname_in_directory,(SI_Long)4L)) {
		filestring_in_directory = Qunbound_in_protected_let;
		converted_filestring = Qunbound_in_protected_let;
		if (PUSH_UNWIND_PROTECT(0)) {
		    filestring_in_directory = gensym_file_namestring(1,
			    pathname_in_directory);
		    converted_filestring = import_text_string(2,
			    filestring_in_directory,Qg2_directory_pathname);
		    g2_list_insert_at_beginning(converted_filestring,
			    list_frame);
		}
		POP_UNWIND_PROTECT(0);
		if (filestring_in_directory) {
		    if ( !EQ(filestring_in_directory,
			    Qunbound_in_protected_let))
			reclaim_text_string(filestring_in_directory);
		}
		CONTINUE_UNWINDING(0);
	    }
	    reclaim_gensym_pathname(pathname_in_directory);
	    goto next_loop;
	  end_loop:
	    reclaim_text_string(g2_directory_string);
	    temp = list_frame;
	    temp_1 = 
		    FIXNUM_NE(Internal_status_of_most_recent_file_operation,
		    File_operation_succeeded_code) ? 
		    most_recent_file_operation_status_as_text() : 
		    copy_as_wide_string(string_constant_6);
	    SAVE_VALUES(VALUES_2(temp,temp_1));
	    goto end_1;
	    SAVE_VALUES(VALUES_1(Qnil));
	  end_1:;
	}
	POP_UNWIND_PROTECT(1);
	if (pathnames_in_directory) {
	    if ( !EQ(pathnames_in_directory,Qunbound_in_protected_let))
		reclaim_path_list_1(pathnames_in_directory);
	}
	CONTINUE_UNWINDING(1);
    }
    POP_UNWIND_PROTECT(2);
    if (directory_pathname_qm) {
	if ( !EQ(directory_pathname_qm,Qunbound_in_protected_let))
	    reclaim_gensym_pathname(directory_pathname_qm);
    }
    if (directory_string) {
	if ( !EQ(directory_string,Qunbound_in_protected_let))
	    reclaim_text_string(directory_string);
    }
    CONTINUE_UNWINDING(2);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* SUBDIRECTORIES-IN-DIRECTORY-LISP-SIDE */
Object subdirectories_in_directory_lisp_side(g2_directory_string)
    Object g2_directory_string;
{
    volatile Object directory_string;
    volatile Object subdirectories_in_directory;
    Object list_frame, subdirectory_in_directory, ab_loop_list_;
    volatile Object filestring_in_directory;
    Object converted_filestring, temp, temp_1;
    Declare_stack_pointer;
    Declare_catch(2);
    Object result;

    x_note_fn_call(164,88);
    SAVE_STACK();
    directory_string = Qunbound_in_protected_let;
    subdirectories_in_directory = Qunbound_in_protected_let;
    list_frame = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(1)) {
	directory_string = export_text_string(2,g2_directory_string,
		Qg2_directory_pathname);
	subdirectories_in_directory = 
		all_subdirectories_in_directory(directory_string);
	list_frame = make_transient_item(Qtext_list);
	subdirectory_in_directory = Nil;
	ab_loop_list_ = subdirectories_in_directory;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	subdirectory_in_directory = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (ISVREF(subdirectory_in_directory,(SI_Long)4L)) {
	    filestring_in_directory = Qunbound_in_protected_let;
	    converted_filestring = Qunbound_in_protected_let;
	    if (PUSH_UNWIND_PROTECT(0)) {
		filestring_in_directory = gensym_file_namestring(1,
			subdirectory_in_directory);
		converted_filestring = import_text_string(2,
			filestring_in_directory,Qg2_directory_pathname);
		g2_list_insert_at_beginning(converted_filestring,list_frame);
	    }
	    POP_UNWIND_PROTECT(0);
	    if (filestring_in_directory) {
		if ( !EQ(filestring_in_directory,Qunbound_in_protected_let))
		    reclaim_text_string(filestring_in_directory);
	    }
	    CONTINUE_UNWINDING(0);
	}
	reclaim_gensym_pathname(subdirectory_in_directory);
	goto next_loop;
      end_loop:
	reclaim_text_string(g2_directory_string);
	temp = list_frame;
	temp_1 = FIXNUM_NE(Internal_status_of_most_recent_file_operation,
		File_operation_succeeded_code) ? 
		most_recent_file_operation_status_as_text() : 
		copy_as_wide_string(string_constant_6);
	SAVE_VALUES(VALUES_2(temp,temp_1));
	goto end_1;
	SAVE_VALUES(VALUES_1(Qnil));
      end_1:;
    }
    POP_UNWIND_PROTECT(1);
    if (subdirectories_in_directory) {
	if ( !EQ(subdirectories_in_directory,Qunbound_in_protected_let))
	    reclaim_path_list_1(subdirectories_in_directory);
    }
    if (directory_string) {
	if ( !EQ(directory_string,Qunbound_in_protected_let))
	    reclaim_text_string(directory_string);
    }
    CONTINUE_UNWINDING(1);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* DEFAULT-DIRECTORY-LISP-SIDE */
Object default_directory_lisp_side()
{
    volatile Object raw_default_directory_qm;
    Object temp, temp_1;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(164,89);
    SAVE_STACK();
    raw_default_directory_qm = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	raw_default_directory_qm = g2_stream_get_default_directory();
	if (raw_default_directory_qm) {
	    temp = import_text_string(2,raw_default_directory_qm,
		    Qg2_directory_pathname);
	    temp_1 = copy_as_wide_string(string_constant_6);
	    SAVE_VALUES(VALUES_2(temp,temp_1));
	}
	else {
	    temp = copy_as_wide_string(string_constant_6);
	    temp_1 = most_recent_file_operation_status_as_text();
	    SAVE_VALUES(VALUES_2(temp,temp_1));
	}
    }
    POP_UNWIND_PROTECT(0);
    if (raw_default_directory_qm) {
	if ( !EQ(raw_default_directory_qm,Qunbound_in_protected_let))
	    reclaim_text_string(raw_default_directory_qm);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object Qforeign_image;      /* foreign-image */

static Object Qattribute;          /* attribute */

static Object Qstatistics;         /* statistics */

static Object Qkb;                 /* kb */

/* CHANGE-DEFAULT-DIRECTORY-LISP-SIDE */
Object change_default_directory_lisp_side(g2_new_directory_string)
    Object g2_new_directory_string;
{
    volatile Object new_directory_string;
    volatile Object new_directory_pathname_qm;
    volatile Object changed_p;
    volatile Object dwim_directory_string;
    Object new_value, temp, temp_1;
    Declare_stack_pointer;
    Declare_catch(2);
    Object result;

    x_note_fn_call(164,90);
    SAVE_STACK();
    new_directory_string = Qunbound_in_protected_let;
    new_directory_pathname_qm = Qunbound_in_protected_let;
    changed_p = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(1)) {
	new_directory_string = export_text_string(2,
		g2_new_directory_string,Qg2_directory_pathname);
	new_directory_pathname_qm = 
		get_new_directory_pathname_dwim(new_directory_string);
	changed_p = Nil;
	if (new_directory_pathname_qm) {
	    dwim_directory_string = Qunbound_in_protected_let;
	    if (PUSH_UNWIND_PROTECT(0)) {
		dwim_directory_string = gensym_namestring(1,
			new_directory_pathname_qm);
		if (g2_stream_change_default_directory(dwim_directory_string)) 
			    {
		    if (Current_foreign_image_pathname_qm) {
			new_value = 
				gensym_merge_pathnames_function(new_directory_pathname_qm,
				Current_foreign_image_pathname_qm,Nil);
			reclaim_pathname_or_string(Current_foreign_image_pathname_qm);
			if (text_string_p(new_value)) {
			    temp = gensym_pathname(new_value);
			    reclaim_text_string(new_value);
			    Current_foreign_image_pathname_qm = temp;
			}
			else
			    Current_foreign_image_pathname_qm = new_value;
		    }
		    else
			Current_foreign_image_pathname_qm = 
				make_first_time_default_pathname(Qforeign_image);
		    if (Current_attribute_file_pathname_qm) {
			new_value = 
				gensym_merge_pathnames_function(new_directory_pathname_qm,
				Current_attribute_file_pathname_qm,Nil);
			reclaim_pathname_or_string(Current_attribute_file_pathname_qm);
			if (text_string_p(new_value)) {
			    temp = gensym_pathname(new_value);
			    reclaim_text_string(new_value);
			    Current_attribute_file_pathname_qm = temp;
			}
			else
			    Current_attribute_file_pathname_qm = new_value;
		    }
		    else
			Current_attribute_file_pathname_qm = 
				make_first_time_default_pathname(Qattribute);
		    if (Current_statistics_file_pathname_qm) {
			new_value = 
				gensym_merge_pathnames_function(new_directory_pathname_qm,
				Current_statistics_file_pathname_qm,Nil);
			reclaim_pathname_or_string(Current_statistics_file_pathname_qm);
			if (text_string_p(new_value)) {
			    temp = gensym_pathname(new_value);
			    reclaim_text_string(new_value);
			    Current_statistics_file_pathname_qm = temp;
			}
			else
			    Current_statistics_file_pathname_qm = new_value;
		    }
		    else
			Current_statistics_file_pathname_qm = 
				make_first_time_default_pathname(Qstatistics);
		    if (Current_kb_pathname_qm) {
			new_value = 
				gensym_merge_pathnames_function(new_directory_pathname_qm,
				Current_kb_pathname_qm,Nil);
			reclaim_pathname_or_string(Current_kb_pathname_qm);
			if (text_string_p(new_value)) {
			    temp = gensym_pathname(new_value);
			    reclaim_text_string(new_value);
			    Current_kb_pathname_qm = temp;
			}
			else
			    Current_kb_pathname_qm = new_value;
		    }
		    else
			Current_kb_pathname_qm = 
				make_first_time_default_pathname(Qkb);
		    if ( !TRUEP(ISVREF(Log_file_parameters,(SI_Long)23L))) {
			if (Log_file_default_pathname_qm) {
			    new_value = 
				    gensym_merge_pathnames_function(new_directory_pathname_qm,
				    Log_file_default_pathname_qm,Nil);
			    reclaim_pathname_or_string(Log_file_default_pathname_qm);
			    if (text_string_p(new_value)) {
				temp = gensym_pathname(new_value);
				reclaim_text_string(new_value);
				Log_file_default_pathname_qm = temp;
			    }
			    else
				Log_file_default_pathname_qm = new_value;
			}
			else
			    Log_file_default_pathname_qm = 
				    make_first_time_default_pathname(Qlog);
		    }
		    changed_p = T;
		}
	    }
	    POP_UNWIND_PROTECT(0);
	    if (dwim_directory_string) {
		if ( !EQ(dwim_directory_string,Qunbound_in_protected_let))
		    reclaim_text_string(dwim_directory_string);
	    }
	    CONTINUE_UNWINDING(0);
	}
	reclaim_evaluation_value(g2_new_directory_string);
	if (changed_p) {
	    temp_1 = Evaluation_true_value;
	    temp = copy_as_wide_string(string_constant_6);
	    SAVE_VALUES(VALUES_2(temp_1,temp));
	}
	else {
	    temp_1 = Evaluation_false_value;
	    temp = most_recent_file_operation_status_as_text();
	    SAVE_VALUES(VALUES_2(temp_1,temp));
	}
    }
    POP_UNWIND_PROTECT(1);
    if (new_directory_pathname_qm) {
	if ( !EQ(new_directory_pathname_qm,Qunbound_in_protected_let))
	    reclaim_gensym_pathname(new_directory_pathname_qm);
    }
    if (new_directory_string) {
	if ( !EQ(new_directory_string,Qunbound_in_protected_let))
	    reclaim_text_string(new_directory_string);
    }
    CONTINUE_UNWINDING(1);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object string_constant_15;  /* "g2" */

static Object string_constant_16;  /* "Unable to obtain temporary filename from operating system." */

/* GET-TEMPORARY-FILENAME-LISP-SIDE */
Object get_temporary_filename_lisp_side()
{
    Object val, top_of_stack, message_1, temp;

    x_note_fn_call(164,91);
    val = make_unique_file_name(string_constant_15);
    if ( !TRUEP(val)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_16);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    temp = copy_as_wide_string(val);
    return VALUES_1(temp);
}

/* DISK-SPACE-AVAILABLE-IN-DIRECTORY-LISP-SIDE */
Object disk_space_available_in_directory_lisp_side(g2_directory_filestring)
    Object g2_directory_filestring;
{
    Object directory_filestring, space_available_qm, temp;

    x_note_fn_call(164,92);
    directory_filestring = export_text_string(2,g2_directory_filestring,
	    Qg2_directory_pathname);
    space_available_qm = 
	    g2_stream_available_disk_space_in_device(directory_filestring);
    reclaim_text_string(g2_directory_filestring);
    reclaim_text_string(directory_filestring);
    if (space_available_qm) {
	temp = copy_as_wide_string(string_constant_6);
	return VALUES_2(space_available_qm,temp);
    }
    else {
	temp = most_recent_file_operation_status_as_text();
	return VALUES_2(FIX((SI_Long)-1L),temp);
    }
}

/* DEVICES-ON-MACHINE-LISP-SIDE */
Object devices_on_machine_lisp_side()
{
    Object device_names, list_frame, device_name, ab_loop_list_;

    x_note_fn_call(164,93);
    device_names = g2_stream_devices();
    list_frame = make_transient_item(Qtext_list);
    device_name = Nil;
    ab_loop_list_ = device_names;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    device_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2_list_insert_at_beginning(device_name,list_frame);
    goto next_loop;
  end_loop:
    reclaim_path_list_1(device_names);
    return VALUES_1(list_frame);
}

/* CREATE-DIRECTORY-LISP-SIDE */
Object create_directory_lisp_side(g2_filestring,create_parents_tv,mask)
    Object g2_filestring, create_parents_tv, mask;
{
    Object filestring, success_qm, temp;
    SI_Long do_create_parent;

    x_note_fn_call(164,94);
    filestring = export_text_string(2,g2_filestring,Qg2_directory_pathname);
    do_create_parent = evaluation_truth_value_is_true_p(create_parents_tv) 
	    ? (SI_Long)1L : (SI_Long)0L;
    success_qm = c_g2_create_directory(filestring,FIX(do_create_parent),mask);
    temp = EQ(success_qm,FIX((SI_Long)1L)) ? Evaluation_true_value : 
	    Evaluation_false_value;
    reclaim_text_string(g2_filestring);
    reclaim_text_string(mask);
    reclaim_text_string(filestring);
    return VALUES_1(temp);
}

static Object Qversion_text;       /* version-text */

static Object Qsystem_version;     /* system-version */

static Object string_constant_17;  /* "G2 ~d.~d ~a" */

static Object Qmajor_version_number;  /* major-version-number */

static Object Qminor_version_number;  /* minor-version-number */

static Object Qrevision_text;      /* revision-text */

/* G2-VERSION-OF-KB-FILE */
Object g2_version_of_kb_file(pathname_1)
    Object pathname_1;
{
    Object full_pathname, plist, temp, system_version, major, floor_1, rem_1;
    Object minor, string_1, gensymed_symbol, gensymed_symbol_1, car_new_value;
    Object result;

    x_note_fn_call(164,95);
    full_pathname = make_full_pathname(pathname_1);
    plist = read_initial_plist(full_pathname,Nil,Nil);
    if ( !TRUEP(plist))
	temp = allocate_evaluation_structure(eval_list_2(Qversion_text,
		copy_as_wide_string(string_constant_6)));
    else {
	system_version = getf(plist,Qsystem_version,_);
	major = FIRST(system_version);
	result = chestnut_floorf_function(SECOND(system_version),
		FIX((SI_Long)10L));
	MVS_2(result,floor_1,rem_1);
	minor = IFIX(rem_1) == (SI_Long)0L ? floor_1 : SECOND(system_version);
	string_1 = FOURTH(system_version);
	gensymed_symbol = make_eval_list_1(FIX((SI_Long)8L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = Qversion_text;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = tformat_text_string(4,string_constant_17,major,
		minor,string_1);
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qmajor_version_number;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = major;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qminor_version_number;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = minor;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qrevision_text;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = copy_as_wide_string(string_1);
	M_CAR(gensymed_symbol_1) = car_new_value;
	temp = allocate_evaluation_structure(gensymed_symbol);
    }
    reclaim_gensym_pathname(full_pathname);
    reclaim_slot_value(plist);
    reclaim_text_string(pathname_1);
    return VALUES_1(temp);
}

static Object Qvms;                /* vms */

/* KILL-POSSIBLY-LEFTOVER-SPAWNED-PROCESS */
Object kill_possibly_leftover_spawned_process(process_id)
    Object process_id;
{
    x_note_fn_call(164,96);
    if ( !EQ(G2_operating_system,Qvms) || 
	    g2ext_process_exists(DFLOAT_ISAREF_1(process_id,(SI_Long)0L)) 
	    == (SI_Long)1L)
	g2ext_kill_spawned_command_line(DFLOAT_ISAREF_1(process_id,
		(SI_Long)0L));
    reclaim_managed_simple_float_array_of_length_1(process_id);
    return VALUES_1(Nil);
}

/* SPAWN-PROCESS-TO-RUN-COMMAND-LINE-LISP-SIDE */
Object spawn_process_to_run_command_line_lisp_side(g2_process_namestring)
    Object g2_process_namestring;
{
    Object process_namestring, process_id, amf_available_array_cons_qm;
    Object amf_array, temp, temp_1, amf_result, new_float;
    double arg, arg_1, aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(164,97);
    process_namestring = 
	    convert_text_string_to_ascii_as_much_as_possible(g2_process_namestring);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	process_id = c_spawn_command_line_process(process_namestring);
	reclaim_text_string(g2_process_namestring);
	reclaim_text_string(process_namestring);
	arg = -1.0;
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(process_id);
	if ( !(arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1))) {
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
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(process_id);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    Known_process_ids_qm = sysproc_cons_1(new_float,
		    Known_process_ids_qm);
	}
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
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(process_id);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	result = VALUES_1(new_float);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* SPAWN-PROCESS-WITH-ARGUMENTS-LISP-SIDE */
Object spawn_process_with_arguments_lisp_side(g2_process_namestring)
    Object g2_process_namestring;
{
    Object process_namestring, process_id, amf_available_array_cons_qm;
    Object amf_array, temp, temp_1, amf_result, new_float;
    double arg, arg_1, aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(164,98);
    process_namestring = 
	    convert_text_string_to_ascii_as_much_as_possible(g2_process_namestring);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	process_id = c_spawn_executable_process(process_namestring);
	reclaim_text_string(g2_process_namestring);
	reclaim_text_string(process_namestring);
	arg = -1.0;
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(process_id);
	if ( !(arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1))) {
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
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(process_id);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    Known_process_ids_qm = sysproc_cons_1(new_float,
		    Known_process_ids_qm);
	}
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
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(process_id);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	result = VALUES_1(new_float);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_sysproc_continuation_hashtable_hash_vector_131_vectors, Qavailable_sysproc_continuation_hashtable_hash_vector_131_vectors);

DEFINE_VARIABLE_WITH_SYMBOL(Count_of_sysproc_continuation_hashtable_hash_vector_131_vectors, Qcount_of_sysproc_continuation_hashtable_hash_vector_131_vectors);

Object Available_sysproc_continuation_hashtable_hash_vector_131_vectors_vector = UNBOUND;

/* SYSPROC-CONTINUATION-HASHTABLE-HASH-VECTOR-131-VECTOR-MEMORY-USAGE */
Object sysproc_continuation_hashtable_hash_vector_131_vector_memory_usage()
{
    Object temp;

    x_note_fn_call(164,99);
    temp = Count_of_sysproc_continuation_hashtable_hash_vector_131_vectors;
    temp = FIXNUM_TIMES(temp,bytes_per_typed_simple_array(T,
	    FIX((SI_Long)131L)));
    return VALUES_1(temp);
}

/* OUT-SYSPROC-CONTINUATION-HASHTABLE-HASH-VECTOR-131-VECTORS */
Object out_sysproc_continuation_hashtable_hash_vector_131_vectors()
{
    Object temp;

    x_note_fn_call(164,100);
    temp = 
	    FIXNUM_MINUS(Count_of_sysproc_continuation_hashtable_hash_vector_131_vectors,
	    length(Available_sysproc_continuation_hashtable_hash_vector_131_vectors));
    return VALUES_1(temp);
}

/* MAKE-PERMANENT-SYSPROC-CONTINUATION-HASHTABLE-HASH-VECTOR-131-VECTOR-INTERNAL */
Object make_permanent_sysproc_continuation_hashtable_hash_vector_131_vector_internal()
{
    Object temp;
    XDeclare_area(1);

    x_note_fn_call(164,101);
    atomic_incff_symval(Qcount_of_sysproc_continuation_hashtable_hash_vector_131_vectors,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0))
	temp = make_array(3,FIX((SI_Long)131L),Kinitial_element,Nil);
    POP_AREA(0);
    return VALUES_1(temp);
}

static Object Qvector_pool;        /* vector-pool */

/* MAKE-SYSPROC-CONTINUATION-HASHTABLE-HASH-VECTOR */
Object make_sysproc_continuation_hashtable_hash_vector()
{
    Object temp, svref_arg_1, svref_arg_2, temp_1, vector_pool_cons, temp_2;
    Object svref_arg_2_1;

    x_note_fn_call(164,102);
    if (ISVREF(Available_sysproc_continuation_hashtable_hash_vector_131_vectors_vector,
	    IFIX(Current_thread_index))) {
	temp = 
		M_CAR(ISVREF(Available_sysproc_continuation_hashtable_hash_vector_131_vectors_vector,
		IFIX(Current_thread_index)));
	svref_arg_1 = 
		Available_sysproc_continuation_hashtable_hash_vector_131_vectors_vector;
	svref_arg_2 = Current_thread_index;
	temp_1 = 
		M_CDR(ISVREF(Available_sysproc_continuation_hashtable_hash_vector_131_vectors_vector,
		IFIX(Current_thread_index)));
	vector_pool_cons = 
		ISVREF(Available_sysproc_continuation_hashtable_hash_vector_131_vectors_vector,
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
		make_permanent_sysproc_continuation_hashtable_hash_vector_131_vector_internal();
    return VALUES_1(temp);
}

/* RECLAIM-SYSPROC-CONTINUATION-HASHTABLE-HASH-VECTOR */
Object reclaim_sysproc_continuation_hashtable_hash_vector(sysproc_continuation_hashtable_hash_vector_131_vector)
    Object sysproc_continuation_hashtable_hash_vector_131_vector;
{
    Object svref_arg_1, svref_arg_2, new_cons, temp, svref_arg_2_1;
    Object svref_new_value, gensymed_symbol;

    x_note_fn_call(164,103);
    svref_arg_1 = 
	    Available_sysproc_continuation_hashtable_hash_vector_131_vectors_vector;
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
	    sysproc_continuation_hashtable_hash_vector_131_vector;
    temp = 
	    ISVREF(Available_sysproc_continuation_hashtable_hash_vector_131_vectors_vector,
	    IFIX(Current_thread_index));
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qvector_pool);
    SVREF(svref_arg_1,svref_arg_2) = gensymed_symbol;
    return VALUES_1(Nil);
}

static Object Qlookup;             /* lookup */

/* RECLAIM-SYSPROC-CONTINUATION-HASHTABLE-TREE-FOR-HASH-LEAVES */
Object reclaim_sysproc_continuation_hashtable_tree_for_hash_leaves(sysproc_continuation_hashtable_tree_for_hash_binary_tree)
    Object sysproc_continuation_hashtable_tree_for_hash_binary_tree;
{
    Object less_than_branch_qm, greater_than_branch_qm, alist, alist_entry;
    Object ab_loop_list_, temp, svref_arg_2, last_1, next_qm, temp_1;

    x_note_fn_call(164,104);
    less_than_branch_qm = Nil;
    greater_than_branch_qm = Nil;
    alist = Nil;
  next_loop:
    if ( !TRUEP(sysproc_continuation_hashtable_tree_for_hash_binary_tree))
	goto end_loop;
    less_than_branch_qm = 
	    ISVREF(sysproc_continuation_hashtable_tree_for_hash_binary_tree,
	    (SI_Long)1L);
    greater_than_branch_qm = 
	    ISVREF(sysproc_continuation_hashtable_tree_for_hash_binary_tree,
	    (SI_Long)2L);
    alist = 
	    ISVREF(sysproc_continuation_hashtable_tree_for_hash_binary_tree,
	    (SI_Long)3L);
    reclaim_binary_tree_element_1(sysproc_continuation_hashtable_tree_for_hash_binary_tree);
    alist_entry = Nil;
    ab_loop_list_ = alist;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    alist_entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    inline_note_reclaim_cons(alist_entry,Qlookup);
    if (ISVREF(Available_lookup_conses_tail_vector,
		IFIX(Current_thread_index))) {
	temp = ISVREF(Available_lookup_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = alist_entry;
	temp = Available_lookup_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = alist_entry;
    }
    else {
	temp = Available_lookup_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = alist_entry;
	temp = Available_lookup_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = alist_entry;
    }
    M_CDR(alist_entry) = Nil;
    goto next_loop_1;
  end_loop_1:;
    if (alist) {
	last_1 = alist;
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
	    temp = ISVREF(Available_lookup_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = alist;
	    temp = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_lookup_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = alist;
	    temp = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    if (less_than_branch_qm && greater_than_branch_qm) {
	reclaim_sysproc_continuation_hashtable_tree_for_hash_leaves(less_than_branch_qm);
	sysproc_continuation_hashtable_tree_for_hash_binary_tree = 
		greater_than_branch_qm;
    }
    else {
	temp_1 = less_than_branch_qm;
	if (temp_1);
	else
	    temp_1 = greater_than_branch_qm;
	sysproc_continuation_hashtable_tree_for_hash_binary_tree = temp_1;
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* CLEAR-SYSPROC-CONTINUATION-HASHTABLE-TREE */
Object clear_sysproc_continuation_hashtable_tree(sysproc_continuation_hashtable_tree_for_hash_binary_tree)
    Object sysproc_continuation_hashtable_tree_for_hash_binary_tree;
{
    Object element_qm;

    x_note_fn_call(164,105);
    element_qm = CDR(sysproc_continuation_hashtable_tree_for_hash_binary_tree);
    if (element_qm) {
	reclaim_sysproc_continuation_hashtable_tree_for_hash_leaves(element_qm);
	M_CDR(sysproc_continuation_hashtable_tree_for_hash_binary_tree) = Nil;
    }
    return VALUES_1(sysproc_continuation_hashtable_tree_for_hash_binary_tree);
}

static Object Qsysproc_continuation_hashtable_tree_for_hash;  /* sysproc-continuation-hashtable-tree-for-hash */

/* MAKE-SYSPROC-CONTINUATION-HASHTABLE */
Object make_sysproc_continuation_hashtable()
{
    Object new_vector, new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, temp;
    SI_Long index_1;

    x_note_fn_call(164,106);
    new_vector = make_sysproc_continuation_hashtable_hash_vector();
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)131L)
	goto end_loop;
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
    M_CAR(gensymed_symbol) = Qsysproc_continuation_hashtable_tree_for_hash;
    M_CDR(gensymed_symbol) = Nil;
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

/* FLATTEN-SYSPROC-CONTINUATION-HASHTABLE */
Object flatten_sysproc_continuation_hashtable(sysproc_continuation_hashtable_hash_table)
    Object sysproc_continuation_hashtable_hash_table;
{
    Object result_1, subtree, temp;
    SI_Long index_1;

    x_note_fn_call(164,107);
    result_1 = Nil;
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)131L)
	goto end_loop;
    subtree = ISVREF(sysproc_continuation_hashtable_hash_table,index_1);
    if (subtree) {
	temp = flatten_binary_tree(CDR(subtree));
	result_1 = nconc2(temp,result_1);
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(result_1);
}

/* CLEAR-SYSPROC-CONTINUATION-HASHTABLE */
Object clear_sysproc_continuation_hashtable(sysproc_continuation_hashtable_hash_table)
    Object sysproc_continuation_hashtable_hash_table;
{
    SI_Long index_1;

    x_note_fn_call(164,108);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)131L)
	goto end_loop;
    clear_sysproc_continuation_hashtable_tree(ISVREF(sysproc_continuation_hashtable_hash_table,
	    index_1));
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* RECLAIM-SYSPROC-CONTINUATION-HASHTABLE */
Object reclaim_sysproc_continuation_hashtable(sysproc_continuation_hashtable_hash_table)
    Object sysproc_continuation_hashtable_hash_table;
{
    Object sysproc_continuation_hashtable_tree_for_hash_binary_tree;
    Object element_qm, temp, svref_arg_2, temp_1;
    SI_Long index_1;

    x_note_fn_call(164,109);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)131L)
	goto end_loop;
    sysproc_continuation_hashtable_tree_for_hash_binary_tree = 
	    ISVREF(sysproc_continuation_hashtable_hash_table,index_1);
    element_qm = 
	    M_CDR(sysproc_continuation_hashtable_tree_for_hash_binary_tree);
    if (element_qm)
	reclaim_sysproc_continuation_hashtable_tree_for_hash_leaves(element_qm);
    inline_note_reclaim_cons(sysproc_continuation_hashtable_tree_for_hash_binary_tree,
	    Qlookup);
    if (ISVREF(Available_lookup_conses_tail_vector,
		IFIX(Current_thread_index))) {
	temp = ISVREF(Available_lookup_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = sysproc_continuation_hashtable_tree_for_hash_binary_tree;
	temp = Available_lookup_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = 
		sysproc_continuation_hashtable_tree_for_hash_binary_tree;
    }
    else {
	temp = Available_lookup_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = 
		sysproc_continuation_hashtable_tree_for_hash_binary_tree;
	temp = Available_lookup_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = 
		sysproc_continuation_hashtable_tree_for_hash_binary_tree;
    }
    M_CDR(sysproc_continuation_hashtable_tree_for_hash_binary_tree) = Nil;
    ISVREF(sysproc_continuation_hashtable_hash_table,index_1) = Nil;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    temp_1 = 
	    reclaim_sysproc_continuation_hashtable_hash_vector(sysproc_continuation_hashtable_hash_table);
    return VALUES_1(temp_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Sysproc_continuation_table, Qsysproc_continuation_table);

DEFINE_VARIABLE_WITH_SYMBOL(Highest_remote_spawn_index, Qhighest_remote_spawn_index);

DEFINE_VARIABLE_WITH_SYMBOL(Used_remote_spawn_indices_qm, Qused_remote_spawn_indices_qm);

/* GET-NEW-REMOTE-SPAWN-INDEX */
Object get_new_remote_spawn_index()
{
    Object sysproc_pop_store, cons_1, next_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(164,110);
    if (Used_remote_spawn_indices_qm) {
	sysproc_pop_store = Nil;
	cons_1 = Used_remote_spawn_indices_qm;
	if (cons_1) {
	    sysproc_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qsysproc);
	    if (ISVREF(Available_sysproc_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_sysproc_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = cons_1;
		temp = Available_sysproc_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    else {
		temp = Available_sysproc_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
		temp = Available_sysproc_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	Used_remote_spawn_indices_qm = next_cons;
	temp_1 = sysproc_pop_store;
    }
    else {
	temp = FIXNUM_ADD1(Highest_remote_spawn_index);
	Highest_remote_spawn_index = temp;
	temp_1 = Highest_remote_spawn_index;
    }
    return VALUES_1(temp_1);
}

static Object Qno_internal_window;  /* no-internal-window */

static Object Qremote_processes_unsupported;  /* remote-processes-unsupported */

static Object Qnot_a_remote_process;  /* not-a-remote-process */

/* GET-REMOTE-PROCESS-PROBLEM-SYMBOL-IF-ANY */
Object get_remote_process_problem_symbol_if_any(g2_window,
	    spawn_as_executable_p)
    Object g2_window, spawn_as_executable_p;
{
    Object gensym_window_qm, icp_socket_of_window_qm;

    x_note_fn_call(164,111);
    gensym_window_qm = get_gensym_window_for_g2_window(g2_window);
    if ( !TRUEP(gensym_window_qm))
	return VALUES_1(Qno_internal_window);
    if ( !(spawn_as_executable_p ? 
	    FIXNUM_LT(Icp_window_protocol_supports_remote_executables,
	    ISVREF(gensym_window_qm,(SI_Long)11L)) : 
	    FIXNUM_LT(Icp_window_protocol_supports_remote_processes,
	    ISVREF(gensym_window_qm,(SI_Long)11L))))
	return VALUES_1(Qremote_processes_unsupported);
    icp_socket_of_window_qm = get_icp_socket_for_g2_window(g2_window);
    if ( !TRUEP(icp_socket_of_window_qm))
	return VALUES_1(Qnot_a_remote_process);
    return VALUES_1(Nil);
    return VALUES_1(Qnil);
}

/* CLEAN-UP-SYSPROC-CONTINUATION */
Object clean_up_sysproc_continuation(completion_form)
    Object completion_form;
{
    Object remote_spawn_index, temp;
    SI_Long gensymed_symbol, temp_1;

    x_note_fn_call(164,112);
    remote_spawn_index = SECOND(completion_form);
    gensymed_symbol = IFIX(sxhashw(remote_spawn_index));
    temp = Sysproc_continuation_table;
    temp_1 = gensymed_symbol % (SI_Long)131L;
    set_balanced_binary_tree_entry(SVREF(temp,FIX(temp_1)),Qeql,Nil,T,
	    remote_spawn_index,FIX(gensymed_symbol),Nil);
    Used_remote_spawn_indices_qm = sysproc_cons_1(remote_spawn_index,
	    Used_remote_spawn_indices_qm);
    temp = reclaim_sysproc_list_1(completion_form);
    return VALUES_1(temp);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qremote_process_procedure_requires_g2_window;  /* remote-process-procedure-requires-g2-window */

static Object Qclean_up_sysproc_continuation;  /* clean-up-sysproc-continuation */

static Object Qtelewindows;        /* telewindows */

static Object Qremote_spawn_initiated;  /* remote-spawn-initiated */

/* SPAWN-REMOTE-PROCESS-LISP-SIDE */
Object spawn_remote_process_lisp_side(g2_process_namestring,g2_window)
    Object g2_process_namestring, g2_window;
{
    Object x2, gensymed_symbol, sub_class_bit_vector, problem_symbol_qm;
    Object code_body_invocation_to_receive_spawn_status, icp_socket_of_window;
    Object temp_1, process_namestring, remote_spawn_index, current_icp_port;
    Object current_icp_socket, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object aref_arg_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp_2;
    char temp;
    double gensymed_symbol_4, gensymed_symbol_5, gensymed_symbol_6;
    double gensymed_symbol_7, gensymed_symbol_8, aref_new_value;
    Declare_special(12);

    x_note_fn_call(164,113);
    if (SIMPLE_VECTOR_P(g2_window) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(g2_window)) > (SI_Long)2L &&  
	    !EQ(ISVREF(g2_window,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(g2_window,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(G2_window_class_description,(SI_Long)18L));
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
    problem_symbol_qm =  !temp ? 
	    Qremote_process_procedure_requires_g2_window : Nil;
    if (problem_symbol_qm);
    else
	problem_symbol_qm = 
		get_remote_process_problem_symbol_if_any(g2_window,Nil);
    if (problem_symbol_qm) {
	reclaim_text_string(g2_process_namestring);
	return VALUES_1(problem_symbol_qm);
    }
    else {
	code_body_invocation_to_receive_spawn_status = 
		Current_computation_instance;
	icp_socket_of_window = get_icp_socket_for_g2_window(g2_window);
	temp_1 = 
		convert_text_string_to_ascii_as_much_as_possible(g2_process_namestring);
	reclaim_text_string(g2_process_namestring);
	process_namestring = temp_1;
	remote_spawn_index = get_new_remote_spawn_index();
	gensymed_symbol_1 = IFIX(sxhashw(remote_spawn_index));
	temp_1 = Sysproc_continuation_table;
	temp_2 = gensymed_symbol_1 % (SI_Long)131L;
	set_balanced_binary_tree_entry(SVREF(temp_1,FIX(temp_2)),Qeql,Nil,
		T,remote_spawn_index,FIX(gensymed_symbol_1),
		code_body_invocation_to_receive_spawn_status);
	install_code_body_invocation_completion_form(code_body_invocation_to_receive_spawn_status,
		sysproc_list_2(Qclean_up_sysproc_continuation,
		remote_spawn_index));
	current_icp_port = ISVREF(icp_socket_of_window,(SI_Long)4L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		11);
	  current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
		  10);
	    temp_1 = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) 
		    : Nil;
	    if (temp_1);
	    else
		temp_1 = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
			Qtelewindows) ? T : Nil;
	    disable_resumability = temp_1;
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
		      number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
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
				gensymed_symbol_4 = 0.0;
				gensymed_symbol_5 = 0.0;
				if (Profiling_enabled_qm) {
				    gensymed_symbol = T;
				    gensymed_symbol_4 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_5 = 
					    g2ext_unix_time_as_float();
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    gensymed_symbol_5);
				}
				if (icp_connection_open_p(Current_icp_socket) 
					&&  
					!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					    {
				    send_icp_spawn_remote_process(remote_spawn_index,
					    process_namestring);
				    end_icp_message_group();
				}
				if (Profiling_enabled_qm) {
				    gensymed_symbol_6 = 
					    g2ext_unix_time_as_float();
				    gensymed_symbol_7 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_8 = gensymed_symbol_6 
					    - gensymed_symbol_7;
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L);
				    aref_new_value = gensymed_symbol_8 + 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L),(SI_Long)0L);
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    aref_new_value);
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    aref_new_value = gensymed_symbol ? 
					    gensymed_symbol_4 + 
					    gensymed_symbol_8 + 
					    (gensymed_symbol_7 - 
					    gensymed_symbol_5) : 
					    gensymed_symbol_6;
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
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
	reclaim_text_string(process_namestring);
	return VALUES_1(Qremote_spawn_initiated);
    }
}

/* G2-SPAWN-REMOTE-PROCESS-TO-RUN-COMMAND-LINE-LISP-SIDE */
Object g2_spawn_remote_process_to_run_command_line_lisp_side(g2_process_namestring,
	    g2_window)
    Object g2_process_namestring, g2_window;
{
    Object x2, gensymed_symbol, sub_class_bit_vector, problem_symbol_qm;
    Object code_body_invocation_to_receive_spawn_status, icp_socket_of_window;
    Object temp_1, process_namestring, remote_spawn_index, current_icp_port;
    Object current_icp_socket, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object aref_arg_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp_2;
    char temp;
    double gensymed_symbol_4, gensymed_symbol_5, gensymed_symbol_6;
    double gensymed_symbol_7, gensymed_symbol_8, aref_new_value;
    Declare_special(12);

    x_note_fn_call(164,114);
    if (SIMPLE_VECTOR_P(g2_window) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(g2_window)) > (SI_Long)2L &&  
	    !EQ(ISVREF(g2_window,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(g2_window,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(G2_window_class_description,(SI_Long)18L));
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
    problem_symbol_qm =  !temp ? 
	    Qremote_process_procedure_requires_g2_window : Nil;
    if (problem_symbol_qm);
    else
	problem_symbol_qm = 
		get_remote_process_problem_symbol_if_any(g2_window,Nil);
    if (problem_symbol_qm) {
	reclaim_text_string(g2_process_namestring);
	return VALUES_1(problem_symbol_qm);
    }
    else {
	code_body_invocation_to_receive_spawn_status = 
		Current_computation_instance;
	icp_socket_of_window = get_icp_socket_for_g2_window(g2_window);
	temp_1 = 
		convert_text_string_to_ascii_as_much_as_possible(g2_process_namestring);
	reclaim_text_string(g2_process_namestring);
	process_namestring = temp_1;
	remote_spawn_index = get_new_remote_spawn_index();
	gensymed_symbol_1 = IFIX(sxhashw(remote_spawn_index));
	temp_1 = Sysproc_continuation_table;
	temp_2 = gensymed_symbol_1 % (SI_Long)131L;
	set_balanced_binary_tree_entry(SVREF(temp_1,FIX(temp_2)),Qeql,Nil,
		T,remote_spawn_index,FIX(gensymed_symbol_1),
		code_body_invocation_to_receive_spawn_status);
	install_code_body_invocation_completion_form(code_body_invocation_to_receive_spawn_status,
		sysproc_list_2(Qclean_up_sysproc_continuation,
		remote_spawn_index));
	current_icp_port = ISVREF(icp_socket_of_window,(SI_Long)4L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		11);
	  current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
		  10);
	    temp_1 = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) 
		    : Nil;
	    if (temp_1);
	    else
		temp_1 = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
			Qtelewindows) ? T : Nil;
	    disable_resumability = temp_1;
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
		      number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
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
				gensymed_symbol_4 = 0.0;
				gensymed_symbol_5 = 0.0;
				if (Profiling_enabled_qm) {
				    gensymed_symbol = T;
				    gensymed_symbol_4 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_5 = 
					    g2ext_unix_time_as_float();
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    gensymed_symbol_5);
				}
				if (icp_connection_open_p(Current_icp_socket) 
					&&  
					!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					    {
				    send_icp_spawn_remote_process(remote_spawn_index,
					    process_namestring);
				    end_icp_message_group();
				}
				if (Profiling_enabled_qm) {
				    gensymed_symbol_6 = 
					    g2ext_unix_time_as_float();
				    gensymed_symbol_7 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_8 = gensymed_symbol_6 
					    - gensymed_symbol_7;
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L);
				    aref_new_value = gensymed_symbol_8 + 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L),(SI_Long)0L);
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    aref_new_value);
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    aref_new_value = gensymed_symbol ? 
					    gensymed_symbol_4 + 
					    gensymed_symbol_8 + 
					    (gensymed_symbol_7 - 
					    gensymed_symbol_5) : 
					    gensymed_symbol_6;
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
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
	reclaim_text_string(process_namestring);
	return VALUES_1(Qremote_spawn_initiated);
    }
}

/* SPAWN-REMOTE-PROCESS-WITH-ARGUMENTS-LISP-SIDE */
Object spawn_remote_process_with_arguments_lisp_side(g2_process_namestring,
	    g2_window)
    Object g2_process_namestring, g2_window;
{
    Object x2, gensymed_symbol, sub_class_bit_vector, problem_symbol_qm;
    Object code_body_invocation_to_receive_spawn_status, icp_socket_of_window;
    Object temp_1, process_namestring, remote_spawn_index, current_icp_port;
    Object current_icp_socket, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object aref_arg_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp_2;
    char temp;
    double gensymed_symbol_4, gensymed_symbol_5, gensymed_symbol_6;
    double gensymed_symbol_7, gensymed_symbol_8, aref_new_value;
    Declare_special(12);

    x_note_fn_call(164,115);
    if (SIMPLE_VECTOR_P(g2_window) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(g2_window)) > (SI_Long)2L &&  
	    !EQ(ISVREF(g2_window,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(g2_window,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(G2_window_class_description,(SI_Long)18L));
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
    problem_symbol_qm =  !temp ? 
	    Qremote_process_procedure_requires_g2_window : Nil;
    if (problem_symbol_qm);
    else
	problem_symbol_qm = 
		get_remote_process_problem_symbol_if_any(g2_window,T);
    if (problem_symbol_qm) {
	reclaim_text_string(g2_process_namestring);
	return VALUES_1(problem_symbol_qm);
    }
    else {
	code_body_invocation_to_receive_spawn_status = 
		Current_computation_instance;
	icp_socket_of_window = get_icp_socket_for_g2_window(g2_window);
	temp_1 = 
		convert_text_string_to_ascii_as_much_as_possible(g2_process_namestring);
	reclaim_text_string(g2_process_namestring);
	process_namestring = temp_1;
	remote_spawn_index = get_new_remote_spawn_index();
	gensymed_symbol_1 = IFIX(sxhashw(remote_spawn_index));
	temp_1 = Sysproc_continuation_table;
	temp_2 = gensymed_symbol_1 % (SI_Long)131L;
	set_balanced_binary_tree_entry(SVREF(temp_1,FIX(temp_2)),Qeql,Nil,
		T,remote_spawn_index,FIX(gensymed_symbol_1),
		code_body_invocation_to_receive_spawn_status);
	install_code_body_invocation_completion_form(code_body_invocation_to_receive_spawn_status,
		sysproc_list_2(Qclean_up_sysproc_continuation,
		remote_spawn_index));
	current_icp_port = ISVREF(icp_socket_of_window,(SI_Long)4L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		11);
	  current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
		  10);
	    temp_1 = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) 
		    : Nil;
	    if (temp_1);
	    else
		temp_1 = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
			Qtelewindows) ? T : Nil;
	    disable_resumability = temp_1;
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
		      number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
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
				gensymed_symbol_4 = 0.0;
				gensymed_symbol_5 = 0.0;
				if (Profiling_enabled_qm) {
				    gensymed_symbol = T;
				    gensymed_symbol_4 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_5 = 
					    g2ext_unix_time_as_float();
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    gensymed_symbol_5);
				}
				if (icp_connection_open_p(Current_icp_socket) 
					&&  
					!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					    {
				    send_icp_spawn_remote_executable(remote_spawn_index,
					    process_namestring);
				    end_icp_message_group();
				}
				if (Profiling_enabled_qm) {
				    gensymed_symbol_6 = 
					    g2ext_unix_time_as_float();
				    gensymed_symbol_7 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_8 = gensymed_symbol_6 
					    - gensymed_symbol_7;
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L);
				    aref_new_value = gensymed_symbol_8 + 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L),(SI_Long)0L);
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    aref_new_value);
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    aref_new_value = gensymed_symbol ? 
					    gensymed_symbol_4 + 
					    gensymed_symbol_8 + 
					    (gensymed_symbol_7 - 
					    gensymed_symbol_5) : 
					    gensymed_symbol_6;
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
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
	reclaim_text_string(process_namestring);
	return VALUES_1(Qremote_spawn_initiated);
    }
}

static Object Qprocess_id;         /* process-id */

/* G2-HANDLE-SPAWN-REMOTE-PROCESS-REPLY */
Object g2_handle_spawn_remote_process_reply(remote_spawn_index,process_id)
    Object remote_spawn_index, process_id;
{
    Object temp, gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_4;
    Object sysproc_continuation_qm;
    SI_Long gensymed_symbol, temp_1, gensymed_symbol_3;

    x_note_fn_call(164,116);
    gensymed_symbol = IFIX(sxhashw(remote_spawn_index));
    temp = Sysproc_continuation_table;
    temp_1 = gensymed_symbol % (SI_Long)131L;
    temp = SVREF(temp,FIX(temp_1));
    gensymed_symbol_1 = CDR(temp);
    gensymed_symbol_2 = remote_spawn_index;
    gensymed_symbol_3 = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(gensymed_symbol_1))
	goto end_loop;
    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol_1,(SI_Long)0L));
    if (gensymed_symbol < gensymed_symbol_3)
	gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
    else if (gensymed_symbol > gensymed_symbol_3)
	gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
    else {
	gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)3L);
	gensymed_symbol_4 = Nil;
      next_loop_1:
	if ( !TRUEP(gensymed_symbol_1))
	    goto end_loop_1;
	gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol_1));
	if (EQL(gensymed_symbol_2,gensymed_symbol_4)) {
	    sysproc_continuation_qm = M_CDR(M_CAR(gensymed_symbol_1));
	    goto end_1;
	}
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:
	sysproc_continuation_qm = Qnil;
      end_1:;
	goto end_2;
    }
    goto next_loop;
  end_loop:
    sysproc_continuation_qm = Qnil;
  end_2:;
    if (sysproc_continuation_qm) {
	set_code_body_invocation_local_name_value(sysproc_continuation_qm,
		Qprocess_id,process_id);
	wake_up_code_body_invocation(sysproc_continuation_qm);
    }
    return VALUES_1(Nil);
}

/* PROCESS-EXISTS-LISP-SIDE */
Object process_exists_lisp_side(g2_process_id)
    Object g2_process_id;
{
    SI_Long return_status;
    double process_id;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(164,117);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	process_id = DFLOAT_ISAREF_1(g2_process_id,(SI_Long)0L);
	reclaim_managed_simple_float_array_of_length_1(g2_process_id);
	return_status = g2ext_process_exists(process_id);
	if ( !((SI_Long)-128L <= return_status && return_status <= 
		(SI_Long)127L))
	    result = VALUES_1(FIX((SI_Long)-1L));
	else
	    switch ((char)return_status) {
	      case 0:
		result = VALUES_1(FIX((SI_Long)0L));
		break;
	      case 1:
		result = VALUES_1(FIX((SI_Long)1L));
		break;
	      default:
		result = VALUES_1(FIX((SI_Long)-1L));
		break;
	    }
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

static Object Qremote_query_initiated;  /* remote-query-initiated */

/* REMOTE-PROCESS-EXISTS-LISP-SIDE */
Object remote_process_exists_lisp_side(g2_process_id,g2_window)
    Object g2_process_id, g2_window;
{
    Object x2, gensymed_symbol, sub_class_bit_vector, problem_symbol_qm;
    Object code_body_invocation_to_receive_query_status, icp_socket_of_window;
    Object remote_query_index, temp_1, current_icp_port, current_icp_socket;
    Object disable_resumability, number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object aref_arg_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp_2;
    char temp;
    double gensymed_symbol_4, gensymed_symbol_5, gensymed_symbol_6;
    double gensymed_symbol_7, gensymed_symbol_8, aref_new_value;
    Declare_special(12);

    x_note_fn_call(164,118);
    if (SIMPLE_VECTOR_P(g2_window) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(g2_window)) > (SI_Long)2L &&  
	    !EQ(ISVREF(g2_window,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(g2_window,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(G2_window_class_description,(SI_Long)18L));
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
    problem_symbol_qm =  !temp ? 
	    Qremote_process_procedure_requires_g2_window : Nil;
    if (problem_symbol_qm);
    else
	problem_symbol_qm = 
		get_remote_process_problem_symbol_if_any(g2_window,Nil);
    if (problem_symbol_qm) {
	reclaim_managed_simple_float_array_of_length_1(g2_process_id);
	return VALUES_1(problem_symbol_qm);
    }
    else {
	code_body_invocation_to_receive_query_status = 
		Current_computation_instance;
	icp_socket_of_window = get_icp_socket_for_g2_window(g2_window);
	remote_query_index = get_new_remote_spawn_index();
	gensymed_symbol_1 = IFIX(sxhashw(remote_query_index));
	temp_1 = Sysproc_continuation_table;
	temp_2 = gensymed_symbol_1 % (SI_Long)131L;
	set_balanced_binary_tree_entry(SVREF(temp_1,FIX(temp_2)),Qeql,Nil,
		T,remote_query_index,FIX(gensymed_symbol_1),
		code_body_invocation_to_receive_query_status);
	install_code_body_invocation_completion_form(code_body_invocation_to_receive_query_status,
		sysproc_list_2(Qclean_up_sysproc_continuation,
		remote_query_index));
	current_icp_port = ISVREF(icp_socket_of_window,(SI_Long)4L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		11);
	  current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
		  10);
	    temp_1 = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) 
		    : Nil;
	    if (temp_1);
	    else
		temp_1 = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
			Qtelewindows) ? T : Nil;
	    disable_resumability = temp_1;
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
		      number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
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
				gensymed_symbol_4 = 0.0;
				gensymed_symbol_5 = 0.0;
				if (Profiling_enabled_qm) {
				    gensymed_symbol = T;
				    gensymed_symbol_4 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_5 = 
					    g2ext_unix_time_as_float();
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    gensymed_symbol_5);
				}
				if (icp_connection_open_p(Current_icp_socket) 
					&&  
					!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					    {
				    send_icp_remote_process_exists_p(remote_query_index,
					    g2_process_id);
				    end_icp_message_group();
				}
				if (Profiling_enabled_qm) {
				    gensymed_symbol_6 = 
					    g2ext_unix_time_as_float();
				    gensymed_symbol_7 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_8 = gensymed_symbol_6 
					    - gensymed_symbol_7;
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L);
				    aref_new_value = gensymed_symbol_8 + 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L),(SI_Long)0L);
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    aref_new_value);
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    aref_new_value = gensymed_symbol ? 
					    gensymed_symbol_4 + 
					    gensymed_symbol_8 + 
					    (gensymed_symbol_7 - 
					    gensymed_symbol_5) : 
					    gensymed_symbol_6;
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
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
	reclaim_managed_simple_float_array_of_length_1(g2_process_id);
	return VALUES_1(Qremote_query_initiated);
    }
}

static Object Qquery_status;       /* query-status */

/* G2-HANDLE-REMOTE-PROCESS-EXISTS-P-REPLY */
Object g2_handle_remote_process_exists_p_reply(remote_query_index,
	    process_status)
    Object remote_query_index, process_status;
{
    Object temp, gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_4;
    Object sysproc_continuation_qm;
    SI_Long gensymed_symbol, temp_1, gensymed_symbol_3;

    x_note_fn_call(164,119);
    gensymed_symbol = IFIX(sxhashw(remote_query_index));
    temp = Sysproc_continuation_table;
    temp_1 = gensymed_symbol % (SI_Long)131L;
    temp = SVREF(temp,FIX(temp_1));
    gensymed_symbol_1 = CDR(temp);
    gensymed_symbol_2 = remote_query_index;
    gensymed_symbol_3 = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(gensymed_symbol_1))
	goto end_loop;
    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol_1,(SI_Long)0L));
    if (gensymed_symbol < gensymed_symbol_3)
	gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
    else if (gensymed_symbol > gensymed_symbol_3)
	gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
    else {
	gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)3L);
	gensymed_symbol_4 = Nil;
      next_loop_1:
	if ( !TRUEP(gensymed_symbol_1))
	    goto end_loop_1;
	gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol_1));
	if (EQL(gensymed_symbol_2,gensymed_symbol_4)) {
	    sysproc_continuation_qm = M_CDR(M_CAR(gensymed_symbol_1));
	    goto end_1;
	}
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:
	sysproc_continuation_qm = Qnil;
      end_1:;
	goto end_2;
    }
    goto next_loop;
  end_loop:
    sysproc_continuation_qm = Qnil;
  end_2:;
    if (sysproc_continuation_qm) {
	set_code_body_invocation_local_name_value(sysproc_continuation_qm,
		Qquery_status,process_status);
	wake_up_code_body_invocation(sysproc_continuation_qm);
    }
    return VALUES_1(Nil);
}

/* KILL-PROCESS-LISP-SIDE */
Object kill_process_lisp_side(g2_process_id)
    Object g2_process_id;
{
    Object first_known_process_id_qm, sysproc_pop_store, cons_1, next_cons;
    Object temp, svref_arg_2, process_id_cons, known_process_id, ab_loop_list_;
    SI_Long return_status;
    double process_id, arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(164,120);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	process_id = DFLOAT_ISAREF_1(g2_process_id,(SI_Long)0L);
	reclaim_managed_simple_float_array_of_length_1(g2_process_id);
	arg = process_id;
	arg_1 = 0.0;
	if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1))
	    result = VALUES_1(Evaluation_false_value);
	else {
	    return_status = g2ext_kill_spawned_command_line(process_id);
	    first_known_process_id_qm = FIRST(Known_process_ids_qm);
	    if (first_known_process_id_qm) {
		arg = DFLOAT_ISAREF_1(first_known_process_id_qm,(SI_Long)0L);
		arg_1 = process_id;
		if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
			!inline_nanp_for_comparison(arg_1)) {
		    reclaim_managed_simple_float_array_of_length_1(first_known_process_id_qm);
		    sysproc_pop_store = Nil;
		    cons_1 = Known_process_ids_qm;
		    if (cons_1) {
			sysproc_pop_store = M_CAR(cons_1);
			next_cons = M_CDR(cons_1);
			inline_note_reclaim_cons(cons_1,Qsysproc);
			if (ISVREF(Available_sysproc_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp = 
				    ISVREF(Available_sysproc_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp) = cons_1;
			    temp = Available_sysproc_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp,svref_arg_2) = cons_1;
			}
			else {
			    temp = Available_sysproc_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp,svref_arg_2) = cons_1;
			    temp = Available_sysproc_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp,svref_arg_2) = cons_1;
			}
			M_CDR(cons_1) = Nil;
		    }
		    else
			next_cons = Nil;
		    Known_process_ids_qm = next_cons;
		}
		else {
		    process_id_cons = Known_process_ids_qm;
		    known_process_id = Nil;
		    ab_loop_list_ = REST(Known_process_ids_qm);
		  next_loop:
		    if ( !TRUEP(process_id_cons))
			goto end_loop;
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop;
		    known_process_id = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    arg = DFLOAT_ISAREF_1(known_process_id,(SI_Long)0L);
		    arg_1 = process_id;
		    if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) 
			    &&  !inline_nanp_for_comparison(arg_1)) {
			reclaim_managed_simple_float_array_of_length_1(known_process_id);
			temp = CDDR(process_id_cons);
			M_CDR(process_id_cons) = temp;
			goto end_loop;
		    }
		    process_id_cons = M_CDR(process_id_cons);
		    goto next_loop;
		  end_loop:;
		}
	    }
	    if (return_status == (SI_Long)0L)
		result = VALUES_1(Evaluation_true_value);
	    else
		result = VALUES_1(Evaluation_false_value);
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

static Object Qremote_kill_initiated;  /* remote-kill-initiated */

/* KILL-REMOTE-PROCESS-LISP-SIDE */
Object kill_remote_process_lisp_side(g2_process_id,g2_window)
    Object g2_process_id, g2_window;
{
    Object x2, gensymed_symbol, sub_class_bit_vector, problem_symbol_qm;
    Object code_body_invocation_to_receive_kill_status, icp_socket_of_window;
    Object remote_kill_index, temp_1, current_icp_port, current_icp_socket;
    Object disable_resumability, number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object aref_arg_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp_2;
    char temp;
    double gensymed_symbol_4, gensymed_symbol_5, gensymed_symbol_6;
    double gensymed_symbol_7, gensymed_symbol_8, aref_new_value;
    Declare_special(12);

    x_note_fn_call(164,121);
    if (SIMPLE_VECTOR_P(g2_window) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(g2_window)) > (SI_Long)2L &&  
	    !EQ(ISVREF(g2_window,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(g2_window,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(G2_window_class_description,(SI_Long)18L));
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
    problem_symbol_qm =  !temp ? 
	    Qremote_process_procedure_requires_g2_window : Nil;
    if (problem_symbol_qm);
    else
	problem_symbol_qm = 
		get_remote_process_problem_symbol_if_any(g2_window,Nil);
    if (problem_symbol_qm) {
	reclaim_managed_simple_float_array_of_length_1(g2_process_id);
	return VALUES_1(problem_symbol_qm);
    }
    else {
	code_body_invocation_to_receive_kill_status = 
		Current_computation_instance;
	icp_socket_of_window = get_icp_socket_for_g2_window(g2_window);
	remote_kill_index = get_new_remote_spawn_index();
	gensymed_symbol_1 = IFIX(sxhashw(remote_kill_index));
	temp_1 = Sysproc_continuation_table;
	temp_2 = gensymed_symbol_1 % (SI_Long)131L;
	set_balanced_binary_tree_entry(SVREF(temp_1,FIX(temp_2)),Qeql,Nil,
		T,remote_kill_index,FIX(gensymed_symbol_1),
		code_body_invocation_to_receive_kill_status);
	install_code_body_invocation_completion_form(code_body_invocation_to_receive_kill_status,
		sysproc_list_2(Qclean_up_sysproc_continuation,
		remote_kill_index));
	current_icp_port = ISVREF(icp_socket_of_window,(SI_Long)4L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		11);
	  current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
		  10);
	    temp_1 = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) 
		    : Nil;
	    if (temp_1);
	    else
		temp_1 = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
			Qtelewindows) ? T : Nil;
	    disable_resumability = temp_1;
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
		      number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
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
				gensymed_symbol_4 = 0.0;
				gensymed_symbol_5 = 0.0;
				if (Profiling_enabled_qm) {
				    gensymed_symbol = T;
				    gensymed_symbol_4 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_5 = 
					    g2ext_unix_time_as_float();
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    gensymed_symbol_5);
				}
				if (icp_connection_open_p(Current_icp_socket) 
					&&  
					!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					    {
				    send_icp_kill_remote_process(remote_kill_index,
					    g2_process_id);
				    end_icp_message_group();
				}
				if (Profiling_enabled_qm) {
				    gensymed_symbol_6 = 
					    g2ext_unix_time_as_float();
				    gensymed_symbol_7 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_8 = gensymed_symbol_6 
					    - gensymed_symbol_7;
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L);
				    aref_new_value = gensymed_symbol_8 + 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L),(SI_Long)0L);
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    aref_new_value);
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    aref_new_value = gensymed_symbol ? 
					    gensymed_symbol_4 + 
					    gensymed_symbol_8 + 
					    (gensymed_symbol_7 - 
					    gensymed_symbol_5) : 
					    gensymed_symbol_6;
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
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
	reclaim_managed_simple_float_array_of_length_1(g2_process_id);
	return VALUES_1(Qremote_kill_initiated);
    }
}

static Object Qkill_status;        /* kill-status */

/* G2-HANDLE-KILL-REMOTE-PROCESS-REPLY */
Object g2_handle_kill_remote_process_reply(remote_kill_index,process_status)
    Object remote_kill_index, process_status;
{
    Object temp, gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_4;
    Object sysproc_continuation_qm;
    SI_Long gensymed_symbol, temp_1, gensymed_symbol_3;

    x_note_fn_call(164,122);
    gensymed_symbol = IFIX(sxhashw(remote_kill_index));
    temp = Sysproc_continuation_table;
    temp_1 = gensymed_symbol % (SI_Long)131L;
    temp = SVREF(temp,FIX(temp_1));
    gensymed_symbol_1 = CDR(temp);
    gensymed_symbol_2 = remote_kill_index;
    gensymed_symbol_3 = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(gensymed_symbol_1))
	goto end_loop;
    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol_1,(SI_Long)0L));
    if (gensymed_symbol < gensymed_symbol_3)
	gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
    else if (gensymed_symbol > gensymed_symbol_3)
	gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
    else {
	gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)3L);
	gensymed_symbol_4 = Nil;
      next_loop_1:
	if ( !TRUEP(gensymed_symbol_1))
	    goto end_loop_1;
	gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol_1));
	if (EQL(gensymed_symbol_2,gensymed_symbol_4)) {
	    sysproc_continuation_qm = M_CDR(M_CAR(gensymed_symbol_1));
	    goto end_1;
	}
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:
	sysproc_continuation_qm = Qnil;
      end_1:;
	goto end_2;
    }
    goto next_loop;
  end_loop:
    sysproc_continuation_qm = Qnil;
  end_2:;
    if (sysproc_continuation_qm) {
	set_code_body_invocation_local_name_value(sysproc_continuation_qm,
		Qkill_status,process_status);
	wake_up_code_body_invocation(sysproc_continuation_qm);
    }
    return VALUES_1(Nil);
}

static Object Quser_command_line_argument;  /* user-command-line-argument */

/* GET-COMMAND-LINE-ARGUMENT-FROM-LAUNCH-LISP-SIDE */
Object get_command_line_argument_from_launch_lisp_side(g2_argument_index)
    Object g2_argument_index;
{
    Object argument_index, command_line_argument_qm;
    Object filtered_command_line_argument, result_1, temp;

    x_note_fn_call(164,123);
    argument_index = g2_argument_index;
    command_line_argument_qm = IFIX(argument_index) >= (SI_Long)0L ? 
	    get_gensym_command_line_argument(argument_index) : Qnil;
    if (command_line_argument_qm) {
	filtered_command_line_argument = import_text_string(2,
		command_line_argument_qm,Quser_command_line_argument);
	result_1 = copy_as_wide_string(filtered_command_line_argument);
	reclaim_text_string(filtered_command_line_argument);
	temp = copy_as_wide_string(result_1);
	reclaim_text_string(result_1);
	return VALUES_1(temp);
    }
    else
	return copy_as_wide_string(string_constant_6);
}

/* GET-HOST-NAME-LISP-SIDE */
Object get_host_name_lisp_side()
{
    Object host_name_qm;

    x_note_fn_call(164,124);
    host_name_qm = get_local_host_name();
    if (host_name_qm)
	return copy_as_wide_string(host_name_qm);
    else
	return copy_as_wide_string(string_constant_6);
}

/* GET-PORT-NUMBER-OR-NAME-LISP-SIDE */
Object get_port_number_or_name_lisp_side()
{
    x_note_fn_call(164,125);
    return get_port_number_or_name_given_index_lisp_side(FIX((SI_Long)1L));
}

/* GET-PORT-NUMBER-OR-NAME-GIVEN-INDEX-LISP-SIDE */
Object get_port_number_or_name_given_index_lisp_side(index_1)
    Object index_1;
{
    Object index_value;
    volatile Object network_addresses_qm;
    Object network_address_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(164,126);
    SAVE_STACK();
    if (Generic_listener_initialized_qm) {
	index_value = Qunbound_in_protected_let;
	network_addresses_qm = Qunbound_in_protected_let;
	network_address_qm = Qunbound_in_protected_let;
	if (PUSH_UNWIND_PROTECT(0)) {
	    index_value = FIXNUM_SUB1(index_1);
	    network_addresses_qm = get_local_host_addresses();
	    network_address_qm = IFIX(index_value) >= (SI_Long)0L ? 
		    nth(index_value,network_addresses_qm) : Qnil;
	    if (network_address_qm)
		SAVE_VALUES(copy_as_wide_string(SECOND(network_address_qm)));
	    else
		SAVE_VALUES(copy_as_wide_string(string_constant_6));
	}
	POP_UNWIND_PROTECT(0);
	if (network_addresses_qm) {
	    if ( !EQ(network_addresses_qm,Qunbound_in_protected_let))
		reclaim_network_addresses(network_addresses_qm);
	}
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
    else {
	result = copy_as_wide_string(string_constant_6);
	RESTORE_STACK();
	return result;
    }
}

/* GET-NETWORK-ADDRESSES-LISP-SIDE */
Object get_network_addresses_lisp_side()
{
    Object buffer, len, address, addresses, ab_loopvar_, ab_loopvar__1;
    Object address_list;
    SI_Long buffer_size, i;

    x_note_fn_call(164,127);
    buffer_size = (SI_Long)300L;
    buffer = obtain_simple_gensym_string(FIX(buffer_size));
    i = (SI_Long)0L;
    len = Nil;
    address = Nil;
    addresses = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    len = get_nth_network_address(FIX(i),buffer,FIX(buffer_size));
    if ( !(IFIX(len) >= (SI_Long)0L))
	goto end_loop;
    address = copy_partial_text_string(buffer,len);
    ab_loopvar__1 = eval_cons_1(address,Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	addresses = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    address_list = allocate_evaluation_sequence(addresses);
    goto end_1;
    address_list = Qnil;
  end_1:;
    reclaim_gensym_string(buffer);
    return VALUES_1(address_list);
}

/* GET-NETWORK-TYPE-LISP-SIDE */
Object get_network_type_lisp_side()
{
    x_note_fn_call(164,128);
    return get_network_type_given_index_lisp_side(FIX((SI_Long)1L));
}

/* GET-NETWORK-TYPE-GIVEN-INDEX-LISP-SIDE */
Object get_network_type_given_index_lisp_side(index_1)
    Object index_1;
{
    Object index_value;
    volatile Object network_addresses_qm;
    Object network_address_qm, string_or_symbol, local_string;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object c, simple_or_wide_character, thing, temp, schar_arg_2;
    Object schar_new_value;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, i;
    SI_Long ab_loop_bind_;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(5);
    Object result;

    x_note_fn_call(164,129);
    SAVE_STACK();
    if (Generic_listener_initialized_qm) {
	index_value = Qunbound_in_protected_let;
	network_addresses_qm = Qunbound_in_protected_let;
	network_address_qm = Qunbound_in_protected_let;
	if (PUSH_UNWIND_PROTECT(0)) {
	    index_value = FIXNUM_SUB1(index_1);
	    network_addresses_qm = get_local_host_addresses();
	    network_address_qm = nth(index_value,network_addresses_qm);
	    if (network_address_qm) {
		string_or_symbol = FIRST(network_address_qm);
		local_string = SYMBOLP(string_or_symbol) ? 
			symbol_name_text_string(string_or_symbol) : 
			string_or_symbol;
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
			  ab_loop_bind_ = IFIX(lengthw(local_string));
			  c = Nil;
			next_loop:
			  if (i >= ab_loop_bind_)
			      goto end_loop;
			  c = FIX(UBYTE_16_ISAREF_1(local_string,i));
			  simple_or_wide_character = (SI_Long)95L == 
				  IFIX(c) ? FIX((SI_Long)45L) : c;
			  if (EQ(Current_twriting_output_type,Qwide_string)) {
			      thing = simple_or_wide_character;
			      twrite_wide_character(CHARACTERP(thing) ? 
				      CHAR_CODE(thing) : thing);
			  }
			  else {
			      if ( 
				      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				      Total_length_of_current_gensym_string))
				  extend_current_gensym_string(0);
			      temp = Current_gensym_string;
			      schar_arg_2 = 
				      Fill_pointer_for_current_gensym_string;
			      thing = simple_or_wide_character;
			      schar_new_value = 
				      CODE_CHAR(CHARACTERP(thing) ? 
				      CHAR_CODE(thing) : thing);
			      SET_SCHAR(temp,schar_arg_2,schar_new_value);
			      temp = 
				      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			      Fill_pointer_for_current_gensym_string = temp;
			  }
			  i = i + (SI_Long)1L;
			  goto next_loop;
			end_loop:;
			  SAVE_VALUES(copy_out_current_wide_string());
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	    }
	    else
		SAVE_VALUES(copy_as_wide_string(string_constant_6));
	}
	POP_UNWIND_PROTECT(0);
	if (network_addresses_qm) {
	    if ( !EQ(network_addresses_qm,Qunbound_in_protected_let))
		reclaim_network_addresses(network_addresses_qm);
	}
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
    else {
	result = copy_as_wide_string(string_constant_6);
	RESTORE_STACK();
	return result;
    }
}

/* GET-SOFTWARE-VERSION-LISP-SIDE */
Object get_software_version_lisp_side()
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(164,130);
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
	      twrite_system_version(1,get(Current_system_name,
		      Qsystem_version,_));
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qab;                 /* ab */

static Object string_constant_18;  /* " ~a" */

/* G2-GET-BUILD-VERSION */
Object g2_get_build_version()
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(164,131);
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
	      twrite_system_version(1,get(Qab,Qsystem_version,_));
	      tformat(2,string_constant_18,Build_identification_string);
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qpatch;              /* patch */

static Object Qunknown_release_level;  /* unknown-release-level */

static Object Qprototype;          /* prototype */

static Object Qalpha;              /* alpha */

static Object Qbeta;               /* beta */

static Object Qreleased;           /* released */

static Object Qrevision;           /* revision */

static Object Qrelease_level;      /* release-level */

static Object Qpatch_number;       /* patch-number */

static Object Qbuild_identification;  /* build-identification */

static Object Qbuild_comment;      /* build-comment */

static Object Qenterprise;         /* enterprise */

/* SYSTEM-VERSION-INFORMATION-AS-STRUCTURE */
Object system_version_information_as_structure()
{
    Object level, gensymed_symbol, gensymed_symbol_1, minor_version, floor_1;
    Object rem_1, car_new_value;
    Object result;

    x_note_fn_call(164,132);
    if (Patch_number_of_current_gensym_product_line_qm)
	level = Qpatch;
    else if ( !TRUEP(T))
	level = Qunknown_release_level;
    else
	switch (INTEGER_TO_CHAR(Release_quality_of_current_gensym_product_line)) 
		    {
	  case 0:
	    level = Qprototype;
	    break;
	  case 1:
	    level = Qalpha;
	    break;
	  case 2:
	    level = Qbeta;
	    break;
	  case 3:
	    level = Qreleased;
	    break;
	  default:
	    level = Qunknown_release_level;
	    break;
	}
    gensymed_symbol = make_eval_list_1(FIX((SI_Long)16L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = Qmajor_version_number;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = 
	    Major_version_number_of_current_gensym_product_line;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qminor_version_number;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    minor_version = Minor_version_number_of_current_gensym_product_line;
    result = chestnut_floorf_function(minor_version,FIX((SI_Long)10L));
    MVS_2(result,floor_1,rem_1);
    car_new_value = IFIX(rem_1) == (SI_Long)0L ? floor_1 : minor_version;
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qrevision;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Revision_number_of_current_gensym_product_line;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qrelease_level;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = level;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qpatch_number;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = Patch_number_of_current_gensym_product_line_qm;
    if (car_new_value);
    else
	car_new_value = Nil ? Evaluation_true_value : Evaluation_false_value;
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qbuild_identification;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = copy_as_wide_string(Build_identification_string);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qbuild_comment;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value =  !TRUEP(Build_comment_string) ? (Nil ? 
	    Evaluation_true_value : Evaluation_false_value) : 
	    copy_as_wide_string(Build_comment_string);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qenterprise;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = Is_g2_enterprise_qm ? Evaluation_true_value : 
	    Evaluation_false_value;
    M_CAR(gensymed_symbol_1) = car_new_value;
    return allocate_evaluation_structure(gensymed_symbol);
}

/* G2-GET-VERSION */
Object g2_get_version()
{
    Object value_1, temp;

    x_note_fn_call(164,133);
    value_1 = Nil;
    value_1 = system_version_information_as_structure();
    temp = IDENTITY(value_1);
    return VALUES_1(temp);
}

/* UNIX-TIME-LISP-SIDE */
Object unix_time_lisp_side()
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(164,134);
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
	aref_new_value = g2ext_unix_time_as_float();
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	result = VALUES_1(new_float);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* UNIX-TIME-AT-START-LISP-SIDE */
Object unix_time_at_start_lisp_side()
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(164,135);
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
	aref_new_value = (double)IFIX(FIXNUM_MINUS(Gensym_time_at_start,
		Gensym_time_at_start)) + DFLOAT_ISAREF_1(G2_time_at_start,
		(SI_Long)0L);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	result = VALUES_1(new_float);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* LOCAL-TIME-LISP-SIDE */
Object local_time_lisp_side()
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(164,136);
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
	aref_new_value = 0.0;
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	result = VALUES_1(new_float);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* IS-DST-USED-LISP-SIDE */
Object is_dst_used_lisp_side()
{
    x_note_fn_call(164,137);
    if (g2ext_is_dst_used() != (SI_Long)0L)
	return VALUES_1(Evaluation_true_value);
    else
	return VALUES_1(Evaluation_false_value);
}

/* UNIX-TIME-TO-TEXT-LISP-SIDE */
Object unix_time_to_text_lisp_side(unix_time,use_seconds)
    Object unix_time, use_seconds;
{
    x_note_fn_call(164,138);
    return unix_time_to_text_internal(unix_time,use_seconds,Nil);
}

/* UNIX-TIME-TO-TEXT-Y2K-LISP-SIDE */
Object unix_time_to_text_y2k_lisp_side(unix_time,use_seconds)
    Object unix_time, use_seconds;
{
    x_note_fn_call(164,139);
    return unix_time_to_text_internal(unix_time,use_seconds,T);
}

static Object string_constant_19;  /* "Currently Windows NT platforms cannot display time values before January 1, 1970 in text form. Unix-time should be no less than 0.0. " */

static Object string_constant_20;  /* "~d/~d/~d" */

static Object string_constant_21;  /* "~d/~d/0~d" */

static Object string_constant_22;  /* " " */

static Object string_constant_23;  /* "~d:" */

static Object string_constant_24;  /* "0" */

static Object string_constant_25;  /* "~d" */

static Object string_constant_26;  /* ":" */

static Object string_constant_27;  /* "p.m." */

static Object string_constant_28;  /* "a.m." */

/* UNIX-TIME-TO-TEXT-INTERNAL */
Object unix_time_to_text_internal(unix_time,use_seconds,use_4_digit_year)
    Object unix_time, use_seconds, use_4_digit_year;
{
    Object use_seconds_p, top_of_stack, message_1, seconds, minute, hour, date;
    Object month, year, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_2;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, temp_1;
    SI_Long simple_year;
    char temp;
    double unix_time_float, arg, arg_1;
    Declare_special(5);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(164,140);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	use_seconds_p = evaluation_truth_value_is_true_p(use_seconds);
	unix_time_float = DFLOAT_ISAREF_1(unix_time,(SI_Long)0L);
	if (windows_platform_p()) {
	    arg = unix_time_float;
	    arg_1 = 0.0;
	    temp = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(1,string_constant_19);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	result = gensym_decode_unix_time(DOUBLE_TO_DOUBLE_FLOAT(unix_time_float));
	MVS_6(result,seconds,minute,hour,date,month,year);
	reclaim_managed_simple_float_array_of_length_1(unix_time);
	if ( !(EQ(use_seconds,Evaluation_true_value) || EQ(use_seconds,
		Evaluation_false_value)))
	    reclaim_eval_cons_1(use_seconds);
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
		  if (use_4_digit_year)
		      tformat(4,string_constant_20,month,date,year);
		  else {
		      temp_1 = IFIX(year) % (SI_Long)100L;
		      simple_year = temp_1;
		      tformat(4,simple_year > (SI_Long)9L ? 
			      string_constant_20 : string_constant_21,
			      month,date,FIX(simple_year));
		  }
		  tformat(1,string_constant_22);
		  if ( !(FIXNUMP(hour) && FIXNUM_LE(FIX((SI_Long)-128L),
			  hour) && FIXNUM_LE(hour,FIX((SI_Long)127L)))) {
		      temp_1 = IFIX(hour) % (SI_Long)12L;
		      temp_2 = FIX(temp_1);
		  }
		  else
		      switch (INTEGER_TO_CHAR(hour)) {
			case 0:
			case 12:
			  temp_2 = FIX((SI_Long)12L);
			  break;
			default:
			  temp_1 = IFIX(hour) % (SI_Long)12L;
			  temp_2 = FIX(temp_1);
			  break;
		      }
		  tformat(2,string_constant_23,temp_2);
		  if (IFIX(minute) < (SI_Long)10L)
		      tformat(1,string_constant_24);
		  tformat(2,string_constant_25,minute);
		  if (use_seconds_p) {
		      tformat(1,string_constant_26);
		      if (IFIX(seconds) < (SI_Long)10L)
			  tformat(1,string_constant_24);
		      tformat(2,string_constant_25,seconds);
		  }
		  tformat(1,string_constant_22);
		  if (IFIX(hour) >= (SI_Long)12L)
		      tformat(1,string_constant_27);
		  else
		      tformat(1,string_constant_28);
		  result = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

static Object array_constant_1;    /* # */

/* G2-GET-ENVIRONMENT-VARIABLE */
Object g2_get_environment_variable(variable_name_string)
    Object variable_name_string;
{
    Object value, temp;

    x_note_fn_call(164,141);
    value = get_gensym_environment_variable(variable_name_string);
    if (value) {
	temp = copy_as_wide_string(value);
	return VALUES_2(temp,T ? Evaluation_true_value : 
		Evaluation_false_value);
    }
    else {
	temp = copy_as_wide_string(array_constant_1);
	return VALUES_2(temp,Nil ? Evaluation_true_value : 
		Evaluation_false_value);
    }
}

/* GET-PROCESS-IDENTIFIER */
Object get_process_identifier()
{
    Object value_1, amf_available_array_cons_qm, amf_array, temp, temp_1;
    Object amf_result, new_float;
    double aref_new_value;

    x_note_fn_call(164,142);
    value_1 = Nil;
    value_1 = DOUBLE_TO_DOUBLE_FLOAT(g2ext_get_process_identifier());
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
    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value_1);
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
    return VALUES_1(new_float);
}

void file_sysproc_INIT()
{
    Object temp, temp_1, temp_2;
    Object text_conversion_style_name_qm_evaluation_setter_1;
    Object text_conversion_style_name_qm_evaluation_getter_1, gensymed_symbol;
    Object Qget_process_identifier;
    Object Qfunction_keeps_procedure_environment_valid_qm, AB_package;
    Object Qg2_get_environment_variable, list_constant_11;
    Object Qunix_time_to_text_y2k_lisp_side, Qunix_time_to_text_lisp_side;
    Object Qis_dst_used_lisp_side, Qlocal_time_lisp_side;
    Object Qunix_time_at_start_lisp_side, Qunix_time_lisp_side;
    Object Qg2_get_version, Qg2_get_build_version;
    Object Qget_software_version_lisp_side;
    Object Qget_network_type_given_index_lisp_side;
    Object Qget_network_type_lisp_side, Qget_network_addresses_lisp_side;
    Object Qget_port_number_or_name_given_index_lisp_side;
    Object Qget_port_number_or_name_lisp_side, Qget_host_name_lisp_side;
    Object Qget_command_line_argument_from_launch_lisp_side;
    Object Qkill_remote_process_lisp_side, Qkill_process_lisp_side;
    Object Qremote_process_exists_lisp_side, Qprocess_exists_lisp_side;
    Object Qspawn_remote_process_with_arguments_lisp_side;
    Object Qg2_spawn_remote_process_to_run_command_line_lisp_side;
    Object Qspawn_remote_process_lisp_side;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qout_sysproc_continuation_hashtable_hash_vector_131_vectors;
    Object Qsysproc_continuation_hashtable_hash_vector_131_vector_memory_usage;
    Object string_constant_69, Qutilities2;
    Object Qspawn_process_with_arguments_lisp_side;
    Object Qspawn_process_to_run_command_line_lisp_side;
    Object Qg2_version_of_kb_file, Qcreate_directory_lisp_side;
    Object Qdevices_on_machine_lisp_side;
    Object Qdisk_space_available_in_directory_lisp_side;
    Object Qget_temporary_filename_lisp_side;
    Object Qchange_default_directory_lisp_side, Qdefault_directory_lisp_side;
    Object Qsubdirectories_in_directory_lisp_side;
    Object Qfiles_in_directory_lisp_side, Qdirectory_exists_lisp_side;
    Object Qlatest_date_file_attributes_were_changed_lisp_side;
    Object Qlatest_date_file_was_accessed_lisp_side;
    Object Qlatest_date_file_was_modified_lisp_side, Qlength_of_file_lisp_side;
    Object Qfile_names_are_identical_lisp_side, Qfile_exists_lisp_side;
    Object Qtype_of_file_system_lisp_side, Qpartition_filestring_lisp_side;
    Object Qcollect_into_filestring_lisp_side, Qfile_version_string_lisp_side;
    Object Qfile_extension_string_lisp_side, Qfile_base_name_string_lisp_side;
    Object Qfile_directory_list_to_string_lisp_side;
    Object Qfile_directory_string_to_list_lisp_side;
    Object Qfile_directory_string_lisp_side, Qfile_device_string_lisp_side;
    Object Qfile_host_string_lisp_side, Qbytes_to_float_lisp_side;
    Object Qfloat_to_bytes_lisp_side, Qwrite_bytes_lisp_side;
    Object Qwrite_byte_lisp_side, Qwrite_string_or_line_lisp_side_internal;
    Object Qwrite_string_in_gensym_charset_lisp_side;
    Object Qwrite_line_in_gensym_charset_lisp_side, Qwrite_string_lisp_side;
    Object Qwrite_line_lisp_side, Qread_bytes_as_text_lisp_side;
    Object Qread_byte_lisp_side, Qbyte_range_0_255_mask, Qread_line_lisp_side;
    Object Qdelete_file_lisp_side, Qcopy_file_lisp_side;
    Object Qrename_file_lisp_side, Qset_file_position_lisp_side;
    Object Qclose_all_open_g2_streams_lisp_side;
    Object Qclose_file_leaving_stream_lisp_side, Qclose_file_lisp_side;
    Object Qopen_file_for_read_and_write_lisp_side;
    Object Qopen_file_for_append_lisp_side, Qopen_file_for_write_lisp_side;
    Object Qopen_file_for_read_lisp_side, Qslot_value_writer;
    Object Qwrite_han_unification_mode_from_slot;
    Object Qwrite_character_set_from_slot, Qcharacter_set, array_constant_15;
    Object Qlatin_6, array_constant_14, Qlatin_5, array_constant_13;
    Object Qlatin_hebrew, array_constant_11, Qlatin_greek, array_constant_12;
    Object Qlatin_arabic, array_constant_10, Qlatin_4, array_constant_9;
    Object Qlatin_3, array_constant_8, Qlatin_2, array_constant_7;
    Object array_constant_6, Qx_compound_text, array_constant_5;
    Object Qunicode_utf_8, array_constant_4, Qunicode_utf_7, array_constant_3;
    Object array_constant_2, string_constant_68, string_constant_67;
    Object string_constant_66, string_constant_65, string_constant_64;
    Object Qwrite_line_separator_from_slot, Qline_separator;
    Object string_constant_63, Qwrite_unconvertible_character_spec_from_slot;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler;
    Object Qcompile_unconvertible_character_spec_for_slot, string_constant_62;
    Object Qslot_putter, Qput_han_unification_mode;
    Object Qput_external_line_separator, Qput_unconvertible_character_spec;
    Object Qput_external_character_set;
    Object Qwrite_text_conversion_style_name_qm_from_slot;
    Object Qtext_conversion_style_name_qm;
    Object Qcompile_text_conversion_style_name_qm_for_slot;
    Object Qput_text_conversion_style, Qregistered_directory_of_names_p;
    Object Qtext_conversion_style_name, string_constant_61, string_constant_60;
    Object Qnamed, Qtype_specification_simple_expansion, list_constant_10;
    Object Qab_or, Qno_item, Qclasses_which_define, Qinitialize;
    Object Qinitialize_for_text_conversion_style, Qinitialize_after_reading;
    Object Qinitialize_after_reading_for_text_conversion_style;
    Object Qreplacement_character, Qslot_value_reclaimer;
    Object Qreclaim_internal_structure_for_text_conversion_style_value;
    Object string_constant_59, string_constant_58, list_constant_4;
    Object string_constant_57, string_constant_56, string_constant_55;
    Object string_constant_54, string_constant_53, string_constant_52;
    Object list_constant_9, Qfile_sysproc, Qfile_system;
    Object Qget_slot_description_from_class, Kfuncall, list_constant_8;
    Object Qposition_in_file, list_constant_7, Qaccess_direction;
    Object list_constant_6, Qname_of_file, list_constant_5, Qg2_stream_status;
    Object Qcleanup, Qcleanup_for_g2_stream;
    Object Qsize_of_g2_stream_frame_input_buffer;
    Object Qwrite_name_of_file_from_slot, string_constant_51;
    Object string_constant_50, string_constant_49, string_constant_48;
    Object string_constant_47, string_constant_46, string_constant_45;
    Object string_constant_44, Qcreate_icon_description, string_constant_43;
    Object string_constant_42, string_constant_41, string_constant_40;
    Object string_constant_39, string_constant_38, string_constant_37;
    Object string_constant_36, string_constant_35, string_constant_34;
    Object string_constant_33, string_constant_32, string_constant_31;
    Object string_constant_30, Qentity, Qitem, string_constant_29;
    Object Qsysproc_cons_memory_usage, Qoutstanding_sysproc_conses;
    Object list_constant_3, Qsysproc_cons_counter_vector, Qmake_thread_array;
    Object list_constant_2, Qavailable_sysproc_conses_tail_vector;
    Object Qavailable_sysproc_conses_vector;

    x_note_fn_call(164,143);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qavailable_sysproc_conses = STATIC_SYMBOL("AVAILABLE-SYSPROC-CONSES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_sysproc_conses,
	    Available_sysproc_conses);
    Qfile_sysproc = STATIC_SYMBOL("FILE-SYSPROC",AB_package);
    record_system_variable(Qavailable_sysproc_conses,Qfile_sysproc,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_sysproc_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-SYSPROC-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_sysproc_conses_tail,
	    Available_sysproc_conses_tail);
    record_system_variable(Qavailable_sysproc_conses_tail,Qfile_sysproc,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qavailable_sysproc_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-SYSPROC-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_sysproc_conses_vector,
	    Available_sysproc_conses_vector);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_thread_array = STATIC_SYMBOL("MAKE-THREAD-ARRAY",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    Qnil);
    record_system_variable(Qavailable_sysproc_conses_vector,Qfile_sysproc,
	    list_constant_2,Qnil,Qt,Qnil,Qnil);
    Qavailable_sysproc_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-SYSPROC-CONSES-TAIL-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_sysproc_conses_tail_vector,
	    Available_sysproc_conses_tail_vector);
    record_system_variable(Qavailable_sysproc_conses_tail_vector,
	    Qfile_sysproc,list_constant_2,Qnil,Qt,Qnil,Qnil);
    Qsysproc_cons_counter_vector = 
	    STATIC_SYMBOL("SYSPROC-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsysproc_cons_counter_vector,
	    Sysproc_cons_counter_vector);
    list_constant_3 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    FIX((SI_Long)0L));
    record_system_variable(Qsysproc_cons_counter_vector,Qfile_sysproc,
	    list_constant_3,Qnil,Qt,Qnil,Qnil);
    Qsysproc_cons_counter = STATIC_SYMBOL("SYSPROC-CONS-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsysproc_cons_counter,Sysproc_cons_counter);
    record_system_variable(Qsysproc_cons_counter,Qfile_sysproc,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_sysproc_conses = 
	    STATIC_SYMBOL("OUTSTANDING-SYSPROC-CONSES",AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_sysproc_conses,
	    STATIC_FUNCTION(outstanding_sysproc_conses,NIL,FALSE,0,0));
    Qsysproc_cons_memory_usage = STATIC_SYMBOL("SYSPROC-CONS-MEMORY-USAGE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qsysproc_cons_memory_usage,
	    STATIC_FUNCTION(sysproc_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_29 = STATIC_STRING("1q83-rky9k83-rjy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_sysproc_conses);
    push_optimized_constant(Qsysproc_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_29));
    Qsysproc = STATIC_SYMBOL("SYSPROC",AB_package);
    Qg2_stream = STATIC_SYMBOL("G2-STREAM",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qitem,Qentity);
    check_if_superior_classes_are_defined(Qg2_stream,list_constant_4);
    string_constant_30 = STATIC_STRING("1m1l83Iy1l83Ly");
    Qcreate_icon_description = STATIC_SYMBOL("CREATE-ICON-DESCRIPTION",
	    AB_package);
    string_constant_31 = 
	    STATIC_STRING("13Ey4z8r8u8u83NTy83NTy01p8w9k3-Wy3ky1w1p83Jy1m3ayt1m3ay3ay1m3-=y3ay1m3-=yt1n83Oy1m3gy3Dy1m3wy3Dy1n83Oy1m3iy3Hy1m3py3Hy1n83Oy1m3h");
    string_constant_32 = 
	    STATIC_STRING("y3Ly1m3xy3Ly1n83Oy1m3hy3Ry1m3vy3Ry1n83Oy1m3jy3Vy1m3wy3Vy1o83qy1o1m3Gy3Py1m3Gy3Ty1mw3Ty1mw3Py1n1m3Gy3Py1m3Gy3Ty1mw3Ty1n1mw3Ty1mw3");
    string_constant_33 = 
	    STATIC_STRING("Py1m3Gy3Py1o83qy1o1m3Sy3Py1m3Sy3Ty1m3Ky3Ty1m3Ky3Py1n1m3Sy3Py1m3Sy3Ty1m3Ky3Ty1n1m3Ky3Ty1m3Ky3Py1m3Sy3Py1n83qy1n1m3fy3Ry1m3Wy3Xy1m");
    string_constant_34 = 
	    STATIC_STRING("3Wy3Ly1n1m3fy3Ry1m3Wy3Xy1m3Wy3Ly1o83qy1o1m3-2yz1m3-2y3Fy1m3wy3Fy1m3wyz1n1m3-2yz1m3-2y3Fy1m3wy3Fy1n1m3wy3Fy1m3wyz1m3-2yz1o83qy1o1");
    string_constant_35 = 
	    STATIC_STRING("m3-Eyz1m3-Ey3Fy1m3-6y3Fy1m3-6yz1n1m3-Eyz1m3-Ey3Fy1m3-6y3Fy1n1m3-6y3Fy1m3-6yz1m3-Eyz1n83qy1n1m3-Ry3Dy1m3-Iy3Jy1m3-Iyv1n1m3-Ry3Dy1");
    string_constant_36 = 
	    STATIC_STRING("m3-Iy3Jy1m3-Iyv001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class definition000004z8r83WCy83WCy83NTy83NTy00001p1l8l1l8o1l83Fy");
    string_constant_37 = 
	    STATIC_STRING("1m8p83-qy1l83Hy000004z8r831vy831vy83NTy83NTy00001p1l8l1l8o1l83Fy1m8p83-qy1l83Hy000004z8r83GQy83GQy83NTy83NTy083I1y001p1l8l1l8o1l");
    string_constant_38 = 
	    STATIC_STRING("83Fy1m8p83-qy1l83Hy000004z8r83Xxy83Xxy83NTy83NTy00001p1l8l1l8o1l83Fy1m8p83-qy1l83Hy000004z8r83NUy83NUy83NTy83NTy0835ry001p1l8l1l");
    string_constant_39 = 
	    STATIC_STRING("8o1l83Fy1m8p83-qy1l83Hy000004z8r83SZy83SZy83NTy83NTy00001n1l8o1l8l1l83Hy000004z8r83Sey83Sey83NTy83NTy00001n1l8o1l8l1l83Hy000004z");
    string_constant_40 = 
	    STATIC_STRING("8r83SVy83SVy83NTy83NTy00001n1l8o1l8l1l83Hy000004z8r83SUy83SUy83NTy83NTy0k001n1l8o1l8l1l83Hy000004z8r83SSy83SSy83NTy83NTy0k001n1l");
    string_constant_41 = 
	    STATIC_STRING("8o1l8l1l83Hy000004z8r83SWy83SWy83NTy83NTy0k001n1l8o1l8l1l83Hy000004z8r83=ly83=ly83NTy83NTy00001p1m8p830Uy1l83-4y1l83Ey1l8l1l83Hy");
    string_constant_42 = 
	    STATIC_STRING("000004z8r83Sfy83Sfy83NTy83NTy00001n1l8o1l8l1l83Hy000004z8r83Sby83Sby83NTy83NTy00001n1l8o1l8l1l83Hy000004z8r83Scy83Scy83NTy83NTy0");
    string_constant_43 = 
	    STATIC_STRING("0001n1l8o1l8l1l83Hy000004z8r83Say83Say83NTy83NTy00001n1l8o1l8l1l83Hy000004z8r83Sdy83Sdy83NTy83NTy00001n1l8o1l8l1l83Hy00000");
    string_constant_44 = 
	    STATIC_STRING("13Gy8q1o83NTy1m83Ry83-+y83Iy83Ly1m8u1p8w9k3-Wy3ky1w1p83Jy1m3ayt1m3ay3ay1m3-=y3ay1m3-=yt1n83Oy1m3gy3Dy1m3wy3Dy1n83Oy1m3iy3Hy1m3py");
    string_constant_45 = 
	    STATIC_STRING("3Hy1n83Oy1m3hy3Ly1m3xy3Ly1n83Oy1m3hy3Ry1m3vy3Ry1n83Oy1m3jy3Vy1m3wy3Vy1o83qy1o1m3Gy3Py1m3Gy3Ty1mw3Ty1mw3Py1n1m3Gy3Py1m3Gy3Ty1mw3T");
    string_constant_46 = 
	    STATIC_STRING("y1n1mw3Ty1mw3Py1m3Gy3Py1o83qy1o1m3Sy3Py1m3Sy3Ty1m3Ky3Ty1m3Ky3Py1n1m3Sy3Py1m3Sy3Ty1m3Ky3Ty1n1m3Ky3Ty1m3Ky3Py1m3Sy3Py1n83qy1n1m3fy");
    string_constant_47 = 
	    STATIC_STRING("3Ry1m3Wy3Xy1m3Wy3Ly1n1m3fy3Ry1m3Wy3Xy1m3Wy3Ly1o83qy1o1m3-2yz1m3-2y3Fy1m3wy3Fy1m3wyz1n1m3-2yz1m3-2y3Fy1m3wy3Fy1n1m3wy3Fy1m3wyz1m3");
    string_constant_48 = 
	    STATIC_STRING("-2yz1o83qy1o1m3-Eyz1m3-Ey3Fy1m3-6y3Fy1m3-6yz1n1m3-Eyz1m3-Ey3Fy1m3-6y3Fy1n1m3-6y3Fy1m3-6yz1m3-Eyz1n83qy1n1m3-Ry3Dy1m3-Iy3Jy1m3-Iy");
    string_constant_49 = 
	    STATIC_STRING("v1n1m3-Ry3Dy1m3-Iy3Jy1m3-Iyv1q83WCy08o83Fy1m8p83-qy83Hy1q831vy08o83Fy1m8p83-qy83Hy1q83GQy83I1y8o83Fy1m8p83-qy83Hy1q83Xxy08o83Fy1");
    string_constant_50 = 
	    STATIC_STRING("m8p83-qy83Hy1q83NUy835ry8o83Fy1m8p83-qy83Hy1p83SZy08o8l83Hy1p83Sey08o8l83Hy1p83SVy08o8l83Hy1p83SUyk8o8l83Hy1p83SSyk8o8l83Hy1p83S");
    string_constant_51 = 
	    STATIC_STRING("Wyk8o8l83Hy1r83=ly01m8p830Uy83-4y83Ey8l83Hy1p83Sfy08o8l83Hy1p83Sby08o8l83Hy1p83Scy08o8l83Hy1p83Say08o8l83Hy1p83Sdy08o8l83Hy");
    temp = regenerate_optimized_constant(string_constant_30);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(list(13,string_constant_31,
	    string_constant_32,string_constant_33,string_constant_34,
	    string_constant_35,string_constant_36,string_constant_37,
	    string_constant_38,string_constant_39,string_constant_40,
	    string_constant_41,string_constant_42,string_constant_43));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qg2_stream,list_constant_4,Nil,temp,Nil,
	    temp_1,list_constant_4,regenerate_optimized_constant(list(8,
	    string_constant_44,string_constant_45,string_constant_46,
	    string_constant_47,string_constant_48,string_constant_49,
	    string_constant_50,string_constant_51)),Nil);
    Qg2_directory_pathname = STATIC_SYMBOL("G2-DIRECTORY-PATHNAME",AB_package);
    Qname_of_file = STATIC_SYMBOL("NAME-OF-FILE",AB_package);
    Qwrite_name_of_file_from_slot = 
	    STATIC_SYMBOL("WRITE-NAME-OF-FILE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_name_of_file_from_slot,
	    STATIC_FUNCTION(write_name_of_file_from_slot,NIL,FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qname_of_file,
	    SYMBOL_FUNCTION(Qwrite_name_of_file_from_slot),Qslot_value_writer);
    Qsize_of_g2_stream_frame_input_buffer = 
	    STATIC_SYMBOL("SIZE-OF-G2-STREAM-FRAME-INPUT-BUFFER",AB_package);
    SET_SYMBOL_VALUE(Qsize_of_g2_stream_frame_input_buffer,FIX((SI_Long)512L));
    Qcleanup_for_g2_stream = STATIC_SYMBOL("CLEANUP-FOR-G2-STREAM",AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_g2_stream,
	    STATIC_FUNCTION(cleanup_for_g2_stream,NIL,FALSE,1,1));
    Qcleanup = STATIC_SYMBOL("CLEANUP",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qcleanup_for_g2_stream);
    set_get(Qg2_stream,Qcleanup,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_2 = CONS(Qg2_stream,temp);
    mutate_global_property(Qcleanup,temp_2,Qclasses_which_define);
    Qg2_stream_status_slot_description = 
	    STATIC_SYMBOL("G2-STREAM-STATUS-SLOT-DESCRIPTION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2_stream_status_slot_description,
	    G2_stream_status_slot_description);
    Qget_slot_description_from_class = 
	    STATIC_SYMBOL("GET-SLOT-DESCRIPTION-FROM-CLASS",AB_package);
    Qg2_stream_status = STATIC_SYMBOL("G2-STREAM-STATUS",AB_package);
    list_constant_5 = STATIC_LIST((SI_Long)4L,Kfuncall,
	    Qget_slot_description_from_class,Qg2_stream,Qg2_stream_status);
    record_system_variable(Qg2_stream_status_slot_description,
	    Qfile_sysproc,list_constant_5,Qnil,Qnil,Qnil,Qnil);
    Qname_of_file_slot_description = 
	    STATIC_SYMBOL("NAME-OF-FILE-SLOT-DESCRIPTION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qname_of_file_slot_description,
	    Name_of_file_slot_description);
    list_constant_6 = STATIC_LIST((SI_Long)4L,Kfuncall,
	    Qget_slot_description_from_class,Qg2_stream,Qname_of_file);
    record_system_variable(Qname_of_file_slot_description,Qfile_sysproc,
	    list_constant_6,Qnil,Qnil,Qnil,Qnil);
    Qaccess_direction_slot_description = 
	    STATIC_SYMBOL("ACCESS-DIRECTION-SLOT-DESCRIPTION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qaccess_direction_slot_description,
	    Access_direction_slot_description);
    Qaccess_direction = STATIC_SYMBOL("ACCESS-DIRECTION",AB_package);
    list_constant_7 = STATIC_LIST((SI_Long)4L,Kfuncall,
	    Qget_slot_description_from_class,Qg2_stream,Qaccess_direction);
    record_system_variable(Qaccess_direction_slot_description,
	    Qfile_sysproc,list_constant_7,Qnil,Qnil,Qnil,Qnil);
    Qposition_in_file_slot_description = 
	    STATIC_SYMBOL("POSITION-IN-FILE-SLOT-DESCRIPTION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qposition_in_file_slot_description,
	    Position_in_file_slot_description);
    Qposition_in_file = STATIC_SYMBOL("POSITION-IN-FILE",AB_package);
    list_constant_8 = STATIC_LIST((SI_Long)4L,Kfuncall,
	    Qget_slot_description_from_class,Qg2_stream,Qposition_in_file);
    record_system_variable(Qposition_in_file_slot_description,
	    Qfile_sysproc,list_constant_8,Qnil,Qnil,Qnil,Qnil);
    Qfile_system_slot_description = 
	    STATIC_SYMBOL("FILE-SYSTEM-SLOT-DESCRIPTION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qfile_system_slot_description,
	    File_system_slot_description);
    Qfile_system = STATIC_SYMBOL("FILE-SYSTEM",AB_package);
    list_constant_9 = STATIC_LIST((SI_Long)4L,Kfuncall,
	    Qget_slot_description_from_class,Qg2_stream,Qfile_system);
    record_system_variable(Qfile_system_slot_description,Qfile_sysproc,
	    list_constant_9,Qnil,Qnil,Qnil,Qnil);
    Qtext_conversion_style = STATIC_SYMBOL("TEXT-CONVERSION-STYLE",AB_package);
    check_if_superior_classes_are_defined(Qtext_conversion_style,
	    list_constant_4);
    string_constant_24 = STATIC_STRING("0");
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    string_constant_52 = 
	    STATIC_STRING("1r4z8r83--y83--y83=ly83=ly00001p1l8l1m8p83-*y1l83Ey1l83Uy1m83Dy53*syWill allow 0 or more author entries. each author entry may h");
    string_constant_53 = 
	    STATIC_STRING("ave a date. ~\nauthors: ([ name: symbol, date: gensym-time ] * ), editor-grammar: struct, defining-class: item, writable: true\n00");
    string_constant_54 = 
	    STATIC_STRING("0004z8r83-0y83-0y83=ly83=ly00001q1l8l1m8p83-0y1l83Fy1l83Ey1l83Uy1m83Dy53-Fy(to replace authors attribute; however, no documentat");
    string_constant_55 = 
	    STATIC_STRING("ion is available at this time)000004z8r83Kty83Kty83=ly83=ly09k001m1l8l1m8p83B5y000004z8r83Ffy83Ffy83=ly83=ly00001m1l8l1m8p83Ffy0");
    string_constant_56 = 
	    STATIC_STRING("00004z8r83Kvy83Kvy83=ly83=ly083EKy001m1l8l1m8p83DQy000004z8r83Cby83Cby83=ly83=ly08378y001m1l8l1m8p83Cby000004z8r83Sgy83Sgy83=ly8");
    string_constant_57 = STATIC_STRING("3=ly00001n1l8l1l83Hy1l83Fy00000");
    string_constant_58 = 
	    STATIC_STRING("1t8q1m83=ly1m83Ry83-+y1n83--y01m8p83-*y1n83-0y01m8p83-0y1n83Kty9k1m8p83B5y1n83Ffy01m8p83Ffy1n83Kvy83EKy1m8p83DQy1n83Cby8378y1m8p");
    string_constant_59 = STATIC_STRING("83Cby1o83Sgy083Hy83Fy");
    temp = regenerate_optimized_constant(string_constant_24);
    clear_optimized_constants();
    push_optimized_constant(Qab_gensym);
    temp_1 = regenerate_optimized_constant(list(6,string_constant_52,
	    string_constant_53,string_constant_54,string_constant_55,
	    string_constant_56,string_constant_57));
    clear_optimized_constants();
    push_optimized_constant(Qab_gensym);
    add_class_to_environment(9,Qtext_conversion_style,list_constant_4,Nil,
	    temp,Nil,temp_1,list_constant_4,
	    regenerate_optimized_constant(LIST_2(string_constant_58,
	    string_constant_59)),Nil);
    Qinternal_structure_for_text_conversion_style = 
	    STATIC_SYMBOL("INTERNAL-STRUCTURE-FOR-TEXT-CONVERSION-STYLE",
	    AB_package);
    Qreclaim_internal_structure_for_text_conversion_style_value = 
	    STATIC_SYMBOL("RECLAIM-INTERNAL-STRUCTURE-FOR-TEXT-CONVERSION-STYLE-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_internal_structure_for_text_conversion_style_value,
	    STATIC_FUNCTION(reclaim_internal_structure_for_text_conversion_style_value,
	    NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qinternal_structure_for_text_conversion_style,
	    SYMBOL_FUNCTION(Qreclaim_internal_structure_for_text_conversion_style_value),
	    Qslot_value_reclaimer);
    Qunconvertible_character_spec = 
	    STATIC_SYMBOL("UNCONVERTIBLE-CHARACTER-SPEC",AB_package);
    Qreplacement_character = STATIC_SYMBOL("REPLACEMENT-CHARACTER",AB_package);
    alias_slot_name(3,Qunconvertible_character_spec,Qreplacement_character,
	    Qtext_conversion_style);
    Qinitialize_after_reading_for_text_conversion_style = 
	    STATIC_SYMBOL("INITIALIZE-AFTER-READING-FOR-TEXT-CONVERSION-STYLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_after_reading_for_text_conversion_style,
	    STATIC_FUNCTION(initialize_after_reading_for_text_conversion_style,
	    NIL,FALSE,1,1));
    Qinitialize_after_reading = STATIC_SYMBOL("INITIALIZE-AFTER-READING",
	    AB_package);
    temp_2 = 
	    SYMBOL_FUNCTION(Qinitialize_after_reading_for_text_conversion_style);
    set_get(Qtext_conversion_style,Qinitialize_after_reading,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize_after_reading),
	    Qclasses_which_define);
    temp_2 = CONS(Qtext_conversion_style,temp);
    mutate_global_property(Qinitialize_after_reading,temp_2,
	    Qclasses_which_define);
    Qinitialize_for_text_conversion_style = 
	    STATIC_SYMBOL("INITIALIZE-FOR-TEXT-CONVERSION-STYLE",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_text_conversion_style,
	    STATIC_FUNCTION(initialize_for_text_conversion_style,NIL,FALSE,
	    1,1));
    Qinitialize = STATIC_SYMBOL("INITIALIZE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qinitialize_for_text_conversion_style);
    set_get(Qtext_conversion_style,Qinitialize,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp_2 = CONS(Qtext_conversion_style,temp);
    mutate_global_property(Qinitialize,temp_2,Qclasses_which_define);
    Qtext_conversion_style_name_qm = 
	    STATIC_SYMBOL("TEXT-CONVERSION-STYLE-NAME\?",AB_package);
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_10 = STATIC_CONS(Qno_item,Qnil);
    list_constant_1 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_10,Qsymbol);
    set_property_value_function(get_symbol_properties_function(Qtext_conversion_style_name_qm),
	    Qtype_specification_simple_expansion,list_constant_1);
    define_type_specification_explicit_complex_type(Qtext_conversion_style_name_qm,
	    list_constant_1);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qtext_conversion_style_name_qm);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    text_conversion_style_name_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(text_conversion_style_name_qm_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qtext_conversion_style_name_qm,
	    text_conversion_style_name_qm_evaluation_setter_1);
    text_conversion_style_name_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(text_conversion_style_name_qm_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qtext_conversion_style_name_qm,
	    text_conversion_style_name_qm_evaluation_getter_1);
    string_constant_60 = STATIC_STRING("1m1m830Uy1m9k83Zy1m830Uy83-Eay");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_60));
    string_constant_61 = STATIC_STRING("1l1m83-Eay83-6y");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_61));
    Qtext_conversion_style_name = 
	    STATIC_SYMBOL("TEXT-CONVERSION-STYLE-NAME",AB_package);
    Qregistered_directory_of_names_p = 
	    STATIC_SYMBOL("REGISTERED-DIRECTORY-OF-NAMES-P",AB_package);
    mutate_global_property(Qtext_conversion_style_name,T,
	    Qregistered_directory_of_names_p);
    Qframe_status_and_notes = STATIC_SYMBOL("FRAME-STATUS-AND-NOTES",
	    AB_package);
    Qstack_change = STATIC_SYMBOL("STACK-CHANGE",AB_package);
    Qput_text_conversion_style = STATIC_SYMBOL("PUT-TEXT-CONVERSION-STYLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_text_conversion_style,
	    STATIC_FUNCTION(put_text_conversion_style,NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qtext_conversion_style,
	    SYMBOL_FUNCTION(Qput_text_conversion_style),Qslot_putter);
    Qcompile_text_conversion_style_name_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-TEXT-CONVERSION-STYLE-NAME\?-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_text_conversion_style_name_qm_for_slot,
	    STATIC_FUNCTION(compile_text_conversion_style_name_qm_for_slot,
	    NIL,TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qtext_conversion_style_name_qm,
	    SYMBOL_FUNCTION(Qcompile_text_conversion_style_name_qm_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qtext_conversion_style_name_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    list_constant_11 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_11,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    Qwrite_text_conversion_style_name_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-TEXT-CONVERSION-STYLE-NAME\?-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_text_conversion_style_name_qm_from_slot,
	    STATIC_FUNCTION(write_text_conversion_style_name_qm_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qtext_conversion_style_name_qm,
	    SYMBOL_FUNCTION(Qwrite_text_conversion_style_name_qm_from_slot),
	    Qslot_value_writer);
    Qexternal_character_set = STATIC_SYMBOL("EXTERNAL-CHARACTER-SET",
	    AB_package);
    Qexternal_line_separator = STATIC_SYMBOL("EXTERNAL-LINE-SEPARATOR",
	    AB_package);
    Qhan_unification_mode = STATIC_SYMBOL("HAN-UNIFICATION-MODE",AB_package);
    Qput_external_character_set = 
	    STATIC_SYMBOL("PUT-EXTERNAL-CHARACTER-SET",AB_package);
    SET_SYMBOL_FUNCTION(Qput_external_character_set,
	    STATIC_FUNCTION(put_external_character_set,NIL,FALSE,3,3));
    mutate_global_property(Qexternal_character_set,
	    SYMBOL_FUNCTION(Qput_external_character_set),Qslot_putter);
    Qput_unconvertible_character_spec = 
	    STATIC_SYMBOL("PUT-UNCONVERTIBLE-CHARACTER-SPEC",AB_package);
    SET_SYMBOL_FUNCTION(Qput_unconvertible_character_spec,
	    STATIC_FUNCTION(put_unconvertible_character_spec,NIL,FALSE,3,3));
    mutate_global_property(Qunconvertible_character_spec,
	    SYMBOL_FUNCTION(Qput_unconvertible_character_spec),Qslot_putter);
    Qput_external_line_separator = 
	    STATIC_SYMBOL("PUT-EXTERNAL-LINE-SEPARATOR",AB_package);
    SET_SYMBOL_FUNCTION(Qput_external_line_separator,
	    STATIC_FUNCTION(put_external_line_separator,NIL,FALSE,3,3));
    mutate_global_property(Qexternal_line_separator,
	    SYMBOL_FUNCTION(Qput_external_line_separator),Qslot_putter);
    Qput_han_unification_mode = STATIC_SYMBOL("PUT-HAN-UNIFICATION-MODE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_han_unification_mode,
	    STATIC_FUNCTION(put_han_unification_mode,NIL,FALSE,3,3));
    mutate_global_property(Qhan_unification_mode,
	    SYMBOL_FUNCTION(Qput_han_unification_mode),Qslot_putter);
    string_constant_62 = STATIC_STRING("1m1m83Ffy830iy1m83Ffy83-Uy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_62));
    string_constant = STATIC_STRING("Text must contain a single character");
    string_constant_1 = 
	    STATIC_STRING("Character code must be an integer between 0 and 65535");
    Qcompile_unconvertible_character_spec_for_slot = 
	    STATIC_SYMBOL("COMPILE-UNCONVERTIBLE-CHARACTER-SPEC-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_unconvertible_character_spec_for_slot,
	    STATIC_FUNCTION(compile_unconvertible_character_spec_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qunconvertible_character_spec,
	    SYMBOL_FUNCTION(Qcompile_unconvertible_character_spec_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qunconvertible_character_spec,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_2 = STATIC_STRING("none");
    string_constant_3 = STATIC_STRING("~c");
    Qwrite_unconvertible_character_spec_from_slot = 
	    STATIC_SYMBOL("WRITE-UNCONVERTIBLE-CHARACTER-SPEC-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_unconvertible_character_spec_from_slot,
	    STATIC_FUNCTION(write_unconvertible_character_spec_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qunconvertible_character_spec,
	    SYMBOL_FUNCTION(Qwrite_unconvertible_character_spec_from_slot),
	    Qslot_value_writer);
    string_constant_63 = 
	    STATIC_STRING("1q1m83DQy1m9k83EKy1m83DQy1m9k83-PJy1m83DQy1m9k83-cay1m83DQy1m9k83-PSy1m83DQy1m9k83-ury1m83DQy1m9k83-usy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_63));
    Qcr = STATIC_SYMBOL("CR",AB_package);
    Qlf = STATIC_SYMBOL("LF",AB_package);
    Qcrlf = STATIC_SYMBOL("CRLF",AB_package);
    Qline_separator = STATIC_SYMBOL("LINE-SEPARATOR",AB_package);
    Qwrite_line_separator_from_slot = 
	    STATIC_SYMBOL("WRITE-LINE-SEPARATOR-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_line_separator_from_slot,
	    STATIC_FUNCTION(write_line_separator_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qline_separator,
	    SYMBOL_FUNCTION(Qwrite_line_separator_from_slot),
	    Qslot_value_writer);
    string_constant_64 = 
	    STATIC_STRING("1o1m83Cby1m9k8378y1m83Cby1m9k83kDy1m83Cby1m9k83-MNy1m83Cby1m9k83-MOy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_64));
    string_constant_65 = 
	    STATIC_STRING("13My1m83B5y1m9k83oHy1m83B5y1m9k83kIy1m83B5y1m9k83kJy1m83B5y1m9k83kKy1m83B5y1m9k83kLy1m83B5y1m9k83kPy1m83B5y1m9k83kOy1m83B5y1m9k8");
    string_constant_66 = 
	    STATIC_STRING("3kQy1m83B5y1m9k83kRy1m83B5y1m9k83kMy1m83B5y1m9k83kNy1m83B5y1m9k83k6y1m83B5y1m9k83-bZy1m83B5y1m9k83-oYy1m83B5y1m9k83kFy1m83B5y1m9");
    string_constant_67 = 
	    STATIC_STRING("k83-c8y1m83B5y1m9k83Pry1m83B5y1m9k83-W3y1m83B5y1m9k83-uny1m83B5y1m9k83-upy1m83B5y1m9k83-uuy1m83B5y1m9k83-uvy1m83B5y1m9k83-uxy1m8");
    string_constant_68 = 
	    STATIC_STRING("3B5y1m9k83-v+y1m83B5y1m9k9l1m83B5y1m9k83-xjy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qab_gensym);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_4(string_constant_65,
	    string_constant_66,string_constant_67,string_constant_68)));
    Qpreferred_spelling_for_character_set = 
	    STATIC_SYMBOL("PREFERRED-SPELLING-FOR-CHARACTER-SET",AB_package);
    Preferred_spelling_for_character_set_prop = 
	    Qpreferred_spelling_for_character_set;
    array_constant_2 = STATIC_ARRAY(list_constant_11,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)57344L);
    mutate_global_property(Qab_gensym,array_constant_2,
	    Qpreferred_spelling_for_character_set);
    Qunicode_byte_swapped = STATIC_SYMBOL("UNICODE-BYTE-SWAPPED",AB_package);
    array_constant_3 = STATIC_ARRAY(list_constant_11,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)12L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)13L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)16L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)17L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)19L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)22L,(SI_Long)20L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)23L,(SI_Long)57344L);
    mutate_global_property(Qunicode_byte_swapped,array_constant_3,
	    Qpreferred_spelling_for_character_set);
    Qunicode_utf_7 = STATIC_SYMBOL("UNICODE-UTF-7",AB_package);
    array_constant_4 = STATIC_ARRAY(list_constant_11,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)11L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)12L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)13L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)57344L);
    mutate_global_property(Qunicode_utf_7,array_constant_4,
	    Qpreferred_spelling_for_character_set);
    Qunicode_utf_8 = STATIC_SYMBOL("UNICODE-UTF-8",AB_package);
    array_constant_5 = STATIC_ARRAY(list_constant_11,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)9L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)10L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)11L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)12L,(SI_Long)56L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)13L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)57344L);
    mutate_global_property(Qunicode_utf_8,array_constant_5,
	    Qpreferred_spelling_for_character_set);
    Qx_compound_text = STATIC_SYMBOL("X-COMPOUND-TEXT",AB_package);
    array_constant_6 = STATIC_ARRAY(list_constant_11,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)88L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)9L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)10L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)11L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)13L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)23L,(SI_Long)57344L);
    mutate_global_property(Qx_compound_text,array_constant_6,
	    Qpreferred_spelling_for_character_set);
    Qlatin_1 = STATIC_SYMBOL("LATIN-1",AB_package);
    array_constant_7 = STATIC_ARRAY(list_constant_11,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)57344L);
    mutate_global_property(Qlatin_1,array_constant_7,
	    Qpreferred_spelling_for_character_set);
    Qlatin_2 = STATIC_SYMBOL("LATIN-2",AB_package);
    array_constant_8 = STATIC_ARRAY(list_constant_11,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)5L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)15L,(SI_Long)57344L);
    mutate_global_property(Qlatin_2,array_constant_8,
	    Qpreferred_spelling_for_character_set);
    Qlatin_3 = STATIC_SYMBOL("LATIN-3",AB_package);
    array_constant_9 = STATIC_ARRAY(list_constant_11,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)5L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)15L,(SI_Long)57344L);
    mutate_global_property(Qlatin_3,array_constant_9,
	    Qpreferred_spelling_for_character_set);
    Qlatin_4 = STATIC_SYMBOL("LATIN-4",AB_package);
    array_constant_10 = STATIC_ARRAY(list_constant_11,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)5L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)52L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)15L,(SI_Long)57344L);
    mutate_global_property(Qlatin_4,array_constant_10,
	    Qpreferred_spelling_for_character_set);
    Qlatin_greek = STATIC_SYMBOL("LATIN-GREEK",AB_package);
    array_constant_11 = STATIC_ARRAY(list_constant_11,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)5L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)10L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)15L,(SI_Long)57344L);
    mutate_global_property(Qlatin_greek,array_constant_11,
	    Qpreferred_spelling_for_character_set);
    Qlatin_arabic = STATIC_SYMBOL("LATIN-ARABIC",AB_package);
    array_constant_12 = STATIC_ARRAY(list_constant_11,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)5L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)9L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)10L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)11L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)15L,(SI_Long)57344L);
    mutate_global_property(Qlatin_arabic,array_constant_12,
	    Qpreferred_spelling_for_character_set);
    mutate_global_property(Qlatin_greek,array_constant_11,
	    Qpreferred_spelling_for_character_set);
    Qlatin_hebrew = STATIC_SYMBOL("LATIN-HEBREW",AB_package);
    array_constant_13 = STATIC_ARRAY(list_constant_11,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)5L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)6L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)8L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)9L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)11L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)15L,(SI_Long)57344L);
    mutate_global_property(Qlatin_hebrew,array_constant_13,
	    Qpreferred_spelling_for_character_set);
    Qlatin_5 = STATIC_SYMBOL("LATIN-5",AB_package);
    array_constant_14 = STATIC_ARRAY(list_constant_11,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)0L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)5L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)6L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)15L,(SI_Long)57344L);
    mutate_global_property(Qlatin_5,array_constant_14,
	    Qpreferred_spelling_for_character_set);
    Qlatin_6 = STATIC_SYMBOL("LATIN-6",AB_package);
    array_constant_15 = STATIC_ARRAY(list_constant_11,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)0L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)5L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)6L,(SI_Long)54L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)15L,(SI_Long)57344L);
    mutate_global_property(Qlatin_6,array_constant_15,
	    Qpreferred_spelling_for_character_set);
    string_constant_4 = STATIC_STRING("unknown");
    string_constant_5 = STATIC_STRING("~a");
    Qcharacter_set = STATIC_SYMBOL("CHARACTER-SET",AB_package);
    Qwrite_character_set_from_slot = 
	    STATIC_SYMBOL("WRITE-CHARACTER-SET-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_character_set_from_slot,
	    STATIC_FUNCTION(write_character_set_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qcharacter_set,
	    SYMBOL_FUNCTION(Qwrite_character_set_from_slot),
	    Qslot_value_writer);
    Kfirst_of_each_word = STATIC_SYMBOL("FIRST-OF-EACH-WORD",Pkeyword);
    Qwrite_han_unification_mode_from_slot = 
	    STATIC_SYMBOL("WRITE-HAN-UNIFICATION-MODE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_han_unification_mode_from_slot,
	    STATIC_FUNCTION(write_han_unification_mode_from_slot,NIL,FALSE,
	    2,2));
    mutate_global_property(Qhan_unification_mode,
	    SYMBOL_FUNCTION(Qwrite_han_unification_mode_from_slot),
	    Qslot_value_writer);
    Qgeneralized_dos = STATIC_SYMBOL("GENERALIZED-DOS",AB_package);
    Qdos = STATIC_SYMBOL("DOS",AB_package);
    Qwin32 = STATIC_SYMBOL("WIN32",AB_package);
    Qopen_file_for_read_lisp_side = 
	    STATIC_SYMBOL("OPEN-FILE-FOR-READ-LISP-SIDE",AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qopen_file_for_read_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qopen_for_read = STATIC_SYMBOL("OPEN-FOR-READ",AB_package);
    Qinput = STATIC_SYMBOL("INPUT",AB_package);
    Qfailed_to_open_for_read = STATIC_SYMBOL("FAILED-TO-OPEN-FOR-READ",
	    AB_package);
    Qclosed = STATIC_SYMBOL("CLOSED",AB_package);
    string_constant_6 = STATIC_STRING("");
    SET_SYMBOL_FUNCTION(Qopen_file_for_read_lisp_side,
	    STATIC_FUNCTION(open_file_for_read_lisp_side,NIL,FALSE,1,1));
    Qopen_file_for_write_lisp_side = 
	    STATIC_SYMBOL("OPEN-FILE-FOR-WRITE-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qopen_file_for_write_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qopen_for_write = STATIC_SYMBOL("OPEN-FOR-WRITE",AB_package);
    Qoutput = STATIC_SYMBOL("OUTPUT",AB_package);
    Qfailed_to_open_for_write = STATIC_SYMBOL("FAILED-TO-OPEN-FOR-WRITE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qopen_file_for_write_lisp_side,
	    STATIC_FUNCTION(open_file_for_write_lisp_side,NIL,FALSE,1,1));
    Qopen_file_for_append_lisp_side = 
	    STATIC_SYMBOL("OPEN-FILE-FOR-APPEND-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qopen_file_for_append_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qopen_for_append = STATIC_SYMBOL("OPEN-FOR-APPEND",AB_package);
    Qfailed_to_open_for_append = STATIC_SYMBOL("FAILED-TO-OPEN-FOR-APPEND",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qopen_file_for_append_lisp_side,
	    STATIC_FUNCTION(open_file_for_append_lisp_side,NIL,FALSE,2,2));
    Qopen_file_for_read_and_write_lisp_side = 
	    STATIC_SYMBOL("OPEN-FILE-FOR-READ-AND-WRITE-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qopen_file_for_read_and_write_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    Qopen_for_read_and_write = STATIC_SYMBOL("OPEN-FOR-READ-AND-WRITE",
	    AB_package);
    Qinput_and_output = STATIC_SYMBOL("INPUT-AND-OUTPUT",AB_package);
    Qfailed_to_open_for_read_and_write = 
	    STATIC_SYMBOL("FAILED-TO-OPEN-FOR-READ-AND-WRITE",AB_package);
    SET_SYMBOL_FUNCTION(Qopen_file_for_read_and_write_lisp_side,
	    STATIC_FUNCTION(open_file_for_read_and_write_lisp_side,NIL,
	    FALSE,1,1));
    Qclose_file_lisp_side = STATIC_SYMBOL("CLOSE-FILE-LISP-SIDE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qclose_file_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qclose_file_lisp_side,
	    STATIC_FUNCTION(close_file_lisp_side,NIL,FALSE,1,1));
    Qsuccessfully_closed = STATIC_SYMBOL("SUCCESSFULLY-CLOSED",AB_package);
    Qfailed_to_close = STATIC_SYMBOL("FAILED-TO-CLOSE",AB_package);
    Qtried_to_close_when_already_closed = 
	    STATIC_SYMBOL("TRIED-TO-CLOSE-WHEN-ALREADY-CLOSED",AB_package);
    Qclose_file_leaving_stream_lisp_side = 
	    STATIC_SYMBOL("CLOSE-FILE-LEAVING-STREAM-LISP-SIDE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qclose_file_leaving_stream_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qclose_file_leaving_stream_lisp_side,
	    STATIC_FUNCTION(close_file_leaving_stream_lisp_side,NIL,FALSE,
	    1,1));
    Qclose_all_open_g2_streams_lisp_side = 
	    STATIC_SYMBOL("CLOSE-ALL-OPEN-G2-STREAMS-LISP-SIDE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qclose_all_open_g2_streams_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qclose_all_open_g2_streams_lisp_side,
	    STATIC_FUNCTION(close_all_open_g2_streams_lisp_side,NIL,FALSE,
	    0,0));
    Qset_file_position_lisp_side = 
	    STATIC_SYMBOL("SET-FILE-POSITION-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qset_file_position_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_7 = 
	    STATIC_STRING("Tried to set file position past end-of-file");
    Qsuccessfully_updated_position = 
	    STATIC_SYMBOL("SUCCESSFULLY-UPDATED-POSITION",AB_package);
    Qfailed_to_update_position = STATIC_SYMBOL("FAILED-TO-UPDATE-POSITION",
	    AB_package);
    Qtried_to_update_position_when_closed = 
	    STATIC_SYMBOL("TRIED-TO-UPDATE-POSITION-WHEN-CLOSED",AB_package);
    string_constant_8 = 
	    STATIC_STRING("Cannot update position of closed stream");
    SET_SYMBOL_FUNCTION(Qset_file_position_lisp_side,
	    STATIC_FUNCTION(set_file_position_lisp_side,NIL,FALSE,3,3));
    Qrename_file_lisp_side = STATIC_SYMBOL("RENAME-FILE-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qrename_file_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qrename_file_lisp_side,
	    STATIC_FUNCTION(rename_file_lisp_side,NIL,FALSE,2,2));
    Qcopy_file_lisp_side = STATIC_SYMBOL("COPY-FILE-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qcopy_file_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qcopy_file_lisp_side,
	    STATIC_FUNCTION(copy_file_lisp_side,NIL,FALSE,2,2));
    Qdelete_file_lisp_side = STATIC_SYMBOL("DELETE-FILE-LISP-SIDE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qdelete_file_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qdelete_file_lisp_side,
	    STATIC_FUNCTION(delete_file_lisp_side,NIL,FALSE,1,1));
    Qread_line_lisp_side = STATIC_SYMBOL("READ-LINE-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qread_line_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qtried_read_line_on_stream_not_opened_for_read = 
	    STATIC_SYMBOL("TRIED-READ-LINE-ON-STREAM-NOT-OPENED-FOR-READ",
	    AB_package);
    Qunicode = STATIC_SYMBOL("UNICODE",AB_package);
    Qunicode_ucs_2 = STATIC_SYMBOL("UNICODE-UCS-2",AB_package);
    Qunicode_ucs_2_byte_swapped = 
	    STATIC_SYMBOL("UNICODE-UCS-2-BYTE-SWAPPED",AB_package);
    Qus_ascii = STATIC_SYMBOL("US-ASCII",AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    Qutf_g = STATIC_SYMBOL("UTF-G",AB_package);
    Qend_of_file_reached = STATIC_SYMBOL("END-OF-FILE-REACHED",AB_package);
    Qerror_during_read_line = STATIC_SYMBOL("ERROR-DURING-READ-LINE",
	    AB_package);
    Qline_truncated_during_read = 
	    STATIC_SYMBOL("LINE-TRUNCATED-DURING-READ",AB_package);
    Qsuccessfully_read_line = STATIC_SYMBOL("SUCCESSFULLY-READ-LINE",
	    AB_package);
    Qtried_read_line_when_closed = 
	    STATIC_SYMBOL("TRIED-READ-LINE-WHEN-CLOSED",AB_package);
    SET_SYMBOL_FUNCTION(Qread_line_lisp_side,
	    STATIC_FUNCTION(read_line_lisp_side,NIL,FALSE,1,1));
    Qbyte_range_0_255_mask = STATIC_SYMBOL("BYTE-RANGE-0-255-MASK",AB_package);
    SET_SYMBOL_VALUE(Qbyte_range_0_255_mask,FIX((SI_Long)255L));
    Qread_byte_lisp_side = STATIC_SYMBOL("READ-BYTE-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qread_byte_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qtried_read_byte_on_stream_not_opened_for_read = 
	    STATIC_SYMBOL("TRIED-READ-BYTE-ON-STREAM-NOT-OPENED-FOR-READ",
	    AB_package);
    Qsuccessfully_read_byte = STATIC_SYMBOL("SUCCESSFULLY-READ-BYTE",
	    AB_package);
    Qerror_during_read_byte = STATIC_SYMBOL("ERROR-DURING-READ-BYTE",
	    AB_package);
    Qtried_read_byte_when_closed = 
	    STATIC_SYMBOL("TRIED-READ-BYTE-WHEN-CLOSED",AB_package);
    SET_SYMBOL_FUNCTION(Qread_byte_lisp_side,
	    STATIC_FUNCTION(read_byte_lisp_side,NIL,FALSE,1,1));
    Qread_bytes_as_text_lisp_side = 
	    STATIC_SYMBOL("READ-BYTES-AS-TEXT-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qread_bytes_as_text_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_9 = 
	    STATIC_STRING("Request to read ~d bytes which exceeds the ~\n                    maximum G2 text length, ~d");
    Qtried_read_bytes_on_stream_not_opened_for_read = 
	    STATIC_SYMBOL("TRIED-READ-BYTES-ON-STREAM-NOT-OPENED-FOR-READ",
	    AB_package);
    Qtext_truncated_during_read = 
	    STATIC_SYMBOL("TEXT-TRUNCATED-DURING-READ",AB_package);
    Qsuccessfully_read_bytes = STATIC_SYMBOL("SUCCESSFULLY-READ-BYTES",
	    AB_package);
    Qerror_during_read_bytes = STATIC_SYMBOL("ERROR-DURING-READ-BYTES",
	    AB_package);
    Qtried_read_bytes_when_closed = 
	    STATIC_SYMBOL("TRIED-READ-BYTES-WHEN-CLOSED",AB_package);
    SET_SYMBOL_FUNCTION(Qread_bytes_as_text_lisp_side,
	    STATIC_FUNCTION(read_bytes_as_text_lisp_side,NIL,FALSE,2,2));
    Qwrite_line_lisp_side = STATIC_SYMBOL("WRITE-LINE-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qwrite_line_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qwrite_line_lisp_side,
	    STATIC_FUNCTION(write_line_lisp_side,NIL,FALSE,2,2));
    Qwrite_string_lisp_side = STATIC_SYMBOL("WRITE-STRING-LISP-SIDE",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qwrite_string_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qwrite_string_lisp_side,
	    STATIC_FUNCTION(write_string_lisp_side,NIL,FALSE,2,2));
    Qwrite_line_in_gensym_charset_lisp_side = 
	    STATIC_SYMBOL("WRITE-LINE-IN-GENSYM-CHARSET-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qwrite_line_in_gensym_charset_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    Qutf_g_string = STATIC_SYMBOL("UTF-G-STRING",AB_package);
    Qtext_conversion_style_for_purpose = 
	    STATIC_SYMBOL("TEXT-CONVERSION-STYLE-FOR-PURPOSE",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_line_in_gensym_charset_lisp_side,
	    STATIC_FUNCTION(write_line_in_gensym_charset_lisp_side,NIL,
	    FALSE,2,2));
    Qwrite_string_in_gensym_charset_lisp_side = 
	    STATIC_SYMBOL("WRITE-STRING-IN-GENSYM-CHARSET-LISP-SIDE",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qwrite_string_in_gensym_charset_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qwrite_string_in_gensym_charset_lisp_side,
	    STATIC_FUNCTION(write_string_in_gensym_charset_lisp_side,NIL,
	    FALSE,2,2));
    Qwrite_string_or_line_lisp_side_internal = 
	    STATIC_SYMBOL("WRITE-STRING-OR-LINE-LISP-SIDE-INTERNAL",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qwrite_string_or_line_lisp_side_internal,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    Qsuccessfully_wrote_line = STATIC_SYMBOL("SUCCESSFULLY-WROTE-LINE",
	    AB_package);
    Qsuccessfully_wrote_string = STATIC_SYMBOL("SUCCESSFULLY-WROTE-STRING",
	    AB_package);
    Qerror_during_write_line = STATIC_SYMBOL("ERROR-DURING-WRITE-LINE",
	    AB_package);
    Qerror_during_write_string = STATIC_SYMBOL("ERROR-DURING-WRITE-STRING",
	    AB_package);
    Qtried_write_line_when_closed = 
	    STATIC_SYMBOL("TRIED-WRITE-LINE-WHEN-CLOSED",AB_package);
    Qtried_write_string_when_closed = 
	    STATIC_SYMBOL("TRIED-WRITE-STRING-WHEN-CLOSED",AB_package);
    string_constant_10 = STATIC_STRING("Cannot write-line to closed stream");
    string_constant_11 = STATIC_STRING("Cannot write-string to closed stream");
    SET_SYMBOL_FUNCTION(Qwrite_string_or_line_lisp_side_internal,
	    STATIC_FUNCTION(write_string_or_line_lisp_side_internal,NIL,
	    FALSE,4,4));
    Qwrite_byte_lisp_side = STATIC_SYMBOL("WRITE-BYTE-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qwrite_byte_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qsuccessfully_wrote_byte = STATIC_SYMBOL("SUCCESSFULLY-WROTE-BYTE",
	    AB_package);
    Qerror_during_write_byte = STATIC_SYMBOL("ERROR-DURING-WRITE-BYTE",
	    AB_package);
    Qtried_write_byte_when_closed = 
	    STATIC_SYMBOL("TRIED-WRITE-BYTE-WHEN-CLOSED",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_byte_lisp_side,
	    STATIC_FUNCTION(write_byte_lisp_side,NIL,FALSE,2,2));
    Qwrite_bytes_lisp_side = STATIC_SYMBOL("WRITE-BYTES-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qwrite_bytes_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_12 = 
	    STATIC_STRING("Request to write bytes of non-sequence value ~a");
    SET_SYMBOL_FUNCTION(Qwrite_bytes_lisp_side,
	    STATIC_FUNCTION(write_bytes_lisp_side,NIL,FALSE,2,2));
    Qfloat_to_bytes_lisp_side = STATIC_SYMBOL("FLOAT-TO-BYTES-LISP-SIDE",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qfloat_to_bytes_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qfloat_to_bytes_lisp_side,
	    STATIC_FUNCTION(float_to_bytes_lisp_side,NIL,FALSE,1,1));
    Qbytes_to_float_lisp_side = STATIC_SYMBOL("BYTES-TO-FLOAT-LISP-SIDE",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qbytes_to_float_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qbytes_to_float_lisp_side,
	    STATIC_FUNCTION(bytes_to_float_lisp_side,NIL,FALSE,8,8));
    Qfile_host_string_lisp_side = 
	    STATIC_SYMBOL("FILE-HOST-STRING-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qfile_host_string_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qfile_host_string_lisp_side,
	    STATIC_FUNCTION(file_host_string_lisp_side,NIL,FALSE,1,1));
    Qfile_device_string_lisp_side = 
	    STATIC_SYMBOL("FILE-DEVICE-STRING-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qfile_device_string_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qfile_device_string_lisp_side,
	    STATIC_FUNCTION(file_device_string_lisp_side,NIL,FALSE,1,1));
    Qfile_directory_string_lisp_side = 
	    STATIC_SYMBOL("FILE-DIRECTORY-STRING-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qfile_directory_string_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qfile_directory_string_lisp_side,
	    STATIC_FUNCTION(file_directory_string_lisp_side,NIL,FALSE,1,1));
    Qfile_directory_string_to_list_lisp_side = 
	    STATIC_SYMBOL("FILE-DIRECTORY-STRING-TO-LIST-LISP-SIDE",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qfile_directory_string_to_list_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    Qtext_list = STATIC_SYMBOL("TEXT-LIST",AB_package);
    Kabsolute = STATIC_SYMBOL("ABSOLUTE",Pkeyword);
    Krelative = STATIC_SYMBOL("RELATIVE",Pkeyword);
    SET_SYMBOL_FUNCTION(Qfile_directory_string_to_list_lisp_side,
	    STATIC_FUNCTION(file_directory_string_to_list_lisp_side,NIL,
	    FALSE,1,1));
    Qfile_directory_list_to_string_lisp_side = 
	    STATIC_SYMBOL("FILE-DIRECTORY-LIST-TO-STRING-LISP-SIDE",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qfile_directory_list_to_string_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qfile_directory_list_to_string_lisp_side,
	    STATIC_FUNCTION(file_directory_list_to_string_lisp_side,NIL,
	    FALSE,1,1));
    Qfile_base_name_string_lisp_side = 
	    STATIC_SYMBOL("FILE-BASE-NAME-STRING-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qfile_base_name_string_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qfile_base_name_string_lisp_side,
	    STATIC_FUNCTION(file_base_name_string_lisp_side,NIL,FALSE,1,1));
    Qfile_extension_string_lisp_side = 
	    STATIC_SYMBOL("FILE-EXTENSION-STRING-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qfile_extension_string_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qfile_extension_string_lisp_side,
	    STATIC_FUNCTION(file_extension_string_lisp_side,NIL,FALSE,1,1));
    Qfile_version_string_lisp_side = 
	    STATIC_SYMBOL("FILE-VERSION-STRING-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qfile_version_string_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qfile_version_string_lisp_side,
	    STATIC_FUNCTION(file_version_string_lisp_side,NIL,FALSE,1,1));
    Qcollect_into_filestring_lisp_side = 
	    STATIC_SYMBOL("COLLECT-INTO-FILESTRING-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qcollect_into_filestring_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    Qunbound_in_protected_let = STATIC_SYMBOL("UNBOUND-IN-PROTECTED-LET",
	    AB_package);
    string_constant_13 = STATIC_STRING("~a~a~a~a~a~a");
    SET_SYMBOL_FUNCTION(Qcollect_into_filestring_lisp_side,
	    STATIC_FUNCTION(collect_into_filestring_lisp_side,NIL,FALSE,6,6));
    Qpartition_filestring_lisp_side = 
	    STATIC_SYMBOL("PARTITION-FILESTRING-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qpartition_filestring_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qpartition_filestring_lisp_side,
	    STATIC_FUNCTION(partition_filestring_lisp_side,NIL,FALSE,1,1));
    Qtype_of_file_system_lisp_side = 
	    STATIC_SYMBOL("TYPE-OF-FILE-SYSTEM-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qtype_of_file_system_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qtype_of_file_system_lisp_side,
	    STATIC_FUNCTION(type_of_file_system_lisp_side,NIL,FALSE,0,0));
    Qfile_exists_lisp_side = STATIC_SYMBOL("FILE-EXISTS-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qfile_exists_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qg2_directory_pathname_w = STATIC_SYMBOL("G2-DIRECTORY-PATHNAME-W",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qfile_exists_lisp_side,
	    STATIC_FUNCTION(file_exists_lisp_side,NIL,FALSE,1,1));
    Qfile_names_are_identical_lisp_side = 
	    STATIC_SYMBOL("FILE-NAMES-ARE-IDENTICAL-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qfile_names_are_identical_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qfile_names_are_identical_lisp_side,
	    STATIC_FUNCTION(file_names_are_identical_lisp_side,NIL,FALSE,2,2));
    Qlength_of_file_lisp_side = STATIC_SYMBOL("LENGTH-OF-FILE-LISP-SIDE",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qlength_of_file_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qsuccessfully_obtained_file_length = 
	    STATIC_SYMBOL("SUCCESSFULLY-OBTAINED-FILE-LENGTH",AB_package);
    Qerror_getting_file_length = STATIC_SYMBOL("ERROR-GETTING-FILE-LENGTH",
	    AB_package);
    Qtried_to_get_length_when_closed = 
	    STATIC_SYMBOL("TRIED-TO-GET-LENGTH-WHEN-CLOSED",AB_package);
    string_constant_14 = STATIC_STRING("Cannot get length of closed stream");
    SET_SYMBOL_FUNCTION(Qlength_of_file_lisp_side,
	    STATIC_FUNCTION(length_of_file_lisp_side,NIL,FALSE,1,1));
    Qlatest_date_file_was_modified_lisp_side = 
	    STATIC_SYMBOL("LATEST-DATE-FILE-WAS-MODIFIED-LISP-SIDE",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qlatest_date_file_was_modified_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qlatest_date_file_was_modified_lisp_side,
	    STATIC_FUNCTION(latest_date_file_was_modified_lisp_side,NIL,
	    FALSE,1,1));
    Qlatest_date_file_was_accessed_lisp_side = 
	    STATIC_SYMBOL("LATEST-DATE-FILE-WAS-ACCESSED-LISP-SIDE",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qlatest_date_file_was_accessed_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qlatest_date_file_was_accessed_lisp_side,
	    STATIC_FUNCTION(latest_date_file_was_accessed_lisp_side,NIL,
	    FALSE,1,1));
    Qlatest_date_file_attributes_were_changed_lisp_side = 
	    STATIC_SYMBOL("LATEST-DATE-FILE-ATTRIBUTES-WERE-CHANGED-LISP-SIDE",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qlatest_date_file_attributes_were_changed_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qlatest_date_file_attributes_were_changed_lisp_side,
	    STATIC_FUNCTION(latest_date_file_attributes_were_changed_lisp_side,
	    NIL,FALSE,1,1));
    Qdirectory_exists_lisp_side = 
	    STATIC_SYMBOL("DIRECTORY-EXISTS-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qdirectory_exists_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qconvert_file_strings_to_uppercase_p = 
	    STATIC_SYMBOL("CONVERT-FILE-STRINGS-TO-UPPERCASE-P",AB_package);
    SET_SYMBOL_FUNCTION(Qdirectory_exists_lisp_side,
	    STATIC_FUNCTION(directory_exists_lisp_side,NIL,FALSE,1,1));
    Qfiles_in_directory_lisp_side = 
	    STATIC_SYMBOL("FILES-IN-DIRECTORY-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qfiles_in_directory_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qfiles_in_directory_lisp_side,
	    STATIC_FUNCTION(files_in_directory_lisp_side,NIL,FALSE,1,1));
    Qsubdirectories_in_directory_lisp_side = 
	    STATIC_SYMBOL("SUBDIRECTORIES-IN-DIRECTORY-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qsubdirectories_in_directory_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qsubdirectories_in_directory_lisp_side,
	    STATIC_FUNCTION(subdirectories_in_directory_lisp_side,NIL,
	    FALSE,1,1));
    Qdefault_directory_lisp_side = 
	    STATIC_SYMBOL("DEFAULT-DIRECTORY-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qdefault_directory_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qdefault_directory_lisp_side,
	    STATIC_FUNCTION(default_directory_lisp_side,NIL,FALSE,0,0));
    Qchange_default_directory_lisp_side = 
	    STATIC_SYMBOL("CHANGE-DEFAULT-DIRECTORY-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qchange_default_directory_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    Qforeign_image = STATIC_SYMBOL("FOREIGN-IMAGE",AB_package);
    Qattribute = STATIC_SYMBOL("ATTRIBUTE",AB_package);
    Qstatistics = STATIC_SYMBOL("STATISTICS",AB_package);
    Qkb = STATIC_SYMBOL("KB",AB_package);
    SET_SYMBOL_FUNCTION(Qchange_default_directory_lisp_side,
	    STATIC_FUNCTION(change_default_directory_lisp_side,NIL,FALSE,1,1));
    Qget_temporary_filename_lisp_side = 
	    STATIC_SYMBOL("GET-TEMPORARY-FILENAME-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qget_temporary_filename_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_15 = STATIC_STRING("g2");
    string_constant_16 = 
	    STATIC_STRING("Unable to obtain temporary filename from operating system.");
    SET_SYMBOL_FUNCTION(Qget_temporary_filename_lisp_side,
	    STATIC_FUNCTION(get_temporary_filename_lisp_side,NIL,FALSE,0,0));
    Qdisk_space_available_in_directory_lisp_side = 
	    STATIC_SYMBOL("DISK-SPACE-AVAILABLE-IN-DIRECTORY-LISP-SIDE",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qdisk_space_available_in_directory_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qdisk_space_available_in_directory_lisp_side,
	    STATIC_FUNCTION(disk_space_available_in_directory_lisp_side,
	    NIL,FALSE,1,1));
    Qdevices_on_machine_lisp_side = 
	    STATIC_SYMBOL("DEVICES-ON-MACHINE-LISP-SIDE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qdevices_on_machine_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qdevices_on_machine_lisp_side,
	    STATIC_FUNCTION(devices_on_machine_lisp_side,NIL,FALSE,0,0));
    Qcreate_directory_lisp_side = 
	    STATIC_SYMBOL("CREATE-DIRECTORY-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qcreate_directory_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qcreate_directory_lisp_side,
	    STATIC_FUNCTION(create_directory_lisp_side,NIL,FALSE,3,3));
    Qg2_version_of_kb_file = STATIC_SYMBOL("G2-VERSION-OF-KB-FILE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_version_of_kb_file,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qversion_text = STATIC_SYMBOL("VERSION-TEXT",AB_package);
    Qsystem_version = STATIC_SYMBOL("SYSTEM-VERSION",AB_package);
    string_constant_17 = STATIC_STRING("G2 ~d.~d ~a");
    Qmajor_version_number = STATIC_SYMBOL("MAJOR-VERSION-NUMBER",AB_package);
    Qminor_version_number = STATIC_SYMBOL("MINOR-VERSION-NUMBER",AB_package);
    Qrevision_text = STATIC_SYMBOL("REVISION-TEXT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_version_of_kb_file,
	    STATIC_FUNCTION(g2_version_of_kb_file,NIL,FALSE,1,1));
    Qvms = STATIC_SYMBOL("VMS",AB_package);
    Qspawn_process_to_run_command_line_lisp_side = 
	    STATIC_SYMBOL("SPAWN-PROCESS-TO-RUN-COMMAND-LINE-LISP-SIDE",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qspawn_process_to_run_command_line_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qspawn_process_to_run_command_line_lisp_side,
	    STATIC_FUNCTION(spawn_process_to_run_command_line_lisp_side,
	    NIL,FALSE,1,1));
    Qspawn_process_with_arguments_lisp_side = 
	    STATIC_SYMBOL("SPAWN-PROCESS-WITH-ARGUMENTS-LISP-SIDE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qspawn_process_with_arguments_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qspawn_process_with_arguments_lisp_side,
	    STATIC_FUNCTION(spawn_process_with_arguments_lisp_side,NIL,
	    FALSE,1,1));
    Qavailable_sysproc_continuation_hashtable_hash_vector_131_vectors = 
	    STATIC_SYMBOL("AVAILABLE-SYSPROC-CONTINUATION-HASHTABLE-HASH-VECTOR-131-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_sysproc_continuation_hashtable_hash_vector_131_vectors,
	    Available_sysproc_continuation_hashtable_hash_vector_131_vectors);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qavailable_sysproc_continuation_hashtable_hash_vector_131_vectors,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcount_of_sysproc_continuation_hashtable_hash_vector_131_vectors = 
	    STATIC_SYMBOL("COUNT-OF-SYSPROC-CONTINUATION-HASHTABLE-HASH-VECTOR-131-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcount_of_sysproc_continuation_hashtable_hash_vector_131_vectors,
	    Count_of_sysproc_continuation_hashtable_hash_vector_131_vectors);
    record_system_variable(Qcount_of_sysproc_continuation_hashtable_hash_vector_131_vectors,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Available_sysproc_continuation_hashtable_hash_vector_131_vectors_vector 
	    == UNBOUND)
	Available_sysproc_continuation_hashtable_hash_vector_131_vectors_vector 
		= make_thread_array(Nil);
    Qout_sysproc_continuation_hashtable_hash_vector_131_vectors = 
	    STATIC_SYMBOL("OUT-SYSPROC-CONTINUATION-HASHTABLE-HASH-VECTOR-131-VECTORS",
	    AB_package);
    Qsysproc_continuation_hashtable_hash_vector_131_vector_memory_usage = 
	    STATIC_SYMBOL("SYSPROC-CONTINUATION-HASHTABLE-HASH-VECTOR-131-VECTOR-MEMORY-USAGE",
	    AB_package);
    string_constant_69 = STATIC_STRING("1q83-rly83*9y83-PDy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qout_sysproc_continuation_hashtable_hash_vector_131_vectors);
    push_optimized_constant(Qsysproc_continuation_hashtable_hash_vector_131_vector_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_69));
    SET_SYMBOL_FUNCTION(Qsysproc_continuation_hashtable_hash_vector_131_vector_memory_usage,
	    STATIC_FUNCTION(sysproc_continuation_hashtable_hash_vector_131_vector_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qout_sysproc_continuation_hashtable_hash_vector_131_vectors,
	    STATIC_FUNCTION(out_sysproc_continuation_hashtable_hash_vector_131_vectors,
	    NIL,FALSE,0,0));
    Qvector_pool = STATIC_SYMBOL("VECTOR-POOL",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qsysproc_continuation_hashtable_tree_for_hash = 
	    STATIC_SYMBOL("SYSPROC-CONTINUATION-HASHTABLE-TREE-FOR-HASH",
	    AB_package);
    if (Sysproc_continuation_table == UNBOUND)
	Sysproc_continuation_table = make_sysproc_continuation_hashtable();
    if (Highest_remote_spawn_index == UNBOUND)
	Highest_remote_spawn_index = FIX((SI_Long)0L);
    if (Used_remote_spawn_indices_qm == UNBOUND)
	Used_remote_spawn_indices_qm = Nil;
    Qno_internal_window = STATIC_SYMBOL("NO-INTERNAL-WINDOW",AB_package);
    Qremote_processes_unsupported = 
	    STATIC_SYMBOL("REMOTE-PROCESSES-UNSUPPORTED",AB_package);
    Qnot_a_remote_process = STATIC_SYMBOL("NOT-A-REMOTE-PROCESS",AB_package);
    Qspawn_remote_process_lisp_side = 
	    STATIC_SYMBOL("SPAWN-REMOTE-PROCESS-LISP-SIDE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qspawn_remote_process_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qremote_process_procedure_requires_g2_window = 
	    STATIC_SYMBOL("REMOTE-PROCESS-PROCEDURE-REQUIRES-G2-WINDOW",
	    AB_package);
    Qclean_up_sysproc_continuation = 
	    STATIC_SYMBOL("CLEAN-UP-SYSPROC-CONTINUATION",AB_package);
    SET_SYMBOL_FUNCTION(Qclean_up_sysproc_continuation,
	    STATIC_FUNCTION(clean_up_sysproc_continuation,NIL,FALSE,1,1));
    Qtelewindows = STATIC_SYMBOL("TELEWINDOWS",AB_package);
    Qremote_spawn_initiated = STATIC_SYMBOL("REMOTE-SPAWN-INITIATED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qspawn_remote_process_lisp_side,
	    STATIC_FUNCTION(spawn_remote_process_lisp_side,NIL,FALSE,2,2));
    Qg2_spawn_remote_process_to_run_command_line_lisp_side = 
	    STATIC_SYMBOL("G2-SPAWN-REMOTE-PROCESS-TO-RUN-COMMAND-LINE-LISP-SIDE",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_spawn_remote_process_to_run_command_line_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_spawn_remote_process_to_run_command_line_lisp_side,
	    STATIC_FUNCTION(g2_spawn_remote_process_to_run_command_line_lisp_side,
	    NIL,FALSE,2,2));
    Qspawn_remote_process_with_arguments_lisp_side = 
	    STATIC_SYMBOL("SPAWN-REMOTE-PROCESS-WITH-ARGUMENTS-LISP-SIDE",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qspawn_remote_process_with_arguments_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qspawn_remote_process_with_arguments_lisp_side,
	    STATIC_FUNCTION(spawn_remote_process_with_arguments_lisp_side,
	    NIL,FALSE,2,2));
    Qprocess_id = STATIC_SYMBOL("PROCESS-ID",AB_package);
    Qprocess_exists_lisp_side = STATIC_SYMBOL("PROCESS-EXISTS-LISP-SIDE",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qprocess_exists_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qprocess_exists_lisp_side,
	    STATIC_FUNCTION(process_exists_lisp_side,NIL,FALSE,1,1));
    Qremote_process_exists_lisp_side = 
	    STATIC_SYMBOL("REMOTE-PROCESS-EXISTS-LISP-SIDE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qremote_process_exists_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    Qremote_query_initiated = STATIC_SYMBOL("REMOTE-QUERY-INITIATED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qremote_process_exists_lisp_side,
	    STATIC_FUNCTION(remote_process_exists_lisp_side,NIL,FALSE,2,2));
    Qquery_status = STATIC_SYMBOL("QUERY-STATUS",AB_package);
    Qkill_process_lisp_side = STATIC_SYMBOL("KILL-PROCESS-LISP-SIDE",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qkill_process_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qkill_process_lisp_side,
	    STATIC_FUNCTION(kill_process_lisp_side,NIL,FALSE,1,1));
    Qkill_remote_process_lisp_side = 
	    STATIC_SYMBOL("KILL-REMOTE-PROCESS-LISP-SIDE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qkill_remote_process_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qremote_kill_initiated = STATIC_SYMBOL("REMOTE-KILL-INITIATED",AB_package);
    SET_SYMBOL_FUNCTION(Qkill_remote_process_lisp_side,
	    STATIC_FUNCTION(kill_remote_process_lisp_side,NIL,FALSE,2,2));
    Qkill_status = STATIC_SYMBOL("KILL-STATUS",AB_package);
    Qget_command_line_argument_from_launch_lisp_side = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-ARGUMENT-FROM-LAUNCH-LISP-SIDE",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qget_command_line_argument_from_launch_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    Quser_command_line_argument = 
	    STATIC_SYMBOL("USER-COMMAND-LINE-ARGUMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_argument_from_launch_lisp_side,
	    STATIC_FUNCTION(get_command_line_argument_from_launch_lisp_side,
	    NIL,FALSE,1,1));
    Qget_host_name_lisp_side = STATIC_SYMBOL("GET-HOST-NAME-LISP-SIDE",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qget_host_name_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qget_host_name_lisp_side,
	    STATIC_FUNCTION(get_host_name_lisp_side,NIL,FALSE,0,0));
    Qget_port_number_or_name_lisp_side = 
	    STATIC_SYMBOL("GET-PORT-NUMBER-OR-NAME-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qget_port_number_or_name_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qget_port_number_or_name_lisp_side,
	    STATIC_FUNCTION(get_port_number_or_name_lisp_side,NIL,FALSE,0,0));
    Qget_port_number_or_name_given_index_lisp_side = 
	    STATIC_SYMBOL("GET-PORT-NUMBER-OR-NAME-GIVEN-INDEX-LISP-SIDE",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qget_port_number_or_name_given_index_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qget_port_number_or_name_given_index_lisp_side,
	    STATIC_FUNCTION(get_port_number_or_name_given_index_lisp_side,
	    NIL,FALSE,1,1));
    Qget_network_addresses_lisp_side = 
	    STATIC_SYMBOL("GET-NETWORK-ADDRESSES-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qget_network_addresses_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qget_network_addresses_lisp_side,
	    STATIC_FUNCTION(get_network_addresses_lisp_side,NIL,FALSE,0,0));
    Qget_network_type_lisp_side = 
	    STATIC_SYMBOL("GET-NETWORK-TYPE-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qget_network_type_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qget_network_type_lisp_side,
	    STATIC_FUNCTION(get_network_type_lisp_side,NIL,FALSE,0,0));
    Qget_network_type_given_index_lisp_side = 
	    STATIC_SYMBOL("GET-NETWORK-TYPE-GIVEN-INDEX-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qget_network_type_given_index_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qget_network_type_given_index_lisp_side,
	    STATIC_FUNCTION(get_network_type_given_index_lisp_side,NIL,
	    FALSE,1,1));
    Qget_software_version_lisp_side = 
	    STATIC_SYMBOL("GET-SOFTWARE-VERSION-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qget_software_version_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qget_software_version_lisp_side,
	    STATIC_FUNCTION(get_software_version_lisp_side,NIL,FALSE,0,0));
    Qg2_get_build_version = STATIC_SYMBOL("G2-GET-BUILD-VERSION",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_get_build_version,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qab = STATIC_SYMBOL("AB",AB_package);
    string_constant_18 = STATIC_STRING(" ~a");
    SET_SYMBOL_FUNCTION(Qg2_get_build_version,
	    STATIC_FUNCTION(g2_get_build_version,NIL,FALSE,0,0));
    Qpatch = STATIC_SYMBOL("PATCH",AB_package);
    Qunknown_release_level = STATIC_SYMBOL("UNKNOWN-RELEASE-LEVEL",AB_package);
    Qprototype = STATIC_SYMBOL("PROTOTYPE",AB_package);
    Qalpha = STATIC_SYMBOL("ALPHA",AB_package);
    Qbeta = STATIC_SYMBOL("BETA",AB_package);
    Qreleased = STATIC_SYMBOL("RELEASED",AB_package);
    Qrevision = STATIC_SYMBOL("REVISION",AB_package);
    Qrelease_level = STATIC_SYMBOL("RELEASE-LEVEL",AB_package);
    Qpatch_number = STATIC_SYMBOL("PATCH-NUMBER",AB_package);
    Qbuild_identification = STATIC_SYMBOL("BUILD-IDENTIFICATION",AB_package);
    Qbuild_comment = STATIC_SYMBOL("BUILD-COMMENT",AB_package);
    Qenterprise = STATIC_SYMBOL("ENTERPRISE",AB_package);
    Qg2_get_version = STATIC_SYMBOL("G2-GET-VERSION",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_get_version,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_version,STATIC_FUNCTION(g2_get_version,NIL,
	    FALSE,0,0));
    Qunix_time_lisp_side = STATIC_SYMBOL("UNIX-TIME-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qunix_time_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qunix_time_lisp_side,
	    STATIC_FUNCTION(unix_time_lisp_side,NIL,FALSE,0,0));
    Qunix_time_at_start_lisp_side = 
	    STATIC_SYMBOL("UNIX-TIME-AT-START-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qunix_time_at_start_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qunix_time_at_start_lisp_side,
	    STATIC_FUNCTION(unix_time_at_start_lisp_side,NIL,FALSE,0,0));
    Qlocal_time_lisp_side = STATIC_SYMBOL("LOCAL-TIME-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qlocal_time_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qlocal_time_lisp_side,
	    STATIC_FUNCTION(local_time_lisp_side,NIL,FALSE,0,0));
    Qis_dst_used_lisp_side = STATIC_SYMBOL("IS-DST-USED-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qis_dst_used_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qis_dst_used_lisp_side,
	    STATIC_FUNCTION(is_dst_used_lisp_side,NIL,FALSE,0,0));
    Qunix_time_to_text_lisp_side = 
	    STATIC_SYMBOL("UNIX-TIME-TO-TEXT-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qunix_time_to_text_lisp_side,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qunix_time_to_text_lisp_side,
	    STATIC_FUNCTION(unix_time_to_text_lisp_side,NIL,FALSE,2,2));
    Qunix_time_to_text_y2k_lisp_side = 
	    STATIC_SYMBOL("UNIX-TIME-TO-TEXT-Y2K-LISP-SIDE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qunix_time_to_text_y2k_lisp_side,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qunix_time_to_text_y2k_lisp_side,
	    STATIC_FUNCTION(unix_time_to_text_y2k_lisp_side,NIL,FALSE,2,2));
    string_constant_19 = 
	    STATIC_STRING("Currently Windows NT platforms cannot display time values before January 1, 1970 in text form. Unix-time should be no less than 0.0. ");
    string_constant_20 = STATIC_STRING("~d/~d/~d");
    string_constant_21 = STATIC_STRING("~d/~d/0~d");
    string_constant_22 = STATIC_STRING(" ");
    string_constant_23 = STATIC_STRING("~d:");
    string_constant_25 = STATIC_STRING("~d");
    string_constant_26 = STATIC_STRING(":");
    string_constant_27 = STATIC_STRING("p.m.");
    string_constant_28 = STATIC_STRING("a.m.");
    Qg2_get_environment_variable = 
	    STATIC_SYMBOL("G2-GET-ENVIRONMENT-VARIABLE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_get_environment_variable,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    array_constant_1 = STATIC_ARRAY(list_constant_11,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    SET_SYMBOL_FUNCTION(Qg2_get_environment_variable,
	    STATIC_FUNCTION(g2_get_environment_variable,NIL,FALSE,1,1));
    Qget_process_identifier = STATIC_SYMBOL("GET-PROCESS-IDENTIFIER",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qget_process_identifier,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qget_process_identifier,
	    STATIC_FUNCTION(get_process_identifier,NIL,FALSE,0,0));
}
