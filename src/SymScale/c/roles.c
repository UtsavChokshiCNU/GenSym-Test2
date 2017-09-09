/* roles.c
 * Input file:  roles.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "roles.h"


DEFINE_VARIABLE_WITH_SYMBOL(Available_role_conses, Qavailable_role_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_role_conses_tail, Qavailable_role_conses_tail);

Object Available_role_conses_vector = UNBOUND;

Object Available_role_conses_tail_vector = UNBOUND;

Object Role_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Role_cons_counter, Qrole_cons_counter);

/* OUTSTANDING-ROLE-CONSES */
Object outstanding_role_conses()
{
    Object temp;

    x_note_fn_call(149,0);
    temp = FIXNUM_MINUS(Role_cons_counter,length(Available_role_conses));
    return VALUES_1(temp);
}

/* ROLE-CONS-MEMORY-USAGE */
Object role_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(149,1);
    temp = FIXNUM_TIMES(Role_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-ROLE-CONS-POOL */
Object replenish_role_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(149,2);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qrole_cons_counter,Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_role_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_role_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_role_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_role_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_role_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Role_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qrole;               /* role */

/* ROLE-CONS-1 */
Object role_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(149,3);
    new_cons = ISVREF(Available_role_conses_vector,IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_role_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_role_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_role_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_role_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qrole);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-ROLE-LIST-POOL */
Object replenish_role_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(149,4);
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
    if (ISVREF(Available_role_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_role_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_role_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_role_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_role_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qrole_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-ROLE-LIST-1 */
Object make_role_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(149,5);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_role_conses_vector,
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
	replenish_role_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_role_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qrole);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_role_conses_vector,IFIX(Current_thread_index));
	svref_arg_1 = Available_role_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_role_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_role_conses_tail_vector;
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

/* ROLE-LIST-2 */
Object role_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(149,6);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_role_conses_vector,IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_role_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_role_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qrole);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_role_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_role_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_role_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_role_conses_tail_vector;
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

/* ROLE-LIST-3 */
Object role_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(149,7);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_role_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_role_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_role_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qrole);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_role_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_role_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_role_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_role_conses_tail_vector;
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

/* ROLE-LIST-4 */
Object role_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(149,8);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_role_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_role_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_role_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qrole);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_role_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_role_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_role_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_role_conses_tail_vector;
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

/* ROLE-LIST-TRACE-HOOK */
Object role_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(149,9);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-ROLE-CONSES-1 */
Object copy_tree_using_role_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(149,10);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_role_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_role_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_role_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_role_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_role_cons_pool();
	temp_1 = copy_tree_using_role_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qrole);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_role_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_role_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_role_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_role_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_role_cons_pool();
	temp_1 = copy_tree_using_role_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qrole);
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

/* COPY-LIST-USING-ROLE-CONSES-1 */
Object copy_list_using_role_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(149,11);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_role_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_role_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_role_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_role_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_role_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qrole);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_role_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_role_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_role_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_role_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_role_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qrole);
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

/* RECLAIM-ROLE-CONS-1 */
Object reclaim_role_cons_1(role_cons)
    Object role_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(149,12);
    inline_note_reclaim_cons(role_cons,Qrole);
    if (ISVREF(Available_role_conses_tail_vector,IFIX(Current_thread_index))) {
	temp = ISVREF(Available_role_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = role_cons;
	temp = Available_role_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = role_cons;
    }
    else {
	temp = Available_role_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = role_cons;
	temp = Available_role_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = role_cons;
    }
    M_CDR(role_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-ROLE-LIST-1 */
Object reclaim_role_list_1(role_list)
    Object role_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(149,13);
    if (role_list) {
	last_1 = role_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qrole);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qrole);
	if (ISVREF(Available_role_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_role_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = role_list;
	    temp = Available_role_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_role_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = role_list;
	    temp = Available_role_conses_tail_vector;
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

/* RECLAIM-ROLE-LIST*-1 */
Object reclaim_role_list_star_1(role_list)
    Object role_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(149,14);
    if (CONSP(role_list)) {
	temp = last(role_list,_);
	M_CDR(temp) = Nil;
	if (role_list) {
	    last_1 = role_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qrole);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qrole);
	    if (ISVREF(Available_role_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_role_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = role_list;
		temp = Available_role_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_role_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = role_list;
		temp = Available_role_conses_tail_vector;
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

/* RECLAIM-ROLE-TREE-1 */
Object reclaim_role_tree_1(tree)
    Object tree;
{
    Object e, e2, role_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(149,15);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_role_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		role_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(role_cons,Qrole);
		if (EQ(role_cons,e))
		    goto end_1;
		else if ( !TRUEP(role_cons))
		    goto end_1;
		else
		    role_cons = CDR(role_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_role_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_role_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_role_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_role_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_role_conses_tail_vector;
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

/* DELETE-ROLE-ELEMENT-1 */
Object delete_role_element_1(element,role_list)
    Object element, role_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(149,16);
    if (role_list) {
	if (EQ(element,M_CAR(role_list))) {
	    temp = CDR(role_list);
	    inline_note_reclaim_cons(role_list,Qrole);
	    if (ISVREF(Available_role_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_role_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = role_list;
		temp_1 = Available_role_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = role_list;
	    }
	    else {
		temp_1 = Available_role_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = role_list;
		temp_1 = Available_role_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = role_list;
	    }
	    M_CDR(role_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = role_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qrole);
		if (ISVREF(Available_role_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_role_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_role_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_role_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_role_conses_tail_vector;
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
	    temp = role_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-ROLE-CONS-1 */
Object delete_role_cons_1(role_cons,role_list)
    Object role_cons, role_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(149,17);
    if (EQ(role_cons,role_list))
	temp = CDR(role_list);
    else {
	l_trailer_qm = Nil;
	l = role_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,role_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = role_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_role_cons_1(role_cons);
    return VALUES_1(temp);
}

Object Role_server_prop = UNBOUND;

Object Defined_type_of_role_prop = UNBOUND;

Object Inverse_role_server_prop = UNBOUND;

Object Role_server_printer_prop = UNBOUND;

Object Role_and_designation_printer_prop = UNBOUND;

static Object Qtruth_value;        /* truth-value */

static Object Qiteration_state;    /* iteration-state */

/* SERVE-NEXT-ITEM-OR-TEMPORARY-CONSTANT-OF-ROLE */
Object serve_next_item_or_temporary_constant_of_role(continuation)
    Object continuation;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, value_qm;
    Object next_continuation, expiration_qm, skip_list, key_value, marked;
    Object pred, curr, succ, reference, temp_1, temp_2, entry_hash;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Object result;

    x_note_fn_call(149,18);
    gensymed_symbol = M_CAR(continuation);
    gensymed_symbol_1 = T;
    gensymed_symbol_2 = continuation;
    result = inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
	    gensymed_symbol_2);
    MVS_3(result,value_qm,next_continuation,expiration_qm);
    if (expiration_qm) {
	gensymed_symbol = value_qm;
	temp = FIXNUMP(gensymed_symbol);
	if (temp);
	else
	    temp = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
		    (SI_Long)0L ? 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		    (SI_Long)1L : TRUEP(Qnil);
	if (temp);
	else
	    temp = INLINE_LONG_VECTOR_P(gensymed_symbol) != (SI_Long)0L ? 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		    (SI_Long)1L : TRUEP(Qnil);
	if (temp);
	else
	    temp = gensymed_symbol ? SYMBOLP(gensymed_symbol) : TRUEP(Qnil);
	if (temp);
	else
	    temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) != 
		    (SI_Long)0L;
	if (temp);
	else if (CONSP(gensymed_symbol)) {
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    temp = EQ(gensymed_symbol,Qtruth_value);
	    if (temp);
	    else
		temp = EQ(gensymed_symbol,Qiteration_state);
	    if (temp);
	    else if (SYMBOLP(gensymed_symbol)) {
		skip_list = CDR(Defined_evaluation_value_types);
		key_value = gensymed_symbol;
		key_hash_value = SXHASH_SYMBOL_1(gensymed_symbol) & 
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_1:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_2:
		if ( !TRUEP(marked))
		    goto end_loop_1;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
		goto next_loop_2;
	      end_loop_1:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
		temp = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
			(EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
			TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : 
			TRUEP(Nil);
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
	value_qm = 
		transform_evaluation_value_into_temporary_constant(value_qm);
    return VALUES_3(value_qm,next_continuation,expiration_qm);
}

/* RECLAIM-EVALUATION-ITERATION-STATE */
Object reclaim_evaluation_iteration_state(evaluation_iteration_state)
    Object evaluation_iteration_state;
{
    Object reference_cons, continuation_qm, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, temp, svref_arg_2;
    SI_Long reference_count, car_new_value;

    x_note_fn_call(149,19);
    reference_cons = M_CAR(evaluation_iteration_state);
    reference_count = IFIX(M_CAR(reference_cons));
    if (reference_count == (SI_Long)1L) {
	continuation_qm = M_CDR(reference_cons);
	if (continuation_qm) {
	    gensymed_symbol = M_CAR(continuation_qm);
	    gensymed_symbol_1 = Nil;
	    gensymed_symbol_2 = continuation_qm;
	    inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2);
	}
	inline_note_reclaim_cons(reference_cons,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = reference_cons;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = reference_cons;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = reference_cons;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = reference_cons;
	}
	M_CDR(reference_cons) = Nil;
	inline_note_reclaim_cons(evaluation_iteration_state,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = evaluation_iteration_state;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = evaluation_iteration_state;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = evaluation_iteration_state;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = evaluation_iteration_state;
	}
	M_CDR(evaluation_iteration_state) = Nil;
    }
    else {
	car_new_value = reference_count - (SI_Long)1L;
	M_CAR(reference_cons) = FIX(car_new_value);
    }
    return VALUES_1(Nil);
}

/* CLOSE-EVALUATION-ITERATION-STATE-CONTINUATION */
Object close_evaluation_iteration_state_continuation(evaluation_iteration_state)
    Object evaluation_iteration_state;
{
    Object reference_cons, continuation_qm, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2;

    x_note_fn_call(149,20);
    reference_cons = M_CAR(evaluation_iteration_state);
    continuation_qm = M_CDR(reference_cons);
    if (continuation_qm) {
	gensymed_symbol = M_CAR(continuation_qm);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = continuation_qm;
	inline_funcall_2(gensymed_symbol,gensymed_symbol_1,gensymed_symbol_2);
	M_CDR(reference_cons) = Nil;
    }
    return VALUES_1(Nil);
}

static Object array_constant;      /* # */

static Object array_constant_1;    /* # */

/* PRINT-ROLE-WHOSE-CAR-IS-ROLE-SERVER */
Object print_role_whose_car_is_role_server(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,21);
    twrite_symbol(1,SECOND(role));
    if (local_variable_qm) {
	twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)1L));
	twrite(local_variable_qm);
    }
    return twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)3L));
}

static Object string_constant;     /* " " */

/* PRINT-STANDARD-TWO-ELEMENT-ROLE */
Object print_standard_two_element_role(role,local_variable_qm,role_string)
    Object role, local_variable_qm, role_string;
{
    x_note_fn_call(149,22);
    print_user_or_datum_type(SECOND(role));
    if (local_variable_qm) {
	twrite(string_constant);
	twrite(local_variable_qm);
    }
    return twrite_general_string(role_string);
}

/* INVERTIBLE-DESIGNATION-P */
Object invertible_designation_p(designation)
    Object designation;
{
    Object temp, role;

    x_note_fn_call(149,23);
    temp = SYMBOLP(designation) ? T : Nil;
    if (temp);
    else {
	role = simple_role_of_role(role_of_designation(designation));
	temp = invertible_role_p(role) ? 
		invertible_designation_p(domain_of_designation(designation)) 
		: Qnil;
    }
    return VALUES_1(temp);
}

static Object Qrole_server;        /* role-server */

static Object Qinverse_role_server;  /* inverse-role-server */

/* INVERTIBLE-ROLE-P */
Object invertible_role_p(role)
    Object role;
{
    Object temp, role_1, role_car, gensymed_symbol;
    char temp_1;

    x_note_fn_call(149,24);
    temp = SYMBOLP(role) ? T : Nil;
    if (temp);
    else {
	if (CONSP(role)) {
	    role_1 = role;
	    role_car = M_CAR(role_1);
	    gensymed_symbol = EQ(role_car,Qrole_server) ? 
		    M_CAR(M_CDR(role_1)) : role_car;
	    temp_1 = 
		    TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		    Qinverse_role_server));
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    temp = atomic_naming_element_of_role(role);
	    temp = SYMBOLP(temp) ? T : Nil;
	}
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qdefined_type_of_role;  /* defined-type-of-role */

/* TYPE-OF-DESIGNATION */
Object type_of_designation(designation)
    Object designation;
{
    Object role, temp, role_1, role_car, role_name, role_type_qm;

    x_note_fn_call(149,25);
    if (CONSP(designation)) {
	role = simple_role_of_role(role_of_designation(designation));
	if (SYMBOLP(role))
	    temp = THIRD(designation) ? Nil : role;
	else {
	    role_1 = role;
	    role_car = M_CAR(role_1);
	    role_name = EQ(role_car,Qrole_server) ? M_CAR(M_CDR(role_1)) : 
		    role_car;
	    role_type_qm = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(role_name),
		    Qdefined_type_of_role);
	    temp = role_type_qm;
	    if (temp);
	    else {
		temp = last(role,_);
		temp = CAR(temp);
	    }
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* TYPE-OF-ROLE */
Object type_of_role(non_atomic_role)
    Object non_atomic_role;
{
    Object role, role_1, role_car, role_name, role_type_qm, temp;

    x_note_fn_call(149,26);
    role = simple_role_of_role(non_atomic_role);
    role_1 = role;
    role_car = M_CAR(role_1);
    role_name = EQ(role_car,Qrole_server) ? M_CAR(M_CDR(role_1)) : role_car;
    role_type_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(role_name),
	    Qdefined_type_of_role);
    temp = role_type_qm;
    if (temp);
    else {
	temp = last(role,_);
	temp = CAR(temp);
    }
    return VALUES_1(temp);
}

/* TYPE-SPECIFICATION-OF-ROLE */
Object type_specification_of_role(non_atomic_role)
    Object non_atomic_role;
{
    Object role, role_1, role_car, role_name, defined_role_type_qm, temp;
    Object type_in_role_spec_qm;

    x_note_fn_call(149,27);
    role = simple_role_of_role(non_atomic_role);
    if (CONSP(role)) {
	role_1 = role;
	role_car = M_CAR(role_1);
	role_name = EQ(role_car,Qrole_server) ? M_CAR(M_CDR(role_1)) : 
		role_car;
    }
    else
	role_name = role;
    defined_role_type_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(role_name),
	    Qdefined_type_of_role);
    temp = defined_role_type_qm;
    if (temp)
	return VALUES_1(temp);
    else {
	if (CONSP(role)) {
	    temp = last(role,_);
	    type_in_role_spec_qm = CAR(temp);
	}
	else
	    type_in_role_spec_qm = Nil;
	if (type_in_role_spec_qm) {
	    temp = 
		    type_specification_for_user_or_datum_type(type_in_role_spec_qm);
	    if (temp)
		return VALUES_1(temp);
	    else if (SYMBOLP(type_in_role_spec_qm))
		return make_class_type_specification(type_in_role_spec_qm);
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
}

/* TYPE-SPECIFICATION-OF-DESIGNATION */
Object type_specification_of_designation(designation)
    Object designation;
{
    Object role;

    x_note_fn_call(149,28);
    if (CONSP(designation)) {
	role = simple_role_of_role(role_of_designation(designation));
	if (SYMBOLP(role)) {
	    if (THIRD(designation))
		return VALUES_1(Nil);
	    else
		return make_class_type_specification(role);
	}
	else
	    return type_specification_of_role(role);
    }
    else
	return VALUES_1(Nil);
}

/* UNIQUE-DESIGNATION-P */
Object unique_designation_p(designation)
    Object designation;
{
    Object temp;

    x_note_fn_call(149,29);
    temp = SYMBOLP(designation) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else if (EQ(CAR(designation),Qthe))
	return unique_designation_p(domain_of_designation(designation));
    else
	return VALUES_1(Nil);
}

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

static Object Qparent_frame;       /* parent-frame */

static Object Qparent_attribute_name;  /* parent-attribute-name */

static Object Qclass_qualified_name;  /* class-qualified-name */

/* GENERATE-DESIGNATION-FOR-BLOCK */
Object generate_designation_for_block(block)
    Object block;
{
    Object name_or_names_qm, parent_frame_qm, parent_attribute_qm, parent_qm;
    Object parent_description_qm, parent_designation_qm, slot_description_qm;
    Object temp;
    char temp_1;

    x_note_fn_call(149,30);
    name_or_names_qm = get_lookup_slot_value_given_default(block,
	    Qname_or_names_for_frame,Nil);
    if (name_or_names_qm && SYMBOLP(name_or_names_qm))
	return VALUES_1(name_or_names_qm);
    else if (CONSP(name_or_names_qm))
	return VALUES_1(CAR(name_or_names_qm));
    else {
	parent_frame_qm = get_lookup_slot_value_given_default(block,
		Qparent_frame,Nil);
	parent_attribute_qm = get_lookup_slot_value_given_default(block,
		Qparent_attribute_name,Nil);
	parent_qm = parent(block);
	parent_description_qm = parent_qm ? 
		lookup_global_or_kb_specific_property_value(ISVREF(ISVREF(parent_qm,
		(SI_Long)1L),(SI_Long)1L),Class_description_gkbprop) : Nil;
	parent_designation_qm = parent_frame_qm ? 
		generate_designation_for_block(parent_frame_qm) : Nil;
	slot_description_qm = parent_attribute_qm && parent_description_qm 
		? 
		get_slot_description_of_class_description_function(parent_attribute_qm,
		parent_description_qm,Nil) : Qnil;
	if (slot_description_qm && parent_description_qm) {
	    if ( ! !TRUEP(ISVREF(slot_description_qm,(SI_Long)8L))) {
		temp = ISVREF(slot_description_qm,(SI_Long)3L);
		temp_1 =  !EQ(temp,
			ISVREF(get_slot_description_of_class_description_function(ISVREF(slot_description_qm,
			(SI_Long)2L),parent_description_qm,Nil),(SI_Long)3L));
	    }
	    else
		temp_1 = TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    return eval_list_3(Qthe,eval_list_3(Qclass_qualified_name,
		    ISVREF(slot_description_qm,(SI_Long)3L),
		    ISVREF(slot_description_qm,(SI_Long)2L)),
		    parent_designation_qm);
	else if (parent_designation_qm)
	    return eval_list_3(Qthe,ISVREF(slot_description_qm,
		    (SI_Long)2L),parent_designation_qm);
	else
	    return VALUES_1(Qnil);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Note_things_encountered_during_role_service_qm, Qnote_things_encountered_during_role_service_qm);

Object Role_predicate_function_prop = UNBOUND;

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qrole_predicate_function;  /* role-predicate-function */

/* VALUE-OF-ROLE-P */
Object value_of_role_p(value_to_check,quantifier,role,domain)
    Object value_to_check, quantifier, role, domain;
{
    Object x2, role_1, role_car, role_name_qm, predicate_function_qm, temp_1;
    Object value_qm, gensymed_symbol, skip_list, key_value, marked, pred, curr;
    Object succ, reference, temp_2, entry_hash, sub_class_bit_vector;
    Object role_value_qm, continuation_qm, expiration_qm, gensymed_symbol_4;
    Object gensymed_symbol_5;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Object result;

    x_note_fn_call(149,31);
    if (SIMPLE_VECTOR_P(value_to_check) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value_to_check)) > (SI_Long)2L 
	    &&  !EQ(ISVREF(value_to_check,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(value_to_check,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if ( !temp)
	return VALUES_1(Nil);
    else {
	if (CONSP(role)) {
	    role_1 = role;
	    role_car = M_CAR(role_1);
	    role_name_qm = EQ(role_car,Qrole_server) ? 
		    M_CAR(M_CDR(role_1)) : role_car;
	}
	else
	    role_name_qm = Nil;
	predicate_function_qm = role_name_qm ? 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(role_name_qm),
		Qrole_predicate_function) : Nil;
	if (predicate_function_qm) {
	    temp_1 = SYMBOL_FUNCTION(predicate_function_qm);
	    return FUNCALL_4(temp_1,value_to_check,quantifier,role,domain);
	}
	else if (EQ(quantifier,Qthe)) {
	    if (SYMBOLP(role) &&  !TRUEP(domain))
		return VALUES_1(Nil);
	    else if (SYMBOLP(role)) {
		if (EQ(get_lookup_slot_value_given_default(value_to_check,
			Qparent_attribute_name,Nil),role))
		    return VALUES_1(EQ(get_lookup_slot_value_given_default(value_to_check,
			    Qparent_frame,Nil),domain) ? T : Nil);
		else
		    return VALUES_1(Nil);
	    }
	    else {
		value_qm = 
			serve_unique_item_or_evaluation_value_of_role(role,
			domain,Nil,Nil);
		gensymed_symbol = value_qm;
		temp = FIXNUMP(gensymed_symbol);
		if (temp);
		else
		    temp = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) 
			    != (SI_Long)0L ? 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			    == (SI_Long)1L : TRUEP(Qnil);
		if (temp);
		else
		    temp = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
			    (SI_Long)0L ? 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			    == (SI_Long)1L : TRUEP(Qnil);
		if (temp);
		else
		    temp = gensymed_symbol ? SYMBOLP(gensymed_symbol) : 
			    TRUEP(Qnil);
		if (temp);
		else
		    temp = 
			    INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
			    != (SI_Long)0L;
		if (temp);
		else if (CONSP(gensymed_symbol)) {
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    temp = EQ(gensymed_symbol,Qtruth_value);
		    if (temp);
		    else
			temp = EQ(gensymed_symbol,Qiteration_state);
		    if (temp);
		    else if (SYMBOLP(gensymed_symbol)) {
			skip_list = CDR(Defined_evaluation_value_types);
			key_value = gensymed_symbol;
			key_hash_value = SXHASH_SYMBOL_1(gensymed_symbol) 
				& IFIX(Most_positive_fixnum);
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
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_1:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_2 = ATOMIC_REF_OBJECT(reference);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_2,temp_1);
			MVS_2(result,succ,marked);
		      next_loop_2:
			if ( !TRUEP(marked))
			    goto end_loop_1;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_2 = ATOMIC_REF_OBJECT(reference);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_2,temp_1);
			MVS_2(result,succ,marked);
			goto next_loop_2;
		      end_loop_1:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			temp = IFIX(ISVREF(curr,(SI_Long)1L)) == 
				key_hash_value ? (EQ(key_value,ISVREF(curr,
				(SI_Long)2L)) ? TRUEP(ISVREF(curr,
				(SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    reclaim_evaluation_value(value_qm);
		    return VALUES_1(Nil);
		}
		else
		    return VALUES_1(EQ(value_qm,value_to_check) ? T : Nil);
	    }
	}
	else if (SYMBOLP(role) &&  !TRUEP(domain)) {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(role,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(value_to_check,
			(SI_Long)1L),(SI_Long)19L);
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
		    return VALUES_1((SI_Long)0L < gensymed_symbol_1 ? T : Nil);
		}
		else
		    return VALUES_1(Nil);
	    }
	    else
		return VALUES_1(Nil);
	}
	else {
	    role_value_qm = Nil;
	    continuation_qm = Nil;
	    expiration_qm = Nil;
	    result = serve_first_item_or_evaluation_value_of_role(4,role,
		    domain,Nil,Nil);
	    MVS_3(result,role_value_qm,continuation_qm,expiration_qm);
	  next_loop_3:
	    if ( !TRUEP(expiration_qm))
		goto end_loop_3;
	    if (EQ(role_value_qm,value_to_check)) {
		if (continuation_qm) {
		    gensymed_symbol = M_CAR(continuation_qm);
		    gensymed_symbol_4 = Nil;
		    gensymed_symbol_5 = continuation_qm;
		    inline_funcall_2(gensymed_symbol,gensymed_symbol_4,
			    gensymed_symbol_5);
		}
		return VALUES_1(T);
	    }
	    else if ( !(FIXNUMP(role_value_qm) || SYMBOLP(role_value_qm) 
		    || SIMPLE_VECTOR_P(role_value_qm)))
		reclaim_if_evaluation_value_1(role_value_qm);
	    if ( !TRUEP(continuation_qm))
		expiration_qm = Nil;
	    else {
		gensymed_symbol = M_CAR(continuation_qm);
		gensymed_symbol_4 = T;
		gensymed_symbol_5 = continuation_qm;
		result = inline_funcall_2(gensymed_symbol,
			gensymed_symbol_4,gensymed_symbol_5);
		MVS_3(result,role_value_qm,continuation_qm,expiration_qm);
	    }
	    goto next_loop_3;
	  end_loop_3:
	    return VALUES_1(Qnil);
	}
    }
}

Object First_value_ok_for_the_prop = UNBOUND;

static Object Qnamed_by;           /* named-by */

static Object Qfirst_value_ok_for_the;  /* first-value-ok-for-the */

/* SERVE-UNIQUE-ITEM-OR-EVALUATION-VALUE-OF-ROLE */
Object serve_unique_item_or_evaluation_value_of_role(role,domain,
	    domain_2_qm,domains_already_type_checked_qm)
    Object role, domain, domain_2_qm, domains_already_type_checked_qm;
{
    Object first_value, continuation, first_expiration, role_1, role_car;
    Object name_of_the_role, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, second_value, second_expiration;
    Object result;

    x_note_fn_call(149,32);
    result = serve_first_item_or_evaluation_value_of_role(4,role,domain,
	    domain_2_qm,domains_already_type_checked_qm);
    MVS_3(result,first_value,continuation,first_expiration);
    if (first_expiration) {
	if ( !TRUEP(continuation))
	    return VALUES_3(first_value,first_expiration,Nil);
	else {
	    if (CONSP(role)) {
		role_1 = role;
		role_car = M_CAR(role_1);
		name_of_the_role = EQ(role_car,Qrole_server) ? 
			M_CAR(M_CDR(role_1)) : role_car;
	    }
	    else
		name_of_the_role = role;
	    if (EQ(name_of_the_role,Qnamed_by) ? 
		    TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(name_of_the_role),
		    Qfirst_value_ok_for_the)) : 
		    TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(name_of_the_role),
		    Qfirst_value_ok_for_the))) {
		gensymed_symbol = M_CAR(continuation);
		gensymed_symbol_1 = Nil;
		gensymed_symbol_2 = continuation;
		inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
			gensymed_symbol_2);
		return VALUES_3(first_value,first_expiration,Nil);
	    }
	    else {
		gensymed_symbol = M_CAR(continuation);
		gensymed_symbol_1 = T;
		gensymed_symbol_2 = continuation;
		result = inline_funcall_2(gensymed_symbol,
			gensymed_symbol_1,gensymed_symbol_2);
		MVS_3(result,second_value,continuation,second_expiration);
		if (second_expiration) {
		    if (continuation) {
			gensymed_symbol = M_CAR(continuation);
			gensymed_symbol_1 = Nil;
			gensymed_symbol_2 = continuation;
			inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
				gensymed_symbol_2);
		    }
		    if ( !(FIXNUMP(second_value) || SYMBOLP(second_value) 
			    || SIMPLE_VECTOR_P(second_value)))
			reclaim_if_evaluation_value_1(second_value);
		    return VALUES_3(Nil,Nil,T);
		}
		else if (continuation) {
		    gensymed_symbol = M_CAR(continuation);
		    gensymed_symbol_1 = Nil;
		    gensymed_symbol_2 = continuation;
		    inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
			    gensymed_symbol_2);
		    return VALUES_3(first_value,first_expiration,Nil);
		}
		else
		    return VALUES_3(first_value,first_expiration,Nil);
	    }
	}
    }
    else if (continuation) {
	gensymed_symbol = M_CAR(continuation);
	gensymed_symbol_1 = T;
	gensymed_symbol_2 = continuation;
	result = inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2);
	MVS_3(result,first_value,continuation,first_expiration);
	if (first_expiration) {
	    if ( !TRUEP(continuation))
		return VALUES_3(first_value,first_expiration,Nil);
	    else {
		if (CONSP(role)) {
		    role_1 = role;
		    role_car = M_CAR(role_1);
		    name_of_the_role = EQ(role_car,Qrole_server) ? 
			    M_CAR(M_CDR(role_1)) : role_car;
		}
		else
		    name_of_the_role = role;
		if (EQ(name_of_the_role,Qnamed_by) ? 
			TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(name_of_the_role),
			Qfirst_value_ok_for_the)) : 
			TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(name_of_the_role),
			Qfirst_value_ok_for_the))) {
		    gensymed_symbol = M_CAR(continuation);
		    gensymed_symbol_1 = Nil;
		    gensymed_symbol_2 = continuation;
		    inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
			    gensymed_symbol_2);
		    return VALUES_3(first_value,first_expiration,Nil);
		}
		else {
		    gensymed_symbol = M_CAR(continuation);
		    gensymed_symbol_1 = T;
		    gensymed_symbol_2 = continuation;
		    result = inline_funcall_2(gensymed_symbol,
			    gensymed_symbol_1,gensymed_symbol_2);
		    MVS_3(result,second_value,continuation,second_expiration);
		    if (second_expiration) {
			if ( !(FIXNUMP(second_value) || 
				SYMBOLP(second_value) || 
				SIMPLE_VECTOR_P(second_value)))
			    reclaim_if_evaluation_value_1(second_value);
			if (continuation) {
			    gensymed_symbol = M_CAR(continuation);
			    gensymed_symbol_1 = Nil;
			    gensymed_symbol_2 = continuation;
			    inline_funcall_2(gensymed_symbol,
				    gensymed_symbol_1,gensymed_symbol_2);
			}
			return VALUES_3(Nil,Nil,T);
		    }
		    else if (continuation) {
			gensymed_symbol = M_CAR(continuation);
			gensymed_symbol_1 = Nil;
			gensymed_symbol_2 = continuation;
			inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
				gensymed_symbol_2);
			return VALUES_3(first_value,first_expiration,Nil);
		    }
		    else
			return VALUES_3(first_value,first_expiration,Nil);
		}
	    }
	}
	else if (continuation) {
	    gensymed_symbol = M_CAR(continuation);
	    gensymed_symbol_1 = Nil;
	    gensymed_symbol_2 = continuation;
	    inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2);
	    return VALUES_3(Nil,Nil,Nil);
	}
	else
	    return VALUES_3(Nil,Nil,Nil);
    }
    else
	return VALUES_3(Nil,Nil,Nil);
}

/* SERVE-UNIQUE-VALUE-OF-ROLE */
Object serve_unique_value_of_role varargs_1(int, n)
{
    Object role, domain;
    Object domain_2_qm, value_qm, expiration_qm, too_many_values_qm;
    Object gensymed_symbol, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_1, temp_2, entry_hash;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(149,33);
    INIT_ARGS_nonrelocating();
    role = REQUIRED_ARG_nonrelocating();
    domain = REQUIRED_ARG_nonrelocating();
    domain_2_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    result = serve_unique_item_or_evaluation_value_of_role(role,domain,
	    domain_2_qm,Nil);
    MVS_3(result,value_qm,expiration_qm,too_many_values_qm);
    if (expiration_qm) {
	gensymed_symbol = value_qm;
	temp = FIXNUMP(gensymed_symbol);
	if (temp);
	else
	    temp = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
		    (SI_Long)0L ? 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		    (SI_Long)1L : TRUEP(Qnil);
	if (temp);
	else
	    temp = INLINE_LONG_VECTOR_P(gensymed_symbol) != (SI_Long)0L ? 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		    (SI_Long)1L : TRUEP(Qnil);
	if (temp);
	else
	    temp = gensymed_symbol ? SYMBOLP(gensymed_symbol) : TRUEP(Qnil);
	if (temp);
	else
	    temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) != 
		    (SI_Long)0L;
	if (temp);
	else if (CONSP(gensymed_symbol)) {
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    temp = EQ(gensymed_symbol,Qtruth_value);
	    if (temp);
	    else
		temp = EQ(gensymed_symbol,Qiteration_state);
	    if (temp);
	    else if (SYMBOLP(gensymed_symbol)) {
		skip_list = CDR(Defined_evaluation_value_types);
		key_value = gensymed_symbol;
		key_hash_value = SXHASH_SYMBOL_1(gensymed_symbol) & 
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_1:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_2:
		if ( !TRUEP(marked))
		    goto end_loop_1;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
		goto next_loop_2;
	      end_loop_1:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
		temp = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
			(EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
			TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : 
			TRUEP(Nil);
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
	value_qm = 
		transform_evaluation_value_into_temporary_constant(value_qm);
    return VALUES_3(value_qm,expiration_qm,too_many_values_qm);
}

/* SERVE-EVAL-LIST-OF-ROLE-VALUES */
Object serve_eval_list_of_role_values(role,domain)
    Object role, domain;
{
    Object value, continuation, expiration, barren_continuation, values_so_far;
    Object last_cons_so_far, cdr_new_value, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2;
    Object result;

    x_note_fn_call(149,34);
    result = serve_first_item_or_temporary_constant_of_role(role,domain,Nil);
    MVS_3(result,value,continuation,expiration);
    barren_continuation = Nil;
    values_so_far = Nil;
    last_cons_so_far = Nil;
  next_loop:
    if (expiration) {
	if (CONSP(last_cons_so_far)) {
	    cdr_new_value = eval_cons_1(value,Nil);
	    M_CDR(last_cons_so_far) = cdr_new_value;
	    last_cons_so_far = CDR(last_cons_so_far);
	}
	else {
	    values_so_far = eval_cons_1(value,Nil);
	    last_cons_so_far = values_so_far;
	}
	barren_continuation = Nil;
    }
    else if (barren_continuation) {
	gensymed_symbol = M_CAR(continuation);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = continuation;
	inline_funcall_2(gensymed_symbol,gensymed_symbol_1,gensymed_symbol_2);
	return VALUES_1(values_so_far);
    }
    else
	barren_continuation = T;
    if ( !TRUEP(continuation))
	return VALUES_1(values_so_far);
    result = serve_next_item_or_temporary_constant_of_role(continuation);
    MVS_3(result,value,continuation,expiration);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qg2_defstruct_structure_name_temporary_constant_g2_struct;  /* g2-defstruct-structure-name::temporary-constant-g2-struct */

/* SERVE-EVAL-LIST-OF-DESIGNATION-VALUES */
Object serve_eval_list_of_designation_values(designation)
    Object designation;
{
    Object value_qm, result_list, domain_values, domain, ab_loop_list_, temp;
    Object role_value_qm, continuation_qm, expiration_qm;
    Object result;

    x_note_fn_call(149,35);
    if (SYMBOLP(designation)) {
	value_qm = evaluate_designation(designation,Nil);
	if (value_qm)
	    return eval_cons_1(value_qm,Nil);
	else
	    return VALUES_1(Nil);
    }
    else if (IFIX(length(designation)) == (SI_Long)2L) {
	if (EQ(CAR(designation),Qthe)) {
	    value_qm = serve_unique_value_of_role(2,
		    role_of_designation(designation),Nil);
	    if (value_qm)
		return eval_cons_1(value_qm,Nil);
	    else
		return VALUES_1(Nil);
	}
	else
	    return serve_eval_list_of_role_values(role_of_designation(designation),
		    Nil);
    }
    else {
	result_list = Nil;
	domain_values = 
		serve_eval_list_of_designation_values(domain_of_designation(designation));
	domain = Nil;
	ab_loop_list_ = domain_values;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	domain = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(CAR(designation),Qthe)) {
	    temp = role_of_designation(designation);
	    value_qm = serve_unique_value_of_role(2,temp,domain);
	    if (value_qm)
		result_list = eval_cons_1(value_qm,result_list);
	}
	else {
	    temp = role_of_designation(designation);
	    result = serve_first_item_or_temporary_constant_of_role(temp,
		    domain,Nil);
	    MVS_3(result,role_value_qm,continuation_qm,expiration_qm);
	  next_loop_1:
	    if ( !TRUEP(expiration_qm))
		goto end_loop_1;
	    result_list = eval_cons_1(role_value_qm,result_list);
	    if ( !TRUEP(continuation_qm))
		goto end_loop_1;
	    result = serve_next_item_or_temporary_constant_of_role(continuation_qm);
	    MVS_3(result,role_value_qm,continuation_qm,expiration_qm);
	    goto next_loop_1;
	  end_loop_1:;
	}
	if (SIMPLE_VECTOR_P(domain) && EQ(ISVREF(domain,(SI_Long)0L),
		Qg2_defstruct_structure_name_temporary_constant_g2_struct))
	    reclaim_temporary_constant_1(domain);
	goto next_loop;
      end_loop:
	reclaim_eval_list_1(domain_values);
	return nreverse(result_list);
	return VALUES_1(Qnil);
    }
}

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

static Object Qrule;               /* rule */

/* COLLECT-INSTANCES-OF-CLASS-FOR-ROLE-SERVICE */
Object collect_instances_of_class_for_role_service(class_1)
    Object class_1;
{
    Object instance_list, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp, temp_1, entry_hash, gensymed_symbol, tail, head;
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_1, gensymed_symbol_2, global_properties;
    Object kb_properties, kb_specific_value, resulting_value;
    Object sub_class_bit_vector, scope_conses, ab_loopvar_, ab_loopvar__1;
    Object object_to_try, ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_skip_list_p_, ab_next_node_, ab_tail_node_, ab_current_alist_;
    Object ab_entry_cons_, ab_connection_, ab_connection_item_, connection;
    Object ab_class_for_connection_frame_, connection_frame_1;
    Object ab_less_than_branch_qm_, connection_frame_or_class, x2, instance;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp_2;
    Declare_special(2);
    Object result;

    x_note_fn_call(149,36);
    instance_list = Nil;
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
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol_3 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_4 = (SI_Long)1L;
	    gensymed_symbol_5 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_4 = gensymed_symbol_4 << gensymed_symbol_5;
	    gensymed_symbol_3 = gensymed_symbol_3 & gensymed_symbol_4;
	    temp_2 = (SI_Long)0L < gensymed_symbol_3;
	}
	else
	    temp_2 = TRUEP(Nil);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	object_to_try = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,1);
	  ab_loopvar_ = collect_subclasses(Qblock);
	next_loop_12:
	  if ( !TRUEP(ab_loopvar__1)) {
	    next_loop_13:
	      if ( !TRUEP(ab_loopvar_))
		  goto end_loop_12;
	      ab_loopvar__1 = 
		      lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		      Instances_specific_to_this_class_kbprop);
	      ab_loopvar_ = M_CDR(ab_loopvar_);
	      if (ab_loopvar__1)
		  goto end_loop_12;
	      goto next_loop_13;
	    end_loop_12:
	      temp_2 =  !TRUEP(ab_loopvar__1);
	  }
	  else
	      temp_2 = TRUEP(Nil);
	  if (temp_2)
	      goto end_loop_13;
	  object_to_try = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  sub_class_bit_vector = ISVREF(ISVREF(object_to_try,(SI_Long)1L),
		  (SI_Long)19L);
	  superior_class_bit_number = 
		  IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
	  sub_class_vector_index = superior_class_bit_number >>  -  - 
		  (SI_Long)3L;
	  if (sub_class_vector_index < 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	      gensymed_symbol_3 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		      sub_class_vector_index);
	      gensymed_symbol_4 = (SI_Long)1L;
	      gensymed_symbol_5 = superior_class_bit_number & (SI_Long)7L;
	      gensymed_symbol_4 = gensymed_symbol_4 << gensymed_symbol_5;
	      gensymed_symbol_3 = gensymed_symbol_3 & gensymed_symbol_4;
	      temp_2 = (SI_Long)0L < gensymed_symbol_3;
	  }
	  else
	      temp_2 = TRUEP(Nil);
	  if ( !temp_2) {
	      scope_conses = Scope_conses;
	      ab_node_stack_ = Nil;
	      ab_current_node_ = Nil;
	      gensymed_symbol = ACCESS_ONCE(ISVREF(object_to_try,
		      (SI_Long)14L));
	      gensymed_symbol = gensymed_symbol ? 
		      ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
	      ab_skip_list_form_ = gensymed_symbol;
	      ab_skip_list_p_ = Nil;
	      ab_next_node_ = Nil;
	      ab_tail_node_ = Nil;
	      ab_current_alist_ = Nil;
	      ab_entry_cons_ = Nil;
	      ab_connection_ = Nil;
	      ab_connection_item_ = Nil;
	      connection = Nil;
	      ab_class_for_connection_frame_ = class_1;
	      PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		      0);
		connection_frame_1 = Nil;
		gensymed_symbol = CDR(ab_skip_list_form_);
		if (CONSP(gensymed_symbol)) {
		    temp_1 = M_CAR(gensymed_symbol);
		    temp_2 = SIMPLE_VECTOR_P(temp_1);
		}
		else
		    temp_2 = TRUEP(Nil);
		if (temp_2) {
		    temp_1 = M_CDR(gensymed_symbol);
		    ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
		}
		else
		    ab_skip_list_p_ = Nil;
		if (ab_skip_list_p_) {
		    ab_next_node_ = 
			    ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
			    (SI_Long)0L),(SI_Long)0L));
		    ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
		    if (EQ(ab_next_node_,ab_tail_node_))
			ab_next_node_ = Nil;
		}
		else
		    ab_next_node_ = CDR(ab_skip_list_form_);
	      next_loop_14:
	      next_loop_15:
		if (ab_current_alist_) {
		    ab_entry_cons_ = M_CAR(ab_current_alist_);
		    ab_connection_ = M_CAR(ab_entry_cons_);
		    ab_connection_item_ = M_CDR(ab_entry_cons_);
		    ab_current_alist_ = M_CDR(ab_current_alist_);
		}
		else if (ab_skip_list_p_) {
		    if (ab_next_node_) {
			ab_current_node_ = ab_next_node_;
			ab_next_node_ = 
				ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node_,
				(SI_Long)0L),(SI_Long)0L));
			if (EQ(ab_next_node_,ab_tail_node_))
			    ab_next_node_ = Nil;
			ab_connection_ = ISVREF(ab_current_node_,(SI_Long)2L);
			ab_connection_item_ = ISVREF(ab_current_node_,
				(SI_Long)3L);
		    }
		    else
			ab_current_node_ = Nil;
		}
		else {
		    if (ab_next_node_) {
			ab_current_node_ = ab_next_node_;
			ab_less_than_branch_qm_ = Nil;
		      next_loop_16:
			ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
				(SI_Long)1L);
			if ( !TRUEP(ab_less_than_branch_qm_))
			    goto end_loop_14;
			ab_node_stack_ = scope_cons(ab_current_node_,
				ab_node_stack_);
			ab_current_node_ = ab_less_than_branch_qm_;
			goto next_loop_16;
		      end_loop_14:;
		    }
		    else if (ab_node_stack_) {
			ab_next_node_ = ab_node_stack_;
			ab_current_node_ = M_CAR(ab_node_stack_);
			ab_node_stack_ = M_CDR(ab_node_stack_);
		    }
		    else
			ab_current_node_ = Nil;
		    if (ab_current_node_) {
			ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
			ab_current_alist_ = ISVREF(ab_current_node_,
				(SI_Long)3L);
			ab_entry_cons_ = M_CAR(ab_current_alist_);
			ab_connection_ = M_CAR(ab_entry_cons_);
			ab_connection_item_ = M_CDR(ab_entry_cons_);
			ab_current_alist_ = M_CDR(ab_current_alist_);
		    }
		}
		temp_2 =  !TRUEP(ab_current_node_);
		if (temp_2);
		else if (ab_current_node_ && ab_connection_ && 
			EQ(ISVREF(ab_connection_,(SI_Long)3L),object_to_try)) {
		    connection_frame_or_class = ISVREF(ab_connection_,
			    (SI_Long)1L);
		    if (SYMBOLP(connection_frame_or_class)) {
			gensymed_symbol = 
				lookup_global_or_kb_specific_property_value(connection_frame_or_class,
				Class_description_gkbprop);
			temp_2 = gensymed_symbol ? 
				TRUEP(memq_function(ab_class_for_connection_frame_,
				ISVREF(gensymed_symbol,(SI_Long)2L))) : 
				TRUEP(Nil);
		    }
		    else {
			if (SIMPLE_VECTOR_P(connection_frame_or_class) && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_or_class)) 
				> (SI_Long)2L &&  
				!EQ(ISVREF(connection_frame_or_class,
				(SI_Long)1L),Qavailable_frame_vector)) {
			    x2 = ISVREF(connection_frame_or_class,(SI_Long)1L);
			    gensymed_symbol = SIMPLE_VECTOR_P(x2) && 
				    EQ(ISVREF(x2,(SI_Long)0L),
				    Qg2_defstruct_structure_name_class_description_g2_struct) 
				    ? x2 : Qnil;
			}
			else
			    gensymed_symbol = Nil;
			if (gensymed_symbol) {
			    gensymed_symbol_1 = 
				    lookup_global_or_kb_specific_property_value(ab_class_for_connection_frame_,
				    Class_description_gkbprop);
			    if (gensymed_symbol_1) {
				sub_class_bit_vector = 
					ISVREF(gensymed_symbol,(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(gensymed_symbol_1,
					(SI_Long)18L));
				sub_class_vector_index = 
					superior_class_bit_number >>  -  - 
					(SI_Long)3L;
				if (sub_class_vector_index < 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					    {
				    gensymed_symbol_3 = 
					    UBYTE_8_ISAREF_1(sub_class_bit_vector,
					    sub_class_vector_index);
				    gensymed_symbol_4 = (SI_Long)1L;
				    gensymed_symbol_5 = 
					    superior_class_bit_number & 
					    (SI_Long)7L;
				    gensymed_symbol_4 = gensymed_symbol_4 
					    << gensymed_symbol_5;
				    gensymed_symbol_3 = gensymed_symbol_3 
					    & gensymed_symbol_4;
				    temp_2 = (SI_Long)0L < gensymed_symbol_3;
				}
				else
				    temp_2 = TRUEP(Nil);
			    }
			    else
				temp_2 = TRUEP(Nil);
			}
			else
			    temp_2 = TRUEP(Nil);
		    }
		}
		else
		    temp_2 = TRUEP(Nil);
		if (temp_2)
		    goto end_5;
		goto next_loop_15;
	      end_loop_15:
	      end_5:
		if ( !TRUEP(ab_current_node_))
		    goto end_loop_16;
		connection = ab_connection_;
		connection_frame_1 = 
			get_or_make_connection_frame_and_activate_if_appropriate(connection);
		instance_list = eval_cons_1(connection_frame_1,instance_list);
		goto next_loop_14;
	      end_loop_16:;
	      POP_SPECIAL();
	  }
	  goto next_loop_12;
	end_loop_13:;
	POP_SPECIAL();
    }
    else {
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
      next_loop_17:
	if (level < ab_loop_bind_)
	    goto end_loop_17;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_18:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_19:
	if ( !TRUEP(marked))
	    goto end_loop_18;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_19;
      end_loop_18:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_6;
	goto next_loop_18;
      end_loop_19:
      end_6:
	level = level - (SI_Long)1L;
	goto next_loop_17;
      end_loop_17:;
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
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
      next_loop_20:
	if (level < ab_loop_bind_)
	    goto end_loop_20;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_21:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_22:
	if ( !TRUEP(marked))
	    goto end_loop_21;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_22;
      end_loop_21:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_7;
	goto next_loop_21;
      end_loop_22:
      end_7:
	level = level - (SI_Long)1L;
	goto next_loop_20;
      end_loop_20:;
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
	  next_loop_23:
	    if (level < ab_loop_bind_)
		goto end_loop_23;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_24:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_25:
	    if ( !TRUEP(marked))
		goto end_loop_24;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_25;
	  end_loop_24:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_8;
	    goto next_loop_24;
	  end_loop_25:
	  end_8:
	    level = level - (SI_Long)1L;
	    goto next_loop_23;
	  end_loop_23:;
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
	  next_loop_26:
	    if (level < ab_loop_bind_)
		goto end_loop_26;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_27:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_28:
	    if ( !TRUEP(marked))
		goto end_loop_27;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_28;
	  end_loop_27:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_9;
	    goto next_loop_27;
	  end_loop_28:
	  end_9:
	    level = level - (SI_Long)1L;
	    goto next_loop_26;
	  end_loop_26:;
	    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (resulting_value);
	    else
		resulting_value = Nil;
	}
	gensymed_symbol = resulting_value;
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(Rule_class_description,
		    (SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol_3 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_4 = (SI_Long)1L;
		gensymed_symbol_5 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_4 = gensymed_symbol_4 << gensymed_symbol_5;
		gensymed_symbol_3 = gensymed_symbol_3 & gensymed_symbol_4;
		temp_2 = (SI_Long)0L < gensymed_symbol_3;
	    }
	    else
		temp_2 = TRUEP(Nil);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    scope_conses = Scope_conses;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    instance = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
	      ab_loopvar_ = collect_subclasses(class_1);
	    next_loop_29:
	      if ( !TRUEP(ab_loopvar__1)) {
		next_loop_30:
		  if ( !TRUEP(ab_loopvar_))
		      goto end_loop_29;
		  ab_loopvar__1 = 
			  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			  Instances_specific_to_this_class_kbprop);
		  ab_loopvar_ = M_CDR(ab_loopvar_);
		  if (ab_loopvar__1)
		      goto end_loop_29;
		  goto next_loop_30;
		end_loop_29:
		  temp_2 =  !TRUEP(ab_loopvar__1);
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      if (temp_2)
		  goto end_loop_30;
	      instance = ab_loopvar__1;
	      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	      if ( !TRUEP(rule_is_embedded_p(instance)))
		  instance_list = eval_cons_1(instance,instance_list);
	      goto next_loop_29;
	    end_loop_30:;
	    POP_SPECIAL();
	}
	else {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(Qrule,
		    Class_description_gkbprop);
	    if (gensymed_symbol ? TRUEP(memq_function(class_1,
		    ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil)) {
		scope_conses = Scope_conses;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		instance = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			0);
		  ab_loopvar_ = collect_subclasses(class_1);
		next_loop_31:
		  if ( !TRUEP(ab_loopvar__1)) {
		    next_loop_32:
		      if ( !TRUEP(ab_loopvar_))
			  goto end_loop_31;
		      ab_loopvar__1 = 
			      lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			      Instances_specific_to_this_class_kbprop);
		      ab_loopvar_ = M_CDR(ab_loopvar_);
		      if (ab_loopvar__1)
			  goto end_loop_31;
		      goto next_loop_32;
		    end_loop_31:
		      temp_2 =  !TRUEP(ab_loopvar__1);
		  }
		  else
		      temp_2 = TRUEP(Nil);
		  if (temp_2)
		      goto end_loop_32;
		  instance = ab_loopvar__1;
		  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
		  if ( !TRUEP(embedded_rule_p(instance)))
		      instance_list = eval_cons_1(instance,instance_list);
		  goto next_loop_31;
		end_loop_32:;
		POP_SPECIAL();
	    }
	    else {
		scope_conses = Scope_conses;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		instance = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			0);
		  ab_loopvar_ = collect_subclasses(class_1);
		next_loop_33:
		  if ( !TRUEP(ab_loopvar__1)) {
		    next_loop_34:
		      if ( !TRUEP(ab_loopvar_))
			  goto end_loop_33;
		      ab_loopvar__1 = 
			      lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			      Instances_specific_to_this_class_kbprop);
		      ab_loopvar_ = M_CDR(ab_loopvar_);
		      if (ab_loopvar__1)
			  goto end_loop_33;
		      goto next_loop_34;
		    end_loop_33:
		      temp_2 =  !TRUEP(ab_loopvar__1);
		  }
		  else
		      temp_2 = TRUEP(Nil);
		  if (temp_2)
		      goto end_loop_34;
		  instance = ab_loopvar__1;
		  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
		  instance_list = eval_cons_1(instance,instance_list);
		  goto next_loop_33;
		end_loop_34:;
		POP_SPECIAL();
	    }
	}
    }
    return VALUES_1(instance_list);
}

DEFINE_VARIABLE_WITH_SYMBOL(There_exists_p, Qthere_exists_p);

static Object Qab_structure;       /* structure */

static Object Qrequired_domain_types_of_role;  /* required-domain-types-of-role */

static Object Qnever;              /* never */

/* SERVE-FIRST-ITEM-OR-EVALUATION-VALUE-OF-ROLE */
Object serve_first_item_or_evaluation_value_of_role varargs_1(int, n)
{
    Object role_arg, domain, domain_2_qm, domain_types_already_checked_qm;
    Object existence_qm, role, role_1, role_car, role_name, x2;
    Object domain_types_qm, coerced_value_qm, list_1, function, there_exists_p;
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_1, temp_2, entry_hash, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, global_properties;
    Object kb_properties, kb_specific_value, resulting_value, slot_value_qm;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(149,37);
    INIT_ARGS_nonrelocating();
    role_arg = REQUIRED_ARG_nonrelocating();
    domain = REQUIRED_ARG_nonrelocating();
    domain_2_qm = REQUIRED_ARG_nonrelocating();
    domain_types_already_checked_qm = REQUIRED_ARG_nonrelocating();
    existence_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    role = simple_role_of_role(role_arg);
    if (CONSP(role)) {
	role_1 = role;
	role_car = M_CAR(role_1);
	role_name = EQ(role_car,Qrole_server) ? M_CAR(M_CDR(role_1)) : 
		role_car;
    }
    else
	role_name = role;
    if ( !TRUEP(domain_types_already_checked_qm)) {
	if (SYMBOLP(role)) {
	    if ( !TRUEP(domain_2_qm)) {
		temp =  !TRUEP(domain);
		if (temp);
		else if (SIMPLE_VECTOR_P(domain) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(domain)) > 
			(SI_Long)2L &&  !EQ(ISVREF(domain,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(domain,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		if (temp);
		else
		    temp = CONSP(domain) ? EQ(M_CDR(domain),Qab_structure) 
			    : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if ( !temp) {
		write_wrong_arguments_for_role_warning(role,domain);
		return VALUES_3(Nil,Nil,Nil);
	    }
	}
	else {
	    domain_types_qm = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(role_name),
		    Qrequired_domain_types_of_role);
	    if ( !TRUEP(domain_types_qm)) {
		if (domain) {
		    write_wrong_arguments_for_role_warning(role,domain);
		    return VALUES_3(Nil,Nil,Nil);
		}
	    }
	    else if ( !TRUEP(M_CDR(domain_types_qm))) {
		if ( !(type_specification_type_p(domain,
			M_CAR(domain_types_qm)) &&  !TRUEP(domain_2_qm))) {
		    coerced_value_qm = 
			    coerce_to_type_for_role_service(domain,
			    M_CAR(domain_types_qm));
		    if (coerced_value_qm)
			domain = coerced_value_qm;
		    else if ( !(SIMPLE_VECTOR_P(domain) && 
			    EQ(ISVREF(domain,(SI_Long)0L),
			    Qg2_defstruct_structure_name_temporary_constant_g2_struct) 
			    && EQ(role_name,Qnamed_by))) {
			write_wrong_arguments_for_role_warning(role,domain);
			return VALUES_3(Nil,Nil,Nil);
		    }
		}
	    }
	    else if ( !(type_specification_type_p(domain,
		    M_CAR(domain_types_qm)) && 
		    type_specification_type_p(domain_2_qm,
		    M_CAR(M_CDR(domain_types_qm))))) {
		write_wrong_arguments_for_role_warning(role,domain);
		return VALUES_3(Nil,Nil,Nil);
	    }
	}
    }
    if (CONSP(role)) {
	list_1 = INLINE_SYMBOL_PLIST(role_name);
      next_loop:
	if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Qrole_server))
	    goto end_loop;
	list_1 = M_CDR(M_CDR(list_1));
	goto next_loop;
      end_loop:
	function = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
	there_exists_p = Is_g2_enterprise_qm ? existence_qm : Nil;
	PUSH_SPECIAL_WITH_SYMBOL(There_exists_p,Qthere_exists_p,there_exists_p,
		0);
	  if (function) {
	      if (domain_2_qm) {
		  gensymed_symbol = function;
		  gensymed_symbol_1 = role;
		  gensymed_symbol_2 = domain;
		  gensymed_symbol_3 = domain_2_qm;
		  result = inline_funcall_3(gensymed_symbol,
			  gensymed_symbol_1,gensymed_symbol_2,
			  gensymed_symbol_3);
	      }
	      else {
		  gensymed_symbol = function;
		  gensymed_symbol_1 = role;
		  gensymed_symbol_2 = domain;
		  result = inline_funcall_2(gensymed_symbol,
			  gensymed_symbol_1,gensymed_symbol_2);
	      }
	  }
	  else
	      result = VALUES_3(Nil,Nil,Nil);
	POP_SPECIAL();
	return result;
    }
    else if ( !TRUEP(domain)) {
	skip_list = CDR(Symbol_properties_table);
	key_value = role;
	key_hash_value = SXHASH_SYMBOL_1(role) & IFIX(Most_positive_fixnum);
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
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp_2);
	MVS_2(result,succ,marked);
      next_loop_3:
	if ( !TRUEP(marked))
	    goto end_loop_2;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp_2);
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
	    gensymed_symbol = role;
	    temp_1 = Symbol_properties_table;
	    temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
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
	    gensymed_symbol = set_skip_list_entry(temp_1,FIX((SI_Long)31L),
		    Qeq,Nil,T,gensymed_symbol,temp_2,gensymed_symbol_1);
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
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp_2);
	MVS_2(result,succ,marked);
      next_loop_6:
	if ( !TRUEP(marked))
	    goto end_loop_5;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp_2);
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
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_9:
	    if ( !TRUEP(marked))
		goto end_loop_8;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
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
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_12:
	    if ( !TRUEP(marked))
		goto end_loop_11;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
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
	gensymed_symbol = resulting_value;
	if (gensymed_symbol && ISVREF(gensymed_symbol,(SI_Long)16L))
	    return serve_all_unreprocessed_frames(collect_instances_of_class_for_role_service(role));
	else
	    return VALUES_3(Nil,Nil,Nil);
    }
    else {
	slot_value_qm = 
		frame_or_evaluation_value_user_attribute_value(domain,role,
		Nil);
	if (slot_value_qm)
	    return VALUES_3(slot_value_qm,Nil,Qnever);
	else
	    return VALUES_3(Nil,Nil,Nil);
    }
}

static Object Qdatum;              /* datum */

static Object Qvalue_request_pending;  /* value-request-pending */

static Object Qfloat_array;        /* float-array */

/* COERCE-TO-TYPE-FOR-ROLE-SERVICE */
Object coerce_to_type_for_role_service(item_or_value,type)
    Object item_or_value, type;
{
    volatile Object coerced_value_qm;
    Object x2, gensymed_symbol, sub_class_bit_vector;
    Object variables_that_did_not_have_values, gensymed_symbol_4;
    Object gensymed_symbol_5, gensymed_symbol_6, pruned_interest_list;
    Object eval_cons, temp_1, temp_2, amf_available_array_cons_qm, amf_array;
    Object amf_result, new_float, result_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    double aref_new_value;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(149,38);
    SAVE_STACK();
    coerced_value_qm = Nil;
    if (type_specification_subtype_in_kb_p(type,Qdatum)) {
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
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
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	if ((IFIX(Current_computation_flags) & (SI_Long)8L) != (SI_Long)0L) {
	    gensymed_symbol = Nil;
	    if (PUSH_UNWIND_PROTECT(0)) {
		variables_that_did_not_have_values = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Variables_that_did_not_have_values,Qvariables_that_did_not_have_values,variables_that_did_not_have_values,
			0);
		  coerced_value_qm = 
			  get_current_evaluation_value(item_or_value,Nil);
		  gensymed_symbol = Variables_that_did_not_have_values;
		POP_SPECIAL();
	    }
	    POP_UNWIND_PROTECT(0);
	    if (gensymed_symbol) {
		gensymed_symbol_4 = gensymed_symbol;
		gensymed_symbol_5 = Nil;
		gensymed_symbol_6 = Nil;
	      next_loop:
		gensymed_symbol_5 = CAR(gensymed_symbol_4);
		gensymed_symbol_6 = CDR(gensymed_symbol_4);
		pruned_interest_list = 
			delete_eval_element_1(Qvalue_request_pending,
			ISVREF(gensymed_symbol_5,(SI_Long)36L));
		ISVREF(gensymed_symbol_5,(SI_Long)36L) = pruned_interest_list;
		if ( !TRUEP(pruned_interest_list) &&  
			!TRUEP(ISVREF(gensymed_symbol_5,(SI_Long)38L)))
		    withdraw_backward_chaining(gensymed_symbol_5);
		if ( !TRUEP(gensymed_symbol_6))
		    goto end_loop;
		gensymed_symbol_4 = gensymed_symbol_6;
		goto next_loop;
	      end_loop:
		if (gensymed_symbol &&  !((SI_Long)0L == 
			inline_debugging_consing())) {
		    eval_cons = gensymed_symbol;
		  next_loop_1:
		    inline_note_reclaim_cons(eval_cons,Qeval);
		    if (EQ(eval_cons,gensymed_symbol_4))
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
		    temp_1 = ISVREF(Available_eval_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = gensymed_symbol;
		    temp_1 = Available_eval_conses_tail_vector;
		    temp_2 = Current_thread_index;
		    SVREF(temp_1,temp_2) = gensymed_symbol_4;
		}
		else {
		    temp_1 = Available_eval_conses_vector;
		    temp_2 = Current_thread_index;
		    SVREF(temp_1,temp_2) = gensymed_symbol;
		    temp_1 = Available_eval_conses_tail_vector;
		    temp_2 = Current_thread_index;
		    SVREF(temp_1,temp_2) = gensymed_symbol_4;
		}
		M_CDR(gensymed_symbol_4) = Nil;
	    }
	    CONTINUE_UNWINDING(0);
	}
	else
	    coerced_value_qm = get_current_evaluation_value(item_or_value,Nil);
    }
    if ( !TRUEP(coerced_value_qm))
	coerced_value_qm = item_or_value;
    if (type_specification_type_p(coerced_value_qm,type)) {
	RESTORE_STACK();
	return VALUES_1(coerced_value_qm);
    }
    else if (type_specification_type_p(coerced_value_qm,Qinteger) && 
	    type_specification_subtype_in_kb_p(type,Qfloat)) {
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
	aref_new_value = (double)IFIX(coerced_value_qm);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	result_1 = new_float;
	RESTORE_STACK();
	return VALUES_1(result_1);
    }
    else {
	if ( !EQ(item_or_value,coerced_value_qm)) {
	    if ( !(FIXNUMP(coerced_value_qm) || SYMBOLP(coerced_value_qm) 
		    || SIMPLE_VECTOR_P(coerced_value_qm)))
		reclaim_if_evaluation_value_1(coerced_value_qm);
	}
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

static Object Qrecord_block_for_tformat;  /* record-block-for-tformat */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object array_constant_2;    /* # */

static Object string_constant_1;   /* "', the argument ~NA was the wrong type of value." */

/* WRITE-WRONG-ARGUMENTS-FOR-ROLE-WARNING */
Object write_wrong_arguments_for_role_warning(role,domain)
    Object role, domain;
{
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_stack_pointer;
    Declare_special(7);
    Object result;

    x_note_fn_call(149,39);
    SAVE_STACK();
    if ((SI_Long)1L <= IFIX(Warning_message_level) &&  
		!TRUEP(Debugging_reset)) {
	if ( !TRUEP(Defer_notifications_qm))
	    break_out_of_debug_messages();
	snapshots_of_related_blocks = Nil;
	note_blocks_in_tformat = SYMBOL_FUNCTION(Qrecord_block_for_tformat);
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
		      write_warning_message_header(FIX((SI_Long)1L));
		      twrite_beginning_of_wide_string(array_constant_2,
			      FIX((SI_Long)17L));
		      print_role(role);
		      tformat(2,string_constant_1,domain);
		      temp = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    SAVE_VALUES(notify_user_1(temp));
	    if (Snapshots_of_related_blocks) {
		reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
		Snapshots_of_related_blocks = Nil;
	    }
	    result = RESTORE_VALUES();
	  POP_SPECIAL();
	POP_SPECIAL();
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

/* SERVE-FIRST-ITEM-OR-TEMPORARY-CONSTANT-OF-ROLE */
Object serve_first_item_or_temporary_constant_of_role(role,domain,domain_2_qm)
    Object role, domain, domain_2_qm;
{
    Object copied_domain, copied_domain_2_qm, value, continuation_qm;
    Object expiration_qm, gensymed_symbol, skip_list, key_value, marked, pred;
    Object curr, succ, reference, temp_1, temp_2, entry_hash;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Object result;

    x_note_fn_call(149,40);
    copied_domain = SIMPLE_VECTOR_P(domain) && EQ(ISVREF(domain,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_temporary_constant_g2_struct) ? 
	    make_evaluation_value_from_temporary_constant(domain) : domain;
    copied_domain_2_qm = SIMPLE_VECTOR_P(domain_2_qm) && 
	    EQ(ISVREF(domain_2_qm,(SI_Long)0L),
	    Qg2_defstruct_structure_name_temporary_constant_g2_struct) ? 
	    make_evaluation_value_from_temporary_constant(domain_2_qm) : 
	    domain_2_qm;
    result = serve_first_item_or_evaluation_value_of_role(4,role,
	    copied_domain,copied_domain_2_qm,Nil);
    MVS_3(result,value,continuation_qm,expiration_qm);
    if (expiration_qm) {
	gensymed_symbol = value;
	temp = FIXNUMP(gensymed_symbol);
	if (temp);
	else
	    temp = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
		    (SI_Long)0L ? 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		    (SI_Long)1L : TRUEP(Qnil);
	if (temp);
	else
	    temp = INLINE_LONG_VECTOR_P(gensymed_symbol) != (SI_Long)0L ? 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		    (SI_Long)1L : TRUEP(Qnil);
	if (temp);
	else
	    temp = gensymed_symbol ? SYMBOLP(gensymed_symbol) : TRUEP(Qnil);
	if (temp);
	else
	    temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) != 
		    (SI_Long)0L;
	if (temp);
	else if (CONSP(gensymed_symbol)) {
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    temp = EQ(gensymed_symbol,Qtruth_value);
	    if (temp);
	    else
		temp = EQ(gensymed_symbol,Qiteration_state);
	    if (temp);
	    else if (SYMBOLP(gensymed_symbol)) {
		skip_list = CDR(Defined_evaluation_value_types);
		key_value = gensymed_symbol;
		key_hash_value = SXHASH_SYMBOL_1(gensymed_symbol) & 
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_1:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_2:
		if ( !TRUEP(marked))
		    goto end_loop_1;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
		goto next_loop_2;
	      end_loop_1:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
		temp = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
			(EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
			TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : 
			TRUEP(Nil);
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
	value = transform_evaluation_value_into_temporary_constant(value);
    if ( !(FIXNUMP(copied_domain) || SYMBOLP(copied_domain) || 
	    SIMPLE_VECTOR_P(copied_domain)))
	reclaim_if_evaluation_value_1(copied_domain);
    if ( !(FIXNUMP(copied_domain_2_qm) || SYMBOLP(copied_domain_2_qm) || 
	    SIMPLE_VECTOR_P(copied_domain_2_qm)))
	reclaim_if_evaluation_value_1(copied_domain_2_qm);
    return VALUES_3(value,continuation_qm,expiration_qm);
}

static Object Qvirtual_attribute;  /* virtual-attribute */

static Object Qattribute;          /* attribute */

/* FRAME-OR-EVALUATION-VALUE-USER-ATTRIBUTE-VALUE */
Object frame_or_evaluation_value_user_attribute_value(item_or_structure,
	    attribute,class_specific_attribute_class_qm)
    Object item_or_structure, attribute, class_specific_attribute_class_qm;
{
    Object structure_slot_value_qm, temp, x2, cdr_1, gensymed_symbol;
    Object sub_class_bit_vector, slot_description_qm, user_slot_qm;
    Object unaliased_name_qm, slot_value_qm, gensymed_symbol_4, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_5, car_1;
    Object managed_value, evaluator_info, getter_qm, virtual_attribute_qm;
    Object extracted_value, reclaim_p, gensymed_symbol_6, value, category_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Object result;

    x_note_fn_call(149,41);
    if (CONSP(item_or_structure) && EQ(M_CDR(item_or_structure),
		Qab_structure)) {
	structure_slot_value_qm = 
		structure_slot_1(M_CAR(item_or_structure),attribute,Nil);
	if ( !TRUEP(structure_slot_value_qm))
	    temp = Nil;
	else {
	    if (SIMPLE_VECTOR_P(structure_slot_value_qm) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(structure_slot_value_qm)) 
		    > (SI_Long)2L &&  !EQ(ISVREF(structure_slot_value_qm,
		    (SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(structure_slot_value_qm,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		temp = serve_item_p(structure_slot_value_qm) ? 
			structure_slot_value_qm : Nil;
	    else if (CONSP(structure_slot_value_qm) && 
		    EQ(M_CDR(structure_slot_value_qm),Qtruth_value))
		temp = EQ(structure_slot_value_qm,Evaluation_true_value) 
			|| EQ(structure_slot_value_qm,
			Evaluation_false_value) ? structure_slot_value_qm :
			 eval_cons_1(M_CAR(structure_slot_value_qm),
			Qtruth_value);
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(structure_slot_value_qm) 
		    != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(structure_slot_value_qm)) 
		    == (SI_Long)1L)
		temp = copy_managed_float(structure_slot_value_qm);
	    else if (INLINE_LONG_VECTOR_P(structure_slot_value_qm) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(structure_slot_value_qm)) 
		    == (SI_Long)1L)
		temp = copy_managed_long(structure_slot_value_qm);
	    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(structure_slot_value_qm) 
		    != (SI_Long)0L)
		temp = copy_wide_string(structure_slot_value_qm);
	    else if (CONSP(structure_slot_value_qm)) {
		cdr_1 = M_CDR(structure_slot_value_qm);
		if (EQ(cdr_1,Qab_structure))
		    temp = copy_evaluation_structure(structure_slot_value_qm);
		else if (EQ(cdr_1,Qsequence))
		    temp = copy_evaluation_sequence(structure_slot_value_qm);
		else
		    temp = structure_slot_value_qm;
	    }
	    else
		temp = structure_slot_value_qm;
	}
    }
    else {
	if (class_specific_attribute_class_qm) {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(class_specific_attribute_class_qm,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(item_or_structure,
			(SI_Long)1L),(SI_Long)19L);
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
		    temp_1 = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_1 =  !temp_1;
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    temp = Nil;
	else {
	    slot_description_qm = 
		    get_slot_description_of_class_description_function(attribute,
		    ISVREF(item_or_structure,(SI_Long)1L),
		    class_specific_attribute_class_qm);
	    user_slot_qm = slot_description_qm ? 
		    ISVREF(slot_description_qm,(SI_Long)8L) : Qnil;
	    unaliased_name_qm =  !TRUEP(user_slot_qm) ? 
		    get_slot_name_for_alias_if_any(attribute,
		    item_or_structure) : Nil;
	    if (user_slot_qm) {
		slot_value_qm = 
			get_slot_description_value(item_or_structure,
			slot_description_qm);
		if ( !((SI_Long)0L != (IFIX(ISVREF(item_or_structure,
			(SI_Long)5L)) & (SI_Long)512L))) {
		    if (Note_things_encountered_during_role_service_qm) {
			gensymed_symbol = Things_that_affect_this_formula;
			gensymed_symbol_4 = item_or_structure;
			if ( !TRUEP(memq_function(gensymed_symbol_4,
				gensymed_symbol))) {
			    new_cons = ISVREF(Available_eval_conses_vector,
				    IFIX(Current_thread_index));
			    if (new_cons) {
				svref_arg_1 = Available_eval_conses_vector;
				svref_arg_2 = Current_thread_index;
				svref_new_value = M_CDR(new_cons);
				SVREF(svref_arg_1,svref_arg_2) = 
					svref_new_value;
				if ( 
					!TRUEP(ISVREF(Available_eval_conses_vector,
					IFIX(Current_thread_index)))) {
				    svref_arg_1 = 
					    Available_eval_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(svref_arg_1,svref_arg_2) = Nil;
				}
				gensymed_symbol_5 = new_cons;
			    }
			    else
				gensymed_symbol_5 = Nil;
			    if ( !TRUEP(gensymed_symbol_5))
				gensymed_symbol_5 = replenish_eval_cons_pool();
			    M_CAR(gensymed_symbol_5) = gensymed_symbol_4;
			    M_CDR(gensymed_symbol_5) = gensymed_symbol;
			    inline_note_allocate_cons(gensymed_symbol_5,Qeval);
			    Things_that_affect_this_formula = 
				    gensymed_symbol_5;
			}
		    }
		    temp_1 = TRUEP(T);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1) {
		    if ( !TRUEP(slot_value_qm))
			temp = Nil;
		    else {
			if (CONSP(slot_value_qm)) {
			    car_1 = M_CAR(slot_value_qm);
			    cdr_1 = M_CDR(slot_value_qm);
			    if (CONSP(cdr_1)) {
				temp = M_CAR(cdr_1);
				temp_1 = SYMBOLP(temp);
			    }
			    else
				temp_1 = TRUEP(Nil);
			    temp_1 = temp_1 ? slot_value_number_p(car_1) 
				    || text_string_p(car_1) || 
				    STRINGP(car_1) : TRUEP(Nil);
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1) {
			    managed_value = M_CAR(slot_value_qm);
			    if (EQ(convert_type_or_unit_of_measure_to_type(M_CAR(M_CDR(slot_value_qm))),
				    Qtruth_value)) {
				if (FIXNUM_EQ(managed_value,Truth))
				    temp = Evaluation_true_value;
				else if (FIXNUM_EQ(managed_value,Falsity))
				    temp = Evaluation_false_value;
				else
				    temp = eval_cons_1(managed_value,
					    Qtruth_value);
			    }
			    else
				temp = FIXNUMP(managed_value) || 
					SYMBOLP(managed_value) ? 
					managed_value : 
					copy_evaluation_value_1(managed_value);
			}
			else {
			    if (SIMPLE_VECTOR_P(slot_value_qm) && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_qm)) 
				    > (SI_Long)2L &&  
				    !EQ(ISVREF(slot_value_qm,(SI_Long)1L),
				    Qavailable_frame_vector)) {
				x2 = ISVREF(slot_value_qm,(SI_Long)1L);
				temp_1 = SIMPLE_VECTOR_P(x2) && 
					EQ(ISVREF(x2,(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					? TRUEP(x2) : TRUEP(Qnil);
			    }
			    else
				temp_1 = TRUEP(Nil);
			    if (temp_1)
				temp = serve_item_p(slot_value_qm) ? 
					slot_value_qm : Nil;
			    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_qm) 
				    != (SI_Long)0L && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_qm)) 
				    == (SI_Long)1L)
				temp = copy_managed_float(slot_value_qm);
			    else if (INLINE_LONG_VECTOR_P(slot_value_qm) 
				    != (SI_Long)0L && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_qm)) 
				    == (SI_Long)1L)
				temp = copy_managed_long(slot_value_qm);
			    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(slot_value_qm) 
				    != (SI_Long)0L)
				temp = copy_wide_string(slot_value_qm);
			    else if (CONSP(slot_value_qm)) {
				cdr_1 = M_CDR(slot_value_qm);
				if (EQ(cdr_1,Qab_structure))
				    temp = 
					    copy_evaluation_structure(slot_value_qm);
				else if (EQ(cdr_1,Qsequence))
				    temp = 
					    copy_evaluation_sequence(slot_value_qm);
				else
				    temp = slot_value_qm;
			    }
			    else
				temp = slot_value_qm;
			}
		    }
		}
		else
		    temp = Nil;
	    }
	    else {
		if (unaliased_name_qm)
		    slot_description_qm = 
			    get_slot_description_of_class_description_function(unaliased_name_qm,
			    ISVREF(item_or_structure,(SI_Long)1L),
			    class_specific_attribute_class_qm);
		else if (get_alias_for_slot_name_if_any(attribute,
			item_or_structure))
		    slot_description_qm = Nil;
		if (slot_description_qm) {
		    evaluator_info = ISVREF(slot_description_qm,(SI_Long)10L);
		    if (evaluator_info);
		    else
			evaluator_info = 
				cache_evaluator_slot_info(slot_description_qm);
		}
		else
		    evaluator_info = Nil;
		getter_qm = evaluator_info ? ISVREF(evaluator_info,
			(SI_Long)3L) : Nil;
		virtual_attribute_qm = Nil;
		if (getter_qm) {
		    gensymed_symbol = ISVREF(evaluator_info,(SI_Long)5L);
		    gensymed_symbol_4 = 
			    get_slot_description_value(item_or_structure,
			    slot_description_qm);
		    gensymed_symbol_5 = evaluator_info;
		    result = inline_funcall_2(gensymed_symbol,
			    gensymed_symbol_4,gensymed_symbol_5);
		    MVS_2(result,extracted_value,reclaim_p);
		    gensymed_symbol = getter_qm;
		    gensymed_symbol_4 = extracted_value;
		    gensymed_symbol_5 = item_or_structure;
		    gensymed_symbol_6 = slot_description_qm;
		    temp = inline_funcall_3(gensymed_symbol,
			    gensymed_symbol_4,gensymed_symbol_5,
			    gensymed_symbol_6);
		    if (reclaim_p)
			reclaim_slot_value(extracted_value);
		}
		else {
		    virtual_attribute_qm = get_property_value_function(3,
			    get_symbol_properties_function(attribute),
			    Qvirtual_attribute,Nil);
		    if (virtual_attribute_qm && 
			    type_specification_type_p(item_or_structure,
			    ISVREF(virtual_attribute_qm,(SI_Long)2L))) {
			getter_qm = ISVREF(virtual_attribute_qm,(SI_Long)6L);
			value = getter_qm ? inline_funcall_1(getter_qm,
				item_or_structure) : No_component_value;
			temp = EQ(value,No_component_value) ? Nil : value;
		    }
		    else if (slot_description_qm) {
			category_qm = ISVREF(evaluator_info,(SI_Long)1L);
			temp = EQ(category_qm,Qattribute) || 
				memq_function(attribute,
				Authorized_system_slots) || 
				assq_function(attribute,
				Predefined_user_attributes) ? Nil : Nil;
		    }
		    else
			temp = Qnil;
		}
	    }
	}
    }
    return VALUES_1(temp);
}

/* FRAME-OR-EVALUATION-VALUE-GIVEN-USER-VECTOR-INDEX */
Object frame_or_evaluation_value_given_user_vector_index(item,
	    user_attribute_index)
    Object item, user_attribute_index;
{
    Object gensymed_symbol, gensymed_symbol_1, new_cons, svref_arg_1;
    Object svref_arg_2, svref_new_value, gensymed_symbol_2, slot_value_qm;
    Object temp_1, car_1, cdr_1, managed_value, x2;
    char temp;

    x_note_fn_call(149,42);
    if (FIXNUMP(user_attribute_index)) {
	if ( !((SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)5L)) & 
		(SI_Long)512L))) {
	    if (Note_things_encountered_during_role_service_qm) {
		gensymed_symbol = Things_that_affect_this_formula;
		gensymed_symbol_1 = item;
		if ( !TRUEP(memq_function(gensymed_symbol_1,
			    gensymed_symbol))) {
		    new_cons = ISVREF(Available_eval_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			svref_arg_1 = Available_eval_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
			if ( !TRUEP(ISVREF(Available_eval_conses_vector,
				IFIX(Current_thread_index)))) {
			    svref_arg_1 = Available_eval_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(svref_arg_1,svref_arg_2) = Nil;
			}
			gensymed_symbol_2 = new_cons;
		    }
		    else
			gensymed_symbol_2 = Nil;
		    if ( !TRUEP(gensymed_symbol_2))
			gensymed_symbol_2 = replenish_eval_cons_pool();
		    M_CAR(gensymed_symbol_2) = gensymed_symbol_1;
		    M_CDR(gensymed_symbol_2) = gensymed_symbol;
		    inline_note_allocate_cons(gensymed_symbol_2,Qeval);
		    Things_that_affect_this_formula = gensymed_symbol_2;
		}
	    }
	    temp = TRUEP(T);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    slot_value_qm = ISVREF(ISVREF(item,(SI_Long)0L),
		    IFIX(user_attribute_index));
	    if ( !TRUEP(slot_value_qm))
		temp_1 = Nil;
	    else {
		if (CONSP(slot_value_qm)) {
		    car_1 = M_CAR(slot_value_qm);
		    cdr_1 = M_CDR(slot_value_qm);
		    if (CONSP(cdr_1)) {
			temp_1 = M_CAR(cdr_1);
			temp = SYMBOLP(temp_1);
		    }
		    else
			temp = TRUEP(Nil);
		    temp = temp ? slot_value_number_p(car_1) || 
			    text_string_p(car_1) || STRINGP(car_1) : 
			    TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    managed_value = M_CAR(slot_value_qm);
		    if (EQ(convert_type_or_unit_of_measure_to_type(M_CAR(M_CDR(slot_value_qm))),
			    Qtruth_value)) {
			if (FIXNUM_EQ(managed_value,Truth))
			    temp_1 = Evaluation_true_value;
			else if (FIXNUM_EQ(managed_value,Falsity))
			    temp_1 = Evaluation_false_value;
			else
			    temp_1 = eval_cons_1(managed_value,Qtruth_value);
		    }
		    else
			temp_1 = FIXNUMP(managed_value) || 
				SYMBOLP(managed_value) ? managed_value : 
				copy_evaluation_value_1(managed_value);
		}
		else {
		    if (SIMPLE_VECTOR_P(slot_value_qm) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_qm)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(slot_value_qm,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(slot_value_qm,(SI_Long)1L);
			temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp)
			temp_1 = serve_item_p(slot_value_qm) ? 
				slot_value_qm : Nil;
		    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_qm) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_qm)) 
			    == (SI_Long)1L)
			temp_1 = copy_managed_float(slot_value_qm);
		    else if (INLINE_LONG_VECTOR_P(slot_value_qm) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_qm)) 
			    == (SI_Long)1L)
			temp_1 = copy_managed_long(slot_value_qm);
		    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(slot_value_qm) 
			    != (SI_Long)0L)
			temp_1 = copy_wide_string(slot_value_qm);
		    else if (CONSP(slot_value_qm)) {
			cdr_1 = M_CDR(slot_value_qm);
			if (EQ(cdr_1,Qab_structure))
			    temp_1 = copy_evaluation_structure(slot_value_qm);
			else if (EQ(cdr_1,Qsequence))
			    temp_1 = copy_evaluation_sequence(slot_value_qm);
			else
			    temp_1 = slot_value_qm;
		    }
		    else
			temp_1 = slot_value_qm;
		}
	    }
	}
	else
	    temp_1 = Nil;
    }
    else
	temp_1 = frame_or_evaluation_value_user_attribute_value(item,
		FIRST(user_attribute_index),FOURTH(user_attribute_index));
    return VALUES_1(temp_1);
}

static Object Qtext;               /* text */

/* CONVERT-CONSTANT-ATTRIBUTE-VALUE-TO-CACHED-VALUE */
Object convert_constant_attribute_value_to_cached_value(constant_attribute_value)
    Object constant_attribute_value;
{
    Object temp, car_1, cdr_1;
    char temp_1;

    x_note_fn_call(149,43);
    if ( !TRUEP(constant_attribute_value))
	return VALUES_3(Nil,Nil,Nil);
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(constant_attribute_value) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(constant_attribute_value)) == 
	    (SI_Long)1L) {
	temp = 
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(constant_attribute_value,
		(SI_Long)0L));
	return VALUES_3(temp,Qnever,Qnumber);
    }
    else {
	if (CONSP(constant_attribute_value)) {
	    car_1 = M_CAR(constant_attribute_value);
	    cdr_1 = M_CDR(constant_attribute_value);
	    if (CONSP(cdr_1)) {
		temp = M_CAR(cdr_1);
		temp_1 = SYMBOLP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_1 = temp_1 ? slot_value_number_p(car_1) || 
		    text_string_p(car_1) || STRINGP(car_1) : TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    temp = 
		    get_slot_value_number_value_or_string_from_slot_constant(constant_attribute_value);
	    return VALUES_3(temp,Qnever,
		    M_CAR(M_CDR(constant_attribute_value)));
	}
	else if (NUMBERP(constant_attribute_value))
	    return VALUES_3(constant_attribute_value,Qnever,Qnumber);
	else if (SYMBOLP(constant_attribute_value))
	    return VALUES_3(constant_attribute_value,Qnever,Qsymbol);
	else if (text_string_p(constant_attribute_value))
	    return VALUES_3(constant_attribute_value,Qnever,Qtext);
	else
	    return VALUES_1(Qnil);
    }
}

/* SERVE-NEXT-EVALUATION-VALUE */
Object serve_next_evaluation_value(continue_qm,continuation)
    Object continue_qm, continuation;
{
    Object evaluation_value, ab_loop_list_, list_qm, temp, svref_arg_2;
    Object constant_to_serve, rest_qm, eval_cons;

    x_note_fn_call(149,44);
    if ( !TRUEP(continue_qm)) {
	evaluation_value = Nil;
	ab_loop_list_ = M_CDR(continuation);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	evaluation_value = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	reclaim_evaluation_value(evaluation_value);
	goto next_loop;
      end_loop:
	reclaim_eval_list_1(continuation);
	return VALUES_1(Qnil);
    }
    else {
	list_qm = M_CDR(continuation);
	if ( !TRUEP(list_qm)) {
	    inline_note_reclaim_cons(continuation,Qeval);
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = continuation;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = continuation;
	    }
	    else {
		temp = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = continuation;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = continuation;
	    }
	    M_CDR(continuation) = Nil;
	    return VALUES_3(Nil,Nil,Nil);
	}
	else {
	    constant_to_serve = M_CAR(list_qm);
	    rest_qm = M_CDR(list_qm);
	    if ( !TRUEP(rest_qm)) {
		if (continuation &&  !((SI_Long)0L == 
			inline_debugging_consing())) {
		    eval_cons = continuation;
		  next_loop_1:
		    inline_note_reclaim_cons(eval_cons,Qeval);
		    if (EQ(eval_cons,list_qm))
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
		    temp = ISVREF(Available_eval_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp) = continuation;
		    temp = Available_eval_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = list_qm;
		}
		else {
		    temp = Available_eval_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = continuation;
		    temp = Available_eval_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = list_qm;
		}
		M_CDR(list_qm) = Nil;
		return VALUES_3(constant_to_serve,Nil,Qnever);
	    }
	    else {
		M_CDR(continuation) = rest_qm;
		inline_note_reclaim_cons(list_qm,Qeval);
		if (ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp = ISVREF(Available_eval_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp) = list_qm;
		    temp = Available_eval_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = list_qm;
		}
		else {
		    temp = Available_eval_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = list_qm;
		    temp = Available_eval_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = list_qm;
		}
		M_CDR(list_qm) = Nil;
		return VALUES_3(constant_to_serve,continuation,Qnever);
	    }
	}
    }
}

/* SERVE-NEXT-UNREPROCESSED-FRAME */
Object serve_next_unreprocessed_frame(continue_qm,continuation)
    Object continue_qm, continuation;
{
    Object last_1, next_qm, temp, svref_arg_2, frame_reference_cons;
    Object frame_reference_number, instance_cons, rest_of_instances, instance;
    Object gensymed_symbol, xa, ya, eval_cons;
    char temp_1;

    x_note_fn_call(149,45);
    if ( !TRUEP(continue_qm)) {
	reclaim_frame_serial_number(SECOND(continuation));
	if (continuation) {
	    last_1 = continuation;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qeval);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qeval);
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = continuation;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = continuation;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    M_CDR(last_1) = Nil;
	    return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else {
	frame_reference_cons = Nil;
	frame_reference_number = Nil;
	instance_cons = Nil;
	rest_of_instances = Nil;
	instance = Nil;
      next_loop_1:
	frame_reference_cons = M_CDR(continuation);
	frame_reference_number = M_CAR(frame_reference_cons);
	instance_cons = M_CDR(frame_reference_cons);
	rest_of_instances = CDR(instance_cons);
	instance = CAR(instance_cons);
	if (rest_of_instances) {
	    M_CDR(frame_reference_cons) = rest_of_instances;
	    inline_note_reclaim_cons(instance_cons,Qeval);
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = instance_cons;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = instance_cons;
	    }
	    else {
		temp = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = instance_cons;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = instance_cons;
	    }
	    M_CDR(instance_cons) = Nil;
	    gensymed_symbol = ISVREF(instance,(SI_Long)3L);
	    temp_1 = SIMPLE_VECTOR_P(instance) ? EQ(ISVREF(instance,
		    (SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) 
			== (SI_Long)-1L : TRUEP(Nil);
	    if (temp_1);
	    else if (FIXNUMP(frame_reference_number))
		temp_1 = FIXNUMP(gensymed_symbol) ? 
			FIXNUM_LT(frame_reference_number,gensymed_symbol) :
			 TRUEP(T);
	    else if (FIXNUMP(gensymed_symbol))
		temp_1 = TRUEP(Nil);
	    else {
		xa = M_CAR(frame_reference_number);
		ya = M_CAR(gensymed_symbol);
		temp_1 = FIXNUM_LT(xa,ya);
		if (temp_1);
		else
		    temp_1 = FIXNUM_EQ(xa,ya) ? 
			    FIXNUM_LT(M_CDR(frame_reference_number),
			    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	    }
	    if ( !temp_1 ? TRUEP(serve_item_p(instance)) : TRUEP(Nil))
		return VALUES_3(instance,continuation,Qnever);
	}
	else if (instance_cons) {
	    if (continuation &&  !((SI_Long)0L == 
			inline_debugging_consing())) {
		eval_cons = continuation;
	      next_loop_2:
		inline_note_reclaim_cons(eval_cons,Qeval);
		if (EQ(eval_cons,instance_cons))
		    goto end_1;
		else if ( !TRUEP(eval_cons))
		    goto end_1;
		else
		    eval_cons = CDR(eval_cons);
		goto next_loop_2;
	      end_loop_1:
	      end_1:;
	    }
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = continuation;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = instance_cons;
	    }
	    else {
		temp = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = continuation;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = instance_cons;
	    }
	    M_CDR(instance_cons) = Nil;
	    gensymed_symbol = ISVREF(instance,(SI_Long)3L);
	    temp_1 = SIMPLE_VECTOR_P(instance) ? EQ(ISVREF(instance,
		    (SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) 
			== (SI_Long)-1L : TRUEP(Nil);
	    if (temp_1);
	    else if (FIXNUMP(frame_reference_number))
		temp_1 = FIXNUMP(gensymed_symbol) ? 
			FIXNUM_LT(frame_reference_number,gensymed_symbol) :
			 TRUEP(T);
	    else if (FIXNUMP(gensymed_symbol))
		temp_1 = TRUEP(Nil);
	    else {
		xa = M_CAR(frame_reference_number);
		ya = M_CAR(gensymed_symbol);
		temp_1 = FIXNUM_LT(xa,ya);
		if (temp_1);
		else
		    temp_1 = FIXNUM_EQ(xa,ya) ? 
			    FIXNUM_LT(M_CDR(frame_reference_number),
			    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	    }
	    if ( !temp_1 ? TRUEP(serve_item_p(instance)) : TRUEP(Nil)) {
		reclaim_frame_serial_number(frame_reference_number);
		return VALUES_3(instance,Nil,Qnever);
	    }
	    else {
		reclaim_frame_serial_number(frame_reference_number);
		return VALUES_3(Nil,Nil,Nil);
	    }
	}
	else {
	    reclaim_frame_serial_number(frame_reference_number);
	    if (continuation) {
		last_1 = continuation;
		next_qm = Nil;
	      next_loop_3:
		next_qm = M_CDR(last_1);
		if ( !TRUEP(next_qm))
		    goto end_loop_2;
		inline_note_reclaim_cons(last_1,Qeval);
		last_1 = next_qm;
		goto next_loop_3;
	      end_loop_2:
		inline_note_reclaim_cons(last_1,Qeval);
		if (ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp = ISVREF(Available_eval_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp) = continuation;
		    temp = Available_eval_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = last_1;
		}
		else {
		    temp = Available_eval_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = continuation;
		    temp = Available_eval_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = last_1;
		}
		M_CDR(last_1) = Nil;
	    }
	    return VALUES_3(Nil,Nil,Nil);
	}
	goto next_loop_1;
      end_loop_3:
	return VALUES_1(Qnil);
    }
}

static Object Qserve_next_unreprocessed_frame;  /* serve-next-unreprocessed-frame */

/* SERVE-ALL-UNREPROCESSED-FRAMES */
Object serve_all_unreprocessed_frames(frame_list)
    Object frame_list;
{
    Object instance_to_serve, temp, svref_arg_2, new_cons, svref_new_value;
    Object gensymed_symbol, continuation;

    x_note_fn_call(149,46);
    instance_to_serve = Nil;
    if ( !TRUEP(frame_list))
	return VALUES_3(Nil,Nil,Nil);
    else if ( !TRUEP(M_CDR(frame_list))) {
	instance_to_serve = M_CAR(frame_list);
	inline_note_reclaim_cons(frame_list,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = frame_list;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = frame_list;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = frame_list;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = frame_list;
	}
	M_CDR(frame_list) = Nil;
	if (serve_item_p(instance_to_serve))
	    return VALUES_3(instance_to_serve,Nil,Qnever);
	else
	    return VALUES_3(Nil,Nil,Nil);
    }
    else {
	instance_to_serve = M_CAR(frame_list);
	temp = copy_frame_serial_number(Current_frame_serial_number);
	M_CAR(frame_list) = temp;
	new_cons = ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_eval_cons_pool();
	temp = SYMBOL_FUNCTION(Qserve_next_unreprocessed_frame);
	M_CAR(gensymed_symbol) = temp;
	M_CDR(gensymed_symbol) = frame_list;
	inline_note_allocate_cons(gensymed_symbol,Qeval);
	continuation = gensymed_symbol;
	if (serve_item_p(instance_to_serve))
	    return VALUES_3(instance_to_serve,continuation,Qnever);
	else
	    return serve_next_unreprocessed_frame(T,continuation);
    }
}

/* SERVE-NEXT-ITEM-OR-VALUE */
Object serve_next_item_or_value(continue_qm,continuation)
    Object continue_qm, continuation;
{
    Object item_or_value, ab_loop_list_, thing, serial_number_cons;
    Object frame_serial_number, value_cons, rest_of_values, temp_1;
    Object svref_arg_2, x2, gensymed_symbol, xa, ya, eval_cons, last_1;
    Object next_qm;
    char temp;

    x_note_fn_call(149,47);
    if ( !TRUEP(continue_qm)) {
	item_or_value = Nil;
	ab_loop_list_ = M_CDR(M_CDR(continuation));
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	item_or_value = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > (SI_Long)2L) {
	    temp = EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector);
	    if (temp);
	    else {
		thing = ISVREF(item_or_value,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(thing) ? EQ(ISVREF(thing,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			: TRUEP(Qnil);
	    }
	}
	else
	    temp = TRUEP(Nil);
	if ( !temp)
	    reclaim_evaluation_value(item_or_value);
	goto next_loop;
      end_loop:
	reclaim_frame_serial_number(CADR(continuation));
	reclaim_eval_list_1(continuation);
	return VALUES_1(Qnil);
    }
    else {
	serial_number_cons = M_CDR(continuation);
	frame_serial_number = M_CAR(serial_number_cons);
	value_cons = M_CDR(serial_number_cons);
	rest_of_values = CDR(value_cons);
	item_or_value = CAR(value_cons);
	if (rest_of_values) {
	    M_CDR(serial_number_cons) = rest_of_values;
	    inline_note_reclaim_cons(value_cons,Qeval);
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = value_cons;
		temp_1 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = value_cons;
	    }
	    else {
		temp_1 = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = value_cons;
		temp_1 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = value_cons;
	    }
	    M_CDR(value_cons) = Nil;
	    if ( !(SIMPLE_VECTOR_P(item_or_value) && 
		    EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector))) {
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
		if (temp);
		else {
		    gensymed_symbol = ISVREF(item_or_value,(SI_Long)3L);
		    temp = SIMPLE_VECTOR_P(item_or_value) ? 
			    EQ(ISVREF(item_or_value,(SI_Long)1L),
			    Qavailable_frame_vector) : TRUEP(Qnil);
		    if (temp);
		    else
			temp = FIXNUMP(gensymed_symbol) ? 
				IFIX(gensymed_symbol) == (SI_Long)-1L : 
				TRUEP(Nil);
		    if (temp);
		    else if (FIXNUMP(frame_serial_number))
			temp = FIXNUMP(gensymed_symbol) ? 
				FIXNUM_LT(frame_serial_number,
				gensymed_symbol) : TRUEP(T);
		    else if (FIXNUMP(gensymed_symbol))
			temp = TRUEP(Nil);
		    else {
			xa = M_CAR(frame_serial_number);
			ya = M_CAR(gensymed_symbol);
			temp = FIXNUM_LT(xa,ya);
			if (temp);
			else
			    temp = FIXNUM_EQ(xa,ya) ? 
				    FIXNUM_LT(M_CDR(frame_serial_number),
				    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
		    }
		    temp =  !temp ? TRUEP(serve_item_p(item_or_value)) : 
			    TRUEP(Nil);
		}
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		return VALUES_3(item_or_value,continuation,Qnever);
	    else
		return serve_next_item_or_value(continue_qm,continuation);
	}
	else if (value_cons) {
	    if (continuation &&  !((SI_Long)0L == 
			inline_debugging_consing())) {
		eval_cons = continuation;
	      next_loop_1:
		inline_note_reclaim_cons(eval_cons,Qeval);
		if (EQ(eval_cons,value_cons))
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
		temp_1 = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = continuation;
		temp_1 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = value_cons;
	    }
	    else {
		temp_1 = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = continuation;
		temp_1 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = value_cons;
	    }
	    M_CDR(value_cons) = Nil;
	    if ( !(SIMPLE_VECTOR_P(item_or_value) && 
		    EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector))) {
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
		if (temp);
		else {
		    gensymed_symbol = ISVREF(item_or_value,(SI_Long)3L);
		    temp = SIMPLE_VECTOR_P(item_or_value) ? 
			    EQ(ISVREF(item_or_value,(SI_Long)1L),
			    Qavailable_frame_vector) : TRUEP(Qnil);
		    if (temp);
		    else
			temp = FIXNUMP(gensymed_symbol) ? 
				IFIX(gensymed_symbol) == (SI_Long)-1L : 
				TRUEP(Nil);
		    if (temp);
		    else if (FIXNUMP(frame_serial_number))
			temp = FIXNUMP(gensymed_symbol) ? 
				FIXNUM_LT(frame_serial_number,
				gensymed_symbol) : TRUEP(T);
		    else if (FIXNUMP(gensymed_symbol))
			temp = TRUEP(Nil);
		    else {
			xa = M_CAR(frame_serial_number);
			ya = M_CAR(gensymed_symbol);
			temp = FIXNUM_LT(xa,ya);
			if (temp);
			else
			    temp = FIXNUM_EQ(xa,ya) ? 
				    FIXNUM_LT(M_CDR(frame_serial_number),
				    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
		    }
		    temp =  !temp ? TRUEP(serve_item_p(item_or_value)) : 
			    TRUEP(Nil);
		}
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		reclaim_frame_serial_number(frame_serial_number);
		return VALUES_3(item_or_value,Nil,Qnever);
	    }
	    else {
		reclaim_frame_serial_number(frame_serial_number);
		return VALUES_3(Nil,Nil,Nil);
	    }
	}
	else {
	    if (continuation) {
		last_1 = continuation;
		next_qm = Nil;
	      next_loop_2:
		next_qm = M_CDR(last_1);
		if ( !TRUEP(next_qm))
		    goto end_loop_2;
		inline_note_reclaim_cons(last_1,Qeval);
		last_1 = next_qm;
		goto next_loop_2;
	      end_loop_2:
		inline_note_reclaim_cons(last_1,Qeval);
		if (ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_eval_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = continuation;
		    temp_1 = Available_eval_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = last_1;
		}
		else {
		    temp_1 = Available_eval_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = continuation;
		    temp_1 = Available_eval_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = last_1;
		}
		M_CDR(last_1) = Nil;
	    }
	    reclaim_frame_serial_number(frame_serial_number);
	    return VALUES_3(Nil,Nil,Nil);
	}
    }
}

static Object Qserve_next_item_or_value;  /* serve-next-item-or-value */

/* SERVE-ALL-ITEMS-AND-VALUES */
Object serve_all_items_and_values(item_or_value_list)
    Object item_or_value_list;
{
    Object value_to_serve, x2, temp_1, new_cons, svref_arg_2, svref_new_value;
    Object gensymed_symbol, continuation;
    char temp;

    x_note_fn_call(149,48);
    value_to_serve = Nil;
    if ( !TRUEP(item_or_value_list))
	return VALUES_3(Nil,Nil,Nil);
    else if ( !TRUEP(M_CDR(item_or_value_list))) {
	value_to_serve = M_CAR(item_or_value_list);
	if (SIMPLE_VECTOR_P(value_to_serve) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value_to_serve)) > 
		(SI_Long)2L &&  !EQ(ISVREF(value_to_serve,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(value_to_serve,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	temp =  !temp;
	if (temp);
	else
	    temp = TRUEP(serve_item_p(value_to_serve));
	if (temp)
	    return VALUES_3(value_to_serve,Nil,Qnever);
	else
	    return VALUES_3(Nil,Nil,Nil);
    }
    else {
	value_to_serve = M_CAR(item_or_value_list);
	temp_1 = copy_frame_serial_number(Current_frame_serial_number);
	M_CAR(item_or_value_list) = temp_1;
	new_cons = ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_eval_cons_pool();
	temp_1 = SYMBOL_FUNCTION(Qserve_next_item_or_value);
	M_CAR(gensymed_symbol) = temp_1;
	M_CDR(gensymed_symbol) = item_or_value_list;
	inline_note_allocate_cons(gensymed_symbol,Qeval);
	continuation = gensymed_symbol;
	if (SIMPLE_VECTOR_P(value_to_serve) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value_to_serve)) > 
		(SI_Long)2L &&  !EQ(ISVREF(value_to_serve,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(value_to_serve,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	temp =  !temp;
	if (temp);
	else
	    temp = TRUEP(serve_item_p(value_to_serve));
	if (temp)
	    return VALUES_3(value_to_serve,continuation,Qnever);
	else
	    return serve_next_item_or_value(T,continuation);
    }
}

/* MAKE-CACHE-LIST */
Object make_cache_list(eval_cons_list_of_frames)
    Object eval_cons_list_of_frames;
{
    Object temp;

    x_note_fn_call(149,49);
    temp = copy_frame_serial_number(Current_frame_serial_number);
    return eval_cons_1(temp,eval_cons_1(FIX((SI_Long)1L),
	    eval_cons_list_of_frames));
}

static Object Qserve_next_unreprocessed_cached_frame;  /* serve-next-unreprocessed-cached-frame */

/* SERVE-ALL-UNREPROCESSED-CACHED-FRAMES */
Object serve_all_unreprocessed_cached_frames(cache_list)
    Object cache_list;
{
    Object frame_serial_number, current_position, current_frame;
    Object gensymed_symbol, xa, ya, temp_1, temp_2, new_cons, svref_arg_2;
    Object svref_new_value, gensymed_symbol_1, temp_3;
    char temp;

    x_note_fn_call(149,50);
    frame_serial_number = CAR(cache_list);
    current_position = CDDR(cache_list);
    current_frame = Nil;
  next_loop:
    if ( !TRUEP(current_position))
	goto end_loop;
    current_frame = M_CAR(current_position);
    if (serve_item_p(current_frame)) {
	gensymed_symbol = ISVREF(current_frame,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(current_frame) ? EQ(ISVREF(current_frame,
		(SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else if (FIXNUMP(frame_serial_number))
	    temp = FIXNUMP(gensymed_symbol) ? 
		    FIXNUM_LT(frame_serial_number,gensymed_symbol) : TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(frame_serial_number);
	    ya = M_CAR(gensymed_symbol);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? 
			FIXNUM_LT(M_CDR(frame_serial_number),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	temp_1 = current_frame;
	current_position = M_CDR(current_position);
	if (current_position) {
	    temp_2 = FIXNUM_ADD1(SECOND(cache_list));
	    M_SECOND(cache_list) = temp_2;
	    new_cons = ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp_2 = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp_2,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_eval_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp_2 = Available_eval_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = Nil;
		}
		gensymed_symbol = new_cons;
	    }
	    else
		gensymed_symbol = Nil;
	    if ( !TRUEP(gensymed_symbol))
		gensymed_symbol = replenish_eval_cons_pool();
	    temp_2 = SYMBOL_FUNCTION(Qserve_next_unreprocessed_cached_frame);
	    M_CAR(gensymed_symbol) = temp_2;
	    new_cons = ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp_2 = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp_2,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_eval_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp_2 = Available_eval_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = Nil;
		}
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_eval_cons_pool();
	    M_CAR(gensymed_symbol_1) = current_position;
	    M_CDR(gensymed_symbol_1) = cache_list;
	    inline_note_allocate_cons(gensymed_symbol_1,Qeval);
	    M_CDR(gensymed_symbol) = gensymed_symbol_1;
	    inline_note_allocate_cons(gensymed_symbol,Qeval);
	    temp_3 = gensymed_symbol;
	}
	else
	    temp_3 = Nil;
	return VALUES_3(temp_1,temp_3,Qnever);
    }
    current_position = M_CDR(current_position);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* SERVE-NEXT-UNREPROCESSED-CACHED-FRAME */
Object serve_next_unreprocessed_cached_frame(continue_qm,continuation)
    Object continue_qm, continuation;
{
    Object current_position_cons, cache_list, current_spot, current_frame;
    Object gensymed_symbol, x, y, xa, ya, next_spot, temp_1, last_1, next_qm;
    Object svref_arg_2, eval_cons;
    char temp;

    x_note_fn_call(149,51);
    current_position_cons = M_CDR(continuation);
    cache_list = M_CDR(current_position_cons);
    if (continue_qm) {
	current_spot = M_CAR(current_position_cons);
	current_frame = Nil;
      next_loop:
	if ( !TRUEP(current_spot))
	    goto end_loop;
	current_frame = M_CAR(current_spot);
	if (serve_item_p(current_frame)) {
	    gensymed_symbol = ISVREF(current_frame,(SI_Long)3L);
	    temp = SIMPLE_VECTOR_P(current_frame) ? 
		    EQ(ISVREF(current_frame,(SI_Long)1L),
		    Qavailable_frame_vector) : TRUEP(Qnil);
	    if (temp);
	    else
		temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
			(SI_Long)-1L : TRUEP(Nil);
	    if (temp);
	    else {
		x = gensymed_symbol;
		y = CAR(cache_list);
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
			temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),
				M_CDR(x)) : TRUEP(Qnil);
		}
	    }
	    temp =  !temp;
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    next_spot = CDR(current_spot);
	    if (next_spot) {
		M_CAR(current_position_cons) = next_spot;
		return VALUES_3(current_frame,continuation,Qnever);
	    }
	    else {
		temp_1 = FIXNUM_SUB1(SECOND(cache_list));
		if (IFIX(M_SECOND(cache_list) = temp_1) == (SI_Long)0L) {
		    reclaim_frame_serial_number(CAR(cache_list));
		    if (cache_list) {
			last_1 = cache_list;
			next_qm = Nil;
		      next_loop_1:
			next_qm = M_CDR(last_1);
			if ( !TRUEP(next_qm))
			    goto end_loop_1;
			inline_note_reclaim_cons(last_1,Qeval);
			last_1 = next_qm;
			goto next_loop_1;
		      end_loop_1:
			inline_note_reclaim_cons(last_1,Qeval);
			if (ISVREF(Available_eval_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_1 = 
				    ISVREF(Available_eval_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_1) = cache_list;
			    temp_1 = Available_eval_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = last_1;
			}
			else {
			    temp_1 = Available_eval_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = cache_list;
			    temp_1 = Available_eval_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = last_1;
			}
			M_CDR(last_1) = Nil;
		    }
		}
		if (continuation &&  !((SI_Long)0L == 
			inline_debugging_consing())) {
		    eval_cons = continuation;
		  next_loop_2:
		    inline_note_reclaim_cons(eval_cons,Qeval);
		    if (EQ(eval_cons,current_position_cons))
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
		    temp_1 = ISVREF(Available_eval_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = continuation;
		    temp_1 = Available_eval_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = current_position_cons;
		}
		else {
		    temp_1 = Available_eval_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = continuation;
		    temp_1 = Available_eval_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = current_position_cons;
		}
		M_CDR(current_position_cons) = Nil;
		return VALUES_3(current_frame,Nil,Qnever);
	    }
	}
	current_spot = M_CDR(current_spot);
	goto next_loop;
      end_loop:
	temp_1 = FIXNUM_SUB1(SECOND(cache_list));
	if (IFIX(M_SECOND(cache_list) = temp_1) == (SI_Long)0L) {
	    reclaim_frame_serial_number(CAR(cache_list));
	    if (cache_list) {
		last_1 = cache_list;
		next_qm = Nil;
	      next_loop_3:
		next_qm = M_CDR(last_1);
		if ( !TRUEP(next_qm))
		    goto end_loop_3;
		inline_note_reclaim_cons(last_1,Qeval);
		last_1 = next_qm;
		goto next_loop_3;
	      end_loop_3:
		inline_note_reclaim_cons(last_1,Qeval);
		if (ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_eval_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = cache_list;
		    temp_1 = Available_eval_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = last_1;
		}
		else {
		    temp_1 = Available_eval_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = cache_list;
		    temp_1 = Available_eval_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = last_1;
		}
		M_CDR(last_1) = Nil;
	    }
	}
	if (continuation &&  !((SI_Long)0L == inline_debugging_consing())) {
	    eval_cons = continuation;
	  next_loop_4:
	    inline_note_reclaim_cons(eval_cons,Qeval);
	    if (EQ(eval_cons,current_position_cons))
		goto end_2;
	    else if ( !TRUEP(eval_cons))
		goto end_2;
	    else
		eval_cons = CDR(eval_cons);
	    goto next_loop_4;
	  end_loop_4:
	  end_2:;
	}
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_1 = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_1) = continuation;
	    temp_1 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = current_position_cons;
	}
	else {
	    temp_1 = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = continuation;
	    temp_1 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = current_position_cons;
	}
	M_CDR(current_position_cons) = Nil;
	return VALUES_3(Nil,Nil,Nil);
	return VALUES_1(Qnil);
    }
    else {
	temp_1 = FIXNUM_SUB1(SECOND(cache_list));
	if (IFIX(M_SECOND(cache_list) = temp_1) == (SI_Long)0L) {
	    reclaim_frame_serial_number(CAR(cache_list));
	    if (cache_list) {
		last_1 = cache_list;
		next_qm = Nil;
	      next_loop_5:
		next_qm = M_CDR(last_1);
		if ( !TRUEP(next_qm))
		    goto end_loop_5;
		inline_note_reclaim_cons(last_1,Qeval);
		last_1 = next_qm;
		goto next_loop_5;
	      end_loop_5:
		inline_note_reclaim_cons(last_1,Qeval);
		if (ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_eval_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = cache_list;
		    temp_1 = Available_eval_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = last_1;
		}
		else {
		    temp_1 = Available_eval_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = cache_list;
		    temp_1 = Available_eval_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = last_1;
		}
		M_CDR(last_1) = Nil;
	    }
	}
	if (continuation &&  !((SI_Long)0L == inline_debugging_consing())) {
	    eval_cons = continuation;
	  next_loop_6:
	    inline_note_reclaim_cons(eval_cons,Qeval);
	    if (EQ(eval_cons,current_position_cons))
		goto end_3;
	    else if ( !TRUEP(eval_cons))
		goto end_3;
	    else
		eval_cons = CDR(eval_cons);
	    goto next_loop_6;
	  end_loop_6:
	  end_3:;
	}
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_1 = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_1) = continuation;
	    temp_1 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = current_position_cons;
	}
	else {
	    temp_1 = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = continuation;
	    temp_1 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = current_position_cons;
	}
	M_CDR(current_position_cons) = Nil;
	return VALUES_1(Nil);
    }
}

/* EQUAL-ASSOC */
Object equal_assoc(key,alist)
    Object key, alist;
{
    Object entry, ab_loop_list_, temp, key_car, key_cdr, key_cadr, entry_key;
    Object entry_key_cdr;
    char temp_1;

    x_note_fn_call(149,52);
    if (ATOM(key)) {
	entry = Nil;
	ab_loop_list_ = alist;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	entry = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(CAR(entry),key)) {
	    temp = entry;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    else {
	key_car = CAR(key);
	key_cdr = CDR(key);
	if (ATOM(key_car) && CONSP(key_cdr) &&  !TRUEP(CDR(key_cdr))) {
	    temp = CAR(key_cdr);
	    temp_1 = ATOM(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    key_cadr = CAR(key_cdr);
	    entry = Nil;
	    ab_loop_list_ = alist;
	    entry_key = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    entry = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    entry_key = CAR(entry);
	    if (CONSP(entry_key) && EQ(CAR(entry_key),key_car)) {
		entry_key_cdr = CDR(entry_key);
		temp_1 = CONSP(entry_key_cdr) &&  
			!TRUEP(CDR(entry_key_cdr)) ? EQ(CAR(entry_key_cdr),
			key_cadr) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		temp = entry;
		goto end_2;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp = Qnil;
	  end_2:;
	}
	else {
	    entry = Nil;
	    ab_loop_list_ = alist;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    entry = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    temp = CAR(entry);
	    if (EQUAL(temp,key)) {
		temp = entry;
		goto end_3;
	    }
	    goto next_loop_2;
	  end_loop_2:
	    temp = Qnil;
	  end_3:;
	}
    }
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Role_caching_enabled_qm, Qrole_caching_enabled_qm);

/* USE-ROLE-CACHING */
Object use_role_caching(enabled_p)
    Object enabled_p;
{
    x_note_fn_call(149,53);
    if ( !TRUEP(enabled_p) && Role_caching_enabled_qm)
	decache_roles_for_all_items();
    Role_caching_enabled_qm = enabled_p;
    return VALUES_1(Role_caching_enabled_qm);
}

static Object Qrole_cache;         /* role-cache */

/* ADD-TO-CACHE-AND-SERVE */
Object add_to_cache_and_serve(entity,role_name,role_argument,
	    eval_cons_list_of_frames)
    Object entity, role_name, role_argument, eval_cons_list_of_frames;
{
    Object cache_list, specific_cache_entry, domain_cache_qm, role_cache_qm;
    Object cdr_new_value;

    x_note_fn_call(149,54);
    cache_list = make_cache_list(eval_cons_list_of_frames);
    specific_cache_entry = eval_cons_1(role_argument,cache_list);
    domain_cache_qm = get_lookup_slot_value_given_default(entity,
	    Qrole_cache,Nil);
    role_cache_qm = assq_function(role_name,domain_cache_qm);
    if (role_cache_qm) {
	cdr_new_value = eval_cons_1(specific_cache_entry,CDR(role_cache_qm));
	M_CDR(role_cache_qm) = cdr_new_value;
    }
    else
	set_non_savable_lookup_slot_value(entity,Qrole_cache,
		eval_cons_1(eval_list_2(role_name,specific_cache_entry),
		domain_cache_qm));
    return serve_all_unreprocessed_cached_frames(cache_list);
}

static Object Qthis_workspace;     /* this-workspace */

static Object Qkb_workspace;       /* kb-workspace */

static Object Qthis_rule;          /* this-rule */

/* DESIGNATION-COULD-DENOTE-ITEM-P */
Object designation_could_denote_item_p(designation,item)
    Object designation, item;
{
    Object role, attribute_qm, name_or_names, gensymed_symbol;
    Object sub_class_bit_vector, temp, class_description, thing, the_cons, x2;
    Object class_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Object result;

    x_note_fn_call(149,55);
    role = Nil;
    attribute_qm = get_lookup_slot_value_given_default(item,
	    Qparent_attribute_name,Nil);
    if (SYMBOLP(designation)) {
	name_or_names = get_lookup_slot_value_given_default(item,
		Qname_or_names_for_frame,Nil);
	if (CONSP(name_or_names))
	    return memq_function(designation,name_or_names);
	else
	    return VALUES_1(EQ(designation,name_or_names) ? T : Nil);
    }
    else {
	role = role_of_designation(designation);
	if (SYMBOLP(role)) {
	    if (EQ(role,attribute_qm) || CONSP(attribute_qm) && EQ(role,
		    M_CAR(attribute_qm)))
		return VALUES_1(T);
	    else {
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(role,
			Class_description_gkbprop);
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
			    (SI_Long)19L);
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
			return VALUES_1((SI_Long)0L < gensymed_symbol_1 ? 
				T : Nil);
		    }
		    else
			return VALUES_1(Nil);
		}
		else
		    return VALUES_1(Nil);
	    }
	}
	else if (SYMBOLP(role) || CONSP(role) && EQ(M_CAR(role),
		Qclass_qualified_name)) {
	    if (CONSP(role) && CONSP(attribute_qm)) {
		temp = CDR(attribute_qm);
		class_description = 
			lookup_global_or_kb_specific_property_value(CONSP(role) 
			? M_CAR(M_CDR(role)) : Nil,Class_description_gkbprop);
		return member_eql(temp,ISVREF(class_description,(SI_Long)2L));
	    }
	    else
		return VALUES_1(Nil);
	}
	else {
	    thing = role;
	    if (CONSP(thing)) {
		the_cons = thing;
		thing = M_CAR(the_cons);
		if (EQ(thing,Qrole_server)) {
		    thing = M_CDR(the_cons);
		    if (CONSP(thing)) {
			the_cons = thing;
			thing = M_CAR(the_cons);
			if (EQ(thing,Qthis_workspace)) {
			    thing = M_CDR(the_cons);
			    if (CONSP(thing)) {
				the_cons = thing;
				thing = M_CAR(the_cons);
				if (EQ(thing,Qkb_workspace)) {
				    thing = M_CDR(the_cons);
				    temp_1 =  !TRUEP(thing);
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
		    else
			temp_1 = TRUEP(Nil);
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		if (SIMPLE_VECTOR_P(Current_computation_frame) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_computation_frame)) 
			> (SI_Long)2L &&  
			!EQ(ISVREF(Current_computation_frame,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(Current_computation_frame,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1) {
		    result = get_block_on_workspace_for_frame(Current_computation_frame);
		    gensymed_symbol = NTH_VALUE((SI_Long)1L, result);
		    return VALUES_1(EQ(item,gensymed_symbol) ? T : Nil);
		}
		else
		    return VALUES_1(Nil);
	    }
	    else {
		thing = role;
		if (CONSP(thing)) {
		    the_cons = thing;
		    thing = M_CAR(the_cons);
		    if (EQ(thing,Qrole_server)) {
			thing = M_CDR(the_cons);
			if (CONSP(thing)) {
			    the_cons = thing;
			    thing = M_CAR(the_cons);
			    if (EQ(thing,Qthis_rule)) {
				thing = M_CDR(the_cons);
				if (CONSP(thing)) {
				    the_cons = thing;
				    thing = M_CAR(the_cons);
				    if (EQ(thing,Qrule)) {
					thing = M_CDR(the_cons);
					temp_1 =  !TRUEP(thing);
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
			else
			    temp_1 = TRUEP(Nil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1)
		    return VALUES_1(EQ(item,Current_computation_frame) ? T 
			    : Nil);
		else {
		    class_qm = atomic_class_element_of_role(role);
		    if (class_qm) {
			gensymed_symbol = 
				lookup_global_or_kb_specific_property_value(class_qm,
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
					superior_class_bit_number & 
					(SI_Long)7L;
				gensymed_symbol_2 = gensymed_symbol_2 << 
					gensymed_symbol_3;
				gensymed_symbol_1 = gensymed_symbol_1 & 
					gensymed_symbol_2;
				return VALUES_1((SI_Long)0L < 
					gensymed_symbol_1 ? T : Nil);
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
	    }
	}
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Get_focal_entity_for_simulation_formula_qm, Qget_focal_entity_for_simulation_formula_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Focal_entity_for_simulation_formula, Qfocal_entity_for_simulation_formula);

/* DESIGNATION-DENOTES-ITEM-P */
Object designation_denotes_item_p(designation,entity)
    Object designation, entity;
{
    Object name_or_names, role, gensymed_symbol, sub_class_bit_vector;
    Object frame_of_class_p, frame, symbol, thing, the_cons, x2, quantifier;
    Object role_cons, domain, value, continuation, expiration;
    Object gensymed_symbol_4, gensymed_symbol_5;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Object result;

    x_note_fn_call(149,56);
    if (designation) {
      next_loop:
	if (SYMBOLP(designation)) {
	    name_or_names = get_lookup_slot_value_given_default(entity,
		    Qname_or_names_for_frame,Nil);
	    if (CONSP(name_or_names))
		return memq_function(designation,name_or_names);
	    else
		return VALUES_1(EQ(designation,name_or_names) ? T : Nil);
	}
	else if (IFIX(length(designation)) == (SI_Long)2L) {
	    role = M_CAR(M_CDR(designation));
	    if (SYMBOLP(role)) {
		if (Get_focal_entity_for_simulation_formula_qm) {
		    gensymed_symbol = 
			    lookup_global_or_kb_specific_property_value(role,
			    Class_description_gkbprop);
		    if (gensymed_symbol) {
			sub_class_bit_vector = ISVREF(ISVREF(entity,
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
			    frame_of_class_p = (SI_Long)0L < 
				    gensymed_symbol_1 ? T : Nil;
			}
			else
			    frame_of_class_p = Nil;
		    }
		    else
			frame_of_class_p = Nil;
		    if (frame_of_class_p)
			Focal_entity_for_simulation_formula = entity;
		    return VALUES_1(frame_of_class_p);
		}
		else {
		    frame = entity;
		    symbol = SECOND(designation);
		    gensymed_symbol = 
			    lookup_global_or_kb_specific_property_value(symbol,
			    Class_description_gkbprop);
		    if (gensymed_symbol) {
			sub_class_bit_vector = ISVREF(ISVREF(frame,
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
			    return VALUES_1((SI_Long)0L < 
				    gensymed_symbol_1 ? T : Nil);
			}
			else
			    return VALUES_1(Nil);
		    }
		    else
			return VALUES_1(Nil);
		}
	    }
	    else {
		thing = role;
		if (CONSP(thing)) {
		    the_cons = thing;
		    thing = M_CAR(the_cons);
		    if (EQ(thing,Qrole_server)) {
			thing = M_CDR(the_cons);
			if (CONSP(thing)) {
			    the_cons = thing;
			    thing = M_CAR(the_cons);
			    if (EQ(thing,Qthis_workspace)) {
				thing = M_CDR(the_cons);
				if (CONSP(thing)) {
				    the_cons = thing;
				    thing = M_CAR(the_cons);
				    if (EQ(thing,Qkb_workspace)) {
					thing = M_CDR(the_cons);
					temp =  !TRUEP(thing);
				    }
				    else
					temp = TRUEP(Nil);
				}
				else
				    temp = TRUEP(Nil);
			    }
			    else
				temp = TRUEP(Nil);
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
		    if (SIMPLE_VECTOR_P(Current_computation_frame) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_computation_frame)) 
			    > (SI_Long)2L &&  
			    !EQ(ISVREF(Current_computation_frame,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(Current_computation_frame,(SI_Long)1L);
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
		if (temp) {
		    result = get_block_on_workspace_for_frame(Current_computation_frame);
		    gensymed_symbol = NTH_VALUE((SI_Long)1L, result);
		    return VALUES_1(EQ(gensymed_symbol,entity) ? T : Nil);
		}
		else
		    return VALUES_1(Nil);
	    }
	}
	else if (IFIX(length(designation)) == (SI_Long)3L) {
	    quantifier = M_CAR(designation);
	    role_cons = M_CDR(designation);
	    role = M_CAR(role_cons);
	    domain = M_CAR(M_CDR(role_cons));
	    result = serve_first_value_of_role_inverse(entity,quantifier,
		    role,domain);
	    MVS_3(result,value,continuation,expiration);
	    if ( !TRUEP(expiration)) {
		if (continuation) {
		    gensymed_symbol = M_CAR(continuation);
		    gensymed_symbol_4 = Nil;
		    gensymed_symbol_5 = continuation;
		    inline_funcall_2(gensymed_symbol,gensymed_symbol_4,
			    gensymed_symbol_5);
		}
		return VALUES_1(Nil);
	    }
	    else if ( !TRUEP(continuation)) {
		entity = value;
		designation = domain;
	    }
	    else {
	      next_loop_1:
		if (designation_denotes_item_p(domain,value)) {
		    if (continuation) {
			gensymed_symbol = M_CAR(continuation);
			gensymed_symbol_4 = Nil;
			gensymed_symbol_5 = continuation;
			inline_funcall_2(gensymed_symbol,gensymed_symbol_4,
				gensymed_symbol_5);
		    }
		    return VALUES_1(T);
		}
		else {
		    if (continuation) {
			gensymed_symbol = M_CAR(continuation);
			gensymed_symbol_4 = T;
			gensymed_symbol_5 = continuation;
			result = inline_funcall_2(gensymed_symbol,
				gensymed_symbol_4,gensymed_symbol_5);
		    }
		    else
			result = VALUES_3(Nil,Nil,Nil);
		    MVS_3(result,value,continuation,expiration);
		}
		if ( !TRUEP(expiration))
		    goto end_loop;
		goto next_loop_1;
	      end_loop:
		if (continuation) {
		    gensymed_symbol = M_CAR(continuation);
		    gensymed_symbol_4 = Nil;
		    gensymed_symbol_5 = continuation;
		    inline_funcall_2(gensymed_symbol,gensymed_symbol_4,
			    gensymed_symbol_5);
		}
		return VALUES_1(Nil);
	    }
	}
	goto next_loop;
      end_loop_1:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* SERVE-FIRST-VALUE-OF-ROLE-INVERSE */
Object serve_first_value_of_role_inverse(object,quantifier,role,
	    domain_designation)
    Object object, quantifier, role, domain_designation;
{
    Object role_1, role_car, gensymed_symbol, inverse_server_function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, parent_qm, attribute_qm, class_qm, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value;
    char temp;
    Object result;

    x_note_fn_call(149,57);
    if (CONSP(role)) {
	role_1 = role;
	role_car = M_CAR(role_1);
	gensymed_symbol = EQ(role_car,Qrole_server) ? M_CAR(M_CDR(role_1)) 
		: role_car;
	inverse_server_function = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qinverse_role_server);
	if (inverse_server_function) {
	    gensymed_symbol = inverse_server_function;
	    gensymed_symbol_1 = object;
	    gensymed_symbol_2 = quantifier;
	    gensymed_symbol_3 = role;
	    gensymed_symbol_4 = domain_designation;
	    return inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    return VALUES_3(Nil,Nil,Nil);
    }
    else if (role && domain_designation) {
	result = get_kb_parent_information(object);
	MVS_3(result,parent_qm,attribute_qm,class_qm);
	if (EQ(attribute_qm,role) && (class_qm ? EQ(class_qm,
		CONSP(domain_designation) ? SECOND(domain_designation) : 
		domain_designation) : TRUEP(T))) {
	    if ( !((SI_Long)0L != (IFIX(ISVREF(parent_qm,(SI_Long)5L)) & 
		    (SI_Long)512L))) {
		if (Note_things_encountered_during_role_service_qm) {
		    gensymed_symbol = Things_that_affect_this_formula;
		    gensymed_symbol_1 = parent_qm;
		    if ( !TRUEP(memq_function(gensymed_symbol_1,
			    gensymed_symbol))) {
			new_cons = ISVREF(Available_eval_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    svref_arg_1 = Available_eval_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_eval_conses_vector,
				    IFIX(Current_thread_index)))) {
				svref_arg_1 = 
					Available_eval_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(svref_arg_1,svref_arg_2) = Nil;
			    }
			    gensymed_symbol_2 = new_cons;
			}
			else
			    gensymed_symbol_2 = Nil;
			if ( !TRUEP(gensymed_symbol_2))
			    gensymed_symbol_2 = replenish_eval_cons_pool();
			M_CAR(gensymed_symbol_2) = gensymed_symbol_1;
			M_CDR(gensymed_symbol_2) = gensymed_symbol;
			inline_note_allocate_cons(gensymed_symbol_2,Qeval);
			Things_that_affect_this_formula = gensymed_symbol_2;
		    }
		}
		temp = TRUEP(T);
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if ((temp ? 
		TRUEP(designation_could_denote_item_p(domain_designation,
		parent_qm)) : TRUEP(Nil)) ? TRUEP(serve_item_p(parent_qm)) 
		: TRUEP(Nil))
	    return VALUES_3(parent_qm,Nil,Qnever);
	else
	    return VALUES_3(Nil,Nil,Nil);
    }
    else
	return VALUES_3(Nil,Nil,Nil);
}

/* UNIQUE-VALUE-OF-ROLE-P */
Object unique_value_of_role_p(object_serving_role,role,object)
    Object object_serving_role, role, object;
{
    Object served_object, expiration, temp;
    Object result;

    x_note_fn_call(149,58);
    result = serve_unique_item_or_evaluation_value_of_role(role,object,Nil,
	    Nil);
    MVS_2(result,served_object,expiration);
    temp = expiration ? (EQ(object_serving_role,served_object) ? T : Nil) :
	     Qnil;
    if (expiration) {
	if ( !(FIXNUMP(served_object) || SYMBOLP(served_object) || 
		SIMPLE_VECTOR_P(served_object)))
	    reclaim_if_evaluation_value_1(served_object);
    }
    return VALUES_1(temp);
}

/* RECLAIM-ROLE-CACHE-VALUE */
Object reclaim_role_cache_value(role_cache_entries,gensymed_symbol)
    Object role_cache_entries, gensymed_symbol;
{
    Object role_cache_entry, ab_loop_list_, list_of_specific_caches;
    Object specific_cache, ab_loop_list__1, cache_list, temp, last_1, next_qm;
    Object svref_arg_2;

    x_note_fn_call(149,59);
    role_cache_entry = Nil;
    ab_loop_list_ = role_cache_entries;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    role_cache_entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    list_of_specific_caches = CDR(role_cache_entry);
    specific_cache = Nil;
    ab_loop_list__1 = list_of_specific_caches;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    specific_cache = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    cache_list = CDR(specific_cache);
    temp = FIXNUM_SUB1(SECOND(cache_list));
    if (IFIX(M_SECOND(cache_list) = temp) == (SI_Long)0L) {
	reclaim_frame_serial_number(CAR(cache_list));
	if (cache_list) {
	    last_1 = cache_list;
	    next_qm = Nil;
	  next_loop_2:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop_2;
	    inline_note_reclaim_cons(last_1,Qeval);
	    last_1 = next_qm;
	    goto next_loop_2;
	  end_loop_2:
	    inline_note_reclaim_cons(last_1,Qeval);
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = cache_list;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cache_list;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    M_CDR(last_1) = Nil;
	}
    }
    reclaim_eval_tree_1(CAR(specific_cache));
    inline_note_reclaim_cons(specific_cache,Qeval);
    if (ISVREF(Available_eval_conses_tail_vector,IFIX(Current_thread_index))) {
	temp = ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = specific_cache;
	temp = Available_eval_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = specific_cache;
    }
    else {
	temp = Available_eval_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = specific_cache;
	temp = Available_eval_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = specific_cache;
    }
    M_CDR(specific_cache) = Nil;
    goto next_loop_1;
  end_loop_1:;
    if (list_of_specific_caches) {
	last_1 = list_of_specific_caches;
	next_qm = Nil;
      next_loop_3:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop_3;
	inline_note_reclaim_cons(last_1,Qeval);
	last_1 = next_qm;
	goto next_loop_3;
      end_loop_3:
	inline_note_reclaim_cons(last_1,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = list_of_specific_caches;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = list_of_specific_caches;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    inline_note_reclaim_cons(role_cache_entry,Qeval);
    if (ISVREF(Available_eval_conses_tail_vector,IFIX(Current_thread_index))) {
	temp = ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = role_cache_entry;
	temp = Available_eval_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = role_cache_entry;
    }
    else {
	temp = Available_eval_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = role_cache_entry;
	temp = Available_eval_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = role_cache_entry;
    }
    M_CDR(role_cache_entry) = Nil;
    goto next_loop;
  end_loop:;
    if (role_cache_entries) {
	last_1 = role_cache_entries;
	next_qm = Nil;
      next_loop_4:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop_4;
	inline_note_reclaim_cons(last_1,Qeval);
	last_1 = next_qm;
	goto next_loop_4;
      end_loop_4:
	inline_note_reclaim_cons(last_1,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = role_cache_entries;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = role_cache_entries;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    return VALUES_1(Nil);
}

/* DECACHE-ROLES-FOR-ALL-ITEMS */
Object decache_roles_for_all_items()
{
    x_note_fn_call(149,60);
    if (Role_caching_enabled_qm)
	return decache_roles_for_all_items_1();
    else
	return VALUES_1(Nil);
}

static Object Qitem;               /* item */

/* DECACHE-ROLES-FOR-ALL-ITEMS-1 */
Object decache_roles_for_all_items_1()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, item, role_cache_qm;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(149,61);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    item = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      role_cache_qm = Nil;
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
	  temp =  !TRUEP(ab_loopvar__1);
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  goto end_loop_1;
      item = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      role_cache_qm = get_lookup_slot_value_given_default(item,Qrole_cache,
	      Nil);
      if (role_cache_qm) {
	  reclaim_role_cache_value(role_cache_qm,Nil);
	  set_non_savable_lookup_slot_value(item,Qrole_cache,Nil);
      }
      goto next_loop;
    end_loop_1:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(List_of_connection_roles, Qlist_of_connection_roles);

/* DECACHE-CONNECTION-ROLES */
Object decache_connection_roles(entity)
    Object entity;
{
    x_note_fn_call(149,62);
    if (Role_caching_enabled_qm)
	return decache_connection_roles_1(entity);
    else
	return VALUES_1(Nil);
}

/* DECACHE-CONNECTION-ROLES-1 */
Object decache_connection_roles_1(entity)
    Object entity;
{
    Object role_entries_to_remove, role_cache_entry, ab_loop_list_, entry;
    Object temp, list_of_specific_caches, specific_cache, ab_loop_list__1;
    Object cache_list, temp_1, last_1, next_qm, svref_arg_2;

    x_note_fn_call(149,63);
    role_entries_to_remove = Nil;
    role_cache_entry = Nil;
    ab_loop_list_ = get_lookup_slot_value_given_default(entity,Qrole_cache,
	    Nil);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    role_cache_entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (memq_function(CAR(role_cache_entry),List_of_connection_roles))
	role_entries_to_remove = eval_cons_1(role_cache_entry,
		role_entries_to_remove);
    goto next_loop;
  end_loop:
    entry = Nil;
    ab_loop_list_ = role_entries_to_remove;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = entry;
    set_non_savable_lookup_slot_value(entity,Qrole_cache,
	    delete_eval_element_1(temp,
	    get_lookup_slot_value_given_default(entity,Qrole_cache,Nil)));
    list_of_specific_caches = CDR(entry);
    specific_cache = Nil;
    ab_loop_list__1 = list_of_specific_caches;
  next_loop_2:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_2;
    specific_cache = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    cache_list = CDR(specific_cache);
    temp_1 = FIXNUM_SUB1(SECOND(cache_list));
    if (IFIX(M_SECOND(cache_list) = temp_1) == (SI_Long)0L) {
	reclaim_frame_serial_number(CAR(cache_list));
	if (cache_list) {
	    last_1 = cache_list;
	    next_qm = Nil;
	  next_loop_3:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop_3;
	    inline_note_reclaim_cons(last_1,Qeval);
	    last_1 = next_qm;
	    goto next_loop_3;
	  end_loop_3:
	    inline_note_reclaim_cons(last_1,Qeval);
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = cache_list;
		temp_1 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = last_1;
	    }
	    else {
		temp_1 = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = cache_list;
		temp_1 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = last_1;
	    }
	    M_CDR(last_1) = Nil;
	}
    }
    reclaim_eval_tree_1(CAR(specific_cache));
    inline_note_reclaim_cons(specific_cache,Qeval);
    if (ISVREF(Available_eval_conses_tail_vector,IFIX(Current_thread_index))) {
	temp_1 = ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp_1) = specific_cache;
	temp_1 = Available_eval_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp_1,svref_arg_2) = specific_cache;
    }
    else {
	temp_1 = Available_eval_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp_1,svref_arg_2) = specific_cache;
	temp_1 = Available_eval_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp_1,svref_arg_2) = specific_cache;
    }
    M_CDR(specific_cache) = Nil;
    goto next_loop_2;
  end_loop_2:;
    if (list_of_specific_caches) {
	last_1 = list_of_specific_caches;
	next_qm = Nil;
      next_loop_4:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop_4;
	inline_note_reclaim_cons(last_1,Qeval);
	last_1 = next_qm;
	goto next_loop_4;
      end_loop_4:
	inline_note_reclaim_cons(last_1,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_1 = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_1) = list_of_specific_caches;
	    temp_1 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = last_1;
	}
	else {
	    temp_1 = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = list_of_specific_caches;
	    temp_1 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    inline_note_reclaim_cons(entry,Qeval);
    if (ISVREF(Available_eval_conses_tail_vector,IFIX(Current_thread_index))) {
	temp_1 = ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp_1) = entry;
	temp_1 = Available_eval_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp_1,svref_arg_2) = entry;
    }
    else {
	temp_1 = Available_eval_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp_1,svref_arg_2) = entry;
	temp_1 = Available_eval_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp_1,svref_arg_2) = entry;
    }
    M_CDR(entry) = Nil;
    goto next_loop_1;
  end_loop_1:;
    if (role_entries_to_remove) {
	last_1 = role_entries_to_remove;
	next_qm = Nil;
      next_loop_5:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop_5;
	inline_note_reclaim_cons(last_1,Qeval);
	last_1 = next_qm;
	goto next_loop_5;
      end_loop_5:
	inline_note_reclaim_cons(last_1,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_1 = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_1) = role_entries_to_remove;
	    temp_1 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = last_1;
	}
	else {
	    temp_1 = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = role_entries_to_remove;
	    temp_1 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Connections_to_be_excluded_qm, Qconnections_to_be_excluded_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Entities_to_be_excluded_qm, Qentities_to_be_excluded_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Entities_or_triples_found_in_search, Qentities_or_triples_found_in_search);

/* DECACHE-ROLES-FOR-ENTITIES-RELATED-TO-THIS-CONNECTION */
Object decache_roles_for_entities_related_to_this_connection(connection)
    Object connection;
{
    x_note_fn_call(149,64);
    if ((System_is_running || System_has_paused) && Role_caching_enabled_qm)
	return decache_roles_for_entities_related_to_this_connection_1(connection);
    else
	return VALUES_1(Nil);
}

static Object Qinput;              /* input */

static Object Qobject;             /* object */

static Object Qoutput;             /* output */

/* DECACHE-ROLES-FOR-ENTITIES-RELATED-TO-THIS-CONNECTION-1 */
Object decache_roles_for_entities_related_to_this_connection_1(connection)
    Object connection;
{
    Object things_that_affect_this_formula;
    Object note_things_encountered_during_role_service_qm, direction_to_try;
    Object block, x2, gensymed_symbol, connections_to_be_excluded_qm;
    Object entities_to_be_excluded_qm, entities_or_triples_found_in_search;
    Object entity_or_connection, ab_loop_list_, connection_frame_qm;
    char temp;
    Declare_special(5);
    Object result;

    x_note_fn_call(149,65);
    things_that_affect_this_formula = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Things_that_affect_this_formula,Qthings_that_affect_this_formula,things_that_affect_this_formula,
	    4);
      note_things_encountered_during_role_service_qm = T;
      PUSH_SPECIAL_WITH_SYMBOL(Note_things_encountered_during_role_service_qm,Qnote_things_encountered_during_role_service_qm,note_things_encountered_during_role_service_qm,
	      3);
	direction_to_try = Qinput;
	block = Nil;
      next_loop:
	block = EQ(direction_to_try,Qinput) ? ISVREF(connection,
		(SI_Long)2L) : ISVREF(connection,(SI_Long)3L);
	if (SIMPLE_VECTOR_P(block) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(block)) > (SI_Long)2L &&  
		!EQ(ISVREF(block,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(block,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol && ISVREF(gensymed_symbol,(SI_Long)16L)) {
	    connections_to_be_excluded_qm = Nil;
	    entities_to_be_excluded_qm = Nil;
	    entities_or_triples_found_in_search = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Entities_or_triples_found_in_search,Qentities_or_triples_found_in_search,entities_or_triples_found_in_search,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Entities_to_be_excluded_qm,Qentities_to_be_excluded_qm,entities_to_be_excluded_qm,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Connections_to_be_excluded_qm,Qconnections_to_be_excluded_qm,connections_to_be_excluded_qm,
			0);
		  search_for_directly_connected_entities_for_connection(block,
			  Qobject,connection,Nil,Nil,Nil,Nil,T);
		  reclaim_eval_list_1(Entities_or_triples_found_in_search);
		  clear_connections_to_be_excluded(Connections_to_be_excluded_qm);
		  clear_entities_to_be_excluded(Entities_to_be_excluded_qm);
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	if (EQ(direction_to_try,Qoutput))
	    goto end_loop;
	direction_to_try = Qoutput;
	goto next_loop;
      end_loop:
	entity_or_connection = Nil;
	ab_loop_list_ = Things_that_affect_this_formula;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	entity_or_connection = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (SIMPLE_VECTOR_P(entity_or_connection) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(entity_or_connection)) > 
		(SI_Long)2L &&  !EQ(ISVREF(entity_or_connection,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(entity_or_connection,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    decache_connection_roles(entity_or_connection);
	else {
	    connection_frame_qm = ISVREF(entity_or_connection,(SI_Long)1L);
	    if (SIMPLE_VECTOR_P(connection_frame_qm) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_qm)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(connection_frame_qm,
		    (SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(connection_frame_qm,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		decache_connection_roles(connection_frame_qm);
	}
	goto next_loop_1;
      end_loop_1:;
	reclaim_eval_list_1(Things_that_affect_this_formula);
	result = VALUES_1(Qnil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object string_constant_2;   /* "Cannot evaluate `" */

static Object string_constant_3;   /* "' of something which cannot be found." */

/* WARNING-FOR-NULL-DOMAIN */
Object warning_for_null_domain(role)
    Object role;
{
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(7);

    x_note_fn_call(149,66);
    if ((SI_Long)1L <= IFIX(Warning_message_level) &&  
		!TRUEP(Debugging_reset)) {
	if ( !TRUEP(Defer_notifications_qm))
	    break_out_of_debug_messages();
	snapshots_of_related_blocks = Nil;
	note_blocks_in_tformat = SYMBOL_FUNCTION(Qrecord_block_for_tformat);
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
		      write_warning_message_header(FIX((SI_Long)1L));
		      twrite(string_constant_2);
		      print_role(role);
		      twrite(string_constant_3);
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
    return VALUES_3(Nil,Nil,Nil);
}

/* ROLE-PRINT-NAME */
Object role_print_name(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,67);
    GENSYM_RETURN_ONE(print_role_whose_car_is_role_server(role,
	    local_variable_qm));
    return VALUES_1(Nil);
}

static Object Qserve_next_name_of_entity;  /* serve-next-name-of-entity */

/* SERVE-FIRST-NAME */
Object serve_first_name(role,domain)
    Object role, domain;
{
    Object name_or_names, temp, temp_1;

    x_note_fn_call(149,68);
    name_or_names = get_lookup_slot_value_given_default(domain,
	    Qname_or_names_for_frame,Nil);
    if ( !TRUEP(name_or_names))
	return VALUES_3(Nil,Nil,Nil);
    else if (CONSP(name_or_names)) {
	temp = M_CAR(name_or_names);
	temp_1 = M_CDR(name_or_names) ? 
		eval_cons_1(SYMBOL_FUNCTION(Qserve_next_name_of_entity),
		copy_list_using_eval_conses_1(M_CDR(name_or_names))) : Nil;
	return VALUES_3(temp,temp_1,Qnever);
    }
    else
	return VALUES_3(name_or_names,Nil,Qnever);
}

/* SERVE-NEXT-NAME-OF-ENTITY */
Object serve_next_name_of_entity(continue_qm,continuation)
    Object continue_qm, continuation;
{
    Object instance_cons, temp, svref_arg_2, temp_1, eval_cons;

    x_note_fn_call(149,69);
    if ( !TRUEP(continue_qm))
	return reclaim_eval_list_1(continuation);
    else {
	instance_cons = M_CDR(continuation);
	if ( !TRUEP(instance_cons)) {
	    inline_note_reclaim_cons(continuation,Qeval);
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = continuation;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = continuation;
	    }
	    else {
		temp = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = continuation;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = continuation;
	    }
	    M_CDR(continuation) = Nil;
	    return VALUES_3(Nil,Nil,Nil);
	}
	else if ( !TRUEP(M_CDR(instance_cons))) {
	    temp_1 = M_CAR(instance_cons);
	    if (continuation &&  !((SI_Long)0L == 
			inline_debugging_consing())) {
		eval_cons = continuation;
	      next_loop:
		inline_note_reclaim_cons(eval_cons,Qeval);
		if (EQ(eval_cons,instance_cons))
		    goto end_1;
		else if ( !TRUEP(eval_cons))
		    goto end_1;
		else
		    eval_cons = CDR(eval_cons);
		goto next_loop;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = continuation;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = instance_cons;
	    }
	    else {
		temp = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = continuation;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = instance_cons;
	    }
	    M_CDR(instance_cons) = Nil;
	    return VALUES_3(temp_1,Nil,Qnever);
	}
	else {
	    temp_1 = CAR(instance_cons);
	    temp = M_CDR(instance_cons);
	    M_CDR(continuation) = temp;
	    inline_note_reclaim_cons(instance_cons,Qeval);
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = instance_cons;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = instance_cons;
	    }
	    else {
		temp = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = instance_cons;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = instance_cons;
	    }
	    M_CDR(instance_cons) = Nil;
	    return VALUES_3(temp_1,continuation,Qnever);
	}
    }
}

static Object string_constant_4;   /* " named by" */

/* ROLE-PRINT-NAMED-BY */
Object role_print_named_by(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,70);
    GENSYM_RETURN_ONE(print_standard_two_element_role(role,
	    local_variable_qm,string_constant_4));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-NAMED-BY */
Object serve_first_named_by(role,domain)
    Object role, domain;
{
    Object class_1, class_description, symbol_name_qm, frame_or_frames_qm;
    Object frame, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object gensymed_symbol, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(149,71);
    class_1 = M_CAR(M_CDR(role));
    class_description = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    symbol_name_qm = coerce_to_symbol_for_named_by_role(role,domain,class_1);
    frame_or_frames_qm = symbol_name_qm ? 
	    lookup_kb_specific_property_value(symbol_name_qm,
	    Frame_or_frames_with_this_name_kbprop) : Qnil;
    if ( !TRUEP(symbol_name_qm))
	return VALUES_3(Nil,Nil,Nil);
    else if ( !TRUEP(class_description) ||  
	    !TRUEP(ISVREF(class_description,(SI_Long)16L)) ||  
	    !TRUEP(frame_or_frames_qm))
	return VALUES_3(Nil,Nil,Nil);
    else if (CONSP(frame_or_frames_qm)) {
	frame = Nil;
	ab_loop_list_ = frame_or_frames_qm;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	frame = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol = ISVREF(frame,(SI_Long)1L);
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(class_description,
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
	    ab_loopvar__2 = eval_cons_1(frame,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	goto next_loop;
      end_loop:
	temp_1 = ab_loopvar_;
	goto end_1;
	temp_1 = Qnil;
      end_1:;
	return serve_all_unreprocessed_frames(temp_1);
    }
    else {
	gensymed_symbol = ISVREF(frame_or_frames_qm,(SI_Long)1L);
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(class_description,
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
	if (temp ? TRUEP(serve_item_p(frame_or_frames_qm)) : TRUEP(Nil))
	    return VALUES_3(frame_or_frames_qm,Nil,Qnever);
	else
	    return VALUES_3(Nil,Nil,Nil);
    }
}

static Object string_constant_5;   /* "Attempting to get the ~a named by ~NC, which is not a symbol." */

static Object string_constant_6;   /* "Attempting to get the ~a named by ~a, which is ~
				    * ??     not a symbolic variable or parameter."
				    */

static Object string_constant_7;   /* "Attempting to get the ~a named by ~a, which is not a ~
				    *               variable or parameter."
				    */

/* COERCE-TO-SYMBOL-FOR-NAMED-BY-ROLE */
Object coerce_to_symbol_for_named_by_role(role,domain,class_name)
    Object role, domain, class_name;
{
    Object symbol_name_qm, value, expiration_qm, type, managed_number_or_value;
    Object temp, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_1;
    Object result;

    x_note_fn_call(149,72);
    symbol_name_qm = Nil;
    value = Nil;
    expiration_qm = Nil;
    type = Nil;
    if ( !TRUEP(domain))
	warning_for_null_domain(role);
    else if (SYMBOLP(domain))
	return VALUES_1(domain);
    else if (SIMPLE_VECTOR_P(domain) && EQ(ISVREF(domain,(SI_Long)0L),
	    Qg2_defstruct_structure_name_temporary_constant_g2_struct)) {
	if (EQ(ISVREF(domain,(SI_Long)2L),Qsymbol)) {
	    managed_number_or_value = ISVREF(domain,(SI_Long)1L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		symbol_name_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		symbol_name_qm = aref1(managed_number_or_value,
			FIX((SI_Long)0L));
	    else
		symbol_name_qm = managed_number_or_value;
	}
	else if ((SI_Long)1L <= IFIX(Warning_message_level)) {
	    managed_number_or_value = ISVREF(domain,(SI_Long)1L);
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
	    give_warning_1(5,FIX((SI_Long)1L),string_constant_5,class_name,
		    temp,ISVREF(domain,(SI_Long)2L));
	}
    }
    else {
	sub_class_bit_vector = ISVREF(ISVREF(domain,(SI_Long)1L),(SI_Long)19L);
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
	    temp_1 = (SI_Long)0L < gensymed_symbol;
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    if ((IFIX(Current_computation_flags) & (SI_Long)8L) != (SI_Long)0L)
		result = get_current_value_for_named_by_without_wake_ups(domain);
	    else
		result = get_current_value(domain,Nil);
	    MVS_3(result,value,expiration_qm,type);
	    if ( !TRUEP(expiration_qm));
	    else if (EQ(type,Qsymbol))
		symbol_name_qm = value;
	    else {
		if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) != (SI_Long)0L)
		    reclaim_wide_string(value);
		if ((SI_Long)1L <= IFIX(Warning_message_level))
		    give_warning_1(4,FIX((SI_Long)1L),string_constant_6,
			    class_name,domain);
	    }
	}
	else if ((SI_Long)1L <= IFIX(Warning_message_level))
	    give_warning_1(4,FIX((SI_Long)1L),string_constant_7,class_name,
		    domain);
    }
    return VALUES_1(symbol_name_qm);
}

/* GET-CURRENT-VALUE-FOR-NAMED-BY-WITHOUT-WAKE-UPS */
Object get_current_value_for_named_by_without_wake_ups(variable_or_parameter)
    Object variable_or_parameter;
{
    volatile Object value;
    volatile Object expiration_qm;
    volatile Object type;
    volatile Object gensymed_symbol;
    Object variables_that_did_not_have_values, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, pruned_interest_list;
    Object eval_cons, temp, svref_arg_2;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(149,73);
    SAVE_STACK();
    value = Nil;
    expiration_qm = Nil;
    type = Nil;
    gensymed_symbol = Nil;
    if (PUSH_UNWIND_PROTECT(0)) {
	variables_that_did_not_have_values = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Variables_that_did_not_have_values,Qvariables_that_did_not_have_values,variables_that_did_not_have_values,
		0);
	  result = get_current_value(variable_or_parameter,Nil);
	  MVS_3(result,value,expiration_qm,type);
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
	ISVREF(gensymed_symbol_2,(SI_Long)36L) = pruned_interest_list;
	if ( !TRUEP(pruned_interest_list) &&  
		!TRUEP(ISVREF(gensymed_symbol_2,(SI_Long)38L)))
	    withdraw_backward_chaining(gensymed_symbol_2);
	if ( !TRUEP(gensymed_symbol_3))
	    goto end_loop;
	gensymed_symbol_1 = gensymed_symbol_3;
	goto next_loop;
      end_loop:
	if (gensymed_symbol &&  !((SI_Long)0L == inline_debugging_consing())) {
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
	    temp = ISVREF(Available_eval_conses_tail_vector,
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
    result = VALUES_3(value,expiration_qm,type);
    RESTORE_STACK();
    return result;
}

static Object string_constant_8;   /* " named by debugging name " */

/* ROLE-PRINT-NAMED-BY-DEBUGGING-NAME */
Object role_print_named_by_debugging_name(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,74);
    GENSYM_RETURN_ONE(print_standard_two_element_role(role,
	    local_variable_qm,string_constant_8));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-NAMED-BY-DEBUGGING-NAME */
Object serve_first_named_by_debugging_name(role,domain)
    Object role, domain;
{
    Object class_1, name_as_string, frame, ab_loop_list_, frame_to_serve_qm;
    Object gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(149,75);
    class_1 = SECOND(role);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(domain) != (SI_Long)0L)
	name_as_string = domain;
    else if (SYMBOLP(domain))
	name_as_string = symbol_name_text_string(domain);
    else
	name_as_string = error((SI_Long)2L,
		"Named-by for inspect received a value that was not a symbol or text:  ~a.",
		domain);
    frame = Nil;
    ab_loop_list_ = All_frames_with_simple_debugging_names;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    frame = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (string_equalw(name_as_string,get_cached_debugging_name(frame))) {
	frame_to_serve_qm = frame;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    frame_to_serve_qm = Qnil;
  end_1:;
    if (frame_to_serve_qm) {
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(class_1,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(frame_to_serve_qm,
		    (SI_Long)1L),(SI_Long)19L);
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
    if (temp ? TRUEP(serve_item_p(frame_to_serve_qm)) : TRUEP(Nil))
	return VALUES_3(frame_to_serve_qm,Nil,Qnever);
    else
	return VALUES_3(Nil,Nil,Nil);
}

static Object string_constant_9;   /* " nearest to" */

/* ROLE-PRINT-NEAREST */
Object role_print_nearest(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,76);
    GENSYM_RETURN_ONE(print_standard_two_element_role(role,
	    local_variable_qm,string_constant_9));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-NEAREST */
Object serve_first_nearest(role,domain)
    Object role, domain;
{
    Object class_1, class_description_qm, found_object;

    x_note_fn_call(149,77);
    class_1 = SECOND(role);
    class_description_qm = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    found_object = class_description_qm && ISVREF(class_description_qm,
	    (SI_Long)16L) ? 
	    find_nearest_active_instance_of_class_to_entity(class_description_qm,
	    domain) : Nil;
    if (found_object)
	return VALUES_3(found_object,Nil,Qnever);
    else
	return VALUES_3(Nil,Nil,Nil);
}

/* FIND-NEAREST-ACTIVE-INSTANCE-OF-CLASS-TO-ENTITY */
Object find_nearest_active_instance_of_class_to_entity(class_description,
	    entity)
    Object class_description, entity;
{
    Object icon_x, icon_y, workspace_qm, nearest_of_class_so_far_qm;
    Object nearest_distance_squared_so_far_qm, gensymed_symbol, ab_queue_form_;
    Object ab_next_queue_element_, subblock, distance_squared_qm, temp;
    Object sub_class_bit_vector;
    SI_Long x_distance, y_distance, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_3;
    char temp_1;
    double fd1, fd2;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(149,78);
    icon_x = item_x_position(entity);
    icon_y = item_y_position(entity);
    workspace_qm = get_workspace_if_any(entity);
    if (workspace_qm) {
	nearest_of_class_so_far_qm = Nil;
	nearest_distance_squared_so_far_qm = Nil;
	gensymed_symbol = ACCESS_ONCE(ISVREF(workspace_qm,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	ab_queue_form_ = gensymed_symbol;
	ab_next_queue_element_ = Nil;
	subblock = Nil;
	x_distance = (SI_Long)0L;
	y_distance = (SI_Long)0L;
	distance_squared_qm = Nil;
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
	temp = FIXNUM_MINUS(icon_x,item_x_position(subblock));
	x_distance = IFIX(FIXNUM_ABS(temp));
	temp = FIXNUM_MINUS(icon_y,item_y_position(subblock));
	y_distance = IFIX(FIXNUM_ABS(temp));
	if ( !EQ(subblock,entity) && serve_item_p(subblock)) {
	    gensymed_symbol = ISVREF(subblock,(SI_Long)1L);
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(class_description,
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
		temp_1 = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp_1 = TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1 ?  !TRUEP(nearest_distance_squared_so_far_qm) || 
		x_distance < IFIX(nearest_distance_squared_so_far_qm) && 
		y_distance < IFIX(nearest_distance_squared_so_far_qm) : 
		TRUEP(Nil)) {
	    if (x_distance < 
		    IFIX(Maximum_x_or_y_separation_allowing_fixnum_vector_distance_calculation) 
		    && y_distance < 
		    IFIX(Maximum_x_or_y_separation_allowing_fixnum_vector_distance_calculation))
		distance_squared_qm = isqrt(FIX(x_distance * x_distance + 
			y_distance * y_distance));
	    else {
		if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		    fd1 = (double)x_distance;
		    fd2 = (double)y_distance;
		    distance_squared_qm = 
			    l_round(DOUBLE_TO_DOUBLE_FLOAT(sqrt(fd1 * fd1 
			    + fd2 * fd2)),_);
		}
		POP_LOCAL_ALLOCATION(0,0);
	    }
	}
	else
	    distance_squared_qm = Nil;
	if (distance_squared_qm && ( 
		!TRUEP(nearest_distance_squared_so_far_qm) || 
		FIXNUM_LT(distance_squared_qm,
		nearest_distance_squared_so_far_qm))) {
	    nearest_of_class_so_far_qm = subblock;
	    nearest_distance_squared_so_far_qm = distance_squared_qm;
	}
	goto next_loop;
      end_loop:
	return VALUES_1(nearest_of_class_so_far_qm);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* SERVE-FIRST-ICON-COLOR */
Object serve_first_icon_color(role,domain)
    Object role, domain;
{
    Object temp;

    x_note_fn_call(149,79);
    temp = icon_color(domain);
    return VALUES_3(temp,Nil,Qnever);
}

static Object list_constant;       /* # */

static Object string_constant_10;  /* " of" */

static Object string_constant_11;  /* " icon-color of" */

/* ROLE-PRINT-ITEM-COLOR */
Object role_print_item_color(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,80);
    twrite_symbol(1,SECOND(role));
    if (local_variable_qm) {
	twrite(string_constant);
	twrite(local_variable_qm);
    }
    GENSYM_RETURN_ONE(memq_function(SECOND(role),list_constant) ? 
	    twrite(string_constant_10) : twrite(string_constant_11));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-ITEM-COLOR */
Object serve_first_item_color(role,domain)
    Object role, domain;
{
    Object value;

    x_note_fn_call(149,81);
    value = item_color(domain,SECOND(role));
    if (value)
	return VALUES_3(value,Nil,Qnever);
    else
	return VALUES_3(Nil,Nil,Nil);
}

/* ROLE-PRINT-ITEM-X-POSITION */
Object role_print_item_x_position(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,82);
    GENSYM_RETURN_ONE(print_role_whose_car_is_role_server(role,
	    local_variable_qm));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-ITEM-X-POSITION */
Object serve_first_item_x_position(role,domain)
    Object role, domain;
{
    Object temp;

    x_note_fn_call(149,83);
    temp = item_x_position(domain);
    return VALUES_3(temp,Nil,Qnever);
}

/* ROLE-PRINT-ITEM-Y-POSITION */
Object role_print_item_y_position(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,84);
    GENSYM_RETURN_ONE(print_role_whose_car_is_role_server(role,
	    local_variable_qm));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-ITEM-Y-POSITION */
Object serve_first_item_y_position(role,domain)
    Object role, domain;
{
    Object temp;

    x_note_fn_call(149,85);
    temp = item_y_position(domain);
    return VALUES_3(temp,Nil,Qnever);
}

/* ROLE-PRINT-ICON-HEADING */
Object role_print_icon_heading(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,86);
    GENSYM_RETURN_ONE(print_role_whose_car_is_role_server(role,
	    local_variable_qm));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-ICON-HEADING */
Object serve_first_icon_heading(role,domain)
    Object role, domain;
{
    Object sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(149,87);
    sub_class_bit_vector = ISVREF(ISVREF(domain,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Entity_class_description,
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
    if ( !temp)
	return VALUES_3(Nil,Nil,Nil);
    else {
	temp_1 = make_evaluation_quantity(icon_heading(domain));
	return VALUES_3(temp_1,Nil,Qnever);
    }
}

/* ROLE-PRINT-ITEM-WIDTH */
Object role_print_item_width(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,88);
    GENSYM_RETURN_ONE(print_role_whose_car_is_role_server(role,
	    local_variable_qm));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-ITEM-WIDTH */
Object serve_first_item_width(role,domain)
    Object role, domain;
{
    Object temp;

    x_note_fn_call(149,89);
    temp = item_width(domain);
    return VALUES_3(temp,Nil,Qnever);
}

/* ROLE-PRINT-ITEM-HEIGHT */
Object role_print_item_height(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,90);
    GENSYM_RETURN_ONE(print_role_whose_car_is_role_server(role,
	    local_variable_qm));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-ITEM-HEIGHT */
Object serve_first_item_height(role,domain)
    Object role, domain;
{
    Object temp;

    x_note_fn_call(149,91);
    temp = item_height(domain);
    return VALUES_3(temp,Nil,Qnever);
}

static Object string_constant_12;  /* "~(~a of~)" */

/* ROLE-PRINT-SYSTEM-ATTRIBUTE */
Object role_print_system_attribute(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,92);
    GENSYM_RETURN_ONE(tformat(2,string_constant_12,SECOND(role)));
    return VALUES_1(Nil);
}

static Object Qgsi_interface_name;  /* gsi-interface-name */

static Object Qgsi_interface_status;  /* gsi-interface-status */

static Object Qinterface_status;   /* interface-status */

static Object Qarray_length;       /* array-length */

/* SERVE-FIRST-SYSTEM-ATTRIBUTE */
Object serve_first_system_attribute(role,domain)
    Object role, domain;
{
    Object attribute_name, slot_value, sub_class_bit_vector, temp_1;
    Object slot_value_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(149,93);
    attribute_name = SECOND(role);
    if (EQ(attribute_name,Qgsi_interface_name) || EQ(attribute_name,
	    Qgsi_interface_status) || EQ(attribute_name,Qinterface_status)) {
	slot_value = get_slot_value_or_no_slot_function(domain,
		attribute_name,Nil);
	if (EQ(slot_value,No_slot))
	    return VALUES_3(Nil,Nil,Nil);
	else if ( !TRUEP(slot_value))
	    return VALUES_3(Nil,Nil,Nil);
	else
	    return VALUES_3(FIXNUMP(slot_value) ? slot_value : slot_value,
		    Nil,Qnever);
    }
    else if (EQ(attribute_name,Qarray_length)) {
	sub_class_bit_vector = ISVREF(ISVREF(domain,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(G2_array_class_description,
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
	    temp_1 = ISVREF(domain,(SI_Long)20L);
	    return VALUES_3(temp_1,Nil,Qnever);
	}
	else {
	    slot_value_qm = 
		    frame_or_evaluation_value_user_attribute_value(domain,
		    attribute_name,Nil);
	    if (slot_value_qm)
		return VALUES_3(slot_value_qm,Nil,Qnever);
	    else
		return VALUES_3(Nil,Nil,Nil);
	}
    }
    else
	return VALUES_1(Qnil);
}

static Object string_constant_13;  /* "text of the ~(~a of~)" */

/* ROLE-PRINT-SYSTEM-ATTRIBUTE-AS-TEXT */
Object role_print_system_attribute_as_text(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,94);
    GENSYM_RETURN_ONE(tformat(2,string_constant_13,SECOND(role)));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-SYSTEM-ATTRIBUTE-AS-TEXT */
Object serve_first_system_attribute_as_text(role,domain)
    Object role, domain;
{
    x_note_fn_call(149,95);
    return serve_text_of_attribute(domain,SECOND(role),Nil);
}

static Object array_constant_3;    /* # */

/* ROLE-PRINT-TEXT-OF-ATTRIBUTE */
Object role_print_text_of_attribute(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,96);
    GENSYM_RETURN_ONE(EQ(SECOND(role),Qtext) ? 
	    twrite_beginning_of_wide_string(array_constant_3,
	    FIX((SI_Long)7L)) : tformat(2,string_constant_13,SECOND(role)));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-TEXT-OF-ATTRIBUTE */
Object serve_first_text_of_attribute(role,domain)
    Object role, domain;
{
    Object slot_denotation;

    x_note_fn_call(149,97);
    slot_denotation = M_CAR(M_CDR(role));
    if (SYMBOLP(slot_denotation))
	return serve_text_of_attribute(domain,slot_denotation,Nil);
    else
	return serve_text_of_attribute(domain,CONSP(slot_denotation) ? 
		M_CAR(M_CDR(M_CDR(slot_denotation))) : slot_denotation,
		CONSP(slot_denotation) ? M_CAR(M_CDR(slot_denotation)) : Nil);
}

static Object Qformat_overrride;   /* format-overrride */

static Object Qddd_dot_dddd_format;  /* ddd.dddd-format */

static Object string_constant_14;  /* "Cannot reference the text of the ~a of ~NF.  The text ~
				    *                        contains ~a characters.  The maximum number of ~
				    *                        characters allowed in text is ~a."
				    */

/* SERVE-TEXT-OF-ATTRIBUTE */
Object serve_text_of_attribute(frame,attribute_name,class_qualifier_qm)
    Object frame, attribute_name, class_qualifier_qm;
{
    Object real_slot_name, slot_description, slot_features, type_of_slot_qm;
    Object unnamed_text_attribute_qm, temp;
    Object evaluation_value_writing_target_length_qm, format_override_qm;
    Object current_ddd_dot_dddd_format_qm, text_string;
    SI_Long length_1;
    char temp_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(149,98);
    real_slot_name = get_slot_name_for_alias_if_any(attribute_name,frame);
    if (real_slot_name);
    else
	real_slot_name = attribute_name;
    slot_description = 
	    get_slot_description_of_class_description_function(real_slot_name,
	    ISVREF(frame,(SI_Long)1L),class_qualifier_qm);
    slot_features = slot_description ? ISVREF(slot_description,
	    (SI_Long)9L) : Nil;
    type_of_slot_qm = assq_function(Qtype,slot_features);
    unnamed_text_attribute_qm = Nil;
    if (CONSP(type_of_slot_qm) && EQ(M_CAR(type_of_slot_qm),Qtype)) {
	temp = M_CDR(type_of_slot_qm);
	temp_1 = CONSP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1 ?  !TRUEP(M_CAR(M_CDR(type_of_slot_qm))) : TRUEP(Nil))
	type_of_slot_qm = Nil;
    if ( !TRUEP(type_of_slot_qm) &&  !EQ(attribute_name,real_slot_name)) {
	real_slot_name = attribute_name;
	type_of_slot_qm = get_type_of_slot_if_any(3,frame,real_slot_name,
		class_qualifier_qm);
    }
    if (EQ(attribute_name,Qtext) &&  !EQ(real_slot_name,Qtext))
	unnamed_text_attribute_qm = T;
    if ( !TRUEP(type_of_slot_qm) ||  !TRUEP(unnamed_text_attribute_qm) && 
	    do_not_put_slot_in_attribute_tables_p(2,slot_description,T))
	return VALUES_3(Nil,Nil,Nil);
    else if ( !TRUEP(attribute_is_visible_via_the_text_of_p(frame,
	    attribute_name,class_qualifier_qm)))
	return VALUES_3(Nil,Nil,Nil);
    else {
	evaluation_value_writing_target_length_qm = 
		Maximum_length_for_user_text_strings;
	PUSH_SPECIAL_WITH_SYMBOL(Evaluation_value_writing_target_length_qm,Qevaluation_value_writing_target_length_qm,evaluation_value_writing_target_length_qm,
		1);
	  format_override_qm = assq_function(Qformat_overrride,slot_features);
	  current_ddd_dot_dddd_format_qm = format_override_qm && 
		  EQ(SECOND(format_override_qm),Qddd_dot_dddd_format) ? 
		  THIRD(format_override_qm) : Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_ddd_dot_dddd_format_qm,Qcurrent_ddd_dot_dddd_format_qm,current_ddd_dot_dddd_format_qm,
		  0);
	    text_string = 
		    make_text_string_representation_for_slot_value_itself(frame,
		    get_slot_description_value(frame,slot_description),
		    type_of_slot_qm);
	    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(text_string));
	    if (FIXNUM_GT(FIX(UBYTE_16_ISAREF_1(text_string,length_1 - 
		    (SI_Long)2L) + ((UBYTE_16_ISAREF_1(text_string,
		    length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
		    (SI_Long)16L)),Maximum_length_for_user_text_strings)) {
		if ((SI_Long)1L <= IFIX(Warning_message_level)) {
		    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(text_string));
		    give_warning_1(6,FIX((SI_Long)1L),string_constant_14,
			    attribute_name,frame,
			    FIX(UBYTE_16_ISAREF_1(text_string,length_1 - 
			    (SI_Long)2L) + ((UBYTE_16_ISAREF_1(text_string,
			    length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			    (SI_Long)16L)),
			    Maximum_length_for_user_text_strings);
		}
		reclaim_text_string(text_string);
		result = VALUES_3(Nil,Nil,Nil);
	    }
	    else
		result = VALUES_3(text_string,Nil,Qnever);
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
}

Object Transparent_classes_for_schematic_search = UNBOUND;

Object Classes_to_ignore_for_schematic_search = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Connections_in_connection_paths, Qconnections_in_connection_paths);

DEFINE_VARIABLE_WITH_SYMBOL(Current_connection_path, Qcurrent_connection_path);

/* CLEAR-ENTITIES-TO-BE-EXCLUDED */
Object clear_entities_to_be_excluded(entities)
    Object entities;
{
    x_note_fn_call(149,99);
    clear_blocks_found_in_search(entities);
    return reclaim_eval_list_1(entities);
}

/* CLEAR-CONNECTIONS-TO-BE-EXCLUDED */
Object clear_connections_to_be_excluded(connections)
    Object connections;
{
    x_note_fn_call(149,100);
    clear_connections_found_in_search(connections);
    return reclaim_eval_list_1(connections);
}

/* SEARCH-FROM-ORIGIN-ENTITY */
Object search_from_origin_entity(entity,class_1,directionality_qm,
	    also_get_port_and_direction_info_qm,
	    required_connection_directionality_for_inverse_role_service_qm,
	    do_not_stop_search_at_connections_qm,original_port_name_qm,
	    original_port_directionality_qm)
    Object entity, class_1, directionality_qm;
    Object also_get_port_and_direction_info_qm;
    Object required_connection_directionality_for_inverse_role_service_qm;
    Object do_not_stop_search_at_connections_qm, original_port_name_qm;
    Object original_port_directionality_qm;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, ab_port_name_, connection_frame_1;
    Object temp, ab_less_than_branch_qm_, x2;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(149,101);
    if (original_port_name_qm) {
	scope_conses = Scope_conses;
	ab_node_stack_ = Nil;
	ab_current_node_ = Nil;
	gensymed_symbol = ACCESS_ONCE(ISVREF(entity,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
	ab_skip_list_form_ = gensymed_symbol;
	ab_skip_list_p_ = Nil;
	ab_next_node_ = Nil;
	ab_tail_node_ = Nil;
	ab_current_alist_ = Nil;
	ab_entry_cons_ = Nil;
	ab_connection_ = Nil;
	ab_connection_item_ = Nil;
	connection = Nil;
	ab_port_name_ = original_port_name_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  connection_frame_1 = Nil;
	  gensymed_symbol = CDR(ab_skip_list_form_);
	  if (CONSP(gensymed_symbol)) {
	      temp = M_CAR(gensymed_symbol);
	      temp_1 = SIMPLE_VECTOR_P(temp);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1) {
	      temp = M_CDR(gensymed_symbol);
	      ab_skip_list_p_ = SIMPLE_VECTOR_P(temp) ? T : Nil;
	  }
	  else
	      ab_skip_list_p_ = Nil;
	  if (ab_skip_list_p_) {
	      ab_next_node_ = 
		      ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
		      (SI_Long)0L),(SI_Long)0L));
	      ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
	      if (EQ(ab_next_node_,ab_tail_node_))
		  ab_next_node_ = Nil;
	  }
	  else
	      ab_next_node_ = CDR(ab_skip_list_form_);
	next_loop:
	next_loop_1:
	  if (ab_current_alist_) {
	      ab_entry_cons_ = M_CAR(ab_current_alist_);
	      ab_connection_ = M_CAR(ab_entry_cons_);
	      ab_connection_item_ = M_CDR(ab_entry_cons_);
	      ab_current_alist_ = M_CDR(ab_current_alist_);
	  }
	  else if (ab_skip_list_p_) {
	      if (ab_next_node_) {
		  ab_current_node_ = ab_next_node_;
		  ab_next_node_ = 
			  ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node_,
			  (SI_Long)0L),(SI_Long)0L));
		  if (EQ(ab_next_node_,ab_tail_node_))
		      ab_next_node_ = Nil;
		  ab_connection_ = ISVREF(ab_current_node_,(SI_Long)2L);
		  ab_connection_item_ = ISVREF(ab_current_node_,(SI_Long)3L);
	      }
	      else
		  ab_current_node_ = Nil;
	  }
	  else {
	      if (ab_next_node_) {
		  ab_current_node_ = ab_next_node_;
		  ab_less_than_branch_qm_ = Nil;
		next_loop_2:
		  ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			  (SI_Long)1L);
		  if ( !TRUEP(ab_less_than_branch_qm_))
		      goto end_loop;
		  ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
		  ab_current_node_ = ab_less_than_branch_qm_;
		  goto next_loop_2;
		end_loop:;
	      }
	      else if (ab_node_stack_) {
		  ab_next_node_ = ab_node_stack_;
		  ab_current_node_ = M_CAR(ab_node_stack_);
		  ab_node_stack_ = M_CDR(ab_node_stack_);
	      }
	      else
		  ab_current_node_ = Nil;
	      if (ab_current_node_) {
		  ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
		  ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
		  ab_entry_cons_ = M_CAR(ab_current_alist_);
		  ab_connection_ = M_CAR(ab_entry_cons_);
		  ab_connection_item_ = M_CDR(ab_entry_cons_);
		  ab_current_alist_ = M_CDR(ab_current_alist_);
	      }
	  }
	  if ( !TRUEP(ab_current_node_) || ab_current_node_ && 
		  ab_connection_ && memq_function(ab_port_name_,
		  connection_item_name_or_names(ab_connection_item_)))
	      goto end_1;
	  goto next_loop_1;
	end_loop_1:
	end_1:
	  if ( !TRUEP(ab_current_node_))
	      goto end_loop_2;
	  connection = ab_connection_;
	  connection_frame_1 = ISVREF(connection,(SI_Long)1L);
	  if (SIMPLE_VECTOR_P(connection_frame_1) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_1)) > 
		  (SI_Long)2L &&  !EQ(ISVREF(connection_frame_1,
		  (SI_Long)1L),Qavailable_frame_vector)) {
	      x2 = ISVREF(connection_frame_1,(SI_Long)1L);
	      temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  temp_1 =  !(temp_1 ? TRUEP(ISVREF(ISVREF(connection_frame_1,
		  (SI_Long)1L),(SI_Long)16L)) : TRUEP(Nil));
	  if (temp_1);
	  else
	      temp_1 = TRUEP(serve_item_p(connection_frame_1));
	  if (temp_1)
	      search_for_directly_connected_entities_for_connection(entity,
		      class_1,connection,directionality_qm,
		      also_get_port_and_direction_info_qm,Nil,
		      required_connection_directionality_for_inverse_role_service_qm,
		      do_not_stop_search_at_connections_qm);
	  goto next_loop;
	end_loop_2:
	  result = VALUES_1(Qnil);
	POP_SPECIAL();
	return result;
    }
    else if (EQ(original_port_directionality_qm,Qinput)) {
	scope_conses = Scope_conses;
	ab_node_stack_ = Nil;
	ab_current_node_ = Nil;
	gensymed_symbol = ACCESS_ONCE(ISVREF(entity,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
	ab_skip_list_form_ = gensymed_symbol;
	ab_skip_list_p_ = Nil;
	ab_next_node_ = Nil;
	ab_tail_node_ = Nil;
	ab_current_alist_ = Nil;
	ab_entry_cons_ = Nil;
	ab_connection_ = Nil;
	ab_connection_item_ = Nil;
	connection = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  connection_frame_1 = Nil;
	  gensymed_symbol = CDR(ab_skip_list_form_);
	  if (CONSP(gensymed_symbol)) {
	      temp = M_CAR(gensymed_symbol);
	      temp_1 = SIMPLE_VECTOR_P(temp);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1) {
	      temp = M_CDR(gensymed_symbol);
	      ab_skip_list_p_ = SIMPLE_VECTOR_P(temp) ? T : Nil;
	  }
	  else
	      ab_skip_list_p_ = Nil;
	  if (ab_skip_list_p_) {
	      ab_next_node_ = 
		      ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
		      (SI_Long)0L),(SI_Long)0L));
	      ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
	      if (EQ(ab_next_node_,ab_tail_node_))
		  ab_next_node_ = Nil;
	  }
	  else
	      ab_next_node_ = CDR(ab_skip_list_form_);
	next_loop_3:
	next_loop_4:
	  if (ab_current_alist_) {
	      ab_entry_cons_ = M_CAR(ab_current_alist_);
	      ab_connection_ = M_CAR(ab_entry_cons_);
	      ab_connection_item_ = M_CDR(ab_entry_cons_);
	      ab_current_alist_ = M_CDR(ab_current_alist_);
	  }
	  else if (ab_skip_list_p_) {
	      if (ab_next_node_) {
		  ab_current_node_ = ab_next_node_;
		  ab_next_node_ = 
			  ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node_,
			  (SI_Long)0L),(SI_Long)0L));
		  if (EQ(ab_next_node_,ab_tail_node_))
		      ab_next_node_ = Nil;
		  ab_connection_ = ISVREF(ab_current_node_,(SI_Long)2L);
		  ab_connection_item_ = ISVREF(ab_current_node_,(SI_Long)3L);
	      }
	      else
		  ab_current_node_ = Nil;
	  }
	  else {
	      if (ab_next_node_) {
		  ab_current_node_ = ab_next_node_;
		  ab_less_than_branch_qm_ = Nil;
		next_loop_5:
		  ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			  (SI_Long)1L);
		  if ( !TRUEP(ab_less_than_branch_qm_))
		      goto end_loop_3;
		  ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
		  ab_current_node_ = ab_less_than_branch_qm_;
		  goto next_loop_5;
		end_loop_3:;
	      }
	      else if (ab_node_stack_) {
		  ab_next_node_ = ab_node_stack_;
		  ab_current_node_ = M_CAR(ab_node_stack_);
		  ab_node_stack_ = M_CDR(ab_node_stack_);
	      }
	      else
		  ab_current_node_ = Nil;
	      if (ab_current_node_) {
		  ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
		  ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
		  ab_entry_cons_ = M_CAR(ab_current_alist_);
		  ab_connection_ = M_CAR(ab_entry_cons_);
		  ab_connection_item_ = M_CDR(ab_entry_cons_);
		  ab_current_alist_ = M_CDR(ab_current_alist_);
	      }
	  }
	  if ( !TRUEP(ab_current_node_) || ab_current_node_ && 
		  ab_connection_ && EQ(ISVREF(ab_connection_,(SI_Long)2L),
		  entity))
	      goto end_2;
	  goto next_loop_4;
	end_loop_4:
	end_2:
	  if ( !TRUEP(ab_current_node_))
	      goto end_loop_5;
	  connection = ab_connection_;
	  connection_frame_1 = ISVREF(connection,(SI_Long)1L);
	  if (SIMPLE_VECTOR_P(connection_frame_1) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_1)) > 
		  (SI_Long)2L &&  !EQ(ISVREF(connection_frame_1,
		  (SI_Long)1L),Qavailable_frame_vector)) {
	      x2 = ISVREF(connection_frame_1,(SI_Long)1L);
	      temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  temp_1 =  !(temp_1 ? TRUEP(ISVREF(ISVREF(connection_frame_1,
		  (SI_Long)1L),(SI_Long)16L)) : TRUEP(Nil));
	  if (temp_1);
	  else
	      temp_1 = TRUEP(serve_item_p(connection_frame_1));
	  if (temp_1) {
	      if ( !((SI_Long)0L != (IFIX(ISVREF(connection,(SI_Long)7L)) 
		      & (SI_Long)1L)))
		  search_for_directly_connected_entities_for_connection(entity,
			  class_1,connection,Qinput,
			  also_get_port_and_direction_info_qm,Nil,
			  required_connection_directionality_for_inverse_role_service_qm,
			  do_not_stop_search_at_connections_qm);
	  }
	  goto next_loop_3;
	end_loop_5:
	  result = VALUES_1(Qnil);
	POP_SPECIAL();
	return result;
    }
    else if (EQ(original_port_directionality_qm,Qoutput)) {
	scope_conses = Scope_conses;
	ab_node_stack_ = Nil;
	ab_current_node_ = Nil;
	gensymed_symbol = ACCESS_ONCE(ISVREF(entity,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
	ab_skip_list_form_ = gensymed_symbol;
	ab_skip_list_p_ = Nil;
	ab_next_node_ = Nil;
	ab_tail_node_ = Nil;
	ab_current_alist_ = Nil;
	ab_entry_cons_ = Nil;
	ab_connection_ = Nil;
	ab_connection_item_ = Nil;
	connection = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  connection_frame_1 = Nil;
	  gensymed_symbol = CDR(ab_skip_list_form_);
	  if (CONSP(gensymed_symbol)) {
	      temp = M_CAR(gensymed_symbol);
	      temp_1 = SIMPLE_VECTOR_P(temp);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1) {
	      temp = M_CDR(gensymed_symbol);
	      ab_skip_list_p_ = SIMPLE_VECTOR_P(temp) ? T : Nil;
	  }
	  else
	      ab_skip_list_p_ = Nil;
	  if (ab_skip_list_p_) {
	      ab_next_node_ = 
		      ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
		      (SI_Long)0L),(SI_Long)0L));
	      ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
	      if (EQ(ab_next_node_,ab_tail_node_))
		  ab_next_node_ = Nil;
	  }
	  else
	      ab_next_node_ = CDR(ab_skip_list_form_);
	next_loop_6:
	next_loop_7:
	  if (ab_current_alist_) {
	      ab_entry_cons_ = M_CAR(ab_current_alist_);
	      ab_connection_ = M_CAR(ab_entry_cons_);
	      ab_connection_item_ = M_CDR(ab_entry_cons_);
	      ab_current_alist_ = M_CDR(ab_current_alist_);
	  }
	  else if (ab_skip_list_p_) {
	      if (ab_next_node_) {
		  ab_current_node_ = ab_next_node_;
		  ab_next_node_ = 
			  ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node_,
			  (SI_Long)0L),(SI_Long)0L));
		  if (EQ(ab_next_node_,ab_tail_node_))
		      ab_next_node_ = Nil;
		  ab_connection_ = ISVREF(ab_current_node_,(SI_Long)2L);
		  ab_connection_item_ = ISVREF(ab_current_node_,(SI_Long)3L);
	      }
	      else
		  ab_current_node_ = Nil;
	  }
	  else {
	      if (ab_next_node_) {
		  ab_current_node_ = ab_next_node_;
		  ab_less_than_branch_qm_ = Nil;
		next_loop_8:
		  ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			  (SI_Long)1L);
		  if ( !TRUEP(ab_less_than_branch_qm_))
		      goto end_loop_6;
		  ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
		  ab_current_node_ = ab_less_than_branch_qm_;
		  goto next_loop_8;
		end_loop_6:;
	      }
	      else if (ab_node_stack_) {
		  ab_next_node_ = ab_node_stack_;
		  ab_current_node_ = M_CAR(ab_node_stack_);
		  ab_node_stack_ = M_CDR(ab_node_stack_);
	      }
	      else
		  ab_current_node_ = Nil;
	      if (ab_current_node_) {
		  ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
		  ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
		  ab_entry_cons_ = M_CAR(ab_current_alist_);
		  ab_connection_ = M_CAR(ab_entry_cons_);
		  ab_connection_item_ = M_CDR(ab_entry_cons_);
		  ab_current_alist_ = M_CDR(ab_current_alist_);
	      }
	  }
	  if ( !TRUEP(ab_current_node_) || ab_current_node_ && 
		  ab_connection_ && EQ(ISVREF(ab_connection_,(SI_Long)3L),
		  entity))
	      goto end_3;
	  goto next_loop_7;
	end_loop_7:
	end_3:
	  if ( !TRUEP(ab_current_node_))
	      goto end_loop_8;
	  connection = ab_connection_;
	  connection_frame_1 = ISVREF(connection,(SI_Long)1L);
	  if (SIMPLE_VECTOR_P(connection_frame_1) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_1)) > 
		  (SI_Long)2L &&  !EQ(ISVREF(connection_frame_1,
		  (SI_Long)1L),Qavailable_frame_vector)) {
	      x2 = ISVREF(connection_frame_1,(SI_Long)1L);
	      temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  temp_1 =  !(temp_1 ? TRUEP(ISVREF(ISVREF(connection_frame_1,
		  (SI_Long)1L),(SI_Long)16L)) : TRUEP(Nil));
	  if (temp_1);
	  else
	      temp_1 = TRUEP(serve_item_p(connection_frame_1));
	  if (temp_1) {
	      if ( !((SI_Long)0L != (IFIX(ISVREF(connection,(SI_Long)7L)) 
		      & (SI_Long)1L)))
		  search_for_directly_connected_entities_for_connection(entity,
			  class_1,connection,Qoutput,
			  also_get_port_and_direction_info_qm,Nil,
			  required_connection_directionality_for_inverse_role_service_qm,
			  do_not_stop_search_at_connections_qm);
	  }
	  goto next_loop_6;
	end_loop_8:
	  result = VALUES_1(Qnil);
	POP_SPECIAL();
	return result;
    }
    else
	return search_for_directly_connected_entities_rec(entity,class_1,
		directionality_qm,also_get_port_and_direction_info_qm,
		required_connection_directionality_for_inverse_role_service_qm,
		do_not_stop_search_at_connections_qm);
}

/* DECACHE-ROLES-FOR-CONNECTION-POST-AND-NAMESAKES */
Object decache_roles_for_connection_post_and_namesakes(connection_post,names)
    Object connection_post, names;
{
    Object namesakes_done_so_far, names_sic, name, names_sic_1, frame;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(149,102);
    if (Role_caching_enabled_qm) {
	decache_connection_roles_1(connection_post);
	namesakes_done_so_far = Qnil;
	names_sic = names;
	name = Nil;
      next_loop:
	name = CONSP(names_sic) ? CAR(names_sic) : names_sic;
	if ( !TRUEP(name))
	    goto end_loop;
	names_sic_1 = lookup_kb_specific_property_value(name,
		Frame_or_frames_with_this_name_kbprop);
	frame = Nil;
      next_loop_1:
	frame = CONSP(names_sic_1) ? CAR(names_sic_1) : names_sic_1;
	if ( !TRUEP(frame))
	    goto end_loop_1;
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Connection_post_class_description,(SI_Long)18L));
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
	if (temp ?  !TRUEP(memq_function(frame,namesakes_done_so_far)) : 
		TRUEP(Nil)) {
	    decache_roles_for_connection_post_search(frame);
	    namesakes_done_so_far = gensym_cons_1(frame,namesakes_done_so_far);
	}
	names_sic_1 = CONSP(names_sic_1) ? CDR(names_sic_1) : Nil;
	goto next_loop_1;
      end_loop_1:;
	names_sic = CONSP(names_sic) ? CDR(names_sic) : Nil;
	goto next_loop;
      end_loop:;
	return reclaim_gensym_list_1(namesakes_done_so_far);
    }
    else
	return VALUES_1(Nil);
}

/* DECACHE-ROLES-FOR-CONNECTION-POST */
Object decache_roles_for_connection_post(connection_post)
    Object connection_post;
{
    x_note_fn_call(149,103);
    if (Role_caching_enabled_qm)
	return decache_roles_for_connection_post_1(connection_post);
    else
	return VALUES_1(Nil);
}

/* DECACHE-ROLES-FOR-CONNECTION-POST-1 */
Object decache_roles_for_connection_post_1(connection_post)
    Object connection_post;
{
    Object name_or_names, cp_list, cp_list_tail, names_sic, name, names_sic_1;
    Object frame, sub_class_bit_vector, gensymed_symbol_3, cp, ab_loop_list_;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(149,104);
    decache_connection_roles(connection_post);
    name_or_names = get_lookup_slot_value_given_default(connection_post,
	    Qname_or_names_for_frame,Nil);
    cp_list = Nil;
    cp_list_tail = Nil;
    if (name_or_names) {
	names_sic = name_or_names;
	name = Nil;
      next_loop:
	name = CONSP(names_sic) ? CAR(names_sic) : names_sic;
	if ( !TRUEP(name))
	    goto end_loop;
	names_sic_1 = lookup_kb_specific_property_value(name,
		Frame_or_frames_with_this_name_kbprop);
	frame = Nil;
      next_loop_1:
	frame = CONSP(names_sic_1) ? CAR(names_sic_1) : names_sic_1;
	if ( !TRUEP(frame))
	    goto end_loop_1;
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Connection_post_class_description,(SI_Long)18L));
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
	if (temp ?  !TRUEP(memq_function(frame,cp_list)) : TRUEP(Nil)) {
	    gensymed_symbol_3 = frame;
	    gensymed_symbol_3 = gensym_cons_1(gensymed_symbol_3,Nil);
	    if (cp_list) {
		if ( !TRUEP(cp_list_tail))
		    cp_list_tail = last(cp_list,_);
		M_CDR(cp_list_tail) = gensymed_symbol_3;
	    }
	    else
		cp_list = gensymed_symbol_3;
	    cp_list_tail = gensymed_symbol_3;
	}
	names_sic_1 = CONSP(names_sic_1) ? CDR(names_sic_1) : Nil;
	goto next_loop_1;
      end_loop_1:;
	names_sic = CONSP(names_sic) ? CDR(names_sic) : Nil;
	goto next_loop;
      end_loop:;
    }
    else
	cp_list = gensym_cons_1(connection_post,Nil);
    cp = Nil;
    ab_loop_list_ = cp_list;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    cp = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    decache_roles_for_connection_post_search(cp);
    goto next_loop_2;
  end_loop_2:;
    return reclaim_gensym_list_1(cp_list);
}

static Object Qsuperior_connection_cache;  /* superior-connection-cache */

/* DECACHE-ROLES-FOR-CONNECTION-POST-SEARCH */
Object decache_roles_for_connection_post_search(connection_post)
    Object connection_post;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, temp, ab_less_than_branch_qm_;
    Object superior_connection_and_end;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(149,105);
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(connection_post,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)6L)) : Nil;
    ab_skip_list_form_ = gensymed_symbol;
    ab_skip_list_p_ = Nil;
    ab_next_node_ = Nil;
    ab_tail_node_ = Nil;
    ab_current_alist_ = Nil;
    ab_entry_cons_ = Nil;
    ab_connection_ = Nil;
    ab_connection_item_ = Nil;
    connection = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      gensymed_symbol = CDR(ab_skip_list_form_);
      if (CONSP(gensymed_symbol)) {
	  temp = M_CAR(gensymed_symbol);
	  temp_1 = SIMPLE_VECTOR_P(temp);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  temp = M_CDR(gensymed_symbol);
	  ab_skip_list_p_ = SIMPLE_VECTOR_P(temp) ? T : Nil;
      }
      else
	  ab_skip_list_p_ = Nil;
      if (ab_skip_list_p_) {
	  ab_next_node_ = 
		  ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
		  (SI_Long)0L),(SI_Long)0L));
	  ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
	  if (EQ(ab_next_node_,ab_tail_node_))
	      ab_next_node_ = Nil;
      }
      else
	  ab_next_node_ = CDR(ab_skip_list_form_);
    next_loop:
    next_loop_1:
      if (ab_current_alist_) {
	  ab_entry_cons_ = M_CAR(ab_current_alist_);
	  ab_connection_ = M_CAR(ab_entry_cons_);
	  ab_connection_item_ = M_CDR(ab_entry_cons_);
	  ab_current_alist_ = M_CDR(ab_current_alist_);
      }
      else if (ab_skip_list_p_) {
	  if (ab_next_node_) {
	      ab_current_node_ = ab_next_node_;
	      ab_next_node_ = 
		      ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node_,
		      (SI_Long)0L),(SI_Long)0L));
	      if (EQ(ab_next_node_,ab_tail_node_))
		  ab_next_node_ = Nil;
	      ab_connection_ = ISVREF(ab_current_node_,(SI_Long)2L);
	      ab_connection_item_ = ISVREF(ab_current_node_,(SI_Long)3L);
	  }
	  else
	      ab_current_node_ = Nil;
      }
      else {
	  if (ab_next_node_) {
	      ab_current_node_ = ab_next_node_;
	      ab_less_than_branch_qm_ = Nil;
	    next_loop_2:
	      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
	      if ( !TRUEP(ab_less_than_branch_qm_))
		  goto end_loop;
	      ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
	      ab_current_node_ = ab_less_than_branch_qm_;
	      goto next_loop_2;
	    end_loop:;
	  }
	  else if (ab_node_stack_) {
	      ab_next_node_ = ab_node_stack_;
	      ab_current_node_ = M_CAR(ab_node_stack_);
	      ab_node_stack_ = M_CDR(ab_node_stack_);
	  }
	  else
	      ab_current_node_ = Nil;
	  if (ab_current_node_) {
	      ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
	      ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
	      ab_entry_cons_ = M_CAR(ab_current_alist_);
	      ab_connection_ = M_CAR(ab_entry_cons_);
	      ab_connection_item_ = M_CDR(ab_entry_cons_);
	      ab_current_alist_ = M_CDR(ab_current_alist_);
	  }
      }
      if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_)
	  goto end_1;
      goto next_loop_1;
    end_loop_1:
    end_1:
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_2;
      connection = ab_connection_;
      decache_roles_for_entities_related_to_this_connection(connection);
      goto next_loop;
    end_loop_2:;
    POP_SPECIAL();
    superior_connection_and_end = 
	    get_lookup_slot_value_given_default(connection_post,
	    Qsuperior_connection_cache,Nil);
    if (superior_connection_and_end)
	return decache_roles_for_entities_related_to_this_connection(CDR(superior_connection_and_end));
    else
	return VALUES_1(Nil);
}

static Object Qreclaim_eval_cons_function;  /* reclaim-eval-cons-function */

/* SEARCH-FOR-DIRECTLY-CONNECTED-ENTITIES */
Object search_for_directly_connected_entities(entity,class_1,
	    original_port_name_qm,original_port_directionality_qm,
	    directionality_qm,also_get_port_and_direction_info_qm,
	    required_connection_directionality_for_inverse_role_service_qm,
	    do_not_stop_search_at_connections_qm)
    Object entity, class_1, original_port_name_qm;
    Object original_port_directionality_qm, directionality_qm;
    Object also_get_port_and_direction_info_qm;
    Object required_connection_directionality_for_inverse_role_service_qm;
    Object do_not_stop_search_at_connections_qm;
{
    Object sub_class_bit_vector, connection_qm;
    Object entities_or_triples_found_in_both_searches, direction_to_try;
    Object connections_to_be_excluded_qm, entities_to_be_excluded_qm;
    Object entities_or_triples_found_in_search, x2, entity_1, temp_1;
    Object name_or_names, cp_list, cp_list_tail, names_sic, name, names_sic_1;
    Object frame, gensymed_symbol_3, cp, ab_loop_list_;
    Object superior_connection_and_end, temp_2, superior_connection;
    Object superior_connection_frame, connection_end, required_direction_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, svref_new_value;
    char temp, self_connected_qm;
    Declare_stack_pointer;
    Declare_special(3);
    Object result;

    x_note_fn_call(149,106);
    SAVE_STACK();
    sub_class_bit_vector = ISVREF(ISVREF(entity,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Connection_class_description,
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
	connection_qm = ISVREF(entity,(SI_Long)21L);
	if (connection_qm) {
	    entities_or_triples_found_in_both_searches = Nil;
	    self_connected_qm = EQ(ISVREF(connection_qm,(SI_Long)2L),
		    ISVREF(connection_qm,(SI_Long)3L));
	    direction_to_try = Qinput;
	  next_loop:
	    connections_to_be_excluded_qm = Nil;
	    entities_to_be_excluded_qm = Nil;
	    entities_or_triples_found_in_search = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Entities_or_triples_found_in_search,Qentities_or_triples_found_in_search,entities_or_triples_found_in_search,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Entities_to_be_excluded_qm,Qentities_to_be_excluded_qm,entities_to_be_excluded_qm,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Connections_to_be_excluded_qm,Qconnections_to_be_excluded_qm,connections_to_be_excluded_qm,
			0);
		  if ( !TRUEP(directionality_qm) || EQ(directionality_qm,
			  direction_to_try)) {
		      if (SIMPLE_VECTOR_P(entity) && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(entity)) > 
			      (SI_Long)2L &&  !EQ(ISVREF(entity,
			      (SI_Long)1L),Qavailable_frame_vector)) {
			  x2 = ISVREF(entity,(SI_Long)1L);
			  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				  (SI_Long)0L),
				  Qg2_defstruct_structure_name_class_description_g2_struct) 
				  ? TRUEP(x2) : TRUEP(Qnil);
		      }
		      else
			  temp = TRUEP(Nil);
		      temp =  !(temp ? TRUEP(ISVREF(ISVREF(entity,
			      (SI_Long)1L),(SI_Long)16L)) : TRUEP(Nil));
		      if (temp);
		      else
			  temp = TRUEP(serve_item_p(entity));
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp) {
		      if (EQ(direction_to_try,Qinput)) {
			  if (directionality_qm &&  !self_connected_qm) {
			      entity_1 = ISVREF(connection_qm,(SI_Long)2L);
			      svref_new_value = IFIX(ISVREF(entity_1,
				      (SI_Long)5L)) | (SI_Long)1048576L;
			      ISVREF(entity_1,(SI_Long)5L) = 
				      FIX(svref_new_value);
			      Entities_to_be_excluded_qm = 
				      eval_cons_1(entity_1,
				      Entities_to_be_excluded_qm);
			  }
			  temp_1 = ISVREF(connection_qm,(SI_Long)2L);
		      }
		      else {
			  if (directionality_qm &&  !self_connected_qm) {
			      entity_1 = ISVREF(connection_qm,(SI_Long)3L);
			      svref_new_value = IFIX(ISVREF(entity_1,
				      (SI_Long)5L)) | (SI_Long)1048576L;
			      ISVREF(entity_1,(SI_Long)5L) = 
				      FIX(svref_new_value);
			      Entities_to_be_excluded_qm = 
				      eval_cons_1(entity_1,
				      Entities_to_be_excluded_qm);
			  }
			  temp_1 = ISVREF(connection_qm,(SI_Long)3L);
		      }
		      search_for_directly_connected_entities_for_connection(temp_1,
			      class_1,connection_qm,directionality_qm,
			      also_get_port_and_direction_info_qm,entity,
			      required_connection_directionality_for_inverse_role_service_qm,
			      do_not_stop_search_at_connections_qm);
		  }
		  entities_or_triples_found_in_both_searches = 
			  nconc2(entities_or_triples_found_in_both_searches,
			  Entities_or_triples_found_in_search);
		  clear_connections_to_be_excluded(Connections_to_be_excluded_qm);
		  clear_entities_to_be_excluded(Entities_to_be_excluded_qm);
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    if (EQ(direction_to_try,Qoutput))
		goto end_loop;
	    direction_to_try = Qoutput;
	    goto next_loop;
	  end_loop:
	    RESTORE_STACK();
	    return VALUES_1(entities_or_triples_found_in_both_searches);
	    RESTORE_STACK();
	    return VALUES_1(Qnil);
	}
	else {
	    RESTORE_STACK();
	    return VALUES_1(Nil);
	}
    }
    else {
	connections_to_be_excluded_qm = Nil;
	entities_to_be_excluded_qm = Nil;
	entities_or_triples_found_in_search = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Entities_or_triples_found_in_search,Qentities_or_triples_found_in_search,entities_or_triples_found_in_search,
		2);
	  PUSH_SPECIAL_WITH_SYMBOL(Entities_to_be_excluded_qm,Qentities_to_be_excluded_qm,entities_to_be_excluded_qm,
		  1);
	    PUSH_SPECIAL_WITH_SYMBOL(Connections_to_be_excluded_qm,Qconnections_to_be_excluded_qm,connections_to_be_excluded_qm,
		    0);
	      sub_class_bit_vector = ISVREF(ISVREF(entity,(SI_Long)1L),
		      (SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Connection_post_class_description,
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
		  if (Nil) {
		      svref_new_value = IFIX(ISVREF(entity,(SI_Long)5L)) | 
			      (SI_Long)1048576L;
		      ISVREF(entity,(SI_Long)5L) = FIX(svref_new_value);
		      Entities_to_be_excluded_qm = eval_cons_1(entity,
			      Entities_to_be_excluded_qm);
		      svref_new_value = IFIX(ISVREF(Nil,(SI_Long)7L)) | 
			      (SI_Long)512L;
		      ISVREF(Nil,(SI_Long)7L) = FIX(svref_new_value);
		      Connections_to_be_excluded_qm = eval_cons_1(Nil,
			      Connections_to_be_excluded_qm);
		  }
		  name_or_names = 
			  get_lookup_slot_value_given_default(entity,
			  Qname_or_names_for_frame,Nil);
		  cp_list = Nil;
		  cp_list_tail = Nil;
		  if (name_or_names) {
		      names_sic = name_or_names;
		      name = Nil;
		    next_loop_1:
		      name = CONSP(names_sic) ? CAR(names_sic) : names_sic;
		      if ( !TRUEP(name))
			  goto end_loop_1;
		      names_sic_1 = lookup_kb_specific_property_value(name,
			      Frame_or_frames_with_this_name_kbprop);
		      frame = Nil;
		    next_loop_2:
		      frame = CONSP(names_sic_1) ? CAR(names_sic_1) : 
			      names_sic_1;
		      if ( !TRUEP(frame))
			  goto end_loop_2;
		      sub_class_bit_vector = ISVREF(ISVREF(frame,
			      (SI_Long)1L),(SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(Connection_post_class_description,
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
		      if (temp ?  !TRUEP(memq_function(frame,cp_list)) : 
			      TRUEP(Nil)) {
			  gensymed_symbol_3 = frame;
			  gensymed_symbol_3 = 
				  gensym_cons_1(gensymed_symbol_3,Nil);
			  if (cp_list) {
			      if ( !TRUEP(cp_list_tail))
				  cp_list_tail = last(cp_list,_);
			      M_CDR(cp_list_tail) = gensymed_symbol_3;
			  }
			  else
			      cp_list = gensymed_symbol_3;
			  cp_list_tail = gensymed_symbol_3;
		      }
		      names_sic_1 = CONSP(names_sic_1) ? CDR(names_sic_1) :
			       Nil;
		      goto next_loop_2;
		    end_loop_2:;
		      names_sic = CONSP(names_sic) ? CDR(names_sic) : Nil;
		      goto next_loop_1;
		    end_loop_1:;
		  }
		  else
		      cp_list = gensym_cons_1(entity,Nil);
		  cp = Nil;
		  ab_loop_list_ = cp_list;
		next_loop_3:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_3;
		  cp = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  superior_connection_and_end = 
			  get_lookup_slot_value_given_default(cp,
			  Qsuperior_connection_cache,Nil);
		  temp_1 = cp;
		  temp_2 = directionality_qm;
		  if (temp_2);
		  else
		      temp_2 = Nil;
		  search_from_origin_entity(temp_1,class_1,temp_2,
			  also_get_port_and_direction_info_qm,
			  required_connection_directionality_for_inverse_role_service_qm,
			  do_not_stop_search_at_connections_qm,
			  original_port_name_qm,
			  original_port_directionality_qm);
		  if (superior_connection_and_end &&  
			  !TRUEP(original_port_name_qm)) {
		      superior_connection = CDR(superior_connection_and_end);
		      superior_connection_frame = Nil;
		      connection_end = CAR(superior_connection_and_end);
		      required_direction_qm = original_port_directionality_qm;
		      if (required_direction_qm);
		      else {
			  required_direction_qm = directionality_qm;
			  if (required_direction_qm);
			  else
			      required_direction_qm = Nil;
		      }
		      direction_to_try = Qinput;
		      superior_connection_frame = 
			      ISVREF(superior_connection,(SI_Long)1L);
		    next_loop_4:
		      if ( !TRUEP(original_port_directionality_qm) && 
			      ((SI_Long)0L != 
			      (IFIX(ISVREF(superior_connection,
			      (SI_Long)7L)) & (SI_Long)1L) ||  
			      !TRUEP(required_direction_qm)) || ( 
			      !TRUEP(original_port_directionality_qm) ||  
			      !((SI_Long)0L != 
			      (IFIX(ISVREF(superior_connection,
			      (SI_Long)7L)) & (SI_Long)1L))) && 
			      EQ(required_direction_qm,direction_to_try) 
			      && (EQ(direction_to_try,Qinput) ? 
			      EQ(connection_end,Qoutput) : 
			      EQ(connection_end,Qinput))) {
			  if (SIMPLE_VECTOR_P(superior_connection_frame) 
				  && 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(superior_connection_frame)) 
				  > (SI_Long)2L &&  
				  !EQ(ISVREF(superior_connection_frame,
				  (SI_Long)1L),Qavailable_frame_vector)) {
			      x2 = ISVREF(superior_connection_frame,
				      (SI_Long)1L);
			      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				      (SI_Long)0L),
				      Qg2_defstruct_structure_name_class_description_g2_struct) 
				      ? TRUEP(x2) : TRUEP(Qnil);
			  }
			  else
			      temp = TRUEP(Nil);
			  temp =  !(temp ? 
				  TRUEP(ISVREF(ISVREF(superior_connection_frame,
				  (SI_Long)1L),(SI_Long)16L)) : TRUEP(Nil));
			  if (temp);
			  else
			      temp = 
				      TRUEP(serve_item_p(superior_connection_frame));
		      }
		      else
			  temp = TRUEP(Nil);
		      if (temp)
			  search_for_directly_connected_entities_for_connection(EQ(direction_to_try,
				  Qinput) ? ISVREF(superior_connection,
				  (SI_Long)2L) : 
				  ISVREF(superior_connection,(SI_Long)3L),
				  class_1,superior_connection,
				  required_direction_qm,
				  also_get_port_and_direction_info_qm,Nil,
				  required_connection_directionality_for_inverse_role_service_qm,
				  do_not_stop_search_at_connections_qm);
		      if (EQ(direction_to_try,Qoutput))
			  goto end_loop_4;
		      superior_connection_frame = 
			      ISVREF(superior_connection,(SI_Long)1L);
		      direction_to_try = Qoutput;
		      goto next_loop_4;
		    end_loop_4:;
		  }
		  goto next_loop_3;
		end_loop_3:;
		  reclaim_gensym_list_1(cp_list);
	      }
	      else
		  search_from_origin_entity(entity,class_1,
			  directionality_qm,
			  also_get_port_and_direction_info_qm,
			  required_connection_directionality_for_inverse_role_service_qm,
			  do_not_stop_search_at_connections_qm,
			  original_port_name_qm,
			  original_port_directionality_qm);
	      Entities_or_triples_found_in_search = 
		      delete_item_from_list_and_reclaim_cons_cells(Entities_or_triples_found_in_search,
		      entity,Qreclaim_eval_cons_function,T);
	      SAVE_VALUES(VALUES_1(Entities_or_triples_found_in_search));
	      clear_connections_to_be_excluded(Connections_to_be_excluded_qm);
	      clear_entities_to_be_excluded(Entities_to_be_excluded_qm);
	      result = RESTORE_VALUES();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	RESTORE_STACK();
	return result;
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Do_not_stop_search_once_found_qm, Qdo_not_stop_search_once_found_qm);

/* SEARCH-FOR-DIRECTLY-CONNECTED-ENTITIES-REC */
Object search_for_directly_connected_entities_rec(entity,class_1,
	    directionality_qm,also_get_port_and_direction_info_qm,
	    required_connection_directionality_for_inverse_role_service_qm,
	    do_not_stop_search_at_connections_qm)
    Object entity, class_1, directionality_qm;
    Object also_get_port_and_direction_info_qm;
    Object required_connection_directionality_for_inverse_role_service_qm;
    Object do_not_stop_search_at_connections_qm;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, connection_frame_1, temp;
    Object ab_less_than_branch_qm_, x2, do_not_stop_search_once_found_qm;
    char temp_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(149,107);
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(entity,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)6L)) : Nil;
    ab_skip_list_form_ = gensymed_symbol;
    ab_skip_list_p_ = Nil;
    ab_next_node_ = Nil;
    ab_tail_node_ = Nil;
    ab_current_alist_ = Nil;
    ab_entry_cons_ = Nil;
    ab_connection_ = Nil;
    ab_connection_item_ = Nil;
    connection = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,1);
      connection_frame_1 = Nil;
      gensymed_symbol = CDR(ab_skip_list_form_);
      if (CONSP(gensymed_symbol)) {
	  temp = M_CAR(gensymed_symbol);
	  temp_1 = SIMPLE_VECTOR_P(temp);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  temp = M_CDR(gensymed_symbol);
	  ab_skip_list_p_ = SIMPLE_VECTOR_P(temp) ? T : Nil;
      }
      else
	  ab_skip_list_p_ = Nil;
      if (ab_skip_list_p_) {
	  ab_next_node_ = 
		  ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
		  (SI_Long)0L),(SI_Long)0L));
	  ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
	  if (EQ(ab_next_node_,ab_tail_node_))
	      ab_next_node_ = Nil;
      }
      else
	  ab_next_node_ = CDR(ab_skip_list_form_);
    next_loop:
    next_loop_1:
      if (ab_current_alist_) {
	  ab_entry_cons_ = M_CAR(ab_current_alist_);
	  ab_connection_ = M_CAR(ab_entry_cons_);
	  ab_connection_item_ = M_CDR(ab_entry_cons_);
	  ab_current_alist_ = M_CDR(ab_current_alist_);
      }
      else if (ab_skip_list_p_) {
	  if (ab_next_node_) {
	      ab_current_node_ = ab_next_node_;
	      ab_next_node_ = 
		      ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node_,
		      (SI_Long)0L),(SI_Long)0L));
	      if (EQ(ab_next_node_,ab_tail_node_))
		  ab_next_node_ = Nil;
	      ab_connection_ = ISVREF(ab_current_node_,(SI_Long)2L);
	      ab_connection_item_ = ISVREF(ab_current_node_,(SI_Long)3L);
	  }
	  else
	      ab_current_node_ = Nil;
      }
      else {
	  if (ab_next_node_) {
	      ab_current_node_ = ab_next_node_;
	      ab_less_than_branch_qm_ = Nil;
	    next_loop_2:
	      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
	      if ( !TRUEP(ab_less_than_branch_qm_))
		  goto end_loop;
	      ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
	      ab_current_node_ = ab_less_than_branch_qm_;
	      goto next_loop_2;
	    end_loop:;
	  }
	  else if (ab_node_stack_) {
	      ab_next_node_ = ab_node_stack_;
	      ab_current_node_ = M_CAR(ab_node_stack_);
	      ab_node_stack_ = M_CDR(ab_node_stack_);
	  }
	  else
	      ab_current_node_ = Nil;
	  if (ab_current_node_) {
	      ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
	      ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
	      ab_entry_cons_ = M_CAR(ab_current_alist_);
	      ab_connection_ = M_CAR(ab_entry_cons_);
	      ab_connection_item_ = M_CDR(ab_entry_cons_);
	      ab_current_alist_ = M_CDR(ab_current_alist_);
	  }
      }
      if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_)
	  goto end_1;
      goto next_loop_1;
    end_loop_1:
    end_1:
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_2;
      connection = ab_connection_;
      connection_frame_1 = ISVREF(connection,(SI_Long)1L);
      if (SIMPLE_VECTOR_P(connection_frame_1) && 
	      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_1)) > 
	      (SI_Long)2L &&  !EQ(ISVREF(connection_frame_1,(SI_Long)1L),
	      Qavailable_frame_vector)) {
	  x2 = ISVREF(connection_frame_1,(SI_Long)1L);
	  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		  Qg2_defstruct_structure_name_class_description_g2_struct) 
		  ? TRUEP(x2) : TRUEP(Qnil);
      }
      else
	  temp_1 = TRUEP(Nil);
      temp_1 =  !(temp_1 ? TRUEP(ISVREF(ISVREF(connection_frame_1,
	      (SI_Long)1L),(SI_Long)16L)) : TRUEP(Nil));
      if (temp_1);
      else
	  temp_1 = TRUEP(serve_item_p(connection_frame_1));
      if (temp_1) {
	  do_not_stop_search_once_found_qm = T;
	  PUSH_SPECIAL_WITH_SYMBOL(Do_not_stop_search_once_found_qm,Qdo_not_stop_search_once_found_qm,do_not_stop_search_once_found_qm,
		  0);
	    search_for_directly_connected_entities_for_connection(entity,
		    class_1,connection,directionality_qm,
		    also_get_port_and_direction_info_qm,Nil,
		    required_connection_directionality_for_inverse_role_service_qm,
		    do_not_stop_search_at_connections_qm);
	    if ( !TRUEP(Do_not_stop_search_once_found_qm)) {
		POP_SPECIAL();
		goto end_loop_2;
	    }
	  POP_SPECIAL();
      }
      goto next_loop;
    end_loop_2:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object Qsave_path;          /* save-path */

/* SEARCH-FOR-DIRECTLY-CONNECTED-ENTITIES-FOR-CONNECTION */
Object search_for_directly_connected_entities_for_connection(entity,
	    class_1,connection,directionality_qm,
	    also_get_port_and_direction_info_qm,
	    connection_frame_to_ignore_qm,
	    required_connection_directionality_for_inverse_role_service_qm,
	    do_not_stop_search_at_connections_qm)
    Object entity, class_1, connection, directionality_qm;
    Object also_get_port_and_direction_info_qm, connection_frame_to_ignore_qm;
    Object required_connection_directionality_for_inverse_role_service_qm;
    Object do_not_stop_search_at_connections_qm;
{
    Object temp, eval_pop_store, cons_1, next_cons, temp_1, svref_arg_2;

    x_note_fn_call(149,108);
    if (EQ(do_not_stop_search_at_connections_qm,Qsave_path)) {
	temp = 
		get_or_make_connection_frame_and_activate_if_appropriate(connection);
	Current_connection_path = eval_cons_1(temp,Current_connection_path);
	search_for_directly_connected_entities_for_connection_1(entity,
		class_1,connection,directionality_qm,
		also_get_port_and_direction_info_qm,
		connection_frame_to_ignore_qm,
		required_connection_directionality_for_inverse_role_service_qm,
		do_not_stop_search_at_connections_qm);
	eval_pop_store = Nil;
	cons_1 = Current_connection_path;
	if (cons_1) {
	    eval_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qeval);
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = cons_1;
		temp_1 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = cons_1;
	    }
	    else {
		temp_1 = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = cons_1;
		temp_1 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	Current_connection_path = next_cons;
	return VALUES_1(eval_pop_store);
    }
    else
	return search_for_directly_connected_entities_for_connection_1(entity,
		class_1,connection,directionality_qm,
		also_get_port_and_direction_info_qm,
		connection_frame_to_ignore_qm,
		required_connection_directionality_for_inverse_role_service_qm,
		do_not_stop_search_at_connections_qm);
}

/* SEARCH-FOR-DIRECTLY-CONNECTED-ENTITIES-FOR-CONNECTION-1 */
Object search_for_directly_connected_entities_for_connection_1(entity,
	    class_1,connection,directionality_qm,
	    also_get_port_and_direction_info_qm,
	    connection_frame_to_ignore_qm,
	    required_connection_directionality_for_inverse_role_service_qm,
	    do_not_stop_search_at_connections_qm)
    Object entity, class_1, connection, directionality_qm;
    Object also_get_port_and_direction_info_qm, connection_frame_to_ignore_qm;
    Object required_connection_directionality_for_inverse_role_service_qm;
    Object do_not_stop_search_at_connections_qm;
{
    Object gensymed_symbol, gensymed_symbol_1, new_cons, svref_arg_1;
    Object svref_arg_2, svref_new_value, gensymed_symbol_2, x, x2;
    Object entity_at_other_end, class_of_entity_at_other_end;
    Object connection_frame_or_class, connection_class, directionality, symbol;
    Object property_name, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_1, temp_2, entry_hash, tail, head;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, sub_class_bit_vector, connection_frame_1;
    Object transparent_class, ab_loop_list_, ab_loop_it_, name_or_names;
    Object cp_list, cp_list_tail, names_sic, name, names_sic_1, frame, cp;
    Object superior_connection_and_end, superior_connection;
    Object superior_connection_frame, connection_end, required_direction_qm;
    Object direction_to_try;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    SI_Long svref_new_value_1;
    char temp;
    Object result;

    x_note_fn_call(149,109);
    if ( !((SI_Long)0L != (IFIX(ISVREF(entity,(SI_Long)5L)) & 
		(SI_Long)512L))) {
	if (Note_things_encountered_during_role_service_qm) {
	    gensymed_symbol = Things_that_affect_this_formula;
	    gensymed_symbol_1 = entity;
	    if ( !TRUEP(memq_function(gensymed_symbol_1,gensymed_symbol))) {
		new_cons = ISVREF(Available_eval_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    svref_arg_1 = Available_eval_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
			    IFIX(Current_thread_index)))) {
			svref_arg_1 = Available_eval_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(svref_arg_1,svref_arg_2) = Nil;
		    }
		    gensymed_symbol_2 = new_cons;
		}
		else
		    gensymed_symbol_2 = Nil;
		if ( !TRUEP(gensymed_symbol_2))
		    gensymed_symbol_2 = replenish_eval_cons_pool();
		M_CAR(gensymed_symbol_2) = gensymed_symbol_1;
		M_CDR(gensymed_symbol_2) = gensymed_symbol;
		inline_note_allocate_cons(gensymed_symbol_2,Qeval);
		Things_that_affect_this_formula = gensymed_symbol_2;
	    }
	}
	temp = TRUEP(T);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	if (Note_things_encountered_during_role_service_qm) {
	    gensymed_symbol = Things_that_affect_this_formula;
	    gensymed_symbol_1 = connection;
	    if ( !TRUEP(memq_function(gensymed_symbol_1,gensymed_symbol))) {
		new_cons = ISVREF(Available_eval_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    svref_arg_1 = Available_eval_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
			    IFIX(Current_thread_index)))) {
			svref_arg_1 = Available_eval_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(svref_arg_1,svref_arg_2) = Nil;
		    }
		    gensymed_symbol_2 = new_cons;
		}
		else
		    gensymed_symbol_2 = Nil;
		if ( !TRUEP(gensymed_symbol_2))
		    gensymed_symbol_2 = replenish_eval_cons_pool();
		M_CAR(gensymed_symbol_2) = gensymed_symbol_1;
		M_CDR(gensymed_symbol_2) = gensymed_symbol;
		inline_note_allocate_cons(gensymed_symbol_2,Qeval);
		Things_that_affect_this_formula = gensymed_symbol_2;
	    }
	}
	if ( !((SI_Long)0L != (IFIX(ISVREF(connection,(SI_Long)7L)) & 
		(SI_Long)512L))) {
	    x = get_block_at_other_end_of_connection(connection,entity);
	    if (SIMPLE_VECTOR_P(x) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(x,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(x,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    entity_at_other_end = 
		    get_block_at_other_end_of_connection(connection,entity);
	    class_of_entity_at_other_end = 
		    ISVREF(ISVREF(entity_at_other_end,(SI_Long)1L),
		    (SI_Long)1L);
	    connection_frame_or_class = ISVREF(connection,(SI_Long)1L);
	    if (SIMPLE_VECTOR_P(connection_frame_or_class) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_or_class)) 
		    > (SI_Long)2L &&  !EQ(ISVREF(connection_frame_or_class,
		    (SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(connection_frame_or_class,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    connection_class = temp ? 
		    ISVREF(ISVREF(connection_frame_or_class,(SI_Long)1L),
		    (SI_Long)1L) : connection_frame_or_class;
	    directionality = Nil;
	    if ( !((SI_Long)0L != (IFIX(ISVREF(entity_at_other_end,
		    (SI_Long)5L)) & (SI_Long)1048576L))) {
		temp = (SI_Long)0L != (IFIX(ISVREF(connection,
			(SI_Long)7L)) & (SI_Long)1L);
		if (temp);
		else if (directionality_qm)
		    temp = EQ(directionality_qm,Qinput) ? 
			    EQ(ISVREF(connection,(SI_Long)2L),entity) : 
			    EQ(ISVREF(connection,(SI_Long)3L),entity);
		else {
		    directionality = EQ(ISVREF(connection,(SI_Long)2L),
			    entity) ? Qinput : Qoutput;
		    temp = TRUEP(T);
		}
		if (temp) {
		    symbol = ISVREF(ISVREF(entity,(SI_Long)1L),(SI_Long)1L);
		    property_name = Class_description_gkbprop;
		    skip_list = CDR(Symbol_properties_table);
		    key_value = symbol;
		    key_hash_value = SXHASH_SYMBOL_1(symbol) & 
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
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_1:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_2:
		    if ( !TRUEP(marked))
			goto end_loop_1;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		    goto next_loop_2;
		  end_loop_1:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
		    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if ( !TRUEP(gensymed_symbol)) {
			gensymed_symbol = symbol;
			temp_1 = Symbol_properties_table;
			temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
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
			    if ( 
				    !TRUEP(ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index)))) {
				svref_arg_1 = 
					Available_lookup_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(svref_arg_1,svref_arg_2) = Nil;
			    }
			    gensymed_symbol_1 = new_cons;
			}
			else
			    gensymed_symbol_1 = Nil;
			if ( !TRUEP(gensymed_symbol_1))
			    gensymed_symbol_1 = replenish_lookup_cons_pool();
			M_CAR(gensymed_symbol_1) = 
				Qsymbol_properties_hash_table;
			new_cons = ISVREF(Available_lookup_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    svref_arg_1 = Available_lookup_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index)))) {
				svref_arg_1 = 
					Available_lookup_conses_tail_vector;
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
			gensymed_symbol = set_skip_list_entry(temp_1,
				FIX((SI_Long)31L),Qeq,Nil,T,
				gensymed_symbol,temp_2,gensymed_symbol_1);
		    }
		    global_properties = gensymed_symbol;
		    skip_list = CDR(global_properties);
		    key_value = 
			    Current_kb_specific_property_list_property_name;
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
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_4:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_5:
		    if ( !TRUEP(marked))
			goto end_loop_4;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		    goto next_loop_5;
		  end_loop_4:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
		    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (kb_properties);
		    else
			kb_properties = Nil;
		    if (kb_properties) {
			skip_list = CDR(kb_properties);
			key_value = property_name;
			key_hash_value = SXHASH_SYMBOL_1(property_name) & 
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
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_7:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
		      next_loop_8:
			if ( !TRUEP(marked))
			    goto end_loop_7;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
			goto next_loop_8;
		      end_loop_7:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
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
			key_value = property_name;
			key_hash_value = SXHASH_SYMBOL_1(property_name) & 
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
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_10:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
		      next_loop_11:
			if ( !TRUEP(marked))
			    goto end_loop_10;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
			goto next_loop_11;
		      end_loop_10:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
			if (resulting_value);
			else
			    resulting_value = Nil;
		    }
		    gensymed_symbol = resulting_value;
		    if (gensymed_symbol) {
			sub_class_bit_vector = ISVREF(gensymed_symbol,
				(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Default_junction_class_description,
				(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol_3 = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_4 = (SI_Long)1L;
			    gensymed_symbol_5 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_4 = gensymed_symbol_4 << 
				    gensymed_symbol_5;
			    gensymed_symbol_3 = gensymed_symbol_3 & 
				    gensymed_symbol_4;
			    temp = (SI_Long)0L < gensymed_symbol_3;
			}
			else
			    temp = TRUEP(Nil);
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp) {
			skip_list = CDR(Symbol_properties_table);
			key_value = class_1;
			key_hash_value = SXHASH_SYMBOL_1(class_1) & 
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
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_13:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
		      next_loop_14:
			if ( !TRUEP(marked))
			    goto end_loop_13;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
			goto next_loop_14;
		      end_loop_13:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
			if ( !TRUEP(gensymed_symbol)) {
			    gensymed_symbol = class_1;
			    temp_1 = Symbol_properties_table;
			    temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) 
				    & IFIX(Most_positive_fixnum));
			    tail = 
				    make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
				    Nil);
			    head = 
				    make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
				    tail);
			    new_cons = 
				    ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index));
			    if (new_cons) {
				svref_arg_1 = Available_lookup_conses_vector;
				svref_arg_2 = Current_thread_index;
				svref_new_value = M_CDR(new_cons);
				SVREF(svref_arg_1,svref_arg_2) = 
					svref_new_value;
				if ( 
					!TRUEP(ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index)))) {
				    svref_arg_1 = 
					    Available_lookup_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(svref_arg_1,svref_arg_2) = Nil;
				}
				gensymed_symbol_1 = new_cons;
			    }
			    else
				gensymed_symbol_1 = Nil;
			    if ( !TRUEP(gensymed_symbol_1))
				gensymed_symbol_1 = 
					replenish_lookup_cons_pool();
			    M_CAR(gensymed_symbol_1) = 
				    Qsymbol_properties_hash_table;
			    new_cons = 
				    ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index));
			    if (new_cons) {
				svref_arg_1 = Available_lookup_conses_vector;
				svref_arg_2 = Current_thread_index;
				svref_new_value = M_CDR(new_cons);
				SVREF(svref_arg_1,svref_arg_2) = 
					svref_new_value;
				if ( 
					!TRUEP(ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index)))) {
				    svref_arg_1 = 
					    Available_lookup_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(svref_arg_1,svref_arg_2) = Nil;
				}
				gensymed_symbol_2 = new_cons;
			    }
			    else
				gensymed_symbol_2 = Nil;
			    if ( !TRUEP(gensymed_symbol_2))
				gensymed_symbol_2 = 
					replenish_lookup_cons_pool();
			    M_CAR(gensymed_symbol_2) = head;
			    M_CDR(gensymed_symbol_2) = tail;
			    inline_note_allocate_cons(gensymed_symbol_2,
				    Qlookup);
			    M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
			    inline_note_allocate_cons(gensymed_symbol_1,
				    Qlookup);
			    gensymed_symbol = set_skip_list_entry(temp_1,
				    FIX((SI_Long)31L),Qeq,Nil,T,
				    gensymed_symbol,temp_2,gensymed_symbol_1);
			}
			global_properties = gensymed_symbol;
			skip_list = CDR(global_properties);
			key_value = 
				Current_kb_specific_property_list_property_name;
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
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_16:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
		      next_loop_17:
			if ( !TRUEP(marked))
			    goto end_loop_16;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
			goto next_loop_17;
		      end_loop_16:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
				key_hash_value ? (EQ(key_value,ISVREF(curr,
				(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
				Nil) : Nil;
			if (kb_properties);
			else
			    kb_properties = Nil;
			if (kb_properties) {
			    skip_list = CDR(kb_properties);
			    key_value = Class_description_gkbprop;
			    key_hash_value = 
				    SXHASH_SYMBOL_1(Class_description_gkbprop) 
				    & IFIX(Most_positive_fixnum);
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
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_19:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp_2 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp_2);
			    MVS_2(result,succ,marked);
			  next_loop_20:
			    if ( !TRUEP(marked))
				goto end_loop_19;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp_2 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp_2);
			    MVS_2(result,succ,marked);
			    goto next_loop_20;
			  end_loop_19:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			    kb_specific_value = IFIX(ISVREF(curr,
				    (SI_Long)1L)) == key_hash_value ? 
				    (EQ(key_value,ISVREF(curr,
				    (SI_Long)2L)) ? ISVREF(curr,
				    (SI_Long)3L) : Nil) : Nil;
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
				    SXHASH_SYMBOL_1(Class_description_gkbprop) 
				    & IFIX(Most_positive_fixnum);
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
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_22:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp_2 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp_2);
			    MVS_2(result,succ,marked);
			  next_loop_23:
			    if ( !TRUEP(marked))
				goto end_loop_22;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp_2 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp_2);
			    MVS_2(result,succ,marked);
			    goto next_loop_23;
			  end_loop_22:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			    resulting_value = IFIX(ISVREF(curr,
				    (SI_Long)1L)) == key_hash_value ? 
				    (EQ(key_value,ISVREF(curr,
				    (SI_Long)2L)) ? ISVREF(curr,
				    (SI_Long)3L) : Nil) : Nil;
			    if (resulting_value);
			    else
				resulting_value = Nil;
			}
			gensymed_symbol = resulting_value;
			if (gensymed_symbol) {
			    sub_class_bit_vector = ISVREF(gensymed_symbol,
				    (SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(Default_junction_class_description,
				    (SI_Long)18L));
			    sub_class_vector_index = 
				    superior_class_bit_number >>  -  - 
				    (SI_Long)3L;
			    if (sub_class_vector_index < 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					{
				gensymed_symbol_3 = 
					UBYTE_8_ISAREF_1(sub_class_bit_vector,
					sub_class_vector_index);
				gensymed_symbol_4 = (SI_Long)1L;
				gensymed_symbol_5 = 
					superior_class_bit_number & 
					(SI_Long)7L;
				gensymed_symbol_4 = gensymed_symbol_4 << 
					gensymed_symbol_5;
				gensymed_symbol_3 = gensymed_symbol_3 & 
					gensymed_symbol_4;
				temp = (SI_Long)0L < gensymed_symbol_3;
			    }
			    else
				temp = TRUEP(Nil);
			}
			else
			    temp = TRUEP(Nil);
			temp =  !temp;
			if (temp);
			else {
			    gensymed_symbol = 
				    lookup_global_or_kb_specific_property_value(ISVREF(ISVREF(entity,
				    (SI_Long)1L),(SI_Long)1L),
				    Class_description_gkbprop);
			    temp =  !(gensymed_symbol ? 
				    TRUEP(memq_function(class_1,
				    ISVREF(gensymed_symbol,(SI_Long)2L))) :
				     TRUEP(Nil));
			}
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp) {
			if ( !((SI_Long)0L != (IFIX(ISVREF(entity,
				(SI_Long)5L)) & (SI_Long)1048576L))) {
			    svref_new_value_1 = IFIX(ISVREF(entity,
				    (SI_Long)5L)) | (SI_Long)1048576L;
			    ISVREF(entity,(SI_Long)5L) = 
				    FIX(svref_new_value_1);
			    Entities_to_be_excluded_qm = 
				    eval_cons_1(entity,
				    Entities_to_be_excluded_qm);
			    svref_new_value_1 = IFIX(ISVREF(connection,
				    (SI_Long)7L)) | (SI_Long)512L;
			    ISVREF(connection,(SI_Long)7L) = 
				    FIX(svref_new_value_1);
			    Connections_to_be_excluded_qm = 
				    eval_cons_1(connection,
				    Connections_to_be_excluded_qm);
			    temp_2 = directionality_qm;
			    if (temp_2);
			    else
				temp_2 = directionality;
			    search_for_directly_connected_entities_rec(entity,
				    class_1,temp_2,
				    also_get_port_and_direction_info_qm,
				    required_connection_directionality_for_inverse_role_service_qm,
				    do_not_stop_search_at_connections_qm);
			}
		    }
		    gensymed_symbol = 
			    lookup_global_or_kb_specific_property_value(connection_class,
			    Class_description_gkbprop);
		    if ((gensymed_symbol ? TRUEP(memq_function(class_1,
			    ISVREF(gensymed_symbol,(SI_Long)2L))) : 
			    TRUEP(Nil)) ?  !EQ(ISVREF(connection,
			    (SI_Long)1L),connection_frame_to_ignore_qm) : 
			    TRUEP(Nil)) {
			if (EQ(required_connection_directionality_for_inverse_role_service_qm,
				Qoutput))
			    temp = EQ(ISVREF(connection,(SI_Long)3L),entity);
			else if (EQ(required_connection_directionality_for_inverse_role_service_qm,
				Qinput))
			    temp = EQ(ISVREF(connection,(SI_Long)2L),entity);
			else
			    temp = TRUEP(T);
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp) {
			connection_frame_1 = 
				get_or_make_connection_frame_and_activate_if_appropriate(connection);
			if ( !((SI_Long)0L != 
				(IFIX(ISVREF(connection_frame_1,
				(SI_Long)5L)) & (SI_Long)512L))) {
			    if (Note_things_encountered_during_role_service_qm) 
					{
				gensymed_symbol = 
					Things_that_affect_this_formula;
				gensymed_symbol_1 = connection_frame_1;
				if ( 
					!TRUEP(memq_function(gensymed_symbol_1,
					gensymed_symbol))) {
				    new_cons = 
					    ISVREF(Available_eval_conses_vector,
					    IFIX(Current_thread_index));
				    if (new_cons) {
					svref_arg_1 = 
						Available_eval_conses_vector;
					svref_arg_2 = Current_thread_index;
					svref_new_value = M_CDR(new_cons);
					SVREF(svref_arg_1,svref_arg_2) = 
						svref_new_value;
					if ( 
						!TRUEP(ISVREF(Available_eval_conses_vector,
						IFIX(Current_thread_index)))) {
					    svref_arg_1 = 
						    Available_eval_conses_tail_vector;
					    svref_arg_2 = Current_thread_index;
					    SVREF(svref_arg_1,svref_arg_2) 
						    = Nil;
					}
					gensymed_symbol_2 = new_cons;
				    }
				    else
					gensymed_symbol_2 = Nil;
				    if ( !TRUEP(gensymed_symbol_2))
					gensymed_symbol_2 = 
						replenish_eval_cons_pool();
				    M_CAR(gensymed_symbol_2) = 
					    gensymed_symbol_1;
				    M_CDR(gensymed_symbol_2) = gensymed_symbol;
				    inline_note_allocate_cons(gensymed_symbol_2,
					    Qeval);
				    Things_that_affect_this_formula = 
					    gensymed_symbol_2;
				}
			    }
			    temp = TRUEP(T);
			}
			else
			    temp = TRUEP(Nil);
			if (temp) {
			    Entities_or_triples_found_in_search = 
				    eval_cons_1(also_get_port_and_direction_info_qm 
				    ? eval_list_3(connection_frame_1,Nil,
				    Nil) : connection_frame_1,
				    Entities_or_triples_found_in_search);
			    svref_new_value_1 = IFIX(ISVREF(connection,
				    (SI_Long)7L)) | (SI_Long)512L;
			    ISVREF(connection,(SI_Long)7L) = 
				    FIX(svref_new_value_1);
			    Connections_to_be_excluded_qm = 
				    eval_cons_1(connection,
				    Connections_to_be_excluded_qm);
			    if (do_not_stop_search_at_connections_qm) {
				transparent_class = Nil;
				ab_loop_list_ = 
					Transparent_classes_for_schematic_search;
				ab_loop_it_ = Nil;
			      next_loop_24:
				if ( !TRUEP(ab_loop_list_))
				    goto end_loop_24;
				transparent_class = M_CAR(ab_loop_list_);
				ab_loop_list_ = M_CDR(ab_loop_list_);
				gensymed_symbol = 
					lookup_global_or_kb_specific_property_value(class_of_entity_at_other_end,
					Class_description_gkbprop);
				ab_loop_it_ = gensymed_symbol ? 
					memq_function(transparent_class,
					ISVREF(gensymed_symbol,
					(SI_Long)2L)) : Nil;
				if (ab_loop_it_) {
				    temp = TRUEP(ab_loop_it_);
				    goto end_9;
				}
				goto next_loop_24;
			      end_loop_24:
				temp = TRUEP(Qnil);
			      end_9:;
				if (temp) {
				    svref_new_value_1 = 
					    IFIX(ISVREF(entity_at_other_end,
					    (SI_Long)5L)) | (SI_Long)1048576L;
				    ISVREF(entity_at_other_end,
					    (SI_Long)5L) = 
					    FIX(svref_new_value_1);
				    Entities_to_be_excluded_qm = 
					    eval_cons_1(entity_at_other_end,
					    Entities_to_be_excluded_qm);
				    svref_new_value_1 = 
					    IFIX(ISVREF(connection,
					    (SI_Long)7L)) | (SI_Long)512L;
				    ISVREF(connection,(SI_Long)7L) = 
					    FIX(svref_new_value_1);
				    Connections_to_be_excluded_qm = 
					    eval_cons_1(connection,
					    Connections_to_be_excluded_qm);
				    temp_2 = directionality_qm;
				    if (temp_2);
				    else
					temp_2 = directionality;
				    search_for_directly_connected_entities_rec(entity_at_other_end,
					    class_1,temp_2,
					    also_get_port_and_direction_info_qm,
					    required_connection_directionality_for_inverse_role_service_qm,
					    do_not_stop_search_at_connections_qm);
				}
			    }
			    else
				return VALUES_1(Nil);
			}
		    }
		    else if (memq_function(class_of_entity_at_other_end,
			    Classes_to_ignore_for_schematic_search));
		    else {
			skip_list = CDR(Symbol_properties_table);
			key_value = class_of_entity_at_other_end;
			key_hash_value = 
				SXHASH_SYMBOL_1(class_of_entity_at_other_end) 
				& IFIX(Most_positive_fixnum);
			bottom_level = (SI_Long)0L;
			marked = Nil;
			pred = M_CAR(skip_list);
			curr = Nil;
			succ = Nil;
			level = (SI_Long)31L;
			ab_loop_bind_ = bottom_level;
		      next_loop_25:
			if (level < ab_loop_bind_)
			    goto end_loop_25;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_26:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
		      next_loop_27:
			if ( !TRUEP(marked))
			    goto end_loop_26;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
			goto next_loop_27;
		      end_loop_26:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_10;
			goto next_loop_26;
		      end_loop_27:
		      end_10:
			level = level - (SI_Long)1L;
			goto next_loop_25;
		      end_loop_25:;
			gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
			if ( !TRUEP(gensymed_symbol)) {
			    gensymed_symbol = class_of_entity_at_other_end;
			    temp_1 = Symbol_properties_table;
			    temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) 
				    & IFIX(Most_positive_fixnum));
			    tail = 
				    make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
				    Nil);
			    head = 
				    make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
				    tail);
			    new_cons = 
				    ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index));
			    if (new_cons) {
				svref_arg_1 = Available_lookup_conses_vector;
				svref_arg_2 = Current_thread_index;
				svref_new_value = M_CDR(new_cons);
				SVREF(svref_arg_1,svref_arg_2) = 
					svref_new_value;
				if ( 
					!TRUEP(ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index)))) {
				    svref_arg_1 = 
					    Available_lookup_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(svref_arg_1,svref_arg_2) = Nil;
				}
				gensymed_symbol_1 = new_cons;
			    }
			    else
				gensymed_symbol_1 = Nil;
			    if ( !TRUEP(gensymed_symbol_1))
				gensymed_symbol_1 = 
					replenish_lookup_cons_pool();
			    M_CAR(gensymed_symbol_1) = 
				    Qsymbol_properties_hash_table;
			    new_cons = 
				    ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index));
			    if (new_cons) {
				svref_arg_1 = Available_lookup_conses_vector;
				svref_arg_2 = Current_thread_index;
				svref_new_value = M_CDR(new_cons);
				SVREF(svref_arg_1,svref_arg_2) = 
					svref_new_value;
				if ( 
					!TRUEP(ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index)))) {
				    svref_arg_1 = 
					    Available_lookup_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(svref_arg_1,svref_arg_2) = Nil;
				}
				gensymed_symbol_2 = new_cons;
			    }
			    else
				gensymed_symbol_2 = Nil;
			    if ( !TRUEP(gensymed_symbol_2))
				gensymed_symbol_2 = 
					replenish_lookup_cons_pool();
			    M_CAR(gensymed_symbol_2) = head;
			    M_CDR(gensymed_symbol_2) = tail;
			    inline_note_allocate_cons(gensymed_symbol_2,
				    Qlookup);
			    M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
			    inline_note_allocate_cons(gensymed_symbol_1,
				    Qlookup);
			    gensymed_symbol = set_skip_list_entry(temp_1,
				    FIX((SI_Long)31L),Qeq,Nil,T,
				    gensymed_symbol,temp_2,gensymed_symbol_1);
			}
			global_properties = gensymed_symbol;
			skip_list = CDR(global_properties);
			key_value = 
				Current_kb_specific_property_list_property_name;
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
		      next_loop_28:
			if (level < ab_loop_bind_)
			    goto end_loop_28;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_29:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
		      next_loop_30:
			if ( !TRUEP(marked))
			    goto end_loop_29;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
			goto next_loop_30;
		      end_loop_29:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_11;
			goto next_loop_29;
		      end_loop_30:
		      end_11:
			level = level - (SI_Long)1L;
			goto next_loop_28;
		      end_loop_28:;
			kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
				key_hash_value ? (EQ(key_value,ISVREF(curr,
				(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
				Nil) : Nil;
			if (kb_properties);
			else
			    kb_properties = Nil;
			if (kb_properties) {
			    skip_list = CDR(kb_properties);
			    key_value = Class_description_gkbprop;
			    key_hash_value = 
				    SXHASH_SYMBOL_1(Class_description_gkbprop) 
				    & IFIX(Most_positive_fixnum);
			    bottom_level = (SI_Long)0L;
			    marked = Nil;
			    pred = M_CAR(skip_list);
			    curr = Nil;
			    succ = Nil;
			    level = (SI_Long)31L;
			    ab_loop_bind_ = bottom_level;
			  next_loop_31:
			    if (level < ab_loop_bind_)
				goto end_loop_31;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_32:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp_2 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp_2);
			    MVS_2(result,succ,marked);
			  next_loop_33:
			    if ( !TRUEP(marked))
				goto end_loop_32;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp_2 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp_2);
			    MVS_2(result,succ,marked);
			    goto next_loop_33;
			  end_loop_32:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_12;
			    goto next_loop_32;
			  end_loop_33:
			  end_12:
			    level = level - (SI_Long)1L;
			    goto next_loop_31;
			  end_loop_31:;
			    kb_specific_value = IFIX(ISVREF(curr,
				    (SI_Long)1L)) == key_hash_value ? 
				    (EQ(key_value,ISVREF(curr,
				    (SI_Long)2L)) ? ISVREF(curr,
				    (SI_Long)3L) : Nil) : Nil;
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
				    SXHASH_SYMBOL_1(Class_description_gkbprop) 
				    & IFIX(Most_positive_fixnum);
			    bottom_level = (SI_Long)0L;
			    marked = Nil;
			    pred = M_CAR(skip_list);
			    curr = Nil;
			    succ = Nil;
			    level = (SI_Long)31L;
			    ab_loop_bind_ = bottom_level;
			  next_loop_34:
			    if (level < ab_loop_bind_)
				goto end_loop_34;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_35:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp_2 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp_2);
			    MVS_2(result,succ,marked);
			  next_loop_36:
			    if ( !TRUEP(marked))
				goto end_loop_35;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp_2 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp_2);
			    MVS_2(result,succ,marked);
			    goto next_loop_36;
			  end_loop_35:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_13;
			    goto next_loop_35;
			  end_loop_36:
			  end_13:
			    level = level - (SI_Long)1L;
			    goto next_loop_34;
			  end_loop_34:;
			    resulting_value = IFIX(ISVREF(curr,
				    (SI_Long)1L)) == key_hash_value ? 
				    (EQ(key_value,ISVREF(curr,
				    (SI_Long)2L)) ? ISVREF(curr,
				    (SI_Long)3L) : Nil) : Nil;
			    if (resulting_value);
			    else
				resulting_value = Nil;
			}
			gensymed_symbol = resulting_value;
			if (gensymed_symbol) {
			    sub_class_bit_vector = ISVREF(gensymed_symbol,
				    (SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(Connection_post_class_description,
				    (SI_Long)18L));
			    sub_class_vector_index = 
				    superior_class_bit_number >>  -  - 
				    (SI_Long)3L;
			    if (sub_class_vector_index < 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					{
				gensymed_symbol_3 = 
					UBYTE_8_ISAREF_1(sub_class_bit_vector,
					sub_class_vector_index);
				gensymed_symbol_4 = (SI_Long)1L;
				gensymed_symbol_5 = 
					superior_class_bit_number & 
					(SI_Long)7L;
				gensymed_symbol_4 = gensymed_symbol_4 << 
					gensymed_symbol_5;
				gensymed_symbol_3 = gensymed_symbol_3 & 
					gensymed_symbol_4;
				temp = (SI_Long)0L < gensymed_symbol_3;
			    }
			    else
				temp = TRUEP(Nil);
			}
			else
			    temp = TRUEP(Nil);
			if (temp) {
			    skip_list = CDR(Symbol_properties_table);
			    key_value = class_1;
			    key_hash_value = SXHASH_SYMBOL_1(class_1) & 
				    IFIX(Most_positive_fixnum);
			    bottom_level = (SI_Long)0L;
			    marked = Nil;
			    pred = M_CAR(skip_list);
			    curr = Nil;
			    succ = Nil;
			    level = (SI_Long)31L;
			    ab_loop_bind_ = bottom_level;
			  next_loop_37:
			    if (level < ab_loop_bind_)
				goto end_loop_37;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_38:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp_2 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp_2);
			    MVS_2(result,succ,marked);
			  next_loop_39:
			    if ( !TRUEP(marked))
				goto end_loop_38;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp_2 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp_2);
			    MVS_2(result,succ,marked);
			    goto next_loop_39;
			  end_loop_38:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_14;
			    goto next_loop_38;
			  end_loop_39:
			  end_14:
			    level = level - (SI_Long)1L;
			    goto next_loop_37;
			  end_loop_37:;
			    gensymed_symbol = IFIX(ISVREF(curr,
				    (SI_Long)1L)) == key_hash_value ? 
				    (EQ(key_value,ISVREF(curr,
				    (SI_Long)2L)) ? ISVREF(curr,
				    (SI_Long)3L) : Nil) : Nil;
			    if ( !TRUEP(gensymed_symbol)) {
				gensymed_symbol = class_1;
				temp_1 = Symbol_properties_table;
				temp_2 = 
					FIX(SXHASH_SYMBOL_1(gensymed_symbol) 
					& IFIX(Most_positive_fixnum));
				tail = 
					make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
					Nil);
				head = 
					make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
					tail);
				new_cons = 
					ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index));
				if (new_cons) {
				    svref_arg_1 = 
					    Available_lookup_conses_vector;
				    svref_arg_2 = Current_thread_index;
				    svref_new_value = M_CDR(new_cons);
				    SVREF(svref_arg_1,svref_arg_2) = 
					    svref_new_value;
				    if ( 
					    !TRUEP(ISVREF(Available_lookup_conses_vector,
					    IFIX(Current_thread_index)))) {
					svref_arg_1 = 
						Available_lookup_conses_tail_vector;
					svref_arg_2 = Current_thread_index;
					SVREF(svref_arg_1,svref_arg_2) = Nil;
				    }
				    gensymed_symbol_1 = new_cons;
				}
				else
				    gensymed_symbol_1 = Nil;
				if ( !TRUEP(gensymed_symbol_1))
				    gensymed_symbol_1 = 
					    replenish_lookup_cons_pool();
				M_CAR(gensymed_symbol_1) = 
					Qsymbol_properties_hash_table;
				new_cons = 
					ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index));
				if (new_cons) {
				    svref_arg_1 = 
					    Available_lookup_conses_vector;
				    svref_arg_2 = Current_thread_index;
				    svref_new_value = M_CDR(new_cons);
				    SVREF(svref_arg_1,svref_arg_2) = 
					    svref_new_value;
				    if ( 
					    !TRUEP(ISVREF(Available_lookup_conses_vector,
					    IFIX(Current_thread_index)))) {
					svref_arg_1 = 
						Available_lookup_conses_tail_vector;
					svref_arg_2 = Current_thread_index;
					SVREF(svref_arg_1,svref_arg_2) = Nil;
				    }
				    gensymed_symbol_2 = new_cons;
				}
				else
				    gensymed_symbol_2 = Nil;
				if ( !TRUEP(gensymed_symbol_2))
				    gensymed_symbol_2 = 
					    replenish_lookup_cons_pool();
				M_CAR(gensymed_symbol_2) = head;
				M_CDR(gensymed_symbol_2) = tail;
				inline_note_allocate_cons(gensymed_symbol_2,
					Qlookup);
				M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
				inline_note_allocate_cons(gensymed_symbol_1,
					Qlookup);
				gensymed_symbol = 
					set_skip_list_entry(temp_1,
					FIX((SI_Long)31L),Qeq,Nil,T,
					gensymed_symbol,temp_2,
					gensymed_symbol_1);
			    }
			    global_properties = gensymed_symbol;
			    skip_list = CDR(global_properties);
			    key_value = 
				    Current_kb_specific_property_list_property_name;
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
			  next_loop_40:
			    if (level < ab_loop_bind_)
				goto end_loop_40;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_41:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp_2 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp_2);
			    MVS_2(result,succ,marked);
			  next_loop_42:
			    if ( !TRUEP(marked))
				goto end_loop_41;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp_2 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp_2);
			    MVS_2(result,succ,marked);
			    goto next_loop_42;
			  end_loop_41:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_15;
			    goto next_loop_41;
			  end_loop_42:
			  end_15:
			    level = level - (SI_Long)1L;
			    goto next_loop_40;
			  end_loop_40:;
			    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) 
				    == key_hash_value ? (EQ(key_value,
				    ISVREF(curr,(SI_Long)2L)) ? 
				    ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
			    if (kb_properties);
			    else
				kb_properties = Nil;
			    if (kb_properties) {
				skip_list = CDR(kb_properties);
				key_value = Class_description_gkbprop;
				key_hash_value = 
					SXHASH_SYMBOL_1(Class_description_gkbprop) 
					& IFIX(Most_positive_fixnum);
				bottom_level = (SI_Long)0L;
				marked = Nil;
				pred = M_CAR(skip_list);
				curr = Nil;
				succ = Nil;
				level = (SI_Long)31L;
				ab_loop_bind_ = bottom_level;
			      next_loop_43:
				if (level < ab_loop_bind_)
				    goto end_loop_43;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_44:
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp_2 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp_2);
				MVS_2(result,succ,marked);
			      next_loop_45:
				if ( !TRUEP(marked))
				    goto end_loop_44;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp_2 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp_2);
				MVS_2(result,succ,marked);
				goto next_loop_45;
			      end_loop_44:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_16;
				goto next_loop_44;
			      end_loop_45:
			      end_16:
				level = level - (SI_Long)1L;
				goto next_loop_43;
			      end_loop_43:;
				kb_specific_value = IFIX(ISVREF(curr,
					(SI_Long)1L)) == key_hash_value ? 
					(EQ(key_value,ISVREF(curr,
					(SI_Long)2L)) ? ISVREF(curr,
					(SI_Long)3L) : Nil) : Nil;
				if (kb_specific_value);
				else
				    kb_specific_value = 
					    No_specific_property_value;
			    }
			    else
				kb_specific_value = No_specific_property_value;
			    if ( !EQ(kb_specific_value,
				    No_specific_property_value))
				resulting_value = kb_specific_value;
			    else {
				skip_list = CDR(global_properties);
				key_value = Class_description_gkbprop;
				key_hash_value = 
					SXHASH_SYMBOL_1(Class_description_gkbprop) 
					& IFIX(Most_positive_fixnum);
				bottom_level = (SI_Long)0L;
				marked = Nil;
				pred = M_CAR(skip_list);
				curr = Nil;
				succ = Nil;
				level = (SI_Long)31L;
				ab_loop_bind_ = bottom_level;
			      next_loop_46:
				if (level < ab_loop_bind_)
				    goto end_loop_46;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_47:
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp_2 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp_2);
				MVS_2(result,succ,marked);
			      next_loop_48:
				if ( !TRUEP(marked))
				    goto end_loop_47;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp_2 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp_2);
				MVS_2(result,succ,marked);
				goto next_loop_48;
			      end_loop_47:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_17;
				goto next_loop_47;
			      end_loop_48:
			      end_17:
				level = level - (SI_Long)1L;
				goto next_loop_46;
			      end_loop_46:;
				resulting_value = IFIX(ISVREF(curr,
					(SI_Long)1L)) == key_hash_value ? 
					(EQ(key_value,ISVREF(curr,
					(SI_Long)2L)) ? ISVREF(curr,
					(SI_Long)3L) : Nil) : Nil;
				if (resulting_value);
				else
				    resulting_value = Nil;
			    }
			    gensymed_symbol = resulting_value;
			    if (gensymed_symbol) {
				sub_class_bit_vector = 
					ISVREF(gensymed_symbol,(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(Connection_post_class_description,
					(SI_Long)18L));
				sub_class_vector_index = 
					superior_class_bit_number >>  -  - 
					(SI_Long)3L;
				if (sub_class_vector_index < 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					    {
				    gensymed_symbol_3 = 
					    UBYTE_8_ISAREF_1(sub_class_bit_vector,
					    sub_class_vector_index);
				    gensymed_symbol_4 = (SI_Long)1L;
				    gensymed_symbol_5 = 
					    superior_class_bit_number & 
					    (SI_Long)7L;
				    gensymed_symbol_4 = gensymed_symbol_4 
					    << gensymed_symbol_5;
				    gensymed_symbol_3 = gensymed_symbol_3 
					    & gensymed_symbol_4;
				    temp = (SI_Long)0L < gensymed_symbol_3;
				}
				else
				    temp = TRUEP(Nil);
			    }
			    else
				temp = TRUEP(Nil);
			    temp =  !temp;
			    if (temp);
			    else {
				gensymed_symbol = 
					lookup_global_or_kb_specific_property_value(class_of_entity_at_other_end,
					Class_description_gkbprop);
				temp =  !(gensymed_symbol ? 
					TRUEP(memq_function(class_1,
					ISVREF(gensymed_symbol,
					(SI_Long)2L))) : TRUEP(Nil));
			    }
			}
			else
			    temp = TRUEP(Nil);
			if (temp) {
			    skip_list = CDR(Symbol_properties_table);
			    key_value = class_1;
			    key_hash_value = SXHASH_SYMBOL_1(class_1) & 
				    IFIX(Most_positive_fixnum);
			    bottom_level = (SI_Long)0L;
			    marked = Nil;
			    pred = M_CAR(skip_list);
			    curr = Nil;
			    succ = Nil;
			    level = (SI_Long)31L;
			    ab_loop_bind_ = bottom_level;
			  next_loop_49:
			    if (level < ab_loop_bind_)
				goto end_loop_49;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_50:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp_2 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp_2);
			    MVS_2(result,succ,marked);
			  next_loop_51:
			    if ( !TRUEP(marked))
				goto end_loop_50;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp_2 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp_2);
			    MVS_2(result,succ,marked);
			    goto next_loop_51;
			  end_loop_50:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_18;
			    goto next_loop_50;
			  end_loop_51:
			  end_18:
			    level = level - (SI_Long)1L;
			    goto next_loop_49;
			  end_loop_49:;
			    gensymed_symbol = IFIX(ISVREF(curr,
				    (SI_Long)1L)) == key_hash_value ? 
				    (EQ(key_value,ISVREF(curr,
				    (SI_Long)2L)) ? ISVREF(curr,
				    (SI_Long)3L) : Nil) : Nil;
			    if ( !TRUEP(gensymed_symbol)) {
				gensymed_symbol = class_1;
				temp_1 = Symbol_properties_table;
				temp_2 = 
					FIX(SXHASH_SYMBOL_1(gensymed_symbol) 
					& IFIX(Most_positive_fixnum));
				tail = 
					make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
					Nil);
				head = 
					make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
					tail);
				new_cons = 
					ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index));
				if (new_cons) {
				    svref_arg_1 = 
					    Available_lookup_conses_vector;
				    svref_arg_2 = Current_thread_index;
				    svref_new_value = M_CDR(new_cons);
				    SVREF(svref_arg_1,svref_arg_2) = 
					    svref_new_value;
				    if ( 
					    !TRUEP(ISVREF(Available_lookup_conses_vector,
					    IFIX(Current_thread_index)))) {
					svref_arg_1 = 
						Available_lookup_conses_tail_vector;
					svref_arg_2 = Current_thread_index;
					SVREF(svref_arg_1,svref_arg_2) = Nil;
				    }
				    gensymed_symbol_1 = new_cons;
				}
				else
				    gensymed_symbol_1 = Nil;
				if ( !TRUEP(gensymed_symbol_1))
				    gensymed_symbol_1 = 
					    replenish_lookup_cons_pool();
				M_CAR(gensymed_symbol_1) = 
					Qsymbol_properties_hash_table;
				new_cons = 
					ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index));
				if (new_cons) {
				    svref_arg_1 = 
					    Available_lookup_conses_vector;
				    svref_arg_2 = Current_thread_index;
				    svref_new_value = M_CDR(new_cons);
				    SVREF(svref_arg_1,svref_arg_2) = 
					    svref_new_value;
				    if ( 
					    !TRUEP(ISVREF(Available_lookup_conses_vector,
					    IFIX(Current_thread_index)))) {
					svref_arg_1 = 
						Available_lookup_conses_tail_vector;
					svref_arg_2 = Current_thread_index;
					SVREF(svref_arg_1,svref_arg_2) = Nil;
				    }
				    gensymed_symbol_2 = new_cons;
				}
				else
				    gensymed_symbol_2 = Nil;
				if ( !TRUEP(gensymed_symbol_2))
				    gensymed_symbol_2 = 
					    replenish_lookup_cons_pool();
				M_CAR(gensymed_symbol_2) = head;
				M_CDR(gensymed_symbol_2) = tail;
				inline_note_allocate_cons(gensymed_symbol_2,
					Qlookup);
				M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
				inline_note_allocate_cons(gensymed_symbol_1,
					Qlookup);
				gensymed_symbol = 
					set_skip_list_entry(temp_1,
					FIX((SI_Long)31L),Qeq,Nil,T,
					gensymed_symbol,temp_2,
					gensymed_symbol_1);
			    }
			    global_properties = gensymed_symbol;
			    skip_list = CDR(global_properties);
			    key_value = 
				    Current_kb_specific_property_list_property_name;
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
			  next_loop_52:
			    if (level < ab_loop_bind_)
				goto end_loop_52;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_53:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp_2 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp_2);
			    MVS_2(result,succ,marked);
			  next_loop_54:
			    if ( !TRUEP(marked))
				goto end_loop_53;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp_2 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp_2);
			    MVS_2(result,succ,marked);
			    goto next_loop_54;
			  end_loop_53:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_19;
			    goto next_loop_53;
			  end_loop_54:
			  end_19:
			    level = level - (SI_Long)1L;
			    goto next_loop_52;
			  end_loop_52:;
			    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) 
				    == key_hash_value ? (EQ(key_value,
				    ISVREF(curr,(SI_Long)2L)) ? 
				    ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
			    if (kb_properties);
			    else
				kb_properties = Nil;
			    if (kb_properties) {
				skip_list = CDR(kb_properties);
				key_value = Class_description_gkbprop;
				key_hash_value = 
					SXHASH_SYMBOL_1(Class_description_gkbprop) 
					& IFIX(Most_positive_fixnum);
				bottom_level = (SI_Long)0L;
				marked = Nil;
				pred = M_CAR(skip_list);
				curr = Nil;
				succ = Nil;
				level = (SI_Long)31L;
				ab_loop_bind_ = bottom_level;
			      next_loop_55:
				if (level < ab_loop_bind_)
				    goto end_loop_55;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_56:
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp_2 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp_2);
				MVS_2(result,succ,marked);
			      next_loop_57:
				if ( !TRUEP(marked))
				    goto end_loop_56;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp_2 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp_2);
				MVS_2(result,succ,marked);
				goto next_loop_57;
			      end_loop_56:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_20;
				goto next_loop_56;
			      end_loop_57:
			      end_20:
				level = level - (SI_Long)1L;
				goto next_loop_55;
			      end_loop_55:;
				kb_specific_value = IFIX(ISVREF(curr,
					(SI_Long)1L)) == key_hash_value ? 
					(EQ(key_value,ISVREF(curr,
					(SI_Long)2L)) ? ISVREF(curr,
					(SI_Long)3L) : Nil) : Nil;
				if (kb_specific_value);
				else
				    kb_specific_value = 
					    No_specific_property_value;
			    }
			    else
				kb_specific_value = No_specific_property_value;
			    if ( !EQ(kb_specific_value,
				    No_specific_property_value))
				resulting_value = kb_specific_value;
			    else {
				skip_list = CDR(global_properties);
				key_value = Class_description_gkbprop;
				key_hash_value = 
					SXHASH_SYMBOL_1(Class_description_gkbprop) 
					& IFIX(Most_positive_fixnum);
				bottom_level = (SI_Long)0L;
				marked = Nil;
				pred = M_CAR(skip_list);
				curr = Nil;
				succ = Nil;
				level = (SI_Long)31L;
				ab_loop_bind_ = bottom_level;
			      next_loop_58:
				if (level < ab_loop_bind_)
				    goto end_loop_58;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_59:
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp_2 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp_2);
				MVS_2(result,succ,marked);
			      next_loop_60:
				if ( !TRUEP(marked))
				    goto end_loop_59;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp_2 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp_2);
				MVS_2(result,succ,marked);
				goto next_loop_60;
			      end_loop_59:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_21;
				goto next_loop_59;
			      end_loop_60:
			      end_21:
				level = level - (SI_Long)1L;
				goto next_loop_58;
			      end_loop_58:;
				resulting_value = IFIX(ISVREF(curr,
					(SI_Long)1L)) == key_hash_value ? 
					(EQ(key_value,ISVREF(curr,
					(SI_Long)2L)) ? ISVREF(curr,
					(SI_Long)3L) : Nil) : Nil;
				if (resulting_value);
				else
				    resulting_value = Nil;
			    }
			    gensymed_symbol = resulting_value;
			    if (gensymed_symbol) {
				sub_class_bit_vector = 
					ISVREF(gensymed_symbol,(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(Connection_class_description,
					(SI_Long)18L));
				sub_class_vector_index = 
					superior_class_bit_number >>  -  - 
					(SI_Long)3L;
				if (sub_class_vector_index < 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					    {
				    gensymed_symbol_3 = 
					    UBYTE_8_ISAREF_1(sub_class_bit_vector,
					    sub_class_vector_index);
				    gensymed_symbol_4 = (SI_Long)1L;
				    gensymed_symbol_5 = 
					    superior_class_bit_number & 
					    (SI_Long)7L;
				    gensymed_symbol_4 = gensymed_symbol_4 
					    << gensymed_symbol_5;
				    gensymed_symbol_3 = gensymed_symbol_3 
					    & gensymed_symbol_4;
				    temp = (SI_Long)0L < gensymed_symbol_3;
				}
				else
				    temp = TRUEP(Nil);
			    }
			    else
				temp = TRUEP(Nil);
			    temp =  !temp;
			    if (temp);
			    else {
				gensymed_symbol = 
					lookup_global_or_kb_specific_property_value(connection_class,
					Class_description_gkbprop);
				temp = gensymed_symbol ? 
					TRUEP(memq_function(class_1,
					ISVREF(gensymed_symbol,
					(SI_Long)2L))) : TRUEP(Nil);
			    }
			}
			else
			    temp = TRUEP(Nil);
			if (temp) {
			    if (connection) {
				svref_new_value_1 = 
					IFIX(ISVREF(entity_at_other_end,
					(SI_Long)5L)) | (SI_Long)1048576L;
				ISVREF(entity_at_other_end,(SI_Long)5L) = 
					FIX(svref_new_value_1);
				Entities_to_be_excluded_qm = 
					eval_cons_1(entity_at_other_end,
					Entities_to_be_excluded_qm);
				svref_new_value_1 = IFIX(ISVREF(connection,
					(SI_Long)7L)) | (SI_Long)512L;
				ISVREF(connection,(SI_Long)7L) = 
					FIX(svref_new_value_1);
				Connections_to_be_excluded_qm = 
					eval_cons_1(connection,
					Connections_to_be_excluded_qm);
			    }
			    name_or_names = 
				    get_lookup_slot_value_given_default(entity_at_other_end,
				    Qname_or_names_for_frame,Nil);
			    cp_list = Nil;
			    cp_list_tail = Nil;
			    if (name_or_names) {
				names_sic = name_or_names;
				name = Nil;
			      next_loop_61:
				name = CONSP(names_sic) ? CAR(names_sic) : 
					names_sic;
				if ( !TRUEP(name))
				    goto end_loop_61;
				names_sic_1 = 
					lookup_kb_specific_property_value(name,
					Frame_or_frames_with_this_name_kbprop);
				frame = Nil;
			      next_loop_62:
				frame = CONSP(names_sic_1) ? 
					CAR(names_sic_1) : names_sic_1;
				if ( !TRUEP(frame))
				    goto end_loop_62;
				sub_class_bit_vector = ISVREF(ISVREF(frame,
					(SI_Long)1L),(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(Connection_post_class_description,
					(SI_Long)18L));
				sub_class_vector_index = 
					superior_class_bit_number >>  -  - 
					(SI_Long)3L;
				if (sub_class_vector_index < 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					    {
				    gensymed_symbol_3 = 
					    UBYTE_8_ISAREF_1(sub_class_bit_vector,
					    sub_class_vector_index);
				    gensymed_symbol_4 = (SI_Long)1L;
				    gensymed_symbol_5 = 
					    superior_class_bit_number & 
					    (SI_Long)7L;
				    gensymed_symbol_4 = gensymed_symbol_4 
					    << gensymed_symbol_5;
				    gensymed_symbol_3 = gensymed_symbol_3 
					    & gensymed_symbol_4;
				    temp = (SI_Long)0L < gensymed_symbol_3;
				}
				else
				    temp = TRUEP(Nil);
				if (temp ?  !TRUEP(memq_function(frame,
					cp_list)) : TRUEP(Nil)) {
				    gensymed_symbol = frame;
				    gensymed_symbol = 
					    gensym_cons_1(gensymed_symbol,Nil);
				    if (cp_list) {
					if ( !TRUEP(cp_list_tail))
					    cp_list_tail = last(cp_list,_);
					M_CDR(cp_list_tail) = gensymed_symbol;
				    }
				    else
					cp_list = gensymed_symbol;
				    cp_list_tail = gensymed_symbol;
				}
				names_sic_1 = CONSP(names_sic_1) ? 
					CDR(names_sic_1) : Nil;
				goto next_loop_62;
			      end_loop_62:;
				names_sic = CONSP(names_sic) ? 
					CDR(names_sic) : Nil;
				goto next_loop_61;
			      end_loop_61:;
			    }
			    else
				cp_list = 
					gensym_cons_1(entity_at_other_end,Nil);
			    cp = Nil;
			    ab_loop_list_ = cp_list;
			  next_loop_63:
			    if ( !TRUEP(ab_loop_list_))
				goto end_loop_63;
			    cp = M_CAR(ab_loop_list_);
			    ab_loop_list_ = M_CDR(ab_loop_list_);
			    superior_connection_and_end = 
				    get_lookup_slot_value_given_default(cp,
				    Qsuperior_connection_cache,Nil);
			    temp_2 = cp;
			    temp_1 = directionality_qm;
			    if (temp_1);
			    else
				temp_1 = directionality;
			    search_for_directly_connected_entities_rec(temp_2,
				    class_1,temp_1,
				    also_get_port_and_direction_info_qm,
				    required_connection_directionality_for_inverse_role_service_qm,
				    do_not_stop_search_at_connections_qm);
			    if (superior_connection_and_end &&  !TRUEP(Nil)) {
				superior_connection = 
					CDR(superior_connection_and_end);
				superior_connection_frame = Nil;
				connection_end = 
					CAR(superior_connection_and_end);
				required_direction_qm = Nil;
				if (required_direction_qm);
				else {
				    required_direction_qm = directionality_qm;
				    if (required_direction_qm);
				    else
					required_direction_qm = directionality;
				}
				direction_to_try = Qinput;
				superior_connection_frame = 
					ISVREF(superior_connection,
					(SI_Long)1L);
			      next_loop_64:
				if ( !TRUEP(Nil) && ((SI_Long)0L != 
					(IFIX(ISVREF(superior_connection,
					(SI_Long)7L)) & (SI_Long)1L) ||  
					!TRUEP(required_direction_qm)) || 
					( !TRUEP(Nil) ||  !((SI_Long)0L != 
					(IFIX(ISVREF(superior_connection,
					(SI_Long)7L)) & (SI_Long)1L))) && 
					EQ(required_direction_qm,
					direction_to_try) && 
					(EQ(direction_to_try,Qinput) ? 
					EQ(connection_end,Qoutput) : 
					EQ(connection_end,Qinput))) {
				    if (SIMPLE_VECTOR_P(superior_connection_frame) 
					    && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(superior_connection_frame)) 
					    > (SI_Long)2L &&  
					    !EQ(ISVREF(superior_connection_frame,
					    (SI_Long)1L),
					    Qavailable_frame_vector)) {
					x2 = 
						ISVREF(superior_connection_frame,
						(SI_Long)1L);
					temp = SIMPLE_VECTOR_P(x2) && 
						EQ(ISVREF(x2,(SI_Long)0L),
						Qg2_defstruct_structure_name_class_description_g2_struct) 
						? TRUEP(x2) : TRUEP(Qnil);
				    }
				    else
					temp = TRUEP(Nil);
				    temp =  !(temp ? 
					    TRUEP(ISVREF(ISVREF(superior_connection_frame,
					    (SI_Long)1L),(SI_Long)16L)) : 
					    TRUEP(Nil));
				    if (temp);
				    else
					temp = 
						TRUEP(serve_item_p(superior_connection_frame));
				}
				else
				    temp = TRUEP(Nil);
				if (temp)
				    search_for_directly_connected_entities_for_connection(EQ(direction_to_try,
					    Qinput) ? 
					    ISVREF(superior_connection,
					    (SI_Long)2L) : 
					    ISVREF(superior_connection,
					    (SI_Long)3L),class_1,
					    superior_connection,
					    required_direction_qm,
					    also_get_port_and_direction_info_qm,
					    Nil,
					    required_connection_directionality_for_inverse_role_service_qm,
					    do_not_stop_search_at_connections_qm);
				if (EQ(direction_to_try,Qoutput))
				    goto end_loop_64;
				superior_connection_frame = 
					ISVREF(superior_connection,
					(SI_Long)1L);
				direction_to_try = Qoutput;
				goto next_loop_64;
			      end_loop_64:;
			    }
			    goto next_loop_63;
			  end_loop_63:;
			    reclaim_gensym_list_1(cp_list);
			}
			else {
			    skip_list = CDR(Symbol_properties_table);
			    key_value = class_of_entity_at_other_end;
			    key_hash_value = 
				    SXHASH_SYMBOL_1(class_of_entity_at_other_end) 
				    & IFIX(Most_positive_fixnum);
			    bottom_level = (SI_Long)0L;
			    marked = Nil;
			    pred = M_CAR(skip_list);
			    curr = Nil;
			    succ = Nil;
			    level = (SI_Long)31L;
			    ab_loop_bind_ = bottom_level;
			  next_loop_65:
			    if (level < ab_loop_bind_)
				goto end_loop_65;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_66:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp_2 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp_2);
			    MVS_2(result,succ,marked);
			  next_loop_67:
			    if ( !TRUEP(marked))
				goto end_loop_66;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp_2 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp_2);
			    MVS_2(result,succ,marked);
			    goto next_loop_67;
			  end_loop_66:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_22;
			    goto next_loop_66;
			  end_loop_67:
			  end_22:
			    level = level - (SI_Long)1L;
			    goto next_loop_65;
			  end_loop_65:;
			    gensymed_symbol = IFIX(ISVREF(curr,
				    (SI_Long)1L)) == key_hash_value ? 
				    (EQ(key_value,ISVREF(curr,
				    (SI_Long)2L)) ? ISVREF(curr,
				    (SI_Long)3L) : Nil) : Nil;
			    if ( !TRUEP(gensymed_symbol)) {
				gensymed_symbol = class_of_entity_at_other_end;
				temp_1 = Symbol_properties_table;
				temp_2 = 
					FIX(SXHASH_SYMBOL_1(gensymed_symbol) 
					& IFIX(Most_positive_fixnum));
				tail = 
					make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
					Nil);
				head = 
					make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
					tail);
				new_cons = 
					ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index));
				if (new_cons) {
				    svref_arg_1 = 
					    Available_lookup_conses_vector;
				    svref_arg_2 = Current_thread_index;
				    svref_new_value = M_CDR(new_cons);
				    SVREF(svref_arg_1,svref_arg_2) = 
					    svref_new_value;
				    if ( 
					    !TRUEP(ISVREF(Available_lookup_conses_vector,
					    IFIX(Current_thread_index)))) {
					svref_arg_1 = 
						Available_lookup_conses_tail_vector;
					svref_arg_2 = Current_thread_index;
					SVREF(svref_arg_1,svref_arg_2) = Nil;
				    }
				    gensymed_symbol_1 = new_cons;
				}
				else
				    gensymed_symbol_1 = Nil;
				if ( !TRUEP(gensymed_symbol_1))
				    gensymed_symbol_1 = 
					    replenish_lookup_cons_pool();
				M_CAR(gensymed_symbol_1) = 
					Qsymbol_properties_hash_table;
				new_cons = 
					ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index));
				if (new_cons) {
				    svref_arg_1 = 
					    Available_lookup_conses_vector;
				    svref_arg_2 = Current_thread_index;
				    svref_new_value = M_CDR(new_cons);
				    SVREF(svref_arg_1,svref_arg_2) = 
					    svref_new_value;
				    if ( 
					    !TRUEP(ISVREF(Available_lookup_conses_vector,
					    IFIX(Current_thread_index)))) {
					svref_arg_1 = 
						Available_lookup_conses_tail_vector;
					svref_arg_2 = Current_thread_index;
					SVREF(svref_arg_1,svref_arg_2) = Nil;
				    }
				    gensymed_symbol_2 = new_cons;
				}
				else
				    gensymed_symbol_2 = Nil;
				if ( !TRUEP(gensymed_symbol_2))
				    gensymed_symbol_2 = 
					    replenish_lookup_cons_pool();
				M_CAR(gensymed_symbol_2) = head;
				M_CDR(gensymed_symbol_2) = tail;
				inline_note_allocate_cons(gensymed_symbol_2,
					Qlookup);
				M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
				inline_note_allocate_cons(gensymed_symbol_1,
					Qlookup);
				gensymed_symbol = 
					set_skip_list_entry(temp_1,
					FIX((SI_Long)31L),Qeq,Nil,T,
					gensymed_symbol,temp_2,
					gensymed_symbol_1);
			    }
			    global_properties = gensymed_symbol;
			    skip_list = CDR(global_properties);
			    key_value = 
				    Current_kb_specific_property_list_property_name;
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
			  next_loop_68:
			    if (level < ab_loop_bind_)
				goto end_loop_68;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_69:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp_2 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp_2);
			    MVS_2(result,succ,marked);
			  next_loop_70:
			    if ( !TRUEP(marked))
				goto end_loop_69;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp_2 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp_2);
			    MVS_2(result,succ,marked);
			    goto next_loop_70;
			  end_loop_69:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_23;
			    goto next_loop_69;
			  end_loop_70:
			  end_23:
			    level = level - (SI_Long)1L;
			    goto next_loop_68;
			  end_loop_68:;
			    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) 
				    == key_hash_value ? (EQ(key_value,
				    ISVREF(curr,(SI_Long)2L)) ? 
				    ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
			    if (kb_properties);
			    else
				kb_properties = Nil;
			    if (kb_properties) {
				skip_list = CDR(kb_properties);
				key_value = Class_description_gkbprop;
				key_hash_value = 
					SXHASH_SYMBOL_1(Class_description_gkbprop) 
					& IFIX(Most_positive_fixnum);
				bottom_level = (SI_Long)0L;
				marked = Nil;
				pred = M_CAR(skip_list);
				curr = Nil;
				succ = Nil;
				level = (SI_Long)31L;
				ab_loop_bind_ = bottom_level;
			      next_loop_71:
				if (level < ab_loop_bind_)
				    goto end_loop_71;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_72:
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp_2 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp_2);
				MVS_2(result,succ,marked);
			      next_loop_73:
				if ( !TRUEP(marked))
				    goto end_loop_72;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp_2 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp_2);
				MVS_2(result,succ,marked);
				goto next_loop_73;
			      end_loop_72:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_24;
				goto next_loop_72;
			      end_loop_73:
			      end_24:
				level = level - (SI_Long)1L;
				goto next_loop_71;
			      end_loop_71:;
				kb_specific_value = IFIX(ISVREF(curr,
					(SI_Long)1L)) == key_hash_value ? 
					(EQ(key_value,ISVREF(curr,
					(SI_Long)2L)) ? ISVREF(curr,
					(SI_Long)3L) : Nil) : Nil;
				if (kb_specific_value);
				else
				    kb_specific_value = 
					    No_specific_property_value;
			    }
			    else
				kb_specific_value = No_specific_property_value;
			    if ( !EQ(kb_specific_value,
				    No_specific_property_value))
				resulting_value = kb_specific_value;
			    else {
				skip_list = CDR(global_properties);
				key_value = Class_description_gkbprop;
				key_hash_value = 
					SXHASH_SYMBOL_1(Class_description_gkbprop) 
					& IFIX(Most_positive_fixnum);
				bottom_level = (SI_Long)0L;
				marked = Nil;
				pred = M_CAR(skip_list);
				curr = Nil;
				succ = Nil;
				level = (SI_Long)31L;
				ab_loop_bind_ = bottom_level;
			      next_loop_74:
				if (level < ab_loop_bind_)
				    goto end_loop_74;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_75:
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp_2 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp_2);
				MVS_2(result,succ,marked);
			      next_loop_76:
				if ( !TRUEP(marked))
				    goto end_loop_75;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp_2 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp_2);
				MVS_2(result,succ,marked);
				goto next_loop_76;
			      end_loop_75:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_25;
				goto next_loop_75;
			      end_loop_76:
			      end_25:
				level = level - (SI_Long)1L;
				goto next_loop_74;
			      end_loop_74:;
				resulting_value = IFIX(ISVREF(curr,
					(SI_Long)1L)) == key_hash_value ? 
					(EQ(key_value,ISVREF(curr,
					(SI_Long)2L)) ? ISVREF(curr,
					(SI_Long)3L) : Nil) : Nil;
				if (resulting_value);
				else
				    resulting_value = Nil;
			    }
			    gensymed_symbol = resulting_value;
			    if (gensymed_symbol) {
				sub_class_bit_vector = 
					ISVREF(gensymed_symbol,(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(Default_junction_class_description,
					(SI_Long)18L));
				sub_class_vector_index = 
					superior_class_bit_number >>  -  - 
					(SI_Long)3L;
				if (sub_class_vector_index < 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					    {
				    gensymed_symbol_3 = 
					    UBYTE_8_ISAREF_1(sub_class_bit_vector,
					    sub_class_vector_index);
				    gensymed_symbol_4 = (SI_Long)1L;
				    gensymed_symbol_5 = 
					    superior_class_bit_number & 
					    (SI_Long)7L;
				    gensymed_symbol_4 = gensymed_symbol_4 
					    << gensymed_symbol_5;
				    gensymed_symbol_3 = gensymed_symbol_3 
					    & gensymed_symbol_4;
				    temp = (SI_Long)0L < gensymed_symbol_3;
				}
				else
				    temp = TRUEP(Nil);
			    }
			    else
				temp = TRUEP(Nil);
			    if (temp) {
				skip_list = CDR(Symbol_properties_table);
				key_value = class_1;
				key_hash_value = SXHASH_SYMBOL_1(class_1) 
					& IFIX(Most_positive_fixnum);
				bottom_level = (SI_Long)0L;
				marked = Nil;
				pred = M_CAR(skip_list);
				curr = Nil;
				succ = Nil;
				level = (SI_Long)31L;
				ab_loop_bind_ = bottom_level;
			      next_loop_77:
				if (level < ab_loop_bind_)
				    goto end_loop_77;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_78:
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp_2 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp_2);
				MVS_2(result,succ,marked);
			      next_loop_79:
				if ( !TRUEP(marked))
				    goto end_loop_78;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp_2 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp_2);
				MVS_2(result,succ,marked);
				goto next_loop_79;
			      end_loop_78:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_26;
				goto next_loop_78;
			      end_loop_79:
			      end_26:
				level = level - (SI_Long)1L;
				goto next_loop_77;
			      end_loop_77:;
				gensymed_symbol = IFIX(ISVREF(curr,
					(SI_Long)1L)) == key_hash_value ? 
					(EQ(key_value,ISVREF(curr,
					(SI_Long)2L)) ? ISVREF(curr,
					(SI_Long)3L) : Nil) : Nil;
				if ( !TRUEP(gensymed_symbol)) {
				    gensymed_symbol = class_1;
				    temp_1 = Symbol_properties_table;
				    temp_2 = 
					    FIX(SXHASH_SYMBOL_1(gensymed_symbol) 
					    & IFIX(Most_positive_fixnum));
				    tail = 
					    make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
					    Nil);
				    head = 
					    make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
					    tail);
				    new_cons = 
					    ISVREF(Available_lookup_conses_vector,
					    IFIX(Current_thread_index));
				    if (new_cons) {
					svref_arg_1 = 
						Available_lookup_conses_vector;
					svref_arg_2 = Current_thread_index;
					svref_new_value = M_CDR(new_cons);
					SVREF(svref_arg_1,svref_arg_2) = 
						svref_new_value;
					if ( 
						!TRUEP(ISVREF(Available_lookup_conses_vector,
						IFIX(Current_thread_index)))) {
					    svref_arg_1 = 
						    Available_lookup_conses_tail_vector;
					    svref_arg_2 = Current_thread_index;
					    SVREF(svref_arg_1,svref_arg_2) 
						    = Nil;
					}
					gensymed_symbol_1 = new_cons;
				    }
				    else
					gensymed_symbol_1 = Nil;
				    if ( !TRUEP(gensymed_symbol_1))
					gensymed_symbol_1 = 
						replenish_lookup_cons_pool();
				    M_CAR(gensymed_symbol_1) = 
					    Qsymbol_properties_hash_table;
				    new_cons = 
					    ISVREF(Available_lookup_conses_vector,
					    IFIX(Current_thread_index));
				    if (new_cons) {
					svref_arg_1 = 
						Available_lookup_conses_vector;
					svref_arg_2 = Current_thread_index;
					svref_new_value = M_CDR(new_cons);
					SVREF(svref_arg_1,svref_arg_2) = 
						svref_new_value;
					if ( 
						!TRUEP(ISVREF(Available_lookup_conses_vector,
						IFIX(Current_thread_index)))) {
					    svref_arg_1 = 
						    Available_lookup_conses_tail_vector;
					    svref_arg_2 = Current_thread_index;
					    SVREF(svref_arg_1,svref_arg_2) 
						    = Nil;
					}
					gensymed_symbol_2 = new_cons;
				    }
				    else
					gensymed_symbol_2 = Nil;
				    if ( !TRUEP(gensymed_symbol_2))
					gensymed_symbol_2 = 
						replenish_lookup_cons_pool();
				    M_CAR(gensymed_symbol_2) = head;
				    M_CDR(gensymed_symbol_2) = tail;
				    inline_note_allocate_cons(gensymed_symbol_2,
					    Qlookup);
				    M_CDR(gensymed_symbol_1) = 
					    gensymed_symbol_2;
				    inline_note_allocate_cons(gensymed_symbol_1,
					    Qlookup);
				    gensymed_symbol = 
					    set_skip_list_entry(temp_1,
					    FIX((SI_Long)31L),Qeq,Nil,T,
					    gensymed_symbol,temp_2,
					    gensymed_symbol_1);
				}
				global_properties = gensymed_symbol;
				skip_list = CDR(global_properties);
				key_value = 
					Current_kb_specific_property_list_property_name;
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
			      next_loop_80:
				if (level < ab_loop_bind_)
				    goto end_loop_80;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_81:
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp_2 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp_2);
				MVS_2(result,succ,marked);
			      next_loop_82:
				if ( !TRUEP(marked))
				    goto end_loop_81;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp_2 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp_2);
				MVS_2(result,succ,marked);
				goto next_loop_82;
			      end_loop_81:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_27;
				goto next_loop_81;
			      end_loop_82:
			      end_27:
				level = level - (SI_Long)1L;
				goto next_loop_80;
			      end_loop_80:;
				kb_properties = IFIX(ISVREF(curr,
					(SI_Long)1L)) == key_hash_value ? 
					(EQ(key_value,ISVREF(curr,
					(SI_Long)2L)) ? ISVREF(curr,
					(SI_Long)3L) : Nil) : Nil;
				if (kb_properties);
				else
				    kb_properties = Nil;
				if (kb_properties) {
				    skip_list = CDR(kb_properties);
				    key_value = Class_description_gkbprop;
				    key_hash_value = 
					    SXHASH_SYMBOL_1(Class_description_gkbprop) 
					    & IFIX(Most_positive_fixnum);
				    bottom_level = (SI_Long)0L;
				    marked = Nil;
				    pred = M_CAR(skip_list);
				    curr = Nil;
				    succ = Nil;
				    level = (SI_Long)31L;
				    ab_loop_bind_ = bottom_level;
				  next_loop_83:
				    if (level < ab_loop_bind_)
					goto end_loop_83;
				    curr = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					    (SI_Long)0L),level));
				  next_loop_84:
				    reference = ISVREF(ISVREF(curr,
					    (SI_Long)0L),level);
				    temp_1 = ATOMIC_REF_OBJECT(reference);
				    temp_2 = (SI_Long)355L == 
					    ATOMIC_REF_STAMP(reference) ? 
					    T : Nil;
				    result = VALUES_2(temp_1,temp_2);
				    MVS_2(result,succ,marked);
				  next_loop_85:
				    if ( !TRUEP(marked))
					goto end_loop_84;
				    curr = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					    (SI_Long)0L),level));
				    reference = ISVREF(ISVREF(curr,
					    (SI_Long)0L),level);
				    temp_1 = ATOMIC_REF_OBJECT(reference);
				    temp_2 = (SI_Long)355L == 
					    ATOMIC_REF_STAMP(reference) ? 
					    T : Nil;
				    result = VALUES_2(temp_1,temp_2);
				    MVS_2(result,succ,marked);
				    goto next_loop_85;
				  end_loop_84:
				    entry_hash = ISVREF(curr,(SI_Long)1L);
				    if (IFIX(entry_hash) < key_hash_value 
					    || IFIX(entry_hash) == 
					    key_hash_value &&  
					    !EQ(key_value,ISVREF(curr,
					    (SI_Long)2L))) {
					pred = curr;
					curr = succ;
				    }
				    else
					goto end_28;
				    goto next_loop_84;
				  end_loop_85:
				  end_28:
				    level = level - (SI_Long)1L;
				    goto next_loop_83;
				  end_loop_83:;
				    kb_specific_value = IFIX(ISVREF(curr,
					    (SI_Long)1L)) == 
					    key_hash_value ? (EQ(key_value,
					    ISVREF(curr,(SI_Long)2L)) ? 
					    ISVREF(curr,(SI_Long)3L) : 
					    Nil) : Nil;
				    if (kb_specific_value);
				    else
					kb_specific_value = 
						No_specific_property_value;
				}
				else
				    kb_specific_value = 
					    No_specific_property_value;
				if ( !EQ(kb_specific_value,
					No_specific_property_value))
				    resulting_value = kb_specific_value;
				else {
				    skip_list = CDR(global_properties);
				    key_value = Class_description_gkbprop;
				    key_hash_value = 
					    SXHASH_SYMBOL_1(Class_description_gkbprop) 
					    & IFIX(Most_positive_fixnum);
				    bottom_level = (SI_Long)0L;
				    marked = Nil;
				    pred = M_CAR(skip_list);
				    curr = Nil;
				    succ = Nil;
				    level = (SI_Long)31L;
				    ab_loop_bind_ = bottom_level;
				  next_loop_86:
				    if (level < ab_loop_bind_)
					goto end_loop_86;
				    curr = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					    (SI_Long)0L),level));
				  next_loop_87:
				    reference = ISVREF(ISVREF(curr,
					    (SI_Long)0L),level);
				    temp_1 = ATOMIC_REF_OBJECT(reference);
				    temp_2 = (SI_Long)355L == 
					    ATOMIC_REF_STAMP(reference) ? 
					    T : Nil;
				    result = VALUES_2(temp_1,temp_2);
				    MVS_2(result,succ,marked);
				  next_loop_88:
				    if ( !TRUEP(marked))
					goto end_loop_87;
				    curr = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					    (SI_Long)0L),level));
				    reference = ISVREF(ISVREF(curr,
					    (SI_Long)0L),level);
				    temp_1 = ATOMIC_REF_OBJECT(reference);
				    temp_2 = (SI_Long)355L == 
					    ATOMIC_REF_STAMP(reference) ? 
					    T : Nil;
				    result = VALUES_2(temp_1,temp_2);
				    MVS_2(result,succ,marked);
				    goto next_loop_88;
				  end_loop_87:
				    entry_hash = ISVREF(curr,(SI_Long)1L);
				    if (IFIX(entry_hash) < key_hash_value 
					    || IFIX(entry_hash) == 
					    key_hash_value &&  
					    !EQ(key_value,ISVREF(curr,
					    (SI_Long)2L))) {
					pred = curr;
					curr = succ;
				    }
				    else
					goto end_29;
				    goto next_loop_87;
				  end_loop_88:
				  end_29:
				    level = level - (SI_Long)1L;
				    goto next_loop_86;
				  end_loop_86:;
				    resulting_value = IFIX(ISVREF(curr,
					    (SI_Long)1L)) == 
					    key_hash_value ? (EQ(key_value,
					    ISVREF(curr,(SI_Long)2L)) ? 
					    ISVREF(curr,(SI_Long)3L) : 
					    Nil) : Nil;
				    if (resulting_value);
				    else
					resulting_value = Nil;
				}
				gensymed_symbol = resulting_value;
				if (gensymed_symbol) {
				    sub_class_bit_vector = 
					    ISVREF(gensymed_symbol,
					    (SI_Long)19L);
				    superior_class_bit_number = 
					    IFIX(ISVREF(Default_junction_class_description,
					    (SI_Long)18L));
				    sub_class_vector_index = 
					    superior_class_bit_number >>  
					    -  - (SI_Long)3L;
				    if (sub_class_vector_index < 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
						{
					gensymed_symbol_3 = 
						UBYTE_8_ISAREF_1(sub_class_bit_vector,
						sub_class_vector_index);
					gensymed_symbol_4 = (SI_Long)1L;
					gensymed_symbol_5 = 
						superior_class_bit_number 
						& (SI_Long)7L;
					gensymed_symbol_4 = 
						gensymed_symbol_4 << 
						gensymed_symbol_5;
					gensymed_symbol_3 = 
						gensymed_symbol_3 & 
						gensymed_symbol_4;
					temp = (SI_Long)0L < gensymed_symbol_3;
				    }
				    else
					temp = TRUEP(Nil);
				}
				else
				    temp = TRUEP(Nil);
				temp =  !temp;
				if (temp);
				else {
				    gensymed_symbol = 
					    lookup_global_or_kb_specific_property_value(class_of_entity_at_other_end,
					    Class_description_gkbprop);
				    temp =  !(gensymed_symbol ? 
					    TRUEP(memq_function(class_1,
					    ISVREF(gensymed_symbol,
					    (SI_Long)2L))) : TRUEP(Nil));
				}
			    }
			    else
				temp = TRUEP(Nil);
			    if (temp) {
				svref_new_value_1 = 
					IFIX(ISVREF(entity_at_other_end,
					(SI_Long)5L)) | (SI_Long)1048576L;
				ISVREF(entity_at_other_end,(SI_Long)5L) = 
					FIX(svref_new_value_1);
				Entities_to_be_excluded_qm = 
					eval_cons_1(entity_at_other_end,
					Entities_to_be_excluded_qm);
				svref_new_value_1 = IFIX(ISVREF(connection,
					(SI_Long)7L)) | (SI_Long)512L;
				ISVREF(connection,(SI_Long)7L) = 
					FIX(svref_new_value_1);
				Connections_to_be_excluded_qm = 
					eval_cons_1(connection,
					Connections_to_be_excluded_qm);
				temp_2 = directionality_qm;
				if (temp_2);
				else
				    temp_2 = directionality;
				search_for_directly_connected_entities_rec(entity_at_other_end,
					class_1,temp_2,
					also_get_port_and_direction_info_qm,
					required_connection_directionality_for_inverse_role_service_qm,
					do_not_stop_search_at_connections_qm);
			    }
			    else {
				gensymed_symbol = 
					lookup_global_or_kb_specific_property_value(class_of_entity_at_other_end,
					Class_description_gkbprop);
				if ((gensymed_symbol ? 
					TRUEP(memq_function(class_1,
					ISVREF(gensymed_symbol,
					(SI_Long)2L))) : TRUEP(Nil)) ?  
					!((SI_Long)0L != 
					(IFIX(ISVREF(entity_at_other_end,
					(SI_Long)5L)) & 
					(SI_Long)1048576L)) : TRUEP(Nil))
				    note_entity_found_in_directly_connected_search(entity_at_other_end,
					    connection,
					    also_get_port_and_direction_info_qm);
			    }
			}
		    }
		}
	    }
	    skip_list = CDR(Symbol_properties_table);
	    key_value = class_1;
	    key_hash_value = SXHASH_SYMBOL_1(class_1) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_89:
	    if (level < ab_loop_bind_)
		goto end_loop_89;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_90:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_91:
	    if ( !TRUEP(marked))
		goto end_loop_90;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	    goto next_loop_91;
	  end_loop_90:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_30;
	    goto next_loop_90;
	  end_loop_91:
	  end_30:
	    level = level - (SI_Long)1L;
	    goto next_loop_89;
	  end_loop_89:;
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = class_1;
		temp_1 = Symbol_properties_table;
		temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
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
		gensymed_symbol = set_skip_list_entry(temp_1,
			FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp_2,
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
	  next_loop_92:
	    if (level < ab_loop_bind_)
		goto end_loop_92;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_93:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_94:
	    if ( !TRUEP(marked))
		goto end_loop_93;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	    goto next_loop_94;
	  end_loop_93:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_31;
	    goto next_loop_93;
	  end_loop_94:
	  end_31:
	    level = level - (SI_Long)1L;
	    goto next_loop_92;
	  end_loop_92:;
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
	      next_loop_95:
		if (level < ab_loop_bind_)
		    goto end_loop_95;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_96:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_97:
		if ( !TRUEP(marked))
		    goto end_loop_96;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
		goto next_loop_97;
	      end_loop_96:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_32;
		goto next_loop_96;
	      end_loop_97:
	      end_32:
		level = level - (SI_Long)1L;
		goto next_loop_95;
	      end_loop_95:;
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
	      next_loop_98:
		if (level < ab_loop_bind_)
		    goto end_loop_98;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_99:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_100:
		if ( !TRUEP(marked))
		    goto end_loop_99;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
		goto next_loop_100;
	      end_loop_99:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_33;
		goto next_loop_99;
	      end_loop_100:
	      end_33:
		level = level - (SI_Long)1L;
		goto next_loop_98;
	      end_loop_98:;
		resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    gensymed_symbol = resulting_value;
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Connection_class_description,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_3 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_4 = (SI_Long)1L;
		    gensymed_symbol_5 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_4 = gensymed_symbol_4 << gensymed_symbol_5;
		    gensymed_symbol_3 = gensymed_symbol_3 & gensymed_symbol_4;
		    temp = (SI_Long)0L < gensymed_symbol_3;
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	    temp =  !temp;
	    if (temp);
	    else {
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(connection_class,
			Class_description_gkbprop);
		temp = gensymed_symbol ? TRUEP(memq_function(class_1,
			ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil);
	    }
	    if (temp) {
		temp_2 = directionality_qm;
		if (temp_2);
		else
		    temp_2 = directionality;
		return search_for_subworkspace_connection_posts(class_1,
			connection,temp_2,
			also_get_port_and_direction_info_qm,
			required_connection_directionality_for_inverse_role_service_qm,
			do_not_stop_search_at_connections_qm);
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

/* NOTE-ENTITY-FOUND-IN-DIRECTLY-CONNECTED-SEARCH */
Object note_entity_found_in_directly_connected_search(entity_found,
	    connection,also_get_port_and_direction_info_qm)
    Object entity_found, connection, also_get_port_and_direction_info_qm;
{
    Object gensymed_symbol, gensymed_symbol_1, new_cons, svref_arg_1;
    Object svref_arg_2, svref_new_value, gensymed_symbol_2;
    SI_Long svref_new_value_1;
    char temp;

    x_note_fn_call(149,110);
    if ( !((SI_Long)0L != (IFIX(ISVREF(entity_found,(SI_Long)5L)) & 
	    (SI_Long)512L))) {
	if (Note_things_encountered_during_role_service_qm) {
	    gensymed_symbol = Things_that_affect_this_formula;
	    gensymed_symbol_1 = entity_found;
	    if ( !TRUEP(memq_function(gensymed_symbol_1,gensymed_symbol))) {
		new_cons = ISVREF(Available_eval_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    svref_arg_1 = Available_eval_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
			    IFIX(Current_thread_index)))) {
			svref_arg_1 = Available_eval_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(svref_arg_1,svref_arg_2) = Nil;
		    }
		    gensymed_symbol_2 = new_cons;
		}
		else
		    gensymed_symbol_2 = Nil;
		if ( !TRUEP(gensymed_symbol_2))
		    gensymed_symbol_2 = replenish_eval_cons_pool();
		M_CAR(gensymed_symbol_2) = gensymed_symbol_1;
		M_CDR(gensymed_symbol_2) = gensymed_symbol;
		inline_note_allocate_cons(gensymed_symbol_2,Qeval);
		Things_that_affect_this_formula = gensymed_symbol_2;
	    }
	}
	temp = TRUEP(T);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	if (Current_connection_path)
	    Connections_in_connection_paths = 
		    eval_cons_1(copy_list_using_eval_conses_1(Current_connection_path),
		    Connections_in_connection_paths);
	if (also_get_port_and_direction_info_qm)
	    add_port_and_direction_info_triple(entity_found,connection,
		    also_get_port_and_direction_info_qm);
	else {
	    svref_new_value_1 = IFIX(ISVREF(entity_found,(SI_Long)5L)) | 
		    (SI_Long)1048576L;
	    ISVREF(entity_found,(SI_Long)5L) = FIX(svref_new_value_1);
	    Entities_to_be_excluded_qm = eval_cons_1(entity_found,
		    Entities_to_be_excluded_qm);
	    Entities_or_triples_found_in_search = eval_cons_1(entity_found,
		    Entities_or_triples_found_in_search);
	}
	if (There_exists_p) {
	    Do_not_stop_search_once_found_qm = Nil;
	    return VALUES_1(Do_not_stop_search_once_found_qm);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qinput_end_subworkspace_connection_posts;  /* input-end-subworkspace-connection-posts */

static Object Qoutput_end_subworkspace_connection_posts;  /* output-end-subworkspace-connection-posts */

/* SEARCH-FOR-SUBWORKSPACE-CONNECTION-POSTS */
Object search_for_subworkspace_connection_posts(class_1,connection,
	    directionality_qm,also_get_port_and_direction_info_qm,
	    required_connection_directionality_for_inverse_role_service_qm,
	    do_not_stop_search_at_connections_qm)
    Object class_1, connection, directionality_qm;
    Object also_get_port_and_direction_info_qm;
    Object required_connection_directionality_for_inverse_role_service_qm;
    Object do_not_stop_search_at_connections_qm;
{
    Object input_end_subworkspace_connection_posts;
    Object output_end_subworkspace_connection_posts;

    x_note_fn_call(149,111);
    input_end_subworkspace_connection_posts = 
	    getfq_function_no_default(ISVREF(connection,(SI_Long)9L),
	    Qinput_end_subworkspace_connection_posts);
    output_end_subworkspace_connection_posts = 
	    getfq_function_no_default(ISVREF(connection,(SI_Long)9L),
	    Qoutput_end_subworkspace_connection_posts);
    search_for_subworkspace_connection_posts_1(input_end_subworkspace_connection_posts,
	    class_1,connection,directionality_qm,
	    also_get_port_and_direction_info_qm,
	    required_connection_directionality_for_inverse_role_service_qm,
	    do_not_stop_search_at_connections_qm,Qinput);
    return search_for_subworkspace_connection_posts_1(output_end_subworkspace_connection_posts,
	    class_1,connection,directionality_qm,
	    also_get_port_and_direction_info_qm,
	    required_connection_directionality_for_inverse_role_service_qm,
	    do_not_stop_search_at_connections_qm,Qoutput);
}

/* SEARCH-FOR-SUBWORKSPACE-CONNECTION-POSTS-1 */
Object search_for_subworkspace_connection_posts_1(connection_posts,class_1,
	    connection,directionality_qm,
	    also_get_port_and_direction_info_qm,
	    required_connection_directionality_for_inverse_role_service_qm,
	    do_not_stop_search_at_connections_qm,required_direction)
    Object connection_posts, class_1, connection, directionality_qm;
    Object also_get_port_and_direction_info_qm;
    Object required_connection_directionality_for_inverse_role_service_qm;
    Object do_not_stop_search_at_connections_qm, required_direction;
{
    Object connection_post, ab_loop_list_, skip_list, key_value, marked, pred;
    Object curr, succ, reference, temp, temp_1, entry_hash, gensymed_symbol;
    Object tail, head, new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_1, gensymed_symbol_2, global_properties;
    Object kb_properties, kb_specific_value, resulting_value;
    Object sub_class_bit_vector, name_or_names, cp_list, cp_list_tail;
    Object names_sic, name, names_sic_1, frame, cp, ab_loop_list__1;
    Object superior_connection_and_end, superior_connection;
    Object superior_connection_frame, connection_end, required_direction_qm;
    Object direction_to_try, x2;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    SI_Long svref_new_value_1;
    char temp_2;
    Object result;

    x_note_fn_call(149,112);
    if ((SI_Long)0L != (IFIX(ISVREF(connection,(SI_Long)7L)) & 
	    (SI_Long)1L) ||  !TRUEP(directionality_qm) || 
	    EQ(directionality_qm,required_direction)) {
	connection_post = Nil;
	ab_loop_list_ = connection_posts;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	connection_post = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !((SI_Long)0L != (IFIX(ISVREF(connection_post,(SI_Long)5L)) & 
		(SI_Long)1048576L))) {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = class_1;
	    key_hash_value = SXHASH_SYMBOL_1(class_1) & 
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
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
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
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
	      next_loop_7:
		if (level < ab_loop_bind_)
		    goto end_loop_7;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_8:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_9:
		if ( !TRUEP(marked))
		    goto end_loop_8;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_9;
	      end_loop_8:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
	      next_loop_10:
		if (level < ab_loop_bind_)
		    goto end_loop_10;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_11:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_12:
		if ( !TRUEP(marked))
		    goto end_loop_11;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_12;
	      end_loop_11:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
	    gensymed_symbol = resulting_value;
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Connection_post_class_description,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_3 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_4 = (SI_Long)1L;
		    gensymed_symbol_5 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_4 = gensymed_symbol_4 << gensymed_symbol_5;
		    gensymed_symbol_3 = gensymed_symbol_3 & gensymed_symbol_4;
		    temp_2 = (SI_Long)0L < gensymed_symbol_3;
		}
		else
		    temp_2 = TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_2 =  !temp_2;
	    if (temp_2);
	    else {
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(ISVREF(ISVREF(connection_post,
			(SI_Long)1L),(SI_Long)1L),Class_description_gkbprop);
		temp_2 =  !(gensymed_symbol ? TRUEP(memq_function(class_1,
			ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil));
	    }
	    if (temp_2) {
		svref_new_value_1 = IFIX(ISVREF(connection_post,
			(SI_Long)5L)) | (SI_Long)1048576L;
		ISVREF(connection_post,(SI_Long)5L) = FIX(svref_new_value_1);
		Entities_to_be_excluded_qm = eval_cons_1(connection_post,
			Entities_to_be_excluded_qm);
		if (Nil) {
		    svref_new_value_1 = IFIX(ISVREF(connection_post,
			    (SI_Long)5L)) | (SI_Long)1048576L;
		    ISVREF(connection_post,(SI_Long)5L) = 
			    FIX(svref_new_value_1);
		    Entities_to_be_excluded_qm = 
			    eval_cons_1(connection_post,
			    Entities_to_be_excluded_qm);
		    svref_new_value_1 = IFIX(ISVREF(Nil,(SI_Long)7L)) | 
			    (SI_Long)512L;
		    ISVREF(Nil,(SI_Long)7L) = FIX(svref_new_value_1);
		    Connections_to_be_excluded_qm = eval_cons_1(Nil,
			    Connections_to_be_excluded_qm);
		}
		name_or_names = 
			get_lookup_slot_value_given_default(connection_post,
			Qname_or_names_for_frame,Nil);
		cp_list = Nil;
		cp_list_tail = Nil;
		if (name_or_names) {
		    names_sic = name_or_names;
		    name = Nil;
		  next_loop_13:
		    name = CONSP(names_sic) ? CAR(names_sic) : names_sic;
		    if ( !TRUEP(name))
			goto end_loop_13;
		    names_sic_1 = lookup_kb_specific_property_value(name,
			    Frame_or_frames_with_this_name_kbprop);
		    frame = Nil;
		  next_loop_14:
		    frame = CONSP(names_sic_1) ? CAR(names_sic_1) : 
			    names_sic_1;
		    if ( !TRUEP(frame))
			goto end_loop_14;
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Connection_post_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_3 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_4 = (SI_Long)1L;
			gensymed_symbol_5 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_4 = gensymed_symbol_4 << 
				gensymed_symbol_5;
			gensymed_symbol_3 = gensymed_symbol_3 & 
				gensymed_symbol_4;
			temp_2 = (SI_Long)0L < gensymed_symbol_3;
		    }
		    else
			temp_2 = TRUEP(Nil);
		    if (temp_2 ?  !TRUEP(memq_function(frame,cp_list)) : 
			    TRUEP(Nil)) {
			gensymed_symbol = frame;
			gensymed_symbol = gensym_cons_1(gensymed_symbol,Nil);
			if (cp_list) {
			    if ( !TRUEP(cp_list_tail))
				cp_list_tail = last(cp_list,_);
			    M_CDR(cp_list_tail) = gensymed_symbol;
			}
			else
			    cp_list = gensymed_symbol;
			cp_list_tail = gensymed_symbol;
		    }
		    names_sic_1 = CONSP(names_sic_1) ? CDR(names_sic_1) : Nil;
		    goto next_loop_14;
		  end_loop_14:;
		    names_sic = CONSP(names_sic) ? CDR(names_sic) : Nil;
		    goto next_loop_13;
		  end_loop_13:;
		}
		else
		    cp_list = gensym_cons_1(connection_post,Nil);
		cp = Nil;
		ab_loop_list__1 = cp_list;
	      next_loop_15:
		if ( !TRUEP(ab_loop_list__1))
		    goto end_loop_15;
		cp = M_CAR(ab_loop_list__1);
		ab_loop_list__1 = M_CDR(ab_loop_list__1);
		superior_connection_and_end = 
			get_lookup_slot_value_given_default(cp,
			Qsuperior_connection_cache,Nil);
		temp_1 = cp;
		temp = directionality_qm;
		if (temp);
		else
		    temp = Nil;
		search_for_directly_connected_entities_rec(temp_1,class_1,
			temp,also_get_port_and_direction_info_qm,
			required_connection_directionality_for_inverse_role_service_qm,
			do_not_stop_search_at_connections_qm);
		if (superior_connection_and_end &&  !TRUEP(Nil)) {
		    superior_connection = CDR(superior_connection_and_end);
		    superior_connection_frame = Nil;
		    connection_end = CAR(superior_connection_and_end);
		    required_direction_qm = Nil;
		    if (required_direction_qm);
		    else {
			required_direction_qm = directionality_qm;
			if (required_direction_qm);
			else
			    required_direction_qm = Nil;
		    }
		    direction_to_try = Qinput;
		    superior_connection_frame = ISVREF(superior_connection,
			    (SI_Long)1L);
		  next_loop_16:
		    if ( !TRUEP(Nil) && ((SI_Long)0L != 
			    (IFIX(ISVREF(superior_connection,(SI_Long)7L)) 
			    & (SI_Long)1L) ||  
			    !TRUEP(required_direction_qm)) || ( 
			    !TRUEP(Nil) ||  !((SI_Long)0L != 
			    (IFIX(ISVREF(superior_connection,(SI_Long)7L)) 
			    & (SI_Long)1L))) && EQ(required_direction_qm,
			    direction_to_try) && (EQ(direction_to_try,
			    Qinput) ? EQ(connection_end,Qoutput) : 
			    EQ(connection_end,Qinput))) {
			if (SIMPLE_VECTOR_P(superior_connection_frame) && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(superior_connection_frame)) 
				> (SI_Long)2L &&  
				!EQ(ISVREF(superior_connection_frame,
				(SI_Long)1L),Qavailable_frame_vector)) {
			    x2 = ISVREF(superior_connection_frame,(SI_Long)1L);
			    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				    (SI_Long)0L),
				    Qg2_defstruct_structure_name_class_description_g2_struct) 
				    ? TRUEP(x2) : TRUEP(Qnil);
			}
			else
			    temp_2 = TRUEP(Nil);
			temp_2 =  !(temp_2 ? 
				TRUEP(ISVREF(ISVREF(superior_connection_frame,
				(SI_Long)1L),(SI_Long)16L)) : TRUEP(Nil));
			if (temp_2);
			else
			    temp_2 = 
				    TRUEP(serve_item_p(superior_connection_frame));
		    }
		    else
			temp_2 = TRUEP(Nil);
		    if (temp_2)
			search_for_directly_connected_entities_for_connection(EQ(direction_to_try,
				Qinput) ? ISVREF(superior_connection,
				(SI_Long)2L) : ISVREF(superior_connection,
				(SI_Long)3L),class_1,superior_connection,
				required_direction_qm,
				also_get_port_and_direction_info_qm,Nil,
				required_connection_directionality_for_inverse_role_service_qm,
				do_not_stop_search_at_connections_qm);
		    if (EQ(direction_to_try,Qoutput))
			goto end_loop_16;
		    superior_connection_frame = ISVREF(superior_connection,
			    (SI_Long)1L);
		    direction_to_try = Qoutput;
		    goto next_loop_16;
		  end_loop_16:;
		}
		goto next_loop_15;
	      end_loop_15:;
		reclaim_gensym_list_1(cp_list);
	    }
	    else
		note_entity_found_in_directly_connected_search(connection_post,
			connection,also_get_port_and_direction_info_qm);
	}
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qboth;               /* both */

static Object Qport_names;         /* port-names */

/* ADD-PORT-AND-DIRECTION-INFO-TRIPLE */
Object add_port_and_direction_info_triple(entity,connection,
	    port_and_direction_info_qm)
    Object entity, connection, port_and_direction_info_qm;
{
    Object port_names, direction_of_connection_for_entity, triple_to_add;
    Object triple, ab_loop_list_, temp;

    x_note_fn_call(149,113);
    port_names = get_port_names_for_connection(entity,connection);
    direction_of_connection_for_entity =  !((SI_Long)0L != 
	    (IFIX(ISVREF(connection,(SI_Long)7L)) & (SI_Long)1L)) ? 
	    (EQ(ISVREF(connection,(SI_Long)2L),entity) ? Qinput : Qoutput) 
	    : Nil;
    triple_to_add = eval_list_3(entity,port_names,
	    direction_of_connection_for_entity);
    if (EQ(port_and_direction_info_qm,Qboth)) {
	Entities_or_triples_found_in_search = eval_cons_1(triple_to_add,
		Entities_or_triples_found_in_search);
	return VALUES_1(Entities_or_triples_found_in_search);
    }
    else {
	triple = Nil;
	ab_loop_list_ = Entities_or_triples_found_in_search;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	triple = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(entity,CAR(triple))) {
	    if (EQ(port_and_direction_info_qm,Qport_names)) {
		temp = SECOND(triple);
		if (EQUAL(port_names,temp)) {
		    reclaim_eval_tree_1(triple_to_add);
		    return VALUES_0();
		}
	    }
	    else if (EQ(direction_of_connection_for_entity,THIRD(triple))) {
		reclaim_eval_tree_1(triple_to_add);
		return VALUES_0();
	    }
	}
	goto next_loop;
      end_loop:
	Entities_or_triples_found_in_search = eval_cons_1(triple_to_add,
		Entities_or_triples_found_in_search);
	return VALUES_1(Qnil);
    }
}

/* GET-PORT-NAMES-FOR-CONNECTION */
Object get_port_names_for_connection(block,connection)
    Object block, connection;
{
    Object gensymed_symbol, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp, temp_1, entry_hash, connection_item;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(149,114);
    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)6L)) : Nil;
    skip_list = CDR(gensymed_symbol);
    key_value = connection;
    key_hash_value = SXHASH_SYMBOL_1(connection) & IFIX(Most_positive_fixnum);
    bottom_level = (SI_Long)0L;
    marked = Nil;
    pred = M_CAR(skip_list);
    curr = Nil;
    succ = Nil;
    level = (SI_Long)7L;
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
    connection_item = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	    (SI_Long)3L) : Nil) : Nil;
    if (connection_item) {
	temp_1 = get_direction_of_connection(2,connection,block);
	temp_1 = copy_list_using_eval_conses_1(EQ(temp_1,Qinput) ? 
		ISVREF(connection_item,(SI_Long)2L) : 
		ISVREF(connection_item,(SI_Long)1L));
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

static Object string_constant_15;  /* " connected to" */

/* ROLE-PRINT-CONNECTED-TO */
Object role_print_connected_to(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,115);
    GENSYM_RETURN_ONE(print_standard_two_element_role(role,
	    local_variable_qm,string_constant_15));
    return VALUES_1(Nil);
}

static Object Qconnected_to;       /* connected-to */

/* SERVE-FIRST-CONNECTED-TO */
Object serve_first_connected_to(role,domain)
    Object role, domain;
{
    Object class_1, class_description, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, domain_cache_qm;
    Object role_cache_qm, specific_cache_qm, gensymed_symbol_4;
    char temp;

    x_note_fn_call(149,116);
    class_1 = M_CAR(M_CDR(role));
    class_description = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    if (class_description && ISVREF(class_description,(SI_Long)16L)) {
	gensymed_symbol = domain;
	gensymed_symbol_1 = Qconnected_to;
	gensymed_symbol_2 = class_1;
	gensymed_symbol_3 = Role_caching_enabled_qm ? ( 
		!((IFIX(Current_computation_flags) & (SI_Long)16L) != 
		(SI_Long)0L) ? T : Nil) : Qnil;
	domain_cache_qm = Nil;
	role_cache_qm = Nil;
	specific_cache_qm = Nil;
	if (gensymed_symbol_3) {
	    domain_cache_qm = 
		    get_lookup_slot_value_given_default(gensymed_symbol,
		    Qrole_cache,Nil);
	    role_cache_qm = assq_function(gensymed_symbol_1,domain_cache_qm);
	    specific_cache_qm = equal_assoc(gensymed_symbol_2,
		    CDR(role_cache_qm));
	    temp = TRUEP(specific_cache_qm);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    return serve_all_unreprocessed_cached_frames(CDR(specific_cache_qm));
	else {
	    gensymed_symbol_4 = 
		    search_for_directly_connected_entities(domain,class_1,
		    Nil,Nil,Nil,Nil,Nil,Nil);
	    if (gensymed_symbol_3)
		return add_to_cache_and_serve(gensymed_symbol,
			gensymed_symbol_1,
			copy_tree_using_eval_conses_1(gensymed_symbol_2),
			gensymed_symbol_4);
	    else
		return serve_all_unreprocessed_frames(gensymed_symbol_4);
	}
    }
    else {
	warn_of_bad_connected_to_class(class_1,domain);
	return VALUES_3(Nil,Nil,Nil);
    }
}

static Object string_constant_16;  /* "In a reference to a ~a connected to ~nf, ~nf is not a ~a, so no connection ~
				    *      search could be performed."
				    */

static Object string_constant_17;  /* "class that can have connections" */

static Object string_constant_18;  /* "defined class" */

/* WARN-OF-BAD-CONNECTED-TO-CLASS */
Object warn_of_bad_connected_to_class(class_1,domain)
    Object class_1, domain;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(149,117);
    if ((SI_Long)1L <= IFIX(Warning_message_level)) {
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
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
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
	return give_warning_1(6,FIX((SI_Long)1L),string_constant_16,
		class_1,domain,domain,gensymed_symbol && 
		ISVREF(gensymed_symbol,(SI_Long)16L) ? string_constant_17 :
		 string_constant_18);
    }
    else
	return VALUES_1(Nil);
}

/* SERVE-FIRST-CONNECTED-TO-INVERSE */
Object serve_first_connected_to_inverse(object,quantifier,role,
	    domain_designation)
    Object object, quantifier, role, domain_designation;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3, gensymed_symbol_4, role_argument, quantifier_1;
    Object designation, domain_cache_qm, role_cache_qm, specific_cache_qm;
    Object frame_or_frames, frame, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, connected_entities, entities_to_serve, entity;
    Object name_or_names, last_1, next_qm, temp_1, svref_arg_2, class_qm;
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp_2;
    Object temp_3, entry_hash, tail, head, new_cons, svref_new_value;
    Object gensymed_symbol_5, gensymed_symbol_6, global_properties;
    Object kb_properties, kb_specific_value, resulting_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Object result;

    x_note_fn_call(149,118);
    gensymed_symbol = object;
    gensymed_symbol_1 = quantifier;
    gensymed_symbol_2 = role;
    gensymed_symbol_3 = domain_designation;
    gensymed_symbol_4 = Role_caching_enabled_qm ? ( 
	    !((IFIX(Current_computation_flags) & (SI_Long)16L) != 
	    (SI_Long)0L) ? T : Nil) : Qnil;
    if (gensymed_symbol_4) {
	role_argument = CDR(gensymed_symbol_2);
	quantifier_1 = gensymed_symbol_1;
	designation = gensymed_symbol_3;
	gensymed_symbol_4 = eval_cons_1(role_argument,
		eval_cons_1(quantifier_1,designation));
    }
    else
	gensymed_symbol_4 = Nil;
    gensymed_symbol_1 = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = Role_caching_enabled_qm ? ( 
	    !((IFIX(Current_computation_flags) & (SI_Long)16L) != 
	    (SI_Long)0L) ? T : Nil) : Qnil;
    domain_cache_qm = Nil;
    role_cache_qm = Nil;
    specific_cache_qm = Nil;
    if (gensymed_symbol_2) {
	domain_cache_qm = 
		get_lookup_slot_value_given_default(gensymed_symbol,
		Qrole_cache,Nil);
	role_cache_qm = assq_function(gensymed_symbol_1,domain_cache_qm);
	specific_cache_qm = equal_assoc(gensymed_symbol_4,CDR(role_cache_qm));
	temp = TRUEP(specific_cache_qm);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	result = serve_all_unreprocessed_cached_frames(CDR(specific_cache_qm));
    else {
	if (SYMBOLP(domain_designation)) {
	    frame_or_frames = 
		    lookup_kb_specific_property_value(domain_designation,
		    Frame_or_frames_with_this_name_kbprop);
	    if (LISTP(frame_or_frames)) {
		frame = Nil;
		ab_loop_list_ = frame_or_frames;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ab_loopvar__2 = Nil;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		frame = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		ab_loopvar__2 = 
			search_for_directly_connected_entities(object,
			ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)1L),Nil,
			Nil,Nil,Nil,Nil,Nil);
		if (ab_loopvar__2) {
		    if (ab_loopvar__1)
			M_CDR(ab_loopvar__1) = ab_loopvar__2;
		    else
			ab_loopvar_ = ab_loopvar__2;
		    ab_loopvar__1 = last(ab_loopvar__2,_);
		}
		goto next_loop;
	      end_loop:
		connected_entities = ab_loopvar_;
		goto end_1;
		connected_entities = Qnil;
	      end_1:;
	    }
	    else
		connected_entities = 
			search_for_directly_connected_entities(object,
			ISVREF(ISVREF(frame_or_frames,(SI_Long)1L),
			(SI_Long)1L),Nil,Nil,Nil,Nil,Nil,Nil);
	    entities_to_serve = Nil;
	    entity = Nil;
	    ab_loop_list_ = connected_entities;
	    name_or_names = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    entity = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    name_or_names = get_lookup_slot_value_given_default(entity,
		    Qname_or_names_for_frame,Nil);
	    if ((CONSP(name_or_names) ? 
		    TRUEP(memq_function(domain_designation,name_or_names)) 
		    : EQ(domain_designation,name_or_names)) && ( 
		    !EQ(quantifier,Qthe) || unique_value_of_role_p(object,
		    role,entity)))
		entities_to_serve = eval_cons_1(entity,entities_to_serve);
	    goto next_loop_1;
	  end_loop_1:;
	    if (connected_entities) {
		last_1 = connected_entities;
		next_qm = Nil;
	      next_loop_2:
		next_qm = M_CDR(last_1);
		if ( !TRUEP(next_qm))
		    goto end_loop_2;
		inline_note_reclaim_cons(last_1,Qeval);
		last_1 = next_qm;
		goto next_loop_2;
	      end_loop_2:
		inline_note_reclaim_cons(last_1,Qeval);
		if (ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_eval_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = connected_entities;
		    temp_1 = Available_eval_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = last_1;
		}
		else {
		    temp_1 = Available_eval_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = connected_entities;
		    temp_1 = Available_eval_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = last_1;
		}
		M_CDR(last_1) = Nil;
	    }
	    gensymed_symbol_3 = entities_to_serve;
	}
	else {
	    class_qm = atomic_class_element_of_designation(domain_designation);
	    if (class_qm) {
		skip_list = CDR(Symbol_properties_table);
		key_value = class_qm;
		key_hash_value = SXHASH_SYMBOL_1(class_qm) & 
			IFIX(Most_positive_fixnum);
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
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp_3 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_2,temp_3);
		MVS_2(result,succ,marked);
	      next_loop_5:
		if ( !TRUEP(marked))
		    goto end_loop_4;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp_3 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_2,temp_3);
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
		    goto end_2;
		goto next_loop_4;
	      end_loop_5:
	      end_2:
		level = level - (SI_Long)1L;
		goto next_loop_3;
	      end_loop_3:;
		gensymed_symbol_3 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if ( !TRUEP(gensymed_symbol_3)) {
		    gensymed_symbol_3 = class_qm;
		    temp_2 = Symbol_properties_table;
		    temp_3 = FIX(SXHASH_SYMBOL_1(gensymed_symbol_3) & 
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
			temp_1 = Available_lookup_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp_1,svref_arg_2) = svref_new_value;
			if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp_1 = Available_lookup_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = Nil;
			}
			gensymed_symbol_5 = new_cons;
		    }
		    else
			gensymed_symbol_5 = Nil;
		    if ( !TRUEP(gensymed_symbol_5))
			gensymed_symbol_5 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_5) = Qsymbol_properties_hash_table;
		    new_cons = ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp_1 = Available_lookup_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp_1,svref_arg_2) = svref_new_value;
			if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp_1 = Available_lookup_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = Nil;
			}
			gensymed_symbol_6 = new_cons;
		    }
		    else
			gensymed_symbol_6 = Nil;
		    if ( !TRUEP(gensymed_symbol_6))
			gensymed_symbol_6 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_6) = head;
		    M_CDR(gensymed_symbol_6) = tail;
		    inline_note_allocate_cons(gensymed_symbol_6,Qlookup);
		    M_CDR(gensymed_symbol_5) = gensymed_symbol_6;
		    inline_note_allocate_cons(gensymed_symbol_5,Qlookup);
		    gensymed_symbol_3 = set_skip_list_entry(temp_2,
			    FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol_3,
			    temp_3,gensymed_symbol_5);
		}
		global_properties = gensymed_symbol_3;
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
	      next_loop_6:
		if (level < ab_loop_bind_)
		    goto end_loop_6;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_7:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp_3 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_2,temp_3);
		MVS_2(result,succ,marked);
	      next_loop_8:
		if ( !TRUEP(marked))
		    goto end_loop_7;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp_3 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_2,temp_3);
		MVS_2(result,succ,marked);
		goto next_loop_8;
	      end_loop_7:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
		  next_loop_9:
		    if (level < ab_loop_bind_)
			goto end_loop_9;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_10:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp_3 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_2,temp_3);
		    MVS_2(result,succ,marked);
		  next_loop_11:
		    if ( !TRUEP(marked))
			goto end_loop_10;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp_3 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_2,temp_3);
		    MVS_2(result,succ,marked);
		    goto next_loop_11;
		  end_loop_10:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
		    kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
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
		  next_loop_12:
		    if (level < ab_loop_bind_)
			goto end_loop_12;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_13:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp_3 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_2,temp_3);
		    MVS_2(result,succ,marked);
		  next_loop_14:
		    if ( !TRUEP(marked))
			goto end_loop_13;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp_3 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_2,temp_3);
		    MVS_2(result,succ,marked);
		    goto next_loop_14;
		  end_loop_13:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
		    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		gensymed_symbol_3 = resulting_value;
		temp = gensymed_symbol_3 ? TRUEP(ISVREF(gensymed_symbol_3,
			(SI_Long)16L)) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    connected_entities = temp ? 
		    search_for_directly_connected_entities(object,class_qm,
		    Nil,Nil,Nil,Nil,Nil,Nil) : Nil;
	    if ( !EQ(quantifier,Qthe))
		gensymed_symbol_3 = connected_entities;
	    else {
		entities_to_serve = Nil;
		entity = Nil;
		ab_loop_list_ = connected_entities;
	      next_loop_15:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_15;
		entity = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if (unique_value_of_role_p(object,role,entity))
		    entities_to_serve = eval_cons_1(entity,entities_to_serve);
		goto next_loop_15;
	      end_loop_15:;
		if (connected_entities) {
		    last_1 = connected_entities;
		    next_qm = Nil;
		  next_loop_16:
		    next_qm = M_CDR(last_1);
		    if ( !TRUEP(next_qm))
			goto end_loop_16;
		    inline_note_reclaim_cons(last_1,Qeval);
		    last_1 = next_qm;
		    goto next_loop_16;
		  end_loop_16:
		    inline_note_reclaim_cons(last_1,Qeval);
		    if (ISVREF(Available_eval_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_1 = ISVREF(Available_eval_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_1) = connected_entities;
			temp_1 = Available_eval_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_1,svref_arg_2) = last_1;
		    }
		    else {
			temp_1 = Available_eval_conses_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_1,svref_arg_2) = connected_entities;
			temp_1 = Available_eval_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_1,svref_arg_2) = last_1;
		    }
		    M_CDR(last_1) = Nil;
		}
		gensymed_symbol_3 = entities_to_serve;
	    }
	}
	if (gensymed_symbol_2)
	    result = add_to_cache_and_serve(gensymed_symbol,
		    gensymed_symbol_1,
		    copy_tree_using_eval_conses_1(gensymed_symbol_4),
		    gensymed_symbol_3);
	else
	    result = serve_all_unreprocessed_frames(gensymed_symbol_3);
    }
    MVS_3(result,gensymed_symbol_1,gensymed_symbol_2,gensymed_symbol_3);
    if (gensymed_symbol_4) {
	reclaim_eval_cons_1(CDR(gensymed_symbol_4));
	reclaim_eval_cons_1(gensymed_symbol_4);
    }
    return VALUES_3(gensymed_symbol_1,gensymed_symbol_2,gensymed_symbol_3);
}

static Object array_constant_4;    /* # */

/* ROLE-PRINT-AT-PORT */
Object role_print_at_port(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,119);
    twrite_symbol(1,THIRD(role));
    if (local_variable_qm) {
	twrite(string_constant);
	twrite(local_variable_qm);
    }
    twrite_beginning_of_wide_string(array_constant_4,FIX((SI_Long)18L));
    twrite_symbol(1,SECOND(role));
    GENSYM_RETURN_ONE(twrite_beginning_of_wide_string(array_constant_1,
	    FIX((SI_Long)3L)));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-AT-PORT */
Object serve_first_at_port(role,domain)
    Object role, domain;
{
    Object class_1, class_description, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, domain_cache_qm;
    Object role_cache_qm, specific_cache_qm, gensymed_symbol_4;
    char temp;

    x_note_fn_call(149,120);
    class_1 = THIRD(role);
    class_description = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    if (class_description && ISVREF(class_description,(SI_Long)16L)) {
	gensymed_symbol = domain;
	gensymed_symbol_1 = FIRST(role);
	gensymed_symbol_2 = CDR(role);
	gensymed_symbol_3 = Role_caching_enabled_qm ? ( 
		!((IFIX(Current_computation_flags) & (SI_Long)16L) != 
		(SI_Long)0L) ? T : Nil) : Qnil;
	domain_cache_qm = Nil;
	role_cache_qm = Nil;
	specific_cache_qm = Nil;
	if (gensymed_symbol_3) {
	    domain_cache_qm = 
		    get_lookup_slot_value_given_default(gensymed_symbol,
		    Qrole_cache,Nil);
	    role_cache_qm = assq_function(gensymed_symbol_1,domain_cache_qm);
	    specific_cache_qm = equal_assoc(gensymed_symbol_2,
		    CDR(role_cache_qm));
	    temp = TRUEP(specific_cache_qm);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    return serve_all_unreprocessed_cached_frames(CDR(specific_cache_qm));
	else {
	    gensymed_symbol_4 = 
		    search_for_directly_connected_entities(domain,class_1,
		    SECOND(role),Nil,Nil,Nil,Nil,Nil);
	    if (gensymed_symbol_3)
		return add_to_cache_and_serve(gensymed_symbol,
			gensymed_symbol_1,
			copy_tree_using_eval_conses_1(gensymed_symbol_2),
			gensymed_symbol_4);
	    else
		return serve_all_unreprocessed_frames(gensymed_symbol_4);
	}
    }
    else {
	warn_of_bad_connected_to_class(class_1,domain);
	return VALUES_3(Nil,Nil,Nil);
    }
}

/* SERVE-FIRST-AT-PORT-INVERSE */
Object serve_first_at_port_inverse(object,quantifier,role,domain_designation)
    Object object, quantifier, role, domain_designation;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3, gensymed_symbol_4, role_argument, quantifier_1;
    Object designation, domain_cache_qm, role_cache_qm, specific_cache_qm;
    Object classes_qm, port_name, class_1, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, connected_entities, entities_to_serve;
    Object entity, entity_entry, last_1, next_qm, temp_1, svref_arg_2;
    char temp;
    Object result;

    x_note_fn_call(149,121);
    gensymed_symbol = object;
    gensymed_symbol_1 = quantifier;
    gensymed_symbol_2 = role;
    gensymed_symbol_3 = domain_designation;
    gensymed_symbol_4 = Role_caching_enabled_qm ? ( 
	    !((IFIX(Current_computation_flags) & (SI_Long)16L) != 
	    (SI_Long)0L) ? T : Nil) : Qnil;
    if (gensymed_symbol_4) {
	role_argument = CDR(gensymed_symbol_2);
	quantifier_1 = gensymed_symbol_1;
	designation = gensymed_symbol_3;
	gensymed_symbol_4 = eval_cons_1(role_argument,
		eval_cons_1(quantifier_1,designation));
    }
    else
	gensymed_symbol_4 = Nil;
    gensymed_symbol_1 = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = Role_caching_enabled_qm ? ( 
	    !((IFIX(Current_computation_flags) & (SI_Long)16L) != 
	    (SI_Long)0L) ? T : Nil) : Qnil;
    domain_cache_qm = Nil;
    role_cache_qm = Nil;
    specific_cache_qm = Nil;
    if (gensymed_symbol_2) {
	domain_cache_qm = 
		get_lookup_slot_value_given_default(gensymed_symbol,
		Qrole_cache,Nil);
	role_cache_qm = assq_function(gensymed_symbol_1,domain_cache_qm);
	specific_cache_qm = equal_assoc(gensymed_symbol_4,CDR(role_cache_qm));
	temp = TRUEP(specific_cache_qm);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	result = serve_all_unreprocessed_cached_frames(CDR(specific_cache_qm));
    else {
	classes_qm = get_classes_given_designation(domain_designation);
	port_name = SECOND(role);
	class_1 = Nil;
	ab_loop_list_ = classes_qm;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	class_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = search_for_directly_connected_entities(object,
		class_1,Nil,Nil,Nil,Qport_names,Nil,Nil);
	if (ab_loopvar__2) {
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = last(ab_loopvar__2,_);
	}
	goto next_loop;
      end_loop:
	connected_entities = ab_loopvar_;
	goto end_1;
	connected_entities = Qnil;
      end_1:;
	entities_to_serve = Nil;
	entity = Nil;
	entity_entry = Nil;
	ab_loop_list_ = connected_entities;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	entity_entry = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (memq_function(port_name,SECOND(entity_entry))) {
	    entity = FIRST(entity_entry);
	    if (designation_could_denote_item_p(domain_designation,entity) 
		    && ( !EQ(quantifier,Qthe) || 
		    unique_value_of_role_p(object,role,entity)))
		entities_to_serve = eval_cons_1(entity,entities_to_serve);
	}
	goto next_loop_1;
      end_loop_1:;
	if (classes_qm) {
	    last_1 = classes_qm;
	    next_qm = Nil;
	  next_loop_2:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop_2;
	    inline_note_reclaim_cons(last_1,Qeval);
	    last_1 = next_qm;
	    goto next_loop_2;
	  end_loop_2:
	    inline_note_reclaim_cons(last_1,Qeval);
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = classes_qm;
		temp_1 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = last_1;
	    }
	    else {
		temp_1 = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = classes_qm;
		temp_1 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = last_1;
	    }
	    M_CDR(last_1) = Nil;
	}
	reclaim_eval_tree_1(connected_entities);
	gensymed_symbol_3 = entities_to_serve;
	if (gensymed_symbol_2)
	    result = add_to_cache_and_serve(gensymed_symbol,
		    gensymed_symbol_1,
		    copy_tree_using_eval_conses_1(gensymed_symbol_4),
		    gensymed_symbol_3);
	else
	    result = serve_all_unreprocessed_frames(gensymed_symbol_3);
    }
    MVS_3(result,gensymed_symbol_1,gensymed_symbol_2,gensymed_symbol_3);
    if (gensymed_symbol_4) {
	reclaim_eval_cons_1(CDR(gensymed_symbol_4));
	reclaim_eval_cons_1(gensymed_symbol_4);
    }
    return VALUES_3(gensymed_symbol_1,gensymed_symbol_2,gensymed_symbol_3);
}

static Object string_constant_19;  /* " connected at an input of" */

/* ROLE-PRINT-AT-AN-INPUT */
Object role_print_at_an_input(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,122);
    GENSYM_RETURN_ONE(print_standard_two_element_role(role,
	    local_variable_qm,string_constant_19));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-AT-AN-INPUT */
Object serve_first_at_an_input(role,domain)
    Object role, domain;
{
    Object class_1, class_description, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, domain_cache_qm;
    Object role_cache_qm, specific_cache_qm, gensymed_symbol_4;
    char temp;

    x_note_fn_call(149,123);
    class_1 = SECOND(role);
    class_description = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    if (class_description && ISVREF(class_description,(SI_Long)16L)) {
	gensymed_symbol = domain;
	gensymed_symbol_1 = FIRST(role);
	gensymed_symbol_2 = class_1;
	gensymed_symbol_3 = Role_caching_enabled_qm ? ( 
		!((IFIX(Current_computation_flags) & (SI_Long)16L) != 
		(SI_Long)0L) ? T : Nil) : Qnil;
	domain_cache_qm = Nil;
	role_cache_qm = Nil;
	specific_cache_qm = Nil;
	if (gensymed_symbol_3) {
	    domain_cache_qm = 
		    get_lookup_slot_value_given_default(gensymed_symbol,
		    Qrole_cache,Nil);
	    role_cache_qm = assq_function(gensymed_symbol_1,domain_cache_qm);
	    specific_cache_qm = equal_assoc(gensymed_symbol_2,
		    CDR(role_cache_qm));
	    temp = TRUEP(specific_cache_qm);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    return serve_all_unreprocessed_cached_frames(CDR(specific_cache_qm));
	else {
	    gensymed_symbol_4 = 
		    search_for_directly_connected_entities(domain,class_1,
		    Nil,Qinput,Qinput,Nil,Nil,Nil);
	    if (gensymed_symbol_3)
		return add_to_cache_and_serve(gensymed_symbol,
			gensymed_symbol_1,
			copy_tree_using_eval_conses_1(gensymed_symbol_2),
			gensymed_symbol_4);
	    else
		return serve_all_unreprocessed_frames(gensymed_symbol_4);
	}
    }
    else {
	warn_of_bad_connected_to_class(class_1,domain);
	return VALUES_3(Nil,Nil,Nil);
    }
}

static Object Qdirectionality;     /* directionality */

/* SERVE-FIRST-AT-AN-INPUT-INVERSE */
Object serve_first_at_an_input_inverse(object,quantifier,role,
	    domain_designation)
    Object object, quantifier, role, domain_designation;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3, gensymed_symbol_4, role_argument, quantifier_1;
    Object designation, domain_cache_qm, role_cache_qm, specific_cache_qm;
    Object classes_qm, class_1, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, connected_entities, entities_to_serve, entity;
    Object entity_entry, last_1, next_qm, temp_1, svref_arg_2;
    char temp;
    Object result;

    x_note_fn_call(149,124);
    gensymed_symbol = object;
    gensymed_symbol_1 = quantifier;
    gensymed_symbol_2 = role;
    gensymed_symbol_3 = domain_designation;
    gensymed_symbol_4 = Role_caching_enabled_qm ? ( 
	    !((IFIX(Current_computation_flags) & (SI_Long)16L) != 
	    (SI_Long)0L) ? T : Nil) : Qnil;
    if (gensymed_symbol_4) {
	role_argument = CDR(gensymed_symbol_2);
	quantifier_1 = gensymed_symbol_1;
	designation = gensymed_symbol_3;
	gensymed_symbol_4 = eval_cons_1(role_argument,
		eval_cons_1(quantifier_1,designation));
    }
    else
	gensymed_symbol_4 = Nil;
    gensymed_symbol_1 = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = Role_caching_enabled_qm ? ( 
	    !((IFIX(Current_computation_flags) & (SI_Long)16L) != 
	    (SI_Long)0L) ? T : Nil) : Qnil;
    domain_cache_qm = Nil;
    role_cache_qm = Nil;
    specific_cache_qm = Nil;
    if (gensymed_symbol_2) {
	domain_cache_qm = 
		get_lookup_slot_value_given_default(gensymed_symbol,
		Qrole_cache,Nil);
	role_cache_qm = assq_function(gensymed_symbol_1,domain_cache_qm);
	specific_cache_qm = equal_assoc(gensymed_symbol_4,CDR(role_cache_qm));
	temp = TRUEP(specific_cache_qm);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	result = serve_all_unreprocessed_cached_frames(CDR(specific_cache_qm));
    else {
	classes_qm = get_classes_given_designation(domain_designation);
	class_1 = Nil;
	ab_loop_list_ = classes_qm;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	class_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = search_for_directly_connected_entities(object,
		class_1,Nil,Nil,Qoutput,Qdirectionality,Nil,Nil);
	if (ab_loopvar__2) {
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = last(ab_loopvar__2,_);
	}
	goto next_loop;
      end_loop:
	connected_entities = ab_loopvar_;
	goto end_1;
	connected_entities = Qnil;
      end_1:;
	entities_to_serve = Nil;
	entity = Nil;
	entity_entry = Nil;
	ab_loop_list_ = connected_entities;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	entity_entry = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(THIRD(entity_entry),Qinput)) {
	    entity = FIRST(entity_entry);
	    if (designation_could_denote_item_p(domain_designation,entity) 
		    && ( !EQ(quantifier,Qthe) || 
		    unique_value_of_role_p(object,role,entity)))
		entities_to_serve = eval_cons_1(entity,entities_to_serve);
	}
	goto next_loop_1;
      end_loop_1:;
	if (classes_qm) {
	    last_1 = classes_qm;
	    next_qm = Nil;
	  next_loop_2:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop_2;
	    inline_note_reclaim_cons(last_1,Qeval);
	    last_1 = next_qm;
	    goto next_loop_2;
	  end_loop_2:
	    inline_note_reclaim_cons(last_1,Qeval);
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = classes_qm;
		temp_1 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = last_1;
	    }
	    else {
		temp_1 = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = classes_qm;
		temp_1 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = last_1;
	    }
	    M_CDR(last_1) = Nil;
	}
	reclaim_eval_tree_1(connected_entities);
	gensymed_symbol_3 = entities_to_serve;
	if (gensymed_symbol_2)
	    result = add_to_cache_and_serve(gensymed_symbol,
		    gensymed_symbol_1,
		    copy_tree_using_eval_conses_1(gensymed_symbol_4),
		    gensymed_symbol_3);
	else
	    result = serve_all_unreprocessed_frames(gensymed_symbol_3);
    }
    MVS_3(result,gensymed_symbol_1,gensymed_symbol_2,gensymed_symbol_3);
    if (gensymed_symbol_4) {
	reclaim_eval_cons_1(CDR(gensymed_symbol_4));
	reclaim_eval_cons_1(gensymed_symbol_4);
    }
    return VALUES_3(gensymed_symbol_1,gensymed_symbol_2,gensymed_symbol_3);
}

static Object string_constant_20;  /* " connected at an output of" */

/* ROLE-PRINT-AT-AN-OUTPUT */
Object role_print_at_an_output(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,125);
    GENSYM_RETURN_ONE(print_standard_two_element_role(role,
	    local_variable_qm,string_constant_20));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-AT-AN-OUTPUT */
Object serve_first_at_an_output(role,domain)
    Object role, domain;
{
    Object class_1, class_description, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, domain_cache_qm;
    Object role_cache_qm, specific_cache_qm, gensymed_symbol_4;
    char temp;

    x_note_fn_call(149,126);
    class_1 = SECOND(role);
    class_description = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    if (class_description && ISVREF(class_description,(SI_Long)16L)) {
	gensymed_symbol = domain;
	gensymed_symbol_1 = FIRST(role);
	gensymed_symbol_2 = class_1;
	gensymed_symbol_3 = Role_caching_enabled_qm ? ( 
		!((IFIX(Current_computation_flags) & (SI_Long)16L) != 
		(SI_Long)0L) ? T : Nil) : Qnil;
	domain_cache_qm = Nil;
	role_cache_qm = Nil;
	specific_cache_qm = Nil;
	if (gensymed_symbol_3) {
	    domain_cache_qm = 
		    get_lookup_slot_value_given_default(gensymed_symbol,
		    Qrole_cache,Nil);
	    role_cache_qm = assq_function(gensymed_symbol_1,domain_cache_qm);
	    specific_cache_qm = equal_assoc(gensymed_symbol_2,
		    CDR(role_cache_qm));
	    temp = TRUEP(specific_cache_qm);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    return serve_all_unreprocessed_cached_frames(CDR(specific_cache_qm));
	else {
	    gensymed_symbol_4 = 
		    search_for_directly_connected_entities(domain,class_1,
		    Nil,Qoutput,Qoutput,Nil,Nil,Nil);
	    if (gensymed_symbol_3)
		return add_to_cache_and_serve(gensymed_symbol,
			gensymed_symbol_1,
			copy_tree_using_eval_conses_1(gensymed_symbol_2),
			gensymed_symbol_4);
	    else
		return serve_all_unreprocessed_frames(gensymed_symbol_4);
	}
    }
    else {
	warn_of_bad_connected_to_class(class_1,domain);
	return VALUES_3(Nil,Nil,Nil);
    }
}

/* SERVE-FIRST-AT-AN-OUTPUT-INVERSE */
Object serve_first_at_an_output_inverse(object,quantifier,role,
	    domain_designation)
    Object object, quantifier, role, domain_designation;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3, gensymed_symbol_4, role_argument, quantifier_1;
    Object designation, domain_cache_qm, role_cache_qm, specific_cache_qm;
    Object classes_qm, class_1, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, connected_entities, entities_to_serve, entity;
    Object entity_entry, last_1, next_qm, temp_1, svref_arg_2;
    char temp;
    Object result;

    x_note_fn_call(149,127);
    gensymed_symbol = object;
    gensymed_symbol_1 = quantifier;
    gensymed_symbol_2 = role;
    gensymed_symbol_3 = domain_designation;
    gensymed_symbol_4 = Role_caching_enabled_qm ? ( 
	    !((IFIX(Current_computation_flags) & (SI_Long)16L) != 
	    (SI_Long)0L) ? T : Nil) : Qnil;
    if (gensymed_symbol_4) {
	role_argument = CDR(gensymed_symbol_2);
	quantifier_1 = gensymed_symbol_1;
	designation = gensymed_symbol_3;
	gensymed_symbol_4 = eval_cons_1(role_argument,
		eval_cons_1(quantifier_1,designation));
    }
    else
	gensymed_symbol_4 = Nil;
    gensymed_symbol_1 = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = Role_caching_enabled_qm ? ( 
	    !((IFIX(Current_computation_flags) & (SI_Long)16L) != 
	    (SI_Long)0L) ? T : Nil) : Qnil;
    domain_cache_qm = Nil;
    role_cache_qm = Nil;
    specific_cache_qm = Nil;
    if (gensymed_symbol_2) {
	domain_cache_qm = 
		get_lookup_slot_value_given_default(gensymed_symbol,
		Qrole_cache,Nil);
	role_cache_qm = assq_function(gensymed_symbol_1,domain_cache_qm);
	specific_cache_qm = equal_assoc(gensymed_symbol_4,CDR(role_cache_qm));
	temp = TRUEP(specific_cache_qm);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	result = serve_all_unreprocessed_cached_frames(CDR(specific_cache_qm));
    else {
	classes_qm = get_classes_given_designation(domain_designation);
	class_1 = Nil;
	ab_loop_list_ = classes_qm;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	class_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = search_for_directly_connected_entities(object,
		class_1,Nil,Nil,Qinput,Qdirectionality,Nil,Nil);
	if (ab_loopvar__2) {
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = last(ab_loopvar__2,_);
	}
	goto next_loop;
      end_loop:
	connected_entities = ab_loopvar_;
	goto end_1;
	connected_entities = Qnil;
      end_1:;
	entities_to_serve = Nil;
	entity = Nil;
	entity_entry = Nil;
	ab_loop_list_ = connected_entities;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	entity_entry = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(THIRD(entity_entry),Qoutput)) {
	    entity = FIRST(entity_entry);
	    if (designation_could_denote_item_p(domain_designation,entity) 
		    && ( !EQ(quantifier,Qthe) || 
		    unique_value_of_role_p(object,role,entity)))
		entities_to_serve = eval_cons_1(entity,entities_to_serve);
	}
	goto next_loop_1;
      end_loop_1:;
	if (classes_qm) {
	    last_1 = classes_qm;
	    next_qm = Nil;
	  next_loop_2:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop_2;
	    inline_note_reclaim_cons(last_1,Qeval);
	    last_1 = next_qm;
	    goto next_loop_2;
	  end_loop_2:
	    inline_note_reclaim_cons(last_1,Qeval);
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = classes_qm;
		temp_1 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = last_1;
	    }
	    else {
		temp_1 = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = classes_qm;
		temp_1 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = last_1;
	    }
	    M_CDR(last_1) = Nil;
	}
	reclaim_eval_tree_1(connected_entities);
	gensymed_symbol_3 = entities_to_serve;
	if (gensymed_symbol_2)
	    result = add_to_cache_and_serve(gensymed_symbol,
		    gensymed_symbol_1,
		    copy_tree_using_eval_conses_1(gensymed_symbol_4),
		    gensymed_symbol_3);
	else
	    result = serve_all_unreprocessed_frames(gensymed_symbol_3);
    }
    MVS_3(result,gensymed_symbol_1,gensymed_symbol_2,gensymed_symbol_3);
    if (gensymed_symbol_4) {
	reclaim_eval_cons_1(CDR(gensymed_symbol_4));
	reclaim_eval_cons_1(gensymed_symbol_4);
    }
    return VALUES_3(gensymed_symbol_1,gensymed_symbol_2,gensymed_symbol_3);
}

/* GET-CLASSES-GIVEN-DESIGNATION */
Object get_classes_given_designation(domain_designation)
    Object domain_designation;
{
    Object frame_or_frames, frame, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, class_qm, skip_list, key_value, marked, pred, curr;
    Object succ, reference, temp, temp_1, entry_hash, gensymed_symbol, tail;
    Object head, new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_1, gensymed_symbol_2, global_properties;
    Object kb_properties, kb_specific_value, resulting_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(149,128);
    if (SYMBOLP(domain_designation)) {
	frame_or_frames = 
		lookup_kb_specific_property_value(domain_designation,
		Frame_or_frames_with_this_name_kbprop);
	if (LISTP(frame_or_frames)) {
	    frame = Nil;
	    ab_loop_list_ = frame_or_frames;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    frame = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)16L)) {
		ab_loopvar__2 = eval_cons_1(ISVREF(ISVREF(frame,
			(SI_Long)1L),(SI_Long)1L),Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
	    }
	    goto next_loop;
	  end_loop:
	    return VALUES_1(ab_loopvar_);
	    return VALUES_1(Qnil);
	}
	else if (ISVREF(ISVREF(frame_or_frames,(SI_Long)1L),(SI_Long)16L))
	    return eval_cons_1(ISVREF(ISVREF(frame_or_frames,(SI_Long)1L),
		    (SI_Long)1L),Nil);
	else
	    return VALUES_1(Nil);
    }
    else {
	class_qm = atomic_class_element_of_designation(domain_designation);
	if (class_qm) {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = class_qm;
	    key_hash_value = SXHASH_SYMBOL_1(class_qm) & 
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
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = class_qm;
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
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
	      next_loop_7:
		if (level < ab_loop_bind_)
		    goto end_loop_7;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_8:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_9:
		if ( !TRUEP(marked))
		    goto end_loop_8;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_9;
	      end_loop_8:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
	      next_loop_10:
		if (level < ab_loop_bind_)
		    goto end_loop_10;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_11:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_12:
		if ( !TRUEP(marked))
		    goto end_loop_11;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_12;
	      end_loop_11:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
	    gensymed_symbol = resulting_value;
	    temp_2 = gensymed_symbol ? TRUEP(ISVREF(gensymed_symbol,
		    (SI_Long)16L)) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2)
	    return eval_cons_1(class_qm,Nil);
	else
	    return VALUES_1(Nil);
    }
}

static Object string_constant_21;  /* " at the input end of" */

/* ROLE-PRINT-AT-INPUT-END */
Object role_print_at_input_end(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,129);
    GENSYM_RETURN_ONE(print_standard_two_element_role(role,
	    local_variable_qm,string_constant_21));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-AT-INPUT-END */
Object serve_first_at_input_end(role,domain)
    Object role, domain;
{
    Object class_1, class_description, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, domain_cache_qm;
    Object role_cache_qm, specific_cache_qm, gensymed_symbol_4;
    char temp;

    x_note_fn_call(149,130);
    class_1 = SECOND(role);
    class_description = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    if (class_description && ISVREF(class_description,(SI_Long)16L)) {
	gensymed_symbol = domain;
	gensymed_symbol_1 = FIRST(role);
	gensymed_symbol_2 = class_1;
	gensymed_symbol_3 = Role_caching_enabled_qm ? ( 
		!((IFIX(Current_computation_flags) & (SI_Long)16L) != 
		(SI_Long)0L) ? T : Nil) : Qnil;
	domain_cache_qm = Nil;
	role_cache_qm = Nil;
	specific_cache_qm = Nil;
	if (gensymed_symbol_3) {
	    domain_cache_qm = 
		    get_lookup_slot_value_given_default(gensymed_symbol,
		    Qrole_cache,Nil);
	    role_cache_qm = assq_function(gensymed_symbol_1,domain_cache_qm);
	    specific_cache_qm = equal_assoc(gensymed_symbol_2,
		    CDR(role_cache_qm));
	    temp = TRUEP(specific_cache_qm);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    return serve_all_unreprocessed_cached_frames(CDR(specific_cache_qm));
	else {
	    gensymed_symbol_4 = search_for_entities_at_input_end(domain,
		    class_1,T);
	    if (gensymed_symbol_3)
		return add_to_cache_and_serve(gensymed_symbol,
			gensymed_symbol_1,
			copy_tree_using_eval_conses_1(gensymed_symbol_2),
			gensymed_symbol_4);
	    else
		return serve_all_unreprocessed_frames(gensymed_symbol_4);
	}
    }
    else {
	warn_of_bad_connected_to_class(class_1,domain);
	return VALUES_3(Nil,Nil,Nil);
    }
}

/* SEARCH-FOR-ENTITIES-AT-INPUT-END */
Object search_for_entities_at_input_end(connection_frame_1,class_1,
	    enforce_directionality_qm)
    Object connection_frame_1, class_1, enforce_directionality_qm;
{
    Object sub_class_bit_vector, connection;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(149,131);
    sub_class_bit_vector = ISVREF(ISVREF(connection_frame_1,(SI_Long)1L),
	    (SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Connection_class_description,
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
	connection = ISVREF(connection_frame_1,(SI_Long)21L);
	if ( !TRUEP(enforce_directionality_qm) ||  !((SI_Long)0L != 
		(IFIX(ISVREF(connection,(SI_Long)7L)) & (SI_Long)1L)))
	    return search_for_directly_connected_entities(connection_frame_1,
		    class_1,Nil,Nil,Qinput,Nil,Nil,Nil);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_22;  /* " at the output end of" */

/* ROLE-PRINT-AT-OUTPUT-END */
Object role_print_at_output_end(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,132);
    GENSYM_RETURN_ONE(print_standard_two_element_role(role,
	    local_variable_qm,string_constant_22));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-AT-OUTPUT-END */
Object serve_first_at_output_end(role,domain)
    Object role, domain;
{
    Object class_1, class_description, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, domain_cache_qm;
    Object role_cache_qm, specific_cache_qm, gensymed_symbol_4;
    char temp;

    x_note_fn_call(149,133);
    class_1 = SECOND(role);
    class_description = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    if (class_description && ISVREF(class_description,(SI_Long)16L)) {
	gensymed_symbol = domain;
	gensymed_symbol_1 = FIRST(role);
	gensymed_symbol_2 = class_1;
	gensymed_symbol_3 = Role_caching_enabled_qm ? ( 
		!((IFIX(Current_computation_flags) & (SI_Long)16L) != 
		(SI_Long)0L) ? T : Nil) : Qnil;
	domain_cache_qm = Nil;
	role_cache_qm = Nil;
	specific_cache_qm = Nil;
	if (gensymed_symbol_3) {
	    domain_cache_qm = 
		    get_lookup_slot_value_given_default(gensymed_symbol,
		    Qrole_cache,Nil);
	    role_cache_qm = assq_function(gensymed_symbol_1,domain_cache_qm);
	    specific_cache_qm = equal_assoc(gensymed_symbol_2,
		    CDR(role_cache_qm));
	    temp = TRUEP(specific_cache_qm);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    return serve_all_unreprocessed_cached_frames(CDR(specific_cache_qm));
	else {
	    gensymed_symbol_4 = search_for_entities_at_output_end(domain,
		    class_1,T);
	    if (gensymed_symbol_3)
		return add_to_cache_and_serve(gensymed_symbol,
			gensymed_symbol_1,
			copy_tree_using_eval_conses_1(gensymed_symbol_2),
			gensymed_symbol_4);
	    else
		return serve_all_unreprocessed_frames(gensymed_symbol_4);
	}
    }
    else {
	warn_of_bad_connected_to_class(class_1,domain);
	return VALUES_3(Nil,Nil,Nil);
    }
}

/* SEARCH-FOR-ENTITIES-AT-OUTPUT-END */
Object search_for_entities_at_output_end(connection_frame_1,class_1,
	    enforce_directionality_qm)
    Object connection_frame_1, class_1, enforce_directionality_qm;
{
    Object sub_class_bit_vector, connection;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(149,134);
    sub_class_bit_vector = ISVREF(ISVREF(connection_frame_1,(SI_Long)1L),
	    (SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Connection_class_description,
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
	connection = ISVREF(connection_frame_1,(SI_Long)21L);
	if ( !TRUEP(enforce_directionality_qm) ||  !((SI_Long)0L != 
		(IFIX(ISVREF(connection,(SI_Long)7L)) & (SI_Long)1L)))
	    return search_for_directly_connected_entities(connection_frame_1,
		    class_1,Nil,Nil,Qoutput,Nil,Nil,Nil);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_23;  /* " at either end of" */

/* ROLE-PRINT-AT-EITHER-END */
Object role_print_at_either_end(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,135);
    GENSYM_RETURN_ONE(print_standard_two_element_role(role,
	    local_variable_qm,string_constant_23));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-AT-EITHER-END */
Object serve_first_at_either_end(role,domain)
    Object role, domain;
{
    Object class_1, class_description, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, domain_cache_qm;
    Object role_cache_qm, specific_cache_qm, gensymed_symbol_4;
    char temp;

    x_note_fn_call(149,136);
    class_1 = SECOND(role);
    class_description = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    if (class_description && ISVREF(class_description,(SI_Long)16L)) {
	gensymed_symbol = domain;
	gensymed_symbol_1 = FIRST(role);
	gensymed_symbol_2 = class_1;
	gensymed_symbol_3 = Role_caching_enabled_qm ? ( 
		!((IFIX(Current_computation_flags) & (SI_Long)16L) != 
		(SI_Long)0L) ? T : Nil) : Qnil;
	domain_cache_qm = Nil;
	role_cache_qm = Nil;
	specific_cache_qm = Nil;
	if (gensymed_symbol_3) {
	    domain_cache_qm = 
		    get_lookup_slot_value_given_default(gensymed_symbol,
		    Qrole_cache,Nil);
	    role_cache_qm = assq_function(gensymed_symbol_1,domain_cache_qm);
	    specific_cache_qm = equal_assoc(gensymed_symbol_2,
		    CDR(role_cache_qm));
	    temp = TRUEP(specific_cache_qm);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    return serve_all_unreprocessed_cached_frames(CDR(specific_cache_qm));
	else {
	    gensymed_symbol_4 = search_for_entities_at_either_end(domain,
		    class_1);
	    if (gensymed_symbol_3)
		return add_to_cache_and_serve(gensymed_symbol,
			gensymed_symbol_1,
			copy_tree_using_eval_conses_1(gensymed_symbol_2),
			gensymed_symbol_4);
	    else
		return serve_all_unreprocessed_frames(gensymed_symbol_4);
	}
    }
    else {
	warn_of_bad_connected_to_class(class_1,domain);
	return VALUES_3(Nil,Nil,Nil);
    }
}

/* SEARCH-FOR-ENTITIES-AT-EITHER-END */
Object search_for_entities_at_either_end(connection_frame_1,class_1)
    Object connection_frame_1, class_1;
{
    Object temp;

    x_note_fn_call(149,137);
    temp = search_for_entities_at_input_end(connection_frame_1,class_1,Nil);
    return VALUES_1(nconc2(temp,
	    search_for_entities_at_output_end(connection_frame_1,class_1,
	    Nil)));
}

/* SERVE-FIRST-AT-INPUT-END-INVERSE */
Object serve_first_at_input_end_inverse(object,quantifier,role,
	    domain_designation)
    Object object, quantifier, role, domain_designation;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3, gensymed_symbol_4, role_argument, quantifier_1;
    Object designation, domain_cache_qm, role_cache_qm, specific_cache_qm;
    Object classes_qm, class_1, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, connected_entities, entities_to_serve, entity;
    Object sub_class_bit_vector, last_1, next_qm, temp_1, svref_arg_2;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_5, gensymed_symbol_6, gensymed_symbol_7;
    char temp;
    Object result;

    x_note_fn_call(149,138);
    gensymed_symbol = object;
    gensymed_symbol_1 = quantifier;
    gensymed_symbol_2 = role;
    gensymed_symbol_3 = domain_designation;
    gensymed_symbol_4 = Role_caching_enabled_qm ? ( 
	    !((IFIX(Current_computation_flags) & (SI_Long)16L) != 
	    (SI_Long)0L) ? T : Nil) : Qnil;
    if (gensymed_symbol_4) {
	role_argument = CDR(gensymed_symbol_2);
	quantifier_1 = gensymed_symbol_1;
	designation = gensymed_symbol_3;
	gensymed_symbol_4 = eval_cons_1(role_argument,
		eval_cons_1(quantifier_1,designation));
    }
    else
	gensymed_symbol_4 = Nil;
    gensymed_symbol_1 = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = Role_caching_enabled_qm ? ( 
	    !((IFIX(Current_computation_flags) & (SI_Long)16L) != 
	    (SI_Long)0L) ? T : Nil) : Qnil;
    domain_cache_qm = Nil;
    role_cache_qm = Nil;
    specific_cache_qm = Nil;
    if (gensymed_symbol_2) {
	domain_cache_qm = 
		get_lookup_slot_value_given_default(gensymed_symbol,
		Qrole_cache,Nil);
	role_cache_qm = assq_function(gensymed_symbol_1,domain_cache_qm);
	specific_cache_qm = equal_assoc(gensymed_symbol_4,CDR(role_cache_qm));
	temp = TRUEP(specific_cache_qm);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	result = serve_all_unreprocessed_cached_frames(CDR(specific_cache_qm));
    else {
	classes_qm = get_classes_given_designation(domain_designation);
	class_1 = Nil;
	ab_loop_list_ = classes_qm;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	class_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = search_for_directly_connected_entities(object,
		class_1,Nil,Nil,Nil,Nil,Qoutput,T);
	if (ab_loopvar__2) {
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = last(ab_loopvar__2,_);
	}
	goto next_loop;
      end_loop:
	connected_entities = ab_loopvar_;
	goto end_1;
	connected_entities = Qnil;
      end_1:;
	entities_to_serve = Nil;
	entity = Nil;
	ab_loop_list_ = connected_entities;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	entity = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	sub_class_bit_vector = ISVREF(ISVREF(entity,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol_5 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_6 = (SI_Long)1L;
	    gensymed_symbol_7 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_6 = gensymed_symbol_6 << gensymed_symbol_7;
	    gensymed_symbol_5 = gensymed_symbol_5 & gensymed_symbol_6;
	    temp = (SI_Long)0L < gensymed_symbol_5;
	}
	else
	    temp = TRUEP(Nil);
	if ((temp ? 
		TRUEP(designation_could_denote_item_p(domain_designation,
		entity)) : TRUEP(Nil)) ?  !EQ(quantifier,Qthe) || 
		unique_value_of_role_p(object,role,entity) : TRUEP(Nil))
	    entities_to_serve = eval_cons_1(entity,entities_to_serve);
	goto next_loop_1;
      end_loop_1:;
	if (classes_qm) {
	    last_1 = classes_qm;
	    next_qm = Nil;
	  next_loop_2:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop_2;
	    inline_note_reclaim_cons(last_1,Qeval);
	    last_1 = next_qm;
	    goto next_loop_2;
	  end_loop_2:
	    inline_note_reclaim_cons(last_1,Qeval);
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = classes_qm;
		temp_1 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = last_1;
	    }
	    else {
		temp_1 = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = classes_qm;
		temp_1 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = last_1;
	    }
	    M_CDR(last_1) = Nil;
	}
	reclaim_eval_tree_1(connected_entities);
	gensymed_symbol_3 = entities_to_serve;
	if (gensymed_symbol_2)
	    result = add_to_cache_and_serve(gensymed_symbol,
		    gensymed_symbol_1,
		    copy_tree_using_eval_conses_1(gensymed_symbol_4),
		    gensymed_symbol_3);
	else
	    result = serve_all_unreprocessed_frames(gensymed_symbol_3);
    }
    MVS_3(result,gensymed_symbol_1,gensymed_symbol_2,gensymed_symbol_3);
    if (gensymed_symbol_4) {
	reclaim_eval_cons_1(CDR(gensymed_symbol_4));
	reclaim_eval_cons_1(gensymed_symbol_4);
    }
    return VALUES_3(gensymed_symbol_1,gensymed_symbol_2,gensymed_symbol_3);
}

/* SERVE-FIRST-AT-OUTPUT-END-INVERSE */
Object serve_first_at_output_end_inverse(object,quantifier,role,
	    domain_designation)
    Object object, quantifier, role, domain_designation;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3, gensymed_symbol_4, role_argument, quantifier_1;
    Object designation, domain_cache_qm, role_cache_qm, specific_cache_qm;
    Object classes_qm, class_1, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, connected_entities, entities_to_serve, entity;
    Object sub_class_bit_vector, last_1, next_qm, temp_1, svref_arg_2;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_5, gensymed_symbol_6, gensymed_symbol_7;
    char temp;
    Object result;

    x_note_fn_call(149,139);
    gensymed_symbol = object;
    gensymed_symbol_1 = quantifier;
    gensymed_symbol_2 = role;
    gensymed_symbol_3 = domain_designation;
    gensymed_symbol_4 = Role_caching_enabled_qm ? ( 
	    !((IFIX(Current_computation_flags) & (SI_Long)16L) != 
	    (SI_Long)0L) ? T : Nil) : Qnil;
    if (gensymed_symbol_4) {
	role_argument = CDR(gensymed_symbol_2);
	quantifier_1 = gensymed_symbol_1;
	designation = gensymed_symbol_3;
	gensymed_symbol_4 = eval_cons_1(role_argument,
		eval_cons_1(quantifier_1,designation));
    }
    else
	gensymed_symbol_4 = Nil;
    gensymed_symbol_1 = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = Role_caching_enabled_qm ? ( 
	    !((IFIX(Current_computation_flags) & (SI_Long)16L) != 
	    (SI_Long)0L) ? T : Nil) : Qnil;
    domain_cache_qm = Nil;
    role_cache_qm = Nil;
    specific_cache_qm = Nil;
    if (gensymed_symbol_2) {
	domain_cache_qm = 
		get_lookup_slot_value_given_default(gensymed_symbol,
		Qrole_cache,Nil);
	role_cache_qm = assq_function(gensymed_symbol_1,domain_cache_qm);
	specific_cache_qm = equal_assoc(gensymed_symbol_4,CDR(role_cache_qm));
	temp = TRUEP(specific_cache_qm);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	result = serve_all_unreprocessed_cached_frames(CDR(specific_cache_qm));
    else {
	classes_qm = get_classes_given_designation(domain_designation);
	class_1 = Nil;
	ab_loop_list_ = classes_qm;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	class_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = search_for_directly_connected_entities(object,
		class_1,Nil,Nil,Nil,Nil,Qinput,T);
	if (ab_loopvar__2) {
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = last(ab_loopvar__2,_);
	}
	goto next_loop;
      end_loop:
	connected_entities = ab_loopvar_;
	goto end_1;
	connected_entities = Qnil;
      end_1:;
	entities_to_serve = Nil;
	entity = Nil;
	ab_loop_list_ = connected_entities;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	entity = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	sub_class_bit_vector = ISVREF(ISVREF(entity,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol_5 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_6 = (SI_Long)1L;
	    gensymed_symbol_7 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_6 = gensymed_symbol_6 << gensymed_symbol_7;
	    gensymed_symbol_5 = gensymed_symbol_5 & gensymed_symbol_6;
	    temp = (SI_Long)0L < gensymed_symbol_5;
	}
	else
	    temp = TRUEP(Nil);
	if ((temp ? 
		TRUEP(designation_could_denote_item_p(domain_designation,
		entity)) : TRUEP(Nil)) ?  !EQ(quantifier,Qthe) || 
		unique_value_of_role_p(object,role,entity) : TRUEP(Nil))
	    entities_to_serve = eval_cons_1(entity,entities_to_serve);
	goto next_loop_1;
      end_loop_1:;
	if (classes_qm) {
	    last_1 = classes_qm;
	    next_qm = Nil;
	  next_loop_2:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop_2;
	    inline_note_reclaim_cons(last_1,Qeval);
	    last_1 = next_qm;
	    goto next_loop_2;
	  end_loop_2:
	    inline_note_reclaim_cons(last_1,Qeval);
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = classes_qm;
		temp_1 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = last_1;
	    }
	    else {
		temp_1 = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = classes_qm;
		temp_1 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = last_1;
	    }
	    M_CDR(last_1) = Nil;
	}
	reclaim_eval_tree_1(connected_entities);
	gensymed_symbol_3 = entities_to_serve;
	if (gensymed_symbol_2)
	    result = add_to_cache_and_serve(gensymed_symbol,
		    gensymed_symbol_1,
		    copy_tree_using_eval_conses_1(gensymed_symbol_4),
		    gensymed_symbol_3);
	else
	    result = serve_all_unreprocessed_frames(gensymed_symbol_3);
    }
    MVS_3(result,gensymed_symbol_1,gensymed_symbol_2,gensymed_symbol_3);
    if (gensymed_symbol_4) {
	reclaim_eval_cons_1(CDR(gensymed_symbol_4));
	reclaim_eval_cons_1(gensymed_symbol_4);
    }
    return VALUES_3(gensymed_symbol_1,gensymed_symbol_2,gensymed_symbol_3);
}

/* SERVE-FIRST-AT-EITHER-END-INVERSE */
Object serve_first_at_either_end_inverse(object,quantifier,role,
	    domain_designation)
    Object object, quantifier, role, domain_designation;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3, gensymed_symbol_4, role_argument, quantifier_1;
    Object designation, domain_cache_qm, role_cache_qm, specific_cache_qm;
    Object classes_qm, class_1, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, connected_entities, entities_to_serve, entity;
    Object sub_class_bit_vector, last_1, next_qm, temp_1, svref_arg_2;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_5, gensymed_symbol_6, gensymed_symbol_7;
    char temp;
    Object result;

    x_note_fn_call(149,140);
    gensymed_symbol = object;
    gensymed_symbol_1 = quantifier;
    gensymed_symbol_2 = role;
    gensymed_symbol_3 = domain_designation;
    gensymed_symbol_4 = Role_caching_enabled_qm ? ( 
	    !((IFIX(Current_computation_flags) & (SI_Long)16L) != 
	    (SI_Long)0L) ? T : Nil) : Qnil;
    if (gensymed_symbol_4) {
	role_argument = CDR(gensymed_symbol_2);
	quantifier_1 = gensymed_symbol_1;
	designation = gensymed_symbol_3;
	gensymed_symbol_4 = eval_cons_1(role_argument,
		eval_cons_1(quantifier_1,designation));
    }
    else
	gensymed_symbol_4 = Nil;
    gensymed_symbol_1 = CAR(gensymed_symbol_2);
    gensymed_symbol_2 = Role_caching_enabled_qm ? ( 
	    !((IFIX(Current_computation_flags) & (SI_Long)16L) != 
	    (SI_Long)0L) ? T : Nil) : Qnil;
    domain_cache_qm = Nil;
    role_cache_qm = Nil;
    specific_cache_qm = Nil;
    if (gensymed_symbol_2) {
	domain_cache_qm = 
		get_lookup_slot_value_given_default(gensymed_symbol,
		Qrole_cache,Nil);
	role_cache_qm = assq_function(gensymed_symbol_1,domain_cache_qm);
	specific_cache_qm = equal_assoc(gensymed_symbol_4,CDR(role_cache_qm));
	temp = TRUEP(specific_cache_qm);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	result = serve_all_unreprocessed_cached_frames(CDR(specific_cache_qm));
    else {
	classes_qm = get_classes_given_designation(domain_designation);
	class_1 = Nil;
	ab_loop_list_ = classes_qm;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	class_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = search_for_directly_connected_entities(object,
		class_1,Nil,Nil,Nil,Nil,Nil,T);
	if (ab_loopvar__2) {
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = last(ab_loopvar__2,_);
	}
	goto next_loop;
      end_loop:
	connected_entities = ab_loopvar_;
	goto end_1;
	connected_entities = Qnil;
      end_1:;
	entities_to_serve = Nil;
	entity = Nil;
	ab_loop_list_ = connected_entities;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	entity = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	sub_class_bit_vector = ISVREF(ISVREF(entity,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol_5 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_6 = (SI_Long)1L;
	    gensymed_symbol_7 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_6 = gensymed_symbol_6 << gensymed_symbol_7;
	    gensymed_symbol_5 = gensymed_symbol_5 & gensymed_symbol_6;
	    temp = (SI_Long)0L < gensymed_symbol_5;
	}
	else
	    temp = TRUEP(Nil);
	if ((temp ? 
		TRUEP(designation_could_denote_item_p(domain_designation,
		entity)) : TRUEP(Nil)) ?  !EQ(quantifier,Qthe) || 
		unique_value_of_role_p(object,role,entity) : TRUEP(Nil))
	    entities_to_serve = eval_cons_1(entity,entities_to_serve);
	goto next_loop_1;
      end_loop_1:;
	if (classes_qm) {
	    last_1 = classes_qm;
	    next_qm = Nil;
	  next_loop_2:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop_2;
	    inline_note_reclaim_cons(last_1,Qeval);
	    last_1 = next_qm;
	    goto next_loop_2;
	  end_loop_2:
	    inline_note_reclaim_cons(last_1,Qeval);
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = classes_qm;
		temp_1 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = last_1;
	    }
	    else {
		temp_1 = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = classes_qm;
		temp_1 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = last_1;
	    }
	    M_CDR(last_1) = Nil;
	}
	reclaim_eval_tree_1(connected_entities);
	gensymed_symbol_3 = entities_to_serve;
	if (gensymed_symbol_2)
	    result = add_to_cache_and_serve(gensymed_symbol,
		    gensymed_symbol_1,
		    copy_tree_using_eval_conses_1(gensymed_symbol_4),
		    gensymed_symbol_3);
	else
	    result = serve_all_unreprocessed_frames(gensymed_symbol_3);
    }
    MVS_3(result,gensymed_symbol_1,gensymed_symbol_2,gensymed_symbol_3);
    if (gensymed_symbol_4) {
	reclaim_eval_cons_1(CDR(gensymed_symbol_4));
	reclaim_eval_cons_1(gensymed_symbol_4);
    }
    return VALUES_3(gensymed_symbol_1,gensymed_symbol_2,gensymed_symbol_3);
}

/* GET-OUTPUT-CONNECTIONS-FOR-CLASS */
Object get_output_connections_for_class(block,connection_class)
    Object block, connection_class;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, connection_frame_or_class;
    Object connection_frame_qm, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object temp, ab_less_than_branch_qm_, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(149,141);
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)6L)) : Nil;
    ab_skip_list_form_ = gensymed_symbol;
    ab_skip_list_p_ = Nil;
    ab_next_node_ = Nil;
    ab_tail_node_ = Nil;
    ab_current_alist_ = Nil;
    ab_entry_cons_ = Nil;
    ab_connection_ = Nil;
    ab_connection_item_ = Nil;
    connection = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      connection_frame_or_class = Nil;
      connection_frame_qm = Nil;
      ab_loopvar_ = Nil;
      ab_loopvar__1 = Nil;
      ab_loopvar__2 = Nil;
      gensymed_symbol = CDR(ab_skip_list_form_);
      if (CONSP(gensymed_symbol)) {
	  temp = M_CAR(gensymed_symbol);
	  temp_1 = SIMPLE_VECTOR_P(temp);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  temp = M_CDR(gensymed_symbol);
	  ab_skip_list_p_ = SIMPLE_VECTOR_P(temp) ? T : Nil;
      }
      else
	  ab_skip_list_p_ = Nil;
      if (ab_skip_list_p_) {
	  ab_next_node_ = 
		  ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
		  (SI_Long)0L),(SI_Long)0L));
	  ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
	  if (EQ(ab_next_node_,ab_tail_node_))
	      ab_next_node_ = Nil;
      }
      else
	  ab_next_node_ = CDR(ab_skip_list_form_);
    next_loop:
    next_loop_1:
      if (ab_current_alist_) {
	  ab_entry_cons_ = M_CAR(ab_current_alist_);
	  ab_connection_ = M_CAR(ab_entry_cons_);
	  ab_connection_item_ = M_CDR(ab_entry_cons_);
	  ab_current_alist_ = M_CDR(ab_current_alist_);
      }
      else if (ab_skip_list_p_) {
	  if (ab_next_node_) {
	      ab_current_node_ = ab_next_node_;
	      ab_next_node_ = 
		      ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node_,
		      (SI_Long)0L),(SI_Long)0L));
	      if (EQ(ab_next_node_,ab_tail_node_))
		  ab_next_node_ = Nil;
	      ab_connection_ = ISVREF(ab_current_node_,(SI_Long)2L);
	      ab_connection_item_ = ISVREF(ab_current_node_,(SI_Long)3L);
	  }
	  else
	      ab_current_node_ = Nil;
      }
      else {
	  if (ab_next_node_) {
	      ab_current_node_ = ab_next_node_;
	      ab_less_than_branch_qm_ = Nil;
	    next_loop_2:
	      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
	      if ( !TRUEP(ab_less_than_branch_qm_))
		  goto end_loop;
	      ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
	      ab_current_node_ = ab_less_than_branch_qm_;
	      goto next_loop_2;
	    end_loop:;
	  }
	  else if (ab_node_stack_) {
	      ab_next_node_ = ab_node_stack_;
	      ab_current_node_ = M_CAR(ab_node_stack_);
	      ab_node_stack_ = M_CDR(ab_node_stack_);
	  }
	  else
	      ab_current_node_ = Nil;
	  if (ab_current_node_) {
	      ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
	      ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
	      ab_entry_cons_ = M_CAR(ab_current_alist_);
	      ab_connection_ = M_CAR(ab_entry_cons_);
	      ab_connection_item_ = M_CDR(ab_entry_cons_);
	      ab_current_alist_ = M_CDR(ab_current_alist_);
	  }
      }
      if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_ 
	      && EQ(ISVREF(ab_connection_,(SI_Long)3L),block))
	  goto end_1;
      goto next_loop_1;
    end_loop_1:
    end_1:
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_2;
      connection = ab_connection_;
      connection_frame_or_class = ISVREF(connection,(SI_Long)1L);
      if (SYMBOLP(connection_frame_or_class)) {
	  gensymed_symbol = 
		  lookup_global_or_kb_specific_property_value(connection_frame_or_class,
		  Class_description_gkbprop);
	  connection_frame_qm = (gensymed_symbol ? 
		  TRUEP(memq_function(connection_class,
		  ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil)) ? 
		  make_and_install_new_connection_frame(connection,
		  connection_class) : Nil;
      }
      else {
	  gensymed_symbol = 
		  lookup_global_or_kb_specific_property_value(connection_class,
		  Class_description_gkbprop);
	  if (gensymed_symbol) {
	      sub_class_bit_vector = 
		      ISVREF(ISVREF(connection_frame_or_class,(SI_Long)1L),
		      (SI_Long)19L);
	      superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,
		      (SI_Long)18L));
	      sub_class_vector_index = superior_class_bit_number >>  -  - 
		      (SI_Long)3L;
	      if (sub_class_vector_index < 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		  gensymed_symbol_1 = 
			  UBYTE_8_ISAREF_1(sub_class_bit_vector,
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
	  connection_frame_qm = temp_1 ? connection_frame_or_class : Nil;
      }
      if (connection_frame_qm) {
	  ab_loopvar__2 = eval_cons_1(connection_frame_qm,Nil);
	  if (ab_loopvar__1)
	      M_CDR(ab_loopvar__1) = ab_loopvar__2;
	  else
	      ab_loopvar_ = ab_loopvar__2;
	  ab_loopvar__1 = ab_loopvar__2;
      }
      goto next_loop;
    end_loop_2:
      result = VALUES_1(ab_loopvar_);
      goto end_2;
      result = VALUES_1(Qnil);
    end_2:;
    POP_SPECIAL();
    return result;
}

/* ROLE-PRINT-SUBWORKSPACE */
Object role_print_subworkspace(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,142);
    GENSYM_RETURN_ONE(print_role_whose_car_is_role_server(role,
	    local_variable_qm));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-SUBWORKSPACE */
Object serve_first_subworkspace(role,domain)
    Object role, domain;
{
    Object sub_class_bit_vector, temp_1, sws;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(149,143);
    sub_class_bit_vector = ISVREF(ISVREF(domain,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Entity_class_description,
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
	temp_1 = ISVREF(domain,(SI_Long)18L);
	sws = CAR(temp_1);
	if (sws && serve_item_p(sws))
	    return VALUES_3(sws,Nil,Qnever);
	else
	    return VALUES_3(Nil,Nil,Nil);
    }
    else
	return VALUES_3(Nil,Nil,Nil);
}

static Object string_constant_24;  /* "~a is not a kb-workspace." */

/* SERVE-FIRST-SUBWORKSPACE-INVERSE */
Object serve_first_subworkspace_inverse(kb_workspace,quantifier,role,
	    domain_designation)
    Object kb_workspace, quantifier, role, domain_designation;
{
    Object sub_class_bit_vector, superior_item;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(149,144);
    sub_class_bit_vector = ISVREF(ISVREF(kb_workspace,(SI_Long)1L),
	    (SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Kb_workspace_class_description,
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
	superior_item = ISVREF(kb_workspace,(SI_Long)18L);
	if (superior_item && 
		designation_could_denote_item_p(domain_designation,
		superior_item))
	    return VALUES_3(superior_item,Nil,Qnever);
	else
	    return VALUES_3(Nil,Nil,Nil);
    }
    else {
	if ((SI_Long)1L <= IFIX(Warning_message_level))
	    give_warning_1(3,FIX((SI_Long)1L),string_constant_24,kb_workspace);
	return VALUES_3(Nil,Nil,Nil);
    }
}

static Object string_constant_25;  /* " superior to" */

/* ROLE-PRINT-SUPERIOR-ITEM */
Object role_print_superior_item(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,145);
    GENSYM_RETURN_ONE(print_standard_two_element_role(role,
	    local_variable_qm,string_constant_25));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-SUPERIOR-ITEM */
Object serve_first_superior_item(role,domain)
    Object role, domain;
{
    Object superior_class, superior_class_description, sub_class_bit_vector;
    Object superior_item_qm, gensymed_symbol_3;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(149,146);
    superior_class = SECOND(role);
    superior_class_description = 
	    lookup_global_or_kb_specific_property_value(superior_class,
	    Class_description_gkbprop);
    if (superior_class_description && ISVREF(superior_class_description,
	    (SI_Long)16L)) {
	sub_class_bit_vector = ISVREF(ISVREF(domain,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Kb_workspace_class_description,(SI_Long)18L));
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
	superior_item_qm = temp ? ISVREF(domain,(SI_Long)18L) : 
		get_lookup_slot_value_given_default(domain,Qparent_frame,Nil);
	if (superior_item_qm) {
	    gensymed_symbol_3 = ISVREF(superior_item_qm,(SI_Long)1L);
	    sub_class_bit_vector = ISVREF(gensymed_symbol_3,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(superior_class_description,(SI_Long)18L));
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
		if (serve_item_p(superior_item_qm))
		    return VALUES_3(superior_item_qm,Nil,Qnever);
		else
		    return VALUES_3(Nil,Nil,Nil);
	    }
	    else
		return VALUES_3(Nil,Nil,Nil);
	}
	else
	    return VALUES_3(Nil,Nil,Nil);
    }
    else
	return VALUES_3(Nil,Nil,Nil);
}

/* ITEM-ATTRIBUTES-OF-KB-FRAME */
Object item_attributes_of_kb_frame(kb_frame,class_description)
    Object kb_frame, class_description;
{
    Object slot_description, class_description_1, ab_loop_list_;
    Object attribute_value_qm, attribute_class_description_qm, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, x2, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(149,147);
    slot_description = Nil;
    class_description_1 = ISVREF(kb_frame,(SI_Long)1L);
    ab_loop_list_ = ISVREF(class_description_1,(SI_Long)6L);
    attribute_value_qm = Nil;
    attribute_class_description_qm = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    slot_description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    attribute_value_qm = ISVREF(slot_description,(SI_Long)8L) ? 
	    get_slot_description_value(kb_frame,slot_description) : Nil;
    if (SIMPLE_VECTOR_P(attribute_value_qm) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(attribute_value_qm)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(attribute_value_qm,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(attribute_value_qm,(SI_Long)1L);
	attribute_class_description_qm = SIMPLE_VECTOR_P(x2) && 
		EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	attribute_class_description_qm = Nil;
    if (attribute_class_description_qm) {
	sub_class_bit_vector = ISVREF(attribute_class_description_qm,
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(class_description,
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
	ab_loopvar__2 = eval_cons_1(attribute_value_qm,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    temp_1 = ab_loopvar_;
    goto end_1;
    temp_1 = Qnil;
  end_1:;
    return VALUES_1(temp_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Attribute_items, Qattribute_items);

/* ADD-TO-ATTRIBUTE-ITEMS */
Object add_to_attribute_items(item)
    Object item;
{
    Object new_cons, temp, svref_arg_2, svref_new_value, gensymed_symbol;

    x_note_fn_call(149,148);
    new_cons = ISVREF(Available_eval_conses_vector,IFIX(Current_thread_index));
    if (new_cons) {
	temp = Available_eval_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_eval_cons_pool();
    M_CAR(gensymed_symbol) = item;
    temp = Attribute_items;
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qeval);
    Attribute_items = gensymed_symbol;
    return VALUES_1(Nil);
}

static Object Qadd_to_attribute_items;  /* add-to-attribute-items */

/* UNORDERED-ITEM-ATTRIBUTES-OF-KB-FRAME */
Object unordered_item_attributes_of_kb_frame(kb_frame)
    Object kb_frame;
{
    Object slot_description, class_description, ab_loop_list_;
    Object vector_slot_index_qm, slot_value, user_vector_slot_index_qm;
    Object slot_name, lookup_structure_qm, slot_index_qm, x2, gensymed_symbol;
    Object gensymed_symbol_1, items_to_return;
    SI_Long max_i, i, ab_loop_bind_;

    x_note_fn_call(149,149);
    Attribute_items = Nil;
    slot_description = Nil;
    class_description = ISVREF(kb_frame,(SI_Long)1L);
    ab_loop_list_ = ISVREF(class_description,(SI_Long)6L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    slot_description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (ISVREF(slot_description,(SI_Long)8L)) {
	vector_slot_index_qm = ISVREF(slot_description,(SI_Long)7L);
	if (vector_slot_index_qm)
	    slot_value = ISVREF(kb_frame,IFIX(vector_slot_index_qm));
	else {
	    user_vector_slot_index_qm = ISVREF(slot_description,(SI_Long)8L);
	    if (user_vector_slot_index_qm)
		slot_value = ISVREF(ISVREF(kb_frame,(SI_Long)0L),
			IFIX(user_vector_slot_index_qm));
	    else {
		slot_name = ISVREF(slot_description,(SI_Long)1L);
		lookup_structure_qm = ISVREF(kb_frame,(SI_Long)0L);
		if (lookup_structure_qm) {
		    max_i = 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(lookup_structure_qm));
		    max_i = max_i - (SI_Long)1L;
		    i = IFIX(ISVREF(ISVREF(kb_frame,(SI_Long)1L),
			    (SI_Long)15L));
		    ab_loop_bind_ = max_i;
		  next_loop_1:
		    if (i >= ab_loop_bind_)
			goto end_loop_1;
		    if (EQ(ISVREF(lookup_structure_qm,i),slot_name)) {
			slot_index_qm = FIX(i + (SI_Long)1L);
			goto end_1;
		    }
		    i = i + (SI_Long)2L;
		    goto next_loop_1;
		  end_loop_1:
		    slot_index_qm = Qnil;
		  end_1:;
		    slot_value = slot_index_qm ? 
			    ISVREF(lookup_structure_qm,
			    IFIX(slot_index_qm)) : ISVREF(slot_description,
			    (SI_Long)6L);
		}
		else
		    slot_value = ISVREF(slot_description,(SI_Long)6L);
	    }
	}
	if (SIMPLE_VECTOR_P(slot_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value)) > (SI_Long)2L 
		&&  !EQ(ISVREF(slot_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(slot_value,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol && ISVREF(gensymed_symbol,(SI_Long)16L)) {
	    gensymed_symbol = SYMBOL_FUNCTION(Qadd_to_attribute_items);
	    gensymed_symbol_1 = slot_value;
	    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	}
    }
    goto next_loop;
  end_loop:;
    items_to_return = Attribute_items;
    Attribute_items = Nil;
    return VALUES_1(items_to_return);
}

/* SERVE-FIRST-SUPERIOR-ITEM-INVERSE */
Object serve_first_superior_item_inverse(item,quantifier,role,
	    domain_designation)
    Object item, quantifier, role, domain_designation;
{
    Object frames_to_serve, sub_class_bit_vector, temp_1, attributes;
    Object current_attribute_cons, attribute, next_attribute_cons, temp_2;
    Object svref_arg_2;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(149,150);
    frames_to_serve = Nil;
    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Entity_class_description,
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
    temp_1 = temp ? copy_list_using_eval_conses_1(ISVREF(item,
	    (SI_Long)18L)) : Nil;
    attributes = nconc2(temp_1,unordered_item_attributes_of_kb_frame(item));
    current_attribute_cons = attributes;
    attribute = Nil;
    next_attribute_cons = Nil;
  next_loop:
    if ( !TRUEP(current_attribute_cons))
	goto end_loop;
    attribute = CAR(current_attribute_cons);
    next_attribute_cons = CDR(current_attribute_cons);
    if (designation_could_denote_item_p(domain_designation,attribute)) {
	M_CDR(current_attribute_cons) = frames_to_serve;
	frames_to_serve = current_attribute_cons;
    }
    else {
	inline_note_reclaim_cons(current_attribute_cons,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_2 = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_2) = current_attribute_cons;
	    temp_2 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = current_attribute_cons;
	}
	else {
	    temp_2 = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = current_attribute_cons;
	    temp_2 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = current_attribute_cons;
	}
	M_CDR(current_attribute_cons) = Nil;
    }
    current_attribute_cons = next_attribute_cons;
    goto next_loop;
  end_loop:;
    return serve_all_unreprocessed_frames(frames_to_serve);
}

static Object string_constant_26;  /* " that is an attribute of" */

/* ROLE-PRINT-ATTRIBUTE-OF-CLASS */
Object role_print_attribute_of_class(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,151);
    GENSYM_RETURN_ONE(print_standard_two_element_role(role,
	    local_variable_qm,string_constant_26));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-ATTRIBUTE-OF-CLASS */
Object serve_first_attribute_of_class(role,domain)
    Object role, domain;
{
    Object given_type_symbol, type_spec_qm, class_description_qm;
    Object gensymed_symbol, held_vector, attribute_value, value, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, x2, value_class_desc_qm;
    Object sub_class_bit_vector, temp_1, slots, slot_name_and_value;
    Object ab_loop_list_, slot_name, value_qm;
    SI_Long next_index, length_1, gensymed_symbol_1, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(149,152);
    given_type_symbol = M_CAR(M_CDR(role));
    type_spec_qm = 
	    type_specification_for_user_or_datum_type(given_type_symbol);
    class_description_qm =  !TRUEP(type_spec_qm) ? 
	    lookup_global_or_kb_specific_property_value(given_type_symbol,
	    Class_description_gkbprop) : Nil;
    if ( !TRUEP(type_spec_qm) && ( !TRUEP(class_description_qm) ||  
	    !TRUEP(ISVREF(class_description_qm,(SI_Long)16L))))
	return VALUES_3(Nil,Nil,Nil);
    else if (CONSP(domain) && EQ(M_CDR(domain),Qab_structure)) {
	gensymed_symbol = domain;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	attribute_value = Nil;
	value = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop:
	if (next_index >= length_1)
	    goto end_loop;
	gensymed_symbol_1 = next_index + (SI_Long)1L;
	attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		gensymed_symbol_1 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		(SI_Long)1023L);
	value = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
	next_index = next_index + (SI_Long)2L;
	if (type_spec_qm)
	    temp = TRUEP(type_specification_type_p(value,type_spec_qm));
	else {
	    if (SIMPLE_VECTOR_P(value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(value,(SI_Long)1L),
			Qavailable_frame_vector)) {
		x2 = ISVREF(value,(SI_Long)1L);
		value_class_desc_qm = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? x2 : Qnil;
	    }
	    else
		value_class_desc_qm = Nil;
	    if (value_class_desc_qm) {
		sub_class_bit_vector = ISVREF(value_class_desc_qm,
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(class_description_qm,(SI_Long)18L));
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
	if (temp) {
	    ab_loopvar__2 = eval_cons_1(FIXNUMP(value) || value && 
		    SYMBOLP(value) || SIMPLE_VECTOR_P(value) ? value : 
		    copy_if_evaluation_value_1(value),Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	goto next_loop;
      end_loop:
	temp_1 = ab_loopvar_;
	goto end_1;
	temp_1 = Qnil;
      end_1:;
	return serve_all_items_and_values(temp_1);
    }
    else if (type_spec_qm) {
	slots = get_list_of_all_user_visible_attributes(ISVREF(domain,
		(SI_Long)1L));
	slot_name_and_value = Nil;
	ab_loop_list_ = slots;
	slot_name = Nil;
	value_qm = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	slot_name_and_value = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	slot_name = M_CAR(slot_name_and_value);
	value_qm = frame_or_evaluation_value_user_attribute_value(domain,
		slot_name,Nil);
	reclaim_eval_cons_1(slot_name_and_value);
	if (value_qm && type_specification_type_p(value_qm,type_spec_qm)) {
	    temp_1 = value_qm;
	    value_qm = Nil;
	    ab_loopvar__2 = eval_cons_1(temp_1,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	if (value_qm) {
	    if ( !(FIXNUMP(value_qm) || SYMBOLP(value_qm) || 
		    SIMPLE_VECTOR_P(value_qm)))
		reclaim_if_evaluation_value_1(value_qm);
	}
	goto next_loop_1;
      end_loop_1:
	reclaim_eval_list_1(slots);
	temp_1 = ab_loopvar_;
	goto end_2;
	temp_1 = Qnil;
      end_2:;
	return serve_all_items_and_values(temp_1);
    }
    else
	return serve_all_unreprocessed_frames(item_attributes_of_kb_frame(domain,
		class_description_qm));
}

/* SERVE-FIRST-ATTRIBUTE-OF-CLASS-INVERSE */
Object serve_first_attribute_of_class_inverse(item,quantifier,role,
	    domain_designation)
    Object item, quantifier, role, domain_designation;
{
    Object parent_frame_qm;

    x_note_fn_call(149,153);
    parent_frame_qm = get_lookup_slot_value_given_default(item,
	    Qparent_frame,Nil);
    if (parent_frame_qm && 
	    designation_could_denote_item_p(domain_designation,
	    parent_frame_qm) && serve_item_p(parent_frame_qm))
	return VALUES_3(parent_frame_qm,Nil,Qnever);
    else
	return VALUES_3(Nil,Nil,Nil);
}

static Object string_constant_27;  /* " that is a user-defined attribute name of" */

/* ROLE-PRINT-USER-ATTRIBUTE-NAMES */
Object role_print_user_attribute_names(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,154);
    GENSYM_RETURN_ONE(print_standard_two_element_role(role,
	    local_variable_qm,string_constant_27));
    return VALUES_1(Nil);
}

static Object Qserve_next_evaluation_value;  /* serve-next-evaluation-value */

/* SERVE-FIRST-USER-ATTRIBUTE-NAMES */
Object serve_first_user_attribute_names(role,domain)
    Object role, domain;
{
    Object structure, gensymed_symbol, held_vector, name, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, val_to_serve, rest_qm, temp;
    Object svref_arg_2, x2, x, class_or_frame, ab_loopvar__3, ab_loopvar__4;
    Object tail_of_slot_descriptions, temp_1;
    SI_Long next_index, length_1;
    char temp_2;

    x_note_fn_call(149,155);
    if (CONSP(domain) && EQ(M_CDR(domain),Qab_structure)) {
	structure = domain;
	gensymed_symbol = structure;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	name = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop:
	if (next_index >= length_1)
	    goto end_loop;
	name = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	next_index = next_index + (SI_Long)2L;
	ab_loopvar__2 = eval_cons_1(name,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	gensymed_symbol = ab_loopvar_;
	goto end_1;
	gensymed_symbol = Qnil;
      end_1:;
	if ( !TRUEP(gensymed_symbol))
	    return VALUES_3(Nil,Nil,Nil);
	else {
	    val_to_serve = M_CAR(gensymed_symbol);
	    rest_qm = M_CDR(gensymed_symbol);
	    if (rest_qm) {
		temp = SYMBOL_FUNCTION(Qserve_next_evaluation_value);
		M_CAR(gensymed_symbol) = temp;
		return VALUES_3(val_to_serve,gensymed_symbol,Qnever);
	    }
	    else {
		inline_note_reclaim_cons(gensymed_symbol,Qeval);
		if (ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp = ISVREF(Available_eval_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp) = gensymed_symbol;
		    temp = Available_eval_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = gensymed_symbol;
		}
		else {
		    temp = Available_eval_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = gensymed_symbol;
		    temp = Available_eval_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = gensymed_symbol;
		}
		M_CDR(gensymed_symbol) = Nil;
		return VALUES_3(val_to_serve,Nil,Qnever);
	    }
	}
    }
    else {
	if (SIMPLE_VECTOR_P(domain) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(domain)) > (SI_Long)2L &&  
		!EQ(ISVREF(domain,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(domain,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol && ISVREF(gensymed_symbol,(SI_Long)16L)) {
	    ab_loopvar_ = Nil;
	    x = Nil;
	    class_or_frame = domain;
	    ab_loopvar__1 = SYMBOLP(class_or_frame) ? 
		    lookup_global_or_kb_specific_property_value(class_or_frame,
		    Class_description_gkbprop) : ISVREF(class_or_frame,
		    (SI_Long)1L);
	    ab_loopvar__2 = Nil;
	    ab_loopvar__3 = Nil;
	    ab_loopvar__4 = Nil;
	    tail_of_slot_descriptions = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  next_loop_1:
	    if ( !TRUEP(tail_of_slot_descriptions))
		goto end_loop_1;
	    if (ISVREF(M_CAR(tail_of_slot_descriptions),(SI_Long)8L))
		goto end_loop_1;
	    tail_of_slot_descriptions = M_CDR(tail_of_slot_descriptions);
	    goto next_loop_1;
	  end_loop_1:
	    ab_loopvar_ = tail_of_slot_descriptions;
	  next_loop_2:
	    if ( !TRUEP(ab_loopvar_))
		goto end_loop_2;
	    ab_loopvar__4 = M_CAR(ab_loopvar_);
	    if ( ! !TRUEP(ISVREF(ab_loopvar__4,(SI_Long)8L))) {
		temp_1 = ISVREF(ab_loopvar__4,(SI_Long)3L);
		temp_2 =  !EQ(temp_1,
			ISVREF(get_slot_description_of_class_description_function(ISVREF(ab_loopvar__4,
			(SI_Long)2L),ab_loopvar__1,Nil),(SI_Long)3L));
	    }
	    else
		temp_2 = TRUEP(Nil);
	    x = temp_2 ? ISVREF(ab_loopvar__4,(SI_Long)1L) : 
		    ISVREF(ab_loopvar__4,(SI_Long)2L);
	    ab_loopvar_ = CDR(ab_loopvar_);
	    ab_loopvar__4 = eval_cons_1(x,Nil);
	    if (ab_loopvar__3)
		M_CDR(ab_loopvar__3) = ab_loopvar__4;
	    else
		ab_loopvar__2 = ab_loopvar__4;
	    ab_loopvar__3 = ab_loopvar__4;
	    goto next_loop_2;
	  end_loop_2:
	    gensymed_symbol = ab_loopvar__2;
	    goto end_2;
	    gensymed_symbol = Qnil;
	  end_2:;
	    if ( !TRUEP(gensymed_symbol))
		return VALUES_3(Nil,Nil,Nil);
	    else {
		val_to_serve = M_CAR(gensymed_symbol);
		rest_qm = M_CDR(gensymed_symbol);
		if (rest_qm) {
		    temp = SYMBOL_FUNCTION(Qserve_next_evaluation_value);
		    M_CAR(gensymed_symbol) = temp;
		    return VALUES_3(val_to_serve,gensymed_symbol,Qnever);
		}
		else {
		    inline_note_reclaim_cons(gensymed_symbol,Qeval);
		    if (ISVREF(Available_eval_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp = ISVREF(Available_eval_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp) = gensymed_symbol;
			temp = Available_eval_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = gensymed_symbol;
		    }
		    else {
			temp = Available_eval_conses_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = gensymed_symbol;
			temp = Available_eval_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = gensymed_symbol;
		    }
		    M_CDR(gensymed_symbol) = Nil;
		    return VALUES_3(val_to_serve,Nil,Qnever);
		}
	    }
	}
	else
	    return VALUES_3(Nil,Nil,Nil);
    }
}

static Object string_constant_28;  /* " that is an attribute name of" */

/* ROLE-PRINT-ATTRIBUTE-NAMES */
Object role_print_attribute_names(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,156);
    GENSYM_RETURN_ONE(print_standard_two_element_role(role,
	    local_variable_qm,string_constant_28));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-ATTRIBUTE-NAMES */
Object serve_first_attribute_names(role,domain)
    Object role, domain;
{
    Object structure, gensymed_symbol, held_vector, name, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, val_to_serve, rest_qm, temp;
    Object svref_arg_2, name_to_slot_description_alist, entry_cons;
    Object alist_entry;
    SI_Long next_index, length_1;

    x_note_fn_call(149,157);
    if (CONSP(domain) && EQ(M_CDR(domain),Qab_structure)) {
	structure = domain;
	gensymed_symbol = structure;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	name = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop:
	if (next_index >= length_1)
	    goto end_loop;
	name = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	next_index = next_index + (SI_Long)2L;
	ab_loopvar__2 = eval_cons_1(name,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	gensymed_symbol = ab_loopvar_;
	goto end_1;
	gensymed_symbol = Qnil;
      end_1:;
	if ( !TRUEP(gensymed_symbol))
	    return VALUES_3(Nil,Nil,Nil);
	else {
	    val_to_serve = M_CAR(gensymed_symbol);
	    rest_qm = M_CDR(gensymed_symbol);
	    if (rest_qm) {
		temp = SYMBOL_FUNCTION(Qserve_next_evaluation_value);
		M_CAR(gensymed_symbol) = temp;
		return VALUES_3(val_to_serve,gensymed_symbol,Qnever);
	    }
	    else {
		inline_note_reclaim_cons(gensymed_symbol,Qeval);
		if (ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp = ISVREF(Available_eval_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp) = gensymed_symbol;
		    temp = Available_eval_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = gensymed_symbol;
		}
		else {
		    temp = Available_eval_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = gensymed_symbol;
		    temp = Available_eval_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = gensymed_symbol;
		}
		M_CDR(gensymed_symbol) = Nil;
		return VALUES_3(val_to_serve,Nil,Qnever);
	    }
	}
    }
    else {
	name_to_slot_description_alist = 
		get_list_of_all_user_visible_attributes(ISVREF(domain,
		(SI_Long)1L));
	entry_cons = name_to_slot_description_alist;
	alist_entry = Nil;
	name = Nil;
      next_loop_1:
	if ( !TRUEP(entry_cons))
	    goto end_loop_1;
	alist_entry = M_CAR(entry_cons);
	name = M_CAR(alist_entry);
	reclaim_eval_cons_1(alist_entry);
	M_CAR(entry_cons) = name;
	entry_cons = M_CDR(entry_cons);
	goto next_loop_1;
      end_loop_1:;
	gensymed_symbol = name_to_slot_description_alist;
	if ( !TRUEP(gensymed_symbol))
	    return VALUES_3(Nil,Nil,Nil);
	else {
	    val_to_serve = M_CAR(gensymed_symbol);
	    rest_qm = M_CDR(gensymed_symbol);
	    if (rest_qm) {
		temp = SYMBOL_FUNCTION(Qserve_next_evaluation_value);
		M_CAR(gensymed_symbol) = temp;
		return VALUES_3(val_to_serve,gensymed_symbol,Qnever);
	    }
	    else {
		inline_note_reclaim_cons(gensymed_symbol,Qeval);
		if (ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp = ISVREF(Available_eval_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp) = gensymed_symbol;
		    temp = Available_eval_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = gensymed_symbol;
		}
		else {
		    temp = Available_eval_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = gensymed_symbol;
		    temp = Available_eval_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = gensymed_symbol;
		}
		M_CDR(gensymed_symbol) = Nil;
		return VALUES_3(val_to_serve,Nil,Qnever);
	    }
	}
    }
}

static Object string_constant_29;  /* " that is an attribute of the item" */

/* ROLE-PRINT-ATTRIBUTE-VALUE */
Object role_print_attribute_value(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,158);
    GENSYM_RETURN_ONE(print_standard_two_element_role(role,
	    local_variable_qm,string_constant_29));
    return VALUES_1(Nil);
}

static Object string_constant_30;  /* " that is an attribute of ~ND named by ~ND" */

/* ROLE-AND-DESIGNATION-PRINT-ATTRIBUTE-VALUE */
Object role_and_designation_print_attribute_value varargs_1(int, n)
{
    Object role;
    Object domain_1_qm, domain_2_qm, temp, local_name_qm;
    Object role_with_no_local_name, type;
    char temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(149,159);
    INIT_ARGS_nonrelocating();
    role = REQUIRED_ARG_nonrelocating();
    domain_1_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    domain_2_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (CONSP(role)) {
	temp = FIRST(role);
	temp_1 = CONSP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    local_name_qm = temp_1 ? CDR(role) : Nil;
    role_with_no_local_name = local_name_qm ? FIRST(role) : role;
    type = LISTP(role_with_no_local_name) ? 
	    SECOND(role_with_no_local_name) : Nil;
    print_user_or_datum_type(type);
    if (local_name_qm) {
	twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)1L));
	twrite_symbol(1,local_name_qm);
    }
    return tformat(3,string_constant_30,domain_1_qm,domain_2_qm);
}

static Object Qab_class;           /* class */

/* SERVE-FIRST-ATTRIBUTE-VALUE */
Object serve_first_attribute_value(role,item,attribute_name)
    Object role, item, attribute_name;
{
    Object attribute, class_qm, class_type_spec, type_spec, attribute_value_qm;
    Object coerced_value_qm, eval_list, eval_list_tail, eval_cons, temp;
    Object svref_arg_2;

    x_note_fn_call(149,160);
    attribute = attribute_name;
    if (unauthorized_system_slot_p(attribute))
	return VALUES_3(Nil,Nil,Nil);
    else {
	class_qm = CONSP(role) ? SECOND(role) : Nil;
	class_type_spec = eval_list_2(Qab_class,class_qm);
	type_spec = type_specification_for_user_or_datum_type(class_qm);
	if (type_spec);
	else
	    type_spec = class_type_spec;
	attribute_value_qm = 
		frame_or_evaluation_value_user_attribute_value(item,
		attribute,Nil);
	if (attribute_value_qm &&  
		!TRUEP(type_specification_type_p(attribute_value_qm,
		type_spec))) {
	    coerced_value_qm = 
		    coerce_to_type_for_role_service(attribute_value_qm,
		    type_spec);
	    if (coerced_value_qm) {
		if ( !(FIXNUMP(attribute_value_qm) || 
			SYMBOLP(attribute_value_qm) || 
			SIMPLE_VECTOR_P(attribute_value_qm)))
		    reclaim_if_evaluation_value_1(attribute_value_qm);
		attribute_value_qm = coerced_value_qm;
	    }
	    else {
		if ( !(FIXNUMP(attribute_value_qm) || 
			SYMBOLP(attribute_value_qm) || 
			SIMPLE_VECTOR_P(attribute_value_qm)))
		    reclaim_if_evaluation_value_1(attribute_value_qm);
		attribute_value_qm = Nil;
	    }
	}
	eval_list = class_type_spec;
	eval_list_tail = M_CDR(class_type_spec);
	if (eval_list &&  !((SI_Long)0L == inline_debugging_consing())) {
	    eval_cons = eval_list;
	  next_loop:
	    inline_note_reclaim_cons(eval_cons,Qeval);
	    if (EQ(eval_cons,eval_list_tail))
		goto end_1;
	    else if ( !TRUEP(eval_cons))
		goto end_1;
	    else
		eval_cons = CDR(eval_cons);
	    goto next_loop;
	  end_loop:
	  end_1:;
	}
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = eval_list;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = eval_list_tail;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = eval_list;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = eval_list_tail;
	}
	M_CDR(eval_list_tail) = Nil;
	if (attribute_value_qm)
	    return VALUES_3(attribute_value_qm,Nil,Qnever);
	else
	    return VALUES_3(Nil,Nil,Nil);
    }
}

static Object array_constant_5;    /* # */

/* ROLE-PRINT-CLASS-QUALIFIED-NAME */
Object role_print_class_qualified_name(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,161);
    twrite_symbol(1,SECOND(role));
    twrite_beginning_of_wide_string(array_constant_5,FIX((SI_Long)2L));
    twrite_symbol(1,THIRD(role));
    if (local_variable_qm) {
	twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)1L));
	twrite(local_variable_qm);
    }
    GENSYM_RETURN_ONE(twrite_beginning_of_wide_string(array_constant_1,
	    FIX((SI_Long)3L)));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-CLASS-QUALIFIED-NAME */
Object serve_first_class_qualified_name(role,domain)
    Object role, domain;
{
    Object class_cons, class_1, attribute_name, attribute_value_qm;

    x_note_fn_call(149,162);
    class_cons = M_CDR(role);
    class_1 = M_CAR(class_cons);
    attribute_name = M_CAR(M_CDR(class_cons));
    attribute_value_qm = 
	    frame_or_evaluation_value_user_attribute_value(domain,
	    attribute_name,class_1);
    if (attribute_value_qm)
	return VALUES_3(attribute_value_qm,Nil,Qnever);
    else
	return VALUES_3(Nil,Nil,Nil);
}

/* SERVE-FIRST-CLASS-QUALIFIED-NAME-INVERSE */
Object serve_first_class_qualified_name_inverse(item,quantifier,role,
	    domain_designation)
    Object item, quantifier, role, domain_designation;
{
    Object parent_frame_qm, pretty_name, qualifier;

    x_note_fn_call(149,163);
    parent_frame_qm = get_lookup_slot_value_given_default(item,
	    Qparent_frame,Nil);
    pretty_name = CONSP(role) ? M_CAR(M_CDR(M_CDR(role))) : role;
    qualifier = CONSP(role) ? M_CAR(M_CDR(role)) : Nil;
    if (parent_frame_qm && EQ(item,get_slot_value_function(parent_frame_qm,
	    pretty_name,qualifier)) && 
	    designation_could_denote_item_p(domain_designation,
	    parent_frame_qm) && serve_item_p(parent_frame_qm))
	return VALUES_3(parent_frame_qm,Nil,Qnever);
    else
	return VALUES_3(Nil,Nil,Nil);
}

/* ROLE-PRINT-WORKSPACE */
Object role_print_workspace(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,164);
    GENSYM_RETURN_ONE(print_role_whose_car_is_role_server(role,
	    local_variable_qm));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-WORKSPACE */
Object serve_first_workspace(role,domain)
    Object role, domain;
{
    Object gensymed_symbol, ws;

    x_note_fn_call(149,165);
    gensymed_symbol = ACCESS_ONCE(ISVREF(domain,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    ws = gensymed_symbol;
    if (ws && serve_item_p(ws)) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(domain,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	return VALUES_3(gensymed_symbol,Nil,Qnever);
    }
    else
	return VALUES_3(Nil,Nil,Nil);
}

/* SERVE-FIRST-WORKSPACE-INVERSE */
Object serve_first_workspace_inverse(workspace,quantifier,role,
	    domain_designation)
    Object workspace, quantifier, role, domain_designation;
{
    Object x2, gensymed_symbol, sub_class_bit_vector, ab_queue_form_;
    Object ab_next_queue_element_, frame, item_list, ab_loopvar_;
    Object ab_loopvar__1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(149,166);
    if (SIMPLE_VECTOR_P(workspace) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(workspace)) > (SI_Long)2L &&  
	    !EQ(ISVREF(workspace,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(workspace,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Kb_workspace_class_description,(SI_Long)18L));
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
    if ( !temp)
	return VALUES_3(Nil,Nil,Nil);
    else {
	gensymed_symbol = ACCESS_ONCE(ISVREF(workspace,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	ab_queue_form_ = gensymed_symbol;
	ab_next_queue_element_ = Nil;
	frame = Nil;
	item_list = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	if (ab_queue_form_)
	    ab_next_queue_element_ = 
		    constant_queue_next(ISVREF(ab_queue_form_,(SI_Long)2L),
		    ab_queue_form_);
      next_loop:
	if ( !TRUEP(ab_next_queue_element_))
	    goto end_loop;
	frame = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	ab_next_queue_element_ = 
		constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	if (ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)16L) && 
		serve_item_p(frame) && 
		designation_could_denote_item_p(domain_designation,frame)) {
	    ab_loopvar__1 = eval_cons_1(frame,Nil);
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		item_list = ab_loopvar__1;
	    ab_loopvar_ = ab_loopvar__1;
	}
	goto next_loop;
      end_loop:
	return serve_all_unreprocessed_frames(item_list);
	return VALUES_1(Qnil);
    }
}

static Object string_constant_31;  /* " upon" */

/* ROLE-PRINT-UPON */
Object role_print_upon(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,167);
    GENSYM_RETURN_ONE(print_standard_two_element_role(role,
	    local_variable_qm,string_constant_31));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-UPON */
Object serve_first_upon(role,domain)
    Object role, domain;
{
    Object class_1, class_description, gensymed_symbol, ab_queue_form_;
    Object ab_next_queue_element_, frame, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, sub_class_bit_vector, temp_1;
    SI_Long counts, superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(149,168);
    class_1 = SECOND(role);
    class_description = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    if ( !TRUEP(class_description) ||  !TRUEP(ISVREF(class_description,
	    (SI_Long)16L)))
	return VALUES_3(Nil,Nil,Nil);
    else {
	gensymed_symbol = ACCESS_ONCE(ISVREF(domain,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	ab_queue_form_ = gensymed_symbol;
	ab_next_queue_element_ = Nil;
	frame = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	counts = (SI_Long)0L;
	if (ab_queue_form_)
	    ab_next_queue_element_ = 
		    constant_queue_next(ISVREF(ab_queue_form_,(SI_Long)2L),
		    ab_queue_form_);
      next_loop:
	if ( !TRUEP(ab_next_queue_element_))
	    goto end_loop;
	frame = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	ab_next_queue_element_ = 
		constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	gensymed_symbol = ISVREF(frame,(SI_Long)1L);
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(class_description,
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
	    ab_loopvar__2 = eval_cons_1(frame,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    if (frame)
		counts = counts + (SI_Long)1L;
	}
	if (There_exists_p && (SI_Long)0L < counts)
	    goto end_loop;
	goto next_loop;
      end_loop:
	temp_1 = ab_loopvar_;
	goto end_1;
	temp_1 = Qnil;
      end_1:;
	return serve_all_unreprocessed_frames(temp_1);
    }
}

/* SERVE-FIRST-UPON-INVERSE */
Object serve_first_upon_inverse(item,quantifier,role,domain_designation)
    Object item, quantifier, role, domain_designation;
{
    Object gensymed_symbol, kb_workspace_qm, temp_1, ab_queue_form_;
    Object ab_next_queue_element_, frame, symbol, sub_class_bit_vector, temp_2;
    SI_Long ab_loopvar_, superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(149,169);
    gensymed_symbol = ACCESS_ONCE(ISVREF(item,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    kb_workspace_qm = gensymed_symbol;
    if (kb_workspace_qm && 
	    designation_could_denote_item_p(domain_designation,
	    kb_workspace_qm)) {
	temp =  !EQ(quantifier,Qthe);
	if (temp);
	else {
	    temp_1 = FIX((SI_Long)1L);
	    gensymed_symbol = ACCESS_ONCE(ISVREF(kb_workspace_qm,
		    (SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	    ab_queue_form_ = gensymed_symbol;
	    ab_next_queue_element_ = Nil;
	    frame = Nil;
	    ab_loopvar_ = (SI_Long)0L;
	    if (ab_queue_form_)
		ab_next_queue_element_ = 
			constant_queue_next(ISVREF(ab_queue_form_,
			(SI_Long)2L),ab_queue_form_);
	  next_loop:
	    if ( !TRUEP(ab_next_queue_element_))
		goto end_loop;
	    frame = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	    ab_next_queue_element_ = 
		    constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	    symbol = SECOND(role);
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
	    if (temp)
		ab_loopvar_ = ab_loopvar_ + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    temp_2 = FIX(ab_loopvar_);
	    goto end_1;
	    temp_2 = Qnil;
	  end_1:;
	    temp = NUM_EQ(temp_1,temp_2);
	}
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_3(kb_workspace_qm,Nil,Qnever);
    else
	return VALUES_3(Nil,Nil,Nil);
}

static Object string_constant_32;  /* "this workspace" */

/* ROLE-PRINT-THIS-WORKSPACE */
Object role_print_this_workspace(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,170);
    GENSYM_RETURN_ONE(twrite(string_constant_32));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-THIS-WORKSPACE */
Object serve_first_this_workspace(role,domain)
    Object role, domain;
{
    Object gensymed_symbol, workspace_qm;
    Object result;

    x_note_fn_call(149,171);
    result = get_block_on_workspace_for_frame(Current_computation_frame);
    gensymed_symbol = NTH_VALUE((SI_Long)1L, result);
    workspace_qm = gensymed_symbol;
    if (workspace_qm && serve_item_p(workspace_qm))
	return VALUES_3(workspace_qm,Nil,Qnever);
    else
	return VALUES_3(Nil,Nil,Nil);
}

/* SERVE-FIRST-THIS-WORKSPACE-INVERSE */
Object serve_first_this_workspace_inverse(kb_workspace,quantifier,role,
	    domain_designation)
    Object kb_workspace, quantifier, role, domain_designation;
{
    x_note_fn_call(149,172);
    return VALUES_3(Nil,Nil,Nil);
}

static Object string_constant_33;  /* "this window" */

/* ROLE-PRINT-THIS-WINDOW */
Object role_print_this_window(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,173);
    GENSYM_RETURN_ONE(twrite(string_constant_33));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-THIS-WINDOW */
Object serve_first_this_window(role,domain)
    Object role, domain;
{
    Object g2_window_or_client_interface_qm;

    x_note_fn_call(149,174);
    g2_window_or_client_interface_qm = serve_this_window(role,domain);
    if (g2_window_or_client_interface_qm && 
	    serve_item_p(g2_window_or_client_interface_qm))
	return VALUES_3(g2_window_or_client_interface_qm,Nil,Qnever);
    else
	return VALUES_3(Nil,Nil,Nil);
}

static Object string_constant_34;  /* " that is a superior-class of" */

/* ROLE-PRINT-SUPERIOR-CLASS */
Object role_print_superior_class(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,175);
    GENSYM_RETURN_ONE(print_standard_two_element_role(role,
	    local_variable_qm,string_constant_34));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-SUPERIOR-CLASS */
Object serve_first_superior_class(role,domain)
    Object role, domain;
{
    Object class_name, temp, system_class_p_qm, superior_classes_qm, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp_1, entry_hash;
    Object gensymed_symbol, tail, head, new_cons, temp_2, svref_arg_2;
    Object svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, class_1, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, val_to_serve, rest_qm;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_3;
    Object result;

    x_note_fn_call(149,176);
    class_name = domain;
    if (lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop)) {
	temp = lookup_global_or_kb_specific_property_value(class_name,
		Class_definition_gkbprop);
	system_class_p_qm = CONSP(temp) ? T : Nil;
    }
    else
	system_class_p_qm = Nil;
    if (system_class_p_qm) {
	if (EQ(class_name,Qitem))
	    superior_classes_qm = Nil;
	else {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = class_name;
	    key_hash_value = SXHASH_SYMBOL_1(class_name) & 
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
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
	    MVS_2(result,succ,marked);
	  next_loop_2:
	    if ( !TRUEP(marked))
		goto end_loop_1;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
	    MVS_2(result,succ,marked);
	    goto next_loop_2;
	  end_loop_1:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = class_name;
		temp_1 = Symbol_properties_table;
		temp = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
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
		gensymed_symbol = set_skip_list_entry(temp_1,
			FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp,
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
	  next_loop_3:
	    if (level < ab_loop_bind_)
		goto end_loop_3;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_4:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
	    MVS_2(result,succ,marked);
	  next_loop_5:
	    if ( !TRUEP(marked))
		goto end_loop_4;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
	    MVS_2(result,succ,marked);
	    goto next_loop_5;
	  end_loop_4:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
	      next_loop_6:
		if (level < ab_loop_bind_)
		    goto end_loop_6;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_7:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_8:
		if ( !TRUEP(marked))
		    goto end_loop_7;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
		goto next_loop_8;
	      end_loop_7:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
	      next_loop_9:
		if (level < ab_loop_bind_)
		    goto end_loop_9;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_10:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_11:
		if ( !TRUEP(marked))
		    goto end_loop_10;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
		goto next_loop_11;
	      end_loop_10:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
	    if (gensymed_symbol && ISVREF(gensymed_symbol,(SI_Long)16L))
		superior_classes_qm = 
			lookup_global_or_kb_specific_property_value(class_name,
			Direct_superior_classes_gkbprop);
	    else
		superior_classes_qm = Nil;
	}
    }
    else
	superior_classes_qm = 
		lookup_global_or_kb_specific_property_value(class_name,
		Direct_superior_classes_gkbprop);
    class_1 = Nil;
    ab_loop_list_ = superior_classes_qm;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_12:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_12;
    class_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp_3 =  !TRUEP(system_class_p_qm);
    if (temp_3);
    else {
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
      next_loop_13:
	if (level < ab_loop_bind_)
	    goto end_loop_13;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_14:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp);
	MVS_2(result,succ,marked);
      next_loop_15:
	if ( !TRUEP(marked))
	    goto end_loop_14;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp);
	MVS_2(result,succ,marked);
	goto next_loop_15;
      end_loop_14:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_5;
	goto next_loop_14;
      end_loop_15:
      end_5:
	level = level - (SI_Long)1L;
	goto next_loop_13;
      end_loop_13:;
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = class_1;
	    temp_1 = Symbol_properties_table;
	    temp = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
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
	    gensymed_symbol = set_skip_list_entry(temp_1,FIX((SI_Long)31L),
		    Qeq,Nil,T,gensymed_symbol,temp,gensymed_symbol_1);
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
      next_loop_16:
	if (level < ab_loop_bind_)
	    goto end_loop_16;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_17:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp);
	MVS_2(result,succ,marked);
      next_loop_18:
	if ( !TRUEP(marked))
	    goto end_loop_17;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp);
	MVS_2(result,succ,marked);
	goto next_loop_18;
      end_loop_17:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_6;
	goto next_loop_17;
      end_loop_18:
      end_6:
	level = level - (SI_Long)1L;
	goto next_loop_16;
      end_loop_16:;
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
	  next_loop_19:
	    if (level < ab_loop_bind_)
		goto end_loop_19;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_20:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
	    MVS_2(result,succ,marked);
	  next_loop_21:
	    if ( !TRUEP(marked))
		goto end_loop_20;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
	    MVS_2(result,succ,marked);
	    goto next_loop_21;
	  end_loop_20:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_7;
	    goto next_loop_20;
	  end_loop_21:
	  end_7:
	    level = level - (SI_Long)1L;
	    goto next_loop_19;
	  end_loop_19:;
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
	  next_loop_22:
	    if (level < ab_loop_bind_)
		goto end_loop_22;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_23:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
	    MVS_2(result,succ,marked);
	  next_loop_24:
	    if ( !TRUEP(marked))
		goto end_loop_23;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
	    MVS_2(result,succ,marked);
	    goto next_loop_24;
	  end_loop_23:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_8;
	    goto next_loop_23;
	  end_loop_24:
	  end_8:
	    level = level - (SI_Long)1L;
	    goto next_loop_22;
	  end_loop_22:;
	    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (resulting_value);
	    else
		resulting_value = Nil;
	}
	gensymed_symbol = resulting_value;
	temp_3 = gensymed_symbol ? TRUEP(ISVREF(gensymed_symbol,
		(SI_Long)16L)) : TRUEP(Qnil);
    }
    if (temp_3) {
	ab_loopvar__2 = eval_cons_1(class_1,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop_12;
  end_loop_12:
    gensymed_symbol = ab_loopvar_;
    goto end_9;
    gensymed_symbol = Qnil;
  end_9:;
    if ( !TRUEP(gensymed_symbol))
	return VALUES_3(Nil,Nil,Nil);
    else {
	val_to_serve = M_CAR(gensymed_symbol);
	rest_qm = M_CDR(gensymed_symbol);
	if (rest_qm) {
	    temp_2 = SYMBOL_FUNCTION(Qserve_next_evaluation_value);
	    M_CAR(gensymed_symbol) = temp_2;
	    return VALUES_3(val_to_serve,gensymed_symbol,Qnever);
	}
	else {
	    inline_note_reclaim_cons(gensymed_symbol,Qeval);
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_2 = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_2) = gensymed_symbol;
		temp_2 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_2,svref_arg_2) = gensymed_symbol;
	    }
	    else {
		temp_2 = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_2,svref_arg_2) = gensymed_symbol;
		temp_2 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_2,svref_arg_2) = gensymed_symbol;
	    }
	    M_CDR(gensymed_symbol) = Nil;
	    return VALUES_3(val_to_serve,Nil,Qnever);
	}
    }
}

static Object string_constant_35;  /* " that is an inferior-class of" */

/* ROLE-PRINT-INFERIOR-CLASS */
Object role_print_inferior_class(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,177);
    GENSYM_RETURN_ONE(print_standard_two_element_role(role,
	    local_variable_qm,string_constant_35));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-INFERIOR-CLASS */
Object serve_first_inferior_class(role,domain)
    Object role, domain;
{
    Object class_name, inferior_classes_qm, class_1, ab_loop_list_;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, gensymed_symbol;
    Object val_to_serve, rest_qm, temp, svref_arg_2;

    x_note_fn_call(149,178);
    class_name = domain;
    inferior_classes_qm = 
	    lookup_global_or_kb_specific_property_value(class_name,
	    Inferior_classes_gkbprop);
    class_1 = Nil;
    ab_loop_list_ = inferior_classes_qm;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    class_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = eval_cons_1(class_1,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    gensymed_symbol = ab_loopvar_;
    goto end_1;
    gensymed_symbol = Qnil;
  end_1:;
    if ( !TRUEP(gensymed_symbol))
	return VALUES_3(Nil,Nil,Nil);
    else {
	val_to_serve = M_CAR(gensymed_symbol);
	rest_qm = M_CDR(gensymed_symbol);
	if (rest_qm) {
	    temp = SYMBOL_FUNCTION(Qserve_next_evaluation_value);
	    M_CAR(gensymed_symbol) = temp;
	    return VALUES_3(val_to_serve,gensymed_symbol,Qnever);
	}
	else {
	    inline_note_reclaim_cons(gensymed_symbol,Qeval);
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = gensymed_symbol;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = gensymed_symbol;
	    }
	    else {
		temp = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = gensymed_symbol;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = gensymed_symbol;
	    }
	    M_CDR(gensymed_symbol) = Nil;
	    return VALUES_3(val_to_serve,Nil,Qnever);
	}
    }
}

static Object string_constant_36;  /* " that is of the class named by" */

/* ROLE-PRINT-CLASS-INSTANCES-NAMED-BY */
Object role_print_class_instances_named_by(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,179);
    GENSYM_RETURN_ONE(print_standard_two_element_role(role,
	    local_variable_qm,string_constant_36));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-CLASS-INSTANCES-NAMED-BY */
Object serve_first_class_instances_named_by(role,domain)
    Object role, domain;
{
    Object role_class, named_by_class, role_class_description;
    Object named_by_class_description, sub_class_bit_vector, named_instances;
    Object instance, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object gensymed_symbol_3, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(149,180);
    role_class = SECOND(role);
    named_by_class = domain;
    role_class_description = 
	    lookup_global_or_kb_specific_property_value(role_class,
	    Class_description_gkbprop);
    named_by_class_description = 
	    lookup_global_or_kb_specific_property_value(named_by_class,
	    Class_description_gkbprop);
    if ( !TRUEP(role_class_description) ||  
	    !TRUEP(named_by_class_description) ||  
	    !TRUEP(ISVREF(Rule_class_description,(SI_Long)16L)) ||  
	    !TRUEP(ISVREF(named_by_class_description,(SI_Long)16L)))
	return VALUES_3(Nil,Nil,Nil);
    else {
	sub_class_bit_vector = ISVREF(named_by_class_description,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(role_class_description,
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
	if (temp)
	    return serve_all_unreprocessed_frames(collect_instances_of_class_for_role_service(named_by_class));
	else {
	    sub_class_bit_vector = ISVREF(role_class_description,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(named_by_class_description,(SI_Long)18L));
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
		return serve_all_unreprocessed_frames(collect_instances_of_class_for_role_service(role_class));
	    else {
		named_instances = 
			collect_instances_of_class_for_role_service(named_by_class);
		instance = Nil;
		ab_loop_list_ = named_instances;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ab_loopvar__2 = Nil;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		instance = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		gensymed_symbol_3 = ISVREF(instance,(SI_Long)1L);
		sub_class_bit_vector = ISVREF(gensymed_symbol_3,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(role_class_description,(SI_Long)18L));
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
		    temp = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    ab_loopvar__2 = eval_cons_1(instance,Nil);
		    if (ab_loopvar__1)
			M_CDR(ab_loopvar__1) = ab_loopvar__2;
		    else
			ab_loopvar_ = ab_loopvar__2;
		    ab_loopvar__1 = ab_loopvar__2;
		}
		goto next_loop;
	      end_loop:
		reclaim_eval_list_1(named_instances);
		temp_1 = ab_loopvar_;
		goto end_1;
		temp_1 = Qnil;
	      end_1:;
		return serve_all_unreprocessed_frames(temp_1);
	    }
	}
    }
}

static Object string_constant_37;  /* "this rule" */

/* ROLE-PRINT-THIS-RULE */
Object role_print_this_rule(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,181);
    GENSYM_RETURN_ONE(twrite(string_constant_37));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-THIS-RULE */
Object serve_first_this_rule(role,domain)
    Object role, domain;
{
    Object this_frame, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(149,182);
    this_frame = Current_computation_frame;
    sub_class_bit_vector = ISVREF(ISVREF(this_frame,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Rule_class_description,
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
    if (temp)
	return VALUES_3(this_frame,Nil,Qnever);
    else
	return VALUES_3(Nil,Nil,Nil);
}

/* SERVE-FIRST-THIS-RULE-INVERSE */
Object serve_first_this_rule_inverse(rule,quantifier,role,domain_designation)
    Object rule, quantifier, role, domain_designation;
{
    x_note_fn_call(149,183);
    return VALUES_3(Nil,Nil,Nil);
}

static Object string_constant_38;  /* "this procedure" */

/* ROLE-PRINT-THIS-PROCEDURE */
Object role_print_this_procedure(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,184);
    GENSYM_RETURN_ONE(twrite(string_constant_38));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-THIS-PROCEDURE */
Object serve_first_this_procedure(role,domain)
    Object role, domain;
{
    Object this_frame, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(149,185);
    this_frame = Current_computation_frame;
    sub_class_bit_vector = ISVREF(ISVREF(this_frame,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Procedure_class_description,
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
    if (temp)
	return VALUES_3(this_frame,Nil,Qnever);
    else
	return VALUES_3(Nil,Nil,Nil);
}

static Object string_constant_39;  /* "this procedure-invocation" */

/* ROLE-PRINT-THIS-PROCEDURE-INVOCATION */
Object role_print_this_procedure_invocation(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,186);
    GENSYM_RETURN_ONE(twrite(string_constant_39));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-THIS-PROCEDURE-INVOCATION */
Object serve_first_this_procedure_invocation(role,domain)
    Object role, domain;
{
    Object this_procedure_invocation_frame_qm;

    x_note_fn_call(149,187);
    this_procedure_invocation_frame_qm = 
	    get_current_procedure_invocation_frame_if_any();
    if (this_procedure_invocation_frame_qm)
	return VALUES_3(this_procedure_invocation_frame_qm,Nil,Qnever);
    else
	return VALUES_3(Nil,Nil,Nil);
}

static Object array_constant_6;    /* # */

/* ROLE-PRINT-RELATED */
Object role_print_related(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,188);
    print_user_or_datum_type(THIRD(role));
    if (local_variable_qm) {
	twrite_character(FIX((SI_Long)32L));
	twrite_symbol(1,local_variable_qm);
    }
    twrite_beginning_of_wide_string(array_constant_6,FIX((SI_Long)9L));
    GENSYM_RETURN_ONE(twrite_symbol(1,SECOND(role)));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-RELATED */
Object serve_first_related(role,domain)
    Object role, domain;
{
    Object class_1, class_description, given_name, gensymed_symbol, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp, temp_1;
    Object entry_hash, unfiltered_related_items, scope_conses, ab_node_stack_;
    Object ab_current_node_, ab_skip_list_form_, ab_binary_tree_form_;
    Object ab_skip_list_p_, ab_next_node_, ab_tail_node_, ab_current_alist_;
    Object ab_entry_cons_, item, result_1, ab_loopvar_, ab_loopvar__1;
    Object ab_less_than_branch_qm_, sub_class_bit_vector;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_2;
    Declare_special(1);
    Object result;

    x_note_fn_call(149,189);
    class_1 = THIRD(role);
    class_description = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    if ( !TRUEP(class_description) ||  !TRUEP(ISVREF(class_description,
	    (SI_Long)16L)))
	return VALUES_3(Nil,Nil,Nil);
    else {
	given_name = SECOND(role);
	gensymed_symbol = domain;
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)12L);
	if (gensymed_symbol) {
	    skip_list = CDR(gensymed_symbol);
	    key_value = given_name;
	    key_hash_value = SXHASH_SYMBOL_1(given_name) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)7L;
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
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    unfiltered_related_items = gensymed_symbol ? 
		    ISVREF(gensymed_symbol,(SI_Long)2L) : Nil;
	}
	else
	    unfiltered_related_items = Nil;
	if (unfiltered_related_items) {
	    scope_conses = Scope_conses;
	    ab_node_stack_ = Nil;
	    ab_current_node_ = Nil;
	    ab_skip_list_form_ = unfiltered_related_items;
	    ab_binary_tree_form_ = unfiltered_related_items;
	    gensymed_symbol = CDR(unfiltered_related_items);
	    if (CONSP(gensymed_symbol)) {
		temp_1 = M_CAR(gensymed_symbol);
		temp_2 = SIMPLE_VECTOR_P(temp_1);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		temp_1 = M_CDR(gensymed_symbol);
		ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
	    }
	    else
		ab_skip_list_p_ = Nil;
	    ab_next_node_ = Nil;
	    ab_tail_node_ = Nil;
	    ab_current_alist_ = Nil;
	    ab_entry_cons_ = Nil;
	    item = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
	      result_1 = Nil;
	      ab_loopvar_ = Nil;
	      ab_loopvar__1 = Nil;
	      if (ab_skip_list_p_) {
		  ab_next_node_ = 
			  ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
			  (SI_Long)0L),(SI_Long)0L));
		  ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
		  if (EQ(ab_next_node_,ab_tail_node_))
		      ab_next_node_ = Nil;
	      }
	      else
		  ab_next_node_ = M_CDR(ab_binary_tree_form_);
	    next_loop_3:
	      if (ab_current_alist_) {
		  ab_entry_cons_ = M_CAR(ab_current_alist_);
		  ab_current_alist_ = M_CDR(ab_current_alist_);
	      }
	      else if (ab_skip_list_p_) {
		  if (ab_next_node_) {
		      ab_current_node_ = ab_next_node_;
		      ab_next_node_ = 
			      ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node_,
			      (SI_Long)0L),(SI_Long)0L));
		      if (EQ(ab_next_node_,ab_tail_node_))
			  ab_next_node_ = Nil;
		      ab_entry_cons_ = scope_cons(ISVREF(ab_current_node_,
			      (SI_Long)2L),ISVREF(ab_current_node_,
			      (SI_Long)3L));
		  }
		  else
		      ab_current_node_ = Nil;
	      }
	      else {
		  if (ab_next_node_) {
		      ab_current_node_ = ab_next_node_;
		      ab_less_than_branch_qm_ = Nil;
		    next_loop_4:
		      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			      (SI_Long)1L);
		      if ( !TRUEP(ab_less_than_branch_qm_))
			  goto end_loop_3;
		      ab_node_stack_ = scope_cons(ab_current_node_,
			      ab_node_stack_);
		      ab_current_node_ = ab_less_than_branch_qm_;
		      goto next_loop_4;
		    end_loop_3:;
		  }
		  else if (ab_node_stack_) {
		      ab_next_node_ = ab_node_stack_;
		      ab_current_node_ = M_CAR(ab_node_stack_);
		      ab_node_stack_ = M_CDR(ab_node_stack_);
		  }
		  else
		      ab_current_node_ = Nil;
		  if (ab_current_node_) {
		      ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
		      ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
		      ab_entry_cons_ = M_CAR(ab_current_alist_);
		      ab_current_alist_ = M_CDR(ab_current_alist_);
		  }
	      }
	      if ( !TRUEP(ab_current_node_))
		  goto end_loop_4;
	      item = M_CDR(ab_entry_cons_);
	      if (item && serve_item_p(item)) {
		  gensymed_symbol = ISVREF(item,(SI_Long)1L);
		  sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(class_description,(SI_Long)18L));
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
		      gensymed_symbol_2 = gensymed_symbol_2 << 
			      gensymed_symbol_3;
		      gensymed_symbol_1 = gensymed_symbol_1 & 
			      gensymed_symbol_2;
		      temp_2 = (SI_Long)0L < gensymed_symbol_1;
		  }
		  else
		      temp_2 = TRUEP(Nil);
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      if (temp_2) {
		  ab_loopvar__1 = eval_cons_1(item,Nil);
		  if (ab_loopvar_)
		      M_CDR(ab_loopvar_) = ab_loopvar__1;
		  else
		      result_1 = ab_loopvar__1;
		  ab_loopvar_ = ab_loopvar__1;
	      }
	      goto next_loop_3;
	    end_loop_4:
	      result = serve_all_unreprocessed_frames(result_1);
	      goto end_2;
	      result = VALUES_1(Qnil);
	    end_2:;
	    POP_SPECIAL();
	    return result;
	}
	else
	    return serve_all_unreprocessed_frames(Nil);
    }
}

static Object Qrelation;           /* relation */

/* SERVE-FIRST-RELATED-INVERSE */
Object serve_first_related_inverse(item,quantifier,role,domain_designation)
    Object item, quantifier, role, domain_designation;
{
    Object relation, given_name, other_name, class_1, gensymed_symbol;
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, subject_unfiltered_list, scope_conses;
    Object ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_binary_tree_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_less_than_branch_qm_, item_2;
    Object result_1, ab_loopvar_, ab_loopvar__1, relation_instances;
    Object relation_instance, forward_instances, ab_node_stack__1;
    Object ab_current_node__1, ab_skip_list_p__1, ab_next_node__1;
    Object ab_tail_node__1, ab_current_alist__1, ab_entry_cons__1;
    Object possible_unique_item, item_list, ab_loopvar__2, ab_node_stack__2;
    Object ab_current_node__2, ab_skip_list_p__2, ab_next_node__2;
    Object ab_tail_node__2, ab_current_alist__2, ab_entry_cons__2;
    Object the_only_item, sub_class_bit_vector;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_2;
    Declare_special(3);
    Object result;

    x_note_fn_call(149,190);
    relation = get_instance_with_name_if_any(Qrelation,SECOND(role));
    given_name = SECOND(role);
    if ( !TRUEP(relation))
	other_name = Nil;
    else if (ISVREF(relation,(SI_Long)25L))
	other_name = given_name;
    else if (EQ(given_name,ISVREF(relation,(SI_Long)22L))) {
	other_name = ISVREF(relation,(SI_Long)23L);
	if (other_name);
	else
	    other_name = ISVREF(relation,(SI_Long)26L);
    }
    else
	other_name = ISVREF(relation,(SI_Long)22L);
    class_1 = THIRD(role);
    if (other_name) {
	gensymed_symbol = item;
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)12L);
	if (gensymed_symbol) {
	    skip_list = CDR(gensymed_symbol);
	    key_value = other_name;
	    key_hash_value = SXHASH_SYMBOL_1(other_name) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)7L;
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
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    subject_unfiltered_list = gensymed_symbol ? 
		    ISVREF(gensymed_symbol,(SI_Long)2L) : Nil;
	}
	else
	    subject_unfiltered_list = Nil;
    }
    else
	subject_unfiltered_list = Nil;
    temp_2 =  !TRUEP(subject_unfiltered_list);
    if (temp_2);
    else {
	gensymed_symbol = CDR(subject_unfiltered_list);
	if (CONSP(gensymed_symbol)) {
	    temp_1 = M_CAR(gensymed_symbol);
	    temp_2 = SIMPLE_VECTOR_P(temp_1);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    temp_1 = M_CDR(gensymed_symbol);
	    temp_2 = SIMPLE_VECTOR_P(temp_1);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    gensymed_symbol = M_CDR(subject_unfiltered_list);
	    temp_1 = 
		    ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(gensymed_symbol),
		    (SI_Long)0L),(SI_Long)0L));
	    temp_2 = EQ(temp_1,M_CDR(gensymed_symbol));
	}
	else
	    temp_2 =  !TRUEP(M_CDR(subject_unfiltered_list));
	if (temp_2);
	else {
	    scope_conses = Scope_conses;
	    ab_node_stack_ = Nil;
	    ab_current_node_ = Nil;
	    ab_skip_list_form_ = subject_unfiltered_list;
	    ab_binary_tree_form_ = subject_unfiltered_list;
	    gensymed_symbol = CDR(subject_unfiltered_list);
	    if (CONSP(gensymed_symbol)) {
		temp_1 = M_CAR(gensymed_symbol);
		temp_2 = SIMPLE_VECTOR_P(temp_1);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		temp_1 = M_CDR(gensymed_symbol);
		ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
	    }
	    else
		ab_skip_list_p_ = Nil;
	    ab_next_node_ = Nil;
	    ab_tail_node_ = Nil;
	    ab_current_alist_ = Nil;
	    ab_entry_cons_ = Nil;
	    item = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
	      if (ab_skip_list_p_) {
		  ab_next_node_ = 
			  ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
			  (SI_Long)0L),(SI_Long)0L));
		  ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
		  if (EQ(ab_next_node_,ab_tail_node_))
		      ab_next_node_ = Nil;
	      }
	      else
		  ab_next_node_ = M_CDR(ab_binary_tree_form_);
	    next_loop_3:
	      if (ab_current_alist_) {
		  ab_entry_cons_ = M_CAR(ab_current_alist_);
		  ab_current_alist_ = M_CDR(ab_current_alist_);
	      }
	      else if (ab_skip_list_p_) {
		  if (ab_next_node_) {
		      ab_current_node_ = ab_next_node_;
		      ab_next_node_ = 
			      ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node_,
			      (SI_Long)0L),(SI_Long)0L));
		      if (EQ(ab_next_node_,ab_tail_node_))
			  ab_next_node_ = Nil;
		      ab_entry_cons_ = scope_cons(ISVREF(ab_current_node_,
			      (SI_Long)2L),ISVREF(ab_current_node_,
			      (SI_Long)3L));
		  }
		  else
		      ab_current_node_ = Nil;
	      }
	      else {
		  if (ab_next_node_) {
		      ab_current_node_ = ab_next_node_;
		      ab_less_than_branch_qm_ = Nil;
		    next_loop_4:
		      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			      (SI_Long)1L);
		      if ( !TRUEP(ab_less_than_branch_qm_))
			  goto end_loop_3;
		      ab_node_stack_ = scope_cons(ab_current_node_,
			      ab_node_stack_);
		      ab_current_node_ = ab_less_than_branch_qm_;
		      goto next_loop_4;
		    end_loop_3:;
		  }
		  else if (ab_node_stack_) {
		      ab_next_node_ = ab_node_stack_;
		      ab_current_node_ = M_CAR(ab_node_stack_);
		      ab_node_stack_ = M_CDR(ab_node_stack_);
		  }
		  else
		      ab_current_node_ = Nil;
		  if (ab_current_node_) {
		      ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
		      ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
		      ab_entry_cons_ = M_CAR(ab_current_alist_);
		      ab_current_alist_ = M_CDR(ab_current_alist_);
		  }
	      }
	      if ( !TRUEP(ab_current_node_))
		  goto end_loop_4;
	      item = M_CDR(ab_entry_cons_);
	      if (item) {
		  temp_2 = TRUEP(Nil);
		  goto end_2;
	      }
	      goto next_loop_3;
	    end_loop_4:
	      temp_2 = TRUEP(T);
	      goto end_2;
	      temp_2 = TRUEP(Qnil);
	    end_2:;
	    POP_SPECIAL();
	}
    }
    if (temp_2)
	return VALUES_3(Nil,Nil,Nil);
    if ( !EQ(quantifier,Qthe)) {
	scope_conses = Scope_conses;
	ab_node_stack_ = Nil;
	ab_current_node_ = Nil;
	ab_skip_list_form_ = subject_unfiltered_list;
	ab_binary_tree_form_ = subject_unfiltered_list;
	gensymed_symbol = CDR(subject_unfiltered_list);
	if (CONSP(gensymed_symbol)) {
	    temp_1 = M_CAR(gensymed_symbol);
	    temp_2 = SIMPLE_VECTOR_P(temp_1);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    temp_1 = M_CDR(gensymed_symbol);
	    ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
	}
	else
	    ab_skip_list_p_ = Nil;
	ab_next_node_ = Nil;
	ab_tail_node_ = Nil;
	ab_current_alist_ = Nil;
	ab_entry_cons_ = Nil;
	item_2 = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  result_1 = Nil;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  if (ab_skip_list_p_) {
	      ab_next_node_ = 
		      ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
		      (SI_Long)0L),(SI_Long)0L));
	      ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
	      if (EQ(ab_next_node_,ab_tail_node_))
		  ab_next_node_ = Nil;
	  }
	  else
	      ab_next_node_ = M_CDR(ab_binary_tree_form_);
	next_loop_5:
	  if (ab_current_alist_) {
	      ab_entry_cons_ = M_CAR(ab_current_alist_);
	      ab_current_alist_ = M_CDR(ab_current_alist_);
	  }
	  else if (ab_skip_list_p_) {
	      if (ab_next_node_) {
		  ab_current_node_ = ab_next_node_;
		  ab_next_node_ = 
			  ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node_,
			  (SI_Long)0L),(SI_Long)0L));
		  if (EQ(ab_next_node_,ab_tail_node_))
		      ab_next_node_ = Nil;
		  ab_entry_cons_ = scope_cons(ISVREF(ab_current_node_,
			  (SI_Long)2L),ISVREF(ab_current_node_,(SI_Long)3L));
	      }
	      else
		  ab_current_node_ = Nil;
	  }
	  else {
	      if (ab_next_node_) {
		  ab_current_node_ = ab_next_node_;
		  ab_less_than_branch_qm_ = Nil;
		next_loop_6:
		  ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			  (SI_Long)1L);
		  if ( !TRUEP(ab_less_than_branch_qm_))
		      goto end_loop_5;
		  ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
		  ab_current_node_ = ab_less_than_branch_qm_;
		  goto next_loop_6;
		end_loop_5:;
	      }
	      else if (ab_node_stack_) {
		  ab_next_node_ = ab_node_stack_;
		  ab_current_node_ = M_CAR(ab_node_stack_);
		  ab_node_stack_ = M_CDR(ab_node_stack_);
	      }
	      else
		  ab_current_node_ = Nil;
	      if (ab_current_node_) {
		  ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
		  ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
		  ab_entry_cons_ = M_CAR(ab_current_alist_);
		  ab_current_alist_ = M_CDR(ab_current_alist_);
	      }
	  }
	  if ( !TRUEP(ab_current_node_))
	      goto end_loop_6;
	  item_2 = M_CDR(ab_entry_cons_);
	  if (serve_item_p(item_2) && 
		  designation_could_denote_item_p(domain_designation,item_2)) {
	      ab_loopvar__1 = eval_cons_1(item_2,Nil);
	      if (ab_loopvar_)
		  M_CDR(ab_loopvar_) = ab_loopvar__1;
	      else
		  result_1 = ab_loopvar__1;
	      ab_loopvar_ = ab_loopvar__1;
	  }
	  goto next_loop_5;
	end_loop_6:
	  result = serve_all_unreprocessed_frames(result_1);
	  goto end_3;
	  result = VALUES_1(Qnil);
	end_3:;
	POP_SPECIAL();
	return result;
    }
    else {
	scope_conses = Scope_conses;
	ab_node_stack_ = Nil;
	ab_current_node_ = Nil;
	ab_skip_list_form_ = subject_unfiltered_list;
	ab_binary_tree_form_ = subject_unfiltered_list;
	gensymed_symbol = CDR(subject_unfiltered_list);
	if (CONSP(gensymed_symbol)) {
	    temp_1 = M_CAR(gensymed_symbol);
	    temp_2 = SIMPLE_VECTOR_P(temp_1);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    temp_1 = M_CDR(gensymed_symbol);
	    ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
	}
	else
	    ab_skip_list_p_ = Nil;
	ab_next_node_ = Nil;
	ab_tail_node_ = Nil;
	ab_current_alist_ = Nil;
	ab_entry_cons_ = Nil;
	item_2 = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,2);
	  result_1 = Nil;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  if (ab_skip_list_p_) {
	      ab_next_node_ = 
		      ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
		      (SI_Long)0L),(SI_Long)0L));
	      ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
	      if (EQ(ab_next_node_,ab_tail_node_))
		  ab_next_node_ = Nil;
	  }
	  else
	      ab_next_node_ = M_CDR(ab_binary_tree_form_);
	next_loop_7:
	  if (ab_current_alist_) {
	      ab_entry_cons_ = M_CAR(ab_current_alist_);
	      ab_current_alist_ = M_CDR(ab_current_alist_);
	  }
	  else if (ab_skip_list_p_) {
	      if (ab_next_node_) {
		  ab_current_node_ = ab_next_node_;
		  ab_next_node_ = 
			  ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node_,
			  (SI_Long)0L),(SI_Long)0L));
		  if (EQ(ab_next_node_,ab_tail_node_))
		      ab_next_node_ = Nil;
		  ab_entry_cons_ = scope_cons(ISVREF(ab_current_node_,
			  (SI_Long)2L),ISVREF(ab_current_node_,(SI_Long)3L));
	      }
	      else
		  ab_current_node_ = Nil;
	  }
	  else {
	      if (ab_next_node_) {
		  ab_current_node_ = ab_next_node_;
		  ab_less_than_branch_qm_ = Nil;
		next_loop_8:
		  ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			  (SI_Long)1L);
		  if ( !TRUEP(ab_less_than_branch_qm_))
		      goto end_loop_7;
		  ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
		  ab_current_node_ = ab_less_than_branch_qm_;
		  goto next_loop_8;
		end_loop_7:;
	      }
	      else if (ab_node_stack_) {
		  ab_next_node_ = ab_node_stack_;
		  ab_current_node_ = M_CAR(ab_node_stack_);
		  ab_node_stack_ = M_CDR(ab_node_stack_);
	      }
	      else
		  ab_current_node_ = Nil;
	      if (ab_current_node_) {
		  ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
		  ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
		  ab_entry_cons_ = M_CAR(ab_current_alist_);
		  ab_current_alist_ = M_CDR(ab_current_alist_);
	      }
	  }
	  if ( !TRUEP(ab_current_node_))
	      goto end_loop_8;
	  item_2 = M_CDR(ab_entry_cons_);
	  if (serve_item_p(item_2) && 
		  designation_could_denote_item_p(domain_designation,item_2)) {
	      relation_instances = ISVREF(item_2,(SI_Long)12L);
	      if (relation_instances) {
		  skip_list = CDR(relation_instances);
		  key_value = given_name;
		  key_hash_value = SXHASH_SYMBOL_1(given_name) & 
			  IFIX(Most_positive_fixnum);
		  bottom_level = (SI_Long)0L;
		  marked = Nil;
		  pred = M_CAR(skip_list);
		  curr = Nil;
		  succ = Nil;
		  level = (SI_Long)7L;
		  ab_loop_bind_ = bottom_level;
		next_loop_9:
		  if (level < ab_loop_bind_)
		      goto end_loop_9;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		next_loop_10:
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp = ATOMIC_REF_OBJECT(reference);
		  temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp,temp_1);
		  MVS_2(result,succ,marked);
		next_loop_11:
		  if ( !TRUEP(marked))
		      goto end_loop_10;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp = ATOMIC_REF_OBJECT(reference);
		  temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp,temp_1);
		  MVS_2(result,succ,marked);
		  goto next_loop_11;
		end_loop_10:
		  entry_hash = ISVREF(curr,(SI_Long)1L);
		  if (IFIX(entry_hash) < key_hash_value || 
			  IFIX(entry_hash) == key_hash_value &&  
			  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
		  relation_instance = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			  key_hash_value ? (EQ(key_value,ISVREF(curr,
			  (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) :
			   Nil;
		  if (relation_instance) {
		      forward_instances = ISVREF(relation_instance,
			      (SI_Long)2L);
		      if (forward_instances) {
			  scope_conses = Scope_conses;
			  ab_node_stack__1 = Nil;
			  ab_current_node__1 = Nil;
			  ab_skip_list_form_ = forward_instances;
			  ab_binary_tree_form_ = forward_instances;
			  gensymed_symbol = CDR(forward_instances);
			  if (CONSP(gensymed_symbol)) {
			      temp_1 = M_CAR(gensymed_symbol);
			      temp_2 = SIMPLE_VECTOR_P(temp_1);
			  }
			  else
			      temp_2 = TRUEP(Nil);
			  if (temp_2) {
			      temp_1 = M_CDR(gensymed_symbol);
			      ab_skip_list_p__1 = SIMPLE_VECTOR_P(temp_1) ?
				       T : Nil;
			  }
			  else
			      ab_skip_list_p__1 = Nil;
			  ab_next_node__1 = Nil;
			  ab_tail_node__1 = Nil;
			  ab_current_alist__1 = Nil;
			  ab_entry_cons__1 = Nil;
			  possible_unique_item = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
				  1);
			    item_list = Nil;
			    ab_loopvar__1 = Nil;
			    ab_loopvar__2 = Nil;
			    if (ab_skip_list_p__1) {
				ab_next_node__1 = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
					(SI_Long)0L),(SI_Long)0L));
				ab_tail_node__1 = 
					M_CDR(M_CDR(ab_skip_list_form_));
				if (EQ(ab_next_node__1,ab_tail_node__1))
				    ab_next_node__1 = Nil;
			    }
			    else
				ab_next_node__1 = M_CDR(ab_binary_tree_form_);
			    if (only_one_related_item_p(forward_instances)) {
				scope_conses = Scope_conses;
				ab_node_stack__2 = Nil;
				ab_current_node__2 = Nil;
				ab_skip_list_form_ = forward_instances;
				ab_binary_tree_form_ = forward_instances;
				gensymed_symbol = CDR(forward_instances);
				if (CONSP(gensymed_symbol)) {
				    temp_1 = M_CAR(gensymed_symbol);
				    temp_2 = SIMPLE_VECTOR_P(temp_1);
				}
				else
				    temp_2 = TRUEP(Nil);
				if (temp_2) {
				    temp_1 = M_CDR(gensymed_symbol);
				    ab_skip_list_p__2 = 
					    SIMPLE_VECTOR_P(temp_1) ? T : Nil;
				}
				else
				    ab_skip_list_p__2 = Nil;
				ab_next_node__2 = Nil;
				ab_tail_node__2 = Nil;
				ab_current_alist__2 = Nil;
				ab_entry_cons__2 = Nil;
				item = Nil;
				PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
					0);
				  if (ab_skip_list_p__2) {
				      ab_next_node__2 = 
					      ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
					      (SI_Long)0L),(SI_Long)0L));
				      ab_tail_node__2 = 
					      M_CDR(M_CDR(ab_skip_list_form_));
				      if (EQ(ab_next_node__2,ab_tail_node__2))
					  ab_next_node__2 = Nil;
				  }
				  else
				      ab_next_node__2 = 
					      M_CDR(ab_binary_tree_form_);
				next_loop_12:
				  if (ab_current_alist__2) {
				      ab_entry_cons__2 = 
					      M_CAR(ab_current_alist__2);
				      ab_current_alist__2 = 
					      M_CDR(ab_current_alist__2);
				  }
				  else if (ab_skip_list_p__2) {
				      if (ab_next_node__2) {
					  ab_current_node__2 = ab_next_node__2;
					  ab_next_node__2 = 
						  ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node__2,
						  (SI_Long)0L),(SI_Long)0L));
					  if (EQ(ab_next_node__2,
						  ab_tail_node__2))
					      ab_next_node__2 = Nil;
					  ab_entry_cons__2 = 
						  scope_cons(ISVREF(ab_current_node__2,
						  (SI_Long)2L),
						  ISVREF(ab_current_node__2,
						  (SI_Long)3L));
				      }
				      else
					  ab_current_node__2 = Nil;
				  }
				  else {
				      if (ab_next_node__2) {
					  ab_current_node__2 = ab_next_node__2;
					  ab_less_than_branch_qm_ = Nil;
					next_loop_13:
					  ab_less_than_branch_qm_ = 
						  ISVREF(ab_current_node__2,
						  (SI_Long)1L);
					  if ( !TRUEP(ab_less_than_branch_qm_))
					      goto end_loop_12;
					  ab_node_stack__2 = 
						  scope_cons(ab_current_node__2,
						  ab_node_stack__2);
					  ab_current_node__2 = 
						  ab_less_than_branch_qm_;
					  goto next_loop_13;
					end_loop_12:;
				      }
				      else if (ab_node_stack__2) {
					  ab_next_node__2 = ab_node_stack__2;
					  ab_current_node__2 = 
						  M_CAR(ab_node_stack__2);
					  ab_node_stack__2 = 
						  M_CDR(ab_node_stack__2);
				      }
				      else
					  ab_current_node__2 = Nil;
				      if (ab_current_node__2) {
					  ab_next_node__2 = 
						  ISVREF(ab_current_node__2,
						  (SI_Long)2L);
					  ab_current_alist__2 = 
						  ISVREF(ab_current_node__2,
						  (SI_Long)3L);
					  ab_entry_cons__2 = 
						  M_CAR(ab_current_alist__2);
					  ab_current_alist__2 = 
						  M_CDR(ab_current_alist__2);
				      }
				  }
				  if ( !TRUEP(ab_current_node__2))
				      goto end_loop_13;
				  item = M_CDR(ab_entry_cons__2);
				  if (item) {
				      the_only_item = item;
				      goto end_5;
				  }
				  goto next_loop_12;
				end_loop_13:
				  the_only_item = Nil;
				  goto end_5;
				  the_only_item = Qnil;
				end_5:;
				POP_SPECIAL();
				gensymed_symbol = 
					lookup_global_or_kb_specific_property_value(class_1,
					Class_description_gkbprop);
				if (gensymed_symbol) {
				    sub_class_bit_vector = 
					    ISVREF(ISVREF(the_only_item,
					    (SI_Long)1L),(SI_Long)19L);
				    superior_class_bit_number = 
					    IFIX(ISVREF(gensymed_symbol,
					    (SI_Long)18L));
				    sub_class_vector_index = 
					    superior_class_bit_number >>  
					    -  - (SI_Long)3L;
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
					temp_2 = (SI_Long)0L < 
						gensymed_symbol_1;
				    }
				    else
					temp_2 = TRUEP(Nil);
				}
				else
				    temp_2 = TRUEP(Nil);
				temp_2 = temp_2 ? 
					TRUEP(serve_item_p(the_only_item)) 
					: TRUEP(Nil);
			    }
			    else
				temp_2 = TRUEP(Nil);
			    if (temp_2) {
				temp_2 = TRUEP(T);
				goto end_6;
			    }
			  next_loop_14:
			    if (ab_current_alist__1) {
				ab_entry_cons__1 = M_CAR(ab_current_alist__1);
				ab_current_alist__1 = 
					M_CDR(ab_current_alist__1);
			    }
			    else if (ab_skip_list_p__1) {
				if (ab_next_node__1) {
				    ab_current_node__1 = ab_next_node__1;
				    ab_next_node__1 = 
					    ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node__1,
					    (SI_Long)0L),(SI_Long)0L));
				    if (EQ(ab_next_node__1,ab_tail_node__1))
					ab_next_node__1 = Nil;
				    ab_entry_cons__1 = 
					    scope_cons(ISVREF(ab_current_node__1,
					    (SI_Long)2L),
					    ISVREF(ab_current_node__1,
					    (SI_Long)3L));
				}
				else
				    ab_current_node__1 = Nil;
			    }
			    else {
				if (ab_next_node__1) {
				    ab_current_node__1 = ab_next_node__1;
				    ab_less_than_branch_qm_ = Nil;
				  next_loop_15:
				    ab_less_than_branch_qm_ = 
					    ISVREF(ab_current_node__1,
					    (SI_Long)1L);
				    if ( !TRUEP(ab_less_than_branch_qm_))
					goto end_loop_14;
				    ab_node_stack__1 = 
					    scope_cons(ab_current_node__1,
					    ab_node_stack__1);
				    ab_current_node__1 = 
					    ab_less_than_branch_qm_;
				    goto next_loop_15;
				  end_loop_14:;
				}
				else if (ab_node_stack__1) {
				    ab_next_node__1 = ab_node_stack__1;
				    ab_current_node__1 = 
					    M_CAR(ab_node_stack__1);
				    ab_node_stack__1 = M_CDR(ab_node_stack__1);
				}
				else
				    ab_current_node__1 = Nil;
				if (ab_current_node__1) {
				    ab_next_node__1 = 
					    ISVREF(ab_current_node__1,
					    (SI_Long)2L);
				    ab_current_alist__1 = 
					    ISVREF(ab_current_node__1,
					    (SI_Long)3L);
				    ab_entry_cons__1 = 
					    M_CAR(ab_current_alist__1);
				    ab_current_alist__1 = 
					    M_CDR(ab_current_alist__1);
				}
			    }
			    if ( !TRUEP(ab_current_node__1))
				goto end_loop_15;
			    possible_unique_item = M_CDR(ab_entry_cons__1);
			    if (CDR(item_list))
				goto end_loop_15;
			    gensymed_symbol = 
				    lookup_global_or_kb_specific_property_value(class_1,
				    Class_description_gkbprop);
			    if (gensymed_symbol) {
				sub_class_bit_vector = 
					ISVREF(ISVREF(possible_unique_item,
					(SI_Long)1L),(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(gensymed_symbol,
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
				    temp_2 = (SI_Long)0L < gensymed_symbol_1;
				}
				else
				    temp_2 = TRUEP(Nil);
			    }
			    else
				temp_2 = TRUEP(Nil);
			    if (temp_2 ? 
				    TRUEP(serve_item_p(possible_unique_item)) 
				    : TRUEP(Nil)) {
				ab_loopvar__2 = 
					eval_cons_1(possible_unique_item,Nil);
				if (ab_loopvar__1)
				    M_CDR(ab_loopvar__1) = ab_loopvar__2;
				else
				    item_list = ab_loopvar__2;
				ab_loopvar__1 = ab_loopvar__2;
			    }
			    goto next_loop_14;
			  end_loop_15:
			    temp_1 = IFIX(length(item_list)) == 
				    (SI_Long)1L ? T : Nil;
			    reclaim_eval_list_1(item_list);
			    temp_2 = TRUEP(temp_1);
			    goto end_6;
			    temp_2 = TRUEP(Qnil);
			  end_6:;
			  POP_SPECIAL();
		      }
		      else
			  temp_2 = TRUEP(Nil);
		  }
		  else
		      temp_2 = TRUEP(Nil);
	      }
	      else
		  temp_2 = TRUEP(Nil);
	  }
	  else
	      temp_2 = TRUEP(Nil);
	  if (temp_2) {
	      ab_loopvar__1 = eval_cons_1(item_2,Nil);
	      if (ab_loopvar_)
		  M_CDR(ab_loopvar_) = ab_loopvar__1;
	      else
		  result_1 = ab_loopvar__1;
	      ab_loopvar_ = ab_loopvar__1;
	  }
	  goto next_loop_7;
	end_loop_8:
	  result = serve_all_unreprocessed_frames(result_1);
	  goto end_7;
	  result = VALUES_1(Qnil);
	end_7:;
	POP_SPECIAL();
	return result;
    }
}

/* RELATED-ROLE-PREDICATE */
Object related_role_predicate(value_to_check,quantifier,role,domain)
    Object value_to_check, quantifier, role, domain;
{
    Object relation_name, class_1, class_description, gensymed_symbol;
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, related_items, sub_class_bit_vector;
    Object scope_conses, ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_binary_tree_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, item, ab_less_than_branch_qm_;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_2;
    Declare_special(1);
    Object result;

    x_note_fn_call(149,191);
    relation_name = SECOND(role);
    class_1 = THIRD(role);
    class_description = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    gensymed_symbol = domain;
    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)12L);
    if (gensymed_symbol) {
	skip_list = CDR(gensymed_symbol);
	key_value = relation_name;
	key_hash_value = SXHASH_SYMBOL_1(relation_name) & 
		IFIX(Most_positive_fixnum);
	bottom_level = (SI_Long)0L;
	marked = Nil;
	pred = M_CAR(skip_list);
	curr = Nil;
	succ = Nil;
	level = (SI_Long)7L;
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
	related_items = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : Nil;
    }
    else
	related_items = Nil;
    if (ISVREF(class_description,(SI_Long)16L)) {
	gensymed_symbol = ISVREF(value_to_check,(SI_Long)1L);
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(class_description,
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
	    temp_2 = (SI_Long)0L < gensymed_symbol_1;
	}
	else
	    temp_2 = TRUEP(Nil);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	if (EQ(quantifier,Qthe)) {
	    if (related_items) {
		scope_conses = Scope_conses;
		ab_node_stack_ = Nil;
		ab_current_node_ = Nil;
		ab_skip_list_form_ = related_items;
		ab_binary_tree_form_ = related_items;
		gensymed_symbol = CDR(related_items);
		if (CONSP(gensymed_symbol)) {
		    temp_1 = M_CAR(gensymed_symbol);
		    temp_2 = SIMPLE_VECTOR_P(temp_1);
		}
		else
		    temp_2 = TRUEP(Nil);
		if (temp_2) {
		    temp_1 = M_CDR(gensymed_symbol);
		    ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
		}
		else
		    ab_skip_list_p_ = Nil;
		ab_next_node_ = Nil;
		ab_tail_node_ = Nil;
		ab_current_alist_ = Nil;
		ab_entry_cons_ = Nil;
		item = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			0);
		  if (ab_skip_list_p_) {
		      ab_next_node_ = 
			      ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
			      (SI_Long)0L),(SI_Long)0L));
		      ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
		      if (EQ(ab_next_node_,ab_tail_node_))
			  ab_next_node_ = Nil;
		  }
		  else
		      ab_next_node_ = M_CDR(ab_binary_tree_form_);
		next_loop_3:
		  if (ab_current_alist_) {
		      ab_entry_cons_ = M_CAR(ab_current_alist_);
		      ab_current_alist_ = M_CDR(ab_current_alist_);
		  }
		  else if (ab_skip_list_p_) {
		      if (ab_next_node_) {
			  ab_current_node_ = ab_next_node_;
			  ab_next_node_ = 
				  ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node_,
				  (SI_Long)0L),(SI_Long)0L));
			  if (EQ(ab_next_node_,ab_tail_node_))
			      ab_next_node_ = Nil;
			  ab_entry_cons_ = 
				  scope_cons(ISVREF(ab_current_node_,
				  (SI_Long)2L),ISVREF(ab_current_node_,
				  (SI_Long)3L));
		      }
		      else
			  ab_current_node_ = Nil;
		  }
		  else {
		      if (ab_next_node_) {
			  ab_current_node_ = ab_next_node_;
			  ab_less_than_branch_qm_ = Nil;
			next_loop_4:
			  ab_less_than_branch_qm_ = 
				  ISVREF(ab_current_node_,(SI_Long)1L);
			  if ( !TRUEP(ab_less_than_branch_qm_))
			      goto end_loop_3;
			  ab_node_stack_ = scope_cons(ab_current_node_,
				  ab_node_stack_);
			  ab_current_node_ = ab_less_than_branch_qm_;
			  goto next_loop_4;
			end_loop_3:;
		      }
		      else if (ab_node_stack_) {
			  ab_next_node_ = ab_node_stack_;
			  ab_current_node_ = M_CAR(ab_node_stack_);
			  ab_node_stack_ = M_CDR(ab_node_stack_);
		      }
		      else
			  ab_current_node_ = Nil;
		      if (ab_current_node_) {
			  ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
			  ab_current_alist_ = ISVREF(ab_current_node_,
				  (SI_Long)3L);
			  ab_entry_cons_ = M_CAR(ab_current_alist_);
			  ab_current_alist_ = M_CDR(ab_current_alist_);
		      }
		  }
		  if ( !TRUEP(ab_current_node_))
		      goto end_loop_4;
		  item = M_CDR(ab_entry_cons_);
		  if (item) {
		      temp_1 = item;
		      goto end_2;
		  }
		  goto next_loop_3;
		end_loop_4:
		  temp_1 = Nil;
		  goto end_2;
		  temp_1 = Qnil;
		end_2:;
		POP_SPECIAL();
		temp_2 = EQ(temp_1,value_to_check);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? only_one_related_item_p(related_items) : Nil;
	}
	else
	    temp_1 = Nil;
	if (temp_1)
	    return VALUES_1(temp_1);
	else if ( !EQ(quantifier,Qthe)) {
	    skip_list = CDR(related_items);
	    key_value = value_to_check;
	    key_hash_value = SXHASH_SYMBOL_1(value_to_check) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)7L;
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
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_3;
	    goto next_loop_6;
	  end_loop_7:
	  end_3:
	    level = level - (SI_Long)1L;
	    goto next_loop_5;
	  end_loop_5:;
	    if (IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value) {
		if (EQ(key_value,ISVREF(curr,(SI_Long)2L)))
		    return VALUES_1(ISVREF(curr,(SI_Long)3L));
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

static Object string_constant_40;  /* "first" */

/* ROLE-PRINT-FIRST-OF-LIST */
Object role_print_first_of_list(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,192);
    GENSYM_RETURN_ONE(print_ordinal_list_role(string_constant_40,role,
	    local_variable_qm));
    return VALUES_1(Nil);
}

static Object string_constant_41;  /* " ~(~a~)" */

static Object array_constant_7;    /* # */

/* PRINT-ORDINAL-LIST-ROLE */
Object print_ordinal_list_role(ordinal_name,role,local_variable_qm)
    Object ordinal_name, role, local_variable_qm;
{
    x_note_fn_call(149,193);
    twrite_general_string(ordinal_name);
    twrite_character(FIX((SI_Long)32L));
    print_user_or_datum_type(SECOND(role));
    if (local_variable_qm)
	tformat(2,string_constant_41,local_variable_qm);
    twrite_beginning_of_wide_string(array_constant_7,FIX((SI_Long)3L));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-FIRST-OF-LIST */
Object serve_first_first_of_list(role,domain)
    Object role, domain;
{
    x_note_fn_call(149,194);
    return serve_element_of_list(role,domain);
}

/* SERVE-FIRST-FIRST-OF-LIST-INVERSE */
Object serve_first_first_of_list_inverse(item,quantifier,role,
	    domain_designation)
    Object item, quantifier, role, domain_designation;
{
    x_note_fn_call(149,195);
    return serve_element_of_list_inverse(item,quantifier,role,
	    domain_designation);
}

static Object string_constant_42;  /* "second" */

/* ROLE-PRINT-SECOND-OF-LIST */
Object role_print_second_of_list(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,196);
    GENSYM_RETURN_ONE(print_ordinal_list_role(string_constant_42,role,
	    local_variable_qm));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-SECOND-OF-LIST */
Object serve_first_second_of_list(role,domain)
    Object role, domain;
{
    x_note_fn_call(149,197);
    return serve_element_of_list(role,domain);
}

/* SERVE-FIRST-SECOND-OF-LIST-INVERSE */
Object serve_first_second_of_list_inverse(item,quantifier,role,
	    domain_designation)
    Object item, quantifier, role, domain_designation;
{
    x_note_fn_call(149,198);
    return serve_element_of_list_inverse(item,quantifier,role,
	    domain_designation);
}

static Object string_constant_43;  /* "next to last" */

/* ROLE-PRINT-NEXT-TO-LAST-OF-LIST */
Object role_print_next_to_last_of_list(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,199);
    GENSYM_RETURN_ONE(print_ordinal_list_role(string_constant_43,role,
	    local_variable_qm));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-NEXT-TO-LAST-OF-LIST */
Object serve_first_next_to_last_of_list(role,domain)
    Object role, domain;
{
    x_note_fn_call(149,200);
    return serve_element_of_list(role,domain);
}

/* SERVE-FIRST-NEXT-TO-LAST-OF-LIST-INVERSE */
Object serve_first_next_to_last_of_list_inverse(item,quantifier,role,
	    domain_designation)
    Object item, quantifier, role, domain_designation;
{
    x_note_fn_call(149,201);
    return serve_element_of_list_inverse(item,quantifier,role,
	    domain_designation);
}

static Object string_constant_44;  /* "last" */

/* ROLE-PRINT-LAST-OF-LIST */
Object role_print_last_of_list(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,202);
    GENSYM_RETURN_ONE(print_ordinal_list_role(string_constant_44,role,
	    local_variable_qm));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-LAST-OF-LIST */
Object serve_first_last_of_list(role,domain)
    Object role, domain;
{
    x_note_fn_call(149,203);
    return serve_element_of_list(role,domain);
}

/* SERVE-FIRST-LAST-OF-LIST-INVERSE */
Object serve_first_last_of_list_inverse(item,quantifier,role,
	    domain_designation)
    Object item, quantifier, role, domain_designation;
{
    x_note_fn_call(149,204);
    return serve_element_of_list_inverse(item,quantifier,role,
	    domain_designation);
}

static Object Qfirst_of_list;      /* first-of-list */

static Object Qsecond_of_list;     /* second-of-list */

static Object Qnext_to_last_of_list;  /* next-to-last-of-list */

static Object Qlast_of_list;       /* last-of-list */

static Object string_constant_45;  /* "The element type ~NT is incorrect for the g2-list ~NF ~
				    *               which is missing a type."
				    */

static Object string_constant_46;  /* "The element type ~NT is incorrect for the g2-list ~NF ~
				    *               which is of type ~NT."
				    */

/* SERVE-ELEMENT-OF-LIST */
Object serve_element_of_list(role,g2_list_or_sequence_qm)
    Object role, g2_list_or_sequence_qm;
{
    Object temp, element_position, desired_list_type_qm, list_type_qm;
    Object class_type_spec, type_spec_qm, gensymed_symbol, held_vector, value;
    Object elt_1, validated_elt, result_1, sub_class_bit_vector, element_qm;
    SI_Long next_index, length_1, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_3;
    char temp_1;

    x_note_fn_call(149,205);
    temp = FIRST(role);
    if (CONSP(temp)) {
	temp = FIRST(role);
	element_position = FIRST(temp);
    }
    else
	element_position = FIRST(role);
    temp = FIRST(role);
    if (CONSP(temp)) {
	temp = FIRST(role);
	desired_list_type_qm = SECOND(temp);
    }
    else
	desired_list_type_qm = SECOND(role);
    list_type_qm = Nil;
    if (CONSP(g2_list_or_sequence_qm) && EQ(M_CDR(g2_list_or_sequence_qm),
	    Qsequence)) {
	class_type_spec = Nil;
	if (desired_list_type_qm) {
	    type_spec_qm = 
		    type_specification_for_user_or_datum_type(desired_list_type_qm);
	    if (type_spec_qm);
	    else {
		class_type_spec = eval_list_2(Qab_class,Nil);
		M_SECOND(class_type_spec) = desired_list_type_qm;
		type_spec_qm = class_type_spec;
	    }
	}
	else
	    type_spec_qm = Nil;
	if (EQ(element_position,Qfirst_of_list) || EQ(element_position,
		Qsecond_of_list)) {
	    gensymed_symbol = g2_list_or_sequence_qm;
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_1 = (SI_Long)0L;
	    value = Nil;
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
	    validated_elt = elt_1 ? 
		    validate_item_or_evaluation_value(elt_1,Nil,Nil) : Nil;
	    next_index = next_index + (SI_Long)1L;
	    value = validated_elt;
	    if ( !TRUEP(type_spec_qm) || type_specification_type_p(value,
		    type_spec_qm)) {
		if (EQ(element_position,Qfirst_of_list)) {
		    result_1 = value;
		    goto end_1;
		}
		else
		    element_position = Qfirst_of_list;
	    }
	    goto next_loop;
	  end_loop:
	    result_1 = Qnil;
	  end_1:;
	}
	else if (EQ(element_position,Qnext_to_last_of_list))
	    result_1 = 
		    search_for_sequence_element_from_back(g2_list_or_sequence_qm,
		    type_spec_qm,FIX((SI_Long)1L));
	else if (EQ(element_position,Qlast_of_list))
	    result_1 = 
		    search_for_sequence_element_from_back(g2_list_or_sequence_qm,
		    type_spec_qm,FIX((SI_Long)0L));
	else
	    result_1 = Qnil;
	reclaim_eval_list_1(class_type_spec);
	if (result_1) {
	    temp = FIXNUMP(result_1) || result_1 && SYMBOLP(result_1) || 
		    SIMPLE_VECTOR_P(result_1) ? result_1 : 
		    copy_if_evaluation_value_1(result_1);
	    return VALUES_3(temp,Nil,Qnever);
	}
	else
	    return VALUES_3(Nil,Nil,Nil);
    }
    else {
	sub_class_bit_vector = ISVREF(ISVREF(g2_list_or_sequence_qm,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(G2_list_class_description,
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
	    temp_1 = (SI_Long)0L < gensymed_symbol_1;
	}
	else
	    temp_1 = TRUEP(Nil);
	if ( !temp_1)
	    return VALUES_3(Nil,Nil,Nil);
	else {
	    list_type_qm = ISVREF(g2_list_or_sequence_qm,(SI_Long)21L);
	    if ( !TRUEP(list_type_qm)) {
		if ((SI_Long)1L <= IFIX(Warning_message_level))
		    give_warning_1(4,FIX((SI_Long)1L),string_constant_45,
			    desired_list_type_qm,g2_list_or_sequence_qm);
		return VALUES_3(Nil,Nil,Nil);
	    }
	    else if ( 
		    !TRUEP(g2_list_or_array_type_ok_p(desired_list_type_qm,
		    list_type_qm,T))) {
		if ((SI_Long)1L <= IFIX(Warning_message_level))
		    give_warning_1(5,FIX((SI_Long)1L),string_constant_46,
			    desired_list_type_qm,g2_list_or_sequence_qm,
			    list_type_qm);
		return VALUES_3(Nil,Nil,Nil);
	    }
	    else {
		if (g2_list_or_array_datum_subtype_p(list_type_qm,
			desired_list_type_qm))
		    desired_list_type_qm = Nil;
		if (EQ(element_position,Qfirst_of_list))
		    element_qm = g2_list_first(g2_list_or_sequence_qm,
			    desired_list_type_qm,Nil);
		else if (EQ(element_position,Qsecond_of_list))
		    element_qm = g2_list_second(g2_list_or_sequence_qm,
			    desired_list_type_qm,Nil);
		else if (EQ(element_position,Qnext_to_last_of_list))
		    element_qm = 
			    g2_list_next_to_last(g2_list_or_sequence_qm,
			    desired_list_type_qm,Nil);
		else if (EQ(element_position,Qlast_of_list))
		    element_qm = g2_list_last(g2_list_or_sequence_qm,
			    desired_list_type_qm,Nil);
		else
		    element_qm = Qnil;
		if ( !TRUEP(element_qm))
		    return VALUES_3(Nil,Nil,Nil);
		else
		    return VALUES_3(element_qm,Nil,Qnever);
	    }
	}
    }
}

/* SERVE-ELEMENT-OF-LIST-INVERSE */
Object serve_element_of_list_inverse(item,quantifier,role,domain_designation)
    Object item, quantifier, role, domain_designation;
{
    Object temp, element_position, desired_list_type, x2;
    Object g2_list_element_structure, ab_loop_list_, g2_list, g2_list_type;
    Object check_domain_role_and_type_qm, element_qm, result_1, ab_loopvar_;
    Object ab_loopvar__1;
    char temp_1;

    x_note_fn_call(149,206);
    temp = FIRST(role);
    if (CONSP(temp)) {
	temp = FIRST(role);
	element_position = FIRST(temp);
    }
    else
	element_position = FIRST(role);
    temp = FIRST(role);
    if (CONSP(temp)) {
	temp = FIRST(role);
	desired_list_type = SECOND(temp);
    }
    else
	desired_list_type = SECOND(role);
    if (SIMPLE_VECTOR_P(item) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(item,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(item,(SI_Long)1L);
	temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp_1 = TRUEP(Nil);
    if ( !temp_1)
	return VALUES_3(Nil,Nil,Nil);
    else {
	g2_list_element_structure = Nil;
	ab_loop_list_ = ISVREF(item,(SI_Long)13L);
	g2_list = Nil;
	g2_list_type = Nil;
	check_domain_role_and_type_qm = Nil;
	element_qm = Nil;
	result_1 = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	g2_list_element_structure = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	g2_list = ISVREF(g2_list_element_structure,(SI_Long)5L);
	g2_list_type = ISVREF(g2_list,(SI_Long)21L);
	check_domain_role_and_type_qm = 
		designation_could_denote_item_p(domain_designation,
		g2_list) && ( !EQ(quantifier,Qthe) || 
		unique_value_of_role_p(item,role,g2_list)) ? 
		g2_list_or_array_type_ok_p(desired_list_type,g2_list_type,
		T) : Qnil;
	if (check_domain_role_and_type_qm) {
	    if (EQ(element_position,Qfirst_of_list))
		element_qm = g2_list_first(g2_list,desired_list_type,Nil);
	    else if (EQ(element_position,Qsecond_of_list))
		element_qm = g2_list_second(g2_list,desired_list_type,Nil);
	    else if (EQ(element_position,Qnext_to_last_of_list))
		element_qm = g2_list_next_to_last(g2_list,
			desired_list_type,Nil);
	    else if (EQ(element_position,Qlast_of_list))
		element_qm = g2_list_last(g2_list,desired_list_type,Nil);
	    else
		element_qm = Qnil;
	}
	else
	    element_qm = Nil;
	if (element_qm && EQ(item,element_qm) &&  
		!TRUEP(memq_function(g2_list,result_1))) {
	    ab_loopvar__1 = eval_cons_1(g2_list,Nil);
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		result_1 = ab_loopvar__1;
	    ab_loopvar_ = ab_loopvar__1;
	}
	if (element_qm) {
	    if ( !(FIXNUMP(element_qm) || SYMBOLP(element_qm) || 
		    SIMPLE_VECTOR_P(element_qm)))
		reclaim_if_evaluation_value_1(element_qm);
	}
	goto next_loop;
      end_loop:
	return serve_all_unreprocessed_frames(result_1);
	return VALUES_1(Qnil);
    }
}

static Object string_constant_47;  /* "nth element of g2-array, g2-list, or sequence" */

/* ROLE-PRINT-NTH-ELEMENT */
Object role_print_nth_element(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,207);
    GENSYM_RETURN_ONE(tformat(1,string_constant_47));
    return VALUES_1(Nil);
}

/* ROLE-AND-DESIGNATION-PRINT-NTH-ELEMENT */
Object role_and_designation_print_nth_element varargs_1(int, n)
{
    Object role;
    Object domain_1_qm, domain_2_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(149,208);
    INIT_ARGS_nonrelocating();
    role = REQUIRED_ARG_nonrelocating();
    domain_1_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    domain_2_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (CONSP(domain_1_qm)) {
	twrite_wide_character(FIX((SI_Long)40L));
	print_designation(domain_1_qm);
	twrite_wide_character(FIX((SI_Long)41L));
    }
    else
	print_designation(domain_1_qm);
    twrite_wide_character(FIX((SI_Long)91L));
    write_expression(domain_2_qm);
    return twrite_wide_character(FIX((SI_Long)93L));
}

/* SERVE-FIRST-NTH-ELEMENT */
Object serve_first_nth_element(role,item_or_value,index_1)
    Object role, item_or_value, index_1;
{
    Object index_value, fetched_item_or_evaluation_value_qm;

    x_note_fn_call(149,209);
    index_value = index_1;
    fetched_item_or_evaluation_value_qm = fetch_nth_element(item_or_value,
	    index_value,Nil,Nil);
    if ( !TRUEP(fetched_item_or_evaluation_value_qm))
	return VALUES_3(Nil,Nil,Nil);
    else
	return VALUES_3(fetched_item_or_evaluation_value_qm,Nil,Qnever);
}

/* BAD-G2-ARRAY-INDEX-WARNING */
Object bad_g2_array_index_warning(g2_array,bad_index)
    Object g2_array, bad_index;
{
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_stack_pointer;
    Declare_special(7);
    Object result;

    x_note_fn_call(149,210);
    SAVE_STACK();
    if ((SI_Long)1L <= IFIX(Warning_message_level) &&  
		!TRUEP(Debugging_reset)) {
	if ( !TRUEP(Defer_notifications_qm))
	    break_out_of_debug_messages();
	snapshots_of_related_blocks = Nil;
	note_blocks_in_tformat = SYMBOL_FUNCTION(Qrecord_block_for_tformat);
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
		      write_warning_message_header(FIX((SI_Long)1L));
		      write_bad_g2_array_index_message(g2_array,bad_index);
		      temp = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    SAVE_VALUES(notify_user_1(temp));
	    if (Snapshots_of_related_blocks) {
		reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
		Snapshots_of_related_blocks = Nil;
	    }
	    result = RESTORE_VALUES();
	  POP_SPECIAL();
	POP_SPECIAL();
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

/* BAD-G2-ARRAY-INDEX-ERROR-1 */
Object bad_g2_array_index_error_1(g2_array,bad_index)
    Object g2_array, bad_index;
{
    Object text_string, snapshots, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(7);

    x_note_fn_call(149,211);
    text_string = Nil;
    snapshots = Nil;
    snapshots_of_related_blocks = Nil;
    note_blocks_in_tformat = SYMBOL_FUNCTION(Qrecord_block_for_tformat);
    PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
	    6);
      PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
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
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			0);
		  write_bad_g2_array_index_message(g2_array,bad_index);
		  text_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	snapshots = Snapshots_of_related_blocks;
	Snapshots_of_related_blocks = Nil;
	if (Snapshots_of_related_blocks) {
	    reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
	    Snapshots_of_related_blocks = Nil;
	}
      POP_SPECIAL();
    POP_SPECIAL();
    return make_error_text(text_string,snapshots);
}

static Object string_constant_48;  /* "The array index ~a is not correct for ~NF.  This array is of length 0." */

static Object string_constant_49;  /* "The array index ~a is not in the range 0 to ~a for ~NF." */

/* WRITE-BAD-G2-ARRAY-INDEX-MESSAGE */
Object write_bad_g2_array_index_message(g2_array,bad_index)
    Object g2_array, bad_index;
{
    Object length_1, end_index;

    x_note_fn_call(149,212);
    length_1 = ISVREF(g2_array,(SI_Long)20L);
    end_index = FIXNUM_SUB1(length_1);
    if (IFIX(length_1) == (SI_Long)0L)
	return tformat(3,string_constant_48,bad_index,g2_array);
    else
	return tformat(4,string_constant_49,bad_index,end_index,g2_array);
}

static Object string_constant_50;  /* "A deleted item was found at index ~a within ~NE." */

static Object string_constant_51;  /* "No item-or-value exists at index ~a within ~NE." */

static Object string_constant_52;  /* "The index ~a is not correct for ~NE. This sequence is of length 0." */

static Object string_constant_53;  /* "The index ~a into the sequence ~NE was out of the ~
				    *                        bounds 0 through ~a."
				    */

static Object string_constant_54;  /* "The index ~a into the text ~NE was out of the bounds 0 ~
				    *                    through ~a."
				    */

static Object string_constant_55;  /* "Cannot reference element ~a of ~NF.  It is neither a g2-list, ~
				    *               g2-array, sequence, or text."
				    */

static Object string_constant_56;  /* "The g2-array ~NF contains no element at index ~a." */

static Object string_constant_57;  /* "A reference to element ~a of ~NF failed because the item at ~
				    *              that location, ~NF, was disabled or inactive."
				    */

static Object string_constant_58;  /* "Cannot access element ~a of ~NF.  This g2-list contains no ~
				    *                elements."
				    */

static Object string_constant_59;  /* "Cannot reference an element at index ~a in the ~
				    *                g2-list ~NF.  The index must be in the range from 0 ~
				    *                to below the number of list elements, which is ~a."
				    */

static Object string_constant_60;  /* "Unable to reference element ~a of ~NF." */

static Object string_constant_61;  /* "Cannot reference element ~a of ~NF.  It is neither a g2-list ~
				    *           nor a g2-array."
				    */

static Object string_constant_62;  /* "Cannot reference element ~a of ~NF.  It is neither a g2-list ~
				    *           nor g2-array."
				    */

/* FETCH-NTH-ELEMENT */
Object fetch_nth_element(item_or_value,index_value,top_of_stack,
	    signal_errors_qm)
    Object item_or_value, index_value, top_of_stack, signal_errors_qm;
{
    Object element_qm, sequence_element_qm, temp, gensymed_symbol;
    Object gensymed_symbol_1, top_of_stack_1, message_1, wide_string, x2;
    Object sub_class_bit_vector, length_2, managed_float_array;
    Object amf_available_array_cons_qm, amf_array, temp_2, temp_3, amf_result;
    Object new_float;
    SI_Long arg, arg_1, arg_2, length_1, gensymed_symbol_2;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4;
    char temp_1;
    double aref_new_value;

    x_note_fn_call(149,213);
    element_qm = Nil;
    if (CONSP(item_or_value) && EQ(M_CDR(item_or_value),Qsequence)) {
	sequence_element_qm = evaluation_sequence_aref(item_or_value,
		index_value);
	if (sequence_element_qm)
	    temp = FIXNUMP(sequence_element_qm) || sequence_element_qm && 
		    SYMBOLP(sequence_element_qm) || 
		    SIMPLE_VECTOR_P(sequence_element_qm) ? 
		    sequence_element_qm : 
		    copy_if_evaluation_value_1(sequence_element_qm);
	else if (signal_errors_qm) {
	    arg = (SI_Long)-1L;
	    arg_1 = IFIX(index_value);
	    arg_2 = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(item_or_value),
		    (SI_Long)1L)));
	    if (arg < arg_1 && arg_1 < arg_2) {
		gensymed_symbol = M_CAR(item_or_value);
		gensymed_symbol_1 = FIXNUM_ADD1(index_value);
		if (FIXNUM_LE(ISVREF(M_CAR(item_or_value),(SI_Long)1L),
			Maximum_in_place_array_size) ? 
			TRUEP(ISVREF(M_CAR(item_or_value),
			IFIX(FIXNUM_ADD(gensymed_symbol_1,
			Managed_array_index_offset)))) : 
			TRUEP(ISVREF(ISVREF(gensymed_symbol,
			(IFIX(gensymed_symbol_1) >>  -  - (SI_Long)10L) + 
			(SI_Long)2L),IFIX(gensymed_symbol_1) & 
			(SI_Long)1023L))) {
		    top_of_stack_1 = top_of_stack;
		    message_1 = tformat_stack_error_text_string(3,
			    string_constant_50,index_value,item_or_value);
		    temp = raw_stack_error_named_error(top_of_stack_1,
			    message_1);
		}
		else {
		    top_of_stack_1 = top_of_stack;
		    message_1 = tformat_stack_error_text_string(3,
			    string_constant_51,index_value,item_or_value);
		    temp = raw_stack_error_named_error(top_of_stack_1,
			    message_1);
		}
	    }
	    else if ((SI_Long)0L == 
		    IFIX(FIXNUM_SUB1(ISVREF(M_CAR(item_or_value),
		    (SI_Long)1L)))) {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_52,index_value,item_or_value);
		temp = raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	    else {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(4,
			string_constant_53,index_value,item_or_value,
			FIX(IFIX(FIXNUM_SUB1(ISVREF(M_CAR(item_or_value),
			(SI_Long)1L))) - (SI_Long)1L));
		temp = raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	}
	else
	    temp = Nil;
    }
    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(item_or_value) != (SI_Long)0L) {
	wide_string = item_or_value;
	arg = (SI_Long)0L;
	arg_1 = IFIX(index_value);
	length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string));
	gensymed_symbol_2 = UBYTE_16_ISAREF_1(wide_string,length_1 - 
		(SI_Long)2L) + ((UBYTE_16_ISAREF_1(wide_string,length_1 - 
		(SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
	arg_2 = gensymed_symbol_2 - (SI_Long)1L;
	if (arg <= arg_1 && arg_1 <= arg_2)
	    temp = FIX(UBYTE_16_ISAREF_1(wide_string,IFIX(index_value)));
	else if (signal_errors_qm) {
	    top_of_stack_1 = top_of_stack;
	    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value));
	    gensymed_symbol_2 = UBYTE_16_ISAREF_1(item_or_value,length_1 - 
		    (SI_Long)2L) + ((UBYTE_16_ISAREF_1(item_or_value,
		    length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
	    message_1 = tformat_stack_error_text_string(4,
		    string_constant_54,index_value,item_or_value,
		    FIX(gensymed_symbol_2 - (SI_Long)1L));
	    temp = raw_stack_error_named_error(top_of_stack_1,message_1);
	}
	else
	    temp = Nil;
    }
    else {
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if ( !temp_1) {
	    if (signal_errors_qm) {
		top_of_stack_1 = top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_55,index_value,item_or_value);
		temp = raw_stack_error_named_error(top_of_stack_1,message_1);
	    }
	    else
		temp = Nil;
	}
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(item_or_value,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(G2_array_class_description,(SI_Long)18L));
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
		temp_1 = (SI_Long)0L < gensymed_symbol_2;
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		length_2 = ISVREF(item_or_value,(SI_Long)20L);
		if ( !(FIXNUMP(index_value) && IFIX(index_value) >= 
			(SI_Long)0L && FIXNUM_LT(index_value,length_2))) {
		    if (signal_errors_qm)
			raw_stack_error_named_error(top_of_stack,
				bad_g2_array_index_error_1(item_or_value,
				index_value));
		    temp = Nil;
		}
		else if (EQ(ISVREF(item_or_value,(SI_Long)21L),Qfloat)) {
		    managed_float_array = ACCESS_ONCE(ISVREF(item_or_value,
			    (SI_Long)23L));
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_3 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
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
		    aref_new_value = 
			    DFLOAT_ISAREF_1(ISVREF(managed_float_array,
			    (IFIX(index_value) >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),IFIX(index_value) & (SI_Long)1023L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		    temp = new_float;
		}
		else {
		    element_qm = 
			    g2_array_aref_item_or_evaluation_value(item_or_value,
			    index_value);
		    if ( !TRUEP(element_qm)) {
			if (signal_errors_qm) {
			    top_of_stack_1 = top_of_stack;
			    message_1 = tformat_stack_error_text_string(3,
				    string_constant_56,item_or_value,
				    index_value);
			    raw_stack_error_named_error(top_of_stack_1,
				    message_1);
			}
			temp = Nil;
		    }
		    else {
			if (SIMPLE_VECTOR_P(element_qm) && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element_qm)) 
				> (SI_Long)2L &&  !EQ(ISVREF(element_qm,
				(SI_Long)1L),Qavailable_frame_vector)) {
			    x2 = ISVREF(element_qm,(SI_Long)1L);
			    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				    (SI_Long)0L),
				    Qg2_defstruct_structure_name_class_description_g2_struct) 
				    ? TRUEP(x2) : TRUEP(Qnil);
			}
			else
			    temp_1 = TRUEP(Nil);
			temp_1 =  !temp_1;
			if (temp_1);
			else
			    temp_1 = TRUEP(serve_item_p(element_qm));
			if (temp_1)
			    temp = element_qm;
			else if (signal_errors_qm) {
			    top_of_stack_1 = top_of_stack;
			    message_1 = tformat_stack_error_text_string(4,
				    string_constant_57,index_value,
				    item_or_value,element_qm);
			    temp = 
				    raw_stack_error_named_error(top_of_stack_1,
				    message_1);
			}
			else
			    temp = Nil;
		    }
		}
	    }
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(item_or_value,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(G2_list_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol_2;
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1) {
		    if (g2_list_empty_p(item_or_value)) {
			if (signal_errors_qm) {
			    top_of_stack_1 = top_of_stack;
			    message_1 = tformat_stack_error_text_string(3,
				    string_constant_58,index_value,
				    item_or_value);
			    raw_stack_error_named_error(top_of_stack_1,
				    message_1);
			}
			temp = Nil;
		    }
		    else {
			element_qm = 
				nth_g2_list_item_or_evaluation_value(index_value,
				item_or_value,T);
			if ( !TRUEP(element_qm)) {
			    if (signal_errors_qm) {
				top_of_stack_1 = top_of_stack;
				message_1 = 
					tformat_stack_error_text_string(4,
					string_constant_59,index_value,
					item_or_value,
					g2_list_length(item_or_value));
				raw_stack_error_named_error(top_of_stack_1,
					message_1);
			    }
			    temp = Nil;
			}
			else {
			    if (SIMPLE_VECTOR_P(element_qm) && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element_qm)) 
				    > (SI_Long)2L &&  
				    !EQ(ISVREF(element_qm,(SI_Long)1L),
				    Qavailable_frame_vector)) {
				x2 = ISVREF(element_qm,(SI_Long)1L);
				temp_1 = SIMPLE_VECTOR_P(x2) && 
					EQ(ISVREF(x2,(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					? TRUEP(x2) : TRUEP(Qnil);
			    }
			    else
				temp_1 = TRUEP(Nil);
			    temp_1 =  !temp_1;
			    if (temp_1);
			    else
				temp_1 = TRUEP(serve_item_p(element_qm));
			    if (temp_1)
				temp = element_qm;
			    else if (signal_errors_qm) {
				top_of_stack_1 = top_of_stack;
				message_1 = 
					tformat_stack_error_text_string(3,
					string_constant_60,index_value,
					item_or_value);
				temp = 
					raw_stack_error_named_error(top_of_stack_1,
					message_1);
			    }
			    else
				temp = Nil;
			}
		    }
		}
		else if (signal_errors_qm) {
		    top_of_stack_1 = top_of_stack;
		    message_1 = tformat_stack_error_text_string(3,
			    string_constant_61,index_value,item_or_value);
		    temp = raw_stack_error_named_error(top_of_stack_1,
			    message_1);
		}
		else {
		    if ((SI_Long)1L <= IFIX(Warning_message_level))
			give_warning_1(4,FIX((SI_Long)1L),
				string_constant_62,index_value,item_or_value);
		    temp = Nil;
		}
	    }
	}
    }
    return VALUES_1(temp);
}

/* ROLE-PRINT-ELEMENT-ITERATOR */
Object role_print_element_iterator(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,214);
    print_user_or_datum_type(SECOND(role));
    if (local_variable_qm)
	tformat(2,string_constant_41,local_variable_qm);
    GENSYM_RETURN_ONE(twrite_beginning_of_wide_string(array_constant_7,
	    FIX((SI_Long)3L)));
    return VALUES_1(Nil);
}

static Object string_constant_63;  /* "~NT is an element-type that is not correct for ~NF.  ~
				    *                   ~NF is a g2-list that has an element-type of ~NT."
				    */

static Object string_constant_64;  /* "~a is not a correct element-type for the g2-list ~NF. ~
				    *                   ~a is not a defined class or type."
				    */

static Object Qserve_remaining_list_elements;  /* serve-remaining-list-elements */

static Object Qquantity;           /* quantity */

static Object string_constant_65;  /* "The element type ~a is not valid for the g2-array ~a." */

static Object string_constant_66;  /* "~a is not a correct element-type for the g2-array ~NF. ~
				    *                   ~a is not a defined class or type."
				    */

static Object Qserve_remaining_g2_array_elements;  /* serve-remaining-g2-array-elements */

static Object string_constant_67;  /* "Cannot iterate over the elements in ~NF.  It is not a g2-list, ~
				    *           g2-array, or sequence."
				    */

/* SERVE-FIRST-ELEMENT-ITERATOR */
Object serve_first_element_iterator(role,domain)
    Object role, domain;
{
    Object desired_element_type, element_type, sub_class_bit_vector, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp_1, temp_2;
    Object entry_hash, gensymed_symbol_3, tail, head, new_cons, temp_3;
    Object svref_arg_2, svref_new_value, gensymed_symbol_4, gensymed_symbol_5;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, g2_list_structure_qm, structure_head, next_element;
    Object skip_element_test_qm, item_or_value_to_serve, x2, continuation;
    Object possible_item_element_p_qm, array_length;
    Object item_or_evaluation_value_element_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, key_hash_value, bottom_level;
    SI_Long level, ab_loop_bind_;
    char temp;
    Object result;

    x_note_fn_call(149,215);
    desired_element_type = SECOND(role);
    element_type = Nil;
    if (CONSP(domain) && EQ(M_CDR(domain),Qsequence))
	return serve_evaluation_sequence_values(domain,desired_element_type);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(domain,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(G2_list_class_description,
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
	    element_type = ISVREF(domain,(SI_Long)21L);
	    if ( !TRUEP(g2_list_or_array_type_ok_p(desired_element_type,
		    element_type,T))) {
		if (SYMBOLP(desired_element_type)) {
		    skip_list = CDR(Symbol_properties_table);
		    key_value = desired_element_type;
		    key_hash_value = SXHASH_SYMBOL_1(desired_element_type) 
			    & IFIX(Most_positive_fixnum);
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
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_1:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_2:
		    if ( !TRUEP(marked))
			goto end_loop_1;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		    goto next_loop_2;
		  end_loop_1:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
		    gensymed_symbol_3 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if ( !TRUEP(gensymed_symbol_3)) {
			gensymed_symbol_3 = desired_element_type;
			temp_1 = Symbol_properties_table;
			temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol_3) & 
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
			    temp_3 = Available_lookup_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(temp_3,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index)))) {
				temp_3 = Available_lookup_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_3,svref_arg_2) = Nil;
			    }
			    gensymed_symbol_4 = new_cons;
			}
			else
			    gensymed_symbol_4 = Nil;
			if ( !TRUEP(gensymed_symbol_4))
			    gensymed_symbol_4 = replenish_lookup_cons_pool();
			M_CAR(gensymed_symbol_4) = 
				Qsymbol_properties_hash_table;
			new_cons = ISVREF(Available_lookup_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    temp_3 = Available_lookup_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(temp_3,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index)))) {
				temp_3 = Available_lookup_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_3,svref_arg_2) = Nil;
			    }
			    gensymed_symbol_5 = new_cons;
			}
			else
			    gensymed_symbol_5 = Nil;
			if ( !TRUEP(gensymed_symbol_5))
			    gensymed_symbol_5 = replenish_lookup_cons_pool();
			M_CAR(gensymed_symbol_5) = head;
			M_CDR(gensymed_symbol_5) = tail;
			inline_note_allocate_cons(gensymed_symbol_5,Qlookup);
			M_CDR(gensymed_symbol_4) = gensymed_symbol_5;
			inline_note_allocate_cons(gensymed_symbol_4,Qlookup);
			gensymed_symbol_3 = set_skip_list_entry(temp_1,
				FIX((SI_Long)31L),Qeq,Nil,T,
				gensymed_symbol_3,temp_2,gensymed_symbol_4);
		    }
		    global_properties = gensymed_symbol_3;
		    skip_list = CDR(global_properties);
		    key_value = 
			    Current_kb_specific_property_list_property_name;
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
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_4:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_5:
		    if ( !TRUEP(marked))
			goto end_loop_4;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		    goto next_loop_5;
		  end_loop_4:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
		    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (kb_properties);
		    else
			kb_properties = Nil;
		    if (kb_properties) {
			skip_list = CDR(kb_properties);
			key_value = Class_description_gkbprop;
			key_hash_value = 
				SXHASH_SYMBOL_1(Class_description_gkbprop) 
				& IFIX(Most_positive_fixnum);
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
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_7:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
		      next_loop_8:
			if ( !TRUEP(marked))
			    goto end_loop_7;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
			goto next_loop_8;
		      end_loop_7:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
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
				SXHASH_SYMBOL_1(Class_description_gkbprop) 
				& IFIX(Most_positive_fixnum);
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
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_10:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
		      next_loop_11:
			if ( !TRUEP(marked))
			    goto end_loop_10;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
			goto next_loop_11;
		      end_loop_10:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
			if (resulting_value);
			else
			    resulting_value = Nil;
		    }
		    temp = TRUEP(resulting_value);
		}
		else
		    temp = TRUEP(Nil);
		if (temp);
		else
		    temp = 
			    TRUEP(valid_type_specification_p(desired_element_type));
		if (temp) {
		    if ((SI_Long)1L <= IFIX(Warning_message_level))
			give_warning_1(6,FIX((SI_Long)1L),
				string_constant_63,desired_element_type,
				domain,domain,element_type);
		}
		else if ((SI_Long)1L <= IFIX(Warning_message_level))
		    give_warning_1(5,FIX((SI_Long)1L),string_constant_64,
			    desired_element_type,domain,desired_element_type);
		return VALUES_3(Nil,Nil,Nil);
	    }
	    else if (g2_list_empty_p(domain))
		return VALUES_3(Nil,Nil,Nil);
	    else {
		g2_list_structure_qm = ISVREF(domain,(SI_Long)20L);
		structure_head = 
			g2_list_structure_next(ISVREF(g2_list_structure_qm,
			(SI_Long)2L),g2_list_structure_qm);
		next_element = g2_list_structure_next(structure_head,
			g2_list_structure_qm);
		skip_element_test_qm = 
			g2_list_or_array_type_ok_p(desired_element_type,
			element_type,Nil);
		if ( !TRUEP(next_element)) {
		    item_or_value_to_serve = ISVREF(structure_head,
			    (SI_Long)4L);
		    if (SIMPLE_VECTOR_P(item_or_value_to_serve) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value_to_serve)) 
			    > (SI_Long)2L &&  
			    !EQ(ISVREF(item_or_value_to_serve,(SI_Long)1L),
			    Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value_to_serve,(SI_Long)1L);
			temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp) {
			if ((skip_element_test_qm || 
				item_ok_for_g2_list_or_array_p(item_or_value_to_serve,
				desired_element_type)) && 
				serve_item_p(item_or_value_to_serve))
			    return VALUES_3(item_or_value_to_serve,Nil,Qnever);
			else
			    return VALUES_3(Nil,Nil,Nil);
		    }
		    else if (item_or_value_to_serve && 
			    (skip_element_test_qm || 
			    datum_ok_for_g2_list_or_array_p(item_or_value_to_serve,
			    desired_element_type))) {
			temp_2 = FIXNUMP(item_or_value_to_serve) || 
				item_or_value_to_serve && 
				SYMBOLP(item_or_value_to_serve) ? 
				item_or_value_to_serve : 
				copy_evaluation_value_1(item_or_value_to_serve);
			return VALUES_3(temp_2,Nil,Qnever);
		    }
		    else
			return VALUES_3(Nil,Nil,Nil);
		}
		else {
		    continuation = 
			    eval_cons_1(SYMBOL_FUNCTION(Qserve_remaining_list_elements),
			    eval_cons_1(structure_head,
			    skip_element_test_qm ? Nil : 
			    desired_element_type));
		    temp_3 = eval_cons_1(continuation,ISVREF(domain,
			    (SI_Long)23L));
		    ISVREF(domain,(SI_Long)23L) = temp_3;
		    return serve_remaining_list_elements(T,continuation);
		}
	    }
	}
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(domain,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(G2_array_class_description,(SI_Long)18L));
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
		element_type = EQ(ISVREF(domain,(SI_Long)21L),Qquantity) ? 
			Qnumber : ISVREF(domain,(SI_Long)21L);
		if ( 
			!TRUEP(g2_list_or_array_type_ok_p(desired_element_type,
			element_type,T))) {
		    if (SYMBOLP(desired_element_type)) {
			skip_list = CDR(Symbol_properties_table);
			key_value = desired_element_type;
			key_hash_value = 
				SXHASH_SYMBOL_1(desired_element_type) & 
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
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_13:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
		      next_loop_14:
			if ( !TRUEP(marked))
			    goto end_loop_13;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
			goto next_loop_14;
		      end_loop_13:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			gensymed_symbol_3 = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
			if ( !TRUEP(gensymed_symbol_3)) {
			    gensymed_symbol_3 = desired_element_type;
			    temp_1 = Symbol_properties_table;
			    temp_2 = 
				    FIX(SXHASH_SYMBOL_1(gensymed_symbol_3) 
				    & IFIX(Most_positive_fixnum));
			    tail = 
				    make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
				    Nil);
			    head = 
				    make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
				    tail);
			    new_cons = 
				    ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index));
			    if (new_cons) {
				temp_3 = Available_lookup_conses_vector;
				svref_arg_2 = Current_thread_index;
				svref_new_value = M_CDR(new_cons);
				SVREF(temp_3,svref_arg_2) = svref_new_value;
				if ( 
					!TRUEP(ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index)))) {
				    temp_3 = 
					    Available_lookup_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(temp_3,svref_arg_2) = Nil;
				}
				gensymed_symbol_4 = new_cons;
			    }
			    else
				gensymed_symbol_4 = Nil;
			    if ( !TRUEP(gensymed_symbol_4))
				gensymed_symbol_4 = 
					replenish_lookup_cons_pool();
			    M_CAR(gensymed_symbol_4) = 
				    Qsymbol_properties_hash_table;
			    new_cons = 
				    ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index));
			    if (new_cons) {
				temp_3 = Available_lookup_conses_vector;
				svref_arg_2 = Current_thread_index;
				svref_new_value = M_CDR(new_cons);
				SVREF(temp_3,svref_arg_2) = svref_new_value;
				if ( 
					!TRUEP(ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index)))) {
				    temp_3 = 
					    Available_lookup_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(temp_3,svref_arg_2) = Nil;
				}
				gensymed_symbol_5 = new_cons;
			    }
			    else
				gensymed_symbol_5 = Nil;
			    if ( !TRUEP(gensymed_symbol_5))
				gensymed_symbol_5 = 
					replenish_lookup_cons_pool();
			    M_CAR(gensymed_symbol_5) = head;
			    M_CDR(gensymed_symbol_5) = tail;
			    inline_note_allocate_cons(gensymed_symbol_5,
				    Qlookup);
			    M_CDR(gensymed_symbol_4) = gensymed_symbol_5;
			    inline_note_allocate_cons(gensymed_symbol_4,
				    Qlookup);
			    gensymed_symbol_3 = set_skip_list_entry(temp_1,
				    FIX((SI_Long)31L),Qeq,Nil,T,
				    gensymed_symbol_3,temp_2,
				    gensymed_symbol_4);
			}
			global_properties = gensymed_symbol_3;
			skip_list = CDR(global_properties);
			key_value = 
				Current_kb_specific_property_list_property_name;
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
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_16:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
		      next_loop_17:
			if ( !TRUEP(marked))
			    goto end_loop_16;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
			goto next_loop_17;
		      end_loop_16:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
				key_hash_value ? (EQ(key_value,ISVREF(curr,
				(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
				Nil) : Nil;
			if (kb_properties);
			else
			    kb_properties = Nil;
			if (kb_properties) {
			    skip_list = CDR(kb_properties);
			    key_value = Class_description_gkbprop;
			    key_hash_value = 
				    SXHASH_SYMBOL_1(Class_description_gkbprop) 
				    & IFIX(Most_positive_fixnum);
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
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_19:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp_2 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp_2);
			    MVS_2(result,succ,marked);
			  next_loop_20:
			    if ( !TRUEP(marked))
				goto end_loop_19;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp_2 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp_2);
			    MVS_2(result,succ,marked);
			    goto next_loop_20;
			  end_loop_19:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			    kb_specific_value = IFIX(ISVREF(curr,
				    (SI_Long)1L)) == key_hash_value ? 
				    (EQ(key_value,ISVREF(curr,
				    (SI_Long)2L)) ? ISVREF(curr,
				    (SI_Long)3L) : Nil) : Nil;
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
				    SXHASH_SYMBOL_1(Class_description_gkbprop) 
				    & IFIX(Most_positive_fixnum);
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
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_22:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp_2 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp_2);
			    MVS_2(result,succ,marked);
			  next_loop_23:
			    if ( !TRUEP(marked))
				goto end_loop_22;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp_2 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp_2);
			    MVS_2(result,succ,marked);
			    goto next_loop_23;
			  end_loop_22:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			    resulting_value = IFIX(ISVREF(curr,
				    (SI_Long)1L)) == key_hash_value ? 
				    (EQ(key_value,ISVREF(curr,
				    (SI_Long)2L)) ? ISVREF(curr,
				    (SI_Long)3L) : Nil) : Nil;
			    if (resulting_value);
			    else
				resulting_value = Nil;
			}
			temp = TRUEP(resulting_value);
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp);
		    else
			temp = 
				TRUEP(valid_type_specification_p(desired_element_type));
		    if (temp) {
			if ((SI_Long)1L <= IFIX(Warning_message_level))
			    give_warning_1(4,FIX((SI_Long)1L),
				    string_constant_65,
				    desired_element_type,
				    get_or_make_up_designation_for_block(domain));
		    }
		    else if ((SI_Long)1L <= IFIX(Warning_message_level))
			give_warning_1(5,FIX((SI_Long)1L),
				string_constant_66,desired_element_type,
				domain,desired_element_type);
		    return VALUES_3(Nil,Nil,Nil);
		}
		else {
		    possible_item_element_p_qm = 
			    g2_list_or_array_element_type_may_contain_item_p(element_type);
		    array_length = ISVREF(domain,(SI_Long)20L);
		    skip_element_test_qm = 
			    g2_list_or_array_type_ok_p(desired_element_type,
			    element_type,Nil);
		    temp_2 = array_length;
		    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp_2) && 
			    FIXNUM_LE(temp_2,FIX((SI_Long)127L)))) {
			continuation = 
				eval_cons_1(SYMBOL_FUNCTION(Qserve_remaining_g2_array_elements),
				eval_cons_1(domain,
				eval_cons_1(FIX((SI_Long)0L),
				skip_element_test_qm ? Nil : 
				desired_element_type)));
			return serve_remaining_g2_array_elements(T,
				continuation);
		    }
		    else
			switch (INTEGER_TO_CHAR(temp_2)) {
			  case 0:
			    return VALUES_3(Nil,Nil,Nil);
			  case 1:
			    item_or_evaluation_value_element_qm = 
				    g2_array_aref_item_or_evaluation_value(domain,
				    FIX((SI_Long)0L));
			    if ( 
				    !TRUEP(item_or_evaluation_value_element_qm) 
				    ||  !TRUEP(skip_element_test_qm) &&  
				    !TRUEP(g2_list_or_array_element_ok_p(item_or_evaluation_value_element_qm,
				    desired_element_type)))
				return VALUES_3(Nil,Nil,Nil);
			    else {
				temp =  !TRUEP(possible_item_element_p_qm);
				if (temp);
				else {
				    if (SIMPLE_VECTOR_P(item_or_evaluation_value_element_qm) 
					    && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_evaluation_value_element_qm)) 
					    > (SI_Long)2L &&  
					    !EQ(ISVREF(item_or_evaluation_value_element_qm,
					    (SI_Long)1L),
					    Qavailable_frame_vector)) {
					x2 = 
						ISVREF(item_or_evaluation_value_element_qm,
						(SI_Long)1L);
					temp = SIMPLE_VECTOR_P(x2) && 
						EQ(ISVREF(x2,(SI_Long)0L),
						Qg2_defstruct_structure_name_class_description_g2_struct) 
						? TRUEP(x2) : TRUEP(Qnil);
				    }
				    else
					temp = TRUEP(Nil);
				    temp =  !temp;
				}
				if (temp)
				    return VALUES_3(item_or_evaluation_value_element_qm,
					    Nil,Qnever);
				else if (serve_item_p(item_or_evaluation_value_element_qm))
				    return VALUES_3(item_or_evaluation_value_element_qm,
					    Nil,Qnever);
				else
				    return VALUES_3(Nil,Nil,Nil);
			    }
			  default:
			    continuation = 
				    eval_cons_1(SYMBOL_FUNCTION(Qserve_remaining_g2_array_elements),
				    eval_cons_1(domain,
				    eval_cons_1(FIX((SI_Long)0L),
				    skip_element_test_qm ? Nil : 
				    desired_element_type)));
			    return serve_remaining_g2_array_elements(T,
				    continuation);
			}
		}
	    }
	    else {
		if ((SI_Long)1L <= IFIX(Warning_message_level))
		    give_warning_1(3,FIX((SI_Long)1L),string_constant_67,
			    domain);
		return VALUES_3(Nil,Nil,Nil);
	    }
	}
    }
}

/* SERVE-NEXT-EVALUATION-SEQUENCE-VALUE */
Object serve_next_evaluation_sequence_value(continue_qm,continuation)
    Object continue_qm, continuation;
{
    Object elt_1, ab_loop_list_, list_qm, elt_to_serve, frame_serial_number;
    Object rest_qm, next_continuation_qm, thing, gensymed_symbol, xa, ya;
    char temp;

    x_note_fn_call(149,216);
    if ( !TRUEP(continue_qm)) {
	elt_1 = Nil;
	ab_loop_list_ = M_CDR(M_CDR(continuation));
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	elt_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !(FIXNUMP(elt_1) || SYMBOLP(elt_1) || SIMPLE_VECTOR_P(elt_1)))
	    reclaim_if_evaluation_value_1(elt_1);
	goto next_loop;
      end_loop:
	reclaim_frame_serial_number(M_CAR(M_CDR(continuation)));
	reclaim_eval_list_1(continuation);
	return VALUES_1(Qnil);
    }
    else if ( !TRUEP(continuation))
	return VALUES_3(Nil,Nil,Nil);
    else {
	list_qm = M_CDR(M_CDR(continuation));
	if (list_qm) {
	    elt_to_serve = M_CAR(list_qm);
	    frame_serial_number = M_CAR(M_CDR(continuation));
	    rest_qm = M_CDR(list_qm);
	    if ( !TRUEP(rest_qm)) {
		reclaim_eval_list_1(continuation);
		next_continuation_qm = Nil;
	    }
	    else {
		M_CDDR(continuation) = rest_qm;
		reclaim_eval_cons_1(list_qm);
		next_continuation_qm = continuation;
	    }
	    if (SIMPLE_VECTOR_P(elt_to_serve) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(elt_to_serve)) > 
		    (SI_Long)2L) {
		temp = EQ(ISVREF(elt_to_serve,(SI_Long)1L),
			Qavailable_frame_vector);
		if (temp);
		else {
		    thing = ISVREF(elt_to_serve,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(thing) ? EQ(ISVREF(thing,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    : TRUEP(Qnil);
		}
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		gensymed_symbol = ISVREF(elt_to_serve,(SI_Long)3L);
		temp = SIMPLE_VECTOR_P(elt_to_serve) ? 
			EQ(ISVREF(elt_to_serve,(SI_Long)1L),
			Qavailable_frame_vector) : TRUEP(Qnil);
		if (temp);
		else
		    temp = FIXNUMP(gensymed_symbol) ? 
			    IFIX(gensymed_symbol) == (SI_Long)-1L : TRUEP(Nil);
		if (temp);
		else if (FIXNUMP(frame_serial_number))
		    temp = FIXNUMP(gensymed_symbol) ? 
			    FIXNUM_LT(frame_serial_number,gensymed_symbol) 
			    : TRUEP(T);
		else if (FIXNUMP(gensymed_symbol))
		    temp = TRUEP(Nil);
		else {
		    xa = M_CAR(frame_serial_number);
		    ya = M_CAR(gensymed_symbol);
		    temp = FIXNUM_LT(xa,ya);
		    if (temp);
		    else
			temp = FIXNUM_EQ(xa,ya) ? 
				FIXNUM_LT(M_CDR(frame_serial_number),
				M_CDR(gensymed_symbol)) : TRUEP(Qnil);
		}
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		if (next_continuation_qm)
		    return serve_next_evaluation_sequence_value(T,
			    next_continuation_qm);
		else {
		    reclaim_frame_serial_number(frame_serial_number);
		    return VALUES_3(Nil,Nil,Nil);
		}
	    }
	    else {
		if ( !TRUEP(next_continuation_qm))
		    reclaim_frame_serial_number(frame_serial_number);
		return VALUES_3(elt_to_serve,next_continuation_qm,Qnever);
	    }
	}
	else {
	    reclaim_frame_serial_number(M_CAR(M_CDR(continuation)));
	    reclaim_eval_list_1(continuation);
	    return VALUES_3(Nil,Nil,Nil);
	}
    }
}

static Object Qserve_next_evaluation_sequence_value;  /* serve-next-evaluation-sequence-value */

/* SERVE-EVALUATION-SEQUENCE-VALUES */
Object serve_evaluation_sequence_values(sequence,desired_element_type)
    Object sequence, desired_element_type;
{
    Object temp, class_spec, type_spec, gensymed_symbol, held_vector, elt_1;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_2, validated_elt;
    Object eval_list, eval_list_tail, eval_cons, temp_1, svref_arg_2, temp_2;
    SI_Long next_index, length_1;

    x_note_fn_call(149,217);
    temp = copy_frame_serial_number(Current_frame_serial_number);
    class_spec = eval_list_2(Qab_class,desired_element_type);
    type_spec = 
	    type_specification_for_user_or_datum_type(desired_element_type);
    if (type_spec);
    else
	type_spec = class_spec;
    gensymed_symbol = sequence;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    elt_1 = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    elt_2 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    validated_elt = elt_2 ? validate_item_or_evaluation_value(elt_2,Nil,
	    Nil) : Nil;
    next_index = next_index + (SI_Long)1L;
    elt_1 = validated_elt;
    if (type_specification_type_p(elt_1,type_spec)) {
	ab_loopvar__2 = eval_cons_1(FIXNUMP(elt_1) || elt_1 && 
		SYMBOLP(elt_1) || SIMPLE_VECTOR_P(elt_1) ? elt_1 : 
		copy_if_evaluation_value_1(elt_1),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    eval_list = class_spec;
    eval_list_tail = M_CDR(class_spec);
    if (eval_list &&  !((SI_Long)0L == inline_debugging_consing())) {
	eval_cons = eval_list;
      next_loop_1:
	inline_note_reclaim_cons(eval_cons,Qeval);
	if (EQ(eval_cons,eval_list_tail))
	    goto end_1;
	else if ( !TRUEP(eval_cons))
	    goto end_1;
	else
	    eval_cons = CDR(eval_cons);
	goto next_loop_1;
      end_loop_1:
      end_1:;
    }
    if (ISVREF(Available_eval_conses_tail_vector,IFIX(Current_thread_index))) {
	temp_1 = ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp_1) = eval_list;
	temp_1 = Available_eval_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp_1,svref_arg_2) = eval_list_tail;
    }
    else {
	temp_1 = Available_eval_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp_1,svref_arg_2) = eval_list;
	temp_1 = Available_eval_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp_1,svref_arg_2) = eval_list_tail;
    }
    M_CDR(eval_list_tail) = Nil;
    temp_2 = ab_loopvar_;
    goto end_2;
    temp_2 = Qnil;
  end_2:;
    return serve_next_evaluation_sequence_value(T,
	    eval_cons_1(SYMBOL_FUNCTION(Qserve_next_evaluation_sequence_value),
	    eval_cons_1(temp,temp_2)));
}

/* SERVE-FIRST-ELEMENT-ITERATOR-INVERSE */
Object serve_first_element_iterator_inverse(item,quantifier,role,
	    domain_designation)
    Object item, quantifier, role, domain_designation;
{
    Object desired_list_type, x2, g2_list_element_structure, ab_loop_list_;
    Object g2_list, g2_list_type, result_1, ab_loopvar_, ab_loopvar__1;
    char temp;

    x_note_fn_call(149,218);
    desired_list_type = SECOND(role);
    if (SIMPLE_VECTOR_P(item) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(item,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(item,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if ( !temp)
	return VALUES_3(Nil,Nil,Nil);
    else {
	g2_list_element_structure = Nil;
	ab_loop_list_ = ISVREF(item,(SI_Long)13L);
	g2_list = Nil;
	g2_list_type = Nil;
	result_1 = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	g2_list_element_structure = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	g2_list = ISVREF(g2_list_element_structure,(SI_Long)5L);
	g2_list_type = ISVREF(g2_list,(SI_Long)21L);
	if (designation_could_denote_item_p(domain_designation,g2_list) && 
		( !EQ(quantifier,Qthe) || unique_value_of_role_p(item,role,
		g2_list)) && g2_list_or_array_type_ok_p(desired_list_type,
		g2_list_type,T) && g2_list_or_array_element_ok_p(item,
		desired_list_type)) {
	    ab_loopvar__1 = eval_cons_1(g2_list,Nil);
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		result_1 = ab_loopvar__1;
	    ab_loopvar_ = ab_loopvar__1;
	}
	goto next_loop;
      end_loop:
	return serve_all_unreprocessed_frames(result_1);
	return VALUES_1(Qnil);
    }
}

static Object string_constant_68;  /* "" */

static Object string_constant_69;  /* "~(~a~)~a~a that contains" */

/* ROLE-PRINT-MEMBER-ITERATOR */
Object role_print_member_iterator(role,local_variable_qm)
    Object role, local_variable_qm;
{
    Object temp, temp_1;

    x_note_fn_call(149,219);
    temp = SECOND(role);
    temp_1 = local_variable_qm;
    if (temp_1);
    else
	temp_1 = string_constant_68;
    GENSYM_RETURN_ONE(tformat(4,string_constant_69,temp,local_variable_qm ?
	     string_constant : string_constant_68,temp_1));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-MEMBER-ITERATOR */
Object serve_first_member_iterator(role,item)
    Object role, item;
{
    Object desired_list_type, class_description, list_of_g2_lists_to_return;
    Object g2_list_element_structure, ab_loop_list_, g2_list, gensymed_symbol;
    Object sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(149,220);
    desired_list_type = SECOND(role);
    class_description = 
	    lookup_global_or_kb_specific_property_value(desired_list_type,
	    Class_description_gkbprop);
    if (class_description) {
	list_of_g2_lists_to_return = Nil;
	g2_list_element_structure = Nil;
	ab_loop_list_ = ISVREF(item,(SI_Long)13L);
	g2_list = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	g2_list_element_structure = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	g2_list = ISVREF(g2_list_element_structure,(SI_Long)5L);
	gensymed_symbol = ISVREF(g2_list,(SI_Long)1L);
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(class_description,
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
	if (temp ?  !TRUEP(memq_function(g2_list,
		list_of_g2_lists_to_return)) : TRUEP(Nil))
	    list_of_g2_lists_to_return = eval_cons_1(g2_list,
		    list_of_g2_lists_to_return);
	goto next_loop;
      end_loop:
	temp_1 = list_of_g2_lists_to_return;
	goto end_1;
	temp_1 = Qnil;
      end_1:;
    }
    else
	temp_1 = Nil;
    return serve_all_unreprocessed_frames(temp_1);
}

static Object array_constant_8;    /* # */

static Object array_constant_9;    /* # */

static Object string_constant_70;  /* "~%~S~%" */

/* SERVE-FIRST-MEMBER-ITERATOR-INVERSE */
Object serve_first_member_iterator_inverse(item,quantifier,role,
	    domain_designation)
    Object item, quantifier, role, domain_designation;
{
    Object frame_or_frames, x2, element, ab_loop_list_, comparison_list;
    Object class_qm, sub_class_bit_vector, is_list, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_1, ab_loopvar_, ab_loopvar__1, gensymed_symbol_3;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, bv16_length, aref_arg_2;
    SI_Long aref_new_value, length_1;
    char temp;
    Declare_special(5);

    x_note_fn_call(149,221);
    frame_or_frames = Nil;
    if (SYMBOLP(domain_designation)) {
	frame_or_frames = 
		lookup_kb_specific_property_value(domain_designation,
		Frame_or_frames_with_this_name_kbprop);
	if (SIMPLE_VECTOR_P(item) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) 
		> (SI_Long)2L &&  !EQ(ISVREF(item,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if ( !temp)
	    return VALUES_3(Nil,Nil,Nil);
	else {
	    element = Nil;
	    ab_loop_list_ = ISVREF(frame_or_frames,(SI_Long)13L);
	    comparison_list = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    element = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    comparison_list = ISVREF(element,(SI_Long)5L);
	    if (EQ(comparison_list,item)) {
		temp = TRUEP(T);
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    temp = TRUEP(Qnil);
	  end_1:;
	    if (temp)
		return VALUES_3(item,Nil,Qnever);
	    else
		return VALUES_1(Nil);
	}
    }
    else {
	class_qm = atomic_class_element_of_designation(domain_designation);
	if (SIMPLE_VECTOR_P(item) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) 
		> (SI_Long)2L &&  !EQ(ISVREF(item,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(G2_list_class_description,(SI_Long)18L));
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
		is_list = (SI_Long)0L < gensymed_symbol ? T : Nil;
	    }
	    else
		is_list = Nil;
	}
	else
	    is_list = Nil;
	if ( !TRUEP(is_list)) {
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
		      twrite_beginning_of_wide_string(array_constant_8,
			      FIX((SI_Long)31L));
		      if (SIMPLE_VECTOR_P(item) && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > 
			      (SI_Long)2L &&  !EQ(ISVREF(item,(SI_Long)1L),
			      Qavailable_frame_vector)) {
			  x2 = ISVREF(item,(SI_Long)1L);
			  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				  (SI_Long)0L),
				  Qg2_defstruct_structure_name_class_description_g2_struct) 
				  ? TRUEP(x2) : TRUEP(Qnil);
		      }
		      else
			  temp = TRUEP(Nil);
		      if (temp)
			  twrite_general_string(string(ISVREF(ISVREF(item,
				  (SI_Long)1L),(SI_Long)1L)));
		      twrite_beginning_of_wide_string(array_constant_9,
			      FIX((SI_Long)78L));
		      temp_1 = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    notify_user_at_console_and_on_logbook(2,string_constant_70,temp_1);
	}
	if (class_qm && is_list) {
	    ab_loopvar_ = ISVREF(item,(SI_Long)20L);
	    ab_loopvar__1 = Nil;
	    element = Nil;
	    ab_loopvar__1 = ab_loopvar_ ? 
		    g2_list_structure_next(ISVREF(ab_loopvar_,(SI_Long)2L),
		    ab_loopvar_) : Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loopvar__1))
		goto end_loop_1;
	    element = ISVREF(ab_loopvar__1,(SI_Long)4L);
	    ab_loopvar__1 = g2_list_structure_next(ab_loopvar__1,ab_loopvar_);
	    if (SIMPLE_VECTOR_P(element) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(element,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(element,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		gensymed_symbol_3 = 
			lookup_global_or_kb_specific_property_value(ISVREF(ISVREF(element,
			(SI_Long)1L),(SI_Long)1L),Class_description_gkbprop);
		temp = gensymed_symbol_3 ? TRUEP(memq_function(class_qm,
			ISVREF(gensymed_symbol_3,(SI_Long)2L))) : TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		temp = TRUEP(T);
		goto end_2;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp = TRUEP(Qnil);
	  end_2:;
	}
	else
	    temp = TRUEP(Nil);
	if (temp ? TRUEP(serve_item_p(item)) : TRUEP(Nil))
	    return VALUES_3(item,Nil,Qnever);
	else
	    return VALUES_1(Nil);
    }
}

static Object Qitem_or_datum;      /* item-or-datum */

/* SERVE-REMAINING-LIST-ELEMENTS */
Object serve_remaining_list_elements(continue_qm,continuation)
    Object continue_qm, continuation;
{
    Object second_cons, element_structure_or_list_cons;
    Object desired_element_type_qm, frame_qm, sub_class_bit_vector;
    Object g2_list_frame_p_qm, temp, eval_cons, svref_arg_2, g2_list_frame;
    Object list_structure, list_type, possible_item_element_p_qm;
    Object item_element_p_qm, item_or_value_to_serve, next_element_structure;
    Object serve_item_or_value_p_qm, x2, gensymed_symbol_3, temp_2;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_1;

    x_note_fn_call(149,222);
    second_cons = CDR(continuation);
    element_structure_or_list_cons = CAR(second_cons);
    desired_element_type_qm = CDR(second_cons);
    if ( !TRUEP(continue_qm) || CONSP(element_structure_or_list_cons)) {
	if ( !TRUEP(element_structure_or_list_cons))
	    frame_qm = Nil;
	else if (CONSP(element_structure_or_list_cons))
	    frame_qm = CAR(element_structure_or_list_cons);
	else
	    frame_qm = ISVREF(element_structure_or_list_cons,(SI_Long)5L);
	if (frame_qm) {
	    sub_class_bit_vector = ISVREF(ISVREF(frame_qm,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(G2_list_class_description,(SI_Long)18L));
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
		g2_list_frame_p_qm = (SI_Long)0L < gensymed_symbol ? T : Nil;
	    }
	    else
		g2_list_frame_p_qm = Nil;
	}
	else
	    g2_list_frame_p_qm = Nil;
	if (g2_list_frame_p_qm) {
	    temp = delete_eval_element_1(continuation,ISVREF(frame_qm,
		    (SI_Long)23L));
	    ISVREF(frame_qm,(SI_Long)23L) = temp;
	}
	if (CONSP(element_structure_or_list_cons))
	    reclaim_eval_list_1(element_structure_or_list_cons);
	if (continuation &&  !((SI_Long)0L == inline_debugging_consing())) {
	    eval_cons = continuation;
	  next_loop:
	    inline_note_reclaim_cons(eval_cons,Qeval);
	    if (EQ(eval_cons,second_cons))
		goto end_1;
	    else if ( !TRUEP(eval_cons))
		goto end_1;
	    else
		eval_cons = CDR(eval_cons);
	    goto next_loop;
	  end_loop:
	  end_1:;
	}
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = continuation;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = second_cons;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = continuation;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = second_cons;
	}
	M_CDR(second_cons) = Nil;
	return VALUES_3(Nil,Nil,Nil);
    }
    else if (element_structure_or_list_cons) {
	g2_list_frame = ISVREF(element_structure_or_list_cons,(SI_Long)5L);
	list_structure = ISVREF(g2_list_frame,(SI_Long)20L);
	list_type = ISVREF(g2_list_frame,(SI_Long)21L);
	possible_item_element_p_qm = 
		g2_list_or_array_element_type_may_contain_item_p(list_type);
	item_element_p_qm = possible_item_element_p_qm ? ( !EQ(list_type,
		Qitem_or_datum) ? T : Nil) : Qnil;
	item_or_value_to_serve = ISVREF(element_structure_or_list_cons,
		(SI_Long)4L);
	next_element_structure = 
		g2_list_structure_next(element_structure_or_list_cons,
		list_structure);
	serve_item_or_value_p_qm = Nil;
      next_loop_1:
	temp_1 =  !TRUEP(desired_element_type_qm);
	if (temp_1);
	else {
	    if (item_element_p_qm) {
		if (SIMPLE_VECTOR_P(item_or_value_to_serve) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value_to_serve)) 
			> (SI_Long)2L &&  
			!EQ(ISVREF(item_or_value_to_serve,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value_to_serve,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		gensymed_symbol_3 = 
			lookup_global_or_kb_specific_property_value(desired_element_type_qm,
			Class_description_gkbprop);
		if (gensymed_symbol_3) {
		    sub_class_bit_vector = 
			    ISVREF(ISVREF(item_or_value_to_serve,
			    (SI_Long)1L),(SI_Long)19L);
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
			temp_1 = (SI_Long)0L < gensymed_symbol;
		    }
		    else
			temp_1 = TRUEP(Nil);
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else if ( !TRUEP(item_element_p_qm))
		temp_1 = 
			TRUEP(g2_list_or_array_element_ok_p(item_or_value_to_serve,
			desired_element_type_qm));
	    else
		temp_1 = TRUEP(Qnil);
	}
	if (temp_1) {
	    temp_2 =  !TRUEP(possible_item_element_p_qm) ? T : Nil;
	    if (temp_2);
	    else {
		if (SIMPLE_VECTOR_P(item_or_value_to_serve) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value_to_serve)) 
			> (SI_Long)2L &&  
			!EQ(ISVREF(item_or_value_to_serve,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value_to_serve,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp_2 =  !temp_1 ? T : Nil;
	    }
	    if (temp_2);
	    else
		temp_2 = serve_item_p(item_or_value_to_serve);
	    serve_item_or_value_p_qm = temp_2;
	}
	else
	    serve_item_or_value_p_qm = Nil;
	if ( !TRUEP(next_element_structure))
	    goto end_loop_1;
	if (serve_item_or_value_p_qm) {
	    M_SECOND(continuation) = next_element_structure;
	    if (possible_item_element_p_qm) {
		if (SIMPLE_VECTOR_P(item_or_value_to_serve) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value_to_serve)) 
			> (SI_Long)2L &&  
			!EQ(ISVREF(item_or_value_to_serve,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value_to_serve,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_2 = temp_1 ? item_or_value_to_serve : 
		    item_or_value_to_serve ? 
		    (FIXNUMP(item_or_value_to_serve) || 
		    item_or_value_to_serve && 
		    SYMBOLP(item_or_value_to_serve) ? 
		    item_or_value_to_serve : 
		    copy_evaluation_value_1(item_or_value_to_serve)) : Nil;
	    return VALUES_3(temp_2,continuation,Qnever);
	}
	item_or_value_to_serve = ISVREF(next_element_structure,(SI_Long)4L);
	next_element_structure = 
		g2_list_structure_next(next_element_structure,list_structure);
	goto next_loop_1;
      end_loop_1:
	temp = delete_eval_element_1(continuation,ISVREF(g2_list_frame,
		(SI_Long)23L));
	ISVREF(g2_list_frame,(SI_Long)23L) = temp;
	if (continuation &&  !((SI_Long)0L == inline_debugging_consing())) {
	    eval_cons = continuation;
	  next_loop_2:
	    inline_note_reclaim_cons(eval_cons,Qeval);
	    if (EQ(eval_cons,second_cons))
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
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = continuation;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = second_cons;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = continuation;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = second_cons;
	}
	M_CDR(second_cons) = Nil;
	if (serve_item_or_value_p_qm) {
	    if (possible_item_element_p_qm) {
		if (SIMPLE_VECTOR_P(item_or_value_to_serve) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value_to_serve)) 
			> (SI_Long)2L &&  
			!EQ(ISVREF(item_or_value_to_serve,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value_to_serve,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_2 = temp_1 ? item_or_value_to_serve : 
		    item_or_value_to_serve ? 
		    (FIXNUMP(item_or_value_to_serve) || 
		    item_or_value_to_serve && 
		    SYMBOLP(item_or_value_to_serve) ? 
		    item_or_value_to_serve : 
		    copy_evaluation_value_1(item_or_value_to_serve)) : Nil;
	    return VALUES_3(temp_2,Nil,Qnever);
	}
	else
	    return VALUES_3(Nil,Nil,Nil);
	return VALUES_1(Qnil);
    }
    else {
	if (continuation &&  !((SI_Long)0L == inline_debugging_consing())) {
	    eval_cons = continuation;
	  next_loop_3:
	    inline_note_reclaim_cons(eval_cons,Qeval);
	    if (EQ(eval_cons,second_cons))
		goto end_3;
	    else if ( !TRUEP(eval_cons))
		goto end_3;
	    else
		eval_cons = CDR(eval_cons);
	    goto next_loop_3;
	  end_loop_3:
	  end_3:;
	}
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = continuation;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = second_cons;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = continuation;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = second_cons;
	}
	M_CDR(second_cons) = Nil;
	return VALUES_3(Nil,Nil,Nil);
    }
}

/* SERVE-REMAINING-G2-ARRAY-ELEMENTS */
Object serve_remaining_g2_array_elements(continue_qm,continuation)
    Object continue_qm, continuation;
{
    Object gensymed_symbol, g2_array, starting_index, element_type_filter_qm;
    Object g2_array_length, element_type, possible_item_element_p_qm;
    Object eval_list, eval_list_tail, eval_cons, temp, svref_arg_2;
    Object current_index, following_index, item_or_evaluation_value_element_qm;
    Object serve_element_qm, serve_continuation_qm, serve_expiration_qm, x2;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(149,223);
    gensymed_symbol = continuation;
    gensymed_symbol = CDR(gensymed_symbol);
    g2_array = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    starting_index = CAR(gensymed_symbol);
    element_type_filter_qm = CDR(gensymed_symbol);
    g2_array_length = ISVREF(g2_array,(SI_Long)20L);
    element_type = ISVREF(g2_array,(SI_Long)21L);
    possible_item_element_p_qm = 
	    g2_list_or_array_element_type_may_contain_item_p(element_type);
    if ( !TRUEP(continue_qm)) {
	eval_list = continuation;
	eval_list_tail = CDDR(continuation);
	if (eval_list &&  !((SI_Long)0L == inline_debugging_consing())) {
	    eval_cons = eval_list;
	  next_loop:
	    inline_note_reclaim_cons(eval_cons,Qeval);
	    if (EQ(eval_cons,eval_list_tail))
		goto end_1;
	    else if ( !TRUEP(eval_cons))
		goto end_1;
	    else
		eval_cons = CDR(eval_cons);
	    goto next_loop;
	  end_loop:
	  end_1:;
	}
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = eval_list;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = eval_list_tail;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = eval_list;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = eval_list_tail;
	}
	M_CDR(eval_list_tail) = Nil;
	result = VALUES_3(Nil,Nil,Nil);
    }
    else if (FIXNUM_GE(starting_index,g2_array_length)) {
	eval_list = continuation;
	eval_list_tail = CDDR(continuation);
	if (eval_list &&  !((SI_Long)0L == inline_debugging_consing())) {
	    eval_cons = eval_list;
	  next_loop_1:
	    inline_note_reclaim_cons(eval_cons,Qeval);
	    if (EQ(eval_cons,eval_list_tail))
		goto end_2;
	    else if ( !TRUEP(eval_cons))
		goto end_2;
	    else
		eval_cons = CDR(eval_cons);
	    goto next_loop_1;
	  end_loop_1:
	  end_2:;
	}
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = eval_list;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = eval_list_tail;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = eval_list;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = eval_list_tail;
	}
	M_CDR(eval_list_tail) = Nil;
	result = VALUES_3(Nil,Nil,Nil);
    }
    else {
	current_index = starting_index;
	PUSH_SPECIAL_WITH_SYMBOL(Current_index,Qcurrent_index,current_index,0);
	  following_index = Nil;
	  item_or_evaluation_value_element_qm = Nil;
	  serve_element_qm = Nil;
	  serve_continuation_qm = Nil;
	  serve_expiration_qm = Nil;
	next_loop_2:
	  following_index = FIXNUM_ADD1(Current_index);
	  item_or_evaluation_value_element_qm = 
		  g2_array_aref_item_or_evaluation_value(g2_array,
		  Current_index);
	  if (item_or_evaluation_value_element_qm && ( 
		  !TRUEP(element_type_filter_qm) || 
		  g2_list_or_array_element_ok_p(item_or_evaluation_value_element_qm,
		  element_type_filter_qm))) {
	      temp_1 =  !TRUEP(possible_item_element_p_qm);
	      if (temp_1);
	      else {
		  if (SIMPLE_VECTOR_P(item_or_evaluation_value_element_qm) 
			  && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_evaluation_value_element_qm)) 
			  > (SI_Long)2L &&  
			  !EQ(ISVREF(item_or_evaluation_value_element_qm,
			  (SI_Long)1L),Qavailable_frame_vector)) {
		      x2 = ISVREF(item_or_evaluation_value_element_qm,
			      (SI_Long)1L);
		      temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			      (SI_Long)0L),
			      Qg2_defstruct_structure_name_class_description_g2_struct) 
			      ? TRUEP(x2) : TRUEP(Qnil);
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  temp_1 =  !temp_1;
	      }
	      if (temp_1);
	      else
		  temp_1 = 
			  TRUEP(serve_item_p(item_or_evaluation_value_element_qm));
	      serve_element_qm = temp_1 ? 
		      item_or_evaluation_value_element_qm : Nil;
	      if (serve_element_qm) {
		  if (FIXNUM_LT(following_index,g2_array_length))
		      serve_continuation_qm = continuation;
		  serve_expiration_qm = Qnever;
		  M_THIRD(continuation) = following_index;
	      }
	  }
	  if (item_or_evaluation_value_element_qm &&  
		      !TRUEP(serve_element_qm)) {
	      if ( !(FIXNUMP(item_or_evaluation_value_element_qm) || 
		      SYMBOLP(item_or_evaluation_value_element_qm) || 
		      SIMPLE_VECTOR_P(item_or_evaluation_value_element_qm)))
		  reclaim_if_evaluation_value_1(item_or_evaluation_value_element_qm);
	  }
	  if (FIXNUM_GE(following_index,g2_array_length) || serve_element_qm)
	      goto end_loop_2;
	  Current_index = FIXNUM_ADD1(Current_index);
	  goto next_loop_2;
	end_loop_2:
	  if ( !TRUEP(serve_continuation_qm)) {
	      eval_list = continuation;
	      eval_list_tail = CDDR(continuation);
	      if (eval_list &&  !((SI_Long)0L == inline_debugging_consing())) {
		  eval_cons = eval_list;
		next_loop_3:
		  inline_note_reclaim_cons(eval_cons,Qeval);
		  if (EQ(eval_cons,eval_list_tail))
		      goto end_3;
		  else if ( !TRUEP(eval_cons))
		      goto end_3;
		  else
		      eval_cons = CDR(eval_cons);
		  goto next_loop_3;
		end_loop_3:
		end_3:;
	      }
	      if (ISVREF(Available_eval_conses_tail_vector,
		      IFIX(Current_thread_index))) {
		  temp = ISVREF(Available_eval_conses_tail_vector,
			  IFIX(Current_thread_index));
		  M_CDR(temp) = eval_list;
		  temp = Available_eval_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp,svref_arg_2) = eval_list_tail;
	      }
	      else {
		  temp = Available_eval_conses_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp,svref_arg_2) = eval_list;
		  temp = Available_eval_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp,svref_arg_2) = eval_list_tail;
	      }
	      M_CDR(eval_list_tail) = Nil;
	  }
	  result = VALUES_3(serve_element_qm,serve_continuation_qm,
		  serve_expiration_qm);
	  POP_SPECIAL();
	  goto end_serve_remaining_g2_array_elements;
	  result = VALUES_1(Qnil);
	POP_SPECIAL();
    }
  end_serve_remaining_g2_array_elements:
    return result;
}

static Object string_constant_71;  /* "~a" */

static Object string_constant_72;  /* " ~a" */

static Object array_constant_10;   /* # */

static Object string_constant_73;  /* "~NQ " */

static Object string_constant_74;  /* " of the ~a if indexed with the value" */

/* ROLE-PRINT-INDEXED-ATTRIBUTE */
Object role_print_indexed_attribute(role,local_variable_qm)
    Object role, local_variable_qm;
{
    Object attribute_name_or_role, class_1, class_qualifier_qm, attribute_name;

    x_note_fn_call(149,224);
    attribute_name_or_role = SECOND(role);
    class_1 = THIRD(role);
    class_qualifier_qm = CONSP(attribute_name_or_role) && 
	    EQ(M_CAR(attribute_name_or_role),Qclass_qualified_name) ? 
	    M_CAR(M_CDR(attribute_name_or_role)) : Nil;
    attribute_name = SYMBOLP(attribute_name_or_role) ? 
	    attribute_name_or_role : THIRD(attribute_name_or_role);
    tformat(2,string_constant_71,class_1);
    if (local_variable_qm)
	tformat(2,string_constant_72,local_variable_qm);
    twrite_beginning_of_wide_string(array_constant_10,FIX((SI_Long)12L));
    if (class_qualifier_qm)
	tformat(3,string_constant_73,attribute_name,class_qualifier_qm);
    else
	tformat(2,string_constant_71,attribute_name);
    GENSYM_RETURN_ONE(tformat(2,string_constant_74,class_1));
    return VALUES_1(Nil);
}

static Object Quuid;               /* uuid */

/* SERVE-FIRST-INDEXED-ATTRIBUTE */
Object serve_first_indexed_attribute(role,attribute_value)
    Object role, attribute_value;
{
    Object gensymed_symbol, attribute_role, class_1, class_qualified_name_p_qm;
    Object class_qualifier_qm, attribute, unpacked_value;
    Object indexed_attribute_value_qm, indexed_attribute_table_qm;
    Object class_description_qm, temp_1, skip_list, key_value, marked, pred;
    Object curr, succ, reference, temp_2, entry_hash, parent_and_class_tree_qm;
    Object scope_conses, ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_binary_tree_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, hashed_item, defining_classes;
    Object slot_description_qm, defining_class_of_attribute_qm, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, ab_less_than_branch_qm_;
    Object sub_class_bit_vector, item_or_item_list, item, ab_loop_list_;
    SI_Long gensymed_symbol_1, temp, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_, superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;
    char temp_3;
    Declare_special(1);
    Object result;

    x_note_fn_call(149,225);
    gensymed_symbol = role;
    gensymed_symbol = CDR(gensymed_symbol);
    attribute_role = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    class_1 = CAR(gensymed_symbol);
    class_qualified_name_p_qm = CONSP(attribute_role) ? 
	    (EQ(M_CAR(attribute_role),Qclass_qualified_name) ? T : Nil) : Qnil;
    class_qualifier_qm = class_qualified_name_p_qm ? 
	    M_CAR(M_CDR(attribute_role)) : Nil;
    attribute = class_qualified_name_p_qm ? THIRD(attribute_role) : 
	    attribute_role;
    unpacked_value = evaluation_value_value(attribute_value);
    indexed_attribute_value_qm = 
	    indexed_attribute_or_inherited_attribute_for_class_p(attribute,
	    class_1) && valid_indexed_attribute_value_p(unpacked_value) ? 
	    unpacked_value : Qnil;
    indexed_attribute_table_qm = 
	    lookup_kb_specific_property_value(attribute,
	    Indexed_attribute_hash_table_kbprop);
    class_description_qm = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    if (indexed_attribute_value_qm && indexed_attribute_table_qm && 
	    class_description_qm) {
	if (FIXNUMP(indexed_attribute_value_qm))
	    gensymed_symbol_1 = IFIX(FIXNUM_ABS(indexed_attribute_value_qm));
	else if (SYMBOLP(indexed_attribute_value_qm))
	    gensymed_symbol_1 = 
		    SXHASH_SYMBOL_1(indexed_attribute_value_qm) & 
		    IFIX(Most_positive_fixnum);
	else if (text_string_p(indexed_attribute_value_qm))
	    gensymed_symbol_1 = 
		    IFIX(compute_text_hash_code(indexed_attribute_value_qm));
	else
	    gensymed_symbol_1 = (SI_Long)0L;
	temp = gensymed_symbol_1 % (SI_Long)43L;
	temp_1 = SVREF(indexed_attribute_table_qm,FIX(temp));
	skip_list = CDR(temp_1);
	key_value = indexed_attribute_value_qm;
	key_hash_value = gensymed_symbol_1;
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
	temp_2 = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_2,temp_1);
	MVS_2(result,succ,marked);
      next_loop_2:
	if ( !TRUEP(marked))
	    goto end_loop_1;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_2 = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_2,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_2;
      end_loop_1:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  
		!TRUEP(evaluation_value_equal_p(key_value,ISVREF(curr,
		(SI_Long)2L)))) {
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
	parent_and_class_tree_qm = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		key_hash_value ? (evaluation_value_equal_p(key_value,
		ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
		Nil) : Nil;
	if (parent_and_class_tree_qm) {
	    scope_conses = Scope_conses;
	    ab_node_stack_ = Nil;
	    ab_current_node_ = Nil;
	    ab_skip_list_form_ = parent_and_class_tree_qm;
	    ab_binary_tree_form_ = parent_and_class_tree_qm;
	    gensymed_symbol = CDR(parent_and_class_tree_qm);
	    if (CONSP(gensymed_symbol)) {
		temp_1 = M_CAR(gensymed_symbol);
		temp_3 = SIMPLE_VECTOR_P(temp_1);
	    }
	    else
		temp_3 = TRUEP(Nil);
	    if (temp_3) {
		temp_1 = M_CDR(gensymed_symbol);
		ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
	    }
	    else
		ab_skip_list_p_ = Nil;
	    ab_next_node_ = Nil;
	    ab_tail_node_ = Nil;
	    ab_current_alist_ = Nil;
	    ab_entry_cons_ = Nil;
	    hashed_item = Nil;
	    defining_classes = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
	      slot_description_qm = Nil;
	      defining_class_of_attribute_qm = Nil;
	      ab_loopvar_ = Nil;
	      ab_loopvar__1 = Nil;
	      ab_loopvar__2 = Nil;
	      if (ab_skip_list_p_) {
		  ab_next_node_ = 
			  ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
			  (SI_Long)0L),(SI_Long)0L));
		  ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
		  if (EQ(ab_next_node_,ab_tail_node_))
		      ab_next_node_ = Nil;
	      }
	      else
		  ab_next_node_ = M_CDR(ab_binary_tree_form_);
	    next_loop_3:
	      if (ab_current_alist_) {
		  ab_entry_cons_ = M_CAR(ab_current_alist_);
		  ab_current_alist_ = M_CDR(ab_current_alist_);
	      }
	      else if (ab_skip_list_p_) {
		  if (ab_next_node_) {
		      ab_current_node_ = ab_next_node_;
		      ab_next_node_ = 
			      ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node_,
			      (SI_Long)0L),(SI_Long)0L));
		      if (EQ(ab_next_node_,ab_tail_node_))
			  ab_next_node_ = Nil;
		      ab_entry_cons_ = scope_cons(ISVREF(ab_current_node_,
			      (SI_Long)2L),ISVREF(ab_current_node_,
			      (SI_Long)3L));
		  }
		  else
		      ab_current_node_ = Nil;
	      }
	      else {
		  if (ab_next_node_) {
		      ab_current_node_ = ab_next_node_;
		      ab_less_than_branch_qm_ = Nil;
		    next_loop_4:
		      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			      (SI_Long)1L);
		      if ( !TRUEP(ab_less_than_branch_qm_))
			  goto end_loop_3;
		      ab_node_stack_ = scope_cons(ab_current_node_,
			      ab_node_stack_);
		      ab_current_node_ = ab_less_than_branch_qm_;
		      goto next_loop_4;
		    end_loop_3:;
		  }
		  else if (ab_node_stack_) {
		      ab_next_node_ = ab_node_stack_;
		      ab_current_node_ = M_CAR(ab_node_stack_);
		      ab_node_stack_ = M_CDR(ab_node_stack_);
		  }
		  else
		      ab_current_node_ = Nil;
		  if (ab_current_node_) {
		      ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
		      ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
		      ab_entry_cons_ = M_CAR(ab_current_alist_);
		      ab_current_alist_ = M_CDR(ab_current_alist_);
		  }
	      }
	      if ( !TRUEP(ab_current_node_))
		  goto end_loop_4;
	      hashed_item = CAR(ab_entry_cons_);
	      defining_classes = CDR(ab_entry_cons_);
	      slot_description_qm = 
		      get_slot_description_of_class_description_function(attribute,
		      ISVREF(hashed_item,(SI_Long)1L),class_qualifier_qm);
	      defining_class_of_attribute_qm = slot_description_qm ? 
		      ISVREF(slot_description_qm,(SI_Long)3L) : Nil;
	      gensymed_symbol = ISVREF(hashed_item,(SI_Long)1L);
	      sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	      superior_class_bit_number = IFIX(ISVREF(class_description_qm,
		      (SI_Long)18L));
	      sub_class_vector_index = superior_class_bit_number >>  -  - 
		      (SI_Long)3L;
	      if (sub_class_vector_index < 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		  gensymed_symbol_1 = 
			  UBYTE_8_ISAREF_1(sub_class_bit_vector,
			  sub_class_vector_index);
		  gensymed_symbol_2 = (SI_Long)1L;
		  gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
		  gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		  gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		  temp_3 = (SI_Long)0L < gensymed_symbol_1;
	      }
	      else
		  temp_3 = TRUEP(Nil);
	      if (temp_3 ? 
		      TRUEP(memq_function(defining_class_of_attribute_qm,
		      defining_classes)) : TRUEP(Nil)) {
		  ab_loopvar__2 = eval_cons_1(hashed_item,Nil);
		  if (ab_loopvar__1)
		      M_CDR(ab_loopvar__1) = ab_loopvar__2;
		  else
		      ab_loopvar_ = ab_loopvar__2;
		  ab_loopvar__1 = ab_loopvar__2;
	      }
	      goto next_loop_3;
	    end_loop_4:
	      temp_1 = ab_loopvar_;
	      goto end_2;
	      temp_1 = Qnil;
	    end_2:;
	    POP_SPECIAL();
	}
	else
	    temp_1 = Nil;
	return serve_all_unreprocessed_frames(temp_1);
    }
    else if (EQ(attribute,Quuid) &&  !TRUEP(class_qualifier_qm) && 
	    class_description_qm && T && text_string_p(attribute_value)) {
	item_or_item_list = get_item_or_item_list_for_uuid(attribute_value);
	if ( !TRUEP(item_or_item_list))
	    temp_1 = Nil;
	else if (ATOM(item_or_item_list)) {
	    gensymed_symbol = ISVREF(item_or_item_list,(SI_Long)1L);
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(class_description_qm,
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
		temp_3 = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp_3 = TRUEP(Nil);
	    temp_1 = temp_3 ? eval_cons_1(item_or_item_list,Nil) : Nil;
	}
	else {
	    item = Nil;
	    ab_loop_list_ = item_or_item_list;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop_5:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_5;
	    item = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    gensymed_symbol = ISVREF(item,(SI_Long)1L);
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(class_description_qm,
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
		temp_3 = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp_3 = TRUEP(Nil);
	    if (temp_3) {
		ab_loopvar__2 = eval_cons_1(item,Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
	    }
	    goto next_loop_5;
	  end_loop_5:
	    temp_1 = ab_loopvar_;
	    goto end_3;
	    temp_1 = Qnil;
	  end_3:;
	}
	return serve_all_unreprocessed_frames(temp_1);
    }
    else if (class_description_qm && ISVREF(class_description_qm,(SI_Long)16L))
	return serve_all_unreprocessed_frames(collect_instances_of_class_for_role_service(class_1));
    else
	return VALUES_3(Nil,Nil,Nil);
}

/* SERVE-FIRST-ATTRIBUTE-FRAME-OR-PLACE-REFERENCE */
Object serve_first_attribute_frame_or_place_reference(role,parent_frame,
	    attribute_name)
    Object role, parent_frame, attribute_name;
{
    x_note_fn_call(149,226);
    return VALUES_3(Nil,Nil,Nil);
}

/* SERVE-FIRST-ELEMENT-FRAME-OR-PLACE-REFERENCE */
Object serve_first_element_frame_or_place_reference(role,list_or_array,index_1)
    Object role, list_or_array, index_1;
{
    x_note_fn_call(149,227);
    return VALUES_3(Nil,Nil,Nil);
}

/* SERVE-FIRST-CLASS-QUALIFIED-NAME-FRAME-OR-PLACE-REFERENCE */
Object serve_first_class_qualified_name_frame_or_place_reference(role,
	    parent_frame)
    Object role, parent_frame;
{
    x_note_fn_call(149,228);
    return VALUES_3(Nil,Nil,Nil);
}

/* ROLE-PRINT-CLASS-QUALIFIED-METHOD */
Object role_print_class_qualified_method(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,229);
    twrite_symbol(1,SECOND(role));
    twrite_beginning_of_wide_string(array_constant_5,FIX((SI_Long)2L));
    GENSYM_RETURN_ONE(twrite_symbol(1,THIRD(role)));
    return VALUES_1(Nil);
}

/* SERVE-FIRST-CLASS-QUALIFIED-METHOD */
Object serve_first_class_qualified_method(role,domain)
    Object role, domain;
{
    Object class_cons, class_1, method_name, method_list_qm, frame;
    Object ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp;

    x_note_fn_call(149,230);
    class_cons = M_CDR(role);
    class_1 = M_CAR(class_cons);
    method_name = M_CAR(M_CDR(class_cons));
    method_list_qm = 
	    get_specific_methods_for_class_or_superior_class(method_name,
	    class_1);
    if (method_list_qm) {
	frame = Nil;
	ab_loop_list_ = method_list_qm;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	frame = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = eval_cons_1(frame,Nil);
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
	return serve_all_unreprocessed_frames(temp);
    }
    else
	return VALUES_3(Nil,Nil,Nil);
}

/* SERVE-FIRST-NEXT-PROCEDURE-METHOD */
Object serve_first_next_procedure_method(role,domain)
    Object role, domain;
{
    Object gensymed_symbol, name, class_1, arg_count, next_method_or_string;

    x_note_fn_call(149,231);
    gensymed_symbol = role;
    gensymed_symbol = CDR(gensymed_symbol);
    name = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    class_1 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    arg_count = CAR(gensymed_symbol);
    next_method_or_string = get_next_specific_method(name,class_1,
	    arg_count,ISVREF(domain,(SI_Long)1L));
    if (text_string_p(next_method_or_string))
	return VALUES_3(Nil,Nil,Nil);
    else
	return VALUES_3(next_method_or_string,Nil,Qnever);
}

/* VALIDATE-ROLE-SERVICE */
Object validate_role_service()
{
    x_note_fn_call(149,232);
    return decache_roles_for_all_items();
}

DEFINE_VARIABLE_WITH_SYMBOL(Unique_value_roles, Qunique_value_roles);

Object Unique_value_of_role_server_macro_prop = UNBOUND;

Object Unique_value_of_role_server_function_prop = UNBOUND;

Object Unique_value_of_role_next_role_prop = UNBOUND;

Object Unique_value_of_role_server_domain_count_prop = UNBOUND;

/* ROLE-PRINT-NAMED-BY-SYMBOL */
Object role_print_named_by_symbol(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,233);
    GENSYM_RETURN_ONE(print_standard_two_element_role(role,
	    local_variable_qm,string_constant_4));
    return VALUES_1(Nil);
}

static Object array_constant_11;   /* # */

/* SERVE-UNIQUE-NAMED-BY-SYMBOL-VALUE */
Object serve_unique_named_by_symbol_value(top_of_stack,role_constant,
	    no_item_allowed_p,name)
    Object top_of_stack, role_constant, no_item_allowed_p, name;
{
    Object class_1, class_description_qm, frame_or_frames_qm, unique_item_qm;
    Object frame, ab_loop_list_, gensymed_symbol, sub_class_bit_vector;
    Object top_of_stack_1, text_string, snapshots, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_1, schar_arg_2, schar_new_value, message_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, thing;
    char temp;
    Declare_special(7);

    x_note_fn_call(149,234);
    class_1 = M_CAR(M_CDR(role_constant));
    class_description_qm = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    frame_or_frames_qm = Nil;
    unique_item_qm = Nil;
    if ( !TRUEP(name))
	unique_item_qm = Nil;
    else if ( !TRUEP(class_description_qm) ||  
	    !TRUEP(ISVREF(class_description_qm,(SI_Long)16L)))
	unique_item_qm = Nil;
    else {
	frame_or_frames_qm = lookup_kb_specific_property_value(name,
		Frame_or_frames_with_this_name_kbprop);
	if (CONSP(frame_or_frames_qm)) {
	    frame = Nil;
	    ab_loop_list_ = frame_or_frames_qm;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    frame = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    gensymed_symbol = ISVREF(frame,(SI_Long)1L);
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(class_description_qm,
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
	    if (temp ? TRUEP(serve_item_p(frame)) : TRUEP(Nil)) {
		unique_item_qm = frame;
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    unique_item_qm = Qnil;
	  end_1:;
	}
	else {
	    if (frame_or_frames_qm) {
		gensymed_symbol = ISVREF(frame_or_frames_qm,(SI_Long)1L);
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(class_description_qm,(SI_Long)18L));
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
	    if (temp ? TRUEP(serve_item_p(frame_or_frames_qm)) : TRUEP(Nil))
		unique_item_qm = frame_or_frames_qm;
	    else
		unique_item_qm = Nil;
	}
    }
    if ( !(unique_item_qm || no_item_allowed_p)) {
	top_of_stack_1 = top_of_stack;
	text_string = Nil;
	snapshots = Nil;
	snapshots_of_related_blocks = Nil;
	note_blocks_in_tformat = SYMBOL_FUNCTION(Qrecord_block_for_tformat);
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
		      twrite_beginning_of_wide_string(array_constant_11,
			      FIX((SI_Long)37L));
		      print_role(role_constant);
		      if (EQ(Current_twriting_output_type,Qwide_string)) {
			  thing = (SI_Long)32L;
			  twrite_wide_character(CHARACTERP(FIX(thing)) ? 
				  CHAR_CODE(FIX(thing)) : FIX(thing));
		      }
		      else {
			  if ( 
				  !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				  Total_length_of_current_gensym_string))
			      extend_current_gensym_string(0);
			  temp_1 = Current_gensym_string;
			  schar_arg_2 = Fill_pointer_for_current_gensym_string;
			  thing = (SI_Long)32L;
			  schar_new_value = 
				  CODE_CHAR(CHARACTERP(FIX(thing)) ? 
				  CHAR_CODE(FIX(thing)) : FIX(thing));
			  SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
			  temp_1 = 
				  FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			  Fill_pointer_for_current_gensym_string = temp_1;
		      }
		      write_stored_value(name);
		      text_string = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    snapshots = Snapshots_of_related_blocks;
	    Snapshots_of_related_blocks = Nil;
	    if (Snapshots_of_related_blocks) {
		reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
		Snapshots_of_related_blocks = Nil;
	    }
	  POP_SPECIAL();
	POP_SPECIAL();
	message_1 = make_error_text(text_string,snapshots);
	raw_stack_error_named_error(top_of_stack_1,message_1);
    }
    GENSYM_RETURN_ONE(unique_item_qm);
    return VALUES_1(Nil);
}

/* ROLE-PRINT-NAME-OF-ITEM */
Object role_print_name_of_item(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,235);
    GENSYM_RETURN_ONE(print_role_whose_car_is_role_server(role,
	    local_variable_qm));
    return VALUES_1(Nil);
}

/* NAME-OF-ITEM-INVALID-REFERENCE-MESSAGE */
Object name_of_item_invalid_reference_message(role_constant,item_qm)
    Object role_constant, item_qm;
{
    Object text_string, snapshots, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, schar_arg_2, schar_new_value;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, thing;
    Declare_special(7);

    x_note_fn_call(149,236);
    text_string = Nil;
    snapshots = Nil;
    snapshots_of_related_blocks = Nil;
    note_blocks_in_tformat = SYMBOL_FUNCTION(Qrecord_block_for_tformat);
    PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
	    6);
      PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
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
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			0);
		  twrite_beginning_of_wide_string(array_constant_11,
			  FIX((SI_Long)37L));
		  print_role(role_constant);
		  if (EQ(Current_twriting_output_type,Qwide_string)) {
		      thing = (SI_Long)32L;
		      twrite_wide_character(CHARACTERP(FIX(thing)) ? 
			      CHAR_CODE(FIX(thing)) : FIX(thing));
		  }
		  else {
		      if ( 
			      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			      Total_length_of_current_gensym_string))
			  extend_current_gensym_string(0);
		      temp = Current_gensym_string;
		      schar_arg_2 = Fill_pointer_for_current_gensym_string;
		      thing = (SI_Long)32L;
		      schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
			      CHAR_CODE(FIX(thing)) : FIX(thing));
		      SET_SCHAR(temp,schar_arg_2,schar_new_value);
		      temp = 
			      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		      Fill_pointer_for_current_gensym_string = temp;
		  }
		  write_stored_value(item_qm);
		  text_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	snapshots = Snapshots_of_related_blocks;
	Snapshots_of_related_blocks = Nil;
	if (Snapshots_of_related_blocks) {
	    reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
	    Snapshots_of_related_blocks = Nil;
	}
      POP_SPECIAL();
    POP_SPECIAL();
    return make_error_text(text_string,snapshots);
}

/* SERVE-UNIQUE-NAME-OF-ITEM-VALUE */
Object serve_unique_name_of_item_value(top_of_stack,role_constant,
	    no_name_allowed_p,item_qm)
    Object top_of_stack, role_constant, no_name_allowed_p, item_qm;
{
    Object name_or_names, name_qm;

    x_note_fn_call(149,237);
    if (item_qm) {
	name_or_names = get_lookup_slot_value_given_default(item_qm,
		Qname_or_names_for_frame,Nil);
	name_qm = CONSP(name_or_names) ? M_CAR(name_or_names) : name_or_names;
    }
    else
	name_qm = Nil;
    if ( !(name_qm || no_name_allowed_p))
	raw_stack_error_named_error(top_of_stack,
		name_of_item_invalid_reference_message(role_constant,item_qm));
    GENSYM_RETURN_ONE(name_qm);
    return VALUES_1(Nil);
}

static Object string_constant_75;  /* " that is ~(~a~)" */

/* ROLE-PRINT-RELATED-TO-ITEM */
Object role_print_related_to_item(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,238);
    print_user_or_datum_type(THIRD(role));
    if (local_variable_qm)
	tformat(2,string_constant_41,local_variable_qm);
    GENSYM_RETURN_ONE(tformat(2,string_constant_75,SECOND(role)));
    return VALUES_1(Nil);
}

static Object list_constant_1;     /* # */

static Object string_constant_76;  /* " ~NF.  Note that this relation exists between ~NF and ~
				    *                          more than one other item."
				    */

/* SERVE-UNIQUE-RELATED-TO-ITEM-VALUE */
Object serve_unique_related_to_item_value(top_of_stack,role_constant,
	    no_item_allowed_p,item_qm)
    Object top_of_stack, role_constant, no_item_allowed_p, item_qm;
{
    Object relation_name, relation_qm, class_name, class_description_qm;
    Object unique_test_not_needed_qm, related_item_qm, gensymed_symbol;
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, unfiltered_related_items, scope_conses;
    Object ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_binary_tree_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, item_2, ab_less_than_branch_qm_;
    Object sub_class_bit_vector, top_of_stack_1, text_string, snapshots;
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object message_1, role, domain_1_qm, domain_2_qm;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char filter_of_items_not_needed_qm, temp_2;
    Declare_special(8);
    Object result;

    x_note_fn_call(149,239);
    relation_name = M_CAR(M_CDR(role_constant));
    relation_qm = get_instance_with_name_if_any(Qrelation,relation_name);
    class_name = M_CAR(M_CDR(M_CDR(role_constant)));
    class_description_qm = 
	    lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop);
    unique_test_not_needed_qm = relation_qm ? 
	    memq_function(ISVREF(relation_qm,(SI_Long)24L),
	    list_constant_1) : Nil;
    filter_of_items_not_needed_qm = EQ(class_name,Qitem);
    related_item_qm = Nil;
    if ( !TRUEP(item_qm))
	related_item_qm = Nil;
    else if ( !TRUEP(class_description_qm) ||  
	    !TRUEP(ISVREF(class_description_qm,(SI_Long)16L)))
	related_item_qm = Nil;
    else if (unique_test_not_needed_qm) {
	gensymed_symbol = item_qm;
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)12L);
	if (gensymed_symbol) {
	    skip_list = CDR(gensymed_symbol);
	    key_value = relation_name;
	    key_hash_value = SXHASH_SYMBOL_1(relation_name) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)7L;
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
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    unfiltered_related_items = gensymed_symbol ? 
		    ISVREF(gensymed_symbol,(SI_Long)2L) : Nil;
	}
	else
	    unfiltered_related_items = Nil;
	if (unfiltered_related_items) {
	    scope_conses = Scope_conses;
	    ab_node_stack_ = Nil;
	    ab_current_node_ = Nil;
	    ab_skip_list_form_ = unfiltered_related_items;
	    ab_binary_tree_form_ = unfiltered_related_items;
	    gensymed_symbol = CDR(unfiltered_related_items);
	    if (CONSP(gensymed_symbol)) {
		temp_1 = M_CAR(gensymed_symbol);
		temp_2 = SIMPLE_VECTOR_P(temp_1);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		temp_1 = M_CDR(gensymed_symbol);
		ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
	    }
	    else
		ab_skip_list_p_ = Nil;
	    ab_next_node_ = Nil;
	    ab_tail_node_ = Nil;
	    ab_current_alist_ = Nil;
	    ab_entry_cons_ = Nil;
	    item_2 = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
	      if (ab_skip_list_p_) {
		  ab_next_node_ = 
			  ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
			  (SI_Long)0L),(SI_Long)0L));
		  ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
		  if (EQ(ab_next_node_,ab_tail_node_))
		      ab_next_node_ = Nil;
	      }
	      else
		  ab_next_node_ = M_CDR(ab_binary_tree_form_);
	    next_loop_3:
	      if (ab_current_alist_) {
		  ab_entry_cons_ = M_CAR(ab_current_alist_);
		  ab_current_alist_ = M_CDR(ab_current_alist_);
	      }
	      else if (ab_skip_list_p_) {
		  if (ab_next_node_) {
		      ab_current_node_ = ab_next_node_;
		      ab_next_node_ = 
			      ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node_,
			      (SI_Long)0L),(SI_Long)0L));
		      if (EQ(ab_next_node_,ab_tail_node_))
			  ab_next_node_ = Nil;
		      ab_entry_cons_ = scope_cons(ISVREF(ab_current_node_,
			      (SI_Long)2L),ISVREF(ab_current_node_,
			      (SI_Long)3L));
		  }
		  else
		      ab_current_node_ = Nil;
	      }
	      else {
		  if (ab_next_node_) {
		      ab_current_node_ = ab_next_node_;
		      ab_less_than_branch_qm_ = Nil;
		    next_loop_4:
		      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			      (SI_Long)1L);
		      if ( !TRUEP(ab_less_than_branch_qm_))
			  goto end_loop_3;
		      ab_node_stack_ = scope_cons(ab_current_node_,
			      ab_node_stack_);
		      ab_current_node_ = ab_less_than_branch_qm_;
		      goto next_loop_4;
		    end_loop_3:;
		  }
		  else if (ab_node_stack_) {
		      ab_next_node_ = ab_node_stack_;
		      ab_current_node_ = M_CAR(ab_node_stack_);
		      ab_node_stack_ = M_CDR(ab_node_stack_);
		  }
		  else
		      ab_current_node_ = Nil;
		  if (ab_current_node_) {
		      ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
		      ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
		      ab_entry_cons_ = M_CAR(ab_current_alist_);
		      ab_current_alist_ = M_CDR(ab_current_alist_);
		  }
	      }
	      if ( !TRUEP(ab_current_node_))
		  goto end_loop_4;
	      item_2 = M_CDR(ab_entry_cons_);
	      if (item_2 && serve_item_p(item_2)) {
		  temp_2 = filter_of_items_not_needed_qm;
		  if (temp_2);
		  else {
		      gensymed_symbol = ISVREF(item_2,(SI_Long)1L);
		      sub_class_bit_vector = ISVREF(gensymed_symbol,
			      (SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(class_description_qm,(SI_Long)18L));
		      sub_class_vector_index = superior_class_bit_number 
			      >>  -  - (SI_Long)3L;
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
			  temp_2 = (SI_Long)0L < gensymed_symbol_1;
		      }
		      else
			  temp_2 = TRUEP(Nil);
		  }
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      if (temp_2) {
		  related_item_qm = item_2;
		  goto end_2;
	      }
	      goto next_loop_3;
	    end_loop_4:
	    end_2:;
	    POP_SPECIAL();
	}
    }
    else {
	gensymed_symbol = item_qm;
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)12L);
	if (gensymed_symbol) {
	    skip_list = CDR(gensymed_symbol);
	    key_value = relation_name;
	    key_hash_value = SXHASH_SYMBOL_1(relation_name) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)7L;
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
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_3;
	    goto next_loop_6;
	  end_loop_7:
	  end_3:
	    level = level - (SI_Long)1L;
	    goto next_loop_5;
	  end_loop_5:;
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    unfiltered_related_items = gensymed_symbol ? 
		    ISVREF(gensymed_symbol,(SI_Long)2L) : Nil;
	}
	else
	    unfiltered_related_items = Nil;
	if (unfiltered_related_items) {
	    scope_conses = Scope_conses;
	    ab_node_stack_ = Nil;
	    ab_current_node_ = Nil;
	    ab_skip_list_form_ = unfiltered_related_items;
	    ab_binary_tree_form_ = unfiltered_related_items;
	    gensymed_symbol = CDR(unfiltered_related_items);
	    if (CONSP(gensymed_symbol)) {
		temp_1 = M_CAR(gensymed_symbol);
		temp_2 = SIMPLE_VECTOR_P(temp_1);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		temp_1 = M_CDR(gensymed_symbol);
		ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
	    }
	    else
		ab_skip_list_p_ = Nil;
	    ab_next_node_ = Nil;
	    ab_tail_node_ = Nil;
	    ab_current_alist_ = Nil;
	    ab_entry_cons_ = Nil;
	    item_2 = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    7);
	      if (ab_skip_list_p_) {
		  ab_next_node_ = 
			  ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
			  (SI_Long)0L),(SI_Long)0L));
		  ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
		  if (EQ(ab_next_node_,ab_tail_node_))
		      ab_next_node_ = Nil;
	      }
	      else
		  ab_next_node_ = M_CDR(ab_binary_tree_form_);
	    next_loop_8:
	      if (ab_current_alist_) {
		  ab_entry_cons_ = M_CAR(ab_current_alist_);
		  ab_current_alist_ = M_CDR(ab_current_alist_);
	      }
	      else if (ab_skip_list_p_) {
		  if (ab_next_node_) {
		      ab_current_node_ = ab_next_node_;
		      ab_next_node_ = 
			      ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node_,
			      (SI_Long)0L),(SI_Long)0L));
		      if (EQ(ab_next_node_,ab_tail_node_))
			  ab_next_node_ = Nil;
		      ab_entry_cons_ = scope_cons(ISVREF(ab_current_node_,
			      (SI_Long)2L),ISVREF(ab_current_node_,
			      (SI_Long)3L));
		  }
		  else
		      ab_current_node_ = Nil;
	      }
	      else {
		  if (ab_next_node_) {
		      ab_current_node_ = ab_next_node_;
		      ab_less_than_branch_qm_ = Nil;
		    next_loop_9:
		      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			      (SI_Long)1L);
		      if ( !TRUEP(ab_less_than_branch_qm_))
			  goto end_loop_8;
		      ab_node_stack_ = scope_cons(ab_current_node_,
			      ab_node_stack_);
		      ab_current_node_ = ab_less_than_branch_qm_;
		      goto next_loop_9;
		    end_loop_8:;
		  }
		  else if (ab_node_stack_) {
		      ab_next_node_ = ab_node_stack_;
		      ab_current_node_ = M_CAR(ab_node_stack_);
		      ab_node_stack_ = M_CDR(ab_node_stack_);
		  }
		  else
		      ab_current_node_ = Nil;
		  if (ab_current_node_) {
		      ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
		      ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
		      ab_entry_cons_ = M_CAR(ab_current_alist_);
		      ab_current_alist_ = M_CDR(ab_current_alist_);
		  }
	      }
	      if ( !TRUEP(ab_current_node_))
		  goto end_loop_9;
	      item_2 = M_CDR(ab_entry_cons_);
	      if (serve_item_p(item_2)) {
		  temp_2 = filter_of_items_not_needed_qm;
		  if (temp_2);
		  else {
		      gensymed_symbol = ISVREF(item_2,(SI_Long)1L);
		      sub_class_bit_vector = ISVREF(gensymed_symbol,
			      (SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(class_description_qm,(SI_Long)18L));
		      sub_class_vector_index = superior_class_bit_number 
			      >>  -  - (SI_Long)3L;
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
			  temp_2 = (SI_Long)0L < gensymed_symbol_1;
		      }
		      else
			  temp_2 = TRUEP(Nil);
		  }
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      if (temp_2) {
		  if ( !TRUEP(related_item_qm))
		      related_item_qm = item_2;
		  else if (no_item_allowed_p) {
		      related_item_qm = Nil;
		      goto end_4;
		  }
		  else {
		      top_of_stack_1 = top_of_stack;
		      text_string = Nil;
		      snapshots = Nil;
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
				    twrite_beginning_of_wide_string(array_constant_11,
					    FIX((SI_Long)37L));
				    print_role(role_constant);
				    tformat(3,string_constant_76,item_qm,
					    item_qm);
				    text_string = 
					    copy_out_current_wide_string();
				  POP_SPECIAL();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			  snapshots = Snapshots_of_related_blocks;
			  Snapshots_of_related_blocks = Nil;
			  if (Snapshots_of_related_blocks) {
			      reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
			      Snapshots_of_related_blocks = Nil;
			  }
			POP_SPECIAL();
		      POP_SPECIAL();
		      message_1 = make_error_text(text_string,snapshots);
		      raw_stack_error_named_error(top_of_stack_1,message_1);
		  }
	      }
	      goto next_loop_8;
	    end_loop_9:
	    end_4:;
	    POP_SPECIAL();
	}
    }
    if ( !(related_item_qm || no_item_allowed_p)) {
	top_of_stack = FIXNUM_SUB1(top_of_stack);
	role = role_constant;
	domain_1_qm = item_qm;
	domain_2_qm = Nil;
	raw_stack_error_named_error(top_of_stack,
		role_returned_no_values_error_1(role,domain_1_qm,domain_2_qm));
    }
    GENSYM_RETURN_ONE(related_item_qm);
    return VALUES_1(Nil);
}

static Object string_constant_77;  /* "The ~a ~NF contains no element at index ~a." */

/* NO-ELEMENT-FOR-ARRAY-ROLE-INDEX-ERROR-MESSAGE */
Object no_element_for_array_role_index_error_message(array_type_string,
	    array,index_1)
    Object array_type_string, array, index_1;
{
    x_note_fn_call(149,240);
    return tformat_stack_error_text_string(4,string_constant_77,
	    array_type_string,array,index_1);
}

static Object string_constant_78;  /* "nth element of integer-array" */

/* ROLE-PRINT-NTH-ELEMENT-OF-INTEGER-ARRAY */
Object role_print_nth_element_of_integer_array(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,241);
    GENSYM_RETURN_ONE(tformat(1,string_constant_78));
    return VALUES_1(Nil);
}

/* ROLE-AND-DESIGNATION-PRINT-NTH-ELEMENT-OF-INTEGER-ARRAY */
Object role_and_designation_print_nth_element_of_integer_array varargs_1(int, n)
{
    Object role;
    Object domain_1_qm, domain_2_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(149,242);
    INIT_ARGS_nonrelocating();
    role = REQUIRED_ARG_nonrelocating();
    domain_1_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    domain_2_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (CONSP(domain_1_qm)) {
	twrite_wide_character(FIX((SI_Long)40L));
	print_designation(domain_1_qm);
	twrite_wide_character(FIX((SI_Long)41L));
    }
    else
	print_designation(domain_1_qm);
    twrite_wide_character(FIX((SI_Long)91L));
    write_expression(domain_2_qm);
    return twrite_wide_character(FIX((SI_Long)93L));
}

static Object string_constant_79;  /* "integer array" */

/* SERVE-UNIQUE-NTH-ELEMENT-OF-INTEGER-ARRAY-VALUE */
Object serve_unique_nth_element_of_integer_array_value(top_of_stack,
	    role_constant,no_item_allowed_p,array,index_1)
    Object top_of_stack, role_constant, no_item_allowed_p, array, index_1;
{
    Object length_1, integer_value_qm, managed_array;

    x_note_fn_call(149,243);
    length_1 = ISVREF(array,(SI_Long)20L);
    integer_value_qm = Nil;
    if (IFIX(index_1) < (SI_Long)0L || FIXNUM_GE(index_1,length_1)) {
	raw_stack_error_named_error(top_of_stack,
		bad_g2_array_index_error_1(array,index_1));
	integer_value_qm = Nil;
    }
    else {
	managed_array = ISVREF(array,(SI_Long)23L);
	integer_value_qm = FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(managed_array,
		IFIX(FIXNUM_ADD(index_1,Managed_array_index_offset))) : 
		ISVREF(ISVREF(managed_array,(IFIX(index_1) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),IFIX(index_1) & (SI_Long)1023L);
    }
    if ( !TRUEP(integer_value_qm))
	raw_stack_error_named_error(top_of_stack,
		no_element_for_array_role_index_error_message(string_constant_79,
		array,index_1));
    GENSYM_RETURN_ONE(integer_value_qm);
    return VALUES_1(Nil);
}

static Object string_constant_80;  /* "nth element of float-array" */

/* ROLE-PRINT-NTH-ELEMENT-OF-FLOAT-ARRAY */
Object role_print_nth_element_of_float_array(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,244);
    GENSYM_RETURN_ONE(tformat(1,string_constant_80));
    return VALUES_1(Nil);
}

/* ROLE-AND-DESIGNATION-PRINT-NTH-ELEMENT-OF-FLOAT-ARRAY */
Object role_and_designation_print_nth_element_of_float_array varargs_1(int, n)
{
    Object role;
    Object domain_1_qm, domain_2_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(149,245);
    INIT_ARGS_nonrelocating();
    role = REQUIRED_ARG_nonrelocating();
    domain_1_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    domain_2_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (CONSP(domain_1_qm)) {
	twrite_wide_character(FIX((SI_Long)40L));
	print_designation(domain_1_qm);
	twrite_wide_character(FIX((SI_Long)41L));
    }
    else
	print_designation(domain_1_qm);
    twrite_wide_character(FIX((SI_Long)91L));
    write_expression(domain_2_qm);
    return twrite_wide_character(FIX((SI_Long)93L));
}

/* SERVE-UNIQUE-NTH-ELEMENT-OF-FLOAT-ARRAY-VALUE */
Object serve_unique_nth_element_of_float_array_value(top_of_stack,
	    role_constant,no_item_allowed_p,array,index_1)
    Object top_of_stack, role_constant, no_item_allowed_p, array, index_1;
{
    Object length_1, float_value_qm, amf_available_array_cons_qm, amf_array;
    Object temp, temp_1, amf_result, new_float;
    double aref_new_value;

    x_note_fn_call(149,246);
    length_1 = ISVREF(array,(SI_Long)20L);
    float_value_qm = Nil;
    if (IFIX(index_1) < (SI_Long)0L || FIXNUM_GE(index_1,length_1)) {
	raw_stack_error_named_error(top_of_stack,
		bad_g2_array_index_error_1(array,index_1));
	float_value_qm = Nil;
    }
    else {
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
	aref_new_value = DFLOAT_ISAREF_1(ISVREF(ISVREF(array,(SI_Long)23L),
		(IFIX(index_1) >>  -  - (SI_Long)10L) + (SI_Long)2L),
		IFIX(index_1) & (SI_Long)1023L);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	float_value_qm = new_float;
    }
    GENSYM_RETURN_ONE(float_value_qm);
    return VALUES_1(Nil);
}

static Object string_constant_81;  /* "nth element of value-array" */

/* ROLE-PRINT-NTH-ELEMENT-OF-VALUE-ARRAY */
Object role_print_nth_element_of_value_array(role,local_variable_qm)
    Object role, local_variable_qm;
{
    x_note_fn_call(149,247);
    GENSYM_RETURN_ONE(tformat(1,string_constant_81));
    return VALUES_1(Nil);
}

/* ROLE-AND-DESIGNATION-PRINT-NTH-ELEMENT-OF-VALUE-ARRAY */
Object role_and_designation_print_nth_element_of_value_array varargs_1(int, n)
{
    Object role;
    Object domain_1_qm, domain_2_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(149,248);
    INIT_ARGS_nonrelocating();
    role = REQUIRED_ARG_nonrelocating();
    domain_1_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    domain_2_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (CONSP(domain_1_qm)) {
	twrite_wide_character(FIX((SI_Long)40L));
	print_designation(domain_1_qm);
	twrite_wide_character(FIX((SI_Long)41L));
    }
    else
	print_designation(domain_1_qm);
    twrite_wide_character(FIX((SI_Long)91L));
    write_expression(domain_2_qm);
    return twrite_wide_character(FIX((SI_Long)93L));
}

static Object string_constant_82;  /* "value array" */

/* SERVE-UNIQUE-NTH-ELEMENT-OF-VALUE-ARRAY-VALUE */
Object serve_unique_nth_element_of_value_array_value(top_of_stack,
	    role_constant,no_item_allowed_p,array,index_1)
    Object top_of_stack, role_constant, no_item_allowed_p, array, index_1;
{
    Object temp, length_1, value_qm, amf_available_array_cons_qm, amf_array;
    Object temp_1, temp_2, amf_result, new_float;
    char float_array_qm;
    double aref_new_value;

    x_note_fn_call(149,249);
    if ( !TRUEP(ISVREF(array,(SI_Long)23L)))
	temp = Nil;
    else {
	length_1 = ISVREF(array,(SI_Long)20L);
	float_array_qm = EQ(ISVREF(array,(SI_Long)21L),Qfloat);
	value_qm = Nil;
	if (IFIX(index_1) < (SI_Long)0L || FIXNUM_GE(index_1,length_1)) {
	    raw_stack_error_named_error(top_of_stack,
		    bad_g2_array_index_error_1(array,index_1));
	    value_qm = Nil;
	}
	else if (float_array_qm) {
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
	    aref_new_value = DFLOAT_ISAREF_1(ISVREF(ISVREF(array,
		    (SI_Long)23L),(IFIX(index_1) >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L),IFIX(index_1) & (SI_Long)1023L);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    value_qm = new_float;
	}
	else {
	    value_qm = FIXNUM_LE(ISVREF(ISVREF(array,(SI_Long)23L),
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(ISVREF(array,(SI_Long)23L),
		    IFIX(FIXNUM_ADD(index_1,Managed_array_index_offset))) :
		     ISVREF(ISVREF(ISVREF(array,(SI_Long)23L),
		    (IFIX(index_1) >>  -  - (SI_Long)10L) + (SI_Long)2L),
		    IFIX(index_1) & (SI_Long)1023L);
	    if (value_qm) {
		if (EQ(ISVREF(array,(SI_Long)21L),Qtruth_value)) {
		    if (FIXNUM_EQ(value_qm,Truth))
			value_qm = Evaluation_true_value;
		    else if (FIXNUM_EQ(value_qm,Falsity))
			value_qm = Evaluation_false_value;
		    else
			value_qm = eval_cons_1(value_qm,Qtruth_value);
		}
		else
		    value_qm = FIXNUMP(value_qm) || value_qm && 
			    SYMBOLP(value_qm) ? value_qm : 
			    copy_evaluation_value_1(value_qm);
	    }
	}
	if ( !TRUEP(value_qm))
	    raw_stack_error_named_error(top_of_stack,
		    no_element_for_array_role_index_error_message(string_constant_82,
		    array,index_1));
	temp = value_qm;
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

void roles_INIT()
{
    Object role_print_name_1, serve_first_name_1, role_print_named_by_1;
    Object serve_first_named_by_1, role_print_named_by_debugging_name_1;
    Object serve_first_named_by_debugging_name_1, role_print_nearest_1;
    Object serve_first_nearest_1, serve_first_icon_color_1;
    Object role_print_item_color_1, serve_first_item_color_1;
    Object role_print_item_x_position_1, serve_first_item_x_position_1;
    Object role_print_item_y_position_1, serve_first_item_y_position_1;
    Object role_print_icon_heading_1, serve_first_icon_heading_1;
    Object role_print_item_width_1, serve_first_item_width_1;
    Object role_print_item_height_1, serve_first_item_height_1;
    Object role_print_system_attribute_1, serve_first_system_attribute_1;
    Object role_print_system_attribute_as_text_1;
    Object serve_first_system_attribute_as_text_1;
    Object role_print_text_of_attribute_1, serve_first_text_of_attribute_1;
    Object role_print_connected_to_1, serve_first_connected_to_1;
    Object serve_first_connected_to_inverse_1, role_print_at_port_1;
    Object serve_first_at_port_1, serve_first_at_port_inverse_1;
    Object role_print_at_an_input_1, serve_first_at_an_input_1;
    Object serve_first_at_an_input_inverse_1, role_print_at_an_output_1;
    Object serve_first_at_an_output_1, serve_first_at_an_output_inverse_1;
    Object role_print_at_input_end_1, serve_first_at_input_end_1;
    Object role_print_at_output_end_1, serve_first_at_output_end_1;
    Object role_print_at_either_end_1, serve_first_at_either_end_1;
    Object serve_first_at_input_end_inverse_1;
    Object serve_first_at_output_end_inverse_1;
    Object serve_first_at_either_end_inverse_1, role_print_subworkspace_1;
    Object serve_first_subworkspace_1, serve_first_subworkspace_inverse_1;
    Object role_print_superior_item_1, serve_first_superior_item_1;
    Object serve_first_superior_item_inverse_1;
    Object role_print_attribute_of_class_1, serve_first_attribute_of_class_1;
    Object serve_first_attribute_of_class_inverse_1;
    Object role_print_user_attribute_names_1;
    Object serve_first_user_attribute_names_1, role_print_attribute_names_1;
    Object serve_first_attribute_names_1, role_print_attribute_value_1;
    Object serve_first_attribute_value_1, role_print_class_qualified_name_1;
    Object serve_first_class_qualified_name_1;
    Object serve_first_class_qualified_name_inverse_1, role_print_workspace_1;
    Object serve_first_workspace_1, serve_first_workspace_inverse_1;
    Object role_print_upon_1, serve_first_upon_1, serve_first_upon_inverse_1;
    Object role_print_this_workspace_1, serve_first_this_workspace_1;
    Object serve_first_this_workspace_inverse_1, role_print_this_window_1;
    Object serve_first_this_window_1, role_print_superior_class_1;
    Object serve_first_superior_class_1, role_print_inferior_class_1;
    Object serve_first_inferior_class_1, role_print_class_instances_named_by_1;
    Object serve_first_class_instances_named_by_1, role_print_this_rule_1;
    Object serve_first_this_rule_1, serve_first_this_rule_inverse_1;
    Object role_print_this_procedure_1, serve_first_this_procedure_1;
    Object role_print_this_procedure_invocation_1;
    Object serve_first_this_procedure_invocation_1, role_print_related_1;
    Object serve_first_related_1, serve_first_related_inverse_1;
    Object role_print_first_of_list_1, serve_first_first_of_list_1;
    Object serve_first_first_of_list_inverse_1, role_print_second_of_list_1;
    Object serve_first_second_of_list_1, serve_first_second_of_list_inverse_1;
    Object role_print_next_to_last_of_list_1;
    Object serve_first_next_to_last_of_list_1;
    Object serve_first_next_to_last_of_list_inverse_1;
    Object role_print_last_of_list_1, serve_first_last_of_list_1;
    Object serve_first_last_of_list_inverse_1, role_print_nth_element_1;
    Object serve_first_nth_element_1, role_print_element_iterator_1;
    Object serve_first_element_iterator_1;
    Object serve_first_element_iterator_inverse_1;
    Object role_print_member_iterator_1, serve_first_member_iterator_1;
    Object serve_first_member_iterator_inverse_1;
    Object role_print_indexed_attribute_1, serve_first_indexed_attribute_1;
    Object serve_first_attribute_frame_or_place_reference_1;
    Object serve_first_element_frame_or_place_reference_1;
    Object serve_first_class_qualified_name_frame_or_place_reference_1;
    Object role_print_class_qualified_method_1;
    Object serve_first_class_qualified_method_1;
    Object serve_first_next_procedure_method_1, role_print_named_by_symbol_1;
    Object unique_value_roles_new_value, serve_unique_named_by_symbol_value_1;
    Object role_print_name_of_item_1, serve_unique_name_of_item_value_1;
    Object role_print_related_to_item_1, serve_unique_related_to_item_value_1;
    Object role_print_nth_element_of_integer_array_1;
    Object serve_unique_nth_element_of_integer_array_value_1;
    Object role_print_nth_element_of_float_array_1;
    Object serve_unique_nth_element_of_float_array_value_1;
    Object role_print_nth_element_of_value_array_1;
    Object serve_unique_nth_element_of_value_array_value_1;
    Object Qunique_value_of_role_server_macro;
    Object Qserve_unique_nth_element_of_value_array_value_macro;
    Object Qnth_element_of_value_array, AB_package;
    Object Qunique_value_of_role_server_function;
    Object Qunique_value_of_role_next_role, Qnth_element;
    Object Qunique_value_of_role_server_domain_count;
    Object Qrole_and_designation_printer;
    Object Qrole_and_designation_print_nth_element_of_value_array;
    Object Qrole_server_printer;
    Object Qserve_unique_nth_element_of_float_array_value_macro;
    Object Qnth_element_of_float_array;
    Object Qrole_and_designation_print_nth_element_of_float_array;
    Object Qserve_unique_nth_element_of_integer_array_value_macro;
    Object Qnth_element_of_integer_array;
    Object Qrole_and_designation_print_nth_element_of_integer_array;
    Object Qserve_unique_related_to_item_value_macro, Qrelated_to_item;
    Object Qone_to_many, Qone_to_one, Qrelated;
    Object Qserve_unique_name_of_item_value_macro, Qname_of_item, Qname;
    Object Qserve_unique_named_by_symbol_value_macro, Qnamed_by_symbol;
    Object list_constant_4, Qnext_procedure_method, list_constant_7;
    Object list_constant_40, Qclass_qualified_method, Qab_method;
    Object Qclass_qualified_name_frame_or_place_reference, list_constant_39;
    Object list_constant_33, Qelement_frame_or_place_reference;
    Object list_constant_38, list_constant_37, list_constant_36;
    Object list_constant_35, list_constant_20, list_constant_24, Qab_or;
    Object list_constant_32, Qattribute_frame_or_place_reference;
    Object list_constant_34, list_constant_8, list_constant_6;
    Object Qplace_reference, Qindexed_attribute, list_constant_31;
    Object Qmember_iterator, Qelement_iterator, list_constant_30;
    Object list_constant_29, list_constant_28, list_constant_21;
    Object list_constant_27, list_constant_26, list_constant_25, Qg2_array;
    Object Qitem_or_value, Qrole_and_designation_print_nth_element;
    Object list_constant_23, list_constant_22, Qg2_list;
    Object Qrelated_role_predicate, Qthis_procedure_invocation;
    Object Qthis_procedure, Qclass_instances_named_by, Qinferior_class;
    Object Qsuperior_class, Qthis_window, Qupon, list_constant_19;
    Object list_constant_18, Qworkspace, Qattribute_value, list_constant_17;
    Object list_constant_16, list_constant_13;
    Object Qrole_and_designation_print_attribute_value, Qattribute_names;
    Object list_constant_15, Quser_attribute_names, Qattribute_of_class;
    Object list_constant_14, Qsuperior_item, Qroles, Qsubworkspace;
    Object Qat_either_end, Qat_output_end, Qat_input_end, Qat_an_output;
    Object Qat_an_input, Qat_port, list_constant_12, Qloose_end;
    Object list_constant_11, Qconnection_post, Qinvisible_entity;
    Object Qdefault_junction, Qtext_of_attribute, Qsystem_attribute_as_text;
    Object Qsystem_attribute, Qitem_height, Qitem_width, Qicon_heading;
    Object Qitem_y_position, Qitem_x_position, Qitem_color, Qborder_color;
    Object Qforeground_color, Qbackground_color, Qtext_color, Qstripe_color;
    Object Qicon_color, Qnearest, Qnamed_by_debugging_name, list_constant_10;
    Object list_constant_9, list_constant_5, Qslot_value_reclaimer;
    Object Qreclaim_role_cache_value, G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object string_constant_83, Qrole_cons_memory_usage;
    Object Qoutstanding_role_conses, list_constant_3;
    Object Qrole_cons_counter_vector, Qmake_thread_array, Kfuncall;
    Object list_constant_2, Qavailable_role_conses_tail_vector;
    Object Qavailable_role_conses_vector;

    x_note_fn_call(149,250);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qavailable_role_conses = STATIC_SYMBOL("AVAILABLE-ROLE-CONSES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_role_conses,Available_role_conses);
    Qroles = STATIC_SYMBOL("ROLES",AB_package);
    record_system_variable(Qavailable_role_conses,Qroles,Nil,Qnil,Qt,Qnil,
	    Qnil);
    Qavailable_role_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-ROLE-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_role_conses_tail,
	    Available_role_conses_tail);
    record_system_variable(Qavailable_role_conses_tail,Qroles,Nil,Qnil,Qt,
	    Qnil,Qnil);
    Qavailable_role_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-ROLE-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_role_conses_vector,
	    Available_role_conses_vector);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_thread_array = STATIC_SYMBOL("MAKE-THREAD-ARRAY",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    Qnil);
    record_system_variable(Qavailable_role_conses_vector,Qroles,
	    list_constant_2,Qnil,Qt,Qnil,Qnil);
    Qavailable_role_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-ROLE-CONSES-TAIL-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_role_conses_tail_vector,
	    Available_role_conses_tail_vector);
    record_system_variable(Qavailable_role_conses_tail_vector,Qroles,
	    list_constant_2,Qnil,Qt,Qnil,Qnil);
    Qrole_cons_counter_vector = STATIC_SYMBOL("ROLE-CONS-COUNTER-VECTOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qrole_cons_counter_vector,
	    Role_cons_counter_vector);
    list_constant_3 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    FIX((SI_Long)0L));
    record_system_variable(Qrole_cons_counter_vector,Qroles,
	    list_constant_3,Qnil,Qt,Qnil,Qnil);
    Qrole_cons_counter = STATIC_SYMBOL("ROLE-CONS-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qrole_cons_counter,Role_cons_counter);
    record_system_variable(Qrole_cons_counter,Qroles,FIX((SI_Long)0L),Qnil,
	    Qt,Qnil,Qnil);
    Qoutstanding_role_conses = STATIC_SYMBOL("OUTSTANDING-ROLE-CONSES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_role_conses,
	    STATIC_FUNCTION(outstanding_role_conses,NIL,FALSE,0,0));
    Qrole_cons_memory_usage = STATIC_SYMBOL("ROLE-CONS-MEMORY-USAGE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qrole_cons_memory_usage,
	    STATIC_FUNCTION(role_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_83 = STATIC_STRING("1q83-nBy9k83-nAy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_role_conses);
    push_optimized_constant(Qrole_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_83));
    Qrole = STATIC_SYMBOL("ROLE",AB_package);
    Qrole_server = STATIC_SYMBOL("ROLE-SERVER",AB_package);
    Role_server_prop = Qrole_server;
    Qdefined_type_of_role = STATIC_SYMBOL("DEFINED-TYPE-OF-ROLE",AB_package);
    Defined_type_of_role_prop = Qdefined_type_of_role;
    Qinverse_role_server = STATIC_SYMBOL("INVERSE-ROLE-SERVER",AB_package);
    Inverse_role_server_prop = Qinverse_role_server;
    Qrole_server_printer = STATIC_SYMBOL("ROLE-SERVER-PRINTER",AB_package);
    Role_server_printer_prop = Qrole_server_printer;
    Qrole_and_designation_printer = 
	    STATIC_SYMBOL("ROLE-AND-DESIGNATION-PRINTER",AB_package);
    Role_and_designation_printer_prop = Qrole_and_designation_printer;
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    Qiteration_state = STATIC_SYMBOL("ITERATION-STATE",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    array_constant_1 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    string_constant = STATIC_STRING(" ");
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qparent_frame = STATIC_SYMBOL("PARENT-FRAME",AB_package);
    Qparent_attribute_name = STATIC_SYMBOL("PARENT-ATTRIBUTE-NAME",AB_package);
    Qclass_qualified_name = STATIC_SYMBOL("CLASS-QUALIFIED-NAME",AB_package);
    Qnote_things_encountered_during_role_service_qm = 
	    STATIC_SYMBOL("NOTE-THINGS-ENCOUNTERED-DURING-ROLE-SERVICE\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qnote_things_encountered_during_role_service_qm,
	    Note_things_encountered_during_role_service_qm);
    record_system_variable(Qnote_things_encountered_during_role_service_qm,
	    Qroles,Nil,Qnil,Qnil,Qnil,Qnil);
    Qthings_that_affect_this_formula = 
	    STATIC_SYMBOL("THINGS-THAT-AFFECT-THIS-FORMULA",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qthings_that_affect_this_formula,
	    Things_that_affect_this_formula);
    record_system_variable(Qthings_that_affect_this_formula,Qroles,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qrole_predicate_function = STATIC_SYMBOL("ROLE-PREDICATE-FUNCTION",
	    AB_package);
    Role_predicate_function_prop = Qrole_predicate_function;
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qfirst_value_ok_for_the = STATIC_SYMBOL("FIRST-VALUE-OK-FOR-THE",
	    AB_package);
    First_value_ok_for_the_prop = Qfirst_value_ok_for_the;
    Qnamed_by = STATIC_SYMBOL("NAMED-BY",AB_package);
    Qg2_defstruct_structure_name_temporary_constant_g2_struct = 
	    STATIC_SYMBOL("TEMPORARY-CONSTANT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qrule = STATIC_SYMBOL("RULE",AB_package);
    Qthere_exists_p = STATIC_SYMBOL("THERE-EXISTS-P",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qthere_exists_p,There_exists_p);
    record_system_variable(Qthere_exists_p,Qroles,Nil,Qnil,Qnil,Qnil,Qnil);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Qrequired_domain_types_of_role = 
	    STATIC_SYMBOL("REQUIRED-DOMAIN-TYPES-OF-ROLE",AB_package);
    Qnever = STATIC_SYMBOL("NEVER",AB_package);
    Qdatum = STATIC_SYMBOL("DATUM",AB_package);
    Qvalue_request_pending = STATIC_SYMBOL("VALUE-REQUEST-PENDING",AB_package);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Qrecord_block_for_tformat = STATIC_SYMBOL("RECORD-BLOCK-FOR-TFORMAT",
	    AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    array_constant_2 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)10L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)11L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)16L,(SI_Long)39L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)22L,(SI_Long)17L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)23L,(SI_Long)57344L);
    string_constant_1 = 
	    STATIC_STRING("\', the argument ~NA was the wrong type of value.");
    Qvirtual_attribute = STATIC_SYMBOL("VIRTUAL-ATTRIBUTE",AB_package);
    Qattribute = STATIC_SYMBOL("ATTRIBUTE",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qserve_next_unreprocessed_frame = 
	    STATIC_SYMBOL("SERVE-NEXT-UNREPROCESSED-FRAME",AB_package);
    SET_SYMBOL_FUNCTION(Qserve_next_unreprocessed_frame,
	    STATIC_FUNCTION(serve_next_unreprocessed_frame,NIL,FALSE,2,2));
    Qserve_next_item_or_value = STATIC_SYMBOL("SERVE-NEXT-ITEM-OR-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qserve_next_item_or_value,
	    STATIC_FUNCTION(serve_next_item_or_value,NIL,FALSE,2,2));
    Qserve_next_unreprocessed_cached_frame = 
	    STATIC_SYMBOL("SERVE-NEXT-UNREPROCESSED-CACHED-FRAME",AB_package);
    SET_SYMBOL_FUNCTION(Qserve_next_unreprocessed_cached_frame,
	    STATIC_FUNCTION(serve_next_unreprocessed_cached_frame,NIL,
	    FALSE,2,2));
    Qrole_caching_enabled_qm = STATIC_SYMBOL("ROLE-CACHING-ENABLED\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qrole_caching_enabled_qm,
	    Role_caching_enabled_qm);
    record_system_variable(Qrole_caching_enabled_qm,Qroles,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qrole_cache = STATIC_SYMBOL("ROLE-CACHE",AB_package);
    Qthis_workspace = STATIC_SYMBOL("THIS-WORKSPACE",AB_package);
    Qkb_workspace = STATIC_SYMBOL("KB-WORKSPACE",AB_package);
    Qthis_rule = STATIC_SYMBOL("THIS-RULE",AB_package);
    Qreclaim_role_cache_value = STATIC_SYMBOL("RECLAIM-ROLE-CACHE-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_role_cache_value,
	    STATIC_FUNCTION(reclaim_role_cache_value,NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qrole_cache,
	    SYMBOL_FUNCTION(Qreclaim_role_cache_value),Qslot_value_reclaimer);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qconnected_to = STATIC_SYMBOL("CONNECTED-TO",AB_package);
    Qat_an_input = STATIC_SYMBOL("AT-AN-INPUT",AB_package);
    Qat_an_output = STATIC_SYMBOL("AT-AN-OUTPUT",AB_package);
    Qat_port = STATIC_SYMBOL("AT-PORT",AB_package);
    Qat_input_end = STATIC_SYMBOL("AT-INPUT-END",AB_package);
    Qat_output_end = STATIC_SYMBOL("AT-OUTPUT-END",AB_package);
    Qat_either_end = STATIC_SYMBOL("AT-EITHER-END",AB_package);
    list_constant_5 = STATIC_LIST((SI_Long)7L,Qconnected_to,Qat_an_input,
	    Qat_an_output,Qat_port,Qat_input_end,Qat_output_end,
	    Qat_either_end);
    if (List_of_connection_roles == UNBOUND)
	List_of_connection_roles = list_constant_5;
    Qinput = STATIC_SYMBOL("INPUT",AB_package);
    Qobject = STATIC_SYMBOL("OBJECT",AB_package);
    Qoutput = STATIC_SYMBOL("OUTPUT",AB_package);
    string_constant_2 = STATIC_STRING("Cannot evaluate `");
    string_constant_3 = 
	    STATIC_STRING("\' of something which cannot be found.");
    Qname = STATIC_SYMBOL("NAME",AB_package);
    mutate_global_property(Qname,T,Qfirst_value_ok_for_the);
    role_print_name_1 = STATIC_FUNCTION(role_print_name,NIL,FALSE,2,2);
    mutate_global_property(Qname,role_print_name_1,Qrole_server_printer);
    Qserve_next_name_of_entity = STATIC_SYMBOL("SERVE-NEXT-NAME-OF-ENTITY",
	    AB_package);
    serve_first_name_1 = STATIC_FUNCTION(serve_first_name,NIL,FALSE,2,2);
    mutate_global_property(Qname,serve_first_name_1,Qrole_server);
    mutate_global_property(Qname,Qsymbol,Qdefined_type_of_role);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Qab_class,Qitem);
    list_constant_7 = STATIC_CONS(list_constant_6,Qnil);
    mutate_global_property(Qname,list_constant_7,
	    Qrequired_domain_types_of_role);
    if ( !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qname),
	    Qinverse_role_server)))
	mutate_global_property(Qname,Nil,Qinverse_role_server);
    SET_SYMBOL_FUNCTION(Qserve_next_name_of_entity,
	    STATIC_FUNCTION(serve_next_name_of_entity,NIL,FALSE,2,2));
    mutate_global_property(Qnamed_by,T,Qfirst_value_ok_for_the);
    string_constant_4 = STATIC_STRING(" named by");
    role_print_named_by_1 = STATIC_FUNCTION(role_print_named_by,NIL,FALSE,2,2);
    mutate_global_property(Qnamed_by,role_print_named_by_1,
	    Qrole_server_printer);
    serve_first_named_by_1 = STATIC_FUNCTION(serve_first_named_by,NIL,
	    FALSE,2,2);
    mutate_global_property(Qnamed_by,serve_first_named_by_1,Qrole_server);
    list_constant_8 = STATIC_CONS(Qsymbol,Qnil);
    mutate_global_property(Qnamed_by,list_constant_8,
	    Qrequired_domain_types_of_role);
    if ( !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qnamed_by),
	    Qinverse_role_server)))
	mutate_global_property(Qnamed_by,Nil,Qinverse_role_server);
    string_constant_5 = 
	    STATIC_STRING("Attempting to get the ~a named by ~NC, which is not a symbol.");
    string_constant_6 = 
	    STATIC_STRING("Attempting to get the ~a named by ~a, which is ~\n\t\t     not a symbolic variable or parameter.");
    string_constant_7 = 
	    STATIC_STRING("Attempting to get the ~a named by ~a, which is not a ~\n              variable or parameter.");
    Qnamed_by_debugging_name = STATIC_SYMBOL("NAMED-BY-DEBUGGING-NAME",
	    AB_package);
    string_constant_8 = STATIC_STRING(" named by debugging name ");
    role_print_named_by_debugging_name_1 = 
	    STATIC_FUNCTION(role_print_named_by_debugging_name,NIL,FALSE,2,2);
    mutate_global_property(Qnamed_by_debugging_name,
	    role_print_named_by_debugging_name_1,Qrole_server_printer);
    serve_first_named_by_debugging_name_1 = 
	    STATIC_FUNCTION(serve_first_named_by_debugging_name,NIL,FALSE,2,2);
    mutate_global_property(Qnamed_by_debugging_name,
	    serve_first_named_by_debugging_name_1,Qrole_server);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    list_constant_9 = STATIC_LIST((SI_Long)3L,Qab_or,Qsymbol,Qtext);
    list_constant_10 = STATIC_CONS(list_constant_9,Qnil);
    mutate_global_property(Qnamed_by_debugging_name,list_constant_10,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qnamed_by_debugging_name),
	    Qinverse_role_server)))
	mutate_global_property(Qnamed_by_debugging_name,Nil,
		Qinverse_role_server);
    Qnearest = STATIC_SYMBOL("NEAREST",AB_package);
    string_constant_9 = STATIC_STRING(" nearest to");
    role_print_nearest_1 = STATIC_FUNCTION(role_print_nearest,NIL,FALSE,2,2);
    mutate_global_property(Qnearest,role_print_nearest_1,Qrole_server_printer);
    serve_first_nearest_1 = STATIC_FUNCTION(serve_first_nearest,NIL,FALSE,2,2);
    mutate_global_property(Qnearest,serve_first_nearest_1,Qrole_server);
    mutate_global_property(Qnearest,list_constant_7,
	    Qrequired_domain_types_of_role);
    if ( !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qnearest),
	    Qinverse_role_server)))
	mutate_global_property(Qnearest,Nil,Qinverse_role_server);
    Qicon_color = STATIC_SYMBOL("ICON-COLOR",AB_package);
    serve_first_icon_color_1 = STATIC_FUNCTION(serve_first_icon_color,NIL,
	    FALSE,2,2);
    mutate_global_property(Qicon_color,serve_first_icon_color_1,Qrole_server);
    mutate_global_property(Qicon_color,Qsymbol,Qdefined_type_of_role);
    mutate_global_property(Qicon_color,list_constant_7,
	    Qrequired_domain_types_of_role);
    if ( !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qicon_color),
	    Qinverse_role_server)))
	mutate_global_property(Qicon_color,Nil,Qinverse_role_server);
    Qitem_color = STATIC_SYMBOL("ITEM-COLOR",AB_package);
    SET_SYMBOL_FUNCTION(Qitem_color,STATIC_FUNCTION(item_color,NIL,FALSE,2,2));
    Qstripe_color = STATIC_SYMBOL("STRIPE-COLOR",AB_package);
    Qtext_color = STATIC_SYMBOL("TEXT-COLOR",AB_package);
    Qbackground_color = STATIC_SYMBOL("BACKGROUND-COLOR",AB_package);
    Qforeground_color = STATIC_SYMBOL("FOREGROUND-COLOR",AB_package);
    Qborder_color = STATIC_SYMBOL("BORDER-COLOR",AB_package);
    list_constant = STATIC_LIST((SI_Long)6L,Qicon_color,Qstripe_color,
	    Qtext_color,Qbackground_color,Qforeground_color,Qborder_color);
    string_constant_10 = STATIC_STRING(" of");
    string_constant_11 = STATIC_STRING(" icon-color of");
    role_print_item_color_1 = STATIC_FUNCTION(role_print_item_color,NIL,
	    FALSE,2,2);
    mutate_global_property(Qitem_color,role_print_item_color_1,
	    Qrole_server_printer);
    serve_first_item_color_1 = STATIC_FUNCTION(serve_first_item_color,NIL,
	    FALSE,2,2);
    mutate_global_property(Qitem_color,serve_first_item_color_1,Qrole_server);
    mutate_global_property(Qitem_color,Qsymbol,Qdefined_type_of_role);
    mutate_global_property(Qitem_color,list_constant_7,
	    Qrequired_domain_types_of_role);
    if ( !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qitem_color),
	    Qinverse_role_server)))
	mutate_global_property(Qitem_color,Nil,Qinverse_role_server);
    Qitem_x_position = STATIC_SYMBOL("ITEM-X-POSITION",AB_package);
    role_print_item_x_position_1 = 
	    STATIC_FUNCTION(role_print_item_x_position,NIL,FALSE,2,2);
    mutate_global_property(Qitem_x_position,role_print_item_x_position_1,
	    Qrole_server_printer);
    serve_first_item_x_position_1 = 
	    STATIC_FUNCTION(serve_first_item_x_position,NIL,FALSE,2,2);
    mutate_global_property(Qitem_x_position,serve_first_item_x_position_1,
	    Qrole_server);
    mutate_global_property(Qitem_x_position,Qinteger,Qdefined_type_of_role);
    mutate_global_property(Qitem_x_position,list_constant_7,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qitem_x_position),
	    Qinverse_role_server)))
	mutate_global_property(Qitem_x_position,Nil,Qinverse_role_server);
    Qitem_y_position = STATIC_SYMBOL("ITEM-Y-POSITION",AB_package);
    role_print_item_y_position_1 = 
	    STATIC_FUNCTION(role_print_item_y_position,NIL,FALSE,2,2);
    mutate_global_property(Qitem_y_position,role_print_item_y_position_1,
	    Qrole_server_printer);
    serve_first_item_y_position_1 = 
	    STATIC_FUNCTION(serve_first_item_y_position,NIL,FALSE,2,2);
    mutate_global_property(Qitem_y_position,serve_first_item_y_position_1,
	    Qrole_server);
    mutate_global_property(Qitem_y_position,Qinteger,Qdefined_type_of_role);
    mutate_global_property(Qitem_y_position,list_constant_7,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qitem_y_position),
	    Qinverse_role_server)))
	mutate_global_property(Qitem_y_position,Nil,Qinverse_role_server);
    Qicon_heading = STATIC_SYMBOL("ICON-HEADING",AB_package);
    role_print_icon_heading_1 = STATIC_FUNCTION(role_print_icon_heading,
	    NIL,FALSE,2,2);
    mutate_global_property(Qicon_heading,role_print_icon_heading_1,
	    Qrole_server_printer);
    serve_first_icon_heading_1 = STATIC_FUNCTION(serve_first_icon_heading,
	    NIL,FALSE,2,2);
    mutate_global_property(Qicon_heading,serve_first_icon_heading_1,
	    Qrole_server);
    mutate_global_property(Qicon_heading,Qnumber,Qdefined_type_of_role);
    mutate_global_property(Qicon_heading,list_constant_7,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qicon_heading),
	    Qinverse_role_server)))
	mutate_global_property(Qicon_heading,Nil,Qinverse_role_server);
    Qitem_width = STATIC_SYMBOL("ITEM-WIDTH",AB_package);
    role_print_item_width_1 = STATIC_FUNCTION(role_print_item_width,NIL,
	    FALSE,2,2);
    mutate_global_property(Qitem_width,role_print_item_width_1,
	    Qrole_server_printer);
    serve_first_item_width_1 = STATIC_FUNCTION(serve_first_item_width,NIL,
	    FALSE,2,2);
    mutate_global_property(Qitem_width,serve_first_item_width_1,Qrole_server);
    mutate_global_property(Qitem_width,Qinteger,Qdefined_type_of_role);
    mutate_global_property(Qitem_width,list_constant_7,
	    Qrequired_domain_types_of_role);
    if ( !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qitem_width),
	    Qinverse_role_server)))
	mutate_global_property(Qitem_width,Nil,Qinverse_role_server);
    Qitem_height = STATIC_SYMBOL("ITEM-HEIGHT",AB_package);
    role_print_item_height_1 = STATIC_FUNCTION(role_print_item_height,NIL,
	    FALSE,2,2);
    mutate_global_property(Qitem_height,role_print_item_height_1,
	    Qrole_server_printer);
    serve_first_item_height_1 = STATIC_FUNCTION(serve_first_item_height,
	    NIL,FALSE,2,2);
    mutate_global_property(Qitem_height,serve_first_item_height_1,
	    Qrole_server);
    mutate_global_property(Qitem_height,Qinteger,Qdefined_type_of_role);
    mutate_global_property(Qitem_height,list_constant_7,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qitem_height),
	    Qinverse_role_server)))
	mutate_global_property(Qitem_height,Nil,Qinverse_role_server);
    Qsystem_attribute = STATIC_SYMBOL("SYSTEM-ATTRIBUTE",AB_package);
    string_constant_12 = STATIC_STRING("~(~a of~)");
    role_print_system_attribute_1 = 
	    STATIC_FUNCTION(role_print_system_attribute,NIL,FALSE,2,2);
    mutate_global_property(Qsystem_attribute,role_print_system_attribute_1,
	    Qrole_server_printer);
    Qgsi_interface_name = STATIC_SYMBOL("GSI-INTERFACE-NAME",AB_package);
    Qgsi_interface_status = STATIC_SYMBOL("GSI-INTERFACE-STATUS",AB_package);
    Qinterface_status = STATIC_SYMBOL("INTERFACE-STATUS",AB_package);
    Qarray_length = STATIC_SYMBOL("ARRAY-LENGTH",AB_package);
    serve_first_system_attribute_1 = 
	    STATIC_FUNCTION(serve_first_system_attribute,NIL,FALSE,2,2);
    mutate_global_property(Qsystem_attribute,
	    serve_first_system_attribute_1,Qrole_server);
    Qitem_or_datum = STATIC_SYMBOL("ITEM-OR-DATUM",AB_package);
    mutate_global_property(Qsystem_attribute,Qitem_or_datum,
	    Qdefined_type_of_role);
    mutate_global_property(Qsystem_attribute,list_constant_7,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qsystem_attribute),
	    Qinverse_role_server)))
	mutate_global_property(Qsystem_attribute,Nil,Qinverse_role_server);
    Qsystem_attribute_as_text = STATIC_SYMBOL("SYSTEM-ATTRIBUTE-AS-TEXT",
	    AB_package);
    string_constant_13 = STATIC_STRING("text of the ~(~a of~)");
    role_print_system_attribute_as_text_1 = 
	    STATIC_FUNCTION(role_print_system_attribute_as_text,NIL,FALSE,2,2);
    mutate_global_property(Qsystem_attribute_as_text,
	    role_print_system_attribute_as_text_1,Qrole_server_printer);
    serve_first_system_attribute_as_text_1 = 
	    STATIC_FUNCTION(serve_first_system_attribute_as_text,NIL,FALSE,
	    2,2);
    mutate_global_property(Qsystem_attribute_as_text,
	    serve_first_system_attribute_as_text_1,Qrole_server);
    mutate_global_property(Qsystem_attribute_as_text,Qtext,
	    Qdefined_type_of_role);
    mutate_global_property(Qsystem_attribute_as_text,list_constant_7,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qsystem_attribute_as_text),
	    Qinverse_role_server)))
	mutate_global_property(Qsystem_attribute_as_text,Nil,
		Qinverse_role_server);
    Qtext_of_attribute = STATIC_SYMBOL("TEXT-OF-ATTRIBUTE",AB_package);
    array_constant_3 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)57344L);
    role_print_text_of_attribute_1 = 
	    STATIC_FUNCTION(role_print_text_of_attribute,NIL,FALSE,2,2);
    mutate_global_property(Qtext_of_attribute,
	    role_print_text_of_attribute_1,Qrole_server_printer);
    serve_first_text_of_attribute_1 = 
	    STATIC_FUNCTION(serve_first_text_of_attribute,NIL,FALSE,2,2);
    mutate_global_property(Qtext_of_attribute,
	    serve_first_text_of_attribute_1,Qrole_server);
    mutate_global_property(Qtext_of_attribute,Qtext,Qdefined_type_of_role);
    mutate_global_property(Qtext_of_attribute,list_constant_7,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtext_of_attribute),
	    Qinverse_role_server)))
	mutate_global_property(Qtext_of_attribute,Nil,Qinverse_role_server);
    Qformat_overrride = STATIC_SYMBOL("FORMAT-OVERRRIDE",AB_package);
    Qddd_dot_dddd_format = STATIC_SYMBOL("DDD.DDDD-FORMAT",AB_package);
    string_constant_14 = 
	    string_append2(STATIC_STRING("Cannot reference the text of the ~a of ~NF.  The text ~\n                       contains ~a characters.  The maximum number of ~\n                       characters allowed in te"),
	    STATIC_STRING("xt is ~a."));
    Qdefault_junction = STATIC_SYMBOL("DEFAULT-JUNCTION",AB_package);
    Qinvisible_entity = STATIC_SYMBOL("INVISIBLE-ENTITY",AB_package);
    Qconnection_post = STATIC_SYMBOL("CONNECTION-POST",AB_package);
    list_constant_11 = STATIC_LIST((SI_Long)3L,Qdefault_junction,
	    Qinvisible_entity,Qconnection_post);
    Transparent_classes_for_schematic_search = list_constant_11;
    Qloose_end = STATIC_SYMBOL("LOOSE-END",AB_package);
    list_constant_12 = STATIC_CONS(Qloose_end,Qnil);
    Classes_to_ignore_for_schematic_search = list_constant_12;
    Qconnections_in_connection_paths = 
	    STATIC_SYMBOL("CONNECTIONS-IN-CONNECTION-PATHS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qconnections_in_connection_paths,
	    Connections_in_connection_paths);
    record_system_variable(Qconnections_in_connection_paths,Qroles,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qcurrent_connection_path = STATIC_SYMBOL("CURRENT-CONNECTION-PATH",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_connection_path,
	    Current_connection_path);
    record_system_variable(Qcurrent_connection_path,Qroles,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qsuperior_connection_cache = STATIC_SYMBOL("SUPERIOR-CONNECTION-CACHE",
	    AB_package);
    Qreclaim_eval_cons_function = 
	    STATIC_SYMBOL("RECLAIM-EVAL-CONS-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_eval_cons_function,
	    STATIC_FUNCTION(reclaim_eval_cons_function,NIL,FALSE,1,1));
    if (Do_not_stop_search_once_found_qm == UNBOUND)
	Do_not_stop_search_once_found_qm = T;
    Qsave_path = STATIC_SYMBOL("SAVE-PATH",AB_package);
    Qinput_end_subworkspace_connection_posts = 
	    STATIC_SYMBOL("INPUT-END-SUBWORKSPACE-CONNECTION-POSTS",
	    AB_package);
    Qoutput_end_subworkspace_connection_posts = 
	    STATIC_SYMBOL("OUTPUT-END-SUBWORKSPACE-CONNECTION-POSTS",
	    AB_package);
    Qboth = STATIC_SYMBOL("BOTH",AB_package);
    Qport_names = STATIC_SYMBOL("PORT-NAMES",AB_package);
    string_constant_15 = STATIC_STRING(" connected to");
    role_print_connected_to_1 = STATIC_FUNCTION(role_print_connected_to,
	    NIL,FALSE,2,2);
    mutate_global_property(Qconnected_to,role_print_connected_to_1,
	    Qrole_server_printer);
    serve_first_connected_to_1 = STATIC_FUNCTION(serve_first_connected_to,
	    NIL,FALSE,2,2);
    mutate_global_property(Qconnected_to,serve_first_connected_to_1,
	    Qrole_server);
    mutate_global_property(Qconnected_to,list_constant_7,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qconnected_to),
	    Qinverse_role_server)))
	mutate_global_property(Qconnected_to,Nil,Qinverse_role_server);
    string_constant_16 = 
	    STATIC_STRING("In a reference to a ~a connected to ~nf, ~nf is not a ~a, so no connection ~\n     search could be performed.");
    string_constant_17 = STATIC_STRING("class that can have connections");
    string_constant_18 = STATIC_STRING("defined class");
    serve_first_connected_to_inverse_1 = 
	    STATIC_FUNCTION(serve_first_connected_to_inverse,NIL,FALSE,4,4);
    mutate_global_property(Qconnected_to,
	    serve_first_connected_to_inverse_1,Qinverse_role_server);
    array_constant_4 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)11L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)22L,(SI_Long)18L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)23L,(SI_Long)57344L);
    role_print_at_port_1 = STATIC_FUNCTION(role_print_at_port,NIL,FALSE,2,2);
    mutate_global_property(Qat_port,role_print_at_port_1,Qrole_server_printer);
    serve_first_at_port_1 = STATIC_FUNCTION(serve_first_at_port,NIL,FALSE,2,2);
    mutate_global_property(Qat_port,serve_first_at_port_1,Qrole_server);
    mutate_global_property(Qat_port,list_constant_7,
	    Qrequired_domain_types_of_role);
    if ( !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qat_port),
	    Qinverse_role_server)))
	mutate_global_property(Qat_port,Nil,Qinverse_role_server);
    serve_first_at_port_inverse_1 = 
	    STATIC_FUNCTION(serve_first_at_port_inverse,NIL,FALSE,4,4);
    mutate_global_property(Qat_port,serve_first_at_port_inverse_1,
	    Qinverse_role_server);
    string_constant_19 = STATIC_STRING(" connected at an input of");
    role_print_at_an_input_1 = STATIC_FUNCTION(role_print_at_an_input,NIL,
	    FALSE,2,2);
    mutate_global_property(Qat_an_input,role_print_at_an_input_1,
	    Qrole_server_printer);
    serve_first_at_an_input_1 = STATIC_FUNCTION(serve_first_at_an_input,
	    NIL,FALSE,2,2);
    mutate_global_property(Qat_an_input,serve_first_at_an_input_1,
	    Qrole_server);
    mutate_global_property(Qat_an_input,list_constant_7,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qat_an_input),
	    Qinverse_role_server)))
	mutate_global_property(Qat_an_input,Nil,Qinverse_role_server);
    Qdirectionality = STATIC_SYMBOL("DIRECTIONALITY",AB_package);
    serve_first_at_an_input_inverse_1 = 
	    STATIC_FUNCTION(serve_first_at_an_input_inverse,NIL,FALSE,4,4);
    mutate_global_property(Qat_an_input,serve_first_at_an_input_inverse_1,
	    Qinverse_role_server);
    string_constant_20 = STATIC_STRING(" connected at an output of");
    role_print_at_an_output_1 = STATIC_FUNCTION(role_print_at_an_output,
	    NIL,FALSE,2,2);
    mutate_global_property(Qat_an_output,role_print_at_an_output_1,
	    Qrole_server_printer);
    serve_first_at_an_output_1 = STATIC_FUNCTION(serve_first_at_an_output,
	    NIL,FALSE,2,2);
    mutate_global_property(Qat_an_output,serve_first_at_an_output_1,
	    Qrole_server);
    mutate_global_property(Qat_an_output,list_constant_7,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qat_an_output),
	    Qinverse_role_server)))
	mutate_global_property(Qat_an_output,Nil,Qinverse_role_server);
    serve_first_at_an_output_inverse_1 = 
	    STATIC_FUNCTION(serve_first_at_an_output_inverse,NIL,FALSE,4,4);
    mutate_global_property(Qat_an_output,
	    serve_first_at_an_output_inverse_1,Qinverse_role_server);
    string_constant_21 = STATIC_STRING(" at the input end of");
    role_print_at_input_end_1 = STATIC_FUNCTION(role_print_at_input_end,
	    NIL,FALSE,2,2);
    mutate_global_property(Qat_input_end,role_print_at_input_end_1,
	    Qrole_server_printer);
    serve_first_at_input_end_1 = STATIC_FUNCTION(serve_first_at_input_end,
	    NIL,FALSE,2,2);
    mutate_global_property(Qat_input_end,serve_first_at_input_end_1,
	    Qrole_server);
    mutate_global_property(Qat_input_end,list_constant_7,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qat_input_end),
	    Qinverse_role_server)))
	mutate_global_property(Qat_input_end,Nil,Qinverse_role_server);
    string_constant_22 = STATIC_STRING(" at the output end of");
    role_print_at_output_end_1 = STATIC_FUNCTION(role_print_at_output_end,
	    NIL,FALSE,2,2);
    mutate_global_property(Qat_output_end,role_print_at_output_end_1,
	    Qrole_server_printer);
    serve_first_at_output_end_1 = 
	    STATIC_FUNCTION(serve_first_at_output_end,NIL,FALSE,2,2);
    mutate_global_property(Qat_output_end,serve_first_at_output_end_1,
	    Qrole_server);
    mutate_global_property(Qat_output_end,list_constant_7,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qat_output_end),
	    Qinverse_role_server)))
	mutate_global_property(Qat_output_end,Nil,Qinverse_role_server);
    string_constant_23 = STATIC_STRING(" at either end of");
    role_print_at_either_end_1 = STATIC_FUNCTION(role_print_at_either_end,
	    NIL,FALSE,2,2);
    mutate_global_property(Qat_either_end,role_print_at_either_end_1,
	    Qrole_server_printer);
    serve_first_at_either_end_1 = 
	    STATIC_FUNCTION(serve_first_at_either_end,NIL,FALSE,2,2);
    mutate_global_property(Qat_either_end,serve_first_at_either_end_1,
	    Qrole_server);
    mutate_global_property(Qat_either_end,list_constant_7,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qat_either_end),
	    Qinverse_role_server)))
	mutate_global_property(Qat_either_end,Nil,Qinverse_role_server);
    serve_first_at_input_end_inverse_1 = 
	    STATIC_FUNCTION(serve_first_at_input_end_inverse,NIL,FALSE,4,4);
    mutate_global_property(Qat_input_end,
	    serve_first_at_input_end_inverse_1,Qinverse_role_server);
    serve_first_at_output_end_inverse_1 = 
	    STATIC_FUNCTION(serve_first_at_output_end_inverse,NIL,FALSE,4,4);
    mutate_global_property(Qat_output_end,
	    serve_first_at_output_end_inverse_1,Qinverse_role_server);
    serve_first_at_either_end_inverse_1 = 
	    STATIC_FUNCTION(serve_first_at_either_end_inverse,NIL,FALSE,4,4);
    mutate_global_property(Qat_either_end,
	    serve_first_at_either_end_inverse_1,Qinverse_role_server);
    Qsubworkspace = STATIC_SYMBOL("SUBWORKSPACE",AB_package);
    role_print_subworkspace_1 = STATIC_FUNCTION(role_print_subworkspace,
	    NIL,FALSE,2,2);
    mutate_global_property(Qsubworkspace,role_print_subworkspace_1,
	    Qrole_server_printer);
    serve_first_subworkspace_1 = STATIC_FUNCTION(serve_first_subworkspace,
	    NIL,FALSE,2,2);
    mutate_global_property(Qsubworkspace,serve_first_subworkspace_1,
	    Qrole_server);
    mutate_global_property(Qsubworkspace,list_constant_7,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qsubworkspace),
	    Qinverse_role_server)))
	mutate_global_property(Qsubworkspace,Nil,Qinverse_role_server);
    string_constant_24 = STATIC_STRING("~a is not a kb-workspace.");
    serve_first_subworkspace_inverse_1 = 
	    STATIC_FUNCTION(serve_first_subworkspace_inverse,NIL,FALSE,4,4);
    mutate_global_property(Qsubworkspace,
	    serve_first_subworkspace_inverse_1,Qinverse_role_server);
    Qsuperior_item = STATIC_SYMBOL("SUPERIOR-ITEM",AB_package);
    string_constant_25 = STATIC_STRING(" superior to");
    role_print_superior_item_1 = STATIC_FUNCTION(role_print_superior_item,
	    NIL,FALSE,2,2);
    mutate_global_property(Qsuperior_item,role_print_superior_item_1,
	    Qrole_server_printer);
    serve_first_superior_item_1 = 
	    STATIC_FUNCTION(serve_first_superior_item,NIL,FALSE,2,2);
    mutate_global_property(Qsuperior_item,serve_first_superior_item_1,
	    Qrole_server);
    mutate_global_property(Qsuperior_item,list_constant_7,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qsuperior_item),
	    Qinverse_role_server)))
	mutate_global_property(Qsuperior_item,Nil,Qinverse_role_server);
    Qattribute_items = STATIC_SYMBOL("ATTRIBUTE-ITEMS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qattribute_items,Attribute_items);
    record_system_variable(Qattribute_items,Qroles,Nil,Qnil,Qnil,Qnil,Qnil);
    Qadd_to_attribute_items = STATIC_SYMBOL("ADD-TO-ATTRIBUTE-ITEMS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qadd_to_attribute_items,
	    STATIC_FUNCTION(add_to_attribute_items,NIL,FALSE,1,1));
    serve_first_superior_item_inverse_1 = 
	    STATIC_FUNCTION(serve_first_superior_item_inverse,NIL,FALSE,4,4);
    mutate_global_property(Qsuperior_item,
	    serve_first_superior_item_inverse_1,Qinverse_role_server);
    Qattribute_of_class = STATIC_SYMBOL("ATTRIBUTE-OF-CLASS",AB_package);
    string_constant_26 = STATIC_STRING(" that is an attribute of");
    role_print_attribute_of_class_1 = 
	    STATIC_FUNCTION(role_print_attribute_of_class,NIL,FALSE,2,2);
    mutate_global_property(Qattribute_of_class,
	    role_print_attribute_of_class_1,Qrole_server_printer);
    serve_first_attribute_of_class_1 = 
	    STATIC_FUNCTION(serve_first_attribute_of_class,NIL,FALSE,2,2);
    mutate_global_property(Qattribute_of_class,
	    serve_first_attribute_of_class_1,Qrole_server);
    list_constant_13 = STATIC_CONS(Qab_structure,Qnil);
    list_constant_14 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,
	    list_constant_13,list_constant_7);
    list_constant_15 = STATIC_CONS(list_constant_14,Qnil);
    mutate_global_property(Qattribute_of_class,list_constant_15,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qattribute_of_class),
	    Qinverse_role_server)))
	mutate_global_property(Qattribute_of_class,Nil,Qinverse_role_server);
    serve_first_attribute_of_class_inverse_1 = 
	    STATIC_FUNCTION(serve_first_attribute_of_class_inverse,NIL,
	    FALSE,4,4);
    mutate_global_property(Qattribute_of_class,
	    serve_first_attribute_of_class_inverse_1,Qinverse_role_server);
    Quser_attribute_names = STATIC_SYMBOL("USER-ATTRIBUTE-NAMES",AB_package);
    string_constant_27 = 
	    STATIC_STRING(" that is a user-defined attribute name of");
    role_print_user_attribute_names_1 = 
	    STATIC_FUNCTION(role_print_user_attribute_names,NIL,FALSE,2,2);
    mutate_global_property(Quser_attribute_names,
	    role_print_user_attribute_names_1,Qrole_server_printer);
    Qserve_next_evaluation_value = 
	    STATIC_SYMBOL("SERVE-NEXT-EVALUATION-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qserve_next_evaluation_value,
	    STATIC_FUNCTION(serve_next_evaluation_value,NIL,FALSE,2,2));
    serve_first_user_attribute_names_1 = 
	    STATIC_FUNCTION(serve_first_user_attribute_names,NIL,FALSE,2,2);
    mutate_global_property(Quser_attribute_names,
	    serve_first_user_attribute_names_1,Qrole_server);
    mutate_global_property(Quser_attribute_names,Qsymbol,
	    Qdefined_type_of_role);
    mutate_global_property(Quser_attribute_names,list_constant_15,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Quser_attribute_names),
	    Qinverse_role_server)))
	mutate_global_property(Quser_attribute_names,Nil,Qinverse_role_server);
    Qattribute_names = STATIC_SYMBOL("ATTRIBUTE-NAMES",AB_package);
    string_constant_28 = STATIC_STRING(" that is an attribute name of");
    role_print_attribute_names_1 = 
	    STATIC_FUNCTION(role_print_attribute_names,NIL,FALSE,2,2);
    mutate_global_property(Qattribute_names,role_print_attribute_names_1,
	    Qrole_server_printer);
    serve_first_attribute_names_1 = 
	    STATIC_FUNCTION(serve_first_attribute_names,NIL,FALSE,2,2);
    mutate_global_property(Qattribute_names,serve_first_attribute_names_1,
	    Qrole_server);
    mutate_global_property(Qattribute_names,Qsymbol,Qdefined_type_of_role);
    mutate_global_property(Qattribute_names,list_constant_15,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qattribute_names),
	    Qinverse_role_server)))
	mutate_global_property(Qattribute_names,Nil,Qinverse_role_server);
    Qattribute_value = STATIC_SYMBOL("ATTRIBUTE-VALUE",AB_package);
    string_constant_29 = STATIC_STRING(" that is an attribute of the item");
    role_print_attribute_value_1 = 
	    STATIC_FUNCTION(role_print_attribute_value,NIL,FALSE,2,2);
    mutate_global_property(Qattribute_value,role_print_attribute_value_1,
	    Qrole_server_printer);
    string_constant_30 = 
	    STATIC_STRING(" that is an attribute of ~ND named by ~ND");
    Qrole_and_designation_print_attribute_value = 
	    STATIC_SYMBOL("ROLE-AND-DESIGNATION-PRINT-ATTRIBUTE-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qrole_and_designation_print_attribute_value,
	    STATIC_FUNCTION(role_and_designation_print_attribute_value,NIL,
	    TRUE,1,3));
    mutate_global_property(Qattribute_value,
	    SYMBOL_FUNCTION(Qrole_and_designation_print_attribute_value),
	    Qrole_and_designation_printer);
    serve_first_attribute_value_1 = 
	    STATIC_FUNCTION(serve_first_attribute_value,NIL,FALSE,3,3);
    mutate_global_property(Qattribute_value,serve_first_attribute_value_1,
	    Qrole_server);
    list_constant_16 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_6,
	    list_constant_13);
    list_constant_17 = STATIC_CONS(list_constant_16,list_constant_8);
    mutate_global_property(Qattribute_value,list_constant_17,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qattribute_value),
	    Qinverse_role_server)))
	mutate_global_property(Qattribute_value,Nil,Qinverse_role_server);
    array_constant_5 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)57344L);
    role_print_class_qualified_name_1 = 
	    STATIC_FUNCTION(role_print_class_qualified_name,NIL,FALSE,2,2);
    mutate_global_property(Qclass_qualified_name,
	    role_print_class_qualified_name_1,Qrole_server_printer);
    serve_first_class_qualified_name_1 = 
	    STATIC_FUNCTION(serve_first_class_qualified_name,NIL,FALSE,2,2);
    mutate_global_property(Qclass_qualified_name,
	    serve_first_class_qualified_name_1,Qrole_server);
    mutate_global_property(Qclass_qualified_name,Qitem_or_datum,
	    Qdefined_type_of_role);
    mutate_global_property(Qclass_qualified_name,list_constant_7,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qclass_qualified_name),
	    Qinverse_role_server)))
	mutate_global_property(Qclass_qualified_name,Nil,Qinverse_role_server);
    serve_first_class_qualified_name_inverse_1 = 
	    STATIC_FUNCTION(serve_first_class_qualified_name_inverse,NIL,
	    FALSE,4,4);
    mutate_global_property(Qclass_qualified_name,
	    serve_first_class_qualified_name_inverse_1,Qinverse_role_server);
    Qworkspace = STATIC_SYMBOL("WORKSPACE",AB_package);
    role_print_workspace_1 = STATIC_FUNCTION(role_print_workspace,NIL,
	    FALSE,2,2);
    mutate_global_property(Qworkspace,role_print_workspace_1,
	    Qrole_server_printer);
    serve_first_workspace_1 = STATIC_FUNCTION(serve_first_workspace,NIL,
	    FALSE,2,2);
    mutate_global_property(Qworkspace,serve_first_workspace_1,Qrole_server);
    mutate_global_property(Qworkspace,list_constant_7,
	    Qrequired_domain_types_of_role);
    if ( !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qworkspace),
	    Qinverse_role_server)))
	mutate_global_property(Qworkspace,Nil,Qinverse_role_server);
    serve_first_workspace_inverse_1 = 
	    STATIC_FUNCTION(serve_first_workspace_inverse,NIL,FALSE,4,4);
    mutate_global_property(Qworkspace,serve_first_workspace_inverse_1,
	    Qinverse_role_server);
    Qupon = STATIC_SYMBOL("UPON",AB_package);
    string_constant_31 = STATIC_STRING(" upon");
    role_print_upon_1 = STATIC_FUNCTION(role_print_upon,NIL,FALSE,2,2);
    mutate_global_property(Qupon,role_print_upon_1,Qrole_server_printer);
    serve_first_upon_1 = STATIC_FUNCTION(serve_first_upon,NIL,FALSE,2,2);
    mutate_global_property(Qupon,serve_first_upon_1,Qrole_server);
    list_constant_18 = STATIC_LIST((SI_Long)2L,Qab_class,Qkb_workspace);
    list_constant_19 = STATIC_CONS(list_constant_18,Qnil);
    mutate_global_property(Qupon,list_constant_19,
	    Qrequired_domain_types_of_role);
    if ( !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qupon),
	    Qinverse_role_server)))
	mutate_global_property(Qupon,Nil,Qinverse_role_server);
    serve_first_upon_inverse_1 = STATIC_FUNCTION(serve_first_upon_inverse,
	    NIL,FALSE,4,4);
    mutate_global_property(Qupon,serve_first_upon_inverse_1,
	    Qinverse_role_server);
    string_constant_32 = STATIC_STRING("this workspace");
    role_print_this_workspace_1 = 
	    STATIC_FUNCTION(role_print_this_workspace,NIL,FALSE,2,2);
    mutate_global_property(Qthis_workspace,role_print_this_workspace_1,
	    Qrole_server_printer);
    serve_first_this_workspace_1 = 
	    STATIC_FUNCTION(serve_first_this_workspace,NIL,FALSE,2,2);
    mutate_global_property(Qthis_workspace,serve_first_this_workspace_1,
	    Qrole_server);
    mutate_global_property(Qthis_workspace,Qnil,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qthis_workspace),
	    Qinverse_role_server)))
	mutate_global_property(Qthis_workspace,Nil,Qinverse_role_server);
    serve_first_this_workspace_inverse_1 = 
	    STATIC_FUNCTION(serve_first_this_workspace_inverse,NIL,FALSE,4,4);
    mutate_global_property(Qthis_workspace,
	    serve_first_this_workspace_inverse_1,Qinverse_role_server);
    Qthis_window = STATIC_SYMBOL("THIS-WINDOW",AB_package);
    string_constant_33 = STATIC_STRING("this window");
    role_print_this_window_1 = STATIC_FUNCTION(role_print_this_window,NIL,
	    FALSE,2,2);
    mutate_global_property(Qthis_window,role_print_this_window_1,
	    Qrole_server_printer);
    serve_first_this_window_1 = STATIC_FUNCTION(serve_first_this_window,
	    NIL,FALSE,2,2);
    mutate_global_property(Qthis_window,serve_first_this_window_1,
	    Qrole_server);
    mutate_global_property(Qthis_window,Qnil,Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qthis_window),
	    Qinverse_role_server)))
	mutate_global_property(Qthis_window,Nil,Qinverse_role_server);
    Qsuperior_class = STATIC_SYMBOL("SUPERIOR-CLASS",AB_package);
    mutate_global_property(Qsuperior_class,T,Qfirst_value_ok_for_the);
    string_constant_34 = STATIC_STRING(" that is a superior-class of");
    role_print_superior_class_1 = 
	    STATIC_FUNCTION(role_print_superior_class,NIL,FALSE,2,2);
    mutate_global_property(Qsuperior_class,role_print_superior_class_1,
	    Qrole_server_printer);
    serve_first_superior_class_1 = 
	    STATIC_FUNCTION(serve_first_superior_class,NIL,FALSE,2,2);
    mutate_global_property(Qsuperior_class,serve_first_superior_class_1,
	    Qrole_server);
    mutate_global_property(Qsuperior_class,Qsymbol,Qdefined_type_of_role);
    mutate_global_property(Qsuperior_class,list_constant_8,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qsuperior_class),
	    Qinverse_role_server)))
	mutate_global_property(Qsuperior_class,Nil,Qinverse_role_server);
    Qinferior_class = STATIC_SYMBOL("INFERIOR-CLASS",AB_package);
    string_constant_35 = STATIC_STRING(" that is an inferior-class of");
    role_print_inferior_class_1 = 
	    STATIC_FUNCTION(role_print_inferior_class,NIL,FALSE,2,2);
    mutate_global_property(Qinferior_class,role_print_inferior_class_1,
	    Qrole_server_printer);
    serve_first_inferior_class_1 = 
	    STATIC_FUNCTION(serve_first_inferior_class,NIL,FALSE,2,2);
    mutate_global_property(Qinferior_class,serve_first_inferior_class_1,
	    Qrole_server);
    mutate_global_property(Qinferior_class,Qsymbol,Qdefined_type_of_role);
    mutate_global_property(Qinferior_class,list_constant_8,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinferior_class),
	    Qinverse_role_server)))
	mutate_global_property(Qinferior_class,Nil,Qinverse_role_server);
    Qclass_instances_named_by = STATIC_SYMBOL("CLASS-INSTANCES-NAMED-BY",
	    AB_package);
    string_constant_36 = STATIC_STRING(" that is of the class named by");
    role_print_class_instances_named_by_1 = 
	    STATIC_FUNCTION(role_print_class_instances_named_by,NIL,FALSE,2,2);
    mutate_global_property(Qclass_instances_named_by,
	    role_print_class_instances_named_by_1,Qrole_server_printer);
    serve_first_class_instances_named_by_1 = 
	    STATIC_FUNCTION(serve_first_class_instances_named_by,NIL,FALSE,
	    2,2);
    mutate_global_property(Qclass_instances_named_by,
	    serve_first_class_instances_named_by_1,Qrole_server);
    mutate_global_property(Qclass_instances_named_by,list_constant_8,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qclass_instances_named_by),
	    Qinverse_role_server)))
	mutate_global_property(Qclass_instances_named_by,Nil,
		Qinverse_role_server);
    string_constant_37 = STATIC_STRING("this rule");
    role_print_this_rule_1 = STATIC_FUNCTION(role_print_this_rule,NIL,
	    FALSE,2,2);
    mutate_global_property(Qthis_rule,role_print_this_rule_1,
	    Qrole_server_printer);
    serve_first_this_rule_1 = STATIC_FUNCTION(serve_first_this_rule,NIL,
	    FALSE,2,2);
    mutate_global_property(Qthis_rule,serve_first_this_rule_1,Qrole_server);
    mutate_global_property(Qthis_rule,Qnil,Qrequired_domain_types_of_role);
    if ( !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qthis_rule),
	    Qinverse_role_server)))
	mutate_global_property(Qthis_rule,Nil,Qinverse_role_server);
    serve_first_this_rule_inverse_1 = 
	    STATIC_FUNCTION(serve_first_this_rule_inverse,NIL,FALSE,4,4);
    mutate_global_property(Qthis_rule,serve_first_this_rule_inverse_1,
	    Qinverse_role_server);
    Qthis_procedure = STATIC_SYMBOL("THIS-PROCEDURE",AB_package);
    string_constant_38 = STATIC_STRING("this procedure");
    role_print_this_procedure_1 = 
	    STATIC_FUNCTION(role_print_this_procedure,NIL,FALSE,2,2);
    mutate_global_property(Qthis_procedure,role_print_this_procedure_1,
	    Qrole_server_printer);
    serve_first_this_procedure_1 = 
	    STATIC_FUNCTION(serve_first_this_procedure,NIL,FALSE,2,2);
    mutate_global_property(Qthis_procedure,serve_first_this_procedure_1,
	    Qrole_server);
    mutate_global_property(Qthis_procedure,Qnil,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qthis_procedure),
	    Qinverse_role_server)))
	mutate_global_property(Qthis_procedure,Nil,Qinverse_role_server);
    Qthis_procedure_invocation = STATIC_SYMBOL("THIS-PROCEDURE-INVOCATION",
	    AB_package);
    string_constant_39 = STATIC_STRING("this procedure-invocation");
    role_print_this_procedure_invocation_1 = 
	    STATIC_FUNCTION(role_print_this_procedure_invocation,NIL,FALSE,
	    2,2);
    mutate_global_property(Qthis_procedure_invocation,
	    role_print_this_procedure_invocation_1,Qrole_server_printer);
    serve_first_this_procedure_invocation_1 = 
	    STATIC_FUNCTION(serve_first_this_procedure_invocation,NIL,
	    FALSE,2,2);
    mutate_global_property(Qthis_procedure_invocation,
	    serve_first_this_procedure_invocation_1,Qrole_server);
    mutate_global_property(Qthis_procedure_invocation,Qnil,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qthis_procedure_invocation),
	    Qinverse_role_server)))
	mutate_global_property(Qthis_procedure_invocation,Nil,
		Qinverse_role_server);
    Qrelated = STATIC_SYMBOL("RELATED",AB_package);
    array_constant_6 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)57344L);
    role_print_related_1 = STATIC_FUNCTION(role_print_related,NIL,FALSE,2,2);
    mutate_global_property(Qrelated,role_print_related_1,Qrole_server_printer);
    serve_first_related_1 = STATIC_FUNCTION(serve_first_related,NIL,FALSE,2,2);
    mutate_global_property(Qrelated,serve_first_related_1,Qrole_server);
    mutate_global_property(Qrelated,list_constant_7,
	    Qrequired_domain_types_of_role);
    if ( !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qrelated),
	    Qinverse_role_server)))
	mutate_global_property(Qrelated,Nil,Qinverse_role_server);
    Qrelation = STATIC_SYMBOL("RELATION",AB_package);
    serve_first_related_inverse_1 = 
	    STATIC_FUNCTION(serve_first_related_inverse,NIL,FALSE,4,4);
    mutate_global_property(Qrelated,serve_first_related_inverse_1,
	    Qinverse_role_server);
    Qrelated_role_predicate = STATIC_SYMBOL("RELATED-ROLE-PREDICATE",
	    AB_package);
    mutate_global_property(Qrelated,Qrelated_role_predicate,
	    Qrole_predicate_function);
    SET_SYMBOL_FUNCTION(Qrelated_role_predicate,
	    STATIC_FUNCTION(related_role_predicate,NIL,FALSE,4,4));
    Qfirst_of_list = STATIC_SYMBOL("FIRST-OF-LIST",AB_package);
    string_constant_40 = STATIC_STRING("first");
    role_print_first_of_list_1 = STATIC_FUNCTION(role_print_first_of_list,
	    NIL,FALSE,2,2);
    mutate_global_property(Qfirst_of_list,role_print_first_of_list_1,
	    Qrole_server_printer);
    string_constant_41 = STATIC_STRING(" ~(~a~)");
    array_constant_7 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)57344L);
    serve_first_first_of_list_1 = 
	    STATIC_FUNCTION(serve_first_first_of_list,NIL,FALSE,2,2);
    mutate_global_property(Qfirst_of_list,serve_first_first_of_list_1,
	    Qrole_server);
    Qg2_list = STATIC_SYMBOL("G2-LIST",AB_package);
    list_constant_20 = STATIC_LIST((SI_Long)2L,Qab_class,Qg2_list);
    list_constant_21 = STATIC_CONS(Qsequence,Qnil);
    list_constant_22 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_20,
	    list_constant_21);
    list_constant_23 = STATIC_CONS(list_constant_22,Qnil);
    mutate_global_property(Qfirst_of_list,list_constant_23,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qfirst_of_list),
	    Qinverse_role_server)))
	mutate_global_property(Qfirst_of_list,Nil,Qinverse_role_server);
    serve_first_first_of_list_inverse_1 = 
	    STATIC_FUNCTION(serve_first_first_of_list_inverse,NIL,FALSE,4,4);
    mutate_global_property(Qfirst_of_list,
	    serve_first_first_of_list_inverse_1,Qinverse_role_server);
    Qsecond_of_list = STATIC_SYMBOL("SECOND-OF-LIST",AB_package);
    string_constant_42 = STATIC_STRING("second");
    role_print_second_of_list_1 = 
	    STATIC_FUNCTION(role_print_second_of_list,NIL,FALSE,2,2);
    mutate_global_property(Qsecond_of_list,role_print_second_of_list_1,
	    Qrole_server_printer);
    serve_first_second_of_list_1 = 
	    STATIC_FUNCTION(serve_first_second_of_list,NIL,FALSE,2,2);
    mutate_global_property(Qsecond_of_list,serve_first_second_of_list_1,
	    Qrole_server);
    mutate_global_property(Qsecond_of_list,list_constant_23,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qsecond_of_list),
	    Qinverse_role_server)))
	mutate_global_property(Qsecond_of_list,Nil,Qinverse_role_server);
    serve_first_second_of_list_inverse_1 = 
	    STATIC_FUNCTION(serve_first_second_of_list_inverse,NIL,FALSE,4,4);
    mutate_global_property(Qsecond_of_list,
	    serve_first_second_of_list_inverse_1,Qinverse_role_server);
    Qnext_to_last_of_list = STATIC_SYMBOL("NEXT-TO-LAST-OF-LIST",AB_package);
    string_constant_43 = STATIC_STRING("next to last");
    role_print_next_to_last_of_list_1 = 
	    STATIC_FUNCTION(role_print_next_to_last_of_list,NIL,FALSE,2,2);
    mutate_global_property(Qnext_to_last_of_list,
	    role_print_next_to_last_of_list_1,Qrole_server_printer);
    serve_first_next_to_last_of_list_1 = 
	    STATIC_FUNCTION(serve_first_next_to_last_of_list,NIL,FALSE,2,2);
    mutate_global_property(Qnext_to_last_of_list,
	    serve_first_next_to_last_of_list_1,Qrole_server);
    mutate_global_property(Qnext_to_last_of_list,list_constant_23,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qnext_to_last_of_list),
	    Qinverse_role_server)))
	mutate_global_property(Qnext_to_last_of_list,Nil,Qinverse_role_server);
    serve_first_next_to_last_of_list_inverse_1 = 
	    STATIC_FUNCTION(serve_first_next_to_last_of_list_inverse,NIL,
	    FALSE,4,4);
    mutate_global_property(Qnext_to_last_of_list,
	    serve_first_next_to_last_of_list_inverse_1,Qinverse_role_server);
    Qlast_of_list = STATIC_SYMBOL("LAST-OF-LIST",AB_package);
    string_constant_44 = STATIC_STRING("last");
    role_print_last_of_list_1 = STATIC_FUNCTION(role_print_last_of_list,
	    NIL,FALSE,2,2);
    mutate_global_property(Qlast_of_list,role_print_last_of_list_1,
	    Qrole_server_printer);
    serve_first_last_of_list_1 = STATIC_FUNCTION(serve_first_last_of_list,
	    NIL,FALSE,2,2);
    mutate_global_property(Qlast_of_list,serve_first_last_of_list_1,
	    Qrole_server);
    mutate_global_property(Qlast_of_list,list_constant_23,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlast_of_list),
	    Qinverse_role_server)))
	mutate_global_property(Qlast_of_list,Nil,Qinverse_role_server);
    serve_first_last_of_list_inverse_1 = 
	    STATIC_FUNCTION(serve_first_last_of_list_inverse,NIL,FALSE,4,4);
    mutate_global_property(Qlast_of_list,
	    serve_first_last_of_list_inverse_1,Qinverse_role_server);
    string_constant_45 = 
	    STATIC_STRING("The element type ~NT is incorrect for the g2-list ~NF ~\n              which is missing a type.");
    string_constant_46 = 
	    STATIC_STRING("The element type ~NT is incorrect for the g2-list ~NF ~\n              which is of type ~NT.");
    Qnth_element = STATIC_SYMBOL("NTH-ELEMENT",AB_package);
    string_constant_47 = 
	    STATIC_STRING("nth element of g2-array, g2-list, or sequence");
    role_print_nth_element_1 = STATIC_FUNCTION(role_print_nth_element,NIL,
	    FALSE,2,2);
    mutate_global_property(Qnth_element,role_print_nth_element_1,
	    Qrole_server_printer);
    Qrole_and_designation_print_nth_element = 
	    STATIC_SYMBOL("ROLE-AND-DESIGNATION-PRINT-NTH-ELEMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qrole_and_designation_print_nth_element,
	    STATIC_FUNCTION(role_and_designation_print_nth_element,NIL,
	    TRUE,1,3));
    mutate_global_property(Qnth_element,
	    SYMBOL_FUNCTION(Qrole_and_designation_print_nth_element),
	    Qrole_and_designation_printer);
    serve_first_nth_element_1 = STATIC_FUNCTION(serve_first_nth_element,
	    NIL,FALSE,3,3);
    mutate_global_property(Qnth_element,serve_first_nth_element_1,
	    Qrole_server);
    Qitem_or_value = STATIC_SYMBOL("ITEM-OR-VALUE",AB_package);
    mutate_global_property(Qnth_element,Qitem_or_value,Qdefined_type_of_role);
    Qg2_array = STATIC_SYMBOL("G2-ARRAY",AB_package);
    list_constant_24 = STATIC_LIST((SI_Long)2L,Qab_class,Qg2_array);
    list_constant_25 = STATIC_CONS(Qtext,Qnil);
    list_constant_26 = STATIC_LIST_STAR((SI_Long)5L,Qab_or,
	    list_constant_24,list_constant_20,list_constant_21,
	    list_constant_25);
    list_constant_27 = STATIC_LIST((SI_Long)2L,list_constant_26,Qinteger);
    mutate_global_property(Qnth_element,list_constant_27,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qnth_element),
	    Qinverse_role_server)))
	mutate_global_property(Qnth_element,Nil,Qinverse_role_server);
    string_constant_48 = 
	    STATIC_STRING("The array index ~a is not correct for ~NF.  This array is of length 0.");
    string_constant_49 = 
	    STATIC_STRING("The array index ~a is not in the range 0 to ~a for ~NF.");
    string_constant_50 = 
	    STATIC_STRING("A deleted item was found at index ~a within ~NE.");
    string_constant_51 = 
	    STATIC_STRING("No item-or-value exists at index ~a within ~NE.");
    string_constant_52 = 
	    STATIC_STRING("The index ~a is not correct for ~NE. This sequence is of length 0.");
    string_constant_53 = 
	    STATIC_STRING("The index ~a into the sequence ~NE was out of the ~\n                       bounds 0 through ~a.");
    string_constant_54 = 
	    STATIC_STRING("The index ~a into the text ~NE was out of the bounds 0 ~\n                   through ~a.");
    string_constant_55 = 
	    STATIC_STRING("Cannot reference element ~a of ~NF.  It is neither a g2-list, ~\n              g2-array, sequence, or text.");
    string_constant_56 = 
	    STATIC_STRING("The g2-array ~NF contains no element at index ~a.");
    string_constant_57 = 
	    STATIC_STRING("A reference to element ~a of ~NF failed because the item at ~\n             that location, ~NF, was disabled or inactive.");
    string_constant_58 = 
	    STATIC_STRING("Cannot access element ~a of ~NF.  This g2-list contains no ~\n               elements.");
    string_constant_59 = 
	    string_append2(STATIC_STRING("Cannot reference an element at index ~a in the ~\n               g2-list ~NF.  The index must be in the range from 0 ~\n               to below the number of list elements, whic"),
	    STATIC_STRING("h is ~a."));
    string_constant_60 = 
	    STATIC_STRING("Unable to reference element ~a of ~NF.");
    string_constant_61 = 
	    STATIC_STRING("Cannot reference element ~a of ~NF.  It is neither a g2-list ~\n          nor a g2-array.");
    string_constant_62 = 
	    STATIC_STRING("Cannot reference element ~a of ~NF.  It is neither a g2-list ~\n          nor g2-array.");
    Qelement_iterator = STATIC_SYMBOL("ELEMENT-ITERATOR",AB_package);
    role_print_element_iterator_1 = 
	    STATIC_FUNCTION(role_print_element_iterator,NIL,FALSE,2,2);
    mutate_global_property(Qelement_iterator,role_print_element_iterator_1,
	    Qrole_server_printer);
    string_constant_63 = 
	    STATIC_STRING("~NT is an element-type that is not correct for ~NF.  ~\n                  ~NF is a g2-list that has an element-type of ~NT.");
    string_constant_64 = 
	    STATIC_STRING("~a is not a correct element-type for the g2-list ~NF. ~\n                  ~a is not a defined class or type.");
    Qserve_remaining_list_elements = 
	    STATIC_SYMBOL("SERVE-REMAINING-LIST-ELEMENTS",AB_package);
    Qquantity = STATIC_SYMBOL("QUANTITY",AB_package);
    string_constant_65 = 
	    STATIC_STRING("The element type ~a is not valid for the g2-array ~a.");
    string_constant_66 = 
	    STATIC_STRING("~a is not a correct element-type for the g2-array ~NF. ~\n                  ~a is not a defined class or type.");
    Qserve_remaining_g2_array_elements = 
	    STATIC_SYMBOL("SERVE-REMAINING-G2-ARRAY-ELEMENTS",AB_package);
    string_constant_67 = 
	    STATIC_STRING("Cannot iterate over the elements in ~NF.  It is not a g2-list, ~\n          g2-array, or sequence.");
    serve_first_element_iterator_1 = 
	    STATIC_FUNCTION(serve_first_element_iterator,NIL,FALSE,2,2);
    mutate_global_property(Qelement_iterator,
	    serve_first_element_iterator_1,Qrole_server);
    list_constant_28 = STATIC_CONS(list_constant_21,Qnil);
    list_constant_29 = STATIC_LIST_STAR((SI_Long)4L,Qab_or,
	    list_constant_20,list_constant_24,list_constant_28);
    list_constant_30 = STATIC_CONS(list_constant_29,Qnil);
    mutate_global_property(Qelement_iterator,list_constant_30,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qelement_iterator),
	    Qinverse_role_server)))
	mutate_global_property(Qelement_iterator,Nil,Qinverse_role_server);
    Qserve_next_evaluation_sequence_value = 
	    STATIC_SYMBOL("SERVE-NEXT-EVALUATION-SEQUENCE-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qserve_next_evaluation_sequence_value,
	    STATIC_FUNCTION(serve_next_evaluation_sequence_value,NIL,FALSE,
	    2,2));
    serve_first_element_iterator_inverse_1 = 
	    STATIC_FUNCTION(serve_first_element_iterator_inverse,NIL,FALSE,
	    4,4);
    mutate_global_property(Qelement_iterator,
	    serve_first_element_iterator_inverse_1,Qinverse_role_server);
    Qmember_iterator = STATIC_SYMBOL("MEMBER-ITERATOR",AB_package);
    string_constant_68 = STATIC_STRING("");
    string_constant_69 = STATIC_STRING("~(~a~)~a~a that contains");
    role_print_member_iterator_1 = 
	    STATIC_FUNCTION(role_print_member_iterator,NIL,FALSE,2,2);
    mutate_global_property(Qmember_iterator,role_print_member_iterator_1,
	    Qrole_server_printer);
    serve_first_member_iterator_1 = 
	    STATIC_FUNCTION(serve_first_member_iterator,NIL,FALSE,2,2);
    mutate_global_property(Qmember_iterator,serve_first_member_iterator_1,
	    Qrole_server);
    mutate_global_property(Qmember_iterator,list_constant_20,
	    Qdefined_type_of_role);
    mutate_global_property(Qmember_iterator,list_constant_7,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qmember_iterator),
	    Qinverse_role_server)))
	mutate_global_property(Qmember_iterator,Nil,Qinverse_role_server);
    array_constant_8 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)5L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)8L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)9L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)10L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)12L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)14L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)16L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)18L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)20L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)21L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)22L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)25L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)26L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)27L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)28L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)29L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)30L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)38L,(SI_Long)31L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)39L,(SI_Long)57344L);
    array_constant_9 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)96L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)10L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)11L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)12L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)13L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)14L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)18L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)19L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)20L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)21L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)22L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)23L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)24L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)25L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)27L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)28L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)29L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)30L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)31L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)32L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)33L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)34L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)35L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)36L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)37L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)38L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)39L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)40L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)41L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)42L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)43L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)44L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)45L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)46L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)47L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)48L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)49L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)50L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)51L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)52L,(SI_Long)39L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)53L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)54L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)55L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)56L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)57L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)58L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)59L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)60L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)61L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)62L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)63L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)64L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)65L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)66L,(SI_Long)39L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)67L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)68L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)69L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)70L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)71L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)72L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)73L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)74L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)75L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)76L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)77L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)94L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)95L,(SI_Long)57344L);
    string_constant_70 = STATIC_STRING("~%~S~%");
    serve_first_member_iterator_inverse_1 = 
	    STATIC_FUNCTION(serve_first_member_iterator_inverse,NIL,FALSE,4,4);
    mutate_global_property(Qmember_iterator,
	    serve_first_member_iterator_inverse_1,Qinverse_role_server);
    SET_SYMBOL_FUNCTION(Qserve_remaining_list_elements,
	    STATIC_FUNCTION(serve_remaining_list_elements,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qserve_remaining_g2_array_elements,
	    STATIC_FUNCTION(serve_remaining_g2_array_elements,NIL,FALSE,2,2));
    Qindexed_attribute = STATIC_SYMBOL("INDEXED-ATTRIBUTE",AB_package);
    string_constant_71 = STATIC_STRING("~a");
    string_constant_72 = STATIC_STRING(" ~a");
    array_constant_10 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)9L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)15L,(SI_Long)57344L);
    string_constant_73 = STATIC_STRING("~NQ ");
    string_constant_74 = STATIC_STRING(" of the ~a if indexed with the value");
    role_print_indexed_attribute_1 = 
	    STATIC_FUNCTION(role_print_indexed_attribute,NIL,FALSE,2,2);
    mutate_global_property(Qindexed_attribute,
	    role_print_indexed_attribute_1,Qrole_server_printer);
    Quuid = STATIC_SYMBOL("UUID",AB_package);
    serve_first_indexed_attribute_1 = 
	    STATIC_FUNCTION(serve_first_indexed_attribute,NIL,FALSE,2,2);
    mutate_global_property(Qindexed_attribute,
	    serve_first_indexed_attribute_1,Qrole_server);
    list_constant_31 = STATIC_CONS(Qdatum,Qnil);
    mutate_global_property(Qindexed_attribute,list_constant_31,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qindexed_attribute),
	    Qinverse_role_server)))
	mutate_global_property(Qindexed_attribute,Nil,Qinverse_role_server);
    Qattribute_frame_or_place_reference = 
	    STATIC_SYMBOL("ATTRIBUTE-FRAME-OR-PLACE-REFERENCE",AB_package);
    serve_first_attribute_frame_or_place_reference_1 = 
	    STATIC_FUNCTION(serve_first_attribute_frame_or_place_reference,
	    NIL,FALSE,3,3);
    mutate_global_property(Qattribute_frame_or_place_reference,
	    serve_first_attribute_frame_or_place_reference_1,Qrole_server);
    Qplace_reference = STATIC_SYMBOL("PLACE-REFERENCE",AB_package);
    list_constant_32 = STATIC_CONS(Qplace_reference,Qnil);
    list_constant_33 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_6,
	    list_constant_32);
    mutate_global_property(Qattribute_frame_or_place_reference,
	    list_constant_33,Qdefined_type_of_role);
    list_constant_34 = STATIC_CONS(list_constant_33,list_constant_8);
    mutate_global_property(Qattribute_frame_or_place_reference,
	    list_constant_34,Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qattribute_frame_or_place_reference),
	    Qinverse_role_server)))
	mutate_global_property(Qattribute_frame_or_place_reference,Nil,
		Qinverse_role_server);
    Qelement_frame_or_place_reference = 
	    STATIC_SYMBOL("ELEMENT-FRAME-OR-PLACE-REFERENCE",AB_package);
    serve_first_element_frame_or_place_reference_1 = 
	    STATIC_FUNCTION(serve_first_element_frame_or_place_reference,
	    NIL,FALSE,3,3);
    mutate_global_property(Qelement_frame_or_place_reference,
	    serve_first_element_frame_or_place_reference_1,Qrole_server);
    mutate_global_property(Qelement_frame_or_place_reference,
	    list_constant_33,Qdefined_type_of_role);
    list_constant_35 = STATIC_CONS(list_constant_32,Qnil);
    list_constant_36 = STATIC_LIST_STAR((SI_Long)4L,Qab_or,
	    list_constant_24,list_constant_20,list_constant_35);
    list_constant_37 = STATIC_CONS(Qinteger,Qnil);
    list_constant_38 = STATIC_CONS(list_constant_36,list_constant_37);
    mutate_global_property(Qelement_frame_or_place_reference,
	    list_constant_38,Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qelement_frame_or_place_reference),
	    Qinverse_role_server)))
	mutate_global_property(Qelement_frame_or_place_reference,Nil,
		Qinverse_role_server);
    Qclass_qualified_name_frame_or_place_reference = 
	    STATIC_SYMBOL("CLASS-QUALIFIED-NAME-FRAME-OR-PLACE-REFERENCE",
	    AB_package);
    serve_first_class_qualified_name_frame_or_place_reference_1 = 
	    STATIC_FUNCTION(serve_first_class_qualified_name_frame_or_place_reference,
	    NIL,FALSE,2,2);
    mutate_global_property(Qclass_qualified_name_frame_or_place_reference,
	    serve_first_class_qualified_name_frame_or_place_reference_1,
	    Qrole_server);
    mutate_global_property(Qclass_qualified_name_frame_or_place_reference,
	    list_constant_33,Qdefined_type_of_role);
    list_constant_39 = STATIC_CONS(list_constant_33,Qnil);
    mutate_global_property(Qclass_qualified_name_frame_or_place_reference,
	    list_constant_39,Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qclass_qualified_name_frame_or_place_reference),
	    Qinverse_role_server)))
	mutate_global_property(Qclass_qualified_name_frame_or_place_reference,
		Nil,Qinverse_role_server);
    Qclass_qualified_method = STATIC_SYMBOL("CLASS-QUALIFIED-METHOD",
	    AB_package);
    role_print_class_qualified_method_1 = 
	    STATIC_FUNCTION(role_print_class_qualified_method,NIL,FALSE,2,2);
    mutate_global_property(Qclass_qualified_method,
	    role_print_class_qualified_method_1,Qrole_server_printer);
    serve_first_class_qualified_method_1 = 
	    STATIC_FUNCTION(serve_first_class_qualified_method,NIL,FALSE,2,2);
    mutate_global_property(Qclass_qualified_method,
	    serve_first_class_qualified_method_1,Qrole_server);
    Qab_method = STATIC_SYMBOL("METHOD",AB_package);
    list_constant_40 = STATIC_LIST((SI_Long)2L,Qab_class,Qab_method);
    mutate_global_property(Qclass_qualified_method,list_constant_40,
	    Qdefined_type_of_role);
    mutate_global_property(Qclass_qualified_method,Qnil,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qclass_qualified_method),
	    Qinverse_role_server)))
	mutate_global_property(Qclass_qualified_method,Nil,
		Qinverse_role_server);
    Qnext_procedure_method = STATIC_SYMBOL("NEXT-PROCEDURE-METHOD",AB_package);
    serve_first_next_procedure_method_1 = 
	    STATIC_FUNCTION(serve_first_next_procedure_method,NIL,FALSE,2,2);
    mutate_global_property(Qnext_procedure_method,
	    serve_first_next_procedure_method_1,Qrole_server);
    mutate_global_property(Qnext_procedure_method,list_constant_40,
	    Qdefined_type_of_role);
    mutate_global_property(Qnext_procedure_method,list_constant_7,
	    Qrequired_domain_types_of_role);
    if ( 
	    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(Qnext_procedure_method),
	    Qinverse_role_server)))
	mutate_global_property(Qnext_procedure_method,Nil,
		Qinverse_role_server);
    if (Unique_value_roles == UNBOUND)
	Unique_value_roles = Nil;
    Qunique_value_of_role_server_macro = 
	    STATIC_SYMBOL("UNIQUE-VALUE-OF-ROLE-SERVER-MACRO",AB_package);
    Unique_value_of_role_server_macro_prop = 
	    Qunique_value_of_role_server_macro;
    Qunique_value_of_role_server_function = 
	    STATIC_SYMBOL("UNIQUE-VALUE-OF-ROLE-SERVER-FUNCTION",AB_package);
    Unique_value_of_role_server_function_prop = 
	    Qunique_value_of_role_server_function;
    Qunique_value_of_role_next_role = 
	    STATIC_SYMBOL("UNIQUE-VALUE-OF-ROLE-NEXT-ROLE",AB_package);
    Unique_value_of_role_next_role_prop = Qunique_value_of_role_next_role;
    Qunique_value_of_role_server_domain_count = 
	    STATIC_SYMBOL("UNIQUE-VALUE-OF-ROLE-SERVER-DOMAIN-COUNT",
	    AB_package);
    Unique_value_of_role_server_domain_count_prop = 
	    Qunique_value_of_role_server_domain_count;
    Qnamed_by_symbol = STATIC_SYMBOL("NAMED-BY-SYMBOL",AB_package);
    role_print_named_by_symbol_1 = 
	    STATIC_FUNCTION(role_print_named_by_symbol,NIL,FALSE,2,2);
    mutate_global_property(Qnamed_by_symbol,role_print_named_by_symbol_1,
	    Qrole_server_printer);
    mutate_global_property(Qnamed_by_symbol,FIX((SI_Long)1L),
	    Qunique_value_of_role_server_domain_count);
    mutate_global_property(Qnamed_by_symbol,Qnamed_by,
	    Qunique_value_of_role_next_role);
    unique_value_roles_new_value = adjoin(2,Qnamed_by_symbol,
	    Unique_value_roles);
    Unique_value_roles = unique_value_roles_new_value;
    array_constant_11 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)8L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)11L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)13L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)15L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)16L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)17L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)20L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)21L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)23L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)24L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)25L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)27L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)28L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)29L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)30L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)31L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)32L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)33L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)34L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)35L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)36L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)38L,(SI_Long)37L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)39L,(SI_Long)57344L);
    serve_unique_named_by_symbol_value_1 = 
	    STATIC_FUNCTION(serve_unique_named_by_symbol_value,NIL,FALSE,4,4);
    mutate_global_property(Qnamed_by_symbol,
	    serve_unique_named_by_symbol_value_1,
	    Qunique_value_of_role_server_function);
    Qserve_unique_named_by_symbol_value_macro = 
	    STATIC_SYMBOL("SERVE-UNIQUE-NAMED-BY-SYMBOL-VALUE-MACRO",
	    AB_package);
    mutate_global_property(Qnamed_by_symbol,
	    Qserve_unique_named_by_symbol_value_macro,
	    Qunique_value_of_role_server_macro);
    Qname_of_item = STATIC_SYMBOL("NAME-OF-ITEM",AB_package);
    role_print_name_of_item_1 = STATIC_FUNCTION(role_print_name_of_item,
	    NIL,FALSE,2,2);
    mutate_global_property(Qname_of_item,role_print_name_of_item_1,
	    Qrole_server_printer);
    mutate_global_property(Qname_of_item,FIX((SI_Long)1L),
	    Qunique_value_of_role_server_domain_count);
    mutate_global_property(Qname_of_item,Qname,
	    Qunique_value_of_role_next_role);
    unique_value_roles_new_value = adjoin(2,Qname_of_item,Unique_value_roles);
    Unique_value_roles = unique_value_roles_new_value;
    serve_unique_name_of_item_value_1 = 
	    STATIC_FUNCTION(serve_unique_name_of_item_value,NIL,FALSE,4,4);
    mutate_global_property(Qname_of_item,serve_unique_name_of_item_value_1,
	    Qunique_value_of_role_server_function);
    Qserve_unique_name_of_item_value_macro = 
	    STATIC_SYMBOL("SERVE-UNIQUE-NAME-OF-ITEM-VALUE-MACRO",AB_package);
    mutate_global_property(Qname_of_item,
	    Qserve_unique_name_of_item_value_macro,
	    Qunique_value_of_role_server_macro);
    Qrelated_to_item = STATIC_SYMBOL("RELATED-TO-ITEM",AB_package);
    string_constant_75 = STATIC_STRING(" that is ~(~a~)");
    role_print_related_to_item_1 = 
	    STATIC_FUNCTION(role_print_related_to_item,NIL,FALSE,2,2);
    mutate_global_property(Qrelated_to_item,role_print_related_to_item_1,
	    Qrole_server_printer);
    mutate_global_property(Qrelated_to_item,FIX((SI_Long)1L),
	    Qunique_value_of_role_server_domain_count);
    mutate_global_property(Qrelated_to_item,Qrelated,
	    Qunique_value_of_role_next_role);
    unique_value_roles_new_value = adjoin(2,Qrelated_to_item,
	    Unique_value_roles);
    Unique_value_roles = unique_value_roles_new_value;
    Qone_to_one = STATIC_SYMBOL("ONE-TO-ONE",AB_package);
    Qone_to_many = STATIC_SYMBOL("ONE-TO-MANY",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qone_to_one,Qone_to_many);
    string_constant_76 = 
	    STATIC_STRING(" ~NF.  Note that this relation exists between ~NF and ~\n                         more than one other item.");
    serve_unique_related_to_item_value_1 = 
	    STATIC_FUNCTION(serve_unique_related_to_item_value,NIL,FALSE,4,4);
    mutate_global_property(Qrelated_to_item,
	    serve_unique_related_to_item_value_1,
	    Qunique_value_of_role_server_function);
    Qserve_unique_related_to_item_value_macro = 
	    STATIC_SYMBOL("SERVE-UNIQUE-RELATED-TO-ITEM-VALUE-MACRO",
	    AB_package);
    mutate_global_property(Qrelated_to_item,
	    Qserve_unique_related_to_item_value_macro,
	    Qunique_value_of_role_server_macro);
    string_constant_77 = 
	    STATIC_STRING("The ~a ~NF contains no element at index ~a.");
    Qnth_element_of_integer_array = 
	    STATIC_SYMBOL("NTH-ELEMENT-OF-INTEGER-ARRAY",AB_package);
    string_constant_78 = STATIC_STRING("nth element of integer-array");
    role_print_nth_element_of_integer_array_1 = 
	    STATIC_FUNCTION(role_print_nth_element_of_integer_array,NIL,
	    FALSE,2,2);
    mutate_global_property(Qnth_element_of_integer_array,
	    role_print_nth_element_of_integer_array_1,Qrole_server_printer);
    Qrole_and_designation_print_nth_element_of_integer_array = 
	    STATIC_SYMBOL("ROLE-AND-DESIGNATION-PRINT-NTH-ELEMENT-OF-INTEGER-ARRAY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qrole_and_designation_print_nth_element_of_integer_array,
	    STATIC_FUNCTION(role_and_designation_print_nth_element_of_integer_array,
	    NIL,TRUE,1,3));
    mutate_global_property(Qnth_element_of_integer_array,
	    SYMBOL_FUNCTION(Qrole_and_designation_print_nth_element_of_integer_array),
	    Qrole_and_designation_printer);
    mutate_global_property(Qnth_element_of_integer_array,FIX((SI_Long)2L),
	    Qunique_value_of_role_server_domain_count);
    mutate_global_property(Qnth_element_of_integer_array,Qnth_element,
	    Qunique_value_of_role_next_role);
    unique_value_roles_new_value = adjoin(2,Qnth_element_of_integer_array,
	    Unique_value_roles);
    Unique_value_roles = unique_value_roles_new_value;
    string_constant_79 = STATIC_STRING("integer array");
    serve_unique_nth_element_of_integer_array_value_1 = 
	    STATIC_FUNCTION(serve_unique_nth_element_of_integer_array_value,
	    NIL,FALSE,5,5);
    mutate_global_property(Qnth_element_of_integer_array,
	    serve_unique_nth_element_of_integer_array_value_1,
	    Qunique_value_of_role_server_function);
    Qserve_unique_nth_element_of_integer_array_value_macro = 
	    STATIC_SYMBOL("SERVE-UNIQUE-NTH-ELEMENT-OF-INTEGER-ARRAY-VALUE-MACRO",
	    AB_package);
    mutate_global_property(Qnth_element_of_integer_array,
	    Qserve_unique_nth_element_of_integer_array_value_macro,
	    Qunique_value_of_role_server_macro);
    Qnth_element_of_float_array = 
	    STATIC_SYMBOL("NTH-ELEMENT-OF-FLOAT-ARRAY",AB_package);
    string_constant_80 = STATIC_STRING("nth element of float-array");
    role_print_nth_element_of_float_array_1 = 
	    STATIC_FUNCTION(role_print_nth_element_of_float_array,NIL,
	    FALSE,2,2);
    mutate_global_property(Qnth_element_of_float_array,
	    role_print_nth_element_of_float_array_1,Qrole_server_printer);
    Qrole_and_designation_print_nth_element_of_float_array = 
	    STATIC_SYMBOL("ROLE-AND-DESIGNATION-PRINT-NTH-ELEMENT-OF-FLOAT-ARRAY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qrole_and_designation_print_nth_element_of_float_array,
	    STATIC_FUNCTION(role_and_designation_print_nth_element_of_float_array,
	    NIL,TRUE,1,3));
    mutate_global_property(Qnth_element_of_float_array,
	    SYMBOL_FUNCTION(Qrole_and_designation_print_nth_element_of_float_array),
	    Qrole_and_designation_printer);
    mutate_global_property(Qnth_element_of_float_array,FIX((SI_Long)2L),
	    Qunique_value_of_role_server_domain_count);
    mutate_global_property(Qnth_element_of_float_array,Qnth_element,
	    Qunique_value_of_role_next_role);
    unique_value_roles_new_value = adjoin(2,Qnth_element_of_float_array,
	    Unique_value_roles);
    Unique_value_roles = unique_value_roles_new_value;
    serve_unique_nth_element_of_float_array_value_1 = 
	    STATIC_FUNCTION(serve_unique_nth_element_of_float_array_value,
	    NIL,FALSE,5,5);
    mutate_global_property(Qnth_element_of_float_array,
	    serve_unique_nth_element_of_float_array_value_1,
	    Qunique_value_of_role_server_function);
    Qserve_unique_nth_element_of_float_array_value_macro = 
	    STATIC_SYMBOL("SERVE-UNIQUE-NTH-ELEMENT-OF-FLOAT-ARRAY-VALUE-MACRO",
	    AB_package);
    mutate_global_property(Qnth_element_of_float_array,
	    Qserve_unique_nth_element_of_float_array_value_macro,
	    Qunique_value_of_role_server_macro);
    Qnth_element_of_value_array = 
	    STATIC_SYMBOL("NTH-ELEMENT-OF-VALUE-ARRAY",AB_package);
    string_constant_81 = STATIC_STRING("nth element of value-array");
    role_print_nth_element_of_value_array_1 = 
	    STATIC_FUNCTION(role_print_nth_element_of_value_array,NIL,
	    FALSE,2,2);
    mutate_global_property(Qnth_element_of_value_array,
	    role_print_nth_element_of_value_array_1,Qrole_server_printer);
    Qrole_and_designation_print_nth_element_of_value_array = 
	    STATIC_SYMBOL("ROLE-AND-DESIGNATION-PRINT-NTH-ELEMENT-OF-VALUE-ARRAY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qrole_and_designation_print_nth_element_of_value_array,
	    STATIC_FUNCTION(role_and_designation_print_nth_element_of_value_array,
	    NIL,TRUE,1,3));
    mutate_global_property(Qnth_element_of_value_array,
	    SYMBOL_FUNCTION(Qrole_and_designation_print_nth_element_of_value_array),
	    Qrole_and_designation_printer);
    mutate_global_property(Qnth_element_of_value_array,FIX((SI_Long)2L),
	    Qunique_value_of_role_server_domain_count);
    mutate_global_property(Qnth_element_of_value_array,Qnth_element,
	    Qunique_value_of_role_next_role);
    unique_value_roles_new_value = adjoin(2,Qnth_element_of_value_array,
	    Unique_value_roles);
    Unique_value_roles = unique_value_roles_new_value;
    string_constant_82 = STATIC_STRING("value array");
    serve_unique_nth_element_of_value_array_value_1 = 
	    STATIC_FUNCTION(serve_unique_nth_element_of_value_array_value,
	    NIL,FALSE,5,5);
    mutate_global_property(Qnth_element_of_value_array,
	    serve_unique_nth_element_of_value_array_value_1,
	    Qunique_value_of_role_server_function);
    Qserve_unique_nth_element_of_value_array_value_macro = 
	    STATIC_SYMBOL("SERVE-UNIQUE-NTH-ELEMENT-OF-VALUE-ARRAY-VALUE-MACRO",
	    AB_package);
    mutate_global_property(Qnth_element_of_value_array,
	    Qserve_unique_nth_element_of_value_array_value_macro,
	    Qunique_value_of_role_server_macro);
}
