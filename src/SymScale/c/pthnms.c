/* pthnms.c
 * Input file:  pathnames.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "pthnms.h"


DEFINE_VARIABLE_WITH_SYMBOL(Available_path_conses, Qavailable_path_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_path_conses_tail, Qavailable_path_conses_tail);

Object Available_path_conses_vector = UNBOUND;

Object Available_path_conses_tail_vector = UNBOUND;

Object Path_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Path_cons_counter, Qpath_cons_counter);

/* OUTSTANDING-PATH-CONSES */
Object outstanding_path_conses()
{
    Object temp;

    x_note_fn_call(39,0);
    temp = FIXNUM_MINUS(Path_cons_counter,length(Available_path_conses));
    return VALUES_1(temp);
}

/* PATH-CONS-MEMORY-USAGE */
Object path_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(39,1);
    temp = FIXNUM_TIMES(Path_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-PATH-CONS-POOL */
Object replenish_path_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(39,2);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qpath_cons_counter,Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_path_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_path_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_path_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_path_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_path_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Path_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qpath;               /* path */

/* PATH-CONS-1 */
Object path_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(39,3);
    new_cons = ISVREF(Available_path_conses_vector,IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_path_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_path_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_path_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_path_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qpath);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-PATH-LIST-POOL */
Object replenish_path_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(39,4);
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
    if (ISVREF(Available_path_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_path_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_path_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_path_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_path_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qpath_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-PATH-LIST-1 */
Object make_path_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(39,5);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_path_conses_vector,
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
	replenish_path_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_path_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qpath);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_path_conses_vector,IFIX(Current_thread_index));
	svref_arg_1 = Available_path_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_path_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_path_conses_tail_vector;
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

/* PATH-LIST-2 */
Object path_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(39,6);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_path_conses_vector,IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_path_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_path_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qpath);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_path_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_path_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_path_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_path_conses_tail_vector;
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

/* PATH-LIST-3 */
Object path_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(39,7);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_path_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_path_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_path_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qpath);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_path_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_path_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_path_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_path_conses_tail_vector;
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

/* PATH-LIST-4 */
Object path_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(39,8);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_path_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_path_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_path_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qpath);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_path_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_path_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_path_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_path_conses_tail_vector;
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

/* PATH-LIST-TRACE-HOOK */
Object path_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(39,9);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-PATH-CONSES-1 */
Object copy_tree_using_path_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(39,10);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_path_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_path_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_path_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_path_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_path_cons_pool();
	temp_1 = copy_tree_using_path_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qpath);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_path_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_path_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_path_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_path_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_path_cons_pool();
	temp_1 = copy_tree_using_path_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qpath);
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

/* COPY-LIST-USING-PATH-CONSES-1 */
Object copy_list_using_path_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(39,11);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_path_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_path_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_path_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_path_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_path_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qpath);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_path_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_path_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_path_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_path_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_path_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qpath);
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

