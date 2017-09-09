/* utlts0.c
 * Input file:  utilities0.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "utlts0.h"


Object Managed_float_unique_marker = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Strange_cons, Qstrange_cons);

DEFINE_VARIABLE_WITH_SYMBOL(Debugging_consing, Qdebugging_consing);

Object Cons_pool_conses_to_make_at_a_time = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(All_cons_pools, Qall_cons_pools);

DEFINE_VARIABLE_WITH_SYMBOL(Available_gensym_conses, Qavailable_gensym_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_gensym_conses_tail, Qavailable_gensym_conses_tail);

Object Available_gensym_conses_vector = UNBOUND;

Object Available_gensym_conses_tail_vector = UNBOUND;

Object Gensym_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_cons_counter, Qgensym_cons_counter);

/* OUTSTANDING-GENSYM-CONSES */
Object outstanding_gensym_conses()
{
    Object temp;

    x_note_fn_call(22,0);
    temp = FIXNUM_MINUS(Gensym_cons_counter,length(Available_gensym_conses));
    return VALUES_1(temp);
}

/* GENSYM-CONS-MEMORY-USAGE */
Object gensym_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(22,1);
    temp = FIXNUM_TIMES(Gensym_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-GENSYM-CONS-POOL */
Object replenish_gensym_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(22,2);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qgensym_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_gensym_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_gensym_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_gensym_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_gensym_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_gensym_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Gensym_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qab_gensym;          /* gensym */

/* GENSYM-CONS-1 */
Object gensym_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(22,3);
    new_cons = ISVREF(Available_gensym_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_gensym_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_gensym_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_gensym_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_gensym_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-GENSYM-LIST-POOL */
Object replenish_gensym_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(22,4);
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
    if (ISVREF(Available_gensym_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_gensym_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_gensym_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_gensym_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_gensym_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qgensym_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-GENSYM-LIST-1 */
Object make_gensym_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(22,5);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_gensym_conses_vector,
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
	replenish_gensym_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_gensym_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_gensym_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_gensym_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_gensym_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_gensym_conses_tail_vector;
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

/* GENSYM-LIST-2 */
Object gensym_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(22,6);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_gensym_conses_vector,IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_gensym_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_gensym_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_gensym_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_gensym_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_gensym_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_gensym_conses_tail_vector;
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

/* GENSYM-LIST-3 */
Object gensym_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(22,7);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_gensym_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_gensym_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_gensym_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_gensym_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_gensym_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_gensym_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_gensym_conses_tail_vector;
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

/* GENSYM-LIST-4 */
Object gensym_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(22,8);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_gensym_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_gensym_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_gensym_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_gensym_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_gensym_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_gensym_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_gensym_conses_tail_vector;
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

/* GENSYM-LIST-TRACE-HOOK */
Object gensym_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(22,9);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-GENSYM-CONSES-1 */
Object copy_tree_using_gensym_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(22,10);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_gensym_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_gensym_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_gensym_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_gensym_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_gensym_cons_pool();
	temp_1 = copy_tree_using_gensym_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_gensym_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_gensym_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_gensym_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_gensym_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_gensym_cons_pool();
	temp_1 = copy_tree_using_gensym_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
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

/* COPY-LIST-USING-GENSYM-CONSES-1 */
Object copy_list_using_gensym_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(22,11);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_gensym_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_gensym_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_gensym_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_gensym_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_gensym_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_gensym_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_gensym_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_gensym_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_gensym_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_gensym_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
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

/* RECLAIM-GENSYM-CONS-1 */
Object reclaim_gensym_cons_1(gensym_cons)
    Object gensym_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(22,12);
    inline_note_reclaim_cons(gensym_cons,Qab_gensym);
    if (ISVREF(Available_gensym_conses_tail_vector,
		IFIX(Current_thread_index))) {
	temp = ISVREF(Available_gensym_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = gensym_cons;
	temp = Available_gensym_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = gensym_cons;
    }
    else {
	temp = Available_gensym_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = gensym_cons;
	temp = Available_gensym_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = gensym_cons;
    }
    M_CDR(gensym_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-GENSYM-LIST-1 */
Object reclaim_gensym_list_1(gensym_list)
    Object gensym_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(22,13);
    if (gensym_list) {
	last_1 = gensym_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qab_gensym);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qab_gensym);
	if (ISVREF(Available_gensym_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_gensym_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = gensym_list;
	    temp = Available_gensym_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_gensym_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = gensym_list;
	    temp = Available_gensym_conses_tail_vector;
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

/* RECLAIM-GENSYM-LIST*-1 */
Object reclaim_gensym_list_star_1(gensym_list)
    Object gensym_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(22,14);
    if (CONSP(gensym_list)) {
	temp = last(gensym_list,_);
	M_CDR(temp) = Nil;
	if (gensym_list) {
	    last_1 = gensym_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qab_gensym);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qab_gensym);
	    if (ISVREF(Available_gensym_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_gensym_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = gensym_list;
		temp = Available_gensym_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_gensym_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = gensym_list;
		temp = Available_gensym_conses_tail_vector;
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

/* RECLAIM-GENSYM-TREE-1 */
Object reclaim_gensym_tree_1(tree)
    Object tree;
{
    Object e, e2, gensym_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(22,15);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_gensym_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		gensym_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(gensym_cons,Qab_gensym);
		if (EQ(gensym_cons,e))
		    goto end_1;
		else if ( !TRUEP(gensym_cons))
		    goto end_1;
		else
		    gensym_cons = CDR(gensym_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_gensym_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_gensym_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_gensym_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_gensym_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_gensym_conses_tail_vector;
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

/* DELETE-GENSYM-ELEMENT-1 */
Object delete_gensym_element_1(element,gensym_list)
    Object element, gensym_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(22,16);
    if (gensym_list) {
	if (EQ(element,M_CAR(gensym_list))) {
	    temp = CDR(gensym_list);
	    inline_note_reclaim_cons(gensym_list,Qab_gensym);
	    if (ISVREF(Available_gensym_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_gensym_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = gensym_list;
		temp_1 = Available_gensym_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = gensym_list;
	    }
	    else {
		temp_1 = Available_gensym_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = gensym_list;
		temp_1 = Available_gensym_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = gensym_list;
	    }
	    M_CDR(gensym_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = gensym_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qab_gensym);
		if (ISVREF(Available_gensym_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_gensym_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_gensym_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_gensym_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_gensym_conses_tail_vector;
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
	    temp = gensym_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-GENSYM-CONS-1 */
Object delete_gensym_cons_1(gensym_cons,gensym_list)
    Object gensym_cons, gensym_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(22,17);
    if (EQ(gensym_cons,gensym_list))
	temp = CDR(gensym_list);
    else {
	l_trailer_qm = Nil;
	l = gensym_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,gensym_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = gensym_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_gensym_cons_1(gensym_cons);
    return VALUES_1(temp);
}

/* GENSYM-CONS-FUNCTION */
Object gensym_cons_function(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(22,18);
    new_cons = ISVREF(Available_gensym_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_gensym_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_gensym_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_gensym_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_gensym_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
    return VALUES_1(gensymed_symbol);
}

/* COPY-TREE-USING-GENSYM-CONSES-FUNCTION */
Object copy_tree_using_gensym_conses_function(tree_qm)
    Object tree_qm;
{
    Object temp;

    x_note_fn_call(22,19);
    temp = copy_tree_using_gensym_conses_1(tree_qm);
    return VALUES_1(temp);
}

/* RECLAIM-GENSYM-LIST-FUNCTION */
Object reclaim_gensym_list_function(list_1)
    Object list_1;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(22,20);
    if (list_1) {
	last_1 = list_1;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qab_gensym);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qab_gensym);
	if (ISVREF(Available_gensym_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_gensym_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = list_1;
	    temp = Available_gensym_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_gensym_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = list_1;
	    temp = Available_gensym_conses_tail_vector;
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

/* RECLAIM-GENSYM-TREE-FUNCTION */
Object reclaim_gensym_tree_function(tree)
    Object tree;
{
    Object temp;

    x_note_fn_call(22,21);
    temp = reclaim_gensym_tree_1(tree);
    return VALUES_1(temp);
}

/* REVERSE-LIST-USING-GENSYM-CONSES */
Object reverse_list_using_gensym_conses(list_1)
    Object list_1;
{
    Object reversed_list, l, temp;

    x_note_fn_call(22,22);
    reversed_list = Nil;
    l = list_1;
  next_loop:
    if ( !TRUEP(l))
	goto end_loop;
    reversed_list = gensym_cons_1(CAR(l),reversed_list);
    l = M_CDR(l);
    goto next_loop;
  end_loop:
    temp = reversed_list;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* RECLAIM-GENSYM-LIST-IF-LIST */
Object reclaim_gensym_list_if_list(atom_or_gensym_list)
    Object atom_or_gensym_list;
{
    x_note_fn_call(22,23);
    if (CONSP(atom_or_gensym_list))
	reclaim_gensym_list_1(atom_or_gensym_list);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Scope_conses, Qscope_conses);

/* SCOPE-CONS */
Object scope_cons(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object cons_holder, cons_to_give, next_cons_holder_qm;

    x_note_fn_call(22,24);
    cons_holder = Scope_conses;
    cons_to_give = M_CAR(cons_holder);
    next_cons_holder_qm = M_CDR(cons_holder);
    if ( !TRUEP(next_cons_holder_qm)) {
	next_cons_holder_qm = gensym_cons_1(gensym_cons_1(Nil,Nil),Nil);
	M_CDR(cons_holder) = next_cons_holder_qm;
    }
    Scope_conses = next_cons_holder_qm;
    M_CAR(cons_to_give) = car_1;
    M_CDR(cons_to_give) = cdr_1;
    return VALUES_1(cons_to_give);
}

/* MAKE-SCOPE-LIST */
Object make_scope_list(count_1)
    Object count_1;
{
    Object next_cons, ab_loop_iter_flag_, temp;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(22,25);
    if (IFIX(count_1) > (SI_Long)0L) {
	ab_loop_repeat_ = IFIX(count_1);
	next_cons = scope_cons(Nil,Nil);
	ab_loop_iter_flag_ = T;
      next_loop:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	if ( !TRUEP(ab_loop_iter_flag_))
	    next_cons = scope_cons(Nil,next_cons);
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:
	temp = next_cons;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* COPY-LIST-USING-SCOPE-CONSES */
Object copy_list_using_scope_conses(list_to_copy)
    Object list_to_copy;
{
    Object element, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object temp;

    x_note_fn_call(22,26);
    element = Nil;
    ab_loop_list_ = list_to_copy;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = scope_cons(element,Nil);
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
    return VALUES_1(temp);
}

/* SORT-ARRAY */
Object sort_array(array,less_than_predicate,key)
    Object array, less_than_predicate, key;
{
    Object lesser_elt, greater_elt, temp;
    SI_Long end_point, lesser_index, ab_loop_bind_, greater_index;
    char temp_1;

    x_note_fn_call(22,27);
    end_point = IFIX(FIXNUM_SUB1(length(array)));
  next_loop:
    if (end_point < (SI_Long)1L)
	goto end_loop;
    lesser_index = (SI_Long)0L;
    ab_loop_bind_ = end_point;
    lesser_elt = Nil;
    greater_index = (SI_Long)0L;
    greater_elt = Nil;
  next_loop_1:
    if (lesser_index >= ab_loop_bind_)
	goto end_loop_1;
    lesser_elt = aref1(array,FIX(lesser_index));
    greater_index = lesser_index + (SI_Long)1L;
    greater_elt = aref1(array,FIX(greater_index));
    if (key) {
	temp = FUNCALL_1(key,greater_elt);
	temp_1 = TRUEP(FUNCALL_2(less_than_predicate,temp,FUNCALL_1(key,
		lesser_elt)));
    }
    else
	temp_1 = TRUEP(FUNCALL_2(less_than_predicate,greater_elt,lesser_elt));
    if (temp_1) {
	set_aref1(array,FIX(greater_index),lesser_elt);
	set_aref1(array,FIX(lesser_index),greater_elt);
    }
    lesser_index = lesser_index + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    end_point = end_point - (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(array);
}

/* SORT-LIST */
Object sort_list(list_1,predicate,key)
    Object list_1, predicate, key;
{
    x_note_fn_call(22,28);
    return sort_list_1(list_1,length(list_1),predicate,key);
}

/* SORT-LIST-1 */
Object sort_list_1(l,n_init,predicate,key)
    Object l, n_init, predicate, key;
{
    Object l_tail, l2, l1, temp;
    SI_Long n_1, half_n;
    char temp_1;

    x_note_fn_call(22,29);
    n_1 = IFIX(n_init);
    if (n_1 > (SI_Long)1L) {
	half_n = n_1 >>  -  - (SI_Long)1L;
	l_tail = nthcdr(FIX(half_n - (SI_Long)1L),l);
	l2 = sort_list_1(CDR(l_tail),FIX(n_1 - half_n),predicate,key);
	M_CDR(l_tail) = Nil;
	l1 = sort_list_1(l,FIX(half_n),predicate,key);
	l = Nil;
      next_loop:
	if (key) {
	    temp = FUNCALL_1(key,CAR(l2));
	    temp_1 =  !TRUEP(FUNCALL_2(predicate,temp,FUNCALL_1(key,CAR(l1))));
	}
	else
	    temp_1 =  !TRUEP(FUNCALL_2(predicate,CAR(l2),CAR(l1)));
	if (temp_1) {
	    if ( !TRUEP(l)) {
		l = l1;
		l_tail = l;
	    }
	    else
		l_tail = M_CDR(l_tail) = l1;
	    l1 = CDR(l1);
	    if ( !TRUEP(l1))
		temp_1 = TRUEP(M_CDR(l_tail) = l2);
	    else
		temp_1 = TRUEP(Nil);
	}
	else {
	    if ( !TRUEP(l)) {
		l = l2;
		l_tail = l;
	    }
	    else
		l_tail = M_CDR(l_tail) = l2;
	    l2 = CDR(l2);
	    if ( !TRUEP(l2))
		temp_1 = TRUEP(M_CDR(l_tail) = l1);
	    else
		temp_1 = TRUEP(Nil);
	}
	if (temp_1)
	    goto end_loop;
	goto next_loop;
      end_loop:;
    }
    return VALUES_1(l);
}

/* DELETE-DUPLICATES-FROM-LIST */
Object delete_duplicates_from_list varargs_1(int, n)
{
    Object list_1;
    Object cons_reclaimer_qm, test_function_qm, l, element, m_trailer, m;
    Object cdr_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(22,30);
    INIT_ARGS_nonrelocating();
    list_1 = REQUIRED_ARG_nonrelocating();
    cons_reclaimer_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    test_function_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    l = list_1;
    element = Nil;
  next_loop:
    if ( !TRUEP(l))
	goto end_loop;
    element = CAR(l);
    m_trailer = l;
    m = Nil;
  next_loop_1:
    m = CDR(m_trailer);
    if ( !TRUEP(m))
	goto end_loop_1;
    if (test_function_qm ? TRUEP(FUNCALL_2(test_function_qm,CAR(m),
	    element)) : EQ(CAR(m),element)) {
	cdr_new_value = CDR(m);
	M_CDR(m_trailer) = cdr_new_value;
	if (cons_reclaimer_qm)
	    FUNCALL_1(cons_reclaimer_qm,m);
    }
    else
	m_trailer = m;
    goto next_loop_1;
  end_loop_1:;
    l = M_CDR(l);
    goto next_loop;
  end_loop:
    return VALUES_1(list_1);
    return VALUES_1(Qnil);
}

/* DELETE-ITEM-FROM-LIST-AND-RECLAIM-CONS-CELLS */
Object delete_item_from_list_and_reclaim_cons_cells(list_1,item,
	    cons_reclaimer,retain_first_value_qm)
    Object list_1, item, cons_reclaimer, retain_first_value_qm;
{
    Object result_list, first_value_retained_qm, l, m_trailer, m;
    Object cdr_new_value;

    x_note_fn_call(22,31);
    result_list = Nil;
    first_value_retained_qm = Nil;
    if (EQ(item,CAR(list_1))) {
	if (retain_first_value_qm) {
	    first_value_retained_qm = T;
	    result_list = list_1;
	}
	else {
	    result_list = CDR(list_1);
	    FUNCALL_1(cons_reclaimer,list_1);
	}
    }
    else
	result_list = list_1;
    l = first_value_retained_qm ? CDR(result_list) : result_list;
  next_loop:
    if ( !TRUEP(l))
	goto end_loop;
    m_trailer = l;
    m = Nil;
  next_loop_1:
    m = CDR(m_trailer);
    if ( !TRUEP(m))
	goto end_loop_1;
    if (EQ(CAR(m),item)) {
	if (retain_first_value_qm &&  !TRUEP(first_value_retained_qm))
	    first_value_retained_qm = T;
	else {
	    cdr_new_value = CDR(m);
	    M_CDR(m_trailer) = cdr_new_value;
	    FUNCALL_1(cons_reclaimer,m);
	}
    }
    else
	m_trailer = m;
    goto next_loop_1;
  end_loop_1:;
    l = M_CDR(l);
    goto next_loop;
  end_loop:;
    return VALUES_1(result_list);
}

/* NREVERSE-CANONICALLY */
Object nreverse_canonically(list_1)
    Object list_1;
{
    Object reversed_list, next_cons;

    x_note_fn_call(22,32);
    reversed_list = Nil;
    next_cons = Nil;
  next_loop:
    if ( !TRUEP(list_1))
	goto end_loop;
    next_cons = CDR(list_1);
    M_CDR(list_1) = reversed_list;
    reversed_list = list_1;
    list_1 = next_cons;
    goto next_loop;
  end_loop:
    return VALUES_1(reversed_list);
    return VALUES_1(Qnil);
}

/* LIST-PREFIX-P */
Object list_prefix_p(list_a,list_b)
    Object list_a, list_b;
{
    Object element, ab_loop_list_, temp, list_b_old_value, temp_1;
    char temp_2;

    x_note_fn_call(22,33);
    element = Nil;
    ab_loop_list_ = list_a;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (list_b) {
	temp = element;
	list_b_old_value = list_b;
	temp_1 = FIRST(list_b_old_value);
	list_b = REST(list_b_old_value);
	temp_2 = EQ(temp,temp_1);
    }
    else
	temp_2 = TRUEP(Nil);
    if ( !temp_2)
	return VALUES_1(Nil);
    goto next_loop;
  end_loop:
    return VALUES_1(T);
    return VALUES_1(Qnil);
}

/* ALLOCATE-INITIAL-MANAGED-SIMPLE-VECTOR-POOL-ARRAY */
Object allocate_initial_managed_simple_vector_pool_array(initial_element)
    Object initial_element;
{
    x_note_fn_call(22,34);
    return make_array(3,FIXNUM_ADD1(Maximum_managed_simple_vector_size),
	    Kinitial_element,initial_element);
}

DEFINE_VARIABLE_WITH_SYMBOL(Vector_of_simple_vector_pools, Qvector_of_simple_vector_pools);

DEFINE_VARIABLE_WITH_SYMBOL(Simple_vector_pool_counts, Qsimple_vector_pool_counts);

DEFINE_VARIABLE_WITH_SYMBOL(Vector_of_oversized_simple_vector_pools, Qvector_of_oversized_simple_vector_pools);

DEFINE_VARIABLE_WITH_SYMBOL(Oversized_simple_vector_pool_counts, Qoversized_simple_vector_pool_counts);

DEFINE_VARIABLE_WITH_SYMBOL(Created_simple_vector_pool_vectors, Qcreated_simple_vector_pool_vectors);

/* OUTSTANDING-SIMPLE-VECTOR-POOL-VECTORS */
Object outstanding_simple_vector_pool_vectors()
{
    Object vector_1;
    SI_Long vectors_in_pools, index_1;

    x_note_fn_call(22,35);
    vectors_in_pools = (SI_Long)0L;
    index_1 = (SI_Long)1L;
  next_loop:
    if (index_1 > IFIX(Maximum_managed_simple_vector_size))
	goto end_loop;
    vector_1 = ISVREF(Vector_of_simple_vector_pools,index_1);
  next_loop_1:
    if ( !TRUEP(vector_1))
	goto end_loop_1;
    vectors_in_pools = vectors_in_pools + (SI_Long)1L;
    vector_1 = ISVREF(vector_1,(SI_Long)0L);
    goto next_loop_1;
  end_loop_1:;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    index_1 = (SI_Long)1L;
  next_loop_2:
    if (index_1 > IFIX(Maximum_managed_simple_vector_size))
	goto end_loop_2;
    vector_1 = ISVREF(Vector_of_oversized_simple_vector_pools,index_1);
  next_loop_3:
    if ( !TRUEP(vector_1))
	goto end_loop_3;
    vectors_in_pools = vectors_in_pools + (SI_Long)1L;
    vector_1 = ISVREF(vector_1,(SI_Long)0L);
    goto next_loop_3;
  end_loop_3:;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop_2;
  end_loop_2:;
    return VALUES_1(FIX(IFIX(Created_simple_vector_pool_vectors) - 
	    vectors_in_pools));
}

DEFINE_VARIABLE_WITH_SYMBOL(Simple_vector_pool_memory_usage, Qsimple_vector_pool_memory_usage);

/* SVP-MEMORY-USAGE */
Object svp_memory_usage()
{
    x_note_fn_call(22,36);
    return VALUES_1(Simple_vector_pool_memory_usage);
}

Object Replenished_simple_vector_size_limit = UNBOUND;

Object Replenished_simple_vectors_to_make_at_a_time = UNBOUND;

/* ALLOCATE-MANAGED-SIMPLE-VECTOR */
Object allocate_managed_simple_vector(length_init)
    Object length_init;
{
    Object local_vector_of_simple_vector_pools;
    Object local_simple_vector_pool_counts, available_vector_qm, temp, array;
    Object svref_arg_2, a, new_vector, vectors_made_so_far, ab_loopvar_;
    Object ab_loopvar__1, temp_1;
    SI_Long length_1, index_1, ab_loop_repeat_;
    XDeclare_area(1);

    x_note_fn_call(22,37);
    length_1 = IFIX(length_init);
    local_vector_of_simple_vector_pools = Vector_of_simple_vector_pools;
    local_simple_vector_pool_counts = Simple_vector_pool_counts;
    index_1 = length_1;
    available_vector_qm = Nil;
    if (length_1 > IFIX(Maximum_managed_simple_vector_size)) {
	if ((length_1 & (SI_Long)1023L) != (SI_Long)0L)
	    length_1 = (length_1 & (SI_Long)-1024L) + (SI_Long)1024L;
	local_vector_of_simple_vector_pools = 
		Vector_of_oversized_simple_vector_pools;
	local_simple_vector_pool_counts = Oversized_simple_vector_pool_counts;
	index_1 = length_1 >>  -  - (SI_Long)10L;
    }
    available_vector_qm = ISVREF(local_vector_of_simple_vector_pools,index_1);
    if (available_vector_qm) {
	temp = M_CDR(available_vector_qm);
	ISVREF(local_vector_of_simple_vector_pools,index_1) = temp;
	array = M_CAR(available_vector_qm);
	inline_note_reclaim_cons(available_vector_qm,Qab_gensym);
	if (ISVREF(Available_gensym_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_gensym_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = available_vector_qm;
	    temp = Available_gensym_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = available_vector_qm;
	}
	else {
	    temp = Available_gensym_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = available_vector_qm;
	    temp = Available_gensym_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = available_vector_qm;
	}
	M_CDR(available_vector_qm) = Nil;
	a = array;
    }
    else
	a = Nil;
    if ( !TRUEP(a)) {
	if (length_1 <= IFIX(Replenished_simple_vector_size_limit)) {
	    if (PUSH_AREA(Dynamic_area,0)) {
		ab_loop_repeat_ = 
			IFIX(FIXNUM_SUB1(Replenished_simple_vectors_to_make_at_a_time));
		new_vector = Nil;
		vectors_made_so_far = Nil;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
	      next_loop:
		if ( !((SI_Long)0L < ab_loop_repeat_))
		    goto end_loop;
		ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		new_vector = make_array(1,FIX(length_1));
		ab_loopvar__1 = gensym_cons_1(new_vector,Nil);
		if (ab_loopvar_)
		    M_CDR(ab_loopvar_) = ab_loopvar__1;
		else
		    vectors_made_so_far = ab_loopvar__1;
		ab_loopvar_ = ab_loopvar__1;
		goto next_loop;
	      end_loop:
		ISVREF(local_vector_of_simple_vector_pools,index_1) = 
			vectors_made_so_far;
		atomic_incff_symval(Qcreated_simple_vector_pool_vectors,
			Replenished_simple_vectors_to_make_at_a_time);
		atomic_incff_svslot(local_simple_vector_pool_counts,
			FIX(index_1),
			Replenished_simple_vectors_to_make_at_a_time);
		temp_1 = Replenished_simple_vectors_to_make_at_a_time;
		atomic_incff_symval(Qsimple_vector_pool_memory_usage,
			FIXNUM_TIMES(temp_1,
			bytes_per_simple_vector(FIX(length_1))));
		a = make_array(1,FIX(length_1));
	    }
	    POP_AREA(0);
	}
	else {
	    atomic_incff_symval(Qcreated_simple_vector_pool_vectors,
		    FIX((SI_Long)1L));
	    atomic_incff_svslot(local_simple_vector_pool_counts,
		    FIX(index_1),FIX((SI_Long)1L));
	    atomic_incff_symval(Qsimple_vector_pool_memory_usage,
		    bytes_per_simple_vector(FIX(length_1)));
	    if (PUSH_AREA(Dynamic_area,0))
		a = make_array(1,FIX(length_1));
	    POP_AREA(0);
	}
    }
    inline_note_allocate_cons(a,Nil);
    return VALUES_1(a);
}

/* ALLOCATE-MANAGED-SIMPLE-VECTOR-FOR-ARRAY */
Object allocate_managed_simple_vector_for_array(length_1)
    Object length_1;
{
    Object temp;

    x_note_fn_call(22,38);
    temp = allocate_managed_simple_vector(length_1);
    return VALUES_1(temp);
}

/* ALLOCATE-MANAGED-SIMPLE-VECTOR-FOR-FLOAT-ARRAY */
Object allocate_managed_simple_vector_for_float_array(length_1)
    Object length_1;
{
    Object temp;

    x_note_fn_call(22,39);
    temp = allocate_managed_simple_vector(length_1);
    return VALUES_1(temp);
}

/* ALLOCATE-MANAGED-SIMPLE-VECTOR-FOR-SKIP-LIST */
Object allocate_managed_simple_vector_for_skip_list(length_1)
    Object length_1;
{
    Object temp;

    x_note_fn_call(22,40);
    temp = allocate_managed_simple_vector(length_1);
    return VALUES_1(temp);
}

/* RECLAIM-MANAGED-SIMPLE-VECTOR */
Object reclaim_managed_simple_vector(managed_simple_vector)
    Object managed_simple_vector;
{
    Object svref_arg_1, new_cons, temp, svref_arg_2, svref_new_value;
    Object gensymed_symbol;
    SI_Long length_1, index_1;

    x_note_fn_call(22,41);
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_simple_vector));
    inline_note_reclaim_cons(managed_simple_vector,Nil);
    barrier();
    if (length_1 > IFIX(Maximum_managed_simple_vector_size)) {
	index_1 = length_1 >>  -  - (SI_Long)10L;
	svref_arg_1 = Vector_of_oversized_simple_vector_pools;
	new_cons = ISVREF(Available_gensym_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_gensym_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_gensym_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_gensym_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_gensym_cons_pool();
	M_CAR(gensymed_symbol) = managed_simple_vector;
	temp = ISVREF(Vector_of_oversized_simple_vector_pools,index_1);
	M_CDR(gensymed_symbol) = temp;
	inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
	ISVREF(svref_arg_1,index_1) = gensymed_symbol;
    }
    else {
	svref_arg_1 = Vector_of_simple_vector_pools;
	new_cons = ISVREF(Available_gensym_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_gensym_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_gensym_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_gensym_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_gensym_cons_pool();
	M_CAR(gensymed_symbol) = managed_simple_vector;
	temp = ISVREF(Vector_of_simple_vector_pools,length_1);
	M_CDR(gensymed_symbol) = temp;
	inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
	ISVREF(svref_arg_1,length_1) = gensymed_symbol;
    }
    return VALUES_1(Nil);
}

/* RECLAIM-MANAGED-SIMPLE-VECTOR-FOR-ARRAY */
Object reclaim_managed_simple_vector_for_array(managed_simple_vector)
    Object managed_simple_vector;
{
    Object temp;

    x_note_fn_call(22,42);
    temp = reclaim_managed_simple_vector(managed_simple_vector);
    return VALUES_1(temp);
}

/* RECLAIM-MANAGED-SIMPLE-VECTOR-FOR-FLOAT-ARRAY */
Object reclaim_managed_simple_vector_for_float_array(managed_simple_vector)
    Object managed_simple_vector;
{
    Object temp;

    x_note_fn_call(22,43);
    temp = reclaim_managed_simple_vector(managed_simple_vector);
    return VALUES_1(temp);
}

/* RECLAIM-MANAGED-SIMPLE-VECTOR-FOR-SKIP-LIST */
Object reclaim_managed_simple_vector_for_skip_list(managed_simple_vector)
    Object managed_simple_vector;
{
    Object temp;

    x_note_fn_call(22,44);
    temp = reclaim_managed_simple_vector(managed_simple_vector);
    return VALUES_1(temp);
}

/* FILL-MANAGED-SIMPLE-VECTOR */
Object fill_managed_simple_vector(managed_simple_vector,value,start_init,
	    end_init)
    Object managed_simple_vector, value, start_init, end_init;
{
    SI_Long start, end_1, i, ab_loop_bind_;

    x_note_fn_call(22,45);
    start = IFIX(start_init);
    end_1 = IFIX(end_init);
    i = start;
    ab_loop_bind_ = end_1;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    ISVREF(managed_simple_vector,i) = value;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    barrier();
    return VALUES_1(Nil);
}

/* MAKE-PARTIAL-BUFFER-INFO */
Object make_partial_buffer_info(max_size,grouping_factor,pool_offset,
	    group_shift)
    Object max_size, grouping_factor, pool_offset, group_shift;
{
    Object array;

    x_note_fn_call(22,46);
    array = make_array(1,FIX((SI_Long)4L));
    SVREF(array,FIX((SI_Long)0L)) = max_size;
    SVREF(array,FIX((SI_Long)1L)) = grouping_factor;
    SVREF(array,FIX((SI_Long)2L)) = pool_offset;
    SVREF(array,FIX((SI_Long)3L)) = group_shift;
    return VALUES_1(array);
}

Object Managed_array_allocation_schemes = UNBOUND;

/* BUFFER-SIZE-FOR-PARTIAL-BUFFER */
Object buffer_size_for_partial_buffer(needed_size_init,allocation_schemes)
    Object needed_size_init, allocation_schemes;
{
    Object allocation_scheme, ab_loop_list_, temp;
    SI_Long needed_size;

    x_note_fn_call(22,47);
    needed_size = IFIX(needed_size_init);
    if ((SI_Long)0L == needed_size)
	needed_size = (SI_Long)1L;
    allocation_scheme = Nil;
    ab_loop_list_ = allocation_schemes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    allocation_scheme = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (needed_size <= IFIX(ISVREF(allocation_scheme,(SI_Long)0L))) {
	temp = FIX((needed_size - (SI_Long)1L | 
		IFIX(FIXNUM_SUB1(ISVREF(allocation_scheme,(SI_Long)1L)))) 
		+ (SI_Long)1L);
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = FIX(needed_size);
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* BUFFER-SIZE-AND-POOL-FOR-PARTIAL-BUFFER */
Object buffer_size_and_pool_for_partial_buffer(needed_size,allocation_schemes)
    Object needed_size, allocation_schemes;
{
    Object allocation_scheme, ab_loop_list_, temp, temp_1;
    SI_Long maximum_scheme_size;

    x_note_fn_call(22,48);
    if ((SI_Long)0L == IFIX(needed_size))
	needed_size = FIX((SI_Long)1L);
    allocation_scheme = Nil;
    ab_loop_list_ = allocation_schemes;
    maximum_scheme_size = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    allocation_scheme = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    maximum_scheme_size = IFIX(ISVREF(allocation_scheme,(SI_Long)0L));
    if (IFIX(needed_size) <= maximum_scheme_size) {
	temp = FIXNUM_ADD1(FIXNUM_LOGIOR(FIXNUM_SUB1(needed_size),
		FIXNUM_SUB1(ISVREF(allocation_scheme,(SI_Long)1L))));
	temp_1 = FIX(IFIX(ISVREF(allocation_scheme,(SI_Long)2L)) + 
		(IFIX(FIXNUM_SUB1(needed_size)) >> 
		IFIX(FIXNUM_NEGATE(FIXNUM_NEGATE(ISVREF(allocation_scheme,
		(SI_Long)3L))))));
	return VALUES_2(temp,temp_1);
    }
    goto next_loop;
  end_loop:
    return VALUES_2(needed_size,FIX((SI_Long)0L));
    return VALUES_1(Qnil);
}

/* PARTIAL-BUFFER-POOL-INDEX-GIVEN-LENGTH */
Object partial_buffer_pool_index_given_length(vector_length_init,
	    array_allocation_schemes)
    Object vector_length_init, array_allocation_schemes;
{
    Object scheme, ab_loop_list_, temp;
    SI_Long vector_length, maximum_scheme_size;

    x_note_fn_call(22,49);
    vector_length = IFIX(vector_length_init);
    scheme = Nil;
    ab_loop_list_ = array_allocation_schemes;
    maximum_scheme_size = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    scheme = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    maximum_scheme_size = IFIX(ISVREF(scheme,(SI_Long)0L));
    if (vector_length <= maximum_scheme_size) {
	temp = FIX(IFIX(ISVREF(scheme,(SI_Long)2L)) + (vector_length - 
		(SI_Long)1L >> 
		IFIX(FIXNUM_NEGATE(FIXNUM_NEGATE(ISVREF(scheme,
		(SI_Long)3L))))));
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = FIX((SI_Long)0L);
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* GENSYM-LIST-MAXIMUM-BUFFER-SIZES */
Object gensym_list_maximum_buffer_sizes(allocation_schemes)
    Object allocation_schemes;
{
    Object maximum_sizes, scheme, ab_loop_list_, temp;
    SI_Long size_so_far, scheme_size, grouping_factor, next_size;

    x_note_fn_call(22,50);
    size_so_far = (SI_Long)0L;
    maximum_sizes = gensym_cons_1(FIX((SI_Long)0L),Nil);
    scheme = Nil;
    ab_loop_list_ = allocation_schemes;
    scheme_size = (SI_Long)0L;
    grouping_factor = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    scheme = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    scheme_size = IFIX(ISVREF(scheme,(SI_Long)0L));
    grouping_factor = IFIX(ISVREF(scheme,(SI_Long)1L));
    next_size = (SI_Long)0L;
  next_loop_1:
    next_size = size_so_far + grouping_factor;
    if ( !(next_size <= scheme_size))
	goto end_loop_1;
    size_so_far = next_size;
    maximum_sizes = gensym_cons_1(FIX(size_so_far),maximum_sizes);
    goto next_loop_1;
  end_loop_1:;
    goto next_loop;
  end_loop:;
    temp = nreverse(maximum_sizes);
    return VALUES_1(temp);
}

Object Managed_array_unique_marker = UNBOUND;

Object Maximum_managed_array_size = UNBOUND;

Object Maximum_in_place_array_size = UNBOUND;

/* ALLOCATE-MANAGED-ARRAY */
Object allocate_managed_array varargs_1(int, n)
{
    Object length_init;
    Object dont_initialize, make_exactly, spine_vector, svref_new_value;
    SI_Long length_1, temp, full_size_buffers, size_of_partial_buffer;
    SI_Long total_buffers, full_buffer_index, ab_loop_bind_, svref_arg_2;
    Declare_varargs_nonrelocating;

    x_note_fn_call(22,51);
    INIT_ARGS_nonrelocating();
    length_init = REQUIRED_ARG_nonrelocating();
    length_1 = IFIX(length_init);
    dont_initialize = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    make_exactly = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    spine_vector = Nil;
    if (length_1 <= IFIX(Maximum_in_place_array_size))
	spine_vector = 
		allocate_managed_simple_vector_for_array(make_exactly ? 
		FIX(length_1 + IFIX(Managed_array_index_offset)) : 
		buffer_size_for_partial_buffer(FIX(length_1 + 
		IFIX(Managed_array_index_offset)),
		Managed_array_allocation_schemes));
    else {
	temp = length_1 / IFIX(Maximum_managed_array_buffer_size);
	full_size_buffers = temp;
	temp = length_1 % IFIX(Maximum_managed_array_buffer_size);
	size_of_partial_buffer = temp;
	total_buffers = size_of_partial_buffer > (SI_Long)0L ? 
		full_size_buffers + (SI_Long)1L : full_size_buffers;
	spine_vector = 
		allocate_managed_simple_vector_for_array(make_exactly ? 
		FIX(total_buffers + IFIX(Managed_array_index_offset)) : 
		buffer_size_for_partial_buffer(FIX(total_buffers + 
		IFIX(Managed_array_index_offset)),
		Managed_array_allocation_schemes));
	full_buffer_index = (SI_Long)0L;
	ab_loop_bind_ = full_size_buffers;
      next_loop:
	if (full_buffer_index >= ab_loop_bind_)
	    goto end_loop;
	svref_arg_2 = full_buffer_index + (SI_Long)2L;
	svref_new_value = 
		allocate_managed_simple_vector_for_array(Maximum_managed_array_buffer_size);
	ISVREF(spine_vector,svref_arg_2) = svref_new_value;
	full_buffer_index = full_buffer_index + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	if (size_of_partial_buffer > (SI_Long)0L) {
	    svref_arg_2 = total_buffers - (SI_Long)1L + (SI_Long)2L;
	    svref_new_value = 
		    allocate_managed_simple_vector_for_array(make_exactly ?
		     FIX(size_of_partial_buffer) : 
		    buffer_size_for_partial_buffer(FIX(size_of_partial_buffer),
		    Managed_array_allocation_schemes));
	    ISVREF(spine_vector,svref_arg_2) = svref_new_value;
	}
    }
    svref_new_value = Managed_array_unique_marker;
    SVREF(spine_vector,FIX((SI_Long)0L)) = svref_new_value;
    ISVREF(spine_vector,(SI_Long)1L) = FIX(length_1);
    if ( !TRUEP(dont_initialize))
	fill_managed_array(spine_vector,Nil);
    return VALUES_1(spine_vector);
}

/* RECLAIM-MANAGED-ARRAY */
Object reclaim_managed_array(managed_array)
    Object managed_array;
{
    Object gensymed_symbol, gensymed_symbol_1;
    SI_Long buffer_index, temp, ab_loop_bind_;

    x_note_fn_call(22,52);
    if (FIXNUM_GT(ISVREF(managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	buffer_index = (SI_Long)0L;
	temp = IFIX(FIXNUM_ADD(ISVREF(managed_array,(SI_Long)1L),
		FIXNUM_SUB1(Maximum_managed_array_buffer_size))) / 
		IFIX(Maximum_managed_array_buffer_size);
	ab_loop_bind_ = temp;
      next_loop:
	if (buffer_index >= ab_loop_bind_)
	    goto end_loop;
	reclaim_managed_simple_vector_for_array(ISVREF(managed_array,
		buffer_index + (SI_Long)2L));
	buffer_index = buffer_index + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
  next_loop_1:
    gensymed_symbol = ISVREF(managed_array,(SI_Long)0L);
    gensymed_symbol_1 = Nil;
    if (CAS_SVREF(managed_array,(SI_Long)0L,gensymed_symbol,gensymed_symbol_1))
	goto end_1;
    goto next_loop_1;
  end_loop_1:
  end_1:
    reclaim_managed_simple_vector_for_array(managed_array);
    return VALUES_1(Nil);
}

/* RECLAIM-IF-MANAGED-ARRAY */
Object reclaim_if_managed_array(managed_array_qm)
    Object managed_array_qm;
{
    x_note_fn_call(22,53);
    if (SIMPLE_VECTOR_P(managed_array_qm) && EQ(ISVREF(managed_array_qm,
	    (SI_Long)0L),Managed_array_unique_marker))
	return reclaim_managed_array(managed_array_qm);
    else
	return VALUES_1(Nil);
}

/* GSI-ALLOCATE-MANAGED-ARRAY */
Object gsi_allocate_managed_array(requested_length)
    Object requested_length;
{
    Object modified_requested_length, vector_1, actual_length, svref_arg_2;

    x_note_fn_call(22,54);
    if (FIXNUM_GT(requested_length,Maximum_managed_array_buffer_size))
	modified_requested_length = FIXNUM_ADD1(requested_length);
    else if (IFIX(requested_length) == (SI_Long)0L)
	modified_requested_length = 
		FIXNUM_ADD1(Maximum_managed_array_buffer_size);
    else
	modified_requested_length = requested_length;
    vector_1 = allocate_managed_simple_vector(modified_requested_length);
    actual_length = length(vector_1);
    if (FIXNUM_GT(actual_length,Maximum_managed_array_buffer_size)) {
	svref_arg_2 = FIXNUM_SUB1(actual_length);
	SVREF(vector_1,svref_arg_2) = requested_length;
    }
    return VALUES_1(vector_1);
}

/* GSI-MANAGED-ARRAY-LENGTH */
Object gsi_managed_array_length(gsi_managed_array)
    Object gsi_managed_array;
{
    Object actual_length, temp;

    x_note_fn_call(22,55);
    actual_length = length(gsi_managed_array);
    temp = FIXNUM_GT(actual_length,Maximum_managed_array_buffer_size) ? 
	    ISVREF(gsi_managed_array,IFIX(FIXNUM_SUB1(actual_length))) : 
	    actual_length;
    return VALUES_1(temp);
}

/* GSI-RECLAIM-MANAGED-ARRAY */
Object gsi_reclaim_managed_array(managed_array)
    Object managed_array;
{
    x_note_fn_call(22,56);
    reclaim_managed_simple_vector(managed_array);
    return VALUES_1(Nil);
}

/* COPY-SIMPLE-VECTOR-PORTION-FUNCTION */
Object copy_simple_vector_portion_function(source_simple_vector,
	    source_index,element_count,destination_simple_vector,
	    destination_index)
    Object source_simple_vector, source_index, element_count;
    Object destination_simple_vector, destination_index;
{
    Object gensymed_symbol, gensymed_symbol_3, svref_new_value;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_4;

    x_note_fn_call(22,57);
    gensymed_symbol = source_simple_vector;
    gensymed_symbol_1 = IFIX(source_index);
    gensymed_symbol_2 = gensymed_symbol_1 + IFIX(element_count);
    gensymed_symbol_3 = destination_simple_vector;
    gensymed_symbol_4 = IFIX(destination_index);
  next_loop:
    if ( !(gensymed_symbol_1 < gensymed_symbol_2))
	goto end_loop;
    svref_new_value = ISVREF(gensymed_symbol,gensymed_symbol_1);
    ISVREF(gensymed_symbol_3,gensymed_symbol_4) = svref_new_value;
    gensymed_symbol_1 = gensymed_symbol_1 + (SI_Long)1L;
    gensymed_symbol_4 = gensymed_symbol_4 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* ADJUST-MANAGED-ARRAY */
Object adjust_managed_array varargs_1(int, n)
{
    Object managed_array, new_length;
    Object dont_copy, dont_initialize, old_full_buffers, old_remainder;
    Object old_total_buffers;
    SI_Long old_length, rounded_new_length, temp, new_full_buffers;
    SI_Long new_remainder, new_total_buffers, index_1, ab_loop_bind_;
    char temp_1;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(22,58);
    INIT_ARGS_nonrelocating();
    managed_array = REQUIRED_ARG_nonrelocating();
    new_length = REQUIRED_ARG_nonrelocating();
    dont_copy = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    dont_initialize = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    old_length = IFIX(ISVREF(managed_array,(SI_Long)1L));
    rounded_new_length = (SI_Long)0L;
    if (IFIX(new_length) == old_length)
	return VALUES_1(managed_array);
    if (old_length > IFIX(Maximum_in_place_array_size) && 
	    FIXNUM_GT(new_length,Maximum_in_place_array_size)) {
	result = chestnut_floorf_function(FIX(old_length),
		Maximum_managed_array_buffer_size);
	MVS_2(result,old_full_buffers,old_remainder);
	temp = IFIX(new_length) / IFIX(Maximum_managed_array_buffer_size);
	new_full_buffers = temp;
	temp = IFIX(new_length) % IFIX(Maximum_managed_array_buffer_size);
	new_remainder = temp;
	old_total_buffers = IFIX(old_remainder) > (SI_Long)0L ? 
		FIXNUM_ADD1(old_full_buffers) : old_full_buffers;
	new_total_buffers = new_remainder > (SI_Long)0L ? new_full_buffers 
		+ (SI_Long)1L : new_full_buffers;
	if (new_total_buffers == IFIX(old_total_buffers)) {
	    adjust_final_buffer_of_managed_array(managed_array,dont_copy,
		    dont_initialize,FIX(new_total_buffers),
		    IFIX(old_remainder) == (SI_Long)0L ? 
		    Maximum_managed_array_buffer_size : old_remainder,
		    new_remainder == (SI_Long)0L ? 
		    Maximum_managed_array_buffer_size : FIX(new_remainder));
	    SVREF(managed_array,FIX((SI_Long)1L)) = new_length;
	}
	else if (new_total_buffers > IFIX(old_total_buffers))
	    managed_array = grow_managed_array(managed_array,dont_copy,
		    dont_initialize,old_full_buffers,old_remainder,
		    old_total_buffers,new_length,FIX(new_full_buffers),
		    FIX(new_remainder),FIX(new_total_buffers));
	else
	    managed_array = shrink_managed_array(managed_array,dont_copy,
		    old_total_buffers,new_length,FIX(new_full_buffers),
		    FIX(new_remainder),FIX(new_total_buffers));
    }
    else {
	if (old_length <= IFIX(Maximum_in_place_array_size) && 
		FIXNUM_LE(new_length,Maximum_in_place_array_size)) {
	    rounded_new_length = 
		    IFIX(buffer_size_for_partial_buffer(FIXNUM_ADD(new_length,
		    Managed_array_index_offset),
		    Managed_array_allocation_schemes));
	    temp_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_array)) == 
		    rounded_new_length;
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    SVREF(managed_array,FIX((SI_Long)1L)) = new_length;
	    if (IFIX(new_length) > old_length &&  !TRUEP(dont_initialize)) {
		index_1 = IFIX(Managed_array_index_offset) + old_length;
		ab_loop_bind_ = IFIX(FIXNUM_ADD(Managed_array_index_offset,
			new_length));
	      next_loop:
		if (index_1 >= ab_loop_bind_)
		    goto end_loop;
		ISVREF(managed_array,index_1) = Nil;
		index_1 = index_1 + (SI_Long)1L;
		goto next_loop;
	      end_loop:;
	    }
	}
	else if (IFIX(new_length) > old_length)
	    managed_array = grow_managed_array(managed_array,dont_copy,
		    dont_initialize,Nil,Nil,Nil,new_length,Nil,Nil,Nil);
	else
	    managed_array = shrink_managed_array(managed_array,dont_copy,
		    Nil,new_length,Nil,Nil,Nil);
    }
    return VALUES_1(managed_array);
}

/* ADJUST-FINAL-BUFFER-OF-MANAGED-ARRAY */
Object adjust_final_buffer_of_managed_array(managed_array,dont_copy,
	    dont_initialize,total_buffers,old_final_buffer_length,
	    new_final_buffer_length)
    Object managed_array, dont_copy, dont_initialize, total_buffers;
    Object old_final_buffer_length, new_final_buffer_length;
{
    Object old_buffer, old_actual_buffer_length, new_actual_buffer_length;
    Object new_buffer;
    SI_Long svref_arg_2, index_1, ab_loop_bind_;

    x_note_fn_call(22,59);
    old_buffer = ISVREF(managed_array,IFIX(FIXNUM_SUB1(total_buffers)) + 
	    (SI_Long)2L);
    old_actual_buffer_length = length(old_buffer);
    new_actual_buffer_length = 
	    buffer_size_for_partial_buffer(new_final_buffer_length,
	    Managed_array_allocation_schemes);
    if (FIXNUM_NE(new_actual_buffer_length,old_actual_buffer_length)) {
	new_buffer = allocate_managed_simple_vector(new_actual_buffer_length);
	if ( !TRUEP(dont_copy))
	    copy_simple_vector_portion_function(old_buffer,
		    FIX((SI_Long)0L),FIXNUM_MIN(new_final_buffer_length,
		    old_final_buffer_length),new_buffer,FIX((SI_Long)0L));
	svref_arg_2 = IFIX(FIXNUM_SUB1(total_buffers)) + (SI_Long)2L;
	ISVREF(managed_array,svref_arg_2) = new_buffer;
	reclaim_managed_simple_vector(old_buffer);
	old_buffer = new_buffer;
    }
    if ( !TRUEP(dont_initialize) && FIXNUM_GT(new_final_buffer_length,
	    old_final_buffer_length)) {
	index_1 = IFIX(old_final_buffer_length);
	ab_loop_bind_ = IFIX(new_final_buffer_length);
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(old_buffer,index_1) = Nil;
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* GROW-MANAGED-ARRAY */
Object grow_managed_array(managed_array,dont_copy,dont_initialize,
	    old_full_buffers,old_remainder,old_total_buffers,new_length,
	    new_full_buffers,new_remainder,new_total_buffers)
    Object managed_array, dont_copy, dont_initialize, old_full_buffers;
    Object old_remainder, old_total_buffers, new_length, new_full_buffers;
    Object new_remainder, new_total_buffers;
{
    Object old_managed_array, new_spine_length, new_spine, gensymed_symbol;
    Object gensymed_symbol_1, new_buffer;
    SI_Long spine_index, ab_loop_bind_, buffer_index;

    x_note_fn_call(22,60);
    if (FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	old_managed_array = managed_array;
	managed_array = allocate_managed_array(1,new_length);
	copy_managed_array_portion(old_managed_array,FIX((SI_Long)0L),
		ISVREF(old_managed_array,(SI_Long)1L),managed_array,
		FIX((SI_Long)0L));
	reclaim_managed_array(old_managed_array);
    }
    else {
	if (FIXNUM_NE(old_full_buffers,old_total_buffers))
	    adjust_final_buffer_of_managed_array(managed_array,dont_copy,
		    dont_initialize,old_total_buffers,old_remainder,
		    Maximum_managed_array_buffer_size);
	new_spine_length = 
		buffer_size_for_partial_buffer(FIX(IFIX(new_total_buffers) 
		+ (SI_Long)2L),Managed_array_allocation_schemes);
	if (FIXNUM_NE(length(managed_array),new_spine_length)) {
	    new_spine = 
		    allocate_managed_simple_vector_for_array(new_spine_length);
	    copy_simple_vector_portion_function(managed_array,
		    FIX((SI_Long)2L),old_total_buffers,new_spine,
		    FIX((SI_Long)2L));
	  next_loop:
	    gensymed_symbol = ISVREF(managed_array,(SI_Long)0L);
	    gensymed_symbol_1 = Nil;
	    if (CAS_SVREF(managed_array,(SI_Long)0L,gensymed_symbol,
		    gensymed_symbol_1))
		goto end_1;
	    goto next_loop;
	  end_loop:
	  end_1:
	    reclaim_managed_simple_vector_for_array(managed_array);
	  next_loop_1:
	    gensymed_symbol = ISVREF(new_spine,(SI_Long)0L);
	    gensymed_symbol_1 = Managed_array_unique_marker;
	    if (CAS_SVREF(new_spine,(SI_Long)0L,gensymed_symbol,
		    gensymed_symbol_1))
		goto end_2;
	    goto next_loop_1;
	  end_loop_1:
	  end_2:
	    managed_array = new_spine;
	}
	SVREF(managed_array,FIX((SI_Long)1L)) = new_length;
	spine_index = IFIX(old_total_buffers);
	ab_loop_bind_ = IFIX(new_full_buffers);
	new_buffer = Nil;
      next_loop_2:
	if (spine_index >= ab_loop_bind_)
	    goto end_loop_2;
	new_buffer = 
		allocate_managed_simple_vector_for_array(Maximum_managed_array_buffer_size);
	if ( !TRUEP(dont_initialize)) {
	    buffer_index = (SI_Long)0L;
	  next_loop_3:
	    if (buffer_index >= IFIX(Maximum_managed_array_buffer_size))
		goto end_loop_3;
	  next_loop_4:
	    gensymed_symbol = ISVREF(new_buffer,buffer_index);
	    gensymed_symbol_1 = Nil;
	    if (CAS_SVREF(new_buffer,buffer_index,gensymed_symbol,
		    gensymed_symbol_1))
		goto end_3;
	    goto next_loop_4;
	  end_loop_4:
	  end_3:
	    buffer_index = buffer_index + (SI_Long)1L;
	    goto next_loop_3;
	  end_loop_3:;
	}
      next_loop_5:
	gensymed_symbol = ISVREF(managed_array,spine_index + (SI_Long)2L);
	gensymed_symbol_1 = new_buffer;
	if (CAS_SVREF(managed_array,spine_index + (SI_Long)2L,
		gensymed_symbol,gensymed_symbol_1))
	    goto end_4;
	goto next_loop_5;
      end_loop_5:
      end_4:
	spine_index = spine_index + (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:;
	if (FIXNUM_NE(new_full_buffers,new_total_buffers)) {
	    new_buffer = 
		    allocate_managed_simple_vector(buffer_size_for_partial_buffer(new_remainder,
		    Managed_array_allocation_schemes));
	    if ( !TRUEP(dont_initialize)) {
		buffer_index = (SI_Long)0L;
		ab_loop_bind_ = IFIX(new_remainder);
	      next_loop_6:
		if (buffer_index >= ab_loop_bind_)
		    goto end_loop_6;
	      next_loop_7:
		gensymed_symbol = ISVREF(new_buffer,buffer_index);
		gensymed_symbol_1 = Nil;
		if (CAS_SVREF(new_buffer,buffer_index,gensymed_symbol,
			gensymed_symbol_1))
		    goto end_5;
		goto next_loop_7;
	      end_loop_7:
	      end_5:
		buffer_index = buffer_index + (SI_Long)1L;
		goto next_loop_6;
	      end_loop_6:;
	    }
	  next_loop_8:
	    gensymed_symbol = ISVREF(managed_array,
		    IFIX(FIXNUM_SUB1(new_total_buffers)) + (SI_Long)2L);
	    gensymed_symbol_1 = new_buffer;
	    if (CAS_SVREF(managed_array,
		    IFIX(FIXNUM_SUB1(new_total_buffers)) + (SI_Long)2L,
		    gensymed_symbol,gensymed_symbol_1))
		goto end_6;
	    goto next_loop_8;
	  end_loop_8:
	  end_6:;
	}
    }
    return VALUES_1(managed_array);
}

/* SHRINK-MANAGED-ARRAY */
Object shrink_managed_array(managed_array,dont_copy,old_total_buffers,
	    new_length,new_full_buffers,new_remainder,new_total_buffers)
    Object managed_array, dont_copy, old_total_buffers, new_length;
    Object new_full_buffers, new_remainder, new_total_buffers;
{
    Object old_managed_array, new_spine_length, new_spine, gensymed_symbol;
    Object gensymed_symbol_1;
    SI_Long buffer_index, ab_loop_bind_;

    x_note_fn_call(22,61);
    if (FIXNUM_LE(new_length,Maximum_in_place_array_size)) {
	old_managed_array = managed_array;
	managed_array = allocate_managed_array(1,new_length);
	copy_managed_array_portion(old_managed_array,FIX((SI_Long)0L),
		ISVREF(managed_array,(SI_Long)1L),managed_array,
		FIX((SI_Long)0L));
	reclaim_managed_array(old_managed_array);
    }
    else {
	buffer_index = IFIX(new_total_buffers);
	ab_loop_bind_ = IFIX(old_total_buffers);
      next_loop:
	if (buffer_index >= ab_loop_bind_)
	    goto end_loop;
	reclaim_managed_simple_vector_for_array(ISVREF(managed_array,
		buffer_index + (SI_Long)2L));
	buffer_index = buffer_index + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	if (FIXNUM_NE(new_full_buffers,new_total_buffers))
	    adjust_final_buffer_of_managed_array(managed_array,dont_copy,T,
		    new_total_buffers,Maximum_managed_array_buffer_size,
		    new_remainder);
	new_spine_length = 
		buffer_size_for_partial_buffer(FIX(IFIX(new_total_buffers) 
		+ (SI_Long)2L),Managed_array_allocation_schemes);
	if (FIXNUM_NE(new_spine_length,length(managed_array))) {
	    new_spine = 
		    allocate_managed_simple_vector_for_array(new_spine_length);
	    copy_simple_vector_portion_function(managed_array,
		    FIX((SI_Long)2L),new_total_buffers,new_spine,
		    FIX((SI_Long)2L));
	  next_loop_1:
	    gensymed_symbol = ISVREF(managed_array,(SI_Long)0L);
	    gensymed_symbol_1 = Nil;
	    if (CAS_SVREF(managed_array,(SI_Long)0L,gensymed_symbol,
		    gensymed_symbol_1))
		goto end_1;
	    goto next_loop_1;
	  end_loop_1:
	  end_1:
	    reclaim_managed_simple_vector(managed_array);
	  next_loop_2:
	    gensymed_symbol = ISVREF(new_spine,(SI_Long)0L);
	    gensymed_symbol_1 = Managed_array_unique_marker;
	    if (CAS_SVREF(new_spine,(SI_Long)0L,gensymed_symbol,
		    gensymed_symbol_1))
		goto end_2;
	    goto next_loop_2;
	  end_loop_2:
	  end_2:
	    managed_array = new_spine;
	}
	SVREF(managed_array,FIX((SI_Long)1L)) = new_length;
    }
    return VALUES_1(managed_array);
}

/* SHRINK-OR-DELETE-MANAGED-ARRAY-NULL-ELEMENTS */
Object shrink_or_delete_managed_array_null_elements(managed_array)
    Object managed_array;
{
    SI_Long array_length, index_1, new_length;

    x_note_fn_call(22,62);
    array_length = IFIX(ISVREF(managed_array,(SI_Long)1L));
    index_1 = array_length - (SI_Long)1L;
  next_loop:
    if (index_1 < (SI_Long)0L)
	goto end_loop;
    if (FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? TRUEP(ISVREF(managed_array,
	    index_1 + IFIX(Managed_array_index_offset))) : 
	    TRUEP(ISVREF(ISVREF(managed_array,(index_1 >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),index_1 & (SI_Long)1023L))) {
	new_length = index_1 + (SI_Long)1L;
	if (new_length == array_length)
	    return VALUES_1(managed_array);
	else
	    return adjust_managed_array(2,managed_array,FIX(new_length));
    }
    index_1 = index_1 - (SI_Long)1L;
    goto next_loop;
  end_loop:
    reclaim_managed_array(managed_array);
    return VALUES_1(Nil);
    return VALUES_1(Qnil);
}

/* COPY-FROM-SIMPLE-VECTOR-INTO-MANAGED-ARRAY */
Object copy_from_simple_vector_into_managed_array(simple_vector,
	    vector_index_init,count_init,managed_array,array_index_init)
    Object simple_vector, vector_index_init, count_init, managed_array;
    Object array_index_init;
{
    Object temp, temp_1;
    SI_Long vector_index, count_1, array_index, buffer_index;
    SI_Long managed_buffer_number, elements_to_copy, temp_2, decff_1_arg;
    SI_Long incff_1_arg;
    Object result;

    x_note_fn_call(22,63);
    vector_index = IFIX(vector_index_init);
    count_1 = IFIX(count_init);
    array_index = IFIX(array_index_init);
    if (FIXNUM_LE(SVREF(managed_array,FIX((SI_Long)1L)),
	    Maximum_in_place_array_size))
	return copy_simple_vector_portion_function(simple_vector,
		FIX(vector_index),FIX(count_1),managed_array,
		FIX(array_index + IFIX(Managed_array_index_offset)));
    else {
	result = chestnut_floorf_function(FIX(array_index),
		Maximum_managed_array_buffer_size);
	MVS_2(result,temp,temp_1);
	buffer_index = IFIX(temp_1);
	managed_buffer_number = IFIX(temp);
	elements_to_copy = (SI_Long)0L;
      next_loop:
	if ( !(count_1 > (SI_Long)0L))
	    goto end_loop;
	temp_2 = IFIX(Maximum_managed_array_buffer_size) - buffer_index;
	elements_to_copy = MIN(temp_2,count_1);
	copy_simple_vector_portion_function(simple_vector,
		FIX(vector_index),FIX(elements_to_copy),
		ISVREF(managed_array,managed_buffer_number + (SI_Long)2L),
		FIX(buffer_index));
	decff_1_arg = elements_to_copy;
	count_1 = count_1 - decff_1_arg;
	incff_1_arg = elements_to_copy;
	vector_index = vector_index + incff_1_arg;
	managed_buffer_number = managed_buffer_number + (SI_Long)1L;
	buffer_index = (SI_Long)0L;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

/* COPY-FROM-MANAGED-ARRAY-INTO-SIMPLE-VECTOR */
Object copy_from_managed_array_into_simple_vector(managed_array,
	    array_index_init,count_init,simple_vector,vector_index_init)
    Object managed_array, array_index_init, count_init, simple_vector;
    Object vector_index_init;
{
    Object temp, temp_1;
    SI_Long array_index, count_1, vector_index, buffer_index;
    SI_Long managed_buffer_number, elements_to_copy, temp_2, decff_1_arg;
    SI_Long incff_1_arg;
    Object result;

    x_note_fn_call(22,64);
    array_index = IFIX(array_index_init);
    count_1 = IFIX(count_init);
    vector_index = IFIX(vector_index_init);
    if (FIXNUM_LT(SVREF(managed_array,FIX((SI_Long)1L)),
	    Maximum_in_place_array_size))
	return copy_simple_vector_portion_function(managed_array,
		FIX(array_index + IFIX(Managed_array_index_offset)),
		FIX(count_1),simple_vector,FIX(vector_index));
    else {
	result = chestnut_floorf_function(FIX(array_index),
		Maximum_managed_array_buffer_size);
	MVS_2(result,temp,temp_1);
	buffer_index = IFIX(temp_1);
	managed_buffer_number = IFIX(temp);
	elements_to_copy = (SI_Long)0L;
      next_loop:
	if ( !(count_1 > (SI_Long)0L))
	    goto end_loop;
	temp_2 = IFIX(Maximum_managed_array_buffer_size) - buffer_index;
	elements_to_copy = MIN(temp_2,count_1);
	copy_simple_vector_portion_function(ISVREF(managed_array,
		managed_buffer_number + (SI_Long)2L),FIX(buffer_index),
		FIX(elements_to_copy),simple_vector,FIX(vector_index));
	decff_1_arg = elements_to_copy;
	count_1 = count_1 - decff_1_arg;
	incff_1_arg = elements_to_copy;
	vector_index = vector_index + incff_1_arg;
	managed_buffer_number = managed_buffer_number + (SI_Long)1L;
	buffer_index = (SI_Long)0L;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

/* COPY-MANAGED-ARRAY-PORTION */
Object copy_managed_array_portion(source_array,source_index_init,
	    element_count_init,destination_array,destination_index_init)
    Object source_array, source_index_init, element_count_init;
    Object destination_array, destination_index_init;
{
    Object temp, temp_1, ab_loop_iter_flag_;
    SI_Long source_index, element_count, destination_index;
    SI_Long source_buffer_index, source_buffer_number, temp_2;
    SI_Long elements_to_copy, decff_1_arg, incff_1_arg;
    Object result;

    x_note_fn_call(22,65);
    source_index = IFIX(source_index_init);
    element_count = IFIX(element_count_init);
    destination_index = IFIX(destination_index_init);
    if (element_count > (SI_Long)0L) {
	result = chestnut_floorf_function(FIX(source_index),
		Maximum_managed_array_buffer_size);
	MVS_2(result,temp,temp_1);
	source_buffer_index = IFIX(temp_1);
	source_buffer_number = IFIX(temp);
	if (FIXNUM_LE(SVREF(source_array,FIX((SI_Long)1L)),
		Maximum_in_place_array_size))
	    return copy_from_simple_vector_into_managed_array(source_array,
		    FIX(source_index + IFIX(Managed_array_index_offset)),
		    FIX(element_count),destination_array,
		    FIX(destination_index));
	else {
	    temp_2 = IFIX(Maximum_managed_array_buffer_size) - 
		    source_buffer_index;
	    elements_to_copy = MIN(temp_2,element_count);
	    ab_loop_iter_flag_ = T;
	  next_loop:
	    if ( !(element_count > (SI_Long)0L))
		goto end_loop;
	    if ( !TRUEP(ab_loop_iter_flag_)) {
		temp_2 = IFIX(Maximum_managed_array_buffer_size);
		elements_to_copy = MIN(temp_2,element_count);
	    }
	    copy_from_simple_vector_into_managed_array(ISVREF(source_array,
		    source_buffer_number + (SI_Long)2L),
		    FIX(source_buffer_index),FIX(elements_to_copy),
		    destination_array,FIX(destination_index));
	    decff_1_arg = elements_to_copy;
	    element_count = element_count - decff_1_arg;
	    incff_1_arg = elements_to_copy;
	    destination_index = destination_index + incff_1_arg;
	    source_buffer_number = source_buffer_number + (SI_Long)1L;
	    source_buffer_index = (SI_Long)0L;
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
    }
    else
	return VALUES_1(Nil);
}

/* FILL-MANAGED-ARRAY */
Object fill_managed_array(managed_array,thing)
    Object managed_array, thing;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, temp_1, full_buffer;
    Object last_buffer;
    SI_Long length_1, index_1, ab_loop_bind_, partial_buffer, full_buffers;
    SI_Long buffer_index;
    Object result;

    x_note_fn_call(22,66);
    length_1 = IFIX(SVREF(managed_array,FIX((SI_Long)1L)));
    if (length_1 <= IFIX(Maximum_in_place_array_size)) {
	index_1 = IFIX(Managed_array_index_offset);
	ab_loop_bind_ = length_1 + IFIX(Managed_array_index_offset);
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
      next_loop_1:
	gensymed_symbol = ISVREF(managed_array,index_1);
	gensymed_symbol_1 = thing;
	if (CAS_SVREF(managed_array,index_1,gensymed_symbol,gensymed_symbol_1))
	    goto end_1;
	goto next_loop_1;
      end_loop_1:
      end_1:
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else {
	result = chestnut_floorf_function(FIX(length_1),
		Maximum_managed_array_buffer_size);
	MVS_2(result,temp,temp_1);
	partial_buffer = IFIX(temp_1);
	full_buffers = IFIX(temp);
	buffer_index = (SI_Long)0L;
	ab_loop_bind_ = full_buffers;
	full_buffer = Nil;
      next_loop_2:
	if (buffer_index >= ab_loop_bind_)
	    goto end_loop_2;
	full_buffer = ISVREF(managed_array,buffer_index + (SI_Long)2L);
	index_1 = (SI_Long)0L;
      next_loop_3:
	if (index_1 >= IFIX(Maximum_managed_array_buffer_size))
	    goto end_loop_3;
      next_loop_4:
	gensymed_symbol = ISVREF(full_buffer,index_1);
	gensymed_symbol_1 = thing;
	if (CAS_SVREF(full_buffer,index_1,gensymed_symbol,gensymed_symbol_1))
	    goto end_2;
	goto next_loop_4;
      end_loop_4:
      end_2:
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop_3;
      end_loop_3:;
	buffer_index = buffer_index + (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:;
	if (partial_buffer != (SI_Long)0L) {
	    last_buffer = ISVREF(managed_array,full_buffers + (SI_Long)2L);
	    index_1 = (SI_Long)0L;
	    ab_loop_bind_ = partial_buffer;
	  next_loop_5:
	    if (index_1 >= ab_loop_bind_)
		goto end_loop_5;
	  next_loop_6:
	    gensymed_symbol = ISVREF(last_buffer,index_1);
	    gensymed_symbol_1 = thing;
	    if (CAS_SVREF(last_buffer,index_1,gensymed_symbol,
		    gensymed_symbol_1))
		goto end_3;
	    goto next_loop_6;
	  end_loop_6:
	  end_3:
	    index_1 = index_1 + (SI_Long)1L;
	    goto next_loop_5;
	  end_loop_5:;
	}
	return VALUES_1(managed_array);
    }
}

/* ROTATE-MANAGED-ARRAY */
Object rotate_managed_array(managed_array,index_to_rotate)
    Object managed_array, index_to_rotate;
{
    Object new_array_or_vector, gensymed_symbol, gensymed_symbol_1;
    Object ab_loop_iter_flag_;
    SI_Long length_1, high_shift_size, copy_index, ab_loop_bind_, from_index;
    SI_Long to_index, buffer_index, temp;

    x_note_fn_call(22,67);
    if (IFIX(index_to_rotate) != (SI_Long)0L) {
	length_1 = IFIX(ISVREF(managed_array,(SI_Long)1L));
	new_array_or_vector = Nil;
	high_shift_size = length_1 - IFIX(index_to_rotate);
	if (length_1 <= IFIX(Maximum_in_place_array_size)) {
	    new_array_or_vector = 
		    allocate_managed_simple_vector(index_to_rotate);
	    copy_index = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(index_to_rotate);
	  next_loop:
	    if (copy_index >= ab_loop_bind_)
		goto end_loop;
	  next_loop_1:
	    gensymed_symbol = ISVREF(new_array_or_vector,copy_index);
	    gensymed_symbol_1 = ISVREF(managed_array,copy_index + 
		    IFIX(Managed_array_index_offset));
	    if (CAS_SVREF(new_array_or_vector,copy_index,gensymed_symbol,
		    gensymed_symbol_1))
		goto end_1;
	    goto next_loop_1;
	  end_loop_1:
	  end_1:
	    copy_index = copy_index + (SI_Long)1L;
	    goto next_loop;
	  end_loop:;
	    from_index = IFIX(FIXNUM_ADD(index_to_rotate,
		    Managed_array_index_offset));
	    ab_loop_bind_ = length_1 + IFIX(Managed_array_index_offset);
	    to_index = IFIX(Managed_array_index_offset);
	    ab_loop_iter_flag_ = T;
	  next_loop_2:
	    if (from_index >= ab_loop_bind_)
		goto end_loop_2;
	    if ( !TRUEP(ab_loop_iter_flag_))
		to_index = to_index + (SI_Long)1L;
	  next_loop_3:
	    gensymed_symbol = ISVREF(managed_array,to_index);
	    gensymed_symbol_1 = ISVREF(managed_array,from_index);
	    if (CAS_SVREF(managed_array,to_index,gensymed_symbol,
		    gensymed_symbol_1))
		goto end_2;
	    goto next_loop_3;
	  end_loop_3:
	  end_2:
	    ab_loop_iter_flag_ = Nil;
	    from_index = from_index + (SI_Long)1L;
	    goto next_loop_2;
	  end_loop_2:;
	    to_index = high_shift_size + IFIX(Managed_array_index_offset);
	    ab_loop_bind_ = length_1 + IFIX(Managed_array_index_offset);
	    from_index = (SI_Long)0L;
	    ab_loop_iter_flag_ = T;
	  next_loop_4:
	    if (to_index >= ab_loop_bind_)
		goto end_loop_4;
	    if ( !TRUEP(ab_loop_iter_flag_))
		from_index = from_index + (SI_Long)1L;
	  next_loop_5:
	    gensymed_symbol = ISVREF(managed_array,to_index);
	    gensymed_symbol_1 = ISVREF(new_array_or_vector,from_index);
	    if (CAS_SVREF(managed_array,to_index,gensymed_symbol,
		    gensymed_symbol_1))
		goto end_3;
	    goto next_loop_5;
	  end_loop_5:
	  end_3:
	    ab_loop_iter_flag_ = Nil;
	    to_index = to_index + (SI_Long)1L;
	    goto next_loop_4;
	  end_loop_4:;
	    reclaim_managed_simple_vector_for_array(new_array_or_vector);
	}
	else {
	    new_array_or_vector = allocate_managed_array(1,FIX(length_1));
	    copy_managed_array_portion(managed_array,index_to_rotate,
		    FIX(high_shift_size),new_array_or_vector,FIX((SI_Long)0L));
	    copy_managed_array_portion(managed_array,FIX((SI_Long)0L),
		    index_to_rotate,new_array_or_vector,FIX(high_shift_size));
	    buffer_index = (SI_Long)0L;
	    temp = (length_1 + 
		    IFIX(FIXNUM_SUB1(Maximum_managed_array_buffer_size))) 
		    / IFIX(Maximum_managed_array_buffer_size);
	    ab_loop_bind_ = temp;
	  next_loop_6:
	    if (buffer_index >= ab_loop_bind_)
		goto end_loop_6;
	    reclaim_managed_simple_vector_for_array(ISVREF(managed_array,
		    buffer_index + (SI_Long)2L));
	  next_loop_7:
	    gensymed_symbol = ISVREF(managed_array,buffer_index + (SI_Long)2L);
	    gensymed_symbol_1 = ISVREF(new_array_or_vector,buffer_index + 
		    (SI_Long)2L);
	    if (CAS_SVREF(managed_array,buffer_index + (SI_Long)2L,
		    gensymed_symbol,gensymed_symbol_1))
		goto end_4;
	    goto next_loop_7;
	  end_loop_7:
	  end_4:
	    buffer_index = buffer_index + (SI_Long)1L;
	    goto next_loop_6;
	  end_loop_6:;
	    reclaim_managed_simple_vector_for_array(new_array_or_vector);
	}
    }
    return VALUES_1(managed_array);
}

/* INSERT-INTO-MANAGED-ARRAY */
Object insert_into_managed_array(managed_array,position_1,new_element)
    Object managed_array, position_1, new_element;
{
    Object temp, svref_new_value;
    SI_Long length_1, index_1, ab_loop_bind_, svref_arg_2, gensymed_symbol;

    x_note_fn_call(22,68);
    length_1 = IFIX(SVREF(managed_array,FIX((SI_Long)1L)));
    managed_array = adjust_managed_array(2,managed_array,FIX(length_1 + 
	    (SI_Long)1L));
    index_1 = length_1;
    ab_loop_bind_ = IFIX(FIXNUM_ADD1(position_1));
  next_loop:
    if (index_1 < ab_loop_bind_)
	goto end_loop;
    if (FIXNUM_LE(SVREF(managed_array,FIX((SI_Long)1L)),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
	gensymed_symbol = index_1 - (SI_Long)1L;
	temp = FIXNUM_LE(SVREF(managed_array,FIX((SI_Long)1L)),
		Maximum_in_place_array_size) ? ISVREF(managed_array,
		gensymed_symbol + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(managed_array,(gensymed_symbol >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),gensymed_symbol & (SI_Long)1023L);
	ISVREF(managed_array,svref_arg_2) = temp;
    }
    else {
	temp = ISVREF(managed_array,(index_1 >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	svref_arg_2 = index_1 & (SI_Long)1023L;
	gensymed_symbol = index_1 - (SI_Long)1L;
	svref_new_value = FIXNUM_LE(SVREF(managed_array,FIX((SI_Long)1L)),
		Maximum_in_place_array_size) ? ISVREF(managed_array,
		gensymed_symbol + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(managed_array,(gensymed_symbol >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),gensymed_symbol & (SI_Long)1023L);
	ISVREF(temp,svref_arg_2) = svref_new_value;
    }
    index_1 = index_1 - (SI_Long)1L;
    goto next_loop;
  end_loop:;
    if (FIXNUM_LE(SVREF(managed_array,FIX((SI_Long)1L)),
	    Maximum_in_place_array_size)) {
	temp = FIXNUM_ADD(position_1,Managed_array_index_offset);
	SVREF(managed_array,temp) = new_element;
    }
    else {
	temp = ISVREF(managed_array,(IFIX(position_1) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = IFIX(position_1) & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = new_element;
    }
    return VALUES_1(managed_array);
}

/* DELETE-MANAGED-ARRAY-ELEMENT */
Object delete_managed_array_element(managed_array,position_1)
    Object managed_array, position_1;
{
    Object temp, svref_new_value;
    SI_Long length_1, index_1, ab_loop_bind_, gensymed_symbol, svref_arg_2;

    x_note_fn_call(22,69);
    length_1 = IFIX(SVREF(managed_array,FIX((SI_Long)1L)));
    index_1 = IFIX(FIXNUM_ADD1(position_1));
    ab_loop_bind_ = length_1;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    gensymed_symbol = index_1 - (SI_Long)1L;
    if (FIXNUM_LE(SVREF(managed_array,FIX((SI_Long)1L)),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol + IFIX(Managed_array_index_offset);
	temp = FIXNUM_LE(SVREF(managed_array,FIX((SI_Long)1L)),
		Maximum_in_place_array_size) ? ISVREF(managed_array,
		index_1 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(managed_array,(index_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),index_1 & (SI_Long)1023L);
	ISVREF(managed_array,svref_arg_2) = temp;
    }
    else {
	temp = ISVREF(managed_array,(gensymed_symbol >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol & (SI_Long)1023L;
	svref_new_value = FIXNUM_LE(SVREF(managed_array,FIX((SI_Long)1L)),
		Maximum_in_place_array_size) ? ISVREF(managed_array,
		index_1 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(managed_array,(index_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),index_1 & (SI_Long)1023L);
	ISVREF(temp,svref_arg_2) = svref_new_value;
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return adjust_managed_array(2,managed_array,FIX(length_1 - (SI_Long)1L));
}

Object Maximum_byte_vector_length = UNBOUND;

Object Byte_vector_allocation_schemes = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Available_byte_vector_conses, Qavailable_byte_vector_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_byte_vector_conses_tail, Qavailable_byte_vector_conses_tail);

Object Available_byte_vector_conses_vector = UNBOUND;

Object Available_byte_vector_conses_tail_vector = UNBOUND;

Object Byte_vector_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Byte_vector_cons_counter, Qbyte_vector_cons_counter);

/* OUTSTANDING-BYTE-VECTOR-CONSES */
Object outstanding_byte_vector_conses()
{
    Object temp;

    x_note_fn_call(22,70);
    temp = FIXNUM_MINUS(Byte_vector_cons_counter,
	    length(Available_byte_vector_conses));
    return VALUES_1(temp);
}

/* BYTE-VECTOR-CONS-MEMORY-USAGE */
Object byte_vector_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(22,71);
    temp = FIXNUM_TIMES(Byte_vector_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-BYTE-VECTOR-CONS-POOL */
Object replenish_byte_vector_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(22,72);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qbyte_vector_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_byte_vector_conses_vector,
		IFIX(Current_thread_index))) {
	svref_arg_1 = Available_byte_vector_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_byte_vector_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_byte_vector_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_byte_vector_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Byte_vector_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qbyte_vector;        /* byte-vector */

/* BYTE-VECTOR-CONS-1 */
Object byte_vector_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(22,73);
    new_cons = ISVREF(Available_byte_vector_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_byte_vector_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_byte_vector_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_byte_vector_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_byte_vector_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qbyte_vector);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-BYTE-VECTOR-LIST-POOL */
Object replenish_byte_vector_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(22,74);
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
    if (ISVREF(Available_byte_vector_conses_vector,
		IFIX(Current_thread_index))) {
	svref_arg_1 = Available_byte_vector_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_byte_vector_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_byte_vector_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_byte_vector_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qbyte_vector_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-BYTE-VECTOR-LIST-1 */
Object make_byte_vector_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(22,75);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_byte_vector_conses_vector,
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
	replenish_byte_vector_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_byte_vector_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qbyte_vector);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_byte_vector_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_byte_vector_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_byte_vector_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_byte_vector_conses_tail_vector;
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

/* BYTE-VECTOR-LIST-2 */
Object byte_vector_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(22,76);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_byte_vector_conses_vector,
	    IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_byte_vector_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_byte_vector_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qbyte_vector);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_byte_vector_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_byte_vector_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_byte_vector_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_byte_vector_conses_tail_vector;
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

/* BYTE-VECTOR-LIST-3 */
Object byte_vector_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(22,77);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_byte_vector_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_byte_vector_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_byte_vector_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qbyte_vector);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_byte_vector_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_byte_vector_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_byte_vector_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_byte_vector_conses_tail_vector;
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

/* BYTE-VECTOR-LIST-4 */
Object byte_vector_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(22,78);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_byte_vector_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_byte_vector_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_byte_vector_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qbyte_vector);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_byte_vector_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_byte_vector_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_byte_vector_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_byte_vector_conses_tail_vector;
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

/* BYTE-VECTOR-LIST-TRACE-HOOK */
Object byte_vector_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(22,79);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-BYTE-VECTOR-CONSES-1 */
Object copy_tree_using_byte_vector_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(22,80);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_byte_vector_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_byte_vector_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_byte_vector_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_byte_vector_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_byte_vector_cons_pool();
	temp_1 = copy_tree_using_byte_vector_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qbyte_vector);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_byte_vector_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_byte_vector_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_byte_vector_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_byte_vector_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_byte_vector_cons_pool();
	temp_1 = 
		copy_tree_using_byte_vector_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qbyte_vector);
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

/* COPY-LIST-USING-BYTE-VECTOR-CONSES-1 */
Object copy_list_using_byte_vector_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(22,81);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_byte_vector_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_byte_vector_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_byte_vector_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_byte_vector_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_byte_vector_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qbyte_vector);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_byte_vector_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_byte_vector_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_byte_vector_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_byte_vector_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_byte_vector_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qbyte_vector);
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

/* RECLAIM-BYTE-VECTOR-CONS-1 */
Object reclaim_byte_vector_cons_1(byte_vector_cons)
    Object byte_vector_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(22,82);
    inline_note_reclaim_cons(byte_vector_cons,Qbyte_vector);
    if (ISVREF(Available_byte_vector_conses_tail_vector,
	    IFIX(Current_thread_index))) {
	temp = ISVREF(Available_byte_vector_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = byte_vector_cons;
	temp = Available_byte_vector_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = byte_vector_cons;
    }
    else {
	temp = Available_byte_vector_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = byte_vector_cons;
	temp = Available_byte_vector_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = byte_vector_cons;
    }
    M_CDR(byte_vector_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-BYTE-VECTOR-LIST-1 */
Object reclaim_byte_vector_list_1(byte_vector_list)
    Object byte_vector_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(22,83);
    if (byte_vector_list) {
	last_1 = byte_vector_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qbyte_vector);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qbyte_vector);
	if (ISVREF(Available_byte_vector_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_byte_vector_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = byte_vector_list;
	    temp = Available_byte_vector_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_byte_vector_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = byte_vector_list;
	    temp = Available_byte_vector_conses_tail_vector;
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

/* RECLAIM-BYTE-VECTOR-LIST*-1 */
Object reclaim_byte_vector_list_star_1(byte_vector_list)
    Object byte_vector_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(22,84);
    if (CONSP(byte_vector_list)) {
	temp = last(byte_vector_list,_);
	M_CDR(temp) = Nil;
	if (byte_vector_list) {
	    last_1 = byte_vector_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qbyte_vector);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qbyte_vector);
	    if (ISVREF(Available_byte_vector_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_byte_vector_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = byte_vector_list;
		temp = Available_byte_vector_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_byte_vector_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = byte_vector_list;
		temp = Available_byte_vector_conses_tail_vector;
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

/* RECLAIM-BYTE-VECTOR-TREE-1 */
Object reclaim_byte_vector_tree_1(tree)
    Object tree;
{
    Object e, e2, byte_vector_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(22,85);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_byte_vector_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		byte_vector_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(byte_vector_cons,Qbyte_vector);
		if (EQ(byte_vector_cons,e))
		    goto end_1;
		else if ( !TRUEP(byte_vector_cons))
		    goto end_1;
		else
		    byte_vector_cons = CDR(byte_vector_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_byte_vector_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_byte_vector_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_byte_vector_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_byte_vector_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_byte_vector_conses_tail_vector;
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

/* DELETE-BYTE-VECTOR-ELEMENT-1 */
Object delete_byte_vector_element_1(element,byte_vector_list)
    Object element, byte_vector_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(22,86);
    if (byte_vector_list) {
	if (EQ(element,M_CAR(byte_vector_list))) {
	    temp = CDR(byte_vector_list);
	    inline_note_reclaim_cons(byte_vector_list,Qbyte_vector);
	    if (ISVREF(Available_byte_vector_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_byte_vector_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = byte_vector_list;
		temp_1 = Available_byte_vector_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = byte_vector_list;
	    }
	    else {
		temp_1 = Available_byte_vector_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = byte_vector_list;
		temp_1 = Available_byte_vector_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = byte_vector_list;
	    }
	    M_CDR(byte_vector_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = byte_vector_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qbyte_vector);
		if (ISVREF(Available_byte_vector_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = 
			    ISVREF(Available_byte_vector_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_byte_vector_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_byte_vector_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_byte_vector_conses_tail_vector;
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
	    temp = byte_vector_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-BYTE-VECTOR-CONS-1 */
Object delete_byte_vector_cons_1(byte_vector_cons,byte_vector_list)
    Object byte_vector_cons, byte_vector_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(22,87);
    if (EQ(byte_vector_cons,byte_vector_list))
	temp = CDR(byte_vector_list);
    else {
	l_trailer_qm = Nil;
	l = byte_vector_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,byte_vector_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = byte_vector_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_byte_vector_cons_1(byte_vector_cons);
    return VALUES_1(temp);
}

/* MAKE-BYTE-VECTOR-POOLS */
Object make_byte_vector_pools(initial_elt)
    Object initial_elt;
{
    XDeclare_area(1);
    Object result;

    x_note_fn_call(22,88);
    if (PUSH_AREA(Dynamic_area,0))
	result = make_array(3,
		FIXNUM_ADD1(partial_buffer_pool_index_given_length(Maximum_byte_vector_length,
		Byte_vector_allocation_schemes)),Kinitial_element,initial_elt);
    POP_AREA(0);
    return result;
}

Object Byte_vector_pools = UNBOUND;

Object Byte_vector_pool_counts = UNBOUND;

Object Allocated_byte_vectors = UNBOUND;

/* OUTSTANDING-BYTE-VECTORS */
Object outstanding_byte_vectors()
{
    Object decff_1_arg;
    SI_Long outstanding, pool_index, ab_loop_bind_;

    x_note_fn_call(22,89);
    outstanding = IFIX(Allocated_byte_vectors);
    pool_index = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length(Byte_vector_pools));
  next_loop:
    if (pool_index >= ab_loop_bind_)
	goto end_loop;
    decff_1_arg = length(ISVREF(Byte_vector_pools,pool_index));
    outstanding = outstanding - IFIX(decff_1_arg);
    pool_index = pool_index + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(FIX(outstanding));
    return VALUES_1(Qnil);
}

Object Bytes_in_allocated_byte_vectors = UNBOUND;

/* BYTE-VECTOR-MEMORY-USAGE */
Object byte_vector_memory_usage()
{
    x_note_fn_call(22,90);
    return VALUES_1(Bytes_in_allocated_byte_vectors);
}

static Object Qallocated_byte_vectors;  /* allocated-byte-vectors */

static Object Qbytes_in_allocated_byte_vectors;  /* bytes-in-allocated-byte-vectors */

static Object list_constant;       /* # */

/* ALLOCATE-BYTE-VECTOR */
Object allocate_byte_vector(required_size)
    Object required_size;
{
    Object temp, pool_index, pool_list, vector_1, temp_1, temp_2;
    SI_Long rounded_up_length;
    XDeclare_area(1);
    Object result;

    x_note_fn_call(22,91);
    if (FIXNUM_GT(required_size,Maximum_byte_vector_length))
	error((SI_Long)3L,
		"Attempted to make a byte vector ~a elements long.  Maximum is ~a.",
		required_size,Maximum_byte_vector_length);
    result = buffer_size_and_pool_for_partial_buffer(required_size,
	    Byte_vector_allocation_schemes);
    MVS_2(result,temp,pool_index);
    rounded_up_length = IFIX(temp);
    pool_list = ISVREF(Byte_vector_pools,IFIX(pool_index));
    if (pool_list) {
	vector_1 = CAR(pool_list);
	temp_1 = Byte_vector_pools;
	temp_2 = CDR(pool_list);
	SVREF(temp_1,pool_index) = temp_2;
	inline_note_reclaim_cons(pool_list,Qbyte_vector);
	if (ISVREF(Available_byte_vector_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_1 = ISVREF(Available_byte_vector_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_1) = pool_list;
	    temp_1 = Available_byte_vector_conses_tail_vector;
	    temp_2 = Current_thread_index;
	    SVREF(temp_1,temp_2) = pool_list;
	}
	else {
	    temp_1 = Available_byte_vector_conses_vector;
	    temp_2 = Current_thread_index;
	    SVREF(temp_1,temp_2) = pool_list;
	    temp_1 = Available_byte_vector_conses_tail_vector;
	    temp_2 = Current_thread_index;
	    SVREF(temp_1,temp_2) = pool_list;
	}
	M_CDR(pool_list) = Nil;
	return VALUES_1(vector_1);
    }
    else {
	atomic_incff_symval(Qallocated_byte_vectors,FIX((SI_Long)1L));
	atomic_incff_symval(Qbytes_in_allocated_byte_vectors,
		bytes_per_unsigned_byte_8_simple_array(FIX(rounded_up_length)));
	if (pool_index)
	    atomic_incff_svslot(Byte_vector_pool_counts,pool_index,
		    FIX((SI_Long)1L));
	if (PUSH_AREA(Dynamic_area,0))
	    result = make_array(3,FIX(rounded_up_length),Kelement_type,
		    list_constant);
	POP_AREA(0);
	return result;
    }
}

/* RECLAIM-BYTE-VECTOR */
Object reclaim_byte_vector(byte_vector)
    Object byte_vector;
{
    Object svref_arg_1, svref_new_value;
    SI_Long array_length, pool_index;

    x_note_fn_call(22,92);
    array_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(byte_vector));
    pool_index = 
	    IFIX(partial_buffer_pool_index_given_length(FIX(array_length),
	    Byte_vector_allocation_schemes));
    svref_arg_1 = Byte_vector_pools;
    svref_new_value = byte_vector_cons_1(byte_vector,
	    ISVREF(Byte_vector_pools,pool_index));
    ISVREF(svref_arg_1,pool_index) = svref_new_value;
    return VALUES_1(Nil);
}

/* COPY-BYTE-VECTOR-PORTION */
Object copy_byte_vector_portion(source_byte_vector,source_index,
	    target_byte_vector,target_index,byte_count)
    Object source_byte_vector, source_index, target_byte_vector, target_index;
    Object byte_count;
{
    Object ab_loop_iter_flag_;
    SI_Long copy_index, ab_loop_bind_, aref_new_value, copy_source_index;
    SI_Long copy_target_index;

    x_note_fn_call(22,93);
    if (FIXNUM_EQ(source_index,target_index)) {
	copy_index = IFIX(source_index);
	ab_loop_bind_ = IFIX(FIXNUM_ADD(source_index,byte_count));
      next_loop:
	if (copy_index >= ab_loop_bind_)
	    goto end_loop;
	aref_new_value = UBYTE_8_ISAREF_1(source_byte_vector,copy_index);
	UBYTE_8_ISASET_1(target_byte_vector,copy_index,aref_new_value);
	copy_index = copy_index + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    else {
	copy_source_index = IFIX(source_index);
	ab_loop_bind_ = IFIX(FIXNUM_ADD(source_index,byte_count));
	copy_target_index = IFIX(target_index);
	ab_loop_iter_flag_ = T;
      next_loop_1:
	if (copy_source_index >= ab_loop_bind_)
	    goto end_loop_1;
	if ( !TRUEP(ab_loop_iter_flag_))
	    copy_target_index = copy_target_index + (SI_Long)1L;
	aref_new_value = UBYTE_8_ISAREF_1(source_byte_vector,
		copy_source_index);
	UBYTE_8_ISASET_1(target_byte_vector,copy_target_index,aref_new_value);
	ab_loop_iter_flag_ = Nil;
	copy_source_index = copy_source_index + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
    }
    return VALUES_1(Nil);
}

Object Maximum_byte_vector_16_length = UNBOUND;

Object Maximum_wide_string_length = UNBOUND;

Object Byte_vector_16_allocation_schemes = UNBOUND;

/* MAKE-BYTE-VECTOR-16-POOLS */
Object make_byte_vector_16_pools(initial_elt)
    Object initial_elt;
{
    XDeclare_area(1);
    Object result;

    x_note_fn_call(22,94);
    if (PUSH_AREA(Dynamic_area,0))
	result = make_array(3,
		FIXNUM_ADD1(partial_buffer_pool_index_given_length(Maximum_byte_vector_16_length,
		Byte_vector_16_allocation_schemes)),Kinitial_element,
		initial_elt);
    POP_AREA(0);
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Byte_vector_16_pools, Qbyte_vector_16_pools);

DEFINE_VARIABLE_WITH_SYMBOL(Byte_vector_16_pool_counts, Qbyte_vector_16_pool_counts);

DEFINE_VARIABLE_WITH_SYMBOL(Allocated_byte_vector_16_vectors, Qallocated_byte_vector_16_vectors);

/* OUTSTANDING-BYTE-VECTOR-16-VECTORS */
Object outstanding_byte_vector_16_vectors()
{
    Object decff_1_arg;
    SI_Long outstanding, pool_index, ab_loop_bind_;

    x_note_fn_call(22,95);
    outstanding = IFIX(Allocated_byte_vector_16_vectors);
    pool_index = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length(Byte_vector_16_pools));
  next_loop:
    if (pool_index >= ab_loop_bind_)
	goto end_loop;
    decff_1_arg = length(ISVREF(Byte_vector_16_pools,pool_index));
    outstanding = outstanding - IFIX(decff_1_arg);
    pool_index = pool_index + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(FIX(outstanding));
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Bytes_in_allocated_byte_vector_16_vectors, Qbytes_in_allocated_byte_vector_16_vectors);

/* BYTE-VECTOR-16-MEMORY-USAGE */
Object byte_vector_16_memory_usage()
{
    x_note_fn_call(22,96);
    return VALUES_1(Bytes_in_allocated_byte_vector_16_vectors);
}

DEFINE_VARIABLE_WITH_SYMBOL(Free_malloced_arrays, Qfree_malloced_arrays);

DEFINE_VARIABLE_WITH_SYMBOL(Largest_non_malloced_byte_vector_16_pool_index, Qlargest_non_malloced_byte_vector_16_pool_index);

DEFINE_VARIABLE_WITH_SYMBOL(Byte_vector_16_pool_number_to_malloc, Qbyte_vector_16_pool_number_to_malloc);

/* SET-MALLOCED-BYTE-VECTOR-16-THRESHHOLD */
Object set_malloced_byte_vector_16_threshhold(length_1)
    Object length_1;
{
    Object rounded_up_length, pool_index;
    Object result;

    x_note_fn_call(22,97);
    if (IFIX(length_1) == (SI_Long)-1L) {
	Byte_vector_16_pool_number_to_malloc = FIX((SI_Long)-1L);
	return VALUES_1(Byte_vector_16_pool_number_to_malloc);
    }
    else {
	result = buffer_size_and_pool_for_partial_buffer(length_1,
		Byte_vector_16_allocation_schemes);
	MVS_2(result,rounded_up_length,pool_index);
	if (FIXNUM_GT(pool_index,
		Largest_non_malloced_byte_vector_16_pool_index))
	    Byte_vector_16_pool_number_to_malloc = pool_index;
	return VALUES_1(rounded_up_length);
    }
}

/* FREE-MALLOCED-BYTE-VECTOR-16S */
Object free_malloced_byte_vector_16s()
{
    Object array_list, array, ab_loop_list_, svref_arg_1;
    SI_Long pool_index, ab_loop_bind_;

    x_note_fn_call(22,98);
    if (IFIX(Byte_vector_16_pool_number_to_malloc) >= (SI_Long)0L) {
	pool_index = IFIX(Byte_vector_16_pool_number_to_malloc);
	ab_loop_bind_ = IFIX(length(Byte_vector_16_pools));
      next_loop:
	if (pool_index >= ab_loop_bind_)
	    goto end_loop;
	array_list = ISVREF(Byte_vector_16_pools,pool_index);
	array = Nil;
	ab_loop_list_ = array_list;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	array = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	free_malloced_byte_vector_16(array);
	goto next_loop_1;
      end_loop_1:;
	reclaim_byte_vector_list_1(array_list);
	svref_arg_1 = Byte_vector_16_pools;
	ISVREF(svref_arg_1,pool_index) = Nil;
	pool_index = pool_index + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object list_constant_1;     /* # */

/* ALLOCATE-BYTE-VECTOR-16 */
Object allocate_byte_vector_16(required_size)
    Object required_size;
{
    Object temp, temp_1, pool_list, vector_1, temp_3, temp_4, bv16;
    SI_Long pool_index, rounded_up_length, temp_2, length_1;
    XDeclare_area(1);
    Object result;

    x_note_fn_call(22,99);
    result = buffer_size_and_pool_for_partial_buffer(required_size,
	    Byte_vector_16_allocation_schemes);
    MVS_2(result,temp,temp_1);
    pool_index = IFIX(temp_1);
    rounded_up_length = IFIX(temp);
    if (IFIX(Byte_vector_16_pool_number_to_malloc) == (SI_Long)-1L || 
	    pool_index < IFIX(Byte_vector_16_pool_number_to_malloc)) {
	temp_2 = IFIX(Largest_non_malloced_byte_vector_16_pool_index);
	Largest_non_malloced_byte_vector_16_pool_index = FIX(MAX(temp_2,
		pool_index));
    }
    pool_list = ISVREF(Byte_vector_16_pools,pool_index);
    if (pool_list) {
	vector_1 = M_CAR(pool_list);
	temp_3 = Byte_vector_16_pools;
	temp_4 = M_CDR(pool_list);
	ISVREF(temp_3,pool_index) = temp_4;
	inline_note_reclaim_cons(pool_list,Qbyte_vector);
	if (ISVREF(Available_byte_vector_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_3 = ISVREF(Available_byte_vector_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_3) = pool_list;
	    temp_3 = Available_byte_vector_conses_tail_vector;
	    temp_4 = Current_thread_index;
	    SVREF(temp_3,temp_4) = pool_list;
	}
	else {
	    temp_3 = Available_byte_vector_conses_vector;
	    temp_4 = Current_thread_index;
	    SVREF(temp_3,temp_4) = pool_list;
	    temp_3 = Available_byte_vector_conses_tail_vector;
	    temp_4 = Current_thread_index;
	    SVREF(temp_3,temp_4) = pool_list;
	}
	M_CDR(pool_list) = Nil;
	bv16 = vector_1;
    }
    else {
	length_1 = rounded_up_length;
	atomic_incff_symval(Qallocated_byte_vector_16_vectors,
		FIX((SI_Long)1L));
	temp_3 = Byte_vector_16_pool_counts;
	temp_4 = FIXNUM_ADD1(ISVREF(temp_3,pool_index));
	ISVREF(temp_3,pool_index) = temp_4;
	atomic_incff_symval(Qbytes_in_allocated_byte_vector_16_vectors,
		bytes_per_unsigned_byte_16_simple_array(FIX(length_1)));
	if (IFIX(Byte_vector_16_pool_number_to_malloc) == (SI_Long)-1L || 
		pool_index < IFIX(Byte_vector_16_pool_number_to_malloc)) {
	    if (PUSH_AREA(Dynamic_area,0))
		bv16 = make_array(3,FIX(length_1),Kelement_type,
			list_constant_1);
	    POP_AREA(0);
	}
	else
	    bv16 = g2rtl_make_malloced_array(length_1);
    }
    inline_note_allocate_cons(bv16,Nil);
    return VALUES_1(bv16);
}

/* RETURN-BYTE-VECTOR-16-TO-POOL */
Object return_byte_vector_16_to_pool(byte_vector_16)
    Object byte_vector_16;
{
    Object svref_arg_1, svref_new_value;
    SI_Long pool_index;

    x_note_fn_call(22,100);
    pool_index = 
	    IFIX(partial_buffer_pool_index_given_length(SIMPLE_ARRAY_ANY_1_LENGTH(byte_vector_16),
	    Byte_vector_16_allocation_schemes));
    svref_arg_1 = Byte_vector_16_pools;
    svref_new_value = byte_vector_cons_1(byte_vector_16,
	    ISVREF(Byte_vector_16_pools,pool_index));
    ISVREF(svref_arg_1,pool_index) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-BYTE-VECTOR-16 */
Object reclaim_byte_vector_16(byte_vector_16)
    Object byte_vector_16;
{
    Object temp;

    x_note_fn_call(22,101);
    inline_note_reclaim_cons(byte_vector_16,Nil);
    temp = Free_malloced_arrays ? 
	    free_malloced_byte_vector_16(byte_vector_16) : 
	    return_byte_vector_16_to_pool(byte_vector_16);
    return VALUES_1(temp);
}

/* FREE-MALLOCED-BYTE-VECTOR-16 */
Object free_malloced_byte_vector_16(byte_vector_16)
    Object byte_vector_16;
{
    Object rounded_up_length, pool_index;
    Object result;

    x_note_fn_call(22,102);
    if (IFIX(Byte_vector_16_pool_number_to_malloc) == (SI_Long)-1L)
	return return_byte_vector_16_to_pool(byte_vector_16);
    result = buffer_size_and_pool_for_partial_buffer(length(byte_vector_16),
	    Byte_vector_16_allocation_schemes);
    MVS_2(result,rounded_up_length,pool_index);
    if (FIXNUM_LT(pool_index,Byte_vector_16_pool_number_to_malloc))
	return_byte_vector_16_to_pool(byte_vector_16);
    else {
	atomic_incff_svslot(Byte_vector_16_pool_counts,pool_index,FIX( - 
		(SI_Long)1L));
	atomic_incff_symval(Qallocated_byte_vector_16_vectors,FIX( - 
		(SI_Long)1L));
	atomic_incff_symval(Qbytes_in_allocated_byte_vector_16_vectors,
		FIXNUM_NEGATE(bytes_per_unsigned_byte_16_simple_array(rounded_up_length)));
	g2rtl_free_malloced_array_internal(byte_vector_16);
    }
    return VALUES_1(T);
}

/* COPY-BYTE-VECTOR-16-PORTION-CAREFULLY */
Object copy_byte_vector_16_portion_carefully(source_vector_16,
	    source_elt_index_init,target_vector_16,target_elt_index_init,
	    element_count_init)
    Object source_vector_16, source_elt_index_init, target_vector_16;
    Object target_elt_index_init, element_count_init;
{
    Object ab_loop_iter_flag_;
    SI_Long source_elt_index, target_elt_index, element_count, source_index;
    SI_Long ab_loop_bind_, target_index, aref_new_value;

    x_note_fn_call(22,103);
    source_elt_index = IFIX(source_elt_index_init);
    target_elt_index = IFIX(target_elt_index_init);
    element_count = IFIX(element_count_init);
    if (EQ(source_vector_16,target_vector_16) && source_elt_index < 
	    target_elt_index) {
	source_index = source_elt_index + element_count - (SI_Long)1L;
	ab_loop_bind_ = source_elt_index;
	target_index = target_elt_index + element_count - (SI_Long)1L;
	ab_loop_iter_flag_ = T;
      next_loop:
	if (source_index < ab_loop_bind_)
	    goto end_loop;
	if ( !TRUEP(ab_loop_iter_flag_))
	    target_index = target_index - (SI_Long)1L;
	aref_new_value = UBYTE_16_ISAREF_1(source_vector_16,source_index);
	UBYTE_16_ISASET_1(target_vector_16,target_index,aref_new_value);
	ab_loop_iter_flag_ = Nil;
	source_index = source_index - (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    else {
	source_index = source_elt_index;
	ab_loop_bind_ = source_elt_index + element_count;
	target_index = target_elt_index;
	ab_loop_iter_flag_ = T;
      next_loop_1:
	if (source_index >= ab_loop_bind_)
	    goto end_loop_1;
	if ( !TRUEP(ab_loop_iter_flag_))
	    target_index = target_index + (SI_Long)1L;
	aref_new_value = UBYTE_16_ISAREF_1(source_vector_16,source_index);
	UBYTE_16_ISASET_1(target_vector_16,target_index,aref_new_value);
	ab_loop_iter_flag_ = Nil;
	source_index = source_index + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
    }
    return VALUES_1(Nil);
}

/* ALLOCATE-CHARACTER-BYTE-VECTOR */
Object allocate_character_byte_vector(length_1)
    Object length_1;
{
    XDeclare_area(1);
    Object result;

    x_note_fn_call(22,104);
    if (PUSH_AREA(Dynamic_area,0))
	result = make_array(5,length_1,Kinitial_element,FIX((SI_Long)0L),
		Kelement_type,list_constant);
    POP_AREA(0);
    return result;
}

/* DO-ACTIVITY */
Object do_activity(activity)
    Object activity;
{
    Object simple_compiled_function, temp, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(22,105);
    simple_compiled_function = CAR(activity);
    temp = FIXNUM_SUB1(length(activity));
    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)127L))))
	return VALUES_1(Nil);
    else
	switch (INTEGER_TO_CHAR(temp)) {
	  case 0:
	    return VALUES_1(inline_funcall_0(simple_compiled_function));
	  case 1:
	    gensymed_symbol = simple_compiled_function;
	    gensymed_symbol_1 = SECOND(activity);
	    return VALUES_1(inline_funcall_1(gensymed_symbol,
		    gensymed_symbol_1));
	  case 2:
	    gensymed_symbol = simple_compiled_function;
	    gensymed_symbol_1 = SECOND(activity);
	    gensymed_symbol_2 = THIRD(activity);
	    return VALUES_1(inline_funcall_2(gensymed_symbol,
		    gensymed_symbol_1,gensymed_symbol_2));
	  case 3:
	    gensymed_symbol = simple_compiled_function;
	    gensymed_symbol_1 = SECOND(activity);
	    gensymed_symbol_2 = THIRD(activity);
	    gensymed_symbol_3 = FOURTH(activity);
	    return VALUES_1(inline_funcall_3(gensymed_symbol,
		    gensymed_symbol_1,gensymed_symbol_2,gensymed_symbol_3));
	  default:
	    return VALUES_1(Nil);
	}
}

/* DO-ACTIVITIES */
Object do_activities(activity_list)
    Object activity_list;
{
    Object activity, ab_loop_list_;

    x_note_fn_call(22,106);
    activity = Nil;
    ab_loop_list_ = activity_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    activity = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    do_activity(activity);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* RECLAIM-ACTIVITIES */
Object reclaim_activities(activity_list)
    Object activity_list;
{
    Object activity, ab_loop_list_;

    x_note_fn_call(22,107);
    activity = Nil;
    ab_loop_list_ = activity_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    activity = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_gensym_list_1(activity);
    goto next_loop;
  end_loop:
    reclaim_gensym_list_1(activity_list);
    return VALUES_1(Qnil);
}

/* PLISTP */
Object plistp(thing)
    Object thing;
{
    Object temp, p, ab_loop_list_;
    char temp_1;

    x_note_fn_call(22,108);
    if (LISTP(thing)) {
	temp = last(thing,_);
	temp_1 =  !TRUEP(CDR(temp));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1 ?  !EQ(Nil,FIXNUM_EVENP(length(thing)) ? T : Nil) : 
		TRUEP(Nil)) {
	p = Nil;
	ab_loop_list_ = thing;
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
      next_loop:
	p = CAR(ab_loop_list_);
	if ( !(p && SYMBOLP(p)))
	    return VALUES_1(Nil);
	ab_loop_list_ = CDDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	goto next_loop;
      end_loop:
	return VALUES_1(T);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* ORDER-IN-FRONT */
Object order_in_front(element_1,element_2,list_1)
    Object element_1, element_2, list_1;
{
    Object cons_before_1, cons_before_2, changed_something_qm, sublist;
    Object element, temp_a, temp_b, temp_1, temp_c;
    char temp;

    x_note_fn_call(22,109);
    cons_before_1 = Nil;
    cons_before_2 = Nil;
    changed_something_qm = Nil;
    sublist = list_1;
    element = Nil;
  next_loop:
    if ( !TRUEP(sublist))
	goto end_loop;
    element = FIRST(sublist);
    if (EQ(element,element_1)) {
	temp = TRUEP(Nil);
	goto end_1;
    }
    else if (EQ(element,element_2)) {
	temp = TRUEP(T);
	goto end_1;
    }
    cons_before_2 = sublist;
    sublist = M_CDR(sublist);
    goto next_loop;
  end_loop:
    temp = TRUEP(Qnil);
  end_1:;
    if (temp) {
	sublist = cons_before_2 ? CDR(cons_before_2) : list_1;
	element = Nil;
      next_loop_1:
	if ( !TRUEP(sublist))
	    goto end_loop_1;
	element = FIRST(sublist);
	if (EQ(element,element_1))
	    goto end_loop_1;
	cons_before_1 = sublist;
	sublist = M_CDR(sublist);
	goto next_loop_1;
      end_loop_1:;
	if (cons_before_2 && CDR(cons_before_1)) {
	    temp_a = CDR(cons_before_2);
	    temp_b = CDR(cons_before_1);
	    temp_1 = CDR(cons_before_1);
	    temp_c = CDR(temp_1);
	    M_CDR(cons_before_2) = temp_b;
	    M_CDR(cons_before_1) = temp_c;
	    M_CDR(temp_b) = temp_a;
	    changed_something_qm = T;
	}
	else if (CDR(cons_before_1)) {
	    temp_a = list_1;
	    temp_b = CDR(cons_before_1);
	    temp_1 = CDR(cons_before_1);
	    temp_c = CDR(temp_1);
	    list_1 = temp_b;
	    M_CDR(cons_before_1) = temp_c;
	    M_CDR(temp_b) = temp_a;
	    changed_something_qm = T;
	}
    }
    return VALUES_2(list_1,changed_something_qm);
}

/* ORDER-IN-BACK */
Object order_in_back(element_1,element_2,list_1)
    Object element_1, element_2, list_1;
{
    Object new_list, changed_qm, temp;
    Object result;

    x_note_fn_call(22,110);
    result = order_in_front(element_1,element_2,nreverse(list_1));
    MVS_2(result,new_list,changed_qm);
    temp = nreverse(new_list);
    return VALUES_2(temp,changed_qm);
}

/* CIRCULAR-LIST-P */
Object circular_list_p(list_1)
    Object list_1;
{
    x_note_fn_call(22,111);
    return VALUES_1( !TRUEP(list_length(list_1)) ? T : Nil);
}

/* CAR-OR-ATOM */
Object car_or_atom(thing)
    Object thing;
{
    x_note_fn_call(22,112);
    if (CONSP(thing))
	return VALUES_1(CAR(thing));
    else
	return VALUES_1(thing);
}

/* CDR-OR-ATOM */
Object cdr_or_atom(thing)
    Object thing;
{
    x_note_fn_call(22,113);
    if (CONSP(thing))
	return VALUES_1(CDR(thing));
    else
	return VALUES_1(Nil);
}

/* ALIST-TO-PLIST */
Object alist_to_plist(alist)
    Object alist;
{
    Object l, cdr_l, result_1, cons_cell, indicator, value, temp;

    x_note_fn_call(22,114);
    l = alist;
    cdr_l = Nil;
    result_1 = l;
    cons_cell = Nil;
    indicator = Nil;
    value = Nil;
  next_loop:
    if ( !TRUEP(l))
	goto end_loop;
    cdr_l = M_CDR(l);
    cons_cell = M_CAR(l);
    indicator = M_CAR(cons_cell);
    value = M_CDR(cons_cell);
    M_CDR(l) = cons_cell;
    M_CDR(cons_cell) = cdr_l;
    M_FIRST(l) = indicator;
    M_SECOND(l) = value;
    l = cdr_l;
    goto next_loop;
  end_loop:
    temp = result_1;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

void utilities0_INIT()
{
    Object star_features_star_new_value, temp, temp_1, temp_2, temp_3, temp_4;
    Object temp_5, temp_6, temp_7, temp_8, temp_9, temp_10, temp_11, temp_12;
    Object temp_13, temp_14, temp_15, temp_16, temp_17, temp_18, temp_19;
    Object temp_20, temp_21;
    Object string_constant_5, Qbyte_vector_16_memory_usage;
    Object Qoutstanding_byte_vector_16_vectors, AB_package, Qutilities0;
    Object list_constant_11, list_constant_6, Qmake_byte_vector_16_pools;
    Object Kfuncall, list_constant_10, list_constant_4, string_constant_4;
    Object Qbyte_vector_memory_usage, Qoutstanding_byte_vectors;
    Object list_constant_9, Qbyte_vector_pool_counts, Qmake_byte_vector_pools;
    Object list_constant_8, Qbyte_vector_pools, string_constant_3;
    Object Qbyte_vector_cons_memory_usage, Qoutstanding_byte_vector_conses;
    Object list_constant_3, Qbyte_vector_cons_counter_vector, list_constant_2;
    Object Qavailable_byte_vector_conses_tail_vector;
    Object Qavailable_byte_vector_conses_vector, Qmaximum_in_place_array_size;
    Object Qmaximum_managed_array_size, Qmanaged_array, string_constant_2;
    Object Qsvp_memory_usage, Qoutstanding_simple_vector_pool_vectors;
    Object list_constant_7, list_constant_5;
    Object Qallocate_initial_managed_simple_vector_pool_array;
    Object Qmaximum_managed_simple_vector_size, string_constant_1;
    Object Qgensym_cons_memory_usage, Qoutstanding_gensym_conses;
    Object Qgensym_cons_counter_vector, Qmake_thread_array;
    Object Qavailable_gensym_conses_tail_vector;
    Object Qavailable_gensym_conses_vector, Kuse_queue_allocation_for_consing;
    Object string_constant;

    x_note_fn_call(22,115);
    SET_PACKAGE("AB");
    string_constant = STATIC_STRING("MANAGED-FLOAT-MARKER");
    if (Managed_float_unique_marker == UNBOUND)
	Managed_float_unique_marker = make_symbol(string_constant);
    AB_package = STATIC_PACKAGE("AB");
    Qstrange_cons = STATIC_SYMBOL("STRANGE-CONS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qstrange_cons,Strange_cons);
    if (Strange_cons == UNBOUND)
	Strange_cons = LIST_1(Qstrange_cons);
    if (Debugging_consing == UNBOUND)
	Debugging_consing = Nil;
    Kuse_queue_allocation_for_consing = 
	    STATIC_SYMBOL("USE-QUEUE-ALLOCATION-FOR-CONSING",Pkeyword);
    star_features_star_new_value = adjoin(2,
	    Kuse_queue_allocation_for_consing,Features);
    Features = star_features_star_new_value;
    Cons_pool_conses_to_make_at_a_time = FIX((SI_Long)1024L);
    if (All_cons_pools == UNBOUND)
	All_cons_pools = Nil;
    Qavailable_gensym_conses = STATIC_SYMBOL("AVAILABLE-GENSYM-CONSES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_gensym_conses,
	    Available_gensym_conses);
    Qutilities0 = STATIC_SYMBOL("UTILITIES0",AB_package);
    record_system_variable(Qavailable_gensym_conses,Qutilities0,Nil,Qnil,
	    Qt,Qnil,Qnil);
    Qavailable_gensym_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-GENSYM-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_gensym_conses_tail,
	    Available_gensym_conses_tail);
    record_system_variable(Qavailable_gensym_conses_tail,Qutilities0,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_gensym_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-GENSYM-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_gensym_conses_vector,
	    Available_gensym_conses_vector);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_thread_array = STATIC_SYMBOL("MAKE-THREAD-ARRAY",AB_package);
    SET_SYMBOL_FUNCTION(Qmake_thread_array,
	    STATIC_FUNCTION(make_thread_array,NIL,FALSE,1,1));
    list_constant_2 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    Qnil);
    record_system_variable(Qavailable_gensym_conses_vector,Qutilities0,
	    list_constant_2,Qnil,Qt,Qnil,Qnil);
    Qavailable_gensym_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-GENSYM-CONSES-TAIL-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_gensym_conses_tail_vector,
	    Available_gensym_conses_tail_vector);
    record_system_variable(Qavailable_gensym_conses_tail_vector,
	    Qutilities0,list_constant_2,Qnil,Qt,Qnil,Qnil);
    Qgensym_cons_counter_vector = 
	    STATIC_SYMBOL("GENSYM-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgensym_cons_counter_vector,
	    Gensym_cons_counter_vector);
    list_constant_3 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    FIX((SI_Long)0L));
    record_system_variable(Qgensym_cons_counter_vector,Qutilities0,
	    list_constant_3,Qnil,Qt,Qnil,Qnil);
    Qgensym_cons_counter = STATIC_SYMBOL("GENSYM-CONS-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgensym_cons_counter,Gensym_cons_counter);
    record_system_variable(Qgensym_cons_counter,Qutilities0,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_gensym_conses = STATIC_SYMBOL("OUTSTANDING-GENSYM-CONSES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_gensym_conses,
	    STATIC_FUNCTION(outstanding_gensym_conses,NIL,FALSE,0,0));
    Qgensym_cons_memory_usage = STATIC_SYMBOL("GENSYM-CONS-MEMORY-USAGE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qgensym_cons_memory_usage,
	    STATIC_FUNCTION(gensym_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_1 = STATIC_STRING("1q83-WEy9k83-WDy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_gensym_conses);
    push_optimized_constant(Qgensym_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_1));
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    SET_SYMBOL_FUNCTION(Qab_gensym,STATIC_FUNCTION(ab_gensym,NIL,TRUE,0,1));
    if (Scope_conses == UNBOUND)
	Scope_conses = LIST_1(LIST_1(Nil));
    Qmaximum_managed_simple_vector_size = 
	    STATIC_SYMBOL("MAXIMUM-MANAGED-SIMPLE-VECTOR-SIZE",AB_package);
    SET_SYMBOL_VALUE(Qmaximum_managed_simple_vector_size,FIX((SI_Long)1024L));
    Qvector_of_simple_vector_pools = 
	    STATIC_SYMBOL("VECTOR-OF-SIMPLE-VECTOR-POOLS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qvector_of_simple_vector_pools,
	    Vector_of_simple_vector_pools);
    Qallocate_initial_managed_simple_vector_pool_array = 
	    STATIC_SYMBOL("ALLOCATE-INITIAL-MANAGED-SIMPLE-VECTOR-POOL-ARRAY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qallocate_initial_managed_simple_vector_pool_array,
	    STATIC_FUNCTION(allocate_initial_managed_simple_vector_pool_array,
	    NIL,FALSE,1,1));
    list_constant_4 = STATIC_CONS(Qnil,Qnil);
    list_constant_5 = STATIC_LIST_STAR((SI_Long)3L,Kfuncall,
	    Qallocate_initial_managed_simple_vector_pool_array,
	    list_constant_4);
    record_system_variable(Qvector_of_simple_vector_pools,Qutilities0,
	    list_constant_5,Qnil,Qt,Qnil,Qnil);
    Qsimple_vector_pool_counts = STATIC_SYMBOL("SIMPLE-VECTOR-POOL-COUNTS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsimple_vector_pool_counts,
	    Simple_vector_pool_counts);
    list_constant_6 = STATIC_CONS(FIX((SI_Long)0L),Qnil);
    list_constant_7 = STATIC_LIST_STAR((SI_Long)3L,Kfuncall,
	    Qallocate_initial_managed_simple_vector_pool_array,
	    list_constant_6);
    record_system_variable(Qsimple_vector_pool_counts,Qutilities0,
	    list_constant_7,Qnil,Qt,Qnil,Qnil);
    Qvector_of_oversized_simple_vector_pools = 
	    STATIC_SYMBOL("VECTOR-OF-OVERSIZED-SIMPLE-VECTOR-POOLS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qvector_of_oversized_simple_vector_pools,
	    Vector_of_oversized_simple_vector_pools);
    record_system_variable(Qvector_of_oversized_simple_vector_pools,
	    Qutilities0,list_constant_5,Qnil,Qnil,Qnil,Qnil);
    Qoversized_simple_vector_pool_counts = 
	    STATIC_SYMBOL("OVERSIZED-SIMPLE-VECTOR-POOL-COUNTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qoversized_simple_vector_pool_counts,
	    Oversized_simple_vector_pool_counts);
    record_system_variable(Qoversized_simple_vector_pool_counts,
	    Qutilities0,list_constant_7,Qnil,Qnil,Qnil,Qnil);
    Qcreated_simple_vector_pool_vectors = 
	    STATIC_SYMBOL("CREATED-SIMPLE-VECTOR-POOL-VECTORS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcreated_simple_vector_pool_vectors,
	    Created_simple_vector_pool_vectors);
    record_system_variable(Qcreated_simple_vector_pool_vectors,Qutilities0,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qsimple_vector_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-VECTOR-POOL-MEMORY-USAGE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsimple_vector_pool_memory_usage,
	    Simple_vector_pool_memory_usage);
    record_system_variable(Qsimple_vector_pool_memory_usage,Qutilities0,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_simple_vector_pool_vectors = 
	    STATIC_SYMBOL("OUTSTANDING-SIMPLE-VECTOR-POOL-VECTORS",AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_simple_vector_pool_vectors,
	    STATIC_FUNCTION(outstanding_simple_vector_pool_vectors,NIL,
	    FALSE,0,0));
    Qsvp_memory_usage = STATIC_SYMBOL("SVP-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qsvp_memory_usage,STATIC_FUNCTION(svp_memory_usage,
	    NIL,FALSE,0,0));
    string_constant_2 = STATIC_STRING("1q83-ddy83*9y83-PPy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_simple_vector_pool_vectors);
    push_optimized_constant(Qsvp_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_2));
    Replenished_simple_vector_size_limit = FIX((SI_Long)10L);
    Replenished_simple_vectors_to_make_at_a_time = FIX((SI_Long)10L);
    temp = make_partial_buffer_info(FIX((SI_Long)8L),FIX((SI_Long)1L),
	    FIX((SI_Long)0L),FIX((SI_Long)0L));
    temp_1 = make_partial_buffer_info(FIX((SI_Long)32L),FIX((SI_Long)4L),
	    FIX((SI_Long)0L),FIX((SI_Long)2L));
    temp_2 = make_partial_buffer_info(FIX((SI_Long)64L),FIX((SI_Long)8L),
	    FIX((SI_Long)5L),FIX((SI_Long)3L));
    temp_3 = make_partial_buffer_info(FIX((SI_Long)128L),FIX((SI_Long)16L),
	    FIX((SI_Long)9L),FIX((SI_Long)4L));
    temp_4 = make_partial_buffer_info(FIX((SI_Long)256L),FIX((SI_Long)32L),
	    FIX((SI_Long)13L),FIX((SI_Long)5L));
    temp_5 = make_partial_buffer_info(FIX((SI_Long)512L),FIX((SI_Long)64L),
	    FIX((SI_Long)17L),FIX((SI_Long)6L));
    Managed_array_allocation_schemes = list(7,temp,temp_1,temp_2,temp_3,
	    temp_4,temp_5,make_partial_buffer_info(FIX((SI_Long)1024L),
	    FIX((SI_Long)128L),FIX((SI_Long)21L),FIX((SI_Long)7L)));
    Qmanaged_array = STATIC_SYMBOL("MANAGED-ARRAY",AB_package);
    if (Managed_array_unique_marker == UNBOUND)
	Managed_array_unique_marker = CONS(Qmanaged_array,Nil);
    Qmaximum_managed_array_size = 
	    STATIC_SYMBOL("MAXIMUM-MANAGED-ARRAY-SIZE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmaximum_managed_array_size,
	    Maximum_managed_array_size);
    SET_SYMBOL_VALUE(Qmaximum_managed_array_size,
	    FIX((IFIX(Maximum_managed_array_buffer_size) - (SI_Long)2L) * 
	    IFIX(Maximum_managed_array_buffer_size)));
    Qmaximum_in_place_array_size = 
	    STATIC_SYMBOL("MAXIMUM-IN-PLACE-ARRAY-SIZE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmaximum_in_place_array_size,
	    Maximum_in_place_array_size);
    SET_SYMBOL_VALUE(Qmaximum_in_place_array_size,
	    FIX(IFIX(Maximum_managed_array_buffer_size) - (SI_Long)2L));
    Maximum_byte_vector_length = FIX((SI_Long)131072L);
    temp_6 = make_partial_buffer_info(FIX((SI_Long)128L),FIX((SI_Long)16L),
	    FIX((SI_Long)0L),FIX((SI_Long)4L));
    temp_7 = make_partial_buffer_info(FIX((SI_Long)256L),FIX((SI_Long)32L),
	    FIX((SI_Long)5L),FIX((SI_Long)5L));
    temp_8 = make_partial_buffer_info(FIX((SI_Long)512L),FIX((SI_Long)64L),
	    FIX((SI_Long)9L),FIX((SI_Long)6L));
    temp_9 = make_partial_buffer_info(FIX((SI_Long)1024L),
	    FIX((SI_Long)128L),FIX((SI_Long)13L),FIX((SI_Long)7L));
    temp = make_partial_buffer_info(FIX((SI_Long)2048L),FIX((SI_Long)256L),
	    FIX((SI_Long)17L),FIX((SI_Long)8L));
    temp_1 = make_partial_buffer_info(FIX((SI_Long)4096L),
	    FIX((SI_Long)512L),FIX((SI_Long)21L),FIX((SI_Long)9L));
    temp_2 = make_partial_buffer_info(FIX((SI_Long)8192L),
	    FIX((SI_Long)1024L),FIX((SI_Long)25L),FIX((SI_Long)10L));
    temp_3 = make_partial_buffer_info(FIX((SI_Long)16384L),
	    FIX((SI_Long)2048L),FIX((SI_Long)29L),FIX((SI_Long)11L));
    temp_4 = make_partial_buffer_info(FIX((SI_Long)32768L),
	    FIX((SI_Long)4096L),FIX((SI_Long)33L),FIX((SI_Long)12L));
    temp_5 = make_partial_buffer_info(FIX((SI_Long)65536L),
	    FIX((SI_Long)8192L),FIX((SI_Long)37L),FIX((SI_Long)13L));
    Byte_vector_allocation_schemes = list(11,temp_6,temp_7,temp_8,temp_9,
	    temp,temp_1,temp_2,temp_3,temp_4,temp_5,
	    make_partial_buffer_info(FIX((SI_Long)131072L),
	    FIX((SI_Long)16384L),FIX((SI_Long)41L),FIX((SI_Long)14L)));
    Qavailable_byte_vector_conses = 
	    STATIC_SYMBOL("AVAILABLE-BYTE-VECTOR-CONSES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_byte_vector_conses,
	    Available_byte_vector_conses);
    record_system_variable(Qavailable_byte_vector_conses,Qutilities0,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_byte_vector_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-BYTE-VECTOR-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_byte_vector_conses_tail,
	    Available_byte_vector_conses_tail);
    record_system_variable(Qavailable_byte_vector_conses_tail,Qutilities0,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qavailable_byte_vector_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-BYTE-VECTOR-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_byte_vector_conses_vector,
	    Available_byte_vector_conses_vector);
    record_system_variable(Qavailable_byte_vector_conses_vector,
	    Qutilities0,list_constant_2,Qnil,Qt,Qnil,Qnil);
    Qavailable_byte_vector_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-BYTE-VECTOR-CONSES-TAIL-VECTOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_byte_vector_conses_tail_vector,
	    Available_byte_vector_conses_tail_vector);
    record_system_variable(Qavailable_byte_vector_conses_tail_vector,
	    Qutilities0,list_constant_2,Qnil,Qt,Qnil,Qnil);
    Qbyte_vector_cons_counter_vector = 
	    STATIC_SYMBOL("BYTE-VECTOR-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbyte_vector_cons_counter_vector,
	    Byte_vector_cons_counter_vector);
    record_system_variable(Qbyte_vector_cons_counter_vector,Qutilities0,
	    list_constant_3,Qnil,Qt,Qnil,Qnil);
    Qbyte_vector_cons_counter = STATIC_SYMBOL("BYTE-VECTOR-CONS-COUNTER",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbyte_vector_cons_counter,
	    Byte_vector_cons_counter);
    record_system_variable(Qbyte_vector_cons_counter,Qutilities0,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_byte_vector_conses = 
	    STATIC_SYMBOL("OUTSTANDING-BYTE-VECTOR-CONSES",AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_byte_vector_conses,
	    STATIC_FUNCTION(outstanding_byte_vector_conses,NIL,FALSE,0,0));
    Qbyte_vector_cons_memory_usage = 
	    STATIC_SYMBOL("BYTE-VECTOR-CONS-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qbyte_vector_cons_memory_usage,
	    STATIC_FUNCTION(byte_vector_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_3 = STATIC_STRING("1q83-LDy9k83-LCy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_byte_vector_conses);
    push_optimized_constant(Qbyte_vector_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_3));
    Qbyte_vector = STATIC_SYMBOL("BYTE-VECTOR",AB_package);
    Qbyte_vector_pools = STATIC_SYMBOL("BYTE-VECTOR-POOLS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbyte_vector_pools,Byte_vector_pools);
    Qmake_byte_vector_pools = STATIC_SYMBOL("MAKE-BYTE-VECTOR-POOLS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmake_byte_vector_pools,
	    STATIC_FUNCTION(make_byte_vector_pools,NIL,FALSE,1,1));
    list_constant_8 = STATIC_LIST_STAR((SI_Long)3L,Kfuncall,
	    Qmake_byte_vector_pools,list_constant_4);
    record_system_variable(Qbyte_vector_pools,Qutilities0,list_constant_8,
	    Qnil,Qt,Qnil,Qnil);
    Qbyte_vector_pool_counts = STATIC_SYMBOL("BYTE-VECTOR-POOL-COUNTS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbyte_vector_pool_counts,
	    Byte_vector_pool_counts);
    list_constant_9 = STATIC_LIST_STAR((SI_Long)3L,Kfuncall,
	    Qmake_byte_vector_pools,list_constant_6);
    record_system_variable(Qbyte_vector_pool_counts,Qutilities0,
	    list_constant_9,Qnil,Qt,Qnil,Qnil);
    Qallocated_byte_vectors = STATIC_SYMBOL("ALLOCATED-BYTE-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qallocated_byte_vectors,Allocated_byte_vectors);
    record_system_variable(Qallocated_byte_vectors,Qutilities0,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qbytes_in_allocated_byte_vectors = 
	    STATIC_SYMBOL("BYTES-IN-ALLOCATED-BYTE-VECTORS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbytes_in_allocated_byte_vectors,
	    Bytes_in_allocated_byte_vectors);
    record_system_variable(Qbytes_in_allocated_byte_vectors,Qutilities0,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_byte_vectors = STATIC_SYMBOL("OUTSTANDING-BYTE-VECTORS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_byte_vectors,
	    STATIC_FUNCTION(outstanding_byte_vectors,NIL,FALSE,0,0));
    Qbyte_vector_memory_usage = STATIC_SYMBOL("BYTE-VECTOR-MEMORY-USAGE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qbyte_vector_memory_usage,
	    STATIC_FUNCTION(byte_vector_memory_usage,NIL,FALSE,0,0));
    string_constant_4 = STATIC_STRING("1q83-LEy1m9k1m83oFys83-JVy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qvector);
    push_optimized_constant(Qoutstanding_byte_vectors);
    push_optimized_constant(Qbyte_vector_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_4));
    list_constant = STATIC_LIST((SI_Long)2L,Qunsigned_byte,FIX((SI_Long)8L));
    Maximum_byte_vector_16_length = FIX((SI_Long)268435456L);
    Maximum_wide_string_length = 
	    FIXNUM_MINUS(Maximum_byte_vector_16_length,
	    Extra_wide_string_bv16_elements);
    temp_10 = make_partial_buffer_info(FIX((SI_Long)64L),FIX((SI_Long)8L),
	    FIX((SI_Long)0L),FIX((SI_Long)3L));
    temp_11 = make_partial_buffer_info(FIX((SI_Long)128L),
	    FIX((SI_Long)16L),FIX((SI_Long)5L),FIX((SI_Long)4L));
    temp_12 = make_partial_buffer_info(FIX((SI_Long)256L),
	    FIX((SI_Long)32L),FIX((SI_Long)9L),FIX((SI_Long)5L));
    temp_13 = make_partial_buffer_info(FIX((SI_Long)512L),
	    FIX((SI_Long)64L),FIX((SI_Long)13L),FIX((SI_Long)6L));
    temp_14 = make_partial_buffer_info(FIX((SI_Long)1024L),
	    FIX((SI_Long)128L),FIX((SI_Long)17L),FIX((SI_Long)7L));
    temp_15 = make_partial_buffer_info(FIX((SI_Long)2048L),
	    FIX((SI_Long)256L),FIX((SI_Long)21L),FIX((SI_Long)8L));
    temp_16 = make_partial_buffer_info(FIX((SI_Long)4096L),
	    FIX((SI_Long)512L),FIX((SI_Long)25L),FIX((SI_Long)9L));
    temp_17 = make_partial_buffer_info(FIX((SI_Long)8192L),
	    FIX((SI_Long)1024L),FIX((SI_Long)29L),FIX((SI_Long)10L));
    temp_18 = make_partial_buffer_info(FIX((SI_Long)16384L),
	    FIX((SI_Long)2048L),FIX((SI_Long)33L),FIX((SI_Long)11L));
    temp_19 = make_partial_buffer_info(FIX((SI_Long)32768L),
	    FIX((SI_Long)4096L),FIX((SI_Long)37L),FIX((SI_Long)12L));
    temp_20 = make_partial_buffer_info(FIX((SI_Long)65536L),
	    FIX((SI_Long)8192L),FIX((SI_Long)41L),FIX((SI_Long)13L));
    temp_21 = make_partial_buffer_info(FIX((SI_Long)131072L),
	    FIX((SI_Long)16384L),FIX((SI_Long)45L),FIX((SI_Long)14L));
    temp_6 = make_partial_buffer_info(FIX((SI_Long)262144L),
	    FIX((SI_Long)32768L),FIX((SI_Long)49L),FIX((SI_Long)15L));
    temp_7 = make_partial_buffer_info(FIX((SI_Long)524288L),
	    FIX((SI_Long)65536L),FIX((SI_Long)53L),FIX((SI_Long)16L));
    temp_8 = make_partial_buffer_info(FIX((SI_Long)1048576L),
	    FIX((SI_Long)131072L),FIX((SI_Long)57L),FIX((SI_Long)17L));
    temp_9 = make_partial_buffer_info(FIX((SI_Long)2097152L),
	    FIX((SI_Long)262144L),FIX((SI_Long)61L),FIX((SI_Long)18L));
    temp = make_partial_buffer_info(FIX((SI_Long)4194304L),
	    FIX((SI_Long)524288L),FIX((SI_Long)65L),FIX((SI_Long)19L));
    temp_1 = make_partial_buffer_info(FIX((SI_Long)8388608L),
	    FIX((SI_Long)1048576L),FIX((SI_Long)69L),FIX((SI_Long)20L));
    temp_2 = make_partial_buffer_info(FIX((SI_Long)16777216L),
	    FIX((SI_Long)2097152L),FIX((SI_Long)73L),FIX((SI_Long)21L));
    temp_3 = make_partial_buffer_info(FIX((SI_Long)33554432L),
	    FIX((SI_Long)4194304L),FIX((SI_Long)77L),FIX((SI_Long)22L));
    temp_4 = make_partial_buffer_info(FIX((SI_Long)67108864L),
	    FIX((SI_Long)8388608L),FIX((SI_Long)81L),FIX((SI_Long)23L));
    temp_5 = make_partial_buffer_info(FIX((SI_Long)134217728L),
	    FIX((SI_Long)16777216L),FIX((SI_Long)85L),FIX((SI_Long)24L));
    Byte_vector_16_allocation_schemes = list(23,temp_10,temp_11,temp_12,
	    temp_13,temp_14,temp_15,temp_16,temp_17,temp_18,temp_19,
	    temp_20,temp_21,temp_6,temp_7,temp_8,temp_9,temp,temp_1,temp_2,
	    temp_3,temp_4,temp_5,
	    make_partial_buffer_info(FIX((SI_Long)268435456L),
	    FIX((SI_Long)33554432L),FIX((SI_Long)89L),FIX((SI_Long)25L)));
    Qbyte_vector_16_pools = STATIC_SYMBOL("BYTE-VECTOR-16-POOLS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbyte_vector_16_pools,Byte_vector_16_pools);
    Qmake_byte_vector_16_pools = STATIC_SYMBOL("MAKE-BYTE-VECTOR-16-POOLS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmake_byte_vector_16_pools,
	    STATIC_FUNCTION(make_byte_vector_16_pools,NIL,FALSE,1,1));
    list_constant_10 = STATIC_LIST_STAR((SI_Long)3L,Kfuncall,
	    Qmake_byte_vector_16_pools,list_constant_4);
    record_system_variable(Qbyte_vector_16_pools,Qutilities0,
	    list_constant_10,Qnil,Qt,Qnil,Qnil);
    Qbyte_vector_16_pool_counts = 
	    STATIC_SYMBOL("BYTE-VECTOR-16-POOL-COUNTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbyte_vector_16_pool_counts,
	    Byte_vector_16_pool_counts);
    list_constant_11 = STATIC_LIST_STAR((SI_Long)3L,Kfuncall,
	    Qmake_byte_vector_16_pools,list_constant_6);
    record_system_variable(Qbyte_vector_16_pool_counts,Qutilities0,
	    list_constant_11,Qnil,Qt,Qnil,Qnil);
    Qallocated_byte_vector_16_vectors = 
	    STATIC_SYMBOL("ALLOCATED-BYTE-VECTOR-16-VECTORS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qallocated_byte_vector_16_vectors,
	    Allocated_byte_vector_16_vectors);
    record_system_variable(Qallocated_byte_vector_16_vectors,Qutilities0,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qbytes_in_allocated_byte_vector_16_vectors = 
	    STATIC_SYMBOL("BYTES-IN-ALLOCATED-BYTE-VECTOR-16-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbytes_in_allocated_byte_vector_16_vectors,
	    Bytes_in_allocated_byte_vector_16_vectors);
    record_system_variable(Qbytes_in_allocated_byte_vector_16_vectors,
	    Qutilities0,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_byte_vector_16_vectors = 
	    STATIC_SYMBOL("OUTSTANDING-BYTE-VECTOR-16-VECTORS",AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_byte_vector_16_vectors,
	    STATIC_FUNCTION(outstanding_byte_vector_16_vectors,NIL,FALSE,0,0));
    Qbyte_vector_16_memory_usage = 
	    STATIC_SYMBOL("BYTE-VECTOR-16-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qbyte_vector_16_memory_usage,
	    STATIC_FUNCTION(byte_vector_16_memory_usage,NIL,FALSE,0,0));
    string_constant_5 = STATIC_STRING("1q83-LBy1m9k1m83oFy3Cy83-JUy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qvector);
    push_optimized_constant(Qoutstanding_byte_vector_16_vectors);
    push_optimized_constant(Qbyte_vector_16_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_5));
    if (Free_malloced_arrays == UNBOUND)
	Free_malloced_arrays = T;
    if (Largest_non_malloced_byte_vector_16_pool_index == UNBOUND)
	Largest_non_malloced_byte_vector_16_pool_index = FIX((SI_Long)-1L);
    if (Byte_vector_16_pool_number_to_malloc == UNBOUND)
	Byte_vector_16_pool_number_to_malloc = FIX((SI_Long)-1L);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
}
