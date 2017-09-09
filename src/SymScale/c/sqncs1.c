/* sqncs1.c
 * Input file:  sequences1.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "sqncs1.h"


DEFINE_VARIABLE_WITH_SYMBOL(Verbosity_level, Qverbosity_level);

static Object Qverbose;            /* verbose */

static Object Qsilent;             /* silent */

static Object Qnormal;             /* normal */

/* INITIALIZE-VERBOSITY-LEVEL */
Object initialize_verbosity_level()
{
    x_note_fn_call(106,0);
    if (getf(Command_line_arguments,Qverbose,_))
	return VALUES_1(Qverbose);
    else if (getf(Command_line_arguments,Qsilent,_))
	return VALUES_1(Qsilent);
    else
	return VALUES_1(Qnormal);
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_sequence_conses, Qavailable_sequence_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_sequence_conses_tail, Qavailable_sequence_conses_tail);

Object Available_sequence_conses_vector = UNBOUND;

Object Available_sequence_conses_tail_vector = UNBOUND;

Object Sequence_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Sequence_cons_counter, Qsequence_cons_counter);

/* OUTSTANDING-SEQUENCE-CONSES */
Object outstanding_sequence_conses()
{
    Object temp;

    x_note_fn_call(106,1);
    temp = FIXNUM_MINUS(Sequence_cons_counter,
	    length(Available_sequence_conses));
    return VALUES_1(temp);
}

/* SEQUENCE-CONS-MEMORY-USAGE */
Object sequence_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(106,2);
    temp = FIXNUM_TIMES(Sequence_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-SEQUENCE-CONS-POOL */
Object replenish_sequence_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(106,3);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qsequence_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_sequence_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_sequence_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_sequence_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_sequence_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_sequence_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Sequence_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

/* SEQUENCE-CONS-1 */
Object sequence_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(106,4);
    new_cons = ISVREF(Available_sequence_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_sequence_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_sequence_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_sequence_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_sequence_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qsequence);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-SEQUENCE-LIST-POOL */
Object replenish_sequence_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(106,5);
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
    if (ISVREF(Available_sequence_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_sequence_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_sequence_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_sequence_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_sequence_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qsequence_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-SEQUENCE-LIST-1 */
Object make_sequence_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(106,6);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_sequence_conses_vector,
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
	replenish_sequence_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_sequence_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qsequence);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_sequence_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_sequence_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_sequence_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_sequence_conses_tail_vector;
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

/* SEQUENCE-LIST-2 */
Object sequence_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(106,7);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_sequence_conses_vector,IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_sequence_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_sequence_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qsequence);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_sequence_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_sequence_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_sequence_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_sequence_conses_tail_vector;
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

/* SEQUENCE-LIST-3 */
Object sequence_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(106,8);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_sequence_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_sequence_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_sequence_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qsequence);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_sequence_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_sequence_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_sequence_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_sequence_conses_tail_vector;
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

/* SEQUENCE-LIST-4 */
Object sequence_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(106,9);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_sequence_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_sequence_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_sequence_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qsequence);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_sequence_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_sequence_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_sequence_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_sequence_conses_tail_vector;
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

/* SEQUENCE-LIST-TRACE-HOOK */
Object sequence_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(106,10);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-SEQUENCE-CONSES-1 */
Object copy_tree_using_sequence_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(106,11);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_sequence_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_sequence_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_sequence_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_sequence_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_sequence_cons_pool();
	temp_1 = copy_tree_using_sequence_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qsequence);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_sequence_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_sequence_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_sequence_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_sequence_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_sequence_cons_pool();
	temp_1 = copy_tree_using_sequence_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qsequence);
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

/* COPY-LIST-USING-SEQUENCE-CONSES-1 */
Object copy_list_using_sequence_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(106,12);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_sequence_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_sequence_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_sequence_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_sequence_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_sequence_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qsequence);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_sequence_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_sequence_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_sequence_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_sequence_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_sequence_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qsequence);
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