/* RECLAIM-PATH-CONS-1 */
Object reclaim_path_cons_1(path_cons)
    Object path_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(39,12);
    inline_note_reclaim_cons(path_cons,Qpath);
    if (ISVREF(Available_path_conses_tail_vector,IFIX(Current_thread_index))) {
	temp = ISVREF(Available_path_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = path_cons;
	temp = Available_path_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = path_cons;
    }
    else {
	temp = Available_path_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = path_cons;
	temp = Available_path_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = path_cons;
    }
    M_CDR(path_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-PATH-LIST-1 */
Object reclaim_path_list_1(path_list)
    Object path_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(39,13);
    if (path_list) {
	last_1 = path_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qpath);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qpath);
	if (ISVREF(Available_path_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_path_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = path_list;
	    temp = Available_path_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_path_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = path_list;
	    temp = Available_path_conses_tail_vector;
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

/* RECLAIM-PATH-LIST*-1 */
Object reclaim_path_list_star_1(path_list)
    Object path_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(39,14);
    if (CONSP(path_list)) {
	temp = last(path_list,_);
	M_CDR(temp) = Nil;
	if (path_list) {
	    last_1 = path_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qpath);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qpath);
	    if (ISVREF(Available_path_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_path_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = path_list;
		temp = Available_path_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_path_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = path_list;
		temp = Available_path_conses_tail_vector;
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

/* RECLAIM-PATH-TREE-1 */
Object reclaim_path_tree_1(tree)
    Object tree;
{
    Object e, e2, path_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(39,15);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_path_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		path_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(path_cons,Qpath);
		if (EQ(path_cons,e))
		    goto end_1;
		else if ( !TRUEP(path_cons))
		    goto end_1;
		else
		    path_cons = CDR(path_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_path_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_path_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_path_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_path_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_path_conses_tail_vector;
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

/* DELETE-PATH-ELEMENT-1 */
Object delete_path_element_1(element,path_list)
    Object element, path_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(39,16);
    if (path_list) {
	if (EQ(element,M_CAR(path_list))) {
	    temp = CDR(path_list);
	    inline_note_reclaim_cons(path_list,Qpath);
	    if (ISVREF(Available_path_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_path_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = path_list;
		temp_1 = Available_path_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = path_list;
	    }
	    else {
		temp_1 = Available_path_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = path_list;
		temp_1 = Available_path_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = path_list;
	    }
	    M_CDR(path_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = path_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qpath);
		if (ISVREF(Available_path_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_path_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_path_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_path_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_path_conses_tail_vector;
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
	    temp = path_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-PATH-CONS-1 */
Object delete_path_cons_1(path_cons,path_list)
    Object path_cons, path_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(39,17);
    if (EQ(path_cons,path_list))
	temp = CDR(path_list);
    else {
	l_trailer_qm = Nil;
	l = path_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,path_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = path_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_path_cons_1(path_cons);
    return VALUES_1(temp);
}

static Object Qunix;               /* unix */

static Object Qvms;                /* vms */

static Object Qdos;                /* dos */

static Object Qwin32;              /* win32 */

/* INITIALIZE-LOCAL-FILE-SYSTEM */
Object initialize_local_file_system()
{
    x_note_fn_call(39,18);
    if (EQ(G2_operating_system,Qunix))
	return VALUES_1(Qunix);
    else if (EQ(G2_operating_system,Qvms))
	return VALUES_1(Qvms);
    else if (EQ(G2_operating_system,Qdos))
	return VALUES_1(Qdos);
    else if (EQ(G2_operating_system,Qwin32))
	return VALUES_1(Qwin32);
    else
	return VALUES_1(Qunix);
}

DEFINE_VARIABLE_WITH_SYMBOL(Local_file_system, Qlocal_file_system);

static Object Qparse_unix_filename;  /* parse-unix-filename */

static Object Qparse_vms_filename;  /* parse-vms-filename */

static Object Qparse_dos_filename;  /* parse-dos-filename */

static Object Qparse_win32_filename;  /* parse-win32-filename */

/* INITIALIZE-LOCAL-FILENAME-PARSER */
Object initialize_local_filename_parser()
{
    x_note_fn_call(39,19);
    if (EQ(G2_operating_system,Qunix))
	return VALUES_1(Qparse_unix_filename);
    else if (EQ(G2_operating_system,Qvms))
	return VALUES_1(Qparse_vms_filename);
    else if (EQ(G2_operating_system,Qdos))
	return VALUES_1(Qparse_dos_filename);
    else if (EQ(G2_operating_system,Qwin32))
	return VALUES_1(Qparse_win32_filename);
    else
	return VALUES_1(Qparse_unix_filename);
}

DEFINE_VARIABLE_WITH_SYMBOL(Local_filename_parser, Qlocal_filename_parser);

static Object Qgenerate_unix_namestring;  /* generate-unix-namestring */

static Object Qgenerate_vms_namestring;  /* generate-vms-namestring */

static Object Qgenerate_dos_namestring;  /* generate-dos-namestring */

static Object Qgenerate_win32_namestring;  /* generate-win32-namestring */

/* INITIALIZE-LOCAL-NAMESTRING-GENERATOR */
Object initialize_local_namestring_generator()
{
    x_note_fn_call(39,20);
    if (EQ(G2_operating_system,Qunix))
	return VALUES_1(Qgenerate_unix_namestring);
    else if (EQ(G2_operating_system,Qvms))
	return VALUES_1(Qgenerate_vms_namestring);
    else if (EQ(G2_operating_system,Qdos))
	return VALUES_1(Qgenerate_dos_namestring);
    else if (EQ(G2_operating_system,Qwin32))
	return VALUES_1(Qgenerate_win32_namestring);
    else
	return VALUES_1(Qgenerate_unix_namestring);
}

DEFINE_VARIABLE_WITH_SYMBOL(Local_namestring_generator, Qlocal_namestring_generator);

Object Convert_file_strings_to_uppercase_p_prop = UNBOUND;

/* INITIALIZE-CONVERT-FILE-STRINGS-TO-UPPERCASE-P */
Object initialize_convert_file_strings_to_uppercase_p()
{
    x_note_fn_call(39,21);
    if (EQ(Local_file_system,Qunix))
	return VALUES_1(Nil);
    else if (EQ(Local_file_system,Qvms))
	return VALUES_1(T);
    else if (EQ(Local_file_system,Qdos))
	return VALUES_1(T);
    else if (EQ(Local_file_system,Qwin32))
	return VALUES_1(Nil);
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Convert_file_strings_to_uppercase_p, Qconvert_file_strings_to_uppercase_p);

Object The_type_description_of_gensym_pathname = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_gensym_pathnames, Qchain_of_available_gensym_pathnames);

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_pathname_count, Qgensym_pathname_count);

Object Chain_of_available_gensym_pathnames_vector = UNBOUND;

/* GENSYM-PATHNAME-STRUCTURE-MEMORY-USAGE */
Object gensym_pathname_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(39,22);
    temp = Gensym_pathname_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)11L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-GENSYM-PATHNAME-COUNT */
Object outstanding_gensym_pathname_count()
{
    Object def_structure_gensym_pathname_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(39,23);
    gensymed_symbol = IFIX(Gensym_pathname_count);
    def_structure_gensym_pathname_variable = 
	    Chain_of_available_gensym_pathnames;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_gensym_pathname_variable))
	goto end_loop;
    def_structure_gensym_pathname_variable = 
	    ISVREF(def_structure_gensym_pathname_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-GENSYM-PATHNAME-STRUCTURE-MACRO-1 */
Object reclaim_gensym_pathname_structure_macro_1(gensym_pathname_1)
    Object gensym_pathname_1;
{
    Object temp, svref_arg_2;

    x_note_fn_call(39,24);
    inline_note_reclaim_cons(gensym_pathname_1,Nil);
    temp = ISVREF(Chain_of_available_gensym_pathnames_vector,
	    IFIX(Current_thread_index));
    SVREF(gensym_pathname_1,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_gensym_pathnames_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = gensym_pathname_1;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GENSYM-PATHNAME */
Object reclaim_structure_for_gensym_pathname(gensym_pathname_1)
    Object gensym_pathname_1;
{
    x_note_fn_call(39,25);
    return reclaim_gensym_pathname_structure_macro_1(gensym_pathname_1);
}

static Object Qg2_defstruct_structure_name_gensym_pathname_g2_struct;  /* g2-defstruct-structure-name::gensym-pathname-g2-struct */

/* MAKE-PERMANENT-GENSYM-PATHNAME-STRUCTURE-INTERNAL */
Object make_permanent_gensym_pathname_structure_internal()
{
    Object def_structure_gensym_pathname_variable;
    Object defstruct_g2_gensym_pathname_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(39,26);
    def_structure_gensym_pathname_variable = Nil;
    atomic_incff_symval(Qgensym_pathname_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_gensym_pathname_variable = Nil;
	gensymed_symbol = (SI_Long)11L;
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
	defstruct_g2_gensym_pathname_variable = the_array;
	SVREF(defstruct_g2_gensym_pathname_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gensym_pathname_g2_struct;
	def_structure_gensym_pathname_variable = 
		defstruct_g2_gensym_pathname_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_gensym_pathname_variable);
}

/* MAKE-GENSYM-PATHNAME-STRUCTURE-MACRO-1 */
Object make_gensym_pathname_structure_macro_1(gensym_pathname_host,
	    gensym_pathname_device,gensym_pathname_directory,
	    gensym_pathname_name,gensym_pathname_type,gensym_pathname_version)
    Object gensym_pathname_host, gensym_pathname_device;
    Object gensym_pathname_directory, gensym_pathname_name;
    Object gensym_pathname_type, gensym_pathname_version;
{
    Object def_structure_gensym_pathname_variable, temp, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(39,27);
    def_structure_gensym_pathname_variable = 
	    ISVREF(Chain_of_available_gensym_pathnames_vector,
	    IFIX(Current_thread_index));
    if (def_structure_gensym_pathname_variable) {
	temp = Chain_of_available_gensym_pathnames_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_gensym_pathname_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_gensym_pathname_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gensym_pathname_g2_struct;
    }
    else
	def_structure_gensym_pathname_variable = 
		make_permanent_gensym_pathname_structure_internal();
    inline_note_allocate_cons(def_structure_gensym_pathname_variable,Nil);
    SVREF(def_structure_gensym_pathname_variable,FIX((SI_Long)1L)) = 
	    gensym_pathname_host;
    SVREF(def_structure_gensym_pathname_variable,FIX((SI_Long)2L)) = 
	    gensym_pathname_device;
    SVREF(def_structure_gensym_pathname_variable,FIX((SI_Long)3L)) = 
	    gensym_pathname_directory;
    SVREF(def_structure_gensym_pathname_variable,FIX((SI_Long)4L)) = 
	    gensym_pathname_name;
    SVREF(def_structure_gensym_pathname_variable,FIX((SI_Long)5L)) = 
	    gensym_pathname_type;
    SVREF(def_structure_gensym_pathname_variable,FIX((SI_Long)6L)) = 
	    gensym_pathname_version;
    SVREF(def_structure_gensym_pathname_variable,FIX((SI_Long)7L)) = Nil;
    temp = Local_file_system;
    SVREF(def_structure_gensym_pathname_variable,FIX((SI_Long)8L)) = temp;
    temp = Local_filename_parser;
    SVREF(def_structure_gensym_pathname_variable,FIX((SI_Long)9L)) = temp;
    temp = Local_namestring_generator;
    SVREF(def_structure_gensym_pathname_variable,FIX((SI_Long)10L)) = temp;
    return VALUES_1(def_structure_gensym_pathname_variable);
}

/* MAKE-GENSYM-PATHNAME-STRUCTURE-FUNCTION */
Object make_gensym_pathname_structure_function(gensym_pathname_host,
	    gensym_pathname_device,gensym_pathname_directory,
	    gensym_pathname_name,gensym_pathname_type,gensym_pathname_version)
    Object gensym_pathname_host, gensym_pathname_device;
    Object gensym_pathname_directory, gensym_pathname_name;
    Object gensym_pathname_type, gensym_pathname_version;
{
    x_note_fn_call(39,28);
    return make_gensym_pathname_structure_macro_1(gensym_pathname_host,
	    gensym_pathname_device,gensym_pathname_directory,
	    gensym_pathname_name,gensym_pathname_type,gensym_pathname_version);
}

/* MAKE-EMPTY-GENSYM-PATHNAME */
Object make_empty_gensym_pathname()
{
    Object temp;

    x_note_fn_call(39,29);
    temp = make_gensym_pathname_structure_macro_1(Nil,Nil,Nil,Nil,Nil,Nil);
    return VALUES_1(temp);
}

static Object list_constant;       /* # */

/* INITIALIZE-DEFAULT-GENSYM-PATHNAME-DEFAULTS */
Object initialize_default_gensym_pathname_defaults()
{
    Object defaults, svref_new_value;

    x_note_fn_call(39,30);
    defaults = make_gensym_pathname_structure_function(Nil,Nil,
	    list_constant,Nil,Nil,Knewest);
    svref_new_value = Local_file_system;
    SVREF(defaults,FIX((SI_Long)8L)) = svref_new_value;
    svref_new_value = Local_filename_parser;
    SVREF(defaults,FIX((SI_Long)9L)) = svref_new_value;
    svref_new_value = Local_namestring_generator;
    SVREF(defaults,FIX((SI_Long)10L)) = svref_new_value;
    return VALUES_1(defaults);
}

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_default_pathname_defaults, Qgensym_default_pathname_defaults);

/* RECLAIM-PATHNAME-OR-STRING */
Object reclaim_pathname_or_string(pathname_var)
    Object pathname_var;
{
    x_note_fn_call(39,31);
    if ( !TRUEP(pathname_var))
	return VALUES_1(Nil);
    else if (SIMPLE_VECTOR_P(pathname_var) && EQ(ISVREF(pathname_var,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct))
	return reclaim_gensym_pathname(pathname_var);
    else if (text_string_p(pathname_var))
	return reclaim_text_string(pathname_var);
    else
	return VALUES_1(Qnil);
}

static Object string_constant;     /* "RclmGsmPthnm" */

/* RECLAIM-GENSYM-PATHNAME */
Object reclaim_gensym_pathname(pathname_1)
    Object pathname_1;
{
    Object current_custom_reclamation_stamp_qm, gensym_pathname_host;
    Object gensym_pathname_device, gensym_pathname_directory;
    Object gensym_pathname_name, gensym_pathname_type, gensym_pathname_version;
    Object directory_component, ab_loop_list_;
    Declare_special(1);
    Object result;

    x_note_fn_call(39,32);
    current_custom_reclamation_stamp_qm = string_constant;
    PUSH_SPECIAL_WITH_SYMBOL(Current_custom_reclamation_stamp_qm,Qcurrent_custom_reclamation_stamp_qm,current_custom_reclamation_stamp_qm,
	    0);
      gensym_pathname_host = ISVREF(pathname_1,(SI_Long)1L);
      gensym_pathname_device = ISVREF(pathname_1,(SI_Long)2L);
      gensym_pathname_directory = ISVREF(pathname_1,(SI_Long)3L);
      gensym_pathname_name = ISVREF(pathname_1,(SI_Long)4L);
      gensym_pathname_type = ISVREF(pathname_1,(SI_Long)5L);
      gensym_pathname_version = ISVREF(pathname_1,(SI_Long)6L);
      if (text_string_p(gensym_pathname_host))
	  reclaim_text_string(gensym_pathname_host);
      if (text_string_p(gensym_pathname_device))
	  reclaim_text_string(gensym_pathname_device);
      if (CONSP(gensym_pathname_directory)) {
	  directory_component = Nil;
	  ab_loop_list_ = gensym_pathname_directory;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  directory_component = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if (text_string_p(directory_component))
	      reclaim_text_string(directory_component);
	  goto next_loop;
	end_loop:
	  reclaim_path_list_1(gensym_pathname_directory);
      }
      if (text_string_p(gensym_pathname_name))
	  reclaim_text_string(gensym_pathname_name);
      if (text_string_p(gensym_pathname_type))
	  reclaim_text_string(gensym_pathname_type);
      if (text_string_p(gensym_pathname_version))
	  reclaim_text_string(gensym_pathname_version);
      result = reclaim_gensym_pathname_structure_macro_1(pathname_1);
    POP_SPECIAL();
    return result;
}

/* RECLAIM-IF-GENSYM-PATHNAME */
Object reclaim_if_gensym_pathname(pathname_qm)
    Object pathname_qm;
{
    Object temp;

    x_note_fn_call(39,33);
    temp = pathname_qm ? reclaim_gensym_pathname(pathname_qm) : Nil;
    return VALUES_1(temp);
}

/* RECLAIM-PATHNAME-COMPONENTS */
Object reclaim_pathname_components varargs_1(int, n)
{
    Object host, device, directory_1, name, type, version, directory_item;
    Object ab_loop_list_;
    Declare_varargs_nonrelocating;

    x_note_fn_call(39,34);
    INIT_ARGS_nonrelocating();
    host = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    device = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    directory_1 = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    name = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    type = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    version = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (text_string_p(host))
	reclaim_text_string(host);
    if (text_string_p(device))
	reclaim_text_string(device);
    directory_item = Nil;
    ab_loop_list_ = directory_1;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    directory_item = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (text_string_p(directory_item))
	reclaim_text_string(directory_item);
    goto next_loop;
  end_loop:
    reclaim_path_list_1(directory_1);
    if (text_string_p(name))
	reclaim_text_string(name);
    if (text_string_p(type))
	reclaim_text_string(type);
    if (text_string_p(version))
	return reclaim_text_string(version);
    else
	return VALUES_1(Nil);
}

/* PRINT-GENSYM-PATHNAME */
Object print_gensym_pathname(pathname_qm)
    Object pathname_qm;
{
    Object gensym_pathname_host, gensym_pathname_device;
    Object gensym_pathname_directory, gensym_pathname_name;
    Object gensym_pathname_type, gensym_pathname_version;

    x_note_fn_call(39,35);
    if (SIMPLE_VECTOR_P(pathname_qm) && EQ(ISVREF(pathname_qm,(SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct)) {
	gensym_pathname_host = ISVREF(pathname_qm,(SI_Long)1L);
	gensym_pathname_device = ISVREF(pathname_qm,(SI_Long)2L);
	gensym_pathname_directory = ISVREF(pathname_qm,(SI_Long)3L);
	gensym_pathname_name = ISVREF(pathname_qm,(SI_Long)4L);
	gensym_pathname_type = ISVREF(pathname_qm,(SI_Long)5L);
	gensym_pathname_version = ISVREF(pathname_qm,(SI_Long)6L);
	format((SI_Long)3L,T,"~&~a pathname -~%",ISVREF(pathname_qm,
		(SI_Long)8L));
	format((SI_Long)3L,T,"~&     host: ~s~%",gensym_pathname_host);
	format((SI_Long)3L,T,"~&   device: ~s~%",gensym_pathname_device);
	format((SI_Long)3L,T,"~&directory: ~s~%",gensym_pathname_directory);
	format((SI_Long)3L,T,"~&     name: ~s~%",gensym_pathname_name);
	format((SI_Long)3L,T,"~&     type: ~s~%",gensym_pathname_type);
	return format((SI_Long)3L,T,"~&  version: ~s~%",
		gensym_pathname_version);
    }
    else
	return format((SI_Long)3L,T,"~&not a gensym-pathname: ~s~%",
		pathname_qm);
}

Object File_systems_which_distinguish_by_version = UNBOUND;

/* PATHNAME-DISTINGUISHED-BY-VERSION-P */
Object pathname_distinguished_by_version_p(pathname_1)
    Object pathname_1;
{
    x_note_fn_call(39,36);
    if (SIMPLE_VECTOR_P(pathname_1) && EQ(ISVREF(pathname_1,(SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct)) {
	if (memq_function(ISVREF(pathname_1,(SI_Long)8L),
		File_systems_which_distinguish_by_version))
	    return VALUES_2(T,T);
	else
	    return VALUES_2(Nil,T);
    }
    else
	return VALUES_2(Nil,Nil);
}

Object File_systems_which_store_device_names = UNBOUND;

/* PATHNAME-CAN-CONTAIN-DEVICE-P */
Object pathname_can_contain_device_p(pathname_1)
    Object pathname_1;
{
    x_note_fn_call(39,37);
    if (SIMPLE_VECTOR_P(pathname_1) && EQ(ISVREF(pathname_1,(SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct)) {
	if (memq_function(ISVREF(pathname_1,(SI_Long)8L),
		File_systems_which_store_device_names))
	    return VALUES_2(T,T);
	else
	    return VALUES_2(Nil,T);
    }
    else
	return VALUES_2(Nil,Nil);
}

/* GET-DEFAULT-FILE-SYSTEM-INFO */
Object get_default_file_system_info()
{
    x_note_fn_call(39,38);
    return VALUES_3(Local_filename_parser,Local_namestring_generator,
	    Local_file_system);
}

/* GENSYM-MAKE-PATHNAME-WITHOUT-COPYING */
Object gensym_make_pathname_without_copying varargs_1(int, n)
{
    Object host, device, directory_1, name, type, version;
    Object defaults, undefaulted_pathname, temp, temp_1, temp_2;
    Object filename_parser, namestring_generator, file_system;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(39,39);
    INIT_ARGS_nonrelocating();
    host = REQUIRED_ARG_nonrelocating();
    device = REQUIRED_ARG_nonrelocating();
    directory_1 = REQUIRED_ARG_nonrelocating();
    name = REQUIRED_ARG_nonrelocating();
    type = REQUIRED_ARG_nonrelocating();
    version = REQUIRED_ARG_nonrelocating();
    defaults = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    undefaulted_pathname = make_gensym_pathname_structure_function(host,
	    device,directory_1,name,type,version);
    if (host && text_string_p(host))
	result = get_parser_from_namestring(host);
    else if (defaults && SIMPLE_VECTOR_P(defaults) && EQ(ISVREF(defaults,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct)) {
	temp = ISVREF(defaults,(SI_Long)9L);
	temp_1 = ISVREF(defaults,(SI_Long)10L);
	temp_2 = ISVREF(defaults,(SI_Long)8L);
	result = VALUES_3(temp,temp_1,temp_2);
    }
    else if (defaults && text_string_p(defaults))
	result = get_parser_from_namestring(defaults);
    else
	result = get_default_file_system_info();
    MVS_3(result,filename_parser,namestring_generator,file_system);
    SVREF(undefaulted_pathname,FIX((SI_Long)9L)) = filename_parser;
    SVREF(undefaulted_pathname,FIX((SI_Long)10L)) = namestring_generator;
    SVREF(undefaulted_pathname,FIX((SI_Long)8L)) = file_system;
    if (defaults) {
	temp_2 = gensym_merge_pathnames_function(undefaulted_pathname,
		defaults,Nil);
	reclaim_gensym_pathname(undefaulted_pathname);
	return VALUES_1(temp_2);
    }
    else
	return VALUES_1(undefaulted_pathname);
}

/* COPY-DIRECTORY-COMPONENTS-FROM-DIRECTORY-STRING */
Object copy_directory_components_from_directory_string(directory_string)
    Object directory_string;
{
    Object raw_directory_pathname_qm, directory_pathname_qm;
    Object directory_component, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2;

    x_note_fn_call(39,40);
    raw_directory_pathname_qm = gensym_pathname(directory_string);
    if ( !TRUEP(raw_directory_pathname_qm))
	return VALUES_1(Nil);
    else if (ISVREF(raw_directory_pathname_qm,(SI_Long)4L)) {
	directory_pathname_qm = 
		gensym_file_as_directory(raw_directory_pathname_qm);
	if (directory_pathname_qm) {
	    directory_component = Nil;
	    ab_loop_list_ = ISVREF(directory_pathname_qm,(SI_Long)3L);
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    directory_component = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loopvar__2 = 
		    path_cons_1(copy_pathname_contents(directory_component),
		    Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop;
	  end_loop:
	    reclaim_gensym_pathname(directory_pathname_qm);
	    reclaim_gensym_pathname(raw_directory_pathname_qm);
	    return VALUES_1(ab_loopvar_);
	    return VALUES_1(Qnil);
	}
	else {
	    directory_component = Nil;
	    ab_loop_list_ = ISVREF(raw_directory_pathname_qm,(SI_Long)3L);
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    directory_component = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loopvar__2 = 
		    path_cons_1(copy_pathname_contents(directory_component),
		    Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop_1;
	  end_loop_1:
	    reclaim_gensym_pathname(raw_directory_pathname_qm);
	    return VALUES_1(ab_loopvar_);
	    return VALUES_1(Qnil);
	}
    }
    else {
	directory_component = Nil;
	ab_loop_list_ = ISVREF(raw_directory_pathname_qm,(SI_Long)3L);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	directory_component = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = 
		path_cons_1(copy_pathname_contents(directory_component),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_2;
      end_loop_2:
	reclaim_gensym_pathname(raw_directory_pathname_qm);
	return VALUES_1(ab_loopvar_);
	return VALUES_1(Qnil);
    }
}

/* GENSYM-MAKE-PATHNAME-WITH-COPIED-COMPONENTS */
Object gensym_make_pathname_with_copied_components(host,device,directory_1,
	    name,type,version,defaults)
    Object host, device, directory_1, name, type, version, defaults;
{
    Object gensymed_symbol, convert_file_strings_to_uppercase_p;
    Object directory_component, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2;
    Declare_special(1);
    Object result;

    x_note_fn_call(39,41);
    if (host && text_string_p(host)) {
	result = get_parser_from_namestring(host);
	gensymed_symbol = NTH_VALUE((SI_Long)2L, result);
	convert_file_strings_to_uppercase_p = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qconvert_file_strings_to_uppercase_p);
    }
    else if (defaults && SIMPLE_VECTOR_P(defaults) && EQ(ISVREF(defaults,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct)) {
	gensymed_symbol = ISVREF(defaults,(SI_Long)8L);
	convert_file_strings_to_uppercase_p = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qconvert_file_strings_to_uppercase_p);
    }
    else if (defaults && text_string_p(defaults)) {
	result = get_parser_from_namestring(defaults);
	gensymed_symbol = NTH_VALUE((SI_Long)2L, result);
	convert_file_strings_to_uppercase_p = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qconvert_file_strings_to_uppercase_p);
    }
    else
	convert_file_strings_to_uppercase_p = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Convert_file_strings_to_uppercase_p,Qconvert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      host = copy_pathname_contents(host);
      device = copy_pathname_contents(device);
      if (CONSP(directory_1)) {
	  directory_component = Nil;
	  ab_loop_list_ = directory_1;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  ab_loopvar__2 = Nil;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  directory_component = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  ab_loopvar__2 = 
		  path_cons_1(copy_pathname_contents(directory_component),Nil);
	  if (ab_loopvar__1)
	      M_CDR(ab_loopvar__1) = ab_loopvar__2;
	  else
	      ab_loopvar_ = ab_loopvar__2;
	  ab_loopvar__1 = ab_loopvar__2;
	  goto next_loop;
	end_loop:
	  directory_1 = ab_loopvar_;
	  goto end_1;
	  directory_1 = Qnil;
	end_1:;
      }
      else if (text_string_p(directory_1))
	  directory_1 = 
		  copy_directory_components_from_directory_string(directory_1);
      else
	  directory_1 = copy_pathname_contents(directory_1);
      name = copy_pathname_contents(name);
      type = copy_pathname_contents(type);
      version = copy_pathname_contents(version);
      result = gensym_make_pathname_without_copying(7,host,device,
	      directory_1,name,type,version,defaults);
    POP_SPECIAL();
    return result;
}

/* GENSYM-MAKE-PATHNAME-FUNCTION */
Object gensym_make_pathname_function varargs_1(int, n)
{
    Object host, device, directory_1, name, type, version;
    Object defaults;
    Declare_varargs_nonrelocating;

    x_note_fn_call(39,42);
    INIT_ARGS_nonrelocating();
    host = REQUIRED_ARG_nonrelocating();
    device = REQUIRED_ARG_nonrelocating();
    directory_1 = REQUIRED_ARG_nonrelocating();
    name = REQUIRED_ARG_nonrelocating();
    type = REQUIRED_ARG_nonrelocating();
    version = REQUIRED_ARG_nonrelocating();
    defaults = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return gensym_make_pathname_with_copied_components(host,device,
	    directory_1,name,type,version,defaults);
}

/* COPY-PATHNAME-CONTENTS */
Object copy_pathname_contents(old_contents)
    Object old_contents;
{
    Object mutable_string_from_symbol;

    x_note_fn_call(39,43);
    if ( !TRUEP(old_contents))
	return VALUES_1(old_contents);
    else if (text_string_p(old_contents) && 
	    Convert_file_strings_to_uppercase_p)
	return nstring_upcasew(copy_text_string(old_contents));
    else if (text_string_p(old_contents))
	return copy_text_string(old_contents);
    else if (SYMBOLP(old_contents) && KEYWORDP(old_contents))
	return VALUES_1(old_contents);
    else if (SYMBOLP(old_contents)) {
	mutable_string_from_symbol = 
		copy_text_string(symbol_name_text_string(old_contents));
	if (Convert_file_strings_to_uppercase_p)
	    return VALUES_1(mutable_string_from_symbol);
	else
	    return nstring_downcasew(mutable_string_from_symbol);
    }
    else if (STRINGP(old_contents))
	return copy_text_string(old_contents);
    else
	return VALUES_1(old_contents);
}

/* COPY-DIRECTORY-CONTENTS */
Object copy_directory_contents(directory_to_copy)
    Object directory_to_copy;
{
    Object directory_component, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2;

    x_note_fn_call(39,44);
    directory_component = Nil;
    ab_loop_list_ = directory_to_copy;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    directory_component = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = 
	    path_cons_1(copy_pathname_contents(directory_component),Nil);
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

/* COPY-GENSYM-PATHNAME */
Object copy_gensym_pathname(old_pathname)
    Object old_pathname;
{
    Object gensym_pathname_host, gensym_pathname_device;
    Object gensym_pathname_directory, gensym_pathname_name;
    Object gensym_pathname_type, gensym_pathname_version, new_pathname;
    Object gensymed_symbol, convert_file_strings_to_uppercase_p;
    Object svref_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(39,45);
    if ( !TRUEP(old_pathname))
	return VALUES_1(Nil);
    gensym_pathname_host = ISVREF(old_pathname,(SI_Long)1L);
    gensym_pathname_device = ISVREF(old_pathname,(SI_Long)2L);
    gensym_pathname_directory = ISVREF(old_pathname,(SI_Long)3L);
    gensym_pathname_name = ISVREF(old_pathname,(SI_Long)4L);
    gensym_pathname_type = ISVREF(old_pathname,(SI_Long)5L);
    gensym_pathname_version = ISVREF(old_pathname,(SI_Long)6L);
    new_pathname = make_gensym_pathname_structure_function(Nil,Nil,Nil,Nil,
	    Nil,Nil);
    gensymed_symbol = ISVREF(old_pathname,(SI_Long)8L);
    convert_file_strings_to_uppercase_p = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qconvert_file_strings_to_uppercase_p);
    PUSH_SPECIAL_WITH_SYMBOL(Convert_file_strings_to_uppercase_p,Qconvert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      svref_new_value = copy_pathname_contents(gensym_pathname_host);
      SVREF(new_pathname,FIX((SI_Long)1L)) = svref_new_value;
      svref_new_value = copy_pathname_contents(gensym_pathname_device);
      SVREF(new_pathname,FIX((SI_Long)2L)) = svref_new_value;
      svref_new_value = CONSP(gensym_pathname_directory) ? 
	      copy_directory_contents(gensym_pathname_directory) : 
	      copy_pathname_contents(gensym_pathname_directory);
      SVREF(new_pathname,FIX((SI_Long)3L)) = svref_new_value;
      svref_new_value = copy_pathname_contents(gensym_pathname_name);
      SVREF(new_pathname,FIX((SI_Long)4L)) = svref_new_value;
      svref_new_value = copy_pathname_contents(gensym_pathname_type);
      SVREF(new_pathname,FIX((SI_Long)5L)) = svref_new_value;
      svref_new_value = copy_pathname_contents(gensym_pathname_version);
      SVREF(new_pathname,FIX((SI_Long)6L)) = svref_new_value;
      svref_new_value = ISVREF(old_pathname,(SI_Long)8L);
      SVREF(new_pathname,FIX((SI_Long)8L)) = svref_new_value;
      svref_new_value = ISVREF(old_pathname,(SI_Long)9L);
      SVREF(new_pathname,FIX((SI_Long)9L)) = svref_new_value;
      svref_new_value = ISVREF(old_pathname,(SI_Long)10L);
      SVREF(new_pathname,FIX((SI_Long)10L)) = svref_new_value;
      result = VALUES_1(new_pathname);
    POP_SPECIAL();
    return result;
}

/* GENSYM-PATHNAME-CONTENTS-EQUAL-P */
Object gensym_pathname_contents_equal_p(contents1,contents2)
    Object contents1, contents2;
{
    x_note_fn_call(39,46);
    if (text_string_p(contents1) && text_string_p(contents2) && 
	    Convert_file_strings_to_uppercase_p)
	return string_equalw(contents1,contents2);
    else if (text_string_p(contents1) && text_string_p(contents2))
	return string_eq_w(contents1,contents2);
    else
	return VALUES_1(EQL(contents1,contents2) ? T : Nil);
}

/* GENSYM-PATHNAMES-EQUAL-P */
Object gensym_pathnames_equal_p(pathname1,pathname2)
    Object pathname1, pathname2;
{
    Object file_system1, file_system2, convert_file_strings_to_uppercase_p;
    Object gensym_pathname_host1, gensym_pathname_device1;
    Object gensym_pathname_directory1, gensym_pathname_name1;
    Object gensym_pathname_type1, gensym_pathname_version1;
    Object gensym_pathname_host2, gensym_pathname_device2;
    Object gensym_pathname_directory2, gensym_pathname_name2;
    Object gensym_pathname_type2, gensym_pathname_version2, component1;
    Object ab_loop_list_, component2, ab_loop_list__1;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(39,47);
    if (SIMPLE_VECTOR_P(pathname1) && EQ(ISVREF(pathname1,(SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct) && 
	    SIMPLE_VECTOR_P(pathname2) && EQ(ISVREF(pathname2,(SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct)) {
	file_system1 = ISVREF(pathname1,(SI_Long)8L);
	file_system2 = ISVREF(pathname2,(SI_Long)8L);
	if (EQ(file_system1,file_system2)) {
	    convert_file_strings_to_uppercase_p = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(file_system1),
		    Qconvert_file_strings_to_uppercase_p);
	    PUSH_SPECIAL_WITH_SYMBOL(Convert_file_strings_to_uppercase_p,Qconvert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
		    0);
	      gensym_pathname_host1 = ISVREF(pathname1,(SI_Long)1L);
	      gensym_pathname_device1 = ISVREF(pathname1,(SI_Long)2L);
	      gensym_pathname_directory1 = ISVREF(pathname1,(SI_Long)3L);
	      gensym_pathname_name1 = ISVREF(pathname1,(SI_Long)4L);
	      gensym_pathname_type1 = ISVREF(pathname1,(SI_Long)5L);
	      gensym_pathname_version1 = ISVREF(pathname1,(SI_Long)6L);
	      gensym_pathname_host2 = ISVREF(pathname2,(SI_Long)1L);
	      gensym_pathname_device2 = ISVREF(pathname2,(SI_Long)2L);
	      gensym_pathname_directory2 = ISVREF(pathname2,(SI_Long)3L);
	      gensym_pathname_name2 = ISVREF(pathname2,(SI_Long)4L);
	      gensym_pathname_type2 = ISVREF(pathname2,(SI_Long)5L);
	      gensym_pathname_version2 = ISVREF(pathname2,(SI_Long)6L);
	      if (gensym_pathname_contents_equal_p(gensym_pathname_host1,
		      gensym_pathname_host2) && 
		      gensym_pathname_contents_equal_p(gensym_pathname_device1,
		      gensym_pathname_device2)) {
		  if (CONSP(gensym_pathname_directory1) && 
			  CONSP(gensym_pathname_directory2)) {
		      if (FIXNUM_EQ(length(gensym_pathname_directory1),
			      length(gensym_pathname_directory2))) {
			  component1 = Nil;
			  ab_loop_list_ = gensym_pathname_directory1;
			  component2 = Nil;
			  ab_loop_list__1 = gensym_pathname_directory2;
			next_loop:
			  if ( !TRUEP(ab_loop_list_))
			      goto end_loop;
			  component1 = M_CAR(ab_loop_list_);
			  ab_loop_list_ = M_CDR(ab_loop_list_);
			  if ( !TRUEP(ab_loop_list__1))
			      goto end_loop;
			  component2 = M_CAR(ab_loop_list__1);
			  ab_loop_list__1 = M_CDR(ab_loop_list__1);
			  if ( 
				  !TRUEP(gensym_pathname_contents_equal_p(component1,
				  component2))) {
			      temp = TRUEP(Nil);
			      goto end_1;
			  }
			  goto next_loop;
			end_loop:
			  temp = TRUEP(T);
			  goto end_1;
			  temp = TRUEP(Qnil);
			end_1:;
		      }
		      else
			  temp = TRUEP(Nil);
		  }
		  else
		      temp = 
			      TRUEP(gensym_pathname_contents_equal_p(gensym_pathname_directory1,
			      gensym_pathname_directory2));
	      }
	      else
		  temp = TRUEP(Nil);
	      if ((temp ? 
		      TRUEP(gensym_pathname_contents_equal_p(gensym_pathname_name1,
		      gensym_pathname_name2)) : TRUEP(Nil)) ? 
		      TRUEP(gensym_pathname_contents_equal_p(gensym_pathname_type1,
		      gensym_pathname_type2)) : TRUEP(Nil))
		  result = gensym_pathname_contents_equal_p(gensym_pathname_version1,
			  gensym_pathname_version2);
	      else
		  result = VALUES_1(Nil);
	    POP_SPECIAL();
	    return result;
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* GENSYM-PATHNAMES-EQUAL-ENOUGH-P */
Object gensym_pathnames_equal_enough_p(pathname1,pathname2)
    Object pathname1, pathname2;
{
    Object file_system1, file_system2, convert_file_strings_to_uppercase_p;
    Object gensym_pathname_host1, gensym_pathname_device1;
    Object gensym_pathname_directory1, gensym_pathname_name1;
    Object gensym_pathname_type1, gensym_pathname_version1;
    Object gensym_pathname_host2, gensym_pathname_device2;
    Object gensym_pathname_directory2, gensym_pathname_name2;
    Object gensym_pathname_type2, gensym_pathname_version2, component1;
    Object ab_loop_list_, component2, ab_loop_list__1;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(39,48);
    if (SIMPLE_VECTOR_P(pathname1) && EQ(ISVREF(pathname1,(SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct) && 
	    SIMPLE_VECTOR_P(pathname2) && EQ(ISVREF(pathname2,(SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct)) {
	file_system1 = ISVREF(pathname1,(SI_Long)8L);
	file_system2 = ISVREF(pathname2,(SI_Long)8L);
	if (EQ(file_system1,file_system2)) {
	    convert_file_strings_to_uppercase_p = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(file_system1),
		    Qconvert_file_strings_to_uppercase_p);
	    PUSH_SPECIAL_WITH_SYMBOL(Convert_file_strings_to_uppercase_p,Qconvert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
		    0);
	      gensym_pathname_host1 = ISVREF(pathname1,(SI_Long)1L);
	      gensym_pathname_device1 = ISVREF(pathname1,(SI_Long)2L);
	      gensym_pathname_directory1 = ISVREF(pathname1,(SI_Long)3L);
	      gensym_pathname_name1 = ISVREF(pathname1,(SI_Long)4L);
	      gensym_pathname_type1 = ISVREF(pathname1,(SI_Long)5L);
	      gensym_pathname_version1 = ISVREF(pathname1,(SI_Long)6L);
	      gensym_pathname_host2 = ISVREF(pathname2,(SI_Long)1L);
	      gensym_pathname_device2 = ISVREF(pathname2,(SI_Long)2L);
	      gensym_pathname_directory2 = ISVREF(pathname2,(SI_Long)3L);
	      gensym_pathname_name2 = ISVREF(pathname2,(SI_Long)4L);
	      gensym_pathname_type2 = ISVREF(pathname2,(SI_Long)5L);
	      gensym_pathname_version2 = ISVREF(pathname2,(SI_Long)6L);
	      if (gensym_pathname_contents_equal_p(gensym_pathname_host1,
		      gensym_pathname_host2) && 
		      gensym_pathname_contents_equal_p(gensym_pathname_device1,
		      gensym_pathname_device2)) {
		  if (CONSP(gensym_pathname_directory1) && 
			  CONSP(gensym_pathname_directory2)) {
		      if (FIXNUM_EQ(length(gensym_pathname_directory1),
			      length(gensym_pathname_directory2))) {
			  component1 = Nil;
			  ab_loop_list_ = gensym_pathname_directory1;
			  component2 = Nil;
			  ab_loop_list__1 = gensym_pathname_directory2;
			next_loop:
			  if ( !TRUEP(ab_loop_list_))
			      goto end_loop;
			  component1 = M_CAR(ab_loop_list_);
			  ab_loop_list_ = M_CDR(ab_loop_list_);
			  if ( !TRUEP(ab_loop_list__1))
			      goto end_loop;
			  component2 = M_CAR(ab_loop_list__1);
			  ab_loop_list__1 = M_CDR(ab_loop_list__1);
			  if ( 
				  !TRUEP(gensym_pathname_contents_equal_p(component1,
				  component2))) {
			      temp = TRUEP(Nil);
			      goto end_1;
			  }
			  goto next_loop;
			end_loop:
			  temp = TRUEP(T);
			  goto end_1;
			  temp = TRUEP(Qnil);
			end_1:;
		      }
		      else
			  temp = TRUEP(Nil);
		  }
		  else
		      temp = 
			      TRUEP(gensym_pathname_contents_equal_p(gensym_pathname_directory1,
			      gensym_pathname_directory2));
	      }
	      else
		  temp = TRUEP(Nil);
	      if ((temp ? 
		      TRUEP(gensym_pathname_contents_equal_p(gensym_pathname_name1,
		      gensym_pathname_name2)) : TRUEP(Nil)) ? 
		      TRUEP(gensym_pathname_contents_equal_p(gensym_pathname_type1,
		      gensym_pathname_type2)) : TRUEP(Nil)) {
		  if (EQ(gensym_pathname_version1,Knewest) &&  
			  !TRUEP(gensym_pathname_version2))
		      result = VALUES_1(T);
		  else if ( !TRUEP(gensym_pathname_version1) && 
			  EQ(gensym_pathname_version2,Knewest))
		      result = VALUES_1(T);
		  else
		      result = gensym_pathname_contents_equal_p(gensym_pathname_version1,
			      gensym_pathname_version2);
	      }
	      else
		  result = VALUES_1(Nil);
	    POP_SPECIAL();
	    return result;
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_1;   /* "~a" */

/* FILE-SYSTEM-HOST-AS-TEXT-STRING */
Object file_system_host_as_text_string(lisp_pathname_host)
    Object lisp_pathname_host;
{
    x_note_fn_call(39,49);
    if (text_string_p(lisp_pathname_host))
	return tformat_text_string(2,string_constant_1,lisp_pathname_host);
    else if ( !TRUEP(lisp_pathname_host))
	return VALUES_1(Nil);
    else
	return VALUES_1(Nil);
}

/* CONVERT-NAMESTRING-TO-GENSYM-PATHNAME-WITH-KNOWN-PARSER */
Object convert_namestring_to_gensym_pathname_with_known_parser(namestring_1,
	    filename_parser,namestring_generator)
    Object namestring_1, filename_parser, namestring_generator;
{
    Object temp, pathname_qm;

    x_note_fn_call(39,50);
    temp = SYMBOL_FUNCTION(filename_parser);
    pathname_qm = FUNCALL_1(temp,namestring_1);
    if (pathname_qm) {
	SVREF(pathname_qm,FIX((SI_Long)9L)) = filename_parser;
	SVREF(pathname_qm,FIX((SI_Long)10L)) = namestring_generator;
	return VALUES_1(pathname_qm);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(All_gensym_pathnames_containing_open_streams, Qall_gensym_pathnames_containing_open_streams);

/* CONVERT-G2-STREAM-TO-GENSYM-PATHNAME */
Object convert_g2_stream_to_gensym_pathname(g2_stream)
    Object g2_stream;
{
    Object queue, next_queue_element, pathname_1, ab_loop_it_;

    x_note_fn_call(39,51);
    queue = All_gensym_pathnames_containing_open_streams;
    next_queue_element = Nil;
    pathname_1 = Nil;
    ab_loop_it_ = Nil;
    next_queue_element = constant_queue_next(ISVREF(queue,(SI_Long)2L),queue);
  next_loop:
    if ( !TRUEP(next_queue_element))
	goto end_loop;
    pathname_1 = ISVREF(next_queue_element,(SI_Long)4L);
    next_queue_element = constant_queue_next(next_queue_element,queue);
    ab_loop_it_ = identical_g2_streams_p(ISVREF(pathname_1,(SI_Long)7L),
	    g2_stream) ? copy_gensym_pathname(pathname_1) : Qnil;
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    goto next_loop;
  end_loop:
    return make_empty_gensym_pathname();
    return VALUES_1(Qnil);
}

/* CONVERT-TO-GENSYM-PATHNAME-WITH-KNOWN-PARSER */
Object convert_to_gensym_pathname_with_known_parser(thing,filename_parser,
	    namestring_generator)
    Object thing, filename_parser, namestring_generator;
{
    x_note_fn_call(39,52);
    if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct))
	return copy_gensym_pathname(thing);
    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	return convert_namestring_to_gensym_pathname_with_known_parser(thing,
		filename_parser,namestring_generator);
    else if (STRINGP(thing))
	return convert_namestring_to_gensym_pathname_with_known_parser(thing,
		filename_parser,namestring_generator);
    else if (SYMBOLP(thing))
	return convert_namestring_to_gensym_pathname_with_known_parser(symbol_name_text_string(thing),
		filename_parser,namestring_generator);
    else if (g2_stream_p(thing))
	return convert_g2_stream_to_gensym_pathname(thing);
    else
	return make_empty_gensym_pathname();
}

/* CONVERT-TO-GENSYM-PATHNAME */
Object convert_to_gensym_pathname(thing,default_filename_parser,
	    default_namestring_generator)
    Object thing, default_filename_parser, default_namestring_generator;
{
    x_note_fn_call(39,53);
    if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct))
	return copy_gensym_pathname(thing);
    else if (text_string_p(thing))
	return convert_to_gensym_pathname_with_known_parser(thing,
		default_filename_parser,default_namestring_generator);
    else if (STRINGP(thing))
	return convert_to_gensym_pathname_with_known_parser(thing,
		default_filename_parser,default_namestring_generator);
    else if (SYMBOLP(thing))
	return convert_to_gensym_pathname_with_known_parser(symbol_name_text_string(thing),
		default_filename_parser,default_namestring_generator);
    else if (g2_stream_p(thing))
	return convert_g2_stream_to_gensym_pathname(thing);
    else
	return make_empty_gensym_pathname();
}

static Object Krelative;           /* :relative */

/* COALESCE-DIRECTORY-COMPONENTS */
Object coalesce_directory_components(directory_list)
    Object directory_list;
{
    Object directory_component, ab_loop_list_, result_directory_list;
    Object retain_relative_marker_p, retain_up_marker_p, ab_loop_iter_flag_;
    Object path_pop_store, cons_1, next_cons, temp, svref_arg_2;
    Object discarded_component;

    x_note_fn_call(39,54);
    directory_component = Nil;
    ab_loop_list_ = directory_list;
    result_directory_list = Nil;
    retain_relative_marker_p = EQ(CAR(directory_list),Krelative) ? T : Nil;
    retain_up_marker_p = EQ(CAR(directory_list),Kup) ? T : Nil;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    directory_component = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_)) {
	retain_relative_marker_p = Nil;
	retain_up_marker_p = retain_up_marker_p ? (EQ(directory_component,
		Kup) ? T : Nil) : Qnil;
    }
    if (EQ(directory_component,Krelative)) {
	if (retain_relative_marker_p)
	    result_directory_list = path_cons_1(directory_component,
		    result_directory_list);
    }
    else if (EQ(directory_component,Kup)) {
	if (retain_up_marker_p)
	    result_directory_list = path_cons_1(directory_component,
		    result_directory_list);
	else {
	    path_pop_store = Nil;
	    cons_1 = result_directory_list;
	    if (cons_1) {
		path_pop_store = M_CAR(cons_1);
		next_cons = M_CDR(cons_1);
		inline_note_reclaim_cons(cons_1,Qpath);
		if (ISVREF(Available_path_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp = ISVREF(Available_path_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp) = cons_1;
		    temp = Available_path_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		}
		else {
		    temp = Available_path_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		    temp = Available_path_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		}
		M_CDR(cons_1) = Nil;
	    }
	    else
		next_cons = Nil;
	    result_directory_list = next_cons;
	    discarded_component = path_pop_store;
	    if (text_string_p(discarded_component))
		reclaim_text_string(discarded_component);
	}
    }
    else
	result_directory_list = path_cons_1(directory_component,
		result_directory_list);
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    reclaim_path_list_1(directory_list);
    return nreverse(result_directory_list);
    return VALUES_1(Qnil);
}

/* CANONICIZE-HOST-NAME-FROM-FILE-SYSTEM */
Object canonicize_host_name_from_file_system(pathname_1)
    Object pathname_1;
{
    x_note_fn_call(39,55);
    return VALUES_1(pathname_1);
}

static Object Qunbound_in_protected_let;  /* unbound-in-protected-let */

static Object array_constant;      /* # */

static Object string_constant_2;   /* "~A/" */

/* SUPPLY-HOME-TO-UNIX-PATHNAME */
Object supply_home_to_unix_pathname(pathname_1)
    Object pathname_1;
{
    volatile Object home_directory_string_qm;
    Object directory_length;
    volatile Object already_terminated_p;
    volatile Object terminated_home_directory_string;
    volatile Object home_directory_pathname;
    Object path_pop_store, cons_1, next_cons, temp, svref_arg_2;
    Declare_stack_pointer;
    Declare_catch(2);
    Object result;

    x_note_fn_call(39,56);
    SAVE_STACK();
    home_directory_string_qm = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(1)) {
	home_directory_string_qm = 
		get_gensym_environment_variable(array_constant);
	if (home_directory_string_qm) {
	    directory_length = lengthw(home_directory_string_qm);
	    if (IFIX(directory_length) > (SI_Long)0L) {
		already_terminated_p = Qunbound_in_protected_let;
		terminated_home_directory_string = Qunbound_in_protected_let;
		home_directory_pathname = Qunbound_in_protected_let;
		if (PUSH_UNWIND_PROTECT(0)) {
		    already_terminated_p = (SI_Long)47L == 
			    UBYTE_16_ISAREF_1(home_directory_string_qm,
			    IFIX(FIXNUM_SUB1(directory_length))) ? T : Nil;
		    terminated_home_directory_string = 
			    already_terminated_p ? 
			    home_directory_string_qm : 
			    tformat_text_string(2,string_constant_2,
			    home_directory_string_qm);
		    home_directory_pathname = 
			    gensym_pathname(terminated_home_directory_string);
		    path_pop_store = Nil;
		    cons_1 = ISVREF(pathname_1,(SI_Long)3L);
		    if (cons_1) {
			path_pop_store = M_CAR(cons_1);
			next_cons = M_CDR(cons_1);
			inline_note_reclaim_cons(cons_1,Qpath);
			if (ISVREF(Available_path_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp = 
				    ISVREF(Available_path_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp) = cons_1;
			    temp = Available_path_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp,svref_arg_2) = cons_1;
			}
			else {
			    temp = Available_path_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp,svref_arg_2) = cons_1;
			    temp = Available_path_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp,svref_arg_2) = cons_1;
			}
			M_CDR(cons_1) = Nil;
		    }
		    else
			next_cons = Nil;
		    SVREF(pathname_1,FIX((SI_Long)3L)) = next_cons;
		    temp = nconc2(ISVREF(home_directory_pathname,
			    (SI_Long)3L),ISVREF(pathname_1,(SI_Long)3L));
		    SVREF(pathname_1,FIX((SI_Long)3L)) = temp;
		    SAVE_VALUES(VALUES_1(SVREF(home_directory_pathname,
			    FIX((SI_Long)3L)) = Nil));
		}
		POP_UNWIND_PROTECT(0);
		if (home_directory_pathname) {
		    if ( !EQ(home_directory_pathname,
			    Qunbound_in_protected_let))
			reclaim_gensym_pathname(home_directory_pathname);
		}
		if (terminated_home_directory_string) {
		    if ( !EQ(terminated_home_directory_string,
			    Qunbound_in_protected_let)) {
			if ( !TRUEP(already_terminated_p))
			    reclaim_text_string(terminated_home_directory_string);
		    }
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
    if (home_directory_string_qm) {
	if ( !EQ(home_directory_string_qm,Qunbound_in_protected_let))
	    reclaim_text_string(home_directory_string_qm);
    }
    CONTINUE_UNWINDING(1);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object Khome;               /* :home */

/* MAYBE-SUPPLY-HOME-TO-POSSIBLE-UNIX-PATHNAME */
Object maybe_supply_home_to_possible_unix_pathname(pathname_1)
    Object pathname_1;
{
    Object temp;
    char temp_1;

    x_note_fn_call(39,57);
    if (EQ(ISVREF(pathname_1,(SI_Long)8L),Qunix)) {
	temp = ISVREF(pathname_1,(SI_Long)3L);
	temp_1 = EQ(FIRST(temp),Khome);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	supply_home_to_unix_pathname(pathname_1);
    return VALUES_1(pathname_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Inside_handling_gensym_file_errors_scope_p, Qinside_handling_gensym_file_errors_scope_p);

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_file_error_occurred_p, Qgensym_file_error_occurred_p);

static Object Qgensym_file_error_catch_tag;  /* gensym-file-error-catch-tag */

static Object Qtformat_text_string;  /* tformat-text-string */

/* SIGNAL-GENSYM-FILE-ERROR */
Object signal_gensym_file_error(file_error_string,arguments_list)
    Object file_error_string, arguments_list;
{
    Object temp, report_string, error_arg, ab_loop_list_;
    Object result;

    x_note_fn_call(39,58);
    if (Inside_handling_gensym_file_errors_scope_p) {
	Gensym_file_error_occurred_p = T;
	result = path_cons_1(file_error_string,arguments_list);
	THROW(Qgensym_file_error_catch_tag,result);
    }
    else {
	temp = SYMBOL_FUNCTION(Qtformat_text_string);
	report_string = APPLY_2(temp,file_error_string,arguments_list);
	notify_user(2,string_constant_1,report_string);
	reclaim_text_string(report_string);
	if (arguments_list) {
	    error_arg = Nil;
	    ab_loop_list_ = arguments_list;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    error_arg = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (text_string_p(error_arg))
		reclaim_text_string(error_arg);
	    goto next_loop;
	  end_loop:
	    reclaim_path_list_1(arguments_list);
	}
	return abort_g2(0);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Report_filename_parsing_errors_in_development_p, Qreport_filename_parsing_errors_in_development_p);

/* VALID-PATHNAME-P */
Object valid_pathname_p(convertible_thing)
    Object convertible_thing;
{
    Object report_filename_parsing_errors_in_development_p;
    Object current_local_filename_parser, current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p, pathname_qm;
    Declare_special(2);
    Object result;

    x_note_fn_call(39,59);
    report_filename_parsing_errors_in_development_p = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Report_filename_parsing_errors_in_development_p,Qreport_filename_parsing_errors_in_development_p,report_filename_parsing_errors_in_development_p,
	    1);
      if (EQUAL(convertible_thing,Nil))
	  result = VALUES_1(Nil);
      else {
	  current_local_filename_parser = Local_filename_parser;
	  current_local_namestring_generator = Local_namestring_generator;
	  convert_file_strings_to_uppercase_p = 
		  getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
		  Qconvert_file_strings_to_uppercase_p);
	  PUSH_SPECIAL_WITH_SYMBOL(Convert_file_strings_to_uppercase_p,Qconvert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
		  0);
	    pathname_qm = convert_to_gensym_pathname(convertible_thing,
		    current_local_filename_parser,
		    current_local_namestring_generator);
	    if (pathname_qm) {
		reclaim_gensym_pathname(pathname_qm);
		result = VALUES_1(T);
	    }
	    else
		result = VALUES_1(Nil);
	  POP_SPECIAL();
      }
    POP_SPECIAL();
    return result;
}

static Object array_constant_1;    /* # */

static Object Qgeneralized_dos;    /* generalized-dos */

/* VALID-DIRECTORY-P */
Object valid_directory_p(convertible_thing)
    Object convertible_thing;
{
    Object report_filename_parsing_errors_in_development_p;
    Object current_local_filename_parser, current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object pathname_qm;
    Object temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(39,60);
    SAVE_STACK();
    report_filename_parsing_errors_in_development_p = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Report_filename_parsing_errors_in_development_p,Qreport_filename_parsing_errors_in_development_p,report_filename_parsing_errors_in_development_p,
	    1);
      current_local_filename_parser = Local_filename_parser;
      current_local_namestring_generator = Local_namestring_generator;
      convert_file_strings_to_uppercase_p = 
	      getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	      Qconvert_file_strings_to_uppercase_p);
      PUSH_SPECIAL_WITH_SYMBOL(Convert_file_strings_to_uppercase_p,Qconvert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	      0);
	pathname_qm = Qunbound_in_protected_let;
	if (PUSH_UNWIND_PROTECT(0)) {
	    pathname_qm = convert_to_gensym_pathname(convertible_thing,
		    current_local_filename_parser,
		    current_local_namestring_generator);
	    if (pathname_qm) {
		temp = ISVREF(pathname_qm,(SI_Long)8L);
		if (EQ(temp,Qunix))
		    temp = ISVREF(pathname_qm,(SI_Long)4L);
		else if (EQ(temp,Qvms))
		    temp = ISVREF(pathname_qm,(SI_Long)4L) ? 
			    string_equalw(ISVREF(pathname_qm,(SI_Long)5L),
			    array_constant_1) : Qnil;
		else if (EQ(temp,Qdos) || EQ(temp,Qwin32) || EQ(temp,
			Qgeneralized_dos))
		    temp = ISVREF(pathname_qm,(SI_Long)4L);
		else
		    temp = Nil;
		if (temp)
		    SAVE_VALUES(VALUES_1(T));
		else
		    SAVE_VALUES(VALUES_1(Nil));
	    }
	    else
		SAVE_VALUES(VALUES_1(Nil));
	}
	POP_UNWIND_PROTECT(0);
	if (pathname_qm) {
	    if ( !EQ(pathname_qm,Qunbound_in_protected_let)) {
		if (pathname_qm)
		    reclaim_gensym_pathname(pathname_qm);
	    }
	}
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* GENSYM-WILD-PATHNAME-P */
Object gensym_wild_pathname_p(convertible_thing)
    Object convertible_thing;
{
    Object current_local_filename_parser, current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object pathname_qm;
    Object contents, temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(39,61);
    SAVE_STACK();
    current_local_filename_parser = Local_filename_parser;
    current_local_namestring_generator = Local_namestring_generator;
    convert_file_strings_to_uppercase_p = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	    Qconvert_file_strings_to_uppercase_p);
    PUSH_SPECIAL_WITH_SYMBOL(Convert_file_strings_to_uppercase_p,Qconvert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      pathname_qm = Qunbound_in_protected_let;
      if (PUSH_UNWIND_PROTECT(0)) {
	  pathname_qm = convert_to_gensym_pathname(convertible_thing,
		  current_local_filename_parser,
		  current_local_namestring_generator);
	  if (pathname_qm) {
	      contents = ISVREF(pathname_qm,(SI_Long)4L);
	      temp = text_string_p(contents) ? 
		      wild_regular_expression_string_p(contents) : 
		      EQ(Kwild,contents) ? T : Nil;
	      if (temp);
	      else {
		  contents = ISVREF(pathname_qm,(SI_Long)5L);
		  temp = text_string_p(contents) ? 
			  wild_regular_expression_string_p(contents) : 
			  EQ(Kwild,contents) ? T : Nil;
	      }
	      if (temp)
		  SAVE_VALUES(VALUES_1(temp));
	      else {
		  contents = ISVREF(pathname_qm,(SI_Long)6L);
		  if (text_string_p(contents))
		      SAVE_VALUES(wild_regular_expression_string_p(contents));
		  else
		      SAVE_VALUES(VALUES_1(EQ(Kwild,contents) ? T : Nil));
	      }
	  }
	  else
	      SAVE_VALUES(VALUES_1(Nil));
      }
      POP_UNWIND_PROTECT(0);
      if (pathname_qm) {
	  if ( !EQ(pathname_qm,Qunbound_in_protected_let)) {
	      if (pathname_qm)
		  reclaim_gensym_pathname(pathname_qm);
	  }
      }
      CONTINUE_UNWINDING(0);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object array_constant_2;    /* # */

/* GENSYM-NAMESTRING */
Object gensym_namestring varargs_1(int, n)
{
    Object convertible_thing;
    Object prefer_lowercase_p, current_local_filename_parser;
    Object current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object pathname_qm;
    Object gensymed_symbol, component, ab_loop_list_, temp;
    Object internal_namestring;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(39,62);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    prefer_lowercase_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    current_local_filename_parser = Local_filename_parser;
    current_local_namestring_generator = Local_namestring_generator;
    convert_file_strings_to_uppercase_p = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	    Qconvert_file_strings_to_uppercase_p);
    PUSH_SPECIAL_WITH_SYMBOL(Convert_file_strings_to_uppercase_p,Qconvert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      pathname_qm = Qunbound_in_protected_let;
      if (PUSH_UNWIND_PROTECT(0)) {
	  pathname_qm = convert_to_gensym_pathname(convertible_thing,
		  current_local_filename_parser,
		  current_local_namestring_generator);
	  if (pathname_qm) {
	      gensymed_symbol = ISVREF(pathname_qm,(SI_Long)8L);
	      if (getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		      Qconvert_file_strings_to_uppercase_p) ? 
		      TRUEP(prefer_lowercase_p) : TRUEP(Nil)) {
		  component = ISVREF(pathname_qm,(SI_Long)1L);
		  if (text_string_p(component)) {
		      if ( !TRUEP(wild_regular_expression_string_p(component)))
			  nstring_downcasew(component);
		  }
		  component = ISVREF(pathname_qm,(SI_Long)2L);
		  if (text_string_p(component)) {
		      if ( !TRUEP(wild_regular_expression_string_p(component)))
			  nstring_downcasew(component);
		  }
		  component = Nil;
		  ab_loop_list_ = ISVREF(pathname_qm,(SI_Long)3L);
		next_loop:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop;
		  component = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  if (text_string_p(component)) {
		      if ( !TRUEP(wild_regular_expression_string_p(component)))
			  nstring_downcasew(component);
		  }
		  goto next_loop;
		end_loop:;
		  component = ISVREF(pathname_qm,(SI_Long)4L);
		  if (text_string_p(component)) {
		      if ( !TRUEP(wild_regular_expression_string_p(component)))
			  nstring_downcasew(component);
		  }
		  component = ISVREF(pathname_qm,(SI_Long)5L);
		  if (text_string_p(component)) {
		      if ( !TRUEP(wild_regular_expression_string_p(component)))
			  nstring_downcasew(component);
		  }
		  component = ISVREF(pathname_qm,(SI_Long)6L);
		  if (text_string_p(component)) {
		      if ( !TRUEP(wild_regular_expression_string_p(component)))
			  nstring_downcasew(component);
		  }
	      }
	      temp = ISVREF(pathname_qm,(SI_Long)10L);
	      internal_namestring = FUNCALL_1(temp,pathname_qm);
	      SAVE_VALUES(VALUES_1(internal_namestring));
	  }
	  else
	      SAVE_VALUES(copy_constant_wide_string_given_length(array_constant_2,
		      FIX((SI_Long)0L)));
      }
      POP_UNWIND_PROTECT(0);
      if (pathname_qm) {
	  if ( !EQ(pathname_qm,Qunbound_in_protected_let)) {
	      if (pathname_qm)
		  reclaim_gensym_pathname(pathname_qm);
	  }
      }
      CONTINUE_UNWINDING(0);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* GENSYM-NAMESTRING-AS-TEXT-STRING */
Object gensym_namestring_as_text_string varargs_1(int, n)
{
    Object convertible_thing;
    Object prefer_lowercase_p, namestring_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(39,63);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    prefer_lowercase_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    namestring_1 = gensym_namestring(2,convertible_thing,prefer_lowercase_p);
    return VALUES_1(namestring_1);
}

static Object Qnamestring_as_gensym_string;  /* namestring-as-gensym-string */

/* NAMESTRING-AS-GENSYM-STRING */
Object namestring_as_gensym_string(pathname_1)
    Object pathname_1;
{
    Object namestring_1, gensym_string;

    x_note_fn_call(39,64);
    namestring_1 = gensym_namestring(1,pathname_1);
    gensym_string = export_text_string(2,namestring_1,
	    Qnamestring_as_gensym_string);
    reclaim_wide_string(namestring_1);
    return VALUES_1(gensym_string);
}

/* GENSYM-FILE-NAMESTRING */
Object gensym_file_namestring varargs_1(int, n)
{
    Object convertible_thing;
    Object prefer_lowercase_p, current_local_filename_parser;
    Object current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object pathname_qm;
    Object old_gensym_pathname_directory, old_gensym_pathname_device;
    Object old_gensym_pathname_host, gensymed_symbol, component, temp;
    Object internal_namestring;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(1);
    Object result;

    x_note_fn_call(39,65);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    prefer_lowercase_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    current_local_filename_parser = Local_filename_parser;
    current_local_namestring_generator = Local_namestring_generator;
    convert_file_strings_to_uppercase_p = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	    Qconvert_file_strings_to_uppercase_p);
    PUSH_SPECIAL_WITH_SYMBOL(Convert_file_strings_to_uppercase_p,Qconvert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      pathname_qm = Qunbound_in_protected_let;
      if (PUSH_UNWIND_PROTECT(1)) {
	  pathname_qm = convert_to_gensym_pathname(convertible_thing,
		  current_local_filename_parser,
		  current_local_namestring_generator);
	  if (pathname_qm) {
	      old_gensym_pathname_directory = ISVREF(pathname_qm,(SI_Long)3L);
	      old_gensym_pathname_device = ISVREF(pathname_qm,(SI_Long)2L);
	      old_gensym_pathname_host = ISVREF(pathname_qm,(SI_Long)1L);
	      if (PUSH_UNWIND_PROTECT(0)) {
		  SVREF(pathname_qm,FIX((SI_Long)3L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)2L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)1L)) = Nil;
		  gensymed_symbol = ISVREF(pathname_qm,(SI_Long)8L);
		  if (getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			  Qconvert_file_strings_to_uppercase_p) ? 
			  TRUEP(prefer_lowercase_p) : TRUEP(Nil)) {
		      component = ISVREF(pathname_qm,(SI_Long)4L);
		      if (text_string_p(component)) {
			  if ( 
				  !TRUEP(wild_regular_expression_string_p(component)))
			      nstring_downcasew(component);
		      }
		      component = ISVREF(pathname_qm,(SI_Long)5L);
		      if (text_string_p(component)) {
			  if ( 
				  !TRUEP(wild_regular_expression_string_p(component)))
			      nstring_downcasew(component);
		      }
		      component = ISVREF(pathname_qm,(SI_Long)6L);
		      if (text_string_p(component)) {
			  if ( 
				  !TRUEP(wild_regular_expression_string_p(component)))
			      nstring_downcasew(component);
		      }
		  }
		  temp = ISVREF(pathname_qm,(SI_Long)10L);
		  internal_namestring = FUNCALL_1(temp,pathname_qm);
		  SAVE_VALUES(VALUES_1(internal_namestring));
	      }
	      POP_UNWIND_PROTECT(0);
	      SVREF(pathname_qm,FIX((SI_Long)3L)) = 
		      old_gensym_pathname_directory;
	      SVREF(pathname_qm,FIX((SI_Long)2L)) = old_gensym_pathname_device;
	      SVREF(pathname_qm,FIX((SI_Long)1L)) = old_gensym_pathname_host;
	      CONTINUE_UNWINDING(0);
	  }
	  else
	      SAVE_VALUES(copy_constant_wide_string_given_length(array_constant_2,
		      FIX((SI_Long)0L)));
      }
      POP_UNWIND_PROTECT(1);
      if (pathname_qm) {
	  if ( !EQ(pathname_qm,Qunbound_in_protected_let)) {
	      if (pathname_qm)
		  reclaim_gensym_pathname(pathname_qm);
	  }
      }
      CONTINUE_UNWINDING(1);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* GENSYM-FILE-NAMESTRING-AS-TEXT-STRING */
Object gensym_file_namestring_as_text_string varargs_1(int, n)
{
    Object convertible_thing;
    Object prefer_lowercase_p, namestring_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(39,66);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    prefer_lowercase_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    namestring_1 = gensym_file_namestring(2,convertible_thing,
	    prefer_lowercase_p);
    return VALUES_1(namestring_1);
}

/* GENSYM-HOST-NAMESTRING */
Object gensym_host_namestring varargs_1(int, n)
{
    Object convertible_thing;
    Object prefer_lowercase_p, current_local_filename_parser;
    Object current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object pathname_qm;
    Object old_gensym_pathname_version, old_gensym_pathname_type;
    Object old_gensym_pathname_name, old_gensym_pathname_directory;
    Object old_gensym_pathname_device, gensymed_symbol, component, temp;
    Object internal_namestring;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(1);
    Object result;

    x_note_fn_call(39,67);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    prefer_lowercase_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    current_local_filename_parser = Local_filename_parser;
    current_local_namestring_generator = Local_namestring_generator;
    convert_file_strings_to_uppercase_p = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	    Qconvert_file_strings_to_uppercase_p);
    PUSH_SPECIAL_WITH_SYMBOL(Convert_file_strings_to_uppercase_p,Qconvert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      pathname_qm = Qunbound_in_protected_let;
      if (PUSH_UNWIND_PROTECT(1)) {
	  pathname_qm = convert_to_gensym_pathname(convertible_thing,
		  current_local_filename_parser,
		  current_local_namestring_generator);
	  if (pathname_qm) {
	      old_gensym_pathname_version = ISVREF(pathname_qm,(SI_Long)6L);
	      old_gensym_pathname_type = ISVREF(pathname_qm,(SI_Long)5L);
	      old_gensym_pathname_name = ISVREF(pathname_qm,(SI_Long)4L);
	      old_gensym_pathname_directory = ISVREF(pathname_qm,(SI_Long)3L);
	      old_gensym_pathname_device = ISVREF(pathname_qm,(SI_Long)2L);
	      if (PUSH_UNWIND_PROTECT(0)) {
		  SVREF(pathname_qm,FIX((SI_Long)6L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)5L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)4L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)3L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)2L)) = Nil;
		  gensymed_symbol = ISVREF(pathname_qm,(SI_Long)8L);
		  if (getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			  Qconvert_file_strings_to_uppercase_p) ? 
			  TRUEP(prefer_lowercase_p) : TRUEP(Nil)) {
		      component = ISVREF(pathname_qm,(SI_Long)1L);
		      if (text_string_p(component)) {
			  if ( 
				  !TRUEP(wild_regular_expression_string_p(component)))
			      nstring_downcasew(component);
		      }
		  }
		  temp = ISVREF(pathname_qm,(SI_Long)10L);
		  internal_namestring = FUNCALL_1(temp,pathname_qm);
		  SAVE_VALUES(VALUES_1(internal_namestring));
	      }
	      POP_UNWIND_PROTECT(0);
	      SVREF(pathname_qm,FIX((SI_Long)6L)) = 
		      old_gensym_pathname_version;
	      SVREF(pathname_qm,FIX((SI_Long)5L)) = old_gensym_pathname_type;
	      SVREF(pathname_qm,FIX((SI_Long)4L)) = old_gensym_pathname_name;
	      SVREF(pathname_qm,FIX((SI_Long)3L)) = 
		      old_gensym_pathname_directory;
	      SVREF(pathname_qm,FIX((SI_Long)2L)) = old_gensym_pathname_device;
	      CONTINUE_UNWINDING(0);
	  }
	  else
	      SAVE_VALUES(copy_constant_wide_string_given_length(array_constant_2,
		      FIX((SI_Long)0L)));
      }
      POP_UNWIND_PROTECT(1);
      if (pathname_qm) {
	  if ( !EQ(pathname_qm,Qunbound_in_protected_let)) {
	      if (pathname_qm)
		  reclaim_gensym_pathname(pathname_qm);
	  }
      }
      CONTINUE_UNWINDING(1);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* GENSYM-DEVICE-NAMESTRING */
Object gensym_device_namestring varargs_1(int, n)
{
    Object convertible_thing;
    Object prefer_lowercase_p, current_local_filename_parser;
    Object current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object pathname_qm;
    Object old_gensym_pathname_version, old_gensym_pathname_type;
    Object old_gensym_pathname_name, old_gensym_pathname_directory;
    Object old_gensym_pathname_host, gensymed_symbol, component, temp;
    Object internal_namestring;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(1);
    Object result;

    x_note_fn_call(39,68);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    prefer_lowercase_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    current_local_filename_parser = Local_filename_parser;
    current_local_namestring_generator = Local_namestring_generator;
    convert_file_strings_to_uppercase_p = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	    Qconvert_file_strings_to_uppercase_p);
    PUSH_SPECIAL_WITH_SYMBOL(Convert_file_strings_to_uppercase_p,Qconvert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      pathname_qm = Qunbound_in_protected_let;
      if (PUSH_UNWIND_PROTECT(1)) {
	  pathname_qm = convert_to_gensym_pathname(convertible_thing,
		  current_local_filename_parser,
		  current_local_namestring_generator);
	  if (pathname_qm) {
	      old_gensym_pathname_version = ISVREF(pathname_qm,(SI_Long)6L);
	      old_gensym_pathname_type = ISVREF(pathname_qm,(SI_Long)5L);
	      old_gensym_pathname_name = ISVREF(pathname_qm,(SI_Long)4L);
	      old_gensym_pathname_directory = ISVREF(pathname_qm,(SI_Long)3L);
	      old_gensym_pathname_host = ISVREF(pathname_qm,(SI_Long)1L);
	      if (PUSH_UNWIND_PROTECT(0)) {
		  SVREF(pathname_qm,FIX((SI_Long)6L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)5L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)4L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)3L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)1L)) = Nil;
		  gensymed_symbol = ISVREF(pathname_qm,(SI_Long)8L);
		  if (getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			  Qconvert_file_strings_to_uppercase_p) ? 
			  TRUEP(prefer_lowercase_p) : TRUEP(Nil)) {
		      component = ISVREF(pathname_qm,(SI_Long)2L);
		      if (text_string_p(component)) {
			  if ( 
				  !TRUEP(wild_regular_expression_string_p(component)))
			      nstring_downcasew(component);
		      }
		  }
		  temp = ISVREF(pathname_qm,(SI_Long)10L);
		  internal_namestring = FUNCALL_1(temp,pathname_qm);
		  SAVE_VALUES(VALUES_1(internal_namestring));
	      }
	      POP_UNWIND_PROTECT(0);
	      SVREF(pathname_qm,FIX((SI_Long)6L)) = 
		      old_gensym_pathname_version;
	      SVREF(pathname_qm,FIX((SI_Long)5L)) = old_gensym_pathname_type;
	      SVREF(pathname_qm,FIX((SI_Long)4L)) = old_gensym_pathname_name;
	      SVREF(pathname_qm,FIX((SI_Long)3L)) = 
		      old_gensym_pathname_directory;
	      SVREF(pathname_qm,FIX((SI_Long)1L)) = old_gensym_pathname_host;
	      CONTINUE_UNWINDING(0);
	  }
	  else
	      SAVE_VALUES(copy_constant_wide_string_given_length(array_constant_2,
		      FIX((SI_Long)0L)));
      }
      POP_UNWIND_PROTECT(1);
      if (pathname_qm) {
	  if ( !EQ(pathname_qm,Qunbound_in_protected_let)) {
	      if (pathname_qm)
		  reclaim_gensym_pathname(pathname_qm);
	  }
      }
      CONTINUE_UNWINDING(1);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* GENSYM-DIRECTORY-NAMESTRING */
Object gensym_directory_namestring varargs_1(int, n)
{
    Object convertible_thing;
    Object prefer_lowercase_p, current_local_filename_parser;
    Object current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object pathname_qm;
    Object old_gensym_pathname_version, old_gensym_pathname_type;
    Object old_gensym_pathname_name, old_gensym_pathname_device;
    Object old_gensym_pathname_host, gensymed_symbol, component, ab_loop_list_;
    Object temp, internal_namestring;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(1);
    Object result;

    x_note_fn_call(39,69);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    prefer_lowercase_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    current_local_filename_parser = Local_filename_parser;
    current_local_namestring_generator = Local_namestring_generator;
    convert_file_strings_to_uppercase_p = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	    Qconvert_file_strings_to_uppercase_p);
    PUSH_SPECIAL_WITH_SYMBOL(Convert_file_strings_to_uppercase_p,Qconvert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      pathname_qm = Qunbound_in_protected_let;
      if (PUSH_UNWIND_PROTECT(1)) {
	  pathname_qm = convert_to_gensym_pathname(convertible_thing,
		  current_local_filename_parser,
		  current_local_namestring_generator);
	  if (pathname_qm) {
	      old_gensym_pathname_version = ISVREF(pathname_qm,(SI_Long)6L);
	      old_gensym_pathname_type = ISVREF(pathname_qm,(SI_Long)5L);
	      old_gensym_pathname_name = ISVREF(pathname_qm,(SI_Long)4L);
	      old_gensym_pathname_device = ISVREF(pathname_qm,(SI_Long)2L);
	      old_gensym_pathname_host = ISVREF(pathname_qm,(SI_Long)1L);
	      if (PUSH_UNWIND_PROTECT(0)) {
		  SVREF(pathname_qm,FIX((SI_Long)6L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)5L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)4L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)2L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)1L)) = Nil;
		  gensymed_symbol = ISVREF(pathname_qm,(SI_Long)8L);
		  if (getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			  Qconvert_file_strings_to_uppercase_p) ? 
			  TRUEP(prefer_lowercase_p) : TRUEP(Nil)) {
		      component = Nil;
		      ab_loop_list_ = ISVREF(pathname_qm,(SI_Long)3L);
		    next_loop:
		      if ( !TRUEP(ab_loop_list_))
			  goto end_loop;
		      component = M_CAR(ab_loop_list_);
		      ab_loop_list_ = M_CDR(ab_loop_list_);
		      if (text_string_p(component)) {
			  if ( 
				  !TRUEP(wild_regular_expression_string_p(component)))
			      nstring_downcasew(component);
		      }
		      goto next_loop;
		    end_loop:;
		  }
		  temp = ISVREF(pathname_qm,(SI_Long)10L);
		  internal_namestring = FUNCALL_1(temp,pathname_qm);
		  SAVE_VALUES(VALUES_1(internal_namestring));
	      }
	      POP_UNWIND_PROTECT(0);
	      SVREF(pathname_qm,FIX((SI_Long)6L)) = 
		      old_gensym_pathname_version;
	      SVREF(pathname_qm,FIX((SI_Long)5L)) = old_gensym_pathname_type;
	      SVREF(pathname_qm,FIX((SI_Long)4L)) = old_gensym_pathname_name;
	      SVREF(pathname_qm,FIX((SI_Long)2L)) = old_gensym_pathname_device;
	      SVREF(pathname_qm,FIX((SI_Long)1L)) = old_gensym_pathname_host;
	      CONTINUE_UNWINDING(0);
	  }
	  else
	      SAVE_VALUES(copy_constant_wide_string_given_length(array_constant_2,
		      FIX((SI_Long)0L)));
      }
      POP_UNWIND_PROTECT(1);
      if (pathname_qm) {
	  if ( !EQ(pathname_qm,Qunbound_in_protected_let)) {
	      if (pathname_qm)
		  reclaim_gensym_pathname(pathname_qm);
	  }
      }
      CONTINUE_UNWINDING(1);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* GENSYM-DIRECTORY-NAMESTRING-AS-TEXT-STRING */
Object gensym_directory_namestring_as_text_string varargs_1(int, n)
{
    Object convertible_thing;
    Object prefer_lowercase_p, namestring_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(39,70);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    prefer_lowercase_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    namestring_1 = gensym_directory_namestring(2,convertible_thing,
	    prefer_lowercase_p);
    return VALUES_1(namestring_1);
}

/* GENSYM-BASE-NAMESTRING */
Object gensym_base_namestring varargs_1(int, n)
{
    Object convertible_thing;
    Object prefer_lowercase_p, current_local_filename_parser;
    Object current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object pathname_qm;
    Object old_gensym_pathname_version, old_gensym_pathname_type;
    Object old_gensym_pathname_directory, old_gensym_pathname_device;
    Object old_gensym_pathname_host, gensymed_symbol, component, temp;
    Object internal_namestring;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(1);
    Object result;

    x_note_fn_call(39,71);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    prefer_lowercase_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    current_local_filename_parser = Local_filename_parser;
    current_local_namestring_generator = Local_namestring_generator;
    convert_file_strings_to_uppercase_p = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	    Qconvert_file_strings_to_uppercase_p);
    PUSH_SPECIAL_WITH_SYMBOL(Convert_file_strings_to_uppercase_p,Qconvert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      pathname_qm = Qunbound_in_protected_let;
      if (PUSH_UNWIND_PROTECT(1)) {
	  pathname_qm = convert_to_gensym_pathname(convertible_thing,
		  current_local_filename_parser,
		  current_local_namestring_generator);
	  if (pathname_qm) {
	      old_gensym_pathname_version = ISVREF(pathname_qm,(SI_Long)6L);
	      old_gensym_pathname_type = ISVREF(pathname_qm,(SI_Long)5L);
	      old_gensym_pathname_directory = ISVREF(pathname_qm,(SI_Long)3L);
	      old_gensym_pathname_device = ISVREF(pathname_qm,(SI_Long)2L);
	      old_gensym_pathname_host = ISVREF(pathname_qm,(SI_Long)1L);
	      if (PUSH_UNWIND_PROTECT(0)) {
		  SVREF(pathname_qm,FIX((SI_Long)6L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)5L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)3L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)2L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)1L)) = Nil;
		  gensymed_symbol = ISVREF(pathname_qm,(SI_Long)8L);
		  if (getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			  Qconvert_file_strings_to_uppercase_p) ? 
			  TRUEP(prefer_lowercase_p) : TRUEP(Nil)) {
		      component = ISVREF(pathname_qm,(SI_Long)4L);
		      if (text_string_p(component)) {
			  if ( 
				  !TRUEP(wild_regular_expression_string_p(component)))
			      nstring_downcasew(component);
		      }
		  }
		  temp = ISVREF(pathname_qm,(SI_Long)10L);
		  internal_namestring = FUNCALL_1(temp,pathname_qm);
		  SAVE_VALUES(VALUES_1(internal_namestring));
	      }
	      POP_UNWIND_PROTECT(0);
	      SVREF(pathname_qm,FIX((SI_Long)6L)) = 
		      old_gensym_pathname_version;
	      SVREF(pathname_qm,FIX((SI_Long)5L)) = old_gensym_pathname_type;
	      SVREF(pathname_qm,FIX((SI_Long)3L)) = 
		      old_gensym_pathname_directory;
	      SVREF(pathname_qm,FIX((SI_Long)2L)) = old_gensym_pathname_device;
	      SVREF(pathname_qm,FIX((SI_Long)1L)) = old_gensym_pathname_host;
	      CONTINUE_UNWINDING(0);
	  }
	  else
	      SAVE_VALUES(copy_constant_wide_string_given_length(array_constant_2,
		      FIX((SI_Long)0L)));
      }
      POP_UNWIND_PROTECT(1);
      if (pathname_qm) {
	  if ( !EQ(pathname_qm,Qunbound_in_protected_let)) {
	      if (pathname_qm)
		  reclaim_gensym_pathname(pathname_qm);
	  }
      }
      CONTINUE_UNWINDING(1);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* GENSYM-TYPE-NAMESTRING */
Object gensym_type_namestring varargs_1(int, n)
{
    Object convertible_thing;
    Object prefer_lowercase_p, current_local_filename_parser;
    Object current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object pathname_qm;
    Object old_gensym_pathname_version, old_gensym_pathname_name;
    Object old_gensym_pathname_directory, old_gensym_pathname_device;
    Object old_gensym_pathname_host, gensymed_symbol, component, temp;
    Object internal_namestring;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(1);
    Object result;

    x_note_fn_call(39,72);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    prefer_lowercase_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    current_local_filename_parser = Local_filename_parser;
    current_local_namestring_generator = Local_namestring_generator;
    convert_file_strings_to_uppercase_p = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	    Qconvert_file_strings_to_uppercase_p);
    PUSH_SPECIAL_WITH_SYMBOL(Convert_file_strings_to_uppercase_p,Qconvert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      pathname_qm = Qunbound_in_protected_let;
      if (PUSH_UNWIND_PROTECT(1)) {
	  pathname_qm = convert_to_gensym_pathname(convertible_thing,
		  current_local_filename_parser,
		  current_local_namestring_generator);
	  if (pathname_qm) {
	      old_gensym_pathname_version = ISVREF(pathname_qm,(SI_Long)6L);
	      old_gensym_pathname_name = ISVREF(pathname_qm,(SI_Long)4L);
	      old_gensym_pathname_directory = ISVREF(pathname_qm,(SI_Long)3L);
	      old_gensym_pathname_device = ISVREF(pathname_qm,(SI_Long)2L);
	      old_gensym_pathname_host = ISVREF(pathname_qm,(SI_Long)1L);
	      if (PUSH_UNWIND_PROTECT(0)) {
		  SVREF(pathname_qm,FIX((SI_Long)6L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)4L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)3L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)2L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)1L)) = Nil;
		  gensymed_symbol = ISVREF(pathname_qm,(SI_Long)8L);
		  if (getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			  Qconvert_file_strings_to_uppercase_p) ? 
			  TRUEP(prefer_lowercase_p) : TRUEP(Nil)) {
		      component = ISVREF(pathname_qm,(SI_Long)5L);
		      if (text_string_p(component)) {
			  if ( 
				  !TRUEP(wild_regular_expression_string_p(component)))
			      nstring_downcasew(component);
		      }
		  }
		  temp = ISVREF(pathname_qm,(SI_Long)10L);
		  internal_namestring = FUNCALL_1(temp,pathname_qm);
		  SAVE_VALUES(VALUES_1(internal_namestring));
	      }
	      POP_UNWIND_PROTECT(0);
	      SVREF(pathname_qm,FIX((SI_Long)6L)) = 
		      old_gensym_pathname_version;
	      SVREF(pathname_qm,FIX((SI_Long)4L)) = old_gensym_pathname_name;
	      SVREF(pathname_qm,FIX((SI_Long)3L)) = 
		      old_gensym_pathname_directory;
	      SVREF(pathname_qm,FIX((SI_Long)2L)) = old_gensym_pathname_device;
	      SVREF(pathname_qm,FIX((SI_Long)1L)) = old_gensym_pathname_host;
	      CONTINUE_UNWINDING(0);
	  }
	  else
	      SAVE_VALUES(copy_constant_wide_string_given_length(array_constant_2,
		      FIX((SI_Long)0L)));
      }
      POP_UNWIND_PROTECT(1);
      if (pathname_qm) {
	  if ( !EQ(pathname_qm,Qunbound_in_protected_let)) {
	      if (pathname_qm)
		  reclaim_gensym_pathname(pathname_qm);
	  }
      }
      CONTINUE_UNWINDING(1);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* GENSYM-VERSION-NAMESTRING */
Object gensym_version_namestring varargs_1(int, n)
{
    Object convertible_thing;
    Object prefer_lowercase_p, current_local_filename_parser;
    Object current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object pathname_qm;
    Object old_gensym_pathname_type, old_gensym_pathname_name;
    Object old_gensym_pathname_directory, old_gensym_pathname_device;
    Object old_gensym_pathname_host, gensymed_symbol, component, temp;
    Object internal_namestring;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(1);
    Object result;

    x_note_fn_call(39,73);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    prefer_lowercase_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    current_local_filename_parser = Local_filename_parser;
    current_local_namestring_generator = Local_namestring_generator;
    convert_file_strings_to_uppercase_p = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	    Qconvert_file_strings_to_uppercase_p);
    PUSH_SPECIAL_WITH_SYMBOL(Convert_file_strings_to_uppercase_p,Qconvert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      pathname_qm = Qunbound_in_protected_let;
      if (PUSH_UNWIND_PROTECT(1)) {
	  pathname_qm = convert_to_gensym_pathname(convertible_thing,
		  current_local_filename_parser,
		  current_local_namestring_generator);
	  if (pathname_qm) {
	      old_gensym_pathname_type = ISVREF(pathname_qm,(SI_Long)5L);
	      old_gensym_pathname_name = ISVREF(pathname_qm,(SI_Long)4L);
	      old_gensym_pathname_directory = ISVREF(pathname_qm,(SI_Long)3L);
	      old_gensym_pathname_device = ISVREF(pathname_qm,(SI_Long)2L);
	      old_gensym_pathname_host = ISVREF(pathname_qm,(SI_Long)1L);
	      if (PUSH_UNWIND_PROTECT(0)) {
		  SVREF(pathname_qm,FIX((SI_Long)5L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)4L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)3L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)2L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)1L)) = Nil;
		  gensymed_symbol = ISVREF(pathname_qm,(SI_Long)8L);
		  if (getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			  Qconvert_file_strings_to_uppercase_p) ? 
			  TRUEP(prefer_lowercase_p) : TRUEP(Nil)) {
		      component = ISVREF(pathname_qm,(SI_Long)6L);
		      if (text_string_p(component)) {
			  if ( 
				  !TRUEP(wild_regular_expression_string_p(component)))
			      nstring_downcasew(component);
		      }
		  }
		  temp = ISVREF(pathname_qm,(SI_Long)10L);
		  internal_namestring = FUNCALL_1(temp,pathname_qm);
		  SAVE_VALUES(VALUES_1(internal_namestring));
	      }
	      POP_UNWIND_PROTECT(0);
	      SVREF(pathname_qm,FIX((SI_Long)5L)) = old_gensym_pathname_type;
	      SVREF(pathname_qm,FIX((SI_Long)4L)) = old_gensym_pathname_name;
	      SVREF(pathname_qm,FIX((SI_Long)3L)) = 
		      old_gensym_pathname_directory;
	      SVREF(pathname_qm,FIX((SI_Long)2L)) = old_gensym_pathname_device;
	      SVREF(pathname_qm,FIX((SI_Long)1L)) = old_gensym_pathname_host;
	      CONTINUE_UNWINDING(0);
	  }
	  else
	      SAVE_VALUES(copy_constant_wide_string_given_length(array_constant_2,
		      FIX((SI_Long)0L)));
      }
      POP_UNWIND_PROTECT(1);
      if (pathname_qm) {
	  if ( !EQ(pathname_qm,Qunbound_in_protected_let)) {
	      if (pathname_qm)
		  reclaim_gensym_pathname(pathname_qm);
	  }
      }
      CONTINUE_UNWINDING(1);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* GENSYM-NAMESTRING-OF-DIRECTORY-AS-FILE */
Object gensym_namestring_of_directory_as_file(pathname_1)
    Object pathname_1;
{
    Object directory_1;
    volatile Object all_but_last_of_directory;
    volatile Object pathname_of_directory_as_file;
    Object len, dn, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object ab_loop_iter_flag_, temp, temp_1, temp_2, temp_3;
    SI_Long i;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(39,74);
    SAVE_STACK();
    directory_1 = Qunbound_in_protected_let;
    all_but_last_of_directory = Qunbound_in_protected_let;
    pathname_of_directory_as_file = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	directory_1 = ISVREF(pathname_1,(SI_Long)3L);
	if (LISTP(directory_1)) {
	    len = Nil;
	    dn = Nil;
	    ab_loop_list_ = directory_1;
	    i = (SI_Long)1L;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	    ab_loop_iter_flag_ = T;
	  next_loop:
	    len = length(directory_1);
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    dn = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(ab_loop_iter_flag_))
		i = i + (SI_Long)1L;
	    if ( !(i == IFIX(len))) {
		ab_loopvar__2 = gensym_cons_1(dn,Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
	    }
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop;
	  end_loop:
	    all_but_last_of_directory = ab_loopvar_;
	    goto end_1;
	    all_but_last_of_directory = Qnil;
	  end_1:;
	}
	else
	    all_but_last_of_directory = directory_1;
	temp = ISVREF(pathname_1,(SI_Long)1L);
	temp_1 = ISVREF(pathname_1,(SI_Long)2L);
	temp_2 = all_but_last_of_directory;
	if (CONSP(directory_1)) {
	    temp_3 = last(directory_1,_);
	    temp_3 = CAR(temp_3);
	}
	else
	    temp_3 = Nil;
	pathname_of_directory_as_file = 
		gensym_make_pathname_with_copied_components(temp,temp_1,
		temp_2,temp_3,Nil,Nil,Nil);
	SAVE_VALUES(gensym_namestring(1,pathname_of_directory_as_file));
    }
    POP_UNWIND_PROTECT(0);
    if (pathname_of_directory_as_file) {
	if ( !EQ(pathname_of_directory_as_file,Qunbound_in_protected_let))
	    reclaim_gensym_pathname(pathname_of_directory_as_file);
    }
    if (all_but_last_of_directory) {
	if ( !EQ(all_but_last_of_directory,Qunbound_in_protected_let)) {
	    if (CONSP(all_but_last_of_directory))
		reclaim_gensym_list_1(all_but_last_of_directory);
	}
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* GENSYM-HOST-AND-DIRECTORY-NAMESTRING */
Object gensym_host_and_directory_namestring varargs_1(int, n)
{
    Object convertible_thing;
    Object prefer_lowercase_p, current_local_filename_parser;
    Object current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object pathname_qm;
    Object old_gensym_pathname_version, old_gensym_pathname_type;
    Object old_gensym_pathname_name, old_gensym_pathname_device;
    Object gensymed_symbol, component, ab_loop_list_, temp;
    Object internal_namestring;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(1);
    Object result;

    x_note_fn_call(39,75);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    prefer_lowercase_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    current_local_filename_parser = Local_filename_parser;
    current_local_namestring_generator = Local_namestring_generator;
    convert_file_strings_to_uppercase_p = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	    Qconvert_file_strings_to_uppercase_p);
    PUSH_SPECIAL_WITH_SYMBOL(Convert_file_strings_to_uppercase_p,Qconvert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      pathname_qm = Qunbound_in_protected_let;
      if (PUSH_UNWIND_PROTECT(1)) {
	  pathname_qm = convert_to_gensym_pathname(convertible_thing,
		  current_local_filename_parser,
		  current_local_namestring_generator);
	  if (pathname_qm) {
	      old_gensym_pathname_version = ISVREF(pathname_qm,(SI_Long)6L);
	      old_gensym_pathname_type = ISVREF(pathname_qm,(SI_Long)5L);
	      old_gensym_pathname_name = ISVREF(pathname_qm,(SI_Long)4L);
	      old_gensym_pathname_device = ISVREF(pathname_qm,(SI_Long)2L);
	      if (PUSH_UNWIND_PROTECT(0)) {
		  SVREF(pathname_qm,FIX((SI_Long)6L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)5L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)4L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)2L)) = Nil;
		  gensymed_symbol = ISVREF(pathname_qm,(SI_Long)8L);
		  if (getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			  Qconvert_file_strings_to_uppercase_p) ? 
			  TRUEP(prefer_lowercase_p) : TRUEP(Nil)) {
		      component = ISVREF(pathname_qm,(SI_Long)1L);
		      if (text_string_p(component)) {
			  if ( 
				  !TRUEP(wild_regular_expression_string_p(component)))
			      nstring_downcasew(component);
		      }
		      component = Nil;
		      ab_loop_list_ = ISVREF(pathname_qm,(SI_Long)3L);
		    next_loop:
		      if ( !TRUEP(ab_loop_list_))
			  goto end_loop;
		      component = M_CAR(ab_loop_list_);
		      ab_loop_list_ = M_CDR(ab_loop_list_);
		      if (text_string_p(component)) {
			  if ( 
				  !TRUEP(wild_regular_expression_string_p(component)))
			      nstring_downcasew(component);
		      }
		      goto next_loop;
		    end_loop:;
		  }
		  temp = ISVREF(pathname_qm,(SI_Long)10L);
		  internal_namestring = FUNCALL_1(temp,pathname_qm);
		  SAVE_VALUES(VALUES_1(internal_namestring));
	      }
	      POP_UNWIND_PROTECT(0);
	      SVREF(pathname_qm,FIX((SI_Long)6L)) = 
		      old_gensym_pathname_version;
	      SVREF(pathname_qm,FIX((SI_Long)5L)) = old_gensym_pathname_type;
	      SVREF(pathname_qm,FIX((SI_Long)4L)) = old_gensym_pathname_name;
	      SVREF(pathname_qm,FIX((SI_Long)2L)) = old_gensym_pathname_device;
	      CONTINUE_UNWINDING(0);
	  }
	  else
	      SAVE_VALUES(copy_constant_wide_string_given_length(array_constant_2,
		      FIX((SI_Long)0L)));
      }
      POP_UNWIND_PROTECT(1);
      if (pathname_qm) {
	  if ( !EQ(pathname_qm,Qunbound_in_protected_let)) {
	      if (pathname_qm)
		  reclaim_gensym_pathname(pathname_qm);
	  }
      }
      CONTINUE_UNWINDING(1);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object string_constant_3;   /* "~a*.*" */

/* GENSYM-DIRECTORY-AND-WILDCARD-FILE-NAMESTRING */
Object gensym_directory_and_wildcard_file_namestring varargs_1(int, n)
{
    Object convertible_thing;
    Object prefer_lowercase_p, host_and_directory_namestring, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(39,76);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    prefer_lowercase_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    host_and_directory_namestring = gensym_host_and_directory_namestring(2,
	    convertible_thing,prefer_lowercase_p);
    temp = tformat_text_string(2,string_constant_3,
	    host_and_directory_namestring);
    reclaim_text_string(host_and_directory_namestring);
    return VALUES_1(temp);
}

/* GENSYM-DEVICE-AND-DIRECTORY-NAMESTRING */
Object gensym_device_and_directory_namestring varargs_1(int, n)
{
    Object convertible_thing;
    Object prefer_lowercase_p, current_local_filename_parser;
    Object current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object pathname_qm;
    Object old_gensym_pathname_version, old_gensym_pathname_type;
    Object old_gensym_pathname_name, old_gensym_pathname_host, gensymed_symbol;
    Object component, ab_loop_list_, temp, internal_namestring;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(1);
    Object result;

    x_note_fn_call(39,77);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    prefer_lowercase_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    current_local_filename_parser = Local_filename_parser;
    current_local_namestring_generator = Local_namestring_generator;
    convert_file_strings_to_uppercase_p = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	    Qconvert_file_strings_to_uppercase_p);
    PUSH_SPECIAL_WITH_SYMBOL(Convert_file_strings_to_uppercase_p,Qconvert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      pathname_qm = Qunbound_in_protected_let;
      if (PUSH_UNWIND_PROTECT(1)) {
	  pathname_qm = convert_to_gensym_pathname(convertible_thing,
		  current_local_filename_parser,
		  current_local_namestring_generator);
	  if (pathname_qm) {
	      old_gensym_pathname_version = ISVREF(pathname_qm,(SI_Long)6L);
	      old_gensym_pathname_type = ISVREF(pathname_qm,(SI_Long)5L);
	      old_gensym_pathname_name = ISVREF(pathname_qm,(SI_Long)4L);
	      old_gensym_pathname_host = ISVREF(pathname_qm,(SI_Long)1L);
	      if (PUSH_UNWIND_PROTECT(0)) {
		  SVREF(pathname_qm,FIX((SI_Long)6L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)5L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)4L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)1L)) = Nil;
		  gensymed_symbol = ISVREF(pathname_qm,(SI_Long)8L);
		  if (getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			  Qconvert_file_strings_to_uppercase_p) ? 
			  TRUEP(prefer_lowercase_p) : TRUEP(Nil)) {
		      component = ISVREF(pathname_qm,(SI_Long)2L);
		      if (text_string_p(component)) {
			  if ( 
				  !TRUEP(wild_regular_expression_string_p(component)))
			      nstring_downcasew(component);
		      }
		      component = Nil;
		      ab_loop_list_ = ISVREF(pathname_qm,(SI_Long)3L);
		    next_loop:
		      if ( !TRUEP(ab_loop_list_))
			  goto end_loop;
		      component = M_CAR(ab_loop_list_);
		      ab_loop_list_ = M_CDR(ab_loop_list_);
		      if (text_string_p(component)) {
			  if ( 
				  !TRUEP(wild_regular_expression_string_p(component)))
			      nstring_downcasew(component);
		      }
		      goto next_loop;
		    end_loop:;
		  }
		  temp = ISVREF(pathname_qm,(SI_Long)10L);
		  internal_namestring = FUNCALL_1(temp,pathname_qm);
		  SAVE_VALUES(VALUES_1(internal_namestring));
	      }
	      POP_UNWIND_PROTECT(0);
	      SVREF(pathname_qm,FIX((SI_Long)6L)) = 
		      old_gensym_pathname_version;
	      SVREF(pathname_qm,FIX((SI_Long)5L)) = old_gensym_pathname_type;
	      SVREF(pathname_qm,FIX((SI_Long)4L)) = old_gensym_pathname_name;
	      SVREF(pathname_qm,FIX((SI_Long)1L)) = old_gensym_pathname_host;
	      CONTINUE_UNWINDING(0);
	  }
	  else
	      SAVE_VALUES(copy_constant_wide_string_given_length(array_constant_2,
		      FIX((SI_Long)0L)));
      }
      POP_UNWIND_PROTECT(1);
      if (pathname_qm) {
	  if ( !EQ(pathname_qm,Qunbound_in_protected_let)) {
	      if (pathname_qm)
		  reclaim_gensym_pathname(pathname_qm);
	  }
      }
      CONTINUE_UNWINDING(1);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* GENSYM-DIRECTORY-AND-ABOVE-NAMESTRING */
Object gensym_directory_and_above_namestring varargs_1(int, n)
{
    Object convertible_thing;
    Object prefer_lowercase_p, current_local_filename_parser;
    Object current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object pathname_qm;
    Object old_gensym_pathname_version, old_gensym_pathname_type;
    Object old_gensym_pathname_name, gensymed_symbol, component, ab_loop_list_;
    Object temp, internal_namestring;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(1);
    Object result;

    x_note_fn_call(39,78);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    prefer_lowercase_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    current_local_filename_parser = Local_filename_parser;
    current_local_namestring_generator = Local_namestring_generator;
    convert_file_strings_to_uppercase_p = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	    Qconvert_file_strings_to_uppercase_p);
    PUSH_SPECIAL_WITH_SYMBOL(Convert_file_strings_to_uppercase_p,Qconvert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      pathname_qm = Qunbound_in_protected_let;
      if (PUSH_UNWIND_PROTECT(1)) {
	  pathname_qm = convert_to_gensym_pathname(convertible_thing,
		  current_local_filename_parser,
		  current_local_namestring_generator);
	  if (pathname_qm) {
	      old_gensym_pathname_version = ISVREF(pathname_qm,(SI_Long)6L);
	      old_gensym_pathname_type = ISVREF(pathname_qm,(SI_Long)5L);
	      old_gensym_pathname_name = ISVREF(pathname_qm,(SI_Long)4L);
	      if (PUSH_UNWIND_PROTECT(0)) {
		  SVREF(pathname_qm,FIX((SI_Long)6L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)5L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)4L)) = Nil;
		  gensymed_symbol = ISVREF(pathname_qm,(SI_Long)8L);
		  if (getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			  Qconvert_file_strings_to_uppercase_p) ? 
			  TRUEP(prefer_lowercase_p) : TRUEP(Nil)) {
		      component = ISVREF(pathname_qm,(SI_Long)1L);
		      if (text_string_p(component)) {
			  if ( 
				  !TRUEP(wild_regular_expression_string_p(component)))
			      nstring_downcasew(component);
		      }
		      component = ISVREF(pathname_qm,(SI_Long)2L);
		      if (text_string_p(component)) {
			  if ( 
				  !TRUEP(wild_regular_expression_string_p(component)))
			      nstring_downcasew(component);
		      }
		      component = Nil;
		      ab_loop_list_ = ISVREF(pathname_qm,(SI_Long)3L);
		    next_loop:
		      if ( !TRUEP(ab_loop_list_))
			  goto end_loop;
		      component = M_CAR(ab_loop_list_);
		      ab_loop_list_ = M_CDR(ab_loop_list_);
		      if (text_string_p(component)) {
			  if ( 
				  !TRUEP(wild_regular_expression_string_p(component)))
			      nstring_downcasew(component);
		      }
		      goto next_loop;
		    end_loop:;
		  }
		  temp = ISVREF(pathname_qm,(SI_Long)10L);
		  internal_namestring = FUNCALL_1(temp,pathname_qm);
		  SAVE_VALUES(VALUES_1(internal_namestring));
	      }
	      POP_UNWIND_PROTECT(0);
	      SVREF(pathname_qm,FIX((SI_Long)6L)) = 
		      old_gensym_pathname_version;
	      SVREF(pathname_qm,FIX((SI_Long)5L)) = old_gensym_pathname_type;
	      SVREF(pathname_qm,FIX((SI_Long)4L)) = old_gensym_pathname_name;
	      CONTINUE_UNWINDING(0);
	  }
	  else
	      SAVE_VALUES(copy_constant_wide_string_given_length(array_constant_2,
		      FIX((SI_Long)0L)));
      }
      POP_UNWIND_PROTECT(1);
      if (pathname_qm) {
	  if ( !EQ(pathname_qm,Qunbound_in_protected_let)) {
	      if (pathname_qm)
		  reclaim_gensym_pathname(pathname_qm);
	  }
      }
      CONTINUE_UNWINDING(1);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* GENSYM-DIRECTORY-AND-ABOVE-NAMESTRING-AS-TEXT-STRING */
