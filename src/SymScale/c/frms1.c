/* frms1.c
 * Input file:  frames1.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "frms1.h"


DEFINE_VARIABLE_WITH_SYMBOL(Available_frame_conses, Qavailable_frame_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_frame_conses_tail, Qavailable_frame_conses_tail);

Object Available_frame_conses_vector = UNBOUND;

Object Available_frame_conses_tail_vector = UNBOUND;

Object Frame_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Frame_cons_counter, Qframe_cons_counter);

/* OUTSTANDING-FRAME-CONSES */
Object outstanding_frame_conses()
{
    Object temp;

    x_note_fn_call(79,0);
    temp = FIXNUM_MINUS(Frame_cons_counter,length(Available_frame_conses));
    return VALUES_1(temp);
}

/* FRAME-CONS-MEMORY-USAGE */
Object frame_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(79,1);
    temp = FIXNUM_TIMES(Frame_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-FRAME-CONS-POOL */
Object replenish_frame_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(79,2);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qframe_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_frame_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_frame_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_frame_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_frame_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_frame_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Frame_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qframe;              /* frame */

/* FRAME-CONS-1 */
Object frame_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(79,3);
    new_cons = ISVREF(Available_frame_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_frame_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_frame_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_frame_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_frame_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qframe);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-FRAME-LIST-POOL */
Object replenish_frame_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(79,4);
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
    if (ISVREF(Available_frame_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_frame_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_frame_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_frame_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_frame_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qframe_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-FRAME-LIST-1 */
Object make_frame_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(79,5);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_frame_conses_vector,
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
	replenish_frame_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_frame_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qframe);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_frame_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_frame_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_frame_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_frame_conses_tail_vector;
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

/* FRAME-LIST-2 */
Object frame_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(79,6);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_frame_conses_vector,IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_frame_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_frame_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qframe);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_frame_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_frame_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_frame_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_frame_conses_tail_vector;
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

/* FRAME-LIST-3 */
Object frame_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(79,7);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_frame_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_frame_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_frame_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qframe);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_frame_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_frame_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_frame_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_frame_conses_tail_vector;
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

/* FRAME-LIST-4 */
Object frame_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(79,8);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_frame_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_frame_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_frame_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qframe);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_frame_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_frame_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_frame_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_frame_conses_tail_vector;
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

/* FRAME-LIST-TRACE-HOOK */
Object frame_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(79,9);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-FRAME-CONSES-1 */
Object copy_tree_using_frame_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(79,10);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_frame_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_frame_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_frame_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_frame_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_frame_cons_pool();
	temp_1 = copy_tree_using_frame_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qframe);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_frame_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_frame_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_frame_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_frame_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_frame_cons_pool();
	temp_1 = copy_tree_using_frame_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qframe);
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

/* COPY-LIST-USING-FRAME-CONSES-1 */
Object copy_list_using_frame_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(79,11);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_frame_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_frame_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_frame_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_frame_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_frame_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qframe);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_frame_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_frame_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_frame_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_frame_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_frame_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qframe);
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

