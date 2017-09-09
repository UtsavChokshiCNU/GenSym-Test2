/* player.c
 * Input file:  player.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "player.h"


DEFINE_VARIABLE_WITH_SYMBOL(Available_player_conses, Qavailable_player_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_player_conses_tail, Qavailable_player_conses_tail);

Object Available_player_conses_vector = UNBOUND;

Object Available_player_conses_tail_vector = UNBOUND;

Object Player_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Player_cons_counter, Qplayer_cons_counter);

/* OUTSTANDING-PLAYER-CONSES */
Object outstanding_player_conses()
{
    Object temp;

    x_note_fn_call(244,0);
    temp = FIXNUM_MINUS(Player_cons_counter,length(Available_player_conses));
    return VALUES_1(temp);
}

/* PLAYER-CONS-MEMORY-USAGE */
Object player_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(244,1);
    temp = FIXNUM_TIMES(Player_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-PLAYER-CONS-POOL */
Object replenish_player_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(244,2);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qplayer_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_player_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_player_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_player_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_player_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_player_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Player_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qplayer;             /* player */

/* PLAYER-CONS-1 */
Object player_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(244,3);
    new_cons = ISVREF(Available_player_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_player_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_player_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_player_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_player_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qplayer);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-PLAYER-LIST-POOL */
Object replenish_player_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(244,4);
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
    if (ISVREF(Available_player_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_player_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_player_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_player_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_player_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qplayer_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-PLAYER-LIST-1 */
Object make_player_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(244,5);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_player_conses_vector,
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
	replenish_player_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_player_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qplayer);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_player_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_player_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_player_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_player_conses_tail_vector;
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

/* PLAYER-LIST-2 */
Object player_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(244,6);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_player_conses_vector,IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_player_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_player_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qplayer);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_player_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_player_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_player_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_player_conses_tail_vector;
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

/* PLAYER-LIST-3 */
Object player_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(244,7);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_player_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_player_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_player_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qplayer);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_player_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_player_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_player_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_player_conses_tail_vector;
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

/* PLAYER-LIST-4 */
Object player_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(244,8);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_player_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_player_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_player_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qplayer);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_player_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_player_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_player_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_player_conses_tail_vector;
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

/* PLAYER-LIST-TRACE-HOOK */
Object player_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(244,9);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-PLAYER-CONSES-1 */
Object copy_tree_using_player_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(244,10);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_player_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_player_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_player_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_player_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_player_cons_pool();
	temp_1 = copy_tree_using_player_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qplayer);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_player_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_player_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_player_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_player_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_player_cons_pool();
	temp_1 = copy_tree_using_player_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qplayer);
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

/* COPY-LIST-USING-PLAYER-CONSES-1 */
Object copy_list_using_player_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(244,11);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_player_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_player_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_player_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_player_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_player_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qplayer);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_player_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_player_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_player_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_player_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_player_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qplayer);
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