Object gensym_directory_and_above_namestring_as_text_string varargs_1(int, n)
{
    Object convertible_thing;
    Object prefer_lowercase_p, namestring_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(39,79);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    prefer_lowercase_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    namestring_1 = gensym_directory_and_above_namestring(2,
	    convertible_thing,prefer_lowercase_p);
    return VALUES_1(namestring_1);
}

/* GENSYM-NAME-AND-TYPE-NAMESTRING */
Object gensym_name_and_type_namestring varargs_1(int, n)
{
    Object convertible_thing;
    Object prefer_lowercase_p, current_local_filename_parser;
    Object current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object pathname_qm;
    Object old_gensym_pathname_version, old_gensym_pathname_directory;
    Object old_gensym_pathname_device, old_gensym_pathname_host;
    Object gensymed_symbol, component, temp, internal_namestring;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(1);
    Object result;

    x_note_fn_call(39,80);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    prefer_lowercase_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    current_local_filename_parser = Local_filename_parser;
    current_local_namestring_generator = Local_namestring_generator;
    convert_file_strings_to_uppercase_p = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	    Qconvert_file_strings_to_uppercase_p);
    PUSH_SPECIAL_WITH_SYMBOL(Convert_file_strings_to_uppercase_p,Qconvert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      pathname_qm = Qunbound_in_protected_let;
      if (PUSH_UNWIND_PROTECT(1)) {
	  pathname_qm = convert_to_gensym_pathname(convertible_thing,
		  current_local_filename_parser,
		  current_local_namestring_generator);
	  if (pathname_qm) {
	      old_gensym_pathname_version = ISVREF(pathname_qm,(SI_Long)6L);
	      old_gensym_pathname_directory = ISVREF(pathname_qm,(SI_Long)3L);
	      old_gensym_pathname_device = ISVREF(pathname_qm,(SI_Long)2L);
	      old_gensym_pathname_host = ISVREF(pathname_qm,(SI_Long)1L);
	      if (PUSH_UNWIND_PROTECT(0)) {
		  SVREF(pathname_qm,FIX((SI_Long)6L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)3L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)2L)) = Nil;
		  SVREF(pathname_qm,FIX((SI_Long)1L)) = Nil;
		  gensymed_symbol = ISVREF(pathname_qm,(SI_Long)8L);
		  if (getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			  Qconvert_file_strings_to_uppercase_p) ? 
			  TRUEP(prefer_lowercase_p) : TRUEP(Nil)) {
		      component = ISVREF(pathname_qm,(SI_Long)4L);
		      if (text_string_p(component)) {
			  if ( 
				  !TRUEP(wild_regular_expression_string_p(component)))
			      nstring_downcasew(component);
		      }
		      component = ISVREF(pathname_qm,(SI_Long)5L);
		      if (text_string_p(component)) {
			  if ( 
				  !TRUEP(wild_regular_expression_string_p(component)))
			      nstring_downcasew(component);
		      }
		  }
		  temp = ISVREF(pathname_qm,(SI_Long)10L);
		  internal_namestring = FUNCALL_1(temp,pathname_qm);
		  SAVE_VALUES(VALUES_1(internal_namestring));
	      }
	      POP_UNWIND_PROTECT(0);
	      SVREF(pathname_qm,FIX((SI_Long)6L)) = 
		      old_gensym_pathname_version;
	      SVREF(pathname_qm,FIX((SI_Long)3L)) = 
		      old_gensym_pathname_directory;
	      SVREF(pathname_qm,FIX((SI_Long)2L)) = old_gensym_pathname_device;
	      SVREF(pathname_qm,FIX((SI_Long)1L)) = old_gensym_pathname_host;
	      CONTINUE_UNWINDING(0);
	  }
	  else
	      SAVE_VALUES(copy_constant_wide_string_given_length(array_constant_2,
		      FIX((SI_Long)0L)));
      }
      POP_UNWIND_PROTECT(1);
      if (pathname_qm) {
	  if ( !EQ(pathname_qm,Qunbound_in_protected_let)) {
	      if (pathname_qm)
		  reclaim_gensym_pathname(pathname_qm);
	  }
      }
      CONTINUE_UNWINDING(1);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Qgensym_enough_namestring;  /* gensym-enough-namestring */