/* RECLAIM-FRAME-CONS-1 */
Object reclaim_frame_cons_1(frame_cons)
    Object frame_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(79,12);
    inline_note_reclaim_cons(frame_cons,Qframe);
    if (ISVREF(Available_frame_conses_tail_vector,
		IFIX(Current_thread_index))) {
	temp = ISVREF(Available_frame_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = frame_cons;
	temp = Available_frame_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = frame_cons;
    }
    else {
	temp = Available_frame_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = frame_cons;
	temp = Available_frame_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = frame_cons;
    }
    M_CDR(frame_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-FRAME-LIST-1 */
Object reclaim_frame_list_1(frame_list)
    Object frame_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(79,13);
    if (frame_list) {
	last_1 = frame_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qframe);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qframe);
	if (ISVREF(Available_frame_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_frame_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = frame_list;
	    temp = Available_frame_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_frame_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = frame_list;
	    temp = Available_frame_conses_tail_vector;
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

/* RECLAIM-FRAME-LIST*-1 */
Object reclaim_frame_list_star_1(frame_list)
    Object frame_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(79,14);
    if (CONSP(frame_list)) {
	temp = last(frame_list,_);
	M_CDR(temp) = Nil;
	if (frame_list) {
	    last_1 = frame_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qframe);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qframe);
	    if (ISVREF(Available_frame_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_frame_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = frame_list;
		temp = Available_frame_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_frame_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = frame_list;
		temp = Available_frame_conses_tail_vector;
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

/* RECLAIM-FRAME-TREE-1 */
Object reclaim_frame_tree_1(tree)
    Object tree;
{
    Object e, e2, frame_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(79,15);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_frame_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		frame_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(frame_cons,Qframe);
		if (EQ(frame_cons,e))
		    goto end_1;
		else if ( !TRUEP(frame_cons))
		    goto end_1;
		else
		    frame_cons = CDR(frame_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_frame_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_frame_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_frame_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_frame_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_frame_conses_tail_vector;
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

/* DELETE-FRAME-ELEMENT-1 */
Object delete_frame_element_1(element,frame_list)
    Object element, frame_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(79,16);
    if (frame_list) {
	if (EQ(element,M_CAR(frame_list))) {
	    temp = CDR(frame_list);
	    inline_note_reclaim_cons(frame_list,Qframe);
	    if (ISVREF(Available_frame_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_frame_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = frame_list;
		temp_1 = Available_frame_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = frame_list;
	    }
	    else {
		temp_1 = Available_frame_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = frame_list;
		temp_1 = Available_frame_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = frame_list;
	    }
	    M_CDR(frame_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = frame_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qframe);
		if (ISVREF(Available_frame_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_frame_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_frame_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_frame_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_frame_conses_tail_vector;
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
	    temp = frame_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-FRAME-CONS-1 */
Object delete_frame_cons_1(frame_cons,frame_list)
    Object frame_cons, frame_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(79,17);
    if (EQ(frame_cons,frame_list))
	temp = CDR(frame_list);
    else {
	l_trailer_qm = Nil;
	l = frame_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,frame_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = frame_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_frame_cons_1(frame_cons);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_class_description_conses, Qavailable_class_description_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_class_description_conses_tail, Qavailable_class_description_conses_tail);

Object Available_class_description_conses_vector = UNBOUND;

Object Available_class_description_conses_tail_vector = UNBOUND;

Object Class_description_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Class_description_cons_counter, Qclass_description_cons_counter);

/* OUTSTANDING-CLASS-DESCRIPTION-CONSES */
Object outstanding_class_description_conses()
{
    Object temp;

    x_note_fn_call(79,18);
    temp = FIXNUM_MINUS(Class_description_cons_counter,
	    length(Available_class_description_conses));
    return VALUES_1(temp);
}

/* CLASS-DESCRIPTION-CONS-MEMORY-USAGE */
Object class_description_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(79,19);
    temp = FIXNUM_TIMES(Class_description_cons_counter,
	    ltimes(FIX((SI_Long)2L),Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-CLASS-DESCRIPTION-CONS-POOL */
Object replenish_class_description_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(79,20);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qclass_description_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_class_description_conses_vector,
	    IFIX(Current_thread_index))) {
	svref_arg_1 = Available_class_description_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_class_description_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_class_description_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_class_description_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Class_description_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qclass_description;  /* class-description */

/* CLASS-DESCRIPTION-CONS-1 */
Object class_description_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(79,21);
    new_cons = ISVREF(Available_class_description_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_class_description_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_class_description_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_class_description_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_class_description_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qclass_description);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-CLASS-DESCRIPTION-LIST-POOL */
Object replenish_class_description_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(79,22);
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
    if (ISVREF(Available_class_description_conses_vector,
	    IFIX(Current_thread_index))) {
	svref_arg_1 = Available_class_description_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_class_description_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_class_description_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_class_description_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qclass_description_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-CLASS-DESCRIPTION-LIST-1 */
Object make_class_description_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(79,23);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = 
		ISVREF(Available_class_description_conses_vector,
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
	replenish_class_description_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = 
		    ISVREF(Available_class_description_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qclass_description);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_class_description_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_class_description_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_class_description_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_class_description_conses_tail_vector;
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

/* CLASS-DESCRIPTION-LIST-2 */
Object class_description_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(79,24);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_class_description_conses_vector,
	    IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_class_description_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = 
		ISVREF(Available_class_description_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qclass_description);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_class_description_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_class_description_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_class_description_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_class_description_conses_tail_vector;
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

/* CLASS-DESCRIPTION-LIST-3 */
Object class_description_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(79,25);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_class_description_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_class_description_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = 
		ISVREF(Available_class_description_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qclass_description);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_class_description_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_class_description_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_class_description_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_class_description_conses_tail_vector;
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

/* CLASS-DESCRIPTION-LIST-4 */
Object class_description_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(79,26);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_class_description_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_class_description_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = 
		ISVREF(Available_class_description_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qclass_description);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_class_description_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_class_description_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_class_description_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_class_description_conses_tail_vector;
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

/* CLASS-DESCRIPTION-LIST-TRACE-HOOK */
Object class_description_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(79,27);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-CLASS-DESCRIPTION-CONSES-1 */
Object copy_tree_using_class_description_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(79,28);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_class_description_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_class_description_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_class_description_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_class_description_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_class_description_cons_pool();
	temp_1 = copy_tree_using_class_description_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qclass_description);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_class_description_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_class_description_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_class_description_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_class_description_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_class_description_cons_pool();
	temp_1 = 
		copy_tree_using_class_description_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qclass_description);
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

/* COPY-LIST-USING-CLASS-DESCRIPTION-CONSES-1 */
Object copy_list_using_class_description_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(79,29);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_class_description_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_class_description_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_class_description_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_class_description_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_class_description_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qclass_description);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_class_description_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_class_description_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_class_description_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_class_description_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_class_description_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qclass_description);
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

/* RECLAIM-CLASS-DESCRIPTION-CONS-1 */
Object reclaim_class_description_cons_1(class_description_cons)
    Object class_description_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(79,30);
    inline_note_reclaim_cons(class_description_cons,Qclass_description);
    if (ISVREF(Available_class_description_conses_tail_vector,
	    IFIX(Current_thread_index))) {
	temp = ISVREF(Available_class_description_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = class_description_cons;
	temp = Available_class_description_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = class_description_cons;
    }
    else {
	temp = Available_class_description_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = class_description_cons;
	temp = Available_class_description_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = class_description_cons;
    }
    M_CDR(class_description_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-CLASS-DESCRIPTION-LIST-1 */
Object reclaim_class_description_list_1(class_description_list)
    Object class_description_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(79,31);
    if (class_description_list) {
	last_1 = class_description_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qclass_description);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qclass_description);
	if (ISVREF(Available_class_description_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_class_description_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = class_description_list;
	    temp = Available_class_description_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_class_description_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = class_description_list;
	    temp = Available_class_description_conses_tail_vector;
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

/* RECLAIM-CLASS-DESCRIPTION-LIST*-1 */
Object reclaim_class_description_list_star_1(class_description_list)
    Object class_description_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(79,32);
    if (CONSP(class_description_list)) {
	temp = last(class_description_list,_);
	M_CDR(temp) = Nil;
	if (class_description_list) {
	    last_1 = class_description_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qclass_description);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qclass_description);
	    if (ISVREF(Available_class_description_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = 
			ISVREF(Available_class_description_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = class_description_list;
		temp = Available_class_description_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_class_description_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = class_description_list;
		temp = Available_class_description_conses_tail_vector;
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

/* RECLAIM-CLASS-DESCRIPTION-TREE-1 */
Object reclaim_class_description_tree_1(tree)
    Object tree;
{
    Object e, e2, class_description_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(79,33);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_class_description_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		class_description_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(class_description_cons,
			Qclass_description);
		if (EQ(class_description_cons,e))
		    goto end_1;
		else if ( !TRUEP(class_description_cons))
		    goto end_1;
		else
		    class_description_cons = CDR(class_description_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_class_description_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = 
			ISVREF(Available_class_description_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_class_description_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_class_description_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_class_description_conses_tail_vector;
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

/* DELETE-CLASS-DESCRIPTION-ELEMENT-1 */
Object delete_class_description_element_1(element,class_description_list)
    Object element, class_description_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(79,34);
    if (class_description_list) {
	if (EQ(element,M_CAR(class_description_list))) {
	    temp = CDR(class_description_list);
	    inline_note_reclaim_cons(class_description_list,
		    Qclass_description);
	    if (ISVREF(Available_class_description_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = 
			ISVREF(Available_class_description_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = class_description_list;
		temp_1 = Available_class_description_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = class_description_list;
	    }
	    else {
		temp_1 = Available_class_description_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = class_description_list;
		temp_1 = Available_class_description_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = class_description_list;
	    }
	    M_CDR(class_description_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = class_description_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qclass_description);
		if (ISVREF(Available_class_description_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = 
			    ISVREF(Available_class_description_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_class_description_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_class_description_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_class_description_conses_tail_vector;
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
	    temp = class_description_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-CLASS-DESCRIPTION-CONS-1 */
Object delete_class_description_cons_1(class_description_cons,
	    class_description_list)
    Object class_description_cons, class_description_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(79,35);
    if (EQ(class_description_cons,class_description_list))
	temp = CDR(class_description_list);
    else {
	l_trailer_qm = Nil;
	l = class_description_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,class_description_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = class_description_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_class_description_cons_1(class_description_cons);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(No_value, Qno_value);

Object Class_methods_prop = UNBOUND;

Object Classes_which_define_prop = UNBOUND;

Object Slot_name_assignment_gkbprop = UNBOUND;

Object Old_slot_name_assignment_gkbprop = UNBOUND;

Object Class_description_gkbprop = UNBOUND;

Object Old_class_description_kbprop = UNBOUND;

/* RECLAIM-CLASS-DESCRIPTION-LIST-FUNCTION */
Object reclaim_class_description_list_function(list_1)
    Object list_1;
{
    x_note_fn_call(79,36);
    return reclaim_class_description_list_1(list_1);
}

Object Direct_superior_classes_gkbprop = UNBOUND;

/* COPY-LIST-USING-CLASS-DESCRIPTION-CONSES-FUNCTION */
Object copy_list_using_class_description_conses_function(list_1)
    Object list_1;
{
    x_note_fn_call(79,37);
    return copy_list_using_class_description_conses_1(list_1);
}

Object Inferior_classes_gkbprop = UNBOUND;

Object Class_definition_gkbprop = UNBOUND;

Object Definition_state_gkbprop = UNBOUND;

static Object string_constant;     /* "~A::~A" */

/* MAKE-UNIQUE-SLOT-NAME-SYMBOL */
Object make_unique_slot_name_symbol(defining_class,pretty_slot_name)
    Object defining_class, pretty_slot_name;
{
    Object text_string, temp;

    x_note_fn_call(79,38);
    text_string = tformat_text_string(3,string_constant,defining_class,
	    pretty_slot_name);
    temp = intern_text_string(2,text_string,Keyword_package_1);
    return VALUES_1(temp);
}

/* DECOMPOSE-CLASS-QUALIFIED-SYMBOL-1 */
Object decompose_class_qualified_symbol_1(symbol)
    Object symbol;
{
    Object print_name, print_name_length, separator_position, class_string;
    Object name_string, ab_loop_iter_flag_, class_symbol, name_symbol;
    SI_Long name_string_length, index_1, ab_loop_bind_, aref_new_value, index1;
    SI_Long index2, ab_loop_bind__1;

    x_note_fn_call(79,39);
    print_name = symbol_name_text_string(symbol);
    print_name_length = text_string_length(print_name);
    separator_position = position_in_text_string(FIX((SI_Long)58L),print_name);
    class_string = obtain_simple_text_string(separator_position);
    name_string_length = IFIX(FIXNUM_MINUS(print_name_length,
	    separator_position)) - (SI_Long)2L;
    name_string = obtain_simple_text_string(FIX(name_string_length));
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(separator_position);
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    aref_new_value = UBYTE_16_ISAREF_1(print_name,index_1);
    UBYTE_16_ISASET_1(class_string,index_1,aref_new_value);
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    index1 = IFIX(separator_position) + (SI_Long)2L;
    ab_loop_bind_ = IFIX(print_name_length);
    index2 = (SI_Long)0L;
    ab_loop_bind__1 = name_string_length;
    ab_loop_iter_flag_ = T;
  next_loop_1:
    if (index1 >= ab_loop_bind_)
	goto end_loop_1;
    if ( !TRUEP(ab_loop_iter_flag_))
	index2 = index2 + (SI_Long)1L;
    if (index2 >= ab_loop_bind__1)
	goto end_loop_1;
    aref_new_value = UBYTE_16_ISAREF_1(print_name,index1);
    UBYTE_16_ISASET_1(name_string,index2,aref_new_value);
    ab_loop_iter_flag_ = Nil;
    index1 = index1 + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    class_symbol = intern_text_string(1,class_string);
    name_symbol = intern_text_string(1,name_string);
    return gensym_cons_1(class_symbol,name_symbol);
}

Object Decomposed_class_qualified_symbol_prop = UNBOUND;

static Object Qdecomposed_class_qualified_symbol;  /* decomposed-class-qualified-symbol */

/* DECOMPOSE-CLASS-QUALIFIED-SYMBOL */
Object decompose_class_qualified_symbol(symbol)
    Object symbol;
{
    Object info;

    x_note_fn_call(79,40);
    info = getfq_function_no_default(INLINE_SYMBOL_PLIST(symbol),
	    Qdecomposed_class_qualified_symbol);
    if (info);
    else
	info = mutate_global_property(symbol,
		decompose_class_qualified_symbol_1(symbol),
		Qdecomposed_class_qualified_symbol);
    return VALUES_2(CAR(info),CDR(info));
}

Object The_type_description_of_slot_description = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_slot_descriptions, Qchain_of_available_slot_descriptions);

DEFINE_VARIABLE_WITH_SYMBOL(Slot_description_count, Qslot_description_count);

Object Chain_of_available_slot_descriptions_vector = UNBOUND;

/* SLOT-DESCRIPTION-STRUCTURE-MEMORY-USAGE */
Object slot_description_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(79,41);
    temp = Slot_description_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)15L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-SLOT-DESCRIPTION-COUNT */
Object outstanding_slot_description_count()
{
    Object def_structure_slot_description_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(79,42);
    gensymed_symbol = IFIX(Slot_description_count);
    def_structure_slot_description_variable = 
	    Chain_of_available_slot_descriptions;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_slot_description_variable))
	goto end_loop;
    def_structure_slot_description_variable = 
	    ISVREF(def_structure_slot_description_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-SLOT-DESCRIPTION-1 */
Object reclaim_slot_description_1(slot_description)
    Object slot_description;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(79,43);
    inline_note_reclaim_cons(slot_description,Nil);
    structure_being_reclaimed = slot_description;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_class_description_tree_1(ISVREF(slot_description,(SI_Long)5L));
      SVREF(slot_description,FIX((SI_Long)5L)) = Nil;
      reclaim_class_description_tree_1(ISVREF(slot_description,(SI_Long)9L));
      SVREF(slot_description,FIX((SI_Long)9L)) = Nil;
      reclaim_if_evaluator_slot_info(ISVREF(slot_description,(SI_Long)10L));
      SVREF(slot_description,FIX((SI_Long)10L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_slot_descriptions_vector,
	    IFIX(Current_thread_index));
    SVREF(slot_description,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_slot_descriptions_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = slot_description;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-SLOT-DESCRIPTION */
Object reclaim_structure_for_slot_description(slot_description)
    Object slot_description;
{
    x_note_fn_call(79,44);
    return reclaim_slot_description_1(slot_description);
}

static Object Qg2_defstruct_structure_name_slot_description_g2_struct;  /* g2-defstruct-structure-name::slot-description-g2-struct */

/* MAKE-PERMANENT-SLOT-DESCRIPTION-STRUCTURE-INTERNAL */
Object make_permanent_slot_description_structure_internal()
{
    Object def_structure_slot_description_variable;
    Object defstruct_g2_slot_description_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(79,45);
    def_structure_slot_description_variable = Nil;
    atomic_incff_symval(Qslot_description_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_slot_description_variable = Nil;
	gensymed_symbol = (SI_Long)15L;
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
	defstruct_g2_slot_description_variable = the_array;
	SVREF(defstruct_g2_slot_description_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_slot_description_g2_struct;
	def_structure_slot_description_variable = 
		defstruct_g2_slot_description_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_slot_description_variable);
}

/* MAKE-SLOT-DESCRIPTION-INTERNAL-1 */
Object make_slot_description_internal_1()
{
    Object def_structure_slot_description_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(79,46);
    def_structure_slot_description_variable = 
	    ISVREF(Chain_of_available_slot_descriptions_vector,
	    IFIX(Current_thread_index));
    if (def_structure_slot_description_variable) {
	svref_arg_1 = Chain_of_available_slot_descriptions_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_slot_description_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_slot_description_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_slot_description_g2_struct;
    }
    else
	def_structure_slot_description_variable = 
		make_permanent_slot_description_structure_internal();
    inline_note_allocate_cons(def_structure_slot_description_variable,Nil);
    SVREF(def_structure_slot_description_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_slot_description_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_slot_description_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_slot_description_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_slot_description_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_slot_description_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_slot_description_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_slot_description_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_slot_description_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_slot_description_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_slot_description_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_slot_description_variable,FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_slot_description_variable,FIX((SI_Long)13L)) = Nil;
    SVREF(def_structure_slot_description_variable,FIX((SI_Long)14L)) = Nil;
    return VALUES_1(def_structure_slot_description_variable);
}

static Object Qlookup;             /* lookup */

/* RECLAIM-SLOT-HASH-LEAVES */
Object reclaim_slot_hash_leaves(slot_hash_binary_tree)
    Object slot_hash_binary_tree;
{
    Object less_than_branch_qm, greater_than_branch_qm, alist, alist_entry;
    Object ab_loop_list_, temp, svref_arg_2, last_1, next_qm, temp_1;

    x_note_fn_call(79,47);
    less_than_branch_qm = Nil;
    greater_than_branch_qm = Nil;
    alist = Nil;
  next_loop:
    if ( !TRUEP(slot_hash_binary_tree))
	goto end_loop;
    less_than_branch_qm = ISVREF(slot_hash_binary_tree,(SI_Long)1L);
    greater_than_branch_qm = ISVREF(slot_hash_binary_tree,(SI_Long)2L);
    alist = ISVREF(slot_hash_binary_tree,(SI_Long)3L);
    reclaim_binary_tree_element_1(slot_hash_binary_tree);
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
	reclaim_slot_hash_leaves(less_than_branch_qm);
	slot_hash_binary_tree = greater_than_branch_qm;
    }
    else {
	temp_1 = less_than_branch_qm;
	if (temp_1);
	else
	    temp_1 = greater_than_branch_qm;
	slot_hash_binary_tree = temp_1;
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* CLEAR-SLOT-HASH-TREE */
Object clear_slot_hash_tree(slot_hash_binary_tree)
    Object slot_hash_binary_tree;
{
    Object element_qm;

    x_note_fn_call(79,48);
    element_qm = CDR(slot_hash_binary_tree);
    if (element_qm) {
	reclaim_slot_hash_leaves(element_qm);
	M_CDR(slot_hash_binary_tree) = Nil;
    }
    return VALUES_1(slot_hash_binary_tree);
}

DEFINE_VARIABLE_WITH_SYMBOL(Any_cached_evaluator_slot_info_p, Qany_cached_evaluator_slot_info_p);

Object The_type_description_of_evaluator_slot_info = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_evaluator_slot_infos, Qchain_of_available_evaluator_slot_infos);

DEFINE_VARIABLE_WITH_SYMBOL(Evaluator_slot_info_count, Qevaluator_slot_info_count);

Object Chain_of_available_evaluator_slot_infos_vector = UNBOUND;

/* EVALUATOR-SLOT-INFO-STRUCTURE-MEMORY-USAGE */
Object evaluator_slot_info_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(79,49);
    temp = Evaluator_slot_info_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)8L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-EVALUATOR-SLOT-INFO-COUNT */
Object outstanding_evaluator_slot_info_count()
{
    Object def_structure_evaluator_slot_info_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(79,50);
    gensymed_symbol = IFIX(Evaluator_slot_info_count);
    def_structure_evaluator_slot_info_variable = 
	    Chain_of_available_evaluator_slot_infos;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_evaluator_slot_info_variable))
	goto end_loop;
    def_structure_evaluator_slot_info_variable = 
	    ISVREF(def_structure_evaluator_slot_info_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-EVALUATOR-SLOT-INFO-1 */
Object reclaim_evaluator_slot_info_1(evaluator_slot_info)
    Object evaluator_slot_info;
{
    Object temp, svref_arg_2;

    x_note_fn_call(79,51);
    inline_note_reclaim_cons(evaluator_slot_info,Nil);
    temp = ISVREF(Chain_of_available_evaluator_slot_infos_vector,
	    IFIX(Current_thread_index));
    SVREF(evaluator_slot_info,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_evaluator_slot_infos_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = evaluator_slot_info;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-EVALUATOR-SLOT-INFO */
Object reclaim_structure_for_evaluator_slot_info(evaluator_slot_info)
    Object evaluator_slot_info;
{
    x_note_fn_call(79,52);
    return reclaim_evaluator_slot_info_1(evaluator_slot_info);
}

static Object Qg2_defstruct_structure_name_evaluator_slot_info_g2_struct;  /* g2-defstruct-structure-name::evaluator-slot-info-g2-struct */

/* MAKE-PERMANENT-EVALUATOR-SLOT-INFO-STRUCTURE-INTERNAL */
Object make_permanent_evaluator_slot_info_structure_internal()
{
    Object def_structure_evaluator_slot_info_variable;
    Object defstruct_g2_evaluator_slot_info_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(79,53);
    def_structure_evaluator_slot_info_variable = Nil;
    atomic_incff_symval(Qevaluator_slot_info_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_evaluator_slot_info_variable = Nil;
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
	defstruct_g2_evaluator_slot_info_variable = the_array;
	SVREF(defstruct_g2_evaluator_slot_info_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_evaluator_slot_info_g2_struct;
	def_structure_evaluator_slot_info_variable = 
		defstruct_g2_evaluator_slot_info_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_evaluator_slot_info_variable);
}

/* MAKE-EVALUATOR-SLOT-INFO-1 */
Object make_evaluator_slot_info_1()
{
    Object def_structure_evaluator_slot_info_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(79,54);
    def_structure_evaluator_slot_info_variable = 
	    ISVREF(Chain_of_available_evaluator_slot_infos_vector,
	    IFIX(Current_thread_index));
    if (def_structure_evaluator_slot_info_variable) {
	svref_arg_1 = Chain_of_available_evaluator_slot_infos_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_evaluator_slot_info_variable,(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_evaluator_slot_info_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_evaluator_slot_info_g2_struct;
    }
    else
	def_structure_evaluator_slot_info_variable = 
		make_permanent_evaluator_slot_info_structure_internal();
    inline_note_allocate_cons(def_structure_evaluator_slot_info_variable,Nil);
    SVREF(def_structure_evaluator_slot_info_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_evaluator_slot_info_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_evaluator_slot_info_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_evaluator_slot_info_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_evaluator_slot_info_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_evaluator_slot_info_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_evaluator_slot_info_variable,FIX((SI_Long)7L)) = Nil;
    return VALUES_1(def_structure_evaluator_slot_info_variable);
}

/* RECLAIM-IF-EVALUATOR-SLOT-INFO */
Object reclaim_if_evaluator_slot_info(evaluator_slot_info_qm)
    Object evaluator_slot_info_qm;
{
    x_note_fn_call(79,55);
    if (evaluator_slot_info_qm)
	return reclaim_evaluator_slot_info_1(evaluator_slot_info_qm);
    else
	return VALUES_1(Nil);
}

Object The_type_description_of_class_description = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_class_descriptions, Qchain_of_available_class_descriptions);

DEFINE_VARIABLE_WITH_SYMBOL(Class_description_count, Qclass_description_count);

Object Chain_of_available_class_descriptions_vector = UNBOUND;

/* CLASS-DESCRIPTION-STRUCTURE-MEMORY-USAGE */
Object class_description_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(79,56);
    temp = Class_description_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)25L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-CLASS-DESCRIPTION-COUNT */
Object outstanding_class_description_count()
{
    Object def_structure_class_description_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(79,57);
    gensymed_symbol = IFIX(Class_description_count);
    def_structure_class_description_variable = 
	    Chain_of_available_class_descriptions;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_class_description_variable))
	goto end_loop;
    def_structure_class_description_variable = 
	    ISVREF(def_structure_class_description_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-CLASS-DESCRIPTION-1 */
Object reclaim_class_description_1(class_description)
    Object class_description;
{
    Object structure_being_reclaimed, slot_hash_binary_tree, element_qm, temp;
    Object svref_arg_2;
    Declare_special(1);

    x_note_fn_call(79,58);
    inline_note_reclaim_cons(class_description,Nil);
    structure_being_reclaimed = class_description;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_class_description_list_1(ISVREF(class_description,(SI_Long)2L));
      SVREF(class_description,FIX((SI_Long)2L)) = Nil;
      reclaim_class_description_list_1(ISVREF(class_description,(SI_Long)3L));
      SVREF(class_description,FIX((SI_Long)3L)) = Nil;
      reclaim_class_description_list_1(ISVREF(class_description,(SI_Long)6L));
      SVREF(class_description,FIX((SI_Long)6L)) = Nil;
      reclaim_class_description_list_1(ISVREF(class_description,(SI_Long)7L));
      SVREF(class_description,FIX((SI_Long)7L)) = Nil;
      reclaim_class_description_list_1(ISVREF(class_description,(SI_Long)8L));
      SVREF(class_description,FIX((SI_Long)8L)) = Nil;
      slot_hash_binary_tree = ISVREF(class_description,(SI_Long)9L);
      element_qm = M_CDR(slot_hash_binary_tree);
      if (element_qm)
	  reclaim_slot_hash_leaves(element_qm);
      inline_note_reclaim_cons(slot_hash_binary_tree,Qlookup);
      if (ISVREF(Available_lookup_conses_tail_vector,
	      IFIX(Current_thread_index))) {
	  temp = ISVREF(Available_lookup_conses_tail_vector,
		  IFIX(Current_thread_index));
	  M_CDR(temp) = slot_hash_binary_tree;
	  temp = Available_lookup_conses_tail_vector;
	  svref_arg_2 = Current_thread_index;
	  SVREF(temp,svref_arg_2) = slot_hash_binary_tree;
      }
      else {
	  temp = Available_lookup_conses_vector;
	  svref_arg_2 = Current_thread_index;
	  SVREF(temp,svref_arg_2) = slot_hash_binary_tree;
	  temp = Available_lookup_conses_tail_vector;
	  svref_arg_2 = Current_thread_index;
	  SVREF(temp,svref_arg_2) = slot_hash_binary_tree;
      }
      M_CDR(slot_hash_binary_tree) = Nil;
      SVREF(class_description,FIX((SI_Long)9L)) = Nil;
      reclaim_class_description_tree_1(ISVREF(class_description,(SI_Long)12L));
      SVREF(class_description,FIX((SI_Long)12L)) = Nil;
      reclaim_byte_vector(ISVREF(class_description,(SI_Long)19L));
      SVREF(class_description,FIX((SI_Long)19L)) = Nil;
      reclaim_class_export_information_if_any(ISVREF(class_description,
	      (SI_Long)21L));
      SVREF(class_description,FIX((SI_Long)21L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_class_descriptions_vector,
	    IFIX(Current_thread_index));
    SVREF(class_description,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_class_descriptions_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = class_description;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-CLASS-DESCRIPTION */
Object reclaim_structure_for_class_description(class_description)
    Object class_description;
{
    x_note_fn_call(79,59);
    return reclaim_class_description_1(class_description);
}

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* MAKE-PERMANENT-CLASS-DESCRIPTION-STRUCTURE-INTERNAL */
Object make_permanent_class_description_structure_internal()
{
    Object def_structure_class_description_variable;
    Object defstruct_g2_class_description_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(79,60);
    def_structure_class_description_variable = Nil;
    atomic_incff_symval(Qclass_description_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_class_description_variable = Nil;
	gensymed_symbol = (SI_Long)25L;
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
	defstruct_g2_class_description_variable = the_array;
	SVREF(defstruct_g2_class_description_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_class_description_g2_struct;
	def_structure_class_description_variable = 
		defstruct_g2_class_description_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_class_description_variable);
}

/* MAKE-CLASS-DESCRIPTION-INTERNAL-1 */
Object make_class_description_internal_1()
{
    Object def_structure_class_description_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(79,61);
    def_structure_class_description_variable = 
	    ISVREF(Chain_of_available_class_descriptions_vector,
	    IFIX(Current_thread_index));
    if (def_structure_class_description_variable) {
	svref_arg_1 = Chain_of_available_class_descriptions_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_class_description_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_class_description_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_class_description_g2_struct;
    }
    else
	def_structure_class_description_variable = 
		make_permanent_class_description_structure_internal();
    inline_note_allocate_cons(def_structure_class_description_variable,Nil);
    SVREF(def_structure_class_description_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_class_description_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_class_description_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_class_description_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_class_description_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_class_description_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_class_description_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_class_description_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_class_description_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_class_description_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_class_description_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_class_description_variable,FIX((SI_Long)12L)) = Nil;
    ISVREF(def_structure_class_description_variable,(SI_Long)13L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_class_description_variable,FIX((SI_Long)14L)) = Nil;
    ISVREF(def_structure_class_description_variable,(SI_Long)15L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_class_description_variable,FIX((SI_Long)16L)) = Nil;
    SVREF(def_structure_class_description_variable,FIX((SI_Long)17L)) = Nil;
    SVREF(def_structure_class_description_variable,FIX((SI_Long)18L)) = Nil;
    SVREF(def_structure_class_description_variable,FIX((SI_Long)19L)) = Nil;
    SVREF(def_structure_class_description_variable,FIX((SI_Long)20L)) = Nil;
    SVREF(def_structure_class_description_variable,FIX((SI_Long)21L)) = Nil;
    SVREF(def_structure_class_description_variable,FIX((SI_Long)22L)) = Nil;
    SVREF(def_structure_class_description_variable,FIX((SI_Long)23L)) = Nil;
    SVREF(def_structure_class_description_variable,FIX((SI_Long)24L)) = Nil;
    return VALUES_1(def_structure_class_description_variable);
}

/* CLASS-INHERITANCE-PATH-FUNCTION */
Object class_inheritance_path_function(class_description,
	    class_inheritance_path)
    Object class_description, class_inheritance_path;
{
    x_note_fn_call(79,62);
    return VALUES_1(SVREF(class_description,FIX((SI_Long)2L)) = 
	    class_inheritance_path);
}

/* CLASS-FEATURES-FUNCTION */
Object class_features_function(class_description,class_features)
    Object class_description, class_features;
{
    x_note_fn_call(79,63);
    return VALUES_1(SVREF(class_description,FIX((SI_Long)12L)) = 
	    class_features);
}

/* SLOT-DESCRIPTIONS-FUNCTION */
Object slot_descriptions_function(class_description,slot_descriptions)
    Object class_description, slot_descriptions;
{
    x_note_fn_call(79,64);
    return VALUES_1(SVREF(class_description,FIX((SI_Long)6L)) = 
	    slot_descriptions);
}

/* MAKE-CLASS-DESCRIPTION */
Object make_class_description(class_name_of_class_description,
	    class_inheritance_path,class_vector_length,class_features,
	    slot_descriptions,class_is_subclass_of_item_qm,
	    class_user_vector_length,slots_local_to_class,
	    inherited_slots_this_class_overrides,
	    slot_descriptions_hash_table,full_hash_table_class,
	    class_bit_number,class_bit_vector,
	    method_table_of_class_description,system_defined_class_p)
    Object class_name_of_class_description, class_inheritance_path;
    Object class_vector_length, class_features, slot_descriptions;
    Object class_is_subclass_of_item_qm, class_user_vector_length;
    Object slots_local_to_class, inherited_slots_this_class_overrides;
    Object slot_descriptions_hash_table, full_hash_table_class;
    Object class_bit_number, class_bit_vector;
    Object method_table_of_class_description, system_defined_class_p;
{
    Object class_description;

    x_note_fn_call(79,65);
    class_description = make_class_description_internal_1();
    SVREF(class_description,FIX((SI_Long)1L)) = 
	    class_name_of_class_description;
    SVREF(class_description,FIX((SI_Long)2L)) = class_inheritance_path;
    SVREF(class_description,FIX((SI_Long)14L)) = class_vector_length;
    SVREF(class_description,FIX((SI_Long)12L)) = class_features;
    SVREF(class_description,FIX((SI_Long)6L)) = slot_descriptions;
    SVREF(class_description,FIX((SI_Long)16L)) = class_is_subclass_of_item_qm;
    SVREF(class_description,FIX((SI_Long)15L)) = class_user_vector_length;
    SVREF(class_description,FIX((SI_Long)7L)) = slots_local_to_class;
    SVREF(class_description,FIX((SI_Long)8L)) = 
	    inherited_slots_this_class_overrides;
    SVREF(class_description,FIX((SI_Long)9L)) = slot_descriptions_hash_table;
    SVREF(class_description,FIX((SI_Long)17L)) = full_hash_table_class;
    SVREF(class_description,FIX((SI_Long)18L)) = class_bit_number;
    SVREF(class_description,FIX((SI_Long)19L)) = class_bit_vector;
    SVREF(class_description,FIX((SI_Long)11L)) = 
	    method_table_of_class_description;
    SVREF(class_description,FIX((SI_Long)20L)) = system_defined_class_p;
    return VALUES_1(class_description);
}

Object Class_description_variable_alist = UNBOUND;

/* ADD-CLASS-TO-CLASS-DESCRIPTION-VARIABLE-ALIST */
Object add_class_to_class_description_variable_alist(class_1,variable_name)
    Object class_1, variable_name;
{
    Object push_arg, class_description_variable_alist_new_value;

    x_note_fn_call(79,66);
    if ( !TRUEP(assq_function(class_1,Class_description_variable_alist))) {
	push_arg = CONS(class_1,variable_name);
	class_description_variable_alist_new_value = CONS(push_arg,
		Class_description_variable_alist);
	Class_description_variable_alist = 
		class_description_variable_alist_new_value;
	return VALUES_1(Class_description_variable_alist);
    }
    else
	return VALUES_1(Nil);
}

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

/* CLASSP-FUNCTION */
Object classp_function(x)
    Object x;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(79,67);
    if (SYMBOLP(x)) {
	skip_list = CDR(Symbol_properties_table);
	key_value = x;
	key_hash_value = SXHASH_SYMBOL_1(x) & IFIX(Most_positive_fixnum);
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
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = x;
	    temp = Symbol_properties_table;
	    temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		    IFIX(Most_positive_fixnum));
	    tail = 
		    make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
		    Nil);
	    head = 
		    make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
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
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_lookup_cons_pool();
	    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
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
		gensymed_symbol_2 = new_cons;
	    }
	    else
		gensymed_symbol_2 = Nil;
	    if ( !TRUEP(gensymed_symbol_2))
		gensymed_symbol_2 = replenish_lookup_cons_pool();
	    M_CAR(gensymed_symbol_2) = head;
	    M_CDR(gensymed_symbol_2) = tail;
	    inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
	    M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
	    inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
	    gensymed_symbol = set_skip_list_entry(temp,FIX((SI_Long)31L),
		    Qeq,Nil,T,gensymed_symbol,temp_1,gensymed_symbol_1);
	}
	global_properties = gensymed_symbol;
	skip_list = CDR(global_properties);
	key_value = Current_kb_specific_property_list_property_name;
	key_hash_value = 
		SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		& IFIX(Most_positive_fixnum);
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
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_4:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_5:
	if ( !TRUEP(marked))
	    goto end_loop_4;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_5;
      end_loop_4:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_2;
	goto next_loop_4;
      end_loop_5:
      end_2:
	level = level - (SI_Long)1L;
	goto next_loop_3;
      end_loop_3:;
	kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		(EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if (kb_properties);
	else
	    kb_properties = Nil;
	if (kb_properties) {
	    skip_list = CDR(kb_properties);
	    key_value = Class_description_gkbprop;
	    key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_6:
	    if (level < ab_loop_bind_)
		goto end_loop_6;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_7:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_8:
	    if ( !TRUEP(marked))
		goto end_loop_7;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_8;
	  end_loop_7:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_3;
	    goto next_loop_7;
	  end_loop_8:
	  end_3:
	    level = level - (SI_Long)1L;
	    goto next_loop_6;
	  end_loop_6:;
	    kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (kb_specific_value);
	    else
		kb_specific_value = No_specific_property_value;
	}
	else
	    kb_specific_value = No_specific_property_value;
	if ( !EQ(kb_specific_value,No_specific_property_value))
	    resulting_value = kb_specific_value;
	else {
	    skip_list = CDR(global_properties);
	    key_value = Class_description_gkbprop;
	    key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_9:
	    if (level < ab_loop_bind_)
		goto end_loop_9;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_10:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_11:
	    if ( !TRUEP(marked))
		goto end_loop_10;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_11;
	  end_loop_10:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_4;
	    goto next_loop_10;
	  end_loop_11:
	  end_4:
	    level = level - (SI_Long)1L;
	    goto next_loop_9;
	  end_loop_9:;
	    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (resulting_value);
	    else
		resulting_value = Nil;
	}
	temp_1 = resulting_value;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* CLASS-DESCRIPTION-SUBCLASS-OF-CLASS-DESCRIPTION-P-FUNCTION */
Object class_description_subclass_of_class_description_p_function(sub_class_description,
	    superior_class_description)
    Object sub_class_description, superior_class_description;
{
    Object sub_class_bit_vector, temp;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(79,68);
    sub_class_bit_vector = ISVREF(sub_class_description,(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(superior_class_description,
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
	temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* SUB-POTENTIAL-CLASS-P */
Object sub_potential_class_p(potential_class1,potential_class2)
    Object potential_class1, potential_class2;
{
    Object temp, direct_superior, ab_loop_list_, ab_loop_it_;

    x_note_fn_call(79,69);
    temp = EQ(potential_class1,potential_class2) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else {
	direct_superior = Nil;
	ab_loop_list_ = 
		lookup_global_or_kb_specific_property_value(potential_class1,
		Direct_superior_classes_gkbprop);
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	direct_superior = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_it_ = EQ(direct_superior,potential_class2) ? T : Nil;
	if (ab_loop_it_)
	    return VALUES_1(ab_loop_it_);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

/* SUBCLASSP-FUNCTION */
Object subclassp_function(symbol,class_1)
    Object symbol, class_1;
{
    Object class_description_qm;

    x_note_fn_call(79,70);
    class_description_qm = 
	    lookup_global_or_kb_specific_property_value(symbol,
	    Class_description_gkbprop);
    if (class_description_qm)
	return memq_function(class_1,ISVREF(class_description_qm,(SI_Long)2L));
    else
	return VALUES_1(Nil);
}

/* THING-IS-ITEM-P */
Object thing_is_item_p(thing)
    Object thing;
{
    Object class_description_qm, temp;

    x_note_fn_call(79,71);
    if (SIMPLE_VECTOR_P(thing) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) > 
	    (SI_Long)2L) {
	class_description_qm = ISVREF(thing,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(class_description_qm) && 
		EQ(ISVREF(class_description_qm,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 ISVREF(class_description_qm,(SI_Long)16L) : Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

/* OF-CLASS-P-FUNCTION */
Object of_class_p_function(x,class_1)
    Object x, class_1;
{
    Object x2, gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector, temp;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;

    x_note_fn_call(79,72);
    if (SIMPLE_VECTOR_P(x) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(x,(SI_Long)1L),
		Qavailable_frame_vector)) {
	x2 = ISVREF(x,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	gensymed_symbol_1 = 
		lookup_global_or_kb_specific_property_value(class_1,
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
		temp = (SI_Long)0L < gensymed_symbol_2 ? T : Nil;
	    }
	    else
		temp = Nil;
	}
	else
	    temp = Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Loading_kb_p, Qloading_kb_p);

static Object Kfuncall;            /* :funcall */

/* SLOT-INIT-FORM-NEEDS-EVALUATION? */
Object slot_init_form_needs_evaluation_qm(slot_init_form)
    Object slot_init_form;
{
    x_note_fn_call(79,73);
    if (CONSP(slot_init_form) && EQ(M_CAR(slot_init_form),Kfuncall))
	return VALUES_1( !TRUEP(Loading_kb_p) ? T : Nil);
    else
	return VALUES_1(Nil);
}

Object Slot_category_prop = UNBOUND;

Object Authorized_system_slots = UNBOUND;

/* UNAUTHORIZED-SYSTEM-SLOT-P */
Object unauthorized_system_slot_p(symbol)
    Object symbol;
{
    x_note_fn_call(79,74);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Class_is_undergoing_inheritance_change_qm, Qclass_is_undergoing_inheritance_change_qm);

/* UNIQUE-SLOT-NAME-EQ */
Object unique_slot_name_eq(x,slot_description)
    Object x, slot_description;
{
    x_note_fn_call(79,75);
    return VALUES_1(EQ(x,ISVREF(slot_description,(SI_Long)1L)) ? T : Nil);
}

/* GET-SLOT-DESCRIPTION-OF-CLASS-DESCRIPTION-FUNCTION */
Object get_slot_description_of_class_description_function(slot_name,
	    class_description,qualifying_class_qm)
    Object slot_name, class_description, qualifying_class_qm;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons, temp_2;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, qualifying_class_description_qm;
    Object qualifying_class_full_hash_table_class, path_class_description;
    Object existing_class_description_path_arg, class_description_arg, class_1;
    Object ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object class_name, slot_description_qm, unique_slot_name_key_qm;
    Object slot_description_to_return_qm, gathered_slot_descriptions_qm;
    Object full_hash_table_class, last_1, next_qm, unique_name;
    Object gathered_slot_description, gathered_slot_description_qm;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long gensymed_symbol_3, gensymed_symbol_4;
    Object result;

    x_note_fn_call(79,76);
    if ( !TRUEP(class_description))
	return VALUES_1(Nil);
    if (Class_is_undergoing_inheritance_change_qm)
	return get_slot_description(3,slot_name,ISVREF(class_description,
		(SI_Long)6L),qualifying_class_qm);
    if (qualifying_class_qm) {
	skip_list = CDR(Symbol_properties_table);
	key_value = qualifying_class_qm;
	key_hash_value = SXHASH_SYMBOL_1(qualifying_class_qm) & 
		IFIX(Most_positive_fixnum);
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
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = qualifying_class_qm;
	    temp = Symbol_properties_table;
	    temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		    IFIX(Most_positive_fixnum));
	    tail = 
		    make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
		    Nil);
	    head = 
		    make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
		    tail);
	    new_cons = ISVREF(Available_lookup_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp_2 = Available_lookup_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp_2,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp_2 = Available_lookup_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = Nil;
		}
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_lookup_cons_pool();
	    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
	    new_cons = ISVREF(Available_lookup_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp_2 = Available_lookup_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp_2,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp_2 = Available_lookup_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = Nil;
		}
		gensymed_symbol_2 = new_cons;
	    }
	    else
		gensymed_symbol_2 = Nil;
	    if ( !TRUEP(gensymed_symbol_2))
		gensymed_symbol_2 = replenish_lookup_cons_pool();
	    M_CAR(gensymed_symbol_2) = head;
	    M_CDR(gensymed_symbol_2) = tail;
	    inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
	    M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
	    inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
	    gensymed_symbol = set_skip_list_entry(temp,FIX((SI_Long)31L),
		    Qeq,Nil,T,gensymed_symbol,temp_1,gensymed_symbol_1);
	}
	global_properties = gensymed_symbol;
	skip_list = CDR(global_properties);
	key_value = Current_kb_specific_property_list_property_name;
	key_hash_value = 
		SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		& IFIX(Most_positive_fixnum);
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
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_4:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_5:
	if ( !TRUEP(marked))
	    goto end_loop_4;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_5;
      end_loop_4:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_2;
	goto next_loop_4;
      end_loop_5:
      end_2:
	level = level - (SI_Long)1L;
	goto next_loop_3;
      end_loop_3:;
	kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		(EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if (kb_properties);
	else
	    kb_properties = Nil;
	if (kb_properties) {
	    skip_list = CDR(kb_properties);
	    key_value = Class_description_gkbprop;
	    key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_6:
	    if (level < ab_loop_bind_)
		goto end_loop_6;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_7:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_8:
	    if ( !TRUEP(marked))
		goto end_loop_7;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_8;
	  end_loop_7:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_3;
	    goto next_loop_7;
	  end_loop_8:
	  end_3:
	    level = level - (SI_Long)1L;
	    goto next_loop_6;
	  end_loop_6:;
	    kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (kb_specific_value);
	    else
		kb_specific_value = No_specific_property_value;
	}
	else
	    kb_specific_value = No_specific_property_value;
	if ( !EQ(kb_specific_value,No_specific_property_value))
	    resulting_value = kb_specific_value;
	else {
	    skip_list = CDR(global_properties);
	    key_value = Class_description_gkbprop;
	    key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_9:
	    if (level < ab_loop_bind_)
		goto end_loop_9;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_10:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_11:
	    if ( !TRUEP(marked))
		goto end_loop_10;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_11;
	  end_loop_10:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_4;
	    goto next_loop_10;
	  end_loop_11:
	  end_4:
	    level = level - (SI_Long)1L;
	    goto next_loop_9;
	  end_loop_9:;
	    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (resulting_value);
	    else
		resulting_value = Nil;
	}
	qualifying_class_description_qm = resulting_value;
	if (qualifying_class_description_qm) {
	    qualifying_class_full_hash_table_class = 
		    ISVREF(qualifying_class_description_qm,(SI_Long)17L);
	    path_class_description = Nil;
	    existing_class_description_path_arg = 
		    ISVREF(qualifying_class_description_qm,(SI_Long)3L);
	    class_description_arg = qualifying_class_description_qm;
	    if ( !TRUEP(existing_class_description_path_arg)) {
		class_1 = Nil;
		ab_loop_list_ = ISVREF(class_description_arg,(SI_Long)2L);
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ab_loopvar__2 = Nil;
	      next_loop_12:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_12;
		class_1 = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		ab_loopvar__2 = 
			class_description_cons_1(lookup_global_or_kb_specific_property_value(class_1,
			Class_description_gkbprop),Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
		goto next_loop_12;
	      end_loop_12:
		goto end_5;
		ab_loopvar_ = Qnil;
	      end_5:;
		ab_loop_list_ = SVREF(class_description_arg,
			FIX((SI_Long)3L)) = ab_loopvar_;
	    }
	    else
		ab_loop_list_ = existing_class_description_path_arg;
	    class_name = Nil;
	    slot_description_qm = Nil;
	  next_loop_13:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_13;
	    path_class_description = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    class_name = ISVREF(path_class_description,(SI_Long)1L);
	    temp_1 = ISVREF(path_class_description,(SI_Long)9L);
	    gensymed_symbol = CDR(temp_1);
	    gensymed_symbol_1 = slot_name;
	    gensymed_symbol_3 = SXHASH_SYMBOL_1(slot_name) & 
		    IFIX(Most_positive_fixnum);
	    gensymed_symbol_4 = (SI_Long)0L;
	  next_loop_14:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_14;
	    gensymed_symbol_4 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_3 < gensymed_symbol_4)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_3 > gensymed_symbol_4)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_2 = Nil;
	      next_loop_15:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_15;
		gensymed_symbol_2 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_2)) {
		    slot_description_qm = M_CDR(M_CAR(gensymed_symbol));
		    goto end_6;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_15;
	      end_loop_15:
		slot_description_qm = Qnil;
	      end_6:;
		goto end_7;
	    }
	    goto next_loop_14;
	  end_loop_14:
	    slot_description_qm = Qnil;
	  end_7:;
	    if (EQ(class_name,qualifying_class_full_hash_table_class)) {
		unique_slot_name_key_qm = slot_description_qm ? 
			ISVREF(slot_description_qm,(SI_Long)1L) : Nil;
		goto end_8;
	    }
	    else if (slot_description_qm && (EQ(ISVREF(slot_description_qm,
		    (SI_Long)3L),class_name) ||  
		    !TRUEP(ISVREF(slot_description_qm,(SI_Long)8L)) || 
		    EQ(slot_name,ISVREF(slot_description_qm,(SI_Long)1L)))) {
		unique_slot_name_key_qm = ISVREF(slot_description_qm,
			(SI_Long)1L);
		goto end_8;
	    }
	    goto next_loop_13;
	  end_loop_13:
	    unique_slot_name_key_qm = Qnil;
	  end_8:;
	    if (unique_slot_name_key_qm) {
		path_class_description = Nil;
		existing_class_description_path_arg = 
			ISVREF(class_description,(SI_Long)3L);
		class_description_arg = class_description;
		if ( !TRUEP(existing_class_description_path_arg)) {
		    class_1 = Nil;
		    ab_loop_list_ = ISVREF(class_description_arg,(SI_Long)2L);
		    ab_loopvar_ = Nil;
		    ab_loopvar__1 = Nil;
		    ab_loopvar__2 = Nil;
		  next_loop_16:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop_16;
		    class_1 = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    ab_loopvar__2 = 
			    class_description_cons_1(lookup_global_or_kb_specific_property_value(class_1,
			    Class_description_gkbprop),Nil);
		    if (ab_loopvar__1)
			M_CDR(ab_loopvar__1) = ab_loopvar__2;
		    else
			ab_loopvar_ = ab_loopvar__2;
		    ab_loopvar__1 = ab_loopvar__2;
		    goto next_loop_16;
		  end_loop_16:
		    goto end_9;
		    ab_loopvar_ = Qnil;
		  end_9:;
		    ab_loop_list_ = SVREF(class_description_arg,
			    FIX((SI_Long)3L)) = ab_loopvar_;
		}
		else
		    ab_loop_list_ = existing_class_description_path_arg;
		slot_description_qm = Nil;
	      next_loop_17:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_17;
		path_class_description = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		temp_1 = ISVREF(path_class_description,(SI_Long)9L);
		gensymed_symbol = CDR(temp_1);
		gensymed_symbol_1 = unique_slot_name_key_qm;
		gensymed_symbol_3 = 
			SXHASH_SYMBOL_1(unique_slot_name_key_qm) & 
			IFIX(Most_positive_fixnum);
		gensymed_symbol_4 = (SI_Long)0L;
	      next_loop_18:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_18;
		gensymed_symbol_4 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_3 < gensymed_symbol_4)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_3 > gensymed_symbol_4)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_2 = Nil;
		  next_loop_19:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_19;
		    gensymed_symbol_2 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_2)) {
			slot_description_qm = M_CDR(M_CAR(gensymed_symbol));
			goto end_10;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_19;
		  end_loop_19:
		    slot_description_qm = Qnil;
		  end_10:;
		    goto end_11;
		}
		goto next_loop_18;
	      end_loop_18:
		slot_description_qm = Qnil;
	      end_11:;
		if (slot_description_qm) {
		    slot_description_to_return_qm = slot_description_qm;
		    goto end_12;
		}
		goto next_loop_17;
	      end_loop_17:
		slot_description_to_return_qm = Qnil;
	      end_12:;
	    }
	    else
		slot_description_to_return_qm = Nil;
	    if (slot_description_to_return_qm)
		return VALUES_1(slot_description_to_return_qm);
	    else
		temp_1 = Nil;
	}
	else
	    temp_1 = Nil;
    }
    else {
	gathered_slot_descriptions_qm = Nil;
	full_hash_table_class = ISVREF(class_description,(SI_Long)17L);
	path_class_description = Nil;
	existing_class_description_path_arg = ISVREF(class_description,
		(SI_Long)3L);
	class_description_arg = class_description;
	if ( !TRUEP(existing_class_description_path_arg)) {
	    class_1 = Nil;
	    ab_loop_list_ = ISVREF(class_description_arg,(SI_Long)2L);
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop_20:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_20;
	    class_1 = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loopvar__2 = 
		    class_description_cons_1(lookup_global_or_kb_specific_property_value(class_1,
		    Class_description_gkbprop),Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop_20;
	  end_loop_20:
	    goto end_13;
	    ab_loopvar_ = Qnil;
	  end_13:;
	    ab_loop_list_ = SVREF(class_description_arg,FIX((SI_Long)3L)) 
		    = ab_loopvar_;
	}
	else
	    ab_loop_list_ = existing_class_description_path_arg;
	class_name = Nil;
	slot_description_qm = Nil;
      next_loop_21:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_21;
	path_class_description = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	class_name = ISVREF(path_class_description,(SI_Long)1L);
	temp_1 = ISVREF(path_class_description,(SI_Long)9L);
	gensymed_symbol = CDR(temp_1);
	gensymed_symbol_1 = slot_name;
	gensymed_symbol_3 = SXHASH_SYMBOL_1(slot_name) & 
		IFIX(Most_positive_fixnum);
	gensymed_symbol_4 = (SI_Long)0L;
      next_loop_22:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_22;
	gensymed_symbol_4 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	if (gensymed_symbol_3 < gensymed_symbol_4)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	else if (gensymed_symbol_3 > gensymed_symbol_4)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	else {
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	    gensymed_symbol_2 = Nil;
	  next_loop_23:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_23;
	    gensymed_symbol_2 = M_CAR(M_CAR(gensymed_symbol));
	    if (EQ(gensymed_symbol_1,gensymed_symbol_2)) {
		slot_description_qm = M_CDR(M_CAR(gensymed_symbol));
		goto end_14;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_23;
	  end_loop_23:
	    slot_description_qm = Qnil;
	  end_14:;
	    goto end_15;
	}
	goto next_loop_22;
      end_loop_22:
	slot_description_qm = Qnil;
      end_15:;
	if (EQ(class_name,full_hash_table_class) &&  
		!TRUEP(slot_description_qm)) {
	    slot_description_to_return_qm = Nil;
	    goto end_16;
	}
	else if (slot_description_qm) {
	    if (EQ(slot_name,ISVREF(slot_description_qm,(SI_Long)1L)) ||  
		    !TRUEP(ISVREF(slot_description_qm,(SI_Long)8L))) {
		if (gathered_slot_descriptions_qm) {
		    last_1 = gathered_slot_descriptions_qm;
		    next_qm = Nil;
		  next_loop_24:
		    next_qm = M_CDR(last_1);
		    if ( !TRUEP(next_qm))
			goto end_loop_24;
		    inline_note_reclaim_cons(last_1,Qframe);
		    last_1 = next_qm;
		    goto next_loop_24;
		  end_loop_24:
		    inline_note_reclaim_cons(last_1,Qframe);
		    if (ISVREF(Available_frame_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_2 = ISVREF(Available_frame_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_2) = gathered_slot_descriptions_qm;
			temp_2 = Available_frame_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_2,svref_arg_2) = last_1;
		    }
		    else {
			temp_2 = Available_frame_conses_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_2,svref_arg_2) = 
				gathered_slot_descriptions_qm;
			temp_2 = Available_frame_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_2,svref_arg_2) = last_1;
		    }
		    M_CDR(last_1) = Nil;
		}
		gathered_slot_descriptions_qm = Nil;
		slot_description_to_return_qm = slot_description_qm;
		goto end_16;
	    }
	    else if (EQ(class_name,full_hash_table_class) || 
		    EQ(ISVREF(slot_description_qm,(SI_Long)3L),class_name)) {
		gathered_slot_descriptions_qm = 
			nreverse(gathered_slot_descriptions_qm);
		unique_name = ISVREF(slot_description_qm,(SI_Long)1L);
		gathered_slot_description = Nil;
		ab_loop_list_ = gathered_slot_descriptions_qm;
	      next_loop_25:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_25;
		gathered_slot_description = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if (EQ(ISVREF(gathered_slot_description,(SI_Long)1L),
			unique_name)) {
		    gathered_slot_description_qm = gathered_slot_description;
		    goto end_17;
		}
		goto next_loop_25;
	      end_loop_25:
		gathered_slot_description_qm = Qnil;
	      end_17:;
		if (gathered_slot_description_qm) {
		    if (gathered_slot_descriptions_qm) {
			last_1 = gathered_slot_descriptions_qm;
			next_qm = Nil;
		      next_loop_26:
			next_qm = M_CDR(last_1);
			if ( !TRUEP(next_qm))
			    goto end_loop_26;
			inline_note_reclaim_cons(last_1,Qframe);
			last_1 = next_qm;
			goto next_loop_26;
		      end_loop_26:
			inline_note_reclaim_cons(last_1,Qframe);
			if (ISVREF(Available_frame_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_frame_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = gathered_slot_descriptions_qm;
			    temp_2 = Available_frame_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_2,svref_arg_2) = last_1;
			}
			else {
			    temp_2 = Available_frame_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_2,svref_arg_2) = 
				    gathered_slot_descriptions_qm;
			    temp_2 = Available_frame_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_2,svref_arg_2) = last_1;
			}
			M_CDR(last_1) = Nil;
		    }
		    slot_description_to_return_qm = 
			    gathered_slot_description_qm;
		    goto end_16;
		}
		else {
		    if (gathered_slot_descriptions_qm) {
			last_1 = gathered_slot_descriptions_qm;
			next_qm = Nil;
		      next_loop_27:
			next_qm = M_CDR(last_1);
			if ( !TRUEP(next_qm))
			    goto end_loop_27;
			inline_note_reclaim_cons(last_1,Qframe);
			last_1 = next_qm;
			goto next_loop_27;
		      end_loop_27:
			inline_note_reclaim_cons(last_1,Qframe);
			if (ISVREF(Available_frame_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_frame_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = gathered_slot_descriptions_qm;
			    temp_2 = Available_frame_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_2,svref_arg_2) = last_1;
			}
			else {
			    temp_2 = Available_frame_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_2,svref_arg_2) = 
				    gathered_slot_descriptions_qm;
			    temp_2 = Available_frame_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_2,svref_arg_2) = last_1;
			}
			M_CDR(last_1) = Nil;
		    }
		    slot_description_to_return_qm = slot_description_qm;
		    goto end_16;
		}
	    }
	    else {
		new_cons = ISVREF(Available_frame_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    temp_2 = Available_frame_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(temp_2,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_frame_conses_vector,
			    IFIX(Current_thread_index)))) {
			temp_2 = Available_frame_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_2,svref_arg_2) = Nil;
		    }
		    gensymed_symbol = new_cons;
		}
		else
		    gensymed_symbol = Nil;
		if ( !TRUEP(gensymed_symbol))
		    gensymed_symbol = replenish_frame_cons_pool();
		M_CAR(gensymed_symbol) = slot_description_qm;
		M_CDR(gensymed_symbol) = gathered_slot_descriptions_qm;
		inline_note_allocate_cons(gensymed_symbol,Qframe);
		gathered_slot_descriptions_qm = gensymed_symbol;
	    }
	}
	goto next_loop_21;
      end_loop_21:
	if (gathered_slot_descriptions_qm) {
	    last_1 = gathered_slot_descriptions_qm;
	    next_qm = Nil;
	  next_loop_28:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop_28;
	    inline_note_reclaim_cons(last_1,Qframe);
	    last_1 = next_qm;
	    goto next_loop_28;
	  end_loop_28:
	    inline_note_reclaim_cons(last_1,Qframe);
	    if (ISVREF(Available_frame_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_2 = ISVREF(Available_frame_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_2) = gathered_slot_descriptions_qm;
		temp_2 = Available_frame_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_2,svref_arg_2) = last_1;
	    }
	    else {
		temp_2 = Available_frame_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_2,svref_arg_2) = gathered_slot_descriptions_qm;
		temp_2 = Available_frame_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_2,svref_arg_2) = last_1;
	    }
	    M_CDR(last_1) = Nil;
	}
	slot_description_to_return_qm = Nil;
	goto end_16;
	slot_description_to_return_qm = Qnil;
      end_16:;
	return VALUES_1(slot_description_to_return_qm);
    }
    return VALUES_1(temp_1);
}

/* GET-SLOT-DESCRIPTION-FROM-CLASS */
Object get_slot_description_from_class varargs_1(int, n)
{
    Object class_1, unique_or_pretty_slot_name;
    Object class_if_specific_qm, skip_list, key_value, marked, pred, curr;
    Object succ, reference, temp, temp_1, entry_hash, gensymed_symbol, tail;
    Object head, new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_1, gensymed_symbol_2, global_properties;
    Object kb_properties, kb_specific_value, resulting_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(79,77);
    INIT_ARGS_nonrelocating();
    class_1 = REQUIRED_ARG_nonrelocating();
    unique_or_pretty_slot_name = REQUIRED_ARG_nonrelocating();
    class_if_specific_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    skip_list = CDR(Symbol_properties_table);
    key_value = class_1;
    key_hash_value = SXHASH_SYMBOL_1(class_1) & IFIX(Most_positive_fixnum);
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
    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	    (SI_Long)3L) : Nil) : Nil;
    if ( !TRUEP(gensymed_symbol)) {
	gensymed_symbol = class_1;
	temp = Symbol_properties_table;
	temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		IFIX(Most_positive_fixnum));
	tail = 
		make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
		Nil);
	head = 
		make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
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
	    gensymed_symbol_1 = new_cons;
	}
	else
	    gensymed_symbol_1 = Nil;
	if ( !TRUEP(gensymed_symbol_1))
	    gensymed_symbol_1 = replenish_lookup_cons_pool();
	M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
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
	    gensymed_symbol_2 = new_cons;
	}
	else
	    gensymed_symbol_2 = Nil;
	if ( !TRUEP(gensymed_symbol_2))
	    gensymed_symbol_2 = replenish_lookup_cons_pool();
	M_CAR(gensymed_symbol_2) = head;
	M_CDR(gensymed_symbol_2) = tail;
	inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
	M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
	inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
	gensymed_symbol = set_skip_list_entry(temp,FIX((SI_Long)31L),Qeq,
		Nil,T,gensymed_symbol,temp_1,gensymed_symbol_1);
    }
    global_properties = gensymed_symbol;
    skip_list = CDR(global_properties);
    key_value = Current_kb_specific_property_list_property_name;
    key_hash_value = 
	    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
	    & IFIX(Most_positive_fixnum);
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
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
  next_loop_4:
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
  next_loop_5:
    if ( !TRUEP(marked))
	goto end_loop_4;
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
    goto next_loop_5;
  end_loop_4:
    entry_hash = ISVREF(curr,(SI_Long)1L);
    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
	    key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	pred = curr;
	curr = succ;
    }
    else
	goto end_2;
    goto next_loop_4;
  end_loop_5:
  end_2:
    level = level - (SI_Long)1L;
    goto next_loop_3;
  end_loop_3:;
    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	    (SI_Long)3L) : Nil) : Nil;
    if (kb_properties);
    else
	kb_properties = Nil;
    if (kb_properties) {
	skip_list = CDR(kb_properties);
	key_value = Class_description_gkbprop;
	key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		IFIX(Most_positive_fixnum);
	bottom_level = (SI_Long)0L;
	marked = Nil;
	pred = M_CAR(skip_list);
	curr = Nil;
	succ = Nil;
	level = (SI_Long)31L;
	ab_loop_bind_ = bottom_level;
      next_loop_6:
	if (level < ab_loop_bind_)
	    goto end_loop_6;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_7:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_8:
	if ( !TRUEP(marked))
	    goto end_loop_7;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_8;
      end_loop_7:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_3;
	goto next_loop_7;
      end_loop_8:
      end_3:
	level = level - (SI_Long)1L;
	goto next_loop_6;
      end_loop_6:;
	kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	if (kb_specific_value);
	else
	    kb_specific_value = No_specific_property_value;
    }
    else
	kb_specific_value = No_specific_property_value;
    if ( !EQ(kb_specific_value,No_specific_property_value))
	resulting_value = kb_specific_value;
    else {
	skip_list = CDR(global_properties);
	key_value = Class_description_gkbprop;
	key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		IFIX(Most_positive_fixnum);
	bottom_level = (SI_Long)0L;
	marked = Nil;
	pred = M_CAR(skip_list);
	curr = Nil;
	succ = Nil;
	level = (SI_Long)31L;
	ab_loop_bind_ = bottom_level;
      next_loop_9:
	if (level < ab_loop_bind_)
	    goto end_loop_9;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_10:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_11:
	if ( !TRUEP(marked))
	    goto end_loop_10;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_11;
      end_loop_10:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_4;
	goto next_loop_10;
      end_loop_11:
      end_4:
	level = level - (SI_Long)1L;
	goto next_loop_9;
      end_loop_9:;
	resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if (resulting_value);
	else
	    resulting_value = Nil;
    }
    gensymed_symbol = resulting_value;
    return get_slot_description_of_class_description_function(unique_or_pretty_slot_name,
	    gensymed_symbol,class_if_specific_qm);
}

/* GET-SLOT-DESCRIPTION-WITH-USER-VECTOR-SLOT-INDEX */
Object get_slot_description_with_user_vector_slot_index(user_vector_slot_index,
	    item)
    Object user_vector_slot_index, item;
{
    Object class_description, slot_descriptions, slot_description;
    Object ab_loop_list_, temp;

    x_note_fn_call(79,78);
    class_description = ISVREF(item,(SI_Long)1L);
    slot_descriptions = ISVREF(class_description,(SI_Long)6L);
    slot_description = Nil;
    ab_loop_list_ = slot_descriptions;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    slot_description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(user_vector_slot_index,ISVREF(slot_description,(SI_Long)8L))) {
	temp = slot_description;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* SLOT-INHERITED-FROM-CLASS-P */
Object slot_inherited_from_class_p(class_1,subclass,pretty_slot_name)
    Object class_1, subclass, pretty_slot_name;
{
    Object temp, temp_1;

    x_note_fn_call(79,79);
    temp = 
	    ISVREF(get_slot_description_of_class_description_function(pretty_slot_name,
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop),Nil),(SI_Long)6L);
    temp_1 = 
	    ISVREF(get_slot_description_of_class_description_function(pretty_slot_name,
	    lookup_global_or_kb_specific_property_value(subclass,
	    Class_description_gkbprop),Nil),(SI_Long)6L);
    return VALUES_1(EQUAL(temp,temp_1) ? T : Nil);
}

/* CLASS-HAS-OVERRIDE-ON-SLOT-P */
Object class_has_override_on_slot_p(class_description,unique_slot_name)
    Object class_description, unique_slot_name;
{
    Object class_name, class_description_qm, temp, class_slot_description_qm;

    x_note_fn_call(79,80);
    class_name = ISVREF(class_description,(SI_Long)1L);
    class_description_qm = 
	    lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop);
    if (class_description_qm &&  !TRUEP(ISVREF(class_description_qm,
	    (SI_Long)20L)))
	temp = memq_function(unique_slot_name,ISVREF(class_description,
		(SI_Long)8L));
    else {
	class_slot_description_qm = 
		get_slot_description_of_class_description_function(unique_slot_name,
		class_description,Nil);
	temp = class_slot_description_qm ? 
		(EQ(ISVREF(class_slot_description_qm,(SI_Long)3L),
		class_name) ? T : Nil) : Qnil;
    }
    return VALUES_1(temp);
}

/* MOST-SPECIFIC-SUPERIOR-THAT-REFINES-SLOT */
Object most_specific_superior_that_refines_slot(class_inheritance_path,
	    slot_description)
    Object class_inheritance_path, slot_description;
{
    Object unique_slot_name, defining_class, superior, ab_loop_list_;
    Object class_description_qm, skip_list, key_value, marked, pred, curr;
    Object succ, reference, temp, temp_1, entry_hash, gensymed_symbol, tail;
    Object head, new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_1, gensymed_symbol_2, global_properties;
    Object kb_properties, kb_specific_value, resulting_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(79,81);
    unique_slot_name = ISVREF(slot_description,(SI_Long)1L);
    defining_class = ISVREF(slot_description,(SI_Long)3L);
    superior = Nil;
    ab_loop_list_ = CDR(class_inheritance_path);
    class_description_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    superior = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(superior,defining_class))
	goto end_loop;
    class_description_qm = 
	    lookup_global_or_kb_specific_property_value(superior,
	    Class_description_gkbprop);
    if (class_description_qm && 
	    class_has_override_on_slot_p(class_description_qm,
	    unique_slot_name))
	return VALUES_1(superior);
    goto next_loop;
  end_loop:
    if (SYMBOLP(defining_class)) {
	skip_list = CDR(Symbol_properties_table);
	key_value = defining_class;
	key_hash_value = SXHASH_SYMBOL_1(defining_class) & 
		IFIX(Most_positive_fixnum);
	bottom_level = (SI_Long)0L;
	marked = Nil;
	pred = M_CAR(skip_list);
	curr = Nil;
	succ = Nil;
	level = (SI_Long)31L;
	ab_loop_bind_ = bottom_level;
      next_loop_1:
	if (level < ab_loop_bind_)
	    goto end_loop_1;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_2:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_3:
	if ( !TRUEP(marked))
	    goto end_loop_2;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_3;
      end_loop_2:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_1;
	goto next_loop_2;
      end_loop_3:
      end_1:
	level = level - (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = defining_class;
	    temp = Symbol_properties_table;
	    temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		    IFIX(Most_positive_fixnum));
	    tail = 
		    make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
		    Nil);
	    head = 
		    make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
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
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_lookup_cons_pool();
	    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
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
		gensymed_symbol_2 = new_cons;
	    }
	    else
		gensymed_symbol_2 = Nil;
	    if ( !TRUEP(gensymed_symbol_2))
		gensymed_symbol_2 = replenish_lookup_cons_pool();
	    M_CAR(gensymed_symbol_2) = head;
	    M_CDR(gensymed_symbol_2) = tail;
	    inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
	    M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
	    inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
	    gensymed_symbol = set_skip_list_entry(temp,FIX((SI_Long)31L),
		    Qeq,Nil,T,gensymed_symbol,temp_1,gensymed_symbol_1);
	}
	global_properties = gensymed_symbol;
	skip_list = CDR(global_properties);
	key_value = Current_kb_specific_property_list_property_name;
	key_hash_value = 
		SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		& IFIX(Most_positive_fixnum);
	bottom_level = (SI_Long)0L;
	marked = Nil;
	pred = M_CAR(skip_list);
	curr = Nil;
	succ = Nil;
	level = (SI_Long)31L;
	ab_loop_bind_ = bottom_level;
      next_loop_4:
	if (level < ab_loop_bind_)
	    goto end_loop_4;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_5:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_6:
	if ( !TRUEP(marked))
	    goto end_loop_5;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_6;
      end_loop_5:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_2;
	goto next_loop_5;
      end_loop_6:
      end_2:
	level = level - (SI_Long)1L;
	goto next_loop_4;
      end_loop_4:;
	kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		(EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if (kb_properties);
	else
	    kb_properties = Nil;
	if (kb_properties) {
	    skip_list = CDR(kb_properties);
	    key_value = Class_description_gkbprop;
	    key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_7:
	    if (level < ab_loop_bind_)
		goto end_loop_7;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_8:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_9:
	    if ( !TRUEP(marked))
		goto end_loop_8;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_9;
	  end_loop_8:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_3;
	    goto next_loop_8;
	  end_loop_9:
	  end_3:
	    level = level - (SI_Long)1L;
	    goto next_loop_7;
	  end_loop_7:;
	    kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (kb_specific_value);
	    else
		kb_specific_value = No_specific_property_value;
	}
	else
	    kb_specific_value = No_specific_property_value;
	if ( !EQ(kb_specific_value,No_specific_property_value))
	    resulting_value = kb_specific_value;
	else {
	    skip_list = CDR(global_properties);
	    key_value = Class_description_gkbprop;
	    key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_10:
	    if (level < ab_loop_bind_)
		goto end_loop_10;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_11:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_12:
	    if ( !TRUEP(marked))
		goto end_loop_11;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_12;
	  end_loop_11:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_4;
	    goto next_loop_11;
	  end_loop_12:
	  end_4:
	    level = level - (SI_Long)1L;
	    goto next_loop_10;
	  end_loop_10:;
	    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (resulting_value);
	    else
		resulting_value = Nil;
	}
	temp_2 = TRUEP(resulting_value);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2)
	return VALUES_1(defining_class);
    else
	return VALUES_1(Nil);
    return VALUES_1(Qnil);
}

/* SLOT-DESCRIPTION-OF-MOST-SPECIFIC-SUPERIOR-REFINING-SLOT */
Object slot_description_of_most_specific_superior_refining_slot(class_inheritance_path,
	    slot_description)
    Object class_inheritance_path, slot_description;
{
    Object refining_superior_qm, class_description;

    x_note_fn_call(79,82);
    refining_superior_qm = 
	    most_specific_superior_that_refines_slot(class_inheritance_path,
	    slot_description);
    if (refining_superior_qm) {
	class_description = 
		lookup_global_or_kb_specific_property_value(refining_superior_qm,
		Class_description_gkbprop);
	return get_slot_description(2,ISVREF(slot_description,(SI_Long)1L),
		ISVREF(class_description,(SI_Long)6L));
    }
    else
	return VALUES_1(Nil);
}

static Object Qslot_hash;          /* slot-hash */

/* MAKE-SPARSE-SLOT-DESCRIPTIONS-HASH-TABLE */
Object make_sparse_slot_descriptions_hash_table(class_1,slot_descriptions,
	    class_inheritance_path)
    Object class_1, slot_descriptions, class_inheritance_path;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, hash_table, slot_description, ab_loop_list_;
    Object unique_slot_name, defining_class;
    Object differs_from_superior_slot_description_qm, superior;
    Object ab_loop_list__1, superior_slot_description_qm, skip_list, key_value;
    Object marked, pred, curr, succ, reference, temp, temp_1, entry_hash, tail;
    Object head, gensymed_symbol_1, gensymed_symbol_2, global_properties;
    Object kb_properties, kb_specific_value, resulting_value, pretty_slot_name;
    Object existing_pretty_name_slot_description_qm, class_inheritance_path_1;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long gensymed_symbol_3, gensymed_symbol_4;
    char temp_2;
    Object result;

    x_note_fn_call(79,83);
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
    M_CAR(gensymed_symbol) = Qslot_hash;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qlookup);
    hash_table = gensymed_symbol;
    slot_description = Nil;
    ab_loop_list_ = slot_descriptions;
    unique_slot_name = Nil;
    defining_class = Nil;
    differs_from_superior_slot_description_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    slot_description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    unique_slot_name = ISVREF(slot_description,(SI_Long)1L);
    defining_class = ISVREF(slot_description,(SI_Long)3L);
    if ( !EQ(defining_class,class_1)) {
	superior = Nil;
	ab_loop_list__1 = CDR(class_inheritance_path);
	superior_slot_description_qm = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	superior = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	skip_list = CDR(Symbol_properties_table);
	key_value = superior;
	key_hash_value = SXHASH_SYMBOL_1(superior) & 
		IFIX(Most_positive_fixnum);
	bottom_level = (SI_Long)0L;
	marked = Nil;
	pred = M_CAR(skip_list);
	curr = Nil;
	succ = Nil;
	level = (SI_Long)31L;
	ab_loop_bind_ = bottom_level;
      next_loop_2:
	if (level < ab_loop_bind_)
	    goto end_loop_2;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_3:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_4:
	if ( !TRUEP(marked))
	    goto end_loop_3;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_4;
      end_loop_3:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_1;
	goto next_loop_3;
      end_loop_4:
      end_1:
	level = level - (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:;
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = superior;
	    temp = Symbol_properties_table;
	    temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		    IFIX(Most_positive_fixnum));
	    tail = 
		    make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
		    Nil);
	    head = 
		    make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
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
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_lookup_cons_pool();
	    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
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
		gensymed_symbol_2 = new_cons;
	    }
	    else
		gensymed_symbol_2 = Nil;
	    if ( !TRUEP(gensymed_symbol_2))
		gensymed_symbol_2 = replenish_lookup_cons_pool();
	    M_CAR(gensymed_symbol_2) = head;
	    M_CDR(gensymed_symbol_2) = tail;
	    inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
	    M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
	    inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
	    gensymed_symbol = set_skip_list_entry(temp,FIX((SI_Long)31L),
		    Qeq,Nil,T,gensymed_symbol,temp_1,gensymed_symbol_1);
	}
	global_properties = gensymed_symbol;
	skip_list = CDR(global_properties);
	key_value = Current_kb_specific_property_list_property_name;
	key_hash_value = 
		SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		& IFIX(Most_positive_fixnum);
	bottom_level = (SI_Long)0L;
	marked = Nil;
	pred = M_CAR(skip_list);
	curr = Nil;
	succ = Nil;
	level = (SI_Long)31L;
	ab_loop_bind_ = bottom_level;
      next_loop_5:
	if (level < ab_loop_bind_)
	    goto end_loop_5;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_6:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_7:
	if ( !TRUEP(marked))
	    goto end_loop_6;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_7;
      end_loop_6:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_2;
	goto next_loop_6;
      end_loop_7:
      end_2:
	level = level - (SI_Long)1L;
	goto next_loop_5;
      end_loop_5:;
	kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		(EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if (kb_properties);
	else
	    kb_properties = Nil;
	if (kb_properties) {
	    skip_list = CDR(kb_properties);
	    key_value = Class_description_gkbprop;
	    key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_8:
	    if (level < ab_loop_bind_)
		goto end_loop_8;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_9:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_10:
	    if ( !TRUEP(marked))
		goto end_loop_9;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_10;
	  end_loop_9:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_3;
	    goto next_loop_9;
	  end_loop_10:
	  end_3:
	    level = level - (SI_Long)1L;
	    goto next_loop_8;
	  end_loop_8:;
	    kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (kb_specific_value);
	    else
		kb_specific_value = No_specific_property_value;
	}
	else
	    kb_specific_value = No_specific_property_value;
	if ( !EQ(kb_specific_value,No_specific_property_value))
	    resulting_value = kb_specific_value;
	else {
	    skip_list = CDR(global_properties);
	    key_value = Class_description_gkbprop;
	    key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_11:
	    if (level < ab_loop_bind_)
		goto end_loop_11;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_12:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_13:
	    if ( !TRUEP(marked))
		goto end_loop_12;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_13;
	  end_loop_12:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_4;
	    goto next_loop_12;
	  end_loop_13:
	  end_4:
	    level = level - (SI_Long)1L;
	    goto next_loop_11;
	  end_loop_11:;
	    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (resulting_value);
	    else
		resulting_value = Nil;
	}
	gensymed_symbol = resulting_value;
	superior_slot_description_qm = 
		get_slot_description_of_class_description_function(unique_slot_name,
		gensymed_symbol,Nil);
	if (superior_slot_description_qm)
	    goto end_loop_1;
	goto next_loop_1;
      end_loop_1:
	if (EQ(slot_description,superior_slot_description_qm)) {
	    differs_from_superior_slot_description_qm = Nil;
	    goto end_5;
	}
	else {
	    differs_from_superior_slot_description_qm = T;
	    goto end_5;
	}
	differs_from_superior_slot_description_qm = Qnil;
      end_5:;
    }
    else
	differs_from_superior_slot_description_qm = Nil;
    if (EQ(defining_class,class_1) || 
	    differs_from_superior_slot_description_qm) {
	gensymed_symbol = unique_slot_name;
	temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		IFIX(Most_positive_fixnum));
	set_balanced_binary_tree_entry(hash_table,Qeq,Nil,T,
		gensymed_symbol,temp_1,slot_description);
	if (ISVREF(slot_description,(SI_Long)8L)) {
	    pretty_slot_name = ISVREF(slot_description,(SI_Long)2L);
	    gensymed_symbol = CDR(hash_table);
	    gensymed_symbol_1 = pretty_slot_name;
	    gensymed_symbol_3 = SXHASH_SYMBOL_1(pretty_slot_name) & 
		    IFIX(Most_positive_fixnum);
	    gensymed_symbol_4 = (SI_Long)0L;
	  next_loop_14:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_14;
	    gensymed_symbol_4 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_3 < gensymed_symbol_4)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_3 > gensymed_symbol_4)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_2 = Nil;
	      next_loop_15:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_15;
		gensymed_symbol_2 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_2)) {
		    existing_pretty_name_slot_description_qm = 
			    M_CDR(M_CAR(gensymed_symbol));
		    goto end_6;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_15;
	      end_loop_15:
		existing_pretty_name_slot_description_qm = Qnil;
	      end_6:;
		goto end_7;
	    }
	    goto next_loop_14;
	  end_loop_14:
	    existing_pretty_name_slot_description_qm = Qnil;
	  end_7:;
	    temp_2 =  !TRUEP(existing_pretty_name_slot_description_qm);
	    if (temp_2);
	    else {
		class_inheritance_path_1 = class_inheritance_path;
		temp_1 = position(2,defining_class,class_inheritance_path_1);
		temp_2 = FIXNUM_LT(temp_1,position(2,
			ISVREF(existing_pretty_name_slot_description_qm,
			(SI_Long)3L),class_inheritance_path_1));
	    }
	    if (temp_2) {
		gensymed_symbol = pretty_slot_name;
		temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum));
		set_balanced_binary_tree_entry(hash_table,Qeq,Nil,T,
			gensymed_symbol,temp_1,slot_description);
	    }
	}
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(hash_table);
}