/* RECLAIM-PLAYER-CONS-1 */
Object reclaim_player_cons_1(player_cons)
    Object player_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(244,12);
    inline_note_reclaim_cons(player_cons,Qplayer);
    if (ISVREF(Available_player_conses_tail_vector,
		IFIX(Current_thread_index))) {
	temp = ISVREF(Available_player_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = player_cons;
	temp = Available_player_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = player_cons;
    }
    else {
	temp = Available_player_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = player_cons;
	temp = Available_player_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = player_cons;
    }
    M_CDR(player_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-PLAYER-LIST-1 */
Object reclaim_player_list_1(player_list)
    Object player_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(244,13);
    if (player_list) {
	last_1 = player_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qplayer);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qplayer);
	if (ISVREF(Available_player_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_player_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = player_list;
	    temp = Available_player_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_player_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = player_list;
	    temp = Available_player_conses_tail_vector;
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

/* RECLAIM-PLAYER-LIST*-1 */
Object reclaim_player_list_star_1(player_list)
    Object player_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(244,14);
    if (CONSP(player_list)) {
	temp = last(player_list,_);
	M_CDR(temp) = Nil;
	if (player_list) {
	    last_1 = player_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qplayer);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qplayer);
	    if (ISVREF(Available_player_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_player_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = player_list;
		temp = Available_player_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_player_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = player_list;
		temp = Available_player_conses_tail_vector;
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

/* RECLAIM-PLAYER-TREE-1 */
Object reclaim_player_tree_1(tree)
    Object tree;
{
    Object e, e2, player_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(244,15);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_player_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		player_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(player_cons,Qplayer);
		if (EQ(player_cons,e))
		    goto end_1;
		else if ( !TRUEP(player_cons))
		    goto end_1;
		else
		    player_cons = CDR(player_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_player_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_player_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_player_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_player_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_player_conses_tail_vector;
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

/* DELETE-PLAYER-ELEMENT-1 */
Object delete_player_element_1(element,player_list)
    Object element, player_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(244,16);
    if (player_list) {
	if (EQ(element,M_CAR(player_list))) {
	    temp = CDR(player_list);
	    inline_note_reclaim_cons(player_list,Qplayer);
	    if (ISVREF(Available_player_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_player_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = player_list;
		temp_1 = Available_player_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = player_list;
	    }
	    else {
		temp_1 = Available_player_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = player_list;
		temp_1 = Available_player_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = player_list;
	    }
	    M_CDR(player_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = player_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qplayer);
		if (ISVREF(Available_player_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_player_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_player_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_player_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_player_conses_tail_vector;
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
	    temp = player_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-PLAYER-CONS-1 */
Object delete_player_cons_1(player_cons,player_list)
    Object player_cons, player_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(244,17);
    if (EQ(player_cons,player_list))
	temp = CDR(player_list);
    else {
	l_trailer_qm = Nil;
	l = player_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,player_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = player_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_player_cons_1(player_cons);
    return VALUES_1(temp);
}

/* RECLAIM-PLAYER-TREE-AND-ATOMS */
Object reclaim_player_tree_and_atoms(tree)
    Object tree;
{
    x_note_fn_call(244,18);
    reclaim_atoms_in_tree(tree);
    return reclaim_player_tree_1(tree);
}

/* RECLAIM-ATOMS-IN-TREE */
Object reclaim_atoms_in_tree(tree)
    Object tree;
{
    x_note_fn_call(244,19);
    if (CONSP(tree)) {
	reclaim_atoms_in_tree(CAR(tree));
	return reclaim_atoms_in_tree(CDR(tree));
    }
    else if (text_string_p(tree))
	return reclaim_text_string(tree);
    else
	return VALUES_1(Qnil);
}

/* COPY-TREE-AND-ATOMS-USING-PLAYER-CONSES */
Object copy_tree_and_atoms_using_player_conses(tree)
    Object tree;
{
    Object temp;

    x_note_fn_call(244,20);
    if (CONSP(tree)) {
	temp = copy_tree_and_atoms_using_player_conses(CAR(tree));
	return player_cons_1(temp,
		copy_tree_and_atoms_using_player_conses(CDR(tree)));
    }
    else if (text_string_p(tree))
	return copy_text_string(tree);
    else
	return VALUES_1(tree);
}

DEFINE_VARIABLE_WITH_SYMBOL(Player_control_stack, Qplayer_control_stack);

DEFINE_VARIABLE_WITH_SYMBOL(Player_value_stack, Qplayer_value_stack);

DEFINE_VARIABLE_WITH_SYMBOL(Player_current_instruction, Qplayer_current_instruction);

DEFINE_VARIABLE_WITH_SYMBOL(Player_lexical_binding_stack, Qplayer_lexical_binding_stack);

DEFINE_VARIABLE_WITH_SYMBOL(Player_definition_stack, Qplayer_definition_stack);

DEFINE_VARIABLE_WITH_SYMBOL(Player_location_stack, Qplayer_location_stack);

DEFINE_VARIABLE_WITH_SYMBOL(Player_named_locations, Qplayer_named_locations);

static Object Qsuspend_player;     /* suspend-player */

/* SUSPEND-PLAYER */
Object suspend_player()
{
    Object result;

    x_note_fn_call(244,21);
    result = VALUES_1(Nil);
    THROW(Qsuspend_player,result);
    return VALUES_1(Nil);
}

/* PLAYER-SYMBOL-VALUE */
Object player_symbol_value(symbol)
    Object symbol;
{
    Object lexical_binding;

    x_note_fn_call(244,22);
    lexical_binding = assq_function(symbol,Player_lexical_binding_stack);
    if (lexical_binding)
	return VALUES_1(CDR(lexical_binding));
    else
	return VALUES_1(SYMBOL_VALUE(symbol));
}

DEFINE_VARIABLE_WITH_SYMBOL(Player_target_gensym_window_g2_struct_qm, Qplayer_target_gensym_window_g2_struct_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Best_text_matched_by_player, Qbest_text_matched_by_player);

DEFINE_VARIABLE_WITH_SYMBOL(Player_mouse_x, Qplayer_mouse_x);

DEFINE_VARIABLE_WITH_SYMBOL(Player_mouse_y, Qplayer_mouse_y);

DEFINE_VARIABLE_WITH_SYMBOL(Last_player_mouse_x, Qlast_player_mouse_x);

DEFINE_VARIABLE_WITH_SYMBOL(Last_player_mouse_y, Qlast_player_mouse_y);

DEFINE_VARIABLE_WITH_SYMBOL(Last_player_event_time, Qlast_player_event_time);

DEFINE_VARIABLE_WITH_SYMBOL(Player_pace, Qplayer_pace);

/* SET-BEST-TEXT-MATCHED-BY-PLAYER */
Object set_best_text_matched_by_player(text)
    Object text;
{
    x_note_fn_call(244,23);
    if (Best_text_matched_by_player)
	reclaim_text_string(Best_text_matched_by_player);
    Best_text_matched_by_player = text;
    return VALUES_1(Best_text_matched_by_player);
}

/* CURRENT-PLAYER-EVENT-TIME */
Object current_player_event_time()
{
    x_note_fn_call(244,24);
    return VALUES_1(FIX(g2ext_x11_last_event_time(IFIX(ISVREF(Player_target_gensym_window_g2_struct_qm,
	    (SI_Long)17L)))));
}

/* PLAYER-GENERATE-EVENT */
Object player_generate_event(event_type)
    Object event_type;
{
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp, temp_1, temp_2;
    Declare_special(2);

    x_note_fn_call(244,25);
    if ( !NUM_EQ(Last_player_mouse_x,Player_mouse_x) ||  
	    !NUM_EQ(Last_player_mouse_y,Player_mouse_y)) {
	Last_player_mouse_x = Player_mouse_x;
	Last_player_mouse_y = Player_mouse_y;
	type_of_current_workstation_window = 
		ISVREF(Player_target_gensym_window_g2_struct_qm,(SI_Long)1L);
	PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_window,Qtype_of_current_workstation_window,type_of_current_workstation_window,
		1);
	  current_workstation_native_window_qm = 
		  ISVREF(Player_target_gensym_window_g2_struct_qm,
		  (SI_Long)17L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
		  0);
	    set_position_of_mouse_1(Player_mouse_x,Player_mouse_y);
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    temp = ISVREF(Player_target_gensym_window_g2_struct_qm,(SI_Long)17L);
    temp_1 = Player_mouse_x;
    temp_2 = Player_mouse_y;
    Last_player_event_time = current_player_event_time();
    enqueue_local_event(5,temp,event_type,temp_1,temp_2,
	    Last_player_event_time);
    maybe_schedule_service_workstation(Nil,T);
    return suspend_player();
}

/* PLAYER-GENERATE-EVENT-AND-SUSPEND */
Object player_generate_event_and_suspend(event_type)
    Object event_type;
{
    x_note_fn_call(244,26);
    player_generate_event(event_type);
    return suspend_player();
}

static Object string_constant;     /* "~&Player Error: ~A~%" */

/* PLAYER-ERROR */
Object player_error varargs_1(int, n)
{
    Object error_string;
    Object arg;
    Declare_varargs_nonrelocating;

    x_note_fn_call(244,27);
    INIT_ARGS_nonrelocating();
    error_string = REQUIRED_ARG_nonrelocating();
    arg = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    error_string = tformat_text_string(2,error_string,arg);
    notify_user_at_console(2,string_constant,error_string);
    reclaim_text_string(error_string);
    pause_player();
    return suspend_player();
}

static Object Qplayer_symbol_function;  /* player-symbol-function */

/* SET-PLAYER-SYMBOL-FUNCTION */
Object set_player_symbol_function(name,new_value)
    Object name, new_value;
{
    Object get_new_value;
    XDeclare_area(1);
    Object result;

    x_note_fn_call(244,28);
    if (PUSH_AREA(Dynamic_area,0)) {
	get_new_value = There_is_a_current_kb_qm ? 
		copy_tree_and_atoms_using_player_conses(new_value) : new_value;
	result = set_get(name,Qplayer_symbol_function,get_new_value);
    }
    POP_AREA(0);
    return result;
}

/* PLAYER-MARK-DEFINITIONS */
Object player_mark_definitions(name)
    Object name;
{
    x_note_fn_call(244,29);
    Player_definition_stack = player_cons_1(player_cons_1(name,Nil),
	    Player_definition_stack);
    return VALUES_1(Player_definition_stack);
}

static Object Qab_defun;           /* defun */

/* PLAYER-RELEASE-DEFINITIONS */
Object player_release_definitions(name)
    Object name;
{
    Object entry_name, definition_records, ab_loop_desetq_, player_pop_store;
    Object cons_1, next_cons, temp, svref_arg_2, definition_kind;
    Object definition_name, ab_loop_list_;

    x_note_fn_call(244,30);
    if ( !(EQ(name,T) || assq_function(name,Player_definition_stack)))
	error((SI_Long)1L,
		"Player-release-definitions is able to find matching mark.");
    entry_name = Nil;
    definition_records = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    player_pop_store = Nil;
    cons_1 = Player_definition_stack;
    if (cons_1) {
	player_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qplayer);
	if (ISVREF(Available_player_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_player_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_player_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_player_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_player_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Player_definition_stack = next_cons;
    ab_loop_desetq_ = player_pop_store;
    entry_name = CAR(ab_loop_desetq_);
    definition_records = CDR(ab_loop_desetq_);
    if ( !TRUEP(entry_name))
	goto end_loop;
    definition_kind = Nil;
    definition_name = Nil;
    ab_loop_list_ = definition_records;
    ab_loop_desetq_ = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    definition_kind = CAR(ab_loop_desetq_);
    definition_name = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(definition_kind,Qab_defun))
	undefine_player_symbol_function(definition_name);
    goto next_loop_1;
  end_loop_1:;
    if ( !EQ(T,name)) {
	if (EQ(entry_name,name))
	    return VALUES_1(Nil);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* PLAYER-RECORD-DEFINITION */
Object player_record_definition(kind,name)
    Object kind, name;
{
    Object cdr_arg, player_push_modify_macro_arg, car_1, cdr_1, cdr_new_value;

    x_note_fn_call(244,31);
    if (BOUNDP(Qplayer_definition_stack) && Player_definition_stack) {
	cdr_arg = FIRST(Player_definition_stack);
	player_push_modify_macro_arg = player_cons_1(kind,name);
	car_1 = player_push_modify_macro_arg;
	cdr_1 = CDR(cdr_arg);
	cdr_new_value = player_cons_1(car_1,cdr_1);
	return VALUES_1(M_CDR(cdr_arg) = cdr_new_value);
    }
    else
	return VALUES_1(Nil);
}

/* UNDEFINE-PLAYER-SYMBOL-FUNCTION */
Object undefine_player_symbol_function(name)
    Object name;
{
    Object definition, symbol_plist_new_value;

    x_note_fn_call(244,32);
    definition = get(name,Qplayer_symbol_function,_);
    if (definition && There_is_a_current_kb_qm)
	reclaim_player_tree_and_atoms(definition);
    symbol_plist_new_value = set_getf(SYMBOL_PLIST(name),
	    Qplayer_symbol_function,Nil);
    SET_SYMBOL_PLIST(name,symbol_plist_new_value);
    return VALUES_1(Nil);
}

static Object Qrunning;            /* running */

/* POLL-PLAYER */
Object poll_player()
{
    Object temp;
    SI_Long i;
    char temp_1;
    Declare_catch(1);
    Object result;

    x_note_fn_call(244,33);
    if (Player_target_gensym_window_g2_struct_qm) {
	if (EQ(Player_state,Qrunning)) {
	    temp = FIXNUM_ADD(Last_player_event_time,Player_pace);
	    temp_1 = FIXNUM_LE(temp,current_player_event_time());
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    if (PUSH_CATCH(Qsuspend_player,0)) {
		i = (SI_Long)0L;
	      next_loop:
		if (i > (SI_Long)20L)
		    goto end_loop;
		if ( !TRUEP(Player_control_stack)) {
		    result = VALUES_1(Nil);
		    goto end_1;
		}
		execute_player();
		i = i + (SI_Long)1L;
		goto next_loop;
	      end_loop:
		result = VALUES_1(Qnil);
	      end_1:;
	    }
	    else
		result = CATCH_VALUES();
	    POP_CATCH(0);
	    return result;
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qplayer_macro_function;  /* player-macro-function */

static Object string_constant_1;   /* "undefined player function ~S" */

/* EXECUTE-PLAYER */
Object execute_player()
{
    Object player_pop_store, cons_1, next_cons, temp, svref_arg_2;
    Object player_current_instruction, temp_1, head, handler;
    Declare_special(1);
    Object result;

    x_note_fn_call(244,34);
    player_pop_store = Nil;
    cons_1 = Player_control_stack;
    if (cons_1) {
	player_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qplayer);
	if (ISVREF(Available_player_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_player_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_player_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_player_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_player_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Player_control_stack = next_cons;
    player_current_instruction = player_pop_store;
    PUSH_SPECIAL_WITH_SYMBOL(Player_current_instruction,Qplayer_current_instruction,player_current_instruction,
	    0);
      if ( !TRUEP(Player_current_instruction)) {
	  Player_value_stack = player_cons_1(Player_current_instruction,
		  Player_value_stack);
	  result = VALUES_1(Player_value_stack);
      }
      else if (SYMBOLP(Player_current_instruction)) {
	  temp_1 = player_symbol_value(Player_current_instruction);
	  Player_value_stack = player_cons_1(temp_1,Player_value_stack);
	  result = VALUES_1(Player_value_stack);
      }
      else if (ATOM(Player_current_instruction)) {
	  Player_value_stack = player_cons_1(Player_current_instruction,
		  Player_value_stack);
	  result = VALUES_1(Player_value_stack);
      }
      else if (LISTP(Player_current_instruction)) {
	  head = FIRST(Player_current_instruction);
	  handler = Nil;
	  handler = get(head,Qplayer_macro_function,_);
	  if (handler)
	      result = FUNCALL_1(handler,Player_current_instruction);
	  else {
	      handler = get(head,Qplayer_symbol_function,_);
	      if (handler)
		  result = do_player_funcall(handler);
	      else
		  result = player_error(2,string_constant_1,
			  Player_current_instruction);
	  }
      }
      else
	  result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object Qdo_call;            /* do-call */

/* DO-PLAYER-FUNCALL */
Object do_player_funcall(handler)
    Object handler;
{
    Object arg_form, ab_loop_list_, call_site, temp_1;
    char temp;

    x_note_fn_call(244,35);
    arg_form = Nil;
    ab_loop_list_ = REST(Player_current_instruction);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    arg_form = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (CONSP(arg_form)) {
	temp = TRUEP(Nil);
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = TRUEP(T);
    goto end_1;
    temp = TRUEP(Qnil);
  end_1:;
    if (temp) {
	call_site = Nil;
	arg_form = Nil;
	ab_loop_list_ = REST(Player_current_instruction);
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	arg_form = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp_1 = SYMBOLP(arg_form) ? player_symbol_value(arg_form) : arg_form;
	call_site = player_cons_1(temp_1,call_site);
	goto next_loop_1;
      end_loop_1:
	call_site = nreverse(call_site);
	return player_do_call_finally(handler,call_site);
	return VALUES_1(Qnil);
    }
    else {
	Player_control_stack = player_cons_1(player_list_4(Qdo_call,
		Player_current_instruction,FIX((SI_Long)1L),
		length(Player_current_instruction)),Player_control_stack);
	return VALUES_1(Player_control_stack);
    }
}

/* PLAYER-INSTRUCTION-DO-CALL */
Object player_instruction_do_call(form)
    Object form;
{
    Object call, args_so_far, total_args, call_site, player_pop_store, cons_1;
    Object next_cons, temp, svref_arg_2;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(244,36);
    call = SECOND(form);
    args_so_far = THIRD(form);
    total_args = FOURTH(form);
    call_site = Nil;
    if (NUM_EQ(args_so_far,total_args)) {
	i = (SI_Long)1L;
	ab_loop_bind_ = IFIX(total_args);
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	player_pop_store = Nil;
	cons_1 = Player_value_stack;
	if (cons_1) {
	    player_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qplayer);
	    if (ISVREF(Available_player_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_player_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = cons_1;
		temp = Available_player_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    else {
		temp = Available_player_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
		temp = Available_player_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	Player_value_stack = next_cons;
	call_site = player_cons_1(player_pop_store,call_site);
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	player_do_call_finally(get(FIRST(call),Qplayer_symbol_function,_),
		call_site);
	return reclaim_player_list_1(form);
    }
    else {
	temp = add1(args_so_far);
	M_THIRD(form) = temp;
	Player_control_stack = player_cons_1(form,Player_control_stack);
	Player_control_stack = player_cons_1(nth(args_so_far,call),
		Player_control_stack);
	return VALUES_1(Player_control_stack);
    }
}

static Object Qreclaim_player_tree;  /* reclaim-player-tree */

/* PLAYER-DO-CALL-FINALLY */
Object player_do_call_finally(handler,call_site)
    Object handler, call_site;
{
    Object temp;

    x_note_fn_call(244,37);
    if (call_site)
	Player_control_stack = 
		player_cons_1(player_list_2(Qreclaim_player_tree,
		call_site),Player_control_stack);
    if (LISTP(handler)) {
	player_parse_arguments(SECOND(handler),call_site);
	Player_control_stack = player_cons_1(THIRD(handler),
		Player_control_stack);
	return VALUES_1(Player_control_stack);
    }
    else if (SYMBOLP(handler)) {
	temp = APPLY_1(handler,call_site);
	Player_value_stack = player_cons_1(temp,Player_value_stack);
	return VALUES_1(Player_value_stack);
    }
    else
	return VALUES_1(Qnil);
}

static Object string_constant_2;   /* "Player call failed since actual parameters don't match lambda list" */

static Object Qunbind;             /* unbind */

/* PLAYER-PARSE-ARGUMENTS */
Object player_parse_arguments(lambda_list,actuals)
    Object lambda_list, actuals;
{
    Object temp, parameter_name, ab_loop_list_, actual, ab_loop_list__1;

    x_note_fn_call(244,38);
    temp =  !TRUEP(lambda_list) ? ( !TRUEP(actuals) ? T : Nil) : Qnil;
    if (temp)
	return VALUES_1(temp);
    else if ( !FIXNUM_EQ(length(actuals),length(lambda_list)))
	return player_error(1,string_constant_2);
    else {
	Player_control_stack = player_cons_1(player_list_2(Qunbind,
		Player_lexical_binding_stack),Player_control_stack);
	parameter_name = Nil;
	ab_loop_list_ = lambda_list;
	actual = Nil;
	ab_loop_list__1 = actuals;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	parameter_name = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop;
	actual = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	Player_lexical_binding_stack = 
		player_cons_1(player_cons_1(parameter_name,actual),
		Player_lexical_binding_stack);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

/* PLAYER-INSTRUCTION-QUOTE */
Object player_instruction_quote(form)
    Object form;
{
    x_note_fn_call(244,39);
    Player_value_stack = player_cons_1(SECOND(form),Player_value_stack);
    return VALUES_1(Player_value_stack);
}

static Object Qprogn_1;            /* progn-1 */

/* PLAYER-INSTRUCTION-PROGN */
Object player_instruction_progn(form)
    Object form;
{
    x_note_fn_call(244,40);
    Player_control_stack = player_cons_1(player_list_4(Qprogn_1,
	    FIX((SI_Long)1L),FIXNUM_SUB1(length(form)),form),
	    Player_control_stack);
    return VALUES_1(Player_control_stack);
}

/* PLAYER-INSTRUCTION-PROGN-1 */
Object player_instruction_progn_1(form)
    Object form;
{
    Object index_1, max_1, statements, statement, player_pop_store, cons_1;
    Object next_cons, temp, svref_arg_2;

    x_note_fn_call(244,41);
    index_1 = SECOND(form);
    max_1 = THIRD(form);
    statements = FOURTH(form);
    statement = nth(index_1,statements);
    if (NUM_EQ(index_1,max_1))
	reclaim_player_list_1(Player_current_instruction);
    else {
	player_pop_store = Nil;
	cons_1 = Player_value_stack;
	if (cons_1) {
	    player_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qplayer);
	    if (ISVREF(Available_player_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_player_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = cons_1;
		temp = Available_player_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    else {
		temp = Available_player_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
		temp = Available_player_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	Player_value_stack = next_cons;
	temp = add1(index_1);
	M_SECOND(form) = temp;
	Player_control_stack = player_cons_1(form,Player_control_stack);
    }
    Player_control_stack = player_cons_1(statement,Player_control_stack);
    return VALUES_1(Player_control_stack);
}

static Object list_constant;       /* # */

/* PLAYER-INSTRUCTION-IF */
Object player_instruction_if(form)
    Object form;
{
    Object test_form, then_form, else_form;

    x_note_fn_call(244,42);
    test_form = SECOND(form);
    then_form = THIRD(form);
    else_form = FOURTH(form);
    Player_control_stack = player_cons_1(else_form,Player_control_stack);
    Player_control_stack = player_cons_1(then_form,Player_control_stack);
    Player_control_stack = player_cons_1(list_constant,Player_control_stack);
    Player_control_stack = player_cons_1(test_form,Player_control_stack);
    return VALUES_1(Player_control_stack);
}

/* PLAYER-INSTRUCTION-IF-1 */
Object player_instruction_if_1(form)
    Object form;
{
    Object player_pop_store, cons_1, next_cons, temp, svref_arg_2, then_form;
    Object else_form, player_value_stack_old_value, temp_1;

    x_note_fn_call(244,43);
    player_pop_store = Nil;
    cons_1 = Player_control_stack;
    if (cons_1) {
	player_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qplayer);
	if (ISVREF(Available_player_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_player_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_player_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_player_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_player_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Player_control_stack = next_cons;
    then_form = player_pop_store;
    player_pop_store = Nil;
    cons_1 = Player_control_stack;
    if (cons_1) {
	player_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qplayer);
	if (ISVREF(Available_player_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_player_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_player_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_player_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_player_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Player_control_stack = next_cons;
    else_form = player_pop_store;
    player_value_stack_old_value = Player_value_stack;
    temp_1 = FIRST(player_value_stack_old_value);
    temp = REST(player_value_stack_old_value);
    Player_value_stack = temp;
    if (temp_1) {
	Player_control_stack = player_cons_1(then_form,Player_control_stack);
	return VALUES_1(Player_control_stack);
    }
    else {
	Player_control_stack = player_cons_1(else_form,Player_control_stack);
	return VALUES_1(Player_control_stack);
    }
}

static Object Qplayer_tagbody_1;   /* player-tagbody-1 */

/* PLAYER-INSTRUCTION-TAGBODY */
Object player_instruction_tagbody(form)
    Object form;
{
    x_note_fn_call(244,44);
    Player_control_stack = player_cons_1(player_list_4(Qplayer_tagbody_1,
	    FIX((SI_Long)1L),length(form),form),Player_control_stack);
    return VALUES_1(Player_control_stack);
}

/* PLAYER-INSTRUCTION-PLAYER-TAGBODY-1 */
Object player_instruction_player_tagbody_1(form)
    Object form;
{
    Object index_1, max_1, statements, statement_or_tag, player_pop_store;
    Object cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(244,45);
    index_1 = SECOND(form);
    max_1 = THIRD(form);
    statements = FOURTH(form);
    statement_or_tag = nth(index_1,statements);
    if (NUM_EQ(index_1,max_1))
	reclaim_player_list_1(Player_current_instruction);
    else {
	player_pop_store = Nil;
	cons_1 = Player_value_stack;
	if (cons_1) {
	    player_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qplayer);
	    if (ISVREF(Available_player_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_player_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = cons_1;
		temp = Available_player_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    else {
		temp = Available_player_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
		temp = Available_player_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	Player_value_stack = next_cons;
	temp = add1(index_1);
	M_SECOND(form) = temp;
	Player_control_stack = player_cons_1(form,Player_control_stack);
    }
    if ( !SYMBOLP(statement_or_tag)) {
	Player_control_stack = player_cons_1(statement_or_tag,
		Player_control_stack);
	return VALUES_1(Player_control_stack);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_3;   /* "Player found no label ~S to go to in enclosing tagbodies." */

/* PLAYER-INSTRUCTION-GO */
Object player_instruction_go(form)
    Object form;
{
    Object label, new_player_control_stack, control_form, head, temp;
    Object statements, position_1, second_new_value;

    x_note_fn_call(244,46);
    label = SECOND(form);
    new_player_control_stack = Player_control_stack;
    control_form = Nil;
    head = Nil;
  next_loop:
    if ( !TRUEP(new_player_control_stack))
	goto end_loop;
    control_form = FIRST(new_player_control_stack);
    head = FIRST(control_form);
    if (EQ(head,Qplayer_tagbody_1)) {
	temp = FOURTH(control_form);
	statements = REST(temp);
	position_1 = position(2,label,statements);
	if (position_1) {
	    second_new_value = FIXNUM_ADD1(position_1);
	    M_SECOND(control_form) = second_new_value;
	    Player_control_stack = new_player_control_stack;
	    return VALUES_1(Nil);
	}
    }
    new_player_control_stack = M_CDR(new_player_control_stack);
    goto next_loop;
  end_loop:
    player_error(2,string_constant_3,label);
    return VALUES_1(Qnil);
}

/* PLAYER-INSTRUCTION-LET*-BIND */
Object player_instruction_let_star_bind(form)
    Object form;
{
    Object temp, binding_in_progress, player_pop_store, cons_1, next_cons;
    Object temp_1, svref_arg_2, temp1, temp2, temp3;

    x_note_fn_call(244,47);
    temp = SECOND(form);
    binding_in_progress = FIRST(temp);
    player_pop_store = Nil;
    cons_1 = Player_value_stack;
    if (cons_1) {
	player_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qplayer);
	if (ISVREF(Available_player_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_1 = ISVREF(Available_player_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_1) = cons_1;
	    temp_1 = Available_player_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = cons_1;
	}
	else {
	    temp_1 = Available_player_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = cons_1;
	    temp_1 = Available_player_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Player_value_stack = next_cons;
    M_CDR(binding_in_progress) = player_pop_store;
    temp = SECOND(form);
    temp1 = CDR(temp);
    temp2 = Player_lexical_binding_stack;
    temp3 = SECOND(form);
    temp_1 = SECOND(form);
    M_CDR(temp_1) = temp2;
    Player_lexical_binding_stack = temp3;
    M_SECOND(form) = temp1;
    if (SECOND(form)) {
	Player_control_stack = player_cons_1(form,Player_control_stack);
	temp = SECOND(form);
	temp = FIRST(temp);
	Player_control_stack = player_cons_1(CDR(temp),Player_control_stack);
	return VALUES_1(Player_control_stack);
    }
    else
	return reclaim_player_list_1(form);
}

/* PLAYER-INSTRUCTION-UNBIND */
Object player_instruction_unbind(form)
    Object form;
{
    Object desired_player_lexical_binding_stack, player_pop_store, cons_1;
    Object next_cons, temp, svref_arg_2;

    x_note_fn_call(244,48);
    desired_player_lexical_binding_stack = SECOND(form);
  next_loop:
    if (EQ(desired_player_lexical_binding_stack,Player_lexical_binding_stack))
	goto end_loop;
    reclaim_player_cons_1(FIRST(Player_lexical_binding_stack));
    player_pop_store = Nil;
    cons_1 = Player_lexical_binding_stack;
    if (cons_1) {
	player_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qplayer);
	if (ISVREF(Available_player_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_player_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_player_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_player_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_player_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Player_lexical_binding_stack = next_cons;
    goto next_loop;
  end_loop:;
    return reclaim_player_list_1(form);
}

static Object Qlet_star_bind;      /* let*-bind */

/* PLAYER-INSTRUCTION-LET* */
Object player_instruction_let_star(form)
    Object form;
{
    Object binding_specs, binding_spec, ab_loop_list_, lexical_variable_name;
    Object lexical_variable_init_form, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp;

    x_note_fn_call(244,49);
    binding_specs = SECOND(form);
    Player_control_stack = player_cons_1(player_list_2(Qunbind,
	    Player_lexical_binding_stack),Player_control_stack);
    Player_control_stack = player_cons_1(player_list_4(Qprogn_1,
	    FIX((SI_Long)2L),length(form),form),Player_control_stack);
    binding_spec = Nil;
    ab_loop_list_ = binding_specs;
    lexical_variable_name = Nil;
    lexical_variable_init_form = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    binding_spec = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    lexical_variable_name = SYMBOLP(binding_spec) ? binding_spec : 
	    CAR(binding_spec);
    lexical_variable_init_form = SYMBOLP(binding_spec) ? Nil : 
	    SECOND(binding_spec);
    ab_loopvar__2 = LIST_1(player_cons_1(lexical_variable_name,
	    lexical_variable_init_form));
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
    Player_control_stack = player_cons_1(player_list_2(Qlet_star_bind,
	    temp),Player_control_stack);
    temp = FIRST(Player_control_stack);
    temp = SECOND(temp);
    temp = FIRST(temp);
    Player_control_stack = player_cons_1(CDR(temp),Player_control_stack);
    return VALUES_1(Player_control_stack);
}

static Object Qwait_until;         /* wait-until */

/* PLAYER-WAIT */
Object player_wait(how_many_ticks)
    Object how_many_ticks;
{
    Object temp;

    x_note_fn_call(244,50);
    temp = player_list_2(Qwait_until,FIXNUM_ADD(how_many_ticks,
	    c_native_clock_ticks_or_cache(Nil,Nil)));
    Player_control_stack = player_cons_1(temp,Player_control_stack);
    return VALUES_1(Nil);
}

/* PLAYER-INSTRUCTION-WAIT-UNTIL */
Object player_instruction_wait_until(form)
    Object form;
{
    Object wake_up_time, temp;

    x_note_fn_call(244,51);
    wake_up_time = SECOND(form);
    temp = c_native_clock_ticks_or_cache(Nil,Nil);
    if (NUM_LE(wake_up_time,temp))
	return reclaim_player_list_1(form);
    else {
	Player_control_stack = player_cons_1(form,Player_control_stack);
	return suspend_player();
    }
}

/* PLAYER-INSTRUCTION-RECLAIM-PLAYER-TREE */
Object player_instruction_reclaim_player_tree(form)
    Object form;
{
    x_note_fn_call(244,52);
    return reclaim_player_tree_function(form);
}

/* RECLAIM-PLAYER-TREE-FUNCTION */
Object reclaim_player_tree_function(tree)
    Object tree;
{
    x_note_fn_call(244,53);
    return reclaim_player_tree_1(tree);
}

/* PLAYER-CENTER-OF-RECTANGLE */
Object player_center_of_rectangle(left,top,right,bottom)
    Object left, top, right, bottom;
{
    Object temp, temp_1;

    x_note_fn_call(244,54);
    temp = FIX(IFIX(FIXNUM_ADD(left,right)) >>  -  - (SI_Long)1L);
    temp_1 = FIX(IFIX(FIXNUM_ADD(top,bottom)) >>  -  - (SI_Long)1L);
    return VALUES_2(temp,temp_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Icp_player_message_handler_array, Qicp_player_message_handler_array);

/* DEFAULT-PLAYER-HANDLER-FOR-ICP-MESSAGES */
Object default_player_handler_for_icp_messages varargs_1(int, n)
{
    Declare_varargs_nonrelocating;

    x_note_fn_call(244,55);
    INIT_ARGS_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_score_of_best_match_for_eyes, Qcurrent_score_of_best_match_for_eyes);

DEFINE_VARIABLE_WITH_SYMBOL(Current_best_match_for_eyes, Qcurrent_best_match_for_eyes);

DEFINE_VARIABLE_WITH_SYMBOL(Current_text_focus_for_eyes_qm, Qcurrent_text_focus_for_eyes_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Current_x_for_eyes_qm, Qcurrent_x_for_eyes_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Current_y_for_eyes_qm, Qcurrent_y_for_eyes_qm);

static Object Qchar_equalw_function;  /* char-equalw-function */

static Object string_constant_4;   /* "found: ~s ~s ~s" */

/* PLAYER-HANDLER-FOR-ADD-FROM-LINE-OF-TEXT-TO-CURRENT-WINDOW */
Object player_handler_for_add_from_line_of_text_to_current_window(subtract_instead_qm,
	    clipped_left_edge,clipped_top_edge,clipped_right_edge,
	    clipped_bottom_edge,text_line,word_spacing,font_map,
	    color_difference,x_scale,y_scale,
	    left_edge_of_line_of_text_in_window,baseline_in_window)
    Object subtract_instead_qm, clipped_left_edge, clipped_top_edge;
    Object clipped_right_edge, clipped_bottom_edge, text_line, word_spacing;
    Object font_map, color_difference, x_scale, y_scale;
    Object left_edge_of_line_of_text_in_window, baseline_in_window;
{
    Object temp, current_score_of_best_match_for_eyes_new_value;
    char temp_1;

    x_note_fn_call(244,56);
    if (Current_text_focus_for_eyes_qm) {
	if (text_string_search_complex(Current_text_focus_for_eyes_qm,
		text_line,Nil,SYMBOL_FUNCTION(Qchar_equalw_function),Nil,
		Nil,FIX((SI_Long)0L),FIX((SI_Long)0L),Nil,Nil)) {
	    temp = lengthw(text_line);
	    temp_1 = FIXNUM_LT(temp,Current_score_of_best_match_for_eyes);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    if (Current_best_match_for_eyes)
		reclaim_text_string(Current_best_match_for_eyes);
	    Current_best_match_for_eyes = copy_text_string(text_line);
	    Current_score_of_best_match_for_eyes = lengthw(text_line);
	    if (Lower_match_rank_for_player_eyes_p) {
		current_score_of_best_match_for_eyes_new_value = 
			FIXNUM_ADD1(Current_score_of_best_match_for_eyes);
		Current_score_of_best_match_for_eyes = 
			current_score_of_best_match_for_eyes_new_value;
	    }
	    Current_x_for_eyes_qm = FIX(IFIX(FIXNUM_ADD(clipped_left_edge,
		    clipped_right_edge)) >>  -  - (SI_Long)1L);
	    Current_y_for_eyes_qm = FIX(IFIX(FIXNUM_ADD(clipped_top_edge,
		    clipped_bottom_edge)) >>  -  - (SI_Long)1L);
	    if (Trace_system_calls_p)
		return notify_user_at_console(4,string_constant_4,
			Current_x_for_eyes_qm,Current_y_for_eyes_qm,
			Current_best_match_for_eyes);
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qprinter;            /* printer */

static Object Kdraw_as_soon_as_possible;  /* :draw-as-soon-as-possible */

/* PLAYER-LOOK-FOR-TEXT-ON-SCREEN */
Object player_look_for_text_on_screen(current_text_focus_for_eyes_qm)
    Object current_text_focus_for_eyes_qm;
{
    Object gensym_window, current_x_for_eyes_qm, current_y_for_eyes_qm;
    Object current_best_match_for_eyes, current_score_of_best_match_for_eyes;
    Object stored_raster_type_for_window, scratchpad_raster_type_for_window;
    Object type_of_gensym_window, icp_printing_message_handler_array;
    Object current_drawing_priority, maximum_time_slice_size;
    Object priority_of_next_task, allow_invalidate_on_printing_window_p;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(10);
    Object result;

    x_note_fn_call(244,57);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Current_text_focus_for_eyes_qm,Qcurrent_text_focus_for_eyes_qm,current_text_focus_for_eyes_qm,
	    9);
      gensym_window = Player_target_gensym_window_g2_struct_qm;
      force_window_drawing(gensym_window);
      current_x_for_eyes_qm = Nil;
      current_y_for_eyes_qm = Nil;
      current_best_match_for_eyes = Nil;
      current_score_of_best_match_for_eyes = Most_positive_fixnum;
      PUSH_SPECIAL_WITH_SYMBOL(Current_score_of_best_match_for_eyes,Qcurrent_score_of_best_match_for_eyes,current_score_of_best_match_for_eyes,
	      8);
	PUSH_SPECIAL_WITH_SYMBOL(Current_best_match_for_eyes,Qcurrent_best_match_for_eyes,current_best_match_for_eyes,
		7);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_y_for_eyes_qm,Qcurrent_y_for_eyes_qm,current_y_for_eyes_qm,
		  6);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_x_for_eyes_qm,Qcurrent_x_for_eyes_qm,current_x_for_eyes_qm,
		    5);
	      stored_raster_type_for_window = ISVREF(gensym_window,
		      (SI_Long)24L);
	      scratchpad_raster_type_for_window = ISVREF(gensym_window,
		      (SI_Long)23L);
	      type_of_gensym_window = ISVREF(gensym_window,(SI_Long)1L);
	      SVREF(gensym_window,FIX((SI_Long)24L)) = Qprinter;
	      SVREF(gensym_window,FIX((SI_Long)23L)) = Qprinter;
	      SVREF(gensym_window,FIX((SI_Long)1L)) = Qprinter;
	      if (PUSH_UNWIND_PROTECT(0)) {
		  icp_printing_message_handler_array = 
			  Icp_player_message_handler_array;
		  PUSH_SPECIAL_WITH_SYMBOL(Icp_printing_message_handler_array,Qicp_printing_message_handler_array,icp_printing_message_handler_array,
			  4);
		    current_drawing_priority = Kdraw_as_soon_as_possible;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_priority,Qcurrent_drawing_priority,current_drawing_priority,
			    3);
		      maximum_time_slice_size = Most_positive_fixnum;
		      priority_of_next_task = Most_positive_fixnum;
		      PUSH_SPECIAL_WITH_SYMBOL(Priority_of_next_task,Qpriority_of_next_task,priority_of_next_task,
			      2);
			PUSH_SPECIAL_WITH_SYMBOL(Maximum_time_slice_size,Qmaximum_time_slice_size,maximum_time_slice_size,
				1);
			  allow_invalidate_on_printing_window_p = T;
			  PUSH_SPECIAL_WITH_SYMBOL(Allow_invalidate_on_printing_window_p,Qallow_invalidate_on_printing_window_p,allow_invalidate_on_printing_window_p,
				  0);
			    refresh_window(gensym_window);
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
	      }
	      POP_UNWIND_PROTECT(0);
	      SVREF(gensym_window,FIX((SI_Long)24L)) = 
		      stored_raster_type_for_window;
	      SVREF(gensym_window,FIX((SI_Long)23L)) = 
		      scratchpad_raster_type_for_window;
	      SVREF(gensym_window,FIX((SI_Long)1L)) = type_of_gensym_window;
	      CONTINUE_UNWINDING(0);
	      set_best_text_matched_by_player(Current_best_match_for_eyes);
	      result = VALUES_2(Current_x_for_eyes_qm,Current_y_for_eyes_qm);
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* DRAWING-FOR-EYES-OF-PLAYER-P */
Object drawing_for_eyes_of_player_p()
{
    x_note_fn_call(244,58);
    if (Player_target_gensym_window_g2_struct_qm && 
	    printing_window_p(Player_target_gensym_window_g2_struct_qm))
	return VALUES_1( !TRUEP(printing_p()) ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* BOUNDS-AND-COMPONENT-IN-WINDOW */
Object bounds_and_component_in_window(left_in_workspace,top_in_workspace,
	    right_in_workspace,bottom_in_workspace,component,image_plane)
    Object left_in_workspace, top_in_workspace, right_in_workspace;
    Object bottom_in_workspace, component, image_plane;
{
    Object current_frame_transform_qm, current_image_x_scale;
    Object current_image_y_scale, current_x_origin_of_drawing;
    Object current_y_origin_of_drawing, temp, temp_1, temp_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, unshifted_result;
    Declare_special(5);
    Object result;

    x_note_fn_call(244,59);
    current_frame_transform_qm = Nil;
    current_image_x_scale = ISVREF(image_plane,(SI_Long)11L);
    current_image_y_scale = ISVREF(image_plane,(SI_Long)12L);
    current_x_origin_of_drawing = ISVREF(image_plane,(SI_Long)13L);
    current_y_origin_of_drawing = ISVREF(image_plane,(SI_Long)14L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
	    4);
      PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
	      3);
	PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
		2);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
		  1);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
		    0);
	      gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	      if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
		  gensymed_symbol_1 = IFIX(left_in_workspace);
	      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		      Current_image_x_scale) && 
		      FIXNUM_LT(Current_image_x_scale,
		      Isqrt_of_most_positive_fixnum) && 
		      FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		      left_in_workspace) && FIXNUM_LT(left_in_workspace,
		      Isqrt_of_most_positive_fixnum)) {
		  unshifted_result = 
			  IFIX(FIXNUM_TIMES(Current_image_x_scale,
			  left_in_workspace)) + (SI_Long)2048L;
		  gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	      }
	      else
		  gensymed_symbol_1 = 
			  IFIX(scalef_function(Current_image_x_scale,
			  left_in_workspace));
	      temp = FIX(gensymed_symbol + gensymed_symbol_1);
	      gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	      if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
		  gensymed_symbol_1 = IFIX(top_in_workspace);
	      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		      Current_image_y_scale) && 
		      FIXNUM_LT(Current_image_y_scale,
		      Isqrt_of_most_positive_fixnum) && 
		      FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		      top_in_workspace) && FIXNUM_LT(top_in_workspace,
		      Isqrt_of_most_positive_fixnum)) {
		  unshifted_result = 
			  IFIX(FIXNUM_TIMES(Current_image_y_scale,
			  top_in_workspace)) + (SI_Long)2048L;
		  gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	      }
	      else
		  gensymed_symbol_1 = 
			  IFIX(scalef_function(Current_image_y_scale,
			  top_in_workspace));
	      temp_1 = FIX(gensymed_symbol + gensymed_symbol_1);
	      gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	      if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
		  gensymed_symbol_1 = IFIX(right_in_workspace);
	      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		      Current_image_x_scale) && 
		      FIXNUM_LT(Current_image_x_scale,
		      Isqrt_of_most_positive_fixnum) && 
		      FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		      right_in_workspace) && FIXNUM_LT(right_in_workspace,
		      Isqrt_of_most_positive_fixnum)) {
		  unshifted_result = 
			  IFIX(FIXNUM_TIMES(Current_image_x_scale,
			  right_in_workspace)) + (SI_Long)2048L;
		  gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	      }
	      else
		  gensymed_symbol_1 = 
			  IFIX(scalef_function(Current_image_x_scale,
			  right_in_workspace));
	      temp_2 = FIX(gensymed_symbol + gensymed_symbol_1);
	      gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	      if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
		  gensymed_symbol_1 = IFIX(bottom_in_workspace);
	      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		      Current_image_y_scale) && 
		      FIXNUM_LT(Current_image_y_scale,
		      Isqrt_of_most_positive_fixnum) && 
		      FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		      bottom_in_workspace) && 
		      FIXNUM_LT(bottom_in_workspace,
		      Isqrt_of_most_positive_fixnum)) {
		  unshifted_result = 
			  IFIX(FIXNUM_TIMES(Current_image_y_scale,
			  bottom_in_workspace)) + (SI_Long)2048L;
		  gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	      }
	      else
		  gensymed_symbol_1 = 
			  IFIX(scalef_function(Current_image_y_scale,
			  bottom_in_workspace));
	      result = VALUES_5(temp,temp_1,temp_2,FIX(gensymed_symbol + 
		      gensymed_symbol_1),component);
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qmenu_workspace;     /* menu-workspace */

/* PLAYER-FIND-MENU-ITEM-CONTAINING-STRING */
Object player_find_menu_item_containing_string(string_to_look_for)
    Object string_to_look_for;
{
    Object match_left, match_top, match_right, match_bottom, match_text_cell;
    Object match_text_string, match_text_length, match_image_plane, pane;
    Object ab_loop_list_, image_plane, ab_loop_list__1, workspace_qm, table;
    Object row, ab_loop_list__2, cell_qm, ab_loop_list__3, text_string;
    Object text_length, temp, left, top, right, bottom;
    Declare_special(1);
    Object result;

    x_note_fn_call(244,60);
    match_left = Nil;
    match_top = Nil;
    match_right = Nil;
    match_bottom = Nil;
    match_text_cell = Nil;
    match_text_string = Nil;
    match_text_length = Nil;
    match_image_plane = Nil;
    pane = Nil;
    ab_loop_list_ = ISVREF(Player_target_gensym_window_g2_struct_qm,
	    (SI_Long)3L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    pane = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    image_plane = Nil;
    ab_loop_list__1 = ISVREF(pane,(SI_Long)5L);
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    image_plane = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    workspace_qm = ISVREF(image_plane,(SI_Long)5L);
    if (workspace_qm && EQ(Qmenu_workspace,ISVREF(ISVREF(workspace_qm,
	    (SI_Long)1L),(SI_Long)1L))) {
	table = first_subblock(workspace_qm);
	row = Nil;
	ab_loop_list__2 = ISVREF(table,(SI_Long)19L);
	PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
	next_loop_2:
	  if ( !TRUEP(ab_loop_list__2))
	      goto end_loop_2;
	  Row = M_CAR(ab_loop_list__2);
	  ab_loop_list__2 = M_CDR(ab_loop_list__2);
	  cell_qm = Nil;
	  ab_loop_list__3 = Row;
	next_loop_3:
	  if ( !TRUEP(ab_loop_list__3))
	      goto end_loop_3;
	  cell_qm = M_CAR(ab_loop_list__3);
	  ab_loop_list__3 = M_CDR(ab_loop_list__3);
	  if (cell_qm && CONSP(cell_qm) &&  
		  !TRUEP(menu_heading_text_cell_p(cell_qm)) && 
		  find_string_in_text(2,string_to_look_for,CDDDR(cell_qm))) {
	      text_string = convert_text_to_text_string(1,CDDDR(cell_qm));
	      text_length = lengthw(text_string);
	      if ( !TRUEP(match_text_length) || FIXNUM_LT(text_length,
		      match_text_length)) {
		  temp = text_string;
		  if (match_text_string)
		      reclaim_text_string(match_text_string);
		  match_text_string = temp;
		  match_text_length = text_length;
		  result = get_table_cell_edges(table,cell_qm);
		  MVS_4(result,left,top,right,bottom);
		  match_left = left;
		  match_top = top;
		  match_right = right;
		  match_bottom = bottom;
		  match_text_cell = cell_qm;
		  match_image_plane = image_plane;
	      }
	  }
	  goto next_loop_3;
	end_loop_3:;
	  goto next_loop_2;
	end_loop_2:;
	POP_SPECIAL();
    }
    goto next_loop_1;
  end_loop_1:;
    goto next_loop;
  end_loop:;
    set_best_text_matched_by_player(match_text_string);
    if (match_text_cell)
	return bounds_and_component_in_window(match_left,match_top,
		match_right,match_bottom,match_text_cell,match_image_plane);
    else
	return VALUES_1(Nil);
}

/* PLAYER-FIND-ATTRIBUTE-TABLE-VALUE-CELL */
Object player_find_attribute_table_value_cell(string_to_look_for)
    Object string_to_look_for;
{
    Object match_left, match_top, match_right, match_bottom, match_text_string;
    Object match_text_length, match_text_cell, match_image_plane, pane;
    Object ab_loop_list_, image_plane, ab_loop_list__1, workspace_qm;
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, subblock;
    Object table, row, ab_loop_list__2, description_cell_qm, text, text_string;
    Object text_length, value_cell, temp, left, top, right, bottom;
    Declare_special(1);
    Object result;

    x_note_fn_call(244,61);
    match_left = Nil;
    match_top = Nil;
    match_right = Nil;
    match_bottom = Nil;
    match_text_string = Nil;
    match_text_length = Nil;
    match_text_cell = Nil;
    match_image_plane = Nil;
    pane = Nil;
    ab_loop_list_ = ISVREF(Player_target_gensym_window_g2_struct_qm,
	    (SI_Long)3L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    pane = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    image_plane = Nil;
    ab_loop_list__1 = ISVREF(pane,(SI_Long)5L);
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    image_plane = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    workspace_qm = ISVREF(image_plane,(SI_Long)5L);
    if (workspace_qm) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(workspace_qm,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	ab_queue_form_ = gensymed_symbol;
	ab_next_queue_element_ = Nil;
	subblock = Nil;
	if (ab_queue_form_)
	    ab_next_queue_element_ = 
		    constant_queue_next(ISVREF(ab_queue_form_,(SI_Long)2L),
		    ab_queue_form_);
      next_loop_2:
	if ( !TRUEP(ab_next_queue_element_))
	    goto end_loop_2;
	subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	ab_next_queue_element_ = 
		constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	if (attribute_table_p(subblock)) {
	    table = subblock;
	    row = Nil;
	    ab_loop_list__2 = ISVREF(table,(SI_Long)19L);
	    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
	      description_cell_qm = Nil;
	    next_loop_3:
	      if ( !TRUEP(ab_loop_list__2))
		  goto end_loop_3;
	      Row = M_CAR(ab_loop_list__2);
	      ab_loop_list__2 = M_CDR(ab_loop_list__2);
	      description_cell_qm = CDR(Row) ? CAR(Row) : Nil;
	      if (description_cell_qm && CONSP(description_cell_qm) && 
		      find_string_in_text(2,string_to_look_for,
		      CDDDR(description_cell_qm))) {
		  text = CDDDR(description_cell_qm);
		  text_string = convert_text_to_text_string(1,text);
		  text_length = lengthw(text_string);
		  value_cell = SECOND(Row);
		  if ( !TRUEP(match_text_length) || FIXNUM_LT(text_length,
			  match_text_length)) {
		      temp = text_string;
		      if (match_text_string)
			  reclaim_text_string(match_text_string);
		      match_text_string = temp;
		      match_text_length = text_length;
		      result = get_table_cell_edges(table,value_cell);
		      MVS_4(result,left,top,right,bottom);
		      match_left = left;
		      match_top = top;
		      match_right = right;
		      match_bottom = bottom;
		      match_text_cell = value_cell;
		      match_image_plane = image_plane;
		  }
	      }
	      goto next_loop_3;
	    end_loop_3:;
	    POP_SPECIAL();
	}
	goto next_loop_2;
      end_loop_2:;
    }
    goto next_loop_1;
  end_loop_1:;
    goto next_loop;
  end_loop:;
    set_best_text_matched_by_player(match_text_string);
    if (match_text_cell)
	return bounds_and_component_in_window(match_left,match_top,
		match_right,match_bottom,match_text_cell,match_image_plane);
    else
	return VALUES_1(Nil);
}

static Object Qaction_button;      /* action-button */

/* PLAYER-FIND-ACTION-BUTTON */
Object player_find_action_button(string_to_look_for)
    Object string_to_look_for;
{
    Object match_subblock, match_image_plane, match_label, match_label_length;
    Object pane, ab_loop_list_, image_plane, ab_loop_list__1, workspace_qm;
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, subblock;
    Object label, temp_1, temp_2, temp_3;
    char temp;

    x_note_fn_call(244,62);
    match_subblock = Nil;
    match_image_plane = Nil;
    match_label = Nil;
    match_label_length = Nil;
    pane = Nil;
    ab_loop_list_ = ISVREF(Player_target_gensym_window_g2_struct_qm,
	    (SI_Long)3L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    pane = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    image_plane = Nil;
    ab_loop_list__1 = ISVREF(pane,(SI_Long)5L);
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    image_plane = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    workspace_qm = ISVREF(image_plane,(SI_Long)5L);
    if (workspace_qm) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(workspace_qm,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	ab_queue_form_ = gensymed_symbol;
	ab_next_queue_element_ = Nil;
	subblock = Nil;
	label = Nil;
	if (ab_queue_form_)
	    ab_next_queue_element_ = 
		    constant_queue_next(ISVREF(ab_queue_form_,(SI_Long)2L),
		    ab_queue_form_);
      next_loop_2:
	if ( !TRUEP(ab_next_queue_element_))
	    goto end_loop_2;
	subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	ab_next_queue_element_ = 
		constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	label = EQ(Qaction_button,ISVREF(ISVREF(subblock,(SI_Long)1L),
		(SI_Long)1L)) ? ISVREF(subblock,(SI_Long)20L) : Qnil;
	if (label && text_string_search_simple(string_to_look_for,label)) {
	    temp =  !TRUEP(match_subblock);
	    if (temp);
	    else {
		temp_1 = lengthw(label);
		temp = FIXNUM_LT(temp_1,match_label_length);
	    }
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    match_subblock = subblock;
	    match_image_plane = image_plane;
	    match_label = ISVREF(subblock,(SI_Long)20L);
	    match_label_length = lengthw(match_label);
	}
	goto next_loop_2;
      end_loop_2:;
    }
    goto next_loop_1;
  end_loop_1:;
    goto next_loop;
  end_loop:;
    if (match_subblock) {
	set_best_text_matched_by_player(copy_text_string(match_label));
	gensymed_symbol = ISVREF(match_subblock,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	temp_2 = gensymed_symbol;
	gensymed_symbol = ISVREF(match_subblock,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	temp_3 = gensymed_symbol;
	gensymed_symbol = ISVREF(match_subblock,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	temp_1 = gensymed_symbol;
	gensymed_symbol = ISVREF(match_subblock,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	return bounds_and_component_in_window(temp_2,temp_3,temp_1,
		gensymed_symbol,match_subblock,match_image_plane);
    }
    else
	return VALUES_1(Nil);
}

/* PLAYER-FIND-INSTANCE */
Object player_find_instance(class_name)
    Object class_name;
{
    Object pane, ab_loop_list_, image_plane, ab_loop_list__1, workspace_qm;
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, subblock;
    Object temp, temp_1, temp_2, left, top, right, bottom;
    Object result;

    x_note_fn_call(244,63);
    pane = Nil;
    ab_loop_list_ = ISVREF(Player_target_gensym_window_g2_struct_qm,
	    (SI_Long)3L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    pane = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    image_plane = Nil;
    ab_loop_list__1 = ISVREF(pane,(SI_Long)5L);
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    image_plane = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    workspace_qm = ISVREF(image_plane,(SI_Long)5L);
    if (workspace_qm) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(workspace_qm,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	ab_queue_form_ = gensymed_symbol;
	ab_next_queue_element_ = Nil;
	subblock = Nil;
	if (ab_queue_form_)
	    ab_next_queue_element_ = 
		    constant_queue_next(ISVREF(ab_queue_form_,(SI_Long)2L),
		    ab_queue_form_);
      next_loop_2:
	if ( !TRUEP(ab_next_queue_element_))
	    goto end_loop_2;
	subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	ab_next_queue_element_ = 
		constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	if (EQ(class_name,ISVREF(ISVREF(subblock,(SI_Long)1L),(SI_Long)1L))) {
	    gensymed_symbol = ISVREF(subblock,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    temp = gensymed_symbol;
	    gensymed_symbol = ISVREF(subblock,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    temp_1 = gensymed_symbol;
	    gensymed_symbol = ISVREF(subblock,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    temp_2 = gensymed_symbol;
	    gensymed_symbol = ISVREF(subblock,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    result = bounds_and_component_in_window(temp,temp_1,temp_2,
		    gensymed_symbol,subblock,image_plane);
	    MVS_4(result,left,top,right,bottom);
	    temp_1 = FIX(IFIX(FIXNUM_ADD(left,right)) >>  -  - (SI_Long)1L);
	    temp_2 = FIX(IFIX(FIXNUM_ADD(top,bottom)) >>  -  - (SI_Long)1L);
	    return VALUES_2(temp_1,temp_2);
	}
	goto next_loop_2;
      end_loop_2:;
    }
    goto next_loop_1;
  end_loop_1:;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* PLAYER-MOVE-TO */
Object player_move_to(x,y)
    Object x, y;
{
    x_note_fn_call(244,64);
    Player_mouse_x = x;
    Player_mouse_y = y;
    return player_generate_event_and_suspend(FIX((SI_Long)771L));
}

/* PLAYER-MOVE */
Object player_move(delta_x,delta_y)
    Object delta_x, delta_y;
{
    Object incf_arg, temp;

    x_note_fn_call(244,65);
    incf_arg = delta_x;
    temp = add(Player_mouse_x,incf_arg);
    Player_mouse_x = temp;
    incf_arg = delta_y;
    temp = add(Player_mouse_y,incf_arg);
    Player_mouse_y = temp;
    return player_generate_event_and_suspend(FIX((SI_Long)771L));
}

/* PLAYER-PUSH-LOCATION */
Object player_push_location()
{
    x_note_fn_call(244,66);
    Player_location_stack = player_cons_1(player_cons_1(Player_mouse_x,
	    Player_mouse_y),Player_location_stack);
    return VALUES_1(Player_location_stack);
}

/* PLAYER-POP-LOCATION */
Object player_pop_location()
{
    Object player_pop_store, cons_1, next_cons, temp, svref_arg_2;
    Object location_record, x, y;

    x_note_fn_call(244,67);
    player_pop_store = Nil;
    cons_1 = Player_location_stack;
    if (cons_1) {
	player_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qplayer);
	if (ISVREF(Available_player_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_player_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_player_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_player_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_player_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Player_location_stack = next_cons;
    location_record = player_pop_store;
    x = CAR(location_record);
    y = CDR(location_record);
    reclaim_player_cons_1(location_record);
    return player_move_to(x,y);
}

/* PLAYER-NAME-LOCATION */
Object player_name_location(name)
    Object name;
{
    Object alist_entry, new_entry, location_record, temp;

    x_note_fn_call(244,68);
    alist_entry = assq_function(name,Player_named_locations);
    if (alist_entry);
    else {
	new_entry = player_cons_1(name,player_cons_1(Nil,Nil));
	Player_named_locations = player_cons_1(new_entry,
		Player_named_locations);
	alist_entry = new_entry;
    }
    location_record = CDR(alist_entry);
    temp = Player_mouse_x;
    M_CAR(location_record) = temp;
    temp = Player_mouse_y;
    return VALUES_1(M_CDR(location_record) = temp);
}

static Object string_constant_5;   /* "Unknown location passed to move-to-location." */

/* PLAYER-MOVE-TO-LOCATION */
Object player_move_to_location(name)
    Object name;
{
    Object alist_entry, location_record;

    x_note_fn_call(244,69);
    alist_entry = assq_function(name,Player_named_locations);
    location_record = CDR(alist_entry);
    if ( !TRUEP(location_record))
	player_error(1,string_constant_5);
    return player_move_to(CAR(location_record),CDR(location_record));
}

/* PLAYER-TRANSLATE-CHARACTER-CODE-TO-EVENT-CODE */
Object player_translate_character_code_to_event_code(wide_character)
    Object wide_character;
{
    x_note_fn_call(244,70);
    return key_code_from_character(CODE_CHAR(wide_character));
}

/* PLAYER-TYPE-CHARACTER */
Object player_type_character(wide_character)
    Object wide_character;
{
    x_note_fn_call(244,71);
    return player_generate_event(player_translate_character_code_to_event_code(wide_character));
}

static Object Qtype_1;             /* type-1 */

/* PLAYER-TYPE */
Object player_type(string_1)
    Object string_1;
{
    Object temp;

    x_note_fn_call(244,72);
    temp = player_list_4(Qtype_1,string_1,lengthw(string_1),FIX((SI_Long)0L));
    Player_control_stack = player_cons_1(temp,Player_control_stack);
    return VALUES_1(Nil);
}

/* PLAYER-INSTRUCTION-TYPE-1 */
Object player_instruction_type_1(form)
    Object form;
{
    Object string_1, max_1, index_1, fourth_new_value;

    x_note_fn_call(244,73);
    string_1 = SECOND(form);
    max_1 = THIRD(form);
    index_1 = FOURTH(form);
    if (NUM_GE(index_1,max_1))
	return reclaim_player_list_1(form);
    else {
	fourth_new_value = add1(index_1);
	M_FOURTH(form) = fourth_new_value;
	Player_control_stack = player_cons_1(form,Player_control_stack);
	return player_generate_event(player_translate_character_code_to_event_code(FIX(UBYTE_16_ISAREF_1(string_1,
		IFIX(index_1)))));
    }
}

static Object string_constant_6;   /* "player-text-visible-p: ~s" */

/* PLAYER-TEXT-VISIBLE-P */
Object player_text_visible_p(text)
    Object text;
{
    x_note_fn_call(244,74);
    if (player_look_for_text_on_screen(text)) {
	if (Trace_system_calls_p)
	    notify_user_at_console(2,string_constant_6,
		    Best_text_matched_by_player);
	return VALUES_1(T);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_7;   /* "player-move-to-text: ~s ~s ~s" */

static Object string_constant_8;   /* "Player couldn't find text." */

/* PLAYER-MOVE-TO-TEXT */
Object player_move_to_text(text)
    Object text;
{
    Object x_qm, y_qm;
    Object result;

    x_note_fn_call(244,75);
    result = player_look_for_text_on_screen(text);
    MVS_2(result,x_qm,y_qm);
    if (x_qm && Trace_system_calls_p)
	notify_user_at_console(4,string_constant_7,x_qm,y_qm,
		Best_text_matched_by_player);
    if (x_qm)
	return player_move_to(x_qm,y_qm);
    else
	return player_error(1,string_constant_8);
}

static Object string_constant_9;   /* "player-move-to-menu-item: ~s" */

static Object string_constant_10;  /* "Player couldn't find menu item." */

/* PLAYER-MOVE-TO-MENU-ITEM */
Object player_move_to_menu_item(text)
    Object text;
{
    Object left, top, right, bottom, x, y;
    Object result;

    x_note_fn_call(244,76);
    result = player_find_menu_item_containing_string(text);
    MVS_4(result,left,top,right,bottom);
    if (left) {
	if (Trace_system_calls_p)
	    notify_user_at_console(2,string_constant_9,
		    Best_text_matched_by_player);
	result = player_center_of_rectangle(left,top,right,bottom);
	MVS_2(result,x,y);
	return player_move_to(x,y);
    }
    else
	return player_error(1,string_constant_10);
}

static Object string_constant_11;  /* "player-move-to-attribute-table-slot: ~s" */

static Object string_constant_12;  /* "Player couldn't find attribute table slot." */

/* PLAYER-MOVE-TO-ATTRIBUTE-TABLE-SLOT */
Object player_move_to_attribute_table_slot(string_to_look_for)
    Object string_to_look_for;
{
    Object left, top, temp, bottom;
    Object result;

    x_note_fn_call(244,77);
    result = player_find_attribute_table_value_cell(string_to_look_for);
    MVS_4(result,left,top,temp,bottom);
    if (left) {
	if (Trace_system_calls_p)
	    notify_user_at_console(2,string_constant_11,
		    Best_text_matched_by_player);
	return player_move_to(FIXNUM_ADD1(left),ltruncate(FIXNUM_ADD(top,
		bottom),FIX((SI_Long)2L)));
    }
    else
	return player_error(1,string_constant_12);
}

static Object string_constant_13;  /* "player-move-to-action-button: ~s" */

/* PLAYER-MOVE-TO-ACTION-BUTTON */
Object player_move_to_action_button(string_to_look_for)
    Object string_to_look_for;
{
    Object left, top, right, bottom;
    Object result;

    x_note_fn_call(244,78);
    result = player_find_action_button(string_to_look_for);
    MVS_4(result,left,top,right,bottom);
    if (left) {
	if (Trace_system_calls_p)
	    notify_user_at_console(2,string_constant_13,
		    Best_text_matched_by_player);
	return player_move_to(ltruncate(FIXNUM_ADD(left,right),
		FIX((SI_Long)2L)),ltruncate(FIXNUM_ADD(top,bottom),
		FIX((SI_Long)2L)));
    }
    else
	return player_error(1,string_constant_12);
}

/* PLAYER-MOVE-TO-INSTANCE */
Object player_move_to_instance(class_name)
    Object class_name;
{
    Object x, y;
    Object result;

    x_note_fn_call(244,79);
    result = player_find_instance(class_name);
    MVS_2(result,x,y);
    if (x)
	return player_move_to(x,y);
    else
	return player_error(1,string_constant_12);
}

static Object Qpaused;             /* paused */

static Object Qg2_window;          /* g2-window */

static Object Qlocal;              /* local */

static Object Qg2_window_management_type;  /* g2-window-management-type */

/* CLEAR-PLAYER */
Object clear_player()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, w, g2_window_qm;
    Object workstation_qm, window_struct;
    char temp;
    Declare_special(1);

    x_note_fn_call(244,80);
    Player_value_stack = Nil;
    Player_control_stack = Nil;
    reclaim_player_tree_1(Player_location_stack);
    Player_location_stack = Nil;
    reclaim_player_tree_1(Player_named_locations);
    Player_named_locations = Nil;
    Player_state = Qpaused;
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    w = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qg2_window);
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
      w = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      if (EQ(Qlocal,get_lookup_slot_value_given_default(w,
	      Qg2_window_management_type,Nil))) {
	  g2_window_qm = w;
	  goto end_1;
      }
      goto next_loop;
    end_loop_1:
      g2_window_qm = Qnil;
    end_1:;
    POP_SPECIAL();
    workstation_qm = g2_window_qm ? ISVREF(g2_window_qm,(SI_Long)20L) : Nil;
    window_struct = workstation_qm ? ISVREF(workstation_qm,(SI_Long)1L) : 
	    System_window;
  test:
    if ( !TRUEP(window_struct)) {
	cerror((SI_Long)2L,"The test will be tried again.",
		"Player-eval couldn\'t find a window to play into.");
	goto test;
    }
    Player_target_gensym_window_g2_struct_qm = window_struct;
    return player_release_definitions(T);
}

/* PAUSE-PLAYER */
Object pause_player()
{
    x_note_fn_call(244,81);
    Player_state = Qpaused;
    return VALUES_1(Player_state);
}

/* RESUME-PLAYER */
Object resume_player()
{
    x_note_fn_call(244,82);
    Last_player_event_time = FIX((SI_Long)0L);
    Player_state = Qrunning;
    return VALUES_1(Player_state);
}

/* PLAYER-EVAL */
Object player_eval(form)
    Object form;
{
    x_note_fn_call(244,83);
    clear_player();
    Player_control_stack = player_cons_1(form,Player_control_stack);
    return resume_player();
}

/* PLAYER-EVAL-SERVER */
Object player_eval_server(form)
    Object form;
{
    Object copy_of_form;

    x_note_fn_call(244,84);
    clear_player();
    copy_of_form = copy_tree_and_atoms_using_player_conses(form);
    Player_control_stack = 
	    player_cons_1(player_list_2(Qreclaim_player_tree,copy_of_form),
	    Player_control_stack);
    Player_control_stack = player_cons_1(copy_of_form,Player_control_stack);
    return resume_player();
}

DEFINE_VARIABLE_WITH_SYMBOL(Player_icp_connection, Qplayer_icp_connection);

/* OPEN-ICP-CONNECTION-FOR-PLAYER */
Object open_icp_connection_for_player(machine,address,protocol)
    Object machine, address, protocol;
{
    x_note_fn_call(244,85);
    if (Player_icp_connection)
	close_icp_connection_for_player();
    Player_icp_connection = setup_network_connection_for_connect(1,
	    make_icp_connection(1,LIST_3(protocol,machine,address)));
    return VALUES_1(Player_icp_connection);
}

/* CLOSE-ICP-CONNECTION-FOR-PLAYER */
Object close_icp_connection_for_player()
{
    Object temp;

    x_note_fn_call(244,86);
    temp = Player_icp_connection;
    Player_icp_connection = Nil;
    return flush_and_shutdown_icp_socket(temp);
}

static Object Qtelewindows;        /* telewindows */

/* REMOTE-EVAL */
Object remote_eval(form)
    Object form;
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

    x_note_fn_call(244,87);
    current_icp_port = ISVREF(Player_icp_connection,(SI_Long)4L);
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
				temp = send_icp_remote_eval(form);
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

/* REMOTE-EVAL-ONCE */
Object remote_eval_once(form,target_machine,target_address,target_protocol)
    Object form, target_machine, target_address, target_protocol;
{
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(244,88);
    SAVE_STACK();
    open_icp_connection_for_player(target_machine,target_address,
	    target_protocol);
    if (PUSH_UNWIND_PROTECT(0))
	SAVE_VALUES(remote_eval(form));
    POP_UNWIND_PROTECT(0);
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* PLAYER-SERVER-PUSH-CONTROL-STACK */
Object player_server_push_control_stack(form)
    Object form;
{
    Object temp;

    x_note_fn_call(244,89);
    temp = copy_tree_and_atoms_using_player_conses(form);
    Player_control_stack = player_cons_1(temp,Player_control_stack);
    return VALUES_1(Player_control_stack);
}

DEFINE_VARIABLE_WITH_SYMBOL(Player_require_modules_already_sent, Qplayer_require_modules_already_sent);

static Object Qtcp_ip;             /* tcp-ip */

static Object list_constant_1;     /* # */

static Object list_constant_2;     /* # */

static Object list_constant_3;     /* # */

static Object list_constant_4;     /* # */

static Object list_constant_5;     /* # */

/* PLAY-TEST */
Object play_test varargs_1(int, n)
{
    Object test_name;
    Object target_machine, target_address, target_protocol;
    Object player_require_modules_already_sent;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(1);
    Object result;

    x_note_fn_call(244,90);
    INIT_ARGS_nonrelocating();
    test_name = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    target_machine = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    target_address = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    target_protocol = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(target_machine))
	target_machine = get_local_host_name();
    if ( !TRUEP(target_address))
	target_address = get_current_icp_contact_port_number_or_name_if_any();
    if ( !TRUEP(target_protocol))
	target_protocol = Qtcp_ip;
    format((SI_Long)6L,T,"~%Sending ~A to ~A at ~D via ~A.",test_name,
	    target_machine,target_address,target_protocol);
    player_require_modules_already_sent = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Player_require_modules_already_sent,Qplayer_require_modules_already_sent,player_require_modules_already_sent,
	    0);
      if (PUSH_UNWIND_PROTECT(1)) {
	  open_icp_connection_for_player(target_machine,target_address,
		  target_protocol);
	  if (PUSH_UNWIND_PROTECT(0)) {
	      remote_eval(list_constant_1);
	      remote_eval(list_constant_2);
	      remote_eval(list_constant_3);
	      remote_eval(list_constant_4);
	      SAVE_VALUES(remote_eval(list_constant_5));
	  }
	  POP_UNWIND_PROTECT(0);
	  CONTINUE_UNWINDING(0);
      }
      POP_UNWIND_PROTECT(1);
      reclaim_player_list_1(Player_require_modules_already_sent);
      CONTINUE_UNWINDING(1);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Qguardian;           /* guardian */

/* GUARDIAN */
Object guardian()
{
    x_note_fn_call(244,91);
    return play_test(1,Qguardian);
}

Object C_boolean_false = UNBOUND;

Object C_boolean_true = UNBOUND;

/* PM-PUSH-LOCATION */
Object pm_push_location()
{
    Object result_1;

    x_note_fn_call(244,92);
    result_1 = C_boolean_true;
    Player_location_stack = player_cons_1(player_cons_1(Player_mouse_x,
	    Player_mouse_y),Player_location_stack);
    return VALUES_1(result_1);
}

/* PM-POP-LOCATION */
Object pm_pop_location()
{
    Object result_1, player_pop_store, cons_1, next_cons, temp, svref_arg_2;
    Object location_record, x, y;
    Declare_catch(1);

    x_note_fn_call(244,93);
    result_1 = C_boolean_true;
    if (Player_location_stack) {
	player_pop_store = Nil;
	cons_1 = Player_location_stack;
	if (cons_1) {
	    player_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qplayer);
	    if (ISVREF(Available_player_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_player_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = cons_1;
		temp = Available_player_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    else {
		temp = Available_player_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
		temp = Available_player_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	Player_location_stack = next_cons;
	location_record = player_pop_store;
	x = CAR(location_record);
	y = CDR(location_record);
	reclaim_player_cons_1(location_record);
	if (PUSH_CATCH(Qsuspend_player,0))
	    player_move_to(x,y);
	POP_CATCH(0);
    }
    return VALUES_1(result_1);
}

/* PM-MOVE */
Object pm_move(mouse_x_as_evaluation_value,mouse_y_as_evaluation_value)
    Object mouse_x_as_evaluation_value, mouse_y_as_evaluation_value;
{
    Object mouse_x, mouse_y, result_1;
    Declare_catch(1);

    x_note_fn_call(244,94);
    mouse_x = mouse_x_as_evaluation_value;
    mouse_y = mouse_y_as_evaluation_value;
    result_1 = C_boolean_true;
    if (PUSH_CATCH(Qsuspend_player,0))
	player_move_to(FIXNUM_ADD(Player_mouse_x,mouse_x),
		FIXNUM_ADD(Player_mouse_y,mouse_y));
    POP_CATCH(0);
    return VALUES_1(result_1);
}

/* PM-RESET */
Object pm_reset()
{
    Object result_1;

    x_note_fn_call(244,95);
    result_1 = C_boolean_true;
    if (Trace_system_calls_p)
	trace_events();
    clear_player();
    return VALUES_1(result_1);
}

/* PM-TYPE-CONTROL-X */
Object pm_type_control_x()
{
    Object result_1;
    Declare_catch(1);

    x_note_fn_call(244,96);
    result_1 = C_boolean_true;
    if (PUSH_CATCH(Qsuspend_player,0))
	player_generate_event(player_translate_character_code_to_event_code(CHAR_CODE(CHR('\030'))));
    POP_CATCH(0);
    return VALUES_1(result_1);
}

static Object Qmouse_down;         /* mouse-down */

static Object Qmouse_up;           /* mouse-up */

static Object Qmouse_motion;       /* mouse-motion */

static Object Qkeystroke;          /* keystroke */

static Object Qkludge;             /* kludge */

/* PM-GENERATE-EVENT */
Object pm_generate_event(simple_event_type_as_evaluation_value,
	    character_as_integer_as_evaluation_value,
	    mouse_x_as_evaluation_value,mouse_y_as_evaluation_value)
    Object simple_event_type_as_evaluation_value;
    Object character_as_integer_as_evaluation_value;
    Object mouse_x_as_evaluation_value, mouse_y_as_evaluation_value;
{
    Object simple_event_type, character_as_integer, mouse_x, mouse_y, result_1;
    Object real_event_type, temp;
    Declare_catch(1);

    x_note_fn_call(244,97);
    simple_event_type = simple_event_type_as_evaluation_value;
    character_as_integer = character_as_integer_as_evaluation_value;
    mouse_x = mouse_x_as_evaluation_value;
    mouse_y = mouse_y_as_evaluation_value;
    result_1 = C_boolean_true;
    if (EQ(simple_event_type,Qmouse_down))
	real_event_type = FIX((SI_Long)772L);
    else if (EQ(simple_event_type,Qmouse_up))
	real_event_type = FIX((SI_Long)773L);
    else if (EQ(simple_event_type,Qmouse_motion))
	real_event_type = FIX((SI_Long)771L);
    else if (EQ(simple_event_type,Qkeystroke))
	real_event_type = character_as_integer;
    else if (EQ(simple_event_type,Qkludge))
	real_event_type = character_as_integer;
    else
	real_event_type = Qnil;
    if (PUSH_CATCH(Qsuspend_player,0)) {
	temp = FIX((SI_Long)0L);
	if (NUM_GT(character_as_integer,temp)) {
	    Player_mouse_x = mouse_x;
	    Player_mouse_y = mouse_y;
	}
	player_generate_event(real_event_type);
    }
    POP_CATCH(0);
    return VALUES_1(result_1);
}

/* PM-GET-CURRENT-LOCATION */
Object pm_get_current_location()
{
    Object player_x, player_y, real_x, real_y;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm;
    Declare_special(2);
    Object result;

    x_note_fn_call(244,98);
    player_x = Nil;
    player_y = Nil;
    real_x = Nil;
    real_y = Nil;
    player_x = Player_mouse_x;
    player_y = Player_mouse_y;
    type_of_current_workstation_window = 
	    ISVREF(Player_target_gensym_window_g2_struct_qm,(SI_Long)1L);
    PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_window,Qtype_of_current_workstation_window,type_of_current_workstation_window,
	    1);
      current_workstation_native_window_qm = 
	      ISVREF(Player_target_gensym_window_g2_struct_qm,(SI_Long)17L);
      PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
	      0);
	result = get_position_of_mouse();
	MVS_2(result,real_x,real_y);
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_4(player_x,player_y,real_x,real_y);
}

/* PM-TEXT-VISIBLE-P */
Object pm_text_visible_p(text_as_evaluation_value)
    Object text_as_evaluation_value;
{
    Object text;
    SI_Long result_1;

    x_note_fn_call(244,99);
    text = text_as_evaluation_value;
    result_1 = player_text_visible_p(text) ? (SI_Long)1L : (SI_Long)0L;
    reclaim_text_string(text_as_evaluation_value);
    return VALUES_1(FIX(result_1));
}

/* PM-MOVE-TO-TEXT */
Object pm_move_to_text(text_as_evaluation_value)
    Object text_as_evaluation_value;
{
    Object text, result_1;
    Declare_catch(1);

    x_note_fn_call(244,100);
    text = text_as_evaluation_value;
    result_1 = C_boolean_true;
    if (PUSH_CATCH(Qsuspend_player,0))
	player_move_to_text(text);
    POP_CATCH(0);
    reclaim_text_string(text_as_evaluation_value);
    return VALUES_1(result_1);
}

/* PM-MENU-ITEM-VISIBLE-P */
Object pm_menu_item_visible_p(text_as_evaluation_value)
    Object text_as_evaluation_value;
{
    Object text;
    SI_Long result_1;

    x_note_fn_call(244,101);
    text = text_as_evaluation_value;
    result_1 = player_find_menu_item_containing_string(text) ? (SI_Long)1L 
	    : (SI_Long)0L;
    reclaim_text_string(text_as_evaluation_value);
    return VALUES_1(FIX(result_1));
}

/* PM-ACTION-BUTTON-VISIBLE-P */
Object pm_action_button_visible_p(text_as_evaluation_value)
    Object text_as_evaluation_value;
{
    Object text;
    SI_Long result_1;

    x_note_fn_call(244,102);
    text = text_as_evaluation_value;
    result_1 = player_find_action_button(text) ? (SI_Long)1L : (SI_Long)0L;
    reclaim_text_string(text_as_evaluation_value);
    return VALUES_1(FIX(result_1));
}

/* PM-MOVE-TO-ACTION-BUTTON */
Object pm_move_to_action_button(string_to_look_for_as_evaluation_value)
    Object string_to_look_for_as_evaluation_value;
{
    Object string_to_look_for;
    volatile Object result_1;
    Object left_qm, top, right, bottom;
    Declare_catch(1);
    Object result;

    x_note_fn_call(244,103);
    string_to_look_for = string_to_look_for_as_evaluation_value;
    result_1 = C_boolean_true;
    if (PUSH_CATCH(Qsuspend_player,0)) {
	result = player_find_action_button(string_to_look_for);
	MVS_4(result,left_qm,top,right,bottom);
	if (left_qm)
	    player_move_to(ltruncate(FIXNUM_ADD(left_qm,right),
		    FIX((SI_Long)2L)),ltruncate(FIXNUM_ADD(top,bottom),
		    FIX((SI_Long)2L)));
	else
	    result_1 = C_boolean_false;
    }
    POP_CATCH(0);
    reclaim_text_string(string_to_look_for_as_evaluation_value);
    return VALUES_1(result_1);
}

/* PM-MOVE-TO-MENU-ITEM */
Object pm_move_to_menu_item(text_as_evaluation_value)
    Object text_as_evaluation_value;
{
    Object text, result_1;
    Declare_catch(1);

    x_note_fn_call(244,104);
    text = text_as_evaluation_value;
    result_1 = C_boolean_true;
    if (PUSH_CATCH(Qsuspend_player,0))
	player_move_to_menu_item(text);
    POP_CATCH(0);
    reclaim_text_string(text_as_evaluation_value);
    return VALUES_1(result_1);
}

/* PM-TABLE-SLOT-VISIBLE-P */
Object pm_table_slot_visible_p(text_as_evaluation_value)
    Object text_as_evaluation_value;
{
    Object text;
    SI_Long result_1;

    x_note_fn_call(244,105);
    text = text_as_evaluation_value;
    result_1 = player_find_attribute_table_value_cell(text) ? (SI_Long)1L :
	     (SI_Long)0L;
    reclaim_text_string(text_as_evaluation_value);
    return VALUES_1(FIX(result_1));
}

/* PM-MOVE-TO-TABLE-SLOT */
Object pm_move_to_table_slot(text_as_evaluation_value)
    Object text_as_evaluation_value;
{
    Object text, result_1;
    Declare_catch(1);

    x_note_fn_call(244,106);
    text = text_as_evaluation_value;
    result_1 = C_boolean_true;
    if (PUSH_CATCH(Qsuspend_player,0))
	player_move_to_attribute_table_slot(text);
    POP_CATCH(0);
    reclaim_text_string(text_as_evaluation_value);
    return VALUES_1(result_1);
}

/* PM-TRANSLATE-CHARACTER-CODE-TO-EVENT-CODE */
Object pm_translate_character_code_to_event_code(text_as_evaluation_value,
	    offset_as_evaluation_value)
    Object text_as_evaluation_value, offset_as_evaluation_value;
{
    Object text, offset, result_1;

    x_note_fn_call(244,107);
    text = text_as_evaluation_value;
    offset = offset_as_evaluation_value;
    result_1 = 
	    player_translate_character_code_to_event_code(FIX(UBYTE_16_ISAREF_1(text,
	    IFIX(offset))));
    reclaim_text_string(text_as_evaluation_value);
    return VALUES_1(result_1);
}

/* PM-KEY-CODE-FROM-SYMBOL */
Object pm_key_code_from_symbol(symbol_as_evaluation_value)
    Object symbol_as_evaluation_value;
{
    Object symbol, result_1;

    x_note_fn_call(244,108);
    symbol = symbol_as_evaluation_value;
    result_1 = key_code_from_symbol(symbol);
    return VALUES_1(result_1);
}

static Object Qfloat_array;        /* float-array */

static Object Qtruth_value;        /* truth-value */

/* PM-BEST-TEXT */
Object pm_best_text()
{
    Object result_1, temp, amf_available_array_cons_qm, amf_array, temp_1;
    Object temp_2, amf_result, new_float, gensymed_symbol;
    double aref_new_value;

    x_note_fn_call(244,109);
    result_1 = Best_text_matched_by_player;
    if (FIXNUMP(result_1))
	temp = result_1;
    else if ( !TRUEP(result_1))
	temp = Evaluation_false_value;
    else if (EQ(result_1,T))
	temp = Evaluation_true_value;
    else if (SYMBOLP(result_1))
	temp = result_1;
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(result_1) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(result_1)) == (SI_Long)1L)
	temp = copy_managed_float(result_1);
    else if (FLOATP(result_1)) {
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
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(result_1);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	temp = new_float;
    }
    else if (INLINE_LONG_VECTOR_P(result_1) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(result_1)) == (SI_Long)1L)
	temp = copy_managed_long(result_1);
    else if (INLINE_LONG_P(result_1) != (SI_Long)0L)
	temp = make_evaluation_long(result_1);
    else if (text_string_p(result_1))
	temp = copy_as_wide_string(result_1);
    else if (CONSP(result_1) && EQ(M_CDR(result_1),Qtruth_value)) {
	gensymed_symbol = M_CAR(result_1);
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
		type_of(result_1));
    return VALUES_1(temp);
}

void player_INIT()
{
    Object result_1, svref_arg_2, gensymed_symbol;
    Object Qpm_best_text, AB_package;
    Object Qfunction_keeps_procedure_environment_valid_qm;
    Object Qpm_key_code_from_symbol;
    Object Qpm_translate_character_code_to_event_code, Qpm_move_to_table_slot;
    Object Qpm_table_slot_visible_p, Qpm_move_to_menu_item;
    Object Qpm_move_to_action_button, Qpm_action_button_visible_p;
    Object Qpm_menu_item_visible_p, Qpm_move_to_text, Qpm_text_visible_p;
    Object Qpm_get_current_location, Qpm_generate_event, Qpm_type_control_x;
    Object Qpm_reset, Qpm_move, Qpm_pop_location, Qpm_push_location;
    Object Qplayer_release_definitions, Qresume_player, list_constant_42;
    Object Qplayer_server_push_control_stack, list_constant_41, Qmain;
    Object list_constant_40, list_constant_39, list_constant_38;
    Object Qplayer_mark_definitions, Qremote_test, Qclear_player;
    Object Qremote_eval_once, Qremote_eval, list_constant_37, Qtype_control_v;
    Object list_constant_36, Qplayer_function, list_constant_35;
    Object Qtype_character, list_constant_34, Qtype_control_t;
    Object list_constant_33, list_constant_32, list_constant_31;
    Object Qtype_control_y, list_constant_30, list_constant_29;
    Object list_constant_28, Qtype_control_x, list_constant_27;
    Object list_constant_26, list_constant_25, Qtype_control_b;
    Object list_constant_24, list_constant_23, list_constant_22;
    Object Qtype_control_s, list_constant_21, list_constant_20;
    Object list_constant_19, Qtype_control_j, list_constant_18;
    Object list_constant_17, list_constant_16, Qtype_entry, list_constant_15;
    Object list_constant_12, list_constant_14, list_constant_13;
    Object Qtype_control_return, list_constant_11, list_constant_10;
    Object list_constant_9, Qplayer_move_to_instance, Qmove_to_instance;
    Object Qplayer_move_to_action_button, Qmove_to_action_button;
    Object Qplayer_move_to_attribute_table_slot, Qmove_to_attribute_table_slot;
    Object Qplayer_move_to_menu_item, Qmove_to_menu_item, Qplayer_move_to_text;
    Object Qmove_to_text, Qplayer_find_instance, Qinstance_visible_p;
    Object Qplayer_find_action_button, Qaction_button_visible_p;
    Object Qplayer_find_attribute_table_value_cell;
    Object Qattribute_table_slot_visible_p;
    Object Qplayer_find_menu_item_containing_string, Qmenu_item_visible_p;
    Object Qplayer_text_visible_p, Qtext_visible_p, Qplayer_instruction_type_1;
    Object Qplayer_type, Qplayer_type_character, Qplayer_move_to_location;
    Object Qmove_to_location, Qplayer_name_location, Qname_location;
    Object Qplayer_pop_location, Qpop_location, Qplayer_push_location;
    Object Qpush_location, Qplayer_move, Qmove, Qplayer_move_to, Qmove_to;
    Object Qplayer_generate_event, Qgenerate_event;
    Object Qplayer_generate_event_and_suspend, Qgenerate_event_and_suspend;
    Object Qplayer_handler_for_add_from_line_of_text_to_current_window;
    Object Qdefault_player_handler_for_icp_messages, Qicp_message_type_code;
    Object Qadd_from_line_of_text_to_current_window;
    Object Qplayer_instruction_reclaim_player_tree;
    Object Qplayer_instruction_wait_until, Qplayer_wait, Qwait;
    Object Qplayer_instruction_let_star, Qab_let_star;
    Object Qplayer_instruction_unbind, Qplayer_instruction_let_star_bind;
    Object Qplayer_instruction_go, Qplayer_instruction_player_tagbody_1;
    Object Qplayer_instruction_tagbody, Qplayer_instruction_if_1, Qif_1;
    Object Qplayer_instruction_if, Qab_if, Qplayer_instruction_progn_1;
    Object Qplayer_instruction_progn, Qplayer_instruction_quote;
    Object Qplayer_instruction_do_call, Qundefine_player_symbol_function;
    Object Qplayer_record_definition, Qset_player_symbol_function;
    Object Kno_initial_value, list_constant_8, string_constant_14;
    Object Qplayer_cons_memory_usage, Qoutstanding_player_conses, Qutilities1;
    Object list_constant_7, Qplayer_cons_counter_vector, Qmake_thread_array;
    Object Kfuncall, list_constant_6, Qavailable_player_conses_tail_vector;
    Object Qavailable_player_conses_vector;

    x_note_fn_call(244,110);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qavailable_player_conses = STATIC_SYMBOL("AVAILABLE-PLAYER-CONSES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_player_conses,
	    Available_player_conses);
    Qutilities1 = STATIC_SYMBOL("UTILITIES1",AB_package);
    record_system_variable(Qavailable_player_conses,Qutilities1,Nil,Qnil,
	    Qt,Qnil,Qnil);
    Qavailable_player_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-PLAYER-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_player_conses_tail,
	    Available_player_conses_tail);
    record_system_variable(Qavailable_player_conses_tail,Qutilities1,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_player_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-PLAYER-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_player_conses_vector,
	    Available_player_conses_vector);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_thread_array = STATIC_SYMBOL("MAKE-THREAD-ARRAY",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    Qnil);
    record_system_variable(Qavailable_player_conses_vector,Qutilities1,
	    list_constant_6,Qnil,Qt,Qnil,Qnil);
    Qavailable_player_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-PLAYER-CONSES-TAIL-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_player_conses_tail_vector,
	    Available_player_conses_tail_vector);
    record_system_variable(Qavailable_player_conses_tail_vector,
	    Qutilities1,list_constant_6,Qnil,Qt,Qnil,Qnil);
    Qplayer_cons_counter_vector = 
	    STATIC_SYMBOL("PLAYER-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qplayer_cons_counter_vector,
	    Player_cons_counter_vector);
    list_constant_7 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    FIX((SI_Long)0L));
    record_system_variable(Qplayer_cons_counter_vector,Qutilities1,
	    list_constant_7,Qnil,Qt,Qnil,Qnil);
    Qplayer_cons_counter = STATIC_SYMBOL("PLAYER-CONS-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qplayer_cons_counter,Player_cons_counter);
    record_system_variable(Qplayer_cons_counter,Qutilities1,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_player_conses = STATIC_SYMBOL("OUTSTANDING-PLAYER-CONSES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_player_conses,
	    STATIC_FUNCTION(outstanding_player_conses,NIL,FALSE,0,0));
    Qplayer_cons_memory_usage = STATIC_SYMBOL("PLAYER-CONS-MEMORY-USAGE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qplayer_cons_memory_usage,
	    STATIC_FUNCTION(player_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_14 = STATIC_STRING("1q83-ivy9k83-iuy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_player_conses);
    push_optimized_constant(Qplayer_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_14));
    Qplayer = STATIC_SYMBOL("PLAYER",AB_package);
    Qplayer_state = STATIC_SYMBOL("PLAYER-STATE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qplayer_state,Player_state);
    Qpaused = STATIC_SYMBOL("PAUSED",AB_package);
    list_constant_8 = STATIC_LIST((SI_Long)2L,Qquote,Qpaused);
    record_system_variable(Qplayer_state,Qplayer,list_constant_8,Qnil,Qnil,
	    Qnil,Qnil);
    Qplayer_control_stack = STATIC_SYMBOL("PLAYER-CONTROL-STACK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qplayer_control_stack,Player_control_stack);
    record_system_variable(Qplayer_control_stack,Qplayer,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qplayer_value_stack = STATIC_SYMBOL("PLAYER-VALUE-STACK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qplayer_value_stack,Player_value_stack);
    record_system_variable(Qplayer_value_stack,Qplayer,Nil,Qnil,Qnil,Qnil,
	    Qnil);
    Qplayer_current_instruction = 
	    STATIC_SYMBOL("PLAYER-CURRENT-INSTRUCTION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qplayer_current_instruction,
	    Player_current_instruction);
    Kno_initial_value = STATIC_SYMBOL("NO-INITIAL-VALUE",Pkeyword);
    record_system_variable(Qplayer_current_instruction,Qplayer,
	    Kno_initial_value,Qnil,Qnil,Qnil,Qnil);
    Qplayer_lexical_binding_stack = 
	    STATIC_SYMBOL("PLAYER-LEXICAL-BINDING-STACK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qplayer_lexical_binding_stack,
	    Player_lexical_binding_stack);
    record_system_variable(Qplayer_lexical_binding_stack,Qplayer,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qplayer_definition_stack = STATIC_SYMBOL("PLAYER-DEFINITION-STACK",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qplayer_definition_stack,
	    Player_definition_stack);
    record_system_variable(Qplayer_definition_stack,Qplayer,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qplayer_location_stack = STATIC_SYMBOL("PLAYER-LOCATION-STACK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qplayer_location_stack,Player_location_stack);
    record_system_variable(Qplayer_location_stack,Qplayer,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qplayer_named_locations = STATIC_SYMBOL("PLAYER-NAMED-LOCATIONS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qplayer_named_locations,Player_named_locations);
    record_system_variable(Qplayer_named_locations,Qplayer,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qsuspend_player = STATIC_SYMBOL("SUSPEND-PLAYER",AB_package);
    SET_SYMBOL_FUNCTION(Qsuspend_player,STATIC_FUNCTION(suspend_player,NIL,
	    FALSE,0,0));
    Qplayer_target_gensym_window_g2_struct_qm = 
	    STATIC_SYMBOL("PLAYER-TARGET-GENSYM-WINDOW-G2-STRUCT\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qplayer_target_gensym_window_g2_struct_qm,
	    Player_target_gensym_window_g2_struct_qm);
    record_system_variable(Qplayer_target_gensym_window_g2_struct_qm,
	    Qplayer,Nil,Qnil,Qnil,Qnil,Qnil);
    Qbest_text_matched_by_player = 
	    STATIC_SYMBOL("BEST-TEXT-MATCHED-BY-PLAYER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbest_text_matched_by_player,
	    Best_text_matched_by_player);
    record_system_variable(Qbest_text_matched_by_player,Qplayer,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qplayer_mouse_x = STATIC_SYMBOL("PLAYER-MOUSE-X",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qplayer_mouse_x,Player_mouse_x);
    record_system_variable(Qplayer_mouse_x,Qplayer,FIX((SI_Long)0L),Qnil,
	    Qnil,Qnil,Qnil);
    Qplayer_mouse_y = STATIC_SYMBOL("PLAYER-MOUSE-Y",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qplayer_mouse_y,Player_mouse_y);
    record_system_variable(Qplayer_mouse_y,Qplayer,FIX((SI_Long)0L),Qnil,
	    Qnil,Qnil,Qnil);
    Qlast_player_mouse_x = STATIC_SYMBOL("LAST-PLAYER-MOUSE-X",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlast_player_mouse_x,Last_player_mouse_x);
    record_system_variable(Qlast_player_mouse_x,Qplayer,FIX((SI_Long)0L),
	    Qnil,Qnil,Qnil,Qnil);
    Qlast_player_mouse_y = STATIC_SYMBOL("LAST-PLAYER-MOUSE-Y",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlast_player_mouse_y,Last_player_mouse_y);
    record_system_variable(Qlast_player_mouse_y,Qplayer,FIX((SI_Long)0L),
	    Qnil,Qnil,Qnil,Qnil);
    Qlast_player_event_time = STATIC_SYMBOL("LAST-PLAYER-EVENT-TIME",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlast_player_event_time,Last_player_event_time);
    record_system_variable(Qlast_player_event_time,Qplayer,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qplayer_pace = STATIC_SYMBOL("PLAYER-PACE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qplayer_pace,Player_pace);
    record_system_variable(Qplayer_pace,Qplayer,FIX((SI_Long)2L),Qnil,Qnil,
	    Qnil,Qnil);
    string_constant = STATIC_STRING("~&Player Error: ~A~%");
    Qplayer_symbol_function = STATIC_SYMBOL("PLAYER-SYMBOL-FUNCTION",
	    AB_package);
    Qset_player_symbol_function = 
	    STATIC_SYMBOL("SET-PLAYER-SYMBOL-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qset_player_symbol_function,
	    STATIC_FUNCTION(set_player_symbol_function,NIL,FALSE,2,2));
    Qab_defun = STATIC_SYMBOL("DEFUN",AB_package);
    Qplayer_record_definition = STATIC_SYMBOL("PLAYER-RECORD-DEFINITION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qplayer_record_definition,
	    STATIC_FUNCTION(player_record_definition,NIL,FALSE,2,2));
    Qundefine_player_symbol_function = 
	    STATIC_SYMBOL("UNDEFINE-PLAYER-SYMBOL-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qundefine_player_symbol_function,
	    STATIC_FUNCTION(undefine_player_symbol_function,NIL,FALSE,1,1));
    Qrunning = STATIC_SYMBOL("RUNNING",AB_package);
    Qplayer_macro_function = STATIC_SYMBOL("PLAYER-MACRO-FUNCTION",AB_package);
    string_constant_1 = STATIC_STRING("undefined player function ~S");
    Qdo_call = STATIC_SYMBOL("DO-CALL",AB_package);
    Qplayer_instruction_do_call = 
	    STATIC_SYMBOL("PLAYER-INSTRUCTION-DO-CALL",AB_package);
    SET_SYMBOL_FUNCTION(Qplayer_instruction_do_call,
	    STATIC_FUNCTION(player_instruction_do_call,NIL,FALSE,1,1));
    set_get(Qdo_call,Qplayer_macro_function,Qplayer_instruction_do_call);
    Qreclaim_player_tree = STATIC_SYMBOL("RECLAIM-PLAYER-TREE",AB_package);
    string_constant_2 = 
	    STATIC_STRING("Player call failed since actual parameters don\'t match lambda list");
    Qunbind = STATIC_SYMBOL("UNBIND",AB_package);
    Qplayer_instruction_quote = STATIC_SYMBOL("PLAYER-INSTRUCTION-QUOTE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qplayer_instruction_quote,
	    STATIC_FUNCTION(player_instruction_quote,NIL,FALSE,1,1));
    set_get(Qquote,Qplayer_macro_function,Qplayer_instruction_quote);
    Qprogn_1 = STATIC_SYMBOL("PROGN-1",AB_package);
    Qplayer_instruction_progn = STATIC_SYMBOL("PLAYER-INSTRUCTION-PROGN",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qplayer_instruction_progn,
	    STATIC_FUNCTION(player_instruction_progn,NIL,FALSE,1,1));
    set_get(Qprogn,Qplayer_macro_function,Qplayer_instruction_progn);
    Qplayer_instruction_progn_1 = 
	    STATIC_SYMBOL("PLAYER-INSTRUCTION-PROGN-1",AB_package);
    SET_SYMBOL_FUNCTION(Qplayer_instruction_progn_1,
	    STATIC_FUNCTION(player_instruction_progn_1,NIL,FALSE,1,1));
    set_get(Qprogn_1,Qplayer_macro_function,Qplayer_instruction_progn_1);
    Qif_1 = STATIC_SYMBOL("IF-1",AB_package);
    list_constant = STATIC_CONS(Qif_1,Qnil);
    Qab_if = STATIC_SYMBOL("IF",AB_package);
    Qplayer_instruction_if = STATIC_SYMBOL("PLAYER-INSTRUCTION-IF",AB_package);
    SET_SYMBOL_FUNCTION(Qplayer_instruction_if,
	    STATIC_FUNCTION(player_instruction_if,NIL,FALSE,1,1));
    set_get(Qab_if,Qplayer_macro_function,Qplayer_instruction_if);
    Qplayer_instruction_if_1 = STATIC_SYMBOL("PLAYER-INSTRUCTION-IF-1",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qplayer_instruction_if_1,
	    STATIC_FUNCTION(player_instruction_if_1,NIL,FALSE,1,1));
    set_get(Qif_1,Qplayer_macro_function,Qplayer_instruction_if_1);
    Qplayer_tagbody_1 = STATIC_SYMBOL("PLAYER-TAGBODY-1",AB_package);
    Qplayer_instruction_tagbody = 
	    STATIC_SYMBOL("PLAYER-INSTRUCTION-TAGBODY",AB_package);
    SET_SYMBOL_FUNCTION(Qplayer_instruction_tagbody,
	    STATIC_FUNCTION(player_instruction_tagbody,NIL,FALSE,1,1));
    set_get(Qtagbody,Qplayer_macro_function,Qplayer_instruction_tagbody);
    Qplayer_instruction_player_tagbody_1 = 
	    STATIC_SYMBOL("PLAYER-INSTRUCTION-PLAYER-TAGBODY-1",AB_package);
    SET_SYMBOL_FUNCTION(Qplayer_instruction_player_tagbody_1,
	    STATIC_FUNCTION(player_instruction_player_tagbody_1,NIL,FALSE,
	    1,1));
    set_get(Qplayer_tagbody_1,Qplayer_macro_function,
	    Qplayer_instruction_player_tagbody_1);
    string_constant_3 = 
	    STATIC_STRING("Player found no label ~S to go to in enclosing tagbodies.");
    Qplayer_instruction_go = STATIC_SYMBOL("PLAYER-INSTRUCTION-GO",AB_package);
    SET_SYMBOL_FUNCTION(Qplayer_instruction_go,
	    STATIC_FUNCTION(player_instruction_go,NIL,FALSE,1,1));
    set_get(Qgo,Qplayer_macro_function,Qplayer_instruction_go);
    Qlet_star_bind = STATIC_SYMBOL("LET*-BIND",AB_package);
    Qplayer_instruction_let_star_bind = 
	    STATIC_SYMBOL("PLAYER-INSTRUCTION-LET*-BIND",AB_package);
    SET_SYMBOL_FUNCTION(Qplayer_instruction_let_star_bind,
	    STATIC_FUNCTION(player_instruction_let_star_bind,NIL,FALSE,1,1));
    set_get(Qlet_star_bind,Qplayer_macro_function,
	    Qplayer_instruction_let_star_bind);
    Qplayer_instruction_unbind = STATIC_SYMBOL("PLAYER-INSTRUCTION-UNBIND",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qplayer_instruction_unbind,
	    STATIC_FUNCTION(player_instruction_unbind,NIL,FALSE,1,1));
    set_get(Qunbind,Qplayer_macro_function,Qplayer_instruction_unbind);
    Qab_let_star = STATIC_SYMBOL("LET*",AB_package);
    Qplayer_instruction_let_star = STATIC_SYMBOL("PLAYER-INSTRUCTION-LET*",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qplayer_instruction_let_star,
	    STATIC_FUNCTION(player_instruction_let_star,NIL,FALSE,1,1));
    set_get(Qab_let_star,Qplayer_macro_function,Qplayer_instruction_let_star);
    Qwait = STATIC_SYMBOL("WAIT",AB_package);
    Qplayer_wait = STATIC_SYMBOL("PLAYER-WAIT",AB_package);
    set_get(Qwait,Qplayer_symbol_function,Qplayer_wait);
    Qwait_until = STATIC_SYMBOL("WAIT-UNTIL",AB_package);
    SET_SYMBOL_FUNCTION(Qplayer_wait,STATIC_FUNCTION(player_wait,NIL,FALSE,
	    1,1));
    Qplayer_instruction_wait_until = 
	    STATIC_SYMBOL("PLAYER-INSTRUCTION-WAIT-UNTIL",AB_package);
    SET_SYMBOL_FUNCTION(Qplayer_instruction_wait_until,
	    STATIC_FUNCTION(player_instruction_wait_until,NIL,FALSE,1,1));
    set_get(Qwait_until,Qplayer_macro_function,Qplayer_instruction_wait_until);
    Qplayer_instruction_reclaim_player_tree = 
	    STATIC_SYMBOL("PLAYER-INSTRUCTION-RECLAIM-PLAYER-TREE",AB_package);
    SET_SYMBOL_FUNCTION(Qplayer_instruction_reclaim_player_tree,
	    STATIC_FUNCTION(player_instruction_reclaim_player_tree,NIL,
	    FALSE,1,1));
    set_get(Qreclaim_player_tree,Qplayer_macro_function,
	    Qplayer_instruction_reclaim_player_tree);
    Qdefault_player_handler_for_icp_messages = 
	    STATIC_SYMBOL("DEFAULT-PLAYER-HANDLER-FOR-ICP-MESSAGES",
	    AB_package);
    Qadd_from_line_of_text_to_current_window = 
	    STATIC_SYMBOL("ADD-FROM-LINE-OF-TEXT-TO-CURRENT-WINDOW",
	    AB_package);
    Qicp_message_type_code = STATIC_SYMBOL("ICP-MESSAGE-TYPE-CODE",AB_package);
    Qplayer_handler_for_add_from_line_of_text_to_current_window = 
	    STATIC_SYMBOL("PLAYER-HANDLER-FOR-ADD-FROM-LINE-OF-TEXT-TO-CURRENT-WINDOW",
	    AB_package);
    if (Icp_player_message_handler_array == UNBOUND) {
	result_1 = make_array(3,FIX((SI_Long)750L),Kinitial_element,
		Qdefault_player_handler_for_icp_messages);
	svref_arg_2 = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qadd_from_line_of_text_to_current_window),
		Qicp_message_type_code);
	SVREF(result_1,svref_arg_2) = 
		Qplayer_handler_for_add_from_line_of_text_to_current_window;
	Icp_player_message_handler_array = result_1;
    }
    SET_SYMBOL_FUNCTION(Qdefault_player_handler_for_icp_messages,
	    STATIC_FUNCTION(default_player_handler_for_icp_messages,NIL,
	    TRUE,0,16));
    if (Current_best_match_for_eyes == UNBOUND)
	Current_best_match_for_eyes = Nil;
    if (Current_text_focus_for_eyes_qm == UNBOUND)
	Current_text_focus_for_eyes_qm = Nil;
    if (Current_x_for_eyes_qm == UNBOUND)
	Current_x_for_eyes_qm = Nil;
    if (Current_y_for_eyes_qm == UNBOUND)
	Current_y_for_eyes_qm = Nil;
    if (Lower_match_rank_for_player_eyes_p == UNBOUND)
	Lower_match_rank_for_player_eyes_p = Nil;
    Qchar_equalw_function = STATIC_SYMBOL("CHAR-EQUALW-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qchar_equalw_function,
	    STATIC_FUNCTION(char_equalw_function,NIL,FALSE,2,2));
    string_constant_4 = STATIC_STRING("found: ~s ~s ~s");
    SET_SYMBOL_FUNCTION(Qplayer_handler_for_add_from_line_of_text_to_current_window,
	    STATIC_FUNCTION(player_handler_for_add_from_line_of_text_to_current_window,
	    NIL,FALSE,13,13));
    Qprinter = STATIC_SYMBOL("PRINTER",AB_package);
    Kdraw_as_soon_as_possible = STATIC_SYMBOL("DRAW-AS-SOON-AS-POSSIBLE",
	    Pkeyword);
    Qmenu_workspace = STATIC_SYMBOL("MENU-WORKSPACE",AB_package);
    Qaction_button = STATIC_SYMBOL("ACTION-BUTTON",AB_package);
    Qgenerate_event_and_suspend = 
	    STATIC_SYMBOL("GENERATE-EVENT-AND-SUSPEND",AB_package);
    Qplayer_generate_event_and_suspend = 
	    STATIC_SYMBOL("PLAYER-GENERATE-EVENT-AND-SUSPEND",AB_package);
    SET_SYMBOL_FUNCTION(Qplayer_generate_event_and_suspend,
	    STATIC_FUNCTION(player_generate_event_and_suspend,NIL,FALSE,1,1));
    set_get(Qgenerate_event_and_suspend,Qplayer_symbol_function,
	    Qplayer_generate_event_and_suspend);
    Qgenerate_event = STATIC_SYMBOL("GENERATE-EVENT",AB_package);
    Qplayer_generate_event = STATIC_SYMBOL("PLAYER-GENERATE-EVENT",AB_package);
    SET_SYMBOL_FUNCTION(Qplayer_generate_event,
	    STATIC_FUNCTION(player_generate_event,NIL,FALSE,1,1));
    set_get(Qgenerate_event,Qplayer_symbol_function,Qplayer_generate_event);
    Qmove_to = STATIC_SYMBOL("MOVE-TO",AB_package);
    Qplayer_move_to = STATIC_SYMBOL("PLAYER-MOVE-TO",AB_package);
    set_get(Qmove_to,Qplayer_symbol_function,Qplayer_move_to);
    SET_SYMBOL_FUNCTION(Qplayer_move_to,STATIC_FUNCTION(player_move_to,NIL,
	    FALSE,2,2));
    Qmove = STATIC_SYMBOL("MOVE",AB_package);
    Qplayer_move = STATIC_SYMBOL("PLAYER-MOVE",AB_package);
    set_get(Qmove,Qplayer_symbol_function,Qplayer_move);
    SET_SYMBOL_FUNCTION(Qplayer_move,STATIC_FUNCTION(player_move,NIL,FALSE,
	    2,2));
    Qpush_location = STATIC_SYMBOL("PUSH-LOCATION",AB_package);
    Qplayer_push_location = STATIC_SYMBOL("PLAYER-PUSH-LOCATION",AB_package);
    set_get(Qpush_location,Qplayer_symbol_function,Qplayer_push_location);
    SET_SYMBOL_FUNCTION(Qplayer_push_location,
	    STATIC_FUNCTION(player_push_location,NIL,FALSE,0,0));
    Qpop_location = STATIC_SYMBOL("POP-LOCATION",AB_package);
    Qplayer_pop_location = STATIC_SYMBOL("PLAYER-POP-LOCATION",AB_package);
    set_get(Qpop_location,Qplayer_symbol_function,Qplayer_pop_location);
    SET_SYMBOL_FUNCTION(Qplayer_pop_location,
	    STATIC_FUNCTION(player_pop_location,NIL,FALSE,0,0));
    Qname_location = STATIC_SYMBOL("NAME-LOCATION",AB_package);
    Qplayer_name_location = STATIC_SYMBOL("PLAYER-NAME-LOCATION",AB_package);
    set_get(Qname_location,Qplayer_symbol_function,Qplayer_name_location);
    SET_SYMBOL_FUNCTION(Qplayer_name_location,
	    STATIC_FUNCTION(player_name_location,NIL,FALSE,1,1));
    Qmove_to_location = STATIC_SYMBOL("MOVE-TO-LOCATION",AB_package);
    Qplayer_move_to_location = STATIC_SYMBOL("PLAYER-MOVE-TO-LOCATION",
	    AB_package);
    set_get(Qmove_to_location,Qplayer_symbol_function,
	    Qplayer_move_to_location);
    string_constant_5 = 
	    STATIC_STRING("Unknown location passed to move-to-location.");
    SET_SYMBOL_FUNCTION(Qplayer_move_to_location,
	    STATIC_FUNCTION(player_move_to_location,NIL,FALSE,1,1));
    Qtype_character = STATIC_SYMBOL("TYPE-CHARACTER",AB_package);
    Qplayer_type_character = STATIC_SYMBOL("PLAYER-TYPE-CHARACTER",AB_package);
    set_get(Qtype_character,Qplayer_symbol_function,Qplayer_type_character);
    SET_SYMBOL_FUNCTION(Qplayer_type_character,
	    STATIC_FUNCTION(player_type_character,NIL,FALSE,1,1));
    Qplayer_type = STATIC_SYMBOL("PLAYER-TYPE",AB_package);
    set_get(Qtype,Qplayer_symbol_function,Qplayer_type);
    Qtype_1 = STATIC_SYMBOL("TYPE-1",AB_package);
    SET_SYMBOL_FUNCTION(Qplayer_type,STATIC_FUNCTION(player_type,NIL,FALSE,
	    1,1));
    Qplayer_instruction_type_1 = STATIC_SYMBOL("PLAYER-INSTRUCTION-TYPE-1",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qplayer_instruction_type_1,
	    STATIC_FUNCTION(player_instruction_type_1,NIL,FALSE,1,1));
    set_get(Qtype_1,Qplayer_macro_function,Qplayer_instruction_type_1);
    Qtext_visible_p = STATIC_SYMBOL("TEXT-VISIBLE-P",AB_package);
    SET_SYMBOL_FUNCTION(Qtext_visible_p,STATIC_FUNCTION(text_visible_p,NIL,
	    FALSE,4,4));
    Qplayer_text_visible_p = STATIC_SYMBOL("PLAYER-TEXT-VISIBLE-P",AB_package);
    set_get(Qtext_visible_p,Qplayer_symbol_function,Qplayer_text_visible_p);
    string_constant_6 = STATIC_STRING("player-text-visible-p: ~s");
    SET_SYMBOL_FUNCTION(Qplayer_text_visible_p,
	    STATIC_FUNCTION(player_text_visible_p,NIL,FALSE,1,1));
    Qmenu_item_visible_p = STATIC_SYMBOL("MENU-ITEM-VISIBLE-P",AB_package);
    Qplayer_find_menu_item_containing_string = 
	    STATIC_SYMBOL("PLAYER-FIND-MENU-ITEM-CONTAINING-STRING",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qplayer_find_menu_item_containing_string,
	    STATIC_FUNCTION(player_find_menu_item_containing_string,NIL,
	    FALSE,1,1));
    set_get(Qmenu_item_visible_p,Qplayer_symbol_function,
	    Qplayer_find_menu_item_containing_string);
    Qattribute_table_slot_visible_p = 
	    STATIC_SYMBOL("ATTRIBUTE-TABLE-SLOT-VISIBLE-P",AB_package);
    Qplayer_find_attribute_table_value_cell = 
	    STATIC_SYMBOL("PLAYER-FIND-ATTRIBUTE-TABLE-VALUE-CELL",AB_package);
    SET_SYMBOL_FUNCTION(Qplayer_find_attribute_table_value_cell,
	    STATIC_FUNCTION(player_find_attribute_table_value_cell,NIL,
	    FALSE,1,1));
    set_get(Qattribute_table_slot_visible_p,Qplayer_symbol_function,
	    Qplayer_find_attribute_table_value_cell);
    Qaction_button_visible_p = STATIC_SYMBOL("ACTION-BUTTON-VISIBLE-P",
	    AB_package);
    Qplayer_find_action_button = STATIC_SYMBOL("PLAYER-FIND-ACTION-BUTTON",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qplayer_find_action_button,
	    STATIC_FUNCTION(player_find_action_button,NIL,FALSE,1,1));
    set_get(Qaction_button_visible_p,Qplayer_symbol_function,
	    Qplayer_find_action_button);
    Qinstance_visible_p = STATIC_SYMBOL("INSTANCE-VISIBLE-P",AB_package);
    Qplayer_find_instance = STATIC_SYMBOL("PLAYER-FIND-INSTANCE",AB_package);
    SET_SYMBOL_FUNCTION(Qplayer_find_instance,
	    STATIC_FUNCTION(player_find_instance,NIL,FALSE,1,1));
    set_get(Qinstance_visible_p,Qplayer_symbol_function,Qplayer_find_instance);
    Qmove_to_text = STATIC_SYMBOL("MOVE-TO-TEXT",AB_package);
    Qplayer_move_to_text = STATIC_SYMBOL("PLAYER-MOVE-TO-TEXT",AB_package);
    set_get(Qmove_to_text,Qplayer_symbol_function,Qplayer_move_to_text);
    string_constant_7 = STATIC_STRING("player-move-to-text: ~s ~s ~s");
    string_constant_8 = STATIC_STRING("Player couldn\'t find text.");
    SET_SYMBOL_FUNCTION(Qplayer_move_to_text,
	    STATIC_FUNCTION(player_move_to_text,NIL,FALSE,1,1));
    Qmove_to_menu_item = STATIC_SYMBOL("MOVE-TO-MENU-ITEM",AB_package);
    Qplayer_move_to_menu_item = STATIC_SYMBOL("PLAYER-MOVE-TO-MENU-ITEM",
	    AB_package);
    set_get(Qmove_to_menu_item,Qplayer_symbol_function,
	    Qplayer_move_to_menu_item);
    string_constant_9 = STATIC_STRING("player-move-to-menu-item: ~s");
    string_constant_10 = STATIC_STRING("Player couldn\'t find menu item.");
    SET_SYMBOL_FUNCTION(Qplayer_move_to_menu_item,
	    STATIC_FUNCTION(player_move_to_menu_item,NIL,FALSE,1,1));
    Qmove_to_attribute_table_slot = 
	    STATIC_SYMBOL("MOVE-TO-ATTRIBUTE-TABLE-SLOT",AB_package);
    Qplayer_move_to_attribute_table_slot = 
	    STATIC_SYMBOL("PLAYER-MOVE-TO-ATTRIBUTE-TABLE-SLOT",AB_package);
    set_get(Qmove_to_attribute_table_slot,Qplayer_symbol_function,
	    Qplayer_move_to_attribute_table_slot);
    string_constant_11 = 
	    STATIC_STRING("player-move-to-attribute-table-slot: ~s");
    string_constant_12 = 
	    STATIC_STRING("Player couldn\'t find attribute table slot.");
    SET_SYMBOL_FUNCTION(Qplayer_move_to_attribute_table_slot,
	    STATIC_FUNCTION(player_move_to_attribute_table_slot,NIL,FALSE,
	    1,1));
    Qmove_to_action_button = STATIC_SYMBOL("MOVE-TO-ACTION-BUTTON",AB_package);
    Qplayer_move_to_action_button = 
	    STATIC_SYMBOL("PLAYER-MOVE-TO-ACTION-BUTTON",AB_package);
    set_get(Qmove_to_action_button,Qplayer_symbol_function,
	    Qplayer_move_to_action_button);
    string_constant_13 = STATIC_STRING("player-move-to-action-button: ~s");
    SET_SYMBOL_FUNCTION(Qplayer_move_to_action_button,
	    STATIC_FUNCTION(player_move_to_action_button,NIL,FALSE,1,1));
    Qmove_to_instance = STATIC_SYMBOL("MOVE-TO-INSTANCE",AB_package);
    Qplayer_move_to_instance = STATIC_SYMBOL("PLAYER-MOVE-TO-INSTANCE",
	    AB_package);
    set_get(Qmove_to_instance,Qplayer_symbol_function,
	    Qplayer_move_to_instance);
    SET_SYMBOL_FUNCTION(Qplayer_move_to_instance,
	    STATIC_FUNCTION(player_move_to_instance,NIL,FALSE,1,1));
    set_get(Qprint,Qplayer_symbol_function,Qprint);
    Qtype_control_return = STATIC_SYMBOL("TYPE-CONTROL-RETURN",AB_package);
    undefine_player_symbol_function(Qtype_control_return);
    player_record_definition(Qab_defun,Qtype_control_return);
    Qplayer_function = STATIC_SYMBOL("PLAYER-FUNCTION",AB_package);
    list_constant_9 = STATIC_LIST((SI_Long)2L,Qtype_character,CHR('\r'));
    list_constant_10 = STATIC_LIST((SI_Long)2L,Qprogn,list_constant_9);
    list_constant_11 = STATIC_LIST((SI_Long)3L,Qplayer_function,Qnil,
	    list_constant_10);
    set_player_symbol_function(Qtype_control_return,list_constant_11);
    Qtype_entry = STATIC_SYMBOL("TYPE-ENTRY",AB_package);
    undefine_player_symbol_function(Qtype_entry);
    player_record_definition(Qab_defun,Qtype_entry);
    list_constant_12 = STATIC_CONS(Qstring,Qnil);
    list_constant_13 = STATIC_CONS(Qtype,list_constant_12);
    list_constant_14 = STATIC_CONS(Qtype_control_return,Qnil);
    list_constant_15 = STATIC_LIST((SI_Long)3L,Qprogn,list_constant_13,
	    list_constant_14);
    list_constant_16 = STATIC_LIST((SI_Long)3L,Qplayer_function,
	    list_constant_12,list_constant_15);
    set_player_symbol_function(Qtype_entry,list_constant_16);
    Qtype_control_j = STATIC_SYMBOL("TYPE-CONTROL-J",AB_package);
    undefine_player_symbol_function(Qtype_control_j);
    player_record_definition(Qab_defun,Qtype_control_j);
    list_constant_17 = STATIC_LIST((SI_Long)2L,Qtype_character,CHR('\n'));
    list_constant_18 = STATIC_LIST((SI_Long)2L,Qprogn,list_constant_17);
    list_constant_19 = STATIC_LIST((SI_Long)3L,Qplayer_function,Qnil,
	    list_constant_18);
    set_player_symbol_function(Qtype_control_j,list_constant_19);
    Qtype_control_s = STATIC_SYMBOL("TYPE-CONTROL-S",AB_package);
    undefine_player_symbol_function(Qtype_control_s);
    player_record_definition(Qab_defun,Qtype_control_s);
    list_constant_20 = STATIC_LIST((SI_Long)2L,Qtype_character,CHR('\023'));
    list_constant_21 = STATIC_LIST((SI_Long)2L,Qprogn,list_constant_20);
    list_constant_22 = STATIC_LIST((SI_Long)3L,Qplayer_function,Qnil,
	    list_constant_21);
    set_player_symbol_function(Qtype_control_s,list_constant_22);
    Qtype_control_b = STATIC_SYMBOL("TYPE-CONTROL-B",AB_package);
    undefine_player_symbol_function(Qtype_control_b);
    player_record_definition(Qab_defun,Qtype_control_b);
    list_constant_23 = STATIC_LIST((SI_Long)2L,Qtype_character,CHR('\002'));
    list_constant_24 = STATIC_LIST((SI_Long)2L,Qprogn,list_constant_23);
    list_constant_25 = STATIC_LIST((SI_Long)3L,Qplayer_function,Qnil,
	    list_constant_24);
    set_player_symbol_function(Qtype_control_b,list_constant_25);
    Qtype_control_x = STATIC_SYMBOL("TYPE-CONTROL-X",AB_package);
    undefine_player_symbol_function(Qtype_control_x);
    player_record_definition(Qab_defun,Qtype_control_x);
    list_constant_26 = STATIC_LIST((SI_Long)2L,Qtype_character,CHR('\030'));
    list_constant_27 = STATIC_LIST((SI_Long)2L,Qprogn,list_constant_26);
    list_constant_28 = STATIC_LIST((SI_Long)3L,Qplayer_function,Qnil,
	    list_constant_27);
    set_player_symbol_function(Qtype_control_x,list_constant_28);
    Qtype_control_y = STATIC_SYMBOL("TYPE-CONTROL-Y",AB_package);
    undefine_player_symbol_function(Qtype_control_y);
    player_record_definition(Qab_defun,Qtype_control_y);
    list_constant_29 = STATIC_LIST((SI_Long)2L,Qtype_character,CHR('\031'));
    list_constant_30 = STATIC_LIST((SI_Long)2L,Qprogn,list_constant_29);
    list_constant_31 = STATIC_LIST((SI_Long)3L,Qplayer_function,Qnil,
	    list_constant_30);
    set_player_symbol_function(Qtype_control_y,list_constant_31);
    Qtype_control_t = STATIC_SYMBOL("TYPE-CONTROL-T",AB_package);
    undefine_player_symbol_function(Qtype_control_t);
    player_record_definition(Qab_defun,Qtype_control_t);
    list_constant_32 = STATIC_LIST((SI_Long)2L,Qtype_character,CHR('\024'));
    list_constant_33 = STATIC_LIST((SI_Long)2L,Qprogn,list_constant_32);
    list_constant_34 = STATIC_LIST((SI_Long)3L,Qplayer_function,Qnil,
	    list_constant_33);
    set_player_symbol_function(Qtype_control_t,list_constant_34);
    Qtype_control_v = STATIC_SYMBOL("TYPE-CONTROL-V",AB_package);
    undefine_player_symbol_function(Qtype_control_v);
    player_record_definition(Qab_defun,Qtype_control_v);
    list_constant_35 = STATIC_LIST((SI_Long)2L,Qtype_character,CHR('\026'));
    list_constant_36 = STATIC_LIST((SI_Long)2L,Qprogn,list_constant_35);
    list_constant_37 = STATIC_LIST((SI_Long)3L,Qplayer_function,Qnil,
	    list_constant_36);
    set_player_symbol_function(Qtype_control_v,list_constant_37);
    Qg2_window = STATIC_SYMBOL("G2-WINDOW",AB_package);
    Qlocal = STATIC_SYMBOL("LOCAL",AB_package);
    Qg2_window_management_type = STATIC_SYMBOL("G2-WINDOW-MANAGEMENT-TYPE",
	    AB_package);
    Qplayer_icp_connection = STATIC_SYMBOL("PLAYER-ICP-CONNECTION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qplayer_icp_connection,Player_icp_connection);
    record_system_variable(Qplayer_icp_connection,Qplayer,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qtelewindows = STATIC_SYMBOL("TELEWINDOWS",AB_package);
    Qremote_eval = STATIC_SYMBOL("REMOTE-EVAL",AB_package);
    SET_SYMBOL_FUNCTION(Qremote_eval,STATIC_FUNCTION(remote_eval,NIL,FALSE,
	    1,1));
    Qremote_eval_once = STATIC_SYMBOL("REMOTE-EVAL-ONCE",AB_package);
    SET_SYMBOL_FUNCTION(Qremote_eval_once,STATIC_FUNCTION(remote_eval_once,
	    NIL,FALSE,4,4));
    Qtcp_ip = STATIC_SYMBOL("TCP-IP",AB_package);
    Qclear_player = STATIC_SYMBOL("CLEAR-PLAYER",AB_package);
    SET_SYMBOL_FUNCTION(Qclear_player,STATIC_FUNCTION(clear_player,NIL,
	    FALSE,0,0));
    list_constant_1 = STATIC_CONS(Qclear_player,Qnil);
    Qplayer_mark_definitions = STATIC_SYMBOL("PLAYER-MARK-DEFINITIONS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qplayer_mark_definitions,
	    STATIC_FUNCTION(player_mark_definitions,NIL,FALSE,1,1));
    Qremote_test = STATIC_SYMBOL("REMOTE-TEST",AB_package);
    list_constant_38 = STATIC_LIST((SI_Long)2L,Qquote,Qremote_test);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qplayer_mark_definitions,
	    list_constant_38);
    Qplayer_server_push_control_stack = 
	    STATIC_SYMBOL("PLAYER-SERVER-PUSH-CONTROL-STACK",AB_package);
    SET_SYMBOL_FUNCTION(Qplayer_server_push_control_stack,
	    STATIC_FUNCTION(player_server_push_control_stack,NIL,FALSE,1,1));
    Qplayer_release_definitions = 
	    STATIC_SYMBOL("PLAYER-RELEASE-DEFINITIONS",AB_package);
    SET_SYMBOL_FUNCTION(Qplayer_release_definitions,
	    STATIC_FUNCTION(player_release_definitions,NIL,FALSE,1,1));
    list_constant_39 = STATIC_LIST((SI_Long)2L,Qplayer_release_definitions,Qt);
    list_constant_40 = STATIC_LIST((SI_Long)2L,Qquote,list_constant_39);
    list_constant_3 = STATIC_LIST((SI_Long)2L,
	    Qplayer_server_push_control_stack,list_constant_40);
    Qmain = STATIC_SYMBOL("MAIN",AB_package);
    list_constant_41 = STATIC_CONS(Qmain,Qnil);
    list_constant_42 = STATIC_LIST((SI_Long)2L,Qquote,list_constant_41);
    list_constant_4 = STATIC_LIST((SI_Long)2L,
	    Qplayer_server_push_control_stack,list_constant_42);
    Qresume_player = STATIC_SYMBOL("RESUME-PLAYER",AB_package);
    SET_SYMBOL_FUNCTION(Qresume_player,STATIC_FUNCTION(resume_player,NIL,
	    FALSE,0,0));
    list_constant_5 = STATIC_CONS(Qresume_player,Qnil);
    Qguardian = STATIC_SYMBOL("GUARDIAN",AB_package);
    SET_SYMBOL_FUNCTION(Qguardian,STATIC_FUNCTION(guardian,NIL,FALSE,0,0));
    set_get(Qplayer_release_definitions,Qplayer_symbol_function,
	    Qplayer_release_definitions);
    set_get(Qrandom,Qplayer_symbol_function,Qrandom);
    C_boolean_false = FIX((SI_Long)0L);
    C_boolean_true = FIX((SI_Long)1L);
    Qpm_push_location = STATIC_SYMBOL("PM-PUSH-LOCATION",AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qpm_push_location,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qpm_push_location,STATIC_FUNCTION(pm_push_location,
	    NIL,FALSE,0,0));
    Qpm_pop_location = STATIC_SYMBOL("PM-POP-LOCATION",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qpm_pop_location,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qpm_pop_location,STATIC_FUNCTION(pm_pop_location,
	    NIL,FALSE,0,0));
    Qpm_move = STATIC_SYMBOL("PM-MOVE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qpm_move,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qpm_move,STATIC_FUNCTION(pm_move,NIL,FALSE,2,2));
    Qpm_reset = STATIC_SYMBOL("PM-RESET",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qpm_reset,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qpm_reset,STATIC_FUNCTION(pm_reset,NIL,FALSE,0,0));
    Qpm_type_control_x = STATIC_SYMBOL("PM-TYPE-CONTROL-X",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qpm_type_control_x,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qpm_type_control_x,
	    STATIC_FUNCTION(pm_type_control_x,NIL,FALSE,0,0));
    Qpm_generate_event = STATIC_SYMBOL("PM-GENERATE-EVENT",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qpm_generate_event,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qmouse_down = STATIC_SYMBOL("MOUSE-DOWN",AB_package);
    Qmouse_up = STATIC_SYMBOL("MOUSE-UP",AB_package);
    Qmouse_motion = STATIC_SYMBOL("MOUSE-MOTION",AB_package);
    Qkeystroke = STATIC_SYMBOL("KEYSTROKE",AB_package);
    Qkludge = STATIC_SYMBOL("KLUDGE",AB_package);
    SET_SYMBOL_FUNCTION(Qpm_generate_event,
	    STATIC_FUNCTION(pm_generate_event,NIL,FALSE,4,4));
    Qpm_get_current_location = STATIC_SYMBOL("PM-GET-CURRENT-LOCATION",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qpm_get_current_location,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qpm_get_current_location,
	    STATIC_FUNCTION(pm_get_current_location,NIL,FALSE,0,0));
    Qpm_text_visible_p = STATIC_SYMBOL("PM-TEXT-VISIBLE-P",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qpm_text_visible_p,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qpm_text_visible_p,
	    STATIC_FUNCTION(pm_text_visible_p,NIL,FALSE,1,1));
    Qpm_move_to_text = STATIC_SYMBOL("PM-MOVE-TO-TEXT",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qpm_move_to_text,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qpm_move_to_text,STATIC_FUNCTION(pm_move_to_text,
	    NIL,FALSE,1,1));
    Qpm_menu_item_visible_p = STATIC_SYMBOL("PM-MENU-ITEM-VISIBLE-P",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qpm_menu_item_visible_p,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qpm_menu_item_visible_p,
	    STATIC_FUNCTION(pm_menu_item_visible_p,NIL,FALSE,1,1));
    Qpm_action_button_visible_p = 
	    STATIC_SYMBOL("PM-ACTION-BUTTON-VISIBLE-P",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qpm_action_button_visible_p,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qpm_action_button_visible_p,
	    STATIC_FUNCTION(pm_action_button_visible_p,NIL,FALSE,1,1));
    Qpm_move_to_action_button = STATIC_SYMBOL("PM-MOVE-TO-ACTION-BUTTON",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qpm_move_to_action_button,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qpm_move_to_action_button,
	    STATIC_FUNCTION(pm_move_to_action_button,NIL,FALSE,1,1));
    Qpm_move_to_menu_item = STATIC_SYMBOL("PM-MOVE-TO-MENU-ITEM",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qpm_move_to_menu_item,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qpm_move_to_menu_item,
	    STATIC_FUNCTION(pm_move_to_menu_item,NIL,FALSE,1,1));
    Qpm_table_slot_visible_p = STATIC_SYMBOL("PM-TABLE-SLOT-VISIBLE-P",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qpm_table_slot_visible_p,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qpm_table_slot_visible_p,
	    STATIC_FUNCTION(pm_table_slot_visible_p,NIL,FALSE,1,1));
    Qpm_move_to_table_slot = STATIC_SYMBOL("PM-MOVE-TO-TABLE-SLOT",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qpm_move_to_table_slot,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qpm_move_to_table_slot,
	    STATIC_FUNCTION(pm_move_to_table_slot,NIL,FALSE,1,1));
    Qpm_translate_character_code_to_event_code = 
	    STATIC_SYMBOL("PM-TRANSLATE-CHARACTER-CODE-TO-EVENT-CODE",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qpm_translate_character_code_to_event_code,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qpm_translate_character_code_to_event_code,
	    STATIC_FUNCTION(pm_translate_character_code_to_event_code,NIL,
	    FALSE,2,2));
    Qpm_key_code_from_symbol = STATIC_SYMBOL("PM-KEY-CODE-FROM-SYMBOL",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qpm_key_code_from_symbol,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qpm_key_code_from_symbol,
	    STATIC_FUNCTION(pm_key_code_from_symbol,NIL,FALSE,1,1));
    Qpm_best_text = STATIC_SYMBOL("PM-BEST-TEXT",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qpm_best_text,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qpm_best_text,STATIC_FUNCTION(pm_best_text,NIL,
	    FALSE,0,0));
}