static Object Kabsolute;           /* :absolute */

static Object string_constant_4;   /* "" */

/* GENSYM-ENOUGH-NAMESTRING */
Object gensym_enough_namestring varargs_1(int, n)
{
    Object convertible_thing;
    Object default_1, tag_temp, current_local_filename_parser;
    Object current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object pathname_qm;
    volatile Object default_pathname_qm;
    Object file_system, temp, gensym_pathname_host1, gensym_pathname_device1;
    Object gensym_pathname_directory1, gensym_pathname_name1;
    Object gensym_pathname_type1, gensym_pathname_version1;
    Object gensym_pathname_host2, gensym_pathname_device2;
    Object gensym_pathname_directory2, gensym_pathname_name2;
    Object gensym_pathname_type2, gensym_pathname_version2;
    Object first_directory_component1, absolute_marker_to_restore_qm;
    Object component_1_qm, component_2_qm, reclaimable_components;
    Object gensym_pathname_directory1_old_value, temp_1;
    Object gensym_pathname_directory2_old_value, remaining_directory_qm;
    Object reclaimable_component, ab_loop_list_, path_pop_store, cons_1;
    Object next_cons, svref_arg_2, car_1, cdr_1;
    SI_Long number_of_components_dropped, count_1, ab_loop_bind_;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(2);
    Object result;

    x_note_fn_call(39,81);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    default_1 = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Gensym_default_pathname_defaults;
    END_ARGS_nonrelocating();
    tag_temp = UNIQUE_TAG(Qgensym_enough_namestring);
    if (PUSH_CATCH(tag_temp,1)) {
	current_local_filename_parser = Local_filename_parser;
	current_local_namestring_generator = Local_namestring_generator;
	convert_file_strings_to_uppercase_p = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
		Qconvert_file_strings_to_uppercase_p);
	PUSH_SPECIAL_WITH_SYMBOL(Convert_file_strings_to_uppercase_p,Qconvert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
		1);
	  pathname_qm = Qunbound_in_protected_let;
	  default_pathname_qm = Qunbound_in_protected_let;
	  if (PUSH_UNWIND_PROTECT(0)) {
	      pathname_qm = convert_to_gensym_pathname(convertible_thing,
		      current_local_filename_parser,
		      current_local_namestring_generator);
	      default_pathname_qm = convert_to_gensym_pathname(default_1,
		      current_local_filename_parser,
		      current_local_namestring_generator);
	      file_system = pathname_qm ? ISVREF(pathname_qm,(SI_Long)8L) :
		       Qnil;
	      if (pathname_qm && default_pathname_qm && EQ(file_system,
		      ISVREF(default_pathname_qm,(SI_Long)8L))) {
		  convert_file_strings_to_uppercase_p = 
			  getfq_function_no_default(INLINE_SYMBOL_PLIST(file_system),
			  Qconvert_file_strings_to_uppercase_p);
		  PUSH_SPECIAL_WITH_SYMBOL(Convert_file_strings_to_uppercase_p,Qconvert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
			  0);
		    temp = 
			    coalesce_directory_components(ISVREF(pathname_qm,
			    (SI_Long)3L));
		    SVREF(pathname_qm,FIX((SI_Long)3L)) = temp;
		    temp = 
			    coalesce_directory_components(ISVREF(default_pathname_qm,
			    (SI_Long)3L));
		    SVREF(default_pathname_qm,FIX((SI_Long)3L)) = temp;
		    gensym_pathname_host1 = ISVREF(pathname_qm,(SI_Long)1L);
		    gensym_pathname_device1 = ISVREF(pathname_qm,(SI_Long)2L);
		    gensym_pathname_directory1 = ISVREF(pathname_qm,
			    (SI_Long)3L);
		    gensym_pathname_name1 = ISVREF(pathname_qm,(SI_Long)4L);
		    gensym_pathname_type1 = ISVREF(pathname_qm,(SI_Long)5L);
		    gensym_pathname_version1 = ISVREF(pathname_qm,(SI_Long)6L);
		    gensym_pathname_host2 = ISVREF(default_pathname_qm,
			    (SI_Long)1L);
		    gensym_pathname_device2 = ISVREF(default_pathname_qm,
			    (SI_Long)2L);
		    gensym_pathname_directory2 = 
			    ISVREF(default_pathname_qm,(SI_Long)3L);
		    gensym_pathname_name2 = ISVREF(default_pathname_qm,
			    (SI_Long)4L);
		    gensym_pathname_type2 = ISVREF(default_pathname_qm,
			    (SI_Long)5L);
		    gensym_pathname_version2 = ISVREF(default_pathname_qm,
			    (SI_Long)6L);
		    if (gensym_pathname_contents_equal_p(gensym_pathname_host1,
			    gensym_pathname_host2)) {
			if (text_string_p(gensym_pathname_host1))
			    reclaim_text_string(gensym_pathname_host1);
			SVREF(pathname_qm,FIX((SI_Long)1L)) = Nil;
		    }
		    else if ( !TRUEP(Nil))
			goto provide_namestring;
		    if (gensym_pathname_contents_equal_p(gensym_pathname_device1,
			    gensym_pathname_device2)) {
			if (text_string_p(gensym_pathname_device1))
			    reclaim_text_string(gensym_pathname_device1);
			SVREF(pathname_qm,FIX((SI_Long)2L)) = Nil;
		    }
		    else if ( !TRUEP(Nil))
			goto provide_namestring;
		    first_directory_component1 = 
			    FIRST(gensym_pathname_directory1);
		    absolute_marker_to_restore_qm = 
			    EQ(first_directory_component1,Kabsolute) && 
			    EQ(first_directory_component1,
			    FIRST(gensym_pathname_directory2)) ? 
			    first_directory_component1 : Qnil;
		    component_1_qm = Nil;
		    component_2_qm = Nil;
		    number_of_components_dropped = (SI_Long)0L;
		    reclaimable_components = Nil;
		    component_1_qm = CAR(gensym_pathname_directory1);
		    component_2_qm = CAR(gensym_pathname_directory2);
		  next_loop:
		    if ( !((component_1_qm || component_2_qm) && 
			    gensym_pathname_contents_equal_p(component_1_qm,
			    component_2_qm)))
			goto end_loop;
		    gensym_pathname_directory1_old_value = 
			    gensym_pathname_directory1;
		    temp_1 = FIRST(gensym_pathname_directory1_old_value);
		    gensym_pathname_directory1 = 
			    REST(gensym_pathname_directory1_old_value);
		    reclaimable_components = path_cons_1(temp_1,
			    reclaimable_components);
		    gensym_pathname_directory2_old_value = 
			    gensym_pathname_directory2;
		    gensym_pathname_directory2 = 
			    REST(gensym_pathname_directory2_old_value);
		    component_1_qm = CAR(gensym_pathname_directory1);
		    component_2_qm = CAR(gensym_pathname_directory2);
		    number_of_components_dropped = 
			    number_of_components_dropped + (SI_Long)1L;
		    goto next_loop;
		  end_loop:
		    remaining_directory_qm = 
			    copy_list_using_path_conses_1(gensym_pathname_directory1);
		    reclaimable_component = Nil;
		    ab_loop_list_ = reclaimable_components;
		  next_loop_1:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop_1;
		    reclaimable_component = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    if (text_string_p(reclaimable_component))
			reclaim_text_string(reclaimable_component);
		    goto next_loop_1;
		  end_loop_1:
		    reclaim_path_list_1(reclaimable_components);
		    reclaim_path_list_1(ISVREF(pathname_qm,(SI_Long)3L));
		  next_loop_2:
		    if ( !EQ(CAR(remaining_directory_qm),Krelative))
			goto end_loop_2;
		    path_pop_store = Nil;
		    cons_1 = remaining_directory_qm;
		    if (cons_1) {
			path_pop_store = M_CAR(cons_1);
			next_cons = M_CDR(cons_1);
			inline_note_reclaim_cons(cons_1,Qpath);
			if (ISVREF(Available_path_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp = 
				    ISVREF(Available_path_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp) = cons_1;
			    temp = Available_path_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp,svref_arg_2) = cons_1;
			}
			else {
			    temp = Available_path_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp,svref_arg_2) = cons_1;
			    temp = Available_path_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp,svref_arg_2) = cons_1;
			}
			M_CDR(cons_1) = Nil;
		    }
		    else
			next_cons = Nil;
		    remaining_directory_qm = next_cons;
		    goto next_loop_2;
		  end_loop_2:
		    SVREF(pathname_qm,FIX((SI_Long)3L)) = 
			    remaining_directory_qm;
		    if (remaining_directory_qm) {
			if (absolute_marker_to_restore_qm && 
				number_of_components_dropped <= (SI_Long)1L) {
			    car_1 = Kabsolute;
			    cdr_1 = ISVREF(pathname_qm,(SI_Long)3L);
			    temp = path_cons_1(car_1,cdr_1);
			    SVREF(pathname_qm,FIX((SI_Long)3L)) = temp;
			}
			if (EQ(ISVREF(pathname_qm,(SI_Long)8L),Qvms) && 
				number_of_components_dropped >= (SI_Long)1L) {
			    car_1 = Krelative;
			    cdr_1 = ISVREF(pathname_qm,(SI_Long)3L);
			    temp = path_cons_1(car_1,cdr_1);
			    SVREF(pathname_qm,FIX((SI_Long)3L)) = temp;
			}
		    }
		    else {
			count_1 = (SI_Long)1L;
			ab_loop_bind_ = 
				IFIX(length(gensym_pathname_directory2));
		      next_loop_3:
			if (count_1 > ab_loop_bind_)
			    goto end_loop_3;
			car_1 = Kup;
			cdr_1 = ISVREF(pathname_qm,(SI_Long)3L);
			temp = path_cons_1(car_1,cdr_1);
			SVREF(pathname_qm,FIX((SI_Long)3L)) = temp;
			count_1 = count_1 + (SI_Long)1L;
			goto next_loop_3;
		      end_loop_3:;
		    }
		    if (gensym_pathname_contents_equal_p(gensym_pathname_name1,
			    gensym_pathname_name2)) {
			if (text_string_p(gensym_pathname_name1))
			    reclaim_text_string(gensym_pathname_name1);
			SVREF(pathname_qm,FIX((SI_Long)4L)) = Nil;
		    }
		    else if ( !TRUEP(T))
			goto provide_namestring;
		    if (gensym_pathname_contents_equal_p(gensym_pathname_type1,
			    gensym_pathname_type2)) {
			if (text_string_p(gensym_pathname_type1))
			    reclaim_text_string(gensym_pathname_type1);
			SVREF(pathname_qm,FIX((SI_Long)5L)) = Nil;
		    }
		    else if ( !TRUEP(T))
			goto provide_namestring;
		    if (gensym_pathname_contents_equal_p(gensym_pathname_version1,
			    gensym_pathname_version2)) {
			if (text_string_p(gensym_pathname_version1))
			    reclaim_text_string(gensym_pathname_version1);
			SVREF(pathname_qm,FIX((SI_Long)6L)) = Nil;
		    }
		    else if ( !TRUEP(T))
			goto provide_namestring;
		  provide_namestring:
		    result = gensym_namestring(1,pathname_qm);
		    THROW(tag_temp,result);
		    SAVE_VALUES(VALUES_1(Qnil));
		  POP_SPECIAL();
	      }
	      else
		  SAVE_VALUES(VALUES_1(string_constant_4));
	  }
	  POP_UNWIND_PROTECT(0);
	  if (default_pathname_qm) {
	      if ( !EQ(default_pathname_qm,Qunbound_in_protected_let)) {
		  if (default_pathname_qm)
		      reclaim_gensym_pathname(default_pathname_qm);
	      }
	  }
	  if (pathname_qm) {
	      if ( !EQ(pathname_qm,Qunbound_in_protected_let)) {
		  if (pathname_qm)
		      reclaim_gensym_pathname(pathname_qm);
	      }
	  }
	  CONTINUE_UNWINDING(0);
	  result = RESTORE_VALUES();
	POP_SPECIAL();
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(1);
    RESTORE_STACK();
    return result;
}

