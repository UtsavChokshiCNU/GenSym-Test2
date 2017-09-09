/* win1.c
 * Input file:  windows1.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "win1.h"


DEFINE_VARIABLE_WITH_SYMBOL(Defer_notifications_qm, Qdefer_notifications_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Available_graphics_conses, Qavailable_graphics_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_graphics_conses_tail, Qavailable_graphics_conses_tail);

Object Available_graphics_conses_vector = UNBOUND;

Object Available_graphics_conses_tail_vector = UNBOUND;

Object Graphics_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Graphics_cons_counter, Qgraphics_cons_counter);

/* OUTSTANDING-GRAPHICS-CONSES */
Object outstanding_graphics_conses()
{
    Object temp;

    x_note_fn_call(55,0);
    temp = FIXNUM_MINUS(Graphics_cons_counter,
	    length(Available_graphics_conses));
    return VALUES_1(temp);
}

/* GRAPHICS-CONS-MEMORY-USAGE */
Object graphics_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(55,1);
    temp = FIXNUM_TIMES(Graphics_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-GRAPHICS-CONS-POOL */
Object replenish_graphics_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(55,2);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qgraphics_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_graphics_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_graphics_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_graphics_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_graphics_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_graphics_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Graphics_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qgraphics;           /* graphics */

/* GRAPHICS-CONS-1 */
Object graphics_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(55,3);
    new_cons = ISVREF(Available_graphics_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_graphics_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_graphics_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_graphics_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_graphics_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qgraphics);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-GRAPHICS-LIST-POOL */
Object replenish_graphics_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(55,4);
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
    if (ISVREF(Available_graphics_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_graphics_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_graphics_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_graphics_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_graphics_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qgraphics_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-GRAPHICS-LIST-1 */
Object make_graphics_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(55,5);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_graphics_conses_vector,
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
	replenish_graphics_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_graphics_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qgraphics);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_graphics_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_graphics_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_graphics_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_graphics_conses_tail_vector;
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

/* GRAPHICS-LIST-2 */
Object graphics_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(55,6);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_graphics_conses_vector,IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_graphics_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_graphics_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qgraphics);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_graphics_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_graphics_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_graphics_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_graphics_conses_tail_vector;
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

/* GRAPHICS-LIST-3 */
Object graphics_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(55,7);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_graphics_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_graphics_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_graphics_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qgraphics);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_graphics_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_graphics_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_graphics_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_graphics_conses_tail_vector;
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

/* GRAPHICS-LIST-4 */
Object graphics_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(55,8);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_graphics_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_graphics_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_graphics_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qgraphics);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_graphics_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_graphics_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_graphics_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_graphics_conses_tail_vector;
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

/* GRAPHICS-LIST-TRACE-HOOK */
Object graphics_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(55,9);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-GRAPHICS-CONSES-1 */
Object copy_tree_using_graphics_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(55,10);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_graphics_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_graphics_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_graphics_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_graphics_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_graphics_cons_pool();
	temp_1 = copy_tree_using_graphics_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qgraphics);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_graphics_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_graphics_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_graphics_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_graphics_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_graphics_cons_pool();
	temp_1 = copy_tree_using_graphics_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qgraphics);
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

/* COPY-LIST-USING-GRAPHICS-CONSES-1 */
Object copy_list_using_graphics_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(55,11);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_graphics_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_graphics_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_graphics_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_graphics_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_graphics_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qgraphics);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_graphics_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_graphics_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_graphics_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_graphics_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_graphics_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qgraphics);
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

/* RECLAIM-GRAPHICS-CONS-1 */
Object reclaim_graphics_cons_1(graphics_cons)
    Object graphics_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(55,12);
    inline_note_reclaim_cons(graphics_cons,Qgraphics);
    if (ISVREF(Available_graphics_conses_tail_vector,
	    IFIX(Current_thread_index))) {
	temp = ISVREF(Available_graphics_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = graphics_cons;
	temp = Available_graphics_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = graphics_cons;
    }
    else {
	temp = Available_graphics_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = graphics_cons;
	temp = Available_graphics_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = graphics_cons;
    }
    M_CDR(graphics_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-GRAPHICS-LIST-1 */
Object reclaim_graphics_list_1(graphics_list)
    Object graphics_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(55,13);
    if (graphics_list) {
	last_1 = graphics_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qgraphics);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qgraphics);
	if (ISVREF(Available_graphics_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_graphics_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = graphics_list;
	    temp = Available_graphics_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_graphics_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = graphics_list;
	    temp = Available_graphics_conses_tail_vector;
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

/* RECLAIM-GRAPHICS-LIST*-1 */
Object reclaim_graphics_list_star_1(graphics_list)
    Object graphics_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(55,14);
    if (CONSP(graphics_list)) {
	temp = last(graphics_list,_);
	M_CDR(temp) = Nil;
	if (graphics_list) {
	    last_1 = graphics_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qgraphics);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qgraphics);
	    if (ISVREF(Available_graphics_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_graphics_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = graphics_list;
		temp = Available_graphics_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_graphics_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = graphics_list;
		temp = Available_graphics_conses_tail_vector;
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

/* RECLAIM-GRAPHICS-TREE-1 */
Object reclaim_graphics_tree_1(tree)
    Object tree;
{
    Object e, e2, graphics_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(55,15);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_graphics_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		graphics_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(graphics_cons,Qgraphics);
		if (EQ(graphics_cons,e))
		    goto end_1;
		else if ( !TRUEP(graphics_cons))
		    goto end_1;
		else
		    graphics_cons = CDR(graphics_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_graphics_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_graphics_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_graphics_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_graphics_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_graphics_conses_tail_vector;
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

/* DELETE-GRAPHICS-ELEMENT-1 */
Object delete_graphics_element_1(element,graphics_list)
    Object element, graphics_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(55,16);
    if (graphics_list) {
	if (EQ(element,M_CAR(graphics_list))) {
	    temp = CDR(graphics_list);
	    inline_note_reclaim_cons(graphics_list,Qgraphics);
	    if (ISVREF(Available_graphics_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_graphics_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = graphics_list;
		temp_1 = Available_graphics_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = graphics_list;
	    }
	    else {
		temp_1 = Available_graphics_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = graphics_list;
		temp_1 = Available_graphics_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = graphics_list;
	    }
	    M_CDR(graphics_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = graphics_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qgraphics);
		if (ISVREF(Available_graphics_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_graphics_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_graphics_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_graphics_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_graphics_conses_tail_vector;
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
	    temp = graphics_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-GRAPHICS-CONS-1 */
Object delete_graphics_cons_1(graphics_cons,graphics_list)
    Object graphics_cons, graphics_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(55,17);
    if (EQ(graphics_cons,graphics_list))
	temp = CDR(graphics_list);
    else {
	l_trailer_qm = Nil;
	l = graphics_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,graphics_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = graphics_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_graphics_cons_1(graphics_cons);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(G2_has_v5_mode_windows_p, Qg2_has_v5_mode_windows_p);

/* INITIALIZE-V5-MODE */
Object initialize_v5_mode()
{
    x_note_fn_call(55,18);
    return set_v5_mode_state(v5_mode_option_specified_p());
}

static Object array_constant;      /* # */

/* V5-MODE-OPTION-SPECIFIED-P */
Object v5_mode_option_specified_p()
{
    x_note_fn_call(55,19);
    return VALUES_1(get_command_line_flag_argument(1,array_constant) ? T : 
	    Nil);
}

/* SET-V5-MODE-STATE */
Object set_v5_mode_state(state_1)
    Object state_1;
{
    x_note_fn_call(55,20);
    G2_has_v5_mode_windows_p = state_1;
    return VALUES_1(G2_has_v5_mode_windows_p);
}

DEFINE_VARIABLE_WITH_SYMBOL(Trace_image_planes_p, Qtrace_image_planes_p);

/* BITMAP-MEMORY-USED */
Object bitmap_memory_used(width,height,depth)
    Object width, height, depth;
{
    SI_Long temp;

    x_note_fn_call(55,21);
    temp = (IFIX(timesn(3,width,depth,height)) + ((SI_Long)8L - 
	    (SI_Long)1L)) / (SI_Long)8L;
    return add(FIX((SI_Long)16L),FIX(temp));
}

/* ICON-BITMAP-MEMORY-USED */
Object icon_bitmap_memory_used(size)
    Object size;
{
    x_note_fn_call(55,22);
    return bitmap_memory_used(size,size,FIX((SI_Long)1L));
}

/* CONVERT-RASTER-SIZES-TO-MEMORY-USED */
Object convert_raster_sizes_to_memory_used(raster_sizes)
    Object raster_sizes;
{
    Object list0, result_1, last_1, temp, new_last;

    x_note_fn_call(55,23);
    list0 = raster_sizes;
    result_1 = Nil;
    last_1 = Nil;
    for ( ; ! !TRUEP(list0); list0 = CDR(list0)) {
	temp = icon_bitmap_memory_used(CAR(list0));
	new_last = CONS(temp,Nil);
	if (result_1)
	    M_CDR(last_1) = new_last;
	else
	    result_1 = new_last;
	last_1 = new_last;
    }
    return VALUES_1(result_1);
}

Object List_of_regular_raster_sizes = UNBOUND;

Object List_of_regular_raster_memory_usage = UNBOUND;

Object Number_of_regular_raster_sizes = UNBOUND;

Object Largest_regular_raster_size = UNBOUND;

Object Largest_regular_raster_size_index = UNBOUND;

Object Deepest_depth = UNBOUND;

Object Minimum_tile_size_for_icons = UNBOUND;

Object Minimum_index_for_icons = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Default_maximum_icon_bitmaps, Qdefault_maximum_icon_bitmaps);

DEFINE_VARIABLE_WITH_SYMBOL(Default_maximum_icon_bitmap_memory, Qdefault_maximum_icon_bitmap_memory);

Object Default_image_palette = UNBOUND;

/* DEFAULT-VALUE-FOR-IMAGE-PALETTE */
Object default_value_for_image_palette()
{
    x_note_fn_call(55,24);
    return VALUES_1(Default_image_palette);
}

/* COPY-GENSYM-WINDOW-PARAMETERS-PLIST */
Object copy_gensym_window_parameters_plist(plist)
    Object plist;
{
    x_note_fn_call(55,25);
    return copy_gensym_tree_with_text_strings(plist);
}

/* RECLAIM-GENSYM-WINDOW-PARAMETERS-PLIST */
Object reclaim_gensym_window_parameters_plist(plist)
    Object plist;
{
    x_note_fn_call(55,26);
    return reclaim_gensym_tree_with_text_strings(plist);
}

Object The_type_description_of_gensym_window = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_gensym_windows, Qchain_of_available_gensym_windows);

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_window_count, Qgensym_window_count);

Object Chain_of_available_gensym_windows_vector = UNBOUND;

/* GENSYM-WINDOW-STRUCTURE-MEMORY-USAGE */
Object gensym_window_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(55,27);
    temp = Gensym_window_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)70L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-GENSYM-WINDOW-COUNT */
Object outstanding_gensym_window_count()
{
    Object def_structure_gensym_window_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(55,28);
    gensymed_symbol = IFIX(Gensym_window_count);
    def_structure_gensym_window_variable = Chain_of_available_gensym_windows;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_gensym_window_variable))
	goto end_loop;
    def_structure_gensym_window_variable = 
	    ISVREF(def_structure_gensym_window_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-GENSYM-WINDOW-INTERNAL-1 */
Object reclaim_gensym_window_internal_1(gensym_window)
    Object gensym_window;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(55,29);
    inline_note_reclaim_cons(gensym_window,Nil);
    structure_being_reclaimed = gensym_window;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_panes_in_window_if_g2(ISVREF(gensym_window,(SI_Long)3L));
      SVREF(gensym_window,FIX((SI_Long)3L)) = Nil;
      reclaim_panes_in_window_if_g2(ISVREF(gensym_window,(SI_Long)4L));
      SVREF(gensym_window,FIX((SI_Long)4L)) = Nil;
      reclaim_gensym_tree_with_text_strings(ISVREF(gensym_window,
	      (SI_Long)19L));
      SVREF(gensym_window,FIX((SI_Long)19L)) = Nil;
      reclaim_color_map_if_any(ISVREF(gensym_window,(SI_Long)20L));
      SVREF(gensym_window,FIX((SI_Long)20L)) = Nil;
      reclaim_default_pane_background_color_or_tiling_pattern(ISVREF(gensym_window,
	      (SI_Long)21L));
      SVREF(gensym_window,FIX((SI_Long)21L)) = Nil;
      reclaim_managed_simple_vector(ISVREF(gensym_window,(SI_Long)25L));
      SVREF(gensym_window,FIX((SI_Long)25L)) = Nil;
      reclaim_managed_simple_vector(ISVREF(gensym_window,(SI_Long)26L));
      SVREF(gensym_window,FIX((SI_Long)26L)) = Nil;
      reclaim_graphics_list_1(ISVREF(gensym_window,(SI_Long)27L));
      SVREF(gensym_window,FIX((SI_Long)27L)) = Nil;
      reclaim_graphics_list_1(ISVREF(gensym_window,(SI_Long)28L));
      SVREF(gensym_window,FIX((SI_Long)28L)) = Nil;
      cancel_list_of_pending_activity(ISVREF(gensym_window,(SI_Long)34L));
      SVREF(gensym_window,FIX((SI_Long)34L)) = Nil;
      reclaim_pixmap(ISVREF(gensym_window,(SI_Long)46L));
      SVREF(gensym_window,FIX((SI_Long)46L)) = Nil;
      reclaim_local_event_queue(ISVREF(gensym_window,(SI_Long)47L));
      SVREF(gensym_window,FIX((SI_Long)47L)) = Nil;
      reclaim_local_event_queue(ISVREF(gensym_window,(SI_Long)48L));
      SVREF(gensym_window,FIX((SI_Long)48L)) = Nil;
      reclaim_local_event_queue(ISVREF(gensym_window,(SI_Long)49L));
      SVREF(gensym_window,FIX((SI_Long)49L)) = Nil;
      reclaim_native_menu_table(ISVREF(gensym_window,(SI_Long)50L));
      SVREF(gensym_window,FIX((SI_Long)50L)) = Nil;
      nms_reclaim_menu_table(ISVREF(gensym_window,(SI_Long)52L));
      SVREF(gensym_window,FIX((SI_Long)52L)) = Nil;
      reclaim_native_icons_table(ISVREF(gensym_window,(SI_Long)57L));
      SVREF(gensym_window,FIX((SI_Long)57L)) = Nil;
      reclaim_gensym_list_1(ISVREF(gensym_window,(SI_Long)58L));
      SVREF(gensym_window,FIX((SI_Long)58L)) = Nil;
      reclaim_pixmap(ISVREF(gensym_window,(SI_Long)60L));
      SVREF(gensym_window,FIX((SI_Long)60L)) = Nil;
      reclaim_pixmap(ISVREF(gensym_window,(SI_Long)61L));
      SVREF(gensym_window,FIX((SI_Long)61L)) = Nil;
      reclaim_native_windows(ISVREF(gensym_window,(SI_Long)63L));
      SVREF(gensym_window,FIX((SI_Long)63L)) = Nil;
      reclaim_gensym_tree_with_text_strings(ISVREF(gensym_window,
	      (SI_Long)64L));
      SVREF(gensym_window,FIX((SI_Long)64L)) = Nil;
      reclaim_gensym_list_1(ISVREF(gensym_window,(SI_Long)69L));
      SVREF(gensym_window,FIX((SI_Long)69L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_gensym_windows_vector,
	    IFIX(Current_thread_index));
    SVREF(gensym_window,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_gensym_windows_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = gensym_window;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GENSYM-WINDOW */
Object reclaim_structure_for_gensym_window(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(55,30);
    return reclaim_gensym_window_internal_1(gensym_window);
}

static Object Qg2_defstruct_structure_name_gensym_window_g2_struct;  /* g2-defstruct-structure-name::gensym-window-g2-struct */

/* MAKE-PERMANENT-GENSYM-WINDOW-STRUCTURE-INTERNAL */
Object make_permanent_gensym_window_structure_internal()
{
    Object def_structure_gensym_window_variable;
    Object defstruct_g2_gensym_window_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(55,31);
    def_structure_gensym_window_variable = Nil;
    atomic_incff_symval(Qgensym_window_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_gensym_window_variable = Nil;
	gensymed_symbol = (SI_Long)70L;
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
	defstruct_g2_gensym_window_variable = the_array;
	SVREF(defstruct_g2_gensym_window_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gensym_window_g2_struct;
	def_structure_gensym_window_variable = 
		defstruct_g2_gensym_window_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_gensym_window_variable);
}

static Object Qnative;             /* native */

static Object Kxor;                /* :xor */

static Object Qunknown;            /* unknown */

/* MAKE-GENSYM-WINDOW-INTERNAL-1 */
Object make_gensym_window_internal_1(native_window_qm)
    Object native_window_qm;
{
    Object def_structure_gensym_window_variable, temp, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(55,32);
    def_structure_gensym_window_variable = 
	    ISVREF(Chain_of_available_gensym_windows_vector,
	    IFIX(Current_thread_index));
    if (def_structure_gensym_window_variable) {
	temp = Chain_of_available_gensym_windows_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_gensym_window_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_gensym_window_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gensym_window_g2_struct;
    }
    else
	def_structure_gensym_window_variable = 
		make_permanent_gensym_window_structure_internal();
    inline_note_allocate_cons(def_structure_gensym_window_variable,Nil);
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)17L)) = 
	    native_window_qm;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)1L)) = Qnative;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)4L)) = Nil;
    ISVREF(def_structure_gensym_window_variable,(SI_Long)5L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_gensym_window_variable,(SI_Long)6L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)11L)) = 
	    Original_icp_window_protocol_version;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)13L)) = Nil;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)14L)) = Nil;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)15L)) = Nil;
    ISVREF(def_structure_gensym_window_variable,(SI_Long)16L) = 
	    FIX((SI_Long)3L);
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)19L)) = Nil;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)20L)) = Nil;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)21L)) = Nil;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)22L)) = Nil;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)23L)) = Qnative;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)24L)) = Qnative;
    temp = allocate_small_2d_array(FIX((SI_Long)14L));
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)25L)) = temp;
    temp = allocate_small_2d_array(FIX((SI_Long)14L));
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)26L)) = temp;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)27L)) = Nil;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)28L)) = Nil;
    ISVREF(def_structure_gensym_window_variable,(SI_Long)29L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)30L)) = Kxor;
    temp = Default_image_palette;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)31L)) = temp;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)32L)) = Nil;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)33L)) = Nil;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)34L)) = Nil;
    ISVREF(def_structure_gensym_window_variable,(SI_Long)35L) = 
	    FIX((SI_Long)8L);
    ISVREF(def_structure_gensym_window_variable,(SI_Long)36L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_gensym_window_variable,(SI_Long)37L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)38L)) = Nil;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)39L)) = Qunknown;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)40L)) = Qunknown;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)41L)) = Qunknown;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)42L)) = Qunknown;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)43L)) = Qunknown;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)44L)) = Qunknown;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)45L)) = Qunknown;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)46L)) = Nil;
    temp = make_queue();
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)47L)) = temp;
    temp = make_queue();
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)48L)) = temp;
    temp = make_queue();
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)49L)) = temp;
    temp = allocate_managed_array(1,FIX((SI_Long)1024L));
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)50L)) = temp;
    ISVREF(def_structure_gensym_window_variable,(SI_Long)51L) = 
	    FIX((SI_Long)-1L);
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)52L)) = Nil;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)53L)) = Nil;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)54L)) = Nil;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)55L)) = Nil;
    ISVREF(def_structure_gensym_window_variable,(SI_Long)56L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)57L)) = Nil;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)58L)) = Nil;
    ISVREF(def_structure_gensym_window_variable,(SI_Long)59L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)60L)) = Nil;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)61L)) = Nil;
    ISVREF(def_structure_gensym_window_variable,(SI_Long)62L) = 
	    FIX((SI_Long)1L);
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)63L)) = Nil;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)64L)) = Nil;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)65L)) = Nil;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)66L)) = Nil;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)67L)) = Nil;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)68L)) = Qunknown;
    SVREF(def_structure_gensym_window_variable,FIX((SI_Long)69L)) = Nil;
    return VALUES_1(def_structure_gensym_window_variable);
}

/* ADD-TWNG-DISCONNECT-CALLBACK */
Object add_twng_disconnect_callback(gensym_window,callback)
    Object gensym_window, callback;
{
    Object callback_qm, temp;

    x_note_fn_call(55,33);
    callback_qm = stored_callback_procedure(callback);
    if ( !( !TRUEP(callback_qm) || find(2,callback_qm,ISVREF(gensym_window,
	    (SI_Long)69L)))) {
	temp = nconc2(ISVREF(gensym_window,(SI_Long)69L),
		gensym_cons_1(callback_qm,Nil));
	SVREF(gensym_window,FIX((SI_Long)69L)) = temp;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* REMOVE-TWNG-DISCONNECT-CALLBACK */
Object remove_twng_disconnect_callback(gensym_window,callback)
    Object gensym_window, callback;
{
    Object callback_qm, cb, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, new_callbacks;

    x_note_fn_call(55,34);
    callback_qm = stored_callback_procedure(callback);
    cb = Nil;
    ab_loop_list_ = ISVREF(gensym_window,(SI_Long)69L);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    cb = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !EQL(cb,callback_qm)) {
	ab_loopvar__2 = gensym_cons_1(cb,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    new_callbacks = ab_loopvar_;
    goto end_1;
    new_callbacks = Qnil;
  end_1:;
    reclaim_gensym_list_1(ISVREF(gensym_window,(SI_Long)69L));
    return VALUES_1(SVREF(gensym_window,FIX((SI_Long)69L)) = new_callbacks);
}

/* CLEAR-TWNG-DISCONNECT-CALLBACKS */
Object clear_twng_disconnect_callbacks(gensym_window)
    Object gensym_window;
{
    Object temp;

    x_note_fn_call(55,35);
    if ( ! !TRUEP(ISVREF(gensym_window,(SI_Long)69L))) {
	reclaim_gensym_list_1(ISVREF(gensym_window,(SI_Long)69L));
	temp = SVREF(gensym_window,FIX((SI_Long)69L)) = Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_gensym_window_serial_number, Qcurrent_gensym_window_serial_number);

/* INCREMENT-CURRENT-GENSYM-WINDOW-SERIAL-NUMBER */
Object increment_current_gensym_window_serial_number()
{
    x_note_fn_call(55,36);
    Current_gensym_window_serial_number = 
	    FIXNUM_EQ(Current_gensym_window_serial_number,
	    Most_positive_fixnum) ? FIX((SI_Long)0L) : 
	    FIXNUM_ADD1(Current_gensym_window_serial_number);
    return VALUES_1(Current_gensym_window_serial_number);
}

/* MAKE-GENSYM-WINDOW */
Object make_gensym_window(native_window_qm)
    Object native_window_qm;
{
    Object gensym_window, svref_new_value;

    x_note_fn_call(55,37);
    gensym_window = make_gensym_window_internal_1(native_window_qm);
    svref_new_value = increment_current_gensym_window_serial_number();
    SVREF(gensym_window,FIX((SI_Long)51L)) = svref_new_value;
    return VALUES_1(gensym_window);
}

/* GENSYM-WINDOW-HAS-NOT-BEEN-REPROCESSED-P */
Object gensym_window_has_not_been_reprocessed_p(gensym_window,serial)
    Object gensym_window, serial;
{
    x_note_fn_call(55,38);
    if (FIXNUM_EQ(ISVREF(gensym_window,(SI_Long)51L),serial))
	return VALUES_1(IFIX(ISVREF(gensym_window,(SI_Long)51L)) != 
		(SI_Long)-1L ? T : Nil);
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Native_menu_table, Qnative_menu_table);

/* RECLAIM-NATIVE-MENU-TABLE */
Object reclaim_native_menu_table(native_menu_table)
    Object native_menu_table;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(55,39);
    PUSH_SPECIAL_WITH_SYMBOL(Native_menu_table,Qnative_menu_table,native_menu_table,
	    0);
      reclaim_contents_of_native_menu_table(Native_menu_table);
      result = reclaim_managed_array(Native_menu_table);
    POP_SPECIAL();
    return result;
}

/* NMS-RECLAIM-MENU-TABLE */
Object nms_reclaim_menu_table(table_qm)
    Object table_qm;
{
    x_note_fn_call(55,40);
    if (table_qm) {
	reclaim_contents_of_nms_menu_table(table_qm);
	return reclaim_managed_array(table_qm);
    }
    else
	return VALUES_1(Nil);
}

/* NMS-NOTE-MENU-DELETION */
Object nms_note_menu_deletion(gensym_window,menu_handle_being_deleted)
    Object gensym_window, menu_handle_being_deleted;
{
    Object temp_1;
    char temp;

    x_note_fn_call(55,41);
    temp = EQ(menu_handle_being_deleted,T);
    if (temp);
    else {
	temp_1 = ISVREF(gensym_window,(SI_Long)53L);
	temp = EQL(menu_handle_being_deleted,temp_1);
    }
    if (temp)
	SVREF(gensym_window,FIX((SI_Long)53L)) = Nil;
    temp = EQ(menu_handle_being_deleted,T);
    if (temp);
    else {
	temp_1 = ISVREF(gensym_window,(SI_Long)54L);
	temp = EQL(menu_handle_being_deleted,temp_1);
    }
    if (temp)
	SVREF(gensym_window,FIX((SI_Long)54L)) = Nil;
    temp = EQ(menu_handle_being_deleted,T);
    if (temp);
    else {
	temp_1 = ISVREF(gensym_window,(SI_Long)55L);
	temp = EQL(menu_handle_being_deleted,temp_1);
    }
    if (temp)
	return VALUES_1(SVREF(gensym_window,FIX((SI_Long)55L)) = Nil);
    else
	return VALUES_1(Nil);
}

/* GENSYM-WINDOW-SESSION-ID */
Object gensym_window_session_id(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(55,42);
    return VALUES_1(ISVREF(gensym_window,(SI_Long)51L));
}

/* FIND-GENSYM-WINDOW-WITH-SESSION-ID */
Object find_gensym_window_with_session_id(session_id)
    Object session_id;
{
    Object workstation, ab_loop_list_, gensym_window, temp;

    x_note_fn_call(55,43);
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
    gensym_window = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensym_window = ISVREF(workstation,(SI_Long)1L);
    temp = gensym_window_session_id(gensym_window);
    if (EQUAL(session_id,temp))
	return VALUES_1(gensym_window);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* GET-GENSYM-WINDOW-RESHAPE-EVENT-QUEUE */
Object get_gensym_window_reshape_event_queue(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(55,44);
    return VALUES_1(ISVREF(gensym_window,(SI_Long)48L));
}

/* GET-GENSYM-WINDOW-OF-NATIVE-WINDOW */
Object get_gensym_window_of_native_window(native_window_qm)
    Object native_window_qm;
{
    Object workstation, ab_loop_list_, temp;

    x_note_fn_call(55,45);
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = ISVREF(ISVREF(workstation,(SI_Long)1L),(SI_Long)17L);
    if (EQL(native_window_qm,temp))
	return VALUES_1(ISVREF(workstation,(SI_Long)1L));
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* GET-EVENT-QUEUE-OF-NATIVE-WINDOW */
Object get_event_queue_of_native_window(native_window_qm)
    Object native_window_qm;
{
    Object workstation, ab_loop_list_, temp;

    x_note_fn_call(55,46);
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = ISVREF(ISVREF(workstation,(SI_Long)1L),(SI_Long)17L);
    if (EQL(native_window_qm,temp))
	return VALUES_1(ISVREF(ISVREF(workstation,(SI_Long)1L),(SI_Long)47L));
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* GET-RESHAPE-EVENT-QUEUE-OF-NATIVE-WINDOW */
Object get_reshape_event_queue_of_native_window(native_window_qm)
    Object native_window_qm;
{
    Object workstation, ab_loop_list_, temp;

    x_note_fn_call(55,47);
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = ISVREF(ISVREF(workstation,(SI_Long)1L),(SI_Long)17L);
    if (EQL(native_window_qm,temp))
	return VALUES_1(ISVREF(ISVREF(workstation,(SI_Long)1L),(SI_Long)48L));
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* GET-PASTE-EVENT-QUEUE-OF-NATIVE-WINDOW */
Object get_paste_event_queue_of_native_window(native_window_qm)
    Object native_window_qm;
{
    Object workstation, ab_loop_list_, temp;

    x_note_fn_call(55,48);
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = ISVREF(ISVREF(workstation,(SI_Long)1L),(SI_Long)17L);
    if (EQL(native_window_qm,temp))
	return VALUES_1(ISVREF(ISVREF(workstation,(SI_Long)1L),(SI_Long)49L));
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* TIME-TO-DECACHE-P */
Object time_to_decache_p(gensym_window)
    Object gensym_window;
{
    Object temp;

    x_note_fn_call(55,49);
    temp = FIXNUM_GT(ISVREF(gensym_window,(SI_Long)36L),
	    Default_maximum_icon_bitmaps) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(FIXNUM_GT(ISVREF(gensym_window,(SI_Long)37L),
		Default_maximum_icon_bitmap_memory) ? T : Nil);
}

static Object Qno_native_clipboard;  /* no-native-clipboard */

/* WINDOW-SUPPORTS-REQUEST-FOR-PASTE-AVAILABILITY-FUNCTION */
Object window_supports_request_for_paste_availability_function(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(55,50);
    if (FIXNUM_LT(Icp_window_protocol_supports_request_for_paste_availability,
	    ISVREF(gensym_window,(SI_Long)11L)))
	return VALUES_1( !TRUEP(get_gensym_window_parameter(gensym_window,
		Qno_native_clipboard)) ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* CLOSE-NATIVE-WINDOW */
Object close_native_window()
{
    Object workstation, ab_loop_list_, native_window_qm;

    x_note_fn_call(55,51);
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
    native_window_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    native_window_qm = ISVREF(ISVREF(workstation,(SI_Long)1L),(SI_Long)17L);
    if (native_window_qm)
	g2ext_x11_close(IFIX(native_window_qm));
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

static Object list_constant;       /* # */

/* SLAVE-GENSYM-WINDOW? */
Object slave_gensym_window_qm(gensym_window)
    Object gensym_window;
{
    Object temp;

    x_note_fn_call(55,52);
    temp = memq_function(Current_system_name,list_constant);
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(ISVREF(gensym_window,(SI_Long)13L));
}

/* ICP-SOCKET-FOR-GENSYM-WINDOW? */
Object icp_socket_for_gensym_window_qm(gensym_window)
    Object gensym_window;
{
    Object icp_output_port_qm;

    x_note_fn_call(55,53);
    icp_output_port_qm = ISVREF(gensym_window,(SI_Long)12L);
    if (icp_output_port_qm)
	return VALUES_1(ISVREF(icp_output_port_qm,(SI_Long)2L));
    else
	return VALUES_1(Nil);
}

static Object Qprinter;            /* printer */

/* PRINTING-WINDOW-P */
Object printing_window_p(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(55,54);
    return VALUES_1(EQ(ISVREF(gensym_window,(SI_Long)1L),Qprinter) ? T : Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(X_debugging_on, Qx_debugging_on);

/* DEBUG-X11 */
Object debug_x11()
{
    x_note_fn_call(55,55);
    X_debugging_on =  !TRUEP(X_debugging_on) ? T : Nil;
    if (X_debugging_on)
	g2ext_x11_set_debug_mode(IFIX(ISVREF(System_window,(SI_Long)17L)));
    else
	g2ext_x11_clear_debug_mode(IFIX(ISVREF(System_window,(SI_Long)17L)));
    return VALUES_1(X_debugging_on);
}

static Object Qnetwork_host_name;  /* network-host-name */

/* GENSYM-WINDOW-HOST-NAME */
Object gensym_window_host_name(gensym_window)
    Object gensym_window;
{
    Object temp;

    x_note_fn_call(55,56);
    temp = getf(ISVREF(gensym_window,(SI_Long)19L),Qnetwork_host_name,_);
    if (temp)
	return VALUES_1(temp);
    else
	return get_local_host_name();
}

static Object Qos_type;            /* os-type */

/* GENSYM-WINDOW-OS-TYPE */
Object gensym_window_os_type(gensym_window)
    Object gensym_window;
{
    Object temp;

    x_note_fn_call(55,57);
    temp = getf(ISVREF(gensym_window,(SI_Long)19L),Qos_type,_);
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(G2_operating_system);
}

DEFINE_VARIABLE_WITH_SYMBOL(On_window_without_drawing, Qon_window_without_drawing);

DEFINE_VARIABLE_WITH_SYMBOL(Current_window, Qcurrent_window);

DEFINE_VARIABLE_WITH_SYMBOL(Drawing_on_window, Qdrawing_on_window);

DEFINE_VARIABLE_WITH_SYMBOL(Left_edge_of_draw_area, Qleft_edge_of_draw_area);

DEFINE_VARIABLE_WITH_SYMBOL(Top_edge_of_draw_area, Qtop_edge_of_draw_area);

DEFINE_VARIABLE_WITH_SYMBOL(Right_edge_of_draw_area, Qright_edge_of_draw_area);

DEFINE_VARIABLE_WITH_SYMBOL(Bottom_edge_of_draw_area, Qbottom_edge_of_draw_area);

DEFINE_VARIABLE_WITH_SYMBOL(Current_image_x_scale, Qcurrent_image_x_scale);

DEFINE_VARIABLE_WITH_SYMBOL(Current_image_y_scale, Qcurrent_image_y_scale);

DEFINE_VARIABLE_WITH_SYMBOL(Current_x_origin_of_drawing, Qcurrent_x_origin_of_drawing);

DEFINE_VARIABLE_WITH_SYMBOL(Current_y_origin_of_drawing, Qcurrent_y_origin_of_drawing);

DEFINE_VARIABLE_WITH_SYMBOL(Type_of_current_window, Qtype_of_current_window);

DEFINE_VARIABLE_WITH_SYMBOL(Current_native_window_qm, Qcurrent_native_window_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Current_color_map, Qcurrent_color_map);

DEFINE_VARIABLE_WITH_SYMBOL(Current_drawing_transfer_mode, Qcurrent_drawing_transfer_mode);

DEFINE_VARIABLE_WITH_SYMBOL(Current_background_color_value, Qcurrent_background_color_value);

DEFINE_VARIABLE_WITH_SYMBOL(Current_foreground_color_value, Qcurrent_foreground_color_value);

DEFINE_VARIABLE_WITH_SYMBOL(Current_pane, Qcurrent_pane);

DEFINE_VARIABLE_WITH_SYMBOL(Current_drawing_priority, Qcurrent_drawing_priority);

DEFINE_VARIABLE_WITH_SYMBOL(Current_draw_paper_p, Qcurrent_draw_paper_p);

DEFINE_VARIABLE_WITH_SYMBOL(Current_draw_document_p, Qcurrent_draw_document_p);

DEFINE_VARIABLE_WITH_SYMBOL(Workspace_for_current_draw_document_qm, Qworkspace_for_current_draw_document_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Currently_jump_out_of_drawing_image_plane_when_empty_rectangle_p, Qcurrently_jump_out_of_drawing_image_plane_when_empty_rectangle_p);

/* RECLAIM-WINDOW-FOR-WORKSTATION */
Object reclaim_window_for_workstation(gensym_window)
    Object gensym_window;
{
    Object current_window_1, delete_corresponding_object_qm, workstation_qm;
    Declare_special(2);

    x_note_fn_call(55,58);
    current_window_1 = gensym_window;
    delete_corresponding_object_qm = Nil;
    workstation_qm = ISVREF(gensym_window,(SI_Long)2L);
    PUSH_SPECIAL_WITH_SYMBOL(Delete_corresponding_object_qm,Qdelete_corresponding_object_qm,delete_corresponding_object_qm,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
	      0);
	Workstations_in_service = delete_eq(workstation_qm,
		Workstations_in_service);
	reclaim_icp_object_map_for_gensym_window(gensym_window);
	reclaim_panes_in_window_if_g2(ISVREF(gensym_window,(SI_Long)3L));
	SVREF(gensym_window,FIX((SI_Long)3L)) = Nil;
	reclaim_cached_structures_for_window(gensym_window);
	clear_all_image_renderings_for_window(gensym_window);
	hard_reclaim_all_reclaimed_stored_rasters(gensym_window);
      POP_SPECIAL();
    POP_SPECIAL();
    SVREF(gensym_window,FIX((SI_Long)12L)) = Nil;
    ISVREF(gensym_window,(SI_Long)51L) = FIX((SI_Long)-1L);
    return reclaim_gensym_window_internal_1(gensym_window);
}

DEFINE_VARIABLE_WITH_SYMBOL(On_window_with_drawing, Qon_window_with_drawing);

static Object Qicp;                /* icp */

/* WORKSTATION-DEAD-P */
Object workstation_dead_p(workstation)
    Object workstation;
{
    Object gensym_window_qm;

    x_note_fn_call(55,59);
    gensym_window_qm = ISVREF(workstation,(SI_Long)1L);
    if (gensym_window_qm && EQ(ISVREF(gensym_window_qm,(SI_Long)1L),Qicp))
	return VALUES_1( !TRUEP(ISVREF(gensym_window_qm,(SI_Long)12L)) ? T 
		: Nil);
    else
	return VALUES_1(Nil);
}

/* GET-GENSYM-WINDOW-PARAMETER */
Object get_gensym_window_parameter(gensym_window,parameter_name)
    Object gensym_window, parameter_name;
{
    Object list_1;

    x_note_fn_call(55,60);
    list_1 = ISVREF(gensym_window,(SI_Long)19L);
  next_loop:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),parameter_name))
	goto end_loop;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop;
  end_loop:
    if (list_1)
	return VALUES_1(M_CAR(M_CDR(list_1)));
    else
	return VALUES_1(Nil);
}

/* SET-GENSYM-WINDOW-PARAMETER */
Object set_gensym_window_parameter(gensym_window,parameter_name,new_value)
    Object gensym_window, parameter_name, new_value;
{
    Object svref_new_value;

    x_note_fn_call(55,61);
    svref_new_value = mutate_gensym_plist(ISVREF(gensym_window,
	    (SI_Long)19L),parameter_name,new_value);
    return VALUES_1(SVREF(gensym_window,FIX((SI_Long)19L)) = svref_new_value);
}

static Object Qsystem_metrics;     /* system-metrics */

/* GET-SYSTEM-METRIC */
Object get_system_metric varargs_1(int, n)
{
    Object gensym_window, index_1;
    Object default_1, system_metrics_qm, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(55,62);
    INIT_ARGS_nonrelocating();
    gensym_window = REQUIRED_ARG_nonrelocating();
    index_1 = REQUIRED_ARG_nonrelocating();
    default_1 = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    system_metrics_qm = get_gensym_window_parameter(gensym_window,
	    Qsystem_metrics);
    temp = system_metrics_qm && IFIX(index_1) >= (SI_Long)0L ? nth(index_1,
	    system_metrics_qm) : Nil;
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(default_1);
}

/* GET-UI-PROPERTY */
Object get_ui_property varargs_1(int, n)
{
    Object gensym_window, property_1;
    Object default_1, list_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(55,63);
    INIT_ARGS_nonrelocating();
    gensym_window = REQUIRED_ARG_nonrelocating();
    property_1 = REQUIRED_ARG_nonrelocating();
    default_1 = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    list_1 = ISVREF(gensym_window,(SI_Long)64L);
  next_loop:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),property_1))
	goto end_loop;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop;
  end_loop:
    if (list_1)
	return VALUES_1(M_CAR(M_CDR(list_1)));
    else
	return VALUES_1(default_1);
}

/* SET-UI-PROPERTY */
Object set_ui_property(gensym_window,property_1,pct_value)
    Object gensym_window, property_1, pct_value;
{
    Object svref_new_value;

    x_note_fn_call(55,64);
    svref_new_value = mutate_gensym_plist(ISVREF(gensym_window,
	    (SI_Long)64L),property_1,pct_value);
    return VALUES_1(SVREF(gensym_window,FIX((SI_Long)64L)) = svref_new_value);
}

/* REMOVE-UI-PROPERTY */
Object remove_ui_property(gensym_window,property_1)
    Object gensym_window, property_1;
{
    Object plist, previous_cons, head, property_2, value, rest_1, temp;

    x_note_fn_call(55,65);
    plist = ISVREF(gensym_window,(SI_Long)64L);
    previous_cons = Nil;
    head = plist;
    property_2 = Nil;
    value = Nil;
    rest_1 = Nil;
  next_loop:
    if ( !TRUEP(head))
	goto end_loop;
    property_2 = CAR(head);
    temp = CDR(head);
    value = CAR(temp);
    temp = CDR(head);
    rest_1 = CDR(temp);
    if (EQ(property_2,property_1)) {
	if (previous_cons)
	    M_CDR(previous_cons) = rest_1;
	reclaim_gensym_cons_1(CDR(head));
	reclaim_gensym_cons_1(head);
	if (previous_cons)
	    goto end_1;
	else {
	    plist = rest_1;
	    goto end_1;
	}
    }
    previous_cons = CDR(head);
    head = CDDR(head);
    goto next_loop;
  end_loop:
    goto end_1;
    plist = Qnil;
  end_1:;
    return VALUES_1(SVREF(gensym_window,FIX((SI_Long)64L)) = plist);
}

/* MAXIMUM-WINDOW-WIDTH */
Object maximum_window_width(gensym_window)
    Object gensym_window;
{
    Object cxmaxtrack_qm, cxframe_qm;

    x_note_fn_call(55,66);
    cxmaxtrack_qm = get_system_metric(2,gensym_window,Sm_cxmaxtrack);
    cxframe_qm = get_system_metric(2,gensym_window,Sm_cxframe);
    if (cxmaxtrack_qm && cxframe_qm)
	return VALUES_1(FIX(IFIX(cxmaxtrack_qm) - IFIX(cxframe_qm) * 
		(SI_Long)2L));
    else
	return VALUES_1(FIXNUM_MINUS(ISVREF(gensym_window,(SI_Long)9L),
		ISVREF(gensym_window,(SI_Long)7L)));
}

/* MAXIMUM-WINDOW-HEIGHT */
Object maximum_window_height(gensym_window)
    Object gensym_window;
{
    Object cymaxtrack_qm, cyframe_qm, cycaption_qm;

    x_note_fn_call(55,67);
    cymaxtrack_qm = get_system_metric(2,gensym_window,Sm_cymaxtrack);
    cyframe_qm = get_system_metric(2,gensym_window,Sm_cyframe);
    cycaption_qm = get_system_metric(2,gensym_window,Sm_cycaption);
    if (cymaxtrack_qm && cyframe_qm && cycaption_qm)
	return VALUES_1(FIX(IFIX(FIXNUM_MINUS(cymaxtrack_qm,cycaption_qm)) 
		- IFIX(cyframe_qm) * (SI_Long)2L));
    else
	return VALUES_1(FIXNUM_MINUS(ISVREF(gensym_window,(SI_Long)10L),
		ISVREF(gensym_window,(SI_Long)8L)));
}

DEFINE_VARIABLE_WITH_SYMBOL(Axis, Qaxis);

static Object Qx;                  /* x */

static Object Qy;                  /* y */

/* DIALOG-UNITS-TO-PIXELS */
Object dialog_units_to_pixels(gensym_window,dialog_units,axis)
    Object gensym_window, dialog_units, axis;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(55,68);
    PUSH_SPECIAL_WITH_SYMBOL(Axis,Qaxis,axis,0);
      if (EQ(Axis,Qx))
	  result = l_round(FIXNUM_TIMES(dialog_units,get_system_metric(3,
		  gensym_window,Sm_cxdialog,FIX((SI_Long)150L))),
		  FIX((SI_Long)100L));
      else if (EQ(Axis,Qy))
	  result = l_round(FIXNUM_TIMES(dialog_units,get_system_metric(3,
		  gensym_window,Sm_cydialog,FIX((SI_Long)163L))),
		  FIX((SI_Long)100L));
      else
	  result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object Qstandard_icp_object_index_space;  /* standard-icp-object-index-space */

static Object Qestablish_new_object_index_for_gensym_window;  /* establish-new-object-index-for-gensym-window */

static Object string_constant;     /* "resumable icp synch error: ~S expected, ~S found" */

/* ESTABLISH-NEW-OBJECT-INDEX-FOR-GENSYM-WINDOW */
Object establish_new_object_index_for_gensym_window varargs_1(int, n)
{
    Object gensym_window, icp_port;
    Object send_enlarge_message_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, svref_new_value, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(55,69);
    INIT_ARGS_nonrelocating();
    gensym_window = REQUIRED_ARG_nonrelocating();
    icp_port = REQUIRED_ARG_nonrelocating();
    send_enlarge_message_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    if (Disable_resumability) {
	result = assign_corresponding_icp_object_index(gensym_window,
		Qstandard_icp_object_index_space,send_enlarge_message_p);
	MVS_2(result,corresponding_icp_object_index,
		new_index_limit_plus_one_qm);
	svref_new_value = gensym_cons_1(icp_port,
		gensym_cons_1(corresponding_icp_object_index,
		ISVREF(gensym_window,(SI_Long)14L)));
	SVREF(gensym_window,FIX((SI_Long)14L)) = svref_new_value;
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
	    if ( !EQ(Qestablish_new_object_index_for_gensym_window,top))
		return icp_error_internal(Qerror,string_constant,
			Qestablish_new_object_index_for_gensym_window,top,Nil);
	}
	gensym_window = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : gensym_window;
	icp_port = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : icp_port;
	send_enlarge_message_p = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : send_enlarge_message_p;
	result = assign_corresponding_icp_object_index(gensym_window,
		Qstandard_icp_object_index_space,send_enlarge_message_p);
	MVS_2(result,corresponding_icp_object_index,
		new_index_limit_plus_one_qm);
	svref_new_value = gensym_cons_1(icp_port,
		gensym_cons_1(corresponding_icp_object_index,
		ISVREF(gensym_window,(SI_Long)14L)));
	SVREF(gensym_window,FIX((SI_Long)14L)) = svref_new_value;
	if (send_enlarge_message_p)
	    return VALUES_1(corresponding_icp_object_index);
	else
	    return VALUES_2(corresponding_icp_object_index,
		    new_index_limit_plus_one_qm);
    }
}

static Object Qtype_of_gensym_window;  /* type-of-gensym-window */

static Object Qscratchpad_raster_type_for_window;  /* scratchpad-raster-type-for-window */

static Object Qstored_raster_type_for_window;  /* stored-raster-type-for-window */

static Object Qmake_corresponding_icp_gensym_window;  /* make-corresponding-icp-gensym-window */

/* MAKE-CORRESPONDING-ICP-GENSYM-WINDOW */
Object make_corresponding_icp_gensym_window(gensym_window)
    Object gensym_window;
{
    Object writing_resumable_icp_messages_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, svref_new_value, temp;
    Object temporary_window_parameters_plist, resumable_icp_state_1;
    Object icp_suspend_1, top, v1, v2, v3;
    Declare_special(1);
    Object result;

    x_note_fn_call(55,70);
    if (Disable_resumability) {
	write_icp_maybe_suspend();
	writing_resumable_icp_messages_p = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Writing_resumable_icp_messages_p,Qwriting_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		0);
	  result = assign_corresponding_icp_object_index(gensym_window,
		  Qstandard_icp_object_index_space,T);
	  MVS_2(result,corresponding_icp_object_index,
		  new_index_limit_plus_one_qm);
	  svref_new_value = gensym_cons_1(Current_icp_port,
		  gensym_cons_1(corresponding_icp_object_index,
		  ISVREF(gensym_window,(SI_Long)14L)));
	  SVREF(gensym_window,FIX((SI_Long)14L)) = svref_new_value;
	  if (T);
	  else {
	      temp = corresponding_icp_object_index;
	      corresponding_icp_object_index = temp;
	  }
	  if ( !TRUEP(Inhibit_corresponding_icp_object_making)) {
	      temporary_window_parameters_plist = 
		      copy_tree_using_gensym_conses_1(ISVREF(gensym_window,
		      (SI_Long)19L));
	      mutate_gensym_plist(temporary_window_parameters_plist,
		      Qtype_of_gensym_window,Qicp);
	      mutate_gensym_plist(temporary_window_parameters_plist,
		      Qscratchpad_raster_type_for_window,Qicp);
	      mutate_gensym_plist(temporary_window_parameters_plist,
		      Qstored_raster_type_for_window,Qicp);
	      send_icp_define_gensym_window(corresponding_icp_object_index,
		      ISVREF(gensym_window,(SI_Long)7L),
		      ISVREF(gensym_window,(SI_Long)8L),
		      ISVREF(gensym_window,(SI_Long)9L),
		      ISVREF(gensym_window,(SI_Long)10L),
		      temporary_window_parameters_plist,
		      ISVREF(gensym_window,(SI_Long)15L));
	      reclaim_gensym_tree_1(temporary_window_parameters_plist);
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
	    if ( !EQ(Qmake_corresponding_icp_gensym_window,top))
		return icp_error_internal(Qerror,string_constant,
			Qmake_corresponding_icp_gensym_window,top,Nil);
	}
	gensym_window = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : gensym_window;
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
	      result = assign_corresponding_icp_object_index(gensym_window,
		      Qstandard_icp_object_index_space,T);
	      MVS_2(result,corresponding_icp_object_index,
		      new_index_limit_plus_one_qm);
	      svref_new_value = gensym_cons_1(Current_icp_port,
		      gensym_cons_1(corresponding_icp_object_index,
		      ISVREF(gensym_window,(SI_Long)14L)));
	      SVREF(gensym_window,FIX((SI_Long)14L)) = svref_new_value;
	      if (T);
	      else {
		  temp = corresponding_icp_object_index;
		  corresponding_icp_object_index = temp;
	      }
	  }
	  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) ||  
		  !TRUEP(Inhibit_corresponding_icp_object_making)) {
	      temporary_window_parameters_plist = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : 
		      copy_tree_using_gensym_conses_1(ISVREF(gensym_window,
		      (SI_Long)19L));
	      if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil))) {
		  mutate_gensym_plist(temporary_window_parameters_plist,
			  Qtype_of_gensym_window,Qicp);
		  mutate_gensym_plist(temporary_window_parameters_plist,
			  Qscratchpad_raster_type_for_window,Qicp);
		  mutate_gensym_plist(temporary_window_parameters_plist,
			  Qstored_raster_type_for_window,Qicp);
	      }
	      if (EQ(icp_suspend_1,
		      send_icp_define_gensym_window(corresponding_icp_object_index,
		      ISVREF(gensym_window,(SI_Long)7L),
		      ISVREF(gensym_window,(SI_Long)8L),
		      ISVREF(gensym_window,(SI_Long)9L),
		      ISVREF(gensym_window,(SI_Long)10L),
		      temporary_window_parameters_plist,
		      ISVREF(gensym_window,(SI_Long)15L)))) {
		  resumable_icp_push(temporary_window_parameters_plist);
		  resumable_icp_push(corresponding_icp_object_index);
		  resumable_icp_push(Writing_resumable_icp_messages_p);
		  resumable_icp_push(FIX((SI_Long)2L));
		  result = VALUES_1(Icp_suspend);
		  POP_SPECIAL();
		  goto end_block;
	      }
	      reclaim_gensym_tree_1(temporary_window_parameters_plist);
	  }
	  result = VALUES_1(corresponding_icp_object_index);
	POP_SPECIAL();
	goto end_block;
      end_block:
	MVS_3(result,v1,v2,v3);
	if (EQ(icp_suspend_1,v1)) {
	    resumable_icp_push(gensym_window);
	    resumable_icp_push(Qmake_corresponding_icp_gensym_window);
	    return VALUES_1(Icp_suspend);
	}
	return VALUES_3(v1,v2,v3);
    }
}

/* GET-ICP-OBJECT-INDEX-FOR-GENSYM-WINDOW */
Object get_icp_object_index_for_gensym_window(gensym_window,icp_port)
    Object gensym_window, icp_port;
{
    x_note_fn_call(55,71);
    return getfq_function_no_default(ISVREF(gensym_window,(SI_Long)14L),
	    icp_port);
}

/* SET-ICP-OBJECT-INDEX-FOR-GENSYM-WINDOW */
Object set_icp_object_index_for_gensym_window(gensym_window,
	    corresponding_icp_object_index,icp_port)
    Object gensym_window, corresponding_icp_object_index, icp_port;
{
    Object svref_new_value;

    x_note_fn_call(55,72);
    svref_new_value = gensym_cons_1(icp_port,
	    gensym_cons_1(corresponding_icp_object_index,
	    ISVREF(gensym_window,(SI_Long)14L)));
    return VALUES_1(SVREF(gensym_window,FIX((SI_Long)14L)) = svref_new_value);
}

/* RECLAIM-ICP-OBJECT-MAP-FOR-GENSYM-WINDOW */
Object reclaim_icp_object_map_for_gensym_window(gensym_window)
    Object gensym_window;
{
    Object icp_object_map;

    x_note_fn_call(55,73);
    icp_object_map = ISVREF(gensym_window,(SI_Long)14L);
    if (icp_object_map)
	return reclaim_icp_object_map(gensym_window,icp_object_map,
		Qstandard_icp_object_index_space);
    else
	return VALUES_1(Nil);
}

static Object Qset_access_form_for_gensym_window;  /* set-access-form-for-gensym-window */

/* RECLAIM-ICP-PORT-ENTRY-FOR-GENSYM-WINDOW */
Object reclaim_icp_port_entry_for_gensym_window(gensym_window,icp_port)
    Object gensym_window, icp_port;
{
    x_note_fn_call(55,74);
    return reclaim_icp_port_entry(icp_port,gensym_window,
	    ISVREF(gensym_window,(SI_Long)14L),
	    Qset_access_form_for_gensym_window);
}

/* SET-ACCESS-FORM-FOR-GENSYM-WINDOW */
Object set_access_form_for_gensym_window(gensym_window,new_value)
    Object gensym_window, new_value;
{
    x_note_fn_call(55,75);
    return VALUES_1(SVREF(gensym_window,FIX((SI_Long)14L)) = new_value);
}

static Object Qsend_icp_define_gensym_window;  /* send-icp-define-gensym-window */

static Object Qdefine_gensym_window;  /* define-gensym-window */

static Object string_constant_1;   /* "[message]" */

static Object Qmessage;            /* message */

static Object Qcorresponding_icp_object_index;  /* corresponding-icp-object-index */

static Object string_constant_2;   /* "[value arg]" */

static Object Qargument;           /* argument */

static Object Qleft_edge_in_window;  /* left-edge-in-window */

static Object Qtop_edge_in_window;  /* top-edge-in-window */

static Object Qright_edge_in_window;  /* right-edge-in-window */

static Object Qbottom_edge_in_window;  /* bottom-edge-in-window */

static Object Qwindow_parameters_plist;  /* window-parameters-plist */

static Object Qcorresponding_icp_object_index_on_other_side_qm;  /* corresponding-icp-object-index-on-other-side? */

/* SEND-ICP-DEFINE-GENSYM-WINDOW */
Object send_icp_define_gensym_window(corresponding_icp_object_index,
	    left_edge_in_window,top_edge_in_window,right_edge_in_window,
	    bottom_edge_in_window,window_parameters_plist,
	    corresponding_icp_object_index_on_other_side_qm)
    Object corresponding_icp_object_index, left_edge_in_window;
    Object top_edge_in_window, right_edge_in_window, bottom_edge_in_window;
    Object window_parameters_plist;
    Object corresponding_icp_object_index_on_other_side_qm;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(3);
    Object result;

    x_note_fn_call(55,76);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_define_gensym_window;
	  }
	  start_writing_icp_message(FIX((SI_Long)30L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qdefine_gensym_window,
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
				Qleft_edge_in_window,string_constant_2,
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
		      result_of_write = write_icp_integer(left_edge_in_window);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qleft_edge_in_window,string_constant_2,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_integer(left_edge_in_window);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qtop_edge_in_window,
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
		      result_of_write = write_icp_integer(top_edge_in_window);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qtop_edge_in_window,string_constant_2,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_integer(top_edge_in_window);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qright_edge_in_window,string_constant_2,
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
			      write_icp_integer(right_edge_in_window);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qright_edge_in_window,string_constant_2,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_integer(right_edge_in_window);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qbottom_edge_in_window,string_constant_2,
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
			      write_icp_integer(bottom_edge_in_window);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qbottom_edge_in_window,string_constant_2,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_integer(bottom_edge_in_window);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qwindow_parameters_plist,string_constant_2,
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
			      write_icp_list(window_parameters_plist);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qwindow_parameters_plist,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_list(window_parameters_plist);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qcorresponding_icp_object_index_on_other_side_qm,
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
			      write_icp_unsigned_integer_qm(corresponding_icp_object_index_on_other_side_qm);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qcorresponding_icp_object_index_on_other_side_qm,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_unsigned_integer_qm(corresponding_icp_object_index_on_other_side_qm);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qdefine_gensym_window,string_constant_1,
			    Qmessage,Nil,Nil,Nil,Nil);
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
		      emit_icp_write_trace(T,Nil,Nil,Qleft_edge_in_window,
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
		    result_of_write = write_icp_integer(left_edge_in_window);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qleft_edge_in_window,string_constant_2,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_integer(left_edge_in_window);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qtop_edge_in_window,
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
		    result_of_write = write_icp_integer(top_edge_in_window);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qtop_edge_in_window,string_constant_2,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_integer(top_edge_in_window);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qright_edge_in_window,
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
		    result_of_write = write_icp_integer(right_edge_in_window);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qright_edge_in_window,string_constant_2,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_integer(right_edge_in_window);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qbottom_edge_in_window,string_constant_2,
			      Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = write_icp_integer(bottom_edge_in_window);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qbottom_edge_in_window,string_constant_2,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_integer(bottom_edge_in_window);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qwindow_parameters_plist,string_constant_2,
			      Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = write_icp_list(window_parameters_plist);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qwindow_parameters_plist,string_constant_2,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_list(window_parameters_plist);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index_on_other_side_qm,
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
			    write_icp_unsigned_integer_qm(corresponding_icp_object_index_on_other_side_qm);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qcorresponding_icp_object_index_on_other_side_qm,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_unsigned_integer_qm(corresponding_icp_object_index_on_other_side_qm);
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_define_gensym_window,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qsend_icp_define_gensym_window,top,Nil);
		goto end_send_icp_define_gensym_window;
	    }
	}
	corresponding_icp_object_index = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : corresponding_icp_object_index;
	left_edge_in_window = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : left_edge_in_window;
	top_edge_in_window = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : top_edge_in_window;
	right_edge_in_window = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : right_edge_in_window;
	bottom_edge_in_window = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : bottom_edge_in_window;
	window_parameters_plist = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : window_parameters_plist;
	corresponding_icp_object_index_on_other_side_qm = 
		(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : 
		corresponding_icp_object_index_on_other_side_qm;
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_define_gensym_window;
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
	  if (EQ(icp_suspend_1,start_writing_icp_message(FIX((SI_Long)30L)))) {
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
		  emit_icp_write_trace(T,Nil,Nil,Qdefine_gensym_window,
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
				Qleft_edge_in_window,string_constant_2,
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
			      write_icp_integer(left_edge_in_window))) {
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
				  Qleft_edge_in_window,string_constant_2,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_integer(left_edge_in_window))) {
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
			emit_icp_write_trace(T,Nil,Nil,Qtop_edge_in_window,
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
			      write_icp_integer(top_edge_in_window))) {
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
				  Qtop_edge_in_window,string_constant_2,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_integer(top_edge_in_window))) {
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
				Qright_edge_in_window,string_constant_2,
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
			      write_icp_integer(right_edge_in_window))) {
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
				  Qright_edge_in_window,string_constant_2,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_integer(right_edge_in_window))) {
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
				Qbottom_edge_in_window,string_constant_2,
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
			      write_icp_integer(bottom_edge_in_window))) {
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
				  Qbottom_edge_in_window,string_constant_2,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_integer(bottom_edge_in_window))) {
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
				Qwindow_parameters_plist,string_constant_2,
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
			      write_icp_list(window_parameters_plist))) {
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
				  Qwindow_parameters_plist,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_list(window_parameters_plist))) {
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
				Qcorresponding_icp_object_index_on_other_side_qm,
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
			      write_icp_unsigned_integer_qm(corresponding_icp_object_index_on_other_side_qm))) 
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
				  Qcorresponding_icp_object_index_on_other_side_qm,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      temp_1 = result_of_write;
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_unsigned_integer_qm(corresponding_icp_object_index_on_other_side_qm))) 
			    {
		    resumable_icp_push(FIX((SI_Long)7L));
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
			    Qdefine_gensym_window,string_constant_1,
			    Qmessage,Nil,Nil,Nil,Nil);
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
		      emit_icp_write_trace(T,Nil,Nil,Qleft_edge_in_window,
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
			    write_icp_integer(left_edge_in_window))) {
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
				Qleft_edge_in_window,string_constant_2,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_integer(left_edge_in_window))) {
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
		      emit_icp_write_trace(T,Nil,Nil,Qtop_edge_in_window,
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
			    write_icp_integer(top_edge_in_window))) {
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
				Qtop_edge_in_window,string_constant_2,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
			  write_icp_integer(top_edge_in_window))) {
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
		      emit_icp_write_trace(T,Nil,Nil,Qright_edge_in_window,
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
			    write_icp_integer(right_edge_in_window))) {
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
				Qright_edge_in_window,string_constant_2,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_integer(right_edge_in_window))) {
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
			      Qbottom_edge_in_window,string_constant_2,
			      Qargument,Nil,Nil,Nil,Nil);
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
			    write_icp_integer(bottom_edge_in_window))) {
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
				Qbottom_edge_in_window,string_constant_2,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_integer(bottom_edge_in_window))) {
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
			      Qwindow_parameters_plist,string_constant_2,
			      Qargument,Nil,Nil,Nil,Nil);
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
			    write_icp_list(window_parameters_plist))) {
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
				Qwindow_parameters_plist,string_constant_2,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_list(window_parameters_plist))) {
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
			      Qcorresponding_icp_object_index_on_other_side_qm,
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
			    write_icp_unsigned_integer_qm(corresponding_icp_object_index_on_other_side_qm))) 
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
				Qcorresponding_icp_object_index_on_other_side_qm,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_unsigned_integer_qm(corresponding_icp_object_index_on_other_side_qm))) 
			  {
		  resumable_icp_push(FIX((SI_Long)7L));
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
	      resumable_icp_push(corresponding_icp_object_index_on_other_side_qm);
	      resumable_icp_push(window_parameters_plist);
	      resumable_icp_push(bottom_edge_in_window);
	      resumable_icp_push(right_edge_in_window);
	      resumable_icp_push(top_edge_in_window);
	      resumable_icp_push(left_edge_in_window);
	      resumable_icp_push(corresponding_icp_object_index);
	      resumable_icp_push(Qsend_icp_define_gensym_window);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_define_gensym_window;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_define_gensym_window:
    return result;
}

static Object Qicp_window_protocol_version;  /* icp-window-protocol-version */

/* HANDLE-ICP-DEFINE-GENSYM-WINDOW--BODY */
Object handle_icp_define_gensym_window__body(corresponding_icp_object_index,
	    left_edge_in_window,top_edge_in_window,right_edge_in_window,
	    bottom_edge_in_window,window_parameters_plist,
	    corresponding_icp_object_index_on_other_side_qm)
    Object corresponding_icp_object_index, left_edge_in_window;
    Object top_edge_in_window, right_edge_in_window, bottom_edge_in_window;
    Object window_parameters_plist;
    Object corresponding_icp_object_index_on_other_side_qm;
{
    Object temp, gensym_window, svref_new_value, major_version, minor_version;
    Object result;

    x_note_fn_call(55,77);
    if (corresponding_icp_object_index_on_other_side_qm) {
	temp = get_from_icp_port(ISVREF(Current_icp_socket,(SI_Long)4L),
		corresponding_icp_object_index_on_other_side_qm,
		Qstandard_icp_object_index_space);
	reclaim_gensym_tree_with_text_strings(window_parameters_plist);
    }
    else {
	gensym_window = make_or_revise_window(Nil,left_edge_in_window,
		top_edge_in_window,right_edge_in_window,
		bottom_edge_in_window,Nil,Nil,window_parameters_plist);
	svref_new_value = ISVREF(Current_icp_socket,(SI_Long)4L);
	SVREF(gensym_window,FIX((SI_Long)12L)) = svref_new_value;
	SVREF(gensym_window,FIX((SI_Long)15L)) = 
		corresponding_icp_object_index;
	obtain_max_window_protocol(gensym_window);
	establish_telewindows_license_level(gensym_window);
	result = decode_icp_window_protocol_version(getf(window_parameters_plist,
		Qicp_window_protocol_version,_));
	MVS_2(result,major_version,minor_version);
	maybe_update_remote_icp_version_info_for_version(Current_icp_socket,
		major_version,minor_version);
	temp = gensym_window;
    }
    store_corresponding_icp_object(corresponding_icp_object_index,temp);
    return VALUES_1(Nil);
}

static Object Qhandle_icp_define_gensym_window;  /* handle-icp-define-gensym-window */

static Object Qresumable_icp_list_end;  /* resumable-icp-list-end */

/* HANDLE-ICP-DEFINE-GENSYM-WINDOW */
Object handle_icp_define_gensym_window()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read, corresponding_icp_object_index;
    Object left_edge_in_window, top_edge_in_window, right_edge_in_window;
    Object bottom_edge_in_window, window_parameters_plist;
    Object corresponding_icp_object_index_on_other_side_qm;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(55,78);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qdefine_gensym_window,
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
		      emit_icp_read_trace(T,Nil,Nil,Qleft_edge_in_window,
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
		    result_of_read = read_icp_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qleft_edge_in_window,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    left_edge_in_window = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  left_edge_in_window = read_icp_integer();
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
		      emit_icp_read_trace(T,Nil,Nil,Qtop_edge_in_window,
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
		    result_of_read = read_icp_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qtop_edge_in_window,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    top_edge_in_window = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  top_edge_in_window = read_icp_integer();
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
		      emit_icp_read_trace(T,Nil,Nil,Qright_edge_in_window,
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
		    result_of_read = read_icp_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qright_edge_in_window,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    right_edge_in_window = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  right_edge_in_window = read_icp_integer();
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
		      emit_icp_read_trace(T,Nil,Nil,Qbottom_edge_in_window,
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
		    result_of_read = read_icp_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qbottom_edge_in_window,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    bottom_edge_in_window = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  bottom_edge_in_window = read_icp_integer();
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
			      Qwindow_parameters_plist,string_constant_2,
			      Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_list();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qwindow_parameters_plist,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    window_parameters_plist = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  window_parameters_plist = read_icp_list();
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
			      Qcorresponding_icp_object_index_on_other_side_qm,
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
		    result_of_read = read_icp_unsigned_integer_qm();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcorresponding_icp_object_index_on_other_side_qm,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    corresponding_icp_object_index_on_other_side_qm = 
			    result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  corresponding_icp_object_index_on_other_side_qm = 
			  read_icp_unsigned_integer_qm();
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_define_gensym_window__body(corresponding_icp_object_index,
			left_edge_in_window,top_edge_in_window,
			right_edge_in_window,bottom_edge_in_window,
			window_parameters_plist,
			corresponding_icp_object_index_on_other_side_qm);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qdefine_gensym_window,string_constant_1,Qmessage,
			  Nil,result_of_read,Nil,T);
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
		    emit_icp_read_trace(T,Nil,Nil,Qleft_edge_in_window,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qleft_edge_in_window,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  left_edge_in_window = result_of_read;
		POP_SPECIAL();
	    }
	    else
		left_edge_in_window = read_icp_integer();
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
		    emit_icp_read_trace(T,Nil,Nil,Qtop_edge_in_window,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qtop_edge_in_window,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  top_edge_in_window = result_of_read;
		POP_SPECIAL();
	    }
	    else
		top_edge_in_window = read_icp_integer();
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
		    emit_icp_read_trace(T,Nil,Nil,Qright_edge_in_window,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qright_edge_in_window,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  right_edge_in_window = result_of_read;
		POP_SPECIAL();
	    }
	    else
		right_edge_in_window = read_icp_integer();
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
		    emit_icp_read_trace(T,Nil,Nil,Qbottom_edge_in_window,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qbottom_edge_in_window,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  bottom_edge_in_window = result_of_read;
		POP_SPECIAL();
	    }
	    else
		bottom_edge_in_window = read_icp_integer();
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
		    emit_icp_read_trace(T,Nil,Nil,Qwindow_parameters_plist,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_list();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qwindow_parameters_plist,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  window_parameters_plist = result_of_read;
		POP_SPECIAL();
	    }
	    else
		window_parameters_plist = read_icp_list();
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
			    Qcorresponding_icp_object_index_on_other_side_qm,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_unsigned_integer_qm();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcorresponding_icp_object_index_on_other_side_qm,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  corresponding_icp_object_index_on_other_side_qm = 
			  result_of_read;
		POP_SPECIAL();
	    }
	    else
		corresponding_icp_object_index_on_other_side_qm = 
			read_icp_unsigned_integer_qm();
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_define_gensym_window__body(corresponding_icp_object_index,
		      left_edge_in_window,top_edge_in_window,
		      right_edge_in_window,bottom_edge_in_window,
		      window_parameters_plist,
		      corresponding_icp_object_index_on_other_side_qm);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_define_gensym_window,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qhandle_icp_define_gensym_window,top,Nil);
		goto end_handle_icp_define_gensym_window;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qdefine_gensym_window,
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
			resumable_icp_push(Qhandle_icp_define_gensym_window);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_define_gensym_window;
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
		      resumable_icp_push(Qhandle_icp_define_gensym_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_gensym_window;
		  }
		  corresponding_icp_object_index = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  left_edge_in_window = resumable_icp_pop();
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
		      emit_icp_read_trace(T,Nil,Nil,Qleft_edge_in_window,
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
		    value = read_icp_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(corresponding_icp_object_index);
			resumable_icp_push(Qhandle_icp_define_gensym_window);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_define_gensym_window;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qleft_edge_in_window,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    left_edge_in_window = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_gensym_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_gensym_window;
		  }
		  left_edge_in_window = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  top_edge_in_window = resumable_icp_pop();
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
		      emit_icp_read_trace(T,Nil,Nil,Qtop_edge_in_window,
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
		    value = read_icp_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(left_edge_in_window);
			resumable_icp_push(corresponding_icp_object_index);
			resumable_icp_push(Qhandle_icp_define_gensym_window);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_define_gensym_window;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qtop_edge_in_window,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    top_edge_in_window = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(left_edge_in_window);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_gensym_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_gensym_window;
		  }
		  top_edge_in_window = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  right_edge_in_window = resumable_icp_pop();
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
		      emit_icp_read_trace(T,Nil,Nil,Qright_edge_in_window,
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
		    value = read_icp_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(top_edge_in_window);
			resumable_icp_push(left_edge_in_window);
			resumable_icp_push(corresponding_icp_object_index);
			resumable_icp_push(Qhandle_icp_define_gensym_window);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_define_gensym_window;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qright_edge_in_window,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    right_edge_in_window = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(top_edge_in_window);
		      resumable_icp_push(left_edge_in_window);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_gensym_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_gensym_window;
		  }
		  right_edge_in_window = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  bottom_edge_in_window = resumable_icp_pop();
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
		      emit_icp_read_trace(T,Nil,Nil,Qbottom_edge_in_window,
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
		    value = read_icp_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(right_edge_in_window);
			resumable_icp_push(top_edge_in_window);
			resumable_icp_push(left_edge_in_window);
			resumable_icp_push(corresponding_icp_object_index);
			resumable_icp_push(Qhandle_icp_define_gensym_window);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_define_gensym_window;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qbottom_edge_in_window,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    bottom_edge_in_window = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(right_edge_in_window);
		      resumable_icp_push(top_edge_in_window);
		      resumable_icp_push(left_edge_in_window);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_gensym_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_gensym_window;
		  }
		  bottom_edge_in_window = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  window_parameters_plist = resumable_icp_pop();
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
			      Qwindow_parameters_plist,string_constant_2,
			      Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_list();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(bottom_edge_in_window);
			resumable_icp_push(right_edge_in_window);
			resumable_icp_push(top_edge_in_window);
			resumable_icp_push(left_edge_in_window);
			resumable_icp_push(corresponding_icp_object_index);
			resumable_icp_push(Qhandle_icp_define_gensym_window);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_define_gensym_window;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qwindow_parameters_plist,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    window_parameters_plist = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_list();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(bottom_edge_in_window);
		      resumable_icp_push(right_edge_in_window);
		      resumable_icp_push(top_edge_in_window);
		      resumable_icp_push(left_edge_in_window);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_gensym_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_gensym_window;
		  }
		  window_parameters_plist = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  corresponding_icp_object_index_on_other_side_qm = 
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
			      Qcorresponding_icp_object_index_on_other_side_qm,
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
		    value = read_icp_unsigned_integer_qm();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(window_parameters_plist);
			resumable_icp_push(bottom_edge_in_window);
			resumable_icp_push(right_edge_in_window);
			resumable_icp_push(top_edge_in_window);
			resumable_icp_push(left_edge_in_window);
			resumable_icp_push(corresponding_icp_object_index);
			resumable_icp_push(Qhandle_icp_define_gensym_window);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_define_gensym_window;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcorresponding_icp_object_index_on_other_side_qm,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    corresponding_icp_object_index_on_other_side_qm = 
			    result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer_qm();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(window_parameters_plist);
		      resumable_icp_push(bottom_edge_in_window);
		      resumable_icp_push(right_edge_in_window);
		      resumable_icp_push(top_edge_in_window);
		      resumable_icp_push(left_edge_in_window);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_gensym_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_gensym_window;
		  }
		  corresponding_icp_object_index_on_other_side_qm = value;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_define_gensym_window__body(corresponding_icp_object_index,
			left_edge_in_window,top_edge_in_window,
			right_edge_in_window,bottom_edge_in_window,
			window_parameters_plist,
			corresponding_icp_object_index_on_other_side_qm);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qdefine_gensym_window,string_constant_1,Qmessage,
			  Nil,result_of_read,Nil,T);
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
		      resumable_icp_push(Qhandle_icp_define_gensym_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_gensym_window;
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
		    resumable_icp_push(Qhandle_icp_define_gensym_window);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_define_gensym_window;
		}
		corresponding_icp_object_index = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		left_edge_in_window = resumable_icp_pop();
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
		    emit_icp_read_trace(T,Nil,Nil,Qleft_edge_in_window,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_gensym_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_gensym_window;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qleft_edge_in_window,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  left_edge_in_window = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(corresponding_icp_object_index);
		    resumable_icp_push(Qhandle_icp_define_gensym_window);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_define_gensym_window;
		}
		left_edge_in_window = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		top_edge_in_window = resumable_icp_pop();
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
		    emit_icp_read_trace(T,Nil,Nil,Qtop_edge_in_window,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(left_edge_in_window);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_gensym_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_gensym_window;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qtop_edge_in_window,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  top_edge_in_window = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(left_edge_in_window);
		    resumable_icp_push(corresponding_icp_object_index);
		    resumable_icp_push(Qhandle_icp_define_gensym_window);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_define_gensym_window;
		}
		top_edge_in_window = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		right_edge_in_window = resumable_icp_pop();
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
		    emit_icp_read_trace(T,Nil,Nil,Qright_edge_in_window,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(top_edge_in_window);
		      resumable_icp_push(left_edge_in_window);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_gensym_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_gensym_window;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qright_edge_in_window,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  right_edge_in_window = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(top_edge_in_window);
		    resumable_icp_push(left_edge_in_window);
		    resumable_icp_push(corresponding_icp_object_index);
		    resumable_icp_push(Qhandle_icp_define_gensym_window);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_define_gensym_window;
		}
		right_edge_in_window = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		bottom_edge_in_window = resumable_icp_pop();
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
		    emit_icp_read_trace(T,Nil,Nil,Qbottom_edge_in_window,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(right_edge_in_window);
		      resumable_icp_push(top_edge_in_window);
		      resumable_icp_push(left_edge_in_window);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_gensym_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_gensym_window;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qbottom_edge_in_window,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  bottom_edge_in_window = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(right_edge_in_window);
		    resumable_icp_push(top_edge_in_window);
		    resumable_icp_push(left_edge_in_window);
		    resumable_icp_push(corresponding_icp_object_index);
		    resumable_icp_push(Qhandle_icp_define_gensym_window);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_define_gensym_window;
		}
		bottom_edge_in_window = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		window_parameters_plist = resumable_icp_pop();
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
		    emit_icp_read_trace(T,Nil,Nil,Qwindow_parameters_plist,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_list();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(bottom_edge_in_window);
		      resumable_icp_push(right_edge_in_window);
		      resumable_icp_push(top_edge_in_window);
		      resumable_icp_push(left_edge_in_window);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_gensym_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_gensym_window;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qwindow_parameters_plist,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  window_parameters_plist = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_list();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(bottom_edge_in_window);
		    resumable_icp_push(right_edge_in_window);
		    resumable_icp_push(top_edge_in_window);
		    resumable_icp_push(left_edge_in_window);
		    resumable_icp_push(corresponding_icp_object_index);
		    resumable_icp_push(Qhandle_icp_define_gensym_window);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_define_gensym_window;
		}
		window_parameters_plist = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		corresponding_icp_object_index_on_other_side_qm = 
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
			    Qcorresponding_icp_object_index_on_other_side_qm,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_unsigned_integer_qm();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(window_parameters_plist);
		      resumable_icp_push(bottom_edge_in_window);
		      resumable_icp_push(right_edge_in_window);
		      resumable_icp_push(top_edge_in_window);
		      resumable_icp_push(left_edge_in_window);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_gensym_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_gensym_window;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcorresponding_icp_object_index_on_other_side_qm,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  corresponding_icp_object_index_on_other_side_qm = 
			  result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer_qm();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(window_parameters_plist);
		    resumable_icp_push(bottom_edge_in_window);
		    resumable_icp_push(right_edge_in_window);
		    resumable_icp_push(top_edge_in_window);
		    resumable_icp_push(left_edge_in_window);
		    resumable_icp_push(corresponding_icp_object_index);
		    resumable_icp_push(Qhandle_icp_define_gensym_window);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_define_gensym_window;
		}
		corresponding_icp_object_index_on_other_side_qm = value;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_define_gensym_window__body(corresponding_icp_object_index,
		      left_edge_in_window,top_edge_in_window,
		      right_edge_in_window,bottom_edge_in_window,
		      window_parameters_plist,
		      corresponding_icp_object_index_on_other_side_qm);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_define_gensym_window:
    return result;
}

/* DECODE-ICP-WINDOW-PROTOCOL-VERSION */
Object decode_icp_window_protocol_version(icp_window_protocol_version)
    Object icp_window_protocol_version;
{
    x_note_fn_call(55,79);
    if ( !(FIXNUMP(icp_window_protocol_version) && 
	    FIXNUM_LE(FIX((SI_Long)-128L),icp_window_protocol_version) && 
	    FIXNUM_LE(icp_window_protocol_version,FIX((SI_Long)127L)))) {
	if (icp_window_protocol_version)
	    return VALUES_2(FIX((SI_Long)5L),FIX((SI_Long)0L));
	else
	    return VALUES_2(FIX((SI_Long)3L),FIX((SI_Long)0L));
    }
    else
	switch (INTEGER_TO_CHAR(icp_window_protocol_version)) {
	  case 3:
	    return VALUES_2(FIX((SI_Long)3L),FIX((SI_Long)1L));
	  case 4:
	  case 5:
	  case 6:
	  case 7:
	  case 8:
	  case 9:
	  case 10:
	  case 11:
	    return VALUES_2(FIX((SI_Long)4L),FIX((SI_Long)0L));
	  case 12:
	  case 13:
	    return VALUES_2(FIX((SI_Long)4L),FIX((SI_Long)1L));
	  default:
	    if (icp_window_protocol_version)
		return VALUES_2(FIX((SI_Long)5L),FIX((SI_Long)0L));
	    else
		return VALUES_2(FIX((SI_Long)3L),FIX((SI_Long)0L));
	}
}

/* SYNC-GRAPHICS-ON-NATIVE-WINDOW */
Object sync_graphics_on_native_window(native_window_qm)
    Object native_window_qm;
{
    x_note_fn_call(55,80);
    if (native_window_qm)
	sync_graphics_on_native_window_maybe_with_tracing(native_window_qm);
    return VALUES_1(Nil);
}

/* SYNC-GRAPHICS-ON-NATIVE-WINDOW-1 */
Object sync_graphics_on_native_window_1(native_window)
    Object native_window;
{
    x_note_fn_call(55,81);
    g2ext_x11_sync(IFIX(native_window));
    return VALUES_1(Nil);
}

/* FLUSH-GRAPHICS-ON-NATIVE-WINDOW */
Object flush_graphics_on_native_window(native_window_qm)
    Object native_window_qm;
{
    x_note_fn_call(55,82);
    if (native_window_qm)
	g2ext_x11_flush(IFIX(native_window_qm));
    return VALUES_1(Nil);
}

static Object Qforce_graphics_on_window;  /* force-graphics-on-window */

static Object Qflush_or_sync;      /* flush-or-sync */

static Object Qx11_window;         /* x11-window */

/* FORCE-GRAPHICS-ON-WINDOW */
Object force_graphics_on_window(flush_or_sync)
    Object flush_or_sync;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top, key;
    Declare_special(3);
    Object result;

    x_note_fn_call(55,83);
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
	      SVREF(temp,svref_arg_2) = Qforce_graphics_on_window;
	  }
	  if (EQ(Type_of_current_window,Qicp)) {
	      icp_message_functions_icp_prologue(Qforce_graphics_on_window);
	      start_writing_icp_message(FIX((SI_Long)188L));
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)2L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qforce_graphics_on_window,string_constant_1,
			      Qmessage,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  1);
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,Qflush_or_sync,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
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
				  write_icp_unsigned_integer(flush_or_sync);
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qflush_or_sync,string_constant_2,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else
			result_of_write = 
				write_icp_unsigned_integer(flush_or_sync);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qforce_graphics_on_window,
				string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qflush_or_sync,
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
			    write_icp_unsigned_integer(flush_or_sync);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qflush_or_sync,string_constant_2,Qargument,
				Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_unsigned_integer(flush_or_sync);
	  }
	  else if (EQ(Type_of_current_window,Qprinter)) {
	      temp_1 = aref1(Icp_printing_message_handler_array,
		      FIX((SI_Long)188L));
	      FUNCALL_1(temp_1,flush_or_sync);
	  }
	  else if (EQ(Type_of_current_window,Qx11_window)) {
	      if (! !(FIXNUMP(flush_or_sync) && 
		      FIXNUM_LE(FIX((SI_Long)-128L),flush_or_sync) && 
		      FIXNUM_LE(flush_or_sync,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(flush_or_sync)) {
		    case 0:
		      flush_graphics_on_native_window(Current_native_window_qm);
		      break;
		    case 1:
		      sync_graphics_on_native_window(Current_native_window_qm);
		      break;
		    default:
		      break;
		  }
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qforce_graphics_on_window,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qforce_graphics_on_window,top,Nil);
		goto end_force_graphics_on_window;
	    }
	}
	flush_or_sync = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : flush_or_sync;
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
	      SVREF(temp,svref_arg_2) = Qforce_graphics_on_window;
	  }
	  key = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		  resumable_icp_pop() : Type_of_current_window;
	  if (EQ(key,Qicp)) {
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
	      icp_message_functions_icp_prologue(Qforce_graphics_on_window);
	    l1:
	      if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)188L)))) {
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
			      Qforce_graphics_on_window,string_constant_1,
			      Qmessage,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  1);
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,Qflush_or_sync,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
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
				  write_icp_unsigned_integer(flush_or_sync))) {
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
				      Qflush_or_sync,string_constant_2,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else if (EQ(icp_suspend_1,
			    write_icp_unsigned_integer(flush_or_sync))) {
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
				Qforce_graphics_on_window,
				string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
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
		      emit_icp_write_trace(T,Nil,Nil,Qflush_or_sync,
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
			    write_icp_unsigned_integer(flush_or_sync))) {
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
				Qflush_or_sync,string_constant_2,Qargument,
				Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_unsigned_integer(flush_or_sync))) {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      else
		  temp_1 = Nil;
	      goto end_block;
	    end_block:
	      if (EQ(icp_suspend_1,temp_1)) {
		  resumable_icp_push(key);
		  resumable_icp_push(flush_or_sync);
		  resumable_icp_push(Qforce_graphics_on_window);
		  result = VALUES_1(Icp_suspend);
		  POP_SPECIAL();
		  goto end_force_graphics_on_window;
	      }
	  }
	  else if (EQ(key,Qprinter)) {
	      temp_1 = aref1(Icp_printing_message_handler_array,
		      FIX((SI_Long)188L));
	      FUNCALL_1(temp_1,flush_or_sync);
	  }
	  else if (EQ(key,Qx11_window)) {
	      if (! !(FIXNUMP(flush_or_sync) && 
		      FIXNUM_LE(FIX((SI_Long)-128L),flush_or_sync) && 
		      FIXNUM_LE(flush_or_sync,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(flush_or_sync)) {
		    case 0:
		      flush_graphics_on_native_window(Current_native_window_qm);
		      break;
		    case 1:
		      sync_graphics_on_native_window(Current_native_window_qm);
		      break;
		    default:
		      break;
		  }
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_force_graphics_on_window:
    return result;
}

static Object string_constant_3;   /* "[msg funct]" */

static Object Qhandle_icp_force_graphics_on_window;  /* handle-icp-force-graphics-on-window */

/* HANDLE-ICP-FORCE-GRAPHICS-ON-WINDOW */
Object handle_icp_force_graphics_on_window()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read, flush_or_sync, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(55,84);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qforce_graphics_on_window,
			string_constant_3,Qmessage,Nil,Nil,Nil,T);
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
		      emit_icp_read_trace(T,Nil,Nil,Qflush_or_sync,
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
				Qflush_or_sync,string_constant_2,Qargument,
				T,result_of_read,Nil,Nil);
		    flush_or_sync = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  flush_or_sync = read_icp_unsigned_integer();
	      result_of_read = force_graphics_on_window(flush_or_sync);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qforce_graphics_on_window,string_constant_3,
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
		    emit_icp_read_trace(T,Nil,Nil,Qflush_or_sync,
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
			      Qflush_or_sync,string_constant_2,Qargument,T,
			      result_of_read,Nil,Nil);
		  flush_or_sync = result_of_read;
		POP_SPECIAL();
	    }
	    else
		flush_or_sync = read_icp_unsigned_integer();
	    force_graphics_on_window(flush_or_sync);
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_force_graphics_on_window,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qhandle_icp_force_graphics_on_window,top,Nil);
		goto end_handle_icp_force_graphics_on_window;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qforce_graphics_on_window,
			string_constant_3,Qmessage,Nil,Nil,Nil,T);
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
		  flush_or_sync = resumable_icp_pop();
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
		      emit_icp_read_trace(T,Nil,Nil,Qflush_or_sync,
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
			resumable_icp_push(Qhandle_icp_force_graphics_on_window);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_force_graphics_on_window;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qflush_or_sync,string_constant_2,Qargument,
				T,result_of_read,Nil,Nil);
		    flush_or_sync = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_force_graphics_on_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_force_graphics_on_window;
		  }
		  flush_or_sync = value;
	      }
	      result_of_read = force_graphics_on_window(flush_or_sync);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qforce_graphics_on_window,string_constant_3,
			  Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		flush_or_sync = resumable_icp_pop();
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
		    emit_icp_read_trace(T,Nil,Nil,Qflush_or_sync,
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
		      resumable_icp_push(Qhandle_icp_force_graphics_on_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_force_graphics_on_window;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qflush_or_sync,string_constant_2,Qargument,T,
			      result_of_read,Nil,Nil);
		  flush_or_sync = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qhandle_icp_force_graphics_on_window);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_force_graphics_on_window;
		}
		flush_or_sync = value;
	    }
	    force_graphics_on_window(flush_or_sync);
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_force_graphics_on_window:
    return result;
}

/* FLUSH-GRAPHICS-ON-CURRENT-WINDOW */
Object flush_graphics_on_current_window()
{
    x_note_fn_call(55,85);
    return force_graphics_on_window(FIX((SI_Long)1L));
}

/* SYNC-GRAPHICS-ON-CURRENT-WINDOW */
Object sync_graphics_on_current_window()
{
    x_note_fn_call(55,86);
    return force_graphics_on_window(FIX((SI_Long)1L));
}

Object The_type_description_of_identified_drawing_activity = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_identified_drawing_activitys, Qchain_of_available_identified_drawing_activitys);

DEFINE_VARIABLE_WITH_SYMBOL(Identified_drawing_activity_count, Qidentified_drawing_activity_count);

Object Chain_of_available_identified_drawing_activitys_vector = UNBOUND;

/* IDENTIFIED-DRAWING-ACTIVITY-STRUCTURE-MEMORY-USAGE */
Object identified_drawing_activity_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(55,87);
    temp = Identified_drawing_activity_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)9L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-IDENTIFIED-DRAWING-ACTIVITY-COUNT */
Object outstanding_identified_drawing_activity_count()
{
    Object def_structure_identified_drawing_activity_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(55,88);
    gensymed_symbol = IFIX(Identified_drawing_activity_count);
    def_structure_identified_drawing_activity_variable = 
	    Chain_of_available_identified_drawing_activitys;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_identified_drawing_activity_variable))
	goto end_loop;
    def_structure_identified_drawing_activity_variable = 
	    ISVREF(def_structure_identified_drawing_activity_variable,
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

/* RECLAIM-IDENTIFIED-DRAWING-ACTIVITY-1-1 */
Object reclaim_identified_drawing_activity_1_1(identified_drawing_activity)
    Object identified_drawing_activity;
{
    Object temp, svref_arg_2;

    x_note_fn_call(55,89);
    inline_note_reclaim_cons(identified_drawing_activity,Nil);
    temp = ISVREF(Chain_of_available_identified_drawing_activitys_vector,
	    IFIX(Current_thread_index));
    SVREF(identified_drawing_activity,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_identified_drawing_activitys_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = identified_drawing_activity;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-IDENTIFIED-DRAWING-ACTIVITY */
Object reclaim_structure_for_identified_drawing_activity(identified_drawing_activity)
    Object identified_drawing_activity;
{
    x_note_fn_call(55,90);
    return reclaim_identified_drawing_activity_1_1(identified_drawing_activity);
}

static Object Qg2_defstruct_structure_name_identified_drawing_activity_g2_struct;  /* g2-defstruct-structure-name::identified-drawing-activity-g2-struct */

/* MAKE-PERMANENT-IDENTIFIED-DRAWING-ACTIVITY-STRUCTURE-INTERNAL */
Object make_permanent_identified_drawing_activity_structure_internal()
{
    Object def_structure_identified_drawing_activity_variable;
    Object defstruct_g2_identified_drawing_activity_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(55,91);
    def_structure_identified_drawing_activity_variable = Nil;
    atomic_incff_symval(Qidentified_drawing_activity_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_identified_drawing_activity_variable = Nil;
	gensymed_symbol = (SI_Long)9L;
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
	defstruct_g2_identified_drawing_activity_variable = the_array;
	SVREF(defstruct_g2_identified_drawing_activity_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_identified_drawing_activity_g2_struct;
	SVREF(defstruct_g2_identified_drawing_activity_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_identified_drawing_activity_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_identified_drawing_activity_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_identified_drawing_activity_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_identified_drawing_activity_variable,
		FIX((SI_Long)5L)) = Nil;
	def_structure_identified_drawing_activity_variable = 
		defstruct_g2_identified_drawing_activity_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_identified_drawing_activity_variable);
}

/* MAKE-IDENTIFIED-DRAWING-ACTIVITY-1-1 */
Object make_identified_drawing_activity_1_1(gensym_window_of_identified_drawing_activity,
	    id_of_identified_drawing_activity,
	    parent_of_pending_activity_qm,name_of_pending_activity,
	    continuation_of_pending_activity_qm,
	    arg_of_identified_drawing_activity)
    Object gensym_window_of_identified_drawing_activity;
    Object id_of_identified_drawing_activity, parent_of_pending_activity_qm;
    Object name_of_pending_activity, continuation_of_pending_activity_qm;
    Object arg_of_identified_drawing_activity;
{
    Object def_structure_identified_drawing_activity_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(55,92);
    def_structure_identified_drawing_activity_variable = 
	    ISVREF(Chain_of_available_identified_drawing_activitys_vector,
	    IFIX(Current_thread_index));
    if (def_structure_identified_drawing_activity_variable) {
	svref_arg_1 = Chain_of_available_identified_drawing_activitys_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_identified_drawing_activity_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_identified_drawing_activity_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_identified_drawing_activity_g2_struct;
    }
    else
	def_structure_identified_drawing_activity_variable = 
		make_permanent_identified_drawing_activity_structure_internal();
    inline_note_allocate_cons(def_structure_identified_drawing_activity_variable,
	    Nil);
    SVREF(def_structure_identified_drawing_activity_variable,
	    FIX((SI_Long)6L)) = gensym_window_of_identified_drawing_activity;
    SVREF(def_structure_identified_drawing_activity_variable,
	    FIX((SI_Long)7L)) = id_of_identified_drawing_activity;
    SVREF(def_structure_identified_drawing_activity_variable,
	    FIX((SI_Long)2L)) = parent_of_pending_activity_qm;
    SVREF(def_structure_identified_drawing_activity_variable,
	    FIX((SI_Long)1L)) = name_of_pending_activity;
    SVREF(def_structure_identified_drawing_activity_variable,
	    FIX((SI_Long)5L)) = continuation_of_pending_activity_qm;
    SVREF(def_structure_identified_drawing_activity_variable,
	    FIX((SI_Long)8L)) = arg_of_identified_drawing_activity;
    SVREF(def_structure_identified_drawing_activity_variable,
	    FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_identified_drawing_activity_variable,
	    FIX((SI_Long)4L)) = T;
    return VALUES_1(def_structure_identified_drawing_activity_variable);
}

/* MAKE-IDENTIFIED-DRAWING-ACTIVITY */
Object make_identified_drawing_activity(gensym_window_of_identified_drawing_activity,
	    id_of_identified_drawing_activity,
	    parent_of_pending_activity_qm,name_of_pending_activity,
	    continuation_of_pending_activity_qm,
	    arg_of_identified_drawing_activity)
    Object gensym_window_of_identified_drawing_activity;
    Object id_of_identified_drawing_activity, parent_of_pending_activity_qm;
    Object name_of_pending_activity, continuation_of_pending_activity_qm;
    Object arg_of_identified_drawing_activity;
{
    Object identified_drawing_activity;

    x_note_fn_call(55,93);
    identified_drawing_activity = 
	    make_identified_drawing_activity_1_1(gensym_window_of_identified_drawing_activity,
	    id_of_identified_drawing_activity,
	    parent_of_pending_activity_qm,name_of_pending_activity,
	    continuation_of_pending_activity_qm,
	    arg_of_identified_drawing_activity);
    if (parent_of_pending_activity_qm)
	block_pending_activity(parent_of_pending_activity_qm,
		identified_drawing_activity);
    return VALUES_1(identified_drawing_activity);
}

static Object Qcontinue_after_drawing;  /* continue-after-drawing */

/* START-IDENTIFIED-DRAWING-ACTIVITY */
Object start_identified_drawing_activity varargs_1(int, n)
{
    Object gensym_window, parent_qm, continuation_function;
    Object arg1, max_1, x, ab_loop_list_, id, identified_drawing_activity;
    Object gensym_push_modify_macro_arg, car_1, cdr_1, svref_new_value;
    SI_Long gensymed_symbol, gensymed_symbol_1, fresh_id;
    Declare_varargs_nonrelocating;

    x_note_fn_call(55,94);
    INIT_ARGS_nonrelocating();
    gensym_window = REQUIRED_ARG_nonrelocating();
    parent_qm = REQUIRED_ARG_nonrelocating();
    continuation_function = REQUIRED_ARG_nonrelocating();
    arg1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    gensymed_symbol = (SI_Long)1L;
    max_1 = FIX((SI_Long)0L);
    x = Nil;
    ab_loop_list_ = ISVREF(gensym_window,(SI_Long)34L);
    id = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    x = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    id = ISVREF(x,(SI_Long)7L);
    if (FIXNUM_LT(max_1,id))
	max_1 = id;
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(max_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    fresh_id = gensymed_symbol + gensymed_symbol_1;
    identified_drawing_activity = 
	    make_identified_drawing_activity(gensym_window,FIX(fresh_id),
	    parent_qm,Qcontinue_after_drawing,continuation_function,arg1);
    gensym_push_modify_macro_arg = identified_drawing_activity;
    car_1 = gensym_push_modify_macro_arg;
    cdr_1 = ISVREF(gensym_window,(SI_Long)34L);
    svref_new_value = gensym_cons_1(car_1,cdr_1);
    SVREF(gensym_window,FIX((SI_Long)34L)) = svref_new_value;
    return VALUES_1(identified_drawing_activity);
}

/* FIND-IDENTIFIED-DRAWING-ACTIVITY */
Object find_identified_drawing_activity(gensym_window,id)
    Object gensym_window, id;
{
    Object tuple, ab_loop_list_;

    x_note_fn_call(55,95);
    tuple = Nil;
    ab_loop_list_ = ISVREF(gensym_window,(SI_Long)34L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    tuple = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (FIXNUM_EQ(id,ISVREF(tuple,(SI_Long)7L)))
	return VALUES_1(tuple);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Kfinished;           /* :finished */

static Object Kcanceled;           /* :canceled */

/* REMOVE-IDENTIFIED-DRAWING-ACTIVITY */
Object remove_identified_drawing_activity(identified_drawing_activity,
	    kind_of_continuation)
    Object identified_drawing_activity, kind_of_continuation;
{
    Object gensym_window, svref_new_value;

    x_note_fn_call(55,96);
    if (EQ(kind_of_continuation,Kfinished) || EQ(kind_of_continuation,
	    Kcanceled)) {
	gensym_window = ISVREF(identified_drawing_activity,(SI_Long)6L);
	svref_new_value = 
		delete_gensym_element_1(identified_drawing_activity,
		ISVREF(gensym_window,(SI_Long)34L));
	SVREF(gensym_window,FIX((SI_Long)34L)) = svref_new_value;
    }
    return VALUES_1(Nil);
}

static Object Qping_drawing;       /* ping-drawing */

static Object Qid_of_identified_drawing_activity;  /* id-of-identified-drawing-activity */

/* PING-DRAWING */
Object ping_drawing(id_of_identified_drawing_activity)
    Object id_of_identified_drawing_activity;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top, key;
    Declare_special(3);
    Object result;

    x_note_fn_call(55,97);
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
	      SVREF(temp,svref_arg_2) = Qping_drawing;
	  }
	  if (EQ(Type_of_current_window,Qicp)) {
	      icp_message_functions_icp_prologue(Qping_drawing);
	      start_writing_icp_message(FIX((SI_Long)189L));
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)2L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qping_drawing,
			      string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  1);
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qid_of_identified_drawing_activity,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
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
				  write_icp_unsigned_integer(id_of_identified_drawing_activity);
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qid_of_identified_drawing_activity,
				      string_constant_2,Qargument,Nil,Nil,
				      Nil,Nil);
			POP_SPECIAL();
		    }
		    else
			result_of_write = 
				write_icp_unsigned_integer(id_of_identified_drawing_activity);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qping_drawing,string_constant_1,Qmessage,
				Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qid_of_identified_drawing_activity,
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
			    write_icp_unsigned_integer(id_of_identified_drawing_activity);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qid_of_identified_drawing_activity,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_unsigned_integer(id_of_identified_drawing_activity);
	  }
	  else if (EQ(Type_of_current_window,Qprinter)) {
	      temp_1 = aref1(Icp_printing_message_handler_array,
		      FIX((SI_Long)189L));
	      FUNCALL_1(temp_1,id_of_identified_drawing_activity);
	  }
	  else if (EQ(Type_of_current_window,Qx11_window)) {
	      sync_graphics_on_native_window(Current_native_window_qm);
	      if (slave_gensym_window_qm(Current_window))
		  send_ping_drawing_reply(Current_window,
			  id_of_identified_drawing_activity);
	      else
		  handle_ping_drawing_reply_1(Current_window,
			  id_of_identified_drawing_activity);
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qping_drawing,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qping_drawing,top,Nil);
		goto end_ping_drawing;
	    }
	}
	id_of_identified_drawing_activity = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : id_of_identified_drawing_activity;
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
	      SVREF(temp,svref_arg_2) = Qping_drawing;
	  }
	  key = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		  resumable_icp_pop() : Type_of_current_window;
	  if (EQ(key,Qicp)) {
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
	      icp_message_functions_icp_prologue(Qping_drawing);
	    l1:
	      if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)189L)))) {
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
		      emit_icp_write_trace(T,Nil,Nil,Qping_drawing,
			      string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  1);
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qid_of_identified_drawing_activity,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
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
				  write_icp_unsigned_integer(id_of_identified_drawing_activity))) 
				      {
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
				      Qid_of_identified_drawing_activity,
				      string_constant_2,Qargument,Nil,Nil,
				      Nil,Nil);
			POP_SPECIAL();
		    }
		    else if (EQ(icp_suspend_1,
			    write_icp_unsigned_integer(id_of_identified_drawing_activity))) 
				{
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
				Qping_drawing,string_constant_1,Qmessage,
				Nil,Nil,Nil,Nil);
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
		      emit_icp_write_trace(T,Nil,Nil,
			      Qid_of_identified_drawing_activity,
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
			    write_icp_unsigned_integer(id_of_identified_drawing_activity))) 
				{
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
				Qid_of_identified_drawing_activity,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_unsigned_integer(id_of_identified_drawing_activity))) 
			  {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      else
		  temp_1 = Nil;
	      goto end_block;
	    end_block:
	      if (EQ(icp_suspend_1,temp_1)) {
		  resumable_icp_push(key);
		  resumable_icp_push(id_of_identified_drawing_activity);
		  resumable_icp_push(Qping_drawing);
		  result = VALUES_1(Icp_suspend);
		  POP_SPECIAL();
		  goto end_ping_drawing;
	      }
	  }
	  else if (EQ(key,Qprinter)) {
	      temp_1 = aref1(Icp_printing_message_handler_array,
		      FIX((SI_Long)189L));
	      FUNCALL_1(temp_1,id_of_identified_drawing_activity);
	  }
	  else if (EQ(key,Qx11_window)) {
	      sync_graphics_on_native_window(Current_native_window_qm);
	      if (slave_gensym_window_qm(Current_window))
		  send_ping_drawing_reply(Current_window,
			  id_of_identified_drawing_activity);
	      else
		  handle_ping_drawing_reply_1(Current_window,
			  id_of_identified_drawing_activity);
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_ping_drawing:
    return result;
}

static Object Qhandle_icp_ping_drawing;  /* handle-icp-ping-drawing */

/* HANDLE-ICP-PING-DRAWING */
Object handle_icp_ping_drawing()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read;
    Object id_of_identified_drawing_activity, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(55,98);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qping_drawing,
			string_constant_3,Qmessage,Nil,Nil,Nil,T);
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
			      Qid_of_identified_drawing_activity,
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
				Qid_of_identified_drawing_activity,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    id_of_identified_drawing_activity = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  id_of_identified_drawing_activity = 
			  read_icp_unsigned_integer();
	      result_of_read = ping_drawing(id_of_identified_drawing_activity);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qping_drawing,string_constant_3,Qmessage,Nil,
			  result_of_read,Nil,T);
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
			    Qid_of_identified_drawing_activity,
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
			      Qid_of_identified_drawing_activity,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  id_of_identified_drawing_activity = result_of_read;
		POP_SPECIAL();
	    }
	    else
		id_of_identified_drawing_activity = 
			read_icp_unsigned_integer();
	    ping_drawing(id_of_identified_drawing_activity);
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_ping_drawing,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qhandle_icp_ping_drawing,top,Nil);
		goto end_handle_icp_ping_drawing;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qping_drawing,
			string_constant_3,Qmessage,Nil,Nil,Nil,T);
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
		  id_of_identified_drawing_activity = resumable_icp_pop();
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
			      Qid_of_identified_drawing_activity,
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
			resumable_icp_push(Qhandle_icp_ping_drawing);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_ping_drawing;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qid_of_identified_drawing_activity,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    id_of_identified_drawing_activity = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_ping_drawing);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_ping_drawing;
		  }
		  id_of_identified_drawing_activity = value;
	      }
	      result_of_read = ping_drawing(id_of_identified_drawing_activity);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qping_drawing,string_constant_3,Qmessage,Nil,
			  result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		id_of_identified_drawing_activity = resumable_icp_pop();
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
			    Qid_of_identified_drawing_activity,
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
		      resumable_icp_push(Qhandle_icp_ping_drawing);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_ping_drawing;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qid_of_identified_drawing_activity,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  id_of_identified_drawing_activity = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qhandle_icp_ping_drawing);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_ping_drawing;
		}
		id_of_identified_drawing_activity = value;
	    }
	    ping_drawing(id_of_identified_drawing_activity);
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_ping_drawing:
    return result;
}

static Object Qtelewindows;        /* telewindows */

/* SEND-PING-DRAWING-REPLY */
Object send_ping_drawing_reply(gensym_window,id_of_identified_drawing_activity)
    Object gensym_window, id_of_identified_drawing_activity;
{
    Object current_icp_port, current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
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
    Object result;

    x_note_fn_call(55,99);
    current_icp_port = ISVREF(gensym_window,(SI_Long)13L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
	    11);
      current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
	      10);
	temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) : Nil;
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
			    gensymed_symbol_1 = 0.0;
			    gensymed_symbol_2 = 0.0;
			    if (Profiling_enabled_qm) {
				gensymed_symbol = T;
				gensymed_symbol_1 = 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)2L),(SI_Long)0L);
				gensymed_symbol_2 = g2ext_unix_time_as_float();
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)2L);
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					gensymed_symbol_2);
			    }
			    if (icp_connection_open_p(Current_icp_socket) 
				    &&  
				    !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					{
				temp = 
					send_icp_ping_drawing_reply(gensym_window,
					id_of_identified_drawing_activity);
				end_icp_message_group();
			    }
			    else
				temp = Nil;
			    if (Profiling_enabled_qm) {
				gensymed_symbol_3 = g2ext_unix_time_as_float();
				gensymed_symbol_4 = 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)2L),(SI_Long)0L);
				gensymed_symbol_5 = gensymed_symbol_3 - 
					gensymed_symbol_4;
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)6L);
				aref_new_value = gensymed_symbol_5 + 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)6L),(SI_Long)0L);
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					aref_new_value);
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)2L);
				aref_new_value = gensymed_symbol ? 
					gensymed_symbol_1 + 
					gensymed_symbol_5 + 
					(gensymed_symbol_4 - 
					gensymed_symbol_2) : gensymed_symbol_3;
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					aref_new_value);
			    }
			    result = VALUES_1(temp);
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
    return result;
}

static Object Qsend_icp_ping_drawing_reply;  /* send-icp-ping-drawing-reply */

static Object Qping_drawing_reply;  /* ping-drawing-reply */

static Object Qgensym_window;      /* gensym-window */

static Object string_constant_4;   /* "[object arg]" */

/* SEND-ICP-PING-DRAWING-REPLY */
Object send_icp_ping_drawing_reply(gensym_window,
	    id_of_identified_drawing_activity)
    Object gensym_window, id_of_identified_drawing_activity;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, resumable_icp_state_1;
    Object icp_suspend_1, top, value, value_1;
    Declare_special(3);
    Object result;

    x_note_fn_call(55,100);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_ping_drawing_reply;
	  }
	  temp_1 = getfq_function_no_default(ISVREF(gensym_window,
		  (SI_Long)14L),Current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = make_corresponding_icp_gensym_window(gensym_window);
	  gensym_window = temp_1;
	  start_writing_icp_message(FIX((SI_Long)190L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qping_drawing_reply,
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
			emit_icp_write_trace(T,Nil,Nil,Qgensym_window,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
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
			      write_icp_corresponding_object_index(gensym_window);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qgensym_window,string_constant_4,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_corresponding_object_index(gensym_window);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qid_of_identified_drawing_activity,
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
			      write_icp_unsigned_integer(id_of_identified_drawing_activity);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qid_of_identified_drawing_activity,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_unsigned_integer(id_of_identified_drawing_activity);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qping_drawing_reply,string_constant_1,Qmessage,
			    Nil,Nil,Nil,Nil);
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
		      emit_icp_write_trace(T,Nil,Nil,Qgensym_window,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
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
			    write_icp_corresponding_object_index(gensym_window);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qgensym_window,string_constant_4,Qargument,
				Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_corresponding_object_index(gensym_window);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qid_of_identified_drawing_activity,
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
			    write_icp_unsigned_integer(id_of_identified_drawing_activity);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qid_of_identified_drawing_activity,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_unsigned_integer(id_of_identified_drawing_activity);
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_ping_drawing_reply,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qsend_icp_ping_drawing_reply,top,Nil);
		goto end_send_icp_ping_drawing_reply;
	    }
	}
	gensym_window = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : gensym_window;
	id_of_identified_drawing_activity = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : id_of_identified_drawing_activity;
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_ping_drawing_reply;
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
		  getfq_function_no_default(ISVREF(gensym_window,
		  (SI_Long)14L),Current_icp_port);
	  if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) && value)
	      gensym_window = value;
	  else {
	      value_1 = make_corresponding_icp_gensym_window(gensym_window);
	      if (EQ(icp_suspend_1,value_1)) {
		  resumable_icp_push(value);
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      gensym_window = value_1;
	  }
	l2:
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)190L)))) {
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
		  emit_icp_write_trace(T,Nil,Nil,Qping_drawing_reply,
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
			emit_icp_write_trace(T,Nil,Nil,Qgensym_window,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
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
			      write_icp_corresponding_object_index(gensym_window))) 
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
				  Qgensym_window,string_constant_4,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_corresponding_object_index(gensym_window))) {
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
				Qid_of_identified_drawing_activity,
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
			      write_icp_unsigned_integer(id_of_identified_drawing_activity))) 
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
				  Qid_of_identified_drawing_activity,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      temp_1 = result_of_write;
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_unsigned_integer(id_of_identified_drawing_activity))) 
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
			    Qping_drawing_reply,string_constant_1,Qmessage,
			    Nil,Nil,Nil,Nil);
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
		      emit_icp_write_trace(T,Nil,Nil,Qgensym_window,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
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
			    write_icp_corresponding_object_index(gensym_window))) 
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
				Qgensym_window,string_constant_4,Qargument,
				Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_corresponding_object_index(gensym_window))) {
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
			      Qid_of_identified_drawing_activity,
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
			    write_icp_unsigned_integer(id_of_identified_drawing_activity))) 
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
				Qid_of_identified_drawing_activity,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_unsigned_integer(id_of_identified_drawing_activity))) 
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
	      resumable_icp_push(id_of_identified_drawing_activity);
	      resumable_icp_push(gensym_window);
	      resumable_icp_push(Qsend_icp_ping_drawing_reply);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_ping_drawing_reply;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_ping_drawing_reply:
    return result;
}

/* HANDLE-ICP-PING-DRAWING-REPLY--BODY */
Object handle_icp_ping_drawing_reply__body(gensym_window,
	    id_of_identified_drawing_activity)
    Object gensym_window, id_of_identified_drawing_activity;
{
    x_note_fn_call(55,101);
    handle_ping_drawing_reply_1(gensym_window,
	    id_of_identified_drawing_activity);
    return VALUES_1(Nil);
}

static Object Qhandle_icp_ping_drawing_reply;  /* handle-icp-ping-drawing-reply */

/* HANDLE-ICP-PING-DRAWING-REPLY */
Object handle_icp_ping_drawing_reply()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, index_1, index_space, result_of_read;
    Object gensym_window, id_of_identified_drawing_activity;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(55,102);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qping_drawing_reply,
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
		      emit_icp_read_trace(T,Nil,Nil,Qgensym_window,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
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
				Qgensym_window,string_constant_4,Qargument,
				T,result_of_read,Nil,Nil);
		    gensym_window = result_of_read;
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
		      gensym_window = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      gensym_window = Nil;
	      }
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
			      Qid_of_identified_drawing_activity,
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
				Qid_of_identified_drawing_activity,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    id_of_identified_drawing_activity = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  id_of_identified_drawing_activity = 
			  read_icp_unsigned_integer();
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_ping_drawing_reply__body(gensym_window,
			id_of_identified_drawing_activity);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qping_drawing_reply,string_constant_1,Qmessage,
			  Nil,result_of_read,Nil,T);
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
		    emit_icp_read_trace(T,Nil,Nil,Qgensym_window,
			    string_constant_4,Qargument,Nil,Nil,Nil,Nil);
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
			      Qgensym_window,string_constant_4,Qargument,T,
			      result_of_read,Nil,Nil);
		  gensym_window = result_of_read;
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
		    gensym_window = ISVREF(ISVREF(ISVREF(index_space,
			    (SI_Long)2L),IFIX(index_1) >>  -  - 
			    (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    gensym_window = Nil;
	    }
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
			    Qid_of_identified_drawing_activity,
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
			      Qid_of_identified_drawing_activity,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  id_of_identified_drawing_activity = result_of_read;
		POP_SPECIAL();
	    }
	    else
		id_of_identified_drawing_activity = 
			read_icp_unsigned_integer();
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_ping_drawing_reply__body(gensym_window,
		      id_of_identified_drawing_activity);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_ping_drawing_reply,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qhandle_icp_ping_drawing_reply,top,Nil);
		goto end_handle_icp_ping_drawing_reply;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qping_drawing_reply,
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
		  gensym_window = resumable_icp_pop();
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
		      emit_icp_read_trace(T,Nil,Nil,Qgensym_window,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
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
			    resumable_icp_push(Qhandle_icp_ping_drawing_reply);
			    result = VALUES_1(Icp_suspend);
			    POP_SPECIAL();
			    POP_SPECIAL();
			    goto end_handle_icp_ping_drawing_reply;
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
				Qgensym_window,string_constant_4,Qargument,
				T,result_of_read,Nil,Nil);
		    gensym_window = result_of_read;
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
			  resumable_icp_push(Qhandle_icp_ping_drawing_reply);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_ping_drawing_reply;
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
		      gensym_window = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      gensym_window = Nil;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  id_of_identified_drawing_activity = resumable_icp_pop();
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
			      Qid_of_identified_drawing_activity,
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
			resumable_icp_push(gensym_window);
			resumable_icp_push(Qhandle_icp_ping_drawing_reply);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_ping_drawing_reply;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qid_of_identified_drawing_activity,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    id_of_identified_drawing_activity = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(gensym_window);
		      resumable_icp_push(Qhandle_icp_ping_drawing_reply);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_ping_drawing_reply;
		  }
		  id_of_identified_drawing_activity = value;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_ping_drawing_reply__body(gensym_window,
			id_of_identified_drawing_activity);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qping_drawing_reply,string_constant_1,Qmessage,
			  Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		gensym_window = resumable_icp_pop();
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
		    emit_icp_read_trace(T,Nil,Nil,Qgensym_window,
			    string_constant_4,Qargument,Nil,Nil,Nil,Nil);
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
			  resumable_icp_push(Qhandle_icp_ping_drawing_reply);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_ping_drawing_reply;
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
			      Qgensym_window,string_constant_4,Qargument,T,
			      result_of_read,Nil,Nil);
		  gensym_window = result_of_read;
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
			resumable_icp_push(Qhandle_icp_ping_drawing_reply);
			result = VALUES_1(Icp_suspend);
			goto end_handle_icp_ping_drawing_reply;
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
		    gensym_window = ISVREF(ISVREF(ISVREF(index_space,
			    (SI_Long)2L),IFIX(index_1) >>  -  - 
			    (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    gensym_window = Nil;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		id_of_identified_drawing_activity = resumable_icp_pop();
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
			    Qid_of_identified_drawing_activity,
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
		      resumable_icp_push(gensym_window);
		      resumable_icp_push(Qhandle_icp_ping_drawing_reply);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_ping_drawing_reply;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qid_of_identified_drawing_activity,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  id_of_identified_drawing_activity = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(gensym_window);
		    resumable_icp_push(Qhandle_icp_ping_drawing_reply);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_ping_drawing_reply;
		}
		id_of_identified_drawing_activity = value;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_ping_drawing_reply__body(gensym_window,
		      id_of_identified_drawing_activity);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_ping_drawing_reply:
    return result;
}

/* HANDLE-PING-DRAWING-REPLY-1 */
Object handle_ping_drawing_reply_1(gensym_window,
	    id_of_identified_drawing_activity)
    Object gensym_window, id_of_identified_drawing_activity;
{
    Object identified_drawing_activity_qm;

    x_note_fn_call(55,103);
    identified_drawing_activity_qm = 
	    find_identified_drawing_activity(gensym_window,
	    id_of_identified_drawing_activity);
    if (identified_drawing_activity_qm)
	return finish_pending_activity(identified_drawing_activity_qm);
    else
	return VALUES_1(Nil);
}

/* ICP-SOCKET-NUMBER-OF-OUTSTANDING-BYTES */
Object icp_socket_number_of_outstanding_bytes(icp_socket)
    Object icp_socket;
{
    x_note_fn_call(55,104);
    if (ISVREF(icp_socket,(SI_Long)24L))
	return VALUES_1(ISVREF(ISVREF(icp_socket,(SI_Long)24L),(SI_Long)14L));
    else
	return VALUES_1(FIX((SI_Long)-1L));
}

DEFINE_VARIABLE_WITH_SYMBOL(Flush_graphics_immediately_qm, Qflush_graphics_immediately_qm);

static Object Qnone;               /* none */

/* SYNCHRONIZE-ICP-ON-WINDOW-WITH-DRAWING */
Object synchronize_icp_on_window_with_drawing(current_window_1,
	    left_edge_of_draw_area,top_edge_of_draw_area,
	    right_edge_of_draw_area,bottom_edge_of_draw_area)
    Object current_window_1, left_edge_of_draw_area, top_edge_of_draw_area;
    Object right_edge_of_draw_area, bottom_edge_of_draw_area;
{
    Object svref_arg_1, svref_new_value, icp_supports_transparent_copy_p;
    Declare_special(5);
    Object result;

    x_note_fn_call(55,105);
    PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
	    4);
      PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
	      3);
	PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
		2);
	  PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
		  1);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
		    0);
	      svref_arg_1 = Current_window;
	      SVREF(svref_arg_1,FIX((SI_Long)38L)) = T;
	      svref_arg_1 = Current_window;
	      SVREF(svref_arg_1,FIX((SI_Long)39L)) = Qunknown;
	      svref_arg_1 = Current_window;
	      svref_new_value = Left_edge_of_draw_area;
	      SVREF(svref_arg_1,FIX((SI_Long)40L)) = svref_new_value;
	      svref_arg_1 = Current_window;
	      svref_new_value = Top_edge_of_draw_area;
	      SVREF(svref_arg_1,FIX((SI_Long)41L)) = svref_new_value;
	      svref_arg_1 = Current_window;
	      svref_new_value = Right_edge_of_draw_area;
	      SVREF(svref_arg_1,FIX((SI_Long)42L)) = svref_new_value;
	      svref_arg_1 = Current_window;
	      svref_new_value = Bottom_edge_of_draw_area;
	      SVREF(svref_arg_1,FIX((SI_Long)43L)) = svref_new_value;
	      icp_supports_transparent_copy_p = EQ(ISVREF(Current_window,
		      (SI_Long)1L),Qicp) ? 
		      (FIXNUM_LT(Icp_window_protocol_supports_transparent_copy,
		      ISVREF(Current_window,(SI_Long)11L)) ? T : Nil) : Qnil;
	      svref_arg_1 = Current_window;
	      svref_new_value = icp_supports_transparent_copy_p ? (EQ(Kxor,
		      Current_drawing_transfer_mode) ? FIX((SI_Long)0L) : 
		      FIX((SI_Long)1L)) : Qnone;
	      SVREF(svref_arg_1,FIX((SI_Long)44L)) = svref_new_value;
	      svref_arg_1 = Current_window;
	      svref_new_value = icp_supports_transparent_copy_p ? 
		      Current_background_color_value : Qnone;
	      result = VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)45L)) = 
		      svref_new_value);
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* ICP-MESSAGE-FUNCTIONS-ICP-PROLOGUE */
Object icp_message_functions_icp_prologue(message_name)
    Object message_name;
{
    Object svref_arg_1;

    x_note_fn_call(55,106);
    if (ISVREF(Current_window,(SI_Long)38L)) {
	svref_arg_1 = Current_window;
	SVREF(svref_arg_1,FIX((SI_Long)38L)) = Nil;
	icp_prologue_send_begin_window_update(Current_window);
	icp_prologue_set_transfer_mode(Current_window);
    }
    icp_prologue_set_background_color_value(Current_window);
    return VALUES_1(Nil);
}

/* ICP-PROLOGUE-SEND-BEGIN-WINDOW-UPDATE */
Object icp_prologue_send_begin_window_update(window)
    Object window;
{
    x_note_fn_call(55,107);
    send_icp_begin_window_update(window,ISVREF(window,(SI_Long)40L),
	    ISVREF(window,(SI_Long)41L),ISVREF(window,(SI_Long)42L),
	    ISVREF(window,(SI_Long)43L));
    return VALUES_1(Nil);
}

/* ICP-PROLOGUE-SET-TRANSFER-MODE */
Object icp_prologue_set_transfer_mode(window)
    Object window;
{
    Object desired_transfer_mode;

    x_note_fn_call(55,108);
    desired_transfer_mode = ISVREF(window,(SI_Long)44L);
    if ( !EQ(desired_transfer_mode,Qnone))
	send_icp_set_transfer_mode(desired_transfer_mode);
    return VALUES_1(Nil);
}

/* ICP-PROLOGUE-SET-BACKGROUND-COLOR-VALUE */
Object icp_prologue_set_background_color_value(window)
    Object window;
{
    Object desired;

    x_note_fn_call(55,109);
    desired = ISVREF(window,(SI_Long)45L);
    if ( !(EQ(desired,Qnone) || EQ(desired,ISVREF(window,(SI_Long)39L)))) {
	SVREF(window,FIX((SI_Long)39L)) = desired;
	send_icp_set_background_color_value(desired);
    }
    return VALUES_1(Nil);
}

/* SYNCHRONIZE-TRANSFER-MODE */
Object synchronize_transfer_mode()
{
    Object svref_arg_1;
    SI_Long svref_new_value;

    x_note_fn_call(55,110);
    if (BOUNDP(Qdrawing_on_window) && Drawing_on_window && 
	    EQ(Type_of_current_window,Qicp) && 
	    FIXNUM_LT(Icp_window_protocol_supports_transparent_copy,
	    ISVREF(Current_window,(SI_Long)11L))) {
	svref_arg_1 = Current_window;
	svref_new_value = EQ(Kxor,Current_drawing_transfer_mode) ? 
		(SI_Long)0L : (SI_Long)1L;
	ISVREF(svref_arg_1,(SI_Long)44L) = FIX(svref_new_value);
	return send_icp_set_transfer_mode(EQ(Kxor,
		Current_drawing_transfer_mode) ? FIX((SI_Long)0L) : 
		FIX((SI_Long)1L));
    }
    else
	return VALUES_1(Nil);
}

/* SYNCHRONIZE-BACKGROUND-COLOR-VALUE */
Object synchronize_background_color_value()
{
    Object svref_arg_1, svref_new_value;

    x_note_fn_call(55,111);
    if (EQ(Type_of_current_window,Qicp) && 
	    FIXNUM_LT(Icp_window_protocol_supports_transparent_copy,
	    ISVREF(Current_window,(SI_Long)11L))) {
	svref_arg_1 = Current_window;
	svref_new_value = Current_background_color_value;
	return VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)45L)) = 
		svref_new_value);
    }
    else
	return VALUES_1(Nil);
}

/* SET-CURRENT-BACKGROUND-COLOR-VALUE */
Object set_current_background_color_value(new_color_value)
    Object new_color_value;
{
    x_note_fn_call(55,112);
    if ( !FIXNUM_EQ(Current_background_color_value,new_color_value)) {
	Current_background_color_value = new_color_value;
	return synchronize_background_color_value();
    }
    else
	return VALUES_1(Nil);
}

Object Color_value_vector_index_and_intensity_prop = UNBOUND;

Object New_pastel_color_qm_prop = UNBOUND;

static Object Qnew_pastel_color_qm;  /* new-pastel-color? */

static Object Qcolor_value_vector_index_and_intensity;  /* color-value-vector-index-and-intensity */

/* DERIVE-STANDARD-GENSYM-COLOR-DATA */
Object derive_standard_gensym_color_data()
{
    Object color, r, g, b, alternative_name_qm, new_pastel_color_qm;
    Object ab_loop_list_, color_value_vector_index_and_intensity;
    Object ab_loop_iter_flag_, ab_loop_desetq_, temp, temp_1;
    SI_Long color_value_vector_index, temp_2;

    x_note_fn_call(55,113);
    color = Nil;
    r = Nil;
    g = Nil;
    b = Nil;
    alternative_name_qm = Nil;
    new_pastel_color_qm = Nil;
    ab_loop_list_ = Standard_gensym_color_alist;
    color_value_vector_index = (SI_Long)0L;
    color_value_vector_index_and_intensity = Nil;
    ab_loop_iter_flag_ = T;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    color = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    r = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    g = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    b = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    alternative_name_qm = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    new_pastel_color_qm = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	color_value_vector_index = color_value_vector_index + (SI_Long)1L;
    temp_1 = FIX(color_value_vector_index);
    temp_2 = ((SI_Long)30L * IFIX(r) + (SI_Long)59L * IFIX(g) + 
	    (SI_Long)11L * IFIX(b)) / (SI_Long)100L;
    temp = FIX(temp_2);
    color_value_vector_index_and_intensity = CONS(temp_1,temp);
    mutate_global_property(color,new_pastel_color_qm,Qnew_pastel_color_qm);
    mutate_global_property(color,color_value_vector_index_and_intensity,
	    Qcolor_value_vector_index_and_intensity);
    if (alternative_name_qm)
	mutate_global_property(alternative_name_qm,
		color_value_vector_index_and_intensity,
		Qcolor_value_vector_index_and_intensity);
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* HUE-SATURATION-VALUE */
Object hue_saturation_value(red_init,green_init,blue_init)
    Object red_init, green_init, blue_init;
{
    Object hue, red_distance, green_distance, blue_distance;
    SI_Long red, green, blue, temp, maximum, minimum, max_less_min, saturation;
    SI_Long result_1;

    x_note_fn_call(55,114);
    red = IFIX(red_init);
    green = IFIX(green_init);
    blue = IFIX(blue_init);
    temp = MAX(red,green);
    maximum = MAX(temp,blue);
    temp = MIN(red,green);
    minimum = MIN(temp,blue);
    max_less_min = maximum - minimum;
    saturation = maximum != (SI_Long)0L ? IFIX(l_round(FIX((SI_Long)100L * 
	    max_less_min),FIX(maximum))) : (SI_Long)0L;
    hue = FIX((SI_Long)0L);
    if (saturation == (SI_Long)0L)
	hue = FIX((SI_Long)0L);
    else {
	red_distance = l_round(FIX((SI_Long)100L * (maximum - red)),
		FIX(max_less_min));
	green_distance = l_round(FIX((SI_Long)100L * (maximum - green)),
		FIX(max_less_min));
	blue_distance = l_round(FIX((SI_Long)100L * (maximum - blue)),
		FIX(max_less_min));
	if (red == maximum)
	    hue = FIXNUM_MINUS(blue_distance,green_distance);
	else if (green == maximum)
	    hue = FIX((SI_Long)200L + IFIX(FIXNUM_MINUS(red_distance,
		    blue_distance)));
	else
	    hue = FIX((SI_Long)400L + IFIX(FIXNUM_MINUS(green_distance,
		    red_distance)));
    }
    if (IFIX(hue) < (SI_Long)0L)
	hue = FIX(IFIX(hue) + (SI_Long)600L);
    result_1 = (IFIX(hue) * (SI_Long)100L + saturation) * (SI_Long)256L + 
	    maximum;
    return VALUES_1(FIX(result_1));
}

/* HUE-LESS-P */
Object hue_less_p(color_1,color_2)
    Object color_1, color_2;
{
    Object red_1_qm, green_1_qm, blue_1_qm, red_2_qm, green_2_qm, blue_2_qm;
    Object temp;
    Object result;

    x_note_fn_call(55,115);
    result = rgb_from_color(color_1);
    MVS_3(result,red_1_qm,green_1_qm,blue_1_qm);
    if (red_1_qm) {
	result = rgb_from_color(color_2);
	MVS_3(result,red_2_qm,green_2_qm,blue_2_qm);
	if (red_2_qm) {
	    temp = hue_saturation_value(red_1_qm,green_1_qm,blue_1_qm);
	    return VALUES_1(FIXNUM_LT(temp,hue_saturation_value(red_2_qm,
		    green_2_qm,blue_2_qm)) ? T : Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qintensity;          /* intensity */

static Object Qalphabetic;         /* alphabetic */

static Object Qhue;                /* hue */

static Object Qhue_less_p;         /* hue-less-p */

/* COMPUTE-STANDARD-GENSYM-COLORS */
Object compute_standard_gensym_colors varargs_1(int, n)
{
    Object for_color_menu_qm;
    Object ordering_qm, color, r, g, b, alternative_name_qm, ab_loop_list_;
    Object hue_number, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object ab_loop_desetq_, temp, colors_with_hue_numbers;
    Declare_varargs_nonrelocating;

    x_note_fn_call(55,116);
    INIT_ARGS_nonrelocating();
    for_color_menu_qm = REQUIRED_ARG_nonrelocating();
    ordering_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    color = Nil;
    r = Nil;
    g = Nil;
    b = Nil;
    alternative_name_qm = Nil;
    ab_loop_list_ = Standard_gensym_color_alist;
    hue_number = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    color = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    r = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    g = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    b = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    alternative_name_qm = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    hue_number = FIX((SI_Long)4L * IFIX(r) + (SI_Long)2L * IFIX(g) + 
	    (SI_Long)1L * IFIX(b));
    ab_loopvar__2 = gensym_cons_1(gensym_cons_1(color,hue_number),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    if (alternative_name_qm &&  !TRUEP(for_color_menu_qm)) {
	ab_loopvar__2 = gensym_cons_1(gensym_cons_1(alternative_name_qm,
		hue_number),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    colors_with_hue_numbers = ab_loopvar_;
    goto end_1;
    colors_with_hue_numbers = Qnil;
  end_1:;
    if (EQ(ordering_qm,Qnil) || EQ(ordering_qm,Qintensity))
	colors_with_hue_numbers = sort(4,colors_with_hue_numbers,
		SYMBOL_FUNCTION(Qnum_lt),Kkey,SYMBOL_FUNCTION(Qcdr));
    else if (EQ(ordering_qm,Qalphabetic))
	colors_with_hue_numbers = sort(4,colors_with_hue_numbers,
		SYMBOL_FUNCTION(Qstring_lessp),Kkey,SYMBOL_FUNCTION(Qcar));
    else if (EQ(ordering_qm,Qhue))
	colors_with_hue_numbers = sort(4,colors_with_hue_numbers,
		SYMBOL_FUNCTION(Qhue_less_p),Kkey,SYMBOL_FUNCTION(Qcar));
    else
	colors_with_hue_numbers = Qnil;
    color = Nil;
    ab_loop_list_ = colors_with_hue_numbers;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    color = CAR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = gensym_cons_1(color,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop_1;
  end_loop_1:
    temp = ab_loopvar_;
    goto end_2;
    temp = Qnil;
  end_2:;
    reclaim_gensym_tree_1(colors_with_hue_numbers);
    return VALUES_1(temp);
}

Object All_metacolors = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(All_colors, Qall_colors);

DEFINE_VARIABLE_WITH_SYMBOL(Menu_colors, Qmenu_colors);

DEFINE_VARIABLE_WITH_SYMBOL(Menu_colors_sorted_alphabetically, Qmenu_colors_sorted_alphabetically);

DEFINE_VARIABLE_WITH_SYMBOL(Menu_colors_sorted_by_hue, Qmenu_colors_sorted_by_hue);

Object The_type_description_of_color_map = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_color_maps, Qchain_of_available_color_maps);

DEFINE_VARIABLE_WITH_SYMBOL(Color_map_count, Qcolor_map_count);

Object Chain_of_available_color_maps_vector = UNBOUND;

/* COLOR-MAP-STRUCTURE-MEMORY-USAGE */
Object color_map_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(55,117);
    temp = Color_map_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)8L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-COLOR-MAP-COUNT */
Object outstanding_color_map_count()
{
    Object def_structure_color_map_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(55,118);
    gensymed_symbol = IFIX(Color_map_count);
    def_structure_color_map_variable = Chain_of_available_color_maps;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_color_map_variable))
	goto end_loop;
    def_structure_color_map_variable = 
	    ISVREF(def_structure_color_map_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-COLOR-MAP-1 */
Object reclaim_color_map_1(color_map)
    Object color_map;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(55,119);
    inline_note_reclaim_cons(color_map,Nil);
    structure_being_reclaimed = color_map;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_gensym_list_1(ISVREF(color_map,(SI_Long)2L));
      SVREF(color_map,FIX((SI_Long)2L)) = Nil;
      reclaim_managed_array(ISVREF(color_map,(SI_Long)3L));
      SVREF(color_map,FIX((SI_Long)3L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_color_maps_vector,
	    IFIX(Current_thread_index));
    SVREF(color_map,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_color_maps_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = color_map;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-COLOR-MAP */
Object reclaim_structure_for_color_map(color_map)
    Object color_map;
{
    x_note_fn_call(55,120);
    return reclaim_color_map_1(color_map);
}

static Object Qg2_defstruct_structure_name_color_map_g2_struct;  /* g2-defstruct-structure-name::color-map-g2-struct */

/* MAKE-PERMANENT-COLOR-MAP-STRUCTURE-INTERNAL */
Object make_permanent_color_map_structure_internal()
{
    Object def_structure_color_map_variable, defstruct_g2_color_map_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(55,121);
    def_structure_color_map_variable = Nil;
    atomic_incff_symval(Qcolor_map_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_color_map_variable = Nil;
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
	defstruct_g2_color_map_variable = the_array;
	SVREF(defstruct_g2_color_map_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_color_map_g2_struct;
	def_structure_color_map_variable = defstruct_g2_color_map_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_color_map_variable);
}

/* MAKE-COLOR-MAP-STRUCTURE-1 */
Object make_color_map_structure_1(color_map_true_color_p,color_value_plist,
	    color_value_vector,color_value_for_black_qm,
	    color_value_for_white_qm)
    Object color_map_true_color_p, color_value_plist, color_value_vector;
    Object color_value_for_black_qm, color_value_for_white_qm;
{
    Object def_structure_color_map_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(55,122);
    def_structure_color_map_variable = 
	    ISVREF(Chain_of_available_color_maps_vector,
	    IFIX(Current_thread_index));
    if (def_structure_color_map_variable) {
	svref_arg_1 = Chain_of_available_color_maps_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_color_map_variable,(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_color_map_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_color_map_g2_struct;
    }
    else
	def_structure_color_map_variable = 
		make_permanent_color_map_structure_internal();
    inline_note_allocate_cons(def_structure_color_map_variable,Nil);
    SVREF(def_structure_color_map_variable,FIX((SI_Long)1L)) = 
	    color_map_true_color_p;
    SVREF(def_structure_color_map_variable,FIX((SI_Long)2L)) = 
	    color_value_plist;
    SVREF(def_structure_color_map_variable,FIX((SI_Long)3L)) = 
	    color_value_vector;
    SVREF(def_structure_color_map_variable,FIX((SI_Long)4L)) = 
	    color_value_for_black_qm;
    SVREF(def_structure_color_map_variable,FIX((SI_Long)5L)) = 
	    color_value_for_white_qm;
    return VALUES_1(def_structure_color_map_variable);
}

static Object Qblack;              /* black */

static Object Qwhite;              /* white */

/* MAKE-COLOR-MAP */
Object make_color_map(screen_depth,color_description_plist)
    Object screen_depth, color_description_plist;
{
    Object color_value_vector, color_value_for_black_qm;
    Object color_value_for_white_qm, color, color_value, ab_loop_list_;
    Object color_value_vector_index_and_intensity_qm, color_value_plist;
    Object ab_loopvar_, ab_loopvar__1, temp, gensymed_symbol, temp_1;
    SI_Long svref_arg_2;

    x_note_fn_call(55,123);
    color_value_vector = allocate_managed_array(1,
	    length(Standard_gensym_color_alist));
    color_value_for_black_qm = Nil;
    color_value_for_white_qm = Nil;
    color = Nil;
    color_value = Nil;
    ab_loop_list_ = color_description_plist;
    color_value_vector_index_and_intensity_qm = Nil;
    color_value_plist = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    color = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    temp = CAR(temp);
    color_value = CAR(temp);
    color_value_vector_index_and_intensity_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(color),
	    Qcolor_value_vector_index_and_intensity);
    if (color_value_vector_index_and_intensity_qm) {
	gensymed_symbol = CAR(color_value_vector_index_and_intensity_qm);
	if (FIXNUM_LE(ISVREF(color_value_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp_1 = FIXNUM_ADD(gensymed_symbol,Managed_array_index_offset);
	    SVREF(color_value_vector,temp_1) = color_value;
	}
	else {
	    temp_1 = ISVREF(color_value_vector,(IFIX(gensymed_symbol) >>  
		    -  - (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = IFIX(gensymed_symbol) & (SI_Long)1023L;
	    ISVREF(temp_1,svref_arg_2) = color_value;
	}
	if (EQ(color,Qblack))
	    color_value_for_black_qm = color_value;
	else if (EQ(color,Qwhite))
	    color_value_for_white_qm = color_value;
    }
    if ( !TRUEP(color_value_vector_index_and_intensity_qm)) {
	ab_loopvar__1 = gensym_list_2(color,color_value);
	if (ab_loopvar__1) {
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		color_value_plist = ab_loopvar__1;
	    ab_loopvar_ = last(ab_loopvar__1,_);
	}
    }
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:
    return make_color_map_structure_1(IFIX(screen_depth) >= (SI_Long)16L ? 
	    T : Nil,color_value_plist,color_value_vector,
	    color_value_for_black_qm,color_value_for_white_qm);
    return VALUES_1(Qnil);
}

/* RECLAIM-COLOR-MAP-IF-ANY */
Object reclaim_color_map_if_any(color_map_for_window)
    Object color_map_for_window;
{
    x_note_fn_call(55,124);
    if (color_map_for_window)
	return reclaim_color_map_1(color_map_for_window);
    else
	return VALUES_1(Nil);
}

/* FIND-NEAREST-COLOR */
Object find_nearest_color(color_alist,red,green,blue,search_gray_only_p)
    Object color_alist, red, green, blue, search_gray_only_p;
{
    Object best_entry, best_distance, entry, ab_loop_list_, color, r, g, b;
    Object temp, temp_1, temp_2, distance;

    x_note_fn_call(55,125);
    best_entry = Nil;
    best_distance = Most_positive_fixnum;
    entry = Nil;
    ab_loop_list_ = color_alist;
    color = Nil;
    r = Nil;
    g = Nil;
    b = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    color = CAR(entry);
    temp = CDR(entry);
    r = CAR(temp);
    temp = CDR(entry);
    temp = CDR(temp);
    g = CAR(temp);
    temp = CDR(entry);
    temp = CDR(temp);
    temp = CDR(temp);
    b = CAR(temp);
    if (search_gray_only_p ? FIXNUM_EQ(r,g) && FIXNUM_EQ(g,b) : TRUEP(T)) {
	temp_1 = FIXNUM_MINUS(r,red);
	temp_2 = FIXNUM_MINUS(g,green);
	temp = FIXNUM_MINUS(b,blue);
	distance = FIXNUM_ADD(FIXNUM_ADD(FIXNUM_ABS(temp_1),
		FIXNUM_ABS(temp_2)),FIXNUM_ABS(temp));
	if (FIXNUM_LT(distance,best_distance)) {
	    best_entry = entry;
	    best_distance = distance;
	}
    }
    goto next_loop;
  end_loop:;
    return VALUES_2(best_entry,best_distance);
}

Object Rgb_color_value_cache_prop = UNBOUND;

Object Rgb_color_intensity_cache_prop = UNBOUND;

Object Rgb_color_nearest_standard_color_cache_prop = UNBOUND;

static Object Qrgb_color_value_cache;  /* rgb-color-value-cache */

/* RGB-COLOR-P */
Object rgb_color_p(thing)
    Object thing;
{
    Object temp, value_qm;

    x_note_fn_call(55,126);
    if (SYMBOLP(thing)) {
	temp =  ! 
		!TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(thing),
		Qrgb_color_value_cache)) ? T : Nil;
	if (temp);
	else {
	    value_qm = rgb_color_value_qm(thing);
	    if (value_qm) {
		mutate_global_property(thing,value_qm,Qrgb_color_value_cache);
		temp = T;
	    }
	    else
		temp = Nil;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* RGB-COLOR-VALUE */
Object rgb_color_value(rgb_color)
    Object rgb_color;
{
    Object temp;

    x_note_fn_call(55,127);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(rgb_color),
	    Qrgb_color_value_cache);
    if (temp);
    else
	temp = mutate_global_property(rgb_color,
		rgb_color_value_qm(rgb_color),Qrgb_color_value_cache);
    return VALUES_1(temp);
}

/* RGB-COLOR-VALUE? */
Object rgb_color_value_qm(symbol)
    Object symbol;
{
    Object str, value, weight_qm, temp, b;
    SI_Long i, r, g, gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(55,128);
    str = SYMBOL_NAME(symbol);
    if (IFIX(length(str)) == (SI_Long)9L && CHAR_EQ(CHAR(str,
	    FIX((SI_Long)0L)),CHR('R')) && CHAR_EQ(CHAR(str,
	    FIX((SI_Long)1L)),CHR('G')) && CHAR_EQ(CHAR(str,
	    FIX((SI_Long)2L)),CHR('B'))) {
	value = FIX((SI_Long)0L);
	i = (SI_Long)3L;
	weight_qm = Nil;
      next_loop:
	if (i >= (SI_Long)9L)
	    goto end_loop;
	weight_qm = digit_char_p(CHR(ISCHAR(str,i)),FIX((SI_Long)16L));
	if ( !TRUEP(weight_qm)) {
	    temp = Nil;
	    goto end_1;
	}
	value = FIX(IFIX(value) << (SI_Long)4L | IFIX(weight_qm));
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	r = IFIX(value) >>  -  - (SI_Long)16L;
	g = IFIX(value) >>  -  - (SI_Long)8L;
	b = value;
	gensymed_symbol = IFIX(b) & (SI_Long)255L;
	gensymed_symbol_1 = (SI_Long)16L;
	gensymed_symbol_1 = gensymed_symbol << gensymed_symbol_1;
	gensymed_symbol_2 = g & (SI_Long)255L;
	gensymed_symbol = (SI_Long)8L;
	gensymed_symbol = gensymed_symbol_2 << gensymed_symbol;
	gensymed_symbol_2 = r & (SI_Long)255L;
	temp = FIX(gensymed_symbol_1 | gensymed_symbol | gensymed_symbol_2);
	goto end_1;
	temp = T;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qrgb_color_intensity_cache;  /* rgb-color-intensity-cache */

/* RGB-COLOR-INTENSITY */
Object rgb_color_intensity(rgb_color)
    Object rgb_color;
{
    Object temp, value, red, green, blue;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, temp_1;
    Object result;

    x_note_fn_call(55,129);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(rgb_color),
	    Qrgb_color_intensity_cache);
    if (temp);
    else {
	value = rgb_color_value(rgb_color);
	gensymed_symbol = IFIX(value) & (SI_Long)255L;
	gensymed_symbol_1 = IFIX(value) >>  -  - (SI_Long)8L & (SI_Long)255L;
	gensymed_symbol_2 = IFIX(value) >>  -  - (SI_Long)16L & (SI_Long)255L;
	result = VALUES_3(FIX(gensymed_symbol),FIX(gensymed_symbol_1),
		FIX(gensymed_symbol_2));
	MVS_3(result,red,green,blue);
	temp_1 = ((SI_Long)30L * IFIX(red) + (SI_Long)59L * IFIX(green) + 
		(SI_Long)11L * IFIX(blue)) / (SI_Long)100L;
	temp = mutate_global_property(rgb_color,FIX(temp_1),
		Qrgb_color_intensity_cache);
    }
    return VALUES_1(temp);
}

static Object Qrgb_color_nearest_standard_color_cache;  /* rgb-color-nearest-standard-color-cache */

/* RGB-COLOR-NEAREST-STANDARD-COLOR */
Object rgb_color_nearest_standard_color(rgb_color)
    Object rgb_color;
{
    Object temp, value, red, green, blue;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object result;

    x_note_fn_call(55,130);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(rgb_color),
	    Qrgb_color_nearest_standard_color_cache);
    if (temp);
    else {
	value = rgb_color_value(rgb_color);
	gensymed_symbol = IFIX(value) & (SI_Long)255L;
	gensymed_symbol_1 = IFIX(value) >>  -  - (SI_Long)8L & (SI_Long)255L;
	gensymed_symbol_2 = IFIX(value) >>  -  - (SI_Long)16L & (SI_Long)255L;
	result = VALUES_3(FIX(gensymed_symbol),FIX(gensymed_symbol_1),
		FIX(gensymed_symbol_2));
	MVS_3(result,red,green,blue);
	temp = find_nearest_color(Standard_gensym_color_alist,red,green,
		blue,Nil);
	temp = mutate_global_property(rgb_color,CAR(temp),
		Qrgb_color_nearest_standard_color_cache);
    }
    return VALUES_1(temp);
}

static Object Qforeground;         /* foreground */

static Object Qbackground;         /* background */

static Object Qtransparent;        /* transparent */

/* CANONICAL-COLOR-NAME */
Object canonical_color_name(color)
    Object color;
{
    Object temp, value, red, green, blue, closest_match, distance;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object result;

    x_note_fn_call(55,131);
    if (EQ(color,Qforeground) || EQ(color,Qbackground) || EQ(color,
	    Qtransparent))
	temp = color;
    else if (getfq_function_no_default(INLINE_SYMBOL_PLIST(color),
	    Qcolor_value_vector_index_and_intensity))
	temp = color;
    else if (rgb_color_p(color)) {
	value = rgb_color_value(color);
	gensymed_symbol = IFIX(value) & (SI_Long)255L;
	gensymed_symbol_1 = IFIX(value) >>  -  - (SI_Long)8L & (SI_Long)255L;
	gensymed_symbol_2 = IFIX(value) >>  -  - (SI_Long)16L & (SI_Long)255L;
	result = VALUES_3(FIX(gensymed_symbol),FIX(gensymed_symbol_1),
		FIX(gensymed_symbol_2));
	MVS_3(result,red,green,blue);
	result = find_nearest_color(Standard_gensym_color_alist,red,green,
		blue,Nil);
	MVS_2(result,closest_match,distance);
	temp = (SI_Long)0L == IFIX(distance) ? CAR(closest_match) : color;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* TWRITE-COLOR */
Object twrite_color(color)
    Object color;
{
    Object temp;

    x_note_fn_call(55,132);
    temp = rgb_color_p(color) ? twrite_symbol(2,color,T) : twrite_symbol(1,
	    color);
    return VALUES_1(temp);
}

/* RGB-FROM-COLOR */
Object rgb_from_color(color)
    Object color;
{
    Object entry, ab_loop_list_, value;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(55,133);
    entry = Nil;
    ab_loop_list_ = Standard_gensym_color_alist;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(FIRST(entry),color) || EQ(FIFTH(entry),color))
	return VALUES_3(SECOND(entry),THIRD(entry),FOURTH(entry));
    goto next_loop;
  end_loop:
    if (rgb_color_p(color)) {
	value = rgb_color_value(color);
	gensymed_symbol = IFIX(value) & (SI_Long)255L;
	gensymed_symbol_1 = IFIX(value) >>  -  - (SI_Long)8L & (SI_Long)255L;
	gensymed_symbol_2 = IFIX(value) >>  -  - (SI_Long)16L & (SI_Long)255L;
	return VALUES_3(FIX(gensymed_symbol),FIX(gensymed_symbol_1),
		FIX(gensymed_symbol_2));
    }
    return VALUES_1(Qnil);
}

/* RGB-VALUE-OF-GENSYM-COLOR */
Object rgb_value_of_gensym_color(color)
    Object color;
{
    Object r, g, b;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object result;

    x_note_fn_call(55,134);
    if (EQ(color,Qforeground) || EQ(color,Qbackground) || EQ(color,
	    Qtransparent) || 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(color),
	    Qcolor_value_vector_index_and_intensity) || rgb_color_p(color)) {
	result = rgb_from_color(color);
	MVS_3(result,r,g,b);
	gensymed_symbol = IFIX(b) & (SI_Long)255L;
	gensymed_symbol_1 = (SI_Long)16L;
	gensymed_symbol_1 = gensymed_symbol << gensymed_symbol_1;
	gensymed_symbol_2 = IFIX(g) & (SI_Long)255L;
	gensymed_symbol = (SI_Long)8L;
	gensymed_symbol = gensymed_symbol_2 << gensymed_symbol;
	gensymed_symbol_2 = IFIX(r) & (SI_Long)255L;
	return VALUES_1(FIX(gensymed_symbol_1 | gensymed_symbol | 
		gensymed_symbol_2));
    }
    else if (rgb_color_p(color))
	return rgb_color_value(color);
    else
	return VALUES_1(FIX((SI_Long)0L));
}

/* MAP-TO-BLACK-OR-WHITE */
Object map_to_black_or_white(color)
    Object color;
{
    Object color_value_vector_index_and_intensity_qm, temp;

    x_note_fn_call(55,135);
    color_value_vector_index_and_intensity_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(color),
	    Qcolor_value_vector_index_and_intensity);
    if (color_value_vector_index_and_intensity_qm)
	temp = FIXNUM_GE(CDR(color_value_vector_index_and_intensity_qm),
		Minimum_intensity_for_white) ? Qwhite : Qblack;
    else if (rgb_color_p(color))
	temp = FIXNUM_GE(rgb_color_intensity(color),
		Minimum_intensity_for_white) ? Qwhite : Qblack;
    else
	temp = Qblack;
    return VALUES_1(temp);
}

/* MAP-TO-COLOR-VALUE-1 */
Object map_to_color_value_1(color)
    Object color;
{
    Object color_value, color_value_vector_index_and_intensity_qm;
    Object gensymed_symbol, gensymed_symbol_1, color_1, svref_arg_1;

    x_note_fn_call(55,136);
    if (EQ(color,Qblack))
	color_value = ISVREF(Current_color_map,(SI_Long)4L);
    else if (EQ(color,Qwhite))
	color_value = ISVREF(Current_color_map,(SI_Long)5L);
    else
	color_value = Qnil;
    if (color_value);
    else {
	color_value_vector_index_and_intensity_qm = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(color),
		Qcolor_value_vector_index_and_intensity);
	if (color_value_vector_index_and_intensity_qm) {
	    gensymed_symbol = ISVREF(Current_color_map,(SI_Long)3L);
	    gensymed_symbol_1 = CAR(color_value_vector_index_and_intensity_qm);
	    color_value = FIXNUM_LE(ISVREF(ISVREF(Current_color_map,
		    (SI_Long)3L),(SI_Long)1L),Maximum_in_place_array_size) 
		    ? ISVREF(ISVREF(Current_color_map,(SI_Long)3L),
		    IFIX(FIXNUM_ADD(gensymed_symbol_1,
		    Managed_array_index_offset))) : 
		    ISVREF(ISVREF(gensymed_symbol,(IFIX(gensymed_symbol_1) 
		    >>  -  - (SI_Long)10L) + (SI_Long)2L),
		    IFIX(gensymed_symbol_1) & (SI_Long)1023L);
	}
	else
	    color_value = Nil;
    }
    if (color_value);
    else if (rgb_color_p(color)) {
	if (ISVREF(Current_color_map,(SI_Long)1L))
	    color_value = rgb_color_value(color);
	else {
	    color_1 = rgb_color_nearest_standard_color(color);
	    color_value_vector_index_and_intensity_qm = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(color_1),
		    Qcolor_value_vector_index_and_intensity);
	    if (color_value_vector_index_and_intensity_qm) {
		gensymed_symbol = ISVREF(Current_color_map,(SI_Long)3L);
		gensymed_symbol_1 = 
			CAR(color_value_vector_index_and_intensity_qm);
		color_value = FIXNUM_LE(ISVREF(ISVREF(Current_color_map,
			(SI_Long)3L),(SI_Long)1L),
			Maximum_in_place_array_size) ? 
			ISVREF(ISVREF(Current_color_map,(SI_Long)3L),
			IFIX(FIXNUM_ADD(gensymed_symbol_1,
			Managed_array_index_offset))) : 
			ISVREF(ISVREF(gensymed_symbol,
			(IFIX(gensymed_symbol_1) >>  -  - (SI_Long)10L) + 
			(SI_Long)2L),IFIX(gensymed_symbol_1) & (SI_Long)1023L);
	    }
	    else
		color_value = Nil;
	}
    }
    else
	color_value = Nil;
    if (color_value);
    else
	color_value = getfq_function_no_default(ISVREF(Current_color_map,
		(SI_Long)2L),color);
    if (color_value);
    else
	color_value = getfq_function_no_default(INLINE_SYMBOL_PLIST(color),
		Qnew_pastel_color_qm) ? ISVREF(Current_color_map,
		(SI_Long)5L) : ISVREF(Current_color_map,(SI_Long)4L);
    if (color_value);
    else
	color_value = FIX((SI_Long)0L);
    svref_arg_1 = Current_color_map;
    SVREF(svref_arg_1,FIX((SI_Long)6L)) = color;
    svref_arg_1 = Current_color_map;
    SVREF(svref_arg_1,FIX((SI_Long)7L)) = color_value;
    return VALUES_1(color_value);
}

/* MAP-TO-COLOR-VALUE */
Object map_to_color_value(color)
    Object color;
{
    x_note_fn_call(55,137);
    if (EQ(color,ISVREF(Current_color_map,(SI_Long)6L)))
	return VALUES_1(ISVREF(Current_color_map,(SI_Long)7L));
    else
	return map_to_color_value_1(color);
}

/* MAP-TO-COLOR */
Object map_to_color(color_value)
    Object color_value;
{
    Object color, ab_loop_list_, ab_loop_desetq_;

    x_note_fn_call(55,138);
    color = Nil;
    ab_loop_list_ = Standard_gensym_color_alist;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    color = CAR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (FIXNUM_EQ(color_value,map_to_color_value(color)))
	return VALUES_1(color);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qcolor_map;          /* color-map */

static Object string_constant_5;   /* "[value]" */

static Object Qvalue;              /* value */

static Object Qread_icp_color_map_using_function;  /* read-icp-color-map-using-function */

/* READ-ICP-COLOR-MAP-USING-FUNCTION */
Object read_icp_color_map_using_function()
{
    Object tracep, byte_count_before, current_icp_read_trace_level;
    Object result_of_read, temp, resumable_icp_state_1, icp_suspend_1, top;
    Object value;
    Declare_special(1);
    Object result;

    x_note_fn_call(55,139);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qcolor_map,string_constant_5,
			Qvalue,Nil,Nil,Nil,Nil);
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
			  instantaneous_icp_reader_byte_count(),Qcolor_map,
			  string_constant_5,Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else
	    temp = read_icp_unsigned_integer();
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qread_icp_color_map_using_function,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qread_icp_color_map_using_function,top,Nil);
		goto end_read_icp_color_map_using_function;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qcolor_map,string_constant_5,
			Qvalue,Nil,Nil,Nil,Nil);
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
		  resumable_icp_push(Qread_icp_color_map_using_function);
		  result = VALUES_1(Icp_suspend);
		  POP_SPECIAL();
		  goto end_read_icp_color_map_using_function;
	      }
	      result_of_read = value;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),Qcolor_map,
			  string_constant_5,Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    value = read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		resumable_icp_push(Qread_icp_color_map_using_function);
		result = VALUES_1(Icp_suspend);
		goto end_read_icp_color_map_using_function;
	    }
	    temp = value;
	}
    }
    result = VALUES_1(temp);
  end_read_icp_color_map_using_function:
    return result;
}

static Object Qwrite_icp_color_map_using_function;  /* write-icp-color-map-using-function */

/* WRITE-ICP-COLOR-MAP-USING-FUNCTION */
Object write_icp_color_map_using_function(color_map)
    Object color_map;
{
    Object tracep, byte_count_before, current_icp_write_trace_level;
    Object result_of_write, temp, resumable_icp_state_1, icp_suspend_1, top;
    Object value;
    Declare_special(1);
    Object result;

    x_note_fn_call(55,140);
    if (Disable_resumability) {
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,Qcolor_map,
			string_constant_5,Qvalue,T,color_map,Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      result_of_write = write_icp_unsigned_integer(FIX((SI_Long)0L));
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),Qcolor_map,
			  string_constant_5,Qvalue,Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else
	    temp = write_icp_unsigned_integer(FIX((SI_Long)0L));
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qwrite_icp_color_map_using_function,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qwrite_icp_color_map_using_function,top,Nil);
		goto end_write_icp_color_map_using_function;
	    }
	}
	color_map = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : color_map;
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,Qcolor_map,
			string_constant_5,Qvalue,T,color_map,Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      value = write_icp_unsigned_integer(FIX((SI_Long)0L));
	      if (EQ(icp_suspend_1,value)) {
		  resumable_icp_push(color_map);
		  resumable_icp_push(Qwrite_icp_color_map_using_function);
		  result = VALUES_1(Icp_suspend);
		  POP_SPECIAL();
		  goto end_write_icp_color_map_using_function;
	      }
	      result_of_write = value;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),Qcolor_map,
			  string_constant_5,Qvalue,Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else {
	    value = write_icp_unsigned_integer(FIX((SI_Long)0L));
	    if (EQ(icp_suspend_1,value)) {
		resumable_icp_push(color_map);
		resumable_icp_push(Qwrite_icp_color_map_using_function);
		result = VALUES_1(Icp_suspend);
		goto end_write_icp_color_map_using_function;
	    }
	    temp = value;
	}
    }
    result = VALUES_1(temp);
  end_write_icp_color_map_using_function:
    return result;
}

static Object Qset_up_palette;     /* set-up-palette */

/* SET-UP-PALETTE */
Object set_up_palette(gensym_window,color_map)
    Object gensym_window, color_map;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, tracep_2, byte_count_before_2;
    Object resumable_icp_state_1, icp_suspend_1, top, key, value, value_1;
    Declare_special(4);
    Object result;

    x_note_fn_call(55,141);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		3);
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
	      SVREF(temp,svref_arg_2) = Qset_up_palette;
	  }
	  if (EQ(Type_of_current_window,Qicp)) {
	      icp_message_functions_icp_prologue(Qset_up_palette);
	      temp_1 = getfq_function_no_default(ISVREF(gensym_window,
		      (SI_Long)14L),Current_icp_port);
	      if (temp_1);
	      else
		  temp_1 = make_corresponding_icp_gensym_window(gensym_window);
	      gensym_window = temp_1;
	      start_writing_icp_message(FIX((SI_Long)23L));
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)2L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qset_up_palette,
			      string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  2);
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,Qgensym_window,
				    string_constant_4,Qargument,Nil,Nil,
				    Nil,Nil);
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
				  write_icp_corresponding_object_index(gensym_window);
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qgensym_window,string_constant_4,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else
			write_icp_corresponding_object_index(gensym_window);
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,Qcolor_map,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
				1);
			  if (Icp_write_trace_cutoff_level_qm) {
			      tracep_2 = 
				      EQ(Icp_write_trace_cutoff_level_qm,
				      T) ? T : Nil;
			      if (tracep_2);
			      else
				  tracep_2 = 
					  IFIX(Icp_write_trace_cutoff_level_qm) 
					  >= (SI_Long)4L ? T : Nil;
			      if (tracep_2) {
				  emit_icp_write_trace(T,Nil,Nil,
					  Qcolor_map,string_constant_5,
					  Qvalue,T,color_map,Nil,Nil);
				  byte_count_before_2 = 
					  instantaneous_icp_writer_byte_count();
			      }
			      else
				  byte_count_before_2 = Nil;
			      current_icp_write_trace_level = 
				      FIXNUM_ADD1(Current_icp_write_trace_level);
			      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
				      0);
				result_of_write = 
					write_icp_unsigned_integer(FIX((SI_Long)0L));
				if (tracep_2)
				    emit_icp_write_trace(Nil,
					    byte_count_before_2,
					    instantaneous_icp_writer_byte_count(),
					    Qcolor_map,string_constant_5,
					    Qvalue,Nil,Nil,Nil,Nil);
			      POP_SPECIAL();
			  }
			  else
			      result_of_write = 
				      write_icp_unsigned_integer(FIX((SI_Long)0L));
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qcolor_map,string_constant_2,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)4L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,Qcolor_map,
				    string_constant_5,Qvalue,T,color_map,
				    Nil,Nil);
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
				  write_icp_unsigned_integer(FIX((SI_Long)0L));
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qcolor_map,string_constant_5,Qvalue,
				      Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else
			result_of_write = 
				write_icp_unsigned_integer(FIX((SI_Long)0L));
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qset_up_palette,string_constant_1,Qmessage,
				Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else {
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qgensym_window,
				  string_constant_4,Qargument,Nil,Nil,Nil,Nil);
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
				write_icp_corresponding_object_index(gensym_window);
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qgensym_window,string_constant_4,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else
		      write_icp_corresponding_object_index(gensym_window);
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qcolor_map,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			      1);
			if (Icp_write_trace_cutoff_level_qm) {
			    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,
				    T) ? T : Nil;
			    if (tracep_1);
			    else
				tracep_1 = 
					IFIX(Icp_write_trace_cutoff_level_qm) 
					>= (SI_Long)4L ? T : Nil;
			    if (tracep_1) {
				emit_icp_write_trace(T,Nil,Nil,Qcolor_map,
					string_constant_5,Qvalue,T,
					color_map,Nil,Nil);
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
				      write_icp_unsigned_integer(FIX((SI_Long)0L));
			      if (tracep_1)
				  emit_icp_write_trace(Nil,
					  byte_count_before_1,
					  instantaneous_icp_writer_byte_count(),
					  Qcolor_map,string_constant_5,
					  Qvalue,Nil,Nil,Nil,Nil);
			    POP_SPECIAL();
			}
			else
			    result_of_write = 
				    write_icp_unsigned_integer(FIX((SI_Long)0L));
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qcolor_map,string_constant_2,Qargument,
				    Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)4L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qcolor_map,
				  string_constant_5,Qvalue,T,color_map,Nil,
				  Nil);
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
				write_icp_unsigned_integer(FIX((SI_Long)0L));
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qcolor_map,string_constant_5,Qvalue,
				    Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else
		      write_icp_unsigned_integer(FIX((SI_Long)0L));
	      }
	  }
	  else if (EQ(Type_of_current_window,Qprinter)) {
	      temp_1 = aref1(Icp_printing_message_handler_array,
		      FIX((SI_Long)23L));
	      FUNCALL_2(temp_1,gensym_window,color_map);
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qset_up_palette,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qset_up_palette,top,Nil);
		goto end_set_up_palette;
	    }
	}
	gensym_window = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : gensym_window;
	color_map = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : color_map;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		3);
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
	      SVREF(temp,svref_arg_2) = Qset_up_palette;
	  }
	  key = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		  resumable_icp_pop() : Type_of_current_window;
	  if (EQ(key,Qicp)) {
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
	      icp_message_functions_icp_prologue(Qset_up_palette);
	    l1:
	      value = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
		       TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : 
		      getfq_function_no_default(ISVREF(gensym_window,
		      (SI_Long)14L),Current_icp_port);
	      if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) && value)
		  gensym_window = value;
	      else {
		  value_1 = 
			  make_corresponding_icp_gensym_window(gensym_window);
		  if (EQ(icp_suspend_1,value_1)) {
		      resumable_icp_push(value);
		      resumable_icp_push(FIX((SI_Long)1L));
		      temp_1 = Icp_suspend;
		      goto end_block;
		  }
		  gensym_window = value_1;
	      }
	    l2:
	      if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)23L)))) {
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
		      emit_icp_write_trace(T,Nil,Nil,Qset_up_palette,
			      string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  2);
		    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
			    : TRUEP(Nil)) {
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
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,Qgensym_window,
				    string_constant_4,Qargument,Nil,Nil,
				    Nil,Nil);
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
				  write_icp_corresponding_object_index(gensym_window))) 
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
				      Qgensym_window,string_constant_4,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else if (EQ(icp_suspend_1,
			    write_icp_corresponding_object_index(gensym_window))) 
				{
			resumable_icp_push(FIX((SI_Long)1L));
			temp_1 = Icp_suspend;
			goto end_block_1;
		    }
		  l2_1:
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,Qcolor_map,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
				1);
			  if (Icp_write_trace_cutoff_level_qm) {
			      tracep_2 = 
				      EQ(Icp_write_trace_cutoff_level_qm,
				      T) ? T : Nil;
			      if (tracep_2);
			      else
				  tracep_2 = 
					  IFIX(Icp_write_trace_cutoff_level_qm) 
					  >= (SI_Long)4L ? T : Nil;
			      if (tracep_2) {
				  emit_icp_write_trace(T,Nil,Nil,
					  Qcolor_map,string_constant_5,
					  Qvalue,T,color_map,Nil,Nil);
				  byte_count_before_2 = 
					  instantaneous_icp_writer_byte_count();
			      }
			      else
				  byte_count_before_2 = Nil;
			      current_icp_write_trace_level = 
				      FIXNUM_ADD1(Current_icp_write_trace_level);
			      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
				      0);
				result_of_write = 
					write_icp_unsigned_integer(FIX((SI_Long)0L));
				if (tracep_2)
				    emit_icp_write_trace(Nil,
					    byte_count_before_2,
					    instantaneous_icp_writer_byte_count(),
					    Qcolor_map,string_constant_5,
					    Qvalue,Nil,Nil,Nil,Nil);
				temp_1 = result_of_write;
			      POP_SPECIAL();
			  }
			  else
			      temp_1 = 
				      write_icp_unsigned_integer(FIX((SI_Long)0L));
			  if (EQ(icp_suspend_1,temp_1)) {
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
				      Qcolor_map,string_constant_2,
				      Qargument,Nil,Nil,Nil,Nil);
			  temp_1 = result_of_write;
			POP_SPECIAL();
		    }
		    else {
			if (Icp_write_trace_cutoff_level_qm) {
			    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,
				    T) ? T : Nil;
			    if (tracep_1);
			    else
				tracep_1 = 
					IFIX(Icp_write_trace_cutoff_level_qm) 
					>= (SI_Long)4L ? T : Nil;
			    if (tracep_1) {
				emit_icp_write_trace(T,Nil,Nil,Qcolor_map,
					string_constant_5,Qvalue,T,
					color_map,Nil,Nil);
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
				      write_icp_unsigned_integer(FIX((SI_Long)0L));
			      if (tracep_1)
				  emit_icp_write_trace(Nil,
					  byte_count_before_1,
					  instantaneous_icp_writer_byte_count(),
					  Qcolor_map,string_constant_5,
					  Qvalue,Nil,Nil,Nil,Nil);
			      temp_1 = result_of_write;
			    POP_SPECIAL();
			}
			else
			    temp_1 = 
				    write_icp_unsigned_integer(FIX((SI_Long)0L));
			if (EQ(icp_suspend_1,temp_1)) {
			    resumable_icp_push(FIX((SI_Long)2L));
			    temp_1 = Icp_suspend;
			    goto end_block_1;
			}
			else
			    temp_1 = Nil;
		    }
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
				Qset_up_palette,string_constant_1,Qmessage,
				Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else {
		  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			  TRUEP(Nil)) {
		      temp_1 = resumable_icp_pop();
		      if (! !(FIXNUMP(temp_1) && 
			      FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			      FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
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
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qgensym_window,
				  string_constant_4,Qargument,Nil,Nil,Nil,Nil);
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
				write_icp_corresponding_object_index(gensym_window))) 
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
				    Qgensym_window,string_constant_4,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else if (EQ(icp_suspend_1,
			  write_icp_corresponding_object_index(gensym_window))) 
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
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qcolor_map,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			      1);
			if (Icp_write_trace_cutoff_level_qm) {
			    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,
				    T) ? T : Nil;
			    if (tracep_1);
			    else
				tracep_1 = 
					IFIX(Icp_write_trace_cutoff_level_qm) 
					>= (SI_Long)4L ? T : Nil;
			    if (tracep_1) {
				emit_icp_write_trace(T,Nil,Nil,Qcolor_map,
					string_constant_5,Qvalue,T,
					color_map,Nil,Nil);
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
				      write_icp_unsigned_integer(FIX((SI_Long)0L));
			      if (tracep_1)
				  emit_icp_write_trace(Nil,
					  byte_count_before_1,
					  instantaneous_icp_writer_byte_count(),
					  Qcolor_map,string_constant_5,
					  Qvalue,Nil,Nil,Nil,Nil);
			      temp_1 = result_of_write;
			    POP_SPECIAL();
			}
			else
			    temp_1 = 
				    write_icp_unsigned_integer(FIX((SI_Long)0L));
			if (EQ(icp_suspend_1,temp_1)) {
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
				    Qcolor_map,string_constant_2,Qargument,
				    Nil,Nil,Nil,Nil);
			temp_1 = result_of_write;
		      POP_SPECIAL();
		  }
		  else {
		      if (Icp_write_trace_cutoff_level_qm) {
			  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				  T : Nil;
			  if (tracep);
			  else
			      tracep = 
				      IFIX(Icp_write_trace_cutoff_level_qm) 
				      >= (SI_Long)4L ? T : Nil;
			  if (tracep) {
			      emit_icp_write_trace(T,Nil,Nil,Qcolor_map,
				      string_constant_5,Qvalue,T,color_map,
				      Nil,Nil);
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
				    write_icp_unsigned_integer(FIX((SI_Long)0L));
			    if (tracep)
				emit_icp_write_trace(Nil,byte_count_before,
					instantaneous_icp_writer_byte_count(),
					Qcolor_map,string_constant_5,
					Qvalue,Nil,Nil,Nil,Nil);
			    temp_1 = result_of_write;
			  POP_SPECIAL();
		      }
		      else
			  temp_1 = 
				  write_icp_unsigned_integer(FIX((SI_Long)0L));
		      if (EQ(icp_suspend_1,temp_1)) {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  goto end_block_2;
		      }
		      else
			  temp_1 = Nil;
		  }
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
		  resumable_icp_push(key);
		  resumable_icp_push(color_map);
		  resumable_icp_push(gensym_window);
		  resumable_icp_push(Qset_up_palette);
		  result = VALUES_1(Icp_suspend);
		  POP_SPECIAL();
		  goto end_set_up_palette;
	      }
	  }
	  else if (EQ(key,Qprinter)) {
	      temp_1 = aref1(Icp_printing_message_handler_array,
		      FIX((SI_Long)23L));
	      FUNCALL_2(temp_1,gensym_window,color_map);
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_set_up_palette:
    return result;
}

static Object Qhandle_icp_set_up_palette;  /* handle-icp-set-up-palette */

/* HANDLE-ICP-SET-UP-PALETTE */
Object handle_icp_set_up_palette()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, index_1, index_space, result_of_read;
    Object gensym_window, tracep_2, byte_count_before_2, color_map, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(3);
    Object result;

    x_note_fn_call(55,142);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qset_up_palette,
			string_constant_3,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    2);
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
		      emit_icp_read_trace(T,Nil,Nil,Qgensym_window,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
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
				Qgensym_window,string_constant_4,Qargument,
				T,result_of_read,Nil,Nil);
		    gensym_window = result_of_read;
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
		      gensym_window = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      gensym_window = Nil;
	      }
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
		      emit_icp_read_trace(T,Nil,Nil,Qcolor_map,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  1);
		    if (Icp_read_trace_cutoff_level_qm) {
			tracep_2 = EQ(Icp_read_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_2);
			else
			    tracep_2 = 
				    IFIX(Icp_read_trace_cutoff_level_qm) 
				    >= (SI_Long)4L ? T : Nil;
			if (tracep_2) {
			    emit_icp_read_trace(T,Nil,Nil,Qcolor_map,
				    string_constant_5,Qvalue,Nil,Nil,Nil,Nil);
			    byte_count_before_2 = 
				    instantaneous_icp_reader_byte_count();
			}
			else
			    byte_count_before_2 = Nil;
			current_icp_read_trace_level = 
				FIXNUM_ADD1(Current_icp_read_trace_level);
			PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
				0);
			  result_of_read = read_icp_unsigned_integer();
			  if (tracep_2)
			      emit_icp_read_trace(Nil,byte_count_before_2,
				      instantaneous_icp_reader_byte_count(),
				      Qcolor_map,string_constant_5,Qvalue,
				      T,result_of_read,Nil,Nil);
			POP_SPECIAL();
		    }
		    else
			result_of_read = read_icp_unsigned_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcolor_map,string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    color_map = result_of_read;
		  POP_SPECIAL();
	      }
	      else if (Icp_read_trace_cutoff_level_qm) {
		  tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep_1);
		  else
		      tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			      (SI_Long)4L ? T : Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qcolor_map,
			      string_constant_5,Qvalue,Nil,Nil,Nil,Nil);
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
				Qcolor_map,string_constant_5,Qvalue,T,
				result_of_read,Nil,Nil);
		    color_map = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  color_map = read_icp_unsigned_integer();
	      result_of_read = set_up_palette(gensym_window,color_map);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qset_up_palette,string_constant_3,Qmessage,Nil,
			  result_of_read,Nil,T);
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
		    emit_icp_read_trace(T,Nil,Nil,Qgensym_window,
			    string_constant_4,Qargument,Nil,Nil,Nil,Nil);
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
			      Qgensym_window,string_constant_4,Qargument,T,
			      result_of_read,Nil,Nil);
		  gensym_window = result_of_read;
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
		    gensym_window = ISVREF(ISVREF(ISVREF(index_space,
			    (SI_Long)2L),IFIX(index_1) >>  -  - 
			    (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    gensym_window = Nil;
	    }
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
		    emit_icp_read_trace(T,Nil,Nil,Qcolor_map,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			1);
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)4L ? T : Nil;
		      if (tracep_1) {
			  emit_icp_read_trace(T,Nil,Nil,Qcolor_map,
				  string_constant_5,Qvalue,Nil,Nil,Nil,Nil);
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
				    Qcolor_map,string_constant_5,Qvalue,T,
				    result_of_read,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else
		      result_of_read = read_icp_unsigned_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcolor_map,string_constant_2,Qargument,T,
			      result_of_read,Nil,Nil);
		  color_map = result_of_read;
		POP_SPECIAL();
	    }
	    else if (Icp_read_trace_cutoff_level_qm) {
		tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		if (tracep);
		else
		    tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			    (SI_Long)4L ? T : Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qcolor_map,
			    string_constant_5,Qvalue,Nil,Nil,Nil,Nil);
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
			      Qcolor_map,string_constant_5,Qvalue,T,
			      result_of_read,Nil,Nil);
		  color_map = result_of_read;
		POP_SPECIAL();
	    }
	    else
		color_map = read_icp_unsigned_integer();
	    set_up_palette(gensym_window,color_map);
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_set_up_palette,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qhandle_icp_set_up_palette,top,Nil);
		goto end_handle_icp_set_up_palette;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qset_up_palette,
			string_constant_3,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    2);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  gensym_window = resumable_icp_pop();
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
		      emit_icp_read_trace(T,Nil,Nil,Qgensym_window,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
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
			    resumable_icp_push(Qhandle_icp_set_up_palette);
			    result = VALUES_1(Icp_suspend);
			    POP_SPECIAL();
			    POP_SPECIAL();
			    goto end_handle_icp_set_up_palette;
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
				Qgensym_window,string_constant_4,Qargument,
				T,result_of_read,Nil,Nil);
		    gensym_window = result_of_read;
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
			  resumable_icp_push(Qhandle_icp_set_up_palette);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_set_up_palette;
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
		      gensym_window = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      gensym_window = Nil;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  color_map = resumable_icp_pop();
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
		      emit_icp_read_trace(T,Nil,Nil,Qcolor_map,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  1);
		    if (Icp_read_trace_cutoff_level_qm) {
			tracep_2 = EQ(Icp_read_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_2);
			else
			    tracep_2 = 
				    IFIX(Icp_read_trace_cutoff_level_qm) 
				    >= (SI_Long)4L ? T : Nil;
			if (tracep_2) {
			    emit_icp_read_trace(T,Nil,Nil,Qcolor_map,
				    string_constant_5,Qvalue,Nil,Nil,Nil,Nil);
			    byte_count_before_2 = 
				    instantaneous_icp_reader_byte_count();
			}
			else
			    byte_count_before_2 = Nil;
			current_icp_read_trace_level = 
				FIXNUM_ADD1(Current_icp_read_trace_level);
			PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
				0);
			  result_of_read = read_icp_unsigned_integer();
			  if (tracep_2)
			      emit_icp_read_trace(Nil,byte_count_before_2,
				      instantaneous_icp_reader_byte_count(),
				      Qcolor_map,string_constant_5,Qvalue,
				      T,result_of_read,Nil,Nil);
			  value = result_of_read;
			POP_SPECIAL();
		    }
		    else
			value = read_icp_unsigned_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(gensym_window);
			resumable_icp_push(Qhandle_icp_set_up_palette);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_set_up_palette;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcolor_map,string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    color_map = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)4L ? T : Nil;
		      if (tracep_1) {
			  emit_icp_read_trace(T,Nil,Nil,Qcolor_map,
				  string_constant_5,Qvalue,Nil,Nil,Nil,Nil);
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
				    Qcolor_map,string_constant_5,Qvalue,T,
				    result_of_read,Nil,Nil);
			value = result_of_read;
		      POP_SPECIAL();
		  }
		  else
		      value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(gensym_window);
		      resumable_icp_push(Qhandle_icp_set_up_palette);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_set_up_palette;
		  }
		  color_map = value;
	      }
	      result_of_read = set_up_palette(gensym_window,color_map);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qset_up_palette,string_constant_3,Qmessage,Nil,
			  result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		gensym_window = resumable_icp_pop();
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
		    emit_icp_read_trace(T,Nil,Nil,Qgensym_window,
			    string_constant_4,Qargument,Nil,Nil,Nil,Nil);
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
			  resumable_icp_push(Qhandle_icp_set_up_palette);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_set_up_palette;
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
			      Qgensym_window,string_constant_4,Qargument,T,
			      result_of_read,Nil,Nil);
		  gensym_window = result_of_read;
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
			resumable_icp_push(Qhandle_icp_set_up_palette);
			result = VALUES_1(Icp_suspend);
			goto end_handle_icp_set_up_palette;
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
		    gensym_window = ISVREF(ISVREF(ISVREF(index_space,
			    (SI_Long)2L),IFIX(index_1) >>  -  - 
			    (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    gensym_window = Nil;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		color_map = resumable_icp_pop();
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
		    emit_icp_read_trace(T,Nil,Nil,Qcolor_map,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			1);
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)4L ? T : Nil;
		      if (tracep_1) {
			  emit_icp_read_trace(T,Nil,Nil,Qcolor_map,
				  string_constant_5,Qvalue,Nil,Nil,Nil,Nil);
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
				    Qcolor_map,string_constant_5,Qvalue,T,
				    result_of_read,Nil,Nil);
			value = result_of_read;
		      POP_SPECIAL();
		  }
		  else
		      value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(gensym_window);
		      resumable_icp_push(Qhandle_icp_set_up_palette);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_set_up_palette;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcolor_map,string_constant_2,Qargument,T,
			      result_of_read,Nil,Nil);
		  color_map = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)4L ? T : Nil;
		    if (tracep) {
			emit_icp_read_trace(T,Nil,Nil,Qcolor_map,
				string_constant_5,Qvalue,Nil,Nil,Nil,Nil);
			byte_count_before = 
				instantaneous_icp_reader_byte_count();
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
				  Qcolor_map,string_constant_5,Qvalue,T,
				  result_of_read,Nil,Nil);
		      value = result_of_read;
		    POP_SPECIAL();
		}
		else
		    value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(gensym_window);
		    resumable_icp_push(Qhandle_icp_set_up_palette);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_set_up_palette;
		}
		color_map = value;
	    }
	    set_up_palette(gensym_window,color_map);
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_set_up_palette:
    return result;
}

/* OBTAIN-MAX-WINDOW-PROTOCOL */
Object obtain_max_window_protocol(gensym_window)
    Object gensym_window;
{
    Object temp, icp_output_port_qm, current_icp_port, current_icp_socket;
    Object disable_resumability, number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol_2, aref_arg_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;
    double gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    double gensymed_symbol_6, gensymed_symbol_7, aref_new_value;
    Declare_special(12);

    x_note_fn_call(55,143);
    gensymed_symbol = IFIX(Latest_icp_window_protocol_version);
    temp = getf(ISVREF(gensym_window,(SI_Long)19L),
	    Qicp_window_protocol_version,_);
    if (temp);
    else
	temp = Original_icp_window_protocol_version;
    gensymed_symbol_1 = IFIX(temp);
    change_icp_window_protocol_version(gensym_window,
	    FIX(MIN(gensymed_symbol,gensymed_symbol_1)));
    if (FIXNUM_LT(Icp_window_protocol_supports_setting_protocol_level,
	    ISVREF(gensym_window,(SI_Long)11L))) {
	icp_output_port_qm = ISVREF(gensym_window,(SI_Long)12L);
	if (icp_output_port_qm && 
		icp_connection_open_p(ISVREF(icp_output_port_qm,
		    (SI_Long)2L))) {
	    current_icp_port = icp_output_port_qm;
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
				    gensymed_symbol_2 = Nil;
				    gensymed_symbol_3 = 0.0;
				    gensymed_symbol_4 = 0.0;
				    if (Profiling_enabled_qm) {
					gensymed_symbol_2 = T;
					gensymed_symbol_3 = 
						DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						(SI_Long)2L),(SI_Long)0L);
					gensymed_symbol_4 = 
						g2ext_unix_time_as_float();
					aref_arg_1 = 
						ISVREF(Profiling_enabled_qm,
						(SI_Long)2L);
					DFLOAT_ISASET_1(aref_arg_1,
						(SI_Long)0L,gensymed_symbol_4);
				    }
				    if (icp_connection_open_p(Current_icp_socket) 
					    &&  
					    !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
						{
					send_icp_set_window_protocol_version(gensym_window,
						ISVREF(gensym_window,
						(SI_Long)11L));
					end_icp_message_group();
				    }
				    if (Profiling_enabled_qm) {
					gensymed_symbol_5 = 
						g2ext_unix_time_as_float();
					gensymed_symbol_6 = 
						DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						(SI_Long)2L),(SI_Long)0L);
					gensymed_symbol_7 = 
						gensymed_symbol_5 - 
						gensymed_symbol_6;
					aref_arg_1 = 
						ISVREF(Profiling_enabled_qm,
						(SI_Long)6L);
					aref_new_value = gensymed_symbol_7 
						+ 
						DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						(SI_Long)6L),(SI_Long)0L);
					DFLOAT_ISASET_1(aref_arg_1,
						(SI_Long)0L,aref_new_value);
					aref_arg_1 = 
						ISVREF(Profiling_enabled_qm,
						(SI_Long)2L);
					aref_new_value = gensymed_symbol_2 
						? gensymed_symbol_3 + 
						gensymed_symbol_7 + 
						(gensymed_symbol_6 - 
						gensymed_symbol_4) : 
						gensymed_symbol_5;
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
    return initialize_image_palette_of_new_gensym_window(gensym_window);
}

static Object Kpaint_infered_from_xor;  /* :paint-infered-from-xor */

/* CHANGE-ICP-WINDOW-PROTOCOL-VERSION */
Object change_icp_window_protocol_version(gensym_window,
	    icp_window_protocol_version)
    Object gensym_window, icp_window_protocol_version;
{
    x_note_fn_call(55,144);
    SVREF(gensym_window,FIX((SI_Long)11L)) = icp_window_protocol_version;
    if (global_paint_mode_p() && 
	    FIXNUM_LT(Icp_window_protocol_supports_transparent_copy,
	    ISVREF(gensym_window,(SI_Long)11L)))
	SVREF(gensym_window,FIX((SI_Long)30L)) = Kpaint_infered_from_xor;
    if ( !TRUEP(slave_gensym_window_qm(gensym_window)))
	initialize_gensym_window_after_connection(gensym_window);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Initialize_gensym_window_after_connection_done, Qinitialize_gensym_window_after_connection_done);

static Object Qxclip;              /* xclip */

/* INITIALIZE-GENSYM-WINDOW-AFTER-CONNECTION */
Object initialize_gensym_window_after_connection(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(55,145);
    if (EQ(ISVREF(gensym_window,(SI_Long)1L),Qx11_window)) {
	if ( !TRUEP(Initialize_gensym_window_after_connection_done)) {
	    g2ext_x11_initialize_after_connection(IFIX(ISVREF(gensym_window,
		    (SI_Long)17L)),IFIX(ISVREF(gensym_window,
		    (SI_Long)11L)),
		    FIXNUM_LT(Icp_window_protocol_supports_unicode_character_events,
		    ISVREF(gensym_window,(SI_Long)11L)) ? (SI_Long)1L : 
		    (SI_Long)0L,getf(Command_line_arguments,Qxclip,_) ? 
		    (SI_Long)1L : (SI_Long)0L);
	    Initialize_gensym_window_after_connection_done = T;
	    return VALUES_1(Initialize_gensym_window_after_connection_done);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qtelewindows_connection_license_level;  /* telewindows-connection-license-level */

static Object Qg2_license_level;   /* g2-license-level */

static Object Qg2_authorized_optional_modules;  /* g2-authorized-optional-modules */

static Object Qent;                /* ent */

static Object Qal;                 /* al */

static Object Qjp;                 /* jp */

static Object Qjl;                 /* jl */

static Object Qg1;                 /* g1 */

static Object Qkorean;             /* korean */

static Object Qnupec;              /* nupec */

static Object Qjapanese;           /* japanese */

static Object Qchinese;            /* chinese */

static Object Qgfi;                /* gfi */

static Object Qgsi;                /* gsi */

/* ESTABLISH-TELEWINDOWS-LICENSE-LEVEL */
Object establish_telewindows_license_level(gensym_window)
    Object gensym_window;
{
    Object license_level_qm, icp_output_port_qm, current_icp_port;
    Object current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, temp_1, gensymed_symbol_3, gensymed_symbol_4;
    Object module_name, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, ab_loop_desetq_, code, info;
    SI_Long gensymed_symbol_5;
    char temp_2;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_6;
    double gensymed_symbol_7, gensymed_symbol_8, aref_new_value;
    Declare_special(12);
    Object result;

    x_note_fn_call(55,146);
    if (FIXNUM_LT(Icp_window_protocol_supports_floating_telewindows,
	    ISVREF(gensym_window,(SI_Long)11L))) {
	license_level_qm = negotiate_telewindows_licensing(gensym_window);
	icp_output_port_qm = ISVREF(gensym_window,(SI_Long)12L);
	if (icp_output_port_qm && 
		icp_connection_open_p(ISVREF(icp_output_port_qm,
		    (SI_Long)2L))) {
	    current_icp_port = icp_output_port_qm;
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
					temp_1 = 
						ISVREF(Profiling_enabled_qm,
						(SI_Long)2L);
					DFLOAT_ISASET_1(temp_1,(SI_Long)0L,
						gensymed_symbol_2);
				    }
				    if (icp_connection_open_p(Current_icp_socket) 
					    &&  
					    !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
						{
					if (FIXNUM_LT(Icp_window_protocol_supports_telewindows_connection_license_info,
						ISVREF(gensym_window,
						(SI_Long)11L))) {
					    gensymed_symbol_3 = 
						    make_gensym_list_1(FIX((SI_Long)6L));
					    gensymed_symbol_4 = 
						    gensymed_symbol_3;
					    M_CAR(gensymed_symbol_4) = 
						    Qtelewindows_connection_license_level;
					    gensymed_symbol_4 = 
						    M_CDR(gensymed_symbol_4);
					    M_CAR(gensymed_symbol_4) = 
						    license_level_qm;
					    gensymed_symbol_4 = 
						    M_CDR(gensymed_symbol_4);
					    M_CAR(gensymed_symbol_4) = 
						    Qg2_license_level;
					    gensymed_symbol_4 = 
						    M_CDR(gensymed_symbol_4);
					    temp_1 = get_g2_license_level();
					    M_CAR(gensymed_symbol_4) = temp_1;
					    gensymed_symbol_4 = 
						    M_CDR(gensymed_symbol_4);
					    M_CAR(gensymed_symbol_4) = 
						    Qg2_authorized_optional_modules;
					    gensymed_symbol_4 = 
						    M_CDR(gensymed_symbol_4);
					    module_name = Nil;
					    ab_loop_list_ = 
						    Optional_modules_map;
					    ab_loopvar_ = Nil;
					    ab_loopvar__1 = Nil;
					    ab_loopvar__2 = Nil;
					    ab_loop_desetq_ = Nil;
					  next_loop:
					    if ( !TRUEP(ab_loop_list_))
						goto end_loop;
					    ab_loop_desetq_ = 
						    M_CAR(ab_loop_list_);
					    module_name = CAR(ab_loop_desetq_);
					    ab_loop_list_ = 
						    M_CDR(ab_loop_list_);
					    if (EQ(module_name,Qent)) {
						code = 
							M_CAR(M_CDR(Radio_button_status_flags_1));
						temp = FIXNUMP(code) && 
							(IFIX(code) & 
							(SI_Long)65536L) 
							!= (SI_Long)0L ? 
							M_CAR(M_CDR(Cache_ent_semantics_graph)) 
							: Nil;
					    }
					    else if (EQ(module_name,Qal)) {
						code = 
							M_CAR(M_CDR(Radio_button_status_flags));
						temp = FIXNUMP(code) && 
							(IFIX(code) & 
							(SI_Long)32768L) 
							!= (SI_Long)0L ? 
							M_CAR(M_CDR(Cache_al_semantics_graph)) 
							: Nil;
					    }
					    else if (EQ(module_name,Qjp)) {
						code = 
							M_CAR(M_CDR(Popup_frames_available));
						temp = FIXNUMP(code) && 
							(IFIX(code) & 
							(SI_Long)16384L) 
							!= (SI_Long)0L ? 
							M_CAR(M_CDR(Cache_jp_semantics_graph)) 
							: Nil;
					    }
					    else if (EQ(module_name,Qjl)) {
						code = 
							M_CAR(M_CDR(Index_of_open_windows));
						temp = FIXNUMP(code) && 
							(IFIX(code) & 
							(SI_Long)8192L) != 
							(SI_Long)0L ? 
							M_CAR(M_CDR(Cache_jl_semantics_graph)) 
							: Nil;
					    }
					    else if (EQ(module_name,Qg1)) {
						code = 
							M_CAR(M_CDR(Edit_type_alias_mapping));
						temp = FIXNUMP(code) ? 
							((IFIX(code) & 
							(SI_Long)4096L) != 
							(SI_Long)0L ? T : 
							Nil) : Qnil;
						if (temp);
						else
						    temp = 
							    M_CAR(M_CDR(Cache_g1_semantics_graph));
					    }
					    else if (EQ(module_name,Qkorean)) {
						code = 
							M_CAR(M_CDR(Get_object_on_kb_workspace_for_item));
						temp = FIXNUMP(code) && 
							(IFIX(code) & 
							(SI_Long)2048L) != 
							(SI_Long)0L ? 
							M_CAR(M_CDR(Cache_korean_semantics_graph)) 
							: Nil;
					    }
					    else if (EQ(module_name,Qnupec)) {
						code = 
							M_CAR(M_CDR(Journal_shutout_scan_p));
						temp = FIXNUMP(code) && 
							(IFIX(code) & 
							(SI_Long)256L) != 
							(SI_Long)0L ? 
							M_CAR(M_CDR(Cache_nupec_semantics_graph)) 
							: Nil;
					    }
					    else if (EQ(module_name,
							Qjapanese)) {
						code = 
							M_CAR(M_CDR(Pop_fonts_stack));
						if (FIXNUMP(code)) {
						    gensymed_symbol_5 = 
							    IFIX(code) & 
							    (SI_Long)128L;
						    temp_2 = 
							    gensymed_symbol_5 
							    != (SI_Long)0L;
						}
						else
						    temp_2 = TRUEP(Nil);
						temp = temp_2 ? 
							M_CAR(M_CDR(Cache_japanese_semantics_graph)) 
							: Nil;
					    }
					    else if (EQ(module_name,
							Qchinese)) {
						code = 
							M_CAR(M_CDR(Reclaim_fonts_stack));
						temp = FIXNUMP(code) && 
							(IFIX(code) & 
							(SI_Long)32L) != 
							(SI_Long)0L ? 
							M_CAR(M_CDR(Cache_chinese_semantics_graph)) 
							: Nil;
					    }
					    else if (EQ(module_name,Qgfi)) {
						code = 
							M_CAR(M_CDR(Gfi_list_of_converters));
						temp = FIXNUMP(code) && 
							(IFIX(code) & 
							(SI_Long)8L) != 
							(SI_Long)0L ? 
							M_CAR(M_CDR(Cache_gfi_semantics_graph)) 
							: Nil;
					    }
					    else if (EQ(module_name,Qicp)) {
						code = 
							M_CAR(M_CDR(Listed_continuation_servers));
						temp = FIXNUMP(code) && 
							(IFIX(code) & 
							(SI_Long)4L) != 
							(SI_Long)0L ? 
							M_CAR(M_CDR(Cache_icp_semantics_graph)) 
							: Nil;
					    }
					    else if (EQ(module_name,Qgsi)) {
						code = 
							M_CAR(M_CDR(Overflow_byte_count));
						temp = FIXNUMP(code) && 
							(IFIX(code) & 
							(SI_Long)1L) != 
							(SI_Long)0L ? 
							M_CAR(M_CDR(Cache_gsi_semantics_graph)) 
							: Nil;
					    }
					    else
						temp = Qnil;
					    if (temp) {
						ab_loopvar__2 = 
							gensym_cons_1(module_name,
							Nil);
						if (ab_loopvar__1)
						    M_CDR(ab_loopvar__1) = 
							    ab_loopvar__2;
						else
						    ab_loopvar_ = 
							    ab_loopvar__2;
						ab_loopvar__1 = ab_loopvar__2;
					    }
					    goto next_loop;
					  end_loop:
					    goto end_1;
					    ab_loopvar_ = Qnil;
					  end_1:;
					    M_CAR(gensymed_symbol_4) = 
						    ab_loopvar_;
					    info = gensymed_symbol_3;
					    send_icp_set_telewindows_connection_license_info(gensym_window,
						    info);
					    temp = reclaim_gensym_tree_1(info);
					}
					else
					    temp = 
						    send_icp_set_window_license_level(gensym_window,
						    license_level_qm);
					end_icp_message_group();
				    }
				    else
					temp = Nil;
				    if (Profiling_enabled_qm) {
					gensymed_symbol_6 = 
						g2ext_unix_time_as_float();
					gensymed_symbol_7 = 
						DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						(SI_Long)2L),(SI_Long)0L);
					gensymed_symbol_8 = 
						gensymed_symbol_6 - 
						gensymed_symbol_7;
					temp_1 = 
						ISVREF(Profiling_enabled_qm,
						(SI_Long)6L);
					aref_new_value = gensymed_symbol_8 
						+ 
						DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						(SI_Long)6L),(SI_Long)0L);
					DFLOAT_ISASET_1(temp_1,(SI_Long)0L,
						aref_new_value);
					temp_1 = 
						ISVREF(Profiling_enabled_qm,
						(SI_Long)2L);
					aref_new_value = gensymed_symbol ? 
						gensymed_symbol_1 + 
						gensymed_symbol_8 + 
						(gensymed_symbol_7 - 
						gensymed_symbol_2) : 
						gensymed_symbol_6;
					DFLOAT_ISASET_1(temp_1,(SI_Long)0L,
						aref_new_value);
				    }
				    result = VALUES_1(temp);
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
	    return result;
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Scratchpad_raster, Qscratchpad_raster);

DEFINE_VARIABLE_WITH_SYMBOL(Current_scratchpad_raster_type, Qcurrent_scratchpad_raster_type);

DEFINE_VARIABLE_WITH_SYMBOL(Current_scratchpad_raster, Qcurrent_scratchpad_raster);

DEFINE_VARIABLE_WITH_SYMBOL(Current_scratchpad_raster_width, Qcurrent_scratchpad_raster_width);

DEFINE_VARIABLE_WITH_SYMBOL(Current_scratchpad_raster_height, Qcurrent_scratchpad_raster_height);

DEFINE_VARIABLE_WITH_SYMBOL(Current_scratchpad_raster_depth, Qcurrent_scratchpad_raster_depth);

DEFINE_VARIABLE_WITH_SYMBOL(Current_scratchpad_raster_tiled_p, Qcurrent_scratchpad_raster_tiled_p);

DEFINE_VARIABLE_WITH_SYMBOL(Current_x_offset_for_stored_raster_qm, Qcurrent_x_offset_for_stored_raster_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Current_y_offset_for_stored_raster_qm, Qcurrent_y_offset_for_stored_raster_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Current_x_max_for_stored_raster_qm, Qcurrent_x_max_for_stored_raster_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Current_y_max_for_stored_raster_qm, Qcurrent_y_max_for_stored_raster_qm);

static Object string_constant_6;   /* "~%Unable to allocate a ~dx~d pixmap! Will retry ....~%" */

static Object string_constant_7;   /* "~%Still unable to allocate a ~dx~d pixmap! Will try larger size ....~%" */

/* ALLOCATE-SCRATCHPAD-RASTER */
Object allocate_scratchpad_raster(gensym_window,minimum_width,
	    minimum_height,callback_function_to_gc_if_allocation_failure)
    Object gensym_window, minimum_width, minimum_height;
    Object callback_function_to_gc_if_allocation_failure;
{
    Object do_not_error_in_x11_create_pixmap_on_failed_allocation, raster;
    Object temp;
    Declare_special(1);

    x_note_fn_call(55,147);
    do_not_error_in_x11_create_pixmap_on_failed_allocation = T;
    PUSH_SPECIAL_WITH_SYMBOL(Do_not_error_in_x11_create_pixmap_on_failed_allocation,Qdo_not_error_in_x11_create_pixmap_on_failed_allocation,do_not_error_in_x11_create_pixmap_on_failed_allocation,
	    0);
      raster = allocate_stored_raster_1(gensym_window,minimum_width,
	      minimum_height,FIX((SI_Long)1L),Nil);
      if (IFIX(raster) < (SI_Long)0L) {
	  notify_user_at_console(3,string_constant_6,minimum_width,
		  minimum_height);
	  FUNCALL_0(callback_function_to_gc_if_allocation_failure);
	  hard_reclaim_all_reclaimed_stored_rasters(gensym_window);
	  raster = allocate_stored_raster_1(gensym_window,minimum_width,
		  minimum_height,FIX((SI_Long)1L),Nil);
	  if (IFIX(raster) < (SI_Long)0L) {
	      notify_user_at_console(3,string_constant_7,minimum_width,
		      minimum_height);
	      raster = allocate_bigger_stored_raster(gensym_window,
		      minimum_width,minimum_height,FIX((SI_Long)1L));
	      if (IFIX(raster) < (SI_Long)0L)
		  handle_no_solution_to_raster_allocation_failure(gensym_window,
			  minimum_width,minimum_height);
	  }
      }
      temp = raster;
    POP_SPECIAL();
    return VALUES_1(temp);
}

static Object Qinitialize_scratchpad_raster;  /* initialize-scratchpad-raster */

static Object Qminimum_width;      /* minimum-width */

static Object Qminimum_height;     /* minimum-height */

static Object Qbits_per_pixel;     /* bits-per-pixel */

static Object Qmake_exact_size_p;  /* make-exact-size-p */

/* INITIALIZE-SCRATCHPAD-RASTER */
Object initialize_scratchpad_raster(gensym_window,minimum_width,
	    minimum_height,bits_per_pixel,make_exact_size_p)
    Object gensym_window, minimum_width, minimum_height, bits_per_pixel;
    Object make_exact_size_p;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, resumable_icp_state_1;
    Object icp_suspend_1, top, key, value, value_1;
    Declare_special(3);
    Object result;

    x_note_fn_call(55,148);
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
	      SVREF(temp,svref_arg_2) = Qinitialize_scratchpad_raster;
	  }
	  if (EQ(Current_scratchpad_raster_type,Qicp)) {
	      icp_message_functions_icp_prologue(Qinitialize_scratchpad_raster);
	      temp_1 = getfq_function_no_default(ISVREF(gensym_window,
		      (SI_Long)14L),Current_icp_port);
	      if (temp_1);
	      else
		  temp_1 = make_corresponding_icp_gensym_window(gensym_window);
	      gensym_window = temp_1;
	      start_writing_icp_message(FIX((SI_Long)31L));
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)2L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qinitialize_scratchpad_raster,
			      string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  1);
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,Qgensym_window,
				    string_constant_4,Qargument,Nil,Nil,
				    Nil,Nil);
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
				  write_icp_corresponding_object_index(gensym_window);
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qgensym_window,string_constant_4,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else
			write_icp_corresponding_object_index(gensym_window);
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,Qminimum_width,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
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
				  write_icp_unsigned_integer(minimum_width);
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qminimum_width,string_constant_2,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else
			write_icp_unsigned_integer(minimum_width);
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,Qminimum_height,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
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
				  write_icp_unsigned_integer(minimum_height);
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qminimum_height,string_constant_2,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else
			write_icp_unsigned_integer(minimum_height);
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,Qbits_per_pixel,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
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
				  write_icp_unsigned_integer(bits_per_pixel);
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qbits_per_pixel,string_constant_2,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else
			write_icp_unsigned_integer(bits_per_pixel);
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qmake_exact_size_p,string_constant_2,
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
				  write_icp_boolean(make_exact_size_p);
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qmake_exact_size_p,string_constant_2,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else
			result_of_write = write_icp_boolean(make_exact_size_p);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qinitialize_scratchpad_raster,
				string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else {
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qgensym_window,
				  string_constant_4,Qargument,Nil,Nil,Nil,Nil);
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
				write_icp_corresponding_object_index(gensym_window);
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qgensym_window,string_constant_4,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else
		      write_icp_corresponding_object_index(gensym_window);
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qminimum_width,
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
				write_icp_unsigned_integer(minimum_width);
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qminimum_width,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else
		      write_icp_unsigned_integer(minimum_width);
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qminimum_height,
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
				write_icp_unsigned_integer(minimum_height);
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qminimum_height,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else
		      write_icp_unsigned_integer(minimum_height);
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qbits_per_pixel,
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
				write_icp_unsigned_integer(bits_per_pixel);
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qbits_per_pixel,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else
		      write_icp_unsigned_integer(bits_per_pixel);
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,
				  Qmake_exact_size_p,string_constant_2,
				  Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			result_of_write = write_icp_boolean(make_exact_size_p);
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qmake_exact_size_p,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else
		      write_icp_boolean(make_exact_size_p);
	      }
	  }
	  else if (EQ(Current_scratchpad_raster_type,Qprinter)) {
	      temp_1 = aref1(Icp_printing_message_handler_array,
		      FIX((SI_Long)31L));
	      FUNCALL_5(temp_1,gensym_window,minimum_width,minimum_height,
		      bits_per_pixel,make_exact_size_p);
	  }
	  else
	      Current_scratchpad_raster = 
		      allocate_stored_raster(gensym_window,minimum_width,
		      minimum_height,bits_per_pixel,make_exact_size_p);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qinitialize_scratchpad_raster,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qinitialize_scratchpad_raster,top,Nil);
		goto end_initialize_scratchpad_raster;
	    }
	}
	gensym_window = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : gensym_window;
	minimum_width = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : minimum_width;
	minimum_height = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : minimum_height;
	bits_per_pixel = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : bits_per_pixel;
	make_exact_size_p = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : make_exact_size_p;
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
	      SVREF(temp,svref_arg_2) = Qinitialize_scratchpad_raster;
	  }
	  key = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		  resumable_icp_pop() : Current_scratchpad_raster_type;
	  if (EQ(key,Qicp)) {
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
	      icp_message_functions_icp_prologue(Qinitialize_scratchpad_raster);
	    l1:
	      value = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
		       TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : 
		      getfq_function_no_default(ISVREF(gensym_window,
		      (SI_Long)14L),Current_icp_port);
	      if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) && value)
		  gensym_window = value;
	      else {
		  value_1 = 
			  make_corresponding_icp_gensym_window(gensym_window);
		  if (EQ(icp_suspend_1,value_1)) {
		      resumable_icp_push(value);
		      resumable_icp_push(FIX((SI_Long)1L));
		      temp_1 = Icp_suspend;
		      goto end_block;
		  }
		  gensym_window = value_1;
	      }
	    l2:
	      if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)31L)))) {
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
			      Qinitialize_scratchpad_raster,
			      string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  1);
		    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
			    : TRUEP(Nil)) {
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
				goto l3_1;
				break;
			      case 4:
				goto l4;
				break;
			      case 5:
				goto l5;
				break;
			      default:
				break;
			    }
		    }
		  l1_1:
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,Qgensym_window,
				    string_constant_4,Qargument,Nil,Nil,
				    Nil,Nil);
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
				  write_icp_corresponding_object_index(gensym_window))) 
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
				      Qgensym_window,string_constant_4,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else if (EQ(icp_suspend_1,
			    write_icp_corresponding_object_index(gensym_window))) 
				{
			resumable_icp_push(FIX((SI_Long)1L));
			temp_1 = Icp_suspend;
			goto end_block_1;
		    }
		  l2_1:
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,Qminimum_width,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
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
				  write_icp_unsigned_integer(minimum_width))) {
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
				      Qminimum_width,string_constant_2,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else if (EQ(icp_suspend_1,
			    write_icp_unsigned_integer(minimum_width))) {
			resumable_icp_push(FIX((SI_Long)2L));
			temp_1 = Icp_suspend;
			goto end_block_1;
		    }
		  l3_1:
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,Qminimum_height,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
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
				  write_icp_unsigned_integer(minimum_height))) 
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
				      Qminimum_height,string_constant_2,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else if (EQ(icp_suspend_1,
			    write_icp_unsigned_integer(minimum_height))) {
			resumable_icp_push(FIX((SI_Long)3L));
			temp_1 = Icp_suspend;
			goto end_block_1;
		    }
		  l4:
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,Qbits_per_pixel,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
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
				  write_icp_unsigned_integer(bits_per_pixel))) 
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
				      Qbits_per_pixel,string_constant_2,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else if (EQ(icp_suspend_1,
			    write_icp_unsigned_integer(bits_per_pixel))) {
			resumable_icp_push(FIX((SI_Long)4L));
			temp_1 = Icp_suspend;
			goto end_block_1;
		    }
		  l5:
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qmake_exact_size_p,string_constant_2,
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
				  write_icp_boolean(make_exact_size_p))) {
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
				      Qmake_exact_size_p,string_constant_2,
				      Qargument,Nil,Nil,Nil,Nil);
			  temp_1 = result_of_write;
			POP_SPECIAL();
		    }
		    else if (EQ(icp_suspend_1,
			    write_icp_boolean(make_exact_size_p))) {
			resumable_icp_push(FIX((SI_Long)5L));
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
				Qinitialize_scratchpad_raster,
				string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else {
		  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			  TRUEP(Nil)) {
		      temp_1 = resumable_icp_pop();
		      if (! !(FIXNUMP(temp_1) && 
			      FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			      FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			  switch (INTEGER_TO_CHAR(temp_1)) {
			    case 1:
			      goto l1_2;
			      break;
			    case 2:
			      goto l2_2;
			      break;
			    case 3:
			      goto l3_2;
			      break;
			    case 4:
			      goto l4_1;
			      break;
			    case 5:
			      goto l5_1;
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
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qgensym_window,
				  string_constant_4,Qargument,Nil,Nil,Nil,Nil);
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
				write_icp_corresponding_object_index(gensym_window))) 
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
				    Qgensym_window,string_constant_4,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else if (EQ(icp_suspend_1,
			  write_icp_corresponding_object_index(gensym_window))) 
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
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qminimum_width,
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
				write_icp_unsigned_integer(minimum_width))) {
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
				    Qminimum_width,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else if (EQ(icp_suspend_1,
			  write_icp_unsigned_integer(minimum_width))) {
		      resumable_icp_push(FIX((SI_Long)2L));
		      temp_1 = Icp_suspend;
		      goto end_block_2;
		  }
		l3_2:
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qminimum_height,
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
				write_icp_unsigned_integer(minimum_height))) {
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
				    Qminimum_height,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else if (EQ(icp_suspend_1,
			  write_icp_unsigned_integer(minimum_height))) {
		      resumable_icp_push(FIX((SI_Long)3L));
		      temp_1 = Icp_suspend;
		      goto end_block_2;
		  }
		l4_1:
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qbits_per_pixel,
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
				write_icp_unsigned_integer(bits_per_pixel))) {
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
				    Qbits_per_pixel,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else if (EQ(icp_suspend_1,
			  write_icp_unsigned_integer(bits_per_pixel))) {
		      resumable_icp_push(FIX((SI_Long)4L));
		      temp_1 = Icp_suspend;
		      goto end_block_2;
		  }
		l5_1:
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,
				  Qmake_exact_size_p,string_constant_2,
				  Qargument,Nil,Nil,Nil,Nil);
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
				write_icp_boolean(make_exact_size_p))) {
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
				    Qmake_exact_size_p,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
			temp_1 = result_of_write;
		      POP_SPECIAL();
		  }
		  else if (EQ(icp_suspend_1,
			  write_icp_boolean(make_exact_size_p))) {
		      resumable_icp_push(FIX((SI_Long)5L));
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
		  resumable_icp_push(key);
		  resumable_icp_push(make_exact_size_p);
		  resumable_icp_push(bits_per_pixel);
		  resumable_icp_push(minimum_height);
		  resumable_icp_push(minimum_width);
		  resumable_icp_push(gensym_window);
		  resumable_icp_push(Qinitialize_scratchpad_raster);
		  result = VALUES_1(Icp_suspend);
		  POP_SPECIAL();
		  goto end_initialize_scratchpad_raster;
	      }
	  }
	  else if (EQ(key,Qprinter)) {
	      temp_1 = aref1(Icp_printing_message_handler_array,
		      FIX((SI_Long)31L));
	      FUNCALL_5(temp_1,gensym_window,minimum_width,minimum_height,
		      bits_per_pixel,make_exact_size_p);
	  }
	  else
	      Current_scratchpad_raster = 
		      allocate_stored_raster(gensym_window,minimum_width,
		      minimum_height,bits_per_pixel,make_exact_size_p);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_initialize_scratchpad_raster:
    return result;
}

static Object Qhandle_icp_initialize_scratchpad_raster;  /* handle-icp-initialize-scratchpad-raster */

/* HANDLE-ICP-INITIALIZE-SCRATCHPAD-RASTER */
Object handle_icp_initialize_scratchpad_raster()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, index_1, index_space, result_of_read;
    Object gensym_window, minimum_width, minimum_height, bits_per_pixel;
    Object make_exact_size_p, temp, resumable_icp_state_1, icp_suspend_1, top;
    Object value;
    Declare_special(2);
    Object result;

    x_note_fn_call(55,149);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qinitialize_scratchpad_raster,string_constant_3,
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
		      emit_icp_read_trace(T,Nil,Nil,Qgensym_window,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
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
				Qgensym_window,string_constant_4,Qargument,
				T,result_of_read,Nil,Nil);
		    gensym_window = result_of_read;
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
		      gensym_window = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      gensym_window = Nil;
	      }
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
		      emit_icp_read_trace(T,Nil,Nil,Qminimum_width,
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
				Qminimum_width,string_constant_2,Qargument,
				T,result_of_read,Nil,Nil);
		    minimum_width = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  minimum_width = read_icp_unsigned_integer();
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
		      emit_icp_read_trace(T,Nil,Nil,Qminimum_height,
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
				Qminimum_height,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    minimum_height = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  minimum_height = read_icp_unsigned_integer();
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
		      emit_icp_read_trace(T,Nil,Nil,Qbits_per_pixel,
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
				Qbits_per_pixel,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    bits_per_pixel = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  bits_per_pixel = read_icp_unsigned_integer();
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
		      emit_icp_read_trace(T,Nil,Nil,Qmake_exact_size_p,
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
		    result_of_read = read_icp_boolean();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qmake_exact_size_p,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    make_exact_size_p = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  make_exact_size_p = read_icp_boolean();
	      result_of_read = initialize_scratchpad_raster(gensym_window,
		      minimum_width,minimum_height,bits_per_pixel,
		      make_exact_size_p);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qinitialize_scratchpad_raster,string_constant_3,
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
		    emit_icp_read_trace(T,Nil,Nil,Qgensym_window,
			    string_constant_4,Qargument,Nil,Nil,Nil,Nil);
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
			      Qgensym_window,string_constant_4,Qargument,T,
			      result_of_read,Nil,Nil);
		  gensym_window = result_of_read;
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
		    gensym_window = ISVREF(ISVREF(ISVREF(index_space,
			    (SI_Long)2L),IFIX(index_1) >>  -  - 
			    (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    gensym_window = Nil;
	    }
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
		    emit_icp_read_trace(T,Nil,Nil,Qminimum_width,
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
			      Qminimum_width,string_constant_2,Qargument,T,
			      result_of_read,Nil,Nil);
		  minimum_width = result_of_read;
		POP_SPECIAL();
	    }
	    else
		minimum_width = read_icp_unsigned_integer();
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
		    emit_icp_read_trace(T,Nil,Nil,Qminimum_height,
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
			      Qminimum_height,string_constant_2,Qargument,
			      T,result_of_read,Nil,Nil);
		  minimum_height = result_of_read;
		POP_SPECIAL();
	    }
	    else
		minimum_height = read_icp_unsigned_integer();
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
		    emit_icp_read_trace(T,Nil,Nil,Qbits_per_pixel,
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
			      Qbits_per_pixel,string_constant_2,Qargument,
			      T,result_of_read,Nil,Nil);
		  bits_per_pixel = result_of_read;
		POP_SPECIAL();
	    }
	    else
		bits_per_pixel = read_icp_unsigned_integer();
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
		    emit_icp_read_trace(T,Nil,Nil,Qmake_exact_size_p,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_boolean();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qmake_exact_size_p,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  make_exact_size_p = result_of_read;
		POP_SPECIAL();
	    }
	    else
		make_exact_size_p = read_icp_boolean();
	    initialize_scratchpad_raster(gensym_window,minimum_width,
		    minimum_height,bits_per_pixel,make_exact_size_p);
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_initialize_scratchpad_raster,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qhandle_icp_initialize_scratchpad_raster,top,Nil);
		goto end_handle_icp_initialize_scratchpad_raster;
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
			Qinitialize_scratchpad_raster,string_constant_3,
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
		  gensym_window = resumable_icp_pop();
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
		      emit_icp_read_trace(T,Nil,Nil,Qgensym_window,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
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
			    resumable_icp_push(Qhandle_icp_initialize_scratchpad_raster);
			    result = VALUES_1(Icp_suspend);
			    POP_SPECIAL();
			    POP_SPECIAL();
			    goto end_handle_icp_initialize_scratchpad_raster;
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
				Qgensym_window,string_constant_4,Qargument,
				T,result_of_read,Nil,Nil);
		    gensym_window = result_of_read;
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
			  resumable_icp_push(Qhandle_icp_initialize_scratchpad_raster);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_initialize_scratchpad_raster;
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
		      gensym_window = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      gensym_window = Nil;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  minimum_width = resumable_icp_pop();
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
		      emit_icp_read_trace(T,Nil,Nil,Qminimum_width,
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
			resumable_icp_push(gensym_window);
			resumable_icp_push(Qhandle_icp_initialize_scratchpad_raster);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_initialize_scratchpad_raster;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qminimum_width,string_constant_2,Qargument,
				T,result_of_read,Nil,Nil);
		    minimum_width = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(gensym_window);
		      resumable_icp_push(Qhandle_icp_initialize_scratchpad_raster);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_initialize_scratchpad_raster;
		  }
		  minimum_width = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  minimum_height = resumable_icp_pop();
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
		      emit_icp_read_trace(T,Nil,Nil,Qminimum_height,
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
			resumable_icp_push(minimum_width);
			resumable_icp_push(gensym_window);
			resumable_icp_push(Qhandle_icp_initialize_scratchpad_raster);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_initialize_scratchpad_raster;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qminimum_height,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    minimum_height = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(minimum_width);
		      resumable_icp_push(gensym_window);
		      resumable_icp_push(Qhandle_icp_initialize_scratchpad_raster);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_initialize_scratchpad_raster;
		  }
		  minimum_height = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  bits_per_pixel = resumable_icp_pop();
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
		      emit_icp_read_trace(T,Nil,Nil,Qbits_per_pixel,
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
			resumable_icp_push(minimum_height);
			resumable_icp_push(minimum_width);
			resumable_icp_push(gensym_window);
			resumable_icp_push(Qhandle_icp_initialize_scratchpad_raster);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_initialize_scratchpad_raster;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qbits_per_pixel,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    bits_per_pixel = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(minimum_height);
		      resumable_icp_push(minimum_width);
		      resumable_icp_push(gensym_window);
		      resumable_icp_push(Qhandle_icp_initialize_scratchpad_raster);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_initialize_scratchpad_raster;
		  }
		  bits_per_pixel = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  make_exact_size_p = resumable_icp_pop();
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
		      emit_icp_read_trace(T,Nil,Nil,Qmake_exact_size_p,
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
		    value = read_icp_boolean();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(bits_per_pixel);
			resumable_icp_push(minimum_height);
			resumable_icp_push(minimum_width);
			resumable_icp_push(gensym_window);
			resumable_icp_push(Qhandle_icp_initialize_scratchpad_raster);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_initialize_scratchpad_raster;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qmake_exact_size_p,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    make_exact_size_p = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_boolean();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(bits_per_pixel);
		      resumable_icp_push(minimum_height);
		      resumable_icp_push(minimum_width);
		      resumable_icp_push(gensym_window);
		      resumable_icp_push(Qhandle_icp_initialize_scratchpad_raster);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_initialize_scratchpad_raster;
		  }
		  make_exact_size_p = value;
	      }
	      result_of_read = initialize_scratchpad_raster(gensym_window,
		      minimum_width,minimum_height,bits_per_pixel,
		      make_exact_size_p);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qinitialize_scratchpad_raster,string_constant_3,
			  Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		gensym_window = resumable_icp_pop();
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
		    emit_icp_read_trace(T,Nil,Nil,Qgensym_window,
			    string_constant_4,Qargument,Nil,Nil,Nil,Nil);
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
			  resumable_icp_push(Qhandle_icp_initialize_scratchpad_raster);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_initialize_scratchpad_raster;
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
			      Qgensym_window,string_constant_4,Qargument,T,
			      result_of_read,Nil,Nil);
		  gensym_window = result_of_read;
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
			resumable_icp_push(Qhandle_icp_initialize_scratchpad_raster);
			result = VALUES_1(Icp_suspend);
			goto end_handle_icp_initialize_scratchpad_raster;
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
		    gensym_window = ISVREF(ISVREF(ISVREF(index_space,
			    (SI_Long)2L),IFIX(index_1) >>  -  - 
			    (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    gensym_window = Nil;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		minimum_width = resumable_icp_pop();
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
		    emit_icp_read_trace(T,Nil,Nil,Qminimum_width,
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
		      resumable_icp_push(gensym_window);
		      resumable_icp_push(Qhandle_icp_initialize_scratchpad_raster);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_initialize_scratchpad_raster;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qminimum_width,string_constant_2,Qargument,T,
			      result_of_read,Nil,Nil);
		  minimum_width = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(gensym_window);
		    resumable_icp_push(Qhandle_icp_initialize_scratchpad_raster);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_initialize_scratchpad_raster;
		}
		minimum_width = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		minimum_height = resumable_icp_pop();
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
		    emit_icp_read_trace(T,Nil,Nil,Qminimum_height,
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
		      resumable_icp_push(minimum_width);
		      resumable_icp_push(gensym_window);
		      resumable_icp_push(Qhandle_icp_initialize_scratchpad_raster);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_initialize_scratchpad_raster;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qminimum_height,string_constant_2,Qargument,
			      T,result_of_read,Nil,Nil);
		  minimum_height = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(minimum_width);
		    resumable_icp_push(gensym_window);
		    resumable_icp_push(Qhandle_icp_initialize_scratchpad_raster);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_initialize_scratchpad_raster;
		}
		minimum_height = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		bits_per_pixel = resumable_icp_pop();
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
		    emit_icp_read_trace(T,Nil,Nil,Qbits_per_pixel,
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
		      resumable_icp_push(minimum_height);
		      resumable_icp_push(minimum_width);
		      resumable_icp_push(gensym_window);
		      resumable_icp_push(Qhandle_icp_initialize_scratchpad_raster);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_initialize_scratchpad_raster;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qbits_per_pixel,string_constant_2,Qargument,
			      T,result_of_read,Nil,Nil);
		  bits_per_pixel = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(minimum_height);
		    resumable_icp_push(minimum_width);
		    resumable_icp_push(gensym_window);
		    resumable_icp_push(Qhandle_icp_initialize_scratchpad_raster);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_initialize_scratchpad_raster;
		}
		bits_per_pixel = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		make_exact_size_p = resumable_icp_pop();
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
		    emit_icp_read_trace(T,Nil,Nil,Qmake_exact_size_p,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_boolean();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(bits_per_pixel);
		      resumable_icp_push(minimum_height);
		      resumable_icp_push(minimum_width);
		      resumable_icp_push(gensym_window);
		      resumable_icp_push(Qhandle_icp_initialize_scratchpad_raster);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_initialize_scratchpad_raster;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qmake_exact_size_p,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  make_exact_size_p = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_boolean();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(bits_per_pixel);
		    resumable_icp_push(minimum_height);
		    resumable_icp_push(minimum_width);
		    resumable_icp_push(gensym_window);
		    resumable_icp_push(Qhandle_icp_initialize_scratchpad_raster);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_initialize_scratchpad_raster;
		}
		make_exact_size_p = value;
	    }
	    initialize_scratchpad_raster(gensym_window,minimum_width,
		    minimum_height,bits_per_pixel,make_exact_size_p);
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_initialize_scratchpad_raster:
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(On_monochrome_raster_list_p, Qon_monochrome_raster_list_p);

DEFINE_VARIABLE_WITH_SYMBOL(Paint_only_target_monochrome_raster_p, Qpaint_only_target_monochrome_raster_p);

/* CONVERT-CURRENT-SCRATCHPAD-RASTER-TO-STORED-RASTER */
Object convert_current_scratchpad_raster_to_stored_raster(gensym_window,
	    minimum_width,minimum_height,bits_per_pixel,make_exact_size_p)
    Object gensym_window, minimum_width, minimum_height, bits_per_pixel;
    Object make_exact_size_p;
{
    Object scratchpad_raster_containing_region, stored_raster_width;
    Object stored_raster_height, x_offset, y_offset;
    Object current_scratchpad_raster_type, current_scratchpad_raster_tiled_p;
    Object current_scratchpad_raster_width, current_scratchpad_raster_height;
    Object current_scratchpad_raster_depth, on_monochrome_raster_list_p;
    Object current_x_offset_for_stored_raster_qm;
    Object current_y_offset_for_stored_raster_qm;
    Object current_x_max_for_stored_raster_qm;
    Object current_y_max_for_stored_raster_qm, current_scratchpad_raster, temp;
    Object new_stored_raster;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(11);
    Object result;

    x_note_fn_call(55,150);
    SAVE_STACK();
    if (T) {
	if ( !TRUEP(Current_scratchpad_raster_tiled_p) && 
		Current_x_offset_for_stored_raster_qm) {
	    scratchpad_raster_containing_region = Current_scratchpad_raster;
	    stored_raster_width = 
		    FIXNUM_MINUS(Current_x_max_for_stored_raster_qm,
		    Current_x_offset_for_stored_raster_qm);
	    stored_raster_height = 
		    FIXNUM_MINUS(Current_y_max_for_stored_raster_qm,
		    Current_y_offset_for_stored_raster_qm);
	    x_offset = Current_x_offset_for_stored_raster_qm;
	    y_offset = Current_y_offset_for_stored_raster_qm;
	    LOCK(Scratchpad_raster);
	    if (PUSH_UNWIND_PROTECT(0)) {
		current_scratchpad_raster_type = ISVREF(gensym_window,
			(SI_Long)23L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
			10);
		  current_scratchpad_raster_tiled_p = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_tiled_p,Qcurrent_scratchpad_raster_tiled_p,current_scratchpad_raster_tiled_p,
			  9);
		    current_scratchpad_raster_width = stored_raster_width;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_width,Qcurrent_scratchpad_raster_width,current_scratchpad_raster_width,
			    8);
		      current_scratchpad_raster_height = stored_raster_height;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_height,Qcurrent_scratchpad_raster_height,current_scratchpad_raster_height,
			      7);
			current_scratchpad_raster_depth = FIX((SI_Long)1L);
			PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_depth,Qcurrent_scratchpad_raster_depth,current_scratchpad_raster_depth,
				6);
			  on_monochrome_raster_list_p = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(On_monochrome_raster_list_p,Qon_monochrome_raster_list_p,on_monochrome_raster_list_p,
				  5);
			    current_x_offset_for_stored_raster_qm = Nil;
			    PUSH_SPECIAL_WITH_SYMBOL(Current_x_offset_for_stored_raster_qm,Qcurrent_x_offset_for_stored_raster_qm,current_x_offset_for_stored_raster_qm,
				    4);
			      current_y_offset_for_stored_raster_qm = Nil;
			      PUSH_SPECIAL_WITH_SYMBOL(Current_y_offset_for_stored_raster_qm,Qcurrent_y_offset_for_stored_raster_qm,current_y_offset_for_stored_raster_qm,
				      3);
				current_x_max_for_stored_raster_qm = Nil;
				PUSH_SPECIAL_WITH_SYMBOL(Current_x_max_for_stored_raster_qm,Qcurrent_x_max_for_stored_raster_qm,current_x_max_for_stored_raster_qm,
					2);
				  current_y_max_for_stored_raster_qm = Nil;
				  PUSH_SPECIAL_WITH_SYMBOL(Current_y_max_for_stored_raster_qm,Qcurrent_y_max_for_stored_raster_qm,current_y_max_for_stored_raster_qm,
					  1);
				    current_scratchpad_raster = Nil;
				    PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster,Qcurrent_scratchpad_raster,current_scratchpad_raster,
					    0);
				      initialize_scratchpad_raster(gensym_window,
					      stored_raster_width,
					      stored_raster_height,
					      FIX((SI_Long)1L),Nil);
				      transfer_region_to_smaller_raster(FIX((SI_Long)0L),
					      FIX((SI_Long)0L),
					      stored_raster_width,
					      stored_raster_height,
					      scratchpad_raster_containing_region,
					      x_offset,y_offset,
					      FIX((SI_Long)1L));
				      temp = 
					      convert_current_scratchpad_raster_to_stored_raster(gensym_window,
					      stored_raster_width,
					      stored_raster_height,
					      FIX((SI_Long)1L),Nil);
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
		SAVE_VALUES(VALUES_1(temp));
	    }
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Scratchpad_raster);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	    new_stored_raster = result;
	    reclaim_stored_raster(scratchpad_raster_containing_region,
		    gensym_window,minimum_width,minimum_height,
		    bits_per_pixel,make_exact_size_p);
	    RESTORE_STACK();
	    return VALUES_1(new_stored_raster);
	}
	else {
	    RESTORE_STACK();
	    return VALUES_1(Current_scratchpad_raster);
	}
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_scratchpad_raster_list, Qcurrent_scratchpad_raster_list);

DEFINE_VARIABLE_WITH_SYMBOL(Current_scratchpad_color_value_list, Qcurrent_scratchpad_color_value_list);

Object The_type_description_of_tiled_raster = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_tiled_rasters, Qchain_of_available_tiled_rasters);

DEFINE_VARIABLE_WITH_SYMBOL(Tiled_raster_count, Qtiled_raster_count);

Object Chain_of_available_tiled_rasters_vector = UNBOUND;

/* TILED-RASTER-STRUCTURE-MEMORY-USAGE */
Object tiled_raster_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(55,151);
    temp = Tiled_raster_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-TILED-RASTER-COUNT */
Object outstanding_tiled_raster_count()
{
    Object def_structure_tiled_raster_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(55,152);
    gensymed_symbol = IFIX(Tiled_raster_count);
    def_structure_tiled_raster_variable = Chain_of_available_tiled_rasters;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_tiled_raster_variable))
	goto end_loop;
    def_structure_tiled_raster_variable = 
	    ISVREF(def_structure_tiled_raster_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-TILED-RASTER-INTERNAL-1 */
Object reclaim_tiled_raster_internal_1(tiled_raster)
    Object tiled_raster;
{
    Object temp, svref_arg_2;

    x_note_fn_call(55,153);
    inline_note_reclaim_cons(tiled_raster,Nil);
    temp = ISVREF(Chain_of_available_tiled_rasters_vector,
	    IFIX(Current_thread_index));
    SVREF(tiled_raster,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_tiled_rasters_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = tiled_raster;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-TILED-RASTER */
Object reclaim_structure_for_tiled_raster(tiled_raster)
    Object tiled_raster;
{
    x_note_fn_call(55,154);
    return reclaim_tiled_raster_internal_1(tiled_raster);
}

static Object Qg2_defstruct_structure_name_tiled_raster_g2_struct;  /* g2-defstruct-structure-name::tiled-raster-g2-struct */

/* MAKE-PERMANENT-TILED-RASTER-STRUCTURE-INTERNAL */
Object make_permanent_tiled_raster_structure_internal()
{
    Object def_structure_tiled_raster_variable;
    Object defstruct_g2_tiled_raster_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(55,155);
    def_structure_tiled_raster_variable = Nil;
    atomic_incff_symval(Qtiled_raster_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_tiled_raster_variable = Nil;
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
	defstruct_g2_tiled_raster_variable = the_array;
	SVREF(defstruct_g2_tiled_raster_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_tiled_raster_g2_struct;
	def_structure_tiled_raster_variable = 
		defstruct_g2_tiled_raster_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_tiled_raster_variable);
}

/* MAKE-TILED-RASTER-1 */
Object make_tiled_raster_1()
{
    Object def_structure_tiled_raster_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(55,156);
    def_structure_tiled_raster_variable = 
	    ISVREF(Chain_of_available_tiled_rasters_vector,
	    IFIX(Current_thread_index));
    if (def_structure_tiled_raster_variable) {
	svref_arg_1 = Chain_of_available_tiled_rasters_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_tiled_raster_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_tiled_raster_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_tiled_raster_g2_struct;
    }
    else
	def_structure_tiled_raster_variable = 
		make_permanent_tiled_raster_structure_internal();
    inline_note_allocate_cons(def_structure_tiled_raster_variable,Nil);
    SVREF(def_structure_tiled_raster_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_tiled_raster_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_tiled_raster_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_tiled_raster_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_tiled_raster_variable,FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_tiled_raster_variable);
}

static Object Qx11_pixmap;         /* x11-pixmap */

static Object string_constant_8;   /* "~%Unable to allocate a ~dx~d pixmap; will attempt to return stored rasters to OS." */

static Object string_constant_9;   /* "~%~d stored rasters returned to OS.~%" */

/* CREATE-STORED-RASTER */
Object create_stored_raster(gensym_window,width,height,depth,irregular_size_p)
    Object gensym_window, width, height, depth, irregular_size_p;
{
    Object temp, do_not_error_in_x11_create_pixmap_on_failed_allocation;
    Object gensym_x_window, the_raster, count_of_rasters, raster;
    SI_Long pixmap_or_error_flag;
    Declare_special(1);

    x_note_fn_call(55,157);
    temp = ISVREF(gensym_window,(SI_Long)24L);
    if (EQ(temp,Qx11_pixmap)) {
	do_not_error_in_x11_create_pixmap_on_failed_allocation = T;
	PUSH_SPECIAL_WITH_SYMBOL(Do_not_error_in_x11_create_pixmap_on_failed_allocation,Qdo_not_error_in_x11_create_pixmap_on_failed_allocation,do_not_error_in_x11_create_pixmap_on_failed_allocation,
		0);
	  gensym_x_window = ISVREF(gensym_window,(SI_Long)17L);
	  pixmap_or_error_flag = g2ext_create_pixmap(IFIX(gensym_x_window),
		  IFIX(width),IFIX(height),IFIX(depth),irregular_size_p ? 
		  (SI_Long)1L : (SI_Long)0L);
	  if (pixmap_or_error_flag < (SI_Long)0L) {
	      if ( 
		      !TRUEP(Do_not_error_in_x11_create_pixmap_on_failed_allocation))
		  handle_no_solution_to_raster_allocation_failure(gensym_x_window,
			  width,height);
	      the_raster = LONG_TO_FIXNUM(pixmap_or_error_flag);
	  }
	  else
	      the_raster = LONG_TO_FIXNUM(pixmap_or_error_flag);
	POP_SPECIAL();
	if (IFIX(the_raster) < (SI_Long)0L) {
	    notify_user_at_console(3,string_constant_8,width,height);
	    count_of_rasters = 
		    hard_reclaim_all_reclaimed_stored_rasters(gensym_window);
	    notify_user_at_console(2,string_constant_9,count_of_rasters);
	    gensym_x_window = ISVREF(gensym_window,(SI_Long)17L);
	    pixmap_or_error_flag = 
		    g2ext_create_pixmap(IFIX(gensym_x_window),IFIX(width),
		    IFIX(height),IFIX(depth),irregular_size_p ? 
		    (SI_Long)1L : (SI_Long)0L);
	    if (pixmap_or_error_flag < (SI_Long)0L) {
		if ( 
			!TRUEP(Do_not_error_in_x11_create_pixmap_on_failed_allocation))
		    handle_no_solution_to_raster_allocation_failure(gensym_x_window,
			    width,height);
		raster = LONG_TO_FIXNUM(pixmap_or_error_flag);
	    }
	    else
		raster = LONG_TO_FIXNUM(pixmap_or_error_flag);
	}
	else
	    raster = the_raster;
    }
    else
	raster = Nil;
    return VALUES_1(raster);
}

Object The_type_description_of_pixmap = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_pixmaps, Qchain_of_available_pixmaps);

DEFINE_VARIABLE_WITH_SYMBOL(Pixmap_count, Qpixmap_count);

Object Chain_of_available_pixmaps_vector = UNBOUND;

/* PIXMAP-STRUCTURE-MEMORY-USAGE */
Object pixmap_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(55,158);
    temp = Pixmap_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)5L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-PIXMAP-COUNT */
Object outstanding_pixmap_count()
{
    Object def_structure_pixmap_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(55,159);
    gensymed_symbol = IFIX(Pixmap_count);
    def_structure_pixmap_variable = Chain_of_available_pixmaps;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_pixmap_variable))
	goto end_loop;
    def_structure_pixmap_variable = ISVREF(def_structure_pixmap_variable,
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

/* RECLAIM-PIXMAP-1-1 */
Object reclaim_pixmap_1_1(pixmap)
    Object pixmap;
{
    Object temp, svref_arg_2;

    x_note_fn_call(55,160);
    inline_note_reclaim_cons(pixmap,Nil);
    temp = ISVREF(Chain_of_available_pixmaps_vector,
	    IFIX(Current_thread_index));
    SVREF(pixmap,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_pixmaps_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = pixmap;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-PIXMAP */
Object reclaim_structure_for_pixmap(pixmap)
    Object pixmap;
{
    x_note_fn_call(55,161);
    return reclaim_pixmap_1_1(pixmap);
}

static Object Qg2_defstruct_structure_name_pixmap_g2_struct;  /* g2-defstruct-structure-name::pixmap-g2-struct */

/* MAKE-PERMANENT-PIXMAP-STRUCTURE-INTERNAL */
Object make_permanent_pixmap_structure_internal()
{
    Object def_structure_pixmap_variable, defstruct_g2_pixmap_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(55,162);
    def_structure_pixmap_variable = Nil;
    atomic_incff_symval(Qpixmap_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_pixmap_variable = Nil;
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
	defstruct_g2_pixmap_variable = the_array;
	SVREF(defstruct_g2_pixmap_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_pixmap_g2_struct;
	def_structure_pixmap_variable = defstruct_g2_pixmap_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_pixmap_variable);
}

/* MAKE-PIXMAP-1 */
Object make_pixmap_1(pixmap_width,pixmap_height,pixmap_depth,pixmap_pointer)
    Object pixmap_width, pixmap_height, pixmap_depth, pixmap_pointer;
{
    Object def_structure_pixmap_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(55,163);
    def_structure_pixmap_variable = 
	    ISVREF(Chain_of_available_pixmaps_vector,
	    IFIX(Current_thread_index));
    if (def_structure_pixmap_variable) {
	svref_arg_1 = Chain_of_available_pixmaps_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_pixmap_variable,(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_pixmap_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_pixmap_g2_struct;
    }
    else
	def_structure_pixmap_variable = 
		make_permanent_pixmap_structure_internal();
    inline_note_allocate_cons(def_structure_pixmap_variable,Nil);
    SVREF(def_structure_pixmap_variable,FIX((SI_Long)1L)) = pixmap_width;
    SVREF(def_structure_pixmap_variable,FIX((SI_Long)2L)) = pixmap_height;
    SVREF(def_structure_pixmap_variable,FIX((SI_Long)3L)) = pixmap_depth;
    SVREF(def_structure_pixmap_variable,FIX((SI_Long)4L)) = pixmap_pointer;
    return VALUES_1(def_structure_pixmap_variable);
}

/* RECLAIM-PIXMAP */
Object reclaim_pixmap(pixmap_qm)
    Object pixmap_qm;
{
    x_note_fn_call(55,164);
    if (pixmap_qm) {
	g2ext_reclaim_pixmap(IFIX(ISVREF(pixmap_qm,(SI_Long)4L)));
	return reclaim_pixmap_1_1(pixmap_qm);
    }
    else
	return VALUES_1(Nil);
}

/* HARD-RECLAIM-ALL-RECLAIMED-STORED-RASTERS */
Object hard_reclaim_all_reclaimed_stored_rasters(gensym_window)
    Object gensym_window;
{
    Object temp;

    x_note_fn_call(55,165);
    temp = 
	    hard_reclaim_all_regular_size_reclaimed_stored_rasters(gensym_window);
    return VALUES_1(FIXNUM_ADD(temp,
	    hard_reclaim_all_irregular_size_reclaimed_stored_rasters(gensym_window)));
}

/* HARD-RECLAIM-ALL-REGULAR-SIZE-RECLAIMED-STORED-RASTERS */
Object hard_reclaim_all_regular_size_reclaimed_stored_rasters(gensym_window)
    Object gensym_window;
{
    Object count_1, max_index, pool_vector, ab_loop_iter_flag_;
    Object stored_raster_qm, graphics_pop_store, cons_1, next_cons, temp;
    Object svref_arg_2;
    SI_Long ab_loop_repeat_, index_1, ab_loop_bind_;

    x_note_fn_call(55,166);
    count_1 = FIX((SI_Long)0L);
    max_index = Maximum_managed_simple_vector_size;
    ab_loop_repeat_ = (SI_Long)2L;
    pool_vector = ISVREF(gensym_window,(SI_Long)25L);
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !((SI_Long)0L < ab_loop_repeat_))
	goto end_loop;
    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
    if ( !TRUEP(ab_loop_iter_flag_))
	pool_vector = ISVREF(gensym_window,(SI_Long)26L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(max_index);
  next_loop_1:
    if (index_1 >= ab_loop_bind_)
	goto end_loop_1;
    stored_raster_qm = Nil;
  next_loop_2:
    graphics_pop_store = Nil;
    cons_1 = ISVREF(pool_vector,index_1);
    if (cons_1) {
	graphics_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qgraphics);
	if (ISVREF(Available_graphics_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_graphics_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_graphics_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_graphics_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_graphics_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    ISVREF(pool_vector,index_1) = next_cons;
    stored_raster_qm = graphics_pop_store;
    if ( !TRUEP(stored_raster_qm))
	goto end_loop_2;
    count_1 = FIXNUM_ADD1(count_1);
    g2ext_reclaim_pixmap(IFIX(stored_raster_qm));
    goto next_loop_2;
  end_loop_2:;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    return VALUES_1(count_1);
    return VALUES_1(Qnil);
}

/* HARD-RECLAIM-ALL-IRREGULAR-SIZE-RECLAIMED-STORED-RASTERS */
Object hard_reclaim_all_irregular_size_reclaimed_stored_rasters(gensym_window)
    Object gensym_window;
{
    Object count_1, pool_vector, raster_info_qm, graphics_pop_store, cons_1;
    Object next_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(55,167);
    count_1 = FIX((SI_Long)0L);
    pool_vector = ISVREF(gensym_window,(SI_Long)27L);
    raster_info_qm = Nil;
  next_loop:
    graphics_pop_store = Nil;
    cons_1 = pool_vector;
    if (cons_1) {
	graphics_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qgraphics);
	if (ISVREF(Available_graphics_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_graphics_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_graphics_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_graphics_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_graphics_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    pool_vector = next_cons;
    raster_info_qm = graphics_pop_store;
    if ( !TRUEP(raster_info_qm))
	goto end_loop;
    count_1 = FIXNUM_ADD1(count_1);
    g2ext_reclaim_pixmap(IFIX(THIRD(raster_info_qm)));
    reclaim_graphics_list_1(raster_info_qm);
    goto next_loop;
  end_loop:
    reclaim_graphics_list_1(pool_vector);
    SVREF(gensym_window,FIX((SI_Long)27L)) = Nil;
    temp_1 = count_1;
    count_1 = FIX((SI_Long)0L);
    pool_vector = ISVREF(gensym_window,(SI_Long)28L);
    raster_info_qm = Nil;
  next_loop_1:
    graphics_pop_store = Nil;
    cons_1 = pool_vector;
    if (cons_1) {
	graphics_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qgraphics);
	if (ISVREF(Available_graphics_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_graphics_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_graphics_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_graphics_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_graphics_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    pool_vector = next_cons;
    raster_info_qm = graphics_pop_store;
    if ( !TRUEP(raster_info_qm))
	goto end_loop_1;
    count_1 = FIXNUM_ADD1(count_1);
    g2ext_reclaim_pixmap(IFIX(THIRD(raster_info_qm)));
    reclaim_graphics_list_1(raster_info_qm);
    goto next_loop_1;
  end_loop_1:
    reclaim_graphics_list_1(pool_vector);
    SVREF(gensym_window,FIX((SI_Long)28L)) = Nil;
    return VALUES_1(FIXNUM_ADD(temp_1,count_1));
}

/* FIND-IRREGULAR-SIZE-STORED-RASTER */
Object find_irregular_size_stored_raster(gensym_window,minimum_width,
	    minimum_height,bits_per_pixel)
    Object gensym_window, minimum_width, minimum_height, bits_per_pixel;
{
    Object irregular_size_raster_pool, the_stored_raster_qm, trailer_qm;
    Object rest_of_pool, raster_info, temp, temp_1;

    x_note_fn_call(55,168);
    irregular_size_raster_pool = IFIX(bits_per_pixel) <= (SI_Long)1L ? 
	    ISVREF(gensym_window,(SI_Long)27L) : ISVREF(gensym_window,
	    (SI_Long)28L);
    the_stored_raster_qm = Nil;
    if (irregular_size_raster_pool) {
	trailer_qm = Nil;
	rest_of_pool = irregular_size_raster_pool;
	raster_info = Nil;
      next_loop:
	raster_info = CAR(rest_of_pool);
	if (FIXNUM_EQ(FIRST(raster_info),minimum_width) && 
		FIXNUM_EQ(SECOND(raster_info),minimum_height)) {
	    the_stored_raster_qm = THIRD(raster_info);
	    reclaim_graphics_list_1(raster_info);
	    goto end_loop;
	}
	trailer_qm = rest_of_pool;
	rest_of_pool = CDR(rest_of_pool);
	if ( !TRUEP(rest_of_pool))
	    goto end_loop;
	goto next_loop;
      end_loop:
	if (the_stored_raster_qm) {
	    if (trailer_qm) {
		temp = CDR(rest_of_pool);
		M_CDR(trailer_qm) = temp;
	    }
	    else if (IFIX(bits_per_pixel) <= (SI_Long)1L) {
		temp = CDR(irregular_size_raster_pool);
		SVREF(gensym_window,FIX((SI_Long)27L)) = temp;
	    }
	    else {
		temp = CDR(irregular_size_raster_pool);
		SVREF(gensym_window,FIX((SI_Long)28L)) = temp;
	    }
	    reclaim_graphics_cons_1(rest_of_pool);
	}
    }
    if (the_stored_raster_qm)
	return clear_stored_raster(the_stored_raster_qm,
		ISVREF(gensym_window,(SI_Long)24L),minimum_width,
		minimum_height);
    else {
	temp_1 = create_stored_raster(gensym_window,minimum_width,
		minimum_height,bits_per_pixel,T);
	return VALUES_2(temp_1,T);
    }
}

/* ALLOCATE-STORED-RASTER */
Object allocate_stored_raster(gensym_window,minimum_width,minimum_height,
	    bits_per_pixel,make_exact_size_p)
    Object gensym_window, minimum_width, minimum_height, bits_per_pixel;
    Object make_exact_size_p;
{
    Object width, height;
    Object result;

    x_note_fn_call(55,169);
    if (Current_scratchpad_raster_tiled_p) {
	result = raster_dimensions_given_max_and_offset(minimum_width,
		minimum_height,Current_x_max_for_stored_raster_qm,
		Current_x_offset_for_stored_raster_qm,
		Current_y_max_for_stored_raster_qm,
		Current_y_offset_for_stored_raster_qm);
	MVS_2(result,width,height);
	return allocate_tiled_raster(gensym_window,width,height,
		bits_per_pixel);
    }
    else
	return allocate_stored_raster_1(gensym_window,minimum_width,
		minimum_height,bits_per_pixel,make_exact_size_p);
}

/* RASTER-DIMENSIONS-GIVEN-MAX-AND-OFFSET */
Object raster_dimensions_given_max_and_offset(width,height,
	    x_max_for_stored_raster_qm,x_offset_for_stored_raster_qm,
	    y_max_for_stored_raster_qm,y_offset_for_stored_raster_qm)
    Object width, height, x_max_for_stored_raster_qm;
    Object x_offset_for_stored_raster_qm, y_max_for_stored_raster_qm;
    Object y_offset_for_stored_raster_qm;
{
    Object temp, temp_1;

    x_note_fn_call(55,170);
    if (x_offset_for_stored_raster_qm) {
	temp = FIXNUM_MINUS(x_max_for_stored_raster_qm,
		x_offset_for_stored_raster_qm);
	temp_1 = FIXNUM_MINUS(y_max_for_stored_raster_qm,
		y_offset_for_stored_raster_qm);
	return VALUES_2(temp,temp_1);
    }
    else
	return VALUES_2(width,height);
}

/* ALLOCATE-STORED-RASTER-1 */
Object allocate_stored_raster_1(gensym_window,minimum_width,minimum_height,
	    bits_per_pixel,make_exact_size_p)
    Object gensym_window, minimum_width, minimum_height, bits_per_pixel;
    Object make_exact_size_p;
{
    Object current_regular_raster_width, current_regular_raster_height;
    Object current_regular_raster_width_index;
    Object current_regular_raster_height_index, pool, graphics_pop_store;
    Object cons_1, next_cons, temp, svref_arg_2_1, stored_raster_qm, temp_1;
    SI_Long svref_arg_2;

    x_note_fn_call(55,171);
    current_regular_raster_width = FIX((SI_Long)0L);
    current_regular_raster_height = FIX((SI_Long)0L);
    current_regular_raster_width_index = FIX((SI_Long)0L);
    current_regular_raster_height_index = FIX((SI_Long)0L);
    if (IFIX(minimum_width) <= (SI_Long)64L) {
	if (IFIX(minimum_width) <= (SI_Long)16L) {
	    if (IFIX(minimum_width) <= (SI_Long)8L) {
		if (IFIX(minimum_width) <= (SI_Long)4L) {
		    current_regular_raster_width = FIX((SI_Long)4L);
		    current_regular_raster_width_index = FIX((SI_Long)0L);
		}
		else {
		    current_regular_raster_width = FIX((SI_Long)8L);
		    current_regular_raster_width_index = FIX((SI_Long)1L);
		}
	    }
	    else if (IFIX(minimum_width) <= (SI_Long)12L) {
		current_regular_raster_width = FIX((SI_Long)12L);
		current_regular_raster_width_index = FIX((SI_Long)2L);
	    }
	    else {
		current_regular_raster_width = FIX((SI_Long)16L);
		current_regular_raster_width_index = FIX((SI_Long)3L);
	    }
	}
	else if (IFIX(minimum_width) <= (SI_Long)32L) {
	    if (IFIX(minimum_width) <= (SI_Long)24L) {
		current_regular_raster_width = FIX((SI_Long)24L);
		current_regular_raster_width_index = FIX((SI_Long)4L);
	    }
	    else {
		current_regular_raster_width = FIX((SI_Long)32L);
		current_regular_raster_width_index = FIX((SI_Long)5L);
	    }
	}
	else if (IFIX(minimum_width) <= (SI_Long)56L) {
	    current_regular_raster_width = FIX((SI_Long)56L);
	    current_regular_raster_width_index = FIX((SI_Long)6L);
	}
	else {
	    current_regular_raster_width = FIX((SI_Long)64L);
	    current_regular_raster_width_index = FIX((SI_Long)7L);
	}
    }
    else if (IFIX(minimum_width) <= (SI_Long)200L) {
	if (IFIX(minimum_width) <= (SI_Long)128L) {
	    if (IFIX(minimum_width) <= (SI_Long)104L) {
		current_regular_raster_width = FIX((SI_Long)104L);
		current_regular_raster_width_index = FIX((SI_Long)8L);
	    }
	    else {
		current_regular_raster_width = FIX((SI_Long)128L);
		current_regular_raster_width_index = FIX((SI_Long)9L);
	    }
	}
	else if (IFIX(minimum_width) <= (SI_Long)152L) {
	    current_regular_raster_width = FIX((SI_Long)152L);
	    current_regular_raster_width_index = FIX((SI_Long)10L);
	}
	else {
	    current_regular_raster_width = FIX((SI_Long)200L);
	    current_regular_raster_width_index = FIX((SI_Long)11L);
	}
    }
    else if (IFIX(minimum_width) <= (SI_Long)256L) {
	current_regular_raster_width = FIX((SI_Long)256L);
	current_regular_raster_width_index = FIX((SI_Long)12L);
    }
    else if (IFIX(minimum_width) <= (SI_Long)400L) {
	current_regular_raster_width = FIX((SI_Long)400L);
	current_regular_raster_width_index = FIX((SI_Long)13L);
    }
    else
	current_regular_raster_width_index = FIX((SI_Long)-1L);
    if (IFIX(minimum_height) <= (SI_Long)64L) {
	if (IFIX(minimum_height) <= (SI_Long)16L) {
	    if (IFIX(minimum_height) <= (SI_Long)8L) {
		if (IFIX(minimum_height) <= (SI_Long)4L) {
		    current_regular_raster_height = FIX((SI_Long)4L);
		    current_regular_raster_height_index = FIX((SI_Long)0L);
		}
		else {
		    current_regular_raster_height = FIX((SI_Long)8L);
		    current_regular_raster_height_index = FIX((SI_Long)1L);
		}
	    }
	    else if (IFIX(minimum_height) <= (SI_Long)12L) {
		current_regular_raster_height = FIX((SI_Long)12L);
		current_regular_raster_height_index = FIX((SI_Long)2L);
	    }
	    else {
		current_regular_raster_height = FIX((SI_Long)16L);
		current_regular_raster_height_index = FIX((SI_Long)3L);
	    }
	}
	else if (IFIX(minimum_height) <= (SI_Long)32L) {
	    if (IFIX(minimum_height) <= (SI_Long)24L) {
		current_regular_raster_height = FIX((SI_Long)24L);
		current_regular_raster_height_index = FIX((SI_Long)4L);
	    }
	    else {
		current_regular_raster_height = FIX((SI_Long)32L);
		current_regular_raster_height_index = FIX((SI_Long)5L);
	    }
	}
	else if (IFIX(minimum_height) <= (SI_Long)56L) {
	    current_regular_raster_height = FIX((SI_Long)56L);
	    current_regular_raster_height_index = FIX((SI_Long)6L);
	}
	else {
	    current_regular_raster_height = FIX((SI_Long)64L);
	    current_regular_raster_height_index = FIX((SI_Long)7L);
	}
    }
    else if (IFIX(minimum_height) <= (SI_Long)200L) {
	if (IFIX(minimum_height) <= (SI_Long)128L) {
	    if (IFIX(minimum_height) <= (SI_Long)104L) {
		current_regular_raster_height = FIX((SI_Long)104L);
		current_regular_raster_height_index = FIX((SI_Long)8L);
	    }
	    else {
		current_regular_raster_height = FIX((SI_Long)128L);
		current_regular_raster_height_index = FIX((SI_Long)9L);
	    }
	}
	else if (IFIX(minimum_height) <= (SI_Long)152L) {
	    current_regular_raster_height = FIX((SI_Long)152L);
	    current_regular_raster_height_index = FIX((SI_Long)10L);
	}
	else {
	    current_regular_raster_height = FIX((SI_Long)200L);
	    current_regular_raster_height_index = FIX((SI_Long)11L);
	}
    }
    else if (IFIX(minimum_height) <= (SI_Long)256L) {
	current_regular_raster_height = FIX((SI_Long)256L);
	current_regular_raster_height_index = FIX((SI_Long)12L);
    }
    else if (IFIX(minimum_height) <= (SI_Long)400L) {
	current_regular_raster_height = FIX((SI_Long)400L);
	current_regular_raster_height_index = FIX((SI_Long)13L);
    }
    else
	current_regular_raster_height_index = FIX((SI_Long)-1L);
    if (IFIX(current_regular_raster_width_index) < (SI_Long)0L || 
	    IFIX(current_regular_raster_height_index) < (SI_Long)0L || 
	    make_exact_size_p &&  !(FIXNUM_EQ(minimum_width,
	    current_regular_raster_width) && FIXNUM_EQ(minimum_height,
	    current_regular_raster_height)))
	return find_irregular_size_stored_raster(gensym_window,
		minimum_width,minimum_height,bits_per_pixel);
    else {
	pool = IFIX(bits_per_pixel) <= (SI_Long)1L ? ISVREF(gensym_window,
		(SI_Long)25L) : ISVREF(gensym_window,(SI_Long)26L);
	graphics_pop_store = Nil;
	svref_arg_2 = IFIX(current_regular_raster_width_index) + 
		IFIX(current_regular_raster_height_index) * (SI_Long)32L;
	cons_1 = ISVREF(pool,svref_arg_2);
	if (cons_1) {
	    graphics_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qgraphics);
	    if (ISVREF(Available_graphics_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_graphics_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = cons_1;
		temp = Available_graphics_conses_tail_vector;
		svref_arg_2_1 = Current_thread_index;
		SVREF(temp,svref_arg_2_1) = cons_1;
	    }
	    else {
		temp = Available_graphics_conses_vector;
		svref_arg_2_1 = Current_thread_index;
		SVREF(temp,svref_arg_2_1) = cons_1;
		temp = Available_graphics_conses_tail_vector;
		svref_arg_2_1 = Current_thread_index;
		SVREF(temp,svref_arg_2_1) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	ISVREF(pool,svref_arg_2) = next_cons;
	stored_raster_qm = graphics_pop_store;
	if (stored_raster_qm)
	    return clear_stored_raster(stored_raster_qm,
		    ISVREF(gensym_window,(SI_Long)24L),minimum_width,
		    minimum_height);
	else {
	    temp_1 = create_stored_raster(gensym_window,
		    current_regular_raster_width,
		    current_regular_raster_height,bits_per_pixel,Nil);
	    return VALUES_2(temp_1,T);
	}
    }
}

/* ALLOCATE-BIGGER-STORED-RASTER */
Object allocate_bigger_stored_raster(gensym_window,minimum_width,
	    minimum_height,bits_per_pixel)
    Object gensym_window, minimum_width, minimum_height, bits_per_pixel;
{
    Object pool_vector, max_index, current_regular_raster_width;
    Object current_regular_raster_height, current_regular_raster_width_index;
    Object current_regular_raster_height_index, bigger_stored_raster_qm;
    Object graphics_pop_store, cons_1, next_cons, temp, svref_arg_2;
    SI_Long bigger_index, ab_loop_bind_;

    x_note_fn_call(55,172);
    pool_vector = IFIX(bits_per_pixel) <= (SI_Long)1L ? 
	    ISVREF(gensym_window,(SI_Long)25L) : ISVREF(gensym_window,
	    (SI_Long)26L);
    max_index = Maximum_managed_simple_vector_size;
    current_regular_raster_width = FIX((SI_Long)0L);
    current_regular_raster_height = FIX((SI_Long)0L);
    current_regular_raster_width_index = FIX((SI_Long)0L);
    current_regular_raster_height_index = FIX((SI_Long)0L);
    if (IFIX(minimum_width) <= (SI_Long)64L) {
	if (IFIX(minimum_width) <= (SI_Long)16L) {
	    if (IFIX(minimum_width) <= (SI_Long)8L) {
		if (IFIX(minimum_width) <= (SI_Long)4L) {
		    current_regular_raster_width = FIX((SI_Long)4L);
		    current_regular_raster_width_index = FIX((SI_Long)0L);
		}
		else {
		    current_regular_raster_width = FIX((SI_Long)8L);
		    current_regular_raster_width_index = FIX((SI_Long)1L);
		}
	    }
	    else if (IFIX(minimum_width) <= (SI_Long)12L) {
		current_regular_raster_width = FIX((SI_Long)12L);
		current_regular_raster_width_index = FIX((SI_Long)2L);
	    }
	    else {
		current_regular_raster_width = FIX((SI_Long)16L);
		current_regular_raster_width_index = FIX((SI_Long)3L);
	    }
	}
	else if (IFIX(minimum_width) <= (SI_Long)32L) {
	    if (IFIX(minimum_width) <= (SI_Long)24L) {
		current_regular_raster_width = FIX((SI_Long)24L);
		current_regular_raster_width_index = FIX((SI_Long)4L);
	    }
	    else {
		current_regular_raster_width = FIX((SI_Long)32L);
		current_regular_raster_width_index = FIX((SI_Long)5L);
	    }
	}
	else if (IFIX(minimum_width) <= (SI_Long)56L) {
	    current_regular_raster_width = FIX((SI_Long)56L);
	    current_regular_raster_width_index = FIX((SI_Long)6L);
	}
	else {
	    current_regular_raster_width = FIX((SI_Long)64L);
	    current_regular_raster_width_index = FIX((SI_Long)7L);
	}
    }
    else if (IFIX(minimum_width) <= (SI_Long)200L) {
	if (IFIX(minimum_width) <= (SI_Long)128L) {
	    if (IFIX(minimum_width) <= (SI_Long)104L) {
		current_regular_raster_width = FIX((SI_Long)104L);
		current_regular_raster_width_index = FIX((SI_Long)8L);
	    }
	    else {
		current_regular_raster_width = FIX((SI_Long)128L);
		current_regular_raster_width_index = FIX((SI_Long)9L);
	    }
	}
	else if (IFIX(minimum_width) <= (SI_Long)152L) {
	    current_regular_raster_width = FIX((SI_Long)152L);
	    current_regular_raster_width_index = FIX((SI_Long)10L);
	}
	else {
	    current_regular_raster_width = FIX((SI_Long)200L);
	    current_regular_raster_width_index = FIX((SI_Long)11L);
	}
    }
    else if (IFIX(minimum_width) <= (SI_Long)256L) {
	current_regular_raster_width = FIX((SI_Long)256L);
	current_regular_raster_width_index = FIX((SI_Long)12L);
    }
    else if (IFIX(minimum_width) <= (SI_Long)400L) {
	current_regular_raster_width = FIX((SI_Long)400L);
	current_regular_raster_width_index = FIX((SI_Long)13L);
    }
    else
	current_regular_raster_width_index = FIX((SI_Long)-1L);
    if (IFIX(minimum_height) <= (SI_Long)64L) {
	if (IFIX(minimum_height) <= (SI_Long)16L) {
	    if (IFIX(minimum_height) <= (SI_Long)8L) {
		if (IFIX(minimum_height) <= (SI_Long)4L) {
		    current_regular_raster_height = FIX((SI_Long)4L);
		    current_regular_raster_height_index = FIX((SI_Long)0L);
		}
		else {
		    current_regular_raster_height = FIX((SI_Long)8L);
		    current_regular_raster_height_index = FIX((SI_Long)1L);
		}
	    }
	    else if (IFIX(minimum_height) <= (SI_Long)12L) {
		current_regular_raster_height = FIX((SI_Long)12L);
		current_regular_raster_height_index = FIX((SI_Long)2L);
	    }
	    else {
		current_regular_raster_height = FIX((SI_Long)16L);
		current_regular_raster_height_index = FIX((SI_Long)3L);
	    }
	}
	else if (IFIX(minimum_height) <= (SI_Long)32L) {
	    if (IFIX(minimum_height) <= (SI_Long)24L) {
		current_regular_raster_height = FIX((SI_Long)24L);
		current_regular_raster_height_index = FIX((SI_Long)4L);
	    }
	    else {
		current_regular_raster_height = FIX((SI_Long)32L);
		current_regular_raster_height_index = FIX((SI_Long)5L);
	    }
	}
	else if (IFIX(minimum_height) <= (SI_Long)56L) {
	    current_regular_raster_height = FIX((SI_Long)56L);
	    current_regular_raster_height_index = FIX((SI_Long)6L);
	}
	else {
	    current_regular_raster_height = FIX((SI_Long)64L);
	    current_regular_raster_height_index = FIX((SI_Long)7L);
	}
    }
    else if (IFIX(minimum_height) <= (SI_Long)200L) {
	if (IFIX(minimum_height) <= (SI_Long)128L) {
	    if (IFIX(minimum_height) <= (SI_Long)104L) {
		current_regular_raster_height = FIX((SI_Long)104L);
		current_regular_raster_height_index = FIX((SI_Long)8L);
	    }
	    else {
		current_regular_raster_height = FIX((SI_Long)128L);
		current_regular_raster_height_index = FIX((SI_Long)9L);
	    }
	}
	else if (IFIX(minimum_height) <= (SI_Long)152L) {
	    current_regular_raster_height = FIX((SI_Long)152L);
	    current_regular_raster_height_index = FIX((SI_Long)10L);
	}
	else {
	    current_regular_raster_height = FIX((SI_Long)200L);
	    current_regular_raster_height_index = FIX((SI_Long)11L);
	}
    }
    else if (IFIX(minimum_height) <= (SI_Long)256L) {
	current_regular_raster_height = FIX((SI_Long)256L);
	current_regular_raster_height_index = FIX((SI_Long)12L);
    }
    else if (IFIX(minimum_height) <= (SI_Long)400L) {
	current_regular_raster_height = FIX((SI_Long)400L);
	current_regular_raster_height_index = FIX((SI_Long)13L);
    }
    else
	current_regular_raster_height_index = FIX((SI_Long)-1L);
    bigger_index = 
	    IFIX(FIXNUM_ADD1(FIX(IFIX(current_regular_raster_width_index) 
	    + IFIX(current_regular_raster_height_index) * (SI_Long)32L)));
    ab_loop_bind_ = IFIX(max_index);
    bigger_stored_raster_qm = Nil;
  next_loop:
    if (bigger_index >= ab_loop_bind_)
	goto end_loop;
    graphics_pop_store = Nil;
    cons_1 = ISVREF(pool_vector,bigger_index);
    if (cons_1) {
	graphics_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qgraphics);
	if (ISVREF(Available_graphics_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_graphics_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_graphics_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_graphics_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_graphics_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    ISVREF(pool_vector,bigger_index) = next_cons;
    bigger_stored_raster_qm = graphics_pop_store;
    if (bigger_stored_raster_qm) {
	clear_stored_raster(bigger_stored_raster_qm,ISVREF(gensym_window,
		(SI_Long)24L),minimum_width,minimum_height);
	return VALUES_1(bigger_stored_raster_qm);
    }
    bigger_index = bigger_index + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return find_irregular_size_stored_raster(gensym_window,minimum_width,
	    minimum_height,bits_per_pixel);
    return VALUES_1(Qnil);
}

/* STORED-RASTER-IN-REGULAR-POOL? */
Object stored_raster_in_regular_pool_qm(gensym_window,width,height,depth)
    Object gensym_window, width, height, depth;
{
    Object current_regular_raster_width, current_regular_raster_height;
    Object current_regular_raster_width_index;
    Object current_regular_raster_height_index, pool, list_1;

    x_note_fn_call(55,173);
    current_regular_raster_width = FIX((SI_Long)0L);
    current_regular_raster_height = FIX((SI_Long)0L);
    current_regular_raster_width_index = FIX((SI_Long)0L);
    current_regular_raster_height_index = FIX((SI_Long)0L);
    if (IFIX(width) <= (SI_Long)64L) {
	if (IFIX(width) <= (SI_Long)16L) {
	    if (IFIX(width) <= (SI_Long)8L) {
		if (IFIX(width) <= (SI_Long)4L) {
		    current_regular_raster_width = FIX((SI_Long)4L);
		    current_regular_raster_width_index = FIX((SI_Long)0L);
		}
		else {
		    current_regular_raster_width = FIX((SI_Long)8L);
		    current_regular_raster_width_index = FIX((SI_Long)1L);
		}
	    }
	    else if (IFIX(width) <= (SI_Long)12L) {
		current_regular_raster_width = FIX((SI_Long)12L);
		current_regular_raster_width_index = FIX((SI_Long)2L);
	    }
	    else {
		current_regular_raster_width = FIX((SI_Long)16L);
		current_regular_raster_width_index = FIX((SI_Long)3L);
	    }
	}
	else if (IFIX(width) <= (SI_Long)32L) {
	    if (IFIX(width) <= (SI_Long)24L) {
		current_regular_raster_width = FIX((SI_Long)24L);
		current_regular_raster_width_index = FIX((SI_Long)4L);
	    }
	    else {
		current_regular_raster_width = FIX((SI_Long)32L);
		current_regular_raster_width_index = FIX((SI_Long)5L);
	    }
	}
	else if (IFIX(width) <= (SI_Long)56L) {
	    current_regular_raster_width = FIX((SI_Long)56L);
	    current_regular_raster_width_index = FIX((SI_Long)6L);
	}
	else {
	    current_regular_raster_width = FIX((SI_Long)64L);
	    current_regular_raster_width_index = FIX((SI_Long)7L);
	}
    }
    else if (IFIX(width) <= (SI_Long)200L) {
	if (IFIX(width) <= (SI_Long)128L) {
	    if (IFIX(width) <= (SI_Long)104L) {
		current_regular_raster_width = FIX((SI_Long)104L);
		current_regular_raster_width_index = FIX((SI_Long)8L);
	    }
	    else {
		current_regular_raster_width = FIX((SI_Long)128L);
		current_regular_raster_width_index = FIX((SI_Long)9L);
	    }
	}
	else if (IFIX(width) <= (SI_Long)152L) {
	    current_regular_raster_width = FIX((SI_Long)152L);
	    current_regular_raster_width_index = FIX((SI_Long)10L);
	}
	else {
	    current_regular_raster_width = FIX((SI_Long)200L);
	    current_regular_raster_width_index = FIX((SI_Long)11L);
	}
    }
    else if (IFIX(width) <= (SI_Long)256L) {
	current_regular_raster_width = FIX((SI_Long)256L);
	current_regular_raster_width_index = FIX((SI_Long)12L);
    }
    else if (IFIX(width) <= (SI_Long)400L) {
	current_regular_raster_width = FIX((SI_Long)400L);
	current_regular_raster_width_index = FIX((SI_Long)13L);
    }
    else
	current_regular_raster_width_index = FIX((SI_Long)-1L);
    if (IFIX(height) <= (SI_Long)64L) {
	if (IFIX(height) <= (SI_Long)16L) {
	    if (IFIX(height) <= (SI_Long)8L) {
		if (IFIX(height) <= (SI_Long)4L) {
		    current_regular_raster_height = FIX((SI_Long)4L);
		    current_regular_raster_height_index = FIX((SI_Long)0L);
		}
		else {
		    current_regular_raster_height = FIX((SI_Long)8L);
		    current_regular_raster_height_index = FIX((SI_Long)1L);
		}
	    }
	    else if (IFIX(height) <= (SI_Long)12L) {
		current_regular_raster_height = FIX((SI_Long)12L);
		current_regular_raster_height_index = FIX((SI_Long)2L);
	    }
	    else {
		current_regular_raster_height = FIX((SI_Long)16L);
		current_regular_raster_height_index = FIX((SI_Long)3L);
	    }
	}
	else if (IFIX(height) <= (SI_Long)32L) {
	    if (IFIX(height) <= (SI_Long)24L) {
		current_regular_raster_height = FIX((SI_Long)24L);
		current_regular_raster_height_index = FIX((SI_Long)4L);
	    }
	    else {
		current_regular_raster_height = FIX((SI_Long)32L);
		current_regular_raster_height_index = FIX((SI_Long)5L);
	    }
	}
	else if (IFIX(height) <= (SI_Long)56L) {
	    current_regular_raster_height = FIX((SI_Long)56L);
	    current_regular_raster_height_index = FIX((SI_Long)6L);
	}
	else {
	    current_regular_raster_height = FIX((SI_Long)64L);
	    current_regular_raster_height_index = FIX((SI_Long)7L);
	}
    }
    else if (IFIX(height) <= (SI_Long)200L) {
	if (IFIX(height) <= (SI_Long)128L) {
	    if (IFIX(height) <= (SI_Long)104L) {
		current_regular_raster_height = FIX((SI_Long)104L);
		current_regular_raster_height_index = FIX((SI_Long)8L);
	    }
	    else {
		current_regular_raster_height = FIX((SI_Long)128L);
		current_regular_raster_height_index = FIX((SI_Long)9L);
	    }
	}
	else if (IFIX(height) <= (SI_Long)152L) {
	    current_regular_raster_height = FIX((SI_Long)152L);
	    current_regular_raster_height_index = FIX((SI_Long)10L);
	}
	else {
	    current_regular_raster_height = FIX((SI_Long)200L);
	    current_regular_raster_height_index = FIX((SI_Long)11L);
	}
    }
    else if (IFIX(height) <= (SI_Long)256L) {
	current_regular_raster_height = FIX((SI_Long)256L);
	current_regular_raster_height_index = FIX((SI_Long)12L);
    }
    else if (IFIX(height) <= (SI_Long)400L) {
	current_regular_raster_height = FIX((SI_Long)400L);
	current_regular_raster_height_index = FIX((SI_Long)13L);
    }
    else
	current_regular_raster_height_index = FIX((SI_Long)-1L);
    if (IFIX(current_regular_raster_width_index) >= (SI_Long)0L && 
	    IFIX(current_regular_raster_height_index) >= (SI_Long)0L) {
	pool = IFIX(depth) <= (SI_Long)1L ? ISVREF(gensym_window,
		(SI_Long)25L) : ISVREF(gensym_window,(SI_Long)26L);
	list_1 = ISVREF(pool,IFIX(current_regular_raster_width_index) + 
		IFIX(current_regular_raster_height_index) * (SI_Long)32L);
	return VALUES_1( ! !TRUEP(list_1) ? T : Nil);
    }
    else
	return VALUES_1(Nil);
}

Object Prefer_to_hard_reclaim_irregular_sized_rasters_p = UNBOUND;

/* RECLAIM-IRREGULAR-SIZE-STORED-RASTER */
Object reclaim_irregular_size_stored_raster(stored_raster_to_be_reclaimed,
	    gensym_window,minimum_width,minimum_height,bits_per_pixel)
    Object stored_raster_to_be_reclaimed, gensym_window, minimum_width;
    Object minimum_height, bits_per_pixel;
{
    Object temp, raster_info;

    x_note_fn_call(55,174);
    if (Prefer_to_hard_reclaim_irregular_sized_rasters_p) {
	temp = ISVREF(gensym_window,(SI_Long)1L);
	if (EQ(temp,Qx11_window)) {
	    g2ext_reclaim_pixmap(IFIX(stored_raster_to_be_reclaimed));
	    temp = T;
	}
	else
	    temp = Nil;
    }
    else
	temp = Nil;
    if (temp);
    else {
	raster_info = graphics_list_4(minimum_width,minimum_height,
		stored_raster_to_be_reclaimed,bits_per_pixel);
	if (IFIX(bits_per_pixel) <= (SI_Long)1L) {
	    temp = graphics_cons_1(raster_info,ISVREF(gensym_window,
		    (SI_Long)27L));
	    SVREF(gensym_window,FIX((SI_Long)27L)) = temp;
	}
	else {
	    temp = graphics_cons_1(raster_info,ISVREF(gensym_window,
		    (SI_Long)28L));
	    SVREF(gensym_window,FIX((SI_Long)28L)) = temp;
	}
    }
    return VALUES_1(temp);
}

/* RECLAIM-STORED-RASTER */
Object reclaim_stored_raster(stored_raster_to_be_reclaimed,gensym_window,
	    minimum_width,minimum_height,bits_per_pixel,made_exact_size_p)
    Object stored_raster_to_be_reclaimed, gensym_window, minimum_width;
    Object minimum_height, bits_per_pixel, made_exact_size_p;
{
    Object temp;

    x_note_fn_call(55,175);
    temp = SIMPLE_VECTOR_P(stored_raster_to_be_reclaimed) && 
	    EQ(ISVREF(stored_raster_to_be_reclaimed,(SI_Long)0L),
	    Qg2_defstruct_structure_name_tiled_raster_g2_struct) ? 
	    reclaim_tiled_raster(stored_raster_to_be_reclaimed) : 
	    reclaim_stored_raster_1(stored_raster_to_be_reclaimed,
	    gensym_window,minimum_width,minimum_height,bits_per_pixel,
	    made_exact_size_p);
    return VALUES_1(temp);
}

/* RECLAIM-STORED-RASTER-1 */
Object reclaim_stored_raster_1(stored_raster_to_be_reclaimed,gensym_window,
	    minimum_width,minimum_height,bits_per_pixel,made_exact_size_p)
    Object stored_raster_to_be_reclaimed, gensym_window, minimum_width;
    Object minimum_height, bits_per_pixel, made_exact_size_p;
{
    Object current_regular_raster_width, current_regular_raster_height;
    Object current_regular_raster_width_index;
    Object current_regular_raster_height_index, temp, raster_pools, result_1;
    SI_Long svref_arg_2;

    x_note_fn_call(55,176);
    current_regular_raster_width = FIX((SI_Long)0L);
    current_regular_raster_height = FIX((SI_Long)0L);
    current_regular_raster_width_index = FIX((SI_Long)0L);
    current_regular_raster_height_index = FIX((SI_Long)0L);
    if (IFIX(minimum_width) <= (SI_Long)64L) {
	if (IFIX(minimum_width) <= (SI_Long)16L) {
	    if (IFIX(minimum_width) <= (SI_Long)8L) {
		if (IFIX(minimum_width) <= (SI_Long)4L) {
		    current_regular_raster_width = FIX((SI_Long)4L);
		    current_regular_raster_width_index = FIX((SI_Long)0L);
		}
		else {
		    current_regular_raster_width = FIX((SI_Long)8L);
		    current_regular_raster_width_index = FIX((SI_Long)1L);
		}
	    }
	    else if (IFIX(minimum_width) <= (SI_Long)12L) {
		current_regular_raster_width = FIX((SI_Long)12L);
		current_regular_raster_width_index = FIX((SI_Long)2L);
	    }
	    else {
		current_regular_raster_width = FIX((SI_Long)16L);
		current_regular_raster_width_index = FIX((SI_Long)3L);
	    }
	}
	else if (IFIX(minimum_width) <= (SI_Long)32L) {
	    if (IFIX(minimum_width) <= (SI_Long)24L) {
		current_regular_raster_width = FIX((SI_Long)24L);
		current_regular_raster_width_index = FIX((SI_Long)4L);
	    }
	    else {
		current_regular_raster_width = FIX((SI_Long)32L);
		current_regular_raster_width_index = FIX((SI_Long)5L);
	    }
	}
	else if (IFIX(minimum_width) <= (SI_Long)56L) {
	    current_regular_raster_width = FIX((SI_Long)56L);
	    current_regular_raster_width_index = FIX((SI_Long)6L);
	}
	else {
	    current_regular_raster_width = FIX((SI_Long)64L);
	    current_regular_raster_width_index = FIX((SI_Long)7L);
	}
    }
    else if (IFIX(minimum_width) <= (SI_Long)200L) {
	if (IFIX(minimum_width) <= (SI_Long)128L) {
	    if (IFIX(minimum_width) <= (SI_Long)104L) {
		current_regular_raster_width = FIX((SI_Long)104L);
		current_regular_raster_width_index = FIX((SI_Long)8L);
	    }
	    else {
		current_regular_raster_width = FIX((SI_Long)128L);
		current_regular_raster_width_index = FIX((SI_Long)9L);
	    }
	}
	else if (IFIX(minimum_width) <= (SI_Long)152L) {
	    current_regular_raster_width = FIX((SI_Long)152L);
	    current_regular_raster_width_index = FIX((SI_Long)10L);
	}
	else {
	    current_regular_raster_width = FIX((SI_Long)200L);
	    current_regular_raster_width_index = FIX((SI_Long)11L);
	}
    }
    else if (IFIX(minimum_width) <= (SI_Long)256L) {
	current_regular_raster_width = FIX((SI_Long)256L);
	current_regular_raster_width_index = FIX((SI_Long)12L);
    }
    else if (IFIX(minimum_width) <= (SI_Long)400L) {
	current_regular_raster_width = FIX((SI_Long)400L);
	current_regular_raster_width_index = FIX((SI_Long)13L);
    }
    else
	current_regular_raster_width_index = FIX((SI_Long)-1L);
    if (IFIX(minimum_height) <= (SI_Long)64L) {
	if (IFIX(minimum_height) <= (SI_Long)16L) {
	    if (IFIX(minimum_height) <= (SI_Long)8L) {
		if (IFIX(minimum_height) <= (SI_Long)4L) {
		    current_regular_raster_height = FIX((SI_Long)4L);
		    current_regular_raster_height_index = FIX((SI_Long)0L);
		}
		else {
		    current_regular_raster_height = FIX((SI_Long)8L);
		    current_regular_raster_height_index = FIX((SI_Long)1L);
		}
	    }
	    else if (IFIX(minimum_height) <= (SI_Long)12L) {
		current_regular_raster_height = FIX((SI_Long)12L);
		current_regular_raster_height_index = FIX((SI_Long)2L);
	    }
	    else {
		current_regular_raster_height = FIX((SI_Long)16L);
		current_regular_raster_height_index = FIX((SI_Long)3L);
	    }
	}
	else if (IFIX(minimum_height) <= (SI_Long)32L) {
	    if (IFIX(minimum_height) <= (SI_Long)24L) {
		current_regular_raster_height = FIX((SI_Long)24L);
		current_regular_raster_height_index = FIX((SI_Long)4L);
	    }
	    else {
		current_regular_raster_height = FIX((SI_Long)32L);
		current_regular_raster_height_index = FIX((SI_Long)5L);
	    }
	}
	else if (IFIX(minimum_height) <= (SI_Long)56L) {
	    current_regular_raster_height = FIX((SI_Long)56L);
	    current_regular_raster_height_index = FIX((SI_Long)6L);
	}
	else {
	    current_regular_raster_height = FIX((SI_Long)64L);
	    current_regular_raster_height_index = FIX((SI_Long)7L);
	}
    }
    else if (IFIX(minimum_height) <= (SI_Long)200L) {
	if (IFIX(minimum_height) <= (SI_Long)128L) {
	    if (IFIX(minimum_height) <= (SI_Long)104L) {
		current_regular_raster_height = FIX((SI_Long)104L);
		current_regular_raster_height_index = FIX((SI_Long)8L);
	    }
	    else {
		current_regular_raster_height = FIX((SI_Long)128L);
		current_regular_raster_height_index = FIX((SI_Long)9L);
	    }
	}
	else if (IFIX(minimum_height) <= (SI_Long)152L) {
	    current_regular_raster_height = FIX((SI_Long)152L);
	    current_regular_raster_height_index = FIX((SI_Long)10L);
	}
	else {
	    current_regular_raster_height = FIX((SI_Long)200L);
	    current_regular_raster_height_index = FIX((SI_Long)11L);
	}
    }
    else if (IFIX(minimum_height) <= (SI_Long)256L) {
	current_regular_raster_height = FIX((SI_Long)256L);
	current_regular_raster_height_index = FIX((SI_Long)12L);
    }
    else if (IFIX(minimum_height) <= (SI_Long)400L) {
	current_regular_raster_height = FIX((SI_Long)400L);
	current_regular_raster_height_index = FIX((SI_Long)13L);
    }
    else
	current_regular_raster_height_index = FIX((SI_Long)-1L);
    if (IFIX(current_regular_raster_width_index) < (SI_Long)0L || 
	    IFIX(current_regular_raster_height_index) < (SI_Long)0L || 
	    made_exact_size_p &&  !(FIXNUM_EQ(minimum_width,
	    current_regular_raster_width) && FIXNUM_EQ(minimum_height,
	    current_regular_raster_height)))
	temp = 
		reclaim_irregular_size_stored_raster(stored_raster_to_be_reclaimed,
		gensym_window,minimum_width,minimum_height,bits_per_pixel);
    else {
	raster_pools = IFIX(bits_per_pixel) <= (SI_Long)1L ? 
		ISVREF(gensym_window,(SI_Long)25L) : ISVREF(gensym_window,
		(SI_Long)26L);
	result_1 = graphics_cons_1(stored_raster_to_be_reclaimed,
		ISVREF(raster_pools,
		IFIX(current_regular_raster_width_index) + 
		IFIX(current_regular_raster_height_index) * (SI_Long)32L));
	svref_arg_2 = IFIX(current_regular_raster_width_index) + 
		IFIX(current_regular_raster_height_index) * (SI_Long)32L;
	ISVREF(raster_pools,svref_arg_2) = result_1;
	temp = result_1;
    }
    return VALUES_1(temp);
}

/* ALLOCATE-TILED-RASTER */
Object allocate_tiled_raster(gensym_window,required_width,required_height,
	    bits_per_pixel)
    Object gensym_window, required_width, required_height, bits_per_pixel;
{
    Object tiled_raster, svref_new_value;

    x_note_fn_call(55,177);
    tiled_raster = make_tiled_raster_1();
    SVREF(tiled_raster,FIX((SI_Long)4L)) = gensym_window;
    SVREF(tiled_raster,FIX((SI_Long)5L)) = bits_per_pixel;
    svref_new_value = make_tile_arrays(tiled_raster,gensym_window,
	    required_width,required_height,bits_per_pixel,T);
    SVREF(tiled_raster,FIX((SI_Long)1L)) = svref_new_value;
    return VALUES_1(tiled_raster);
}

/* ALLOCATE-JUST-TILED-RASTER */
Object allocate_just_tiled_raster(gensym_window,required_width,
	    required_height,bits_per_pixel,singleton_p)
    Object gensym_window, required_width, required_height, bits_per_pixel;
    Object singleton_p;
{
    Object tiled_raster, svref_new_value;

    x_note_fn_call(55,178);
    tiled_raster = make_tiled_raster_1();
    SVREF(tiled_raster,FIX((SI_Long)4L)) = gensym_window;
    SVREF(tiled_raster,FIX((SI_Long)5L)) = bits_per_pixel;
    svref_new_value = singleton_p ? make_singleton_tile_array(tiled_raster,
	    required_width) : make_tile_arrays(tiled_raster,gensym_window,
	    required_width,required_height,bits_per_pixel,Nil);
    SVREF(tiled_raster,FIX((SI_Long)1L)) = svref_new_value;
    return VALUES_1(tiled_raster);
}

/* MAKE-SINGLETON-TILE-ARRAY */
Object make_singleton_tile_array(tiled_raster,size)
    Object tiled_raster, size;
{
    Object row_array, row, temp, svref_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(55,179);
    row_array = allocate_managed_array(1,FIX((SI_Long)1L));
    row = allocate_managed_array(1,FIX((SI_Long)1L));
    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
      if (FIXNUM_LE(ISVREF(row_array,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	  temp = Row;
	  SVREF(row_array,FIX((SI_Long)2L)) = temp;
      }
      else {
	  temp = ISVREF(row_array,(SI_Long)2L);
	  svref_new_value = Row;
	  SVREF(temp,FIX((SI_Long)0L)) = svref_new_value;
      }
      if (FIXNUM_LE(ISVREF(Row,(SI_Long)1L),Maximum_in_place_array_size)) {
	  temp = Row;
	  SVREF(temp,FIX((SI_Long)2L)) = Nil;
      }
      else {
	  temp = ISVREF(Row,(SI_Long)2L);
	  SVREF(temp,FIX((SI_Long)0L)) = Nil;
      }
      SVREF(tiled_raster,FIX((SI_Long)2L)) = size;
      ISVREF(tiled_raster,(SI_Long)3L) = FIX((SI_Long)0L);
      result = VALUES_1(row_array);
    POP_SPECIAL();
    return result;
}

static Object Qreclaim_all_scaled_fonts;  /* reclaim-all-scaled-fonts */

/* MAKE-TILE-ARRAYS */
Object make_tile_arrays(tiled_raster,gensym_window,required_width,
	    required_height,bits_per_pixel,allocate_rasters_qm)
    Object tiled_raster, gensym_window, required_width, required_height;
    Object bits_per_pixel, allocate_rasters_qm;
{
    Object tile_size, tile_size_index, number_of_rows, number_of_columns;
    Object row_array, row, temp, svref_new_value;
    SI_Long i, ab_loop_bind_, svref_arg_2, j, ab_loop_bind__1;
    Declare_special(1);
    Object result;

    x_note_fn_call(55,180);
    tile_size = Nil;
    tile_size_index = Nil;
    number_of_rows = Nil;
    number_of_columns = Nil;
    row_array = Nil;
    result = compute_tile_size_given_required_area(required_width,
	    required_height);
    MVS_2(result,tile_size,tile_size_index);
    SVREF(tiled_raster,FIX((SI_Long)2L)) = tile_size;
    SVREF(tiled_raster,FIX((SI_Long)3L)) = tile_size_index;
    result = compute_rows_columns_given_tile_size(tile_size,required_width,
	    required_height);
    MVS_2(result,number_of_rows,number_of_columns);
    row_array = allocate_managed_array(1,number_of_rows);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(number_of_rows);
    row = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
    next_loop:
      if (i >= ab_loop_bind_)
	  goto end_loop;
      Row = allocate_managed_array(1,number_of_columns);
      if (FIXNUM_LE(ISVREF(row_array,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	  svref_arg_2 = i + IFIX(Managed_array_index_offset);
	  temp = Row;
	  ISVREF(row_array,svref_arg_2) = temp;
      }
      else {
	  temp = ISVREF(row_array,(i >>  -  - (SI_Long)10L) + (SI_Long)2L);
	  svref_arg_2 = i & (SI_Long)1023L;
	  svref_new_value = Row;
	  ISVREF(temp,svref_arg_2) = svref_new_value;
      }
      j = (SI_Long)0L;
      ab_loop_bind__1 = IFIX(number_of_columns);
    next_loop_1:
      if (j >= ab_loop_bind__1)
	  goto end_loop_1;
      if (FIXNUM_LE(ISVREF(Row,(SI_Long)1L),Maximum_in_place_array_size)) {
	  temp = Row;
	  svref_arg_2 = j + IFIX(Managed_array_index_offset);
	  svref_new_value = allocate_rasters_qm ? 
		  allocate_scratchpad_raster(gensym_window,tile_size,
		  tile_size,SYMBOL_FUNCTION(Qreclaim_all_scaled_fonts)) : Nil;
	  ISVREF(temp,svref_arg_2) = svref_new_value;
      }
      else {
	  temp = ISVREF(Row,(j >>  -  - (SI_Long)10L) + (SI_Long)2L);
	  svref_arg_2 = j & (SI_Long)1023L;
	  svref_new_value = allocate_rasters_qm ? 
		  allocate_scratchpad_raster(gensym_window,tile_size,
		  tile_size,SYMBOL_FUNCTION(Qreclaim_all_scaled_fonts)) : Nil;
	  ISVREF(temp,svref_arg_2) = svref_new_value;
      }
      j = j + (SI_Long)1L;
      goto next_loop_1;
    end_loop_1:;
      i = i + (SI_Long)1L;
      goto next_loop;
    end_loop:;
    POP_SPECIAL();
    return VALUES_1(row_array);
}

/* COMPUTE-ROWS-COLUMNS-GIVEN-TILE-SIZE */
Object compute_rows_columns_given_tile_size(tile_edge_size_in_pixels,
	    required_width,required_height)
    Object tile_edge_size_in_pixels, required_width, required_height;
{
    Object temp, temp_1;

    x_note_fn_call(55,181);
    temp = ceiling(required_height,tile_edge_size_in_pixels);
    temp_1 = ceiling(required_width,tile_edge_size_in_pixels);
    return VALUES_2(temp,temp_1);
}

/* RECLAIM-TILED-RASTER */
Object reclaim_tiled_raster(tiled_raster)
    Object tiled_raster;
{
    Object tile_arrays, number_of_rows, row, gensym_window, bits_per_pixel;
    Object tile_size, stored_raster_qm, temp;
    SI_Long number_of_columns, i, ab_loop_bind_, j, ab_loop_bind__1;
    Declare_special(1);

    x_note_fn_call(55,182);
    tile_arrays = ISVREF(tiled_raster,(SI_Long)1L);
    number_of_rows = ISVREF(ISVREF(tiled_raster,(SI_Long)1L),(SI_Long)1L);
    row = ISVREF(tiled_raster,(SI_Long)1L);
    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
      number_of_columns = IFIX(ISVREF(Row,(SI_Long)1L)) > (SI_Long)0L ? 
	      IFIX(ISVREF(FIXNUM_LE(ISVREF(Row,(SI_Long)1L),
	      Maximum_in_place_array_size) ? ISVREF(Row,(SI_Long)0L + 
	      IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(Row,
	      (SI_Long)2L),(SI_Long)0L),(SI_Long)1L)) : (SI_Long)0L;
    POP_SPECIAL();
    gensym_window = ISVREF(tiled_raster,(SI_Long)4L);
    bits_per_pixel = ISVREF(tiled_raster,(SI_Long)5L);
    tile_size = ISVREF(tiled_raster,(SI_Long)2L);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(number_of_rows);
    row = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
    next_loop:
      if (i >= ab_loop_bind_)
	  goto end_loop;
      Row = FIXNUM_LE(ISVREF(tile_arrays,(SI_Long)1L),
	      Maximum_in_place_array_size) ? ISVREF(tile_arrays,i + 
	      IFIX(Managed_array_index_offset)) : 
	      ISVREF(ISVREF(tile_arrays,(i >>  -  - (SI_Long)10L) + 
	      (SI_Long)2L),i & (SI_Long)1023L);
      j = (SI_Long)0L;
      ab_loop_bind__1 = number_of_columns;
      stored_raster_qm = Nil;
    next_loop_1:
      if (j >= ab_loop_bind__1)
	  goto end_loop_1;
      stored_raster_qm = FIXNUM_LE(ISVREF(Row,(SI_Long)1L),
	      Maximum_in_place_array_size) ? ISVREF(Row,j + 
	      IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(Row,(j >>  
	      -  - (SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L);
      if (stored_raster_qm)
	  reclaim_stored_raster_1(stored_raster_qm,gensym_window,tile_size,
		  tile_size,bits_per_pixel,Nil);
      j = j + (SI_Long)1L;
      goto next_loop_1;
    end_loop_1:;
      reclaim_managed_array(Row);
      i = i + (SI_Long)1L;
      goto next_loop;
    end_loop:;
    POP_SPECIAL();
    reclaim_managed_array(tile_arrays);
    temp = reclaim_tiled_raster_internal_1(tiled_raster);
    return VALUES_1(temp);
}

/* COMPUTE-TILE-SIZE-GIVEN-REQUIRED-AREA */
Object compute_tile_size_given_required_area(required_width,required_height)
    Object required_width, required_height;
{
    Object larger_dimension, smaller_dimension, minimum_required_size, size;
    Object index_1, temp;
    SI_Long temp_1;

    x_note_fn_call(55,183);
    larger_dimension = Nil;
    smaller_dimension = Nil;
    minimum_required_size = Nil;
    size = Nil;
    index_1 = Nil;
    if (FIXNUM_GT(required_width,required_height)) {
	larger_dimension = required_width;
	smaller_dimension = required_height;
    }
    else {
	larger_dimension = required_height;
	smaller_dimension = required_width;
    }
    temp = ceiling(larger_dimension,FIX((SI_Long)4L));
    temp_1 = IFIX(FIXNUM_MAX(temp,smaller_dimension));
    minimum_required_size = FIX(MAX(temp_1,(SI_Long)32L));
    if (IFIX(minimum_required_size) <= (SI_Long)64L) {
	if (IFIX(minimum_required_size) <= (SI_Long)16L) {
	    if (IFIX(minimum_required_size) <= (SI_Long)8L) {
		if (IFIX(minimum_required_size) <= (SI_Long)4L) {
		    size = FIX((SI_Long)4L);
		    index_1 = FIX((SI_Long)0L);
		}
		else {
		    size = FIX((SI_Long)8L);
		    index_1 = FIX((SI_Long)1L);
		}
	    }
	    else if (IFIX(minimum_required_size) <= (SI_Long)12L) {
		size = FIX((SI_Long)12L);
		index_1 = FIX((SI_Long)2L);
	    }
	    else {
		size = FIX((SI_Long)16L);
		index_1 = FIX((SI_Long)3L);
	    }
	}
	else if (IFIX(minimum_required_size) <= (SI_Long)32L) {
	    if (IFIX(minimum_required_size) <= (SI_Long)24L) {
		size = FIX((SI_Long)24L);
		index_1 = FIX((SI_Long)4L);
	    }
	    else {
		size = FIX((SI_Long)32L);
		index_1 = FIX((SI_Long)5L);
	    }
	}
	else if (IFIX(minimum_required_size) <= (SI_Long)56L) {
	    size = FIX((SI_Long)56L);
	    index_1 = FIX((SI_Long)6L);
	}
	else {
	    size = FIX((SI_Long)64L);
	    index_1 = FIX((SI_Long)7L);
	}
    }
    else if (IFIX(minimum_required_size) <= (SI_Long)200L) {
	if (IFIX(minimum_required_size) <= (SI_Long)128L) {
	    if (IFIX(minimum_required_size) <= (SI_Long)104L) {
		size = FIX((SI_Long)104L);
		index_1 = FIX((SI_Long)8L);
	    }
	    else {
		size = FIX((SI_Long)128L);
		index_1 = FIX((SI_Long)9L);
	    }
	}
	else if (IFIX(minimum_required_size) <= (SI_Long)152L) {
	    size = FIX((SI_Long)152L);
	    index_1 = FIX((SI_Long)10L);
	}
	else {
	    size = FIX((SI_Long)200L);
	    index_1 = FIX((SI_Long)11L);
	}
    }
    else if (IFIX(minimum_required_size) <= (SI_Long)256L) {
	size = FIX((SI_Long)256L);
	index_1 = FIX((SI_Long)12L);
    }
    else if (IFIX(minimum_required_size) <= (SI_Long)400L) {
	size = FIX((SI_Long)400L);
	index_1 = FIX((SI_Long)13L);
    }
    else
	index_1 = FIX((SI_Long)-1L);
    if (IFIX(index_1) < (SI_Long)0L) {
	size = FIX((SI_Long)400L);
	index_1 = FIX((SI_Long)13L);
    }
    return VALUES_2(size,index_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Region_and_tile_x_offset, Qregion_and_tile_x_offset);

DEFINE_VARIABLE_WITH_SYMBOL(Region_and_tile_y_offset, Qregion_and_tile_y_offset);

/* BEEP-IN-WINDOW-1 */
Object beep_in_window_1(gensym_window)
    Object gensym_window;
{
    Object temp;

    x_note_fn_call(55,184);
    temp = ISVREF(gensym_window,(SI_Long)1L);
    if (EQ(temp,Qx11_window))
	return VALUES_1(FIX(g2ext_x11_bell(IFIX(ISVREF(gensym_window,
		(SI_Long)17L)),(SI_Long)100L)));
    else
	return VALUES_1(Nil);
}

/* UPDATE-WINDOW */
Object update_window varargs_1(int, n)
{
    Object gensym_window, left_edge_of_update_area, top_edge_of_update_area;
    Object right_edge_of_update_area, bottom_edge_of_update_area, function;
    Object arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11;
    Object left_edge_of_draw_area, top_edge_of_draw_area;
    Object right_edge_of_draw_area, bottom_edge_of_draw_area;
    Object current_image_x_scale, current_image_y_scale;
    Object current_x_origin_of_drawing, current_y_origin_of_drawing;
    Object current_window_1, drawing_on_window, current_drawing_transfer_mode;
    Object type_of_current_window, current_native_window_qm, current_color_map;
    Object temp, current_background_color_value;
    Object current_foreground_color_value, defer_notifications_qm;
    Object icp_output_port_qm, icp_socket_qm, i_am_alive_info_qm;
    Object icp_output_port_qm_1, current_icp_port, current_icp_socket;
    Object disable_resumability, number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, aref_arg_1;
    char temp_1;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(34);
    Object result;

    x_note_fn_call(55,185);
    INIT_ARGS_nonrelocating();
    gensym_window = REQUIRED_ARG_nonrelocating();
    left_edge_of_update_area = REQUIRED_ARG_nonrelocating();
    top_edge_of_update_area = REQUIRED_ARG_nonrelocating();
    right_edge_of_update_area = REQUIRED_ARG_nonrelocating();
    bottom_edge_of_update_area = REQUIRED_ARG_nonrelocating();
    function = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    arg1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg3 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg4 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg5 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg6 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg7 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg8 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg9 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg10 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     No_arg;
    arg11 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     No_arg;
    END_ARGS_nonrelocating();
    left_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)7L);
    top_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)8L);
    right_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)9L);
    bottom_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)10L);
    PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
	    33);
      PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
	      32);
	PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
		31);
	  PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
		  30);
	    current_image_x_scale = FIX((SI_Long)4096L);
	    current_image_y_scale = FIX((SI_Long)4096L);
	    current_x_origin_of_drawing = FIX((SI_Long)0L);
	    current_y_origin_of_drawing = FIX((SI_Long)0L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
		    29);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
		      28);
		PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
			27);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
			  26);
		    left_edge_of_draw_area = Left_edge_of_draw_area;
		    top_edge_of_draw_area = Top_edge_of_draw_area;
		    right_edge_of_draw_area = Right_edge_of_draw_area;
		    bottom_edge_of_draw_area = Bottom_edge_of_draw_area;
		    PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
			    25);
		      PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
			      24);
			PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
				23);
			  PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
				  22);
			    Left_edge_of_draw_area = 
				    FIXNUM_MAX(left_edge_of_update_area,
				    Left_edge_of_draw_area);
			    Top_edge_of_draw_area = 
				    FIXNUM_MAX(top_edge_of_update_area,
				    Top_edge_of_draw_area);
			    Right_edge_of_draw_area = 
				    FIXNUM_MIN(right_edge_of_update_area,
				    Right_edge_of_draw_area);
			    Bottom_edge_of_draw_area = 
				    FIXNUM_MIN(bottom_edge_of_update_area,
				    Bottom_edge_of_draw_area);
			    if (FIXNUM_LT(Left_edge_of_draw_area,
				    Right_edge_of_draw_area) && 
				    FIXNUM_LT(Top_edge_of_draw_area,
				    Bottom_edge_of_draw_area)) {
				LOCK(On_window_without_drawing);
				if (PUSH_UNWIND_PROTECT(1)) {
				    current_window_1 = gensym_window;
				    PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
					    21);
				      drawing_on_window = Nil;
				      PUSH_SPECIAL_WITH_SYMBOL(Drawing_on_window,Qdrawing_on_window,drawing_on_window,
					      20);
					current_drawing_transfer_mode = 
						EQ(Current_drawing_transfer_mode,
						Kxor) ? 
						Current_drawing_transfer_mode 
						: ISVREF(Current_window,
						(SI_Long)30L);
					PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
						19);
					  type_of_current_window = 
						  ISVREF(Current_window,
						  (SI_Long)1L);
					  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
						  18);
					    current_native_window_qm = 
						    ISVREF(Current_window,
						    (SI_Long)17L);
					    PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
						    17);
					      current_color_map = 
						      ISVREF(Current_window,
						      (SI_Long)20L);
					      PUSH_SPECIAL_WITH_SYMBOL(Current_color_map,Qcurrent_color_map,current_color_map,
						      16);
						temp = 
							ISVREF(Current_color_map,
							(SI_Long)5L);
						if (temp);
						else
						    temp = 
							    map_to_color_value_1(Qwhite);
						current_background_color_value 
							= temp;
						PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
							15);
						  temp = 
							  ISVREF(Current_color_map,
							  (SI_Long)4L);
						  if (temp);
						  else
						      temp = 
							      map_to_color_value_1(Qblack);
						  current_foreground_color_value 
							  = temp;
						  PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
							  14);
						    defer_notifications_qm = T;
						    PUSH_SPECIAL_WITH_SYMBOL(Defer_notifications_qm,Qdefer_notifications_qm,defer_notifications_qm,
							    13);
						      LOCK(On_window_with_drawing);
						      if (PUSH_UNWIND_PROTECT(0)) 
								  {
							  drawing_on_window 
								  = T;
							  PUSH_SPECIAL_WITH_SYMBOL(Drawing_on_window,Qdrawing_on_window,drawing_on_window,
								  12);
							    if (EQ(Type_of_current_window,
								    Qx11_window)) 
									{
								if (EQ(arg1,
									No_arg))
								    temp = 
									    FUNCALL_0(SYMBOL_FUNCTION(function));
								else if (EQ(arg2,
									No_arg)) 
									    {
								    temp = 
									    SYMBOL_FUNCTION(function);
								    temp = 
									    FUNCALL_1(temp,
									    arg1);
								}
								else if (EQ(arg3,
									No_arg)) 
									    {
								    temp = 
									    SYMBOL_FUNCTION(function);
								    temp = 
									    FUNCALL_2(temp,
									    arg1,
									    arg2);
								}
								else if (EQ(arg4,
									No_arg)) 
									    {
								    temp = 
									    SYMBOL_FUNCTION(function);
								    temp = 
									    FUNCALL_3(temp,
									    arg1,
									    arg2,
									    arg3);
								}
								else if (EQ(arg5,
									No_arg)) 
									    {
								    temp = 
									    SYMBOL_FUNCTION(function);
								    temp = 
									    FUNCALL_4(temp,
									    arg1,
									    arg2,
									    arg3,
									    arg4);
								}
								else if (EQ(arg6,
									No_arg)) 
									    {
								    temp = 
									    SYMBOL_FUNCTION(function);
								    temp = 
									    FUNCALL_5(temp,
									    arg1,
									    arg2,
									    arg3,
									    arg4,
									    arg5);
								}
								else if (EQ(arg7,
									No_arg))
								    temp = 
									    funcall(7,
									    SYMBOL_FUNCTION(function),
									    arg1,
									    arg2,
									    arg3,
									    arg4,
									    arg5,
									    arg6);
								else if (EQ(arg8,
									No_arg))
								    temp = 
									    funcall(8,
									    SYMBOL_FUNCTION(function),
									    arg1,
									    arg2,
									    arg3,
									    arg4,
									    arg5,
									    arg6,
									    arg7);
								else if (EQ(arg9,
									No_arg))
								    temp = 
									    funcall(9,
									    SYMBOL_FUNCTION(function),
									    arg1,
									    arg2,
									    arg3,
									    arg4,
									    arg5,
									    arg6,
									    arg7,
									    arg8);
								else if (EQ(arg10,
									No_arg))
								    temp = 
									    funcall(10,
									    SYMBOL_FUNCTION(function),
									    arg1,
									    arg2,
									    arg3,
									    arg4,
									    arg5,
									    arg6,
									    arg7,
									    arg8,
									    arg9);
								else if (EQ(arg11,
									No_arg))
								    temp = 
									    funcall(11,
									    SYMBOL_FUNCTION(function),
									    arg1,
									    arg2,
									    arg3,
									    arg4,
									    arg5,
									    arg6,
									    arg7,
									    arg8,
									    arg9,
									    arg10);
								else
								    temp = 
									    funcall(12,
									    SYMBOL_FUNCTION(function),
									    arg1,
									    arg2,
									    arg3,
									    arg4,
									    arg5,
									    arg6,
									    arg7,
									    arg8,
									    arg9,
									    arg10,
									    arg11);
								SAVE_VALUES(VALUES_1(temp));
								if (Flush_graphics_immediately_qm)
								    sync_graphics_on_current_window();
							    }
							    else if (EQ(Type_of_current_window,
								    Qicp)) {
								icp_output_port_qm 
									= 
									ISVREF(Current_window,
									(SI_Long)12L);
								icp_socket_qm 
									= 
									icp_output_port_qm 
									? 
									ISVREF(icp_output_port_qm,
									(SI_Long)2L) 
									: Qnil;
								if (icp_socket_qm) 
									    {
								    i_am_alive_info_qm 
									    = 
									    ISVREF(icp_socket_qm,
									    (SI_Long)24L);
								    temp_1 
									    = 
									     
									    !TRUEP(i_am_alive_info_qm);
								    if (temp_1);
								    else
									temp_1 
										= 
										 
										!TRUEP(Do_icp_flow_control_qm);
								    if (temp_1);
								    else
									temp_1 
										= 
										 
										!TRUEP(ISVREF(i_am_alive_info_qm,
										(SI_Long)2L));
								}
								else
								    temp_1 
									    = 
									    TRUEP(Nil);
								if (temp_1) {
								    icp_output_port_qm_1 
									    = 
									    ISVREF(Current_window,
									    (SI_Long)12L);
								    if (icp_output_port_qm_1 
									    && 
									    icp_connection_open_p(ISVREF(icp_output_port_qm_1,
									    (SI_Long)2L))) 
										{
									current_icp_port 
										= 
										icp_output_port_qm_1;
									PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
										11);
									  current_icp_socket 
										  = 
										  ISVREF(Current_icp_port,
										  (SI_Long)2L);
									  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
										  10);
									    temp 
										    = 
										    IFIX(ISVREF(Current_icp_socket,
										    (SI_Long)22L)) 
										    >= 
										    (SI_Long)17L 
										    ?
										     
										    ISVREF(Current_icp_socket,
										    (SI_Long)53L) 
										    :
										     
										    Nil;
									    if (temp);
									    else
										temp 
											= 
											EQ(ISVREF(Current_icp_socket,
											(SI_Long)25L),
											Qtelewindows) 
											?
											 T : Nil;
									    disable_resumability 
										    = 
										    temp;
									    PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
										    9);
									      number_of_icp_bytes_for_message_series 
										      = 
										      FIX((SI_Long)0L);
									      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
										      8);
										icp_buffers_for_message_group 
											= 
											Nil;
										PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
											7);
										  icp_buffer_of_start_of_message_series_qm 
											  = 
											  Nil;
										  PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
											  6);
										    icp_byte_position_of_start_of_message_series_qm 
											    = 
											    Nil;
										    PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
											    5);
										      number_of_icp_bytes_to_fill_buffer 
											      = 
											      FIX((SI_Long)0L);
										      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
											      4);
											current_icp_buffer 
												= 
												Nil;
											PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
												3);
											  current_write_icp_byte_position 
												  = 
												  Nil;
											  PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
												  2);
											    number_of_icp_bytes_in_message_group 
												    = 
												    FIX((SI_Long)0L);
											    PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
												    1);
											      writing_icp_message_group 
												      = 
												      FIXNUM_ADD1(Writing_icp_message_group);
											      PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
												      0);
												gensymed_symbol 
													= 
													Nil;
												gensymed_symbol_1 
													= 
													0.0;
												gensymed_symbol_2 
													= 
													0.0;
												if (Profiling_enabled_qm) 
													    {
												    gensymed_symbol 
													    = 
													    T;
												    gensymed_symbol_1 
													    = 
													    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
													    (SI_Long)2L),
													    (SI_Long)0L);
												    gensymed_symbol_2 
													    = 
													    g2ext_unix_time_as_float();
												    aref_arg_1 
													    = 
													    ISVREF(Profiling_enabled_qm,
													    (SI_Long)2L);
												    DFLOAT_ISASET_1(aref_arg_1,
													    (SI_Long)0L,
													    gensymed_symbol_2);
												}
												if (icp_connection_open_p(Current_icp_socket) 
													&& 
													 
													!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
													    {
												    synchronize_icp_on_window_with_drawing(Current_window,
													    Left_edge_of_draw_area,
													    Top_edge_of_draw_area,
													    Right_edge_of_draw_area,
													    Bottom_edge_of_draw_area);
												    if (EQ(arg1,
													    No_arg))
													temp 
														= 
														FUNCALL_0(SYMBOL_FUNCTION(function));
												    else if (EQ(arg2,
													    No_arg)) 
														{
													temp 
														= 
														SYMBOL_FUNCTION(function);
													temp 
														= 
														FUNCALL_1(temp,
														arg1);
												    }
												    else if (EQ(arg3,
													    No_arg)) 
														{
													temp 
														= 
														SYMBOL_FUNCTION(function);
													temp 
														= 
														FUNCALL_2(temp,
														arg1,
														arg2);
												    }
												    else if (EQ(arg4,
													    No_arg)) 
														{
													temp 
														= 
														SYMBOL_FUNCTION(function);
													temp 
														= 
														FUNCALL_3(temp,
														arg1,
														arg2,
														arg3);
												    }
												    else if (EQ(arg5,
													    No_arg)) 
														{
													temp 
														= 
														SYMBOL_FUNCTION(function);
													temp 
														= 
														FUNCALL_4(temp,
														arg1,
														arg2,
														arg3,
														arg4);
												    }
												    else if (EQ(arg6,
													    No_arg)) 
														{
													temp 
														= 
														SYMBOL_FUNCTION(function);
													temp 
														= 
														FUNCALL_5(temp,
														arg1,
														arg2,
														arg3,
														arg4,
														arg5);
												    }
												    else if (EQ(arg7,
													    No_arg))
													temp 
														= 
														funcall(7,
														SYMBOL_FUNCTION(function),
														arg1,
														arg2,
														arg3,
														arg4,
														arg5,
														arg6);
												    else if (EQ(arg8,
													    No_arg))
													temp 
														= 
														funcall(8,
														SYMBOL_FUNCTION(function),
														arg1,
														arg2,
														arg3,
														arg4,
														arg5,
														arg6,
														arg7);
												    else if (EQ(arg9,
													    No_arg))
													temp 
														= 
														funcall(9,
														SYMBOL_FUNCTION(function),
														arg1,
														arg2,
														arg3,
														arg4,
														arg5,
														arg6,
														arg7,
														arg8);
												    else if (EQ(arg10,
													    No_arg))
													temp 
														= 
														funcall(10,
														SYMBOL_FUNCTION(function),
														arg1,
														arg2,
														arg3,
														arg4,
														arg5,
														arg6,
														arg7,
														arg8,
														arg9);
												    else if (EQ(arg11,
													    No_arg))
													temp 
														= 
														funcall(11,
														SYMBOL_FUNCTION(function),
														arg1,
														arg2,
														arg3,
														arg4,
														arg5,
														arg6,
														arg7,
														arg8,
														arg9,
														arg10);
												    else
													temp 
														= 
														funcall(12,
														SYMBOL_FUNCTION(function),
														arg1,
														arg2,
														arg3,
														arg4,
														arg5,
														arg6,
														arg7,
														arg8,
														arg9,
														arg10,
														arg11);
												    if (Flush_graphics_immediately_qm 
													    && 
													    FIXNUM_NE(ISVREF(Current_icp_socket,
													    (SI_Long)15L),
													    Icp_connection_closed))
													sync_graphics_on_current_window();
												    end_icp_message_group();
												}
												else
												    temp 
													    = 
													    Nil;
												SAVE_VALUES(VALUES_1(temp));
												if (Profiling_enabled_qm) 
													    {
												    gensymed_symbol_3 
													    = 
													    g2ext_unix_time_as_float();
												    gensymed_symbol_4 
													    = 
													    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
													    (SI_Long)2L),
													    (SI_Long)0L);
												    gensymed_symbol_5 
													    = 
													    gensymed_symbol_3 
													    - 
													    gensymed_symbol_4;
												    aref_arg_1 
													    = 
													    ISVREF(Profiling_enabled_qm,
													    (SI_Long)6L);
												    aref_new_value 
													    = 
													    gensymed_symbol_5 
													    + 
													    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
													    (SI_Long)6L),
													    (SI_Long)0L);
												    DFLOAT_ISASET_1(aref_arg_1,
													    (SI_Long)0L,
													    aref_new_value);
												    aref_arg_1 
													    = 
													    ISVREF(Profiling_enabled_qm,
													    (SI_Long)2L);
												    aref_new_value 
													    = 
													    gensymed_symbol 
													    ?
													     
													    gensymed_symbol_1 
													    + 
													    gensymed_symbol_5 
													    + 
													    (gensymed_symbol_4 
													    - 
													    gensymed_symbol_2) 
													    :
													     
													    gensymed_symbol_3;
												    DFLOAT_ISASET_1(aref_arg_1,
													    (SI_Long)0L,
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
								    }
								    else
									SAVE_VALUES(VALUES_1(Nil));
								}
								else
								    SAVE_VALUES(VALUES_1(Nil));
							    }
							    else if (EQ(Type_of_current_window,
								    Qprinter)) 
									{
								if (EQ(arg1,
									No_arg))
								    SAVE_VALUES(FUNCALL_0(SYMBOL_FUNCTION(function)));
								else if (EQ(arg2,
									No_arg)) 
									    {
								    temp = 
									    SYMBOL_FUNCTION(function);
								    SAVE_VALUES(FUNCALL_1(temp,
									    arg1));
								}
								else if (EQ(arg3,
									No_arg)) 
									    {
								    temp = 
									    SYMBOL_FUNCTION(function);
								    SAVE_VALUES(FUNCALL_2(temp,
									    arg1,
									    arg2));
								}
								else if (EQ(arg4,
									No_arg)) 
									    {
								    temp = 
									    SYMBOL_FUNCTION(function);
								    SAVE_VALUES(FUNCALL_3(temp,
									    arg1,
									    arg2,
									    arg3));
								}
								else if (EQ(arg5,
									No_arg)) 
									    {
								    temp = 
									    SYMBOL_FUNCTION(function);
								    SAVE_VALUES(FUNCALL_4(temp,
									    arg1,
									    arg2,
									    arg3,
									    arg4));
								}
								else if (EQ(arg6,
									No_arg)) 
									    {
								    temp = 
									    SYMBOL_FUNCTION(function);
								    SAVE_VALUES(FUNCALL_5(temp,
									    arg1,
									    arg2,
									    arg3,
									    arg4,
									    arg5));
								}
								else if (EQ(arg7,
									No_arg))
								    SAVE_VALUES(funcall(7,
									    SYMBOL_FUNCTION(function),
									    arg1,
									    arg2,
									    arg3,
									    arg4,
									    arg5,
									    arg6));
								else if (EQ(arg8,
									No_arg))
								    SAVE_VALUES(funcall(8,
									    SYMBOL_FUNCTION(function),
									    arg1,
									    arg2,
									    arg3,
									    arg4,
									    arg5,
									    arg6,
									    arg7));
								else if (EQ(arg9,
									No_arg))
								    SAVE_VALUES(funcall(9,
									    SYMBOL_FUNCTION(function),
									    arg1,
									    arg2,
									    arg3,
									    arg4,
									    arg5,
									    arg6,
									    arg7,
									    arg8));
								else if (EQ(arg10,
									No_arg))
								    SAVE_VALUES(funcall(10,
									    SYMBOL_FUNCTION(function),
									    arg1,
									    arg2,
									    arg3,
									    arg4,
									    arg5,
									    arg6,
									    arg7,
									    arg8,
									    arg9));
								else if (EQ(arg11,
									No_arg))
								    SAVE_VALUES(funcall(11,
									    SYMBOL_FUNCTION(function),
									    arg1,
									    arg2,
									    arg3,
									    arg4,
									    arg5,
									    arg6,
									    arg7,
									    arg8,
									    arg9,
									    arg10));
								else
								    SAVE_VALUES(funcall(12,
									    SYMBOL_FUNCTION(function),
									    arg1,
									    arg2,
									    arg3,
									    arg4,
									    arg5,
									    arg6,
									    arg7,
									    arg8,
									    arg9,
									    arg10,
									    arg11));
							    }
							    else
								SAVE_VALUES(VALUES_1(Qnil));
							  POP_SPECIAL();
						      }
						      POP_UNWIND_PROTECT(0);
						      UNLOCK(On_window_with_drawing);
						      CONTINUE_UNWINDING(0);
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
				POP_UNWIND_PROTECT(1);
				UNLOCK(On_window_without_drawing);
				CONTINUE_UNWINDING(1);
				result = RESTORE_VALUES();
			    }
			    else
				result = VALUES_1(Nil);
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
    RESTORE_STACK();
    return result;
}

/* MAKE-WINDOW-VISIBLE */
Object make_window_visible(gensym_window)
    Object gensym_window;
{
    Object temp;

    x_note_fn_call(55,186);
    temp = ISVREF(gensym_window,(SI_Long)1L);
    if (EQ(temp,Qicp) || EQ(temp,Qprinter));
    else if (EQ(temp,Qx11_window))
	g2ext_x11_make_xwindow_visible(IFIX(ISVREF(gensym_window,
		(SI_Long)17L)));
    else if (ISVREF(gensym_window,(SI_Long)17L))
	enqueue_window_reshape_event(3,ISVREF(gensym_window,(SI_Long)17L),
		FIX((SI_Long)0L),FIX((SI_Long)784L));
    return VALUES_1(Nil);
}

/* UPDATE-INDEXED-MD5-CONTEXT */
Object update_indexed_md5_context(index_1,data_string)
    Object index_1, data_string;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(55,187);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(data_string);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = data_string;
    g2ext_update_g2_MD5_context(IFIX(index_1),ISTRING(temp));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(Nil);
}

/* FINALIZE-INDEXED-MD5-CONTEXT */
Object finalize_indexed_md5_context(index_1,result_string)
    Object index_1, result_string;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(55,188);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(result_string);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = result_string;
    g2ext_finalize_g2_MD5_context(IFIX(index_1),ISTRING(temp));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(Nil);
}

void windows1_INIT()
{
    Object temp, reclaim_structure_for_gensym_window_1;
    Object named_dynamic_extent_description, temp_1, cdddr_new_value;
    Object reclaim_structure_for_identified_drawing_activity_1;
    Object reclaim_structure_for_color_map_1;
    Object reclaim_structure_for_tiled_raster_1;
    Object reclaim_structure_for_pixmap_1;
    Object Qwindows1, AB_package, Qpixmap, Qreclaim_structure;
    Object Qoutstanding_pixmap_count, Qpixmap_structure_memory_usage;
    Object Qutilities2, string_constant_23, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_22, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qtiled_raster;
    Object Qoutstanding_tiled_raster_count;
    Object Qtiled_raster_structure_memory_usage, string_constant_21;
    Object string_constant_20;
    Object Qhandler_for_printing_initialize_scratchpad_raster;
    Object Qnamed_dynamic_extent_description, string_constant_19;
    Object Qhandler_for_printing_set_up_palette, Qequivalent_icp_value_type;
    Object Qboolean, Qsubtract_instead_qm, Qunsigned_integer_qm;
    Object Qcolor_difference_qm, Qunsigned_integer, Qcolor_difference;
    Object Qcolor_value_qm, Qcolor_value, Qoutstanding_color_map_count;
    Object Qcolor_map_structure_memory_usage, string_constant_18;
    Object string_constant_17, list_constant_14;
    Object Qcompute_standard_gensym_colors, Kfuncall, list_constant_13;
    Object list_constant_12, list_constant_11, list_constant_10;
    Object list_constant_9, Qhandler_for_printing_ping_drawing;
    Object Qidentified_drawing_activity;
    Object Qoutstanding_identified_drawing_activity_count;
    Object Qidentified_drawing_activity_structure_memory_usage;
    Object string_constant_16, string_constant_15;
    Object Qhandler_for_printing_force_graphics_on_window;
    Object Qreclaim_icp_port_entry_for_gensym_window, list_constant_8;
    Object Qcorresponding_icp_object_map_for_window;
    Object Qrequest_to_move_native_window, Qrequest_to_move_window;
    Object Qset_background_color_value, Qset_transfer_mode;
    Object Qrequest_to_close_telewindows_connection, Qshift_position_of_mouse;
    Object Qrequest_to_reshape_native_window, Qrequest_to_reshape_window;
    Object Qrequest_to_refresh_window, Qset_window_protocol_version;
    Object Qset_position_of_mouse, Qdefine_telewindows_workstation;
    Object Qcoordinate, list_constant_7, Qexcluded_dynamic_superiors;
    Object list_constant_6, string_constant_14, Kdraw_as_late_as_possible;
    Object string_constant_13, Qoutstanding_gensym_window_count;
    Object Qgensym_window_structure_memory_usage, string_constant_12;
    Object string_constant_11, Qstandard_colors, list_constant_5;
    Object list_constant_4, Qinitialize_v5_mode, list_constant_3;
    Object string_constant_10, Qgraphics_cons_memory_usage;
    Object Qoutstanding_graphics_conses, list_constant_2;
    Object Qgraphics_cons_counter_vector, Qmake_thread_array, list_constant_1;
    Object Qavailable_graphics_conses_tail_vector;
    Object Qavailable_graphics_conses_vector;

    x_note_fn_call(55,189);
    SET_PACKAGE("AB");
    if (Defer_notifications_qm == UNBOUND)
	Defer_notifications_qm = Nil;
    AB_package = STATIC_PACKAGE("AB");
    Qavailable_graphics_conses = STATIC_SYMBOL("AVAILABLE-GRAPHICS-CONSES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_graphics_conses,
	    Available_graphics_conses);
    Qwindows1 = STATIC_SYMBOL("WINDOWS1",AB_package);
    record_system_variable(Qavailable_graphics_conses,Qwindows1,Nil,Qnil,
	    Qt,Qnil,Qnil);
    Qavailable_graphics_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-GRAPHICS-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_graphics_conses_tail,
	    Available_graphics_conses_tail);
    record_system_variable(Qavailable_graphics_conses_tail,Qwindows1,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_graphics_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-GRAPHICS-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_graphics_conses_vector,
	    Available_graphics_conses_vector);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_thread_array = STATIC_SYMBOL("MAKE-THREAD-ARRAY",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    Qnil);
    record_system_variable(Qavailable_graphics_conses_vector,Qwindows1,
	    list_constant_1,Qnil,Qt,Qnil,Qnil);
    Qavailable_graphics_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-GRAPHICS-CONSES-TAIL-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_graphics_conses_tail_vector,
	    Available_graphics_conses_tail_vector);
    record_system_variable(Qavailable_graphics_conses_tail_vector,
	    Qwindows1,list_constant_1,Qnil,Qt,Qnil,Qnil);
    Qgraphics_cons_counter_vector = 
	    STATIC_SYMBOL("GRAPHICS-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgraphics_cons_counter_vector,
	    Graphics_cons_counter_vector);
    list_constant_2 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    FIX((SI_Long)0L));
    record_system_variable(Qgraphics_cons_counter_vector,Qwindows1,
	    list_constant_2,Qnil,Qt,Qnil,Qnil);
    Qgraphics_cons_counter = STATIC_SYMBOL("GRAPHICS-CONS-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgraphics_cons_counter,Graphics_cons_counter);
    record_system_variable(Qgraphics_cons_counter,Qwindows1,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_graphics_conses = 
	    STATIC_SYMBOL("OUTSTANDING-GRAPHICS-CONSES",AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_graphics_conses,
	    STATIC_FUNCTION(outstanding_graphics_conses,NIL,FALSE,0,0));
    Qgraphics_cons_memory_usage = 
	    STATIC_SYMBOL("GRAPHICS-CONS-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qgraphics_cons_memory_usage,
	    STATIC_FUNCTION(graphics_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_10 = STATIC_STRING("1q83-XCy9k83-XBy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_graphics_conses);
    push_optimized_constant(Qgraphics_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_10));
    Qgraphics = STATIC_SYMBOL("GRAPHICS",AB_package);
    Qg2_has_v5_mode_windows_p = STATIC_SYMBOL("G2-HAS-V5-MODE-WINDOWS-P",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2_has_v5_mode_windows_p,
	    G2_has_v5_mode_windows_p);
    Qinitialize_v5_mode = STATIC_SYMBOL("INITIALIZE-V5-MODE",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Kfuncall,Qinitialize_v5_mode);
    record_system_variable(Qg2_has_v5_mode_windows_p,Qwindows1,
	    list_constant_3,Qnil,Qnil,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qinitialize_v5_mode,
	    STATIC_FUNCTION(initialize_v5_mode,NIL,FALSE,0,0));
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)57344L);
    if (Trace_image_planes_p == UNBOUND)
	Trace_image_planes_p = Nil;
    list_constant_5 = STATIC_LIST((SI_Long)14L,FIX((SI_Long)4L),
	    FIX((SI_Long)8L),FIX((SI_Long)12L),FIX((SI_Long)16L),
	    FIX((SI_Long)24L),FIX((SI_Long)32L),FIX((SI_Long)56L),
	    FIX((SI_Long)64L),FIX((SI_Long)104L),FIX((SI_Long)128L),
	    FIX((SI_Long)152L),FIX((SI_Long)200L),FIX((SI_Long)256L),
	    FIX((SI_Long)400L));
    List_of_regular_raster_sizes = list_constant_5;
    List_of_regular_raster_memory_usage = 
	    convert_raster_sizes_to_memory_used(List_of_regular_raster_sizes);
    Number_of_regular_raster_sizes = length(List_of_regular_raster_sizes);
    temp = last(List_of_regular_raster_sizes,_);
    Largest_regular_raster_size = CAR(temp);
    Largest_regular_raster_size_index = 
	    FIXNUM_SUB1(length(List_of_regular_raster_sizes));
    Deepest_depth = FIX((SI_Long)32L);
    Minimum_tile_size_for_icons = FIX((SI_Long)32L);
    Minimum_index_for_icons = position(2,Minimum_tile_size_for_icons,
	    List_of_regular_raster_sizes);
    Qdefault_maximum_icon_bitmaps = 
	    STATIC_SYMBOL("DEFAULT-MAXIMUM-ICON-BITMAPS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefault_maximum_icon_bitmaps,
	    Default_maximum_icon_bitmaps);
    record_system_variable(Qdefault_maximum_icon_bitmaps,Qwindows1,
	    FIX((SI_Long)1000L),Qnil,Qnil,Qnil,Qnil);
    Qdefault_maximum_icon_bitmap_memory = 
	    STATIC_SYMBOL("DEFAULT-MAXIMUM-ICON-BITMAP-MEMORY",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefault_maximum_icon_bitmap_memory,
	    Default_maximum_icon_bitmap_memory);
    record_system_variable(Qdefault_maximum_icon_bitmap_memory,Qwindows1,
	    FIX((SI_Long)2000000L),Qnil,Qnil,Qnil,Qnil);
    Qstandard_colors = STATIC_SYMBOL("STANDARD-COLORS",AB_package);
    Default_image_palette = Qstandard_colors;
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_gensym_window_g2_struct = 
	    STATIC_SYMBOL("GENSYM-WINDOW-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qgensym_window = STATIC_SYMBOL("GENSYM-WINDOW",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_gensym_window_g2_struct,
	    Qgensym_window,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qgensym_window,
	    Qg2_defstruct_structure_name_gensym_window_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_gensym_window == UNBOUND)
	The_type_description_of_gensym_window = Nil;
    string_constant_11 = 
	    STATIC_STRING("43Dy8m83hxy1n83hxy8n8k1l8n0000001m1m83My83-AKy1n8y83-4=y1l83-7Eyk3-2yk0k0");
    temp = The_type_description_of_gensym_window;
    The_type_description_of_gensym_window = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_11));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_gensym_window_g2_struct,
	    The_type_description_of_gensym_window,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qgensym_window,
	    The_type_description_of_gensym_window,Qtype_description_of_type);
    Qoutstanding_gensym_window_count = 
	    STATIC_SYMBOL("OUTSTANDING-GENSYM-WINDOW-COUNT",AB_package);
    Qgensym_window_structure_memory_usage = 
	    STATIC_SYMBOL("GENSYM-WINDOW-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_12 = STATIC_STRING("1q83hxy8s83-WKy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_gensym_window_count);
    push_optimized_constant(Qgensym_window_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_12));
    Qchain_of_available_gensym_windows = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-GENSYM-WINDOWS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_gensym_windows,
	    Chain_of_available_gensym_windows);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_gensym_windows,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qgensym_window_count = STATIC_SYMBOL("GENSYM-WINDOW-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgensym_window_count,Gensym_window_count);
    record_system_variable(Qgensym_window_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_gensym_windows_vector == UNBOUND)
	Chain_of_available_gensym_windows_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qgensym_window_structure_memory_usage,
	    STATIC_FUNCTION(gensym_window_structure_memory_usage,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_gensym_window_count,
	    STATIC_FUNCTION(outstanding_gensym_window_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_gensym_window_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_gensym_window,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qgensym_window,
	    reclaim_structure_for_gensym_window_1);
    Qnative = STATIC_SYMBOL("NATIVE",AB_package);
    Kxor = STATIC_SYMBOL("XOR",Pkeyword);
    Qunknown = STATIC_SYMBOL("UNKNOWN",AB_package);
    Qcurrent_gensym_window_serial_number = 
	    STATIC_SYMBOL("CURRENT-GENSYM-WINDOW-SERIAL-NUMBER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_gensym_window_serial_number,
	    Current_gensym_window_serial_number);
    record_system_variable(Qcurrent_gensym_window_serial_number,Qwindows1,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qno_native_clipboard = STATIC_SYMBOL("NO-NATIVE-CLIPBOARD",AB_package);
    Qtelewindows = STATIC_SYMBOL("TELEWINDOWS",AB_package);
    list_constant = STATIC_CONS(Qtelewindows,Qnil);
    Qprinter = STATIC_SYMBOL("PRINTER",AB_package);
    if (X_debugging_on == UNBOUND)
	X_debugging_on = Nil;
    Qnetwork_host_name = STATIC_SYMBOL("NETWORK-HOST-NAME",AB_package);
    Qos_type = STATIC_SYMBOL("OS-TYPE",AB_package);
    string_constant_13 = STATIC_STRING("ON-WINDOW-WITHOUT-DRAWING");
    if (On_window_without_drawing == UNBOUND)
	On_window_without_drawing = make_recursive_lock(2,Kname,
		string_constant_13);
    Qon_window_without_drawing = STATIC_SYMBOL("ON-WINDOW-WITHOUT-DRAWING",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qon_window_without_drawing,
	    On_window_without_drawing);
    Qnamed_dynamic_extent_description = 
	    STATIC_SYMBOL("NAMED-DYNAMIC-EXTENT-DESCRIPTION",AB_package);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qon_window_without_drawing,
	    Qwindows1,Nil,Qnil,Qnil,Qnil,Nil);
    mutate_global_property(Qon_window_without_drawing,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    Qcurrent_drawing_transfer_mode = 
	    STATIC_SYMBOL("CURRENT-DRAWING-TRANSFER-MODE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_drawing_transfer_mode,
	    Current_drawing_transfer_mode);
    Kpaint_infered_from_xor = STATIC_SYMBOL("PAINT-INFERED-FROM-XOR",Pkeyword);
    record_system_variable(Qcurrent_drawing_transfer_mode,Qwindows1,
	    Kpaint_infered_from_xor,Qnil,Qnil,Qnil,Qnil);
    Qcurrent_drawing_priority = STATIC_SYMBOL("CURRENT-DRAWING-PRIORITY",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_drawing_priority,
	    Current_drawing_priority);
    Kdraw_as_late_as_possible = STATIC_SYMBOL("DRAW-AS-LATE-AS-POSSIBLE",
	    Pkeyword);
    record_system_variable(Qcurrent_drawing_priority,Qwindows1,
	    Kdraw_as_late_as_possible,Qnil,Qnil,Qnil,Qnil);
    Qcurrent_draw_paper_p = STATIC_SYMBOL("CURRENT-DRAW-PAPER-P",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_draw_paper_p,Current_draw_paper_p);
    record_system_variable(Qcurrent_draw_paper_p,Qwindows1,T,Qnil,Qnil,
	    Qnil,Qnil);
    Qcurrent_draw_document_p = STATIC_SYMBOL("CURRENT-DRAW-DOCUMENT-P",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_draw_document_p,
	    Current_draw_document_p);
    record_system_variable(Qcurrent_draw_document_p,Qwindows1,T,Qnil,Qnil,
	    Qnil,Qnil);
    Qworkspace_for_current_draw_document_qm = 
	    STATIC_SYMBOL("WORKSPACE-FOR-CURRENT-DRAW-DOCUMENT\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qworkspace_for_current_draw_document_qm,
	    Workspace_for_current_draw_document_qm);
    record_system_variable(Qworkspace_for_current_draw_document_qm,
	    Qwindows1,Nil,Qnil,Qnil,Qnil,Qnil);
    if (Currently_jump_out_of_drawing_image_plane_when_empty_rectangle_p 
	    == UNBOUND)
	Currently_jump_out_of_drawing_image_plane_when_empty_rectangle_p = T;
    string_constant_14 = STATIC_STRING("ON-WINDOW-WITH-DRAWING");
    if (On_window_with_drawing == UNBOUND)
	On_window_with_drawing = make_recursive_lock(2,Kname,
		string_constant_14);
    Qon_window_with_drawing = STATIC_SYMBOL("ON-WINDOW-WITH-DRAWING",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qon_window_with_drawing,On_window_with_drawing);
    list_constant_6 = STATIC_CONS(Qon_window_without_drawing,Qnil);
    Qexcluded_dynamic_superiors = 
	    STATIC_SYMBOL("EXCLUDED-DYNAMIC-SUPERIORS",AB_package);
    list_constant_7 = STATIC_CONS(Qon_window_with_drawing,Qnil);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qon_window_with_drawing,
	    Qwindows1,Nil,list_constant_6,Qnil,Qnil,Nil);
    temp_1 = CDDDR(named_dynamic_extent_description);
    cdddr_new_value = set_getf(CDDDR(temp_1),Qexcluded_dynamic_superiors,
	    list_constant_7);
    M_CDDDR(temp_1) = cdddr_new_value;
    mutate_global_property(Qon_window_with_drawing,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    Qicp = STATIC_SYMBOL("ICP",AB_package);
    Qsystem_metrics = STATIC_SYMBOL("SYSTEM-METRICS",AB_package);
    Qcoordinate = STATIC_SYMBOL("COORDINATE",AB_package);
    Qequivalent_icp_value_type = STATIC_SYMBOL("EQUIVALENT-ICP-VALUE-TYPE",
	    AB_package);
    mutate_global_property(Qcoordinate,Qinteger,Qequivalent_icp_value_type);
    Qx = STATIC_SYMBOL("X",AB_package);
    Qy = STATIC_SYMBOL("Y",AB_package);
    Qdefine_telewindows_workstation = 
	    STATIC_SYMBOL("DEFINE-TELEWINDOWS-WORKSTATION",AB_package);
    add_icp_message_type_code(Qdefine_telewindows_workstation,
	    FIX((SI_Long)28L),Qnil);
    Qset_position_of_mouse = STATIC_SYMBOL("SET-POSITION-OF-MOUSE",AB_package);
    add_icp_message_type_code(Qset_position_of_mouse,FIX((SI_Long)29L),Qnil);
    Qset_window_protocol_version = 
	    STATIC_SYMBOL("SET-WINDOW-PROTOCOL-VERSION",AB_package);
    add_icp_message_type_code(Qset_window_protocol_version,
	    FIX((SI_Long)22L),Qnil);
    Qrequest_to_refresh_window = STATIC_SYMBOL("REQUEST-TO-REFRESH-WINDOW",
	    AB_package);
    add_icp_message_type_code(Qrequest_to_refresh_window,FIX((SI_Long)90L),
	    Qnil);
    Qrequest_to_reshape_window = STATIC_SYMBOL("REQUEST-TO-RESHAPE-WINDOW",
	    AB_package);
    add_icp_message_type_code(Qrequest_to_reshape_window,FIX((SI_Long)91L),
	    Qnil);
    Qrequest_to_reshape_native_window = 
	    STATIC_SYMBOL("REQUEST-TO-RESHAPE-NATIVE-WINDOW",AB_package);
    add_icp_message_type_code(Qrequest_to_reshape_native_window,
	    FIX((SI_Long)92L),Qnil);
    Qshift_position_of_mouse = STATIC_SYMBOL("SHIFT-POSITION-OF-MOUSE",
	    AB_package);
    add_icp_message_type_code(Qshift_position_of_mouse,FIX((SI_Long)94L),Qnil);
    Qrequest_to_close_telewindows_connection = 
	    STATIC_SYMBOL("REQUEST-TO-CLOSE-TELEWINDOWS-CONNECTION",
	    AB_package);
    add_icp_message_type_code(Qrequest_to_close_telewindows_connection,
	    FIX((SI_Long)95L),Qnil);
    Qset_transfer_mode = STATIC_SYMBOL("SET-TRANSFER-MODE",AB_package);
    add_icp_message_type_code(Qset_transfer_mode,FIX((SI_Long)96L),Qnil);
    Qset_background_color_value = 
	    STATIC_SYMBOL("SET-BACKGROUND-COLOR-VALUE",AB_package);
    add_icp_message_type_code(Qset_background_color_value,
	    FIX((SI_Long)97L),Qnil);
    Qrequest_to_move_window = STATIC_SYMBOL("REQUEST-TO-MOVE-WINDOW",
	    AB_package);
    add_icp_message_type_code(Qrequest_to_move_window,FIX((SI_Long)98L),Qnil);
    Qrequest_to_move_native_window = 
	    STATIC_SYMBOL("REQUEST-TO-MOVE-NATIVE-WINDOW",AB_package);
    add_icp_message_type_code(Qrequest_to_move_native_window,
	    FIX((SI_Long)99L),Qnil);
    Qstandard_icp_object_index_space = 
	    STATIC_SYMBOL("STANDARD-ICP-OBJECT-INDEX-SPACE",AB_package);
    Qestablish_new_object_index_for_gensym_window = 
	    STATIC_SYMBOL("ESTABLISH-NEW-OBJECT-INDEX-FOR-GENSYM-WINDOW",
	    AB_package);
    string_constant = 
	    STATIC_STRING("resumable icp synch error: ~S expected, ~S found");
    SET_SYMBOL_FUNCTION(Qestablish_new_object_index_for_gensym_window,
	    STATIC_FUNCTION(establish_new_object_index_for_gensym_window,
	    NIL,TRUE,2,3));
    Qtype_of_gensym_window = STATIC_SYMBOL("TYPE-OF-GENSYM-WINDOW",AB_package);
    Qscratchpad_raster_type_for_window = 
	    STATIC_SYMBOL("SCRATCHPAD-RASTER-TYPE-FOR-WINDOW",AB_package);
    Qstored_raster_type_for_window = 
	    STATIC_SYMBOL("STORED-RASTER-TYPE-FOR-WINDOW",AB_package);
    Qmake_corresponding_icp_gensym_window = 
	    STATIC_SYMBOL("MAKE-CORRESPONDING-ICP-GENSYM-WINDOW",AB_package);
    SET_SYMBOL_FUNCTION(Qmake_corresponding_icp_gensym_window,
	    STATIC_FUNCTION(make_corresponding_icp_gensym_window,NIL,FALSE,
	    1,1));
    Qset_access_form_for_gensym_window = 
	    STATIC_SYMBOL("SET-ACCESS-FORM-FOR-GENSYM-WINDOW",AB_package);
    SET_SYMBOL_FUNCTION(Qset_access_form_for_gensym_window,
	    STATIC_FUNCTION(set_access_form_for_gensym_window,NIL,FALSE,2,2));
    Qcorresponding_icp_object_map_for_window = 
	    STATIC_SYMBOL("CORRESPONDING-ICP-OBJECT-MAP-FOR-WINDOW",
	    AB_package);
    list_constant_8 = STATIC_LIST((SI_Long)2L,
	    Qcorresponding_icp_object_map_for_window,Qgensym_window);
    initialize_icp_object_type_compile(Qgensym_window,
	    Qstandard_icp_object_index_space,list_constant_8);
    Qreclaim_icp_port_entry_for_gensym_window = 
	    STATIC_SYMBOL("RECLAIM-ICP-PORT-ENTRY-FOR-GENSYM-WINDOW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_icp_port_entry_for_gensym_window,
	    STATIC_FUNCTION(reclaim_icp_port_entry_for_gensym_window,NIL,
	    FALSE,2,2));
    initialize_icp_object_type(Qgensym_window,Qnil,Qnil,
	    Qreclaim_icp_port_entry_for_gensym_window);
    Qsend_icp_define_gensym_window = 
	    STATIC_SYMBOL("SEND-ICP-DEFINE-GENSYM-WINDOW",AB_package);
    Qdefine_gensym_window = STATIC_SYMBOL("DEFINE-GENSYM-WINDOW",AB_package);
    string_constant_1 = STATIC_STRING("[message]");
    Qmessage = STATIC_SYMBOL("MESSAGE",AB_package);
    Qcorresponding_icp_object_index = 
	    STATIC_SYMBOL("CORRESPONDING-ICP-OBJECT-INDEX",AB_package);
    string_constant_2 = STATIC_STRING("[value arg]");
    Qargument = STATIC_SYMBOL("ARGUMENT",AB_package);
    Qleft_edge_in_window = STATIC_SYMBOL("LEFT-EDGE-IN-WINDOW",AB_package);
    Qtop_edge_in_window = STATIC_SYMBOL("TOP-EDGE-IN-WINDOW",AB_package);
    Qright_edge_in_window = STATIC_SYMBOL("RIGHT-EDGE-IN-WINDOW",AB_package);
    Qbottom_edge_in_window = STATIC_SYMBOL("BOTTOM-EDGE-IN-WINDOW",AB_package);
    Qwindow_parameters_plist = STATIC_SYMBOL("WINDOW-PARAMETERS-PLIST",
	    AB_package);
    Qcorresponding_icp_object_index_on_other_side_qm = 
	    STATIC_SYMBOL("CORRESPONDING-ICP-OBJECT-INDEX-ON-OTHER-SIDE\?",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_define_gensym_window,
	    STATIC_FUNCTION(send_icp_define_gensym_window,NIL,FALSE,7,7));
    Qicp_window_protocol_version = 
	    STATIC_SYMBOL("ICP-WINDOW-PROTOCOL-VERSION",AB_package);
    Qhandle_icp_define_gensym_window = 
	    STATIC_SYMBOL("HANDLE-ICP-DEFINE-GENSYM-WINDOW",AB_package);
    Qresumable_icp_list_end = STATIC_SYMBOL("RESUMABLE-ICP-LIST-END",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_define_gensym_window,
	    STATIC_FUNCTION(handle_icp_define_gensym_window,NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_define_gensym_window,
	    FIX((SI_Long)30L));
    Qflush_or_sync = STATIC_SYMBOL("FLUSH-OR-SYNC",AB_package);
    Qunsigned_integer = STATIC_SYMBOL("UNSIGNED-INTEGER",AB_package);
    mutate_global_property(Qflush_or_sync,Qunsigned_integer,
	    Qequivalent_icp_value_type);
    Qhandler_for_printing_force_graphics_on_window = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-FORCE-GRAPHICS-ON-WINDOW",
	    AB_package);
    temp_1 = Icp_printing_message_handler_array;
    set_aref1(temp_1,FIX((SI_Long)188L),
	    Qhandler_for_printing_force_graphics_on_window);
    Qforce_graphics_on_window = STATIC_SYMBOL("FORCE-GRAPHICS-ON-WINDOW",
	    AB_package);
    Qx11_window = STATIC_SYMBOL("X11-WINDOW",AB_package);
    SET_SYMBOL_FUNCTION(Qforce_graphics_on_window,
	    STATIC_FUNCTION(force_graphics_on_window,NIL,FALSE,1,1));
    string_constant_3 = STATIC_STRING("[msg funct]");
    Qhandle_icp_force_graphics_on_window = 
	    STATIC_SYMBOL("HANDLE-ICP-FORCE-GRAPHICS-ON-WINDOW",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_force_graphics_on_window,
	    STATIC_FUNCTION(handle_icp_force_graphics_on_window,NIL,FALSE,
	    0,0));
    add_icp_message_handler(Qhandle_icp_force_graphics_on_window,
	    FIX((SI_Long)188L));
    Qg2_defstruct_structure_name_identified_drawing_activity_g2_struct = 
	    STATIC_SYMBOL("IDENTIFIED-DRAWING-ACTIVITY-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qidentified_drawing_activity = 
	    STATIC_SYMBOL("IDENTIFIED-DRAWING-ACTIVITY",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_identified_drawing_activity_g2_struct,
	    Qidentified_drawing_activity,Qab_name_of_unique_structure_type);
    mutate_global_property(Qidentified_drawing_activity,
	    Qg2_defstruct_structure_name_identified_drawing_activity_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_identified_drawing_activity == UNBOUND)
	The_type_description_of_identified_drawing_activity = Nil;
    string_constant_15 = 
	    STATIC_STRING("43Dy8m83iny1o83iny83EJy8n8k1l83EJy0000001n1m8x83EJy1m83My83-Aay1n8y83-4Ty1q83-+xy83-=By83Xay83WEy83Iny83pkyktk0k0");
    temp = The_type_description_of_identified_drawing_activity;
    The_type_description_of_identified_drawing_activity = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_15));
    mutate_global_property(Qg2_defstruct_structure_name_identified_drawing_activity_g2_struct,
	    The_type_description_of_identified_drawing_activity,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qidentified_drawing_activity,
	    The_type_description_of_identified_drawing_activity,
	    Qtype_description_of_type);
    Qoutstanding_identified_drawing_activity_count = 
	    STATIC_SYMBOL("OUTSTANDING-IDENTIFIED-DRAWING-ACTIVITY-COUNT",
	    AB_package);
    Qidentified_drawing_activity_structure_memory_usage = 
	    STATIC_SYMBOL("IDENTIFIED-DRAWING-ACTIVITY-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_16 = STATIC_STRING("1q83iny8s83-Yvy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_identified_drawing_activity_count);
    push_optimized_constant(Qidentified_drawing_activity_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_16));
    Qchain_of_available_identified_drawing_activitys = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-IDENTIFIED-DRAWING-ACTIVITYS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_identified_drawing_activitys,
	    Chain_of_available_identified_drawing_activitys);
    record_system_variable(Qchain_of_available_identified_drawing_activitys,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qidentified_drawing_activity_count = 
	    STATIC_SYMBOL("IDENTIFIED-DRAWING-ACTIVITY-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qidentified_drawing_activity_count,
	    Identified_drawing_activity_count);
    record_system_variable(Qidentified_drawing_activity_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_identified_drawing_activitys_vector == UNBOUND)
	Chain_of_available_identified_drawing_activitys_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qidentified_drawing_activity_structure_memory_usage,
	    STATIC_FUNCTION(identified_drawing_activity_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_identified_drawing_activity_count,
	    STATIC_FUNCTION(outstanding_identified_drawing_activity_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_identified_drawing_activity_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_identified_drawing_activity,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qidentified_drawing_activity,
	    reclaim_structure_for_identified_drawing_activity_1);
    Qcontinue_after_drawing = STATIC_SYMBOL("CONTINUE-AFTER-DRAWING",
	    AB_package);
    Kfinished = STATIC_SYMBOL("FINISHED",Pkeyword);
    Kcanceled = STATIC_SYMBOL("CANCELED",Pkeyword);
    Qid_of_identified_drawing_activity = 
	    STATIC_SYMBOL("ID-OF-IDENTIFIED-DRAWING-ACTIVITY",AB_package);
    mutate_global_property(Qid_of_identified_drawing_activity,
	    Qunsigned_integer,Qequivalent_icp_value_type);
    Qhandler_for_printing_ping_drawing = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-PING-DRAWING",AB_package);
    temp_1 = Icp_printing_message_handler_array;
    set_aref1(temp_1,FIX((SI_Long)189L),Qhandler_for_printing_ping_drawing);
    Qping_drawing = STATIC_SYMBOL("PING-DRAWING",AB_package);
    SET_SYMBOL_FUNCTION(Qping_drawing,STATIC_FUNCTION(ping_drawing,NIL,
	    FALSE,1,1));
    Qhandle_icp_ping_drawing = STATIC_SYMBOL("HANDLE-ICP-PING-DRAWING",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_ping_drawing,
	    STATIC_FUNCTION(handle_icp_ping_drawing,NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_ping_drawing,FIX((SI_Long)189L));
    Qsend_icp_ping_drawing_reply = 
	    STATIC_SYMBOL("SEND-ICP-PING-DRAWING-REPLY",AB_package);
    Qping_drawing_reply = STATIC_SYMBOL("PING-DRAWING-REPLY",AB_package);
    string_constant_4 = STATIC_STRING("[object arg]");
    SET_SYMBOL_FUNCTION(Qsend_icp_ping_drawing_reply,
	    STATIC_FUNCTION(send_icp_ping_drawing_reply,NIL,FALSE,2,2));
    Qhandle_icp_ping_drawing_reply = 
	    STATIC_SYMBOL("HANDLE-ICP-PING-DRAWING-REPLY",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_ping_drawing_reply,
	    STATIC_FUNCTION(handle_icp_ping_drawing_reply,NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_ping_drawing_reply,FIX((SI_Long)190L));
    if (Flush_graphics_immediately_qm == UNBOUND)
	Flush_graphics_immediately_qm = Nil;
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Qdrawing_on_window = STATIC_SYMBOL("DRAWING-ON-WINDOW",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdrawing_on_window,Drawing_on_window);
    Qcolor_value_vector_index_and_intensity = 
	    STATIC_SYMBOL("COLOR-VALUE-VECTOR-INDEX-AND-INTENSITY",AB_package);
    Color_value_vector_index_and_intensity_prop = 
	    Qcolor_value_vector_index_and_intensity;
    Qnew_pastel_color_qm = STATIC_SYMBOL("NEW-PASTEL-COLOR\?",AB_package);
    New_pastel_color_qm_prop = Qnew_pastel_color_qm;
    derive_standard_gensym_color_data();
    Qintensity = STATIC_SYMBOL("INTENSITY",AB_package);
    Qalphabetic = STATIC_SYMBOL("ALPHABETIC",AB_package);
    Qhue = STATIC_SYMBOL("HUE",AB_package);
    Qhue_less_p = STATIC_SYMBOL("HUE-LESS-P",AB_package);
    SET_SYMBOL_FUNCTION(Qhue_less_p,STATIC_FUNCTION(hue_less_p,NIL,FALSE,2,2));
    Qtransparent = STATIC_SYMBOL("TRANSPARENT",AB_package);
    Qforeground = STATIC_SYMBOL("FOREGROUND",AB_package);
    list_constant_9 = STATIC_LIST((SI_Long)2L,Qtransparent,Qforeground);
    All_metacolors = list_constant_9;
    Qall_colors = STATIC_SYMBOL("ALL-COLORS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qall_colors,All_colors);
    Qcompute_standard_gensym_colors = 
	    STATIC_SYMBOL("COMPUTE-STANDARD-GENSYM-COLORS",AB_package);
    SET_SYMBOL_FUNCTION(Qcompute_standard_gensym_colors,
	    STATIC_FUNCTION(compute_standard_gensym_colors,NIL,TRUE,1,2));
    list_constant_10 = STATIC_CONS(Qnil,Qnil);
    list_constant_11 = STATIC_LIST_STAR((SI_Long)3L,Kfuncall,
	    Qcompute_standard_gensym_colors,list_constant_10);
    record_system_variable(Qall_colors,Qwindows1,list_constant_11,Qnil,
	    Qnil,Qnil,Qnil);
    Qmenu_colors = STATIC_SYMBOL("MENU-COLORS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmenu_colors,Menu_colors);
    list_constant_12 = STATIC_LIST((SI_Long)3L,Kfuncall,
	    Qcompute_standard_gensym_colors,Qt);
    record_system_variable(Qmenu_colors,Qwindows1,list_constant_12,Qnil,
	    Qnil,Qnil,Qnil);
    Qmenu_colors_sorted_alphabetically = 
	    STATIC_SYMBOL("MENU-COLORS-SORTED-ALPHABETICALLY",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmenu_colors_sorted_alphabetically,
	    Menu_colors_sorted_alphabetically);
    list_constant_13 = STATIC_LIST((SI_Long)4L,Kfuncall,
	    Qcompute_standard_gensym_colors,Qt,Qalphabetic);
    record_system_variable(Qmenu_colors_sorted_alphabetically,Qwindows1,
	    list_constant_13,Qnil,Qnil,Qnil,Qnil);
    Qmenu_colors_sorted_by_hue = STATIC_SYMBOL("MENU-COLORS-SORTED-BY-HUE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmenu_colors_sorted_by_hue,
	    Menu_colors_sorted_by_hue);
    list_constant_14 = STATIC_LIST((SI_Long)4L,Kfuncall,
	    Qcompute_standard_gensym_colors,Qt,Qhue);
    record_system_variable(Qmenu_colors_sorted_by_hue,Qwindows1,
	    list_constant_14,Qnil,Qnil,Qnil,Qnil);
    Qg2_defstruct_structure_name_color_map_g2_struct = 
	    STATIC_SYMBOL("COLOR-MAP-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qcolor_map = STATIC_SYMBOL("COLOR-MAP",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_color_map_g2_struct,
	    Qcolor_map,Qab_name_of_unique_structure_type);
    mutate_global_property(Qcolor_map,
	    Qg2_defstruct_structure_name_color_map_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_color_map == UNBOUND)
	The_type_description_of_color_map = Nil;
    string_constant_17 = 
	    STATIC_STRING("43Dy8m83g=y1n83g=y8n8k1l8n0000001l1n8y83-3Dy1p83sFy83sIy83sJy83sGy83sHyksk0k0");
    temp = The_type_description_of_color_map;
    The_type_description_of_color_map = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_17));
    mutate_global_property(Qg2_defstruct_structure_name_color_map_g2_struct,
	    The_type_description_of_color_map,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qcolor_map,The_type_description_of_color_map,
	    Qtype_description_of_type);
    Qoutstanding_color_map_count = 
	    STATIC_SYMBOL("OUTSTANDING-COLOR-MAP-COUNT",AB_package);
    Qcolor_map_structure_memory_usage = 
	    STATIC_SYMBOL("COLOR-MAP-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_18 = STATIC_STRING("1q83g=y8s83-N6y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_color_map_count);
    push_optimized_constant(Qcolor_map_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_18));
    Qchain_of_available_color_maps = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-COLOR-MAPS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_color_maps,
	    Chain_of_available_color_maps);
    record_system_variable(Qchain_of_available_color_maps,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qcolor_map_count = STATIC_SYMBOL("COLOR-MAP-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcolor_map_count,Color_map_count);
    record_system_variable(Qcolor_map_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_color_maps_vector == UNBOUND)
	Chain_of_available_color_maps_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qcolor_map_structure_memory_usage,
	    STATIC_FUNCTION(color_map_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_color_map_count,
	    STATIC_FUNCTION(outstanding_color_map_count,NIL,FALSE,0,0));
    reclaim_structure_for_color_map_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_color_map,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qcolor_map,
	    reclaim_structure_for_color_map_1);
    Qblack = STATIC_SYMBOL("BLACK",AB_package);
    Qwhite = STATIC_SYMBOL("WHITE",AB_package);
    Qrgb_color_value_cache = STATIC_SYMBOL("RGB-COLOR-VALUE-CACHE",AB_package);
    Rgb_color_value_cache_prop = Qrgb_color_value_cache;
    Qrgb_color_intensity_cache = STATIC_SYMBOL("RGB-COLOR-INTENSITY-CACHE",
	    AB_package);
    Rgb_color_intensity_cache_prop = Qrgb_color_intensity_cache;
    Qrgb_color_nearest_standard_color_cache = 
	    STATIC_SYMBOL("RGB-COLOR-NEAREST-STANDARD-COLOR-CACHE",AB_package);
    Rgb_color_nearest_standard_color_cache_prop = 
	    Qrgb_color_nearest_standard_color_cache;
    Qbackground = STATIC_SYMBOL("BACKGROUND",AB_package);
    Qcolor_value = STATIC_SYMBOL("COLOR-VALUE",AB_package);
    mutate_global_property(Qcolor_value,Qunsigned_integer,
	    Qequivalent_icp_value_type);
    Qcolor_value_qm = STATIC_SYMBOL("COLOR-VALUE\?",AB_package);
    Qunsigned_integer_qm = STATIC_SYMBOL("UNSIGNED-INTEGER\?",AB_package);
    mutate_global_property(Qcolor_value_qm,Qunsigned_integer_qm,
	    Qequivalent_icp_value_type);
    Qcolor_difference = STATIC_SYMBOL("COLOR-DIFFERENCE",AB_package);
    mutate_global_property(Qcolor_difference,Qunsigned_integer,
	    Qequivalent_icp_value_type);
    Qcolor_difference_qm = STATIC_SYMBOL("COLOR-DIFFERENCE\?",AB_package);
    mutate_global_property(Qcolor_difference_qm,Qunsigned_integer_qm,
	    Qequivalent_icp_value_type);
    Qsubtract_instead_qm = STATIC_SYMBOL("SUBTRACT-INSTEAD\?",AB_package);
    Qboolean = STATIC_SYMBOL("BOOLEAN",AB_package);
    mutate_global_property(Qsubtract_instead_qm,Qboolean,
	    Qequivalent_icp_value_type);
    string_constant_5 = STATIC_STRING("[value]");
    Qvalue = STATIC_SYMBOL("VALUE",AB_package);
    Qread_icp_color_map_using_function = 
	    STATIC_SYMBOL("READ-ICP-COLOR-MAP-USING-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qread_icp_color_map_using_function,
	    STATIC_FUNCTION(read_icp_color_map_using_function,NIL,FALSE,0,0));
    Qwrite_icp_color_map_using_function = 
	    STATIC_SYMBOL("WRITE-ICP-COLOR-MAP-USING-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_icp_color_map_using_function,
	    STATIC_FUNCTION(write_icp_color_map_using_function,NIL,FALSE,1,1));
    Qhandler_for_printing_set_up_palette = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-SET-UP-PALETTE",AB_package);
    temp_1 = Icp_printing_message_handler_array;
    set_aref1(temp_1,FIX((SI_Long)23L),Qhandler_for_printing_set_up_palette);
    Qset_up_palette = STATIC_SYMBOL("SET-UP-PALETTE",AB_package);
    SET_SYMBOL_FUNCTION(Qset_up_palette,STATIC_FUNCTION(set_up_palette,NIL,
	    FALSE,2,2));
    Qhandle_icp_set_up_palette = STATIC_SYMBOL("HANDLE-ICP-SET-UP-PALETTE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_set_up_palette,
	    STATIC_FUNCTION(handle_icp_set_up_palette,NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_set_up_palette,FIX((SI_Long)23L));
    Qinitialize_gensym_window_after_connection_done = 
	    STATIC_SYMBOL("INITIALIZE-GENSYM-WINDOW-AFTER-CONNECTION-DONE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qinitialize_gensym_window_after_connection_done,
	    Initialize_gensym_window_after_connection_done);
    record_system_variable(Qinitialize_gensym_window_after_connection_done,
	    Qwindows1,Nil,Qnil,Qnil,Qnil,Qnil);
    Qxclip = STATIC_SYMBOL("XCLIP",AB_package);
    Qtelewindows_connection_license_level = 
	    STATIC_SYMBOL("TELEWINDOWS-CONNECTION-LICENSE-LEVEL",AB_package);
    Qg2_license_level = STATIC_SYMBOL("G2-LICENSE-LEVEL",AB_package);
    Qg2_authorized_optional_modules = 
	    STATIC_SYMBOL("G2-AUTHORIZED-OPTIONAL-MODULES",AB_package);
    Qent = STATIC_SYMBOL("ENT",AB_package);
    Qal = STATIC_SYMBOL("AL",AB_package);
    Qjp = STATIC_SYMBOL("JP",AB_package);
    Qjl = STATIC_SYMBOL("JL",AB_package);
    Qg1 = STATIC_SYMBOL("G1",AB_package);
    Qkorean = STATIC_SYMBOL("KOREAN",AB_package);
    Qnupec = STATIC_SYMBOL("NUPEC",AB_package);
    Qjapanese = STATIC_SYMBOL("JAPANESE",AB_package);
    Qchinese = STATIC_SYMBOL("CHINESE",AB_package);
    Qgfi = STATIC_SYMBOL("GFI",AB_package);
    Qgsi = STATIC_SYMBOL("GSI",AB_package);
    string_constant_19 = STATIC_STRING("SCRATCHPAD-RASTER");
    if (Scratchpad_raster == UNBOUND)
	Scratchpad_raster = make_recursive_lock(2,Kname,string_constant_19);
    Qscratchpad_raster = STATIC_SYMBOL("SCRATCHPAD-RASTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qscratchpad_raster,Scratchpad_raster);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qscratchpad_raster,
	    Qwindows1,Nil,Qnil,Qnil,Qnil,Nil);
    mutate_global_property(Qscratchpad_raster,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    string_constant_6 = 
	    STATIC_STRING("~%Unable to allocate a ~dx~d pixmap! Will retry ....~%");
    string_constant_7 = 
	    STATIC_STRING("~%Still unable to allocate a ~dx~d pixmap! Will try larger size ....~%");
    Qhandler_for_printing_initialize_scratchpad_raster = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-INITIALIZE-SCRATCHPAD-RASTER",
	    AB_package);
    temp_1 = Icp_printing_message_handler_array;
    set_aref1(temp_1,FIX((SI_Long)31L),
	    Qhandler_for_printing_initialize_scratchpad_raster);
    Qinitialize_scratchpad_raster = 
	    STATIC_SYMBOL("INITIALIZE-SCRATCHPAD-RASTER",AB_package);
    Qminimum_width = STATIC_SYMBOL("MINIMUM-WIDTH",AB_package);
    Qminimum_height = STATIC_SYMBOL("MINIMUM-HEIGHT",AB_package);
    Qbits_per_pixel = STATIC_SYMBOL("BITS-PER-PIXEL",AB_package);
    Qmake_exact_size_p = STATIC_SYMBOL("MAKE-EXACT-SIZE-P",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_scratchpad_raster,
	    STATIC_FUNCTION(initialize_scratchpad_raster,NIL,FALSE,5,5));
    Qhandle_icp_initialize_scratchpad_raster = 
	    STATIC_SYMBOL("HANDLE-ICP-INITIALIZE-SCRATCHPAD-RASTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_initialize_scratchpad_raster,
	    STATIC_FUNCTION(handle_icp_initialize_scratchpad_raster,NIL,
	    FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_initialize_scratchpad_raster,
	    FIX((SI_Long)31L));
    if (Paint_only_target_monochrome_raster_p == UNBOUND)
	Paint_only_target_monochrome_raster_p = Nil;
    Qg2_defstruct_structure_name_tiled_raster_g2_struct = 
	    STATIC_SYMBOL("TILED-RASTER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qtiled_raster = STATIC_SYMBOL("TILED-RASTER",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_tiled_raster_g2_struct,
	    Qtiled_raster,Qab_name_of_unique_structure_type);
    mutate_global_property(Qtiled_raster,
	    Qg2_defstruct_structure_name_tiled_raster_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_tiled_raster == UNBOUND)
	The_type_description_of_tiled_raster = Nil;
    string_constant_20 = 
	    STATIC_STRING("43Dy8m83nqy1n83nqy8n8k1l8n0000001l1m83My83-BBykqk0k0");
    temp = The_type_description_of_tiled_raster;
    The_type_description_of_tiled_raster = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_20));
    mutate_global_property(Qg2_defstruct_structure_name_tiled_raster_g2_struct,
	    The_type_description_of_tiled_raster,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qtiled_raster,
	    The_type_description_of_tiled_raster,Qtype_description_of_type);
    Qoutstanding_tiled_raster_count = 
	    STATIC_SYMBOL("OUTSTANDING-TILED-RASTER-COUNT",AB_package);
    Qtiled_raster_structure_memory_usage = 
	    STATIC_SYMBOL("TILED-RASTER-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_21 = STATIC_STRING("1q83nqy8s83-t+y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_tiled_raster_count);
    push_optimized_constant(Qtiled_raster_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_21));
    Qchain_of_available_tiled_rasters = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-TILED-RASTERS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_tiled_rasters,
	    Chain_of_available_tiled_rasters);
    record_system_variable(Qchain_of_available_tiled_rasters,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qtiled_raster_count = STATIC_SYMBOL("TILED-RASTER-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtiled_raster_count,Tiled_raster_count);
    record_system_variable(Qtiled_raster_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_tiled_rasters_vector == UNBOUND)
	Chain_of_available_tiled_rasters_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qtiled_raster_structure_memory_usage,
	    STATIC_FUNCTION(tiled_raster_structure_memory_usage,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_tiled_raster_count,
	    STATIC_FUNCTION(outstanding_tiled_raster_count,NIL,FALSE,0,0));
    reclaim_structure_for_tiled_raster_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_tiled_raster,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qtiled_raster,
	    reclaim_structure_for_tiled_raster_1);
    Qx11_pixmap = STATIC_SYMBOL("X11-PIXMAP",AB_package);
    string_constant_8 = 
	    STATIC_STRING("~%Unable to allocate a ~dx~d pixmap; will attempt to return stored rasters to OS.");
    string_constant_9 = STATIC_STRING("~%~d stored rasters returned to OS.~%");
    Qg2_defstruct_structure_name_pixmap_g2_struct = 
	    STATIC_SYMBOL("PIXMAP-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qpixmap = STATIC_SYMBOL("PIXMAP",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_pixmap_g2_struct,
	    Qpixmap,Qab_name_of_unique_structure_type);
    mutate_global_property(Qpixmap,
	    Qg2_defstruct_structure_name_pixmap_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_pixmap == UNBOUND)
	The_type_description_of_pixmap = Nil;
    string_constant_22 = 
	    STATIC_STRING("43Dy8m83lVy1n83lVy8n8k1l8n0000001m1n8y83-54y1o83-8vy83-8ty83-8sy83-8uy1m83My83-Akykpk0k0");
    temp = The_type_description_of_pixmap;
    The_type_description_of_pixmap = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_22));
    mutate_global_property(Qg2_defstruct_structure_name_pixmap_g2_struct,
	    The_type_description_of_pixmap,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qpixmap,The_type_description_of_pixmap,
	    Qtype_description_of_type);
    Qoutstanding_pixmap_count = STATIC_SYMBOL("OUTSTANDING-PIXMAP-COUNT",
	    AB_package);
    Qpixmap_structure_memory_usage = 
	    STATIC_SYMBOL("PIXMAP-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_23 = STATIC_STRING("1q83lVy8s83-isy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_pixmap_count);
    push_optimized_constant(Qpixmap_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_23));
    Qchain_of_available_pixmaps = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-PIXMAPS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_pixmaps,
	    Chain_of_available_pixmaps);
    record_system_variable(Qchain_of_available_pixmaps,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qpixmap_count = STATIC_SYMBOL("PIXMAP-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpixmap_count,Pixmap_count);
    record_system_variable(Qpixmap_count,Qutilities2,FIX((SI_Long)0L),Qnil,
	    Qt,Qnil,Qnil);
    if (Chain_of_available_pixmaps_vector == UNBOUND)
	Chain_of_available_pixmaps_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qpixmap_structure_memory_usage,
	    STATIC_FUNCTION(pixmap_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_pixmap_count,
	    STATIC_FUNCTION(outstanding_pixmap_count,NIL,FALSE,0,0));
    reclaim_structure_for_pixmap_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_pixmap,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qpixmap,
	    reclaim_structure_for_pixmap_1);
    Prefer_to_hard_reclaim_irregular_sized_rasters_p = Nil;
    Qreclaim_all_scaled_fonts = STATIC_SYMBOL("RECLAIM-ALL-SCALED-FONTS",
	    AB_package);
    Qregion_and_tile_x_offset = STATIC_SYMBOL("REGION-AND-TILE-X-OFFSET",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qregion_and_tile_x_offset,
	    Region_and_tile_x_offset);
    record_system_variable(Qregion_and_tile_x_offset,Qwindows1,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qregion_and_tile_y_offset = STATIC_SYMBOL("REGION-AND-TILE-Y-OFFSET",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qregion_and_tile_y_offset,
	    Region_and_tile_y_offset);
    record_system_variable(Qregion_and_tile_y_offset,Qwindows1,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
}
