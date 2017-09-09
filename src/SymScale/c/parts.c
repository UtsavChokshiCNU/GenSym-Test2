/* parts.c
 * Input file:  parts.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "parts.h"


/* MAKE-PART-DESCRIPTION */
Object make_part_description(part_description_type,part_description_features)
    Object part_description_type, part_description_features;
{
    x_note_fn_call(170,0);
    return slot_value_cons_1(part_description_type,part_description_features);
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_part_stack_conses, Qavailable_part_stack_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_part_stack_conses_tail, Qavailable_part_stack_conses_tail);

Object Available_part_stack_conses_vector = UNBOUND;

Object Available_part_stack_conses_tail_vector = UNBOUND;

Object Part_stack_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Part_stack_cons_counter, Qpart_stack_cons_counter);

/* OUTSTANDING-PART-STACK-CONSES */
Object outstanding_part_stack_conses()
{
    Object temp;

    x_note_fn_call(170,1);
    temp = FIXNUM_MINUS(Part_stack_cons_counter,
	    length(Available_part_stack_conses));
    return VALUES_1(temp);
}

/* PART-STACK-CONS-MEMORY-USAGE */
Object part_stack_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(170,2);
    temp = FIXNUM_TIMES(Part_stack_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-PART-STACK-CONS-POOL */
Object replenish_part_stack_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(170,3);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qpart_stack_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_part_stack_conses_vector,
		IFIX(Current_thread_index))) {
	svref_arg_1 = Available_part_stack_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_part_stack_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_part_stack_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_part_stack_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Part_stack_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qpart_stack;         /* part-stack */

/* PART-STACK-CONS-1 */
Object part_stack_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(170,4);
    new_cons = ISVREF(Available_part_stack_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_part_stack_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_part_stack_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_part_stack_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-PART-STACK-LIST-POOL */
Object replenish_part_stack_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(170,5);
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
    if (ISVREF(Available_part_stack_conses_vector,
		IFIX(Current_thread_index))) {
	svref_arg_1 = Available_part_stack_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_part_stack_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_part_stack_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_part_stack_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qpart_stack_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-PART-STACK-LIST-1 */
Object make_part_stack_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(170,6);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_part_stack_conses_vector,
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
	replenish_part_stack_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_part_stack_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_part_stack_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_part_stack_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_part_stack_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_part_stack_conses_tail_vector;
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

/* PART-STACK-LIST-2 */
Object part_stack_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(170,7);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_part_stack_conses_vector,
	    IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_part_stack_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_part_stack_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qpart_stack);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_part_stack_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_part_stack_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_part_stack_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_part_stack_conses_tail_vector;
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

/* PART-STACK-LIST-3 */
Object part_stack_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(170,8);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_part_stack_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_part_stack_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_part_stack_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qpart_stack);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_part_stack_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_part_stack_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_part_stack_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_part_stack_conses_tail_vector;
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

/* PART-STACK-LIST-4 */
Object part_stack_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(170,9);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_part_stack_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_part_stack_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_part_stack_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qpart_stack);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_part_stack_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_part_stack_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_part_stack_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_part_stack_conses_tail_vector;
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

/* PART-STACK-LIST-TRACE-HOOK */
Object part_stack_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(170,10);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-PART-STACK-CONSES-1 */
Object copy_tree_using_part_stack_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(170,11);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_part_stack_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_part_stack_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_part_stack_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_part_stack_cons_pool();
	temp_1 = copy_tree_using_part_stack_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_part_stack_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_part_stack_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_part_stack_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_part_stack_cons_pool();
	temp_1 = 
		copy_tree_using_part_stack_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
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

/* COPY-LIST-USING-PART-STACK-CONSES-1 */
Object copy_list_using_part_stack_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(170,12);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_part_stack_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_part_stack_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_part_stack_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_part_stack_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_part_stack_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_part_stack_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_part_stack_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_part_stack_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
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

/* RECLAIM-PART-STACK-CONS-1 */
Object reclaim_part_stack_cons_1(part_stack_cons)
    Object part_stack_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(170,13);
    inline_note_reclaim_cons(part_stack_cons,Qpart_stack);
    if (ISVREF(Available_part_stack_conses_tail_vector,
	    IFIX(Current_thread_index))) {
	temp = ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = part_stack_cons;
	temp = Available_part_stack_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = part_stack_cons;
    }
    else {
	temp = Available_part_stack_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = part_stack_cons;
	temp = Available_part_stack_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = part_stack_cons;
    }
    M_CDR(part_stack_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-PART-STACK-LIST-1 */
Object reclaim_part_stack_list_1(part_stack_list)
    Object part_stack_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(170,14);
    if (part_stack_list) {
	last_1 = part_stack_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qpart_stack);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = part_stack_list;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = part_stack_list;
	    temp = Available_part_stack_conses_tail_vector;
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

/* RECLAIM-PART-STACK-LIST*-1 */
Object reclaim_part_stack_list_star_1(part_stack_list)
    Object part_stack_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(170,15);
    if (CONSP(part_stack_list)) {
	temp = last(part_stack_list,_);
	M_CDR(temp) = Nil;
	if (part_stack_list) {
	    last_1 = part_stack_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qpart_stack);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qpart_stack);
	    if (ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_part_stack_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = part_stack_list;
		temp = Available_part_stack_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_part_stack_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = part_stack_list;
		temp = Available_part_stack_conses_tail_vector;
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

/* RECLAIM-PART-STACK-TREE-1 */
Object reclaim_part_stack_tree_1(tree)
    Object tree;
{
    Object e, e2, part_stack_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(170,16);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_part_stack_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		part_stack_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(part_stack_cons,Qpart_stack);
		if (EQ(part_stack_cons,e))
		    goto end_1;
		else if ( !TRUEP(part_stack_cons))
		    goto end_1;
		else
		    part_stack_cons = CDR(part_stack_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_part_stack_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_part_stack_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_part_stack_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_part_stack_conses_tail_vector;
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

/* DELETE-PART-STACK-ELEMENT-1 */
Object delete_part_stack_element_1(element,part_stack_list)
    Object element, part_stack_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(170,17);
    if (part_stack_list) {
	if (EQ(element,M_CAR(part_stack_list))) {
	    temp = CDR(part_stack_list);
	    inline_note_reclaim_cons(part_stack_list,Qpart_stack);
	    if (ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_part_stack_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = part_stack_list;
		temp_1 = Available_part_stack_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = part_stack_list;
	    }
	    else {
		temp_1 = Available_part_stack_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = part_stack_list;
		temp_1 = Available_part_stack_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = part_stack_list;
	    }
	    M_CDR(part_stack_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = part_stack_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qpart_stack);
		if (ISVREF(Available_part_stack_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = 
			    ISVREF(Available_part_stack_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_part_stack_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_part_stack_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_part_stack_conses_tail_vector;
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
	    temp = part_stack_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-PART-STACK-CONS-1 */
Object delete_part_stack_cons_1(part_stack_cons,part_stack_list)
    Object part_stack_cons, part_stack_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(170,18);
    if (EQ(part_stack_cons,part_stack_list))
	temp = CDR(part_stack_list);
    else {
	l_trailer_qm = Nil;
	l = part_stack_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,part_stack_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = part_stack_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_part_stack_cons_1(part_stack_cons);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Working_on_annotated_frame, Qworking_on_annotated_frame);

DEFINE_VARIABLE_WITH_SYMBOL(Current_annotated_frame, Qcurrent_annotated_frame);

DEFINE_VARIABLE_WITH_SYMBOL(Scanning_subparts_of_block, Qscanning_subparts_of_block);

DEFINE_VARIABLE_WITH_SYMBOL(Part_feature_recall_stack, Qpart_feature_recall_stack);

DEFINE_VARIABLE_WITH_SYMBOL(Stack_of_current_part_descriptions, Qstack_of_current_part_descriptions);

DEFINE_VARIABLE_WITH_SYMBOL(Maintain_stack_of_current_part_descriptions_p, Qmaintain_stack_of_current_part_descriptions_p);

DEFINE_VARIABLE_WITH_SYMBOL(Part_exceptions_from_parents, Qpart_exceptions_from_parents);

DEFINE_VARIABLE_WITH_SYMBOL(Projection, Qprojection);

DEFINE_VARIABLE_WITH_SYMBOL(Projection_mode, Qprojection_mode);

DEFINE_VARIABLE_WITH_SYMBOL(Projection_focus_method, Qprojection_focus_method);

DEFINE_VARIABLE_WITH_SYMBOL(Projection_focus_annotation, Qprojection_focus_annotation);

DEFINE_VARIABLE_WITH_SYMBOL(Projection_focus_cell_index, Qprojection_focus_cell_index);

DEFINE_VARIABLE_WITH_SYMBOL(Projection_focus_cell_new_cached_value, Qprojection_focus_cell_new_cached_value);

DEFINE_VARIABLE_WITH_SYMBOL(Projection_drawing, Qprojection_drawing);

DEFINE_VARIABLE_WITH_SYMBOL(Projection_funcall_on_focus, Qprojection_funcall_on_focus);

DEFINE_VARIABLE_WITH_SYMBOL(Current_projection_function_for_funcall, Qcurrent_projection_function_for_funcall);

DEFINE_VARIABLE_WITH_SYMBOL(Projection_tracking, Qprojection_tracking);

DEFINE_VARIABLE_WITH_SYMBOL(Current_tracking_x_in_window, Qcurrent_tracking_x_in_window);

DEFINE_VARIABLE_WITH_SYMBOL(Current_tracking_y_in_window, Qcurrent_tracking_y_in_window);

DEFINE_VARIABLE_WITH_SYMBOL(Current_tracking_subcomponent, Qcurrent_tracking_subcomponent);

DEFINE_VARIABLE_WITH_SYMBOL(Create_subpart_upon_tracking_p, Qcreate_subpart_upon_tracking_p);

DEFINE_VARIABLE_WITH_SYMBOL(Projection_update_dependencies, Qprojection_update_dependencies);

DEFINE_VARIABLE_WITH_SYMBOL(Current_kind_of_change, Qcurrent_kind_of_change);

DEFINE_VARIABLE_WITH_SYMBOL(Current_thing_changed, Qcurrent_thing_changed);

DEFINE_VARIABLE_WITH_SYMBOL(Projection_computing_path_of_focus, Qprojection_computing_path_of_focus);

DEFINE_VARIABLE_WITH_SYMBOL(Projection_focus_path, Qprojection_focus_path);

DEFINE_VARIABLE_WITH_SYMBOL(Parts_of_annotated_frames_currently_erased, Qparts_of_annotated_frames_currently_erased);

/* ERASE-ENTIRE-ANNOTATED-BLOCK */
Object erase_entire_annotated_block(block)
    Object block;
{
    Object blocks_already_erased;

    x_note_fn_call(170,19);
    blocks_already_erased = Parts_of_annotated_frames_currently_erased;
    Parts_of_annotated_frames_currently_erased = 
	    part_stack_cons_1(part_stack_cons_1(block,Nil),
	    Parts_of_annotated_frames_currently_erased);
    if ( !TRUEP(assq_function(block,blocks_already_erased)))
	return update_images_of_block(block,T,T);
    else
	return VALUES_1(Nil);
}

/* REDRAW-ENTIRE-ANNOTATED-BLOCK */
Object redraw_entire_annotated_block()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;
    Object erase_record, block;

    x_note_fn_call(170,20);
    part_stack_pop_store = Nil;
    cons_1 = Parts_of_annotated_frames_currently_erased;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Parts_of_annotated_frames_currently_erased = next_cons;
    erase_record = part_stack_pop_store;
    block = FIRST(erase_record);
    reclaim_part_stack_cons_1(erase_record);
    if ( !TRUEP(assq_function(block,
	    Parts_of_annotated_frames_currently_erased)))
	return update_images_of_block(block,Nil,T);
    else
	return VALUES_1(Nil);
}

static Object Qannotation;         /* annotation */

/* ERASE-PART-OF-BLOCK */
Object erase_part_of_block(frame_containing_part,part)
    Object frame_containing_part, part;
{
    Object projection_focus_method, projection_focus_annotation;
    Declare_special(2);
    Object result;

    x_note_fn_call(170,21);
    projection_focus_method = Qannotation;
    projection_focus_annotation = part;
    PUSH_SPECIAL_WITH_SYMBOL(Projection_focus_annotation,Qprojection_focus_annotation,projection_focus_annotation,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Projection_focus_method,Qprojection_focus_method,projection_focus_method,
	      0);
	result = erase_entire_annotated_block(frame_containing_part);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* REDRAW-PART-OF-BLOCK */
Object redraw_part_of_block(part)
    Object part;
{
    Object projection_focus_method, projection_focus_annotation;
    Declare_special(2);
    Object result;

    x_note_fn_call(170,22);
    projection_focus_method = Qannotation;
    projection_focus_annotation = part;
    PUSH_SPECIAL_WITH_SYMBOL(Projection_focus_annotation,Qprojection_focus_annotation,projection_focus_annotation,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Projection_focus_method,Qprojection_focus_method,projection_focus_method,
	      0);
	result = redraw_entire_annotated_block();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Currently_supressing_part_highlighting, Qcurrently_supressing_part_highlighting);

static Object Qhighlighted_qm;     /* highlighted? */

/* HIGHLIGHT-PART-OF-FRAME */
Object highlight_part_of_frame(frame_containing_annotation,part)
    Object frame_containing_annotation, part;
{
    Object projection_focus_method, projection_focus_annotation;
    Declare_special(2);
    Object result;

    x_note_fn_call(170,23);
    if ( !TRUEP(Currently_supressing_part_highlighting)) {
	projection_focus_method = Qannotation;
	projection_focus_annotation = part;
	PUSH_SPECIAL_WITH_SYMBOL(Projection_focus_annotation,Qprojection_focus_annotation,projection_focus_annotation,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Projection_focus_method,Qprojection_focus_method,projection_focus_method,
		  0);
	    erase_entire_annotated_block(frame_containing_annotation);
	    set_simple_part_feature(part,Qhighlighted_qm,T);
	    result = redraw_entire_annotated_block();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* UNHIGHLIGHT-PART-OF-FRAME */
Object unhighlight_part_of_frame(frame_containing_annotation,part)
    Object frame_containing_annotation, part;
{
    Object current_annotated_frame, projection_focus_method;
    Object projection_focus_annotation;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(3);
    Object result;

    x_note_fn_call(170,24);
    SAVE_STACK();
    if (get_simple_part_feature(part,Qhighlighted_qm)) {
	LOCK(Working_on_annotated_frame);
	if (PUSH_UNWIND_PROTECT(0)) {
	    current_annotated_frame = frame_containing_annotation;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_annotated_frame,Qcurrent_annotated_frame,current_annotated_frame,
		    2);
	      projection_focus_method = Qannotation;
	      projection_focus_annotation = part;
	      PUSH_SPECIAL_WITH_SYMBOL(Projection_focus_annotation,Qprojection_focus_annotation,projection_focus_annotation,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Projection_focus_method,Qprojection_focus_method,projection_focus_method,
			0);
		  erase_entire_annotated_block(frame_containing_annotation);
		  remove_simple_part_feature(part,Qhighlighted_qm);
		  SAVE_VALUES(redraw_entire_annotated_block());
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	POP_UNWIND_PROTECT(0);
	UNLOCK(Working_on_annotated_frame);
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

Object User_spellings_of_internal_symbol_prop = UNBOUND;

Object Internal_spellings_of_user_symbol_prop = UNBOUND;

static Object Qinternal_spellings_of_user_symbol;  /* internal-spellings-of-user-symbol */

static Object Quser_spellings_of_internal_symbol;  /* user-spellings-of-internal-symbol */

/* DEF-USER-SPELLING */
Object def_user_spelling(internal_symbol,context,external_symbol)
    Object internal_symbol, context, external_symbol;
{
    Object temp;

    x_note_fn_call(170,25);
    temp = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(external_symbol),
	    Qinternal_spellings_of_user_symbol),context,internal_symbol);
    mutate_global_property(external_symbol,temp,
	    Qinternal_spellings_of_user_symbol);
    temp = 
	    set_getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(internal_symbol),
	    Quser_spellings_of_internal_symbol),context,external_symbol);
    mutate_global_property(internal_symbol,temp,
	    Quser_spellings_of_internal_symbol);
    return VALUES_1(external_symbol);
}

/* GET-USER-SPELLING */
Object get_user_spelling(internal_symbol,context)
    Object internal_symbol, context;
{
    Object temp;

    x_note_fn_call(170,26);
    temp = 
	    getf(getfq_function_no_default(INLINE_SYMBOL_PLIST(internal_symbol),
	    Quser_spellings_of_internal_symbol),context,_);
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(internal_symbol);
}

/* GET-INTERNAL-SPELLING */
Object get_internal_spelling(user_symbol,context)
    Object user_symbol, context;
{
    Object result_qm;

    x_note_fn_call(170,27);
    result_qm = getfq_function_no_default(INLINE_SYMBOL_PLIST(user_symbol),
	    Qinternal_spellings_of_user_symbol);
    if (memq_function(context,result_qm))
	return getf(result_qm,context,_);
    else
	return VALUES_1(user_symbol);
}

static Object Qget_internal_spelling;  /* get-internal-spelling */

/* FIX-UP-PARSE-UPON-REDUCTION */
Object fix_up_parse_upon_reduction(parse)
    Object parse;
{
    Object temp, temp_1;

    x_note_fn_call(170,28);
    if (ATOM(parse))
	return VALUES_1(parse);
    else {
	temp = FIRST(parse);
	if (EQ(temp,Qget_internal_spelling))
	    return get_internal_spelling(SECOND(parse),THIRD(parse));
	else {
	    temp_1 = fix_up_parse_upon_reduction(CAR(parse));
	    M_CAR(parse) = temp_1;
	    temp_1 = fix_up_parse_upon_reduction(CDR(parse));
	    M_CDR(parse) = temp_1;
	    return VALUES_1(parse);
	}
    }
}

static Object Qpart_feature;       /* part-feature */

static Object Qconstant;           /* constant */

static Object Qset_simple_part_feature;  /* set-simple-part-feature */

static Object Qcopy_for_slot_value;  /* copy-for-slot-value */

/* REDUCE-ANNOTATION */
Object reduce_annotation(parse)
    Object parse;
{
    Object part_description_to_annotate, external_part_feature;
    Object external_desired_value, internal_part_feature;
    Object internal_desired_value, parse_after_reduction;

    x_note_fn_call(170,29);
    part_description_to_annotate = FIRST(parse);
    external_part_feature = SECOND(parse);
    external_desired_value = THIRD(parse);
    internal_part_feature = get_internal_spelling(external_part_feature,
	    Qpart_feature);
    internal_desired_value = SYMBOLP(external_desired_value) ? 
	    get_internal_spelling(external_desired_value,Qconstant) : 
	    external_desired_value;
    parse_after_reduction = phrase_list_4(Qset_simple_part_feature,
	    part_description_to_annotate,phrase_list_2(Qquote,
	    internal_part_feature),phrase_list_2(Qcopy_for_slot_value,
	    phrase_list_2(Qquote,internal_desired_value)));
    return VALUES_1(parse_after_reduction);
}

static Object Qcompile_computed_part_feature;  /* compile-computed-part-feature */

/* REDUCE-ANNOTATION-WITH-EXPRESSION */
Object reduce_annotation_with_expression(parse)
    Object parse;
{
    Object part_description_to_annotate, external_part_feature;
    Object external_desired_value, internal_part_feature;
    Object internal_desired_value, parse_after_reduction;

    x_note_fn_call(170,30);
    part_description_to_annotate = FIRST(parse);
    external_part_feature = SECOND(parse);
    external_desired_value = THIRD(parse);
    internal_part_feature = ATOM(external_part_feature) ? 
	    get_internal_spelling(external_part_feature,Qpart_feature) : 
	    external_part_feature;
    internal_desired_value = SYMBOLP(external_desired_value) ? 
	    get_internal_spelling(external_desired_value,Qconstant) : 
	    external_desired_value;
    parse_after_reduction = phrase_list_4(Qset_simple_part_feature,
	    part_description_to_annotate,phrase_list_2(Qquote,
	    internal_part_feature),ATOM(internal_desired_value) ? 
	    phrase_list_2(Qquote,internal_desired_value) : 
	    phrase_list_2(Qcompile_computed_part_feature,
	    phrase_list_2(Qquote,internal_desired_value)));
    return VALUES_1(parse_after_reduction);
}

Object Maximum_number_of_part_features = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Part_feature_indexes, Qpart_feature_indexes);

Object Part_feature_index_prop = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Last_part_features_index_allocated, Qlast_part_features_index_allocated);

static Object Qpart_feature_index;  /* part-feature-index */

/* GET-OR-MAKE-PART-FEATURE-INDEX */
Object get_or_make_part_feature_index(part_feature)
    Object part_feature;
{
    Object temp, temp_1, svref_arg_2;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(170,31);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(part_feature),
	    Qpart_feature_index);
    if (temp)
	return VALUES_1(temp);
    else {
	temp_1 = FIXNUM_ADD1(Last_part_features_index_allocated);
	Last_part_features_index_allocated = temp_1;
	if (ISVREF(Part_feature_indexes,
		IFIX(Last_part_features_index_allocated))) {
	    i = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(Maximum_number_of_part_features);
	  next_loop:
	    if (i >= ab_loop_bind_)
		goto end_loop;
	    if ( !TRUEP(ISVREF(Part_feature_indexes,i))) {
		Last_part_features_index_allocated = FIX(i);
		goto end_1;
	    }
	    i = i + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    error((SI_Long)1L,
		    "No additional part-feature indexes are available.");
	    Last_part_features_index_allocated = Qnil;
	  end_1:;
	}
	temp_1 = Part_feature_indexes;
	svref_arg_2 = Last_part_features_index_allocated;
	SVREF(temp_1,svref_arg_2) = part_feature;
	return mutate_global_property(part_feature,
		Last_part_features_index_allocated,Qpart_feature_index);
    }
}

Object Part_type_description_prop = UNBOUND;

/* MAKE-PART-TYPE-DESCRIPTION */
Object make_part_type_description(part_type_name,part_type_features,
	    part_type_user_spelling,part_type_includes,
	    part_type_hidden_features,
	    part_type_allow_individual_exceptions_in_parents,
	    part_type_allow_defaulting_in_parents,part_type_semantic_check)
    Object part_type_name, part_type_features, part_type_user_spelling;
    Object part_type_includes, part_type_hidden_features;
    Object part_type_allow_individual_exceptions_in_parents;
    Object part_type_allow_defaulting_in_parents, part_type_semantic_check;
{
    Object temp;

    x_note_fn_call(170,32);
    temp = CONS(part_type_semantic_check,Nil);
    temp = CONS(part_type_allow_defaulting_in_parents,temp);
    temp = CONS(part_type_allow_individual_exceptions_in_parents,temp);
    temp = CONS(part_type_hidden_features,temp);
    temp = CONS(part_type_includes,temp);
    temp = CONS(part_type_user_spelling,temp);
    temp = CONS(part_type_features,temp);
    return VALUES_1(CONS(part_type_name,temp));
}

static Object Qpart_type_description;  /* part-type-description */

/* PART-FEATURE-DESCRIPTION */
Object part_feature_description(part_type,part_feature)
    Object part_type, part_feature;
{
    Object list_1, part_type_description, temp, included_part_type;
    Object ab_loop_list_, description;

    x_note_fn_call(170,33);
    list_1 = SYMBOL_PLIST(part_type);
  next_loop:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Qpart_type_description))
	goto end_loop;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop;
  end_loop:
    part_type_description = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    temp = CDR(part_type_description);
    list_1 = CAR(temp);
  next_loop_1:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),part_feature))
	goto end_loop_1;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_1;
  end_loop_1:
    temp = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    if (temp)
	return VALUES_1(temp);
    else {
	included_part_type = Nil;
	temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(part_type),
		Qpart_type_description);
	temp = CDDDR(temp);
	ab_loop_list_ = CAR(temp);
	description = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	included_part_type = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	description = part_feature_description(included_part_type,
		part_feature);
	if (description)
	    return VALUES_1(description);
	goto next_loop_2;
      end_loop_2:
	return VALUES_1(Qnil);
    }
}

static Object Quser_spelling;      /* user-spelling */

static Object Qhidden_features;    /* hidden-features */

static Object Qallow_individual_exceptions_in_parents;  /* allow-individual-exceptions-in-parents */

static Object Qallow_defaulting_in_parents;  /* allow-defaulting-in-parents */

static Object Qpart_type;          /* part-type */

/* DEF-PART-TYPE-1 */
Object def_part_type_1(part_type_name,includes,args)
    Object part_type_name, includes, args;
{
    Object user_spelling_specified_p, user_spelling_qm;
    Object hidden_features_specified_p, hidden_features_qm;
    Object allow_individual_exceptions_in_parents_specified_p;
    Object allow_individual_exceptions_in_parents;
    Object allow_defaulting_in_parents_specified_p;
    Object allow_defaulting_in_parents;

    x_note_fn_call(170,34);
    user_spelling_specified_p = assq_function(Quser_spelling,args);
    user_spelling_qm = SECOND(user_spelling_specified_p);
    hidden_features_specified_p = assq_function(Qhidden_features,args);
    hidden_features_qm = REST(hidden_features_specified_p);
    allow_individual_exceptions_in_parents_specified_p = 
	    assq_function(Qallow_individual_exceptions_in_parents,args);
    allow_individual_exceptions_in_parents = 
	    allow_individual_exceptions_in_parents_specified_p ? 
	    SECOND(allow_individual_exceptions_in_parents_specified_p) : T;
    allow_defaulting_in_parents_specified_p = 
	    assq_function(Qallow_defaulting_in_parents,args);
    allow_defaulting_in_parents = allow_defaulting_in_parents_specified_p ?
	     SECOND(allow_defaulting_in_parents_specified_p) : T;
    if (user_spelling_qm)
	def_user_spelling(part_type_name,Qpart_type,user_spelling_qm);
    return mutate_global_property(part_type_name,
	    make_part_type_description(part_type_name,Nil,
	    user_spelling_specified_p ? user_spelling_qm : part_type_name,
	    includes,hidden_features_qm,
	    allow_individual_exceptions_in_parents,
	    allow_defaulting_in_parents,Nil),Qpart_type_description);
}

/* MAKE-PART-FEATURE-DESCRIPTION */
Object make_part_feature_description(part_feature_name,
	    part_feature_means_of_scanning,part_feature_type,
	    part_feature_user_spelling,part_feature_user_visible_qm)
    Object part_feature_name, part_feature_means_of_scanning;
    Object part_feature_type, part_feature_user_spelling;
    Object part_feature_user_visible_qm;
{
    Object temp;

    x_note_fn_call(170,35);
    temp = CONS(part_feature_user_visible_qm,Nil);
    temp = CONS(part_feature_user_spelling,temp);
    temp = CONS(part_feature_type,temp);
    temp = CONS(part_feature_means_of_scanning,temp);
    return VALUES_1(CONS(part_feature_name,temp));
}

DEFINE_VARIABLE_WITH_SYMBOL(Part_feature_enter_methods, Qpart_feature_enter_methods);

DEFINE_VARIABLE_WITH_SYMBOL(Part_feature_exit_methods, Qpart_feature_exit_methods);

/* PART-TYPE-DESCENDANT-PART-TYPES */
Object part_type_descendant_part_types(part_type)
    Object part_type;
{
    Object temp;

    x_note_fn_call(170,36);
    temp = part_feature_description(part_type,Qsubpart_defaults);
    temp = CDDR(temp);
    temp = CAR(temp);
    return VALUES_1(REST(temp));
}

/* DEF-PART-FEATURE-1 */
Object def_part_feature_1(part_type,feature_name,type,user_spelling,
	    user_visible,enter_feature_routine,exit_feature_routine,
	    means_of_scanning)
    Object part_type, feature_name, type, user_spelling, user_visible;
    Object enter_feature_routine, exit_feature_routine, means_of_scanning;
{
    Object part_feature_index, temp, temp_1, getf_new_value, car_new_value;

    x_note_fn_call(170,37);
    part_feature_index = get_or_make_part_feature_index(feature_name);
    temp = Part_feature_enter_methods;
    SVREF(temp,part_feature_index) = enter_feature_routine;
    temp = Part_feature_exit_methods;
    SVREF(temp,part_feature_index) = exit_feature_routine;
    if (user_spelling)
	def_user_spelling(feature_name,Qpart_feature,user_spelling);
    temp_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(part_type),
	    Qpart_type_description);
    temp = CDR(temp_1);
    getf_new_value = LIST_5(feature_name,list_star(3,enter_feature_routine,
	    exit_feature_routine,means_of_scanning),type,user_spelling,
	    user_visible);
    car_new_value = set_getf(CAR(temp),feature_name,getf_new_value);
    M_CAR(temp) = car_new_value;
    return VALUES_1(getf_new_value);
}

/* SCAN-FEATURE-DOING-NOTHING */
Object scan_feature_doing_nothing(old_value,new_value)
    Object old_value, new_value;
{
    x_note_fn_call(170,38);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Subpart_defaults, Qsubpart_defaults);

/* ENTER-SUBPART-DEFAULTS */
Object enter_subpart_defaults(new_value)
    Object new_value;
{
    Object part_template, ab_loop_list_, temp;

    x_note_fn_call(170,39);
    Subpart_defaults = new_value;
    part_template = Nil;
    ab_loop_list_ = new_value;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    temp = CDR(ab_loop_list_);
    temp = CAR(temp);
    part_template = CAR(temp);
    enter_part_description(part_template);
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:;
    Part_feature_recall_stack = part_stack_cons_1(Subpart_defaults,
	    Part_feature_recall_stack);
    return VALUES_1(Nil);
}

/* EXIT-SUBPART-DEFAULTS */
Object exit_subpart_defaults()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(170,40);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Subpart_defaults = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Basic_part, Qbasic_part);

DEFINE_VARIABLE_WITH_SYMBOL(Subparts, Qsubparts);

/* ENTER-PART-FEATURE-SUBPARTS */
Object enter_part_feature_subparts(new_value)
    Object new_value;
{
    x_note_fn_call(170,41);
    Part_feature_recall_stack = part_stack_cons_1(Subparts,
	    Part_feature_recall_stack);
    Subparts = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-SUBPARTS */
Object exit_part_feature_subparts()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(170,42);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Subparts = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Subpart_exceptions, Qsubpart_exceptions);

/* ENTER-SUBPART-EXCEPTIONS */
Object enter_subpart_exceptions(new_value)
    Object new_value;
{
    x_note_fn_call(170,43);
    Subpart_exceptions = new_value;
    Part_exceptions_from_parents = part_stack_cons_1(new_value,
	    Part_exceptions_from_parents);
    return VALUES_1(Nil);
}

/* EXIT-SUBPART-EXCEPTIONS */
Object exit_subpart_exceptions()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(170,44);
    part_stack_pop_store = Nil;
    cons_1 = Part_exceptions_from_parents;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_exceptions_from_parents = next_cons;
    Subpart_exceptions = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_part_description, Qcurrent_part_description);

DEFINE_VARIABLE_WITH_SYMBOL(Current_basic_part, Qcurrent_basic_part);

DEFINE_VARIABLE_WITH_SYMBOL(Part_index, Qpart_index);

/* ENTER-PART-FEATURE-PART-INDEX */
Object enter_part_feature_part_index(new_value)
    Object new_value;
{
    x_note_fn_call(170,45);
    Part_feature_recall_stack = part_stack_cons_1(Part_index,
	    Part_feature_recall_stack);
    Part_index = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-PART-INDEX */
Object exit_part_feature_part_index()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(170,46);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Part_index = part_stack_pop_store;
    return VALUES_1(Nil);
}

/* COMPUTE-PART-FEATURE-OF-TYPE-COLOR-OR-METACOLOR-P */
Object compute_part_feature_of_type_color_or_metacolor_p(data)
    Object data;
{
    Object temp;

    x_note_fn_call(170,47);
    temp = evaluated_computed_part_feature_p(data);
    if (temp)
	return VALUES_1(temp);
    else
	return color_or_metacolor_p(data);
}

static Object Qcolor_or_metacolor;  /* color-or-metacolor */

/* COMPUTE-PART-FEATURE-OF-TYPE-COLOR-OR-METACOLOR-TYPE-WRITER */
Object compute_part_feature_of_type_color_or_metacolor_type_writer(x)
    Object x;
{
    x_note_fn_call(170,48);
    return write_computed_part_feature(Qsymbol,Qcolor_or_metacolor,x);
}

/* WORKSPACE-MEASURE-P */
Object workspace_measure_p(x)
    Object x;
{
    Object value;
    double arg, arg_1, arg_2;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(170,49);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	if (slot_value_number_p(x)) {
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(x) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) == (SI_Long)1L)
		value = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(x,(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(x) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) == (SI_Long)1L)
		value = aref1(x,FIX((SI_Long)0L));
	    else
		value = x;
	    if (FIXNUMP(value)) {
		if ((SI_Long)1L <= IFIX(value))
		    result = VALUES_1(IFIX(value) <= (SI_Long)4092L ? T : Nil);
		else
		    result = VALUES_1(Nil);
	    }
	    else {
		arg = 1.0;
		arg_1 = DOUBLE_FLOAT_TO_DOUBLE(value);
		arg_2 = 4092.0;
		if (arg <= arg_1 && arg_1 <= arg_2 &&  
			!inline_nanp_for_comparison(arg) &&  
			!inline_nanp_for_comparison(arg_1))
		    result = VALUES_1( !inline_nanp_for_comparison(arg_2) ?
			     T : Nil);
		else
		    result = VALUES_1(Nil);
	    }
	}
	else
	    result = VALUES_1(Nil);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* SIMPLE-INTERVAL-P */
Object simple_interval_p(x)
    Object x;
{
    Object temp;
    double arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(170,50);
    temp = FIXNUMP(x) ? ((SI_Long)0L < IFIX(x) ? T : Nil) : Qnil;
    if (temp)
	return VALUES_1(temp);
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(x) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) == (SI_Long)1L) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    arg = 0.0;
	    arg_1 = DFLOAT_ISAREF_1(x,(SI_Long)0L);
	    if (arg < arg_1 &&  !inline_nanp_for_comparison(arg))
		result = VALUES_1( !inline_nanp_for_comparison(arg_1) ? T :
			 Nil);
	    else
		result = VALUES_1(Nil);
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant;     /* "~(~D~)" */

static Object string_constant_1;   /* "~(~A~)" */

/* SLOT-VALUE-FLOAT-TYPE-WRITER */
Object slot_value_float_type_writer(x)
    Object x;
{
    Object temp;
    double actual_value, arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(170,51);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	actual_value = DFLOAT_ISAREF_1(x,(SI_Long)0L);
	temp = fround(DOUBLE_TO_DOUBLE_FLOAT(actual_value),_);
	arg = DOUBLE_FLOAT_TO_DOUBLE(temp);
	arg_1 = actual_value;
	if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1))
	    result = tformat(2,string_constant,
		    ltruncate(DOUBLE_TO_DOUBLE_FLOAT(actual_value),_));
	else
	    result = tformat(2,string_constant_1,
		    DOUBLE_TO_DOUBLE_FLOAT(actual_value));
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

static Object string_constant_2;   /* "~A" */

static Object string_constant_3;   /* "true" */

static Object string_constant_4;   /* "false" */

/* BOOLEAN-TYPE-WRITER */
Object boolean_type_writer(x)
    Object x;
{
    x_note_fn_call(170,52);
    return tformat(2,string_constant_2,x ? string_constant_3 : 
	    string_constant_4);
}

DEFINE_VARIABLE_WITH_SYMBOL(Formatted_part, Qformatted_part);

DEFINE_VARIABLE_WITH_SYMBOL(Current_formatted_part, Qcurrent_formatted_part);

static Object Qbackground;         /* background */

static Object Qtext_cell_background_color_qm;  /* text-cell-background-color? */

static Object Qforeground;         /* foreground */

static Object Qtransparent;        /* transparent */

static Object Qcolor_value_vector_index_and_intensity;  /* color-value-vector-index-and-intensity */

/* ENTER-BACKGROUND-COLOR */
Object enter_background_color(compute_part_feature_of_type_color_or_metacolor)
    Object compute_part_feature_of_type_color_or_metacolor;
{
    Object color_qm, svref_arg_1, svref_new_value;

    x_note_fn_call(170,53);
    Part_feature_recall_stack = 
	    part_stack_cons_1(ISVREF(Current_text_box_format,(SI_Long)24L),
	    Part_feature_recall_stack);
    color_qm = 
	    value_of_computed_part_feature(compute_part_feature_of_type_color_or_metacolor,
	    Qbackground);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_text_box_format,
		Qtext_cell_background_color_qm);
    svref_arg_1 = Current_text_box_format;
    svref_new_value = EQ(color_qm,Qforeground) || EQ(color_qm,Qbackground) 
	    || EQ(color_qm,Qtransparent) || 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(color_qm),
	    Qcolor_value_vector_index_and_intensity) || 
	    rgb_color_p(color_qm) ? color_qm : Qbackground;
    SVREF(svref_arg_1,FIX((SI_Long)24L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* EXIT-BACKGROUND-COLOR */
Object exit_background_color()
{
    Object svref_arg_1, part_stack_pop_store, cons_1, next_cons, temp;
    Object svref_arg_2;

    x_note_fn_call(170,54);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_text_box_format,
		Qtext_cell_background_color_qm);
    svref_arg_1 = Current_text_box_format;
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    SVREF(svref_arg_1,FIX((SI_Long)24L)) = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Formatted_part_true_line_color, Qformatted_part_true_line_color);

/* ENTER-PART-FEATURE-LINE-COLOR */
Object enter_part_feature_line_color(new_value)
    Object new_value;
{
    x_note_fn_call(170,55);
    Part_feature_recall_stack = 
	    part_stack_cons_1(Formatted_part_true_line_color,
	    Part_feature_recall_stack);
    Formatted_part_true_line_color = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-LINE-COLOR */
Object exit_part_feature_line_color()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(170,56);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Formatted_part_true_line_color = part_stack_pop_store;
    return VALUES_1(Nil);
}

static Object Qtext_box_border_color_qm;  /* text-box-border-color? */

/* ENTER-PART-FEATURE-BORDER-COLOR */
Object enter_part_feature_border_color(new_value)
    Object new_value;
{
    Object svref_arg_1;

    x_note_fn_call(170,57);
    Part_feature_recall_stack = 
	    part_stack_cons_1(ISVREF(Current_text_box_format,(SI_Long)48L),
	    Part_feature_recall_stack);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_text_box_format,
		Qtext_box_border_color_qm);
    svref_arg_1 = Current_text_box_format;
    SVREF(svref_arg_1,FIX((SI_Long)48L)) = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-BORDER-COLOR */
Object exit_part_feature_border_color()
{
    Object svref_arg_1, part_stack_pop_store, cons_1, next_cons, temp;
    Object svref_arg_2;

    x_note_fn_call(170,58);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_text_box_format,
		Qtext_box_border_color_qm);
    svref_arg_1 = Current_text_box_format;
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    SVREF(svref_arg_1,FIX((SI_Long)48L)) = part_stack_pop_store;
    return VALUES_1(Nil);
}

static Object Qtext_cell_line_color_qm;  /* text-cell-line-color? */

/* ENTER-PART-FEATURE-TEXT-COLOR */
Object enter_part_feature_text_color(new_value)
    Object new_value;
{
    Object svref_arg_1;

    x_note_fn_call(170,59);
    Part_feature_recall_stack = 
	    part_stack_cons_1(ISVREF(Current_text_box_format,(SI_Long)23L),
	    Part_feature_recall_stack);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_text_box_format,
		Qtext_cell_line_color_qm);
    svref_arg_1 = Current_text_box_format;
    SVREF(svref_arg_1,FIX((SI_Long)23L)) = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-TEXT-COLOR */
Object exit_part_feature_text_color()
{
    Object svref_arg_1, part_stack_pop_store, cons_1, next_cons, temp;
    Object svref_arg_2;

    x_note_fn_call(170,60);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_text_box_format,
		Qtext_cell_line_color_qm);
    svref_arg_1 = Current_text_box_format;
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    SVREF(svref_arg_1,FIX((SI_Long)23L)) = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Formatted_part_highlight_flag, Qformatted_part_highlight_flag);

/* ENTER-PART-FEATURE-HIGHLIGHTED? */
Object enter_part_feature_highlighted_qm(new_value)
    Object new_value;
{
    x_note_fn_call(170,61);
    Part_feature_recall_stack = 
	    part_stack_cons_1(Formatted_part_highlight_flag,
	    Part_feature_recall_stack);
    Formatted_part_highlight_flag = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-HIGHLIGHTED? */
Object exit_part_feature_highlighted_qm()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(170,62);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Formatted_part_highlight_flag = part_stack_pop_store;
    return VALUES_1(Nil);
}

static Object Qtext_cell_line_quadding_qm;  /* text-cell-line-quadding? */

/* ENTER-PART-FEATURE-TEXT-ALIGNMENT */
Object enter_part_feature_text_alignment(new_value)
    Object new_value;
{
    Object svref_arg_1;

    x_note_fn_call(170,63);
    Part_feature_recall_stack = 
	    part_stack_cons_1(ISVREF(Current_text_box_format,(SI_Long)39L),
	    Part_feature_recall_stack);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_text_box_format,
		Qtext_cell_line_quadding_qm);
    svref_arg_1 = Current_text_box_format;
    SVREF(svref_arg_1,FIX((SI_Long)39L)) = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-TEXT-ALIGNMENT */
Object exit_part_feature_text_alignment()
{
    Object svref_arg_1, part_stack_pop_store, cons_1, next_cons, temp;
    Object svref_arg_2;

    x_note_fn_call(170,64);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_text_box_format,
		Qtext_cell_line_quadding_qm);
    svref_arg_1 = Current_text_box_format;
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    SVREF(svref_arg_1,FIX((SI_Long)39L)) = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_width_of_formatted_part, Qcurrent_width_of_formatted_part);

static Object Qminimum_format_width_for_text_cell;  /* minimum-format-width-for-text-cell */

static Object Qmaximum_format_width_for_text_cell;  /* maximum-format-width-for-text-cell */

/* ENTER-FORMATTED-PART-WIDTH */
Object enter_formatted_part_width(new_width)
    Object new_width;
{
    Object svref_arg_1;

    x_note_fn_call(170,65);
    Part_feature_recall_stack = 
	    part_stack_cons_1(Current_width_of_formatted_part,
	    Part_feature_recall_stack);
    Current_width_of_formatted_part = new_width;
    Part_feature_recall_stack = 
	    part_stack_cons_1(ISVREF(Current_text_box_format,(SI_Long)41L),
	    Part_feature_recall_stack);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_text_box_format,
		Qminimum_format_width_for_text_cell);
    svref_arg_1 = Current_text_box_format;
    SVREF(svref_arg_1,FIX((SI_Long)41L)) = new_width;
    Part_feature_recall_stack = 
	    part_stack_cons_1(ISVREF(Current_text_box_format,(SI_Long)42L),
	    Part_feature_recall_stack);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_text_box_format,
		Qmaximum_format_width_for_text_cell);
    svref_arg_1 = Current_text_box_format;
    SVREF(svref_arg_1,FIX((SI_Long)42L)) = new_width;
    return VALUES_1(Nil);
}

/* EXIT-FORMATTED-PART-WIDTH */
Object exit_formatted_part_width()
{
    Object temp, part_stack_pop_store, cons_1, next_cons, temp_1, svref_arg_2;

    x_note_fn_call(170,66);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_text_box_format,
		Qmaximum_format_width_for_text_cell);
    temp = Current_text_box_format;
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_1 = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_1) = cons_1;
	    temp_1 = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = cons_1;
	}
	else {
	    temp_1 = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = cons_1;
	    temp_1 = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    SVREF(temp,FIX((SI_Long)42L)) = part_stack_pop_store;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_text_box_format,
		Qminimum_format_width_for_text_cell);
    temp = Current_text_box_format;
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_1 = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_1) = cons_1;
	    temp_1 = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = cons_1;
	}
	else {
	    temp_1 = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = cons_1;
	    temp_1 = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    SVREF(temp,FIX((SI_Long)41L)) = part_stack_pop_store;
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Current_width_of_formatted_part = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_height_of_formatted_part, Qcurrent_height_of_formatted_part);

/* ENTER-PART-FEATURE-HEIGHT */
Object enter_part_feature_height(new_value)
    Object new_value;
{
    x_note_fn_call(170,67);
    Part_feature_recall_stack = 
	    part_stack_cons_1(Current_height_of_formatted_part,
	    Part_feature_recall_stack);
    Current_height_of_formatted_part = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-HEIGHT */
Object exit_part_feature_height()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(170,68);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Current_height_of_formatted_part = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Part_text_size_parameters, Qpart_text_size_parameters);

static Object Qtext_cell_font_map;  /* text-cell-font-map */

static Object Qtext_cell_line_height;  /* text-cell-line-height */

static Object Qtext_cell_baseline_position;  /* text-cell-baseline-position */

static Object Qtext_cell_line_spacing;  /* text-cell-line-spacing */

static Object Qdefault_word_spacing;  /* default-word-spacing */

static Object Qminimum_word_spacing;  /* minimum-word-spacing */

static Object Qmaximum_word_spacing;  /* maximum-word-spacing */

/* ENTER-TEXT-SIZE */
Object enter_text_size(new_text_size)
    Object new_text_size;
{
    Object temp, new_settings, svref_arg_1, text_cell_font_map_old_value;
    Object new_settings_old_value, text_cell_line_height_old_value;
    Object text_cell_baseline_position_old_value;
    Object text_cell_line_spacing_old_value, default_word_spacing_old_value;
    Object minimum_word_spacing_old_value, maximum_word_spacing_old_value;

    x_note_fn_call(170,69);
    temp = assq_function(new_text_size,Part_text_size_parameters);
    new_settings = REST(temp);
    svref_arg_1 = Current_text_box_format;
    text_cell_font_map_old_value = ISVREF(svref_arg_1,(SI_Long)22L);
    new_settings_old_value = new_settings;
    temp = FIRST(new_settings_old_value);
    new_settings = REST(new_settings_old_value);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(svref_arg_1,Qtext_cell_font_map);
    SVREF(svref_arg_1,FIX((SI_Long)22L)) = temp;
    temp = text_cell_font_map_old_value;
    Part_feature_recall_stack = part_stack_cons_1(temp,
	    Part_feature_recall_stack);
    svref_arg_1 = Current_text_box_format;
    text_cell_line_height_old_value = ISVREF(svref_arg_1,(SI_Long)31L);
    new_settings_old_value = new_settings;
    temp = FIRST(new_settings_old_value);
    new_settings = REST(new_settings_old_value);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(svref_arg_1,Qtext_cell_line_height);
    SVREF(svref_arg_1,FIX((SI_Long)31L)) = temp;
    temp = text_cell_line_height_old_value;
    Part_feature_recall_stack = part_stack_cons_1(temp,
	    Part_feature_recall_stack);
    svref_arg_1 = Current_text_box_format;
    text_cell_baseline_position_old_value = ISVREF(svref_arg_1,(SI_Long)32L);
    new_settings_old_value = new_settings;
    temp = FIRST(new_settings_old_value);
    new_settings = REST(new_settings_old_value);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(svref_arg_1,Qtext_cell_baseline_position);
    SVREF(svref_arg_1,FIX((SI_Long)32L)) = temp;
    temp = text_cell_baseline_position_old_value;
    Part_feature_recall_stack = part_stack_cons_1(temp,
	    Part_feature_recall_stack);
    svref_arg_1 = Current_text_box_format;
    text_cell_line_spacing_old_value = ISVREF(svref_arg_1,(SI_Long)33L);
    new_settings_old_value = new_settings;
    temp = FIRST(new_settings_old_value);
    new_settings = REST(new_settings_old_value);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(svref_arg_1,Qtext_cell_line_spacing);
    SVREF(svref_arg_1,FIX((SI_Long)33L)) = temp;
    temp = text_cell_line_spacing_old_value;
    Part_feature_recall_stack = part_stack_cons_1(temp,
	    Part_feature_recall_stack);
    svref_arg_1 = Current_text_box_format;
    default_word_spacing_old_value = ISVREF(svref_arg_1,(SI_Long)34L);
    new_settings_old_value = new_settings;
    temp = FIRST(new_settings_old_value);
    new_settings = REST(new_settings_old_value);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(svref_arg_1,Qdefault_word_spacing);
    SVREF(svref_arg_1,FIX((SI_Long)34L)) = temp;
    temp = default_word_spacing_old_value;
    Part_feature_recall_stack = part_stack_cons_1(temp,
	    Part_feature_recall_stack);
    svref_arg_1 = Current_text_box_format;
    minimum_word_spacing_old_value = ISVREF(svref_arg_1,(SI_Long)35L);
    new_settings_old_value = new_settings;
    temp = FIRST(new_settings_old_value);
    new_settings = REST(new_settings_old_value);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(svref_arg_1,Qminimum_word_spacing);
    SVREF(svref_arg_1,FIX((SI_Long)35L)) = temp;
    temp = minimum_word_spacing_old_value;
    Part_feature_recall_stack = part_stack_cons_1(temp,
	    Part_feature_recall_stack);
    svref_arg_1 = Current_text_box_format;
    maximum_word_spacing_old_value = ISVREF(svref_arg_1,(SI_Long)36L);
    new_settings_old_value = new_settings;
    temp = FIRST(new_settings_old_value);
    new_settings = REST(new_settings_old_value);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(svref_arg_1,Qmaximum_word_spacing);
    SVREF(svref_arg_1,FIX((SI_Long)36L)) = temp;
    temp = maximum_word_spacing_old_value;
    Part_feature_recall_stack = part_stack_cons_1(temp,
	    Part_feature_recall_stack);
    return VALUES_1(Nil);
}

/* EXIT-TEXT-SIZE */
Object exit_text_size()
{
    Object svref_arg_1, part_stack_pop_store, cons_1, next_cons, temp;
    Object svref_arg_2;

    x_note_fn_call(170,70);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_text_box_format,Qmaximum_word_spacing);
    svref_arg_1 = Current_text_box_format;
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    SVREF(svref_arg_1,FIX((SI_Long)36L)) = part_stack_pop_store;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_text_box_format,Qminimum_word_spacing);
    svref_arg_1 = Current_text_box_format;
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    SVREF(svref_arg_1,FIX((SI_Long)35L)) = part_stack_pop_store;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_text_box_format,Qdefault_word_spacing);
    svref_arg_1 = Current_text_box_format;
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    SVREF(svref_arg_1,FIX((SI_Long)34L)) = part_stack_pop_store;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_text_box_format,
		Qtext_cell_line_spacing);
    svref_arg_1 = Current_text_box_format;
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    SVREF(svref_arg_1,FIX((SI_Long)33L)) = part_stack_pop_store;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_text_box_format,
		Qtext_cell_baseline_position);
    svref_arg_1 = Current_text_box_format;
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    SVREF(svref_arg_1,FIX((SI_Long)32L)) = part_stack_pop_store;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_text_box_format,Qtext_cell_line_height);
    svref_arg_1 = Current_text_box_format;
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    SVREF(svref_arg_1,FIX((SI_Long)31L)) = part_stack_pop_store;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_text_box_format,Qtext_cell_font_map);
    svref_arg_1 = Current_text_box_format;
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    SVREF(svref_arg_1,FIX((SI_Long)22L)) = part_stack_pop_store;
    return VALUES_1(Nil);
}

static Object Qtext_size;          /* text-size */

static Object list_constant;       /* # */

static Object Qsmall;              /* small */

/* STANDARDIZE-TEXT-SIZE-FEATURE-IN-PART-DESCRIPTION */
Object standardize_text_size_feature_in_part_description(part_description)
    Object part_description;
{
    Object p, temp, cadr_new_value;

    x_note_fn_call(170,71);
    p = REST(part_description);
  next_loop:
    if ( !TRUEP(p))
	goto end_loop;
    if (EQ(Qtext_size,CAR(p))) {
	temp = assoc_eql(CADR(p),list_constant);
	cadr_new_value = CDR(temp);
	if (cadr_new_value);
	else
	    cadr_new_value = Qsmall;
	M_CADR(p) = cadr_new_value;
    }
    p = CDDR(p);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object list_constant_1;     /* # */

static Object list_constant_2;     /* # */

/* GET-DEFAULT-FORMATTED-PART-OF-CLASS */
Object get_default_formatted_part_of_class()
{
    Object gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(170,72);
    gensymed_symbol = ISVREF(Current_computation_frame,(SI_Long)1L);
    gensymed_symbol_1 = 
	    lookup_global_or_kb_specific_property_value(Qnew_table,
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
	    temp = (SI_Long)0L < gensymed_symbol_2;
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_1(list_constant_1);
    else
	return VALUES_1(list_constant_2);
}

/* ENTER-PART-DESCRIPTION */
Object enter_part_description(part_description)
    Object part_description;
{
    Object part_feature_name, new_feature_value, ab_loop_list_;
    Object part_feature_index, enter_feature_handler, temp, new_cons, temp_1;
    Object svref_arg_2, svref_new_value, gensymed_symbol;

    x_note_fn_call(170,73);
    part_feature_name = Nil;
    new_feature_value = Nil;
    ab_loop_list_ = CDR(part_description);
    part_feature_index = Nil;
    enter_feature_handler = Nil;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    part_feature_name = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    new_feature_value = CAR(temp);
    part_feature_index = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(part_feature_name),
	    Qpart_feature_index);
    enter_feature_handler = ISVREF(Part_feature_enter_methods,
	    IFIX(part_feature_index));
    inline_funcall_1(enter_feature_handler,new_feature_value);
    new_cons = ISVREF(Available_part_stack_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp_1 = Available_part_stack_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_part_stack_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp_1 = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_part_stack_cons_pool();
    M_CAR(gensymed_symbol) = part_feature_index;
    temp_1 = Part_feature_recall_stack;
    M_CDR(gensymed_symbol) = temp_1;
    inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
    Part_feature_recall_stack = gensymed_symbol;
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* LOOKUP-PART-EXCEPTION */
Object lookup_part_exception(part_type,index_1)
    Object part_type, index_1;
{
    Object exception_collection, ab_loop_list_, exception_for_part_type_qm;
    Object part_exception, ab_loop_list__1, temp;

    x_note_fn_call(170,74);
    exception_collection = Nil;
    ab_loop_list_ = Part_exceptions_from_parents;
    exception_for_part_type_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    exception_collection = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    exception_for_part_type_qm = getf(exception_collection,part_type,_);
    if (exception_for_part_type_qm) {
	part_exception = Nil;
	ab_loop_list__1 = exception_for_part_type_qm;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	part_exception = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	temp = getf(REST(part_exception),Qpart_index,_);
	if (EQL(index_1,temp))
	    return VALUES_1(part_exception);
	goto next_loop_1;
      end_loop_1:;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Writing_annotations, Qwriting_annotations);

DEFINE_VARIABLE_WITH_SYMBOL(Write_annotations_part_pattern_stack, Qwrite_annotations_part_pattern_stack);

DEFINE_VARIABLE_WITH_SYMBOL(Wrote_first_annotation_flag, Qwrote_first_annotation_flag);

DEFINE_VARIABLE_WITH_SYMBOL(Part_features_to_write, Qpart_features_to_write);

DEFINE_VARIABLE_WITH_SYMBOL(Write_annotations_indent, Qwrite_annotations_indent);

DEFINE_VARIABLE_WITH_SYMBOL(Write_annotations_suppress_the_p, Qwrite_annotations_suppress_the_p);

static Object string_constant_5;   /* ";~%" */

static Object Qwide_string;        /* wide-string */

static Object string_constant_6;   /* "the " */

static Object string_constant_7;   /* "~( of any ~A~)" */

static Object string_constant_8;   /* "~( of ~A ~D~)" */

static Object Qthis_part_defaults;  /* this-part-defaults */

static Object string_constant_9;   /* "~( of this ~A~)" */

static Object string_constant_10;  /* "~( ~A ~)" */

static Object Qcompute_part_feature_of_type_color_or_metacolor;  /* compute-part-feature-of-type-color-or-metacolor */

static Object string_constant_11;  /* "is" */

static Object string_constant_12;  /* "=" */

/* WRITE-ANNOTATION */
Object write_annotation(part_type,part_feature,feature_value)
    Object part_type, part_feature, feature_value;
{
    Object part_feature_user_name, temp, schar_arg_2, schar_new_value;
    Object part_index_qm, ancestor_part_type, collection_feature_name;
    Object ab_loop_list_, ancestor_part_type_user_name, temp_1, feature_type;
    SI_Long i, ab_loop_bind_, thing;

    x_note_fn_call(170,75);
    if (EQ(T,Part_features_to_write) || memq_function(part_feature,
	    Part_features_to_write)) {
	part_feature_user_name = get_user_spelling(part_feature,Qpart_feature);
	if (Wrote_first_annotation_flag)
	    tformat(1,string_constant_5);
	Wrote_first_annotation_flag = T;
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(Write_annotations_indent);
      next_loop:
	if (i > ab_loop_bind_)
	    goto end_loop;
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
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	if ( !TRUEP(Write_annotations_suppress_the_p))
	    tformat(1,string_constant_6);
	tformat(2,string_constant_1,part_feature_user_name);
	part_index_qm = Nil;
	ancestor_part_type = Nil;
	collection_feature_name = Nil;
	ab_loop_list_ = Write_annotations_part_pattern_stack;
	ancestor_part_type_user_name = Nil;
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
      next_loop_1:
	part_index_qm = CAR(ab_loop_list_);
	temp_1 = CDR(ab_loop_list_);
	ancestor_part_type = CAR(temp_1);
	temp_1 = CDR(ab_loop_list_);
	temp_1 = CDR(temp_1);
	collection_feature_name = CAR(temp_1);
	ancestor_part_type_user_name = 
		get_user_spelling(ancestor_part_type,Qpart_type);
	if (EQ(collection_feature_name,Qsubpart_defaults))
	    tformat(2,string_constant_7,ancestor_part_type_user_name);
	else if (EQ(collection_feature_name,Qsubpart_exceptions))
	    tformat(3,string_constant_8,ancestor_part_type_user_name,
		    part_index_qm);
	else if (EQ(collection_feature_name,Qthis_part_defaults))
	    tformat(2,string_constant_9,ancestor_part_type_user_name);
	ab_loop_list_ = CDDDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	goto next_loop_1;
      end_loop_1:;
	temp_1 = part_feature_description(part_type,part_feature);
	temp_1 = CDDR(temp_1);
	feature_type = CAR(temp_1);
	tformat(2,string_constant_10,SYMBOLP(feature_value) || 
		EQ(feature_type,
		Qcompute_part_feature_of_type_color_or_metacolor) ? 
		string_constant_11 : string_constant_12);
	return write_instance_of_simple_type_1(feature_type,feature_value);
    }
    else
	return VALUES_1(Nil);
}

static Object Qab_slot_value;      /* slot-value */

/* WRITE-ANNOTATION-PART-PATTERN */
Object write_annotation_part_pattern(part_feature,subpart_template_collection)
    Object part_feature, subpart_template_collection;
{
    Object part_type, part_templates_for_type, ab_loop_list_, temp;
    Object part_template, ab_loop_list__1, slot_value_pop_store, cons_1;
    Object next_cons, temp_1, svref_arg_2;

    x_note_fn_call(170,76);
    Write_annotations_part_pattern_stack = slot_value_cons_1(part_feature,
	    Write_annotations_part_pattern_stack);
    part_type = Nil;
    part_templates_for_type = Nil;
    ab_loop_list_ = subpart_template_collection;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    part_type = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    part_templates_for_type = CAR(temp);
    Write_annotations_part_pattern_stack = slot_value_cons_1(part_type,
	    Write_annotations_part_pattern_stack);
    part_template = Nil;
    ab_loop_list__1 = part_templates_for_type;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    part_template = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    write_annotations_in_part_template(part_template);
    goto next_loop_1;
  end_loop_1:;
    slot_value_pop_store = Nil;
    cons_1 = Write_annotations_part_pattern_stack;
    if (cons_1) {
	slot_value_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qab_slot_value);
	if (ISVREF(Available_slot_value_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_1 = ISVREF(Available_slot_value_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_1) = cons_1;
	    temp_1 = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = cons_1;
	}
	else {
	    temp_1 = Available_slot_value_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = cons_1;
	    temp_1 = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Write_annotations_part_pattern_stack = next_cons;
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:;
    slot_value_pop_store = Nil;
    cons_1 = Write_annotations_part_pattern_stack;
    if (cons_1) {
	slot_value_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qab_slot_value);
	if (ISVREF(Available_slot_value_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_1 = ISVREF(Available_slot_value_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_1) = cons_1;
	    temp_1 = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = cons_1;
	}
	else {
	    temp_1 = Available_slot_value_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = cons_1;
	    temp_1 = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Write_annotations_part_pattern_stack = next_cons;
    return VALUES_1(slot_value_pop_store);
}

/* WRITE-ANNOTATIONS-IN-PART-TEMPLATE */
Object write_annotations_in_part_template(part_template)
    Object part_template;
{
    Object temp, ab_loop_destructure_, part_type, part_features, part_feature;
    Object feature_value, ab_loop_list_, slot_value_pop_store, cons_1;
    Object next_cons, temp_1, svref_arg_2;

    x_note_fn_call(170,77);
    temp = get_simple_part_feature(part_template,Qpart_index);
    Write_annotations_part_pattern_stack = slot_value_cons_1(temp,
	    Write_annotations_part_pattern_stack);
    ab_loop_destructure_ = part_template;
    part_type = Nil;
    part_features = Nil;
    part_type = CAR(ab_loop_destructure_);
    part_features = CDR(ab_loop_destructure_);
    part_feature = Nil;
    feature_value = Nil;
    ab_loop_list_ = part_features;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    part_feature = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    feature_value = CAR(temp);
    if (EQ(part_feature,Qsubpart_defaults) || EQ(part_feature,
	    Qsubpart_exceptions))
	write_annotation_part_pattern(part_feature,feature_value);
    else if (EQ(part_feature,Qpart_index));
    else
	write_annotation(part_type,part_feature,feature_value);
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:;
    slot_value_pop_store = Nil;
    cons_1 = Write_annotations_part_pattern_stack;
    if (cons_1) {
	slot_value_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qab_slot_value);
	if (ISVREF(Available_slot_value_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_1 = ISVREF(Available_slot_value_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_1) = cons_1;
	    temp_1 = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = cons_1;
	}
	else {
	    temp_1 = Available_slot_value_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = cons_1;
	    temp_1 = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Write_annotations_part_pattern_stack = next_cons;
    return VALUES_1(slot_value_pop_store);
}

static Object Qnone;               /* none */

/* WRITE-PART-DESCRIPTION */
Object write_part_description varargs_1(int, n)
{
    Object annotations_slot_value;
    Object part_features_to_write, indent, suppress_the_p;
    Object write_annotations_part_pattern_stack, wrote_first_annotation_flag;
    Object write_annotations_indent, write_annotations_suppress_the_p;
    Object ab_loop_destructure_, part_type, part_features, part_feature;
    Object feature_value, ab_loop_list_, temp;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(5);
    Object result;

    x_note_fn_call(170,78);
    INIT_ARGS_nonrelocating();
    annotations_slot_value = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    part_features_to_write = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    PUSH_SPECIAL_WITH_SYMBOL(Part_features_to_write,Qpart_features_to_write,part_features_to_write,
	    4);
      indent = OPTIONAL_ARG_P_nonrelocating() ? 
	      OPTIONAL_ARG_nonrelocating() : FIX((SI_Long)0L);
      suppress_the_p = OPTIONAL_ARG_P_nonrelocating() ? 
	      OPTIONAL_ARG_nonrelocating() : Nil;
      END_ARGS_nonrelocating();
      LOCK(Writing_annotations);
      if (PUSH_UNWIND_PROTECT(0)) {
	  write_annotations_part_pattern_stack = Nil;
	  wrote_first_annotation_flag = Nil;
	  write_annotations_indent = indent;
	  write_annotations_suppress_the_p = suppress_the_p;
	  PUSH_SPECIAL_WITH_SYMBOL(Write_annotations_suppress_the_p,Qwrite_annotations_suppress_the_p,write_annotations_suppress_the_p,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Write_annotations_indent,Qwrite_annotations_indent,write_annotations_indent,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Wrote_first_annotation_flag,Qwrote_first_annotation_flag,wrote_first_annotation_flag,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Write_annotations_part_pattern_stack,Qwrite_annotations_part_pattern_stack,write_annotations_part_pattern_stack,
			0);
		  ab_loop_destructure_ = annotations_slot_value;
		  part_type = Nil;
		  part_features = Nil;
		  part_type = CAR(ab_loop_destructure_);
		  part_features = CDR(ab_loop_destructure_);
		  part_feature = Nil;
		  feature_value = Nil;
		  ab_loop_list_ = part_features;
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop;
		next_loop:
		  part_feature = CAR(ab_loop_list_);
		  temp = CDR(ab_loop_list_);
		  feature_value = CAR(temp);
		  if (EQ(part_feature,Qsubpart_defaults) || 
			  EQ(part_feature,Qsubpart_exceptions))
		      write_annotation_part_pattern(part_feature,
			      feature_value);
		  else
		      write_annotation(part_type,part_feature,feature_value);
		  ab_loop_list_ = CDDR(ab_loop_list_);
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop;
		  goto next_loop;
		end_loop:
		  if ( !TRUEP(Wrote_first_annotation_flag))
		      twrite_symbol(1,Qnone);
		  SAVE_VALUES(VALUES_1(Qnil));
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
      }
      POP_UNWIND_PROTECT(0);
      UNLOCK(Writing_annotations);
      CONTINUE_UNWINDING(0);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Last_semantic_check_error_string, Qlast_semantic_check_error_string);

static Object Qsemantic_error;     /* semantic-error */

static Object string_constant_13;  /* "~(In statement #~D, ~A is not a known feature of ~A ~A.~)" */

static Object string_constant_14;  /* "~(In statement #~D, ~A is not a supported attribute of ~A ~A.~)" */

static Object Qred;                /* red */

static Object Qdo_not_use;         /* do-not-use */

static Object string_constant_15;  /* "~(In statement #~D for ~S: ~)" */

/* SEMANTIC-CHECK-PART-DESCRIPTION */
Object semantic_check_part_description(part_description_parse)
    Object part_description_parse;
{
    Object annotation, ab_loop_list_, part_lookup, part_feature, value_desired;
    Object subpart_type, hidden_features, ab_loop_iter_flag_, temp;
    Object subpart_type_user_spelling, temp_1, error_string;
    Object part_type_user_spelling, actual_value, type_spec;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long statement_number, bv16_length, aref_arg_2, aref_new_value;
    SI_Long length_1;
    char temp_2;
    Declare_catch(1);
    Declare_special(5);
    Object result;

    x_note_fn_call(170,79);
    if (PUSH_CATCH(Qsemantic_error,0)) {
	annotation = Nil;
	ab_loop_list_ = REST(part_description_parse);
	statement_number = (SI_Long)1L;
	part_lookup = Nil;
	part_feature = Nil;
	value_desired = Nil;
	subpart_type = Nil;
	hidden_features = Nil;
	ab_loop_iter_flag_ = T;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	annotation = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    statement_number = statement_number + (SI_Long)1L;
	temp = CDR(annotation);
	part_lookup = CAR(temp);
	temp = CDR(annotation);
	temp = CDR(temp);
	temp = CAR(temp);
	temp = CDR(temp);
	part_feature = CAR(temp);
	temp = CDR(annotation);
	temp = CDR(temp);
	temp = CDR(temp);
	value_desired = CAR(temp);
	subpart_type = semantic_check_part_lookup(FIX(statement_number),
		part_lookup);
	temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(subpart_type),
		Qpart_type_description);
	temp = CDDDDR(temp);
	hidden_features = CAR(temp);
	if ( !TRUEP(part_feature_description(subpart_type,part_feature))) {
	    subpart_type_user_spelling = get_user_spelling(subpart_type,
		    Qpart_type);
	    temp_1 = FIX(statement_number);
	    temp = get_user_spelling(part_feature,Qpart_feature);
	    error_string = tformat_text_string(5,string_constant_13,temp_1,
		    temp,supply_a_or_an(subpart_type_user_spelling),
		    subpart_type_user_spelling);
	    Last_semantic_check_error_string = error_string;
	    result = VALUES_1(error_string);
	    THROW(Qsemantic_error,result);
	}
	if (memq_function(part_feature,hidden_features)) {
	    part_type_user_spelling = get_user_spelling(subpart_type,
		    Qpart_type);
	    temp_1 = FIX(statement_number);
	    temp = get_user_spelling(part_feature,Qpart_feature);
	    error_string = tformat_text_string(5,string_constant_14,temp_1,
		    temp,supply_a_or_an(part_type_user_spelling),
		    part_type_user_spelling);
	    Last_semantic_check_error_string = error_string;
	    result = VALUES_1(error_string);
	    THROW(Qsemantic_error,result);
	}
	if (ATOM(value_desired))
	    actual_value = value_desired;
	else if (EQ(Qquote,FIRST(value_desired)))
	    actual_value = SECOND(value_desired);
	else {
	    if (EQ(Qcopy_for_slot_value,CAR(value_desired))) {
		temp = SECOND(value_desired);
		temp_2 = EQ(Qquote,CAR(temp));
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		temp = SECOND(value_desired);
		actual_value = SECOND(temp);
	    }
	    else if (EQ(Qcompile_computed_part_feature,FIRST(value_desired)))
		actual_value = Qred;
	    else
		actual_value = Qnil;
	}
	temp = part_feature_description(subpart_type,part_feature);
	temp = CDDR(temp);
	type_spec = CAR(temp);
	if ( !TRUEP(simple_typep(actual_value,type_spec))) {
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
		      temp = FIX(statement_number);
		      tformat(3,string_constant_15,temp,
			      get_user_spelling(part_feature,Qpart_feature));
		      tformat_type_error(SYMBOLP(actual_value) ? 
			      get_user_spelling(actual_value,Qconstant) : 
			      actual_value,type_spec);
		      error_string = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    Last_semantic_check_error_string = error_string;
	    result = VALUES_1(error_string);
	    THROW(Qsemantic_error,result);
	}
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:;
	result = VALUES_1(Nil);
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    return result;
}

static Object string_constant_16;  /* "Defaulting via \"any ~(~A~)\" is not supported." */

static Object string_constant_17;  /* "Setting a feature of an individual ~(~A~) is not supported." */

/* SEMANTIC-CHECK-PART-LOOKUP */
Object semantic_check_part_lookup(statement_number,part_lookup)
    Object statement_number, part_lookup;
{
    Object gensymed_symbol, parent_part_lookup, gensymed_symbol_1;
    Object subpart_flavor, desired_subpart_type, temp, error_string;
    Object result;

    x_note_fn_call(170,80);
    if (EQ(part_lookup,Qcurrent_part_description))
	return VALUES_1(FIRST(Current_part_description));
    else {
	gensymed_symbol = part_lookup;
	gensymed_symbol = CDR(gensymed_symbol);
	parent_part_lookup = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	gensymed_symbol_1 = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	subpart_flavor = CAR(gensymed_symbol_1);
	gensymed_symbol_1 = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	desired_subpart_type = CAR(gensymed_symbol_1);
	gensymed_symbol = CDR(gensymed_symbol);
	if (EQ(subpart_flavor,Qsubpart_defaults)) {
	    temp = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(desired_subpart_type),
		    Qpart_type_description);
	    temp = CDDDDR(temp);
	    temp = CDDR(temp);
	    if ( !TRUEP(CAR(temp))) {
		error_string = tformat_text_string(2,string_constant_16,
			get_user_spelling(desired_subpart_type,Qpart_type));
		Last_semantic_check_error_string = error_string;
		result = VALUES_1(error_string);
		THROW(Qsemantic_error,result);
	    }
	}
	else if (EQ(subpart_flavor,Qsubpart_exceptions)) {
	    temp = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(desired_subpart_type),
		    Qpart_type_description);
	    temp = CDDDDR(temp);
	    temp = CDR(temp);
	    if ( !TRUEP(CAR(temp))) {
		error_string = tformat_text_string(2,string_constant_17,
			get_user_spelling(desired_subpart_type,Qpart_type));
		Last_semantic_check_error_string = error_string;
		result = VALUES_1(error_string);
		THROW(Qsemantic_error,result);
	    }
	}
	semantic_check_part_lookup(statement_number,parent_part_lookup);
	return VALUES_1(desired_subpart_type);
    }
}

static Object array_constant;      /* # */

static Object array_constant_1;    /* # */

static Object array_constant_2;    /* # */

/* COMPILE-PART-DESCRIPTION */
Object compile_part_description(part_description_parse,part_type)
    Object part_description_parse, part_type;
{
    Object result_1, error_message_qm;
    Object part_description_parse_in_slot_value_conses;
    Object current_part_description, temp, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object semantic_check_function_qm;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(6);

    x_note_fn_call(170,81);
    if (EQ(part_description_parse,Qnone) ||  !TRUEP(part_description_parse))
	return VALUES_1(Nil);
    M_FIRST(part_description_parse) = Qprogn;
    result_1 = Bad_phrase;
    error_message_qm = Nil;
    error_message_qm = 
	    kludge_to_avoid_computed_part_feature_in_certain_places(part_description_parse);
    if ( !TRUEP(error_message_qm)) {
	part_description_parse_in_slot_value_conses = 
		copy_for_slot_value(part_description_parse);
	current_part_description = slot_value_cons_1(part_type,Nil);
	PUSH_SPECIAL_WITH_SYMBOL(Current_part_description,Qcurrent_part_description,current_part_description,
		5);
	  current_part_description = slot_value_cons_1(part_type,Nil);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_part_description,Qcurrent_part_description,current_part_description,
		  0);
	    temp = 
		    semantic_check_part_description(part_description_parse_in_slot_value_conses);
	    reclaim_slot_value_list_1(Current_part_description);
	    error_message_qm = temp;
	  POP_SPECIAL();
	  if ( !TRUEP(error_message_qm)) {
	      result_1 = 
		      simple_eval(part_description_parse_in_slot_value_conses);
	      if (EQ(result_1,Bad_phrase)) {
		  if ( !TRUEP(Last_semantic_check_error_string) ||  
			  !TRUEP(valid_wide_string_length_bv16(Last_semantic_check_error_string))) 
			      {
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
				twrite_beginning_of_wide_string(array_constant,
					FIX((SI_Long)35L));
				twrite_beginning_of_wide_string(array_constant_1,
					FIX((SI_Long)38L));
				twrite_beginning_of_wide_string(array_constant_2,
					FIX((SI_Long)26L));
				error_message_qm = 
					copy_out_current_wide_string();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		  }
		  else
		      error_message_qm = Last_semantic_check_error_string;
		  Last_semantic_check_error_string = Nil;
	      }
	      else {
		  temp = 
			  getfq_function_no_default(INLINE_SYMBOL_PLIST(part_type),
			  Qpart_type_description);
		  temp = CDDDDR(temp);
		  temp = CDDDR(temp);
		  semantic_check_function_qm = CAR(temp);
		  if (semantic_check_function_qm)
		      error_message_qm = 
			      FUNCALL_1(semantic_check_function_qm,
			      Current_part_description);
	      }
	  }
	  if (error_message_qm)
	      result_1 = Bad_phrase;
	  else
	      result_1 = copy_for_phrase(Current_part_description);
	  reclaim_slot_value(part_description_parse_in_slot_value_conses);
	  reclaim_slot_value(Current_part_description);
	POP_SPECIAL();
    }
    return VALUES_2(result_1,error_message_qm);
}

static Object Qdefault_cell_format;  /* default-cell-format */

/* KLUDGE-TO-AVOID-COMPUTED-PART-FEATURE-IN-CERTAIN-PLACES */
Object kludge_to_avoid_computed_part_feature_in_certain_places(parse_of_part_description)
    Object parse_of_part_description;
{
    Object frame, symbol, gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(170,82);
    if (EQ(ISVREF(Current_edit_state,(SI_Long)5L),Qdefault_cell_format)) {
	frame = ISVREF(Current_edit_state,(SI_Long)3L);
	symbol = Qnew_table;
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
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return kludge_to_avoid_computed_part_feature_in_certain_places_1(parse_of_part_description);
    else
	return VALUES_1(Nil);
}

static Object array_constant_3;    /* # */

/* KLUDGE-TO-AVOID-COMPUTED-PART-FEATURE-IN-CERTAIN-PLACES-1 */
Object kludge_to_avoid_computed_part_feature_in_certain_places_1(parse_tree)
    Object parse_tree;
{
    Object temp;

    x_note_fn_call(170,83);
    if (CONSP(parse_tree)) {
	temp = 
		kludge_to_avoid_computed_part_feature_in_certain_places_1(CAR(parse_tree));
	if (temp)
	    return VALUES_1(temp);
	else
	    return kludge_to_avoid_computed_part_feature_in_certain_places_1(CDR(parse_tree));
    }
    else if (SYMBOLP(parse_tree)) {
	if (EQ(Qcompile_computed_part_feature,parse_tree))
	    return copy_constant_wide_string_given_length(array_constant_3,
		    FIX((SI_Long)56L));
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Qnil);
}

Object Part_feature_type_reclaimer_prop = UNBOUND;

/* RECLAIM-PART-DESCRIPTION */
Object reclaim_part_description(part_description)
    Object part_description;
{
    x_note_fn_call(170,84);
    delete_all_editors_of_cell(part_description);
    if (part_description) {
	reclaim_part_features(CAR(part_description),CDR(part_description));
	reclaim_slot_value_cons_1(part_description);
	return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* RECLAIM-PART-FEATURES */
Object reclaim_part_features(part_type,part_features)
    Object part_type, part_features;
{
    Object p, part_feature_name, part_feature_value, temp;

    x_note_fn_call(170,85);
    p = part_features;
    part_feature_name = Nil;
    part_feature_value = Nil;
  next_loop:
    if ( !TRUEP(p))
	goto end_loop;
    part_feature_name = CAR(p);
    temp = CDR(p);
    part_feature_value = CAR(temp);
    reclaim_part_feature(part_type,part_feature_name,part_feature_value);
    M_SECOND(p) = Nil;
    p = CDDR(p);
    goto next_loop;
  end_loop:;
    reclaim_slot_value_list_1(part_features);
    return VALUES_1(Nil);
}

static Object Qpart_feature_type_reclaimer;  /* part-feature-type-reclaimer */

/* RECLAIM-PART-FEATURE */
Object reclaim_part_feature(part_type,feature_name,feature_value)
    Object part_type, feature_name, feature_value;
{
    Object temp, part_feature_type, gensymed_symbol, part_type_reclaimer;

    x_note_fn_call(170,86);
    temp = part_feature_description(part_type,feature_name);
    temp = CDDR(temp);
    part_feature_type = CAR(temp);
    gensymed_symbol = SYMBOLP(part_feature_type) ? part_feature_type : 
	    CAR(part_feature_type);
    part_type_reclaimer = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qpart_feature_type_reclaimer);
    if (part_type_reclaimer)
	return FUNCALL_1(part_type_reclaimer,feature_value);
    else
	return reclaim_slot_value(feature_value);
}

/* FEATURE-TYPE-RECLAIMER-FOR-SUBPARTS-COLLECTION */
Object feature_type_reclaimer_for_subparts_collection(the_part_collection)
    Object the_part_collection;
{
    Object list_of_part_descriptions, ab_loop_list_, temp, p2, car_new_value;

    x_note_fn_call(170,87);
    list_of_part_descriptions = Nil;
    ab_loop_list_ = the_part_collection;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    temp = CDR(ab_loop_list_);
    list_of_part_descriptions = CAR(temp);
    p2 = list_of_part_descriptions;
  next_loop_1:
    if ( !TRUEP(p2))
	goto end_loop_1;
    car_new_value = reclaim_part_description(CAR(p2));
    M_CAR(p2) = car_new_value;
    p2 = M_CDR(p2);
    goto next_loop_1;
  end_loop_1:;
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:;
    return reclaim_slot_value_tree_1(the_part_collection);
}

static Object Qcell_array;         /* cell-array */

/* FEATURE-TYPE-RECLAIMER-FOR-COMPUTE-PART-FEATURE-OF-TYPE-COLOR-OR-METACOLOR */
Object feature_type_reclaimer_for_compute_part_feature_of_type_color_or_metacolor(compute_part_feature_of_type_color_or_metacolor)
    Object compute_part_feature_of_type_color_or_metacolor;
{
    Object temp;

    x_note_fn_call(170,88);
    if (evaluated_computed_part_feature_p(compute_part_feature_of_type_color_or_metacolor)) 
		{
	temp = get_lookup_slot_value_given_default(Current_annotated_frame,
		Qcell_array,Nil);
	deactivate_cell_of_g2_cell_array(temp,
		get_simple_part_feature(compute_part_feature_of_type_color_or_metacolor,
		Qexpression_cell_index));
	return reclaim_part_description(compute_part_feature_of_type_color_or_metacolor);
    }
    else
	return VALUES_1(Nil);
}

/* PART-DESCRIPTION-OF-FRAME */
Object part_description_of_frame(slot_name,frame)
    Object slot_name, frame;
{
    x_note_fn_call(170,89);
    return get_slot_value_function(frame,slot_name,Nil);
}

/* GET-SIMPLE-PART-FEATURE */
Object get_simple_part_feature(part_description,part_feature)
    Object part_description, part_feature;
{
    x_note_fn_call(170,90);
    return getf(REST(part_description),part_feature,_);
}

/* GET-SUBPART-COLLECTION */
Object get_subpart_collection(part_description,part_feature,part_type)
    Object part_description, part_feature, part_type;
{
    Object subpart_collection, subparts_for_this_type;

    x_note_fn_call(170,91);
    subpart_collection = get_simple_part_feature(part_description,
	    part_feature);
    subparts_for_this_type = getf(subpart_collection,part_type,_);
    return VALUES_1(subparts_for_this_type);
}

/* SET-SUBPART-COLLECTION-WITHOUT-RECLAIMING */
Object set_subpart_collection_without_reclaiming(part_description,
	    collection_feature,part_type,new_collection)
    Object part_description, collection_feature, part_type, new_collection;
{
    Object subpart_collection, p, subpart_type;

    x_note_fn_call(170,92);
    subpart_collection = get_simple_part_feature(part_description,
	    collection_feature);
    p = subpart_collection;
    subpart_type = Nil;
    if ( !TRUEP(memq_function(part_type,subpart_collection))) {
	subpart_collection = slot_value_cons_1(part_type,
		slot_value_cons_1(Nil,subpart_collection));
	set_simple_part_feature(part_description,collection_feature,
		subpart_collection);
    }
  next_loop:
    if ( !TRUEP(p))
	goto end_loop;
    subpart_type = FIRST(p);
    if (EQ(subpart_type,part_type)) {
	M_SECOND(p) = new_collection;
	return VALUES_1(Nil);
    }
    p = CDDR(p);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* GET-SUBPART-OF-COLLECTION */
Object get_subpart_of_collection(part_description,part_feature,part_type,
	    part_index)
    Object part_description, part_feature, part_type, part_index;
{
    Object subparts_for_this_type, exceptional_part_template, ab_loop_list_;
    Object exceptional_part_index;
    Declare_special(1);
    Object result;

    x_note_fn_call(170,93);
    PUSH_SPECIAL_WITH_SYMBOL(Part_index,Qpart_index,part_index,0);
      subparts_for_this_type = get_subpart_collection(part_description,
	      part_feature,part_type);
      if (EQ(part_feature,Qsubparts))
	  result = nth(Part_index,subparts_for_this_type);
      else if (EQ(part_feature,Qsubpart_exceptions)) {
	  exceptional_part_template = Nil;
	  ab_loop_list_ = subparts_for_this_type;
	  exceptional_part_index = Nil;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  exceptional_part_template = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  exceptional_part_index = 
		  get_simple_part_feature(exceptional_part_template,
		  Qpart_index);
	  if (NUM_GT(exceptional_part_index,Part_index)) {
	      result = VALUES_1(Nil);
	      goto end_1;
	  }
	  else if (NUM_EQ(exceptional_part_index,Part_index)) {
	      result = VALUES_1(exceptional_part_template);
	      goto end_1;
	  }
	  goto next_loop;
	end_loop:
	  result = VALUES_1(Qnil);
	end_1:;
      }
      else if (EQ(part_feature,Qsubpart_defaults))
	  result = VALUES_1(FIRST(subparts_for_this_type));
      else
	  result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* SET-SIMPLE-PART-FEATURE */
Object set_simple_part_feature(part_description,part_feature,new_value)
    Object part_description, part_feature, new_value;
{
    Object ab_loop_destructure_, part_type, part_features, key, value_cons;
    Object ab_loop_list_, new_bit;

    x_note_fn_call(170,94);
    if ( !EQ(new_value,Bad_phrase)) {
	ab_loop_destructure_ = part_description;
	part_type = Nil;
	part_features = Nil;
	part_type = CAR(ab_loop_destructure_);
	part_features = CDR(ab_loop_destructure_);
	key = Nil;
	value_cons = Nil;
	ab_loop_list_ = part_features;
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
      next_loop:
	key = CAR(ab_loop_list_);
	value_cons = CDR(ab_loop_list_);
	if (EQ(key,part_feature)) {
	    reclaim_part_feature(part_type,key,CAR(value_cons));
	    M_CAR(value_cons) = new_value;
	    goto end_1;
	}
	ab_loop_list_ = CDDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	goto next_loop;
      end_loop:
	new_bit = slot_value_list_2(part_feature,new_value);
	if ( !TRUEP(value_cons))
	    M_CDR(part_description) = new_bit;
	else
	    M_CDR(value_cons) = new_bit;
      end_1:;
    }
    return VALUES_1(new_value);
}

/* SET-SIMPLE-PART-FEATURE-WITHOUT-RECLAIMING */
Object set_simple_part_feature_without_reclaiming(part_description,
	    part_feature,new_value)
    Object part_description, part_feature, new_value;
{
    Object ab_loop_destructure_, part_features, key, value_cons, ab_loop_list_;
    Object new_bit;

    x_note_fn_call(170,95);
    ab_loop_destructure_ = part_description;
    part_features = Nil;
    part_features = CDR(ab_loop_destructure_);
    key = Nil;
    value_cons = Nil;
    ab_loop_list_ = part_features;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    key = CAR(ab_loop_list_);
    value_cons = CDR(ab_loop_list_);
    if (EQ(key,part_feature)) {
	M_CAR(value_cons) = new_value;
	goto end_1;
    }
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:
    new_bit = slot_value_list_2(part_feature,new_value);
    if ( !TRUEP(value_cons))
	M_CDR(part_description) = new_bit;
    else
	M_CDR(value_cons) = new_bit;
  end_1:;
    return VALUES_1(new_value);
}

/* PART-HAS-FEATURE-P */
Object part_has_feature_p(part_description,part_feature)
    Object part_description, part_feature;
{
    Object actual_part_feature, feature_value, ab_loop_list_, temp;

    x_note_fn_call(170,96);
    actual_part_feature = Nil;
    feature_value = Nil;
    ab_loop_list_ = REST(part_description);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    actual_part_feature = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    feature_value = CAR(temp);
    if (EQ(part_feature,actual_part_feature)) {
	temp = feature_value;
	if (temp)
	    return VALUES_1(temp);
	else
	    return VALUES_1(T);
    }
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object list_constant_3;     /* # */

/* MAP-OVER-PART-DESCRIPTION */
Object map_over_part_description(function,part_description)
    Object function, part_description;
{
    Object feature_name, feature_value, ab_loop_list_, temp;

    x_note_fn_call(170,97);
    feature_name = Nil;
    feature_value = Nil;
    ab_loop_list_ = REST(part_description);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    feature_name = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    feature_value = CAR(temp);
    if (memq_function(feature_name,list_constant_3))
	map_over_subpart_collection(function,feature_value);
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:
    FUNCALL_1(function,part_description);
    return VALUES_1(Qnil);
}

/* MAP-OVER-SUBPART-COLLECTION */
Object map_over_subpart_collection(function,subpart_collection)
    Object function, subpart_collection;
{
    Object instances, ab_loop_list_, temp, part_description, ab_loop_list__1;

    x_note_fn_call(170,98);
    instances = Nil;
    ab_loop_list_ = subpart_collection;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    temp = CDR(ab_loop_list_);
    instances = CAR(temp);
    part_description = Nil;
    ab_loop_list__1 = instances;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    part_description = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    map_over_part_description(function,part_description);
    goto next_loop_1;
  end_loop_1:;
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* REMOVE-SIMPLE-PART-FEATURE */
Object remove_simple_part_feature(part_description,part_feature)
    Object part_description, part_feature;
{
    Object part_type, p, cantidate_feature, old_value, temp, bit_to_reclaim;
    Object cdr_new_value;

    x_note_fn_call(170,99);
    part_type = FIRST(part_description);
    p = part_description;
    cantidate_feature = Nil;
    old_value = Nil;
  next_loop:
    if ( !TRUEP(p))
	goto end_loop;
    temp = CDR(p);
    cantidate_feature = CAR(temp);
    temp = CDR(p);
    temp = CDR(temp);
    old_value = CAR(temp);
    if (EQ(cantidate_feature,part_feature)) {
	bit_to_reclaim = CDR(p);
	reclaim_part_feature(part_type,part_feature,old_value);
	cdr_new_value = CDDDR(p);
	M_CDR(p) = cdr_new_value;
	M_CDDR(bit_to_reclaim) = Nil;
	reclaim_slot_value_list_1(bit_to_reclaim);
    }
    p = CDDR(p);
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* REMOVE-SIMPLE-PART-FEATURE-WITHOUT-RECLAIMING */
Object remove_simple_part_feature_without_reclaiming(part_description,
	    part_feature)
    Object part_description, part_feature;
{
    Object p, cantidate_feature, temp, bit_to_reclaim, cdr_new_value;

    x_note_fn_call(170,100);
    p = part_description;
    cantidate_feature = Nil;
  next_loop:
    if ( !TRUEP(p))
	goto end_loop;
    temp = CDR(p);
    cantidate_feature = CAR(temp);
    if (EQ(cantidate_feature,part_feature)) {
	bit_to_reclaim = CDR(p);
	cdr_new_value = CDDDR(p);
	M_CDR(p) = cdr_new_value;
	M_CDDR(bit_to_reclaim) = Nil;
	reclaim_slot_value_list_1(bit_to_reclaim);
    }
    p = CDDR(p);
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* LOOKUP-SUBPART-OF-COLLECTION */
Object lookup_subpart_of_collection(part_description,part_feature,
	    part_type,part_index)
    Object part_description, part_feature, part_type, part_index;
{
    Object subpart_collection_qm, subpart_collection, found_it_flag;
    Object part_type_for_these, cantidate_cons, ab_loop_list_, last_cons;
    Object cons_of_subparts_for_this_type, temp, subparts_for_this_type_qm;
    Object result_1, new_bit, exceptional_part_template_cons, cantidate_result;
    Object exceptional_part_index, cdr_old_value, cdr_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(170,101);
    PUSH_SPECIAL_WITH_SYMBOL(Part_index,Qpart_index,part_index,0);
      subpart_collection_qm = get_simple_part_feature(part_description,
	      part_feature);
      subpart_collection = subpart_collection_qm ? subpart_collection_qm : 
	      set_simple_part_feature(part_description,part_feature,
	      slot_value_list_2(part_type,Nil));
      found_it_flag = Nil;
      part_type_for_these = Nil;
      cantidate_cons = Nil;
      ab_loop_list_ = subpart_collection;
      last_cons = Nil;
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
    next_loop:
      part_type_for_these = CAR(ab_loop_list_);
      cantidate_cons = CDR(ab_loop_list_);
      last_cons = cantidate_cons;
      if (EQ(part_type,part_type_for_these)) {
	  found_it_flag = T;
	  cons_of_subparts_for_this_type = cantidate_cons;
	  goto end_1;
      }
      ab_loop_list_ = CDDR(ab_loop_list_);
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      goto next_loop;
    end_loop:
      if ( !TRUEP(found_it_flag)) {
	  temp = slot_value_list_2(part_type,Nil);
	  M_CDR(last_cons) = temp;
	  cons_of_subparts_for_this_type = CDR(temp);
	  goto end_1;
      }
      cons_of_subparts_for_this_type = Qnil;
    end_1:;
      subparts_for_this_type_qm = CAR(cons_of_subparts_for_this_type);
      if (EQ(part_feature,Qsubparts)) {
	  result_1 = nth(Part_index,subparts_for_this_type_qm);
	  if ( !TRUEP(result_1))
	      error((SI_Long)1L,
		      "Can not create new parts instances on the fly.");
	  result = VALUES_1(result_1);
      }
      else if (EQ(part_feature,Qsubpart_defaults)) {
	  if (subparts_for_this_type_qm)
	      result = VALUES_1(FIRST(subparts_for_this_type_qm));
	  else {
	      new_bit = slot_value_cons_1(slot_value_cons_1(part_type,Nil),
		      Nil);
	      M_CAR(cons_of_subparts_for_this_type) = new_bit;
	      result = VALUES_1(CAR(new_bit));
	  }
      }
      else if (EQ(part_feature,Qsubpart_exceptions)) {
	  if (subparts_for_this_type_qm) {
	      found_it_flag = Nil;
	      last_cons = Nil;
	      exceptional_part_template_cons = subparts_for_this_type_qm;
	      cantidate_result = Nil;
	      exceptional_part_index = Nil;
	    next_loop_1:
	      if ( !TRUEP(exceptional_part_template_cons))
		  goto end_loop_1;
	      cantidate_result = CAR(exceptional_part_template_cons);
	      exceptional_part_index = 
		      get_simple_part_feature(cantidate_result,Qpart_index);
	      if (NUM_EQ(exceptional_part_index,Part_index)) {
		  found_it_flag = T;
		  result = VALUES_1(cantidate_result);
		  goto end_2;
	      }
	      else if (NUM_GT(exceptional_part_index,Part_index)) {
		  found_it_flag = T;
		  new_bit = slot_value_cons_1(slot_value_list_3(part_type,
			  Qpart_index,Part_index),Nil);
		  if (last_cons) {
		      cdr_old_value = CDR(new_bit);
		      cdr_new_value = CDR(last_cons);
		      M_CDR(new_bit) = cdr_new_value;
		      M_CDR(last_cons) = new_bit;
		  }
		  else {
		      cdr_old_value = CDR(new_bit);
		      cdr_new_value = CAR(cons_of_subparts_for_this_type);
		      M_CDR(new_bit) = cdr_new_value;
		      M_CAR(cons_of_subparts_for_this_type) = new_bit;
		  }
		  result = VALUES_1(CAR(new_bit));
		  goto end_2;
	      }
	      last_cons = exceptional_part_template_cons;
	      exceptional_part_template_cons = 
		      M_CDR(exceptional_part_template_cons);
	      goto next_loop_1;
	    end_loop_1:
	      if ( !TRUEP(found_it_flag)) {
		  new_bit = slot_value_cons_1(slot_value_list_3(part_type,
			  Qpart_index,Part_index),Nil);
		  M_CDR(last_cons) = new_bit;
		  result = VALUES_1(CAR(new_bit));
		  goto end_2;
	      }
	      result = VALUES_1(Qnil);
	    end_2:;
	  }
	  else {
	      new_bit = slot_value_cons_1(slot_value_list_3(part_type,
		      Qpart_index,Part_index),Nil);
	      M_CAR(cons_of_subparts_for_this_type) = new_bit;
	      result = VALUES_1(CAR(new_bit));
	  }
      }
      else
	  result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* RECLAIM-FRAME-BEING-EDITED-VALUE */
Object reclaim_frame_being_edited_value(frame,gensymed_symbol)
    Object frame, gensymed_symbol;
{
    x_note_fn_call(170,102);
    return VALUES_1(Nil);
}

/* RECLAIM-ANNOTATION-CONTAINING-FEATURE-VALUE */
Object reclaim_annotation_containing_feature_value(annotation,gensymed_symbol)
    Object annotation, gensymed_symbol;
{
    x_note_fn_call(170,103);
    return VALUES_1(Nil);
}

/* RECLAIM-EDITABLE-SLOT-FOR-CELL-EXPRESSION-AND-TEXT-VALUE */
Object reclaim_editable_slot_for_cell_expression_and_text_value(cell_expression_and_text,
	    gensymed_symbol)
    Object cell_expression_and_text, gensymed_symbol;
{
    x_note_fn_call(170,104);
    return VALUES_1(Nil);
}

/* RECLAIM-REFERENCE-TO-DATA-IN-FRAME-CONTAINING-ANNOTATION-VALUE */
Object reclaim_reference_to_data_in_frame_containing_annotation_value(data_we_ignore,
	    gensymed_symbol)
    Object data_we_ignore, gensymed_symbol;
{
    x_note_fn_call(170,105);
    return VALUES_1(Nil);
}

/* RECLAIM-FRAME-SERIAL-NUMBER-OF-FRAME-BEING-EDITED-VALUE */
Object reclaim_frame_serial_number_of_frame_being_edited_value(serial_number,
	    annotation_editing_info)
    Object serial_number, annotation_editing_info;
{
    x_note_fn_call(170,106);
    reclaim_frame_serial_number(serial_number);
    ISVREF(annotation_editing_info,(SI_Long)17L) = Nil;
    return VALUES_1(Nil);
}

static Object Qannotation_editing_info;  /* annotation-editing-info */

static Object list_constant_4;     /* # */

static Object Qcell_format;        /* cell-format */

static Object Qreference_to_data_in_frame_containing_annotation;  /* reference-to-data-in-frame-containing-annotation */

static Object Qcell_expression_and_text;  /* cell-expression-and-text */

static Object Qeditable_slot_for_cell_expression_and_text;  /* editable-slot-for-cell-expression-and-text */

static Object Qfinish_edit_of_annotation_subexpression;  /* finish-edit-of-annotation-subexpression */

static Object Qcleanup_edit_of_annotation_subexpression;  /* cleanup-edit-of-annotation-subexpression */

static Object list_constant_5;     /* # */

static Object list_constant_6;     /* # */

/* START-EDIT-OF-ANNOTATION-SUBEXPRESSION */
Object start_edit_of_annotation_subexpression varargs_1(int, n)
{
    Object frame_containing_annotation, annotation_containing_feature;
    Object feature_to_edit, type_of_feature_being_edited;
    Object hide_workspace_p, temporary_frame_for_editor, slot_to_edit;
    Object frame_serial_number_setf_arg, old, new_1, svref_new_value;
    Object original_value, value_for_editor_to_work_on, temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(170,107);
    INIT_ARGS_nonrelocating();
    frame_containing_annotation = REQUIRED_ARG_nonrelocating();
    annotation_containing_feature = REQUIRED_ARG_nonrelocating();
    feature_to_edit = REQUIRED_ARG_nonrelocating();
    type_of_feature_being_edited = REQUIRED_ARG_nonrelocating();
    hide_workspace_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    highlight_part_of_frame(frame_containing_annotation,
	    annotation_containing_feature);
    temporary_frame_for_editor = make_frame(Qannotation_editing_info);
    slot_to_edit = Nil;
    ISVREF(temporary_frame_for_editor,(SI_Long)16L) = 
	    frame_containing_annotation;
    frame_serial_number_setf_arg = ISVREF(frame_containing_annotation,
	    (SI_Long)3L);
    old = ISVREF(temporary_frame_for_editor,(SI_Long)17L);
    new_1 = frame_serial_number_setf_arg;
    svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && (FIXNUMP(new_1) || 
	     !TRUEP(new_1)) ? new_1 : 
	    frame_serial_number_setf_helper_1(old,new_1);
    ISVREF(temporary_frame_for_editor,(SI_Long)17L) = svref_new_value;
    ISVREF(temporary_frame_for_editor,(SI_Long)18L) = 
	    annotation_containing_feature;
    ISVREF(temporary_frame_for_editor,(SI_Long)19L) = feature_to_edit;
    ISVREF(temporary_frame_for_editor,(SI_Long)20L) = 
	    type_of_feature_being_edited;
    slot_to_edit = getf(list_constant_4,type_of_feature_being_edited,_);
    original_value = EQ(T,feature_to_edit) ? annotation_containing_feature 
	    : get_simple_part_feature(annotation_containing_feature,
	    feature_to_edit);
    value_for_editor_to_work_on = EQ(type_of_feature_being_edited,
	    Qcell_format) ? original_value : 
	    copy_for_slot_value(original_value);
    if (EQ(type_of_feature_being_edited,Qcell_format)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(temporary_frame_for_editor,
		    Qreference_to_data_in_frame_containing_annotation);
	SVREF(temporary_frame_for_editor,FIX((SI_Long)22L)) = 
		value_for_editor_to_work_on;
    }
    else if (EQ(type_of_feature_being_edited,Qcell_expression_and_text)) {
	if (value_for_editor_to_work_on && 
		compiled_cell_expression_p(CAR(value_for_editor_to_work_on)))
	    remove_simple_part_feature_without_reclaiming(CAR(value_for_editor_to_work_on),
		    Qexpression_cell_index);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(temporary_frame_for_editor,
		    Qeditable_slot_for_cell_expression_and_text);
	SVREF(temporary_frame_for_editor,FIX((SI_Long)21L)) = 
		value_for_editor_to_work_on;
    }
    establish_next_workstation_context_continuation(Nil,
	    Qfinish_edit_of_annotation_subexpression,
	    temporary_frame_for_editor,
	    Qcleanup_edit_of_annotation_subexpression);
    temp = slot_to_edit;
    if (EQ(type_of_feature_being_edited,Qcell_expression_and_text))
	temp_1 = list_constant_5;
    else if (EQ(type_of_feature_being_edited,Qcell_format))
	temp_1 = list_constant_6;
    else
	temp_1 = error((SI_Long)2L,
		"start-edit-of-annotation-subexpression unknown type-of-feature-being-edited: ~S.",
		type_of_feature_being_edited);
    return enter_editing_context(15,temporary_frame_for_editor,temp,Nil,
	    hide_workspace_p,Nil,Nil,Nil,Nil,Nil,Nil,Nil,Nil,Nil,Nil,temp_1);
}

static Object Qediting;            /* editing */

/* DELETE-ALL-EDITORS-OF-CELL */
Object delete_all_editors_of_cell(part_description)
    Object part_description;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, annotation_editing_info;
    Object ab_loopvar__2, ab_loopvar__3, ab_loopvar__4, aei_list, workstation;
    Object ab_loop_list_, context, ab_loop_list__1, frame_list, frame;
    char temp;
    Declare_special(1);

    x_note_fn_call(170,108);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    annotation_editing_info = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar__2 = Nil;
      ab_loopvar__3 = Nil;
      ab_loopvar__4 = Nil;
      ab_loopvar_ = collect_subclasses(Qannotation_editing_info);
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
      annotation_editing_info = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      if (EQ(ISVREF(annotation_editing_info,(SI_Long)18L),part_description)) {
	  ab_loopvar__4 = gensym_cons_1(annotation_editing_info,Nil);
	  if (ab_loopvar__3)
	      M_CDR(ab_loopvar__3) = ab_loopvar__4;
	  else
	      ab_loopvar__2 = ab_loopvar__4;
	  ab_loopvar__3 = ab_loopvar__4;
      }
      goto next_loop;
    end_loop_1:
      aei_list = ab_loopvar__2;
      goto end_1;
      aei_list = Qnil;
    end_1:;
    POP_SPECIAL();
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    context = Nil;
    ab_loop_list__1 = ISVREF(workstation,(SI_Long)17L);
    ab_loopvar__2 = Nil;
    ab_loopvar__3 = Nil;
    ab_loopvar__4 = Nil;
  next_loop_3:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_3;
    context = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if (EQ(ISVREF(context,(SI_Long)1L),Qediting) && 
	    memq_function(ISVREF(context,(SI_Long)5L),aei_list)) {
	ab_loopvar__4 = gensym_cons_1(ISVREF(ISVREF(context,(SI_Long)2L),
		(SI_Long)12L),Nil);
	if (ab_loopvar__3)
	    M_CDR(ab_loopvar__3) = ab_loopvar__4;
	else
	    ab_loopvar__2 = ab_loopvar__4;
	ab_loopvar__3 = ab_loopvar__4;
    }
    goto next_loop_3;
  end_loop_3:
    goto end_2;
    ab_loopvar__2 = Qnil;
  end_2:;
    if (ab_loopvar__2) {
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = last(ab_loopvar__2,_);
    }
    goto next_loop_2;
  end_loop_2:
    frame_list = ab_loopvar_;
    goto end_3;
    frame_list = Qnil;
  end_3:;
    annotation_editing_info = Nil;
    ab_loop_list_ = aei_list;
  next_loop_4:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_4;
    annotation_editing_info = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ISVREF(annotation_editing_info,(SI_Long)18L) = Nil;
    goto next_loop_4;
  end_loop_4:;
    frame = Nil;
    ab_loop_list_ = frame_list;
  next_loop_5:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_5;
    frame = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    delete_frame(frame);
    goto next_loop_5;
  end_loop_5:;
    reclaim_gensym_list_1(aei_list);
    return reclaim_gensym_list_1(frame_list);
}

Object Cell_format_part_features = UNBOUND;

static Object Qframe_status_and_notes;  /* frame-status-and-notes */

static Object Qstack_change;       /* stack-change */

static Object Qbackground_color;   /* background-color */

static Object list_constant_7;     /* # */

static Object Qfreeform_table;     /* freeform-table */

static Object Qtable_cells;        /* table-cells */

static Object Qvirtual_attribute;  /* virtual-attribute */

/* PUT-REFERENCE-TO-DATA-IN-FRAME-CONTAINING-ANNOTATION */
Object put_reference_to_data_in_frame_containing_annotation(annotation_editing_info,
	    new_compiled_data,gensymed_symbol)
    Object annotation_editing_info, new_compiled_data, gensymed_symbol;
{
    Object original_slot_value, frame_being_edited;
    Object annotation_containing_feature, feature_of_annotation_being_edited;
    Object current_block_of_dependent_frame, needs_update_p, result_1;
    Object current_flag_state_qm, slot_description, new_cons, temp;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object stack_of_slot_value_changes, gensymed_symbol_2, gensymed_symbol_3;
    Object current_annotated_frame, original_slot_value_1, feature_key;
    Object feature_value, ab_loop_list_, temp_1, features_this_overrides;
    Object part_feature, ab_loop_list__1, possibly_embedded_computation;
    Object g2_cell_array, index_1, sub_class_bit_vector;
    Object projection_focus_method, projection_focus_annotation, frame;
    Object sub_vector_qm, function_qm, frame_and_slot_or_atom, ab_loop_it_;
    Object stack_change_pop_store, cons_1, next_cons;
    SI_Long svref_new_value_1, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_4, gensymed_symbol_5;
    SI_Long gensymed_symbol_6, method_index;
    char temp_2;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(5);
    Object result;

    x_note_fn_call(170,109);
    SAVE_STACK();
    original_slot_value = ISVREF(annotation_editing_info,(SI_Long)22L);
    frame_being_edited = ISVREF(annotation_editing_info,(SI_Long)16L);
    annotation_containing_feature = ISVREF(annotation_editing_info,
	    (SI_Long)18L);
    feature_of_annotation_being_edited = ISVREF(annotation_editing_info,
	    (SI_Long)19L);
    current_block_of_dependent_frame = frame_being_edited;
    PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
	    4);
      needs_update_p = Nil;
      result_1 = Nil;
      current_flag_state_qm = Nil;
      slot_description = 
	      get_slot_description_of_class_description_function(Qframe_status_and_notes,
	      ISVREF(frame_being_edited,(SI_Long)1L),Nil);
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
		  nconc2(stack_change_list_2(frame_being_edited,
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
	  M_CAR(gensymed_symbol_1) = frame_being_edited;
	  M_CDR(gensymed_symbol_1) = slot_description;
	  inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
      }
      M_CAR(gensymed_symbol) = gensymed_symbol_1;
      temp = Stack_of_slot_value_changes;
      M_CDR(gensymed_symbol) = temp;
      inline_note_allocate_cons(gensymed_symbol,Qstack_change);
      stack_of_slot_value_changes = gensymed_symbol;
      PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
	      3);
	current_flag_state_qm = (SI_Long)0L != 
		(IFIX(ISVREF(frame_being_edited,(SI_Long)5L)) & 
		(SI_Long)16777216L) ? T : Nil;
	if ( !TRUEP(current_flag_state_qm)) {
	    gensymed_symbol = 
		    ISVREF(ISVREF(ISVREF(ISVREF(frame_being_edited,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	    gensymed_symbol_1 = frame_being_edited;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = T;
	    inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	    svref_new_value_1 = IFIX(ISVREF(frame_being_edited,
		    (SI_Long)5L)) | (SI_Long)16777216L;
	    ISVREF(frame_being_edited,(SI_Long)5L) = FIX(svref_new_value_1);
	}
	LOCK(Working_on_annotated_frame);
	if (PUSH_UNWIND_PROTECT(0)) {
	    current_annotated_frame = frame_being_edited;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_annotated_frame,Qcurrent_annotated_frame,current_annotated_frame,
		    2);
	      erase_part_of_block(frame_being_edited,
		      annotation_containing_feature);
	      if (EQ(Qt,feature_of_annotation_being_edited)) {
		  original_slot_value_1 = ISVREF(annotation_editing_info,
			  (SI_Long)22L);
		  feature_key = Nil;
		  feature_value = Nil;
		  ab_loop_list_ = CDR(new_compiled_data);
		  temp_1 = ISVREF(annotation_editing_info,(SI_Long)20L);
		  features_this_overrides = EQ(temp_1,Qcell_format) ? 
			  Cell_format_part_features : Nil;
		  part_feature = Nil;
		  ab_loop_list__1 = features_this_overrides;
		  if (memq_function(Qbackground_color,
			      features_this_overrides)) {
		      possibly_embedded_computation = 
			      get_simple_part_feature(original_slot_value_1,
			      Qbackground_color);
		      if (compiled_cell_expression_p(possibly_embedded_computation)) 
				  {
			  temp_1 = 
				  get_lookup_slot_value_given_default(Current_block_of_dependent_frame,
				  Qcell_array,Nil);
			  deactivate_cell_of_g2_cell_array(temp_1,
				  get_simple_part_feature(possibly_embedded_computation,
				  Qexpression_cell_index));
		      }
		  }
		next_loop:
		  if ( !TRUEP(ab_loop_list__1))
		      goto end_loop;
		  part_feature = M_CAR(ab_loop_list__1);
		  ab_loop_list__1 = M_CDR(ab_loop_list__1);
		  remove_simple_part_feature(original_slot_value_1,
			  part_feature);
		  goto next_loop;
		end_loop:;
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_1;
		next_loop_1:
		  feature_key = CAR(ab_loop_list_);
		  temp_1 = CDR(ab_loop_list_);
		  feature_value = CAR(temp_1);
		  set_simple_part_feature(original_slot_value_1,
			  feature_key,copy_for_slot_value(feature_value));
		  if (memq_function(feature_key,list_constant_7))
		      needs_update_p = T;
		  if (compiled_cell_expression_p(feature_value)) {
		      g2_cell_array = 
			      get_lookup_slot_value_given_default(Current_block_of_dependent_frame,
			      Qcell_array,Nil);
		      index_1 = get_simple_part_feature(feature_value,
			      Qexpression_cell_index);
		      register_expression_cell_during_slot_putter(g2_cell_array,
			      index_1,Nil);
		  }
		  ab_loop_list_ = CDDR(ab_loop_list_);
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_1;
		  goto next_loop_1;
		end_loop_1:
		  reclaim_slot_value_list_1(new_compiled_data);
	      }
	      else;
	      if (G2_has_v5_mode_windows_p) {
		  gensymed_symbol = ISVREF(frame_being_edited,(SI_Long)1L);
		  gensymed_symbol_1 = 
			  lookup_global_or_kb_specific_property_value(Qfreeform_table,
			  Class_description_gkbprop);
		  if (gensymed_symbol_1) {
		      sub_class_bit_vector = ISVREF(gensymed_symbol,
			      (SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
		      sub_class_vector_index = superior_class_bit_number 
			      >>  -  - (SI_Long)3L;
		      if (sub_class_vector_index < 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				  {
			  gensymed_symbol_4 = 
				  UBYTE_8_ISAREF_1(sub_class_bit_vector,
				  sub_class_vector_index);
			  gensymed_symbol_5 = (SI_Long)1L;
			  gensymed_symbol_6 = superior_class_bit_number & 
				  (SI_Long)7L;
			  gensymed_symbol_5 = gensymed_symbol_5 << 
				  gensymed_symbol_6;
			  gensymed_symbol_4 = gensymed_symbol_4 & 
				  gensymed_symbol_5;
			  temp_2 = (SI_Long)0L < gensymed_symbol_4;
		      }
		      else
			  temp_2 = TRUEP(Nil);
		  }
		  else
		      temp_2 = TRUEP(Nil);
		  if (temp_2)
		      send_ws_representations_item_virtual_attribute_change(frame_being_edited,
			      get_property_value_function(3,
			      get_symbol_properties_function(Qtable_cells),
			      Qvirtual_attribute,Nil),Nil);
	      }
	      if (needs_update_p) {
		  projection_focus_method = Qannotation;
		  projection_focus_annotation = annotation_containing_feature;
		  PUSH_SPECIAL_WITH_SYMBOL(Projection_focus_annotation,Qprojection_focus_annotation,projection_focus_annotation,
			  1);
		    PUSH_SPECIAL_WITH_SYMBOL(Projection_focus_method,Qprojection_focus_method,projection_focus_method,
			    0);
		      method_index = (SI_Long)46L;
		      frame = frame_being_edited;
		      sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,
			      (SI_Long)1L),(SI_Long)11L),method_index);
		      function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,
			      (SI_Long)1L) : Nil;
		      if (function_qm)
			  inline_funcall_3(function_qm,frame,Qannotation,
				  annotation_containing_feature);
		    POP_SPECIAL();
		  POP_SPECIAL();
	      }
	      temp_1 = redraw_part_of_block(annotation_containing_feature);
	    POP_SPECIAL();
	    SAVE_VALUES(VALUES_1(temp_1));
	}
	POP_UNWIND_PROTECT(0);
	UNLOCK(Working_on_annotated_frame);
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
	result_1 = result;
	if ( !TRUEP(current_flag_state_qm)) {
	    svref_new_value_1 = IFIX(ISVREF(frame_being_edited,
		    (SI_Long)5L)) &  ~(SI_Long)16777216L;
	    ISVREF(frame_being_edited,(SI_Long)5L) = FIX(svref_new_value_1);
	    gensymed_symbol = 
		    ISVREF(ISVREF(ISVREF(ISVREF(frame_being_edited,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	    gensymed_symbol_1 = frame_being_edited;
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
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    frame_and_slot_or_atom = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (ATOM(frame_and_slot_or_atom))
		goto end_loop_2;
	    temp_2 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	    if (temp_2);
	    else {
		temp_1 = M_CDR(frame_and_slot_or_atom);
		temp_2 = CONSP(temp_1) ? EQ(slot_description,
			SECOND(frame_and_slot_or_atom)) && EQ(Nil,
			THIRD(frame_and_slot_or_atom)) && EQ(Nil,
			CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	    }
	    ab_loop_it_ = temp_2 ? (EQ(frame_being_edited,
		    M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
	    if (ab_loop_it_) {
		temp_2 = TRUEP(ab_loop_it_);
		goto end_1;
	    }
	    goto next_loop_2;
	  end_loop_2:
	    temp_2 = TRUEP(Qnil);
	  end_1:;
	}
	else
	    temp_2 = TRUEP(Nil);
	if ( !temp_2)
	    update_all_representations_of_slot(frame_being_edited,
		    slot_description,Nil,Nil);
	if (ISVREF(slot_description,(SI_Long)14L))
	    update_frame_name_references(frame_being_edited);
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
	    temp_1 = M_CAR(Stack_of_slot_value_changes);
	    temp_2 = ATOM(temp_1);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2 ?  
		!TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) : 
		TRUEP(Nil))
	    do_deferred_updates_to_representations_in_tables();
      POP_SPECIAL();
      result = VALUES_2(original_slot_value,T);
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object list_constant_8;     /* # */

/* FINISH-EDIT-OF-ANNOTATION-SUBEXPRESSION */
Object finish_edit_of_annotation_subexpression(edit_workstation_context)
    Object edit_workstation_context;
{
    Object temporary_frame_for_editor, frame_containing_annotation;
    Object supress_reclaiming_old_value_flag, current_block_of_dependent_frame;
    Object annotation_containing_feature, simple_type_of_feature;
    Object gensymed_symbol, gensymed_symbol_1, slot_that_was_edited;
    Declare_special(1);

    x_note_fn_call(170,110);
    temporary_frame_for_editor = ISVREF(edit_workstation_context,(SI_Long)5L);
    frame_containing_annotation = ISVREF(temporary_frame_for_editor,
	    (SI_Long)16L);
    supress_reclaiming_old_value_flag = Nil;
    current_block_of_dependent_frame = frame_containing_annotation;
    PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
	    0);
      annotation_containing_feature = ISVREF(temporary_frame_for_editor,
	      (SI_Long)18L);
      simple_type_of_feature = ISVREF(temporary_frame_for_editor,(SI_Long)20L);
      gensymed_symbol = ISVREF(temporary_frame_for_editor,(SI_Long)17L);
      gensymed_symbol_1 = ISVREF(frame_containing_annotation,(SI_Long)3L);
      if (FIXNUMP(gensymed_symbol) ? (FIXNUMP(gensymed_symbol_1) ? 
	      FIXNUM_EQ(gensymed_symbol,gensymed_symbol_1) : TRUEP(Nil)) : 
	      FIXNUMP(gensymed_symbol_1) ? TRUEP(Nil) : 
	      FIXNUM_EQ(M_CAR(gensymed_symbol),M_CAR(gensymed_symbol_1)) 
	      && FIXNUM_EQ(M_CDR(gensymed_symbol),M_CDR(gensymed_symbol_1))) {
	  erase_part_of_block(frame_containing_annotation,
		  annotation_containing_feature);
	  if ( !EQ(Qcell_format,simple_type_of_feature)) {
	      slot_that_was_edited = getf(list_constant_8,
		      simple_type_of_feature,_);
	      if (EQ(simple_type_of_feature,Qcell_format))
		  supress_reclaiming_old_value_flag = T;
	      change_annotation(frame_containing_annotation,
		      annotation_containing_feature,
		      ISVREF(temporary_frame_for_editor,(SI_Long)19L),
		      simple_type_of_feature,
		      supress_reclaiming_old_value_flag,
		      get_slot_value_function(temporary_frame_for_editor,
		      slot_that_was_edited,Nil));
	  }
	  unhighlight_part_of_frame(frame_containing_annotation,
		  annotation_containing_feature);
	  redraw_part_of_block(annotation_containing_feature);
      }
    POP_SPECIAL();
    return exit_current_workstation_context_in_return_function(Qediting);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

/* CLEANUP-EDIT-OF-ANNOTATION-SUBEXPRESSION */
Object cleanup_edit_of_annotation_subexpression(temporary_frame_for_editor)
    Object temporary_frame_for_editor;
{
    Object frame_containing_annotation, current_block_of_dependent_frame;
    Object annotation_containing_feature, gensymed_symbol, x, y, xa, ya;
    char temp;
    Declare_special(1);

    x_note_fn_call(170,111);
    frame_containing_annotation = ISVREF(temporary_frame_for_editor,
	    (SI_Long)16L);
    current_block_of_dependent_frame = frame_containing_annotation;
    PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
	    0);
      annotation_containing_feature = ISVREF(temporary_frame_for_editor,
	      (SI_Long)18L);
      gensymed_symbol = ISVREF(frame_containing_annotation,(SI_Long)3L);
      temp = SIMPLE_VECTOR_P(frame_containing_annotation) ? 
	      EQ(ISVREF(frame_containing_annotation,(SI_Long)1L),
	      Qavailable_frame_vector) : TRUEP(Qnil);
      if (temp);
      else
	  temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		  (SI_Long)-1L : TRUEP(Nil);
      if (temp);
      else {
	  x = gensymed_symbol;
	  y = ISVREF(temporary_frame_for_editor,(SI_Long)17L);
	  if (FIXNUMP(y))
	      temp = FIXNUMP(x) ? FIXNUM_LT(y,x) : TRUEP(T);
	  else if (FIXNUMP(x))
	      temp = TRUEP(Nil);
	  else {
	      xa = M_CAR(y);
	      ya = M_CAR(x);
	      temp = FIXNUM_LT(xa,ya);
	      if (temp);
	      else
		  temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),M_CDR(x)) : 
			  TRUEP(Qnil);
	  }
      }
      if ( !temp)
	  unhighlight_part_of_frame(frame_containing_annotation,
		  annotation_containing_feature);
    POP_SPECIAL();
    return delete_frame(temporary_frame_for_editor);
}

/* RECOMPILE-COMPONENT-OF-PART-DESCRIPTION */
Object recompile_component_of_part_description(part_description,
	    part_feature,type_of_feature)
    Object part_description, part_feature, type_of_feature;
{
    Object currently_supressing_part_highlighting, editing_context;
    Declare_special(2);
    Object result;

    x_note_fn_call(170,112);
    currently_supressing_part_highlighting = T;
    PUSH_SPECIAL_WITH_SYMBOL(Currently_supressing_part_highlighting,Qcurrently_supressing_part_highlighting,currently_supressing_part_highlighting,
	    1);
      start_edit_of_annotation_subexpression(5,Current_computation_frame,
	      part_description,part_feature,type_of_feature,T);
      editing_context = Current_workstation_context;
      PUSH_SPECIAL_WITH_SYMBOL(Editing_context,Qediting_context,editing_context,
	      0);
	finish_parsing_insofar_as_possible();
	if (Keep_edit_workspace_hidden_no_matter_what_qm && 
		EQ(Current_workstation_context,Editing_context))
	    result = return_from_current_workstation_context(1,Qediting);
	else
	    result = VALUES_1(Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qcell_expression;    /* cell-expression */

/* CHANGE-ANNOTATION */
Object change_annotation(frame_containing_annotation,annotation,
	    part_feature_or_t,simple_type_of_feature,
	    supress_reclaiming_old_value_flag,new_value)
    Object frame_containing_annotation, annotation, part_feature_or_t;
    Object simple_type_of_feature, supress_reclaiming_old_value_flag;
    Object new_value;
{
    Object result_1, current_flag_state_qm, slot_description, new_cons, temp;
    Object svref_arg_2, svref_new_value, gensymed_symbol, gensymed_symbol_1;
    Object stack_of_slot_value_changes, gensymed_symbol_2, gensymed_symbol_3;
    Object current_annotated_frame, cdr_old_value, temp_1, old_part_features;
    Object projection_focus_method, projection_focus_annotation;
    Object sub_class_bit_vector, frame_and_slot_or_atom, ab_loop_list_;
    Object ab_loop_it_, stack_change_pop_store, cons_1, next_cons;
    SI_Long svref_new_value_1, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_4, gensymed_symbol_5;
    SI_Long gensymed_symbol_6;
    char temp_2;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(4);
    Object result;

    x_note_fn_call(170,113);
    SAVE_STACK();
    result_1 = Nil;
    current_flag_state_qm = Nil;
    slot_description = 
	    get_slot_description_of_class_description_function(Qframe_status_and_notes,
	    ISVREF(frame_containing_annotation,(SI_Long)1L),Nil);
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
		nconc2(stack_change_list_2(frame_containing_annotation,
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
	M_CAR(gensymed_symbol_1) = frame_containing_annotation;
	M_CDR(gensymed_symbol_1) = slot_description;
	inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
    }
    M_CAR(gensymed_symbol) = gensymed_symbol_1;
    temp = Stack_of_slot_value_changes;
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qstack_change);
    stack_of_slot_value_changes = gensymed_symbol;
    PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
	    3);
      current_flag_state_qm = (SI_Long)0L != 
	      (IFIX(ISVREF(frame_containing_annotation,(SI_Long)5L)) & 
	      (SI_Long)16777216L) ? T : Nil;
      if ( !TRUEP(current_flag_state_qm)) {
	  gensymed_symbol = 
		  ISVREF(ISVREF(ISVREF(ISVREF(frame_containing_annotation,
		  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	  gensymed_symbol_1 = frame_containing_annotation;
	  gensymed_symbol_2 = Nil;
	  gensymed_symbol_3 = T;
	  inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		  gensymed_symbol_2,gensymed_symbol_3);
	  svref_new_value_1 = IFIX(ISVREF(frame_containing_annotation,
		  (SI_Long)5L)) | (SI_Long)16777216L;
	  ISVREF(frame_containing_annotation,(SI_Long)5L) = 
		  FIX(svref_new_value_1);
      }
      LOCK(Working_on_annotated_frame);
      if (PUSH_UNWIND_PROTECT(0)) {
	  current_annotated_frame = frame_containing_annotation;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_annotated_frame,Qcurrent_annotated_frame,current_annotated_frame,
		  2);
	    erase_part_of_block(frame_containing_annotation,annotation);
	    if (EQ(T,part_feature_or_t)) {
		cdr_old_value = CDR(annotation);
		temp = CDR(new_value);
		M_CDR(annotation) = temp;
		M_CDR(new_value) = Nil;
		temp_1 = cdr_old_value;
		old_part_features = temp_1;
		if ( !TRUEP(supress_reclaiming_old_value_flag))
		    reclaim_part_features(CAR(annotation),old_part_features);
		reclaim_slot_value_cons_1(new_value);
	    }
	    else if (EQ(Qcell_contents,part_feature_or_t) &&  
		    !TRUEP(CAR(new_value))) {
		remove_simple_part_feature(annotation,part_feature_or_t);
		reclaim_part_feature(CAR(annotation),part_feature_or_t,
			new_value);
	    }
	    else
		set_simple_part_feature(annotation,part_feature_or_t,
			new_value);
	    projection_focus_method = Qannotation;
	    projection_focus_annotation = annotation;
	    PUSH_SPECIAL_WITH_SYMBOL(Projection_focus_annotation,Qprojection_focus_annotation,projection_focus_annotation,
		    1);
	      PUSH_SPECIAL_WITH_SYMBOL(Projection_focus_method,Qprojection_focus_method,projection_focus_method,
		      0);
		gensymed_symbol = 
			ISVREF(ISVREF(ISVREF(ISVREF(Current_annotated_frame,
			(SI_Long)1L),(SI_Long)11L),(SI_Long)46L),(SI_Long)1L);
		gensymed_symbol_1 = Current_annotated_frame;
		gensymed_symbol_2 = Qannotation;
		gensymed_symbol_3 = annotation;
		inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
			gensymed_symbol_2,gensymed_symbol_3);
	      POP_SPECIAL();
	    POP_SPECIAL();
	    redraw_part_of_block(annotation);
	    if (G2_has_v5_mode_windows_p) {
		gensymed_symbol = ISVREF(frame_containing_annotation,
			(SI_Long)1L);
		gensymed_symbol_1 = 
			lookup_global_or_kb_specific_property_value(Qfreeform_table,
			Class_description_gkbprop);
		if (gensymed_symbol_1) {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_4 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_5 = (SI_Long)1L;
			gensymed_symbol_6 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_5 = gensymed_symbol_5 << 
				gensymed_symbol_6;
			gensymed_symbol_4 = gensymed_symbol_4 & 
				gensymed_symbol_5;
			temp_2 = (SI_Long)0L < gensymed_symbol_4;
		    }
		    else
			temp_2 = TRUEP(Nil);
		}
		else
		    temp_2 = TRUEP(Nil);
		if (temp_2)
		    send_ws_representations_item_virtual_attribute_change(frame_containing_annotation,
			    get_property_value_function(3,
			    get_symbol_properties_function(Qtable_cells),
			    Qvirtual_attribute,Nil),Nil);
	    }
	    if (EQ(simple_type_of_feature,Qcell_expression_and_text)) {
		if (compiled_cell_expression_p(CAR(new_value))) {
		    temp_1 = 
			    get_lookup_slot_value_given_default(frame_containing_annotation,
			    Qcell_array,Nil);
		    temp_1 = 
			    register_expression_cell_during_slot_putter(temp_1,
			    get_simple_part_feature(CAR(new_value),
			    Qexpression_cell_index),Nil);
		}
		else
		    temp_1 = Nil;
	    }
	    else if (EQ(simple_type_of_feature,Qcell_expression)) {
		if (compiled_cell_expression_p(new_value)) {
		    temp_1 = 
			    get_lookup_slot_value_given_default(frame_containing_annotation,
			    Qcell_array,Nil);
		    temp_1 = 
			    register_expression_cell_during_slot_putter(temp_1,
			    get_simple_part_feature(new_value,
			    Qexpression_cell_index),Nil);
		}
		else
		    temp_1 = Nil;
	    }
	    else
		temp_1 = Qnil;
	  POP_SPECIAL();
	  SAVE_VALUES(VALUES_1(temp_1));
      }
      POP_UNWIND_PROTECT(0);
      UNLOCK(Working_on_annotated_frame);
      CONTINUE_UNWINDING(0);
      result = RESTORE_VALUES();
      result_1 = result;
      if ( !TRUEP(current_flag_state_qm)) {
	  svref_new_value_1 = IFIX(ISVREF(frame_containing_annotation,
		  (SI_Long)5L)) &  ~(SI_Long)16777216L;
	  ISVREF(frame_containing_annotation,(SI_Long)5L) = 
		  FIX(svref_new_value_1);
	  gensymed_symbol = 
		  ISVREF(ISVREF(ISVREF(ISVREF(frame_containing_annotation,
		  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	  gensymed_symbol_1 = frame_containing_annotation;
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
	      temp_1 = M_CDR(frame_and_slot_or_atom);
	      temp_2 = CONSP(temp_1) ? EQ(slot_description,
		      SECOND(frame_and_slot_or_atom)) && EQ(Nil,
		      THIRD(frame_and_slot_or_atom)) && EQ(Nil,
		      CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	  }
	  ab_loop_it_ = temp_2 ? (EQ(frame_containing_annotation,
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
	  update_all_representations_of_slot(frame_containing_annotation,
		  slot_description,Nil,Nil);
      if (ISVREF(slot_description,(SI_Long)14L))
	  update_frame_name_references(frame_containing_annotation);
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
	  temp_1 = M_CAR(Stack_of_slot_value_changes);
	  temp_2 = ATOM(temp_1);
      }
      else
	  temp_2 = TRUEP(Nil);
      if (temp_2 ?  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) :
	       TRUEP(Nil))
	  do_deferred_updates_to_representations_in_tables();
    POP_SPECIAL();
    RESTORE_STACK();
    return VALUES_1(result_1);
}

static Object Qcomputation_style_tracing_and_breakpoints;  /* computation-style-tracing-and-breakpoints */

/* ENTER-TRACING-OR-BREAKPOINTS-SETTING */
Object enter_tracing_or_breakpoints_setting(new_value,shift)
    Object new_value, shift;
{
    Object original_computation_style_tracing_and_breakpoints, svref_arg_1;
    Object temp, svref_new_value;

    x_note_fn_call(170,114);
    original_computation_style_tracing_and_breakpoints = 
	    ISVREF(Current_computation_style,(SI_Long)22L);
    Part_feature_recall_stack = 
	    part_stack_cons_1(original_computation_style_tracing_and_breakpoints,
	    Part_feature_recall_stack);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_computation_style,
		Qcomputation_style_tracing_and_breakpoints);
    svref_arg_1 = Current_computation_style;
    temp = original_computation_style_tracing_and_breakpoints;
    if (temp);
    else
	temp = Completely_unspecified_debugging_code;
    svref_new_value = logior(logandc2(temp,ash(Message_field_mask,shift)),
	    ash(new_value,shift));
    SVREF(svref_arg_1,FIX((SI_Long)22L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* EXIT-TRACING-OR-BREAKPOINTS-SETTING */
Object exit_tracing_or_breakpoints_setting()
{
    Object svref_arg_1, part_stack_pop_store, cons_1, next_cons, temp;
    Object svref_arg_2;

    x_note_fn_call(170,115);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_computation_style,
		Qcomputation_style_tracing_and_breakpoints);
    svref_arg_1 = Current_computation_style;
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    SVREF(svref_arg_1,FIX((SI_Long)22L)) = part_stack_pop_store;
    return VALUES_1(Nil);
}

/* ENTER-WARNING-LEVEL */
Object enter_warning_level(warning_level)
    Object warning_level;
{
    x_note_fn_call(170,116);
    enter_tracing_or_breakpoints_setting(warning_level,Warning_shift);
    return VALUES_1(Nil);
}

/* ENTER-TRACING-LEVEL */
Object enter_tracing_level(tracing_level)
    Object tracing_level;
{
    x_note_fn_call(170,117);
    enter_tracing_or_breakpoints_setting(tracing_level,Tracing_shift);
    return VALUES_1(Nil);
}

/* ENTER-BREAK-LEVEL */
Object enter_break_level(break_level)
    Object break_level;
{
    x_note_fn_call(170,118);
    enter_tracing_or_breakpoints_setting(break_level,Breakpoint_shift);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Computation_style_description, Qcomputation_style_description);

DEFINE_VARIABLE_WITH_SYMBOL(Current_computation_style_description, Qcurrent_computation_style_description);

static Object Qcomputation_style_priority;  /* computation-style-priority */

/* ENTER-PART-FEATURE-PRIORITY */
Object enter_part_feature_priority(new_value)
    Object new_value;
{
    Object svref_arg_1;

    x_note_fn_call(170,119);
    Part_feature_recall_stack = 
	    part_stack_cons_1(ISVREF(Current_computation_style,
	    (SI_Long)18L),Part_feature_recall_stack);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_computation_style,
		Qcomputation_style_priority);
    svref_arg_1 = Current_computation_style;
    SVREF(svref_arg_1,FIX((SI_Long)18L)) = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-PRIORITY */
Object exit_part_feature_priority()
{
    Object svref_arg_1, part_stack_pop_store, cons_1, next_cons, temp;
    Object svref_arg_2;

    x_note_fn_call(170,120);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_computation_style,
		Qcomputation_style_priority);
    svref_arg_1 = Current_computation_style;
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    SVREF(svref_arg_1,FIX((SI_Long)18L)) = part_stack_pop_store;
    return VALUES_1(Nil);
}

static Object Qcomputation_style_scan_interval;  /* computation-style-scan-interval */

/* ENTER-PART-FEATURE-SCAN-INTERVAL */
Object enter_part_feature_scan_interval(new_value)
    Object new_value;
{
    Object svref_arg_1;

    x_note_fn_call(170,121);
    Part_feature_recall_stack = 
	    part_stack_cons_1(ISVREF(Current_computation_style,
	    (SI_Long)19L),Part_feature_recall_stack);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_computation_style,
		Qcomputation_style_scan_interval);
    svref_arg_1 = Current_computation_style;
    SVREF(svref_arg_1,FIX((SI_Long)19L)) = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-SCAN-INTERVAL */
Object exit_part_feature_scan_interval()
{
    Object svref_arg_1, part_stack_pop_store, cons_1, next_cons, temp;
    Object svref_arg_2;

    x_note_fn_call(170,122);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_computation_style,
		Qcomputation_style_scan_interval);
    svref_arg_1 = Current_computation_style;
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    SVREF(svref_arg_1,FIX((SI_Long)19L)) = part_stack_pop_store;
    return VALUES_1(Nil);
}

static Object Qcomputation_style_initial_scan_wait_interval;  /* computation-style-initial-scan-wait-interval */

/* ENTER-PART-FEATURE-INITIAL-SCAN-WAIT-INTERVAL */
Object enter_part_feature_initial_scan_wait_interval(new_value)
    Object new_value;
{
    Object svref_arg_1;

    x_note_fn_call(170,123);
    Part_feature_recall_stack = 
	    part_stack_cons_1(ISVREF(Current_computation_style,
	    (SI_Long)20L),Part_feature_recall_stack);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_computation_style,
		Qcomputation_style_initial_scan_wait_interval);
    svref_arg_1 = Current_computation_style;
    SVREF(svref_arg_1,FIX((SI_Long)20L)) = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-INITIAL-SCAN-WAIT-INTERVAL */
Object exit_part_feature_initial_scan_wait_interval()
{
    Object svref_arg_1, part_stack_pop_store, cons_1, next_cons, temp;
    Object svref_arg_2;

    x_note_fn_call(170,124);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_computation_style,
		Qcomputation_style_initial_scan_wait_interval);
    svref_arg_1 = Current_computation_style;
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    SVREF(svref_arg_1,FIX((SI_Long)20L)) = part_stack_pop_store;
    return VALUES_1(Nil);
}

static Object Qcomputation_style_value_domain;  /* computation-style-value-domain */

/* ENTER-PART-FEATURE-VALUE-DOMAIN */
Object enter_part_feature_value_domain(new_value)
    Object new_value;
{
    Object svref_arg_1;

    x_note_fn_call(170,125);
    Part_feature_recall_stack = 
	    part_stack_cons_1(ISVREF(Current_computation_style,
	    (SI_Long)27L),Part_feature_recall_stack);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_computation_style,
		Qcomputation_style_value_domain);
    svref_arg_1 = Current_computation_style;
    SVREF(svref_arg_1,FIX((SI_Long)27L)) = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-VALUE-DOMAIN */
Object exit_part_feature_value_domain()
{
    Object svref_arg_1, part_stack_pop_store, cons_1, next_cons, temp;
    Object svref_arg_2;

    x_note_fn_call(170,126);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_computation_style,
		Qcomputation_style_value_domain);
    svref_arg_1 = Current_computation_style;
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    SVREF(svref_arg_1,FIX((SI_Long)27L)) = part_stack_pop_store;
    return VALUES_1(Nil);
}

static Object Qcomputation_style_update_only_when_shown;  /* computation-style-update-only-when-shown */

/* ENTER-PART-FEATURE-UPDATE-ONLY-WHEN-SHOWN */
Object enter_part_feature_update_only_when_shown(new_value)
    Object new_value;
{
    Object svref_arg_1;

    x_note_fn_call(170,127);
    Part_feature_recall_stack = 
	    part_stack_cons_1(ISVREF(Current_computation_style,
	    (SI_Long)21L),Part_feature_recall_stack);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_computation_style,
		Qcomputation_style_update_only_when_shown);
    svref_arg_1 = Current_computation_style;
    SVREF(svref_arg_1,FIX((SI_Long)21L)) = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-UPDATE-ONLY-WHEN-SHOWN */
Object exit_part_feature_update_only_when_shown()
{
    Object svref_arg_1, part_stack_pop_store, cons_1, next_cons, temp;
    Object svref_arg_2;

    x_note_fn_call(170,128);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_computation_style,
		Qcomputation_style_update_only_when_shown);
    svref_arg_1 = Current_computation_style;
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    SVREF(svref_arg_1,FIX((SI_Long)21L)) = part_stack_pop_store;
    return VALUES_1(Nil);
}

static Object Qcomputation_style_may_request_event_updates;  /* computation-style-may-request-event-updates */

/* ENTER-PART-FEATURE-MAY-REQUEST-EVENT-UPDATES */
Object enter_part_feature_may_request_event_updates(new_value)
    Object new_value;
{
    Object svref_arg_1;

    x_note_fn_call(170,129);
    Part_feature_recall_stack = 
	    part_stack_cons_1(ISVREF(Current_computation_style,
	    (SI_Long)23L),Part_feature_recall_stack);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_computation_style,
		Qcomputation_style_may_request_event_updates);
    svref_arg_1 = Current_computation_style;
    SVREF(svref_arg_1,FIX((SI_Long)23L)) = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-MAY-REQUEST-EVENT-UPDATES */
Object exit_part_feature_may_request_event_updates()
{
    Object svref_arg_1, part_stack_pop_store, cons_1, next_cons, temp;
    Object svref_arg_2;

    x_note_fn_call(170,130);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_computation_style,
		Qcomputation_style_may_request_event_updates);
    svref_arg_1 = Current_computation_style;
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    SVREF(svref_arg_1,FIX((SI_Long)23L)) = part_stack_pop_store;
    return VALUES_1(Nil);
}

static Object Qcomputation_style_may_request_data_seeking;  /* computation-style-may-request-data-seeking */

/* ENTER-PART-FEATURE-MAY-REQUEST-DATA-SEEKING */
Object enter_part_feature_may_request_data_seeking(new_value)
    Object new_value;
{
    Object svref_arg_1;

    x_note_fn_call(170,131);
    Part_feature_recall_stack = 
	    part_stack_cons_1(ISVREF(Current_computation_style,
	    (SI_Long)24L),Part_feature_recall_stack);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_computation_style,
		Qcomputation_style_may_request_data_seeking);
    svref_arg_1 = Current_computation_style;
    SVREF(svref_arg_1,FIX((SI_Long)24L)) = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-MAY-REQUEST-DATA-SEEKING */
Object exit_part_feature_may_request_data_seeking()
{
    Object svref_arg_1, part_stack_pop_store, cons_1, next_cons, temp;
    Object svref_arg_2;

    x_note_fn_call(170,132);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_computation_style,
		Qcomputation_style_may_request_data_seeking);
    svref_arg_1 = Current_computation_style;
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    SVREF(svref_arg_1,FIX((SI_Long)24L)) = part_stack_pop_store;
    return VALUES_1(Nil);
}

static Object Qcomputation_style_time_out_when_requesting_data_seeking;  /* computation-style-time-out-when-requesting-data-seeking */

/* ENTER-PART-FEATURE-TIME-OUT-WHEN-REQUESTING-DATA-SEEKING */
Object enter_part_feature_time_out_when_requesting_data_seeking(new_value)
    Object new_value;
{
    Object svref_arg_1;

    x_note_fn_call(170,133);
    Part_feature_recall_stack = 
	    part_stack_cons_1(ISVREF(Current_computation_style,
	    (SI_Long)29L),Part_feature_recall_stack);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_computation_style,
		Qcomputation_style_time_out_when_requesting_data_seeking);
    svref_arg_1 = Current_computation_style;
    SVREF(svref_arg_1,FIX((SI_Long)29L)) = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-TIME-OUT-WHEN-REQUESTING-DATA-SEEKING */
Object exit_part_feature_time_out_when_requesting_data_seeking()
{
    Object svref_arg_1, part_stack_pop_store, cons_1, next_cons, temp;
    Object svref_arg_2;

    x_note_fn_call(170,134);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_computation_style,
		Qcomputation_style_time_out_when_requesting_data_seeking);
    svref_arg_1 = Current_computation_style;
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    SVREF(svref_arg_1,FIX((SI_Long)29L)) = part_stack_pop_store;
    return VALUES_1(Nil);
}

static Object Qcomputation_style_may_provide_data_on_request;  /* computation-style-may-provide-data-on-request */

/* ENTER-PART-FEATURE-MAY-PROVIDE-DATA-ON-REQUEST */
Object enter_part_feature_may_provide_data_on_request(new_value)
    Object new_value;
{
    Object svref_arg_1;

    x_note_fn_call(170,135);
    Part_feature_recall_stack = 
	    part_stack_cons_1(ISVREF(Current_computation_style,
	    (SI_Long)25L),Part_feature_recall_stack);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_computation_style,
		Qcomputation_style_may_provide_data_on_request);
    svref_arg_1 = Current_computation_style;
    SVREF(svref_arg_1,FIX((SI_Long)25L)) = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-MAY-PROVIDE-DATA-ON-REQUEST */
Object exit_part_feature_may_provide_data_on_request()
{
    Object svref_arg_1, part_stack_pop_store, cons_1, next_cons, temp;
    Object svref_arg_2;

    x_note_fn_call(170,136);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_computation_style,
		Qcomputation_style_may_provide_data_on_request);
    svref_arg_1 = Current_computation_style;
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    SVREF(svref_arg_1,FIX((SI_Long)25L)) = part_stack_pop_store;
    return VALUES_1(Nil);
}

static Object Qcomputation_style_may_provide_event_updates;  /* computation-style-may-provide-event-updates */

/* ENTER-PART-FEATURE-MAY-PROVIDE-EVENT-UPDATES */
Object enter_part_feature_may_provide_event_updates(new_value)
    Object new_value;
{
    Object svref_arg_1;

    x_note_fn_call(170,137);
    Part_feature_recall_stack = 
	    part_stack_cons_1(ISVREF(Current_computation_style,
	    (SI_Long)26L),Part_feature_recall_stack);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_computation_style,
		Qcomputation_style_may_provide_event_updates);
    svref_arg_1 = Current_computation_style;
    SVREF(svref_arg_1,FIX((SI_Long)26L)) = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-MAY-PROVIDE-EVENT-UPDATES */
Object exit_part_feature_may_provide_event_updates()
{
    Object svref_arg_1, part_stack_pop_store, cons_1, next_cons, temp;
    Object svref_arg_2;

    x_note_fn_call(170,138);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_computation_style,
		Qcomputation_style_may_provide_event_updates);
    svref_arg_1 = Current_computation_style;
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    SVREF(svref_arg_1,FIX((SI_Long)26L)) = part_stack_pop_store;
    return VALUES_1(Nil);
}

/* ENTER-PART-FEATURE-UPDATE-AFTER-EDITS */
Object enter_part_feature_update_after_edits(new_value)
    Object new_value;
{
    Object svref_arg_1;

    x_note_fn_call(170,139);
    Part_feature_recall_stack = 
	    part_stack_cons_1(ISVREF(Current_computation_style,
	    (SI_Long)26L),Part_feature_recall_stack);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_computation_style,
		Qcomputation_style_may_provide_event_updates);
    svref_arg_1 = Current_computation_style;
    SVREF(svref_arg_1,FIX((SI_Long)26L)) = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-UPDATE-AFTER-EDITS */
Object exit_part_feature_update_after_edits()
{
    Object svref_arg_1, part_stack_pop_store, cons_1, next_cons, temp;
    Object svref_arg_2;

    x_note_fn_call(170,140);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_computation_style,
		Qcomputation_style_may_provide_event_updates);
    svref_arg_1 = Current_computation_style;
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    SVREF(svref_arg_1,FIX((SI_Long)26L)) = part_stack_pop_store;
    return VALUES_1(Nil);
}

static Object Qcomputation_style_network_access_attempt;  /* computation-style-network-access-attempt */

/* ENTER-PART-FEATURE-NETWORK-ACCESS-ATTEMPT */
Object enter_part_feature_network_access_attempt(new_value)
    Object new_value;
{
    Object svref_arg_1;

    x_note_fn_call(170,141);
    Part_feature_recall_stack = 
	    part_stack_cons_1(ISVREF(Current_computation_style,
	    (SI_Long)32L),Part_feature_recall_stack);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_computation_style,
		Qcomputation_style_network_access_attempt);
    svref_arg_1 = Current_computation_style;
    SVREF(svref_arg_1,FIX((SI_Long)32L)) = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-NETWORK-ACCESS-ATTEMPT */
Object exit_part_feature_network_access_attempt()
{
    Object svref_arg_1, part_stack_pop_store, cons_1, next_cons, temp;
    Object svref_arg_2;

    x_note_fn_call(170,142);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(Current_computation_style,
		Qcomputation_style_network_access_attempt);
    svref_arg_1 = Current_computation_style;
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    SVREF(svref_arg_1,FIX((SI_Long)32L)) = part_stack_pop_store;
    return VALUES_1(Nil);
}

/* REDUCE-COMMON-COMPUTATION-PHRASE-SCAN-INTERVAL */
Object reduce_common_computation_phrase_scan_interval(parse)
    Object parse;
{
    Object temp, third_new_value;

    x_note_fn_call(170,143);
    temp = THIRD(parse);
    third_new_value = CAR(temp);
    M_THIRD(parse) = third_new_value;
    return reduce_annotation(parse);
}

static Object list_constant_9;     /* # */

static Object Qscan_interval;      /* scan-interval */

static Object Qpriority;           /* priority */

static Object string_constant_18;  /* "~%  " */

static Object string_constant_19;  /* "evaluated" */

static Object string_constant_20;  /* " every ~NC" */

static Object Qseconds;            /* seconds */

static Object string_constant_21;  /* " at priority ~D" */

static Object string_constant_22;  /* "evaluated with these settings:~%" */

/* TWRITE-COMPUTATION-STYLE */
Object twrite_computation_style(computation_style,on_fresh_line)
    Object computation_style, on_fresh_line;
{
    Object part_features_of_computation_style, use_none, scan_interval;
    Object priority, use_short_form, feature, value, ab_loop_list_, temp;

    x_note_fn_call(170,144);
    part_features_of_computation_style = list_constant_9;
    use_none = T;
    scan_interval = Nil;
    priority = Nil;
    use_short_form = T;
    feature = Nil;
    value = Nil;
    ab_loop_list_ = CDR(computation_style);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    feature = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    value = CAR(temp);
    if (memq_function(feature,part_features_of_computation_style)) {
	use_none = Nil;
	if (EQ(feature,Qscan_interval))
	    scan_interval = value;
	else if (EQ(feature,Qpriority))
	    priority = value;
	else
	    use_short_form = Nil;
    }
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:;
    temp = use_none;
    if (temp)
	return VALUES_1(temp);
    else if (use_short_form) {
	if (on_fresh_line)
	    tformat(1,string_constant_18);
	tformat(1,string_constant_19);
	if (scan_interval)
	    tformat(3,string_constant_20,scan_interval,Qseconds);
	if (priority)
	    return tformat(2,string_constant_21,priority);
	else
	    return VALUES_1(Nil);
    }
    else {
	if (on_fresh_line)
	    tformat(1,string_constant_18);
	tformat(1,string_constant_22);
	return write_part_description(4,computation_style,
		part_features_of_computation_style,FIX((SI_Long)4L),T);
    }
}

static Object array_constant_4;    /* # */

/* WRITE-COMPUTATION-STYLE-OR-NONE-FROM-SLOT */
Object write_computation_style_or_none_from_slot(computation_style_or_none,
	    gensymed_symbol)
    Object computation_style_or_none, gensymed_symbol;
{
    x_note_fn_call(170,145);
    if (computation_style_or_none)
	return twrite_computation_style(computation_style_or_none,Nil);
    else
	return twrite_beginning_of_wide_string(array_constant_4,
		FIX((SI_Long)4L));
}

/* COMPILE-COMPUTATION-STYLE-OR-NONE-FOR-SLOT */
Object compile_computation_style_or_none_for_slot varargs_1(int, n)
{
    Object parse_result, frame_containing_annotation, gensymed_symbol;
    volatile Object result_1;
    volatile Object error_message_qm;
    Object current_block_of_dependent_frame, current_annotated_frame;
    Object current_computation_style;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(3);
    Object result;

    x_note_fn_call(170,146);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame_containing_annotation = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    result_1 = Nil;
    error_message_qm = Nil;
    LOCK(Working_on_annotated_frame);
    if (PUSH_UNWIND_PROTECT(0)) {
	current_block_of_dependent_frame = 
		ISVREF(frame_containing_annotation,(SI_Long)16L);
	current_annotated_frame = frame_containing_annotation;
	current_computation_style = The_only_dynamic_computation_style;
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_style,Qcurrent_computation_style,current_computation_style,
		2);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_annotated_frame,Qcurrent_annotated_frame,current_annotated_frame,
		  1);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
		    0);
	      result = compile_part_description(parse_result,
		      Qcomputation_style_description);
	      MVS_2(result,result_1,error_message_qm);
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    POP_UNWIND_PROTECT(0);
    UNLOCK(Working_on_annotated_frame);
    CONTINUE_UNWINDING(0);
    result = VALUES_2(result_1,error_message_qm);
    RESTORE_STACK();
    return result;
}

static Object list_constant_10;    /* # */

static Object list_constant_11;    /* # */

static Object list_constant_12;    /* # */

static Object list_constant_13;    /* # */

static Object Qtruth_value;        /* truth-value */

static Object string_constant_23;  /* "~NT " */

static Object string_constant_24;  /* "~NV must be one of the following types: ~a" */

/* COMPUTATION-STYLE-OR-NONE-EVALUATION-SETTER */
Object computation_style_or_none_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object feature_name, attribute_value, feature_value, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string;
    SI_Long next_index, length_1, gensymed_symbol_1, bv16_length, aref_arg_2;
    SI_Long aref_new_value, length_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(170,147);
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
			  list_constant_10))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_11,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_computation_style_or_none_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_12))
	result = VALUES_1(Nil);
    else if (type_specification_type_p(gensymed_symbol,list_constant_13)) {
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	feature_name = Nil;
	attribute_value = Nil;
	feature_value = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop:
	if (next_index >= length_1)
	    goto end_loop;
	feature_name = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	gensymed_symbol_1 = next_index + (SI_Long)1L;
	attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		gensymed_symbol_1 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		(SI_Long)1023L);
	feature_value = validate_item_or_evaluation_value(attribute_value,
		Nil,Nil);
	next_index = next_index + (SI_Long)2L;
	temp_1 = phrase_list_2(Qquote,feature_name);
	ab_loopvar__2 = phrase_cons(phrase_list_4(Qset_simple_part_feature,
		Qcurrent_part_description,temp_1,
		phrase_list_2(Qcopy_for_slot_value,phrase_list_2(Qquote,
		CONSP(feature_value) && EQ(M_CDR(feature_value),
		Qtruth_value) ? 
		evaluation_truth_value_is_true_p(feature_value) : 
		feature_value))),Nil);
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
	result = phrase_cons(Qprogn,temp_1);
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
		  tformat(2,string_constant_23,list_constant_12);
		  tformat(2,string_constant_23,list_constant_13);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_24,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_computation_style_or_none_evaluation_setter:
    return result;
}

static Object Qfloat_array;        /* float-array */

/* COMPUTATION-STYLE-OR-NONE-EVALUATION-GETTER */
Object computation_style_or_none_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object feature_name, feature_value, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, temp, amf_available_array_cons_qm;
    Object amf_array, temp_1, temp_2, amf_result, new_float, gensymed_symbol;
    Object feature_list;
    double aref_new_value;

    x_note_fn_call(170,148);
    if (slot_value) {
	feature_name = Nil;
	feature_value = Nil;
	ab_loop_list_ = CDR(slot_value);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
      next_loop:
	feature_name = CAR(ab_loop_list_);
	temp = CDR(ab_loop_list_);
	feature_value = CAR(temp);
	ab_loopvar__2 = eval_cons_1(feature_name,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	if (FIXNUMP(feature_value))
	    temp = feature_value;
	else if ( !TRUEP(feature_value))
	    temp = Evaluation_false_value;
	else if (EQ(feature_value,T))
	    temp = Evaluation_true_value;
	else if (SYMBOLP(feature_value))
	    temp = feature_value;
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(feature_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(feature_value)) == (SI_Long)1L)
	    temp = copy_managed_float(feature_value);
	else if (FLOATP(feature_value)) {
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
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(feature_value);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    temp = new_float;
	}
	else if (INLINE_LONG_VECTOR_P(feature_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(feature_value)) == (SI_Long)1L)
	    temp = copy_managed_long(feature_value);
	else if (INLINE_LONG_P(feature_value) != (SI_Long)0L)
	    temp = make_evaluation_long(feature_value);
	else if (text_string_p(feature_value))
	    temp = copy_as_wide_string(feature_value);
	else if (CONSP(feature_value) && EQ(M_CDR(feature_value),
		    Qtruth_value)) {
	    gensymed_symbol = M_CAR(feature_value);
	    if (FIXNUM_EQ(gensymed_symbol,Truth))
		temp = Evaluation_true_value;
	    else if (FIXNUM_EQ(gensymed_symbol,Falsity))
		temp = Evaluation_false_value;
	    else
		temp = eval_cons_1(gensymed_symbol,Qtruth_value);
	}
	else
	    temp = error((SI_Long)2L,
		    "Bad type ~a for make-evaluation-value-based-on-type.",
		    type_of(feature_value));
	ab_loopvar__2 = eval_cons_1(temp,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	ab_loop_list_ = CDDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	goto next_loop;
      end_loop:
	feature_list = ab_loopvar_;
	goto end_1;
	feature_list = Qnil;
      end_1:;
	temp = allocate_evaluation_structure(feature_list);
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* WRITE-CELL-FORMAT-FROM-SLOT */
Object write_cell_format_from_slot(cell_part_description,gensymed_symbol)
    Object cell_part_description, gensymed_symbol;
{
    x_note_fn_call(170,149);
    return write_part_description(2,cell_part_description,
	    Cell_format_part_features);
}

/* COMPILE-CELL-FORMAT-FOR-SLOT */
Object compile_cell_format_for_slot varargs_1(int, n)
{
    Object cell_part_description_parse, frame_containing_annotation;
    Object gensymed_symbol;
    volatile Object result_1;
    volatile Object error_message_qm;
    Object current_block_of_dependent_frame, current_annotated_frame;
    Object current_computation_style;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(3);
    Object result;

    x_note_fn_call(170,150);
    INIT_ARGS_nonrelocating();
    cell_part_description_parse = REQUIRED_ARG_nonrelocating();
    frame_containing_annotation = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    result_1 = Nil;
    error_message_qm = Nil;
    LOCK(Working_on_annotated_frame);
    if (PUSH_UNWIND_PROTECT(0)) {
	current_block_of_dependent_frame = 
		ISVREF(frame_containing_annotation,(SI_Long)16L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
		2);
	  current_annotated_frame = Current_block_of_dependent_frame;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_annotated_frame,Qcurrent_annotated_frame,current_annotated_frame,
		  1);
	    current_computation_style = The_only_dynamic_computation_style;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_style,Qcurrent_computation_style,current_computation_style,
		    0);
	      result = compile_part_description(cell_part_description_parse,
		      Qcell);
	      MVS_2(result,result_1,error_message_qm);
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    POP_UNWIND_PROTECT(0);
    UNLOCK(Working_on_annotated_frame);
    CONTINUE_UNWINDING(0);
    result = VALUES_2(result_1,error_message_qm);
    RESTORE_STACK();
    return result;
}

static Object string_constant_25;  /* "none" */

/* WRITE-CELL-FORMAT-OR-NONE-FROM-SLOT */
Object write_cell_format_or_none_from_slot(cell_format_or_none_parse,
	    gensymed_symbol)
    Object cell_format_or_none_parse, gensymed_symbol;
{
    x_note_fn_call(170,151);
    if (EQ(Qnone,cell_format_or_none_parse))
	return tformat(1,string_constant_25);
    else
	return write_part_description(2,cell_format_or_none_parse,
		Cell_format_part_features);
}

/* COMPILE-CELL-FORMAT-OR-NONE-FOR-SLOT */
Object compile_cell_format_or_none_for_slot varargs_1(int, n)
{
    Object cell_format_or_none_parse, frame_containing_annotation;
    Object gensymed_symbol;
    volatile Object result_1;
    volatile Object error_message_qm;
    Object current_annotated_frame, current_block_of_dependent_frame;
    Object current_computation_style;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(3);
    Object result;

    x_note_fn_call(170,152);
    INIT_ARGS_nonrelocating();
    cell_format_or_none_parse = REQUIRED_ARG_nonrelocating();
    frame_containing_annotation = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(Qnone,cell_format_or_none_parse)) {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
    else {
	result_1 = Nil;
	error_message_qm = Nil;
	LOCK(Working_on_annotated_frame);
	if (PUSH_UNWIND_PROTECT(0)) {
	    current_annotated_frame = frame_containing_annotation;
	    current_block_of_dependent_frame = frame_containing_annotation;
	    current_computation_style = The_only_dynamic_computation_style;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_style,Qcurrent_computation_style,current_computation_style,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Current_annotated_frame,Qcurrent_annotated_frame,current_annotated_frame,
			0);
		  result = compile_part_description(cell_format_or_none_parse,
			  Qcell);
		  MVS_2(result,result_1,error_message_qm);
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	POP_UNWIND_PROTECT(0);
	UNLOCK(Working_on_annotated_frame);
	CONTINUE_UNWINDING(0);
	result = VALUES_2(result_1,error_message_qm);
	RESTORE_STACK();
	return result;
    }
}

static Object list_constant_14;    /* # */

static Object list_constant_15;    /* # */

static Object Qsc;                 /* \; */

/* CELL-FORMAT-OR-NONE-EVALUATION-SETTER */
Object cell_format_or_none_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object feature_name, attribute_value, feature_value, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string;
    SI_Long next_index, length_1, gensymed_symbol_1, bv16_length, aref_arg_2;
    SI_Long aref_new_value, length_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(170,153);
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
			  list_constant_14))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_15,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_cell_format_or_none_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_12))
	result = VALUES_1(Nil);
    else if (type_specification_type_p(gensymed_symbol,list_constant_13)) {
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	feature_name = Nil;
	attribute_value = Nil;
	feature_value = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop:
	if (next_index >= length_1)
	    goto end_loop;
	feature_name = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	gensymed_symbol_1 = next_index + (SI_Long)1L;
	attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		gensymed_symbol_1 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		(SI_Long)1023L);
	feature_value = validate_item_or_evaluation_value(attribute_value,
		Nil,Nil);
	next_index = next_index + (SI_Long)2L;
	ab_loopvar__2 = phrase_cons(phrase_list_4(Qset_simple_part_feature,
		Qcurrent_part_description,phrase_list_2(Qquote,
		feature_name),EQ(feature_name,Qbackground_color) ? 
		phrase_list_2(Qquote,feature_value) : 
		phrase_list_2(Qcopy_for_slot_value,phrase_list_2(Qquote,
		feature_value))),Nil);
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
		  tformat(2,string_constant_23,list_constant_12);
		  tformat(2,string_constant_23,list_constant_13);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_24,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_cell_format_or_none_evaluation_setter:
    return result;
}

/* CELL-FORMAT-OR-NONE-EVALUATION-GETTER */
Object cell_format_or_none_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(170,154);
    GENSYM_RETURN_ONE(slot_value ? 
	    allocate_evaluation_structure(copy_list_using_slot_value_conses_1(CDR(slot_value))) 
	    : Nil);
    return VALUES_1(Nil);
}

/* MAKE-CELL-EXPRESSION-AND-TEXT */
Object make_cell_expression_and_text(cell_expression_of_cell_expression_and_text,
	    text_of_cell_expression_and_text)
    Object cell_expression_of_cell_expression_and_text;
    Object text_of_cell_expression_and_text;
{
    x_note_fn_call(170,155);
    return slot_value_cons_1(cell_expression_of_cell_expression_and_text,
	    text_of_cell_expression_and_text);
}

/* REDUCE-TO-BAD-PHRASE */
Object reduce_to_bad_phrase(x)
    Object x;
{
    x_note_fn_call(170,156);
    return VALUES_1(Bad_phrase);
}

/* MAKE-SIMPLE-CELL-EXPRESSION-P */
Object make_simple_cell_expression_p(simple_cell_expression_value,
	    simple_cell_expression_tag)
    Object simple_cell_expression_value, simple_cell_expression_tag;
{
    x_note_fn_call(170,157);
    return VALUES_1(CONS(simple_cell_expression_value,
	    simple_cell_expression_tag));
}

static Object Qsimple_cell_expression;  /* simple-cell-expression */

/* SIMPLE-CELL-EXPRESSION-P */
Object simple_cell_expression_p(x)
    Object x;
{
    x_note_fn_call(170,158);
    if (CONSP(x))
	return VALUES_1(EQ(Qsimple_cell_expression,CDR(x)) ? T : Nil);
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Compiled_cell_expression, Qcompiled_cell_expression);

DEFINE_VARIABLE_WITH_SYMBOL(Current_compiled_cell_expression, Qcurrent_compiled_cell_expression);

/* COMPILED-CELL-EXPRESSION-P */
Object compiled_cell_expression_p(x)
    Object x;
{
    x_note_fn_call(170,159);
    if (CONSP(x))
	return VALUES_1(EQ(Qcompiled_cell_expression,CAR(x)) ? T : Nil);
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Expression_cell_index, Qexpression_cell_index);

/* ENTER-PART-FEATURE-EXPRESSION-CELL-INDEX */
Object enter_part_feature_expression_cell_index(new_value)
    Object new_value;
{
    x_note_fn_call(170,160);
    Part_feature_recall_stack = part_stack_cons_1(Expression_cell_index,
	    Part_feature_recall_stack);
    Expression_cell_index = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-EXPRESSION-CELL-INDEX */
Object exit_part_feature_expression_cell_index()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(170,161);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Expression_cell_index = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Expression_source_text, Qexpression_source_text);

/* ENTER-PART-FEATURE-EXPRESSION-SOURCE-TEXT */
Object enter_part_feature_expression_source_text(new_value)
    Object new_value;
{
    x_note_fn_call(170,162);
    Part_feature_recall_stack = part_stack_cons_1(Expression_source_text,
	    Part_feature_recall_stack);
    Expression_source_text = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-EXPRESSION-SOURCE-TEXT */
Object exit_part_feature_expression_source_text()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(170,163);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Expression_source_text = part_stack_pop_store;
    return VALUES_1(Nil);
}

static Object Qcell_array_element;  /* cell-array-element */

/* FEATURE-TYPE-RECLAIMER-FOR-EXPRESSION-CELL-INDEX */
Object feature_type_reclaimer_for_expression_cell_index(expression_cell_index)
    Object expression_cell_index;
{
    Object current_computation_frame;
    Object current_computation_component_particulars, temp;
    Declare_special(3);
    Object result;

    x_note_fn_call(170,164);
    PUSH_SPECIAL_WITH_SYMBOL(Expression_cell_index,Qexpression_cell_index,expression_cell_index,
	    2);
      current_computation_frame = Current_annotated_frame;
      current_computation_component_particulars = 
	      slot_value_list_2(Qcell_array_element,Expression_cell_index);
      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
	      1);
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		0);
	  temp = 
		  get_lookup_slot_value_given_default(Current_annotated_frame,
		  Qcell_array,Nil);
	  delete_cell_from_g2_cell_array(temp,Expression_cell_index);
	  result = reclaim_slot_value_list_1(Current_computation_component_particulars);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* FEATURE-TYPE-RECLAIMER-FOR-CELL-EXPRESSION-AND-TEXT */
Object feature_type_reclaimer_for_cell_expression_and_text(cell_expression_and_text)
    Object cell_expression_and_text;
{
    Object cell_expression, temp;

    x_note_fn_call(170,165);
    cell_expression = CAR(cell_expression_and_text);
    if (compiled_cell_expression_p(cell_expression)) {
	temp = get_lookup_slot_value_given_default(Current_annotated_frame,
		Qcell_array,Nil);
	deactivate_cell_of_g2_cell_array(temp,
		get_simple_part_feature(cell_expression,
		Qexpression_cell_index));
	reclaim_part_description(cell_expression);
	M_CAR(cell_expression_and_text) = Nil;
    }
    return reclaim_slot_value(cell_expression_and_text);
}

static Object Qexpression_with_computation_style;  /* expression-with-computation-style */

static Object Qsource_position;    /* source-position */

/* COMPILE-A-CELL-EXPRESSION-WITH-OPTIONAL-COMPUTATION-STYLE */
Object compile_a_cell_expression_with_optional_computation_style(expression_parse,
	    desired_evaluation_type)
    Object expression_parse, desired_evaluation_type;
{
    Object text_end_position_qm, computation_style_parse_qm, gensymed_symbol;
    Object result_1, error_message_qm;
    Object result;

    x_note_fn_call(170,166);
    text_end_position_qm = Nil;
    computation_style_parse_qm = Nil;
    if (CONSP(expression_parse) && EQ(Qexpression_with_computation_style,
	    FIRST(expression_parse))) {
	gensymed_symbol = expression_parse;
	gensymed_symbol = CDR(gensymed_symbol);
	expression_parse = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	computation_style_parse_qm = CAR(gensymed_symbol);
    }
    if (! !(CONSP(expression_parse) && EQ(CAR(expression_parse),
	    Qsource_position))) {
	gensymed_symbol = expression_parse;
	gensymed_symbol = CDR(gensymed_symbol);
	expression_parse = CAR(gensymed_symbol);
	text_end_position_qm = CDR(gensymed_symbol);
    }
    result = compile_a_compiled_cell_expression_from_style_and_expression_parse(expression_parse,
	    computation_style_parse_qm,desired_evaluation_type);
    MVS_2(result,result_1,error_message_qm);
    return VALUES_3(result_1,error_message_qm,text_end_position_qm);
}

static Object Qunknown;            /* unknown */

static Object list_constant_16;    /* # */

/* COMPILE-CELL-EXPRESSION-PARSE-FOR-SLOT */
Object compile_cell_expression_parse_for_slot varargs_1(int, n)
{
    Object cell_expression_parse, temporary_frame_for_editor, gensymed_symbol;
    Object x, y, xa, ya, result_1, error_message_qm;
    Object expression_text_end_position_qm, expression_text_string;
    Object possible_scalar, current_block_of_dependent_frame, temp_1;
    char temp;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(170,167);
    INIT_ARGS_nonrelocating();
    cell_expression_parse = REQUIRED_ARG_nonrelocating();
    temporary_frame_for_editor = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    gensymed_symbol = ISVREF(ISVREF(temporary_frame_for_editor,
	    (SI_Long)16L),(SI_Long)3L);
    x = ISVREF(temporary_frame_for_editor,(SI_Long)16L);
    temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else {
	x = gensymed_symbol;
	y = ISVREF(temporary_frame_for_editor,(SI_Long)17L);
	if (FIXNUMP(y))
	    temp = FIXNUMP(x) ? FIXNUM_LT(y,x) : TRUEP(T);
	else if (FIXNUMP(x))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(y);
	    ya = M_CAR(x);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),M_CDR(x)) : 
			TRUEP(Qnil);
	}
    }
    if ( !temp) {
	result_1 = Qunknown;
	error_message_qm = Nil;
	expression_text_end_position_qm = Nil;
	expression_text_string = Nil;
	possible_scalar = CONSP(cell_expression_parse) && 
		EQ(Qsource_position,CAR(cell_expression_parse)) ? 
		SECOND(cell_expression_parse) : cell_expression_parse;
	if (EQ(Qnone,cell_expression_parse))
	    result_1 = Nil;
	else if (text_string_p(possible_scalar) || 
		INTEGERP(possible_scalar) || 
		INLINE_DOUBLE_FLOAT_VECTOR_P(possible_scalar) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(possible_scalar)) == 
		(SI_Long)1L) {
	    result_1 = phrase_cons(possible_scalar,Qsimple_cell_expression);
	    expression_text_string = convert_text_to_text_string(7,
		    ISVREF(Current_edit_state,(SI_Long)15L),Nil,Nil,Nil,
		    Nil,Nil,T);
	}
	else {
	    current_block_of_dependent_frame = 
		    ISVREF(temporary_frame_for_editor,(SI_Long)16L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
		    0);
	      result = compile_a_cell_expression_with_optional_computation_style(cell_expression_parse,
		      list_constant_16);
	      MVS_3(result,result_1,error_message_qm,
		      expression_text_end_position_qm);
	      if ( !EQ(result_1,Bad_phrase)) {
		  expression_text_string = 
			  text_string_from_current_source(Nil,
			  expression_text_end_position_qm);
		  note_use_of_text_string_in_phrase(expression_text_string);
	      }
	    POP_SPECIAL();
	}
	if (EQ(result_1,Bad_phrase))
	    return VALUES_2(Bad_phrase,error_message_qm);
	else {
	    temp_1 = phrase_cons(result_1,expression_text_string);
	    return VALUES_2(temp_1,error_message_qm);
	}
    }
    else
	return VALUES_1(Nil);
}

/* COMPILE-A-COMPILED-CELL-EXPRESSION-FROM-STYLE-AND-EXPRESSION-PARSE */
Object compile_a_compiled_cell_expression_from_style_and_expression_parse(expression_parse,
	    computation_style_parse_qm,desired_evaluation_value_type)
    Object expression_parse, computation_style_parse_qm;
    Object desired_evaluation_value_type;
{
    volatile Object result_1;
    volatile Object error_message_qm;
    Object current_annotated_frame, current_computation_frame, temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(170,168);
    SAVE_STACK();
    result_1 = Nil;
    error_message_qm = Nil;
    LOCK(Working_on_annotated_frame);
    if (PUSH_UNWIND_PROTECT(0)) {
	current_annotated_frame = Current_block_of_dependent_frame;
	current_computation_frame = Current_block_of_dependent_frame;
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_annotated_frame,Qcurrent_annotated_frame,current_annotated_frame,
		  0);
	    if (computation_style_parse_qm)
		result = compile_part_description(computation_style_parse_qm,
			Qcompiled_cell_expression);
	    else
		result = phrase_cons(Qcompiled_cell_expression,Nil);
	    MVS_2(result,result_1,error_message_qm);
	    if ( !EQ(Bad_phrase,result_1)) {
		temp = result_1;
		nconc2(temp,phrase_list_2(Qexpression_cell_index,
			compile_a_compiled_cell_expression_from_expression_parse_and_style_description(expression_parse,
			result_1,desired_evaluation_value_type)));
	    }
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    POP_UNWIND_PROTECT(0);
    UNLOCK(Working_on_annotated_frame);
    CONTINUE_UNWINDING(0);
    result = VALUES_2(result_1,error_message_qm);
    RESTORE_STACK();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Fake_attribute, Qfake_attribute);

static Object Qmark;               /* mark */

static Object Qg2_lambda;          /* g2-lambda */

/* COMPILE-A-COMPILED-CELL-EXPRESSION-FROM-EXPRESSION-PARSE-AND-STYLE-DESCRIPTION */
Object compile_a_compiled_cell_expression_from_expression_parse_and_style_description(expression_parse,
	    computation_style_description_for_embedded_part,
	    desired_evaluation_value_type)
    Object expression_parse, computation_style_description_for_embedded_part;
    Object desired_evaluation_value_type;
{
    Object cell_array, new_cell_index, cell_index_currently_being_registered;
    Object current_computation_component_particulars;
    Object current_computation_style, result_1, current_flag_state_qm;
    Object slot_description, new_cons, temp, svref_arg_2, svref_new_value;
    Object gensymed_symbol, gensymed_symbol_1, stack_of_slot_value_changes;
    Object gensymed_symbol_2, gensymed_symbol_3, old_current_part_description;
    Object old_current_part_description_1, g2_lambda_qm, temp_1, argument_qm;
    Object local_qm, class_qm, domain_qm, attribute_qm;
    Object old_current_part_description_2, part_feature_index;
    Object exit_feature_handler, part_stack_pop_store, cons_1, next_cons;
    Object frame_and_slot_or_atom, ab_loop_list_, ab_loop_it_;
    Object stack_change_pop_store;
    SI_Long svref_new_value_1;
    char temp_2;
    Declare_special(4);
    Object result;

    x_note_fn_call(170,169);
    cell_array = 
	    get_lookup_slot_value_given_default(Current_block_of_dependent_frame,
	    Qcell_array,Nil);
    new_cell_index = make_empty_expression_cell(cell_array);
    cell_index_currently_being_registered = new_cell_index;
    PUSH_SPECIAL_WITH_SYMBOL(Cell_index_currently_being_registered,Qcell_index_currently_being_registered,cell_index_currently_being_registered,
	    3);
      current_computation_component_particulars = 
	      slot_value_list_2(Qcell_array_element,new_cell_index);
      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
	      2);
	current_computation_style = The_only_dynamic_computation_style;
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_style,Qcurrent_computation_style,current_computation_style,
		1);
	  result_1 = Nil;
	  current_flag_state_qm = Nil;
	  slot_description = 
		  get_slot_description_of_class_description_function(Qframe_status_and_notes,
		  ISVREF(Current_computation_frame,(SI_Long)1L),Nil);
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
		      nconc2(stack_change_list_2(Current_computation_frame,
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
	      temp = Current_computation_frame;
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
		    (IFIX(ISVREF(Current_computation_frame,(SI_Long)5L)) & 
		    (SI_Long)16777216L) ? T : Nil;
	    if ( !TRUEP(current_flag_state_qm)) {
		gensymed_symbol = 
			ISVREF(ISVREF(ISVREF(ISVREF(Current_computation_frame,
			(SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
		gensymed_symbol_1 = Current_computation_frame;
		gensymed_symbol_2 = Nil;
		gensymed_symbol_3 = T;
		inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
			gensymed_symbol_2,gensymed_symbol_3);
		temp = Current_computation_frame;
		svref_new_value_1 = IFIX(ISVREF(Current_computation_frame,
			(SI_Long)5L)) | (SI_Long)16777216L;
		ISVREF(temp,(SI_Long)5L) = FIX(svref_new_value_1);
	    }
	    old_current_part_description = Current_part_description;
	    Current_part_description = 
		    get_default_computation_style_of_class();
	    if (Maintain_stack_of_current_part_descriptions_p) {
		new_cons = ISVREF(Available_part_stack_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    temp = Available_part_stack_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(temp,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_part_stack_conses_vector,
			    IFIX(Current_thread_index)))) {
			temp = Available_part_stack_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = Nil;
		    }
		    gensymed_symbol = new_cons;
		}
		else
		    gensymed_symbol = Nil;
		if ( !TRUEP(gensymed_symbol))
		    gensymed_symbol = replenish_part_stack_cons_pool();
		temp = Current_part_description;
		M_CAR(gensymed_symbol) = temp;
		temp = Stack_of_current_part_descriptions;
		M_CDR(gensymed_symbol) = temp;
		inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
		Stack_of_current_part_descriptions = gensymed_symbol;
	    }
	    new_cons = ISVREF(Available_part_stack_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp = Available_part_stack_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_part_stack_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp = Available_part_stack_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = Nil;
		}
		gensymed_symbol = new_cons;
	    }
	    else
		gensymed_symbol = Nil;
	    if ( !TRUEP(gensymed_symbol))
		gensymed_symbol = replenish_part_stack_cons_pool();
	    M_CAR(gensymed_symbol) = Qmark;
	    temp = Part_feature_recall_stack;
	    M_CDR(gensymed_symbol) = temp;
	    inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
	    Part_feature_recall_stack = gensymed_symbol;
	    enter_part_description(Current_part_description);
	    old_current_part_description_1 = Current_part_description;
	    Current_part_description = 
		    get_default_computation_style_of_frame();
	    if (Maintain_stack_of_current_part_descriptions_p) {
		new_cons = ISVREF(Available_part_stack_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    temp = Available_part_stack_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(temp,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_part_stack_conses_vector,
			    IFIX(Current_thread_index)))) {
			temp = Available_part_stack_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = Nil;
		    }
		    gensymed_symbol = new_cons;
		}
		else
		    gensymed_symbol = Nil;
		if ( !TRUEP(gensymed_symbol))
		    gensymed_symbol = replenish_part_stack_cons_pool();
		temp = Current_part_description;
		M_CAR(gensymed_symbol) = temp;
		temp = Stack_of_current_part_descriptions;
		M_CDR(gensymed_symbol) = temp;
		inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
		Stack_of_current_part_descriptions = gensymed_symbol;
	    }
	    new_cons = ISVREF(Available_part_stack_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp = Available_part_stack_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_part_stack_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp = Available_part_stack_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = Nil;
		}
		gensymed_symbol = new_cons;
	    }
	    else
		gensymed_symbol = Nil;
	    if ( !TRUEP(gensymed_symbol))
		gensymed_symbol = replenish_part_stack_cons_pool();
	    M_CAR(gensymed_symbol) = Qmark;
	    temp = Part_feature_recall_stack;
	    M_CDR(gensymed_symbol) = temp;
	    inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
	    Part_feature_recall_stack = gensymed_symbol;
	    enter_part_description(Current_part_description);
	    g2_lambda_qm = CONSP(expression_parse) ? 
		    (EQ(CAR(expression_parse),Qg2_lambda) ? T : Nil) : Qnil;
	    if (g2_lambda_qm) {
		temp_1 = SECOND(expression_parse);
		argument_qm = CAR(temp_1);
	    }
	    else
		argument_qm = Nil;
	    local_qm = g2_lambda_qm ? CAR(argument_qm) : Nil;
	    if (g2_lambda_qm) {
		temp_1 = SECOND(argument_qm);
		class_qm = SECOND(temp_1);
	    }
	    else
		class_qm = Nil;
	    domain_qm = g2_lambda_qm ? phrase_cons(class_qm,local_qm) : Nil;
	    attribute_qm = g2_lambda_qm ? Fake_attribute : Nil;
	    if (g2_lambda_qm) {
		gensymed_symbol = expression_parse;
		gensymed_symbol = CDR(gensymed_symbol);
		gensymed_symbol = CAR(gensymed_symbol);
		gensymed_symbol = CAR(gensymed_symbol);
		local_qm = CAR(gensymed_symbol);
		gensymed_symbol = CDR(gensymed_symbol);
		gensymed_symbol = CAR(gensymed_symbol);
		gensymed_symbol = CDR(gensymed_symbol);
		class_qm = CAR(gensymed_symbol);
		temp_1 = SECOND(expression_parse);
		temp = CAR(temp_1);
		M_CAR(temp) = class_qm;
	    }
	    old_current_part_description_2 = Current_part_description;
	    Current_part_description = 
		    computation_style_description_for_embedded_part;
	    if (Maintain_stack_of_current_part_descriptions_p) {
		new_cons = ISVREF(Available_part_stack_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    temp = Available_part_stack_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(temp,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_part_stack_conses_vector,
			    IFIX(Current_thread_index)))) {
			temp = Available_part_stack_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = Nil;
		    }
		    gensymed_symbol = new_cons;
		}
		else
		    gensymed_symbol = Nil;
		if ( !TRUEP(gensymed_symbol))
		    gensymed_symbol = replenish_part_stack_cons_pool();
		temp = Current_part_description;
		M_CAR(gensymed_symbol) = temp;
		temp = Stack_of_current_part_descriptions;
		M_CDR(gensymed_symbol) = temp;
		inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
		Stack_of_current_part_descriptions = gensymed_symbol;
	    }
	    new_cons = ISVREF(Available_part_stack_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp = Available_part_stack_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_part_stack_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp = Available_part_stack_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = Nil;
		}
		gensymed_symbol = new_cons;
	    }
	    else
		gensymed_symbol = Nil;
	    if ( !TRUEP(gensymed_symbol))
		gensymed_symbol = replenish_part_stack_cons_pool();
	    M_CAR(gensymed_symbol) = Qmark;
	    temp = Part_feature_recall_stack;
	    M_CDR(gensymed_symbol) = temp;
	    inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
	    Part_feature_recall_stack = gensymed_symbol;
	    enter_part_description(Current_part_description);
	    register_expression_cell_during_compilation(7,cell_array,
		    new_cell_index,Nil,expression_parse,
		    desired_evaluation_value_type,domain_qm,attribute_qm);
	    part_feature_index = Nil;
	    exit_feature_handler = Nil;
	  next_loop:
	    part_stack_pop_store = Nil;
	    cons_1 = Part_feature_recall_stack;
	    if (cons_1) {
		part_stack_pop_store = M_CAR(cons_1);
		next_cons = M_CDR(cons_1);
		inline_note_reclaim_cons(cons_1,Qpart_stack);
		if (ISVREF(Available_part_stack_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp = ISVREF(Available_part_stack_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp) = cons_1;
		    temp = Available_part_stack_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		}
		else {
		    temp = Available_part_stack_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		    temp = Available_part_stack_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		}
		M_CDR(cons_1) = Nil;
	    }
	    else
		next_cons = Nil;
	    Part_feature_recall_stack = next_cons;
	    part_feature_index = part_stack_pop_store;
	    if (EQ(part_feature_index,Qmark))
		goto end_loop;
	    exit_feature_handler = ISVREF(Part_feature_exit_methods,
		    IFIX(part_feature_index));
	    inline_funcall_0(exit_feature_handler);
	    goto next_loop;
	  end_loop:;
	    Current_part_description = old_current_part_description_2;
	    if (Maintain_stack_of_current_part_descriptions_p) {
		part_stack_pop_store = Nil;
		cons_1 = Stack_of_current_part_descriptions;
		if (cons_1) {
		    part_stack_pop_store = M_CAR(cons_1);
		    next_cons = M_CDR(cons_1);
		    inline_note_reclaim_cons(cons_1,Qpart_stack);
		    if (ISVREF(Available_part_stack_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp = 
				ISVREF(Available_part_stack_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp) = cons_1;
			temp = Available_part_stack_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = cons_1;
		    }
		    else {
			temp = Available_part_stack_conses_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = cons_1;
			temp = Available_part_stack_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = cons_1;
		    }
		    M_CDR(cons_1) = Nil;
		}
		else
		    next_cons = Nil;
		Stack_of_current_part_descriptions = next_cons;
	    }
	    if (g2_lambda_qm) {
		temp_1 = SECOND(expression_parse);
		temp = CAR(temp_1);
		temp_1 = M_CAR(temp) = class_qm;
	    }
	    else
		temp_1 = Nil;
	    part_feature_index = Nil;
	    exit_feature_handler = Nil;
	  next_loop_1:
	    part_stack_pop_store = Nil;
	    cons_1 = Part_feature_recall_stack;
	    if (cons_1) {
		part_stack_pop_store = M_CAR(cons_1);
		next_cons = M_CDR(cons_1);
		inline_note_reclaim_cons(cons_1,Qpart_stack);
		if (ISVREF(Available_part_stack_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp = ISVREF(Available_part_stack_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp) = cons_1;
		    temp = Available_part_stack_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		}
		else {
		    temp = Available_part_stack_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		    temp = Available_part_stack_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		}
		M_CDR(cons_1) = Nil;
	    }
	    else
		next_cons = Nil;
	    Part_feature_recall_stack = next_cons;
	    part_feature_index = part_stack_pop_store;
	    if (EQ(part_feature_index,Qmark))
		goto end_loop_1;
	    exit_feature_handler = ISVREF(Part_feature_exit_methods,
		    IFIX(part_feature_index));
	    inline_funcall_0(exit_feature_handler);
	    goto next_loop_1;
	  end_loop_1:;
	    Current_part_description = old_current_part_description_1;
	    if (Maintain_stack_of_current_part_descriptions_p) {
		part_stack_pop_store = Nil;
		cons_1 = Stack_of_current_part_descriptions;
		if (cons_1) {
		    part_stack_pop_store = M_CAR(cons_1);
		    next_cons = M_CDR(cons_1);
		    inline_note_reclaim_cons(cons_1,Qpart_stack);
		    if (ISVREF(Available_part_stack_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp = 
				ISVREF(Available_part_stack_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp) = cons_1;
			temp = Available_part_stack_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = cons_1;
		    }
		    else {
			temp = Available_part_stack_conses_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = cons_1;
			temp = Available_part_stack_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = cons_1;
		    }
		    M_CDR(cons_1) = Nil;
		}
		else
		    next_cons = Nil;
		Stack_of_current_part_descriptions = next_cons;
	    }
	    part_feature_index = Nil;
	    exit_feature_handler = Nil;
	  next_loop_2:
	    part_stack_pop_store = Nil;
	    cons_1 = Part_feature_recall_stack;
	    if (cons_1) {
		part_stack_pop_store = M_CAR(cons_1);
		next_cons = M_CDR(cons_1);
		inline_note_reclaim_cons(cons_1,Qpart_stack);
		if (ISVREF(Available_part_stack_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp = ISVREF(Available_part_stack_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp) = cons_1;
		    temp = Available_part_stack_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		}
		else {
		    temp = Available_part_stack_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		    temp = Available_part_stack_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		}
		M_CDR(cons_1) = Nil;
	    }
	    else
		next_cons = Nil;
	    Part_feature_recall_stack = next_cons;
	    part_feature_index = part_stack_pop_store;
	    if (EQ(part_feature_index,Qmark))
		goto end_loop_2;
	    exit_feature_handler = ISVREF(Part_feature_exit_methods,
		    IFIX(part_feature_index));
	    inline_funcall_0(exit_feature_handler);
	    goto next_loop_2;
	  end_loop_2:;
	    Current_part_description = old_current_part_description;
	    if (Maintain_stack_of_current_part_descriptions_p) {
		part_stack_pop_store = Nil;
		cons_1 = Stack_of_current_part_descriptions;
		if (cons_1) {
		    part_stack_pop_store = M_CAR(cons_1);
		    next_cons = M_CDR(cons_1);
		    inline_note_reclaim_cons(cons_1,Qpart_stack);
		    if (ISVREF(Available_part_stack_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp = 
				ISVREF(Available_part_stack_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp) = cons_1;
			temp = Available_part_stack_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = cons_1;
		    }
		    else {
			temp = Available_part_stack_conses_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = cons_1;
			temp = Available_part_stack_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = cons_1;
		    }
		    M_CDR(cons_1) = Nil;
		}
		else
		    next_cons = Nil;
		Stack_of_current_part_descriptions = next_cons;
	    }
	    result_1 = temp_1;
	    if ( !TRUEP(current_flag_state_qm)) {
		temp = Current_computation_frame;
		svref_new_value_1 = IFIX(ISVREF(Current_computation_frame,
			(SI_Long)5L)) &  ~(SI_Long)16777216L;
		ISVREF(temp,(SI_Long)5L) = FIX(svref_new_value_1);
		gensymed_symbol = 
			ISVREF(ISVREF(ISVREF(ISVREF(Current_computation_frame,
			(SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
		gensymed_symbol_1 = Current_computation_frame;
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
	      next_loop_3:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_3;
		frame_and_slot_or_atom = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if (ATOM(frame_and_slot_or_atom))
		    goto end_loop_3;
		temp_2 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
		if (temp_2);
		else {
		    temp_1 = M_CDR(frame_and_slot_or_atom);
		    temp_2 = CONSP(temp_1) ? EQ(slot_description,
			    SECOND(frame_and_slot_or_atom)) && EQ(Nil,
			    THIRD(frame_and_slot_or_atom)) && EQ(Nil,
			    CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
		}
		ab_loop_it_ = temp_2 ? (EQ(Current_computation_frame,
			M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
		if (ab_loop_it_) {
		    temp_2 = TRUEP(ab_loop_it_);
		    goto end_1;
		}
		goto next_loop_3;
	      end_loop_3:
		temp_2 = TRUEP(Qnil);
	      end_1:;
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if ( !temp_2)
		update_all_representations_of_slot(Current_computation_frame,
			slot_description,Nil,Nil);
	    if (ISVREF(slot_description,(SI_Long)14L))
		update_frame_name_references(Current_computation_frame);
	    stack_change_pop_store = Nil;
	    cons_1 = Stack_of_slot_value_changes;
	    if (cons_1) {
		stack_change_pop_store = M_CAR(cons_1);
		next_cons = M_CDR(cons_1);
		inline_note_reclaim_cons(cons_1,Qstack_change);
		if (ISVREF(Available_stack_change_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp = 
			    ISVREF(Available_stack_change_conses_tail_vector,
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
		temp_1 = M_CAR(Stack_of_slot_value_changes);
		temp_2 = ATOM(temp_1);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2 ?  
		    !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) :
		     TRUEP(Nil))
		do_deferred_updates_to_representations_in_tables();
	  POP_SPECIAL();
	  reclaim_slot_value_list_1(Current_computation_component_particulars);
	  result = VALUES_1(new_cell_index);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object list_constant_17;    /* # */

static Object list_constant_18;    /* # */

static Object Qinter_g2_data_request_holder;  /* inter-g2-data-request-holder */

static Object list_constant_19;    /* # */

static Object list_constant_20;    /* # */

static Object list_constant_21;    /* # */

static Object list_constant_22;    /* # */

/* GET-DEFAULT-COMPUTATION-STYLE-OF-CLASS */
Object get_default_computation_style_of_class()
{
    Object gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(170,170);
    gensymed_symbol = ISVREF(Current_computation_frame,(SI_Long)1L);
    gensymed_symbol_1 = 
	    lookup_global_or_kb_specific_property_value(Qnew_table,
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
	    temp = (SI_Long)0L < gensymed_symbol_2;
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp);
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Chart_class_description,
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
	    temp = (SI_Long)0L < gensymed_symbol_2;
	}
	else
	    temp = TRUEP(Nil);
    }
    if (temp)
	return VALUES_1(list_constant_17);
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Variable_class_description,
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
	    temp = (SI_Long)0L < gensymed_symbol_2;
	}
	else
	    temp = TRUEP(Nil);
	if (temp);
	else {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Generic_formula_class_description,
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
		temp = (SI_Long)0L < gensymed_symbol_2;
	    }
	    else
		temp = TRUEP(Nil);
	}
	if (temp)
	    return VALUES_1(list_constant_18);
	else {
	    gensymed_symbol_1 = 
		    lookup_global_or_kb_specific_property_value(Qinter_g2_data_request_holder,
		    Class_description_gkbprop);
	    if (gensymed_symbol_1) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_1,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_2 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_3 = (SI_Long)1L;
		    gensymed_symbol_4 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
		    gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
		    temp = (SI_Long)0L < gensymed_symbol_2;
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		return VALUES_1(list_constant_19);
	    else {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Readout_table_class_description,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_2 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_3 = (SI_Long)1L;
		    gensymed_symbol_4 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
		    gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
		    temp = (SI_Long)0L < gensymed_symbol_2;
		}
		else
		    temp = TRUEP(Nil);
		if (temp);
		else {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Dial_class_description,(SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_2 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_3 = (SI_Long)1L;
			gensymed_symbol_4 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_3 = gensymed_symbol_3 << 
				gensymed_symbol_4;
			gensymed_symbol_2 = gensymed_symbol_2 & 
				gensymed_symbol_3;
			temp = (SI_Long)0L < gensymed_symbol_2;
		    }
		    else
			temp = TRUEP(Nil);
		}
		if (temp);
		else {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Meter_class_description,(SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_2 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_3 = (SI_Long)1L;
			gensymed_symbol_4 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_3 = gensymed_symbol_3 << 
				gensymed_symbol_4;
			gensymed_symbol_2 = gensymed_symbol_2 & 
				gensymed_symbol_3;
			temp = (SI_Long)0L < gensymed_symbol_2;
		    }
		    else
			temp = TRUEP(Nil);
		}
		if (temp)
		    return VALUES_1(list_constant_20);
		else {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(User_menu_choice_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_2 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_3 = (SI_Long)1L;
			gensymed_symbol_4 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_3 = gensymed_symbol_3 << 
				gensymed_symbol_4;
			gensymed_symbol_2 = gensymed_symbol_2 & 
				gensymed_symbol_3;
			temp = (SI_Long)0L < gensymed_symbol_2;
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp)
			return VALUES_1(list_constant_21);
		    else {
			sub_class_bit_vector = ISVREF(gensymed_symbol,
				(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Block_class_description,
				(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol_2 = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_3 = (SI_Long)1L;
			    gensymed_symbol_4 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_3 = gensymed_symbol_3 << 
				    gensymed_symbol_4;
			    gensymed_symbol_2 = gensymed_symbol_2 & 
				    gensymed_symbol_3;
			    temp = (SI_Long)0L < gensymed_symbol_2;
			}
			else
			    temp = TRUEP(Nil);
			if (temp)
			    return VALUES_1(list_constant_22);
			else
			    return VALUES_1(Qnil);
		    }
		}
	    }
	}
    }
}

static Object Qdefault_evaluation_setting;  /* default-evaluation-setting */

static Object list_constant_23;    /* # */

/* GET-DEFAULT-COMPUTATION-STYLE-OF-FRAME */
Object get_default_computation_style_of_frame()
{
    Object gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(170,171);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(ISVREF(ISVREF(Current_computation_frame,
	    (SI_Long)1L),(SI_Long)1L),Class_description_gkbprop);
    gensymed_symbol_1 = 
	    lookup_global_or_kb_specific_property_value(Qnew_table,
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
	    temp = (SI_Long)0L < gensymed_symbol_2;
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    temp_1 = temp ? get_slot_value_function(Current_computation_frame,
	    Qdefault_evaluation_setting,Nil) : Nil;
    if (temp_1)
	return VALUES_1(temp_1);
    else
	return VALUES_1(list_constant_23);
}

/* WRITE-CELL-EXPRESSION-PARSE-FROM-SLOT */
Object write_cell_expression_parse_from_slot(cell_expression_and_text,
	    gensymed_symbol)
    Object cell_expression_and_text, gensymed_symbol;
{
    Object cell_expression, expression_text_string;

    x_note_fn_call(170,172);
    gensymed_symbol = cell_expression_and_text;
    cell_expression = CAR(gensymed_symbol);
    expression_text_string = CDR(gensymed_symbol);
    tformat(2,string_constant_2,expression_text_string);
    if (compiled_cell_expression_p(cell_expression))
	return twrite_computation_style(cell_expression,T);
    else
	return VALUES_1(Nil);
}

/* CONSTANT-COMPUTED-PART-FEATURE-P */
Object constant_computed_part_feature_p(computed_part_feature)
    Object computed_part_feature;
{
    x_note_fn_call(170,173);
    return VALUES_1(ATOM(computed_part_feature) ? T : Nil);
}

/* EVALUATED-COMPUTED-PART-FEATURE-P */
Object evaluated_computed_part_feature_p(computed_part_feature)
    Object computed_part_feature;
{
    x_note_fn_call(170,174);
    return VALUES_1(CONSP(computed_part_feature) ? T : Nil);
}

static Object Qobsolete_datum;     /* obsolete-datum */

/* VALUE-OF-COMPUTED-PART-FEATURE */
Object value_of_computed_part_feature(computed_part_feature,default_value)
    Object computed_part_feature, default_value;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, expression_cell, result_1;

    x_note_fn_call(170,175);
    if (constant_computed_part_feature_p(computed_part_feature))
	return VALUES_1(computed_part_feature);
    else {
	gensymed_symbol = 
		ISVREF(get_lookup_slot_value_given_default(Current_block_of_dependent_frame,
		Qcell_array,Nil),(SI_Long)3L);
	gensymed_symbol_1 = get_simple_part_feature(computed_part_feature,
		Qexpression_cell_index);
	if (FIXNUM_LE(ISVREF(ISVREF(get_lookup_slot_value_given_default(Current_block_of_dependent_frame,
		Qcell_array,Nil),(SI_Long)3L),(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = 
		    ISVREF(get_lookup_slot_value_given_default(Current_block_of_dependent_frame,
		    Qcell_array,Nil),(SI_Long)3L);
	    expression_cell = ISVREF(temp,
		    IFIX(FIXNUM_ADD(gensymed_symbol_1,
		    Managed_array_index_offset)));
	}
	else
	    expression_cell = ISVREF(ISVREF(gensymed_symbol,
		    (IFIX(gensymed_symbol_1) >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L),IFIX(gensymed_symbol_1) & (SI_Long)1023L);
	result_1 = ISVREF(expression_cell,(SI_Long)6L);
	if (CONSP(result_1) && EQ(M_CDR(result_1),Qobsolete_datum) ||  
		!TRUEP(result_1))
	    return VALUES_1(default_value);
	else
	    return VALUES_1(result_1);
    }
}

/* COMPILE-COMPUTED-PART-FEATURE */
Object compile_computed_part_feature(parse_of_computed_part_feature)
    Object parse_of_computed_part_feature;
{
    Object result_1, error_message_qm, source_position_2_qm, gensymed_symbol;
    Object gensymed_symbol_1, desired_evaluation_type, source_position_1;
    Object expression, temp;
    Object result;

    x_note_fn_call(170,176);
    result_1 = Nil;
    error_message_qm = Nil;
    source_position_2_qm = Nil;
    gensymed_symbol = parse_of_computed_part_feature;
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol_1 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol_1 = CDR(gensymed_symbol_1);
    desired_evaluation_type = CAR(gensymed_symbol_1);
    source_position_1 = CDR(gensymed_symbol_1);
    expression = CAR(gensymed_symbol);
    result = compile_a_cell_expression_with_optional_computation_style(expression,
	    desired_evaluation_type);
    MVS_3(result,result_1,error_message_qm,source_position_2_qm);
    if ( !TRUEP(error_message_qm)) {
	temp = result_1;
	nconc2(temp,phrase_list_2(Qexpression_source_text,
		text_string_from_current_source(source_position_1,
		source_position_2_qm)));
	return copy_for_slot_value(result_1);
    }
    else
	return VALUES_2(Bad_phrase,error_message_qm);
}

static Object string_constant_26;  /* "symbolic" */

static Object string_constant_27;  /* "given by the ~A expression~A" */

/* WRITE-COMPUTED-PART-FEATURE */
Object write_computed_part_feature(desired_evaluation_type,
	    embedded_simple_type,computed_part_feature)
    Object desired_evaluation_type, embedded_simple_type;
    Object computed_part_feature;
{
    Object temp;

    x_note_fn_call(170,177);
    if (constant_computed_part_feature_p(computed_part_feature))
	return write_instance_of_simple_type_1(embedded_simple_type,
		computed_part_feature);
    else {
	temp = EQ(desired_evaluation_type,Qsymbol) ? string_constant_26 : Nil;
	tformat(3,string_constant_27,temp,
		get_simple_part_feature(computed_part_feature,
		Qexpression_source_text));
	return twrite_computation_style(computed_part_feature,T);
    }
}

void parts_INIT()
{
    Object named_dynamic_extent_description, gensymed_symbol, the_array, temp;
    Object temp_1, computation_style_or_none_evaluation_setter_1;
    Object computation_style_or_none_evaluation_getter_1;
    Object cell_format_or_none_evaluation_setter_1;
    Object cell_format_or_none_evaluation_getter_1;
    SI_Long i, ab_loop_bind_;
    Object Qslot_value_writer, Qwrite_cell_expression_parse_from_slot;
    Object Qcell_expression_parse, AB_package, list_constant_156;
    Object list_constant_153, Qmay_request_event_updates, Qinference_engine;
    Object Qvalue_domain, Qupdate_only_when_shown, Qinitial_scan_wait_interval;
    Object list_constant_154, list_constant_155, list_constant_152;
    Object Qmay_request_data_seeking, list_constant_28;
    Object Qmay_provide_event_updates, Qmay_provide_data_on_request;
    Object Qtime_out_when_requesting_data_seeking;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler, Qcompile_cell_expression_parse_for_slot;
    Object list_constant_151, list_constant_150, Qdatum, Qab_or;
    Object Qunknown_datum;
    Object Qfeature_type_reclaimer_for_cell_expression_and_text;
    Object Qfeature_type_reclaimer_for_expression_cell_index;
    Object list_constant_149, Qexit_part_feature_expression_source_text;
    Object Qenter_part_feature_expression_source_text, Qtext_string;
    Object Qspecial_variable, Qsymbol_standing_in_for_unbound;
    Object list_constant_148, Qexit_part_feature_expression_cell_index;
    Object Qenter_part_feature_expression_cell_index, list_constant_40;
    Object Qexit_subpart_exceptions, Qenter_subpart_exceptions;
    Object list_constant_33, list_constant_37, Qexit_subpart_defaults;
    Object Qenter_subpart_defaults, list_constant_34;
    Object Qexit_part_feature_subparts, Qenter_part_feature_subparts;
    Object list_constant_147, list_constant_143, list_constant_146;
    Object list_constant_29, list_constant_145, list_constant_144, Qincludes;
    Object Qnamed_dynamic_extent_description, Qparts, list_constant_53;
    Object string_constant_68, Qreduce_to_bad_phrase, string_constant_67;
    Object string_constant_66, Qreduce_noting_source_position;
    Object Qcell_format_or_none, Qnamed, list_constant_142, list_constant_141;
    Object list_constant_140, Qab_structure, Qheight, Qwidth, Qtext_alignment;
    Object Qtext_color, Qborder_color, Qline_color, list_constant_139;
    Object list_constant_138, list_constant_137, list_constant_136;
    Object list_constant_135, list_constant_134, list_constant_133;
    Object list_constant_132, list_constant_131, list_constant_130, Qfont_name;
    Object list_constant_44, list_constant_129, list_constant_128;
    Object list_constant_108, Qtype_specification_simple_expansion;
    Object Qcompile_cell_format_or_none_for_slot;
    Object Qwrite_cell_format_or_none_from_slot, string_constant_65;
    Object Qcompile_cell_format_for_slot, Qwrite_cell_format_from_slot;
    Object string_constant_64, Qcell_format_annotation, string_constant_63;
    Object string_constant_62, string_constant_61, string_constant_60;
    Object Qreduce_annotation_with_expression, Qreduce_annotation;
    Object Qcomputation_style_or_none, list_constant_127, list_constant_126;
    Object list_constant_125, Qbreak_message_level, Qtrace_message_level;
    Object list_constant_124, list_constant_123, list_constant_122;
    Object list_constant_121, list_constant_120, list_constant_119;
    Object list_constant_118, list_constant_117, list_constant_116;
    Object list_constant_115, list_constant_114, list_constant_113;
    Object list_constant_112, list_constant_110, list_constant_111;
    Object list_constant_48, list_constant_47, list_constant_109;
    Object list_constant_50, Qno_item;
    Object Qcompile_computation_style_or_none_for_slot;
    Object Qwrite_computation_style_or_none_from_slot, list_constant_83;
    Object string_constant_59, Qtrace_message_level_for_computation_style;
    Object Qwarning_message_level_for_computation_style;
    Object Qbreak_message_level_for_computation_style, string_constant_58;
    Object Qreduce_common_computation_phrase_scan_interval, string_constant_57;
    Object string_constant_56, string_constant_55, string_constant_54;
    Object string_constant_53, string_constant_52, string_constant_51;
    Object string_constant_50, Qsimplify_associative_operation;
    Object string_constant_49, list_constant_107;
    Object Qexit_part_feature_network_access_attempt;
    Object Qenter_part_feature_network_access_attempt, Qnetwork_access_attempt;
    Object Qnetwork_access_kind, Qclass_slot, list_constant_106;
    Object Qexit_part_feature_update_after_edits;
    Object Qenter_part_feature_update_after_edits, Qupdate_after_edits;
    Object Qboolean, Qexit_part_feature_may_provide_event_updates;
    Object Qenter_part_feature_may_provide_event_updates, list_constant_105;
    Object Qexit_part_feature_may_provide_data_on_request;
    Object Qenter_part_feature_may_provide_data_on_request, list_constant_104;
    Object Qexit_part_feature_time_out_when_requesting_data_seeking;
    Object Qenter_part_feature_time_out_when_requesting_data_seeking;
    Object Qsimple_interval, list_constant_103;
    Object Qexit_part_feature_may_request_data_seeking;
    Object Qenter_part_feature_may_request_data_seeking, list_constant_102;
    Object Qexit_part_feature_may_request_event_updates;
    Object Qenter_part_feature_may_request_event_updates, list_constant_101;
    Object Qexit_tracing_or_breakpoints_setting, Qenter_break_level;
    Object Qbreak_level, list_constant_98, list_constant_100, Qcall_handlers;
    Object list_constant_99, Qenter_warning_level, Qwarning_level;
    Object list_constant_97, list_constant_95, list_constant_96;
    Object Qenter_tracing_level, Qtrace_level, list_constant_94;
    Object list_constant_93, Qexit_part_feature_update_only_when_shown;
    Object Qenter_part_feature_update_only_when_shown, list_constant_92;
    Object Qexit_part_feature_value_domain, Qenter_part_feature_value_domain;
    Object Qvalue_domain_kind, list_constant_91;
    Object Qexit_part_feature_initial_scan_wait_interval;
    Object Qenter_part_feature_initial_scan_wait_interval, list_constant_90;
    Object Qexit_part_feature_scan_interval, Qenter_part_feature_scan_interval;
    Object list_constant_89, Qexit_part_feature_priority;
    Object Qenter_part_feature_priority, Qpriority_level, list_constant_88;
    Object list_constant_87, Qevaluation_attributes, string_constant_48;
    Object Qslot_putter, Qput_reference_to_data_in_frame_containing_annotation;
    Object list_constant_86, Qgeneric_method_lambda_list, list_constant_85;
    Object Qupdate_part_dependencies, Qwhat_changed, Qkind_of_change;
    Object Qslot_value_reclaimer;
    Object Qreclaim_frame_serial_number_of_frame_being_edited_value;
    Object Qframe_serial_number_of_frame_being_edited;
    Object Qreclaim_reference_to_data_in_frame_containing_annotation_value;
    Object Qreclaim_editable_slot_for_cell_expression_and_text_value;
    Object Qreclaim_annotation_containing_feature_value;
    Object Qannotation_containing_feature, Qreclaim_frame_being_edited_value;
    Object Qframe_being_edited, string_constant_47, list_constant_84;
    Object string_constant_46, string_constant_45, string_constant_44;
    Object string_constant_43, Qget_subpart_of_collection;
    Object Qget_simple_part_feature, Qpart_description_of_frame;
    Object Qfeature_type_reclaimer_for_compute_part_feature_of_type_color_or_metacolor;
    Object Qfeature_type_reclaimer_for_subparts_collection;
    Object Qsubparts_collection, string_constant_42, list_constant_82, Qright;
    Object list_constant_81, list_constant_80, list_constant_79;
    Object list_constant_78, Qextra_large, Qlarge, Qregular, list_constant_77;
    Object Qexit_text_size, Qenter_text_size, list_constant_76;
    Object list_constant_75, list_constant_74, list_constant_73;
    Object list_constant_72, list_constant_71, list_constant_70, Qhm24;
    Object list_constant_69, Qhm18, list_constant_68, Qhm14, list_constant_67;
    Object Qexit_part_feature_height, Qenter_part_feature_height;
    Object Qworkspace_measure, list_constant_66, Qexit_formatted_part_width;
    Object Qenter_formatted_part_width, list_constant_65, list_constant_64;
    Object list_constant_63, Qexit_part_feature_text_alignment;
    Object Qenter_part_feature_text_alignment, Qtext_alignment_kind;
    Object list_constant_62, Qexit_part_feature_highlighted_qm;
    Object Qenter_part_feature_highlighted_qm, list_constant_61;
    Object Qexit_part_feature_text_color, Qenter_part_feature_text_color;
    Object list_constant_60, Qexit_part_feature_border_color;
    Object Qenter_part_feature_border_color, list_constant_59;
    Object Qexit_part_feature_line_color, Qenter_part_feature_line_color;
    Object list_constant_58, Qexit_background_color, Qenter_background_color;
    Object list_constant_57, list_constant_56, list_constant_55;
    Object list_constant_54, Qformatting_attributes, string_constant_41;
    Object Qformat_description, string_constant_40, Qnew_table_cell_format;
    Object string_constant_39, Qdynamic_text_cell_format;
    Object Qsimple_type_specification, list_constant_52, list_constant_51;
    Object Qtext_string_p, Qsimple_type_writer, Qboolean_type_writer;
    Object Qslot_value_float_type_writer, Qslot_value_float;
    Object Qtype_error_printer, string_constant_38, list_constant_49;
    Object Qsimple_interval_p, Qg2_simulator, list_constant_46;
    Object list_constant_45, Qworkspace_measure_p, Qcenter, Qleft;
    Object Qcompute_part_feature_of_type_color_or_metacolor_type_writer;
    Object Qcompute_part_feature_of_type_color_or_metacolor_p;
    Object list_constant_43, list_constant_42, Qcolor_or_metacolor_p;
    Object list_constant_41, Qexit_part_feature_part_index;
    Object Qenter_part_feature_part_index, list_constant_39, list_constant_38;
    Object list_constant_36, list_constant_35, list_constant_32;
    Object list_constant_31, list_constant_30, string_constant_37, Qfalse;
    Object Qtrue, list_constant_27, string_constant_36, string_constant_35;
    Object string_constant_34, string_constant_33, string_constant_32;
    Object string_constant_31, list_constant_26, string_constant_30;
    Object string_constant_29, string_constant_28;
    Object Qpart_stack_cons_memory_usage, Qoutstanding_part_stack_conses;
    Object list_constant_25, Qpart_stack_cons_counter_vector;
    Object Qmake_thread_array, Kfuncall, list_constant_24;
    Object Qavailable_part_stack_conses_tail_vector;
    Object Qavailable_part_stack_conses_vector;

    x_note_fn_call(170,178);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qsubparts_collection = STATIC_SYMBOL("SUBPARTS-COLLECTION",AB_package);
    Qsimple_type_specification = STATIC_SYMBOL("SIMPLE-TYPE-SPECIFICATION",
	    AB_package);
    mutate_global_property(Qsubparts_collection,Qt,Qsimple_type_specification);
    Qavailable_part_stack_conses = 
	    STATIC_SYMBOL("AVAILABLE-PART-STACK-CONSES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_part_stack_conses,
	    Available_part_stack_conses);
    Qparts = STATIC_SYMBOL("PARTS",AB_package);
    record_system_variable(Qavailable_part_stack_conses,Qparts,Nil,Qnil,Qt,
	    Qnil,Qnil);
    Qavailable_part_stack_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-PART-STACK-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_part_stack_conses_tail,
	    Available_part_stack_conses_tail);
    record_system_variable(Qavailable_part_stack_conses_tail,Qparts,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_part_stack_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-PART-STACK-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_part_stack_conses_vector,
	    Available_part_stack_conses_vector);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_thread_array = STATIC_SYMBOL("MAKE-THREAD-ARRAY",AB_package);
    list_constant_24 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    Qnil);
    record_system_variable(Qavailable_part_stack_conses_vector,Qparts,
	    list_constant_24,Qnil,Qt,Qnil,Qnil);
    Qavailable_part_stack_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-PART-STACK-CONSES-TAIL-VECTOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_part_stack_conses_tail_vector,
	    Available_part_stack_conses_tail_vector);
    record_system_variable(Qavailable_part_stack_conses_tail_vector,Qparts,
	    list_constant_24,Qnil,Qt,Qnil,Qnil);
    Qpart_stack_cons_counter_vector = 
	    STATIC_SYMBOL("PART-STACK-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpart_stack_cons_counter_vector,
	    Part_stack_cons_counter_vector);
    list_constant_25 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    FIX((SI_Long)0L));
    record_system_variable(Qpart_stack_cons_counter_vector,Qparts,
	    list_constant_25,Qnil,Qt,Qnil,Qnil);
    Qpart_stack_cons_counter = STATIC_SYMBOL("PART-STACK-CONS-COUNTER",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpart_stack_cons_counter,
	    Part_stack_cons_counter);
    record_system_variable(Qpart_stack_cons_counter,Qparts,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_part_stack_conses = 
	    STATIC_SYMBOL("OUTSTANDING-PART-STACK-CONSES",AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_part_stack_conses,
	    STATIC_FUNCTION(outstanding_part_stack_conses,NIL,FALSE,0,0));
    Qpart_stack_cons_memory_usage = 
	    STATIC_SYMBOL("PART-STACK-CONS-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qpart_stack_cons_memory_usage,
	    STATIC_FUNCTION(part_stack_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_28 = STATIC_STRING("1q83-iQy9k83-iPy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_part_stack_conses);
    push_optimized_constant(Qpart_stack_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_28));
    Qpart_stack = STATIC_SYMBOL("PART-STACK",AB_package);
    string_constant_29 = STATIC_STRING("WORKING-ON-ANNOTATED-FRAME");
    if (Working_on_annotated_frame == UNBOUND)
	Working_on_annotated_frame = make_recursive_lock(2,Kname,
		string_constant_29);
    Qworking_on_annotated_frame = 
	    STATIC_SYMBOL("WORKING-ON-ANNOTATED-FRAME",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qworking_on_annotated_frame,
	    Working_on_annotated_frame);
    Qnamed_dynamic_extent_description = 
	    STATIC_SYMBOL("NAMED-DYNAMIC-EXTENT-DESCRIPTION",AB_package);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qworking_on_annotated_frame,
	    Qparts,Nil,Qnil,Qnil,Qnil,Nil);
    mutate_global_property(Qworking_on_annotated_frame,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    string_constant_30 = STATIC_STRING("SCANNING-SUBPARTS-OF-BLOCK");
    if (Scanning_subparts_of_block == UNBOUND)
	Scanning_subparts_of_block = make_recursive_lock(2,Kname,
		string_constant_30);
    Qscanning_subparts_of_block = 
	    STATIC_SYMBOL("SCANNING-SUBPARTS-OF-BLOCK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qscanning_subparts_of_block,
	    Scanning_subparts_of_block);
    list_constant_26 = STATIC_CONS(Qworking_on_annotated_frame,Qnil);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qscanning_subparts_of_block,
	    Qparts,Nil,list_constant_26,Qnil,Qnil,Nil);
    mutate_global_property(Qscanning_subparts_of_block,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    Qpart_feature_recall_stack = STATIC_SYMBOL("PART-FEATURE-RECALL-STACK",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpart_feature_recall_stack,
	    Part_feature_recall_stack);
    record_system_variable(Qpart_feature_recall_stack,Qparts,Nil,Qnil,Qt,
	    Qnil,Qnil);
    Qstack_of_current_part_descriptions = 
	    STATIC_SYMBOL("STACK-OF-CURRENT-PART-DESCRIPTIONS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qstack_of_current_part_descriptions,
	    Stack_of_current_part_descriptions);
    record_system_variable(Qstack_of_current_part_descriptions,Qparts,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qmaintain_stack_of_current_part_descriptions_p = 
	    STATIC_SYMBOL("MAINTAIN-STACK-OF-CURRENT-PART-DESCRIPTIONS-P",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmaintain_stack_of_current_part_descriptions_p,
	    Maintain_stack_of_current_part_descriptions_p);
    record_system_variable(Qmaintain_stack_of_current_part_descriptions_p,
	    Qparts,Nil,Qnil,Qnil,Qnil,Qnil);
    string_constant_31 = STATIC_STRING("PROJECTION");
    if (Projection == UNBOUND)
	Projection = make_recursive_lock(2,Kname,string_constant_31);
    Qprojection = STATIC_SYMBOL("PROJECTION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qprojection,Projection);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qprojection,Qparts,Nil,
	    Qnil,Qnil,Qnil,Nil);
    mutate_global_property(Qprojection,named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    if (Projection_focus_method == UNBOUND)
	Projection_focus_method = Nil;
    string_constant_32 = STATIC_STRING("PROJECTION-DRAWING");
    if (Projection_drawing == UNBOUND)
	Projection_drawing = make_recursive_lock(2,Kname,string_constant_32);
    Qprojection_drawing = STATIC_SYMBOL("PROJECTION-DRAWING",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qprojection_drawing,Projection_drawing);
    list_constant_27 = STATIC_CONS(Qprojection,Qnil);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qprojection_drawing,
	    Qparts,Nil,Qnil,Qnil,list_constant_27,Nil);
    mutate_global_property(Qprojection_drawing,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    string_constant_33 = STATIC_STRING("PROJECTION-FUNCALL-ON-FOCUS");
    if (Projection_funcall_on_focus == UNBOUND)
	Projection_funcall_on_focus = make_recursive_lock(2,Kname,
		string_constant_33);
    Qprojection_funcall_on_focus = 
	    STATIC_SYMBOL("PROJECTION-FUNCALL-ON-FOCUS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qprojection_funcall_on_focus,
	    Projection_funcall_on_focus);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qprojection_funcall_on_focus,
	    Qparts,Nil,Qnil,Qnil,list_constant_27,Nil);
    mutate_global_property(Qprojection_funcall_on_focus,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    string_constant_34 = STATIC_STRING("PROJECTION-TRACKING");
    if (Projection_tracking == UNBOUND)
	Projection_tracking = make_recursive_lock(2,Kname,string_constant_34);
    Qprojection_tracking = STATIC_SYMBOL("PROJECTION-TRACKING",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qprojection_tracking,Projection_tracking);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qprojection_tracking,
	    Qparts,Nil,Qnil,Qnil,list_constant_27,Nil);
    mutate_global_property(Qprojection_tracking,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    string_constant_35 = STATIC_STRING("PROJECTION-UPDATE-DEPENDENCIES");
    if (Projection_update_dependencies == UNBOUND)
	Projection_update_dependencies = make_recursive_lock(2,Kname,
		string_constant_35);
    Qprojection_update_dependencies = 
	    STATIC_SYMBOL("PROJECTION-UPDATE-DEPENDENCIES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qprojection_update_dependencies,
	    Projection_update_dependencies);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qprojection_update_dependencies,
	    Qparts,Nil,Qnil,Qnil,list_constant_27,Nil);
    mutate_global_property(Qprojection_update_dependencies,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    string_constant_36 = STATIC_STRING("PROJECTION-COMPUTING-PATH-OF-FOCUS");
    if (Projection_computing_path_of_focus == UNBOUND)
	Projection_computing_path_of_focus = make_recursive_lock(2,Kname,
		string_constant_36);
    Qprojection_computing_path_of_focus = 
	    STATIC_SYMBOL("PROJECTION-COMPUTING-PATH-OF-FOCUS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qprojection_computing_path_of_focus,
	    Projection_computing_path_of_focus);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qprojection_computing_path_of_focus,
	    Qparts,Nil,Qnil,Qnil,list_constant_27,Nil);
    mutate_global_property(Qprojection_computing_path_of_focus,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    Qparts_of_annotated_frames_currently_erased = 
	    STATIC_SYMBOL("PARTS-OF-ANNOTATED-FRAMES-CURRENTLY-ERASED",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qparts_of_annotated_frames_currently_erased,
	    Parts_of_annotated_frames_currently_erased);
    record_system_variable(Qparts_of_annotated_frames_currently_erased,
	    Qparts,Nil,Qnil,Qnil,Qnil,Qt);
    Qannotation = STATIC_SYMBOL("ANNOTATION",AB_package);
    if (Currently_supressing_part_highlighting == UNBOUND)
	Currently_supressing_part_highlighting = Nil;
    Qhighlighted_qm = STATIC_SYMBOL("HIGHLIGHTED\?",AB_package);
    Quser_spellings_of_internal_symbol = 
	    STATIC_SYMBOL("USER-SPELLINGS-OF-INTERNAL-SYMBOL",AB_package);
    User_spellings_of_internal_symbol_prop = 
	    Quser_spellings_of_internal_symbol;
    Qinternal_spellings_of_user_symbol = 
	    STATIC_SYMBOL("INTERNAL-SPELLINGS-OF-USER-SYMBOL",AB_package);
    Internal_spellings_of_user_symbol_prop = 
	    Qinternal_spellings_of_user_symbol;
    Qconstant = STATIC_SYMBOL("CONSTANT",AB_package);
    Qtrue = STATIC_SYMBOL("TRUE",AB_package);
    def_user_spelling(Qt,Qconstant,Qtrue);
    Qfalse = STATIC_SYMBOL("FALSE",AB_package);
    def_user_spelling(Qnil,Qconstant,Qfalse);
    Qget_internal_spelling = STATIC_SYMBOL("GET-INTERNAL-SPELLING",AB_package);
    SET_SYMBOL_FUNCTION(Qget_internal_spelling,
	    STATIC_FUNCTION(get_internal_spelling,NIL,FALSE,2,2));
    Qpart_feature = STATIC_SYMBOL("PART-FEATURE",AB_package);
    Qset_simple_part_feature = STATIC_SYMBOL("SET-SIMPLE-PART-FEATURE",
	    AB_package);
    Qcopy_for_slot_value = STATIC_SYMBOL("COPY-FOR-SLOT-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qcopy_for_slot_value,
	    STATIC_FUNCTION(copy_for_slot_value,NIL,FALSE,1,1));
    Qcompile_computed_part_feature = 
	    STATIC_SYMBOL("COMPILE-COMPUTED-PART-FEATURE",AB_package);
    Maximum_number_of_part_features = FIX((SI_Long)91L);
    if (Part_feature_indexes == UNBOUND) {
	gensymed_symbol = Maximum_number_of_part_features;
	the_array = make_array(1,gensymed_symbol);
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(gensymed_symbol);
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	Part_feature_indexes = the_array;
    }
    Qpart_feature_index = STATIC_SYMBOL("PART-FEATURE-INDEX",AB_package);
    Part_feature_index_prop = Qpart_feature_index;
    if (Last_part_features_index_allocated == UNBOUND)
	Last_part_features_index_allocated = FIX((SI_Long)-1L);
    Qpart_type_description = STATIC_SYMBOL("PART-TYPE-DESCRIPTION",AB_package);
    Part_type_description_prop = Qpart_type_description;
    Quser_spelling = STATIC_SYMBOL("USER-SPELLING",AB_package);
    Qhidden_features = STATIC_SYMBOL("HIDDEN-FEATURES",AB_package);
    Qallow_individual_exceptions_in_parents = 
	    STATIC_SYMBOL("ALLOW-INDIVIDUAL-EXCEPTIONS-IN-PARENTS",AB_package);
    Qallow_defaulting_in_parents = 
	    STATIC_SYMBOL("ALLOW-DEFAULTING-IN-PARENTS",AB_package);
    Qpart_type = STATIC_SYMBOL("PART-TYPE",AB_package);
    if (Part_feature_enter_methods == UNBOUND)
	Part_feature_enter_methods = make_array(1,
		Maximum_number_of_part_features);
    if (Part_feature_exit_methods == UNBOUND)
	Part_feature_exit_methods = make_array(1,
		Maximum_number_of_part_features);
    Qsubpart_defaults = STATIC_SYMBOL("SUBPART-DEFAULTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsubpart_defaults,Subpart_defaults);
    Qsymbol_standing_in_for_unbound = 
	    STATIC_SYMBOL("SYMBOL-STANDING-IN-FOR-UNBOUND",AB_package);
    if (Subpart_defaults == UNBOUND)
	Subpart_defaults = Qsymbol_standing_in_for_unbound;
    string_constant_37 = STATIC_STRING("BASIC-PART");
    if (Basic_part == UNBOUND)
	Basic_part = make_recursive_lock(2,Kname,string_constant_37);
    Qbasic_part = STATIC_SYMBOL("BASIC-PART",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbasic_part,Basic_part);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qbasic_part,Qparts,Nil,
	    Qnil,Qnil,Qnil,Nil);
    mutate_global_property(Qbasic_part,named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    Qsubparts = STATIC_SYMBOL("SUBPARTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsubparts,Subparts);
    if (Subparts == UNBOUND)
	Subparts = Qsymbol_standing_in_for_unbound;
    if (Subpart_exceptions == UNBOUND)
	Subpart_exceptions = Qsymbol_standing_in_for_unbound;
    if (Current_part_description == UNBOUND)
	Current_part_description = Nil;
    if (Current_basic_part == UNBOUND)
	Current_basic_part = Qsymbol_standing_in_for_unbound;
    list_constant_28 = STATIC_CONS(Qnil,Qnil);
    list_constant_29 = STATIC_CONS(Quser_spelling,list_constant_28);
    list_constant_30 = STATIC_CONS(list_constant_29,Qnil);
    def_part_type_1(Qbasic_part,Qnil,list_constant_30);
    list_constant_33 = STATIC_CONS(Qsubparts_collection,Qnil);
    Qenter_part_feature_subparts = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-SUBPARTS",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_subparts,
	    STATIC_FUNCTION(enter_part_feature_subparts,NIL,FALSE,1,1));
    Qexit_part_feature_subparts = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-SUBPARTS",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_subparts,
	    STATIC_FUNCTION(exit_part_feature_subparts,NIL,FALSE,0,0));
    Qcall_handlers = STATIC_SYMBOL("CALL-HANDLERS",AB_package);
    list_constant_31 = STATIC_LIST((SI_Long)2L,Qfunction,
	    Qenter_part_feature_subparts);
    list_constant_32 = STATIC_LIST((SI_Long)2L,Qfunction,
	    Qexit_part_feature_subparts);
    list_constant_34 = STATIC_LIST((SI_Long)3L,Qcall_handlers,
	    list_constant_31,list_constant_32);
    def_part_feature_1(Qbasic_part,Qsubparts,list_constant_33,Qsubparts,
	    Qnil,SYMBOL_FUNCTION(Qenter_part_feature_subparts),
	    SYMBOL_FUNCTION(Qexit_part_feature_subparts),list_constant_34);
    Qenter_subpart_defaults = STATIC_SYMBOL("ENTER-SUBPART-DEFAULTS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_subpart_defaults,
	    STATIC_FUNCTION(enter_subpart_defaults,NIL,FALSE,1,1));
    Qexit_subpart_defaults = STATIC_SYMBOL("EXIT-SUBPART-DEFAULTS",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_subpart_defaults,
	    STATIC_FUNCTION(exit_subpart_defaults,NIL,FALSE,0,0));
    list_constant_35 = STATIC_LIST((SI_Long)2L,Qfunction,
	    Qenter_subpart_defaults);
    list_constant_36 = STATIC_LIST((SI_Long)2L,Qfunction,
	    Qexit_subpart_defaults);
    list_constant_37 = STATIC_LIST((SI_Long)3L,Qcall_handlers,
	    list_constant_35,list_constant_36);
    def_part_feature_1(Qbasic_part,Qsubpart_defaults,list_constant_33,
	    Qsubpart_defaults,Qnil,
	    SYMBOL_FUNCTION(Qenter_subpart_defaults),
	    SYMBOL_FUNCTION(Qexit_subpart_defaults),list_constant_37);
    Qsubpart_exceptions = STATIC_SYMBOL("SUBPART-EXCEPTIONS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsubpart_exceptions,Subpart_exceptions);
    Qenter_subpart_exceptions = STATIC_SYMBOL("ENTER-SUBPART-EXCEPTIONS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_subpart_exceptions,
	    STATIC_FUNCTION(enter_subpart_exceptions,NIL,FALSE,1,1));
    Qexit_subpart_exceptions = STATIC_SYMBOL("EXIT-SUBPART-EXCEPTIONS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_subpart_exceptions,
	    STATIC_FUNCTION(exit_subpart_exceptions,NIL,FALSE,0,0));
    list_constant_38 = STATIC_LIST((SI_Long)2L,Qfunction,
	    Qenter_subpart_exceptions);
    list_constant_39 = STATIC_LIST((SI_Long)2L,Qfunction,
	    Qexit_subpart_exceptions);
    list_constant_40 = STATIC_LIST((SI_Long)3L,Qcall_handlers,
	    list_constant_38,list_constant_39);
    def_part_feature_1(Qbasic_part,Qsubpart_exceptions,list_constant_33,
	    Qsubpart_exceptions,Qnil,
	    SYMBOL_FUNCTION(Qenter_subpart_exceptions),
	    SYMBOL_FUNCTION(Qexit_subpart_exceptions),list_constant_40);
    def_part_feature_1(Qbasic_part,Qsubpart_defaults,Qsubparts_collection,
	    Qsubpart_defaults,Qt,SYMBOL_FUNCTION(Qenter_subpart_defaults),
	    SYMBOL_FUNCTION(Qexit_subpart_defaults),list_constant_37);
    def_part_feature_1(Qbasic_part,Qsubpart_exceptions,
	    Qsubparts_collection,Qsubpart_exceptions,Qt,
	    SYMBOL_FUNCTION(Qenter_subpart_exceptions),
	    SYMBOL_FUNCTION(Qexit_subpart_exceptions),list_constant_40);
    if (Part_index == UNBOUND)
	Part_index = Qsymbol_standing_in_for_unbound;
    Qpart_index = STATIC_SYMBOL("PART-INDEX",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpart_index,Part_index);
    Qenter_part_feature_part_index = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-PART-INDEX",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_part_index,
	    STATIC_FUNCTION(enter_part_feature_part_index,NIL,FALSE,1,1));
    Qexit_part_feature_part_index = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-PART-INDEX",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_part_index,
	    STATIC_FUNCTION(exit_part_feature_part_index,NIL,FALSE,0,0));
    Qspecial_variable = STATIC_SYMBOL("SPECIAL-VARIABLE",AB_package);
    list_constant_41 = STATIC_LIST((SI_Long)2L,Qspecial_variable,Qpart_index);
    def_part_feature_1(Qbasic_part,Qpart_index,Qfixnum,Qpart_index,Qt,
	    SYMBOL_FUNCTION(Qenter_part_feature_part_index),
	    SYMBOL_FUNCTION(Qexit_part_feature_part_index),list_constant_41);
    Qcolor_or_metacolor = STATIC_SYMBOL("COLOR-OR-METACOLOR",AB_package);
    Qcolor_or_metacolor_p = STATIC_SYMBOL("COLOR-OR-METACOLOR-P",AB_package);
    list_constant_42 = STATIC_LIST((SI_Long)2L,Qsatisfies,
	    Qcolor_or_metacolor_p);
    mutate_global_property(Qcolor_or_metacolor,list_constant_42,
	    Qsimple_type_specification);
    Qcompute_part_feature_of_type_color_or_metacolor = 
	    STATIC_SYMBOL("COMPUTE-PART-FEATURE-OF-TYPE-COLOR-OR-METACOLOR",
	    AB_package);
    Qcompute_part_feature_of_type_color_or_metacolor_p = 
	    STATIC_SYMBOL("COMPUTE-PART-FEATURE-OF-TYPE-COLOR-OR-METACOLOR-P",
	    AB_package);
    list_constant_43 = STATIC_LIST((SI_Long)2L,Qsatisfies,
	    Qcompute_part_feature_of_type_color_or_metacolor_p);
    mutate_global_property(Qcompute_part_feature_of_type_color_or_metacolor,
	    list_constant_43,Qsimple_type_specification);
    SET_SYMBOL_FUNCTION(Qcompute_part_feature_of_type_color_or_metacolor_p,
	    STATIC_FUNCTION(compute_part_feature_of_type_color_or_metacolor_p,
	    NIL,FALSE,1,1));
    Qcompute_part_feature_of_type_color_or_metacolor_type_writer = 
	    STATIC_SYMBOL("COMPUTE-PART-FEATURE-OF-TYPE-COLOR-OR-METACOLOR-TYPE-WRITER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompute_part_feature_of_type_color_or_metacolor_type_writer,
	    STATIC_FUNCTION(compute_part_feature_of_type_color_or_metacolor_type_writer,
	    NIL,FALSE,1,1));
    Qsimple_type_writer = STATIC_SYMBOL("SIMPLE-TYPE-WRITER",AB_package);
    mutate_global_property(Qcompute_part_feature_of_type_color_or_metacolor,
	    Qcompute_part_feature_of_type_color_or_metacolor_type_writer,
	    Qsimple_type_writer);
    Qtext_alignment_kind = STATIC_SYMBOL("TEXT-ALIGNMENT-KIND",AB_package);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qcenter = STATIC_SYMBOL("CENTER",AB_package);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    list_constant_44 = STATIC_LIST((SI_Long)4L,Qmember,Qleft,Qcenter,Qright);
    mutate_global_property(Qtext_alignment_kind,list_constant_44,
	    Qsimple_type_specification);
    Qworkspace_measure = STATIC_SYMBOL("WORKSPACE-MEASURE",AB_package);
    Qworkspace_measure_p = STATIC_SYMBOL("WORKSPACE-MEASURE-P",AB_package);
    SET_SYMBOL_FUNCTION(Qworkspace_measure_p,
	    STATIC_FUNCTION(workspace_measure_p,NIL,FALSE,1,1));
    list_constant_45 = STATIC_LIST((SI_Long)2L,Qsatisfies,
	    Qworkspace_measure_p);
    mutate_global_property(Qworkspace_measure,list_constant_45,
	    Qsimple_type_specification);
    Qtext_size = STATIC_SYMBOL("TEXT-SIZE",AB_package);
    Qsmall = STATIC_SYMBOL("SMALL",AB_package);
    Qlarge = STATIC_SYMBOL("LARGE",AB_package);
    Qextra_large = STATIC_SYMBOL("EXTRA-LARGE",AB_package);
    list_constant_46 = STATIC_LIST((SI_Long)4L,Qmember,Qsmall,Qlarge,
	    Qextra_large);
    mutate_global_property(Qtext_size,list_constant_46,
	    Qsimple_type_specification);
    Qvalue_domain_kind = STATIC_SYMBOL("VALUE-DOMAIN-KIND",AB_package);
    Qinference_engine = STATIC_SYMBOL("INFERENCE-ENGINE",AB_package);
    Qg2_simulator = STATIC_SYMBOL("G2-SIMULATOR",AB_package);
    list_constant_47 = STATIC_LIST((SI_Long)3L,Qmember,Qinference_engine,
	    Qg2_simulator);
    mutate_global_property(Qvalue_domain_kind,list_constant_47,
	    Qsimple_type_specification);
    Qtrace_level = STATIC_SYMBOL("TRACE-LEVEL",AB_package);
    list_constant_48 = STATIC_LIST((SI_Long)5L,Qmember,FIX((SI_Long)0L),
	    FIX((SI_Long)1L),FIX((SI_Long)2L),FIX((SI_Long)3L));
    mutate_global_property(Qtrace_level,list_constant_48,
	    Qsimple_type_specification);
    Qbreak_level = STATIC_SYMBOL("BREAK-LEVEL",AB_package);
    mutate_global_property(Qbreak_level,list_constant_48,
	    Qsimple_type_specification);
    Qwarning_level = STATIC_SYMBOL("WARNING-LEVEL",AB_package);
    mutate_global_property(Qwarning_level,list_constant_48,
	    Qsimple_type_specification);
    Qsimple_interval = STATIC_SYMBOL("SIMPLE-INTERVAL",AB_package);
    Qsimple_interval_p = STATIC_SYMBOL("SIMPLE-INTERVAL-P",AB_package);
    SET_SYMBOL_FUNCTION(Qsimple_interval_p,
	    STATIC_FUNCTION(simple_interval_p,NIL,FALSE,1,1));
    list_constant_49 = STATIC_LIST((SI_Long)2L,Qsatisfies,Qsimple_interval_p);
    mutate_global_property(Qsimple_interval,list_constant_49,
	    Qsimple_type_specification);
    Qpriority_level = STATIC_SYMBOL("PRIORITY-LEVEL",AB_package);
    list_constant_50 = STATIC_LIST((SI_Long)11L,Qmember,FIX((SI_Long)1L),
	    FIX((SI_Long)2L),FIX((SI_Long)3L),FIX((SI_Long)4L),
	    FIX((SI_Long)5L),FIX((SI_Long)6L),FIX((SI_Long)7L),
	    FIX((SI_Long)8L),FIX((SI_Long)9L),FIX((SI_Long)10L));
    mutate_global_property(Qpriority_level,list_constant_50,
	    Qsimple_type_specification);
    string_constant_38 = STATIC_STRING("not an integer from 1 through 10");
    Qtype_error_printer = STATIC_SYMBOL("TYPE-ERROR-PRINTER",AB_package);
    mutate_global_property(Qpriority_level,string_constant_38,
	    Qtype_error_printer);
    Qcell_expression_and_text = STATIC_SYMBOL("CELL-EXPRESSION-AND-TEXT",
	    AB_package);
    mutate_global_property(Qcell_expression_and_text,Qcons,
	    Qsimple_type_specification);
    Qexpression_cell_index = STATIC_SYMBOL("EXPRESSION-CELL-INDEX",AB_package);
    mutate_global_property(Qexpression_cell_index,Qfixnum,
	    Qsimple_type_specification);
    string_constant = STATIC_STRING("~(~D~)");
    string_constant_1 = STATIC_STRING("~(~A~)");
    Qslot_value_float = STATIC_SYMBOL("SLOT-VALUE-FLOAT",AB_package);
    Qslot_value_float_type_writer = 
	    STATIC_SYMBOL("SLOT-VALUE-FLOAT-TYPE-WRITER",AB_package);
    SET_SYMBOL_FUNCTION(Qslot_value_float_type_writer,
	    STATIC_FUNCTION(slot_value_float_type_writer,NIL,FALSE,1,1));
    mutate_global_property(Qslot_value_float,Qslot_value_float_type_writer,
	    Qsimple_type_writer);
    string_constant_2 = STATIC_STRING("~A");
    string_constant_3 = STATIC_STRING("true");
    string_constant_4 = STATIC_STRING("false");
    Qboolean = STATIC_SYMBOL("BOOLEAN",AB_package);
    Qboolean_type_writer = STATIC_SYMBOL("BOOLEAN-TYPE-WRITER",AB_package);
    SET_SYMBOL_FUNCTION(Qboolean_type_writer,
	    STATIC_FUNCTION(boolean_type_writer,NIL,FALSE,1,1));
    mutate_global_property(Qboolean,Qboolean_type_writer,Qsimple_type_writer);
    Qtext_string = STATIC_SYMBOL("TEXT-STRING",AB_package);
    Qtext_string_p = STATIC_SYMBOL("TEXT-STRING-P",AB_package);
    SET_SYMBOL_FUNCTION(Qtext_string_p,STATIC_FUNCTION(text_string_p,NIL,
	    FALSE,1,1));
    list_constant_51 = STATIC_LIST((SI_Long)2L,Qsatisfies,Qtext_string_p);
    mutate_global_property(Qtext_string,list_constant_51,
	    Qsimple_type_specification);
    Qnetwork_access_kind = STATIC_SYMBOL("NETWORK-ACCESS-KIND",AB_package);
    list_constant_52 = STATIC_LIST((SI_Long)4L,Qmember,Qnil,Qread,Qwrite);
    mutate_global_property(Qnetwork_access_kind,list_constant_52,
	    Qsimple_type_specification);
    Qdynamic_text_cell_format = STATIC_SYMBOL("DYNAMIC-TEXT-CELL-FORMAT",
	    AB_package);
    string_constant_39 = 
	    STATIC_STRING("13Py83-Qy83-By083wy83-by83bys83ayo83Wys83cyo83kyk83-=ys83ny1l83-ry83tyz83syy83uyn83-7y3C+y83iy30ey");
    Qformat_description = STATIC_SYMBOL("FORMAT-DESCRIPTION",AB_package);
    mutate_global_property(Qdynamic_text_cell_format,
	    regenerate_optimized_constant(string_constant_39),
	    Qformat_description);
    Qnew_table_cell_format = STATIC_SYMBOL("NEW-TABLE-CELL-FORMAT",AB_package);
    string_constant_40 = 
	    STATIC_STRING("13Py83-Qy83-By083wy83-by83bys83ayo83Wys83cyo83kyk83-=ys83ny1l83-ry83ty3Ey83syy83uyn83-7y3C+y83iy30ey");
    mutate_global_property(Qnew_table_cell_format,
	    regenerate_optimized_constant(string_constant_40),
	    Qformat_description);
    string_constant_41 = STATIC_STRING("FORMATTED-PART");
    if (Formatted_part == UNBOUND)
	Formatted_part = make_recursive_lock(2,Kname,string_constant_41);
    Qformatted_part = STATIC_SYMBOL("FORMATTED-PART",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qformatted_part,Formatted_part);
    list_constant_53 = STATIC_CONS(Qbasic_part,Qnil);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qformatted_part,Qparts,
	    Nil,Qnil,Qnil,list_constant_53,Nil);
    mutate_global_property(Qformatted_part,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    if (Current_formatted_part == UNBOUND)
	Current_formatted_part = Qsymbol_standing_in_for_unbound;
    Qformatting_attributes = STATIC_SYMBOL("FORMATTING-ATTRIBUTES",AB_package);
    list_constant_54 = STATIC_LIST((SI_Long)2L,Quser_spelling,
	    Qformatting_attributes);
    list_constant_55 = STATIC_CONS(list_constant_54,Qnil);
    def_part_type_1(Qformatted_part,list_constant_53,list_constant_55);
    def_part_feature_1(Qformatted_part,Qsubparts,list_constant_33,
	    Qsubparts,Qnil,SYMBOL_FUNCTION(Qenter_part_feature_subparts),
	    SYMBOL_FUNCTION(Qexit_part_feature_subparts),list_constant_34);
    def_part_feature_1(Qformatted_part,Qsubpart_defaults,list_constant_33,
	    Qsubpart_defaults,Qnil,
	    SYMBOL_FUNCTION(Qenter_subpart_defaults),
	    SYMBOL_FUNCTION(Qexit_subpart_defaults),list_constant_37);
    def_part_feature_1(Qformatted_part,Qsubpart_exceptions,
	    list_constant_33,Qsubpart_exceptions,Qnil,
	    SYMBOL_FUNCTION(Qenter_subpart_exceptions),
	    SYMBOL_FUNCTION(Qexit_subpart_exceptions),list_constant_40);
    Qbackground = STATIC_SYMBOL("BACKGROUND",AB_package);
    Qtext_cell_background_color_qm = 
	    STATIC_SYMBOL("TEXT-CELL-BACKGROUND-COLOR\?",AB_package);
    Qforeground = STATIC_SYMBOL("FOREGROUND",AB_package);
    Qtransparent = STATIC_SYMBOL("TRANSPARENT",AB_package);
    Qcolor_value_vector_index_and_intensity = 
	    STATIC_SYMBOL("COLOR-VALUE-VECTOR-INDEX-AND-INTENSITY",AB_package);
    Qbackground_color = STATIC_SYMBOL("BACKGROUND-COLOR",AB_package);
    Qenter_background_color = STATIC_SYMBOL("ENTER-BACKGROUND-COLOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_background_color,
	    STATIC_FUNCTION(enter_background_color,NIL,FALSE,1,1));
    Qexit_background_color = STATIC_SYMBOL("EXIT-BACKGROUND-COLOR",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_background_color,
	    STATIC_FUNCTION(exit_background_color,NIL,FALSE,0,0));
    list_constant_56 = STATIC_LIST((SI_Long)2L,Qfunction,
	    Qenter_background_color);
    list_constant_57 = STATIC_LIST((SI_Long)2L,Qfunction,
	    Qexit_background_color);
    list_constant_58 = STATIC_LIST((SI_Long)3L,Qcall_handlers,
	    list_constant_56,list_constant_57);
    def_part_feature_1(Qformatted_part,Qbackground_color,
	    Qcompute_part_feature_of_type_color_or_metacolor,
	    Qbackground_color,Qt,SYMBOL_FUNCTION(Qenter_background_color),
	    SYMBOL_FUNCTION(Qexit_background_color),list_constant_58);
    if (Formatted_part_true_line_color == UNBOUND)
	Formatted_part_true_line_color = Qsymbol_standing_in_for_unbound;
    Qline_color = STATIC_SYMBOL("LINE-COLOR",AB_package);
    Qenter_part_feature_line_color = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-LINE-COLOR",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_line_color,
	    STATIC_FUNCTION(enter_part_feature_line_color,NIL,FALSE,1,1));
    Qexit_part_feature_line_color = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-LINE-COLOR",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_line_color,
	    STATIC_FUNCTION(exit_part_feature_line_color,NIL,FALSE,0,0));
    Qformatted_part_true_line_color = 
	    STATIC_SYMBOL("FORMATTED-PART-TRUE-LINE-COLOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qformatted_part_true_line_color,
	    Formatted_part_true_line_color);
    list_constant_59 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qformatted_part_true_line_color);
    def_part_feature_1(Qformatted_part,Qline_color,Qcolor_or_metacolor,
	    Qline_color,Qt,SYMBOL_FUNCTION(Qenter_part_feature_line_color),
	    SYMBOL_FUNCTION(Qexit_part_feature_line_color),list_constant_59);
    Qtext_box_border_color_qm = STATIC_SYMBOL("TEXT-BOX-BORDER-COLOR\?",
	    AB_package);
    Qborder_color = STATIC_SYMBOL("BORDER-COLOR",AB_package);
    Qenter_part_feature_border_color = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-BORDER-COLOR",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_border_color,
	    STATIC_FUNCTION(enter_part_feature_border_color,NIL,FALSE,1,1));
    Qexit_part_feature_border_color = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-BORDER-COLOR",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_border_color,
	    STATIC_FUNCTION(exit_part_feature_border_color,NIL,FALSE,0,0));
    Qclass_slot = STATIC_SYMBOL("CLASS-SLOT",AB_package);
    Qcurrent_text_box_format = STATIC_SYMBOL("CURRENT-TEXT-BOX-FORMAT",
	    AB_package);
    list_constant_60 = STATIC_LIST((SI_Long)3L,Qclass_slot,
	    Qcurrent_text_box_format,Qtext_box_border_color_qm);
    def_part_feature_1(Qformatted_part,Qborder_color,Qcolor_or_metacolor,
	    Qborder_color,Qt,
	    SYMBOL_FUNCTION(Qenter_part_feature_border_color),
	    SYMBOL_FUNCTION(Qexit_part_feature_border_color),list_constant_60);
    Qtext_cell_line_color_qm = STATIC_SYMBOL("TEXT-CELL-LINE-COLOR\?",
	    AB_package);
    Qtext_color = STATIC_SYMBOL("TEXT-COLOR",AB_package);
    Qenter_part_feature_text_color = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-TEXT-COLOR",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_text_color,
	    STATIC_FUNCTION(enter_part_feature_text_color,NIL,FALSE,1,1));
    Qexit_part_feature_text_color = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-TEXT-COLOR",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_text_color,
	    STATIC_FUNCTION(exit_part_feature_text_color,NIL,FALSE,0,0));
    list_constant_61 = STATIC_LIST((SI_Long)3L,Qclass_slot,
	    Qcurrent_text_box_format,Qtext_cell_line_color_qm);
    def_part_feature_1(Qformatted_part,Qtext_color,Qcolor_or_metacolor,
	    Qtext_color,Qt,SYMBOL_FUNCTION(Qenter_part_feature_text_color),
	    SYMBOL_FUNCTION(Qexit_part_feature_text_color),list_constant_61);
    if (Formatted_part_highlight_flag == UNBOUND)
	Formatted_part_highlight_flag = Qsymbol_standing_in_for_unbound;
    Qenter_part_feature_highlighted_qm = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-HIGHLIGHTED\?",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_highlighted_qm,
	    STATIC_FUNCTION(enter_part_feature_highlighted_qm,NIL,FALSE,1,1));
    Qexit_part_feature_highlighted_qm = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-HIGHLIGHTED\?",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_highlighted_qm,
	    STATIC_FUNCTION(exit_part_feature_highlighted_qm,NIL,FALSE,0,0));
    Qformatted_part_highlight_flag = 
	    STATIC_SYMBOL("FORMATTED-PART-HIGHLIGHT-FLAG",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qformatted_part_highlight_flag,
	    Formatted_part_highlight_flag);
    list_constant_62 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qformatted_part_highlight_flag);
    def_part_feature_1(Qformatted_part,Qhighlighted_qm,Qboolean,
	    Qhighlighted_qm,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_highlighted_qm),
	    SYMBOL_FUNCTION(Qexit_part_feature_highlighted_qm),
	    list_constant_62);
    Qtext_cell_line_quadding_qm = 
	    STATIC_SYMBOL("TEXT-CELL-LINE-QUADDING\?",AB_package);
    Qtext_alignment = STATIC_SYMBOL("TEXT-ALIGNMENT",AB_package);
    Qenter_part_feature_text_alignment = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-TEXT-ALIGNMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_text_alignment,
	    STATIC_FUNCTION(enter_part_feature_text_alignment,NIL,FALSE,1,1));
    Qexit_part_feature_text_alignment = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-TEXT-ALIGNMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_text_alignment,
	    STATIC_FUNCTION(exit_part_feature_text_alignment,NIL,FALSE,0,0));
    list_constant_63 = STATIC_LIST((SI_Long)3L,Qclass_slot,
	    Qcurrent_text_box_format,Qtext_cell_line_quadding_qm);
    def_part_feature_1(Qformatted_part,Qtext_alignment,
	    Qtext_alignment_kind,Qtext_alignment,Qt,
	    SYMBOL_FUNCTION(Qenter_part_feature_text_alignment),
	    SYMBOL_FUNCTION(Qexit_part_feature_text_alignment),
	    list_constant_63);
    if (Current_width_of_formatted_part == UNBOUND)
	Current_width_of_formatted_part = Qsymbol_standing_in_for_unbound;
    Qminimum_format_width_for_text_cell = 
	    STATIC_SYMBOL("MINIMUM-FORMAT-WIDTH-FOR-TEXT-CELL",AB_package);
    Qmaximum_format_width_for_text_cell = 
	    STATIC_SYMBOL("MAXIMUM-FORMAT-WIDTH-FOR-TEXT-CELL",AB_package);
    Qwidth = STATIC_SYMBOL("WIDTH",AB_package);
    Qenter_formatted_part_width = 
	    STATIC_SYMBOL("ENTER-FORMATTED-PART-WIDTH",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_formatted_part_width,
	    STATIC_FUNCTION(enter_formatted_part_width,NIL,FALSE,1,1));
    Qexit_formatted_part_width = STATIC_SYMBOL("EXIT-FORMATTED-PART-WIDTH",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_formatted_part_width,
	    STATIC_FUNCTION(exit_formatted_part_width,NIL,FALSE,0,0));
    list_constant_64 = STATIC_LIST((SI_Long)2L,Qfunction,
	    Qenter_formatted_part_width);
    list_constant_65 = STATIC_LIST((SI_Long)2L,Qfunction,
	    Qexit_formatted_part_width);
    list_constant_66 = STATIC_LIST((SI_Long)3L,Qcall_handlers,
	    list_constant_64,list_constant_65);
    def_part_feature_1(Qformatted_part,Qwidth,Qworkspace_measure,Qwidth,Qt,
	    SYMBOL_FUNCTION(Qenter_formatted_part_width),
	    SYMBOL_FUNCTION(Qexit_formatted_part_width),list_constant_66);
    if (Current_height_of_formatted_part == UNBOUND)
	Current_height_of_formatted_part = Qsymbol_standing_in_for_unbound;
    Qheight = STATIC_SYMBOL("HEIGHT",AB_package);
    Qenter_part_feature_height = STATIC_SYMBOL("ENTER-PART-FEATURE-HEIGHT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_height,
	    STATIC_FUNCTION(enter_part_feature_height,NIL,FALSE,1,1));
    Qexit_part_feature_height = STATIC_SYMBOL("EXIT-PART-FEATURE-HEIGHT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_height,
	    STATIC_FUNCTION(exit_part_feature_height,NIL,FALSE,0,0));
    Qcurrent_height_of_formatted_part = 
	    STATIC_SYMBOL("CURRENT-HEIGHT-OF-FORMATTED-PART",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_height_of_formatted_part,
	    Current_height_of_formatted_part);
    list_constant_67 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qcurrent_height_of_formatted_part);
    def_part_feature_1(Qformatted_part,Qheight,Qworkspace_measure,Qheight,
	    Qt,SYMBOL_FUNCTION(Qenter_part_feature_height),
	    SYMBOL_FUNCTION(Qexit_part_feature_height),list_constant_67);
    Qhm14 = STATIC_SYMBOL("HM14",AB_package);
    list_constant_68 = STATIC_CONS(Qhm14,Qnil);
    list_constant_71 = STATIC_LIST((SI_Long)8L,Qsmall,list_constant_68,
	    FIX((SI_Long)18L),FIX((SI_Long)14L),FIX((SI_Long)3L),
	    FIX((SI_Long)1280L),FIX((SI_Long)1024L),FIX((SI_Long)3072L));
    Qhm18 = STATIC_SYMBOL("HM18",AB_package);
    list_constant_69 = STATIC_CONS(Qhm18,Qnil);
    list_constant_72 = STATIC_LIST((SI_Long)8L,Qlarge,list_constant_69,
	    FIX((SI_Long)20L),FIX((SI_Long)15L),FIX((SI_Long)2L),
	    FIX((SI_Long)1728L),FIX((SI_Long)1280L),FIX((SI_Long)3840L));
    Qhm24 = STATIC_SYMBOL("HM24",AB_package);
    list_constant_70 = STATIC_CONS(Qhm24,Qnil);
    list_constant_73 = STATIC_LIST((SI_Long)8L,Qextra_large,
	    list_constant_70,FIX((SI_Long)26L),FIX((SI_Long)19L),
	    FIX((SI_Long)3L),FIX((SI_Long)2240L),FIX((SI_Long)1792L),
	    FIX((SI_Long)5376L));
    list_constant_74 = STATIC_LIST((SI_Long)3L,list_constant_71,
	    list_constant_72,list_constant_73);
    if (Part_text_size_parameters == UNBOUND)
	Part_text_size_parameters = list_constant_74;
    Qtext_cell_font_map = STATIC_SYMBOL("TEXT-CELL-FONT-MAP",AB_package);
    Qtext_cell_line_height = STATIC_SYMBOL("TEXT-CELL-LINE-HEIGHT",AB_package);
    Qtext_cell_baseline_position = 
	    STATIC_SYMBOL("TEXT-CELL-BASELINE-POSITION",AB_package);
    Qtext_cell_line_spacing = STATIC_SYMBOL("TEXT-CELL-LINE-SPACING",
	    AB_package);
    Qdefault_word_spacing = STATIC_SYMBOL("DEFAULT-WORD-SPACING",AB_package);
    Qminimum_word_spacing = STATIC_SYMBOL("MINIMUM-WORD-SPACING",AB_package);
    Qmaximum_word_spacing = STATIC_SYMBOL("MAXIMUM-WORD-SPACING",AB_package);
    Qenter_text_size = STATIC_SYMBOL("ENTER-TEXT-SIZE",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_text_size,STATIC_FUNCTION(enter_text_size,
	    NIL,FALSE,1,1));
    Qexit_text_size = STATIC_SYMBOL("EXIT-TEXT-SIZE",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_text_size,STATIC_FUNCTION(exit_text_size,NIL,
	    FALSE,0,0));
    list_constant_75 = STATIC_LIST((SI_Long)2L,Qfunction,Qenter_text_size);
    list_constant_76 = STATIC_LIST((SI_Long)2L,Qfunction,Qexit_text_size);
    list_constant_77 = STATIC_LIST((SI_Long)3L,Qcall_handlers,
	    list_constant_75,list_constant_76);
    def_part_feature_1(Qformatted_part,Qtext_size,Qtext_size,Qtext_size,Qt,
	    SYMBOL_FUNCTION(Qenter_text_size),
	    SYMBOL_FUNCTION(Qexit_text_size),list_constant_77);
    list_constant_78 = STATIC_CONS(Qsmall,Qsmall);
    Qregular = STATIC_SYMBOL("REGULAR",AB_package);
    list_constant_79 = STATIC_CONS(Qregular,Qlarge);
    list_constant_80 = STATIC_CONS(Qlarge,Qextra_large);
    list_constant_81 = STATIC_CONS(Qextra_large,Qextra_large);
    list_constant = STATIC_LIST((SI_Long)4L,list_constant_78,
	    list_constant_79,list_constant_80,list_constant_81);
    Qnew_table = STATIC_SYMBOL("NEW-TABLE",AB_package);
    list_constant_82 = STATIC_CONS(Qright,Qnil);
    list_constant_1 = STATIC_LIST_STAR((SI_Long)13L,Qformatted_part,
	    Qtext_color,Qforeground,Qline_color,Qforeground,Qborder_color,
	    Qforeground,Qbackground_color,Qtransparent,Qtext_size,Qsmall,
	    Qtext_alignment,list_constant_82);
    list_constant_2 = STATIC_CONS(Qformatted_part,Qnil);
    string_constant_42 = STATIC_STRING("WRITING-ANNOTATIONS");
    if (Writing_annotations == UNBOUND)
	Writing_annotations = make_recursive_lock(2,Kname,string_constant_42);
    Qwriting_annotations = STATIC_SYMBOL("WRITING-ANNOTATIONS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qwriting_annotations,Writing_annotations);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qwriting_annotations,
	    Qparts,Nil,Qnil,Qnil,Qnil,Nil);
    mutate_global_property(Qwriting_annotations,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    string_constant_5 = STATIC_STRING(";~%");
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_6 = STATIC_STRING("the ");
    string_constant_7 = STATIC_STRING("~( of any ~A~)");
    string_constant_8 = STATIC_STRING("~( of ~A ~D~)");
    Qthis_part_defaults = STATIC_SYMBOL("THIS-PART-DEFAULTS",AB_package);
    string_constant_9 = STATIC_STRING("~( of this ~A~)");
    string_constant_10 = STATIC_STRING("~( ~A ~)");
    string_constant_11 = STATIC_STRING("is");
    string_constant_12 = STATIC_STRING("=");
    Qab_slot_value = STATIC_SYMBOL("SLOT-VALUE",AB_package);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    if (Last_semantic_check_error_string == UNBOUND)
	Last_semantic_check_error_string = Nil;
    Qsemantic_error = STATIC_SYMBOL("SEMANTIC-ERROR",AB_package);
    string_constant_13 = 
	    STATIC_STRING("~(In statement #~D, ~A is not a known feature of ~A ~A.~)");
    string_constant_14 = 
	    STATIC_STRING("~(In statement #~D, ~A is not a supported attribute of ~A ~A.~)");
    Qred = STATIC_SYMBOL("RED",AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    string_constant_15 = STATIC_STRING("~(In statement #~D for ~S: ~)");
    Qcurrent_part_description = STATIC_SYMBOL("CURRENT-PART-DESCRIPTION",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_part_description,
	    Current_part_description);
    string_constant_16 = 
	    STATIC_STRING("Defaulting via \"any ~(~A~)\" is not supported.");
    string_constant_17 = 
	    STATIC_STRING("Setting a feature of an individual ~(~A~) is not supported.");
    list_constant_83 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_83,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)17L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)18L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)19L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)21L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)25L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)26L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)28L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)29L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)30L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)31L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)32L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)33L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)34L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)38L,(SI_Long)35L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)39L,(SI_Long)57344L);
    array_constant_1 = STATIC_ARRAY(list_constant_83,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)12L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)13L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)17L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)18L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)19L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)20L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)22L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)23L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)24L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)25L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)26L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)27L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)28L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)29L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)30L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)31L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)32L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)33L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)34L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)35L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)36L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)37L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)46L,(SI_Long)38L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)47L,(SI_Long)57344L);
    array_constant_2 = STATIC_ARRAY(list_constant_83,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)11L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)16L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)18L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)20L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)21L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)22L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)23L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)24L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)25L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)30L,(SI_Long)26L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)31L,(SI_Long)57344L);
    Qdefault_cell_format = STATIC_SYMBOL("DEFAULT-CELL-FORMAT",AB_package);
    array_constant_3 = STATIC_ARRAY(list_constant_83,(SI_Long)1L,
	    FIX((SI_Long)64L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)10L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)11L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)16L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)17L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)19L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)20L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)21L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)23L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)24L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)25L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)26L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)27L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)28L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)29L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)30L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)31L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)32L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)33L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)34L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)35L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)36L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)37L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)38L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)39L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)40L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)41L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)42L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)43L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)44L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)45L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)46L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)47L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)48L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)49L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)50L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)51L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)52L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)53L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)54L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)55L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)62L,(SI_Long)56L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)63L,(SI_Long)57344L);
    Qpart_feature_type_reclaimer = 
	    STATIC_SYMBOL("PART-FEATURE-TYPE-RECLAIMER",AB_package);
    Part_feature_type_reclaimer_prop = Qpart_feature_type_reclaimer;
    Qfeature_type_reclaimer_for_subparts_collection = 
	    STATIC_SYMBOL("FEATURE-TYPE-RECLAIMER-FOR-SUBPARTS-COLLECTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qfeature_type_reclaimer_for_subparts_collection,
	    STATIC_FUNCTION(feature_type_reclaimer_for_subparts_collection,
	    NIL,FALSE,1,1));
    mutate_global_property(Qsubparts_collection,
	    Qfeature_type_reclaimer_for_subparts_collection,
	    Qpart_feature_type_reclaimer);
    Qcell_array = STATIC_SYMBOL("CELL-ARRAY",AB_package);
    Qfeature_type_reclaimer_for_compute_part_feature_of_type_color_or_metacolor 
	    = 
	    STATIC_SYMBOL("FEATURE-TYPE-RECLAIMER-FOR-COMPUTE-PART-FEATURE-OF-TYPE-COLOR-OR-METACOLOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qfeature_type_reclaimer_for_compute_part_feature_of_type_color_or_metacolor,
	    STATIC_FUNCTION(feature_type_reclaimer_for_compute_part_feature_of_type_color_or_metacolor,
	    NIL,FALSE,1,1));
    mutate_global_property(Qcompute_part_feature_of_type_color_or_metacolor,
	    Qfeature_type_reclaimer_for_compute_part_feature_of_type_color_or_metacolor,
	    Qpart_feature_type_reclaimer);
    Qpart_description_of_frame = STATIC_SYMBOL("PART-DESCRIPTION-OF-FRAME",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpart_description_of_frame,
	    STATIC_FUNCTION(part_description_of_frame,NIL,FALSE,2,2));
    Qget_simple_part_feature = STATIC_SYMBOL("GET-SIMPLE-PART-FEATURE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_simple_part_feature,
	    STATIC_FUNCTION(get_simple_part_feature,NIL,FALSE,2,2));
    Qget_subpart_of_collection = STATIC_SYMBOL("GET-SUBPART-OF-COLLECTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_subpart_of_collection,
	    STATIC_FUNCTION(get_subpart_of_collection,NIL,FALSE,4,4));
    SET_SYMBOL_FUNCTION(Qset_simple_part_feature,
	    STATIC_FUNCTION(set_simple_part_feature,NIL,FALSE,3,3));
    list_constant_3 = STATIC_LIST((SI_Long)3L,Qsubparts,Qsubpart_defaults,
	    Qsubpart_exceptions);
    Qannotation_editing_info = STATIC_SYMBOL("ANNOTATION-EDITING-INFO",
	    AB_package);
    list_constant_84 = STATIC_CONS(Qblock,Qnil);
    check_if_superior_classes_are_defined(Qannotation_editing_info,
	    list_constant_84);
    string_constant_43 = STATIC_STRING("0");
    string_constant_44 = 
	    STATIC_STRING("1r4z8r83M8y83M8y83Gdy83Gdy00001m1l8o1l8l000004z8r83MJy83MJy83Gdy83Gdy00001m1l8o1l8l000004z8r83Gcy83Gcy83Gdy83Gdy00001m1l8o1l8l00");
    string_constant_45 = 
	    STATIC_STRING("0004z8r83LIy83LIy83Gdy83Gdy00001m1l8o1l8l000004z8r83csy83csy83Gdy83Gdy00001m1l8o1l8l000004z8r83KIy83KIy83Gdy83Gdy00001n1l8o1l8l1");
    string_constant_46 = 
	    STATIC_STRING("m8p83B3y000004z8r83Yiy83Yiy83Gdy83Gdy08k001n1l8o1l8l1m8p83B4y00000");
    string_constant_47 = 
	    STATIC_STRING("1t8q1m83Gdy1l9k1o83M8y08o8l1o83MJy08o8l1o83Gcy08o8l1o83LIy08o8l1o83csy08o8l1p83KIy08o8l1m8p83B3y1p83Yiy8k8o8l1m8p83B4y");
    temp = regenerate_optimized_constant(string_constant_43);
    temp_1 = regenerate_optimized_constant(LIST_3(string_constant_44,
	    string_constant_45,string_constant_46));
    clear_optimized_constants();
    push_optimized_constant(Qblock);
    add_class_to_environment(9,Qannotation_editing_info,list_constant_84,
	    Nil,temp,Nil,temp_1,list_constant_84,
	    regenerate_optimized_constant(string_constant_47),Nil);
    Qframe_being_edited = STATIC_SYMBOL("FRAME-BEING-EDITED",AB_package);
    Qreclaim_frame_being_edited_value = 
	    STATIC_SYMBOL("RECLAIM-FRAME-BEING-EDITED-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_frame_being_edited_value,
	    STATIC_FUNCTION(reclaim_frame_being_edited_value,NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qframe_being_edited,
	    SYMBOL_FUNCTION(Qreclaim_frame_being_edited_value),
	    Qslot_value_reclaimer);
    Qannotation_containing_feature = 
	    STATIC_SYMBOL("ANNOTATION-CONTAINING-FEATURE",AB_package);
    Qreclaim_annotation_containing_feature_value = 
	    STATIC_SYMBOL("RECLAIM-ANNOTATION-CONTAINING-FEATURE-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_annotation_containing_feature_value,
	    STATIC_FUNCTION(reclaim_annotation_containing_feature_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qannotation_containing_feature,
	    SYMBOL_FUNCTION(Qreclaim_annotation_containing_feature_value),
	    Qslot_value_reclaimer);
    Qeditable_slot_for_cell_expression_and_text = 
	    STATIC_SYMBOL("EDITABLE-SLOT-FOR-CELL-EXPRESSION-AND-TEXT",
	    AB_package);
    Qreclaim_editable_slot_for_cell_expression_and_text_value = 
	    STATIC_SYMBOL("RECLAIM-EDITABLE-SLOT-FOR-CELL-EXPRESSION-AND-TEXT-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_editable_slot_for_cell_expression_and_text_value,
	    STATIC_FUNCTION(reclaim_editable_slot_for_cell_expression_and_text_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qeditable_slot_for_cell_expression_and_text,
	    SYMBOL_FUNCTION(Qreclaim_editable_slot_for_cell_expression_and_text_value),
	    Qslot_value_reclaimer);
    Qreference_to_data_in_frame_containing_annotation = 
	    STATIC_SYMBOL("REFERENCE-TO-DATA-IN-FRAME-CONTAINING-ANNOTATION",
	    AB_package);
    Qreclaim_reference_to_data_in_frame_containing_annotation_value = 
	    STATIC_SYMBOL("RECLAIM-REFERENCE-TO-DATA-IN-FRAME-CONTAINING-ANNOTATION-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_reference_to_data_in_frame_containing_annotation_value,
	    STATIC_FUNCTION(reclaim_reference_to_data_in_frame_containing_annotation_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qreference_to_data_in_frame_containing_annotation,
	    SYMBOL_FUNCTION(Qreclaim_reference_to_data_in_frame_containing_annotation_value),
	    Qslot_value_reclaimer);
    Qframe_serial_number_of_frame_being_edited = 
	    STATIC_SYMBOL("FRAME-SERIAL-NUMBER-OF-FRAME-BEING-EDITED",
	    AB_package);
    Qreclaim_frame_serial_number_of_frame_being_edited_value = 
	    STATIC_SYMBOL("RECLAIM-FRAME-SERIAL-NUMBER-OF-FRAME-BEING-EDITED-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_frame_serial_number_of_frame_being_edited_value,
	    STATIC_FUNCTION(reclaim_frame_serial_number_of_frame_being_edited_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qframe_serial_number_of_frame_being_edited,
	    SYMBOL_FUNCTION(Qreclaim_frame_serial_number_of_frame_being_edited_value),
	    Qslot_value_reclaimer);
    Qcell_format = STATIC_SYMBOL("CELL-FORMAT",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)4L,Qcell_format,
	    Qreference_to_data_in_frame_containing_annotation,
	    Qcell_expression_and_text,
	    Qeditable_slot_for_cell_expression_and_text);
    Qfinish_edit_of_annotation_subexpression = 
	    STATIC_SYMBOL("FINISH-EDIT-OF-ANNOTATION-SUBEXPRESSION",
	    AB_package);
    Qcleanup_edit_of_annotation_subexpression = 
	    STATIC_SYMBOL("CLEANUP-EDIT-OF-ANNOTATION-SUBEXPRESSION",
	    AB_package);
    Qcell_expression_parse = STATIC_SYMBOL("CELL-EXPRESSION-PARSE",AB_package);
    list_constant_5 = STATIC_LIST((SI_Long)2L,Qtype,Qcell_expression_parse);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Qtype,Qcell_format);
    Qediting = STATIC_SYMBOL("EDITING",AB_package);
    Qupdate_part_dependencies = STATIC_SYMBOL("UPDATE-PART-DEPENDENCIES",
	    AB_package);
    Qkind_of_change = STATIC_SYMBOL("KIND-OF-CHANGE",AB_package);
    Qwhat_changed = STATIC_SYMBOL("WHAT-CHANGED",AB_package);
    list_constant_85 = STATIC_LIST((SI_Long)3L,Qblock,Qkind_of_change,
	    Qwhat_changed);
    Qgeneric_method_lambda_list = 
	    STATIC_SYMBOL("GENERIC-METHOD-LAMBDA-LIST",AB_package);
    mutate_global_property(Qupdate_part_dependencies,list_constant_85,
	    Qgeneric_method_lambda_list);
    list_constant_86 = STATIC_LIST((SI_Long)7L,Qbackground_color,Qwidth,
	    Qheight,Qborder_color,Qtext_alignment,Qtext_color,Qtext_size);
    Cell_format_part_features = list_constant_86;
    Qframe_status_and_notes = STATIC_SYMBOL("FRAME-STATUS-AND-NOTES",
	    AB_package);
    Qstack_change = STATIC_SYMBOL("STACK-CHANGE",AB_package);
    list_constant_7 = STATIC_LIST((SI_Long)2L,Qtext_size,Qtext_alignment);
    Qfreeform_table = STATIC_SYMBOL("FREEFORM-TABLE",AB_package);
    Qtable_cells = STATIC_SYMBOL("TABLE-CELLS",AB_package);
    Qvirtual_attribute = STATIC_SYMBOL("VIRTUAL-ATTRIBUTE",AB_package);
    Qput_reference_to_data_in_frame_containing_annotation = 
	    STATIC_SYMBOL("PUT-REFERENCE-TO-DATA-IN-FRAME-CONTAINING-ANNOTATION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_reference_to_data_in_frame_containing_annotation,
	    STATIC_FUNCTION(put_reference_to_data_in_frame_containing_annotation,
	    NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qreference_to_data_in_frame_containing_annotation,
	    SYMBOL_FUNCTION(Qput_reference_to_data_in_frame_containing_annotation),
	    Qslot_putter);
    list_constant_8 = STATIC_LIST((SI_Long)2L,Qcell_expression_and_text,
	    Qeditable_slot_for_cell_expression_and_text);
    SET_SYMBOL_FUNCTION(Qfinish_edit_of_annotation_subexpression,
	    STATIC_FUNCTION(finish_edit_of_annotation_subexpression,NIL,
	    FALSE,1,1));
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_edit_of_annotation_subexpression,
	    STATIC_FUNCTION(cleanup_edit_of_annotation_subexpression,NIL,
	    FALSE,1,1));
    Qcell_contents = STATIC_SYMBOL("CELL-CONTENTS",AB_package);
    Qcell_expression = STATIC_SYMBOL("CELL-EXPRESSION",AB_package);
    Qcomputation_style_tracing_and_breakpoints = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-TRACING-AND-BREAKPOINTS",
	    AB_package);
    string_constant_48 = STATIC_STRING("COMPUTATION-STYLE-DESCRIPTION");
    if (Computation_style_description == UNBOUND)
	Computation_style_description = make_recursive_lock(2,Kname,
		string_constant_48);
    Qcomputation_style_description = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-DESCRIPTION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcomputation_style_description,
	    Computation_style_description);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qcomputation_style_description,
	    Qparts,Nil,Qnil,Qnil,list_constant_53,Nil);
    mutate_global_property(Qcomputation_style_description,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    if (Current_computation_style_description == UNBOUND)
	Current_computation_style_description = 
		Qsymbol_standing_in_for_unbound;
    Qevaluation_attributes = STATIC_SYMBOL("EVALUATION-ATTRIBUTES",AB_package);
    list_constant_87 = STATIC_LIST((SI_Long)2L,Quser_spelling,
	    Qevaluation_attributes);
    list_constant_88 = STATIC_CONS(list_constant_87,Qnil);
    def_part_type_1(Qcomputation_style_description,list_constant_53,
	    list_constant_88);
    def_part_feature_1(Qcomputation_style_description,Qsubparts,
	    list_constant_33,Qsubparts,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_subparts),
	    SYMBOL_FUNCTION(Qexit_part_feature_subparts),list_constant_34);
    def_part_feature_1(Qcomputation_style_description,Qsubpart_defaults,
	    list_constant_33,Qsubpart_defaults,Qnil,
	    SYMBOL_FUNCTION(Qenter_subpart_defaults),
	    SYMBOL_FUNCTION(Qexit_subpart_defaults),list_constant_37);
    def_part_feature_1(Qcomputation_style_description,Qsubpart_exceptions,
	    list_constant_33,Qsubpart_exceptions,Qnil,
	    SYMBOL_FUNCTION(Qenter_subpart_exceptions),
	    SYMBOL_FUNCTION(Qexit_subpart_exceptions),list_constant_40);
    Qcomputation_style_priority = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-PRIORITY",AB_package);
    Qpriority = STATIC_SYMBOL("PRIORITY",AB_package);
    Qenter_part_feature_priority = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-PRIORITY",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_priority,
	    STATIC_FUNCTION(enter_part_feature_priority,NIL,FALSE,1,1));
    Qexit_part_feature_priority = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-PRIORITY",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_priority,
	    STATIC_FUNCTION(exit_part_feature_priority,NIL,FALSE,0,0));
    Qcurrent_computation_style = STATIC_SYMBOL("CURRENT-COMPUTATION-STYLE",
	    AB_package);
    list_constant_89 = STATIC_LIST((SI_Long)3L,Qclass_slot,
	    Qcurrent_computation_style,Qcomputation_style_priority);
    def_part_feature_1(Qcomputation_style_description,Qpriority,
	    Qpriority_level,Qpriority,Qt,
	    SYMBOL_FUNCTION(Qenter_part_feature_priority),
	    SYMBOL_FUNCTION(Qexit_part_feature_priority),list_constant_89);
    Qcomputation_style_scan_interval = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-SCAN-INTERVAL",AB_package);
    Qscan_interval = STATIC_SYMBOL("SCAN-INTERVAL",AB_package);
    Qenter_part_feature_scan_interval = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-SCAN-INTERVAL",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_scan_interval,
	    STATIC_FUNCTION(enter_part_feature_scan_interval,NIL,FALSE,1,1));
    Qexit_part_feature_scan_interval = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-SCAN-INTERVAL",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_scan_interval,
	    STATIC_FUNCTION(exit_part_feature_scan_interval,NIL,FALSE,0,0));
    list_constant_90 = STATIC_LIST((SI_Long)3L,Qclass_slot,
	    Qcurrent_computation_style,Qcomputation_style_scan_interval);
    def_part_feature_1(Qcomputation_style_description,Qscan_interval,
	    Qsimple_interval,Qscan_interval,Qt,
	    SYMBOL_FUNCTION(Qenter_part_feature_scan_interval),
	    SYMBOL_FUNCTION(Qexit_part_feature_scan_interval),
	    list_constant_90);
    Qcomputation_style_initial_scan_wait_interval = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-INITIAL-SCAN-WAIT-INTERVAL",
	    AB_package);
    Qinitial_scan_wait_interval = 
	    STATIC_SYMBOL("INITIAL-SCAN-WAIT-INTERVAL",AB_package);
    Qenter_part_feature_initial_scan_wait_interval = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-INITIAL-SCAN-WAIT-INTERVAL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_initial_scan_wait_interval,
	    STATIC_FUNCTION(enter_part_feature_initial_scan_wait_interval,
	    NIL,FALSE,1,1));
    Qexit_part_feature_initial_scan_wait_interval = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-INITIAL-SCAN-WAIT-INTERVAL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_initial_scan_wait_interval,
	    STATIC_FUNCTION(exit_part_feature_initial_scan_wait_interval,
	    NIL,FALSE,0,0));
    list_constant_91 = STATIC_LIST((SI_Long)3L,Qclass_slot,
	    Qcurrent_computation_style,
	    Qcomputation_style_initial_scan_wait_interval);
    def_part_feature_1(Qcomputation_style_description,
	    Qinitial_scan_wait_interval,Qsimple_interval,
	    Qinitial_scan_wait_interval,Qt,
	    SYMBOL_FUNCTION(Qenter_part_feature_initial_scan_wait_interval),
	    SYMBOL_FUNCTION(Qexit_part_feature_initial_scan_wait_interval),
	    list_constant_91);
    Qcomputation_style_value_domain = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-VALUE-DOMAIN",AB_package);
    Qvalue_domain = STATIC_SYMBOL("VALUE-DOMAIN",AB_package);
    Qenter_part_feature_value_domain = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-VALUE-DOMAIN",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_value_domain,
	    STATIC_FUNCTION(enter_part_feature_value_domain,NIL,FALSE,1,1));
    Qexit_part_feature_value_domain = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-VALUE-DOMAIN",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_value_domain,
	    STATIC_FUNCTION(exit_part_feature_value_domain,NIL,FALSE,0,0));
    list_constant_92 = STATIC_LIST((SI_Long)3L,Qclass_slot,
	    Qcurrent_computation_style,Qcomputation_style_value_domain);
    def_part_feature_1(Qcomputation_style_description,Qvalue_domain,
	    Qvalue_domain_kind,Qvalue_domain,Qt,
	    SYMBOL_FUNCTION(Qenter_part_feature_value_domain),
	    SYMBOL_FUNCTION(Qexit_part_feature_value_domain),list_constant_92);
    Qcomputation_style_update_only_when_shown = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-UPDATE-ONLY-WHEN-SHOWN",
	    AB_package);
    Qupdate_only_when_shown = STATIC_SYMBOL("UPDATE-ONLY-WHEN-SHOWN",
	    AB_package);
    Qenter_part_feature_update_only_when_shown = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-UPDATE-ONLY-WHEN-SHOWN",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_update_only_when_shown,
	    STATIC_FUNCTION(enter_part_feature_update_only_when_shown,NIL,
	    FALSE,1,1));
    Qexit_part_feature_update_only_when_shown = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-UPDATE-ONLY-WHEN-SHOWN",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_update_only_when_shown,
	    STATIC_FUNCTION(exit_part_feature_update_only_when_shown,NIL,
	    FALSE,0,0));
    list_constant_93 = STATIC_LIST((SI_Long)3L,Qclass_slot,
	    Qcurrent_computation_style,
	    Qcomputation_style_update_only_when_shown);
    def_part_feature_1(Qcomputation_style_description,
	    Qupdate_only_when_shown,Qboolean,Qupdate_only_when_shown,Qt,
	    SYMBOL_FUNCTION(Qenter_part_feature_update_only_when_shown),
	    SYMBOL_FUNCTION(Qexit_part_feature_update_only_when_shown),
	    list_constant_93);
    Qtrace_message_level_for_computation_style = 
	    STATIC_SYMBOL("TRACE-MESSAGE-LEVEL-FOR-COMPUTATION-STYLE",
	    AB_package);
    Qtrace_message_level = STATIC_SYMBOL("TRACE-MESSAGE-LEVEL",AB_package);
    Qenter_tracing_level = STATIC_SYMBOL("ENTER-TRACING-LEVEL",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_tracing_level,
	    STATIC_FUNCTION(enter_tracing_level,NIL,FALSE,1,1));
    Qexit_tracing_or_breakpoints_setting = 
	    STATIC_SYMBOL("EXIT-TRACING-OR-BREAKPOINTS-SETTING",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_tracing_or_breakpoints_setting,
	    STATIC_FUNCTION(exit_tracing_or_breakpoints_setting,NIL,FALSE,
	    0,0));
    list_constant_94 = STATIC_LIST((SI_Long)2L,Qfunction,Qenter_tracing_level);
    list_constant_95 = STATIC_LIST((SI_Long)2L,Qfunction,
	    Qexit_tracing_or_breakpoints_setting);
    list_constant_96 = STATIC_LIST((SI_Long)3L,Qcall_handlers,
	    list_constant_94,list_constant_95);
    def_part_feature_1(Qcomputation_style_description,
	    Qtrace_message_level_for_computation_style,Qtrace_level,
	    Qtrace_message_level,Qt,SYMBOL_FUNCTION(Qenter_tracing_level),
	    SYMBOL_FUNCTION(Qexit_tracing_or_breakpoints_setting),
	    list_constant_96);
    Qwarning_message_level_for_computation_style = 
	    STATIC_SYMBOL("WARNING-MESSAGE-LEVEL-FOR-COMPUTATION-STYLE",
	    AB_package);
    Qwarning_message_level = STATIC_SYMBOL("WARNING-MESSAGE-LEVEL",AB_package);
    Qenter_warning_level = STATIC_SYMBOL("ENTER-WARNING-LEVEL",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_warning_level,
	    STATIC_FUNCTION(enter_warning_level,NIL,FALSE,1,1));
    list_constant_97 = STATIC_LIST((SI_Long)2L,Qfunction,Qenter_warning_level);
    list_constant_98 = STATIC_CONS(list_constant_95,Qnil);
    list_constant_99 = STATIC_LIST_STAR((SI_Long)3L,Qcall_handlers,
	    list_constant_97,list_constant_98);
    def_part_feature_1(Qcomputation_style_description,
	    Qwarning_message_level_for_computation_style,Qwarning_level,
	    Qwarning_message_level,Qt,
	    SYMBOL_FUNCTION(Qenter_warning_level),
	    SYMBOL_FUNCTION(Qexit_tracing_or_breakpoints_setting),
	    list_constant_99);
    Qbreak_message_level_for_computation_style = 
	    STATIC_SYMBOL("BREAK-MESSAGE-LEVEL-FOR-COMPUTATION-STYLE",
	    AB_package);
    Qbreak_message_level = STATIC_SYMBOL("BREAK-MESSAGE-LEVEL",AB_package);
    Qenter_break_level = STATIC_SYMBOL("ENTER-BREAK-LEVEL",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_break_level,
	    STATIC_FUNCTION(enter_break_level,NIL,FALSE,1,1));
    list_constant_100 = STATIC_LIST((SI_Long)2L,Qfunction,Qenter_break_level);
    list_constant_101 = STATIC_LIST_STAR((SI_Long)3L,Qcall_handlers,
	    list_constant_100,list_constant_98);
    def_part_feature_1(Qcomputation_style_description,
	    Qbreak_message_level_for_computation_style,Qbreak_level,
	    Qbreak_message_level,Qt,SYMBOL_FUNCTION(Qenter_break_level),
	    SYMBOL_FUNCTION(Qexit_tracing_or_breakpoints_setting),
	    list_constant_101);
    Qcomputation_style_may_request_event_updates = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-MAY-REQUEST-EVENT-UPDATES",
	    AB_package);
    Qmay_request_event_updates = STATIC_SYMBOL("MAY-REQUEST-EVENT-UPDATES",
	    AB_package);
    Qenter_part_feature_may_request_event_updates = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-MAY-REQUEST-EVENT-UPDATES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_may_request_event_updates,
	    STATIC_FUNCTION(enter_part_feature_may_request_event_updates,
	    NIL,FALSE,1,1));
    Qexit_part_feature_may_request_event_updates = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-MAY-REQUEST-EVENT-UPDATES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_may_request_event_updates,
	    STATIC_FUNCTION(exit_part_feature_may_request_event_updates,
	    NIL,FALSE,0,0));
    list_constant_102 = STATIC_LIST((SI_Long)3L,Qclass_slot,
	    Qcurrent_computation_style,
	    Qcomputation_style_may_request_event_updates);
    def_part_feature_1(Qcomputation_style_description,
	    Qmay_request_event_updates,Qboolean,Qmay_request_event_updates,
	    Qt,
	    SYMBOL_FUNCTION(Qenter_part_feature_may_request_event_updates),
	    SYMBOL_FUNCTION(Qexit_part_feature_may_request_event_updates),
	    list_constant_102);
    Qcomputation_style_may_request_data_seeking = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-MAY-REQUEST-DATA-SEEKING",
	    AB_package);
    Qmay_request_data_seeking = STATIC_SYMBOL("MAY-REQUEST-DATA-SEEKING",
	    AB_package);
    Qenter_part_feature_may_request_data_seeking = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-MAY-REQUEST-DATA-SEEKING",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_may_request_data_seeking,
	    STATIC_FUNCTION(enter_part_feature_may_request_data_seeking,
	    NIL,FALSE,1,1));
    Qexit_part_feature_may_request_data_seeking = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-MAY-REQUEST-DATA-SEEKING",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_may_request_data_seeking,
	    STATIC_FUNCTION(exit_part_feature_may_request_data_seeking,NIL,
	    FALSE,0,0));
    list_constant_103 = STATIC_LIST((SI_Long)3L,Qclass_slot,
	    Qcurrent_computation_style,
	    Qcomputation_style_may_request_data_seeking);
    def_part_feature_1(Qcomputation_style_description,
	    Qmay_request_data_seeking,Qboolean,Qmay_request_data_seeking,
	    Qt,
	    SYMBOL_FUNCTION(Qenter_part_feature_may_request_data_seeking),
	    SYMBOL_FUNCTION(Qexit_part_feature_may_request_data_seeking),
	    list_constant_103);
    Qcomputation_style_time_out_when_requesting_data_seeking = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-TIME-OUT-WHEN-REQUESTING-DATA-SEEKING",
	    AB_package);
    Qtime_out_when_requesting_data_seeking = 
	    STATIC_SYMBOL("TIME-OUT-WHEN-REQUESTING-DATA-SEEKING",AB_package);
    Qenter_part_feature_time_out_when_requesting_data_seeking = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-TIME-OUT-WHEN-REQUESTING-DATA-SEEKING",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_time_out_when_requesting_data_seeking,
	    STATIC_FUNCTION(enter_part_feature_time_out_when_requesting_data_seeking,
	    NIL,FALSE,1,1));
    Qexit_part_feature_time_out_when_requesting_data_seeking = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-TIME-OUT-WHEN-REQUESTING-DATA-SEEKING",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_time_out_when_requesting_data_seeking,
	    STATIC_FUNCTION(exit_part_feature_time_out_when_requesting_data_seeking,
	    NIL,FALSE,0,0));
    list_constant_104 = STATIC_LIST((SI_Long)3L,Qclass_slot,
	    Qcurrent_computation_style,
	    Qcomputation_style_time_out_when_requesting_data_seeking);
    def_part_feature_1(Qcomputation_style_description,
	    Qtime_out_when_requesting_data_seeking,Qsimple_interval,
	    Qtime_out_when_requesting_data_seeking,Qt,
	    SYMBOL_FUNCTION(Qenter_part_feature_time_out_when_requesting_data_seeking),
	    SYMBOL_FUNCTION(Qexit_part_feature_time_out_when_requesting_data_seeking),
	    list_constant_104);
    Qcomputation_style_may_provide_data_on_request = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-MAY-PROVIDE-DATA-ON-REQUEST",
	    AB_package);
    Qmay_provide_data_on_request = 
	    STATIC_SYMBOL("MAY-PROVIDE-DATA-ON-REQUEST",AB_package);
    Qenter_part_feature_may_provide_data_on_request = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-MAY-PROVIDE-DATA-ON-REQUEST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_may_provide_data_on_request,
	    STATIC_FUNCTION(enter_part_feature_may_provide_data_on_request,
	    NIL,FALSE,1,1));
    Qexit_part_feature_may_provide_data_on_request = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-MAY-PROVIDE-DATA-ON-REQUEST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_may_provide_data_on_request,
	    STATIC_FUNCTION(exit_part_feature_may_provide_data_on_request,
	    NIL,FALSE,0,0));
    list_constant_105 = STATIC_LIST((SI_Long)3L,Qclass_slot,
	    Qcurrent_computation_style,
	    Qcomputation_style_may_provide_data_on_request);
    def_part_feature_1(Qcomputation_style_description,
	    Qmay_provide_data_on_request,Qboolean,
	    Qmay_provide_data_on_request,Qt,
	    SYMBOL_FUNCTION(Qenter_part_feature_may_provide_data_on_request),
	    SYMBOL_FUNCTION(Qexit_part_feature_may_provide_data_on_request),
	    list_constant_105);
    Qcomputation_style_may_provide_event_updates = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-MAY-PROVIDE-EVENT-UPDATES",
	    AB_package);
    Qmay_provide_event_updates = STATIC_SYMBOL("MAY-PROVIDE-EVENT-UPDATES",
	    AB_package);
    Qenter_part_feature_may_provide_event_updates = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-MAY-PROVIDE-EVENT-UPDATES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_may_provide_event_updates,
	    STATIC_FUNCTION(enter_part_feature_may_provide_event_updates,
	    NIL,FALSE,1,1));
    Qexit_part_feature_may_provide_event_updates = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-MAY-PROVIDE-EVENT-UPDATES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_may_provide_event_updates,
	    STATIC_FUNCTION(exit_part_feature_may_provide_event_updates,
	    NIL,FALSE,0,0));
    list_constant_106 = STATIC_LIST((SI_Long)3L,Qclass_slot,
	    Qcurrent_computation_style,
	    Qcomputation_style_may_provide_event_updates);
    def_part_feature_1(Qcomputation_style_description,
	    Qmay_provide_event_updates,Qboolean,Qmay_provide_event_updates,
	    Qt,
	    SYMBOL_FUNCTION(Qenter_part_feature_may_provide_event_updates),
	    SYMBOL_FUNCTION(Qexit_part_feature_may_provide_event_updates),
	    list_constant_106);
    Qupdate_after_edits = STATIC_SYMBOL("UPDATE-AFTER-EDITS",AB_package);
    Qenter_part_feature_update_after_edits = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-UPDATE-AFTER-EDITS",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_update_after_edits,
	    STATIC_FUNCTION(enter_part_feature_update_after_edits,NIL,
	    FALSE,1,1));
    Qexit_part_feature_update_after_edits = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-UPDATE-AFTER-EDITS",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_update_after_edits,
	    STATIC_FUNCTION(exit_part_feature_update_after_edits,NIL,FALSE,
	    0,0));
    def_part_feature_1(Qcomputation_style_description,Qupdate_after_edits,
	    Qboolean,Qupdate_after_edits,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_update_after_edits),
	    SYMBOL_FUNCTION(Qexit_part_feature_update_after_edits),
	    list_constant_106);
    Qcomputation_style_network_access_attempt = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-NETWORK-ACCESS-ATTEMPT",
	    AB_package);
    Qnetwork_access_attempt = STATIC_SYMBOL("NETWORK-ACCESS-ATTEMPT",
	    AB_package);
    Qenter_part_feature_network_access_attempt = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-NETWORK-ACCESS-ATTEMPT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_network_access_attempt,
	    STATIC_FUNCTION(enter_part_feature_network_access_attempt,NIL,
	    FALSE,1,1));
    Qexit_part_feature_network_access_attempt = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-NETWORK-ACCESS-ATTEMPT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_network_access_attempt,
	    STATIC_FUNCTION(exit_part_feature_network_access_attempt,NIL,
	    FALSE,0,0));
    list_constant_107 = STATIC_LIST((SI_Long)3L,Qclass_slot,
	    Qcurrent_computation_style,
	    Qcomputation_style_network_access_attempt);
    def_part_feature_1(Qcomputation_style_description,
	    Qnetwork_access_attempt,Qnetwork_access_kind,
	    Qnetwork_access_attempt,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_network_access_attempt),
	    SYMBOL_FUNCTION(Qexit_part_feature_network_access_attempt),
	    list_constant_107);
    string_constant_49 = STATIC_STRING("1m1m832Uy1m9k83=Oy1m832Uy1m9k832Zy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_49));
    Qsimplify_associative_operation = 
	    STATIC_SYMBOL("SIMPLIFY-ASSOCIATIVE-OPERATION",AB_package);
    Qreduce_annotation = STATIC_SYMBOL("REDUCE-ANNOTATION",AB_package);
    SET_SYMBOL_FUNCTION(Qreduce_annotation,
	    STATIC_FUNCTION(reduce_annotation,NIL,FALSE,1,1));
    Qreduce_common_computation_phrase_scan_interval = 
	    STATIC_SYMBOL("REDUCE-COMMON-COMPUTATION-PHRASE-SCAN-INTERVAL",
	    AB_package);
    string_constant_50 = 
	    STATIC_STRING("13Ly1n836hy1m1m9k83-T0y83-NIym1n836hy1m1m9k83-T0y83-NUym1m83-NIy83-NJy1n83-NJy83-NHy1m9ll1o83-NJy1m83-NHy83-NJy1n9llm9m1o83-NHy1");
    string_constant_51 = 
	    STATIC_STRING("n1m9k83=Gy1m9k83-Yy83Sy1n83BSy83-Yyn9n1o83-NHy1m1m9k9o831Ny1n83BSy83-CNym9p1n83-NUy1p1m9k83=Fy1m9k83-sny1m9k83-oUy1m9k83-Py83-Nc");
    string_constant_52 = 
	    STATIC_STRING("yp1m83-Ncy83-Ndy1n83-Ndy83-Nby1m9ll1o83-Ndy1n83-Nby1m9k83-Zy83-Ndy1n9lln9m1o83-Nby1n1m9k83-Yy1m9k9q83-Hy1n83BSy83-Yyn9n1o83-Nby1");
    string_constant_53 = 
	    STATIC_STRING("n1m9k83-CNy1m9k9q83-Hy1n83BSy83-CNyn9n1o83-Nby1n1m9k83-a-y1m9k9q83-Hy1n83BSy83-a-yn9n1o83-Nby1n1m9k83-w7y1m9k83*Iy1m9k837*y1n83B");
    string_constant_54 = 
	    STATIC_STRING("Sy83-w7yn9n1o83-Nby1n1m9k83-w7y1m9k83*Iy1m9k83-VVy1n83BSy83-w7yn9n1o83-Nby1n1m9k83-vYy1m9k83*Iy832Uy1n83BSy83-vYyn9n1o83-Nby1n1m");
    string_constant_55 = 
	    STATIC_STRING("9k83-tdy1m9k9q83-Hy1n83BSy83-tdyn9n1o83-Nby1n1m9k832Ty1m9k9q83-Hy1n83BSy832Tyn9n1o83-Nby1n1m9k83-L=y1m9k9q83-Hy1n83BSy83-L=yn9n1");
    string_constant_56 = 
	    STATIC_STRING("o83-Nby1n1m9k83-tCy1m9k9q83-Hy1n83BSy83-tCyn9n1o83-Nby1n1m9k83-e0y1m9k83*Iy832Uy1n83BSy83-e0yn9n1o83-Nby1n1m9k83-e*y1m9k83*Iy832");
    string_constant_57 = 
	    STATIC_STRING("Uy1n83BSy83-e*yn9n1o83-Nby1n1m9k83-e+y1m9k83*Iy832Uy1n83BSy83-e+yn9n1o83-Nby1n1m9k83-e-y1m9k83*Iy832Uy1n83BSy83-e-yn9n");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qprogn);
    push_optimized_constant(Qsimplify_associative_operation);
    push_optimized_constant(Qreduce_annotation);
    push_optimized_constant(Qevery);
    push_optimized_constant(Qreduce_common_computation_phrase_scan_interval);
    push_optimized_constant(Qnum_eq);
    add_grammar_rules_function(regenerate_optimized_constant(list(8,
	    string_constant_50,string_constant_51,string_constant_52,
	    string_constant_53,string_constant_54,string_constant_55,
	    string_constant_56,string_constant_57)));
    SET_SYMBOL_FUNCTION(Qreduce_common_computation_phrase_scan_interval,
	    STATIC_FUNCTION(reduce_common_computation_phrase_scan_interval,
	    NIL,FALSE,1,1));
    string_constant_58 = STATIC_STRING("1m1m83sfy1m9k83Zy1m83sfy836hy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_58));
    list_constant_9 = STATIC_LIST((SI_Long)13L,Qmay_provide_event_updates,
	    Qmay_provide_data_on_request,
	    Qtime_out_when_requesting_data_seeking,
	    Qmay_request_data_seeking,Qmay_request_event_updates,
	    Qbreak_message_level_for_computation_style,
	    Qwarning_message_level_for_computation_style,
	    Qtrace_message_level_for_computation_style,
	    Qupdate_only_when_shown,Qvalue_domain,
	    Qinitial_scan_wait_interval,Qscan_interval,Qpriority);
    string_constant_18 = STATIC_STRING("~%  ");
    string_constant_19 = STATIC_STRING("evaluated");
    string_constant_20 = STATIC_STRING(" every ~NC");
    Qseconds = STATIC_SYMBOL("SECONDS",AB_package);
    string_constant_21 = STATIC_STRING(" at priority ~D");
    string_constant_22 = STATIC_STRING("evaluated with these settings:~%");
    string_constant_59 = STATIC_STRING("1l1m832wy83sfy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_59));
    array_constant_4 = STATIC_ARRAY(list_constant_83,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)57344L);
    Qcomputation_style_or_none = STATIC_SYMBOL("COMPUTATION-STYLE-OR-NONE",
	    AB_package);
    Qwrite_computation_style_or_none_from_slot = 
	    STATIC_SYMBOL("WRITE-COMPUTATION-STYLE-OR-NONE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_computation_style_or_none_from_slot,
	    STATIC_FUNCTION(write_computation_style_or_none_from_slot,NIL,
	    FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qcomputation_style_or_none,
	    SYMBOL_FUNCTION(Qwrite_computation_style_or_none_from_slot),
	    Qslot_value_writer);
    Qcompile_computation_style_or_none_for_slot = 
	    STATIC_SYMBOL("COMPILE-COMPUTATION-STYLE-OR-NONE-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_computation_style_or_none_for_slot,
	    STATIC_FUNCTION(compile_computation_style_or_none_for_slot,NIL,
	    TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qcomputation_style_or_none,
	    SYMBOL_FUNCTION(Qcompile_computation_style_or_none_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qcomputation_style_or_none,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_12 = STATIC_CONS(Qno_item,Qnil);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    list_constant_13 = STATIC_CONS(Qab_structure,Qnil);
    list_constant_108 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_12,
	    list_constant_13);
    set_property_value_function(get_symbol_properties_function(Qcomputation_style_or_none),
	    Qtype_specification_simple_expansion,list_constant_108);
    list_constant_112 = STATIC_LIST((SI_Long)2L,Qpriority,list_constant_50);
    list_constant_109 = STATIC_CONS(Qnumber,Qnil);
    list_constant_113 = STATIC_CONS(Qscan_interval,list_constant_109);
    list_constant_114 = STATIC_CONS(Qinitial_scan_wait_interval,
	    list_constant_109);
    list_constant_115 = STATIC_LIST((SI_Long)2L,Qvalue_domain,
	    list_constant_47);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    list_constant_110 = STATIC_CONS(Qtruth_value,Qnil);
    list_constant_116 = STATIC_CONS(Qupdate_only_when_shown,list_constant_110);
    list_constant_111 = STATIC_CONS(list_constant_48,Qnil);
    list_constant_117 = STATIC_CONS(Qtrace_message_level,list_constant_111);
    list_constant_118 = STATIC_CONS(Qwarning_message_level,list_constant_111);
    list_constant_119 = STATIC_CONS(Qbreak_message_level,list_constant_111);
    list_constant_120 = STATIC_LIST((SI_Long)2L,
	    Qtime_out_when_requesting_data_seeking,Qinteger);
    list_constant_121 = STATIC_CONS(Qmay_request_event_updates,
	    list_constant_110);
    list_constant_122 = STATIC_CONS(Qmay_request_data_seeking,
	    list_constant_110);
    list_constant_123 = STATIC_CONS(Qmay_provide_data_on_request,
	    list_constant_110);
    list_constant_124 = STATIC_CONS(Qmay_provide_event_updates,
	    list_constant_110);
    list_constant_125 = STATIC_LIST((SI_Long)13L,list_constant_112,
	    list_constant_113,list_constant_114,list_constant_115,
	    list_constant_116,list_constant_117,list_constant_118,
	    list_constant_119,list_constant_120,list_constant_121,
	    list_constant_122,list_constant_123,list_constant_124);
    list_constant_126 = STATIC_LIST((SI_Long)14L,Qab_or,Qpriority,
	    Qscan_interval,Qinitial_scan_wait_interval,Qvalue_domain,
	    Qupdate_only_when_shown,Qtrace_message_level,
	    Qwarning_message_level,Qbreak_message_level,
	    Qtime_out_when_requesting_data_seeking,
	    Qmay_request_event_updates,Qmay_request_data_seeking,
	    Qmay_provide_data_on_request,Qmay_provide_event_updates);
    list_constant_127 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_125,list_constant_126);
    list_constant_11 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_12,
	    list_constant_127);
    define_type_specification_explicit_complex_type(Qcomputation_style_or_none,
	    list_constant_11);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    list_constant_10 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qcomputation_style_or_none);
    string_constant_23 = STATIC_STRING("~NT ");
    string_constant_24 = 
	    STATIC_STRING("~NV must be one of the following types: ~a");
    computation_style_or_none_evaluation_setter_1 = 
	    STATIC_FUNCTION(computation_style_or_none_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qcomputation_style_or_none,
	    computation_style_or_none_evaluation_setter_1);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    computation_style_or_none_evaluation_getter_1 = 
	    STATIC_FUNCTION(computation_style_or_none_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qcomputation_style_or_none,
	    computation_style_or_none_evaluation_getter_1);
    Qreduce_annotation_with_expression = 
	    STATIC_SYMBOL("REDUCE-ANNOTATION-WITH-EXPRESSION",AB_package);
    SET_SYMBOL_FUNCTION(Qreduce_annotation_with_expression,
	    STATIC_FUNCTION(reduce_annotation_with_expression,NIL,FALSE,1,1));
    string_constant_60 = 
	    STATIC_STRING("1y1o83-Lny1o1m9k9l1m9k83Tvy1m9k83*Iy83*uy1n83BSymo9m1o83-Lny1o1m9k9l1m9k83Avy1m9k83*Iy83sgy1n83BSymo9n1o83-Lny1o1m9k9l1m9k83HHy1");
    string_constant_61 = 
	    STATIC_STRING("m9k83*Iy83*uy1n83BSymo9m1o83-Lny1o1m9k9l1m9k83bcy1m9k83*Iy83niy1n83BSymo9m1m83niy1m9k83*hy1m83niy1m9k83-cy1m83niy1m9k83-by1o83-L");
    string_constant_62 = 
	    STATIC_STRING("ny1o1m9k9l1m9k83biy1m9k83*Iy83*uy1n83BSymo9m1o83-Lny1o1m9k9l1m9k83-Ehy1m9k83*Iy83-Eiy1n83BSymo9m1m83-Eiy1m9k83-Vy1m83-Eiy1m9k83=");
    string_constant_63 = 
	    STATIC_STRING("Ay1m83-Eiy1m9k83C0y1o83-Lny1o1m9k9l1m9k83*4y1m9k9o83Sy1n83BSymo9m1o83-Lny1o1m9k9l1m9k83=sy1m9k9o83Sy1n83BSymo9m");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qreduce_annotation);
    push_optimized_constant(Qreduce_annotation_with_expression);
    push_optimized_constant(Qnum_eq);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_4(string_constant_60,
	    string_constant_61,string_constant_62,string_constant_63)));
    Qcell_format_annotation = STATIC_SYMBOL("CELL-FORMAT-ANNOTATION",
	    AB_package);
    Qsc = STATIC_SYMBOL(";",AB_package);
    add_grammar_rules_for_list(5,Qcell_format,Qcell_format_annotation,Qsc,
	    Nil,Qnone);
    Qreduce_noting_source_position = 
	    STATIC_SYMBOL("REDUCE-NOTING-SOURCE-POSITION",AB_package);
    SET_SYMBOL_FUNCTION(Qreduce_noting_source_position,
	    STATIC_FUNCTION(reduce_noting_source_position,NIL,FALSE,1,1));
    string_constant_64 = 
	    STATIC_STRING("1n1m83sgy83*uy1n83sgy1m83-cNy83pQy1n9klm1o83-cNy1p1m9l8344y1m9l83*ty1m9l9k1m9l83-rcy1m9l83=py1n83=Uy83-2y1l83-vJy9m");
    clear_optimized_constants();
    push_optimized_constant(Qthe);
    push_optimized_constant(Qquote);
    push_optimized_constant(Qreduce_noting_source_position);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_64));
    Qwrite_cell_format_from_slot = 
	    STATIC_SYMBOL("WRITE-CELL-FORMAT-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_cell_format_from_slot,
	    STATIC_FUNCTION(write_cell_format_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qcell_format,
	    SYMBOL_FUNCTION(Qwrite_cell_format_from_slot),Qslot_value_writer);
    Qcell = STATIC_SYMBOL("CELL",AB_package);
    Qcompile_cell_format_for_slot = 
	    STATIC_SYMBOL("COMPILE-CELL-FORMAT-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_cell_format_for_slot,
	    STATIC_FUNCTION(compile_cell_format_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qcell_format,
	    SYMBOL_FUNCTION(Qcompile_cell_format_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qcell_format,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_65 = STATIC_STRING("1m1m832vy1m9k83Zy1m832vy83B4y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_65));
    string_constant_25 = STATIC_STRING("none");
    Qcell_format_or_none = STATIC_SYMBOL("CELL-FORMAT-OR-NONE",AB_package);
    Qwrite_cell_format_or_none_from_slot = 
	    STATIC_SYMBOL("WRITE-CELL-FORMAT-OR-NONE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_cell_format_or_none_from_slot,
	    STATIC_FUNCTION(write_cell_format_or_none_from_slot,NIL,FALSE,
	    2,2));
    mutate_global_property(Qcell_format_or_none,
	    SYMBOL_FUNCTION(Qwrite_cell_format_or_none_from_slot),
	    Qslot_value_writer);
    Qcompile_cell_format_or_none_for_slot = 
	    STATIC_SYMBOL("COMPILE-CELL-FORMAT-OR-NONE-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_cell_format_or_none_for_slot,
	    STATIC_FUNCTION(compile_cell_format_or_none_for_slot,NIL,TRUE,
	    3,6));
    mutate_global_property(Qcell_format_or_none,
	    SYMBOL_FUNCTION(Qcompile_cell_format_or_none_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qcell_format_or_none,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    set_property_value_function(get_symbol_properties_function(Qcell_format_or_none),
	    Qtype_specification_simple_expansion,list_constant_108);
    list_constant_128 = STATIC_LIST((SI_Long)2L,Qnamed,Qcolor_or_metacolor);
    list_constant_129 = STATIC_CONS(list_constant_128,Qnil);
    list_constant_132 = STATIC_CONS(Qbackground_color,list_constant_129);
    list_constant_133 = STATIC_CONS(Qline_color,list_constant_129);
    list_constant_134 = STATIC_CONS(Qborder_color,list_constant_129);
    list_constant_135 = STATIC_CONS(Qtext_color,list_constant_129);
    list_constant_136 = STATIC_LIST((SI_Long)2L,Qtext_alignment,
	    list_constant_44);
    Qfont_name = STATIC_SYMBOL("FONT-NAME",AB_package);
    list_constant_130 = STATIC_LIST((SI_Long)2L,Qnamed,Qfont_name);
    list_constant_137 = STATIC_LIST((SI_Long)2L,Qtext_size,list_constant_130);
    list_constant_131 = STATIC_CONS(Qinteger,Qnil);
    list_constant_138 = STATIC_CONS(Qwidth,list_constant_131);
    list_constant_139 = STATIC_CONS(Qheight,list_constant_131);
    list_constant_140 = STATIC_LIST((SI_Long)8L,list_constant_132,
	    list_constant_133,list_constant_134,list_constant_135,
	    list_constant_136,list_constant_137,list_constant_138,
	    list_constant_139);
    list_constant_141 = STATIC_LIST((SI_Long)9L,Qab_or,Qbackground_color,
	    Qline_color,Qborder_color,Qtext_color,Qtext_alignment,
	    Qtext_size,Qwidth,Qheight);
    list_constant_142 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_140,list_constant_141);
    list_constant_15 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_12,
	    list_constant_142);
    define_type_specification_explicit_complex_type(Qcell_format_or_none,
	    list_constant_15);
    list_constant_14 = STATIC_LIST((SI_Long)2L,Qnamed,Qcell_format_or_none);
    cell_format_or_none_evaluation_setter_1 = 
	    STATIC_FUNCTION(cell_format_or_none_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qcell_format_or_none,
	    cell_format_or_none_evaluation_setter_1);
    cell_format_or_none_evaluation_getter_1 = 
	    STATIC_FUNCTION(cell_format_or_none_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qcell_format_or_none,
	    cell_format_or_none_evaluation_getter_1);
    Qreduce_to_bad_phrase = STATIC_SYMBOL("REDUCE-TO-BAD-PHRASE",AB_package);
    string_constant_66 = 
	    STATIC_STRING("1q1m83B3y1m9k83Zy1m83B3y83pQy1o83pQy83=pyl9l1o83pQy1n83=py1m9k83-Zy836hy09m1n83pQy1m83-J9y836hy1n83-TQylm1o83-J9y1m83=py1m9k83-Z");
    string_constant_67 = STATIC_STRING("yl9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qreduce_noting_source_position);
    push_optimized_constant(Qreduce_to_bad_phrase);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_66,
	    string_constant_67)));
    SET_SYMBOL_FUNCTION(Qreduce_to_bad_phrase,
	    STATIC_FUNCTION(reduce_to_bad_phrase,NIL,FALSE,1,1));
    Qsimple_cell_expression = STATIC_SYMBOL("SIMPLE-CELL-EXPRESSION",
	    AB_package);
    string_constant_68 = STATIC_STRING("COMPILED-CELL-EXPRESSION");
    if (Compiled_cell_expression == UNBOUND)
	Compiled_cell_expression = make_recursive_lock(2,Kname,
		string_constant_68);
    Qcompiled_cell_expression = STATIC_SYMBOL("COMPILED-CELL-EXPRESSION",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcompiled_cell_expression,
	    Compiled_cell_expression);
    list_constant_143 = STATIC_CONS(Qcomputation_style_description,
	    list_constant_53);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qcompiled_cell_expression,
	    Qparts,Nil,Qnil,Qnil,list_constant_143,Nil);
    mutate_global_property(Qcompiled_cell_expression,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    if (Current_compiled_cell_expression == UNBOUND)
	Current_compiled_cell_expression = Qsymbol_standing_in_for_unbound;
    Qincludes = STATIC_SYMBOL("INCLUDES",AB_package);
    list_constant_145 = STATIC_LIST((SI_Long)2L,Qincludes,
	    Qcomputation_style_description);
    list_constant_144 = STATIC_LIST((SI_Long)2L,
	    Qmay_provide_data_on_request,Qmay_provide_event_updates);
    list_constant_146 = STATIC_CONS(Qhidden_features,list_constant_144);
    list_constant_147 = STATIC_LIST((SI_Long)3L,list_constant_145,
	    list_constant_29,list_constant_146);
    def_part_type_1(Qcompiled_cell_expression,list_constant_143,
	    list_constant_147);
    def_part_feature_1(Qcompiled_cell_expression,Qsubparts,
	    list_constant_33,Qsubparts,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_subparts),
	    SYMBOL_FUNCTION(Qexit_part_feature_subparts),list_constant_34);
    def_part_feature_1(Qcompiled_cell_expression,Qsubpart_defaults,
	    list_constant_33,Qsubpart_defaults,Qnil,
	    SYMBOL_FUNCTION(Qenter_subpart_defaults),
	    SYMBOL_FUNCTION(Qexit_subpart_defaults),list_constant_37);
    def_part_feature_1(Qcompiled_cell_expression,Qsubpart_exceptions,
	    list_constant_33,Qsubpart_exceptions,Qnil,
	    SYMBOL_FUNCTION(Qenter_subpart_exceptions),
	    SYMBOL_FUNCTION(Qexit_subpart_exceptions),list_constant_40);
    SET_SYMBOL_VALUE_LOCATION(Qexpression_cell_index,Expression_cell_index);
    if (Expression_cell_index == UNBOUND)
	Expression_cell_index = Qsymbol_standing_in_for_unbound;
    Qenter_part_feature_expression_cell_index = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-EXPRESSION-CELL-INDEX",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_expression_cell_index,
	    STATIC_FUNCTION(enter_part_feature_expression_cell_index,NIL,
	    FALSE,1,1));
    Qexit_part_feature_expression_cell_index = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-EXPRESSION-CELL-INDEX",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_expression_cell_index,
	    STATIC_FUNCTION(exit_part_feature_expression_cell_index,NIL,
	    FALSE,0,0));
    list_constant_148 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qexpression_cell_index);
    def_part_feature_1(Qcompiled_cell_expression,Qexpression_cell_index,
	    Qexpression_cell_index,Qexpression_cell_index,Qt,
	    SYMBOL_FUNCTION(Qenter_part_feature_expression_cell_index),
	    SYMBOL_FUNCTION(Qexit_part_feature_expression_cell_index),
	    list_constant_148);
    if (Expression_source_text == UNBOUND)
	Expression_source_text = Qsymbol_standing_in_for_unbound;
    Qexpression_source_text = STATIC_SYMBOL("EXPRESSION-SOURCE-TEXT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qexpression_source_text,Expression_source_text);
    Qenter_part_feature_expression_source_text = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-EXPRESSION-SOURCE-TEXT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_expression_source_text,
	    STATIC_FUNCTION(enter_part_feature_expression_source_text,NIL,
	    FALSE,1,1));
    Qexit_part_feature_expression_source_text = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-EXPRESSION-SOURCE-TEXT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_expression_source_text,
	    STATIC_FUNCTION(exit_part_feature_expression_source_text,NIL,
	    FALSE,0,0));
    list_constant_149 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qexpression_source_text);
    def_part_feature_1(Qcompiled_cell_expression,Qexpression_source_text,
	    Qtext_string,Qexpression_source_text,Qt,
	    SYMBOL_FUNCTION(Qenter_part_feature_expression_source_text),
	    SYMBOL_FUNCTION(Qexit_part_feature_expression_source_text),
	    list_constant_149);
    Qcell_array_element = STATIC_SYMBOL("CELL-ARRAY-ELEMENT",AB_package);
    Qfeature_type_reclaimer_for_expression_cell_index = 
	    STATIC_SYMBOL("FEATURE-TYPE-RECLAIMER-FOR-EXPRESSION-CELL-INDEX",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qfeature_type_reclaimer_for_expression_cell_index,
	    STATIC_FUNCTION(feature_type_reclaimer_for_expression_cell_index,
	    NIL,FALSE,1,1));
    mutate_global_property(Qexpression_cell_index,
	    Qfeature_type_reclaimer_for_expression_cell_index,
	    Qpart_feature_type_reclaimer);
    Qfeature_type_reclaimer_for_cell_expression_and_text = 
	    STATIC_SYMBOL("FEATURE-TYPE-RECLAIMER-FOR-CELL-EXPRESSION-AND-TEXT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qfeature_type_reclaimer_for_cell_expression_and_text,
	    STATIC_FUNCTION(feature_type_reclaimer_for_cell_expression_and_text,
	    NIL,FALSE,1,1));
    mutate_global_property(Qcell_expression_and_text,
	    Qfeature_type_reclaimer_for_cell_expression_and_text,
	    Qpart_feature_type_reclaimer);
    Qexpression_with_computation_style = 
	    STATIC_SYMBOL("EXPRESSION-WITH-COMPUTATION-STYLE",AB_package);
    Qsource_position = STATIC_SYMBOL("SOURCE-POSITION",AB_package);
    Qunknown = STATIC_SYMBOL("UNKNOWN",AB_package);
    Qdatum = STATIC_SYMBOL("DATUM",AB_package);
    Qunknown_datum = STATIC_SYMBOL("UNKNOWN-DATUM",AB_package);
    list_constant_150 = STATIC_CONS(Qunknown_datum,Qnil);
    Qobsolete_datum = STATIC_SYMBOL("OBSOLETE-DATUM",AB_package);
    list_constant_151 = STATIC_CONS(Qobsolete_datum,Qnil);
    list_constant_16 = STATIC_LIST((SI_Long)4L,Qab_or,Qdatum,
	    list_constant_150,list_constant_151);
    Qcompile_cell_expression_parse_for_slot = 
	    STATIC_SYMBOL("COMPILE-CELL-EXPRESSION-PARSE-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_cell_expression_parse_for_slot,
	    STATIC_FUNCTION(compile_cell_expression_parse_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qcell_expression_parse,
	    SYMBOL_FUNCTION(Qcompile_cell_expression_parse_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qcell_expression_parse,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qmark = STATIC_SYMBOL("MARK",AB_package);
    Qg2_lambda = STATIC_SYMBOL("G2-LAMBDA",AB_package);
    list_constant_152 = STATIC_LIST_STAR((SI_Long)6L,
	    Qtime_out_when_requesting_data_seeking,Qnil,
	    Qmay_provide_data_on_request,Qnil,Qmay_provide_event_updates,
	    list_constant_28);
    list_constant_153 = STATIC_LIST_STAR((SI_Long)3L,
	    Qmay_request_data_seeking,Qnil,list_constant_152);
    list_constant_17 = STATIC_LIST_STAR((SI_Long)14L,
	    Qcomputation_style_description,Qscan_interval,Qnil,Qpriority,
	    FIX((SI_Long)2L),Qinitial_scan_wait_interval,FIX((SI_Long)2L),
	    Qupdate_only_when_shown,Qt,Qvalue_domain,Qinference_engine,
	    Qmay_request_event_updates,Qt,list_constant_153);
    list_constant_154 = STATIC_LIST_STAR((SI_Long)7L,Qvalue_domain,
	    Qinference_engine,Qmay_request_event_updates,Qnil,
	    Qmay_request_data_seeking,Qt,list_constant_152);
    list_constant_155 = STATIC_LIST_STAR((SI_Long)5L,
	    Qinitial_scan_wait_interval,FIX((SI_Long)0L),
	    Qupdate_only_when_shown,Qnil,list_constant_154);
    list_constant_18 = STATIC_LIST_STAR((SI_Long)6L,
	    Qcomputation_style_description,Qscan_interval,Qnil,Qpriority,
	    FIX((SI_Long)10L),list_constant_155);
    Qinter_g2_data_request_holder = 
	    STATIC_SYMBOL("INTER-G2-DATA-REQUEST-HOLDER",AB_package);
    list_constant_19 = STATIC_LIST_STAR((SI_Long)6L,
	    Qcomputation_style_description,Qscan_interval,Qnil,Qpriority,
	    FIX((SI_Long)6L),list_constant_155);
    list_constant_20 = STATIC_LIST_STAR((SI_Long)10L,
	    Qcomputation_style_description,Qscan_interval,FIX((SI_Long)5L),
	    Qpriority,FIX((SI_Long)2L),Qinitial_scan_wait_interval,
	    FIX((SI_Long)2L),Qupdate_only_when_shown,Qt,list_constant_154);
    list_constant_156 = STATIC_LIST_STAR((SI_Long)9L,
	    Qinitial_scan_wait_interval,FIX((SI_Long)2L),
	    Qupdate_only_when_shown,Qnil,Qvalue_domain,Qinference_engine,
	    Qmay_request_event_updates,Qnil,list_constant_153);
    list_constant_21 = STATIC_LIST_STAR((SI_Long)6L,
	    Qcomputation_style_description,Qscan_interval,Qnil,Qpriority,
	    FIX((SI_Long)10L),list_constant_156);
    list_constant_22 = STATIC_LIST_STAR((SI_Long)6L,
	    Qcomputation_style_description,Qpriority,FIX((SI_Long)2L),
	    Qscan_interval,Qnil,list_constant_156);
    Qdefault_evaluation_setting = 
	    STATIC_SYMBOL("DEFAULT-EVALUATION-SETTING",AB_package);
    list_constant_23 = STATIC_CONS(Qcomputation_style_description,Qnil);
    Qwrite_cell_expression_parse_from_slot = 
	    STATIC_SYMBOL("WRITE-CELL-EXPRESSION-PARSE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_cell_expression_parse_from_slot,
	    STATIC_FUNCTION(write_cell_expression_parse_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qcell_expression_parse,
	    SYMBOL_FUNCTION(Qwrite_cell_expression_parse_from_slot),
	    Qslot_value_writer);
    SET_SYMBOL_FUNCTION(Qcompile_computed_part_feature,
	    STATIC_FUNCTION(compile_computed_part_feature,NIL,FALSE,1,1));
    string_constant_26 = STATIC_STRING("symbolic");
    string_constant_27 = STATIC_STRING("given by the ~A expression~A");
}