/* GENSYM-ENOUGH-NAMESTRING-AS-TEXT-STRING */
Object gensym_enough_namestring_as_text_string varargs_1(int, n)
{
    Object convertible_thing;
    Object default_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(39,82);
    INIT_ARGS_nonrelocating();
    convertible_thing = REQUIRED_ARG_nonrelocating();
    default_1 = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Gensym_default_pathname_defaults;
    END_ARGS_nonrelocating();
    return gensym_enough_namestring(2,convertible_thing,default_1);
}

/* GENSYM-PATHNAME-VERSION-EMPTY-P */
Object gensym_pathname_version_empty_p(pathname_1)
    Object pathname_1;
{
    Object version, temp;

    x_note_fn_call(39,83);
    version = ISVREF(pathname_1,(SI_Long)6L);
    temp =  !TRUEP(version) ? T : Nil;
    if (temp);
    else
	temp = EQ(version,Kunspecific) ? T : Nil;
    return VALUES_1(temp);
}

static Object list_constant_1;     /* # */

static Object list_constant_2;     /* # */

/* GENSYM-DIRECTORY-AS-FILE */
Object gensym_directory_as_file(convertible_thing)
    Object convertible_thing;
{
    Object current_local_filename_parser, current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p, pathname_qm;
    Object directory_subcomponents, svref_new_value, subcomponent_cons;
    Object pointer_to_last_subcomponent, last_subcomponent, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(39,84);
    current_local_filename_parser = Local_filename_parser;
    current_local_namestring_generator = Local_namestring_generator;
    convert_file_strings_to_uppercase_p = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	    Qconvert_file_strings_to_uppercase_p);
    PUSH_SPECIAL_WITH_SYMBOL(Convert_file_strings_to_uppercase_p,Qconvert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      pathname_qm = convert_to_gensym_pathname(convertible_thing,
	      current_local_filename_parser,
	      current_local_namestring_generator);
      if (pathname_qm) {
	  if (ISVREF(pathname_qm,(SI_Long)4L) || ISVREF(pathname_qm,
		  (SI_Long)5L) || ISVREF(pathname_qm,(SI_Long)6L)) {
	      reclaim_gensym_pathname(pathname_qm);
	      pathname_qm = Nil;
	  }
	  else {
	      directory_subcomponents = ISVREF(pathname_qm,(SI_Long)3L);
	      if ( !TRUEP(directory_subcomponents)) {
		  svref_new_value = path_cons_1(Kabsolute,Nil);
		  SVREF(pathname_qm,FIX((SI_Long)3L)) = svref_new_value;
	      }
	      else if (EQUAL(directory_subcomponents,list_constant_1));
	      else if (EQUAL(directory_subcomponents,list_constant)) {
		  reclaim_gensym_pathname(pathname_qm);
		  pathname_qm = Nil;
	      }
	      else {
		  if ( !TRUEP(memq_function(CAR(directory_subcomponents),
			  list_constant_2)))
		      directory_subcomponents = path_cons_1(Krelative,
			      directory_subcomponents);
		  subcomponent_cons = directory_subcomponents;
		next_loop:
		  if ( !TRUEP(subcomponent_cons))
		      goto end_loop;
		  if ( !TRUEP(CDDR(subcomponent_cons))) {
		      pointer_to_last_subcomponent = subcomponent_cons;
		      goto end_1;
		  }
		  subcomponent_cons = M_CDR(subcomponent_cons);
		  goto next_loop;
		end_loop:
		  pointer_to_last_subcomponent = Qnil;
		end_1:;
		  last_subcomponent = CADR(pointer_to_last_subcomponent);
		  M_CDR(pointer_to_last_subcomponent) = Nil;
		  temp = ISVREF(pathname_qm,(SI_Long)8L);
		  if (EQ(temp,Qunix))
		      SVREF(pathname_qm,FIX((SI_Long)4L)) = last_subcomponent;
		  else if (EQ(temp,Qvms)) {
		      SVREF(pathname_qm,FIX((SI_Long)4L)) = last_subcomponent;
		      svref_new_value = 
			      copy_constant_wide_string_given_length(array_constant_1,
			      FIX((SI_Long)3L));
		      SVREF(pathname_qm,FIX((SI_Long)5L)) = svref_new_value;
		  }
		  else if (EQ(temp,Qdos) || EQ(temp,Qwin32) || EQ(temp,
			  Qgeneralized_dos))
		      SVREF(pathname_qm,FIX((SI_Long)4L)) = last_subcomponent;
		  else {
		      reclaim_gensym_pathname(pathname_qm);
		      pathname_qm = Nil;
		  }
	      }
	  }
      }
      result = VALUES_1(pathname_qm);
    POP_SPECIAL();
    return result;
}