/* MAKE-FULL-SLOT-DESCRIPTIONS-HASH-TABLE */
Object make_full_slot_descriptions_hash_table(slot_descriptions,
	    class_inheritance_path)
    Object slot_descriptions, class_inheritance_path;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, hash_table, slot_description, ab_loop_list_, temp;
    Object pretty_slot_name, gensymed_symbol_1, gensymed_symbol_4;
    Object current_slot_value_qm;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;

    x_note_fn_call(79,84);
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
    M_CAR(gensymed_symbol) = Qslot_hash;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qlookup);
    hash_table = gensymed_symbol;
    slot_description = Nil;
    ab_loop_list_ = slot_descriptions;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    slot_description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = ISVREF(slot_description,(SI_Long)1L);
    temp = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & IFIX(Most_positive_fixnum));
    set_balanced_binary_tree_entry(hash_table,Qeq,Nil,T,gensymed_symbol,
	    temp,slot_description);
    if (ISVREF(slot_description,(SI_Long)8L)) {
	pretty_slot_name = ISVREF(slot_description,(SI_Long)2L);
	gensymed_symbol = CDR(hash_table);
	gensymed_symbol_1 = pretty_slot_name;
	gensymed_symbol_2 = SXHASH_SYMBOL_1(pretty_slot_name) & 
		IFIX(Most_positive_fixnum);
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop_1:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	if (gensymed_symbol_2 < gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	else if (gensymed_symbol_2 > gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	else {
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_2:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_2;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		current_slot_value_qm = M_CDR(M_CAR(gensymed_symbol));
		goto end_1;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:
	    current_slot_value_qm = Qnil;
	  end_1:;
	    goto end_2;
	}
	goto next_loop_1;
      end_loop_1:
	current_slot_value_qm = Qnil;
      end_2:;
	temp_1 =  !TRUEP(current_slot_value_qm);
	if (temp_1);
	else {
	    temp = position(2,ISVREF(slot_description,(SI_Long)3L),
		    class_inheritance_path);
	    temp_1 = FIXNUM_LT(temp,position(2,
		    ISVREF(current_slot_value_qm,(SI_Long)3L),
		    class_inheritance_path));
	}
	if (temp_1) {
	    gensymed_symbol = pretty_slot_name;
	    temp = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		    IFIX(Most_positive_fixnum));
	    set_balanced_binary_tree_entry(hash_table,Qeq,Nil,T,
		    gensymed_symbol,temp,slot_description);
	}
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(hash_table);
}

/* RECLAIM-FRAME-LIST-FUNCTION */
Object reclaim_frame_list_function(list_1)
    Object list_1;
{
    x_note_fn_call(79,85);
    return reclaim_frame_list_1(list_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Class_bit_numbers_pool, Qclass_bit_numbers_pool);

/* NORMALIZE-FEATURES */
Object normalize_features(features)
    Object features;
{
    Object feature, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;

    x_note_fn_call(79,86);
    feature = Nil;
    ab_loop_list_ = features;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    feature = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = LIST_1(CONSP(feature) ? copy_tree(feature) : 
	    CONS(feature,Nil));
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

Object Global_class_features = UNBOUND;

/* GET-CLASS-FEATURE-IF-ANY */
Object get_class_feature_if_any(class_1,feature_name)
    Object class_1, feature_name;
{
    Object class_description_qm;

    x_note_fn_call(79,87);
    class_description_qm = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    if (class_description_qm)
	return assq_function(feature_name,ISVREF(class_description_qm,
		(SI_Long)12L));
    else
	return VALUES_1(Nil);
}

Object Global_slot_features = UNBOUND;

/* ERROR-CHECK-SLOT-FEATURES */
Object error_check_slot_features(slot_features)
    Object slot_features;
{
    Object supposed_feature, ab_loop_list_;

    x_note_fn_call(79,88);
    if ( !( !TRUEP(slot_features) || CONSP(slot_features)))
	error((SI_Long)2L,"~S is an invalid slot feature list.",slot_features);
    else {
	supposed_feature = Nil;
	ab_loop_list_ = slot_features;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	supposed_feature = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(memq_function(ATOM(supposed_feature) ? 
		supposed_feature : CAR(supposed_feature),
		Global_slot_features)))
	    error((SI_Long)2L,"~S is an invalid slot feature.",
		    supposed_feature);
	goto next_loop;
      end_loop:;
    }
    return VALUES_1(slot_features);
}

/* GET-SLOT-FEATURE-IF-ANY */
Object get_slot_feature_if_any varargs_1(int, n)
{
    Object class_1, unique_or_pretty_slot_name, feature_name;
    Object class_if_specific_qm, class_description_qm, slot_description_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(79,89);
    INIT_ARGS_nonrelocating();
    class_1 = REQUIRED_ARG_nonrelocating();
    unique_or_pretty_slot_name = REQUIRED_ARG_nonrelocating();
    feature_name = REQUIRED_ARG_nonrelocating();
    class_if_specific_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    class_description_qm = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    slot_description_qm = class_description_qm ? 
	    get_slot_description_of_class_description_function(unique_or_pretty_slot_name,
	    class_description_qm,class_if_specific_qm) : Nil;
    if (slot_description_qm)
	return assq_function(feature_name,ISVREF(slot_description_qm,
		(SI_Long)9L));
    else
	return VALUES_1(Nil);
}

static Object Qitem;               /* item */

static Object Qclass_definition;   /* class-definition */

static Object Qobject_definition;  /* object-definition */

static Object Qpreviously_put_in_attribute_tables;  /* previously-put-in-attribute-tables */

/* ATTRIBUTE-PREVIOUSLY-PUT-IN-ATTRIBUTE-TABLES-P */
Object attribute_previously_put_in_attribute_tables_p varargs_1(int, n)
{
    Object attribute;
    Object class_qm, slot_name_or_alias, class_or_frame_qm;
    Object unaliased_attribute, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp, temp_1, entry_hash, gensymed_symbol, tail, head;
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_1, gensymed_symbol_2, global_properties;
    Object kb_properties, kb_specific_value, resulting_value;
    Object slot_description_qm, ab_loop_list_;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(79,90);
    INIT_ARGS_nonrelocating();
    attribute = REQUIRED_ARG_nonrelocating();
    class_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    slot_name_or_alias = attribute;
    class_or_frame_qm = class_qm;
    if (class_or_frame_qm);
    else
	class_or_frame_qm = Qitem;
    unaliased_attribute = 
	    get_slot_name_for_alias_if_any(slot_name_or_alias,
	    class_or_frame_qm);
    if (unaliased_attribute);
    else
	unaliased_attribute = slot_name_or_alias;
    if (class_qm) {
	skip_list = CDR(Symbol_properties_table);
	key_value = unaliased_attribute;
	key_hash_value = SXHASH_SYMBOL_1(unaliased_attribute) & 
		IFIX(Most_positive_fixnum);
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
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = unaliased_attribute;
	    temp = Symbol_properties_table;
	    temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		    IFIX(Most_positive_fixnum));
	    tail = 
		    make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
		    Nil);
	    head = 
		    make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
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
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_lookup_cons_pool();
	    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
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
		gensymed_symbol_2 = new_cons;
	    }
	    else
		gensymed_symbol_2 = Nil;
	    if ( !TRUEP(gensymed_symbol_2))
		gensymed_symbol_2 = replenish_lookup_cons_pool();
	    M_CAR(gensymed_symbol_2) = head;
	    M_CDR(gensymed_symbol_2) = tail;
	    inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
	    M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
	    inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
	    gensymed_symbol = set_skip_list_entry(temp,FIX((SI_Long)31L),
		    Qeq,Nil,T,gensymed_symbol,temp_1,gensymed_symbol_1);
	}
	global_properties = gensymed_symbol;
	skip_list = CDR(global_properties);
	key_value = Current_kb_specific_property_list_property_name;
	key_hash_value = 
		SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		& IFIX(Most_positive_fixnum);
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
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_4:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_5:
	if ( !TRUEP(marked))
	    goto end_loop_4;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_5;
      end_loop_4:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_2;
	goto next_loop_4;
      end_loop_5:
      end_2:
	level = level - (SI_Long)1L;
	goto next_loop_3;
      end_loop_3:;
	kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		(EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if (kb_properties);
	else
	    kb_properties = Nil;
	if (kb_properties) {
	    skip_list = CDR(kb_properties);
	    key_value = Class_description_gkbprop;
	    key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_6:
	    if (level < ab_loop_bind_)
		goto end_loop_6;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_7:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_8:
	    if ( !TRUEP(marked))
		goto end_loop_7;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_8;
	  end_loop_7:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_3;
	    goto next_loop_7;
	  end_loop_8:
	  end_3:
	    level = level - (SI_Long)1L;
	    goto next_loop_6;
	  end_loop_6:;
	    kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (kb_specific_value);
	    else
		kb_specific_value = No_specific_property_value;
	}
	else
	    kb_specific_value = No_specific_property_value;
	if ( !EQ(kb_specific_value,No_specific_property_value))
	    resulting_value = kb_specific_value;
	else {
	    skip_list = CDR(global_properties);
	    key_value = Class_description_gkbprop;
	    key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_9:
	    if (level < ab_loop_bind_)
		goto end_loop_9;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_10:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_11:
	    if ( !TRUEP(marked))
		goto end_loop_10;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_11;
	  end_loop_10:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_4;
	    goto next_loop_10;
	  end_loop_11:
	  end_4:
	    level = level - (SI_Long)1L;
	    goto next_loop_9;
	  end_loop_9:;
	    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (resulting_value);
	    else
		resulting_value = Nil;
	}
	gensymed_symbol = resulting_value;
	slot_description_qm = 
		get_slot_description_of_class_description_function(class_qm,
		gensymed_symbol,Nil);
    }
    else {
	skip_list = CDR(Symbol_properties_table);
	key_value = Qclass_definition;
	key_hash_value = SXHASH_SYMBOL_1(Qclass_definition) & 
		IFIX(Most_positive_fixnum);
	bottom_level = (SI_Long)0L;
	marked = Nil;
	pred = M_CAR(skip_list);
	curr = Nil;
	succ = Nil;
	level = (SI_Long)31L;
	ab_loop_bind_ = bottom_level;
      next_loop_12:
	if (level < ab_loop_bind_)
	    goto end_loop_12;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_13:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_14:
	if ( !TRUEP(marked))
	    goto end_loop_13;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_14;
      end_loop_13:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_5;
	goto next_loop_13;
      end_loop_14:
      end_5:
	level = level - (SI_Long)1L;
	goto next_loop_12;
      end_loop_12:;
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = Qclass_definition;
	    temp = Symbol_properties_table;
	    temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		    IFIX(Most_positive_fixnum));
	    tail = 
		    make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
		    Nil);
	    head = 
		    make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
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
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_lookup_cons_pool();
	    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
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
		gensymed_symbol_2 = new_cons;
	    }
	    else
		gensymed_symbol_2 = Nil;
	    if ( !TRUEP(gensymed_symbol_2))
		gensymed_symbol_2 = replenish_lookup_cons_pool();
	    M_CAR(gensymed_symbol_2) = head;
	    M_CDR(gensymed_symbol_2) = tail;
	    inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
	    M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
	    inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
	    gensymed_symbol = set_skip_list_entry(temp,FIX((SI_Long)31L),
		    Qeq,Nil,T,gensymed_symbol,temp_1,gensymed_symbol_1);
	}
	global_properties = gensymed_symbol;
	skip_list = CDR(global_properties);
	key_value = Current_kb_specific_property_list_property_name;
	key_hash_value = 
		SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		& IFIX(Most_positive_fixnum);
	bottom_level = (SI_Long)0L;
	marked = Nil;
	pred = M_CAR(skip_list);
	curr = Nil;
	succ = Nil;
	level = (SI_Long)31L;
	ab_loop_bind_ = bottom_level;
      next_loop_15:
	if (level < ab_loop_bind_)
	    goto end_loop_15;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_16:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_17:
	if ( !TRUEP(marked))
	    goto end_loop_16;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_17;
      end_loop_16:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_6;
	goto next_loop_16;
      end_loop_17:
      end_6:
	level = level - (SI_Long)1L;
	goto next_loop_15;
      end_loop_15:;
	kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		(EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if (kb_properties);
	else
	    kb_properties = Nil;
	if (kb_properties) {
	    skip_list = CDR(kb_properties);
	    key_value = Class_description_gkbprop;
	    key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_18:
	    if (level < ab_loop_bind_)
		goto end_loop_18;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_19:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_20:
	    if ( !TRUEP(marked))
		goto end_loop_19;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_20;
	  end_loop_19:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_7;
	    goto next_loop_19;
	  end_loop_20:
	  end_7:
	    level = level - (SI_Long)1L;
	    goto next_loop_18;
	  end_loop_18:;
	    kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (kb_specific_value);
	    else
		kb_specific_value = No_specific_property_value;
	}
	else
	    kb_specific_value = No_specific_property_value;
	if ( !EQ(kb_specific_value,No_specific_property_value))
	    resulting_value = kb_specific_value;
	else {
	    skip_list = CDR(global_properties);
	    key_value = Class_description_gkbprop;
	    key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_21:
	    if (level < ab_loop_bind_)
		goto end_loop_21;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_22:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_23:
	    if ( !TRUEP(marked))
		goto end_loop_22;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_23;
	  end_loop_22:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_8;
	    goto next_loop_22;
	  end_loop_23:
	  end_8:
	    level = level - (SI_Long)1L;
	    goto next_loop_21;
	  end_loop_21:;
	    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (resulting_value);
	    else
		resulting_value = Nil;
	}
	gensymed_symbol = resulting_value;
	slot_description_qm = 
		get_slot_description_of_class_description_function(unaliased_attribute,
		gensymed_symbol,Nil);
	if (slot_description_qm);
	else {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = Qobject_definition;
	    key_hash_value = SXHASH_SYMBOL_1(Qobject_definition) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_24:
	    if (level < ab_loop_bind_)
		goto end_loop_24;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_25:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_26:
	    if ( !TRUEP(marked))
		goto end_loop_25;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_26;
	  end_loop_25:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_9;
	    goto next_loop_25;
	  end_loop_26:
	  end_9:
	    level = level - (SI_Long)1L;
	    goto next_loop_24;
	  end_loop_24:;
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = Qobject_definition;
		temp = Symbol_properties_table;
		temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum));
		tail = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
			Nil);
		head = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
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
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
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
		    gensymed_symbol_2 = new_cons;
		}
		else
		    gensymed_symbol_2 = Nil;
		if ( !TRUEP(gensymed_symbol_2))
		    gensymed_symbol_2 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_2) = head;
		M_CDR(gensymed_symbol_2) = tail;
		inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
		M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
		inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
		gensymed_symbol = set_skip_list_entry(temp,
			FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp_1,
			gensymed_symbol_1);
	    }
	    global_properties = gensymed_symbol;
	    skip_list = CDR(global_properties);
	    key_value = Current_kb_specific_property_list_property_name;
	    key_hash_value = 
		    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		    & IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_27:
	    if (level < ab_loop_bind_)
		goto end_loop_27;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_28:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_29:
	    if ( !TRUEP(marked))
		goto end_loop_28;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_29;
	  end_loop_28:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_10;
	    goto next_loop_28;
	  end_loop_29:
	  end_10:
	    level = level - (SI_Long)1L;
	    goto next_loop_27;
	  end_loop_27:;
	    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (kb_properties);
	    else
		kb_properties = Nil;
	    if (kb_properties) {
		skip_list = CDR(kb_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_30:
		if (level < ab_loop_bind_)
		    goto end_loop_30;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_31:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_32:
		if ( !TRUEP(marked))
		    goto end_loop_31;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_32;
	      end_loop_31:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_11;
		goto next_loop_31;
	      end_loop_32:
	      end_11:
		level = level - (SI_Long)1L;
		goto next_loop_30;
	      end_loop_30:;
		kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (kb_specific_value);
		else
		    kb_specific_value = No_specific_property_value;
	    }
	    else
		kb_specific_value = No_specific_property_value;
	    if ( !EQ(kb_specific_value,No_specific_property_value))
		resulting_value = kb_specific_value;
	    else {
		skip_list = CDR(global_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_33:
		if (level < ab_loop_bind_)
		    goto end_loop_33;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_34:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_35:
		if ( !TRUEP(marked))
		    goto end_loop_34;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_35;
	      end_loop_34:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_12;
		goto next_loop_34;
	      end_loop_35:
	      end_12:
		level = level - (SI_Long)1L;
		goto next_loop_33;
	      end_loop_33:;
		resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    gensymed_symbol = resulting_value;
	    slot_description_qm = 
		    get_slot_description_of_class_description_function(unaliased_attribute,
		    gensymed_symbol,Nil);
	}
	if (slot_description_qm);
	else {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = Qblock;
	    key_hash_value = SXHASH_SYMBOL_1(Qblock) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_36:
	    if (level < ab_loop_bind_)
		goto end_loop_36;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_37:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_38:
	    if ( !TRUEP(marked))
		goto end_loop_37;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_38;
	  end_loop_37:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_13;
	    goto next_loop_37;
	  end_loop_38:
	  end_13:
	    level = level - (SI_Long)1L;
	    goto next_loop_36;
	  end_loop_36:;
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = Qblock;
		temp = Symbol_properties_table;
		temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum));
		tail = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
			Nil);
		head = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
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
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
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
		    gensymed_symbol_2 = new_cons;
		}
		else
		    gensymed_symbol_2 = Nil;
		if ( !TRUEP(gensymed_symbol_2))
		    gensymed_symbol_2 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_2) = head;
		M_CDR(gensymed_symbol_2) = tail;
		inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
		M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
		inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
		gensymed_symbol = set_skip_list_entry(temp,
			FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp_1,
			gensymed_symbol_1);
	    }
	    global_properties = gensymed_symbol;
	    skip_list = CDR(global_properties);
	    key_value = Current_kb_specific_property_list_property_name;
	    key_hash_value = 
		    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		    & IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_39:
	    if (level < ab_loop_bind_)
		goto end_loop_39;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_40:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_41:
	    if ( !TRUEP(marked))
		goto end_loop_40;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_41;
	  end_loop_40:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_14;
	    goto next_loop_40;
	  end_loop_41:
	  end_14:
	    level = level - (SI_Long)1L;
	    goto next_loop_39;
	  end_loop_39:;
	    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (kb_properties);
	    else
		kb_properties = Nil;
	    if (kb_properties) {
		skip_list = CDR(kb_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_42:
		if (level < ab_loop_bind_)
		    goto end_loop_42;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_43:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_44:
		if ( !TRUEP(marked))
		    goto end_loop_43;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_44;
	      end_loop_43:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_15;
		goto next_loop_43;
	      end_loop_44:
	      end_15:
		level = level - (SI_Long)1L;
		goto next_loop_42;
	      end_loop_42:;
		kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (kb_specific_value);
		else
		    kb_specific_value = No_specific_property_value;
	    }
	    else
		kb_specific_value = No_specific_property_value;
	    if ( !EQ(kb_specific_value,No_specific_property_value))
		resulting_value = kb_specific_value;
	    else {
		skip_list = CDR(global_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_45:
		if (level < ab_loop_bind_)
		    goto end_loop_45;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_46:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_47:
		if ( !TRUEP(marked))
		    goto end_loop_46;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_47;
	      end_loop_46:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_16;
		goto next_loop_46;
	      end_loop_47:
	      end_16:
		level = level - (SI_Long)1L;
		goto next_loop_45;
	      end_loop_45:;
		resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    gensymed_symbol = resulting_value;
	    slot_description_qm = 
		    get_slot_description_of_class_description_function(unaliased_attribute,
		    gensymed_symbol,Nil);
	}
	if (slot_description_qm);
	else {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = Qdrawing_parameters;
	    key_hash_value = SXHASH_SYMBOL_1(Qdrawing_parameters) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_48:
	    if (level < ab_loop_bind_)
		goto end_loop_48;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_49:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_50:
	    if ( !TRUEP(marked))
		goto end_loop_49;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_50;
	  end_loop_49:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_17;
	    goto next_loop_49;
	  end_loop_50:
	  end_17:
	    level = level - (SI_Long)1L;
	    goto next_loop_48;
	  end_loop_48:;
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = Qdrawing_parameters;
		temp = Symbol_properties_table;
		temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum));
		tail = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
			Nil);
		head = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
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
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
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
		    gensymed_symbol_2 = new_cons;
		}
		else
		    gensymed_symbol_2 = Nil;
		if ( !TRUEP(gensymed_symbol_2))
		    gensymed_symbol_2 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_2) = head;
		M_CDR(gensymed_symbol_2) = tail;
		inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
		M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
		inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
		gensymed_symbol = set_skip_list_entry(temp,
			FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp_1,
			gensymed_symbol_1);
	    }
	    global_properties = gensymed_symbol;
	    skip_list = CDR(global_properties);
	    key_value = Current_kb_specific_property_list_property_name;
	    key_hash_value = 
		    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		    & IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_51:
	    if (level < ab_loop_bind_)
		goto end_loop_51;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_52:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_53:
	    if ( !TRUEP(marked))
		goto end_loop_52;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_53;
	  end_loop_52:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_18;
	    goto next_loop_52;
	  end_loop_53:
	  end_18:
	    level = level - (SI_Long)1L;
	    goto next_loop_51;
	  end_loop_51:;
	    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (kb_properties);
	    else
		kb_properties = Nil;
	    if (kb_properties) {
		skip_list = CDR(kb_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_54:
		if (level < ab_loop_bind_)
		    goto end_loop_54;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_55:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_56:
		if ( !TRUEP(marked))
		    goto end_loop_55;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_56;
	      end_loop_55:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_19;
		goto next_loop_55;
	      end_loop_56:
	      end_19:
		level = level - (SI_Long)1L;
		goto next_loop_54;
	      end_loop_54:;
		kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (kb_specific_value);
		else
		    kb_specific_value = No_specific_property_value;
	    }
	    else
		kb_specific_value = No_specific_property_value;
	    if ( !EQ(kb_specific_value,No_specific_property_value))
		resulting_value = kb_specific_value;
	    else {
		skip_list = CDR(global_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_57:
		if (level < ab_loop_bind_)
		    goto end_loop_57;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_58:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_59:
		if ( !TRUEP(marked))
		    goto end_loop_58;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_59;
	      end_loop_58:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_20;
		goto next_loop_58;
	      end_loop_59:
	      end_20:
		level = level - (SI_Long)1L;
		goto next_loop_57;
	      end_loop_57:;
		resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    gensymed_symbol = resulting_value;
	    slot_description_qm = 
		    get_slot_description_of_class_description_function(unaliased_attribute,
		    gensymed_symbol,Nil);
	}
    }
    if (slot_description_qm) {
	gensymed_symbol = Nil;
	ab_loop_list_ = ISVREF(slot_description_qm,(SI_Long)9L);
      next_loop_60:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_60;
	gensymed_symbol = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (gensymed_symbol && EQ(M_CAR(gensymed_symbol),
		Qpreviously_put_in_attribute_tables))
	    return VALUES_1(gensymed_symbol);
	goto next_loop_60;
      end_loop_60:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* MAKE-AND-CHANGE-CLASS-DESCRIPTION */
Object make_and_change_class_description(class_1,class_inheritance_path,
	    class_vector_length,class_features,slot_descriptions,
	    class_is_subclass_of_item_qm,class_user_vector_length,
	    slots_local_to_class,inherited_slots_this_class_overrides,
	    slot_descriptions_hash_table,full_hash_table_class,
	    class_bit_number,class_bit_vector,
	    method_table_of_class_description,system_defined_class_p)
    Object class_1, class_inheritance_path, class_vector_length;
    Object class_features, slot_descriptions, class_is_subclass_of_item_qm;
    Object class_user_vector_length, slots_local_to_class;
    Object inherited_slots_this_class_overrides, slot_descriptions_hash_table;
    Object full_hash_table_class, class_bit_number, class_bit_vector;
    Object method_table_of_class_description, system_defined_class_p;
{
    Object class_description;

    x_note_fn_call(79,91);
    class_description = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    if (class_description);
    else
	class_description = make_class_description_internal_1();
    SVREF(class_description,FIX((SI_Long)1L)) = class_1;
    SVREF(class_description,FIX((SI_Long)2L)) = class_inheritance_path;
    SVREF(class_description,FIX((SI_Long)14L)) = class_vector_length;
    SVREF(class_description,FIX((SI_Long)12L)) = class_features;
    SVREF(class_description,FIX((SI_Long)6L)) = slot_descriptions;
    SVREF(class_description,FIX((SI_Long)16L)) = class_is_subclass_of_item_qm;
    SVREF(class_description,FIX((SI_Long)15L)) = class_user_vector_length;
    SVREF(class_description,FIX((SI_Long)7L)) = slots_local_to_class;
    SVREF(class_description,FIX((SI_Long)8L)) = 
	    inherited_slots_this_class_overrides;
    SVREF(class_description,FIX((SI_Long)9L)) = slot_descriptions_hash_table;
    SVREF(class_description,FIX((SI_Long)17L)) = full_hash_table_class;
    SVREF(class_description,FIX((SI_Long)18L)) = class_bit_number;
    SVREF(class_description,FIX((SI_Long)19L)) = class_bit_vector;
    SVREF(class_description,FIX((SI_Long)11L)) = 
	    method_table_of_class_description;
    SVREF(class_description,FIX((SI_Long)20L)) = system_defined_class_p;
    mutate_global_or_kb_specific_property_value(class_1,class_description,
	    Class_description_gkbprop);
    return VALUES_1(class_description);
}

static Object Qnamelike_slot;      /* namelike-slot */

/* MAKE-SLOT-DESCRIPTION */
Object make_slot_description varargs_1(int, n)
{
    Object pretty_slot_name, defining_class, owner_class;
    Object slot_type_specification, slot_init_form, vector_slot_index_qm;
    Object user_vector_slot_index_qm, slot_features;
    Object do_not_copy_arguments_qm, slot_description, unique_slot_name_to_set;
    Object svref_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(79,92);
    INIT_ARGS_nonrelocating();
    pretty_slot_name = REQUIRED_ARG_nonrelocating();
    defining_class = REQUIRED_ARG_nonrelocating();
    owner_class = REQUIRED_ARG_nonrelocating();
    slot_type_specification = REQUIRED_ARG_nonrelocating();
    slot_init_form = REQUIRED_ARG_nonrelocating();
    vector_slot_index_qm = REQUIRED_ARG_nonrelocating();
    user_vector_slot_index_qm = REQUIRED_ARG_nonrelocating();
    slot_features = REQUIRED_ARG_nonrelocating();
    do_not_copy_arguments_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    slot_description = make_slot_description_internal_1();
    unique_slot_name_to_set = user_vector_slot_index_qm ? 
	    make_unique_slot_name_symbol(defining_class,pretty_slot_name) :
	     pretty_slot_name;
    SVREF(slot_description,FIX((SI_Long)1L)) = unique_slot_name_to_set;
    SVREF(slot_description,FIX((SI_Long)2L)) = pretty_slot_name;
    SVREF(slot_description,FIX((SI_Long)3L)) = defining_class;
    SVREF(slot_description,FIX((SI_Long)4L)) = owner_class;
    svref_new_value = do_not_copy_arguments_qm ? slot_type_specification : 
	    copy_tree_using_class_description_conses_1(slot_type_specification);
    SVREF(slot_description,FIX((SI_Long)5L)) = svref_new_value;
    svref_new_value = do_not_copy_arguments_qm || 
	    icon_description_slot_init_form_p(slot_init_form) ? 
	    slot_init_form : copy_for_slot_value(slot_init_form);
    SVREF(slot_description,FIX((SI_Long)6L)) = svref_new_value;
    SVREF(slot_description,FIX((SI_Long)7L)) = vector_slot_index_qm;
    SVREF(slot_description,FIX((SI_Long)8L)) = user_vector_slot_index_qm;
    svref_new_value = do_not_copy_arguments_qm ? slot_features : 
	    copy_tree_using_class_description_conses_1(slot_features);
    SVREF(slot_description,FIX((SI_Long)9L)) = svref_new_value;
    svref_new_value = assq_function(Qnamelike_slot,slot_features) ? T : Nil;
    SVREF(slot_description,FIX((SI_Long)14L)) = svref_new_value;
    return VALUES_1(slot_description);
}

static Object list_constant;       /* # */

static Object Qsystem;             /* system */

static Object Qvector_slot;        /* vector-slot */

static Object Qlookup_slot;        /* lookup-slot */

static Object string_constant_1;   /* "VECTOR-SLOT" */

static Object string_constant_2;   /* "LOOKUP-SLOT" */

/* MAKE-SLOT-DESCRIPTION-WITH-ERROR-CHECKING */
Object make_slot_description_with_error_checking varargs_1(int, n)
{
    Object class_1, slot_definition;
    Object vector_slot_index, direct_superior_classes_qm, temp_1;
    Object pretty_slot_name, x, slot_init_form, normalized_slot_features;
    Object temp_2, temp_3, slot, new_type;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(79,93);
    INIT_ARGS_nonrelocating();
    class_1 = REQUIRED_ARG_nonrelocating();
    slot_definition = REQUIRED_ARG_nonrelocating();
    vector_slot_index = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    direct_superior_classes_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(slot_definition))
	return error((SI_Long)2L,"~S is an invalid slot name.",Nil);
    else if (CONSP(slot_definition)) {
	temp =  !TRUEP(FIRST(slot_definition));
	if (temp);
	else {
	    temp_1 = CAR(slot_definition);
	    temp =  !SYMBOLP(temp_1);
	}
	if (temp) {
	    pretty_slot_name = FIRST(slot_definition);
	    return error((SI_Long)2L,"~S is an invalid slot name.",
		    pretty_slot_name);
	}
	else {
	    temp =  !TRUEP(CDR(slot_definition));
	    if (temp);
	    else {
		temp_1 = CDR(slot_definition);
		temp = ATOM(temp_1);
	    }
	    if (temp);
	    else {
		x = SECOND(slot_definition);
		temp = TRUEP(memq_function(ATOM(x) ? x : CAR(x),
			Global_slot_features));
	    }
	    if (temp)
		return error((SI_Long)2L,
			"~S is an invalid slot definition.",slot_definition);
	    else {
		pretty_slot_name = FIRST(slot_definition);
		slot_init_form = SECOND(slot_definition);
		if (CONSP(slot_init_form)) {
		    if (memq_function(CAR(slot_init_form),list_constant)) {
			temp =  !TRUEP(CDR(slot_init_form));
			if (temp);
			else {
			    temp_1 = CADR(slot_init_form);
			    if ( !SYMBOLP(temp_1)) {
				temp_1 = CADR(slot_init_form);
				temp = ATOM(temp_1);
			    }
			    else
				temp = TRUEP(Nil);
			}
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		temp_1 = temp ? error((SI_Long)3L,
			"~S, the slot init form of ~S, is an invalid slot initialization.",
			slot_init_form,slot_definition) : slot_init_form;
		normalized_slot_features = 
			normalize_features(error_check_slot_features(CDDR(slot_definition)));
		if ( !TRUEP(assq_function(Qsystem,normalized_slot_features))) {
		    temp_2 = LIST_1(Qsystem);
		    normalized_slot_features = CONS(temp_2,
			    normalized_slot_features);
		}
		if (direct_superior_classes_qm) {
		    temp_2 = FIRST(slot_definition);
		    temp_3 = assq_function(Qvector_slot,
			    normalized_slot_features) ? Qvector_slot : Qnil;
		    if (temp_3);
		    else
			temp_3 = assq_function(Qlookup_slot,
				normalized_slot_features) ? Qlookup_slot : 
				Qnil;
		    if ( 
			    !TRUEP(slot_type_compatible_with_ancestors_p(temp_2,
			    temp_3,direct_superior_classes_qm))) {
			slot = FIRST(slot_definition);
			new_type = assq_function(Qvector_slot,
				normalized_slot_features) ? 
				string_constant_1 : string_constant_2;
			error((SI_Long)3L,
				"An attempt was made to redefine type of slot ~A to ~A.",
				slot,new_type);
		    }
		}
		return make_slot_description(8,pretty_slot_name,class_1,
			class_1,Nil,temp_1,vector_slot_index,Nil,
			normalized_slot_features);
	    }
	}
    }
    else
	return error((SI_Long)2L,"~S is an invalid slot definition.",
		slot_definition);
}

static Object Kfuncall_at_load_time;  /* :funcall-at-load-time */

static Object Qcreate_icon_description_if_valid;  /* create-icon-description-if-valid */

/* EVAL-SLOT-INIT-FORMS-OF-SLOT-DESCRIPTIONS-DEFINED-FOR-CLASS */
Object eval_slot_init_forms_of_slot_descriptions_defined_for_class(user_class,
	    slot_descriptions)
    Object user_class, slot_descriptions;
{
    Object slot_description, ab_loop_list_, slot_init_form, funcall_spec;
    Object function_to_funcall, temp, svref_new_value;

    x_note_fn_call(79,94);
    slot_description = Nil;
    ab_loop_list_ = slot_descriptions;
    slot_init_form = Nil;
    funcall_spec = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    slot_description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    slot_init_form = ISVREF(slot_description,(SI_Long)6L);
    if (CONSP(slot_init_form) && EQ(CAR(slot_init_form),
		Kfuncall_at_load_time)) {
	function_to_funcall = SECOND(slot_init_form);
	funcall_spec = slot_init_form;
	temp = CADR(slot_init_form);
	svref_new_value = APPLY_1(temp,CDDR(slot_init_form));
	SVREF(slot_description,FIX((SI_Long)6L)) = svref_new_value;
	if (EQ(function_to_funcall,Qcreate_icon_description_if_valid))
	    set_icon_owner_class(user_class,ISVREF(slot_description,
		    (SI_Long)6L));
	reclaim_slot_value_list_function(funcall_spec);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* COPY-SLOT-DESCRIPTIONS-EVALUATING-INITIALIZATION-IF-EVAL-ONCE */
Object copy_slot_descriptions_evaluating_initialization_if_eval_once(slot_descriptions)
    Object slot_descriptions;
{
    Object slot_description, ab_loop_list_, slot_init_form;
    Object copy_of_slot_description, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object temp, svref_new_value;

    x_note_fn_call(79,95);
    slot_description = Nil;
    ab_loop_list_ = slot_descriptions;
    slot_init_form = Nil;
    copy_of_slot_description = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    slot_description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    slot_init_form = ISVREF(slot_description,(SI_Long)6L);
    copy_of_slot_description = make_slot_description(9,
	    ISVREF(slot_description,(SI_Long)2L),ISVREF(slot_description,
	    (SI_Long)3L),ISVREF(slot_description,(SI_Long)4L),
	    ISVREF(slot_description,(SI_Long)5L),ISVREF(slot_description,
	    (SI_Long)6L),ISVREF(slot_description,(SI_Long)7L),
	    ISVREF(slot_description,(SI_Long)8L),ISVREF(slot_description,
	    (SI_Long)9L),T);
    if (CONSP(slot_init_form) && EQ(CAR(slot_init_form),
		Kfuncall_at_load_time)) {
	temp = CADR(slot_init_form);
	svref_new_value = APPLY_1(temp,CDDR(slot_init_form));
	SVREF(copy_of_slot_description,FIX((SI_Long)6L)) = svref_new_value;
    }
    ab_loopvar__2 = LIST_1(copy_of_slot_description);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

/* SLOT-TYPE-COMPATIBLE-WITH-ANCESTORS-P */
Object slot_type_compatible_with_ancestors_p(pretty_slot_name,slot_type,
	    direct_superior_classes)
    Object pretty_slot_name, slot_type, direct_superior_classes;
{
    Object slot_description, superior, ab_loop_list_;
    Object slot_description_in_direct_superior_qm;

    x_note_fn_call(79,96);
    if ( !TRUEP(slot_type))
	return VALUES_1(T);
    else {
	slot_description = Nil;
	superior = Nil;
	ab_loop_list_ = direct_superior_classes;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	superior = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (slot_description)
	    goto end_loop;
	slot_description = 
		get_slot_description_of_class_description_function(pretty_slot_name,
		lookup_global_or_kb_specific_property_value(superior,
		Class_description_gkbprop),Nil);
	goto next_loop;
      end_loop:
	slot_description_in_direct_superior_qm = slot_description;
	goto end_1;
	slot_description_in_direct_superior_qm = Qnil;
      end_1:;
	if ( !TRUEP(slot_description_in_direct_superior_qm) || 
		assq_function(slot_type,
		ISVREF(slot_description_in_direct_superior_qm,(SI_Long)9L)))
	    return VALUES_1(T);
	else
	    return VALUES_1(Nil);
    }
}

Object Slot_putter_prop = UNBOUND;

Object Class_slot_description_updater_prop = UNBOUND;

/* CHANGE-CLASS-SLOT-DESCRIPTION-VALUE */
Object change_class_slot_description_value(pretty_slot_name,class_1,new_value)
    Object pretty_slot_name, class_1, new_value;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons, temp_2;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, slot_description;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(79,97);
    skip_list = CDR(Symbol_properties_table);
    key_value = class_1;
    key_hash_value = SXHASH_SYMBOL_1(class_1) & IFIX(Most_positive_fixnum);
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
    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	    (SI_Long)3L) : Nil) : Nil;
    if ( !TRUEP(gensymed_symbol)) {
	gensymed_symbol = class_1;
	temp = Symbol_properties_table;
	temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		IFIX(Most_positive_fixnum));
	tail = 
		make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
		Nil);
	head = 
		make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
		tail);
	new_cons = ISVREF(Available_lookup_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_2 = Available_lookup_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_2,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_2 = Available_lookup_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_2,svref_arg_2) = Nil;
	    }
	    gensymed_symbol_1 = new_cons;
	}
	else
	    gensymed_symbol_1 = Nil;
	if ( !TRUEP(gensymed_symbol_1))
	    gensymed_symbol_1 = replenish_lookup_cons_pool();
	M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
	new_cons = ISVREF(Available_lookup_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_2 = Available_lookup_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_2,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_2 = Available_lookup_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_2,svref_arg_2) = Nil;
	    }
	    gensymed_symbol_2 = new_cons;
	}
	else
	    gensymed_symbol_2 = Nil;
	if ( !TRUEP(gensymed_symbol_2))
	    gensymed_symbol_2 = replenish_lookup_cons_pool();
	M_CAR(gensymed_symbol_2) = head;
	M_CDR(gensymed_symbol_2) = tail;
	inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
	M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
	inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
	gensymed_symbol = set_skip_list_entry(temp,FIX((SI_Long)31L),Qeq,
		Nil,T,gensymed_symbol,temp_1,gensymed_symbol_1);
    }
    global_properties = gensymed_symbol;
    skip_list = CDR(global_properties);
    key_value = Current_kb_specific_property_list_property_name;
    key_hash_value = 
	    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
	    & IFIX(Most_positive_fixnum);
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
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
  next_loop_4:
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
  next_loop_5:
    if ( !TRUEP(marked))
	goto end_loop_4;
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
    goto next_loop_5;
  end_loop_4:
    entry_hash = ISVREF(curr,(SI_Long)1L);
    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
	    key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	pred = curr;
	curr = succ;
    }
    else
	goto end_2;
    goto next_loop_4;
  end_loop_5:
  end_2:
    level = level - (SI_Long)1L;
    goto next_loop_3;
  end_loop_3:;
    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	    (SI_Long)3L) : Nil) : Nil;
    if (kb_properties);
    else
	kb_properties = Nil;
    if (kb_properties) {
	skip_list = CDR(kb_properties);
	key_value = Class_description_gkbprop;
	key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		IFIX(Most_positive_fixnum);
	bottom_level = (SI_Long)0L;
	marked = Nil;
	pred = M_CAR(skip_list);
	curr = Nil;
	succ = Nil;
	level = (SI_Long)31L;
	ab_loop_bind_ = bottom_level;
      next_loop_6:
	if (level < ab_loop_bind_)
	    goto end_loop_6;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_7:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_8:
	if ( !TRUEP(marked))
	    goto end_loop_7;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_8;
      end_loop_7:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_3;
	goto next_loop_7;
      end_loop_8:
      end_3:
	level = level - (SI_Long)1L;
	goto next_loop_6;
      end_loop_6:;
	kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	if (kb_specific_value);
	else
	    kb_specific_value = No_specific_property_value;
    }
    else
	kb_specific_value = No_specific_property_value;
    if ( !EQ(kb_specific_value,No_specific_property_value))
	resulting_value = kb_specific_value;
    else {
	skip_list = CDR(global_properties);
	key_value = Class_description_gkbprop;
	key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		IFIX(Most_positive_fixnum);
	bottom_level = (SI_Long)0L;
	marked = Nil;
	pred = M_CAR(skip_list);
	curr = Nil;
	succ = Nil;
	level = (SI_Long)31L;
	ab_loop_bind_ = bottom_level;
      next_loop_9:
	if (level < ab_loop_bind_)
	    goto end_loop_9;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_10:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_11:
	if ( !TRUEP(marked))
	    goto end_loop_10;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_11;
      end_loop_10:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_4;
	goto next_loop_10;
      end_loop_11:
      end_4:
	level = level - (SI_Long)1L;
	goto next_loop_9;
      end_loop_9:;
	resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if (resulting_value);
	else
	    resulting_value = Nil;
    }
    gensymed_symbol = resulting_value;
    slot_description = 
	    get_slot_description_of_class_description_function(pretty_slot_name,
	    gensymed_symbol,Nil);
    reclaim_slot_value(ISVREF(slot_description,(SI_Long)6L));
    temp_2 = copy_for_slot_value(new_value);
    return VALUES_1(SVREF(slot_description,FIX((SI_Long)6L)) = temp_2);
}