/* RECLAIM-SEQUENCE-CONS-1 */
Object reclaim_sequence_cons_1(sequence_cons)
    Object sequence_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(106,13);
    inline_note_reclaim_cons(sequence_cons,Qsequence);
    if (ISVREF(Available_sequence_conses_tail_vector,
	    IFIX(Current_thread_index))) {
	temp = ISVREF(Available_sequence_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = sequence_cons;
	temp = Available_sequence_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = sequence_cons;
    }
    else {
	temp = Available_sequence_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = sequence_cons;
	temp = Available_sequence_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = sequence_cons;
    }
    M_CDR(sequence_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-SEQUENCE-LIST-1 */
Object reclaim_sequence_list_1(sequence_list)
    Object sequence_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(106,14);
    if (sequence_list) {
	last_1 = sequence_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qsequence);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qsequence);
	if (ISVREF(Available_sequence_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_sequence_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = sequence_list;
	    temp = Available_sequence_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_sequence_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = sequence_list;
	    temp = Available_sequence_conses_tail_vector;
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

/* RECLAIM-SEQUENCE-LIST*-1 */
Object reclaim_sequence_list_star_1(sequence_list)
    Object sequence_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(106,15);
    if (CONSP(sequence_list)) {
	temp = last(sequence_list,_);
	M_CDR(temp) = Nil;
	if (sequence_list) {
	    last_1 = sequence_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qsequence);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qsequence);
	    if (ISVREF(Available_sequence_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_sequence_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = sequence_list;
		temp = Available_sequence_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_sequence_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = sequence_list;
		temp = Available_sequence_conses_tail_vector;
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

/* RECLAIM-SEQUENCE-TREE-1 */
Object reclaim_sequence_tree_1(tree)
    Object tree;
{
    Object e, e2, sequence_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(106,16);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_sequence_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		sequence_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(sequence_cons,Qsequence);
		if (EQ(sequence_cons,e))
		    goto end_1;
		else if ( !TRUEP(sequence_cons))
		    goto end_1;
		else
		    sequence_cons = CDR(sequence_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_sequence_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_sequence_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_sequence_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_sequence_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_sequence_conses_tail_vector;
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

/* DELETE-SEQUENCE-ELEMENT-1 */
Object delete_sequence_element_1(element,sequence_list)
    Object element, sequence_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(106,17);
    if (sequence_list) {
	if (EQ(element,M_CAR(sequence_list))) {
	    temp = CDR(sequence_list);
	    inline_note_reclaim_cons(sequence_list,Qsequence);
	    if (ISVREF(Available_sequence_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_sequence_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = sequence_list;
		temp_1 = Available_sequence_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = sequence_list;
	    }
	    else {
		temp_1 = Available_sequence_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = sequence_list;
		temp_1 = Available_sequence_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = sequence_list;
	    }
	    M_CDR(sequence_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = sequence_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qsequence);
		if (ISVREF(Available_sequence_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_sequence_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_sequence_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_sequence_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_sequence_conses_tail_vector;
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
	    temp = sequence_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-SEQUENCE-CONS-1 */
Object delete_sequence_cons_1(sequence_cons,sequence_list)
    Object sequence_cons, sequence_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(106,18);
    if (EQ(sequence_cons,sequence_list))
	temp = CDR(sequence_list);
    else {
	l_trailer_qm = Nil;
	l = sequence_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,sequence_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = sequence_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_sequence_cons_1(sequence_cons);
    return VALUES_1(temp);
}

/* TRANSFORM-TYPE-SPECIFICATION-2 */
Object transform_type_specification_2(string_length,string_chars,string_specs)
    Object string_length, string_chars, string_specs;
{
    Object new_string, string_spec, this_char, new_index;
    SI_Long index_1, ab_loop_bind_, spec_index, ab_loop_bind__1;

    x_note_fn_call(106,19);
    new_string = obtain_text_string(string_length);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length(string_specs));
    string_spec = Nil;
    this_char = Nil;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    string_spec = ISVREF(string_specs,index_1);
    this_char = FIX(UBYTE_16_ISAREF_1(string_chars,index_1));
    spec_index = (SI_Long)0L;
    ab_loop_bind__1 = IFIX(length(string_spec));
    new_index = Nil;
  next_loop_1:
    if (spec_index >= ab_loop_bind__1)
	goto end_loop_1;
    new_index = ISVREF(string_spec,spec_index);
    UBYTE_16_ISASET_1(new_string,IFIX(new_index),IFIX(this_char));
    spec_index = spec_index + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(new_string);
}

Object G2_product = UNBOUND;

Object G2_runtime_option = UNBOUND;

Object G2_restricted_use_option = UNBOUND;

Object G2_embedded_option = UNBOUND;

Object G2_development_option = UNBOUND;

Object Tw_product = UNBOUND;

Object Tw_runtime_option = UNBOUND;

Object Tw_restricted_use_option = UNBOUND;

Object Tw_embedded_option = UNBOUND;

Object Tw_development_option = UNBOUND;

/* UPDATE-FRAMES-NEEDING-ICP-CALLBACK */
Object update_frames_needing_icp_callback(system_1,option)
    Object system_1, option;
{
    Object gensymed_symbol, gensymed_symbol_1, temp;
    char *temp_1;

    x_note_fn_call(106,20);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(system_1);
    gensymed_symbol_1 = copy_foreign_string_arg_if_appropriate(option);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = system_1;
    temp_1 = ISTRING(temp);
    temp = gensymed_symbol_1;
    if (temp);
    else
	temp = option;
    temp = FIX(g2ext_update_callback_frames(temp_1,ISTRING(temp)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    if (gensymed_symbol_1)
	reclaim_gensym_string(gensymed_symbol_1);
    return VALUES_1(temp);
}

Object Unlimited_backtracking_in_internal_truth_maintenance_p = UNBOUND;

/* FREQUENTLY_TYPED_CHARACTERS */
Object frequently_typed_characters(system_1,option)
    Object system_1, option;
{
    Object gensymed_symbol, gensymed_symbol_1, temp;
    char *temp_1;

    x_note_fn_call(106,21);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(system_1);
    gensymed_symbol_1 = copy_foreign_string_arg_if_appropriate(option);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = system_1;
    temp_1 = ISTRING(temp);
    temp = gensymed_symbol_1;
    if (temp);
    else
	temp = option;
    temp = FIX(g2ext_frequently_typed_chars(temp_1,ISTRING(temp)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    if (gensymed_symbol_1)
	reclaim_gensym_string(gensymed_symbol_1);
    return VALUES_1(temp);
}

/* CACHE-DEFERRED-RULE-INVOCATION-INDICES-FUNCTION */
Object cache_deferred_rule_invocation_indices_function()
{
    x_note_fn_call(106,22);
    return VALUES_1(FIX(g2ext_cache_deferred_rules()));
}

Object G2_process_count_exceeded_goodbye_message = UNBOUND;

Object Tw_process_count_exceeded_goodbye_message = UNBOUND;

Object Tw_cannot_register_process_license_goodbye_message = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Available_timestamp_conses, Qavailable_timestamp_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_timestamp_conses_tail, Qavailable_timestamp_conses_tail);

Object Available_timestamp_conses_vector = UNBOUND;

Object Available_timestamp_conses_tail_vector = UNBOUND;

Object Timestamp_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Timestamp_cons_counter, Qtimestamp_cons_counter);

/* OUTSTANDING-TIMESTAMP-CONSES */
Object outstanding_timestamp_conses()
{
    Object temp;

    x_note_fn_call(106,23);
    temp = FIXNUM_MINUS(Timestamp_cons_counter,
	    length(Available_timestamp_conses));
    return VALUES_1(temp);
}

/* TIMESTAMP-CONS-MEMORY-USAGE */
Object timestamp_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(106,24);
    temp = FIXNUM_TIMES(Timestamp_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-TIMESTAMP-CONS-POOL */
Object replenish_timestamp_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(106,25);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qtimestamp_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_timestamp_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_timestamp_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_timestamp_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_timestamp_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_timestamp_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Timestamp_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qtimestamp;          /* timestamp */

/* TIMESTAMP-CONS-1 */
Object timestamp_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(106,26);
    new_cons = ISVREF(Available_timestamp_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_timestamp_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_timestamp_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_timestamp_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_timestamp_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qtimestamp);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-TIMESTAMP-LIST-POOL */
Object replenish_timestamp_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(106,27);
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
    if (ISVREF(Available_timestamp_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_timestamp_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_timestamp_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_timestamp_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_timestamp_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qtimestamp_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-TIMESTAMP-LIST-1 */
Object make_timestamp_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(106,28);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_timestamp_conses_vector,
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
	replenish_timestamp_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_timestamp_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qtimestamp);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_timestamp_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_timestamp_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_timestamp_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_timestamp_conses_tail_vector;
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

/* TIMESTAMP-LIST-2 */
Object timestamp_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(106,29);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_timestamp_conses_vector,
	    IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_timestamp_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_timestamp_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qtimestamp);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_timestamp_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_timestamp_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_timestamp_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_timestamp_conses_tail_vector;
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

/* TIMESTAMP-LIST-3 */
Object timestamp_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(106,30);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_timestamp_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_timestamp_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_timestamp_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qtimestamp);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_timestamp_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_timestamp_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_timestamp_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_timestamp_conses_tail_vector;
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

/* TIMESTAMP-LIST-4 */
Object timestamp_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(106,31);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_timestamp_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_timestamp_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_timestamp_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qtimestamp);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_timestamp_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_timestamp_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_timestamp_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_timestamp_conses_tail_vector;
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

/* TIMESTAMP-LIST-TRACE-HOOK */
Object timestamp_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(106,32);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-TIMESTAMP-CONSES-1 */
Object copy_tree_using_timestamp_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(106,33);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_timestamp_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_timestamp_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_timestamp_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_timestamp_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_timestamp_cons_pool();
	temp_1 = copy_tree_using_timestamp_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qtimestamp);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_timestamp_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_timestamp_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_timestamp_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_timestamp_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_timestamp_cons_pool();
	temp_1 = 
		copy_tree_using_timestamp_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qtimestamp);
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

/* COPY-LIST-USING-TIMESTAMP-CONSES-1 */
Object copy_list_using_timestamp_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(106,34);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_timestamp_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_timestamp_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_timestamp_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_timestamp_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_timestamp_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qtimestamp);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_timestamp_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_timestamp_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_timestamp_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_timestamp_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_timestamp_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qtimestamp);
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

/* RECLAIM-TIMESTAMP-CONS-1 */
Object reclaim_timestamp_cons_1(timestamp_cons)
    Object timestamp_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(106,35);
    inline_note_reclaim_cons(timestamp_cons,Qtimestamp);
    if (ISVREF(Available_timestamp_conses_tail_vector,
	    IFIX(Current_thread_index))) {
	temp = ISVREF(Available_timestamp_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = timestamp_cons;
	temp = Available_timestamp_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = timestamp_cons;
    }
    else {
	temp = Available_timestamp_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = timestamp_cons;
	temp = Available_timestamp_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = timestamp_cons;
    }
    M_CDR(timestamp_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-TIMESTAMP-LIST-1 */
Object reclaim_timestamp_list_1(timestamp_list)
    Object timestamp_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(106,36);
    if (timestamp_list) {
	last_1 = timestamp_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qtimestamp);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qtimestamp);
	if (ISVREF(Available_timestamp_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_timestamp_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = timestamp_list;
	    temp = Available_timestamp_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_timestamp_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = timestamp_list;
	    temp = Available_timestamp_conses_tail_vector;
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

/* RECLAIM-TIMESTAMP-LIST*-1 */
Object reclaim_timestamp_list_star_1(timestamp_list)
    Object timestamp_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(106,37);
    if (CONSP(timestamp_list)) {
	temp = last(timestamp_list,_);
	M_CDR(temp) = Nil;
	if (timestamp_list) {
	    last_1 = timestamp_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qtimestamp);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qtimestamp);
	    if (ISVREF(Available_timestamp_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_timestamp_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = timestamp_list;
		temp = Available_timestamp_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_timestamp_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = timestamp_list;
		temp = Available_timestamp_conses_tail_vector;
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

/* RECLAIM-TIMESTAMP-TREE-1 */
Object reclaim_timestamp_tree_1(tree)
    Object tree;
{
    Object e, e2, timestamp_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(106,38);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_timestamp_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		timestamp_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(timestamp_cons,Qtimestamp);
		if (EQ(timestamp_cons,e))
		    goto end_1;
		else if ( !TRUEP(timestamp_cons))
		    goto end_1;
		else
		    timestamp_cons = CDR(timestamp_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_timestamp_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_timestamp_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_timestamp_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_timestamp_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_timestamp_conses_tail_vector;
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

/* DELETE-TIMESTAMP-ELEMENT-1 */
Object delete_timestamp_element_1(element,timestamp_list)
    Object element, timestamp_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(106,39);
    if (timestamp_list) {
	if (EQ(element,M_CAR(timestamp_list))) {
	    temp = CDR(timestamp_list);
	    inline_note_reclaim_cons(timestamp_list,Qtimestamp);
	    if (ISVREF(Available_timestamp_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_timestamp_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = timestamp_list;
		temp_1 = Available_timestamp_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = timestamp_list;
	    }
	    else {
		temp_1 = Available_timestamp_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = timestamp_list;
		temp_1 = Available_timestamp_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = timestamp_list;
	    }
	    M_CDR(timestamp_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = timestamp_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qtimestamp);
		if (ISVREF(Available_timestamp_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_timestamp_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_timestamp_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_timestamp_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_timestamp_conses_tail_vector;
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
	    temp = timestamp_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-TIMESTAMP-CONS-1 */
Object delete_timestamp_cons_1(timestamp_cons,timestamp_list)
    Object timestamp_cons, timestamp_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(106,40);
    if (EQ(timestamp_cons,timestamp_list))
	temp = CDR(timestamp_list);
    else {
	l_trailer_qm = Nil;
	l = timestamp_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,timestamp_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = timestamp_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_timestamp_cons_1(timestamp_cons);
    return VALUES_1(temp);
}

/* INITIALIZE-CLASS-INSTANCE-DELTA-MASKS */
Object initialize_class_instance_delta_masks()
{
    Object mask, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, ab_loop_iter_flag_;
    Object temp;
    SI_Long index_1;

    x_note_fn_call(106,41);
    index_1 = (SI_Long)0L;
    mask = FIX((SI_Long)127L);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_iter_flag_ = T;
  next_loop:
    if (index_1 > (SI_Long)32L)
	goto end_loop;
    if ( !TRUEP(ab_loop_iter_flag_))
	mask = ash(mask,FIX((SI_Long)7L));
    ab_loopvar__2 = LIST_1(mask);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    ab_loop_iter_flag_ = Nil;
    index_1 = index_1 + (SI_Long)7L;
    goto next_loop;
  end_loop:
    temp = ab_loopvar_;
    goto end_1;
    temp = Qnil;
  end_1:;
    return make_array(5,FIX((SI_Long)5L),Kelement_type,T,Kinitial_contents,
	    temp);
}

Object Class_instance_delta_masks = UNBOUND;

/* ASSEMBLE-UNCACHED-COMPOUND-METHOD-FLAGS */
Object assemble_uncached_compound_method_flags(n_1,amount,offset,window)
    Object n_1, amount, offset, window;
{
    Object temp, intact, span, temp_2;
    char temp_1;

    x_note_fn_call(106,42);
    amount = mod(amount,window);
    if (NUMBERP(amount)) {
	temp = FIX((SI_Long)0L);
	temp_1 = NUM_EQ(amount,temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	return VALUES_1(n_1);
    else {
	intact = logand(lognot(ash(sub1(ash(FIX((SI_Long)1L),window)),
		offset)),n_1);
	span = minus(window,amount);
	temp_2 = ash(logand(ash(sub1(ash(FIX((SI_Long)1L),span)),offset),
		n_1),amount);
	temp = logand(ash(sub1(ash(FIX((SI_Long)1L),amount)),add(offset,
		span)),n_1);
	return logiorn(3,temp_2,ash(temp,negate(span)),intact);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Embedded_fuzzy_conditionals_list, Qembedded_fuzzy_conditionals_list);

/* INITIALIZE-EMBEDDED-FUZZY-CONDITIONALS-LIST */
Object initialize_embedded_fuzzy_conditionals_list()
{
    x_note_fn_call(106,43);
    return list(7,FIX((SI_Long)13L),FIX((SI_Long)-2L),FIX((SI_Long)4L),
	    FIX((SI_Long)2L),FIX((SI_Long)-1L),FIX((SI_Long)7L),
	    FIX((SI_Long)8L));
}

DEFINE_VARIABLE_WITH_SYMBOL(Separate_imminent_actions_p, Qseparate_imminent_actions_p);

Object Engage_context_pipelining_p = UNBOUND;

Object Current_inner_procedure_loop_cache_index = UNBOUND;

Object Drawing_task_tuning_info = UNBOUND;

Object Counter_for_sleep_management_adjustment = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Legacy_subsecond_heartbeat_adjustment_interval, Qlegacy_subsecond_heartbeat_adjustment_interval);

Object Refuse_load_at_discrepancy_with_system_clock_message = UNBOUND;

Object Refuse_save_after_system_clock_tampering_message = UNBOUND;

Object Limit_bignum_inner_loop_cache_p = UNBOUND;

Object Evaluator_tradeoff_info = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Minimal_fragmentation_seeds, Qminimal_fragmentation_seeds);

/* INITIALIZE-MINIMAL-FRAGMENTATION-SEEDS */
Object initialize_minimal_fragmentation_seeds()
{
    Object temp;

    x_note_fn_call(106,44);
    temp = LIST_5(FIX((SI_Long)1691441L),FIX((SI_Long)1755045L),
	    FIX((SI_Long)1150513L),FIX((SI_Long)574721L),FIX((SI_Long)4162L));
    return VALUES_1(temp);
}

Object G2_system_time_too_early_goodbye_message = UNBOUND;

Object Tw_system_time_too_early_goodbye_message = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Master_hierarchy_reconciliation_switches, Qmaster_hierarchy_reconciliation_switches);

/* INITIALIZE-MASTER-HIERARCHY-RECONCILIATION-SWITCHES */
Object initialize_master_hierarchy_reconciliation_switches()
{
    Object temp;

    x_note_fn_call(106,45);
    temp = LIST_3(Nil,Nil,Nil);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Consistency_tree_focus_shifts, Qconsistency_tree_focus_shifts);

/* INITIALIZE-CONSISTENCY-TREE-FOCUS-SHIFTS */
Object initialize_consistency_tree_focus_shifts()
{
    Object original_list, cdr_arg, cdr_new_value;

    x_note_fn_call(106,46);
    original_list = make_list(1,FIX((SI_Long)5L));
    cdr_arg = last(original_list,_);
    cdr_new_value = CDR(Master_hierarchy_reconciliation_switches);
    M_CDR(cdr_arg) = cdr_new_value;
    return VALUES_1(original_list);
}

Object Embedded_g2_with_windows_goodbye_message = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chaining_refresh_version, Qchaining_refresh_version);

static Object array_constant;      /* # */

static Object array_constant_1;    /* # */

static Object array_constant_2;    /* # */

static Object array_constant_3;    /* # */

static Object array_constant_4;    /* # */

static Object array_constant_5;    /* # */

/* CHOOSE-CHAINING-REFRESH-LIST */
Object choose_chaining_refresh_list()
{
    x_note_fn_call(106,47);
    if ( !(FIXNUMP(Chaining_refresh_version) && 
	    FIXNUM_LE(FIX((SI_Long)-128L),Chaining_refresh_version) && 
	    FIXNUM_LE(Chaining_refresh_version,FIX((SI_Long)127L))))
	return error((SI_Long)2L,"unknown version: ~d",
		Chaining_refresh_version);
    else
	switch (INTEGER_TO_CHAR(Chaining_refresh_version)) {
	  case 3:
	    return VALUES_1(array_constant);
	  case 4:
	    return VALUES_1(array_constant_1);
	  case 5:
	  case 6:
	    return VALUES_1(array_constant_2);
	  case 8:
	    return VALUES_1(array_constant_3);
	  case 9:
	  case 12:
	    return VALUES_1(array_constant_4);
	  case 11:
	    return VALUES_1(array_constant_5);
	  default:
	    return error((SI_Long)2L,"unknown version: ~d",
		    Chaining_refresh_version);
	}
}

DEFINE_VARIABLE_WITH_SYMBOL(Chaining_refresh_list, Qchaining_refresh_list);

/* C-NSLEEP */
Object c_nsleep(timestring)
    Object timestring;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(106,48);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(timestring);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = timestring;
    temp = FIX(g2ext_nsleep(ISTRING(temp)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* C-NSLEEP-NEXT */
Object c_nsleep_next(timestring)
    Object timestring;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(106,49);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(timestring);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = timestring;
    temp = FIX(g2ext_nsleep_next(ISTRING(temp)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* GET-LOCAL-MACHINE-ID-FUNCTION */
Object get_local_machine_id_function()
{
    Object temp, success_qm, text_string_result, temp_1, temp_2, maximum_index;
    SI_Long i;

    x_note_fn_call(106,50);
    temp = obtain_simple_gensym_string(Size_of_local_machine_id);
    success_qm = Nil;
    text_string_result = Nil;
    temp_1 = CHR('\000');
    SET_SCHAR(temp,FIX((SI_Long)0L),temp_1);
    success_qm = IFIX(c_nsleep(temp)) >= (SI_Long)0L ? T : Nil;
    temp_1 = copy_text_string(temp);
    reclaim_simple_gensym_string(temp);
    text_string_result = temp_1;
    if (!success_qm) {
	if (!shunned_machine_id_string_p(text_string_result)) {
	    UBYTE_16_ISASET_1(text_string_result,(SI_Long)0L,(SI_Long)69L);
	    UBYTE_16_ISASET_1(text_string_result,(SI_Long)1L,(SI_Long)82L);
	    UBYTE_16_ISASET_1(text_string_result,(SI_Long)2L,(SI_Long)82L);
	    UBYTE_16_ISASET_1(text_string_result,(SI_Long)3L,(SI_Long)79L);
	    UBYTE_16_ISASET_1(text_string_result,(SI_Long)4L,(SI_Long)82L);
	    UBYTE_16_ISASET_1(text_string_result,(SI_Long)5L,(SI_Long)0L);
	}
    }
    temp_2 = text_string_result;
    maximum_index = FIXNUM_SUB1(text_string_length(text_string_result));
    i = (SI_Long)0L;
  next_loop:
    if (UBYTE_16_ISAREF_1(text_string_result,i) == (SI_Long)0L) {
	temp_1 = FIX(i);
	goto end_1;
    }
    if (i >= IFIX(maximum_index)) {
	temp_1 = FIX(i + (SI_Long)1L);
	goto end_1;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp_1 = Qnil;
  end_1:;
    temp_1 = text_string_substring(temp_2,FIX((SI_Long)0L),temp_1);
    reclaim_text_string(text_string_result);
    return VALUES_1(temp_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(First_string_in_pool_group, Qfirst_string_in_pool_group);

/* SET-FIRST-STRING-IN-POOL-GROUP */
Object set_first_string_in_pool_group(text_string)
    Object text_string;
{
    x_note_fn_call(106,51);
    First_string_in_pool_group = copy_text_string(text_string);
    return VALUES_1(First_string_in_pool_group);
}

/* POINTER-TO-FIRST-STRING-IN-POOL-GROUP */
Object pointer_to_first_string_in_pool_group()
{
    x_note_fn_call(106,52);
    return copy_text_string(First_string_in_pool_group);
}

DEFINE_VARIABLE_WITH_SYMBOL(Name_of_customer_in_ok_file, Qname_of_customer_in_ok_file);

DEFINE_VARIABLE_WITH_SYMBOL(Serial_number_in_ok_file, Qserial_number_in_ok_file);

DEFINE_VARIABLE_WITH_SYMBOL(Installation_code_in_ok_file, Qinstallation_code_in_ok_file);

Object Original_site_license_title_block_phrase = UNBOUND;

Object Site_license_title_block_phrase = UNBOUND;

Object Serial_number_title_block_phrase = UNBOUND;

static Object Qunbound_in_protected_let;  /* unbound-in-protected-let */

static Object array_constant_6;    /* # */

static Object string_constant;     /* ";~% ~a ~a" */

static Object string_constant_1;   /* ";~% This ~a ~a ~a~% ~a ~a" */

static Object string_constant_2;   /* ";~% This ~a ~a ~a" */

static Object string_constant_3;   /* ";~% This ~a ~a UNKNOWN~% ~a ~a" */

static Object string_constant_4;   /* ";~% This ~a ~a UNKNOWN" */

static Object string_constant_5;   /* ";~% Machine ID: ~s" */

/* PRINT-FIRST-STRING-IN-POOL-GROUP */
Object print_first_string_in_pool_group()
{
    volatile Object id_string;
    Object end2, ab_loop_iter_flag_, temp_1, temp_2, site_license_label;
    SI_Long temp, end1, length1, length2, index1, ab_loop_bind_, index2;
    SI_Long ab_loop_bind__1, code;
    char temp_3;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(106,53);
    SAVE_STACK();
    id_string = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	id_string = pointer_to_first_string_in_pool_group();
	temp = IFIX(text_string_length(id_string));
	end1 = MIN((SI_Long)5L,temp);
	end2 = text_string_length(array_constant_6);
	length1 = end1 - (SI_Long)0L;
	length2 = IFIX(end2) - (SI_Long)0L;
	if (length1 == length2) {
	    index1 = (SI_Long)0L;
	    ab_loop_bind_ = end1;
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
	    code = UBYTE_16_ISAREF_1(id_string,index1);
	    if (code < (SI_Long)127L)
		temp_1 = (SI_Long)65L <= code && code <= (SI_Long)90L ? 
			FIX(code + (SI_Long)32L) : FIX(code);
	    else {
		temp_1 = unicode_lowercase_if_uppercase(FIX(code));
		if (temp_1);
		else
		    temp_1 = FIX(code);
	    }
	    code = UBYTE_16_ISAREF_1(array_constant_6,index2);
	    if (code < (SI_Long)127L)
		temp_2 = (SI_Long)65L <= code && code <= (SI_Long)90L ? 
			FIX(code + (SI_Long)32L) : FIX(code);
	    else {
		temp_2 = unicode_lowercase_if_uppercase(FIX(code));
		if (temp_2);
		else
		    temp_2 = FIX(code);
	    }
	    if ( !NUM_EQ(temp_1,temp_2)) {
		temp_3 = TRUEP(Nil);
		goto end_1;
	    }
	    ab_loop_iter_flag_ = Nil;
	    index1 = index1 + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    temp_3 = TRUEP(T);
	    goto end_1;
	    temp_3 = TRUEP(Qnil);
	  end_1:;
	}
	else
	    temp_3 = TRUEP(Nil);
	if (temp_3) {
	    temp_1 = id_string;
	    site_license_label = text_string_substring(temp_1,
		    IFIX(text_string_length(id_string)) >= (SI_Long)6L && 
		    UBYTE_16_ISAREF_1(id_string,(SI_Long)5L) == 
		    (SI_Long)32L ? FIX((SI_Long)6L) : FIX((SI_Long)5L),Nil);
	    if ( !(Name_of_customer_in_ok_file || Serial_number_in_ok_file 
		    || Installation_code_in_ok_file))
		SAVE_VALUES(tformat(3,string_constant,
			Original_site_license_title_block_phrase,
			site_license_label));
	    else if (Name_of_customer_in_ok_file && Serial_number_in_ok_file)
		SAVE_VALUES(tformat(6,string_constant_1,site_license_label,
			Site_license_title_block_phrase,
			Name_of_customer_in_ok_file,
			Serial_number_title_block_phrase,
			Serial_number_in_ok_file));
	    else if (Name_of_customer_in_ok_file)
		SAVE_VALUES(tformat(4,string_constant_2,site_license_label,
			Site_license_title_block_phrase,
			Name_of_customer_in_ok_file));
	    else if (Serial_number_in_ok_file)
		SAVE_VALUES(tformat(5,string_constant_3,site_license_label,
			Site_license_title_block_phrase,
			Serial_number_title_block_phrase,
			Serial_number_in_ok_file));
	    else if (Installation_code_in_ok_file)
		SAVE_VALUES(tformat(3,string_constant_4,site_license_label,
			Site_license_title_block_phrase));
	    else
		SAVE_VALUES(VALUES_1(Qnil));
	}
	else
	    SAVE_VALUES(tformat(2,string_constant_5,id_string));
    }
    POP_UNWIND_PROTECT(0);
    if (id_string) {
	if ( !EQ(id_string,Qunbound_in_protected_let)) {
	    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(id_string) != (SI_Long)0L)
		reclaim_wide_string(id_string);
	}
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Cached_machine_id_qm, Qcached_machine_id_qm);

/* GET-NEXT-LOCAL-MACHINE-ID-AS-TEXT-STRING */
Object get_next_local_machine_id_as_text_string()
{
    Object temp, temp_text_string, temp_1, temp_2, maximum_index;
    SI_Long i;

    x_note_fn_call(106,54);
    temp = obtain_simple_gensym_string(Size_of_local_machine_id);
    temp_text_string = Nil;
    temp_1 = CHR('\000');
    SET_SCHAR(temp,FIX((SI_Long)0L),temp_1);
    if (IFIX(c_nsleep_next(temp)) >= (SI_Long)0L) {
	temp_text_string = copy_text_string(temp);
	temp_2 = temp_text_string;
	maximum_index = FIXNUM_SUB1(text_string_length(temp_text_string));
	i = (SI_Long)0L;
      next_loop:
	if (UBYTE_16_ISAREF_1(temp_text_string,i) == (SI_Long)0L) {
	    temp_1 = FIX(i);
	    goto end_1;
	}
	if (i >= IFIX(maximum_index)) {
	    temp_1 = FIX(i + (SI_Long)1L);
	    goto end_1;
	}
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp_1 = Qnil;
      end_1:;
	temp_1 = text_string_substring(temp_2,FIX((SI_Long)0L),temp_1);
	reclaim_text_string(temp_text_string);
    }
    else
	temp_1 = Nil;
    reclaim_simple_gensym_string(temp);
    return VALUES_1(temp_1);
}

/* GET-LOCAL-MACHINE-IDS-AS-GENSYM-LIST */
Object get_local_machine_ids_as_gensym_list()
{
    Object result_1, temp, success_qm, text_string_result, temp_1, temp_2;
    Object maximum_index, machine_id_qm, prev, ab_loop_list_;
    SI_Long i;
    char temp_3;

    x_note_fn_call(106,55);
    result_1 = Nil;
    temp = obtain_simple_gensym_string(Size_of_local_machine_id);
    success_qm = Nil;
    text_string_result = Nil;
    temp_1 = CHR('\000');
    SET_SCHAR(temp,FIX((SI_Long)0L),temp_1);
    success_qm = IFIX(c_nsleep(temp)) >= (SI_Long)0L ? T : Nil;
    temp_1 = copy_text_string(temp);
    reclaim_simple_gensym_string(temp);
    text_string_result = temp_1;
    if (!success_qm) {
	if (!shunned_machine_id_string_p(text_string_result)) {
	    UBYTE_16_ISASET_1(text_string_result,(SI_Long)0L,(SI_Long)69L);
	    UBYTE_16_ISASET_1(text_string_result,(SI_Long)1L,(SI_Long)82L);
	    UBYTE_16_ISASET_1(text_string_result,(SI_Long)2L,(SI_Long)82L);
	    UBYTE_16_ISASET_1(text_string_result,(SI_Long)3L,(SI_Long)79L);
	    UBYTE_16_ISASET_1(text_string_result,(SI_Long)4L,(SI_Long)82L);
	    UBYTE_16_ISASET_1(text_string_result,(SI_Long)5L,(SI_Long)0L);
	}
    }
    temp_2 = text_string_result;
    maximum_index = FIXNUM_SUB1(text_string_length(text_string_result));
    i = (SI_Long)0L;
  next_loop:
    if (UBYTE_16_ISAREF_1(text_string_result,i) == (SI_Long)0L) {
	temp_1 = FIX(i);
	goto end_1;
    }
    if (i >= IFIX(maximum_index)) {
	temp_1 = FIX(i + (SI_Long)1L);
	goto end_1;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp_1 = Qnil;
  end_1:;
    temp_1 = text_string_substring(temp_2,FIX((SI_Long)0L),temp_1);
    reclaim_text_string(text_string_result);
    machine_id_qm = temp_1;
  next_loop_1:
    if ( !TRUEP(machine_id_qm))
	goto end_loop_1;
    if ( !TRUEP(shunned_machine_id_string_p(machine_id_qm))) {
	prev = Nil;
	ab_loop_list_ = result_1;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	prev = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (normalized_string_equal(2,prev,machine_id_qm)) {
	    temp_3 = TRUEP(Nil);
	    goto end_2;
	}
	goto next_loop_2;
      end_loop_2:
	temp_3 = TRUEP(T);
	goto end_2;
	temp_3 = TRUEP(Qnil);
      end_2:;
    }
    else
	temp_3 = TRUEP(Nil);
    if (temp_3)
	result_1 = nconc2(result_1,gensym_cons_1(machine_id_qm,Nil));
    else
	reclaim_text_string(machine_id_qm);
    machine_id_qm = get_next_local_machine_id_as_text_string();
    goto next_loop_1;
  end_loop_1:
    return VALUES_1(result_1);
    return VALUES_1(Qnil);
}

Object Mask12 = UNBOUND;

/* INNER-MULTIPLY */
Object inner_multiply(x,y)
    Object x, y;
{
    x_note_fn_call(106,56);
    return VALUES_1(FIX((IFIX(FIXNUM_LOGAND(x,Mask12)) ^ IFIX(x) >>  -  - 
	    (SI_Long)12L & IFIX(Mask12)) * (IFIX(FIXNUM_LOGAND(y,Mask12)) 
	    ^ IFIX(y) >>  -  - (SI_Long)12L & IFIX(Mask12))));
}

Object New_modulus = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Shunned_machine_ids_list, Qshunned_machine_ids_list);

static Object Qnormalized_string_equal;  /* normalized-string-equal */

static Object string_constant_6;   /* "error" */

/* SHUNNED-MACHINE-ID-STRING-P */
Object shunned_machine_id_string_p(machine_id_string)
    Object machine_id_string;
{
    Object temp;

    x_note_fn_call(106,57);
    temp = IFIX(normalized_string_length(machine_id_string)) < (SI_Long)3L 
	    ? T : Nil;
    if (temp);
    else
	temp = member(4,machine_id_string,Shunned_machine_ids_list,Ktest,
		Qnormalized_string_equal);
    if (temp)
	return VALUES_1(temp);
    else
	return search(2,string_constant_6,Shunned_machine_ids_list);
}

/* NORMALIZED-STRING-EQUAL */
Object normalized_string_equal varargs_1(int, n)
{
    Object text_string_1, text_string_2;
    Object different_lengths_ok_qm, length1, length2, w1, w2, i1, i2, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(106,58);
    INIT_ARGS_nonrelocating();
    text_string_1 = REQUIRED_ARG_nonrelocating();
    text_string_2 = REQUIRED_ARG_nonrelocating();
    different_lengths_ok_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    length1 = lengthw(text_string_1);
    length2 = lengthw(text_string_2);
    w1 = Nil;
    w2 = Nil;
    i1 = FIX((SI_Long)0L);
    i2 = FIX((SI_Long)0L);
  next_loop:
  next_loop_1:
    if (FIXNUM_GE(i1,length1))
	goto end_loop;
    w1 = digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(text_string_1,
	    IFIX(i1))),FIX((SI_Long)36L));
    if (w1) {
	i1 = FIXNUM_ADD1(i1);
	goto end_1;
    }
    i1 = FIXNUM_ADD1(i1);
    goto next_loop_1;
  end_loop:
    w1 = Nil;
  end_1:
  next_loop_2:
    if (FIXNUM_GE(i2,length2))
	goto end_loop_1;
    w2 = digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(text_string_2,
	    IFIX(i2))),FIX((SI_Long)36L));
    if (w2) {
	i2 = FIXNUM_ADD1(i2);
	goto end_2;
    }
    i2 = FIXNUM_ADD1(i2);
    goto next_loop_2;
  end_loop_1:
    w2 = Nil;
  end_2:
    if ( !EQL(w1,w2)) {
	if (different_lengths_ok_qm) {
	    temp =  !TRUEP(w1) ? T : Nil;
	    if (temp)
		return VALUES_1(temp);
	    else
		return VALUES_1( !TRUEP(w2) ? T : Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    if (FIXNUM_GE(i1,length1) && FIXNUM_GE(i2,length2))
	return VALUES_1(T);
    goto next_loop;
  end_loop_2:
    return VALUES_1(Qnil);
}

/* NORMALIZED-STRING-LENGTH */
Object normalized_string_length(string_1)
    Object string_1;
{
    SI_Long i, ab_loop_bind_, ab_loopvar_;

    x_note_fn_call(106,59);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(lengthw(string_1));
    ab_loopvar_ = (SI_Long)0L;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    if (digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(string_1,i)),
	    FIX((SI_Long)36L)))
	ab_loopvar_ = ab_loopvar_ + (SI_Long)1L;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(FIX(ab_loopvar_));
    return VALUES_1(Qnil);
}

static Object Kcommand_line;       /* :command-line */

static Object Kenvironment_variable;  /* :environment-variable */

/* GET-APPROPRIATE-OK-PATHNAME */
Object get_appropriate_ok_pathname varargs_1(int, n)
{
    Object telewindows_case_qm, v_pathname_qm, v_desired_namestring_qm;
    Object v_source_qm, pathname_qm, desired_namestring_qm, source_qm, temp;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(106,60);
    INIT_ARGS_nonrelocating();
    telewindows_case_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(T))
	result = VALUES_1(Nil);
    else
	switch (INTEGER_TO_CHAR(Major_version_number_of_current_gensym_product_line)) 
		    {
	  case 12:
	    if (telewindows_case_qm)
		result = get_or_use_twv12_ok_pathname(1,T);
	    else
		result = get_or_use_g2v12_ok_pathname(1,T);
	    break;
	  case 11:
	    if (telewindows_case_qm)
		result = get_or_use_twv11_ok_pathname(1,T);
	    else
		result = get_or_use_g2v11_ok_pathname(1,T);
	    break;
	  case 9:
	    if (telewindows_case_qm)
		result = get_or_use_twv9_ok_pathname(1,T);
	    else
		result = get_or_use_g2v9_ok_pathname(1,T);
	    break;
	  case 8:
	    if (telewindows_case_qm)
		result = get_or_use_twv8_ok_pathname(1,T);
	    else if (IFIX(Minor_version_number_of_current_gensym_product_line) 
		    > (SI_Long)30L || 
		    IFIX(Minor_version_number_of_current_gensym_product_line) 
		    == (SI_Long)30L && 
		    FIXNUM_GE(Release_quality_of_current_gensym_product_line,
		    Beta_release_quality))
		result = get_or_use_g2v83_ok_pathname(1,T);
	    else
		result = get_or_use_g2v8_ok_pathname(1,T);
	    break;
	  case 7:
	    if (telewindows_case_qm)
		result = get_or_use_twv7_ok_pathname(1,T);
	    else
		result = get_or_use_g2v7_ok_pathname(1,T);
	    break;
	  case 6:
	    if (telewindows_case_qm)
		result = get_or_use_twv6_ok_pathname(1,T);
	    else
		result = get_or_use_g2v6_ok_pathname(1,T);
	    break;
	  case 5:
	    if (telewindows_case_qm)
		result = get_or_use_twv5_ok_pathname(1,T);
	    else if (IFIX(Minor_version_number_of_current_gensym_product_line) 
		    >= (SI_Long)10L)
		result = get_or_use_g2v51_ok_pathname(1,T);
	    else
		result = get_or_use_g2v5_ok_pathname(1,T);
	    break;
	  default:
	    result = VALUES_1(Nil);
	    break;
	}
    MVS_3(result,v_pathname_qm,v_desired_namestring_qm,v_source_qm);
    if ( !TRUEP(v_pathname_qm) &&  !TRUEP(telewindows_case_qm) && 
	    (SI_Long)5L == 
	    IFIX(Major_version_number_of_current_gensym_product_line) && 
	    IFIX(Minor_version_number_of_current_gensym_product_line) >= 
	    (SI_Long)10L) {
	result = get_or_use_g2v5_ok_pathname(1,T);
	MVS_3(result,v_pathname_qm,v_desired_namestring_qm,v_source_qm);
    }
    if (telewindows_case_qm)
	result = get_or_use_tw_ok_pathname(1,T);
    else
	result = get_or_use_g2_ok_pathname(1,T);
    MVS_3(result,pathname_qm,desired_namestring_qm,source_qm);
    if (pathname_qm && v_pathname_qm) {
	if (EQ(v_source_qm,Kcommand_line))
	    temp = v_pathname_qm;
	else if (EQ(source_qm,Kcommand_line))
	    temp = pathname_qm;
	else if (EQ(v_source_qm,Kenvironment_variable))
	    temp = v_pathname_qm;
	else if (EQ(source_qm,Kenvironment_variable))
	    temp = pathname_qm;
	else if (EQ(v_source_qm,Kdirectory))
	    temp = v_pathname_qm;
	else if (EQ(source_qm,Kdirectory))
	    temp = pathname_qm;
	else
	    temp = Qnil;
    }
    else
	temp = Nil;
    if (temp);
    else {
	temp = v_pathname_qm;
	if (temp);
	else
	    temp = pathname_qm;
    }
    if (v_desired_namestring_qm)
	reclaim_text_string(v_desired_namestring_qm);
    if (desired_namestring_qm)
	reclaim_text_string(desired_namestring_qm);
    return VALUES_1(temp);
}

static Object array_constant_7;    /* # */

static Object array_constant_8;    /* # */

/* INITIALIZE-DEFAULT-TW-OK-PATHNAME */
Object initialize_default_tw_ok_pathname()
{
    x_note_fn_call(106,61);
    return gensym_make_pathname_with_copied_components(Nil,Nil,Nil,
	    array_constant_7,array_constant_8,Knewest,
	    Process_specific_system_pathname);
}

DEFINE_VARIABLE_WITH_SYMBOL(Default_tw_ok_pathname, Qdefault_tw_ok_pathname);

static Object list_constant;       /* # */

static Object array_constant_9;    /* # */

static Object array_constant_10;   /* # */

/* INITIALIZER-FOR-PATHNAME-FOR-DISABLING-TW-OK-COMMAND-LINE */
Object initializer_for_pathname_for_disabling_tw_ok_command_line()
{
    x_note_fn_call(106,62);
    return gensym_make_pathname_with_copied_components(Nil,Nil,
	    list_constant,array_constant_9,array_constant_10,Knewest,Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_tw_ok_command_line, Qpathname_for_disabling_tw_ok_command_line);

static Object array_constant_11;   /* # */

/* GET-OR-USE-TW-OK-PATHNAME */
Object get_or_use_tw_ok_pathname varargs_1(int, n)
{
    Object provide_desired_namestring_p;
    Declare_varargs_nonrelocating;

    x_note_fn_call(106,63);
    INIT_ARGS_nonrelocating();
    provide_desired_namestring_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return provide_pathname_for_launch_time_load(Default_tw_ok_pathname,
	    Pathname_for_disabling_tw_ok_command_line,array_constant_8,
	    array_constant_11,array_constant_8,provide_desired_namestring_p);
}

static Object array_constant_12;   /* # */

/* INITIALIZE-DEFAULT-TWV5-OK-PATHNAME */
Object initialize_default_twv5_ok_pathname()
{
    x_note_fn_call(106,64);
    return gensym_make_pathname_with_copied_components(Nil,Nil,Nil,
	    array_constant_12,array_constant_8,Knewest,
	    Process_specific_system_pathname);
}

DEFINE_VARIABLE_WITH_SYMBOL(Default_twv5_ok_pathname, Qdefault_twv5_ok_pathname);

static Object array_constant_13;   /* # */

/* INITIALIZER-FOR-PATHNAME-FOR-DISABLING-TWV5-OK-COMMAND-LINE */
Object initializer_for_pathname_for_disabling_twv5_ok_command_line()
{
    x_note_fn_call(106,65);
    return gensym_make_pathname_with_copied_components(Nil,Nil,
	    list_constant,array_constant_13,array_constant_10,Knewest,Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_twv5_ok_command_line, Qpathname_for_disabling_twv5_ok_command_line);

static Object array_constant_14;   /* # */

static Object array_constant_15;   /* # */

/* GET-OR-USE-TWV5-OK-PATHNAME */
Object get_or_use_twv5_ok_pathname varargs_1(int, n)
{
    Object provide_desired_namestring_p;
    Declare_varargs_nonrelocating;

    x_note_fn_call(106,66);
    INIT_ARGS_nonrelocating();
    provide_desired_namestring_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return provide_pathname_for_launch_time_load(Default_twv5_ok_pathname,
	    Pathname_for_disabling_twv5_ok_command_line,array_constant_14,
	    array_constant_15,array_constant_8,provide_desired_namestring_p);
}

static Object array_constant_16;   /* # */

/* INITIALIZE-DEFAULT-TWV6-OK-PATHNAME */
Object initialize_default_twv6_ok_pathname()
{
    x_note_fn_call(106,67);
    return gensym_make_pathname_with_copied_components(Nil,Nil,Nil,
	    array_constant_16,array_constant_8,Knewest,
	    Process_specific_system_pathname);
}

DEFINE_VARIABLE_WITH_SYMBOL(Default_twv6_ok_pathname, Qdefault_twv6_ok_pathname);

/* INITIALIZER-FOR-PATHNAME-FOR-DISABLING-TWV6-OK-COMMAND-LINE */
Object initializer_for_pathname_for_disabling_twv6_ok_command_line()
{
    x_note_fn_call(106,68);
    return gensym_make_pathname_with_copied_components(Nil,Nil,
	    list_constant,array_constant_13,array_constant_10,Knewest,Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_twv6_ok_command_line, Qpathname_for_disabling_twv6_ok_command_line);

static Object array_constant_17;   /* # */

static Object array_constant_18;   /* # */

/* GET-OR-USE-TWV6-OK-PATHNAME */
Object get_or_use_twv6_ok_pathname varargs_1(int, n)
{
    Object provide_desired_namestring_p;
    Declare_varargs_nonrelocating;

    x_note_fn_call(106,69);
    INIT_ARGS_nonrelocating();
    provide_desired_namestring_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return provide_pathname_for_launch_time_load(Default_twv6_ok_pathname,
	    Pathname_for_disabling_twv6_ok_command_line,array_constant_17,
	    array_constant_18,array_constant_8,provide_desired_namestring_p);
}

static Object array_constant_19;   /* # */

/* INITIALIZE-DEFAULT-TWV7-OK-PATHNAME */
Object initialize_default_twv7_ok_pathname()
{
    x_note_fn_call(106,70);
    return gensym_make_pathname_with_copied_components(Nil,Nil,Nil,
	    array_constant_19,array_constant_8,Knewest,
	    Process_specific_system_pathname);
}

DEFINE_VARIABLE_WITH_SYMBOL(Default_twv7_ok_pathname, Qdefault_twv7_ok_pathname);

/* INITIALIZER-FOR-PATHNAME-FOR-DISABLING-TWV7-OK-COMMAND-LINE */
Object initializer_for_pathname_for_disabling_twv7_ok_command_line()
{
    x_note_fn_call(106,71);
    return gensym_make_pathname_with_copied_components(Nil,Nil,
	    list_constant,array_constant_13,array_constant_10,Knewest,Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_twv7_ok_command_line, Qpathname_for_disabling_twv7_ok_command_line);

static Object array_constant_20;   /* # */

static Object array_constant_21;   /* # */

/* GET-OR-USE-TWV7-OK-PATHNAME */
Object get_or_use_twv7_ok_pathname varargs_1(int, n)
{
    Object provide_desired_namestring_p;
    Declare_varargs_nonrelocating;

    x_note_fn_call(106,72);
    INIT_ARGS_nonrelocating();
    provide_desired_namestring_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return provide_pathname_for_launch_time_load(Default_twv7_ok_pathname,
	    Pathname_for_disabling_twv7_ok_command_line,array_constant_20,
	    array_constant_21,array_constant_8,provide_desired_namestring_p);
}

static Object array_constant_22;   /* # */

/* INITIALIZE-DEFAULT-TWV8-OK-PATHNAME */
Object initialize_default_twv8_ok_pathname()
{
    x_note_fn_call(106,73);
    return gensym_make_pathname_with_copied_components(Nil,Nil,Nil,
	    array_constant_22,array_constant_8,Knewest,
	    Process_specific_system_pathname);
}

DEFINE_VARIABLE_WITH_SYMBOL(Default_twv8_ok_pathname, Qdefault_twv8_ok_pathname);

/* INITIALIZER-FOR-PATHNAME-FOR-DISABLING-TWV8-OK-COMMAND-LINE */
Object initializer_for_pathname_for_disabling_twv8_ok_command_line()
{
    x_note_fn_call(106,74);
    return gensym_make_pathname_with_copied_components(Nil,Nil,
	    list_constant,array_constant_13,array_constant_10,Knewest,Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_twv8_ok_command_line, Qpathname_for_disabling_twv8_ok_command_line);

static Object array_constant_23;   /* # */

static Object array_constant_24;   /* # */

/* GET-OR-USE-TWV8-OK-PATHNAME */
Object get_or_use_twv8_ok_pathname varargs_1(int, n)
{
    Object provide_desired_namestring_p;
    Declare_varargs_nonrelocating;

    x_note_fn_call(106,75);
    INIT_ARGS_nonrelocating();
    provide_desired_namestring_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return provide_pathname_for_launch_time_load(Default_twv8_ok_pathname,
	    Pathname_for_disabling_twv8_ok_command_line,array_constant_23,
	    array_constant_24,array_constant_8,provide_desired_namestring_p);
}

static Object array_constant_25;   /* # */

/* INITIALIZE-DEFAULT-TWV9-OK-PATHNAME */
Object initialize_default_twv9_ok_pathname()
{
    x_note_fn_call(106,76);
    return gensym_make_pathname_with_copied_components(Nil,Nil,Nil,
	    array_constant_25,array_constant_8,Knewest,
	    Process_specific_system_pathname);
}

DEFINE_VARIABLE_WITH_SYMBOL(Default_twv9_ok_pathname, Qdefault_twv9_ok_pathname);

/* INITIALIZER-FOR-PATHNAME-FOR-DISABLING-TWV9-OK-COMMAND-LINE */
Object initializer_for_pathname_for_disabling_twv9_ok_command_line()
{
    x_note_fn_call(106,77);
    return gensym_make_pathname_with_copied_components(Nil,Nil,
	    list_constant,array_constant_13,array_constant_10,Knewest,Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_twv9_ok_command_line, Qpathname_for_disabling_twv9_ok_command_line);

static Object array_constant_26;   /* # */

static Object array_constant_27;   /* # */

/* GET-OR-USE-TWV9-OK-PATHNAME */
Object get_or_use_twv9_ok_pathname varargs_1(int, n)
{
    Object provide_desired_namestring_p;
    Declare_varargs_nonrelocating;

    x_note_fn_call(106,78);
    INIT_ARGS_nonrelocating();
    provide_desired_namestring_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return provide_pathname_for_launch_time_load(Default_twv9_ok_pathname,
	    Pathname_for_disabling_twv9_ok_command_line,array_constant_26,
	    array_constant_27,array_constant_8,provide_desired_namestring_p);
}

static Object array_constant_28;   /* # */

/* INITIALIZE-DEFAULT-TWV11-OK-PATHNAME */
Object initialize_default_twv11_ok_pathname()
{
    x_note_fn_call(106,79);
    return gensym_make_pathname_with_copied_components(Nil,Nil,Nil,
	    array_constant_28,array_constant_8,Knewest,
	    Process_specific_system_pathname);
}

DEFINE_VARIABLE_WITH_SYMBOL(Default_twv11_ok_pathname, Qdefault_twv11_ok_pathname);

/* INITIALIZER-FOR-PATHNAME-FOR-DISABLING-TWV11-OK-COMMAND-LINE */
Object initializer_for_pathname_for_disabling_twv11_ok_command_line()
{
    x_note_fn_call(106,80);
    return gensym_make_pathname_with_copied_components(Nil,Nil,
	    list_constant,array_constant_13,array_constant_10,Knewest,Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_twv11_ok_command_line, Qpathname_for_disabling_twv11_ok_command_line);

static Object array_constant_29;   /* # */

static Object array_constant_30;   /* # */

/* GET-OR-USE-TWV11-OK-PATHNAME */
Object get_or_use_twv11_ok_pathname varargs_1(int, n)
{
    Object provide_desired_namestring_p;
    Declare_varargs_nonrelocating;

    x_note_fn_call(106,81);
    INIT_ARGS_nonrelocating();
    provide_desired_namestring_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return provide_pathname_for_launch_time_load(Default_twv11_ok_pathname,
	    Pathname_for_disabling_twv11_ok_command_line,array_constant_29,
	    array_constant_30,array_constant_8,provide_desired_namestring_p);
}

static Object array_constant_31;   /* # */

/* INITIALIZE-DEFAULT-TWV12-OK-PATHNAME */
Object initialize_default_twv12_ok_pathname()
{
    x_note_fn_call(106,82);
    return gensym_make_pathname_with_copied_components(Nil,Nil,Nil,
	    array_constant_31,array_constant_8,Knewest,
	    Process_specific_system_pathname);
}

DEFINE_VARIABLE_WITH_SYMBOL(Default_twv12_ok_pathname, Qdefault_twv12_ok_pathname);

/* INITIALIZER-FOR-PATHNAME-FOR-DISABLING-TWV12-OK-COMMAND-LINE */
Object initializer_for_pathname_for_disabling_twv12_ok_command_line()
{
    x_note_fn_call(106,83);
    return gensym_make_pathname_with_copied_components(Nil,Nil,
	    list_constant,array_constant_13,array_constant_10,Knewest,Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_twv12_ok_command_line, Qpathname_for_disabling_twv12_ok_command_line);

static Object array_constant_32;   /* # */

static Object array_constant_33;   /* # */

/* GET-OR-USE-TWV12-OK-PATHNAME */
Object get_or_use_twv12_ok_pathname varargs_1(int, n)
{
    Object provide_desired_namestring_p;
    Declare_varargs_nonrelocating;

    x_note_fn_call(106,84);
    INIT_ARGS_nonrelocating();
    provide_desired_namestring_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return provide_pathname_for_launch_time_load(Default_twv12_ok_pathname,
	    Pathname_for_disabling_twv12_ok_command_line,array_constant_32,
	    array_constant_33,array_constant_8,provide_desired_namestring_p);
}

static Object array_constant_34;   /* # */

/* INITIALIZE-DEFAULT-G2-OK-PATHNAME */
Object initialize_default_g2_ok_pathname()
{
    x_note_fn_call(106,85);
    return gensym_make_pathname_with_copied_components(Nil,Nil,Nil,
	    array_constant_34,array_constant_8,Knewest,
	    Process_specific_system_pathname);
}

DEFINE_VARIABLE_WITH_SYMBOL(Default_g2_ok_pathname, Qdefault_g2_ok_pathname);

/* INITIALIZER-FOR-PATHNAME-FOR-DISABLING-G2-OK-COMMAND-LINE */
Object initializer_for_pathname_for_disabling_g2_ok_command_line()
{
    x_note_fn_call(106,86);
    return gensym_make_pathname_with_copied_components(Nil,Nil,
	    list_constant,array_constant_13,array_constant_10,Knewest,Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_g2_ok_command_line, Qpathname_for_disabling_g2_ok_command_line);

static Object array_constant_35;   /* # */

/* GET-OR-USE-G2-OK-PATHNAME */
Object get_or_use_g2_ok_pathname varargs_1(int, n)
{
    Object provide_desired_namestring_p;
    Declare_varargs_nonrelocating;

    x_note_fn_call(106,87);
    INIT_ARGS_nonrelocating();
    provide_desired_namestring_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return provide_pathname_for_launch_time_load(Default_g2_ok_pathname,
	    Pathname_for_disabling_g2_ok_command_line,array_constant_8,
	    array_constant_35,array_constant_8,provide_desired_namestring_p);
}

static Object array_constant_36;   /* # */

/* INITIALIZE-DEFAULT-G2V5-OK-PATHNAME */
Object initialize_default_g2v5_ok_pathname()
{
    x_note_fn_call(106,88);
    return gensym_make_pathname_with_copied_components(Nil,Nil,Nil,
	    array_constant_36,array_constant_8,Knewest,
	    Process_specific_system_pathname);
}

DEFINE_VARIABLE_WITH_SYMBOL(Default_g2v5_ok_pathname, Qdefault_g2v5_ok_pathname);

/* INITIALIZER-FOR-PATHNAME-FOR-DISABLING-G2V5-OK-COMMAND-LINE */
Object initializer_for_pathname_for_disabling_g2v5_ok_command_line()
{
    x_note_fn_call(106,89);
    return gensym_make_pathname_with_copied_components(Nil,Nil,
	    list_constant,array_constant_13,array_constant_10,Knewest,Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_g2v5_ok_command_line, Qpathname_for_disabling_g2v5_ok_command_line);

static Object array_constant_37;   /* # */

/* GET-OR-USE-G2V5-OK-PATHNAME */
Object get_or_use_g2v5_ok_pathname varargs_1(int, n)
{
    Object provide_desired_namestring_p;
    Declare_varargs_nonrelocating;

    x_note_fn_call(106,90);
    INIT_ARGS_nonrelocating();
    provide_desired_namestring_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return provide_pathname_for_launch_time_load(Default_g2v5_ok_pathname,
	    Pathname_for_disabling_g2v5_ok_command_line,array_constant_14,
	    array_constant_37,array_constant_8,provide_desired_namestring_p);
}

static Object array_constant_38;   /* # */

/* INITIALIZE-DEFAULT-G2V51-OK-PATHNAME */
Object initialize_default_g2v51_ok_pathname()
{
    x_note_fn_call(106,91);
    return gensym_make_pathname_with_copied_components(Nil,Nil,Nil,
	    array_constant_38,array_constant_8,Knewest,
	    Process_specific_system_pathname);
}

DEFINE_VARIABLE_WITH_SYMBOL(Default_g2v51_ok_pathname, Qdefault_g2v51_ok_pathname);

/* INITIALIZER-FOR-PATHNAME-FOR-DISABLING-G2V51-OK-COMMAND-LINE */
Object initializer_for_pathname_for_disabling_g2v51_ok_command_line()
{
    x_note_fn_call(106,92);
    return gensym_make_pathname_with_copied_components(Nil,Nil,
	    list_constant,array_constant_13,array_constant_10,Knewest,Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_g2v51_ok_command_line, Qpathname_for_disabling_g2v51_ok_command_line);

static Object array_constant_39;   /* # */

static Object array_constant_40;   /* # */

/* GET-OR-USE-G2V51-OK-PATHNAME */
Object get_or_use_g2v51_ok_pathname varargs_1(int, n)
{
    Object provide_desired_namestring_p;
    Declare_varargs_nonrelocating;

    x_note_fn_call(106,93);
    INIT_ARGS_nonrelocating();
    provide_desired_namestring_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return provide_pathname_for_launch_time_load(Default_g2v51_ok_pathname,
	    Pathname_for_disabling_g2v51_ok_command_line,array_constant_39,
	    array_constant_40,array_constant_8,provide_desired_namestring_p);
}

static Object array_constant_41;   /* # */

/* INITIALIZE-DEFAULT-G2V6-OK-PATHNAME */
Object initialize_default_g2v6_ok_pathname()
{
    x_note_fn_call(106,94);
    return gensym_make_pathname_with_copied_components(Nil,Nil,Nil,
	    array_constant_41,array_constant_8,Knewest,
	    Process_specific_system_pathname);
}

DEFINE_VARIABLE_WITH_SYMBOL(Default_g2v6_ok_pathname, Qdefault_g2v6_ok_pathname);

/* INITIALIZER-FOR-PATHNAME-FOR-DISABLING-G2V6-OK-COMMAND-LINE */
Object initializer_for_pathname_for_disabling_g2v6_ok_command_line()
{
    x_note_fn_call(106,95);
    return gensym_make_pathname_with_copied_components(Nil,Nil,
	    list_constant,array_constant_13,array_constant_10,Knewest,Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_g2v6_ok_command_line, Qpathname_for_disabling_g2v6_ok_command_line);

static Object array_constant_42;   /* # */

/* GET-OR-USE-G2V6-OK-PATHNAME */
Object get_or_use_g2v6_ok_pathname varargs_1(int, n)
{
    Object provide_desired_namestring_p;
    Declare_varargs_nonrelocating;

    x_note_fn_call(106,96);
    INIT_ARGS_nonrelocating();
    provide_desired_namestring_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return provide_pathname_for_launch_time_load(Default_g2v6_ok_pathname,
	    Pathname_for_disabling_g2v6_ok_command_line,array_constant_17,
	    array_constant_42,array_constant_8,provide_desired_namestring_p);
}

static Object array_constant_43;   /* # */

/* INITIALIZE-DEFAULT-G2V7-OK-PATHNAME */
Object initialize_default_g2v7_ok_pathname()
{
    x_note_fn_call(106,97);
    return gensym_make_pathname_with_copied_components(Nil,Nil,Nil,
	    array_constant_43,array_constant_8,Knewest,
	    Process_specific_system_pathname);
}

DEFINE_VARIABLE_WITH_SYMBOL(Default_g2v7_ok_pathname, Qdefault_g2v7_ok_pathname);

/* INITIALIZER-FOR-PATHNAME-FOR-DISABLING-G2V7-OK-COMMAND-LINE */
Object initializer_for_pathname_for_disabling_g2v7_ok_command_line()
{
    x_note_fn_call(106,98);
    return gensym_make_pathname_with_copied_components(Nil,Nil,
	    list_constant,array_constant_13,array_constant_10,Knewest,Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_g2v7_ok_command_line, Qpathname_for_disabling_g2v7_ok_command_line);

static Object array_constant_44;   /* # */

/* GET-OR-USE-G2V7-OK-PATHNAME */
Object get_or_use_g2v7_ok_pathname varargs_1(int, n)
{
    Object provide_desired_namestring_p;
    Declare_varargs_nonrelocating;

    x_note_fn_call(106,99);
    INIT_ARGS_nonrelocating();
    provide_desired_namestring_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return provide_pathname_for_launch_time_load(Default_g2v7_ok_pathname,
	    Pathname_for_disabling_g2v7_ok_command_line,array_constant_20,
	    array_constant_44,array_constant_8,provide_desired_namestring_p);
}

static Object array_constant_45;   /* # */

/* INITIALIZE-DEFAULT-G2V8-OK-PATHNAME */
Object initialize_default_g2v8_ok_pathname()
{
    x_note_fn_call(106,100);
    return gensym_make_pathname_with_copied_components(Nil,Nil,Nil,
	    array_constant_45,array_constant_8,Knewest,
	    Process_specific_system_pathname);
}

DEFINE_VARIABLE_WITH_SYMBOL(Default_g2v8_ok_pathname, Qdefault_g2v8_ok_pathname);

/* INITIALIZER-FOR-PATHNAME-FOR-DISABLING-G2V8-OK-COMMAND-LINE */
Object initializer_for_pathname_for_disabling_g2v8_ok_command_line()
{
    x_note_fn_call(106,101);
    return gensym_make_pathname_with_copied_components(Nil,Nil,
	    list_constant,array_constant_13,array_constant_10,Knewest,Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_g2v8_ok_command_line, Qpathname_for_disabling_g2v8_ok_command_line);

static Object array_constant_46;   /* # */

/* GET-OR-USE-G2V8-OK-PATHNAME */
Object get_or_use_g2v8_ok_pathname varargs_1(int, n)
{
    Object provide_desired_namestring_p;
    Declare_varargs_nonrelocating;

    x_note_fn_call(106,102);
    INIT_ARGS_nonrelocating();
    provide_desired_namestring_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return provide_pathname_for_launch_time_load(Default_g2v8_ok_pathname,
	    Pathname_for_disabling_g2v8_ok_command_line,array_constant_23,
	    array_constant_46,array_constant_8,provide_desired_namestring_p);
}

static Object array_constant_47;   /* # */

/* INITIALIZE-DEFAULT-G2V83-OK-PATHNAME */
Object initialize_default_g2v83_ok_pathname()
{
    x_note_fn_call(106,103);
    return gensym_make_pathname_with_copied_components(Nil,Nil,Nil,
	    array_constant_47,array_constant_8,Knewest,
	    Process_specific_system_pathname);
}

DEFINE_VARIABLE_WITH_SYMBOL(Default_g2v83_ok_pathname, Qdefault_g2v83_ok_pathname);

/* INITIALIZER-FOR-PATHNAME-FOR-DISABLING-G2V83-OK-COMMAND-LINE */
Object initializer_for_pathname_for_disabling_g2v83_ok_command_line()
{
    x_note_fn_call(106,104);
    return gensym_make_pathname_with_copied_components(Nil,Nil,
	    list_constant,array_constant_13,array_constant_10,Knewest,Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_g2v83_ok_command_line, Qpathname_for_disabling_g2v83_ok_command_line);

static Object array_constant_48;   /* # */

static Object array_constant_49;   /* # */

/* GET-OR-USE-G2V83-OK-PATHNAME */
Object get_or_use_g2v83_ok_pathname varargs_1(int, n)
{
    Object provide_desired_namestring_p;
    Declare_varargs_nonrelocating;

    x_note_fn_call(106,105);
    INIT_ARGS_nonrelocating();
    provide_desired_namestring_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return provide_pathname_for_launch_time_load(Default_g2v83_ok_pathname,
	    Pathname_for_disabling_g2v83_ok_command_line,array_constant_48,
	    array_constant_49,array_constant_8,provide_desired_namestring_p);
}

static Object array_constant_50;   /* # */

/* INITIALIZE-DEFAULT-G2V9-OK-PATHNAME */
Object initialize_default_g2v9_ok_pathname()
{
    x_note_fn_call(106,106);
    return gensym_make_pathname_with_copied_components(Nil,Nil,Nil,
	    array_constant_50,array_constant_8,Knewest,
	    Process_specific_system_pathname);
}

DEFINE_VARIABLE_WITH_SYMBOL(Default_g2v9_ok_pathname, Qdefault_g2v9_ok_pathname);

/* INITIALIZER-FOR-PATHNAME-FOR-DISABLING-G2V9-OK-COMMAND-LINE */
Object initializer_for_pathname_for_disabling_g2v9_ok_command_line()
{
    x_note_fn_call(106,107);
    return gensym_make_pathname_with_copied_components(Nil,Nil,
	    list_constant,array_constant_13,array_constant_10,Knewest,Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_g2v9_ok_command_line, Qpathname_for_disabling_g2v9_ok_command_line);

static Object array_constant_51;   /* # */

/* GET-OR-USE-G2V9-OK-PATHNAME */
Object get_or_use_g2v9_ok_pathname varargs_1(int, n)
{
    Object provide_desired_namestring_p;
    Declare_varargs_nonrelocating;

    x_note_fn_call(106,108);
    INIT_ARGS_nonrelocating();
    provide_desired_namestring_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return provide_pathname_for_launch_time_load(Default_g2v9_ok_pathname,
	    Pathname_for_disabling_g2v9_ok_command_line,array_constant_26,
	    array_constant_51,array_constant_8,provide_desired_namestring_p);
}

static Object array_constant_52;   /* # */

/* INITIALIZE-DEFAULT-G2V11-OK-PATHNAME */
Object initialize_default_g2v11_ok_pathname()
{
    x_note_fn_call(106,109);
    return gensym_make_pathname_with_copied_components(Nil,Nil,Nil,
	    array_constant_52,array_constant_8,Knewest,
	    Process_specific_system_pathname);
}

DEFINE_VARIABLE_WITH_SYMBOL(Default_g2v11_ok_pathname, Qdefault_g2v11_ok_pathname);

/* INITIALIZER-FOR-PATHNAME-FOR-DISABLING-G2V11-OK-COMMAND-LINE */
Object initializer_for_pathname_for_disabling_g2v11_ok_command_line()
{
    x_note_fn_call(106,110);
    return gensym_make_pathname_with_copied_components(Nil,Nil,
	    list_constant,array_constant_13,array_constant_10,Knewest,Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_g2v11_ok_command_line, Qpathname_for_disabling_g2v11_ok_command_line);

static Object array_constant_53;   /* # */

/* GET-OR-USE-G2V11-OK-PATHNAME */
Object get_or_use_g2v11_ok_pathname varargs_1(int, n)
{
    Object provide_desired_namestring_p;
    Declare_varargs_nonrelocating;

    x_note_fn_call(106,111);
    INIT_ARGS_nonrelocating();
    provide_desired_namestring_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return provide_pathname_for_launch_time_load(Default_g2v11_ok_pathname,
	    Pathname_for_disabling_g2v11_ok_command_line,array_constant_29,
	    array_constant_53,array_constant_8,provide_desired_namestring_p);
}

static Object array_constant_54;   /* # */

/* INITIALIZE-DEFAULT-G2V12-OK-PATHNAME */
Object initialize_default_g2v12_ok_pathname()
{
    x_note_fn_call(106,112);
    return gensym_make_pathname_with_copied_components(Nil,Nil,Nil,
	    array_constant_54,array_constant_8,Knewest,
	    Process_specific_system_pathname);
}

DEFINE_VARIABLE_WITH_SYMBOL(Default_g2v12_ok_pathname, Qdefault_g2v12_ok_pathname);

/* INITIALIZER-FOR-PATHNAME-FOR-DISABLING-G2V12-OK-COMMAND-LINE */
Object initializer_for_pathname_for_disabling_g2v12_ok_command_line()
{
    x_note_fn_call(106,113);
    return gensym_make_pathname_with_copied_components(Nil,Nil,
	    list_constant,array_constant_13,array_constant_10,Knewest,Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_g2v12_ok_command_line, Qpathname_for_disabling_g2v12_ok_command_line);

static Object array_constant_55;   /* # */

/* GET-OR-USE-G2V12-OK-PATHNAME */
Object get_or_use_g2v12_ok_pathname varargs_1(int, n)
{
    Object provide_desired_namestring_p;
    Declare_varargs_nonrelocating;

    x_note_fn_call(106,114);
    INIT_ARGS_nonrelocating();
    provide_desired_namestring_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return provide_pathname_for_launch_time_load(Default_g2v12_ok_pathname,
	    Pathname_for_disabling_g2v12_ok_command_line,array_constant_32,
	    array_constant_55,array_constant_8,provide_desired_namestring_p);
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_7;   /* "(Authorization file: ~a; Machine ID" */

static Object string_constant_8;   /* "(none found)" */

static Object string_constant_9;   /* ": (none found))" */

static Object string_constant_10;  /* ": ~a)" */

static Object string_constant_11;  /* "s:" */

static Object string_constant_12;  /* "~a" */

static Object string_constant_13;  /* ", " */

static Object string_constant_14;  /* ")" */

/* MAKE-AUTHORIZATION-FILE-STATUS-STRING */
Object make_authorization_file_status_string(pathname_qm,machine_ids)
    Object pathname_qm, machine_ids;
{
    volatile Object namestring_1;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object ids;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(5);
    Object result;

    x_note_fn_call(106,115);
    SAVE_STACK();
    namestring_1 = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	namestring_1 = pathname_qm ? gensym_enough_namestring(1,
		pathname_qm) : Nil;
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
		  tformat(2,string_constant_7,pathname_qm ? namestring_1 : 
			  string_constant_8);
		  if ( !TRUEP(machine_ids))
		      tformat(1,string_constant_9);
		  else if ( !TRUEP(CDR(machine_ids)))
		      tformat(2,string_constant_10,FIRST(machine_ids));
		  else {
		      tformat(1,string_constant_11);
		      ids = machine_ids;
		    next_loop:
		      if ( !TRUEP(ids))
			  goto end_loop;
		      tformat(2,string_constant_12,FIRST(ids));
		      if (CDR(ids))
			  tformat(1,string_constant_13);
		      ids = M_CDR(ids);
		      goto next_loop;
		    end_loop:;
		      tformat(1,string_constant_14);
		  }
		  SAVE_VALUES(copy_out_current_wide_string());
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    POP_UNWIND_PROTECT(0);
    if (namestring_1) {
	if ( !EQ(namestring_1,Qunbound_in_protected_let))
	    reclaim_text_string(namestring_1);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object Qoffline;            /* offline */

static Object list_constant_1;     /* # */

/* SORT-SCHEDULED-PRIORITIES */
Object sort_scheduled_priorities(authorized_products)
    Object authorized_products;
{
    Object result_1, product, ab_loop_list_, temp, product_1, clearbits_arg;
    SI_Long result_new_value;

    x_note_fn_call(106,116);
    result_1 = FIX((SI_Long)0L);
    product = Nil;
    ab_loop_list_ = authorized_products;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    product = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = assq_function(product,Optional_modules_map);
    result_1 = FIXNUM_LOGIOR(result_1,SECOND(temp));
    goto next_loop;
  end_loop:
    if (memq_function(Qoffline,authorized_products)) {
	product_1 = Nil;
	ab_loop_list_ = list_constant_1;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	product_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(memq_function(product_1,authorized_products))) {
	    temp = assq_function(product_1,Optional_modules_map);
	    clearbits_arg = SECOND(temp);
	    result_new_value = IFIX(result_1) &  ~IFIX(clearbits_arg);
	    result_1 = FIX(result_new_value);
	}
	goto next_loop_1;
      end_loop_1:;
    }
    return VALUES_1(result_1);
    return VALUES_1(Qnil);
}

/* MAKE-ARRAY-FROM-STRINGS */
Object make_array_from_strings(text_string_1,text_string_2)
    Object text_string_1, text_string_2;
{
    Object length1, length2, nlength1, nlength2, array, w1, w2, i1, i2;
    Object aref_new_value;
    SI_Long length_1, i, ab_loop_bind_, ab_loopvar_, aref_arg_2;

    x_note_fn_call(106,117);
    length1 = lengthw(text_string_1);
    length2 = lengthw(text_string_2);
    length_1 = IFIX(lengthw(text_string_1));
    i = (SI_Long)0L;
    ab_loop_bind_ = length_1;
    ab_loopvar_ = (SI_Long)0L;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    if (digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(text_string_1,i)),
	    FIX((SI_Long)36L)))
	ab_loopvar_ = ab_loopvar_ + (SI_Long)1L;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    nlength1 = FIX(ab_loopvar_);
    goto end_1;
    nlength1 = Qnil;
  end_1:;
    length_1 = IFIX(lengthw(text_string_2));
    i = (SI_Long)0L;
    ab_loop_bind_ = length_1;
    ab_loopvar_ = (SI_Long)0L;
  next_loop_1:
    if (i >= ab_loop_bind_)
	goto end_loop_1;
    if (digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(text_string_2,i)),
	    FIX((SI_Long)36L)))
	ab_loopvar_ = ab_loopvar_ + (SI_Long)1L;
    i = i + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:
    nlength2 = FIX(ab_loopvar_);
    goto end_2;
    nlength2 = Qnil;
  end_2:;
    array = make_array(1,FIXNUM_ADD(nlength1,nlength2));
    w1 = Nil;
    w2 = Nil;
    i1 = FIX((SI_Long)0L);
    i2 = FIX((SI_Long)0L);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(FIXNUM_MAX(nlength1,nlength2));
  next_loop_2:
    if (i >= ab_loop_bind_)
	goto end_loop_2;
  next_loop_3:
    if (FIXNUM_GE(i1,length1))
	goto end_loop_3;
    w1 = digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(text_string_1,
	    IFIX(i1))),FIX((SI_Long)36L));
    if (w1) {
	i1 = FIXNUM_ADD1(i1);
	goto end_3;
    }
    i1 = FIXNUM_ADD1(i1);
    goto next_loop_3;
  end_loop_3:
    w1 = Nil;
  end_3:
  next_loop_4:
    if (FIXNUM_GE(i2,length2))
	goto end_loop_4;
    w2 = digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(text_string_2,
	    IFIX(i2))),FIX((SI_Long)36L));
    if (w2) {
	i2 = FIXNUM_ADD1(i2);
	goto end_4;
    }
    i2 = FIXNUM_ADD1(i2);
    goto next_loop_4;
  end_loop_4:
    w2 = Nil;
  end_4:
    if (i < IFIX(nlength1))
	set_aref1(array,FIX(i),w1);
    if (i < IFIX(nlength2)) {
	aref_arg_2 = i + IFIX(nlength1);
	set_aref1(array,FIX(aref_arg_2),w2);
    }
    i = i + (SI_Long)1L;
    goto next_loop_2;
  end_loop_2:
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(FIXNUM_ADD(nlength1,nlength2)) + (SI_Long)-2L;
  next_loop_5:
    if (i > ab_loop_bind_)
	goto end_loop_5;
    aref_arg_2 = i + (SI_Long)1L;
    aref_new_value = chestnut_modf_function(FIX((SI_Long)3769L * 
	    IFIX(aref1(array,FIX(i))) + (SI_Long)6237L * IFIX(aref1(array,
	    FIX(i + (SI_Long)1L)))),FIX((SI_Long)256L));
    set_aref1(array,FIX(aref_arg_2),aref_new_value);
    i = i + (SI_Long)1L;
    goto next_loop_5;
  end_loop_5:;
    return VALUES_1(array);
    return VALUES_1(Qnil);
}

Object No_valid_telewindows_ok_entry_message = UNBOUND;

Object Cannot_open_telewindows_ok_file_message = UNBOUND;

/* GET-TW-OK-INFO-FROM-STREAM */
Object get_tw_ok_info_from_stream(input_stream_qm,machine_ids_to_match)
    Object input_stream_qm, machine_ids_to_match;
{
    Object line_qm, result_1;

    x_note_fn_call(106,118);
    line_qm = Nil;
    result_1 = Nil;
  next_loop:
    line_qm = g2_stream_read_line(input_stream_qm);
    if ( !TRUEP(line_qm))
	goto end_loop;
    result_1 = get_tw_ok_info_from_string(line_qm,machine_ids_to_match);
    if (result_1) {
	if (LISTP(result_1))
	    return VALUES_1(result_1);
	else
	    return VALUES_1(Nil);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

Object Telewindows_product_modules_to_select = UNBOUND;

/* GET-TW-MODULES-FROM-REMAINING-FIELDS */
Object get_tw_modules_from_remaining_fields(remaining_fields)
    Object remaining_fields;
{
    Object modules, x, ab_loop_list_, module_qm, user_name, internal_name;
    Object ab_loop_list__1, ab_loop_desetq_, temp;
    char temp_1;

    x_note_fn_call(106,119);
    modules = Nil;
  next_loop:
    x = Nil;
    ab_loop_list_ = remaining_fields;
    module_qm = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    x = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    user_name = Nil;
    internal_name = Nil;
    ab_loop_list__1 = Telewindows_product_modules_to_select;
    ab_loop_desetq_ = Nil;
  next_loop_2:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    ab_loop_desetq_ = M_CAR(ab_loop_list__1);
    user_name = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    internal_name = CAR(temp);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    temp = x;
    if (normalized_string_equal(2,temp,symbol_name_text_string(user_name))) {
	module_qm = internal_name;
	goto end_1;
    }
    goto next_loop_2;
  end_loop_1:
    module_qm = Qnil;
  end_1:;
    if (module_qm) {
	remaining_fields = delete_gensym_element_1(x,remaining_fields);
	reclaim_text_string(x);
	modules = gensym_cons_1(module_qm,modules);
	temp_1 = TRUEP(T);
	goto end_2;
    }
    goto next_loop_1;
  end_loop:
    temp_1 = TRUEP(Qnil);
  end_2:;
    if ( !temp_1)
	goto end_loop_2;
    goto next_loop;
  end_loop_2:
    return VALUES_2(remaining_fields,modules);
}

static Object array_constant_56;   /* # */

static Object Qfrom;               /* from */

static Object array_constant_57;   /* # */

static Object Qto;                 /* to */

/* GET-TW-DATES-FROM-REMAINING-FIELDS */
Object get_tw_dates_from_remaining_fields(remaining_fields)
    Object remaining_fields;
{
    Object start_date_qm, expiration_date_qm, x, day_string_qm;
    Object month_string_qm, year_string_qm, ab_loop_list_, from_or_to_qm, temp;
    Object day, month, year, date_list, universal_date_qm, temp_1, temp_2;
    char temp_3;

    x_note_fn_call(106,120);
    start_date_qm = Nil;
    expiration_date_qm = Nil;
  next_loop:
    x = Nil;
    day_string_qm = Nil;
    month_string_qm = Nil;
    year_string_qm = Nil;
    ab_loop_list_ = remaining_fields;
    from_or_to_qm = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    x = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    day_string_qm = CAR(temp);
    temp = CDR(ab_loop_list_);
    temp = CDR(temp);
    month_string_qm = CAR(temp);
    temp = CDR(ab_loop_list_);
    temp = CDR(temp);
    temp = CDR(temp);
    year_string_qm = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    from_or_to_qm = normalized_string_equal(2,array_constant_56,x) ? Qfrom 
	    : normalized_string_equal(2,array_constant_57,x) ? Qto : Nil;
    if (from_or_to_qm && day_string_qm && month_string_qm && year_string_qm) {
	temp = day_string_qm;
	day = read_positive_fixnum_from_string(temp,FIX((SI_Long)0L),
		text_string_length(day_string_qm));
	temp = month_string_qm;
	month = read_symbol_from_string(temp,FIX((SI_Long)0L),
		text_string_length(month_string_qm));
	temp = year_string_qm;
	year = read_positive_fixnum_from_string(temp,FIX((SI_Long)0L),
		text_string_length(year_string_qm));
	date_list = gensym_list_3(day,month,year);
	universal_date_qm = day && month && year && 
		valid_universal_date_elements_p(day,month,year) ? 
		convert_input_to_universal_date(date_list) : Nil;
	if (universal_date_qm) {
	    if (EQ(from_or_to_qm,Qfrom))
		start_date_qm = universal_date_qm;
	    else
		expiration_date_qm = universal_date_qm;
	}
	temp_1 = x;
	temp_2 = day_string_qm;
	temp = month_string_qm;
	remaining_fields = delete_gensym_element_1(temp_1,
		delete_gensym_element_1(temp_2,
		delete_gensym_element_1(temp,
		delete_gensym_element_1(year_string_qm,remaining_fields))));
	reclaim_gensym_list_1(date_list);
	reclaim_text_string(x);
	reclaim_text_string(day_string_qm);
	reclaim_text_string(month_string_qm);
	reclaim_text_string(year_string_qm);
	temp_3 = TRUEP(T);
	goto end_1;
    }
    goto next_loop_1;
  end_loop:
    temp_3 = TRUEP(Qnil);
  end_1:;
    if ( !temp_3)
	goto end_loop_1;
    goto next_loop;
  end_loop_1:
    return VALUES_3(remaining_fields,start_date_qm,expiration_date_qm);
}

/* GET-TW-PROCESS-LIMIT-FROM-REMAINING-FIELDS */
Object get_tw_process_limit_from_remaining_fields(remaining_fields)
    Object remaining_fields;
{
    Object x, ab_loop_list_, integer_qm, temp;

    x_note_fn_call(106,121);
    x = Nil;
    ab_loop_list_ = remaining_fields;
    integer_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    x = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = x;
    integer_qm = read_positive_fixnum_from_string(temp,FIX((SI_Long)0L),
	    text_string_length(x));
    if (integer_qm) {
	remaining_fields = delete_gensym_element_1(x,remaining_fields);
	reclaim_text_string(x);
	return VALUES_2(remaining_fields,integer_qm);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object list_constant_2;     /* # */

static Object array_constant_58;   /* # */

static Object list_constant_3;     /* # */

static Object list_constant_4;     /* # */

static Object array_constant_59;   /* # */

static Object Qfloating;           /* floating */

static Object Qdoes_not_contain_5_codes;  /* does-not-contain-5-codes */

static Object Qshunned_machine_id_string;  /* shunned-machine-id-string */

/* GET-TW-OK-INFO-FROM-STRING */
Object get_tw_ok_info_from_string(string_1,machine_ids_to_match)
    Object string_1, machine_ids_to_match;
{
    Object fields, machine_id_string, machine_id, ab_loop_list_, ab_loop_it_;
    Object gensymed_symbol, gensymed_symbol_1, temp_1, host_name, code_string;
    Object length_1, code_qm, codes, ab_loopvar_, ab_loopvar__1;
    Object remaining_fields, modules, start_date_qm, expiration_date_qm;
    Object number_of_processes_qm, x, temp_2;
    SI_Long ab_loop_repeat_, code_count;
    char temp;
    Object result;

    x_note_fn_call(106,122);
    fields = parse_text_line_into_list_of_text_strings_function(string_1,
	    list_constant_2,list_constant_2,Nil,Nil,array_constant_58);
    machine_id_string = SECOND(fields);
    temp = IFIX(lengthw(machine_id_string)) > (SI_Long)5L && 
	    UBYTE_16_ISAREF_1(machine_id_string,(SI_Long)4L) == 
	    (SI_Long)58L && 
	    wide_character_member(FIX(UBYTE_16_ISAREF_1(machine_id_string,
	    (SI_Long)2L)),list_constant_3) && 
	    wide_character_member(FIX(UBYTE_16_ISAREF_1(machine_id_string,
	    (SI_Long)1L)),list_constant_4) && 
	    (UBYTE_16_ISAREF_1(machine_id_string,(SI_Long)3L) == 
	    (SI_Long)101L || UBYTE_16_ISAREF_1(machine_id_string,
	    (SI_Long)3L) == (SI_Long)69L) ? 
	    UBYTE_16_ISAREF_1(machine_id_string,(SI_Long)0L) == 
	    (SI_Long)83L || UBYTE_16_ISAREF_1(machine_id_string,
	    (SI_Long)0L) == (SI_Long)115L : TRUEP(Qnil);
    if (temp);
    else {
	machine_id = Nil;
	ab_loop_list_ = machine_ids_to_match;
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	machine_id = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_it_ = normalized_string_equal(2,SECOND(fields),machine_id);
	if (ab_loop_it_) {
	    temp = TRUEP(ab_loop_it_);
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = TRUEP(Qnil);
      end_1:;
    }
    if (temp) {
	if (IFIX(length(fields)) == (SI_Long)3L) {
	    if (normalized_string_equal(2,THIRD(fields),array_constant_59)) {
		gensymed_symbol = make_gensym_list_1(FIX((SI_Long)10L));
		gensymed_symbol_1 = gensymed_symbol;
		temp_1 = copy_text_string(FIRST(fields));
		M_CAR(gensymed_symbol_1) = temp_1;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp_1 = copy_text_string(SECOND(fields));
		M_CAR(gensymed_symbol_1) = temp_1;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		M_CAR(gensymed_symbol_1) = Nil;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		M_CAR(gensymed_symbol_1) = Nil;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		M_CAR(gensymed_symbol_1) = Nil;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		M_CAR(gensymed_symbol_1) = Nil;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		M_CAR(gensymed_symbol_1) = Nil;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		M_CAR(gensymed_symbol_1) = Nil;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		M_CAR(gensymed_symbol_1) = Nil;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp_1 = gensym_cons_1(Qfloating,Nil);
		M_CAR(gensymed_symbol_1) = temp_1;
		return VALUES_1(gensymed_symbol);
	    }
	    else
		return VALUES_1(Nil);
	}
	else if (FIXNUM_GE(length(fields),FIX((SI_Long)6L))) {
	    host_name = copy_text_string(FIRST(fields));
	    machine_id = copy_text_string(SECOND(fields));
	    code_string = Nil;
	    ab_loop_list_ = nthcdr(FIX((SI_Long)2L),fields);
	    length_1 = Nil;
	    code_qm = Nil;
	    ab_loop_repeat_ = (SI_Long)5L;
	    code_count = (SI_Long)0L;
	    codes = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    code_string = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    length_1 = text_string_length(code_string);
	    code_qm = read_positive_fixnum_from_string(code_string,
		    FIX((SI_Long)0L),length_1);
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_1;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    if ( !TRUEP(code_qm))
		goto end_loop_1;
	    code_count = code_count + (SI_Long)1L;
	    ab_loopvar__1 = gensym_cons_1(code_qm,Nil);
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		codes = ab_loopvar__1;
	    ab_loopvar_ = ab_loopvar__1;
	    goto next_loop_1;
	  end_loop_1:
	    if (code_count < (SI_Long)5L)
		return VALUES_1(Qdoes_not_contain_5_codes);
	    else if (shunned_machine_id_string_p(machine_id))
		return VALUES_1(Qshunned_machine_id_string);
	    else {
		remaining_fields = nthcdr(FIX((SI_Long)7L),fields);
		modules = Nil;
		start_date_qm = Nil;
		expiration_date_qm = Nil;
		number_of_processes_qm = Nil;
		temp_1 = nthcdr(FIX((SI_Long)6L),fields);
		M_CDR(temp_1) = Nil;
		x = Nil;
		ab_loop_list_ = fields;
	      next_loop_2:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_2;
		x = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		reclaim_text_string(x);
		goto next_loop_2;
	      end_loop_2:;
		reclaim_gensym_list_1(fields);
		result = get_tw_modules_from_remaining_fields(remaining_fields);
		MVS_2(result,remaining_fields,modules);
		result = get_tw_dates_from_remaining_fields(remaining_fields);
		MVS_3(result,remaining_fields,start_date_qm,
			expiration_date_qm);
		result = get_tw_process_limit_from_remaining_fields(remaining_fields);
		MVS_2(result,remaining_fields,number_of_processes_qm);
		temp_2 = gensym_list_2(host_name,machine_id);
		return VALUES_1(nconc2(temp_2,nconc2(codes,
			gensym_list_4(start_date_qm,expiration_date_qm,
			modules,number_of_processes_qm))));
	    }
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_15;  /* "[Telewindows: unable to locate a Telewindows OK file ...]" */

static Object string_constant_16;  /* "~%[Telewindows: using Telewindows OK file: ~s]" */

static Object Qg2_defstruct_structure_name_gensym_pathname_g2_struct;  /* g2-defstruct-structure-name::gensym-pathname-g2-struct */

static Object string_constant_17;  /* "[Telewindows: ~a]" */

static Object string_constant_18;  /* "[Telewindows: no local authorization found for this machine]" */

/* FIND-MACHINE-ID-IN-TELEWINDOWS-OK-FILE */
Object find_machine_id_in_telewindows_ok_file()
{
    Object tw_ok_pathname_qm, namestring_for_tw_ok_file_qm;
    volatile Object machine_ids;
    volatile Object pathname_used_p;
    volatile Object namestring_1;
    volatile Object input_stream_qm;
    Object ok_information_qm, gensymed_symbol, machine_id, code_1, code_2;
    Object code_3, code_4, code_5, start_date_qm, expiration_date_qm;
    Object optional_modules, number_of_processes_qm;
    volatile Object status_string;
    Object temp;
    Declare_stack_pointer;
    Declare_catch(3);
    Object result;

    x_note_fn_call(106,123);
    SAVE_STACK();
    tw_ok_pathname_qm = get_appropriate_ok_pathname(1,T);
    namestring_for_tw_ok_file_qm = tw_ok_pathname_qm ? gensym_namestring(1,
	    tw_ok_pathname_qm) : Nil;
    if ( !TRUEP(namestring_for_tw_ok_file_qm)) {
	if (EQ(Verbosity_level,Qverbose))
	    notify_user(1,string_constant_15);
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
    else if (g2_stream_probe_file_for_read(namestring_for_tw_ok_file_qm)) {
	machine_ids = Qunbound_in_protected_let;
	if (PUSH_UNWIND_PROTECT(2)) {
	    machine_ids = get_local_machine_ids_as_gensym_list();
	    if (EQ(Verbosity_level,Qverbose))
		notify_user(2,string_constant_16,namestring_for_tw_ok_file_qm);
	    pathname_used_p = Qunbound_in_protected_let;
	    namestring_1 = Qunbound_in_protected_let;
	    input_stream_qm = Qunbound_in_protected_let;
	    if (PUSH_UNWIND_PROTECT(1)) {
		pathname_used_p = 
			SIMPLE_VECTOR_P(namestring_for_tw_ok_file_qm) ? 
			(EQ(ISVREF(namestring_for_tw_ok_file_qm,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_gensym_pathname_g2_struct) 
			? T : Nil) : Qnil;
		namestring_1 = 
			SIMPLE_VECTOR_P(namestring_for_tw_ok_file_qm) && 
			EQ(ISVREF(namestring_for_tw_ok_file_qm,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_gensym_pathname_g2_struct) 
			? gensym_namestring(1,
			namestring_for_tw_ok_file_qm) : 
			namestring_for_tw_ok_file_qm;
		input_stream_qm = g2_stream_open_for_input(namestring_1);
		if (input_stream_qm) {
		    ok_information_qm = 
			    get_tw_ok_info_from_stream(input_stream_qm,
			    machine_ids);
		    if (ok_information_qm && LISTP(ok_information_qm)) {
			gensymed_symbol = ok_information_qm;
			gensymed_symbol = CDR(gensymed_symbol);
			machine_id = CAR(gensymed_symbol);
			gensymed_symbol = CDR(gensymed_symbol);
			code_1 = CAR(gensymed_symbol);
			gensymed_symbol = CDR(gensymed_symbol);
			code_2 = CAR(gensymed_symbol);
			gensymed_symbol = CDR(gensymed_symbol);
			code_3 = CAR(gensymed_symbol);
			gensymed_symbol = CDR(gensymed_symbol);
			code_4 = CAR(gensymed_symbol);
			gensymed_symbol = CDR(gensymed_symbol);
			code_5 = CAR(gensymed_symbol);
			gensymed_symbol = CDR(gensymed_symbol);
			start_date_qm = CAR(gensymed_symbol);
			gensymed_symbol = CDR(gensymed_symbol);
			expiration_date_qm = CAR(gensymed_symbol);
			gensymed_symbol = CDR(gensymed_symbol);
			optional_modules = CAR(gensymed_symbol);
			gensymed_symbol = CDR(gensymed_symbol);
			number_of_processes_qm = CAR(gensymed_symbol);
			SAVE_VALUES(VALUES_10(machine_id,code_1,code_2,
				code_3,code_4,code_5,start_date_qm,
				expiration_date_qm,optional_modules,
				number_of_processes_qm));
		    }
		    else if (EQ(Verbosity_level,Qverbose)) {
			status_string = Qunbound_in_protected_let;
			if (PUSH_UNWIND_PROTECT(0)) {
			    temp = gensym_truename(input_stream_qm);
			    status_string = 
				    make_authorization_file_status_string(temp,
				    machine_ids);
			    notify_user(2,string_constant_17,status_string);
			    notify_user(1,string_constant_18);
			    SAVE_VALUES(VALUES_1(Nil));
			}
			POP_UNWIND_PROTECT(0);
			if (status_string) {
			    if ( !EQ(status_string,Qunbound_in_protected_let))
				reclaim_text_string(status_string);
			}
			CONTINUE_UNWINDING(0);
		    }
		    else
			SAVE_VALUES(VALUES_1(Nil));
		}
		else
		    SAVE_VALUES(VALUES_1(Nil));
	    }
	    POP_UNWIND_PROTECT(1);
	    if (input_stream_qm) {
		if ( !EQ(input_stream_qm,Qunbound_in_protected_let))
		    g2_stream_close(input_stream_qm);
	    }
	    if (namestring_1) {
		if ( !EQ(namestring_1,Qunbound_in_protected_let)) {
		    if (pathname_used_p)
			reclaim_text_string(namestring_1);
		}
	    }
	    CONTINUE_UNWINDING(1);
	}
	POP_UNWIND_PROTECT(2);
	if (machine_ids) {
	    if ( !EQ(machine_ids,Qunbound_in_protected_let))
		reclaim_gensym_tree_with_text_strings(machine_ids);
	}
	CONTINUE_UNWINDING(2);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Qnil);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Number_of_raster_oddspaces, Qnumber_of_raster_oddspaces);

Object Tw_months_of_the_year = UNBOUND;

/* VALID-UNIVERSAL-DATE-ELEMENTS-P */
Object valid_universal_date_elements_p(day,month,year)
    Object day, month, year;
{
    x_note_fn_call(106,124);
    if (FIXNUMP(day) && IFIX(day) >= (SI_Long)1L && IFIX(day) <= 
	    (SI_Long)31L && memq_function(month,Tw_months_of_the_year))
	return VALUES_1(FIXNUMP(year) ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* DECREASE-RASTER-DIMENSION */
Object decrease_raster_dimension(day,month,year)
    Object day, month, year;
{
    x_note_fn_call(106,125);
    if (FIXNUMP(day) && IFIX(day) >= (SI_Long)1L && IFIX(day) <= 
	    (SI_Long)31L && memq_function(month,Tw_months_of_the_year) && 
	    FIXNUMP(year))
	return VALUES_1(T);
    else {
	format((SI_Long)5L,T,
		"~%~%~s ~s ~s in the tw.ok file is not a valid date.~%",
		day,month,year);
	return VALUES_1(Nil);
    }
}

Object Map_month_to_number_code = UNBOUND;

/* CONVERT-INPUT-TO-UNIVERSAL-DATE */
Object convert_input_to_universal_date(list_1)
    Object list_1;
{
    Object day, month_input, month_code, month, days_in_month, year_abbrev;
    Object year;

    x_note_fn_call(106,126);
    day = FIRST(list_1);
    month_input = SECOND(list_1);
    if (SYMBOLP(month_input))
	month_code = assq_function(month_input,Map_month_to_number_code);
    else if ((SI_Long)1L <= IFIX(month_input) && IFIX(month_input) <= 
	    (SI_Long)12L)
	month_code = elt(Map_month_to_number_code,FIXNUM_SUB1(month_input));
    else
	return VALUES_1(Nil);
    month = SECOND(month_code);
    days_in_month = THIRD(month_code);
    year_abbrev = THIRD(list_1);
    year = IFIX(year_abbrev) <= (SI_Long)99L ? 
	    guess_year_from_two_digit_year(year_abbrev) : year_abbrev;
    if ((SI_Long)1899L < IFIX(year) && IFIX(year) < (SI_Long)2399L && 
	    (SI_Long)1L <= IFIX(month) && IFIX(month) <= (SI_Long)12L && 
	    IFIX(day) > (SI_Long)0L && (FIXNUM_LE(day,days_in_month) || 
	    leap_year_p(year) && IFIX(month) == (SI_Long)2L && IFIX(day) 
	    == (SI_Long)29L))
	return encode_universal_date(day,month,year);
    else
	return VALUES_1(Nil);
}

/* GUESS-YEAR-FROM-TWO-DIGIT-YEAR */
Object guess_year_from_two_digit_year(year_abbrev)
    Object year_abbrev;
{
    Object gensymed_symbol, current_year;
    SI_Long temp, this_century_guess;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(106,127);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	result = gensym_decode_unix_time(DOUBLE_TO_DOUBLE_FLOAT(g2ext_unix_time_as_float()));
	gensymed_symbol = NTH_VALUE((SI_Long)5L, result);
	current_year = gensymed_symbol;
    }
    POP_LOCAL_ALLOCATION(0,0);
    temp = IFIX(current_year) / (SI_Long)100L;
    this_century_guess = temp * (SI_Long)100L + IFIX(year_abbrev);
    return VALUES_1(this_century_guess >= IFIX(current_year) ? 
	    (this_century_guess - IFIX(current_year) < IFIX(current_year) 
	    - (this_century_guess - (SI_Long)100L) ? 
	    FIX(this_century_guess) : FIX(this_century_guess - 
	    (SI_Long)100L)) : IFIX(current_year) - this_century_guess < 
	    this_century_guess + (SI_Long)100L - IFIX(current_year) ? 
	    FIX(this_century_guess) : FIX(this_century_guess + (SI_Long)100L));
}

DEFINE_VARIABLE_WITH_SYMBOL(Icon_list_notes, Qicon_list_notes);

DEFINE_VARIABLE_WITH_SYMBOL(Graph_allocation_factor, Qgraph_allocation_factor);

DEFINE_VARIABLE_WITH_SYMBOL(Clogged_count, Qclogged_count);

DEFINE_VARIABLE_WITH_SYMBOL(Telewindows_screen_utilization, Qtelewindows_screen_utilization);

DEFINE_VARIABLE_WITH_SYMBOL(Time_of_last_expiration_check, Qtime_of_last_expiration_check);

DEFINE_VARIABLE_WITH_SYMBOL(Tw_expiration_check_interval, Qtw_expiration_check_interval);

static Object Qtw_expiration;      /* tw-expiration */

/* WARN-OF-TW-EXPIRATION-IF-NECESSARY-1 */
Object warn_of_tw_expiration_if_necessary_1()
{
    Object expiration_qm, days_left;

    x_note_fn_call(106,128);
    expiration_qm = EIGHTH(SECOND(Icon_list_notes));
    if (expiration_qm && FIXNUMP(expiration_qm)) {
	days_left = FIXNUM_MINUS(expiration_qm,get_tw_universal_date());
	if (IFIX(days_left) < (SI_Long)0L) {
	    format((SI_Long)2L,T,
		    "~%~%The authorization for this machine has expired.~%\n                        Telewindows will not run.~%");
	    force_output(_);
	    return abort_telewindows_top_level(Qtw_expiration);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Reclaimed_telewindows_boxes, Qreclaimed_telewindows_boxes);

/* CACHE-ICON-IN-SYSTEM-TABLE */
Object cache_icon_in_system_table()
{
    Object authorization_info_list, stored_machine_id, id1, id2, i, j, length1;
    Object length2, weight1, weight2, second_arg;
    char temp;

    x_note_fn_call(106,129);
    authorization_info_list = SECOND(Graph_allocation_factor);
    if (authorization_info_list && CONSP(authorization_info_list) && 
	    IFIX(length(authorization_info_list)) == (SI_Long)10L) {
	stored_machine_id = FIRST(authorization_info_list);
	if (text_string_p(stored_machine_id)) {
	    id1 = stored_machine_id;
	    id2 = pointer_to_first_string_in_pool_group();
	    i = FIX((SI_Long)0L);
	    j = FIX((SI_Long)0L);
	    length1 = text_string_length(id1);
	    length2 = text_string_length(id2);
	    weight1 = Nil;
	    weight2 = Nil;
	  next_loop:
	  next_loop_1:
	    if (FIXNUM_EQ(i,length1))
		goto end_loop;
	    weight1 = digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(id1,
		    IFIX(i))),FIX((SI_Long)36L));
	    i = add1(i);
	    if (weight1)
		goto end_1;
	    goto next_loop_1;
	  end_loop:
	    weight1 = Nil;
	  end_1:
	  next_loop_2:
	    if (FIXNUM_EQ(j,length2))
		goto end_loop_1;
	    weight2 = digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(id2,
		    IFIX(j))),FIX((SI_Long)36L));
	    j = add1(j);
	    if (weight2)
		goto end_2;
	    goto next_loop_2;
	  end_loop_1:
	    weight2 = Nil;
	  end_2:
	    if ( !TRUEP(weight1)) {
		temp =  !TRUEP(weight2);
		goto end_3;
	    }
	    else if ( !TRUEP(weight2)) {
		temp = TRUEP(Nil);
		goto end_3;
	    }
	    else if (FIXNUM_NE(weight1,weight2)) {
		temp = TRUEP(Nil);
		goto end_3;
	    }
	    goto next_loop;
	  end_loop_2:
	    temp = TRUEP(Qnil);
	  end_3:;
	}
	else
	    temp = TRUEP(Nil);
	if ( !temp) {
	    second_arg = Reclaimed_telewindows_boxes;
	    return VALUES_1(M_SECOND(second_arg) = Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* TELEWINDOWS-SCREEN-LIST-TOO-BIG */
Object telewindows_screen_list_too_big()
{
    Object authorization_info_list, machine_id, number1, number2, number3;
    Object number4, number5, start_date_qm, expiration_date_qm;
    Object authorized_products_bitmask, number_of_processes_qm;
    Object computed_number1, computed_number2, computed_number3;
    Object computed_number4, second_arg;
    char temp;
    Object result;

    x_note_fn_call(106,130);
    authorization_info_list = SECOND(Graph_allocation_factor);
    if (authorization_info_list && CONSP(authorization_info_list) && 
	    IFIX(length(authorization_info_list)) == (SI_Long)10L) {
	machine_id = FIRST(authorization_info_list);
	number1 = SECOND(authorization_info_list);
	number2 = THIRD(authorization_info_list);
	number3 = FOURTH(authorization_info_list);
	number4 = FIFTH(authorization_info_list);
	number5 = SIXTH(authorization_info_list);
	start_date_qm = SEVENTH(authorization_info_list);
	expiration_date_qm = EIGHTH(authorization_info_list);
	authorized_products_bitmask = NINTH(authorization_info_list);
	number_of_processes_qm = TENTH(authorization_info_list);
	if (text_string_p(machine_id) && FIXNUMP(number1) && 
		FIXNUMP(number2) && FIXNUMP(number3) && FIXNUMP(number4) 
		&& FIXNUMP(number5) && ( !TRUEP(start_date_qm) || 
		FIXNUMP(start_date_qm)) && ( !TRUEP(expiration_date_qm) || 
		FIXNUMP(expiration_date_qm))) {
	    result = enlarge_telewindows_memory(machine_id,start_date_qm,
		    expiration_date_qm,authorized_products_bitmask,
		    number_of_processes_qm);
	    MVS_4(result,computed_number1,computed_number2,
		    computed_number3,computed_number4);
	    temp = FIXNUM_EQ(number1,computed_number1) && 
		    FIXNUM_EQ(number2,computed_number2) && 
		    FIXNUM_EQ(number3,computed_number3) ? 
		    FIXNUM_EQ(number4,computed_number4) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if ( !temp) {
	    second_arg = Reclaimed_telewindows_boxes;
	    return VALUES_1(M_SECOND(second_arg) = Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* ENHANCE-GRAPHICS-COLORS */
Object enhance_graphics_colors()
{
    x_note_fn_call(106,131);
    if ( !TRUEP(SECOND(Reclaimed_telewindows_boxes)))
	return abort_telewindows_for_protocol_out_of_synch_case_6();
    else
	return VALUES_1(Nil);
}

static Object string_constant_19;  /* "~a~a" */

static Object Qjapanese;           /* japanese */

static Object Qkorean;             /* korean */

static Object Qruntime_option;     /* runtime-option */

static Object Qrestricted_use_option;  /* restricted-use-option */

static Object Qembedded_option;    /* embedded-option */

/* CHECK-SMALL-WORKSPACE */
Object check_small_workspace(machine_id,number1,number2,number3,number4,
	    start_date_qm,expiration_date_qm,authorized_products,
	    number_of_processes_qm)
    Object machine_id, number1, number2, number3, number4, start_date_qm;
    Object expiration_date_qm, authorized_products, number_of_processes_qm;
{
    Object keystring, gensymed_symbol, gensymed_symbol_1, expt_1, value;
    Object weight_qm, temp, modularized_key, japanese_qm, korean_qm, t1, t2;
    Object t3, t4, t5, t6, license_type_multiplier, t7, t8;
    SI_Long i, ab_loop_bind_, temp_1;

    x_note_fn_call(106,132);
    keystring = tformat_text_string(3,string_constant_19,machine_id,
	    Chaining_refresh_list);
    gensymed_symbol = keystring;
    gensymed_symbol_1 = New_modulus;
    expt_1 = FIX((SI_Long)1L);
    value = FIX((SI_Long)0L);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(FIXNUM_SUB1(lengthw(gensymed_symbol)));
    weight_qm = Nil;
  next_loop:
    if (i > ab_loop_bind_)
	goto end_loop;
    weight_qm = 
	    digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(gensymed_symbol,
	    i)),FIX((SI_Long)36L));
    if (weight_qm) {
	temp = value;
	temp_1 = IFIX(FIXNUM_TIMES(weight_qm,expt_1)) % 
		IFIX(gensymed_symbol_1);
	temp_1 = IFIX(FIXNUM_ADD(temp,FIX(temp_1))) % IFIX(gensymed_symbol_1);
	value = FIX(temp_1);
	temp_1 = IFIX(expt_1) * (SI_Long)36L % IFIX(gensymed_symbol_1);
	expt_1 = FIX(temp_1);
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = value;
    goto end_1;
    temp = Qnil;
  end_1:;
    reclaim_text_string(keystring);
    modularized_key = temp;
    japanese_qm = memq_function(Qjapanese,authorized_products);
    korean_qm = memq_function(Qkorean,authorized_products);
    if (IFIX(number1) < (SI_Long)100L)
	number1 = FIX((SI_Long)253L + (SI_Long)792L * IFIX(number1));
    if (IFIX(number2) < (SI_Long)100L)
	number2 = FIX((SI_Long)468L + (SI_Long)905L * IFIX(number2));
    if (IFIX(number3) < (SI_Long)100L)
	number3 = FIX((SI_Long)167L + (SI_Long)312L * IFIX(number3));
    if (IFIX(number4) < (SI_Long)100L)
	number4 = FIX((SI_Long)833L + (SI_Long)398L * IFIX(number4));
    t1 = start_date_qm;
    if (t1);
    else
	t1 = FIX((SI_Long)0L);
    t2 = expiration_date_qm;
    if (t2);
    else
	t2 = FIX((SI_Long)0L);
    t3 = add(japanese_qm ? FIX((SI_Long)5781L) : FIX((SI_Long)0L),
	    korean_qm ? FIX((SI_Long)2556L) : FIX((SI_Long)0L));
    t4 = add(japanese_qm ? number4 : FIX((SI_Long)0L),korean_qm ? number3 :
	     FIX((SI_Long)0L));
    t5 = number_of_processes_qm;
    if (t5);
    else
	t5 = FIX((SI_Long)1001L);
    t6 = number_of_processes_qm;
    if (t6);
    else
	t6 = FIX((SI_Long)1001L);
    if (memq_function(Qruntime_option,authorized_products))
	license_type_multiplier = number1;
    else if (memq_function(Qrestricted_use_option,authorized_products))
	license_type_multiplier = number2;
    else if (memq_function(Qembedded_option,authorized_products))
	license_type_multiplier = number3;
    else
	license_type_multiplier = FIX((SI_Long)0L);
    t7 = inner_multiply(license_type_multiplier,number1);
    t8 = inner_multiply(license_type_multiplier,number2);
    temp = inner_multiply(modularized_key,number1);
    temp = FIXNUM_LOGXOR(temp,inner_multiply(number2,number3));
    temp = FIXNUM_LOGXOR(temp,inner_multiply(number4,number4));
    temp = FIXNUM_LOGXOR(temp,inner_multiply(t1,t2));
    temp = FIXNUM_LOGXOR(temp,inner_multiply(t3,t4));
    temp = FIXNUM_LOGXOR(temp,inner_multiply(t5,t6));
    temp = FIXNUM_LOGXOR(temp,inner_multiply(t7,t8));
    return mod(temp,New_modulus);
}

/* MAKE-SMALL-WORKSPACE */
Object make_small_workspace(machine_id,code_1,code_2,code_3,code_4,code_5,
	    start_date_qm,expiration_date_qm,authorized_products,
	    number_of_processes_qm)
    Object machine_id, code_1, code_2, code_3, code_4, code_5, start_date_qm;
    Object expiration_date_qm, authorized_products, number_of_processes_qm;
{
    Object computed_code_5;

    x_note_fn_call(106,133);
    computed_code_5 = check_small_workspace(machine_id,code_1,code_2,
	    code_3,code_4,start_date_qm,expiration_date_qm,
	    authorized_products,number_of_processes_qm);
    return VALUES_1(FIXNUM_EQ(code_5,computed_code_5) ? T : Nil);
}

Object Too_late_telewindows_authorization_message = UNBOUND;

Object Too_early_telewindows_authorization_message = UNBOUND;

static Object Qruntime;            /* runtime */

static Object Qrestricted_use;     /* restricted-use */

static Object Qembedded;           /* embedded */

static Object Qcannot_register_process;  /* cannot-register-process */

static Object Qprocess_count_exceeded;  /* process-count-exceeded */

/* INITIALIZE-NETWORK-SCHEDULER-INTERWEAVE-MATRIX */
Object initialize_network_scheduler_interweave_matrix(authorized_products)
    Object authorized_products;
{
    Object system_1, option;
    Object unlimited_backtracking_in_internal_truth_maintenance_p_new_value;
    Object temp, temp_1;

    x_note_fn_call(106,134);
    if ( !TRUEP(Unlimited_backtracking_in_internal_truth_maintenance_p)) {
	system_1 = Tw_product;
	if (memq_function(Qruntime,authorized_products))
	    option = Tw_runtime_option;
	else if (memq_function(Qrestricted_use,authorized_products))
	    option = Tw_restricted_use_option;
	else if (memq_function(Qembedded,authorized_products))
	    option = Tw_embedded_option;
	else
	    option = Tw_development_option;
	unlimited_backtracking_in_internal_truth_maintenance_p_new_value = 
		(IFIX(update_frames_needing_icp_callback(system_1,option)) 
		== (SI_Long)1L ? TRUEP(T) : TRUEP(Nil)) ? 
		(g2ext_reduce_sleep_tolerance() != (SI_Long)-1L ? T : Nil) 
		: Nil;
	Unlimited_backtracking_in_internal_truth_maintenance_p = 
		unlimited_backtracking_in_internal_truth_maintenance_p_new_value;
    }
    if ( !TRUEP(Unlimited_backtracking_in_internal_truth_maintenance_p)) {
	notify_user(1,Tw_cannot_register_process_license_goodbye_message);
	return abort_telewindows_top_level(Qcannot_register_process);
    }
    else {
	temp =  !TRUEP(TENTH(SECOND(Icon_list_notes))) ? T : Nil;
	if (temp);
	else {
	    system_1 = Tw_product;
	    if (memq_function(Qruntime,authorized_products))
		option = Tw_runtime_option;
	    else if (memq_function(Qrestricted_use,authorized_products))
		option = Tw_restricted_use_option;
	    else if (memq_function(Qembedded,authorized_products))
		option = Tw_embedded_option;
	    else
		option = Tw_development_option;
	    temp_1 = frequently_typed_characters(system_1,option);
	    temp = TENTH(SECOND(Icon_list_notes));
	    if (temp);
	    else
		temp = FIX((SI_Long)2L);
	    temp = NUM_LT(temp_1,temp) ? T : Nil;
	}
	if (temp)
	    return VALUES_1(temp);
	else {
	    notify_user(1,Tw_process_count_exceeded_goodbye_message);
	    return abort_telewindows_top_level(Qprocess_count_exceeded);
	}
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Telewindows_authorized_products, Qtelewindows_authorized_products);

DEFINE_VARIABLE_WITH_SYMBOL(Telewindows_license_level, Qtelewindows_license_level);

/* TELEWINDOWS-LICENSE-LEVEL */
Object telewindows_license_level(authorized_products)
    Object authorized_products;
{
    Object product, ab_loop_list_, ab_loop_it_, temp;

    x_note_fn_call(106,135);
    product = Nil;
    ab_loop_list_ = authorized_products;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    product = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(product,Qembedded_option))
	ab_loop_it_ = FIX((SI_Long)0L);
    else if (EQ(product,Qruntime_option))
	ab_loop_it_ = FIX((SI_Long)1L);
    else if (EQ(product,Qrestricted_use_option))
	ab_loop_it_ = FIX((SI_Long)2L);
    else
	ab_loop_it_ = Qnil;
    if (ab_loop_it_) {
	temp = ab_loop_it_;
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

/* RECORD-TELEWINDOWS-AUTHORIZED-PRODUCTS */
Object record_telewindows_authorized_products(authorized_products)
    Object authorized_products;
{
    x_note_fn_call(106,136);
    Telewindows_authorized_products = 
	    copy_list_using_gensym_conses_1(authorized_products);
    Telewindows_license_level = telewindows_license_level(authorized_products);
    return VALUES_1(Telewindows_license_level);
}

static Object Qunauthorized;       /* unauthorized */

static Object Qdevelopment;        /* development */

/* TELEWINDOWS-LICENSE-LEVEL-FROM-PRODUCT */
Object telewindows_license_level_from_product(product)
    Object product;
{
    x_note_fn_call(106,137);
    if (EQ(product,Qunauthorized))
	return VALUES_1(FIX((SI_Long)-2L));
    else if (EQ(product,Qfloating))
	return VALUES_1(FIX((SI_Long)-1L));
    else if (EQ(product,Qembedded_option))
	return VALUES_1(FIX((SI_Long)0L));
    else if (EQ(product,Qruntime_option))
	return VALUES_1(FIX((SI_Long)1L));
    else if (EQ(product,Qrestricted_use_option))
	return VALUES_1(FIX((SI_Long)2L));
    else if (EQ(product,Qdevelopment))
	return VALUES_1(FIX((SI_Long)3L));
    else
	return VALUES_1(Qnil);
}

/* GET-TELEWINDOWS-PRODUCT-FROM-LEVEL */
Object get_telewindows_product_from_level(level)
    Object level;
{
    x_note_fn_call(106,138);
    if ( !(FIXNUMP(level) && FIXNUM_LE(FIX((SI_Long)-128L),level) && 
	    FIXNUM_LE(level,FIX((SI_Long)127L))))
	return VALUES_1(Nil);
    else
	switch (INTEGER_TO_CHAR(level)) {
	  case -2:
	    return VALUES_1(Qunauthorized);
	  case -1:
	    return VALUES_1(Qfloating);
	  case 0:
	    return VALUES_1(Qembedded_option);
	  case 1:
	    return VALUES_1(Qruntime_option);
	  case 2:
	    return VALUES_1(Qrestricted_use_option);
	  case 3:
	    return VALUES_1(Qdevelopment);
	  default:
	    return VALUES_1(Nil);
	}
}

/* GET-TELEWINDOWS-PRODUCT-NAME-FROM-LEVEL */
Object get_telewindows_product_name_from_level(level)
    Object level;
{
    x_note_fn_call(106,139);
    if ( !(FIXNUMP(level) && FIXNUM_LE(FIX((SI_Long)-128L),level) && 
	    FIXNUM_LE(level,FIX((SI_Long)127L))))
	return VALUES_1(Nil);
    else
	switch (INTEGER_TO_CHAR(level)) {
	  case -2:
	    return VALUES_1(Qunauthorized);
	  case -1:
	    return VALUES_1(Qfloating);
	  case 0:
	    return VALUES_1(Qembedded);
	  case 1:
	    return VALUES_1(Qruntime);
	  case 2:
	    return VALUES_1(Qrestricted_use);
	  case 3:
	    return VALUES_1(Qdevelopment);
	  default:
	    return VALUES_1(Nil);
	}
}

/* GET-TELEWINDOWS-AUTHORIZATION-STATE */
Object get_telewindows_authorization_state(level)
    Object level;
{
    x_note_fn_call(106,140);
    if ( !(FIXNUMP(level) && FIXNUM_LE(FIX((SI_Long)-128L),level) && 
	    FIXNUM_LE(level,FIX((SI_Long)127L))))
	return VALUES_1(Nil);
    else
	switch (INTEGER_TO_CHAR(level)) {
	  case -2:
	    return VALUES_1(Nil);
	  case -1:
	    return VALUES_1(Qfloating);
	  case 0:
	  case 1:
	    return VALUES_1(Qruntime);
	  case 2:
	  case 3:
	    return VALUES_1(Qdevelopment);
	  default:
	    return VALUES_1(Nil);
	}
}

/* TELEWINDOWS-LICENSED-FOR-PRODUCT-P */
Object telewindows_licensed_for_product_p(product)
    Object product;
{
    Object temp;

    x_note_fn_call(106,141);
    temp = Telewindows_license_level;
    return VALUES_1(FIXNUM_GE(temp,
	    telewindows_license_level_from_product(product)) ? T : Nil);
}

static Object string_constant_20;  /* "~%[Telewindows: will attempt to connect using a Floating Telewindows authorization ...]~%" */

static Object string_constant_21;  /* "[Telewindows: entry for machine ID ~s incorrect.]" */

static Object string_constant_22;  /* "[Telewindows: will attempt to connect using a Floating Telewindows authorization ...]" */

static Object string_constant_23;  /* "~%[Telewindows: ~a~a; will attempt to connect using a Floating Telewindows authorization ...]~%" */

/* CHANGE-LOGIN-BOX-SIZE */
Object change_login_box_size()
{
    Object machine_id, ok_number1, ok_number2, ok_number3, ok_number4;
    Object ok_number5, start_date_qm, expiration_date_qm, authorized_products;
    Object number_of_processes_qm, date, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object day, month, year, date_string, second_arg, second_new_value;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char too_early_qm, too_late_qm;
    Declare_special(5);
    Object result;

    x_note_fn_call(106,142);
    result = warp_login_box_1();
    MVS_10(result,machine_id,ok_number1,ok_number2,ok_number3,ok_number4,
	    ok_number5,start_date_qm,expiration_date_qm,
	    authorized_products,number_of_processes_qm);
    if (memq_function(Qfloating,authorized_products)) {
	if (EQ(Verbosity_level,Qverbose))
	    notify_user(1,string_constant_20);
	return VALUES_1(Nil);
    }
    if ( !TRUEP(ok_number1))
	return VALUES_1(Nil);
    if ( !TRUEP(make_small_workspace(machine_id,ok_number1,ok_number2,
	    ok_number3,ok_number4,ok_number5,start_date_qm,
	    expiration_date_qm,authorized_products,number_of_processes_qm))) {
	if (EQ(Verbosity_level,Qverbose)) {
	    notify_user(2,string_constant_21,machine_id);
	    notify_user(1,string_constant_22);
	}
	force_output(_);
	return VALUES_1(Nil);
    }
    if (start_date_qm) {
	date = get_tw_universal_date();
	too_early_qm = FIXNUM_LT(date,start_date_qm);
	too_late_qm = FIXNUM_GT(date,expiration_date_qm);
	if (too_early_qm || too_late_qm) {
	    if (EQ(Verbosity_level,Qverbose)) {
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
			  result = decode_universal_date(too_late_qm ? 
				  expiration_date_qm : start_date_qm);
			  MVS_3(result,day,month,year);
			  tformat_tw_decoded_date(day,month,year);
			  date_string = copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		notify_user(3,string_constant_23,too_late_qm ? 
			Too_late_telewindows_authorization_message : 
			Too_early_telewindows_authorization_message,
			date_string);
		reclaim_text_string(date_string);
	    }
	    return VALUES_1(Nil);
	}
    }
    second_arg = Telewindows_screen_utilization;
    M_SECOND(second_arg) = T;
    if (IFIX(lengthw(machine_id)) > (SI_Long)5L && 
	    UBYTE_16_ISAREF_1(machine_id,(SI_Long)4L) == (SI_Long)58L && 
	    wide_character_member(FIX(UBYTE_16_ISAREF_1(machine_id,
	    (SI_Long)2L)),list_constant_3) && 
	    wide_character_member(FIX(UBYTE_16_ISAREF_1(machine_id,
	    (SI_Long)1L)),list_constant_4) && 
	    (UBYTE_16_ISAREF_1(machine_id,(SI_Long)3L) == (SI_Long)101L || 
	    UBYTE_16_ISAREF_1(machine_id,(SI_Long)3L) == (SI_Long)69L) && 
	    (UBYTE_16_ISAREF_1(machine_id,(SI_Long)0L) == (SI_Long)83L || 
	    UBYTE_16_ISAREF_1(machine_id,(SI_Long)0L) == (SI_Long)115L))
	c_nsleep(machine_id);
    set_first_string_in_pool_group(machine_id);
    second_arg = Icon_list_notes;
    second_new_value = list(10,machine_id,ok_number1,ok_number2,ok_number3,
	    ok_number4,ok_number5,start_date_qm,expiration_date_qm,
	    sort_scheduled_priorities(authorized_products),
	    number_of_processes_qm);
    M_SECOND(second_arg) = second_new_value;
    record_telewindows_authorized_products(authorized_products);
    return initialize_network_scheduler_interweave_matrix(authorized_products);
}

/* WARP-LOGIN-BOX-1 */
Object warp_login_box_1()
{
    x_note_fn_call(106,143);
    return find_machine_id_in_telewindows_ok_file();
}

/* ENLARGE-TELEWINDOWS-MEMORY */
Object enlarge_telewindows_memory(machine_id,start_date_qm,
	    expiration_date_qm,authorized_products_bitmask,
	    number_of_processes_qm)
    Object machine_id, start_date_qm, expiration_date_qm;
    Object authorized_products_bitmask, number_of_processes_qm;
{
    Object temp, temp_1, temp_2, temp_3;
    SI_Long i;

    x_note_fn_call(106,144);
    shrink_telewindows_memory(machine_id,start_date_qm,expiration_date_qm,
	    authorized_products_bitmask,number_of_processes_qm);
    Random_state_array_current_pointer = FIX((SI_Long)54L);
    Random_state_array_24_pointer = FIX((SI_Long)30L);
    i = (SI_Long)1L;
  next_loop:
    if (i > (SI_Long)500L)
	goto end_loop;
    generate_large_random();
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    temp = aref1(Random_state_array,FIX((SI_Long)0L));
    temp_1 = aref1(Random_state_array,FIX((SI_Long)1L));
    temp_2 = aref1(Random_state_array,FIX((SI_Long)2L));
    temp_3 = aref1(Random_state_array,FIX((SI_Long)3L));
    return VALUES_4(temp,temp_1,temp_2,temp_3);
}

/* SHRINK-TELEWINDOWS-MEMORY */
Object shrink_telewindows_memory(machine_id,start_date_qm,
	    expiration_date_qm,authorized_products_bitmask,
	    number_of_processes_qm)
    Object machine_id, start_date_qm, expiration_date_qm;
    Object authorized_products_bitmask, number_of_processes_qm;
{
    Object aref_arg_1, aref_new_value, state_array_index_1, weight_qm;
    SI_Long state_array_index, i, ab_loop_bind_, gensymed_symbol;
    SI_Long aref_new_value_1;
    char temp;
    XDeclare_area(1);

    x_note_fn_call(106,145);
    if ( !TRUEP(Random_state_array)) {
	if (PUSH_AREA(Dynamic_area,0))
	    Random_state_array = make_array(3,FIX((SI_Long)55L),
		    Kelement_type,Qfixnum);
	POP_AREA(0);
    }
    state_array_index = (SI_Long)0L;
  next_loop:
    if (state_array_index > (SI_Long)54L)
	goto end_loop;
    aref_arg_1 = Random_state_array;
    if ( !(FIXNUMP(Chaining_refresh_version) && 
	    FIXNUM_LE(FIX((SI_Long)-128L),Chaining_refresh_version) && 
	    FIXNUM_LE(Chaining_refresh_version,FIX((SI_Long)127L))))
	aref_new_value = Nil;
    else
	switch (INTEGER_TO_CHAR(Chaining_refresh_version)) {
	  case 3:
	    aref_new_value = FIX((SI_Long)97578L);
	    break;
	  case 4:
	    aref_new_value = FIX((SI_Long)109225L);
	    break;
	  case 5:
	  case 6:
	    aref_new_value = FIX((SI_Long)74890L);
	    break;
	  case 8:
	    aref_new_value = FIX((SI_Long)98312L);
	    break;
	  case 9:
	  case 12:
	    aref_new_value = FIX((SI_Long)57909L);
	    break;
	  case 11:
	    aref_new_value = FIX((SI_Long)19863L);
	    break;
	  default:
	    aref_new_value = Nil;
	    break;
	}
    set_aref1(aref_arg_1,FIX(state_array_index),aref_new_value);
    state_array_index = state_array_index + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    state_array_index_1 = FIX((SI_Long)0L);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(text_string_length(machine_id));
    weight_qm = Nil;
  next_loop_1:
    if (i >= ab_loop_bind_)
	goto end_loop_1;
    weight_qm = digit_char_pw_function(FIX(UBYTE_16_ISAREF_1(machine_id,
	    i)),FIX((SI_Long)36L));
    if (weight_qm) {
	aref_arg_1 = Random_state_array;
	set_aref1(aref_arg_1,state_array_index_1,weight_qm);
	state_array_index_1 = FIXNUM_ADD1(state_array_index_1);
    }
    if (IFIX(state_array_index_1) == (SI_Long)55L)
	goto end_loop_1;
    i = i + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    aref_arg_1 = Random_state_array;
    set_aref1(aref_arg_1,FIX((SI_Long)54L),FIX((SI_Long)1L));
    if (start_date_qm) {
	aref_arg_1 = Random_state_array;
	aref_new_value = FIXNUM_LOGXOR(aref1(Random_state_array,
		FIX((SI_Long)3L)),start_date_qm);
	set_aref1(aref_arg_1,FIX((SI_Long)3L),aref_new_value);
	aref_arg_1 = Random_state_array;
	aref_new_value = FIXNUM_LOGXOR(aref1(Random_state_array,
		FIX((SI_Long)4L)),start_date_qm);
	set_aref1(aref_arg_1,FIX((SI_Long)4L),aref_new_value);
	aref_arg_1 = Random_state_array;
	aref_new_value = FIXNUM_LOGXOR(aref1(Random_state_array,
		FIX((SI_Long)5L)),start_date_qm);
	set_aref1(aref_arg_1,FIX((SI_Long)5L),aref_new_value);
	aref_arg_1 = Random_state_array;
	aref_new_value = FIXNUM_LOGXOR(aref1(Random_state_array,
		FIX((SI_Long)6L)),start_date_qm);
	set_aref1(aref_arg_1,FIX((SI_Long)6L),aref_new_value);
    }
    if (expiration_date_qm) {
	aref_arg_1 = Random_state_array;
	aref_new_value = FIXNUM_LOGXOR(aref1(Random_state_array,
		FIX((SI_Long)7L)),expiration_date_qm);
	set_aref1(aref_arg_1,FIX((SI_Long)7L),aref_new_value);
	aref_arg_1 = Random_state_array;
	aref_new_value = FIXNUM_LOGXOR(aref1(Random_state_array,
		FIX((SI_Long)8L)),expiration_date_qm);
	set_aref1(aref_arg_1,FIX((SI_Long)8L),aref_new_value);
	aref_arg_1 = Random_state_array;
	aref_new_value = FIXNUM_LOGXOR(aref1(Random_state_array,
		FIX((SI_Long)9L)),expiration_date_qm);
	set_aref1(aref_arg_1,FIX((SI_Long)9L),aref_new_value);
	aref_arg_1 = Random_state_array;
	aref_new_value = FIXNUM_LOGXOR(aref1(Random_state_array,
		FIX((SI_Long)10L)),expiration_date_qm);
	set_aref1(aref_arg_1,FIX((SI_Long)10L),aref_new_value);
    }
    if (FIXNUMP(authorized_products_bitmask)) {
	gensymed_symbol = IFIX(authorized_products_bitmask) & (SI_Long)128L;
	temp = gensymed_symbol != (SI_Long)0L;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	aref_arg_1 = Random_state_array;
	aref_new_value_1 = IFIX(aref1(Random_state_array,
		FIX((SI_Long)11L))) ^ (SI_Long)89342L;
	set_aref1(aref_arg_1,FIX((SI_Long)11L),FIX(aref_new_value_1));
	aref_arg_1 = Random_state_array;
	aref_new_value_1 = IFIX(aref1(Random_state_array,
		FIX((SI_Long)12L))) ^ (SI_Long)14783L;
	set_aref1(aref_arg_1,FIX((SI_Long)12L),FIX(aref_new_value_1));
	aref_arg_1 = Random_state_array;
	aref_new_value_1 = IFIX(aref1(Random_state_array,
		FIX((SI_Long)13L))) ^ (SI_Long)28335L;
	set_aref1(aref_arg_1,FIX((SI_Long)13L),FIX(aref_new_value_1));
	aref_arg_1 = Random_state_array;
	aref_new_value_1 = IFIX(aref1(Random_state_array,
		FIX((SI_Long)14L))) ^ (SI_Long)67482L;
	set_aref1(aref_arg_1,FIX((SI_Long)14L),FIX(aref_new_value_1));
    }
    if (FIXNUMP(authorized_products_bitmask) && 
	    (IFIX(authorized_products_bitmask) & (SI_Long)2048L) != 
	    (SI_Long)0L) {
	aref_arg_1 = Random_state_array;
	aref_new_value_1 = IFIX(aref1(Random_state_array,
		FIX((SI_Long)11L))) ^ (SI_Long)29138L;
	set_aref1(aref_arg_1,FIX((SI_Long)11L),FIX(aref_new_value_1));
	aref_arg_1 = Random_state_array;
	aref_new_value_1 = IFIX(aref1(Random_state_array,
		FIX((SI_Long)12L))) ^ (SI_Long)40417L;
	set_aref1(aref_arg_1,FIX((SI_Long)12L),FIX(aref_new_value_1));
	aref_arg_1 = Random_state_array;
	aref_new_value_1 = IFIX(aref1(Random_state_array,
		FIX((SI_Long)13L))) ^ (SI_Long)57969L;
	set_aref1(aref_arg_1,FIX((SI_Long)13L),FIX(aref_new_value_1));
	aref_arg_1 = Random_state_array;
	aref_new_value_1 = IFIX(aref1(Random_state_array,
		FIX((SI_Long)14L))) ^ (SI_Long)15408L;
	set_aref1(aref_arg_1,FIX((SI_Long)14L),FIX(aref_new_value_1));
    }
    if (number_of_processes_qm) {
	aref_arg_1 = Random_state_array;
	aref_new_value_1 = IFIX(aref1(Random_state_array,
		FIX((SI_Long)15L))) ^ IFIX(number_of_processes_qm) * 
		(SI_Long)47L;
	set_aref1(aref_arg_1,FIX((SI_Long)15L),FIX(aref_new_value_1));
	aref_arg_1 = Random_state_array;
	aref_new_value_1 = IFIX(aref1(Random_state_array,
		FIX((SI_Long)16L))) ^ (SI_Long)11963L;
	set_aref1(aref_arg_1,FIX((SI_Long)16L),FIX(aref_new_value_1));
	aref_arg_1 = Random_state_array;
	aref_new_value_1 = IFIX(aref1(Random_state_array,
		FIX((SI_Long)17L))) ^ (SI_Long)67802L;
	set_aref1(aref_arg_1,FIX((SI_Long)17L),FIX(aref_new_value_1));
	aref_arg_1 = Random_state_array;
	aref_new_value_1 = IFIX(aref1(Random_state_array,
		FIX((SI_Long)17L))) ^ (SI_Long)19575L;
	set_aref1(aref_arg_1,FIX((SI_Long)18L),FIX(aref_new_value_1));
    }
    if (FIXNUMP(authorized_products_bitmask) && 
	    (IFIX(authorized_products_bitmask) & (SI_Long)64L) != 
	    (SI_Long)0L || FIXNUMP(authorized_products_bitmask) && 
	    (IFIX(authorized_products_bitmask) & (SI_Long)512L) != 
	    (SI_Long)0L || FIXNUMP(authorized_products_bitmask) && 
	    (IFIX(authorized_products_bitmask) & (SI_Long)1024L) != 
	    (SI_Long)0L) {
	aref_arg_1 = Random_state_array;
	aref_new_value = FIXNUM_LOGXOR(aref1(Random_state_array,
		FIX((SI_Long)19L)),authorized_products_bitmask);
	return set_aref1(aref_arg_1,FIX((SI_Long)19L),aref_new_value);
    }
    else
	return VALUES_1(Nil);
}

/* GET-TW-UNIVERSAL-DATE */
Object get_tw_universal_date()
{
    Object temp, day, month, year;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(106,146);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	result = get_decoded_real_time();
	MVS_6(result,temp,temp,temp,day,month,year);
	result = encode_universal_date(day,month,year);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

static Object string_constant_24;  /* "Jan" */

static Object string_constant_25;  /* "Feb" */

static Object string_constant_26;  /* "Mar" */

static Object string_constant_27;  /* "Apr" */

static Object string_constant_28;  /* "May" */

static Object string_constant_29;  /* "Jun" */

static Object string_constant_30;  /* "Jul" */

static Object string_constant_31;  /* "Aug" */

static Object string_constant_32;  /* "Sep" */

static Object string_constant_33;  /* "Oct" */

static Object string_constant_34;  /* "Nov" */

static Object string_constant_35;  /* "Dec" */

static Object string_constant_36;  /* "~d ~a ~d" */

/* TFORMAT-TW-DECODED-DATE */
Object tformat_tw_decoded_date(day,month,year)
    Object day, month, year;
{
    Object temp;

    x_note_fn_call(106,147);
    if ( !(FIXNUMP(month) && FIXNUM_LE(FIX((SI_Long)-128L),month) && 
	    FIXNUM_LE(month,FIX((SI_Long)127L))))
	temp = Nil;
    else
	switch (INTEGER_TO_CHAR(month)) {
	  case 1:
	    temp = string_constant_24;
	    break;
	  case 2:
	    temp = string_constant_25;
	    break;
	  case 3:
	    temp = string_constant_26;
	    break;
	  case 4:
	    temp = string_constant_27;
	    break;
	  case 5:
	    temp = string_constant_28;
	    break;
	  case 6:
	    temp = string_constant_29;
	    break;
	  case 7:
	    temp = string_constant_30;
	    break;
	  case 8:
	    temp = string_constant_31;
	    break;
	  case 9:
	    temp = string_constant_32;
	    break;
	  case 10:
	    temp = string_constant_33;
	    break;
	  case 11:
	    temp = string_constant_34;
	    break;
	  case 12:
	    temp = string_constant_35;
	    break;
	  default:
	    temp = Nil;
	    break;
	}
    return tformat(4,string_constant_36,day,temp,year);
}

Object Default_text_string_hash_modulus = UNBOUND;

/* GENSYM-SYMBOL-HASH */
Object gensym_symbol_hash(symbol)
    Object symbol;
{
    Object temp;

    x_note_fn_call(106,148);
    temp = gensym_symbol_hash_with_modulus(symbol,
	    Default_text_string_hash_modulus);
    return VALUES_1(temp);
}

/* GENSYM-SYMBOL-HASH-WITH-MODULUS */
Object gensym_symbol_hash_with_modulus(symbol,modulus)
    Object symbol, modulus;
{
    Object temp;

    x_note_fn_call(106,149);
    temp = text_string_hash_with_modulus(symbol_name_text_string(symbol),
	    modulus);
    return VALUES_1(temp);
}

/* TEXT-STRING-HASH */
Object text_string_hash(text_string)
    Object text_string;
{
    Object temp;

    x_note_fn_call(106,150);
    temp = text_string_hash_with_modulus(text_string,
	    Default_text_string_hash_modulus);
    return VALUES_1(temp);
}

/* TEXT-STRING-HASH-WITH-MODULUS */
Object text_string_hash_with_modulus(text_string,modulus)
    Object text_string, modulus;
{
    Object length_1, accumulator, packer, packing_index, char_1;
    Object gensymed_symbol, temp_1;
    SI_Long name_index, temp, gensymed_symbol_1;

    x_note_fn_call(106,151);
    length_1 = lengthw(text_string);
    accumulator = FIX((SI_Long)0L);
    packer = FIX((SI_Long)0L);
    packing_index = FIX((SI_Long)0L);
    name_index = (SI_Long)0L;
    char_1 = Nil;
  next_loop:
    if (name_index == IFIX(length_1))
	goto end_loop;
    char_1 = FIX(UBYTE_16_ISAREF_1(text_string,name_index));
    gensymed_symbol = char_1;
    if ((SI_Long)97L <= IFIX(gensymed_symbol) && IFIX(gensymed_symbol) <= 
	    (SI_Long)122L || (SI_Long)65L <= IFIX(gensymed_symbol) && 
	    IFIX(gensymed_symbol) <= (SI_Long)90L || (SI_Long)48L <= 
	    IFIX(gensymed_symbol) && IFIX(gensymed_symbol) <= (SI_Long)57L) {
	temp = IFIX(packer) << (SI_Long)6L;
	packer = FIX(temp + IFIX(digit_char_pw_function(char_1,
		FIX((SI_Long)36L))));
	packing_index = FIXNUM_ADD1(packing_index);
	if ((SI_Long)0L == (IFIX(packing_index) & (SI_Long)3L)) {
	    temp = IFIX(accumulator) % IFIX(modulus);
	    temp = IFIX(FIXNUM_ADD(FIX(temp),packer)) % IFIX(modulus);
	    accumulator = FIX(temp);
	    packer = FIX((SI_Long)0L);
	}
    }
    name_index = name_index + (SI_Long)1L;
    goto next_loop;
  end_loop:
    if (IFIX(packer) > (SI_Long)0L) {
	gensymed_symbol = packer;
	gensymed_symbol_1 = (SI_Long)6L * ((SI_Long)4L - 
		(IFIX(packing_index) & (SI_Long)3L));
	packer = ash(gensymed_symbol,FIX(gensymed_symbol_1));
	temp = IFIX(packer) % IFIX(modulus);
	temp = IFIX(FIXNUM_ADD(FIX(temp),accumulator)) % IFIX(modulus);
	accumulator = FIX(temp);
    }
    temp_1 = accumulator;
    goto end_1;
    temp_1 = Qnil;
  end_1:;
    return VALUES_1(temp_1);
}

/* ENCODE-USER-PASSWORD-STRING-FUNCTION */
Object encode_user_password_string_function(string_1)
    Object string_1;
{
    Object string_value, x1, x2, x3, x4, temp;
    SI_Long y1_1, y4;

    x_note_fn_call(106,152);
    string_value = string_1;
    x1 = text_string_hash_with_modulus(string_value,FIX((SI_Long)4051L));
    x2 = text_string_hash_with_modulus(string_value,FIX((SI_Long)4003L));
    x3 = text_string_hash_with_modulus(string_value,FIX((SI_Long)3943L));
    x4 = text_string_hash_with_modulus(string_value,FIX((SI_Long)3889L));
    y1_1 = IFIX(x1) >>  -  - (SI_Long)6L | (IFIX(x4) & (SI_Long)63L) << 
	    (SI_Long)6L;
    y4 = IFIX(x4) >>  -  - (SI_Long)6L | (IFIX(x1) & (SI_Long)63L) << 
	    (SI_Long)6L;
    temp = FIX((y1_1 * y4 ^ IFIX(FIXNUM_TIMES(x2,x3))) + (SI_Long)1L);
    return VALUES_1(temp);
}

static Object array_constant_60;   /* # */

static Object array_constant_61;   /* # */

/* ENCODE-PASSWORD-VIA-MD5 */
Object encode_password_via_md5(user_name_qm,password_qm,default_result_qm)
    Object user_name_qm, password_qm, default_result_qm;
{
    Object str, string_1, temp;

    x_note_fn_call(106,153);
    if (user_name_qm && password_qm) {
	g2ext_init_g2_MD5_context((SI_Long)0L);
	update_indexed_md5_context(FIX((SI_Long)0L),array_constant_60);
	str = string_downcasew(SYMBOLP(user_name_qm) ? 
		symbol_name_text_string(user_name_qm) : user_name_qm);
	update_indexed_md5_context(FIX((SI_Long)0L),str);
	reclaim_text_string(str);
	update_indexed_md5_context(FIX((SI_Long)0L),array_constant_61);
	str = string_downcasew(SYMBOLP(password_qm) ? 
		symbol_name_text_string(password_qm) : password_qm);
	update_indexed_md5_context(FIX((SI_Long)0L),str);
	reclaim_text_string(str);
	string_1 = obtain_simple_gensym_string(FIX((SI_Long)16L));
	finalize_indexed_md5_context(FIX((SI_Long)0L),string_1);
	temp = convert_md5_result_string_to_hex_string(string_1,
		FIX((SI_Long)16L));
	reclaim_simple_gensym_string(string_1);
    }
    else
	temp = default_result_qm;
    return VALUES_1(temp);
}

static Object string_constant_37;  /* "0~x" */

static Object string_constant_38;  /* "~x" */

/* CONVERT-MD5-RESULT-STRING-TO-HEX-STRING */
Object convert_md5_result_string_to_hex_string(simple_gensym_string,length_1)
    Object simple_gensym_string, length_1;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object result_string, value, temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_2, i;
    SI_Long ab_loop_bind_;
    Declare_special(5);

    x_note_fn_call(106,154);
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
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_2 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    0);
	      result_string = simple_gensym_string;
	      i = (SI_Long)0L;
	      ab_loop_bind_ = IFIX(length_1);
	      value = Nil;
	    next_loop:
	      if (i >= ab_loop_bind_)
		  goto end_loop;
	      value = CHAR_CODE(CHR(ISCHAR(result_string,i)));
	      if (IFIX(value) < (SI_Long)16L)
		  tformat(2,string_constant_37,value);
	      else
		  tformat(2,string_constant_38,value);
	      i = i + (SI_Long)1L;
	      goto next_loop;
	    end_loop:;
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    temp = nstring_downcasew(temp);
    return VALUES_1(temp);
}

/* CONVERT-UUID-STRING-TO-HEX-STRING */
Object convert_uuid_string_to_hex_string(wide_string,length_1)
    Object wide_string, length_1;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object result_string, value, temp, new_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_2, i;
    SI_Long ab_loop_bind_;
    Declare_special(5);

    x_note_fn_call(106,155);
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
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_2 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    0);
	      result_string = wide_string;
	      i = (SI_Long)0L;
	      ab_loop_bind_ = IFIX(length_1);
	      value = Nil;
	    next_loop:
	      if (i >= ab_loop_bind_)
		  goto end_loop;
	      value = FIX(UBYTE_16_ISAREF_1(result_string,i));
	      tformat(2,string_constant_38,value);
	      i = i + (SI_Long)1L;
	      goto next_loop;
	    end_loop:;
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    new_string = nstring_downcasew(temp);
    reclaim_wide_string(wide_string);
    return VALUES_1(new_string);
}

void sequences1_INIT()
{
    Object temp;
    Object list_constant_8, Qdefault_text_string_hash_modulus, AB_package;
    Object Qsequences1, string_constant_91, string_constant_90;
    Object array_constant_88, Qtoo_early_telewindows_authorization_message;
    Object string_constant_89, string_constant_88, array_constant_87;
    Object Qtoo_late_telewindows_authorization_message, list_constant_77;
    Object Qtelewindows, Qfixnum_time_interval, Kfuncall, list_constant_76;
    Object Qget_fixnum_time_function, Qtelestubs, list_constant_75;
    Object Qmap_month_to_number_code, list_constant_74, list_constant_73;
    Object list_constant_72, list_constant_71, list_constant_70;
    Object list_constant_69, list_constant_68, list_constant_67;
    Object list_constant_66, list_constant_65, list_constant_64;
    Object list_constant_63, list_constant_61, Qdec, list_constant_62, Qnov;
    Object Qoct, Qsep, Qaug, Qjul, Qjun, Qmay, Qapr, Qmar, Qfeb, Qjan;
    Object list_constant_60, G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object list_constant_59, list_constant_58, list_constant_57;
    Object list_constant_56, list_constant_55, list_constant_54;
    Object list_constant_53, list_constant_52, Qchinese, string_constant_87;
    Object array_constant_86, Qcannot_open_telewindows_ok_file_message;
    Object string_constant_86, string_constant_85, array_constant_85;
    Object Qno_valid_telewindows_ok_entry_message, Qicp, Qgfi, Qgsi;
    Object list_constant_51, Qpathnames;
    Object Qinitializer_for_pathname_for_disabling_g2v12_ok_command_line;
    Object list_constant_50, Qinitialize_default_g2v12_ok_pathname;
    Object list_constant_49;
    Object Qinitializer_for_pathname_for_disabling_g2v11_ok_command_line;
    Object list_constant_48, Qinitialize_default_g2v11_ok_pathname;
    Object list_constant_47;
    Object Qinitializer_for_pathname_for_disabling_g2v9_ok_command_line;
    Object list_constant_46, Qinitialize_default_g2v9_ok_pathname;
    Object list_constant_45;
    Object Qinitializer_for_pathname_for_disabling_g2v83_ok_command_line;
    Object list_constant_44, Qinitialize_default_g2v83_ok_pathname;
    Object list_constant_43;
    Object Qinitializer_for_pathname_for_disabling_g2v8_ok_command_line;
    Object list_constant_42, Qinitialize_default_g2v8_ok_pathname;
    Object list_constant_41;
    Object Qinitializer_for_pathname_for_disabling_g2v7_ok_command_line;
    Object list_constant_40, Qinitialize_default_g2v7_ok_pathname;
    Object list_constant_39;
    Object Qinitializer_for_pathname_for_disabling_g2v6_ok_command_line;
    Object list_constant_38, Qinitialize_default_g2v6_ok_pathname;
    Object list_constant_37;
    Object Qinitializer_for_pathname_for_disabling_g2v51_ok_command_line;
    Object list_constant_36, Qinitialize_default_g2v51_ok_pathname;
    Object list_constant_35;
    Object Qinitializer_for_pathname_for_disabling_g2v5_ok_command_line;
    Object list_constant_34, Qinitialize_default_g2v5_ok_pathname;
    Object list_constant_33;
    Object Qinitializer_for_pathname_for_disabling_g2_ok_command_line;
    Object list_constant_32, Qinitialize_default_g2_ok_pathname;
    Object list_constant_31;
    Object Qinitializer_for_pathname_for_disabling_twv12_ok_command_line;
    Object list_constant_30, Qinitialize_default_twv12_ok_pathname;
    Object list_constant_29;
    Object Qinitializer_for_pathname_for_disabling_twv11_ok_command_line;
    Object list_constant_28, Qinitialize_default_twv11_ok_pathname;
    Object list_constant_27;
    Object Qinitializer_for_pathname_for_disabling_twv9_ok_command_line;
    Object list_constant_26, Qinitialize_default_twv9_ok_pathname;
    Object list_constant_25;
    Object Qinitializer_for_pathname_for_disabling_twv8_ok_command_line;
    Object list_constant_24, Qinitialize_default_twv8_ok_pathname;
    Object list_constant_23;
    Object Qinitializer_for_pathname_for_disabling_twv7_ok_command_line;
    Object list_constant_22, Qinitialize_default_twv7_ok_pathname;
    Object list_constant_21;
    Object Qinitializer_for_pathname_for_disabling_twv6_ok_command_line;
    Object list_constant_20, Qinitialize_default_twv6_ok_pathname;
    Object list_constant_19;
    Object Qinitializer_for_pathname_for_disabling_twv5_ok_command_line;
    Object list_constant_18, Qinitialize_default_twv5_ok_pathname;
    Object list_constant_17;
    Object Qinitializer_for_pathname_for_disabling_tw_ok_command_line;
    Object Kabsolute, list_constant_16, Qinitialize_default_tw_ok_pathname;
    Object list_constant_15, array_constant_84, array_constant_83;
    Object array_constant_82, array_constant_81, array_constant_80;
    Object array_constant_79, array_constant_78, array_constant_77;
    Object array_constant_76, Qsize_of_local_machine_id, list_constant_14;
    Object Qchoose_chaining_refresh_list, string_constant_84;
    Object string_constant_83, string_constant_82, string_constant_81;
    Object string_constant_80, array_constant_75;
    Object Qembedded_g2_with_windows_goodbye_message;
    Object Qinitialize_consistency_tree_focus_shifts, list_constant_13;
    Object Qinitialize_master_hierarchy_reconciliation_switches;
    Object list_constant_12, string_constant_79, string_constant_78;
    Object string_constant_77, string_constant_76, string_constant_75;
    Object string_constant_74, string_constant_73, string_constant_72;
    Object array_constant_74, Qtw_system_time_too_early_goodbye_message;
    Object string_constant_71, string_constant_70, string_constant_69;
    Object string_constant_68, string_constant_67, string_constant_66;
    Object string_constant_65, string_constant_64, array_constant_73;
    Object Qg2_system_time_too_early_goodbye_message;
    Object Qinitialize_minimal_fragmentation_seeds, list_constant_11;
    Object Qevaluator_tradeoff_info, Qlimit_bignum_inner_loop_cache_p;
    Object string_constant_63, string_constant_62, string_constant_61;
    Object string_constant_60, array_constant_72;
    Object Qrefuse_save_after_system_clock_tampering_message;
    Object string_constant_59, string_constant_58, string_constant_57;
    Object array_constant_71;
    Object Qrefuse_load_at_discrepancy_with_system_clock_message, Qcycles;
    Object Qcounter_for_sleep_management_adjustment, Qdrawing_task_tuning_info;
    Object Qcurrent_inner_procedure_loop_cache_index;
    Object Qengage_context_pipelining_p;
    Object Qinitialize_embedded_fuzzy_conditionals_list, list_constant_10;
    Object list_constant_9, Qclass_instance_delta_masks;
    Object Qinitialize_class_instance_delta_masks, string_constant_56;
    Object Qtimestamp_cons_memory_usage, Qoutstanding_timestamp_conses;
    Object list_constant_7, Qtimestamp_cons_counter_vector, list_constant_6;
    Object Qavailable_timestamp_conses_tail_vector;
    Object Qavailable_timestamp_conses_vector, string_constant_55;
    Object string_constant_54, string_constant_53, array_constant_70;
    Object Qtw_cannot_register_process_license_goodbye_message;
    Object string_constant_52, string_constant_51, string_constant_50;
    Object string_constant_49, array_constant_69;
    Object Qtw_process_count_exceeded_goodbye_message, string_constant_48;
    Object string_constant_47, string_constant_46, array_constant_68;
    Object Qg2_process_count_exceeded_goodbye_message;
    Object Qunlimited_backtracking_in_internal_truth_maintenance_p;
    Object string_constant_45, array_constant_67, Qtw_development_option;
    Object string_constant_43, array_constant_65, Qtw_embedded_option;
    Object string_constant_42, array_constant_64, Qtw_restricted_use_option;
    Object string_constant_41, array_constant_63, Qtw_runtime_option;
    Object Qtw_product, string_constant_44, array_constant_66;
    Object Qg2_development_option, Qg2_embedded_option;
    Object Qg2_restricted_use_option, Qg2_runtime_option, string_constant_40;
    Object array_constant_62, Qg2_product, string_constant_39;
    Object Qsequence_cons_memory_usage, Qoutstanding_sequence_conses;
    Object Qsequence_cons_counter_vector, Qmake_thread_array;
    Object Qavailable_sequence_conses_tail_vector;
    Object Qavailable_sequence_conses_vector, Qinitialize_verbosity_level;
    Object list_constant_5;

    x_note_fn_call(106,156);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qverbosity_level = STATIC_SYMBOL("VERBOSITY-LEVEL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qverbosity_level,Verbosity_level);
    Qsequences1 = STATIC_SYMBOL("SEQUENCES1",AB_package);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qinitialize_verbosity_level = 
	    STATIC_SYMBOL("INITIALIZE-VERBOSITY-LEVEL",AB_package);
    list_constant_5 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_verbosity_level);
    record_system_variable(Qverbosity_level,Qsequences1,list_constant_5,
	    Qnil,Qnil,Qnil,Qnil);
    Qverbose = STATIC_SYMBOL("VERBOSE",AB_package);
    Qsilent = STATIC_SYMBOL("SILENT",AB_package);
    Qnormal = STATIC_SYMBOL("NORMAL",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_verbosity_level,
	    STATIC_FUNCTION(initialize_verbosity_level,NIL,FALSE,0,0));
    Qavailable_sequence_conses = STATIC_SYMBOL("AVAILABLE-SEQUENCE-CONSES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_sequence_conses,
	    Available_sequence_conses);
    record_system_variable(Qavailable_sequence_conses,Qsequences1,Nil,Qnil,
	    Qt,Qnil,Qnil);
    Qavailable_sequence_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-SEQUENCE-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_sequence_conses_tail,
	    Available_sequence_conses_tail);
    record_system_variable(Qavailable_sequence_conses_tail,Qsequences1,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_sequence_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-SEQUENCE-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_sequence_conses_vector,
	    Available_sequence_conses_vector);
    Qmake_thread_array = STATIC_SYMBOL("MAKE-THREAD-ARRAY",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    Qnil);
    record_system_variable(Qavailable_sequence_conses_vector,Qsequences1,
	    list_constant_6,Qnil,Qt,Qnil,Qnil);
    Qavailable_sequence_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-SEQUENCE-CONSES-TAIL-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_sequence_conses_tail_vector,
	    Available_sequence_conses_tail_vector);
    record_system_variable(Qavailable_sequence_conses_tail_vector,
	    Qsequences1,list_constant_6,Qnil,Qt,Qnil,Qnil);
    Qsequence_cons_counter_vector = 
	    STATIC_SYMBOL("SEQUENCE-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsequence_cons_counter_vector,
	    Sequence_cons_counter_vector);
    list_constant_7 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    FIX((SI_Long)0L));
    record_system_variable(Qsequence_cons_counter_vector,Qsequences1,
	    list_constant_7,Qnil,Qt,Qnil,Qnil);
    Qsequence_cons_counter = STATIC_SYMBOL("SEQUENCE-CONS-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsequence_cons_counter,Sequence_cons_counter);
    record_system_variable(Qsequence_cons_counter,Qsequences1,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_sequence_conses = 
	    STATIC_SYMBOL("OUTSTANDING-SEQUENCE-CONSES",AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_sequence_conses,
	    STATIC_FUNCTION(outstanding_sequence_conses,NIL,FALSE,0,0));
    Qsequence_cons_memory_usage = 
	    STATIC_SYMBOL("SEQUENCE-CONS-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qsequence_cons_memory_usage,
	    STATIC_FUNCTION(sequence_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_39 = STATIC_STRING("1q83-oMy9k83-oLy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_sequence_conses);
    push_optimized_constant(Qsequence_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_39));
    Qg2_product = STATIC_SYMBOL("G2-PRODUCT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2_product,G2_product);
    list_constant_8 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant_62 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)0L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)2L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)3L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)4L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)5L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)7L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)9L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)12L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)13L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)14L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_62,(SI_Long)23L,(SI_Long)57344L);
    string_constant_40 = STATIC_STRING("4z4k4ll4k4k4lk4k4k4k4k4k4k4k4k4k4k");
    SET_SYMBOL_VALUE(Qg2_product,
	    transform_type_specification_2(FIX((SI_Long)2L),
	    array_constant_62,
	    regenerate_optimized_constant(string_constant_40)));
    Qg2_runtime_option = STATIC_SYMBOL("G2-RUNTIME-OPTION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2_runtime_option,G2_runtime_option);
    array_constant_63 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)0L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)1L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)2L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)3L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)4L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)5L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)6L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)7L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)8L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)9L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)10L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)11L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)12L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)14L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)17L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)18L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)19L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)22L,(SI_Long)20L);
    UBYTE_16_ISASET_1(array_constant_63,(SI_Long)23L,(SI_Long)57344L);
    string_constant_41 = 
	    STATIC_STRING("43Gy4k4k4k4k4lq4lo4lp4lm4lk4ll4ln4k4k4k4k4k4k4k4k4k");
    SET_SYMBOL_VALUE(Qg2_runtime_option,
	    transform_type_specification_2(FIX((SI_Long)7L),
	    array_constant_63,
	    regenerate_optimized_constant(string_constant_41)));
    Qg2_restricted_use_option = STATIC_SYMBOL("G2-RESTRICTED-USE-OPTION",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2_restricted_use_option,
	    G2_restricted_use_option);
    array_constant_64 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)1L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)2L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)3L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)4L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)5L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)6L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)7L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)8L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)9L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)10L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)11L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)12L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)13L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)14L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)16L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)17L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)18L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)19L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)20L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)21L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)30L,(SI_Long)22L);
    UBYTE_16_ISASET_1(array_constant_64,(SI_Long)31L,(SI_Long)57344L);
    string_constant_42 = 
	    STATIC_STRING("43Iy4lu4k4k4k4lq4k4lt4nlsx4lp4mko4mmw4mnr4lv4k4k4k4k4k4k4k4k4k");
    SET_SYMBOL_VALUE(Qg2_restricted_use_option,
	    transform_type_specification_2(FIX((SI_Long)14L),
	    array_constant_64,
	    regenerate_optimized_constant(string_constant_42)));
    Qg2_embedded_option = STATIC_SYMBOL("G2-EMBEDDED-OPTION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2_embedded_option,G2_embedded_option);
    array_constant_65 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)0L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)1L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)2L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)3L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)4L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)5L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)6L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)7L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)9L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)11L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)12L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)14L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)15L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)16L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)22L,(SI_Long)17L);
    UBYTE_16_ISASET_1(array_constant_65,(SI_Long)23L,(SI_Long)57344L);
    string_constant_43 = 
	    STATIC_STRING("43Dy4k4k4k4k4nopr4nknq4lm4ll4k4k4k4k4k4k4k4k4k");
    SET_SYMBOL_VALUE(Qg2_embedded_option,
	    transform_type_specification_2(FIX((SI_Long)8L),
	    array_constant_65,
	    regenerate_optimized_constant(string_constant_43)));
    Qg2_development_option = STATIC_SYMBOL("G2-DEVELOPMENT-OPTION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2_development_option,G2_development_option);
    array_constant_66 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)0L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)1L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)2L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)3L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)4L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)5L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)6L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)7L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)8L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)9L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)10L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)11L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)12L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)13L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)14L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)16L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)17L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)18L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)19L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)20L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)21L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)30L,(SI_Long)22L);
    UBYTE_16_ISASET_1(array_constant_66,(SI_Long)31L,(SI_Long)57344L);
    string_constant_44 = 
	    STATIC_STRING("43Iy4k4nlns4lm4lo4lp4lq4lr4lt4lu4lk4k4k4k4k4k4k4k4k4k4k4k4k");
    SET_SYMBOL_VALUE(Qg2_development_option,
	    transform_type_specification_2(FIX((SI_Long)11L),
	    array_constant_66,
	    regenerate_optimized_constant(string_constant_44)));
    Qtw_product = STATIC_SYMBOL("TW-PRODUCT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtw_product,Tw_product);
    array_constant_67 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)0L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)1L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)2L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)3L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)4L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)5L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)7L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)9L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)12L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)13L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)14L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_67,(SI_Long)23L,(SI_Long)57344L);
    string_constant_45 = STATIC_STRING("4z4k4k4k4lk4ll4k4k4k4k4k4k4k4k4k4k");
    SET_SYMBOL_VALUE(Qtw_product,
	    transform_type_specification_2(FIX((SI_Long)2L),
	    array_constant_67,
	    regenerate_optimized_constant(string_constant_45)));
    Qtw_runtime_option = STATIC_SYMBOL("TW-RUNTIME-OPTION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtw_runtime_option,Tw_runtime_option);
    SET_SYMBOL_VALUE(Qtw_runtime_option,
	    transform_type_specification_2(FIX((SI_Long)7L),
	    array_constant_63,
	    regenerate_optimized_constant(string_constant_41)));
    Qtw_restricted_use_option = STATIC_SYMBOL("TW-RESTRICTED-USE-OPTION",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtw_restricted_use_option,
	    Tw_restricted_use_option);
    SET_SYMBOL_VALUE(Qtw_restricted_use_option,
	    transform_type_specification_2(FIX((SI_Long)14L),
	    array_constant_64,
	    regenerate_optimized_constant(string_constant_42)));
    Qtw_embedded_option = STATIC_SYMBOL("TW-EMBEDDED-OPTION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtw_embedded_option,Tw_embedded_option);
    SET_SYMBOL_VALUE(Qtw_embedded_option,
	    transform_type_specification_2(FIX((SI_Long)8L),
	    array_constant_65,
	    regenerate_optimized_constant(string_constant_43)));
    Qtw_development_option = STATIC_SYMBOL("TW-DEVELOPMENT-OPTION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtw_development_option,Tw_development_option);
    SET_SYMBOL_VALUE(Qtw_development_option,
	    transform_type_specification_2(FIX((SI_Long)2L),
	    array_constant_67,
	    regenerate_optimized_constant(string_constant_45)));
    Qunlimited_backtracking_in_internal_truth_maintenance_p = 
	    STATIC_SYMBOL("UNLIMITED-BACKTRACKING-IN-INTERNAL-TRUTH-MAINTENANCE-P",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qunlimited_backtracking_in_internal_truth_maintenance_p,
	    Unlimited_backtracking_in_internal_truth_maintenance_p);
    record_system_variable(Qunlimited_backtracking_in_internal_truth_maintenance_p,
	    Qsequences1,Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2_process_count_exceeded_goodbye_message = 
	    STATIC_SYMBOL("G2-PROCESS-COUNT-EXCEEDED-GOODBYE-MESSAGE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2_process_count_exceeded_goodbye_message,
	    G2_process_count_exceeded_goodbye_message);
    array_constant_68 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)0L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)2L,(SI_Long)37L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)3L,(SI_Long)38L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)4L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)5L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)6L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)7L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)8L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)9L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)10L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)11L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)12L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)13L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)14L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)15L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)16L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)17L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)19L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)20L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)21L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)22L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)23L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)24L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)25L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)26L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)27L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)28L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)29L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)30L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)31L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)32L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)33L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)34L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)35L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)36L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)37L,(SI_Long)126L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)46L,(SI_Long)38L);
    UBYTE_16_ISASET_1(array_constant_68,(SI_Long)47L,(SI_Long)57344L);
    string_constant_46 = 
	    STATIC_STRING("43Yy4l3-1y43Gyv3Cy3Fy3Ly3Sy3Wy3fy3my3py3-2y3-3y3-4y3-5y3-6y3-7y3-8y3-9y3-Ay3-Hy3-My4m3-=y3-Ty4ll4l3-Gy4m3--y3-Ry4k4l3Ey4k4k4k4l3");
    string_constant_47 = 
	    STATIC_STRING("Dy4lm4l3-By4ln4oq3Oy3Zy3ty4l3jy4n3Ky3Ry3ey4u3My3Py3Qy3Vy3ay3dy3ky3uy3xy3-Ny4l3oy4lu4nrx3Uy4osy3Yy3-Py4m3Jy3Xy4m3iy3-Iy4opt3by3gy");
    string_constant_48 = 
	    STATIC_STRING("4o3Hy3ny3sy3-Cy4l3qy4o3ly3ry3-Dy3-Ey4qz3cy3vy3wy3-+y3-Ky4ow3Ty3-Ly3-Qy4oo3Iy3hy3-Jy4k4l3Gy4m3Ny3-Oy4l3-Fy4k4ok3-*y3-0y3-Sy");
    SET_SYMBOL_VALUE(Qg2_process_count_exceeded_goodbye_message,
	    transform_type_specification_2(FIX((SI_Long)98L),
	    array_constant_68,
	    regenerate_optimized_constant(LIST_3(string_constant_46,
	    string_constant_47,string_constant_48))));
    Qtw_process_count_exceeded_goodbye_message = 
	    STATIC_SYMBOL("TW-PROCESS-COUNT-EXCEEDED-GOODBYE-MESSAGE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtw_process_count_exceeded_goodbye_message,
	    Tw_process_count_exceeded_goodbye_message);
    array_constant_69 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)0L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)2L,(SI_Long)37L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)3L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)4L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)5L,(SI_Long)38L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)6L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)7L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)8L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)9L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)10L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)11L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)12L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)13L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)14L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)15L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)16L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)18L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)19L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)20L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)21L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)22L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)23L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)24L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)25L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)26L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)27L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)28L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)29L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)30L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)31L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)32L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)33L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)34L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)35L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)36L,(SI_Long)126L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)38L,(SI_Long)37L);
    UBYTE_16_ISASET_1(array_constant_69,(SI_Long)39L,(SI_Long)57344L);
    string_constant_49 = 
	    STATIC_STRING("43Xy4l3-*y43Gyv3Cy3Oy3Uy3by3fy3oy3vy3-+y3-=y3-0y3-1y3-2y3-3y3-4y3-5y3-6y3-7y3-Qy3-Vy4m3-Jy3-cy4m3-Hy3-ay4l3-Py4ll4k4k4k4lm4k4l3-");
    string_constant_50 = 
	    STATIC_STRING("Ky4l3Dy4ln4oq3Xy3iy3-By4l3sy4o3Ky3Ty3ay3ny4w3Ey3Gy3Vy3Yy3Zy3ey3jy3my3ty3-Cy3-Fy3-Wy4l3xy4lu4nrx3dy4psy3Iy3hy3-Yy4n3Fy3Sy3gy4m3ry");
    string_constant_51 = 
	    STATIC_STRING("3-Ry4ppt3Jy3ky3py4p3Ly3Qy3wy3-Ay3-Ly4l3-8y4o3uy3-9y3-My3-Ny4rz3Ny3ly3-Dy3-Ey3-Gy3-Ty4ow3cy3-Uy3-Zy4oo3Ry3qy3-Sy4k4n3Hy3My3Py4m3W");
    string_constant_52 = STATIC_STRING("y3-Xy4l3-Oy4k4ok3--y3-Iy3-by");
    SET_SYMBOL_VALUE(Qtw_process_count_exceeded_goodbye_message,
	    transform_type_specification_2(FIX((SI_Long)107L),
	    array_constant_69,
	    regenerate_optimized_constant(LIST_4(string_constant_49,
	    string_constant_50,string_constant_51,string_constant_52))));
    Qtw_cannot_register_process_license_goodbye_message = 
	    STATIC_SYMBOL("TW-CANNOT-REGISTER-PROCESS-LICENSE-GOODBYE-MESSAGE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtw_cannot_register_process_license_goodbye_message,
	    Tw_cannot_register_process_license_goodbye_message);
    array_constant_70 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)0L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)2L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)3L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)4L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)5L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)6L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)7L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)8L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)9L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)10L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)11L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)13L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)14L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)16L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)17L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)18L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)19L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)20L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)21L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)22L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)23L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)24L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)25L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)26L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)27L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)28L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)29L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)30L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)31L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)32L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)33L,(SI_Long)126L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)34L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)38L,(SI_Long)35L);
    UBYTE_16_ISASET_1(array_constant_70,(SI_Long)39L,(SI_Long)57344L);
    string_constant_53 = 
	    STATIC_STRING("43Vy4l3jy4wr3Fy3Ny3Vy3Yy3hy3ky3ly3my3ty3wy3-1y4l3sy4m3gy3-Ay4k4k4k4lk4k4l3ny4l3uy4l3vy4l3-+y4ln4o3Jy3Qy3xy3-2y4spty3Ky3Ry3Uy3ay3");
    string_constant_54 = 
	    STATIC_STRING("-9y4mu3Ey4k4ov3Cy3Py3-6y4l3fy4mo3Oy4lq4s3Dy3Sy3Xy3Zy3--y3-*y3-4y3-7y4rm3Iy3Wy3dy3oy3-=y3-3y4l3Gy4rlsz3Hy3ey3py3qy4ow3Ly3My3Ty4ox");
    string_constant_55 = 
	    STATIC_STRING("3by3-0y3-5y4l3-8y4k4l3cy4k4l3ry4l3iy4k");
    SET_SYMBOL_VALUE(Qtw_cannot_register_process_license_goodbye_message,
	    transform_type_specification_2(FIX((SI_Long)79L),
	    array_constant_70,
	    regenerate_optimized_constant(LIST_3(string_constant_53,
	    string_constant_54,string_constant_55))));
    Qavailable_timestamp_conses = 
	    STATIC_SYMBOL("AVAILABLE-TIMESTAMP-CONSES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_timestamp_conses,
	    Available_timestamp_conses);
    record_system_variable(Qavailable_timestamp_conses,Qsequences1,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_timestamp_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-TIMESTAMP-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_timestamp_conses_tail,
	    Available_timestamp_conses_tail);
    record_system_variable(Qavailable_timestamp_conses_tail,Qsequences1,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qavailable_timestamp_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-TIMESTAMP-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_timestamp_conses_vector,
	    Available_timestamp_conses_vector);
    record_system_variable(Qavailable_timestamp_conses_vector,Qsequences1,
	    list_constant_6,Qnil,Qt,Qnil,Qnil);
    Qavailable_timestamp_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-TIMESTAMP-CONSES-TAIL-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_timestamp_conses_tail_vector,
	    Available_timestamp_conses_tail_vector);
    record_system_variable(Qavailable_timestamp_conses_tail_vector,
	    Qsequences1,list_constant_6,Qnil,Qt,Qnil,Qnil);
    Qtimestamp_cons_counter_vector = 
	    STATIC_SYMBOL("TIMESTAMP-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtimestamp_cons_counter_vector,
	    Timestamp_cons_counter_vector);
    record_system_variable(Qtimestamp_cons_counter_vector,Qsequences1,
	    list_constant_7,Qnil,Qt,Qnil,Qnil);
    Qtimestamp_cons_counter = STATIC_SYMBOL("TIMESTAMP-CONS-COUNTER",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtimestamp_cons_counter,Timestamp_cons_counter);
    record_system_variable(Qtimestamp_cons_counter,Qsequences1,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_timestamp_conses = 
	    STATIC_SYMBOL("OUTSTANDING-TIMESTAMP-CONSES",AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_timestamp_conses,
	    STATIC_FUNCTION(outstanding_timestamp_conses,NIL,FALSE,0,0));
    Qtimestamp_cons_memory_usage = 
	    STATIC_SYMBOL("TIMESTAMP-CONS-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qtimestamp_cons_memory_usage,
	    STATIC_FUNCTION(timestamp_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_56 = STATIC_STRING("1q83-tLy9k83-tKy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_timestamp_conses);
    push_optimized_constant(Qtimestamp_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_56));
    Qtimestamp = STATIC_SYMBOL("TIMESTAMP",AB_package);
    Qclass_instance_delta_masks = 
	    STATIC_SYMBOL("CLASS-INSTANCE-DELTA-MASKS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qclass_instance_delta_masks,
	    Class_instance_delta_masks);
    Qinitialize_class_instance_delta_masks = 
	    STATIC_SYMBOL("INITIALIZE-CLASS-INSTANCE-DELTA-MASKS",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_class_instance_delta_masks,
	    STATIC_FUNCTION(initialize_class_instance_delta_masks,NIL,
	    FALSE,0,0));
    list_constant_9 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_class_instance_delta_masks);
    record_system_variable(Qclass_instance_delta_masks,Qsequences1,
	    list_constant_9,Qnil,Qnil,Qnil,Qnil);
    Qembedded_fuzzy_conditionals_list = 
	    STATIC_SYMBOL("EMBEDDED-FUZZY-CONDITIONALS-LIST",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qembedded_fuzzy_conditionals_list,
	    Embedded_fuzzy_conditionals_list);
    Qinitialize_embedded_fuzzy_conditionals_list = 
	    STATIC_SYMBOL("INITIALIZE-EMBEDDED-FUZZY-CONDITIONALS-LIST",
	    AB_package);
    list_constant_10 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_embedded_fuzzy_conditionals_list);
    record_system_variable(Qembedded_fuzzy_conditionals_list,Qsequences1,
	    list_constant_10,Qnil,Qnil,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qinitialize_embedded_fuzzy_conditionals_list,
	    STATIC_FUNCTION(initialize_embedded_fuzzy_conditionals_list,
	    NIL,FALSE,0,0));
    Qseparate_imminent_actions_p = 
	    STATIC_SYMBOL("SEPARATE-IMMINENT-ACTIONS-P",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qseparate_imminent_actions_p,
	    Separate_imminent_actions_p);
    record_system_variable(Qseparate_imminent_actions_p,Qsequences1,T,Qnil,
	    Qnil,Qnil,Qnil);
    Qengage_context_pipelining_p = 
	    STATIC_SYMBOL("ENGAGE-CONTEXT-PIPELINING-P",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qengage_context_pipelining_p,
	    Engage_context_pipelining_p);
    record_system_variable(Qengage_context_pipelining_p,Qsequences1,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qcurrent_inner_procedure_loop_cache_index = 
	    STATIC_SYMBOL("CURRENT-INNER-PROCEDURE-LOOP-CACHE-INDEX",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_inner_procedure_loop_cache_index,
	    Current_inner_procedure_loop_cache_index);
    record_system_variable(Qcurrent_inner_procedure_loop_cache_index,
	    Qsequences1,FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qdrawing_task_tuning_info = STATIC_SYMBOL("DRAWING-TASK-TUNING-INFO",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdrawing_task_tuning_info,
	    Drawing_task_tuning_info);
    record_system_variable(Qdrawing_task_tuning_info,Qsequences1,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qcounter_for_sleep_management_adjustment = 
	    STATIC_SYMBOL("COUNTER-FOR-SLEEP-MANAGEMENT-ADJUSTMENT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcounter_for_sleep_management_adjustment,
	    Counter_for_sleep_management_adjustment);
    Qcycles = STATIC_SYMBOL("CYCLES",AB_package);
    record_system_variable(Qcounter_for_sleep_management_adjustment,
	    Qcycles,FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    if (Legacy_subsecond_heartbeat_adjustment_interval == UNBOUND)
	Legacy_subsecond_heartbeat_adjustment_interval = FIX((SI_Long)10000L);
    Qrefuse_load_at_discrepancy_with_system_clock_message = 
	    STATIC_SYMBOL("REFUSE-LOAD-AT-DISCREPANCY-WITH-SYSTEM-CLOCK-MESSAGE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qrefuse_load_at_discrepancy_with_system_clock_message,
	    Refuse_load_at_discrepancy_with_system_clock_message);
    array_constant_71 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)0L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)2L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)3L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)4L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)5L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)7L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)8L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)9L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)10L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)12L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)13L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)14L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)15L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)16L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)17L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)18L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)19L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)20L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)21L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)22L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)23L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)25L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)26L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)27L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)28L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)29L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)30L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)31L,(SI_Long)126L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)38L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_71,(SI_Long)39L,(SI_Long)57344L);
    string_constant_57 = 
	    STATIC_STRING("43Sy4l3ey43Fymtw3Fy3Ny3Qy3Uy3cy3fy3gy3hy3ny3ry3wy3-0y3-3y3-7y3-Hy3-Oy4l3-Uy4k4k4k4roz3Jy3Sy3Yy3iy3-Cy4k4nu3Gy3-1y4pn3Iy3Vy3-Py3-");
    string_constant_58 = 
	    STATIC_STRING("Sy4n3Cy3Ey3by4xv3Dy3Hy3My3Xy3ay3ly3qy3vy3-*y3-6y3-Ay3-My4l3jy4m3xy3-Gy4m3py3-5y4m3uy3-Ny4opq3-=y3-Fy4o3Oy3ty3-+y3-Ey4mx3-Qy4ory3");
    string_constant_59 = 
	    STATIC_STRING("-8y3-Ry4l3-Ty4l3-9y4n3Wy3my3-By4pl3Ly3Ty3-Iy3-Ky4ts3Py3Zy3ky3oy3sy3-4y3-Dy3-Ly4l3Ky4l3--y4l3Ry4k4m3-2y3-Jy4k4mk3dy");
    SET_SYMBOL_VALUE(Qrefuse_load_at_discrepancy_with_system_clock_message,
	    transform_type_specification_2(FIX((SI_Long)99L),
	    array_constant_71,
	    regenerate_optimized_constant(LIST_3(string_constant_57,
	    string_constant_58,string_constant_59))));
    Qrefuse_save_after_system_clock_tampering_message = 
	    STATIC_SYMBOL("REFUSE-SAVE-AFTER-SYSTEM-CLOCK-TAMPERING-MESSAGE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qrefuse_save_after_system_clock_tampering_message,
	    Refuse_save_after_system_clock_tampering_message);
    array_constant_72 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)0L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)2L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)3L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)4L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)5L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)6L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)7L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)9L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)10L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)11L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)12L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)13L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)15L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)16L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)17L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)18L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)19L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)20L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)21L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)22L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)23L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)24L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)25L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)26L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)27L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)28L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)29L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)30L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)31L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)32L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)33L,(SI_Long)126L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)34L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)38L,(SI_Long)35L);
    UBYTE_16_ISASET_1(array_constant_72,(SI_Long)39L,(SI_Long)57344L);
    string_constant_60 = 
	    STATIC_STRING("43Vy4l3-5y43Jyory3Dy3Jy3Ry3Vy3fy3my3sy3wy3-*y3-3y3-6y3-7y3-8y3-Cy3-Ly3-Ty3-Yy3-cy3-gy3-jy4l3-qy4k4k4k4k4lq4ut3Fy3Ny3ay3uy3-0y3-9");
    string_constant_61 = 
	    STATIC_STRING("y3-Ey3-Ny3-ay4qs3My3ny3qy3-1y3-oy4nz3Ky3-=y4lk4lp4n3Iy3-By3-Dy4v3Cy3Hy3Ly3Qy3Uy3Yy3ky3-+y3-Xy3-ky3-ny4m3-ly3-my4n3ey3-Iy3-Ry4nl3");
    string_constant_62 = 
	    STATIC_STRING("Ty3-Jy4qm3cy3-Hy3-Py3-Vy3-hy4m3ry3-2y4m3oy3-Gy4m3ly3-Wy4ruv3dy3-Ay3-Qy3-dy3-iy4ow3Wy3py3-ey4l3Xy4l3Zy4un3Ey3Py3gy3iy3vy3xy3-My3-");
    string_constant_63 = 
	    STATIC_STRING("Sy3-by4tx3Sy3by3jy3--y3-Ky3-Uy3-fy3-py4l3Oy4m3Gy3-Oy4m3ty3-Zy4k4m3hy3-Fy4l3-4y4k");
    SET_SYMBOL_VALUE(Qrefuse_save_after_system_clock_tampering_message,
	    transform_type_specification_2(FIX((SI_Long)121L),
	    array_constant_72,
	    regenerate_optimized_constant(LIST_4(string_constant_60,
	    string_constant_61,string_constant_62,string_constant_63))));
    Qlimit_bignum_inner_loop_cache_p = 
	    STATIC_SYMBOL("LIMIT-BIGNUM-INNER-LOOP-CACHE-P",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlimit_bignum_inner_loop_cache_p,
	    Limit_bignum_inner_loop_cache_p);
    record_system_variable(Qlimit_bignum_inner_loop_cache_p,Qsequences1,T,
	    Qnil,Qnil,Qnil,Qnil);
    Qevaluator_tradeoff_info = STATIC_SYMBOL("EVALUATOR-TRADEOFF-INFO",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qevaluator_tradeoff_info,
	    Evaluator_tradeoff_info);
    record_system_variable(Qevaluator_tradeoff_info,Qsequences1,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qminimal_fragmentation_seeds = 
	    STATIC_SYMBOL("MINIMAL-FRAGMENTATION-SEEDS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qminimal_fragmentation_seeds,
	    Minimal_fragmentation_seeds);
    Qinitialize_minimal_fragmentation_seeds = 
	    STATIC_SYMBOL("INITIALIZE-MINIMAL-FRAGMENTATION-SEEDS",AB_package);
    list_constant_11 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_minimal_fragmentation_seeds);
    record_system_variable(Qminimal_fragmentation_seeds,Qsequences1,
	    list_constant_11,Qnil,Qnil,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qinitialize_minimal_fragmentation_seeds,
	    STATIC_FUNCTION(initialize_minimal_fragmentation_seeds,NIL,
	    FALSE,0,0));
    Qg2_system_time_too_early_goodbye_message = 
	    STATIC_SYMBOL("G2-SYSTEM-TIME-TOO-EARLY-GOODBYE-MESSAGE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2_system_time_too_early_goodbye_message,
	    G2_system_time_too_early_goodbye_message);
    array_constant_73 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)0L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)2L,(SI_Long)37L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)3L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)4L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)5L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)6L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)7L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)8L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)9L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)10L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)11L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)12L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)13L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)14L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)15L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)16L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)17L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)19L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)20L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)21L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)22L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)23L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)24L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)25L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)26L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)27L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)28L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)29L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)30L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)31L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)32L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)33L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)34L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)35L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)36L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)37L,(SI_Long)126L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)46L,(SI_Long)38L);
    UBYTE_16_ISASET_1(array_constant_73,(SI_Long)47L,(SI_Long)57344L);
    string_constant_64 = 
	    STATIC_STRING("43Yy4n3-2y3*Ay3=Ky43mynx3Gy3My3Sy3Uy3Zy3ey3hy3vy3-0y3-3y3-4y3-5y3-6y3-7y3-8y3-9y3-Dy3-Ly3-Zy3-cy3-jy3-ny3-ty3*+y3*By3*Cy3*Dy3*Ey");
    string_constant_65 = 
	    STATIC_STRING("3*Fy3*Gy3*Hy3*Oy3*Uy3*Zy3*gy3*my3*py3*ty3==y3=4y3=8y3=Fy3=Iy3=Ly3=My3=Ny3=Oy3=Py3=Qy3=Ry4n3-Sy3*8y3=Zy4l3-Yy4n3-Qy3*6y3=Xy4k4m3-");
    string_constant_66 = 
	    STATIC_STRING("by3=Hy4k4k4k4m3-ay3=Gy4l3*Iy4lk4l3-Ty4vs3Ty3cy3ny3ry3-ey3*Ly3=5y3=Ay3=Sy3=Uy4m3ky3wy4t3Hy3Ky3-Ey3-dy3*-y3*hy3*ky3*uy3=Dy4n3-qy3*");
    string_constant_67 = 
	    STATIC_STRING("0y3=7y43Fymq3Ey3Qy3Yy3xy3-=y3-Cy3-Iy3-Py3-ry3*Ky3*Ny3*Qy3*Sy3*ey3*sy3=+y3=3y4l3-+y4nw3Ny3=Ty4ql3by3-By3-vy3*ry3=Ey4vu3Oy3Wy3fy3q");
    string_constant_68 = 
	    STATIC_STRING("y3-Ny3-wy3*1y3*3y3=1y3=Vy4m3Ly3*ly4q3Iy3sy3ty3*Jy3*iy3=9y4p3Fy3Xy3-Oy3*fy3=2y4xv3oy3-Jy3-fy3-gy3-my3-py3*=y3*5y3=-y3=6y3=Cy3=Wy4");
    string_constant_69 = 
	    STATIC_STRING("uo3Jy3--y3-Uy3-hy3**y3*4y3*Wy3*jy3*oy4lp4wr3-*y3-Gy3-Hy3-Vy3-Wy3-ky3-sy3*Py3*Yy3*wy3*xy4vy3Cy3Ry3gy3iy3ly3-xy3*My3*Ry3*ay3*cy43F");
    string_constant_70 = 
	    STATIC_STRING("yt3Dy3Vy3ay3dy3my3py3-Ay3-Ky3-My3-iy3-uy3*2y3*Ty3*dy3*ny3*qy3=*y3=0y4r3jy3-Fy3-ly3-oy3*Xy3*vy3=By4l3Py4k4pz3uy3-Xy3*Vy3*by4k4q3-");
    string_constant_71 = STATIC_STRING("1y3-Ry3*7y3*9y3=Jy3=Yy");
    SET_SYMBOL_VALUE(Qg2_system_time_too_early_goodbye_message,
	    transform_type_specification_2(FIX((SI_Long)232L),
	    array_constant_73,regenerate_optimized_constant(list(8,
	    string_constant_64,string_constant_65,string_constant_66,
	    string_constant_67,string_constant_68,string_constant_69,
	    string_constant_70,string_constant_71))));
    Qtw_system_time_too_early_goodbye_message = 
	    STATIC_SYMBOL("TW-SYSTEM-TIME-TOO-EARLY-GOODBYE-MESSAGE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtw_system_time_too_early_goodbye_message,
	    Tw_system_time_too_early_goodbye_message);
    array_constant_74 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)0L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)2L,(SI_Long)37L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)3L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)4L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)5L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)6L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)7L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)13L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)14L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)15L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)16L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)17L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)18L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)19L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)20L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)21L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)22L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)23L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)24L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)25L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)26L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)27L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)28L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)29L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)30L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)31L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)32L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)33L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)34L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)35L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)36L,(SI_Long)126L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)38L,(SI_Long)37L);
    UBYTE_16_ISASET_1(array_constant_74,(SI_Long)39L,(SI_Long)57344L);
    string_constant_72 = 
	    STATIC_STRING("43Xy4n3-2y3*7y3=Fy43mynx3Gy3My3Sy3Uy3Zy3ey3hy3vy3-0y3-3y3-4y3-5y3-6y3-7y3-8y3-9y3-Dy3-Ly3-Zy3-ly3-sy3-wy3*0y3*5y3*8y3*9y3*Ay3*By");
    string_constant_73 = 
	    STATIC_STRING("3*Cy3*Dy3*Ey3*Xy3*dy3*iy3*py3*vy3=+y3=0y3=8y3=Dy3=Gy3=Hy3=Iy3=Jy3=Ky3=Ly3=My3=Qy3=Xy3=jy4n3-Sy3*Qy3=ry4k4n3-Qy3*Oy3=py4l3-Yy4k4l");
    string_constant_74 = 
	    STATIC_STRING("3-+y4wo3Jy3--y3-Uy3-iy3-qy3*Gy3*My3*fy3*sy3*xy3=gy4zv3oy3-Jy3-gy3-oy3-py3-vy3*+y3*Hy3*Ny3=6y3=Oy3=Uy3=ey3=oy43Jymq3Ey3Qy3Yy3xy3-");
    string_constant_75 = 
	    STATIC_STRING("=y3-Cy3-Iy3-Py3-by3-dy3**y3*Ty3*Wy3*Zy3*by3*ny3==y3=5y3=Cy3=Zy3=by4xu3Oy3Wy3fy3qy3-Ny3-fy3*3y3*Jy3*Ly3=Ay3=dy3=ny4vs3Ty3cy3ny3ry");
    string_constant_76 = 
	    STATIC_STRING("3-ny3*Uy3=Ny3=Sy3=ky3=my4m3ky3wy4nw3Ny3=ly4ql3by3-By3*2y3=*y3=Wy4t3Hy3Ky3-Ey3-my3*Fy3*qy3*ty3=1y3=Vy4s3Iy3sy3ty3-cy3*Sy3*ry3=Ry3");
    string_constant_77 = 
	    STATIC_STRING("=ay4nk3-ay3=Yy4p3Fy3Xy3-Oy3*oy3=By4l3-Ty4p3-hy3*-y3*Iy3=Py3=fy4m3Ly3*uy4k4k4l3*Ry4wr3-*y3-Gy3-Hy3-Vy3-Wy3-ty3*=y3*Yy3*hy3=3y3=4y");
    string_constant_78 = 
	    STATIC_STRING("4lp4xy3Cy3Ry3gy3iy3ly3-ky3*4y3*Vy3*ay3*jy3*ly3=iy43Fyt3Dy3Vy3ay3dy3my3py3-Ay3-Ky3-My3-ry3*1y3*Ky3*cy3*my3*wy3=-y3=7y3=9y4r3jy3-F");
    string_constant_79 = 
	    STATIC_STRING("y3-uy3-xy3*gy3=2y3=Ty4l3Py4o3-ey3-jy3=cy3=hy4k4pz3uy3-Xy3*ey3*ky4k4q3-1y3-Ry3*6y3*Py3=Ey3=qy");
    SET_SYMBOL_VALUE(Qtw_system_time_too_early_goodbye_message,
	    transform_type_specification_2(FIX((SI_Long)250L),
	    array_constant_74,regenerate_optimized_constant(list(8,
	    string_constant_72,string_constant_73,string_constant_74,
	    string_constant_75,string_constant_76,string_constant_77,
	    string_constant_78,string_constant_79))));
    Qmaster_hierarchy_reconciliation_switches = 
	    STATIC_SYMBOL("MASTER-HIERARCHY-RECONCILIATION-SWITCHES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmaster_hierarchy_reconciliation_switches,
	    Master_hierarchy_reconciliation_switches);
    Qinitialize_master_hierarchy_reconciliation_switches = 
	    STATIC_SYMBOL("INITIALIZE-MASTER-HIERARCHY-RECONCILIATION-SWITCHES",
	    AB_package);
    list_constant_12 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_master_hierarchy_reconciliation_switches);
    record_system_variable(Qmaster_hierarchy_reconciliation_switches,
	    Qsequences1,list_constant_12,Qnil,Qnil,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qinitialize_master_hierarchy_reconciliation_switches,
	    STATIC_FUNCTION(initialize_master_hierarchy_reconciliation_switches,
	    NIL,FALSE,0,0));
    Qconsistency_tree_focus_shifts = 
	    STATIC_SYMBOL("CONSISTENCY-TREE-FOCUS-SHIFTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qconsistency_tree_focus_shifts,
	    Consistency_tree_focus_shifts);
    Qinitialize_consistency_tree_focus_shifts = 
	    STATIC_SYMBOL("INITIALIZE-CONSISTENCY-TREE-FOCUS-SHIFTS",
	    AB_package);
    list_constant_13 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_consistency_tree_focus_shifts);
    record_system_variable(Qconsistency_tree_focus_shifts,Qsequences1,
	    list_constant_13,Qnil,Qnil,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qinitialize_consistency_tree_focus_shifts,
	    STATIC_FUNCTION(initialize_consistency_tree_focus_shifts,NIL,
	    FALSE,0,0));
    Qembedded_g2_with_windows_goodbye_message = 
	    STATIC_SYMBOL("EMBEDDED-G2-WITH-WINDOWS-GOODBYE-MESSAGE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qembedded_g2_with_windows_goodbye_message,
	    Embedded_g2_with_windows_goodbye_message);
    array_constant_75 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)0L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)2L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)3L,(SI_Long)37L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)4L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)5L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)6L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)7L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)8L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)9L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)10L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)11L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)12L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)13L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)14L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)15L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)17L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)18L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)19L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)20L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)21L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)22L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)23L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)24L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)25L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)26L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)27L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)28L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)29L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)30L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)31L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)32L,(SI_Long)126L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)38L,(SI_Long)33L);
    UBYTE_16_ISASET_1(array_constant_75,(SI_Long)39L,(SI_Long)57344L);
    string_constant_80 = 
	    STATIC_STRING("43Ty4m3sy3*=y43Oyqtw3Cy3Ny3Qy3Uy3Zy3by3hy3ty3uy3vy3-0y3-7y3-Cy3-Gy3-Qy3-Xy3-ay3-ey3-my3-ry3-vy3*-y3*0y3*1y3*2y4l3-Hy4ml3qy4m3oy3");
    string_constant_81 = 
	    STATIC_STRING("*Ey4k4ls4k4k4k4lr4l3wy4mm3*3y4r3Dy3ay3fy3--y3-2y3-jy3-sy4n3ey3-5y3-fy4q3My3ly3-Ny3-ly3-uy3*Ay4t3Ly3-+y3-=y3-Fy3-dy3-qy3*+y3*4y3*");
    string_constant_82 = 
	    STATIC_STRING("6y4rn3Gy3Yy3-6y3-By3-Ey3-cy4uou3Jy3Wy3jy3-9y3-Ly3-Uy3-oy3*8y4q3cy3gy3xy3-1y3-ny3*5y4m3-hy3-iy4wx3Ty3ky3-4y3-Iy3-My3-Wy3-Zy3-ky3-");
    string_constant_83 = 
	    STATIC_STRING("py3-ty3*9y4wy3Hy3Py3dy3my3-Jy3-Oy3-Ry3-Vy3-Yy3-gy3*By4l3-Sy4m3Iy3Ry4ppv3-*y3-xy3*Dy4sz3Fy3Oy3Xy3-Ay3-Dy3-Ty3-by4o3Ey3Sy3-3y3-wy4");
    string_constant_84 = 
	    STATIC_STRING("k4s3Vy3iy3ny3-8y3-Ky3-Py3*7y3*Cy4k4l3Ky4ok3py3ry3**y");
    SET_SYMBOL_VALUE(Qembedded_g2_with_windows_goodbye_message,
	    transform_type_specification_2(FIX((SI_Long)147L),
	    array_constant_75,
	    regenerate_optimized_constant(LIST_5(string_constant_80,
	    string_constant_81,string_constant_82,string_constant_83,
	    string_constant_84))));
    if (Chaining_refresh_version == UNBOUND)
	Chaining_refresh_version = 
		Major_version_number_of_current_gensym_product_line;
    array_constant = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)54L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)52L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)57344L);
    array_constant_1 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)56L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)56L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)113L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)57344L);
    array_constant_2 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)57L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)57L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)52L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)57344L);
    array_constant_3 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)56L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)54L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)52L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)57344L);
    array_constant_4 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)56L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)106L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)57L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)57344L);
    array_constant_5 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)56L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)54L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)57344L);
    Qchaining_refresh_list = STATIC_SYMBOL("CHAINING-REFRESH-LIST",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchaining_refresh_list,Chaining_refresh_list);
    Qchoose_chaining_refresh_list = 
	    STATIC_SYMBOL("CHOOSE-CHAINING-REFRESH-LIST",AB_package);
    SET_SYMBOL_FUNCTION(Qchoose_chaining_refresh_list,
	    STATIC_FUNCTION(choose_chaining_refresh_list,NIL,FALSE,0,0));
    list_constant_14 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qchoose_chaining_refresh_list);
    record_system_variable(Qchaining_refresh_list,Qsequences1,
	    list_constant_14,Qnil,Qnil,Qnil,Qnil);
    Qsize_of_local_machine_id = STATIC_SYMBOL("SIZE-OF-LOCAL-MACHINE-ID",
	    AB_package);
    SET_SYMBOL_VALUE(Qsize_of_local_machine_id,FIX((SI_Long)256L));
    if (First_string_in_pool_group == UNBOUND)
	First_string_in_pool_group = Nil;
    if (Name_of_customer_in_ok_file == UNBOUND)
	Name_of_customer_in_ok_file = Nil;
    if (Serial_number_in_ok_file == UNBOUND)
	Serial_number_in_ok_file = Nil;
    if (Installation_code_in_ok_file == UNBOUND)
	Installation_code_in_ok_file = Nil;
    array_constant_76 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)56L));
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)5L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)7L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)9L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)11L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)14L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)18L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)19L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)20L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)21L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)22L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)23L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)24L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)25L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)26L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)27L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)28L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)29L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)30L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)31L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)32L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)33L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)34L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)35L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)36L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)37L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)38L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)39L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)40L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)41L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)42L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)43L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)44L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)45L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)46L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)47L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)54L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_76,(SI_Long)55L,(SI_Long)57344L);
    Original_site_license_title_block_phrase = array_constant_76;
    array_constant_77 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)1L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)3L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)5L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)10L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)11L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)14L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)15L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)16L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)17L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)18L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)19L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)20L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)21L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)22L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)23L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)25L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)26L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)27L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)28L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)29L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)30L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)31L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)32L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)33L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)34L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)35L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)36L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)37L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)38L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)39L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)40L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)41L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)42L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)43L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)46L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_77,(SI_Long)47L,(SI_Long)57344L);
    Site_license_title_block_phrase = array_constant_77;
    array_constant_78 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)7L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)8L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)9L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)10L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)12L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)13L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_78,(SI_Long)23L,(SI_Long)57344L);
    Serial_number_title_block_phrase = array_constant_78;
    Qunbound_in_protected_let = STATIC_SYMBOL("UNBOUND-IN-PROTECTED-LET",
	    AB_package);
    array_constant_6 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)57344L);
    string_constant = STATIC_STRING(";~% ~a ~a");
    string_constant_1 = STATIC_STRING(";~% This ~a ~a ~a~% ~a ~a");
    string_constant_2 = STATIC_STRING(";~% This ~a ~a ~a");
    string_constant_3 = STATIC_STRING(";~% This ~a ~a UNKNOWN~% ~a ~a");
    string_constant_4 = STATIC_STRING(";~% This ~a ~a UNKNOWN");
    string_constant_5 = STATIC_STRING(";~% Machine ID: ~s");
    if (Cached_machine_id_qm == UNBOUND)
	Cached_machine_id_qm = Nil;
    Mask12 = FIX((SI_Long)4095L);
    New_modulus = FIX((SI_Long)943223L);
    array_constant_79 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)0L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)1L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)2L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)3L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)4L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)5L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)6L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)7L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)8L,(SI_Long)52L);
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)9L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)10L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)11L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant_79,(SI_Long)15L,(SI_Long)57344L);
    array_constant_80 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)0L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)2L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)5L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_80,(SI_Long)15L,(SI_Long)57344L);
    array_constant_81 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_81,(SI_Long)7L,(SI_Long)57344L);
    array_constant_82 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_82,(SI_Long)0L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_82,(SI_Long)1L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_82,(SI_Long)2L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_82,(SI_Long)3L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_82,(SI_Long)4L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_82,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_82,(SI_Long)7L,(SI_Long)57344L);
    array_constant_83 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_83,(SI_Long)0L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_83,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_83,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_83,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_83,(SI_Long)4L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_83,(SI_Long)5L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_83,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_83,(SI_Long)15L,(SI_Long)57344L);
    array_constant_84 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_84,(SI_Long)0L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_84,(SI_Long)1L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_84,(SI_Long)2L,(SI_Long)54L);
    UBYTE_16_ISASET_1(array_constant_84,(SI_Long)3L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_84,(SI_Long)4L,(SI_Long)57L);
    UBYTE_16_ISASET_1(array_constant_84,(SI_Long)5L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_84,(SI_Long)6L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_84,(SI_Long)7L,(SI_Long)52L);
    UBYTE_16_ISASET_1(array_constant_84,(SI_Long)8L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_84,(SI_Long)9L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_84,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_84,(SI_Long)15L,(SI_Long)57344L);
    list_constant_15 = STATIC_LIST((SI_Long)6L,array_constant_79,
	    array_constant_80,array_constant_81,array_constant_82,
	    array_constant_83,array_constant_84);
    if (Shunned_machine_ids_list == UNBOUND)
	Shunned_machine_ids_list = list_constant_15;
    Qnormalized_string_equal = STATIC_SYMBOL("NORMALIZED-STRING-EQUAL",
	    AB_package);
    string_constant_6 = STATIC_STRING("error");
    SET_SYMBOL_FUNCTION(Qnormalized_string_equal,
	    STATIC_FUNCTION(normalized_string_equal,NIL,TRUE,2,3));
    Kcommand_line = STATIC_SYMBOL("COMMAND-LINE",Pkeyword);
    Kenvironment_variable = STATIC_SYMBOL("ENVIRONMENT-VARIABLE",Pkeyword);
    array_constant_7 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)57344L);
    array_constant_8 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)57344L);
    Qdefault_tw_ok_pathname = STATIC_SYMBOL("DEFAULT-TW-OK-PATHNAME",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefault_tw_ok_pathname,Default_tw_ok_pathname);
    Qpathnames = STATIC_SYMBOL("PATHNAMES",AB_package);
    Qinitialize_default_tw_ok_pathname = 
	    STATIC_SYMBOL("INITIALIZE-DEFAULT-TW-OK-PATHNAME",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_default_tw_ok_pathname,
	    STATIC_FUNCTION(initialize_default_tw_ok_pathname,NIL,FALSE,0,0));
    list_constant_16 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_default_tw_ok_pathname);
    record_system_variable(Qdefault_tw_ok_pathname,Qpathnames,
	    list_constant_16,Qnil,Qnil,Qnil,Qnil);
    Kabsolute = STATIC_SYMBOL("ABSOLUTE",Pkeyword);
    list_constant = STATIC_CONS(Kabsolute,Qnil);
    array_constant_9 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)5L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)15L,(SI_Long)57344L);
    array_constant_10 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)57344L);
    Qpathname_for_disabling_tw_ok_command_line = 
	    STATIC_SYMBOL("PATHNAME-FOR-DISABLING-TW-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpathname_for_disabling_tw_ok_command_line,
	    Pathname_for_disabling_tw_ok_command_line);
    Qinitializer_for_pathname_for_disabling_tw_ok_command_line = 
	    STATIC_SYMBOL("INITIALIZER-FOR-PATHNAME-FOR-DISABLING-TW-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitializer_for_pathname_for_disabling_tw_ok_command_line,
	    STATIC_FUNCTION(initializer_for_pathname_for_disabling_tw_ok_command_line,
	    NIL,FALSE,0,0));
    list_constant_17 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitializer_for_pathname_for_disabling_tw_ok_command_line);
    record_system_variable(Qpathname_for_disabling_tw_ok_command_line,
	    Qpathnames,list_constant_17,Qnil,Qnil,Qnil,Qnil);
    array_constant_11 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)4L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)57344L);
    array_constant_12 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)3L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)57344L);
    Qdefault_twv5_ok_pathname = STATIC_SYMBOL("DEFAULT-TWV5-OK-PATHNAME",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefault_twv5_ok_pathname,
	    Default_twv5_ok_pathname);
    Qinitialize_default_twv5_ok_pathname = 
	    STATIC_SYMBOL("INITIALIZE-DEFAULT-TWV5-OK-PATHNAME",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_default_twv5_ok_pathname,
	    STATIC_FUNCTION(initialize_default_twv5_ok_pathname,NIL,FALSE,
	    0,0));
    list_constant_18 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_default_twv5_ok_pathname);
    record_system_variable(Qdefault_twv5_ok_pathname,Qpathnames,
	    list_constant_18,Qnil,Qnil,Qnil,Qnil);
    array_constant_13 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)1L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)2L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)3L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)4L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)7L,(SI_Long)57344L);
    Qpathname_for_disabling_twv5_ok_command_line = 
	    STATIC_SYMBOL("PATHNAME-FOR-DISABLING-TWV5-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpathname_for_disabling_twv5_ok_command_line,
	    Pathname_for_disabling_twv5_ok_command_line);
    Qinitializer_for_pathname_for_disabling_twv5_ok_command_line = 
	    STATIC_SYMBOL("INITIALIZER-FOR-PATHNAME-FOR-DISABLING-TWV5-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitializer_for_pathname_for_disabling_twv5_ok_command_line,
	    STATIC_FUNCTION(initializer_for_pathname_for_disabling_twv5_ok_command_line,
	    NIL,FALSE,0,0));
    list_constant_19 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitializer_for_pathname_for_disabling_twv5_ok_command_line);
    record_system_variable(Qpathname_for_disabling_twv5_ok_command_line,
	    Qpathnames,list_constant_19,Qnil,Qnil,Qnil,Qnil);
    array_constant_14 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)0L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)1L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)3L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)7L,(SI_Long)57344L);
    array_constant_15 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)1L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)2L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)3L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)4L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)5L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)6L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)15L,(SI_Long)57344L);
    array_constant_16 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)1L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)3L,(SI_Long)54L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)7L,(SI_Long)57344L);
    Qdefault_twv6_ok_pathname = STATIC_SYMBOL("DEFAULT-TWV6-OK-PATHNAME",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefault_twv6_ok_pathname,
	    Default_twv6_ok_pathname);
    Qinitialize_default_twv6_ok_pathname = 
	    STATIC_SYMBOL("INITIALIZE-DEFAULT-TWV6-OK-PATHNAME",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_default_twv6_ok_pathname,
	    STATIC_FUNCTION(initialize_default_twv6_ok_pathname,NIL,FALSE,
	    0,0));
    list_constant_20 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_default_twv6_ok_pathname);
    record_system_variable(Qdefault_twv6_ok_pathname,Qpathnames,
	    list_constant_20,Qnil,Qnil,Qnil,Qnil);
    Qpathname_for_disabling_twv6_ok_command_line = 
	    STATIC_SYMBOL("PATHNAME-FOR-DISABLING-TWV6-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpathname_for_disabling_twv6_ok_command_line,
	    Pathname_for_disabling_twv6_ok_command_line);
    Qinitializer_for_pathname_for_disabling_twv6_ok_command_line = 
	    STATIC_SYMBOL("INITIALIZER-FOR-PATHNAME-FOR-DISABLING-TWV6-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitializer_for_pathname_for_disabling_twv6_ok_command_line,
	    STATIC_FUNCTION(initializer_for_pathname_for_disabling_twv6_ok_command_line,
	    NIL,FALSE,0,0));
    list_constant_21 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitializer_for_pathname_for_disabling_twv6_ok_command_line);
    record_system_variable(Qpathname_for_disabling_twv6_ok_command_line,
	    Qpathnames,list_constant_21,Qnil,Qnil,Qnil,Qnil);
    array_constant_17 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)0L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)1L,(SI_Long)54L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)3L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)7L,(SI_Long)57344L);
    array_constant_18 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)1L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)2L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)3L,(SI_Long)54L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)4L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)5L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)6L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)15L,(SI_Long)57344L);
    array_constant_19 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)1L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)3L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)7L,(SI_Long)57344L);
    Qdefault_twv7_ok_pathname = STATIC_SYMBOL("DEFAULT-TWV7-OK-PATHNAME",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefault_twv7_ok_pathname,
	    Default_twv7_ok_pathname);
    Qinitialize_default_twv7_ok_pathname = 
	    STATIC_SYMBOL("INITIALIZE-DEFAULT-TWV7-OK-PATHNAME",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_default_twv7_ok_pathname,
	    STATIC_FUNCTION(initialize_default_twv7_ok_pathname,NIL,FALSE,
	    0,0));
    list_constant_22 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_default_twv7_ok_pathname);
    record_system_variable(Qdefault_twv7_ok_pathname,Qpathnames,
	    list_constant_22,Qnil,Qnil,Qnil,Qnil);
    Qpathname_for_disabling_twv7_ok_command_line = 
	    STATIC_SYMBOL("PATHNAME-FOR-DISABLING-TWV7-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpathname_for_disabling_twv7_ok_command_line,
	    Pathname_for_disabling_twv7_ok_command_line);
    Qinitializer_for_pathname_for_disabling_twv7_ok_command_line = 
	    STATIC_SYMBOL("INITIALIZER-FOR-PATHNAME-FOR-DISABLING-TWV7-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitializer_for_pathname_for_disabling_twv7_ok_command_line,
	    STATIC_FUNCTION(initializer_for_pathname_for_disabling_twv7_ok_command_line,
	    NIL,FALSE,0,0));
    list_constant_23 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitializer_for_pathname_for_disabling_twv7_ok_command_line);
    record_system_variable(Qpathname_for_disabling_twv7_ok_command_line,
	    Qpathnames,list_constant_23,Qnil,Qnil,Qnil,Qnil);
    array_constant_20 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)0L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)1L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)3L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)7L,(SI_Long)57344L);
    array_constant_21 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)1L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)2L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)3L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)4L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)5L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)6L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)15L,(SI_Long)57344L);
    array_constant_22 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)1L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)3L,(SI_Long)56L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)7L,(SI_Long)57344L);
    Qdefault_twv8_ok_pathname = STATIC_SYMBOL("DEFAULT-TWV8-OK-PATHNAME",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefault_twv8_ok_pathname,
	    Default_twv8_ok_pathname);
    Qinitialize_default_twv8_ok_pathname = 
	    STATIC_SYMBOL("INITIALIZE-DEFAULT-TWV8-OK-PATHNAME",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_default_twv8_ok_pathname,
	    STATIC_FUNCTION(initialize_default_twv8_ok_pathname,NIL,FALSE,
	    0,0));
    list_constant_24 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_default_twv8_ok_pathname);
    record_system_variable(Qdefault_twv8_ok_pathname,Qpathnames,
	    list_constant_24,Qnil,Qnil,Qnil,Qnil);
    Qpathname_for_disabling_twv8_ok_command_line = 
	    STATIC_SYMBOL("PATHNAME-FOR-DISABLING-TWV8-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpathname_for_disabling_twv8_ok_command_line,
	    Pathname_for_disabling_twv8_ok_command_line);
    Qinitializer_for_pathname_for_disabling_twv8_ok_command_line = 
	    STATIC_SYMBOL("INITIALIZER-FOR-PATHNAME-FOR-DISABLING-TWV8-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitializer_for_pathname_for_disabling_twv8_ok_command_line,
	    STATIC_FUNCTION(initializer_for_pathname_for_disabling_twv8_ok_command_line,
	    NIL,FALSE,0,0));
    list_constant_25 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitializer_for_pathname_for_disabling_twv8_ok_command_line);
    record_system_variable(Qpathname_for_disabling_twv8_ok_command_line,
	    Qpathnames,list_constant_25,Qnil,Qnil,Qnil,Qnil);
    array_constant_23 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)0L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)1L,(SI_Long)56L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)3L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)7L,(SI_Long)57344L);
    array_constant_24 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)1L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)2L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)3L,(SI_Long)56L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)4L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)5L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)6L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)15L,(SI_Long)57344L);
    array_constant_25 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)1L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)3L,(SI_Long)57L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)7L,(SI_Long)57344L);
    Qdefault_twv9_ok_pathname = STATIC_SYMBOL("DEFAULT-TWV9-OK-PATHNAME",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefault_twv9_ok_pathname,
	    Default_twv9_ok_pathname);
    Qinitialize_default_twv9_ok_pathname = 
	    STATIC_SYMBOL("INITIALIZE-DEFAULT-TWV9-OK-PATHNAME",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_default_twv9_ok_pathname,
	    STATIC_FUNCTION(initialize_default_twv9_ok_pathname,NIL,FALSE,
	    0,0));
    list_constant_26 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_default_twv9_ok_pathname);
    record_system_variable(Qdefault_twv9_ok_pathname,Qpathnames,
	    list_constant_26,Qnil,Qnil,Qnil,Qnil);
    Qpathname_for_disabling_twv9_ok_command_line = 
	    STATIC_SYMBOL("PATHNAME-FOR-DISABLING-TWV9-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpathname_for_disabling_twv9_ok_command_line,
	    Pathname_for_disabling_twv9_ok_command_line);
    Qinitializer_for_pathname_for_disabling_twv9_ok_command_line = 
	    STATIC_SYMBOL("INITIALIZER-FOR-PATHNAME-FOR-DISABLING-TWV9-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitializer_for_pathname_for_disabling_twv9_ok_command_line,
	    STATIC_FUNCTION(initializer_for_pathname_for_disabling_twv9_ok_command_line,
	    NIL,FALSE,0,0));
    list_constant_27 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitializer_for_pathname_for_disabling_twv9_ok_command_line);
    record_system_variable(Qpathname_for_disabling_twv9_ok_command_line,
	    Qpathnames,list_constant_27,Qnil,Qnil,Qnil,Qnil);
    array_constant_26 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)0L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)1L,(SI_Long)57L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)3L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)7L,(SI_Long)57344L);
    array_constant_27 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)1L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)2L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)3L,(SI_Long)57L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)4L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)5L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)6L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)15L,(SI_Long)57344L);
    array_constant_28 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)1L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)3L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)4L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)7L,(SI_Long)57344L);
    Qdefault_twv11_ok_pathname = STATIC_SYMBOL("DEFAULT-TWV11-OK-PATHNAME",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefault_twv11_ok_pathname,
	    Default_twv11_ok_pathname);
    Qinitialize_default_twv11_ok_pathname = 
	    STATIC_SYMBOL("INITIALIZE-DEFAULT-TWV11-OK-PATHNAME",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_default_twv11_ok_pathname,
	    STATIC_FUNCTION(initialize_default_twv11_ok_pathname,NIL,FALSE,
	    0,0));
    list_constant_28 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_default_twv11_ok_pathname);
    record_system_variable(Qdefault_twv11_ok_pathname,Qpathnames,
	    list_constant_28,Qnil,Qnil,Qnil,Qnil);
    Qpathname_for_disabling_twv11_ok_command_line = 
	    STATIC_SYMBOL("PATHNAME-FOR-DISABLING-TWV11-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpathname_for_disabling_twv11_ok_command_line,
	    Pathname_for_disabling_twv11_ok_command_line);
    Qinitializer_for_pathname_for_disabling_twv11_ok_command_line = 
	    STATIC_SYMBOL("INITIALIZER-FOR-PATHNAME-FOR-DISABLING-TWV11-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitializer_for_pathname_for_disabling_twv11_ok_command_line,
	    STATIC_FUNCTION(initializer_for_pathname_for_disabling_twv11_ok_command_line,
	    NIL,FALSE,0,0));
    list_constant_29 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitializer_for_pathname_for_disabling_twv11_ok_command_line);
    record_system_variable(Qpathname_for_disabling_twv11_ok_command_line,
	    Qpathnames,list_constant_29,Qnil,Qnil,Qnil,Qnil);
    array_constant_29 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)0L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)1L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)2L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)4L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)7L,(SI_Long)57344L);
    array_constant_30 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)1L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)2L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)3L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)4L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)5L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)6L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)7L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)15L,(SI_Long)57344L);
    array_constant_31 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)1L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)3L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)4L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)7L,(SI_Long)57344L);
    Qdefault_twv12_ok_pathname = STATIC_SYMBOL("DEFAULT-TWV12-OK-PATHNAME",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefault_twv12_ok_pathname,
	    Default_twv12_ok_pathname);
    Qinitialize_default_twv12_ok_pathname = 
	    STATIC_SYMBOL("INITIALIZE-DEFAULT-TWV12-OK-PATHNAME",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_default_twv12_ok_pathname,
	    STATIC_FUNCTION(initialize_default_twv12_ok_pathname,NIL,FALSE,
	    0,0));
    list_constant_30 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_default_twv12_ok_pathname);
    record_system_variable(Qdefault_twv12_ok_pathname,Qpathnames,
	    list_constant_30,Qnil,Qnil,Qnil,Qnil);
    Qpathname_for_disabling_twv12_ok_command_line = 
	    STATIC_SYMBOL("PATHNAME-FOR-DISABLING-TWV12-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpathname_for_disabling_twv12_ok_command_line,
	    Pathname_for_disabling_twv12_ok_command_line);
    Qinitializer_for_pathname_for_disabling_twv12_ok_command_line = 
	    STATIC_SYMBOL("INITIALIZER-FOR-PATHNAME-FOR-DISABLING-TWV12-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitializer_for_pathname_for_disabling_twv12_ok_command_line,
	    STATIC_FUNCTION(initializer_for_pathname_for_disabling_twv12_ok_command_line,
	    NIL,FALSE,0,0));
    list_constant_31 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitializer_for_pathname_for_disabling_twv12_ok_command_line);
    record_system_variable(Qpathname_for_disabling_twv12_ok_command_line,
	    Qpathnames,list_constant_31,Qnil,Qnil,Qnil,Qnil);
    array_constant_32 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)0L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)1L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)2L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)4L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)7L,(SI_Long)57344L);
    array_constant_33 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)1L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)2L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)3L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)4L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)5L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)6L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)7L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)15L,(SI_Long)57344L);
    array_constant_34 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)0L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)7L,(SI_Long)57344L);
    Qdefault_g2_ok_pathname = STATIC_SYMBOL("DEFAULT-G2-OK-PATHNAME",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefault_g2_ok_pathname,Default_g2_ok_pathname);
    Qinitialize_default_g2_ok_pathname = 
	    STATIC_SYMBOL("INITIALIZE-DEFAULT-G2-OK-PATHNAME",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_default_g2_ok_pathname,
	    STATIC_FUNCTION(initialize_default_g2_ok_pathname,NIL,FALSE,0,0));
    list_constant_32 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_default_g2_ok_pathname);
    record_system_variable(Qdefault_g2_ok_pathname,Qpathnames,
	    list_constant_32,Qnil,Qnil,Qnil,Qnil);
    Qpathname_for_disabling_g2_ok_command_line = 
	    STATIC_SYMBOL("PATHNAME-FOR-DISABLING-G2-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpathname_for_disabling_g2_ok_command_line,
	    Pathname_for_disabling_g2_ok_command_line);
    Qinitializer_for_pathname_for_disabling_g2_ok_command_line = 
	    STATIC_SYMBOL("INITIALIZER-FOR-PATHNAME-FOR-DISABLING-G2-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitializer_for_pathname_for_disabling_g2_ok_command_line,
	    STATIC_FUNCTION(initializer_for_pathname_for_disabling_g2_ok_command_line,
	    NIL,FALSE,0,0));
    list_constant_33 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitializer_for_pathname_for_disabling_g2_ok_command_line);
    record_system_variable(Qpathname_for_disabling_g2_ok_command_line,
	    Qpathnames,list_constant_33,Qnil,Qnil,Qnil,Qnil);
    array_constant_35 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)0L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)2L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)3L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)4L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)7L,(SI_Long)57344L);
    array_constant_36 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)0L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)3L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)7L,(SI_Long)57344L);
    Qdefault_g2v5_ok_pathname = STATIC_SYMBOL("DEFAULT-G2V5-OK-PATHNAME",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefault_g2v5_ok_pathname,
	    Default_g2v5_ok_pathname);
    Qinitialize_default_g2v5_ok_pathname = 
	    STATIC_SYMBOL("INITIALIZE-DEFAULT-G2V5-OK-PATHNAME",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_default_g2v5_ok_pathname,
	    STATIC_FUNCTION(initialize_default_g2v5_ok_pathname,NIL,FALSE,
	    0,0));
    list_constant_34 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_default_g2v5_ok_pathname);
    record_system_variable(Qdefault_g2v5_ok_pathname,Qpathnames,
	    list_constant_34,Qnil,Qnil,Qnil,Qnil);
    Qpathname_for_disabling_g2v5_ok_command_line = 
	    STATIC_SYMBOL("PATHNAME-FOR-DISABLING-G2V5-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpathname_for_disabling_g2v5_ok_command_line,
	    Pathname_for_disabling_g2v5_ok_command_line);
    Qinitializer_for_pathname_for_disabling_g2v5_ok_command_line = 
	    STATIC_SYMBOL("INITIALIZER-FOR-PATHNAME-FOR-DISABLING-G2V5-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitializer_for_pathname_for_disabling_g2v5_ok_command_line,
	    STATIC_FUNCTION(initializer_for_pathname_for_disabling_g2v5_ok_command_line,
	    NIL,FALSE,0,0));
    list_constant_35 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitializer_for_pathname_for_disabling_g2v5_ok_command_line);
    record_system_variable(Qpathname_for_disabling_g2v5_ok_command_line,
	    Qpathnames,list_constant_35,Qnil,Qnil,Qnil,Qnil);
    array_constant_37 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)0L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)2L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)3L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)4L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)5L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)6L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)15L,(SI_Long)57344L);
    array_constant_38 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)0L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)3L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)4L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)7L,(SI_Long)57344L);
    Qdefault_g2v51_ok_pathname = STATIC_SYMBOL("DEFAULT-G2V51-OK-PATHNAME",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefault_g2v51_ok_pathname,
	    Default_g2v51_ok_pathname);
    Qinitialize_default_g2v51_ok_pathname = 
	    STATIC_SYMBOL("INITIALIZE-DEFAULT-G2V51-OK-PATHNAME",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_default_g2v51_ok_pathname,
	    STATIC_FUNCTION(initialize_default_g2v51_ok_pathname,NIL,FALSE,
	    0,0));
    list_constant_36 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_default_g2v51_ok_pathname);
    record_system_variable(Qdefault_g2v51_ok_pathname,Qpathnames,
	    list_constant_36,Qnil,Qnil,Qnil,Qnil);
    Qpathname_for_disabling_g2v51_ok_command_line = 
	    STATIC_SYMBOL("PATHNAME-FOR-DISABLING-G2V51-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpathname_for_disabling_g2v51_ok_command_line,
	    Pathname_for_disabling_g2v51_ok_command_line);
    Qinitializer_for_pathname_for_disabling_g2v51_ok_command_line = 
	    STATIC_SYMBOL("INITIALIZER-FOR-PATHNAME-FOR-DISABLING-G2V51-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitializer_for_pathname_for_disabling_g2v51_ok_command_line,
	    STATIC_FUNCTION(initializer_for_pathname_for_disabling_g2v51_ok_command_line,
	    NIL,FALSE,0,0));
    list_constant_37 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitializer_for_pathname_for_disabling_g2v51_ok_command_line);
    record_system_variable(Qpathname_for_disabling_g2v51_ok_command_line,
	    Qpathnames,list_constant_37,Qnil,Qnil,Qnil,Qnil);
    array_constant_39 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)0L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)1L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)2L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)4L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)7L,(SI_Long)57344L);
    array_constant_40 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)0L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)2L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)3L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)4L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)5L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)6L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)7L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)15L,(SI_Long)57344L);
    array_constant_41 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)0L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)3L,(SI_Long)54L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)7L,(SI_Long)57344L);
    Qdefault_g2v6_ok_pathname = STATIC_SYMBOL("DEFAULT-G2V6-OK-PATHNAME",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefault_g2v6_ok_pathname,
	    Default_g2v6_ok_pathname);
    Qinitialize_default_g2v6_ok_pathname = 
	    STATIC_SYMBOL("INITIALIZE-DEFAULT-G2V6-OK-PATHNAME",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_default_g2v6_ok_pathname,
	    STATIC_FUNCTION(initialize_default_g2v6_ok_pathname,NIL,FALSE,
	    0,0));
    list_constant_38 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_default_g2v6_ok_pathname);
    record_system_variable(Qdefault_g2v6_ok_pathname,Qpathnames,
	    list_constant_38,Qnil,Qnil,Qnil,Qnil);
    Qpathname_for_disabling_g2v6_ok_command_line = 
	    STATIC_SYMBOL("PATHNAME-FOR-DISABLING-G2V6-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpathname_for_disabling_g2v6_ok_command_line,
	    Pathname_for_disabling_g2v6_ok_command_line);
    Qinitializer_for_pathname_for_disabling_g2v6_ok_command_line = 
	    STATIC_SYMBOL("INITIALIZER-FOR-PATHNAME-FOR-DISABLING-G2V6-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitializer_for_pathname_for_disabling_g2v6_ok_command_line,
	    STATIC_FUNCTION(initializer_for_pathname_for_disabling_g2v6_ok_command_line,
	    NIL,FALSE,0,0));
    list_constant_39 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitializer_for_pathname_for_disabling_g2v6_ok_command_line);
    record_system_variable(Qpathname_for_disabling_g2v6_ok_command_line,
	    Qpathnames,list_constant_39,Qnil,Qnil,Qnil,Qnil);
    array_constant_42 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)0L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)2L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)3L,(SI_Long)54L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)4L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)5L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)6L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)15L,(SI_Long)57344L);
    array_constant_43 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)0L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)3L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)7L,(SI_Long)57344L);
    Qdefault_g2v7_ok_pathname = STATIC_SYMBOL("DEFAULT-G2V7-OK-PATHNAME",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefault_g2v7_ok_pathname,
	    Default_g2v7_ok_pathname);
    Qinitialize_default_g2v7_ok_pathname = 
	    STATIC_SYMBOL("INITIALIZE-DEFAULT-G2V7-OK-PATHNAME",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_default_g2v7_ok_pathname,
	    STATIC_FUNCTION(initialize_default_g2v7_ok_pathname,NIL,FALSE,
	    0,0));
    list_constant_40 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_default_g2v7_ok_pathname);
    record_system_variable(Qdefault_g2v7_ok_pathname,Qpathnames,
	    list_constant_40,Qnil,Qnil,Qnil,Qnil);
    Qpathname_for_disabling_g2v7_ok_command_line = 
	    STATIC_SYMBOL("PATHNAME-FOR-DISABLING-G2V7-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpathname_for_disabling_g2v7_ok_command_line,
	    Pathname_for_disabling_g2v7_ok_command_line);
    Qinitializer_for_pathname_for_disabling_g2v7_ok_command_line = 
	    STATIC_SYMBOL("INITIALIZER-FOR-PATHNAME-FOR-DISABLING-G2V7-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitializer_for_pathname_for_disabling_g2v7_ok_command_line,
	    STATIC_FUNCTION(initializer_for_pathname_for_disabling_g2v7_ok_command_line,
	    NIL,FALSE,0,0));
    list_constant_41 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitializer_for_pathname_for_disabling_g2v7_ok_command_line);
    record_system_variable(Qpathname_for_disabling_g2v7_ok_command_line,
	    Qpathnames,list_constant_41,Qnil,Qnil,Qnil,Qnil);
    array_constant_44 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)0L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)2L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)3L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)4L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)5L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)6L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)15L,(SI_Long)57344L);
    array_constant_45 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)0L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)3L,(SI_Long)56L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)7L,(SI_Long)57344L);
    Qdefault_g2v8_ok_pathname = STATIC_SYMBOL("DEFAULT-G2V8-OK-PATHNAME",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefault_g2v8_ok_pathname,
	    Default_g2v8_ok_pathname);
    Qinitialize_default_g2v8_ok_pathname = 
	    STATIC_SYMBOL("INITIALIZE-DEFAULT-G2V8-OK-PATHNAME",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_default_g2v8_ok_pathname,
	    STATIC_FUNCTION(initialize_default_g2v8_ok_pathname,NIL,FALSE,
	    0,0));
    list_constant_42 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_default_g2v8_ok_pathname);
    record_system_variable(Qdefault_g2v8_ok_pathname,Qpathnames,
	    list_constant_42,Qnil,Qnil,Qnil,Qnil);
    Qpathname_for_disabling_g2v8_ok_command_line = 
	    STATIC_SYMBOL("PATHNAME-FOR-DISABLING-G2V8-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpathname_for_disabling_g2v8_ok_command_line,
	    Pathname_for_disabling_g2v8_ok_command_line);
    Qinitializer_for_pathname_for_disabling_g2v8_ok_command_line = 
	    STATIC_SYMBOL("INITIALIZER-FOR-PATHNAME-FOR-DISABLING-G2V8-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitializer_for_pathname_for_disabling_g2v8_ok_command_line,
	    STATIC_FUNCTION(initializer_for_pathname_for_disabling_g2v8_ok_command_line,
	    NIL,FALSE,0,0));
    list_constant_43 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitializer_for_pathname_for_disabling_g2v8_ok_command_line);
    record_system_variable(Qpathname_for_disabling_g2v8_ok_command_line,
	    Qpathnames,list_constant_43,Qnil,Qnil,Qnil,Qnil);
    array_constant_46 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)0L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)2L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)3L,(SI_Long)56L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)4L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)5L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)6L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_46,(SI_Long)15L,(SI_Long)57344L);
    array_constant_47 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)0L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)3L,(SI_Long)56L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)4L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_47,(SI_Long)7L,(SI_Long)57344L);
    Qdefault_g2v83_ok_pathname = STATIC_SYMBOL("DEFAULT-G2V83-OK-PATHNAME",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefault_g2v83_ok_pathname,
	    Default_g2v83_ok_pathname);
    Qinitialize_default_g2v83_ok_pathname = 
	    STATIC_SYMBOL("INITIALIZE-DEFAULT-G2V83-OK-PATHNAME",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_default_g2v83_ok_pathname,
	    STATIC_FUNCTION(initialize_default_g2v83_ok_pathname,NIL,FALSE,
	    0,0));
    list_constant_44 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_default_g2v83_ok_pathname);
    record_system_variable(Qdefault_g2v83_ok_pathname,Qpathnames,
	    list_constant_44,Qnil,Qnil,Qnil,Qnil);
    Qpathname_for_disabling_g2v83_ok_command_line = 
	    STATIC_SYMBOL("PATHNAME-FOR-DISABLING-G2V83-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpathname_for_disabling_g2v83_ok_command_line,
	    Pathname_for_disabling_g2v83_ok_command_line);
    Qinitializer_for_pathname_for_disabling_g2v83_ok_command_line = 
	    STATIC_SYMBOL("INITIALIZER-FOR-PATHNAME-FOR-DISABLING-G2V83-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitializer_for_pathname_for_disabling_g2v83_ok_command_line,
	    STATIC_FUNCTION(initializer_for_pathname_for_disabling_g2v83_ok_command_line,
	    NIL,FALSE,0,0));
    list_constant_45 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitializer_for_pathname_for_disabling_g2v83_ok_command_line);
    record_system_variable(Qpathname_for_disabling_g2v83_ok_command_line,
	    Qpathnames,list_constant_45,Qnil,Qnil,Qnil,Qnil);
    array_constant_48 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)0L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)1L,(SI_Long)56L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)2L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)4L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_48,(SI_Long)7L,(SI_Long)57344L);
    array_constant_49 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)0L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)2L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)3L,(SI_Long)56L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)4L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)5L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)6L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)7L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_49,(SI_Long)15L,(SI_Long)57344L);
    array_constant_50 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)0L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)3L,(SI_Long)57L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_50,(SI_Long)7L,(SI_Long)57344L);
    Qdefault_g2v9_ok_pathname = STATIC_SYMBOL("DEFAULT-G2V9-OK-PATHNAME",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefault_g2v9_ok_pathname,
	    Default_g2v9_ok_pathname);
    Qinitialize_default_g2v9_ok_pathname = 
	    STATIC_SYMBOL("INITIALIZE-DEFAULT-G2V9-OK-PATHNAME",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_default_g2v9_ok_pathname,
	    STATIC_FUNCTION(initialize_default_g2v9_ok_pathname,NIL,FALSE,
	    0,0));
    list_constant_46 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_default_g2v9_ok_pathname);
    record_system_variable(Qdefault_g2v9_ok_pathname,Qpathnames,
	    list_constant_46,Qnil,Qnil,Qnil,Qnil);
    Qpathname_for_disabling_g2v9_ok_command_line = 
	    STATIC_SYMBOL("PATHNAME-FOR-DISABLING-G2V9-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpathname_for_disabling_g2v9_ok_command_line,
	    Pathname_for_disabling_g2v9_ok_command_line);
    Qinitializer_for_pathname_for_disabling_g2v9_ok_command_line = 
	    STATIC_SYMBOL("INITIALIZER-FOR-PATHNAME-FOR-DISABLING-G2V9-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitializer_for_pathname_for_disabling_g2v9_ok_command_line,
	    STATIC_FUNCTION(initializer_for_pathname_for_disabling_g2v9_ok_command_line,
	    NIL,FALSE,0,0));
    list_constant_47 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitializer_for_pathname_for_disabling_g2v9_ok_command_line);
    record_system_variable(Qpathname_for_disabling_g2v9_ok_command_line,
	    Qpathnames,list_constant_47,Qnil,Qnil,Qnil,Qnil);
    array_constant_51 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)0L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)2L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)3L,(SI_Long)57L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)4L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)5L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)6L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_51,(SI_Long)15L,(SI_Long)57344L);
    array_constant_52 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)0L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)3L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)4L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_52,(SI_Long)7L,(SI_Long)57344L);
    Qdefault_g2v11_ok_pathname = STATIC_SYMBOL("DEFAULT-G2V11-OK-PATHNAME",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefault_g2v11_ok_pathname,
	    Default_g2v11_ok_pathname);
    Qinitialize_default_g2v11_ok_pathname = 
	    STATIC_SYMBOL("INITIALIZE-DEFAULT-G2V11-OK-PATHNAME",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_default_g2v11_ok_pathname,
	    STATIC_FUNCTION(initialize_default_g2v11_ok_pathname,NIL,FALSE,
	    0,0));
    list_constant_48 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_default_g2v11_ok_pathname);
    record_system_variable(Qdefault_g2v11_ok_pathname,Qpathnames,
	    list_constant_48,Qnil,Qnil,Qnil,Qnil);
    Qpathname_for_disabling_g2v11_ok_command_line = 
	    STATIC_SYMBOL("PATHNAME-FOR-DISABLING-G2V11-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpathname_for_disabling_g2v11_ok_command_line,
	    Pathname_for_disabling_g2v11_ok_command_line);
    Qinitializer_for_pathname_for_disabling_g2v11_ok_command_line = 
	    STATIC_SYMBOL("INITIALIZER-FOR-PATHNAME-FOR-DISABLING-G2V11-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitializer_for_pathname_for_disabling_g2v11_ok_command_line,
	    STATIC_FUNCTION(initializer_for_pathname_for_disabling_g2v11_ok_command_line,
	    NIL,FALSE,0,0));
    list_constant_49 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitializer_for_pathname_for_disabling_g2v11_ok_command_line);
    record_system_variable(Qpathname_for_disabling_g2v11_ok_command_line,
	    Qpathnames,list_constant_49,Qnil,Qnil,Qnil,Qnil);
    array_constant_53 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)0L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)2L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)3L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)4L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)5L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)6L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)7L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_53,(SI_Long)15L,(SI_Long)57344L);
    array_constant_54 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)0L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)3L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)4L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_54,(SI_Long)7L,(SI_Long)57344L);
    Qdefault_g2v12_ok_pathname = STATIC_SYMBOL("DEFAULT-G2V12-OK-PATHNAME",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefault_g2v12_ok_pathname,
	    Default_g2v12_ok_pathname);
    Qinitialize_default_g2v12_ok_pathname = 
	    STATIC_SYMBOL("INITIALIZE-DEFAULT-G2V12-OK-PATHNAME",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_default_g2v12_ok_pathname,
	    STATIC_FUNCTION(initialize_default_g2v12_ok_pathname,NIL,FALSE,
	    0,0));
    list_constant_50 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_default_g2v12_ok_pathname);
    record_system_variable(Qdefault_g2v12_ok_pathname,Qpathnames,
	    list_constant_50,Qnil,Qnil,Qnil,Qnil);
    Qpathname_for_disabling_g2v12_ok_command_line = 
	    STATIC_SYMBOL("PATHNAME-FOR-DISABLING-G2V12-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpathname_for_disabling_g2v12_ok_command_line,
	    Pathname_for_disabling_g2v12_ok_command_line);
    Qinitializer_for_pathname_for_disabling_g2v12_ok_command_line = 
	    STATIC_SYMBOL("INITIALIZER-FOR-PATHNAME-FOR-DISABLING-G2V12-OK-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitializer_for_pathname_for_disabling_g2v12_ok_command_line,
	    STATIC_FUNCTION(initializer_for_pathname_for_disabling_g2v12_ok_command_line,
	    NIL,FALSE,0,0));
    list_constant_51 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitializer_for_pathname_for_disabling_g2v12_ok_command_line);
    record_system_variable(Qpathname_for_disabling_g2v12_ok_command_line,
	    Qpathnames,list_constant_51,Qnil,Qnil,Qnil,Qnil);
    array_constant_55 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)0L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)2L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)3L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)4L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)5L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)6L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)7L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_55,(SI_Long)15L,(SI_Long)57344L);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_7 = STATIC_STRING("(Authorization file: ~a; Machine ID");
    string_constant_8 = STATIC_STRING("(none found)");
    string_constant_9 = STATIC_STRING(": (none found))");
    string_constant_10 = STATIC_STRING(": ~a)");
    string_constant_11 = STATIC_STRING("s:");
    string_constant_12 = STATIC_STRING("~a");
    string_constant_13 = STATIC_STRING(", ");
    string_constant_14 = STATIC_STRING(")");
    Qoffline = STATIC_SYMBOL("OFFLINE",AB_package);
    Qgsi = STATIC_SYMBOL("GSI",AB_package);
    Qgfi = STATIC_SYMBOL("GFI",AB_package);
    Qicp = STATIC_SYMBOL("ICP",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)3L,Qgsi,Qgfi,Qicp);
    Qno_valid_telewindows_ok_entry_message = 
	    STATIC_SYMBOL("NO-VALID-TELEWINDOWS-OK-ENTRY-MESSAGE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qno_valid_telewindows_ok_entry_message,
	    No_valid_telewindows_ok_entry_message);
    array_constant_85 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)1L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)2L,(SI_Long)37L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)3L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)4L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)5L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)6L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)7L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)8L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)10L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)11L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)13L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)14L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)15L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)16L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)17L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)18L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)19L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)20L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)21L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)22L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)23L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)24L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)25L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)26L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)27L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)28L,(SI_Long)126L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)30L,(SI_Long)29L);
    UBYTE_16_ISASET_1(array_constant_85,(SI_Long)31L,(SI_Long)57344L);
    string_constant_85 = 
	    STATIC_STRING("43Py4tqw3Ey3Ky3Ny3Sy3Vy3Zy3ky4l3ny4nln3py4l3hy4k4k4k4k4lo4ms3by4l3cy4nv3Jy3jy4nx3Ry3gy4n3Fy3Oy3Wy4l3dy4pu3Ly3Py3ey3iy4mt3Qy4l3ay");
    string_constant_86 = 
	    STATIC_STRING("4oy3Iy3My3fy4np3Gy3Xy4m3Cy3Yy4m3Uy3my4lz4l3Hy4lr4k4l3Dy4k4pkm3Ty3ly3oy");
    SET_SYMBOL_VALUE(Qno_valid_telewindows_ok_entry_message,
	    transform_type_specification_2(FIX((SI_Long)56L),
	    array_constant_85,
	    regenerate_optimized_constant(LIST_2(string_constant_85,
	    string_constant_86))));
    Qcannot_open_telewindows_ok_file_message = 
	    STATIC_SYMBOL("CANNOT-OPEN-TELEWINDOWS-OK-FILE-MESSAGE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcannot_open_telewindows_ok_file_message,
	    Cannot_open_telewindows_ok_file_message);
    array_constant_86 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)1L,(SI_Long)33L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)2L,(SI_Long)37L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)3L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)4L,(SI_Long)39L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)5L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)7L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)8L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)9L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)10L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)12L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)14L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)15L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)16L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)18L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)19L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)20L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)21L,(SI_Long)126L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)30L,(SI_Long)22L);
    UBYTE_16_ISASET_1(array_constant_86,(SI_Long)31L,(SI_Long)57344L);
    string_constant_87 = 
	    STATIC_STRING("43Iy4mty4l3Dy4nln3Fy4k4lr4k4lp4lo4k4k4k4lw4k4mqx4lu4lv4l3Cy4ls4k4k4k4okmz3Ey");
    SET_SYMBOL_VALUE(Qcannot_open_telewindows_ok_file_message,
	    transform_type_specification_2(FIX((SI_Long)20L),
	    array_constant_86,
	    regenerate_optimized_constant(string_constant_87)));
    Qjapanese = STATIC_SYMBOL("JAPANESE",AB_package);
    list_constant_52 = STATIC_LIST((SI_Long)2L,Qjapanese,Qjapanese);
    Qkorean = STATIC_SYMBOL("KOREAN",AB_package);
    list_constant_53 = STATIC_LIST((SI_Long)2L,Qkorean,Qkorean);
    Qchinese = STATIC_SYMBOL("CHINESE",AB_package);
    list_constant_54 = STATIC_LIST((SI_Long)2L,Qchinese,Qchinese);
    Qfloating = STATIC_SYMBOL("FLOATING",AB_package);
    list_constant_55 = STATIC_LIST((SI_Long)2L,Qfloating,Qfloating);
    Qruntime = STATIC_SYMBOL("RUNTIME",AB_package);
    Qruntime_option = STATIC_SYMBOL("RUNTIME-OPTION",AB_package);
    list_constant_56 = STATIC_LIST((SI_Long)2L,Qruntime,Qruntime_option);
    Qrestricted_use = STATIC_SYMBOL("RESTRICTED-USE",AB_package);
    Qrestricted_use_option = STATIC_SYMBOL("RESTRICTED-USE-OPTION",AB_package);
    list_constant_57 = STATIC_LIST((SI_Long)2L,Qrestricted_use,
	    Qrestricted_use_option);
    Qembedded = STATIC_SYMBOL("EMBEDDED",AB_package);
    Qembedded_option = STATIC_SYMBOL("EMBEDDED-OPTION",AB_package);
    list_constant_58 = STATIC_LIST((SI_Long)2L,Qembedded,Qembedded_option);
    list_constant_59 = STATIC_LIST((SI_Long)7L,list_constant_52,
	    list_constant_53,list_constant_54,list_constant_55,
	    list_constant_56,list_constant_57,list_constant_58);
    Telewindows_product_modules_to_select = list_constant_59;
    array_constant_56 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)3L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_56,(SI_Long)7L,(SI_Long)57344L);
    Qfrom = STATIC_SYMBOL("FROM",AB_package);
    array_constant_57 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_57,(SI_Long)7L,(SI_Long)57344L);
    Qto = STATIC_SYMBOL("TO",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)32L),
	    FIX((SI_Long)9L));
    array_constant_58 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)0L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)1L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_58,(SI_Long)7L,(SI_Long)57344L);
    list_constant_3 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)116L),
	    FIX((SI_Long)84L));
    list_constant_4 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)73L),
	    FIX((SI_Long)105L));
    array_constant_59 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)1L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)7L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_59,(SI_Long)15L,(SI_Long)57344L);
    Qdoes_not_contain_5_codes = STATIC_SYMBOL("DOES-NOT-CONTAIN-5-CODES",
	    AB_package);
    Qshunned_machine_id_string = STATIC_SYMBOL("SHUNNED-MACHINE-ID-STRING",
	    AB_package);
    string_constant_15 = 
	    STATIC_STRING("[Telewindows: unable to locate a Telewindows OK file ...]");
    string_constant_16 = 
	    STATIC_STRING("~%[Telewindows: using Telewindows OK file: ~s]");
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_gensym_pathname_g2_struct = 
	    STATIC_SYMBOL("GENSYM-PATHNAME-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    string_constant_17 = STATIC_STRING("[Telewindows: ~a]");
    string_constant_18 = 
	    STATIC_STRING("[Telewindows: no local authorization found for this machine]");
    if (Number_of_raster_oddspaces == UNBOUND)
	Number_of_raster_oddspaces = FIX((SI_Long)2L);
    Qjan = STATIC_SYMBOL("JAN",AB_package);
    Qfeb = STATIC_SYMBOL("FEB",AB_package);
    Qmar = STATIC_SYMBOL("MAR",AB_package);
    Qapr = STATIC_SYMBOL("APR",AB_package);
    Qmay = STATIC_SYMBOL("MAY",AB_package);
    Qjun = STATIC_SYMBOL("JUN",AB_package);
    Qjul = STATIC_SYMBOL("JUL",AB_package);
    Qaug = STATIC_SYMBOL("AUG",AB_package);
    Qsep = STATIC_SYMBOL("SEP",AB_package);
    Qoct = STATIC_SYMBOL("OCT",AB_package);
    Qnov = STATIC_SYMBOL("NOV",AB_package);
    Qdec = STATIC_SYMBOL("DEC",AB_package);
    list_constant_60 = STATIC_LIST((SI_Long)12L,Qjan,Qfeb,Qmar,Qapr,Qmay,
	    Qjun,Qjul,Qaug,Qsep,Qoct,Qnov,Qdec);
    Tw_months_of_the_year = list_constant_60;
    Qmap_month_to_number_code = STATIC_SYMBOL("MAP-MONTH-TO-NUMBER-CODE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmap_month_to_number_code,
	    Map_month_to_number_code);
    list_constant_61 = STATIC_CONS(FIX((SI_Long)31L),Qnil);
    list_constant_63 = STATIC_LIST_STAR((SI_Long)3L,Qjan,FIX((SI_Long)1L),
	    list_constant_61);
    list_constant_64 = STATIC_LIST((SI_Long)3L,Qfeb,FIX((SI_Long)2L),
	    FIX((SI_Long)28L));
    list_constant_65 = STATIC_LIST_STAR((SI_Long)3L,Qmar,FIX((SI_Long)3L),
	    list_constant_61);
    list_constant_62 = STATIC_CONS(FIX((SI_Long)30L),Qnil);
    list_constant_66 = STATIC_LIST_STAR((SI_Long)3L,Qapr,FIX((SI_Long)4L),
	    list_constant_62);
    list_constant_67 = STATIC_LIST_STAR((SI_Long)3L,Qmay,FIX((SI_Long)5L),
	    list_constant_61);
    list_constant_68 = STATIC_LIST_STAR((SI_Long)3L,Qjun,FIX((SI_Long)6L),
	    list_constant_62);
    list_constant_69 = STATIC_LIST_STAR((SI_Long)3L,Qjul,FIX((SI_Long)7L),
	    list_constant_61);
    list_constant_70 = STATIC_LIST_STAR((SI_Long)3L,Qaug,FIX((SI_Long)8L),
	    list_constant_61);
    list_constant_71 = STATIC_LIST_STAR((SI_Long)3L,Qsep,FIX((SI_Long)9L),
	    list_constant_62);
    list_constant_72 = STATIC_LIST_STAR((SI_Long)3L,Qoct,FIX((SI_Long)10L),
	    list_constant_61);
    list_constant_73 = STATIC_LIST_STAR((SI_Long)3L,Qnov,FIX((SI_Long)11L),
	    list_constant_62);
    list_constant_74 = STATIC_LIST_STAR((SI_Long)3L,Qdec,FIX((SI_Long)12L),
	    list_constant_61);
    list_constant_75 = STATIC_LIST((SI_Long)12L,list_constant_63,
	    list_constant_64,list_constant_65,list_constant_66,
	    list_constant_67,list_constant_68,list_constant_69,
	    list_constant_70,list_constant_71,list_constant_72,
	    list_constant_73,list_constant_74);
    SET_SYMBOL_VALUE(Qmap_month_to_number_code,list_constant_75);
    if (Icon_list_notes == UNBOUND)
	Icon_list_notes = LIST_2(Nil,list(10,Nil,Nil,Nil,Nil,Nil,Nil,Nil,
		Nil,Nil,FIX((SI_Long)0L)));
    if (Graph_allocation_factor == UNBOUND) {
	temp = CDR(Icon_list_notes);
	Graph_allocation_factor = CONS(Nil,temp);
    }
    Qclogged_count = STATIC_SYMBOL("CLOGGED-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qclogged_count,Clogged_count);
    Qtelestubs = STATIC_SYMBOL("TELESTUBS",AB_package);
    record_system_variable(Qclogged_count,Qtelestubs,FIX((SI_Long)0L),Qnil,
	    Qnil,Qnil,Qnil);
    if (Telewindows_screen_utilization == UNBOUND)
	Telewindows_screen_utilization = LIST_2(Nil,Nil);
    Qtime_of_last_expiration_check = 
	    STATIC_SYMBOL("TIME-OF-LAST-EXPIRATION-CHECK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtime_of_last_expiration_check,
	    Time_of_last_expiration_check);
    Qtelewindows = STATIC_SYMBOL("TELEWINDOWS",AB_package);
    Qget_fixnum_time_function = STATIC_SYMBOL("GET-FIXNUM-TIME-FUNCTION",
	    AB_package);
    list_constant_76 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qget_fixnum_time_function);
    record_system_variable(Qtime_of_last_expiration_check,Qtelewindows,
	    list_constant_76,Qnil,Qnil,Qnil,Qnil);
    Qtw_expiration_check_interval = 
	    STATIC_SYMBOL("TW-EXPIRATION-CHECK-INTERVAL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtw_expiration_check_interval,
	    Tw_expiration_check_interval);
    Qfixnum_time_interval = STATIC_SYMBOL("FIXNUM-TIME-INTERVAL",AB_package);
    list_constant_77 = STATIC_LIST((SI_Long)3L,Kfuncall,
	    Qfixnum_time_interval,FIX((SI_Long)100000L));
    record_system_variable(Qtw_expiration_check_interval,Qtelewindows,
	    list_constant_77,Qnil,Qnil,Qnil,Qnil);
    Qtw_expiration = STATIC_SYMBOL("TW-EXPIRATION",AB_package);
    if (Reclaimed_telewindows_boxes == UNBOUND) {
	temp = CDR(Telewindows_screen_utilization);
	Reclaimed_telewindows_boxes = CONS(Nil,temp);
    }
    string_constant_19 = STATIC_STRING("~a~a");
    Qtoo_late_telewindows_authorization_message = 
	    STATIC_SYMBOL("TOO-LATE-TELEWINDOWS-AUTHORIZATION-MESSAGE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtoo_late_telewindows_authorization_message,
	    Too_late_telewindows_authorization_message);
    array_constant_87 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)1L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)2L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)3L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)4L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)5L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)7L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)8L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)9L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)11L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)12L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)14L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)15L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)16L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)18L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)19L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)20L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)21L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)22L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)23L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)24L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)30L,(SI_Long)25L);
    UBYTE_16_ISASET_1(array_constant_87,(SI_Long)31L,(SI_Long)57344L);
    string_constant_88 = 
	    STATIC_STRING("43Ly4un3Dy3Hy3My3Uy3Yy3cy3hy3ny3ty4k4k4k4k4lk4pow3Oy3Wy3jy4l3dy4m3Py3ry4l3my4pm3Ty3ey3fy3sy4l3Ey4plr3Jy3Qy3Vy4quy3Ky3Ry3ly3py4l3");
    string_constant_89 = 
	    STATIC_STRING("ky4l3Ny4p3Cy3Sy3Zy3gy3qy4osz3Fy3ay4mt3Gy4n3Ly3Xy3oy4oqx3Iy3by4lp4l3iy4k4lv");
    SET_SYMBOL_VALUE(Qtoo_late_telewindows_authorization_message,
	    transform_type_specification_2(FIX((SI_Long)60L),
	    array_constant_87,
	    regenerate_optimized_constant(LIST_2(string_constant_88,
	    string_constant_89))));
    Qtoo_early_telewindows_authorization_message = 
	    STATIC_SYMBOL("TOO-EARLY-TELEWINDOWS-AUTHORIZATION-MESSAGE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtoo_early_telewindows_authorization_message,
	    Too_early_telewindows_authorization_message);
    array_constant_88 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)1L,(SI_Long)49L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)2L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)3L,(SI_Long)53L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)4L,(SI_Long)55L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)5L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)7L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)8L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)9L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)11L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)12L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)13L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)14L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)15L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)16L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)18L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)19L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)20L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)21L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)22L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)23L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)24L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)25L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)30L,(SI_Long)26L);
    UBYTE_16_ISASET_1(array_constant_88,(SI_Long)31L,(SI_Long)57344L);
    string_constant_90 = 
	    STATIC_STRING("43My4un3Dy3Hy3My3Uy3Zy3dy3gy3my3sy4k4k4k4k4lk4oow3Oy3iy4l3ey4l3Py4l3ly4nm3Ty3fy4olr3Jy3Qy4ruy3Ky3Ry3Wy3ky3qy4o3Xy3Yy3jy3ry4l3Ey4");
    string_constant_91 = 
	    STATIC_STRING("l3Ny4o3Cy3Sy3ay3oy4osz3Fy3by4mt3Gy4l3Ly4pqx3Iy3cy3py4mp3ny4l3hy4l3Vy4k4lv");
    SET_SYMBOL_VALUE(Qtoo_early_telewindows_authorization_message,
	    transform_type_specification_2(FIX((SI_Long)59L),
	    array_constant_88,
	    regenerate_optimized_constant(LIST_2(string_constant_90,
	    string_constant_91))));
    Qcannot_register_process = STATIC_SYMBOL("CANNOT-REGISTER-PROCESS",
	    AB_package);
    Qprocess_count_exceeded = STATIC_SYMBOL("PROCESS-COUNT-EXCEEDED",
	    AB_package);
    Qtelewindows_authorized_products = 
	    STATIC_SYMBOL("TELEWINDOWS-AUTHORIZED-PRODUCTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtelewindows_authorized_products,
	    Telewindows_authorized_products);
    record_system_variable(Qtelewindows_authorized_products,Qsequences1,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qtelewindows_license_level = STATIC_SYMBOL("TELEWINDOWS-LICENSE-LEVEL",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtelewindows_license_level,
	    Telewindows_license_level);
    record_system_variable(Qtelewindows_license_level,Qsequences1,
	    FIX((SI_Long)-1L),Qnil,Qnil,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qtelewindows_license_level,
	    STATIC_FUNCTION(telewindows_license_level,NIL,FALSE,1,1));
    Qunauthorized = STATIC_SYMBOL("UNAUTHORIZED",AB_package);
    Qdevelopment = STATIC_SYMBOL("DEVELOPMENT",AB_package);
    string_constant_20 = 
	    STATIC_STRING("~%[Telewindows: will attempt to connect using a Floating Telewindows authorization ...]~%");
    string_constant_21 = 
	    STATIC_STRING("[Telewindows: entry for machine ID ~s incorrect.]");
    string_constant_22 = 
	    STATIC_STRING("[Telewindows: will attempt to connect using a Floating Telewindows authorization ...]");
    string_constant_23 = 
	    STATIC_STRING("~%[Telewindows: ~a~a; will attempt to connect using a Floating Telewindows authorization ...]~%");
    string_constant_24 = STATIC_STRING("Jan");
    string_constant_25 = STATIC_STRING("Feb");
    string_constant_26 = STATIC_STRING("Mar");
    string_constant_27 = STATIC_STRING("Apr");
    string_constant_28 = STATIC_STRING("May");
    string_constant_29 = STATIC_STRING("Jun");
    string_constant_30 = STATIC_STRING("Jul");
    string_constant_31 = STATIC_STRING("Aug");
    string_constant_32 = STATIC_STRING("Sep");
    string_constant_33 = STATIC_STRING("Oct");
    string_constant_34 = STATIC_STRING("Nov");
    string_constant_35 = STATIC_STRING("Dec");
    string_constant_36 = STATIC_STRING("~d ~a ~d");
    Qdefault_text_string_hash_modulus = 
	    STATIC_SYMBOL("DEFAULT-TEXT-STRING-HASH-MODULUS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefault_text_string_hash_modulus,
	    Default_text_string_hash_modulus);
    SET_SYMBOL_VALUE(Qdefault_text_string_hash_modulus,
	    FIX((IFIX(Most_positive_fixnum) >>  -  - (SI_Long)1L) - 
	    (SI_Long)1L));
    array_constant_60 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)0L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)1L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)4L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_60,(SI_Long)7L,(SI_Long)57344L);
    array_constant_61 = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)0L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)1L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)5L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)8L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)9L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_61,(SI_Long)15L,(SI_Long)57344L);
    string_constant_37 = STATIC_STRING("0~x");
    string_constant_38 = STATIC_STRING("~x");
}