/* GENSYM-FILE-AS-DIRECTORY */
Object gensym_file_as_directory(convertible_thing)
    Object convertible_thing;
{
    Object current_local_filename_parser, current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p, pathname_qm, temp;
    Object final_directory_component, svref_new_value, pathname_name_1;
    Object pathname_type_1, pathname_version_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(39,85);
    current_local_filename_parser = Local_filename_parser;
    current_local_namestring_generator = Local_namestring_generator;
    convert_file_strings_to_uppercase_p = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	    Qconvert_file_strings_to_uppercase_p);
    PUSH_SPECIAL_WITH_SYMBOL(Convert_file_strings_to_uppercase_p,Qconvert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      pathname_qm = convert_to_gensym_pathname(convertible_thing,
	      current_local_filename_parser,
	      current_local_namestring_generator);
      if (pathname_qm) {
	  if (valid_directory_p(pathname_qm)) {
	      temp = ISVREF(pathname_qm,(SI_Long)8L);
	      final_directory_component = EQ(temp,Qunix) || EQ(temp,
		      Qwin32) || EQ(temp,Qdos) ? gensym_file_namestring(1,
		      pathname_qm) : copy_text_string(ISVREF(pathname_qm,
		      (SI_Long)4L));
	      svref_new_value = nconc2(ISVREF(pathname_qm,(SI_Long)3L),
		      path_cons_1(final_directory_component,Nil));
	      SVREF(pathname_qm,FIX((SI_Long)3L)) = svref_new_value;
	      pathname_name_1 = ISVREF(pathname_qm,(SI_Long)4L);
	      if (text_string_p(pathname_name_1))
		  reclaim_text_string(pathname_name_1);
	      SVREF(pathname_qm,FIX((SI_Long)4L)) = Nil;
	      pathname_type_1 = ISVREF(pathname_qm,(SI_Long)5L);
	      if (text_string_p(pathname_type_1))
		  reclaim_text_string(pathname_type_1);
	      SVREF(pathname_qm,FIX((SI_Long)5L)) = Nil;
	      pathname_version_1 = ISVREF(pathname_qm,(SI_Long)6L);
	      if (text_string_p(pathname_version_1))
		  reclaim_text_string(pathname_version_1);
	      SVREF(pathname_qm,FIX((SI_Long)6L)) = Nil;
	      result = VALUES_1(pathname_qm);
	  }
	  else {
	      reclaim_gensym_pathname(pathname_qm);
	      result = VALUES_1(Nil);
	  }
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* GET-NEW-DIRECTORY-PATHNAME-DWIM */
Object get_new_directory_pathname_dwim(new_directory_string)
    Object new_directory_string;
{
    Object raw_pathname_qm, raw_pathname_name, raw_pathname_type, temp;
    Object raw_pathname_version;

    x_note_fn_call(39,86);
    raw_pathname_qm = gensym_pathname(new_directory_string);
    if (raw_pathname_qm) {
	raw_pathname_name = ISVREF(raw_pathname_qm,(SI_Long)4L);
	raw_pathname_type = ISVREF(raw_pathname_qm,(SI_Long)5L);
	if ( !TRUEP(raw_pathname_name) &&  !TRUEP(raw_pathname_type) && 
		gensym_pathname_version_empty_p(raw_pathname_qm))
	    return VALUES_1(raw_pathname_qm);
	else if (g2_stream_directory_p(new_directory_string)) {
	    temp = gensym_file_as_directory(raw_pathname_qm);
	    reclaim_gensym_pathname(raw_pathname_qm);
	    return VALUES_1(temp);
	}
	else {
	    raw_pathname_version = ISVREF(raw_pathname_qm,(SI_Long)6L);
	    if (text_string_p(raw_pathname_name))
		reclaim_text_string(raw_pathname_name);
	    SVREF(raw_pathname_qm,FIX((SI_Long)4L)) = Nil;
	    if (text_string_p(raw_pathname_type))
		reclaim_text_string(raw_pathname_type);
	    SVREF(raw_pathname_qm,FIX((SI_Long)5L)) = Nil;
	    if (text_string_p(raw_pathname_version))
		reclaim_text_string(raw_pathname_version);
	    SVREF(raw_pathname_qm,FIX((SI_Long)6L)) = Nil;
	    return VALUES_1(raw_pathname_qm);
	}
    }
    else
	return VALUES_1(Nil);
}

/* GENSYM-PATHNAME */
Object gensym_pathname(convertible_thing)
    Object convertible_thing;
{
    Object current_local_filename_parser, current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p, pathname_qm, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(39,87);
    current_local_filename_parser = Local_filename_parser;
    current_local_namestring_generator = Local_namestring_generator;
    convert_file_strings_to_uppercase_p = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	    Qconvert_file_strings_to_uppercase_p);
    PUSH_SPECIAL_WITH_SYMBOL(Convert_file_strings_to_uppercase_p,Qconvert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      pathname_qm = convert_to_gensym_pathname(convertible_thing,
	      current_local_filename_parser,
	      current_local_namestring_generator);
      temp = pathname_qm;
      if (temp)
	  result = VALUES_1(temp);
      else
	  result = make_empty_gensym_pathname();
    POP_SPECIAL();
    return result;
}

/* GET-PARSER-FROM-HOST */
Object get_parser_from_host(host)
    Object host;
{
    x_note_fn_call(39,88);
    return get_default_file_system_info();
}

/* GET-PARSER-FROM-NAMESTRING */
Object get_parser_from_namestring(namestring_1)
    Object namestring_1;
{
    x_note_fn_call(39,89);
    return get_default_file_system_info();
}

/* PARSER-IN-NAMESTRING-P */
Object parser_in_namestring_p(namestring_1)
    Object namestring_1;
{
    x_note_fn_call(39,90);
    return VALUES_1(Nil);
}

/* GENSYM-PARSE-NAMESTRING-FUNCTION */
Object gensym_parse_namestring_function(convertible_thing,host,default_1)
    Object convertible_thing, host, default_1;
{
    Object current_local_filename_parser, current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object default_pathname_qm;
    Object host_for_conversion, filename_parser, namestring_generator;
    Object pathname_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(39,91);
    SAVE_STACK();
    current_local_filename_parser = Local_filename_parser;
    current_local_namestring_generator = Local_namestring_generator;
    convert_file_strings_to_uppercase_p = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
	    Qconvert_file_strings_to_uppercase_p);
    PUSH_SPECIAL_WITH_SYMBOL(Convert_file_strings_to_uppercase_p,Qconvert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      default_pathname_qm = Qunbound_in_protected_let;
      if (PUSH_UNWIND_PROTECT(0)) {
	  default_pathname_qm = convert_to_gensym_pathname(default_1,
		  current_local_filename_parser,
		  current_local_namestring_generator);
	  host_for_conversion = host;
	  if (host_for_conversion);
	  else
	      host_for_conversion = default_pathname_qm ? 
		      ISVREF(default_pathname_qm,(SI_Long)1L) : Qnil;
	  result = get_parser_from_host(host_for_conversion);
	  MVS_2(result,filename_parser,namestring_generator);
	  if ( !TRUEP(filename_parser)) {
	      filename_parser = Local_filename_parser;
	      namestring_generator = Local_namestring_generator;
	  }
	  pathname_qm = convert_to_gensym_pathname(convertible_thing,
		  filename_parser,namestring_generator);
	  if (pathname_qm) {
	      SVREF(pathname_qm,FIX((SI_Long)9L)) = filename_parser;
	      SVREF(pathname_qm,FIX((SI_Long)10L)) = namestring_generator;
	      SAVE_VALUES(VALUES_1(pathname_qm));
	  }
	  else
	      SAVE_VALUES(make_empty_gensym_pathname());
      }
      POP_UNWIND_PROTECT(0);
      if (default_pathname_qm) {
	  if ( !EQ(default_pathname_qm,Qunbound_in_protected_let)) {
	      if (default_pathname_qm)
		  reclaim_gensym_pathname(default_pathname_qm);
	  }
      }
      CONTINUE_UNWINDING(0);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object string_constant_5;   /* "GENSYM-TRUENAME: Cannot get pathname from stream ~a" */

static Object string_constant_6;   /* "GENSYM-TRUENAME: Cannot access file ~a" */

static Object string_constant_7;   /* "GENSYM-TRUENAME: Cannot obtain pathname for ~a" */

/* GENSYM-TRUENAME */
Object gensym_truename(convertible_thing)
    Object convertible_thing;
{
    Object pathname_from_stream_qm, temp, current_local_filename_parser;
    Object current_local_namestring_generator;
    Object convert_file_strings_to_uppercase_p;
    volatile Object pathname_qm;
    Object probed_pathname_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(39,92);
    SAVE_STACK();
    if (g2_stream_p(convertible_thing)) {
	pathname_from_stream_qm = gensym_probe_file(convertible_thing);
	temp = pathname_from_stream_qm;
	if (temp) {
	    RESTORE_STACK();
	    return VALUES_1(temp);
	}
	else {
	    result = signal_gensym_file_error(string_constant_5,
		    path_cons_1(convertible_thing,Nil));
	    RESTORE_STACK();
	    return result;
	}
    }
    else {
	current_local_filename_parser = Local_filename_parser;
	current_local_namestring_generator = Local_namestring_generator;
	convert_file_strings_to_uppercase_p = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(current_local_filename_parser),
		Qconvert_file_strings_to_uppercase_p);
	PUSH_SPECIAL_WITH_SYMBOL(Convert_file_strings_to_uppercase_p,Qconvert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
		0);
	  pathname_qm = Qunbound_in_protected_let;
	  if (PUSH_UNWIND_PROTECT(0)) {
	      pathname_qm = convert_to_gensym_pathname(convertible_thing,
		      current_local_filename_parser,
		      current_local_namestring_generator);
	      if (pathname_qm) {
		  probed_pathname_qm = gensym_probe_file(pathname_qm);
		  temp = probed_pathname_qm;
		  if (temp)
		      SAVE_VALUES(VALUES_1(temp));
		  else
		      SAVE_VALUES(signal_gensym_file_error(string_constant_6,
			      path_cons_1(convertible_thing,Nil)));
	      }
	      else
		  SAVE_VALUES(signal_gensym_file_error(string_constant_7,
			  path_cons_1(convertible_thing,Nil)));
	  }
	  POP_UNWIND_PROTECT(0);
	  if (pathname_qm) {
	      if ( !EQ(pathname_qm,Qunbound_in_protected_let)) {
		  if (pathname_qm)
		      reclaim_gensym_pathname(pathname_qm);
	      }
	  }
	  CONTINUE_UNWINDING(0);
	  result = RESTORE_VALUES();
	POP_SPECIAL();
	RESTORE_STACK();
	return result;
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Merge_pathnames_rules, Qmerge_pathnames_rules);

DEFINE_VARIABLE_WITH_SYMBOL(Merge_pathnames_rules_sorted_p, Qmerge_pathnames_rules_sorted_p);

/* TRANSFER-GENSYM-PATHNAME-CONTENTS */
Object transfer_gensym_pathname_contents(old_contents,new_contents)
    Object old_contents, new_contents;
{
    Object old_component, ab_loop_list_, new_component, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2;

    x_note_fn_call(39,93);
    if (CONSP(old_contents)) {
	old_component = Nil;
	ab_loop_list_ = old_contents;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	old_component = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (text_string_p(old_component))
	    reclaim_text_string(old_component);
	goto next_loop;
      end_loop:
	reclaim_path_list_1(old_contents);
    }
    else if (text_string_p(old_contents))
	reclaim_text_string(old_contents);
    if (CONSP(new_contents)) {
	new_component = Nil;
	ab_loop_list_ = new_contents;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	new_component = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = path_cons_1(text_string_p(new_component) ? 
		copy_text_string(new_component) : new_component,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(ab_loopvar_);
	return VALUES_1(Qnil);
    }
    else if (text_string_p(new_contents))
	return copy_text_string(new_contents);
    else
	return VALUES_1(new_contents);
}

/* GET-DEFAULT-FILE-DEVICE-FROM-HOST */
Object get_default_file_device_from_host(pathname_1)
    Object pathname_1;
{
    x_note_fn_call(39,94);
    return VALUES_1(Nil);
}

/* MERGE-PATHNAMES-DEVICE-DEFAULT-RULE */
Object merge_pathnames_device_default_rule varargs_1(int, n)
{
    Object original_pathname, pathname_1;
    Object defaults, old_contents, svref_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(39,95);
    INIT_ARGS_nonrelocating();
    original_pathname = REQUIRED_ARG_nonrelocating();
    pathname_1 = REQUIRED_ARG_nonrelocating();
    defaults = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (ISVREF(original_pathname,(SI_Long)1L) &&  
	    !TRUEP(ISVREF(original_pathname,(SI_Long)2L)) && 
	    string_eq_w(ISVREF(original_pathname,(SI_Long)1L),
	    ISVREF(defaults,(SI_Long)1L))) {
	old_contents = ISVREF(pathname_1,(SI_Long)2L);
	svref_new_value = transfer_gensym_pathname_contents(old_contents,
		ISVREF(defaults,(SI_Long)2L));
	return VALUES_1(SVREF(pathname_1,FIX((SI_Long)2L)) = svref_new_value);
    }
    else if (ISVREF(original_pathname,(SI_Long)1L) &&  
	    !TRUEP(ISVREF(original_pathname,(SI_Long)2L))) {
	if ( !EQ(ISVREF(original_pathname,(SI_Long)2L),Kunspecific)) {
	    old_contents = ISVREF(pathname_1,(SI_Long)2L);
	    svref_new_value = 
		    transfer_gensym_pathname_contents(old_contents,
		    get_default_file_device_from_host(original_pathname));
	    return VALUES_1(SVREF(pathname_1,FIX((SI_Long)2L)) = 
		    svref_new_value);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* MERGE-PATHNAMES-PROPAGATE-FILE-SYSTEM */
Object merge_pathnames_propagate_file_system varargs_1(int, n)
{
    Object original_pathname, pathname_1;
    Object defaults, svref_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(39,96);
    INIT_ARGS_nonrelocating();
    original_pathname = REQUIRED_ARG_nonrelocating();
    pathname_1 = REQUIRED_ARG_nonrelocating();
    defaults = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if ( !TRUEP(ISVREF(original_pathname,(SI_Long)1L))) {
	svref_new_value = ISVREF(defaults,(SI_Long)8L);
	SVREF(pathname_1,FIX((SI_Long)8L)) = svref_new_value;
	svref_new_value = ISVREF(defaults,(SI_Long)9L);
	SVREF(pathname_1,FIX((SI_Long)9L)) = svref_new_value;
	svref_new_value = ISVREF(defaults,(SI_Long)10L);
	return VALUES_1(SVREF(pathname_1,FIX((SI_Long)10L)) = svref_new_value);
    }
    else
	return VALUES_1(Nil);
}

/* MERGE-PATHNAMES-REPLACE-UNSPECIFIC-HOST */
Object merge_pathnames_replace_unspecific_host varargs_1(int, n)
{
    Object original_pathname, pathname_1;
    Object defaults, old_contents, svref_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(39,97);
    INIT_ARGS_nonrelocating();
    original_pathname = REQUIRED_ARG_nonrelocating();
    pathname_1 = REQUIRED_ARG_nonrelocating();
    defaults = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(ISVREF(original_pathname,(SI_Long)1L),Kunspecific) &&  ! 
	    !TRUEP(ISVREF(defaults,(SI_Long)1L))) {
	old_contents = ISVREF(pathname_1,(SI_Long)1L);
	svref_new_value = transfer_gensym_pathname_contents(old_contents,
		ISVREF(defaults,(SI_Long)1L));
	return VALUES_1(SVREF(pathname_1,FIX((SI_Long)1L)) = svref_new_value);
    }
    else
	return VALUES_1(Nil);
}

/* MERGE-PATHNAMES-REPLACE-EMPTY-COMPONENTS */
Object merge_pathnames_replace_empty_components varargs_1(int, n)
{
    Object original_pathname, pathname_1;
    Object defaults, old_contents, svref_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(39,98);
    INIT_ARGS_nonrelocating();
    original_pathname = REQUIRED_ARG_nonrelocating();
    pathname_1 = REQUIRED_ARG_nonrelocating();
    defaults = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if ( !TRUEP(ISVREF(original_pathname,(SI_Long)1L))) {
	old_contents = ISVREF(pathname_1,(SI_Long)1L);
	svref_new_value = transfer_gensym_pathname_contents(old_contents,
		ISVREF(defaults,(SI_Long)1L));
	SVREF(pathname_1,FIX((SI_Long)1L)) = svref_new_value;
    }
    if ( !TRUEP(ISVREF(original_pathname,(SI_Long)2L)) &&  
	    !(ISVREF(original_pathname,(SI_Long)1L) || 
	    EQ(ISVREF(pathname_1,(SI_Long)8L),Qvms) && 
	    ISVREF(original_pathname,(SI_Long)3L))) {
	old_contents = ISVREF(pathname_1,(SI_Long)2L);
	svref_new_value = transfer_gensym_pathname_contents(old_contents,
		ISVREF(defaults,(SI_Long)2L));
	SVREF(pathname_1,FIX((SI_Long)2L)) = svref_new_value;
    }
    if ( !TRUEP(ISVREF(original_pathname,(SI_Long)3L)) &&  
	    !(EQ(ISVREF(pathname_1,(SI_Long)8L),Qvms) && 
	    ISVREF(original_pathname,(SI_Long)2L))) {
	old_contents = ISVREF(pathname_1,(SI_Long)3L);
	svref_new_value = transfer_gensym_pathname_contents(old_contents,
		ISVREF(defaults,(SI_Long)3L));
	SVREF(pathname_1,FIX((SI_Long)3L)) = svref_new_value;
    }
    if ( !TRUEP(ISVREF(original_pathname,(SI_Long)4L))) {
	old_contents = ISVREF(pathname_1,(SI_Long)4L);
	svref_new_value = transfer_gensym_pathname_contents(old_contents,
		ISVREF(defaults,(SI_Long)4L));
	SVREF(pathname_1,FIX((SI_Long)4L)) = svref_new_value;
    }
    if ( !TRUEP(ISVREF(original_pathname,(SI_Long)5L))) {
	old_contents = ISVREF(pathname_1,(SI_Long)5L);
	svref_new_value = transfer_gensym_pathname_contents(old_contents,
		ISVREF(defaults,(SI_Long)5L));
	return VALUES_1(SVREF(pathname_1,FIX((SI_Long)5L)) = svref_new_value);
    }
    else
	return VALUES_1(Nil);
}

/* MERGE-PATHNAMES-VERSION-DEFAULT-RULE */
Object merge_pathnames_version_default_rule varargs_1(int, n)
{
    Object original_pathname, pathname_1;
    Object defaults, default_version, old_contents, svref_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(39,99);
    INIT_ARGS_nonrelocating();
    original_pathname = REQUIRED_ARG_nonrelocating();
    pathname_1 = REQUIRED_ARG_nonrelocating();
    defaults = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    default_version = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(ISVREF(original_pathname,(SI_Long)6L)) &&  
	    !TRUEP(ISVREF(original_pathname,(SI_Long)4L))) {
	old_contents = ISVREF(pathname_1,(SI_Long)6L);
	svref_new_value = transfer_gensym_pathname_contents(old_contents,
		ISVREF(defaults,(SI_Long)6L));
	SVREF(pathname_1,FIX((SI_Long)6L)) = svref_new_value;
    }
    if ( !TRUEP(ISVREF(pathname_1,(SI_Long)6L))) {
	old_contents = ISVREF(pathname_1,(SI_Long)6L);
	svref_new_value = transfer_gensym_pathname_contents(old_contents,
		default_version);
	return VALUES_1(SVREF(pathname_1,FIX((SI_Long)6L)) = svref_new_value);
    }
    else
	return VALUES_1(Nil);
}

/* ELIDE-DIRECTORY-CONTAINING-UP-WITH-DEFAULT-DIRECTORY */
Object elide_directory_containing_up_with_default_directory(directory_containing_up,
	    default_directory)
    Object directory_containing_up, default_directory;
{
    Object reversed_copy_of_default_directory_qm, directory_component;
    Object ab_loop_list_, path_pop_store, cons_1, next_cons, temp, svref_arg_2;
    Object temp_1;

    x_note_fn_call(39,100);
    reversed_copy_of_default_directory_qm = 
	    nreverse(copy_directory_contents(default_directory));
    directory_component = Nil;
    ab_loop_list_ = directory_containing_up;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    directory_component = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !(EQ(directory_component,Kup) && 
	    reversed_copy_of_default_directory_qm && 
	    text_string_p(CAR(reversed_copy_of_default_directory_qm))))
	goto end_loop;
    path_pop_store = Nil;
    cons_1 = directory_containing_up;
    if (cons_1) {
	path_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpath);
	if (ISVREF(Available_path_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_path_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_path_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_path_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_path_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    directory_containing_up = next_cons;
    path_pop_store = Nil;
    cons_1 = reversed_copy_of_default_directory_qm;
    if (cons_1) {
	path_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpath);
	if (ISVREF(Available_path_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_path_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_path_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_path_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_path_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    reversed_copy_of_default_directory_qm = next_cons;
    reclaim_text_string(path_pop_store);
    goto next_loop;
  end_loop:
    temp_1 = nreverse(reversed_copy_of_default_directory_qm);
    return VALUES_1(nconc2(temp_1,directory_containing_up));
    return VALUES_1(Qnil);
}

static Object list_constant_3;     /* # */

/* MERGE-PATHNAMES-MERGE-STRUCTURED-DIRECTORIES */
Object merge_pathnames_merge_structured_directories varargs_1(int, n)
{
    Object original_pathname, pathname_1;
    Object defaults, temp, directory_so_far, default_directory_qm;
    Object gensymed_symbol, first_component, second_component, path_pop_store;
    Object cons_1, next_cons, temp_2, svref_arg_2;
    Object default_directory_section_to_merge;
    char temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(39,101);
    INIT_ARGS_nonrelocating();
    original_pathname = REQUIRED_ARG_nonrelocating();
    pathname_1 = REQUIRED_ARG_nonrelocating();
    defaults = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (ISVREF(original_pathname,(SI_Long)3L)) {
	temp = ISVREF(pathname_1,(SI_Long)3L);
	temp_1 = TRUEP(memq_function(CAR(temp),list_constant_3));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	directory_so_far = ISVREF(pathname_1,(SI_Long)3L);
	default_directory_qm = ISVREF(defaults,(SI_Long)3L);
	if (default_directory_qm) {
	    gensymed_symbol = directory_so_far;
	    first_component = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    second_component = CAR(gensymed_symbol);
	    if (EQ(first_component,Krelative) && EQ(second_component,Kup)) {
		path_pop_store = Nil;
		cons_1 = directory_so_far;
		if (cons_1) {
		    path_pop_store = M_CAR(cons_1);
		    next_cons = M_CDR(cons_1);
		    inline_note_reclaim_cons(cons_1,Qpath);
		    if (ISVREF(Available_path_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_2 = ISVREF(Available_path_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_2) = cons_1;
			temp_2 = Available_path_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_2,svref_arg_2) = cons_1;
		    }
		    else {
			temp_2 = Available_path_conses_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_2,svref_arg_2) = cons_1;
			temp_2 = Available_path_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_2,svref_arg_2) = cons_1;
		    }
		    M_CDR(cons_1) = Nil;
		}
		else
		    next_cons = Nil;
		directory_so_far = next_cons;
		temp_2 = 
			elide_directory_containing_up_with_default_directory(directory_so_far,
			default_directory_qm);
		return VALUES_1(SVREF(pathname_1,FIX((SI_Long)3L)) = temp_2);
	    }
	    else if (EQ(first_component,Kup)) {
		temp_2 = 
			elide_directory_containing_up_with_default_directory(directory_so_far,
			default_directory_qm);
		return VALUES_1(SVREF(pathname_1,FIX((SI_Long)3L)) = temp_2);
	    }
	    else if (EQ(first_component,Krelative)) {
		path_pop_store = Nil;
		cons_1 = directory_so_far;
		if (cons_1) {
		    path_pop_store = M_CAR(cons_1);
		    next_cons = M_CDR(cons_1);
		    inline_note_reclaim_cons(cons_1,Qpath);
		    if (ISVREF(Available_path_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_2 = ISVREF(Available_path_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_2) = cons_1;
			temp_2 = Available_path_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_2,svref_arg_2) = cons_1;
		    }
		    else {
			temp_2 = Available_path_conses_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_2,svref_arg_2) = cons_1;
			temp_2 = Available_path_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_2,svref_arg_2) = cons_1;
		    }
		    M_CDR(cons_1) = Nil;
		}
		else
		    next_cons = Nil;
		directory_so_far = next_cons;
		default_directory_section_to_merge = 
			copy_directory_contents(default_directory_qm);
		temp_2 = nconc2(default_directory_section_to_merge,
			directory_so_far);
		return VALUES_1(SVREF(pathname_1,FIX((SI_Long)3L)) = temp_2);
	    }
	    else
		return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* GENSYM-MERGE-PATHNAMES-AFTER-CONVERSION */
Object gensym_merge_pathnames_after_conversion varargs_1(int, n)
{
    Object pathname_1;
    Object defaults, default_version, convert_file_strings_to_uppercase_p;
    Object original_pathname, merge_pathnames_rule, ab_loop_list_;
    Object ab_loop_desetq_, temp;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(39,102);
    INIT_ARGS_nonrelocating();
    pathname_1 = REQUIRED_ARG_nonrelocating();
    defaults = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    default_version = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    convert_file_strings_to_uppercase_p = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Convert_file_strings_to_uppercase_p,Qconvert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      original_pathname = copy_gensym_pathname(pathname_1);
      merge_pathnames_rule = Nil;
      ab_loop_list_ = Merge_pathnames_rules;
      ab_loop_desetq_ = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      ab_loop_desetq_ = M_CAR(ab_loop_list_);
      merge_pathnames_rule = CDR(ab_loop_desetq_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      temp = SYMBOL_FUNCTION(merge_pathnames_rule);
      FUNCALL_4(temp,original_pathname,pathname_1,defaults,default_version);
      goto next_loop;
    end_loop:;
      reclaim_gensym_pathname(original_pathname);
      result = VALUES_1(pathname_1);
    POP_SPECIAL();
    return result;
}

/* GENSYM-MERGE-PATHNAMES-FUNCTION */
Object gensym_merge_pathnames_function(convertible_thing,default_1,
	    default_version)
    Object convertible_thing, default_1, default_version;
{
    Object filename_parser, namestring_generator, default_filename_parser;
    Object default_namestring_generator, convert_file_strings_to_uppercase_p;
    Object pathname_qm;
    volatile Object default_pathname_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(39,103);
    SAVE_STACK();
    filename_parser = Nil;
    namestring_generator = Nil;
    default_filename_parser = Nil;
    default_namestring_generator = Nil;
    if (SIMPLE_VECTOR_P(convertible_thing) && EQ(ISVREF(convertible_thing,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct)) {
	filename_parser = ISVREF(convertible_thing,(SI_Long)9L);
	namestring_generator = ISVREF(convertible_thing,(SI_Long)10L);
    }
    else if (text_string_p(convertible_thing) && 
	    parser_in_namestring_p(convertible_thing)) {
	result = get_parser_from_namestring(convertible_thing);
	MVS_2(result,filename_parser,namestring_generator);
    }
    else if (SIMPLE_VECTOR_P(default_1) && EQ(ISVREF(default_1,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct)) {
	filename_parser = ISVREF(default_1,(SI_Long)9L);
	namestring_generator = ISVREF(default_1,(SI_Long)10L);
    }
    else if (text_string_p(default_1) && parser_in_namestring_p(default_1)) {
	result = get_parser_from_namestring(default_1);
	MVS_2(result,filename_parser,namestring_generator);
    }
    else {
	filename_parser = Local_filename_parser;
	namestring_generator = Local_namestring_generator;
    }
    if (SIMPLE_VECTOR_P(default_1) && EQ(ISVREF(default_1,(SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct)) {
	default_filename_parser = ISVREF(default_1,(SI_Long)9L);
	default_namestring_generator = ISVREF(default_1,(SI_Long)10L);
    }
    else if (text_string_p(default_1) && parser_in_namestring_p(default_1)) {
	result = get_parser_from_namestring(default_1);
	MVS_2(result,default_filename_parser,default_namestring_generator);
    }
    else {
	default_filename_parser = filename_parser;
	default_namestring_generator = namestring_generator;
    }
    convert_file_strings_to_uppercase_p = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(filename_parser),
	    Qconvert_file_strings_to_uppercase_p);
    PUSH_SPECIAL_WITH_SYMBOL(Convert_file_strings_to_uppercase_p,Qconvert_file_strings_to_uppercase_p,convert_file_strings_to_uppercase_p,
	    0);
      pathname_qm = 
	      convert_to_gensym_pathname_with_known_parser(convertible_thing,
	      filename_parser,namestring_generator);
      default_pathname_qm = Qunbound_in_protected_let;
      if (PUSH_UNWIND_PROTECT(0)) {
	  default_pathname_qm = 
		  convert_to_gensym_pathname_with_known_parser(default_1,
		  default_filename_parser,default_namestring_generator);
	  if (pathname_qm && default_pathname_qm)
	      SAVE_VALUES(gensym_merge_pathnames_after_conversion(3,
		      pathname_qm,default_pathname_qm,default_version));
	  else if (pathname_qm)
	      SAVE_VALUES(gensym_merge_pathnames_after_conversion(3,
		      pathname_qm,Gensym_default_pathname_defaults,
		      default_version));
	  else
	      SAVE_VALUES(make_empty_gensym_pathname());
      }
      POP_UNWIND_PROTECT(0);
      if (default_pathname_qm) {
	  if ( !EQ(default_pathname_qm,Qunbound_in_protected_let))
	      reclaim_gensym_pathname(default_pathname_qm);
      }
      CONTINUE_UNWINDING(0);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Process_specific_system_pathname, Qprocess_specific_system_pathname);

/* MAKE-ABSOLUTE-PATHNAME-IF-POSSIBLE */
Object make_absolute_pathname_if_possible(filename)
    Object filename;
{
    volatile Object pathname_of_filename;
    volatile Object pathname_for_namestring;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(39,104);
    SAVE_STACK();
    if (SIMPLE_VECTOR_P(Process_specific_system_pathname) && 
	    EQ(ISVREF(Process_specific_system_pathname,(SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct)) {
	pathname_of_filename = Qunbound_in_protected_let;
	pathname_for_namestring = Qunbound_in_protected_let;
	if (PUSH_UNWIND_PROTECT(0)) {
	    pathname_of_filename = gensym_pathname(filename);
	    pathname_for_namestring = 
		    gensym_make_pathname_with_copied_components(Nil,Nil,
		    Nil,ISVREF(pathname_of_filename,(SI_Long)4L),
		    ISVREF(pathname_of_filename,(SI_Long)5L),Nil,
		    Process_specific_system_pathname);
	    SAVE_VALUES(gensym_namestring(1,pathname_for_namestring));
	}
	POP_UNWIND_PROTECT(0);
	if (pathname_for_namestring) {
	    if ( !EQ(pathname_for_namestring,Qunbound_in_protected_let))
		reclaim_gensym_pathname(pathname_for_namestring);
	}
	if (pathname_of_filename) {
	    if ( !EQ(pathname_of_filename,Qunbound_in_protected_let))
		reclaim_gensym_pathname(pathname_of_filename);
	}
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(filename);
    }
}

/* MAKE-WILD-NAME-AND-TYPE-PATHNAME */
Object make_wild_name_and_type_pathname(default_pathname)
    Object default_pathname;
{
    Object temp;

    x_note_fn_call(39,105);
    temp = ISVREF(default_pathname,(SI_Long)8L);
    if (EQ(temp,Qunix))
	return gensym_make_pathname_with_copied_components(Nil,Nil,Nil,
		Kwild,Nil,Nil,Nil);
    else if (EQ(temp,Qwin32) || EQ(temp,Qdos) || EQ(temp,Qgeneralized_dos))
	return gensym_make_pathname_with_copied_components(Nil,Nil,Nil,
		Kwild,Nil,Nil,Nil);
    else
	return gensym_make_pathname_with_copied_components(Nil,Nil,Nil,
		Kwild,Kwild,Nil,Nil);
}

/* MAKE-CANONICAL-WILD-DIRECTORY-PATHNAME-IF-POSSIBLE */
Object make_canonical_wild_directory_pathname_if_possible(directory_pathname,
	    directory_string)
    Object directory_pathname, directory_string;
{
    volatile Object wild_pathname;
    volatile Object canonical_directory_pathname_qm;
    Declare_stack_pointer;
    Declare_catch(2);
    Object result;

    x_note_fn_call(39,106);
    SAVE_STACK();
    if ( !TRUEP(ISVREF(directory_pathname,(SI_Long)4L)) &&  
	    !TRUEP(ISVREF(directory_pathname,(SI_Long)5L)) && 
	    gensym_pathname_version_empty_p(directory_pathname)) {
	wild_pathname = Qunbound_in_protected_let;
	if (PUSH_UNWIND_PROTECT(0)) {
	    wild_pathname = 
		    make_wild_name_and_type_pathname(directory_pathname);
	    SAVE_VALUES(gensym_merge_pathnames_function(directory_pathname,
		    wild_pathname,Nil));
	}
	POP_UNWIND_PROTECT(0);
	if (wild_pathname) {
	    if ( !EQ(wild_pathname,Qunbound_in_protected_let))
		reclaim_gensym_pathname(wild_pathname);
	}
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
    else if (g2_stream_directory_p(directory_string)) {
	canonical_directory_pathname_qm = Qunbound_in_protected_let;
	if (PUSH_UNWIND_PROTECT(1)) {
	    canonical_directory_pathname_qm = 
		    gensym_file_as_directory(directory_pathname);
	    if (canonical_directory_pathname_qm) {
		wild_pathname = Qunbound_in_protected_let;
		if (PUSH_UNWIND_PROTECT(0)) {
		    wild_pathname = 
			    make_wild_name_and_type_pathname(canonical_directory_pathname_qm);
		    SAVE_VALUES(gensym_merge_pathnames_function(canonical_directory_pathname_qm,
			    wild_pathname,Nil));
		}
		POP_UNWIND_PROTECT(0);
		if (wild_pathname) {
		    if ( !EQ(wild_pathname,Qunbound_in_protected_let))
			reclaim_gensym_pathname(wild_pathname);
		}
		CONTINUE_UNWINDING(0);
	    }
	    else
		SAVE_VALUES(VALUES_1(Nil));
	}
	POP_UNWIND_PROTECT(1);
	if (canonical_directory_pathname_qm) {
	    if ( !EQ(canonical_directory_pathname_qm,
		    Qunbound_in_protected_let))
		reclaim_gensym_pathname(canonical_directory_pathname_qm);
	}
	CONTINUE_UNWINDING(1);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

/* GET-LESS-CASE-SENSITIVE-GENSYM-PATHNAME-GIVEN-DIRECTORY */
Object get_less_case_sensitive_gensym_pathname_given_directory(gensym_pathname_1,
	    directory_1)
    Object gensym_pathname_1, directory_1;
{
    Object name, type, version, truename_1, ab_loop_list_, ab_loop_it_;
    Object truename_version;

    x_note_fn_call(39,107);
    name = ISVREF(gensym_pathname_1,(SI_Long)4L);
    type = ISVREF(gensym_pathname_1,(SI_Long)5L);
    version = ISVREF(gensym_pathname_1,(SI_Long)6L);
    truename_1 = Nil;
    ab_loop_list_ = directory_1;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    truename_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (name && ISVREF(truename_1,(SI_Long)4L) && 
	    string_equalw(ISVREF(truename_1,(SI_Long)4L),name) && type && 
	    ISVREF(truename_1,(SI_Long)5L) && 
	    string_equalw(ISVREF(truename_1,(SI_Long)5L),type)) {
	truename_version = ISVREF(truename_1,(SI_Long)6L);
	ab_loop_it_ = EQL(version,truename_version) || (EQ(version,Qnil) 
		|| EQ(version,Knewest) || EQ(version,Kunspecific)) && 
		(EQ(truename_version,Qnil) || EQ(truename_version,Knewest) 
		|| EQ(truename_version,Kunspecific)) ? 
		copy_gensym_pathname(truename_1) : Qnil;
    }
    else
	ab_loop_it_ = Nil;
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* MAKE-MODULE-NAME-FROM-KB-PATHNAME */
Object make_module_name_from_kb_pathname(kb_pathname)
    Object kb_pathname;
{
    x_note_fn_call(39,108);
    return intern_text_string(1,
	    nstring_upcasew(copy_text_string(ISVREF(kb_pathname,
	    (SI_Long)4L))));
}

/* MERGE-SERIES-OF-PATHNAMES */
Object merge_series_of_pathnames(series_of_pathnames)
    Object series_of_pathnames;
{
    Object pathname_qm, result_so_far, series_of_pathnames_old_value, temp;

    x_note_fn_call(39,109);
    pathname_qm = Nil;
    result_so_far = gensym_make_pathname_with_copied_components(Nil,Nil,
	    Nil,Nil,Nil,Nil,Nil);
  next_loop:
    if ( !TRUEP(series_of_pathnames))
	goto end_loop;
    series_of_pathnames_old_value = series_of_pathnames;
    temp = FIRST(series_of_pathnames_old_value);
    series_of_pathnames = REST(series_of_pathnames_old_value);
    pathname_qm = temp;
    if (pathname_qm) {
	temp = gensym_merge_pathnames_function(result_so_far,pathname_qm,Nil);
	reclaim_gensym_pathname(result_so_far);
	result_so_far = temp;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(result_so_far);
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Object_file_pathname_for_machine, Qobject_file_pathname_for_machine);

Object G2_machine_type_string = UNBOUND;

static Object Kappend_to_directory;  /* :append-to-directory */

static Object Kappend_to_name;     /* :append-to-name */

static Object string_constant_8;   /* "~A-~A" */

/* MAKE-OBJECT-FILE-PATHNAME */
Object make_object_file_pathname(pathname_1,type)
    Object pathname_1, type;
{
    Object directory_1, obj_file_dir, name, obj_file_name, temp;

    x_note_fn_call(39,110);
    directory_1 = ISVREF(pathname_1,(SI_Long)3L);
    obj_file_dir = EQ(Object_file_pathname_for_machine,
	    Kappend_to_directory) && CONSP(directory_1) ? 
	    nconc2(copy_list_using_path_conses_1(directory_1),
	    path_cons_1(G2_machine_type_string,Nil)) : directory_1;
    name = ISVREF(pathname_1,(SI_Long)4L);
    obj_file_name = EQ(Object_file_pathname_for_machine,Kappend_to_name) ? 
	    tformat_text_string(3,string_constant_8,name,
	    G2_machine_type_string) : name;
    temp = gensym_make_pathname_with_copied_components(Nil,Nil,
	    obj_file_dir,obj_file_name,type,Nil,pathname_1);
    if (EQ(Object_file_pathname_for_machine,Kappend_to_directory) && 
	    CONSP(directory_1))
	reclaim_path_list_1(obj_file_dir);
    if (EQ(Object_file_pathname_for_machine,Kappend_to_name))
	reclaim_text_string(obj_file_name);
    return VALUES_1(temp);
}

static Object array_constant_3;    /* # */

static Object array_constant_4;    /* # */

static Object array_constant_5;    /* # */

/* PATHNAME->SHARED-FILE-PATHNAME */
Object pathname_gt_shared_file_pathname(pathname_1)
    Object pathname_1;
{
    Object temp;

    x_note_fn_call(39,111);
    if (T) {
	if (EQ(Local_file_system,Qunix))
	    temp = array_constant_3;
	else if (EQ(Local_file_system,Qvms))
	    temp = array_constant_4;
	else if (EQ(Local_file_system,Qwin32))
	    temp = array_constant_5;
	else
	    temp = array_constant_5;
    }
    else
	temp = Nil;
    temp = make_object_file_pathname(pathname_1,temp);
    return VALUES_1(temp);
}

static Object array_constant_6;    /* # */

static Object array_constant_7;    /* # */

/* GET-OBJECT-FILE-SUFFIX-FOR-THIS-OS */
Object get_object_file_suffix_for_this_os()
{
    x_note_fn_call(39,112);
    return VALUES_1(EQ(Local_file_system,Qunix) ? array_constant_6 : 
	    array_constant_7);
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

/* KB-NAME->SHARED-OBJECT-FILENAME */
Object kb_name_gt_shared_object_filename(kb_filename)
    Object kb_filename;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object c, temp, aref_arg_2_1, temp_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, i;
    SI_Long ab_loop_bind_;
    Declare_special(5);

    x_note_fn_call(39,113);
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
	      i = (SI_Long)0L;
	      ab_loop_bind_ = IFIX(text_string_length(kb_filename));
	      c = Nil;
	    next_loop:
	      if (i >= ab_loop_bind_)
		  goto end_loop;
	      c = FIX(UBYTE_16_ISAREF_1(kb_filename,i));
	      if ((SI_Long)46L == IFIX(c))
		  goto end_loop;
	      if ( !FIXNUM_LT(Fill_pointer_for_current_wide_string,
		      Total_length_of_current_wide_string))
		  extend_current_wide_string(Fill_pointer_for_current_wide_string);
	      temp = Current_wide_string;
	      aref_arg_2_1 = Fill_pointer_for_current_wide_string;
	      UBYTE_16_ISASET_1(temp,IFIX(aref_arg_2_1),IFIX(c));
	      temp = FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
	      Fill_pointer_for_current_wide_string = temp;
	      i = i + (SI_Long)1L;
	      goto next_loop;
	    end_loop:;
	      if ( !FIXNUM_LT(Fill_pointer_for_current_wide_string,
		      Total_length_of_current_wide_string))
		  extend_current_wide_string(Fill_pointer_for_current_wide_string);
	      temp = Current_wide_string;
	      aref_arg_2_1 = Fill_pointer_for_current_wide_string;
	      UBYTE_16_ISASET_1(temp,IFIX(aref_arg_2_1),(SI_Long)45L);
	      temp = FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
	      Fill_pointer_for_current_wide_string = temp;
	      twrite_general_string(G2_machine_type_string);
	      if ( !FIXNUM_LT(Fill_pointer_for_current_wide_string,
		      Total_length_of_current_wide_string))
		  extend_current_wide_string(Fill_pointer_for_current_wide_string);
	      temp = Current_wide_string;
	      aref_arg_2_1 = Fill_pointer_for_current_wide_string;
	      UBYTE_16_ISASET_1(temp,IFIX(aref_arg_2_1),(SI_Long)46L);
	      temp = FIXNUM_ADD1(Fill_pointer_for_current_wide_string);
	      Fill_pointer_for_current_wide_string = temp;
	      if (EQ(Local_file_system,Qunix))
		  twrite_beginning_of_wide_string(array_constant_3,
			  FIX((SI_Long)2L));
	      else if (EQ(Local_file_system,Qvms))
		  twrite_beginning_of_wide_string(array_constant_4,
			  FIX((SI_Long)3L));
	      else if (EQ(Local_file_system,Qwin32))
		  twrite_beginning_of_wide_string(array_constant_5,
			  FIX((SI_Long)3L));
	      else
		  twrite_beginning_of_wide_string(array_constant_5,
			  FIX((SI_Long)3L));
	      temp_1 = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp_1);
}

/* C-USER-NAME */
Object c_user_name(buff)
    Object buff;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(39,114);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(buff);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = buff;
    temp = FIX(g2ext_get_user_name(ISTRING(temp)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* FOREIGN-GET-USER-NAME */
Object foreign_get_user_name()
{
    Object result_code;

    x_note_fn_call(39,115);
    result_code = c_user_name(Gensym_environment_variable_buffer);
    if ( !(FIXNUMP(result_code) && FIXNUM_LE(FIX((SI_Long)-128L),
	    result_code) && FIXNUM_LE(result_code,FIX((SI_Long)127L))))
	return VALUES_1(Nil);
    else
	switch (INTEGER_TO_CHAR(result_code)) {
	  case 0:
	    return copy_null_terminated_string_as_text_string(Gensym_environment_variable_buffer);
	  case -1:
	    return VALUES_1(Nil);
	  default:
	    return VALUES_1(Nil);
	}
}

void pathnames_INIT()
{
    Object temp, reclaim_structure_for_gensym_pathname_1, pushnew_arg_1;
    Object pushnew_arg_3, pushnew_arg_5, merge_pathnames_rules_new_value;
    Object AB_package, list_constant_9;
    Object Qmerge_pathnames_merge_structured_directories;
    Object Qmerge_pathnames_version_default_rule;
    Object Qmerge_pathnames_replace_empty_components;
    Object Qmerge_pathnames_replace_unspecific_host;
    Object Qmerge_pathnames_propagate_file_system;
    Object Qmerge_pathnames_device_default_rule, Qgensym_pathname;
    Object list_constant_8, Qfile_systems_which_store_device_names, Qcoral;
    Object list_constant_7, Qfile_systems_which_distinguish_by_version;
    Object list_constant_6, Qpathnames;
    Object Qinitialize_default_gensym_pathname_defaults, Kfuncall;
    Object Qreclaim_structure, Qoutstanding_gensym_pathname_count;
    Object Qgensym_pathname_structure_memory_usage, Qutilities2;
    Object string_constant_11, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_10, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, string_constant_9;
    Object Qpath_cons_memory_usage, Qoutstanding_path_conses, list_constant_5;
    Object Qpath_cons_counter_vector, Qmake_thread_array, list_constant_4;
    Object Qavailable_path_conses_tail_vector, Qavailable_path_conses_vector;

    x_note_fn_call(39,116);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qavailable_path_conses = STATIC_SYMBOL("AVAILABLE-PATH-CONSES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_path_conses,Available_path_conses);
    Qpathnames = STATIC_SYMBOL("PATHNAMES",AB_package);
    record_system_variable(Qavailable_path_conses,Qpathnames,Nil,Qnil,Qt,
	    Qnil,Qnil);
    Qavailable_path_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-PATH-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_path_conses_tail,
	    Available_path_conses_tail);
    record_system_variable(Qavailable_path_conses_tail,Qpathnames,Nil,Qnil,
	    Qt,Qnil,Qnil);
    Qavailable_path_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-PATH-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_path_conses_vector,
	    Available_path_conses_vector);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_thread_array = STATIC_SYMBOL("MAKE-THREAD-ARRAY",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    Qnil);
    record_system_variable(Qavailable_path_conses_vector,Qpathnames,
	    list_constant_4,Qnil,Qt,Qnil,Qnil);
    Qavailable_path_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-PATH-CONSES-TAIL-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_path_conses_tail_vector,
	    Available_path_conses_tail_vector);
    record_system_variable(Qavailable_path_conses_tail_vector,Qpathnames,
	    list_constant_4,Qnil,Qt,Qnil,Qnil);
    Qpath_cons_counter_vector = STATIC_SYMBOL("PATH-CONS-COUNTER-VECTOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpath_cons_counter_vector,
	    Path_cons_counter_vector);
    list_constant_5 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    FIX((SI_Long)0L));
    record_system_variable(Qpath_cons_counter_vector,Qpathnames,
	    list_constant_5,Qnil,Qt,Qnil,Qnil);
    Qpath_cons_counter = STATIC_SYMBOL("PATH-CONS-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpath_cons_counter,Path_cons_counter);
    record_system_variable(Qpath_cons_counter,Qpathnames,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    Qoutstanding_path_conses = STATIC_SYMBOL("OUTSTANDING-PATH-CONSES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_path_conses,
	    STATIC_FUNCTION(outstanding_path_conses,NIL,FALSE,0,0));
    Qpath_cons_memory_usage = STATIC_SYMBOL("PATH-CONS-MEMORY-USAGE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpath_cons_memory_usage,
	    STATIC_FUNCTION(path_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_9 = STATIC_STRING("1q83-icy9k83-iby09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_path_conses);
    push_optimized_constant(Qpath_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_9));
    Qpath = STATIC_SYMBOL("PATH",AB_package);
    Qunix = STATIC_SYMBOL("UNIX",AB_package);
    Qvms = STATIC_SYMBOL("VMS",AB_package);
    Qdos = STATIC_SYMBOL("DOS",AB_package);
    Qwin32 = STATIC_SYMBOL("WIN32",AB_package);
    if (Local_file_system == UNBOUND)
	Local_file_system = initialize_local_file_system();
    Qparse_unix_filename = STATIC_SYMBOL("PARSE-UNIX-FILENAME",AB_package);
    Qparse_vms_filename = STATIC_SYMBOL("PARSE-VMS-FILENAME",AB_package);
    Qparse_dos_filename = STATIC_SYMBOL("PARSE-DOS-FILENAME",AB_package);
    Qparse_win32_filename = STATIC_SYMBOL("PARSE-WIN32-FILENAME",AB_package);
    if (Local_filename_parser == UNBOUND)
	Local_filename_parser = initialize_local_filename_parser();
    Qgenerate_unix_namestring = STATIC_SYMBOL("GENERATE-UNIX-NAMESTRING",
	    AB_package);
    Qgenerate_vms_namestring = STATIC_SYMBOL("GENERATE-VMS-NAMESTRING",
	    AB_package);
    Qgenerate_dos_namestring = STATIC_SYMBOL("GENERATE-DOS-NAMESTRING",
	    AB_package);
    Qgenerate_win32_namestring = STATIC_SYMBOL("GENERATE-WIN32-NAMESTRING",
	    AB_package);
    if (Local_namestring_generator == UNBOUND)
	Local_namestring_generator = initialize_local_namestring_generator();
    Qconvert_file_strings_to_uppercase_p = 
	    STATIC_SYMBOL("CONVERT-FILE-STRINGS-TO-UPPERCASE-P",AB_package);
    Convert_file_strings_to_uppercase_p_prop = 
	    Qconvert_file_strings_to_uppercase_p;
    SET_SYMBOL_VALUE_LOCATION(Qconvert_file_strings_to_uppercase_p,
	    Convert_file_strings_to_uppercase_p);
    if (Convert_file_strings_to_uppercase_p == UNBOUND)
	Convert_file_strings_to_uppercase_p = 
		initialize_convert_file_strings_to_uppercase_p();
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_gensym_pathname_g2_struct = 
	    STATIC_SYMBOL("GENSYM-PATHNAME-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qgensym_pathname = STATIC_SYMBOL("GENSYM-PATHNAME",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_gensym_pathname_g2_struct,
	    Qgensym_pathname,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qgensym_pathname,
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_gensym_pathname == UNBOUND)
	The_type_description_of_gensym_pathname = Nil;
    string_constant_10 = 
	    STATIC_STRING("43Dy8m9k1n9k8n8k1l8n0000001m1n8y83-4-y1q83-+ny83-+ly83-+my83-+oy83-+py83-+qy1m83My83-AJykvk0k0");
    temp = The_type_description_of_gensym_pathname;
    clear_optimized_constants();
    push_optimized_constant(Qgensym_pathname);
    The_type_description_of_gensym_pathname = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_10));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_gensym_pathname_g2_struct,
	    The_type_description_of_gensym_pathname,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qgensym_pathname,
	    The_type_description_of_gensym_pathname,Qtype_description_of_type);
    Qoutstanding_gensym_pathname_count = 
	    STATIC_SYMBOL("OUTSTANDING-GENSYM-PATHNAME-COUNT",AB_package);
    Qgensym_pathname_structure_memory_usage = 
	    STATIC_SYMBOL("GENSYM-PATHNAME-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_11 = STATIC_STRING("1q9k8s83-WHy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qgensym_pathname);
    push_optimized_constant(Qoutstanding_gensym_pathname_count);
    push_optimized_constant(Qgensym_pathname_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_11));
    Qchain_of_available_gensym_pathnames = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-GENSYM-PATHNAMES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_gensym_pathnames,
	    Chain_of_available_gensym_pathnames);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_gensym_pathnames,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qgensym_pathname_count = STATIC_SYMBOL("GENSYM-PATHNAME-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgensym_pathname_count,Gensym_pathname_count);
    record_system_variable(Qgensym_pathname_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_gensym_pathnames_vector == UNBOUND)
	Chain_of_available_gensym_pathnames_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qgensym_pathname_structure_memory_usage,
	    STATIC_FUNCTION(gensym_pathname_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_gensym_pathname_count,
	    STATIC_FUNCTION(outstanding_gensym_pathname_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_gensym_pathname_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_gensym_pathname,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qgensym_pathname,
	    reclaim_structure_for_gensym_pathname_1);
    Krelative = STATIC_SYMBOL("RELATIVE",Pkeyword);
    list_constant = STATIC_CONS(Krelative,Qnil);
    Qgensym_default_pathname_defaults = 
	    STATIC_SYMBOL("GENSYM-DEFAULT-PATHNAME-DEFAULTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgensym_default_pathname_defaults,
	    Gensym_default_pathname_defaults);
    Qinitialize_default_gensym_pathname_defaults = 
	    STATIC_SYMBOL("INITIALIZE-DEFAULT-GENSYM-PATHNAME-DEFAULTS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_default_gensym_pathname_defaults,
	    STATIC_FUNCTION(initialize_default_gensym_pathname_defaults,
	    NIL,FALSE,0,0));
    list_constant_6 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_default_gensym_pathname_defaults);
    record_system_variable(Qgensym_default_pathname_defaults,Qpathnames,
	    list_constant_6,Qnil,Qt,Qnil,Qnil);
    string_constant = STATIC_STRING("RclmGsmPthnm");
    Qfile_systems_which_distinguish_by_version = 
	    STATIC_SYMBOL("FILE-SYSTEMS-WHICH-DISTINGUISH-BY-VERSION",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qfile_systems_which_distinguish_by_version,
	    File_systems_which_distinguish_by_version);
    list_constant_7 = STATIC_CONS(Qvms,Qnil);
    SET_SYMBOL_VALUE(Qfile_systems_which_distinguish_by_version,
	    list_constant_7);
    Qfile_systems_which_store_device_names = 
	    STATIC_SYMBOL("FILE-SYSTEMS-WHICH-STORE-DEVICE-NAMES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qfile_systems_which_store_device_names,
	    File_systems_which_store_device_names);
    Qcoral = STATIC_SYMBOL("CORAL",AB_package);
    list_constant_8 = STATIC_LIST((SI_Long)2L,Qvms,Qcoral);
    SET_SYMBOL_VALUE(Qfile_systems_which_store_device_names,list_constant_8);
    string_constant_1 = STATIC_STRING("~a");
    Qunbound_in_protected_let = STATIC_SYMBOL("UNBOUND-IN-PROTECTED-LET",
	    AB_package);
    list_constant_9 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_9,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    string_constant_2 = STATIC_STRING("~A/");
    Khome = STATIC_SYMBOL("HOME",Pkeyword);
    if (Inside_handling_gensym_file_errors_scope_p == UNBOUND)
	Inside_handling_gensym_file_errors_scope_p = Nil;
    if (Gensym_file_error_occurred_p == UNBOUND)
	Gensym_file_error_occurred_p = Nil;
    Qgensym_file_error_catch_tag = 
	    STATIC_SYMBOL("GENSYM-FILE-ERROR-CATCH-TAG",AB_package);
    Qtformat_text_string = STATIC_SYMBOL("TFORMAT-TEXT-STRING",AB_package);
    SET_SYMBOL_FUNCTION(Qtformat_text_string,
	    STATIC_FUNCTION(tformat_text_string,NIL,TRUE,1,10));
    if (Report_filename_parsing_errors_in_development_p == UNBOUND)
	Report_filename_parsing_errors_in_development_p = Nil;
    array_constant_1 = STATIC_ARRAY(list_constant_9,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    Qgeneralized_dos = STATIC_SYMBOL("GENERALIZED-DOS",AB_package);
    array_constant_2 = STATIC_ARRAY(list_constant_9,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)57344L);
    Qnamestring_as_gensym_string = 
	    STATIC_SYMBOL("NAMESTRING-AS-GENSYM-STRING",AB_package);
    SET_SYMBOL_FUNCTION(Qnamestring_as_gensym_string,
	    STATIC_FUNCTION(namestring_as_gensym_string,NIL,FALSE,1,1));
    string_constant_3 = STATIC_STRING("~a*.*");
    Qgensym_enough_namestring = STATIC_SYMBOL("GENSYM-ENOUGH-NAMESTRING",
	    AB_package);
    Kabsolute = STATIC_SYMBOL("ABSOLUTE",Pkeyword);
    string_constant_4 = STATIC_STRING("");
    SET_SYMBOL_FUNCTION(Qgensym_enough_namestring,
	    STATIC_FUNCTION(gensym_enough_namestring,NIL,TRUE,1,2));
    list_constant_1 = STATIC_CONS(Kabsolute,Qnil);
    list_constant_2 = STATIC_CONS(Kabsolute,list_constant);
    SET_SYMBOL_FUNCTION(Qgensym_pathname,STATIC_FUNCTION(gensym_pathname,
	    NIL,FALSE,1,1));
    string_constant_5 = 
	    STATIC_STRING("GENSYM-TRUENAME: Cannot get pathname from stream ~a");
    string_constant_6 = 
	    STATIC_STRING("GENSYM-TRUENAME: Cannot access file ~a");
    string_constant_7 = 
	    STATIC_STRING("GENSYM-TRUENAME: Cannot obtain pathname for ~a");
    if (Merge_pathnames_rules == UNBOUND)
	Merge_pathnames_rules = Nil;
    if (Merge_pathnames_rules_sorted_p == UNBOUND)
	Merge_pathnames_rules_sorted_p = Nil;
    Qmerge_pathnames_device_default_rule = 
	    STATIC_SYMBOL("MERGE-PATHNAMES-DEVICE-DEFAULT-RULE",AB_package);
    SET_SYMBOL_FUNCTION(Qmerge_pathnames_device_default_rule,
	    STATIC_FUNCTION(merge_pathnames_device_default_rule,NIL,TRUE,2,4));
    temp = FIX((SI_Long)0L);
    pushnew_arg_1 = CONS(temp,Qmerge_pathnames_device_default_rule);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcdr);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    merge_pathnames_rules_new_value = adjoin(6,pushnew_arg_1,
	    Merge_pathnames_rules,Kkey,pushnew_arg_3,Ktest,pushnew_arg_5);
    Merge_pathnames_rules = merge_pathnames_rules_new_value;
    Qmerge_pathnames_propagate_file_system = 
	    STATIC_SYMBOL("MERGE-PATHNAMES-PROPAGATE-FILE-SYSTEM",AB_package);
    SET_SYMBOL_FUNCTION(Qmerge_pathnames_propagate_file_system,
	    STATIC_FUNCTION(merge_pathnames_propagate_file_system,NIL,TRUE,
	    2,4));
    temp = FIX((SI_Long)1L);
    pushnew_arg_1 = CONS(temp,Qmerge_pathnames_propagate_file_system);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcdr);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    merge_pathnames_rules_new_value = adjoin(6,pushnew_arg_1,
	    Merge_pathnames_rules,Kkey,pushnew_arg_3,Ktest,pushnew_arg_5);
    Merge_pathnames_rules = merge_pathnames_rules_new_value;
    Qmerge_pathnames_replace_unspecific_host = 
	    STATIC_SYMBOL("MERGE-PATHNAMES-REPLACE-UNSPECIFIC-HOST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmerge_pathnames_replace_unspecific_host,
	    STATIC_FUNCTION(merge_pathnames_replace_unspecific_host,NIL,
	    TRUE,2,4));
    temp = FIX((SI_Long)2L);
    pushnew_arg_1 = CONS(temp,Qmerge_pathnames_replace_unspecific_host);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcdr);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    merge_pathnames_rules_new_value = adjoin(6,pushnew_arg_1,
	    Merge_pathnames_rules,Kkey,pushnew_arg_3,Ktest,pushnew_arg_5);
    Merge_pathnames_rules = merge_pathnames_rules_new_value;
    Qmerge_pathnames_replace_empty_components = 
	    STATIC_SYMBOL("MERGE-PATHNAMES-REPLACE-EMPTY-COMPONENTS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmerge_pathnames_replace_empty_components,
	    STATIC_FUNCTION(merge_pathnames_replace_empty_components,NIL,
	    TRUE,2,4));
    temp = FIX((SI_Long)3L);
    pushnew_arg_1 = CONS(temp,Qmerge_pathnames_replace_empty_components);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcdr);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    merge_pathnames_rules_new_value = adjoin(6,pushnew_arg_1,
	    Merge_pathnames_rules,Kkey,pushnew_arg_3,Ktest,pushnew_arg_5);
    Merge_pathnames_rules = merge_pathnames_rules_new_value;
    Qmerge_pathnames_version_default_rule = 
	    STATIC_SYMBOL("MERGE-PATHNAMES-VERSION-DEFAULT-RULE",AB_package);
    SET_SYMBOL_FUNCTION(Qmerge_pathnames_version_default_rule,
	    STATIC_FUNCTION(merge_pathnames_version_default_rule,NIL,TRUE,
	    2,4));
    temp = FIX((SI_Long)4L);
    pushnew_arg_1 = CONS(temp,Qmerge_pathnames_version_default_rule);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcdr);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    merge_pathnames_rules_new_value = adjoin(6,pushnew_arg_1,
	    Merge_pathnames_rules,Kkey,pushnew_arg_3,Ktest,pushnew_arg_5);
    Merge_pathnames_rules = merge_pathnames_rules_new_value;
    list_constant_3 = STATIC_CONS(Kup,list_constant);
    Qmerge_pathnames_merge_structured_directories = 
	    STATIC_SYMBOL("MERGE-PATHNAMES-MERGE-STRUCTURED-DIRECTORIES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmerge_pathnames_merge_structured_directories,
	    STATIC_FUNCTION(merge_pathnames_merge_structured_directories,
	    NIL,TRUE,2,4));
    temp = FIX((SI_Long)5L);
    pushnew_arg_1 = CONS(temp,Qmerge_pathnames_merge_structured_directories);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qcdr);
    pushnew_arg_5 = SYMBOL_FUNCTION(Qequal);
    merge_pathnames_rules_new_value = adjoin(6,pushnew_arg_1,
	    Merge_pathnames_rules,Kkey,pushnew_arg_3,Ktest,pushnew_arg_5);
    Merge_pathnames_rules = merge_pathnames_rules_new_value;
    Merge_pathnames_rules = sort(4,Merge_pathnames_rules,
	    SYMBOL_FUNCTION(Qnum_lt),Kkey,SYMBOL_FUNCTION(Qcar));
    Merge_pathnames_rules_sorted_p = T;
    Kappend_to_name = STATIC_SYMBOL("APPEND-TO-NAME",Pkeyword);
    if (Object_file_pathname_for_machine == UNBOUND)
	Object_file_pathname_for_machine = Kappend_to_name;
    G2_machine_type_string = 
	    gensym_string_to_wide_string(string_downcase(1,
	    SYMBOL_NAME(G2_machine_type)));
    Kappend_to_directory = STATIC_SYMBOL("APPEND-TO-DIRECTORY",Pkeyword);
    string_constant_8 = STATIC_STRING("~A-~A");
    array_constant_3 = STATIC_ARRAY(list_constant_9,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)57344L);
    array_constant_4 = STATIC_ARRAY(list_constant_9,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)57344L);
    array_constant_5 = STATIC_ARRAY(list_constant_9,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)57344L);
    array_constant_6 = STATIC_ARRAY(list_constant_9,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)57344L);
    array_constant_7 = STATIC_ARRAY(list_constant_9,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)106L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)57344L);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
}