void frames1_INIT()
{
    Object temp, reclaim_structure_for_slot_description_1;
    Object reclaim_structure_for_evaluator_slot_info_1;
    Object reclaim_structure_for_class_description_1;
    Object Qclass_slot_description_updater, AB_package, Qslot_putter;
    Object list_constant_7, Qlocal_name_or_names, Qformat_override;
    Object Qattribute_export_comment, Qnote_slot_changes, Qselect_changes;
    Object Qdo_not_clone, Qedit_only, Qnot_user_editable, Qclass_slot;
    Object Quser_overridable, Qdo_not_put_in_attribute_tables_if_null;
    Object list_constant_6, list_constant_5, list_constant_4;
    Object Qdo_not_put_in_attribute_tables;
    Object Qdo_not_identify_in_attribute_tables, Qclass_of_optional_subframe;
    Object Qdo_not_save, Qsave, Qno_accessor, Qnot_ent, Qnot_nupec, Qnupec;
    Object list_constant_3, Qnot_normally_transient, Qclass_export_comment;
    Object Qonly_compatible_with, Qdisjoint_from, Qhas_indexed_attributes;
    Object Qattribute_displays, Qstubs, Qfoundation_class;
    Object Qnot_solely_instantiable, Qnot_user_instantiable;
    Object Qdo_not_put_in_menus, Qdefine_predicate;
    Object Qreclaim_frame_list_function, Qframes1, Qslot_category;
    Object Qreclaim_structure, Qoutstanding_class_description_count;
    Object Qclass_description_structure_memory_usage, Qutilities2;
    Object string_constant_10, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_9, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qevaluator_slot_info;
    Object Qoutstanding_evaluator_slot_info_count;
    Object Qevaluator_slot_info_structure_memory_usage, string_constant_8;
    Object string_constant_7, Qslot_description;
    Object Qoutstanding_slot_description_count;
    Object Qslot_description_structure_memory_usage, string_constant_6;
    Object string_constant_5, Qdefinition_state, Qinferior_classes;
    Object Qfunction_to_reclaim_kb_specific_property_value_qm;
    Object Qreclaim_class_description_list_function;
    Object Qfunction_to_copy_global_value_for_this_property_name;
    Object Qcopy_list_using_class_description_conses_function;
    Object Qdirect_superior_classes, Qold_class_description;
    Object Qdo_not_carry_global_property_value_into_kbs_qm;
    Object Qcopy_class_description, Qold_slot_name_assignment;
    Object Qslot_name_assignment, Qclasses_which_define, Qclass_methods;
    Object string_constant_4, Qclass_description_cons_memory_usage;
    Object Qoutstanding_class_description_conses, list_constant_2;
    Object Qclass_description_cons_counter_vector, list_constant_1;
    Object Qavailable_class_description_conses_tail_vector;
    Object Qavailable_class_description_conses_vector, string_constant_3;
    Object Qframe_cons_memory_usage, Qoutstanding_frame_conses;
    Object Qframe_cons_counter_vector, Qmake_thread_array;
    Object Qavailable_frame_conses_tail_vector, Qavailable_frame_conses_vector;

    x_note_fn_call(79,98);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qavailable_frame_conses = STATIC_SYMBOL("AVAILABLE-FRAME-CONSES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_frame_conses,Available_frame_conses);
    Qframes1 = STATIC_SYMBOL("FRAMES1",AB_package);
    record_system_variable(Qavailable_frame_conses,Qframes1,Nil,Qnil,Qt,
	    Qnil,Qnil);
    Qavailable_frame_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-FRAME-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_frame_conses_tail,
	    Available_frame_conses_tail);
    record_system_variable(Qavailable_frame_conses_tail,Qframes1,Nil,Qnil,
	    Qt,Qnil,Qnil);
    Qavailable_frame_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-FRAME-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_frame_conses_vector,
	    Available_frame_conses_vector);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_thread_array = STATIC_SYMBOL("MAKE-THREAD-ARRAY",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    Qnil);
    record_system_variable(Qavailable_frame_conses_vector,Qframes1,
	    list_constant_1,Qnil,Qt,Qnil,Qnil);
    Qavailable_frame_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-FRAME-CONSES-TAIL-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_frame_conses_tail_vector,
	    Available_frame_conses_tail_vector);
    record_system_variable(Qavailable_frame_conses_tail_vector,Qframes1,
	    list_constant_1,Qnil,Qt,Qnil,Qnil);
    Qframe_cons_counter_vector = STATIC_SYMBOL("FRAME-CONS-COUNTER-VECTOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qframe_cons_counter_vector,
	    Frame_cons_counter_vector);
    list_constant_2 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    FIX((SI_Long)0L));
    record_system_variable(Qframe_cons_counter_vector,Qframes1,
	    list_constant_2,Qnil,Qt,Qnil,Qnil);
    Qframe_cons_counter = STATIC_SYMBOL("FRAME-CONS-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qframe_cons_counter,Frame_cons_counter);
    record_system_variable(Qframe_cons_counter,Qframes1,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    Qoutstanding_frame_conses = STATIC_SYMBOL("OUTSTANDING-FRAME-CONSES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_frame_conses,
	    STATIC_FUNCTION(outstanding_frame_conses,NIL,FALSE,0,0));
    Qframe_cons_memory_usage = STATIC_SYMBOL("FRAME-CONS-MEMORY-USAGE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qframe_cons_memory_usage,
	    STATIC_FUNCTION(frame_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_3 = STATIC_STRING("1q83-V+y9k83-Uxy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_frame_conses);
    push_optimized_constant(Qframe_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_3));
    Qframe = STATIC_SYMBOL("FRAME",AB_package);
    Qavailable_class_description_conses = 
	    STATIC_SYMBOL("AVAILABLE-CLASS-DESCRIPTION-CONSES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_class_description_conses,
	    Available_class_description_conses);
    record_system_variable(Qavailable_class_description_conses,Qframes1,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qavailable_class_description_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-CLASS-DESCRIPTION-CONSES-TAIL",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_class_description_conses_tail,
	    Available_class_description_conses_tail);
    record_system_variable(Qavailable_class_description_conses_tail,
	    Qframes1,Nil,Qnil,Qt,Qnil,Qnil);
    Qavailable_class_description_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-CLASS-DESCRIPTION-CONSES-VECTOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_class_description_conses_vector,
	    Available_class_description_conses_vector);
    record_system_variable(Qavailable_class_description_conses_vector,
	    Qframes1,list_constant_1,Qnil,Qt,Qnil,Qnil);
    Qavailable_class_description_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-CLASS-DESCRIPTION-CONSES-TAIL-VECTOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_class_description_conses_tail_vector,
	    Available_class_description_conses_tail_vector);
    record_system_variable(Qavailable_class_description_conses_tail_vector,
	    Qframes1,list_constant_1,Qnil,Qt,Qnil,Qnil);
    Qclass_description_cons_counter_vector = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qclass_description_cons_counter_vector,
	    Class_description_cons_counter_vector);
    record_system_variable(Qclass_description_cons_counter_vector,Qframes1,
	    list_constant_2,Qnil,Qt,Qnil,Qnil);
    Qclass_description_cons_counter = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-CONS-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qclass_description_cons_counter,
	    Class_description_cons_counter);
    record_system_variable(Qclass_description_cons_counter,Qframes1,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_class_description_conses = 
	    STATIC_SYMBOL("OUTSTANDING-CLASS-DESCRIPTION-CONSES",AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_class_description_conses,
	    STATIC_FUNCTION(outstanding_class_description_conses,NIL,FALSE,
	    0,0));
    Qclass_description_cons_memory_usage = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-CONS-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qclass_description_cons_memory_usage,
	    STATIC_FUNCTION(class_description_cons_memory_usage,NIL,FALSE,
	    0,0));
    string_constant_4 = STATIC_STRING("1q83-MWy9k83-MVy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_class_description_conses);
    push_optimized_constant(Qclass_description_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_4));
    Qclass_description = STATIC_SYMBOL("CLASS-DESCRIPTION",AB_package);
    Qno_value = STATIC_SYMBOL("NO-VALUE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qno_value,No_value);
    if (No_value == UNBOUND)
	No_value = LIST_1(Qno_value);
    Qclass_methods = STATIC_SYMBOL("CLASS-METHODS",AB_package);
    Class_methods_prop = Qclass_methods;
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    Classes_which_define_prop = Qclasses_which_define;
    Qslot_name_assignment = STATIC_SYMBOL("SLOT-NAME-ASSIGNMENT",AB_package);
    Kb_specific_property_names = CONS(Qslot_name_assignment,
	    Kb_specific_property_names);
    Slot_name_assignment_gkbprop = Qslot_name_assignment;
    Qold_slot_name_assignment = STATIC_SYMBOL("OLD-SLOT-NAME-ASSIGNMENT",
	    AB_package);
    Kb_specific_property_names = CONS(Qold_slot_name_assignment,
	    Kb_specific_property_names);
    Old_slot_name_assignment_gkbprop = Qold_slot_name_assignment;
    Kb_specific_property_names = CONS(Qclass_description,
	    Kb_specific_property_names);
    Qcopy_class_description = STATIC_SYMBOL("COPY-CLASS-DESCRIPTION",
	    AB_package);
    Qfunction_to_copy_global_value_for_this_property_name = 
	    STATIC_SYMBOL("FUNCTION-TO-COPY-GLOBAL-VALUE-FOR-THIS-PROPERTY-NAME",
	    AB_package);
    mutate_global_property(Qclass_description,Qcopy_class_description,
	    Qfunction_to_copy_global_value_for_this_property_name);
    Class_description_gkbprop = Qclass_description;
    Qold_class_description = STATIC_SYMBOL("OLD-CLASS-DESCRIPTION",AB_package);
    Kb_specific_property_names = CONS(Qold_class_description,
	    Kb_specific_property_names);
    Qdo_not_carry_global_property_value_into_kbs_qm = 
	    STATIC_SYMBOL("DO-NOT-CARRY-GLOBAL-PROPERTY-VALUE-INTO-KBS\?",
	    AB_package);
    mutate_global_property(Qold_class_description,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Old_class_description_kbprop = Qold_class_description;
    Qdirect_superior_classes = STATIC_SYMBOL("DIRECT-SUPERIOR-CLASSES",
	    AB_package);
    Kb_specific_property_names = CONS(Qdirect_superior_classes,
	    Kb_specific_property_names);
    Qcopy_list_using_class_description_conses_function = 
	    STATIC_SYMBOL("COPY-LIST-USING-CLASS-DESCRIPTION-CONSES-FUNCTION",
	    AB_package);
    mutate_global_property(Qdirect_superior_classes,
	    Qcopy_list_using_class_description_conses_function,
	    Qfunction_to_copy_global_value_for_this_property_name);
    Qreclaim_class_description_list_function = 
	    STATIC_SYMBOL("RECLAIM-CLASS-DESCRIPTION-LIST-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_class_description_list_function,
	    STATIC_FUNCTION(reclaim_class_description_list_function,NIL,
	    FALSE,1,1));
    Qfunction_to_reclaim_kb_specific_property_value_qm = 
	    STATIC_SYMBOL("FUNCTION-TO-RECLAIM-KB-SPECIFIC-PROPERTY-VALUE\?",
	    AB_package);
    mutate_global_property(Qdirect_superior_classes,
	    Qreclaim_class_description_list_function,
	    Qfunction_to_reclaim_kb_specific_property_value_qm);
    Direct_superior_classes_gkbprop = Qdirect_superior_classes;
    SET_SYMBOL_FUNCTION(Qcopy_list_using_class_description_conses_function,
	    STATIC_FUNCTION(copy_list_using_class_description_conses_function,
	    NIL,FALSE,1,1));
    Qinferior_classes = STATIC_SYMBOL("INFERIOR-CLASSES",AB_package);
    Kb_specific_property_names = CONS(Qinferior_classes,
	    Kb_specific_property_names);
    mutate_global_property(Qinferior_classes,
	    Qcopy_list_using_class_description_conses_function,
	    Qfunction_to_copy_global_value_for_this_property_name);
    mutate_global_property(Qinferior_classes,
	    Qreclaim_class_description_list_function,
	    Qfunction_to_reclaim_kb_specific_property_value_qm);
    Inferior_classes_gkbprop = Qinferior_classes;
    Qclass_definition = STATIC_SYMBOL("CLASS-DEFINITION",AB_package);
    Kb_specific_property_names = CONS(Qclass_definition,
	    Kb_specific_property_names);
    Class_definition_gkbprop = Qclass_definition;
    Qdefinition_state = STATIC_SYMBOL("DEFINITION-STATE",AB_package);
    Kb_specific_property_names = CONS(Qdefinition_state,
	    Kb_specific_property_names);
    Definition_state_gkbprop = Qdefinition_state;
    string_constant = STATIC_STRING("~A::~A");
    Qdecomposed_class_qualified_symbol = 
	    STATIC_SYMBOL("DECOMPOSED-CLASS-QUALIFIED-SYMBOL",AB_package);
    Decomposed_class_qualified_symbol_prop = 
	    Qdecomposed_class_qualified_symbol;
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_slot_description_g2_struct = 
	    STATIC_SYMBOL("SLOT-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qslot_description = STATIC_SYMBOL("SLOT-DESCRIPTION",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_slot_description_g2_struct,
	    Qslot_description,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qslot_description,
	    Qg2_defstruct_structure_name_slot_description_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_slot_description == UNBOUND)
	The_type_description_of_slot_description = Nil;
    string_constant_5 = 
	    STATIC_STRING("43Dy8m83nFy1n83nFy8n8k1l8n0000001l1n8y83-5sy0kzk0k0");
    temp = The_type_description_of_slot_description;
    The_type_description_of_slot_description = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_5));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_slot_description_g2_struct,
	    The_type_description_of_slot_description,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qslot_description,
	    The_type_description_of_slot_description,
	    Qtype_description_of_type);
    Qoutstanding_slot_description_count = 
	    STATIC_SYMBOL("OUTSTANDING-SLOT-DESCRIPTION-COUNT",AB_package);
    Qslot_description_structure_memory_usage = 
	    STATIC_SYMBOL("SLOT-DESCRIPTION-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_6 = STATIC_STRING("1q83nFy8s83-q4y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_slot_description_count);
    push_optimized_constant(Qslot_description_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_6));
    Qchain_of_available_slot_descriptions = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-SLOT-DESCRIPTIONS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_slot_descriptions,
	    Chain_of_available_slot_descriptions);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_slot_descriptions,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qslot_description_count = STATIC_SYMBOL("SLOT-DESCRIPTION-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qslot_description_count,Slot_description_count);
    record_system_variable(Qslot_description_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_slot_descriptions_vector == UNBOUND)
	Chain_of_available_slot_descriptions_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qslot_description_structure_memory_usage,
	    STATIC_FUNCTION(slot_description_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_slot_description_count,
	    STATIC_FUNCTION(outstanding_slot_description_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_slot_description_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_slot_description,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qslot_description,
	    reclaim_structure_for_slot_description_1);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    if (Any_cached_evaluator_slot_info_p == UNBOUND)
	Any_cached_evaluator_slot_info_p = Nil;
    Qg2_defstruct_structure_name_evaluator_slot_info_g2_struct = 
	    STATIC_SYMBOL("EVALUATOR-SLOT-INFO-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qevaluator_slot_info = STATIC_SYMBOL("EVALUATOR-SLOT-INFO",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_evaluator_slot_info_g2_struct,
	    Qevaluator_slot_info,Qab_name_of_unique_structure_type);
    mutate_global_property(Qevaluator_slot_info,
	    Qg2_defstruct_structure_name_evaluator_slot_info_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_evaluator_slot_info == UNBOUND)
	The_type_description_of_evaluator_slot_info = Nil;
    string_constant_7 = 
	    STATIC_STRING("43Dy8m83h8y1n83h8y8n8k1l8n0000000ksk0k0");
    temp = The_type_description_of_evaluator_slot_info;
    The_type_description_of_evaluator_slot_info = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_7));
    mutate_global_property(Qg2_defstruct_structure_name_evaluator_slot_info_g2_struct,
	    The_type_description_of_evaluator_slot_info,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qevaluator_slot_info,
	    The_type_description_of_evaluator_slot_info,
	    Qtype_description_of_type);
    Qoutstanding_evaluator_slot_info_count = 
	    STATIC_SYMBOL("OUTSTANDING-EVALUATOR-SLOT-INFO-COUNT",AB_package);
    Qevaluator_slot_info_structure_memory_usage = 
	    STATIC_SYMBOL("EVALUATOR-SLOT-INFO-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_8 = STATIC_STRING("1q83h8y8s83-T1y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_evaluator_slot_info_count);
    push_optimized_constant(Qevaluator_slot_info_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_8));
    Qchain_of_available_evaluator_slot_infos = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-EVALUATOR-SLOT-INFOS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_evaluator_slot_infos,
	    Chain_of_available_evaluator_slot_infos);
    record_system_variable(Qchain_of_available_evaluator_slot_infos,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qevaluator_slot_info_count = STATIC_SYMBOL("EVALUATOR-SLOT-INFO-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qevaluator_slot_info_count,
	    Evaluator_slot_info_count);
    record_system_variable(Qevaluator_slot_info_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_evaluator_slot_infos_vector == UNBOUND)
	Chain_of_available_evaluator_slot_infos_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qevaluator_slot_info_structure_memory_usage,
	    STATIC_FUNCTION(evaluator_slot_info_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_evaluator_slot_info_count,
	    STATIC_FUNCTION(outstanding_evaluator_slot_info_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_evaluator_slot_info_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_evaluator_slot_info,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qevaluator_slot_info,
	    reclaim_structure_for_evaluator_slot_info_1);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    mutate_global_property(Qg2_defstruct_structure_name_class_description_g2_struct,
	    Qclass_description,Qab_name_of_unique_structure_type);
    mutate_global_property(Qclass_description,
	    Qg2_defstruct_structure_name_class_description_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_class_description == UNBOUND)
	The_type_description_of_class_description = Nil;
    string_constant_9 = 
	    STATIC_STRING("43Dy8m836fy1n836fy8n8k1l8n0000001l1n8y83-39y0k3Lyk0k0");
    temp = The_type_description_of_class_description;
    The_type_description_of_class_description = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_9));
    mutate_global_property(Qg2_defstruct_structure_name_class_description_g2_struct,
	    The_type_description_of_class_description,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qclass_description,
	    The_type_description_of_class_description,
	    Qtype_description_of_type);
    Qoutstanding_class_description_count = 
	    STATIC_SYMBOL("OUTSTANDING-CLASS-DESCRIPTION-COUNT",AB_package);
    Qclass_description_structure_memory_usage = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_10 = STATIC_STRING("1q836fy8s83-MXy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_class_description_count);
    push_optimized_constant(Qclass_description_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_10));
    Qchain_of_available_class_descriptions = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-CLASS-DESCRIPTIONS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_class_descriptions,
	    Chain_of_available_class_descriptions);
    record_system_variable(Qchain_of_available_class_descriptions,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qclass_description_count = STATIC_SYMBOL("CLASS-DESCRIPTION-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qclass_description_count,
	    Class_description_count);
    record_system_variable(Qclass_description_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_class_descriptions_vector == UNBOUND)
	Chain_of_available_class_descriptions_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qclass_description_structure_memory_usage,
	    STATIC_FUNCTION(class_description_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_class_description_count,
	    STATIC_FUNCTION(outstanding_class_description_count,NIL,FALSE,
	    0,0));
    reclaim_structure_for_class_description_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_class_description,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qclass_description,
	    reclaim_structure_for_class_description_1);
    Class_description_variable_alist = Nil;
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qslot_category = STATIC_SYMBOL("SLOT-CATEGORY",AB_package);
    Slot_category_prop = Qslot_category;
    Authorized_system_slots = Nil;
    if (Class_is_undergoing_inheritance_change_qm == UNBOUND)
	Class_is_undergoing_inheritance_change_qm = Nil;
    Qslot_hash = STATIC_SYMBOL("SLOT-HASH",AB_package);
    Qclass_bit_numbers_pool = STATIC_SYMBOL("CLASS-BIT-NUMBERS-POOL",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qclass_bit_numbers_pool,Class_bit_numbers_pool);
    Qreclaim_frame_list_function = 
	    STATIC_SYMBOL("RECLAIM-FRAME-LIST-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_frame_list_function,
	    STATIC_FUNCTION(reclaim_frame_list_function,NIL,FALSE,1,1));
    record_system_variable(Qclass_bit_numbers_pool,Qframes1,Nil,Qnil,Qt,
	    Qreclaim_frame_list_function,Qt);
    Qdefine_predicate = STATIC_SYMBOL("DEFINE-PREDICATE",AB_package);
    Qdo_not_put_in_menus = STATIC_SYMBOL("DO-NOT-PUT-IN-MENUS",AB_package);
    Qnot_user_instantiable = STATIC_SYMBOL("NOT-USER-INSTANTIABLE",AB_package);
    Qnot_solely_instantiable = STATIC_SYMBOL("NOT-SOLELY-INSTANTIABLE",
	    AB_package);
    Qfoundation_class = STATIC_SYMBOL("FOUNDATION-CLASS",AB_package);
    Qstubs = STATIC_SYMBOL("STUBS",AB_package);
    Qattribute_displays = STATIC_SYMBOL("ATTRIBUTE-DISPLAYS",AB_package);
    Qhas_indexed_attributes = STATIC_SYMBOL("HAS-INDEXED-ATTRIBUTES",
	    AB_package);
    Qdisjoint_from = STATIC_SYMBOL("DISJOINT-FROM",AB_package);
    Qonly_compatible_with = STATIC_SYMBOL("ONLY-COMPATIBLE-WITH",AB_package);
    Qclass_export_comment = STATIC_SYMBOL("CLASS-EXPORT-COMMENT",AB_package);
    Qnot_normally_transient = STATIC_SYMBOL("NOT-NORMALLY-TRANSIENT",
	    AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)12L,Qdefine_predicate,
	    Qdo_not_put_in_menus,Qnot_user_instantiable,
	    Qnot_solely_instantiable,Qfoundation_class,Qstubs,
	    Qattribute_displays,Qhas_indexed_attributes,Qdisjoint_from,
	    Qonly_compatible_with,Qclass_export_comment,
	    Qnot_normally_transient);
    Global_class_features = list_constant_3;
    Qlookup_slot = STATIC_SYMBOL("LOOKUP-SLOT",AB_package);
    Qvector_slot = STATIC_SYMBOL("VECTOR-SLOT",AB_package);
    Qno_accessor = STATIC_SYMBOL("NO-ACCESSOR",AB_package);
    Qsave = STATIC_SYMBOL("SAVE",AB_package);
    Qdo_not_save = STATIC_SYMBOL("DO-NOT-SAVE",AB_package);
    Qsystem = STATIC_SYMBOL("SYSTEM",AB_package);
    Qclass_of_optional_subframe = 
	    STATIC_SYMBOL("CLASS-OF-OPTIONAL-SUBFRAME",AB_package);
    Qdo_not_identify_in_attribute_tables = 
	    STATIC_SYMBOL("DO-NOT-IDENTIFY-IN-ATTRIBUTE-TABLES",AB_package);
    Qdo_not_put_in_attribute_tables = 
	    STATIC_SYMBOL("DO-NOT-PUT-IN-ATTRIBUTE-TABLES",AB_package);
    Qnupec = STATIC_SYMBOL("NUPEC",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)2L,
	    Qdo_not_put_in_attribute_tables,Qnupec);
    Qnot_nupec = STATIC_SYMBOL("NOT-NUPEC",AB_package);
    list_constant_5 = STATIC_LIST((SI_Long)2L,
	    Qdo_not_put_in_attribute_tables,Qnot_nupec);
    Qnot_ent = STATIC_SYMBOL("NOT-ENT",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)2L,
	    Qdo_not_put_in_attribute_tables,Qnot_ent);
    Qdo_not_put_in_attribute_tables_if_null = 
	    STATIC_SYMBOL("DO-NOT-PUT-IN-ATTRIBUTE-TABLES-IF-NULL",AB_package);
    Quser_overridable = STATIC_SYMBOL("USER-OVERRIDABLE",AB_package);
    Qclass_slot = STATIC_SYMBOL("CLASS-SLOT",AB_package);
    Qnot_user_editable = STATIC_SYMBOL("NOT-USER-EDITABLE",AB_package);
    Qedit_only = STATIC_SYMBOL("EDIT-ONLY",AB_package);
    Qdo_not_clone = STATIC_SYMBOL("DO-NOT-CLONE",AB_package);
    Qselect_changes = STATIC_SYMBOL("SELECT-CHANGES",AB_package);
    Qnote_slot_changes = STATIC_SYMBOL("NOTE-SLOT-CHANGES",AB_package);
    Qpreviously_put_in_attribute_tables = 
	    STATIC_SYMBOL("PREVIOUSLY-PUT-IN-ATTRIBUTE-TABLES",AB_package);
    Qattribute_export_comment = STATIC_SYMBOL("ATTRIBUTE-EXPORT-COMMENT",
	    AB_package);
    Qnamelike_slot = STATIC_SYMBOL("NAMELIKE-SLOT",AB_package);
    Qformat_override = STATIC_SYMBOL("FORMAT-OVERRIDE",AB_package);
    Qlocal_name_or_names = STATIC_SYMBOL("LOCAL-NAME-OR-NAMES",AB_package);
    list_constant_7 = STATIC_LIST((SI_Long)26L,Qlookup_slot,Qvector_slot,
	    Qno_accessor,Qtype,Qsave,Qdo_not_save,Qsystem,
	    Qclass_of_optional_subframe,
	    Qdo_not_identify_in_attribute_tables,
	    Qdo_not_put_in_attribute_tables,list_constant_4,
	    list_constant_5,list_constant_6,
	    Qdo_not_put_in_attribute_tables_if_null,Quser_overridable,
	    Qclass_slot,Qnot_user_editable,Qedit_only,Qdo_not_clone,
	    Qselect_changes,Qnote_slot_changes,
	    Qpreviously_put_in_attribute_tables,Qattribute_export_comment,
	    Qnamelike_slot,Qformat_override,Qlocal_name_or_names);
    Global_slot_features = list_constant_7;
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qobject_definition = STATIC_SYMBOL("OBJECT-DEFINITION",AB_package);
    Qdrawing_parameters = STATIC_SYMBOL("DRAWING-PARAMETERS",AB_package);
    Kfuncall_at_load_time = STATIC_SYMBOL("FUNCALL-AT-LOAD-TIME",Pkeyword);
    list_constant = STATIC_LIST((SI_Long)2L,Kfuncall,Kfuncall_at_load_time);
    string_constant_1 = STATIC_STRING("VECTOR-SLOT");
    string_constant_2 = STATIC_STRING("LOOKUP-SLOT");
    Qcreate_icon_description_if_valid = 
	    STATIC_SYMBOL("CREATE-ICON-DESCRIPTION-IF-VALID",AB_package);
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    Slot_putter_prop = Qslot_putter;
    Qclass_slot_description_updater = 
	    STATIC_SYMBOL("CLASS-SLOT-DESCRIPTION-UPDATER",AB_package);
    Class_slot_description_updater_prop = Qclass_slot_description_updater;
}
