/* gfi.c
 * Input file:  gfi.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "gfi.h"


Object Gfi_designation_for_base_time = UNBOUND;

Object Gfi_designation_for_base_time_string_length = UNBOUND;

Object Gfi_title_for_base_time = UNBOUND;

Object Gfi_title_for_base_time_string_length = UNBOUND;

Object Gfi_input_white_space = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Available_gfi_conses, Qavailable_gfi_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_gfi_conses_tail, Qavailable_gfi_conses_tail);

Object Available_gfi_conses_vector = UNBOUND;

Object Available_gfi_conses_tail_vector = UNBOUND;

Object Gfi_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Gfi_cons_counter, Qgfi_cons_counter);

/* OUTSTANDING-GFI-CONSES */
Object outstanding_gfi_conses()
{
    Object temp;

    x_note_fn_call(217,0);
    temp = FIXNUM_MINUS(Gfi_cons_counter,length(Available_gfi_conses));
    return VALUES_1(temp);
}

/* GFI-CONS-MEMORY-USAGE */
Object gfi_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(217,1);
    temp = FIXNUM_TIMES(Gfi_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-GFI-CONS-POOL */
Object replenish_gfi_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(217,2);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qgfi_cons_counter,Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_gfi_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_gfi_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_gfi_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_gfi_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_gfi_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Gfi_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qgfi;                /* gfi */

/* GFI-CONS-1 */
Object gfi_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(217,3);
    new_cons = ISVREF(Available_gfi_conses_vector,IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_gfi_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_gfi_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_gfi_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_gfi_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qgfi);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-GFI-LIST-POOL */
Object replenish_gfi_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(217,4);
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
    if (ISVREF(Available_gfi_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_gfi_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_gfi_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_gfi_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_gfi_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qgfi_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-GFI-LIST-1 */
Object make_gfi_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(217,5);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_gfi_conses_vector,
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
	replenish_gfi_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_gfi_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qgfi);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_gfi_conses_vector,IFIX(Current_thread_index));
	svref_arg_1 = Available_gfi_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_gfi_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_gfi_conses_tail_vector;
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

/* GFI-LIST-2 */
Object gfi_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(217,6);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_gfi_conses_vector,IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_gfi_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_gfi_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qgfi);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_gfi_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_gfi_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_gfi_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_gfi_conses_tail_vector;
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

/* GFI-LIST-3 */
Object gfi_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(217,7);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_gfi_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_gfi_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_gfi_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qgfi);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_gfi_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_gfi_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_gfi_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_gfi_conses_tail_vector;
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

/* GFI-LIST-4 */
Object gfi_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(217,8);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_gfi_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_gfi_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_gfi_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qgfi);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_gfi_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_gfi_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_gfi_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_gfi_conses_tail_vector;
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

/* GFI-LIST-TRACE-HOOK */
Object gfi_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(217,9);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-GFI-CONSES-1 */
Object copy_tree_using_gfi_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(217,10);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_gfi_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_gfi_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_gfi_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_gfi_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_gfi_cons_pool();
	temp_1 = copy_tree_using_gfi_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qgfi);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_gfi_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_gfi_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_gfi_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_gfi_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_gfi_cons_pool();
	temp_1 = copy_tree_using_gfi_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qgfi);
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

/* COPY-LIST-USING-GFI-CONSES-1 */
Object copy_list_using_gfi_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(217,11);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_gfi_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_gfi_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_gfi_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_gfi_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_gfi_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qgfi);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_gfi_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_gfi_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_gfi_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_gfi_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_gfi_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qgfi);
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

/* RECLAIM-GFI-CONS-1 */
Object reclaim_gfi_cons_1(gfi_cons)
    Object gfi_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(217,12);
    inline_note_reclaim_cons(gfi_cons,Qgfi);
    if (ISVREF(Available_gfi_conses_tail_vector,IFIX(Current_thread_index))) {
	temp = ISVREF(Available_gfi_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = gfi_cons;
	temp = Available_gfi_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = gfi_cons;
    }
    else {
	temp = Available_gfi_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = gfi_cons;
	temp = Available_gfi_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = gfi_cons;
    }
    M_CDR(gfi_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-GFI-LIST-1 */
Object reclaim_gfi_list_1(gfi_list)
    Object gfi_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(217,13);
    if (gfi_list) {
	last_1 = gfi_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qgfi);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qgfi);
	if (ISVREF(Available_gfi_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_gfi_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = gfi_list;
	    temp = Available_gfi_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_gfi_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = gfi_list;
	    temp = Available_gfi_conses_tail_vector;
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

/* RECLAIM-GFI-LIST*-1 */
Object reclaim_gfi_list_star_1(gfi_list)
    Object gfi_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(217,14);
    if (CONSP(gfi_list)) {
	temp = last(gfi_list,_);
	M_CDR(temp) = Nil;
	if (gfi_list) {
	    last_1 = gfi_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qgfi);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qgfi);
	    if (ISVREF(Available_gfi_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_gfi_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = gfi_list;
		temp = Available_gfi_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_gfi_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = gfi_list;
		temp = Available_gfi_conses_tail_vector;
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

/* RECLAIM-GFI-TREE-1 */
Object reclaim_gfi_tree_1(tree)
    Object tree;
{
    Object e, e2, gfi_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(217,15);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_gfi_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		gfi_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(gfi_cons,Qgfi);
		if (EQ(gfi_cons,e))
		    goto end_1;
		else if ( !TRUEP(gfi_cons))
		    goto end_1;
		else
		    gfi_cons = CDR(gfi_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_gfi_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_gfi_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_gfi_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_gfi_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_gfi_conses_tail_vector;
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

/* DELETE-GFI-ELEMENT-1 */
Object delete_gfi_element_1(element,gfi_list)
    Object element, gfi_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(217,16);
    if (gfi_list) {
	if (EQ(element,M_CAR(gfi_list))) {
	    temp = CDR(gfi_list);
	    inline_note_reclaim_cons(gfi_list,Qgfi);
	    if (ISVREF(Available_gfi_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_gfi_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = gfi_list;
		temp_1 = Available_gfi_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = gfi_list;
	    }
	    else {
		temp_1 = Available_gfi_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = gfi_list;
		temp_1 = Available_gfi_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = gfi_list;
	    }
	    M_CDR(gfi_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = gfi_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qgfi);
		if (ISVREF(Available_gfi_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_gfi_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_gfi_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_gfi_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_gfi_conses_tail_vector;
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
	    temp = gfi_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-GFI-CONS-1 */
Object delete_gfi_cons_1(gfi_cons,gfi_list)
    Object gfi_cons, gfi_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(217,17);
    if (EQ(gfi_cons,gfi_list))
	temp = CDR(gfi_list);
    else {
	l_trailer_qm = Nil;
	l = gfi_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,gfi_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = gfi_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_gfi_cons_1(gfi_cons);
    return VALUES_1(temp);
}

Object The_type_description_of_gfi_queue_item = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_gfi_queue_items, Qchain_of_available_gfi_queue_items);

DEFINE_VARIABLE_WITH_SYMBOL(Gfi_queue_item_count, Qgfi_queue_item_count);

Object Chain_of_available_gfi_queue_items_vector = UNBOUND;

/* GFI-QUEUE-ITEM-STRUCTURE-MEMORY-USAGE */
Object gfi_queue_item_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(217,18);
    temp = Gfi_queue_item_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)10L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-GFI-QUEUE-ITEM-COUNT */
Object outstanding_gfi_queue_item_count()
{
    Object def_structure_gfi_queue_item_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(217,19);
    gensymed_symbol = IFIX(Gfi_queue_item_count);
    def_structure_gfi_queue_item_variable = Chain_of_available_gfi_queue_items;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_gfi_queue_item_variable))
	goto end_loop;
    def_structure_gfi_queue_item_variable = 
	    ISVREF(def_structure_gfi_queue_item_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-GFI-QUEUE-ITEM-1 */
Object reclaim_gfi_queue_item_1(gfi_queue_item)
    Object gfi_queue_item;
{
    Object structure_being_reclaimed, temp, thing, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(217,20);
    inline_note_reclaim_cons(gfi_queue_item,Nil);
    structure_being_reclaimed = gfi_queue_item;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      temp = 
	      reclaim_managed_number_or_value_function(ISVREF(gfi_queue_item,
	      (SI_Long)1L));
      SVREF(gfi_queue_item,FIX((SI_Long)1L)) = temp;
      SVREF(gfi_queue_item,FIX((SI_Long)1L)) = Nil;
      temp = 
	      reclaim_managed_number_or_value_function(ISVREF(gfi_queue_item,
	      (SI_Long)2L));
      SVREF(gfi_queue_item,FIX((SI_Long)2L)) = temp;
      SVREF(gfi_queue_item,FIX((SI_Long)2L)) = Nil;
      reclaim_gfi_tree_1(ISVREF(gfi_queue_item,(SI_Long)4L));
      SVREF(gfi_queue_item,FIX((SI_Long)4L)) = Nil;
      thing = ISVREF(gfi_queue_item,(SI_Long)7L);
      if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	  reclaim_wide_string(thing);
      SVREF(gfi_queue_item,FIX((SI_Long)7L)) = Nil;
      reclaim_eval_tree_1(ISVREF(gfi_queue_item,(SI_Long)8L));
      SVREF(gfi_queue_item,FIX((SI_Long)8L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_gfi_queue_items_vector,
	    IFIX(Current_thread_index));
    SVREF(gfi_queue_item,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_gfi_queue_items_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = gfi_queue_item;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GFI-QUEUE-ITEM */
Object reclaim_structure_for_gfi_queue_item(gfi_queue_item)
    Object gfi_queue_item;
{
    x_note_fn_call(217,21);
    return reclaim_gfi_queue_item_1(gfi_queue_item);
}

static Object Qg2_defstruct_structure_name_gfi_queue_item_g2_struct;  /* g2-defstruct-structure-name::gfi-queue-item-g2-struct */

/* MAKE-PERMANENT-GFI-QUEUE-ITEM-STRUCTURE-INTERNAL */
Object make_permanent_gfi_queue_item_structure_internal()
{
    Object def_structure_gfi_queue_item_variable;
    Object defstruct_g2_gfi_queue_item_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(217,22);
    def_structure_gfi_queue_item_variable = Nil;
    atomic_incff_symval(Qgfi_queue_item_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_gfi_queue_item_variable = Nil;
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
	defstruct_g2_gfi_queue_item_variable = the_array;
	SVREF(defstruct_g2_gfi_queue_item_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gfi_queue_item_g2_struct;
	def_structure_gfi_queue_item_variable = 
		defstruct_g2_gfi_queue_item_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_gfi_queue_item_variable);
}

/* MAKE-GFI-QUEUE-ITEM-1 */
Object make_gfi_queue_item_1()
{
    Object def_structure_gfi_queue_item_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(217,23);
    def_structure_gfi_queue_item_variable = 
	    ISVREF(Chain_of_available_gfi_queue_items_vector,
	    IFIX(Current_thread_index));
    if (def_structure_gfi_queue_item_variable) {
	svref_arg_1 = Chain_of_available_gfi_queue_items_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_gfi_queue_item_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_gfi_queue_item_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gfi_queue_item_g2_struct;
    }
    else
	def_structure_gfi_queue_item_variable = 
		make_permanent_gfi_queue_item_structure_internal();
    inline_note_allocate_cons(def_structure_gfi_queue_item_variable,Nil);
    SVREF(def_structure_gfi_queue_item_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_gfi_queue_item_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_gfi_queue_item_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_gfi_queue_item_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_gfi_queue_item_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_gfi_queue_item_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_gfi_queue_item_variable,FIX((SI_Long)9L)) = 
	    Most_negative_fixnum;
    return VALUES_1(def_structure_gfi_queue_item_variable);
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_gfi_spreadsheet_field_index_hash_vector_131_vectors, Qavailable_gfi_spreadsheet_field_index_hash_vector_131_vectors);

DEFINE_VARIABLE_WITH_SYMBOL(Count_of_gfi_spreadsheet_field_index_hash_vector_131_vectors, Qcount_of_gfi_spreadsheet_field_index_hash_vector_131_vectors);

Object Available_gfi_spreadsheet_field_index_hash_vector_131_vectors_vector = UNBOUND;

/* GFI-SPREADSHEET-FIELD-INDEX-HASH-VECTOR-131-VECTOR-MEMORY-USAGE */
Object gfi_spreadsheet_field_index_hash_vector_131_vector_memory_usage()
{
    Object temp;

    x_note_fn_call(217,24);
    temp = Count_of_gfi_spreadsheet_field_index_hash_vector_131_vectors;
    temp = FIXNUM_TIMES(temp,bytes_per_typed_simple_array(T,
	    FIX((SI_Long)131L)));
    return VALUES_1(temp);
}

/* OUT-GFI-SPREADSHEET-FIELD-INDEX-HASH-VECTOR-131-VECTORS */
Object out_gfi_spreadsheet_field_index_hash_vector_131_vectors()
{
    Object temp;

    x_note_fn_call(217,25);
    temp = 
	    FIXNUM_MINUS(Count_of_gfi_spreadsheet_field_index_hash_vector_131_vectors,
	    length(Available_gfi_spreadsheet_field_index_hash_vector_131_vectors));
    return VALUES_1(temp);
}

/* MAKE-PERMANENT-GFI-SPREADSHEET-FIELD-INDEX-HASH-VECTOR-131-VECTOR-INTERNAL */
Object make_permanent_gfi_spreadsheet_field_index_hash_vector_131_vector_internal()
{
    Object temp;
    XDeclare_area(1);

    x_note_fn_call(217,26);
    atomic_incff_symval(Qcount_of_gfi_spreadsheet_field_index_hash_vector_131_vectors,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0))
	temp = make_array(3,FIX((SI_Long)131L),Kinitial_element,Nil);
    POP_AREA(0);
    return VALUES_1(temp);
}

static Object Qvector_pool;        /* vector-pool */

/* MAKE-GFI-SPREADSHEET-FIELD-INDEX-HASH-VECTOR */
Object make_gfi_spreadsheet_field_index_hash_vector()
{
    Object temp, svref_arg_1, svref_arg_2, temp_1, vector_pool_cons, temp_2;
    Object svref_arg_2_1;

    x_note_fn_call(217,27);
    if (ISVREF(Available_gfi_spreadsheet_field_index_hash_vector_131_vectors_vector,
	    IFIX(Current_thread_index))) {
	temp = 
		M_CAR(ISVREF(Available_gfi_spreadsheet_field_index_hash_vector_131_vectors_vector,
		IFIX(Current_thread_index)));
	svref_arg_1 = 
		Available_gfi_spreadsheet_field_index_hash_vector_131_vectors_vector;
	svref_arg_2 = Current_thread_index;
	temp_1 = 
		M_CDR(ISVREF(Available_gfi_spreadsheet_field_index_hash_vector_131_vectors_vector,
		IFIX(Current_thread_index)));
	vector_pool_cons = 
		ISVREF(Available_gfi_spreadsheet_field_index_hash_vector_131_vectors_vector,
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
		make_permanent_gfi_spreadsheet_field_index_hash_vector_131_vector_internal();
    return VALUES_1(temp);
}

/* RECLAIM-GFI-SPREADSHEET-FIELD-INDEX-HASH-VECTOR */
Object reclaim_gfi_spreadsheet_field_index_hash_vector(gfi_spreadsheet_field_index_hash_vector_131_vector)
    Object gfi_spreadsheet_field_index_hash_vector_131_vector;
{
    Object svref_arg_1, svref_arg_2, new_cons, temp, svref_arg_2_1;
    Object svref_new_value, gensymed_symbol;

    x_note_fn_call(217,28);
    svref_arg_1 = 
	    Available_gfi_spreadsheet_field_index_hash_vector_131_vectors_vector;
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
	    gfi_spreadsheet_field_index_hash_vector_131_vector;
    temp = 
	    ISVREF(Available_gfi_spreadsheet_field_index_hash_vector_131_vectors_vector,
	    IFIX(Current_thread_index));
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qvector_pool);
    SVREF(svref_arg_1,svref_arg_2) = gensymed_symbol;
    return VALUES_1(Nil);
}

static Object Qsentinel_node;      /* sentinel-node */

static Object Qhead;               /* head */

static Object Qtail;               /* tail */

/* MAKE-GFI-SPREADSHEET-FIELD-INDEX-TREE-FOR-HASH-SKIP-LIST-SENTINEL */
Object make_gfi_spreadsheet_field_index_tree_for_hash_skip_list_sentinel(hash,
	    tail)
    Object hash, tail;
{
    Object node, next, svref_new_value;
    SI_Long i;

    x_note_fn_call(217,29);
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

/* RECLAIM-GFI-SPREADSHEET-FIELD-INDEX-TREE-FOR-HASH-NODES */
Object reclaim_gfi_spreadsheet_field_index_tree_for_hash_nodes(gfi_spreadsheet_field_index_tree_for_hash_skip_list,
	    tail)
    Object gfi_spreadsheet_field_index_tree_for_hash_skip_list, tail;
{
    Object next_element, key, entry;

    x_note_fn_call(217,30);
    next_element = Nil;
    key = Nil;
    entry = Nil;
  next_loop:
    if (EQ(gfi_spreadsheet_field_index_tree_for_hash_skip_list,tail))
	goto end_loop;
    next_element = 
	    ATOMIC_REF_OBJECT(ISVREF(ISVREF(gfi_spreadsheet_field_index_tree_for_hash_skip_list,
	    (SI_Long)0L),(SI_Long)0L));
    key = ISVREF(gfi_spreadsheet_field_index_tree_for_hash_skip_list,
	    (SI_Long)2L);
    entry = ISVREF(gfi_spreadsheet_field_index_tree_for_hash_skip_list,
	    (SI_Long)3L);
    reclaim_skip_list_element(gfi_spreadsheet_field_index_tree_for_hash_skip_list);
    gfi_spreadsheet_field_index_tree_for_hash_skip_list = next_element;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* CLEAR-GFI-SPREADSHEET-FIELD-INDEX-TREE */
Object clear_gfi_spreadsheet_field_index_tree(gfi_spreadsheet_field_index_tree_for_hash_skip_list)
    Object gfi_spreadsheet_field_index_tree_for_hash_skip_list;
{
    Object head, tail, element_qm;

    x_note_fn_call(217,31);
    head = M_CAR(M_CDR(gfi_spreadsheet_field_index_tree_for_hash_skip_list));
    tail = M_CDR(M_CDR(gfi_spreadsheet_field_index_tree_for_hash_skip_list));
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    if ( !EQ(element_qm,tail))
	reclaim_gfi_spreadsheet_field_index_tree_for_hash_nodes(element_qm,
		tail);
    return VALUES_1(gfi_spreadsheet_field_index_tree_for_hash_skip_list);
}

static Object Qgfi_spreadsheet_field_index_tree_for_hash;  /* gfi-spreadsheet-field-index-tree-for-hash */

static Object Qlookup;             /* lookup */

/* MAKE-GFI-SPREADSHEET-FIELD-INDEX */
Object make_gfi_spreadsheet_field_index()
{
    Object new_vector, tail, head, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol, gensymed_symbol_1, temp;
    SI_Long index_1;

    x_note_fn_call(217,32);
    new_vector = make_gfi_spreadsheet_field_index_hash_vector();
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)131L)
	goto end_loop;
    tail = 
	    make_gfi_spreadsheet_field_index_tree_for_hash_skip_list_sentinel(Most_positive_fixnum,
	    Nil);
    head = 
	    make_gfi_spreadsheet_field_index_tree_for_hash_skip_list_sentinel(Most_negative_fixnum,
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
    M_CAR(gensymed_symbol) = Qgfi_spreadsheet_field_index_tree_for_hash;
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

/* FLATTEN-GFI-SPREADSHEET-FIELD-INDEX */
Object flatten_gfi_spreadsheet_field_index(gfi_spreadsheet_field_index_hash_table)
    Object gfi_spreadsheet_field_index_hash_table;
{
    Object result_1, subtree, temp;
    SI_Long index_1;

    x_note_fn_call(217,33);
    result_1 = Nil;
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)131L)
	goto end_loop;
    subtree = ISVREF(gfi_spreadsheet_field_index_hash_table,index_1);
    if (subtree) {
	temp = flatten_skip_list(CDR(subtree));
	result_1 = nconc2(temp,result_1);
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(result_1);
}

/* CLEAR-GFI-SPREADSHEET-FIELD-INDEX */
Object clear_gfi_spreadsheet_field_index(gfi_spreadsheet_field_index_hash_table)
    Object gfi_spreadsheet_field_index_hash_table;
{
    SI_Long index_1;

    x_note_fn_call(217,34);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)131L)
	goto end_loop;
    clear_gfi_spreadsheet_field_index_tree(ISVREF(gfi_spreadsheet_field_index_hash_table,
	    index_1));
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* RECLAIM-GFI-SPREADSHEET-FIELD-INDEX */
Object reclaim_gfi_spreadsheet_field_index(gfi_spreadsheet_field_index_hash_table)
    Object gfi_spreadsheet_field_index_hash_table;
{
    Object gfi_spreadsheet_field_index_tree_for_hash_skip_list, head, tail;
    Object element_qm, last_1, next_qm, temp, svref_arg_2, temp_1;
    SI_Long index_1;

    x_note_fn_call(217,35);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)131L)
	goto end_loop;
    gfi_spreadsheet_field_index_tree_for_hash_skip_list = 
	    ISVREF(gfi_spreadsheet_field_index_hash_table,index_1);
    head = M_CAR(M_CDR(gfi_spreadsheet_field_index_tree_for_hash_skip_list));
    tail = M_CDR(M_CDR(gfi_spreadsheet_field_index_tree_for_hash_skip_list));
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    if ( !EQ(element_qm,tail))
	reclaim_gfi_spreadsheet_field_index_tree_for_hash_nodes(element_qm,
		tail);
    reclaim_skip_list_element(head);
    reclaim_skip_list_element(tail);
    M_CDDR(gfi_spreadsheet_field_index_tree_for_hash_skip_list) = Nil;
    M_CADR(gfi_spreadsheet_field_index_tree_for_hash_skip_list) = Nil;
    M_CAR(gfi_spreadsheet_field_index_tree_for_hash_skip_list) = Nil;
    if (gfi_spreadsheet_field_index_tree_for_hash_skip_list) {
	last_1 = gfi_spreadsheet_field_index_tree_for_hash_skip_list;
	next_qm = Nil;
      next_loop_1:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop_1;
	inline_note_reclaim_cons(last_1,Qlookup);
	last_1 = next_qm;
	goto next_loop_1;
      end_loop_1:
	inline_note_reclaim_cons(last_1,Qlookup);
	if (ISVREF(Available_lookup_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_lookup_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = gfi_spreadsheet_field_index_tree_for_hash_skip_list;
	    temp = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_lookup_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = 
		    gfi_spreadsheet_field_index_tree_for_hash_skip_list;
	    temp = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    ISVREF(gfi_spreadsheet_field_index_hash_table,index_1) = Nil;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    temp_1 = 
	    reclaim_gfi_spreadsheet_field_index_hash_vector(gfi_spreadsheet_field_index_hash_table);
    return VALUES_1(temp_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Queue_of_active_gfi_output_interface_objects, Qqueue_of_active_gfi_output_interface_objects);

DEFINE_VARIABLE_WITH_SYMBOL(Queue_of_active_gfi_input_interface_objects, Qqueue_of_active_gfi_input_interface_objects);

DEFINE_VARIABLE_WITH_SYMBOL(Queue_of_active_uninterruptable_gfi_output_interface_objects, Qqueue_of_active_uninterruptable_gfi_output_interface_objects);

DEFINE_VARIABLE_WITH_SYMBOL(Queue_of_active_uninterruptable_gfi_input_interface_objects, Qqueue_of_active_uninterruptable_gfi_input_interface_objects);

DEFINE_VARIABLE_WITH_SYMBOL(Time_slice_expired_p, Qtime_slice_expired_p);

/* GFI-DELETE-FROM-QUEUE */
Object gfi_delete_from_queue(key,queue_pair)
    Object key, queue_pair;
{
    Object queue_list, delete_cons, cons_in_front_of_delete_cons, temp;
    Object next_cons, rest_of_list, svref_arg_2;

    x_note_fn_call(217,36);
    queue_list = CAR(queue_pair);
    delete_cons = Nil;
    cons_in_front_of_delete_cons = Nil;
    if (EQ(key,CAR(queue_list))) {
	delete_cons = queue_list;
	temp = CDR(queue_list);
	M_CAR(queue_pair) = temp;
    }
    else {
	next_cons = Nil;
	rest_of_list = queue_list;
      next_loop:
	if ( !TRUEP(rest_of_list))
	    goto end_loop;
	next_cons = CDR(rest_of_list);
	if (next_cons) {
	    if (EQ(key,CAR(next_cons))) {
		cons_in_front_of_delete_cons = rest_of_list;
		delete_cons = next_cons;
		temp = CDR(next_cons);
		M_CDR(rest_of_list) = temp;
		goto end_1;
	    }
	}
	rest_of_list = next_cons;
	goto next_loop;
      end_loop:
      end_1:;
    }
    if (delete_cons) {
	if (EQ(CDR(queue_pair),delete_cons))
	    M_CDR(queue_pair) = cons_in_front_of_delete_cons;
	inline_note_reclaim_cons(delete_cons,Qgfi);
	if (ISVREF(Available_gfi_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_gfi_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = delete_cons;
	    temp = Available_gfi_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = delete_cons;
	}
	else {
	    temp = Available_gfi_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = delete_cons;
	    temp = Available_gfi_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = delete_cons;
	}
	M_CDR(delete_cons) = Nil;
    }
    return VALUES_1(queue_pair);
}

/* RECLAIM-GFI-QUEUE-OF-NEW-OUTPUT-VALUES-CONTENTS */
Object reclaim_gfi_queue_of_new_output_values_contents(queue_pair)
    Object queue_pair;
{
    Object queue_list, item_, rest_of_list_, last_1, next_qm, temp;
    Object svref_arg_2;

    x_note_fn_call(217,37);
    queue_list = CAR(queue_pair);
    if (queue_pair) {
	item_ = Nil;
	rest_of_list_ = queue_list;
      next_loop:
	if ( !TRUEP(rest_of_list_))
	    goto end_loop;
	item_ = CAR(rest_of_list_);
	if (item_)
	    reclaim_gfi_queue_item_1(item_);
	M_CAR(rest_of_list_) = Nil;
	rest_of_list_ = M_CDR(rest_of_list_);
	goto next_loop;
      end_loop:;
	if (queue_list) {
	    last_1 = queue_list;
	    next_qm = Nil;
	  next_loop_1:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop_1;
	    inline_note_reclaim_cons(last_1,Qgfi);
	    last_1 = next_qm;
	    goto next_loop_1;
	  end_loop_1:
	    inline_note_reclaim_cons(last_1,Qgfi);
	    if (ISVREF(Available_gfi_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_gfi_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = queue_list;
		temp = Available_gfi_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_gfi_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = queue_list;
		temp = Available_gfi_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    M_CDR(last_1) = Nil;
	}
	M_CAR(queue_pair) = Nil;
	return VALUES_1(M_CDR(queue_pair) = Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qgfi_output_file_pathname;  /* gfi-output-file-pathname */

static Object Qgfi_output_when_active;  /* gfi-output-when-active */

static Object Qgfi_outputting_qm;  /* gfi-outputting? */

static Object Qno_gfi_output_file_pathname;  /* no-gfi-output-file-pathname */

static Object Qincomplete;         /* incomplete */

/* PUT-GFI-OUTPUT-FILE-PATHNAME */
Object put_gfi_output_file_pathname(frame,new_value,gensymed_symbol)
    Object frame, new_value, gensymed_symbol;
{
    Object gensymed_symbol_1, gensymed_symbol_2, temp;
    char temp_1;

    x_note_fn_call(217,38);
    gensymed_symbol = frame;
    gensymed_symbol_1 = new_value;
    gensymed_symbol_2 = Qgfi_output_file_pathname;
    if ((SI_Long)0L != (IFIX(ISVREF(gensymed_symbol,(SI_Long)5L)) & 
	    (SI_Long)1L) && get_lookup_slot_value(gensymed_symbol,
	    Qgfi_output_when_active) && 
	    get_lookup_slot_value_given_default(gensymed_symbol,
	    Qgfi_outputting_qm,Nil))
	close_gfi_output_interface(gensymed_symbol,T);
    set_slot_value_function(gensymed_symbol,gensymed_symbol_2,
	    gensymed_symbol_1,Nil);
    if ( !TRUEP(new_value)) {
	add_frame_note(2,Qno_gfi_output_file_pathname,frame);
	update_frame_status(frame,Qincomplete,Nil);
    }
    else {
	delete_frame_note_if_any(Qno_gfi_output_file_pathname,frame);
	if (gfi_output_interface_non_default_slots_set_p(frame))
	    update_frame_status(frame,Nil,Nil);
    }
    if ((SI_Long)0L != (IFIX(ISVREF(gensymed_symbol,(SI_Long)5L)) & 
	    (SI_Long)1L) && get_lookup_slot_value(gensymed_symbol,
	    Qgfi_output_when_active)) {
	temp = ISVREF(gensymed_symbol,(SI_Long)8L);
	temp_1 =  !TRUEP(CAR(temp));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	prepare_gfi_output_interface_to_open(gensymed_symbol);
    return VALUES_2(gensymed_symbol_1,Nil);
}

static Object Qrenamed_gfi_output_file_pathname;  /* renamed-gfi-output-file-pathname */

/* PUT-RENAMED-GFI-OUTPUT-FILE-PATHNAME */
Object put_renamed_gfi_output_file_pathname(frame,new_value,gensymed_symbol)
    Object frame, new_value, gensymed_symbol;
{
    Object gensymed_symbol_1, gensymed_symbol_2, temp;
    char temp_1;

    x_note_fn_call(217,39);
    gensymed_symbol = frame;
    gensymed_symbol_1 = new_value;
    gensymed_symbol_2 = Qrenamed_gfi_output_file_pathname;
    if ((SI_Long)0L != (IFIX(ISVREF(gensymed_symbol,(SI_Long)5L)) & 
	    (SI_Long)1L) && get_lookup_slot_value(gensymed_symbol,
	    Qgfi_output_when_active) && 
	    get_lookup_slot_value_given_default(gensymed_symbol,
	    Qgfi_outputting_qm,Nil))
	close_gfi_output_interface(gensymed_symbol,T);
    set_slot_value_function(gensymed_symbol,gensymed_symbol_2,
	    gensymed_symbol_1,Nil);
    if ((SI_Long)0L != (IFIX(ISVREF(gensymed_symbol,(SI_Long)5L)) & 
	    (SI_Long)1L) && get_lookup_slot_value(gensymed_symbol,
	    Qgfi_output_when_active)) {
	temp = ISVREF(gensymed_symbol,(SI_Long)8L);
	temp_1 =  !TRUEP(CAR(temp));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	prepare_gfi_output_interface_to_open(gensymed_symbol);
    return VALUES_2(gensymed_symbol_1,Nil);
}

static Object Qgfi_output_file_format;  /* gfi-output-file-format */

/* PUT-GFI-OUTPUT-FILE-FORMAT */
Object put_gfi_output_file_format(frame,new_value,gensymed_symbol)
    Object frame, new_value, gensymed_symbol;
{
    Object gensymed_symbol_1, gensymed_symbol_2, temp;
    char temp_1;

    x_note_fn_call(217,40);
    gensymed_symbol = frame;
    gensymed_symbol_1 = new_value;
    gensymed_symbol_2 = Qgfi_output_file_format;
    if ((SI_Long)0L != (IFIX(ISVREF(gensymed_symbol,(SI_Long)5L)) & 
	    (SI_Long)1L) && get_lookup_slot_value(gensymed_symbol,
	    Qgfi_output_when_active) && 
	    get_lookup_slot_value_given_default(gensymed_symbol,
	    Qgfi_outputting_qm,Nil))
	close_gfi_output_interface(gensymed_symbol,T);
    set_slot_value_function(gensymed_symbol,gensymed_symbol_2,
	    gensymed_symbol_1,Nil);
    if ((SI_Long)0L != (IFIX(ISVREF(gensymed_symbol,(SI_Long)5L)) & 
	    (SI_Long)1L) && get_lookup_slot_value(gensymed_symbol,
	    Qgfi_output_when_active)) {
	temp = ISVREF(gensymed_symbol,(SI_Long)8L);
	temp_1 =  !TRUEP(CAR(temp));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	prepare_gfi_output_interface_to_open(gensymed_symbol);
    return VALUES_2(gensymed_symbol_1,Nil);
}

static Object Qgfi_output_time_stamp_format;  /* gfi-output-time-stamp-format */

/* PUT-GFI-OUTPUT-TIME-STAMP-FORMAT */
Object put_gfi_output_time_stamp_format(frame,new_value,gensymed_symbol)
    Object frame, new_value, gensymed_symbol;
{
    Object gensymed_symbol_1, gensymed_symbol_2, temp;
    char temp_1;

    x_note_fn_call(217,41);
    gensymed_symbol = frame;
    gensymed_symbol_1 = new_value;
    gensymed_symbol_2 = Qgfi_output_time_stamp_format;
    if ((SI_Long)0L != (IFIX(ISVREF(gensymed_symbol,(SI_Long)5L)) & 
	    (SI_Long)1L) && get_lookup_slot_value(gensymed_symbol,
	    Qgfi_output_when_active) && 
	    get_lookup_slot_value_given_default(gensymed_symbol,
	    Qgfi_outputting_qm,Nil))
	close_gfi_output_interface(gensymed_symbol,T);
    set_slot_value_function(gensymed_symbol,gensymed_symbol_2,
	    gensymed_symbol_1,Nil);
    if ((SI_Long)0L != (IFIX(ISVREF(gensymed_symbol,(SI_Long)5L)) & 
	    (SI_Long)1L) && get_lookup_slot_value(gensymed_symbol,
	    Qgfi_output_when_active)) {
	temp = ISVREF(gensymed_symbol,(SI_Long)8L);
	temp_1 =  !TRUEP(CAR(temp));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	prepare_gfi_output_interface_to_open(gensymed_symbol);
    return VALUES_2(gensymed_symbol_1,Nil);
}

static Object Qgfi_output_file_update_frequency;  /* gfi-output-file-update-frequency */

static Object Qno_gfi_output_update_frequency;  /* no-gfi-output-update-frequency */

static Object Qoutput_one_shot_when_activated_without_interruption;  /* output-one-shot-when-activated-without-interruption */

static Object Qgfi_output_without_interruption_qm;  /* gfi-output-without-interruption? */

/* PUT-GFI-OUTPUT-FILE-UPDATE-FREQUENCY */
Object put_gfi_output_file_update_frequency(frame,new_value,gensymed_symbol)
    Object frame, new_value, gensymed_symbol;
{
    Object gensymed_symbol_1, gensymed_symbol_2, temp;
    char temp_1;

    x_note_fn_call(217,42);
    gensymed_symbol = frame;
    gensymed_symbol_1 = new_value;
    gensymed_symbol_2 = Qgfi_output_file_update_frequency;
    if ((SI_Long)0L != (IFIX(ISVREF(gensymed_symbol,(SI_Long)5L)) & 
	    (SI_Long)1L) && get_lookup_slot_value(gensymed_symbol,
	    Qgfi_output_when_active) && 
	    get_lookup_slot_value_given_default(gensymed_symbol,
	    Qgfi_outputting_qm,Nil))
	close_gfi_output_interface(gensymed_symbol,T);
    set_slot_value_function(gensymed_symbol,gensymed_symbol_2,
	    gensymed_symbol_1,Nil);
    if ( !TRUEP(new_value)) {
	add_frame_note(2,Qno_gfi_output_update_frequency,frame);
	update_frame_status(frame,Qincomplete,Nil);
    }
    else {
	delete_frame_note_if_any(Qno_gfi_output_update_frequency,frame);
	if (gfi_output_interface_non_default_slots_set_p(frame))
	    update_frame_status(frame,Nil,Nil);
	if (EQ(new_value,Qoutput_one_shot_when_activated_without_interruption))
	    change_slot_value(3,frame,Qgfi_output_without_interruption_qm,T);
	else
	    change_slot_value(3,frame,Qgfi_output_without_interruption_qm,Nil);
    }
    if ((SI_Long)0L != (IFIX(ISVREF(gensymed_symbol,(SI_Long)5L)) & 
	    (SI_Long)1L) && get_lookup_slot_value(gensymed_symbol,
	    Qgfi_output_when_active)) {
	temp = ISVREF(gensymed_symbol,(SI_Long)8L);
	temp_1 =  !TRUEP(CAR(temp));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	prepare_gfi_output_interface_to_open(gensymed_symbol);
    return VALUES_2(gensymed_symbol_1,Nil);
}

static Object Qgfi_output_values;  /* gfi-output-values */

static Object Qgfi_output_not_unique_designation_p_results;  /* gfi-output-not-unique-designation-p-results */

static Object Qno_gfi_output_values;  /* no-gfi-output-values */

/* PUT-GFI-OUTPUT-VALUES */
Object put_gfi_output_values(frame,new_value,gensymed_symbol)
    Object frame, new_value, gensymed_symbol;
{
    Object gensymed_symbol_1, gensymed_symbol_2, gfi_output_frame;
    Object designations, new_not_unique_designation_p_results;
    Object tail_of_not_unique_designation_p_results, designation;
    Object ab_loop_list_, temp;
    char gensymed_symbol_3, temp_1;

    x_note_fn_call(217,43);
    gensymed_symbol = frame;
    gensymed_symbol_1 = new_value;
    gensymed_symbol_2 = Qgfi_output_values;
    if ((SI_Long)0L != (IFIX(ISVREF(gensymed_symbol,(SI_Long)5L)) & 
	    (SI_Long)1L) && get_lookup_slot_value(gensymed_symbol,
	    Qgfi_output_when_active) && 
	    get_lookup_slot_value_given_default(gensymed_symbol,
	    Qgfi_outputting_qm,Nil))
	close_gfi_output_interface(gensymed_symbol,T);
    set_slot_value_function(gensymed_symbol,gensymed_symbol_2,
	    gensymed_symbol_1,Nil);
    gfi_output_frame = frame;
    designations = CAR(new_value);
    if (get_lookup_slot_value_given_default(gfi_output_frame,
	    Qgfi_output_not_unique_designation_p_results,Nil)) {
	reclaim_gfi_list_1(get_lookup_slot_value_given_default(gfi_output_frame,
		Qgfi_output_not_unique_designation_p_results,Nil));
	set_non_savable_lookup_slot_value(gfi_output_frame,
		Qgfi_output_not_unique_designation_p_results,Nil);
    }
    new_not_unique_designation_p_results = Nil;
    tail_of_not_unique_designation_p_results = Nil;
    designation = Nil;
    ab_loop_list_ = designations;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    designation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol_3 =  !TRUEP(unique_designation_p(designation));
    gensymed_symbol_2 = gfi_cons_1(gensymed_symbol_3 ? T : Nil,Nil);
    if (new_not_unique_designation_p_results) {
	if ( !TRUEP(tail_of_not_unique_designation_p_results))
	    tail_of_not_unique_designation_p_results = 
		    last(new_not_unique_designation_p_results,_);
	M_CDR(tail_of_not_unique_designation_p_results) = gensymed_symbol_2;
    }
    else
	new_not_unique_designation_p_results = gensymed_symbol_2;
    tail_of_not_unique_designation_p_results = gensymed_symbol_2;
    goto next_loop;
  end_loop:
    set_non_savable_lookup_slot_value(gfi_output_frame,
	    Qgfi_output_not_unique_designation_p_results,
	    new_not_unique_designation_p_results);
    if ( !TRUEP(new_value) || LISTP(new_value) &&  !TRUEP(FIRST(new_value))) {
	add_frame_note(2,Qno_gfi_output_values,frame);
	update_frame_status(frame,Qincomplete,Nil);
    }
    else {
	delete_frame_note_if_any(Qno_gfi_output_values,frame);
	if (gfi_output_interface_non_default_slots_set_p(frame))
	    update_frame_status(frame,Nil,Nil);
    }
    if ((SI_Long)0L != (IFIX(ISVREF(gensymed_symbol,(SI_Long)5L)) & 
	    (SI_Long)1L) && get_lookup_slot_value(gensymed_symbol,
	    Qgfi_output_when_active)) {
	temp = ISVREF(gensymed_symbol,(SI_Long)8L);
	temp_1 =  !TRUEP(CAR(temp));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	prepare_gfi_output_interface_to_open(gensymed_symbol);
    return VALUES_2(gensymed_symbol_1,Nil);
}

/* PUT-GFI-OUTPUT-WHEN-ACTIVE */
Object put_gfi_output_when_active(frame,new_value,gensymed_symbol)
    Object frame, new_value, gensymed_symbol;
{
    Object gensymed_symbol_1, gensymed_symbol_2, temp;
    char temp_1;

    x_note_fn_call(217,44);
    gensymed_symbol = frame;
    gensymed_symbol_1 = new_value;
    gensymed_symbol_2 = Qgfi_output_when_active;
    if ((SI_Long)0L != (IFIX(ISVREF(gensymed_symbol,(SI_Long)5L)) & 
	    (SI_Long)1L) && get_lookup_slot_value(gensymed_symbol,
	    Qgfi_output_when_active) && 
	    get_lookup_slot_value_given_default(gensymed_symbol,
	    Qgfi_outputting_qm,Nil))
	close_gfi_output_interface(gensymed_symbol,T);
    set_slot_value_function(gensymed_symbol,gensymed_symbol_2,
	    gensymed_symbol_1,Nil);
    if ((SI_Long)0L != (IFIX(ISVREF(gensymed_symbol,(SI_Long)5L)) & 
	    (SI_Long)1L) && get_lookup_slot_value(gensymed_symbol,
	    Qgfi_output_when_active)) {
	temp = ISVREF(gensymed_symbol,(SI_Long)8L);
	temp_1 =  !TRUEP(CAR(temp));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	prepare_gfi_output_interface_to_open(gensymed_symbol);
    return VALUES_2(gensymed_symbol_1,Nil);
}

static Object Qfile_status;        /* file-status */

/* PUT-FILE-STATUS */
Object put_file_status(interface_object,status_symbol,initializing_qm)
    Object interface_object, status_symbol, initializing_qm;
{
    Object old_status;

    x_note_fn_call(217,45);
    old_status = get_slot_value_function(interface_object,Qfile_status,Nil);
    set_slot_value_function(interface_object,Qfile_status,status_symbol,Nil);
    invoke_rules_for_attribute_change_chaining(interface_object,
	    Qfile_status,old_status,Nil);
    return VALUES_2(status_symbol,Nil);
}

/* RECLAIM-GFI-OUTPUT-VALUES-VALUE */
Object reclaim_gfi_output_values_value(slot_value,frame)
    Object slot_value, frame;
{
    x_note_fn_call(217,46);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,Qgfi_output_values);
    set_lookup_slot_value_1(frame,Qgfi_output_values,Nil);
    reclaim_slot_value(slot_value);
    return VALUES_1(Nil);
}

static Object Qgfi_list_of_new_spreadsheet_output_values;  /* gfi-list-of-new-spreadsheet-output-values */

/* RECLAIM-GFI-LIST-OF-NEW-SPREADSHEET-OUTPUT-VALUES-VALUE */
Object reclaim_gfi_list_of_new_spreadsheet_output_values_value(slot_value,
	    frame)
    Object slot_value, frame;
{
    Object managed_value_qm, ab_loop_list_;

    x_note_fn_call(217,47);
    set_non_savable_lookup_slot_value(frame,
	    Qgfi_list_of_new_spreadsheet_output_values,Nil);
    if (LISTP(slot_value)) {
	managed_value_qm = Nil;
	ab_loop_list_ = slot_value;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	managed_value_qm = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (managed_value_qm)
	    managed_value_qm = 
		    reclaim_managed_number_or_value_function(managed_value_qm);
	goto next_loop;
      end_loop:;
	reclaim_gfi_list_1(slot_value);
    }
    return VALUES_1(Nil);
}

/* RECLAIM-GFI-OUTPUT-NOT-UNIQUE-DESIGNATION-P-RESULTS-VALUE */
Object reclaim_gfi_output_not_unique_designation_p_results_value(value_qm,
	    frame)
    Object value_qm, frame;
{
    x_note_fn_call(217,48);
    set_non_savable_lookup_slot_value(frame,
	    Qgfi_output_not_unique_designation_p_results,Nil);
    if (value_qm)
	reclaim_gfi_list_1(value_qm);
    return VALUES_1(Nil);
}

static Object Qgfi_output_spreadsheet_field_index_hash;  /* gfi-output-spreadsheet-field-index-hash */

/* RECLAIM-GFI-OUTPUT-SPREADSHEET-FIELD-INDEX-HASH-VALUE */
Object reclaim_gfi_output_spreadsheet_field_index_hash_value(value_qm,frame)
    Object value_qm, frame;
{
    x_note_fn_call(217,49);
    set_non_savable_lookup_slot_value(frame,
	    Qgfi_output_spreadsheet_field_index_hash,Nil);
    if (value_qm)
	reclaim_gfi_spreadsheet_field_index(value_qm);
    return VALUES_1(Nil);
}

static Object Qgfi_output_unique_designations;  /* gfi-output-unique-designations */

/* RECLAIM-GFI-OUTPUT-UNIQUE-DESIGNATIONS-VALUE */
Object reclaim_gfi_output_unique_designations_value(value,gfi_output_frame)
    Object value, gfi_output_frame;
{
    x_note_fn_call(217,50);
    set_non_savable_lookup_slot_value(gfi_output_frame,
	    Qgfi_output_unique_designations,Nil);
    if (value)
	reclaim_eval_tree_1(value);
    return VALUES_1(Nil);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object string_constant;     /* "~ND is not a variable or parameter, but it was specified ~
				    * ? as an output value for the GFI Output Interface ~NF."
				    */

static Object string_constant_1;   /* "Could not find the value of ~ND in the GFI Output Interface ~NF." */

/* WARNING-MESSAGE-FOR-WRONG-REFERENCE-FOR-GFI-DESIGNATION */
Object warning_message_for_wrong_reference_for_gfi_designation(gfi_output_frame,
	    designation_that_should_refer_to_variable,
	    thing_that_should_be_variable)
    Object gfi_output_frame, designation_that_should_refer_to_variable;
    Object thing_that_should_be_variable;
{
    Object x2;
    char temp;

    x_note_fn_call(217,51);
    if (SIMPLE_VECTOR_P(thing_that_should_be_variable) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing_that_should_be_variable)) 
	    > (SI_Long)2L &&  !EQ(ISVREF(thing_that_should_be_variable,
	    (SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(thing_that_should_be_variable,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	Suppress_warning_message_header_qm = T;
	if ((SI_Long)2L <= IFIX(Warning_message_level))
	    give_warning_1(4,FIX((SI_Long)2L),string_constant,
		    designation_that_should_refer_to_variable,
		    gfi_output_frame);
	Suppress_warning_message_header_qm = Nil;
	return VALUES_1(Suppress_warning_message_header_qm);
    }
    else {
	Suppress_warning_message_header_qm = T;
	if ((SI_Long)2L <= IFIX(Warning_message_level))
	    give_warning_1(4,FIX((SI_Long)2L),string_constant_1,
		    designation_that_should_refer_to_variable,
		    gfi_output_frame);
	Suppress_warning_message_header_qm = Nil;
	return VALUES_1(Suppress_warning_message_header_qm);
    }
}

static Object string_constant_2;   /* "\"~ND\"" */

static Object string_constant_3;   /* "a designation in the GFI interface" */

static Object string_constant_4;   /* "The GFI Output Interface ~NF found a variable or parameter, ~
				    *        ~NF, which matches ~A.  However, the variable cannot be ~
				    *        referenced with respect to a named item, and thus will be ~
				    *        ignored by GFI."
				    */

/* WARNING-MESSAGE-FOR-UNNAMEABLE-VARIABLE */
Object warning_message_for_unnameable_variable(gfi_output_frame,
	    name_or_variable_or_parameter,designation_qm)
    Object gfi_output_frame, name_or_variable_or_parameter, designation_qm;
{
    Object designation_or_substitute_string;

    x_note_fn_call(217,52);
    designation_or_substitute_string = tformat_text_string(2,
	    designation_qm ? string_constant_2 : string_constant_3,
	    designation_qm);
    Suppress_warning_message_header_qm = T;
    if ((SI_Long)2L <= IFIX(Warning_message_level))
	give_warning_1(5,FIX((SI_Long)2L),string_constant_4,
		gfi_output_frame,name_or_variable_or_parameter,
		designation_or_substitute_string);
    Suppress_warning_message_header_qm = Nil;
    return reclaim_text_string(designation_or_substitute_string);
}

static Object Qg2_defstruct_structure_name_temporary_constant_g2_struct;  /* g2-defstruct-structure-name::temporary-constant-g2-struct */

static Object string_constant_5;   /* "~NC is not a variable or parameter.  This output value for the ~
				    *          GFI Output Interface, ~NF, cannot be written."
				    */

static Object string_constant_6;   /* "The GFI Output Interface, ~NF, cannot write a value.  The output ~
				    *          value was not a variable or parameter."
				    */

/* WARNING-MESSAGE-FOR-NON-FRAME-REFERENCE-FOR-GFI-DESIGNATION */
Object warning_message_for_non_frame_reference_for_gfi_designation(gfi_output_frame,
	    temporary_constant_qm)
    Object gfi_output_frame, temporary_constant_qm;
{
    Object managed_number_or_value, temp;

    x_note_fn_call(217,53);
    if (SIMPLE_VECTOR_P(temporary_constant_qm) && 
	    EQ(ISVREF(temporary_constant_qm,(SI_Long)0L),
	    Qg2_defstruct_structure_name_temporary_constant_g2_struct)) {
	if ((SI_Long)2L <= IFIX(Warning_message_level)) {
	    managed_number_or_value = ISVREF(temporary_constant_qm,
		    (SI_Long)1L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		temp = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		temp = aref1(managed_number_or_value,FIX((SI_Long)0L));
	    else
		temp = managed_number_or_value;
	    return give_warning_1(5,FIX((SI_Long)2L),string_constant_5,
		    temp,ISVREF(temporary_constant_qm,(SI_Long)2L),
		    gfi_output_frame);
	}
	else
	    return VALUES_1(Nil);
    }
    else if ((SI_Long)2L <= IFIX(Warning_message_level))
	return give_warning_1(3,FIX((SI_Long)2L),string_constant_6,
		gfi_output_frame);
    else
	return VALUES_1(Nil);
}

static Object list_constant;       /* # */

static Object Qhandle_gfi_output_interface_new_values;  /* handle-gfi-output-interface-new-values */

/* INSTALL-GFI-TRUE-VALUE-UPDATE */
Object install_gfi_true_value_update(gfi_output_frame,e_designations,
	    not_unique_designation_results)
    Object gfi_output_frame, e_designations, not_unique_designation_results;
{
    Object install_qm, hash_table_qm, eval_list_of_designations_for_installing;
    Object tail_of_eval_list_of_designations_for_installing, position_1;
    Object designation_position_pair, designation, ab_loop_list_;
    Object rest_of_not_unique_designation_results, not_unique_designation_p;
    Object ab_loop_iter_flag_, current_computation_frame;
    Object eval_list_of_designation_values, designation_value, ab_loop_list__1;
    Object x2, sub_class_bit_vector, generated_designation_qm, temp_1;
    Object gensymed_symbol_3;
    SI_Long number_of_unique_designations, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol, gensymed_symbol_1;
    SI_Long gensymed_symbol_2, temp_2;
    char temp;
    Declare_special(1);

    x_note_fn_call(217,54);
    number_of_unique_designations = (SI_Long)0L;
    install_qm = memq_function(get_lookup_slot_value(gfi_output_frame,
	    Qgfi_output_file_update_frequency),list_constant);
    hash_table_qm = get_lookup_slot_value_given_default(gfi_output_frame,
	    Qgfi_output_spreadsheet_field_index_hash,Nil);
    eval_list_of_designations_for_installing = Nil;
    tail_of_eval_list_of_designations_for_installing = Nil;
    if ( !TRUEP(hash_table_qm)) {
	hash_table_qm = make_gfi_spreadsheet_field_index();
	set_non_savable_lookup_slot_value(gfi_output_frame,
		Qgfi_output_spreadsheet_field_index_hash,hash_table_qm);
    }
    clear_gfi_spreadsheet_field_index(hash_table_qm);
    position_1 = FIX((SI_Long)0L);
    designation_position_pair = gfi_cons_1(Nil,Nil);
    designation = Nil;
    ab_loop_list_ = e_designations;
    rest_of_not_unique_designation_results = not_unique_designation_results;
    not_unique_designation_p = Nil;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    designation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	rest_of_not_unique_designation_results = 
		M_CDR(rest_of_not_unique_designation_results);
    if ( !TRUEP(rest_of_not_unique_designation_results))
	goto end_loop;
    not_unique_designation_p = CAR(rest_of_not_unique_designation_results);
    M_CAR(designation_position_pair) = designation;
    if (not_unique_designation_p) {
	M_CDR(designation_position_pair) = Nil;
	number_of_unique_designations = (SI_Long)0L;
	current_computation_frame = gfi_output_frame;
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		0);
	  eval_list_of_designation_values = 
		  serve_eval_list_of_designation_values(designation);
	POP_SPECIAL();
	designation_value = Nil;
	ab_loop_list__1 = eval_list_of_designation_values;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	designation_value = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if (SIMPLE_VECTOR_P(designation_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(designation_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(designation_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(designation_value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(designation_value,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Variable_or_parameter_class_description,
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
	    generated_designation_qm = 
		    generate_designation_for_block(designation_value);
	    if (generated_designation_qm) {
		gensymed_symbol = IFIX(frame_hash_function(designation_value));
		temp_1 = hash_table_qm;
		temp_2 = gensymed_symbol % (SI_Long)131L;
		set_skip_list_entry(SVREF(temp_1,FIX(temp_2)),
			FIX((SI_Long)31L),Qeq,Nil,T,designation_value,
			FIX(gensymed_symbol),position_1);
		gensymed_symbol_3 = generated_designation_qm;
		gensymed_symbol_3 = eval_cons_1(gensymed_symbol_3,Nil);
		if (eval_list_of_designations_for_installing) {
		    if ( 
			    !TRUEP(tail_of_eval_list_of_designations_for_installing))
			tail_of_eval_list_of_designations_for_installing = 
				last(eval_list_of_designations_for_installing,
				_);
		    M_CDR(tail_of_eval_list_of_designations_for_installing) 
			    = gensymed_symbol_3;
		}
		else
		    eval_list_of_designations_for_installing = 
			    gensymed_symbol_3;
		tail_of_eval_list_of_designations_for_installing = 
			gensymed_symbol_3;
		number_of_unique_designations = 
			number_of_unique_designations + (SI_Long)1L;
		position_1 = FIXNUM_ADD1(position_1);
	    }
	    else
		warning_message_for_unnameable_variable(gfi_output_frame,
			designation_value,designation);
	}
	else {
	    warning_message_for_wrong_reference_for_gfi_designation(gfi_output_frame,
		    designation,designation_value);
	    reclaim_if_temporary_constant_function(designation_value);
	}
	goto next_loop_1;
      end_loop_1:
	reclaim_eval_list_1(eval_list_of_designation_values);
	M_CAR(rest_of_not_unique_designation_results) = 
		FIX(number_of_unique_designations);
    }
    else {
	M_CDR(designation_position_pair) = position_1;
	gensymed_symbol_3 = copy_tree_using_eval_conses_1(designation);
	gensymed_symbol_3 = eval_cons_1(gensymed_symbol_3,Nil);
	if (eval_list_of_designations_for_installing) {
	    if ( !TRUEP(tail_of_eval_list_of_designations_for_installing))
		tail_of_eval_list_of_designations_for_installing = 
			last(eval_list_of_designations_for_installing,_);
	    M_CDR(tail_of_eval_list_of_designations_for_installing) = 
		    gensymed_symbol_3;
	}
	else
	    eval_list_of_designations_for_installing = gensymed_symbol_3;
	tail_of_eval_list_of_designations_for_installing = gensymed_symbol_3;
	position_1 = FIXNUM_ADD1(position_1);
    }
    if (install_qm)
	install_true_value_update(Qhandle_gfi_output_interface_new_values,
		gfi_output_frame,designation_position_pair,Nil,designation);
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    reclaim_gfi_cons_1(designation_position_pair);
    return VALUES_1(eval_list_of_designations_for_installing);
}

/* DEINSTALL-GFI-TRUE-VALUE-UPDATE */
Object deinstall_gfi_true_value_update(gfi_output_frame,e_designations,
	    not_unique_designation_results)
    Object gfi_output_frame, e_designations, not_unique_designation_results;
{
    Object position_1, designation_position_pair, e_designation, ab_loop_list_;
    Object not_unique_designation_p, ab_loop_list__1, incff_1_arg;

    x_note_fn_call(217,55);
    if (memq_function(get_lookup_slot_value(gfi_output_frame,
	    Qgfi_output_file_update_frequency),list_constant)) {
	position_1 = FIX((SI_Long)0L);
	designation_position_pair = gfi_cons_1(Nil,Nil);
	e_designation = Nil;
	ab_loop_list_ = e_designations;
	not_unique_designation_p = Nil;
	ab_loop_list__1 = not_unique_designation_results;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	e_designation = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop;
	not_unique_designation_p = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	M_CAR(designation_position_pair) = e_designation;
	if (not_unique_designation_p) {
	    M_CDR(designation_position_pair) = Nil;
	    incff_1_arg = not_unique_designation_p;
	    position_1 = FIXNUM_ADD(position_1,incff_1_arg);
	}
	else {
	    M_CDR(designation_position_pair) = position_1;
	    position_1 = FIXNUM_ADD1(position_1);
	}
	install_true_value_update(Qhandle_gfi_output_interface_new_values,
		gfi_output_frame,designation_position_pair,e_designation,Nil);
	goto next_loop;
      end_loop:
	reclaim_gfi_cons_1(designation_position_pair);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qtext;               /* text */

static Object array_constant;      /* # */

static Object Qnone;               /* none */

static Object string_constant_7;   /* "The variable or parameter which is supposed to hold a ~
				    * ? ?      pathname in the GFI ~A Interface ~NF, ~ND, does not ~
				    * ??      have a valid value.  (It should be a string.)"
				    */

static Object Qgfi_input_file_pathname;  /* gfi-input-file-pathname */

static Object array_constant_1;    /* # */

static Object array_constant_2;    /* # */

static Object Qvalue_request_pending;  /* value-request-pending */

static Object string_constant_8;   /* "The variable or parameter which is supposed to hold a ~
				    *  ?? pathname in the GFI ~A Interface ~NF, ~ND, does not exist."
				    */

/* GET-PATHNAME-FOR-GFI-INTERFACE */
Object get_pathname_for_gfi_interface(gfi_interface_frame,
	    slot_name_for_pathname)
    Object gfi_interface_frame, slot_name_for_pathname;
{
    Object pathname_1, current_computation_frame;
    volatile Object value_to_return;
    Object parameter_or_variable_qm, current_computation_instance;
    Object current_computation_flags;
    volatile Object gensymed_symbol;
    Object variables_that_did_not_have_values, current_value, expiration_time;
    Object data_type, gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object pruned_interest_list, eval_cons, temp, svref_arg_2;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(5);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(217,56);
    SAVE_STACK();
    pathname_1 = get_slot_value_function(gfi_interface_frame,
	    slot_name_for_pathname,Nil);
    if (text_string_p(pathname_1)) {
	result = copy_text_string(pathname_1);
	RESTORE_STACK();
	return result;
    }
    else if (ATOM(pathname_1) ? pathname_1 && SYMBOLP(pathname_1) : 
	    TRUEP(designation_operator_or_giver_of_value_p(CAR(pathname_1)))) {
	current_computation_frame = gfi_interface_frame;
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		4);
	  value_to_return = Nil;
	  parameter_or_variable_qm = evaluate_designation(pathname_1,Nil);
	  if (parameter_or_variable_qm) {
	      current_computation_frame = parameter_or_variable_qm;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		      3);
		current_computation_instance = Current_computation_frame;
		PUSH_SPECIAL_WITH_SYMBOL(Current_computation_instance,Qcurrent_computation_instance,current_computation_instance,
			2);
		  current_computation_flags = Current_computation_flags;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
			  1);
		    Current_computation_flags = 
			    FIX(IFIX(Current_computation_flags) &  
			    ~(SI_Long)4L);
		    Current_computation_flags = 
			    FIX(IFIX(Current_computation_flags) | 
			    (SI_Long)256L);
		    gensymed_symbol = Nil;
		    if (PUSH_UNWIND_PROTECT(0)) {
			variables_that_did_not_have_values = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Variables_that_did_not_have_values,Qvariables_that_did_not_have_values,variables_that_did_not_have_values,
				0);
			  if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
			      result = get_current_value(Current_computation_frame,
				      Nil);
			      MVS_3(result,current_value,expiration_time,
				      data_type);
			      if (expiration_time && EQ(data_type,Qtext) 
				      && text_string_p(current_value)) {
				  if ( !TRUEP(string_equalw(current_value,
					  array_constant)))
				      value_to_return = 
					      copy_text_string(current_value);
			      }
			      else if (expiration_time && EQ(data_type,
				      Qsymbol) && EQ(current_value,Qnone));
			      else {
				  Suppress_warning_message_header_qm = T;
				  if ((SI_Long)2L <= 
					  IFIX(Warning_message_level))
				      give_warning_1(5,FIX((SI_Long)2L),
					      string_constant_7,
					      EQ(slot_name_for_pathname,
					      Qgfi_input_file_pathname) ? 
					      array_constant_1 : 
					      array_constant_2,
					      gfi_interface_frame,pathname_1);
				  Suppress_warning_message_header_qm = Nil;
			      }
			      if (expiration_time && 
				      text_string_p(current_value))
				  reclaim_text_string(current_value);
			  }
			  POP_LOCAL_ALLOCATION(0,0);
			  gensymed_symbol = Variables_that_did_not_have_values;
			POP_SPECIAL();
		    }
		    POP_UNWIND_PROTECT(0);
		    if (gensymed_symbol) {
			gensymed_symbol_1 = gensymed_symbol;
			gensymed_symbol_2 = Nil;
			gensymed_symbol_3 = Nil;
		      next_loop:
			gensymed_symbol_2 = CAR(gensymed_symbol_1);
			gensymed_symbol_3 = CDR(gensymed_symbol_1);
			pruned_interest_list = 
				delete_eval_element_1(Qvalue_request_pending,
				ISVREF(gensymed_symbol_2,(SI_Long)36L));
			ISVREF(gensymed_symbol_2,(SI_Long)36L) = 
				pruned_interest_list;
			if ( !TRUEP(pruned_interest_list) &&  
				!TRUEP(ISVREF(gensymed_symbol_2,(SI_Long)38L)))
			    withdraw_backward_chaining(gensymed_symbol_2);
			if ( !TRUEP(gensymed_symbol_3))
			    goto end_loop;
			gensymed_symbol_1 = gensymed_symbol_3;
			goto next_loop;
		      end_loop:
			if (gensymed_symbol &&  !((SI_Long)0L == 
				inline_debugging_consing())) {
			    eval_cons = gensymed_symbol;
			  next_loop_1:
			    inline_note_reclaim_cons(eval_cons,Qeval);
			    if (EQ(eval_cons,gensymed_symbol_1))
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
			    temp = 
				    ISVREF(Available_eval_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp) = gensymed_symbol;
			    temp = Available_eval_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp,svref_arg_2) = gensymed_symbol_1;
			}
			else {
			    temp = Available_eval_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp,svref_arg_2) = gensymed_symbol;
			    temp = Available_eval_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp,svref_arg_2) = gensymed_symbol_1;
			}
			M_CDR(gensymed_symbol_1) = Nil;
		    }
		    CONTINUE_UNWINDING(0);
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	  }
	  else {
	      Suppress_warning_message_header_qm = T;
	      if ((SI_Long)2L <= IFIX(Warning_message_level))
		  give_warning_1(5,FIX((SI_Long)2L),string_constant_8,
			  EQ(slot_name_for_pathname,
			  Qgfi_input_file_pathname) ? array_constant_1 : 
			  array_constant_2,gfi_interface_frame,pathname_1);
	      Suppress_warning_message_header_qm = Nil;
	  }
	  result = VALUES_1(value_to_return);
	POP_SPECIAL();
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

static Object string_constant_9;   /* "Maximum number of output lines has been reached for GFI Output ~
				    *      Interface ~NF.  No more outputs will be made."
				    */

/* WARNING-MESSAGE-FOR-LIMIT-REACHED-IN-GFI-OUTPUT */
Object warning_message_for_limit_reached_in_gfi_output(gfi_output_frame)
    Object gfi_output_frame;
{
    x_note_fn_call(217,57);
    Suppress_warning_message_header_qm = T;
    if ((SI_Long)2L <= IFIX(Warning_message_level))
	give_warning_1(3,FIX((SI_Long)2L),string_constant_9,gfi_output_frame);
    Suppress_warning_message_header_qm = Nil;
    return close_gfi_output_interface(gfi_output_frame,Nil);
}

static Object Qgfi_output_pathname_string_of_stream_qm;  /* gfi-output-pathname-string-of-stream? */

static Object Qgfi_output_file_stream;  /* gfi-output-file-stream */

static Object Qfloat_array;        /* float-array */

static Object Qgfi_output_base_time;  /* gfi-output-base-time */

static Object Qgfi_output_scheduled_task;  /* gfi-output-scheduled-task */

static Object Qnumber_of_lines_output_so_far;  /* number-of-lines-output-so-far */

static Object Qnew_gfi_output_values_this_cycle_qm;  /* new-gfi-output-values-this-cycle? */

static Object Qgfi_queue_of_new_output_values;  /* gfi-queue-of-new-output-values */

static Object Qspreadsheet;        /* spreadsheet */

static Object Qfailed_to_open;     /* failed-to-open */

static Object string_constant_10;  /* "Could not open output file ~S for ~NF:  ~A." */

/* OPEN-GFI-OUTPUT-INTERFACE */
Object open_gfi_output_interface(gfi_output_frame)
    Object gfi_output_frame;
{
    Object code, pathname_qm, amf_available_array_cons_qm, amf_array, temp;
    Object temp_1, amf_result, new_float, temp_2, list_of_output_designations;
    Object designations, queue_of_values, error_text;
    SI_Long ab_loop_repeat_;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(217,58);
    set_non_savable_lookup_slot_value(gfi_output_frame,Qgfi_outputting_qm,Nil);
    code = M_CAR(M_CDR(Gfi_list_of_converters));
    if (FIXNUMP(code) && (IFIX(code) & (SI_Long)8L) != (SI_Long)0L ? 
	    TRUEP(M_CAR(M_CDR(Cache_gfi_semantics_graph))) : TRUEP(Nil)) {
	pathname_qm = get_pathname_for_gfi_interface(gfi_output_frame,
		Qgfi_output_file_pathname);
	if (pathname_qm) {
	    set_non_savable_lookup_slot_value(gfi_output_frame,
		    Qgfi_output_pathname_string_of_stream_qm,pathname_qm);
	    set_non_savable_lookup_slot_value(gfi_output_frame,
		    Qgfi_output_file_stream,
		    g2_stream_open_for_output(pathname_qm));
	}
	if (pathname_qm && 
		g2_stream_p(get_lookup_slot_value_given_default(gfi_output_frame,
		Qgfi_output_file_stream,Nil))) {
	    set_non_savable_lookup_slot_value(gfi_output_frame,
		    Qgfi_outputting_qm,T);
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
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
			temp = 
				ISVREF(Available_float_array_conses_tail_vector,
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
		aref_new_value = 
			inline_ffloor_1(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L));
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		set_non_savable_lookup_slot_value(gfi_output_frame,
			Qgfi_output_base_time,new_float);
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	    set_non_savable_lookup_slot_value(gfi_output_frame,
		    Qgfi_output_scheduled_task,Nil);
	    set_non_savable_lookup_slot_value(gfi_output_frame,
		    Qnumber_of_lines_output_so_far,FIX((SI_Long)0L));
	    set_non_savable_lookup_slot_value(gfi_output_frame,
		    Qnew_gfi_output_values_this_cycle_qm,Nil);
	    temp_2 = get_lookup_slot_value_given_default(gfi_output_frame,
		    Qgfi_output_values,Nil);
	    temp_2 = CAR(temp_2);
	    list_of_output_designations = 
		    install_gfi_true_value_update(gfi_output_frame,temp_2,
		    get_lookup_slot_value_given_default(gfi_output_frame,
		    Qgfi_output_not_unique_designation_p_results,Nil));
	    change_slot_value(3,gfi_output_frame,
		    Qgfi_output_unique_designations,
		    list_of_output_designations);
	    temp_2 = get_lookup_slot_value_given_default(gfi_output_frame,
		    Qgfi_output_values,Nil);
	    designations = CAR(temp_2);
	    if (designations) {
		set_non_savable_lookup_slot_value(gfi_output_frame,
			Qgfi_queue_of_new_output_values,gfi_cons_1(Nil,Nil));
		if (EQ(get_lookup_slot_value(gfi_output_frame,
			Qgfi_output_file_format),Qspreadsheet)) {
		    queue_of_values = Nil;
		    ab_loop_repeat_ = 
			    IFIX(length(list_of_output_designations));
		  next_loop:
		    if ( !((SI_Long)0L < ab_loop_repeat_))
			goto end_loop;
		    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		    queue_of_values = gfi_cons_1(Nil,queue_of_values);
		    goto next_loop;
		  end_loop:
		    set_non_savable_lookup_slot_value(gfi_output_frame,
			    Qgfi_list_of_new_spreadsheet_output_values,
			    queue_of_values);
		    goto end_1;
		  end_1:;
		}
	    }
	    write_gfi_output_file_header(gfi_output_frame);
	    schedule_gfi_output_tasks(gfi_output_frame);
	    change_slot_value(3,gfi_output_frame,Qfile_status,Qopen);
	    return VALUES_1(T);
	}
	else {
	    change_slot_value(3,gfi_output_frame,Qfile_status,Qfailed_to_open);
	    if (pathname_qm) {
		error_text = most_recent_file_operation_status_as_text();
		Suppress_warning_message_header_qm = T;
		if ((SI_Long)2L <= IFIX(Warning_message_level))
		    give_warning_1(5,FIX((SI_Long)2L),string_constant_10,
			    pathname_qm,gfi_output_frame,error_text);
		Suppress_warning_message_header_qm = Nil;
		reclaim_text_string(error_text);
	    }
	    close_gfi_output_interface(gfi_output_frame,Nil);
	    return VALUES_1(Nil);
	}
    }
    else
	return parse_gfi_schedule_tree();
}

/* HANDLE-GFI-OUTPUT-INTERFACE-NEW-VALUES */
Object handle_gfi_output_interface_new_values(gfi_output_frame,
	    designation_position_pair,variable,attribute_qm,old_value,
	    class_if_specific_qm)
    Object gfi_output_frame, designation_position_pair, variable, attribute_qm;
    Object old_value, class_if_specific_qm;
{
    Object sub_class_bit_vector, current_computation_frame;
    Object current_computation_instance, current_computation_flags;
    volatile Object gensymed_symbol_3;
    Object variables_that_did_not_have_values, current_value, expiration_time;
    Object data_type, managed_current_value, queue_item, position_qm;
    Object store_managed_number_or_value_arg, temp_1, user_visible_designation;
    Object queue_pair, temp_2, last_queue_item_qm, gensymed_symbol_4, new_cons;
    Object svref_arg_2, svref_new_value, gensymed_symbol_5, first_1, last_1;
    Object next, temp_3, gensymed_symbol_6, pruned_interest_list, eval_cons;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp, spreadsheet_format_qm;
    double arg, arg_1;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(4);
    XDeclare_area(2);
    XDeclare_frontier(2);
    Object result;

    x_note_fn_call(217,59);
    SAVE_STACK();
    if (get_lookup_slot_value_given_default(gfi_output_frame,
	    Qgfi_outputting_qm,Nil)) {
	sub_class_bit_vector = ISVREF(ISVREF(variable,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Variable_or_parameter_class_description,
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
	    current_computation_frame = variable;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		    3);
	      current_computation_instance = Current_computation_frame;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_instance,Qcurrent_computation_instance,current_computation_instance,
		      2);
		current_computation_flags = Current_computation_flags;
		PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
			1);
		  Current_computation_flags = 
			  FIX(IFIX(Current_computation_flags) &  ~(SI_Long)4L);
		  Current_computation_flags = 
			  FIX(IFIX(Current_computation_flags) | (SI_Long)256L);
		  gensymed_symbol_3 = Nil;
		  if (PUSH_UNWIND_PROTECT(0)) {
		      variables_that_did_not_have_values = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Variables_that_did_not_have_values,Qvariables_that_did_not_have_values,variables_that_did_not_have_values,
			      0);
			if (PUSH_LOCAL_ALLOCATION(Local_area,1,1)) {
			    result = get_current_value(Current_computation_frame,
				    Nil);
			    MVS_3(result,current_value,expiration_time,
				    data_type);
			    if (expiration_time) {
				managed_current_value = Nil;
				queue_item = make_gfi_queue_item_1();
				position_qm = CDR(designation_position_pair);
				spreadsheet_format_qm = 
					EQ(get_lookup_slot_value(gfi_output_frame,
					Qgfi_output_file_format),Qspreadsheet);
				store_managed_number_or_value_arg = 
					current_value;
				managed_current_value = 
					store_managed_number_or_value_function(managed_current_value,
					store_managed_number_or_value_arg);
				SVREF(queue_item,FIX((SI_Long)1L)) = 
					managed_current_value;
				SVREF(queue_item,FIX((SI_Long)3L)) = data_type;
				temp_1 = copy_managed_float(Current_g2_time);
				SVREF(queue_item,FIX((SI_Long)2L)) = temp_1;
				if (position_qm) {
				    if ( !spreadsheet_format_qm) {
					temp_1 = 
						copy_tree_using_gfi_conses_1(CAR(designation_position_pair));
					SVREF(queue_item,FIX((SI_Long)4L)) 
						= temp_1;
				    }
				}
				else {
				    temp_1 = 
					    generate_designation_for_block(variable);
				    SVREF(queue_item,FIX((SI_Long)8L)) = 
					    temp_1;
				}
				SVREF(queue_item,FIX((SI_Long)5L)) = 
					position_qm;
				SVREF(queue_item,FIX((SI_Long)6L)) = variable;
				user_visible_designation = 
					get_or_make_up_designation_for_block(variable);
				if (text_string_p(user_visible_designation))
				    user_visible_designation = 
					    copy_text_string(user_visible_designation);
				SVREF(queue_item,FIX((SI_Long)7L)) = 
					user_visible_designation;
				queue_pair = 
					get_lookup_slot_value_given_default(gfi_output_frame,
					Qgfi_queue_of_new_output_values,Nil);
				if (CAR(queue_pair)) {
				    temp_2 = CDR(queue_pair);
				    last_queue_item_qm = CAR(temp_2);
				}
				else
				    last_queue_item_qm = Nil;
				if (last_queue_item_qm) {
				    temp_1 = 
					    FIXNUM_ADD1(ISVREF(last_queue_item_qm,
					    (SI_Long)9L));
				    SVREF(queue_item,FIX((SI_Long)9L)) = 
					    temp_1;
				}
				gensymed_symbol_4 = queue_item;
				new_cons = 
					ISVREF(Available_gfi_conses_vector,
					IFIX(Current_thread_index));
				if (new_cons) {
				    temp_1 = Available_gfi_conses_vector;
				    svref_arg_2 = Current_thread_index;
				    svref_new_value = M_CDR(new_cons);
				    SVREF(temp_1,svref_arg_2) = 
					    svref_new_value;
				    if ( 
					    !TRUEP(ISVREF(Available_gfi_conses_vector,
					    IFIX(Current_thread_index)))) {
					temp_1 = 
						Available_gfi_conses_tail_vector;
					svref_arg_2 = Current_thread_index;
					SVREF(temp_1,svref_arg_2) = Nil;
				    }
				    gensymed_symbol_5 = new_cons;
				}
				else
				    gensymed_symbol_5 = Nil;
				if ( !TRUEP(gensymed_symbol_5))
				    gensymed_symbol_5 = 
					    replenish_gfi_cons_pool();
				M_CAR(gensymed_symbol_5) = gensymed_symbol_4;
				M_CDR(gensymed_symbol_5) = Nil;
				inline_note_allocate_cons(gensymed_symbol_5,
					Qgfi);
			      next_loop:
				first_1 = CAR(queue_pair);
				last_1 = CDR(queue_pair);
				temp_2 = CDR(queue_pair);
				next = CDR(temp_2);
				if ( !TRUEP(first_1)) {
				    if (CAS_CAR(queue_pair,first_1,
					    gensymed_symbol_5)) {
					CAS_CDR(queue_pair,last_1,
						gensymed_symbol_5);
					goto end_1;
				    }
				}
				else if (EQ(last_1,CDR(queue_pair))) {
				    if ( !TRUEP(next)) {
					if (CAS_CDR(last_1,next,
						gensymed_symbol_5)) {
					    CAS_CDR(queue_pair,last_1,
						    gensymed_symbol_5);
					    goto end_1;
					}
				    }
				    else
					CAS_CDR(queue_pair,last_1,next);
				}
				goto next_loop;
			      end_loop:
			      end_1:;
				set_non_savable_lookup_slot_value(gfi_output_frame,
					Qnew_gfi_output_values_this_cycle_qm,
					T);
				temp_2 = CDR(queue_pair);
				temp_3 = CAR(queue_pair);
				if (FIXNUM_GE(FIXNUM_MINUS(ISVREF(CAR(temp_2),
					(SI_Long)9L),ISVREF(CAR(temp_3),
					(SI_Long)9L)),
					Maximum_gfi_output_queue_count)) {
				    temp =  !spreadsheet_format_qm;
				    if (temp);
				    else {
					if (PUSH_LOCAL_ALLOCATION(Local_area,
						0,0)) {
					    temp_2 = CDR(queue_pair);
					    arg = 
						    inline_ffloor_1(DFLOAT_ISAREF_1(ISVREF(CAR(temp_2),
						    (SI_Long)2L),(SI_Long)0L));
					    temp_2 = CAR(queue_pair);
					    arg_1 = 
						    inline_ffloor_1(DFLOAT_ISAREF_1(ISVREF(CAR(temp_2),
						    (SI_Long)2L),(SI_Long)0L));
					    temp = arg > arg_1 &&  
						    !inline_nanp_for_comparison(arg) 
						    ?  
						    !inline_nanp_for_comparison(arg_1) 
						    : TRUEP(Qnil);
					}
					POP_LOCAL_ALLOCATION(0,0);
				    }
				}
				else
				    temp = TRUEP(Nil);
				if (temp)
				    output_gfi_queued_values_to_stream(gfi_output_frame,
					    FIX((SI_Long)1L));
			    }
			    if (expiration_time && 
				    text_string_p(current_value))
				reclaim_text_string(current_value);
			}
			POP_LOCAL_ALLOCATION(1,1);
			gensymed_symbol_3 = Variables_that_did_not_have_values;
			SAVE_VALUES(VALUES_1(gensymed_symbol_3));
		      POP_SPECIAL();
		  }
		  POP_UNWIND_PROTECT(0);
		  if (gensymed_symbol_3) {
		      gensymed_symbol_4 = gensymed_symbol_3;
		      gensymed_symbol_5 = Nil;
		      gensymed_symbol_6 = Nil;
		    next_loop_1:
		      gensymed_symbol_5 = CAR(gensymed_symbol_4);
		      gensymed_symbol_6 = CDR(gensymed_symbol_4);
		      pruned_interest_list = 
			      delete_eval_element_1(Qvalue_request_pending,
			      ISVREF(gensymed_symbol_5,(SI_Long)36L));
		      ISVREF(gensymed_symbol_5,(SI_Long)36L) = 
			      pruned_interest_list;
		      if ( !TRUEP(pruned_interest_list) &&  
			      !TRUEP(ISVREF(gensymed_symbol_5,(SI_Long)38L)))
			  withdraw_backward_chaining(gensymed_symbol_5);
		      if ( !TRUEP(gensymed_symbol_6))
			  goto end_loop_1;
		      gensymed_symbol_4 = gensymed_symbol_6;
		      goto next_loop_1;
		    end_loop_1:
		      if (gensymed_symbol_3 &&  !((SI_Long)0L == 
			      inline_debugging_consing())) {
			  eval_cons = gensymed_symbol_3;
			next_loop_2:
			  inline_note_reclaim_cons(eval_cons,Qeval);
			  if (EQ(eval_cons,gensymed_symbol_4))
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
			  temp_1 = 
				  ISVREF(Available_eval_conses_tail_vector,
				  IFIX(Current_thread_index));
			  M_CDR(temp_1) = gensymed_symbol_3;
			  temp_1 = Available_eval_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp_1,svref_arg_2) = gensymed_symbol_4;
		      }
		      else {
			  temp_1 = Available_eval_conses_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp_1,svref_arg_2) = gensymed_symbol_3;
			  temp_1 = Available_eval_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp_1,svref_arg_2) = gensymed_symbol_4;
		      }
		      M_CDR(gensymed_symbol_4) = Nil;
		  }
		  CONTINUE_UNWINDING(0);
		  result = RESTORE_VALUES();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    RESTORE_STACK();
	    return result;
	}
	else {
	    result = warning_message_for_wrong_reference_for_gfi_designation(gfi_output_frame,
		    CAR(designation_position_pair),variable);
	    RESTORE_STACK();
	    return result;
	}
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

/* TPRINT-GFI-TIME-STAMP */
Object tprint_gfi_time_stamp(g2_time_to_print)
    Object g2_time_to_print;
{
    Object g2_time_float, subsecond_time_qm, seconds, minutes, hours, day;
    Object month, year;
    double temp, temp_1, second_fraction_float, arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(217,60);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	g2_time_float = INLINE_DOUBLE_FLOAT_VECTOR_P(g2_time_to_print) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(g2_time_to_print)) == 
		(SI_Long)1L ? 
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(g2_time_to_print,
		(SI_Long)0L)) : g2_time_to_print;
	temp = DOUBLE_FLOAT_TO_DOUBLE(g2_time_float);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(g2_time_float);
	second_fraction_float = temp - inline_ffloor_1(temp_1);
	arg = second_fraction_float;
	arg_1 = 0.0;
	subsecond_time_qm =  !(arg == arg_1 &&  
		!inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) ? 
		DOUBLE_TO_DOUBLE_FLOAT(second_fraction_float) : Nil;
	result = gensym_decode_unix_time(g2_time_float);
	MVS_6(result,seconds,minutes,hours,day,month,year);
	if (subsecond_time_qm) {
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(subsecond_time_qm);
	    seconds = DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(seconds) + temp_1);
	}
	result = print_decoded_time(seconds,minutes,hours,day,month,year);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

/* OUTPUT-GFI-EXPLICIT-TIME-STAMP-TO-STREAM */
Object output_gfi_explicit_time_stamp_to_stream(g2_time_to_print,
	    gfi_output_frame)
    Object g2_time_to_print, gfi_output_frame;
{
    Object gensymed_symbol, gensymed_symbol_1, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(217,61);
    gensymed_symbol = g2_time_to_print;
    gensymed_symbol_1 = gfi_output_frame;
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
	      tprint_gfi_time_stamp(gensymed_symbol);
	      gensymed_symbol = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    temp = gfi_write_string(gensymed_symbol,gensymed_symbol_1);
    reclaim_text_string(gensymed_symbol);
    return VALUES_1(temp);
}

static Object Qexplicit;           /* explicit */

/* OUTPUT-APPROPRIATE-GFI-TIME-STAMP */
Object output_appropriate_gfi_time_stamp(gfi_output_frame,g2_time_to_print)
    Object gfi_output_frame, g2_time_to_print;
{
    Object gensymed_symbol, gensymed_symbol_1, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, relative_time_stamp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    double gensymed_symbol_2, gensymed_symbol_3, relative_time, arg, arg_1;
    Declare_special(5);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(217,62);
    if (EQ(get_lookup_slot_value(gfi_output_frame,
	    Qgfi_output_time_stamp_format),Qexplicit)) {
	gensymed_symbol = g2_time_to_print;
	gensymed_symbol_1 = gfi_output_frame;
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
		  tprint_gfi_time_stamp(gensymed_symbol);
		  gensymed_symbol = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = gfi_write_string(gensymed_symbol,gensymed_symbol_1);
	reclaim_text_string(gensymed_symbol);
	return VALUES_1(temp);
    }
    else {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(g2_time_to_print) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(g2_time_to_print)) == 
		    (SI_Long)1L)
		gensymed_symbol_2 = DFLOAT_ISAREF_1(g2_time_to_print,
			(SI_Long)0L);
	    else
		gensymed_symbol_2 = DOUBLE_FLOAT_TO_DOUBLE(g2_time_to_print);
	    gensymed_symbol_3 = 
		    DFLOAT_ISAREF_1(get_lookup_slot_value_given_default(gfi_output_frame,
		    Qgfi_output_base_time,Nil),(SI_Long)0L);
	    relative_time = gensymed_symbol_2 - gensymed_symbol_3;
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
		      arg = relative_time;
		      arg_1 = inline_ffloor_1(relative_time);
		      if (arg == arg_1 &&  
			      !inline_nanp_for_comparison(arg) &&  
			      !inline_nanp_for_comparison(arg_1))
			  twrite_fixnum(LONG_TO_FIXNUM(inline_floor_1(relative_time)));
		      else
			  write_floating_point_number_simple_c_format(1,
				  DOUBLE_TO_DOUBLE_FLOAT(relative_time));
		      relative_time_stamp = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    temp = gfi_write_string(relative_time_stamp,gfi_output_frame);
	    reclaim_text_string(relative_time_stamp);
	    result = VALUES_1(temp);
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
}

static Object Qgfi_output_interface;  /* gfi-output-interface */

static Object Qfile_system;        /* file-system */

/* INITIALIZE-FOR-GFI-OUTPUT-INTERFACE */
Object initialize_for_gfi_output_interface(gfi_output_interface)
    Object gfi_output_interface;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(217,63);
    frame = gfi_output_interface;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)2L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qgfi_output_interface)) {
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
    change_slot_value(3,gfi_output_interface,Qfile_system,G2_operating_system);
    if ( 
	    !TRUEP(gfi_output_interface_non_default_slots_set_p(gfi_output_interface))) 
		{
	add_any_gfi_output_incomplete_frame_notes(gfi_output_interface);
	return update_frame_status(gfi_output_interface,Qincomplete,Nil);
    }
    else
	return VALUES_1(Nil);
}

/* INITIALIZE-AFTER-READING-FOR-GFI-OUTPUT-INTERFACE */
Object initialize_after_reading_for_gfi_output_interface(gfi_output_interface)
    Object gfi_output_interface;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(217,64);
    frame = gfi_output_interface;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)4L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qgfi_output_interface)) {
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
    change_slot_value(3,gfi_output_interface,Qfile_system,G2_operating_system);
    if ( 
	    !TRUEP(gfi_output_interface_non_default_slots_set_p(gfi_output_interface))) 
		{
	add_any_gfi_output_incomplete_frame_notes(gfi_output_interface);
	update_frame_status(gfi_output_interface,Qincomplete,Nil);
    }
    return update_representations_of_slot_value(2,gfi_output_interface,
	    Qfile_status);
}

/* GFI-OUTPUT-INTERFACE-NON-DEFAULT-SLOTS-SET-P */
Object gfi_output_interface_non_default_slots_set_p(gfi_output_interface)
    Object gfi_output_interface;
{
    Object temp;
    char temp_1;

    x_note_fn_call(217,65);
    if (get_lookup_slot_value_given_default(gfi_output_interface,
	    Qgfi_output_values,Nil)) {
	temp = get_lookup_slot_value_given_default(gfi_output_interface,
		Qgfi_output_values,Nil);
	temp_1 = LISTP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	temp = get_lookup_slot_value_given_default(gfi_output_interface,
		Qgfi_output_values,Nil);
	temp_1 = TRUEP(FIRST(temp));
    }
    else
	temp_1 = TRUEP(Nil);
    return VALUES_1(((temp_1 ? 
	    TRUEP(get_lookup_slot_value(gfi_output_interface,
	    Qgfi_output_file_update_frequency)) : TRUEP(Nil)) ? 
	    TRUEP(get_lookup_slot_value(gfi_output_interface,
	    Qgfi_output_file_pathname)) : TRUEP(Nil)) ? T : Nil);
}

/* ADD-ANY-GFI-OUTPUT-INCOMPLETE-FRAME-NOTES */
Object add_any_gfi_output_incomplete_frame_notes(gfi_output_interface)
    Object gfi_output_interface;
{
    Object temp_1;
    char temp;

    x_note_fn_call(217,66);
    temp =  
	    !TRUEP(get_lookup_slot_value_given_default(gfi_output_interface,
	    Qgfi_output_values,Nil));
    if (temp);
    else {
	temp_1 = get_lookup_slot_value_given_default(gfi_output_interface,
		Qgfi_output_values,Nil);
	if (LISTP(temp_1)) {
	    temp_1 = 
		    get_lookup_slot_value_given_default(gfi_output_interface,
		    Qgfi_output_values,Nil);
	    temp =  !TRUEP(FIRST(temp_1));
	}
	else
	    temp = TRUEP(Nil);
    }
    if (temp)
	add_frame_note(2,Qno_gfi_output_values,gfi_output_interface);
    if ( !TRUEP(get_lookup_slot_value(gfi_output_interface,
	    Qgfi_output_file_update_frequency)))
	add_frame_note(2,Qno_gfi_output_update_frequency,gfi_output_interface);
    if ( !TRUEP(get_lookup_slot_value(gfi_output_interface,
	    Qgfi_output_file_pathname)))
	add_frame_note(2,Qno_gfi_output_file_pathname,gfi_output_interface);
    return VALUES_1(Nil);
}

/* ACTIVATE-FOR-GFI-OUTPUT-INTERFACE */
Object activate_for_gfi_output_interface(gfi_output_interface)
    Object gfi_output_interface;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(217,67);
    if (get_lookup_slot_value(gfi_output_interface,Qgfi_output_when_active))
	prepare_gfi_output_interface_to_open(gfi_output_interface);
    frame = gfi_output_interface;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)6L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qgfi_output_interface)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	return inline_funcall_1(method_function_qm,frame);
    else
	return VALUES_1(Nil);
}

static Object string_constant_11;  /* "While activating ~NF, the GFI output file could not be ~
				    *                 opened.  This item is incomplete."
				    */

static Object Qnupec_snapshot;     /* nupec-snapshot */

static Object Qnupec_snapshot_with_restart_time;  /* nupec-snapshot-with-restart-time */

static Object Qoutput_one_shot_when_activated;  /* output-one-shot-when-activated */

static Object string_constant_12;  /* "When using a GFI file format of NUPEC snapshot for ~NF, the gfi-~
				    *           output-file-update-frequency must be either \"write to file when ~
				    *           activated\" or \"write to file when activated, without ~
				    *           interruption\"."
				    */

static Object Qready_to_open;      /* ready-to-open */

/* PREPARE-GFI-OUTPUT-INTERFACE-TO-OPEN */
Object prepare_gfi_output_interface_to_open(gfi_output_interface)
    Object gfi_output_interface;
{
    Object code, temp, gensymed_symbol, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol_1, first_1, last_1, next;
    Object queue_list;

    x_note_fn_call(217,68);
    code = M_CAR(M_CDR(Gfi_list_of_converters));
    if (FIXNUMP(code) && (IFIX(code) & (SI_Long)8L) != (SI_Long)0L ? 
	    TRUEP(M_CAR(M_CDR(Cache_gfi_semantics_graph))) : TRUEP(Nil)) {
	temp = ISVREF(gfi_output_interface,(SI_Long)8L);
	if ( ! !TRUEP(CAR(temp)))
	    temp = (SI_Long)2L <= IFIX(Warning_message_level) ? 
		    give_warning_1(3,FIX((SI_Long)2L),string_constant_11,
		    gfi_output_interface) : Nil;
	else if ((EQ(get_lookup_slot_value(gfi_output_interface,
		Qgfi_output_file_format),Qnupec_snapshot) || 
		EQ(get_lookup_slot_value(gfi_output_interface,
		Qgfi_output_file_format),
		Qnupec_snapshot_with_restart_time)) &&  
		!EQ(get_lookup_slot_value(gfi_output_interface,
		Qgfi_output_file_update_frequency),
		Qoutput_one_shot_when_activated) &&  
		!EQ(get_lookup_slot_value(gfi_output_interface,
		Qgfi_output_file_update_frequency),
		Qoutput_one_shot_when_activated_without_interruption)) {
	    Suppress_warning_message_header_qm = T;
	    if ((SI_Long)2L <= IFIX(Warning_message_level))
		give_warning_1(3,FIX((SI_Long)2L),string_constant_12,
			gfi_output_interface);
	    Suppress_warning_message_header_qm = Nil;
	    temp = Suppress_warning_message_header_qm;
	}
	else {
	    if (g2_stream_p(get_lookup_slot_value_given_default(gfi_output_interface,
		    Qgfi_output_file_stream,Nil)))
		close_gfi_output_interface(gfi_output_interface,T);
	    set_non_savable_lookup_slot_value(gfi_output_interface,
		    Qgfi_list_of_new_spreadsheet_output_values,Nil);
	    set_non_savable_lookup_slot_value(gfi_output_interface,
		    Qgfi_output_file_stream,Nil);
	    set_non_savable_lookup_slot_value(gfi_output_interface,
		    Qgfi_outputting_qm,Nil);
	    change_slot_value(3,gfi_output_interface,Qfile_status,
		    Qready_to_open);
	    if (get_lookup_slot_value_given_default(gfi_output_interface,
		    Qgfi_output_without_interruption_qm,Nil)) {
		if (Queue_of_active_uninterruptable_gfi_output_interface_objects) 
			    {
		    gensymed_symbol = gfi_output_interface;
		    new_cons = ISVREF(Available_gfi_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			svref_arg_1 = Available_gfi_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
			if ( !TRUEP(ISVREF(Available_gfi_conses_vector,
				IFIX(Current_thread_index)))) {
			    svref_arg_1 = Available_gfi_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(svref_arg_1,svref_arg_2) = Nil;
			}
			gensymed_symbol_1 = new_cons;
		    }
		    else
			gensymed_symbol_1 = Nil;
		    if ( !TRUEP(gensymed_symbol_1))
			gensymed_symbol_1 = replenish_gfi_cons_pool();
		    M_CAR(gensymed_symbol_1) = gensymed_symbol;
		    M_CDR(gensymed_symbol_1) = Nil;
		    inline_note_allocate_cons(gensymed_symbol_1,Qgfi);
		  next_loop:
		    first_1 = 
			    CAR(Queue_of_active_uninterruptable_gfi_output_interface_objects);
		    last_1 = 
			    CDR(Queue_of_active_uninterruptable_gfi_output_interface_objects);
		    temp = 
			    CDR(Queue_of_active_uninterruptable_gfi_output_interface_objects);
		    next = CDR(temp);
		    if ( !TRUEP(first_1)) {
			if (CAS_CAR(Queue_of_active_uninterruptable_gfi_output_interface_objects,
				first_1,gensymed_symbol_1)) {
			    CAS_CDR(Queue_of_active_uninterruptable_gfi_output_interface_objects,
				    last_1,gensymed_symbol_1);
			    goto end_1;
			}
		    }
		    else if (EQ(last_1,
			    CDR(Queue_of_active_uninterruptable_gfi_output_interface_objects))) 
				{
			if ( !TRUEP(next)) {
			    if (CAS_CDR(last_1,next,gensymed_symbol_1)) {
				CAS_CDR(Queue_of_active_uninterruptable_gfi_output_interface_objects,
					last_1,gensymed_symbol_1);
				goto end_1;
			    }
			}
			else
			    CAS_CDR(Queue_of_active_uninterruptable_gfi_output_interface_objects,
				    last_1,next);
		    }
		    goto next_loop;
		  end_loop:
		  end_1:;
		}
		else {
		    queue_list = gfi_cons_1(gfi_output_interface,Nil);
		    Queue_of_active_uninterruptable_gfi_output_interface_objects 
			    = gfi_cons_1(queue_list,queue_list);
		}
	    }
	    else if (Queue_of_active_gfi_output_interface_objects) {
		gensymed_symbol = gfi_output_interface;
		new_cons = ISVREF(Available_gfi_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    svref_arg_1 = Available_gfi_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_gfi_conses_vector,
			    IFIX(Current_thread_index)))) {
			svref_arg_1 = Available_gfi_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(svref_arg_1,svref_arg_2) = Nil;
		    }
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_gfi_cons_pool();
		M_CAR(gensymed_symbol_1) = gensymed_symbol;
		M_CDR(gensymed_symbol_1) = Nil;
		inline_note_allocate_cons(gensymed_symbol_1,Qgfi);
	      next_loop_1:
		first_1 = CAR(Queue_of_active_gfi_output_interface_objects);
		last_1 = CDR(Queue_of_active_gfi_output_interface_objects);
		temp = CDR(Queue_of_active_gfi_output_interface_objects);
		next = CDR(temp);
		if ( !TRUEP(first_1)) {
		    if (CAS_CAR(Queue_of_active_gfi_output_interface_objects,
			    first_1,gensymed_symbol_1)) {
			CAS_CDR(Queue_of_active_gfi_output_interface_objects,
				last_1,gensymed_symbol_1);
			goto end_2;
		    }
		}
		else if (EQ(last_1,
			CDR(Queue_of_active_gfi_output_interface_objects))) {
		    if ( !TRUEP(next)) {
			if (CAS_CDR(last_1,next,gensymed_symbol_1)) {
			    CAS_CDR(Queue_of_active_gfi_output_interface_objects,
				    last_1,gensymed_symbol_1);
			    goto end_2;
			}
		    }
		    else
			CAS_CDR(Queue_of_active_gfi_output_interface_objects,
				last_1,next);
		}
		goto next_loop_1;
	      end_loop_1:
	      end_2:;
	    }
	    else {
		queue_list = gfi_cons_1(gfi_output_interface,Nil);
		Queue_of_active_gfi_output_interface_objects = 
			gfi_cons_1(queue_list,queue_list);
	    }
	    temp = schedule_data_server_accept_data_calls();
	}
    }
    else
	temp = parse_gfi_schedule_tree();
    return VALUES_1(temp);
}

/* WRITE-DESIGNATION-TO-STREAM */
Object write_designation_to_stream(designation,gfi_output_frame)
    Object designation, gfi_output_frame;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object designation_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(217,69);
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
	      print_designation(designation);
	      designation_string = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    gfi_write_string(designation_string,gfi_output_frame);
    return reclaim_text_string(designation_string);
}

static Object Qnumber_of_periodic_specified_designation_handled;  /* number-of-periodic-specified-designation-handled */

static Object Qrelative;           /* relative */

static Object array_constant_3;    /* # */

static Object array_constant_4;    /* # */

static Object Qevent_log;          /* event-log */

static Object string_constant_13;  /* "Illegal GFI output file format ~A in ~NF." */

/* WRITE-GFI-OUTPUT-FILE-HEADER */
Object write_gfi_output_file_header(gfi_output_frame)
    Object gfi_output_frame;
{
    Object temp, designation, ab_loop_list_;
    Object number_of_lines_output_so_far_new_value;

    x_note_fn_call(217,70);
    set_non_savable_lookup_slot_value(gfi_output_frame,
	    Qnumber_of_periodic_specified_designation_handled,
	    FIX((SI_Long)0L));
    temp = get_lookup_slot_value(gfi_output_frame,Qgfi_output_file_format);
    if (EQ(temp,Qspreadsheet)) {
	if (EQ(get_lookup_slot_value(gfi_output_frame,
		Qgfi_output_time_stamp_format),Qrelative)) {
	    gfi_write_string(Gfi_title_for_base_time,gfi_output_frame);
	    gfi_write_string(array_constant_3,gfi_output_frame);
	    output_gfi_explicit_time_stamp_to_stream(get_lookup_slot_value_given_default(gfi_output_frame,
		    Qgfi_output_base_time,Nil),gfi_output_frame);
	}
	else
	    gfi_write_string(array_constant_4,gfi_output_frame);
	designation = Nil;
	ab_loop_list_ = 
		get_lookup_slot_value_given_default(gfi_output_frame,
		Qgfi_output_unique_designations,Nil);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	designation = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gfi_write_char(Gfi_delimitter,gfi_output_frame);
	write_designation_to_stream(designation,gfi_output_frame);
	goto next_loop;
      end_loop:
	gfi_terpri(gfi_output_frame);
	number_of_lines_output_so_far_new_value = 
		FIXNUM_ADD1(get_lookup_slot_value_given_default(gfi_output_frame,
		Qnumber_of_lines_output_so_far,Nil));
	return set_non_savable_lookup_slot_value(gfi_output_frame,
		Qnumber_of_lines_output_so_far,
		number_of_lines_output_so_far_new_value);
    }
    else if (EQ(temp,Qevent_log)) {
	if (EQ(get_lookup_slot_value(gfi_output_frame,
		Qgfi_output_time_stamp_format),Qrelative)) {
	    output_gfi_explicit_time_stamp_to_stream(get_lookup_slot_value_given_default(gfi_output_frame,
		    Qgfi_output_base_time,Nil),gfi_output_frame);
	    gfi_write_char(Gfi_delimitter,gfi_output_frame);
	    gfi_write_string(Gfi_designation_for_base_time,gfi_output_frame);
	    gfi_write_char(Gfi_delimitter,gfi_output_frame);
	    gfi_write_char(CHR('0'),gfi_output_frame);
	    gfi_terpri(gfi_output_frame);
	    number_of_lines_output_so_far_new_value = 
		    FIXNUM_ADD1(get_lookup_slot_value_given_default(gfi_output_frame,
		    Qnumber_of_lines_output_so_far,Nil));
	    return set_non_savable_lookup_slot_value(gfi_output_frame,
		    Qnumber_of_lines_output_so_far,
		    number_of_lines_output_so_far_new_value);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (EQ(temp,Qnupec_snapshot) || EQ(temp,
	    Qnupec_snapshot_with_restart_time)) {
	output_gfi_explicit_time_stamp_to_stream(get_lookup_slot_value_given_default(gfi_output_frame,
		Qgfi_output_base_time,Nil),gfi_output_frame);
	gfi_write_char(Gfi_delimitter,gfi_output_frame);
	gfi_write_string(Gfi_designation_for_base_time,gfi_output_frame);
	gfi_write_char(Gfi_delimitter,gfi_output_frame);
	gfi_write_char(CHR('0'),gfi_output_frame);
	gfi_terpri(gfi_output_frame);
	number_of_lines_output_so_far_new_value = 
		FIXNUM_ADD1(get_lookup_slot_value_given_default(gfi_output_frame,
		Qnumber_of_lines_output_so_far,Nil));
	return set_non_savable_lookup_slot_value(gfi_output_frame,
		Qnumber_of_lines_output_so_far,
		number_of_lines_output_so_far_new_value);
    }
    else {
	Suppress_warning_message_header_qm = T;
	if ((SI_Long)2L <= IFIX(Warning_message_level))
	    give_warning_1(4,FIX((SI_Long)2L),string_constant_13,
		    get_lookup_slot_value(gfi_output_frame,
		    Qgfi_output_file_format),gfi_output_frame);
	Suppress_warning_message_header_qm = Nil;
	return VALUES_1(Suppress_warning_message_header_qm);
    }
}

static Object Qwrite_interval;     /* write-interval */

static Object Qpriority_of_data_service;  /* priority-of-data-service */

static Object Qgfi_output_spreadsheet_values_periodically_task;  /* gfi-output-spreadsheet-values-periodically-task */

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qgfi_output_event_log_values_periodically_task;  /* gfi-output-event-log-values-periodically-task */

static Object string_constant_14;  /* "Illegal GFI output file update frequency ~A in ~NF." */

/* SCHEDULE-GFI-OUTPUT-TASKS */
Object schedule_gfi_output_tasks(gfi_output_frame)
    Object gfi_output_frame;
{
    Object value, temp, file_format, current_task_schedule_modify_1_arg_2;
    Object current_task_schedule_modify_1_arg_8;
    Object current_task_schedule_modify_1_arg_11, schedule_task_qm;
    Object structure_being_reclaimed, temp_2, svref_arg_2;
    Object def_structure_schedule_task_variable, svref_new_value, task, ctask;
    Object p, v, q;
    char temp_1, g2_p;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(217,71);
    if (memq_function(get_lookup_slot_value(gfi_output_frame,
	    Qgfi_output_file_update_frequency),list_constant))
	return VALUES_1(Nil);
    else if (EQ(get_lookup_slot_value(gfi_output_frame,
	    Qgfi_output_file_update_frequency),
	    Qoutput_one_shot_when_activated) || 
	    EQ(get_lookup_slot_value(gfi_output_frame,
	    Qgfi_output_file_update_frequency),
	    Qoutput_one_shot_when_activated_without_interruption))
	return VALUES_1(Nil);
    else {
	value = get_lookup_slot_value(gfi_output_frame,
		Qgfi_output_file_update_frequency);
	if (LISTP(value) && EQ(CAR(value),Qwrite_interval)) {
	    temp = SECOND(value);
	    temp_1 = CONSP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    file_format = get_lookup_slot_value(gfi_output_frame,
		    Qgfi_output_file_format);
	    if (EQ(file_format,Qspreadsheet)) {
		current_task_schedule_modify_1_arg_2 = 
			get_slot_value_function(Data_server_parameters,
			Qpriority_of_data_service,Nil);
		current_task_schedule_modify_1_arg_8 = 
			SYMBOL_FUNCTION(Qgfi_output_spreadsheet_values_periodically_task);
		current_task_schedule_modify_1_arg_11 = gfi_output_frame;
		schedule_task_qm = 
			get_lookup_slot_value_given_default(gfi_output_frame,
			Qgfi_output_scheduled_task,Nil);
		if (schedule_task_qm) {
		    if (EQ(schedule_task_qm,Current_schedule_task))
			Current_schedule_task = Nil;
		    if (ISVREF(schedule_task_qm,(SI_Long)6L))
			cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
		    inline_note_reclaim_cons(schedule_task_qm,Nil);
		    structure_being_reclaimed = schedule_task_qm;
		    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
			    0);
		      reclaim_schedule_task_args(ISVREF(schedule_task_qm,
			      (SI_Long)9L));
		      SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
		    POP_SPECIAL();
		    temp_2 = 
			    ISVREF(Chain_of_available_schedule_tasks_vector,
			    IFIX(Current_thread_index));
		    SVREF(schedule_task_qm,FIX((SI_Long)0L)) = temp_2;
		    temp_2 = Chain_of_available_schedule_tasks_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = schedule_task_qm;
		}
		def_structure_schedule_task_variable = 
			ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		if (def_structure_schedule_task_variable) {
		    temp_2 = Chain_of_available_schedule_tasks_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = 
			    ISVREF(def_structure_schedule_task_variable,
			    (SI_Long)0L);
		    SVREF(temp_2,svref_arg_2) = svref_new_value;
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
			FIX((SI_Long)2L)) = Nil;
		SVREF(def_structure_schedule_task_variable,
			FIX((SI_Long)9L)) = Nil;
		task = def_structure_schedule_task_variable;
		temp_2 = ISVREF(task,(SI_Long)1L);
		aref_new_value = -1.0;
		DFLOAT_ISASET_1(temp_2,(SI_Long)1L,aref_new_value);
		SVREF(task,FIX((SI_Long)4L)) = 
			current_task_schedule_modify_1_arg_2;
		SVREF(task,FIX((SI_Long)5L)) = Nil;
		SVREF(task,FIX((SI_Long)9L)) = Nil;
		SVREF(task,FIX((SI_Long)10L)) = Nil;
		g2_p =  !TRUEP(Nil);
		SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
		temp_2 = ISVREF(task,(SI_Long)1L);
		aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
			Current_real_time,(SI_Long)0L);
		DFLOAT_ISASET_1(temp_2,(SI_Long)0L,aref_new_value);
		SVREF(task,FIX((SI_Long)7L)) = 
			Qgfi_output_spreadsheet_values_periodically_task;
		SVREF(task,FIX((SI_Long)8L)) = 
			current_task_schedule_modify_1_arg_8;
		ISVREF(task,(SI_Long)12L) = FIX((SI_Long)2L);
		SVREF(task,FIX((SI_Long)13L)) = 
			current_task_schedule_modify_1_arg_11;
		SVREF(task,FIX((SI_Long)14L)) = T;
		ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
		if (ctask);
		else
		    ctask = System_is_running;
		p = ISVREF(task,(SI_Long)4L);
		v = ctask ? Current_task_queue_vector : 
			Deferred_task_queue_vector;
		q = ISVREF(v,IFIX(p));
		SVREF(task,FIX((SI_Long)11L)) = q;
		temp_2 = constant_queue_push_right(q,task);
		SVREF(task,FIX((SI_Long)6L)) = temp_2;
		if (ctask && FIXNUM_LT(p,Priority_of_next_task))
		    Priority_of_next_task = p;
		return set_non_savable_lookup_slot_value(gfi_output_frame,
			Qgfi_output_scheduled_task,task);
	    }
	    else if (EQ(file_format,Qevent_log)) {
		current_task_schedule_modify_1_arg_2 = 
			get_slot_value_function(Data_server_parameters,
			Qpriority_of_data_service,Nil);
		current_task_schedule_modify_1_arg_8 = 
			SYMBOL_FUNCTION(Qgfi_output_event_log_values_periodically_task);
		current_task_schedule_modify_1_arg_11 = gfi_output_frame;
		schedule_task_qm = 
			get_lookup_slot_value_given_default(gfi_output_frame,
			Qgfi_output_scheduled_task,Nil);
		if (schedule_task_qm) {
		    if (EQ(schedule_task_qm,Current_schedule_task))
			Current_schedule_task = Nil;
		    if (ISVREF(schedule_task_qm,(SI_Long)6L))
			cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
		    inline_note_reclaim_cons(schedule_task_qm,Nil);
		    structure_being_reclaimed = schedule_task_qm;
		    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
			    0);
		      reclaim_schedule_task_args(ISVREF(schedule_task_qm,
			      (SI_Long)9L));
		      SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
		    POP_SPECIAL();
		    temp_2 = 
			    ISVREF(Chain_of_available_schedule_tasks_vector,
			    IFIX(Current_thread_index));
		    SVREF(schedule_task_qm,FIX((SI_Long)0L)) = temp_2;
		    temp_2 = Chain_of_available_schedule_tasks_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = schedule_task_qm;
		}
		def_structure_schedule_task_variable = 
			ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		if (def_structure_schedule_task_variable) {
		    temp_2 = Chain_of_available_schedule_tasks_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = 
			    ISVREF(def_structure_schedule_task_variable,
			    (SI_Long)0L);
		    SVREF(temp_2,svref_arg_2) = svref_new_value;
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
			FIX((SI_Long)2L)) = Nil;
		SVREF(def_structure_schedule_task_variable,
			FIX((SI_Long)9L)) = Nil;
		task = def_structure_schedule_task_variable;
		temp_2 = ISVREF(task,(SI_Long)1L);
		aref_new_value = -1.0;
		DFLOAT_ISASET_1(temp_2,(SI_Long)1L,aref_new_value);
		SVREF(task,FIX((SI_Long)4L)) = 
			current_task_schedule_modify_1_arg_2;
		SVREF(task,FIX((SI_Long)5L)) = Nil;
		SVREF(task,FIX((SI_Long)9L)) = Nil;
		SVREF(task,FIX((SI_Long)10L)) = Nil;
		g2_p =  !TRUEP(Nil);
		SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
		temp_2 = ISVREF(task,(SI_Long)1L);
		aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
			Current_real_time,(SI_Long)0L);
		DFLOAT_ISASET_1(temp_2,(SI_Long)0L,aref_new_value);
		SVREF(task,FIX((SI_Long)7L)) = 
			Qgfi_output_event_log_values_periodically_task;
		SVREF(task,FIX((SI_Long)8L)) = 
			current_task_schedule_modify_1_arg_8;
		ISVREF(task,(SI_Long)12L) = FIX((SI_Long)2L);
		SVREF(task,FIX((SI_Long)13L)) = 
			current_task_schedule_modify_1_arg_11;
		SVREF(task,FIX((SI_Long)14L)) = T;
		ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
		if (ctask);
		else
		    ctask = System_is_running;
		p = ISVREF(task,(SI_Long)4L);
		v = ctask ? Current_task_queue_vector : 
			Deferred_task_queue_vector;
		q = ISVREF(v,IFIX(p));
		SVREF(task,FIX((SI_Long)11L)) = q;
		temp_2 = constant_queue_push_right(q,task);
		SVREF(task,FIX((SI_Long)6L)) = temp_2;
		if (ctask && FIXNUM_LT(p,Priority_of_next_task))
		    Priority_of_next_task = p;
		return set_non_savable_lookup_slot_value(gfi_output_frame,
			Qgfi_output_scheduled_task,task);
	    }
	    else
		return VALUES_1(Qnil);
	}
	else {
	    Suppress_warning_message_header_qm = T;
	    if ((SI_Long)2L <= IFIX(Warning_message_level))
		give_warning_1(4,FIX((SI_Long)2L),string_constant_14,
			get_lookup_slot_value(gfi_output_frame,
			Qgfi_output_file_update_frequency),gfi_output_frame);
	    Suppress_warning_message_header_qm = Nil;
	    return VALUES_1(Suppress_warning_message_header_qm);
	}
    }
}

/* OUTPUT-GFI-VALUE */
Object output_gfi_value(current_value,data_type,gfi_output_frame)
    Object current_value, data_type, gfi_output_frame;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object output_value, temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(217,72);
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
	      if (EQ(data_type,Qfloat))
		  write_floating_point_number(9,current_value,
			  Maximum_significant_decimal_digits_in_gensym_float,
			  Maximum_significant_decimal_digits_in_gensym_float,
			  Maximum_significant_decimal_digits_in_gensym_float,
			  T,Nil,T,Nil,
			  FIXNUM_ADD1(Maximum_significant_decimal_digits_in_gensym_float));
	      else if (EQ(data_type,Qnumber)) {
		  if (FIXNUMP(data_type))
		      twrite_fixnum(current_value);
		  else
		      write_floating_point_number(9,current_value,
			      Maximum_significant_decimal_digits_in_gensym_float,
			      Maximum_significant_decimal_digits_in_gensym_float,
			      Maximum_significant_decimal_digits_in_gensym_float,
			      T,Nil,T,Nil,
			      FIXNUM_ADD1(Maximum_significant_decimal_digits_in_gensym_float));
	      }
	      else if (EQ(data_type,Qinteger))
		  twrite_fixnum(current_value);
	      else
		  print_constant(2,current_value,data_type);
	      output_value = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    temp = gfi_write_string(output_value,gfi_output_frame);
    reclaim_text_string(output_value);
    return VALUES_1(temp);
}

/* GFI-OUTPUT-SPREADSHEET-VALUES-PERIODICALLY-TASK */
Object gfi_output_spreadsheet_values_periodically_task(gfi_output_frame,
	    do_not_override_time_slice_p)
    Object gfi_output_frame, do_not_override_time_slice_p;
{
    Object temp;

    x_note_fn_call(217,73);
    temp = gfi_output_spreadsheet_values_periodically(gfi_output_frame,
	    do_not_override_time_slice_p);
    return VALUES_1(temp);
}

static Object Qmaximum_number_of_output_lines;  /* maximum-number-of-output-lines */

static Object Qgfi_output_scheduled_task_start_time;  /* gfi-output-scheduled-task-start-time */

/* GFI-OUTPUT-SPREADSHEET-VALUES-PERIODICALLY */
Object gfi_output_spreadsheet_values_periodically(gfi_output_frame,
	    do_not_override_time_slice_p)
    Object gfi_output_frame, do_not_override_time_slice_p;
{
    Object time_slice_expired_p_1, output_stream, output_limit;
    Object number_of_designations_already_handled, value, temp, temp_2;
    Object variable_qm, designation_list, designation;
    Object current_computation_frame, sub_class_bit_vector;
    Object current_computation_instance, current_computation_flags;
    volatile Object gensymed_symbol_3;
    Object variables_that_did_not_have_values, current_value, expiration_time;
    Object data_type, gensymed_symbol_4, gensymed_symbol_5, gensymed_symbol_6;
    Object pruned_interest_list, eval_cons, svref_arg_2;
    Object current_task_schedule_modify_1_arg_2;
    Object current_task_schedule_modify_1_arg_8;
    Object current_task_schedule_modify_1_arg_11, schedule_task_qm;
    Object structure_being_reclaimed, def_structure_schedule_task_variable;
    Object svref_new_value, task, ctask, p, v, q, execution_time;
    Object future_task_schedule_modify_1_arg_2;
    Object future_task_schedule_modify_1_arg_8;
    Object future_task_schedule_modify_1_arg_11;
    SI_Long value_count, superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, temp_4;
    char temp_1, g2_p, svref_new_value_1;
    double aref_new_value, temp_3, future_task_schedule_modify_1_arg_3;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(5);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(217,74);
    SAVE_STACK();
    if (get_lookup_slot_value_given_default(gfi_output_frame,
	    Qgfi_outputting_qm,Nil)) {
	time_slice_expired_p_1 = Nil;
	output_stream = 
		get_lookup_slot_value_given_default(gfi_output_frame,
		Qgfi_output_file_stream,Nil);
	output_limit = get_lookup_slot_value(gfi_output_frame,
		Qmaximum_number_of_output_lines);
	number_of_designations_already_handled = 
		get_lookup_slot_value_given_default(gfi_output_frame,
		Qnumber_of_periodic_specified_designation_handled,Nil);
	if (number_of_designations_already_handled);
	else
	    number_of_designations_already_handled = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Time_slice_expired_p,Qtime_slice_expired_p,time_slice_expired_p_1,
		4);
	  if (output_stream) {
	      if (output_limit && FIXNUM_LE(output_limit,
		      get_lookup_slot_value_given_default(gfi_output_frame,
		      Qnumber_of_lines_output_so_far,Nil))) {
		  warning_message_for_limit_reached_in_gfi_output(gfi_output_frame);
		  result = VALUES_1(Nil);
	      }
	      else {
		  value = get_lookup_slot_value(gfi_output_frame,
			  Qgfi_output_file_update_frequency);
		  if (LISTP(value) && EQ(CAR(value),Qwrite_interval)) {
		      temp = SECOND(value);
		      temp_1 = CONSP(temp);
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  if (temp_1 ?  
			  !TRUEP(get_lookup_slot_value_given_default(gfi_output_frame,
			  Qgfi_output_scheduled_task_start_time,Nil)) : 
			  TRUEP(Nil))
		      set_non_savable_lookup_slot_value(gfi_output_frame,
			      Qgfi_output_scheduled_task_start_time,
			      Gensym_time);
		  temp_2 = 
			  FIXNUM_ADD1(get_lookup_slot_value_given_default(gfi_output_frame,
			  Qnumber_of_lines_output_so_far,Nil));
		  set_non_savable_lookup_slot_value(gfi_output_frame,
			  Qnumber_of_lines_output_so_far,temp_2);
		  if (IFIX(number_of_designations_already_handled) <= 
			  (SI_Long)0L)
		      output_appropriate_gfi_time_stamp(gfi_output_frame,
			      Current_g2_time);
		  variable_qm = Nil;
		  temp = number_of_designations_already_handled;
		  designation_list = nthcdr(temp,
			  get_lookup_slot_value_given_default(gfi_output_frame,
			  Qgfi_output_unique_designations,Nil));
		  designation = Nil;
		  value_count = (SI_Long)0L;
		next_loop:
		  if ( !TRUEP(designation_list))
		      goto end_loop;
		  designation = CAR(designation_list);
		  value_count = value_count + (SI_Long)1L;
		  gfi_write_char(Gfi_delimitter,gfi_output_frame);
		  current_computation_frame = gfi_output_frame;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
			  0);
		    variable_qm = evaluate_designation(designation,Nil);
		  POP_SPECIAL();
		  if (variable_qm &&  !(SIMPLE_VECTOR_P(variable_qm) && 
			  EQ(ISVREF(variable_qm,(SI_Long)0L),
			  Qg2_defstruct_structure_name_temporary_constant_g2_struct))) 
			      {
		      sub_class_bit_vector = ISVREF(ISVREF(variable_qm,
			      (SI_Long)1L),(SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(Variable_or_parameter_class_description,
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
			  temp_1 = (SI_Long)0L < gensymed_symbol;
		      }
		      else
			  temp_1 = TRUEP(Nil);
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  if (temp_1) {
		      current_computation_frame = variable_qm;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
			      3);
			current_computation_instance = 
				Current_computation_frame;
			PUSH_SPECIAL_WITH_SYMBOL(Current_computation_instance,Qcurrent_computation_instance,current_computation_instance,
				2);
			  current_computation_flags = 
				  Current_computation_flags;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
				  1);
			    Current_computation_flags = 
				    FIX(IFIX(Current_computation_flags) &  
				    ~(SI_Long)4L);
			    Current_computation_flags = 
				    FIX(IFIX(Current_computation_flags) | 
				    (SI_Long)256L);
			    gensymed_symbol_3 = Nil;
			    if (PUSH_UNWIND_PROTECT(0)) {
				variables_that_did_not_have_values = Nil;
				PUSH_SPECIAL_WITH_SYMBOL(Variables_that_did_not_have_values,Qvariables_that_did_not_have_values,variables_that_did_not_have_values,
					0);
				  if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
				      result = get_current_value(Current_computation_frame,
					      Nil);
				      MVS_3(result,current_value,
					      expiration_time,data_type);
				      if (expiration_time)
					  output_gfi_value(current_value,
						  data_type,gfi_output_frame);
				      if (expiration_time && 
					      text_string_p(current_value))
					  reclaim_text_string(current_value);
				  }
				  POP_LOCAL_ALLOCATION(0,0);
				  gensymed_symbol_3 = 
					  Variables_that_did_not_have_values;
				POP_SPECIAL();
			    }
			    POP_UNWIND_PROTECT(0);
			    if (gensymed_symbol_3) {
				gensymed_symbol_4 = gensymed_symbol_3;
				gensymed_symbol_5 = Nil;
				gensymed_symbol_6 = Nil;
			      next_loop_1:
				gensymed_symbol_5 = CAR(gensymed_symbol_4);
				gensymed_symbol_6 = CDR(gensymed_symbol_4);
				pruned_interest_list = 
					delete_eval_element_1(Qvalue_request_pending,
					ISVREF(gensymed_symbol_5,
					(SI_Long)36L));
				ISVREF(gensymed_symbol_5,(SI_Long)36L) = 
					pruned_interest_list;
				if ( !TRUEP(pruned_interest_list) &&  
					!TRUEP(ISVREF(gensymed_symbol_5,
					(SI_Long)38L)))
				    withdraw_backward_chaining(gensymed_symbol_5);
				if ( !TRUEP(gensymed_symbol_6))
				    goto end_loop_1;
				gensymed_symbol_4 = gensymed_symbol_6;
				goto next_loop_1;
			      end_loop_1:
				if (gensymed_symbol_3 &&  !((SI_Long)0L == 
					inline_debugging_consing())) {
				    eval_cons = gensymed_symbol_3;
				  next_loop_2:
				    inline_note_reclaim_cons(eval_cons,Qeval);
				    if (EQ(eval_cons,gensymed_symbol_4))
					goto end_1;
				    else if ( !TRUEP(eval_cons))
					goto end_1;
				    else
					eval_cons = CDR(eval_cons);
				    goto next_loop_2;
				  end_loop_2:
				  end_1:;
				}
				if (ISVREF(Available_eval_conses_tail_vector,
					IFIX(Current_thread_index))) {
				    temp_2 = 
					    ISVREF(Available_eval_conses_tail_vector,
					    IFIX(Current_thread_index));
				    M_CDR(temp_2) = gensymed_symbol_3;
				    temp_2 = Available_eval_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(temp_2,svref_arg_2) = 
					    gensymed_symbol_4;
				}
				else {
				    temp_2 = Available_eval_conses_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(temp_2,svref_arg_2) = 
					    gensymed_symbol_3;
				    temp_2 = Available_eval_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(temp_2,svref_arg_2) = 
					    gensymed_symbol_4;
				}
				M_CDR(gensymed_symbol_4) = Nil;
			    }
			    CONTINUE_UNWINDING(0);
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		  }
		  else {
		      warning_message_for_wrong_reference_for_gfi_designation(gfi_output_frame,
			      designation,variable_qm);
		      reclaim_if_temporary_constant_function(variable_qm);
		  }
		  if (do_not_override_time_slice_p) {
		      Time_slice_expired_p = time_slice_expired_p();
		      temp_1 = TRUEP(Time_slice_expired_p);
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  if (temp_1)
		      goto end_loop;
		  designation_list = M_CDR(designation_list);
		  goto next_loop;
		end_loop:
		  number_of_designations_already_handled =  
			  !TRUEP(CDR(designation_list)) ? FIX((SI_Long)0L) 
			  : 
			  FIX(IFIX(number_of_designations_already_handled) 
			  + value_count);
		  if (do_not_override_time_slice_p && Time_slice_expired_p 
			  && (SI_Long)0L != 
			  IFIX(number_of_designations_already_handled)) {
		      set_non_savable_lookup_slot_value(gfi_output_frame,
			      Qnumber_of_periodic_specified_designation_handled,
			      number_of_designations_already_handled);
		      value = get_lookup_slot_value(gfi_output_frame,
			      Qgfi_output_file_update_frequency);
		      if (LISTP(value) && EQ(CAR(value),Qwrite_interval)) {
			  temp = SECOND(value);
			  temp_1 = CONSP(temp);
		      }
		      else
			  temp_1 = TRUEP(Nil);
		      if (temp_1) {
			  current_task_schedule_modify_1_arg_2 = 
				  get_slot_value_function(Data_server_parameters,
				  Qpriority_of_data_service,Nil);
			  current_task_schedule_modify_1_arg_8 = 
				  SYMBOL_FUNCTION(Qgfi_output_spreadsheet_values_periodically_task);
			  current_task_schedule_modify_1_arg_11 = 
				  gfi_output_frame;
			  schedule_task_qm = 
				  get_lookup_slot_value_given_default(gfi_output_frame,
				  Qgfi_output_scheduled_task,Nil);
			  if (schedule_task_qm) {
			      if (EQ(schedule_task_qm,Current_schedule_task))
				  Current_schedule_task = Nil;
			      if (ISVREF(schedule_task_qm,(SI_Long)6L))
				  cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
			      inline_note_reclaim_cons(schedule_task_qm,Nil);
			      structure_being_reclaimed = schedule_task_qm;
			      PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
				      0);
				reclaim_schedule_task_args(ISVREF(schedule_task_qm,
					(SI_Long)9L));
				SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
			      POP_SPECIAL();
			      temp_2 = 
				      ISVREF(Chain_of_available_schedule_tasks_vector,
				      IFIX(Current_thread_index));
			      SVREF(schedule_task_qm,FIX((SI_Long)0L)) = 
				      temp_2;
			      temp_2 = 
				      Chain_of_available_schedule_tasks_vector;
			      svref_arg_2 = Current_thread_index;
			      SVREF(temp_2,svref_arg_2) = schedule_task_qm;
			  }
			  def_structure_schedule_task_variable = 
				  ISVREF(Chain_of_available_schedule_tasks_vector,
				  IFIX(Current_thread_index));
			  if (def_structure_schedule_task_variable) {
			      temp_2 = 
				      Chain_of_available_schedule_tasks_vector;
			      svref_arg_2 = Current_thread_index;
			      svref_new_value = 
				      ISVREF(def_structure_schedule_task_variable,
				      (SI_Long)0L);
			      SVREF(temp_2,svref_arg_2) = svref_new_value;
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
				  FIX((SI_Long)2L)) = Nil;
			  SVREF(def_structure_schedule_task_variable,
				  FIX((SI_Long)9L)) = Nil;
			  task = def_structure_schedule_task_variable;
			  temp_2 = ISVREF(task,(SI_Long)1L);
			  aref_new_value = -1.0;
			  DFLOAT_ISASET_1(temp_2,(SI_Long)1L,aref_new_value);
			  SVREF(task,FIX((SI_Long)4L)) = 
				  current_task_schedule_modify_1_arg_2;
			  SVREF(task,FIX((SI_Long)5L)) = Nil;
			  SVREF(task,FIX((SI_Long)9L)) = Nil;
			  SVREF(task,FIX((SI_Long)10L)) = Nil;
			  g2_p =  !TRUEP(Nil);
			  SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
			  temp_2 = ISVREF(task,(SI_Long)1L);
			  aref_new_value = DFLOAT_ISAREF_1(g2_p ? 
				  Current_g2_time : Current_real_time,
				  (SI_Long)0L);
			  DFLOAT_ISASET_1(temp_2,(SI_Long)0L,aref_new_value);
			  SVREF(task,FIX((SI_Long)7L)) = 
				  Qgfi_output_spreadsheet_values_periodically_task;
			  SVREF(task,FIX((SI_Long)8L)) = 
				  current_task_schedule_modify_1_arg_8;
			  ISVREF(task,(SI_Long)12L) = FIX((SI_Long)2L);
			  SVREF(task,FIX((SI_Long)13L)) = 
				  current_task_schedule_modify_1_arg_11;
			  SVREF(task,FIX((SI_Long)14L)) = T;
			  ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
			  if (ctask);
			  else
			      ctask = System_is_running;
			  p = ISVREF(task,(SI_Long)4L);
			  v = ctask ? Current_task_queue_vector : 
				  Deferred_task_queue_vector;
			  q = ISVREF(v,IFIX(p));
			  SVREF(task,FIX((SI_Long)11L)) = q;
			  temp_2 = constant_queue_push_right(q,task);
			  SVREF(task,FIX((SI_Long)6L)) = temp_2;
			  if (ctask && FIXNUM_LT(p,Priority_of_next_task))
			      Priority_of_next_task = p;
			  set_non_savable_lookup_slot_value(gfi_output_frame,
				  Qgfi_output_scheduled_task,task);
		      }
		      result = VALUES_1(Nil);
		  }
		  else {
		      set_non_savable_lookup_slot_value(gfi_output_frame,
			      Qnumber_of_periodic_specified_designation_handled,
			      FIX((SI_Long)0L));
		      value = get_lookup_slot_value(gfi_output_frame,
			      Qgfi_output_file_update_frequency);
		      if (LISTP(value) && EQ(CAR(value),Qwrite_interval)) {
			  temp = SECOND(value);
			  temp_1 = CONSP(temp);
		      }
		      else
			  temp_1 = TRUEP(Nil);
		      if (temp_1) {
			  temp = Gensym_time;
			  execution_time = FIXNUM_MINUS(temp,
				  get_lookup_slot_value_given_default(gfi_output_frame,
				  Qgfi_output_scheduled_task_start_time,Nil));
			  future_task_schedule_modify_1_arg_2 = 
				  get_slot_value_function(Data_server_parameters,
				  Qpriority_of_data_service,Nil);
			  temp_3 = DFLOAT_ISAREF_1(Current_g2_time,
				  (SI_Long)0L);
			  temp = get_lookup_slot_value(gfi_output_frame,
				  Qgfi_output_file_update_frequency);
			  if (FIXNUM_GE(execution_time,CAADR(temp)))
			      temp_4 = (SI_Long)0L;
			  else {
			      temp = 
				      get_lookup_slot_value(gfi_output_frame,
				      Qgfi_output_file_update_frequency);
			      temp_4 = IFIX(FIXNUM_MINUS(CAADR(temp),
				      execution_time));
			  }
			  future_task_schedule_modify_1_arg_3 = temp_3 + 
				  (double)temp_4;
			  future_task_schedule_modify_1_arg_8 = 
				  SYMBOL_FUNCTION(Qgfi_output_spreadsheet_values_periodically_task);
			  future_task_schedule_modify_1_arg_11 = 
				  gfi_output_frame;
			  schedule_task_qm = 
				  get_lookup_slot_value_given_default(gfi_output_frame,
				  Qgfi_output_scheduled_task,Nil);
			  if (schedule_task_qm) {
			      if (EQ(schedule_task_qm,Current_schedule_task))
				  Current_schedule_task = Nil;
			      if (ISVREF(schedule_task_qm,(SI_Long)6L))
				  cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
			      inline_note_reclaim_cons(schedule_task_qm,Nil);
			      structure_being_reclaimed = schedule_task_qm;
			      PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
				      0);
				reclaim_schedule_task_args(ISVREF(schedule_task_qm,
					(SI_Long)9L));
				SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
			      POP_SPECIAL();
			      temp_2 = 
				      ISVREF(Chain_of_available_schedule_tasks_vector,
				      IFIX(Current_thread_index));
			      SVREF(schedule_task_qm,FIX((SI_Long)0L)) = 
				      temp_2;
			      temp_2 = 
				      Chain_of_available_schedule_tasks_vector;
			      svref_arg_2 = Current_thread_index;
			      SVREF(temp_2,svref_arg_2) = schedule_task_qm;
			  }
			  def_structure_schedule_task_variable = 
				  ISVREF(Chain_of_available_schedule_tasks_vector,
				  IFIX(Current_thread_index));
			  if (def_structure_schedule_task_variable) {
			      temp_2 = 
				      Chain_of_available_schedule_tasks_vector;
			      svref_arg_2 = Current_thread_index;
			      svref_new_value = 
				      ISVREF(def_structure_schedule_task_variable,
				      (SI_Long)0L);
			      SVREF(temp_2,svref_arg_2) = svref_new_value;
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
				  FIX((SI_Long)2L)) = Nil;
			  SVREF(def_structure_schedule_task_variable,
				  FIX((SI_Long)9L)) = Nil;
			  task = def_structure_schedule_task_variable;
			  temp_2 = ISVREF(task,(SI_Long)1L);
			  DFLOAT_ISASET_1(temp_2,(SI_Long)0L,
				  future_task_schedule_modify_1_arg_3);
			  temp_2 = ISVREF(task,(SI_Long)1L);
			  aref_new_value = -1.0;
			  DFLOAT_ISASET_1(temp_2,(SI_Long)1L,aref_new_value);
			  svref_new_value_1 =  !TRUEP(Nil);
			  SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 
				  ? T : Nil;
			  SVREF(task,FIX((SI_Long)4L)) = 
				  future_task_schedule_modify_1_arg_2;
			  SVREF(task,FIX((SI_Long)5L)) = Nil;
			  SVREF(task,FIX((SI_Long)9L)) = Nil;
			  SVREF(task,FIX((SI_Long)10L)) = Nil;
			  SVREF(task,FIX((SI_Long)7L)) = 
				  Qgfi_output_spreadsheet_values_periodically_task;
			  SVREF(task,FIX((SI_Long)8L)) = 
				  future_task_schedule_modify_1_arg_8;
			  ISVREF(task,(SI_Long)12L) = FIX((SI_Long)2L);
			  SVREF(task,FIX((SI_Long)13L)) = 
				  future_task_schedule_modify_1_arg_11;
			  SVREF(task,FIX((SI_Long)14L)) = T;
			  future_task_schedule_2(task);
			  set_non_savable_lookup_slot_value(gfi_output_frame,
				  Qgfi_output_scheduled_task,task);
			  set_non_savable_lookup_slot_value(gfi_output_frame,
				  Qgfi_output_scheduled_task_start_time,Nil);
		      }
		      gfi_terpri(gfi_output_frame);
		      result = VALUES_1(T);
		  }
	      }
	  }
	  else
	      result = VALUES_1(Nil);
	POP_SPECIAL();
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

/* GFI-OUTPUT-EVENT-LOG-VALUES-PERIODICALLY-TASK */
Object gfi_output_event_log_values_periodically_task(gfi_output_frame,
	    do_not_override_time_slice_p)
    Object gfi_output_frame, do_not_override_time_slice_p;
{
    Object temp;

    x_note_fn_call(217,75);
    temp = gfi_output_event_log_values_periodically(gfi_output_frame,
	    do_not_override_time_slice_p);
    return VALUES_1(temp);
}

/* GFI-OUTPUT-EVENT-LOG-VALUES-PERIODICALLY */
Object gfi_output_event_log_values_periodically(gfi_output_frame,
	    do_not_override_time_slice_p)
    Object gfi_output_frame, do_not_override_time_slice_p;
{
    Object time_slice_expired_p_1, output_stream, output_limit_qm;
    Object number_of_designations_already_handled, value, temp, temp_2;
    Object designation_list, designation, not_unique_designation_p;
    Object ab_loop_list_, unique_designation_p_1, current_computation_frame;
    Object eval_list_of_designation_values, designation_qm, variable;
    Object ab_loop_list__1, sub_class_bit_vector, current_computation_instance;
    Object current_computation_flags;
    volatile Object gensymed_symbol_3;
    Object variables_that_did_not_have_values, current_value, expiration_time;
    Object data_type, temp_3, gensymed_symbol_4, gensymed_symbol_5;
    Object gensymed_symbol_6, pruned_interest_list, eval_cons, svref_arg_2, x2;
    Object current_task_schedule_modify_1_arg_2;
    Object current_task_schedule_modify_1_arg_8;
    Object current_task_schedule_modify_1_arg_11, schedule_task_qm;
    Object structure_being_reclaimed, def_structure_schedule_task_variable;
    Object svref_new_value, task, ctask, p, v, q, execution_time;
    Object future_task_schedule_modify_1_arg_2;
    Object future_task_schedule_modify_1_arg_8;
    Object future_task_schedule_modify_1_arg_11;
    SI_Long value_count, superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, temp_5;
    char temp_1, g2_p, svref_new_value_1;
    double aref_new_value, temp_4, future_task_schedule_modify_1_arg_3;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(5);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(217,76);
    SAVE_STACK();
    if (get_lookup_slot_value_given_default(gfi_output_frame,
	    Qgfi_outputting_qm,Nil)) {
	time_slice_expired_p_1 = Nil;
	output_stream = 
		get_lookup_slot_value_given_default(gfi_output_frame,
		Qgfi_output_file_stream,Nil);
	output_limit_qm = get_lookup_slot_value(gfi_output_frame,
		Qmaximum_number_of_output_lines);
	number_of_designations_already_handled = 
		get_lookup_slot_value_given_default(gfi_output_frame,
		Qnumber_of_periodic_specified_designation_handled,Nil);
	if (number_of_designations_already_handled);
	else
	    number_of_designations_already_handled = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Time_slice_expired_p,Qtime_slice_expired_p,time_slice_expired_p_1,
		4);
	  if (output_stream) {
	      value = get_lookup_slot_value(gfi_output_frame,
		      Qgfi_output_file_update_frequency);
	      if (LISTP(value) && EQ(CAR(value),Qwrite_interval)) {
		  temp = SECOND(value);
		  temp_1 = CONSP(temp);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if (temp_1 ?  
		      !TRUEP(get_lookup_slot_value_given_default(gfi_output_frame,
		      Qgfi_output_scheduled_task_start_time,Nil)) : TRUEP(Nil))
		  set_non_savable_lookup_slot_value(gfi_output_frame,
			  Qgfi_output_scheduled_task_start_time,Gensym_time);
	      temp_2 = number_of_designations_already_handled;
	      temp = get_lookup_slot_value_given_default(gfi_output_frame,
		      Qgfi_output_values,Nil);
	      designation_list = nthcdr(temp_2,CAR(temp));
	      designation = Nil;
	      not_unique_designation_p = Nil;
	      ab_loop_list_ = 
		      get_lookup_slot_value_given_default(gfi_output_frame,
		      Qgfi_output_not_unique_designation_p_results,Nil);
	      unique_designation_p_1 = Nil;
	      value_count = (SI_Long)0L;
	    next_loop:
	      if ( !TRUEP(designation_list))
		  goto end_loop;
	      designation = CAR(designation_list);
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      not_unique_designation_p = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      unique_designation_p_1 =  !TRUEP(not_unique_designation_p) ? 
		      T : Nil;
	      value_count = value_count + (SI_Long)1L;
	      if (output_limit_qm && FIXNUM_LE(output_limit_qm,
		      get_lookup_slot_value_given_default(gfi_output_frame,
		      Qnumber_of_lines_output_so_far,Nil)))
		  warning_message_for_limit_reached_in_gfi_output(gfi_output_frame);
	      else {
		  current_computation_frame = gfi_output_frame;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
			  0);
		    eval_list_of_designation_values = 
			    serve_eval_list_of_designation_values(designation);
		  POP_SPECIAL();
		  value = get_lookup_slot_value(gfi_output_frame,
			  Qgfi_output_file_update_frequency);
		  if (LISTP(value) && EQ(CAR(value),Qwrite_interval)) {
		      temp = SECOND(value);
		      temp_1 = CONSP(temp);
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  if (temp_1 ?  
			  !TRUEP(get_lookup_slot_value_given_default(gfi_output_frame,
			  Qgfi_output_scheduled_task_start_time,Nil)) : 
			  TRUEP(Nil))
		      set_non_savable_lookup_slot_value(gfi_output_frame,
			      Qgfi_output_scheduled_task_start_time,
			      Gensym_time);
		  if (eval_list_of_designation_values) {
		      designation_qm = Nil;
		      variable = Nil;
		      ab_loop_list__1 = eval_list_of_designation_values;
		    next_loop_1:
		      if ( !TRUEP(ab_loop_list__1))
			  goto end_loop_1;
		      variable = M_CAR(ab_loop_list__1);
		      ab_loop_list__1 = M_CDR(ab_loop_list__1);
		      if (output_limit_qm && FIXNUM_LE(output_limit_qm,
			      get_lookup_slot_value_given_default(gfi_output_frame,
			      Qnumber_of_lines_output_so_far,Nil)))
			  goto end_loop_1;
		      if (unique_designation_p_1)
			  designation_qm = 
				  copy_tree_using_eval_conses_1(designation);
		      else if (SIMPLE_VECTOR_P(variable) && 
			      EQ(ISVREF(variable,(SI_Long)0L),
			      Qg2_defstruct_structure_name_temporary_constant_g2_struct))
			  designation_qm = Nil;
		      else
			  designation_qm = 
				  generate_designation_for_block(variable);
		      if (designation_qm) {
			  if ( !(SIMPLE_VECTOR_P(variable) && 
				  EQ(ISVREF(variable,(SI_Long)0L),
				  Qg2_defstruct_structure_name_temporary_constant_g2_struct))) 
				      {
			      sub_class_bit_vector = 
				      ISVREF(ISVREF(variable,(SI_Long)1L),
				      (SI_Long)19L);
			      superior_class_bit_number = 
				      IFIX(ISVREF(Variable_or_parameter_class_description,
				      (SI_Long)18L));
			      sub_class_vector_index = 
				      superior_class_bit_number >>  -  - 
				      (SI_Long)3L;
			      if (sub_class_vector_index < 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					  {
				  gensymed_symbol = 
					  UBYTE_8_ISAREF_1(sub_class_bit_vector,
					  sub_class_vector_index);
				  gensymed_symbol_1 = (SI_Long)1L;
				  gensymed_symbol_2 = 
					  superior_class_bit_number & 
					  (SI_Long)7L;
				  gensymed_symbol_1 = gensymed_symbol_1 << 
					  gensymed_symbol_2;
				  gensymed_symbol = gensymed_symbol & 
					  gensymed_symbol_1;
				  temp_1 = (SI_Long)0L < gensymed_symbol;
			      }
			      else
				  temp_1 = TRUEP(Nil);
			  }
			  else
			      temp_1 = TRUEP(Nil);
			  if (temp_1) {
			      current_computation_frame = variable;
			      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
				      3);
				current_computation_instance = 
					Current_computation_frame;
				PUSH_SPECIAL_WITH_SYMBOL(Current_computation_instance,Qcurrent_computation_instance,current_computation_instance,
					2);
				  current_computation_flags = 
					  Current_computation_flags;
				  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
					  1);
				    Current_computation_flags = 
					    FIX(IFIX(Current_computation_flags) 
					    &  ~(SI_Long)4L);
				    Current_computation_flags = 
					    FIX(IFIX(Current_computation_flags) 
					    | (SI_Long)256L);
				    gensymed_symbol_3 = Nil;
				    if (PUSH_UNWIND_PROTECT(0)) {
					variables_that_did_not_have_values 
						= Nil;
					PUSH_SPECIAL_WITH_SYMBOL(Variables_that_did_not_have_values,Qvariables_that_did_not_have_values,variables_that_did_not_have_values,
						0);
					  if (PUSH_LOCAL_ALLOCATION(Local_area,
						  0,0)) {
					      result = get_current_value(Current_computation_frame,
						      Nil);
					      MVS_3(result,current_value,
						      expiration_time,
						      data_type);
					      if (expiration_time) {
						  temp_3 = 
							  FIXNUM_ADD1(get_lookup_slot_value_given_default(gfi_output_frame,
							  Qnumber_of_lines_output_so_far,
							  Nil));
						  set_non_savable_lookup_slot_value(gfi_output_frame,
							  Qnumber_of_lines_output_so_far,
							  temp_3);
						  output_appropriate_gfi_time_stamp(gfi_output_frame,
							  Current_g2_time);
						  gfi_write_char(Gfi_delimitter,
							  gfi_output_frame);
						  write_designation_to_stream(designation_qm,
							  gfi_output_frame);
						  gfi_write_char(Gfi_delimitter,
							  gfi_output_frame);
						  output_gfi_value(current_value,
							  data_type,
							  gfi_output_frame);
						  gfi_terpri(gfi_output_frame);
					      }
					      if (expiration_time && 
						      text_string_p(current_value))
						  reclaim_text_string(current_value);
					  }
					  POP_LOCAL_ALLOCATION(0,0);
					  gensymed_symbol_3 = 
						  Variables_that_did_not_have_values;
					POP_SPECIAL();
				    }
				    POP_UNWIND_PROTECT(0);
				    if (gensymed_symbol_3) {
					gensymed_symbol_4 = gensymed_symbol_3;
					gensymed_symbol_5 = Nil;
					gensymed_symbol_6 = Nil;
				      next_loop_2:
					gensymed_symbol_5 = 
						CAR(gensymed_symbol_4);
					gensymed_symbol_6 = 
						CDR(gensymed_symbol_4);
					pruned_interest_list = 
						delete_eval_element_1(Qvalue_request_pending,
						ISVREF(gensymed_symbol_5,
						(SI_Long)36L));
					ISVREF(gensymed_symbol_5,
						(SI_Long)36L) = 
						pruned_interest_list;
					if ( !TRUEP(pruned_interest_list) 
						&&  
						!TRUEP(ISVREF(gensymed_symbol_5,
						(SI_Long)38L)))
					    withdraw_backward_chaining(gensymed_symbol_5);
					if ( !TRUEP(gensymed_symbol_6))
					    goto end_loop_2;
					gensymed_symbol_4 = gensymed_symbol_6;
					goto next_loop_2;
				      end_loop_2:
					if (gensymed_symbol_3 &&  
						!((SI_Long)0L == 
						inline_debugging_consing())) {
					    eval_cons = gensymed_symbol_3;
					  next_loop_3:
					    inline_note_reclaim_cons(eval_cons,
						    Qeval);
					    if (EQ(eval_cons,
						    gensymed_symbol_4))
						goto end_1;
					    else if ( !TRUEP(eval_cons))
						goto end_1;
					    else
						eval_cons = CDR(eval_cons);
					    goto next_loop_3;
					  end_loop_3:
					  end_1:;
					}
					if (ISVREF(Available_eval_conses_tail_vector,
						IFIX(Current_thread_index))) {
					    temp_3 = 
						    ISVREF(Available_eval_conses_tail_vector,
						    IFIX(Current_thread_index));
					    M_CDR(temp_3) = gensymed_symbol_3;
					    temp_3 = 
						    Available_eval_conses_tail_vector;
					    svref_arg_2 = Current_thread_index;
					    SVREF(temp_3,svref_arg_2) = 
						    gensymed_symbol_4;
					}
					else {
					    temp_3 = 
						    Available_eval_conses_vector;
					    svref_arg_2 = Current_thread_index;
					    SVREF(temp_3,svref_arg_2) = 
						    gensymed_symbol_3;
					    temp_3 = 
						    Available_eval_conses_tail_vector;
					    svref_arg_2 = Current_thread_index;
					    SVREF(temp_3,svref_arg_2) = 
						    gensymed_symbol_4;
					}
					M_CDR(gensymed_symbol_4) = Nil;
				    }
				    CONTINUE_UNWINDING(0);
				  POP_SPECIAL();
				POP_SPECIAL();
			      POP_SPECIAL();
			  }
			  else {
			      reclaim_if_temporary_constant_function(variable);
			      warning_message_for_wrong_reference_for_gfi_designation(gfi_output_frame,
				      designation_qm,variable);
			  }
		      }
		      else {
			  if (SIMPLE_VECTOR_P(variable) && 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(variable)) 
				  > (SI_Long)2L &&  !EQ(ISVREF(variable,
				  (SI_Long)1L),Qavailable_frame_vector)) {
			      x2 = ISVREF(variable,(SI_Long)1L);
			      temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				      (SI_Long)0L),
				      Qg2_defstruct_structure_name_class_description_g2_struct) 
				      ? TRUEP(x2) : TRUEP(Qnil);
			  }
			  else
			      temp_1 = TRUEP(Nil);
			  if ( !temp_1)
			      warning_message_for_non_frame_reference_for_gfi_designation(gfi_output_frame,
				      variable);
			  else
			      warning_message_for_unnameable_variable(gfi_output_frame,
				      variable,Nil);
		      }
		      if (unique_designation_p_1)
			  reclaim_eval_tree_1(designation_qm);
		      goto next_loop_1;
		    end_loop_1:
		      reclaim_eval_tree_1(eval_list_of_designation_values);
		  }
		  else
		      warning_message_for_wrong_reference_for_gfi_designation(gfi_output_frame,
			      designation,Nil);
	      }
	      if (do_not_override_time_slice_p) {
		  Time_slice_expired_p = time_slice_expired_p();
		  temp_1 = TRUEP(Time_slice_expired_p);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if (temp_1)
		  goto end_loop;
	      designation_list = M_CDR(designation_list);
	      goto next_loop;
	    end_loop:
	      number_of_designations_already_handled =  
		      !TRUEP(CDR(designation_list)) ? FIX((SI_Long)0L) : 
		      FIX(IFIX(number_of_designations_already_handled) + 
		      value_count);
	      if (do_not_override_time_slice_p && Time_slice_expired_p) {
		  set_non_savable_lookup_slot_value(gfi_output_frame,
			  Qnumber_of_periodic_specified_designation_handled,
			  number_of_designations_already_handled);
		  value = get_lookup_slot_value(gfi_output_frame,
			  Qgfi_output_file_update_frequency);
		  if (LISTP(value) && EQ(CAR(value),Qwrite_interval)) {
		      temp = SECOND(value);
		      temp_1 = CONSP(temp);
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  if (temp_1) {
		      current_task_schedule_modify_1_arg_2 = 
			      get_slot_value_function(Data_server_parameters,
			      Qpriority_of_data_service,Nil);
		      current_task_schedule_modify_1_arg_8 = 
			      SYMBOL_FUNCTION(Qgfi_output_event_log_values_periodically_task);
		      current_task_schedule_modify_1_arg_11 = gfi_output_frame;
		      schedule_task_qm = 
			      get_lookup_slot_value_given_default(gfi_output_frame,
			      Qgfi_output_scheduled_task,Nil);
		      if (schedule_task_qm) {
			  if (EQ(schedule_task_qm,Current_schedule_task))
			      Current_schedule_task = Nil;
			  if (ISVREF(schedule_task_qm,(SI_Long)6L))
			      cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
			  inline_note_reclaim_cons(schedule_task_qm,Nil);
			  structure_being_reclaimed = schedule_task_qm;
			  PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
				  0);
			    reclaim_schedule_task_args(ISVREF(schedule_task_qm,
				    (SI_Long)9L));
			    SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
			  POP_SPECIAL();
			  temp_3 = 
				  ISVREF(Chain_of_available_schedule_tasks_vector,
				  IFIX(Current_thread_index));
			  SVREF(schedule_task_qm,FIX((SI_Long)0L)) = temp_3;
			  temp_3 = Chain_of_available_schedule_tasks_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp_3,svref_arg_2) = schedule_task_qm;
		      }
		      def_structure_schedule_task_variable = 
			      ISVREF(Chain_of_available_schedule_tasks_vector,
			      IFIX(Current_thread_index));
		      if (def_structure_schedule_task_variable) {
			  temp_3 = Chain_of_available_schedule_tasks_vector;
			  svref_arg_2 = Current_thread_index;
			  svref_new_value = 
				  ISVREF(def_structure_schedule_task_variable,
				  (SI_Long)0L);
			  SVREF(temp_3,svref_arg_2) = svref_new_value;
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
			      FIX((SI_Long)2L)) = Nil;
		      SVREF(def_structure_schedule_task_variable,
			      FIX((SI_Long)9L)) = Nil;
		      task = def_structure_schedule_task_variable;
		      temp_3 = ISVREF(task,(SI_Long)1L);
		      aref_new_value = -1.0;
		      DFLOAT_ISASET_1(temp_3,(SI_Long)1L,aref_new_value);
		      SVREF(task,FIX((SI_Long)4L)) = 
			      current_task_schedule_modify_1_arg_2;
		      SVREF(task,FIX((SI_Long)5L)) = Nil;
		      SVREF(task,FIX((SI_Long)9L)) = Nil;
		      SVREF(task,FIX((SI_Long)10L)) = Nil;
		      g2_p =  !TRUEP(Nil);
		      SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
		      temp_3 = ISVREF(task,(SI_Long)1L);
		      aref_new_value = DFLOAT_ISAREF_1(g2_p ? 
			      Current_g2_time : Current_real_time,(SI_Long)0L);
		      DFLOAT_ISASET_1(temp_3,(SI_Long)0L,aref_new_value);
		      SVREF(task,FIX((SI_Long)7L)) = 
			      Qgfi_output_event_log_values_periodically_task;
		      SVREF(task,FIX((SI_Long)8L)) = 
			      current_task_schedule_modify_1_arg_8;
		      ISVREF(task,(SI_Long)12L) = FIX((SI_Long)2L);
		      SVREF(task,FIX((SI_Long)13L)) = 
			      current_task_schedule_modify_1_arg_11;
		      SVREF(task,FIX((SI_Long)14L)) = T;
		      ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
		      if (ctask);
		      else
			  ctask = System_is_running;
		      p = ISVREF(task,(SI_Long)4L);
		      v = ctask ? Current_task_queue_vector : 
			      Deferred_task_queue_vector;
		      q = ISVREF(v,IFIX(p));
		      SVREF(task,FIX((SI_Long)11L)) = q;
		      temp_3 = constant_queue_push_right(q,task);
		      SVREF(task,FIX((SI_Long)6L)) = temp_3;
		      if (ctask && FIXNUM_LT(p,Priority_of_next_task))
			  Priority_of_next_task = p;
		      set_non_savable_lookup_slot_value(gfi_output_frame,
			      Qgfi_output_scheduled_task,task);
		  }
		  result = VALUES_1(Nil);
	      }
	      else {
		  set_non_savable_lookup_slot_value(gfi_output_frame,
			  Qnumber_of_periodic_specified_designation_handled,
			  FIX((SI_Long)0L));
		  value = get_lookup_slot_value(gfi_output_frame,
			  Qgfi_output_file_update_frequency);
		  if (LISTP(value) && EQ(CAR(value),Qwrite_interval)) {
		      temp = SECOND(value);
		      temp_1 = CONSP(temp);
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  if (temp_1) {
		      temp = Gensym_time;
		      execution_time = FIXNUM_MINUS(temp,
			      get_lookup_slot_value_given_default(gfi_output_frame,
			      Qgfi_output_scheduled_task_start_time,Nil));
		      future_task_schedule_modify_1_arg_2 = 
			      get_slot_value_function(Data_server_parameters,
			      Qpriority_of_data_service,Nil);
		      temp_4 = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L);
		      temp = get_lookup_slot_value(gfi_output_frame,
			      Qgfi_output_file_update_frequency);
		      if (FIXNUM_GE(execution_time,CAADR(temp)))
			  temp_5 = (SI_Long)0L;
		      else {
			  temp = get_lookup_slot_value(gfi_output_frame,
				  Qgfi_output_file_update_frequency);
			  temp_5 = IFIX(FIXNUM_MINUS(CAADR(temp),
				  execution_time));
		      }
		      future_task_schedule_modify_1_arg_3 = temp_4 + 
			      (double)temp_5;
		      future_task_schedule_modify_1_arg_8 = 
			      SYMBOL_FUNCTION(Qgfi_output_event_log_values_periodically_task);
		      future_task_schedule_modify_1_arg_11 = gfi_output_frame;
		      schedule_task_qm = 
			      get_lookup_slot_value_given_default(gfi_output_frame,
			      Qgfi_output_scheduled_task,Nil);
		      if (schedule_task_qm) {
			  if (EQ(schedule_task_qm,Current_schedule_task))
			      Current_schedule_task = Nil;
			  if (ISVREF(schedule_task_qm,(SI_Long)6L))
			      cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
			  inline_note_reclaim_cons(schedule_task_qm,Nil);
			  structure_being_reclaimed = schedule_task_qm;
			  PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
				  0);
			    reclaim_schedule_task_args(ISVREF(schedule_task_qm,
				    (SI_Long)9L));
			    SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
			  POP_SPECIAL();
			  temp_3 = 
				  ISVREF(Chain_of_available_schedule_tasks_vector,
				  IFIX(Current_thread_index));
			  SVREF(schedule_task_qm,FIX((SI_Long)0L)) = temp_3;
			  temp_3 = Chain_of_available_schedule_tasks_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp_3,svref_arg_2) = schedule_task_qm;
		      }
		      def_structure_schedule_task_variable = 
			      ISVREF(Chain_of_available_schedule_tasks_vector,
			      IFIX(Current_thread_index));
		      if (def_structure_schedule_task_variable) {
			  temp_3 = Chain_of_available_schedule_tasks_vector;
			  svref_arg_2 = Current_thread_index;
			  svref_new_value = 
				  ISVREF(def_structure_schedule_task_variable,
				  (SI_Long)0L);
			  SVREF(temp_3,svref_arg_2) = svref_new_value;
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
			      FIX((SI_Long)2L)) = Nil;
		      SVREF(def_structure_schedule_task_variable,
			      FIX((SI_Long)9L)) = Nil;
		      task = def_structure_schedule_task_variable;
		      temp_3 = ISVREF(task,(SI_Long)1L);
		      DFLOAT_ISASET_1(temp_3,(SI_Long)0L,
			      future_task_schedule_modify_1_arg_3);
		      temp_3 = ISVREF(task,(SI_Long)1L);
		      aref_new_value = -1.0;
		      DFLOAT_ISASET_1(temp_3,(SI_Long)1L,aref_new_value);
		      svref_new_value_1 =  !TRUEP(Nil);
		      SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T 
			      : Nil;
		      SVREF(task,FIX((SI_Long)4L)) = 
			      future_task_schedule_modify_1_arg_2;
		      SVREF(task,FIX((SI_Long)5L)) = Nil;
		      SVREF(task,FIX((SI_Long)9L)) = Nil;
		      SVREF(task,FIX((SI_Long)10L)) = Nil;
		      SVREF(task,FIX((SI_Long)7L)) = 
			      Qgfi_output_event_log_values_periodically_task;
		      SVREF(task,FIX((SI_Long)8L)) = 
			      future_task_schedule_modify_1_arg_8;
		      ISVREF(task,(SI_Long)12L) = FIX((SI_Long)2L);
		      SVREF(task,FIX((SI_Long)13L)) = 
			      future_task_schedule_modify_1_arg_11;
		      SVREF(task,FIX((SI_Long)14L)) = T;
		      future_task_schedule_2(task);
		      set_non_savable_lookup_slot_value(gfi_output_frame,
			      Qgfi_output_scheduled_task,task);
		      set_non_savable_lookup_slot_value(gfi_output_frame,
			      Qgfi_output_scheduled_task_start_time,Nil);
		  }
		  result = VALUES_1(T);
	      }
	  }
	  else
	      result = VALUES_1(Nil);
	POP_SPECIAL();
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

static Object Qrenamed_gfi_output_file_pathname_qm;  /* renamed-gfi-output-file-pathname? */

static Object string_constant_15;  /* "Error in renaming file ~S to ~S upon close of file." */

static Object string_constant_16;  /* "The file ~S for the GFI Output Interface ~NF was not renamed." */

static Object Qclosed;             /* closed */

/* CLOSE-GFI-OUTPUT-INTERFACE */
Object close_gfi_output_interface(gfi_output_frame,flush_queues_to_file_qm)
    Object gfi_output_frame, flush_queues_to_file_qm;
{
    Object schedule_task_qm, structure_being_reclaimed, temp, svref_arg_2;
    Object line_limit_qm, value_list, managed_value_qm, ab_loop_list_;
    Object queue_pair_, output_stream, temp_1, old_pathname, new_pathname_qm;
    Declare_special(1);

    x_note_fn_call(217,77);
    if (get_lookup_slot_value_given_default(gfi_output_frame,
	    Qgfi_output_scheduled_task,Nil)) {
	schedule_task_qm = 
		get_lookup_slot_value_given_default(gfi_output_frame,
		Qgfi_output_scheduled_task,Nil);
	if (schedule_task_qm) {
	    if (EQ(schedule_task_qm,Current_schedule_task))
		Current_schedule_task = Nil;
	    if (ISVREF(schedule_task_qm,(SI_Long)6L))
		cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
	    inline_note_reclaim_cons(schedule_task_qm,Nil);
	    structure_being_reclaimed = schedule_task_qm;
	    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		    0);
	      reclaim_schedule_task_args(ISVREF(schedule_task_qm,(SI_Long)9L));
	      SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
	    POP_SPECIAL();
	    temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    SVREF(schedule_task_qm,FIX((SI_Long)0L)) = temp;
	    temp = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = schedule_task_qm;
	}
	set_non_savable_lookup_slot_value(gfi_output_frame,
		Qgfi_output_scheduled_task,Nil);
    }
    line_limit_qm = get_lookup_slot_value(gfi_output_frame,
	    Qmaximum_number_of_output_lines);
    if (flush_queues_to_file_qm && 
	    get_lookup_slot_value_given_default(gfi_output_frame,
	    Qgfi_outputting_qm,Nil) && ( !TRUEP(line_limit_qm) || 
	    FIXNUM_LT(get_lookup_slot_value_given_default(gfi_output_frame,
	    Qnumber_of_lines_output_so_far,Nil),line_limit_qm)))
	output_gfi_queued_values_to_stream(gfi_output_frame,T);
    if (EQ(get_lookup_slot_value(gfi_output_frame,Qgfi_output_file_format),
	    Qspreadsheet)) {
	value_list = get_lookup_slot_value_given_default(gfi_output_frame,
		Qgfi_list_of_new_spreadsheet_output_values,Nil);
	managed_value_qm = Nil;
	ab_loop_list_ = value_list;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	managed_value_qm = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	managed_value_qm = 
		reclaim_managed_number_or_value_function(managed_value_qm);
	goto next_loop;
      end_loop:
	reclaim_gfi_list_1(value_list);
    }
    set_non_savable_lookup_slot_value(gfi_output_frame,
	    Qgfi_list_of_new_spreadsheet_output_values,Nil);
    queue_pair_ = get_lookup_slot_value_given_default(gfi_output_frame,
	    Qgfi_queue_of_new_output_values,Nil);
    if (queue_pair_) {
	reclaim_gfi_queue_of_new_output_values_contents(queue_pair_);
	inline_note_reclaim_cons(queue_pair_,Qgfi);
	if (ISVREF(Available_gfi_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_gfi_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = queue_pair_;
	    temp = Available_gfi_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = queue_pair_;
	}
	else {
	    temp = Available_gfi_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = queue_pair_;
	    temp = Available_gfi_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = queue_pair_;
	}
	M_CDR(queue_pair_) = Nil;
    }
    set_non_savable_lookup_slot_value(gfi_output_frame,
	    Qgfi_queue_of_new_output_values,Nil);
    set_non_savable_lookup_slot_value(gfi_output_frame,
	    Qnew_gfi_output_values_this_cycle_qm,Nil);
    if (get_lookup_slot_value_given_default(gfi_output_frame,
	    Qgfi_output_without_interruption_qm,Nil))
	gfi_delete_from_queue(gfi_output_frame,
		Queue_of_active_uninterruptable_gfi_output_interface_objects);
    else
	gfi_delete_from_queue(gfi_output_frame,
		Queue_of_active_gfi_output_interface_objects);
    set_non_savable_lookup_slot_value(gfi_output_frame,Qgfi_outputting_qm,Nil);
    output_stream = get_lookup_slot_value_given_default(gfi_output_frame,
	    Qgfi_output_file_stream,Nil);
    if (output_stream) {
	temp_1 = get_lookup_slot_value_given_default(gfi_output_frame,
		Qgfi_output_values,Nil);
	temp_1 = CAR(temp_1);
	deinstall_gfi_true_value_update(gfi_output_frame,temp_1,
		get_lookup_slot_value_given_default(gfi_output_frame,
		Qgfi_output_not_unique_designation_p_results,Nil));
	g2_stream_close(output_stream);
	if (get_lookup_slot_value(gfi_output_frame,
		Qrenamed_gfi_output_file_pathname_qm)) {
	    old_pathname = 
		    get_lookup_slot_value_given_default(gfi_output_frame,
		    Qgfi_output_pathname_string_of_stream_qm,Nil);
	    new_pathname_qm = 
		    get_pathname_for_gfi_interface(gfi_output_frame,
		    Qrenamed_gfi_output_file_pathname_qm);
	    if (new_pathname_qm) {
		if ( !TRUEP(g2_stream_rename_file(old_pathname,
			new_pathname_qm))) {
		    Suppress_warning_message_header_qm = T;
		    if ((SI_Long)2L <= IFIX(Warning_message_level))
			give_warning_1(4,FIX((SI_Long)2L),
				string_constant_15,old_pathname,
				new_pathname_qm);
		    Suppress_warning_message_header_qm = Nil;
		}
		if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(new_pathname_qm) != 
			(SI_Long)0L)
		    reclaim_wide_string(new_pathname_qm);
	    }
	    else {
		Suppress_warning_message_header_qm = T;
		if ((SI_Long)2L <= IFIX(Warning_message_level))
		    give_warning_1(4,FIX((SI_Long)2L),string_constant_16,
			    old_pathname,gfi_output_frame);
		Suppress_warning_message_header_qm = Nil;
	    }
	}
	change_slot_value(3,gfi_output_frame,Qfile_status,Qclosed);
	set_non_savable_lookup_slot_value(gfi_output_frame,
		Qgfi_output_file_stream,Nil);
    }
    else if ( !EQ(get_slot_value_function(gfi_output_frame,Qfile_status,
	    Nil),Qfailed_to_open))
	change_slot_value(3,gfi_output_frame,Qfile_status,Qready_to_open);
    if (get_lookup_slot_value_given_default(gfi_output_frame,
	    Qgfi_output_pathname_string_of_stream_qm,Nil)) {
	reclaim_text_string(get_lookup_slot_value_given_default(gfi_output_frame,
		Qgfi_output_pathname_string_of_stream_qm,Nil));
	return set_non_savable_lookup_slot_value(gfi_output_frame,
		Qgfi_output_pathname_string_of_stream_qm,Nil);
    }
    else
	return VALUES_1(Nil);
}

/* DEACTIVATE-FOR-GFI-OUTPUT-INTERFACE */
Object deactivate_for_gfi_output_interface(gfi_output_interface)
    Object gfi_output_interface;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(217,78);
    close_gfi_output_interface(gfi_output_interface,T);
    frame = gfi_output_interface;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)7L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qgfi_output_interface)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	return inline_funcall_1(method_function_qm,frame);
    else
	return VALUES_1(Nil);
}

static Object Qgfi_input_when_active;  /* gfi-input-when-active */

static Object Qgfi_inputting_qm;   /* gfi-inputting? */

static Object Qno_gfi_input_file_pathname;  /* no-gfi-input-file-pathname */

/* PUT-GFI-INPUT-FILE-PATHNAME */
Object put_gfi_input_file_pathname(frame,new_value,gensymed_symbol)
    Object frame, new_value, gensymed_symbol;
{
    Object gensymed_symbol_1, gensymed_symbol_2, temp;
    char temp_1;

    x_note_fn_call(217,79);
    gensymed_symbol = frame;
    gensymed_symbol_1 = new_value;
    gensymed_symbol_2 = Qgfi_input_file_pathname;
    if ((SI_Long)0L != (IFIX(ISVREF(gensymed_symbol,(SI_Long)5L)) & 
	    (SI_Long)1L) && get_lookup_slot_value(gensymed_symbol,
	    Qgfi_input_when_active) && 
	    get_lookup_slot_value_given_default(gensymed_symbol,
	    Qgfi_inputting_qm,Nil))
	close_gfi_input_interface(gensymed_symbol);
    set_slot_value_function(gensymed_symbol,gensymed_symbol_2,
	    gensymed_symbol_1,Nil);
    if ( !TRUEP(new_value)) {
	add_frame_note(2,Qno_gfi_input_file_pathname,frame);
	update_frame_status(frame,Qincomplete,Nil);
    }
    else {
	delete_frame_note_if_any(Qno_gfi_input_file_pathname,frame);
	if (gfi_input_interface_non_default_slots_set_p(frame))
	    update_frame_status(frame,Nil,Nil);
    }
    if ((SI_Long)0L != (IFIX(ISVREF(gensymed_symbol,(SI_Long)5L)) & 
	    (SI_Long)1L) && get_lookup_slot_value(gensymed_symbol,
	    Qgfi_input_when_active)) {
	temp = ISVREF(gensymed_symbol,(SI_Long)8L);
	temp_1 =  !TRUEP(CAR(temp));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	prepare_gfi_input_interface_to_open(gensymed_symbol);
    return VALUES_2(gensymed_symbol_1,Nil);
}

static Object Qgfi_input_file_format;  /* gfi-input-file-format */

/* PUT-GFI-INPUT-FILE-FORMAT */
Object put_gfi_input_file_format(frame,new_value,gensymed_symbol)
    Object frame, new_value, gensymed_symbol;
{
    Object gensymed_symbol_1, gensymed_symbol_2, temp;
    char temp_1;

    x_note_fn_call(217,80);
    gensymed_symbol = frame;
    gensymed_symbol_1 = new_value;
    gensymed_symbol_2 = Qgfi_input_file_format;
    if ((SI_Long)0L != (IFIX(ISVREF(gensymed_symbol,(SI_Long)5L)) & 
	    (SI_Long)1L) && get_lookup_slot_value(gensymed_symbol,
	    Qgfi_input_when_active) && 
	    get_lookup_slot_value_given_default(gensymed_symbol,
	    Qgfi_inputting_qm,Nil))
	close_gfi_input_interface(gensymed_symbol);
    set_slot_value_function(gensymed_symbol,gensymed_symbol_2,
	    gensymed_symbol_1,Nil);
    if ((SI_Long)0L != (IFIX(ISVREF(gensymed_symbol,(SI_Long)5L)) & 
	    (SI_Long)1L) && get_lookup_slot_value(gensymed_symbol,
	    Qgfi_input_when_active)) {
	temp = ISVREF(gensymed_symbol,(SI_Long)8L);
	temp_1 =  !TRUEP(CAR(temp));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	prepare_gfi_input_interface_to_open(gensymed_symbol);
    return VALUES_2(gensymed_symbol_1,Nil);
}

static Object Qgfi_input_time_stamp_format;  /* gfi-input-time-stamp-format */

/* PUT-GFI-INPUT-TIME-STAMP-FORMAT */
Object put_gfi_input_time_stamp_format(frame,new_value,gensymed_symbol)
    Object frame, new_value, gensymed_symbol;
{
    Object gensymed_symbol_1, gensymed_symbol_2, temp;
    char temp_1;

    x_note_fn_call(217,81);
    gensymed_symbol = frame;
    gensymed_symbol_1 = new_value;
    gensymed_symbol_2 = Qgfi_input_time_stamp_format;
    if ((SI_Long)0L != (IFIX(ISVREF(gensymed_symbol,(SI_Long)5L)) & 
	    (SI_Long)1L) && get_lookup_slot_value(gensymed_symbol,
	    Qgfi_input_when_active) && 
	    get_lookup_slot_value_given_default(gensymed_symbol,
	    Qgfi_inputting_qm,Nil))
	close_gfi_input_interface(gensymed_symbol);
    set_slot_value_function(gensymed_symbol,gensymed_symbol_2,
	    gensymed_symbol_1,Nil);
    if ((SI_Long)0L != (IFIX(ISVREF(gensymed_symbol,(SI_Long)5L)) & 
	    (SI_Long)1L) && get_lookup_slot_value(gensymed_symbol,
	    Qgfi_input_when_active)) {
	temp = ISVREF(gensymed_symbol,(SI_Long)8L);
	temp_1 =  !TRUEP(CAR(temp));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	prepare_gfi_input_interface_to_open(gensymed_symbol);
    return VALUES_2(gensymed_symbol_1,Nil);
}

static Object Qignore_gfi_input_base_time_qm;  /* ignore-gfi-input-base-time? */

/* PUT-IGNORE-GFI-INPUT-BASE-TIME? */
Object put_ignore_gfi_input_base_time_qm(frame,new_value,gensymed_symbol)
    Object frame, new_value, gensymed_symbol;
{
    Object gensymed_symbol_1, gensymed_symbol_2, temp;
    char temp_1;

    x_note_fn_call(217,82);
    gensymed_symbol = frame;
    gensymed_symbol_1 = new_value;
    gensymed_symbol_2 = Qignore_gfi_input_base_time_qm;
    if ((SI_Long)0L != (IFIX(ISVREF(gensymed_symbol,(SI_Long)5L)) & 
	    (SI_Long)1L) && get_lookup_slot_value(gensymed_symbol,
	    Qgfi_input_when_active) && 
	    get_lookup_slot_value_given_default(gensymed_symbol,
	    Qgfi_inputting_qm,Nil))
	close_gfi_input_interface(gensymed_symbol);
    set_slot_value_function(gensymed_symbol,gensymed_symbol_2,
	    gensymed_symbol_1,Nil);
    if ((SI_Long)0L != (IFIX(ISVREF(gensymed_symbol,(SI_Long)5L)) & 
	    (SI_Long)1L) && get_lookup_slot_value(gensymed_symbol,
	    Qgfi_input_when_active)) {
	temp = ISVREF(gensymed_symbol,(SI_Long)8L);
	temp_1 =  !TRUEP(CAR(temp));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	prepare_gfi_input_interface_to_open(gensymed_symbol);
    return VALUES_2(gensymed_symbol_1,Nil);
}

static Object Qgfi_input_variables_update_mode;  /* gfi-input-variables-update-mode */

static Object Qno_gfi_input_variables_update_mode;  /* no-gfi-input-variables-update-mode */

static Object Qinput_one_shot_when_activated_without_interruption;  /* input-one-shot-when-activated-without-interruption */

static Object Qgfi_input_without_interruption_qm;  /* gfi-input-without-interruption? */

/* PUT-GFI-INPUT-VARIABLES-UPDATE-MODE */
Object put_gfi_input_variables_update_mode(frame,new_value,gensymed_symbol)
    Object frame, new_value, gensymed_symbol;
{
    Object gensymed_symbol_1, gensymed_symbol_2, temp;
    char temp_1;

    x_note_fn_call(217,83);
    gensymed_symbol = frame;
    gensymed_symbol_1 = new_value;
    gensymed_symbol_2 = Qgfi_input_variables_update_mode;
    if ((SI_Long)0L != (IFIX(ISVREF(gensymed_symbol,(SI_Long)5L)) & 
	    (SI_Long)1L) && get_lookup_slot_value(gensymed_symbol,
	    Qgfi_input_when_active) && 
	    get_lookup_slot_value_given_default(gensymed_symbol,
	    Qgfi_inputting_qm,Nil))
	close_gfi_input_interface(gensymed_symbol);
    set_slot_value_function(gensymed_symbol,gensymed_symbol_2,
	    gensymed_symbol_1,Nil);
    if ( !TRUEP(new_value)) {
	add_frame_note(2,Qno_gfi_input_variables_update_mode,frame);
	update_frame_status(frame,Qincomplete,Nil);
    }
    else {
	delete_frame_note_if_any(Qno_gfi_input_variables_update_mode,frame);
	if (gfi_input_interface_non_default_slots_set_p(frame))
	    update_frame_status(frame,Nil,Nil);
	if (EQ(new_value,Qinput_one_shot_when_activated_without_interruption))
	    change_slot_value(3,frame,Qgfi_input_without_interruption_qm,T);
	else
	    change_slot_value(3,frame,Qgfi_input_without_interruption_qm,Nil);
    }
    if ((SI_Long)0L != (IFIX(ISVREF(gensymed_symbol,(SI_Long)5L)) & 
	    (SI_Long)1L) && get_lookup_slot_value(gensymed_symbol,
	    Qgfi_input_when_active)) {
	temp = ISVREF(gensymed_symbol,(SI_Long)8L);
	temp_1 =  !TRUEP(CAR(temp));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	prepare_gfi_input_interface_to_open(gensymed_symbol);
    return VALUES_2(gensymed_symbol_1,Nil);
}

/* PUT-GFI-INPUT-WHEN-ACTIVE */
Object put_gfi_input_when_active(frame,new_value,gensymed_symbol)
    Object frame, new_value, gensymed_symbol;
{
    Object gensymed_symbol_1, gensymed_symbol_2, temp;
    char temp_1;

    x_note_fn_call(217,84);
    gensymed_symbol = frame;
    gensymed_symbol_1 = new_value;
    gensymed_symbol_2 = Qgfi_input_when_active;
    if ((SI_Long)0L != (IFIX(ISVREF(gensymed_symbol,(SI_Long)5L)) & 
	    (SI_Long)1L) && get_lookup_slot_value(gensymed_symbol,
	    Qgfi_input_when_active) && 
	    get_lookup_slot_value_given_default(gensymed_symbol,
	    Qgfi_inputting_qm,Nil))
	close_gfi_input_interface(gensymed_symbol);
    set_slot_value_function(gensymed_symbol,gensymed_symbol_2,
	    gensymed_symbol_1,Nil);
    if ((SI_Long)0L != (IFIX(ISVREF(gensymed_symbol,(SI_Long)5L)) & 
	    (SI_Long)1L) && get_lookup_slot_value(gensymed_symbol,
	    Qgfi_input_when_active)) {
	temp = ISVREF(gensymed_symbol,(SI_Long)8L);
	temp_1 =  !TRUEP(CAR(temp));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	prepare_gfi_input_interface_to_open(gensymed_symbol);
    return VALUES_2(gensymed_symbol_1,Nil);
}

static Object Qgfi_input_interface;  /* gfi-input-interface */

/* INITIALIZE-FOR-GFI-INPUT-INTERFACE */
Object initialize_for_gfi_input_interface(gfi_input_interface)
    Object gfi_input_interface;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(217,85);
    frame = gfi_input_interface;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)2L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qgfi_input_interface)) {
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
    change_slot_value(3,gfi_input_interface,Qfile_system,G2_operating_system);
    if ( 
	    !TRUEP(gfi_input_interface_non_default_slots_set_p(gfi_input_interface))) 
		{
	add_any_gfi_input_incomplete_frame_notes(gfi_input_interface);
	return update_frame_status(gfi_input_interface,Qincomplete,Nil);
    }
    else
	return VALUES_1(Nil);
}

/* INITIALIZE-AFTER-READING-FOR-GFI-INPUT-INTERFACE */
Object initialize_after_reading_for_gfi_input_interface(gfi_input_interface)
    Object gfi_input_interface;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(217,86);
    frame = gfi_input_interface;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)4L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qgfi_input_interface)) {
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
    change_slot_value(3,gfi_input_interface,Qfile_system,G2_operating_system);
    if ( 
	    !TRUEP(gfi_input_interface_non_default_slots_set_p(gfi_input_interface))) 
		{
	add_any_gfi_input_incomplete_frame_notes(gfi_input_interface);
	return update_frame_status(gfi_input_interface,Qincomplete,Nil);
    }
    else
	return VALUES_1(Nil);
}

/* GFI-INPUT-INTERFACE-NON-DEFAULT-SLOTS-SET-P */
Object gfi_input_interface_non_default_slots_set_p(gfi_input_interface)
    Object gfi_input_interface;
{
    x_note_fn_call(217,87);
    return VALUES_1(get_lookup_slot_value(gfi_input_interface,
	    Qgfi_input_variables_update_mode) && 
	    get_lookup_slot_value(gfi_input_interface,
	    Qgfi_input_file_pathname) ? T : Qnil);
}

/* ADD-ANY-GFI-INPUT-INCOMPLETE-FRAME-NOTES */
Object add_any_gfi_input_incomplete_frame_notes(gfi_input_interface)
    Object gfi_input_interface;
{
    x_note_fn_call(217,88);
    if ( !TRUEP(get_lookup_slot_value(gfi_input_interface,
	    Qgfi_input_variables_update_mode)))
	add_frame_note(2,Qno_gfi_input_variables_update_mode,
		gfi_input_interface);
    if ( !TRUEP(get_lookup_slot_value(gfi_input_interface,
	    Qgfi_input_file_pathname)))
	add_frame_note(2,Qno_gfi_input_file_pathname,gfi_input_interface);
    return VALUES_1(Nil);
}

/* ACTIVATE-FOR-GFI-INPUT-INTERFACE */
Object activate_for_gfi_input_interface(gfi_input_interface)
    Object gfi_input_interface;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(217,89);
    if (get_lookup_slot_value(gfi_input_interface,Qgfi_input_when_active))
	prepare_gfi_input_interface_to_open(gfi_input_interface);
    frame = gfi_input_interface;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)6L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qgfi_input_interface)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	return inline_funcall_1(method_function_qm,frame);
    else
	return VALUES_1(Nil);
}

static Object string_constant_17;  /* "While activating ~NF, the GFI input file could not be ~
				    *                 opened.  This item is incomplete."
				    */

static Object Qnupec_catch_up;     /* nupec-catch-up */

static Object string_constant_18;  /* "When using a GFI file format of NUPEC snapshot-with-restart-time ~
				    *             for ~NF, the scheduler-mode of timing-parameters must be ~
				    *             NUPEC-catch-up-mode."
				    */

static Object string_constant_19;  /* "When using a GFI file format of NUPEC snapshot ~
				    *             for ~NF, the scheduler-mode of timing-parameters must not be ~
				    *             NUPEC-catch-up-mode.  If the scheduler mode is required to be ~
				    *             NUPEC-catch-up-mode, the GFI file format must be NUPEC ~
				    *             snapshot-with-restart-time."
				    */

static Object Qinput_one_shot_when_activated;  /* input-one-shot-when-activated */

static Object string_constant_20;  /* "When using a GFI file format of NUPEC snapshot for ~NF, the gfi-~
				    *             input-variables-update-mode attribute must be either \"input when ~
				    *             activated\" or \"input when activated, without interruption\"."
				    */

static Object Qyes;                /* yes */

static Object string_constant_21;  /* "When using a GFI file format of NUPEC snapshot for ~NF, the ~
				    *             ignore-input-base-time attribute must be set to no."
				    */

static Object list_constant_1;     /* # */

static Object Qgfi_input_ignore_data_server_qm;  /* gfi-input-ignore-data-server? */

/* PREPARE-GFI-INPUT-INTERFACE-TO-OPEN */
Object prepare_gfi_input_interface_to_open(gfi_input_interface)
    Object gfi_input_interface;
{
    Object code, update_mode_qm, file_format, temp, result_qm, gensymed_symbol;
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_1, first_1, last_1, next, queue_list;

    x_note_fn_call(217,90);
    code = M_CAR(M_CDR(Gfi_list_of_converters));
    if (FIXNUMP(code) && (IFIX(code) & (SI_Long)8L) != (SI_Long)0L ? 
	    TRUEP(M_CAR(M_CDR(Cache_gfi_semantics_graph))) : TRUEP(Nil)) {
	update_mode_qm = get_lookup_slot_value(gfi_input_interface,
		Qgfi_input_variables_update_mode);
	file_format = get_lookup_slot_value(gfi_input_interface,
		Qgfi_input_file_format);
	temp = ISVREF(gfi_input_interface,(SI_Long)8L);
	if ( ! !TRUEP(CAR(temp)))
	    temp = (SI_Long)2L <= IFIX(Warning_message_level) ? 
		    give_warning_1(3,FIX((SI_Long)2L),string_constant_17,
		    gfi_input_interface) : Nil;
	else if (EQ(file_format,Qnupec_snapshot_with_restart_time) &&  
		!EQ(ISVREF(Timing_parameters,(SI_Long)22L),Qnupec_catch_up)) {
	    Suppress_warning_message_header_qm = T;
	    if ((SI_Long)2L <= IFIX(Warning_message_level))
		give_warning_1(3,FIX((SI_Long)2L),string_constant_18,
			gfi_input_interface);
	    Suppress_warning_message_header_qm = Nil;
	    temp = Suppress_warning_message_header_qm;
	}
	else if (EQ(file_format,Qnupec_snapshot) && 
		EQ(ISVREF(Timing_parameters,(SI_Long)22L),Qnupec_catch_up)) {
	    Suppress_warning_message_header_qm = T;
	    if ((SI_Long)2L <= IFIX(Warning_message_level))
		give_warning_1(3,FIX((SI_Long)2L),string_constant_19,
			gfi_input_interface);
	    Suppress_warning_message_header_qm = Nil;
	    temp = Suppress_warning_message_header_qm;
	}
	else if ((EQ(file_format,Qnupec_snapshot) || EQ(file_format,
		Qnupec_snapshot_with_restart_time)) &&  !EQ(update_mode_qm,
		Qinput_one_shot_when_activated) &&  !EQ(update_mode_qm,
		Qinput_one_shot_when_activated_without_interruption)) {
	    Suppress_warning_message_header_qm = T;
	    if ((SI_Long)2L <= IFIX(Warning_message_level))
		give_warning_1(3,FIX((SI_Long)2L),string_constant_20,
			gfi_input_interface);
	    Suppress_warning_message_header_qm = Nil;
	    temp = Suppress_warning_message_header_qm;
	}
	else if ((EQ(file_format,Qnupec_snapshot) || EQ(file_format,
		Qnupec_snapshot_with_restart_time)) && 
		EQ(get_lookup_slot_value(gfi_input_interface,
		Qignore_gfi_input_base_time_qm),Qyes)) {
	    Suppress_warning_message_header_qm = T;
	    if ((SI_Long)2L <= IFIX(Warning_message_level))
		give_warning_1(3,FIX((SI_Long)2L),string_constant_21,
			gfi_input_interface);
	    Suppress_warning_message_header_qm = Nil;
	    temp = Suppress_warning_message_header_qm;
	}
	else {
	    result_qm = memq_function(update_mode_qm,list_constant_1);
	    set_non_savable_lookup_slot_value(gfi_input_interface,
		    Qgfi_input_ignore_data_server_qm,result_qm ? T : Nil);
	    close_gfi_input_interface(gfi_input_interface);
	    change_slot_value(3,gfi_input_interface,Qfile_status,
		    Qready_to_open);
	    if (get_lookup_slot_value_given_default(gfi_input_interface,
		    Qgfi_input_without_interruption_qm,Nil)) {
		if (Queue_of_active_uninterruptable_gfi_input_interface_objects) 
			    {
		    gensymed_symbol = gfi_input_interface;
		    new_cons = ISVREF(Available_gfi_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			svref_arg_1 = Available_gfi_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
			if ( !TRUEP(ISVREF(Available_gfi_conses_vector,
				IFIX(Current_thread_index)))) {
			    svref_arg_1 = Available_gfi_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(svref_arg_1,svref_arg_2) = Nil;
			}
			gensymed_symbol_1 = new_cons;
		    }
		    else
			gensymed_symbol_1 = Nil;
		    if ( !TRUEP(gensymed_symbol_1))
			gensymed_symbol_1 = replenish_gfi_cons_pool();
		    M_CAR(gensymed_symbol_1) = gensymed_symbol;
		    M_CDR(gensymed_symbol_1) = Nil;
		    inline_note_allocate_cons(gensymed_symbol_1,Qgfi);
		  next_loop:
		    first_1 = 
			    CAR(Queue_of_active_uninterruptable_gfi_input_interface_objects);
		    last_1 = 
			    CDR(Queue_of_active_uninterruptable_gfi_input_interface_objects);
		    temp = 
			    CDR(Queue_of_active_uninterruptable_gfi_input_interface_objects);
		    next = CDR(temp);
		    if ( !TRUEP(first_1)) {
			if (CAS_CAR(Queue_of_active_uninterruptable_gfi_input_interface_objects,
				first_1,gensymed_symbol_1)) {
			    CAS_CDR(Queue_of_active_uninterruptable_gfi_input_interface_objects,
				    last_1,gensymed_symbol_1);
			    goto end_1;
			}
		    }
		    else if (EQ(last_1,
			    CDR(Queue_of_active_uninterruptable_gfi_input_interface_objects))) 
				{
			if ( !TRUEP(next)) {
			    if (CAS_CDR(last_1,next,gensymed_symbol_1)) {
				CAS_CDR(Queue_of_active_uninterruptable_gfi_input_interface_objects,
					last_1,gensymed_symbol_1);
				goto end_1;
			    }
			}
			else
			    CAS_CDR(Queue_of_active_uninterruptable_gfi_input_interface_objects,
				    last_1,next);
		    }
		    goto next_loop;
		  end_loop:
		  end_1:;
		}
		else {
		    queue_list = gfi_cons_1(gfi_input_interface,Nil);
		    Queue_of_active_uninterruptable_gfi_input_interface_objects 
			    = gfi_cons_1(queue_list,queue_list);
		}
	    }
	    else if (Queue_of_active_gfi_input_interface_objects) {
		gensymed_symbol = gfi_input_interface;
		new_cons = ISVREF(Available_gfi_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    svref_arg_1 = Available_gfi_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_gfi_conses_vector,
			    IFIX(Current_thread_index)))) {
			svref_arg_1 = Available_gfi_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(svref_arg_1,svref_arg_2) = Nil;
		    }
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_gfi_cons_pool();
		M_CAR(gensymed_symbol_1) = gensymed_symbol;
		M_CDR(gensymed_symbol_1) = Nil;
		inline_note_allocate_cons(gensymed_symbol_1,Qgfi);
	      next_loop_1:
		first_1 = CAR(Queue_of_active_gfi_input_interface_objects);
		last_1 = CDR(Queue_of_active_gfi_input_interface_objects);
		temp = CDR(Queue_of_active_gfi_input_interface_objects);
		next = CDR(temp);
		if ( !TRUEP(first_1)) {
		    if (CAS_CAR(Queue_of_active_gfi_input_interface_objects,
			    first_1,gensymed_symbol_1)) {
			CAS_CDR(Queue_of_active_gfi_input_interface_objects,
				last_1,gensymed_symbol_1);
			goto end_2;
		    }
		}
		else if (EQ(last_1,
			CDR(Queue_of_active_gfi_input_interface_objects))) {
		    if ( !TRUEP(next)) {
			if (CAS_CDR(last_1,next,gensymed_symbol_1)) {
			    CAS_CDR(Queue_of_active_gfi_input_interface_objects,
				    last_1,gensymed_symbol_1);
			    goto end_2;
			}
		    }
		    else
			CAS_CDR(Queue_of_active_gfi_input_interface_objects,
				last_1,next);
		}
		goto next_loop_1;
	      end_loop_1:
	      end_2:;
	    }
	    else {
		queue_list = gfi_cons_1(gfi_input_interface,Nil);
		Queue_of_active_gfi_input_interface_objects = 
			gfi_cons_1(queue_list,queue_list);
	    }
	    temp = schedule_data_server_accept_data_calls();
	}
    }
    else
	temp = parse_gfi_schedule_tree();
    return VALUES_1(temp);
}

static Object Qgfi_input_pathname_string_of_stream_qm;  /* gfi-input-pathname-string-of-stream? */

static Object Qgfi_input_file_stream;  /* gfi-input-file-stream */

static Object Qgfi_input_file_buffer_position;  /* gfi-input-file-buffer-position */

static Object Qgfi_input_file_buffer_available_characters;  /* gfi-input-file-buffer-available-characters */

static Object Qgfi_input_file_buffer_offset;  /* gfi-input-file-buffer-offset */

static Object Qgfi_input_line;     /* gfi-input-line */

static Object Qgfi_queue_of_variables_that_need_values;  /* gfi-queue-of-variables-that-need-values */

static Object Qgfi_input_file_synchronized_qm;  /* gfi-input-file-synchronized? */

static Object Qgfi_input_g2_time_at_start;  /* gfi-input-g2-time-at-start */

static Object string_constant_22;  /* "Couldn't open input file ~S for ~NF." */

/* OPEN-GFI-INPUT-INTERFACE */
Object open_gfi_input_interface(gfi_input_frame)
    Object gfi_input_frame;
{
    Object code, pathname_qm, current_computation_frame;
    Object managed_float_or_number, gfi_input_g2_time_at_start_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(217,91);
    set_non_savable_lookup_slot_value(gfi_input_frame,Qgfi_inputting_qm,Nil);
    code = M_CAR(M_CDR(Gfi_list_of_converters));
    if (FIXNUMP(code) && (IFIX(code) & (SI_Long)8L) != (SI_Long)0L ? 
	    TRUEP(M_CAR(M_CDR(Cache_gfi_semantics_graph))) : TRUEP(Nil)) {
	pathname_qm = get_pathname_for_gfi_interface(gfi_input_frame,
		Qgfi_input_file_pathname);
	current_computation_frame = gfi_input_frame;
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		0);
	  if (pathname_qm) {
	      set_non_savable_lookup_slot_value(gfi_input_frame,
		      Qgfi_input_pathname_string_of_stream_qm,pathname_qm);
	      set_non_savable_lookup_slot_value(gfi_input_frame,
		      Qgfi_input_file_stream,
		      g2_stream_open_for_input(pathname_qm));
	      if (get_lookup_slot_value_given_default(gfi_input_frame,
		      Qgfi_input_file_stream,Nil)) {
		  set_non_savable_lookup_slot_value(gfi_input_frame,
			  Qgfi_input_file_buffer_position,
			  g2_stream_get_file_position(get_lookup_slot_value_given_default(gfi_input_frame,
			  Qgfi_input_file_stream,Nil)));
		  set_non_savable_lookup_slot_value(gfi_input_frame,
			  Qgfi_input_file_buffer_available_characters,
			  FIX((SI_Long)0L));
		  set_non_savable_lookup_slot_value(gfi_input_frame,
			  Qgfi_input_file_buffer_offset,FIX((SI_Long)0L));
	      }
	  }
	  if (pathname_qm && 
		  get_lookup_slot_value_given_default(gfi_input_frame,
		  Qgfi_input_file_stream,Nil)) {
	      set_non_savable_lookup_slot_value(gfi_input_frame,
		      Qgfi_inputting_qm,T);
	      set_non_savable_lookup_slot_value(gfi_input_frame,
		      Qgfi_input_line,
		      copy_constant_wide_string_given_length(array_constant,
		      FIX((SI_Long)0L)));
	      set_non_savable_lookup_slot_value(gfi_input_frame,
		      Qgfi_queue_of_variables_that_need_values,
		      gfi_cons_1(Nil,Nil));
	      set_non_savable_lookup_slot_value(gfi_input_frame,
		      Qgfi_input_file_synchronized_qm,Nil);
	      if (get_lookup_slot_value_given_default(gfi_input_frame,
		      Qgfi_input_g2_time_at_start,Nil)) {
		  managed_float_or_number = 
			  get_lookup_slot_value_given_default(gfi_input_frame,
			  Qgfi_input_g2_time_at_start,Nil);
		  if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_float_or_number) 
			  != (SI_Long)0L && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_float_or_number)) 
			  == (SI_Long)1L)
		      reclaim_managed_simple_float_array_of_length_1(managed_float_or_number);
		  else if (INLINE_LONG_VECTOR_P(managed_float_or_number) 
			  != (SI_Long)0L && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_float_or_number)) 
			  == (SI_Long)1L)
		      reclaim_managed_simple_long_array_of_length_1(managed_float_or_number);
		  gfi_input_g2_time_at_start_new_value = Nil;
		  set_non_savable_lookup_slot_value(gfi_input_frame,
			  Qgfi_input_g2_time_at_start,
			  gfi_input_g2_time_at_start_new_value);
	      }
	      set_non_savable_lookup_slot_value(gfi_input_frame,
		      Qgfi_input_g2_time_at_start,
		      copy_managed_float(Current_g2_time));
	      read_gfi_file_header(gfi_input_frame);
	      change_slot_value(3,gfi_input_frame,Qfile_status,Qopen);
	      result = VALUES_1(T);
	  }
	  else {
	      change_slot_value(3,gfi_input_frame,Qfile_status,
		      Qfailed_to_open);
	      if (pathname_qm) {
		  Suppress_warning_message_header_qm = T;
		  if ((SI_Long)2L <= IFIX(Warning_message_level))
		      give_warning_1(4,FIX((SI_Long)2L),string_constant_22,
			      pathname_qm,gfi_input_frame);
		  Suppress_warning_message_header_qm = Nil;
	      }
	      close_gfi_input_interface(gfi_input_frame);
	      result = VALUES_1(Nil);
	  }
	POP_SPECIAL();
	return result;
    }
    else
	return parse_gfi_schedule_tree();
}

/* SKIP-TO-AFTER-GFI-DELIMITTER-IN-STRING */
Object skip_to_after_gfi_delimitter_in_string(string_1,start_index,end_index)
    Object string_1, start_index, end_index;
{
    Object current_index, temp, current_index_new_value;
    Declare_special(1);

    x_note_fn_call(217,92);
    current_index = start_index;
    PUSH_SPECIAL_WITH_SYMBOL(Current_index,Qcurrent_index,current_index,0);
    next_loop:
      if ( !FIXNUM_LT(Current_index,end_index))
	  goto end_loop;
      if (UBYTE_16_ISAREF_1(string_1,IFIX(Current_index)) == 
	      IFIX(Gfi_delimitter)) {
	  temp = FIXNUM_ADD1(Current_index);
	  goto end_1;
      }
      current_index_new_value = FIXNUM_ADD1(Current_index);
      Current_index = current_index_new_value;
      goto next_loop;
    end_loop:
      temp = Nil;
      goto end_1;
      temp = Qnil;
    end_1:;
    POP_SPECIAL();
    return VALUES_1(temp);
}

static Object string_constant_23;  /* "The end of the file has been reached in the GFI input file ~S.  ~
				    *              The GFI Input Interface ~NF will not provide any ~A values."
				    */

static Object Qon_request_sample_and_hold;  /* on-request-sample-and-hold */

static Object string_constant_24;  /* "new" */

static Object string_constant_25;  /* "more" */

static Object string_constant_26;  /* "Can't read from ~S for the GFI Input Interface ~NF:  ~A." */

static Object Qgfi_input_line_length;  /* gfi-input-line-length */

static Object Qgfi_input_line_current_index;  /* gfi-input-line-current-index */

/* READ-ONE-GFI-INPUT-LINE */
Object read_one_gfi_input_line(gfi_input_frame)
    Object gfi_input_frame;
{
    Object line, length_1, comment_char_index_qm, temp, error_text;

    x_note_fn_call(217,93);
    line = Nil;
    length_1 = Nil;
    comment_char_index_qm = Nil;
  next_loop:
    line = gfi_read_line(gfi_input_frame);
    if ( !TRUEP(line)) {
	if (FIXNUM_EQ(Internal_status_of_most_recent_file_operation,
		End_of_file_reached_code)) {
	    Suppress_warning_message_header_qm = T;
	    if ((SI_Long)2L <= IFIX(Warning_message_level)) {
		temp = get_lookup_slot_value_given_default(gfi_input_frame,
			Qgfi_input_pathname_string_of_stream_qm,Nil);
		give_warning_1(5,FIX((SI_Long)2L),string_constant_23,temp,
			gfi_input_frame,
			EQ(get_lookup_slot_value(gfi_input_frame,
			Qgfi_input_variables_update_mode),
			Qon_request_sample_and_hold) ? string_constant_24 :
			 string_constant_25);
	    }
	    Suppress_warning_message_header_qm = Nil;
	}
	else {
	    error_text = most_recent_file_operation_status_as_text();
	    Suppress_warning_message_header_qm = T;
	    if ((SI_Long)2L <= IFIX(Warning_message_level))
		give_warning_1(5,FIX((SI_Long)2L),string_constant_26,
			get_lookup_slot_value_given_default(gfi_input_frame,
			Qgfi_input_pathname_string_of_stream_qm,Nil),
			gfi_input_frame,error_text);
	    Suppress_warning_message_header_qm = Nil;
	    reclaim_text_string(error_text);
	}
	close_gfi_input_interface(gfi_input_frame);
	return VALUES_1(Nil);
    }
    else {
	length_1 = text_string_length(line);
	if (IFIX(length_1) == (SI_Long)0L)
	    reclaim_text_string(line);
	else {
	    comment_char_index_qm = gfi_input_find_non_white_space(1,line);
	    if ( !TRUEP(comment_char_index_qm))
		reclaim_text_string(line);
	    else if (UBYTE_16_ISAREF_1(line,IFIX(comment_char_index_qm)) 
		    == (SI_Long)59L)
		reclaim_text_string(line);
	    else {
		reclaim_text_string(get_lookup_slot_value_given_default(gfi_input_frame,
			Qgfi_input_line,Nil));
		set_non_savable_lookup_slot_value(gfi_input_frame,
			Qgfi_input_line,line);
		set_non_savable_lookup_slot_value(gfi_input_frame,
			Qgfi_input_line_length,length_1);
		set_non_savable_lookup_slot_value(gfi_input_frame,
			Qgfi_input_line_current_index,FIX((SI_Long)0L));
		return VALUES_1(line);
	    }
	}
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qgfi_current_input_designation;  /* gfi-current-input-designation */

/* READ-GFI-DESIGNATION-FROM-STRING */
Object read_gfi_designation_from_string(frame,designation_text_string)
    Object frame, designation_text_string;
{
    Object parse_qm;

    x_note_fn_call(217,94);
    reclaim_slot_value(get_lookup_slot_value_given_default(frame,
	    Qgfi_current_input_designation,Nil));
    parse_qm = parse_constant_designation(designation_text_string,
	    FIX((SI_Long)0L));
    reclaim_text_string(designation_text_string);
    set_non_savable_lookup_slot_value(frame,Qgfi_current_input_designation,
	    parse_qm);
    return VALUES_1(parse_qm);
}

/* PARSE-DELIMITTER-THEN-DESIGNATION */
Object parse_delimitter_then_designation varargs_1(int, n)
{
    Object gfi_input_frame;
    Object do_not_parse_delimitter_qm, length_1, line, start_index, end_index;
    Object designation_text_string;
    Declare_varargs_nonrelocating;

    x_note_fn_call(217,95);
    INIT_ARGS_nonrelocating();
    gfi_input_frame = REQUIRED_ARG_nonrelocating();
    do_not_parse_delimitter_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    length_1 = get_lookup_slot_value_given_default(gfi_input_frame,
	    Qgfi_input_line_length,FIX((SI_Long)0L));
    if (FIXNUM_LT(get_lookup_slot_value_given_default(gfi_input_frame,
	    Qgfi_input_line_current_index,FIX((SI_Long)0L)),length_1)) {
	line = get_lookup_slot_value_given_default(gfi_input_frame,
		Qgfi_input_line,Nil);
	start_index = do_not_parse_delimitter_qm ? 
		get_lookup_slot_value_given_default(gfi_input_frame,
		Qgfi_input_line_current_index,FIX((SI_Long)0L)) : 
		skip_to_after_gfi_delimitter_in_string(line,
		get_lookup_slot_value_given_default(gfi_input_frame,
		Qgfi_input_line_current_index,FIX((SI_Long)0L)),length_1);
	end_index = Nil;
	if (start_index && FIXNUM_LT(start_index,length_1)) {
	    end_index = skip_to_after_gfi_delimitter_in_string(line,
		    start_index,length_1);
	    if ( !TRUEP(end_index))
		end_index = length_1;
	    else
		end_index = FIXNUM_SUB1(end_index);
	    designation_text_string = text_string_substring(line,
		    start_index,end_index);
	    set_non_savable_lookup_slot_value(gfi_input_frame,
		    Qgfi_input_line_current_index,end_index);
	    return read_gfi_designation_from_string(gfi_input_frame,
		    designation_text_string);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qgfi_input_spreadsheet_designations;  /* gfi-input-spreadsheet-designations */

/* READ-LIST-OF-GFI-DESIGNATIONS */
Object read_list_of_gfi_designations(gfi_input_frame)
    Object gfi_input_frame;
{
    Object list_of_designations, tail, designation, error_p, cdr_new_value;
    Object result;

    x_note_fn_call(217,96);
    list_of_designations = slot_value_cons_1(Nil,Nil);
    tail = list_of_designations;
    designation = Nil;
    error_p = Nil;
  next_loop:
    result = parse_delimitter_then_designation(1,gfi_input_frame);
    MVS_2(result,designation,error_p);
    set_non_savable_lookup_slot_value(gfi_input_frame,
	    Qgfi_current_input_designation,Nil);
    if (designation &&  !TRUEP(error_p)) {
	if (CAR(tail)) {
	    cdr_new_value = slot_value_cons_1(designation,Nil);
	    M_CDR(tail) = cdr_new_value;
	    tail = CDR(tail);
	}
	else
	    M_CAR(tail) = designation;
    }
    else
	goto end_loop;
    goto next_loop;
  end_loop:
    if (error_p) {
	reclaim_slot_value(list_of_designations);
	return VALUES_2(Nil,T);
    }
    else if (CAR(list_of_designations)) {
	reclaim_slot_value(get_lookup_slot_value_given_default(gfi_input_frame,
		Qgfi_input_spreadsheet_designations,Nil));
	set_non_savable_lookup_slot_value(gfi_input_frame,
		Qgfi_input_spreadsheet_designations,list_of_designations);
	return VALUES_1(list_of_designations);
    }
    else {
	reclaim_slot_value_cons_1(list_of_designations);
	return VALUES_1(Nil);
    }
    return VALUES_1(Qnil);
}

static Object Qgfi_input_base_time;  /* gfi-input-base-time */

/* READ-AND-ENCODE-GFI-INPUT-BASE-TIME */
Object read_and_encode_gfi_input_base_time(gfi_input_frame)
    Object gfi_input_frame;
{
    Object temp, temp_1, seconds_qm, minutes, hours, day, month, year;
    Object end_index_of_time_stamp, second_fraction_float_qm;
    Object subsecond_time_qm, seconds_fixnum_qm, encoded_time, base_time_qm;
    char temp_3;
    double temp_2, arg, arg_1, store_managed_number_arg;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(217,97);
    temp = get_lookup_slot_value_given_default(gfi_input_frame,
	    Qgfi_input_line,Nil);
    temp_1 = get_lookup_slot_value_given_default(gfi_input_frame,
	    Qgfi_input_line_current_index,FIX((SI_Long)0L));
    result = read_time_stamp_from_string(temp,temp_1,
	    get_lookup_slot_value_given_default(gfi_input_frame,
	    Qgfi_input_line_length,FIX((SI_Long)0L)));
    MVS_7(result,seconds_qm,minutes,hours,day,month,year,
	    end_index_of_time_stamp);
    if (seconds_qm) {
	set_non_savable_lookup_slot_value(gfi_input_frame,
		Qgfi_input_line_current_index,end_index_of_time_stamp);
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(seconds_qm) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(seconds_qm)) == 
			(SI_Long)1L) {
		temp_2 = DFLOAT_ISAREF_1(seconds_qm,(SI_Long)0L);
		second_fraction_float_qm = DOUBLE_TO_DOUBLE_FLOAT(temp_2 - 
			inline_ffloor_1(DFLOAT_ISAREF_1(seconds_qm,
			(SI_Long)0L)));
	    }
	    else
		second_fraction_float_qm = Nil;
	    if (second_fraction_float_qm) {
		arg = DOUBLE_FLOAT_TO_DOUBLE(second_fraction_float_qm);
		arg_1 = 0.0;
		temp_3 =  !(arg == arg_1 &&  
			!inline_nanp_for_comparison(arg) &&  
			!inline_nanp_for_comparison(arg_1));
	    }
	    else
		temp_3 = TRUEP(Nil);
	    subsecond_time_qm = temp_3 ? second_fraction_float_qm : Nil;
	    seconds_fixnum_qm = seconds_qm ? 
		    (INLINE_DOUBLE_FLOAT_VECTOR_P(seconds_qm) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(seconds_qm)) == 
		    (SI_Long)1L ? 
		    LONG_TO_FIXNUM(inline_floor_1(DFLOAT_ISAREF_1(seconds_qm,
		    (SI_Long)0L))) : seconds_qm) : Nil;
	    encoded_time = 
		    gensym_encode_unix_time_as_managed_float(seconds_fixnum_qm,
		    minutes,hours,day,month,year);
	    base_time_qm = 
		    get_lookup_slot_value_given_default(gfi_input_frame,
		    Qgfi_input_base_time,Nil);
	    if (subsecond_time_qm) {
		temp_2 = DOUBLE_FLOAT_TO_DOUBLE(subsecond_time_qm);
		store_managed_number_arg = temp_2 + 
			DFLOAT_ISAREF_1(encoded_time,(SI_Long)0L);
		encoded_time = store_managed_number_function(encoded_time,
			DOUBLE_TO_DOUBLE_FLOAT(store_managed_number_arg));
	    }
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(base_time_qm) != (SI_Long)0L 
		    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(base_time_qm)) == 
		    (SI_Long)1L)
		reclaim_managed_simple_float_array_of_length_1(base_time_qm);
	    set_non_savable_lookup_slot_value(gfi_input_frame,
		    Qgfi_input_base_time,encoded_time);
	}
	POP_LOCAL_ALLOCATION(0,0);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(seconds_qm) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(seconds_qm)) == (SI_Long)1L)
	    reclaim_managed_simple_float_array_of_length_1(seconds_qm);
	else if (INLINE_LONG_VECTOR_P(seconds_qm) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(seconds_qm)) == (SI_Long)1L)
	    reclaim_managed_simple_long_array_of_length_1(seconds_qm);
	seconds_qm = Nil;
	return VALUES_1(T);
    }
    else
	return VALUES_1(Nil);
}

/* GFI-INPUT-FIND-NON-WHITE-SPACE */
Object gfi_input_find_non_white_space varargs_1(int, n)
{
    Object string_1;
    Object start, end_1, i, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(217,98);
    INIT_ARGS_nonrelocating();
    string_1 = REQUIRED_ARG_nonrelocating();
    start = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     FIX((SI_Long)0L);
    end_1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    i = start;
    if (end_1) {
	temp = text_string_length(string_1);
	end_1 = FIXNUM_MIN(temp,end_1);
    }
    else
	end_1 = text_string_length(string_1);
  next_loop:
    if (FIXNUM_GE(i,end_1) ||  
	    !TRUEP(wide_character_member(FIX(UBYTE_16_ISAREF_1(string_1,
	    IFIX(i))),Gfi_input_white_space)))
	goto end_loop;
    i = FIXNUM_ADD1(i);
    goto next_loop;
  end_loop:
    if (FIXNUM_GE(i,end_1))
	return VALUES_1(Nil);
    else
	return VALUES_1(i);
    return VALUES_1(Qnil);
}

/* MATCH-SHORTER-SUBSTRING-P */
Object match_shorter_substring_p(string_1,start_index_1,end_index_1,
	    shorter_string_2,start_index_2,end_index_2)
    Object string_1, start_index_1, end_index_1, shorter_string_2;
    Object start_index_2, end_index_2;
{
    Object delta_1, delta_2;

    x_note_fn_call(217,99);
    delta_1 = FIXNUM_MINUS(end_index_1,start_index_1);
    delta_2 = FIXNUM_MINUS(end_index_2,start_index_2);
    if (FIXNUM_GE(delta_1,delta_2))
	return substring_equal(string_1,start_index_1,
		FIXNUM_ADD(start_index_1,delta_2),shorter_string_2,
		start_index_2,end_index_2);
    else
	return VALUES_1(Nil);
}

static Object string_constant_27;  /* "event log" */

static Object string_constant_28;  /* "spreadsheet" */

static Object string_constant_29;  /* "NUPEC snapshot" */

static Object string_constant_30;  /* "unknown file format" */

static Object string_constant_31;  /* "The base time was not found in the ~S GFI file ~S ~
				    *              for ~NF, where relative time-stamping was specified."
				    */

static Object string_constant_32;  /* "Can't parse the first line of the ~S GFI file ~S of the GFI ~
				    *              Input Interface ~NF."
				    */

static Object string_constant_33;  /* "Error in reading the time stamp in the ~S GFI ~
				    * ?     file ~S of the GFI Input Interface ~NF.  Note that the first ~
				    * ?     line of this file must have an explicit time stamp."
				    */

static Object string_constant_34;  /* "Error in parsing the header of the spreadsheet format GFI ~
				    * ?     file ~S for the GFI Input Interface ~NF.  Invalid variable or parameter ~
				    *              reference."
				    */

static Object string_constant_35;  /* "Error in parsing the header of the spreadsheet format GFI ~
				    * ?     file ~S for the GFI Input Interface ~NF.  Variable or parameter ~
				    *              reference not found."
				    */

static Object string_constant_36;  /* "Error in parsing the base time of the spreadsheet format GFI ~
				    * ?     file ~S for the GFI Input Interface ~NF."
				    */

static Object string_constant_37;  /* "The spreadsheet format GFI file ~S for the GFI Input ~
				    *              Interface ~NF should start with ~S."
				    */

/* READ-GFI-FILE-HEADER */
Object read_gfi_file_header(gfi_input_frame)
    Object gfi_input_frame;
{
    Object temp, line, gfi_current_index, file_format, file_format_string;
    Object temp_1, designation_list_qm, error_p_qm;
    Object result;

    x_note_fn_call(217,100);
    if (read_one_gfi_input_line(gfi_input_frame)) {
	temp = get_lookup_slot_value(gfi_input_frame,Qgfi_input_file_format);
	if (EQ(temp,Qevent_log) || EQ(temp,Qnupec_snapshot) || EQ(temp,
		Qnupec_snapshot_with_restart_time)) {
	    if (read_and_encode_gfi_input_base_time(gfi_input_frame)) {
		if (EQ(get_lookup_slot_value(gfi_input_frame,
			Qgfi_input_time_stamp_format),Qrelative) || 
			EQ(get_lookup_slot_value(gfi_input_frame,
			Qgfi_input_file_format),Qnupec_snapshot) || 
			EQ(get_lookup_slot_value(gfi_input_frame,
			Qgfi_input_file_format),
			Qnupec_snapshot_with_restart_time)) {
		    line = 
			    get_lookup_slot_value_given_default(gfi_input_frame,
			    Qgfi_input_line,Nil);
		    temp = 
			    get_lookup_slot_value_given_default(gfi_input_frame,
			    Qgfi_input_line_current_index,FIX((SI_Long)0L));
		    gfi_current_index = 
			    skip_to_after_gfi_delimitter_in_string(line,
			    temp,
			    get_lookup_slot_value_given_default(gfi_input_frame,
			    Qgfi_input_line_length,FIX((SI_Long)0L)));
		    if (gfi_current_index && FIXNUM_LT(gfi_current_index,
			    get_lookup_slot_value_given_default(gfi_input_frame,
			    Qgfi_input_line_length,FIX((SI_Long)0L))) && 
			    FIXNUM_GT(FIXNUM_MINUS(get_lookup_slot_value_given_default(gfi_input_frame,
			    Qgfi_input_line_length,FIX((SI_Long)0L)),
			    gfi_current_index),
			    Gfi_designation_for_base_time_string_length)) {
			if (substring_equal(Gfi_designation_for_base_time,
				FIX((SI_Long)0L),
				Gfi_designation_for_base_time_string_length,
				line,gfi_current_index,
				FIXNUM_ADD(gfi_current_index,
				Gfi_designation_for_base_time_string_length)))
			    return read_one_gfi_input_line(gfi_input_frame);
			else {
			    file_format = 
				    get_lookup_slot_value(gfi_input_frame,
				    Qgfi_input_file_format);
			    if (EQ(file_format,Qevent_log))
				file_format_string = string_constant_27;
			    else if (EQ(file_format,Qspreadsheet))
				file_format_string = string_constant_28;
			    else if (EQ(file_format,Qnupec_snapshot))
				file_format_string = string_constant_29;
			    else
				file_format_string = string_constant_30;
			    Suppress_warning_message_header_qm = T;
			    if ((SI_Long)2L <= IFIX(Warning_message_level))
				give_warning_1(5,FIX((SI_Long)2L),
					string_constant_31,
					file_format_string,
					get_lookup_slot_value_given_default(gfi_input_frame,
					Qgfi_input_pathname_string_of_stream_qm,
					Nil),gfi_input_frame);
			    Suppress_warning_message_header_qm = Nil;
			    close_gfi_input_interface(gfi_input_frame);
			    return VALUES_1(Nil);
			}
		    }
		    else {
			file_format = 
				get_lookup_slot_value(gfi_input_frame,
				Qgfi_input_file_format);
			if (EQ(file_format,Qevent_log))
			    file_format_string = string_constant_27;
			else if (EQ(file_format,Qspreadsheet))
			    file_format_string = string_constant_28;
			else if (EQ(file_format,Qnupec_snapshot))
			    file_format_string = string_constant_29;
			else
			    file_format_string = string_constant_30;
			Suppress_warning_message_header_qm = T;
			if ((SI_Long)2L <= IFIX(Warning_message_level))
			    give_warning_1(5,FIX((SI_Long)2L),
				    string_constant_32,file_format_string,
				    get_lookup_slot_value_given_default(gfi_input_frame,
				    Qgfi_input_pathname_string_of_stream_qm,
				    Nil),gfi_input_frame);
			Suppress_warning_message_header_qm = Nil;
			close_gfi_input_interface(gfi_input_frame);
			return VALUES_1(Nil);
		    }
		}
		else
		    return set_non_savable_lookup_slot_value(gfi_input_frame,
			    Qgfi_input_line_current_index,FIX((SI_Long)0L));
	    }
	    else {
		file_format = get_lookup_slot_value(gfi_input_frame,
			Qgfi_input_file_format);
		if (EQ(file_format,Qevent_log))
		    file_format_string = string_constant_27;
		else if (EQ(file_format,Qspreadsheet))
		    file_format_string = string_constant_28;
		else if (EQ(file_format,Qnupec_snapshot))
		    file_format_string = string_constant_29;
		else
		    file_format_string = string_constant_30;
		Suppress_warning_message_header_qm = T;
		if ((SI_Long)2L <= IFIX(Warning_message_level))
		    give_warning_1(5,FIX((SI_Long)2L),string_constant_33,
			    file_format_string,
			    get_lookup_slot_value_given_default(gfi_input_frame,
			    Qgfi_input_pathname_string_of_stream_qm,Nil),
			    gfi_input_frame);
		Suppress_warning_message_header_qm = Nil;
		close_gfi_input_interface(gfi_input_frame);
		return VALUES_1(Nil);
	    }
	}
	else if (EQ(temp,Qspreadsheet)) {
	    if (EQ(get_lookup_slot_value(gfi_input_frame,
		    Qgfi_input_time_stamp_format),Qrelative)) {
		temp = get_lookup_slot_value_given_default(gfi_input_frame,
			Qgfi_input_line,Nil);
		if (match_shorter_substring_p(temp,FIX((SI_Long)0L),
			get_lookup_slot_value_given_default(gfi_input_frame,
			Qgfi_input_line_length,FIX((SI_Long)0L)),
			Gfi_title_for_base_time,FIX((SI_Long)0L),
			Gfi_title_for_base_time_string_length)) {
		    set_non_savable_lookup_slot_value(gfi_input_frame,
			    Qgfi_input_line_current_index,
			    Gfi_title_for_base_time_string_length);
		    temp = 
			    get_lookup_slot_value_given_default(gfi_input_frame,
			    Qgfi_input_line,Nil);
		    temp_1 = 
			    get_lookup_slot_value_given_default(gfi_input_frame,
			    Qgfi_input_line_current_index,FIX((SI_Long)0L));
		    set_non_savable_lookup_slot_value(gfi_input_frame,
			    Qgfi_input_line_current_index,
			    skip_spaces_in_string(temp,temp_1,
			    get_lookup_slot_value_given_default(gfi_input_frame,
			    Qgfi_input_line_length,FIX((SI_Long)0L))));
		    if (read_and_encode_gfi_input_base_time(gfi_input_frame)) {
			result = read_list_of_gfi_designations(gfi_input_frame);
			MVS_2(result,designation_list_qm,error_p_qm);
			if (designation_list_qm)
			    return read_one_gfi_input_line(gfi_input_frame);
			else if (error_p_qm) {
			    file_format = 
				    get_lookup_slot_value(gfi_input_frame,
				    Qgfi_input_file_format);
			    if (EQ(file_format,Qevent_log))
				file_format_string = string_constant_27;
			    else if (EQ(file_format,Qspreadsheet))
				file_format_string = string_constant_28;
			    else if (EQ(file_format,Qnupec_snapshot))
				file_format_string = string_constant_29;
			    else
				file_format_string = string_constant_30;
			    Suppress_warning_message_header_qm = T;
			    if ((SI_Long)2L <= IFIX(Warning_message_level))
				give_warning_1(4,FIX((SI_Long)2L),
					string_constant_34,
					get_lookup_slot_value_given_default(gfi_input_frame,
					Qgfi_input_pathname_string_of_stream_qm,
					Nil),gfi_input_frame);
			    Suppress_warning_message_header_qm = Nil;
			    close_gfi_input_interface(gfi_input_frame);
			    return VALUES_1(Nil);
			}
			else {
			    file_format = 
				    get_lookup_slot_value(gfi_input_frame,
				    Qgfi_input_file_format);
			    if (EQ(file_format,Qevent_log))
				file_format_string = string_constant_27;
			    else if (EQ(file_format,Qspreadsheet))
				file_format_string = string_constant_28;
			    else if (EQ(file_format,Qnupec_snapshot))
				file_format_string = string_constant_29;
			    else
				file_format_string = string_constant_30;
			    Suppress_warning_message_header_qm = T;
			    if ((SI_Long)2L <= IFIX(Warning_message_level))
				give_warning_1(4,FIX((SI_Long)2L),
					string_constant_35,
					get_lookup_slot_value_given_default(gfi_input_frame,
					Qgfi_input_pathname_string_of_stream_qm,
					Nil),gfi_input_frame);
			    Suppress_warning_message_header_qm = Nil;
			    close_gfi_input_interface(gfi_input_frame);
			    return VALUES_1(Nil);
			}
		    }
		    else {
			file_format = 
				get_lookup_slot_value(gfi_input_frame,
				Qgfi_input_file_format);
			if (EQ(file_format,Qevent_log))
			    file_format_string = string_constant_27;
			else if (EQ(file_format,Qspreadsheet))
			    file_format_string = string_constant_28;
			else if (EQ(file_format,Qnupec_snapshot))
			    file_format_string = string_constant_29;
			else
			    file_format_string = string_constant_30;
			Suppress_warning_message_header_qm = T;
			if ((SI_Long)2L <= IFIX(Warning_message_level))
			    give_warning_1(4,FIX((SI_Long)2L),
				    string_constant_36,
				    get_lookup_slot_value_given_default(gfi_input_frame,
				    Qgfi_input_pathname_string_of_stream_qm,
				    Nil),gfi_input_frame);
			Suppress_warning_message_header_qm = Nil;
			close_gfi_input_interface(gfi_input_frame);
			return VALUES_1(Nil);
		    }
		}
		else {
		    file_format = get_lookup_slot_value(gfi_input_frame,
			    Qgfi_input_file_format);
		    if (EQ(file_format,Qevent_log))
			file_format_string = string_constant_27;
		    else if (EQ(file_format,Qspreadsheet))
			file_format_string = string_constant_28;
		    else if (EQ(file_format,Qnupec_snapshot))
			file_format_string = string_constant_29;
		    else
			file_format_string = string_constant_30;
		    Suppress_warning_message_header_qm = T;
		    if ((SI_Long)2L <= IFIX(Warning_message_level))
			give_warning_1(5,FIX((SI_Long)2L),
				string_constant_37,
				get_lookup_slot_value_given_default(gfi_input_frame,
				Qgfi_input_pathname_string_of_stream_qm,
				Nil),gfi_input_frame,Gfi_title_for_base_time);
		    Suppress_warning_message_header_qm = Nil;
		    close_gfi_input_interface(gfi_input_frame);
		    return VALUES_1(Nil);
		}
	    }
	    else {
		temp = get_lookup_slot_value_given_default(gfi_input_frame,
			Qgfi_input_line,Nil);
		temp_1 = 
			get_lookup_slot_value_given_default(gfi_input_frame,
			Qgfi_input_line_current_index,FIX((SI_Long)0L));
		set_non_savable_lookup_slot_value(gfi_input_frame,
			Qgfi_input_line_current_index,
			skip_spaces_in_string(temp,temp_1,
			get_lookup_slot_value_given_default(gfi_input_frame,
			Qgfi_input_line_length,FIX((SI_Long)0L))));
		result = read_list_of_gfi_designations(gfi_input_frame);
		MVS_2(result,designation_list_qm,error_p_qm);
		if (designation_list_qm) {
		    if (read_one_gfi_input_line(gfi_input_frame)) {
			if (read_and_encode_gfi_input_base_time(gfi_input_frame)) 
				    {
			    set_non_savable_lookup_slot_value(gfi_input_frame,
				    Qgfi_input_line_current_index,
				    FIX((SI_Long)0L));
			    return VALUES_1(T);
			}
			else {
			    file_format = 
				    get_lookup_slot_value(gfi_input_frame,
				    Qgfi_input_file_format);
			    if (EQ(file_format,Qevent_log))
				file_format_string = string_constant_27;
			    else if (EQ(file_format,Qspreadsheet))
				file_format_string = string_constant_28;
			    else if (EQ(file_format,Qnupec_snapshot))
				file_format_string = string_constant_29;
			    else
				file_format_string = string_constant_30;
			    Suppress_warning_message_header_qm = T;
			    if ((SI_Long)2L <= IFIX(Warning_message_level))
				give_warning_1(4,FIX((SI_Long)2L),
					string_constant_36,
					get_lookup_slot_value_given_default(gfi_input_frame,
					Qgfi_input_pathname_string_of_stream_qm,
					Nil),gfi_input_frame);
			    Suppress_warning_message_header_qm = Nil;
			    close_gfi_input_interface(gfi_input_frame);
			    return VALUES_1(Nil);
			}
		    }
		    else
			return VALUES_1(Nil);
		}
		else if (error_p_qm) {
		    file_format = get_lookup_slot_value(gfi_input_frame,
			    Qgfi_input_file_format);
		    if (EQ(file_format,Qevent_log))
			file_format_string = string_constant_27;
		    else if (EQ(file_format,Qspreadsheet))
			file_format_string = string_constant_28;
		    else if (EQ(file_format,Qnupec_snapshot))
			file_format_string = string_constant_29;
		    else
			file_format_string = string_constant_30;
		    Suppress_warning_message_header_qm = T;
		    if ((SI_Long)2L <= IFIX(Warning_message_level))
			give_warning_1(4,FIX((SI_Long)2L),
				string_constant_34,
				get_lookup_slot_value_given_default(gfi_input_frame,
				Qgfi_input_pathname_string_of_stream_qm,
				Nil),gfi_input_frame);
		    Suppress_warning_message_header_qm = Nil;
		    close_gfi_input_interface(gfi_input_frame);
		    return VALUES_1(Nil);
		}
		else {
		    file_format = get_lookup_slot_value(gfi_input_frame,
			    Qgfi_input_file_format);
		    if (EQ(file_format,Qevent_log))
			file_format_string = string_constant_27;
		    else if (EQ(file_format,Qspreadsheet))
			file_format_string = string_constant_28;
		    else if (EQ(file_format,Qnupec_snapshot))
			file_format_string = string_constant_29;
		    else
			file_format_string = string_constant_30;
		    Suppress_warning_message_header_qm = T;
		    if ((SI_Long)2L <= IFIX(Warning_message_level))
			give_warning_1(4,FIX((SI_Long)2L),
				string_constant_35,
				get_lookup_slot_value_given_default(gfi_input_frame,
				Qgfi_input_pathname_string_of_stream_qm,
				Nil),gfi_input_frame);
		    Suppress_warning_message_header_qm = Nil;
		    close_gfi_input_interface(gfi_input_frame);
		    return VALUES_1(Nil);
		}
	    }
	}
	else
	    return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* READ-TEXT-STRING-WITH-OR-WITHOUT-QUOTES-FROM-STRING */
Object read_text_string_with_or_without_quotes_from_string(string_1,
	    start_index,end_index)
    Object string_1, start_index, end_index;
{
    Object managed_string, text_string, current_index;
    Object store_managed_number_or_value_arg;
    Declare_special(1);
    Object result;

    x_note_fn_call(217,101);
    if (UBYTE_16_ISAREF_1(string_1,IFIX(start_index)) == (SI_Long)34L)
	return read_text_string_from_string(string_1,start_index,end_index);
    else {
	managed_string = Nil;
	result = read_text_string_ending_in_a_delimitter_from_string(string_1,
		start_index,end_index,Gfi_delimitter);
	MVS_2(result,text_string,current_index);
	PUSH_SPECIAL_WITH_SYMBOL(Current_index,Qcurrent_index,current_index,0);
	  store_managed_number_or_value_arg = text_string;
	  managed_string = 
		  store_managed_number_or_value_function(managed_string,
		  store_managed_number_or_value_arg);
	  reclaim_text_string(text_string);
	  result = VALUES_3(managed_string,Current_index,Nil);
	POP_SPECIAL();
	return result;
    }
}

static Object string_constant_38;  /* "The GFI Input Interface ~NF has received a value for ~ND ~
				    * ?    but could not find an appropriate variable to store the value."
				    */

static Object Qgfi_data_service;   /* gfi-data-service */

static Object Qgfi_data_server;    /* gfi-data-server */

static Object Qgfi_input_interface_object;  /* gfi-input-interface-object */

static Object Qgfi_input_line_g2_time;  /* gfi-input-line-g2-time */

static Object Qlong;               /* long */

static Object Qtruth_value;        /* truth-value */

static Object Qon_request;         /* on-request */

static Object Qgfi_last_value;     /* gfi-last-value */

static Object Qgfi_time_of_last_value_update;  /* gfi-time-of-last-value-update */

static Object string_constant_39;  /* "The GFI Input Interface ~NF obtained a line containing an illegal ~
				    * ??? string or symbol for the value of ~ND (~A~A).  The input interface ~
				    * ??? will be shut down, since the input file is probably corrupted."
				    */

static Object string_constant_40;  /* "The GFI Input Interface ~NF could not parse the line ~
				    *                           ~S, starting at character ~A, ~ND (~A~A).  There is ~
				    *                           a data type mismatch or an illegal string or symbol."
				    */

static Object array_constant_5;    /* # */

static Object Qrecord_block_for_tformat;  /* record-block-for-tformat */

static Object string_constant_41;  /* "The GFI input interface object ~NF could not find a variable" */

static Object array_constant_6;    /* # */

static Object string_constant_42;  /* " (which has GFI data service and has ~NF as its GFI ~
				    * ??input interface object)"
				    */

static Object string_constant_43;  /* " corresponding to \"~ND\", as specified in the GFI input file ~S." */

/* PUT-GFI-VALUE-OF-DESIGNATION-INTO-APPROPRIATE-PLACE */
Object put_gfi_value_of_designation_into_appropriate_place(designation,
	    gfi_input_frame,no_data_service_required_qm)
    Object designation, gfi_input_frame, no_data_service_required_qm;
{
    Object current_computation_frame, gensymed_symbol, variable_or_parameter;
    Object sub_class_bit_vector, gfi_interface_object_designation, temp_1;
    Object temp_2, end_index_qm, source_or_map, server_qm, string_1;
    Object current_index, end_index, collection_time, illegal_string_p;
    Object data_type, symbol_qm, symbol_end_index, text, text_end_index;
    Object managed_value, gfi_last_value_new_value, managed_float;
    Object current_computation_instance, legal_text_string;
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    Declare_special(7);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(217,102);
    current_computation_frame = gfi_input_frame;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    0);
      gensymed_symbol = evaluate_designation(designation,Nil);
      if ( !TRUEP(gensymed_symbol))
	  variable_or_parameter = Nil;
      else if (SIMPLE_VECTOR_P(gensymed_symbol) && 
	      EQ(ISVREF(gensymed_symbol,(SI_Long)0L),
	      Qg2_defstruct_structure_name_temporary_constant_g2_struct)) {
	  reclaim_temporary_constant_1(gensymed_symbol);
	  variable_or_parameter = Nil;
      }
      else {
	  sub_class_bit_vector = ISVREF(ISVREF(gensymed_symbol,
		  (SI_Long)1L),(SI_Long)19L);
	  superior_class_bit_number = 
		  IFIX(ISVREF(Variable_or_parameter_class_description,
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
	  if (temp ? (SI_Long)0L != (IFIX(ISVREF(gensymed_symbol,
		  (SI_Long)5L)) & (SI_Long)1L) : TRUEP(Nil))
	      variable_or_parameter = gensymed_symbol;
	  else
	      variable_or_parameter = Nil;
      }
    POP_SPECIAL();
    gfi_interface_object_designation = Nil;
    if ( !TRUEP(variable_or_parameter)) {
	temp_1 = get_lookup_slot_value_given_default(gfi_input_frame,
		Qgfi_input_line,Nil);
	temp_2 = get_lookup_slot_value_given_default(gfi_input_frame,
		Qgfi_input_line_current_index,FIX((SI_Long)0L));
	end_index_qm = skip_to_after_gfi_delimitter_in_string(temp_1,
		temp_2,get_lookup_slot_value_given_default(gfi_input_frame,
		Qgfi_input_line_length,FIX((SI_Long)0L)));
	Suppress_warning_message_header_qm = T;
	if ((SI_Long)2L <= IFIX(Warning_message_level))
	    give_warning_1(4,FIX((SI_Long)2L),string_constant_38,
		    gfi_input_frame,designation);
	Suppress_warning_message_header_qm = Nil;
	if (end_index_qm)
	    set_non_savable_lookup_slot_value(gfi_input_frame,
		    Qgfi_input_line_current_index,end_index_qm);
	else
	    set_non_savable_lookup_slot_value(gfi_input_frame,
		    Qgfi_input_line_current_index,
		    get_lookup_slot_value_given_default(gfi_input_frame,
		    Qgfi_input_line_length,FIX((SI_Long)0L)));
	return VALUES_1(Nil);
    }
    else {
	sub_class_bit_vector = ISVREF(ISVREF(variable_or_parameter,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Variable_or_parameter_class_description,
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
	if (temp) {
	    temp = TRUEP(no_data_service_required_qm);
	    if (temp);
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(variable_or_parameter,
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
		    temp = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    gensymed_symbol = 
			    lookup_global_or_kb_specific_property_value(Qgfi_data_service,
			    Class_description_gkbprop);
		    if (gensymed_symbol) {
			sub_class_bit_vector = 
				ISVREF(ISVREF(variable_or_parameter,
				(SI_Long)1L),(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol_1 = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_2 = (SI_Long)1L;
			    gensymed_symbol_3 = superior_class_bit_number 
				    & (SI_Long)7L;
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
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    source_or_map = ISVREF(variable_or_parameter,(SI_Long)31L);
		    server_qm = ATOM(source_or_map) ? 
			    lookup_kb_specific_property_value(source_or_map,
			    Data_server_or_alias_qm_kbprop) : Nil;
		    temp_2 = server_qm ? server_qm : 
			    warn_of_undefined_data_server(variable_or_parameter,
			    source_or_map);
		    temp = EQ(temp_2,
			    lookup_kb_specific_property_value(Qgfi_data_server,
			    Data_server_kbprop));
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    gfi_interface_object_designation = 
			    get_lookup_slot_value(variable_or_parameter,
			    Qgfi_input_interface_object);
		    temp = TRUEP(gfi_interface_object_designation);
		}
		else
		    temp = TRUEP(Nil);
		temp = temp ? 
			TRUEP(designation_denotes_item_p(gfi_interface_object_designation,
			gfi_input_frame)) : TRUEP(Nil);
	    }
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    string_1 = get_lookup_slot_value_given_default(gfi_input_frame,
		    Qgfi_input_line,Nil);
	    current_index = 
		    get_lookup_slot_value_given_default(gfi_input_frame,
		    Qgfi_input_line_current_index,FIX((SI_Long)0L));
	    end_index = 
		    get_lookup_slot_value_given_default(gfi_input_frame,
		    Qgfi_input_line_length,FIX((SI_Long)0L));
	    collection_time = 
		    get_lookup_slot_value_given_default(gfi_input_frame,
		    Qgfi_input_line_g2_time,Nil);
	    illegal_string_p = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_index,Qcurrent_index,current_index,
		    2);
	      data_type = 
		      type_specification_of_variable_or_parameter_value(variable_or_parameter);
	      if (EQ(data_type,Qnumber) || EQ(data_type,Qinteger) || 
		      EQ(data_type,Qfloat) || EQ(data_type,Qlong) || 
		      lookup_global_or_kb_specific_property_value(data_type,
		      Numeric_data_type_gkbprop))
		  result = read_number_from_string(string_1,Current_index,
			  end_index);
	      else if (EQ(data_type,Qtruth_value))
		  result = read_truth_value_from_string(string_1,
			  Current_index,end_index);
	      else if (EQ(data_type,Qsymbol)) {
		  result = read_symbol_from_text_string(2,string_1,
			  Current_index);
		  MVS_2(result,symbol_qm,symbol_end_index);
		  if ( !TRUEP(symbol_qm))
		      result = VALUES_2(Nil,symbol_end_index);
		  else
		      result = VALUES_2(symbol_qm,symbol_end_index);
	      }
	      else if (EQ(data_type,Qtext)) {
		  result = read_text_string_with_or_without_quotes_from_string(string_1,
			  Current_index,end_index);
		  MVS_2(result,text,text_end_index);
		  result = VALUES_2(text,text_end_index);
	      }
	      else
		  result = VALUES_2(Nil,Current_index);
	      MVS_2(result,managed_value,end_index);
	      set_non_savable_lookup_slot_value(gfi_input_frame,
		      Qgfi_input_line_current_index,end_index);
	      if (managed_value) {
		  temp_2 = get_lookup_slot_value(gfi_input_frame,
			  Qgfi_input_variables_update_mode);
		  if (EQ(temp_2,Qon_request_sample_and_hold) || EQ(temp_2,
			  Qon_request)) {
		      if (get_lookup_slot_value_given_default(variable_or_parameter,
			      Qgfi_last_value,Nil)) {
			  gfi_last_value_new_value = 
				  reclaim_managed_number_or_value_function(get_lookup_slot_value_given_default(variable_or_parameter,
				  Qgfi_last_value,Nil));
			  set_non_savable_lookup_slot_value(variable_or_parameter,
				  Qgfi_last_value,gfi_last_value_new_value);
		      }
		      set_non_savable_lookup_slot_value(variable_or_parameter,
			      Qgfi_last_value,managed_value);
		      if (get_lookup_slot_value_given_default(variable_or_parameter,
			      Qgfi_time_of_last_value_update,Nil)) {
			  managed_float = 
				  get_lookup_slot_value_given_default(variable_or_parameter,
				  Qgfi_time_of_last_value_update,Nil);
			  reclaim_managed_simple_float_array_of_length_1(managed_float);
		      }
		      set_non_savable_lookup_slot_value(variable_or_parameter,
			      Qgfi_time_of_last_value_update,
			      copy_managed_float(collection_time));
		      result = VALUES_1(Nil);
		  }
		  else {
		      current_computation_frame = gfi_input_frame;
		      current_computation_instance = 
			      lookup_kb_specific_property_value(Qgfi_data_server,
			      Data_server_kbprop);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_instance,Qcurrent_computation_instance,current_computation_instance,
			      1);
			PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
				0);
			  if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
			      if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_value) 
				      != (SI_Long)0L && 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_value)) 
				      == (SI_Long)1L)
				  temp_2 = 
					  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_value,
					  (SI_Long)0L));
			      else if (INLINE_LONG_VECTOR_P(managed_value) 
				      != (SI_Long)0L && 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_value)) 
				      == (SI_Long)1L)
				  temp_2 = aref1(managed_value,
					  FIX((SI_Long)0L));
			      else
				  temp_2 = managed_value;
			      if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_value) 
				      != (SI_Long)0L && 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_value)) 
				      == (SI_Long)1L)
				  temp_1 = 
					  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_value,
					  (SI_Long)0L));
			      else if (INLINE_LONG_VECTOR_P(managed_value) 
				      != (SI_Long)0L && 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_value)) 
				      == (SI_Long)1L)
				  temp_1 = aref1(managed_value,
					  FIX((SI_Long)0L));
			      else
				  temp_1 = managed_value;
			      put_current_value(5,variable_or_parameter,
				      temp_2,
				      data_type_of_variable_or_parameter_datum(temp_1,
				      variable_or_parameter),Nil,
				      collection_time);
			      managed_value = 
				      reclaim_managed_number_or_value_function(managed_value);
			  }
			  POP_LOCAL_ALLOCATION(0,0);
			POP_SPECIAL();
		      POP_SPECIAL();
		      result = VALUES_1(Nil);
		  }
	      }
	      else {
		  if (illegal_string_p) {
		      Suppress_warning_message_header_qm = T;
		      if ((SI_Long)2L <= IFIX(Warning_message_level)) {
			  temp_2 = 
				  supply_a_or_an(ISVREF(variable_or_parameter,
				  (SI_Long)20L));
			  give_warning_1(6,FIX((SI_Long)2L),
				  string_constant_39,gfi_input_frame,
				  designation,temp_2,
				  ISVREF(variable_or_parameter,(SI_Long)20L));
		      }
		      Suppress_warning_message_header_qm = Nil;
		      close_gfi_input_interface(gfi_input_frame);
		  }
		  else {
		      legal_text_string = copy_text_string(string_1);
		      Suppress_warning_message_header_qm = T;
		      if ((SI_Long)2L <= IFIX(Warning_message_level)) {
			  temp_2 = Current_index;
			  temp_1 = 
				  supply_a_or_an(ISVREF(variable_or_parameter,
				  (SI_Long)20L));
			  give_warning_1(8,FIX((SI_Long)2L),
				  string_constant_40,gfi_input_frame,
				  legal_text_string,temp_2,designation,
				  temp_1,ISVREF(variable_or_parameter,
				  (SI_Long)20L));
		      }
		      Suppress_warning_message_header_qm = Nil;
		      reclaim_text_string(legal_text_string);
		      close_gfi_input_interface(gfi_input_frame);
		  }
		  result = VALUES_1(array_constant_5);
	      }
	    POP_SPECIAL();
	    return result;
	}
	else {
	    if ((SI_Long)3L <= IFIX(Warning_message_level) &&  
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
			      tformat(2,string_constant_41,gfi_input_frame);
			      if (no_data_service_required_qm)
				  twrite_beginning_of_wide_string(array_constant_6,
					  FIX((SI_Long)15L));
			      else
				  tformat(2,string_constant_42,
					  gfi_input_frame);
			      tformat(3,string_constant_43,designation,
				      get_lookup_slot_value_given_default(gfi_input_frame,
				      Qgfi_input_pathname_string_of_stream_qm,
				      Nil));
			      temp_2 = copy_out_current_wide_string();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		    notify_user_1(temp_2);
		    if (Snapshots_of_related_blocks) {
			reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
			Snapshots_of_related_blocks = Nil;
		    }
		  POP_SPECIAL();
		POP_SPECIAL();
	    }
	    temp_1 = get_lookup_slot_value_given_default(gfi_input_frame,
		    Qgfi_input_line,Nil);
	    temp_2 = get_lookup_slot_value_given_default(gfi_input_frame,
		    Qgfi_input_line_current_index,FIX((SI_Long)0L));
	    end_index_qm = skip_to_after_gfi_delimitter_in_string(temp_1,
		    temp_2,
		    get_lookup_slot_value_given_default(gfi_input_frame,
		    Qgfi_input_line_length,FIX((SI_Long)0L)));
	    if (end_index_qm)
		set_non_savable_lookup_slot_value(gfi_input_frame,
			Qgfi_input_line_current_index,end_index_qm);
	    else
		set_non_savable_lookup_slot_value(gfi_input_frame,
			Qgfi_input_line_current_index,
			get_lookup_slot_value_given_default(gfi_input_frame,
			Qgfi_input_line_length,FIX((SI_Long)0L)));
	    return VALUES_1(Nil);
	}
    }
}

static Object float_constant;      /* 0.0 */

static Object array_constant_7;    /* # */

static Object array_constant_8;    /* # */

/* ENCODE-GFI-INPUT-LINE-G2-TIME */
Object encode_gfi_input_line_g2_time(gfi_input_frame)
    Object gfi_input_frame;
{
    Object temp, relative_time_stamp, end_index, managed_float_or_number;
    Object gfi_input_line_g2_time_new_value, seconds_qm, minutes, hours, day;
    Object month, year, second_fraction_float_qm, subsecond_time_qm;
    Object seconds_fixnum_qm, explicit_time_stamp;
    char temp_2;
    double temp_1, store_managed_number_arg, arg, arg_1, aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(217,103);
    if (EQ(get_lookup_slot_value(gfi_input_frame,
	    Qgfi_input_time_stamp_format),Qrelative)) {
	temp = get_lookup_slot_value_given_default(gfi_input_frame,
		Qgfi_input_line,Nil);
	result = read_number_from_string(temp,FIX((SI_Long)0L),
		get_lookup_slot_value_given_default(gfi_input_frame,
		Qgfi_input_line_length,FIX((SI_Long)0L)));
	MVS_2(result,relative_time_stamp,end_index);
	set_non_savable_lookup_slot_value(gfi_input_frame,
		Qgfi_input_line_current_index,end_index);
	if (relative_time_stamp) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		if (get_lookup_slot_value(gfi_input_frame,
			Qignore_gfi_input_base_time_qm)) {
		    if (get_lookup_slot_value_given_default(gfi_input_frame,
			    Qgfi_input_line_g2_time,Nil)) {
			managed_float_or_number = 
				get_lookup_slot_value_given_default(gfi_input_frame,
				Qgfi_input_line_g2_time,Nil);
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_float_or_number) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_float_or_number)) 
				== (SI_Long)1L)
			    reclaim_managed_simple_float_array_of_length_1(managed_float_or_number);
			else if (INLINE_LONG_VECTOR_P(managed_float_or_number) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_float_or_number)) 
				== (SI_Long)1L)
			    reclaim_managed_simple_long_array_of_length_1(managed_float_or_number);
			gfi_input_line_g2_time_new_value = Nil;
			set_non_savable_lookup_slot_value(gfi_input_frame,
				Qgfi_input_line_g2_time,
				gfi_input_line_g2_time_new_value);
		    }
		    if (FIXNUMP(relative_time_stamp)) {
			temp = lfloat(relative_time_stamp,float_constant);
			temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
			store_managed_number_arg = temp_1 + 
				DFLOAT_ISAREF_1(get_lookup_slot_value_given_default(gfi_input_frame,
				Qgfi_input_g2_time_at_start,Nil),(SI_Long)0L);
		    }
		    else {
			temp_1 = DFLOAT_ISAREF_1(relative_time_stamp,
				(SI_Long)0L);
			store_managed_number_arg = temp_1 + 
				DFLOAT_ISAREF_1(get_lookup_slot_value_given_default(gfi_input_frame,
				Qgfi_input_g2_time_at_start,Nil),(SI_Long)0L);
		    }
		    relative_time_stamp = 
			    store_managed_number_function(relative_time_stamp,
			    DOUBLE_TO_DOUBLE_FLOAT(store_managed_number_arg));
		    result = set_non_savable_lookup_slot_value(gfi_input_frame,
			    Qgfi_input_line_g2_time,relative_time_stamp);
		}
		else {
		    if (FIXNUMP(relative_time_stamp)) {
			temp = lfloat(relative_time_stamp,float_constant);
			temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
			store_managed_number_arg = temp_1 + 
				DFLOAT_ISAREF_1(get_lookup_slot_value_given_default(gfi_input_frame,
				Qgfi_input_base_time,Nil),(SI_Long)0L);
		    }
		    else {
			temp_1 = DFLOAT_ISAREF_1(relative_time_stamp,
				(SI_Long)0L);
			store_managed_number_arg = temp_1 + 
				DFLOAT_ISAREF_1(get_lookup_slot_value_given_default(gfi_input_frame,
				Qgfi_input_base_time,Nil),(SI_Long)0L);
		    }
		    relative_time_stamp = 
			    store_managed_number_function(relative_time_stamp,
			    DOUBLE_TO_DOUBLE_FLOAT(store_managed_number_arg));
		    if (get_lookup_slot_value_given_default(gfi_input_frame,
			    Qgfi_input_line_g2_time,Nil)) {
			managed_float_or_number = 
				get_lookup_slot_value_given_default(gfi_input_frame,
				Qgfi_input_line_g2_time,Nil);
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_float_or_number) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_float_or_number)) 
				== (SI_Long)1L)
			    reclaim_managed_simple_float_array_of_length_1(managed_float_or_number);
			else if (INLINE_LONG_VECTOR_P(managed_float_or_number) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_float_or_number)) 
				== (SI_Long)1L)
			    reclaim_managed_simple_long_array_of_length_1(managed_float_or_number);
			gfi_input_line_g2_time_new_value = Nil;
			set_non_savable_lookup_slot_value(gfi_input_frame,
				Qgfi_input_line_g2_time,
				gfi_input_line_g2_time_new_value);
		    }
		    result = set_non_savable_lookup_slot_value(gfi_input_frame,
			    Qgfi_input_line_g2_time,relative_time_stamp);
		}
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	    return result;
	}
	else {
	    if (get_lookup_slot_value_given_default(gfi_input_frame,
		    Qgfi_input_line_g2_time,Nil)) {
		managed_float_or_number = 
			get_lookup_slot_value_given_default(gfi_input_frame,
			Qgfi_input_line_g2_time,Nil);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_float_or_number) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_float_or_number)) 
			== (SI_Long)1L)
		    reclaim_managed_simple_float_array_of_length_1(managed_float_or_number);
		else if (INLINE_LONG_VECTOR_P(managed_float_or_number) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_float_or_number)) 
			== (SI_Long)1L)
		    reclaim_managed_simple_long_array_of_length_1(managed_float_or_number);
		gfi_input_line_g2_time_new_value = Nil;
		set_non_savable_lookup_slot_value(gfi_input_frame,
			Qgfi_input_line_g2_time,
			gfi_input_line_g2_time_new_value);
	    }
	    set_non_savable_lookup_slot_value(gfi_input_frame,
		    Qgfi_input_line_g2_time,Nil);
	    return VALUES_1(array_constant_7);
	}
    }
    else {
	temp = get_lookup_slot_value_given_default(gfi_input_frame,
		Qgfi_input_line,Nil);
	result = read_time_stamp_from_string(temp,FIX((SI_Long)0L),
		get_lookup_slot_value_given_default(gfi_input_frame,
		Qgfi_input_line_length,FIX((SI_Long)0L)));
	MVS_7(result,seconds_qm,minutes,hours,day,month,year,end_index);
	set_non_savable_lookup_slot_value(gfi_input_frame,
		Qgfi_input_line_current_index,end_index);
	if (seconds_qm) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(seconds_qm) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(seconds_qm)) == 
			(SI_Long)1L) {
		    temp_1 = DFLOAT_ISAREF_1(seconds_qm,(SI_Long)0L);
		    second_fraction_float_qm = 
			    DOUBLE_TO_DOUBLE_FLOAT(temp_1 - 
			    inline_ffloor_1(DFLOAT_ISAREF_1(seconds_qm,
			    (SI_Long)0L)));
		}
		else
		    second_fraction_float_qm = Nil;
		if (second_fraction_float_qm) {
		    arg = DOUBLE_FLOAT_TO_DOUBLE(second_fraction_float_qm);
		    arg_1 = 0.0;
		    temp_2 =  !(arg == arg_1 &&  
			    !inline_nanp_for_comparison(arg) &&  
			    !inline_nanp_for_comparison(arg_1));
		}
		else
		    temp_2 = TRUEP(Nil);
		subsecond_time_qm = temp_2 ? second_fraction_float_qm : Nil;
		seconds_fixnum_qm = seconds_qm ? 
			(INLINE_DOUBLE_FLOAT_VECTOR_P(seconds_qm) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(seconds_qm)) == 
			(SI_Long)1L ? 
			LONG_TO_FIXNUM(inline_floor_1(DFLOAT_ISAREF_1(seconds_qm,
			(SI_Long)0L))) : seconds_qm) : Nil;
		explicit_time_stamp = 
			gensym_encode_unix_time_as_managed_float(seconds_fixnum_qm,
			minutes,hours,day,month,year);
		if (subsecond_time_qm) {
		    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(subsecond_time_qm);
		    aref_new_value = temp_1 + 
			    DFLOAT_ISAREF_1(explicit_time_stamp,(SI_Long)0L);
		    DFLOAT_ISASET_1(explicit_time_stamp,(SI_Long)0L,
			    aref_new_value);
		}
		if (get_lookup_slot_value(gfi_input_frame,
			Qignore_gfi_input_base_time_qm)) {
		    temp_1 = DFLOAT_ISAREF_1(explicit_time_stamp,(SI_Long)0L);
		    temp_1 = temp_1 - 
			    DFLOAT_ISAREF_1(get_lookup_slot_value_given_default(gfi_input_frame,
			    Qgfi_input_base_time,Nil),(SI_Long)0L);
		    store_managed_number_arg = temp_1 + 
			    DFLOAT_ISAREF_1(get_lookup_slot_value_given_default(gfi_input_frame,
			    Qgfi_input_g2_time_at_start,Nil),(SI_Long)0L);
		    explicit_time_stamp = 
			    store_managed_number_function(explicit_time_stamp,
			    DOUBLE_TO_DOUBLE_FLOAT(store_managed_number_arg));
		}
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(seconds_qm) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(seconds_qm)) == 
			(SI_Long)1L)
		    reclaim_managed_simple_float_array_of_length_1(seconds_qm);
		else if (INLINE_LONG_VECTOR_P(seconds_qm) != (SI_Long)0L 
			&& IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(seconds_qm)) == 
			(SI_Long)1L)
		    reclaim_managed_simple_long_array_of_length_1(seconds_qm);
		seconds_qm = Nil;
		if (get_lookup_slot_value_given_default(gfi_input_frame,
			Qgfi_input_line_g2_time,Nil)) {
		    managed_float_or_number = 
			    get_lookup_slot_value_given_default(gfi_input_frame,
			    Qgfi_input_line_g2_time,Nil);
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_float_or_number) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_float_or_number)) 
			    == (SI_Long)1L)
			reclaim_managed_simple_float_array_of_length_1(managed_float_or_number);
		    else if (INLINE_LONG_VECTOR_P(managed_float_or_number) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_float_or_number)) 
			    == (SI_Long)1L)
			reclaim_managed_simple_long_array_of_length_1(managed_float_or_number);
		    gfi_input_line_g2_time_new_value = Nil;
		    set_non_savable_lookup_slot_value(gfi_input_frame,
			    Qgfi_input_line_g2_time,
			    gfi_input_line_g2_time_new_value);
		}
		result = set_non_savable_lookup_slot_value(gfi_input_frame,
			Qgfi_input_line_g2_time,explicit_time_stamp);
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	    return result;
	}
	else {
	    if (get_lookup_slot_value_given_default(gfi_input_frame,
		    Qgfi_input_line_g2_time,Nil)) {
		managed_float_or_number = 
			get_lookup_slot_value_given_default(gfi_input_frame,
			Qgfi_input_line_g2_time,Nil);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_float_or_number) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_float_or_number)) 
			== (SI_Long)1L)
		    reclaim_managed_simple_float_array_of_length_1(managed_float_or_number);
		else if (INLINE_LONG_VECTOR_P(managed_float_or_number) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_float_or_number)) 
			== (SI_Long)1L)
		    reclaim_managed_simple_long_array_of_length_1(managed_float_or_number);
		gfi_input_line_g2_time_new_value = Nil;
		set_non_savable_lookup_slot_value(gfi_input_frame,
			Qgfi_input_line_g2_time,
			gfi_input_line_g2_time_new_value);
	    }
	    set_non_savable_lookup_slot_value(gfi_input_frame,
		    Qgfi_input_line_g2_time,Nil);
	    return VALUES_1(array_constant_8);
	}
    }
}

static Object Qsynchronize_gfi_input_file;  /* synchronize-gfi-input-file */

static Object string_constant_44;  /* "The GFI Input Interface ~NF could not parse an input line of ~
				    *                  event log file ~S.  The line read is ~S."
				    */

static Object string_constant_45;  /* "An input line of the spreadsheet file ~S ~
				    *                  of the GFI Input Interface ~NF ended unexpectedly.  The ~
				    *                  line read is ~S."
				    */

static Object string_constant_46;  /* "Couldn't parse an input line of spreadsheet file ~S ~
				    *                        for the GFI Input Interface ~NF.  The line read ~
				    *                        is ~S."
				    */

static Object string_constant_47;  /* "Error in reading the time stamp from the GFI file ~S for ~
				    *  ?       the GFI Input Interface ~NF:  ~A."
				    */

/* SYNCHRONIZE-GFI-INPUT-FILE */
Object synchronize_gfi_input_file(gfi_input_frame,
	    do_not_override_time_slice_p,no_data_service_required_qm)
    Object gfi_input_frame, do_not_override_time_slice_p;
    Object no_data_service_required_qm;
{
    Object tag_temp, lines_read, error_message_qm, designation, error_p;
    Object temp_1, temp_2, start_index_of_value, legal_text_string;
    Object current_index_qm, line, length_1, result_1, ab_loop_list_;
    SI_Long temp_3;
    char temp;
    double arg, arg_1;
    Declare_catch(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(217,104);
    tag_temp = UNIQUE_TAG(Qsynchronize_gfi_input_file);
    if (PUSH_CATCH(tag_temp,0)) {
	lines_read = FIX((SI_Long)0L);
	error_message_qm = Nil;
      next_loop:
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	  next_loop_1:
	    error_message_qm = encode_gfi_input_line_g2_time(gfi_input_frame);
	    if ( !TRUEP(text_string_p(error_message_qm))) {
		arg = 
			DFLOAT_ISAREF_1(get_lookup_slot_value_given_default(gfi_input_frame,
			Qgfi_input_line_g2_time,Nil),(SI_Long)0L);
		arg_1 = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L);
		temp = arg <= arg_1 &&  !inline_nanp_for_comparison(arg) ? 
			 !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if ( !temp)
		goto end_loop;
	    if (EQ(get_lookup_slot_value(gfi_input_frame,
		    Qgfi_input_file_format),Qevent_log)) {
	      next_loop_2:
		result = parse_delimitter_then_designation(1,gfi_input_frame);
		MVS_2(result,designation,error_p);
		if (designation &&  !TRUEP(error_p)) {
		    temp_1 = 
			    get_lookup_slot_value_given_default(gfi_input_frame,
			    Qgfi_input_line,Nil);
		    temp_2 = 
			    get_lookup_slot_value_given_default(gfi_input_frame,
			    Qgfi_input_line_current_index,FIX((SI_Long)0L));
		    start_index_of_value = 
			    skip_to_after_gfi_delimitter_in_string(temp_1,
			    temp_2,
			    get_lookup_slot_value_given_default(gfi_input_frame,
			    Qgfi_input_line_length,FIX((SI_Long)0L)));
		    if (start_index_of_value && 
			    FIXNUM_LT(start_index_of_value,
			    get_lookup_slot_value_given_default(gfi_input_frame,
			    Qgfi_input_line_length,FIX((SI_Long)0L)))) {
			set_non_savable_lookup_slot_value(gfi_input_frame,
				Qgfi_input_line_current_index,
				start_index_of_value);
			temp_2 = 
				put_gfi_value_of_designation_into_appropriate_place(designation,
				gfi_input_frame,no_data_service_required_qm);
			goto end_1;
		    }
		}
		legal_text_string = 
			copy_text_string(get_lookup_slot_value_given_default(gfi_input_frame,
			Qgfi_input_line,Nil));
		Suppress_warning_message_header_qm = T;
		if ((SI_Long)2L <= IFIX(Warning_message_level))
		    give_warning_1(5,FIX((SI_Long)2L),string_constant_44,
			    gfi_input_frame,
			    get_lookup_slot_value_given_default(gfi_input_frame,
			    Qgfi_input_pathname_string_of_stream_qm,Nil),
			    legal_text_string);
		Suppress_warning_message_header_qm = Nil;
		reclaim_text_string(legal_text_string);
		close_gfi_input_interface(gfi_input_frame);
		temp_2 = array_constant_5;
		goto end_1;
		goto next_loop_2;
	      end_loop_1:
		temp_2 = Qnil;
	      end_1:;
	    }
	    else {
		current_index_qm = 
			get_lookup_slot_value_given_default(gfi_input_frame,
			Qgfi_input_line_current_index,FIX((SI_Long)0L));
		line = get_lookup_slot_value_given_default(gfi_input_frame,
			Qgfi_input_line,Nil);
		length_1 = 
			get_lookup_slot_value_given_default(gfi_input_frame,
			Qgfi_input_line_length,FIX((SI_Long)0L));
		result_1 = Nil;
		designation = Nil;
		ab_loop_list_ = 
			get_lookup_slot_value_given_default(gfi_input_frame,
			Qgfi_input_spreadsheet_designations,Nil);
	      next_loop_3:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_2;
		designation = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if (FIXNUM_EQ(current_index_qm,length_1)) {
		    legal_text_string = 
			    copy_text_string(get_lookup_slot_value_given_default(gfi_input_frame,
			    Qgfi_input_line,Nil));
		    Suppress_warning_message_header_qm = T;
		    if ((SI_Long)2L <= IFIX(Warning_message_level))
			give_warning_1(5,FIX((SI_Long)2L),
				string_constant_45,
				get_lookup_slot_value_given_default(gfi_input_frame,
				Qgfi_input_pathname_string_of_stream_qm,
				Nil),gfi_input_frame,legal_text_string);
		    Suppress_warning_message_header_qm = Nil;
		    reclaim_text_string(legal_text_string);
		    close_gfi_input_interface(gfi_input_frame);
		    temp_2 = array_constant_5;
		    goto end_2;
		}
		current_index_qm = 
			skip_to_after_gfi_delimitter_in_string(line,
			current_index_qm,length_1);
		if (current_index_qm) {
		    set_non_savable_lookup_slot_value(gfi_input_frame,
			    Qgfi_input_line_current_index,current_index_qm);
		    if (FIXNUM_LT(current_index_qm,length_1)) {
			temp_2 = 
				get_lookup_slot_value_given_default(gfi_input_frame,
				Qgfi_input_line,Nil);
			temp =  !(UBYTE_16_ISAREF_1(temp_2,
				IFIX(current_index_qm)) == 
				IFIX(Gfi_delimitter));
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp) {
			result_1 = 
				put_gfi_value_of_designation_into_appropriate_place(designation,
				gfi_input_frame,no_data_service_required_qm);
			if (text_string_p(result_1)) {
			    close_gfi_input_interface(gfi_input_frame);
			    temp_2 = result_1;
			    goto end_2;
			}
		    }
		}
		else {
		    legal_text_string = 
			    copy_text_string(get_lookup_slot_value_given_default(gfi_input_frame,
			    Qgfi_input_line,Nil));
		    Suppress_warning_message_header_qm = T;
		    if ((SI_Long)2L <= IFIX(Warning_message_level))
			give_warning_1(5,FIX((SI_Long)2L),
				string_constant_46,
				get_lookup_slot_value_given_default(gfi_input_frame,
				Qgfi_input_pathname_string_of_stream_qm,
				Nil),gfi_input_frame,legal_text_string);
		    Suppress_warning_message_header_qm = Nil;
		    reclaim_text_string(legal_text_string);
		    close_gfi_input_interface(gfi_input_frame);
		    temp_2 = array_constant_5;
		    goto end_2;
		}
		goto next_loop_3;
	      end_loop_2:
		temp_2 = Qnil;
	      end_2:;
	    }
	    if (text_string_p(temp_2)) {
		set_non_savable_lookup_slot_value(gfi_input_frame,
			Qgfi_input_file_synchronized_qm,Nil);
		result = VALUES_1(Nil);
		THROW(tag_temp,result);
	    }
	    if ( !TRUEP(read_one_gfi_input_line(gfi_input_frame))) {
		set_non_savable_lookup_slot_value(gfi_input_frame,
			Qgfi_input_file_synchronized_qm,T);
		result = VALUES_1(T);
		THROW(tag_temp,result);
	    }
	    lines_read = FIXNUM_ADD1(lines_read);
	    if (do_not_override_time_slice_p) {
		Time_slice_expired_p = time_slice_expired_p();
		temp = TRUEP(Time_slice_expired_p);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp);
	    else {
		temp_3 = IFIX(lines_read) % (SI_Long)500L;
		temp = temp_3 == (SI_Long)0L;
	    }
	    if (temp)
		goto end_loop;
	    goto next_loop_1;
	  end_loop:;
	}
	POP_LOCAL_ALLOCATION(0,0);
	if (do_not_override_time_slice_p) {
	    temp = TRUEP(Time_slice_expired_p);
	    if (temp);
	    else {
		Time_slice_expired_p = time_slice_expired_p();
		temp = TRUEP(Time_slice_expired_p);
	    }
	}
	else
	    temp = TRUEP(Nil);
	if (temp);
	else
	    temp = TRUEP(text_string_p(error_message_qm));
	if (temp);
	else {
	    arg = 
		    DFLOAT_ISAREF_1(get_lookup_slot_value_given_default(gfi_input_frame,
		    Qgfi_input_line_g2_time,Nil),(SI_Long)0L);
	    arg_1 = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L);
	    temp = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	}
	if (temp)
	    goto end_loop_3;
	goto next_loop;
      end_loop_3:
	if (text_string_p(error_message_qm)) {
	    Suppress_warning_message_header_qm = T;
	    if ((SI_Long)2L <= IFIX(Warning_message_level)) {
		temp_2 = 
			get_lookup_slot_value_given_default(gfi_input_frame,
			Qgfi_input_pathname_string_of_stream_qm,Nil);
		give_warning_1(5,FIX((SI_Long)2L),string_constant_47,
			temp_2,gfi_input_frame,error_message_qm);
	    }
	    Suppress_warning_message_header_qm = Nil;
	    close_gfi_input_interface(gfi_input_frame);
	    set_non_savable_lookup_slot_value(gfi_input_frame,
		    Qgfi_input_file_synchronized_qm,Nil);
	    result = VALUES_1(Nil);
	    goto end_3;
	}
	set_non_savable_lookup_slot_value(gfi_input_frame,
		Qgfi_input_file_synchronized_qm, 
		!TRUEP(Time_slice_expired_p) ? T : Nil);
	result = VALUES_1( !TRUEP(Time_slice_expired_p) ? T : Nil);
	goto end_3;
	result = VALUES_1(Qnil);
      end_3:;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    return result;
}

/* CLOSE-GFI-INPUT-INTERFACE */
Object close_gfi_input_interface(gfi_input_frame)
    Object gfi_input_frame;
{
    Object queue, time_slice_expired_p_1, gensymed_symbol, temp;
    Object gensymed_symbol_1, gensymed_symbol_2, first_1, last_1, next, temp_2;
    Object temp_3, variable, ab_loop_list_, input_stream;
    Object current_computation_frame, thing, managed_float;
    Object amf_available_array_cons_qm, amf_array, amf_result, new_float;
    SI_Long svref_new_value;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(217,105);
    queue = get_lookup_slot_value_given_default(gfi_input_frame,
	    Qgfi_queue_of_variables_that_need_values,Nil);
    if (queue) {
	if (CAR(queue)) {
	    if (System_is_running) {
		set_non_savable_lookup_slot_value(gfi_input_frame,
			Qgfi_input_file_synchronized_qm,T);
		time_slice_expired_p_1 = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Time_slice_expired_p,Qtime_slice_expired_p,time_slice_expired_p_1,
			0);
		  gensymed_symbol = 
			  get_lookup_slot_value_given_default(gfi_input_frame,
			  Qgfi_queue_of_variables_that_need_values,Nil);
		  temp = CDR(gensymed_symbol);
		  gensymed_symbol_1 = CAR(temp);
		  gensymed_symbol_2 = Nil;
		next_loop:
		  if (CAR(gensymed_symbol)) {
		      temp = CAR(gensymed_symbol);
		      temp_1 =  !EQ(gensymed_symbol_1,CAR(temp));
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  if ( !temp_1)
		      goto end_loop;
		next_loop_1:
		  first_1 = CAR(gensymed_symbol);
		  last_1 = CDR(gensymed_symbol);
		  next = CDR(first_1);
		  if ( !TRUEP(first_1)) {
		      gensymed_symbol_2 = Nil;
		      goto end_1;
		  }
		  else if (EQ(first_1,CAR(gensymed_symbol))) {
		      if (EQ(first_1,last_1))
			  CAS_CDR(gensymed_symbol,last_1,next);
		      else {
			  gensymed_symbol_2 = CAR(first_1);
			  if (CAS_CAR(gensymed_symbol,first_1,next)) {
			      inline_note_reclaim_cons(first_1,Qgfi);
			      if (ISVREF(Available_gfi_conses_tail_vector,
				      IFIX(Current_thread_index))) {
				  temp_2 = 
					  ISVREF(Available_gfi_conses_tail_vector,
					  IFIX(Current_thread_index));
				  M_CDR(temp_2) = first_1;
				  temp_2 = Available_gfi_conses_tail_vector;
				  temp_3 = Current_thread_index;
				  SVREF(temp_2,temp_3) = first_1;
			      }
			      else {
				  temp_2 = Available_gfi_conses_vector;
				  temp_3 = Current_thread_index;
				  SVREF(temp_2,temp_3) = first_1;
				  temp_2 = Available_gfi_conses_tail_vector;
				  temp_3 = Current_thread_index;
				  SVREF(temp_2,temp_3) = first_1;
			      }
			      M_CDR(first_1) = Nil;
			      goto end_1;
			  }
		      }
		  }
		  goto next_loop_1;
		end_loop_1:
		  gensymed_symbol_2 = Qnil;
		end_1:
		  svref_new_value = IFIX(ISVREF(gensymed_symbol_2,
			  (SI_Long)5L)) &  ~(SI_Long)4096L;
		  ISVREF(gensymed_symbol_2,(SI_Long)5L) = FIX(svref_new_value);
		  collect_one_shot_data_for_gfi_data_service(gensymed_symbol_2);
		  Time_slice_expired_p = time_slice_expired_p();
		  if (Time_slice_expired_p)
		      goto end_loop;
		  goto next_loop;
		end_loop:;
		  queue = 
			  get_lookup_slot_value_given_default(gfi_input_frame,
			  Qgfi_queue_of_variables_that_need_values,Nil);
		  variable = Nil;
		  ab_loop_list_ = CAR(queue);
		next_loop_2:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_2;
		  variable = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  svref_new_value = IFIX(ISVREF(variable,(SI_Long)5L)) &  
			  ~(SI_Long)4096L;
		  ISVREF(variable,(SI_Long)5L) = FIX(svref_new_value);
		  goto next_loop_2;
		end_loop_2:;
		POP_SPECIAL();
	    }
	    reclaim_gfi_list_1(CAR(queue));
	}
	reclaim_gfi_cons_1(queue);
    }
    set_non_savable_lookup_slot_value(gfi_input_frame,
	    Qgfi_queue_of_variables_that_need_values,Nil);
    set_non_savable_lookup_slot_value(gfi_input_frame,
	    Qgfi_input_file_synchronized_qm,Nil);
    if (get_lookup_slot_value_given_default(gfi_input_frame,
	    Qgfi_input_without_interruption_qm,Nil))
	gfi_delete_from_queue(gfi_input_frame,
		Queue_of_active_uninterruptable_gfi_input_interface_objects);
    else
	gfi_delete_from_queue(gfi_input_frame,
		Queue_of_active_gfi_input_interface_objects);
    if (get_lookup_slot_value_given_default(gfi_input_frame,
	    Qgfi_current_input_designation,Nil)) {
	reclaim_slot_value(get_lookup_slot_value_given_default(gfi_input_frame,
		Qgfi_current_input_designation,Nil));
	set_non_savable_lookup_slot_value(gfi_input_frame,
		Qgfi_current_input_designation,Nil);
    }
    set_non_savable_lookup_slot_value(gfi_input_frame,Qgfi_inputting_qm,Nil);
    input_stream = get_lookup_slot_value_given_default(gfi_input_frame,
	    Qgfi_input_file_stream,Nil);
    current_computation_frame = gfi_input_frame;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    0);
      if (input_stream) {
	  g2_stream_close(input_stream);
	  change_slot_value(3,gfi_input_frame,Qfile_status,Qclosed);
	  set_non_savable_lookup_slot_value(gfi_input_frame,
		  Qgfi_input_file_stream,Nil);
      }
      else if ( !EQ(get_slot_value_function(gfi_input_frame,Qfile_status,
	      Nil),Qfailed_to_open))
	  change_slot_value(3,gfi_input_frame,Qfile_status,Qready_to_open);
    POP_SPECIAL();
    thing = get_lookup_slot_value_given_default(gfi_input_frame,
	    Qgfi_input_base_time,Nil);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(thing) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) == (SI_Long)1L) {
	managed_float = 
		get_lookup_slot_value_given_default(gfi_input_frame,
		Qgfi_input_base_time,Nil);
	reclaim_managed_simple_float_array_of_length_1(managed_float);
	set_non_savable_lookup_slot_value(gfi_input_frame,
		Qgfi_input_base_time,Nil);
    }
    if (get_lookup_slot_value_given_default(gfi_input_frame,
	    Qgfi_input_line,Nil)) {
	reclaim_text_string(get_lookup_slot_value_given_default(gfi_input_frame,
		Qgfi_input_line,Nil));
	set_non_savable_lookup_slot_value(gfi_input_frame,Qgfi_input_line,Nil);
    }
    if (get_lookup_slot_value_given_default(gfi_input_frame,
	    Qgfi_input_line_g2_time,Nil)) {
	temp_2 = get_lookup_slot_value_given_default(gfi_input_frame,
		Qgfi_input_line_g2_time,Nil);
	DFLOAT_ISASET_1(temp_2,(SI_Long)0L,0.0);
    }
    else {
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp_2 = Vector_of_simple_float_array_pools;
	    temp_3 = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	    if (ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_2 = ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_2) = amf_available_array_cons_qm;
		temp_2 = Available_float_array_conses_tail_vector;
		temp_3 = Current_thread_index;
		SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
	    }
	    else {
		temp_2 = Available_float_array_conses_vector;
		temp_3 = Current_thread_index;
		SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		temp_2 = Available_float_array_conses_tail_vector;
		temp_3 = Current_thread_index;
		SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
	set_non_savable_lookup_slot_value(gfi_input_frame,
		Qgfi_input_line_g2_time,new_float);
    }
    set_non_savable_lookup_slot_value(gfi_input_frame,
	    Qgfi_input_line_length,FIX((SI_Long)0L));
    set_non_savable_lookup_slot_value(gfi_input_frame,
	    Qgfi_input_line_current_index,FIX((SI_Long)0L));
    if (get_lookup_slot_value_given_default(gfi_input_frame,
	    Qgfi_input_pathname_string_of_stream_qm,Nil)) {
	reclaim_text_string(get_lookup_slot_value_given_default(gfi_input_frame,
		Qgfi_input_pathname_string_of_stream_qm,Nil));
	set_non_savable_lookup_slot_value(gfi_input_frame,
		Qgfi_input_pathname_string_of_stream_qm,Nil);
    }
    if (get_lookup_slot_value_given_default(gfi_input_frame,
	    Qgfi_input_spreadsheet_designations,Nil)) {
	reclaim_slot_value(get_lookup_slot_value_given_default(gfi_input_frame,
		Qgfi_input_spreadsheet_designations,Nil));
	return set_non_savable_lookup_slot_value(gfi_input_frame,
		Qgfi_input_spreadsheet_designations,Nil);
    }
    else
	return VALUES_1(Nil);
}

/* DEACTIVATE-FOR-GFI-INPUT-INTERFACE */
Object deactivate_for_gfi_input_interface(gfi_input_interface)
    Object gfi_input_interface;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(217,106);
    close_gfi_input_interface(gfi_input_interface);
    frame = gfi_input_interface;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)7L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qgfi_input_interface)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	return inline_funcall_1(method_function_qm,frame);
    else
	return VALUES_1(Nil);
}

/* RECLAIM-GFI-LAST-VALUE-VALUE */
Object reclaim_gfi_last_value_value(slot_value,frame)
    Object slot_value, frame;
{
    Object gfi_last_value_new_value;

    x_note_fn_call(217,107);
    gfi_last_value_new_value = 
	    reclaim_managed_number_or_value_function(get_lookup_slot_value_given_default(frame,
	    Qgfi_last_value,Nil));
    set_non_savable_lookup_slot_value(frame,Qgfi_last_value,
	    gfi_last_value_new_value);
    return VALUES_1(Nil);
}

static Object string_constant_48;  /* "The GFI input interface object ~ND is not active ~
				    *                         and thus could not supply a value in response ~
				    *                         to a request by ~NF."
				    */

static Object string_constant_49;  /* "The GFI input interface object of ~NF, ~ND, is not a GFI ~
				    *                        Input Interface.  Hence no value could be obtained ~
				    *                        for the variable via the GFI Data Server."
				    */

static Object string_constant_50;  /* "The GFI input interface object of ~NF, ~ND, does ~
				    *                        not exist.  Hence no value could be ~
				    * ??       obtained for it via the GFI Data Server."
				    */

static Object string_constant_51;  /* "The GFI input interface object of ~NF has not yet ~
				    *  ??       been specified.  Hence no value could be obtained ~
				    *                        for it via the GFI Data Server."
				    */

static Object string_constant_52;  /* "The variable ~NF has not been given the gfi-data-service ~
				    *            superior class and so it may not have GFI as its data server."
				    */

/* COLLECT-ONE-SHOT-DATA-FOR-GFI-DATA-SERVICE */
Object collect_one_shot_data_for_gfi_data_service(variable)
    Object variable;
{
    Object gensymed_symbol, sub_class_bit_vector, gfi_input_frame_designation;
    Object gfi_input_frame, gfi_last_value, current_computation_frame;
    Object current_computation_instance, temp_1, temp_2, temp_3, item;
    Object queue_pair, new_cons, svref_arg_2, svref_new_value;
    Object gensymed_symbol_4, first_1, last_1, next;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long svref_new_value_1;
    char temp;
    Declare_special(2);
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(217,108);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(Qgfi_data_service,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(variable,(SI_Long)1L),
		(SI_Long)19L);
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
    if (temp) {
	if (ISVREF(lookup_kb_specific_property_value(Qgfi_data_server,
		Data_server_kbprop),(SI_Long)6L)) {
	    gfi_input_frame_designation = get_lookup_slot_value(variable,
		    Qgfi_input_interface_object);
	    gfi_input_frame = Nil;
	    gfi_last_value = Nil;
	    if (gfi_input_frame_designation) {
		current_computation_frame = variable;
		PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
			0);
		  gfi_input_frame = 
			  evaluate_designation(gfi_input_frame_designation,
			  Nil);
		POP_SPECIAL();
		temp = TRUEP(gfi_input_frame);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp ?  !(SIMPLE_VECTOR_P(gfi_input_frame) && 
		    EQ(ISVREF(gfi_input_frame,(SI_Long)0L),
		    Qg2_defstruct_structure_name_temporary_constant_g2_struct)) 
		    : TRUEP(Nil)) {
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(Qgfi_input_interface,
			Class_description_gkbprop);
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(ISVREF(gfi_input_frame,
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
		if (temp) {
		    if (get_lookup_slot_value_given_default(gfi_input_frame,
			    Qgfi_input_file_synchronized_qm,Nil)) {
			gfi_last_value = 
				get_lookup_slot_value_given_default(variable,
				Qgfi_last_value,Nil);
			temp = TRUEP(gfi_last_value);
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp) {
			if (EQ(get_lookup_slot_value(gfi_input_frame,
				Qgfi_input_variables_update_mode),
				Qon_request_sample_and_hold)) {
			    current_computation_frame = gfi_input_frame;
			    current_computation_instance = 
				    lookup_kb_specific_property_value(Qgfi_data_server,
				    Data_server_kbprop);
			    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_instance,Qcurrent_computation_instance,current_computation_instance,
				    1);
			      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
				      0);
				if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
				    if (INLINE_DOUBLE_FLOAT_VECTOR_P(gfi_last_value) 
					    != (SI_Long)0L && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gfi_last_value)) 
					    == (SI_Long)1L)
					temp_1 = 
						DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(gfi_last_value,
						(SI_Long)0L));
				    else if (INLINE_LONG_VECTOR_P(gfi_last_value) 
					    != (SI_Long)0L && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gfi_last_value)) 
					    == (SI_Long)1L)
					temp_1 = aref1(gfi_last_value,
						FIX((SI_Long)0L));
				    else
					temp_1 = gfi_last_value;
				    if (INLINE_DOUBLE_FLOAT_VECTOR_P(gfi_last_value) 
					    != (SI_Long)0L && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gfi_last_value)) 
					    == (SI_Long)1L)
					temp_2 = 
						DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(gfi_last_value,
						(SI_Long)0L));
				    else if (INLINE_LONG_VECTOR_P(gfi_last_value) 
					    != (SI_Long)0L && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gfi_last_value)) 
					    == (SI_Long)1L)
					temp_2 = aref1(gfi_last_value,
						FIX((SI_Long)0L));
				    else
					temp_2 = gfi_last_value;
				    temp_2 = 
					    data_type_of_variable_or_parameter_datum(temp_2,
					    variable);
				    put_current_value(5,variable,temp_1,
					    temp_2,Nil,Current_g2_time);
				}
				POP_LOCAL_ALLOCATION(0,0);
			      POP_SPECIAL();
			    POP_SPECIAL();
			}
			else {
			    current_computation_frame = gfi_input_frame;
			    current_computation_instance = 
				    lookup_kb_specific_property_value(Qgfi_data_server,
				    Data_server_kbprop);
			    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_instance,Qcurrent_computation_instance,current_computation_instance,
				    1);
			      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
				      0);
				if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
				    if (INLINE_DOUBLE_FLOAT_VECTOR_P(gfi_last_value) 
					    != (SI_Long)0L && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gfi_last_value)) 
					    == (SI_Long)1L)
					temp_1 = 
						DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(gfi_last_value,
						(SI_Long)0L));
				    else if (INLINE_LONG_VECTOR_P(gfi_last_value) 
					    != (SI_Long)0L && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gfi_last_value)) 
					    == (SI_Long)1L)
					temp_1 = aref1(gfi_last_value,
						FIX((SI_Long)0L));
				    else
					temp_1 = gfi_last_value;
				    if (INLINE_DOUBLE_FLOAT_VECTOR_P(gfi_last_value) 
					    != (SI_Long)0L && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gfi_last_value)) 
					    == (SI_Long)1L)
					temp_2 = 
						DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(gfi_last_value,
						(SI_Long)0L));
				    else if (INLINE_LONG_VECTOR_P(gfi_last_value) 
					    != (SI_Long)0L && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gfi_last_value)) 
					    == (SI_Long)1L)
					temp_2 = aref1(gfi_last_value,
						FIX((SI_Long)0L));
				    else
					temp_2 = gfi_last_value;
				    temp_2 = 
					    data_type_of_variable_or_parameter_datum(temp_2,
					    variable);
				    put_current_value(5,variable,temp_1,
					    temp_2,Nil,
					    get_lookup_slot_value_given_default(variable,
					    Qgfi_time_of_last_value_update,
					    Nil));
				    temp_3 = 
					    reclaim_managed_number_or_value_function(get_lookup_slot_value_given_default(variable,
					    Qgfi_last_value,Nil));
				    set_non_savable_lookup_slot_value(variable,
					    Qgfi_last_value,temp_3);
				    set_non_savable_lookup_slot_value(variable,
					    Qgfi_last_value,Nil);
				}
				POP_LOCAL_ALLOCATION(0,0);
			      POP_SPECIAL();
			    POP_SPECIAL();
			}
		    }
		    else if (get_lookup_slot_value_given_default(gfi_input_frame,
			    Qgfi_inputting_qm,Nil) &&  !((SI_Long)0L != 
			    (IFIX(ISVREF(variable,(SI_Long)5L)) & 
			    (SI_Long)4096L))) {
			item = variable;
			queue_pair = 
				get_lookup_slot_value_given_default(gfi_input_frame,
				Qgfi_queue_of_variables_that_need_values,Nil);
			gensymed_symbol = item;
			new_cons = ISVREF(Available_gfi_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    temp_3 = Available_gfi_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(temp_3,svref_arg_2) = svref_new_value;
			    if ( !TRUEP(ISVREF(Available_gfi_conses_vector,
				    IFIX(Current_thread_index)))) {
				temp_3 = Available_gfi_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_3,svref_arg_2) = Nil;
			    }
			    gensymed_symbol_4 = new_cons;
			}
			else
			    gensymed_symbol_4 = Nil;
			if ( !TRUEP(gensymed_symbol_4))
			    gensymed_symbol_4 = replenish_gfi_cons_pool();
			M_CAR(gensymed_symbol_4) = gensymed_symbol;
			M_CDR(gensymed_symbol_4) = Nil;
			inline_note_allocate_cons(gensymed_symbol_4,Qgfi);
		      next_loop:
			first_1 = CAR(queue_pair);
			last_1 = CDR(queue_pair);
			temp_1 = CDR(queue_pair);
			next = CDR(temp_1);
			if ( !TRUEP(first_1)) {
			    if (CAS_CAR(queue_pair,first_1,
					gensymed_symbol_4)) {
				CAS_CDR(queue_pair,last_1,gensymed_symbol_4);
				goto end_1;
			    }
			}
			else if (EQ(last_1,CDR(queue_pair))) {
			    if ( !TRUEP(next)) {
				if (CAS_CDR(last_1,next,gensymed_symbol_4)) {
				    CAS_CDR(queue_pair,last_1,
					    gensymed_symbol_4);
				    goto end_1;
				}
			    }
			    else
				CAS_CDR(queue_pair,last_1,next);
			}
			goto next_loop;
		      end_loop:
		      end_1:;
			svref_new_value_1 = IFIX(ISVREF(variable,
				(SI_Long)5L)) | (SI_Long)4096L;
			ISVREF(variable,(SI_Long)5L) = FIX(svref_new_value_1);
		    }
		    else if ( !((SI_Long)0L != 
			    (IFIX(ISVREF(gfi_input_frame,(SI_Long)5L)) & 
			    (SI_Long)1L))) {
			Suppress_warning_message_header_qm = T;
			if ((SI_Long)2L <= IFIX(Warning_message_level))
			    give_warning_1(4,FIX((SI_Long)2L),
				    string_constant_48,
				    gfi_input_frame_designation,variable);
			Suppress_warning_message_header_qm = Nil;
		    }
		}
		else {
		    reclaim_if_temporary_constant_function(gfi_input_frame);
		    Suppress_warning_message_header_qm = T;
		    if ((SI_Long)2L <= IFIX(Warning_message_level))
			give_warning_1(3,FIX((SI_Long)2L),
				string_constant_49,variable);
		    Suppress_warning_message_header_qm = Nil;
		}
	    }
	    else {
		reclaim_if_temporary_constant_function(gfi_input_frame);
		if (gfi_input_frame_designation) {
		    Suppress_warning_message_header_qm = T;
		    if ((SI_Long)2L <= IFIX(Warning_message_level))
			give_warning_1(4,FIX((SI_Long)2L),
				string_constant_50,variable,
				gfi_input_frame_designation);
		    Suppress_warning_message_header_qm = Nil;
		}
		else {
		    Suppress_warning_message_header_qm = T;
		    if ((SI_Long)2L <= IFIX(Warning_message_level))
			give_warning_1(3,FIX((SI_Long)2L),
				string_constant_51,variable);
		    Suppress_warning_message_header_qm = Nil;
		}
	    }
	}
    }
    else {
	Suppress_warning_message_header_qm = T;
	if ((SI_Long)1L <= IFIX(Warning_message_level))
	    give_warning_1(3,FIX((SI_Long)1L),string_constant_52,variable);
	Suppress_warning_message_header_qm = Nil;
    }
    return VALUES_1(Nil);
}

static Object Qcollect_one_shot_data_for_gfi_data_service;  /* collect-one-shot-data-for-gfi-data-service */

static Object string_constant_53;  /* "The variable ~NF has not been given the gfi-data-service ~
				    *              superior class and so it may not have GFI as its data server."
				    */

/* BEGIN-COLLECTING-DATA-FOR-GFI-DATA-SERVICE */
Object begin_collecting_data_for_gfi_data_service(variable,interval)
    Object variable, interval;
{
    Object gensymed_symbol, sub_class_bit_vector, old, new_1;
    Object def_structure_schedule_task_variable, temp_1, svref_arg_2;
    Object svref_new_value, task, ctask, p, v, q, structure_being_reclaimed;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp, g2_p;
    double aref_new_value;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(217,109);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(Qgfi_data_service,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(variable,(SI_Long)1L),
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
	if (temp) {
	    old = Nil;
	    new_1 = Nil;
	  next_loop:
	    old = ISVREF(variable,(SI_Long)40L);
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
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = Nil;
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
	    task = def_structure_schedule_task_variable;
	    temp_1 = ISVREF(task,(SI_Long)1L);
	    aref_new_value = FIXNUMP(interval) ? (double)IFIX(interval) : 
		    DFLOAT_ISAREF_1(interval,(SI_Long)0L);
	    DFLOAT_ISASET_1(temp_1,(SI_Long)1L,aref_new_value);
	    temp_1 = ISVREF(Data_server_parameters,(SI_Long)22L);
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
	    SVREF(task,FIX((SI_Long)7L)) = 
		    Qcollect_one_shot_data_for_gfi_data_service;
	    temp_1 = 
		    SYMBOL_FUNCTION(Qcollect_one_shot_data_for_gfi_data_service);
	    SVREF(task,FIX((SI_Long)8L)) = temp_1;
	    ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
	    SVREF(task,FIX((SI_Long)13L)) = variable;
	    new_1 = task;
	    if (CAS_SVREF(variable,(SI_Long)40L,old,new_1)) {
		task = new_1;
		ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
		if (ctask);
		else
		    ctask = System_is_running;
		p = ISVREF(task,(SI_Long)4L);
		v = ctask ? Current_task_queue_vector : 
			Deferred_task_queue_vector;
		q = ISVREF(v,IFIX(p));
		SVREF(task,FIX((SI_Long)11L)) = q;
		temp_1 = constant_queue_push_right(q,task);
		SVREF(task,FIX((SI_Long)6L)) = temp_1;
		if (ctask && FIXNUM_LT(p,Priority_of_next_task))
		    Priority_of_next_task = p;
		result = VALUES_1(task);
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
	    result = VALUES_1(Qnil);
	  end_1:;
	}
	else {
	    Suppress_warning_message_header_qm = T;
	    if ((SI_Long)2L <= IFIX(Warning_message_level))
		give_warning_1(3,FIX((SI_Long)2L),string_constant_53,variable);
	    Suppress_warning_message_header_qm = Nil;
	    result = VALUES_1(Suppress_warning_message_header_qm);
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* STOP-COLLECTING-DATA-FOR-GFI-DATA-SERVICE */
Object stop_collecting_data_for_gfi_data_service(variable)
    Object variable;
{
    Object gensymed_symbol, structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(217,110);
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = ISVREF(variable,(SI_Long)40L);
    if (CAS_SVREF(variable,(SI_Long)40L,gensymed_symbol,Nil)) {
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
	return VALUES_1(T);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object string_constant_54;  /* "a designation in the GFI Output Interface" */

static Object string_constant_55;  /* "The GFI Output Interface ~NF found a variable or ~
				    *                          parameter, ~A, which matches ~A.  However, when the ~
				    *                          GFI Output Interface started ~
				    * ??? to output to the file ~S, the variable did not match ~
				    * ??? the desgnation.  The value of this variable or ~
				    * ??? parameter will be ignored by GFI."
				    */

/* OUTPUT-GFI-QUEUED-VALUES-TO-STREAM */
Object output_gfi_queued_values_to_stream(gfi_output_frame,forcibly_flush)
    Object gfi_output_frame, forcibly_flush;
{
    Object temp, line_limit, queue, item, output_list, pointer;
    Object head_of_queue_qm, g2_time_of_current_line, new_line_required_qm;
    Object position_qm, first_1, last_1, next, gensymed_symbol, temp_2;
    Object svref_arg_2, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_4, entry_hash, designation_or_substitute_string;
    Object rest_of_list, managed_number_or_value, head_of_queue;
    Object designation_qm;
    SI_Long gensymed_symbol_1, temp_3, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_;
    char temp_1;
    double arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(217,111);
    temp = get_lookup_slot_value(gfi_output_frame,Qgfi_output_file_format);
    if (EQ(temp,Qspreadsheet)) {
	line_limit = get_lookup_slot_value(gfi_output_frame,
		Qmaximum_number_of_output_lines);
	queue = get_lookup_slot_value_given_default(gfi_output_frame,
		Qgfi_queue_of_new_output_values,Nil);
	item = Nil;
	output_list = get_lookup_slot_value_given_default(gfi_output_frame,
		Qgfi_list_of_new_spreadsheet_output_values,Nil);
	pointer = Nil;
	temp = CAR(queue);
	head_of_queue_qm = CAR(temp);
	g2_time_of_current_line = head_of_queue_qm ? 
		ISVREF(head_of_queue_qm,(SI_Long)2L) : Nil;
      next_loop:
	if ( !TRUEP(head_of_queue_qm))
	    goto end_loop;
	if (line_limit && 
		FIXNUM_GE(get_lookup_slot_value_given_default(gfi_output_frame,
		Qnumber_of_lines_output_so_far,Nil),line_limit)) {
	    warning_message_for_limit_reached_in_gfi_output(gfi_output_frame);
	    temp = T;
	    goto end_1;
	}
	else {
	    new_line_required_qm = Nil;
	    position_qm = Nil;
	  next_loop_1:
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		if (head_of_queue_qm) {
		    arg = DFLOAT_ISAREF_1(g2_time_of_current_line,(SI_Long)0L);
		    arg_1 = DFLOAT_ISAREF_1(ISVREF(head_of_queue_qm,
			    (SI_Long)2L),(SI_Long)0L);
		    temp_1 = arg == arg_1 &&  
			    !inline_nanp_for_comparison(arg) ?  
			    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	    if ( !temp_1)
		goto end_loop_1;
	  next_loop_2:
	    first_1 = CAR(queue);
	    last_1 = CDR(queue);
	    next = CDR(first_1);
	    if ( !TRUEP(first_1)) {
		item = Nil;
		goto end_2;
	    }
	    else if (EQ(first_1,CAR(queue))) {
		if (EQ(first_1,last_1))
		    CAS_CDR(queue,last_1,next);
		else {
		    gensymed_symbol = CAR(first_1);
		    if (CAS_CAR(queue,first_1,next)) {
			inline_note_reclaim_cons(first_1,Qgfi);
			if (ISVREF(Available_gfi_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_gfi_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = first_1;
			    temp_2 = Available_gfi_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_2,svref_arg_2) = first_1;
			}
			else {
			    temp_2 = Available_gfi_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_2,svref_arg_2) = first_1;
			    temp_2 = Available_gfi_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_2,svref_arg_2) = first_1;
			}
			M_CDR(first_1) = Nil;
			item = gensymed_symbol;
			goto end_2;
		    }
		}
	    }
	    goto next_loop_2;
	  end_loop_2:
	    item = Qnil;
	  end_2:
	    temp = CAR(queue);
	    head_of_queue_qm = CAR(temp);
	    temp = ISVREF(item,(SI_Long)5L);
	    if (temp);
	    else {
		gensymed_symbol = ISVREF(item,(SI_Long)6L);
		gensymed_symbol_1 = IFIX(frame_hash_function(gensymed_symbol));
		temp = 
			get_lookup_slot_value_given_default(gfi_output_frame,
			Qgfi_output_spreadsheet_field_index_hash,Nil);
		temp_3 = gensymed_symbol_1 % (SI_Long)131L;
		temp = SVREF(temp,FIX(temp_3));
		skip_list = CDR(temp);
		key_value = gensymed_symbol;
		key_hash_value = gensymed_symbol_1;
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_3:
		if (level < ab_loop_bind_)
		    goto end_loop_3;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_4:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_4 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_4,temp);
		MVS_2(result,succ,marked);
	      next_loop_5:
		if ( !TRUEP(marked))
		    goto end_loop_4;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_4 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_4,temp);
		MVS_2(result,succ,marked);
		goto next_loop_5;
	      end_loop_4:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_3;
		goto next_loop_4;
	      end_loop_5:
	      end_3:
		level = level - (SI_Long)1L;
		goto next_loop_3;
	      end_loop_3:;
		temp = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
			(EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
			ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    }
	    position_qm = temp;
	    pointer = position_qm ? nthcdr(position_qm,output_list) : Nil;
	    if (position_qm && pointer) {
		new_line_required_qm = T;
		if (CAR(pointer))
		    reclaim_gfi_queue_item_1(CAR(pointer));
		M_CAR(pointer) = item;
	    }
	    else {
		designation_or_substitute_string = tformat_text_string(2,
			ISVREF(item,(SI_Long)4L) ? string_constant_2 : 
			string_constant_54,ISVREF(item,(SI_Long)4L));
		Suppress_warning_message_header_qm = T;
		if ((SI_Long)2L <= IFIX(Warning_message_level)) {
		    temp = ISVREF(item,(SI_Long)7L);
		    give_warning_1(6,FIX((SI_Long)2L),string_constant_55,
			    gfi_output_frame,temp,
			    designation_or_substitute_string,
			    get_lookup_slot_value_given_default(gfi_output_frame,
			    Qgfi_output_pathname_string_of_stream_qm,Nil));
		}
		Suppress_warning_message_header_qm = Nil;
		reclaim_gfi_queue_item_1(item);
	    }
	    goto next_loop_1;
	  end_loop_1:
	    if (new_line_required_qm) {
		output_appropriate_gfi_time_stamp(gfi_output_frame,
			g2_time_of_current_line);
		item = Nil;
		rest_of_list = output_list;
	      next_loop_6:
		if ( !TRUEP(rest_of_list))
		    goto end_loop_6;
		gfi_write_char(Gfi_delimitter,gfi_output_frame);
		item = CAR(rest_of_list);
		if (item) {
		    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
			managed_number_or_value = ISVREF(item,(SI_Long)1L);
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				== (SI_Long)1L)
			    temp = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				    (SI_Long)0L));
			else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				== (SI_Long)1L)
			    temp = aref1(managed_number_or_value,
				    FIX((SI_Long)0L));
			else
			    temp = managed_number_or_value;
			output_gfi_value(temp,ISVREF(item,(SI_Long)3L),
				gfi_output_frame);
		    }
		    POP_LOCAL_ALLOCATION(0,0);
		    reclaim_gfi_queue_item_1(item);
		    M_CAR(rest_of_list) = Nil;
		}
		rest_of_list = M_CDR(rest_of_list);
		goto next_loop_6;
	      end_loop_6:;
		gfi_terpri(gfi_output_frame);
		temp_2 = 
			FIXNUM_ADD1(get_lookup_slot_value_given_default(gfi_output_frame,
			Qnumber_of_lines_output_so_far,Nil));
		set_non_savable_lookup_slot_value(gfi_output_frame,
			Qnumber_of_lines_output_so_far,temp_2);
	    }
	    if (head_of_queue_qm)
		g2_time_of_current_line = ISVREF(head_of_queue_qm,(SI_Long)2L);
	}
	if ( !TRUEP(forcibly_flush) && time_slice_expired_p() || 
		FIXNUMP(forcibly_flush) && IFIX(forcibly_flush) == (SI_Long)1L)
	    goto end_loop;
	goto next_loop;
      end_loop:
	if (head_of_queue_qm) {
	    temp = Nil;
	    goto end_1;
	}
	else {
	    set_non_savable_lookup_slot_value(gfi_output_frame,
		    Qnew_gfi_output_values_this_cycle_qm,Nil);
	    temp = T;
	    goto end_1;
	}
	temp = Qnil;
      end_1:;
    }
    else if (EQ(temp,Qevent_log)) {
	line_limit = get_lookup_slot_value(gfi_output_frame,
		Qmaximum_number_of_output_lines);
	queue = get_lookup_slot_value_given_default(gfi_output_frame,
		Qgfi_queue_of_new_output_values,Nil);
	item = Nil;
	head_of_queue = Nil;
      next_loop_7:
	temp = CAR(queue);
	head_of_queue = CAR(temp);
	if ( !TRUEP(head_of_queue))
	    goto end_loop_7;
	if (line_limit && 
		FIXNUM_GE(get_lookup_slot_value_given_default(gfi_output_frame,
		Qnumber_of_lines_output_so_far,Nil),line_limit)) {
	    warning_message_for_limit_reached_in_gfi_output(gfi_output_frame);
	    temp = T;
	    goto end_4;
	}
	else {
	    designation_qm = Nil;
	  next_loop_8:
	    first_1 = CAR(queue);
	    last_1 = CDR(queue);
	    next = CDR(first_1);
	    if ( !TRUEP(first_1)) {
		item = Nil;
		goto end_5;
	    }
	    else if (EQ(first_1,CAR(queue))) {
		if (EQ(first_1,last_1))
		    CAS_CDR(queue,last_1,next);
		else {
		    gensymed_symbol = CAR(first_1);
		    if (CAS_CAR(queue,first_1,next)) {
			inline_note_reclaim_cons(first_1,Qgfi);
			if (ISVREF(Available_gfi_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_gfi_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = first_1;
			    temp_2 = Available_gfi_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_2,svref_arg_2) = first_1;
			}
			else {
			    temp_2 = Available_gfi_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_2,svref_arg_2) = first_1;
			    temp_2 = Available_gfi_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_2,svref_arg_2) = first_1;
			}
			M_CDR(first_1) = Nil;
			item = gensymed_symbol;
			goto end_5;
		    }
		}
	    }
	    goto next_loop_8;
	  end_loop_8:
	    item = Qnil;
	  end_5:
	    temp = ISVREF(item,(SI_Long)4L);
	    if (temp);
	    else
		temp = ISVREF(item,(SI_Long)8L);
	    designation_qm = temp;
	    if (designation_qm) {
		output_appropriate_gfi_time_stamp(gfi_output_frame,
			ISVREF(item,(SI_Long)2L));
		gfi_write_char(Gfi_delimitter,gfi_output_frame);
		write_designation_to_stream(designation_qm,gfi_output_frame);
		gfi_write_char(Gfi_delimitter,gfi_output_frame);
		if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		    managed_number_or_value = ISVREF(item,(SI_Long)1L);
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			temp = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			temp = aref1(managed_number_or_value,FIX((SI_Long)0L));
		    else
			temp = managed_number_or_value;
		    output_gfi_value(temp,ISVREF(item,(SI_Long)3L),
			    gfi_output_frame);
		}
		POP_LOCAL_ALLOCATION(0,0);
		gfi_terpri(gfi_output_frame);
		temp_2 = 
			FIXNUM_ADD1(get_lookup_slot_value_given_default(gfi_output_frame,
			Qnumber_of_lines_output_so_far,Nil));
		set_non_savable_lookup_slot_value(gfi_output_frame,
			Qnumber_of_lines_output_so_far,temp_2);
	    }
	    else
		warning_message_for_unnameable_variable(gfi_output_frame,
			ISVREF(item,(SI_Long)7L),designation_qm);
	    reclaim_gfi_queue_item_1(item);
	}
	if ( !TRUEP(forcibly_flush) && time_slice_expired_p() || 
		FIXNUMP(forcibly_flush) && IFIX(forcibly_flush) == (SI_Long)1L)
	    goto end_loop_7;
	goto next_loop_7;
      end_loop_7:
	if (head_of_queue) {
	    temp = Nil;
	    goto end_4;
	}
	else {
	    set_non_savable_lookup_slot_value(gfi_output_frame,
		    Qnew_gfi_output_values_this_cycle_qm,Nil);
	    temp = T;
	    goto end_4;
	}
	temp = Qnil;
      end_4:;
    }
    else
	temp = Qnil;
    return VALUES_1(temp);
}

static Object string_constant_56;  /* "NUPEC Snaphot Input for ~NF has completed." */

static Object string_constant_57;  /* "GFI Input Interface for ~NF has completed.  There ~
				    *                         remain unread values with future timestamps in file ~S."
				    */

static Object string_constant_58;  /* "NUPEC Snaphot Output for ~NF has completed." */

static Object string_constant_59;  /* "GFI Output Interface for ~NF, using file ~S, has completed." */

static Object string_constant_60;  /* "GFI Input Interface for ~NF has completed. ~
				    *                               There remain unread values with future timestamps ~
				    *                               in file ~S."
				    */

/* ACCEPT-DATA-FROM-GFI-DATA-SERVICE */
Object accept_data_from_gfi_data_service()
{
    Object time_slice_expired_p_1, gfi_input_frame, number_of_frames_so_far;
    Object initial_number_of_frames, first_1, last_1, next, gensymed_symbol;
    Object temp, svref_arg_2, temp_1, gfi_output_frame, new_cons;
    Object svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long svref_new_value_1;
    char temp_2;
    Declare_special(1);
    Object result;

    x_note_fn_call(217,112);
    time_slice_expired_p_1 = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Time_slice_expired_p,Qtime_slice_expired_p,time_slice_expired_p_1,
	    0);
      if (CAR(Queue_of_active_uninterruptable_gfi_input_interface_objects)) {
	  gfi_input_frame = Nil;
	  number_of_frames_so_far = FIX((SI_Long)0L);
	  initial_number_of_frames = 
		  length(CAR(Queue_of_active_uninterruptable_gfi_input_interface_objects));
	next_loop:
	next_loop_1:
	  first_1 = 
		  CAR(Queue_of_active_uninterruptable_gfi_input_interface_objects);
	  last_1 = 
		  CDR(Queue_of_active_uninterruptable_gfi_input_interface_objects);
	  next = CDR(first_1);
	  if ( !TRUEP(first_1)) {
	      gfi_input_frame = Nil;
	      goto end_1;
	  }
	  else if (EQ(first_1,
		  CAR(Queue_of_active_uninterruptable_gfi_input_interface_objects))) 
		      {
	      if (EQ(first_1,last_1))
		  CAS_CDR(Queue_of_active_uninterruptable_gfi_input_interface_objects,
			  last_1,next);
	      else {
		  gensymed_symbol = CAR(first_1);
		  if (CAS_CAR(Queue_of_active_uninterruptable_gfi_input_interface_objects,
			  first_1,next)) {
		      inline_note_reclaim_cons(first_1,Qgfi);
		      if (ISVREF(Available_gfi_conses_tail_vector,
			      IFIX(Current_thread_index))) {
			  temp = ISVREF(Available_gfi_conses_tail_vector,
				  IFIX(Current_thread_index));
			  M_CDR(temp) = first_1;
			  temp = Available_gfi_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp,svref_arg_2) = first_1;
		      }
		      else {
			  temp = Available_gfi_conses_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp,svref_arg_2) = first_1;
			  temp = Available_gfi_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp,svref_arg_2) = first_1;
		      }
		      M_CDR(first_1) = Nil;
		      gfi_input_frame = gensymed_symbol;
		      goto end_1;
		  }
	      }
	  }
	  goto next_loop_1;
	end_loop:
	  gfi_input_frame = Qnil;
	end_1:
	  if (gfi_input_frame) {
	      if ( 
		      !TRUEP(get_lookup_slot_value_given_default(gfi_input_frame,
		      Qgfi_input_file_stream,Nil)))
		  open_gfi_input_interface(gfi_input_frame);
	      if (get_lookup_slot_value_given_default(gfi_input_frame,
		      Qgfi_inputting_qm,Nil)) {
		  if (EQ(get_lookup_slot_value(gfi_input_frame,
			  Qgfi_input_file_format),Qnupec_snapshot)) {
		      temp_1 = gfi_input_frame;
		      if (gfi_input_nupec_snapshot_values_periodically(temp_1,
			      Nil,Nil,
			      get_lookup_slot_value_given_default(gfi_input_frame,
			      Qgfi_input_ignore_data_server_qm,Nil))) {
			  Suppress_warning_message_header_qm = T;
			  if ((SI_Long)2L <= IFIX(Warning_message_level))
			      give_warning_1(3,FIX((SI_Long)2L),
				      string_constant_56,gfi_input_frame);
			  Suppress_warning_message_header_qm = Nil;
			  close_gfi_input_interface(gfi_input_frame);
		      }
		  }
		  else if (EQ(get_lookup_slot_value(gfi_input_frame,
			  Qgfi_input_file_format),
			  Qnupec_snapshot_with_restart_time)) {
		      temp_1 = gfi_input_frame;
		      if (gfi_input_nupec_snapshot_values_periodically(temp_1,
			      T,Nil,
			      get_lookup_slot_value_given_default(gfi_input_frame,
			      Qgfi_input_ignore_data_server_qm,Nil))) {
			  Suppress_warning_message_header_qm = T;
			  if ((SI_Long)2L <= IFIX(Warning_message_level))
			      give_warning_1(3,FIX((SI_Long)2L),
				      string_constant_56,gfi_input_frame);
			  Suppress_warning_message_header_qm = Nil;
			  close_gfi_input_interface(gfi_input_frame);
		      }
		  }
		  else {
		      temp_1 = gfi_input_frame;
		      if (synchronize_gfi_input_file(temp_1,Nil,
			      get_lookup_slot_value_given_default(gfi_input_frame,
			      Qgfi_input_ignore_data_server_qm,Nil))) {
			  if (get_lookup_slot_value_given_default(gfi_input_frame,
				  Qgfi_inputting_qm,Nil)) {
			      Suppress_warning_message_header_qm = T;
			      if ((SI_Long)2L <= IFIX(Warning_message_level)) {
				  temp_1 = gfi_input_frame;
				  give_warning_1(4,FIX((SI_Long)2L),
					  string_constant_57,temp_1,
					  get_lookup_slot_value_given_default(gfi_input_frame,
					  Qgfi_input_pathname_string_of_stream_qm,
					  Nil));
			      }
			      Suppress_warning_message_header_qm = Nil;
			      close_gfi_input_interface(gfi_input_frame);
			  }
		      }
		  }
	      }
	  }
	  number_of_frames_so_far = FIXNUM_ADD1(number_of_frames_so_far);
	  if (FIXNUM_GE(number_of_frames_so_far,initial_number_of_frames))
	      goto end_loop_1;
	  goto next_loop;
	end_loop_1:;
      }
      if (CAR(Queue_of_active_uninterruptable_gfi_output_interface_objects)) {
	  gfi_output_frame = Nil;
	  number_of_frames_so_far = FIX((SI_Long)0L);
	  initial_number_of_frames = 
		  length(CAR(Queue_of_active_uninterruptable_gfi_output_interface_objects));
	next_loop_2:
	next_loop_3:
	  first_1 = 
		  CAR(Queue_of_active_uninterruptable_gfi_output_interface_objects);
	  last_1 = 
		  CDR(Queue_of_active_uninterruptable_gfi_output_interface_objects);
	  next = CDR(first_1);
	  if ( !TRUEP(first_1)) {
	      gfi_output_frame = Nil;
	      goto end_2;
	  }
	  else if (EQ(first_1,
		  CAR(Queue_of_active_uninterruptable_gfi_output_interface_objects))) 
		      {
	      if (EQ(first_1,last_1))
		  CAS_CDR(Queue_of_active_uninterruptable_gfi_output_interface_objects,
			  last_1,next);
	      else {
		  gensymed_symbol = CAR(first_1);
		  if (CAS_CAR(Queue_of_active_uninterruptable_gfi_output_interface_objects,
			  first_1,next)) {
		      inline_note_reclaim_cons(first_1,Qgfi);
		      if (ISVREF(Available_gfi_conses_tail_vector,
			      IFIX(Current_thread_index))) {
			  temp = ISVREF(Available_gfi_conses_tail_vector,
				  IFIX(Current_thread_index));
			  M_CDR(temp) = first_1;
			  temp = Available_gfi_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp,svref_arg_2) = first_1;
		      }
		      else {
			  temp = Available_gfi_conses_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp,svref_arg_2) = first_1;
			  temp = Available_gfi_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp,svref_arg_2) = first_1;
		      }
		      M_CDR(first_1) = Nil;
		      gfi_output_frame = gensymed_symbol;
		      goto end_2;
		  }
	      }
	  }
	  goto next_loop_3;
	end_loop_2:
	  gfi_output_frame = Qnil;
	end_2:
	  if (gfi_output_frame) {
	      if ( 
		      !TRUEP(get_lookup_slot_value_given_default(gfi_output_frame,
		      Qgfi_output_file_stream,Nil)))
		  open_gfi_output_interface(gfi_output_frame);
	      if (get_lookup_slot_value_given_default(gfi_output_frame,
		      Qgfi_outputting_qm,Nil)) {
		  temp_1 = get_lookup_slot_value(gfi_output_frame,
			  Qgfi_output_file_format);
		  if (EQ(temp_1,Qnupec_snapshot) || EQ(temp_1,
			  Qnupec_snapshot_with_restart_time)) {
		      if (gfi_output_nupec_snapshot_values_periodically(gfi_output_frame,
			      Nil)) {
			  Suppress_warning_message_header_qm = T;
			  if ((SI_Long)2L <= IFIX(Warning_message_level))
			      give_warning_1(3,FIX((SI_Long)2L),
				      string_constant_58,gfi_output_frame);
			  Suppress_warning_message_header_qm = Nil;
			  close_gfi_output_interface(gfi_output_frame,T);
		      }
		  }
		  else if (EQ(temp_1,Qspreadsheet)) {
		      if (gfi_output_spreadsheet_values_periodically(gfi_output_frame,
			      Nil)) {
			  Suppress_warning_message_header_qm = T;
			  if ((SI_Long)2L <= IFIX(Warning_message_level)) {
			      temp_1 = gfi_output_frame;
			      give_warning_1(4,FIX((SI_Long)2L),
				      string_constant_59,temp_1,
				      get_lookup_slot_value_given_default(gfi_output_frame,
				      Qgfi_output_pathname_string_of_stream_qm,
				      Nil));
			  }
			  Suppress_warning_message_header_qm = Nil;
			  close_gfi_output_interface(gfi_output_frame,T);
		      }
		  }
		  else if (gfi_output_event_log_values_periodically(gfi_output_frame,
			  Nil)) {
		      Suppress_warning_message_header_qm = T;
		      if ((SI_Long)2L <= IFIX(Warning_message_level)) {
			  temp_1 = gfi_output_frame;
			  give_warning_1(4,FIX((SI_Long)2L),
				  string_constant_59,temp_1,
				  get_lookup_slot_value_given_default(gfi_output_frame,
				  Qgfi_output_pathname_string_of_stream_qm,
				  Nil));
		      }
		      Suppress_warning_message_header_qm = Nil;
		      close_gfi_output_interface(gfi_output_frame,T);
		  }
	      }
	  }
	  number_of_frames_so_far = FIXNUM_ADD1(number_of_frames_so_far);
	  if (FIXNUM_GE(number_of_frames_so_far,initial_number_of_frames))
	      goto end_loop_3;
	  goto next_loop_2;
	end_loop_3:;
      }
      if (CAR(Queue_of_active_gfi_input_interface_objects)) {
	  gfi_input_frame = Nil;
	  number_of_frames_so_far = FIX((SI_Long)0L);
	  initial_number_of_frames = 
		  length(CAR(Queue_of_active_gfi_input_interface_objects));
	next_loop_4:
	next_loop_5:
	  first_1 = CAR(Queue_of_active_gfi_input_interface_objects);
	  last_1 = CDR(Queue_of_active_gfi_input_interface_objects);
	  next = CDR(first_1);
	  if ( !TRUEP(first_1)) {
	      gfi_input_frame = Nil;
	      goto end_3;
	  }
	  else if (EQ(first_1,
		  CAR(Queue_of_active_gfi_input_interface_objects))) {
	      if (EQ(first_1,last_1))
		  CAS_CDR(Queue_of_active_gfi_input_interface_objects,
			  last_1,next);
	      else {
		  gensymed_symbol = CAR(first_1);
		  if (CAS_CAR(Queue_of_active_gfi_input_interface_objects,
			  first_1,next)) {
		      inline_note_reclaim_cons(first_1,Qgfi);
		      if (ISVREF(Available_gfi_conses_tail_vector,
			      IFIX(Current_thread_index))) {
			  temp = ISVREF(Available_gfi_conses_tail_vector,
				  IFIX(Current_thread_index));
			  M_CDR(temp) = first_1;
			  temp = Available_gfi_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp,svref_arg_2) = first_1;
		      }
		      else {
			  temp = Available_gfi_conses_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp,svref_arg_2) = first_1;
			  temp = Available_gfi_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp,svref_arg_2) = first_1;
		      }
		      M_CDR(first_1) = Nil;
		      gfi_input_frame = gensymed_symbol;
		      goto end_3;
		  }
	      }
	  }
	  goto next_loop_5;
	end_loop_4:
	  gfi_input_frame = Qnil;
	end_3:
	  if (gfi_input_frame) {
	      gensymed_symbol = gfi_input_frame;
	      new_cons = ISVREF(Available_gfi_conses_vector,
		      IFIX(Current_thread_index));
	      if (new_cons) {
		  temp = Available_gfi_conses_vector;
		  svref_arg_2 = Current_thread_index;
		  svref_new_value = M_CDR(new_cons);
		  SVREF(temp,svref_arg_2) = svref_new_value;
		  if ( !TRUEP(ISVREF(Available_gfi_conses_vector,
			  IFIX(Current_thread_index)))) {
		      temp = Available_gfi_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp,svref_arg_2) = Nil;
		  }
		  gensymed_symbol_1 = new_cons;
	      }
	      else
		  gensymed_symbol_1 = Nil;
	      if ( !TRUEP(gensymed_symbol_1))
		  gensymed_symbol_1 = replenish_gfi_cons_pool();
	      M_CAR(gensymed_symbol_1) = gensymed_symbol;
	      M_CDR(gensymed_symbol_1) = Nil;
	      inline_note_allocate_cons(gensymed_symbol_1,Qgfi);
	    next_loop_6:
	      first_1 = CAR(Queue_of_active_gfi_input_interface_objects);
	      last_1 = CDR(Queue_of_active_gfi_input_interface_objects);
	      temp_1 = CDR(Queue_of_active_gfi_input_interface_objects);
	      next = CDR(temp_1);
	      if ( !TRUEP(first_1)) {
		  if (CAS_CAR(Queue_of_active_gfi_input_interface_objects,
			  first_1,gensymed_symbol_1)) {
		      CAS_CDR(Queue_of_active_gfi_input_interface_objects,
			      last_1,gensymed_symbol_1);
		      goto end_4;
		  }
	      }
	      else if (EQ(last_1,
		      CDR(Queue_of_active_gfi_input_interface_objects))) {
		  if ( !TRUEP(next)) {
		      if (CAS_CDR(last_1,next,gensymed_symbol_1)) {
			  CAS_CDR(Queue_of_active_gfi_input_interface_objects,
				  last_1,gensymed_symbol_1);
			  goto end_4;
		      }
		  }
		  else
		      CAS_CDR(Queue_of_active_gfi_input_interface_objects,
			      last_1,next);
	      }
	      goto next_loop_6;
	    end_loop_5:
	    end_4:;
	      if ( 
		      !TRUEP(get_lookup_slot_value_given_default(gfi_input_frame,
		      Qgfi_input_file_stream,Nil)))
		  open_gfi_input_interface(gfi_input_frame);
	      if (get_lookup_slot_value_given_default(gfi_input_frame,
		      Qgfi_inputting_qm,Nil)) {
		  if (EQ(get_lookup_slot_value(gfi_input_frame,
			  Qgfi_input_file_format),Qnupec_snapshot)) {
		      temp_1 = gfi_input_frame;
		      if (gfi_input_nupec_snapshot_values_periodically(temp_1,
			      Nil,T,
			      get_lookup_slot_value_given_default(gfi_input_frame,
			      Qgfi_input_ignore_data_server_qm,Nil))) {
			  Suppress_warning_message_header_qm = T;
			  if ((SI_Long)2L <= IFIX(Warning_message_level))
			      give_warning_1(3,FIX((SI_Long)2L),
				      string_constant_56,gfi_input_frame);
			  Suppress_warning_message_header_qm = Nil;
			  close_gfi_input_interface(gfi_input_frame);
		      }
		  }
		  else if (EQ(get_lookup_slot_value(gfi_input_frame,
			  Qgfi_input_file_format),
			  Qnupec_snapshot_with_restart_time)) {
		      temp_1 = gfi_input_frame;
		      if (gfi_input_nupec_snapshot_values_periodically(temp_1,
			      T,T,
			      get_lookup_slot_value_given_default(gfi_input_frame,
			      Qgfi_input_ignore_data_server_qm,Nil))) {
			  Suppress_warning_message_header_qm = T;
			  if ((SI_Long)2L <= IFIX(Warning_message_level))
			      give_warning_1(3,FIX((SI_Long)2L),
				      string_constant_56,gfi_input_frame);
			  Suppress_warning_message_header_qm = Nil;
			  close_gfi_input_interface(gfi_input_frame);
		      }
		  }
		  else if (EQ(get_lookup_slot_value(gfi_input_frame,
			  Qgfi_input_variables_update_mode),
			  Qinput_one_shot_when_activated)) {
		      temp_1 = gfi_input_frame;
		      if (synchronize_gfi_input_file(temp_1,T,
			      get_lookup_slot_value_given_default(gfi_input_frame,
			      Qgfi_input_ignore_data_server_qm,Nil))) {
			  if (get_lookup_slot_value_given_default(gfi_input_frame,
				  Qgfi_inputting_qm,Nil)) {
			      Suppress_warning_message_header_qm = T;
			      if ((SI_Long)2L <= IFIX(Warning_message_level)) {
				  temp_1 = gfi_input_frame;
				  give_warning_1(4,FIX((SI_Long)2L),
					  string_constant_60,temp_1,
					  get_lookup_slot_value_given_default(gfi_input_frame,
					  Qgfi_input_pathname_string_of_stream_qm,
					  Nil));
			      }
			      Suppress_warning_message_header_qm = Nil;
			      close_gfi_input_interface(gfi_input_frame);
			  }
		      }
		  }
		  else {
		      temp_1 = gfi_input_frame;
		      if (synchronize_gfi_input_file(temp_1,T,
			      get_lookup_slot_value_given_default(gfi_input_frame,
			      Qgfi_input_ignore_data_server_qm,Nil))) {
			  gensymed_symbol = 
				  get_lookup_slot_value_given_default(gfi_input_frame,
				  Qgfi_queue_of_variables_that_need_values,
				  Nil);
			  temp_1 = CDR(gensymed_symbol);
			  gensymed_symbol_1 = CAR(temp_1);
			  gensymed_symbol_2 = Nil;
			next_loop_7:
			  if (CAR(gensymed_symbol)) {
			      temp_1 = CAR(gensymed_symbol);
			      temp_2 =  !EQ(gensymed_symbol_1,CAR(temp_1));
			  }
			  else
			      temp_2 = TRUEP(Nil);
			  if ( !temp_2)
			      goto end_loop_6;
			next_loop_8:
			  first_1 = CAR(gensymed_symbol);
			  last_1 = CDR(gensymed_symbol);
			  next = CDR(first_1);
			  if ( !TRUEP(first_1)) {
			      gensymed_symbol_2 = Nil;
			      goto end_5;
			  }
			  else if (EQ(first_1,CAR(gensymed_symbol))) {
			      if (EQ(first_1,last_1))
				  CAS_CDR(gensymed_symbol,last_1,next);
			      else {
				  gensymed_symbol_2 = CAR(first_1);
				  if (CAS_CAR(gensymed_symbol,first_1,next)) {
				      inline_note_reclaim_cons(first_1,Qgfi);
				      if (ISVREF(Available_gfi_conses_tail_vector,
					      IFIX(Current_thread_index))) {
					  temp = 
						  ISVREF(Available_gfi_conses_tail_vector,
						  IFIX(Current_thread_index));
					  M_CDR(temp) = first_1;
					  temp = 
						  Available_gfi_conses_tail_vector;
					  svref_arg_2 = Current_thread_index;
					  SVREF(temp,svref_arg_2) = first_1;
				      }
				      else {
					  temp = Available_gfi_conses_vector;
					  svref_arg_2 = Current_thread_index;
					  SVREF(temp,svref_arg_2) = first_1;
					  temp = 
						  Available_gfi_conses_tail_vector;
					  svref_arg_2 = Current_thread_index;
					  SVREF(temp,svref_arg_2) = first_1;
				      }
				      M_CDR(first_1) = Nil;
				      goto end_5;
				  }
			      }
			  }
			  goto next_loop_8;
			end_loop_7:
			  gensymed_symbol_2 = Qnil;
			end_5:
			  svref_new_value_1 = 
				  IFIX(ISVREF(gensymed_symbol_2,
				  (SI_Long)5L)) &  ~(SI_Long)4096L;
			  ISVREF(gensymed_symbol_2,(SI_Long)5L) = 
				  FIX(svref_new_value_1);
			  collect_one_shot_data_for_gfi_data_service(gensymed_symbol_2);
			  Time_slice_expired_p = time_slice_expired_p();
			  if (Time_slice_expired_p)
			      goto end_loop_6;
			  goto next_loop_7;
			end_loop_6:;
		      }
		  }
	      }
	  }
	  number_of_frames_so_far = FIXNUM_ADD1(number_of_frames_so_far);
	  if (FIXNUM_GE(number_of_frames_so_far,initial_number_of_frames) 
		  || Time_slice_expired_p)
	      goto end_loop_8;
	  goto next_loop_4;
	end_loop_8:;
      }
      if (CAR(Queue_of_active_gfi_output_interface_objects)) {
	  gfi_output_frame = Nil;
	  number_of_frames_so_far = FIX((SI_Long)0L);
	  initial_number_of_frames = 
		  length(CAR(Queue_of_active_gfi_output_interface_objects));
	next_loop_9:
	next_loop_10:
	  first_1 = CAR(Queue_of_active_gfi_output_interface_objects);
	  last_1 = CDR(Queue_of_active_gfi_output_interface_objects);
	  next = CDR(first_1);
	  if ( !TRUEP(first_1)) {
	      gfi_output_frame = Nil;
	      goto end_6;
	  }
	  else if (EQ(first_1,
		  CAR(Queue_of_active_gfi_output_interface_objects))) {
	      if (EQ(first_1,last_1))
		  CAS_CDR(Queue_of_active_gfi_output_interface_objects,
			  last_1,next);
	      else {
		  gensymed_symbol = CAR(first_1);
		  if (CAS_CAR(Queue_of_active_gfi_output_interface_objects,
			  first_1,next)) {
		      inline_note_reclaim_cons(first_1,Qgfi);
		      if (ISVREF(Available_gfi_conses_tail_vector,
			      IFIX(Current_thread_index))) {
			  temp = ISVREF(Available_gfi_conses_tail_vector,
				  IFIX(Current_thread_index));
			  M_CDR(temp) = first_1;
			  temp = Available_gfi_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp,svref_arg_2) = first_1;
		      }
		      else {
			  temp = Available_gfi_conses_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp,svref_arg_2) = first_1;
			  temp = Available_gfi_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp,svref_arg_2) = first_1;
		      }
		      M_CDR(first_1) = Nil;
		      gfi_output_frame = gensymed_symbol;
		      goto end_6;
		  }
	      }
	  }
	  goto next_loop_10;
	end_loop_9:
	  gfi_output_frame = Qnil;
	end_6:
	  if (gfi_output_frame) {
	      gensymed_symbol = gfi_output_frame;
	      new_cons = ISVREF(Available_gfi_conses_vector,
		      IFIX(Current_thread_index));
	      if (new_cons) {
		  temp = Available_gfi_conses_vector;
		  svref_arg_2 = Current_thread_index;
		  svref_new_value = M_CDR(new_cons);
		  SVREF(temp,svref_arg_2) = svref_new_value;
		  if ( !TRUEP(ISVREF(Available_gfi_conses_vector,
			  IFIX(Current_thread_index)))) {
		      temp = Available_gfi_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp,svref_arg_2) = Nil;
		  }
		  gensymed_symbol_1 = new_cons;
	      }
	      else
		  gensymed_symbol_1 = Nil;
	      if ( !TRUEP(gensymed_symbol_1))
		  gensymed_symbol_1 = replenish_gfi_cons_pool();
	      M_CAR(gensymed_symbol_1) = gensymed_symbol;
	      M_CDR(gensymed_symbol_1) = Nil;
	      inline_note_allocate_cons(gensymed_symbol_1,Qgfi);
	    next_loop_11:
	      first_1 = CAR(Queue_of_active_gfi_output_interface_objects);
	      last_1 = CDR(Queue_of_active_gfi_output_interface_objects);
	      temp_1 = CDR(Queue_of_active_gfi_output_interface_objects);
	      next = CDR(temp_1);
	      if ( !TRUEP(first_1)) {
		  if (CAS_CAR(Queue_of_active_gfi_output_interface_objects,
			  first_1,gensymed_symbol_1)) {
		      CAS_CDR(Queue_of_active_gfi_output_interface_objects,
			      last_1,gensymed_symbol_1);
		      goto end_7;
		  }
	      }
	      else if (EQ(last_1,
		      CDR(Queue_of_active_gfi_output_interface_objects))) {
		  if ( !TRUEP(next)) {
		      if (CAS_CDR(last_1,next,gensymed_symbol_1)) {
			  CAS_CDR(Queue_of_active_gfi_output_interface_objects,
				  last_1,gensymed_symbol_1);
			  goto end_7;
		      }
		  }
		  else
		      CAS_CDR(Queue_of_active_gfi_output_interface_objects,
			      last_1,next);
	      }
	      goto next_loop_11;
	    end_loop_10:
	    end_7:;
	      if ( 
		      !TRUEP(get_lookup_slot_value_given_default(gfi_output_frame,
		      Qgfi_output_file_stream,Nil)))
		  open_gfi_output_interface(gfi_output_frame);
	      if (get_lookup_slot_value_given_default(gfi_output_frame,
		      Qgfi_outputting_qm,Nil)) {
		  if (get_lookup_slot_value_given_default(gfi_output_frame,
			  Qnew_gfi_output_values_this_cycle_qm,Nil))
		      Time_slice_expired_p =  
			      !TRUEP(output_gfi_queued_values_to_stream(gfi_output_frame,
			      Nil)) ? T : Nil;
		  else if (EQ(get_lookup_slot_value(gfi_output_frame,
			  Qgfi_output_file_format),Qnupec_snapshot) || 
			  EQ(get_lookup_slot_value(gfi_output_frame,
			  Qgfi_output_file_format),
			  Qnupec_snapshot_with_restart_time)) {
		      if (gfi_output_nupec_snapshot_values_periodically(gfi_output_frame,
			      T)) {
			  Suppress_warning_message_header_qm = T;
			  if ((SI_Long)2L <= IFIX(Warning_message_level))
			      give_warning_1(3,FIX((SI_Long)2L),
				      string_constant_58,gfi_output_frame);
			  Suppress_warning_message_header_qm = Nil;
			  close_gfi_output_interface(gfi_output_frame,T);
		      }
		  }
		  else if (EQ(get_lookup_slot_value(gfi_output_frame,
			  Qgfi_output_file_update_frequency),
			  Qoutput_one_shot_when_activated)) {
		      if (EQ(get_lookup_slot_value(gfi_output_frame,
			      Qgfi_output_file_format),Qspreadsheet)) {
			  if (gfi_output_spreadsheet_values_periodically(gfi_output_frame,
				  T)) {
			      Suppress_warning_message_header_qm = T;
			      if ((SI_Long)2L <= IFIX(Warning_message_level)) {
				  temp_1 = gfi_output_frame;
				  give_warning_1(4,FIX((SI_Long)2L),
					  string_constant_59,temp_1,
					  get_lookup_slot_value_given_default(gfi_output_frame,
					  Qgfi_output_pathname_string_of_stream_qm,
					  Nil));
			      }
			      Suppress_warning_message_header_qm = Nil;
			      close_gfi_output_interface(gfi_output_frame,T);
			  }
		      }
		      else if (gfi_output_event_log_values_periodically(gfi_output_frame,
			      T)) {
			  Suppress_warning_message_header_qm = T;
			  if ((SI_Long)2L <= IFIX(Warning_message_level)) {
			      temp_1 = gfi_output_frame;
			      give_warning_1(4,FIX((SI_Long)2L),
				      string_constant_59,temp_1,
				      get_lookup_slot_value_given_default(gfi_output_frame,
				      Qgfi_output_pathname_string_of_stream_qm,
				      Nil));
			  }
			  Suppress_warning_message_header_qm = Nil;
			  close_gfi_output_interface(gfi_output_frame,T);
		      }
		  }
	      }
	  }
	  number_of_frames_so_far = FIXNUM_ADD1(number_of_frames_so_far);
	  if (FIXNUM_GE(number_of_frames_so_far,initial_number_of_frames) 
		  || Time_slice_expired_p)
	      goto end_loop_11;
	  goto next_loop_9;
	end_loop_11:;
      }
      result = VALUES_1( !TRUEP(Time_slice_expired_p) ? T : Nil);
    POP_SPECIAL();
    return result;
}

/* GFI-REQUESTS-ACCEPT-DATA-CALLS */
Object gfi_requests_accept_data_calls()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, input, ab_loop_it_;
    Object temp_1, output;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(217,113);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    input = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loop_it_ = Nil;
      ab_loopvar_ = collect_subclasses(Qgfi_input_interface);
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
      input = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      ab_loop_it_ = (SI_Long)0L != (IFIX(ISVREF(input,(SI_Long)5L)) & 
	      (SI_Long)1L) ? get_lookup_slot_value(input,
	      Qgfi_input_when_active) : Qnil;
      if (ab_loop_it_) {
	  temp_1 = ab_loop_it_;
	  goto end_1;
      }
      goto next_loop;
    end_loop_1:
      temp_1 = Qnil;
    end_1:;
    POP_SPECIAL();
    if (temp_1)
	return VALUES_1(temp_1);
    else {
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	output = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  ab_loop_it_ = Nil;
	  ab_loopvar_ = collect_subclasses(Qgfi_output_interface);
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
	      temp =  !TRUEP(ab_loopvar__1);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp)
	      goto end_loop_3;
	  output = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  ab_loop_it_ = (SI_Long)0L != (IFIX(ISVREF(output,(SI_Long)5L)) & 
		  (SI_Long)1L) ? get_lookup_slot_value(output,
		  Qgfi_output_when_active) : Qnil;
	  if (ab_loop_it_) {
	      result = VALUES_1(ab_loop_it_);
	      goto end_2;
	  }
	  goto next_loop_2;
	end_loop_3:
	  result = VALUES_1(Qnil);
	end_2:;
	POP_SPECIAL();
	return result;
    }
}

/* INITIALIZE-GFI-DATA-SERVER */
Object initialize_gfi_data_server()
{
    Object svref_arg_1;

    x_note_fn_call(217,114);
    svref_arg_1 = lookup_kb_specific_property_value(Qgfi_data_server,
	    Data_server_kbprop);
    SVREF(svref_arg_1,FIX((SI_Long)6L)) = T;
    return VALUES_1(Nil);
}

static Object string_constant_61;  /* "An attempt was made to set the external value of the variable ~NF, ~
				    *      which gets data service through the GFI Data Server, to the value ~
				    *      ~NV.  The set operation is not allowed within this data server."
				    */

/* SET-EXTERNAL-VARIABLE-FOR-GFI */
Object set_external_variable_for_gfi(variable,value,data_type)
    Object variable, value, data_type;
{
    x_note_fn_call(217,115);
    Suppress_warning_message_header_qm = T;
    if ((SI_Long)2L <= IFIX(Warning_message_level))
	give_warning_1(5,FIX((SI_Long)2L),string_constant_61,variable,
		value,data_type);
    Suppress_warning_message_header_qm = Nil;
    return VALUES_1(Suppress_warning_message_header_qm);
}

/* SHUT-DOWN-GFI-DATA-SERVER */
Object shut_down_gfi_data_server()
{
    Object svref_arg_1;

    x_note_fn_call(217,116);
    svref_arg_1 = lookup_kb_specific_property_value(Qgfi_data_server,
	    Data_server_kbprop);
    SVREF(svref_arg_1,FIX((SI_Long)6L)) = Nil;
    return VALUES_1(Nil);
}

/* GFI-OUTPUT-NUPEC-SNAPSHOT-VALUES-PERIODICALLY */
Object gfi_output_nupec_snapshot_values_periodically(gfi_output_frame,
	    do_not_override_time_slice_p)
    Object gfi_output_frame, do_not_override_time_slice_p;
{
    Object current_computation_frame, time_slice_expired_p_1, output_stream;
    Object output_limit_qm, number_of_designations_already_handled, temp;
    Object temp_1, designation_list, designation, not_unique_designation_p;
    Object ab_loop_list_, unique_designation_p_1;
    Object eval_list_of_designation_values, designation_qm, variable;
    Object ab_loop_list__1, sub_class_bit_vector, x2;
    SI_Long value_count, superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    char temp_2;
    Declare_special(2);
    Object result;

    x_note_fn_call(217,117);
    if (get_lookup_slot_value_given_default(gfi_output_frame,
	    Qgfi_outputting_qm,Nil)) {
	current_computation_frame = gfi_output_frame;
	time_slice_expired_p_1 = Nil;
	output_stream = 
		get_lookup_slot_value_given_default(gfi_output_frame,
		Qgfi_output_file_stream,Nil);
	output_limit_qm = get_lookup_slot_value(gfi_output_frame,
		Qmaximum_number_of_output_lines);
	number_of_designations_already_handled = 
		get_lookup_slot_value_given_default(gfi_output_frame,
		Qnumber_of_periodic_specified_designation_handled,Nil);
	if (number_of_designations_already_handled);
	else
	    number_of_designations_already_handled = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Time_slice_expired_p,Qtime_slice_expired_p,time_slice_expired_p_1,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		  0);
	    if (output_stream) {
		temp = number_of_designations_already_handled;
		temp_1 = 
			get_lookup_slot_value_given_default(gfi_output_frame,
			Qgfi_output_values,Nil);
		designation_list = nthcdr(temp,CAR(temp_1));
		designation = Nil;
		not_unique_designation_p = Nil;
		ab_loop_list_ = 
			get_lookup_slot_value_given_default(gfi_output_frame,
			Qgfi_output_not_unique_designation_p_results,Nil);
		unique_designation_p_1 = Nil;
		value_count = (SI_Long)0L;
	      next_loop:
		if ( !TRUEP(designation_list))
		    goto end_loop;
		designation = CAR(designation_list);
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		not_unique_designation_p = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		unique_designation_p_1 =  !TRUEP(not_unique_designation_p) 
			? T : Nil;
		value_count = value_count + (SI_Long)1L;
		if (output_limit_qm && FIXNUM_LE(output_limit_qm,
			get_lookup_slot_value_given_default(gfi_output_frame,
			Qnumber_of_lines_output_so_far,Nil)))
		    warning_message_for_limit_reached_in_gfi_output(gfi_output_frame);
		else {
		    eval_list_of_designation_values = 
			    serve_eval_list_of_designation_values(designation);
		    if (eval_list_of_designation_values) {
			designation_qm = Nil;
			variable = Nil;
			ab_loop_list__1 = eval_list_of_designation_values;
		      next_loop_1:
			if ( !TRUEP(ab_loop_list__1))
			    goto end_loop_1;
			variable = M_CAR(ab_loop_list__1);
			ab_loop_list__1 = M_CDR(ab_loop_list__1);
			if (output_limit_qm && FIXNUM_LE(output_limit_qm,
				get_lookup_slot_value_given_default(gfi_output_frame,
				Qnumber_of_lines_output_so_far,Nil)))
			    goto end_loop_1;
			if (unique_designation_p_1)
			    designation_qm = 
				    copy_tree_using_eval_conses_1(designation);
			else if (SIMPLE_VECTOR_P(variable) && 
				EQ(ISVREF(variable,(SI_Long)0L),
				Qg2_defstruct_structure_name_temporary_constant_g2_struct))
			    designation_qm = Nil;
			else
			    designation_qm = 
				    generate_designation_for_block(variable);
			if (designation_qm) {
			    if ( !(SIMPLE_VECTOR_P(variable) && 
				    EQ(ISVREF(variable,(SI_Long)0L),
				    Qg2_defstruct_structure_name_temporary_constant_g2_struct))) 
					{
				sub_class_bit_vector = 
					ISVREF(ISVREF(variable,
					(SI_Long)1L),(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(Variable_or_parameter_class_description,
					(SI_Long)18L));
				sub_class_vector_index = 
					superior_class_bit_number >>  -  - 
					(SI_Long)3L;
				if (sub_class_vector_index < 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					    {
				    gensymed_symbol = 
					    UBYTE_8_ISAREF_1(sub_class_bit_vector,
					    sub_class_vector_index);
				    gensymed_symbol_1 = (SI_Long)1L;
				    gensymed_symbol_2 = 
					    superior_class_bit_number & 
					    (SI_Long)7L;
				    gensymed_symbol_1 = gensymed_symbol_1 
					    << gensymed_symbol_2;
				    gensymed_symbol = gensymed_symbol & 
					    gensymed_symbol_1;
				    temp_2 = (SI_Long)0L < gensymed_symbol;
				}
				else
				    temp_2 = TRUEP(Nil);
			    }
			    else
				temp_2 = TRUEP(Nil);
			    if (temp_2)
				write_gfi_nupec_snapshot_variable_state(variable,
					gfi_output_frame);
			    else {
				reclaim_if_temporary_constant_function(variable);
				warning_message_for_wrong_reference_for_gfi_designation(gfi_output_frame,
					designation_qm,variable);
			    }
			}
			else {
			    if (SIMPLE_VECTOR_P(variable) && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(variable)) 
				    > (SI_Long)2L &&  !EQ(ISVREF(variable,
				    (SI_Long)1L),Qavailable_frame_vector)) {
				x2 = ISVREF(variable,(SI_Long)1L);
				temp_2 = SIMPLE_VECTOR_P(x2) && 
					EQ(ISVREF(x2,(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					? TRUEP(x2) : TRUEP(Qnil);
			    }
			    else
				temp_2 = TRUEP(Nil);
			    if ( !temp_2)
				warning_message_for_non_frame_reference_for_gfi_designation(gfi_output_frame,
					variable);
			    else
				warning_message_for_unnameable_variable(gfi_output_frame,
					variable,Nil);
			}
			if (unique_designation_p_1)
			    reclaim_eval_tree_1(designation_qm);
			goto next_loop_1;
		      end_loop_1:
			reclaim_eval_tree_1(eval_list_of_designation_values);
		    }
		    else
			warning_message_for_wrong_reference_for_gfi_designation(gfi_output_frame,
				designation,Nil);
		}
		if (do_not_override_time_slice_p) {
		    Time_slice_expired_p = time_slice_expired_p();
		    temp_2 = TRUEP(Time_slice_expired_p);
		}
		else
		    temp_2 = TRUEP(Nil);
		if (temp_2)
		    goto end_loop;
		designation_list = M_CDR(designation_list);
		goto next_loop;
	      end_loop:
		number_of_designations_already_handled =  
			!TRUEP(CDR(designation_list)) ? FIX((SI_Long)0L) : 
			FIX(IFIX(number_of_designations_already_handled) + 
			value_count);
		if (do_not_override_time_slice_p && Time_slice_expired_p) {
		    set_non_savable_lookup_slot_value(gfi_output_frame,
			    Qnumber_of_periodic_specified_designation_handled,
			    number_of_designations_already_handled);
		    result = VALUES_1(Nil);
		}
		else {
		    set_non_savable_lookup_slot_value(gfi_output_frame,
			    Qnumber_of_periodic_specified_designation_handled,
			    FIX((SI_Long)0L));
		    result = VALUES_1(T);
		}
	    }
	    else
		result = VALUES_1(Nil);
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

static Object Qnever;              /* never */

static Object array_constant_9;    /* # */

static Object array_constant_10;   /* # */

/* WRITE-GFI-NUPEC-SNAPSHOT-VARIABLE-STATE */
Object write_gfi_nupec_snapshot_variable_state(variable,gfi_output_frame)
    Object variable, gfi_output_frame;
{
    Object designation_qm, history_qm, data_type, oldest_index_qm;
    Object newest_index_qm, history_count, ring_buffer, index_1;
    Object oldest_active_element_index_for_ring_buffer, current_value;
    Object collection_time, expiration_time, sub_class_bit_vector, temp_1;
    Object number_of_lines_output_so_far_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(217,118);
    designation_qm = generate_designation_for_block(variable);
    history_qm = ISVREF(variable,(SI_Long)24L);
    data_type = ISVREF(variable,(SI_Long)20L);
    oldest_index_qm = Nil;
    newest_index_qm = Nil;
    history_count = FIX((SI_Long)0L);
    if (history_qm &&  !TRUEP(cascaded_ring_buffer_empty_qm(history_qm))) {
	oldest_index_qm = 
		get_oldest_active_element_index_for_cascaded_ring_buffer(history_qm);
	newest_index_qm = 
		get_newest_active_element_index_for_cascaded_ring_buffer(history_qm);
	ring_buffer = CAR(oldest_index_qm);
	index_1 = ISVREF(ring_buffer,(SI_Long)1L);
	oldest_active_element_index_for_ring_buffer = ISVREF(ring_buffer,
		(SI_Long)2L);
	history_count = FIXNUM_GE(index_1,
		oldest_active_element_index_for_ring_buffer) ? 
		FIXNUM_ADD1(FIXNUM_MINUS(index_1,
		oldest_active_element_index_for_ring_buffer)) : 
		FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(index_1,
		ISVREF(ring_buffer,(SI_Long)4L)),
		oldest_active_element_index_for_ring_buffer));
    }
    write_designation_to_stream(designation_qm,gfi_output_frame);
    gfi_write_char(Gfi_delimitter,gfi_output_frame);
    reclaim_eval_tree_1(designation_qm);
    output_gfi_value(history_count,Qnumber,gfi_output_frame);
    gfi_write_char(Gfi_delimitter,gfi_output_frame);
    current_value = ISVREF(variable,(SI_Long)23L);
    collection_time = ISVREF(variable,(SI_Long)21L);
    expiration_time = Nil;
    sub_class_bit_vector = ISVREF(ISVREF(variable,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Parameter_class_description,
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
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(current_value) != (SI_Long)0L 
		    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_value)) == 
		    (SI_Long)1L)
		temp_1 = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(current_value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(current_value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_value)) == 
		    (SI_Long)1L)
		temp_1 = aref1(current_value,FIX((SI_Long)0L));
	    else
		temp_1 = current_value;
	    output_gfi_value(temp_1,data_type,gfi_output_frame);
	}
	POP_LOCAL_ALLOCATION(0,0);
	gfi_write_char(Gfi_delimitter,gfi_output_frame);
	output_appropriate_gfi_time_stamp(gfi_output_frame,collection_time);
    }
    else {
	expiration_time = ISVREF(variable,(SI_Long)26L);
	if ( !EQ(expiration_time,Qnever) && FIXNUM_EQ(expiration_time,
		Some_time_ago)) {
	    output_appropriate_nupec_gfi_default_value(data_type,
		    gfi_output_frame);
	    gfi_write_char(Gfi_delimitter,gfi_output_frame);
	    output_appropriate_nupec_gfi_default_time_stamp(gfi_output_frame);
	    gfi_write_char(Gfi_delimitter,gfi_output_frame);
	    gfi_write_string(array_constant_9,gfi_output_frame);
	}
	else {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(current_value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_value)) == 
			(SI_Long)1L)
		    temp_1 = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(current_value,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(current_value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_value)) == 
			(SI_Long)1L)
		    temp_1 = aref1(current_value,FIX((SI_Long)0L));
		else
		    temp_1 = current_value;
		output_gfi_value(temp_1,data_type,gfi_output_frame);
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	    gfi_write_char(Gfi_delimitter,gfi_output_frame);
	    output_appropriate_gfi_time_stamp(gfi_output_frame,
		    collection_time);
	    gfi_write_char(Gfi_delimitter,gfi_output_frame);
	    if (EQ(expiration_time,Qnever))
		gfi_write_string(array_constant_10,gfi_output_frame);
	    else {
		if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
		    output_appropriate_gfi_time_stamp(gfi_output_frame,
			    DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(FIXNUM_MINUS(expiration_time,
			    Gensym_time_at_start)) + 
			    DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L)));
		POP_LOCAL_ALLOCATION(0,0);
	    }
	}
    }
    gfi_terpri(gfi_output_frame);
    number_of_lines_output_so_far_new_value = 
	    FIXNUM_ADD1(get_lookup_slot_value_given_default(gfi_output_frame,
	    Qnumber_of_lines_output_so_far,Nil));
    set_non_savable_lookup_slot_value(gfi_output_frame,
	    Qnumber_of_lines_output_so_far,
	    number_of_lines_output_so_far_new_value);
    if (IFIX(history_count) > (SI_Long)0L) {
      next_loop:
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    gfi_write_char(Gfi_delimitter,gfi_output_frame);
	    output_appropriate_gfi_time_stamp(gfi_output_frame,
		    get_history_g2_time(2,history_qm,CDR(oldest_index_qm)));
	    gfi_write_char(Gfi_delimitter,gfi_output_frame);
	    output_gfi_value(get_history_value_for_cascaded_ring_buffer(history_qm,
		    oldest_index_qm),data_type,gfi_output_frame);
	}
	POP_LOCAL_ALLOCATION(0,0);
	gfi_terpri(gfi_output_frame);
	number_of_lines_output_so_far_new_value = 
		FIXNUM_ADD1(get_lookup_slot_value_given_default(gfi_output_frame,
		Qnumber_of_lines_output_so_far,Nil));
	set_non_savable_lookup_slot_value(gfi_output_frame,
		Qnumber_of_lines_output_so_far,
		number_of_lines_output_so_far_new_value);
	if (cascaded_ring_buffer_indices_same_p(oldest_index_qm,
		newest_index_qm))
	    goto end_loop;
	increment_active_element_index_for_cascaded_ring_buffer(oldest_index_qm,
		history_qm);
	goto next_loop;
      end_loop:
	reclaim_history_cons_1(oldest_index_qm);
	reclaim_history_cons_1(newest_index_qm);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qg2;                 /* g2 */

/* OUTPUT-APPROPRIATE-NUPEC-GFI-DEFAULT-VALUE */
Object output_appropriate_nupec_gfi_default_value(data_type,gfi_output_frame)
    Object data_type, gfi_output_frame;
{
    Object default_value_qm, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object output_value, temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(217,119);
    if (EQ(data_type,Qinteger))
	default_value_qm = FIX((SI_Long)0L);
    else if (EQ(data_type,Qnumber) || EQ(data_type,Qinteger) || 
	    EQ(data_type,Qfloat) || EQ(data_type,Qlong) || 
	    lookup_global_or_kb_specific_property_value(data_type,
	    Numeric_data_type_gkbprop))
	default_value_qm = float_constant;
    else if (EQ(data_type,Qtruth_value))
	default_value_qm = Falsity;
    else if (EQ(data_type,Qsymbol))
	default_value_qm = Qg2;
    else if (EQ(data_type,Qtext))
	default_value_qm = array_constant;
    else
	default_value_qm = Nil;
    if (default_value_qm) {
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
		  print_constant(2,default_value_qm,data_type);
		  output_value = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = gfi_write_string(output_value,gfi_output_frame);
	reclaim_text_string(output_value);
	return VALUES_1(temp);
    }
    else
	return VALUES_1(Nil);
}

/* OUTPUT-APPROPRIATE-NUPEC-GFI-DEFAULT-TIME-STAMP */
Object output_appropriate_nupec_gfi_default_time_stamp(gfi_output_frame)
    Object gfi_output_frame;
{
    x_note_fn_call(217,120);
    return output_appropriate_gfi_time_stamp(gfi_output_frame,
	    get_lookup_slot_value_given_default(gfi_output_frame,
	    Qgfi_output_base_time,Nil));
}

static Object string_constant_62;  /* "NUPEC Snapshot input has been stopped!  Error ~
				    *                              while resetting the G2 time to the NUPEC snapshot ~
				    *                              time."
				    */

static Object array_constant_11;   /* # */

static Object string_constant_63;  /* "  The snapshot time is too far into the past.  ~
				    *                                 This value cannot be represented internally as ~
				    *                                 an integer."
				    */

static Object string_constant_64;  /* "NUPEC Snapshot input has been stopped!" */

static Object Qgraph;              /* graph */

/* GFI-INPUT-NUPEC-SNAPSHOT-VALUES-PERIODICALLY */
Object gfi_input_nupec_snapshot_values_periodically(gfi_input_frame,
	    reset_time_qm,do_not_override_time_slice_p,
	    no_data_service_required_qm)
    Object gfi_input_frame, reset_time_qm, do_not_override_time_slice_p;
    Object no_data_service_required_qm;
{
    Object current_computation_frame, base_time, gensym_base_time;
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_1, scope_conses, ab_loopvar_, ab_loopvar__1, graph;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    double gensymed_symbol, arg, arg_1;
    Declare_special(8);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(217,121);
    current_computation_frame = gfi_input_frame;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    7);
      if (reset_time_qm) {
	  if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	      base_time = 
		      get_lookup_slot_value_given_default(gfi_input_frame,
		      Qgfi_input_base_time,Nil);
	      if (base_time) {
		  gensymed_symbol = DFLOAT_ISAREF_1(base_time,(SI_Long)0L) 
			  - DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L) 
			  + (double)IFIX(Gensym_time_at_start);
		  arg = gensymed_symbol;
		  arg_1 = 
			  DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum_as_float);
		  temp = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?
			    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		  if (temp);
		  else {
		      arg = gensymed_symbol;
		      arg_1 = 
			      DOUBLE_FLOAT_TO_DOUBLE(Most_negative_fixnum_as_float);
		      temp = arg < arg_1 &&  
			      !inline_nanp_for_comparison(arg) ?  
			      !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		  }
		  gensym_base_time = temp ? Most_negative_fixnum : 
			  LONG_TO_FIXNUM(inline_floor_1(gensymed_symbol));
	      }
	      else
		  gensym_base_time = Nil;
	      if (gensym_base_time && FIXNUMP(gensym_base_time) && 
		      FIXNUM_LE(gensym_base_time,Gensym_time)) {
		  change_current_time_in_nupec_catch_up_mode(gensym_base_time);
		  temp = TRUEP(T);
	      }
	      else {
		  if ((SI_Long)2L <= IFIX(Warning_message_level) &&  
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
				    write_warning_message_header(FIX((SI_Long)2L));
				    tformat(1,string_constant_62);
				    if ( !NUM_LE(gensym_base_time,Gensym_time))
					twrite_beginning_of_wide_string(array_constant_11,
						FIX((SI_Long)41L));
				    else if ( !FIXNUMP(gensym_base_time))
					tformat(1,string_constant_63);
				    temp_1 = copy_out_current_wide_string();
				  POP_SPECIAL();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			  notify_user_1(temp_1);
			  if (Snapshots_of_related_blocks) {
			      reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
			      Snapshots_of_related_blocks = Nil;
			  }
			POP_SPECIAL();
		      POP_SPECIAL();
		  }
		  close_gfi_input_interface(gfi_input_frame);
		  set_non_savable_lookup_slot_value(gfi_input_frame,
			  Qgfi_input_file_synchronized_qm,Nil);
		  temp = TRUEP(Nil);
	      }
	  }
	  POP_LOCAL_ALLOCATION(0,0);
	  temp =  !temp;
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  result = VALUES_1(Nil);
      else {
	next_loop:
	  if (text_string_p(parse_and_put_gfi_nupec_snapshot_values(gfi_input_frame,
		  reset_time_qm,no_data_service_required_qm))) {
	      Suppress_warning_message_header_qm = T;
	      if ((SI_Long)2L <= IFIX(Warning_message_level))
		  give_warning_1(2,FIX((SI_Long)2L),string_constant_64);
	      Suppress_warning_message_header_qm = Nil;
	      close_gfi_input_interface(gfi_input_frame);
	      set_non_savable_lookup_slot_value(gfi_input_frame,
		      Qgfi_input_file_synchronized_qm,Nil);
	      result = VALUES_1(Nil);
	      goto end_1;
	  }
	  temp =  !TRUEP(read_one_gfi_input_line(gfi_input_frame));
	  if (temp);
	  else if (do_not_override_time_slice_p) {
	      Time_slice_expired_p = time_slice_expired_p();
	      temp = TRUEP(Time_slice_expired_p);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp)
	      goto end_loop;
	  goto next_loop;
	end_loop:
	  set_non_savable_lookup_slot_value(gfi_input_frame,
		  Qgfi_input_file_synchronized_qm, 
		  !TRUEP(Time_slice_expired_p) ? T : Nil);
	  if ( !TRUEP(Time_slice_expired_p)) {
	      scope_conses = Scope_conses;
	      ab_loopvar_ = Nil;
	      ab_loopvar__1 = Nil;
	      graph = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		      0);
		ab_loopvar_ = collect_subclasses(Qgraph);
	      next_loop_1:
		if ( !TRUEP(ab_loopvar__1)) {
		  next_loop_2:
		    if ( !TRUEP(ab_loopvar_))
			goto end_loop_1;
		    ab_loopvar__1 = 
			    lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			    Instances_specific_to_this_class_kbprop);
		    ab_loopvar_ = M_CDR(ab_loopvar_);
		    if (ab_loopvar__1)
			goto end_loop_1;
		    goto next_loop_2;
		  end_loop_1:
		    temp =  !TRUEP(ab_loopvar__1);
		}
		else
		    temp = TRUEP(Nil);
		if (temp)
		    goto end_loop_2;
		graph = ab_loopvar__1;
		ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
		if ((SI_Long)0L != (IFIX(ISVREF(graph,(SI_Long)5L)) & 
			(SI_Long)1L)) {
		    gensymed_symbol_1 = ISVREF(ISVREF(ISVREF(ISVREF(graph,
			    (SI_Long)1L),(SI_Long)11L),(SI_Long)31L),
			    (SI_Long)1L);
		    gensymed_symbol_2 = graph;
		    gensymed_symbol_3 = Nil;
		    inline_funcall_2(gensymed_symbol_1,gensymed_symbol_2,
			    gensymed_symbol_3);
		    gensymed_symbol_1 = ISVREF(ISVREF(ISVREF(ISVREF(graph,
			    (SI_Long)1L),(SI_Long)11L),(SI_Long)30L),
			    (SI_Long)1L);
		    gensymed_symbol_2 = graph;
		    inline_funcall_1(gensymed_symbol_1,gensymed_symbol_2);
		}
		goto next_loop_1;
	      end_loop_2:;
	      POP_SPECIAL();
	  }
	  result = VALUES_1( !TRUEP(Time_slice_expired_p) ? T : Nil);
	  goto end_1;
	  result = VALUES_1(Qnil);
	end_1:;
      }
    POP_SPECIAL();
    return result;
}

static Object string_constant_65;  /* "Error while reading the snapshot file ~S for the GFI input ~
				    *           object ~NF.  A variable or parameter reference is missing."
				    */

static Object string_constant_66;  /* "Error while reading the snapshot file ~S for the GFI input ~
				    *              object ~NF.  The variable or parameter ~ND does not exist."
				    */

static Object string_constant_67;  /* "Error while reading the snapshot file ~S for the GFI input ~
				    *              object ~NF.  The object ~ND is not a variable or parameter."
				    */

static Object string_constant_68;  /* "Error while reading the snapshot file ~S for the GFI input ~
				    *                 object ~NF.  Could not locate a valid variable or parameter ~
				    *                 history count."
				    */

static Object string_constant_69;  /* "Error while reading the snapshot file ~S for the GFI ~
				    *                    input object ~NF.  There should be ~D history values for ~ND."
				    */

static Object Qsupplied;           /* supplied */

/* PARSE-AND-PUT-GFI-NUPEC-SNAPSHOT-VALUES */
Object parse_and_put_gfi_nupec_snapshot_values(gfi_input_frame,
	    replace_history_qm,no_data_service_required_qm)
    Object gfi_input_frame, replace_history_qm, no_data_service_required_qm;
{
    Object designation_qm, start_index_of_value_qm, variable_or_parameter_qm;
    Object history_count_qm, current_value_qm, collection_time_qm;
    Object expiration_time_qm, error_flag, current_value_error_qm, result_qm;
    Object gensymed_symbol, sub_class_bit_vector, temp_1, temp_2;
    Object store_managed_number_or_value_arg, svref_new_value, temp_3, temp_4;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    double gensymed_symbol_4, arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(217,122);
    designation_qm = 
	    parse_nupec_snapshot_constant_designation(gfi_input_frame);
    start_index_of_value_qm = Nil;
    variable_or_parameter_qm = Nil;
    history_count_qm = Nil;
    current_value_qm = Nil;
    collection_time_qm = Nil;
    expiration_time_qm = Nil;
    error_flag = array_constant_5;
    current_value_error_qm = Nil;
    result_qm = Nil;
    if ( !TRUEP(designation_qm)) {
	Suppress_warning_message_header_qm = T;
	if ((SI_Long)2L <= IFIX(Warning_message_level))
	    give_warning_1(4,FIX((SI_Long)2L),string_constant_65,
		    get_lookup_slot_value(gfi_input_frame,
		    Qgfi_input_file_pathname),gfi_input_frame);
	Suppress_warning_message_header_qm = Nil;
	result_qm = error_flag;
    }
    else {
	gensymed_symbol = evaluate_designation(designation_qm,Nil);
	if ( !TRUEP(gensymed_symbol))
	    variable_or_parameter_qm = Nil;
	else if (SIMPLE_VECTOR_P(gensymed_symbol) && 
		EQ(ISVREF(gensymed_symbol,(SI_Long)0L),
		Qg2_defstruct_structure_name_temporary_constant_g2_struct)) {
	    reclaim_temporary_constant_1(gensymed_symbol);
	    variable_or_parameter_qm = Nil;
	}
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(gensymed_symbol,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Variable_or_parameter_class_description,
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
	    if (temp ? (SI_Long)0L != (IFIX(ISVREF(gensymed_symbol,
		    (SI_Long)5L)) & (SI_Long)1L) : TRUEP(Nil))
		variable_or_parameter_qm = gensymed_symbol;
	    else
		variable_or_parameter_qm = Nil;
	}
	if ( !TRUEP(variable_or_parameter_qm)) {
	    Suppress_warning_message_header_qm = T;
	    if ((SI_Long)2L <= IFIX(Warning_message_level))
		give_warning_1(5,FIX((SI_Long)2L),string_constant_66,
			get_lookup_slot_value(gfi_input_frame,
			Qgfi_input_file_pathname),gfi_input_frame,
			designation_qm);
	    Suppress_warning_message_header_qm = Nil;
	    result_qm = error_flag;
	}
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(variable_or_parameter_qm,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Variable_or_parameter_class_description,
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
	    if ( !temp) {
		Suppress_warning_message_header_qm = T;
		if ((SI_Long)2L <= IFIX(Warning_message_level))
		    give_warning_1(5,FIX((SI_Long)2L),string_constant_67,
			    get_lookup_slot_value(gfi_input_frame,
			    Qgfi_input_file_pathname),gfi_input_frame,
			    designation_qm);
		Suppress_warning_message_header_qm = Nil;
		result_qm = error_flag;
	    }
	    else {
		temp_1 = 
			get_lookup_slot_value_given_default(gfi_input_frame,
			Qgfi_input_line,Nil);
		temp_2 = 
			get_lookup_slot_value_given_default(gfi_input_frame,
			Qgfi_input_line_current_index,FIX((SI_Long)0L));
		start_index_of_value_qm = 
			skip_to_after_gfi_delimitter_in_string(temp_1,
			temp_2,
			get_lookup_slot_value_given_default(gfi_input_frame,
			Qgfi_input_line_length,FIX((SI_Long)0L)));
		if (start_index_of_value_qm) {
		    set_non_savable_lookup_slot_value(gfi_input_frame,
			    Qgfi_input_line_current_index,
			    start_index_of_value_qm);
		    temp_1 = 
			    get_lookup_slot_value_given_default(gfi_input_frame,
			    Qgfi_input_line,Nil);
		    temp_2 = 
			    get_lookup_slot_value_given_default(gfi_input_frame,
			    Qgfi_input_line_current_index,FIX((SI_Long)0L));
		    result = read_number_from_string(temp_1,temp_2,
			    get_lookup_slot_value_given_default(gfi_input_frame,
			    Qgfi_input_line_length,FIX((SI_Long)0L)));
		    MVS_2(result,history_count_qm,start_index_of_value_qm);
		}
		if ( !TRUEP(start_index_of_value_qm) ||  
			!TRUEP(history_count_qm) || IFIX(history_count_qm) 
			< (SI_Long)0L) {
		    Suppress_warning_message_header_qm = T;
		    if ((SI_Long)2L <= IFIX(Warning_message_level))
			give_warning_1(4,FIX((SI_Long)2L),
				string_constant_68,
				get_lookup_slot_value(gfi_input_frame,
				Qgfi_input_file_pathname),gfi_input_frame);
		    Suppress_warning_message_header_qm = Nil;
		    result_qm = error_flag;
		}
		else {
		    if (start_index_of_value_qm)
			set_non_savable_lookup_slot_value(gfi_input_frame,
				Qgfi_input_line_current_index,
				start_index_of_value_qm);
		    current_value_qm = 
			    parse_nupec_snapshot_gfi_variable_or_parameter_value(gfi_input_frame,
			    designation_qm,variable_or_parameter_qm);
		    if ( !TRUEP(current_value_qm))
			current_value_error_qm = T;
		    else {
			collection_time_qm = 
				parse_nupec_snapshot_gfi_time_stamp(gfi_input_frame,
				designation_qm,T);
			if ( !TRUEP(collection_time_qm))
			    current_value_error_qm = T;
			else {
			    sub_class_bit_vector = 
				    ISVREF(ISVREF(variable_or_parameter_qm,
				    (SI_Long)1L),(SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(Variable_class_description,
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
				gensymed_symbol_2 = gensymed_symbol_2 << 
					gensymed_symbol_3;
				gensymed_symbol_1 = gensymed_symbol_1 & 
					gensymed_symbol_2;
				temp = (SI_Long)0L < gensymed_symbol_1;
			    }
			    else
				temp = TRUEP(Nil);
			    if (temp) {
				expiration_time_qm = 
					parse_nupec_snapshot_gfi_time_stamp(gfi_input_frame,
					designation_qm,Nil);
				if ( !TRUEP(expiration_time_qm))
				    current_value_error_qm = T;
			    }
			}
		    }
		    if (current_value_error_qm)
			result_qm = error_flag;
		    else if (EQ(history_count_qm,FIX((SI_Long)0L))) {
			if (replace_history_qm)
			    clear_histories(variable_or_parameter_qm);
		    }
		    else if (IFIX(history_count_qm) > (SI_Long)0L &&  
			    !TRUEP(read_one_gfi_input_line(gfi_input_frame))) {
			Suppress_warning_message_header_qm = T;
			if ((SI_Long)2L <= IFIX(Warning_message_level)) {
			    temp_2 = get_lookup_slot_value(gfi_input_frame,
				    Qgfi_input_file_pathname);
			    give_warning_1(6,FIX((SI_Long)2L),
				    string_constant_69,temp_2,
				    gfi_input_frame,history_count_qm,
				    designation_qm);
			}
			Suppress_warning_message_header_qm = Nil;
			result_qm = error_flag;
		    }
		    else
			result_qm = replace_history_qm ? 
				replace_gfi_nupec_snapshot_values_in_history(gfi_input_frame,
				designation_qm,variable_or_parameter_qm,
				history_count_qm) : 
				add_gfi_nupec_snapshot_values_to_history(gfi_input_frame,
				designation_qm,variable_or_parameter_qm,
				history_count_qm);
		    if ( !(current_value_error_qm || 
			    text_string_p(result_qm) && 
			    string_equalw(result_qm,error_flag) || 
			    EQL(expiration_time_qm,Some_time_ago))) {
			if (replace_history_qm) {
			    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
				if (INLINE_DOUBLE_FLOAT_VECTOR_P(current_value_qm) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_value_qm)) 
					== (SI_Long)1L)
				    store_managed_number_or_value_arg = 
					    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(current_value_qm,
					    (SI_Long)0L));
				else if (INLINE_LONG_VECTOR_P(current_value_qm) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_value_qm)) 
					== (SI_Long)1L)
				    store_managed_number_or_value_arg = 
					    aref1(current_value_qm,
					    FIX((SI_Long)0L));
				else
				    store_managed_number_or_value_arg = 
					    current_value_qm;
				svref_new_value = 
					store_managed_number_or_value_function(ISVREF(variable_or_parameter_qm,
					(SI_Long)23L),
					store_managed_number_or_value_arg);
				ISVREF(variable_or_parameter_qm,
					(SI_Long)23L) = svref_new_value;
			    }
			    POP_LOCAL_ALLOCATION(0,0);
			    svref_new_value = FIXNUMP(collection_time_qm) 
				    || SYMBOLP(collection_time_qm) ? 
				    collection_time_qm : 
				    copy_evaluation_value_1(collection_time_qm);
			    ISVREF(variable_or_parameter_qm,(SI_Long)21L) 
				    = svref_new_value;
			    sub_class_bit_vector = 
				    ISVREF(ISVREF(variable_or_parameter_qm,
				    (SI_Long)1L),(SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(Variable_class_description,
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
				gensymed_symbol_2 = gensymed_symbol_2 << 
					gensymed_symbol_3;
				gensymed_symbol_1 = gensymed_symbol_1 & 
					gensymed_symbol_2;
				temp = (SI_Long)0L < gensymed_symbol_1;
			    }
			    else
				temp = TRUEP(Nil);
			    if (temp) {
				if (INLINE_DOUBLE_FLOAT_VECTOR_P(expiration_time_qm) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(expiration_time_qm)) 
					== (SI_Long)1L) {
				    gensymed_symbol_4 = 
					    DFLOAT_ISAREF_1(expiration_time_qm,
					    (SI_Long)0L) - 
					    DFLOAT_ISAREF_1(G2_time_at_start,
					    (SI_Long)0L) + 
					    (double)IFIX(Gensym_time_at_start);
				    arg = gensymed_symbol_4;
				    arg_1 = 
					    DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum_as_float);
				    temp = arg > arg_1 &&  
					    !inline_nanp_for_comparison(arg) 
					    ?  
					    !inline_nanp_for_comparison(arg_1) 
					    : TRUEP(Qnil);
				    if (temp);
				    else {
					arg = gensymed_symbol_4;
					arg_1 = 
						DOUBLE_FLOAT_TO_DOUBLE(Most_negative_fixnum_as_float);
					temp = arg < arg_1 &&  
						!inline_nanp_for_comparison(arg) 
						?  
						!inline_nanp_for_comparison(arg_1) 
						: TRUEP(Qnil);
				    }
				    svref_new_value = temp ? 
					    Most_negative_fixnum : 
					    LONG_TO_FIXNUM(inline_floor_1(gensymed_symbol_4));
				}
				else
				    svref_new_value = expiration_time_qm;
				ISVREF(variable_or_parameter_qm,
					(SI_Long)26L) = svref_new_value;
			    }
			}
			else {
			    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
				temp_2 = variable_or_parameter_qm;
				if (INLINE_DOUBLE_FLOAT_VECTOR_P(current_value_qm) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_value_qm)) 
					== (SI_Long)1L)
				    temp_1 = 
					    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(current_value_qm,
					    (SI_Long)0L));
				else if (INLINE_LONG_VECTOR_P(current_value_qm) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_value_qm)) 
					== (SI_Long)1L)
				    temp_1 = aref1(current_value_qm,
					    FIX((SI_Long)0L));
				else
				    temp_1 = current_value_qm;
				if (INLINE_DOUBLE_FLOAT_VECTOR_P(current_value_qm) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_value_qm)) 
					== (SI_Long)1L)
				    temp_3 = 
					    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(current_value_qm,
					    (SI_Long)0L));
				else if (INLINE_LONG_VECTOR_P(current_value_qm) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_value_qm)) 
					== (SI_Long)1L)
				    temp_3 = aref1(current_value_qm,
					    FIX((SI_Long)0L));
				else
				    temp_3 = current_value_qm;
				temp_3 = 
					data_type_of_variable_or_parameter_datum(temp_3,
					variable_or_parameter_qm);
				sub_class_bit_vector = 
					ISVREF(ISVREF(variable_or_parameter_qm,
					(SI_Long)1L),(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(Variable_class_description,
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
				if (temp) {
				    if (EQ(ISVREF(variable_or_parameter_qm,
					    (SI_Long)27L),Qsupplied)) {
					sub_class_bit_vector = 
						ISVREF(ISVREF(variable_or_parameter_qm,
						(SI_Long)1L),(SI_Long)19L);
					superior_class_bit_number = 
						IFIX(ISVREF(Quantitative_variable_class_description,
						(SI_Long)18L));
					sub_class_vector_index = 
						superior_class_bit_number 
						>>  -  - (SI_Long)3L;
					if (sub_class_vector_index < 
						IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
						    {
					    gensymed_symbol_1 = 
						    UBYTE_8_ISAREF_1(sub_class_bit_vector,
						    sub_class_vector_index);
					    gensymed_symbol_2 = (SI_Long)1L;
					    gensymed_symbol_3 = 
						    superior_class_bit_number 
						    & (SI_Long)7L;
					    gensymed_symbol_2 = 
						    gensymed_symbol_2 << 
						    gensymed_symbol_3;
					    gensymed_symbol_1 = 
						    gensymed_symbol_1 & 
						    gensymed_symbol_2;
					    temp = (SI_Long)0L < 
						    gensymed_symbol_1;
					}
					else
					    temp = TRUEP(Nil);
					temp_4 = temp ? expiration_time_qm 
						: Qnever;
				    }
				    else
					temp_4 = Nil;
				}
				else
				    temp_4 = Nil;
				put_current_value(5,temp_2,temp_1,temp_3,
					temp_4,collection_time_qm);
			    }
			    POP_LOCAL_ALLOCATION(0,0);
			}
		    }
		    collection_time_qm = 
			    reclaim_managed_number_or_value_function(collection_time_qm);
		    expiration_time_qm = 
			    reclaim_managed_number_or_value_function(expiration_time_qm);
		    current_value_qm = 
			    reclaim_managed_number_or_value_function(current_value_qm);
		}
	    }
	}
    }
    return VALUES_1(result_qm);
}

/* PARSE-NUPEC-SNAPSHOT-CONSTANT-DESIGNATION */
Object parse_nupec_snapshot_constant_designation(gfi_input_frame)
    Object gfi_input_frame;
{
    Object length_1, start_index, line, end_index, substring;

    x_note_fn_call(217,123);
    length_1 = get_lookup_slot_value_given_default(gfi_input_frame,
	    Qgfi_input_line_length,FIX((SI_Long)0L));
    start_index = get_lookup_slot_value_given_default(gfi_input_frame,
	    Qgfi_input_line_current_index,FIX((SI_Long)0L));
    line = get_lookup_slot_value_given_default(gfi_input_frame,
	    Qgfi_input_line,Nil);
    end_index = Nil;
    if (start_index && FIXNUM_LT(start_index,length_1)) {
	end_index = skip_to_after_gfi_delimitter_in_string(line,
		start_index,length_1);
	if ( !TRUEP(end_index))
	    end_index = length_1;
	else
	    end_index = FIXNUM_SUB1(end_index);
	set_non_savable_lookup_slot_value(gfi_input_frame,
		Qgfi_input_line_current_index,end_index);
	substring = text_string_substring(line,start_index,end_index);
	return read_gfi_designation_from_string(gfi_input_frame,substring);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_70;  /* "Missing a time-stamp for ~ND while reading from the ~
				    *               file ~S for the GFI input object ~NF."
				    */

static Object string_constant_71;  /* "Incorrect time-stamp for ~ND while reading from the ~
				    *                       file ~S for the GFI input object ~NF."
				    */

/* PARSE-NUPEC-SNAPSHOT-GFI-TIME-STAMP */
Object parse_nupec_snapshot_gfi_time_stamp(gfi_input_frame,designation,
	    time_stamp_only_qm)
    Object gfi_input_frame, designation, time_stamp_only_qm;
{
    Object temp, temp_1, current_index_qm, collection_time_qm;

    x_note_fn_call(217,124);
    temp = get_lookup_slot_value_given_default(gfi_input_frame,
	    Qgfi_input_line,Nil);
    temp_1 = get_lookup_slot_value_given_default(gfi_input_frame,
	    Qgfi_input_line_current_index,FIX((SI_Long)0L));
    current_index_qm = skip_to_after_gfi_delimitter_in_string(temp,temp_1,
	    get_lookup_slot_value_given_default(gfi_input_frame,
	    Qgfi_input_line_length,FIX((SI_Long)0L)));
    if ( !TRUEP(current_index_qm)) {
	Suppress_warning_message_header_qm = T;
	if ((SI_Long)2L <= IFIX(Warning_message_level))
	    give_warning_1(5,FIX((SI_Long)2L),string_constant_70,
		    designation,get_lookup_slot_value(gfi_input_frame,
		    Qgfi_input_file_pathname),gfi_input_frame);
	Suppress_warning_message_header_qm = Nil;
	return VALUES_1(Nil);
    }
    else {
	set_non_savable_lookup_slot_value(gfi_input_frame,
		Qgfi_input_line_current_index,current_index_qm);
	collection_time_qm = 
		read_and_encode_nupec_snapshot_time_stamp_or_symbol(gfi_input_frame,
		time_stamp_only_qm);
	temp_1 = collection_time_qm;
	if (temp_1)
	    return VALUES_1(temp_1);
	else {
	    Suppress_warning_message_header_qm = T;
	    if ((SI_Long)2L <= IFIX(Warning_message_level))
		give_warning_1(5,FIX((SI_Long)2L),string_constant_71,
			designation,get_lookup_slot_value(gfi_input_frame,
			Qgfi_input_file_pathname),gfi_input_frame);
	    Suppress_warning_message_header_qm = Nil;
	    return VALUES_1(Nil);
	}
    }
}

/* READ-AND-ENCODE-NUPEC-SNAPSHOT-TIME-STAMP-OR-SYMBOL */
Object read_and_encode_nupec_snapshot_time_stamp_or_symbol(gfi_input_frame,
	    time_stamp_only_qm)
    Object gfi_input_frame, time_stamp_only_qm;
{
    Object temp, temp_1, seconds_qm, minutes, hours, day, month, year;
    Object end_index_of_time_stamp, second_fraction_float_qm;
    Object subsecond_time_qm, seconds_fixnum_qm, encoded_time, symbol_value_qm;
    Object end_index_of_symbol_qm, relative_time_qm;
    Object end_index_of_relative_time_qm;
    char temp_3;
    double temp_2, arg, arg_1, store_managed_number_arg;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(217,125);
    if (EQ(get_lookup_slot_value(gfi_input_frame,
	    Qgfi_input_time_stamp_format),Qexplicit)) {
	temp = get_lookup_slot_value_given_default(gfi_input_frame,
		Qgfi_input_line,Nil);
	temp_1 = get_lookup_slot_value_given_default(gfi_input_frame,
		Qgfi_input_line_current_index,FIX((SI_Long)0L));
	result = read_time_stamp_from_string(temp,temp_1,
		get_lookup_slot_value_given_default(gfi_input_frame,
		Qgfi_input_line_length,FIX((SI_Long)0L)));
	MVS_7(result,seconds_qm,minutes,hours,day,month,year,
		end_index_of_time_stamp);
	if (seconds_qm) {
	    set_non_savable_lookup_slot_value(gfi_input_frame,
		    Qgfi_input_line_current_index,end_index_of_time_stamp);
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(seconds_qm) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(seconds_qm)) == 
			(SI_Long)1L) {
		    temp_2 = DFLOAT_ISAREF_1(seconds_qm,(SI_Long)0L);
		    second_fraction_float_qm = 
			    DOUBLE_TO_DOUBLE_FLOAT(temp_2 - 
			    inline_ffloor_1(DFLOAT_ISAREF_1(seconds_qm,
			    (SI_Long)0L)));
		}
		else
		    second_fraction_float_qm = Nil;
		if (second_fraction_float_qm) {
		    arg = DOUBLE_FLOAT_TO_DOUBLE(second_fraction_float_qm);
		    arg_1 = 0.0;
		    temp_3 =  !(arg == arg_1 &&  
			    !inline_nanp_for_comparison(arg) &&  
			    !inline_nanp_for_comparison(arg_1));
		}
		else
		    temp_3 = TRUEP(Nil);
		subsecond_time_qm = temp_3 ? second_fraction_float_qm : Nil;
		seconds_fixnum_qm = seconds_qm ? 
			(INLINE_DOUBLE_FLOAT_VECTOR_P(seconds_qm) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(seconds_qm)) == 
			(SI_Long)1L ? 
			LONG_TO_FIXNUM(inline_floor_1(DFLOAT_ISAREF_1(seconds_qm,
			(SI_Long)0L))) : seconds_qm) : Nil;
		encoded_time = 
			gensym_encode_unix_time_as_managed_float(seconds_fixnum_qm,
			minutes,hours,day,month,year);
		if (subsecond_time_qm) {
		    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(subsecond_time_qm);
		    store_managed_number_arg = temp_2 + 
			    DFLOAT_ISAREF_1(encoded_time,(SI_Long)0L);
		    encoded_time = 
			    store_managed_number_function(encoded_time,
			    DOUBLE_TO_DOUBLE_FLOAT(store_managed_number_arg));
		}
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(seconds_qm) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(seconds_qm)) == 
			(SI_Long)1L)
		    reclaim_managed_simple_float_array_of_length_1(seconds_qm);
		else if (INLINE_LONG_VECTOR_P(seconds_qm) != (SI_Long)0L 
			&& IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(seconds_qm)) == 
			(SI_Long)1L)
		    reclaim_managed_simple_long_array_of_length_1(seconds_qm);
		seconds_qm = Nil;
		result = VALUES_1(encoded_time);
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	    return result;
	}
	else if ( !TRUEP(time_stamp_only_qm)) {
	    temp_1 = get_lookup_slot_value_given_default(gfi_input_frame,
		    Qgfi_input_line,Nil);
	    result = read_symbol_from_text_string(2,temp_1,
		    get_lookup_slot_value_given_default(gfi_input_frame,
		    Qgfi_input_line_current_index,FIX((SI_Long)0L)));
	    MVS_2(result,symbol_value_qm,end_index_of_symbol_qm);
	    if (symbol_value_qm) {
		set_non_savable_lookup_slot_value(gfi_input_frame,
			Qgfi_input_line_current_index,end_index_of_symbol_qm);
		if (EQ(symbol_value_qm,Qno_value))
		    return VALUES_1(Some_time_ago);
		else if (EQ(symbol_value_qm,Qnever))
		    return VALUES_1(Qnever);
		else
		    return VALUES_1(Nil);
	    }
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else {
	temp = get_lookup_slot_value_given_default(gfi_input_frame,
		Qgfi_input_line,Nil);
	temp_1 = get_lookup_slot_value_given_default(gfi_input_frame,
		Qgfi_input_line_current_index,FIX((SI_Long)0L));
	result = read_number_from_string(temp,temp_1,
		get_lookup_slot_value_given_default(gfi_input_frame,
		Qgfi_input_line_length,FIX((SI_Long)0L)));
	MVS_2(result,relative_time_qm,end_index_of_relative_time_qm);
	if (relative_time_qm) {
	    set_non_savable_lookup_slot_value(gfi_input_frame,
		    Qgfi_input_line_current_index,
		    end_index_of_relative_time_qm);
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		if (FIXNUMP(relative_time_qm)) {
		    temp_1 = lfloat(relative_time_qm,float_constant);
		    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
		    store_managed_number_arg = temp_2 + 
			    DFLOAT_ISAREF_1(get_lookup_slot_value_given_default(gfi_input_frame,
			    Qgfi_input_base_time,Nil),(SI_Long)0L);
		}
		else {
		    temp_2 = DFLOAT_ISAREF_1(relative_time_qm,(SI_Long)0L);
		    store_managed_number_arg = temp_2 + 
			    DFLOAT_ISAREF_1(get_lookup_slot_value_given_default(gfi_input_frame,
			    Qgfi_input_base_time,Nil),(SI_Long)0L);
		}
		relative_time_qm = 
			store_managed_number_function(relative_time_qm,
			DOUBLE_TO_DOUBLE_FLOAT(store_managed_number_arg));
		result = VALUES_1(relative_time_qm);
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	    return result;
	}
	else if ( !TRUEP(time_stamp_only_qm)) {
	    temp_1 = get_lookup_slot_value_given_default(gfi_input_frame,
		    Qgfi_input_line,Nil);
	    result = read_symbol_from_text_string(2,temp_1,
		    get_lookup_slot_value_given_default(gfi_input_frame,
		    Qgfi_input_line_current_index,FIX((SI_Long)0L)));
	    MVS_2(result,symbol_value_qm,end_index_of_symbol_qm);
	    if (symbol_value_qm && legal_gensym_string_p(1,
		    SYMBOL_NAME(symbol_value_qm))) {
		set_non_savable_lookup_slot_value(gfi_input_frame,
			Qgfi_input_line_current_index,end_index_of_symbol_qm);
		if (EQ(symbol_value_qm,Qno_value))
		    return VALUES_1(Some_time_ago);
		else if (EQ(symbol_value_qm,Qnever))
		    return VALUES_1(Qnever);
		else
		    return VALUES_1(Nil);
	    }
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
}

static Object string_constant_72;  /* "Error while reading the snapshot file ~S for the GFI ~
				    *               input object ~NF.  A value is missing for ~ND."
				    */

static Object string_constant_73;  /* "Error while reading the snapshot file ~S for the GFI ~
				    *                       input object ~NF.  Incorrect value for ~ND."
				    */

/* PARSE-NUPEC-SNAPSHOT-GFI-VARIABLE-OR-PARAMETER-VALUE */
Object parse_nupec_snapshot_gfi_variable_or_parameter_value(gfi_input_frame,
	    designation,variable_or_parameter)
    Object gfi_input_frame, designation, variable_or_parameter;
{
    Object temp, temp_1, current_index_qm, managed_value_qm;

    x_note_fn_call(217,126);
    temp = get_lookup_slot_value_given_default(gfi_input_frame,
	    Qgfi_input_line,Nil);
    temp_1 = get_lookup_slot_value_given_default(gfi_input_frame,
	    Qgfi_input_line_current_index,FIX((SI_Long)0L));
    current_index_qm = skip_to_after_gfi_delimitter_in_string(temp,temp_1,
	    get_lookup_slot_value_given_default(gfi_input_frame,
	    Qgfi_input_line_length,FIX((SI_Long)0L)));
    if ( !TRUEP(current_index_qm)) {
	Suppress_warning_message_header_qm = T;
	if ((SI_Long)2L <= IFIX(Warning_message_level))
	    give_warning_1(5,FIX((SI_Long)2L),string_constant_72,
		    get_lookup_slot_value(gfi_input_frame,
		    Qgfi_input_file_pathname),gfi_input_frame,designation);
	Suppress_warning_message_header_qm = Nil;
	return VALUES_1(Nil);
    }
    else {
	set_non_savable_lookup_slot_value(gfi_input_frame,
		Qgfi_input_line_current_index,current_index_qm);
	managed_value_qm = 
		read_gfi_nupec_snapshot_value_from_input_line(variable_or_parameter,
		gfi_input_frame);
	temp_1 = managed_value_qm;
	if (temp_1)
	    return VALUES_1(temp_1);
	else {
	    Suppress_warning_message_header_qm = T;
	    if ((SI_Long)2L <= IFIX(Warning_message_level))
		give_warning_1(5,FIX((SI_Long)2L),string_constant_73,
			get_lookup_slot_value(gfi_input_frame,
			Qgfi_input_file_pathname),gfi_input_frame,designation);
	    Suppress_warning_message_header_qm = Nil;
	    return VALUES_1(Nil);
	}
    }
}

/* READ-GFI-NUPEC-SNAPSHOT-VALUE-FROM-INPUT-LINE */
Object read_gfi_nupec_snapshot_value_from_input_line(variable_or_parameter,
	    gfi_input_frame)
    Object variable_or_parameter, gfi_input_frame;
{
    Object data_type, string_1, current_index, max_index, symbol;
    Object symbol_end_index, text, text_end_index, error_message_qm;
    Object managed_value, end_index;
    Declare_special(1);
    Object result;

    x_note_fn_call(217,127);
    data_type = ISVREF(variable_or_parameter,(SI_Long)20L);
    string_1 = get_lookup_slot_value_given_default(gfi_input_frame,
	    Qgfi_input_line,Nil);
    current_index = get_lookup_slot_value_given_default(gfi_input_frame,
	    Qgfi_input_line_current_index,FIX((SI_Long)0L));
    max_index = get_lookup_slot_value_given_default(gfi_input_frame,
	    Qgfi_input_line_length,FIX((SI_Long)0L));
    PUSH_SPECIAL_WITH_SYMBOL(Current_index,Qcurrent_index,current_index,0);
      if (EQ(data_type,Qnumber) || EQ(data_type,Qinteger) || EQ(data_type,
	      Qfloat) || EQ(data_type,Qlong) || 
	      lookup_global_or_kb_specific_property_value(data_type,
	      Numeric_data_type_gkbprop))
	  result = read_number_from_string(string_1,Current_index,max_index);
      else if (EQ(data_type,Qtruth_value))
	  result = read_truth_value_from_string(string_1,Current_index,
		  max_index);
      else if (EQ(data_type,Qsymbol)) {
	  result = read_symbol_from_text_string(2,string_1,Current_index);
	  MVS_2(result,symbol,symbol_end_index);
	  if (symbol && legal_gensym_string_p(1,SYMBOL_NAME(symbol)))
	      result = VALUES_2(symbol,symbol_end_index);
	  else
	      result = VALUES_3(Nil,Current_index,Nil);
      }
      else if (EQ(data_type,Qtext)) {
	  result = read_text_string_with_or_without_quotes_from_string(string_1,
		  Current_index,max_index);
	  MVS_3(result,text,text_end_index,error_message_qm);
	  if (string_1 &&  !TRUEP(error_message_qm))
	      result = VALUES_2(text,text_end_index);
	  else
	      result = VALUES_3(Nil,Current_index,Nil);
      }
      else
	  result = VALUES_3(Nil,Current_index,Nil);
    POP_SPECIAL();
    MVS_2(result,managed_value,end_index);
    if (managed_value)
	set_non_savable_lookup_slot_value(gfi_input_frame,
		Qgfi_input_line_current_index,end_index);
    return VALUES_1(managed_value);
}

static Object string_constant_74;  /* "Error while reading from the Snapshot file ~S for the ~
				    *               GFI input object ~NF.  Future time-stamp for ~ND."
				    */

/* ADD-GFI-NUPEC-SNAPSHOT-VALUES-TO-HISTORY */
Object add_gfi_nupec_snapshot_values_to_history(gfi_input_frame,
	    designation,variable_or_parameter,history_length)
    Object gfi_input_frame, designation, variable_or_parameter, history_length;
{
    Object history_count, collection_time_qm, value_qm, error_flag, temp_1;
    Object temp_2, sub_class_bit_vector, temp_3;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    double arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(217,128);
    history_count = FIX((SI_Long)0L);
    collection_time_qm = Nil;
    value_qm = Nil;
    error_flag = array_constant_5;
  next_loop:
    collection_time_qm = 
	    parse_nupec_snapshot_gfi_time_stamp(gfi_input_frame,designation,T);
    if ( !TRUEP(collection_time_qm))
	return VALUES_1(error_flag);
    else {
	temp = FIXNUMP(collection_time_qm) ? FIXNUM_GT(collection_time_qm,
		Gensym_time) : TRUEP(Qnil);
	if (temp);
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(collection_time_qm) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(collection_time_qm)) == 
		(SI_Long)1L) {
	    arg = DFLOAT_ISAREF_1(collection_time_qm,(SI_Long)0L);
	    arg_1 = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L);
	    temp = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    Suppress_warning_message_header_qm = T;
	    if ((SI_Long)2L <= IFIX(Warning_message_level))
		give_warning_1(5,FIX((SI_Long)2L),string_constant_74,
			get_lookup_slot_value(gfi_input_frame,
			Qgfi_input_file_pathname),gfi_input_frame,designation);
	    Suppress_warning_message_header_qm = Nil;
	    collection_time_qm = 
		    reclaim_managed_number_or_value_function(collection_time_qm);
	    return VALUES_1(error_flag);
	}
	else {
	    value_qm = 
		    parse_nupec_snapshot_gfi_variable_or_parameter_value(gfi_input_frame,
		    designation,variable_or_parameter);
	    if (value_qm) {
		if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(value_qm) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value_qm)) == 
			    (SI_Long)1L)
			temp_1 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value_qm,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(value_qm) != (SI_Long)0L 
			    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value_qm)) 
			    == (SI_Long)1L)
			temp_1 = aref1(value_qm,FIX((SI_Long)0L));
		    else
			temp_1 = value_qm;
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(value_qm) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value_qm)) == 
			    (SI_Long)1L)
			temp_2 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value_qm,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(value_qm) != (SI_Long)0L 
			    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value_qm)) 
			    == (SI_Long)1L)
			temp_2 = aref1(value_qm,FIX((SI_Long)0L));
		    else
			temp_2 = value_qm;
		    temp_2 = 
			    data_type_of_variable_or_parameter_datum(temp_2,
			    variable_or_parameter);
		    sub_class_bit_vector = 
			    ISVREF(ISVREF(variable_or_parameter,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Variable_class_description,
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
			temp = (SI_Long)0L < gensymed_symbol;
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp) {
			if (EQ(ISVREF(variable_or_parameter,(SI_Long)27L),
				Qsupplied)) {
			    sub_class_bit_vector = 
				    ISVREF(ISVREF(variable_or_parameter,
				    (SI_Long)1L),(SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(Quantitative_variable_class_description,
				    (SI_Long)18L));
			    sub_class_vector_index = 
				    superior_class_bit_number >>  -  - 
				    (SI_Long)3L;
			    if (sub_class_vector_index < 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					{
				gensymed_symbol = 
					UBYTE_8_ISAREF_1(sub_class_bit_vector,
					sub_class_vector_index);
				gensymed_symbol_1 = (SI_Long)1L;
				gensymed_symbol_2 = 
					superior_class_bit_number & 
					(SI_Long)7L;
				gensymed_symbol_1 = gensymed_symbol_1 << 
					gensymed_symbol_2;
				gensymed_symbol = gensymed_symbol & 
					gensymed_symbol_1;
				temp = (SI_Long)0L < gensymed_symbol;
			    }
			    else
				temp = TRUEP(Nil);
			    temp_3 = temp ? collection_time_qm : Qnever;
			}
			else
			    temp_3 = Nil;
		    }
		    else
			temp_3 = Nil;
		    put_current_value(5,variable_or_parameter,temp_1,
			    temp_2,temp_3,collection_time_qm);
		    collection_time_qm = 
			    reclaim_managed_number_or_value_function(collection_time_qm);
		    value_qm = 
			    reclaim_managed_number_or_value_function(value_qm);
		}
		POP_LOCAL_ALLOCATION(0,0);
	    }
	    else {
		collection_time_qm = 
			reclaim_managed_number_or_value_function(collection_time_qm);
		return VALUES_1(error_flag);
	    }
	}
    }
    history_count = FIXNUM_ADD1(history_count);
    if ( !(FIXNUM_LT(history_count,history_length) && 
	    read_one_gfi_input_line(gfi_input_frame)))
	goto end_loop;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object string_constant_75;  /* "Error while reading from the Snapshot file ~S for ~
				    *                           the GFI input object ~NF.  Future time-stamp for ~ND."
				    */

/* REPLACE-GFI-NUPEC-SNAPSHOT-VALUES-IN-HISTORY */
Object replace_gfi_nupec_snapshot_values_in_history(gfi_input_frame,
	    designation,variable_or_parameter,history_length)
    Object gfi_input_frame, designation, variable_or_parameter, history_length;
{
    volatile Object history_qm;
    Object sub_class_bit_vector, history_spec_qm, error_flag;
    volatile Object error_qm;
    Object history, history_count, ring_buffer_shell, temp_1, ring_buffer;
    Object time_stamp_qm, value_qm, tag_temp, amf_available_array_cons_qm;
    Object amf_array, temp_2, amf_result, new_float;
    Object elt_0_of_parallel_vector_values, elt_1_of_parallel_vector_values;
    Object index_1, vector_1, store_managed_number_or_value_arg;
    Object new_managed_array, element_index, temp_4, index_2;
    Object oldest_active_element_index_for_ring_buffer, old_history_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, temp_3;
    char temp;
    double aref_new_value, arg, arg_1;
    Declare_catch(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(217,129);
    history_qm = Nil;
    if (variable_or_parameter) {
	sub_class_bit_vector = ISVREF(ISVREF(variable_or_parameter,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Variable_class_description,
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
    history_spec_qm = temp ? ISVREF(variable_or_parameter,(SI_Long)25L) : Nil;
    error_flag = array_constant_5;
    error_qm = Nil;
    if (IFIX(history_length) <= (SI_Long)0L)
	return VALUES_1(error_flag);
    else {
	history = make_or_reformat_cascaded_ring_buffer(Nil,
		SECOND(history_spec_qm),THIRD(history_spec_qm),
		FOURTH(history_spec_qm));
	history_count = FIX((SI_Long)0L);
	ring_buffer_shell = make_history_ring_buffer_1();
	temp_1 = allocate_managed_float_array(1,
		Smallest_ring_buffer_vector_size);
	SVREF(ring_buffer_shell,FIX((SI_Long)6L)) = temp_1;
	temp_1 = allocate_managed_float_array(1,
		Smallest_ring_buffer_vector_size);
	SVREF(ring_buffer_shell,FIX((SI_Long)7L)) = temp_1;
	temp_1 = Smallest_ring_buffer_vector_size;
	SVREF(ring_buffer_shell,FIX((SI_Long)4L)) = temp_1;
	ring_buffer = ring_buffer_shell;
	time_stamp_qm = Nil;
	value_qm = Nil;
	tag_temp = UNIQUE_TAG(Qnil);
	if (PUSH_CATCH(tag_temp,0)) {
	    temp_1 = history_cons_1(ring_buffer,Nil);
	    SVREF(history,FIX((SI_Long)4L)) = temp_1;
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		amf_available_array_cons_qm = 
			ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
		if (amf_available_array_cons_qm) {
		    amf_array = M_CAR(amf_available_array_cons_qm);
		    temp_1 = Vector_of_simple_float_array_pools;
		    temp_2 = M_CDR(amf_available_array_cons_qm);
		    SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
		    inline_note_reclaim_cons(amf_available_array_cons_qm,
			    Qfloat_array);
		    if (ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_1 = 
				ISVREF(Available_float_array_conses_tail_vector,
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
		aref_new_value = 
			inline_ffloor_1(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L));
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		SVREF(history,FIX((SI_Long)10L)) = new_float;
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	  next_loop:
	    time_stamp_qm = 
		    parse_nupec_snapshot_gfi_time_stamp(gfi_input_frame,
		    designation,T);
	    value_qm = time_stamp_qm ? 
		    parse_nupec_snapshot_gfi_variable_or_parameter_value(gfi_input_frame,
		    designation,variable_or_parameter) : Qnil;
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		if ( !TRUEP(time_stamp_qm) ||  !TRUEP(value_qm)) {
		    error_qm = T;
		    history_qm = history;
		    if (time_stamp_qm)
			time_stamp_qm = 
				reclaim_managed_number_or_value_function(time_stamp_qm);
		    result = VALUES_1(Nil);
		    THROW(tag_temp,result);
		}
		else {
		    temp = FIXNUMP(time_stamp_qm) ? 
			    FIXNUM_GT(time_stamp_qm,Gensym_time) : TRUEP(Qnil);
		    if (temp);
		    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(time_stamp_qm) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(time_stamp_qm)) 
			    == (SI_Long)1L) {
			arg = DFLOAT_ISAREF_1(time_stamp_qm,(SI_Long)0L);
			arg_1 = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L);
			temp = arg > arg_1 &&  
				!inline_nanp_for_comparison(arg) ?  
				!inline_nanp_for_comparison(arg_1) : 
				TRUEP(Qnil);
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp) {
			Suppress_warning_message_header_qm = T;
			if ((SI_Long)2L <= IFIX(Warning_message_level))
			    give_warning_1(5,FIX((SI_Long)2L),
				    string_constant_75,
				    get_lookup_slot_value(gfi_input_frame,
				    Qgfi_input_file_pathname),
				    gfi_input_frame,designation);
			Suppress_warning_message_header_qm = Nil;
			error_qm = T;
			history_qm = history;
			time_stamp_qm = 
				reclaim_managed_number_or_value_function(time_stamp_qm);
			result = VALUES_1(Nil);
			THROW(tag_temp,result);
		    }
		    else {
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(value_qm) != 
				(SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value_qm)) 
				== (SI_Long)1L)
			    elt_0_of_parallel_vector_values = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value_qm,
				    (SI_Long)0L));
			else if (INLINE_LONG_VECTOR_P(value_qm) != 
				(SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value_qm)) 
				== (SI_Long)1L)
			    elt_0_of_parallel_vector_values = 
				    aref1(value_qm,FIX((SI_Long)0L));
			else
			    elt_0_of_parallel_vector_values = value_qm;
			elt_1_of_parallel_vector_values = 
				FIXNUMP(time_stamp_qm) ? 
				FIXNUM_MINUS(time_stamp_qm,
				Gensym_time_at_start) : 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(time_stamp_qm,
				(SI_Long)0L) - 
				DFLOAT_ISAREF_1(ISVREF(history,
				(SI_Long)10L),(SI_Long)0L));
			if (ISVREF(ring_buffer,(SI_Long)3L)) {
			    index_1 = ISVREF(ring_buffer,(SI_Long)1L);
			    temp_1 = FIXNUM_ADD1(ISVREF(ring_buffer,
				    (SI_Long)5L));
			    SVREF(ring_buffer,FIX((SI_Long)5L)) = temp_1;
			    vector_1 = ISVREF(ring_buffer,(SI_Long)6L);
			    if (SIMPLE_VECTOR_P(vector_1) && 
				    EQ(ISVREF(vector_1,(SI_Long)0L),
				    Managed_array_unique_marker)) {
				store_managed_number_or_value_arg = 
					elt_0_of_parallel_vector_values;
				temp_2 = 
					store_managed_number_or_value_function(FIXNUM_LE(ISVREF(vector_1,
					(SI_Long)1L),
					Maximum_in_place_array_size) ? 
					ISVREF(vector_1,
					IFIX(FIXNUM_ADD(index_1,
					Managed_array_index_offset))) : 
					ISVREF(ISVREF(vector_1,
					(IFIX(index_1) >>  -  - 
					(SI_Long)10L) + (SI_Long)2L),
					IFIX(index_1) & (SI_Long)1023L),
					store_managed_number_or_value_arg);
				if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
					Maximum_in_place_array_size)) {
				    temp_1 = FIXNUM_ADD(index_1,
					    Managed_array_index_offset);
				    SVREF(vector_1,temp_1) = temp_2;
				}
				else {
				    temp_1 = ISVREF(vector_1,
					    (IFIX(index_1) >>  -  - 
					    (SI_Long)10L) + (SI_Long)2L);
				    temp_3 = IFIX(index_1) & (SI_Long)1023L;
				    ISVREF(temp_1,temp_3) = temp_2;
				}
			    }
			    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(elt_0_of_parallel_vector_values) 
				    != (SI_Long)0L && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(elt_0_of_parallel_vector_values)) 
				    == (SI_Long)1L) {
				temp_1 = ISVREF(vector_1,(IFIX(index_1) >> 
					 -  - (SI_Long)10L) + (SI_Long)2L);
				temp_3 = IFIX(index_1) & (SI_Long)1023L;
				aref_new_value = 
					DFLOAT_ISAREF_1(elt_0_of_parallel_vector_values,
					(SI_Long)0L);
				DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
			    }
			    else if (FLOATP(elt_0_of_parallel_vector_values)) {
				temp_1 = ISVREF(vector_1,(IFIX(index_1) >> 
					 -  - (SI_Long)10L) + (SI_Long)2L);
				temp_3 = IFIX(index_1) & (SI_Long)1023L;
				aref_new_value = 
					DOUBLE_FLOAT_TO_DOUBLE(elt_0_of_parallel_vector_values);
				DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
			    }
			    else {
				new_managed_array = 
					allocate_managed_array(1,
					ISVREF(vector_1,(SI_Long)1L));
				if ( !TRUEP(ISVREF(ring_buffer,(SI_Long)3L))) {
				    element_index = ISVREF(ring_buffer,
					    (SI_Long)2L);
				  next_loop_1:
				    if (FIXNUM_LE(ISVREF(new_managed_array,
					    (SI_Long)1L),
					    Maximum_in_place_array_size)) {
					temp_1 = FIXNUM_ADD(element_index,
						Managed_array_index_offset);
					amf_available_array_cons_qm = 
						ISVREF(Vector_of_simple_float_array_pools,
						(SI_Long)1L);
					if (amf_available_array_cons_qm) {
					    amf_array = 
						    M_CAR(amf_available_array_cons_qm);
					    temp_2 = 
						    Vector_of_simple_float_array_pools;
					    temp_4 = 
						    M_CDR(amf_available_array_cons_qm);
					    SVREF(temp_2,FIX((SI_Long)1L)) 
						    = temp_4;
					    inline_note_reclaim_cons(amf_available_array_cons_qm,
						    Qfloat_array);
					    if (ISVREF(Available_float_array_conses_tail_vector,
						    IFIX(Current_thread_index))) 
							{
						temp_2 = 
							ISVREF(Available_float_array_conses_tail_vector,
							IFIX(Current_thread_index));
						M_CDR(temp_2) = 
							amf_available_array_cons_qm;
						temp_2 = 
							Available_float_array_conses_tail_vector;
						temp_4 = Current_thread_index;
						SVREF(temp_2,temp_4) = 
							amf_available_array_cons_qm;
					    }
					    else {
						temp_2 = 
							Available_float_array_conses_vector;
						temp_4 = Current_thread_index;
						SVREF(temp_2,temp_4) = 
							amf_available_array_cons_qm;
						temp_2 = 
							Available_float_array_conses_tail_vector;
						temp_4 = Current_thread_index;
						SVREF(temp_2,temp_4) = 
							amf_available_array_cons_qm;
					    }
					    M_CDR(amf_available_array_cons_qm) 
						    = Nil;
					    amf_result = amf_array;
					}
					else {
					    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
						    FIX((SI_Long)1L));
					    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
						    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
					    amf_result = 
						    generate_float_vector(FIX((SI_Long)1L));
					}
					new_float = amf_result;
					aref_new_value = 
						DFLOAT_ISAREF_1(ISVREF(vector_1,
						(IFIX(element_index) >>  - 
						 - (SI_Long)10L) + 
						(SI_Long)2L),
						IFIX(element_index) & 
						(SI_Long)1023L);
					DFLOAT_ISASET_1(new_float,
						(SI_Long)0L,aref_new_value);
					SVREF(new_managed_array,temp_1) = 
						new_float;
				    }
				    else {
					temp_1 = ISVREF(new_managed_array,
						(IFIX(element_index) >>  - 
						 - (SI_Long)10L) + 
						(SI_Long)2L);
					temp_3 = IFIX(element_index) & 
						(SI_Long)1023L;
					amf_available_array_cons_qm = 
						ISVREF(Vector_of_simple_float_array_pools,
						(SI_Long)1L);
					if (amf_available_array_cons_qm) {
					    amf_array = 
						    M_CAR(amf_available_array_cons_qm);
					    temp_2 = 
						    Vector_of_simple_float_array_pools;
					    temp_4 = 
						    M_CDR(amf_available_array_cons_qm);
					    SVREF(temp_2,FIX((SI_Long)1L)) 
						    = temp_4;
					    inline_note_reclaim_cons(amf_available_array_cons_qm,
						    Qfloat_array);
					    if (ISVREF(Available_float_array_conses_tail_vector,
						    IFIX(Current_thread_index))) 
							{
						temp_2 = 
							ISVREF(Available_float_array_conses_tail_vector,
							IFIX(Current_thread_index));
						M_CDR(temp_2) = 
							amf_available_array_cons_qm;
						temp_2 = 
							Available_float_array_conses_tail_vector;
						temp_4 = Current_thread_index;
						SVREF(temp_2,temp_4) = 
							amf_available_array_cons_qm;
					    }
					    else {
						temp_2 = 
							Available_float_array_conses_vector;
						temp_4 = Current_thread_index;
						SVREF(temp_2,temp_4) = 
							amf_available_array_cons_qm;
						temp_2 = 
							Available_float_array_conses_tail_vector;
						temp_4 = Current_thread_index;
						SVREF(temp_2,temp_4) = 
							amf_available_array_cons_qm;
					    }
					    M_CDR(amf_available_array_cons_qm) 
						    = Nil;
					    amf_result = amf_array;
					}
					else {
					    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
						    FIX((SI_Long)1L));
					    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
						    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
					    amf_result = 
						    generate_float_vector(FIX((SI_Long)1L));
					}
					new_float = amf_result;
					aref_new_value = 
						DFLOAT_ISAREF_1(ISVREF(vector_1,
						(IFIX(element_index) >>  - 
						 - (SI_Long)10L) + 
						(SI_Long)2L),
						IFIX(element_index) & 
						(SI_Long)1023L);
					DFLOAT_ISASET_1(new_float,
						(SI_Long)0L,aref_new_value);
					ISVREF(temp_1,temp_3) = new_float;
				    }
				    if (FIXNUM_EQ(element_index,
					    ISVREF(ring_buffer,(SI_Long)1L)))
					goto end_loop;
				    element_index = 
					    FIXNUM_EQ(element_index,
					    FIXNUM_SUB1(ISVREF(ring_buffer,
					    (SI_Long)4L))) ? 
					    FIX((SI_Long)0L) : 
					    FIXNUM_ADD1(element_index);
				    goto next_loop_1;
				  end_loop:;
				}
				reclaim_managed_float_array(vector_1);
				SVREF(ring_buffer,FIX((SI_Long)6L)) = 
					new_managed_array;
				temp_1 = ISVREF(ring_buffer,(SI_Long)6L);
				store_managed_number_or_value_arg = 
					elt_0_of_parallel_vector_values;
				temp_4 = 
					store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp_1,
					(SI_Long)1L),
					Maximum_in_place_array_size) ? 
					ISVREF(temp_1,
					IFIX(FIXNUM_ADD(index_1,
					Managed_array_index_offset))) : 
					ISVREF(ISVREF(temp_1,
					(IFIX(index_1) >>  -  - 
					(SI_Long)10L) + (SI_Long)2L),
					IFIX(index_1) & (SI_Long)1023L),
					store_managed_number_or_value_arg);
				if (FIXNUM_LE(ISVREF(temp_1,(SI_Long)1L),
					Maximum_in_place_array_size)) {
				    temp_2 = FIXNUM_ADD(index_1,
					    Managed_array_index_offset);
				    SVREF(temp_1,temp_2) = temp_4;
				}
				else {
				    temp_1 = ISVREF(temp_1,(IFIX(index_1) 
					    >>  -  - (SI_Long)10L) + 
					    (SI_Long)2L);
				    temp_3 = IFIX(index_1) & (SI_Long)1023L;
				    ISVREF(temp_1,temp_3) = temp_4;
				}
			    }
			    vector_1 = ISVREF(ring_buffer,(SI_Long)7L);
			    if (SIMPLE_VECTOR_P(vector_1) && 
				    EQ(ISVREF(vector_1,(SI_Long)0L),
				    Managed_array_unique_marker)) {
				store_managed_number_or_value_arg = 
					elt_1_of_parallel_vector_values;
				temp_2 = 
					store_managed_number_or_value_function(FIXNUM_LE(ISVREF(vector_1,
					(SI_Long)1L),
					Maximum_in_place_array_size) ? 
					ISVREF(vector_1,
					IFIX(FIXNUM_ADD(index_1,
					Managed_array_index_offset))) : 
					ISVREF(ISVREF(vector_1,
					(IFIX(index_1) >>  -  - 
					(SI_Long)10L) + (SI_Long)2L),
					IFIX(index_1) & (SI_Long)1023L),
					store_managed_number_or_value_arg);
				if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
					Maximum_in_place_array_size)) {
				    temp_1 = FIXNUM_ADD(index_1,
					    Managed_array_index_offset);
				    SVREF(vector_1,temp_1) = temp_2;
				}
				else {
				    temp_1 = ISVREF(vector_1,
					    (IFIX(index_1) >>  -  - 
					    (SI_Long)10L) + (SI_Long)2L);
				    temp_3 = IFIX(index_1) & (SI_Long)1023L;
				    ISVREF(temp_1,temp_3) = temp_2;
				}
			    }
			    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(elt_1_of_parallel_vector_values) 
				    != (SI_Long)0L && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(elt_1_of_parallel_vector_values)) 
				    == (SI_Long)1L) {
				temp_1 = ISVREF(vector_1,(IFIX(index_1) >> 
					 -  - (SI_Long)10L) + (SI_Long)2L);
				temp_3 = IFIX(index_1) & (SI_Long)1023L;
				aref_new_value = 
					DFLOAT_ISAREF_1(elt_1_of_parallel_vector_values,
					(SI_Long)0L);
				DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
			    }
			    else if (FLOATP(elt_1_of_parallel_vector_values)) {
				temp_1 = ISVREF(vector_1,(IFIX(index_1) >> 
					 -  - (SI_Long)10L) + (SI_Long)2L);
				temp_3 = IFIX(index_1) & (SI_Long)1023L;
				aref_new_value = 
					DOUBLE_FLOAT_TO_DOUBLE(elt_1_of_parallel_vector_values);
				DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
			    }
			    else {
				new_managed_array = 
					allocate_managed_array(1,
					ISVREF(vector_1,(SI_Long)1L));
				if ( !TRUEP(ISVREF(ring_buffer,(SI_Long)3L))) {
				    element_index = ISVREF(ring_buffer,
					    (SI_Long)2L);
				  next_loop_2:
				    if (FIXNUM_LE(ISVREF(new_managed_array,
					    (SI_Long)1L),
					    Maximum_in_place_array_size)) {
					temp_1 = FIXNUM_ADD(element_index,
						Managed_array_index_offset);
					amf_available_array_cons_qm = 
						ISVREF(Vector_of_simple_float_array_pools,
						(SI_Long)1L);
					if (amf_available_array_cons_qm) {
					    amf_array = 
						    M_CAR(amf_available_array_cons_qm);
					    temp_2 = 
						    Vector_of_simple_float_array_pools;
					    temp_4 = 
						    M_CDR(amf_available_array_cons_qm);
					    SVREF(temp_2,FIX((SI_Long)1L)) 
						    = temp_4;
					    inline_note_reclaim_cons(amf_available_array_cons_qm,
						    Qfloat_array);
					    if (ISVREF(Available_float_array_conses_tail_vector,
						    IFIX(Current_thread_index))) 
							{
						temp_2 = 
							ISVREF(Available_float_array_conses_tail_vector,
							IFIX(Current_thread_index));
						M_CDR(temp_2) = 
							amf_available_array_cons_qm;
						temp_2 = 
							Available_float_array_conses_tail_vector;
						temp_4 = Current_thread_index;
						SVREF(temp_2,temp_4) = 
							amf_available_array_cons_qm;
					    }
					    else {
						temp_2 = 
							Available_float_array_conses_vector;
						temp_4 = Current_thread_index;
						SVREF(temp_2,temp_4) = 
							amf_available_array_cons_qm;
						temp_2 = 
							Available_float_array_conses_tail_vector;
						temp_4 = Current_thread_index;
						SVREF(temp_2,temp_4) = 
							amf_available_array_cons_qm;
					    }
					    M_CDR(amf_available_array_cons_qm) 
						    = Nil;
					    amf_result = amf_array;
					}
					else {
					    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
						    FIX((SI_Long)1L));
					    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
						    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
					    amf_result = 
						    generate_float_vector(FIX((SI_Long)1L));
					}
					new_float = amf_result;
					aref_new_value = 
						DFLOAT_ISAREF_1(ISVREF(vector_1,
						(IFIX(element_index) >>  - 
						 - (SI_Long)10L) + 
						(SI_Long)2L),
						IFIX(element_index) & 
						(SI_Long)1023L);
					DFLOAT_ISASET_1(new_float,
						(SI_Long)0L,aref_new_value);
					SVREF(new_managed_array,temp_1) = 
						new_float;
				    }
				    else {
					temp_1 = ISVREF(new_managed_array,
						(IFIX(element_index) >>  - 
						 - (SI_Long)10L) + 
						(SI_Long)2L);
					temp_3 = IFIX(element_index) & 
						(SI_Long)1023L;
					amf_available_array_cons_qm = 
						ISVREF(Vector_of_simple_float_array_pools,
						(SI_Long)1L);
					if (amf_available_array_cons_qm) {
					    amf_array = 
						    M_CAR(amf_available_array_cons_qm);
					    temp_2 = 
						    Vector_of_simple_float_array_pools;
					    temp_4 = 
						    M_CDR(amf_available_array_cons_qm);
					    SVREF(temp_2,FIX((SI_Long)1L)) 
						    = temp_4;
					    inline_note_reclaim_cons(amf_available_array_cons_qm,
						    Qfloat_array);
					    if (ISVREF(Available_float_array_conses_tail_vector,
						    IFIX(Current_thread_index))) 
							{
						temp_2 = 
							ISVREF(Available_float_array_conses_tail_vector,
							IFIX(Current_thread_index));
						M_CDR(temp_2) = 
							amf_available_array_cons_qm;
						temp_2 = 
							Available_float_array_conses_tail_vector;
						temp_4 = Current_thread_index;
						SVREF(temp_2,temp_4) = 
							amf_available_array_cons_qm;
					    }
					    else {
						temp_2 = 
							Available_float_array_conses_vector;
						temp_4 = Current_thread_index;
						SVREF(temp_2,temp_4) = 
							amf_available_array_cons_qm;
						temp_2 = 
							Available_float_array_conses_tail_vector;
						temp_4 = Current_thread_index;
						SVREF(temp_2,temp_4) = 
							amf_available_array_cons_qm;
					    }
					    M_CDR(amf_available_array_cons_qm) 
						    = Nil;
					    amf_result = amf_array;
					}
					else {
					    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
						    FIX((SI_Long)1L));
					    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
						    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
					    amf_result = 
						    generate_float_vector(FIX((SI_Long)1L));
					}
					new_float = amf_result;
					aref_new_value = 
						DFLOAT_ISAREF_1(ISVREF(vector_1,
						(IFIX(element_index) >>  - 
						 - (SI_Long)10L) + 
						(SI_Long)2L),
						IFIX(element_index) & 
						(SI_Long)1023L);
					DFLOAT_ISASET_1(new_float,
						(SI_Long)0L,aref_new_value);
					ISVREF(temp_1,temp_3) = new_float;
				    }
				    if (FIXNUM_EQ(element_index,
					    ISVREF(ring_buffer,(SI_Long)1L)))
					goto end_loop_1;
				    element_index = 
					    FIXNUM_EQ(element_index,
					    FIXNUM_SUB1(ISVREF(ring_buffer,
					    (SI_Long)4L))) ? 
					    FIX((SI_Long)0L) : 
					    FIXNUM_ADD1(element_index);
				    goto next_loop_2;
				  end_loop_1:;
				}
				reclaim_managed_float_array(vector_1);
				SVREF(ring_buffer,FIX((SI_Long)7L)) = 
					new_managed_array;
				temp_1 = ISVREF(ring_buffer,(SI_Long)7L);
				store_managed_number_or_value_arg = 
					elt_1_of_parallel_vector_values;
				temp_4 = 
					store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp_1,
					(SI_Long)1L),
					Maximum_in_place_array_size) ? 
					ISVREF(temp_1,
					IFIX(FIXNUM_ADD(index_1,
					Managed_array_index_offset))) : 
					ISVREF(ISVREF(temp_1,
					(IFIX(index_1) >>  -  - 
					(SI_Long)10L) + (SI_Long)2L),
					IFIX(index_1) & (SI_Long)1023L),
					store_managed_number_or_value_arg);
				if (FIXNUM_LE(ISVREF(temp_1,(SI_Long)1L),
					Maximum_in_place_array_size)) {
				    temp_2 = FIXNUM_ADD(index_1,
					    Managed_array_index_offset);
				    SVREF(temp_1,temp_2) = temp_4;
				}
				else {
				    temp_1 = ISVREF(temp_1,(IFIX(index_1) 
					    >>  -  - (SI_Long)10L) + 
					    (SI_Long)2L);
				    temp_3 = IFIX(index_1) & (SI_Long)1023L;
				    ISVREF(temp_1,temp_3) = temp_4;
				}
			    }
			    SVREF(ring_buffer,FIX((SI_Long)3L)) = Nil;
			}
			else {
			    index_2 = ISVREF(ring_buffer,(SI_Long)1L);
			    oldest_active_element_index_for_ring_buffer = 
				    ISVREF(ring_buffer,(SI_Long)2L);
			    if (FIXNUM_EQ(FIXNUM_GE(index_2,
				    oldest_active_element_index_for_ring_buffer) 
				    ? FIXNUM_ADD1(FIXNUM_MINUS(index_2,
				    oldest_active_element_index_for_ring_buffer)) 
				    : 
				    FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(index_2,
				    ISVREF(ring_buffer,(SI_Long)4L)),
				    oldest_active_element_index_for_ring_buffer)),
				    ISVREF(ring_buffer,(SI_Long)4L)))
				expand_history_ring_buffer(ring_buffer);
			    index_2 = ISVREF(ring_buffer,(SI_Long)1L);
			    temp_3 = FIXNUM_EQ(index_2,
				    FIXNUM_SUB1(ISVREF(ring_buffer,
				    (SI_Long)4L))) ? (SI_Long)0L : 
				    IFIX(FIXNUM_ADD1(index_2));
			    ISVREF(ring_buffer,(SI_Long)1L) = FIX(temp_3);
			    index_1 = ISVREF(ring_buffer,(SI_Long)1L);
			    temp_1 = FIXNUM_ADD1(ISVREF(ring_buffer,
				    (SI_Long)5L));
			    SVREF(ring_buffer,FIX((SI_Long)5L)) = temp_1;
			    vector_1 = ISVREF(ring_buffer,(SI_Long)6L);
			    if (SIMPLE_VECTOR_P(vector_1) && 
				    EQ(ISVREF(vector_1,(SI_Long)0L),
				    Managed_array_unique_marker)) {
				store_managed_number_or_value_arg = 
					elt_0_of_parallel_vector_values;
				temp_2 = 
					store_managed_number_or_value_function(FIXNUM_LE(ISVREF(vector_1,
					(SI_Long)1L),
					Maximum_in_place_array_size) ? 
					ISVREF(vector_1,
					IFIX(FIXNUM_ADD(index_1,
					Managed_array_index_offset))) : 
					ISVREF(ISVREF(vector_1,
					(IFIX(index_1) >>  -  - 
					(SI_Long)10L) + (SI_Long)2L),
					IFIX(index_1) & (SI_Long)1023L),
					store_managed_number_or_value_arg);
				if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
					Maximum_in_place_array_size)) {
				    temp_1 = FIXNUM_ADD(index_1,
					    Managed_array_index_offset);
				    SVREF(vector_1,temp_1) = temp_2;
				}
				else {
				    temp_1 = ISVREF(vector_1,
					    (IFIX(index_1) >>  -  - 
					    (SI_Long)10L) + (SI_Long)2L);
				    temp_3 = IFIX(index_1) & (SI_Long)1023L;
				    ISVREF(temp_1,temp_3) = temp_2;
				}
			    }
			    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(elt_0_of_parallel_vector_values) 
				    != (SI_Long)0L && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(elt_0_of_parallel_vector_values)) 
				    == (SI_Long)1L) {
				temp_1 = ISVREF(vector_1,(IFIX(index_1) >> 
					 -  - (SI_Long)10L) + (SI_Long)2L);
				temp_3 = IFIX(index_1) & (SI_Long)1023L;
				aref_new_value = 
					DFLOAT_ISAREF_1(elt_0_of_parallel_vector_values,
					(SI_Long)0L);
				DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
			    }
			    else if (FLOATP(elt_0_of_parallel_vector_values)) {
				temp_1 = ISVREF(vector_1,(IFIX(index_1) >> 
					 -  - (SI_Long)10L) + (SI_Long)2L);
				temp_3 = IFIX(index_1) & (SI_Long)1023L;
				aref_new_value = 
					DOUBLE_FLOAT_TO_DOUBLE(elt_0_of_parallel_vector_values);
				DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
			    }
			    else {
				new_managed_array = 
					allocate_managed_array(1,
					ISVREF(vector_1,(SI_Long)1L));
				if ( !TRUEP(ISVREF(ring_buffer,(SI_Long)3L))) {
				    element_index = ISVREF(ring_buffer,
					    (SI_Long)2L);
				  next_loop_3:
				    if (FIXNUM_LE(ISVREF(new_managed_array,
					    (SI_Long)1L),
					    Maximum_in_place_array_size)) {
					temp_1 = FIXNUM_ADD(element_index,
						Managed_array_index_offset);
					amf_available_array_cons_qm = 
						ISVREF(Vector_of_simple_float_array_pools,
						(SI_Long)1L);
					if (amf_available_array_cons_qm) {
					    amf_array = 
						    M_CAR(amf_available_array_cons_qm);
					    temp_2 = 
						    Vector_of_simple_float_array_pools;
					    temp_4 = 
						    M_CDR(amf_available_array_cons_qm);
					    SVREF(temp_2,FIX((SI_Long)1L)) 
						    = temp_4;
					    inline_note_reclaim_cons(amf_available_array_cons_qm,
						    Qfloat_array);
					    if (ISVREF(Available_float_array_conses_tail_vector,
						    IFIX(Current_thread_index))) 
							{
						temp_2 = 
							ISVREF(Available_float_array_conses_tail_vector,
							IFIX(Current_thread_index));
						M_CDR(temp_2) = 
							amf_available_array_cons_qm;
						temp_2 = 
							Available_float_array_conses_tail_vector;
						temp_4 = Current_thread_index;
						SVREF(temp_2,temp_4) = 
							amf_available_array_cons_qm;
					    }
					    else {
						temp_2 = 
							Available_float_array_conses_vector;
						temp_4 = Current_thread_index;
						SVREF(temp_2,temp_4) = 
							amf_available_array_cons_qm;
						temp_2 = 
							Available_float_array_conses_tail_vector;
						temp_4 = Current_thread_index;
						SVREF(temp_2,temp_4) = 
							amf_available_array_cons_qm;
					    }
					    M_CDR(amf_available_array_cons_qm) 
						    = Nil;
					    amf_result = amf_array;
					}
					else {
					    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
						    FIX((SI_Long)1L));
					    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
						    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
					    amf_result = 
						    generate_float_vector(FIX((SI_Long)1L));
					}
					new_float = amf_result;
					aref_new_value = 
						DFLOAT_ISAREF_1(ISVREF(vector_1,
						(IFIX(element_index) >>  - 
						 - (SI_Long)10L) + 
						(SI_Long)2L),
						IFIX(element_index) & 
						(SI_Long)1023L);
					DFLOAT_ISASET_1(new_float,
						(SI_Long)0L,aref_new_value);
					SVREF(new_managed_array,temp_1) = 
						new_float;
				    }
				    else {
					temp_1 = ISVREF(new_managed_array,
						(IFIX(element_index) >>  - 
						 - (SI_Long)10L) + 
						(SI_Long)2L);
					temp_3 = IFIX(element_index) & 
						(SI_Long)1023L;
					amf_available_array_cons_qm = 
						ISVREF(Vector_of_simple_float_array_pools,
						(SI_Long)1L);
					if (amf_available_array_cons_qm) {
					    amf_array = 
						    M_CAR(amf_available_array_cons_qm);
					    temp_2 = 
						    Vector_of_simple_float_array_pools;
					    temp_4 = 
						    M_CDR(amf_available_array_cons_qm);
					    SVREF(temp_2,FIX((SI_Long)1L)) 
						    = temp_4;
					    inline_note_reclaim_cons(amf_available_array_cons_qm,
						    Qfloat_array);
					    if (ISVREF(Available_float_array_conses_tail_vector,
						    IFIX(Current_thread_index))) 
							{
						temp_2 = 
							ISVREF(Available_float_array_conses_tail_vector,
							IFIX(Current_thread_index));
						M_CDR(temp_2) = 
							amf_available_array_cons_qm;
						temp_2 = 
							Available_float_array_conses_tail_vector;
						temp_4 = Current_thread_index;
						SVREF(temp_2,temp_4) = 
							amf_available_array_cons_qm;
					    }
					    else {
						temp_2 = 
							Available_float_array_conses_vector;
						temp_4 = Current_thread_index;
						SVREF(temp_2,temp_4) = 
							amf_available_array_cons_qm;
						temp_2 = 
							Available_float_array_conses_tail_vector;
						temp_4 = Current_thread_index;
						SVREF(temp_2,temp_4) = 
							amf_available_array_cons_qm;
					    }
					    M_CDR(amf_available_array_cons_qm) 
						    = Nil;
					    amf_result = amf_array;
					}
					else {
					    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
						    FIX((SI_Long)1L));
					    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
						    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
					    amf_result = 
						    generate_float_vector(FIX((SI_Long)1L));
					}
					new_float = amf_result;
					aref_new_value = 
						DFLOAT_ISAREF_1(ISVREF(vector_1,
						(IFIX(element_index) >>  - 
						 - (SI_Long)10L) + 
						(SI_Long)2L),
						IFIX(element_index) & 
						(SI_Long)1023L);
					DFLOAT_ISASET_1(new_float,
						(SI_Long)0L,aref_new_value);
					ISVREF(temp_1,temp_3) = new_float;
				    }
				    if (FIXNUM_EQ(element_index,
					    ISVREF(ring_buffer,(SI_Long)1L)))
					goto end_loop_2;
				    element_index = 
					    FIXNUM_EQ(element_index,
					    FIXNUM_SUB1(ISVREF(ring_buffer,
					    (SI_Long)4L))) ? 
					    FIX((SI_Long)0L) : 
					    FIXNUM_ADD1(element_index);
				    goto next_loop_3;
				  end_loop_2:;
				}
				reclaim_managed_float_array(vector_1);
				SVREF(ring_buffer,FIX((SI_Long)6L)) = 
					new_managed_array;
				temp_1 = ISVREF(ring_buffer,(SI_Long)6L);
				store_managed_number_or_value_arg = 
					elt_0_of_parallel_vector_values;
				temp_4 = 
					store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp_1,
					(SI_Long)1L),
					Maximum_in_place_array_size) ? 
					ISVREF(temp_1,
					IFIX(FIXNUM_ADD(index_1,
					Managed_array_index_offset))) : 
					ISVREF(ISVREF(temp_1,
					(IFIX(index_1) >>  -  - 
					(SI_Long)10L) + (SI_Long)2L),
					IFIX(index_1) & (SI_Long)1023L),
					store_managed_number_or_value_arg);
				if (FIXNUM_LE(ISVREF(temp_1,(SI_Long)1L),
					Maximum_in_place_array_size)) {
				    temp_2 = FIXNUM_ADD(index_1,
					    Managed_array_index_offset);
				    SVREF(temp_1,temp_2) = temp_4;
				}
				else {
				    temp_1 = ISVREF(temp_1,(IFIX(index_1) 
					    >>  -  - (SI_Long)10L) + 
					    (SI_Long)2L);
				    temp_3 = IFIX(index_1) & (SI_Long)1023L;
				    ISVREF(temp_1,temp_3) = temp_4;
				}
			    }
			    vector_1 = ISVREF(ring_buffer,(SI_Long)7L);
			    if (SIMPLE_VECTOR_P(vector_1) && 
				    EQ(ISVREF(vector_1,(SI_Long)0L),
				    Managed_array_unique_marker)) {
				store_managed_number_or_value_arg = 
					elt_1_of_parallel_vector_values;
				temp_2 = 
					store_managed_number_or_value_function(FIXNUM_LE(ISVREF(vector_1,
					(SI_Long)1L),
					Maximum_in_place_array_size) ? 
					ISVREF(vector_1,
					IFIX(FIXNUM_ADD(index_1,
					Managed_array_index_offset))) : 
					ISVREF(ISVREF(vector_1,
					(IFIX(index_1) >>  -  - 
					(SI_Long)10L) + (SI_Long)2L),
					IFIX(index_1) & (SI_Long)1023L),
					store_managed_number_or_value_arg);
				if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
					Maximum_in_place_array_size)) {
				    temp_1 = FIXNUM_ADD(index_1,
					    Managed_array_index_offset);
				    SVREF(vector_1,temp_1) = temp_2;
				}
				else {
				    temp_1 = ISVREF(vector_1,
					    (IFIX(index_1) >>  -  - 
					    (SI_Long)10L) + (SI_Long)2L);
				    temp_3 = IFIX(index_1) & (SI_Long)1023L;
				    ISVREF(temp_1,temp_3) = temp_2;
				}
			    }
			    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(elt_1_of_parallel_vector_values) 
				    != (SI_Long)0L && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(elt_1_of_parallel_vector_values)) 
				    == (SI_Long)1L) {
				temp_1 = ISVREF(vector_1,(IFIX(index_1) >> 
					 -  - (SI_Long)10L) + (SI_Long)2L);
				temp_3 = IFIX(index_1) & (SI_Long)1023L;
				aref_new_value = 
					DFLOAT_ISAREF_1(elt_1_of_parallel_vector_values,
					(SI_Long)0L);
				DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
			    }
			    else if (FLOATP(elt_1_of_parallel_vector_values)) {
				temp_1 = ISVREF(vector_1,(IFIX(index_1) >> 
					 -  - (SI_Long)10L) + (SI_Long)2L);
				temp_3 = IFIX(index_1) & (SI_Long)1023L;
				aref_new_value = 
					DOUBLE_FLOAT_TO_DOUBLE(elt_1_of_parallel_vector_values);
				DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
			    }
			    else {
				new_managed_array = 
					allocate_managed_array(1,
					ISVREF(vector_1,(SI_Long)1L));
				if ( !TRUEP(ISVREF(ring_buffer,(SI_Long)3L))) {
				    element_index = ISVREF(ring_buffer,
					    (SI_Long)2L);
				  next_loop_4:
				    if (FIXNUM_LE(ISVREF(new_managed_array,
					    (SI_Long)1L),
					    Maximum_in_place_array_size)) {
					temp_1 = FIXNUM_ADD(element_index,
						Managed_array_index_offset);
					amf_available_array_cons_qm = 
						ISVREF(Vector_of_simple_float_array_pools,
						(SI_Long)1L);
					if (amf_available_array_cons_qm) {
					    amf_array = 
						    M_CAR(amf_available_array_cons_qm);
					    temp_2 = 
						    Vector_of_simple_float_array_pools;
					    temp_4 = 
						    M_CDR(amf_available_array_cons_qm);
					    SVREF(temp_2,FIX((SI_Long)1L)) 
						    = temp_4;
					    inline_note_reclaim_cons(amf_available_array_cons_qm,
						    Qfloat_array);
					    if (ISVREF(Available_float_array_conses_tail_vector,
						    IFIX(Current_thread_index))) 
							{
						temp_2 = 
							ISVREF(Available_float_array_conses_tail_vector,
							IFIX(Current_thread_index));
						M_CDR(temp_2) = 
							amf_available_array_cons_qm;
						temp_2 = 
							Available_float_array_conses_tail_vector;
						temp_4 = Current_thread_index;
						SVREF(temp_2,temp_4) = 
							amf_available_array_cons_qm;
					    }
					    else {
						temp_2 = 
							Available_float_array_conses_vector;
						temp_4 = Current_thread_index;
						SVREF(temp_2,temp_4) = 
							amf_available_array_cons_qm;
						temp_2 = 
							Available_float_array_conses_tail_vector;
						temp_4 = Current_thread_index;
						SVREF(temp_2,temp_4) = 
							amf_available_array_cons_qm;
					    }
					    M_CDR(amf_available_array_cons_qm) 
						    = Nil;
					    amf_result = amf_array;
					}
					else {
					    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
						    FIX((SI_Long)1L));
					    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
						    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
					    amf_result = 
						    generate_float_vector(FIX((SI_Long)1L));
					}
					new_float = amf_result;
					aref_new_value = 
						DFLOAT_ISAREF_1(ISVREF(vector_1,
						(IFIX(element_index) >>  - 
						 - (SI_Long)10L) + 
						(SI_Long)2L),
						IFIX(element_index) & 
						(SI_Long)1023L);
					DFLOAT_ISASET_1(new_float,
						(SI_Long)0L,aref_new_value);
					SVREF(new_managed_array,temp_1) = 
						new_float;
				    }
				    else {
					temp_1 = ISVREF(new_managed_array,
						(IFIX(element_index) >>  - 
						 - (SI_Long)10L) + 
						(SI_Long)2L);
					temp_3 = IFIX(element_index) & 
						(SI_Long)1023L;
					amf_available_array_cons_qm = 
						ISVREF(Vector_of_simple_float_array_pools,
						(SI_Long)1L);
					if (amf_available_array_cons_qm) {
					    amf_array = 
						    M_CAR(amf_available_array_cons_qm);
					    temp_2 = 
						    Vector_of_simple_float_array_pools;
					    temp_4 = 
						    M_CDR(amf_available_array_cons_qm);
					    SVREF(temp_2,FIX((SI_Long)1L)) 
						    = temp_4;
					    inline_note_reclaim_cons(amf_available_array_cons_qm,
						    Qfloat_array);
					    if (ISVREF(Available_float_array_conses_tail_vector,
						    IFIX(Current_thread_index))) 
							{
						temp_2 = 
							ISVREF(Available_float_array_conses_tail_vector,
							IFIX(Current_thread_index));
						M_CDR(temp_2) = 
							amf_available_array_cons_qm;
						temp_2 = 
							Available_float_array_conses_tail_vector;
						temp_4 = Current_thread_index;
						SVREF(temp_2,temp_4) = 
							amf_available_array_cons_qm;
					    }
					    else {
						temp_2 = 
							Available_float_array_conses_vector;
						temp_4 = Current_thread_index;
						SVREF(temp_2,temp_4) = 
							amf_available_array_cons_qm;
						temp_2 = 
							Available_float_array_conses_tail_vector;
						temp_4 = Current_thread_index;
						SVREF(temp_2,temp_4) = 
							amf_available_array_cons_qm;
					    }
					    M_CDR(amf_available_array_cons_qm) 
						    = Nil;
					    amf_result = amf_array;
					}
					else {
					    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
						    FIX((SI_Long)1L));
					    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
						    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
					    amf_result = 
						    generate_float_vector(FIX((SI_Long)1L));
					}
					new_float = amf_result;
					aref_new_value = 
						DFLOAT_ISAREF_1(ISVREF(vector_1,
						(IFIX(element_index) >>  - 
						 - (SI_Long)10L) + 
						(SI_Long)2L),
						IFIX(element_index) & 
						(SI_Long)1023L);
					DFLOAT_ISASET_1(new_float,
						(SI_Long)0L,aref_new_value);
					ISVREF(temp_1,temp_3) = new_float;
				    }
				    if (FIXNUM_EQ(element_index,
					    ISVREF(ring_buffer,(SI_Long)1L)))
					goto end_loop_3;
				    element_index = 
					    FIXNUM_EQ(element_index,
					    FIXNUM_SUB1(ISVREF(ring_buffer,
					    (SI_Long)4L))) ? 
					    FIX((SI_Long)0L) : 
					    FIXNUM_ADD1(element_index);
				    goto next_loop_4;
				  end_loop_3:;
				}
				reclaim_managed_float_array(vector_1);
				SVREF(ring_buffer,FIX((SI_Long)7L)) = 
					new_managed_array;
				temp_1 = ISVREF(ring_buffer,(SI_Long)7L);
				store_managed_number_or_value_arg = 
					elt_1_of_parallel_vector_values;
				temp_4 = 
					store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp_1,
					(SI_Long)1L),
					Maximum_in_place_array_size) ? 
					ISVREF(temp_1,
					IFIX(FIXNUM_ADD(index_1,
					Managed_array_index_offset))) : 
					ISVREF(ISVREF(temp_1,
					(IFIX(index_1) >>  -  - 
					(SI_Long)10L) + (SI_Long)2L),
					IFIX(index_1) & (SI_Long)1023L),
					store_managed_number_or_value_arg);
				if (FIXNUM_LE(ISVREF(temp_1,(SI_Long)1L),
					Maximum_in_place_array_size)) {
				    temp_2 = FIXNUM_ADD(index_1,
					    Managed_array_index_offset);
				    SVREF(temp_1,temp_2) = temp_4;
				}
				else {
				    temp_1 = ISVREF(temp_1,(IFIX(index_1) 
					    >>  -  - (SI_Long)10L) + 
					    (SI_Long)2L);
				    temp_3 = IFIX(index_1) & (SI_Long)1023L;
				    ISVREF(temp_1,temp_3) = temp_4;
				}
			    }
			}
			time_stamp_qm = 
				reclaim_managed_number_or_value_function(time_stamp_qm);
			value_qm = 
				reclaim_managed_number_or_value_function(value_qm);
		    }
		}
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	    history_count = FIXNUM_ADD1(history_count);
	    if ( !(FIXNUM_LT(history_count,history_length) && 
		    read_one_gfi_input_line(gfi_input_frame)))
		goto end_loop_4;
	    goto next_loop;
	  end_loop_4:
	    history_qm = history;
	}
	POP_CATCH(0);
	if (error_qm) {
	    reclaim_history_buffer(history_qm);
	    return VALUES_1(error_flag);
	}
	else {
	    old_history_qm = ISVREF(variable_or_parameter,(SI_Long)24L);
	    if (old_history_qm)
		reclaim_history_buffer(old_history_qm);
	    ISVREF(variable_or_parameter,(SI_Long)24L) = history_qm;
	    return VALUES_1(variable_or_parameter);
	}
    }
}

static Object Qtext_conversion_style;  /* text-conversion-style */

/* GFI-WRITE-STRING */
Object gfi_write_string(string_1,gfi_output_interface)
    Object string_1, gfi_output_interface;
{
    Object temp;

    x_note_fn_call(217,130);
    temp = 
	    come_up_with_text_conversion_style_structure(get_slot_value_function(gfi_output_interface,
	    Qtext_conversion_style,Nil),Nil);
    temp = export_and_emit_text_string(string_1,temp,
	    get_lookup_slot_value_given_default(gfi_output_interface,
	    Qgfi_output_file_stream,Nil));
    return VALUES_1(temp);
}

/* GFI-WRITE-CHAR */
Object gfi_write_char(character_1,gfi_output_interface)
    Object character_1, gfi_output_interface;
{
    Object thing, temp, temp_1;

    x_note_fn_call(217,131);
    thing = character_1;
    temp = CHARACTERP(thing) ? CHAR_CODE(thing) : thing;
    temp_1 = 
	    come_up_with_text_conversion_style_structure(get_slot_value_function(gfi_output_interface,
	    Qtext_conversion_style,Nil),Nil);
    temp_1 = export_and_emit_character(temp,temp_1,
	    get_lookup_slot_value_given_default(gfi_output_interface,
	    Qgfi_output_file_stream,Nil));
    return VALUES_1(temp_1);
}

/* GFI-TERPRI */
Object gfi_terpri(gfi_output_interface)
    Object gfi_output_interface;
{
    Object temp;

    x_note_fn_call(217,132);
    temp = 
	    come_up_with_text_conversion_style_structure(get_slot_value_function(gfi_output_interface,
	    Qtext_conversion_style,Nil),Nil);
    temp = 
	    g2_stream_write_line_terminator_using_text_conversion_style(temp,
	    get_lookup_slot_value_given_default(gfi_output_interface,
	    Qgfi_output_file_stream,Nil));
    return VALUES_1(temp);
}

static Object Qgfi_input_file_buffer;  /* gfi-input-file-buffer */

static Object Qunicode;            /* unicode */

static Object Qunicode_byte_swapped;  /* unicode-byte-swapped */

static Object Qunicode_ucs_2;      /* unicode-ucs-2 */

static Object Qunicode_ucs_2_byte_swapped;  /* unicode-ucs-2-byte-swapped */

/* GFI-READ-LINE */
Object gfi_read_line(gfi_input_interface)
    Object gfi_input_interface;
{
    Object g2_input_stream, buffer, text_conversion_style_structure;
    Object gensymed_symbol, n_2_octet_byte_swapped_p, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object character_qm, lead_octet, trail_octet, count_of_characters_read_qm;
    Object temp, peeked_character_qm, thing, temp_1, schar_arg_2;
    Object schar_new_value, text_line;
    SI_Long offset, available_characters, position_1, initial_file_position;
    SI_Long n_octets_per_character, octets_per_char_minus_one, bv16_length;
    SI_Long aref_arg_2, aref_new_value, length_1, gensymed_symbol_1;
    SI_Long gensymed_symbol_2, incff_1_arg, decff_1_arg;
    char char_1, char_2;
    Declare_special(5);

    x_note_fn_call(217,133);
    g2_input_stream = 
	    get_lookup_slot_value_given_default(gfi_input_interface,
	    Qgfi_input_file_stream,Nil);
    buffer = get_lookup_slot_value(gfi_input_interface,Qgfi_input_file_buffer);
    offset = IFIX(get_lookup_slot_value_given_default(gfi_input_interface,
	    Qgfi_input_file_buffer_offset,FIX((SI_Long)0L)));
    available_characters = 
	    IFIX(get_lookup_slot_value_given_default(gfi_input_interface,
	    Qgfi_input_file_buffer_available_characters,FIX((SI_Long)0L)));
    position_1 = 
	    IFIX(get_lookup_slot_value_given_default(gfi_input_interface,
	    Qgfi_input_file_buffer_position,FIX((SI_Long)0L)));
    initial_file_position = offset + position_1;
    text_conversion_style_structure = 
	    come_up_with_text_conversion_style_structure(get_slot_value_function(gfi_input_interface,
	    Qtext_conversion_style,Nil),Nil);
    gensymed_symbol = ISVREF(text_conversion_style_structure,(SI_Long)2L);
    n_octets_per_character = EQ(gensymed_symbol,Qunicode) || 
	    EQ(gensymed_symbol,Qunicode_byte_swapped) || 
	    EQ(gensymed_symbol,Qunicode_ucs_2) || EQ(gensymed_symbol,
	    Qunicode_ucs_2_byte_swapped) ? (SI_Long)2L : (SI_Long)1L;
    octets_per_char_minus_one = n_octets_per_character == (SI_Long)2L ? 
	    (SI_Long)1L : (SI_Long)0L;
    gensymed_symbol = ISVREF(text_conversion_style_structure,(SI_Long)2L);
    n_2_octet_byte_swapped_p = EQ(gensymed_symbol,Qunicode_byte_swapped) 
	    || EQ(gensymed_symbol,Qunicode_ucs_2_byte_swapped) ? T : Nil;
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
	      character_qm = Nil;
	    next_loop:
	      if (position_1 < available_characters - 
		      octets_per_char_minus_one) {
		  char_1 = ISCHAR(buffer,position_1);
		  char_2 = '\000';
		  position_1 = position_1 + (SI_Long)1L;
		  if (n_octets_per_character == (SI_Long)2L) {
		      char_2 = ISCHAR(buffer,position_1);
		      position_1 = position_1 + (SI_Long)1L;
		      if (n_2_octet_byte_swapped_p) {
			  lead_octet = CHAR_CODE(CHAR_TO_CHARACTER(char_2));
			  trail_octet = CHAR_CODE(CHAR_TO_CHARACTER(char_1));
			  gensymed_symbol_1 = IFIX(lead_octet) & (SI_Long)255L;
			  gensymed_symbol_2 = (SI_Long)8L;
			  gensymed_symbol_2 = gensymed_symbol_1 << 
				  gensymed_symbol_2;
			  gensymed_symbol_1 = IFIX(trail_octet) & 
				  (SI_Long)255L;
			  character_qm = FIX(gensymed_symbol_2 | 
				  gensymed_symbol_1);
		      }
		      else {
			  lead_octet = CHAR_CODE(CHAR_TO_CHARACTER(char_1));
			  trail_octet = CHAR_CODE(CHAR_TO_CHARACTER(char_2));
			  gensymed_symbol_1 = IFIX(lead_octet) & (SI_Long)255L;
			  gensymed_symbol_2 = (SI_Long)8L;
			  gensymed_symbol_2 = gensymed_symbol_1 << 
				  gensymed_symbol_2;
			  gensymed_symbol_1 = IFIX(trail_octet) & 
				  (SI_Long)255L;
			  character_qm = FIX(gensymed_symbol_2 | 
				  gensymed_symbol_1);
		      }
		  }
		  else
		      character_qm = CHAR_CODE(CHAR_TO_CHARACTER(char_1));
	      }
	      else {
		  count_of_characters_read_qm = 
			  g2_stream_read_into_buffer(buffer,
			  FIX((SI_Long)512L),g2_input_stream);
		  temp = count_of_characters_read_qm;
		  if (temp);
		  else
		      temp = FIX((SI_Long)0L);
		  available_characters = IFIX(temp);
		  incff_1_arg = position_1;
		  offset = offset + incff_1_arg;
		  position_1 = (SI_Long)0L;
		  if (available_characters > octets_per_char_minus_one) {
		      char_1 = ISCHAR(buffer,position_1);
		      char_2 = '\000';
		      position_1 = position_1 + (SI_Long)1L;
		      if (n_octets_per_character == (SI_Long)2L) {
			  char_2 = ISCHAR(buffer,position_1);
			  position_1 = position_1 + (SI_Long)1L;
			  if (n_2_octet_byte_swapped_p) {
			      lead_octet = 
				      CHAR_CODE(CHAR_TO_CHARACTER(char_2));
			      trail_octet = 
				      CHAR_CODE(CHAR_TO_CHARACTER(char_1));
			      gensymed_symbol_1 = IFIX(lead_octet) & 
				      (SI_Long)255L;
			      gensymed_symbol_2 = (SI_Long)8L;
			      gensymed_symbol_2 = gensymed_symbol_1 << 
				      gensymed_symbol_2;
			      gensymed_symbol_1 = IFIX(trail_octet) & 
				      (SI_Long)255L;
			      character_qm = FIX(gensymed_symbol_2 | 
				      gensymed_symbol_1);
			  }
			  else {
			      lead_octet = 
				      CHAR_CODE(CHAR_TO_CHARACTER(char_1));
			      trail_octet = 
				      CHAR_CODE(CHAR_TO_CHARACTER(char_2));
			      gensymed_symbol_1 = IFIX(lead_octet) & 
				      (SI_Long)255L;
			      gensymed_symbol_2 = (SI_Long)8L;
			      gensymed_symbol_2 = gensymed_symbol_1 << 
				      gensymed_symbol_2;
			      gensymed_symbol_1 = IFIX(trail_octet) & 
				      (SI_Long)255L;
			      character_qm = FIX(gensymed_symbol_2 | 
				      gensymed_symbol_1);
			  }
		      }
		      else
			  character_qm = CHAR_CODE(CHAR_TO_CHARACTER(char_1));
		  }
		  else
		      character_qm = Nil;
	      }
	      if ( !TRUEP(character_qm) || IFIX(character_qm) == 
		      (SI_Long)10L || IFIX(character_qm) == (SI_Long)8232L 
		      || IFIX(character_qm) == (SI_Long)8233L)
		  goto end_loop;
	      else if (IFIX(character_qm) == (SI_Long)13L) {
		  if (position_1 < available_characters - 
			  octets_per_char_minus_one) {
		      char_1 = ISCHAR(buffer,position_1);
		      char_2 = '\000';
		      position_1 = position_1 + (SI_Long)1L;
		      if (n_octets_per_character == (SI_Long)2L) {
			  char_2 = ISCHAR(buffer,position_1);
			  position_1 = position_1 + (SI_Long)1L;
			  if (n_2_octet_byte_swapped_p) {
			      lead_octet = 
				      CHAR_CODE(CHAR_TO_CHARACTER(char_2));
			      trail_octet = 
				      CHAR_CODE(CHAR_TO_CHARACTER(char_1));
			      gensymed_symbol_1 = IFIX(lead_octet) & 
				      (SI_Long)255L;
			      gensymed_symbol_2 = (SI_Long)8L;
			      gensymed_symbol_2 = gensymed_symbol_1 << 
				      gensymed_symbol_2;
			      gensymed_symbol_1 = IFIX(trail_octet) & 
				      (SI_Long)255L;
			      peeked_character_qm = FIX(gensymed_symbol_2 
				      | gensymed_symbol_1);
			  }
			  else {
			      lead_octet = 
				      CHAR_CODE(CHAR_TO_CHARACTER(char_1));
			      trail_octet = 
				      CHAR_CODE(CHAR_TO_CHARACTER(char_2));
			      gensymed_symbol_1 = IFIX(lead_octet) & 
				      (SI_Long)255L;
			      gensymed_symbol_2 = (SI_Long)8L;
			      gensymed_symbol_2 = gensymed_symbol_1 << 
				      gensymed_symbol_2;
			      gensymed_symbol_1 = IFIX(trail_octet) & 
				      (SI_Long)255L;
			      peeked_character_qm = FIX(gensymed_symbol_2 
				      | gensymed_symbol_1);
			  }
		      }
		      else
			  peeked_character_qm = 
				  CHAR_CODE(CHAR_TO_CHARACTER(char_1));
		  }
		  else {
		      count_of_characters_read_qm = 
			      g2_stream_read_into_buffer(buffer,
			      FIX((SI_Long)512L),g2_input_stream);
		      temp = count_of_characters_read_qm;
		      if (temp);
		      else
			  temp = FIX((SI_Long)0L);
		      available_characters = IFIX(temp);
		      incff_1_arg = position_1;
		      offset = offset + incff_1_arg;
		      position_1 = (SI_Long)0L;
		      if (available_characters > octets_per_char_minus_one) {
			  char_1 = ISCHAR(buffer,position_1);
			  char_2 = '\000';
			  position_1 = position_1 + (SI_Long)1L;
			  if (n_octets_per_character == (SI_Long)2L) {
			      char_2 = ISCHAR(buffer,position_1);
			      position_1 = position_1 + (SI_Long)1L;
			      if (n_2_octet_byte_swapped_p) {
				  lead_octet = 
					  CHAR_CODE(CHAR_TO_CHARACTER(char_2));
				  trail_octet = 
					  CHAR_CODE(CHAR_TO_CHARACTER(char_1));
				  gensymed_symbol_1 = IFIX(lead_octet) & 
					  (SI_Long)255L;
				  gensymed_symbol_2 = (SI_Long)8L;
				  gensymed_symbol_2 = gensymed_symbol_1 << 
					  gensymed_symbol_2;
				  gensymed_symbol_1 = IFIX(trail_octet) & 
					  (SI_Long)255L;
				  peeked_character_qm = 
					  FIX(gensymed_symbol_2 | 
					  gensymed_symbol_1);
			      }
			      else {
				  lead_octet = 
					  CHAR_CODE(CHAR_TO_CHARACTER(char_1));
				  trail_octet = 
					  CHAR_CODE(CHAR_TO_CHARACTER(char_2));
				  gensymed_symbol_1 = IFIX(lead_octet) & 
					  (SI_Long)255L;
				  gensymed_symbol_2 = (SI_Long)8L;
				  gensymed_symbol_2 = gensymed_symbol_1 << 
					  gensymed_symbol_2;
				  gensymed_symbol_1 = IFIX(trail_octet) & 
					  (SI_Long)255L;
				  peeked_character_qm = 
					  FIX(gensymed_symbol_2 | 
					  gensymed_symbol_1);
			      }
			  }
			  else
			      peeked_character_qm = 
				      CHAR_CODE(CHAR_TO_CHARACTER(char_1));
		      }
		      else
			  peeked_character_qm = Nil;
		  }
		  if ( !(peeked_character_qm && IFIX(peeked_character_qm) 
			  == (SI_Long)10L)) {
		      decff_1_arg = n_octets_per_character;
		      position_1 = position_1 - decff_1_arg;
		  }
		  goto end_loop;
	      }
	      else if (EQ(Current_twriting_output_type,Qwide_string)) {
		  thing = character_qm;
		  twrite_wide_character(CHARACTERP(thing) ? 
			  CHAR_CODE(thing) : thing);
	      }
	      else {
		  if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			  Total_length_of_current_gensym_string))
		      extend_current_gensym_string(0);
		  temp_1 = Current_gensym_string;
		  schar_arg_2 = Fill_pointer_for_current_gensym_string;
		  thing = character_qm;
		  schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			  CHAR_CODE(thing) : thing);
		  SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
		  temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		  Fill_pointer_for_current_gensym_string = temp_1;
	      }
	      goto next_loop;
	    end_loop:;
	      set_non_savable_lookup_slot_value(gfi_input_interface,
		      Qgfi_input_file_buffer_position,FIX(position_1));
	      set_non_savable_lookup_slot_value(gfi_input_interface,
		      Qgfi_input_file_buffer_available_characters,
		      FIX(available_characters));
	      set_non_savable_lookup_slot_value(gfi_input_interface,
		      Qgfi_input_file_buffer_offset,FIX(offset));
	      text_line = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    if (offset + position_1 > initial_file_position)
	temp = text_line;
    else {
	reclaim_text_string(text_line);
	temp = Nil;
    }
    return VALUES_1(temp);
}

void gfi_INIT()
{
    Object temp, temp_1, reclaim_structure_for_gfi_queue_item_1;
    Object AB_package, list_constant_2, Qshut_down_gfi_data_server;
    Object Qset_external_variable_for_gfi, Qinitialize_gfi_data_server;
    Object Qgfi_requests_accept_data_calls, Qaccept_data_from_gfi_data_service;
    Object Qstop_collecting_data_for_gfi_data_service;
    Object Qbegin_collecting_data_for_gfi_data_service, Qpost_on_message_board;
    Object list_constant_13, list_constant_12, list_constant_11;
    Object list_constant_10, Qdata_server_map, Qdata_server_spec;
    Object list_constant_9, list_constant_8, list_constant_7, list_constant_6;
    Object Qserver, Qdata, Qslot_value_reclaimer;
    Object Qreclaim_gfi_last_value_value, Qclasses_which_define, Qdeactivate;
    Object Qdeactivate_for_gfi_input_interface;
    Object Qasynchronous_ignoring_data_server, Qactivate;
    Object Qactivate_for_gfi_input_interface, Qinitialize_after_reading;
    Object Qinitialize_after_reading_for_gfi_input_interface, Qinitialize;
    Object Qinitialize_for_gfi_input_interface, Qslot_putter;
    Object Qput_gfi_input_when_active, Qput_gfi_input_variables_update_mode;
    Object Qput_ignore_gfi_input_base_time_qm;
    Object Qput_gfi_input_time_stamp_format, Qput_gfi_input_file_format;
    Object Qput_gfi_input_file_pathname, Qdeactivate_for_gfi_output_interface;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qactivate_for_gfi_output_interface;
    Object Qinitialize_after_reading_for_gfi_output_interface;
    Object Qinitialize_for_gfi_output_interface, Qwhen_received_value;
    Object Qreclaim_gfi_output_unique_designations_value;
    Object Qreclaim_gfi_output_spreadsheet_field_index_hash_value;
    Object Qreclaim_gfi_output_not_unique_designation_p_results_value;
    Object Qreclaim_gfi_list_of_new_spreadsheet_output_values_value;
    Object Qreclaim_gfi_output_values_value, Qput_file_status;
    Object Qput_gfi_output_when_active, Qput_gfi_output_values;
    Object Qput_gfi_output_file_update_frequency;
    Object Qput_gfi_output_time_stamp_format, Qput_gfi_output_file_format;
    Object Qput_renamed_gfi_output_file_pathname;
    Object Qput_gfi_output_file_pathname;
    Object Qout_gfi_spreadsheet_field_index_hash_vector_131_vectors;
    Object Qgfi_spreadsheet_field_index_hash_vector_131_vector_memory_usage;
    Object string_constant_79, Qutilities2, Qgfi_queue_item;
    Object Qreclaim_structure, Qoutstanding_gfi_queue_item_count;
    Object Qgfi_queue_item_structure_memory_usage, string_constant_78;
    Object Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_77, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type, string_constant_76;
    Object Qgfi_cons_memory_usage, Qoutstanding_gfi_conses, Qutilities1;
    Object list_constant_5, Qgfi_cons_counter_vector, Qmake_thread_array;
    Object Kfuncall, list_constant_4, Qavailable_gfi_conses_tail_vector;
    Object Qavailable_gfi_conses_vector, list_constant_3;
    Object Qgfi_input_white_space, Qgfi_title_for_base_time_string_length;
    Object array_constant_13, Qgfi_title_for_base_time;
    Object Qgfi_designation_for_base_time_string_length, array_constant_12;
    Object Qgfi_designation_for_base_time, Qgfi_delimitter, Qoptional_modules;
    Object Qab, Qstring_or_symbol_equal;

    x_note_fn_call(217,134);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qgfi = STATIC_SYMBOL("GFI",AB_package);
    Qab = STATIC_SYMBOL("AB",AB_package);
    Qoptional_modules = STATIC_SYMBOL("OPTIONAL-MODULES",AB_package);
    Qstring_or_symbol_equal = STATIC_SYMBOL("STRING-OR-SYMBOL-EQUAL",
	    AB_package);
    if ( !TRUEP(member(4,Qgfi,get(Qab,Qoptional_modules,_),Ktest,
	    SYMBOL_FUNCTION(Qstring_or_symbol_equal)))) {
	temp = get(Qab,Qoptional_modules,Nil);
	temp_1 = CONS(Qgfi,temp);
	set_get(Qab,Qoptional_modules,temp_1);
    }
    Qgfi_delimitter = STATIC_SYMBOL("GFI-DELIMITTER",AB_package);
    SET_SYMBOL_VALUE(Qgfi_delimitter,FIX((SI_Long)9L));
    Qgfi_designation_for_base_time = 
	    STATIC_SYMBOL("GFI-DESIGNATION-FOR-BASE-TIME",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgfi_designation_for_base_time,
	    Gfi_designation_for_base_time);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant_12 = STATIC_ARRAY(list_constant_2,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)5L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)14L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)23L,(SI_Long)57344L);
    SET_SYMBOL_VALUE(Qgfi_designation_for_base_time,array_constant_12);
    Qgfi_designation_for_base_time_string_length = 
	    STATIC_SYMBOL("GFI-DESIGNATION-FOR-BASE-TIME-STRING-LENGTH",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgfi_designation_for_base_time_string_length,
	    Gfi_designation_for_base_time_string_length);
    SET_SYMBOL_VALUE(Qgfi_designation_for_base_time_string_length,
	    text_string_length(Gfi_designation_for_base_time));
    Qgfi_title_for_base_time = STATIC_SYMBOL("GFI-TITLE-FOR-BASE-TIME",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgfi_title_for_base_time,
	    Gfi_title_for_base_time);
    array_constant_13 = STATIC_ARRAY(list_constant_2,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)1L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)2L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)3L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)5L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)6L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)7L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)8L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)9L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)15L,(SI_Long)57344L);
    SET_SYMBOL_VALUE(Qgfi_title_for_base_time,array_constant_13);
    Qgfi_title_for_base_time_string_length = 
	    STATIC_SYMBOL("GFI-TITLE-FOR-BASE-TIME-STRING-LENGTH",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgfi_title_for_base_time_string_length,
	    Gfi_title_for_base_time_string_length);
    SET_SYMBOL_VALUE(Qgfi_title_for_base_time_string_length,
	    text_string_length(Gfi_title_for_base_time));
    Qgfi_input_white_space = STATIC_SYMBOL("GFI-INPUT-WHITE-SPACE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgfi_input_white_space,Gfi_input_white_space);
    list_constant_3 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)32L),
	    FIX((SI_Long)9L),FIX((SI_Long)13L));
    SET_SYMBOL_VALUE(Qgfi_input_white_space,list_constant_3);
    Qavailable_gfi_conses = STATIC_SYMBOL("AVAILABLE-GFI-CONSES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_gfi_conses,Available_gfi_conses);
    Qutilities1 = STATIC_SYMBOL("UTILITIES1",AB_package);
    record_system_variable(Qavailable_gfi_conses,Qutilities1,Nil,Qnil,Qt,
	    Qnil,Qnil);
    Qavailable_gfi_conses_tail = STATIC_SYMBOL("AVAILABLE-GFI-CONSES-TAIL",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_gfi_conses_tail,
	    Available_gfi_conses_tail);
    record_system_variable(Qavailable_gfi_conses_tail,Qutilities1,Nil,Qnil,
	    Qt,Qnil,Qnil);
    Qavailable_gfi_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-GFI-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_gfi_conses_vector,
	    Available_gfi_conses_vector);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_thread_array = STATIC_SYMBOL("MAKE-THREAD-ARRAY",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    Qnil);
    record_system_variable(Qavailable_gfi_conses_vector,Qutilities1,
	    list_constant_4,Qnil,Qt,Qnil,Qnil);
    Qavailable_gfi_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-GFI-CONSES-TAIL-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_gfi_conses_tail_vector,
	    Available_gfi_conses_tail_vector);
    record_system_variable(Qavailable_gfi_conses_tail_vector,Qutilities1,
	    list_constant_4,Qnil,Qt,Qnil,Qnil);
    Qgfi_cons_counter_vector = STATIC_SYMBOL("GFI-CONS-COUNTER-VECTOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgfi_cons_counter_vector,
	    Gfi_cons_counter_vector);
    list_constant_5 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    FIX((SI_Long)0L));
    record_system_variable(Qgfi_cons_counter_vector,Qutilities1,
	    list_constant_5,Qnil,Qt,Qnil,Qnil);
    Qgfi_cons_counter = STATIC_SYMBOL("GFI-CONS-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgfi_cons_counter,Gfi_cons_counter);
    record_system_variable(Qgfi_cons_counter,Qutilities1,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    Qoutstanding_gfi_conses = STATIC_SYMBOL("OUTSTANDING-GFI-CONSES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_gfi_conses,
	    STATIC_FUNCTION(outstanding_gfi_conses,NIL,FALSE,0,0));
    Qgfi_cons_memory_usage = STATIC_SYMBOL("GFI-CONS-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qgfi_cons_memory_usage,
	    STATIC_FUNCTION(gfi_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_76 = STATIC_STRING("1q83-WTy9k83-WSy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_gfi_conses);
    push_optimized_constant(Qgfi_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_76));
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_gfi_queue_item_g2_struct = 
	    STATIC_SYMBOL("GFI-QUEUE-ITEM-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qgfi_queue_item = STATIC_SYMBOL("GFI-QUEUE-ITEM",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_gfi_queue_item_g2_struct,
	    Qgfi_queue_item,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qgfi_queue_item,
	    Qg2_defstruct_structure_name_gfi_queue_item_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_gfi_queue_item == UNBOUND)
	The_type_description_of_gfi_queue_item = Nil;
    string_constant_77 = 
	    STATIC_STRING("43Dy8m83i0y1n83i0y8n8k1l8n0000000kuk0k0");
    temp = The_type_description_of_gfi_queue_item;
    The_type_description_of_gfi_queue_item = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_77));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_gfi_queue_item_g2_struct,
	    The_type_description_of_gfi_queue_item,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qgfi_queue_item,
	    The_type_description_of_gfi_queue_item,Qtype_description_of_type);
    Qoutstanding_gfi_queue_item_count = 
	    STATIC_SYMBOL("OUTSTANDING-GFI-QUEUE-ITEM-COUNT",AB_package);
    Qgfi_queue_item_structure_memory_usage = 
	    STATIC_SYMBOL("GFI-QUEUE-ITEM-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_78 = STATIC_STRING("1q83i0y8s83-WVy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_gfi_queue_item_count);
    push_optimized_constant(Qgfi_queue_item_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_78));
    Qchain_of_available_gfi_queue_items = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-GFI-QUEUE-ITEMS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_gfi_queue_items,
	    Chain_of_available_gfi_queue_items);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_gfi_queue_items,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qgfi_queue_item_count = STATIC_SYMBOL("GFI-QUEUE-ITEM-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgfi_queue_item_count,Gfi_queue_item_count);
    record_system_variable(Qgfi_queue_item_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_gfi_queue_items_vector == UNBOUND)
	Chain_of_available_gfi_queue_items_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qgfi_queue_item_structure_memory_usage,
	    STATIC_FUNCTION(gfi_queue_item_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_gfi_queue_item_count,
	    STATIC_FUNCTION(outstanding_gfi_queue_item_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_gfi_queue_item_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_gfi_queue_item,NIL,FALSE,
	    1,1);
    record_direct_structure_method(Qreclaim_structure,Qgfi_queue_item,
	    reclaim_structure_for_gfi_queue_item_1);
    Qavailable_gfi_spreadsheet_field_index_hash_vector_131_vectors = 
	    STATIC_SYMBOL("AVAILABLE-GFI-SPREADSHEET-FIELD-INDEX-HASH-VECTOR-131-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_gfi_spreadsheet_field_index_hash_vector_131_vectors,
	    Available_gfi_spreadsheet_field_index_hash_vector_131_vectors);
    record_system_variable(Qavailable_gfi_spreadsheet_field_index_hash_vector_131_vectors,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcount_of_gfi_spreadsheet_field_index_hash_vector_131_vectors = 
	    STATIC_SYMBOL("COUNT-OF-GFI-SPREADSHEET-FIELD-INDEX-HASH-VECTOR-131-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcount_of_gfi_spreadsheet_field_index_hash_vector_131_vectors,
	    Count_of_gfi_spreadsheet_field_index_hash_vector_131_vectors);
    record_system_variable(Qcount_of_gfi_spreadsheet_field_index_hash_vector_131_vectors,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Available_gfi_spreadsheet_field_index_hash_vector_131_vectors_vector 
	    == UNBOUND)
	Available_gfi_spreadsheet_field_index_hash_vector_131_vectors_vector 
		= make_thread_array(Nil);
    Qout_gfi_spreadsheet_field_index_hash_vector_131_vectors = 
	    STATIC_SYMBOL("OUT-GFI-SPREADSHEET-FIELD-INDEX-HASH-VECTOR-131-VECTORS",
	    AB_package);
    Qgfi_spreadsheet_field_index_hash_vector_131_vector_memory_usage = 
	    STATIC_SYMBOL("GFI-SPREADSHEET-FIELD-INDEX-HASH-VECTOR-131-VECTOR-MEMORY-USAGE",
	    AB_package);
    string_constant_79 = STATIC_STRING("1q83-WWy83*9y83-Oty09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qout_gfi_spreadsheet_field_index_hash_vector_131_vectors);
    push_optimized_constant(Qgfi_spreadsheet_field_index_hash_vector_131_vector_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_79));
    SET_SYMBOL_FUNCTION(Qgfi_spreadsheet_field_index_hash_vector_131_vector_memory_usage,
	    STATIC_FUNCTION(gfi_spreadsheet_field_index_hash_vector_131_vector_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qout_gfi_spreadsheet_field_index_hash_vector_131_vectors,
	    STATIC_FUNCTION(out_gfi_spreadsheet_field_index_hash_vector_131_vectors,
	    NIL,FALSE,0,0));
    Qvector_pool = STATIC_SYMBOL("VECTOR-POOL",AB_package);
    Qsentinel_node = STATIC_SYMBOL("SENTINEL-NODE",AB_package);
    Qhead = STATIC_SYMBOL("HEAD",AB_package);
    Qtail = STATIC_SYMBOL("TAIL",AB_package);
    Qgfi_spreadsheet_field_index_tree_for_hash = 
	    STATIC_SYMBOL("GFI-SPREADSHEET-FIELD-INDEX-TREE-FOR-HASH",
	    AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qqueue_of_active_gfi_output_interface_objects = 
	    STATIC_SYMBOL("QUEUE-OF-ACTIVE-GFI-OUTPUT-INTERFACE-OBJECTS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qqueue_of_active_gfi_output_interface_objects,
	    Queue_of_active_gfi_output_interface_objects);
    record_system_variable(Qqueue_of_active_gfi_output_interface_objects,
	    Qgfi,Nil,Qnil,Qnil,Qnil,Qnil);
    Qqueue_of_active_gfi_input_interface_objects = 
	    STATIC_SYMBOL("QUEUE-OF-ACTIVE-GFI-INPUT-INTERFACE-OBJECTS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qqueue_of_active_gfi_input_interface_objects,
	    Queue_of_active_gfi_input_interface_objects);
    record_system_variable(Qqueue_of_active_gfi_input_interface_objects,
	    Qgfi,Nil,Qnil,Qnil,Qnil,Qnil);
    Qqueue_of_active_uninterruptable_gfi_output_interface_objects = 
	    STATIC_SYMBOL("QUEUE-OF-ACTIVE-UNINTERRUPTABLE-GFI-OUTPUT-INTERFACE-OBJECTS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qqueue_of_active_uninterruptable_gfi_output_interface_objects,
	    Queue_of_active_uninterruptable_gfi_output_interface_objects);
    record_system_variable(Qqueue_of_active_uninterruptable_gfi_output_interface_objects,
	    Qgfi,Nil,Qnil,Qnil,Qnil,Qnil);
    Qqueue_of_active_uninterruptable_gfi_input_interface_objects = 
	    STATIC_SYMBOL("QUEUE-OF-ACTIVE-UNINTERRUPTABLE-GFI-INPUT-INTERFACE-OBJECTS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qqueue_of_active_uninterruptable_gfi_input_interface_objects,
	    Queue_of_active_uninterruptable_gfi_input_interface_objects);
    record_system_variable(Qqueue_of_active_uninterruptable_gfi_input_interface_objects,
	    Qgfi,Nil,Qnil,Qnil,Qnil,Qnil);
    Qtime_slice_expired_p = STATIC_SYMBOL("TIME-SLICE-EXPIRED-P",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtime_slice_expired_p,Time_slice_expired_p);
    Qgfi_output_file_pathname = STATIC_SYMBOL("GFI-OUTPUT-FILE-PATHNAME",
	    AB_package);
    Qgfi_output_when_active = STATIC_SYMBOL("GFI-OUTPUT-WHEN-ACTIVE",
	    AB_package);
    Qgfi_outputting_qm = STATIC_SYMBOL("GFI-OUTPUTTING\?",AB_package);
    Qno_gfi_output_file_pathname = 
	    STATIC_SYMBOL("NO-GFI-OUTPUT-FILE-PATHNAME",AB_package);
    Qincomplete = STATIC_SYMBOL("INCOMPLETE",AB_package);
    Qput_gfi_output_file_pathname = 
	    STATIC_SYMBOL("PUT-GFI-OUTPUT-FILE-PATHNAME",AB_package);
    SET_SYMBOL_FUNCTION(Qput_gfi_output_file_pathname,
	    STATIC_FUNCTION(put_gfi_output_file_pathname,NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qgfi_output_file_pathname,
	    SYMBOL_FUNCTION(Qput_gfi_output_file_pathname),Qslot_putter);
    Qrenamed_gfi_output_file_pathname = 
	    STATIC_SYMBOL("RENAMED-GFI-OUTPUT-FILE-PATHNAME",AB_package);
    Qput_renamed_gfi_output_file_pathname = 
	    STATIC_SYMBOL("PUT-RENAMED-GFI-OUTPUT-FILE-PATHNAME",AB_package);
    SET_SYMBOL_FUNCTION(Qput_renamed_gfi_output_file_pathname,
	    STATIC_FUNCTION(put_renamed_gfi_output_file_pathname,NIL,FALSE,
	    3,3));
    mutate_global_property(Qrenamed_gfi_output_file_pathname,
	    SYMBOL_FUNCTION(Qput_renamed_gfi_output_file_pathname),
	    Qslot_putter);
    Qgfi_output_file_format = STATIC_SYMBOL("GFI-OUTPUT-FILE-FORMAT",
	    AB_package);
    Qput_gfi_output_file_format = 
	    STATIC_SYMBOL("PUT-GFI-OUTPUT-FILE-FORMAT",AB_package);
    SET_SYMBOL_FUNCTION(Qput_gfi_output_file_format,
	    STATIC_FUNCTION(put_gfi_output_file_format,NIL,FALSE,3,3));
    mutate_global_property(Qgfi_output_file_format,
	    SYMBOL_FUNCTION(Qput_gfi_output_file_format),Qslot_putter);
    Qgfi_output_time_stamp_format = 
	    STATIC_SYMBOL("GFI-OUTPUT-TIME-STAMP-FORMAT",AB_package);
    Qput_gfi_output_time_stamp_format = 
	    STATIC_SYMBOL("PUT-GFI-OUTPUT-TIME-STAMP-FORMAT",AB_package);
    SET_SYMBOL_FUNCTION(Qput_gfi_output_time_stamp_format,
	    STATIC_FUNCTION(put_gfi_output_time_stamp_format,NIL,FALSE,3,3));
    mutate_global_property(Qgfi_output_time_stamp_format,
	    SYMBOL_FUNCTION(Qput_gfi_output_time_stamp_format),Qslot_putter);
    Qgfi_output_file_update_frequency = 
	    STATIC_SYMBOL("GFI-OUTPUT-FILE-UPDATE-FREQUENCY",AB_package);
    Qno_gfi_output_update_frequency = 
	    STATIC_SYMBOL("NO-GFI-OUTPUT-UPDATE-FREQUENCY",AB_package);
    Qoutput_one_shot_when_activated_without_interruption = 
	    STATIC_SYMBOL("OUTPUT-ONE-SHOT-WHEN-ACTIVATED-WITHOUT-INTERRUPTION",
	    AB_package);
    Qgfi_output_without_interruption_qm = 
	    STATIC_SYMBOL("GFI-OUTPUT-WITHOUT-INTERRUPTION\?",AB_package);
    Qput_gfi_output_file_update_frequency = 
	    STATIC_SYMBOL("PUT-GFI-OUTPUT-FILE-UPDATE-FREQUENCY",AB_package);
    SET_SYMBOL_FUNCTION(Qput_gfi_output_file_update_frequency,
	    STATIC_FUNCTION(put_gfi_output_file_update_frequency,NIL,FALSE,
	    3,3));
    mutate_global_property(Qgfi_output_file_update_frequency,
	    SYMBOL_FUNCTION(Qput_gfi_output_file_update_frequency),
	    Qslot_putter);
    Qgfi_output_values = STATIC_SYMBOL("GFI-OUTPUT-VALUES",AB_package);
    Qgfi_output_not_unique_designation_p_results = 
	    STATIC_SYMBOL("GFI-OUTPUT-NOT-UNIQUE-DESIGNATION-P-RESULTS",
	    AB_package);
    Qno_gfi_output_values = STATIC_SYMBOL("NO-GFI-OUTPUT-VALUES",AB_package);
    Qput_gfi_output_values = STATIC_SYMBOL("PUT-GFI-OUTPUT-VALUES",AB_package);
    SET_SYMBOL_FUNCTION(Qput_gfi_output_values,
	    STATIC_FUNCTION(put_gfi_output_values,NIL,FALSE,3,3));
    mutate_global_property(Qgfi_output_values,
	    SYMBOL_FUNCTION(Qput_gfi_output_values),Qslot_putter);
    Qput_gfi_output_when_active = 
	    STATIC_SYMBOL("PUT-GFI-OUTPUT-WHEN-ACTIVE",AB_package);
    SET_SYMBOL_FUNCTION(Qput_gfi_output_when_active,
	    STATIC_FUNCTION(put_gfi_output_when_active,NIL,FALSE,3,3));
    mutate_global_property(Qgfi_output_when_active,
	    SYMBOL_FUNCTION(Qput_gfi_output_when_active),Qslot_putter);
    Qfile_status = STATIC_SYMBOL("FILE-STATUS",AB_package);
    Qput_file_status = STATIC_SYMBOL("PUT-FILE-STATUS",AB_package);
    SET_SYMBOL_FUNCTION(Qput_file_status,STATIC_FUNCTION(put_file_status,
	    NIL,FALSE,3,3));
    mutate_global_property(Qfile_status,SYMBOL_FUNCTION(Qput_file_status),
	    Qslot_putter);
    Qreclaim_gfi_output_values_value = 
	    STATIC_SYMBOL("RECLAIM-GFI-OUTPUT-VALUES-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_gfi_output_values_value,
	    STATIC_FUNCTION(reclaim_gfi_output_values_value,NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qgfi_output_values,
	    SYMBOL_FUNCTION(Qreclaim_gfi_output_values_value),
	    Qslot_value_reclaimer);
    Qgfi_list_of_new_spreadsheet_output_values = 
	    STATIC_SYMBOL("GFI-LIST-OF-NEW-SPREADSHEET-OUTPUT-VALUES",
	    AB_package);
    Qreclaim_gfi_list_of_new_spreadsheet_output_values_value = 
	    STATIC_SYMBOL("RECLAIM-GFI-LIST-OF-NEW-SPREADSHEET-OUTPUT-VALUES-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_gfi_list_of_new_spreadsheet_output_values_value,
	    STATIC_FUNCTION(reclaim_gfi_list_of_new_spreadsheet_output_values_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qgfi_list_of_new_spreadsheet_output_values,
	    SYMBOL_FUNCTION(Qreclaim_gfi_list_of_new_spreadsheet_output_values_value),
	    Qslot_value_reclaimer);
    Qreclaim_gfi_output_not_unique_designation_p_results_value = 
	    STATIC_SYMBOL("RECLAIM-GFI-OUTPUT-NOT-UNIQUE-DESIGNATION-P-RESULTS-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_gfi_output_not_unique_designation_p_results_value,
	    STATIC_FUNCTION(reclaim_gfi_output_not_unique_designation_p_results_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qgfi_output_not_unique_designation_p_results,
	    SYMBOL_FUNCTION(Qreclaim_gfi_output_not_unique_designation_p_results_value),
	    Qslot_value_reclaimer);
    Qgfi_output_spreadsheet_field_index_hash = 
	    STATIC_SYMBOL("GFI-OUTPUT-SPREADSHEET-FIELD-INDEX-HASH",
	    AB_package);
    Qreclaim_gfi_output_spreadsheet_field_index_hash_value = 
	    STATIC_SYMBOL("RECLAIM-GFI-OUTPUT-SPREADSHEET-FIELD-INDEX-HASH-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_gfi_output_spreadsheet_field_index_hash_value,
	    STATIC_FUNCTION(reclaim_gfi_output_spreadsheet_field_index_hash_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qgfi_output_spreadsheet_field_index_hash,
	    SYMBOL_FUNCTION(Qreclaim_gfi_output_spreadsheet_field_index_hash_value),
	    Qslot_value_reclaimer);
    Qgfi_output_unique_designations = 
	    STATIC_SYMBOL("GFI-OUTPUT-UNIQUE-DESIGNATIONS",AB_package);
    Qreclaim_gfi_output_unique_designations_value = 
	    STATIC_SYMBOL("RECLAIM-GFI-OUTPUT-UNIQUE-DESIGNATIONS-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_gfi_output_unique_designations_value,
	    STATIC_FUNCTION(reclaim_gfi_output_unique_designations_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qgfi_output_unique_designations,
	    SYMBOL_FUNCTION(Qreclaim_gfi_output_unique_designations_value),
	    Qslot_value_reclaimer);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    string_constant = 
	    STATIC_STRING("~ND is not a variable or parameter, but it was specified ~\n\t as an output value for the GFI Output Interface ~NF.");
    string_constant_1 = 
	    STATIC_STRING("Could not find the value of ~ND in the GFI Output Interface ~NF.");
    string_constant_2 = STATIC_STRING("\"~ND\"");
    string_constant_3 = STATIC_STRING("a designation in the GFI interface");
    string_constant_4 = 
	    string_append2(STATIC_STRING("The GFI Output Interface ~NF found a variable or parameter, ~\n       ~NF, which matches ~A.  However, the variable cannot be ~\n       referenced with respect to a named item, "),
	    STATIC_STRING("and thus will be ~\n       ignored by GFI."));
    Qg2_defstruct_structure_name_temporary_constant_g2_struct = 
	    STATIC_SYMBOL("TEMPORARY-CONSTANT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    string_constant_5 = 
	    STATIC_STRING("~NC is not a variable or parameter.  This output value for the ~\n         GFI Output Interface, ~NF, cannot be written.");
    string_constant_6 = 
	    STATIC_STRING("The GFI Output Interface, ~NF, cannot write a value.  The output ~\n         value was not a variable or parameter.");
    Qwhen_received_value = STATIC_SYMBOL("WHEN-RECEIVED-VALUE",AB_package);
    list_constant = STATIC_CONS(Qwhen_received_value,Qnil);
    Qhandle_gfi_output_interface_new_values = 
	    STATIC_SYMBOL("HANDLE-GFI-OUTPUT-INTERFACE-NEW-VALUES",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    array_constant = STATIC_ARRAY(list_constant_2,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    string_constant_7 = 
	    STATIC_STRING("The variable or parameter which is supposed to hold a ~\n\t \t      pathname in the GFI ~A Interface ~NF, ~ND, does not ~\n\t\t      have a valid value.  (It should be a string.)");
    Qgfi_input_file_pathname = STATIC_SYMBOL("GFI-INPUT-FILE-PATHNAME",
	    AB_package);
    array_constant_1 = STATIC_ARRAY(list_constant_2,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    array_constant_2 = STATIC_ARRAY(list_constant_2,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)57344L);
    Qvalue_request_pending = STATIC_SYMBOL("VALUE-REQUEST-PENDING",AB_package);
    string_constant_8 = 
	    STATIC_STRING("The variable or parameter which is supposed to hold a ~\n \t\t pathname in the GFI ~A Interface ~NF, ~ND, does not exist.");
    string_constant_9 = 
	    STATIC_STRING("Maximum number of output lines has been reached for GFI Output ~\n     Interface ~NF.  No more outputs will be made.");
    Qgfi_output_pathname_string_of_stream_qm = 
	    STATIC_SYMBOL("GFI-OUTPUT-PATHNAME-STRING-OF-STREAM\?",AB_package);
    Qgfi_output_file_stream = STATIC_SYMBOL("GFI-OUTPUT-FILE-STREAM",
	    AB_package);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Qgfi_output_base_time = STATIC_SYMBOL("GFI-OUTPUT-BASE-TIME",AB_package);
    Qgfi_output_scheduled_task = STATIC_SYMBOL("GFI-OUTPUT-SCHEDULED-TASK",
	    AB_package);
    Qnumber_of_lines_output_so_far = 
	    STATIC_SYMBOL("NUMBER-OF-LINES-OUTPUT-SO-FAR",AB_package);
    Qnew_gfi_output_values_this_cycle_qm = 
	    STATIC_SYMBOL("NEW-GFI-OUTPUT-VALUES-THIS-CYCLE\?",AB_package);
    Qgfi_queue_of_new_output_values = 
	    STATIC_SYMBOL("GFI-QUEUE-OF-NEW-OUTPUT-VALUES",AB_package);
    Qspreadsheet = STATIC_SYMBOL("SPREADSHEET",AB_package);
    Qfailed_to_open = STATIC_SYMBOL("FAILED-TO-OPEN",AB_package);
    string_constant_10 = 
	    STATIC_STRING("Could not open output file ~S for ~NF:  ~A.");
    SET_SYMBOL_FUNCTION(Qhandle_gfi_output_interface_new_values,
	    STATIC_FUNCTION(handle_gfi_output_interface_new_values,NIL,
	    FALSE,6,6));
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    Qexplicit = STATIC_SYMBOL("EXPLICIT",AB_package);
    Qgfi_output_interface = STATIC_SYMBOL("GFI-OUTPUT-INTERFACE",AB_package);
    Qfile_system = STATIC_SYMBOL("FILE-SYSTEM",AB_package);
    Qinitialize_for_gfi_output_interface = 
	    STATIC_SYMBOL("INITIALIZE-FOR-GFI-OUTPUT-INTERFACE",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_gfi_output_interface,
	    STATIC_FUNCTION(initialize_for_gfi_output_interface,NIL,FALSE,
	    1,1));
    Qinitialize = STATIC_SYMBOL("INITIALIZE",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qinitialize_for_gfi_output_interface);
    set_get(Qgfi_output_interface,Qinitialize,temp_1);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp_1 = CONS(Qgfi_output_interface,temp);
    mutate_global_property(Qinitialize,temp_1,Qclasses_which_define);
    Qinitialize_after_reading_for_gfi_output_interface = 
	    STATIC_SYMBOL("INITIALIZE-AFTER-READING-FOR-GFI-OUTPUT-INTERFACE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_after_reading_for_gfi_output_interface,
	    STATIC_FUNCTION(initialize_after_reading_for_gfi_output_interface,
	    NIL,FALSE,1,1));
    Qinitialize_after_reading = STATIC_SYMBOL("INITIALIZE-AFTER-READING",
	    AB_package);
    temp_1 = 
	    SYMBOL_FUNCTION(Qinitialize_after_reading_for_gfi_output_interface);
    set_get(Qgfi_output_interface,Qinitialize_after_reading,temp_1);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize_after_reading),
	    Qclasses_which_define);
    temp_1 = CONS(Qgfi_output_interface,temp);
    mutate_global_property(Qinitialize_after_reading,temp_1,
	    Qclasses_which_define);
    Qactivate_for_gfi_output_interface = 
	    STATIC_SYMBOL("ACTIVATE-FOR-GFI-OUTPUT-INTERFACE",AB_package);
    SET_SYMBOL_FUNCTION(Qactivate_for_gfi_output_interface,
	    STATIC_FUNCTION(activate_for_gfi_output_interface,NIL,FALSE,1,1));
    Qactivate = STATIC_SYMBOL("ACTIVATE",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qactivate_for_gfi_output_interface);
    set_get(Qgfi_output_interface,Qactivate,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qactivate),
	    Qclasses_which_define);
    temp_1 = CONS(Qgfi_output_interface,temp);
    mutate_global_property(Qactivate,temp_1,Qclasses_which_define);
    string_constant_11 = 
	    STATIC_STRING("While activating ~NF, the GFI output file could not be ~\n                opened.  This item is incomplete.");
    Qnupec_snapshot = STATIC_SYMBOL("NUPEC-SNAPSHOT",AB_package);
    Qnupec_snapshot_with_restart_time = 
	    STATIC_SYMBOL("NUPEC-SNAPSHOT-WITH-RESTART-TIME",AB_package);
    Qoutput_one_shot_when_activated = 
	    STATIC_SYMBOL("OUTPUT-ONE-SHOT-WHEN-ACTIVATED",AB_package);
    string_constant_12 = 
	    string_append2(STATIC_STRING("When using a GFI file format of NUPEC snapshot for ~NF, the gfi-~\n          output-file-update-frequency must be either \"write to file when ~\n          activated\" or \"write to"),
	    STATIC_STRING(" file when activated, without ~\n          interruption\"."));
    Qready_to_open = STATIC_SYMBOL("READY-TO-OPEN",AB_package);
    Qnumber_of_periodic_specified_designation_handled = 
	    STATIC_SYMBOL("NUMBER-OF-PERIODIC-SPECIFIED-DESIGNATION-HANDLED",
	    AB_package);
    Qrelative = STATIC_SYMBOL("RELATIVE",AB_package);
    array_constant_3 = STATIC_ARRAY(list_constant_2,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)57344L);
    array_constant_4 = STATIC_ARRAY(list_constant_2,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)30L,(SI_Long)24L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)31L,(SI_Long)57344L);
    Qevent_log = STATIC_SYMBOL("EVENT-LOG",AB_package);
    string_constant_13 = 
	    STATIC_STRING("Illegal GFI output file format ~A in ~NF.");
    Qwrite_interval = STATIC_SYMBOL("WRITE-INTERVAL",AB_package);
    Qpriority_of_data_service = STATIC_SYMBOL("PRIORITY-OF-DATA-SERVICE",
	    AB_package);
    Qgfi_output_spreadsheet_values_periodically_task = 
	    STATIC_SYMBOL("GFI-OUTPUT-SPREADSHEET-VALUES-PERIODICALLY-TASK",
	    AB_package);
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qgfi_output_event_log_values_periodically_task = 
	    STATIC_SYMBOL("GFI-OUTPUT-EVENT-LOG-VALUES-PERIODICALLY-TASK",
	    AB_package);
    string_constant_14 = 
	    STATIC_STRING("Illegal GFI output file update frequency ~A in ~NF.");
    SET_SYMBOL_FUNCTION(Qgfi_output_spreadsheet_values_periodically_task,
	    STATIC_FUNCTION(gfi_output_spreadsheet_values_periodically_task,
	    NIL,FALSE,2,2));
    Qmaximum_number_of_output_lines = 
	    STATIC_SYMBOL("MAXIMUM-NUMBER-OF-OUTPUT-LINES",AB_package);
    Qgfi_output_scheduled_task_start_time = 
	    STATIC_SYMBOL("GFI-OUTPUT-SCHEDULED-TASK-START-TIME",AB_package);
    SET_SYMBOL_FUNCTION(Qgfi_output_event_log_values_periodically_task,
	    STATIC_FUNCTION(gfi_output_event_log_values_periodically_task,
	    NIL,FALSE,2,2));
    Qrenamed_gfi_output_file_pathname_qm = 
	    STATIC_SYMBOL("RENAMED-GFI-OUTPUT-FILE-PATHNAME\?",AB_package);
    string_constant_15 = 
	    STATIC_STRING("Error in renaming file ~S to ~S upon close of file.");
    string_constant_16 = 
	    STATIC_STRING("The file ~S for the GFI Output Interface ~NF was not renamed.");
    Qclosed = STATIC_SYMBOL("CLOSED",AB_package);
    Qdeactivate_for_gfi_output_interface = 
	    STATIC_SYMBOL("DEACTIVATE-FOR-GFI-OUTPUT-INTERFACE",AB_package);
    SET_SYMBOL_FUNCTION(Qdeactivate_for_gfi_output_interface,
	    STATIC_FUNCTION(deactivate_for_gfi_output_interface,NIL,FALSE,
	    1,1));
    Qdeactivate = STATIC_SYMBOL("DEACTIVATE",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qdeactivate_for_gfi_output_interface);
    set_get(Qgfi_output_interface,Qdeactivate,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeactivate),
	    Qclasses_which_define);
    temp_1 = CONS(Qgfi_output_interface,temp);
    mutate_global_property(Qdeactivate,temp_1,Qclasses_which_define);
    Qgfi_input_when_active = STATIC_SYMBOL("GFI-INPUT-WHEN-ACTIVE",AB_package);
    Qgfi_inputting_qm = STATIC_SYMBOL("GFI-INPUTTING\?",AB_package);
    Qno_gfi_input_file_pathname = 
	    STATIC_SYMBOL("NO-GFI-INPUT-FILE-PATHNAME",AB_package);
    Qput_gfi_input_file_pathname = 
	    STATIC_SYMBOL("PUT-GFI-INPUT-FILE-PATHNAME",AB_package);
    SET_SYMBOL_FUNCTION(Qput_gfi_input_file_pathname,
	    STATIC_FUNCTION(put_gfi_input_file_pathname,NIL,FALSE,3,3));
    mutate_global_property(Qgfi_input_file_pathname,
	    SYMBOL_FUNCTION(Qput_gfi_input_file_pathname),Qslot_putter);
    Qgfi_input_file_format = STATIC_SYMBOL("GFI-INPUT-FILE-FORMAT",AB_package);
    Qput_gfi_input_file_format = STATIC_SYMBOL("PUT-GFI-INPUT-FILE-FORMAT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_gfi_input_file_format,
	    STATIC_FUNCTION(put_gfi_input_file_format,NIL,FALSE,3,3));
    mutate_global_property(Qgfi_input_file_format,
	    SYMBOL_FUNCTION(Qput_gfi_input_file_format),Qslot_putter);
    Qgfi_input_time_stamp_format = 
	    STATIC_SYMBOL("GFI-INPUT-TIME-STAMP-FORMAT",AB_package);
    Qput_gfi_input_time_stamp_format = 
	    STATIC_SYMBOL("PUT-GFI-INPUT-TIME-STAMP-FORMAT",AB_package);
    SET_SYMBOL_FUNCTION(Qput_gfi_input_time_stamp_format,
	    STATIC_FUNCTION(put_gfi_input_time_stamp_format,NIL,FALSE,3,3));
    mutate_global_property(Qgfi_input_time_stamp_format,
	    SYMBOL_FUNCTION(Qput_gfi_input_time_stamp_format),Qslot_putter);
    Qignore_gfi_input_base_time_qm = 
	    STATIC_SYMBOL("IGNORE-GFI-INPUT-BASE-TIME\?",AB_package);
    Qput_ignore_gfi_input_base_time_qm = 
	    STATIC_SYMBOL("PUT-IGNORE-GFI-INPUT-BASE-TIME\?",AB_package);
    SET_SYMBOL_FUNCTION(Qput_ignore_gfi_input_base_time_qm,
	    STATIC_FUNCTION(put_ignore_gfi_input_base_time_qm,NIL,FALSE,3,3));
    mutate_global_property(Qignore_gfi_input_base_time_qm,
	    SYMBOL_FUNCTION(Qput_ignore_gfi_input_base_time_qm),Qslot_putter);
    Qgfi_input_variables_update_mode = 
	    STATIC_SYMBOL("GFI-INPUT-VARIABLES-UPDATE-MODE",AB_package);
    Qno_gfi_input_variables_update_mode = 
	    STATIC_SYMBOL("NO-GFI-INPUT-VARIABLES-UPDATE-MODE",AB_package);
    Qinput_one_shot_when_activated_without_interruption = 
	    STATIC_SYMBOL("INPUT-ONE-SHOT-WHEN-ACTIVATED-WITHOUT-INTERRUPTION",
	    AB_package);
    Qgfi_input_without_interruption_qm = 
	    STATIC_SYMBOL("GFI-INPUT-WITHOUT-INTERRUPTION\?",AB_package);
    Qput_gfi_input_variables_update_mode = 
	    STATIC_SYMBOL("PUT-GFI-INPUT-VARIABLES-UPDATE-MODE",AB_package);
    SET_SYMBOL_FUNCTION(Qput_gfi_input_variables_update_mode,
	    STATIC_FUNCTION(put_gfi_input_variables_update_mode,NIL,FALSE,
	    3,3));
    mutate_global_property(Qgfi_input_variables_update_mode,
	    SYMBOL_FUNCTION(Qput_gfi_input_variables_update_mode),
	    Qslot_putter);
    Qput_gfi_input_when_active = STATIC_SYMBOL("PUT-GFI-INPUT-WHEN-ACTIVE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_gfi_input_when_active,
	    STATIC_FUNCTION(put_gfi_input_when_active,NIL,FALSE,3,3));
    mutate_global_property(Qgfi_input_when_active,
	    SYMBOL_FUNCTION(Qput_gfi_input_when_active),Qslot_putter);
    Qgfi_input_interface = STATIC_SYMBOL("GFI-INPUT-INTERFACE",AB_package);
    Qinitialize_for_gfi_input_interface = 
	    STATIC_SYMBOL("INITIALIZE-FOR-GFI-INPUT-INTERFACE",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_gfi_input_interface,
	    STATIC_FUNCTION(initialize_for_gfi_input_interface,NIL,FALSE,1,1));
    temp_1 = SYMBOL_FUNCTION(Qinitialize_for_gfi_input_interface);
    set_get(Qgfi_input_interface,Qinitialize,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp_1 = CONS(Qgfi_input_interface,temp);
    mutate_global_property(Qinitialize,temp_1,Qclasses_which_define);
    Qinitialize_after_reading_for_gfi_input_interface = 
	    STATIC_SYMBOL("INITIALIZE-AFTER-READING-FOR-GFI-INPUT-INTERFACE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_after_reading_for_gfi_input_interface,
	    STATIC_FUNCTION(initialize_after_reading_for_gfi_input_interface,
	    NIL,FALSE,1,1));
    temp_1 = 
	    SYMBOL_FUNCTION(Qinitialize_after_reading_for_gfi_input_interface);
    set_get(Qgfi_input_interface,Qinitialize_after_reading,temp_1);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize_after_reading),
	    Qclasses_which_define);
    temp_1 = CONS(Qgfi_input_interface,temp);
    mutate_global_property(Qinitialize_after_reading,temp_1,
	    Qclasses_which_define);
    Qactivate_for_gfi_input_interface = 
	    STATIC_SYMBOL("ACTIVATE-FOR-GFI-INPUT-INTERFACE",AB_package);
    SET_SYMBOL_FUNCTION(Qactivate_for_gfi_input_interface,
	    STATIC_FUNCTION(activate_for_gfi_input_interface,NIL,FALSE,1,1));
    temp_1 = SYMBOL_FUNCTION(Qactivate_for_gfi_input_interface);
    set_get(Qgfi_input_interface,Qactivate,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qactivate),
	    Qclasses_which_define);
    temp_1 = CONS(Qgfi_input_interface,temp);
    mutate_global_property(Qactivate,temp_1,Qclasses_which_define);
    string_constant_17 = 
	    STATIC_STRING("While activating ~NF, the GFI input file could not be ~\n                opened.  This item is incomplete.");
    Qnupec_catch_up = STATIC_SYMBOL("NUPEC-CATCH-UP",AB_package);
    string_constant_18 = 
	    STATIC_STRING("When using a GFI file format of NUPEC snapshot-with-restart-time ~\n            for ~NF, the scheduler-mode of timing-parameters must be ~\n            NUPEC-catch-up-mode.");
    string_constant_19 = 
	    string_append2(STATIC_STRING("When using a GFI file format of NUPEC snapshot ~\n            for ~NF, the scheduler-mode of timing-parameters must not be ~\n            NUPEC-catch-up-mode.  If the scheduler "),
	    STATIC_STRING("mode is required to be ~\n            NUPEC-catch-up-mode, the GFI file format must be NUPEC ~\n            snapshot-with-restart-time."));
    Qinput_one_shot_when_activated = 
	    STATIC_SYMBOL("INPUT-ONE-SHOT-WHEN-ACTIVATED",AB_package);
    string_constant_20 = 
	    string_append2(STATIC_STRING("When using a GFI file format of NUPEC snapshot for ~NF, the gfi-~\n            input-variables-update-mode attribute must be either \"input when ~\n            activated\" or \"inp"),
	    STATIC_STRING("ut when activated, without interruption\"."));
    Qyes = STATIC_SYMBOL("YES",AB_package);
    string_constant_21 = 
	    STATIC_STRING("When using a GFI file format of NUPEC snapshot for ~NF, the ~\n            ignore-input-base-time attribute must be set to no.");
    Qasynchronous_ignoring_data_server = 
	    STATIC_SYMBOL("ASYNCHRONOUS-IGNORING-DATA-SERVER",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)3L,
	    Qasynchronous_ignoring_data_server,
	    Qinput_one_shot_when_activated,
	    Qinput_one_shot_when_activated_without_interruption);
    Qgfi_input_ignore_data_server_qm = 
	    STATIC_SYMBOL("GFI-INPUT-IGNORE-DATA-SERVER\?",AB_package);
    Qgfi_input_pathname_string_of_stream_qm = 
	    STATIC_SYMBOL("GFI-INPUT-PATHNAME-STRING-OF-STREAM\?",AB_package);
    Qgfi_input_file_stream = STATIC_SYMBOL("GFI-INPUT-FILE-STREAM",AB_package);
    Qgfi_input_file_buffer_position = 
	    STATIC_SYMBOL("GFI-INPUT-FILE-BUFFER-POSITION",AB_package);
    Qgfi_input_file_buffer_available_characters = 
	    STATIC_SYMBOL("GFI-INPUT-FILE-BUFFER-AVAILABLE-CHARACTERS",
	    AB_package);
    Qgfi_input_file_buffer_offset = 
	    STATIC_SYMBOL("GFI-INPUT-FILE-BUFFER-OFFSET",AB_package);
    Qgfi_input_line = STATIC_SYMBOL("GFI-INPUT-LINE",AB_package);
    Qgfi_queue_of_variables_that_need_values = 
	    STATIC_SYMBOL("GFI-QUEUE-OF-VARIABLES-THAT-NEED-VALUES",
	    AB_package);
    Qgfi_input_file_synchronized_qm = 
	    STATIC_SYMBOL("GFI-INPUT-FILE-SYNCHRONIZED\?",AB_package);
    Qgfi_input_g2_time_at_start = 
	    STATIC_SYMBOL("GFI-INPUT-G2-TIME-AT-START",AB_package);
    string_constant_22 = 
	    STATIC_STRING("Couldn\'t open input file ~S for ~NF.");
    string_constant_23 = 
	    STATIC_STRING("The end of the file has been reached in the GFI input file ~S.  ~\n             The GFI Input Interface ~NF will not provide any ~A values.");
    Qon_request_sample_and_hold = 
	    STATIC_SYMBOL("ON-REQUEST-SAMPLE-AND-HOLD",AB_package);
    string_constant_24 = STATIC_STRING("new");
    string_constant_25 = STATIC_STRING("more");
    string_constant_26 = 
	    STATIC_STRING("Can\'t read from ~S for the GFI Input Interface ~NF:  ~A.");
    Qgfi_input_line_length = STATIC_SYMBOL("GFI-INPUT-LINE-LENGTH",AB_package);
    Qgfi_input_line_current_index = 
	    STATIC_SYMBOL("GFI-INPUT-LINE-CURRENT-INDEX",AB_package);
    Qgfi_current_input_designation = 
	    STATIC_SYMBOL("GFI-CURRENT-INPUT-DESIGNATION",AB_package);
    Qgfi_input_spreadsheet_designations = 
	    STATIC_SYMBOL("GFI-INPUT-SPREADSHEET-DESIGNATIONS",AB_package);
    Qgfi_input_base_time = STATIC_SYMBOL("GFI-INPUT-BASE-TIME",AB_package);
    string_constant_27 = STATIC_STRING("event log");
    string_constant_28 = STATIC_STRING("spreadsheet");
    string_constant_29 = STATIC_STRING("NUPEC snapshot");
    string_constant_30 = STATIC_STRING("unknown file format");
    string_constant_31 = 
	    STATIC_STRING("The base time was not found in the ~S GFI file ~S ~\n             for ~NF, where relative time-stamping was specified.");
    string_constant_32 = 
	    STATIC_STRING("Can\'t parse the first line of the ~S GFI file ~S of the GFI ~\n             Input Interface ~NF.");
    string_constant_33 = 
	    STATIC_STRING("Error in reading the time stamp in the ~S GFI ~\n\t     file ~S of the GFI Input Interface ~NF.  Note that the first ~\n\t     line of this file must have an explicit time stamp.");
    string_constant_34 = 
	    STATIC_STRING("Error in parsing the header of the spreadsheet format GFI ~\n\t     file ~S for the GFI Input Interface ~NF.  Invalid variable or parameter ~\n             reference.");
    string_constant_35 = 
	    STATIC_STRING("Error in parsing the header of the spreadsheet format GFI ~\n\t     file ~S for the GFI Input Interface ~NF.  Variable or parameter ~\n             reference not found.");
    string_constant_36 = 
	    STATIC_STRING("Error in parsing the base time of the spreadsheet format GFI ~\n\t     file ~S for the GFI Input Interface ~NF.");
    string_constant_37 = 
	    STATIC_STRING("The spreadsheet format GFI file ~S for the GFI Input ~\n             Interface ~NF should start with ~S.");
    string_constant_38 = 
	    STATIC_STRING("The GFI Input Interface ~NF has received a value for ~ND ~\n\t    but could not find an appropriate variable to store the value.");
    Qgfi_data_service = STATIC_SYMBOL("GFI-DATA-SERVICE",AB_package);
    Qgfi_data_server = STATIC_SYMBOL("GFI-DATA-SERVER",AB_package);
    Qgfi_input_interface_object = 
	    STATIC_SYMBOL("GFI-INPUT-INTERFACE-OBJECT",AB_package);
    Qgfi_input_line_g2_time = STATIC_SYMBOL("GFI-INPUT-LINE-G2-TIME",
	    AB_package);
    Qlong = STATIC_SYMBOL("LONG",AB_package);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    Qon_request = STATIC_SYMBOL("ON-REQUEST",AB_package);
    Qgfi_last_value = STATIC_SYMBOL("GFI-LAST-VALUE",AB_package);
    Qgfi_time_of_last_value_update = 
	    STATIC_SYMBOL("GFI-TIME-OF-LAST-VALUE-UPDATE",AB_package);
    string_constant_39 = 
	    string_append2(STATIC_STRING("The GFI Input Interface ~NF obtained a line containing an illegal ~\n\t\t\t string or symbol for the value of ~ND (~A~A).  The input interface ~\n\t\t\t will be shut down, since the i"),
	    STATIC_STRING("nput file is probably corrupted."));
    string_constant_40 = 
	    string_append2(STATIC_STRING("The GFI Input Interface ~NF could not parse the line ~\n                          ~S, starting at character ~A, ~ND (~A~A).  There is ~\n                          a data type mi"),
	    STATIC_STRING("smatch or an illegal string or symbol."));
    array_constant_5 = STATIC_ARRAY(list_constant_2,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)57344L);
    Qrecord_block_for_tformat = STATIC_SYMBOL("RECORD-BLOCK-FOR-TFORMAT",
	    AB_package);
    string_constant_41 = 
	    STATIC_STRING("The GFI input interface object ~NF could not find a variable");
    array_constant_6 = STATIC_ARRAY(list_constant_2,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)10L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)23L,(SI_Long)57344L);
    string_constant_42 = 
	    STATIC_STRING(" (which has GFI data service and has ~NF as its GFI ~\n\t\tinput interface object)");
    string_constant_43 = 
	    STATIC_STRING(" corresponding to \"~ND\", as specified in the GFI input file ~S.");
    float_constant = STATIC_FLOAT(0.0);
    array_constant_7 = STATIC_ARRAY(list_constant_2,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)39L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)9L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)11L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)12L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)16L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)19L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)20L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)21L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)22L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)23L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)24L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)25L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)28L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)29L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)30L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)31L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)32L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)33L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)34L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)35L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)36L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)37L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)46L,(SI_Long)38L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)47L,(SI_Long)57344L);
    array_constant_8 = STATIC_ARRAY(list_constant_2,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)39L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)9L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)11L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)12L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)16L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)20L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)21L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)22L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)23L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)24L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)25L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)26L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)28L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)29L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)30L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)31L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)32L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)33L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)34L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)35L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)36L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)37L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)46L,(SI_Long)38L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)47L,(SI_Long)57344L);
    Qsynchronize_gfi_input_file = 
	    STATIC_SYMBOL("SYNCHRONIZE-GFI-INPUT-FILE",AB_package);
    string_constant_44 = 
	    STATIC_STRING("The GFI Input Interface ~NF could not parse an input line of ~\n                 event log file ~S.  The line read is ~S.");
    string_constant_45 = 
	    STATIC_STRING("An input line of the spreadsheet file ~S ~\n                 of the GFI Input Interface ~NF ended unexpectedly.  The ~\n                 line read is ~S.");
    string_constant_46 = 
	    STATIC_STRING("Couldn\'t parse an input line of spreadsheet file ~S ~\n                       for the GFI Input Interface ~NF.  The line read ~\n                       is ~S.");
    string_constant_47 = 
	    STATIC_STRING("Error in reading the time stamp from the GFI file ~S for ~\n \t       the GFI Input Interface ~NF:  ~A.");
    SET_SYMBOL_FUNCTION(Qsynchronize_gfi_input_file,
	    STATIC_FUNCTION(synchronize_gfi_input_file,NIL,FALSE,3,3));
    Qdeactivate_for_gfi_input_interface = 
	    STATIC_SYMBOL("DEACTIVATE-FOR-GFI-INPUT-INTERFACE",AB_package);
    SET_SYMBOL_FUNCTION(Qdeactivate_for_gfi_input_interface,
	    STATIC_FUNCTION(deactivate_for_gfi_input_interface,NIL,FALSE,1,1));
    temp_1 = SYMBOL_FUNCTION(Qdeactivate_for_gfi_input_interface);
    set_get(Qgfi_input_interface,Qdeactivate,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeactivate),
	    Qclasses_which_define);
    temp_1 = CONS(Qgfi_input_interface,temp);
    mutate_global_property(Qdeactivate,temp_1,Qclasses_which_define);
    Qreclaim_gfi_last_value_value = 
	    STATIC_SYMBOL("RECLAIM-GFI-LAST-VALUE-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_gfi_last_value_value,
	    STATIC_FUNCTION(reclaim_gfi_last_value_value,NIL,FALSE,2,2));
    mutate_global_property(Qgfi_last_value,
	    SYMBOL_FUNCTION(Qreclaim_gfi_last_value_value),
	    Qslot_value_reclaimer);
    Qdata_server_spec = STATIC_SYMBOL("DATA-SERVER-SPEC",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Qquote,Qgfi);
    Qdata = STATIC_SYMBOL("DATA",AB_package);
    list_constant_7 = STATIC_LIST((SI_Long)2L,Qquote,Qdata);
    Qserver = STATIC_SYMBOL("SERVER",AB_package);
    list_constant_8 = STATIC_LIST((SI_Long)2L,Qquote,Qserver);
    list_constant_9 = STATIC_LIST((SI_Long)3L,list_constant_6,
	    list_constant_7,list_constant_8);
    list_constant_10 = STATIC_LIST((SI_Long)2L,list_constant_9,
	    Qgfi_data_server);
    list_constant_11 = STATIC_CONS(Qdata_server_spec,list_constant_10);
    Qdata_server_map = STATIC_SYMBOL("DATA-SERVER-MAP",AB_package);
    list_constant_12 = STATIC_CONS(Qdata_server_map,list_constant_10);
    list_constant_13 = STATIC_LIST((SI_Long)2L,list_constant_11,
	    list_constant_12);
    add_grammar_rules_function(list_constant_13);
    Qcollect_one_shot_data_for_gfi_data_service = 
	    STATIC_SYMBOL("COLLECT-ONE-SHOT-DATA-FOR-GFI-DATA-SERVICE",
	    AB_package);
    Qbegin_collecting_data_for_gfi_data_service = 
	    STATIC_SYMBOL("BEGIN-COLLECTING-DATA-FOR-GFI-DATA-SERVICE",
	    AB_package);
    Qstop_collecting_data_for_gfi_data_service = 
	    STATIC_SYMBOL("STOP-COLLECTING-DATA-FOR-GFI-DATA-SERVICE",
	    AB_package);
    Qaccept_data_from_gfi_data_service = 
	    STATIC_SYMBOL("ACCEPT-DATA-FROM-GFI-DATA-SERVICE",AB_package);
    Qinitialize_gfi_data_server = 
	    STATIC_SYMBOL("INITIALIZE-GFI-DATA-SERVER",AB_package);
    Qset_external_variable_for_gfi = 
	    STATIC_SYMBOL("SET-EXTERNAL-VARIABLE-FOR-GFI",AB_package);
    Qshut_down_gfi_data_server = STATIC_SYMBOL("SHUT-DOWN-GFI-DATA-SERVER",
	    AB_package);
    Qpost_on_message_board = STATIC_SYMBOL("POST-ON-MESSAGE-BOARD",AB_package);
    Qgfi_requests_accept_data_calls = 
	    STATIC_SYMBOL("GFI-REQUESTS-ACCEPT-DATA-CALLS",AB_package);
    def_data_server(13,Qgfi_data_server,
	    Qcollect_one_shot_data_for_gfi_data_service,
	    Qbegin_collecting_data_for_gfi_data_service,
	    Qstop_collecting_data_for_gfi_data_service,
	    Qaccept_data_from_gfi_data_service,Nil,
	    Qinitialize_gfi_data_server,Qset_external_variable_for_gfi,
	    Qshut_down_gfi_data_server,Qpost_on_message_board,Nil,Nil,
	    Qgfi_requests_accept_data_calls);
    string_constant_48 = 
	    STATIC_STRING("The GFI input interface object ~ND is not active ~\n                        and thus could not supply a value in response ~\n                        to a request by ~NF.");
    string_constant_49 = 
	    string_append2(STATIC_STRING("The GFI input interface object of ~NF, ~ND, is not a GFI ~\n                       Input Interface.  Hence no value could be obtained ~\n                       for the variable "),
	    STATIC_STRING("via the GFI Data Server."));
    string_constant_50 = 
	    STATIC_STRING("The GFI input interface object of ~NF, ~ND, does ~\n                       not exist.  Hence no value could be ~\n\t\t       obtained for it via the GFI Data Server.");
    string_constant_51 = 
	    STATIC_STRING("The GFI input interface object of ~NF has not yet ~\n \t\t       been specified.  Hence no value could be obtained ~\n                       for it via the GFI Data Server.");
    string_constant_52 = 
	    STATIC_STRING("The variable ~NF has not been given the gfi-data-service ~\n           superior class and so it may not have GFI as its data server.");
    SET_SYMBOL_FUNCTION(Qcollect_one_shot_data_for_gfi_data_service,
	    STATIC_FUNCTION(collect_one_shot_data_for_gfi_data_service,NIL,
	    FALSE,1,1));
    string_constant_53 = 
	    STATIC_STRING("The variable ~NF has not been given the gfi-data-service ~\n             superior class and so it may not have GFI as its data server.");
    SET_SYMBOL_FUNCTION(Qbegin_collecting_data_for_gfi_data_service,
	    STATIC_FUNCTION(begin_collecting_data_for_gfi_data_service,NIL,
	    FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qstop_collecting_data_for_gfi_data_service,
	    STATIC_FUNCTION(stop_collecting_data_for_gfi_data_service,NIL,
	    FALSE,1,1));
    string_constant_54 = 
	    STATIC_STRING("a designation in the GFI Output Interface");
    string_constant_55 = 
	    string_append2(STATIC_STRING("The GFI Output Interface ~NF found a variable or ~\n                         parameter, ~A, which matches ~A.  However, when the ~\n                         GFI Output Interface"),
	    STATIC_STRING(" started ~\n\t\t\t to output to the file ~S, the variable did not match ~\n\t\t\t the desgnation.  The value of this variable or ~\n\t\t\t parameter will be ignored by GFI."));
    string_constant_56 = 
	    STATIC_STRING("NUPEC Snaphot Input for ~NF has completed.");
    string_constant_57 = 
	    STATIC_STRING("GFI Input Interface for ~NF has completed.  There ~\n                        remain unread values with future timestamps in file ~S.");
    string_constant_58 = 
	    STATIC_STRING("NUPEC Snaphot Output for ~NF has completed.");
    string_constant_59 = 
	    STATIC_STRING("GFI Output Interface for ~NF, using file ~S, has completed.");
    string_constant_60 = 
	    STATIC_STRING("GFI Input Interface for ~NF has completed. ~\n                              There remain unread values with future timestamps ~\n                              in file ~S.");
    SET_SYMBOL_FUNCTION(Qaccept_data_from_gfi_data_service,
	    STATIC_FUNCTION(accept_data_from_gfi_data_service,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qgfi_requests_accept_data_calls,
	    STATIC_FUNCTION(gfi_requests_accept_data_calls,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qinitialize_gfi_data_server,
	    STATIC_FUNCTION(initialize_gfi_data_server,NIL,FALSE,0,0));
    string_constant_61 = 
	    string_append2(STATIC_STRING("An attempt was made to set the external value of the variable ~NF, ~\n     which gets data service through the GFI Data Server, to the value ~\n     ~NV.  The set operation is n"),
	    STATIC_STRING("ot allowed within this data server."));
    SET_SYMBOL_FUNCTION(Qset_external_variable_for_gfi,
	    STATIC_FUNCTION(set_external_variable_for_gfi,NIL,FALSE,3,3));
    SET_SYMBOL_FUNCTION(Qshut_down_gfi_data_server,
	    STATIC_FUNCTION(shut_down_gfi_data_server,NIL,FALSE,0,0));
    Qnever = STATIC_SYMBOL("NEVER",AB_package);
    array_constant_9 = STATIC_ARRAY(list_constant_2,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)15L,(SI_Long)57344L);
    array_constant_10 = STATIC_ARRAY(list_constant_2,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)57344L);
    Qg2 = STATIC_SYMBOL("G2",AB_package);
    string_constant_62 = 
	    STATIC_STRING("NUPEC Snapshot input has been stopped!  Error ~\n                             while resetting the G2 time to the NUPEC snapshot ~\n                             time.");
    array_constant_11 = STATIC_ARRAY(list_constant_2,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)10L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)11L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)12L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)14L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)17L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)20L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)21L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)22L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)25L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)27L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)28L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)29L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)30L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)31L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)32L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)33L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)34L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)35L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)36L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)37L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)38L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)39L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)40L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)46L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)47L,(SI_Long)57344L);
    string_constant_63 = 
	    STATIC_STRING("  The snapshot time is too far into the past.  ~\n                                This value cannot be represented internally as ~\n                                an integer.");
    string_constant_64 = 
	    STATIC_STRING("NUPEC Snapshot input has been stopped!");
    Qgraph = STATIC_SYMBOL("GRAPH",AB_package);
    string_constant_65 = 
	    STATIC_STRING("Error while reading the snapshot file ~S for the GFI input ~\n          object ~NF.  A variable or parameter reference is missing.");
    string_constant_66 = 
	    STATIC_STRING("Error while reading the snapshot file ~S for the GFI input ~\n             object ~NF.  The variable or parameter ~ND does not exist.");
    string_constant_67 = 
	    STATIC_STRING("Error while reading the snapshot file ~S for the GFI input ~\n             object ~NF.  The object ~ND is not a variable or parameter.");
    string_constant_68 = 
	    STATIC_STRING("Error while reading the snapshot file ~S for the GFI input ~\n                object ~NF.  Could not locate a valid variable or parameter ~\n                history count.");
    string_constant_69 = 
	    STATIC_STRING("Error while reading the snapshot file ~S for the GFI ~\n                   input object ~NF.  There should be ~D history values for ~ND.");
    Qsupplied = STATIC_SYMBOL("SUPPLIED",AB_package);
    string_constant_70 = 
	    STATIC_STRING("Missing a time-stamp for ~ND while reading from the ~\n              file ~S for the GFI input object ~NF.");
    string_constant_71 = 
	    STATIC_STRING("Incorrect time-stamp for ~ND while reading from the ~\n                      file ~S for the GFI input object ~NF.");
    Qno_value = STATIC_SYMBOL("NO-VALUE",AB_package);
    string_constant_72 = 
	    STATIC_STRING("Error while reading the snapshot file ~S for the GFI ~\n              input object ~NF.  A value is missing for ~ND.");
    string_constant_73 = 
	    STATIC_STRING("Error while reading the snapshot file ~S for the GFI ~\n                      input object ~NF.  Incorrect value for ~ND.");
    string_constant_74 = 
	    STATIC_STRING("Error while reading from the Snapshot file ~S for the ~\n              GFI input object ~NF.  Future time-stamp for ~ND.");
    string_constant_75 = 
	    STATIC_STRING("Error while reading from the Snapshot file ~S for ~\n                          the GFI input object ~NF.  Future time-stamp for ~ND.");
    Qtext_conversion_style = STATIC_SYMBOL("TEXT-CONVERSION-STYLE",AB_package);
    Qgfi_input_file_buffer = STATIC_SYMBOL("GFI-INPUT-FILE-BUFFER",AB_package);
    Qunicode = STATIC_SYMBOL("UNICODE",AB_package);
    Qunicode_byte_swapped = STATIC_SYMBOL("UNICODE-BYTE-SWAPPED",AB_package);
    Qunicode_ucs_2 = STATIC_SYMBOL("UNICODE-UCS-2",AB_package);
    Qunicode_ucs_2_byte_swapped = 
	    STATIC_SYMBOL("UNICODE-UCS-2-BYTE-SWAPPED",AB_package);
}
